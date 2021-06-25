<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2014 Endless Mobile
 *
 * Written by:
 *     Jasper St. Pierre <jstpierre@mecheye.net>
 */

#अगर_अघोषित __MESON_VENC_CVBS_H
#घोषणा __MESON_VENC_CVBS_H

#समावेश "meson_drv.h"
#समावेश "meson_venc.h"

काष्ठा meson_cvbs_mode अणु
	काष्ठा meson_cvbs_enci_mode *enci;
	काष्ठा drm_display_mode mode;
पूर्ण;

#घोषणा MESON_CVBS_MODES_COUNT	2

/* Modes supported by the CVBS output */
बाह्य काष्ठा meson_cvbs_mode meson_cvbs_modes[MESON_CVBS_MODES_COUNT];

पूर्णांक meson_venc_cvbs_create(काष्ठा meson_drm *priv);

#पूर्ण_अगर /* __MESON_VENC_CVBS_H */
