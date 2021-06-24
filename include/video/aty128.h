<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  $Id: aty128.h,v 1.1 1999/10/12 11:00:40 geert Exp $
 *  linux/drivers/video/aty128.h
 *  Register definitions क्रम ATI Rage128 boards
 *
 *  Anthony Tong <atong@uiuc.edu>, 1999
 *  Brad Douglas <brad@neruo.com>, 2000
 */

#अगर_अघोषित REG_RAGE128_H
#घोषणा REG_RAGE128_H

#घोषणा CLOCK_CNTL_INDEX			0x0008
#घोषणा CLOCK_CNTL_DATA				0x000c
#घोषणा BIOS_0_SCRATCH				0x0010
#घोषणा BUS_CNTL				0x0030
#घोषणा BUS_CNTL1				0x0034
#घोषणा GEN_INT_CNTL				0x0040
#घोषणा CRTC_GEN_CNTL				0x0050
#घोषणा CRTC_EXT_CNTL				0x0054
#घोषणा DAC_CNTL				0x0058
#घोषणा I2C_CNTL_1				0x0094
#घोषणा PALETTE_INDEX				0x00b0
#घोषणा PALETTE_DATA				0x00b4
#घोषणा CNFG_CNTL				0x00e0
#घोषणा GEN_RESET_CNTL				0x00f0
#घोषणा CNFG_MEMSIZE				0x00f8
#घोषणा MEM_CNTL				0x0140
#घोषणा MEM_POWER_MISC				0x015c
#घोषणा AGP_BASE				0x0170
#घोषणा AGP_CNTL				0x0174
#घोषणा AGP_APER_OFFSET				0x0178
#घोषणा PCI_GART_PAGE				0x017c
#घोषणा PC_NGUI_MODE				0x0180
#घोषणा PC_NGUI_CTLSTAT				0x0184
#घोषणा MPP_TB_CONFIG				0x01C0
#घोषणा MPP_GP_CONFIG				0x01C8
#घोषणा VIPH_CONTROL				0x01D0
#घोषणा CRTC_H_TOTAL_DISP			0x0200
#घोषणा CRTC_H_SYNC_STRT_WID			0x0204
#घोषणा CRTC_V_TOTAL_DISP			0x0208
#घोषणा CRTC_V_SYNC_STRT_WID			0x020c
#घोषणा CRTC_VLINE_CRNT_VLINE			0x0210
#घोषणा CRTC_CRNT_FRAME				0x0214
#घोषणा CRTC_GUI_TRIG_VLINE			0x0218
#घोषणा CRTC_OFFSET				0x0224
#घोषणा CRTC_OFFSET_CNTL			0x0228
#घोषणा CRTC_PITCH				0x022c
#घोषणा OVR_CLR					0x0230
#घोषणा OVR_WID_LEFT_RIGHT			0x0234
#घोषणा OVR_WID_TOP_BOTTOM			0x0238
#घोषणा LVDS_GEN_CNTL				0x02d0
#घोषणा DDA_CONFIG				0x02e0
#घोषणा DDA_ON_OFF				0x02e4
#घोषणा VGA_DDA_CONFIG				0x02e8
#घोषणा VGA_DDA_ON_OFF				0x02ec
#घोषणा CRTC2_H_TOTAL_DISP			0x0300
#घोषणा CRTC2_H_SYNC_STRT_WID			0x0304
#घोषणा CRTC2_V_TOTAL_DISP			0x0308
#घोषणा CRTC2_V_SYNC_STRT_WID			0x030c
#घोषणा CRTC2_VLINE_CRNT_VLINE			0x0310
#घोषणा CRTC2_CRNT_FRAME			0x0314
#घोषणा CRTC2_GUI_TRIG_VLINE			0x0318
#घोषणा CRTC2_OFFSET				0x0324
#घोषणा CRTC2_OFFSET_CNTL			0x0328
#घोषणा CRTC2_PITCH				0x032c
#घोषणा DDA2_CONFIG				0x03e0
#घोषणा DDA2_ON_OFF				0x03e4
#घोषणा CRTC2_GEN_CNTL				0x03f8
#घोषणा CRTC2_STATUS				0x03fc
#घोषणा OV0_SCALE_CNTL				0x0420
#घोषणा SUBPIC_CNTL				0x0540
#घोषणा PM4_BUFFER_OFFSET			0x0700
#घोषणा PM4_BUFFER_CNTL				0x0704
#घोषणा PM4_BUFFER_WM_CNTL			0x0708
#घोषणा PM4_BUFFER_DL_RPTR_ADDR			0x070c
#घोषणा PM4_BUFFER_DL_RPTR			0x0710
#घोषणा PM4_BUFFER_DL_WPTR			0x0714
#घोषणा PM4_VC_FPU_SETUP			0x071c
#घोषणा PM4_FPU_CNTL				0x0720
#घोषणा PM4_VC_FORMAT				0x0724
#घोषणा PM4_VC_CNTL				0x0728
#घोषणा PM4_VC_I01				0x072c
#घोषणा PM4_VC_VLOFF				0x0730
#घोषणा PM4_VC_VLSIZE				0x0734
#घोषणा PM4_IW_INDOFF				0x0738
#घोषणा PM4_IW_INDSIZE				0x073c
#घोषणा PM4_FPU_FPX0				0x0740
#घोषणा PM4_FPU_FPY0				0x0744
#घोषणा PM4_FPU_FPX1				0x0748
#घोषणा PM4_FPU_FPY1				0x074c
#घोषणा PM4_FPU_FPX2				0x0750
#घोषणा PM4_FPU_FPY2				0x0754
#घोषणा PM4_FPU_FPY3				0x0758
#घोषणा PM4_FPU_FPY4				0x075c
#घोषणा PM4_FPU_FPY5				0x0760
#घोषणा PM4_FPU_FPY6				0x0764
#घोषणा PM4_FPU_FPR				0x0768
#घोषणा PM4_FPU_FPG				0x076c
#घोषणा PM4_FPU_FPB				0x0770
#घोषणा PM4_FPU_FPA				0x0774
#घोषणा PM4_FPU_INTXY0				0x0780
#घोषणा PM4_FPU_INTXY1				0x0784
#घोषणा PM4_FPU_INTXY2				0x0788
#घोषणा PM4_FPU_INTARGB				0x078c
#घोषणा PM4_FPU_FPTWICEAREA			0x0790
#घोषणा PM4_FPU_DMAJOR01			0x0794
#घोषणा PM4_FPU_DMAJOR12			0x0798
#घोषणा PM4_FPU_DMAJOR02			0x079c
#घोषणा PM4_FPU_STAT				0x07a0
#घोषणा PM4_STAT				0x07b8
#घोषणा PM4_TEST_CNTL				0x07d0
#घोषणा PM4_MICROCODE_ADDR			0x07d4
#घोषणा PM4_MICROCODE_RADDR			0x07d8
#घोषणा PM4_MICROCODE_DATAH			0x07dc
#घोषणा PM4_MICROCODE_DATAL			0x07e0
#घोषणा PM4_CMDFIFO_ADDR			0x07e4
#घोषणा PM4_CMDFIFO_DATAH			0x07e8
#घोषणा PM4_CMDFIFO_DATAL			0x07ec
#घोषणा PM4_BUFFER_ADDR				0x07f0
#घोषणा PM4_BUFFER_DATAH			0x07f4
#घोषणा PM4_BUFFER_DATAL			0x07f8
#घोषणा PM4_MICRO_CNTL				0x07fc
#घोषणा CAP0_TRIG_CNTL				0x0950
#घोषणा CAP1_TRIG_CNTL				0x09c0

/******************************************************************************
 *                  GUI Block Memory Mapped Registers                         *
 *                     These रेजिस्टरs are FIFOed.                            *
 *****************************************************************************/
#घोषणा PM4_FIFO_DATA_EVEN			0x1000
#घोषणा PM4_FIFO_DATA_ODD			0x1004

#घोषणा DST_OFFSET				0x1404
#घोषणा DST_PITCH				0x1408
#घोषणा DST_WIDTH				0x140c
#घोषणा DST_HEIGHT				0x1410
#घोषणा SRC_X					0x1414
#घोषणा SRC_Y					0x1418
#घोषणा DST_X					0x141c
#घोषणा DST_Y					0x1420
#घोषणा SRC_PITCH_OFFSET			0x1428
#घोषणा DST_PITCH_OFFSET			0x142c
#घोषणा SRC_Y_X					0x1434
#घोषणा DST_Y_X					0x1438
#घोषणा DST_HEIGHT_WIDTH			0x143c
#घोषणा DP_GUI_MASTER_CNTL			0x146c
#घोषणा BRUSH_SCALE				0x1470
#घोषणा BRUSH_Y_X				0x1474
#घोषणा DP_BRUSH_BKGD_CLR			0x1478
#घोषणा DP_BRUSH_FRGD_CLR			0x147c
#घोषणा DST_WIDTH_X				0x1588
#घोषणा DST_HEIGHT_WIDTH_8			0x158c
#घोषणा SRC_X_Y					0x1590
#घोषणा DST_X_Y					0x1594
#घोषणा DST_WIDTH_HEIGHT			0x1598
#घोषणा DST_WIDTH_X_INCY			0x159c
#घोषणा DST_HEIGHT_Y				0x15a0
#घोषणा DST_X_SUB				0x15a4
#घोषणा DST_Y_SUB				0x15a8
#घोषणा SRC_OFFSET				0x15ac
#घोषणा SRC_PITCH				0x15b0
#घोषणा DST_HEIGHT_WIDTH_BW			0x15b4
#घोषणा CLR_CMP_CNTL				0x15c0
#घोषणा CLR_CMP_CLR_SRC				0x15c4
#घोषणा CLR_CMP_CLR_DST				0x15c8
#घोषणा CLR_CMP_MASK				0x15cc
#घोषणा DP_SRC_FRGD_CLR				0x15d8
#घोषणा DP_SRC_BKGD_CLR				0x15dc
#घोषणा DST_BRES_ERR				0x1628
#घोषणा DST_BRES_INC				0x162c
#घोषणा DST_BRES_DEC				0x1630
#घोषणा DST_BRES_LNTH				0x1634
#घोषणा DST_BRES_LNTH_SUB			0x1638
#घोषणा SC_LEFT					0x1640
#घोषणा SC_RIGHT				0x1644
#घोषणा SC_TOP					0x1648
#घोषणा SC_BOTTOM				0x164c
#घोषणा SRC_SC_RIGHT				0x1654
#घोषणा SRC_SC_BOTTOM				0x165c
#घोषणा GUI_DEBUG0				0x16a0
#घोषणा GUI_DEBUG1				0x16a4
#घोषणा GUI_TIMEOUT				0x16b0
#घोषणा GUI_TIMEOUT0				0x16b4
#घोषणा GUI_TIMEOUT1				0x16b8
#घोषणा GUI_PROBE				0x16bc
#घोषणा DP_CNTL					0x16c0
#घोषणा DP_DATATYPE				0x16c4
#घोषणा DP_MIX					0x16c8
#घोषणा DP_WRITE_MASK				0x16cc
#घोषणा DP_CNTL_Xसूची_Yसूची_YMAJOR		0x16d0
#घोषणा DEFAULT_OFFSET				0x16e0
#घोषणा DEFAULT_PITCH				0x16e4
#घोषणा DEFAULT_SC_BOTTOM_RIGHT			0x16e8
#घोषणा SC_TOP_LEFT				0x16ec
#घोषणा SC_BOTTOM_RIGHT				0x16f0
#घोषणा SRC_SC_BOTTOM_RIGHT			0x16f4
#घोषणा WAIT_UNTIL				0x1720
#घोषणा CACHE_CNTL				0x1724
#घोषणा GUI_STAT				0x1740
#घोषणा PC_GUI_MODE				0x1744
#घोषणा PC_GUI_CTLSTAT				0x1748
#घोषणा PC_DEBUG_MODE				0x1760
#घोषणा BRES_DST_ERR_DEC			0x1780
#घोषणा TRAIL_BRES_T12_ERR_DEC			0x1784
#घोषणा TRAIL_BRES_T12_INC			0x1788
#घोषणा DP_T12_CNTL				0x178c
#घोषणा DST_BRES_T1_LNTH			0x1790
#घोषणा DST_BRES_T2_LNTH			0x1794
#घोषणा SCALE_SRC_HEIGHT_WIDTH			0x1994
#घोषणा SCALE_OFFSET_0				0x1998
#घोषणा SCALE_PITCH				0x199c
#घोषणा SCALE_X_INC				0x19a0
#घोषणा SCALE_Y_INC				0x19a4
#घोषणा SCALE_HACC				0x19a8
#घोषणा SCALE_VACC				0x19ac
#घोषणा SCALE_DST_X_Y				0x19b0
#घोषणा SCALE_DST_HEIGHT_WIDTH			0x19b4
#घोषणा SCALE_3D_CNTL				0x1a00
#घोषणा SCALE_3D_DATATYPE			0x1a20
#घोषणा SETUP_CNTL				0x1bc4
#घोषणा SOLID_COLOR				0x1bc8
#घोषणा WINDOW_XY_OFFSET			0x1bcc
#घोषणा DRAW_LINE_POINT				0x1bd0
#घोषणा SETUP_CNTL_PM4				0x1bd4
#घोषणा DST_PITCH_OFFSET_C			0x1c80
#घोषणा DP_GUI_MASTER_CNTL_C			0x1c84
#घोषणा SC_TOP_LEFT_C				0x1c88
#घोषणा SC_BOTTOM_RIGHT_C			0x1c8c

#घोषणा CLR_CMP_MASK_3D				0x1A28
#घोषणा MISC_3D_STATE_CNTL_REG			0x1CA0
#घोषणा MC_SRC1_CNTL				0x19D8
#घोषणा TEX_CNTL				0x1800

/* CONSTANTS */
#घोषणा GUI_ACTIVE				0x80000000
#घोषणा ENGINE_IDLE				0x0

#घोषणा PLL_WR_EN				0x00000080

#घोषणा CLK_PIN_CNTL				0x0001
#घोषणा PPLL_CNTL				0x0002
#घोषणा PPLL_REF_DIV				0x0003
#घोषणा PPLL_DIV_0				0x0004
#घोषणा PPLL_DIV_1				0x0005
#घोषणा PPLL_DIV_2				0x0006
#घोषणा PPLL_DIV_3				0x0007
#घोषणा VCLK_ECP_CNTL				0x0008
#घोषणा HTOTAL_CNTL				0x0009
#घोषणा X_MPLL_REF_FB_DIV			0x000a
#घोषणा XPLL_CNTL				0x000b
#घोषणा XDLL_CNTL				0x000c
#घोषणा XCLK_CNTL				0x000d
#घोषणा MPLL_CNTL				0x000e
#घोषणा MCLK_CNTL				0x000f
#घोषणा AGP_PLL_CNTL				0x0010
#घोषणा FCP_CNTL				0x0012
#घोषणा PLL_TEST_CNTL				0x0013
#घोषणा P2PLL_CNTL				0x002a
#घोषणा P2PLL_REF_DIV				0x002b
#घोषणा P2PLL_DIV_0				0x002b
#घोषणा POWER_MANAGEMENT			0x002f

#घोषणा PPLL_RESET				0x01
#घोषणा PPLL_ATOMIC_UPDATE_EN			0x10000
#घोषणा PPLL_VGA_ATOMIC_UPDATE_EN		0x20000
#घोषणा PPLL_REF_DIV_MASK			0x3FF
#घोषणा PPLL_FB3_DIV_MASK			0x7FF
#घोषणा PPLL_POST3_DIV_MASK			0x70000
#घोषणा PPLL_ATOMIC_UPDATE_R			0x8000
#घोषणा PPLL_ATOMIC_UPDATE_W			0x8000
#घोषणा MEM_CFG_TYPE_MASK			0x3
#घोषणा XCLK_SRC_SEL_MASK			0x7
#घोषणा XPLL_FB_DIV_MASK			0xFF00
#घोषणा X_MPLL_REF_DIV_MASK			0xFF

/* CRTC control values (CRTC_GEN_CNTL) */
#घोषणा CRTC_CSYNC_EN				0x00000010

#घोषणा CRTC2_DBL_SCAN_EN			0x00000001
#घोषणा CRTC2_DISPLAY_DIS			0x00800000
#घोषणा CRTC2_FIFO_EXTSENSE			0x00200000
#घोषणा CRTC2_ICON_EN				0x00100000
#घोषणा CRTC2_CUR_EN				0x00010000
#घोषणा CRTC2_EN				0x02000000
#घोषणा CRTC2_DISP_REQ_EN_B			0x04000000

#घोषणा CRTC_PIX_WIDTH_MASK			0x00000700
#घोषणा CRTC_PIX_WIDTH_4BPP			0x00000100
#घोषणा CRTC_PIX_WIDTH_8BPP			0x00000200
#घोषणा CRTC_PIX_WIDTH_15BPP			0x00000300
#घोषणा CRTC_PIX_WIDTH_16BPP			0x00000400
#घोषणा CRTC_PIX_WIDTH_24BPP			0x00000500
#घोषणा CRTC_PIX_WIDTH_32BPP			0x00000600

/* DAC_CNTL bit स्थिरants */
#घोषणा DAC_8BIT_EN				0x00000100
#घोषणा DAC_MASK				0xFF000000
#घोषणा DAC_BLANKING				0x00000004
#घोषणा DAC_RANGE_CNTL				0x00000003
#घोषणा DAC_CLK_SEL				0x00000010
#घोषणा DAC_PALETTE_ACCESS_CNTL			0x00000020
#घोषणा DAC_PALETTE2_SNOOP_EN			0x00000040
#घोषणा DAC_PDWN				0x00008000

/* CRTC_EXT_CNTL */
#घोषणा CRT_CRTC_ON				0x00008000

/* GEN_RESET_CNTL bit स्थिरants */
#घोषणा SOFT_RESET_GUI				0x00000001
#घोषणा SOFT_RESET_VCLK				0x00000100
#घोषणा SOFT_RESET_PCLK				0x00000200
#घोषणा SOFT_RESET_ECP				0x00000400
#घोषणा SOFT_RESET_DISPENG_XCLK			0x00000800

/* PC_GUI_CTLSTAT bit स्थिरants */
#घोषणा PC_BUSY_INIT				0x10000000
#घोषणा PC_BUSY_GUI				0x20000000
#घोषणा PC_BUSY_NGUI				0x40000000
#घोषणा PC_BUSY					0x80000000

#घोषणा BUS_MASTER_DIS				0x00000040
#घोषणा PM4_BUFFER_CNTL_NONPM4			0x00000000

/* DP_DATATYPE bit स्थिरants */
#घोषणा DST_8BPP				0x00000002
#घोषणा DST_15BPP				0x00000003
#घोषणा DST_16BPP				0x00000004
#घोषणा DST_24BPP				0x00000005
#घोषणा DST_32BPP				0x00000006

#घोषणा BRUSH_SOLIDCOLOR			0x00000d00

/* DP_GUI_MASTER_CNTL bit स्थिरants */
#घोषणा	GMC_SRC_PITCH_OFFSET_DEFAULT		0x00000000
#घोषणा GMC_DST_PITCH_OFFSET_DEFAULT		0x00000000
#घोषणा GMC_SRC_CLIP_DEFAULT			0x00000000
#घोषणा GMC_DST_CLIP_DEFAULT			0x00000000
#घोषणा GMC_BRUSH_SOLIDCOLOR			0x000000d0
#घोषणा GMC_SRC_DSTCOLOR			0x00003000
#घोषणा GMC_BYTE_ORDER_MSB_TO_LSB		0x00000000
#घोषणा GMC_DP_SRC_RECT				0x02000000
#घोषणा GMC_3D_FCN_EN_CLR			0x00000000
#घोषणा GMC_AUX_CLIP_CLEAR			0x20000000
#घोषणा GMC_DST_CLR_CMP_FCN_CLEAR		0x10000000
#घोषणा GMC_WRITE_MASK_SET			0x40000000
#घोषणा GMC_DP_CONVERSION_TEMP_6500		0x00000000

/* DP_GUI_MASTER_CNTL ROP3 named स्थिरants */
#घोषणा	ROP3_PATCOPY				0x00f00000
#घोषणा ROP3_SRCCOPY				0x00cc0000

#घोषणा SRC_DSTCOLOR				0x00030000

/* DP_CNTL bit स्थिरants */
#घोषणा DST_X_RIGHT_TO_LEFT			0x00000000
#घोषणा DST_X_LEFT_TO_RIGHT			0x00000001
#घोषणा DST_Y_BOTTOM_TO_TOP			0x00000000
#घोषणा DST_Y_TOP_TO_BOTTOM			0x00000002
#घोषणा DST_X_MAJOR				0x00000000
#घोषणा DST_Y_MAJOR				0x00000004
#घोषणा DST_X_TILE				0x00000008
#घोषणा DST_Y_TILE				0x00000010
#घोषणा DST_LAST_PEL				0x00000020
#घोषणा DST_TRAIL_X_RIGHT_TO_LEFT		0x00000000
#घोषणा DST_TRAIL_X_LEFT_TO_RIGHT		0x00000040
#घोषणा DST_TRAP_FILL_RIGHT_TO_LEFT		0x00000000
#घोषणा DST_TRAP_FILL_LEFT_TO_RIGHT		0x00000080
#घोषणा DST_BRES_SIGN				0x00000100
#घोषणा DST_HOST_BIG_ENDIAN_EN			0x00000200
#घोषणा DST_POLYLINE_NONLAST			0x00008000
#घोषणा DST_RASTER_STALL			0x00010000
#घोषणा DST_POLY_EDGE				0x00040000

/* DP_MIX bit स्थिरants */
#घोषणा DP_SRC_RECT				0x00000200
#घोषणा DP_SRC_HOST				0x00000300
#घोषणा DP_SRC_HOST_BYTEALIGN			0x00000400

/* LVDS_GEN_CNTL स्थिरants */
#घोषणा LVDS_BL_MOD_LEVEL_MASK			0x0000ff00
#घोषणा LVDS_BL_MOD_LEVEL_SHIFT			8
#घोषणा LVDS_BL_MOD_EN				0x00010000
#घोषणा LVDS_DIGION				0x00040000
#घोषणा LVDS_BLON				0x00080000
#घोषणा LVDS_ON					0x00000001
#घोषणा LVDS_DISPLAY_DIS			0x00000002
#घोषणा LVDS_PANEL_TYPE_2PIX_PER_CLK		0x00000004
#घोषणा LVDS_PANEL_24BITS_TFT			0x00000008
#घोषणा LVDS_FRAME_MOD_NO			0x00000000
#घोषणा LVDS_FRAME_MOD_2_LEVELS			0x00000010
#घोषणा LVDS_FRAME_MOD_4_LEVELS			0x00000020
#घोषणा LVDS_RST_FM				0x00000040
#घोषणा LVDS_EN					0x00000080

/* CRTC2_GEN_CNTL स्थिरants */
#घोषणा CRTC2_EN				0x02000000

/* POWER_MANAGEMENT स्थिरants */
#घोषणा PWR_MGT_ON				0x00000001
#घोषणा PWR_MGT_MODE_MASK			0x00000006
#घोषणा PWR_MGT_MODE_PIN			0x00000000
#घोषणा PWR_MGT_MODE_REGISTER			0x00000002
#घोषणा PWR_MGT_MODE_TIMER			0x00000004
#घोषणा PWR_MGT_MODE_PCI			0x00000006
#घोषणा PWR_MGT_AUTO_PWR_UP_EN			0x00000008
#घोषणा PWR_MGT_ACTIVITY_PIN_ON			0x00000010
#घोषणा PWR_MGT_STANDBY_POL			0x00000020
#घोषणा PWR_MGT_SUSPEND_POL			0x00000040
#घोषणा PWR_MGT_SELF_REFRESH			0x00000080
#घोषणा PWR_MGT_ACTIVITY_PIN_EN			0x00000100
#घोषणा PWR_MGT_KEYBD_SNOOP			0x00000200
#घोषणा PWR_MGT_TRISTATE_MEM_EN			0x00000800
#घोषणा PWR_MGT_SELW4MS				0x00001000
#घोषणा PWR_MGT_SLOWDOWN_MCLK			0x00002000

#घोषणा PMI_PMSCR_REG				0x60

/* used by ATI bug fix क्रम hardware ROM */
#घोषणा RAGE128_MPP_TB_CONFIG                   0x01c0

#पूर्ण_अगर				/* REG_RAGE128_H */
