<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap_crtc.h -- OMAP DRM CRTC
 *
 * Copyright (C) 2011 Texas Instruments
 * Author: Rob Clark <rob@ti.com>
 */

#अगर_अघोषित __OMAPDRM_CRTC_H__
#घोषणा __OMAPDRM_CRTC_H__

#समावेश <linux/types.h>

क्रमागत omap_channel;

काष्ठा drm_crtc;
काष्ठा drm_device;
काष्ठा drm_plane;
काष्ठा omap_drm_pipeline;
काष्ठा omap_dss_device;
काष्ठा videomode;

काष्ठा videomode *omap_crtc_timings(काष्ठा drm_crtc *crtc);
क्रमागत omap_channel omap_crtc_channel(काष्ठा drm_crtc *crtc);
काष्ठा drm_crtc *omap_crtc_init(काष्ठा drm_device *dev,
				काष्ठा omap_drm_pipeline *pipe,
				काष्ठा drm_plane *plane);
पूर्णांक omap_crtc_रुको_pending(काष्ठा drm_crtc *crtc);
व्योम omap_crtc_error_irq(काष्ठा drm_crtc *crtc, u32 irqstatus);
व्योम omap_crtc_vblank_irq(काष्ठा drm_crtc *crtc);
व्योम omap_crtc_frameकरोne_irq(काष्ठा drm_crtc *crtc, uपूर्णांक32_t irqstatus);
व्योम omap_crtc_flush(काष्ठा drm_crtc *crtc);

#पूर्ण_अगर /* __OMAPDRM_CRTC_H__ */
