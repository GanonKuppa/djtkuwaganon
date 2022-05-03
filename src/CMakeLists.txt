cmake_minimum_required(VERSION 3.14)

message(STATUS  "======== djtkuwaganon building mot file ========")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_SYSTEM_NAME Generic)

# tool chain
set(CMAKE_C_COMPILER   rx-elf-gcc)
set(CMAKE_ASM_COMPILER rx-elf-gcc)
set(CMAKE_CXX_COMPILER rx-elf-g++)
set(CMAKE_EXE_LINKER   rx-elf-g++)
set(OBJCOPY            rx-elf-objcopy)
set(SIZE               rx-elf-size)

# project
project(djtkuwaganon)

set(ELF_FILE ${PROJECT_NAME}.elf)
set(MOT_FILE ${PROJECT_NAME}.mot)
set(MAP_FILE ${PROJECT_NAME}.map)

# mpu
set(LDSCRIPT  ${PROJECT_SOURCE_DIR}/generate/linker_script.ld)

# compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-fdiagnostics-color")
add_compile_options(-O2)
add_compile_options(-ffunction-sections)
add_compile_options(-fdata-sections)
add_compile_options(-fdiagnostics-parseable-fixits)
add_compile_options(-Wstack-usage=4000)
add_compile_options(-g2)
add_compile_options(-m64bit-doubles)
add_compile_options(-mcpu=rx71m)
add_compile_options(-misa=v2)
add_compile_options(-mlittle-endian-data)

set(CMAKE_AS_FLAGS "-Wa,--gdwarf2 -x assembler-with-cpp")

add_link_options(-O2)
add_link_options(-ffunction-sections)
add_link_options(-fdata-sections)
add_link_options(-fdiagnostics-parseable-fixits)
add_link_options(-Wstack-usage=4000)
add_link_options(-g2)
add_link_options(-m64bit-doubles)
add_link_options(-mcpu=rx71m)
add_link_options(-misa=v2)
add_link_options(-mlittle-endian-data)

set(CMAKE_EXE_LINKER_FLAGS "-T ${PROJECT_SOURCE_DIR}/generate/linker_script.ld -Wl,--start-group -lm -lc -lgcc -lstdc++ -Wl,--end-group -nostartfiles -Wl,-e_PowerON_Reset -Wl,-M=${MAP_FILE} ")

enable_language(ASM)

# define
add_definitions(-DCPPAPP)

# includes
set(GENERATE_DIR_H ${PROJECT_SOURCE_DIR}/generate)
set(SRC_DIR_H ${PROJECT_SOURCE_DIR})
set(APP_ACTIVITY_H ${PROJECT_SOURCE_DIR}/ApplicationLayer/Activity)
set(APP_LIB_H ${PROJECT_SOURCE_DIR}/ApplicationLayer/Lib)
set(APP_MESSAGE_H ${PROJECT_SOURCE_DIR}/ApplicationLayer/Message/)
set(APP_MODULE_H ${PROJECT_SOURCE_DIR}/ApplicationLayer/Module)
set(APP_OBJECT_H ${PROJECT_SOURCE_DIR}/ApplicationLayer/Object)
set(HAL_H ${PROJECT_SOURCE_DIR}/HardwareAbstractionLayer)
set(PD_H ${PROJECT_SOURCE_DIR}/PeripheralDriverLayer)

set(EIGEN_DIR_H ${PROJECT_SOURCE_DIR}/ApplicationLayer/Lib/Eigen)
set(NTSHELL_CORE_DIR_H ${PROJECT_SOURCE_DIR}/ApplicationLayer/Lib/ntshell/core)
set(NTSHELL_UTIL_DIR_H ${PROJECT_SOURCE_DIR}/ApplicationLayer/Lib/ntshell/util)
set(PATH_CALCULATION_DIR_H ${PROJECT_SOURCE_DIR}/ApplicationLayer/Lib/PathCalculation)

include_directories(
    ${GENERATE_DIR_H}
    ${SRC_DIR_H}
    ${APP_ACTIVITY_H}
    ${APP_LIB_H}
    ${APP_MESSAGE_H}
    ${APP_MODULE_H}
    ${APP_OBJECT_H}
    ${HAL_H}    
    ${EIGEN_DIR_H}
    ${NTSHELL_CORE_DIR_H}
    ${NTSHELL_UTIL_DIR_H}
    ${PATH_CALCULATION_DIR_H}
)


# sources
file(GLOB_RECURSE GENERATE_C ${PROJECT_SOURCE_DIR}/generate/*.c)
file(GLOB_RECURSE GENERATE_CPP ${PROJECT_SOURCE_DIR}/generate/*.cpp)
file(GLOB_RECURSE APP_CPP ${PROJECT_SOURCE_DIR}/ApplicationLayer/*.cpp)
file(GLOB_RECURSE APP_C ${PROJECT_SOURCE_DIR}/ApplicationLayer/*.c)
file(GLOB_RECURSE HAL_CPP ${PROJECT_SOURCE_DIR}/HardwareAbstractionLayer/*.cpp)
file(GLOB_RECURSE HAL_C ${PROJECT_SOURCE_DIR}/HardwareAbstractionLayer/*.c)
file(GLOB_RECURSE PD_CPP ${PROJECT_SOURCE_DIR}/PeripheralDriverLayer/*.cpp)
file(GLOB_RECURSE PATH_CALCULATION_CPP ${PROJECT_SOURCE_DIR}/ApplicationLayer/Lib/PathCalculation/*.cpp)


# executables
add_executable(${ELF_FILE} 
    ${GENERATE_C}
    ${GENERATE_CPP}
    ${PROJECT_SOURCE_DIR}/generate/start.S
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/oneshotTask.cpp
    ${APP_CPP}
    ${APP_C}
    ${HAL_CPP}
    ${HAL_C}
    ${PD_CPP}
)

add_custom_command(TARGET ${ELF_FILE} POST_BUILD
    COMMAND ${OBJCOPY} -O srec -I elf32-rx-be-ns  ${ELF_FILE} ${MOT_FILE}
    COMMAND ${SIZE} --format=berkeley ${ELF_FILE}    
)

