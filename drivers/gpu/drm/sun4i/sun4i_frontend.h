<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Free Electrons
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _SUN4I_FRONTEND_H_
#घोषणा _SUN4I_FRONTEND_H_

#समावेश <linux/list.h>

#घोषणा SUN4I_FRONTEND_EN_REG			0x000
#घोषणा SUN4I_FRONTEND_EN_EN				BIT(0)

#घोषणा SUN4I_FRONTEND_FRM_CTRL_REG		0x004
#घोषणा SUN4I_FRONTEND_FRM_CTRL_COEF_ACCESS_CTRL	BIT(23)
#घोषणा SUN4I_FRONTEND_FRM_CTRL_FRM_START		BIT(16)
#घोषणा SUN4I_FRONTEND_FRM_CTRL_COEF_RDY		BIT(1)
#घोषणा SUN4I_FRONTEND_FRM_CTRL_REG_RDY			BIT(0)

#घोषणा SUN4I_FRONTEND_BYPASS_REG		0x008
#घोषणा SUN4I_FRONTEND_BYPASS_CSC_EN			BIT(1)

#घोषणा SUN4I_FRONTEND_BUF_ADDR0_REG		0x020
#घोषणा SUN4I_FRONTEND_BUF_ADDR1_REG		0x024
#घोषणा SUN4I_FRONTEND_BUF_ADDR2_REG		0x028

#घोषणा SUN4I_FRONTEND_TB_OFF0_REG		0x030
#घोषणा SUN4I_FRONTEND_TB_OFF1_REG		0x034
#घोषणा SUN4I_FRONTEND_TB_OFF2_REG		0x038
#घोषणा SUN4I_FRONTEND_TB_OFF_X1(x1)			((x1) << 16)
#घोषणा SUN4I_FRONTEND_TB_OFF_Y0(y0)			((y0) << 8)
#घोषणा SUN4I_FRONTEND_TB_OFF_X0(x0)			(x0)

#घोषणा SUN4I_FRONTEND_LINESTRD0_REG		0x040
#घोषणा SUN4I_FRONTEND_LINESTRD1_REG		0x044
#घोषणा SUN4I_FRONTEND_LINESTRD2_REG		0x048

/*
 * In tiled mode, the stride is defined as the distance between the start of the
 * end line of the current tile and the start of the first line in the next
 * vertical tile.
 *
 * Tiles are represented in row-major order, thus the end line of current tile
 * starts at: 31 * 32 (31 lines of 32 cols), the next vertical tile starts at:
 * 32-bit-aligned-width * 32 and the distance is:
 * 32 * (32-bit-aligned-width - 31).
 */
#घोषणा SUN4I_FRONTEND_LINESTRD_TILED(stride)		(((stride) - 31) * 32)

#घोषणा SUN4I_FRONTEND_INPUT_FMT_REG		0x04c
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_MOD_PLANAR	(0 << 8)
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_MOD_PACKED	(1 << 8)
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_MOD_SEMIPLANAR	(2 << 8)
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_MOD_MB32_PLANAR	(4 << 8)
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_MOD_MB32_SEMIPLANAR (6 << 8)
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_FMT_YUV444	(0 << 4)
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_FMT_YUV422	(1 << 4)
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_FMT_YUV420	(2 << 4)
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_FMT_YUV411	(3 << 4)
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_FMT_RGB		(5 << 4)
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_PS_UYVY		0
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_PS_YUYV		1
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_PS_VYUY		2
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_PS_YVYU		3
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_PS_UV		0
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_PS_VU		1
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_PS_BGRX		0
#घोषणा SUN4I_FRONTEND_INPUT_FMT_DATA_PS_XRGB		1

#घोषणा SUN4I_FRONTEND_OUTPUT_FMT_REG		0x05c
#घोषणा SUN4I_FRONTEND_OUTPUT_FMT_DATA_FMT_BGRX8888	1
#घोषणा SUN4I_FRONTEND_OUTPUT_FMT_DATA_FMT_XRGB8888	2

#घोषणा SUN4I_FRONTEND_CSC_COEF_REG(c)		(0x070 + (0x4 * (c)))

#घोषणा SUN4I_FRONTEND_CH0_INSIZE_REG		0x100
#घोषणा SUN4I_FRONTEND_INSIZE(h, w)			((((h) - 1) << 16) | (((w) - 1)))

#घोषणा SUN4I_FRONTEND_CH0_OUTSIZE_REG		0x104
#घोषणा SUN4I_FRONTEND_OUTSIZE(h, w)			((((h) - 1) << 16) | (((w) - 1)))

#घोषणा SUN4I_FRONTEND_CH0_HORZFACT_REG		0x108
#घोषणा SUN4I_FRONTEND_HORZFACT(i, f)			(((i) << 16) | (f))

#घोषणा SUN4I_FRONTEND_CH0_VERTFACT_REG		0x10c
#घोषणा SUN4I_FRONTEND_VERTFACT(i, f)			(((i) << 16) | (f))

#घोषणा SUN4I_FRONTEND_CH0_HORZPHASE_REG	0x110
#घोषणा SUN4I_FRONTEND_CH0_VERTPHASE0_REG	0x114
#घोषणा SUN4I_FRONTEND_CH0_VERTPHASE1_REG	0x118

#घोषणा SUN4I_FRONTEND_CH1_INSIZE_REG		0x200
#घोषणा SUN4I_FRONTEND_CH1_OUTSIZE_REG		0x204
#घोषणा SUN4I_FRONTEND_CH1_HORZFACT_REG		0x208
#घोषणा SUN4I_FRONTEND_CH1_VERTFACT_REG		0x20c

#घोषणा SUN4I_FRONTEND_CH1_HORZPHASE_REG	0x210
#घोषणा SUN4I_FRONTEND_CH1_VERTPHASE0_REG	0x214
#घोषणा SUN4I_FRONTEND_CH1_VERTPHASE1_REG	0x218

#घोषणा SUN4I_FRONTEND_CH0_HORZCOEF0_REG(i)	(0x400 + i * 4)
#घोषणा SUN4I_FRONTEND_CH0_HORZCOEF1_REG(i)	(0x480 + i * 4)
#घोषणा SUN4I_FRONTEND_CH0_VERTCOEF_REG(i)	(0x500 + i * 4)
#घोषणा SUN4I_FRONTEND_CH1_HORZCOEF0_REG(i)	(0x600 + i * 4)
#घोषणा SUN4I_FRONTEND_CH1_HORZCOEF1_REG(i)	(0x680 + i * 4)
#घोषणा SUN4I_FRONTEND_CH1_VERTCOEF_REG(i)	(0x700 + i * 4)

काष्ठा clk;
काष्ठा device_node;
काष्ठा drm_plane;
काष्ठा regmap;
काष्ठा reset_control;

काष्ठा sun4i_frontend_data अणु
	bool	has_coef_access_ctrl;
	bool	has_coef_rdy;
	u32	ch_phase[2];
पूर्ण;

काष्ठा sun4i_frontend अणु
	काष्ठा list_head	list;
	काष्ठा device		*dev;
	काष्ठा device_node	*node;

	काष्ठा clk		*bus_clk;
	काष्ठा clk		*mod_clk;
	काष्ठा clk		*ram_clk;
	काष्ठा regmap		*regs;
	काष्ठा reset_control	*reset;

	स्थिर काष्ठा sun4i_frontend_data	*data;
पूर्ण;

बाह्य स्थिर काष्ठा of_device_id sun4i_frontend_of_table[];
बाह्य स्थिर u32 sunxi_bt601_yuv2rgb_coef[12];

पूर्णांक sun4i_frontend_init(काष्ठा sun4i_frontend *frontend);
व्योम sun4i_frontend_निकास(काष्ठा sun4i_frontend *frontend);
पूर्णांक sun4i_frontend_enable(काष्ठा sun4i_frontend *frontend);

व्योम sun4i_frontend_update_buffer(काष्ठा sun4i_frontend *frontend,
				  काष्ठा drm_plane *plane);
व्योम sun4i_frontend_update_coord(काष्ठा sun4i_frontend *frontend,
				 काष्ठा drm_plane *plane);
पूर्णांक sun4i_frontend_update_क्रमmats(काष्ठा sun4i_frontend *frontend,
				  काष्ठा drm_plane *plane, uपूर्णांक32_t out_fmt);
bool sun4i_frontend_क्रमmat_is_supported(uपूर्णांक32_t fmt, uपूर्णांक64_t modअगरier);

#पूर्ण_अगर /* _SUN4I_FRONTEND_H_ */
