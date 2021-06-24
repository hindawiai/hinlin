<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "sun4i_drv.h"
#समावेश "sun4i_frontend.h"
#समावेश "sun4i_framebuffer.h"
#समावेश "sun4i_tcon.h"
#समावेश "sun8i_tcon_top.h"

अटल पूर्णांक drm_sun4i_gem_dumb_create(काष्ठा drm_file *file_priv,
				     काष्ठा drm_device *drm,
				     काष्ठा drm_mode_create_dumb *args)
अणु
	/* The hardware only allows even pitches क्रम YUV buffers. */
	args->pitch = ALIGN(DIV_ROUND_UP(args->width * args->bpp, 8), 2);

	वापस drm_gem_cma_dumb_create_पूर्णांकernal(file_priv, drm, args);
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(sun4i_drv_fops);

अटल स्थिर काष्ठा drm_driver sun4i_drv_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,

	/* Generic Operations */
	.fops			= &sun4i_drv_fops,
	.name			= "sun4i-drm",
	.desc			= "Allwinner sun4i Display Engine",
	.date			= "20150629",
	.major			= 1,
	.minor			= 0,

	/* GEM Operations */
	DRM_GEM_CMA_DRIVER_OPS_VMAP_WITH_DUMB_CREATE(drm_sun4i_gem_dumb_create),
पूर्ण;

अटल पूर्णांक sun4i_drv_bind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm;
	काष्ठा sun4i_drv *drv;
	पूर्णांक ret;

	drm = drm_dev_alloc(&sun4i_drv_driver, dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	drv = devm_kzalloc(dev, माप(*drv), GFP_KERNEL);
	अगर (!drv) अणु
		ret = -ENOMEM;
		जाओ मुक्त_drm;
	पूर्ण

	dev_set_drvdata(dev, drm);
	drm->dev_निजी = drv;
	INIT_LIST_HEAD(&drv->frontend_list);
	INIT_LIST_HEAD(&drv->engine_list);
	INIT_LIST_HEAD(&drv->tcon_list);

	ret = of_reserved_mem_device_init(dev);
	अगर (ret && ret != -ENODEV) अणु
		dev_err(drm->dev, "Couldn't claim our memory region\n");
		जाओ मुक्त_drm;
	पूर्ण

	drm_mode_config_init(drm);

	ret = component_bind_all(drm->dev, drm);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't bind all pipelines components\n");
		जाओ cleanup_mode_config;
	पूर्ण

	/* drm_vblank_init calls kसुस्मृति, which can fail */
	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	अगर (ret)
		जाओ cleanup_mode_config;

	drm->irq_enabled = true;

	/* Remove early framebuffers (ie. simplefb) */
	drm_fb_helper_हटाओ_conflicting_framebuffers(शून्य, "sun4i-drm-fb", false);

	sun4i_framebuffer_init(drm);

	/* Enable connectors polling */
	drm_kms_helper_poll_init(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		जाओ finish_poll;

	drm_fbdev_generic_setup(drm, 32);

	वापस 0;

finish_poll:
	drm_kms_helper_poll_fini(drm);
cleanup_mode_config:
	drm_mode_config_cleanup(drm);
	of_reserved_mem_device_release(dev);
मुक्त_drm:
	drm_dev_put(drm);
	वापस ret;
पूर्ण

अटल व्योम sun4i_drv_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	drm_dev_unरेजिस्टर(drm);
	drm_kms_helper_poll_fini(drm);
	drm_atomic_helper_shutकरोwn(drm);
	drm_mode_config_cleanup(drm);

	component_unbind_all(dev, शून्य);
	of_reserved_mem_device_release(dev);

	drm_dev_put(drm);
पूर्ण

अटल स्थिर काष्ठा component_master_ops sun4i_drv_master_ops = अणु
	.bind	= sun4i_drv_bind,
	.unbind	= sun4i_drv_unbind,
पूर्ण;

अटल bool sun4i_drv_node_is_connector(काष्ठा device_node *node)
अणु
	वापस of_device_is_compatible(node, "hdmi-connector");
पूर्ण

अटल bool sun4i_drv_node_is_frontend(काष्ठा device_node *node)
अणु
	वापस of_device_is_compatible(node, "allwinner,sun4i-a10-display-frontend") ||
		of_device_is_compatible(node, "allwinner,sun5i-a13-display-frontend") ||
		of_device_is_compatible(node, "allwinner,sun6i-a31-display-frontend") ||
		of_device_is_compatible(node, "allwinner,sun7i-a20-display-frontend") ||
		of_device_is_compatible(node, "allwinner,sun8i-a23-display-frontend") ||
		of_device_is_compatible(node, "allwinner,sun8i-a33-display-frontend") ||
		of_device_is_compatible(node, "allwinner,sun9i-a80-display-frontend");
पूर्ण

अटल bool sun4i_drv_node_is_deu(काष्ठा device_node *node)
अणु
	वापस of_device_is_compatible(node, "allwinner,sun9i-a80-deu");
पूर्ण

अटल bool sun4i_drv_node_is_supported_frontend(काष्ठा device_node *node)
अणु
	अगर (IS_ENABLED(CONFIG_DRM_SUN4I_BACKEND))
		वापस !!of_match_node(sun4i_frontend_of_table, node);

	वापस false;
पूर्ण

अटल bool sun4i_drv_node_is_tcon(काष्ठा device_node *node)
अणु
	वापस !!of_match_node(sun4i_tcon_of_table, node);
पूर्ण

अटल bool sun4i_drv_node_is_tcon_with_ch0(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा of_device_id *match;

	match = of_match_node(sun4i_tcon_of_table, node);
	अगर (match) अणु
		काष्ठा sun4i_tcon_quirks *quirks;

		quirks = (काष्ठा sun4i_tcon_quirks *)match->data;

		वापस quirks->has_channel_0;
	पूर्ण

	वापस false;
पूर्ण

अटल bool sun4i_drv_node_is_tcon_top(काष्ठा device_node *node)
अणु
	वापस IS_ENABLED(CONFIG_DRM_SUN8I_TCON_TOP) &&
		!!of_match_node(sun8i_tcon_top_of_table, node);
पूर्ण

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	DRM_DEBUG_DRIVER("Comparing of node %pOF with %pOF\n",
			 dev->of_node,
			 data);

	वापस dev->of_node == data;
पूर्ण

/*
 * The encoder drivers use drm_of_find_possible_crtcs to get upstream
 * crtcs from the device tree using of_graph. For the results to be
 * correct, encoders must be probed/bound after _all_ crtcs have been
 * created. The existing code uses a depth first recursive traversal
 * of the of_graph, which means the encoders करोwnstream of the TCON
 * get add right after the first TCON. The second TCON or CRTC will
 * never be properly associated with encoders connected to it.
 *
 * Also, in a dual display pipeline setup, both frontends can feed
 * either backend, and both backends can feed either TCON, we want
 * all components of the same type to be added beक्रमe the next type
 * in the pipeline. Fortunately, the pipelines are perfectly symmetric,
 * i.e. components of the same type are at the same depth when counted
 * from the frontend. The only exception is the third pipeline in
 * the A80 SoC, which we करो not support anyway.
 *
 * Hence we can use a bपढ़ोth first search traversal order to add
 * components. We करो not need to check क्रम duplicates. The component
 * matching प्रणाली handles this क्रम us.
 */
काष्ठा endpoपूर्णांक_list अणु
	DECLARE_KFIFO(fअगरo, काष्ठा device_node *, 16);
पूर्ण;

अटल व्योम sun4i_drv_traverse_endpoपूर्णांकs(काष्ठा endpoपूर्णांक_list *list,
					 काष्ठा device_node *node,
					 पूर्णांक port_id)
अणु
	काष्ठा device_node *ep, *remote, *port;

	port = of_graph_get_port_by_id(node, port_id);
	अगर (!port) अणु
		DRM_DEBUG_DRIVER("No output to bind on port %d\n", port_id);
		वापस;
	पूर्ण

	क्रम_each_available_child_of_node(port, ep) अणु
		remote = of_graph_get_remote_port_parent(ep);
		अगर (!remote) अणु
			DRM_DEBUG_DRIVER("Error retrieving the output node\n");
			जारी;
		पूर्ण

		अगर (sun4i_drv_node_is_tcon(node)) अणु
			/*
			 * TCON TOP is always probed beक्रमe TCON. However, TCON
			 * poपूर्णांकs back to TCON TOP when it is source क्रम HDMI.
			 * We have to skip it here to prevent infinite looping
			 * between TCON TOP and TCON.
			 */
			अगर (sun4i_drv_node_is_tcon_top(remote)) अणु
				DRM_DEBUG_DRIVER("TCON output endpoint is TCON TOP... skipping\n");
				of_node_put(remote);
				जारी;
			पूर्ण

			/*
			 * If the node is our TCON with channel 0, the first
			 * port is used क्रम panel or bridges, and will not be
			 * part of the component framework.
			 */
			अगर (sun4i_drv_node_is_tcon_with_ch0(node)) अणु
				काष्ठा of_endpoपूर्णांक endpoपूर्णांक;

				अगर (of_graph_parse_endpoपूर्णांक(ep, &endpoपूर्णांक)) अणु
					DRM_DEBUG_DRIVER("Couldn't parse endpoint\n");
					of_node_put(remote);
					जारी;
				पूर्ण

				अगर (!endpoपूर्णांक.id) अणु
					DRM_DEBUG_DRIVER("Endpoint is our panel... skipping\n");
					of_node_put(remote);
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण

		kfअगरo_put(&list->fअगरo, remote);
	पूर्ण
पूर्ण

अटल पूर्णांक sun4i_drv_add_endpoपूर्णांकs(काष्ठा device *dev,
				   काष्ठा endpoपूर्णांक_list *list,
				   काष्ठा component_match **match,
				   काष्ठा device_node *node)
अणु
	पूर्णांक count = 0;

	/*
	 * The frontend has been disabled in some of our old device
	 * trees. If we find a node that is the frontend and is
	 * disabled, we should just follow through and parse its
	 * child, but without adding it to the component list.
	 * Otherwise, we obviously want to add it to the list.
	 */
	अगर (!sun4i_drv_node_is_frontend(node) &&
	    !of_device_is_available(node))
		वापस 0;

	/*
	 * The connectors will be the last nodes in our pipeline, we
	 * can just bail out.
	 */
	अगर (sun4i_drv_node_is_connector(node))
		वापस 0;

	/*
	 * If the device is either just a regular device, or an
	 * enabled frontend supported by the driver, we add it to our
	 * component list.
	 */
	अगर (!(sun4i_drv_node_is_frontend(node) ||
	      sun4i_drv_node_is_deu(node)) ||
	    (sun4i_drv_node_is_supported_frontend(node) &&
	     of_device_is_available(node))) अणु
		/* Add current component */
		DRM_DEBUG_DRIVER("Adding component %pOF\n", node);
		drm_of_component_match_add(dev, match, compare_of, node);
		count++;
	पूर्ण

	/* each node has at least one output */
	sun4i_drv_traverse_endpoपूर्णांकs(list, node, 1);

	/* TCON TOP has second and third output */
	अगर (sun4i_drv_node_is_tcon_top(node)) अणु
		sun4i_drv_traverse_endpoपूर्णांकs(list, node, 3);
		sun4i_drv_traverse_endpoपूर्णांकs(list, node, 5);
	पूर्ण

	वापस count;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sun4i_drv_drm_sys_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(drm);
पूर्ण

अटल पूर्णांक sun4i_drv_drm_sys_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(drm);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sun4i_drv_drm_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sun4i_drv_drm_sys_suspend,
				sun4i_drv_drm_sys_resume)
पूर्ण;

अटल पूर्णांक sun4i_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा component_match *match = शून्य;
	काष्ठा device_node *np = pdev->dev.of_node, *endpoपूर्णांक;
	काष्ठा endpoपूर्णांक_list list;
	पूर्णांक i, ret, count = 0;

	INIT_KFIFO(list.fअगरo);

	क्रम (i = 0;; i++) अणु
		काष्ठा device_node *pipeline = of_parse_phandle(np,
								"allwinner,pipelines",
								i);
		अगर (!pipeline)
			अवरोध;

		kfअगरo_put(&list.fअगरo, pipeline);
	पूर्ण

	जबतक (kfअगरo_get(&list.fअगरo, &endpoपूर्णांक)) अणु
		/* process this endpoपूर्णांक */
		ret = sun4i_drv_add_endpoपूर्णांकs(&pdev->dev, &list, &match,
					      endpoपूर्णांक);

		/* sun4i_drv_add_endpoपूर्णांकs can fail to allocate memory */
		अगर (ret < 0)
			वापस ret;

		count += ret;
	पूर्ण

	अगर (count)
		वापस component_master_add_with_match(&pdev->dev,
						       &sun4i_drv_master_ops,
						       match);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक sun4i_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &sun4i_drv_master_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_drv_of_table[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun5i-a10s-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun5i-a13-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31s-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun7i-a20-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun8i-a23-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun8i-a33-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun8i-h3-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun8i-r40-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun8i-v3s-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun9i-a80-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-display-engine" पूर्ण,
	अणु .compatible = "allwinner,sun50i-h6-display-engine" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_drv_of_table);

अटल काष्ठा platक्रमm_driver sun4i_drv_platक्रमm_driver = अणु
	.probe		= sun4i_drv_probe,
	.हटाओ		= sun4i_drv_हटाओ,
	.driver		= अणु
		.name		= "sun4i-drm",
		.of_match_table	= sun4i_drv_of_table,
		.pm = &sun4i_drv_drm_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun4i_drv_platक्रमm_driver);

MODULE_AUTHOR("Boris Brezillon <boris.brezillon@free-electrons.com>");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A10 Display Engine DRM/KMS Driver");
MODULE_LICENSE("GPL");
