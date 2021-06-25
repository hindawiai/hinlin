<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Cadence MIPI-CSI2 RX Controller v1.3
 *
 * Copyright (C) 2017 Cadence Design Systems Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा CSI2RX_DEVICE_CFG_REG			0x000

#घोषणा CSI2RX_SOFT_RESET_REG			0x004
#घोषणा CSI2RX_SOFT_RESET_PROTOCOL			BIT(1)
#घोषणा CSI2RX_SOFT_RESET_FRONT				BIT(0)

#घोषणा CSI2RX_STATIC_CFG_REG			0x008
#घोषणा CSI2RX_STATIC_CFG_DLANE_MAP(llane, plane)	((plane) << (16 + (llane) * 4))
#घोषणा CSI2RX_STATIC_CFG_LANES_MASK			GENMASK(11, 8)

#घोषणा CSI2RX_STREAM_BASE(n)		(((n) + 1) * 0x100)

#घोषणा CSI2RX_STREAM_CTRL_REG(n)		(CSI2RX_STREAM_BASE(n) + 0x000)
#घोषणा CSI2RX_STREAM_CTRL_START			BIT(0)

#घोषणा CSI2RX_STREAM_DATA_CFG_REG(n)		(CSI2RX_STREAM_BASE(n) + 0x008)
#घोषणा CSI2RX_STREAM_DATA_CFG_EN_VC_SELECT		BIT(31)
#घोषणा CSI2RX_STREAM_DATA_CFG_VC_SELECT(n)		BIT((n) + 16)

#घोषणा CSI2RX_STREAM_CFG_REG(n)		(CSI2RX_STREAM_BASE(n) + 0x00c)
#घोषणा CSI2RX_STREAM_CFG_FIFO_MODE_LARGE_BUF		(1 << 8)

#घोषणा CSI2RX_LANES_MAX	4
#घोषणा CSI2RX_STREAMS_MAX	4

क्रमागत csi2rx_pads अणु
	CSI2RX_PAD_SINK,
	CSI2RX_PAD_SOURCE_STREAM0,
	CSI2RX_PAD_SOURCE_STREAM1,
	CSI2RX_PAD_SOURCE_STREAM2,
	CSI2RX_PAD_SOURCE_STREAM3,
	CSI2RX_PAD_MAX,
पूर्ण;

काष्ठा csi2rx_priv अणु
	काष्ठा device			*dev;
	अचिन्हित पूर्णांक			count;

	/*
	 * Used to prevent race conditions between multiple,
	 * concurrent calls to start and stop.
	 */
	काष्ठा mutex			lock;

	व्योम __iomem			*base;
	काष्ठा clk			*sys_clk;
	काष्ठा clk			*p_clk;
	काष्ठा clk			*pixel_clk[CSI2RX_STREAMS_MAX];
	काष्ठा phy			*dphy;

	u8				lanes[CSI2RX_LANES_MAX];
	u8				num_lanes;
	u8				max_lanes;
	u8				max_streams;
	bool				has_पूर्णांकernal_dphy;

	काष्ठा v4l2_subdev		subdev;
	काष्ठा v4l2_async_notअगरier	notअगरier;
	काष्ठा media_pad		pads[CSI2RX_PAD_MAX];

	/* Remote source */
	काष्ठा v4l2_subdev		*source_subdev;
	पूर्णांक				source_pad;
पूर्ण;

अटल अंतरभूत
काष्ठा csi2rx_priv *v4l2_subdev_to_csi2rx(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा csi2rx_priv, subdev);
पूर्ण

अटल व्योम csi2rx_reset(काष्ठा csi2rx_priv *csi2rx)
अणु
	ग_लिखोl(CSI2RX_SOFT_RESET_PROTOCOL | CSI2RX_SOFT_RESET_FRONT,
	       csi2rx->base + CSI2RX_SOFT_RESET_REG);

	udelay(10);

	ग_लिखोl(0, csi2rx->base + CSI2RX_SOFT_RESET_REG);
पूर्ण

अटल पूर्णांक csi2rx_start(काष्ठा csi2rx_priv *csi2rx)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ lanes_used = 0;
	u32 reg;
	पूर्णांक ret;

	ret = clk_prepare_enable(csi2rx->p_clk);
	अगर (ret)
		वापस ret;

	csi2rx_reset(csi2rx);

	reg = csi2rx->num_lanes << 8;
	क्रम (i = 0; i < csi2rx->num_lanes; i++) अणु
		reg |= CSI2RX_STATIC_CFG_DLANE_MAP(i, csi2rx->lanes[i]);
		set_bit(csi2rx->lanes[i], &lanes_used);
	पूर्ण

	/*
	 * Even the unused lanes need to be mapped. In order to aव्योम
	 * to map twice to the same physical lane, keep the lanes used
	 * in the previous loop, and only map unused physical lanes to
	 * the rest of our logical lanes.
	 */
	क्रम (i = csi2rx->num_lanes; i < csi2rx->max_lanes; i++) अणु
		अचिन्हित पूर्णांक idx = find_first_zero_bit(&lanes_used,
						       csi2rx->max_lanes);
		set_bit(idx, &lanes_used);
		reg |= CSI2RX_STATIC_CFG_DLANE_MAP(i, i + 1);
	पूर्ण

	ग_लिखोl(reg, csi2rx->base + CSI2RX_STATIC_CFG_REG);

	ret = v4l2_subdev_call(csi2rx->source_subdev, video, s_stream, true);
	अगर (ret)
		जाओ err_disable_pclk;

	/*
	 * Create a अटल mapping between the CSI भव channels
	 * and the output stream.
	 *
	 * This should be enhanced, but v4l2 lacks the support क्रम
	 * changing that mapping dynamically.
	 *
	 * We also cannot enable and disable independent streams here,
	 * hence the reference counting.
	 */
	क्रम (i = 0; i < csi2rx->max_streams; i++) अणु
		ret = clk_prepare_enable(csi2rx->pixel_clk[i]);
		अगर (ret)
			जाओ err_disable_pixclk;

		ग_लिखोl(CSI2RX_STREAM_CFG_FIFO_MODE_LARGE_BUF,
		       csi2rx->base + CSI2RX_STREAM_CFG_REG(i));

		ग_लिखोl(CSI2RX_STREAM_DATA_CFG_EN_VC_SELECT |
		       CSI2RX_STREAM_DATA_CFG_VC_SELECT(i),
		       csi2rx->base + CSI2RX_STREAM_DATA_CFG_REG(i));

		ग_लिखोl(CSI2RX_STREAM_CTRL_START,
		       csi2rx->base + CSI2RX_STREAM_CTRL_REG(i));
	पूर्ण

	ret = clk_prepare_enable(csi2rx->sys_clk);
	अगर (ret)
		जाओ err_disable_pixclk;

	clk_disable_unprepare(csi2rx->p_clk);

	वापस 0;

err_disable_pixclk:
	क्रम (; i > 0; i--)
		clk_disable_unprepare(csi2rx->pixel_clk[i - 1]);

err_disable_pclk:
	clk_disable_unprepare(csi2rx->p_clk);

	वापस ret;
पूर्ण

अटल व्योम csi2rx_stop(काष्ठा csi2rx_priv *csi2rx)
अणु
	अचिन्हित पूर्णांक i;

	clk_prepare_enable(csi2rx->p_clk);
	clk_disable_unprepare(csi2rx->sys_clk);

	क्रम (i = 0; i < csi2rx->max_streams; i++) अणु
		ग_लिखोl(0, csi2rx->base + CSI2RX_STREAM_CTRL_REG(i));

		clk_disable_unprepare(csi2rx->pixel_clk[i]);
	पूर्ण

	clk_disable_unprepare(csi2rx->p_clk);

	अगर (v4l2_subdev_call(csi2rx->source_subdev, video, s_stream, false))
		dev_warn(csi2rx->dev, "Couldn't disable our subdev\n");
पूर्ण

अटल पूर्णांक csi2rx_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा csi2rx_priv *csi2rx = v4l2_subdev_to_csi2rx(subdev);
	पूर्णांक ret = 0;

	mutex_lock(&csi2rx->lock);

	अगर (enable) अणु
		/*
		 * If we're not the first users, there's no need to
		 * enable the whole controller.
		 */
		अगर (!csi2rx->count) अणु
			ret = csi2rx_start(csi2rx);
			अगर (ret)
				जाओ out;
		पूर्ण

		csi2rx->count++;
	पूर्ण अन्यथा अणु
		csi2rx->count--;

		/*
		 * Let the last user turn off the lights.
		 */
		अगर (!csi2rx->count)
			csi2rx_stop(csi2rx);
	पूर्ण

out:
	mutex_unlock(&csi2rx->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops csi2rx_video_ops = अणु
	.s_stream	= csi2rx_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops csi2rx_subdev_ops = अणु
	.video		= &csi2rx_video_ops,
पूर्ण;

अटल पूर्णांक csi2rx_async_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
			      काष्ठा v4l2_subdev *s_subdev,
			      काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा v4l2_subdev *subdev = notअगरier->sd;
	काष्ठा csi2rx_priv *csi2rx = v4l2_subdev_to_csi2rx(subdev);

	csi2rx->source_pad = media_entity_get_fwnode_pad(&s_subdev->entity,
							 s_subdev->fwnode,
							 MEDIA_PAD_FL_SOURCE);
	अगर (csi2rx->source_pad < 0) अणु
		dev_err(csi2rx->dev, "Couldn't find output pad for subdev %s\n",
			s_subdev->name);
		वापस csi2rx->source_pad;
	पूर्ण

	csi2rx->source_subdev = s_subdev;

	dev_dbg(csi2rx->dev, "Bound %s pad: %d\n", s_subdev->name,
		csi2rx->source_pad);

	वापस media_create_pad_link(&csi2rx->source_subdev->entity,
				     csi2rx->source_pad,
				     &csi2rx->subdev.entity, 0,
				     MEDIA_LNK_FL_ENABLED |
				     MEDIA_LNK_FL_IMMUTABLE);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations csi2rx_notअगरier_ops = अणु
	.bound		= csi2rx_async_bound,
पूर्ण;

अटल पूर्णांक csi2rx_get_resources(काष्ठा csi2rx_priv *csi2rx,
				काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	अचिन्हित अक्षर i;
	u32 dev_cfg;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	csi2rx->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(csi2rx->base))
		वापस PTR_ERR(csi2rx->base);

	csi2rx->sys_clk = devm_clk_get(&pdev->dev, "sys_clk");
	अगर (IS_ERR(csi2rx->sys_clk)) अणु
		dev_err(&pdev->dev, "Couldn't get sys clock\n");
		वापस PTR_ERR(csi2rx->sys_clk);
	पूर्ण

	csi2rx->p_clk = devm_clk_get(&pdev->dev, "p_clk");
	अगर (IS_ERR(csi2rx->p_clk)) अणु
		dev_err(&pdev->dev, "Couldn't get P clock\n");
		वापस PTR_ERR(csi2rx->p_clk);
	पूर्ण

	csi2rx->dphy = devm_phy_optional_get(&pdev->dev, "dphy");
	अगर (IS_ERR(csi2rx->dphy)) अणु
		dev_err(&pdev->dev, "Couldn't get external D-PHY\n");
		वापस PTR_ERR(csi2rx->dphy);
	पूर्ण

	/*
	 * FIXME: Once we'll have बाह्यal D-PHY support, the check
	 * will need to be हटाओd.
	 */
	अगर (csi2rx->dphy) अणु
		dev_err(&pdev->dev, "External D-PHY not supported yet\n");
		वापस -EINVAL;
	पूर्ण

	clk_prepare_enable(csi2rx->p_clk);
	dev_cfg = पढ़ोl(csi2rx->base + CSI2RX_DEVICE_CFG_REG);
	clk_disable_unprepare(csi2rx->p_clk);

	csi2rx->max_lanes = dev_cfg & 7;
	अगर (csi2rx->max_lanes > CSI2RX_LANES_MAX) अणु
		dev_err(&pdev->dev, "Invalid number of lanes: %u\n",
			csi2rx->max_lanes);
		वापस -EINVAL;
	पूर्ण

	csi2rx->max_streams = (dev_cfg >> 4) & 7;
	अगर (csi2rx->max_streams > CSI2RX_STREAMS_MAX) अणु
		dev_err(&pdev->dev, "Invalid number of streams: %u\n",
			csi2rx->max_streams);
		वापस -EINVAL;
	पूर्ण

	csi2rx->has_पूर्णांकernal_dphy = dev_cfg & BIT(3) ? true : false;

	/*
	 * FIXME: Once we'll have पूर्णांकernal D-PHY support, the check
	 * will need to be हटाओd.
	 */
	अगर (csi2rx->has_पूर्णांकernal_dphy) अणु
		dev_err(&pdev->dev, "Internal D-PHY not supported yet\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < csi2rx->max_streams; i++) अणु
		अक्षर clk_name[16];

		snम_लिखो(clk_name, माप(clk_name), "pixel_if%u_clk", i);
		csi2rx->pixel_clk[i] = devm_clk_get(&pdev->dev, clk_name);
		अगर (IS_ERR(csi2rx->pixel_clk[i])) अणु
			dev_err(&pdev->dev, "Couldn't get clock %s\n", clk_name);
			वापस PTR_ERR(csi2rx->pixel_clk[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक csi2rx_parse_dt(काष्ठा csi2rx_priv *csi2rx)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक v4l2_ep = अणु .bus_type = 0 पूर्ण;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा fwnode_handle *fwh;
	काष्ठा device_node *ep;
	पूर्णांक ret;

	ep = of_graph_get_endpoपूर्णांक_by_regs(csi2rx->dev->of_node, 0, 0);
	अगर (!ep)
		वापस -EINVAL;

	fwh = of_fwnode_handle(ep);
	ret = v4l2_fwnode_endpoपूर्णांक_parse(fwh, &v4l2_ep);
	अगर (ret) अणु
		dev_err(csi2rx->dev, "Could not parse v4l2 endpoint\n");
		of_node_put(ep);
		वापस ret;
	पूर्ण

	अगर (v4l2_ep.bus_type != V4L2_MBUS_CSI2_DPHY) अणु
		dev_err(csi2rx->dev, "Unsupported media bus type: 0x%x\n",
			v4l2_ep.bus_type);
		of_node_put(ep);
		वापस -EINVAL;
	पूर्ण

	स_नकल(csi2rx->lanes, v4l2_ep.bus.mipi_csi2.data_lanes,
	       माप(csi2rx->lanes));
	csi2rx->num_lanes = v4l2_ep.bus.mipi_csi2.num_data_lanes;
	अगर (csi2rx->num_lanes > csi2rx->max_lanes) अणु
		dev_err(csi2rx->dev, "Unsupported number of data-lanes: %d\n",
			csi2rx->num_lanes);
		of_node_put(ep);
		वापस -EINVAL;
	पूर्ण

	v4l2_async_notअगरier_init(&csi2rx->notअगरier);

	asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(&csi2rx->notअगरier,
							   fwh,
							   काष्ठा v4l2_async_subdev);
	of_node_put(ep);
	अगर (IS_ERR(asd))
		वापस PTR_ERR(asd);

	csi2rx->notअगरier.ops = &csi2rx_notअगरier_ops;

	ret = v4l2_async_subdev_notअगरier_रेजिस्टर(&csi2rx->subdev,
						  &csi2rx->notअगरier);
	अगर (ret)
		v4l2_async_notअगरier_cleanup(&csi2rx->notअगरier);

	वापस ret;
पूर्ण

अटल पूर्णांक csi2rx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा csi2rx_priv *csi2rx;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	csi2rx = kzalloc(माप(*csi2rx), GFP_KERNEL);
	अगर (!csi2rx)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, csi2rx);
	csi2rx->dev = &pdev->dev;
	mutex_init(&csi2rx->lock);

	ret = csi2rx_get_resources(csi2rx, pdev);
	अगर (ret)
		जाओ err_मुक्त_priv;

	ret = csi2rx_parse_dt(csi2rx);
	अगर (ret)
		जाओ err_मुक्त_priv;

	csi2rx->subdev.owner = THIS_MODULE;
	csi2rx->subdev.dev = &pdev->dev;
	v4l2_subdev_init(&csi2rx->subdev, &csi2rx_subdev_ops);
	v4l2_set_subdevdata(&csi2rx->subdev, &pdev->dev);
	snम_लिखो(csi2rx->subdev.name, V4L2_SUBDEV_NAME_SIZE, "%s.%s",
		 KBUILD_MODNAME, dev_name(&pdev->dev));

	/* Create our media pads */
	csi2rx->subdev.entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	csi2rx->pads[CSI2RX_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	क्रम (i = CSI2RX_PAD_SOURCE_STREAM0; i < CSI2RX_PAD_MAX; i++)
		csi2rx->pads[i].flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&csi2rx->subdev.entity, CSI2RX_PAD_MAX,
				     csi2rx->pads);
	अगर (ret)
		जाओ err_cleanup;

	ret = v4l2_async_रेजिस्टर_subdev(&csi2rx->subdev);
	अगर (ret < 0)
		जाओ err_cleanup;

	dev_info(&pdev->dev,
		 "Probed CSI2RX with %u/%u lanes, %u streams, %s D-PHY\n",
		 csi2rx->num_lanes, csi2rx->max_lanes, csi2rx->max_streams,
		 csi2rx->has_पूर्णांकernal_dphy ? "internal" : "no");

	वापस 0;

err_cleanup:
	v4l2_async_notअगरier_cleanup(&csi2rx->notअगरier);
err_मुक्त_priv:
	kमुक्त(csi2rx);
	वापस ret;
पूर्ण

अटल पूर्णांक csi2rx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा csi2rx_priv *csi2rx = platक्रमm_get_drvdata(pdev);

	v4l2_async_unरेजिस्टर_subdev(&csi2rx->subdev);
	kमुक्त(csi2rx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id csi2rx_of_table[] = अणु
	अणु .compatible = "cdns,csi2rx" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, csi2rx_of_table);

अटल काष्ठा platक्रमm_driver csi2rx_driver = अणु
	.probe	= csi2rx_probe,
	.हटाओ	= csi2rx_हटाओ,

	.driver	= अणु
		.name		= "cdns-csi2rx",
		.of_match_table	= csi2rx_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(csi2rx_driver);
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@bootlin.com>");
MODULE_DESCRIPTION("Cadence CSI2-RX controller");
MODULE_LICENSE("GPL");
