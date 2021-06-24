<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Hisilicon Hibmc SoC drm driver
 *
 * Based on the bochs drm driver.
 *
 * Copyright (c) 2016 Huawei Limited.
 *
 * Author:
 *	Rongrong Zou <zourongrong@huawei.com>
 *	Rongrong Zou <zourongrong@gmail.com>
 *	Jianhua Li <lijianhua@huawei.com>
 */

#अगर_अघोषित HIBMC_DRM_DRV_H
#घोषणा HIBMC_DRM_DRV_H

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/i2c.h>

#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_framebuffer.h>

काष्ठा hibmc_connector अणु
	काष्ठा drm_connector base;

	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_bit_data bit_data;
पूर्ण;

काष्ठा hibmc_drm_निजी अणु
	/* hw */
	व्योम __iomem   *mmio;
	व्योम __iomem   *fb_map;
	resource_माप_प्रकार  fb_base;
	resource_माप_प्रकार  fb_size;

	/* drm */
	काष्ठा drm_device dev;
	काष्ठा drm_plane primary_plane;
	काष्ठा drm_crtc crtc;
	काष्ठा drm_encoder encoder;
	काष्ठा hibmc_connector connector;
पूर्ण;

अटल अंतरभूत काष्ठा hibmc_connector *to_hibmc_connector(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा hibmc_connector, base);
पूर्ण

अटल अंतरभूत काष्ठा hibmc_drm_निजी *to_hibmc_drm_निजी(काष्ठा drm_device *dev)
अणु
	वापस container_of(dev, काष्ठा hibmc_drm_निजी, dev);
पूर्ण

व्योम hibmc_set_घातer_mode(काष्ठा hibmc_drm_निजी *priv,
			  u32 घातer_mode);
व्योम hibmc_set_current_gate(काष्ठा hibmc_drm_निजी *priv,
			    u32 gate);

पूर्णांक hibmc_de_init(काष्ठा hibmc_drm_निजी *priv);
पूर्णांक hibmc_vdac_init(काष्ठा hibmc_drm_निजी *priv);

पूर्णांक hibmc_mm_init(काष्ठा hibmc_drm_निजी *hibmc);
पूर्णांक hibmc_ddc_create(काष्ठा drm_device *drm_dev, काष्ठा hibmc_connector *connector);

#पूर्ण_अगर
