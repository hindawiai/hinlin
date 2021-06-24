<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#अगर_अघोषित __TIDSS_DRV_H__
#घोषणा __TIDSS_DRV_H__

#समावेश <linux/spinlock.h>

#घोषणा TIDSS_MAX_PORTS 4
#घोषणा TIDSS_MAX_PLANES 4

प्रकार u32 dispc_irq_t;

काष्ठा tidss_device अणु
	काष्ठा drm_device ddev;		/* DRM device क्रम DSS */
	काष्ठा device *dev;		/* Underlying DSS device */

	स्थिर काष्ठा dispc_features *feat;
	काष्ठा dispc_device *dispc;

	अचिन्हित पूर्णांक num_crtcs;
	काष्ठा drm_crtc *crtcs[TIDSS_MAX_PORTS];

	अचिन्हित पूर्णांक num_planes;
	काष्ठा drm_plane *planes[TIDSS_MAX_PLANES];

	spinlock_t रुको_lock;	/* protects the irq masks */
	dispc_irq_t irq_mask;	/* enabled irqs in addition to रुको_list */
पूर्ण;

#घोषणा to_tidss(__dev) container_of(__dev, काष्ठा tidss_device, ddev)

पूर्णांक tidss_runसमय_get(काष्ठा tidss_device *tidss);
व्योम tidss_runसमय_put(काष्ठा tidss_device *tidss);

#पूर्ण_अगर
