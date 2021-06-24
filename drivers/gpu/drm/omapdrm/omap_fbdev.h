<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap_fbdev.h -- OMAP DRM FBDEV Compatibility
 *
 * Copyright (C) 2011 Texas Instruments
 * Author: Rob Clark <rob@ti.com>
 */

#अगर_अघोषित __OMAPDRM_FBDEV_H__
#घोषणा __OMAPDRM_FBDEV_H__

काष्ठा drm_device;
काष्ठा drm_fb_helper;

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
व्योम omap_fbdev_init(काष्ठा drm_device *dev);
व्योम omap_fbdev_fini(काष्ठा drm_device *dev);
#अन्यथा
अटल अंतरभूत व्योम omap_fbdev_init(काष्ठा drm_device *dev)
अणु
पूर्ण
अटल अंतरभूत व्योम omap_fbdev_fini(काष्ठा drm_device *dev)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __OMAPDRM_FBDEV_H__ */
