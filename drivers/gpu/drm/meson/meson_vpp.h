<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

/* Video Post Process */

#अगर_अघोषित __MESON_VPP_H
#घोषणा __MESON_VPP_H

काष्ठा drm_rect;
काष्ठा meson_drm;

/* Mux VIU/VPP to ENCI */
#घोषणा MESON_VIU_VPP_MUX_ENCI	0x5
/* Mux VIU/VPP to ENCP */
#घोषणा MESON_VIU_VPP_MUX_ENCP	0xA

व्योम meson_vpp_setup_mux(काष्ठा meson_drm *priv, अचिन्हित पूर्णांक mux);

व्योम meson_vpp_setup_पूर्णांकerlace_vscaler_osd1(काष्ठा meson_drm *priv,
					    काष्ठा drm_rect *input);
व्योम meson_vpp_disable_पूर्णांकerlace_vscaler_osd1(काष्ठा meson_drm *priv);

व्योम meson_vpp_init(काष्ठा meson_drm *priv);

#पूर्ण_अगर /* __MESON_VPP_H */
