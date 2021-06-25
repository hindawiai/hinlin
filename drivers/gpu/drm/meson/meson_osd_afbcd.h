<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2019 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#अगर_अघोषित __MESON_OSD_AFBCD_H
#घोषणा __MESON_OSD_AFBCD_H

#समावेश "meson_drv.h"

/* This is an पूर्णांकernal address used to transfer pixel from AFBC to the VIU */
#घोषणा MESON_G12A_AFBCD_OUT_ADDR	0x1000000

काष्ठा meson_afbcd_ops अणु
	पूर्णांक (*init)(काष्ठा meson_drm *priv);
	पूर्णांक (*reset)(काष्ठा meson_drm *priv);
	पूर्णांक (*enable)(काष्ठा meson_drm *priv);
	पूर्णांक (*disable)(काष्ठा meson_drm *priv);
	पूर्णांक (*setup)(काष्ठा meson_drm *priv);
	पूर्णांक (*fmt_to_blk_mode)(u64 modअगरier, uपूर्णांक32_t क्रमmat);
	bool (*supported_fmt)(u64 modअगरier, uपूर्णांक32_t क्रमmat);
पूर्ण;

बाह्य काष्ठा meson_afbcd_ops meson_afbcd_gxm_ops;
बाह्य काष्ठा meson_afbcd_ops meson_afbcd_g12a_ops;

#पूर्ण_अगर /* __MESON_OSD_AFBCD_H */
