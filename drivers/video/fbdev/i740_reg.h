<शैली गुरु>
/**************************************************************************

Copyright 1998-1999 Precision Insight, Inc., Cedar Park, Texas.
All Rights Reserved.

Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
copy of this software and associated करोcumentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modअगरy, merge, publish,
distribute, sub license, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to करो so, subject to
the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

/*
 * Authors:
 *   Kevin E. Martin <kevin@precisioninsight.com>
 */

/* I/O रेजिस्टर offsets */
#घोषणा SRX VGA_SEQ_I
#घोषणा GRX VGA_GFX_I
#घोषणा ARX VGA_ATT_IW
#घोषणा XRX 0x3D6
#घोषणा MRX 0x3D2

/* VGA Color Palette Registers */
#घोषणा DACMASK		0x3C6
#घोषणा DACSTATE	0x3C7
#घोषणा DACRX		0x3C7
#घोषणा DACWX		0x3C8
#घोषणा DACDATA		0x3C9

/* CRT Controller Registers (CRX) */
#घोषणा START_ADDR_HI		0x0C
#घोषणा START_ADDR_LO		0x0D
#घोषणा VERT_SYNC_END		0x11
#घोषणा EXT_VERT_TOTAL		0x30
#घोषणा EXT_VERT_DISPLAY	0x31
#घोषणा EXT_VERT_SYNC_START	0x32
#घोषणा EXT_VERT_BLANK_START	0x33
#घोषणा EXT_HORIZ_TOTAL		0x35
#घोषणा EXT_HORIZ_BLANK		0x39
#घोषणा EXT_START_ADDR		0x40
#घोषणा EXT_START_ADDR_ENABLE	0x80
#घोषणा EXT_OFFSET		0x41
#घोषणा EXT_START_ADDR_HI	0x42
#घोषणा INTERLACE_CNTL		0x70
#घोषणा INTERLACE_ENABLE	0x80
#घोषणा INTERLACE_DISABLE	0x00

/* Miscellaneous Output Register */
#घोषणा MSR_R		0x3CC
#घोषणा MSR_W		0x3C2
#घोषणा IO_ADDR_SELECT	0x01

#घोषणा MDA_BASE	0x3B0
#घोषणा CGA_BASE	0x3D0

/* System Configuration Extension Registers (XRX) */
#घोषणा IO_CTNL		0x09
#घोषणा EXTENDED_ATTR_CNTL	0x02
#घोषणा EXTENDED_CRTC_CNTL	0x01

#घोषणा ADDRESS_MAPPING	0x0A
#घोषणा PACKED_MODE_ENABLE	0x04
#घोषणा LINEAR_MODE_ENABLE	0x02
#घोषणा PAGE_MAPPING_ENABLE	0x01

#घोषणा BITBLT_CNTL	0x20
#घोषणा COLEXP_MODE		0x30
#घोषणा COLEXP_8BPP		0x00
#घोषणा COLEXP_16BPP		0x10
#घोषणा COLEXP_24BPP		0x20
#घोषणा COLEXP_RESERVED		0x30
#घोषणा CHIP_RESET		0x02
#घोषणा BITBLT_STATUS		0x01

#घोषणा DISPLAY_CNTL	0x40
#घोषणा VGA_WRAP_MODE		0x02
#घोषणा VGA_WRAP_AT_256KB	0x00
#घोषणा VGA_NO_WRAP		0x02
#घोषणा GUI_MODE		0x01
#घोषणा STANDARD_VGA_MODE	0x00
#घोषणा HIRES_MODE		0x01

#घोषणा DRAM_ROW_TYPE	0x50
#घोषणा DRAM_ROW_0		0x07
#घोषणा DRAM_ROW_0_SDRAM	0x00
#घोषणा DRAM_ROW_0_EMPTY	0x07
#घोषणा DRAM_ROW_1		0x38
#घोषणा DRAM_ROW_1_SDRAM	0x00
#घोषणा DRAM_ROW_1_EMPTY	0x38
#घोषणा DRAM_ROW_CNTL_LO 0x51
#घोषणा DRAM_CAS_LATENCY	0x10
#घोषणा DRAM_RAS_TIMING		0x08
#घोषणा DRAM_RAS_PRECHARGE	0x04
#घोषणा DRAM_ROW_CNTL_HI 0x52
#घोषणा DRAM_EXT_CNTL	0x53
#घोषणा DRAM_REFRESH_RATE	0x03
#घोषणा DRAM_REFRESH_DISABLE	0x00
#घोषणा DRAM_REFRESH_60HZ	0x01
#घोषणा DRAM_REFRESH_FAST_TEST	0x02
#घोषणा DRAM_REFRESH_RESERVED	0x03
#घोषणा DRAM_TIMING	0x54
#घोषणा DRAM_ROW_BNDRY_0 0x55
#घोषणा DRAM_ROW_BNDRY_1 0x56

#घोषणा DPMS_SYNC_SELECT 0x61
#घोषणा VSYNC_CNTL		0x08
#घोषणा VSYNC_ON		0x00
#घोषणा VSYNC_OFF		0x08
#घोषणा HSYNC_CNTL		0x02
#घोषणा HSYNC_ON		0x00
#घोषणा HSYNC_OFF		0x02

#घोषणा PIXPIPE_CONFIG_0 0x80
#घोषणा DAC_8_BIT		0x80
#घोषणा DAC_6_BIT		0x00
#घोषणा HW_CURSOR_ENABLE	0x10
#घोषणा EXTENDED_PALETTE	0x01

#घोषणा PIXPIPE_CONFIG_1 0x81
#घोषणा DISPLAY_COLOR_MODE	0x0F
#घोषणा DISPLAY_VGA_MODE	0x00
#घोषणा DISPLAY_8BPP_MODE	0x02
#घोषणा DISPLAY_15BPP_MODE	0x04
#घोषणा DISPLAY_16BPP_MODE	0x05
#घोषणा DISPLAY_24BPP_MODE	0x06
#घोषणा DISPLAY_32BPP_MODE	0x07

#घोषणा PIXPIPE_CONFIG_2 0x82
#घोषणा DISPLAY_GAMMA_ENABLE	0x08
#घोषणा DISPLAY_GAMMA_DISABLE	0x00
#घोषणा OVERLAY_GAMMA_ENABLE	0x04
#घोषणा OVERLAY_GAMMA_DISABLE	0x00

#घोषणा CURSOR_CONTROL	0xA0
#घोषणा CURSOR_ORIGIN_SCREEN	0x00
#घोषणा CURSOR_ORIGIN_DISPLAY	0x10
#घोषणा CURSOR_MODE		0x07
#घोषणा CURSOR_MODE_DISABLE	0x00
#घोषणा CURSOR_MODE_32_4C_AX	0x01
#घोषणा CURSOR_MODE_128_2C	0x02
#घोषणा CURSOR_MODE_128_1C	0x03
#घोषणा CURSOR_MODE_64_3C	0x04
#घोषणा CURSOR_MODE_64_4C_AX	0x05
#घोषणा CURSOR_MODE_64_4C	0x06
#घोषणा CURSOR_MODE_RESERVED	0x07
#घोषणा CURSOR_BASEADDR_LO 0xA2
#घोषणा CURSOR_BASEADDR_HI 0xA3
#घोषणा CURSOR_X_LO	0xA4
#घोषणा CURSOR_X_HI	0xA5
#घोषणा CURSOR_X_POS		0x00
#घोषणा CURSOR_X_NEG		0x80
#घोषणा CURSOR_Y_LO	0xA6
#घोषणा CURSOR_Y_HI	0xA7
#घोषणा CURSOR_Y_POS		0x00
#घोषणा CURSOR_Y_NEG		0x80

#घोषणा VCLK2_VCO_M	0xC8
#घोषणा VCLK2_VCO_N	0xC9
#घोषणा VCLK2_VCO_MN_MSBS 0xCA
#घोषणा VCO_N_MSBS		0x30
#घोषणा VCO_M_MSBS		0x03
#घोषणा VCLK2_VCO_DIV_SEL 0xCB
#घोषणा POST_DIV_SELECT		0x70
#घोषणा POST_DIV_1		0x00
#घोषणा POST_DIV_2		0x10
#घोषणा POST_DIV_4		0x20
#घोषणा POST_DIV_8		0x30
#घोषणा POST_DIV_16		0x40
#घोषणा POST_DIV_32		0x50
#घोषणा VCO_LOOP_DIV_BY_4M	0x00
#घोषणा VCO_LOOP_DIV_BY_16M	0x04
#घोषणा REF_CLK_DIV_BY_5	0x02
#घोषणा REF_DIV_4		0x00
#घोषणा REF_DIV_1		0x01

#घोषणा PLL_CNTL	0xCE
#घोषणा PLL_MEMCLK_SEL		0x03
#घोषणा PLL_MEMCLK__66667KHZ	0x00
#घोषणा PLL_MEMCLK__75000KHZ	0x01
#घोषणा PLL_MEMCLK__88889KHZ	0x02
#घोषणा PLL_MEMCLK_100000KHZ	0x03

/* Mulसमयdia Extension Registers (MRX) */
#घोषणा ACQ_CNTL_1	0x02
#घोषणा ACQ_CNTL_2	0x03
#घोषणा FRAME_CAP_MODE		0x01
#घोषणा CONT_CAP_MODE		0x00
#घोषणा SINGLE_CAP_MODE		0x01
#घोषणा ACQ_CNTL_3	0x04
#घोषणा COL_KEY_CNTL_1		0x3C
#घोषणा BLANK_DISP_OVERLAY	0x20

/* FIFOs */
#घोषणा LP_FIFO		0x1000
#घोषणा HP_FIFO		0x2000
#घोषणा INSTPNT		0x3040
#घोषणा LP_FIFO_COUNT	0x3040
#घोषणा HP_FIFO_COUNT	0x3041

/* FIFO Commands */
#घोषणा CLIENT		0xE0000000
#घोषणा CLIENT_2D	0x60000000

/* Command Parser Mode Register */
#घोषणा COMPARS		0x3038
#घोषणा TWO_D_INST_DISABLE		0x08
#घोषणा THREE_D_INST_DISABLE		0x04
#घोषणा STATE_VAR_UPDATE_DISABLE	0x02
#घोषणा PAL_STIP_DISABLE		0x01

/* Interrupt Control Registers */
#घोषणा IER		0x3030
#घोषणा IIR		0x3032
#घोषणा IMR		0x3034
#घोषणा ISR		0x3036
#घोषणा VMIINTB_EVENT		0x2000
#घोषणा GPIO4_INT		0x1000
#घोषणा DISP_FLIP_EVENT		0x0800
#घोषणा DVD_PORT_DMA		0x0400
#घोषणा DISP_VBLANK		0x0200
#घोषणा FIFO_EMPTY_DMA_DONE	0x0100
#घोषणा INST_PARSER_ERROR	0x0080
#घोषणा USER_DEFINED		0x0040
#घोषणा BREAKPOINT		0x0020
#घोषणा DISP_HORIZ_COUNT	0x0010
#घोषणा DISP_VSYNC		0x0008
#घोषणा CAPTURE_HORIZ_COUNT	0x0004
#घोषणा CAPTURE_VSYNC		0x0002
#घोषणा THREE_D_PIPE_FLUSHED	0x0001

/* FIFO Watermark and Burst Length Control Register */
#घोषणा FWATER_BLC	0x00006000
#घोषणा LMI_BURST_LENGTH	0x7F000000
#घोषणा LMI_FIFO_WATERMARK	0x003F0000
#घोषणा AGP_BURST_LENGTH	0x00007F00
#घोषणा AGP_FIFO_WATERMARK	0x0000003F

/* BitBLT Registers */
#घोषणा SRC_DST_PITCH	0x00040000
#घोषणा DST_PITCH		0x1FFF0000
#घोषणा SRC_PITCH		0x00001FFF
#घोषणा COLEXP_BG_COLOR	0x00040004
#घोषणा COLEXP_FG_COLOR	0x00040008
#घोषणा MONO_SRC_CNTL	0x0004000C
#घोषणा MONO_USE_COLEXP		0x00000000
#घोषणा MONO_USE_SRCEXP		0x08000000
#घोषणा MONO_DATA_ALIGN		0x07000000
#घोषणा MONO_BIT_ALIGN		0x01000000
#घोषणा MONO_BYTE_ALIGN		0x02000000
#घोषणा MONO_WORD_ALIGN		0x03000000
#घोषणा MONO_DWORD_ALIGN	0x04000000
#घोषणा MONO_QWORD_ALIGN	0x05000000
#घोषणा MONO_SRC_INIT_DSCRD	0x003F0000
#घोषणा MONO_SRC_RIGHT_CLIP	0x00003F00
#घोषणा MONO_SRC_LEFT_CLIP	0x0000003F
#घोषणा BITBLT_CONTROL	0x00040010
#घोषणा BLTR_STATUS		0x80000000
#घोषणा DYN_DEPTH		0x03000000
#घोषणा DYN_DEPTH_8BPP		0x00000000
#घोषणा DYN_DEPTH_16BPP		0x01000000
#घोषणा DYN_DEPTH_24BPP		0x02000000
#घोषणा DYN_DEPTH_32BPP		0x03000000	/* Unimplemented on the i740 */
#घोषणा DYN_DEPTH_ENABLE	0x00800000
#घोषणा PAT_VERT_ALIGN		0x00700000
#घोषणा SOLID_PAT_SELECT	0x00080000
#घोषणा PAT_IS_IN_COLOR		0x00000000
#घोषणा PAT_IS_MONO		0x00040000
#घोषणा MONO_PAT_TRANSP		0x00020000
#घोषणा COLOR_TRANSP_ROP	0x00000000
#घोषणा COLOR_TRANSP_DST	0x00008000
#घोषणा COLOR_TRANSP_EQ		0x00000000
#घोषणा COLOR_TRANSP_NOT_EQ	0x00010000
#घोषणा COLOR_TRANSP_ENABLE	0x00004000
#घोषणा MONO_SRC_TRANSP		0x00002000
#घोषणा SRC_IS_IN_COLOR		0x00000000
#घोषणा SRC_IS_MONO		0x00001000
#घोषणा SRC_USE_SRC_ADDR	0x00000000
#घोषणा SRC_USE_BLTDATA		0x00000400
#घोषणा BLT_TOP_TO_BOT		0x00000000
#घोषणा BLT_BOT_TO_TOP		0x00000200
#घोषणा BLT_LEFT_TO_RIGHT	0x00000000
#घोषणा BLT_RIGHT_TO_LEFT	0x00000100
#घोषणा BLT_ROP			0x000000FF
#घोषणा BLT_PAT_ADDR	0x00040014
#घोषणा BLT_SRC_ADDR	0x00040018
#घोषणा BLT_DST_ADDR	0x0004001C
#घोषणा BLT_DST_H_W	0x00040020
#घोषणा BLT_DST_HEIGHT		0x1FFF0000
#घोषणा BLT_DST_WIDTH		0x00001FFF
#घोषणा SRCEXP_BG_COLOR	0x00040024
#घोषणा SRCEXP_FG_COLOR	0x00040028
#घोषणा BLTDATA		0x00050000
