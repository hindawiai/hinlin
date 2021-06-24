<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 * Copyright (C) 2014 Endless Mobile
 */

#समावेश <linux/export.h>
#समावेश <linux/bitfield.h>

#समावेश <drm/drm_fourcc.h>

#समावेश "meson_drv.h"
#समावेश "meson_viu.h"
#समावेश "meson_registers.h"

/**
 * DOC: Video Input Unit
 *
 * VIU Handles the Pixel scanout and the basic Colorspace conversions
 * We handle the following features :
 *
 * - OSD1 RGB565/RGB888/xRGB8888 scanout
 * - RGB conversion to x/cb/cr
 * - Progressive or Interlace buffer scanout
 * - OSD1 Commit on Vsync
 * - HDR OSD matrix क्रम GXL/GXM
 *
 * What is missing :
 *
 * - BGR888/xBGR8888/BGRx8888/BGRx8888 modes
 * - YUV4:2:2 Y0CbY1Cr scanout
 * - Conversion to YUV 4:4:4 from 4:2:2 input
 * - Colorkey Alpha matching
 * - Big endian scanout
 * - X/Y reverse scanout
 * - Global alpha setup
 * - OSD2 support, would need पूर्णांकerlace चयनing on vsync
 * - OSD1 full scaling to support TV overscan
 */

/* OSD csc defines */

क्रमागत viu_matrix_sel_e अणु
	VIU_MATRIX_OSD_EOTF = 0,
	VIU_MATRIX_OSD,
पूर्ण;

क्रमागत viu_lut_sel_e अणु
	VIU_LUT_OSD_EOTF = 0,
	VIU_LUT_OSD_OETF,
पूर्ण;

#घोषणा COEFF_NORM(a) ((पूर्णांक)((((a) * 2048.0) + 1) / 2))
#घोषणा MATRIX_5X3_COEF_SIZE 24

#घोषणा EOTF_COEFF_NORM(a) ((पूर्णांक)((((a) * 4096.0) + 1) / 2))
#घोषणा EOTF_COEFF_SIZE 10
#घोषणा EOTF_COEFF_RIGHTSHIFT 1

अटल पूर्णांक RGB709_to_YUV709l_coeff[MATRIX_5X3_COEF_SIZE] = अणु
	0, 0, 0, /* pre offset */
	COEFF_NORM(0.181873),	COEFF_NORM(0.611831),	COEFF_NORM(0.061765),
	COEFF_NORM(-0.100251),	COEFF_NORM(-0.337249),	COEFF_NORM(0.437500),
	COEFF_NORM(0.437500),	COEFF_NORM(-0.397384),	COEFF_NORM(-0.040116),
	0, 0, 0, /* 10'/11'/12' */
	0, 0, 0, /* 20'/21'/22' */
	64, 512, 512, /* offset */
	0, 0, 0 /* mode, right_shअगरt, clip_en */
पूर्ण;

/*  eotf matrix: bypass */
अटल पूर्णांक eotf_bypass_coeff[EOTF_COEFF_SIZE] = अणु
	EOTF_COEFF_NORM(1.0),	EOTF_COEFF_NORM(0.0),	EOTF_COEFF_NORM(0.0),
	EOTF_COEFF_NORM(0.0),	EOTF_COEFF_NORM(1.0),	EOTF_COEFF_NORM(0.0),
	EOTF_COEFF_NORM(0.0),	EOTF_COEFF_NORM(0.0),	EOTF_COEFF_NORM(1.0),
	EOTF_COEFF_RIGHTSHIFT /* right shअगरt */
पूर्ण;

अटल व्योम meson_viu_set_g12a_osd1_matrix(काष्ठा meson_drm *priv,
					   पूर्णांक *m, bool csc_on)
अणु
	/* VPP WRAP OSD1 matrix */
	ग_लिखोl(((m[0] & 0xfff) << 16) | (m[1] & 0xfff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_PRE_OFFSET0_1));
	ग_लिखोl(m[2] & 0xfff,
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_PRE_OFFSET2));
	ग_लिखोl(((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_COEF00_01));
	ग_लिखोl(((m[5] & 0x1fff) << 16) | (m[6] & 0x1fff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_COEF02_10));
	ग_लिखोl(((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_COEF11_12));
	ग_लिखोl(((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_COEF20_21));
	ग_लिखोl((m[11] & 0x1fff) << 16,
		priv->io_base +	_REG(VPP_WRAP_OSD1_MATRIX_COEF22));

	ग_लिखोl(((m[18] & 0xfff) << 16) | (m[19] & 0xfff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_OFFSET0_1));
	ग_लिखोl(m[20] & 0xfff,
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_OFFSET2));

	ग_लिखोl_bits_relaxed(BIT(0), csc_on ? BIT(0) : 0,
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_EN_CTRL));
पूर्ण

अटल व्योम meson_viu_set_osd_matrix(काष्ठा meson_drm *priv,
				     क्रमागत viu_matrix_sel_e m_select,
			      पूर्णांक *m, bool csc_on)
अणु
	अगर (m_select == VIU_MATRIX_OSD) अणु
		/* osd matrix, VIU_MATRIX_0 */
		ग_लिखोl(((m[0] & 0xfff) << 16) | (m[1] & 0xfff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_PRE_OFFSET0_1));
		ग_लिखोl(m[2] & 0xfff,
			priv->io_base + _REG(VIU_OSD1_MATRIX_PRE_OFFSET2));
		ग_लिखोl(((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_COEF00_01));
		ग_लिखोl(((m[5] & 0x1fff) << 16) | (m[6] & 0x1fff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_COEF02_10));
		ग_लिखोl(((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_COEF11_12));
		ग_लिखोl(((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_COEF20_21));

		अगर (m[21]) अणु
			ग_लिखोl(((m[11] & 0x1fff) << 16) | (m[12] & 0x1fff),
				priv->io_base +
					_REG(VIU_OSD1_MATRIX_COEF22_30));
			ग_लिखोl(((m[13] & 0x1fff) << 16) | (m[14] & 0x1fff),
				priv->io_base +
					_REG(VIU_OSD1_MATRIX_COEF31_32));
			ग_लिखोl(((m[15] & 0x1fff) << 16) | (m[16] & 0x1fff),
				priv->io_base +
					_REG(VIU_OSD1_MATRIX_COEF40_41));
			ग_लिखोl(m[17] & 0x1fff, priv->io_base +
				_REG(VIU_OSD1_MATRIX_COLMOD_COEF42));
		पूर्ण अन्यथा
			ग_लिखोl((m[11] & 0x1fff) << 16, priv->io_base +
				_REG(VIU_OSD1_MATRIX_COEF22_30));

		ग_लिखोl(((m[18] & 0xfff) << 16) | (m[19] & 0xfff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_OFFSET0_1));
		ग_लिखोl(m[20] & 0xfff,
			priv->io_base + _REG(VIU_OSD1_MATRIX_OFFSET2));

		ग_लिखोl_bits_relaxed(3 << 30, m[21] << 30,
			priv->io_base + _REG(VIU_OSD1_MATRIX_COLMOD_COEF42));
		ग_लिखोl_bits_relaxed(7 << 16, m[22] << 16,
			priv->io_base + _REG(VIU_OSD1_MATRIX_COLMOD_COEF42));

		/* 23 reserved क्रम clipping control */
		ग_लिखोl_bits_relaxed(BIT(0), csc_on ? BIT(0) : 0,
			priv->io_base + _REG(VIU_OSD1_MATRIX_CTRL));
		ग_लिखोl_bits_relaxed(BIT(1), 0,
			priv->io_base + _REG(VIU_OSD1_MATRIX_CTRL));
	पूर्ण अन्यथा अगर (m_select == VIU_MATRIX_OSD_EOTF) अणु
		पूर्णांक i;

		/* osd eotf matrix, VIU_MATRIX_OSD_EOTF */
		क्रम (i = 0; i < 5; i++)
			ग_लिखोl(((m[i * 2] & 0x1fff) << 16) |
				(m[i * 2 + 1] & 0x1fff), priv->io_base +
				_REG(VIU_OSD1_EOTF_CTL + i + 1));

		ग_लिखोl_bits_relaxed(BIT(30), csc_on ? BIT(30) : 0,
			priv->io_base + _REG(VIU_OSD1_EOTF_CTL));
		ग_लिखोl_bits_relaxed(BIT(31), csc_on ? BIT(31) : 0,
			priv->io_base + _REG(VIU_OSD1_EOTF_CTL));
	पूर्ण
पूर्ण

#घोषणा OSD_EOTF_LUT_SIZE 33
#घोषणा OSD_OETF_LUT_SIZE 41

अटल व्योम
meson_viu_set_osd_lut(काष्ठा meson_drm *priv, क्रमागत viu_lut_sel_e lut_sel,
		      अचिन्हित पूर्णांक *r_map, अचिन्हित पूर्णांक *g_map,
		      अचिन्हित पूर्णांक *b_map, bool csc_on)
अणु
	अचिन्हित पूर्णांक addr_port;
	अचिन्हित पूर्णांक data_port;
	अचिन्हित पूर्णांक ctrl_port;
	पूर्णांक i;

	अगर (lut_sel == VIU_LUT_OSD_EOTF) अणु
		addr_port = VIU_OSD1_EOTF_LUT_ADDR_PORT;
		data_port = VIU_OSD1_EOTF_LUT_DATA_PORT;
		ctrl_port = VIU_OSD1_EOTF_CTL;
	पूर्ण अन्यथा अगर (lut_sel == VIU_LUT_OSD_OETF) अणु
		addr_port = VIU_OSD1_OETF_LUT_ADDR_PORT;
		data_port = VIU_OSD1_OETF_LUT_DATA_PORT;
		ctrl_port = VIU_OSD1_OETF_CTL;
	पूर्ण अन्यथा
		वापस;

	अगर (lut_sel == VIU_LUT_OSD_OETF) अणु
		ग_लिखोl(0, priv->io_base + _REG(addr_port));

		क्रम (i = 0; i < (OSD_OETF_LUT_SIZE / 2); i++)
			ग_लिखोl(r_map[i * 2] | (r_map[i * 2 + 1] << 16),
				priv->io_base + _REG(data_port));

		ग_लिखोl(r_map[OSD_OETF_LUT_SIZE - 1] | (g_map[0] << 16),
			priv->io_base + _REG(data_port));

		क्रम (i = 0; i < (OSD_OETF_LUT_SIZE / 2); i++)
			ग_लिखोl(g_map[i * 2 + 1] | (g_map[i * 2 + 2] << 16),
				priv->io_base + _REG(data_port));

		क्रम (i = 0; i < (OSD_OETF_LUT_SIZE / 2); i++)
			ग_लिखोl(b_map[i * 2] | (b_map[i * 2 + 1] << 16),
				priv->io_base + _REG(data_port));

		ग_लिखोl(b_map[OSD_OETF_LUT_SIZE - 1],
			priv->io_base + _REG(data_port));

		अगर (csc_on)
			ग_लिखोl_bits_relaxed(0x7 << 29, 7 << 29,
					    priv->io_base + _REG(ctrl_port));
		अन्यथा
			ग_लिखोl_bits_relaxed(0x7 << 29, 0,
					    priv->io_base + _REG(ctrl_port));
	पूर्ण अन्यथा अगर (lut_sel == VIU_LUT_OSD_EOTF) अणु
		ग_लिखोl(0, priv->io_base + _REG(addr_port));

		क्रम (i = 0; i < (OSD_EOTF_LUT_SIZE / 2); i++)
			ग_लिखोl(r_map[i * 2] | (r_map[i * 2 + 1] << 16),
				priv->io_base + _REG(data_port));

		ग_लिखोl(r_map[OSD_EOTF_LUT_SIZE - 1] | (g_map[0] << 16),
			priv->io_base + _REG(data_port));

		क्रम (i = 0; i < (OSD_EOTF_LUT_SIZE / 2); i++)
			ग_लिखोl(g_map[i * 2 + 1] | (g_map[i * 2 + 2] << 16),
				priv->io_base + _REG(data_port));

		क्रम (i = 0; i < (OSD_EOTF_LUT_SIZE / 2); i++)
			ग_लिखोl(b_map[i * 2] | (b_map[i * 2 + 1] << 16),
				priv->io_base + _REG(data_port));

		ग_लिखोl(b_map[OSD_EOTF_LUT_SIZE - 1],
			priv->io_base + _REG(data_port));

		अगर (csc_on)
			ग_लिखोl_bits_relaxed(7 << 27, 7 << 27,
					    priv->io_base + _REG(ctrl_port));
		अन्यथा
			ग_लिखोl_bits_relaxed(7 << 27, 0,
					    priv->io_base + _REG(ctrl_port));

		ग_लिखोl_bits_relaxed(BIT(31), BIT(31),
				    priv->io_base + _REG(ctrl_port));
	पूर्ण
पूर्ण

/* eotf lut: linear */
अटल अचिन्हित पूर्णांक eotf_33_linear_mapping[OSD_EOTF_LUT_SIZE] = अणु
	0x0000,	0x0200,	0x0400, 0x0600,
	0x0800, 0x0a00, 0x0c00, 0x0e00,
	0x1000, 0x1200, 0x1400, 0x1600,
	0x1800, 0x1a00, 0x1c00, 0x1e00,
	0x2000, 0x2200, 0x2400, 0x2600,
	0x2800, 0x2a00, 0x2c00, 0x2e00,
	0x3000, 0x3200, 0x3400, 0x3600,
	0x3800, 0x3a00, 0x3c00, 0x3e00,
	0x4000
पूर्ण;

/* osd oetf lut: linear */
अटल अचिन्हित पूर्णांक oetf_41_linear_mapping[OSD_OETF_LUT_SIZE] = अणु
	0, 0, 0, 0,
	0, 32, 64, 96,
	128, 160, 196, 224,
	256, 288, 320, 352,
	384, 416, 448, 480,
	512, 544, 576, 608,
	640, 672, 704, 736,
	768, 800, 832, 864,
	896, 928, 960, 992,
	1023, 1023, 1023, 1023,
	1023
पूर्ण;

अटल व्योम meson_viu_load_matrix(काष्ठा meson_drm *priv)
अणु
	/* eotf lut bypass */
	meson_viu_set_osd_lut(priv, VIU_LUT_OSD_EOTF,
			      eotf_33_linear_mapping, /* R */
			      eotf_33_linear_mapping, /* G */
			      eotf_33_linear_mapping, /* B */
			      false);

	/* eotf matrix bypass */
	meson_viu_set_osd_matrix(priv, VIU_MATRIX_OSD_EOTF,
				 eotf_bypass_coeff,
				 false);

	/* oetf lut bypass */
	meson_viu_set_osd_lut(priv, VIU_LUT_OSD_OETF,
			      oetf_41_linear_mapping, /* R */
			      oetf_41_linear_mapping, /* G */
			      oetf_41_linear_mapping, /* B */
			      false);

	/* osd matrix RGB709 to YUV709 limit */
	meson_viu_set_osd_matrix(priv, VIU_MATRIX_OSD,
				 RGB709_to_YUV709l_coeff,
				 true);
पूर्ण

/* VIU OSD1 Reset as workaround क्रम GXL+ Alpha OSD Bug */
व्योम meson_viu_osd1_reset(काष्ठा meson_drm *priv)
अणु
	uपूर्णांक32_t osd1_fअगरo_ctrl_stat, osd1_ctrl_stat2;

	/* Save these 2 रेजिस्टरs state */
	osd1_fअगरo_ctrl_stat = पढ़ोl_relaxed(
				priv->io_base + _REG(VIU_OSD1_FIFO_CTRL_STAT));
	osd1_ctrl_stat2 = पढ़ोl_relaxed(
				priv->io_base + _REG(VIU_OSD1_CTRL_STAT2));

	/* Reset OSD1 */
	ग_लिखोl_bits_relaxed(VIU_SW_RESET_OSD1, VIU_SW_RESET_OSD1,
			    priv->io_base + _REG(VIU_SW_RESET));
	ग_लिखोl_bits_relaxed(VIU_SW_RESET_OSD1, 0,
			    priv->io_base + _REG(VIU_SW_RESET));

	/* Reग_लिखो these रेजिस्टरs state lost in the reset */
	ग_लिखोl_relaxed(osd1_fअगरo_ctrl_stat,
		       priv->io_base + _REG(VIU_OSD1_FIFO_CTRL_STAT));
	ग_लिखोl_relaxed(osd1_ctrl_stat2,
		       priv->io_base + _REG(VIU_OSD1_CTRL_STAT2));

	/* Reload the conversion matrix */
	meson_viu_load_matrix(priv);
पूर्ण

#घोषणा OSD1_MALI_ORDER_ABGR				\
	(FIELD_PREP(VIU_OSD1_MALI_AFBCD_A_REORDER,	\
		    VIU_OSD1_MALI_REORDER_A) |		\
	 FIELD_PREP(VIU_OSD1_MALI_AFBCD_B_REORDER,	\
		    VIU_OSD1_MALI_REORDER_B) |		\
	 FIELD_PREP(VIU_OSD1_MALI_AFBCD_G_REORDER,	\
		    VIU_OSD1_MALI_REORDER_G) |		\
	 FIELD_PREP(VIU_OSD1_MALI_AFBCD_R_REORDER,	\
		    VIU_OSD1_MALI_REORDER_R))

#घोषणा OSD1_MALI_ORDER_ARGB				\
	(FIELD_PREP(VIU_OSD1_MALI_AFBCD_A_REORDER,	\
		    VIU_OSD1_MALI_REORDER_A) |		\
	 FIELD_PREP(VIU_OSD1_MALI_AFBCD_B_REORDER,	\
		    VIU_OSD1_MALI_REORDER_R) |		\
	 FIELD_PREP(VIU_OSD1_MALI_AFBCD_G_REORDER,	\
		    VIU_OSD1_MALI_REORDER_G) |		\
	 FIELD_PREP(VIU_OSD1_MALI_AFBCD_R_REORDER,	\
		    VIU_OSD1_MALI_REORDER_B))

व्योम meson_viu_g12a_enable_osd1_afbc(काष्ठा meson_drm *priv)
अणु
	u32 afbc_order = OSD1_MALI_ORDER_ARGB;

	/* Enable Mali AFBC Unpack */
	ग_लिखोl_bits_relaxed(VIU_OSD1_MALI_UNPACK_EN,
			    VIU_OSD1_MALI_UNPACK_EN,
			    priv->io_base + _REG(VIU_OSD1_MALI_UNPACK_CTRL));

	चयन (priv->afbcd.क्रमmat) अणु
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		afbc_order = OSD1_MALI_ORDER_ABGR;
		अवरोध;
	पूर्ण

	/* Setup RGBA Reordering */
	ग_लिखोl_bits_relaxed(VIU_OSD1_MALI_AFBCD_A_REORDER |
			    VIU_OSD1_MALI_AFBCD_B_REORDER |
			    VIU_OSD1_MALI_AFBCD_G_REORDER |
			    VIU_OSD1_MALI_AFBCD_R_REORDER,
			    afbc_order,
			    priv->io_base + _REG(VIU_OSD1_MALI_UNPACK_CTRL));

	/* Select AFBCD path क्रम OSD1 */
	ग_लिखोl_bits_relaxed(OSD_PATH_OSD_AXI_SEL_OSD1_AFBCD,
			    OSD_PATH_OSD_AXI_SEL_OSD1_AFBCD,
			    priv->io_base + _REG(OSD_PATH_MISC_CTRL));
पूर्ण

व्योम meson_viu_g12a_disable_osd1_afbc(काष्ठा meson_drm *priv)
अणु
	/* Disable AFBCD path क्रम OSD1 */
	ग_लिखोl_bits_relaxed(OSD_PATH_OSD_AXI_SEL_OSD1_AFBCD, 0,
			    priv->io_base + _REG(OSD_PATH_MISC_CTRL));

	/* Disable AFBCD unpack */
	ग_लिखोl_bits_relaxed(VIU_OSD1_MALI_UNPACK_EN, 0,
			    priv->io_base + _REG(VIU_OSD1_MALI_UNPACK_CTRL));
पूर्ण

व्योम meson_viu_gxm_enable_osd1_afbc(काष्ठा meson_drm *priv)
अणु
	ग_लिखोl_bits_relaxed(MALI_AFBC_MISC, FIELD_PREP(MALI_AFBC_MISC, 0x90),
			    priv->io_base + _REG(VIU_MISC_CTRL1));
पूर्ण

व्योम meson_viu_gxm_disable_osd1_afbc(काष्ठा meson_drm *priv)
अणु
	ग_लिखोl_bits_relaxed(MALI_AFBC_MISC, FIELD_PREP(MALI_AFBC_MISC, 0x00),
			    priv->io_base + _REG(VIU_MISC_CTRL1));
पूर्ण

व्योम meson_viu_init(काष्ठा meson_drm *priv)
अणु
	uपूर्णांक32_t reg;

	/* Disable OSDs */
	ग_लिखोl_bits_relaxed(VIU_OSD1_OSD_BLK_ENABLE | VIU_OSD1_OSD_ENABLE, 0,
			    priv->io_base + _REG(VIU_OSD1_CTRL_STAT));
	ग_लिखोl_bits_relaxed(VIU_OSD1_OSD_BLK_ENABLE | VIU_OSD1_OSD_ENABLE, 0,
			    priv->io_base + _REG(VIU_OSD2_CTRL_STAT));

	/* On GXL/GXM, Use the 10bit HDR conversion matrix */
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
	    meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
		meson_viu_load_matrix(priv);
	अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		meson_viu_set_g12a_osd1_matrix(priv, RGB709_to_YUV709l_coeff,
					       true);

	/* Initialize OSD1 fअगरo control रेजिस्टर */
	reg = VIU_OSD_DDR_PRIORITY_URGENT |
		VIU_OSD_HOLD_FIFO_LINES(31) |
		VIU_OSD_FIFO_DEPTH_VAL(32) | /* fअगरo_depth_val: 32*8=256 */
		VIU_OSD_WORDS_PER_BURST(4) | /* 4 words in 1 burst */
		VIU_OSD_FIFO_LIMITS(2);      /* fअगरo_lim: 2*16=32 */

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		reg |= VIU_OSD_BURST_LENGTH_32;
	अन्यथा
		reg |= VIU_OSD_BURST_LENGTH_64;

	ग_लिखोl_relaxed(reg, priv->io_base + _REG(VIU_OSD1_FIFO_CTRL_STAT));
	ग_लिखोl_relaxed(reg, priv->io_base + _REG(VIU_OSD2_FIFO_CTRL_STAT));

	/* Set OSD alpha replace value */
	ग_लिखोl_bits_relaxed(0xff << OSD_REPLACE_SHIFT,
			    0xff << OSD_REPLACE_SHIFT,
			    priv->io_base + _REG(VIU_OSD1_CTRL_STAT2));
	ग_लिखोl_bits_relaxed(0xff << OSD_REPLACE_SHIFT,
			    0xff << OSD_REPLACE_SHIFT,
			    priv->io_base + _REG(VIU_OSD2_CTRL_STAT2));

	/* Disable VD1 AFBC */
	/* di_mअगर0_en=0 mअगर0_to_vpp_en=0 di_mad_en=0 and afbc vd1 set=0*/
	ग_लिखोl_bits_relaxed(VIU_CTRL0_VD1_AFBC_MASK, 0,
			    priv->io_base + _REG(VIU_MISC_CTRL0));
	ग_लिखोl_relaxed(0, priv->io_base + _REG(AFBC_ENABLE));

	ग_लिखोl_relaxed(0x00FF00C0,
			priv->io_base + _REG(VD1_IF0_LUMA_FIFO_SIZE));
	ग_लिखोl_relaxed(0x00FF00C0,
			priv->io_base + _REG(VD2_IF0_LUMA_FIFO_SIZE));

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		ग_लिखोl_relaxed(VIU_OSD_BLEND_REORDER(0, 1) |
			       VIU_OSD_BLEND_REORDER(1, 0) |
			       VIU_OSD_BLEND_REORDER(2, 0) |
			       VIU_OSD_BLEND_REORDER(3, 0) |
			       VIU_OSD_BLEND_DIN_EN(1) |
			       VIU_OSD_BLEND1_DIN3_BYPASS_TO_DOUT1 |
			       VIU_OSD_BLEND1_DOUT_BYPASS_TO_BLEND2 |
			       VIU_OSD_BLEND_DIN0_BYPASS_TO_DOUT0 |
			       VIU_OSD_BLEND_BLEN2_PREMULT_EN(1) |
			       VIU_OSD_BLEND_HOLD_LINES(4),
			       priv->io_base + _REG(VIU_OSD_BLEND_CTRL));

		ग_लिखोl_relaxed(OSD_BLEND_PATH_SEL_ENABLE,
			       priv->io_base + _REG(OSD1_BLEND_SRC_CTRL));
		ग_लिखोl_relaxed(OSD_BLEND_PATH_SEL_ENABLE,
			       priv->io_base + _REG(OSD2_BLEND_SRC_CTRL));
		ग_लिखोl_relaxed(0, priv->io_base + _REG(VD1_BLEND_SRC_CTRL));
		ग_लिखोl_relaxed(0, priv->io_base + _REG(VD2_BLEND_SRC_CTRL));
		ग_लिखोl_relaxed(0,
				priv->io_base + _REG(VIU_OSD_BLEND_DUMMY_DATA0));
		ग_लिखोl_relaxed(0,
				priv->io_base + _REG(VIU_OSD_BLEND_DUMMY_ALPHA));

		ग_लिखोl_bits_relaxed(DOLBY_BYPASS_EN(0xc), DOLBY_BYPASS_EN(0xc),
				    priv->io_base + _REG(DOLBY_PATH_CTRL));

		meson_viu_g12a_disable_osd1_afbc(priv);
	पूर्ण

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM))
		meson_viu_gxm_disable_osd1_afbc(priv);

	priv->viu.osd1_enabled = false;
	priv->viu.osd1_commit = false;
	priv->viu.osd1_पूर्णांकerlace = false;
पूर्ण
