<शैली गुरु>
/*
 * Permedia2 framebuffer driver definitions.
 * Copyright (c) 1998-2000 Ilario Nardinocchi (nardinoc@CS.UniBO.IT)
 * --------------------------------------------------------------------------
 * $Id: pm2fb.h,v 1.26 2000/09/19 00:11:53 illo Exp $
 * --------------------------------------------------------------------------
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित PM2FB_H
#घोषणा PM2FB_H

#घोषणा PM2_REFERENCE_CLOCK	14318			/* in KHz */
#घोषणा PM2_MAX_PIXCLOCK	230000			/* in KHz */
#घोषणा PM2_REGS_SIZE		0x10000

#घोषणा PM2TAG(r) (u32 )(((r)-0x8000)>>3)

/*****************************************************************************
 * Permedia2 रेजिस्टरs used in the framebuffer
 *****************************************************************************/
 
#घोषणा PM2R_RESET_STATUS				0x0000
#घोषणा PM2R_IN_FIFO_SPACE				0x0018
#घोषणा PM2R_OUT_FIFO_WORDS				0x0020
#घोषणा PM2R_APERTURE_ONE				0x0050
#घोषणा PM2R_APERTURE_TWO				0x0058
#घोषणा PM2R_FIFO_DISCON				0x0068
#घोषणा PM2R_CHIP_CONFIG				0x0070

#घोषणा PM2R_REBOOT					0x1000
#घोषणा PM2R_MEM_CONTROL				0x1040
#घोषणा PM2R_BOOT_ADDRESS				0x1080
#घोषणा PM2R_MEM_CONFIG					0x10c0
#घोषणा PM2R_BYPASS_WRITE_MASK				0x1100
#घोषणा PM2R_FRAMEBUFFER_WRITE_MASK			0x1140

#घोषणा PM2R_OUT_FIFO					0x2000

#घोषणा PM2R_SCREEN_BASE				0x3000
#घोषणा PM2R_SCREEN_STRIDE				0x3008
#घोषणा PM2R_H_TOTAL					0x3010
#घोषणा PM2R_HG_END					0x3018
#घोषणा PM2R_HB_END					0x3020
#घोषणा PM2R_HS_START					0x3028
#घोषणा PM2R_HS_END					0x3030
#घोषणा PM2R_V_TOTAL					0x3038
#घोषणा PM2R_VB_END					0x3040
#घोषणा PM2R_VS_START					0x3048
#घोषणा PM2R_VS_END					0x3050
#घोषणा PM2R_VIDEO_CONTROL				0x3058
#घोषणा PM2R_LINE_COUNT					0x3070
#घोषणा PM2R_FIFO_CONTROL				0x3078

#घोषणा PM2R_RD_PALETTE_WRITE_ADDRESS			0x4000
#घोषणा PM2R_RD_PALETTE_DATA				0x4008
#घोषणा PM2R_RD_PIXEL_MASK				0x4010
#घोषणा PM2R_RD_PALETTE_READ_ADDRESS			0x4018
#घोषणा PM2R_RD_CURSOR_COLOR_ADDRESS		        0x4020
#घोषणा PM2R_RD_CURSOR_COLOR_DATA		        0x4028
#घोषणा PM2R_RD_INDEXED_DATA				0x4050
#घोषणा PM2R_RD_CURSOR_DATA				0x4058
#घोषणा PM2R_RD_CURSOR_X_LSB				0x4060
#घोषणा PM2R_RD_CURSOR_X_MSB				0x4068
#घोषणा PM2R_RD_CURSOR_Y_LSB				0x4070
#घोषणा PM2R_RD_CURSOR_Y_MSB				0x4078

#घोषणा PM2R_START_X_DOM				0x8000
#घोषणा PM2R_D_X_DOM					0x8008
#घोषणा PM2R_START_X_SUB				0x8010
#घोषणा PM2R_D_X_SUB					0x8018
#घोषणा PM2R_START_Y					0x8020
#घोषणा PM2R_D_Y					0x8028
#घोषणा PM2R_COUNT					0x8030
#घोषणा PM2R_RENDER					0x8038
#घोषणा PM2R_BIT_MASK_PATTERN				0x8068
#घोषणा PM2R_RASTERIZER_MODE				0x80a0
#घोषणा PM2R_RECTANGLE_ORIGIN				0x80d0
#घोषणा PM2R_RECTANGLE_SIZE				0x80d8
#घोषणा PM2R_PACKED_DATA_LIMITS				0x8150
#घोषणा PM2R_SCISSOR_MODE				0x8180
#घोषणा PM2R_SCISSOR_MIN_XY				0x8188
#घोषणा PM2R_SCISSOR_MAX_XY				0x8190
#घोषणा PM2R_SCREEN_SIZE				0x8198
#घोषणा PM2R_AREA_STIPPLE_MODE				0x81a0
#घोषणा PM2R_WINDOW_ORIGIN				0x81c8
#घोषणा PM2R_TEXTURE_ADDRESS_MODE			0x8380
#घोषणा PM2R_TEXTURE_MAP_FORMAT				0x8588
#घोषणा PM2R_TEXTURE_DATA_FORMAT			0x8590
#घोषणा PM2R_TEXTURE_READ_MODE				0x8670
#घोषणा PM2R_TEXEL_LUT_MODE				0x8678
#घोषणा PM2R_TEXTURE_COLOR_MODE				0x8680
#घोषणा PM2R_FOG_MODE					0x8690
#घोषणा PM2R_TEXEL0					0x8760
#घोषणा PM2R_COLOR_DDA_MODE				0x87e0
#घोषणा PM2R_CONSTANT_COLOR				0x87e8
#घोषणा PM2R_ALPHA_BLEND_MODE				0x8810
#घोषणा PM2R_DITHER_MODE				0x8818
#घोषणा PM2R_FB_SOFT_WRITE_MASK				0x8820
#घोषणा PM2R_LOGICAL_OP_MODE				0x8828
#घोषणा PM2R_LB_READ_MODE				0x8880
#घोषणा PM2R_LB_READ_FORMAT				0x8888
#घोषणा PM2R_LB_SOURCE_OFFSET				0x8890
#घोषणा PM2R_LB_WINDOW_BASE				0x88b8
#घोषणा PM2R_LB_WRITE_FORMAT				0x88c8
#घोषणा PM2R_STENCIL_MODE				0x8988
#घोषणा PM2R_DEPTH_MODE					0x89a0
#घोषणा PM2R_FB_READ_MODE				0x8a80
#घोषणा PM2R_FB_SOURCE_OFFSET				0x8a88
#घोषणा PM2R_FB_PIXEL_OFFSET				0x8a90
#घोषणा PM2R_FB_WINDOW_BASE				0x8ab0
#घोषणा PM2R_FB_WRITE_MODE				0x8ab8
#घोषणा PM2R_FB_HARD_WRITE_MASK				0x8ac0
#घोषणा PM2R_FB_BLOCK_COLOR				0x8ac8
#घोषणा PM2R_FB_READ_PIXEL				0x8ad0
#घोषणा PM2R_FILTER_MODE				0x8c00
#घोषणा PM2R_SYNC					0x8c40
#घोषणा PM2R_YUV_MODE					0x8f00
#घोषणा PM2R_STATISTICS_MODE				0x8c08
#घोषणा PM2R_FB_SOURCE_DELTA				0x8d88
#घोषणा PM2R_CONFIG					0x8d90
#घोषणा PM2R_DELTA_MODE					0x9300

/* Permedia2v */
#घोषणा PM2VR_RD_INDEX_LOW				0x4020
#घोषणा PM2VR_RD_INDEX_HIGH				0x4028
#घोषणा PM2VR_RD_INDEXED_DATA				0x4030

/* Permedia2 RAMDAC indexed रेजिस्टरs */
#घोषणा PM2I_RD_CURSOR_CONTROL				0x06
#घोषणा PM2I_RD_COLOR_MODE				0x18
#घोषणा PM2I_RD_MODE_CONTROL				0x19
#घोषणा PM2I_RD_MISC_CONTROL				0x1e
#घोषणा PM2I_RD_PIXEL_CLOCK_A1				0x20
#घोषणा PM2I_RD_PIXEL_CLOCK_A2				0x21
#घोषणा PM2I_RD_PIXEL_CLOCK_A3				0x22
#घोषणा PM2I_RD_PIXEL_CLOCK_STATUS			0x29
#घोषणा PM2I_RD_MEMORY_CLOCK_1				0x30
#घोषणा PM2I_RD_MEMORY_CLOCK_2				0x31
#घोषणा PM2I_RD_MEMORY_CLOCK_3				0x32
#घोषणा PM2I_RD_MEMORY_CLOCK_STATUS			0x33
#घोषणा PM2I_RD_COLOR_KEY_CONTROL			0x40
#घोषणा PM2I_RD_OVERLAY_KEY				0x41
#घोषणा PM2I_RD_RED_KEY					0x42
#घोषणा PM2I_RD_GREEN_KEY				0x43
#घोषणा PM2I_RD_BLUE_KEY				0x44

/* Permedia2v extensions */
#घोषणा PM2VI_RD_MISC_CONTROL				0x000
#घोषणा PM2VI_RD_SYNC_CONTROL				0x001
#घोषणा PM2VI_RD_DAC_CONTROL				0x002
#घोषणा PM2VI_RD_PIXEL_SIZE				0x003
#घोषणा PM2VI_RD_COLOR_FORMAT				0x004
#घोषणा PM2VI_RD_CURSOR_MODE				0x005
#घोषणा PM2VI_RD_CURSOR_X_LOW				0x007
#घोषणा PM2VI_RD_CURSOR_X_HIGH				0x008
#घोषणा PM2VI_RD_CURSOR_Y_LOW				0x009
#घोषणा PM2VI_RD_CURSOR_Y_HIGH				0x00A
#घोषणा PM2VI_RD_CURSOR_X_HOT				0x00B
#घोषणा PM2VI_RD_CURSOR_Y_HOT				0x00C
#घोषणा PM2VI_RD_OVERLAY_KEY				0x00D
#घोषणा PM2VI_RD_CLK0_PRESCALE				0x201
#घोषणा PM2VI_RD_CLK0_FEEDBACK				0x202
#घोषणा PM2VI_RD_CLK0_POSTSCALE				0x203
#घोषणा PM2VI_RD_CLK1_PRESCALE				0x204
#घोषणा PM2VI_RD_CLK1_FEEDBACK				0x205
#घोषणा PM2VI_RD_CLK1_POSTSCALE				0x206
#घोषणा PM2VI_RD_MCLK_CONTROL				0x20D
#घोषणा PM2VI_RD_MCLK_PRESCALE				0x20E
#घोषणा PM2VI_RD_MCLK_FEEDBACK				0x20F
#घोषणा PM2VI_RD_MCLK_POSTSCALE				0x210
#घोषणा PM2VI_RD_CURSOR_PALETTE				0x303
#घोषणा PM2VI_RD_CURSOR_PATTERN				0x400

/* Fields and flags */
#घोषणा PM2F_RENDER_AREASTIPPLE				(1L<<0)
#घोषणा PM2F_RENDER_FASTFILL				(1L<<3)
#घोषणा PM2F_RENDER_PRIMITIVE_MASK			(3L<<6)
#घोषणा PM2F_RENDER_LINE				0
#घोषणा PM2F_RENDER_TRAPEZOID				(1L<<6)
#घोषणा PM2F_RENDER_POINT				(2L<<6)
#घोषणा PM2F_RENDER_RECTANGLE				(3L<<6)
#घोषणा PM2F_RENDER_SYNC_ON_BIT_MASK			(1L<<11)
#घोषणा PM2F_RENDER_TEXTURE_ENABLE			(1L<<13)
#घोषणा PM2F_SYNCHRONIZATION				(1L<<10)
#घोषणा PM2F_PLL_LOCKED					0x10
#घोषणा PM2F_BEING_RESET				(1L<<31)
#घोषणा PM2F_DATATYPE_COLOR				0x8000
#घोषणा PM2F_VGA_ENABLE					0x02
#घोषणा PM2F_VGA_FIXED					0x04
#घोषणा PM2F_FB_WRITE_ENABLE				0x01
#घोषणा PM2F_FB_READ_SOURCE_ENABLE			0x0200
#घोषणा PM2F_RD_PALETTE_WIDTH_8				0x02
#घोषणा PM2F_PART_PROD_MASK				0x01ff
#घोषणा PM2F_SCREEN_SCISSOR_ENABLE			0x02
#घोषणा PM2F_DATA_64_ENABLE				0x00010000
#घोषणा PM2F_BLANK_LOW					0x02
#घोषणा PM2F_HSYNC_MASK					0x18
#घोषणा PM2F_VSYNC_MASK					0x60
#घोषणा PM2F_HSYNC_ACT_HIGH				0x08
#घोषणा PM2F_HSYNC_FORCED_LOW				0x10
#घोषणा PM2F_HSYNC_ACT_LOW				0x18
#घोषणा PM2F_VSYNC_ACT_HIGH				0x20
#घोषणा PM2F_VSYNC_FORCED_LOW				0x40
#घोषणा PM2F_VSYNC_ACT_LOW				0x60
#घोषणा PM2F_LINE_DOUBLE				0x04
#घोषणा PM2F_VIDEO_ENABLE				0x01
#घोषणा PM2F_RD_PIXELFORMAT_SVGA			0x01
#घोषणा PM2F_RD_PIXELFORMAT_RGB232OFFSET		0x02
#घोषणा PM2F_RD_PIXELFORMAT_RGBA2321			0x03
#घोषणा PM2F_RD_PIXELFORMAT_RGBA5551			0x04
#घोषणा PM2F_RD_PIXELFORMAT_RGBA4444			0x05
#घोषणा PM2F_RD_PIXELFORMAT_RGB565			0x06
#घोषणा PM2F_RD_PIXELFORMAT_RGBA8888			0x08
#घोषणा PM2F_RD_PIXELFORMAT_RGB888			0x09
#घोषणा PM2F_RD_GUI_ACTIVE				0x10
#घोषणा PM2F_RD_COLOR_MODE_RGB				0x20
#घोषणा PM2F_DELTA_ORDER_RGB				(1L<<18)
#घोषणा PM2F_RD_TRUECOLOR				0x80
#घोषणा PM2F_NO_ALPHA_BUFFER				0x10
#घोषणा PM2F_TEXTEL_SIZE_16				0x00080000
#घोषणा PM2F_TEXTEL_SIZE_32				0x00100000
#घोषणा PM2F_TEXTEL_SIZE_4				0x00180000
#घोषणा PM2F_TEXTEL_SIZE_24				0x00200000
#घोषणा PM2F_INCREASE_X					(1L<<21)
#घोषणा PM2F_INCREASE_Y					(1L<<22)
#घोषणा PM2F_CONFIG_FB_WRITE_ENABLE			(1L<<3)
#घोषणा PM2F_CONFIG_FB_PACKED_DATA			(1L<<2)
#घोषणा PM2F_CONFIG_FB_READ_DEST_ENABLE			(1L<<1)
#घोषणा PM2F_CONFIG_FB_READ_SOURCE_ENABLE		(1L<<0)
#घोषणा PM2F_COLOR_KEY_TEST_OFF				(1L<<4)
#घोषणा PM2F_MEM_CONFIG_RAM_MASK			(3L<<29)
#घोषणा PM2F_MEM_BANKS_1				0L
#घोषणा PM2F_MEM_BANKS_2				(1L<<29)
#घोषणा PM2F_MEM_BANKS_3				(2L<<29)
#घोषणा PM2F_MEM_BANKS_4				(3L<<29)
#घोषणा PM2F_APERTURE_STANDARD				0
#घोषणा PM2F_APERTURE_BYTESWAP				1
#घोषणा PM2F_APERTURE_HALFWORDSWAP			2
#घोषणा PM2F_CURSORMODE_CURSOR_ENABLE			(1 << 0)
#घोषणा PM2F_CURSORMODE_TYPE_X				(1 << 4)

प्रकार क्रमागत अणु
	PM2_TYPE_PERMEDIA2,
	PM2_TYPE_PERMEDIA2V
पूर्ण pm2type_t;

#पूर्ण_अगर /* PM2FB_H */

/*****************************************************************************
 * That's all folks!
 *****************************************************************************/
