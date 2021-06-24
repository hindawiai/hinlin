<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 * Copyright (C) 2014 Endless Mobile
 */

#समावेश <linux/export.h>

#समावेश "meson_drv.h"
#समावेश "meson_registers.h"
#समावेश "meson_vpp.h"

/**
 * DOC: Video Post Processing
 *
 * VPP Handles all the Post Processing after the Scanout from the VIU
 * We handle the following post processings :
 *
 * - Postblend, Blends the OSD1 only
 *	We exclude OSD2, VS1, VS1 and Preblend output
 * - Vertical OSD Scaler क्रम OSD1 only, we disable vertical scaler and
 *	use it only क्रम पूर्णांकerlace scanout
 * - Intermediate FIFO with शेष Amlogic values
 *
 * What is missing :
 *
 * - Preblend क्रम video overlay pre-scaling
 * - OSD2 support क्रम cursor framebuffer
 * - Video pre-scaling beक्रमe postblend
 * - Full Vertical/Horizontal OSD scaling to support TV overscan
 * - HDR conversion
 */

व्योम meson_vpp_setup_mux(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक mux)
अणु
	ग_लिखोl(mux, priv->io_base + _REG(VPU_VIU_VENC_MUX_CTRL));
पूर्ण

अटल अचिन्हित पूर्णांक vpp_filter_coefs_4poपूर्णांक_bspline[] = अणु
	0x15561500, 0x14561600, 0x13561700, 0x12561800,
	0x11551a00, 0x11541b00, 0x10541c00, 0x0f541d00,
	0x0f531e00, 0x0e531f00, 0x0d522100, 0x0c522200,
	0x0b522300, 0x0b512400, 0x0a502600, 0x0a4f2700,
	0x094e2900, 0x084e2a00, 0x084d2b00, 0x074c2c01,
	0x074b2d01, 0x064a2f01, 0x06493001, 0x05483201,
	0x05473301, 0x05463401, 0x04453601, 0x04433702,
	0x04423802, 0x03413a02, 0x03403b02, 0x033f3c02,
	0x033d3d03
पूर्ण;

अटल व्योम meson_vpp_ग_लिखो_scaling_filter_coefs(काष्ठा meson_drm *priv,
						 स्थिर अचिन्हित पूर्णांक *coefs,
						 bool is_horizontal)
अणु
	पूर्णांक i;

	ग_लिखोl_relaxed(is_horizontal ? VPP_SCALE_HORIZONTAL_COEF : 0,
			priv->io_base + _REG(VPP_OSD_SCALE_COEF_IDX));
	क्रम (i = 0; i < 33; i++)
		ग_लिखोl_relaxed(coefs[i],
				priv->io_base + _REG(VPP_OSD_SCALE_COEF));
पूर्ण

अटल स्थिर uपूर्णांक32_t vpp_filter_coefs_bicubic[] = अणु
	0x00800000, 0x007f0100, 0xff7f0200, 0xfe7f0300,
	0xfd7e0500, 0xfc7e0600, 0xfb7d0800, 0xfb7c0900,
	0xfa7b0b00, 0xfa7a0dff, 0xf9790fff, 0xf97711ff,
	0xf87613ff, 0xf87416fe, 0xf87218fe, 0xf8701afe,
	0xf76f1dfd, 0xf76d1ffd, 0xf76b21fd, 0xf76824fd,
	0xf76627fc, 0xf76429fc, 0xf7612cfc, 0xf75f2ffb,
	0xf75d31fb, 0xf75a34fb, 0xf75837fa, 0xf7553afa,
	0xf8523cfa, 0xf8503ff9, 0xf84d42f9, 0xf84a45f9,
	0xf84848f8
पूर्ण;

अटल व्योम meson_vpp_ग_लिखो_vd_scaling_filter_coefs(काष्ठा meson_drm *priv,
						    स्थिर अचिन्हित पूर्णांक *coefs,
						    bool is_horizontal)
अणु
	पूर्णांक i;

	ग_लिखोl_relaxed(is_horizontal ? VPP_SCALE_HORIZONTAL_COEF : 0,
			priv->io_base + _REG(VPP_SCALE_COEF_IDX));
	क्रम (i = 0; i < 33; i++)
		ग_लिखोl_relaxed(coefs[i],
				priv->io_base + _REG(VPP_SCALE_COEF));
पूर्ण

व्योम meson_vpp_init(काष्ठा meson_drm *priv)
अणु
	/* set dummy data शेष YUV black */
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
		ग_लिखोl_relaxed(0x108080, priv->io_base + _REG(VPP_DUMMY_DATA1));
	अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM)) अणु
		ग_लिखोl_bits_relaxed(0xff << 16, 0xff << 16,
				    priv->io_base + _REG(VIU_MISC_CTRL1));
		ग_लिखोl_relaxed(VPP_PPS_DUMMY_DATA_MODE,
			       priv->io_base + _REG(VPP_DOLBY_CTRL));
		ग_लिखोl_relaxed(0x1020080,
				priv->io_base + _REG(VPP_DUMMY_DATA1));
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		ग_लिखोl_relaxed(0xf, priv->io_base + _REG(DOLBY_PATH_CTRL));

	/* Initialize vpu fअगरo control रेजिस्टरs */
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		ग_लिखोl_relaxed(VPP_OFIFO_SIZE_DEFAULT,
			       priv->io_base + _REG(VPP_OFIFO_SIZE));
	अन्यथा
		ग_लिखोl_bits_relaxed(VPP_OFIFO_SIZE_MASK, 0x77f,
				    priv->io_base + _REG(VPP_OFIFO_SIZE));
	ग_लिखोl_relaxed(VPP_POSTBLEND_HOLD_LINES(4) | VPP_PREBLEND_HOLD_LINES(4),
		       priv->io_base + _REG(VPP_HOLD_LINES));

	अगर (!meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		/* Turn off preblend */
		ग_लिखोl_bits_relaxed(VPP_PREBLEND_ENABLE, 0,
				    priv->io_base + _REG(VPP_MISC));

		/* Turn off POSTBLEND */
		ग_लिखोl_bits_relaxed(VPP_POSTBLEND_ENABLE, 0,
				    priv->io_base + _REG(VPP_MISC));

		/* Force all planes off */
		ग_लिखोl_bits_relaxed(VPP_OSD1_POSTBLEND | VPP_OSD2_POSTBLEND |
				    VPP_VD1_POSTBLEND | VPP_VD2_POSTBLEND |
				    VPP_VD1_PREBLEND | VPP_VD2_PREBLEND, 0,
				    priv->io_base + _REG(VPP_MISC));

		/* Setup शेष VD settings */
		ग_लिखोl_relaxed(4096,
				priv->io_base + _REG(VPP_PREBLEND_VD1_H_START_END));
		ग_लिखोl_relaxed(4096,
				priv->io_base + _REG(VPP_BLEND_VD2_H_START_END));
	पूर्ण

	/* Disable Scalers */
	ग_लिखोl_relaxed(0, priv->io_base + _REG(VPP_OSD_SC_CTRL0));
	ग_लिखोl_relaxed(0, priv->io_base + _REG(VPP_OSD_VSC_CTRL0));
	ग_लिखोl_relaxed(0, priv->io_base + _REG(VPP_OSD_HSC_CTRL0));

	/* Set horizontal/vertical bank length and enable video scale out */
	ग_लिखोl_relaxed(VPP_VSC_BANK_LENGTH(4) | VPP_HSC_BANK_LENGTH(4) |
		       VPP_SC_VD_EN_ENABLE,
		       priv->io_base + _REG(VPP_SC_MISC));

	/* Enable minus black level क्रम vadj1 */
	ग_लिखोl_relaxed(VPP_MINUS_BLACK_LVL_VADJ1_ENABLE,
		       priv->io_base + _REG(VPP_VADJ_CTRL));

	/* Write in the proper filter coefficients. */
	meson_vpp_ग_लिखो_scaling_filter_coefs(priv,
				vpp_filter_coefs_4poपूर्णांक_bspline, false);
	meson_vpp_ग_लिखो_scaling_filter_coefs(priv,
				vpp_filter_coefs_4poपूर्णांक_bspline, true);

	/* Write the VD proper filter coefficients. */
	meson_vpp_ग_लिखो_vd_scaling_filter_coefs(priv, vpp_filter_coefs_bicubic,
						false);
	meson_vpp_ग_लिखो_vd_scaling_filter_coefs(priv, vpp_filter_coefs_bicubic,
						true);
पूर्ण
