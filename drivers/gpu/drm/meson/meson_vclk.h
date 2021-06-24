<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

/* Video Clock */

#अगर_अघोषित __MESON_VCLK_H
#घोषणा __MESON_VCLK_H

#समावेश <drm/drm_modes.h>

काष्ठा meson_drm;

क्रमागत अणु
	MESON_VCLK_TARGET_CVBS = 0,
	MESON_VCLK_TARGET_HDMI = 1,
	MESON_VCLK_TARGET_DMT = 2,
पूर्ण;

/* 27MHz is the CVBS Pixel Clock */
#घोषणा MESON_VCLK_CVBS			27000

क्रमागत drm_mode_status
meson_vclk_dmt_supported_freq(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक freq);
क्रमागत drm_mode_status
meson_vclk_vic_supported_freq(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक phy_freq,
			      अचिन्हित पूर्णांक vclk_freq);

व्योम meson_vclk_setup(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक target,
		      अचिन्हित पूर्णांक phy_freq, अचिन्हित पूर्णांक vclk_freq,
		      अचिन्हित पूर्णांक venc_freq, अचिन्हित पूर्णांक dac_freq,
		      bool hdmi_use_enci);

#पूर्ण_अगर /* __MESON_VCLK_H */
