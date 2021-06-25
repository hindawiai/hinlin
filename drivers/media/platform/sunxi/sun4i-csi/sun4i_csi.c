<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 NextThing Co
 * Copyright (C) 2016-2019 Bootlin
 *
 * Author: Maxime Ripard <maxime.ripard@bootlin.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mediabus.h>

#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "sun4i_csi.h"

काष्ठा sun4i_csi_traits अणु
	अचिन्हित पूर्णांक channels;
	अचिन्हित पूर्णांक max_width;
	bool has_isp;
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations sun4i_csi_video_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल पूर्णांक sun4i_csi_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				  काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा sun4i_csi *csi = container_of(notअगरier, काष्ठा sun4i_csi,
					     notअगरier);

	csi->src_subdev = subdev;
	csi->src_pad = media_entity_get_fwnode_pad(&subdev->entity,
						   subdev->fwnode,
						   MEDIA_PAD_FL_SOURCE);
	अगर (csi->src_pad < 0) अणु
		dev_err(csi->dev, "Couldn't find output pad for subdev %s\n",
			subdev->name);
		वापस csi->src_pad;
	पूर्ण

	dev_dbg(csi->dev, "Bound %s pad: %d\n", subdev->name, csi->src_pad);
	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा sun4i_csi *csi = container_of(notअगरier, काष्ठा sun4i_csi,
					     notअगरier);
	काष्ठा v4l2_subdev *subdev = &csi->subdev;
	काष्ठा video_device *vdev = &csi->vdev;
	पूर्णांक ret;

	ret = v4l2_device_रेजिस्टर_subdev(&csi->v4l, subdev);
	अगर (ret < 0)
		वापस ret;

	ret = sun4i_csi_v4l2_रेजिस्टर(csi);
	अगर (ret < 0)
		वापस ret;

	ret = media_device_रेजिस्टर(&csi->mdev);
	अगर (ret)
		वापस ret;

	/* Create link from subdev to मुख्य device */
	ret = media_create_pad_link(&subdev->entity, CSI_SUBDEV_SOURCE,
				    &vdev->entity, 0,
				    MEDIA_LNK_FL_ENABLED |
				    MEDIA_LNK_FL_IMMUTABLE);
	अगर (ret)
		जाओ err_clean_media;

	ret = media_create_pad_link(&csi->src_subdev->entity, csi->src_pad,
				    &subdev->entity, CSI_SUBDEV_SINK,
				    MEDIA_LNK_FL_ENABLED |
				    MEDIA_LNK_FL_IMMUTABLE);
	अगर (ret)
		जाओ err_clean_media;

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&csi->v4l);
	अगर (ret < 0)
		जाओ err_clean_media;

	वापस 0;

err_clean_media:
	media_device_unरेजिस्टर(&csi->mdev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations sun4i_csi_notअगरy_ops = अणु
	.bound		= sun4i_csi_notअगरy_bound,
	.complete	= sun4i_csi_notअगरy_complete,
पूर्ण;

अटल पूर्णांक sun4i_csi_notअगरier_init(काष्ठा sun4i_csi *csi)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
		.bus_type = V4L2_MBUS_PARALLEL,
	पूर्ण;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा fwnode_handle *ep;
	पूर्णांक ret;

	v4l2_async_notअगरier_init(&csi->notअगरier);

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(csi->dev), 0, 0,
					     FWNODE_GRAPH_ENDPOINT_NEXT);
	अगर (!ep)
		वापस -EINVAL;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);
	अगर (ret)
		जाओ out;

	csi->bus = vep.bus.parallel;

	asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(&csi->notअगरier, ep,
							   काष्ठा v4l2_async_subdev);
	अगर (IS_ERR(asd)) अणु
		ret = PTR_ERR(asd);
		जाओ out;
	पूर्ण

	csi->notअगरier.ops = &sun4i_csi_notअगरy_ops;

out:
	fwnode_handle_put(ep);
	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_csi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v4l2_subdev *subdev;
	काष्ठा video_device *vdev;
	काष्ठा sun4i_csi *csi;
	काष्ठा resource *res;
	पूर्णांक ret;
	पूर्णांक irq;

	csi = devm_kzalloc(&pdev->dev, माप(*csi), GFP_KERNEL);
	अगर (!csi)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, csi);
	csi->dev = &pdev->dev;
	subdev = &csi->subdev;
	vdev = &csi->vdev;

	csi->traits = of_device_get_match_data(&pdev->dev);
	अगर (!csi->traits)
		वापस -EINVAL;

	csi->mdev.dev = csi->dev;
	strscpy(csi->mdev.model, "Allwinner Video Capture Device",
		माप(csi->mdev.model));
	csi->mdev.hw_revision = 0;
	snम_लिखो(csi->mdev.bus_info, माप(csi->mdev.bus_info), "platform:%s",
		 dev_name(csi->dev));
	media_device_init(&csi->mdev);
	csi->v4l.mdev = &csi->mdev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	csi->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(csi->regs))
		वापस PTR_ERR(csi->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	csi->bus_clk = devm_clk_get(&pdev->dev, "bus");
	अगर (IS_ERR(csi->bus_clk)) अणु
		dev_err(&pdev->dev, "Couldn't get our bus clock\n");
		वापस PTR_ERR(csi->bus_clk);
	पूर्ण

	अगर (csi->traits->has_isp) अणु
		csi->isp_clk = devm_clk_get(&pdev->dev, "isp");
		अगर (IS_ERR(csi->isp_clk)) अणु
			dev_err(&pdev->dev, "Couldn't get our ISP clock\n");
			वापस PTR_ERR(csi->isp_clk);
		पूर्ण
	पूर्ण

	csi->ram_clk = devm_clk_get(&pdev->dev, "ram");
	अगर (IS_ERR(csi->ram_clk)) अणु
		dev_err(&pdev->dev, "Couldn't get our ram clock\n");
		वापस PTR_ERR(csi->ram_clk);
	पूर्ण

	csi->rst = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(csi->rst)) अणु
		dev_err(&pdev->dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(csi->rst);
	पूर्ण

	/* Initialize subdev */
	v4l2_subdev_init(subdev, &sun4i_csi_subdev_ops);
	subdev->flags = V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
	subdev->entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	subdev->owner = THIS_MODULE;
	snम_लिखो(subdev->name, माप(subdev->name), "sun4i-csi-0");
	v4l2_set_subdevdata(subdev, csi);

	csi->subdev_pads[CSI_SUBDEV_SINK].flags =
		MEDIA_PAD_FL_SINK | MEDIA_PAD_FL_MUST_CONNECT;
	csi->subdev_pads[CSI_SUBDEV_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&subdev->entity, CSI_SUBDEV_PADS,
				     csi->subdev_pads);
	अगर (ret < 0)
		वापस ret;

	csi->vdev_pad.flags = MEDIA_PAD_FL_SINK | MEDIA_PAD_FL_MUST_CONNECT;
	vdev->entity.ops = &sun4i_csi_video_entity_ops;
	ret = media_entity_pads_init(&vdev->entity, 1, &csi->vdev_pad);
	अगर (ret < 0)
		वापस ret;

	ret = sun4i_csi_dma_रेजिस्टर(csi, irq);
	अगर (ret)
		जाओ err_clean_pad;

	ret = sun4i_csi_notअगरier_init(csi);
	अगर (ret)
		जाओ err_unरेजिस्टर_media;

	ret = v4l2_async_notअगरier_रेजिस्टर(&csi->v4l, &csi->notअगरier);
	अगर (ret) अणु
		dev_err(csi->dev, "Couldn't register our notifier.\n");
		जाओ err_unरेजिस्टर_media;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	वापस 0;

err_unरेजिस्टर_media:
	media_device_unरेजिस्टर(&csi->mdev);
	sun4i_csi_dma_unरेजिस्टर(csi);

err_clean_pad:
	media_device_cleanup(&csi->mdev);

	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_csi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_csi *csi = platक्रमm_get_drvdata(pdev);

	v4l2_async_notअगरier_unरेजिस्टर(&csi->notअगरier);
	v4l2_async_notअगरier_cleanup(&csi->notअगरier);
	vb2_video_unरेजिस्टर_device(&csi->vdev);
	media_device_unरेजिस्टर(&csi->mdev);
	sun4i_csi_dma_unरेजिस्टर(csi);
	media_device_cleanup(&csi->mdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun4i_csi_traits sun4i_a10_csi1_traits = अणु
	.channels = 1,
	.max_width = 24,
	.has_isp = false,
पूर्ण;

अटल स्थिर काष्ठा sun4i_csi_traits sun7i_a20_csi0_traits = अणु
	.channels = 4,
	.max_width = 16,
	.has_isp = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun4i_csi_of_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-csi1", .data = &sun4i_a10_csi1_traits पूर्ण,
	अणु .compatible = "allwinner,sun7i-a20-csi0", .data = &sun7i_a20_csi0_traits पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_csi_of_match);

अटल पूर्णांक __maybe_unused sun4i_csi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sun4i_csi *csi = dev_get_drvdata(dev);

	reset_control_deनिश्चित(csi->rst);
	clk_prepare_enable(csi->bus_clk);
	clk_prepare_enable(csi->ram_clk);
	clk_set_rate(csi->isp_clk, 80000000);
	clk_prepare_enable(csi->isp_clk);

	ग_लिखोl(1, csi->regs + CSI_EN_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sun4i_csi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sun4i_csi *csi = dev_get_drvdata(dev);

	clk_disable_unprepare(csi->isp_clk);
	clk_disable_unprepare(csi->ram_clk);
	clk_disable_unprepare(csi->bus_clk);

	reset_control_निश्चित(csi->rst);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sun4i_csi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sun4i_csi_runसमय_suspend,
			   sun4i_csi_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sun4i_csi_driver = अणु
	.probe	= sun4i_csi_probe,
	.हटाओ	= sun4i_csi_हटाओ,
	.driver	= अणु
		.name		= "sun4i-csi",
		.of_match_table	= sun4i_csi_of_match,
		.pm		= &sun4i_csi_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun4i_csi_driver);

MODULE_DESCRIPTION("Allwinner A10 Camera Sensor Interface driver");
MODULE_AUTHOR("Maxime Ripard <mripard@kernel.org>");
MODULE_LICENSE("GPL");
