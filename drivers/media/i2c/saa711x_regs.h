<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * saa711x - Philips SAA711x video decoder रेजिस्टर specअगरications
 *
 * Copyright (c) 2006 Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#घोषणा R_00_CHIP_VERSION                             0x00
/* Video Decoder */
	/* Video Decoder - Frontend part */
#घोषणा R_01_INC_DELAY                                0x01
#घोषणा R_02_INPUT_CNTL_1                             0x02
#घोषणा R_03_INPUT_CNTL_2                             0x03
#घोषणा R_04_INPUT_CNTL_3                             0x04
#घोषणा R_05_INPUT_CNTL_4                             0x05
	/* Video Decoder - Decoder part */
#घोषणा R_06_H_SYNC_START                             0x06
#घोषणा R_07_H_SYNC_STOP                              0x07
#घोषणा R_08_SYNC_CNTL                                0x08
#घोषणा R_09_LUMA_CNTL                                0x09
#घोषणा R_0A_LUMA_BRIGHT_CNTL                         0x0a
#घोषणा R_0B_LUMA_CONTRAST_CNTL                       0x0b
#घोषणा R_0C_CHROMA_SAT_CNTL                          0x0c
#घोषणा R_0D_CHROMA_HUE_CNTL                          0x0d
#घोषणा R_0E_CHROMA_CNTL_1                            0x0e
#घोषणा R_0F_CHROMA_GAIN_CNTL                         0x0f
#घोषणा R_10_CHROMA_CNTL_2                            0x10
#घोषणा R_11_MODE_DELAY_CNTL                          0x11
#घोषणा R_12_RT_SIGNAL_CNTL                           0x12
#घोषणा R_13_RT_X_PORT_OUT_CNTL                       0x13
#घोषणा R_14_ANAL_ADC_COMPAT_CNTL                     0x14
#घोषणा R_15_VGATE_START_FID_CHG                      0x15
#घोषणा R_16_VGATE_STOP                               0x16
#घोषणा R_17_MISC_VGATE_CONF_AND_MSB                  0x17
#घोषणा R_18_RAW_DATA_GAIN_CNTL                       0x18
#घोषणा R_19_RAW_DATA_OFF_CNTL                        0x19
#घोषणा R_1A_COLOR_KILL_LVL_CNTL                      0x1a
#घोषणा R_1B_MISC_TVVCRDET                            0x1b
#घोषणा R_1C_ENHAN_COMB_CTRL1                         0x1c
#घोषणा R_1D_ENHAN_COMB_CTRL2                         0x1d
#घोषणा R_1E_STATUS_BYTE_1_VD_DEC                     0x1e
#घोषणा R_1F_STATUS_BYTE_2_VD_DEC                     0x1f

/* Component processing and पूर्णांकerrupt masking part */
#घोषणा R_23_INPUT_CNTL_5                             0x23
#घोषणा R_24_INPUT_CNTL_6                             0x24
#घोषणा R_25_INPUT_CNTL_7                             0x25
#घोषणा R_29_COMP_DELAY                               0x29
#घोषणा R_2A_COMP_BRIGHT_CNTL                         0x2a
#घोषणा R_2B_COMP_CONTRAST_CNTL                       0x2b
#घोषणा R_2C_COMP_SAT_CNTL                            0x2c
#घोषणा R_2D_INTERRUPT_MASK_1                         0x2d
#घोषणा R_2E_INTERRUPT_MASK_2                         0x2e
#घोषणा R_2F_INTERRUPT_MASK_3                         0x2f

/* Audio घड़ी generator part */
#घोषणा R_30_AUD_MAST_CLK_CYCLES_PER_FIELD            0x30
#घोषणा R_34_AUD_MAST_CLK_NOMINAL_INC                 0x34
#घोषणा R_38_CLK_RATIO_AMXCLK_TO_ASCLK                0x38
#घोषणा R_39_CLK_RATIO_ASCLK_TO_ALRCLK                0x39
#घोषणा R_3A_AUD_CLK_GEN_BASIC_SETUP                  0x3a

/* General purpose VBI data slicer part */
#घोषणा R_40_SLICER_CNTL_1                            0x40
#घोषणा R_41_LCR_BASE                                 0x41
#घोषणा R_58_PROGRAM_FRAMING_CODE                     0x58
#घोषणा R_59_H_OFF_FOR_SLICER                         0x59
#घोषणा R_5A_V_OFF_FOR_SLICER                         0x5a
#घोषणा R_5B_FLD_OFF_AND_MSB_FOR_H_AND_V_OFF          0x5b
#घोषणा R_5D_DID                                      0x5d
#घोषणा R_5E_SDID                                     0x5e
#घोषणा R_60_SLICER_STATUS_BYTE_0                     0x60
#घोषणा R_61_SLICER_STATUS_BYTE_1                     0x61
#घोषणा R_62_SLICER_STATUS_BYTE_2                     0x62

/* X port, I port and the scaler part */
	/* Task independent global settings */
#घोषणा R_80_GLOBAL_CNTL_1                            0x80
#घोषणा R_81_V_SYNC_FLD_ID_SRC_SEL_AND_RETIMED_V_F    0x81
#घोषणा R_83_X_PORT_I_O_ENA_AND_OUT_CLK               0x83
#घोषणा R_84_I_PORT_SIGNAL_DEF                        0x84
#घोषणा R_85_I_PORT_SIGNAL_POLAR                      0x85
#घोषणा R_86_I_PORT_FIFO_FLAG_CNTL_AND_ARBIT          0x86
#घोषणा R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED         0x87
#घोषणा R_88_POWER_SAVE_ADC_PORT_CNTL                 0x88
#घोषणा R_8F_STATUS_INFO_SCALER                       0x8f
	/* Task A definition */
		/* Basic settings and acquisition winकरोw definition */
#घोषणा R_90_A_TASK_HANDLING_CNTL                     0x90
#घोषणा R_91_A_X_PORT_FORMATS_AND_CONF                0x91
#घोषणा R_92_A_X_PORT_INPUT_REFERENCE_SIGNAL          0x92
#घोषणा R_93_A_I_PORT_OUTPUT_FORMATS_AND_CONF         0x93
#घोषणा R_94_A_HORIZ_INPUT_WINDOW_START               0x94
#घोषणा R_95_A_HORIZ_INPUT_WINDOW_START_MSB           0x95
#घोषणा R_96_A_HORIZ_INPUT_WINDOW_LENGTH              0x96
#घोषणा R_97_A_HORIZ_INPUT_WINDOW_LENGTH_MSB          0x97
#घोषणा R_98_A_VERT_INPUT_WINDOW_START                0x98
#घोषणा R_99_A_VERT_INPUT_WINDOW_START_MSB            0x99
#घोषणा R_9A_A_VERT_INPUT_WINDOW_LENGTH               0x9a
#घोषणा R_9B_A_VERT_INPUT_WINDOW_LENGTH_MSB           0x9b
#घोषणा R_9C_A_HORIZ_OUTPUT_WINDOW_LENGTH             0x9c
#घोषणा R_9D_A_HORIZ_OUTPUT_WINDOW_LENGTH_MSB         0x9d
#घोषणा R_9E_A_VERT_OUTPUT_WINDOW_LENGTH              0x9e
#घोषणा R_9F_A_VERT_OUTPUT_WINDOW_LENGTH_MSB          0x9f
		/* FIR filtering and prescaling */
#घोषणा R_A0_A_HORIZ_PRESCALING                       0xa0
#घोषणा R_A1_A_ACCUMULATION_LENGTH                    0xa1
#घोषणा R_A2_A_PRESCALER_DC_GAIN_AND_FIR_PREFILTER    0xa2
#घोषणा R_A4_A_LUMA_BRIGHTNESS_CNTL                   0xa4
#घोषणा R_A5_A_LUMA_CONTRAST_CNTL                     0xa5
#घोषणा R_A6_A_CHROMA_SATURATION_CNTL                 0xa6
		/* Horizontal phase scaling */
#घोषणा R_A8_A_HORIZ_LUMA_SCALING_INC                 0xa8
#घोषणा R_A9_A_HORIZ_LUMA_SCALING_INC_MSB             0xa9
#घोषणा R_AA_A_HORIZ_LUMA_PHASE_OFF                   0xaa
#घोषणा R_AC_A_HORIZ_CHROMA_SCALING_INC               0xac
#घोषणा R_AD_A_HORIZ_CHROMA_SCALING_INC_MSB           0xad
#घोषणा R_AE_A_HORIZ_CHROMA_PHASE_OFF                 0xae
#घोषणा R_AF_A_HORIZ_CHROMA_PHASE_OFF_MSB             0xaf
		/* Vertical scaling */
#घोषणा R_B0_A_VERT_LUMA_SCALING_INC                  0xb0
#घोषणा R_B1_A_VERT_LUMA_SCALING_INC_MSB              0xb1
#घोषणा R_B2_A_VERT_CHROMA_SCALING_INC                0xb2
#घोषणा R_B3_A_VERT_CHROMA_SCALING_INC_MSB            0xb3
#घोषणा R_B4_A_VERT_SCALING_MODE_CNTL                 0xb4
#घोषणा R_B8_A_VERT_CHROMA_PHASE_OFF_00               0xb8
#घोषणा R_B9_A_VERT_CHROMA_PHASE_OFF_01               0xb9
#घोषणा R_BA_A_VERT_CHROMA_PHASE_OFF_10               0xba
#घोषणा R_BB_A_VERT_CHROMA_PHASE_OFF_11               0xbb
#घोषणा R_BC_A_VERT_LUMA_PHASE_OFF_00                 0xbc
#घोषणा R_BD_A_VERT_LUMA_PHASE_OFF_01                 0xbd
#घोषणा R_BE_A_VERT_LUMA_PHASE_OFF_10                 0xbe
#घोषणा R_BF_A_VERT_LUMA_PHASE_OFF_11                 0xbf
	/* Task B definition */
		/* Basic settings and acquisition winकरोw definition */
#घोषणा R_C0_B_TASK_HANDLING_CNTL                     0xc0
#घोषणा R_C1_B_X_PORT_FORMATS_AND_CONF                0xc1
#घोषणा R_C2_B_INPUT_REFERENCE_SIGNAL_DEFINITION      0xc2
#घोषणा R_C3_B_I_PORT_FORMATS_AND_CONF                0xc3
#घोषणा R_C4_B_HORIZ_INPUT_WINDOW_START               0xc4
#घोषणा R_C5_B_HORIZ_INPUT_WINDOW_START_MSB           0xc5
#घोषणा R_C6_B_HORIZ_INPUT_WINDOW_LENGTH              0xc6
#घोषणा R_C7_B_HORIZ_INPUT_WINDOW_LENGTH_MSB          0xc7
#घोषणा R_C8_B_VERT_INPUT_WINDOW_START                0xc8
#घोषणा R_C9_B_VERT_INPUT_WINDOW_START_MSB            0xc9
#घोषणा R_CA_B_VERT_INPUT_WINDOW_LENGTH               0xca
#घोषणा R_CB_B_VERT_INPUT_WINDOW_LENGTH_MSB           0xcb
#घोषणा R_CC_B_HORIZ_OUTPUT_WINDOW_LENGTH             0xcc
#घोषणा R_CD_B_HORIZ_OUTPUT_WINDOW_LENGTH_MSB         0xcd
#घोषणा R_CE_B_VERT_OUTPUT_WINDOW_LENGTH              0xce
#घोषणा R_CF_B_VERT_OUTPUT_WINDOW_LENGTH_MSB          0xcf
		/* FIR filtering and prescaling */
#घोषणा R_D0_B_HORIZ_PRESCALING                       0xd0
#घोषणा R_D1_B_ACCUMULATION_LENGTH                    0xd1
#घोषणा R_D2_B_PRESCALER_DC_GAIN_AND_FIR_PREFILTER    0xd2
#घोषणा R_D4_B_LUMA_BRIGHTNESS_CNTL                   0xd4
#घोषणा R_D5_B_LUMA_CONTRAST_CNTL                     0xd5
#घोषणा R_D6_B_CHROMA_SATURATION_CNTL                 0xd6
		/* Horizontal phase scaling */
#घोषणा R_D8_B_HORIZ_LUMA_SCALING_INC                 0xd8
#घोषणा R_D9_B_HORIZ_LUMA_SCALING_INC_MSB             0xd9
#घोषणा R_DA_B_HORIZ_LUMA_PHASE_OFF                   0xda
#घोषणा R_DC_B_HORIZ_CHROMA_SCALING                   0xdc
#घोषणा R_DD_B_HORIZ_CHROMA_SCALING_MSB               0xdd
#घोषणा R_DE_B_HORIZ_PHASE_OFFSET_CRHOMA              0xde
		/* Vertical scaling */
#घोषणा R_E0_B_VERT_LUMA_SCALING_INC                  0xe0
#घोषणा R_E1_B_VERT_LUMA_SCALING_INC_MSB              0xe1
#घोषणा R_E2_B_VERT_CHROMA_SCALING_INC                0xe2
#घोषणा R_E3_B_VERT_CHROMA_SCALING_INC_MSB            0xe3
#घोषणा R_E4_B_VERT_SCALING_MODE_CNTL                 0xe4
#घोषणा R_E8_B_VERT_CHROMA_PHASE_OFF_00               0xe8
#घोषणा R_E9_B_VERT_CHROMA_PHASE_OFF_01               0xe9
#घोषणा R_EA_B_VERT_CHROMA_PHASE_OFF_10               0xea
#घोषणा R_EB_B_VERT_CHROMA_PHASE_OFF_11               0xeb
#घोषणा R_EC_B_VERT_LUMA_PHASE_OFF_00                 0xec
#घोषणा R_ED_B_VERT_LUMA_PHASE_OFF_01                 0xed
#घोषणा R_EE_B_VERT_LUMA_PHASE_OFF_10                 0xee
#घोषणा R_EF_B_VERT_LUMA_PHASE_OFF_11                 0xef

/* second PLL (PLL2) and Pulsegenerator Programming */
#घोषणा R_F0_LFCO_PER_LINE                            0xf0
#घोषणा R_F1_P_I_PARAM_SELECT                         0xf1
#घोषणा R_F2_NOMINAL_PLL2_DTO                         0xf2
#घोषणा R_F3_PLL_INCREMENT                            0xf3
#घोषणा R_F4_PLL2_STATUS                              0xf4
#घोषणा R_F5_PULSGEN_LINE_LENGTH                      0xf5
#घोषणा R_F6_PULSE_A_POS_LSB_AND_PULSEGEN_CONFIG      0xf6
#घोषणा R_F7_PULSE_A_POS_MSB                          0xf7
#घोषणा R_F8_PULSE_B_POS                              0xf8
#घोषणा R_F9_PULSE_B_POS_MSB                          0xf9
#घोषणा R_FA_PULSE_C_POS                              0xfa
#घोषणा R_FB_PULSE_C_POS_MSB                          0xfb
#घोषणा R_FF_S_PLL_MAX_PHASE_ERR_THRESH_NUM_LINES     0xff

/* SAA7113 bit-masks */
#घोषणा SAA7113_R_08_HTC_OFFSET 3
#घोषणा SAA7113_R_08_HTC_MASK (0x3 << SAA7113_R_08_HTC_OFFSET)
#घोषणा SAA7113_R_08_FSEL 0x40
#घोषणा SAA7113_R_08_AUFD 0x80

#घोषणा SAA7113_R_10_VRLN_OFFSET 3
#घोषणा SAA7113_R_10_VRLN_MASK (0x1 << SAA7113_R_10_VRLN_OFFSET)
#घोषणा SAA7113_R_10_OFTS_OFFSET 6
#घोषणा SAA7113_R_10_OFTS_MASK (0x3 << SAA7113_R_10_OFTS_OFFSET)

#घोषणा SAA7113_R_12_RTS0_OFFSET 0
#घोषणा SAA7113_R_12_RTS0_MASK (0xf << SAA7113_R_12_RTS0_OFFSET)
#घोषणा SAA7113_R_12_RTS1_OFFSET 4
#घोषणा SAA7113_R_12_RTS1_MASK (0xf << SAA7113_R_12_RTS1_OFFSET)

#घोषणा SAA7113_R_13_ADLSB_OFFSET 7
#घोषणा SAA7113_R_13_ADLSB_MASK (0x1 << SAA7113_R_13_ADLSB_OFFSET)

#अगर 0
/* Those काष्ठाs will be used in the future क्रम debug purposes */
काष्ठा saa711x_reg_descr अणु
	u8 reg;
	पूर्णांक count;
	अक्षर *name;
पूर्ण;

काष्ठा saa711x_reg_descr saa711x_regs[] = अणु
	/* REG COUNT NAME */
	अणुR_00_CHIP_VERSION,1,
	 "Chip version"पूर्ण,

	/* Video Decoder: R_01_INC_DELAY to R_1F_STATUS_BYTE_2_VD_DEC */

	/* Video Decoder - Frontend part: R_01_INC_DELAY to R_05_INPUT_CNTL_4 */
	अणुR_01_INC_DELAY,1,
	 "Increment delay"पूर्ण,
	अणुR_02_INPUT_CNTL_1,1,
	 "Analog input control 1"पूर्ण,
	अणुR_03_INPUT_CNTL_2,1,
	 "Analog input control 2"पूर्ण,
	अणुR_04_INPUT_CNTL_3,1,
	 "Analog input control 3"पूर्ण,
	अणुR_05_INPUT_CNTL_4,1,
	 "Analog input control 4"पूर्ण,

	/* Video Decoder - Decoder part: R_06_H_SYNC_START to R_1F_STATUS_BYTE_2_VD_DEC */
	अणुR_06_H_SYNC_START,1,
	 "Horizontal sync start"पूर्ण,
	अणुR_07_H_SYNC_STOP,1,
	 "Horizontal sync stop"पूर्ण,
	अणुR_08_SYNC_CNTL,1,
	 "Sync control"पूर्ण,
	अणुR_09_LUMA_CNTL,1,
	 "Luminance control"पूर्ण,
	अणुR_0A_LUMA_BRIGHT_CNTL,1,
	 "Luminance brightness control"पूर्ण,
	अणुR_0B_LUMA_CONTRAST_CNTL,1,
	 "Luminance contrast control"पूर्ण,
	अणुR_0C_CHROMA_SAT_CNTL,1,
	 "Chrominance saturation control"पूर्ण,
	अणुR_0D_CHROMA_HUE_CNTL,1,
	 "Chrominance hue control"पूर्ण,
	अणुR_0E_CHROMA_CNTL_1,1,
	 "Chrominance control 1"पूर्ण,
	अणुR_0F_CHROMA_GAIN_CNTL,1,
	 "Chrominance gain control"पूर्ण,
	अणुR_10_CHROMA_CNTL_2,1,
	 "Chrominance control 2"पूर्ण,
	अणुR_11_MODE_DELAY_CNTL,1,
	 "Mode/delay control"पूर्ण,
	अणुR_12_RT_SIGNAL_CNTL,1,
	 "RT signal control"पूर्ण,
	अणुR_13_RT_X_PORT_OUT_CNTL,1,
	 "RT/X port output control"पूर्ण,
	अणुR_14_ANAL_ADC_COMPAT_CNTL,1,
	 "Analog/ADC/compatibility control"पूर्ण,
	अणुR_15_VGATE_START_FID_CHG,  1,
	 "VGATE start FID change"पूर्ण,
	अणुR_16_VGATE_STOP,1,
	 "VGATE stop"पूर्ण,
	अणुR_17_MISC_VGATE_CONF_AND_MSB,  1,
	 "Miscellaneous VGATE configuration and MSBs"पूर्ण,
	अणुR_18_RAW_DATA_GAIN_CNTL,1,
	 "Raw data gain control",पूर्ण,
	अणुR_19_RAW_DATA_OFF_CNTL,1,
	 "Raw data offset control",पूर्ण,
	अणुR_1A_COLOR_KILL_LVL_CNTL,1,
	 "Color Killer Level Control"पूर्ण,
	अणु R_1B_MISC_TVVCRDET, 1,
	  "MISC /TVVCRDET"पूर्ण,
	अणु R_1C_ENHAN_COMB_CTRL1, 1,
	 "Enhanced comb ctrl1"पूर्ण,
	अणु R_1D_ENHAN_COMB_CTRL2, 1,
	 "Enhanced comb ctrl1"पूर्ण,
	अणुR_1E_STATUS_BYTE_1_VD_DEC,1,
	 "Status byte 1 video decoder"पूर्ण,
	अणुR_1F_STATUS_BYTE_2_VD_DEC,1,
	 "Status byte 2 video decoder"पूर्ण,

	/* Component processing and पूर्णांकerrupt masking part:  0x20h to R_2F_INTERRUPT_MASK_3 */
	/* 0x20 to 0x22 - Reserved */
	अणुR_23_INPUT_CNTL_5,1,
	 "Analog input control 5"पूर्ण,
	अणुR_24_INPUT_CNTL_6,1,
	 "Analog input control 6"पूर्ण,
	अणुR_25_INPUT_CNTL_7,1,
	 "Analog input control 7"पूर्ण,
	/* 0x26 to 0x28 - Reserved */
	अणुR_29_COMP_DELAY,1,
	 "Component delay"पूर्ण,
	अणुR_2A_COMP_BRIGHT_CNTL,1,
	 "Component brightness control"पूर्ण,
	अणुR_2B_COMP_CONTRAST_CNTL,1,
	 "Component contrast control"पूर्ण,
	अणुR_2C_COMP_SAT_CNTL,1,
	 "Component saturation control"पूर्ण,
	अणुR_2D_INTERRUPT_MASK_1,1,
	 "Interrupt mask 1"पूर्ण,
	अणुR_2E_INTERRUPT_MASK_2,1,
	 "Interrupt mask 2"पूर्ण,
	अणुR_2F_INTERRUPT_MASK_3,1,
	 "Interrupt mask 3"पूर्ण,

	/* Audio घड़ी generator part: R_30_AUD_MAST_CLK_CYCLES_PER_FIELD to 0x3f */
	अणुR_30_AUD_MAST_CLK_CYCLES_PER_FIELD,3,
	 "Audio master clock cycles per field"पूर्ण,
	/* 0x33 - Reserved */
	अणुR_34_AUD_MAST_CLK_NOMINAL_INC,3,
	 "Audio master clock nominal increment"पूर्ण,
	/* 0x37 - Reserved */
	अणुR_38_CLK_RATIO_AMXCLK_TO_ASCLK,1,
	 "Clock ratio AMXCLK to ASCLK"पूर्ण,
	अणुR_39_CLK_RATIO_ASCLK_TO_ALRCLK,1,
	 "Clock ratio ASCLK to ALRCLK"पूर्ण,
	अणुR_3A_AUD_CLK_GEN_BASIC_SETUP,1,
	 "Audio clock generator basic setup"पूर्ण,
	/* 0x3b-0x3f - Reserved */

	/* General purpose VBI data slicer part: R_40_SLICER_CNTL_1 to 0x7f */
	अणुR_40_SLICER_CNTL_1,1,
	 "Slicer control 1"पूर्ण,
	अणुR_41_LCR,23,
	 "R_41_LCR"पूर्ण,
	अणुR_58_PROGRAM_FRAMING_CODE,1,
	 "Programmable framing code"पूर्ण,
	अणुR_59_H_OFF_FOR_SLICER,1,
	 "Horizontal offset for slicer"पूर्ण,
	अणुR_5A_V_OFF_FOR_SLICER,1,
	 "Vertical offset for slicer"पूर्ण,
	अणुR_5B_FLD_OFF_AND_MSB_FOR_H_AND_V_OFF,1,
	 "Field offset and MSBs for horizontal and vertical offset"पूर्ण,
	अणुR_5D_DID,1,
	 "Header and data identification (R_5D_DID)"पूर्ण,
	अणुR_5E_SDID,1,
	 "Sliced data identification (R_5E_SDID) code"पूर्ण,
	अणुR_60_SLICER_STATUS_BYTE_0,1,
	 "Slicer status byte 0"पूर्ण,
	अणुR_61_SLICER_STATUS_BYTE_1,1,
	 "Slicer status byte 1"पूर्ण,
	अणुR_62_SLICER_STATUS_BYTE_2,1,
	 "Slicer status byte 2"पूर्ण,
	/* 0x63-0x7f - Reserved */

	/* X port, I port and the scaler part: R_80_GLOBAL_CNTL_1 to R_EF_B_VERT_LUMA_PHASE_OFF_11 */
	/* Task independent global settings: R_80_GLOBAL_CNTL_1 to R_8F_STATUS_INFO_SCALER */
	अणुR_80_GLOBAL_CNTL_1,1,
	 "Global control 1"पूर्ण,
	अणुR_81_V_SYNC_FLD_ID_SRC_SEL_AND_RETIMED_V_F,1,
	 "Vertical sync and Field ID source selection, retimed V and F signals"पूर्ण,
	/* 0x82 - Reserved */
	अणुR_83_X_PORT_I_O_ENA_AND_OUT_CLK,1,
	 "X port I/O enable and output clock"पूर्ण,
	अणुR_84_I_PORT_SIGNAL_DEF,1,
	 "I port signal definitions"पूर्ण,
	अणुR_85_I_PORT_SIGNAL_POLAR,1,
	 "I port signal polarities"पूर्ण,
	अणुR_86_I_PORT_FIFO_FLAG_CNTL_AND_ARBIT,1,
	 "I port FIFO flag control and arbitration"पूर्ण,
	अणुR_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED,  1,
	 "I port I/O enable output clock and gated"पूर्ण,
	अणुR_88_POWER_SAVE_ADC_PORT_CNTL,1,
	 "Power save/ADC port control"पूर्ण,
	/* 089-0x8e - Reserved */
	अणुR_8F_STATUS_INFO_SCALER,1,
	 "Status information scaler part"पूर्ण,

	/* Task A definition: R_90_A_TASK_HANDLING_CNTL to R_BF_A_VERT_LUMA_PHASE_OFF_11 */
	/* Task A: Basic settings and acquisition winकरोw definition */
	अणुR_90_A_TASK_HANDLING_CNTL,1,
	 "Task A: Task handling control"पूर्ण,
	अणुR_91_A_X_PORT_FORMATS_AND_CONF,1,
	 "Task A: X port formats and configuration"पूर्ण,
	अणुR_92_A_X_PORT_INPUT_REFERENCE_SIGNAL,1,
	 "Task A: X port input reference signal definition"पूर्ण,
	अणुR_93_A_I_PORT_OUTPUT_FORMATS_AND_CONF,1,
	 "Task A: I port output formats and configuration"पूर्ण,
	अणुR_94_A_HORIZ_INPUT_WINDOW_START,2,
	 "Task A: Horizontal input window start"पूर्ण,
	अणुR_96_A_HORIZ_INPUT_WINDOW_LENGTH,2,
	 "Task A: Horizontal input window length"पूर्ण,
	अणुR_98_A_VERT_INPUT_WINDOW_START,2,
	 "Task A: Vertical input window start"पूर्ण,
	अणुR_9A_A_VERT_INPUT_WINDOW_LENGTH,2,
	 "Task A: Vertical input window length"पूर्ण,
	अणुR_9C_A_HORIZ_OUTPUT_WINDOW_LENGTH,2,
	 "Task A: Horizontal output window length"पूर्ण,
	अणुR_9E_A_VERT_OUTPUT_WINDOW_LENGTH,2,
	 "Task A: Vertical output window length"पूर्ण,

	/* Task A: FIR filtering and prescaling */
	अणुR_A0_A_HORIZ_PRESCALING,1,
	 "Task A: Horizontal prescaling"पूर्ण,
	अणुR_A1_A_ACCUMULATION_LENGTH,1,
	 "Task A: Accumulation length"पूर्ण,
	अणुR_A2_A_PRESCALER_DC_GAIN_AND_FIR_PREFILTER,1,
	 "Task A: Prescaler DC gain and FIR prefilter"पूर्ण,
	/* 0xa3 - Reserved */
	अणुR_A4_A_LUMA_BRIGHTNESS_CNTL,1,
	 "Task A: Luminance brightness control"पूर्ण,
	अणुR_A5_A_LUMA_CONTRAST_CNTL,1,
	 "Task A: Luminance contrast control"पूर्ण,
	अणुR_A6_A_CHROMA_SATURATION_CNTL,1,
	 "Task A: Chrominance saturation control"पूर्ण,
	/* 0xa7 - Reserved */

	/* Task A: Horizontal phase scaling */
	अणुR_A8_A_HORIZ_LUMA_SCALING_INC,2,
	 "Task A: Horizontal luminance scaling increment"पूर्ण,
	अणुR_AA_A_HORIZ_LUMA_PHASE_OFF,1,
	 "Task A: Horizontal luminance phase offset"पूर्ण,
	/* 0xab - Reserved */
	अणुR_AC_A_HORIZ_CHROMA_SCALING_INC,2,
	 "Task A: Horizontal chrominance scaling increment"पूर्ण,
	अणुR_AE_A_HORIZ_CHROMA_PHASE_OFF,1,
	 "Task A: Horizontal chrominance phase offset"पूर्ण,
	/* 0xaf - Reserved */

	/* Task A: Vertical scaling */
	अणुR_B0_A_VERT_LUMA_SCALING_INC,2,
	 "Task A: Vertical luminance scaling increment"पूर्ण,
	अणुR_B2_A_VERT_CHROMA_SCALING_INC,2,
	 "Task A: Vertical chrominance scaling increment"पूर्ण,
	अणुR_B4_A_VERT_SCALING_MODE_CNTL,1,
	 "Task A: Vertical scaling mode control"पूर्ण,
	/* 0xb5-0xb7 - Reserved */
	अणुR_B8_A_VERT_CHROMA_PHASE_OFF_00,1,
	 "Task A: Vertical chrominance phase offset '00'"पूर्ण,
	अणुR_B9_A_VERT_CHROMA_PHASE_OFF_01,1,
	 "Task A: Vertical chrominance phase offset '01'"पूर्ण,
	अणुR_BA_A_VERT_CHROMA_PHASE_OFF_10,1,
	 "Task A: Vertical chrominance phase offset '10'"पूर्ण,
	अणुR_BB_A_VERT_CHROMA_PHASE_OFF_11,1,
	 "Task A: Vertical chrominance phase offset '11'"पूर्ण,
	अणुR_BC_A_VERT_LUMA_PHASE_OFF_00,1,
	 "Task A: Vertical luminance phase offset '00'"पूर्ण,
	अणुR_BD_A_VERT_LUMA_PHASE_OFF_01,1,
	 "Task A: Vertical luminance phase offset '01'"पूर्ण,
	अणुR_BE_A_VERT_LUMA_PHASE_OFF_10,1,
	 "Task A: Vertical luminance phase offset '10'"पूर्ण,
	अणुR_BF_A_VERT_LUMA_PHASE_OFF_11,1,
	 "Task A: Vertical luminance phase offset '11'"पूर्ण,

	/* Task B definition: R_C0_B_TASK_HANDLING_CNTL to R_EF_B_VERT_LUMA_PHASE_OFF_11 */
	/* Task B: Basic settings and acquisition winकरोw definition */
	अणुR_C0_B_TASK_HANDLING_CNTL,1,
	 "Task B: Task handling control"पूर्ण,
	अणुR_C1_B_X_PORT_FORMATS_AND_CONF,1,
	 "Task B: X port formats and configuration"पूर्ण,
	अणुR_C2_B_INPUT_REFERENCE_SIGNAL_DEFINITION,1,
	 "Task B: Input reference signal definition"पूर्ण,
	अणुR_C3_B_I_PORT_FORMATS_AND_CONF,1,
	 "Task B: I port formats and configuration"पूर्ण,
	अणुR_C4_B_HORIZ_INPUT_WINDOW_START,2,
	 "Task B: Horizontal input window start"पूर्ण,
	अणुR_C6_B_HORIZ_INPUT_WINDOW_LENGTH,2,
	 "Task B: Horizontal input window length"पूर्ण,
	अणुR_C8_B_VERT_INPUT_WINDOW_START,2,
	 "Task B: Vertical input window start"पूर्ण,
	अणुR_CA_B_VERT_INPUT_WINDOW_LENGTH,2,
	 "Task B: Vertical input window length"पूर्ण,
	अणुR_CC_B_HORIZ_OUTPUT_WINDOW_LENGTH,2,
	 "Task B: Horizontal output window length"पूर्ण,
	अणुR_CE_B_VERT_OUTPUT_WINDOW_LENGTH,2,
	 "Task B: Vertical output window length"पूर्ण,

	/* Task B: FIR filtering and prescaling */
	अणुR_D0_B_HORIZ_PRESCALING,1,
	 "Task B: Horizontal prescaling"पूर्ण,
	अणुR_D1_B_ACCUMULATION_LENGTH,1,
	 "Task B: Accumulation length"पूर्ण,
	अणुR_D2_B_PRESCALER_DC_GAIN_AND_FIR_PREFILTER,1,
	 "Task B: Prescaler DC gain and FIR prefilter"पूर्ण,
	/* 0xd3 - Reserved */
	अणुR_D4_B_LUMA_BRIGHTNESS_CNTL,1,
	 "Task B: Luminance brightness control"पूर्ण,
	अणुR_D5_B_LUMA_CONTRAST_CNTL,1,
	 "Task B: Luminance contrast control"पूर्ण,
	अणुR_D6_B_CHROMA_SATURATION_CNTL,1,
	 "Task B: Chrominance saturation control"पूर्ण,
	/* 0xd7 - Reserved */

	/* Task B: Horizontal phase scaling */
	अणुR_D8_B_HORIZ_LUMA_SCALING_INC,2,
	 "Task B: Horizontal luminance scaling increment"पूर्ण,
	अणुR_DA_B_HORIZ_LUMA_PHASE_OFF,1,
	 "Task B: Horizontal luminance phase offset"पूर्ण,
	/* 0xdb - Reserved */
	अणुR_DC_B_HORIZ_CHROMA_SCALING,2,
	 "Task B: Horizontal chrominance scaling"पूर्ण,
	अणुR_DE_B_HORIZ_PHASE_OFFSET_CRHOMA,1,
	 "Task B: Horizontal Phase Offset Chroma"पूर्ण,
	/* 0xdf - Reserved */

	/* Task B: Vertical scaling */
	अणुR_E0_B_VERT_LUMA_SCALING_INC,2,
	 "Task B: Vertical luminance scaling increment"पूर्ण,
	अणुR_E2_B_VERT_CHROMA_SCALING_INC,2,
	 "Task B: Vertical chrominance scaling increment"पूर्ण,
	अणुR_E4_B_VERT_SCALING_MODE_CNTL,1,
	 "Task B: Vertical scaling mode control"पूर्ण,
	/* 0xe5-0xe7 - Reserved */
	अणुR_E8_B_VERT_CHROMA_PHASE_OFF_00,1,
	 "Task B: Vertical chrominance phase offset '00'"पूर्ण,
	अणुR_E9_B_VERT_CHROMA_PHASE_OFF_01,1,
	 "Task B: Vertical chrominance phase offset '01'"पूर्ण,
	अणुR_EA_B_VERT_CHROMA_PHASE_OFF_10,1,
	 "Task B: Vertical chrominance phase offset '10'"पूर्ण,
	अणुR_EB_B_VERT_CHROMA_PHASE_OFF_11,1,
	 "Task B: Vertical chrominance phase offset '11'"पूर्ण,
	अणुR_EC_B_VERT_LUMA_PHASE_OFF_00,1,
	 "Task B: Vertical luminance phase offset '00'"पूर्ण,
	अणुR_ED_B_VERT_LUMA_PHASE_OFF_01,1,
	 "Task B: Vertical luminance phase offset '01'"पूर्ण,
	अणुR_EE_B_VERT_LUMA_PHASE_OFF_10,1,
	 "Task B: Vertical luminance phase offset '10'"पूर्ण,
	अणुR_EF_B_VERT_LUMA_PHASE_OFF_11,1,
	 "Task B: Vertical luminance phase offset '11'"पूर्ण,

	/* second PLL (PLL2) and Pulsegenerator Programming */
	अणु R_F0_LFCO_PER_LINE, 1,
	  "LFCO's per line"पूर्ण,
	अणु R_F1_P_I_PARAM_SELECT,1,
	  "P-/I- Param. Select., PLL Mode, PLL H-Src., LFCO's per line"पूर्ण,
	अणु R_F2_NOMINAL_PLL2_DTO,1,
	 "Nominal PLL2 DTO"पूर्ण,
	अणुR_F3_PLL_INCREMENT,1,
	 "PLL2 Increment"पूर्ण,
	अणुR_F4_PLL2_STATUS,1,
	 "PLL2 Status"पूर्ण,
	अणुR_F5_PULSGEN_LINE_LENGTH,1,
	 "Pulsgen. line length"पूर्ण,
	अणुR_F6_PULSE_A_POS_LSB_AND_PULSEGEN_CONFIG,1,
	 "Pulse A Position, Pulsgen Resync., Pulsgen. H-Src., Pulsgen. line length"पूर्ण,
	अणुR_F7_PULSE_A_POS_MSB,1,
	 "Pulse A Position"पूर्ण,
	अणुR_F8_PULSE_B_POS,2,
	 "Pulse B Position"पूर्ण,
	अणुR_FA_PULSE_C_POS,2,
	 "Pulse C Position"पूर्ण,
	/* 0xfc to 0xfe - Reserved */
	अणुR_FF_S_PLL_MAX_PHASE_ERR_THRESH_NUM_LINES,1,
	 "S_PLL max. phase, error threshold, PLL2 no. of lines, threshold"पूर्ण,
पूर्ण;
#पूर्ण_अगर
