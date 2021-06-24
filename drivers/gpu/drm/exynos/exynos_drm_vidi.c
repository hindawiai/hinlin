<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* exynos_drm_vidi.c
 *
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/समयr.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_crtc.h"
#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_fb.h"
#समावेश "exynos_drm_plane.h"
#समावेश "exynos_drm_vidi.h"

/* VIDI uses fixed refresh rate of 50Hz */
#घोषणा VIDI_REFRESH_TIME (1000 / 50)

/* vidi has totally three भव winकरोws. */
#घोषणा WINDOWS_NR		3

#घोषणा ctx_from_connector(c)	container_of(c, काष्ठा vidi_context, \
					connector)

काष्ठा vidi_context अणु
	काष्ठा drm_encoder		encoder;
	काष्ठा drm_device		*drm_dev;
	काष्ठा device			*dev;
	काष्ठा exynos_drm_crtc		*crtc;
	काष्ठा drm_connector		connector;
	काष्ठा exynos_drm_plane		planes[WINDOWS_NR];
	काष्ठा edid			*raw_edid;
	अचिन्हित पूर्णांक			clkभाग;
	अचिन्हित पूर्णांक			connected;
	bool				suspended;
	काष्ठा समयr_list		समयr;
	काष्ठा mutex			lock;
पूर्ण;

अटल अंतरभूत काष्ठा vidi_context *encoder_to_vidi(काष्ठा drm_encoder *e)
अणु
	वापस container_of(e, काष्ठा vidi_context, encoder);
पूर्ण

अटल स्थिर अक्षर fake_edid_info[] = अणु
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x4c, 0x2d, 0x05, 0x05,
	0x00, 0x00, 0x00, 0x00, 0x30, 0x12, 0x01, 0x03, 0x80, 0x10, 0x09, 0x78,
	0x0a, 0xee, 0x91, 0xa3, 0x54, 0x4c, 0x99, 0x26, 0x0f, 0x50, 0x54, 0xbd,
	0xee, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x66, 0x21, 0x50, 0xb0, 0x51, 0x00,
	0x1b, 0x30, 0x40, 0x70, 0x36, 0x00, 0xa0, 0x5a, 0x00, 0x00, 0x00, 0x1e,
	0x01, 0x1d, 0x00, 0x72, 0x51, 0xd0, 0x1e, 0x20, 0x6e, 0x28, 0x55, 0x00,
	0xa0, 0x5a, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x18,
	0x4b, 0x1a, 0x44, 0x17, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x00, 0x00, 0x00, 0xfc, 0x00, 0x53, 0x41, 0x4d, 0x53, 0x55, 0x4e, 0x47,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0xbc, 0x02, 0x03, 0x1e, 0xf1,
	0x46, 0x84, 0x05, 0x03, 0x10, 0x20, 0x22, 0x23, 0x09, 0x07, 0x07, 0x83,
	0x01, 0x00, 0x00, 0xe2, 0x00, 0x0f, 0x67, 0x03, 0x0c, 0x00, 0x10, 0x00,
	0xb8, 0x2d, 0x01, 0x1d, 0x80, 0x18, 0x71, 0x1c, 0x16, 0x20, 0x58, 0x2c,
	0x25, 0x00, 0xa0, 0x5a, 0x00, 0x00, 0x00, 0x9e, 0x8c, 0x0a, 0xd0, 0x8a,
	0x20, 0xe0, 0x2d, 0x10, 0x10, 0x3e, 0x96, 0x00, 0xa0, 0x5a, 0x00, 0x00,
	0x00, 0x18, 0x02, 0x3a, 0x80, 0x18, 0x71, 0x38, 0x2d, 0x40, 0x58, 0x2c,
	0x45, 0x00, 0xa0, 0x5a, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x06
पूर्ण;

अटल स्थिर uपूर्णांक32_t क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_NV12,
पूर्ण;

अटल स्थिर क्रमागत drm_plane_type vidi_win_types[WINDOWS_NR] = अणु
	DRM_PLANE_TYPE_PRIMARY,
	DRM_PLANE_TYPE_OVERLAY,
	DRM_PLANE_TYPE_CURSOR,
पूर्ण;

अटल पूर्णांक vidi_enable_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा vidi_context *ctx = crtc->ctx;

	अगर (ctx->suspended)
		वापस -EPERM;

	mod_समयr(&ctx->समयr,
		jअगरfies + msecs_to_jअगरfies(VIDI_REFRESH_TIME) - 1);

	वापस 0;
पूर्ण

अटल व्योम vidi_disable_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
पूर्ण

अटल व्योम vidi_update_plane(काष्ठा exynos_drm_crtc *crtc,
			      काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->base.state;
	काष्ठा vidi_context *ctx = crtc->ctx;
	dma_addr_t addr;

	अगर (ctx->suspended)
		वापस;

	addr = exynos_drm_fb_dma_addr(state->fb, 0);
	DRM_DEV_DEBUG_KMS(ctx->dev, "dma_addr = %pad\n", &addr);
पूर्ण

अटल व्योम vidi_atomic_enable(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा vidi_context *ctx = crtc->ctx;

	mutex_lock(&ctx->lock);

	ctx->suspended = false;

	mutex_unlock(&ctx->lock);

	drm_crtc_vblank_on(&crtc->base);
पूर्ण

अटल व्योम vidi_atomic_disable(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा vidi_context *ctx = crtc->ctx;

	drm_crtc_vblank_off(&crtc->base);

	mutex_lock(&ctx->lock);

	ctx->suspended = true;

	mutex_unlock(&ctx->lock);
पूर्ण

अटल स्थिर काष्ठा exynos_drm_crtc_ops vidi_crtc_ops = अणु
	.atomic_enable = vidi_atomic_enable,
	.atomic_disable = vidi_atomic_disable,
	.enable_vblank = vidi_enable_vblank,
	.disable_vblank = vidi_disable_vblank,
	.update_plane = vidi_update_plane,
	.atomic_flush = exynos_crtc_handle_event,
पूर्ण;

अटल व्योम vidi_fake_vblank_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा vidi_context *ctx = from_समयr(ctx, t, समयr);

	अगर (drm_crtc_handle_vblank(&ctx->crtc->base))
		mod_समयr(&ctx->समयr,
			jअगरfies + msecs_to_jअगरfies(VIDI_REFRESH_TIME) - 1);
पूर्ण

अटल sमाप_प्रकार vidi_show_connection(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vidi_context *ctx = dev_get_drvdata(dev);
	पूर्णांक rc;

	mutex_lock(&ctx->lock);

	rc = प्र_लिखो(buf, "%d\n", ctx->connected);

	mutex_unlock(&ctx->lock);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार vidi_store_connection(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा vidi_context *ctx = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &ctx->connected);
	अगर (ret)
		वापस ret;

	अगर (ctx->connected > 1)
		वापस -EINVAL;

	/* use fake edid data क्रम test. */
	अगर (!ctx->raw_edid)
		ctx->raw_edid = (काष्ठा edid *)fake_edid_info;

	/* अगर raw_edid isn't same as fake data then it can't be tested. */
	अगर (ctx->raw_edid != (काष्ठा edid *)fake_edid_info) अणु
		DRM_DEV_DEBUG_KMS(dev, "edid data is not fake data.\n");
		वापस -EINVAL;
	पूर्ण

	DRM_DEV_DEBUG_KMS(dev, "requested connection.\n");

	drm_helper_hpd_irq_event(ctx->drm_dev);

	वापस len;
पूर्ण

अटल DEVICE_ATTR(connection, 0644, vidi_show_connection,
			vidi_store_connection);

अटल काष्ठा attribute *vidi_attrs[] = अणु
	&dev_attr_connection.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(vidi);

पूर्णांक vidi_connection_ioctl(काष्ठा drm_device *drm_dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा vidi_context *ctx = dev_get_drvdata(drm_dev->dev);
	काष्ठा drm_exynos_vidi_connection *vidi = data;

	अगर (!vidi) अणु
		DRM_DEV_DEBUG_KMS(ctx->dev,
				  "user data for vidi is null.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vidi->connection > 1) अणु
		DRM_DEV_DEBUG_KMS(ctx->dev,
				  "connection should be 0 or 1.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->connected == vidi->connection) अणु
		DRM_DEV_DEBUG_KMS(ctx->dev,
				  "same connection request.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vidi->connection) अणु
		काष्ठा edid *raw_edid;

		raw_edid = (काष्ठा edid *)(अचिन्हित दीर्घ)vidi->edid;
		अगर (!drm_edid_is_valid(raw_edid)) अणु
			DRM_DEV_DEBUG_KMS(ctx->dev,
					  "edid data is invalid.\n");
			वापस -EINVAL;
		पूर्ण
		ctx->raw_edid = drm_edid_duplicate(raw_edid);
		अगर (!ctx->raw_edid) अणु
			DRM_DEV_DEBUG_KMS(ctx->dev,
					  "failed to allocate raw_edid.\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * with connection = 0, मुक्त raw_edid
		 * only अगर raw edid data isn't same as fake data.
		 */
		अगर (ctx->raw_edid && ctx->raw_edid !=
				(काष्ठा edid *)fake_edid_info) अणु
			kमुक्त(ctx->raw_edid);
			ctx->raw_edid = शून्य;
		पूर्ण
	पूर्ण

	ctx->connected = vidi->connection;
	drm_helper_hpd_irq_event(ctx->drm_dev);

	वापस 0;
पूर्ण

अटल क्रमागत drm_connector_status vidi_detect(काष्ठा drm_connector *connector,
			bool क्रमce)
अणु
	काष्ठा vidi_context *ctx = ctx_from_connector(connector);

	/*
	 * connection request would come from user side
	 * to करो hotplug through specअगरic ioctl.
	 */
	वापस ctx->connected ? connector_status_connected :
			connector_status_disconnected;
पूर्ण

अटल व्योम vidi_connector_destroy(काष्ठा drm_connector *connector)
अणु
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs vidi_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = vidi_detect,
	.destroy = vidi_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक vidi_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा vidi_context *ctx = ctx_from_connector(connector);
	काष्ठा edid *edid;
	पूर्णांक edid_len;

	/*
	 * the edid data comes from user side and it would be set
	 * to ctx->raw_edid through specअगरic ioctl.
	 */
	अगर (!ctx->raw_edid) अणु
		DRM_DEV_DEBUG_KMS(ctx->dev, "raw_edid is null.\n");
		वापस -EFAULT;
	पूर्ण

	edid_len = (1 + ctx->raw_edid->extensions) * EDID_LENGTH;
	edid = kmemdup(ctx->raw_edid, edid_len, GFP_KERNEL);
	अगर (!edid) अणु
		DRM_DEV_DEBUG_KMS(ctx->dev, "failed to allocate edid\n");
		वापस -ENOMEM;
	पूर्ण

	drm_connector_update_edid_property(connector, edid);

	वापस drm_add_edid_modes(connector, edid);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs vidi_connector_helper_funcs = अणु
	.get_modes = vidi_get_modes,
पूर्ण;

अटल पूर्णांक vidi_create_connector(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vidi_context *ctx = encoder_to_vidi(encoder);
	काष्ठा drm_connector *connector = &ctx->connector;
	पूर्णांक ret;

	connector->polled = DRM_CONNECTOR_POLL_HPD;

	ret = drm_connector_init(ctx->drm_dev, connector,
			&vidi_connector_funcs, DRM_MODE_CONNECTOR_VIRTUAL);
	अगर (ret) अणु
		DRM_DEV_ERROR(ctx->dev,
			      "Failed to initialize connector with drm\n");
		वापस ret;
	पूर्ण

	drm_connector_helper_add(connector, &vidi_connector_helper_funcs);
	drm_connector_attach_encoder(connector, encoder);

	वापस 0;
पूर्ण

अटल व्योम exynos_vidi_mode_set(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode)
अणु
पूर्ण

अटल व्योम exynos_vidi_enable(काष्ठा drm_encoder *encoder)
अणु
पूर्ण

अटल व्योम exynos_vidi_disable(काष्ठा drm_encoder *encoder)
अणु
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs exynos_vidi_encoder_helper_funcs = अणु
	.mode_set = exynos_vidi_mode_set,
	.enable = exynos_vidi_enable,
	.disable = exynos_vidi_disable,
पूर्ण;

अटल पूर्णांक vidi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा vidi_context *ctx = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा drm_encoder *encoder = &ctx->encoder;
	काष्ठा exynos_drm_plane *exynos_plane;
	काष्ठा exynos_drm_plane_config plane_config = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ctx->drm_dev = drm_dev;

	plane_config.pixel_क्रमmats = क्रमmats;
	plane_config.num_pixel_क्रमmats = ARRAY_SIZE(क्रमmats);

	क्रम (i = 0; i < WINDOWS_NR; i++) अणु
		plane_config.zpos = i;
		plane_config.type = vidi_win_types[i];

		ret = exynos_plane_init(drm_dev, &ctx->planes[i], i,
					&plane_config);
		अगर (ret)
			वापस ret;
	पूर्ण

	exynos_plane = &ctx->planes[DEFAULT_WIN];
	ctx->crtc = exynos_drm_crtc_create(drm_dev, &exynos_plane->base,
			EXYNOS_DISPLAY_TYPE_VIDI, &vidi_crtc_ops, ctx);
	अगर (IS_ERR(ctx->crtc)) अणु
		DRM_DEV_ERROR(dev, "failed to create crtc.\n");
		वापस PTR_ERR(ctx->crtc);
	पूर्ण

	drm_simple_encoder_init(drm_dev, encoder, DRM_MODE_ENCODER_TMDS);

	drm_encoder_helper_add(encoder, &exynos_vidi_encoder_helper_funcs);

	ret = exynos_drm_set_possible_crtcs(encoder, EXYNOS_DISPLAY_TYPE_VIDI);
	अगर (ret < 0)
		वापस ret;

	ret = vidi_create_connector(encoder);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to create connector ret = %d\n",
			      ret);
		drm_encoder_cleanup(encoder);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम vidi_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा vidi_context *ctx = dev_get_drvdata(dev);

	del_समयr_sync(&ctx->समयr);
पूर्ण

अटल स्थिर काष्ठा component_ops vidi_component_ops = अणु
	.bind	= vidi_bind,
	.unbind = vidi_unbind,
पूर्ण;

अटल पूर्णांक vidi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vidi_context *ctx;
	काष्ठा device *dev = &pdev->dev;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = dev;

	समयr_setup(&ctx->समयr, vidi_fake_vblank_समयr, 0);

	mutex_init(&ctx->lock);

	platक्रमm_set_drvdata(pdev, ctx);

	वापस component_add(dev, &vidi_component_ops);
पूर्ण

अटल पूर्णांक vidi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vidi_context *ctx = platक्रमm_get_drvdata(pdev);

	अगर (ctx->raw_edid != (काष्ठा edid *)fake_edid_info) अणु
		kमुक्त(ctx->raw_edid);
		ctx->raw_edid = शून्य;

		वापस -EINVAL;
	पूर्ण

	component_del(&pdev->dev, &vidi_component_ops);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver vidi_driver = अणु
	.probe		= vidi_probe,
	.हटाओ		= vidi_हटाओ,
	.driver		= अणु
		.name	= "exynos-drm-vidi",
		.owner	= THIS_MODULE,
		.dev_groups = vidi_groups,
	पूर्ण,
पूर्ण;
