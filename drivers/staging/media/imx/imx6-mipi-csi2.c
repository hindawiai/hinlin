<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * MIPI CSI-2 Receiver Subdev क्रम Freescale i.MX6 SOC.
 *
 * Copyright (c) 2012-2017 Mentor Graphics Inc.
 */
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>
#समावेश "imx-media.h"

/*
 * there must be 5 pads: 1 input pad from sensor, and
 * the 4 भव channel output pads
 */
#घोषणा CSI2_SINK_PAD       0
#घोषणा CSI2_NUM_SINK_PADS  1
#घोषणा CSI2_NUM_SRC_PADS   4
#घोषणा CSI2_NUM_PADS       5

/*
 * The शेष maximum bit-rate per lane in Mbps, अगर the
 * source subdev करोes not provide V4L2_CID_LINK_FREQ.
 */
#घोषणा CSI2_DEFAULT_MAX_MBPS 849

काष्ठा csi2_dev अणु
	काष्ठा device          *dev;
	काष्ठा v4l2_subdev      sd;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा media_pad       pad[CSI2_NUM_PADS];
	काष्ठा clk             *dphy_clk;
	काष्ठा clk             *pllref_clk;
	काष्ठा clk             *pix_clk; /* what is this? */
	व्योम __iomem           *base;

	काष्ठा v4l2_subdev	*remote;
	अचिन्हित पूर्णांक		remote_pad;
	अचिन्हित लघु		data_lanes;

	/* lock to protect all members below */
	काष्ठा mutex lock;

	काष्ठा v4l2_mbus_framefmt क्रमmat_mbus;

	पूर्णांक                     stream_count;
	काष्ठा v4l2_subdev      *src_sd;
	bool                    sink_linked[CSI2_NUM_SRC_PADS];
पूर्ण;

#घोषणा DEVICE_NAME "imx6-mipi-csi2"

/* Register offsets */
#घोषणा CSI2_VERSION            0x000
#घोषणा CSI2_N_LANES            0x004
#घोषणा CSI2_PHY_SHUTDOWNZ      0x008
#घोषणा CSI2_DPHY_RSTZ          0x00c
#घोषणा CSI2_RESETN             0x010
#घोषणा CSI2_PHY_STATE          0x014
#घोषणा PHY_STOPSTATEDATA_BIT   4
#घोषणा PHY_STOPSTATEDATA(n)    BIT(PHY_STOPSTATEDATA_BIT + (n))
#घोषणा PHY_RXCLKACTIVEHS       BIT(8)
#घोषणा PHY_RXULPSCLKNOT        BIT(9)
#घोषणा PHY_STOPSTATECLK        BIT(10)
#घोषणा CSI2_DATA_IDS_1         0x018
#घोषणा CSI2_DATA_IDS_2         0x01c
#घोषणा CSI2_ERR1               0x020
#घोषणा CSI2_ERR2               0x024
#घोषणा CSI2_MSK1               0x028
#घोषणा CSI2_MSK2               0x02c
#घोषणा CSI2_PHY_TST_CTRL0      0x030
#घोषणा PHY_TESTCLR		BIT(0)
#घोषणा PHY_TESTCLK		BIT(1)
#घोषणा CSI2_PHY_TST_CTRL1      0x034
#घोषणा PHY_TESTEN		BIT(16)
/*
 * i.MX CSI2IPU Gasket रेजिस्टरs follow. The CSI2IPU gasket is
 * not part of the MIPI CSI-2 core, but its रेजिस्टरs fall in the
 * same रेजिस्टर map range.
 */
#घोषणा CSI2IPU_GASKET		0xf00
#घोषणा CSI2IPU_YUV422_YUYV	BIT(2)

अटल अंतरभूत काष्ठा csi2_dev *sd_to_dev(काष्ठा v4l2_subdev *sdev)
अणु
	वापस container_of(sdev, काष्ठा csi2_dev, sd);
पूर्ण

अटल अंतरभूत काष्ठा csi2_dev *notअगरier_to_dev(काष्ठा v4l2_async_notअगरier *n)
अणु
	वापस container_of(n, काष्ठा csi2_dev, notअगरier);
पूर्ण

/*
 * The required sequence of MIPI CSI-2 startup as specअगरied in the i.MX6
 * reference manual is as follows:
 *
 * 1. Deनिश्चित presetn संकेत (global reset).
 *        It's not clear what this "global reset" संकेत is (maybe APB
 *        global reset), but in any हाल this step would be probably
 *        be carried out during driver load in csi2_probe().
 *
 * 2. Configure MIPI Camera Sensor to put all Tx lanes in LP-11 state.
 *        This must be carried out by the MIPI sensor's s_घातer(ON) subdev
 *        op.
 *
 * 3. D-PHY initialization.
 * 4. CSI2 Controller programming (Set N_LANES, deनिश्चित PHY_SHUTDOWNZ,
 *    deनिश्चित PHY_RSTZ, deनिश्चित CSI2_RESETN).
 * 5. Read the PHY status रेजिस्टर (PHY_STATE) to confirm that all data and
 *    घड़ी lanes of the D-PHY are in LP-11 state.
 * 6. Configure the MIPI Camera Sensor to start transmitting a घड़ी on the
 *    D-PHY घड़ी lane.
 * 7. CSI2 Controller programming - Read the PHY status रेजिस्टर (PHY_STATE)
 *    to confirm that the D-PHY is receiving a घड़ी on the D-PHY घड़ी lane.
 *
 * All steps 3 through 7 are carried out by csi2_s_stream(ON) here. Step
 * 6 is accomplished by calling the source subdev's s_stream(ON) between
 * steps 5 and 7.
 */

अटल व्योम csi2_enable(काष्ठा csi2_dev *csi2, bool enable)
अणु
	अगर (enable) अणु
		ग_लिखोl(0x1, csi2->base + CSI2_PHY_SHUTDOWNZ);
		ग_लिखोl(0x1, csi2->base + CSI2_DPHY_RSTZ);
		ग_लिखोl(0x1, csi2->base + CSI2_RESETN);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0x0, csi2->base + CSI2_PHY_SHUTDOWNZ);
		ग_लिखोl(0x0, csi2->base + CSI2_DPHY_RSTZ);
		ग_लिखोl(0x0, csi2->base + CSI2_RESETN);
	पूर्ण
पूर्ण

अटल व्योम csi2_set_lanes(काष्ठा csi2_dev *csi2, अचिन्हित पूर्णांक lanes)
अणु
	ग_लिखोl(lanes - 1, csi2->base + CSI2_N_LANES);
पूर्ण

अटल व्योम dw_mipi_csi2_phy_ग_लिखो(काष्ठा csi2_dev *csi2,
				   u32 test_code, u32 test_data)
अणु
	/* Clear PHY test पूर्णांकerface */
	ग_लिखोl(PHY_TESTCLR, csi2->base + CSI2_PHY_TST_CTRL0);
	ग_लिखोl(0x0, csi2->base + CSI2_PHY_TST_CTRL1);
	ग_लिखोl(0x0, csi2->base + CSI2_PHY_TST_CTRL0);

	/* Raise test पूर्णांकerface strobe संकेत */
	ग_लिखोl(PHY_TESTCLK, csi2->base + CSI2_PHY_TST_CTRL0);

	/* Configure address ग_लिखो on falling edge and lower strobe संकेत */
	ग_लिखोl(PHY_TESTEN | test_code, csi2->base + CSI2_PHY_TST_CTRL1);
	ग_लिखोl(0x0, csi2->base + CSI2_PHY_TST_CTRL0);

	/* Configure data ग_लिखो on rising edge and उठाओ strobe संकेत */
	ग_लिखोl(test_data, csi2->base + CSI2_PHY_TST_CTRL1);
	ग_लिखोl(PHY_TESTCLK, csi2->base + CSI2_PHY_TST_CTRL0);

	/* Clear strobe संकेत */
	ग_लिखोl(0x0, csi2->base + CSI2_PHY_TST_CTRL0);
पूर्ण

/*
 * This table is based on the table करोcumented at
 * https://community.nxp.com/करोcs/DOC-94312. It assumes
 * a 27MHz D-PHY pll reference घड़ी.
 */
अटल स्थिर काष्ठा अणु
	u32 max_mbps;
	u32 hsfreqrange_sel;
पूर्ण hsfreq_map[] = अणु
	अणु 90, 0x00पूर्ण, अणु100, 0x20पूर्ण, अणु110, 0x40पूर्ण, अणु125, 0x02पूर्ण,
	अणु140, 0x22पूर्ण, अणु150, 0x42पूर्ण, अणु160, 0x04पूर्ण, अणु180, 0x24पूर्ण,
	अणु200, 0x44पूर्ण, अणु210, 0x06पूर्ण, अणु240, 0x26पूर्ण, अणु250, 0x46पूर्ण,
	अणु270, 0x08पूर्ण, अणु300, 0x28पूर्ण, अणु330, 0x48पूर्ण, अणु360, 0x2aपूर्ण,
	अणु400, 0x4aपूर्ण, अणु450, 0x0cपूर्ण, अणु500, 0x2cपूर्ण, अणु550, 0x0eपूर्ण,
	अणु600, 0x2eपूर्ण, अणु650, 0x10पूर्ण, अणु700, 0x30पूर्ण, अणु750, 0x12पूर्ण,
	अणु800, 0x32पूर्ण, अणु850, 0x14पूर्ण, अणु900, 0x34पूर्ण, अणु950, 0x54पूर्ण,
	अणु1000, 0x74पूर्ण,
पूर्ण;

अटल पूर्णांक max_mbps_to_hsfreqrange_sel(u32 max_mbps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hsfreq_map); i++)
		अगर (hsfreq_map[i].max_mbps > max_mbps)
			वापस hsfreq_map[i].hsfreqrange_sel;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक csi2_dphy_init(काष्ठा csi2_dev *csi2)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	u32 mbps_per_lane;
	पूर्णांक sel;

	ctrl = v4l2_ctrl_find(csi2->src_sd->ctrl_handler,
			      V4L2_CID_LINK_FREQ);
	अगर (!ctrl)
		mbps_per_lane = CSI2_DEFAULT_MAX_MBPS;
	अन्यथा
		mbps_per_lane = DIV_ROUND_UP_ULL(2 * ctrl->qmenu_पूर्णांक[ctrl->val],
						 USEC_PER_SEC);

	sel = max_mbps_to_hsfreqrange_sel(mbps_per_lane);
	अगर (sel < 0)
		वापस sel;

	dw_mipi_csi2_phy_ग_लिखो(csi2, 0x44, sel);

	वापस 0;
पूर्ण

/*
 * Waits क्रम ultra-low-घातer state on D-PHY घड़ी lane. This is currently
 * unused and may not be needed at all, but keep around just in हाल.
 */
अटल पूर्णांक __maybe_unused csi2_dphy_रुको_ulp(काष्ठा csi2_dev *csi2)
अणु
	u32 reg;
	पूर्णांक ret;

	/* रुको क्रम ULP on घड़ी lane */
	ret = पढ़ोl_poll_समयout(csi2->base + CSI2_PHY_STATE, reg,
				 !(reg & PHY_RXULPSCLKNOT), 0, 500000);
	अगर (ret) अणु
		v4l2_err(&csi2->sd, "ULP timeout, phy_state = 0x%08x\n", reg);
		वापस ret;
	पूर्ण

	/* रुको until no errors on bus */
	ret = पढ़ोl_poll_समयout(csi2->base + CSI2_ERR1, reg,
				 reg == 0x0, 0, 500000);
	अगर (ret) अणु
		v4l2_err(&csi2->sd, "stable bus timeout, err1 = 0x%08x\n", reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Waits क्रम low-घातer LP-11 state on data and घड़ी lanes. */
अटल व्योम csi2_dphy_रुको_stopstate(काष्ठा csi2_dev *csi2, अचिन्हित पूर्णांक lanes)
अणु
	u32 mask, reg;
	पूर्णांक ret;

	mask = PHY_STOPSTATECLK | (((1 << lanes) - 1) << PHY_STOPSTATEDATA_BIT);

	ret = पढ़ोl_poll_समयout(csi2->base + CSI2_PHY_STATE, reg,
				 (reg & mask) == mask, 0, 500000);
	अगर (ret) अणु
		v4l2_warn(&csi2->sd, "LP-11 wait timeout, likely a sensor driver bug, expect capture failures.\n");
		v4l2_warn(&csi2->sd, "phy_state = 0x%08x\n", reg);
	पूर्ण
पूर्ण

/* Wait क्रम active घड़ी on the घड़ी lane. */
अटल पूर्णांक csi2_dphy_रुको_घड़ी_lane(काष्ठा csi2_dev *csi2)
अणु
	u32 reg;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout(csi2->base + CSI2_PHY_STATE, reg,
				 (reg & PHY_RXCLKACTIVEHS), 0, 500000);
	अगर (ret) अणु
		v4l2_err(&csi2->sd, "clock lane timeout, phy_state = 0x%08x\n",
			 reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Setup the i.MX CSI2IPU Gasket */
अटल व्योम csi2ipu_gasket_init(काष्ठा csi2_dev *csi2)
अणु
	u32 reg = 0;

	चयन (csi2->क्रमmat_mbus.code) अणु
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
		reg = CSI2IPU_YUV422_YUYV;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ग_लिखोl(reg, csi2->base + CSI2IPU_GASKET);
पूर्ण

अटल पूर्णांक csi2_get_active_lanes(काष्ठा csi2_dev *csi2, अचिन्हित पूर्णांक *lanes)
अणु
	काष्ठा v4l2_mbus_config mbus_config = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक num_lanes = अच_पूर्णांक_उच्च;
	पूर्णांक ret;

	*lanes = csi2->data_lanes;

	ret = v4l2_subdev_call(csi2->remote, pad, get_mbus_config,
			       csi2->remote_pad, &mbus_config);
	अगर (ret == -ENOIOCTLCMD) अणु
		dev_dbg(csi2->dev, "No remote mbus configuration available\n");
		वापस 0;
	पूर्ण

	अगर (ret) अणु
		dev_err(csi2->dev, "Failed to get remote mbus configuration\n");
		वापस ret;
	पूर्ण

	अगर (mbus_config.type != V4L2_MBUS_CSI2_DPHY) अणु
		dev_err(csi2->dev, "Unsupported media bus type %u\n",
			mbus_config.type);
		वापस -EINVAL;
	पूर्ण

	चयन (mbus_config.flags & V4L2_MBUS_CSI2_LANES) अणु
	हाल V4L2_MBUS_CSI2_1_LANE:
		num_lanes = 1;
		अवरोध;
	हाल V4L2_MBUS_CSI2_2_LANE:
		num_lanes = 2;
		अवरोध;
	हाल V4L2_MBUS_CSI2_3_LANE:
		num_lanes = 3;
		अवरोध;
	हाल V4L2_MBUS_CSI2_4_LANE:
		num_lanes = 4;
		अवरोध;
	शेष:
		num_lanes = csi2->data_lanes;
		अवरोध;
	पूर्ण

	अगर (num_lanes > csi2->data_lanes) अणु
		dev_err(csi2->dev,
			"Unsupported mbus config: too many data lanes %u\n",
			num_lanes);
		वापस -EINVAL;
	पूर्ण

	*lanes = num_lanes;

	वापस 0;
पूर्ण

अटल पूर्णांक csi2_start(काष्ठा csi2_dev *csi2)
अणु
	अचिन्हित पूर्णांक lanes;
	पूर्णांक ret;

	ret = clk_prepare_enable(csi2->pix_clk);
	अगर (ret)
		वापस ret;

	/* setup the gasket */
	csi2ipu_gasket_init(csi2);

	/* Step 3 */
	ret = csi2_dphy_init(csi2);
	अगर (ret)
		जाओ err_disable_clk;

	ret = csi2_get_active_lanes(csi2, &lanes);
	अगर (ret)
		जाओ err_disable_clk;

	/* Step 4 */
	csi2_set_lanes(csi2, lanes);
	csi2_enable(csi2, true);

	/* Step 5 */
	csi2_dphy_रुको_stopstate(csi2, lanes);

	/* Step 6 */
	ret = v4l2_subdev_call(csi2->src_sd, video, s_stream, 1);
	ret = (ret && ret != -ENOIOCTLCMD) ? ret : 0;
	अगर (ret)
		जाओ err_निश्चित_reset;

	/* Step 7 */
	ret = csi2_dphy_रुको_घड़ी_lane(csi2);
	अगर (ret)
		जाओ err_stop_upstream;

	वापस 0;

err_stop_upstream:
	v4l2_subdev_call(csi2->src_sd, video, s_stream, 0);
err_निश्चित_reset:
	csi2_enable(csi2, false);
err_disable_clk:
	clk_disable_unprepare(csi2->pix_clk);
	वापस ret;
पूर्ण

अटल व्योम csi2_stop(काष्ठा csi2_dev *csi2)
अणु
	/* stop upstream */
	v4l2_subdev_call(csi2->src_sd, video, s_stream, 0);

	csi2_enable(csi2, false);
	clk_disable_unprepare(csi2->pix_clk);
पूर्ण

/*
 * V4L2 subdev operations.
 */

अटल पूर्णांक csi2_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा csi2_dev *csi2 = sd_to_dev(sd);
	पूर्णांक i, ret = 0;

	mutex_lock(&csi2->lock);

	अगर (!csi2->src_sd) अणु
		ret = -EPIPE;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < CSI2_NUM_SRC_PADS; i++) अणु
		अगर (csi2->sink_linked[i])
			अवरोध;
	पूर्ण
	अगर (i >= CSI2_NUM_SRC_PADS) अणु
		ret = -EPIPE;
		जाओ out;
	पूर्ण

	/*
	 * enable/disable streaming only अगर stream_count is
	 * going from 0 to 1 / 1 to 0.
	 */
	अगर (csi2->stream_count != !enable)
		जाओ update_count;

	dev_dbg(csi2->dev, "stream %s\n", enable ? "ON" : "OFF");
	अगर (enable)
		ret = csi2_start(csi2);
	अन्यथा
		csi2_stop(csi2);
	अगर (ret)
		जाओ out;

update_count:
	csi2->stream_count += enable ? 1 : -1;
	अगर (csi2->stream_count < 0)
		csi2->stream_count = 0;
out:
	mutex_unlock(&csi2->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi2_link_setup(काष्ठा media_entity *entity,
			   स्थिर काष्ठा media_pad *local,
			   स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा csi2_dev *csi2 = sd_to_dev(sd);
	काष्ठा v4l2_subdev *remote_sd;
	पूर्णांक ret = 0;

	dev_dbg(csi2->dev, "link setup %s -> %s", remote->entity->name,
		local->entity->name);

	remote_sd = media_entity_to_v4l2_subdev(remote->entity);

	mutex_lock(&csi2->lock);

	अगर (local->flags & MEDIA_PAD_FL_SOURCE) अणु
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (csi2->sink_linked[local->index - 1]) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			csi2->sink_linked[local->index - 1] = true;
		पूर्ण अन्यथा अणु
			csi2->sink_linked[local->index - 1] = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (csi2->src_sd) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			csi2->src_sd = remote_sd;
		पूर्ण अन्यथा अणु
			csi2->src_sd = शून्य;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&csi2->lock);
	वापस ret;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__csi2_get_fmt(काष्ठा csi2_dev *csi2, काष्ठा v4l2_subdev_pad_config *cfg,
	       अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&csi2->sd, cfg, pad);
	अन्यथा
		वापस &csi2->क्रमmat_mbus;
पूर्ण

अटल पूर्णांक csi2_get_fmt(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा csi2_dev *csi2 = sd_to_dev(sd);
	काष्ठा v4l2_mbus_framefmt *fmt;

	mutex_lock(&csi2->lock);

	fmt = __csi2_get_fmt(csi2, cfg, sdक्रमmat->pad, sdक्रमmat->which);

	sdक्रमmat->क्रमmat = *fmt;

	mutex_unlock(&csi2->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक csi2_set_fmt(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा csi2_dev *csi2 = sd_to_dev(sd);
	काष्ठा v4l2_mbus_framefmt *fmt;
	पूर्णांक ret = 0;

	अगर (sdक्रमmat->pad >= CSI2_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&csi2->lock);

	अगर (csi2->stream_count > 0) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* Output pads mirror active input pad, no limits on input pads */
	अगर (sdक्रमmat->pad != CSI2_SINK_PAD)
		sdक्रमmat->क्रमmat = csi2->क्रमmat_mbus;

	fmt = __csi2_get_fmt(csi2, cfg, sdक्रमmat->pad, sdक्रमmat->which);

	*fmt = sdक्रमmat->क्रमmat;
out:
	mutex_unlock(&csi2->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi2_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा csi2_dev *csi2 = sd_to_dev(sd);

	/* set a शेष mbus क्रमmat  */
	वापस imx_media_init_mbus_fmt(&csi2->क्रमmat_mbus,
				      IMX_MEDIA_DEF_PIX_WIDTH,
				      IMX_MEDIA_DEF_PIX_HEIGHT, 0,
				      V4L2_FIELD_NONE, शून्य);
पूर्ण

अटल स्थिर काष्ठा media_entity_operations csi2_entity_ops = अणु
	.link_setup = csi2_link_setup,
	.link_validate = v4l2_subdev_link_validate,
	.get_fwnode_pad = v4l2_subdev_get_fwnode_pad_1_to_1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops csi2_video_ops = अणु
	.s_stream = csi2_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops csi2_pad_ops = अणु
	.init_cfg = imx_media_init_cfg,
	.get_fmt = csi2_get_fmt,
	.set_fmt = csi2_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops csi2_subdev_ops = अणु
	.video = &csi2_video_ops,
	.pad = &csi2_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops csi2_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = csi2_रेजिस्टरed,
पूर्ण;

अटल पूर्णांक csi2_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
			     काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा csi2_dev *csi2 = notअगरier_to_dev(notअगरier);
	काष्ठा media_pad *sink = &csi2->sd.entity.pads[CSI2_SINK_PAD];
	पूर्णांक pad;

	pad = media_entity_get_fwnode_pad(&sd->entity, asd->match.fwnode,
					  MEDIA_PAD_FL_SOURCE);
	अगर (pad < 0) अणु
		dev_err(csi2->dev, "Failed to find pad for %s\n", sd->name);
		वापस pad;
	पूर्ण

	csi2->remote = sd;
	csi2->remote_pad = pad;

	dev_dbg(csi2->dev, "Bound %s pad: %d\n", sd->name, pad);

	वापस v4l2_create_fwnode_links_to_pad(sd, sink, 0);
पूर्ण

अटल व्योम csi2_notअगरy_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
			       काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा csi2_dev *csi2 = notअगरier_to_dev(notअगरier);

	csi2->remote = शून्य;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations csi2_notअगरy_ops = अणु
	.bound = csi2_notअगरy_bound,
	.unbind = csi2_notअगरy_unbind,
पूर्ण;

अटल पूर्णांक csi2_async_रेजिस्टर(काष्ठा csi2_dev *csi2)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY,
	पूर्ण;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा fwnode_handle *ep;
	पूर्णांक ret;

	v4l2_async_notअगरier_init(&csi2->notअगरier);

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(csi2->dev), 0, 0,
					     FWNODE_GRAPH_ENDPOINT_NEXT);
	अगर (!ep)
		वापस -ENOTCONN;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);
	अगर (ret)
		जाओ err_parse;

	csi2->data_lanes = vep.bus.mipi_csi2.num_data_lanes;

	dev_dbg(csi2->dev, "data lanes: %d\n", vep.bus.mipi_csi2.num_data_lanes);
	dev_dbg(csi2->dev, "flags: 0x%08x\n", vep.bus.mipi_csi2.flags);

	asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
		&csi2->notअगरier, ep, काष्ठा v4l2_async_subdev);
	fwnode_handle_put(ep);

	अगर (IS_ERR(asd))
		वापस PTR_ERR(asd);

	csi2->notअगरier.ops = &csi2_notअगरy_ops;

	ret = v4l2_async_subdev_notअगरier_रेजिस्टर(&csi2->sd,
						  &csi2->notअगरier);
	अगर (ret)
		वापस ret;

	वापस v4l2_async_रेजिस्टर_subdev(&csi2->sd);

err_parse:
	fwnode_handle_put(ep);
	वापस ret;
पूर्ण

अटल पूर्णांक csi2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा csi2_dev *csi2;
	काष्ठा resource *res;
	पूर्णांक i, ret;

	csi2 = devm_kzalloc(&pdev->dev, माप(*csi2), GFP_KERNEL);
	अगर (!csi2)
		वापस -ENOMEM;

	csi2->dev = &pdev->dev;

	v4l2_subdev_init(&csi2->sd, &csi2_subdev_ops);
	v4l2_set_subdevdata(&csi2->sd, &pdev->dev);
	csi2->sd.पूर्णांकernal_ops = &csi2_पूर्णांकernal_ops;
	csi2->sd.entity.ops = &csi2_entity_ops;
	csi2->sd.dev = &pdev->dev;
	csi2->sd.owner = THIS_MODULE;
	csi2->sd.flags = V4L2_SUBDEV_FL_HAS_DEVNODE;
	strscpy(csi2->sd.name, DEVICE_NAME, माप(csi2->sd.name));
	csi2->sd.entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	csi2->sd.grp_id = IMX_MEDIA_GRP_ID_CSI2;

	क्रम (i = 0; i < CSI2_NUM_PADS; i++) अणु
		csi2->pad[i].flags = (i == CSI2_SINK_PAD) ?
		MEDIA_PAD_FL_SINK : MEDIA_PAD_FL_SOURCE;
	पूर्ण

	ret = media_entity_pads_init(&csi2->sd.entity, CSI2_NUM_PADS,
				     csi2->pad);
	अगर (ret)
		वापस ret;

	csi2->pllref_clk = devm_clk_get(&pdev->dev, "ref");
	अगर (IS_ERR(csi2->pllref_clk)) अणु
		v4l2_err(&csi2->sd, "failed to get pll reference clock\n");
		वापस PTR_ERR(csi2->pllref_clk);
	पूर्ण

	csi2->dphy_clk = devm_clk_get(&pdev->dev, "dphy");
	अगर (IS_ERR(csi2->dphy_clk)) अणु
		v4l2_err(&csi2->sd, "failed to get dphy clock\n");
		वापस PTR_ERR(csi2->dphy_clk);
	पूर्ण

	csi2->pix_clk = devm_clk_get(&pdev->dev, "pix");
	अगर (IS_ERR(csi2->pix_clk)) अणु
		v4l2_err(&csi2->sd, "failed to get pixel clock\n");
		वापस PTR_ERR(csi2->pix_clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		v4l2_err(&csi2->sd, "failed to get platform resources\n");
		वापस -ENODEV;
	पूर्ण

	csi2->base = devm_ioremap(&pdev->dev, res->start, PAGE_SIZE);
	अगर (!csi2->base)
		वापस -ENOMEM;

	mutex_init(&csi2->lock);

	ret = clk_prepare_enable(csi2->pllref_clk);
	अगर (ret) अणु
		v4l2_err(&csi2->sd, "failed to enable pllref_clk\n");
		जाओ rmmutex;
	पूर्ण

	ret = clk_prepare_enable(csi2->dphy_clk);
	अगर (ret) अणु
		v4l2_err(&csi2->sd, "failed to enable dphy_clk\n");
		जाओ pllref_off;
	पूर्ण

	platक्रमm_set_drvdata(pdev, &csi2->sd);

	ret = csi2_async_रेजिस्टर(csi2);
	अगर (ret)
		जाओ clean_notअगरier;

	वापस 0;

clean_notअगरier:
	v4l2_async_notअगरier_unरेजिस्टर(&csi2->notअगरier);
	v4l2_async_notअगरier_cleanup(&csi2->notअगरier);
	clk_disable_unprepare(csi2->dphy_clk);
pllref_off:
	clk_disable_unprepare(csi2->pllref_clk);
rmmutex:
	mutex_destroy(&csi2->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक csi2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v4l2_subdev *sd = platक्रमm_get_drvdata(pdev);
	काष्ठा csi2_dev *csi2 = sd_to_dev(sd);

	v4l2_async_notअगरier_unरेजिस्टर(&csi2->notअगरier);
	v4l2_async_notअगरier_cleanup(&csi2->notअगरier);
	v4l2_async_unरेजिस्टर_subdev(sd);
	clk_disable_unprepare(csi2->dphy_clk);
	clk_disable_unprepare(csi2->pllref_clk);
	mutex_destroy(&csi2->lock);
	media_entity_cleanup(&sd->entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id csi2_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6-mipi-csi2", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, csi2_dt_ids);

अटल काष्ठा platक्रमm_driver csi2_driver = अणु
	.driver = अणु
		.name = DEVICE_NAME,
		.of_match_table = csi2_dt_ids,
	पूर्ण,
	.probe = csi2_probe,
	.हटाओ = csi2_हटाओ,
पूर्ण;

module_platक्रमm_driver(csi2_driver);

MODULE_DESCRIPTION("i.MX5/6 MIPI CSI-2 Receiver driver");
MODULE_AUTHOR("Steve Longerbeam <steve_longerbeam@mentor.com>");
MODULE_LICENSE("GPL");
