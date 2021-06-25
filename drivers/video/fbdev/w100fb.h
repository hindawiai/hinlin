<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/drivers/video/w100fb.h
 *
 * Frame Buffer Device क्रम ATI w100 (Wallaby)
 *
 * Copyright (C) 2002, ATI Corp.
 * Copyright (C) 2004-2005 Riअक्षरd Purdie
 * Copyright (c) 2005 Ian Molton <spyro@f2s.com>
 *
 * Modअगरied to work with 2.6 by Riअक्षरd Purdie <rpurdie@rpsys.net>
 *
 * w32xx support by Ian Molton
 */

#अगर !defined (_W100FB_H)
#घोषणा _W100FB_H

/* Block CIF Start: */
#घोषणा mmCHIP_ID           0x0000
#घोषणा mmREVISION_ID       0x0004
#घोषणा mmWRAP_BUF_A        0x0008
#घोषणा mmWRAP_BUF_B        0x000C
#घोषणा mmWRAP_TOP_सूची      0x0010
#घोषणा mmWRAP_START_सूची    0x0014
#घोषणा mmCIF_CNTL          0x0018
#घोषणा mmCFGREG_BASE       0x001C
#घोषणा mmCIF_IO            0x0020
#घोषणा mmCIF_READ_DBG      0x0024
#घोषणा mmCIF_WRITE_DBG     0x0028
#घोषणा cfgIND_ADDR_A_0     0x0000
#घोषणा cfgIND_ADDR_A_1     0x0001
#घोषणा cfgIND_ADDR_A_2     0x0002
#घोषणा cfgIND_DATA_A       0x0003
#घोषणा cfgREG_BASE         0x0004
#घोषणा cfgINTF_CNTL        0x0005
#घोषणा cfgSTATUS           0x0006
#घोषणा cfgCPU_DEFAULTS     0x0007
#घोषणा cfgIND_ADDR_B_0     0x0008
#घोषणा cfgIND_ADDR_B_1     0x0009
#घोषणा cfgIND_ADDR_B_2     0x000A
#घोषणा cfgIND_DATA_B       0x000B
#घोषणा cfgPM4_RPTR         0x000C
#घोषणा cfgSCRATCH          0x000D
#घोषणा cfgPM4_WRPTR_0      0x000E
#घोषणा cfgPM4_WRPTR_1      0x000F
/* Block CIF End: */

/* Block CP Start: */
#घोषणा mmSCRATCH_UMSK      0x0280
#घोषणा mmSCRATCH_ADDR      0x0284
#घोषणा mmGEN_INT_CNTL      0x0200
#घोषणा mmGEN_INT_STATUS    0x0204
/* Block CP End: */

/* Block DISPLAY Start: */
#घोषणा mmLCD_FORMAT        0x0410
#घोषणा mmGRAPHIC_CTRL      0x0414
#घोषणा mmGRAPHIC_OFFSET    0x0418
#घोषणा mmGRAPHIC_PITCH     0x041C
#घोषणा mmCRTC_TOTAL        0x0420
#घोषणा mmACTIVE_H_DISP     0x0424
#घोषणा mmACTIVE_V_DISP     0x0428
#घोषणा mmGRAPHIC_H_DISP    0x042C
#घोषणा mmGRAPHIC_V_DISP    0x0430
#घोषणा mmVIDEO_CTRL        0x0434
#घोषणा mmGRAPHIC_KEY       0x0438
#घोषणा mmBRIGHTNESS_CNTL   0x045C
#घोषणा mmDISP_INT_CNTL     0x0488
#घोषणा mmCRTC_SS           0x048C
#घोषणा mmCRTC_LS           0x0490
#घोषणा mmCRTC_REV          0x0494
#घोषणा mmCRTC_DCLK         0x049C
#घोषणा mmCRTC_GS           0x04A0
#घोषणा mmCRTC_VPOS_GS      0x04A4
#घोषणा mmCRTC_GCLK         0x04A8
#घोषणा mmCRTC_GOE          0x04AC
#घोषणा mmCRTC_FRAME        0x04B0
#घोषणा mmCRTC_FRAME_VPOS   0x04B4
#घोषणा mmGPIO_DATA         0x04B8
#घोषणा mmGPIO_CNTL1        0x04BC
#घोषणा mmGPIO_CNTL2        0x04C0
#घोषणा mmLCDD_CNTL1        0x04C4
#घोषणा mmLCDD_CNTL2        0x04C8
#घोषणा mmGENLCD_CNTL1      0x04CC
#घोषणा mmGENLCD_CNTL2      0x04D0
#घोषणा mmDISP_DEBUG        0x04D4
#घोषणा mmDISP_DB_BUF_CNTL  0x04D8
#घोषणा mmDISP_CRC_SIG      0x04DC
#घोषणा mmCRTC_DEFAULT_COUNT    0x04E0
#घोषणा mmLCD_BACKGROUND_COLOR  0x04E4
#घोषणा mmCRTC_PS2          0x04E8
#घोषणा mmCRTC_PS2_VPOS     0x04EC
#घोषणा mmCRTC_PS1_ACTIVE   0x04F0
#घोषणा mmCRTC_PS1_NACTIVE  0x04F4
#घोषणा mmCRTC_GCLK_EXT     0x04F8
#घोषणा mmCRTC_ALW          0x04FC
#घोषणा mmCRTC_ALW_VPOS     0x0500
#घोषणा mmCRTC_PSK          0x0504
#घोषणा mmCRTC_PSK_HPOS     0x0508
#घोषणा mmCRTC_CV4_START    0x050C
#घोषणा mmCRTC_CV4_END      0x0510
#घोषणा mmCRTC_CV4_HPOS     0x0514
#घोषणा mmCRTC_ECK          0x051C
#घोषणा mmREFRESH_CNTL      0x0520
#घोषणा mmGENLCD_CNTL3      0x0524
#घोषणा mmGPIO_DATA2        0x0528
#घोषणा mmGPIO_CNTL3        0x052C
#घोषणा mmGPIO_CNTL4        0x0530
#घोषणा mmCHIP_STRAP        0x0534
#घोषणा mmDISP_DEBUG2       0x0538
#घोषणा mmDEBUG_BUS_CNTL    0x053C
#घोषणा mmGAMMA_VALUE1      0x0540
#घोषणा mmGAMMA_VALUE2      0x0544
#घोषणा mmGAMMA_SLOPE       0x0548
#घोषणा mmGEN_STATUS        0x054C
#घोषणा mmHW_INT            0x0550
/* Block DISPLAY End: */

/* Block GFX Start: */
#घोषणा mmDST_OFFSET          0x1004
#घोषणा mmDST_PITCH           0x1008
#घोषणा mmDST_Y_X             0x1038
#घोषणा mmDST_WIDTH_HEIGHT    0x1198
#घोषणा mmDP_GUI_MASTER_CNTL  0x106C
#घोषणा mmBRUSH_OFFSET        0x108C
#घोषणा mmBRUSH_Y_X           0x1074
#घोषणा mmDP_BRUSH_FRGD_CLR   0x107C
#घोषणा mmSRC_OFFSET          0x11AC
#घोषणा mmSRC_PITCH           0x11B0
#घोषणा mmSRC_Y_X             0x1034
#घोषणा mmDEFAULT_PITCH_OFFSET      0x10A0
#घोषणा mmDEFAULT_SC_BOTTOM_RIGHT   0x10A8
#घोषणा mmDEFAULT2_SC_BOTTOM_RIGHT  0x10AC
#घोषणा mmSC_TOP_LEFT         0x11BC
#घोषणा mmSC_BOTTOM_RIGHT     0x11C0
#घोषणा mmSRC_SC_BOTTOM_RIGHT 0x11C4
#घोषणा mmGLOBAL_ALPHA        0x1210
#घोषणा mmFILTER_COEF         0x1214
#घोषणा mmMVC_CNTL_START      0x11E0
#घोषणा mmE2_ARITHMETIC_CNTL  0x1220
#घोषणा mmDP_CNTL             0x11C8
#घोषणा mmDP_CNTL_DST_सूची     0x11CC
#घोषणा mmDP_DATATYPE         0x12C4
#घोषणा mmDP_MIX              0x12C8
#घोषणा mmDP_WRITE_MSK        0x12CC
#घोषणा mmENG_CNTL            0x13E8
#घोषणा mmENG_PERF_CNT        0x13F0
/* Block GFX End: */

/* Block IDCT Start: */
#घोषणा mmIDCT_RUNS         0x0C00
#घोषणा mmIDCT_LEVELS       0x0C04
#घोषणा mmIDCT_CONTROL      0x0C3C
#घोषणा mmIDCT_AUTH_CONTROL 0x0C08
#घोषणा mmIDCT_AUTH         0x0C0C
/* Block IDCT End: */

/* Block MC Start: */
#घोषणा mmMEM_CNTL             0x0180
#घोषणा mmMEM_ARB              0x0184
#घोषणा mmMC_FB_LOCATION       0x0188
#घोषणा mmMEM_EXT_CNTL         0x018C
#घोषणा mmMC_EXT_MEM_LOCATION  0x0190
#घोषणा mmMEM_EXT_TIMING_CNTL  0x0194
#घोषणा mmMEM_SDRAM_MODE_REG   0x0198
#घोषणा mmMEM_IO_CNTL          0x019C
#घोषणा mmMC_DEBUG             0x01A0
#घोषणा mmMC_BIST_CTRL         0x01A4
#घोषणा mmMC_BIST_COLLAR_READ  0x01A8
#घोषणा mmTC_MISMATCH          0x01AC
#घोषणा mmMC_PERF_MON_CNTL     0x01B0
#घोषणा mmMC_PERF_COUNTERS     0x01B4
/* Block MC End: */

/* Block BM Start: */
#घोषणा mmBM_EXT_MEM_BANDWIDTH    0x0A00
#घोषणा mmBM_OFFSET               0x0A04
#घोषणा mmBM_MEM_EXT_TIMING_CNTL  0x0A08
#घोषणा mmBM_MEM_EXT_CNTL         0x0A0C
#घोषणा mmBM_MEM_MODE_REG         0x0A10
#घोषणा mmBM_MEM_IO_CNTL          0x0A18
#घोषणा mmBM_CONFIG               0x0A1C
#घोषणा mmBM_STATUS               0x0A20
#घोषणा mmBM_DEBUG                0x0A24
#घोषणा mmBM_PERF_MON_CNTL        0x0A28
#घोषणा mmBM_PERF_COUNTERS        0x0A2C
#घोषणा mmBM_PERF2_MON_CNTL       0x0A30
#घोषणा mmBM_PERF2_COUNTERS       0x0A34
/* Block BM End: */

/* Block RBBM Start: */
#घोषणा mmWAIT_UNTIL        0x1400
#घोषणा mmISYNC_CNTL        0x1404
#घोषणा mmRBBM_STATUS       0x0140
#घोषणा mmRBBM_CNTL         0x0144
#घोषणा mmNQWAIT_UNTIL      0x0150
/* Block RBBM End: */

/* Block CG Start: */
#घोषणा mmCLK_PIN_CNTL      0x0080
#घोषणा mmPLL_REF_FB_DIV    0x0084
#घोषणा mmPLL_CNTL          0x0088
#घोषणा mmSCLK_CNTL         0x008C
#घोषणा mmPCLK_CNTL         0x0090
#घोषणा mmCLK_TEST_CNTL     0x0094
#घोषणा mmPWRMGT_CNTL       0x0098
#घोषणा mmPWRMGT_STATUS     0x009C
/* Block CG End: */

/* शेष value definitions */
#घोषणा defWRAP_TOP_सूची        0x00000000
#घोषणा defWRAP_START_सूची      0x00000000
#घोषणा defCFGREG_BASE         0x00000000
#घोषणा defCIF_IO              0x000C0902
#घोषणा defINTF_CNTL           0x00000011
#घोषणा defCPU_DEFAULTS        0x00000006
#घोषणा defHW_INT              0x00000000
#घोषणा defMC_EXT_MEM_LOCATION 0x07ff0000
#घोषणा defTC_MISMATCH         0x00000000

#घोषणा W100_CFG_BASE          0x0
#घोषणा W100_CFG_LEN           0x10
#घोषणा W100_REG_BASE          0x10000
#घोषणा W100_REG_LEN           0x2000
#घोषणा MEM_INT_BASE_VALUE     0x100000
#घोषणा MEM_EXT_BASE_VALUE     0x800000
#घोषणा MEM_INT_SIZE           0x05ffff
#घोषणा MEM_WINDOW_BASE        0x100000
#घोषणा MEM_WINDOW_SIZE        0xf00000

#घोषणा WRAP_BUF_BASE_VALUE    0x80000
#घोषणा WRAP_BUF_TOP_VALUE     0xbffff

#घोषणा CHIP_ID_W100           0x57411002
#घोषणा CHIP_ID_W3200          0x56441002
#घोषणा CHIP_ID_W3220          0x57441002

/* Register काष्ठाure definitions */

काष्ठा wrap_top_dir_t अणु
	u32 top_addr  : 23;
	u32           : 9;
पूर्ण __attribute__((packed));

जोड़ wrap_top_dir_u अणु
	u32 val : 32;
	काष्ठा wrap_top_dir_t f;
पूर्ण __attribute__((packed));

काष्ठा wrap_start_dir_t अणु
	u32 start_addr : 23;
	u32            : 9;
पूर्ण __attribute__((packed));

जोड़ wrap_start_dir_u अणु
	u32 val : 32;
	काष्ठा wrap_start_dir_t f;
पूर्ण __attribute__((packed));

काष्ठा cअगर_cntl_t अणु
	u32 swap_reg                 : 2;
	u32 swap_fbuf_1              : 2;
	u32 swap_fbuf_2              : 2;
	u32 swap_fbuf_3              : 2;
	u32 pmi_पूर्णांक_disable          : 1;
	u32 pmi_schmen_disable       : 1;
	u32 पूर्णांकb_oe                  : 1;
	u32 en_रुको_to_compensate_dq_prop_dly  : 1;
	u32 compensate_रुको_rd_size  : 2;
	u32 रुको_निश्चितed_समयout_val  : 2;
	u32 रुको_masked_val          : 2;
	u32 en_रुको_समयout          : 1;
	u32 en_one_clk_setup_beक्रमe_रुको  : 1;
	u32 पूर्णांकerrupt_active_high    : 1;
	u32 en_overग_लिखो_straps      : 1;
	u32 strap_रुको_active_hi     : 1;
	u32 lat_busy_count           : 2;
	u32 lat_rd_pm4_sclk_busy     : 1;
	u32 dis_प्रणाली_bits          : 1;
	u32 dis_mr                   : 1;
	u32 cअगर_spare_1              : 4;
पूर्ण __attribute__((packed));

जोड़ cअगर_cntl_u अणु
	u32 val : 32;
	काष्ठा cअगर_cntl_t f;
पूर्ण __attribute__((packed));

काष्ठा cfgreg_base_t अणु
	u32 cfgreg_base  : 24;
	u32              : 8;
पूर्ण __attribute__((packed));

जोड़ cfgreg_base_u अणु
	u32 val : 32;
	काष्ठा cfgreg_base_t f;
पूर्ण __attribute__((packed));

काष्ठा cअगर_io_t अणु
	u32 dq_srp     : 1;
	u32 dq_srn     : 1;
	u32 dq_sp      : 4;
	u32 dq_sn      : 4;
	u32 रुकोb_srp  : 1;
	u32 रुकोb_srn  : 1;
	u32 रुकोb_sp   : 4;
	u32 रुकोb_sn   : 4;
	u32 पूर्णांकb_srp   : 1;
	u32 पूर्णांकb_srn   : 1;
	u32 पूर्णांकb_sp    : 4;
	u32 पूर्णांकb_sn    : 4;
	u32            : 2;
पूर्ण __attribute__((packed));

जोड़ cअगर_io_u अणु
	u32 val : 32;
	काष्ठा cअगर_io_t f;
पूर्ण __attribute__((packed));

काष्ठा cअगर_पढ़ो_dbg_t अणु
	u32 unpacker_pre_fetch_trig_gen  : 2;
	u32 dly_second_rd_fetch_trig     : 1;
	u32 rst_rd_burst_id              : 1;
	u32 dis_rd_burst_id              : 1;
	u32 en_block_rd_when_packer_is_not_emp : 1;
	u32 dis_pre_fetch_cntl_sm        : 1;
	u32 rbbm_chrncy_dis              : 1;
	u32 rbbm_rd_after_wr_lat         : 2;
	u32 dis_be_during_rd             : 1;
	u32 one_clk_invalidate_pulse     : 1;
	u32 dis_chnl_priority            : 1;
	u32 rst_पढ़ो_path_a_pls          : 1;
	u32 rst_पढ़ो_path_b_pls          : 1;
	u32 dis_reg_rd_fetch_trig        : 1;
	u32 dis_rd_fetch_trig_from_ind_addr : 1;
	u32 dis_rd_same_byte_to_trig_fetch : 1;
	u32 dis_dir_wrap                 : 1;
	u32 dis_ring_buf_to_क्रमce_dec    : 1;
	u32 dis_addr_comp_in_16bit       : 1;
	u32 clr_w                        : 1;
	u32 err_rd_tag_is_3              : 1;
	u32 err_load_when_ful_a          : 1;
	u32 err_load_when_ful_b          : 1;
	u32                              : 7;
पूर्ण __attribute__((packed));

जोड़ cअगर_पढ़ो_dbg_u अणु
	u32 val : 32;
	काष्ठा cअगर_पढ़ो_dbg_t f;
पूर्ण __attribute__((packed));

काष्ठा cअगर_ग_लिखो_dbg_t अणु
	u32 packer_समयout_count          : 2;
	u32 en_upper_load_cond            : 1;
	u32 en_chnl_change_cond           : 1;
	u32 dis_addr_comp_cond            : 1;
	u32 dis_load_same_byte_addr_cond  : 1;
	u32 dis_समयout_cond              : 1;
	u32 dis_समयout_during_rbbm       : 1;
	u32 dis_packer_ful_during_rbbm_समयout : 1;
	u32 en_dword_split_to_rbbm        : 1;
	u32 en_dummy_val                  : 1;
	u32 dummy_val_sel                 : 1;
	u32 mask_pm4_wrptr_dec            : 1;
	u32 dis_mc_clean_cond             : 1;
	u32 err_two_reqi_during_ful       : 1;
	u32 err_reqi_during_idle_clk      : 1;
	u32 err_global                    : 1;
	u32 en_wr_buf_dbg_load            : 1;
	u32 en_wr_buf_dbg_path            : 1;
	u32 sel_wr_buf_byte               : 3;
	u32 dis_rd_flush_wr               : 1;
	u32 dis_packer_ful_cond           : 1;
	u32 dis_invalidate_by_ops_chnl    : 1;
	u32 en_halt_when_reqi_err         : 1;
	u32 cअगर_spare_2                   : 5;
	u32                               : 1;
पूर्ण __attribute__((packed));

जोड़ cअगर_ग_लिखो_dbg_u अणु
	u32 val : 32;
	काष्ठा cअगर_ग_लिखो_dbg_t f;
पूर्ण __attribute__((packed));


काष्ठा पूर्णांकf_cntl_t अणु
	अचिन्हित अक्षर ad_inc_a            : 1;
	अचिन्हित अक्षर ring_buf_a          : 1;
	अचिन्हित अक्षर rd_fetch_trigger_a  : 1;
	अचिन्हित अक्षर rd_data_rdy_a       : 1;
	अचिन्हित अक्षर ad_inc_b            : 1;
	अचिन्हित अक्षर ring_buf_b          : 1;
	अचिन्हित अक्षर rd_fetch_trigger_b  : 1;
	अचिन्हित अक्षर rd_data_rdy_b       : 1;
पूर्ण __attribute__((packed));

जोड़ पूर्णांकf_cntl_u अणु
	अचिन्हित अक्षर val : 8;
	काष्ठा पूर्णांकf_cntl_t f;
पूर्ण __attribute__((packed));

काष्ठा cpu_शेषs_t अणु
	अचिन्हित अक्षर unpack_rd_data     : 1;
	अचिन्हित अक्षर access_ind_addr_a  : 1;
	अचिन्हित अक्षर access_ind_addr_b  : 1;
	अचिन्हित अक्षर access_scratch_reg : 1;
	अचिन्हित अक्षर pack_wr_data       : 1;
	अचिन्हित अक्षर transition_size    : 1;
	अचिन्हित अक्षर en_पढ़ो_buf_mode   : 1;
	अचिन्हित अक्षर rd_fetch_scratch   : 1;
पूर्ण __attribute__((packed));

जोड़ cpu_शेषs_u अणु
	अचिन्हित अक्षर val : 8;
	काष्ठा cpu_शेषs_t f;
पूर्ण __attribute__((packed));

काष्ठा crtc_total_t अणु
	u32 crtc_h_total : 10;
	u32              : 6;
	u32 crtc_v_total : 10;
	u32              : 6;
पूर्ण __attribute__((packed));

जोड़ crtc_total_u अणु
	u32 val : 32;
	काष्ठा crtc_total_t f;
पूर्ण __attribute__((packed));

काष्ठा crtc_ss_t अणु
	u32 ss_start    : 10;
	u32             : 6;
	u32 ss_end      : 10;
	u32             : 2;
	u32 ss_align    : 1;
	u32 ss_pol      : 1;
	u32 ss_run_mode : 1;
	u32 ss_en       : 1;
पूर्ण __attribute__((packed));

जोड़ crtc_ss_u अणु
	u32 val : 32;
	काष्ठा crtc_ss_t f;
पूर्ण __attribute__((packed));

काष्ठा active_h_disp_t अणु
	u32 active_h_start  : 10;
	u32                 : 6;
	u32 active_h_end    : 10;
	u32                 : 6;
पूर्ण __attribute__((packed));

जोड़ active_h_disp_u अणु
	u32 val : 32;
	काष्ठा active_h_disp_t f;
पूर्ण __attribute__((packed));

काष्ठा active_v_disp_t अणु
	u32 active_v_start  : 10;
	u32                 : 6;
	u32 active_v_end    : 10;
	u32                 : 6;
पूर्ण __attribute__((packed));

जोड़ active_v_disp_u अणु
	u32 val : 32;
	काष्ठा active_v_disp_t f;
पूर्ण __attribute__((packed));

काष्ठा graphic_h_disp_t अणु
	u32 graphic_h_start : 10;
	u32                 : 6;
	u32 graphic_h_end   : 10;
	u32                 : 6;
पूर्ण __attribute__((packed));

जोड़ graphic_h_disp_u अणु
	u32 val : 32;
	काष्ठा graphic_h_disp_t f;
पूर्ण __attribute__((packed));

काष्ठा graphic_v_disp_t अणु
	u32 graphic_v_start : 10;
	u32                 : 6;
	u32 graphic_v_end   : 10;
	u32                 : 6;
पूर्ण __attribute__((packed));

जोड़ graphic_v_disp_uअणु
	u32 val : 32;
	काष्ठा graphic_v_disp_t f;
पूर्ण __attribute__((packed));

काष्ठा graphic_ctrl_t_w100 अणु
	u32 color_depth       : 3;
	u32 portrait_mode     : 2;
	u32 low_घातer_on      : 1;
	u32 req_freq          : 4;
	u32 en_crtc           : 1;
	u32 en_graphic_req    : 1;
	u32 en_graphic_crtc   : 1;
	u32 total_req_graphic : 9;
	u32 lcd_pclk_on       : 1;
	u32 lcd_sclk_on       : 1;
	u32 pclk_running      : 1;
	u32 sclk_running      : 1;
	u32                   : 6;
पूर्ण __attribute__((packed));

काष्ठा graphic_ctrl_t_w32xx अणु
	u32 color_depth       : 3;
	u32 portrait_mode     : 2;
	u32 low_घातer_on      : 1;
	u32 req_freq          : 4;
	u32 en_crtc           : 1;
	u32 en_graphic_req    : 1;
	u32 en_graphic_crtc   : 1;
	u32 total_req_graphic : 10;
	u32 lcd_pclk_on       : 1;
	u32 lcd_sclk_on       : 1;
	u32 pclk_running      : 1;
	u32 sclk_running      : 1;
	u32                   : 5;
पूर्ण __attribute__((packed));

जोड़ graphic_ctrl_u अणु
	u32 val : 32;
	काष्ठा graphic_ctrl_t_w100 f_w100;
	काष्ठा graphic_ctrl_t_w32xx f_w32xx;
पूर्ण __attribute__((packed));

काष्ठा video_ctrl_t अणु
	u32 video_mode       : 1;
	u32 keyer_en         : 1;
	u32 en_video_req     : 1;
	u32 en_graphic_req_video  : 1;
	u32 en_video_crtc    : 1;
	u32 video_hor_exp    : 2;
	u32 video_ver_exp    : 2;
	u32 uv_combine       : 1;
	u32 total_req_video  : 9;
	u32 video_ch_sel     : 1;
	u32 video_portrait   : 2;
	u32 yuv2rgb_en       : 1;
	u32 yuv2rgb_option   : 1;
	u32 video_inv_hor    : 1;
	u32 video_inv_ver    : 1;
	u32 gamma_sel        : 2;
	u32 dis_limit        : 1;
	u32 en_uv_hblend     : 1;
	u32 rgb_gamma_sel    : 2;
पूर्ण __attribute__((packed));

जोड़ video_ctrl_u अणु
	u32 val : 32;
	काष्ठा video_ctrl_t f;
पूर्ण __attribute__((packed));

काष्ठा disp_db_buf_cntl_rd_t अणु
	u32 en_db_buf           : 1;
	u32 update_db_buf_करोne  : 1;
	u32 db_buf_cntl         : 6;
	u32                     : 24;
पूर्ण __attribute__((packed));

जोड़ disp_db_buf_cntl_rd_u अणु
	u32 val : 32;
	काष्ठा disp_db_buf_cntl_rd_t f;
पूर्ण __attribute__((packed));

काष्ठा disp_db_buf_cntl_wr_t अणु
	u32 en_db_buf      : 1;
	u32 update_db_buf  : 1;
	u32 db_buf_cntl    : 6;
	u32                : 24;
पूर्ण __attribute__((packed));

जोड़ disp_db_buf_cntl_wr_u अणु
	u32 val : 32;
	काष्ठा disp_db_buf_cntl_wr_t f;
पूर्ण __attribute__((packed));

काष्ठा gamma_value1_t अणु
	u32 gamma1   : 8;
	u32 gamma2   : 8;
	u32 gamma3   : 8;
	u32 gamma4   : 8;
पूर्ण __attribute__((packed));

जोड़ gamma_value1_u अणु
	u32 val : 32;
	काष्ठा gamma_value1_t f;
पूर्ण __attribute__((packed));

काष्ठा gamma_value2_t अणु
	u32 gamma5   : 8;
	u32 gamma6   : 8;
	u32 gamma7   : 8;
	u32 gamma8   : 8;
पूर्ण __attribute__((packed));

जोड़ gamma_value2_u अणु
	u32 val : 32;
	काष्ठा gamma_value2_t f;
पूर्ण __attribute__((packed));

काष्ठा gamma_slope_t अणु
	u32 slope1   : 3;
	u32 slope2   : 3;
	u32 slope3   : 3;
	u32 slope4   : 3;
	u32 slope5   : 3;
	u32 slope6   : 3;
	u32 slope7   : 3;
	u32 slope8   : 3;
	u32          : 8;
पूर्ण __attribute__((packed));

जोड़ gamma_slope_u अणु
	u32 val : 32;
	काष्ठा gamma_slope_t f;
पूर्ण __attribute__((packed));

काष्ठा mc_ext_mem_location_t अणु
	u32 mc_ext_mem_start : 16;
	u32 mc_ext_mem_top   : 16;
पूर्ण __attribute__((packed));

जोड़ mc_ext_mem_location_u अणु
	u32 val : 32;
	काष्ठा mc_ext_mem_location_t f;
पूर्ण __attribute__((packed));

काष्ठा mc_fb_location_t अणु
	u32 mc_fb_start      : 16;
	u32 mc_fb_top        : 16;
पूर्ण __attribute__((packed));

जोड़ mc_fb_location_u अणु
	u32 val : 32;
	काष्ठा mc_fb_location_t f;
पूर्ण __attribute__((packed));

काष्ठा clk_pin_cntl_t अणु
	u32 osc_en           : 1;
	u32 osc_gain         : 5;
	u32 करोnt_use_xtalin  : 1;
	u32 xtalin_pm_en     : 1;
	u32 xtalin_dbl_en    : 1;
	u32                  : 7;
	u32 cg_debug         : 16;
पूर्ण __attribute__((packed));

जोड़ clk_pin_cntl_u अणु
	u32 val : 32;
	काष्ठा clk_pin_cntl_t f;
पूर्ण __attribute__((packed));

काष्ठा pll_ref_fb_भाग_प्रकार अणु
	u32 pll_ref_भाग      : 4;
	u32                  : 4;
	u32 pll_fb_भाग_पूर्णांक   : 6;
	u32                  : 2;
	u32 pll_fb_भाग_frac  : 3;
	u32                  : 1;
	u32 pll_reset_समय   : 4;
	u32 pll_lock_समय    : 8;
पूर्ण __attribute__((packed));

जोड़ pll_ref_fb_भाग_u अणु
	u32 val : 32;
	काष्ठा pll_ref_fb_भाग_प्रकार f;
पूर्ण __attribute__((packed));

काष्ठा pll_cntl_t अणु
	u32 pll_pwdn        : 1;
	u32 pll_reset       : 1;
	u32 pll_pm_en       : 1;
	u32 pll_mode        : 1;
	u32 pll_refclk_sel  : 1;
	u32 pll_fbclk_sel   : 1;
	u32 pll_tcpoff      : 1;
	u32 pll_pcp         : 3;
	u32 pll_pvg         : 3;
	u32 pll_vcofr       : 1;
	u32 pll_ioffset     : 2;
	u32 pll_pecc_mode   : 2;
	u32 pll_pecc_scon   : 2;
	u32 pll_dactal      : 4;
	u32 pll_cp_clip     : 2;
	u32 pll_conf        : 3;
	u32 pll_mbctrl      : 2;
	u32 pll_ring_off    : 1;
पूर्ण __attribute__((packed));

जोड़ pll_cntl_u अणु
	u32 val : 32;
	काष्ठा pll_cntl_t f;
पूर्ण __attribute__((packed));

काष्ठा sclk_cntl_t अणु
	u32 sclk_src_sel         : 2;
	u32                      : 2;
	u32 sclk_post_भाग_fast   : 4;
	u32 sclk_clkon_hys       : 3;
	u32 sclk_post_भाग_slow   : 4;
	u32 disp_cg_ok2चयन_en : 1;
	u32 sclk_क्रमce_reg       : 1;
	u32 sclk_क्रमce_disp      : 1;
	u32 sclk_क्रमce_mc        : 1;
	u32 sclk_क्रमce_exपंचांगc     : 1;
	u32 sclk_क्रमce_cp        : 1;
	u32 sclk_क्रमce_e2        : 1;
	u32 sclk_क्रमce_e3        : 1;
	u32 sclk_क्रमce_idct      : 1;
	u32 sclk_क्रमce_bist      : 1;
	u32 busy_extend_cp       : 1;
	u32 busy_extend_e2       : 1;
	u32 busy_extend_e3       : 1;
	u32 busy_extend_idct     : 1;
	u32                      : 3;
पूर्ण __attribute__((packed));

जोड़ sclk_cntl_u अणु
	u32 val : 32;
	काष्ठा sclk_cntl_t f;
पूर्ण __attribute__((packed));

काष्ठा pclk_cntl_t अणु
	u32 pclk_src_sel     : 2;
	u32                  : 2;
	u32 pclk_post_भाग    : 4;
	u32                  : 8;
	u32 pclk_क्रमce_disp  : 1;
	u32                  : 15;
पूर्ण __attribute__((packed));

जोड़ pclk_cntl_u अणु
	u32 val : 32;
	काष्ठा pclk_cntl_t f;
पूर्ण __attribute__((packed));


#घोषणा TESTCLK_SRC_PLL   0x01
#घोषणा TESTCLK_SRC_SCLK  0x02
#घोषणा TESTCLK_SRC_PCLK  0x03
/* 4 and 5 seem to by XTAL/M */
#घोषणा TESTCLK_SRC_XTAL  0x06

काष्ठा clk_test_cntl_t अणु
	u32 testclk_sel      : 4;
	u32                  : 3;
	u32 start_check_freq : 1;
	u32 tstcount_rst     : 1;
	u32                  : 15;
	u32 test_count       : 8;
पूर्ण __attribute__((packed));

जोड़ clk_test_cntl_u अणु
	u32 val : 32;
	काष्ठा clk_test_cntl_t f;
पूर्ण __attribute__((packed));

काष्ठा pwrmgt_cntl_t अणु
	u32 pwm_enable           : 1;
	u32                      : 1;
	u32 pwm_mode_req         : 2;
	u32 pwm_wakeup_cond      : 2;
	u32 pwm_fast_noml_hw_en  : 1;
	u32 pwm_noml_fast_hw_en  : 1;
	u32 pwm_fast_noml_cond   : 4;
	u32 pwm_noml_fast_cond   : 4;
	u32 pwm_idle_समयr       : 8;
	u32 pwm_busy_समयr       : 8;
पूर्ण __attribute__((packed));

जोड़ pwrmgt_cntl_u अणु
	u32 val : 32;
	काष्ठा pwrmgt_cntl_t f;
पूर्ण __attribute__((packed));

#घोषणा SRC_DATATYPE_EQU_DST	3

#घोषणा ROP3_SRCCOPY	0xcc
#घोषणा ROP3_PATCOPY	0xf0

#घोषणा GMC_BRUSH_SOLID_COLOR	13
#घोषणा GMC_BRUSH_NONE			15

#घोषणा DP_SRC_MEM_RECTANGULAR	2

#घोषणा DP_OP_ROP	0

काष्ठा dp_gui_master_cntl_t अणु
	u32 gmc_src_pitch_offset_cntl : 1;
	u32 gmc_dst_pitch_offset_cntl : 1;
	u32 gmc_src_clipping          : 1;
	u32 gmc_dst_clipping          : 1;
	u32 gmc_brush_datatype        : 4;
	u32 gmc_dst_datatype          : 4;
	u32 gmc_src_datatype          : 3;
	u32 gmc_byte_pix_order        : 1;
	u32 gmc_शेष_sel           : 1;
	u32 gmc_rop3                  : 8;
	u32 gmc_dp_src_source         : 3;
	u32 gmc_clr_cmp_fcn_dis       : 1;
	u32                           : 1;
	u32 gmc_wr_msk_dis            : 1;
	u32 gmc_dp_op                 : 1;
पूर्ण __attribute__((packed));

जोड़ dp_gui_master_cntl_u अणु
	u32 val : 32;
	काष्ठा dp_gui_master_cntl_t f;
पूर्ण __attribute__((packed));

काष्ठा rbbm_status_t अणु
	u32 cmdfअगरo_avail   : 7;
	u32                 : 1;
	u32 hirq_on_rbb     : 1;
	u32 cprq_on_rbb     : 1;
	u32 cfrq_on_rbb     : 1;
	u32 hirq_in_rtbuf   : 1;
	u32 cprq_in_rtbuf   : 1;
	u32 cfrq_in_rtbuf   : 1;
	u32 cf_pipe_busy    : 1;
	u32 eng_ev_busy     : 1;
	u32 cp_cmdstrm_busy : 1;
	u32 e2_busy         : 1;
	u32 rb2d_busy       : 1;
	u32 rb3d_busy       : 1;
	u32 se_busy         : 1;
	u32 re_busy         : 1;
	u32 tam_busy        : 1;
	u32 tdm_busy        : 1;
	u32 pb_busy         : 1;
	u32                 : 6;
	u32 gui_active      : 1;
पूर्ण __attribute__((packed));

जोड़ rbbm_status_u अणु
	u32 val : 32;
	काष्ठा rbbm_status_t f;
पूर्ण __attribute__((packed));

काष्ठा dp_datatype_t अणु
	u32 dp_dst_datatype   : 4;
	u32                   : 4;
	u32 dp_brush_datatype : 4;
	u32 dp_src2_type      : 1;
	u32 dp_src2_datatype  : 3;
	u32 dp_src_datatype   : 3;
	u32                   : 11;
	u32 dp_byte_pix_order : 1;
	u32                   : 1;
पूर्ण __attribute__((packed));

जोड़ dp_datatype_u अणु
	u32 val : 32;
	काष्ठा dp_datatype_t f;
पूर्ण __attribute__((packed));

काष्ठा dp_mix_t अणु
	u32                : 8;
	u32 dp_src_source  : 3;
	u32 dp_src2_source : 3;
	u32                : 2;
	u32 dp_rop3        : 8;
	u32 dp_op          : 1;
	u32                : 7;
पूर्ण __attribute__((packed));

जोड़ dp_mix_u अणु
	u32 val : 32;
	काष्ठा dp_mix_t f;
पूर्ण __attribute__((packed));

काष्ठा eng_cntl_t अणु
	u32 erc_reg_rd_ws            : 1;
	u32 erc_reg_wr_ws            : 1;
	u32 erc_idle_reg_wr          : 1;
	u32 dis_engine_triggers      : 1;
	u32 dis_rop_src_uses_dst_w_h : 1;
	u32 dis_src_uses_dst_dirmaj  : 1;
	u32                          : 6;
	u32 क्रमce_3dclk_when_2dclk   : 1;
	u32                          : 19;
पूर्ण __attribute__((packed));

जोड़ eng_cntl_u अणु
	u32 val : 32;
	काष्ठा eng_cntl_t f;
पूर्ण __attribute__((packed));

काष्ठा dp_cntl_t अणु
	u32 dst_x_dir   : 1;
	u32 dst_y_dir   : 1;
	u32 src_x_dir   : 1;
	u32 src_y_dir   : 1;
	u32 dst_major_x : 1;
	u32 src_major_x : 1;
	u32             : 26;
पूर्ण __attribute__((packed));

जोड़ dp_cntl_u अणु
	u32 val : 32;
	काष्ठा dp_cntl_t f;
पूर्ण __attribute__((packed));

काष्ठा dp_cntl_dst_dir_t अणु
	u32           : 15;
	u32 dst_y_dir : 1;
	u32           : 15;
	u32 dst_x_dir : 1;
पूर्ण __attribute__((packed));

जोड़ dp_cntl_dst_dir_u अणु
	u32 val : 32;
	काष्ठा dp_cntl_dst_dir_t f;
पूर्ण __attribute__((packed));

#पूर्ण_अगर

