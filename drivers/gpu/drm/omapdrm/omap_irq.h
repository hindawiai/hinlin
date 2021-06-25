<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap_irq.h -- OMAP DRM IRQ Handling
 *
 * Copyright (C) 2011 Texas Instruments
 * Author: Rob Clark <rob@ti.com>
 */

#अगर_अघोषित __OMAPDRM_IRQ_H__
#घोषणा __OMAPDRM_IRQ_H__

#समावेश <linux/types.h>

काष्ठा drm_crtc;
काष्ठा drm_device;
काष्ठा omap_irq_रुको;

पूर्णांक omap_irq_enable_vblank(काष्ठा drm_crtc *crtc);
पूर्णांक omap_irq_enable_frameकरोne(काष्ठा drm_crtc *crtc, bool enable);
व्योम omap_irq_disable_vblank(काष्ठा drm_crtc *crtc);
व्योम omap_drm_irq_uninstall(काष्ठा drm_device *dev);
पूर्णांक omap_drm_irq_install(काष्ठा drm_device *dev);

काष्ठा omap_irq_रुको *omap_irq_रुको_init(काष्ठा drm_device *dev,
		u32 irqmask, पूर्णांक count);
पूर्णांक omap_irq_रुको(काष्ठा drm_device *dev, काष्ठा omap_irq_रुको *रुको,
		अचिन्हित दीर्घ समयout);

#पूर्ण_अगर /* __OMAPDRM_IRQ_H__ */
