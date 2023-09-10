# set env(BOARD) zcu104/zed
proc runWookie { designName } {
    global scriptPath  ;# <-- Access the global variable
    global board  ;# Declare the variable as global

    if {$board eq "zcu104"} {
        # Replace with actual command/actions for "boardx"
        create_bd_design $designName
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
        create_bd_cell -type ip -vlnv xilinx.com:hls:$designName:1.0 ${designName}
        endgroup
        startgroup
        apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins axi_dma_0/S_AXI_LITE]
        apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/${designName}/s_axi_CTRL} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins ${designName}/s_axi_CTRL]
        apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/axi_dma_0/M_AXI_S2MM} Slave {/zynq_ultra_ps_e_0/S_AXI_HPC0_FPD} ddr_seg {Auto} intc_ip {New AXI SmartConnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HPC0_FPD]

        endgroup
        connect_bd_intf_net [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM] [get_bd_intf_pins ${designName}/output_stream]
        startgroup
        create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0
        endgroup
        set_property location {4 986 -1283} [get_bd_cells xlconcat_0]
        connect_bd_net [get_bd_pins axi_dma_0/s2mm_introut] [get_bd_pins xlconcat_0/In0]
        connect_bd_net [get_bd_pins ${designName}/interrupt] [get_bd_pins xlconcat_0/In1]
        connect_bd_net [get_bd_pins xlconcat_0/dout] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq0]
        apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {/zynq_ultra_ps_e_0/pl_clk0 (90 MHz)} Clk_xbar {/zynq_ultra_ps_e_0/pl_clk0 (90 MHz)} Master {/zynq_ultra_ps_e_0/M_AXI_HPM1_FPD} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {/ps8_0_axi_periph} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM1_FPD]

        startgroup
        set_property CONFIG.PSU__USE__M_AXI_GP1 {0} [get_bd_cells zynq_ultra_ps_e_0]
        delete_bd_objs [get_bd_intf_nets zynq_ultra_ps_e_0_M_AXI_HPM1_FPD]
        endgroup
        regenerate_bd_layout

        save_bd_design
        close_bd_design [get_bd_designs $designName]

        update_compile_order -fileset sources_1

        puts "Selected zcu104"
    } elseif {$board eq "zed"} {


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

        # Replace with actual command/actions for "boardy"
        puts "Selected zed"
    } else {
        puts "Unsupported board: $board"
    }
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

    open_run impl_${designName}

    if {![file exists "${scriptPath}/reports"]} {
        file mkdir "${scriptPath}/reports"
    }
    report_utilization -file "${scriptPath}/reports/utilization_${designName}.rpt"
    report_power -file "${scriptPath}/reports/power_${designName}.rpt"
    report_timing_summary -file "${scriptPath}/reports/timing_${designName}.rpt"

    close_design
}

puts "First argument: $argv"
set scriptPath [file dirname [info script]]
puts "Present location: $scriptPath"

global board
# Check if BOARD environment variable exists, otherwise default to "none"
set board [expr {[info exists ::env(BOARD)] ? $::env(BOARD) : "none"}]
puts "Selected board: $board"


create_project -force hw $scriptPath
if {$board eq "zcu104"} {
    set_property board_part xilinx.com:zcu104:part0:1.1 [current_project]
    import_files -fileset constrs_1 -force -norecurse $scriptPath/xdc/zcu104.xdc

    puts "Selected zcu104"
} elseif {$board eq "zed"} {
    set_property board_part digilentinc.com:zedboard:part0:1.1 [current_project]
    import_files -fileset constrs_1 -force -norecurse $scriptPath/xdc/zed.xdc
    puts "Selected zed"
} else {
    puts "Unsupported board: $board"
}
set_property ip_repo_paths $scriptPath/ip_repo [current_project]

runWookie "CCE_1_32"
runWookie "CCE_2_32"
runWookie "CCE_B_32"
runWookie "CCE_1_64"
runWookie "CCE_2_64"
runWookie "CCE_B_64"