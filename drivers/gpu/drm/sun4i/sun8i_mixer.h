<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 */

#अगर_अघोषित _SUN8I_MIXER_H_
#घोषणा _SUN8I_MIXER_H_

#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश "sunxi_engine.h"

#घोषणा SUN8I_MIXER_SIZE(w, h)			(((h) - 1) << 16 | ((w) - 1))
#घोषणा SUN8I_MIXER_COORD(x, y)			((y) << 16 | (x))

#घोषणा SUN8I_MIXER_GLOBAL_CTL			0x0
#घोषणा SUN8I_MIXER_GLOBAL_STATUS		0x4
#घोषणा SUN8I_MIXER_GLOBAL_DBUFF		0x8
#घोषणा SUN8I_MIXER_GLOBAL_SIZE			0xc

#घोषणा SUN8I_MIXER_GLOBAL_CTL_RT_EN		BIT(0)

#घोषणा SUN8I_MIXER_GLOBAL_DBUFF_ENABLE		BIT(0)

#घोषणा DE2_MIXER_UNIT_SIZE			0x6000
#घोषणा DE3_MIXER_UNIT_SIZE			0x3000

#घोषणा DE2_BLD_BASE				0x1000
#घोषणा DE2_CH_BASE				0x2000
#घोषणा DE2_CH_SIZE				0x1000

#घोषणा DE3_BLD_BASE				0x0800
#घोषणा DE3_CH_BASE				0x1000
#घोषणा DE3_CH_SIZE				0x0800

#घोषणा SUN8I_MIXER_BLEND_PIPE_CTL(base)	((base) + 0)
#घोषणा SUN8I_MIXER_BLEND_ATTR_FCOLOR(base, x)	((base) + 0x4 + 0x10 * (x))
#घोषणा SUN8I_MIXER_BLEND_ATTR_INSIZE(base, x)	((base) + 0x8 + 0x10 * (x))
#घोषणा SUN8I_MIXER_BLEND_ATTR_COORD(base, x)	((base) + 0xc + 0x10 * (x))
#घोषणा SUN8I_MIXER_BLEND_ROUTE(base)		((base) + 0x80)
#घोषणा SUN8I_MIXER_BLEND_PREMULTIPLY(base)	((base) + 0x84)
#घोषणा SUN8I_MIXER_BLEND_BKCOLOR(base)		((base) + 0x88)
#घोषणा SUN8I_MIXER_BLEND_OUTSIZE(base)		((base) + 0x8c)
#घोषणा SUN8I_MIXER_BLEND_MODE(base, x)		((base) + 0x90 + 0x04 * (x))
#घोषणा SUN8I_MIXER_BLEND_CK_CTL(base)		((base) + 0xb0)
#घोषणा SUN8I_MIXER_BLEND_CK_CFG(base)		((base) + 0xb4)
#घोषणा SUN8I_MIXER_BLEND_CK_MAX(base, x)	((base) + 0xc0 + 0x04 * (x))
#घोषणा SUN8I_MIXER_BLEND_CK_MIN(base, x)	((base) + 0xe0 + 0x04 * (x))
#घोषणा SUN8I_MIXER_BLEND_OUTCTL(base)		((base) + 0xfc)
#घोषणा SUN50I_MIXER_BLEND_CSC_CTL(base)	((base) + 0x100)
#घोषणा SUN50I_MIXER_BLEND_CSC_COEFF(base, layer, x) \
	((base) + 0x110 + (layer) * 0x30 +  (x) * 4)

#घोषणा SUN8I_MIXER_BLEND_PIPE_CTL_EN_MSK	GENMASK(12, 8)
#घोषणा SUN8I_MIXER_BLEND_PIPE_CTL_EN(pipe)	BIT(8 + pipe)
#घोषणा SUN8I_MIXER_BLEND_PIPE_CTL_FC_EN(pipe)	BIT(pipe)

/* colors are always in AARRGGBB क्रमmat */
#घोषणा SUN8I_MIXER_BLEND_COLOR_BLACK		0xff000000
/* The following numbers are some still unknown magic numbers */
#घोषणा SUN8I_MIXER_BLEND_MODE_DEF		0x03010301

#घोषणा SUN8I_MIXER_BLEND_ROUTE_PIPE_MSK(n)	(0xf << ((n) << 2))
#घोषणा SUN8I_MIXER_BLEND_ROUTE_PIPE_SHIFT(n)	((n) << 2)

#घोषणा SUN8I_MIXER_BLEND_OUTCTL_INTERLACED	BIT(1)

#घोषणा SUN50I_MIXER_BLEND_CSC_CTL_EN(ch)	BIT(ch)
#घोषणा SUN50I_MIXER_BLEND_CSC_CONST_VAL(d, c)	(((d) << 16) | ((c) & 0xffff))

#घोषणा SUN8I_MIXER_FBFMT_ARGB8888	0
#घोषणा SUN8I_MIXER_FBFMT_ABGR8888	1
#घोषणा SUN8I_MIXER_FBFMT_RGBA8888	2
#घोषणा SUN8I_MIXER_FBFMT_BGRA8888	3
#घोषणा SUN8I_MIXER_FBFMT_XRGB8888	4
#घोषणा SUN8I_MIXER_FBFMT_XBGR8888	5
#घोषणा SUN8I_MIXER_FBFMT_RGBX8888	6
#घोषणा SUN8I_MIXER_FBFMT_BGRX8888	7
#घोषणा SUN8I_MIXER_FBFMT_RGB888	8
#घोषणा SUN8I_MIXER_FBFMT_BGR888	9
#घोषणा SUN8I_MIXER_FBFMT_RGB565	10
#घोषणा SUN8I_MIXER_FBFMT_BGR565	11
#घोषणा SUN8I_MIXER_FBFMT_ARGB4444	12
#घोषणा SUN8I_MIXER_FBFMT_ABGR4444	13
#घोषणा SUN8I_MIXER_FBFMT_RGBA4444	14
#घोषणा SUN8I_MIXER_FBFMT_BGRA4444	15
#घोषणा SUN8I_MIXER_FBFMT_ARGB1555	16
#घोषणा SUN8I_MIXER_FBFMT_ABGR1555	17
#घोषणा SUN8I_MIXER_FBFMT_RGBA5551	18
#घोषणा SUN8I_MIXER_FBFMT_BGRA5551	19
#घोषणा SUN8I_MIXER_FBFMT_ARGB2101010	20
#घोषणा SUN8I_MIXER_FBFMT_ABGR2101010	21
#घोषणा SUN8I_MIXER_FBFMT_RGBA1010102	22
#घोषणा SUN8I_MIXER_FBFMT_BGRA1010102	23

#घोषणा SUN8I_MIXER_FBFMT_YUYV		0
#घोषणा SUN8I_MIXER_FBFMT_UYVY		1
#घोषणा SUN8I_MIXER_FBFMT_YVYU		2
#घोषणा SUN8I_MIXER_FBFMT_VYUY		3
#घोषणा SUN8I_MIXER_FBFMT_NV16		4
#घोषणा SUN8I_MIXER_FBFMT_NV61		5
#घोषणा SUN8I_MIXER_FBFMT_YUV422	6
/* क्रमmat 7 करोesn't exist */
#घोषणा SUN8I_MIXER_FBFMT_NV12		8
#घोषणा SUN8I_MIXER_FBFMT_NV21		9
#घोषणा SUN8I_MIXER_FBFMT_YUV420	10
/* क्रमmat 11 करोesn't exist */
/* क्रमmat 12 is semi-planar YUV411 UVUV */
/* क्रमmat 13 is semi-planar YUV411 VUVU */
#घोषणा SUN8I_MIXER_FBFMT_YUV411	14
/* क्रमmat 15 करोesn't exist */
/* क्रमmat 16 is P010 YVU */
#घोषणा SUN8I_MIXER_FBFMT_P010_YUV	17
/* क्रमmat 18 is P210 YVU */
#घोषणा SUN8I_MIXER_FBFMT_P210_YUV	19
/* क्रमmat 20 is packed YVU444 10-bit */
/* क्रमmat 21 is packed YUV444 10-bit */

/*
 * Sub-engines listed bellow are unused क्रम now. The EN रेजिस्टरs are here only
 * to be used to disable these sub-engines.
 */
#घोषणा SUN8I_MIXER_FCE_EN			0xa0000
#घोषणा SUN8I_MIXER_BWS_EN			0xa2000
#घोषणा SUN8I_MIXER_LTI_EN			0xa4000
#घोषणा SUN8I_MIXER_PEAK_EN			0xa6000
#घोषणा SUN8I_MIXER_ASE_EN			0xa8000
#घोषणा SUN8I_MIXER_FCC_EN			0xaa000
#घोषणा SUN8I_MIXER_DCSC_EN			0xb0000

#घोषणा SUN50I_MIXER_FCE_EN			0x70000
#घोषणा SUN50I_MIXER_PEAK_EN			0x70800
#घोषणा SUN50I_MIXER_LCTI_EN			0x71000
#घोषणा SUN50I_MIXER_BLS_EN			0x71800
#घोषणा SUN50I_MIXER_FCC_EN			0x72000
#घोषणा SUN50I_MIXER_DNS_EN			0x80000
#घोषणा SUN50I_MIXER_DRC_EN			0xa0000
#घोषणा SUN50I_MIXER_FMT_EN			0xa8000
#घोषणा SUN50I_MIXER_CDC0_EN			0xd0000
#घोषणा SUN50I_MIXER_CDC1_EN			0xd8000

/**
 * काष्ठा sun8i_mixer_cfg - mixer HW configuration
 * @vi_num: number of VI channels
 * @ui_num: number of UI channels
 * @scaler_mask: biपंचांगask which tells which channel supports scaling
 *	First, scaler supports क्रम VI channels is defined and after that, scaler
 *	support क्रम UI channels. For example, अगर mixer has 2 VI channels without
 *	scaler and 2 UI channels with scaler, biपंचांगask would be 0xC.
 * @ccsc: select set of CCSC base addresses
 *	Set value to 0 अगर this is first mixer or second mixer with VEP support.
 *	Set value to 1 अगर this is second mixer without VEP support. Other values
 *	are invalid.
 * @mod_rate: module घड़ी rate that needs to be set in order to have
 *	a functional block.
 * @is_de3: true, अगर this is next gen display engine 3.0, false otherwise.
 * @scaline_yuv: size of a scanline क्रम VI scaler क्रम YUV क्रमmats.
 */
काष्ठा sun8i_mixer_cfg अणु
	पूर्णांक		vi_num;
	पूर्णांक		ui_num;
	पूर्णांक		scaler_mask;
	पूर्णांक		ccsc;
	अचिन्हित दीर्घ	mod_rate;
	अचिन्हित पूर्णांक	is_de3 : 1;
	अचिन्हित पूर्णांक	scanline_yuv;
पूर्ण;

काष्ठा sun8i_mixer अणु
	काष्ठा sunxi_engine		engine;

	स्थिर काष्ठा sun8i_mixer_cfg	*cfg;

	काष्ठा reset_control		*reset;

	काष्ठा clk			*bus_clk;
	काष्ठा clk			*mod_clk;
पूर्ण;

अटल अंतरभूत काष्ठा sun8i_mixer *
engine_to_sun8i_mixer(काष्ठा sunxi_engine *engine)
अणु
	वापस container_of(engine, काष्ठा sun8i_mixer, engine);
पूर्ण

अटल अंतरभूत u32
sun8i_blender_base(काष्ठा sun8i_mixer *mixer)
अणु
	वापस mixer->cfg->is_de3 ? DE3_BLD_BASE : DE2_BLD_BASE;
पूर्ण

अटल अंतरभूत u32
sun8i_channel_base(काष्ठा sun8i_mixer *mixer, पूर्णांक channel)
अणु
	अगर (mixer->cfg->is_de3)
		वापस DE3_CH_BASE + channel * DE3_CH_SIZE;
	अन्यथा
		वापस DE2_CH_BASE + channel * DE2_CH_SIZE;
पूर्ण

पूर्णांक sun8i_mixer_drm_क्रमmat_to_hw(u32 क्रमmat, u32 *hw_क्रमmat);
#पूर्ण_अगर /* _SUN8I_MIXER_H_ */
