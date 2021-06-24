<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ATI Mach64 Register Definitions
 *
 * Copyright (C) 1997 Michael AK Tesch
 *  written with much help from Jon Howell
 *
 * Updated क्रम 3D RAGE PRO and 3D RAGE Mobility by Geert Uytterhoeven
 */

/*
 * most of the rest of this file comes from ATI sample code
 */
#अगर_अघोषित REGMACH64_H
#घोषणा REGMACH64_H

/* NON-GUI MEMORY MAPPED Registers - expressed in BYTE offsets */

/* Accelerator CRTC */
#घोषणा CRTC_H_TOTAL_DISP	0x0000	/* Dword offset 0_00 */
#घोषणा CRTC2_H_TOTAL_DISP	0x0000	/* Dword offset 0_00 */
#घोषणा CRTC_H_SYNC_STRT_WID	0x0004	/* Dword offset 0_01 */
#घोषणा CRTC2_H_SYNC_STRT_WID	0x0004	/* Dword offset 0_01 */
#घोषणा CRTC_H_SYNC_STRT	0x0004
#घोषणा CRTC2_H_SYNC_STRT	0x0004
#घोषणा CRTC_H_SYNC_DLY		0x0005
#घोषणा CRTC2_H_SYNC_DLY	0x0005
#घोषणा CRTC_H_SYNC_WID		0x0006
#घोषणा CRTC2_H_SYNC_WID	0x0006
#घोषणा CRTC_V_TOTAL_DISP	0x0008	/* Dword offset 0_02 */
#घोषणा CRTC2_V_TOTAL_DISP	0x0008	/* Dword offset 0_02 */
#घोषणा CRTC_V_TOTAL		0x0008
#घोषणा CRTC2_V_TOTAL		0x0008
#घोषणा CRTC_V_DISP		0x000A
#घोषणा CRTC2_V_DISP		0x000A
#घोषणा CRTC_V_SYNC_STRT_WID	0x000C	/* Dword offset 0_03 */
#घोषणा CRTC2_V_SYNC_STRT_WID	0x000C	/* Dword offset 0_03 */
#घोषणा CRTC_V_SYNC_STRT	0x000C
#घोषणा CRTC2_V_SYNC_STRT	0x000C
#घोषणा CRTC_V_SYNC_WID		0x000E
#घोषणा CRTC2_V_SYNC_WID	0x000E
#घोषणा CRTC_VLINE_CRNT_VLINE	0x0010	/* Dword offset 0_04 */
#घोषणा CRTC2_VLINE_CRNT_VLINE	0x0010	/* Dword offset 0_04 */
#घोषणा CRTC_OFF_PITCH		0x0014	/* Dword offset 0_05 */
#घोषणा CRTC_OFFSET		0x0014
#घोषणा CRTC_PITCH		0x0016
#घोषणा CRTC_INT_CNTL		0x0018	/* Dword offset 0_06 */
#घोषणा CRTC_GEN_CNTL		0x001C	/* Dword offset 0_07 */
#घोषणा CRTC_PIX_WIDTH		0x001D
#घोषणा CRTC_FIFO		0x001E
#घोषणा CRTC_EXT_DISP		0x001F

/* Memory Buffer Control */
#घोषणा DSP_CONFIG		0x0020	/* Dword offset 0_08 */
#घोषणा PM_DSP_CONFIG		0x0020	/* Dword offset 0_08 (Mobility Only) */
#घोषणा DSP_ON_OFF		0x0024	/* Dword offset 0_09 */
#घोषणा PM_DSP_ON_OFF		0x0024	/* Dword offset 0_09 (Mobility Only) */
#घोषणा TIMER_CONFIG		0x0028	/* Dword offset 0_0A */
#घोषणा MEM_BUF_CNTL		0x002C	/* Dword offset 0_0B */
#घोषणा MEM_ADDR_CONFIG		0x0034	/* Dword offset 0_0D */

/* Accelerator CRTC */
#घोषणा CRT_TRAP		0x0038	/* Dword offset 0_0E */

#घोषणा I2C_CNTL_0		0x003C	/* Dword offset 0_0F */

#घोषणा DSTN_CONTROL_LG		0x003C	/* Dword offset 0_0F (LG) */

/* Overscan */
#घोषणा OVR_CLR			0x0040	/* Dword offset 0_10 */
#घोषणा OVR2_CLR		0x0040	/* Dword offset 0_10 */
#घोषणा OVR_WID_LEFT_RIGHT	0x0044	/* Dword offset 0_11 */
#घोषणा OVR2_WID_LEFT_RIGHT	0x0044	/* Dword offset 0_11 */
#घोषणा OVR_WID_TOP_BOTTOM	0x0048	/* Dword offset 0_12 */
#घोषणा OVR2_WID_TOP_BOTTOM	0x0048	/* Dword offset 0_12 */

/* Memory Buffer Control */
#घोषणा VGA_DSP_CONFIG		0x004C	/* Dword offset 0_13 */
#घोषणा PM_VGA_DSP_CONFIG	0x004C	/* Dword offset 0_13 (Mobility Only) */
#घोषणा VGA_DSP_ON_OFF		0x0050	/* Dword offset 0_14 */
#घोषणा PM_VGA_DSP_ON_OFF	0x0050	/* Dword offset 0_14 (Mobility Only) */
#घोषणा DSP2_CONFIG		0x0054	/* Dword offset 0_15 */
#घोषणा PM_DSP2_CONFIG		0x0054	/* Dword offset 0_15 (Mobility Only) */
#घोषणा DSP2_ON_OFF		0x0058	/* Dword offset 0_16 */
#घोषणा PM_DSP2_ON_OFF		0x0058	/* Dword offset 0_16 (Mobility Only) */

/* Accelerator CRTC */
#घोषणा CRTC2_OFF_PITCH		0x005C	/* Dword offset 0_17 */

/* Hardware Cursor */
#घोषणा CUR_CLR0		0x0060	/* Dword offset 0_18 */
#घोषणा CUR2_CLR0		0x0060	/* Dword offset 0_18 */
#घोषणा CUR_CLR1		0x0064	/* Dword offset 0_19 */
#घोषणा CUR2_CLR1		0x0064	/* Dword offset 0_19 */
#घोषणा CUR_OFFSET		0x0068	/* Dword offset 0_1A */
#घोषणा CUR2_OFFSET		0x0068	/* Dword offset 0_1A */
#घोषणा CUR_HORZ_VERT_POSN	0x006C	/* Dword offset 0_1B */
#घोषणा CUR2_HORZ_VERT_POSN	0x006C	/* Dword offset 0_1B */
#घोषणा CUR_HORZ_VERT_OFF	0x0070	/* Dword offset 0_1C */
#घोषणा CUR2_HORZ_VERT_OFF	0x0070	/* Dword offset 0_1C */

#घोषणा CNFG_PANEL_LG		0x0074	/* Dword offset 0_1D (LG) */

/* General I/O Control */
#घोषणा GP_IO			0x0078	/* Dword offset 0_1E */

/* Test and Debug */
#घोषणा HW_DEBUG		0x007C	/* Dword offset 0_1F */

/* Scratch Pad and Test */
#घोषणा SCRATCH_REG0		0x0080	/* Dword offset 0_20 */
#घोषणा SCRATCH_REG1		0x0084	/* Dword offset 0_21 */
#घोषणा SCRATCH_REG2		0x0088	/* Dword offset 0_22 */
#घोषणा SCRATCH_REG3		0x008C	/* Dword offset 0_23 */

/* Clock Control */
#घोषणा CLOCK_CNTL			0x0090	/* Dword offset 0_24 */
/* CLOCK_CNTL रेजिस्टर स्थिरants CT LAYOUT */
#घोषणा CLOCK_SEL			0x0f
#घोषणा CLOCK_SEL_INTERNAL		0x03
#घोषणा CLOCK_SEL_EXTERNAL		0x0c
#घोषणा CLOCK_DIV			0x30
#घोषणा CLOCK_DIV1			0x00
#घोषणा CLOCK_DIV2			0x10
#घोषणा CLOCK_DIV4			0x20
#घोषणा CLOCK_STROBE			0x40
/*  ?					0x80 */
/* CLOCK_CNTL रेजिस्टर स्थिरants GX LAYOUT */
#घोषणा CLOCK_BIT			0x04	/* For ICS2595 */
#घोषणा CLOCK_PULSE			0x08	/* For ICS2595 */
/*#घोषणा CLOCK_STROBE			0x40 dito as CT */
#घोषणा CLOCK_DATA			0x80

/* For पूर्णांकernal PLL(CT) start */
#घोषणा CLOCK_CNTL_ADDR			CLOCK_CNTL + 1
#घोषणा PLL_WR_EN			0x02
#घोषणा PLL_ADDR			0xfc
#घोषणा CLOCK_CNTL_DATA			CLOCK_CNTL + 2
#घोषणा PLL_DATA			0xff
/* For पूर्णांकernal PLL(CT) end */

#घोषणा CLOCK_SEL_CNTL		0x0090	/* Dword offset 0_24 */

/* Configuration */
#घोषणा CNFG_STAT1		0x0094	/* Dword offset 0_25 */
#घोषणा CNFG_STAT2		0x0098	/* Dword offset 0_26 */

/* Bus Control */
#घोषणा BUS_CNTL		0x00A0	/* Dword offset 0_28 */

#घोषणा LCD_INDEX		0x00A4	/* Dword offset 0_29 */
#घोषणा LCD_DATA		0x00A8	/* Dword offset 0_2A */

#घोषणा HFB_PITCH_ADDR_LG	0x00A8	/* Dword offset 0_2A (LG) */

/* Memory Control */
#घोषणा EXT_MEM_CNTL		0x00AC	/* Dword offset 0_2B */
#घोषणा MEM_CNTL		0x00B0	/* Dword offset 0_2C */
#घोषणा MEM_VGA_WP_SEL		0x00B4	/* Dword offset 0_2D */
#घोषणा MEM_VGA_RP_SEL		0x00B8	/* Dword offset 0_2E */

#घोषणा I2C_CNTL_1		0x00BC	/* Dword offset 0_2F */

#घोषणा LT_GIO_LG		0x00BC	/* Dword offset 0_2F (LG) */

/* DAC Control */
#घोषणा DAC_REGS		0x00C0	/* Dword offset 0_30 */
#घोषणा DAC_W_INDEX		0x00C0	/* Dword offset 0_30 */
#घोषणा DAC_DATA		0x00C1	/* Dword offset 0_30 */
#घोषणा DAC_MASK		0x00C2	/* Dword offset 0_30 */
#घोषणा DAC_R_INDEX		0x00C3	/* Dword offset 0_30 */
#घोषणा DAC_CNTL		0x00C4	/* Dword offset 0_31 */

#घोषणा EXT_DAC_REGS		0x00C8	/* Dword offset 0_32 */

#घोषणा HORZ_STRETCHING_LG	0x00C8	/* Dword offset 0_32 (LG) */
#घोषणा VERT_STRETCHING_LG	0x00CC	/* Dword offset 0_33 (LG) */

/* Test and Debug */
#घोषणा GEN_TEST_CNTL		0x00D0	/* Dword offset 0_34 */

/* Custom Macros */
#घोषणा CUSTOM_MACRO_CNTL	0x00D4	/* Dword offset 0_35 */

#घोषणा LCD_GEN_CNTL_LG		0x00D4	/* Dword offset 0_35 (LG) */
#घोषणा POWER_MANAGEMENT_LG	0x00D8	/* Dword offset 0_36 (LG) */

/* Configuration */
#घोषणा CNFG_CNTL		0x00DC	/* Dword offset 0_37 (CT, ET, VT) */
#घोषणा CNFG_CHIP_ID		0x00E0	/* Dword offset 0_38 */
#घोषणा CNFG_STAT0		0x00E4	/* Dword offset 0_39 */

/* Test and Debug */
#घोषणा CRC_SIG			0x00E8	/* Dword offset 0_3A */
#घोषणा CRC2_SIG		0x00E8	/* Dword offset 0_3A */


/* GUI MEMORY MAPPED Registers */

/* Draw Engine Destination Trajectory */
#घोषणा DST_OFF_PITCH		0x0100	/* Dword offset 0_40 */
#घोषणा DST_X			0x0104	/* Dword offset 0_41 */
#घोषणा DST_Y			0x0108	/* Dword offset 0_42 */
#घोषणा DST_Y_X			0x010C	/* Dword offset 0_43 */
#घोषणा DST_WIDTH		0x0110	/* Dword offset 0_44 */
#घोषणा DST_HEIGHT		0x0114	/* Dword offset 0_45 */
#घोषणा DST_HEIGHT_WIDTH	0x0118	/* Dword offset 0_46 */
#घोषणा DST_X_WIDTH		0x011C	/* Dword offset 0_47 */
#घोषणा DST_BRES_LNTH		0x0120	/* Dword offset 0_48 */
#घोषणा DST_BRES_ERR		0x0124	/* Dword offset 0_49 */
#घोषणा DST_BRES_INC		0x0128	/* Dword offset 0_4A */
#घोषणा DST_BRES_DEC		0x012C	/* Dword offset 0_4B */
#घोषणा DST_CNTL		0x0130	/* Dword offset 0_4C */
#घोषणा DST_Y_X__ALIAS__	0x0134	/* Dword offset 0_4D */
#घोषणा TRAIL_BRES_ERR		0x0138	/* Dword offset 0_4E */
#घोषणा TRAIL_BRES_INC		0x013C	/* Dword offset 0_4F */
#घोषणा TRAIL_BRES_DEC		0x0140	/* Dword offset 0_50 */
#घोषणा LEAD_BRES_LNTH		0x0144	/* Dword offset 0_51 */
#घोषणा Z_OFF_PITCH		0x0148	/* Dword offset 0_52 */
#घोषणा Z_CNTL			0x014C	/* Dword offset 0_53 */
#घोषणा ALPHA_TST_CNTL		0x0150	/* Dword offset 0_54 */
#घोषणा SECONDARY_STW_EXP	0x0158	/* Dword offset 0_56 */
#घोषणा SECONDARY_S_X_INC	0x015C	/* Dword offset 0_57 */
#घोषणा SECONDARY_S_Y_INC	0x0160	/* Dword offset 0_58 */
#घोषणा SECONDARY_S_START	0x0164	/* Dword offset 0_59 */
#घोषणा SECONDARY_W_X_INC	0x0168	/* Dword offset 0_5A */
#घोषणा SECONDARY_W_Y_INC	0x016C	/* Dword offset 0_5B */
#घोषणा SECONDARY_W_START	0x0170	/* Dword offset 0_5C */
#घोषणा SECONDARY_T_X_INC	0x0174	/* Dword offset 0_5D */
#घोषणा SECONDARY_T_Y_INC	0x0178	/* Dword offset 0_5E */
#घोषणा SECONDARY_T_START	0x017C	/* Dword offset 0_5F */

/* Draw Engine Source Trajectory */
#घोषणा SRC_OFF_PITCH		0x0180	/* Dword offset 0_60 */
#घोषणा SRC_X			0x0184	/* Dword offset 0_61 */
#घोषणा SRC_Y			0x0188	/* Dword offset 0_62 */
#घोषणा SRC_Y_X			0x018C	/* Dword offset 0_63 */
#घोषणा SRC_WIDTH1		0x0190	/* Dword offset 0_64 */
#घोषणा SRC_HEIGHT1		0x0194	/* Dword offset 0_65 */
#घोषणा SRC_HEIGHT1_WIDTH1	0x0198	/* Dword offset 0_66 */
#घोषणा SRC_X_START		0x019C	/* Dword offset 0_67 */
#घोषणा SRC_Y_START		0x01A0	/* Dword offset 0_68 */
#घोषणा SRC_Y_X_START		0x01A4	/* Dword offset 0_69 */
#घोषणा SRC_WIDTH2		0x01A8	/* Dword offset 0_6A */
#घोषणा SRC_HEIGHT2		0x01AC	/* Dword offset 0_6B */
#घोषणा SRC_HEIGHT2_WIDTH2	0x01B0	/* Dword offset 0_6C */
#घोषणा SRC_CNTL		0x01B4	/* Dword offset 0_6D */

#घोषणा SCALE_OFF		0x01C0	/* Dword offset 0_70 */
#घोषणा SECONDARY_SCALE_OFF	0x01C4	/* Dword offset 0_71 */

#घोषणा TEX_0_OFF		0x01C0	/* Dword offset 0_70 */
#घोषणा TEX_1_OFF		0x01C4	/* Dword offset 0_71 */
#घोषणा TEX_2_OFF		0x01C8	/* Dword offset 0_72 */
#घोषणा TEX_3_OFF		0x01CC	/* Dword offset 0_73 */
#घोषणा TEX_4_OFF		0x01D0	/* Dword offset 0_74 */
#घोषणा TEX_5_OFF		0x01D4	/* Dword offset 0_75 */
#घोषणा TEX_6_OFF		0x01D8	/* Dword offset 0_76 */
#घोषणा TEX_7_OFF		0x01DC	/* Dword offset 0_77 */

#घोषणा SCALE_WIDTH		0x01DC	/* Dword offset 0_77 */
#घोषणा SCALE_HEIGHT		0x01E0	/* Dword offset 0_78 */

#घोषणा TEX_8_OFF		0x01E0	/* Dword offset 0_78 */
#घोषणा TEX_9_OFF		0x01E4	/* Dword offset 0_79 */
#घोषणा TEX_10_OFF		0x01E8	/* Dword offset 0_7A */
#घोषणा S_Y_INC			0x01EC	/* Dword offset 0_7B */

#घोषणा SCALE_PITCH		0x01EC	/* Dword offset 0_7B */
#घोषणा SCALE_X_INC		0x01F0	/* Dword offset 0_7C */

#घोषणा RED_X_INC		0x01F0	/* Dword offset 0_7C */
#घोषणा GREEN_X_INC		0x01F4	/* Dword offset 0_7D */

#घोषणा SCALE_Y_INC		0x01F4	/* Dword offset 0_7D */
#घोषणा SCALE_VACC		0x01F8	/* Dword offset 0_7E */
#घोषणा SCALE_3D_CNTL		0x01FC	/* Dword offset 0_7F */

/* Host Data */
#घोषणा HOST_DATA0		0x0200	/* Dword offset 0_80 */
#घोषणा HOST_DATA1		0x0204	/* Dword offset 0_81 */
#घोषणा HOST_DATA2		0x0208	/* Dword offset 0_82 */
#घोषणा HOST_DATA3		0x020C	/* Dword offset 0_83 */
#घोषणा HOST_DATA4		0x0210	/* Dword offset 0_84 */
#घोषणा HOST_DATA5		0x0214	/* Dword offset 0_85 */
#घोषणा HOST_DATA6		0x0218	/* Dword offset 0_86 */
#घोषणा HOST_DATA7		0x021C	/* Dword offset 0_87 */
#घोषणा HOST_DATA8		0x0220	/* Dword offset 0_88 */
#घोषणा HOST_DATA9		0x0224	/* Dword offset 0_89 */
#घोषणा HOST_DATAA		0x0228	/* Dword offset 0_8A */
#घोषणा HOST_DATAB		0x022C	/* Dword offset 0_8B */
#घोषणा HOST_DATAC		0x0230	/* Dword offset 0_8C */
#घोषणा HOST_DATAD		0x0234	/* Dword offset 0_8D */
#घोषणा HOST_DATAE		0x0238	/* Dword offset 0_8E */
#घोषणा HOST_DATAF		0x023C	/* Dword offset 0_8F */
#घोषणा HOST_CNTL		0x0240	/* Dword offset 0_90 */

/* GUI Bus Mastering */
#घोषणा BM_HOSTDATA		0x0244	/* Dword offset 0_91 */
#घोषणा BM_ADDR			0x0248	/* Dword offset 0_92 */
#घोषणा BM_DATA			0x0248	/* Dword offset 0_92 */
#घोषणा BM_GUI_TABLE_CMD	0x024C	/* Dword offset 0_93 */

/* Pattern */
#घोषणा PAT_REG0		0x0280	/* Dword offset 0_A0 */
#घोषणा PAT_REG1		0x0284	/* Dword offset 0_A1 */
#घोषणा PAT_CNTL		0x0288	/* Dword offset 0_A2 */

/* Scissors */
#घोषणा SC_LEFT			0x02A0	/* Dword offset 0_A8 */
#घोषणा SC_RIGHT		0x02A4	/* Dword offset 0_A9 */
#घोषणा SC_LEFT_RIGHT		0x02A8	/* Dword offset 0_AA */
#घोषणा SC_TOP			0x02AC	/* Dword offset 0_AB */
#घोषणा SC_BOTTOM		0x02B0	/* Dword offset 0_AC */
#घोषणा SC_TOP_BOTTOM		0x02B4	/* Dword offset 0_AD */

/* Data Path */
#घोषणा USR1_DST_OFF_PITCH	0x02B8	/* Dword offset 0_AE */
#घोषणा USR2_DST_OFF_PITCH	0x02BC	/* Dword offset 0_AF */
#घोषणा DP_BKGD_CLR		0x02C0	/* Dword offset 0_B0 */
#घोषणा DP_FOG_CLR		0x02C4	/* Dword offset 0_B1 */
#घोषणा DP_FRGD_CLR		0x02C4	/* Dword offset 0_B1 */
#घोषणा DP_WRITE_MASK		0x02C8	/* Dword offset 0_B2 */
#घोषणा DP_CHAIN_MASK		0x02CC	/* Dword offset 0_B3 */
#घोषणा DP_PIX_WIDTH		0x02D0	/* Dword offset 0_B4 */
#घोषणा DP_MIX			0x02D4	/* Dword offset 0_B5 */
#घोषणा DP_SRC			0x02D8	/* Dword offset 0_B6 */
#घोषणा DP_FRGD_CLR_MIX		0x02DC	/* Dword offset 0_B7 */
#घोषणा DP_FRGD_BKGD_CLR	0x02E0	/* Dword offset 0_B8 */

/* Draw Engine Destination Trajectory */
#घोषणा DST_X_Y			0x02E8	/* Dword offset 0_BA */
#घोषणा DST_WIDTH_HEIGHT	0x02EC	/* Dword offset 0_BB */

/* Data Path */
#घोषणा USR_DST_PICTH		0x02F0	/* Dword offset 0_BC */
#घोषणा DP_SET_GUI_ENGINE2	0x02F8	/* Dword offset 0_BE */
#घोषणा DP_SET_GUI_ENGINE	0x02FC	/* Dword offset 0_BF */

/* Color Compare */
#घोषणा CLR_CMP_CLR		0x0300	/* Dword offset 0_C0 */
#घोषणा CLR_CMP_MASK		0x0304	/* Dword offset 0_C1 */
#घोषणा CLR_CMP_CNTL		0x0308	/* Dword offset 0_C2 */

/* Command FIFO */
#घोषणा FIFO_STAT		0x0310	/* Dword offset 0_C4 */

#घोषणा CONTEXT_MASK		0x0320	/* Dword offset 0_C8 */
#घोषणा CONTEXT_LOAD_CNTL	0x032C	/* Dword offset 0_CB */

/* Engine Control */
#घोषणा GUI_TRAJ_CNTL		0x0330	/* Dword offset 0_CC */

/* Engine Status/FIFO */
#घोषणा GUI_STAT		0x0338	/* Dword offset 0_CE */

#घोषणा TEX_PALETTE_INDEX	0x0340	/* Dword offset 0_D0 */
#घोषणा STW_EXP			0x0344	/* Dword offset 0_D1 */
#घोषणा LOG_MAX_INC		0x0348	/* Dword offset 0_D2 */
#घोषणा S_X_INC			0x034C	/* Dword offset 0_D3 */
#घोषणा S_Y_INC__ALIAS__	0x0350	/* Dword offset 0_D4 */

#घोषणा SCALE_PITCH__ALIAS__	0x0350	/* Dword offset 0_D4 */

#घोषणा S_START			0x0354	/* Dword offset 0_D5 */
#घोषणा W_X_INC			0x0358	/* Dword offset 0_D6 */
#घोषणा W_Y_INC			0x035C	/* Dword offset 0_D7 */
#घोषणा W_START			0x0360	/* Dword offset 0_D8 */
#घोषणा T_X_INC			0x0364	/* Dword offset 0_D9 */
#घोषणा T_Y_INC			0x0368	/* Dword offset 0_DA */

#घोषणा SECONDARY_SCALE_PITCH	0x0368	/* Dword offset 0_DA */

#घोषणा T_START			0x036C	/* Dword offset 0_DB */
#घोषणा TEX_SIZE_PITCH		0x0370	/* Dword offset 0_DC */
#घोषणा TEX_CNTL		0x0374	/* Dword offset 0_DD */
#घोषणा SECONDARY_TEX_OFFSET	0x0378	/* Dword offset 0_DE */
#घोषणा TEX_PALETTE		0x037C	/* Dword offset 0_DF */

#घोषणा SCALE_PITCH_BOTH	0x0380	/* Dword offset 0_E0 */
#घोषणा SECONDARY_SCALE_OFF_ACC	0x0384	/* Dword offset 0_E1 */
#घोषणा SCALE_OFF_ACC		0x0388	/* Dword offset 0_E2 */
#घोषणा SCALE_DST_Y_X		0x038C	/* Dword offset 0_E3 */

/* Draw Engine Destination Trajectory */
#घोषणा COMPOSITE_SHADOW_ID	0x0398	/* Dword offset 0_E6 */

#घोषणा SECONDARY_SCALE_X_INC	0x039C	/* Dword offset 0_E7 */

#घोषणा SPECULAR_RED_X_INC	0x039C	/* Dword offset 0_E7 */
#घोषणा SPECULAR_RED_Y_INC	0x03A0	/* Dword offset 0_E8 */
#घोषणा SPECULAR_RED_START	0x03A4	/* Dword offset 0_E9 */

#घोषणा SECONDARY_SCALE_HACC	0x03A4	/* Dword offset 0_E9 */

#घोषणा SPECULAR_GREEN_X_INC	0x03A8	/* Dword offset 0_EA */
#घोषणा SPECULAR_GREEN_Y_INC	0x03AC	/* Dword offset 0_EB */
#घोषणा SPECULAR_GREEN_START	0x03B0	/* Dword offset 0_EC */
#घोषणा SPECULAR_BLUE_X_INC	0x03B4	/* Dword offset 0_ED */
#घोषणा SPECULAR_BLUE_Y_INC	0x03B8	/* Dword offset 0_EE */
#घोषणा SPECULAR_BLUE_START	0x03BC	/* Dword offset 0_EF */

#घोषणा SCALE_X_INC__ALIAS__	0x03C0	/* Dword offset 0_F0 */

#घोषणा RED_X_INC__ALIAS__	0x03C0	/* Dword offset 0_F0 */
#घोषणा RED_Y_INC		0x03C4	/* Dword offset 0_F1 */
#घोषणा RED_START		0x03C8	/* Dword offset 0_F2 */

#घोषणा SCALE_HACC		0x03C8	/* Dword offset 0_F2 */
#घोषणा SCALE_Y_INC__ALIAS__	0x03CC	/* Dword offset 0_F3 */

#घोषणा GREEN_X_INC__ALIAS__	0x03CC	/* Dword offset 0_F3 */
#घोषणा GREEN_Y_INC		0x03D0	/* Dword offset 0_F4 */

#घोषणा SECONDARY_SCALE_Y_INC	0x03D0	/* Dword offset 0_F4 */
#घोषणा SECONDARY_SCALE_VACC	0x03D4	/* Dword offset 0_F5 */

#घोषणा GREEN_START		0x03D4	/* Dword offset 0_F5 */
#घोषणा BLUE_X_INC		0x03D8	/* Dword offset 0_F6 */
#घोषणा BLUE_Y_INC		0x03DC	/* Dword offset 0_F7 */
#घोषणा BLUE_START		0x03E0	/* Dword offset 0_F8 */
#घोषणा Z_X_INC			0x03E4	/* Dword offset 0_F9 */
#घोषणा Z_Y_INC			0x03E8	/* Dword offset 0_FA */
#घोषणा Z_START			0x03EC	/* Dword offset 0_FB */
#घोषणा ALPHA_X_INC		0x03F0	/* Dword offset 0_FC */
#घोषणा FOG_X_INC		0x03F0	/* Dword offset 0_FC */
#घोषणा ALPHA_Y_INC		0x03F4	/* Dword offset 0_FD */
#घोषणा FOG_Y_INC		0x03F4	/* Dword offset 0_FD */
#घोषणा ALPHA_START		0x03F8	/* Dword offset 0_FE */
#घोषणा FOG_START		0x03F8	/* Dword offset 0_FE */

#घोषणा OVERLAY_Y_X_START		0x0400	/* Dword offset 1_00 */
#घोषणा OVERLAY_Y_X_END			0x0404	/* Dword offset 1_01 */
#घोषणा OVERLAY_VIDEO_KEY_CLR		0x0408	/* Dword offset 1_02 */
#घोषणा OVERLAY_VIDEO_KEY_MSK		0x040C	/* Dword offset 1_03 */
#घोषणा OVERLAY_GRAPHICS_KEY_CLR	0x0410	/* Dword offset 1_04 */
#घोषणा OVERLAY_GRAPHICS_KEY_MSK	0x0414	/* Dword offset 1_05 */
#घोषणा OVERLAY_KEY_CNTL		0x0418	/* Dword offset 1_06 */

#घोषणा OVERLAY_SCALE_INC	0x0420	/* Dword offset 1_08 */
#घोषणा OVERLAY_SCALE_CNTL	0x0424	/* Dword offset 1_09 */
#घोषणा SCALER_HEIGHT_WIDTH	0x0428	/* Dword offset 1_0A */
#घोषणा SCALER_TEST		0x042C	/* Dword offset 1_0B */
#घोषणा SCALER_BUF0_OFFSET	0x0434	/* Dword offset 1_0D */
#घोषणा SCALER_BUF1_OFFSET	0x0438	/* Dword offset 1_0E */
#घोषणा SCALE_BUF_PITCH		0x043C	/* Dword offset 1_0F */

#घोषणा CAPTURE_START_END	0x0440	/* Dword offset 1_10 */
#घोषणा CAPTURE_X_WIDTH		0x0444	/* Dword offset 1_11 */
#घोषणा VIDEO_FORMAT		0x0448	/* Dword offset 1_12 */
#घोषणा VBI_START_END		0x044C	/* Dword offset 1_13 */
#घोषणा CAPTURE_CONFIG		0x0450	/* Dword offset 1_14 */
#घोषणा TRIG_CNTL		0x0454	/* Dword offset 1_15 */

#घोषणा OVERLAY_EXCLUSIVE_HORZ	0x0458	/* Dword offset 1_16 */
#घोषणा OVERLAY_EXCLUSIVE_VERT	0x045C	/* Dword offset 1_17 */

#घोषणा VAL_WIDTH		0x0460	/* Dword offset 1_18 */
#घोषणा CAPTURE_DEBUG		0x0464	/* Dword offset 1_19 */
#घोषणा VIDEO_SYNC_TEST		0x0468	/* Dword offset 1_1A */

/* GenLocking */
#घोषणा SNAPSHOT_VH_COUNTS	0x0470	/* Dword offset 1_1C */
#घोषणा SNAPSHOT_F_COUNT	0x0474	/* Dword offset 1_1D */
#घोषणा N_VIF_COUNT		0x0478	/* Dword offset 1_1E */
#घोषणा SNAPSHOT_VIF_COUNT	0x047C	/* Dword offset 1_1F */

#घोषणा CAPTURE_BUF0_OFFSET	0x0480	/* Dword offset 1_20 */
#घोषणा CAPTURE_BUF1_OFFSET	0x0484	/* Dword offset 1_21 */
#घोषणा CAPTURE_BUF_PITCH	0x0488	/* Dword offset 1_22 */

/* GenLocking */
#घोषणा SNAPSHOT2_VH_COUNTS	0x04B0	/* Dword offset 1_2C */
#घोषणा SNAPSHOT2_F_COUNT	0x04B4	/* Dword offset 1_2D */
#घोषणा N_VIF2_COUNT		0x04B8	/* Dword offset 1_2E */
#घोषणा SNAPSHOT2_VIF_COUNT	0x04BC	/* Dword offset 1_2F */

#घोषणा MPP_CONFIG		0x04C0	/* Dword offset 1_30 */
#घोषणा MPP_STROBE_SEQ		0x04C4	/* Dword offset 1_31 */
#घोषणा MPP_ADDR		0x04C8	/* Dword offset 1_32 */
#घोषणा MPP_DATA		0x04CC	/* Dword offset 1_33 */
#घोषणा TVO_CNTL		0x0500	/* Dword offset 1_40 */

/* Test and Debug */
#घोषणा CRT_HORZ_VERT_LOAD	0x0544	/* Dword offset 1_51 */

/* AGP */
#घोषणा AGP_BASE		0x0548	/* Dword offset 1_52 */
#घोषणा AGP_CNTL		0x054C	/* Dword offset 1_53 */

#घोषणा SCALER_COLOUR_CNTL	0x0550	/* Dword offset 1_54 */
#घोषणा SCALER_H_COEFF0		0x0554	/* Dword offset 1_55 */
#घोषणा SCALER_H_COEFF1		0x0558	/* Dword offset 1_56 */
#घोषणा SCALER_H_COEFF2		0x055C	/* Dword offset 1_57 */
#घोषणा SCALER_H_COEFF3		0x0560	/* Dword offset 1_58 */
#घोषणा SCALER_H_COEFF4		0x0564	/* Dword offset 1_59 */

/* Command FIFO */
#घोषणा GUI_CMDFIFO_DEBUG	0x0570	/* Dword offset 1_5C */
#घोषणा GUI_CMDFIFO_DATA	0x0574	/* Dword offset 1_5D */
#घोषणा GUI_CNTL		0x0578	/* Dword offset 1_5E */

/* Bus Mastering */
#घोषणा BM_FRAME_BUF_OFFSET	0x0580	/* Dword offset 1_60 */
#घोषणा BM_SYSTEM_MEM_ADDR	0x0584	/* Dword offset 1_61 */
#घोषणा BM_COMMAND		0x0588	/* Dword offset 1_62 */
#घोषणा BM_STATUS		0x058C	/* Dword offset 1_63 */
#घोषणा BM_GUI_TABLE		0x05B8	/* Dword offset 1_6E */
#घोषणा BM_SYSTEM_TABLE		0x05BC	/* Dword offset 1_6F */

#घोषणा SCALER_BUF0_OFFSET_U	0x05D4	/* Dword offset 1_75 */
#घोषणा SCALER_BUF0_OFFSET_V	0x05D8	/* Dword offset 1_76 */
#घोषणा SCALER_BUF1_OFFSET_U	0x05DC	/* Dword offset 1_77 */
#घोषणा SCALER_BUF1_OFFSET_V	0x05E0	/* Dword offset 1_78 */

/* Setup Engine */
#घोषणा VERTEX_1_S		0x0640	/* Dword offset 1_90 */
#घोषणा VERTEX_1_T		0x0644	/* Dword offset 1_91 */
#घोषणा VERTEX_1_W		0x0648	/* Dword offset 1_92 */
#घोषणा VERTEX_1_SPEC_ARGB	0x064C	/* Dword offset 1_93 */
#घोषणा VERTEX_1_Z		0x0650	/* Dword offset 1_94 */
#घोषणा VERTEX_1_ARGB		0x0654	/* Dword offset 1_95 */
#घोषणा VERTEX_1_X_Y		0x0658	/* Dword offset 1_96 */
#घोषणा ONE_OVER_AREA		0x065C	/* Dword offset 1_97 */
#घोषणा VERTEX_2_S		0x0660	/* Dword offset 1_98 */
#घोषणा VERTEX_2_T		0x0664	/* Dword offset 1_99 */
#घोषणा VERTEX_2_W		0x0668	/* Dword offset 1_9A */
#घोषणा VERTEX_2_SPEC_ARGB	0x066C	/* Dword offset 1_9B */
#घोषणा VERTEX_2_Z		0x0670	/* Dword offset 1_9C */
#घोषणा VERTEX_2_ARGB		0x0674	/* Dword offset 1_9D */
#घोषणा VERTEX_2_X_Y		0x0678	/* Dword offset 1_9E */
#घोषणा ONE_OVER_AREA		0x065C	/* Dword offset 1_9F */
#घोषणा VERTEX_3_S		0x0680	/* Dword offset 1_A0 */
#घोषणा VERTEX_3_T		0x0684	/* Dword offset 1_A1 */
#घोषणा VERTEX_3_W		0x0688	/* Dword offset 1_A2 */
#घोषणा VERTEX_3_SPEC_ARGB	0x068C	/* Dword offset 1_A3 */
#घोषणा VERTEX_3_Z		0x0690	/* Dword offset 1_A4 */
#घोषणा VERTEX_3_ARGB		0x0694	/* Dword offset 1_A5 */
#घोषणा VERTEX_3_X_Y		0x0698	/* Dword offset 1_A6 */
#घोषणा ONE_OVER_AREA		0x065C	/* Dword offset 1_A7 */
#घोषणा VERTEX_1_S		0x0640	/* Dword offset 1_AB */
#घोषणा VERTEX_1_T		0x0644	/* Dword offset 1_AC */
#घोषणा VERTEX_1_W		0x0648	/* Dword offset 1_AD */
#घोषणा VERTEX_2_S		0x0660	/* Dword offset 1_AE */
#घोषणा VERTEX_2_T		0x0664	/* Dword offset 1_AF */
#घोषणा VERTEX_2_W		0x0668	/* Dword offset 1_B0 */
#घोषणा VERTEX_3_SECONDARY_S	0x06C0	/* Dword offset 1_B0 */
#घोषणा VERTEX_3_S		0x0680	/* Dword offset 1_B1 */
#घोषणा VERTEX_3_SECONDARY_T	0x06C4	/* Dword offset 1_B1 */
#घोषणा VERTEX_3_T		0x0684	/* Dword offset 1_B2 */
#घोषणा VERTEX_3_SECONDARY_W	0x06C8	/* Dword offset 1_B2 */
#घोषणा VERTEX_3_W		0x0688	/* Dword offset 1_B3 */
#घोषणा VERTEX_1_SPEC_ARGB	0x064C	/* Dword offset 1_B4 */
#घोषणा VERTEX_2_SPEC_ARGB	0x066C	/* Dword offset 1_B5 */
#घोषणा VERTEX_3_SPEC_ARGB	0x068C	/* Dword offset 1_B6 */
#घोषणा VERTEX_1_Z		0x0650	/* Dword offset 1_B7 */
#घोषणा VERTEX_2_Z		0x0670	/* Dword offset 1_B8 */
#घोषणा VERTEX_3_Z		0x0690	/* Dword offset 1_B9 */
#घोषणा VERTEX_1_ARGB		0x0654	/* Dword offset 1_BA */
#घोषणा VERTEX_2_ARGB		0x0674	/* Dword offset 1_BB */
#घोषणा VERTEX_3_ARGB		0x0694	/* Dword offset 1_BC */
#घोषणा VERTEX_1_X_Y		0x0658	/* Dword offset 1_BD */
#घोषणा VERTEX_2_X_Y		0x0678	/* Dword offset 1_BE */
#घोषणा VERTEX_3_X_Y		0x0698	/* Dword offset 1_BF */
#घोषणा ONE_OVER_AREA_UC	0x0700	/* Dword offset 1_C0 */
#घोषणा SETUP_CNTL		0x0704	/* Dword offset 1_C1 */
#घोषणा VERTEX_1_SECONDARY_S	0x0728	/* Dword offset 1_CA */
#घोषणा VERTEX_1_SECONDARY_T	0x072C	/* Dword offset 1_CB */
#घोषणा VERTEX_1_SECONDARY_W	0x0730	/* Dword offset 1_CC */
#घोषणा VERTEX_2_SECONDARY_S	0x0734	/* Dword offset 1_CD */
#घोषणा VERTEX_2_SECONDARY_T	0x0738	/* Dword offset 1_CE */
#घोषणा VERTEX_2_SECONDARY_W	0x073C	/* Dword offset 1_CF */


#घोषणा GTC_3D_RESET_DELAY	3	/* 3D engine reset delay in ms */

/* CRTC control values (mostly CRTC_GEN_CNTL) */

#घोषणा CRTC_H_SYNC_NEG		0x00200000
#घोषणा CRTC_V_SYNC_NEG		0x00200000

#घोषणा CRTC_DBL_SCAN_EN	0x00000001
#घोषणा CRTC_INTERLACE_EN	0x00000002
#घोषणा CRTC_HSYNC_DIS		0x00000004
#घोषणा CRTC_VSYNC_DIS		0x00000008
#घोषणा CRTC_CSYNC_EN		0x00000010
#घोषणा CRTC_PIX_BY_2_EN	0x00000020	/* unused on RAGE */
#घोषणा CRTC_DISPLAY_DIS	0x00000040
#घोषणा CRTC_VGA_XOVERSCAN	0x00000080

#घोषणा CRTC_PIX_WIDTH_MASK	0x00000700
#घोषणा CRTC_PIX_WIDTH_4BPP	0x00000100
#घोषणा CRTC_PIX_WIDTH_8BPP	0x00000200
#घोषणा CRTC_PIX_WIDTH_15BPP	0x00000300
#घोषणा CRTC_PIX_WIDTH_16BPP	0x00000400
#घोषणा CRTC_PIX_WIDTH_24BPP	0x00000500
#घोषणा CRTC_PIX_WIDTH_32BPP	0x00000600

#घोषणा CRTC_BYTE_PIX_ORDER	0x00000800
#घोषणा CRTC_PIX_ORDER_MSN_LSN	0x00000000
#घोषणा CRTC_PIX_ORDER_LSN_MSN	0x00000800

#घोषणा CRTC_VSYNC_INT_EN	0x00001000ul	/* XC/XL */
#घोषणा CRTC_VSYNC_INT		0x00002000ul	/* XC/XL */
#घोषणा CRTC_FIFO_OVERFILL	0x0000c000ul	/* VT/GT */
#घोषणा CRTC2_VSYNC_INT_EN	0x00004000ul	/* XC/XL */
#घोषणा CRTC2_VSYNC_INT		0x00008000ul	/* XC/XL */

#घोषणा CRTC_FIFO_LWM		0x000f0000
#घोषणा CRTC_HVSYNC_IO_DRIVE	0x00010000	/* XC/XL */
#घोषणा CRTC2_PIX_WIDTH		0x000e0000	/* LTPro */

#घोषणा CRTC_VGA_128KAP_PAGING	0x00100000
#घोषणा CRTC_VFC_SYNC_TRISTATE	0x00200000	/* VTB/GTB/LT */
#घोषणा CRTC2_EN		0x00200000	/* LTPro */
#घोषणा CRTC_LOCK_REGS		0x00400000
#घोषणा CRTC_SYNC_TRISTATE	0x00800000

#घोषणा CRTC_EXT_DISP_EN	0x01000000
#घोषणा CRTC_EN			0x02000000
#घोषणा CRTC_DISP_REQ_EN	0x04000000
#घोषणा CRTC_VGA_LINEAR		0x08000000
#घोषणा CRTC_VSYNC_FALL_EDGE	0x10000000
#घोषणा CRTC_VGA_TEXT_132	0x20000000
#घोषणा CRTC_CNT_EN		0x40000000
#घोषणा CRTC_CUR_B_TEST		0x80000000

#घोषणा CRTC_CRNT_VLINE		0x07f00000

#घोषणा CRTC_PRESERVED_MASK	0x0001f000

#घोषणा CRTC_VBLANK		0x00000001
#घोषणा CRTC_VBLANK_INT_EN	0x00000002
#घोषणा CRTC_VBLANK_INT		0x00000004
#घोषणा CRTC_VBLANK_INT_AK	CRTC_VBLANK_INT
#घोषणा CRTC_VLINE_INT_EN	0x00000008
#घोषणा CRTC_VLINE_INT		0x00000010
#घोषणा CRTC_VLINE_INT_AK	CRTC_VLINE_INT
#घोषणा CRTC_VLINE_SYNC		0x00000020
#घोषणा CRTC_FRAME		0x00000040
#घोषणा SNAPSHOT_INT_EN		0x00000080
#घोषणा SNAPSHOT_INT		0x00000100
#घोषणा SNAPSHOT_INT_AK		SNAPSHOT_INT
#घोषणा I2C_INT_EN		0x00000200
#घोषणा I2C_INT			0x00000400
#घोषणा I2C_INT_AK		I2C_INT
#घोषणा CRTC2_VBLANK		0x00000800
#घोषणा CRTC2_VBLANK_INT_EN	0x00001000
#घोषणा CRTC2_VBLANK_INT	0x00002000
#घोषणा CRTC2_VBLANK_INT_AK	CRTC2_VBLANK_INT
#घोषणा CRTC2_VLINE_INT_EN	0x00004000
#घोषणा CRTC2_VLINE_INT		0x00008000
#घोषणा CRTC2_VLINE_INT_AK	CRTC2_VLINE_INT
#घोषणा CAPBUF0_INT_EN		0x00010000
#घोषणा CAPBUF0_INT		0x00020000
#घोषणा CAPBUF0_INT_AK		CAPBUF0_INT
#घोषणा CAPBUF1_INT_EN		0x00040000
#घोषणा CAPBUF1_INT		0x00080000
#घोषणा CAPBUF1_INT_AK		CAPBUF1_INT
#घोषणा OVERLAY_खातापूर्ण_INT_EN	0x00100000
#घोषणा OVERLAY_खातापूर्ण_INT		0x00200000
#घोषणा OVERLAY_खातापूर्ण_INT_AK	OVERLAY_खातापूर्ण_INT
#घोषणा ONESHOT_CAP_INT_EN	0x00400000
#घोषणा ONESHOT_CAP_INT		0x00800000
#घोषणा ONESHOT_CAP_INT_AK	ONESHOT_CAP_INT
#घोषणा BUSMASTER_EOL_INT_EN	0x01000000
#घोषणा BUSMASTER_EOL_INT	0x02000000
#घोषणा BUSMASTER_EOL_INT_AK	BUSMASTER_EOL_INT
#घोषणा GP_INT_EN		0x04000000
#घोषणा GP_INT			0x08000000
#घोषणा GP_INT_AK		GP_INT
#घोषणा CRTC2_VLINE_SYNC	0x10000000
#घोषणा SNAPSHOT2_INT_EN	0x20000000
#घोषणा SNAPSHOT2_INT		0x40000000
#घोषणा SNAPSHOT2_INT_AK	SNAPSHOT2_INT
#घोषणा VBLANK_BIT2_INT		0x80000000
#घोषणा VBLANK_BIT2_INT_AK	VBLANK_BIT2_INT

#घोषणा CRTC_INT_EN_MASK	(CRTC_VBLANK_INT_EN |	\
				 CRTC_VLINE_INT_EN |	\
				 SNAPSHOT_INT_EN |	\
				 I2C_INT_EN |		\
				 CRTC2_VBLANK_INT_EN |	\
				 CRTC2_VLINE_INT_EN |	\
				 CAPBUF0_INT_EN |	\
				 CAPBUF1_INT_EN |	\
				 OVERLAY_खातापूर्ण_INT_EN |	\
				 ONESHOT_CAP_INT_EN |	\
				 BUSMASTER_EOL_INT_EN |	\
				 GP_INT_EN |		\
				 SNAPSHOT2_INT_EN)

/* DAC control values */

#घोषणा DAC_EXT_SEL_RS2		0x01
#घोषणा DAC_EXT_SEL_RS3		0x02
#घोषणा DAC_8BIT_EN		0x00000100
#घोषणा DAC_PIX_DLY_MASK	0x00000600
#घोषणा DAC_PIX_DLY_0NS		0x00000000
#घोषणा DAC_PIX_DLY_2NS		0x00000200
#घोषणा DAC_PIX_DLY_4NS		0x00000400
#घोषणा DAC_BLANK_ADJ_MASK	0x00001800
#घोषणा DAC_BLANK_ADJ_0		0x00000000
#घोषणा DAC_BLANK_ADJ_1		0x00000800
#घोषणा DAC_BLANK_ADJ_2		0x00001000

/* DAC control values (my source XL/XC Register reference) */
#घोषणा DAC_OUTPUT_MASK         0x00000001  /* 0 - PAL, 1 - NTSC */
#घोषणा DAC_MISTERY_BIT         0x00000002  /* PS2 ? RS343 ?, EXTRA_BRIGHT क्रम GT */
#घोषणा DAC_BLANKING            0x00000004
#घोषणा DAC_CMP_DISABLE         0x00000008
#घोषणा DAC1_CLK_SEL            0x00000010
#घोषणा PALETTE_ACCESS_CNTL     0x00000020
#घोषणा PALETTE2_SNOOP_EN       0x00000040
#घोषणा DAC_CMP_OUTPUT          0x00000080 /* पढ़ो only */
/* #घोषणा DAC_8BIT_EN is ok */
#घोषणा CRT_SENSE               0x00000800 /* पढ़ो only */
#घोषणा CRT_DETECTION_ON        0x00001000
#घोषणा DAC_VGA_ADR_EN          0x00002000
#घोषणा DAC_FEA_CON_EN          0x00004000
#घोषणा DAC_PDWN                0x00008000
#घोषणा DAC_TYPE_MASK           0x00070000 /* पढ़ो only */



/* Mix control values */

#घोषणा MIX_NOT_DST		0x0000
#घोषणा MIX_0			0x0001
#घोषणा MIX_1			0x0002
#घोषणा MIX_DST			0x0003
#घोषणा MIX_NOT_SRC		0x0004
#घोषणा MIX_XOR			0x0005
#घोषणा MIX_XNOR		0x0006
#घोषणा MIX_SRC			0x0007
#घोषणा MIX_न_अंकD		0x0008
#घोषणा MIX_NOT_SRC_OR_DST	0x0009
#घोषणा MIX_SRC_OR_NOT_DST	0x000a
#घोषणा MIX_OR			0x000b
#घोषणा MIX_AND			0x000c
#घोषणा MIX_SRC_AND_NOT_DST	0x000d
#घोषणा MIX_NOT_SRC_AND_DST	0x000e
#घोषणा MIX_NOR			0x000f

/* Maximum engine dimensions */
#घोषणा ENGINE_MIN_X		0
#घोषणा ENGINE_MIN_Y		0
#घोषणा ENGINE_MAX_X		4095
#घोषणा ENGINE_MAX_Y		16383

/* Mach64 engine bit स्थिरants - these are typically ORed together */

/* BUS_CNTL रेजिस्टर स्थिरants */
#घोषणा BUS_APER_REG_DIS	0x00000010
#घोषणा BUS_FIFO_ERR_ACK	0x00200000
#घोषणा BUS_HOST_ERR_ACK	0x00800000

/* GEN_TEST_CNTL रेजिस्टर स्थिरants */
#घोषणा GEN_OVR_OUTPUT_EN	0x20
#घोषणा HWCURSOR_ENABLE		0x80
#घोषणा GUI_ENGINE_ENABLE	0x100
#घोषणा BLOCK_WRITE_ENABLE	0x200

/* DSP_CONFIG रेजिस्टर स्थिरants */
#घोषणा DSP_XCLKS_PER_QW	0x00003fff
#घोषणा DSP_LOOP_LATENCY	0x000f0000
#घोषणा DSP_PRECISION		0x00700000

/* DSP_ON_OFF रेजिस्टर स्थिरants */
#घोषणा DSP_OFF			0x000007ff
#घोषणा DSP_ON			0x07ff0000
#घोषणा VGA_DSP_OFF		DSP_OFF
#घोषणा VGA_DSP_ON		DSP_ON
#घोषणा VGA_DSP_XCLKS_PER_QW	DSP_XCLKS_PER_QW

/* PLL रेजिस्टर indices and fields */
#घोषणा MPLL_CNTL		0x00
#घोषणा PLL_PC_GAIN		0x07
#घोषणा PLL_VC_GAIN		0x18
#घोषणा PLL_DUTY_CYC		0xE0
#घोषणा VPLL_CNTL		0x01
#घोषणा PLL_REF_DIV		0x02
#घोषणा PLL_GEN_CNTL		0x03
#घोषणा PLL_OVERRIDE		0x01	/* PLL_SLEEP */
#घोषणा PLL_MCLK_RST		0x02	/* PLL_MRESET */
#घोषणा OSC_EN			0x04
#घोषणा EXT_CLK_EN		0x08
#घोषणा FORCE_DCLK_TRI_STATE	0x08    /* VT4 -> */
#घोषणा MCLK_SRC_SEL		0x70
#घोषणा EXT_CLK_CNTL		0x80
#घोषणा DLL_PWDN		0x80    /* VT4 -> */
#घोषणा MCLK_FB_DIV		0x04
#घोषणा PLL_VCLK_CNTL		0x05
#घोषणा PLL_VCLK_SRC_SEL	0x03
#घोषणा PLL_VCLK_RST		0x04
#घोषणा PLL_VCLK_INVERT		0x08
#घोषणा VCLK_POST_DIV		0x06
#घोषणा VCLK0_POST		0x03
#घोषणा VCLK1_POST		0x0C
#घोषणा VCLK2_POST		0x30
#घोषणा VCLK3_POST		0xC0
#घोषणा VCLK0_FB_DIV		0x07
#घोषणा VCLK1_FB_DIV		0x08
#घोषणा VCLK2_FB_DIV		0x09
#घोषणा VCLK3_FB_DIV		0x0A
#घोषणा PLL_EXT_CNTL		0x0B
#घोषणा PLL_XCLK_MCLK_RATIO	0x03
#घोषणा PLL_XCLK_SRC_SEL	0x07
#घोषणा PLL_MFB_TIMES_4_2B	0x08
#घोषणा PLL_VCLK0_XDIV		0x10
#घोषणा PLL_VCLK1_XDIV		0x20
#घोषणा PLL_VCLK2_XDIV		0x40
#घोषणा PLL_VCLK3_XDIV		0x80
#घोषणा DLL_CNTL		0x0C
#घोषणा DLL1_CNTL		0x0C
#घोषणा VFC_CNTL		0x0D
#घोषणा PLL_TEST_CNTL		0x0E
#घोषणा PLL_TEST_COUNT		0x0F
#घोषणा LVDS_CNTL0		0x10
#घोषणा LVDS_CNTL1		0x11
#घोषणा AGP1_CNTL		0x12
#घोषणा AGP2_CNTL		0x13
#घोषणा DLL2_CNTL		0x14
#घोषणा SCLK_FB_DIV		0x15
#घोषणा SPLL_CNTL1		0x16
#घोषणा SPLL_CNTL2		0x17
#घोषणा APLL_STRAPS		0x18
#घोषणा EXT_VPLL_CNTL		0x19
#घोषणा EXT_VPLL_EN		0x04
#घोषणा EXT_VPLL_VGA_EN		0x08
#घोषणा EXT_VPLL_INSYNC		0x10
#घोषणा EXT_VPLL_REF_DIV	0x1A
#घोषणा EXT_VPLL_FB_DIV		0x1B
#घोषणा EXT_VPLL_MSB		0x1C
#घोषणा HTOTAL_CNTL		0x1D
#घोषणा BYTE_CLK_CNTL		0x1E
#घोषणा TV_PLL_CNTL1		0x1F
#घोषणा TV_PLL_CNTL2		0x20
#घोषणा TV_PLL_CNTL		0x21
#घोषणा EXT_TV_PLL		0x22
#घोषणा V2PLL_CNTL		0x23
#घोषणा PLL_V2CLK_CNTL		0x24
#घोषणा EXT_V2PLL_REF_DIV	0x25
#घोषणा EXT_V2PLL_FB_DIV	0x26
#घोषणा EXT_V2PLL_MSB		0x27
#घोषणा HTOTAL2_CNTL		0x28
#घोषणा PLL_YCLK_CNTL		0x29
#घोषणा PM_DYN_CLK_CNTL		0x2A

/* CNFG_CNTL रेजिस्टर स्थिरants */
#घोषणा APERTURE_4M_ENABLE	1
#घोषणा APERTURE_8M_ENABLE	2
#घोषणा VGA_APERTURE_ENABLE	4

/* CNFG_STAT0 रेजिस्टर स्थिरants (GX, CX) */
#घोषणा CFG_BUS_TYPE		0x00000007
#घोषणा CFG_MEM_TYPE		0x00000038
#घोषणा CFG_INIT_DAC_TYPE	0x00000e00

/* CNFG_STAT0 रेजिस्टर स्थिरants (CT, ET, VT) */
#घोषणा CFG_MEM_TYPE_xT		0x00000007

#घोषणा ISA			0
#घोषणा EISA			1
#घोषणा LOCAL_BUS		6
#घोषणा PCI			7

/* Memory types क्रम GX, CX */
#घोषणा DRAMx4			0
#घोषणा VRAMx16			1
#घोषणा VRAMx16ssr		2
#घोषणा DRAMx16			3
#घोषणा GraphicsDRAMx16		4
#घोषणा EnhancedVRAMx16		5
#घोषणा EnhancedVRAMx16ssr	6

/* Memory types क्रम CT, ET, VT, GT */
#घोषणा DRAM			1
#घोषणा EDO			2
#घोषणा PSEUDO_EDO		3
#घोषणा SDRAM			4
#घोषणा SGRAM			5
#घोषणा WRAM			6
#घोषणा SDRAM32			6

#घोषणा DAC_INTERNAL		0x00
#घोषणा DAC_IBMRGB514		0x01
#घोषणा DAC_ATI68875		0x02
#घोषणा DAC_TVP3026_A		0x72
#घोषणा DAC_BT476		0x03
#घोषणा DAC_BT481		0x04
#घोषणा DAC_ATT20C491		0x14
#घोषणा DAC_SC15026		0x24
#घोषणा DAC_MU9C1880		0x34
#घोषणा DAC_IMSG174		0x44
#घोषणा DAC_ATI68860_B		0x05
#घोषणा DAC_ATI68860_C		0x15
#घोषणा DAC_TVP3026_B		0x75
#घोषणा DAC_STG1700		0x06
#घोषणा DAC_ATT498		0x16
#घोषणा DAC_STG1702		0x07
#घोषणा DAC_SC15021		0x17
#घोषणा DAC_ATT21C498		0x27
#घोषणा DAC_STG1703		0x37
#घोषणा DAC_CH8398		0x47
#घोषणा DAC_ATT20C408		0x57

#घोषणा CLK_ATI18818_0		0
#घोषणा CLK_ATI18818_1		1
#घोषणा CLK_STG1703		2
#घोषणा CLK_CH8398		3
#घोषणा CLK_INTERNAL		4
#घोषणा CLK_ATT20C408		5
#घोषणा CLK_IBMRGB514		6

/* MEM_CNTL रेजिस्टर स्थिरants */
#घोषणा MEM_SIZE_ALIAS		0x00000007
#घोषणा MEM_SIZE_512K		0x00000000
#घोषणा MEM_SIZE_1M		0x00000001
#घोषणा MEM_SIZE_2M		0x00000002
#घोषणा MEM_SIZE_4M		0x00000003
#घोषणा MEM_SIZE_6M		0x00000004
#घोषणा MEM_SIZE_8M		0x00000005
#घोषणा MEM_SIZE_ALIAS_GTB	0x0000000F
#घोषणा MEM_SIZE_2M_GTB		0x00000003
#घोषणा MEM_SIZE_4M_GTB		0x00000007
#घोषणा MEM_SIZE_6M_GTB		0x00000009
#घोषणा MEM_SIZE_8M_GTB		0x0000000B
#घोषणा MEM_BNDRY		0x00030000
#घोषणा MEM_BNDRY_0K		0x00000000
#घोषणा MEM_BNDRY_256K		0x00010000
#घोषणा MEM_BNDRY_512K		0x00020000
#घोषणा MEM_BNDRY_1M		0x00030000
#घोषणा MEM_BNDRY_EN		0x00040000

#घोषणा ONE_MB			0x100000
/* ATI PCI स्थिरants */
#घोषणा PCI_ATI_VENDOR_ID	0x1002


/* CNFG_CHIP_ID रेजिस्टर स्थिरants */
#घोषणा CFG_CHIP_TYPE		0x0000FFFF
#घोषणा CFG_CHIP_CLASS		0x00FF0000
#घोषणा CFG_CHIP_REV		0xFF000000
#घोषणा CFG_CHIP_MAJOR		0x07000000
#घोषणा CFG_CHIP_FND_ID		0x38000000
#घोषणा CFG_CHIP_MINOR		0xC0000000


/* Chip IDs पढ़ो from CNFG_CHIP_ID */

/* mach64GX family */
#घोषणा GX_CHIP_ID	0xD7	/* mach64GX (ATI888GX00) */
#घोषणा CX_CHIP_ID	0x57	/* mach64CX (ATI888CX00) */

#घोषणा GX_PCI_ID	0x4758	/* mach64GX (ATI888GX00) */
#घोषणा CX_PCI_ID	0x4358	/* mach64CX (ATI888CX00) */

/* mach64CT family */
#घोषणा CT_CHIP_ID	0x4354	/* mach64CT (ATI264CT) */
#घोषणा ET_CHIP_ID	0x4554	/* mach64ET (ATI264ET) */

/* mach64CT family / mach64VT class */
#घोषणा VT_CHIP_ID	0x5654	/* mach64VT (ATI264VT) */
#घोषणा VU_CHIP_ID	0x5655	/* mach64VTB (ATI264VTB) */
#घोषणा VV_CHIP_ID	0x5656	/* mach64VT4 (ATI264VT4) */

/* mach64CT family / mach64GT (3D RAGE) class */
#घोषणा LB_CHIP_ID	0x4c42	/* RAGE LT PRO, AGP */
#घोषणा LD_CHIP_ID	0x4c44	/* RAGE LT PRO */
#घोषणा LG_CHIP_ID	0x4c47	/* RAGE LT */
#घोषणा LI_CHIP_ID	0x4c49	/* RAGE LT PRO */
#घोषणा LP_CHIP_ID	0x4c50	/* RAGE LT PRO */
#घोषणा LT_CHIP_ID	0x4c54	/* RAGE LT */

/* mach64CT family / (Rage XL) class */
#घोषणा GR_CHIP_ID	0x4752	/* RAGE XL, BGA, PCI33 */
#घोषणा GS_CHIP_ID	0x4753	/* RAGE XL, PQFP, PCI33 */
#घोषणा GM_CHIP_ID	0x474d	/* RAGE XL, BGA, AGP 1x,2x */
#घोषणा GN_CHIP_ID	0x474e	/* RAGE XL, PQFP,AGP 1x,2x */
#घोषणा GO_CHIP_ID	0x474f	/* RAGE XL, BGA, PCI66 */
#घोषणा GL_CHIP_ID	0x474c	/* RAGE XL, PQFP, PCI66 */

#घोषणा IS_XL(id) ((id)==GR_CHIP_ID || (id)==GS_CHIP_ID || \
		   (id)==GM_CHIP_ID || (id)==GN_CHIP_ID || \
		   (id)==GO_CHIP_ID || (id)==GL_CHIP_ID)

#घोषणा GT_CHIP_ID	0x4754	/* RAGE (GT) */
#घोषणा GU_CHIP_ID	0x4755	/* RAGE II/II+ (GTB) */
#घोषणा GV_CHIP_ID	0x4756	/* RAGE IIC, PCI */
#घोषणा GW_CHIP_ID	0x4757	/* RAGE IIC, AGP */
#घोषणा GZ_CHIP_ID	0x475a	/* RAGE IIC, AGP */
#घोषणा GB_CHIP_ID	0x4742	/* RAGE PRO, BGA, AGP 1x and 2x */
#घोषणा GD_CHIP_ID	0x4744	/* RAGE PRO, BGA, AGP 1x only */
#घोषणा GI_CHIP_ID	0x4749	/* RAGE PRO, BGA, PCI33 only */
#घोषणा GP_CHIP_ID	0x4750	/* RAGE PRO, PQFP, PCI33, full 3D */
#घोषणा GQ_CHIP_ID	0x4751	/* RAGE PRO, PQFP, PCI33, limited 3D */

#घोषणा LM_CHIP_ID	0x4c4d	/* RAGE Mobility AGP, full function */
#घोषणा LN_CHIP_ID	0x4c4e	/* RAGE Mobility AGP */
#घोषणा LR_CHIP_ID	0x4c52	/* RAGE Mobility PCI, full function */
#घोषणा LS_CHIP_ID	0x4c53	/* RAGE Mobility PCI */

#घोषणा IS_MOBILITY(id) ((id)==LM_CHIP_ID || (id)==LN_CHIP_ID || \
			(id)==LR_CHIP_ID || (id)==LS_CHIP_ID)
/* Mach64 major ASIC revisions */
#घोषणा MACH64_ASIC_NEC_VT_A3		0x08
#घोषणा MACH64_ASIC_NEC_VT_A4		0x48
#घोषणा MACH64_ASIC_SGS_VT_A4		0x40
#घोषणा MACH64_ASIC_SGS_VT_B1S1		0x01
#घोषणा MACH64_ASIC_SGS_GT_B1S1		0x01
#घोषणा MACH64_ASIC_SGS_GT_B1S2		0x41
#घोषणा MACH64_ASIC_UMC_GT_B2U1		0x1a
#घोषणा MACH64_ASIC_UMC_GT_B2U2		0x5a
#घोषणा MACH64_ASIC_UMC_VT_B2U3		0x9a
#घोषणा MACH64_ASIC_UMC_GT_B2U3		0x9a
#घोषणा MACH64_ASIC_UMC_R3B_D_P_A1	0x1b
#घोषणा MACH64_ASIC_UMC_R3B_D_P_A2	0x5b
#घोषणा MACH64_ASIC_UMC_R3B_D_P_A3	0x1c
#घोषणा MACH64_ASIC_UMC_R3B_D_P_A4	0x5c

/* Mach64 foundries */
#घोषणा MACH64_FND_SGS		0
#घोषणा MACH64_FND_NEC		1
#घोषणा MACH64_FND_UMC		3

/* Mach64 chip types */
#घोषणा MACH64_UNKNOWN		0
#घोषणा MACH64_GX		1
#घोषणा MACH64_CX		2
#घोषणा MACH64_CT		3Restore
#घोषणा MACH64_ET		4
#घोषणा MACH64_VT		5
#घोषणा MACH64_GT		6

/* DST_CNTL रेजिस्टर स्थिरants */
#घोषणा DST_X_RIGHT_TO_LEFT	0
#घोषणा DST_X_LEFT_TO_RIGHT	1
#घोषणा DST_Y_BOTTOM_TO_TOP	0
#घोषणा DST_Y_TOP_TO_BOTTOM	2
#घोषणा DST_X_MAJOR		0
#घोषणा DST_Y_MAJOR		4
#घोषणा DST_X_TILE		8
#घोषणा DST_Y_TILE		0x10
#घोषणा DST_LAST_PEL		0x20
#घोषणा DST_POLYGON_ENABLE	0x40
#घोषणा DST_24_ROTATION_ENABLE	0x80

/* SRC_CNTL रेजिस्टर स्थिरants */
#घोषणा SRC_PATTERN_ENABLE		1
#घोषणा SRC_ROTATION_ENABLE		2
#घोषणा SRC_LINEAR_ENABLE		4
#घोषणा SRC_BYTE_ALIGN			8
#घोषणा SRC_LINE_X_RIGHT_TO_LEFT	0
#घोषणा SRC_LINE_X_LEFT_TO_RIGHT	0x10

/* HOST_CNTL रेजिस्टर स्थिरants */
#घोषणा HOST_BYTE_ALIGN		1

/* GUI_TRAJ_CNTL रेजिस्टर स्थिरants */
#घोषणा PAT_MONO_8x8_ENABLE	0x01000000
#घोषणा PAT_CLR_4x2_ENABLE	0x02000000
#घोषणा PAT_CLR_8x1_ENABLE	0x04000000

/* DP_CHAIN_MASK रेजिस्टर स्थिरants */
#घोषणा DP_CHAIN_4BPP		0x8888
#घोषणा DP_CHAIN_7BPP		0xD2D2
#घोषणा DP_CHAIN_8BPP		0x8080
#घोषणा DP_CHAIN_8BPP_RGB	0x9292
#घोषणा DP_CHAIN_15BPP		0x4210
#घोषणा DP_CHAIN_16BPP		0x8410
#घोषणा DP_CHAIN_24BPP		0x8080
#घोषणा DP_CHAIN_32BPP		0x8080

/* DP_PIX_WIDTH रेजिस्टर स्थिरants */
#घोषणा DST_1BPP		0x0
#घोषणा DST_4BPP		0x1
#घोषणा DST_8BPP		0x2
#घोषणा DST_15BPP		0x3
#घोषणा DST_16BPP		0x4
#घोषणा DST_24BPP		0x5
#घोषणा DST_32BPP		0x6
#घोषणा DST_MASK		0xF
#घोषणा SRC_1BPP		0x000
#घोषणा SRC_4BPP		0x100
#घोषणा SRC_8BPP		0x200
#घोषणा SRC_15BPP		0x300
#घोषणा SRC_16BPP		0x400
#घोषणा SRC_24BPP		0x500
#घोषणा SRC_32BPP		0x600
#घोषणा SRC_MASK		0xF00
#घोषणा DP_HOST_TRIPLE_EN	0x2000
#घोषणा HOST_1BPP		0x00000
#घोषणा HOST_4BPP		0x10000
#घोषणा HOST_8BPP		0x20000
#घोषणा HOST_15BPP		0x30000
#घोषणा HOST_16BPP		0x40000
#घोषणा HOST_24BPP		0x50000
#घोषणा HOST_32BPP		0x60000
#घोषणा HOST_MASK		0xF0000
#घोषणा BYTE_ORDER_MSB_TO_LSB	0
#घोषणा BYTE_ORDER_LSB_TO_MSB	0x1000000
#घोषणा BYTE_ORDER_MASK		0x1000000

/* DP_MIX रेजिस्टर स्थिरants */
#घोषणा BKGD_MIX_NOT_D			0
#घोषणा BKGD_MIX_ZERO			1
#घोषणा BKGD_MIX_ONE			2
#घोषणा BKGD_MIX_D			3
#घोषणा BKGD_MIX_NOT_S			4
#घोषणा BKGD_MIX_D_XOR_S		5
#घोषणा BKGD_MIX_NOT_D_XOR_S		6
#घोषणा BKGD_MIX_S			7
#घोषणा BKGD_MIX_NOT_D_OR_NOT_S		8
#घोषणा BKGD_MIX_D_OR_NOT_S		9
#घोषणा BKGD_MIX_NOT_D_OR_S		10
#घोषणा BKGD_MIX_D_OR_S			11
#घोषणा BKGD_MIX_D_AND_S		12
#घोषणा BKGD_MIX_NOT_D_AND_S		13
#घोषणा BKGD_MIX_D_AND_NOT_S		14
#घोषणा BKGD_MIX_NOT_D_AND_NOT_S	15
#घोषणा BKGD_MIX_D_PLUS_S_DIV2		0x17
#घोषणा FRGD_MIX_NOT_D			0
#घोषणा FRGD_MIX_ZERO			0x10000
#घोषणा FRGD_MIX_ONE			0x20000
#घोषणा FRGD_MIX_D			0x30000
#घोषणा FRGD_MIX_NOT_S			0x40000
#घोषणा FRGD_MIX_D_XOR_S		0x50000
#घोषणा FRGD_MIX_NOT_D_XOR_S		0x60000
#घोषणा FRGD_MIX_S			0x70000
#घोषणा FRGD_MIX_NOT_D_OR_NOT_S		0x80000
#घोषणा FRGD_MIX_D_OR_NOT_S		0x90000
#घोषणा FRGD_MIX_NOT_D_OR_S		0xa0000
#घोषणा FRGD_MIX_D_OR_S			0xb0000
#घोषणा FRGD_MIX_D_AND_S		0xc0000
#घोषणा FRGD_MIX_NOT_D_AND_S		0xd0000
#घोषणा FRGD_MIX_D_AND_NOT_S		0xe0000
#घोषणा FRGD_MIX_NOT_D_AND_NOT_S	0xf0000
#घोषणा FRGD_MIX_D_PLUS_S_DIV2		0x170000

/* DP_SRC रेजिस्टर स्थिरants */
#घोषणा BKGD_SRC_BKGD_CLR	0
#घोषणा BKGD_SRC_FRGD_CLR	1
#घोषणा BKGD_SRC_HOST		2
#घोषणा BKGD_SRC_BLIT		3
#घोषणा BKGD_SRC_PATTERN	4
#घोषणा FRGD_SRC_BKGD_CLR	0
#घोषणा FRGD_SRC_FRGD_CLR	0x100
#घोषणा FRGD_SRC_HOST		0x200
#घोषणा FRGD_SRC_BLIT		0x300
#घोषणा FRGD_SRC_PATTERN	0x400
#घोषणा MONO_SRC_ONE		0
#घोषणा MONO_SRC_PATTERN	0x10000
#घोषणा MONO_SRC_HOST		0x20000
#घोषणा MONO_SRC_BLIT		0x30000

/* CLR_CMP_CNTL रेजिस्टर स्थिरants */
#घोषणा COMPARE_FALSE		0
#घोषणा COMPARE_TRUE		1
#घोषणा COMPARE_NOT_EQUAL	4
#घोषणा COMPARE_EQUAL		5
#घोषणा COMPARE_DESTINATION	0
#घोषणा COMPARE_SOURCE		0x1000000

/* FIFO_STAT रेजिस्टर स्थिरants */
#घोषणा FIFO_ERR		0x80000000

/* CONTEXT_LOAD_CNTL स्थिरants */
#घोषणा CONTEXT_NO_LOAD			0
#घोषणा CONTEXT_LOAD			0x10000
#घोषणा CONTEXT_LOAD_AND_DO_FILL	0x20000
#घोषणा CONTEXT_LOAD_AND_DO_LINE	0x30000
#घोषणा CONTEXT_EXECUTE			0
#घोषणा CONTEXT_CMD_DISABLE		0x80000000

/* GUI_STAT रेजिस्टर स्थिरants */
#घोषणा ENGINE_IDLE			0
#घोषणा ENGINE_BUSY			1
#घोषणा SCISSOR_LEFT_FLAG		0x10
#घोषणा SCISSOR_RIGHT_FLAG		0x20
#घोषणा SCISSOR_TOP_FLAG		0x40
#घोषणा SCISSOR_BOTTOM_FLAG		0x80

/* ATI VGA Extended Regsiters */
#घोषणा sioATIEXT		0x1ce
#घोषणा bioATIEXT		0x3ce

#घोषणा ATI2E			0xae
#घोषणा ATI32			0xb2
#घोषणा ATI36			0xb6

/* VGA Graphics Controller Registers */
#घोषणा R_GENMO			0x3cc
#घोषणा VGAGRA			0x3ce
#घोषणा GRA06			0x06

/* VGA Seququencer Registers */
#घोषणा VGASEQ			0x3c4
#घोषणा SEQ02			0x02
#घोषणा SEQ04			0x04

#घोषणा MACH64_MAX_X		ENGINE_MAX_X
#घोषणा MACH64_MAX_Y		ENGINE_MAX_Y

#घोषणा INC_X			0x0020
#घोषणा INC_Y			0x0080

#घोषणा RGB16_555		0x0000
#घोषणा RGB16_565		0x0040
#घोषणा RGB16_655		0x0080
#घोषणा RGB16_664		0x00c0

#घोषणा POLY_TEXT_TYPE		0x0001
#घोषणा IMAGE_TEXT_TYPE		0x0002
#घोषणा TEXT_TYPE_8_BIT		0x0004
#घोषणा TEXT_TYPE_16_BIT	0x0008
#घोषणा POLY_TEXT_TYPE_8	(POLY_TEXT_TYPE | TEXT_TYPE_8_BIT)
#घोषणा IMAGE_TEXT_TYPE_8	(IMAGE_TEXT_TYPE | TEXT_TYPE_8_BIT)
#घोषणा POLY_TEXT_TYPE_16	(POLY_TEXT_TYPE | TEXT_TYPE_16_BIT)
#घोषणा IMAGE_TEXT_TYPE_16	(IMAGE_TEXT_TYPE | TEXT_TYPE_16_BIT)

#घोषणा MACH64_NUM_CLOCKS	16
#घोषणा MACH64_NUM_FREQS	50

/* Power Management रेजिस्टर स्थिरants (LT & LT Pro) */
#घोषणा PWR_MGT_ON		0x00000001
#घोषणा PWR_MGT_MODE_MASK	0x00000006
#घोषणा AUTO_PWR_UP		0x00000008
#घोषणा USE_F32KHZ		0x00000400
#घोषणा TRISTATE_MEM_EN		0x00000800
#घोषणा SELF_REFRESH		0x00000080
#घोषणा PWR_BLON		0x02000000
#घोषणा STANDBY_NOW		0x10000000
#घोषणा SUSPEND_NOW		0x20000000
#घोषणा PWR_MGT_STATUS_MASK	0xC0000000
#घोषणा PWR_MGT_STATUS_SUSPEND	0x80000000

/* PM Mode स्थिरants  */
#घोषणा PWR_MGT_MODE_PIN	0x00000000
#घोषणा PWR_MGT_MODE_REG	0x00000002
#घोषणा PWR_MGT_MODE_TIMER	0x00000004
#घोषणा PWR_MGT_MODE_PCI	0x00000006

/* LCD रेजिस्टरs (LT Pro) */

/* LCD Index रेजिस्टर */
#घोषणा LCD_INDEX_MASK		0x0000003F
#घोषणा LCD_DISPLAY_DIS		0x00000100
#घोषणा LCD_SRC_SEL		0x00000200
#घोषणा CRTC2_DISPLAY_DIS	0x00000400

/* LCD रेजिस्टर indices */
#घोषणा CNFG_PANEL		0x00
#घोषणा LCD_GEN_CNTL		0x01
#घोषणा DSTN_CONTROL		0x02
#घोषणा HFB_PITCH_ADDR		0x03
#घोषणा HORZ_STRETCHING		0x04
#घोषणा VERT_STRETCHING		0x05
#घोषणा EXT_VERT_STRETCH	0x06
#घोषणा LT_GIO			0x07
#घोषणा POWER_MANAGEMENT	0x08
#घोषणा ZVGPIO			0x09
#घोषणा ICON_CLR0		0x0A
#घोषणा ICON_CLR1		0x0B
#घोषणा ICON_OFFSET		0x0C
#घोषणा ICON_HORZ_VERT_POSN	0x0D
#घोषणा ICON_HORZ_VERT_OFF	0x0E
#घोषणा ICON2_CLR0		0x0F
#घोषणा ICON2_CLR1		0x10
#घोषणा ICON2_OFFSET		0x11
#घोषणा ICON2_HORZ_VERT_POSN	0x12
#घोषणा ICON2_HORZ_VERT_OFF	0x13
#घोषणा LCD_MISC_CNTL		0x14
#घोषणा APC_CNTL		0x1C
#घोषणा POWER_MANAGEMENT_2	0x1D
#घोषणा ALPHA_BLENDING		0x25
#घोषणा PORTRAIT_GEN_CNTL	0x26
#घोषणा APC_CTRL_IO		0x27
#घोषणा TEST_IO			0x28
#घोषणा TEST_OUTPUTS		0x29
#घोषणा DP1_MEM_ACCESS		0x2A
#घोषणा DP0_MEM_ACCESS		0x2B
#घोषणा DP0_DEBUG_A		0x2C
#घोषणा DP0_DEBUG_B		0x2D
#घोषणा DP1_DEBUG_A		0x2E
#घोषणा DP1_DEBUG_B		0x2F
#घोषणा DPCTRL_DEBUG_A		0x30
#घोषणा DPCTRL_DEBUG_B		0x31
#घोषणा MEMBLK_DEBUG		0x32
#घोषणा APC_LUT_AB		0x33
#घोषणा APC_LUT_CD		0x34
#घोषणा APC_LUT_EF		0x35
#घोषणा APC_LUT_GH		0x36
#घोषणा APC_LUT_IJ		0x37
#घोषणा APC_LUT_KL		0x38
#घोषणा APC_LUT_MN		0x39
#घोषणा APC_LUT_OP		0x3A

/* Values in LCD_GEN_CTRL */
#घोषणा CRT_ON                          0x00000001ul
#घोषणा LCD_ON                          0x00000002ul
#घोषणा HORZ_DIVBY2_EN                  0x00000004ul
#घोषणा DONT_DS_ICON                    0x00000008ul
#घोषणा LOCK_8DOT                       0x00000010ul
#घोषणा ICON_ENABLE                     0x00000020ul
#घोषणा DONT_SHADOW_VPAR                0x00000040ul
#घोषणा V2CLK_PM_EN                     0x00000080ul
#घोषणा RST_FM                          0x00000100ul
#घोषणा DISABLE_PCLK_RESET              0x00000200ul	/* XC/XL */
#घोषणा DIS_HOR_CRT_DIVBY2              0x00000400ul
#घोषणा SCLK_SEL                        0x00000800ul
#घोषणा SCLK_DELAY                      0x0000f000ul
#घोषणा TVCLK_PM_EN                     0x00010000ul
#घोषणा VCLK_DAC_PM_EN                  0x00020000ul
#घोषणा VCLK_LCD_OFF                    0x00040000ul
#घोषणा SELECT_WAIT_4MS                 0x00080000ul
#घोषणा XTALIN_PM_EN                    0x00080000ul	/* XC/XL */
#घोषणा V2CLK_DAC_PM_EN                 0x00100000ul
#घोषणा LVDS_EN                         0x00200000ul
#घोषणा LVDS_PLL_EN                     0x00400000ul
#घोषणा LVDS_PLL_RESET                  0x00800000ul
#घोषणा LVDS_RESERVED_BITS              0x07000000ul
#घोषणा CRTC_RW_SELECT                  0x08000000ul	/* LTPro */
#घोषणा USE_SHADOWED_VEND               0x10000000ul
#घोषणा USE_SHADOWED_ROWCUR             0x20000000ul
#घोषणा SHADOW_EN                       0x40000000ul
#घोषणा SHADOW_RW_EN                  	0x80000000ul

#घोषणा LCD_SET_PRIMARY_MASK            0x07FFFBFBul

/* Values in HORZ_STRETCHING */
#घोषणा HORZ_STRETCH_BLEND		0x00000ffful
#घोषणा HORZ_STRETCH_RATIO		0x0000fffful
#घोषणा HORZ_STRETCH_LOOP		0x00070000ul
#घोषणा HORZ_STRETCH_LOOP09		0x00000000ul
#घोषणा HORZ_STRETCH_LOOP11		0x00010000ul
#घोषणा HORZ_STRETCH_LOOP12		0x00020000ul
#घोषणा HORZ_STRETCH_LOOP14		0x00030000ul
#घोषणा HORZ_STRETCH_LOOP15		0x00040000ul
/*	?				0x00050000ul */
/*	?				0x00060000ul */
/*	?				0x00070000ul */
/*	?				0x00080000ul */
#घोषणा HORZ_PANEL_SIZE			0x0ff00000ul	/* XC/XL */
/*	?				0x10000000ul */
#घोषणा AUTO_HORZ_RATIO			0x20000000ul	/* XC/XL */
#घोषणा HORZ_STRETCH_MODE		0x40000000ul
#घोषणा HORZ_STRETCH_EN			0x80000000ul

/* Values in VERT_STRETCHING */
#घोषणा VERT_STRETCH_RATIO0		0x000003fful
#घोषणा VERT_STRETCH_RATIO1		0x000ffc00ul
#घोषणा VERT_STRETCH_RATIO2		0x3ff00000ul
#घोषणा VERT_STRETCH_USE0		0x40000000ul
#घोषणा VERT_STRETCH_EN			0x80000000ul

/* Values in EXT_VERT_STRETCH */
#घोषणा VERT_STRETCH_RATIO3		0x000003fful
#घोषणा FORCE_DAC_DATA			0x000000fful
#घोषणा FORCE_DAC_DATA_SEL		0x00000300ul
#घोषणा VERT_STRETCH_MODE		0x00000400ul
#घोषणा VERT_PANEL_SIZE			0x003ff800ul
#घोषणा AUTO_VERT_RATIO			0x00400000ul
#घोषणा USE_AUTO_FP_POS			0x00800000ul
#घोषणा USE_AUTO_LCD_VSYNC		0x01000000ul
/*	?				0xfe000000ul */

/* Values in LCD_MISC_CNTL */
#घोषणा BIAS_MOD_LEVEL_MASK		0x0000ff00
#घोषणा BIAS_MOD_LEVEL_SHIFT		8
#घोषणा BLMOD_EN			0x00010000
#घोषणा BIASMOD_EN			0x00020000

#पूर्ण_अगर				/* REGMACH64_H */
