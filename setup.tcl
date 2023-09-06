# Copyright (C) 2019-2022, Xilinx, Inc.
# Copyright (C) 2022-2023, Advanced Micro Devices, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# vitis hls makefile-generator v2.0.0

puts "First argument: $argv"
set scriptPath [file dirname [info script]]
puts "Present location: $scriptPath"
cd $scriptPath
set PROJ "ChuaFinitePrecision"
exec mkdir -p ../hw/ip_repo/
exec rm -R ../hw/ip_repo/
exec mkdir -p ../hw/ip_repo/
open_project -reset $PROJ

add_files "codes/Header.h" 
add_files "codes/topfunc.cpp"
add_files -tb "codes/test_core.cpp" 


set_top RK4_LBE

open_solution -reset "solution1" -flow_target vivado
set_part {xczu7ev-ffvc1156-2-e}
create_clock -period 11 -name default

csim_design -argv {11}
csynth_design
export_design -rtl verilog -format ip_catalog -output ../hw/ip_repo/
exec unzip ../hw/ip_repo/export.zip -d ../hw/ip_repo/
exec rm -R ../hw/ip_repo/export.zip
exit