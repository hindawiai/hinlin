<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/component.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "sti_drv.h"
#समावेश "sti_plane.h"

#घोषणा DRIVER_NAME	"sti"
#घोषणा DRIVER_DESC	"STMicroelectronics SoC DRM"
#घोषणा DRIVER_DATE	"20140601"
#घोषणा DRIVER_MAJOR	1
#घोषणा DRIVER_MINOR	0

#घोषणा STI_MAX_FB_HEIGHT	4096
#घोषणा STI_MAX_FB_WIDTH	4096

अटल पूर्णांक sti_drm_fps_get(व्योम *data, u64 *val)
अणु
	काष्ठा drm_device *drm_dev = data;
	काष्ठा drm_plane *p;
	अचिन्हित पूर्णांक i = 0;

	*val = 0;
	list_क्रम_each_entry(p, &drm_dev->mode_config.plane_list, head) अणु
		काष्ठा sti_plane *plane = to_sti_plane(p);

		*val |= plane->fps_info.output << i;
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sti_drm_fps_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_device *drm_dev = data;
	काष्ठा drm_plane *p;
	अचिन्हित पूर्णांक i = 0;

	list_क्रम_each_entry(p, &drm_dev->mode_config.plane_list, head) अणु
		काष्ठा sti_plane *plane = to_sti_plane(p);

		स_रखो(&plane->fps_info, 0, माप(plane->fps_info));
		plane->fps_info.output = (val >> i) & 1;

		i++;
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(sti_drm_fps_fops,
			sti_drm_fps_get, sti_drm_fps_set, "%llu\n");

अटल पूर्णांक sti_drm_fps_dbg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा drm_plane *p;

	list_क्रम_each_entry(p, &dev->mode_config.plane_list, head) अणु
		काष्ठा sti_plane *plane = to_sti_plane(p);

		seq_म_लिखो(s, "%s%s\n",
			   plane->fps_info.fps_str,
			   plane->fps_info.fips_str);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list sti_drm_dbg_list[] = अणु
	अणु"fps_get", sti_drm_fps_dbg_show, 0पूर्ण,
पूर्ण;

अटल व्योम sti_drm_dbg_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(sti_drm_dbg_list,
				 ARRAY_SIZE(sti_drm_dbg_list),
				 minor->debugfs_root, minor);

	debugfs_create_file("fps_show", S_IRUGO | S_IWUSR, minor->debugfs_root,
			    minor->dev, &sti_drm_fps_fops);

	DRM_INFO("%s: debugfs installed\n", DRIVER_NAME);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs sti_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल व्योम sti_mode_config_init(काष्ठा drm_device *dev)
अणु
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	/*
	 * set max width and height as शेष value.
	 * this value would be used to check framebuffer size limitation
	 * at drm_mode_addfb().
	 */
	dev->mode_config.max_width = STI_MAX_FB_WIDTH;
	dev->mode_config.max_height = STI_MAX_FB_HEIGHT;

	dev->mode_config.funcs = &sti_mode_config_funcs;

	dev->mode_config.normalize_zpos = true;
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(sti_driver_fops);

अटल स्थिर काष्ठा drm_driver sti_driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	.fops = &sti_driver_fops,
	DRM_GEM_CMA_DRIVER_OPS,

	.debugfs_init = sti_drm_dbg_init,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
पूर्ण;

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

अटल पूर्णांक sti_init(काष्ठा drm_device *ddev)
अणु
	काष्ठा sti_निजी *निजी;

	निजी = kzalloc(माप(*निजी), GFP_KERNEL);
	अगर (!निजी)
		वापस -ENOMEM;

	ddev->dev_निजी = (व्योम *)निजी;
	dev_set_drvdata(ddev->dev, ddev);
	निजी->drm_dev = ddev;

	drm_mode_config_init(ddev);

	sti_mode_config_init(ddev);

	drm_kms_helper_poll_init(ddev);

	वापस 0;
पूर्ण

अटल व्योम sti_cleanup(काष्ठा drm_device *ddev)
अणु
	काष्ठा sti_निजी *निजी = ddev->dev_निजी;

	drm_kms_helper_poll_fini(ddev);
	drm_atomic_helper_shutकरोwn(ddev);
	drm_mode_config_cleanup(ddev);
	component_unbind_all(ddev->dev, ddev);
	kमुक्त(निजी);
	ddev->dev_निजी = शून्य;
पूर्ण

अटल पूर्णांक sti_bind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev;
	पूर्णांक ret;

	ddev = drm_dev_alloc(&sti_driver, dev);
	अगर (IS_ERR(ddev))
		वापस PTR_ERR(ddev);

	ret = sti_init(ddev);
	अगर (ret)
		जाओ err_drm_dev_put;

	ret = component_bind_all(ddev->dev, ddev);
	अगर (ret)
		जाओ err_cleanup;

	ret = drm_dev_रेजिस्टर(ddev, 0);
	अगर (ret)
		जाओ err_cleanup;

	drm_mode_config_reset(ddev);

	drm_fbdev_generic_setup(ddev, 32);

	वापस 0;

err_cleanup:
	sti_cleanup(ddev);
err_drm_dev_put:
	drm_dev_put(ddev);
	वापस ret;
पूर्ण

अटल व्योम sti_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);

	drm_dev_unरेजिस्टर(ddev);
	sti_cleanup(ddev);
	drm_dev_put(ddev);
पूर्ण

अटल स्थिर काष्ठा component_master_ops sti_ops = अणु
	.bind = sti_bind,
	.unbind = sti_unbind,
पूर्ण;

अटल पूर्णांक sti_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *child_np;
	काष्ठा component_match *match = शून्य;

	dma_set_coherent_mask(dev, DMA_BIT_MASK(32));

	devm_of_platक्रमm_populate(dev);

	child_np = of_get_next_available_child(node, शून्य);

	जबतक (child_np) अणु
		drm_of_component_match_add(dev, &match, compare_of,
					   child_np);
		child_np = of_get_next_available_child(node, child_np);
	पूर्ण

	वापस component_master_add_with_match(dev, &sti_ops, match);
पूर्ण

अटल पूर्णांक sti_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &sti_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sti_dt_ids[] = अणु
	अणु .compatible = "st,sti-display-subsystem", पूर्ण,
	अणु /* end node */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sti_dt_ids);

अटल काष्ठा platक्रमm_driver sti_platक्रमm_driver = अणु
	.probe = sti_platक्रमm_probe,
	.हटाओ = sti_platक्रमm_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = sti_dt_ids,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&sti_tvout_driver,
	&sti_hqvdp_driver,
	&sti_hdmi_driver,
	&sti_hda_driver,
	&sti_dvo_driver,
	&sti_vtg_driver,
	&sti_compositor_driver,
	&sti_platक्रमm_driver,
पूर्ण;

अटल पूर्णांक sti_drm_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_init(sti_drm_init);

अटल व्योम sti_drm_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_निकास(sti_drm_निकास);

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
MODULE_DESCRIPTION("STMicroelectronics SoC DRM driver");
MODULE_LICENSE("GPL");
