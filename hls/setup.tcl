#set BOARD=zcu104/zed

proc replaceTextInMultipleFiles {filenames searchStrList replaceStr} {
    foreach filename $filenames {
        # Check if the file exists
        if { ![file exists $filename] } {
            puts "Error: The file $filename does not exist."
            continue;  ;# Skip to the next filename
        }

        # Read the contents of the file
        set fd [open $filename r]
        set content [read $fd]
        close $fd

        # Loop through each search string in the list and replace it
        foreach searchStr $searchStrList {
            set content [string map [list $searchStr $replaceStr] $content]
        }

        # Write the updated content back to the file
        set fd [open $filename w]
        puts $fd $content
        close $fd

        puts "Processed file: $filename"
    }
}

proc setDefinitionsInMultipleFiles {filenames binaryTuple} {
    foreach filename $filenames {
        # Ensure that the file exists
        if { ![file exists $filename] } {
            puts "Error: The file $filename does not exist."
            continue;  ;# Skip to the next filename
        }

        # Read the file contents
        set fd [open $filename r]
        set content [read $fd]
        close $fd

        # List of definitions
        set definitions [list "USE_FLOAT" "ORBIT_1_ONLY" "ORBIT_2_ONLY" "BOTH_ORBITS"]

        # First, reset all definitions to an uncommented state by removing all comment slashes
        foreach def $definitions {
            while {[string first "//#define $def" $content] >= 0} {
                set content [string map [list "//#define $def" "#define $def"] $content]
            }
        }

        # Then apply the binary tuple to comment or uncomment as needed
        foreach bit $binaryTuple def $definitions {
            if {!$bit} {
                # Comment the definition (add leading //)
                set content [string map [list "#define $def" "//#define $def"] $content]
            }
        }

        # Write back the modified content
        set fd [open $filename w]
        puts $fd $content
        close $fd

        puts "Processed file: $filename"
    }
}


proc runWorkflow {binaryTuple replaceValue} {
    global board  ;# Declare the variable as global

    # Constants
    set filelist [list "codes/topfunc.cpp" "codes/Header.h" "codes/test_core.cpp"]
    set searchForList [list "CCE_1_64" "CCE_2_64" "CCE_B_64" "CCE_1_32" "CCE_2_32" "CCE_B_32"]

    # Use the provided arguments
    set binaryConfig $binaryTuple
    set replaceWith $replaceValue

    replaceTextInMultipleFiles $filelist $searchForList $replaceWith
    setDefinitionsInMultipleFiles $filelist $binaryConfig

    set_top $replaceWith

    open_solution -reset "solution1" -flow_target vivado
    switch -- $board {
    "zcu104" {
        set_part {xczu7ev-ffvc1156-2-e}
    }
    "zed" {
        set_part {xc7z020clg484-1}
    }
    default {
        puts "Error: Unknown board $board"
        exit 1
    }
}
    create_clock -period 11 -name default

    csynth_design
    export_design -rtl verilog -format ip_catalog -output ../hw/ip_repo/
    exec mv ../hw/ip_repo/export.zip ../hw/ip_repo/$replaceWith.zip
    exec unzip ../hw/ip_repo/$replaceWith.zip -d ../hw/ip_repo/$replaceWith

    unset binaryConfig
    unset replaceWith
}

global board
set board [expr {[info exists ::env(BOARD)] ? $::env(BOARD) : "none"}]
puts "Selected board: $board"



puts "First argument: $argv"
set scriptPath [file dirname [info script]]
puts "Present location: $scriptPath"
cd $scriptPath
set PROJ "CFP"
exec mkdir -p ../hw/ip_repo/
exec rm -R ../hw/ip_repo/
exec mkdir -p ../hw/ip_repo/
open_project -reset $PROJ

add_files "codes/Header.h" 
add_files "codes/topfunc.cpp"
add_files -tb "codes/test_core.cpp" 

runWorkflow {1 1 0 0} "CCE_1_32"
runWorkflow {1 0 1 0} "CCE_2_32"
runWorkflow {1 0 0 1} "CCE_B_32"
runWorkflow {0 1 0 0} "CCE_1_64"
runWorkflow {0 0 1 0} "CCE_2_64"
runWorkflow {0 0 0 1} "CCE_B_64"

exit