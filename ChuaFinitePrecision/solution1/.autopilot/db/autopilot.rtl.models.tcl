set SynModuleInfo {
  {SRCNAME RK4_LBE MODELNAME RK4_LBE RTLNAME RK4_LBE IS_TOP 1
    SUBMODULES {
      {MODELNAME RK4_LBE_faddfsub_32ns_32ns_32_4_full_dsp_1 RTLNAME RK4_LBE_faddfsub_32ns_32ns_32_4_full_dsp_1 BINDTYPE op TYPE fsub IMPL fulldsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME RK4_LBE_fsub_32ns_32ns_32_4_full_dsp_1 RTLNAME RK4_LBE_fsub_32ns_32ns_32_4_full_dsp_1 BINDTYPE op TYPE fsub IMPL fulldsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME RK4_LBE_fmul_32ns_32ns_32_3_max_dsp_1 RTLNAME RK4_LBE_fmul_32ns_32ns_32_3_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME RK4_LBE_fdiv_32ns_32ns_32_9_no_dsp_1 RTLNAME RK4_LBE_fdiv_32ns_32ns_32_9_no_dsp_1 BINDTYPE op TYPE fdiv IMPL fabric LATENCY 8 ALLOW_PRAGMA 1}
      {MODELNAME RK4_LBE_fptrunc_64ns_32_2_no_dsp_1 RTLNAME RK4_LBE_fptrunc_64ns_32_2_no_dsp_1 BINDTYPE op TYPE fptrunc IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME RK4_LBE_fpext_32ns_64_2_no_dsp_1 RTLNAME RK4_LBE_fpext_32ns_64_2_no_dsp_1 BINDTYPE op TYPE fpext IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME RK4_LBE_fcmp_32ns_32ns_1_2_no_dsp_1 RTLNAME RK4_LBE_fcmp_32ns_32ns_1_2_no_dsp_1 BINDTYPE op TYPE fcmp IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME RK4_LBE_flog_32ns_32ns_32_9_full_dsp_1 RTLNAME RK4_LBE_flog_32ns_32ns_32_9_full_dsp_1 BINDTYPE op TYPE flog IMPL fulldsp LATENCY 8 ALLOW_PRAGMA 1}
      {MODELNAME RK4_LBE_dadd_64ns_64ns_64_5_full_dsp_1 RTLNAME RK4_LBE_dadd_64ns_64ns_64_5_full_dsp_1 BINDTYPE op TYPE dadd IMPL fulldsp LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME RK4_LBE_dmul_64ns_64ns_64_5_max_dsp_1 RTLNAME RK4_LBE_dmul_64ns_64ns_64_5_max_dsp_1 BINDTYPE op TYPE dmul IMPL maxdsp LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME RK4_LBE_CTRL_s_axi RTLNAME RK4_LBE_CTRL_s_axi BINDTYPE interface TYPE interface_s_axilite}
      {MODELNAME RK4_LBE_regslice_both RTLNAME RK4_LBE_regslice_both BINDTYPE interface TYPE interface_regslice INSTNAME RK4_LBE_regslice_both_U}
    }
  }
}
