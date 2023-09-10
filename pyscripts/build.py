import os
import subprocess

def functiontoruncommands(command):
    # Path to the batch file
    batch_file = r"C:\Xilinx\Vitis_HLS\2023.1\bin\vitis_hls_cmd.bat"
    
    # Create a combined command: batch file + '&&' + your command
    full_command = f'cmd.exe /c "{batch_file} && {command}"'
    print
    # Execute the command
    result = subprocess.run(full_command, capture_output=True, text=True, shell=True)
    
    # Print output (you can also return it if you like)
    print(result.stdout)
    print(result.stderr)

# Example of usage
functiontoruncommands('vitis_hls -version')  # Replace with your desired command


# Path to the original Vitis HLS batch file
vitis_hls_batch_path = r"C:\Xilinx\Vitis_HLS\2023.1\bin\vitis_hls.bat"  # Replace with your batch file name

# Create content for the new batch file
batch_content = f"""
@echo off
setlocal enabledelayedexpansion
rem #
rem # COPYRIGHT NOTICE
rem # Copyright 1986-2022 Xilinx, Inc. All Rights Reserved. 
rem # Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved. 
rem # 
set MY_ROOT_DIR=%~dp0

set PATH=%MY_ROOT_DIR%;%MY_ROOT_DIR%..\tps\win64\msys64\usr\bin;%PATH%
set PATH=%MY_ROOT_DIR%;%MY_ROOT_DIR%..\tps\win64\msys64\mingw64\bin;%PATH%

rem # Setup default environmental variables
call "%MY_ROOT_DIR%setupEnv.bat"

rem # Use vbs launcher for GUI to avoid command shell
set RDI_VBSLAUNCH=
if [%1] == [] (
 set RDI_VBSLAUNCH=%~dp0vitis_hls_gui.vbs
)

set RDI_USE_JDK11=True
set RDI_PROG=%~n0
set HLS_ORIG_ARGS=%*
rem # Setup HLS variables
call "%~dp0hlsArgs.bat " %*

rem # Launch the loader
set HLS_TMP_CMD=call "%RDI_BINROOT%/loader.bat" -exec %RDI_PROG% %ALL_HLS_ARGS%
if [%HLS_TERSE_OUTPUT%]==[1] (
   if [%HLS_LOG_FILTERS%]==[] set HLS_LOG_FILTERS=INFO: [HLS 200-1510];INFO: [HLS 200-111];INFO: [Common 17-206];Sourcing Tcl script;ERROR:
   if [%HLS_START_FILTERS%]==[] set HLS_START_FILTERS=** Copyright
   if [%HLS_NEEDLOG%]==[1] (
      %HLS_INTERPRETER% /c %HLS_TMP_CMD% 2>&1 | "%RDI_BINROOT%/loader.bat" -exec hls_tee -start ";!HLS_START_FILTERS!;" -filter ";!HLS_LOG_FILTERS!;" -log !HLS_LOG! 
   ) else (
      %HLS_INTERPRETER% /c %HLS_TMP_CMD% 2>&1 | "%RDI_BINROOT%/loader.bat" -exec hls_tee -start ";!HLS_START_FILTERS!;" -filter ";!HLS_LOG_FILTERS!;"
   )
) else if [%HLS_NEEDLOG%]==[1] (
   %HLS_INTERPRETER% /c %HLS_TMP_CMD% 2>&1 | tee.exe %HLS_LOG%
) else (
   %HLS_INTERPRETER% /c %HLS_TMP_CMD%
)

endlocal

rem exit /b %errorlevel%

"""

# Save the new batch file content to a file
new_batch_filename = "run_vitis_hls.bat"
with open(new_batch_filename, 'w') as f:
    f.write(batch_content)

# Create a temporary Tcl script
tcl_script_content = """
# Set a local Tcl variable from an environment variable
set BOARD zed
# Print the variable
puts $board
# Add any other Tcl commands you wish to run in Vitis HLS here
"""

# Save the Tcl commands to a temporary file
with open('temp_script.tcl', 'w') as f:
    f.write(tcl_script_content)

# Execute the new batch file
subprocess.run([new_batch_filename])
