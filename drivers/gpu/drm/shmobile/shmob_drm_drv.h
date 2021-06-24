<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * shmob_drm.h  --  SH Mobile DRM driver
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 *
 * Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __SHMOB_DRM_DRV_H__
#घोषणा __SHMOB_DRM_DRV_H__

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_data/shmob_drm.h>
#समावेश <linux/spinlock.h>

#समावेश "shmob_drm_crtc.h"

काष्ठा clk;
काष्ठा device;
काष्ठा drm_device;

काष्ठा shmob_drm_device अणु
	काष्ठा device *dev;
	स्थिर काष्ठा shmob_drm_platक्रमm_data *pdata;

	व्योम __iomem *mmio;
	काष्ठा clk *घड़ी;
	u32 lddckr;
	u32 ldmt1r;

	spinlock_t irq_lock;		/* Protects hardware LDINTR रेजिस्टर */

	काष्ठा drm_device *ddev;

	काष्ठा shmob_drm_crtc crtc;
	काष्ठा shmob_drm_encoder encoder;
	काष्ठा shmob_drm_connector connector;
पूर्ण;

#पूर्ण_अगर /* __SHMOB_DRM_DRV_H__ */
