#include "controlMixer.h"

#include <cmath>

// Lib
#include "debugLog.h"
#include "ntlibc.h"
#include "pidController.h"

// Msg
#include "msgBroker.h"
#include "actuatorOutputMsg.h"
#include "pidControlValMsg.h"

// Module
#include "parameterManager.h"
#include "ledController.h"

namespace module {

    ControlMixer::ControlMixer() :
        _isLWall(false),
        _isRWall(false),
        _center_dist_r(0.0f),
        _center_dist_l(0.0f),
        _ahead_dist_r(0.0f),
        _ahead_dist_l(0.0f),
        _setp_v_xy_body(0.0f),
        _setp_a_xy_body(0.0f),
        _setp_yaw(0.0f),
        _setp_yawrate(0.0f),
        _setp_yawacc(0.0f),
        _traj_type_pre(ETrajType::STOP),
        _traj_type(ETrajType::STOP),
        _turn_type_pre(ETurnType::STOP),
        _turn_type(ETurnType::STOP),
        _duty_r(0.0f),
        _duty_l(0.0f),
        _duty_r_v(0.0f),
        _duty_l_v(0.0f),
        _duty_r_yaw(0.0f),
        _duty_l_yaw(0.0f),
        _error_sec(0.0f),
        _is_error(false) {
        setModuleName("ControlMixer");
        _resetController();
    }

    void ControlMixer::update0() {
        _msgUpdate();
        _updateControllerParam();
        _updateController();

        if(_nav_msg.mode == ENavMode::STANDBY || _nav_msg.mode == ENavMode::FASTEST || _nav_msg.mode == ENavMode::SEARCH) {
            _publish();
        }
    }

    void ControlMixer::setDeltaT(float delta_t) {
        _delta_t = delta_t;
        _wall_pidf.setDeltaT(delta_t);
        _wall_diag_pidf.setDeltaT(delta_t);
        _yaw_pidf.setDeltaT(delta_t);
        _yawrate_pidf.setDeltaT(delta_t);
        _v_pidf.setDeltaT(delta_t);
        _wall_dist_pidf.setDeltaT(delta_t);
        _wall_diff_pidf.setDeltaT(delta_t);
    };

    void ControlMixer::debug() {
        PRINTF_ASYNC("  duty_r     : %f\n", _duty_r);
        PRINTF_ASYNC("  duty_l     : %f\n", _duty_l);
        PRINTF_ASYNC("  duty_r_v   : %f\n", _duty_r_v);
        PRINTF_ASYNC("  duty_l_v   : %f\n", _duty_l_v);
        PRINTF_ASYNC("  duty_r_yaw : %f\n", _duty_r_yaw);
        PRINTF_ASYNC("  duty_l_yaw : %f\n", _duty_l_yaw);
        PRINTF_ASYNC("  traj_type  : %s\n", trajType2Str(_traj_type).c_str());
        PRINTF_ASYNC("  turn_type  : %s\n", turnType2Str(_turn_type).c_str());
    }


    void ControlMixer::_msgUpdate() {
        copyMsg(msg_id::CTRL_SETPOINT, &_setp_msg);
        copyMsg(msg_id::NAV_STATE, &_nav_msg);
        copyMsg(msg_id::WALL_SENSOR, &_ws_msg);
        copyMsg(msg_id::VEHICLE_ATTITUDE, &_att_msg);
        copyMsg(msg_id::VEHICLE_POSITION, &_pos_msg);

        _traj_type_pre = _traj_type;
        _turn_type_pre = _turn_type;
        _traj_type = _setp_msg.traj_type;
        _turn_type = _setp_msg.turn_type;
    }

    void ControlMixer::_updateControllerParam() {
        ParameterManager& pm = ParameterManager::getInstance();

        // ??????, ?????????, ??????PIDF???????????????
        if(_traj_type == ETrajType::STOP || _traj_type == ETrajType::SPINTURN) {
            _v_pidf.set(pm.spin_v_p, pm.spin_v_i, pm.spin_v_d, pm.spin_v_f);
            _yawrate_pidf.set(pm.spin_yawrate_p, pm.spin_yawrate_i, pm.spin_yawrate_d, pm.spin_yawrate_f);
            _yaw_pidf.set(pm.spin_yaw_p, pm.spin_yaw_i, 0.0f, 0.0f);

        }
        else if(_nav_msg.mode == ENavMode::FASTEST) {
            _v_pidf.set(pm.fast_v_p, pm.fast_v_i, pm.fast_v_d, pm.fast_v_f);
            _yawrate_pidf.set(pm.fast_yawrate_p, pm.fast_yawrate_i, pm.fast_yawrate_d, pm.fast_yawrate_f);
            _yaw_pidf.set(pm.fast_yaw_p, pm.fast_yaw_i, 0.0f, 0.0f);
        }
        else if(_nav_msg.mode == ENavMode::SEARCH) {
            _v_pidf.set(pm.search_v_p, pm.search_v_i, pm.search_v_d, pm.search_v_f);
            _yawrate_pidf.set(pm.search_yawrate_p, pm.search_yawrate_i, pm.search_yawrate_d, pm.search_yawrate_f);
            _yaw_pidf.set(pm.search_yaw_p, pm.search_yaw_i, 0.0f, 0.0f);
        }
        else {
            _v_pidf.set(pm.search_v_p, pm.search_v_i, pm.search_v_d, pm.search_v_f);
            _yawrate_pidf.set(pm.search_yawrate_p, pm.search_yawrate_i, pm.search_yawrate_d, pm.search_yawrate_f);
            _yaw_pidf.set(pm.search_yaw_p, pm.search_yaw_i, 0.0f, 0.0f);
        }

        // ???PIDF???????????????
        _wall_pidf.set(pm.wall_p, pm.wall_i, pm.wall_d, pm.wall_f);

        // ??????PIDF???????????????
        _wall_diag_pidf.set(pm.wall_diag_p, pm.wall_diag_i, pm.wall_diag_d, pm.wall_diag_f);

        // FB???????????????????????????
        _v_pidf.setEnable(pm.v_fb_enable);
        _yawrate_pidf.setEnable(pm.yawrate_fb_enable);
        _yaw_pidf.setEnable(pm.yaw_fb_enable);
        _wall_pidf.setEnable(pm.wall_fb_enable);
        _wall_diag_pidf.setEnable(pm.wall_diag_fb_enable);

        // ????????????????????????enable??????
        if(_traj_type == ETrajType::STOP || _traj_type == ETrajType::SPINTURN) {
            _v_pidf.setSaturationEnable(false);
            _yawrate_pidf.setSaturationEnable(false);
        }
        else {
            _v_pidf.setSaturationEnable(pm.v_saturation_enable);
            _yawrate_pidf.setSaturationEnable(pm.yawrate_saturation_enable);
        }

        _yaw_pidf.setSaturationEnable(pm.yaw_saturation_enable);
        _wall_pidf.setSaturationEnable(pm.wall_saturation_enable);
        _wall_diag_pidf.setSaturationEnable(pm.wall_diag_saturation_enable);

        // ?????????????????????????????????
        //_v_pidf?????????_yawrate_pidf?????????????????????????????????updateController()?????????
        _yaw_pidf.setSaturation(pm.yaw_saturation);
        _wall_pidf.setSaturation(pm.wall_saturation);
        _wall_diag_pidf.setSaturation(pm.wall_diag_saturation);

        // ???????????????????????????????????????????????????
        _v_pidf.setIntegralSaturationEnable(pm.v_i_saturation_enable);
        _yawrate_pidf.setIntegralSaturationEnable(pm.yawrate_i_saturation_enable);
        _yaw_pidf.setIntegralSaturationEnable(pm.yaw_i_saturation_enable);
        _wall_pidf.setIntegralSaturationEnable(pm.wall_i_saturation_enable);
        _wall_diag_pidf.setIntegralSaturationEnable(pm.wall_diag_i_saturation_enable);

        // ???????????????????????????????????????
        _v_pidf.setIntegralSaturation(pm.v_i_saturation);
        _yawrate_pidf.setIntegralSaturation(pm.yawrate_i_saturation);
        _yaw_pidf.setIntegralSaturation(pm.yaw_i_saturation);
        _wall_pidf.setIntegralSaturation(pm.wall_i_saturation);
        _wall_diag_pidf.setIntegralSaturation(pm.wall_diag_i_saturation);

        // ??????????????????????????????
        constexpr float DEG2RAD = 180.0f/3.14159265f;
        _wall_dist_pidf.setEnable(true);
        _wall_dist_pidf.setIntegralSaturationEnable(true);
        _wall_dist_pidf.setSaturationEnable(true);
        _wall_dist_pidf.set(pm.wall_dist_p, pm.wall_dist_i, 0.0f, 0.0f);
        _wall_dist_pidf.setSaturation(0.3f);
        _wall_dist_pidf.setIntegralSaturation(0.15f);
        _wall_diff_pidf.setEnable(true);
        _wall_diff_pidf.setIntegralSaturationEnable(true);
        _wall_diff_pidf.setSaturationEnable(true);
        _wall_diff_pidf.setSaturation(360.0f * DEG2RAD);
        _wall_diff_pidf.setIntegralSaturation(45.0f * DEG2RAD);
        _wall_diff_pidf.set(pm.wall_diff_p, pm.wall_diff_i, 0.0f, 0.0f);
    }

    void ControlMixer::_updateController() {
        _setp_v_xy_body = _setp_msg.v_xy_body;
        _setp_yaw = _setp_msg.yaw;
        _setp_yawrate = _setp_msg.yawrate;

        if(_nav_msg.mode == ENavMode::DEBUG || _setp_msg.traj_type == ETrajType::NONE) {
            _resetController();
            return;
        }

        ParameterManager& pm = ParameterManager::getInstance();

        // ????????? or ????????????????????????????????????????????????
        if( _traj_type != _traj_type_pre &&
                (_traj_type_pre == ETrajType::STOP || _traj_type_pre == ETrajType::SPINTURN)
          ) {
            _resetController();
        }

        // ?????????
        if(_turn_type == ETurnType::STRAIGHT_CENTER || _turn_type == ETurnType::STRAIGHT_CENTER_EDGE) {
            float wall_center_r = pm.wall_center_r;
            float wall_center_l = pm.wall_center_l;
            _wall_pidf.update(wall_center_r - _ws_msg.dist_r, wall_center_l - _ws_msg.dist_l, _nav_msg.r_wall_enable, _nav_msg.l_wall_enable);
            //_wall_pidf.update(0.045f - _ws_msg.dist_r, 0.045f - _ws_msg.dist_l, true, true);
            // ?????????????????????????????????, ?????????????????????????????????????????????
            float v_now = _pos_msg.v_xy_body_for_ctrl;

            if(v_now < 0.05f) v_now = 0.05f;

            if(v_now > 1.0f) v_now = 1.0f;

            _setp_yawrate += v_now * _wall_pidf.getControlVal();
        }
        else {
            _wall_pidf.reset();
        }

        // ??????????????????????????????????????????
        if(_turn_type == ETurnType::DIAGONAL_CENTER || _turn_type == ETurnType::DIAGONAL_CENTER_EDGE ||
                (_turn_type == ETurnType::STRAIGHT_CENTER_EDGE && !_setp_msg.in_detect_edge_area && (_nav_msg.in_skewers_area))
          ) {
            float v_now = _pos_msg.v_xy_body_for_ctrl;

            if(v_now < 0.1f) v_now = 0.1f;

            if(v_now > 1.0f) v_now = 1.0f;

            bool ctrl_ccw = false;
            bool ctrl_cw = false;
            float thr_al = 0.0f;
            float thr_ar = 0.0f;

            if(_turn_type == ETurnType::DIAGONAL_CENTER || _turn_type == ETurnType::DIAGONAL_CENTER_EDGE) {
                thr_al = pm.diag_ctrl_dist_thr_l;
                thr_ar = pm.diag_ctrl_dist_thr_r;
            }
            else {
                thr_al = pm.ca_ctrl_dist_thr_l;
                thr_ar = pm.ca_ctrl_dist_thr_r;
            }

            //???????????????????????????????????????????????????
            if(_ws_msg.dist_al < thr_al && _ws_msg.dist_ar < thr_ar) {
                if(_turn_type == ETurnType::DIAGONAL_CENTER || _turn_type == ETurnType::DIAGONAL_CENTER_EDGE) {
                    ctrl_ccw = false;
                    ctrl_cw = false;
                }
                else {
                    if(_ws_msg.dist_al < _ws_msg.dist_ar) ctrl_cw = true;
                    else ctrl_ccw = true;
                }
            }
            else if(_ws_msg.dist_al < thr_al) {
                ctrl_cw = true;
            }
            else if(_ws_msg.dist_ar < thr_ar) {
                ctrl_ccw = true;
            }

            if (ctrl_ccw) {
                float target = 1.0f;

                if(_turn_type == ETurnType::DIAGONAL_CENTER || _turn_type == ETurnType::DIAGONAL_CENTER_EDGE) target = pm.diag_ctrl_dist_thr_l;
                else target = pm.ca_ctrl_dist_thr_l;

                _wall_diag_pidf.update(_ws_msg.dist_al, target);
                _setp_yawrate += v_now * _wall_diag_pidf.getControlVal();
                module::LedController::getInstance().turnRightLed(1);
            }
            else if (ctrl_cw) {
                float target = 1.0f;

                if(_turn_type == ETurnType::DIAGONAL_CENTER || _turn_type == ETurnType::DIAGONAL_CENTER_EDGE) target = pm.diag_ctrl_dist_thr_r;
                else target = pm.ca_ctrl_dist_thr_r;

                _wall_diag_pidf.update(_ws_msg.dist_ar, target);
                _setp_yawrate += - v_now * _wall_diag_pidf.getControlVal();
                module::LedController::getInstance().turnLeftLed(1);
            }
            else {
                _wall_diag_pidf.reset();
                module::LedController::getInstance().turnRightLed(0);
                module::LedController::getInstance().turnLeftLed(0);

            }
        }
        else {
            _wall_diag_pidf.reset();
            module::LedController::getInstance().turnRightLed(0);
            module::LedController::getInstance().turnLeftLed(0);
        }

        // ????????????????????????
        if(_turn_type == ETurnType::AHEAD_WALL_CORRECTION || _turn_type == ETurnType::AHEAD_WALL_YAW_CORRECTION) {
            float dist_setp = 0.045f;
            float wall_dist = _ws_msg.dist_a;

            _wall_dist_pidf.update(dist_setp, wall_dist); // ???????????????
            _setp_v_xy_body = -_wall_dist_pidf.getControlVal();
        }
        else {
            _wall_dist_pidf.reset();
        }

        if(_turn_type == ETurnType::AHEAD_WALL_YAW_CORRECTION) {
            float diff_setp = 0.0f;
            float wall_diff = _ws_msg.dist_al - _ws_msg.dist_ar;
            _wall_diff_pidf.update(diff_setp, wall_diff); // ??????????????????

            if(_ws_msg.dist_a < 0.032f) {
                _wall_diff_pidf.reset();
            }

            _setp_yawrate = _wall_diff_pidf.getControlVal();
        }
        else {
            _wall_diff_pidf.reset();
        }

        // ????????????
        if( _turn_type == ETurnType::DIAGONAL_CENTER || _turn_type == ETurnType::DIAGONAL_CENTER_EDGE ||
                _wall_pidf.engaged() || _wall_diag_pidf.engaged() ||_turn_type == ETurnType::AHEAD_WALL_YAW_CORRECTION) {
            _yaw_pidf.reset();
        }
        else {
            _yaw_pidf.update(_setp_yaw, _att_msg.yaw);
            _setp_yawrate += _yaw_pidf.getControlVal();
        }



        // ??????, ????????????????????????
        _v_pidf.update(_setp_v_xy_body, _pos_msg.v_xy_body_for_ctrl);
        _yawrate_pidf.update(_setp_yawrate, _att_msg.yawrate);

        _duty_r = 0.0f;
        _duty_l = 0.0f;
        _duty_r_v = 0.0f;
        _duty_l_v = 0.0f;
        _duty_r_yaw = 0.0f;
        _duty_l_yaw = 0.0f;
        float duty_v_saturation = 0.0f;
        float duty_yawrate_saturation = 0.0f;

        // ??????FF??????
        float v_ff = pm.v_ff_coef * _setp_v_xy_body + pm.v_ff_offset;
        float a_ff = pm.a_ff_coef * _setp_a_xy_body + pm.a_ff_offset;

        if(pm.v_ff_enable && _setp_v_xy_body > 0.01f) {
            _duty_r_v += v_ff + a_ff;
            _duty_l_v += v_ff + a_ff;
            duty_v_saturation = std::min(pm.v_saturation_ff_multiplier * (v_ff + a_ff), pm.v_saturation_offset_duty);
        }
        else {
            duty_v_saturation = pm.v_saturation_offset_duty;
        }

        // ?????????FF??????
        float yawrate_ff = pm.yawrate_ff_coef * std::fabs(_setp_yawrate) + pm.yawrate_ff_offset;
        float yawacc_ff = pm.yawacc_ff_coef * std::fabs(_setp_yawacc) + pm.yawacc_ff_offset;

        if(pm.yawrate_ff_enable && std::fabs(_setp_yawrate) > 0.52f) { // 0.52 rad/s = 30 deg/s
            float rate_sign = _sign(_setp_yawrate);
            float acc_sign = _sign(_setp_yawacc);

            _duty_r_yaw +=    rate_sign * yawrate_ff + acc_sign * yawacc_ff;
            _duty_l_yaw += - (rate_sign * yawrate_ff + acc_sign * yawacc_ff);
            float ff_saturation = pm.yawrate_saturation_ff_multiplier * std::fabs(rate_sign * yawrate_ff + acc_sign * yawacc_ff);
            duty_yawrate_saturation = std::min(ff_saturation, pm.yawrate_saturation_offset_duty);
        }
        else {
            duty_yawrate_saturation = pm.yawrate_saturation_offset_duty;
        }

        // ??????????????????saturation
        if(_traj_type == ETrajType::STOP || _traj_type == ETrajType::SPINTURN) {
            // do nothing
        }
        else {
            _v_pidf.setSaturation(duty_v_saturation);
            _yawrate_pidf.setSaturation(duty_yawrate_saturation);
        }

        // duty????????????
        _duty_r_v += _v_pidf.getControlVal();        
        _duty_l_v += _v_pidf.getControlVal();
        _duty_r_yaw +=   _yawrate_pidf.getControlVal();
        _duty_l_yaw += - _yawrate_pidf.getControlVal();                
        _duty_r = _duty_r_v + _duty_r_yaw;
        _duty_l = _duty_l_v + _duty_l_yaw;

        // ?????????????????????
        if( !(_turn_type == ETurnType::AHEAD_WALL_CORRECTION || _turn_type == ETurnType::AHEAD_WALL_YAW_CORRECTION) &&
                (std::fabs(_yawrate_pidf.getError()) > YAWRATE_ERROR_TH ||
                 std::fabs(_v_pidf.getError()) > V_ERROR_TH ||
                 std::fabs(_yaw_pidf.getError()) > YAW_ERROR_TH) ||
                (std::fabs(_pos_msg.v_xy_body_enc) < 0.1f && _setp_msg.v_xy_body > 0.1f)
          ) {
            _error_sec += _delta_t;
        }
        else {
            _error_sec = 0.0f;
        }

        _is_error = (_error_sec > ERROR_TIME_TH);
    }

    void ControlMixer::_resetController() {
        _wall_pidf.reset();
        _wall_diag_pidf.reset();
        _yaw_pidf.reset();
        _yawrate_pidf.reset();
        _v_pidf.reset();
        _wall_dist_pidf.reset();
        _wall_diff_pidf.reset();
    }


    void ControlMixer::_publish() {
        ActuatorOutputMsg out_msg;
        PidControlValMsg pid_msg;
        out_msg.duty_r = _duty_r;
        out_msg.duty_l = _duty_l;
        out_msg.duty_r_v = _duty_r_v;
        out_msg.duty_l_v = _duty_l_v;
        out_msg.duty_r_yaw = _duty_r_yaw;
        out_msg.duty_l_yaw = _duty_l_yaw;
        out_msg.is_error = _is_error;

        out_msg.ctrl_mode = ECtrlMode::VEHICLE;

        pid_msg.v_p = _v_pidf.getPVal();
        pid_msg.v_i = _v_pidf.getIVal();
        pid_msg.v_d = _v_pidf.getDVal();
        pid_msg.yawrate_p = _yawrate_pidf.getPVal();
        pid_msg.yawrate_i = _yawrate_pidf.getIVal();
        pid_msg.yawrate_d = _yawrate_pidf.getDVal();
        pid_msg.yaw_p = _yaw_pidf.getPVal();
        pid_msg.yaw_i = _yaw_pidf.getIVal();
        pid_msg.yaw_d = _yaw_pidf.getDVal();
        pid_msg.wall_p = _wall_pidf.getPVal();
        pid_msg.wall_i = _wall_pidf.getIVal();
        pid_msg.wall_d = _wall_pidf.getDVal();
        pid_msg.diag_p = _wall_diag_pidf.getPVal();
        pid_msg.diag_i = _wall_diag_pidf.getIVal();
        pid_msg.diag_d = _wall_diag_pidf.getDVal();

        pid_msg.setp_v_xy_body = _setp_v_xy_body;
        pid_msg.setp_yaw = _setp_yaw;
        pid_msg.setp_yawrate = _setp_yawrate;

        publishMsg(msg_id::ACTUATOR_OUTPUT, &out_msg);
        publishMsg(msg_id::PID_CONTROL_VAL, &pid_msg);
    }

    float ControlMixer::_sign(float val) {
        if(val > 0.0f) return 1.0f;
        else if(val < 0.0f) return -1.0f;
        else return 0.0f;
    }

    int usrcmd_controlMixer(int argc, char** argv) {
        if (ntlibc_strcmp(argv[1], "help") == 0) {
            PRINTF_ASYNC("  status :\r\n");
            return 0;
        }

        if (ntlibc_strcmp(argv[1], "status") == 0) {
            ControlMixer::getInstance().debug();
            return 0;
        }

        return 0;
    };
}
