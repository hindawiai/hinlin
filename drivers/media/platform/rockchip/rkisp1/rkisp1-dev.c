<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Rockchip ISP1 Driver - Base driver
 *
 * Copyright (C) 2019 Collabora, Ltd.
 *
 * Based on Rockchip ISP1 driver by Rockchip Electronics Co., Ltd.
 * Copyright (C) 2017 Rockchip Electronics Co., Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-mipi-dphy.h>
#समावेश <media/v4l2-fwnode.h>

#समावेश "rkisp1-common.h"

/*
 * ISP Details
 * -----------
 *
 * ISP Comprises with:
 *	MIPI serial camera पूर्णांकerface
 *	Image Signal Processing
 *	Many Image Enhancement Blocks
 *	Crop
 *	Resizer
 *	RBG display पढ़ोy image
 *	Image Rotation
 *
 * ISP Block Diagram
 * -----------------
 *                                                             rkisp1-resizer.c          rkisp1-capture.c
 *                                                          |====================|  |=======================|
 *                                rkisp1-isp.c                              Main Picture Path
 *                        |==========================|      |===============================================|
 *                        +-----------+  +--+--+--+--+      +--------+  +--------+              +-----------+
 *                        |           |  |  |  |  |  |      |        |  |        |              |           |
 * +--------+    |\       |           |  |  |  |  |  |   -->|  Crop  |->|  RSZ   |------------->|           |
 * |  MIPI  |--->|  \     |           |  |  |  |  |  |   |  |        |  |        |              |           |
 * +--------+    |   |    |           |  |IE|IE|IE|IE|   |  +--------+  +--------+              |  Memory   |
 *               |MUX|--->|    ISP    |->|0 |1 |2 |3 |---+                                      | Interface |
 * +--------+    |   |    |           |  |  |  |  |  |   |  +--------+  +--------+  +--------+  |           |
 * |Parallel|--->|  /     |           |  |  |  |  |  |   |  |        |  |        |  |        |  |           |
 * +--------+    |/       |           |  |  |  |  |  |   -->|  Crop  |->|  RSZ   |->|  RGB   |->|           |
 *                        |           |  |  |  |  |  |      |        |  |        |  | Rotate |  |           |
 *                        +-----------+  +--+--+--+--+      +--------+  +--------+  +--------+  +-----------+
 *                                               ^
 * +--------+                                    |          |===============================================|
 * |  DMA   |------------------------------------+                          Self Picture Path
 * +--------+
 *
 *         rkisp1-stats.c        rkisp1-params.c
 *       |===============|      |===============|
 *       +---------------+      +---------------+
 *       |               |      |               |
 *       |      ISP      |      |      ISP      |
 *       |               |      |               |
 *       +---------------+      +---------------+
 *
 *
 * Media Topology
 * --------------
 *      +----------+     +----------+
 *      | Sensor 2 |     | Sensor X |
 *      ------------ ... ------------
 *      |    0     |     |    0     |
 *      +----------+     +----------+      +-----------+
 *                  \      |               |  params   |
 *                   \     |               | (output)  |
 *    +----------+    \    |               +-----------+
 *    | Sensor 1 |     v   v                     |
 *    ------------      +------+------+          |
 *    |    0     |----->|  0   |  1   |<---------+
 *    +----------+      |------+------|
 *                      |     ISP     |
 *                      |------+------|
 *        +-------------|  2   |  3   |----------+
 *        |             +------+------+          |
 *        |                |                     |
 *        v                v                     v
 *  +- ---------+    +-----------+         +-----------+
 *  |     0     |    |     0     |         |   stats   |
 *  -------------    -------------         | (capture) |
 *  |  Resizer  |    |  Resizer  |         +-----------+
 *  ------------|    ------------|
 *  |     1     |    |     1     |
 *  +-----------+    +-----------+
 *        |                |
 *        v                v
 *  +-----------+    +-----------+
 *  | selfpath  |    | मुख्यpath  |
 *  | (capture) |    | (capture) |
 *  +-----------+    +-----------+
 */

काष्ठा rkisp1_match_data अणु
	स्थिर अक्षर * स्थिर *clks;
	अचिन्हित पूर्णांक size;
	क्रमागत rkisp1_cअगर_isp_version isp_ver;
पूर्ण;

/* ----------------------------------------------------------------------------
 * Sensor DT bindings
 */

अटल पूर्णांक rkisp1_create_links(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा media_entity *source, *sink;
	अचिन्हित पूर्णांक flags, source_pad;
	काष्ठा v4l2_subdev *sd;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* sensor links */
	flags = MEDIA_LNK_FL_ENABLED;
	list_क्रम_each_entry(sd, &rkisp1->v4l2_dev.subdevs, list) अणु
		अगर (sd == &rkisp1->isp.sd ||
		    sd == &rkisp1->resizer_devs[RKISP1_MAINPATH].sd ||
		    sd == &rkisp1->resizer_devs[RKISP1_SELFPATH].sd)
			जारी;

		ret = media_entity_get_fwnode_pad(&sd->entity, sd->fwnode,
						  MEDIA_PAD_FL_SOURCE);
		अगर (ret < 0) अणु
			dev_err(rkisp1->dev, "failed to find src pad for %s\n",
				sd->name);
			वापस ret;
		पूर्ण
		source_pad = ret;

		ret = media_create_pad_link(&sd->entity, source_pad,
					    &rkisp1->isp.sd.entity,
					    RKISP1_ISP_PAD_SINK_VIDEO,
					    flags);
		अगर (ret)
			वापस ret;

		flags = 0;
	पूर्ण

	flags = MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE;

	/* create ISP->RSZ->CAP links */
	क्रम (i = 0; i < 2; i++) अणु
		source = &rkisp1->isp.sd.entity;
		sink = &rkisp1->resizer_devs[i].sd.entity;
		ret = media_create_pad_link(source, RKISP1_ISP_PAD_SOURCE_VIDEO,
					    sink, RKISP1_RSZ_PAD_SINK,
					    MEDIA_LNK_FL_ENABLED);
		अगर (ret)
			वापस ret;

		source = sink;
		sink = &rkisp1->capture_devs[i].vnode.vdev.entity;
		ret = media_create_pad_link(source, RKISP1_RSZ_PAD_SRC,
					    sink, 0, flags);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* params links */
	source = &rkisp1->params.vnode.vdev.entity;
	sink = &rkisp1->isp.sd.entity;
	ret = media_create_pad_link(source, 0, sink,
				    RKISP1_ISP_PAD_SINK_PARAMS, flags);
	अगर (ret)
		वापस ret;

	/* 3A stats links */
	source = &rkisp1->isp.sd.entity;
	sink = &rkisp1->stats.vnode.vdev.entity;
	वापस media_create_pad_link(source, RKISP1_ISP_PAD_SOURCE_STATS,
				     sink, 0, flags);
पूर्ण

अटल पूर्णांक rkisp1_subdev_notअगरier_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
					काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा rkisp1_device *rkisp1 =
		container_of(notअगरier, काष्ठा rkisp1_device, notअगरier);
	काष्ठा rkisp1_sensor_async *s_asd =
		container_of(asd, काष्ठा rkisp1_sensor_async, asd);

	s_asd->pixel_rate_ctrl = v4l2_ctrl_find(sd->ctrl_handler,
						V4L2_CID_PIXEL_RATE);
	s_asd->sd = sd;
	s_asd->dphy = devm_phy_get(rkisp1->dev, "dphy");
	अगर (IS_ERR(s_asd->dphy)) अणु
		अगर (PTR_ERR(s_asd->dphy) != -EPROBE_DEFER)
			dev_err(rkisp1->dev, "Couldn't get the MIPI D-PHY\n");
		वापस PTR_ERR(s_asd->dphy);
	पूर्ण

	phy_init(s_asd->dphy);

	वापस 0;
पूर्ण

अटल व्योम rkisp1_subdev_notअगरier_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
					  काष्ठा v4l2_subdev *sd,
					  काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा rkisp1_sensor_async *s_asd =
		container_of(asd, काष्ठा rkisp1_sensor_async, asd);

	phy_निकास(s_asd->dphy);
पूर्ण

अटल पूर्णांक rkisp1_subdev_notअगरier_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा rkisp1_device *rkisp1 =
		container_of(notअगरier, काष्ठा rkisp1_device, notअगरier);
	पूर्णांक ret;

	ret = rkisp1_create_links(rkisp1);
	अगर (ret)
		वापस ret;

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&rkisp1->v4l2_dev);
	अगर (ret)
		वापस ret;

	dev_dbg(rkisp1->dev, "Async subdev notifier completed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations rkisp1_subdev_notअगरier_ops = अणु
	.bound = rkisp1_subdev_notअगरier_bound,
	.unbind = rkisp1_subdev_notअगरier_unbind,
	.complete = rkisp1_subdev_notअगरier_complete,
पूर्ण;

अटल पूर्णांक rkisp1_subdev_notअगरier(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा v4l2_async_notअगरier *ntf = &rkisp1->notअगरier;
	अचिन्हित पूर्णांक next_id = 0;
	पूर्णांक ret;

	v4l2_async_notअगरier_init(ntf);

	जबतक (1) अणु
		काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
			.bus_type = V4L2_MBUS_CSI2_DPHY
		पूर्ण;
		काष्ठा rkisp1_sensor_async *rk_asd;
		काष्ठा fwnode_handle *ep;

		ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(rkisp1->dev),
						     0, next_id,
						     FWNODE_GRAPH_ENDPOINT_NEXT);
		अगर (!ep)
			अवरोध;

		ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);
		अगर (ret)
			जाओ err_parse;

		rk_asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(ntf, ep,
							काष्ठा rkisp1_sensor_async);
		अगर (IS_ERR(rk_asd)) अणु
			ret = PTR_ERR(rk_asd);
			जाओ err_parse;
		पूर्ण

		rk_asd->mbus_type = vep.bus_type;
		rk_asd->mbus_flags = vep.bus.mipi_csi2.flags;
		rk_asd->lanes = vep.bus.mipi_csi2.num_data_lanes;

		dev_dbg(rkisp1->dev, "registered ep id %d with %d lanes\n",
			vep.base.id, rk_asd->lanes);

		next_id = vep.base.id + 1;

		fwnode_handle_put(ep);

		जारी;
err_parse:
		fwnode_handle_put(ep);
		v4l2_async_notअगरier_cleanup(ntf);
		वापस ret;
	पूर्ण

	अगर (next_id == 0)
		dev_dbg(rkisp1->dev, "no remote subdevice found\n");
	ntf->ops = &rkisp1_subdev_notअगरier_ops;
	ret = v4l2_async_notअगरier_रेजिस्टर(&rkisp1->v4l2_dev, ntf);
	अगर (ret) अणु
		v4l2_async_notअगरier_cleanup(ntf);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------------
 * Power
 */

अटल पूर्णांक __maybe_unused rkisp1_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rkisp1_device *rkisp1 = dev_get_drvdata(dev);

	clk_bulk_disable_unprepare(rkisp1->clk_size, rkisp1->clks);
	वापस pinctrl_pm_select_sleep_state(dev);
पूर्ण

अटल पूर्णांक __maybe_unused rkisp1_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rkisp1_device *rkisp1 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret)
		वापस ret;
	ret = clk_bulk_prepare_enable(rkisp1->clk_size, rkisp1->clks);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rkisp1_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(rkisp1_runसमय_suspend, rkisp1_runसमय_resume, शून्य)
पूर्ण;

/* ----------------------------------------------------------------------------
 * Core
 */

अटल पूर्णांक rkisp1_entities_रेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	पूर्णांक ret;

	ret = rkisp1_isp_रेजिस्टर(rkisp1);
	अगर (ret)
		वापस ret;

	ret = rkisp1_resizer_devs_रेजिस्टर(rkisp1);
	अगर (ret)
		जाओ err_unreg_isp_subdev;

	ret = rkisp1_capture_devs_रेजिस्टर(rkisp1);
	अगर (ret)
		जाओ err_unreg_resizer_devs;

	ret = rkisp1_stats_रेजिस्टर(rkisp1);
	अगर (ret)
		जाओ err_unreg_capture_devs;

	ret = rkisp1_params_रेजिस्टर(rkisp1);
	अगर (ret)
		जाओ err_unreg_stats;

	ret = rkisp1_subdev_notअगरier(rkisp1);
	अगर (ret) अणु
		dev_err(rkisp1->dev,
			"Failed to register subdev notifier(%d)\n", ret);
		जाओ err_unreg_params;
	पूर्ण

	वापस 0;
err_unreg_params:
	rkisp1_params_unरेजिस्टर(rkisp1);
err_unreg_stats:
	rkisp1_stats_unरेजिस्टर(rkisp1);
err_unreg_capture_devs:
	rkisp1_capture_devs_unरेजिस्टर(rkisp1);
err_unreg_resizer_devs:
	rkisp1_resizer_devs_unरेजिस्टर(rkisp1);
err_unreg_isp_subdev:
	rkisp1_isp_unरेजिस्टर(rkisp1);
	वापस ret;
पूर्ण

अटल irqवापस_t rkisp1_isr(पूर्णांक irq, व्योम *ctx)
अणु
	काष्ठा device *dev = ctx;
	काष्ठा rkisp1_device *rkisp1 = dev_get_drvdata(dev);

	/*
	 * Call rkisp1_capture_isr() first to handle the frame that
	 * potentially completed using the current frame_sequence number beक्रमe
	 * it is potentially incremented by rkisp1_isp_isr() in the vertical
	 * sync.
	 */
	rkisp1_capture_isr(rkisp1);
	rkisp1_isp_isr(rkisp1);
	rkisp1_mipi_isr(rkisp1);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अक्षर * स्थिर rk3399_isp_clks[] = अणु
	"isp",
	"aclk",
	"hclk",
पूर्ण;

अटल स्थिर काष्ठा rkisp1_match_data rk3399_isp_match_data = अणु
	.clks = rk3399_isp_clks,
	.size = ARRAY_SIZE(rk3399_isp_clks),
	.isp_ver = RKISP1_V10,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rkisp1_of_match[] = अणु
	अणु
		.compatible = "rockchip,rk3399-cif-isp",
		.data = &rk3399_isp_match_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rkisp1_of_match);

अटल व्योम rkisp1_debug_init(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_debug *debug = &rkisp1->debug;

	debug->debugfs_dir = debugfs_create_dir(RKISP1_DRIVER_NAME, शून्य);
	debugfs_create_uदीर्घ("data_loss", 0444, debug->debugfs_dir,
			     &debug->data_loss);
	debugfs_create_uदीर्घ("outform_size_err", 0444,  debug->debugfs_dir,
			     &debug->outक्रमm_size_error);
	debugfs_create_uदीर्घ("img_stabilization_size_error", 0444,
			     debug->debugfs_dir,
			     &debug->img_stabilization_size_error);
	debugfs_create_uदीर्घ("inform_size_error", 0444,  debug->debugfs_dir,
			     &debug->inक्रमm_size_error);
	debugfs_create_uदीर्घ("irq_delay", 0444,  debug->debugfs_dir,
			     &debug->irq_delay);
	debugfs_create_uदीर्घ("mipi_error", 0444, debug->debugfs_dir,
			     &debug->mipi_error);
	debugfs_create_uदीर्घ("stats_error", 0444, debug->debugfs_dir,
			     &debug->stats_error);
	debugfs_create_uदीर्घ("mp_stop_timeout", 0444, debug->debugfs_dir,
			     &debug->stop_समयout[RKISP1_MAINPATH]);
	debugfs_create_uदीर्घ("sp_stop_timeout", 0444, debug->debugfs_dir,
			     &debug->stop_समयout[RKISP1_SELFPATH]);
	debugfs_create_uदीर्घ("mp_frame_drop", 0444, debug->debugfs_dir,
			     &debug->frame_drop[RKISP1_MAINPATH]);
	debugfs_create_uदीर्घ("sp_frame_drop", 0444, debug->debugfs_dir,
			     &debug->frame_drop[RKISP1_SELFPATH]);
पूर्ण

अटल पूर्णांक rkisp1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा rkisp1_match_data *match_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rkisp1_device *rkisp1;
	काष्ठा v4l2_device *v4l2_dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret, irq;

	match_data = of_device_get_match_data(&pdev->dev);
	अगर (!match_data)
		वापस -ENODEV;

	rkisp1 = devm_kzalloc(dev, माप(*rkisp1), GFP_KERNEL);
	अगर (!rkisp1)
		वापस -ENOMEM;

	dev_set_drvdata(dev, rkisp1);
	rkisp1->dev = dev;

	mutex_init(&rkisp1->stream_lock);

	rkisp1->base_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rkisp1->base_addr))
		वापस PTR_ERR(rkisp1->base_addr);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, rkisp1_isr, IRQF_SHARED,
			       dev_driver_string(dev), dev);
	अगर (ret) अणु
		dev_err(dev, "request irq failed: %d\n", ret);
		वापस ret;
	पूर्ण

	rkisp1->irq = irq;

	क्रम (i = 0; i < match_data->size; i++)
		rkisp1->clks[i].id = match_data->clks[i];
	ret = devm_clk_bulk_get(dev, match_data->size, rkisp1->clks);
	अगर (ret)
		वापस ret;
	rkisp1->clk_size = match_data->size;

	pm_runसमय_enable(&pdev->dev);

	rkisp1->media_dev.hw_revision = match_data->isp_ver;
	strscpy(rkisp1->media_dev.model, RKISP1_DRIVER_NAME,
		माप(rkisp1->media_dev.model));
	rkisp1->media_dev.dev = &pdev->dev;
	strscpy(rkisp1->media_dev.bus_info, RKISP1_BUS_INFO,
		माप(rkisp1->media_dev.bus_info));
	media_device_init(&rkisp1->media_dev);

	v4l2_dev = &rkisp1->v4l2_dev;
	v4l2_dev->mdev = &rkisp1->media_dev;
	strscpy(v4l2_dev->name, RKISP1_DRIVER_NAME, माप(v4l2_dev->name));

	ret = v4l2_device_रेजिस्टर(rkisp1->dev, &rkisp1->v4l2_dev);
	अगर (ret)
		वापस ret;

	ret = media_device_रेजिस्टर(&rkisp1->media_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register media device: %d\n", ret);
		जाओ err_unreg_v4l2_dev;
	पूर्ण

	ret = rkisp1_entities_रेजिस्टर(rkisp1);
	अगर (ret)
		जाओ err_unreg_media_dev;

	rkisp1_debug_init(rkisp1);

	वापस 0;

err_unreg_media_dev:
	media_device_unरेजिस्टर(&rkisp1->media_dev);
err_unreg_v4l2_dev:
	v4l2_device_unरेजिस्टर(&rkisp1->v4l2_dev);
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक rkisp1_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rkisp1_device *rkisp1 = platक्रमm_get_drvdata(pdev);

	v4l2_async_notअगरier_unरेजिस्टर(&rkisp1->notअगरier);
	v4l2_async_notअगरier_cleanup(&rkisp1->notअगरier);

	rkisp1_params_unरेजिस्टर(rkisp1);
	rkisp1_stats_unरेजिस्टर(rkisp1);
	rkisp1_capture_devs_unरेजिस्टर(rkisp1);
	rkisp1_resizer_devs_unरेजिस्टर(rkisp1);
	rkisp1_isp_unरेजिस्टर(rkisp1);

	media_device_unरेजिस्टर(&rkisp1->media_dev);
	v4l2_device_unरेजिस्टर(&rkisp1->v4l2_dev);

	pm_runसमय_disable(&pdev->dev);

	debugfs_हटाओ_recursive(rkisp1->debug.debugfs_dir);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rkisp1_drv = अणु
	.driver = अणु
		.name = RKISP1_DRIVER_NAME,
		.of_match_table = of_match_ptr(rkisp1_of_match),
		.pm = &rkisp1_pm_ops,
	पूर्ण,
	.probe = rkisp1_probe,
	.हटाओ = rkisp1_हटाओ,
पूर्ण;

module_platक्रमm_driver(rkisp1_drv);
MODULE_DESCRIPTION("Rockchip ISP1 platform driver");
MODULE_LICENSE("Dual MIT/GPL");
