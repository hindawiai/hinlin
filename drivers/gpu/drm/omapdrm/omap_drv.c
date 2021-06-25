<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob@ti.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sort.h>
#समावेश <linux/sys_soc.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_bridge_connector.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "omap_dmm_tiler.h"
#समावेश "omap_drv.h"

#घोषणा DRIVER_NAME		MODULE_NAME
#घोषणा DRIVER_DESC		"OMAP DRM"
#घोषणा DRIVER_DATE		"20110917"
#घोषणा DRIVER_MAJOR		1
#घोषणा DRIVER_MINOR		0
#घोषणा DRIVER_PATCHLEVEL	0

/*
 * mode config funcs
 */

/* Notes about mapping DSS and DRM entities:
 *    CRTC:        overlay
 *    encoder:     manager.. with some extension to allow one primary CRTC
 *                 and zero or more video CRTC's to be mapped to one encoder?
 *    connector:   dssdev.. manager can be attached/detached from dअगरferent
 *                 devices
 */

अटल व्योम omap_atomic_रुको_क्रम_completion(काष्ठा drm_device *dev,
					    काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम_each_new_crtc_in_state(old_state, crtc, new_crtc_state, i) अणु
		अगर (!new_crtc_state->active)
			जारी;

		ret = omap_crtc_रुको_pending(crtc);

		अगर (!ret)
			dev_warn(dev->dev,
				 "atomic complete timeout (pipe %u)!\n", i);
	पूर्ण
पूर्ण

अटल व्योम omap_atomic_commit_tail(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_device *dev = old_state->dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	bool fence_cookie = dma_fence_begin_संकेतling();

	dispc_runसमय_get(priv->dispc);

	/* Apply the atomic update. */
	drm_atomic_helper_commit_modeset_disables(dev, old_state);

	अगर (priv->omaprev != 0x3430) अणु
		/* With the current dss dispc implementation we have to enable
		 * the new modeset beक्रमe we can commit planes. The dispc ovl
		 * configuration relies on the video mode configuration been
		 * written पूर्णांकo the HW when the ovl configuration is
		 * calculated.
		 *
		 * This approach is not ideal because after a mode change the
		 * plane update is executed only after the first vblank
		 * पूर्णांकerrupt. The dispc implementation should be fixed so that
		 * it is able use uncommitted drm state inक्रमmation.
		 */
		drm_atomic_helper_commit_modeset_enables(dev, old_state);
		omap_atomic_रुको_क्रम_completion(dev, old_state);

		drm_atomic_helper_commit_planes(dev, old_state, 0);
	पूर्ण अन्यथा अणु
		/*
		 * OMAP3 DSS seems to have issues with the work-around above,
		 * resulting in endless sync losts अगर a crtc is enabled without
		 * a plane. For now, skip the WA क्रम OMAP3.
		 */
		drm_atomic_helper_commit_planes(dev, old_state, 0);

		drm_atomic_helper_commit_modeset_enables(dev, old_state);
	पूर्ण

	drm_atomic_helper_commit_hw_करोne(old_state);

	dma_fence_end_संकेतling(fence_cookie);

	/*
	 * Wait क्रम completion of the page flips to ensure that old buffers
	 * can't be touched by the hardware anymore beक्रमe cleaning up planes.
	 */
	omap_atomic_रुको_क्रम_completion(dev, old_state);

	drm_atomic_helper_cleanup_planes(dev, old_state);

	dispc_runसमय_put(priv->dispc);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_helper_funcs omap_mode_config_helper_funcs = अणु
	.atomic_commit_tail = omap_atomic_commit_tail,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs omap_mode_config_funcs = अणु
	.fb_create = omap_framebuffer_create,
	.output_poll_changed = drm_fb_helper_output_poll_changed,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल व्योम omap_disconnect_pipelines(काष्ठा drm_device *ddev)
अणु
	काष्ठा omap_drm_निजी *priv = ddev->dev_निजी;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->num_pipes; i++) अणु
		काष्ठा omap_drm_pipeline *pipe = &priv->pipes[i];

		omapdss_device_disconnect(शून्य, pipe->output);

		omapdss_device_put(pipe->output);
		pipe->output = शून्य;
	पूर्ण

	स_रखो(&priv->channels, 0, माप(priv->channels));

	priv->num_pipes = 0;
पूर्ण

अटल पूर्णांक omap_connect_pipelines(काष्ठा drm_device *ddev)
अणु
	काष्ठा omap_drm_निजी *priv = ddev->dev_निजी;
	काष्ठा omap_dss_device *output = शून्य;
	पूर्णांक r;

	क्रम_each_dss_output(output) अणु
		r = omapdss_device_connect(priv->dss, शून्य, output);
		अगर (r == -EPROBE_DEFER) अणु
			omapdss_device_put(output);
			वापस r;
		पूर्ण अन्यथा अगर (r) अणु
			dev_warn(output->dev, "could not connect output %s\n",
				 output->name);
		पूर्ण अन्यथा अणु
			काष्ठा omap_drm_pipeline *pipe;

			pipe = &priv->pipes[priv->num_pipes++];
			pipe->output = omapdss_device_get(output);

			अगर (priv->num_pipes == ARRAY_SIZE(priv->pipes)) अणु
				/* To balance the 'for_each_dss_output' loop */
				omapdss_device_put(output);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_compare_pipelines(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा omap_drm_pipeline *pipe1 = a;
	स्थिर काष्ठा omap_drm_pipeline *pipe2 = b;

	अगर (pipe1->alias_id > pipe2->alias_id)
		वापस 1;
	अन्यथा अगर (pipe1->alias_id < pipe2->alias_id)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक omap_modeset_init_properties(काष्ठा drm_device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित पूर्णांक num_planes = dispc_get_num_ovls(priv->dispc);

	priv->zorder_prop = drm_property_create_range(dev, 0, "zorder", 0,
						      num_planes - 1);
	अगर (!priv->zorder_prop)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_display_id(काष्ठा omap_dss_device *output)
अणु
	काष्ठा device_node *node = शून्य;

	अगर (output->bridge) अणु
		काष्ठा drm_bridge *bridge = output->bridge;

		जबतक (drm_bridge_get_next_bridge(bridge))
			bridge = drm_bridge_get_next_bridge(bridge);

		node = bridge->of_node;
	पूर्ण

	वापस node ? of_alias_get_id(node, "display") : -ENODEV;
पूर्ण

अटल पूर्णांक omap_modeset_init(काष्ठा drm_device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	पूर्णांक num_ovls = dispc_get_num_ovls(priv->dispc);
	पूर्णांक num_mgrs = dispc_get_num_mgrs(priv->dispc);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	u32 plane_crtc_mask;

	अगर (!omapdss_stack_is_पढ़ोy())
		वापस -EPROBE_DEFER;

	drm_mode_config_init(dev);

	ret = omap_modeset_init_properties(dev);
	अगर (ret < 0)
		वापस ret;

	/*
	 * This function creates exactly one connector, encoder, crtc,
	 * and primary plane per each connected dss-device. Each
	 * connector->encoder->crtc chain is expected to be separate
	 * and each crtc is connect to a single dss-channel. If the
	 * configuration करोes not match the expectations or exceeds
	 * the available resources, the configuration is rejected.
	 */
	ret = omap_connect_pipelines(dev);
	अगर (ret < 0)
		वापस ret;

	अगर (priv->num_pipes > num_mgrs || priv->num_pipes > num_ovls) अणु
		dev_err(dev->dev, "%s(): Too many connected displays\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	/* Create all planes first. They can all be put to any CRTC. */
	plane_crtc_mask = (1 << priv->num_pipes) - 1;

	क्रम (i = 0; i < num_ovls; i++) अणु
		क्रमागत drm_plane_type type = i < priv->num_pipes
					 ? DRM_PLANE_TYPE_PRIMARY
					 : DRM_PLANE_TYPE_OVERLAY;
		काष्ठा drm_plane *plane;

		अगर (WARN_ON(priv->num_planes >= ARRAY_SIZE(priv->planes)))
			वापस -EINVAL;

		plane = omap_plane_init(dev, i, type, plane_crtc_mask);
		अगर (IS_ERR(plane))
			वापस PTR_ERR(plane);

		priv->planes[priv->num_planes++] = plane;
	पूर्ण

	/*
	 * Create the encoders, attach the bridges and get the pipeline alias
	 * IDs.
	 */
	क्रम (i = 0; i < priv->num_pipes; i++) अणु
		काष्ठा omap_drm_pipeline *pipe = &priv->pipes[i];
		पूर्णांक id;

		pipe->encoder = omap_encoder_init(dev, pipe->output);
		अगर (!pipe->encoder)
			वापस -ENOMEM;

		अगर (pipe->output->bridge) अणु
			ret = drm_bridge_attach(pipe->encoder,
						pipe->output->bridge, शून्य,
						DRM_BRIDGE_ATTACH_NO_CONNECTOR);
			अगर (ret < 0) अणु
				dev_err(priv->dev,
					"unable to attach bridge %pOF\n",
					pipe->output->bridge->of_node);
				वापस ret;
			पूर्ण
		पूर्ण

		id = omap_display_id(pipe->output);
		pipe->alias_id = id >= 0 ? id : i;
	पूर्ण

	/* Sort the pipelines by DT aliases. */
	sort(priv->pipes, priv->num_pipes, माप(priv->pipes[0]),
	     omap_compare_pipelines, शून्य);

	/*
	 * Populate the pipeline lookup table by DISPC channel. Only one display
	 * is allowed per channel.
	 */
	क्रम (i = 0; i < priv->num_pipes; ++i) अणु
		काष्ठा omap_drm_pipeline *pipe = &priv->pipes[i];
		क्रमागत omap_channel channel = pipe->output->dispc_channel;

		अगर (WARN_ON(priv->channels[channel] != शून्य))
			वापस -EINVAL;

		priv->channels[channel] = pipe;
	पूर्ण

	/* Create the connectors and CRTCs. */
	क्रम (i = 0; i < priv->num_pipes; i++) अणु
		काष्ठा omap_drm_pipeline *pipe = &priv->pipes[i];
		काष्ठा drm_encoder *encoder = pipe->encoder;
		काष्ठा drm_crtc *crtc;

		pipe->connector = drm_bridge_connector_init(dev, encoder);
		अगर (IS_ERR(pipe->connector)) अणु
			dev_err(priv->dev,
				"unable to create bridge connector for %s\n",
				pipe->output->name);
			वापस PTR_ERR(pipe->connector);
		पूर्ण

		drm_connector_attach_encoder(pipe->connector, encoder);

		crtc = omap_crtc_init(dev, pipe, priv->planes[i]);
		अगर (IS_ERR(crtc))
			वापस PTR_ERR(crtc);

		encoder->possible_crtcs = 1 << i;
		pipe->crtc = crtc;
	पूर्ण

	DBG("registered %u planes, %u crtcs/encoders/connectors\n",
	    priv->num_planes, priv->num_pipes);

	dev->mode_config.min_width = 8;
	dev->mode_config.min_height = 2;

	/*
	 * Note: these values are used क्रम multiple independent things:
	 * connector mode filtering, buffer sizes, crtc sizes...
	 * Use big enough values here to cover all use हालs, and करो more
	 * specअगरic checking in the respective code paths.
	 */
	dev->mode_config.max_width = 8192;
	dev->mode_config.max_height = 8192;

	/* We want the zpos to be normalized */
	dev->mode_config.normalize_zpos = true;

	dev->mode_config.funcs = &omap_mode_config_funcs;
	dev->mode_config.helper_निजी = &omap_mode_config_helper_funcs;

	drm_mode_config_reset(dev);

	omap_drm_irq_install(dev);

	वापस 0;
पूर्ण

अटल व्योम omap_modeset_fini(काष्ठा drm_device *ddev)
अणु
	omap_drm_irq_uninstall(ddev);

	drm_mode_config_cleanup(ddev);
पूर्ण

/*
 * Enable the HPD in बाह्यal components अगर supported
 */
अटल व्योम omap_modeset_enable_बाह्यal_hpd(काष्ठा drm_device *ddev)
अणु
	काष्ठा omap_drm_निजी *priv = ddev->dev_निजी;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->num_pipes; i++) अणु
		काष्ठा drm_connector *connector = priv->pipes[i].connector;

		अगर (!connector)
			जारी;

		अगर (priv->pipes[i].output->bridge)
			drm_bridge_connector_enable_hpd(connector);
	पूर्ण
पूर्ण

/*
 * Disable the HPD in बाह्यal components अगर supported
 */
अटल व्योम omap_modeset_disable_बाह्यal_hpd(काष्ठा drm_device *ddev)
अणु
	काष्ठा omap_drm_निजी *priv = ddev->dev_निजी;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->num_pipes; i++) अणु
		काष्ठा drm_connector *connector = priv->pipes[i].connector;

		अगर (!connector)
			जारी;

		अगर (priv->pipes[i].output->bridge)
			drm_bridge_connector_disable_hpd(connector);
	पूर्ण
पूर्ण

/*
 * drm ioctl funcs
 */


अटल पूर्णांक ioctl_get_param(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file_priv)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_omap_param *args = data;

	DBG("%p: param=%llu", dev, args->param);

	चयन (args->param) अणु
	हाल OMAP_PARAM_CHIPSET_ID:
		args->value = priv->omaprev;
		अवरोध;
	शेष:
		DBG("unknown parameter %lld", args->param);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा OMAP_BO_USER_MASK	0x00ffffff	/* flags settable by userspace */

अटल पूर्णांक ioctl_gem_new(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_omap_gem_new *args = data;
	u32 flags = args->flags & OMAP_BO_USER_MASK;

	VERB("%p:%p: size=0x%08x, flags=%08x", dev, file_priv,
	     args->size.bytes, flags);

	वापस omap_gem_new_handle(dev, file_priv, args->size, flags,
				   &args->handle);
पूर्ण

अटल पूर्णांक ioctl_gem_info(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_omap_gem_info *args = data;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret = 0;

	VERB("%p:%p: handle=%d", dev, file_priv, args->handle);

	obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	args->size = omap_gem_mmap_size(obj);
	args->offset = omap_gem_mmap_offset(obj);

	drm_gem_object_put(obj);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_ioctl_desc ioctls[DRM_COMMAND_END - DRM_COMMAND_BASE] = अणु
	DRM_IOCTL_DEF_DRV(OMAP_GET_PARAM, ioctl_get_param,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(OMAP_SET_PARAM, drm_invalid_op,
			  DRM_AUTH | DRM_MASTER | DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(OMAP_GEM_NEW, ioctl_gem_new,
			  DRM_RENDER_ALLOW),
	/* Deprecated, to be हटाओd. */
	DRM_IOCTL_DEF_DRV(OMAP_GEM_CPU_PREP, drm_noop,
			  DRM_RENDER_ALLOW),
	/* Deprecated, to be हटाओd. */
	DRM_IOCTL_DEF_DRV(OMAP_GEM_CPU_FINI, drm_noop,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(OMAP_GEM_INFO, ioctl_gem_info,
			  DRM_RENDER_ALLOW),
पूर्ण;

/*
 * drm driver funcs
 */

अटल पूर्णांक dev_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	file->driver_priv = शून्य;

	DBG("open: dev=%p, file=%p", dev, file);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations omapdriver_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.unlocked_ioctl = drm_ioctl,
	.compat_ioctl = drm_compat_ioctl,
	.release = drm_release,
	.mmap = omap_gem_mmap,
	.poll = drm_poll,
	.पढ़ो = drm_पढ़ो,
	.llseek = noop_llseek,
पूर्ण;

अटल स्थिर काष्ठा drm_driver omap_drm_driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM  |
		DRIVER_ATOMIC | DRIVER_RENDER,
	.खोलो = dev_खोलो,
	.lastबंद = drm_fb_helper_lastबंद,
#अगर_घोषित CONFIG_DEBUG_FS
	.debugfs_init = omap_debugfs_init,
#पूर्ण_अगर
	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import = omap_gem_prime_import,
	.dumb_create = omap_gem_dumb_create,
	.dumb_map_offset = omap_gem_dumb_map_offset,
	.ioctls = ioctls,
	.num_ioctls = DRM_OMAP_NUM_IOCTLS,
	.fops = &omapdriver_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute omapdrm_soc_devices[] = अणु
	अणु .family = "OMAP3", .data = (व्योम *)0x3430 पूर्ण,
	अणु .family = "OMAP4", .data = (व्योम *)0x4430 पूर्ण,
	अणु .family = "OMAP5", .data = (व्योम *)0x5430 पूर्ण,
	अणु .family = "DRA7",  .data = (व्योम *)0x0752 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक omapdrm_init(काष्ठा omap_drm_निजी *priv, काष्ठा device *dev)
अणु
	स्थिर काष्ठा soc_device_attribute *soc;
	काष्ठा dss_pdata *pdata = dev->platक्रमm_data;
	काष्ठा drm_device *ddev;
	पूर्णांक ret;

	DBG("%s", dev_name(dev));

	/* Allocate and initialize the DRM device. */
	ddev = drm_dev_alloc(&omap_drm_driver, dev);
	अगर (IS_ERR(ddev))
		वापस PTR_ERR(ddev);

	priv->ddev = ddev;
	ddev->dev_निजी = priv;

	priv->dev = dev;
	priv->dss = pdata->dss;
	priv->dispc = dispc_get_dispc(priv->dss);

	priv->dss->mgr_ops_priv = priv;

	soc = soc_device_match(omapdrm_soc_devices);
	priv->omaprev = soc ? (अचिन्हित पूर्णांक)soc->data : 0;
	priv->wq = alloc_ordered_workqueue("omapdrm", 0);

	mutex_init(&priv->list_lock);
	INIT_LIST_HEAD(&priv->obj_list);

	/* Get memory bandwidth limits */
	priv->max_bandwidth = dispc_get_memory_bandwidth_limit(priv->dispc);

	omap_gem_init(ddev);

	ret = omap_modeset_init(ddev);
	अगर (ret) अणु
		dev_err(priv->dev, "omap_modeset_init failed: ret=%d\n", ret);
		जाओ err_gem_deinit;
	पूर्ण

	/* Initialize vblank handling, start with all CRTCs disabled. */
	ret = drm_vblank_init(ddev, priv->num_pipes);
	अगर (ret) अणु
		dev_err(priv->dev, "could not init vblank\n");
		जाओ err_cleanup_modeset;
	पूर्ण

	omap_fbdev_init(ddev);

	drm_kms_helper_poll_init(ddev);
	omap_modeset_enable_बाह्यal_hpd(ddev);

	/*
	 * Register the DRM device with the core and the connectors with
	 * sysfs.
	 */
	ret = drm_dev_रेजिस्टर(ddev, 0);
	अगर (ret)
		जाओ err_cleanup_helpers;

	वापस 0;

err_cleanup_helpers:
	omap_modeset_disable_बाह्यal_hpd(ddev);
	drm_kms_helper_poll_fini(ddev);

	omap_fbdev_fini(ddev);
err_cleanup_modeset:
	omap_modeset_fini(ddev);
err_gem_deinit:
	omap_gem_deinit(ddev);
	destroy_workqueue(priv->wq);
	omap_disconnect_pipelines(ddev);
	drm_dev_put(ddev);
	वापस ret;
पूर्ण

अटल व्योम omapdrm_cleanup(काष्ठा omap_drm_निजी *priv)
अणु
	काष्ठा drm_device *ddev = priv->ddev;

	DBG("");

	drm_dev_unरेजिस्टर(ddev);

	omap_modeset_disable_बाह्यal_hpd(ddev);
	drm_kms_helper_poll_fini(ddev);

	omap_fbdev_fini(ddev);

	drm_atomic_helper_shutकरोwn(ddev);

	omap_modeset_fini(ddev);
	omap_gem_deinit(ddev);

	destroy_workqueue(priv->wq);

	omap_disconnect_pipelines(ddev);

	drm_dev_put(ddev);
पूर्ण

अटल पूर्णांक pdev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_drm_निजी *priv;
	पूर्णांक ret;

	ret = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to set the DMA mask\n");
		वापस ret;
	पूर्ण

	/* Allocate and initialize the driver निजी काष्ठाure. */
	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	ret = omapdrm_init(priv, &pdev->dev);
	अगर (ret < 0)
		kमुक्त(priv);

	वापस ret;
पूर्ण

अटल पूर्णांक pdev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_drm_निजी *priv = platक्रमm_get_drvdata(pdev);

	omapdrm_cleanup(priv);
	kमुक्त(priv);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक omap_drm_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = priv->ddev;

	वापस drm_mode_config_helper_suspend(drm_dev);
पूर्ण

अटल पूर्णांक omap_drm_resume(काष्ठा device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = priv->ddev;

	drm_mode_config_helper_resume(drm_dev);

	वापस omap_gem_resume(drm_dev);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(omapdrm_pm_ops, omap_drm_suspend, omap_drm_resume);

अटल काष्ठा platक्रमm_driver pdev = अणु
	.driver = अणु
		.name = "omapdrm",
		.pm = &omapdrm_pm_ops,
	पूर्ण,
	.probe = pdev_probe,
	.हटाओ = pdev_हटाओ,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&omap_dmm_driver,
	&pdev,
पूर्ण;

अटल पूर्णांक __init omap_drm_init(व्योम)
अणु
	पूर्णांक r;

	DBG("init");

	r = omap_dss_init();
	अगर (r)
		वापस r;

	r = platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
	अगर (r) अणु
		omap_dss_निकास();
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास omap_drm_fini(व्योम)
अणु
	DBG("fini");

	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));

	omap_dss_निकास();
पूर्ण

module_init(omap_drm_init);
module_निकास(omap_drm_fini);

MODULE_AUTHOR("Rob Clark <rob@ti.com>");
MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("OMAP DRM Display Driver");
MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_LICENSE("GPL v2");
