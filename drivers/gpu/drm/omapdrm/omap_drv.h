<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob@ti.com>
 */

#अगर_अघोषित __OMAPDRM_DRV_H__
#घोषणा __OMAPDRM_DRV_H__

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश "dss/omapdss.h"
#समावेश "dss/dss.h"

#समावेश <drm/drm_gem.h>
#समावेश <drm/omap_drm.h>

#समावेश "omap_crtc.h"
#समावेश "omap_encoder.h"
#समावेश "omap_fb.h"
#समावेश "omap_fbdev.h"
#समावेश "omap_gem.h"
#समावेश "omap_irq.h"
#समावेश "omap_plane.h"

#घोषणा DBG(fmt, ...) DRM_DEBUG_DRIVER(fmt"\n", ##__VA_ARGS__)
#घोषणा VERB(fmt, ...) अगर (0) DRM_DEBUG_DRIVER(fmt, ##__VA_ARGS__) /* verbose debug */

#घोषणा MODULE_NAME     "omapdrm"

काष्ठा omap_drm_usergart;

काष्ठा omap_drm_pipeline अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;
	काष्ठा omap_dss_device *output;
	अचिन्हित पूर्णांक alias_id;
पूर्ण;

काष्ठा omap_drm_निजी अणु
	काष्ठा drm_device *ddev;
	काष्ठा device *dev;
	u32 omaprev;

	काष्ठा dss_device *dss;
	काष्ठा dispc_device *dispc;

	अचिन्हित पूर्णांक num_pipes;
	काष्ठा omap_drm_pipeline pipes[8];
	काष्ठा omap_drm_pipeline *channels[8];

	अचिन्हित पूर्णांक num_planes;
	काष्ठा drm_plane *planes[8];

	काष्ठा drm_fb_helper *fbdev;

	काष्ठा workqueue_काष्ठा *wq;

	/* lock क्रम obj_list below */
	काष्ठा mutex list_lock;

	/* list of GEM objects: */
	काष्ठा list_head obj_list;

	काष्ठा omap_drm_usergart *usergart;
	bool has_dmm;

	/* properties: */
	काष्ठा drm_property *zorder_prop;

	/* irq handling: */
	spinlock_t रुको_lock;		/* protects the रुको_list */
	काष्ठा list_head रुको_list;	/* list of omap_irq_रुको */
	u32 irq_mask;			/* enabled irqs in addition to रुको_list */

	/* memory bandwidth limit अगर it is needed on the platक्रमm */
	अचिन्हित पूर्णांक max_bandwidth;
पूर्ण;


व्योम omap_debugfs_init(काष्ठा drm_minor *minor);

#पूर्ण_अगर /* __OMAPDRM_DRV_H__ */
