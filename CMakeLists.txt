# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(cz C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()


# Add executable. Default name is the project name, version 0.1
add_executable(cz)
target_sources(cz PRIVATE 
                main.cpp 
                utils.cpp
                ui.cpp
                drivers/audio_dac.cpp
                drivers/adc_input.cpp
                drivers/gpio_irq_handler.cpp
                drivers/encoder.cpp
                dsp/synth.cpp
                dsp/phase_distorter.cpp
                dsp/phase_distortion/default.cpp
                dsp/phase_distortion/pd_algo.cpp
                dsp/phase_distortion/kink.cpp
                dsp/phase_distortion/sync.cpp
                dsp/phase_distortion/reverse.cpp
                dsp/phase_distortion/double_kink.cpp
                dsp/phase_distortion/sync_high.cpp
                dsp/phase_distortion/bitcrush.cpp
                dsp/phase_distortion/bitfade.cpp
              )

pico_set_program_name(cz "cz")
pico_set_program_version(cz "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(cz 0)
pico_enable_stdio_usb(cz 1)

# Add the standard library to the build
target_link_libraries(cz
        pico_stdlib
        pico_multicore
        hardware_dma
        hardware_clocks
        hardware_pio
        hardware_interp
        hardware_adc
        )

# Add the standard include files to the build
target_include_directories(cz PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(cz)

