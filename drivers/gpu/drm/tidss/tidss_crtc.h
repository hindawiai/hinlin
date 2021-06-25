<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#अगर_अघोषित __TIDSS_CRTC_H__
#घोषणा __TIDSS_CRTC_H__

#समावेश <linux/completion.h>
#समावेश <linux/रुको.h>

#समावेश <drm/drm_crtc.h>

#घोषणा to_tidss_crtc(c) container_of((c), काष्ठा tidss_crtc, crtc)

काष्ठा tidss_device;

काष्ठा tidss_crtc अणु
	काष्ठा drm_crtc crtc;

	u32 hw_videoport;

	काष्ठा drm_pending_vblank_event *event;

	काष्ठा completion frameकरोne_completion;
पूर्ण;

#घोषणा to_tidss_crtc_state(x) container_of(x, काष्ठा tidss_crtc_state, base)

काष्ठा tidss_crtc_state अणु
	/* Must be first. */
	काष्ठा drm_crtc_state base;

	bool plane_pos_changed;

	u32 bus_क्रमmat;
	u32 bus_flags;
पूर्ण;

व्योम tidss_crtc_vblank_irq(काष्ठा drm_crtc *crtc);
व्योम tidss_crtc_frameकरोne_irq(काष्ठा drm_crtc *crtc);
व्योम tidss_crtc_error_irq(काष्ठा drm_crtc *crtc, u64 irqstatus);

काष्ठा tidss_crtc *tidss_crtc_create(काष्ठा tidss_device *tidss,
				     u32 hw_videoport,
				     काष्ठा drm_plane *primary);
#पूर्ण_अगर
