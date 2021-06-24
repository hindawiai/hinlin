<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2015 Broadcom
 * Copyright (C) 2013 Red Hat
 */

/**
 * DOC: Broadcom VC4 Graphics Driver
 *
 * The Broadcom VideoCore 4 (present in the Raspberry Pi) contains a
 * OpenGL ES 2.0-compatible 3D engine called V3D, and a highly
 * configurable display output pipeline that supports HDMI, DSI, DPI,
 * and Composite TV output.
 *
 * The 3D engine also has an पूर्णांकerface क्रम submitting arbitrary
 * compute shader-style jobs using the same shader processor as is
 * used क्रम vertex and fragment shaders in GLES 2.0.  However, given
 * that the hardware isn't able to expose any standard पूर्णांकerfaces like
 * OpenGL compute shaders or OpenCL, it isn't supported by this
 * driver.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "uapi/drm/vc4_drm.h"

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

#घोषणा DRIVER_NAME "vc4"
#घोषणा DRIVER_DESC "Broadcom VC4 graphics"
#घोषणा DRIVER_DATE "20140616"
#घोषणा DRIVER_MAJOR 0
#घोषणा DRIVER_MINOR 0
#घोषणा DRIVER_PATCHLEVEL 0

/* Helper function क्रम mapping the regs on a platक्रमm device. */
व्योम __iomem *vc4_ioremap_regs(काष्ठा platक्रमm_device *dev, पूर्णांक index)
अणु
	काष्ठा resource *res;
	व्योम __iomem *map;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, index);
	map = devm_ioremap_resource(&dev->dev, res);
	अगर (IS_ERR(map)) अणु
		DRM_ERROR("Failed to map registers: %ld\n", PTR_ERR(map));
		वापस map;
	पूर्ण

	वापस map;
पूर्ण

अटल पूर्णांक vc4_get_param_ioctl(काष्ठा drm_device *dev, व्योम *data,
			       काष्ठा drm_file *file_priv)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_vc4_get_param *args = data;
	पूर्णांक ret;

	अगर (args->pad != 0)
		वापस -EINVAL;

	अगर (!vc4->v3d)
		वापस -ENODEV;

	चयन (args->param) अणु
	हाल DRM_VC4_PARAM_V3D_IDENT0:
		ret = vc4_v3d_pm_get(vc4);
		अगर (ret)
			वापस ret;
		args->value = V3D_READ(V3D_IDENT0);
		vc4_v3d_pm_put(vc4);
		अवरोध;
	हाल DRM_VC4_PARAM_V3D_IDENT1:
		ret = vc4_v3d_pm_get(vc4);
		अगर (ret)
			वापस ret;
		args->value = V3D_READ(V3D_IDENT1);
		vc4_v3d_pm_put(vc4);
		अवरोध;
	हाल DRM_VC4_PARAM_V3D_IDENT2:
		ret = vc4_v3d_pm_get(vc4);
		अगर (ret)
			वापस ret;
		args->value = V3D_READ(V3D_IDENT2);
		vc4_v3d_pm_put(vc4);
		अवरोध;
	हाल DRM_VC4_PARAM_SUPPORTS_BRANCHES:
	हाल DRM_VC4_PARAM_SUPPORTS_ETC1:
	हाल DRM_VC4_PARAM_SUPPORTS_THREADED_FS:
	हाल DRM_VC4_PARAM_SUPPORTS_FIXED_RCL_ORDER:
	हाल DRM_VC4_PARAM_SUPPORTS_MADVISE:
	हाल DRM_VC4_PARAM_SUPPORTS_PERFMON:
		args->value = true;
		अवरोध;
	शेष:
		DRM_DEBUG("Unknown parameter %d\n", args->param);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा vc4_file *vc4file;

	vc4file = kzalloc(माप(*vc4file), GFP_KERNEL);
	अगर (!vc4file)
		वापस -ENOMEM;

	vc4_perfmon_खोलो_file(vc4file);
	file->driver_priv = vc4file;
	वापस 0;
पूर्ण

अटल व्योम vc4_बंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_file *vc4file = file->driver_priv;

	अगर (vc4file->bin_bo_used)
		vc4_v3d_bin_bo_put(vc4);

	vc4_perfmon_बंद_file(vc4file);
	kमुक्त(vc4file);
पूर्ण

DEFINE_DRM_GEM_FOPS(vc4_drm_fops);

अटल स्थिर काष्ठा drm_ioctl_desc vc4_drm_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(VC4_SUBMIT_CL, vc4_submit_cl_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_WAIT_SEQNO, vc4_रुको_seqno_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_WAIT_BO, vc4_रुको_bo_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_CREATE_BO, vc4_create_bo_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_MMAP_BO, vc4_mmap_bo_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_CREATE_SHADER_BO, vc4_create_shader_bo_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_GET_HANG_STATE, vc4_get_hang_state_ioctl,
			  DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(VC4_GET_PARAM, vc4_get_param_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_SET_TILING, vc4_set_tiling_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_GET_TILING, vc4_get_tiling_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_LABEL_BO, vc4_label_bo_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_GEM_MADVISE, vc4_gem_madvise_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_PERFMON_CREATE, vc4_perfmon_create_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_PERFMON_DESTROY, vc4_perfmon_destroy_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VC4_PERFMON_GET_VALUES, vc4_perfmon_get_values_ioctl, DRM_RENDER_ALLOW),
पूर्ण;

अटल काष्ठा drm_driver vc4_drm_driver = अणु
	.driver_features = (DRIVER_MODESET |
			    DRIVER_ATOMIC |
			    DRIVER_GEM |
			    DRIVER_RENDER |
			    DRIVER_SYNCOBJ),
	.खोलो = vc4_खोलो,
	.postबंद = vc4_बंद,
	.irq_handler = vc4_irq,
	.irq_preinstall = vc4_irq_preinstall,
	.irq_postinstall = vc4_irq_postinstall,
	.irq_uninstall = vc4_irq_uninstall,

#अगर defined(CONFIG_DEBUG_FS)
	.debugfs_init = vc4_debugfs_init,
#पूर्ण_अगर

	.gem_create_object = vc4_create_object,

	DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE(vc4_dumb_create),

	.ioctls = vc4_drm_ioctls,
	.num_ioctls = ARRAY_SIZE(vc4_drm_ioctls),
	.fops = &vc4_drm_fops,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;

अटल पूर्णांक compare_dev(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev == data;
पूर्ण

अटल व्योम vc4_match_add_drivers(काष्ठा device *dev,
				  काष्ठा component_match **match,
				  काष्ठा platक्रमm_driver *स्थिर *drivers,
				  पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा device_driver *drv = &drivers[i]->driver;
		काष्ठा device *p = शून्य, *d;

		जबतक ((d = platक्रमm_find_device_by_driver(p, drv))) अणु
			put_device(p);
			component_match_add(dev, match, compare_dev, d);
			p = d;
		पूर्ण
		put_device(p);
	पूर्ण
पूर्ण

अटल पूर्णांक vc4_drm_bind(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm;
	काष्ठा vc4_dev *vc4;
	काष्ठा device_node *node;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret = 0;

	dev->coherent_dma_mask = DMA_BIT_MASK(32);

	/* If VC4 V3D is missing, करोn't advertise render nodes. */
	node = of_find_matching_node_and_match(शून्य, vc4_v3d_dt_match, शून्य);
	अगर (!node || !of_device_is_available(node))
		vc4_drm_driver.driver_features &= ~DRIVER_RENDER;
	of_node_put(node);

	vc4 = devm_drm_dev_alloc(dev, &vc4_drm_driver, काष्ठा vc4_dev, base);
	अगर (IS_ERR(vc4))
		वापस PTR_ERR(vc4);

	drm = &vc4->base;
	platक्रमm_set_drvdata(pdev, drm);
	INIT_LIST_HEAD(&vc4->debugfs_list);

	mutex_init(&vc4->bin_bo_lock);

	ret = vc4_bo_cache_init(drm);
	अगर (ret)
		वापस ret;

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		वापस ret;

	ret = vc4_gem_init(drm);
	अगर (ret)
		वापस ret;

	ret = component_bind_all(dev, drm);
	अगर (ret)
		वापस ret;

	ret = vc4_plane_create_additional_planes(drm);
	अगर (ret)
		जाओ unbind_all;

	drm_fb_helper_हटाओ_conflicting_framebuffers(शून्य, "vc4drmfb", false);

	ret = vc4_kms_load(drm);
	अगर (ret < 0)
		जाओ unbind_all;

	drm_क्रम_each_crtc(crtc, drm)
		vc4_crtc_disable_at_boot(crtc);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret < 0)
		जाओ unbind_all;

	drm_fbdev_generic_setup(drm, 16);

	वापस 0;

unbind_all:
	component_unbind_all(dev, drm);

	वापस ret;
पूर्ण

अटल व्योम vc4_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	drm_dev_unरेजिस्टर(drm);

	drm_atomic_helper_shutकरोwn(drm);
पूर्ण

अटल स्थिर काष्ठा component_master_ops vc4_drm_ops = अणु
	.bind = vc4_drm_bind,
	.unbind = vc4_drm_unbind,
पूर्ण;

अटल काष्ठा platक्रमm_driver *स्थिर component_drivers[] = अणु
	&vc4_hdmi_driver,
	&vc4_vec_driver,
	&vc4_dpi_driver,
	&vc4_dsi_driver,
	&vc4_hvs_driver,
	&vc4_txp_driver,
	&vc4_crtc_driver,
	&vc4_v3d_driver,
पूर्ण;

अटल पूर्णांक vc4_platक्रमm_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा component_match *match = शून्य;
	काष्ठा device *dev = &pdev->dev;

	vc4_match_add_drivers(dev, &match,
			      component_drivers, ARRAY_SIZE(component_drivers));

	वापस component_master_add_with_match(dev, &vc4_drm_ops, match);
पूर्ण

अटल पूर्णांक vc4_platक्रमm_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &vc4_drm_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vc4_of_match[] = अणु
	अणु .compatible = "brcm,bcm2711-vc5", पूर्ण,
	अणु .compatible = "brcm,bcm2835-vc4", पूर्ण,
	अणु .compatible = "brcm,cygnus-vc4", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vc4_of_match);

अटल काष्ठा platक्रमm_driver vc4_platक्रमm_driver = अणु
	.probe		= vc4_platक्रमm_drm_probe,
	.हटाओ		= vc4_platक्रमm_drm_हटाओ,
	.driver		= अणु
		.name	= "vc4-drm",
		.of_match_table = vc4_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init vc4_drm_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_रेजिस्टर_drivers(component_drivers,
					ARRAY_SIZE(component_drivers));
	अगर (ret)
		वापस ret;

	वापस platक्रमm_driver_रेजिस्टर(&vc4_platक्रमm_driver);
पूर्ण

अटल व्योम __निकास vc4_drm_unरेजिस्टर(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(component_drivers,
				    ARRAY_SIZE(component_drivers));
	platक्रमm_driver_unरेजिस्टर(&vc4_platक्रमm_driver);
पूर्ण

module_init(vc4_drm_रेजिस्टर);
module_निकास(vc4_drm_unरेजिस्टर);

MODULE_ALIAS("platform:vc4-drm");
MODULE_DESCRIPTION("Broadcom VC4 DRM Driver");
MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_LICENSE("GPL v2");
