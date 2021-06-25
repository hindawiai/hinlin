<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Archit Taneja <archit@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_panel.h>

#समावेश "dss.h"
#समावेश "omapdss.h"

पूर्णांक omapdss_device_init_output(काष्ठा omap_dss_device *out,
			       काष्ठा drm_bridge *local_bridge)
अणु
	काष्ठा device_node *remote_node;
	पूर्णांक ret;

	remote_node = of_graph_get_remote_node(out->dev->of_node,
					       out->of_port, 0);
	अगर (!remote_node) अणु
		dev_dbg(out->dev, "failed to find video sink\n");
		वापस 0;
	पूर्ण

	out->bridge = of_drm_find_bridge(remote_node);
	out->panel = of_drm_find_panel(remote_node);
	अगर (IS_ERR(out->panel))
		out->panel = शून्य;

	of_node_put(remote_node);

	अगर (out->panel) अणु
		काष्ठा drm_bridge *bridge;

		bridge = drm_panel_bridge_add(out->panel);
		अगर (IS_ERR(bridge)) अणु
			dev_err(out->dev,
				"unable to create panel bridge (%ld)\n",
				PTR_ERR(bridge));
			ret = PTR_ERR(bridge);
			जाओ error;
		पूर्ण

		out->bridge = bridge;
	पूर्ण

	अगर (local_bridge) अणु
		अगर (!out->bridge) अणु
			ret = -EPROBE_DEFER;
			जाओ error;
		पूर्ण

		out->next_bridge = out->bridge;
		out->bridge = local_bridge;
	पूर्ण

	अगर (!out->bridge) अणु
		ret = -EPROBE_DEFER;
		जाओ error;
	पूर्ण

	वापस 0;

error:
	omapdss_device_cleanup_output(out);
	वापस ret;
पूर्ण

व्योम omapdss_device_cleanup_output(काष्ठा omap_dss_device *out)
अणु
	अगर (out->bridge && out->panel)
		drm_panel_bridge_हटाओ(out->next_bridge ?
					out->next_bridge : out->bridge);
पूर्ण

व्योम dss_mgr_set_timings(काष्ठा omap_dss_device *dssdev,
			 स्थिर काष्ठा videomode *vm)
अणु
	omap_crtc_dss_set_timings(dssdev->dss->mgr_ops_priv,
					  dssdev->dispc_channel, vm);
पूर्ण

व्योम dss_mgr_set_lcd_config(काष्ठा omap_dss_device *dssdev,
		स्थिर काष्ठा dss_lcd_mgr_config *config)
अणु
	omap_crtc_dss_set_lcd_config(dssdev->dss->mgr_ops_priv,
					     dssdev->dispc_channel, config);
पूर्ण

पूर्णांक dss_mgr_enable(काष्ठा omap_dss_device *dssdev)
अणु
	वापस omap_crtc_dss_enable(dssdev->dss->mgr_ops_priv,
					    dssdev->dispc_channel);
पूर्ण

व्योम dss_mgr_disable(काष्ठा omap_dss_device *dssdev)
अणु
	omap_crtc_dss_disable(dssdev->dss->mgr_ops_priv,
				      dssdev->dispc_channel);
पूर्ण

व्योम dss_mgr_start_update(काष्ठा omap_dss_device *dssdev)
अणु
	omap_crtc_dss_start_update(dssdev->dss->mgr_ops_priv,
					   dssdev->dispc_channel);
पूर्ण

पूर्णांक dss_mgr_रेजिस्टर_frameकरोne_handler(काष्ठा omap_dss_device *dssdev,
		व्योम (*handler)(व्योम *), व्योम *data)
अणु
	काष्ठा dss_device *dss = dssdev->dss;

	वापस omap_crtc_dss_रेजिस्टर_frameकरोne(dss->mgr_ops_priv,
							dssdev->dispc_channel,
							handler, data);
पूर्ण

व्योम dss_mgr_unरेजिस्टर_frameकरोne_handler(काष्ठा omap_dss_device *dssdev,
		व्योम (*handler)(व्योम *), व्योम *data)
अणु
	काष्ठा dss_device *dss = dssdev->dss;

	omap_crtc_dss_unरेजिस्टर_frameकरोne(dss->mgr_ops_priv,
						   dssdev->dispc_channel,
						   handler, data);
पूर्ण
