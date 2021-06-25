<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright 2018 IBM Corporation */

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_simple_kms_helper.h>

काष्ठा aspeed_gfx अणु
	काष्ठा drm_device		drm;
	व्योम __iomem			*base;
	काष्ठा clk			*clk;
	काष्ठा reset_control		*rst;
	काष्ठा regmap			*scu;

	u32				dac_reg;
	u32				vga_scratch_reg;
	u32				throd_val;
	u32				scan_line_max;

	काष्ठा drm_simple_display_pipe	pipe;
	काष्ठा drm_connector		connector;
पूर्ण;
#घोषणा to_aspeed_gfx(x) container_of(x, काष्ठा aspeed_gfx, drm)

पूर्णांक aspeed_gfx_create_pipe(काष्ठा drm_device *drm);
पूर्णांक aspeed_gfx_create_output(काष्ठा drm_device *drm);

#घोषणा CRT_CTRL1		0x60 /* CRT Control I */
#घोषणा CRT_CTRL2		0x64 /* CRT Control II */
#घोषणा CRT_STATUS		0x68 /* CRT Status */
#घोषणा CRT_MISC		0x6c /* CRT Misc Setting */
#घोषणा CRT_HORIZ0		0x70 /* CRT Horizontal Total & Display Enable End */
#घोषणा CRT_HORIZ1		0x74 /* CRT Horizontal Retrace Start & End */
#घोषणा CRT_VERT0		0x78 /* CRT Vertical Total & Display Enable End */
#घोषणा CRT_VERT1		0x7C /* CRT Vertical Retrace Start & End */
#घोषणा CRT_ADDR		0x80 /* CRT Display Starting Address */
#घोषणा CRT_OFFSET		0x84 /* CRT Display Offset & Terminal Count */
#घोषणा CRT_THROD		0x88 /* CRT Threshold */
#घोषणा CRT_XSCALE		0x8C /* CRT Scaling-Up Factor */
#घोषणा CRT_CURSOR0		0x90 /* CRT Hardware Cursor X & Y Offset */
#घोषणा CRT_CURSOR1		0x94 /* CRT Hardware Cursor X & Y Position */
#घोषणा CRT_CURSOR2		0x98 /* CRT Hardware Cursor Pattern Address */
#घोषणा CRT_9C			0x9C
#घोषणा CRT_OSD_H		0xA0 /* CRT OSD Horizontal Start/End */
#घोषणा CRT_OSD_V		0xA4 /* CRT OSD Vertical Start/End */
#घोषणा CRT_OSD_ADDR		0xA8 /* CRT OSD Pattern Address */
#घोषणा CRT_OSD_DISP		0xAC /* CRT OSD Offset */
#घोषणा CRT_OSD_THRESH		0xB0 /* CRT OSD Threshold & Alpha */
#घोषणा CRT_B4			0xB4
#घोषणा CRT_STS_V		0xB8 /* CRT Status V */
#घोषणा CRT_SCRATCH		0xBC /* Scratchpad */
#घोषणा CRT_BB0_ADDR		0xD0 /* CRT Display BB0 Starting Address */
#घोषणा CRT_BB1_ADDR		0xD4 /* CRT Display BB1 Starting Address */
#घोषणा CRT_BB_COUNT		0xD8 /* CRT Display BB Terminal Count */
#घोषणा OSD_COLOR1		0xE0 /* OSD Color Palette Index 1 & 0 */
#घोषणा OSD_COLOR2		0xE4 /* OSD Color Palette Index 3 & 2 */
#घोषणा OSD_COLOR3		0xE8 /* OSD Color Palette Index 5 & 4 */
#घोषणा OSD_COLOR4		0xEC /* OSD Color Palette Index 7 & 6 */
#घोषणा OSD_COLOR5		0xF0 /* OSD Color Palette Index 9 & 8 */
#घोषणा OSD_COLOR6		0xF4 /* OSD Color Palette Index 11 & 10 */
#घोषणा OSD_COLOR7		0xF8 /* OSD Color Palette Index 13 & 12 */
#घोषणा OSD_COLOR8		0xFC /* OSD Color Palette Index 15 & 14 */

/* CTRL1 */
#घोषणा CRT_CTRL_EN			BIT(0)
#घोषणा CRT_CTRL_HW_CURSOR_EN		BIT(1)
#घोषणा CRT_CTRL_OSD_EN			BIT(2)
#घोषणा CRT_CTRL_INTERLACED		BIT(3)
#घोषणा CRT_CTRL_COLOR_RGB565		(0 << 7)
#घोषणा CRT_CTRL_COLOR_YUV444		(1 << 7)
#घोषणा CRT_CTRL_COLOR_XRGB8888		(2 << 7)
#घोषणा CRT_CTRL_COLOR_RGB888		(3 << 7)
#घोषणा CRT_CTRL_COLOR_YUV444_2RGB	(5 << 7)
#घोषणा CRT_CTRL_COLOR_YUV422		(7 << 7)
#घोषणा CRT_CTRL_COLOR_MASK		GENMASK(9, 7)
#घोषणा CRT_CTRL_HSYNC_NEGATIVE		BIT(16)
#घोषणा CRT_CTRL_VSYNC_NEGATIVE		BIT(17)
#घोषणा CRT_CTRL_VERTICAL_INTR_EN	BIT(30)
#घोषणा CRT_CTRL_VERTICAL_INTR_STS	BIT(31)

/* CTRL2 */
#घोषणा CRT_CTRL_DAC_EN			BIT(0)
#घोषणा CRT_CTRL_VBLANK_LINE(x)		(((x) << 20) & CRT_CTRL_VBLANK_LINE_MASK)
#घोषणा CRT_CTRL_VBLANK_LINE_MASK	GENMASK(31, 20)

/* CRT_HORIZ0 */
#घोषणा CRT_H_TOTAL(x)			(x)
#घोषणा CRT_H_DE(x)			((x) << 16)

/* CRT_HORIZ1 */
#घोषणा CRT_H_RS_START(x)		(x)
#घोषणा CRT_H_RS_END(x)			((x) << 16)

/* CRT_VIRT0 */
#घोषणा CRT_V_TOTAL(x)			(x)
#घोषणा CRT_V_DE(x)			((x) << 16)

/* CRT_VIRT1 */
#घोषणा CRT_V_RS_START(x)		(x)
#घोषणा CRT_V_RS_END(x)			((x) << 16)

/* CRT_OFFSET */
#घोषणा CRT_DISP_OFFSET(x)		(x)
#घोषणा CRT_TERM_COUNT(x)		((x) << 16)

/* CRT_THROD */
#घोषणा CRT_THROD_LOW(x)		(x)
#घोषणा CRT_THROD_HIGH(x)		((x) << 8)
