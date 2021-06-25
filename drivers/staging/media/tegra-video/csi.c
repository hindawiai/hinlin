<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/device.h>
#समावेश <linux/host1x.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <media/v4l2-fwnode.h>

#समावेश "csi.h"
#समावेश "video.h"

#घोषणा MHZ			1000000

अटल अंतरभूत काष्ठा tegra_csi *
host1x_client_to_csi(काष्ठा host1x_client *client)
अणु
	वापस container_of(client, काष्ठा tegra_csi, client);
पूर्ण

अटल अंतरभूत काष्ठा tegra_csi_channel *to_csi_chan(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा tegra_csi_channel, subdev);
पूर्ण

/*
 * CSI is a separate subdevice which has 6 source pads to generate
 * test pattern. CSI subdevice pad ops are used only क्रम TPG and
 * allows below TPG क्रमmats.
 */
अटल स्थिर काष्ठा v4l2_mbus_framefmt tegra_csi_tpg_fmts[] = अणु
	अणु
		TEGRA_DEF_WIDTH,
		TEGRA_DEF_HEIGHT,
		MEDIA_BUS_FMT_SRGGB10_1X10,
		V4L2_FIELD_NONE,
		V4L2_COLORSPACE_SRGB
	पूर्ण,
	अणु
		TEGRA_DEF_WIDTH,
		TEGRA_DEF_HEIGHT,
		MEDIA_BUS_FMT_RGB888_1X32_PADHI,
		V4L2_FIELD_NONE,
		V4L2_COLORSPACE_SRGB
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_frmsize_discrete tegra_csi_tpg_sizes[] = अणु
	अणु 1280, 720 पूर्ण,
	अणु 1920, 1080 पूर्ण,
	अणु 3840, 2160 पूर्ण,
पूर्ण;

/*
 * V4L2 Subdevice Pad Operations
 */
अटल पूर्णांक csi_क्रमागत_bus_code(काष्ठा v4l2_subdev *subdev,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		वापस -ENOIOCTLCMD;

	अगर (code->index >= ARRAY_SIZE(tegra_csi_tpg_fmts))
		वापस -EINVAL;

	code->code = tegra_csi_tpg_fmts[code->index].code;

	वापस 0;
पूर्ण

अटल पूर्णांक csi_get_क्रमmat(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा tegra_csi_channel *csi_chan = to_csi_chan(subdev);

	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		वापस -ENOIOCTLCMD;

	fmt->क्रमmat = csi_chan->क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक csi_get_frmrate_table_index(काष्ठा tegra_csi *csi, u32 code,
				       u32 width, u32 height)
अणु
	स्थिर काष्ठा tpg_framerate *frmrate;
	अचिन्हित पूर्णांक i;

	frmrate = csi->soc->tpg_frmrate_table;
	क्रम (i = 0; i < csi->soc->tpg_frmrate_table_size; i++) अणु
		अगर (frmrate[i].code == code &&
		    frmrate[i].frmsize.width == width &&
		    frmrate[i].frmsize.height == height) अणु
			वापस i;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम csi_chan_update_blank_पूर्णांकervals(काष्ठा tegra_csi_channel *csi_chan,
					    u32 code, u32 width, u32 height)
अणु
	काष्ठा tegra_csi *csi = csi_chan->csi;
	स्थिर काष्ठा tpg_framerate *frmrate = csi->soc->tpg_frmrate_table;
	पूर्णांक index;

	index = csi_get_frmrate_table_index(csi_chan->csi, code,
					    width, height);
	अगर (index >= 0) अणु
		csi_chan->h_blank = frmrate[index].h_blank;
		csi_chan->v_blank = frmrate[index].v_blank;
		csi_chan->framerate = frmrate[index].framerate;
	पूर्ण
पूर्ण

अटल पूर्णांक csi_क्रमागत_framesizes(काष्ठा v4l2_subdev *subdev,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		वापस -ENOIOCTLCMD;

	अगर (fse->index >= ARRAY_SIZE(tegra_csi_tpg_sizes))
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(tegra_csi_tpg_fmts); i++)
		अगर (fse->code == tegra_csi_tpg_fmts[i].code)
			अवरोध;

	अगर (i == ARRAY_SIZE(tegra_csi_tpg_fmts))
		वापस -EINVAL;

	fse->min_width = tegra_csi_tpg_sizes[fse->index].width;
	fse->max_width = tegra_csi_tpg_sizes[fse->index].width;
	fse->min_height = tegra_csi_tpg_sizes[fse->index].height;
	fse->max_height = tegra_csi_tpg_sizes[fse->index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक csi_क्रमागत_frameपूर्णांकervals(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	काष्ठा tegra_csi_channel *csi_chan = to_csi_chan(subdev);
	काष्ठा tegra_csi *csi = csi_chan->csi;
	स्थिर काष्ठा tpg_framerate *frmrate = csi->soc->tpg_frmrate_table;
	पूर्णांक index;

	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		वापस -ENOIOCTLCMD;

	/* one framerate per क्रमmat and resolution */
	अगर (fie->index > 0)
		वापस -EINVAL;

	index = csi_get_frmrate_table_index(csi_chan->csi, fie->code,
					    fie->width, fie->height);
	अगर (index < 0)
		वापस -EINVAL;

	fie->पूर्णांकerval.numerator = 1;
	fie->पूर्णांकerval.denominator = frmrate[index].framerate;

	वापस 0;
पूर्ण

अटल पूर्णांक csi_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा tegra_csi_channel *csi_chan = to_csi_chan(subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat = &fmt->क्रमmat;
	स्थिर काष्ठा v4l2_frmsize_discrete *sizes;
	अचिन्हित पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		वापस -ENOIOCTLCMD;

	sizes = v4l2_find_nearest_size(tegra_csi_tpg_sizes,
				       ARRAY_SIZE(tegra_csi_tpg_sizes),
				       width, height,
				       क्रमmat->width, क्रमmat->width);
	क्रमmat->width = sizes->width;
	क्रमmat->height = sizes->height;

	क्रम (i = 0; i < ARRAY_SIZE(tegra_csi_tpg_fmts); i++)
		अगर (क्रमmat->code == tegra_csi_tpg_fmts[i].code)
			अवरोध;

	अगर (i == ARRAY_SIZE(tegra_csi_tpg_fmts))
		i = 0;

	क्रमmat->code = tegra_csi_tpg_fmts[i].code;
	क्रमmat->field = V4L2_FIELD_NONE;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		वापस 0;

	/* update blanking पूर्णांकervals from frame rate table and क्रमmat */
	csi_chan_update_blank_पूर्णांकervals(csi_chan, क्रमmat->code,
					क्रमmat->width, क्रमmat->height);
	csi_chan->क्रमmat = *क्रमmat;

	वापस 0;
पूर्ण

/*
 * V4L2 Subdevice Video Operations
 */
अटल पूर्णांक tegra_csi_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				      काष्ठा v4l2_subdev_frame_पूर्णांकerval *vfi)
अणु
	काष्ठा tegra_csi_channel *csi_chan = to_csi_chan(subdev);

	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		वापस -ENOIOCTLCMD;

	vfi->पूर्णांकerval.numerator = 1;
	vfi->पूर्णांकerval.denominator = csi_chan->framerate;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक csi_get_pixel_rate(काष्ठा tegra_csi_channel *csi_chan)
अणु
	काष्ठा tegra_vi_channel *chan;
	काष्ठा v4l2_subdev *src_subdev;
	काष्ठा v4l2_ctrl *ctrl;

	chan = v4l2_get_subdev_hostdata(&csi_chan->subdev);
	src_subdev = tegra_channel_get_remote_source_subdev(chan);
	ctrl = v4l2_ctrl_find(src_subdev->ctrl_handler, V4L2_CID_PIXEL_RATE);
	अगर (ctrl)
		वापस v4l2_ctrl_g_ctrl_पूर्णांक64(ctrl);

	वापस 0;
पूर्ण

व्योम tegra_csi_calc_settle_समय(काष्ठा tegra_csi_channel *csi_chan,
				u8 csi_port_num,
				u8 *clk_settle_समय,
				u8 *ths_settle_समय)
अणु
	काष्ठा tegra_csi *csi = csi_chan->csi;
	अचिन्हित पूर्णांक cil_clk_mhz;
	अचिन्हित पूर्णांक pix_clk_mhz;
	पूर्णांक clk_idx = (csi_port_num >> 1) + 1;

	cil_clk_mhz = clk_get_rate(csi->clks[clk_idx].clk) / MHZ;
	pix_clk_mhz = csi_get_pixel_rate(csi_chan) / MHZ;

	/*
	 * CLK Settle समय is the पूर्णांकerval during which HS receiver should
	 * ignore any घड़ी lane HS transitions, starting from the beginning
	 * of T-CLK-PREPARE.
	 * Per DPHY specअगरication, T-CLK-SETTLE should be between 95ns ~ 300ns
	 *
	 * 95ns < (clk-settle-programmed + 7) * lp clk period < 300ns
	 * midpoपूर्णांक = 197.5 ns
	 */
	*clk_settle_समय = ((95 + 300) * cil_clk_mhz - 14000) / 2000;

	/*
	 * THS Settle समय is the पूर्णांकerval during which HS receiver should
	 * ignore any data lane HS transitions, starting from the beginning
	 * of THS-PREPARE.
	 *
	 * Per DPHY specअगरication, T-HS-SETTLE should be between 85ns + 6UI
	 * and 145ns+10UI.
	 * 85ns + 6UI < (Ths-settle-prog + 5) * lp_clk_period < 145ns + 10UI
	 * midpoपूर्णांक = 115ns + 8UI
	 */
	अगर (pix_clk_mhz)
		*ths_settle_समय = (115 * cil_clk_mhz + 8000 * cil_clk_mhz
				   / (2 * pix_clk_mhz) - 5000) / 1000;
पूर्ण

अटल पूर्णांक tegra_csi_enable_stream(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा tegra_vi_channel *chan = v4l2_get_subdev_hostdata(subdev);
	काष्ठा tegra_csi_channel *csi_chan = to_csi_chan(subdev);
	काष्ठा tegra_csi *csi = csi_chan->csi;
	पूर्णांक ret, err;

	ret = pm_runसमय_get_sync(csi->dev);
	अगर (ret < 0) अणु
		dev_err(csi->dev, "failed to get runtime PM: %d\n", ret);
		pm_runसमय_put_noidle(csi->dev);
		वापस ret;
	पूर्ण

	अगर (csi_chan->mipi) अणु
		ret = tegra_mipi_enable(csi_chan->mipi);
		अगर (ret < 0) अणु
			dev_err(csi->dev,
				"failed to enable MIPI pads: %d\n", ret);
			जाओ rpm_put;
		पूर्ण

		/*
		 * CSI MIPI pads PULLUP, PULLDN and TERM impedances need to
		 * be calibrated after घातer on.
		 * So, trigger the calibration start here and results will
		 * be latched and applied to the pads when link is in LP11
		 * state during start of sensor streaming.
		 */
		ret = tegra_mipi_start_calibration(csi_chan->mipi);
		अगर (ret < 0) अणु
			dev_err(csi->dev,
				"failed to start MIPI calibration: %d\n", ret);
			जाओ disable_mipi;
		पूर्ण
	पूर्ण

	csi_chan->pg_mode = chan->pg_mode;
	ret = csi->ops->csi_start_streaming(csi_chan);
	अगर (ret < 0)
		जाओ finish_calibration;

	वापस 0;

finish_calibration:
	अगर (csi_chan->mipi)
		tegra_mipi_finish_calibration(csi_chan->mipi);
disable_mipi:
	अगर (csi_chan->mipi) अणु
		err = tegra_mipi_disable(csi_chan->mipi);
		अगर (err < 0)
			dev_err(csi->dev,
				"failed to disable MIPI pads: %d\n", err);
	पूर्ण

rpm_put:
	pm_runसमय_put(csi->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_csi_disable_stream(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा tegra_csi_channel *csi_chan = to_csi_chan(subdev);
	काष्ठा tegra_csi *csi = csi_chan->csi;
	पूर्णांक err;

	csi->ops->csi_stop_streaming(csi_chan);

	अगर (csi_chan->mipi) अणु
		err = tegra_mipi_disable(csi_chan->mipi);
		अगर (err < 0)
			dev_err(csi->dev,
				"failed to disable MIPI pads: %d\n", err);
	पूर्ण

	pm_runसमय_put(csi->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_csi_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	पूर्णांक ret;

	अगर (enable)
		ret = tegra_csi_enable_stream(subdev);
	अन्यथा
		ret = tegra_csi_disable_stream(subdev);

	वापस ret;
पूर्ण

/*
 * V4L2 Subdevice Operations
 */
अटल स्थिर काष्ठा v4l2_subdev_video_ops tegra_csi_video_ops = अणु
	.s_stream = tegra_csi_s_stream,
	.g_frame_पूर्णांकerval = tegra_csi_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = tegra_csi_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops tegra_csi_pad_ops = अणु
	.क्रमागत_mbus_code		= csi_क्रमागत_bus_code,
	.क्रमागत_frame_size	= csi_क्रमागत_framesizes,
	.क्रमागत_frame_पूर्णांकerval	= csi_क्रमागत_frameपूर्णांकervals,
	.get_fmt		= csi_get_क्रमmat,
	.set_fmt		= csi_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tegra_csi_ops = अणु
	.video  = &tegra_csi_video_ops,
	.pad    = &tegra_csi_pad_ops,
पूर्ण;

अटल पूर्णांक tegra_csi_channel_alloc(काष्ठा tegra_csi *csi,
				   काष्ठा device_node *node,
				   अचिन्हित पूर्णांक port_num, अचिन्हित पूर्णांक lanes,
				   अचिन्हित पूर्णांक num_pads)
अणु
	काष्ठा tegra_csi_channel *chan;
	पूर्णांक ret = 0, i;

	chan = kzalloc(माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस -ENOMEM;

	list_add_tail(&chan->list, &csi->csi_chans);
	chan->csi = csi;
	/*
	 * Each CSI brick has maximum of 4 lanes.
	 * For lanes more than 4, use multiple of immediate CSI bricks as gang.
	 */
	अगर (lanes <= CSI_LANES_PER_BRICK) अणु
		chan->numlanes = lanes;
		chan->numgangports = 1;
	पूर्ण अन्यथा अणु
		chan->numlanes = CSI_LANES_PER_BRICK;
		chan->numgangports = lanes / CSI_LANES_PER_BRICK;
	पूर्ण

	क्रम (i = 0; i < chan->numgangports; i++)
		chan->csi_port_nums[i] = port_num + i * CSI_PORTS_PER_BRICK;

	chan->of_node = node;
	chan->numpads = num_pads;
	अगर (num_pads & 0x2) अणु
		chan->pads[0].flags = MEDIA_PAD_FL_SINK;
		chan->pads[1].flags = MEDIA_PAD_FL_SOURCE;
	पूर्ण अन्यथा अणु
		chan->pads[0].flags = MEDIA_PAD_FL_SOURCE;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		वापस 0;

	chan->mipi = tegra_mipi_request(csi->dev, node);
	अगर (IS_ERR(chan->mipi)) अणु
		ret = PTR_ERR(chan->mipi);
		dev_err(csi->dev, "failed to get mipi device: %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_csi_tpg_channels_alloc(काष्ठा tegra_csi *csi)
अणु
	काष्ठा device_node *node = csi->dev->of_node;
	अचिन्हित पूर्णांक port_num;
	अचिन्हित पूर्णांक tpg_channels = csi->soc->csi_max_channels;
	पूर्णांक ret;

	/* allocate CSI channel क्रम each CSI x2 ports */
	क्रम (port_num = 0; port_num < tpg_channels; port_num++) अणु
		ret = tegra_csi_channel_alloc(csi, node, port_num, 2, 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_csi_channels_alloc(काष्ठा tegra_csi *csi)
अणु
	काष्ठा device_node *node = csi->dev->of_node;
	काष्ठा v4l2_fwnode_endpoपूर्णांक v4l2_ep = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY
	पूर्ण;
	काष्ठा fwnode_handle *fwh;
	काष्ठा device_node *channel;
	काष्ठा device_node *ep;
	अचिन्हित पूर्णांक lanes, portno, num_pads;
	पूर्णांक ret;

	क्रम_each_child_of_node(node, channel) अणु
		अगर (!of_node_name_eq(channel, "channel"))
			जारी;

		ret = of_property_पढ़ो_u32(channel, "reg", &portno);
		अगर (ret < 0)
			जारी;

		अगर (portno >= csi->soc->csi_max_channels) अणु
			dev_err(csi->dev, "invalid port num %d for %pOF\n",
				portno, channel);
			ret = -EINVAL;
			जाओ err_node_put;
		पूर्ण

		ep = of_graph_get_endpoपूर्णांक_by_regs(channel, 0, 0);
		अगर (!ep)
			जारी;

		fwh = of_fwnode_handle(ep);
		ret = v4l2_fwnode_endpoपूर्णांक_parse(fwh, &v4l2_ep);
		of_node_put(ep);
		अगर (ret) अणु
			dev_err(csi->dev,
				"failed to parse v4l2 endpoint for %pOF: %d\n",
				channel, ret);
			जाओ err_node_put;
		पूर्ण

		lanes = v4l2_ep.bus.mipi_csi2.num_data_lanes;
		/*
		 * Each CSI brick has maximum 4 data lanes.
		 * For lanes more than 4, validate lanes to be multiple of 4
		 * so multiple of consecutive CSI bricks can be ganged up क्रम
		 * streaming.
		 */
		अगर (!lanes || ((lanes & (lanes - 1)) != 0) ||
		    (lanes > CSI_LANES_PER_BRICK && ((portno & 1) != 0))) अणु
			dev_err(csi->dev, "invalid data-lanes %d for %pOF\n",
				lanes, channel);
			ret = -EINVAL;
			जाओ err_node_put;
		पूर्ण

		num_pads = of_graph_get_endpoपूर्णांक_count(channel);
		अगर (num_pads == TEGRA_CSI_PADS_NUM) अणु
			ret = tegra_csi_channel_alloc(csi, channel, portno,
						      lanes, num_pads);
			अगर (ret < 0)
				जाओ err_node_put;
		पूर्ण
	पूर्ण

	वापस 0;

err_node_put:
	of_node_put(channel);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_csi_channel_init(काष्ठा tegra_csi_channel *chan)
अणु
	काष्ठा tegra_csi *csi = chan->csi;
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक ret;

	/* initialize the शेष क्रमmat */
	chan->क्रमmat.code = MEDIA_BUS_FMT_SRGGB10_1X10;
	chan->क्रमmat.field = V4L2_FIELD_NONE;
	chan->क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;
	chan->क्रमmat.width = TEGRA_DEF_WIDTH;
	chan->क्रमmat.height = TEGRA_DEF_HEIGHT;
	csi_chan_update_blank_पूर्णांकervals(chan, chan->क्रमmat.code,
					chan->क्रमmat.width,
					chan->क्रमmat.height);
	/* initialize V4L2 subdevice and media entity */
	subdev = &chan->subdev;
	v4l2_subdev_init(subdev, &tegra_csi_ops);
	subdev->dev = csi->dev;
	अगर (IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		snम_लिखो(subdev->name, V4L2_SUBDEV_NAME_SIZE, "%s-%d", "tpg",
			 chan->csi_port_nums[0]);
	अन्यथा
		snम_लिखो(subdev->name, V4L2_SUBDEV_NAME_SIZE, "%s",
			 kbasename(chan->of_node->full_name));

	v4l2_set_subdevdata(subdev, chan);
	subdev->fwnode = of_fwnode_handle(chan->of_node);
	subdev->entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;

	/* initialize media entity pads */
	ret = media_entity_pads_init(&subdev->entity, chan->numpads,
				     chan->pads);
	अगर (ret < 0) अणु
		dev_err(csi->dev,
			"failed to initialize media entity: %d\n", ret);
		subdev->dev = शून्य;
		वापस ret;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG)) अणु
		ret = v4l2_async_रेजिस्टर_subdev(subdev);
		अगर (ret < 0) अणु
			dev_err(csi->dev,
				"failed to register subdev: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम tegra_csi_error_recover(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tegra_csi_channel *csi_chan = to_csi_chan(sd);
	काष्ठा tegra_csi *csi = csi_chan->csi;

	/* stop streaming during error recovery */
	csi->ops->csi_stop_streaming(csi_chan);
	csi->ops->csi_err_recover(csi_chan);
	csi->ops->csi_start_streaming(csi_chan);
पूर्ण

अटल पूर्णांक tegra_csi_channels_init(काष्ठा tegra_csi *csi)
अणु
	काष्ठा tegra_csi_channel *chan;
	पूर्णांक ret;

	list_क्रम_each_entry(chan, &csi->csi_chans, list) अणु
		ret = tegra_csi_channel_init(chan);
		अगर (ret) अणु
			dev_err(csi->dev,
				"failed to initialize channel-%d: %d\n",
				chan->csi_port_nums[0], ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_csi_channels_cleanup(काष्ठा tegra_csi *csi)
अणु
	काष्ठा v4l2_subdev *subdev;
	काष्ठा tegra_csi_channel *chan, *पंचांगp;

	list_क्रम_each_entry_safe(chan, पंचांगp, &csi->csi_chans, list) अणु
		अगर (chan->mipi)
			tegra_mipi_मुक्त(chan->mipi);

		subdev = &chan->subdev;
		अगर (subdev->dev) अणु
			अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
				v4l2_async_unरेजिस्टर_subdev(subdev);
			media_entity_cleanup(&subdev->entity);
		पूर्ण

		list_del(&chan->list);
		kमुक्त(chan);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused csi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_csi *csi = dev_get_drvdata(dev);

	clk_bulk_disable_unprepare(csi->soc->num_clks, csi->clks);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused csi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_csi *csi = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_bulk_prepare_enable(csi->soc->num_clks, csi->clks);
	अगर (ret < 0) अणु
		dev_err(csi->dev, "failed to enable clocks: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_csi_init(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_csi *csi = host1x_client_to_csi(client);
	काष्ठा tegra_video_device *vid = dev_get_drvdata(client->host);
	पूर्णांक ret;

	INIT_LIST_HEAD(&csi->csi_chans);

	अगर (IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		ret = tegra_csi_tpg_channels_alloc(csi);
	अन्यथा
		ret = tegra_csi_channels_alloc(csi);
	अगर (ret < 0) अणु
		dev_err(csi->dev,
			"failed to allocate channels: %d\n", ret);
		जाओ cleanup;
	पूर्ण

	ret = tegra_csi_channels_init(csi);
	अगर (ret < 0)
		जाओ cleanup;

	vid->csi = csi;

	वापस 0;

cleanup:
	tegra_csi_channels_cleanup(csi);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_csi_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_csi *csi = host1x_client_to_csi(client);

	tegra_csi_channels_cleanup(csi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा host1x_client_ops csi_client_ops = अणु
	.init = tegra_csi_init,
	.निकास = tegra_csi_निकास,
पूर्ण;

अटल पूर्णांक tegra_csi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_csi *csi;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	csi = devm_kzalloc(&pdev->dev, माप(*csi), GFP_KERNEL);
	अगर (!csi)
		वापस -ENOMEM;

	csi->iomem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(csi->iomem))
		वापस PTR_ERR(csi->iomem);

	csi->soc = of_device_get_match_data(&pdev->dev);

	csi->clks = devm_kसुस्मृति(&pdev->dev, csi->soc->num_clks,
				 माप(*csi->clks), GFP_KERNEL);
	अगर (!csi->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < csi->soc->num_clks; i++)
		csi->clks[i].id = csi->soc->clk_names[i];

	ret = devm_clk_bulk_get(&pdev->dev, csi->soc->num_clks, csi->clks);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get the clocks: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!pdev->dev.pm_करोमुख्य) अणु
		ret = -ENOENT;
		dev_warn(&pdev->dev, "PM domain is not attached: %d\n", ret);
		वापस ret;
	पूर्ण

	csi->dev = &pdev->dev;
	csi->ops = csi->soc->ops;
	platक्रमm_set_drvdata(pdev, csi);
	pm_runसमय_enable(&pdev->dev);

	/* initialize host1x पूर्णांकerface */
	INIT_LIST_HEAD(&csi->client.list);
	csi->client.ops = &csi_client_ops;
	csi->client.dev = &pdev->dev;

	ret = host1x_client_रेजिस्टर(&csi->client);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"failed to register host1x client: %d\n", ret);
		जाओ rpm_disable;
	पूर्ण

	वापस 0;

rpm_disable:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_csi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_csi *csi = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = host1x_client_unरेजिस्टर(&csi->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev,
			"failed to unregister host1x client: %d\n", err);
		वापस err;
	पूर्ण

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_csi_of_id_table[] = अणु
#अगर defined(CONFIG_ARCH_TEGRA_210_SOC)
	अणु .compatible = "nvidia,tegra210-csi", .data = &tegra210_csi_soc पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_csi_of_id_table);

अटल स्थिर काष्ठा dev_pm_ops tegra_csi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(csi_runसमय_suspend, csi_runसमय_resume, शून्य)
पूर्ण;

काष्ठा platक्रमm_driver tegra_csi_driver = अणु
	.driver = अणु
		.name		= "tegra-csi",
		.of_match_table	= tegra_csi_of_id_table,
		.pm		= &tegra_csi_pm_ops,
	पूर्ण,
	.probe			= tegra_csi_probe,
	.हटाओ			= tegra_csi_हटाओ,
पूर्ण;
