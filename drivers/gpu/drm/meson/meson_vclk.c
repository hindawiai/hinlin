<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 */

#समावेश <linux/export.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "meson_drv.h"
#समावेश "meson_vclk.h"

/**
 * DOC: Video Clocks
 *
 * VCLK is the "Pixel Clock" frequency generator from a dedicated PLL.
 * We handle the following encodings :
 *
 * - CVBS 27MHz generator via the VCLK2 to the VENCI and VDAC blocks
 * - HDMI Pixel Clocks generation
 *
 * What is missing :
 *
 * - Genenate Pixel घड़ीs क्रम 2K/4K 10bit क्रमmats
 *
 * Clock generator scheme :
 *
 * .. code::
 *
 *    __________   _________            _____
 *   |          | |         |          |     |--ENCI
 *   | HDMI PLL |-| PLL_DIV |--- VCLK--|     |--ENCL
 *   |__________| |_________| \        | MUX |--ENCP
 *                             --VCLK2-|     |--VDAC
 *                                     |_____|--HDMI-TX
 *
 * Final घड़ीs can take input क्रम either VCLK or VCLK2, but
 * VCLK is the preferred path क्रम HDMI घड़ीing and VCLK2 is the
 * preferred path क्रम CVBS VDAC घड़ीing.
 *
 * VCLK and VCLK2 have fixed भागided घड़ीs paths क्रम /1, /2, /4, /6 or /12.
 *
 * The PLL_DIV can achieve an additional fractional भागiding like
 * 1.5, 3.5, 3.75... to generate special 2K and 4K 10bit घड़ीs.
 */

/* HHI Registers */
#घोषणा HHI_VID_PLL_CLK_DIV	0x1a0 /* 0x68 offset in data sheet */
#घोषणा VID_PLL_EN		BIT(19)
#घोषणा VID_PLL_BYPASS		BIT(18)
#घोषणा VID_PLL_PRESET		BIT(15)
#घोषणा HHI_VIID_CLK_DIV	0x128 /* 0x4a offset in data sheet */
#घोषणा VCLK2_DIV_MASK		0xff
#घोषणा VCLK2_DIV_EN		BIT(16)
#घोषणा VCLK2_DIV_RESET		BIT(17)
#घोषणा CTS_VDAC_SEL_MASK	(0xf << 28)
#घोषणा CTS_VDAC_SEL_SHIFT	28
#घोषणा HHI_VIID_CLK_CNTL	0x12c /* 0x4b offset in data sheet */
#घोषणा VCLK2_EN		BIT(19)
#घोषणा VCLK2_SEL_MASK		(0x7 << 16)
#घोषणा VCLK2_SEL_SHIFT		16
#घोषणा VCLK2_SOFT_RESET	BIT(15)
#घोषणा VCLK2_DIV1_EN		BIT(0)
#घोषणा HHI_VID_CLK_DIV		0x164 /* 0x59 offset in data sheet */
#घोषणा VCLK_DIV_MASK		0xff
#घोषणा VCLK_DIV_EN		BIT(16)
#घोषणा VCLK_DIV_RESET		BIT(17)
#घोषणा CTS_ENCP_SEL_MASK	(0xf << 24)
#घोषणा CTS_ENCP_SEL_SHIFT	24
#घोषणा CTS_ENCI_SEL_MASK	(0xf << 28)
#घोषणा CTS_ENCI_SEL_SHIFT	28
#घोषणा HHI_VID_CLK_CNTL	0x17c /* 0x5f offset in data sheet */
#घोषणा VCLK_EN			BIT(19)
#घोषणा VCLK_SEL_MASK		(0x7 << 16)
#घोषणा VCLK_SEL_SHIFT		16
#घोषणा VCLK_SOFT_RESET		BIT(15)
#घोषणा VCLK_DIV1_EN		BIT(0)
#घोषणा VCLK_DIV2_EN		BIT(1)
#घोषणा VCLK_DIV4_EN		BIT(2)
#घोषणा VCLK_DIV6_EN		BIT(3)
#घोषणा VCLK_DIV12_EN		BIT(4)
#घोषणा HHI_VID_CLK_CNTL2	0x194 /* 0x65 offset in data sheet */
#घोषणा CTS_ENCI_EN		BIT(0)
#घोषणा CTS_ENCP_EN		BIT(2)
#घोषणा CTS_VDAC_EN		BIT(4)
#घोषणा HDMI_TX_PIXEL_EN	BIT(5)
#घोषणा HHI_HDMI_CLK_CNTL	0x1cc /* 0x73 offset in data sheet */
#घोषणा HDMI_TX_PIXEL_SEL_MASK	(0xf << 16)
#घोषणा HDMI_TX_PIXEL_SEL_SHIFT	16
#घोषणा CTS_HDMI_SYS_SEL_MASK	(0x7 << 9)
#घोषणा CTS_HDMI_SYS_DIV_MASK	(0x7f)
#घोषणा CTS_HDMI_SYS_EN		BIT(8)

#घोषणा HHI_VDAC_CNTL0		0x2F4 /* 0xbd offset in data sheet */
#घोषणा HHI_VDAC_CNTL1		0x2F8 /* 0xbe offset in data sheet */

#घोषणा HHI_HDMI_PLL_CNTL	0x320 /* 0xc8 offset in data sheet */
#घोषणा HHI_HDMI_PLL_CNTL_EN	BIT(30)
#घोषणा HHI_HDMI_PLL_CNTL2	0x324 /* 0xc9 offset in data sheet */
#घोषणा HHI_HDMI_PLL_CNTL3	0x328 /* 0xca offset in data sheet */
#घोषणा HHI_HDMI_PLL_CNTL4	0x32C /* 0xcb offset in data sheet */
#घोषणा HHI_HDMI_PLL_CNTL5	0x330 /* 0xcc offset in data sheet */
#घोषणा HHI_HDMI_PLL_CNTL6	0x334 /* 0xcd offset in data sheet */
#घोषणा HHI_HDMI_PLL_CNTL7	0x338 /* 0xce offset in data sheet */

#घोषणा HDMI_PLL_RESET		BIT(28)
#घोषणा HDMI_PLL_RESET_G12A	BIT(29)
#घोषणा HDMI_PLL_LOCK		BIT(31)
#घोषणा HDMI_PLL_LOCK_G12A	(3 << 30)

#घोषणा FREQ_1000_1001(_freq)	DIV_ROUND_CLOSEST(_freq * 1000, 1001)

/* VID PLL Dividers */
क्रमागत अणु
	VID_PLL_DIV_1 = 0,
	VID_PLL_DIV_2,
	VID_PLL_DIV_2p5,
	VID_PLL_DIV_3,
	VID_PLL_DIV_3p5,
	VID_PLL_DIV_3p75,
	VID_PLL_DIV_4,
	VID_PLL_DIV_5,
	VID_PLL_DIV_6,
	VID_PLL_DIV_6p25,
	VID_PLL_DIV_7,
	VID_PLL_DIV_7p5,
	VID_PLL_DIV_12,
	VID_PLL_DIV_14,
	VID_PLL_DIV_15,
पूर्ण;

अटल व्योम meson_vid_pll_set(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक भाग)
अणु
	अचिन्हित पूर्णांक shअगरt_val = 0;
	अचिन्हित पूर्णांक shअगरt_sel = 0;

	/* Disable vid_pll output घड़ी */
	regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV, VID_PLL_EN, 0);
	regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV, VID_PLL_PRESET, 0);

	चयन (भाग) अणु
	हाल VID_PLL_DIV_2:
		shअगरt_val = 0x0aaa;
		shअगरt_sel = 0;
		अवरोध;
	हाल VID_PLL_DIV_2p5:
		shअगरt_val = 0x5294;
		shअगरt_sel = 2;
		अवरोध;
	हाल VID_PLL_DIV_3:
		shअगरt_val = 0x0db6;
		shअगरt_sel = 0;
		अवरोध;
	हाल VID_PLL_DIV_3p5:
		shअगरt_val = 0x36cc;
		shअगरt_sel = 1;
		अवरोध;
	हाल VID_PLL_DIV_3p75:
		shअगरt_val = 0x6666;
		shअगरt_sel = 2;
		अवरोध;
	हाल VID_PLL_DIV_4:
		shअगरt_val = 0x0ccc;
		shअगरt_sel = 0;
		अवरोध;
	हाल VID_PLL_DIV_5:
		shअगरt_val = 0x739c;
		shअगरt_sel = 2;
		अवरोध;
	हाल VID_PLL_DIV_6:
		shअगरt_val = 0x0e38;
		shअगरt_sel = 0;
		अवरोध;
	हाल VID_PLL_DIV_6p25:
		shअगरt_val = 0x0000;
		shअगरt_sel = 3;
		अवरोध;
	हाल VID_PLL_DIV_7:
		shअगरt_val = 0x3c78;
		shअगरt_sel = 1;
		अवरोध;
	हाल VID_PLL_DIV_7p5:
		shअगरt_val = 0x78f0;
		shअगरt_sel = 2;
		अवरोध;
	हाल VID_PLL_DIV_12:
		shअगरt_val = 0x0fc0;
		shअगरt_sel = 0;
		अवरोध;
	हाल VID_PLL_DIV_14:
		shअगरt_val = 0x3f80;
		shअगरt_sel = 1;
		अवरोध;
	हाल VID_PLL_DIV_15:
		shअगरt_val = 0x7f80;
		shअगरt_sel = 2;
		अवरोध;
	पूर्ण

	अगर (भाग == VID_PLL_DIV_1)
		/* Enable vid_pll bypass to HDMI pll */
		regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV,
				   VID_PLL_BYPASS, VID_PLL_BYPASS);
	अन्यथा अणु
		/* Disable Bypass */
		regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV,
				   VID_PLL_BYPASS, 0);
		/* Clear sel */
		regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV,
				   3 << 16, 0);
		regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV,
				   VID_PLL_PRESET, 0);
		regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV,
				   0x7fff, 0);

		/* Setup sel and val */
		regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV,
				   3 << 16, shअगरt_sel << 16);
		regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV,
				   VID_PLL_PRESET, VID_PLL_PRESET);
		regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV,
				   0x7fff, shअगरt_val);

		regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV,
				   VID_PLL_PRESET, 0);
	पूर्ण

	/* Enable the vid_pll output घड़ी */
	regmap_update_bits(priv->hhi, HHI_VID_PLL_CLK_DIV,
				VID_PLL_EN, VID_PLL_EN);
पूर्ण

/*
 * Setup VCLK2 क्रम 27MHz, and enable घड़ीs क्रम ENCI and VDAC
 *
 * TOFIX: Refactor पूर्णांकo table to also handle HDMI frequency and paths
 */
अटल व्योम meson_venci_cvbs_घड़ी_config(काष्ठा meson_drm *priv)
अणु
	अचिन्हित पूर्णांक val;

	/* Setup PLL to output 1.485GHz */
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB)) अणु
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL, 0x5800023d);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL2, 0x00404e00);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL3, 0x0d5c5091);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL4, 0x801da72c);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL5, 0x71486980);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x00000e55);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL, 0x4800023d);

		/* Poll क्रम lock bit */
		regmap_पढ़ो_poll_समयout(priv->hhi, HHI_HDMI_PLL_CNTL, val,
					 (val & HDMI_PLL_LOCK), 10, 0);
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		   meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL)) अणु
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL, 0x4000027b);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL2, 0x800cb300);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL3, 0xa6212844);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL4, 0x0c4d000c);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL5, 0x001fa729);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x01a31500);

		/* Reset PLL */
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
					HDMI_PLL_RESET, HDMI_PLL_RESET);
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
					HDMI_PLL_RESET, 0);

		/* Poll क्रम lock bit */
		regmap_पढ़ो_poll_समयout(priv->hhi, HHI_HDMI_PLL_CNTL, val,
					 (val & HDMI_PLL_LOCK), 10, 0);
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL, 0x1a0504f7);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL2, 0x00010000);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL3, 0x00000000);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL4, 0x6a28dc00);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL5, 0x65771290);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x39272000);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL7, 0x56540000);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL, 0x3a0504f7);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL, 0x1a0504f7);

		/* Poll क्रम lock bit */
		regmap_पढ़ो_poll_समयout(priv->hhi, HHI_HDMI_PLL_CNTL, val,
			((val & HDMI_PLL_LOCK_G12A) == HDMI_PLL_LOCK_G12A),
			10, 0);
	पूर्ण

	/* Disable VCLK2 */
	regmap_update_bits(priv->hhi, HHI_VIID_CLK_CNTL, VCLK2_EN, 0);

	/* Setup vid_pll to /1 */
	meson_vid_pll_set(priv, VID_PLL_DIV_1);

	/* Setup the VCLK2 भागider value to achieve 27MHz */
	regmap_update_bits(priv->hhi, HHI_VIID_CLK_DIV,
				VCLK2_DIV_MASK, (55 - 1));

	/* select vid_pll क्रम vclk2 */
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		regmap_update_bits(priv->hhi, HHI_VIID_CLK_CNTL,
					VCLK2_SEL_MASK, (0 << VCLK2_SEL_SHIFT));
	अन्यथा
		regmap_update_bits(priv->hhi, HHI_VIID_CLK_CNTL,
					VCLK2_SEL_MASK, (4 << VCLK2_SEL_SHIFT));

	/* enable vclk2 gate */
	regmap_update_bits(priv->hhi, HHI_VIID_CLK_CNTL, VCLK2_EN, VCLK2_EN);

	/* select vclk_भाग1 क्रम enci */
	regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCI_SEL_MASK, (8 << CTS_ENCI_SEL_SHIFT));
	/* select vclk_भाग1 क्रम vdac */
	regmap_update_bits(priv->hhi, HHI_VIID_CLK_DIV,
				CTS_VDAC_SEL_MASK, (8 << CTS_VDAC_SEL_SHIFT));

	/* release vclk2_भाग_reset and enable vclk2_भाग */
	regmap_update_bits(priv->hhi, HHI_VIID_CLK_DIV,
				VCLK2_DIV_EN | VCLK2_DIV_RESET, VCLK2_DIV_EN);

	/* enable vclk2_भाग1 gate */
	regmap_update_bits(priv->hhi, HHI_VIID_CLK_CNTL,
				VCLK2_DIV1_EN, VCLK2_DIV1_EN);

	/* reset vclk2 */
	regmap_update_bits(priv->hhi, HHI_VIID_CLK_CNTL,
				VCLK2_SOFT_RESET, VCLK2_SOFT_RESET);
	regmap_update_bits(priv->hhi, HHI_VIID_CLK_CNTL,
				VCLK2_SOFT_RESET, 0);

	/* enable enci_clk */
	regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL2,
				CTS_ENCI_EN, CTS_ENCI_EN);
	/* enable vdac_clk */
	regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL2,
				CTS_VDAC_EN, CTS_VDAC_EN);
पूर्ण

क्रमागत अणु
/* PLL	O1 O2 O3 VP DV     EN TX */
/* 4320 /4 /4 /1 /5 /1  => /2 /2 */
	MESON_VCLK_HDMI_ENCI_54000 = 0,
/* 4320 /4 /4 /1 /5 /1  => /1 /2 */
	MESON_VCLK_HDMI_DDR_54000,
/* 2970 /4 /1 /1 /5 /1  => /1 /2 */
	MESON_VCLK_HDMI_DDR_148500,
/* 2970 /2 /2 /2 /5 /1  => /1 /1 */
	MESON_VCLK_HDMI_74250,
/* 2970 /1 /2 /2 /5 /1  => /1 /1 */
	MESON_VCLK_HDMI_148500,
/* 2970 /1 /1 /1 /5 /2  => /1 /1 */
	MESON_VCLK_HDMI_297000,
/* 5940 /1 /1 /2 /5 /1  => /1 /1 */
	MESON_VCLK_HDMI_594000,
/* 2970 /1 /1 /1 /5 /1  => /1 /2 */
	MESON_VCLK_HDMI_594000_YUV420,
पूर्ण;

काष्ठा meson_vclk_params अणु
	अचिन्हित पूर्णांक pll_freq;
	अचिन्हित पूर्णांक phy_freq;
	अचिन्हित पूर्णांक vclk_freq;
	अचिन्हित पूर्णांक venc_freq;
	अचिन्हित पूर्णांक pixel_freq;
	अचिन्हित पूर्णांक pll_od1;
	अचिन्हित पूर्णांक pll_od2;
	अचिन्हित पूर्णांक pll_od3;
	अचिन्हित पूर्णांक vid_pll_भाग;
	अचिन्हित पूर्णांक vclk_भाग;
पूर्ण params[] = अणु
	[MESON_VCLK_HDMI_ENCI_54000] = अणु
		.pll_freq = 4320000,
		.phy_freq = 270000,
		.vclk_freq = 54000,
		.venc_freq = 54000,
		.pixel_freq = 54000,
		.pll_od1 = 4,
		.pll_od2 = 4,
		.pll_od3 = 1,
		.vid_pll_भाग = VID_PLL_DIV_5,
		.vclk_भाग = 1,
	पूर्ण,
	[MESON_VCLK_HDMI_DDR_54000] = अणु
		.pll_freq = 4320000,
		.phy_freq = 270000,
		.vclk_freq = 54000,
		.venc_freq = 54000,
		.pixel_freq = 27000,
		.pll_od1 = 4,
		.pll_od2 = 4,
		.pll_od3 = 1,
		.vid_pll_भाग = VID_PLL_DIV_5,
		.vclk_भाग = 1,
	पूर्ण,
	[MESON_VCLK_HDMI_DDR_148500] = अणु
		.pll_freq = 2970000,
		.phy_freq = 742500,
		.vclk_freq = 148500,
		.venc_freq = 148500,
		.pixel_freq = 74250,
		.pll_od1 = 4,
		.pll_od2 = 1,
		.pll_od3 = 1,
		.vid_pll_भाग = VID_PLL_DIV_5,
		.vclk_भाग = 1,
	पूर्ण,
	[MESON_VCLK_HDMI_74250] = अणु
		.pll_freq = 2970000,
		.phy_freq = 742500,
		.vclk_freq = 74250,
		.venc_freq = 74250,
		.pixel_freq = 74250,
		.pll_od1 = 2,
		.pll_od2 = 2,
		.pll_od3 = 2,
		.vid_pll_भाग = VID_PLL_DIV_5,
		.vclk_भाग = 1,
	पूर्ण,
	[MESON_VCLK_HDMI_148500] = अणु
		.pll_freq = 2970000,
		.phy_freq = 1485000,
		.vclk_freq = 148500,
		.venc_freq = 148500,
		.pixel_freq = 148500,
		.pll_od1 = 1,
		.pll_od2 = 2,
		.pll_od3 = 2,
		.vid_pll_भाग = VID_PLL_DIV_5,
		.vclk_भाग = 1,
	पूर्ण,
	[MESON_VCLK_HDMI_297000] = अणु
		.pll_freq = 5940000,
		.phy_freq = 2970000,
		.venc_freq = 297000,
		.vclk_freq = 297000,
		.pixel_freq = 297000,
		.pll_od1 = 2,
		.pll_od2 = 1,
		.pll_od3 = 1,
		.vid_pll_भाग = VID_PLL_DIV_5,
		.vclk_भाग = 2,
	पूर्ण,
	[MESON_VCLK_HDMI_594000] = अणु
		.pll_freq = 5940000,
		.phy_freq = 5940000,
		.venc_freq = 594000,
		.vclk_freq = 594000,
		.pixel_freq = 594000,
		.pll_od1 = 1,
		.pll_od2 = 1,
		.pll_od3 = 2,
		.vid_pll_भाग = VID_PLL_DIV_5,
		.vclk_भाग = 1,
	पूर्ण,
	[MESON_VCLK_HDMI_594000_YUV420] = अणु
		.pll_freq = 5940000,
		.phy_freq = 2970000,
		.venc_freq = 594000,
		.vclk_freq = 594000,
		.pixel_freq = 297000,
		.pll_od1 = 2,
		.pll_od2 = 1,
		.pll_od3 = 1,
		.vid_pll_भाग = VID_PLL_DIV_5,
		.vclk_भाग = 1,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक pll_od_to_reg(अचिन्हित पूर्णांक od)
अणु
	चयन (od) अणु
	हाल 1:
		वापस 0;
	हाल 2:
		वापस 1;
	हाल 4:
		वापस 2;
	हाल 8:
		वापस 3;
	पूर्ण

	/* Invalid */
	वापस 0;
पूर्ण

अटल व्योम meson_hdmi_pll_set_params(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक m,
				      अचिन्हित पूर्णांक frac, अचिन्हित पूर्णांक od1,
				      अचिन्हित पूर्णांक od2, अचिन्हित पूर्णांक od3)
अणु
	अचिन्हित पूर्णांक val;

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB)) अणु
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL, 0x58000200 | m);
		अगर (frac)
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL2,
				     0x00004000 | frac);
		अन्यथा
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL2,
				     0x00000000);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL3, 0x0d5c5091);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL4, 0x801da72c);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL5, 0x71486980);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x00000e55);

		/* Enable and unreset */
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				   0x7 << 28, HHI_HDMI_PLL_CNTL_EN);

		/* Poll क्रम lock bit */
		regmap_पढ़ो_poll_समयout(priv->hhi, HHI_HDMI_PLL_CNTL,
					 val, (val & HDMI_PLL_LOCK), 10, 0);
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		   meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL)) अणु
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL, 0x40000200 | m);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL2, 0x800cb000 | frac);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL3, 0x860f30c4);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL4, 0x0c8e0000);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL5, 0x001fa729);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x01a31500);

		/* Reset PLL */
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				HDMI_PLL_RESET, HDMI_PLL_RESET);
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				HDMI_PLL_RESET, 0);

		/* Poll क्रम lock bit */
		regmap_पढ़ो_poll_समयout(priv->hhi, HHI_HDMI_PLL_CNTL, val,
				(val & HDMI_PLL_LOCK), 10, 0);
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL, 0x0b3a0400 | m);

		/* Enable and reset */
		/* TODO: add specअगरic macro क्रम g12a here */
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				   0x3 << 28, 0x3 << 28);

		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL2, frac);
		regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL3, 0x00000000);

		/* G12A HDMI PLL Needs specअगरic parameters क्रम 5.4GHz */
		अगर (m >= 0xf7) अणु
			अगर (frac < 0x10000) अणु
				regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL4,
							0x6a685c00);
				regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL5,
							0x11551293);
			पूर्ण अन्यथा अणु
				regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL4,
							0xea68dc00);
				regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL5,
							0x65771290);
			पूर्ण
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x39272000);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL7, 0x55540000);
		पूर्ण अन्यथा अणु
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL4, 0x0a691c00);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL5, 0x33771290);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x39270000);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PLL_CNTL7, 0x50540000);
		पूर्ण

		करो अणु
			/* Reset PLL */
			regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
					HDMI_PLL_RESET_G12A, HDMI_PLL_RESET_G12A);

			/* UN-Reset PLL */
			regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
					HDMI_PLL_RESET_G12A, 0);

			/* Poll क्रम lock bits */
			अगर (!regmap_पढ़ो_poll_समयout(priv->hhi,
						      HHI_HDMI_PLL_CNTL, val,
						      ((val & HDMI_PLL_LOCK_G12A)
						        == HDMI_PLL_LOCK_G12A),
						      10, 100))
				अवरोध;
		पूर्ण जबतक(1);
	पूर्ण

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL2,
				3 << 16, pll_od_to_reg(od1) << 16);
	अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		 meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL3,
				3 << 21, pll_od_to_reg(od1) << 21);
	अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				3 << 16, pll_od_to_reg(od1) << 16);

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL2,
				3 << 22, pll_od_to_reg(od2) << 22);
	अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		 meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL3,
				3 << 23, pll_od_to_reg(od2) << 23);
	अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				3 << 18, pll_od_to_reg(od2) << 18);

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL2,
				3 << 18, pll_od_to_reg(od3) << 18);
	अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		 meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL3,
				3 << 19, pll_od_to_reg(od3) << 19);
	अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				3 << 20, pll_od_to_reg(od3) << 20);
पूर्ण

#घोषणा XTAL_FREQ 24000

अटल अचिन्हित पूर्णांक meson_hdmi_pll_get_m(काष्ठा meson_drm *priv,
					 अचिन्हित पूर्णांक pll_freq)
अणु
	/* The GXBB PLL has a /2 pre-multiplier */
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB))
		pll_freq /= 2;

	वापस pll_freq / XTAL_FREQ;
पूर्ण

#घोषणा HDMI_FRAC_MAX_GXBB	4096
#घोषणा HDMI_FRAC_MAX_GXL	1024
#घोषणा HDMI_FRAC_MAX_G12A	131072

अटल अचिन्हित पूर्णांक meson_hdmi_pll_get_frac(काष्ठा meson_drm *priv,
					    अचिन्हित पूर्णांक m,
					    अचिन्हित पूर्णांक pll_freq)
अणु
	अचिन्हित पूर्णांक parent_freq = XTAL_FREQ;
	अचिन्हित पूर्णांक frac_max = HDMI_FRAC_MAX_GXL;
	अचिन्हित पूर्णांक frac_m;
	अचिन्हित पूर्णांक frac;

	/* The GXBB PLL has a /2 pre-multiplier and a larger FRAC width */
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB)) अणु
		frac_max = HDMI_FRAC_MAX_GXBB;
		parent_freq *= 2;
	पूर्ण

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		frac_max = HDMI_FRAC_MAX_G12A;

	/* We can have a perfect match !*/
	अगर (pll_freq / m == parent_freq &&
	    pll_freq % m == 0)
		वापस 0;

	frac = भाग_u64((u64)pll_freq * (u64)frac_max, parent_freq);
	frac_m = m * frac_max;
	अगर (frac_m > frac)
		वापस frac_max;
	frac -= frac_m;

	वापस min((u16)frac, (u16)(frac_max - 1));
पूर्ण

अटल bool meson_hdmi_pll_validate_params(काष्ठा meson_drm *priv,
					   अचिन्हित पूर्णांक m,
					   अचिन्हित पूर्णांक frac)
अणु
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB)) अणु
		/* Empiric supported min/max भागiders */
		अगर (m < 53 || m > 123)
			वापस false;
		अगर (frac >= HDMI_FRAC_MAX_GXBB)
			वापस false;
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		   meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL)) अणु
		/* Empiric supported min/max भागiders */
		अगर (m < 106 || m > 247)
			वापस false;
		अगर (frac >= HDMI_FRAC_MAX_GXL)
			वापस false;
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		/* Empiric supported min/max भागiders */
		अगर (m < 106 || m > 247)
			वापस false;
		अगर (frac >= HDMI_FRAC_MAX_G12A)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool meson_hdmi_pll_find_params(काष्ठा meson_drm *priv,
				       अचिन्हित पूर्णांक freq,
				       अचिन्हित पूर्णांक *m,
				       अचिन्हित पूर्णांक *frac,
				       अचिन्हित पूर्णांक *od)
अणु
	/* Cycle from /16 to /2 */
	क्रम (*od = 16 ; *od > 1 ; *od >>= 1) अणु
		*m = meson_hdmi_pll_get_m(priv, freq * *od);
		अगर (!*m)
			जारी;
		*frac = meson_hdmi_pll_get_frac(priv, *m, freq * *od);

		DRM_DEBUG_DRIVER("PLL params for %dkHz: m=%x frac=%x od=%d\n",
				 freq, *m, *frac, *od);

		अगर (meson_hdmi_pll_validate_params(priv, *m, *frac))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* pll_freq is the frequency after the OD भागiders */
क्रमागत drm_mode_status
meson_vclk_dmt_supported_freq(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित पूर्णांक od, m, frac;

	/* In DMT mode, path after PLL is always /10 */
	freq *= 10;

	/* Check against soc revision/package limits */
	अगर (priv->limits) अणु
		अगर (priv->limits->max_hdmi_phy_freq &&
		    freq > priv->limits->max_hdmi_phy_freq)
			वापस MODE_CLOCK_HIGH;
	पूर्ण

	अगर (meson_hdmi_pll_find_params(priv, freq, &m, &frac, &od))
		वापस MODE_OK;

	वापस MODE_CLOCK_RANGE;
पूर्ण
EXPORT_SYMBOL_GPL(meson_vclk_dmt_supported_freq);

/* pll_freq is the frequency after the OD भागiders */
अटल व्योम meson_hdmi_pll_generic_set(काष्ठा meson_drm *priv,
				       अचिन्हित पूर्णांक pll_freq)
अणु
	अचिन्हित पूर्णांक od, m, frac, od1, od2, od3;

	अगर (meson_hdmi_pll_find_params(priv, pll_freq, &m, &frac, &od)) अणु
		/* OD2 goes to the PHY, and needs to be *10, so keep OD3=1 */
		od3 = 1;
		अगर (od < 4) अणु
			od1 = 2;
			od2 = 1;
		पूर्ण अन्यथा अणु
			od2 = od / 4;
			od1 = od / od2;
		पूर्ण

		DRM_DEBUG_DRIVER("PLL params for %dkHz: m=%x frac=%x od=%d/%d/%d\n",
				 pll_freq, m, frac, od1, od2, od3);

		meson_hdmi_pll_set_params(priv, m, frac, od1, od2, od3);

		वापस;
	पूर्ण

	DRM_ERROR("Fatal, unable to find parameters for PLL freq %d\n",
		  pll_freq);
पूर्ण

क्रमागत drm_mode_status
meson_vclk_vic_supported_freq(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक phy_freq,
			      अचिन्हित पूर्णांक vclk_freq)
अणु
	पूर्णांक i;

	DRM_DEBUG_DRIVER("phy_freq = %d vclk_freq = %d\n",
			 phy_freq, vclk_freq);

	/* Check against soc revision/package limits */
	अगर (priv->limits) अणु
		अगर (priv->limits->max_hdmi_phy_freq &&
		    phy_freq > priv->limits->max_hdmi_phy_freq)
			वापस MODE_CLOCK_HIGH;
	पूर्ण

	क्रम (i = 0 ; params[i].pixel_freq ; ++i) अणु
		DRM_DEBUG_DRIVER("i = %d pixel_freq = %d alt = %d\n",
				 i, params[i].pixel_freq,
				 FREQ_1000_1001(params[i].pixel_freq));
		DRM_DEBUG_DRIVER("i = %d phy_freq = %d alt = %d\n",
				 i, params[i].phy_freq,
				 FREQ_1000_1001(params[i].phy_freq/10)*10);
		/* Match strict frequency */
		अगर (phy_freq == params[i].phy_freq &&
		    vclk_freq == params[i].vclk_freq)
			वापस MODE_OK;
		/* Match 1000/1001 variant */
		अगर (phy_freq == (FREQ_1000_1001(params[i].phy_freq/10)*10) &&
		    vclk_freq == FREQ_1000_1001(params[i].vclk_freq))
			वापस MODE_OK;
	पूर्ण

	वापस MODE_CLOCK_RANGE;
पूर्ण
EXPORT_SYMBOL_GPL(meson_vclk_vic_supported_freq);

अटल व्योम meson_vclk_set(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक pll_base_freq,
			   अचिन्हित पूर्णांक od1, अचिन्हित पूर्णांक od2, अचिन्हित पूर्णांक od3,
			   अचिन्हित पूर्णांक vid_pll_भाग, अचिन्हित पूर्णांक vclk_भाग,
			   अचिन्हित पूर्णांक hdmi_tx_भाग, अचिन्हित पूर्णांक venc_भाग,
			   bool hdmi_use_enci, bool vic_alternate_घड़ी)
अणु
	अचिन्हित पूर्णांक m = 0, frac = 0;

	/* Set HDMI-TX sys घड़ी */
	regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			   CTS_HDMI_SYS_SEL_MASK, 0);
	regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			   CTS_HDMI_SYS_DIV_MASK, 0);
	regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			   CTS_HDMI_SYS_EN, CTS_HDMI_SYS_EN);

	/* Set HDMI PLL rate */
	अगर (!od1 && !od2 && !od3) अणु
		meson_hdmi_pll_generic_set(priv, pll_base_freq);
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB)) अणु
		चयन (pll_base_freq) अणु
		हाल 2970000:
			m = 0x3d;
			frac = vic_alternate_घड़ी ? 0xd02 : 0xe00;
			अवरोध;
		हाल 4320000:
			m = vic_alternate_घड़ी ? 0x59 : 0x5a;
			frac = vic_alternate_घड़ी ? 0xe8f : 0;
			अवरोध;
		हाल 5940000:
			m = 0x7b;
			frac = vic_alternate_घड़ी ? 0xa05 : 0xc00;
			अवरोध;
		पूर्ण

		meson_hdmi_pll_set_params(priv, m, frac, od1, od2, od3);
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		   meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL)) अणु
		चयन (pll_base_freq) अणु
		हाल 2970000:
			m = 0x7b;
			frac = vic_alternate_घड़ी ? 0x281 : 0x300;
			अवरोध;
		हाल 4320000:
			m = vic_alternate_घड़ी ? 0xb3 : 0xb4;
			frac = vic_alternate_घड़ी ? 0x347 : 0;
			अवरोध;
		हाल 5940000:
			m = 0xf7;
			frac = vic_alternate_घड़ी ? 0x102 : 0x200;
			अवरोध;
		पूर्ण

		meson_hdmi_pll_set_params(priv, m, frac, od1, od2, od3);
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		चयन (pll_base_freq) अणु
		हाल 2970000:
			m = 0x7b;
			frac = vic_alternate_घड़ी ? 0x140b4 : 0x18000;
			अवरोध;
		हाल 4320000:
			m = vic_alternate_घड़ी ? 0xb3 : 0xb4;
			frac = vic_alternate_घड़ी ? 0x1a3ee : 0;
			अवरोध;
		हाल 5940000:
			m = 0xf7;
			frac = vic_alternate_घड़ी ? 0x8148 : 0x10000;
			अवरोध;
		पूर्ण

		meson_hdmi_pll_set_params(priv, m, frac, od1, od2, od3);
	पूर्ण

	/* Setup vid_pll भागider */
	meson_vid_pll_set(priv, vid_pll_भाग);

	/* Set VCLK भाग */
	regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
			   VCLK_SEL_MASK, 0);
	regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
			   VCLK_DIV_MASK, vclk_भाग - 1);

	/* Set HDMI-TX source */
	चयन (hdmi_tx_भाग) अणु
	हाल 1:
		/* enable vclk_भाग1 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV1_EN, VCLK_DIV1_EN);

		/* select vclk_भाग1 क्रम HDMI-TX */
		regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
				   HDMI_TX_PIXEL_SEL_MASK, 0);
		अवरोध;
	हाल 2:
		/* enable vclk_भाग2 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV2_EN, VCLK_DIV2_EN);

		/* select vclk_भाग2 क्रम HDMI-TX */
		regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			HDMI_TX_PIXEL_SEL_MASK, 1 << HDMI_TX_PIXEL_SEL_SHIFT);
		अवरोध;
	हाल 4:
		/* enable vclk_भाग4 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV4_EN, VCLK_DIV4_EN);

		/* select vclk_भाग4 क्रम HDMI-TX */
		regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			HDMI_TX_PIXEL_SEL_MASK, 2 << HDMI_TX_PIXEL_SEL_SHIFT);
		अवरोध;
	हाल 6:
		/* enable vclk_भाग6 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV6_EN, VCLK_DIV6_EN);

		/* select vclk_भाग6 क्रम HDMI-TX */
		regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			HDMI_TX_PIXEL_SEL_MASK, 3 << HDMI_TX_PIXEL_SEL_SHIFT);
		अवरोध;
	हाल 12:
		/* enable vclk_भाग12 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV12_EN, VCLK_DIV12_EN);

		/* select vclk_भाग12 क्रम HDMI-TX */
		regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL,
			HDMI_TX_PIXEL_SEL_MASK, 4 << HDMI_TX_PIXEL_SEL_SHIFT);
		अवरोध;
	पूर्ण
	regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL2,
				   HDMI_TX_PIXEL_EN, HDMI_TX_PIXEL_EN);

	/* Set ENCI/ENCP Source */
	चयन (venc_भाग) अणु
	हाल 1:
		/* enable vclk_भाग1 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV1_EN, VCLK_DIV1_EN);

		अगर (hdmi_use_enci)
			/* select vclk_भाग1 क्रम enci */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
					   CTS_ENCI_SEL_MASK, 0);
		अन्यथा
			/* select vclk_भाग1 क्रम encp */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
					   CTS_ENCP_SEL_MASK, 0);
		अवरोध;
	हाल 2:
		/* enable vclk_भाग2 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV2_EN, VCLK_DIV2_EN);

		अगर (hdmi_use_enci)
			/* select vclk_भाग2 क्रम enci */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCI_SEL_MASK, 1 << CTS_ENCI_SEL_SHIFT);
		अन्यथा
			/* select vclk_भाग2 क्रम encp */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCP_SEL_MASK, 1 << CTS_ENCP_SEL_SHIFT);
		अवरोध;
	हाल 4:
		/* enable vclk_भाग4 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV4_EN, VCLK_DIV4_EN);

		अगर (hdmi_use_enci)
			/* select vclk_भाग4 क्रम enci */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCI_SEL_MASK, 2 << CTS_ENCI_SEL_SHIFT);
		अन्यथा
			/* select vclk_भाग4 क्रम encp */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCP_SEL_MASK, 2 << CTS_ENCP_SEL_SHIFT);
		अवरोध;
	हाल 6:
		/* enable vclk_भाग6 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV6_EN, VCLK_DIV6_EN);

		अगर (hdmi_use_enci)
			/* select vclk_भाग6 क्रम enci */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCI_SEL_MASK, 3 << CTS_ENCI_SEL_SHIFT);
		अन्यथा
			/* select vclk_भाग6 क्रम encp */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCP_SEL_MASK, 3 << CTS_ENCP_SEL_SHIFT);
		अवरोध;
	हाल 12:
		/* enable vclk_भाग12 gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL,
				   VCLK_DIV12_EN, VCLK_DIV12_EN);

		अगर (hdmi_use_enci)
			/* select vclk_भाग12 क्रम enci */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCI_SEL_MASK, 4 << CTS_ENCI_SEL_SHIFT);
		अन्यथा
			/* select vclk_भाग12 क्रम encp */
			regmap_update_bits(priv->hhi, HHI_VID_CLK_DIV,
				CTS_ENCP_SEL_MASK, 4 << CTS_ENCP_SEL_SHIFT);
		अवरोध;
	पूर्ण

	अगर (hdmi_use_enci)
		/* Enable ENCI घड़ी gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL2,
				   CTS_ENCI_EN, CTS_ENCI_EN);
	अन्यथा
		/* Enable ENCP घड़ी gate */
		regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL2,
				   CTS_ENCP_EN, CTS_ENCP_EN);

	regmap_update_bits(priv->hhi, HHI_VID_CLK_CNTL, VCLK_EN, VCLK_EN);
पूर्ण

व्योम meson_vclk_setup(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक target,
		      अचिन्हित पूर्णांक phy_freq, अचिन्हित पूर्णांक vclk_freq,
		      अचिन्हित पूर्णांक venc_freq, अचिन्हित पूर्णांक dac_freq,
		      bool hdmi_use_enci)
अणु
	bool vic_alternate_घड़ी = false;
	अचिन्हित पूर्णांक freq;
	अचिन्हित पूर्णांक hdmi_tx_भाग;
	अचिन्हित पूर्णांक venc_भाग;

	अगर (target == MESON_VCLK_TARGET_CVBS) अणु
		meson_venci_cvbs_घड़ी_config(priv);
		वापस;
	पूर्ण अन्यथा अगर (target == MESON_VCLK_TARGET_DMT) अणु
		/*
		 * The DMT घड़ी path is fixed after the PLL:
		 * - स्वतःmatic PLL freq + OD management
		 * - vid_pll_भाग = VID_PLL_DIV_5
		 * - vclk_भाग = 2
		 * - hdmi_tx_भाग = 1
		 * - venc_भाग = 1
		 * - encp encoder
		 */
		meson_vclk_set(priv, phy_freq, 0, 0, 0,
			       VID_PLL_DIV_5, 2, 1, 1, false, false);
		वापस;
	पूर्ण

	hdmi_tx_भाग = vclk_freq / dac_freq;

	अगर (hdmi_tx_भाग == 0) अणु
		pr_err("Fatal Error, invalid HDMI-TX freq %d\n",
		       dac_freq);
		वापस;
	पूर्ण

	venc_भाग = vclk_freq / venc_freq;

	अगर (venc_भाग == 0) अणु
		pr_err("Fatal Error, invalid HDMI venc freq %d\n",
		       venc_freq);
		वापस;
	पूर्ण

	क्रम (freq = 0 ; params[freq].pixel_freq ; ++freq) अणु
		अगर ((phy_freq == params[freq].phy_freq ||
		     phy_freq == FREQ_1000_1001(params[freq].phy_freq/10)*10) &&
		    (vclk_freq == params[freq].vclk_freq ||
		     vclk_freq == FREQ_1000_1001(params[freq].vclk_freq))) अणु
			अगर (vclk_freq != params[freq].vclk_freq)
				vic_alternate_घड़ी = true;
			अन्यथा
				vic_alternate_घड़ी = false;

			अगर (freq == MESON_VCLK_HDMI_ENCI_54000 &&
			    !hdmi_use_enci)
				जारी;

			अगर (freq == MESON_VCLK_HDMI_DDR_54000 &&
			    hdmi_use_enci)
				जारी;

			अगर (freq == MESON_VCLK_HDMI_DDR_148500 &&
			    dac_freq == vclk_freq)
				जारी;

			अगर (freq == MESON_VCLK_HDMI_148500 &&
			    dac_freq != vclk_freq)
				जारी;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!params[freq].pixel_freq) अणु
		pr_err("Fatal Error, invalid HDMI vclk freq %d\n", vclk_freq);
		वापस;
	पूर्ण

	meson_vclk_set(priv, params[freq].pll_freq,
		       params[freq].pll_od1, params[freq].pll_od2,
		       params[freq].pll_od3, params[freq].vid_pll_भाग,
		       params[freq].vclk_भाग, hdmi_tx_भाग, venc_भाग,
		       hdmi_use_enci, vic_alternate_घड़ी);
पूर्ण
EXPORT_SYMBOL_GPL(meson_vclk_setup);
