<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Cadence MIPI-CSI2 TX Controller
 *
 * Copyright (C) 2017-2019 Cadence Design Systems Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा CSI2TX_DEVICE_CONFIG_REG	0x00
#घोषणा CSI2TX_DEVICE_CONFIG_STREAMS_MASK	GENMASK(6, 4)
#घोषणा CSI2TX_DEVICE_CONFIG_HAS_DPHY		BIT(3)
#घोषणा CSI2TX_DEVICE_CONFIG_LANES_MASK		GENMASK(2, 0)

#घोषणा CSI2TX_CONFIG_REG		0x20
#घोषणा CSI2TX_CONFIG_CFG_REQ			BIT(2)
#घोषणा CSI2TX_CONFIG_SRST_REQ			BIT(1)

#घोषणा CSI2TX_DPHY_CFG_REG		0x28
#घोषणा CSI2TX_DPHY_CFG_CLK_RESET		BIT(16)
#घोषणा CSI2TX_DPHY_CFG_LANE_RESET(n)		BIT((n) + 12)
#घोषणा CSI2TX_DPHY_CFG_MODE_MASK		GENMASK(9, 8)
#घोषणा CSI2TX_DPHY_CFG_MODE_LPDT		(2 << 8)
#घोषणा CSI2TX_DPHY_CFG_MODE_HS			(1 << 8)
#घोषणा CSI2TX_DPHY_CFG_MODE_ULPS		(0 << 8)
#घोषणा CSI2TX_DPHY_CFG_CLK_ENABLE		BIT(4)
#घोषणा CSI2TX_DPHY_CFG_LANE_ENABLE(n)		BIT(n)

#घोषणा CSI2TX_DPHY_CLK_WAKEUP_REG	0x2c
#घोषणा CSI2TX_DPHY_CLK_WAKEUP_ULPS_CYCLES(n)	((n) & 0xffff)

#घोषणा CSI2TX_DT_CFG_REG(n)		(0x80 + (n) * 8)
#घोषणा CSI2TX_DT_CFG_DT(n)			(((n) & 0x3f) << 2)

#घोषणा CSI2TX_DT_FORMAT_REG(n)		(0x84 + (n) * 8)
#घोषणा CSI2TX_DT_FORMAT_BYTES_PER_LINE(n)	(((n) & 0xffff) << 16)
#घोषणा CSI2TX_DT_FORMAT_MAX_LINE_NUM(n)	((n) & 0xffff)

#घोषणा CSI2TX_STREAM_IF_CFG_REG(n)	(0x100 + (n) * 4)
#घोषणा CSI2TX_STREAM_IF_CFG_FILL_LEVEL(n)	((n) & 0x1f)

/* CSI2TX V2 Registers */
#घोषणा CSI2TX_V2_DPHY_CFG_REG			0x28
#घोषणा CSI2TX_V2_DPHY_CFG_RESET		BIT(16)
#घोषणा CSI2TX_V2_DPHY_CFG_CLOCK_MODE		BIT(10)
#घोषणा CSI2TX_V2_DPHY_CFG_MODE_MASK		GENMASK(9, 8)
#घोषणा CSI2TX_V2_DPHY_CFG_MODE_LPDT		(2 << 8)
#घोषणा CSI2TX_V2_DPHY_CFG_MODE_HS		(1 << 8)
#घोषणा CSI2TX_V2_DPHY_CFG_MODE_ULPS		(0 << 8)
#घोषणा CSI2TX_V2_DPHY_CFG_CLK_ENABLE		BIT(4)
#घोषणा CSI2TX_V2_DPHY_CFG_LANE_ENABLE(n)	BIT(n)

#घोषणा CSI2TX_LANES_MAX	4
#घोषणा CSI2TX_STREAMS_MAX	4

क्रमागत csi2tx_pads अणु
	CSI2TX_PAD_SOURCE,
	CSI2TX_PAD_SINK_STREAM0,
	CSI2TX_PAD_SINK_STREAM1,
	CSI2TX_PAD_SINK_STREAM2,
	CSI2TX_PAD_SINK_STREAM3,
	CSI2TX_PAD_MAX,
पूर्ण;

काष्ठा csi2tx_fmt अणु
	u32	mbus;
	u32	dt;
	u32	bpp;
पूर्ण;

काष्ठा csi2tx_priv;

/* CSI2TX Variant Operations */
काष्ठा csi2tx_vops अणु
	व्योम (*dphy_setup)(काष्ठा csi2tx_priv *csi2tx);
पूर्ण;

काष्ठा csi2tx_priv अणु
	काष्ठा device			*dev;
	अचिन्हित पूर्णांक			count;

	/*
	 * Used to prevent race conditions between multiple,
	 * concurrent calls to start and stop.
	 */
	काष्ठा mutex			lock;

	व्योम __iomem			*base;

	काष्ठा csi2tx_vops		*vops;

	काष्ठा clk			*esc_clk;
	काष्ठा clk			*p_clk;
	काष्ठा clk			*pixel_clk[CSI2TX_STREAMS_MAX];

	काष्ठा v4l2_subdev		subdev;
	काष्ठा media_pad		pads[CSI2TX_PAD_MAX];
	काष्ठा v4l2_mbus_framefmt	pad_fmts[CSI2TX_PAD_MAX];

	bool				has_पूर्णांकernal_dphy;
	u8				lanes[CSI2TX_LANES_MAX];
	अचिन्हित पूर्णांक			num_lanes;
	अचिन्हित पूर्णांक			max_lanes;
	अचिन्हित पूर्णांक			max_streams;
पूर्ण;

अटल स्थिर काष्ठा csi2tx_fmt csi2tx_क्रमmats[] = अणु
	अणु
		.mbus	= MEDIA_BUS_FMT_UYVY8_1X16,
		.bpp	= 2,
		.dt	= 0x1e,
	पूर्ण,
	अणु
		.mbus	= MEDIA_BUS_FMT_RGB888_1X24,
		.bpp	= 3,
		.dt	= 0x24,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_mbus_framefmt fmt_शेष = अणु
	.width		= 1280,
	.height		= 720,
	.code		= MEDIA_BUS_FMT_RGB888_1X24,
	.field		= V4L2_FIELD_NONE,
	.colorspace	= V4L2_COLORSPACE_DEFAULT,
पूर्ण;

अटल अंतरभूत
काष्ठा csi2tx_priv *v4l2_subdev_to_csi2tx(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा csi2tx_priv, subdev);
पूर्ण

अटल स्थिर काष्ठा csi2tx_fmt *csi2tx_get_fmt_from_mbus(u32 mbus)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(csi2tx_क्रमmats); i++)
		अगर (csi2tx_क्रमmats[i].mbus == mbus)
			वापस &csi2tx_क्रमmats[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक csi2tx_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index >= ARRAY_SIZE(csi2tx_क्रमmats))
		वापस -EINVAL;

	code->code = csi2tx_क्रमmats[code->index].mbus;

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__csi2tx_get_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा csi2tx_priv *csi2tx = v4l2_subdev_to_csi2tx(subdev);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(subdev, cfg,
						  fmt->pad);

	वापस &csi2tx->pad_fmts[fmt->pad];
पूर्ण

अटल पूर्णांक csi2tx_get_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	स्थिर काष्ठा v4l2_mbus_framefmt *क्रमmat;

	/* Multiplexed pad? */
	अगर (fmt->pad == CSI2TX_PAD_SOURCE)
		वापस -EINVAL;

	क्रमmat = __csi2tx_get_pad_क्रमmat(subdev, cfg, fmt);
	अगर (!क्रमmat)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक csi2tx_set_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	स्थिर काष्ठा v4l2_mbus_framefmt *src_क्रमmat = &fmt->क्रमmat;
	काष्ठा v4l2_mbus_framefmt *dst_क्रमmat;

	/* Multiplexed pad? */
	अगर (fmt->pad == CSI2TX_PAD_SOURCE)
		वापस -EINVAL;

	अगर (!csi2tx_get_fmt_from_mbus(fmt->क्रमmat.code))
		src_क्रमmat = &fmt_शेष;

	dst_क्रमmat = __csi2tx_get_pad_क्रमmat(subdev, cfg, fmt);
	अगर (!dst_क्रमmat)
		वापस -EINVAL;

	*dst_क्रमmat = *src_क्रमmat;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops csi2tx_pad_ops = अणु
	.क्रमागत_mbus_code	= csi2tx_क्रमागत_mbus_code,
	.get_fmt	= csi2tx_get_pad_क्रमmat,
	.set_fmt	= csi2tx_set_pad_क्रमmat,
पूर्ण;

/* Set Wake Up value in the D-PHY */
अटल व्योम csi2tx_dphy_set_wakeup(काष्ठा csi2tx_priv *csi2tx)
अणु
	ग_लिखोl(CSI2TX_DPHY_CLK_WAKEUP_ULPS_CYCLES(32),
	       csi2tx->base + CSI2TX_DPHY_CLK_WAKEUP_REG);
पूर्ण

/*
 * Finishes the D-PHY initialization
 * reg dphy cfg value to be used
 */
अटल व्योम csi2tx_dphy_init_finish(काष्ठा csi2tx_priv *csi2tx, u32 reg)
अणु
	अचिन्हित पूर्णांक i;

	udelay(10);

	/* Enable our (घड़ी and data) lanes */
	reg |= CSI2TX_DPHY_CFG_CLK_ENABLE;
	क्रम (i = 0; i < csi2tx->num_lanes; i++)
		reg |= CSI2TX_DPHY_CFG_LANE_ENABLE(csi2tx->lanes[i] - 1);
	ग_लिखोl(reg, csi2tx->base + CSI2TX_DPHY_CFG_REG);

	udelay(10);

	/* Switch to HS mode */
	reg &= ~CSI2TX_DPHY_CFG_MODE_MASK;
	ग_लिखोl(reg | CSI2TX_DPHY_CFG_MODE_HS,
	       csi2tx->base + CSI2TX_DPHY_CFG_REG);
पूर्ण

/* Configures D-PHY in CSIv1.3 */
अटल व्योम csi2tx_dphy_setup(काष्ठा csi2tx_priv *csi2tx)
अणु
	u32 reg;
	अचिन्हित पूर्णांक i;

	csi2tx_dphy_set_wakeup(csi2tx);

	/* Put our lanes (घड़ी and data) out of reset */
	reg = CSI2TX_DPHY_CFG_CLK_RESET | CSI2TX_DPHY_CFG_MODE_LPDT;
	क्रम (i = 0; i < csi2tx->num_lanes; i++)
		reg |= CSI2TX_DPHY_CFG_LANE_RESET(csi2tx->lanes[i] - 1);
	ग_लिखोl(reg, csi2tx->base + CSI2TX_DPHY_CFG_REG);

	csi2tx_dphy_init_finish(csi2tx, reg);
पूर्ण

/* Configures D-PHY in CSIv2 */
अटल व्योम csi2tx_v2_dphy_setup(काष्ठा csi2tx_priv *csi2tx)
अणु
	u32 reg;

	csi2tx_dphy_set_wakeup(csi2tx);

	/* Put our lanes (घड़ी and data) out of reset */
	reg = CSI2TX_V2_DPHY_CFG_RESET | CSI2TX_V2_DPHY_CFG_MODE_LPDT;
	ग_लिखोl(reg, csi2tx->base + CSI2TX_V2_DPHY_CFG_REG);

	csi2tx_dphy_init_finish(csi2tx, reg);
पूर्ण

अटल व्योम csi2tx_reset(काष्ठा csi2tx_priv *csi2tx)
अणु
	ग_लिखोl(CSI2TX_CONFIG_SRST_REQ, csi2tx->base + CSI2TX_CONFIG_REG);

	udelay(10);
पूर्ण

अटल पूर्णांक csi2tx_start(काष्ठा csi2tx_priv *csi2tx)
अणु
	काष्ठा media_entity *entity = &csi2tx->subdev.entity;
	काष्ठा media_link *link;
	अचिन्हित पूर्णांक i;

	csi2tx_reset(csi2tx);

	ग_लिखोl(CSI2TX_CONFIG_CFG_REQ, csi2tx->base + CSI2TX_CONFIG_REG);

	udelay(10);

	अगर (csi2tx->vops && csi2tx->vops->dphy_setup) अणु
		csi2tx->vops->dphy_setup(csi2tx);
		udelay(10);
	पूर्ण

	/*
	 * Create a अटल mapping between the CSI भव channels
	 * and the input streams.
	 *
	 * This should be enhanced, but v4l2 lacks the support क्रम
	 * changing that mapping dynamically at the moment.
	 *
	 * We're रक्षित from the userspace setting up links at the
	 * same समय by the upper layer having called
	 * media_pipeline_start().
	 */
	list_क्रम_each_entry(link, &entity->links, list) अणु
		काष्ठा v4l2_mbus_framefmt *mfmt;
		स्थिर काष्ठा csi2tx_fmt *fmt;
		अचिन्हित पूर्णांक stream;
		पूर्णांक pad_idx = -1;

		/* Only consider our enabled input pads */
		क्रम (i = CSI2TX_PAD_SINK_STREAM0; i < CSI2TX_PAD_MAX; i++) अणु
			काष्ठा media_pad *pad = &csi2tx->pads[i];

			अगर ((pad == link->sink) &&
			    (link->flags & MEDIA_LNK_FL_ENABLED)) अणु
				pad_idx = i;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (pad_idx < 0)
			जारी;

		mfmt = &csi2tx->pad_fmts[pad_idx];
		fmt = csi2tx_get_fmt_from_mbus(mfmt->code);
		अगर (!fmt)
			जारी;

		stream = pad_idx - CSI2TX_PAD_SINK_STREAM0;

		/*
		 * We use the stream ID there, but it's wrong.
		 *
		 * A stream could very well send a data type that is
		 * not equal to its stream ID. We need to find a
		 * proper way to address it.
		 */
		ग_लिखोl(CSI2TX_DT_CFG_DT(fmt->dt),
		       csi2tx->base + CSI2TX_DT_CFG_REG(stream));

		ग_लिखोl(CSI2TX_DT_FORMAT_BYTES_PER_LINE(mfmt->width * fmt->bpp) |
		       CSI2TX_DT_FORMAT_MAX_LINE_NUM(mfmt->height + 1),
		       csi2tx->base + CSI2TX_DT_FORMAT_REG(stream));

		/*
		 * TODO: This needs to be calculated based on the
		 * output CSI2 घड़ी rate.
		 */
		ग_लिखोl(CSI2TX_STREAM_IF_CFG_FILL_LEVEL(4),
		       csi2tx->base + CSI2TX_STREAM_IF_CFG_REG(stream));
	पूर्ण

	/* Disable the configuration mode */
	ग_लिखोl(0, csi2tx->base + CSI2TX_CONFIG_REG);

	वापस 0;
पूर्ण

अटल व्योम csi2tx_stop(काष्ठा csi2tx_priv *csi2tx)
अणु
	ग_लिखोl(CSI2TX_CONFIG_CFG_REQ | CSI2TX_CONFIG_SRST_REQ,
	       csi2tx->base + CSI2TX_CONFIG_REG);
पूर्ण

अटल पूर्णांक csi2tx_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा csi2tx_priv *csi2tx = v4l2_subdev_to_csi2tx(subdev);
	पूर्णांक ret = 0;

	mutex_lock(&csi2tx->lock);

	अगर (enable) अणु
		/*
		 * If we're not the first users, there's no need to
		 * enable the whole controller.
		 */
		अगर (!csi2tx->count) अणु
			ret = csi2tx_start(csi2tx);
			अगर (ret)
				जाओ out;
		पूर्ण

		csi2tx->count++;
	पूर्ण अन्यथा अणु
		csi2tx->count--;

		/*
		 * Let the last user turn off the lights.
		 */
		अगर (!csi2tx->count)
			csi2tx_stop(csi2tx);
	पूर्ण

out:
	mutex_unlock(&csi2tx->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops csi2tx_video_ops = अणु
	.s_stream	= csi2tx_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops csi2tx_subdev_ops = अणु
	.pad		= &csi2tx_pad_ops,
	.video		= &csi2tx_video_ops,
पूर्ण;

अटल पूर्णांक csi2tx_get_resources(काष्ठा csi2tx_priv *csi2tx,
				काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	u32 dev_cfg;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	csi2tx->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(csi2tx->base))
		वापस PTR_ERR(csi2tx->base);

	csi2tx->p_clk = devm_clk_get(&pdev->dev, "p_clk");
	अगर (IS_ERR(csi2tx->p_clk)) अणु
		dev_err(&pdev->dev, "Couldn't get p_clk\n");
		वापस PTR_ERR(csi2tx->p_clk);
	पूर्ण

	csi2tx->esc_clk = devm_clk_get(&pdev->dev, "esc_clk");
	अगर (IS_ERR(csi2tx->esc_clk)) अणु
		dev_err(&pdev->dev, "Couldn't get the esc_clk\n");
		वापस PTR_ERR(csi2tx->esc_clk);
	पूर्ण

	clk_prepare_enable(csi2tx->p_clk);
	dev_cfg = पढ़ोl(csi2tx->base + CSI2TX_DEVICE_CONFIG_REG);
	clk_disable_unprepare(csi2tx->p_clk);

	csi2tx->max_lanes = dev_cfg & CSI2TX_DEVICE_CONFIG_LANES_MASK;
	अगर (csi2tx->max_lanes > CSI2TX_LANES_MAX) अणु
		dev_err(&pdev->dev, "Invalid number of lanes: %u\n",
			csi2tx->max_lanes);
		वापस -EINVAL;
	पूर्ण

	csi2tx->max_streams = (dev_cfg & CSI2TX_DEVICE_CONFIG_STREAMS_MASK) >> 4;
	अगर (csi2tx->max_streams > CSI2TX_STREAMS_MAX) अणु
		dev_err(&pdev->dev, "Invalid number of streams: %u\n",
			csi2tx->max_streams);
		वापस -EINVAL;
	पूर्ण

	csi2tx->has_पूर्णांकernal_dphy = !!(dev_cfg & CSI2TX_DEVICE_CONFIG_HAS_DPHY);

	क्रम (i = 0; i < csi2tx->max_streams; i++) अणु
		अक्षर clk_name[16];

		snम_लिखो(clk_name, माप(clk_name), "pixel_if%u_clk", i);
		csi2tx->pixel_clk[i] = devm_clk_get(&pdev->dev, clk_name);
		अगर (IS_ERR(csi2tx->pixel_clk[i])) अणु
			dev_err(&pdev->dev, "Couldn't get clock %s\n",
				clk_name);
			वापस PTR_ERR(csi2tx->pixel_clk[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक csi2tx_check_lanes(काष्ठा csi2tx_priv *csi2tx)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक v4l2_ep = अणु .bus_type = 0 पूर्ण;
	काष्ठा device_node *ep;
	पूर्णांक ret, i;

	ep = of_graph_get_endpoपूर्णांक_by_regs(csi2tx->dev->of_node, 0, 0);
	अगर (!ep)
		वापस -EINVAL;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep), &v4l2_ep);
	अगर (ret) अणु
		dev_err(csi2tx->dev, "Could not parse v4l2 endpoint\n");
		जाओ out;
	पूर्ण

	अगर (v4l2_ep.bus_type != V4L2_MBUS_CSI2_DPHY) अणु
		dev_err(csi2tx->dev, "Unsupported media bus type: 0x%x\n",
			v4l2_ep.bus_type);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	csi2tx->num_lanes = v4l2_ep.bus.mipi_csi2.num_data_lanes;
	अगर (csi2tx->num_lanes > csi2tx->max_lanes) अणु
		dev_err(csi2tx->dev,
			"Current configuration uses more lanes than supported\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < csi2tx->num_lanes; i++) अणु
		अगर (v4l2_ep.bus.mipi_csi2.data_lanes[i] < 1) अणु
			dev_err(csi2tx->dev, "Invalid lane[%d] number: %u\n",
				i, v4l2_ep.bus.mipi_csi2.data_lanes[i]);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	स_नकल(csi2tx->lanes, v4l2_ep.bus.mipi_csi2.data_lanes,
	       माप(csi2tx->lanes));

out:
	of_node_put(ep);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा csi2tx_vops csi2tx_vops = अणु
	.dphy_setup = csi2tx_dphy_setup,
पूर्ण;

अटल स्थिर काष्ठा csi2tx_vops csi2tx_v2_vops = अणु
	.dphy_setup = csi2tx_v2_dphy_setup,
पूर्ण;

अटल स्थिर काष्ठा of_device_id csi2tx_of_table[] = अणु
	अणु
		.compatible = "cdns,csi2tx",
		.data = &csi2tx_vops
	पूर्ण,
	अणु
		.compatible = "cdns,csi2tx-1.3",
		.data = &csi2tx_vops
	पूर्ण,
	अणु
		.compatible = "cdns,csi2tx-2.1",
		.data = &csi2tx_v2_vops
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, csi2tx_of_table);

अटल पूर्णांक csi2tx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा csi2tx_priv *csi2tx;
	स्थिर काष्ठा of_device_id *of_id;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	csi2tx = kzalloc(माप(*csi2tx), GFP_KERNEL);
	अगर (!csi2tx)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, csi2tx);
	mutex_init(&csi2tx->lock);
	csi2tx->dev = &pdev->dev;

	ret = csi2tx_get_resources(csi2tx, pdev);
	अगर (ret)
		जाओ err_मुक्त_priv;

	of_id = of_match_node(csi2tx_of_table, pdev->dev.of_node);
	csi2tx->vops = (काष्ठा csi2tx_vops *)of_id->data;

	v4l2_subdev_init(&csi2tx->subdev, &csi2tx_subdev_ops);
	csi2tx->subdev.owner = THIS_MODULE;
	csi2tx->subdev.dev = &pdev->dev;
	csi2tx->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	snम_लिखो(csi2tx->subdev.name, V4L2_SUBDEV_NAME_SIZE, "%s.%s",
		 KBUILD_MODNAME, dev_name(&pdev->dev));

	ret = csi2tx_check_lanes(csi2tx);
	अगर (ret)
		जाओ err_मुक्त_priv;

	/* Create our media pads */
	csi2tx->subdev.entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	csi2tx->pads[CSI2TX_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	क्रम (i = CSI2TX_PAD_SINK_STREAM0; i < CSI2TX_PAD_MAX; i++)
		csi2tx->pads[i].flags = MEDIA_PAD_FL_SINK;

	/*
	 * Only the input pads are considered to have a क्रमmat at the
	 * moment. The CSI link can multiplex various streams with
	 * dअगरferent क्रमmats, and we can't expose this in v4l2 right
	 * now.
	 */
	क्रम (i = CSI2TX_PAD_SINK_STREAM0; i < CSI2TX_PAD_MAX; i++)
		csi2tx->pad_fmts[i] = fmt_शेष;

	ret = media_entity_pads_init(&csi2tx->subdev.entity, CSI2TX_PAD_MAX,
				     csi2tx->pads);
	अगर (ret)
		जाओ err_मुक्त_priv;

	ret = v4l2_async_रेजिस्टर_subdev(&csi2tx->subdev);
	अगर (ret < 0)
		जाओ err_मुक्त_priv;

	dev_info(&pdev->dev,
		 "Probed CSI2TX with %u/%u lanes, %u streams, %s D-PHY\n",
		 csi2tx->num_lanes, csi2tx->max_lanes, csi2tx->max_streams,
		 csi2tx->has_पूर्णांकernal_dphy ? "internal" : "no");

	वापस 0;

err_मुक्त_priv:
	kमुक्त(csi2tx);
	वापस ret;
पूर्ण

अटल पूर्णांक csi2tx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा csi2tx_priv *csi2tx = platक्रमm_get_drvdata(pdev);

	v4l2_async_unरेजिस्टर_subdev(&csi2tx->subdev);
	kमुक्त(csi2tx);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver csi2tx_driver = अणु
	.probe	= csi2tx_probe,
	.हटाओ	= csi2tx_हटाओ,

	.driver	= अणु
		.name		= "cdns-csi2tx",
		.of_match_table	= csi2tx_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(csi2tx_driver);
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@bootlin.com>");
MODULE_DESCRIPTION("Cadence CSI2-TX controller");
MODULE_LICENSE("GPL");
