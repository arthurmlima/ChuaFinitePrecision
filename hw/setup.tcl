puts "First argument: $argv"
set scriptPath [file dirname [info script]]
puts "Present location: $scriptPath"

create_project -force hw $scriptPath
set_property board_part xilinx.com:zcu104:part0:1.1 [current_project]
import_files -fileset constrs_1 -force -norecurse $scriptPath/xdc/zcu104.xdc
set_property  ip_repo_paths $scriptPath/ip_repo [current_project]

create_bd_design "RK4_LBE_1_32"
update_compile_order -fileset sources_1
set_property  ip_repo_paths $scriptPath/ip_repo [current_project]

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e:3.5 zynq_ultra_ps_e_0
endgroup

startgroup
set_property CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {90} [get_bd_cells zynq_ultra_ps_e_0]
endgroup

apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
update_ip_catalog -rebuild


set_property location {0.5 -329 -823} [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma:7.1 axi_dma_0
endgroup
set_property -dict [list \
  CONFIG.c_include_mm2s {0} \
  CONFIG.c_include_s2mm_dre {1} \
  CONFIG.c_include_sg {0} \
  CONFIG.c_sg_length_width {26} \
] [get_bd_cells axi_dma_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:RK4_LBE_1_32:1.0 RK4_LBE_1_32_0
endgroup
startgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins axi_dma_0/S_AXI_LITE]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/RK4_LBE_1_32_0/s_axi_CTRL} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins RK4_LBE_1_32_0/s_axi_CTRL]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/axi_dma_0/M_AXI_S2MM} Slave {/zynq_ultra_ps_e_0/S_AXI_HPC0_FPD} ddr_seg {Auto} intc_ip {New AXI SmartConnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HPC0_FPD]

endgroup
connect_bd_intf_net [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM] [get_bd_intf_pins RK4_LBE_1_32_0/output_stream]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0
endgroup
set_property location {4 986 -1283} [get_bd_cells xlconcat_0]
connect_bd_net [get_bd_pins axi_dma_0/s2mm_introut] [get_bd_pins xlconcat_0/In0]
connect_bd_net [get_bd_pins RK4_LBE_1_32_0/interrupt] [get_bd_pins xlconcat_0/In1]
connect_bd_net [get_bd_pins xlconcat_0/dout] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq0]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Clk_xbar {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Master {/zynq_ultra_ps_e_0/M_AXI_HPM1_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {/ps8_0_axi_periph} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM1_FPD]

startgroup
set_property CONFIG.PSU__USE__M_AXI_GP1 {0} [get_bd_cells zynq_ultra_ps_e_0]
delete_bd_objs [get_bd_intf_nets zynq_ultra_ps_e_0_M_AXI_HPM1_FPD]
endgroup
regenerate_bd_layout
set_property location {2 660 345} [get_bd_cells xlconcat_0]
set_property location {4 1225 420} [get_bd_cells ps8_0_axi_periph]
set_property location {3 913 446} [get_bd_cells ps8_0_axi_periph]
set_property location {4 1440 453} [get_bd_cells RK4_LBE_1_32_0]
set_property location {2 609 452} [get_bd_cells rst_ps8_0_100M]


save_bd_design
close_bd_design [get_bd_designs RK4_LBE_1_32]


create_bd_design "RK4_LBE_2_32"
update_compile_order -fileset sources_1
set_property  ip_repo_paths $scriptPath/ip_repo [current_project]

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e:3.5 zynq_ultra_ps_e_0
endgroup

startgroup
set_property CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {90} [get_bd_cells zynq_ultra_ps_e_0]
endgroup

apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
update_ip_catalog -rebuild


set_property location {0.5 -329 -823} [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma:7.1 axi_dma_0
endgroup
set_property -dict [list \
  CONFIG.c_include_mm2s {0} \
  CONFIG.c_include_s2mm_dre {1} \
  CONFIG.c_include_sg {0} \
  CONFIG.c_sg_length_width {26} \
] [get_bd_cells axi_dma_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:RK4_LBE_2_32:1.0 RK4_LBE_2_32_0
endgroup
startgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins axi_dma_0/S_AXI_LITE]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/RK4_LBE_2_32_0/s_axi_CTRL} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins RK4_LBE_2_32_0/s_axi_CTRL]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/axi_dma_0/M_AXI_S2MM} Slave {/zynq_ultra_ps_e_0/S_AXI_HPC0_FPD} ddr_seg {Auto} intc_ip {New AXI SmartConnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HPC0_FPD]

endgroup
connect_bd_intf_net [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM] [get_bd_intf_pins RK4_LBE_2_32_0/output_stream]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0
endgroup
set_property location {4 986 -1283} [get_bd_cells xlconcat_0]
connect_bd_net [get_bd_pins axi_dma_0/s2mm_introut] [get_bd_pins xlconcat_0/In0]
connect_bd_net [get_bd_pins RK4_LBE_2_32_0/interrupt] [get_bd_pins xlconcat_0/In1]
connect_bd_net [get_bd_pins xlconcat_0/dout] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq0]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Clk_xbar {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Master {/zynq_ultra_ps_e_0/M_AXI_HPM1_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {/ps8_0_axi_periph} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM1_FPD]

startgroup
set_property CONFIG.PSU__USE__M_AXI_GP1 {0} [get_bd_cells zynq_ultra_ps_e_0]
delete_bd_objs [get_bd_intf_nets zynq_ultra_ps_e_0_M_AXI_HPM1_FPD]
endgroup
regenerate_bd_layout
set_property location {2 660 345} [get_bd_cells xlconcat_0]
set_property location {4 1225 420} [get_bd_cells ps8_0_axi_periph]
set_property location {3 913 446} [get_bd_cells ps8_0_axi_periph]
set_property location {4 1440 453} [get_bd_cells RK4_LBE_2_32_0]
set_property location {2 609 452} [get_bd_cells rst_ps8_0_100M]


save_bd_design
close_bd_design [get_bd_designs RK4_LBE_2_32]


create_bd_design "RK4_LBE_B_32"
update_compile_order -fileset sources_1
set_property  ip_repo_paths $scriptPath/ip_repo [current_project]

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e:3.5 zynq_ultra_ps_e_0
endgroup

startgroup
set_property CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {90} [get_bd_cells zynq_ultra_ps_e_0]
endgroup

apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
update_ip_catalog -rebuild


set_property location {0.5 -329 -823} [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma:7.1 axi_dma_0
endgroup
set_property -dict [list \
  CONFIG.c_include_mm2s {0} \
  CONFIG.c_include_s2mm_dre {1} \
  CONFIG.c_include_sg {0} \
  CONFIG.c_sg_length_width {26} \
] [get_bd_cells axi_dma_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:RK4_LBE_B_32:1.0 RK4_LBE_B_32_0
endgroup
startgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins axi_dma_0/S_AXI_LITE]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/RK4_LBE_B_32_0/s_axi_CTRL} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins RK4_LBE_B_32_0/s_axi_CTRL]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/axi_dma_0/M_AXI_S2MM} Slave {/zynq_ultra_ps_e_0/S_AXI_HPC0_FPD} ddr_seg {Auto} intc_ip {New AXI SmartConnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HPC0_FPD]

endgroup
connect_bd_intf_net [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM] [get_bd_intf_pins RK4_LBE_B_32_0/output_stream]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0
endgroup
set_property location {4 986 -1283} [get_bd_cells xlconcat_0]
connect_bd_net [get_bd_pins axi_dma_0/s2mm_introut] [get_bd_pins xlconcat_0/In0]
connect_bd_net [get_bd_pins RK4_LBE_B_32_0/interrupt] [get_bd_pins xlconcat_0/In1]
connect_bd_net [get_bd_pins xlconcat_0/dout] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq0]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Clk_xbar {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Master {/zynq_ultra_ps_e_0/M_AXI_HPM1_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {/ps8_0_axi_periph} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM1_FPD]

startgroup
set_property CONFIG.PSU__USE__M_AXI_GP1 {0} [get_bd_cells zynq_ultra_ps_e_0]
delete_bd_objs [get_bd_intf_nets zynq_ultra_ps_e_0_M_AXI_HPM1_FPD]
endgroup
regenerate_bd_layout
set_property location {2 660 345} [get_bd_cells xlconcat_0]
set_property location {4 1225 420} [get_bd_cells ps8_0_axi_periph]
set_property location {3 913 446} [get_bd_cells ps8_0_axi_periph]
set_property location {4 1440 453} [get_bd_cells RK4_LBE_B_32_0]
set_property location {2 609 452} [get_bd_cells rst_ps8_0_100M]


save_bd_design
close_bd_design [get_bd_designs RK4_LBE_B_32]


create_bd_design "RK4_LBE_1_64"
update_compile_order -fileset sources_1
set_property  ip_repo_paths $scriptPath/ip_repo [current_project]

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e:3.5 zynq_ultra_ps_e_0
endgroup

startgroup
set_property CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {90} [get_bd_cells zynq_ultra_ps_e_0]
endgroup

apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
update_ip_catalog -rebuild


set_property location {0.5 -329 -823} [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma:7.1 axi_dma_0
endgroup
set_property -dict [list \
  CONFIG.c_include_mm2s {0} \
  CONFIG.c_include_s2mm_dre {1} \
  CONFIG.c_include_sg {0} \
  CONFIG.c_sg_length_width {26} \
] [get_bd_cells axi_dma_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:RK4_LBE_1_64:1.0 RK4_LBE_1_64_0
endgroup
startgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins axi_dma_0/S_AXI_LITE]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/RK4_LBE_1_64_0/s_axi_CTRL} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins RK4_LBE_1_64_0/s_axi_CTRL]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/axi_dma_0/M_AXI_S2MM} Slave {/zynq_ultra_ps_e_0/S_AXI_HPC0_FPD} ddr_seg {Auto} intc_ip {New AXI SmartConnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HPC0_FPD]

endgroup
connect_bd_intf_net [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM] [get_bd_intf_pins RK4_LBE_1_64_0/output_stream]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0
endgroup
set_property location {4 986 -1283} [get_bd_cells xlconcat_0]
connect_bd_net [get_bd_pins axi_dma_0/s2mm_introut] [get_bd_pins xlconcat_0/In0]
connect_bd_net [get_bd_pins RK4_LBE_1_64_0/interrupt] [get_bd_pins xlconcat_0/In1]
connect_bd_net [get_bd_pins xlconcat_0/dout] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq0]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Clk_xbar {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Master {/zynq_ultra_ps_e_0/M_AXI_HPM1_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {/ps8_0_axi_periph} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM1_FPD]

startgroup
set_property CONFIG.PSU__USE__M_AXI_GP1 {0} [get_bd_cells zynq_ultra_ps_e_0]
delete_bd_objs [get_bd_intf_nets zynq_ultra_ps_e_0_M_AXI_HPM1_FPD]
endgroup
regenerate_bd_layout
set_property location {2 660 345} [get_bd_cells xlconcat_0]
set_property location {4 1225 420} [get_bd_cells ps8_0_axi_periph]
set_property location {3 913 446} [get_bd_cells ps8_0_axi_periph]
set_property location {4 1440 453} [get_bd_cells RK4_LBE_1_64_0]
set_property location {2 609 452} [get_bd_cells rst_ps8_0_100M]


save_bd_design
close_bd_design [get_bd_designs RK4_LBE_1_64]


create_bd_design "RK4_LBE_2_64"
update_compile_order -fileset sources_1
set_property  ip_repo_paths $scriptPath/ip_repo [current_project]

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e:3.5 zynq_ultra_ps_e_0
endgroup

startgroup
set_property CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {90} [get_bd_cells zynq_ultra_ps_e_0]
endgroup

apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
update_ip_catalog -rebuild


set_property location {0.5 -329 -823} [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma:7.1 axi_dma_0
endgroup
set_property -dict [list \
  CONFIG.c_include_mm2s {0} \
  CONFIG.c_include_s2mm_dre {1} \
  CONFIG.c_include_sg {0} \
  CONFIG.c_sg_length_width {26} \
] [get_bd_cells axi_dma_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:RK4_LBE_2_64:1.0 RK4_LBE_2_64_0
endgroup
startgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins axi_dma_0/S_AXI_LITE]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/RK4_LBE_2_64_0/s_axi_CTRL} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins RK4_LBE_2_64_0/s_axi_CTRL]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/axi_dma_0/M_AXI_S2MM} Slave {/zynq_ultra_ps_e_0/S_AXI_HPC0_FPD} ddr_seg {Auto} intc_ip {New AXI SmartConnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HPC0_FPD]

endgroup
connect_bd_intf_net [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM] [get_bd_intf_pins RK4_LBE_2_64_0/output_stream]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0
endgroup
set_property location {4 986 -1283} [get_bd_cells xlconcat_0]
connect_bd_net [get_bd_pins axi_dma_0/s2mm_introut] [get_bd_pins xlconcat_0/In0]
connect_bd_net [get_bd_pins RK4_LBE_2_64_0/interrupt] [get_bd_pins xlconcat_0/In1]
connect_bd_net [get_bd_pins xlconcat_0/dout] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq0]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Clk_xbar {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Master {/zynq_ultra_ps_e_0/M_AXI_HPM1_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {/ps8_0_axi_periph} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM1_FPD]

startgroup
set_property CONFIG.PSU__USE__M_AXI_GP1 {0} [get_bd_cells zynq_ultra_ps_e_0]
delete_bd_objs [get_bd_intf_nets zynq_ultra_ps_e_0_M_AXI_HPM1_FPD]
endgroup
regenerate_bd_layout
set_property location {2 660 345} [get_bd_cells xlconcat_0]
set_property location {4 1225 420} [get_bd_cells ps8_0_axi_periph]
set_property location {3 913 446} [get_bd_cells ps8_0_axi_periph]
set_property location {4 1440 453} [get_bd_cells RK4_LBE_2_64_0]
set_property location {2 609 452} [get_bd_cells rst_ps8_0_100M]


save_bd_design
close_bd_design [get_bd_designs RK4_LBE_2_64]


create_bd_design "RK4_LBE_B_64"
update_compile_order -fileset sources_1
set_property  ip_repo_paths $scriptPath/ip_repo [current_project]

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e:3.5 zynq_ultra_ps_e_0
endgroup

startgroup
set_property CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {90} [get_bd_cells zynq_ultra_ps_e_0]
endgroup

apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
update_ip_catalog -rebuild


set_property location {0.5 -329 -823} [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma:7.1 axi_dma_0
endgroup
set_property -dict [list \
  CONFIG.c_include_mm2s {0} \
  CONFIG.c_include_s2mm_dre {1} \
  CONFIG.c_include_sg {0} \
  CONFIG.c_sg_length_width {26} \
] [get_bd_cells axi_dma_0]
set_property CONFIG.PSU__USE__S_AXI_GP0 {1} [get_bd_cells zynq_ultra_ps_e_0]
apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:RK4_LBE_B_64:1.0 RK4_LBE_B_64_0
endgroup
startgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins axi_dma_0/S_AXI_LITE]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/RK4_LBE_B_64_0/s_axi_CTRL} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins RK4_LBE_B_64_0/s_axi_CTRL]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/axi_dma_0/M_AXI_S2MM} Slave {/zynq_ultra_ps_e_0/S_AXI_HPC0_FPD} ddr_seg {Auto} intc_ip {New AXI SmartConnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HPC0_FPD]

endgroup
connect_bd_intf_net [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM] [get_bd_intf_pins RK4_LBE_B_64_0/output_stream]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0
endgroup
set_property location {4 986 -1283} [get_bd_cells xlconcat_0]
connect_bd_net [get_bd_pins axi_dma_0/s2mm_introut] [get_bd_pins xlconcat_0/In0]
connect_bd_net [get_bd_pins RK4_LBE_B_64_0/interrupt] [get_bd_pins xlconcat_0/In1]
connect_bd_net [get_bd_pins xlconcat_0/dout] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq0]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Clk_xbar {/zynq_ultra_ps_e_0/pl_clk0 (100 MHz)} Master {/zynq_ultra_ps_e_0/M_AXI_HPM1_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {/ps8_0_axi_periph} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM1_FPD]

startgroup
set_property CONFIG.PSU__USE__M_AXI_GP1 {0} [get_bd_cells zynq_ultra_ps_e_0]
delete_bd_objs [get_bd_intf_nets zynq_ultra_ps_e_0_M_AXI_HPM1_FPD]
endgroup
regenerate_bd_layout
set_property location {2 660 345} [get_bd_cells xlconcat_0]
set_property location {4 1225 420} [get_bd_cells ps8_0_axi_periph]
set_property location {3 913 446} [get_bd_cells ps8_0_axi_periph]
set_property location {4 1440 453} [get_bd_cells RK4_LBE_B_64_0]
set_property location {2 609 452} [get_bd_cells rst_ps8_0_100M]


save_bd_design
close_bd_design [get_bd_designs RK4_LBE_B_64]



update_compile_order -fileset sources_1
make_wrapper -files [get_files $scriptPath/hw.srcs/sources_1/bd/RK4_LBE_1_64/RK4_LBE_1_64.bd] -top
add_files -norecurse $scriptPath/hw.gen/sources_1/bd/RK4_LBE_1_64/hdl/RK4_LBE_1_64_wrapper.v

update_compile_order -fileset sources_1
make_wrapper -files [get_files $scriptPath/hw.srcs/sources_1/bd/RK4_LBE_2_64/RK4_LBE_2_64.bd] -top
add_files -norecurse $scriptPath/hw.gen/sources_1/bd/RK4_LBE_2_64/hdl/RK4_LBE_2_64_wrapper.v

update_compile_order -fileset sources_1
make_wrapper -files [get_files $scriptPath/hw.srcs/sources_1/bd/RK4_LBE_B_64/RK4_LBE_B_64.bd] -top
add_files -norecurse $scriptPath/hw.gen/sources_1/bd/RK4_LBE_B_64/hdl/RK4_LBE_B_64_wrapper.v


update_compile_order -fileset sources_1
make_wrapper -files [get_files $scriptPath/hw.srcs/sources_1/bd/RK4_LBE_1_32/RK4_LBE_1_32.bd] -top
add_files -norecurse $scriptPath/hw.gen/sources_1/bd/RK4_LBE_1_32/hdl/RK4_LBE_1_32_wrapper.v
update_compile_order -fileset sources_1

update_compile_order -fileset sources_1
make_wrapper -files [get_files $scriptPath/hw.srcs/sources_1/bd/RK4_LBE_2_32/RK4_LBE_2_32.bd] -top
add_files -norecurse $scriptPath/hw.gen/sources_1/bd/RK4_LBE_2_32/hdl/RK4_LBE_2_32_wrapper.v
update_compile_order -fileset sources_1


update_compile_order -fileset sources_1
make_wrapper -files [get_files $scriptPath/hw.srcs/sources_1/bd/RK4_LBE_B_32/RK4_LBE_B_32.bd] -top
add_files -norecurse $scriptPath/hw.gen/sources_1/bd/RK4_LBE_B_32/hdl/RK4_LBE_B_32_wrapper.v
update_compile_order -fileset sources_1


create_run synth_1_32 -flow {Vivado Synthesis 2023}
create_run impl_1_32 -parent_run synth_1_32 -flow {Vivado Implementation 2023}

create_run synth_2_32 -flow {Vivado Synthesis 2023}
create_run impl_2_32 -parent_run synth_2_32 -flow {Vivado Implementation 2023}

create_run synth_B_32 -flow {Vivado Synthesis 2023}
create_run impl_B_32 -parent_run synth_B_32 -flow {Vivado Implementation 2023}

create_run synth_1_64 -flow {Vivado Synthesis 2023}
create_run impl_1_64 -parent_run synth_1_64 -flow {Vivado Implementation 2023}

create_run synth_2_64 -flow {Vivado Synthesis 2023}
create_run impl_2_64 -parent_run synth_2_64 -flow {Vivado Implementation 2023}


create_run synth_B_64 -flow {Vivado Synthesis 2023}
create_run impl_B_64 -parent_run synth_B_64 -flow {Vivado Implementation 2023}


set_property top RK4_LBE_1_32_wrapper [current_fileset]
update_compile_order -fileset sources_1
launch_runs impl_1_32 -to_step write_bitstream -jobs 6
wait_on_run impl_1_32


set_property top RK4_LBE_2_32_wrapper [current_fileset]
update_compile_order -fileset sources_1
launch_runs impl_2_32 -to_step write_bitstream -jobs 6
wait_on_run impl_2_32

set_property top RK4_LBE_B_32_wrapper [current_fileset]
update_compile_order -fileset sources_1
launch_runs impl_B_32 -to_step write_bitstream -jobs 6
wait_on_run impl_B_32

set_property top RK4_LBE_1_64_wrapper [current_fileset]
update_compile_order -fileset sources_1
launch_runs impl_1_64 -to_step write_bitstream -jobs 6
wait_on_run impl_1_64

set_property top RK4_LBE_2_64_wrapper [current_fileset]
update_compile_order -fileset sources_1
launch_runs impl_2_64 -to_step write_bitstream -jobs 6
wait_on_run impl_2_64

set_property top RK4_LBE_B_64_wrapper [current_fileset]
update_compile_order -fileset sources_1
launch_runs impl_B_64 -to_step write_bitstream -jobs 6
wait_on_run impl_B_64
