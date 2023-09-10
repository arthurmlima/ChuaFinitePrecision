puts "First argument: $argv"
set scriptPath [file dirname [info script]]
puts "Present location: $scriptPath"

create_project -force hw $scriptPath
set_property board_part xilinx.com:zcu104:part0:1.1 [current_project]
import_files -fileset constrs_1 -force -norecurse $scriptPath/xdc/zcu104.xdc
set_property  ip_repo_paths $scriptPath/ip_repo [current_project]


