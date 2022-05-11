#pragma once

constexpr float INT_MOLLIFIER_F_IN_MIN = 0.0f;
constexpr float INT_MOLLIFIER_F_IN_MAX = 6.0f;
constexpr float INT_MOLLIFIER_F_IN_DELTA = 0.01f;
constexpr int INT_MOLLIFIER_F_TBL_SIZE = 601;
// int_moli(c)のcを0.0から6.0まで0.01刻みで変えた時のテーブル
constexpr float INT_MOLLIFIER_F_TBL[INT_MOLLIFIER_F_TBL_SIZE] {
    0.000000000f,
    0.000000028f,
    0.000005723f,
    0.000068947f,
    0.000301698f,
    0.000821088f,
    0.001712135f,
    0.003021874f,
    0.004766381f,
    0.006940046f,
    0.009523439f,
    0.012489108f,
    0.015805571f,
    0.019439935f,
    0.023359554f,
    0.027533040f,
    0.031930826f,
    0.036525454f,
    0.041291678f,
    0.046206445f,
    0.051248822f,
    0.056399868f,
    0.061642496f,
    0.066961330f,
    0.072342552f,
    0.077773763f,
    0.083243852f,
    0.088742868f,
    0.094261912f,
    0.099793026f,
    0.105329103f,
    0.110863804f,
    0.116391475f,
    0.121907081f,
    0.127406143f,
    0.132884685f,
    0.138339176f,
    0.143766495f,
    0.149163882f,
    0.154528907f,
    0.159859434f,
    0.165153593f,
    0.170409755f,
    0.175626507f,
    0.180802628f,
    0.185937075f,
    0.191028963f,
    0.196077549f,
    0.201082217f,
    0.206042470f,
    0.210957913f,
    0.215828246f,
    0.220653253f,
    0.225432795f,
    0.230166802f,
    0.234855264f,
    0.239498228f,
    0.244095789f,
    0.248648089f,
    0.253155308f,
    0.257617661f,
    0.262035398f,
    0.266408793f,
    0.270738149f,
    0.275023788f,
    0.279266054f,
    0.283465307f,
    0.287621923f,
    0.291736289f,
    0.295808805f,
    0.299839882f,
    0.303829936f,
    0.307779393f,
    0.311688682f,
    0.315558237f,
    0.319388498f,
    0.323179906f,
    0.326932902f,
    0.330647931f,
    0.334325438f,
    0.337965866f,
    0.341569658f,
    0.345137257f,
    0.348669103f,
    0.352165635f,
    0.355627288f,
    0.359054496f,
    0.362447688f,
    0.365807292f,
    0.369133730f,
    0.372427422f,
    0.375688784f,
    0.378918227f,
    0.382116158f,
    0.385282981f,
    0.388419094f,
    0.391524890f,
    0.394600761f,
    0.397647089f,
    0.400664256f,
    0.403652638f,
    0.406612604f,
    0.409544520f,
    0.412448749f,
    0.415325646f,
    0.418175562f,
    0.420998846f,
    0.423795839f,
    0.426566878f,
    0.429312297f,
    0.432032423f,
    0.434727579f,
    0.437398086f,
    0.440044257f,
    0.442666401f,
    0.445264825f,
    0.447839828f,
    0.450391709f,
    0.452920758f,
    0.455427264f,
    0.457911510f,
    0.460373776f,
    0.462814337f,
    0.465233465f,
    0.467631427f,
    0.470008486f,
    0.472364901f,
    0.474700929f,
    0.477016820f,
    0.479312822f,
    0.481589181f,
    0.483846137f,
    0.486083926f,
    0.488302782f,
    0.490502936f,
    0.492684613f,
    0.494848037f,
    0.496993429f,
    0.499121003f,
    0.501230975f,
    0.503323555f,
    0.505398948f,
    0.507457360f,
    0.509498991f,
    0.511524040f,
    0.513532702f,
    0.515525168f,
    0.517501629f,
    0.519462271f,
    0.521407278f,
    0.523336831f,
    0.525251109f,
    0.527150287f,
    0.529034539f,
    0.530904037f,
    0.532758947f,
    0.534599437f,
    0.536425670f,
    0.538237807f,
    0.540036007f,
    0.541820426f,
    0.543591220f,
    0.545348539f,
    0.547092534f,
    0.548823353f,
    0.550541142f,
    0.552246044f,
    0.553938201f,
    0.555617753f,
    0.557284836f,
    0.558939588f,
    0.560582142f,
    0.562212629f,
    0.563831181f,
    0.565437924f,
    0.567032987f,
    0.568616493f,
    0.570188566f,
    0.571749327f,
    0.573298896f,
    0.574837391f,
    0.576364929f,
    0.577881624f,
    0.579387589f,
    0.580882937f,
    0.582367777f,
    0.583842220f,
    0.585306371f,
    0.586760336f,
    0.588204221f,
    0.589638129f,
    0.591062160f,
    0.592476416f,
    0.593880996f,
    0.595275997f,
    0.596661515f,
    0.598037646f,
    0.599404484f,
    0.600762122f,
    0.602110651f,
    0.603450161f,
    0.604780742f,
    0.606102481f,
    0.607415466f,
    0.608719782f,
    0.610015514f,
    0.611302746f,
    0.612581559f,
    0.613852036f,
    0.615114257f,
    0.616368301f,
    0.617614247f,
    0.618852173f,
    0.620082154f,
    0.621304266f,
    0.622518584f,
    0.623725181f,
    0.624924131f,
    0.626115505f,
    0.627299373f,
    0.628475807f,
    0.629644875f,
    0.630806646f,
    0.631961187f,
    0.633108566f,
    0.634248847f,
    0.635382096f,
    0.636508378f,
    0.637627755f,
    0.638740291f,
    0.639846049f,
    0.640945088f,
    0.642037470f,
    0.643123255f,
    0.644202501f,
    0.645275268f,
    0.646341612f,
    0.647401592f,
    0.648455264f,
    0.649502682f,
    0.650543904f,
    0.651578982f,
    0.652607971f,
    0.653630924f,
    0.654647893f,
    0.655658932f,
    0.656664090f,
    0.657663419f,
    0.658656970f,
    0.659644791f,
    0.660626933f,
    0.661603443f,
    0.662574369f,
    0.663539760f,
    0.664499661f,
    0.665454120f,
    0.666403183f,
    0.667346894f,
    0.668285299f,
    0.669218441f,
    0.670146366f,
    0.671069116f,
    0.671986734f,
    0.672899264f,
    0.673806745f,
    0.674709222f,
    0.675606733f,
    0.676499321f,
    0.677387025f,
    0.678269885f,
    0.679147941f,
    0.680021231f,
    0.680889794f,
    0.681753668f,
    0.682612890f,
    0.683467499f,
    0.684317530f,
    0.685163021f,
    0.686004008f,
    0.686840525f,
    0.687672610f,
    0.688500296f,
    0.689323618f,
    0.690142611f,
    0.690957309f,
    0.691767744f,
    0.692573951f,
    0.693375963f,
    0.694173810f,
    0.694967527f,
    0.695757145f,
    0.696542695f,
    0.697324208f,
    0.698101717f,
    0.698875250f,
    0.699644839f,
    0.700410513f,
    0.701172302f,
    0.701930236f,
    0.702684343f,
    0.703434653f,
    0.704181193f,
    0.704923993f,
    0.705663080f,
    0.706398482f,
    0.707130226f,
    0.707858339f,
    0.708582848f,
    0.709303780f,
    0.710021162f,
    0.710735018f,
    0.711445376f,
    0.712152260f,
    0.712855696f,
    0.713555709f,
    0.714252324f,
    0.714945566f,
    0.715635459f,
    0.716322026f,
    0.717005293f,
    0.717685282f,
    0.718362017f,
    0.719035522f,
    0.719705819f,
    0.720372931f,
    0.721036881f,
    0.721697691f,
    0.722355383f,
    0.723009980f,
    0.723661502f,
    0.724309972f,
    0.724955411f,
    0.725597840f,
    0.726237279f,
    0.726873751f,
    0.727507275f,
    0.728137871f,
    0.728765560f,
    0.729390362f,
    0.730012297f,
    0.730631384f,
    0.731247643f,
    0.731861094f,
    0.732471754f,
    0.733079643f,
    0.733684781f,
    0.734287185f,
    0.734886874f,
    0.735483866f,
    0.736078180f,
    0.736669832f,
    0.737258842f,
    0.737845227f,
    0.738429004f,
    0.739010190f,
    0.739588803f,
    0.740164860f,
    0.740738378f,
    0.741309372f,
    0.741877861f,
    0.742443860f,
    0.743007385f,
    0.743568453f,
    0.744127080f,
    0.744683282f,
    0.745237074f,
    0.745788472f,
    0.746337491f,
    0.746884147f,
    0.747428455f,
    0.747970430f,
    0.748510086f,
    0.749047440f,
    0.749582505f,
    0.750115296f,
    0.750645827f,
    0.751174113f,
    0.751700169f,
    0.752224007f,
    0.752745642f,
    0.753265088f,
    0.753782358f,
    0.754297467f,
    0.754810427f,
    0.755321253f,
    0.755829957f,
    0.756336552f,
    0.756841052f,
    0.757343469f,
    0.757843817f,
    0.758342108f,
    0.758838354f,
    0.759332569f,
    0.759824765f,
    0.760314954f,
    0.760803148f,
    0.761289359f,
    0.761773600f,
    0.762255882f,
    0.762736218f,
    0.763214618f,
    0.763691095f,
    0.764165661f,
    0.764638325f,
    0.765109101f,
    0.765578000f,
    0.766045031f,
    0.766510208f,
    0.766973540f,
    0.767435038f,
    0.767894714f,
    0.768352578f,
    0.768808641f,
    0.769262914f,
    0.769715406f,
    0.770166129f,
    0.770615093f,
    0.771062307f,
    0.771507783f,
    0.771951530f,
    0.772393558f,
    0.772833877f,
    0.773272498f,
    0.773709430f,
    0.774144682f,
    0.774578265f,
    0.775010187f,
    0.775440459f,
    0.775869090f,
    0.776296089f,
    0.776721465f,
    0.777145229f,
    0.777567388f,
    0.777987952f,
    0.778406930f,
    0.778824330f,
    0.779240163f,
    0.779654436f,
    0.780067159f,
    0.780478339f,
    0.780887986f,
    0.781296109f,
    0.781702715f,
    0.782107813f,
    0.782511411f,
    0.782913518f,
    0.783314143f,
    0.783713292f,
    0.784110975f,
    0.784507199f,
    0.784901972f,
    0.785295303f,
    0.785687199f,
    0.786077668f,
    0.786466718f,
    0.786854356f,
    0.787240590f,
    0.787625429f,
    0.788008878f,
    0.788390946f,
    0.788771641f,
    0.789150969f,
    0.789528938f,
    0.789905556f,
    0.790280829f,
    0.790654764f,
    0.791027370f,
    0.791398652f,
    0.791768618f,
    0.792137276f,
    0.792504631f,
    0.792870690f,
    0.793235461f,
    0.793598951f,
    0.793961165f,
    0.794322112f,
    0.794681796f,
    0.795040226f,
    0.795397407f,
    0.795753346f,
    0.796108050f,
    0.796461525f,
    0.796813777f,
    0.797164812f,
    0.797514638f,
    0.797863259f,
    0.798210683f,
    0.798556915f,
    0.798901962f,
    0.799245830f,
    0.799588525f,
    0.799930052f,
    0.800270418f,
    0.800609628f,
    0.800947689f,
    0.801284606f,
    0.801620385f,
    0.801955032f,
    0.802288552f,
    0.802620952f,
    0.802952236f,
    0.803282411f,
    0.803611482f,
    0.803939454f,
    0.804266333f,
    0.804592125f,
    0.804916834f,
    0.805240467f,
    0.805563029f,
    0.805884524f,
    0.806204958f,
    0.806524337f,
    0.806842666f,
    0.807159949f,
    0.807476192f,
    0.807791400f,
    0.808105578f,
    0.808418732f,
    0.808730865f,
    0.809041984f,
    0.809352092f,
    0.809661196f,
    0.809969299f,
    0.810276407f,
    0.810582524f,
    0.810887656f,
    0.811191807f,
    0.811494981f,
    0.811797184f,
    0.812098419f,
    0.812398693f,
    0.812698009f,
    0.812996371f,
    0.813293786f,
    0.813590256f,
    0.813885786f,
    0.814180381f,
    0.814474046f,
    0.814766784f,
    0.815058600f,
    0.815349499f,
    0.815639485f,
    0.815928561f,
    0.816216733f,
    0.816504004f,
    0.816790379f,
    0.817075862f,
    0.817360457f,
    0.817644169f,
    0.817927000f,
    0.818208956f,
    0.818490041f,
    0.818770258f,
    0.819049611f,
    0.819328105f,
    0.819605743f,
    0.819882530f,
    0.820158469f,
    0.820433565f,
    0.820707820f,
    0.820981239f,
    0.821253826f,
    0.821525584f,
    0.821796518f,
    0.822066630f,
    0.822335926f,
    0.822604407f,
    0.822872079f,
    0.823138945f,
    0.823405008f,
    0.823670272f,
    0.823934740f,
    0.824198417f,
    0.824461305f,
    0.824723409f,
    0.824984732f,
    0.825245276f,
    0.825505047f,
    0.825764046f,
    0.826022279f,
    0.826279747f,
    0.826536454f,
    0.826792405f,
    0.827047601f,
    0.827302047f,
    0.827555745f,
    0.827808699f,
    0.828060913f,
    0.828312389f,
    0.828563131f,
    0.828813142f,
    0.829062425f,
    0.829310983f,
    0.829558820f,
    0.829805938f,
    0.830052341f,
    0.830298032f,
    0.830543014f,
    0.830787289f,
    0.831030862f,
    0.831273735f,
};



#ifdef MEMO
# molifireの積分値を計算するための関数

import numpy as np
from numba import jit
import math

#y = math.e / a * np.exp( (-1)/(1- np.abs(2*x/b -1)**c))

@jit
def moli(x,a,b,c):
    return math.e / a * np.exp( (-1)/(1- np.abs(2*x/b -1)**c))

           @jit
           def int_moli(c):
           delta_t = 0.000001
                     x = np.arange(0.0,1,delta_t)

                         S = 0
                             y = moli(x,1,1,c)

                                 for i,ele in enumerate(y):
                             if i != 0:
                                     S = S + delta_t* ele
                                         return S


                                                for i in np.arange(0.0, 6.01, 0.01):
                                                        print("{:.9f}".format(int_moli(i))+"f,")

#endif