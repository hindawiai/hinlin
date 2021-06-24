<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Samsung S5P G2D - 2D Graphics Accelerator Driver
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Kamil Debski, <k.debski@samsung.com>
 */

/* General Registers */
#घोषणा SOFT_RESET_REG		0x0000	/* Software reset reg */
#घोषणा INTEN_REG		0x0004	/* Interrupt Enable reg */
#घोषणा INTC_PEND_REG		0x000C	/* Interrupt Control Pending reg */
#घोषणा FIFO_STAT_REG		0x0010	/* Command FIFO Status reg */
#घोषणा AXI_ID_MODE_REG		0x0014	/* AXI Read ID Mode reg */
#घोषणा CACHECTL_REG		0x0018	/* Cache & Buffer clear reg */
#घोषणा AXI_MODE_REG		0x001C	/* AXI Mode reg */

/* Command Registers */
#घोषणा BITBLT_START_REG	0x0100	/* BitBLT Start reg */
#घोषणा BITBLT_COMMAND_REG	0x0104	/* Command reg क्रम BitBLT */

/* Parameter Setting Registers (Rotate & Direction) */
#घोषणा ROTATE_REG		0x0200	/* Rotation reg */
#घोषणा SRC_MSK_सूचीECT_REG	0x0204	/* Src and Mask Direction reg */
#घोषणा DST_PAT_सूचीECT_REG	0x0208	/* Dest and Pattern Direction reg */

/* Parameter Setting Registers (Src) */
#घोषणा SRC_SELECT_REG		0x0300	/* Src Image Selection reg */
#घोषणा SRC_BASE_ADDR_REG	0x0304	/* Src Image Base Address reg */
#घोषणा SRC_STRIDE_REG		0x0308	/* Src Stride reg */
#घोषणा SRC_COLOR_MODE_REG	0x030C	/* Src Image Color Mode reg */
#घोषणा SRC_LEFT_TOP_REG	0x0310	/* Src Left Top Coordinate reg */
#घोषणा SRC_RIGHT_BOTTOM_REG	0x0314	/* Src Right Bottom Coordinate reg */
#घोषणा SRC_SCALE_CTRL_REG	0x0328	/* Src Scaling type select */
#घोषणा SRC_XSCALE_REG		0x032c	/* Src X Scaling ratio */
#घोषणा SRC_YSCALE_REG		0x0330	/* Src Y Scaling ratio */

/* Parameter Setting Registers (Dest) */
#घोषणा DST_SELECT_REG		0x0400	/* Dest Image Selection reg */
#घोषणा DST_BASE_ADDR_REG	0x0404	/* Dest Image Base Address reg */
#घोषणा DST_STRIDE_REG		0x0408	/* Dest Stride reg */
#घोषणा DST_COLOR_MODE_REG	0x040C	/* Dest Image Color Mode reg */
#घोषणा DST_LEFT_TOP_REG	0x0410	/* Dest Left Top Coordinate reg */
#घोषणा DST_RIGHT_BOTTOM_REG	0x0414	/* Dest Right Bottom Coordinate reg */

/* Parameter Setting Registers (Pattern) */
#घोषणा PAT_BASE_ADDR_REG	0x0500	/* Pattern Image Base Address reg */
#घोषणा PAT_SIZE_REG		0x0504	/* Pattern Image Size reg */
#घोषणा PAT_COLOR_MODE_REG	0x0508	/* Pattern Image Color Mode reg */
#घोषणा PAT_OFFSET_REG		0x050C	/* Pattern Left Top Coordinate reg */
#घोषणा PAT_STRIDE_REG		0x0510	/* Pattern Stride reg */

/* Parameter Setting Registers (Mask) */
#घोषणा MASK_BASE_ADDR_REG	0x0520	/* Mask Base Address reg */
#घोषणा MASK_STRIDE_REG		0x0524	/* Mask Stride reg */

/* Parameter Setting Registers (Clipping Winकरोw) */
#घोषणा CW_LT_REG		0x0600	/* LeftTop coordinates of Clip Winकरोw */
#घोषणा CW_RB_REG		0x0604	/* RightBottom coordinates of Clip
								Winकरोw */

/* Parameter Setting Registers (ROP & Alpha Setting) */
#घोषणा THIRD_OPERAND_REG	0x0610	/* Third Opeअक्रम Selection reg */
#घोषणा ROP4_REG		0x0614	/* Raster Operation reg */
#घोषणा ALPHA_REG		0x0618	/* Alpha value, Fading offset value */

/* Parameter Setting Registers (Color) */
#घोषणा FG_COLOR_REG		0x0700	/* Foreground Color reg */
#घोषणा BG_COLOR_REG		0x0704	/* Background Color reg */
#घोषणा BS_COLOR_REG		0x0708	/* Blue Screen Color reg */

/* Parameter Setting Registers (Color Key) */
#घोषणा SRC_COLORKEY_CTRL_REG	0x0710	/* Src Colorkey control reg */
#घोषणा SRC_COLORKEY_DR_MIN_REG	0x0714	/* Src Colorkey Decision Reference
								Min reg */
#घोषणा SRC_COLORKEY_DR_MAX_REG	0x0718	/* Src Colorkey Decision Reference
								Max reg */
#घोषणा DST_COLORKEY_CTRL_REG	0x071C	/* Dest Colorkey control reg */
#घोषणा DST_COLORKEY_DR_MIN_REG	0x0720	/* Dest Colorkey Decision Reference
								Min reg */
#घोषणा DST_COLORKEY_DR_MAX_REG	0x0724	/* Dest Colorkey Decision Reference
								Max reg */

/* Color mode values */

#घोषणा ORDER_XRGB		0
#घोषणा ORDER_RGBX		1
#घोषणा ORDER_XBGR		2
#घोषणा ORDER_BGRX		3

#घोषणा MODE_XRGB_8888		0
#घोषणा MODE_ARGB_8888		1
#घोषणा MODE_RGB_565		2
#घोषणा MODE_XRGB_1555		3
#घोषणा MODE_ARGB_1555		4
#घोषणा MODE_XRGB_4444		5
#घोषणा MODE_ARGB_4444		6
#घोषणा MODE_PACKED_RGB_888	7

#घोषणा COLOR_MODE(o, m)	(((o) << 4) | (m))

/* ROP4 operation values */
#घोषणा ROP4_COPY		0xCCCC
#घोषणा ROP4_INVERT		0x3333

/* Hardware limits */
#घोषणा MAX_WIDTH		8000
#घोषणा MAX_HEIGHT		8000

#घोषणा G2D_TIMEOUT		500

#घोषणा DEFAULT_WIDTH		100
#घोषणा DEFAULT_HEIGHT		100

#घोषणा DEFAULT_SCALE_MODE	(2 << 0)

/* Command mode रेजिस्टर values */
#घोषणा CMD_V3_ENABLE_STRETCH	(1 << 4)
