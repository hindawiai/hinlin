<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 *
 * based on exynos_drm_drv.c
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/component.h>
#समावेश <linux/console.h>
#समावेश <linux/iommu.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_fb.h"
#समावेश "rockchip_drm_fbdev.h"
#समावेश "rockchip_drm_gem.h"

#घोषणा DRIVER_NAME	"rockchip"
#घोषणा DRIVER_DESC	"RockChip Soc DRM"
#घोषणा DRIVER_DATE	"20140818"
#घोषणा DRIVER_MAJOR	1
#घोषणा DRIVER_MINOR	0

अटल bool is_support_iommu = true;
अटल स्थिर काष्ठा drm_driver rockchip_drm_driver;

/*
 * Attach a (component) device to the shared drm dma mapping from master drm
 * device.  This is used by the VOPs to map GEM buffers to a common DMA
 * mapping.
 */
पूर्णांक rockchip_drm_dma_attach_device(काष्ठा drm_device *drm_dev,
				   काष्ठा device *dev)
अणु
	काष्ठा rockchip_drm_निजी *निजी = drm_dev->dev_निजी;
	पूर्णांक ret;

	अगर (!is_support_iommu)
		वापस 0;

	ret = iommu_attach_device(निजी->करोमुख्य, dev);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "Failed to attach iommu device\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम rockchip_drm_dma_detach_device(काष्ठा drm_device *drm_dev,
				    काष्ठा device *dev)
अणु
	काष्ठा rockchip_drm_निजी *निजी = drm_dev->dev_निजी;
	काष्ठा iommu_करोमुख्य *करोमुख्य = निजी->करोमुख्य;

	अगर (!is_support_iommu)
		वापस;

	iommu_detach_device(करोमुख्य, dev);
पूर्ण

अटल पूर्णांक rockchip_drm_init_iommu(काष्ठा drm_device *drm_dev)
अणु
	काष्ठा rockchip_drm_निजी *निजी = drm_dev->dev_निजी;
	काष्ठा iommu_करोमुख्य_geometry *geometry;
	u64 start, end;

	अगर (!is_support_iommu)
		वापस 0;

	निजी->करोमुख्य = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
	अगर (!निजी->करोमुख्य)
		वापस -ENOMEM;

	geometry = &निजी->करोमुख्य->geometry;
	start = geometry->aperture_start;
	end = geometry->aperture_end;

	DRM_DEBUG("IOMMU context initialized (aperture: %#llx-%#llx)\n",
		  start, end);
	drm_mm_init(&निजी->mm, start, end - start + 1);
	mutex_init(&निजी->mm_lock);

	वापस 0;
पूर्ण

अटल व्योम rockchip_iommu_cleanup(काष्ठा drm_device *drm_dev)
अणु
	काष्ठा rockchip_drm_निजी *निजी = drm_dev->dev_निजी;

	अगर (!is_support_iommu)
		वापस;

	drm_mm_takeकरोwn(&निजी->mm);
	iommu_करोमुख्य_मुक्त(निजी->करोमुख्य);
पूर्ण

अटल पूर्णांक rockchip_drm_bind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev;
	काष्ठा rockchip_drm_निजी *निजी;
	पूर्णांक ret;

	drm_dev = drm_dev_alloc(&rockchip_drm_driver, dev);
	अगर (IS_ERR(drm_dev))
		वापस PTR_ERR(drm_dev);

	dev_set_drvdata(dev, drm_dev);

	निजी = devm_kzalloc(drm_dev->dev, माप(*निजी), GFP_KERNEL);
	अगर (!निजी) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	drm_dev->dev_निजी = निजी;

	INIT_LIST_HEAD(&निजी->psr_list);
	mutex_init(&निजी->psr_list_lock);

	ret = rockchip_drm_init_iommu(drm_dev);
	अगर (ret)
		जाओ err_मुक्त;

	ret = drmm_mode_config_init(drm_dev);
	अगर (ret)
		जाओ err_iommu_cleanup;

	rockchip_drm_mode_config_init(drm_dev);

	/* Try to bind all sub drivers. */
	ret = component_bind_all(dev, drm_dev);
	अगर (ret)
		जाओ err_iommu_cleanup;

	ret = drm_vblank_init(drm_dev, drm_dev->mode_config.num_crtc);
	अगर (ret)
		जाओ err_unbind_all;

	drm_mode_config_reset(drm_dev);

	/*
	 * enable drm irq mode.
	 * - with irq_enabled = true, we can use the vblank feature.
	 */
	drm_dev->irq_enabled = true;

	ret = rockchip_drm_fbdev_init(drm_dev);
	अगर (ret)
		जाओ err_unbind_all;

	/* init kms poll क्रम handling hpd */
	drm_kms_helper_poll_init(drm_dev);

	ret = drm_dev_रेजिस्टर(drm_dev, 0);
	अगर (ret)
		जाओ err_kms_helper_poll_fini;

	वापस 0;
err_kms_helper_poll_fini:
	drm_kms_helper_poll_fini(drm_dev);
	rockchip_drm_fbdev_fini(drm_dev);
err_unbind_all:
	component_unbind_all(dev, drm_dev);
err_iommu_cleanup:
	rockchip_iommu_cleanup(drm_dev);
err_मुक्त:
	drm_dev_put(drm_dev);
	वापस ret;
पूर्ण

अटल व्योम rockchip_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	drm_dev_unरेजिस्टर(drm_dev);

	rockchip_drm_fbdev_fini(drm_dev);
	drm_kms_helper_poll_fini(drm_dev);

	drm_atomic_helper_shutकरोwn(drm_dev);
	component_unbind_all(dev, drm_dev);
	rockchip_iommu_cleanup(drm_dev);

	drm_dev_put(drm_dev);
पूर्ण

अटल स्थिर काष्ठा file_operations rockchip_drm_driver_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.mmap = rockchip_gem_mmap,
	.poll = drm_poll,
	.पढ़ो = drm_पढ़ो,
	.unlocked_ioctl = drm_ioctl,
	.compat_ioctl = drm_compat_ioctl,
	.release = drm_release,
पूर्ण;

अटल स्थिर काष्ठा drm_driver rockchip_drm_driver = अणु
	.driver_features	= DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	.lastबंद		= drm_fb_helper_lastबंद,
	.dumb_create		= rockchip_gem_dumb_create,
	.prime_handle_to_fd	= drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle	= drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table	= rockchip_gem_prime_import_sg_table,
	.gem_prime_mmap		= rockchip_gem_mmap_buf,
	.fops			= &rockchip_drm_driver_fops,
	.name	= DRIVER_NAME,
	.desc	= DRIVER_DESC,
	.date	= DRIVER_DATE,
	.major	= DRIVER_MAJOR,
	.minor	= DRIVER_MINOR,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rockchip_drm_sys_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(drm);
पूर्ण

अटल पूर्णांक rockchip_drm_sys_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(drm);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rockchip_drm_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rockchip_drm_sys_suspend,
				rockchip_drm_sys_resume)
पूर्ण;

#घोषणा MAX_ROCKCHIP_SUB_DRIVERS 16
अटल काष्ठा platक्रमm_driver *rockchip_sub_drivers[MAX_ROCKCHIP_SUB_DRIVERS];
अटल पूर्णांक num_rockchip_sub_drivers;

/*
 * Check अगर a vop endpoपूर्णांक is leading to a rockchip subdriver or bridge.
 * Should be called from the component bind stage of the drivers
 * to ensure that all subdrivers are probed.
 *
 * @ep: endpoपूर्णांक of a rockchip vop
 *
 * वापसs true अगर subdriver, false अगर बाह्यal bridge and -ENODEV
 * अगर remote port करोes not contain a device.
 */
पूर्णांक rockchip_drm_endpoपूर्णांक_is_subdriver(काष्ठा device_node *ep)
अणु
	काष्ठा device_node *node = of_graph_get_remote_port_parent(ep);
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_driver *drv;
	पूर्णांक i;

	अगर (!node)
		वापस -ENODEV;

	/* status disabled will prevent creation of platक्रमm-devices */
	pdev = of_find_device_by_node(node);
	of_node_put(node);
	अगर (!pdev)
		वापस -ENODEV;

	/*
	 * All rockchip subdrivers have probed at this poपूर्णांक, so
	 * any device not having a driver now is an बाह्यal bridge.
	 */
	drv = pdev->dev.driver;
	अगर (!drv) अणु
		platक्रमm_device_put(pdev);
		वापस false;
	पूर्ण

	क्रम (i = 0; i < num_rockchip_sub_drivers; i++) अणु
		अगर (rockchip_sub_drivers[i] == to_platक्रमm_driver(drv)) अणु
			platक्रमm_device_put(pdev);
			वापस true;
		पूर्ण
	पूर्ण

	platक्रमm_device_put(pdev);
	वापस false;
पूर्ण

अटल पूर्णांक compare_dev(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev == (काष्ठा device *)data;
पूर्ण

अटल व्योम rockchip_drm_match_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;

	list_क्रम_each_entry(link, &dev->links.consumers, s_node)
		device_link_del(link);
पूर्ण

अटल काष्ठा component_match *rockchip_drm_match_add(काष्ठा device *dev)
अणु
	काष्ठा component_match *match = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < num_rockchip_sub_drivers; i++) अणु
		काष्ठा platक्रमm_driver *drv = rockchip_sub_drivers[i];
		काष्ठा device *p = शून्य, *d;

		करो अणु
			d = platक्रमm_find_device_by_driver(p, &drv->driver);
			put_device(p);
			p = d;

			अगर (!d)
				अवरोध;

			device_link_add(dev, d, DL_FLAG_STATELESS);
			component_match_add(dev, &match, compare_dev, d);
		पूर्ण जबतक (true);
	पूर्ण

	अगर (IS_ERR(match))
		rockchip_drm_match_हटाओ(dev);

	वापस match ?: ERR_PTR(-ENODEV);
पूर्ण

अटल स्थिर काष्ठा component_master_ops rockchip_drm_ops = अणु
	.bind = rockchip_drm_bind,
	.unbind = rockchip_drm_unbind,
पूर्ण;

अटल पूर्णांक rockchip_drm_platक्रमm_of_probe(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *port;
	bool found = false;
	पूर्णांक i;

	अगर (!np)
		वापस -ENODEV;

	क्रम (i = 0;; i++) अणु
		काष्ठा device_node *iommu;

		port = of_parse_phandle(np, "ports", i);
		अगर (!port)
			अवरोध;

		अगर (!of_device_is_available(port->parent)) अणु
			of_node_put(port);
			जारी;
		पूर्ण

		iommu = of_parse_phandle(port->parent, "iommus", 0);
		अगर (!iommu || !of_device_is_available(iommu->parent)) अणु
			DRM_DEV_DEBUG(dev,
				      "no iommu attached for %pOF, using non-iommu buffers\n",
				      port->parent);
			/*
			 * अगर there is a crtc not support iommu, क्रमce set all
			 * crtc use non-iommu buffer.
			 */
			is_support_iommu = false;
		पूर्ण

		found = true;

		of_node_put(iommu);
		of_node_put(port);
	पूर्ण

	अगर (i == 0) अणु
		DRM_DEV_ERROR(dev, "missing 'ports' property\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!found) अणु
		DRM_DEV_ERROR(dev,
			      "No available vop found for display-subsystem.\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_drm_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा component_match *match = शून्य;
	पूर्णांक ret;

	ret = rockchip_drm_platक्रमm_of_probe(dev);
	अगर (ret)
		वापस ret;

	match = rockchip_drm_match_add(dev);
	अगर (IS_ERR(match))
		वापस PTR_ERR(match);

	ret = component_master_add_with_match(dev, &rockchip_drm_ops, match);
	अगर (ret < 0) अणु
		rockchip_drm_match_हटाओ(dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_drm_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &rockchip_drm_ops);

	rockchip_drm_match_हटाओ(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम rockchip_drm_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *drm = platक्रमm_get_drvdata(pdev);

	अगर (drm)
		drm_atomic_helper_shutकरोwn(drm);
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_drm_dt_ids[] = अणु
	अणु .compatible = "rockchip,display-subsystem", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_drm_dt_ids);

अटल काष्ठा platक्रमm_driver rockchip_drm_platक्रमm_driver = अणु
	.probe = rockchip_drm_platक्रमm_probe,
	.हटाओ = rockchip_drm_platक्रमm_हटाओ,
	.shutकरोwn = rockchip_drm_platक्रमm_shutकरोwn,
	.driver = अणु
		.name = "rockchip-drm",
		.of_match_table = rockchip_drm_dt_ids,
		.pm = &rockchip_drm_pm_ops,
	पूर्ण,
पूर्ण;

#घोषणा ADD_ROCKCHIP_SUB_DRIVER(drv, cond) अणु \
	अगर (IS_ENABLED(cond) && \
	    !WARN_ON(num_rockchip_sub_drivers >= MAX_ROCKCHIP_SUB_DRIVERS)) \
		rockchip_sub_drivers[num_rockchip_sub_drivers++] = &drv; \
पूर्ण

अटल पूर्णांक __init rockchip_drm_init(व्योम)
अणु
	पूर्णांक ret;

	num_rockchip_sub_drivers = 0;
	ADD_ROCKCHIP_SUB_DRIVER(vop_platक्रमm_driver, CONFIG_DRM_ROCKCHIP);
	ADD_ROCKCHIP_SUB_DRIVER(rockchip_lvds_driver,
				CONFIG_ROCKCHIP_LVDS);
	ADD_ROCKCHIP_SUB_DRIVER(rockchip_dp_driver,
				CONFIG_ROCKCHIP_ANALOGIX_DP);
	ADD_ROCKCHIP_SUB_DRIVER(cdn_dp_driver, CONFIG_ROCKCHIP_CDN_DP);
	ADD_ROCKCHIP_SUB_DRIVER(dw_hdmi_rockchip_pltfm_driver,
				CONFIG_ROCKCHIP_DW_HDMI);
	ADD_ROCKCHIP_SUB_DRIVER(dw_mipi_dsi_rockchip_driver,
				CONFIG_ROCKCHIP_DW_MIPI_DSI);
	ADD_ROCKCHIP_SUB_DRIVER(inno_hdmi_driver, CONFIG_ROCKCHIP_INNO_HDMI);
	ADD_ROCKCHIP_SUB_DRIVER(rk3066_hdmi_driver,
				CONFIG_ROCKCHIP_RK3066_HDMI);

	ret = platक्रमm_रेजिस्टर_drivers(rockchip_sub_drivers,
					num_rockchip_sub_drivers);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&rockchip_drm_platक्रमm_driver);
	अगर (ret)
		जाओ err_unreg_drivers;

	वापस 0;

err_unreg_drivers:
	platक्रमm_unरेजिस्टर_drivers(rockchip_sub_drivers,
				    num_rockchip_sub_drivers);
	वापस ret;
पूर्ण

अटल व्योम __निकास rockchip_drm_fini(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&rockchip_drm_platक्रमm_driver);

	platक्रमm_unरेजिस्टर_drivers(rockchip_sub_drivers,
				    num_rockchip_sub_drivers);
पूर्ण

module_init(rockchip_drm_init);
module_निकास(rockchip_drm_fini);

MODULE_AUTHOR("Mark Yao <mark.yao@rock-chips.com>");
MODULE_DESCRIPTION("ROCKCHIP DRM Driver");
MODULE_LICENSE("GPL v2");
