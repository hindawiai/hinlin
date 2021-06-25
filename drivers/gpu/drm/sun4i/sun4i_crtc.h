<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _SUN4I_CRTC_H_
#घोषणा _SUN4I_CRTC_H_

काष्ठा sun4i_crtc अणु
	काष्ठा drm_crtc			crtc;
	काष्ठा drm_pending_vblank_event	*event;

	काष्ठा sunxi_engine		*engine;
	काष्ठा sun4i_tcon		*tcon;
पूर्ण;

अटल अंतरभूत काष्ठा sun4i_crtc *drm_crtc_to_sun4i_crtc(काष्ठा drm_crtc *crtc)
अणु
	वापस container_of(crtc, काष्ठा sun4i_crtc, crtc);
पूर्ण

काष्ठा sun4i_crtc *sun4i_crtc_init(काष्ठा drm_device *drm,
				   काष्ठा sunxi_engine *engine,
				   काष्ठा sun4i_tcon *tcon);

#पूर्ण_अगर /* _SUN4I_CRTC_H_ */
