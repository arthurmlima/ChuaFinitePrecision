

puts "First argument: $argv"
set scriptPath [file dirname [info script]]
puts "Present location: $scriptPath"


create_project -force hw $scriptPath -part xc7z020clg484-1
set_property board_part digilentinc.com:zedboard:part0:1.1 [current_project]
import_files -fileset constrs_1 -force -norecurse $scriptPath/xdc/zed.xdc
set_property ip_repo_paths $scriptPath/ip_repo [current_project]





# Function to create a common block design
proc runWookie { designName } {
    global scriptPath  ;# <-- Access the global variable

create_bd_design $designName
update_compile_order -fileset sources_1
set_property  ip_repo_paths $scriptPath/ip_repo [current_project]
update_compile_order -fileset sources_1

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 processing_system7_0
endgroup
set_property -dict [list \
  CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ {90} \
  CONFIG.PCW_USE_S_AXI_GP0 {1} \
] [get_bd_cells processing_system7_0]
apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 -config {make_external "FIXED_IO, DDR" apply_board_preset "1" Master "Disable" Slave "Disable" }  [get_bd_cells processing_system7_0]
startgroup
set_property CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ {90} [get_bd_cells processing_system7_0]
endgroup

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma:7.1 axi_dma_0
endgroup
set_property -dict [list \
  CONFIG.c_include_mm2s {0} \
  CONFIG.c_include_s2mm_dre {1} \
  CONFIG.c_include_sg {0} \
  CONFIG.c_sg_length_width {26} \
] [get_bd_cells axi_dma_0]


startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:$designName:1.0 ${designName}
endgroup

startgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/processing_system7_0/M_AXI_GP0} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins axi_dma_0/S_AXI_LITE]

apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {/processing_system7_0/FCLK_CLK0} Clk_slave {Auto} Clk_xbar {/processing_system7_0/FCLK_CLK0} Master {/processing_system7_0/M_AXI_GP0} Slave {/${designName}/s_axi_CTRL} ddr_seg {Auto} intc_ip {/ps7_0_axi_periph} master_apm {0}}  [get_bd_intf_pins ${designName}/s_axi_CTRL]

apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/axi_dma_0/M_AXI_S2MM} Slave {/processing_system7_0/S_AXI_GP0} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins processing_system7_0/S_AXI_GP0]


endgroup
connect_bd_intf_net [get_bd_intf_pins ${designName}/output_stream] [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM]




save_bd_design
close_bd_design [get_bd_designs $designName]
update_compile_order -fileset sources_1
make_wrapper -files [get_files ${scriptPath}/hw.srcs/sources_1/bd/${designName}/${designName}.bd] -top
add_files -norecurse ${scriptPath}/hw.gen/sources_1/bd/${designName}/hdl/${designName}_wrapper.v
update_compile_order -fileset sources_1
create_run synth_${designName} -flow {Vivado Synthesis 2023}
create_run impl_${designName} -parent_run synth_${designName} -flow {Vivado Implementation 2023}
update_compile_order -fileset sources_1
set_property top ${designName}_wrapper [current_fileset]
update_compile_order -fileset sources_1
launch_runs impl_${designName} -to_step write_bitstream -jobs 6
wait_on_run impl_${designName}



}

runWookie "CCE_1_32"
runWookie "CCE_2_32"
runWookie "CCE_B_32"
runWookie "CCE_1_64"
runWookie "CCE_2_64"
runWookie "CCE_B_64"

