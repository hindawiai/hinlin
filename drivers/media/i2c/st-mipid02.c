<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम ST MIPID02 CSI-2 to PARALLEL bridge
 *
 * Copyright (C) STMicroelectronics SA 2019
 * Authors: Mickael Guene <mickael.guene@st.com>
 *          क्रम STMicroelectronics.
 *
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा MIPID02_CLK_LANE_WR_REG1			0x01
#घोषणा MIPID02_CLK_LANE_REG1				0x02
#घोषणा MIPID02_CLK_LANE_REG3				0x04
#घोषणा MIPID02_DATA_LANE0_REG1				0x05
#घोषणा MIPID02_DATA_LANE0_REG2				0x06
#घोषणा MIPID02_DATA_LANE1_REG1				0x09
#घोषणा MIPID02_DATA_LANE1_REG2				0x0a
#घोषणा MIPID02_MODE_REG1				0x14
#घोषणा MIPID02_MODE_REG2				0x15
#घोषणा MIPID02_DATA_ID_RREG				0x17
#घोषणा MIPID02_DATA_SELECTION_CTRL			0x19
#घोषणा MIPID02_PIX_WIDTH_CTRL				0x1e
#घोषणा MIPID02_PIX_WIDTH_CTRL_EMB			0x1f

/* Bits definition क्रम MIPID02_CLK_LANE_REG1 */
#घोषणा CLK_ENABLE					BIT(0)
/* Bits definition क्रम MIPID02_CLK_LANE_REG3 */
#घोषणा CLK_MIPI_CSI					BIT(1)
/* Bits definition क्रम MIPID02_DATA_LANE0_REG1 */
#घोषणा DATA_ENABLE					BIT(0)
/* Bits definition क्रम MIPID02_DATA_LANEx_REG2 */
#घोषणा DATA_MIPI_CSI					BIT(0)
/* Bits definition क्रम MIPID02_MODE_REG1 */
#घोषणा MODE_DATA_SWAP					BIT(2)
#घोषणा MODE_NO_BYPASS					BIT(6)
/* Bits definition क्रम MIPID02_MODE_REG2 */
#घोषणा MODE_HSYNC_ACTIVE_HIGH				BIT(1)
#घोषणा MODE_VSYNC_ACTIVE_HIGH				BIT(2)
/* Bits definition क्रम MIPID02_DATA_SELECTION_CTRL */
#घोषणा SELECTION_MANUAL_DATA				BIT(2)
#घोषणा SELECTION_MANUAL_WIDTH				BIT(3)

अटल स्थिर u32 mipid02_supported_fmt_codes[] = अणु
	MEDIA_BUS_FMT_SBGGR8_1X8, MEDIA_BUS_FMT_SGBRG8_1X8,
	MEDIA_BUS_FMT_SGRBG8_1X8, MEDIA_BUS_FMT_SRGGB8_1X8,
	MEDIA_BUS_FMT_SBGGR10_1X10, MEDIA_BUS_FMT_SGBRG10_1X10,
	MEDIA_BUS_FMT_SGRBG10_1X10, MEDIA_BUS_FMT_SRGGB10_1X10,
	MEDIA_BUS_FMT_SBGGR12_1X12, MEDIA_BUS_FMT_SGBRG12_1X12,
	MEDIA_BUS_FMT_SGRBG12_1X12, MEDIA_BUS_FMT_SRGGB12_1X12,
	MEDIA_BUS_FMT_UYVY8_1X16, MEDIA_BUS_FMT_BGR888_1X24,
	MEDIA_BUS_FMT_RGB565_2X8_LE, MEDIA_BUS_FMT_RGB565_2X8_BE,
	MEDIA_BUS_FMT_YUYV8_2X8, MEDIA_BUS_FMT_UYVY8_2X8,
	MEDIA_BUS_FMT_JPEG_1X8
पूर्ण;

/* regulator supplies */
अटल स्थिर अक्षर * स्थिर mipid02_supply_name[] = अणु
	"VDDE", /* 1.8V digital I/O supply */
	"VDDIN", /* 1V8 voltage regulator supply */
पूर्ण;

#घोषणा MIPID02_NUM_SUPPLIES		ARRAY_SIZE(mipid02_supply_name)

#घोषणा MIPID02_SINK_0			0
#घोषणा MIPID02_SINK_1			1
#घोषणा MIPID02_SOURCE			2
#घोषणा MIPID02_PAD_NB			3

काष्ठा mipid02_dev अणु
	काष्ठा i2c_client *i2c_client;
	काष्ठा regulator_bulk_data supplies[MIPID02_NUM_SUPPLIES];
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad[MIPID02_PAD_NB];
	काष्ठा clk *xclk;
	काष्ठा gpio_desc *reset_gpio;
	/* endpoपूर्णांकs info */
	काष्ठा v4l2_fwnode_endpoपूर्णांक rx;
	u64 link_frequency;
	काष्ठा v4l2_fwnode_endpoपूर्णांक tx;
	/* remote source */
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा v4l2_subdev *s_subdev;
	/* रेजिस्टरs */
	काष्ठा अणु
		u8 clk_lane_reg1;
		u8 data_lane0_reg1;
		u8 data_lane1_reg1;
		u8 mode_reg1;
		u8 mode_reg2;
		u8 data_selection_ctrl;
		u8 data_id_rreg;
		u8 pix_width_ctrl;
		u8 pix_width_ctrl_emb;
	पूर्ण r;
	/* lock to protect all members below */
	काष्ठा mutex lock;
	bool streaming;
	काष्ठा v4l2_mbus_framefmt fmt;
पूर्ण;

अटल पूर्णांक bpp_from_code(__u32 code)
अणु
	चयन (code) अणु
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
		वापस 8;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
	हाल MEDIA_BUS_FMT_SGBRG10_1X10:
	हाल MEDIA_BUS_FMT_SGRBG10_1X10:
	हाल MEDIA_BUS_FMT_SRGGB10_1X10:
		वापस 10;
	हाल MEDIA_BUS_FMT_SBGGR12_1X12:
	हाल MEDIA_BUS_FMT_SGBRG12_1X12:
	हाल MEDIA_BUS_FMT_SGRBG12_1X12:
	हाल MEDIA_BUS_FMT_SRGGB12_1X12:
		वापस 12;
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
	हाल MEDIA_BUS_FMT_RGB565_2X8_BE:
		वापस 16;
	हाल MEDIA_BUS_FMT_BGR888_1X24:
		वापस 24;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u8 data_type_from_code(__u32 code)
अणु
	चयन (code) अणु
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
		वापस 0x2a;
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
	हाल MEDIA_BUS_FMT_SGBRG10_1X10:
	हाल MEDIA_BUS_FMT_SGRBG10_1X10:
	हाल MEDIA_BUS_FMT_SRGGB10_1X10:
		वापस 0x2b;
	हाल MEDIA_BUS_FMT_SBGGR12_1X12:
	हाल MEDIA_BUS_FMT_SGBRG12_1X12:
	हाल MEDIA_BUS_FMT_SGRBG12_1X12:
	हाल MEDIA_BUS_FMT_SRGGB12_1X12:
		वापस 0x2c;
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		वापस 0x1e;
	हाल MEDIA_BUS_FMT_BGR888_1X24:
		वापस 0x24;
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
	हाल MEDIA_BUS_FMT_RGB565_2X8_BE:
		वापस 0x22;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम init_क्रमmat(काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->code = MEDIA_BUS_FMT_SBGGR8_1X8;
	fmt->field = V4L2_FIELD_NONE;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
	fmt->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(V4L2_COLORSPACE_SRGB);
	fmt->quantization = V4L2_QUANTIZATION_FULL_RANGE;
	fmt->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(V4L2_COLORSPACE_SRGB);
	fmt->width = 640;
	fmt->height = 480;
पूर्ण

अटल __u32 get_fmt_code(__u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mipid02_supported_fmt_codes); i++) अणु
		अगर (code == mipid02_supported_fmt_codes[i])
			वापस code;
	पूर्ण

	वापस mipid02_supported_fmt_codes[0];
पूर्ण

अटल __u32 serial_to_parallel_code(__u32 serial)
अणु
	अगर (serial == MEDIA_BUS_FMT_UYVY8_1X16)
		वापस MEDIA_BUS_FMT_UYVY8_2X8;
	अगर (serial == MEDIA_BUS_FMT_BGR888_1X24)
		वापस MEDIA_BUS_FMT_BGR888_3X8;

	वापस serial;
पूर्ण

अटल अंतरभूत काष्ठा mipid02_dev *to_mipid02_dev(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा mipid02_dev, sd);
पूर्ण

अटल पूर्णांक mipid02_पढ़ो_reg(काष्ठा mipid02_dev *bridge, u16 reg, u8 *val)
अणु
	काष्ठा i2c_client *client = bridge->i2c_client;
	काष्ठा i2c_msg msg[2];
	u8 buf[2];
	पूर्णांक ret;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;

	msg[0].addr = client->addr;
	msg[0].flags = client->flags;
	msg[0].buf = buf;
	msg[0].len = माप(buf);

	msg[1].addr = client->addr;
	msg[1].flags = client->flags | I2C_M_RD;
	msg[1].buf = val;
	msg[1].len = 1;

	ret = i2c_transfer(client->adapter, msg, 2);
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "%s: %x i2c_transfer, reg: %x => %d\n",
			    __func__, client->addr, reg, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mipid02_ग_लिखो_reg(काष्ठा mipid02_dev *bridge, u16 reg, u8 val)
अणु
	काष्ठा i2c_client *client = bridge->i2c_client;
	काष्ठा i2c_msg msg;
	u8 buf[3];
	पूर्णांक ret;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;
	buf[2] = val;

	msg.addr = client->addr;
	msg.flags = client->flags;
	msg.buf = buf;
	msg.len = माप(buf);

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "%s: i2c_transfer, reg: %x => %d\n",
			    __func__, reg, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mipid02_get_regulators(काष्ठा mipid02_dev *bridge)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MIPID02_NUM_SUPPLIES; i++)
		bridge->supplies[i].supply = mipid02_supply_name[i];

	वापस devm_regulator_bulk_get(&bridge->i2c_client->dev,
				       MIPID02_NUM_SUPPLIES,
				       bridge->supplies);
पूर्ण

अटल व्योम mipid02_apply_reset(काष्ठा mipid02_dev *bridge)
अणु
	gpiod_set_value_cansleep(bridge->reset_gpio, 0);
	usleep_range(5000, 10000);
	gpiod_set_value_cansleep(bridge->reset_gpio, 1);
	usleep_range(5000, 10000);
	gpiod_set_value_cansleep(bridge->reset_gpio, 0);
	usleep_range(5000, 10000);
पूर्ण

अटल पूर्णांक mipid02_set_घातer_on(काष्ठा mipid02_dev *bridge)
अणु
	काष्ठा i2c_client *client = bridge->i2c_client;
	पूर्णांक ret;

	ret = clk_prepare_enable(bridge->xclk);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: failed to enable clock\n", __func__);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(MIPID02_NUM_SUPPLIES,
				    bridge->supplies);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: failed to enable regulators\n",
			    __func__);
		जाओ xclk_off;
	पूर्ण

	अगर (bridge->reset_gpio) अणु
		dev_dbg(&client->dev, "apply reset");
		mipid02_apply_reset(bridge);
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "don't apply reset");
		usleep_range(5000, 10000);
	पूर्ण

	वापस 0;

xclk_off:
	clk_disable_unprepare(bridge->xclk);
	वापस ret;
पूर्ण

अटल व्योम mipid02_set_घातer_off(काष्ठा mipid02_dev *bridge)
अणु
	regulator_bulk_disable(MIPID02_NUM_SUPPLIES, bridge->supplies);
	clk_disable_unprepare(bridge->xclk);
पूर्ण

अटल पूर्णांक mipid02_detect(काष्ठा mipid02_dev *bridge)
अणु
	u8 reg;

	/*
	 * There is no version रेजिस्टरs. Just try to पढ़ो रेजिस्टर
	 * MIPID02_CLK_LANE_WR_REG1.
	 */
	वापस mipid02_पढ़ो_reg(bridge, MIPID02_CLK_LANE_WR_REG1, &reg);
पूर्ण

अटल u32 mipid02_get_link_freq_from_cid_link_freq(काष्ठा mipid02_dev *bridge,
						    काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा v4l2_querymenu qm = अणु.id = V4L2_CID_LINK_FREQ, पूर्ण;
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक ret;

	ctrl = v4l2_ctrl_find(subdev->ctrl_handler, V4L2_CID_LINK_FREQ);
	अगर (!ctrl)
		वापस 0;
	qm.index = v4l2_ctrl_g_ctrl(ctrl);

	ret = v4l2_querymenu(subdev->ctrl_handler, &qm);
	अगर (ret)
		वापस 0;

	वापस qm.value;
पूर्ण

अटल u32 mipid02_get_link_freq_from_cid_pixel_rate(काष्ठा mipid02_dev *bridge,
						     काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक *ep = &bridge->rx;
	काष्ठा v4l2_ctrl *ctrl;
	u32 pixel_घड़ी;
	u32 bpp = bpp_from_code(bridge->fmt.code);

	ctrl = v4l2_ctrl_find(subdev->ctrl_handler, V4L2_CID_PIXEL_RATE);
	अगर (!ctrl)
		वापस 0;
	pixel_घड़ी = v4l2_ctrl_g_ctrl_पूर्णांक64(ctrl);

	वापस pixel_घड़ी * bpp / (2 * ep->bus.mipi_csi2.num_data_lanes);
पूर्ण

/*
 * We need to know link frequency to setup clk_lane_reg1 timings. Link frequency
 * will be computed using connected device V4L2_CID_PIXEL_RATE, bit per pixel
 * and number of lanes.
 */
अटल पूर्णांक mipid02_configure_from_rx_speed(काष्ठा mipid02_dev *bridge)
अणु
	काष्ठा i2c_client *client = bridge->i2c_client;
	काष्ठा v4l2_subdev *subdev = bridge->s_subdev;
	u32 link_freq;

	link_freq = mipid02_get_link_freq_from_cid_link_freq(bridge, subdev);
	अगर (!link_freq) अणु
		link_freq = mipid02_get_link_freq_from_cid_pixel_rate(bridge,
								      subdev);
		अगर (!link_freq) अणु
			dev_err(&client->dev, "Failed to get link frequency");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dev_dbg(&client->dev, "detect link_freq = %d Hz", link_freq);
	bridge->r.clk_lane_reg1 |= (2000000000 / link_freq) << 2;

	वापस 0;
पूर्ण

अटल पूर्णांक mipid02_configure_clk_lane(काष्ठा mipid02_dev *bridge)
अणु
	काष्ठा i2c_client *client = bridge->i2c_client;
	काष्ठा v4l2_fwnode_endpoपूर्णांक *ep = &bridge->rx;
	bool *polarities = ep->bus.mipi_csi2.lane_polarities;

	/* midid02 करोesn't support घड़ी lane remapping */
	अगर (ep->bus.mipi_csi2.घड़ी_lane != 0) अणु
		dev_err(&client->dev, "clk lane must be map to lane 0\n");
		वापस -EINVAL;
	पूर्ण
	bridge->r.clk_lane_reg1 |= (polarities[0] << 1) | CLK_ENABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक mipid02_configure_data0_lane(काष्ठा mipid02_dev *bridge, पूर्णांक nb,
					bool are_lanes_swap, bool *polarities)
अणु
	bool are_pin_swap = are_lanes_swap ? polarities[2] : polarities[1];

	अगर (nb == 1 && are_lanes_swap)
		वापस 0;

	/*
	 * data lane 0 as pin swap polarity reversed compared to घड़ी and
	 * data lane 1
	 */
	अगर (!are_pin_swap)
		bridge->r.data_lane0_reg1 = 1 << 1;
	bridge->r.data_lane0_reg1 |= DATA_ENABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक mipid02_configure_data1_lane(काष्ठा mipid02_dev *bridge, पूर्णांक nb,
					bool are_lanes_swap, bool *polarities)
अणु
	bool are_pin_swap = are_lanes_swap ? polarities[1] : polarities[2];

	अगर (nb == 1 && !are_lanes_swap)
		वापस 0;

	अगर (are_pin_swap)
		bridge->r.data_lane1_reg1 = 1 << 1;
	bridge->r.data_lane1_reg1 |= DATA_ENABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक mipid02_configure_from_rx(काष्ठा mipid02_dev *bridge)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक *ep = &bridge->rx;
	bool are_lanes_swap = ep->bus.mipi_csi2.data_lanes[0] == 2;
	bool *polarities = ep->bus.mipi_csi2.lane_polarities;
	पूर्णांक nb = ep->bus.mipi_csi2.num_data_lanes;
	पूर्णांक ret;

	ret = mipid02_configure_clk_lane(bridge);
	अगर (ret)
		वापस ret;

	ret = mipid02_configure_data0_lane(bridge, nb, are_lanes_swap,
					   polarities);
	अगर (ret)
		वापस ret;

	ret = mipid02_configure_data1_lane(bridge, nb, are_lanes_swap,
					   polarities);
	अगर (ret)
		वापस ret;

	bridge->r.mode_reg1 |= are_lanes_swap ? MODE_DATA_SWAP : 0;
	bridge->r.mode_reg1 |= (nb - 1) << 1;

	वापस mipid02_configure_from_rx_speed(bridge);
पूर्ण

अटल पूर्णांक mipid02_configure_from_tx(काष्ठा mipid02_dev *bridge)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक *ep = &bridge->tx;

	bridge->r.data_selection_ctrl = SELECTION_MANUAL_WIDTH;
	bridge->r.pix_width_ctrl = ep->bus.parallel.bus_width;
	bridge->r.pix_width_ctrl_emb = ep->bus.parallel.bus_width;
	अगर (ep->bus.parallel.flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		bridge->r.mode_reg2 |= MODE_HSYNC_ACTIVE_HIGH;
	अगर (ep->bus.parallel.flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		bridge->r.mode_reg2 |= MODE_VSYNC_ACTIVE_HIGH;

	वापस 0;
पूर्ण

अटल पूर्णांक mipid02_configure_from_code(काष्ठा mipid02_dev *bridge)
अणु
	u8 data_type;

	bridge->r.data_id_rreg = 0;

	अगर (bridge->fmt.code != MEDIA_BUS_FMT_JPEG_1X8) अणु
		bridge->r.data_selection_ctrl |= SELECTION_MANUAL_DATA;

		data_type = data_type_from_code(bridge->fmt.code);
		अगर (!data_type)
			वापस -EINVAL;
		bridge->r.data_id_rreg = data_type;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mipid02_stream_disable(काष्ठा mipid02_dev *bridge)
अणु
	काष्ठा i2c_client *client = bridge->i2c_client;
	पूर्णांक ret;

	/* Disable all lanes */
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_CLK_LANE_REG1, 0);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_DATA_LANE0_REG1, 0);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_DATA_LANE1_REG1, 0);
	अगर (ret)
		जाओ error;
error:
	अगर (ret)
		dev_err(&client->dev, "failed to stream off %d", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mipid02_stream_enable(काष्ठा mipid02_dev *bridge)
अणु
	काष्ठा i2c_client *client = bridge->i2c_client;
	पूर्णांक ret = -EINVAL;

	अगर (!bridge->s_subdev)
		जाओ error;

	स_रखो(&bridge->r, 0, माप(bridge->r));
	/* build रेजिस्टरs content */
	ret = mipid02_configure_from_rx(bridge);
	अगर (ret)
		जाओ error;
	ret = mipid02_configure_from_tx(bridge);
	अगर (ret)
		जाओ error;
	ret = mipid02_configure_from_code(bridge);
	अगर (ret)
		जाओ error;

	/* ग_लिखो mipi रेजिस्टरs */
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_CLK_LANE_REG1,
		bridge->r.clk_lane_reg1);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_CLK_LANE_REG3, CLK_MIPI_CSI);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_DATA_LANE0_REG1,
		bridge->r.data_lane0_reg1);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_DATA_LANE0_REG2,
		DATA_MIPI_CSI);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_DATA_LANE1_REG1,
		bridge->r.data_lane1_reg1);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_DATA_LANE1_REG2,
		DATA_MIPI_CSI);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_MODE_REG1,
		MODE_NO_BYPASS | bridge->r.mode_reg1);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_MODE_REG2,
		bridge->r.mode_reg2);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_DATA_ID_RREG,
		bridge->r.data_id_rreg);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_DATA_SELECTION_CTRL,
		bridge->r.data_selection_ctrl);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_PIX_WIDTH_CTRL,
		bridge->r.pix_width_ctrl);
	अगर (ret)
		जाओ error;
	ret = mipid02_ग_लिखो_reg(bridge, MIPID02_PIX_WIDTH_CTRL_EMB,
		bridge->r.pix_width_ctrl_emb);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	dev_err(&client->dev, "failed to stream on %d", ret);
	mipid02_stream_disable(bridge);

	वापस ret;
पूर्ण

अटल पूर्णांक mipid02_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा mipid02_dev *bridge = to_mipid02_dev(sd);
	काष्ठा i2c_client *client = bridge->i2c_client;
	पूर्णांक ret = 0;

	dev_dbg(&client->dev, "%s : requested %d / current = %d", __func__,
		    enable, bridge->streaming);
	mutex_lock(&bridge->lock);

	अगर (bridge->streaming == enable)
		जाओ out;

	ret = enable ? mipid02_stream_enable(bridge) :
		       mipid02_stream_disable(bridge);
	अगर (!ret)
		bridge->streaming = enable;

out:
	dev_dbg(&client->dev, "%s current now = %d / %d", __func__,
		    bridge->streaming, ret);
	mutex_unlock(&bridge->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mipid02_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा mipid02_dev *bridge = to_mipid02_dev(sd);
	पूर्णांक ret = 0;

	चयन (code->pad) अणु
	हाल MIPID02_SINK_0:
		अगर (code->index >= ARRAY_SIZE(mipid02_supported_fmt_codes))
			ret = -EINVAL;
		अन्यथा
			code->code = mipid02_supported_fmt_codes[code->index];
		अवरोध;
	हाल MIPID02_SOURCE:
		अगर (code->index == 0)
			code->code = serial_to_parallel_code(bridge->fmt.code);
		अन्यथा
			ret = -EINVAL;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mipid02_get_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &क्रमmat->क्रमmat;
	काष्ठा mipid02_dev *bridge = to_mipid02_dev(sd);
	काष्ठा i2c_client *client = bridge->i2c_client;
	काष्ठा v4l2_mbus_framefmt *fmt;

	dev_dbg(&client->dev, "%s probe %d", __func__, क्रमmat->pad);

	अगर (क्रमmat->pad >= MIPID02_PAD_NB)
		वापस -EINVAL;
	/* second CSI-2 pad not yet supported */
	अगर (क्रमmat->pad == MIPID02_SINK_1)
		वापस -EINVAL;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt = v4l2_subdev_get_try_क्रमmat(&bridge->sd, cfg, क्रमmat->pad);
	अन्यथा
		fmt = &bridge->fmt;

	mutex_lock(&bridge->lock);

	*mbus_fmt = *fmt;
	/* code may need to be converted क्रम source */
	अगर (क्रमmat->pad == MIPID02_SOURCE)
		mbus_fmt->code = serial_to_parallel_code(mbus_fmt->code);

	mutex_unlock(&bridge->lock);

	वापस 0;
पूर्ण

अटल व्योम mipid02_set_fmt_source(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा mipid02_dev *bridge = to_mipid02_dev(sd);

	/* source pad mirror active sink pad */
	क्रमmat->क्रमmat = bridge->fmt;
	/* but code may need to be converted */
	क्रमmat->क्रमmat.code = serial_to_parallel_code(क्रमmat->क्रमmat.code);

	/* only apply क्रमmat क्रम V4L2_SUBDEV_FORMAT_TRY हाल */
	अगर (क्रमmat->which != V4L2_SUBDEV_FORMAT_TRY)
		वापस;

	*v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad) = क्रमmat->क्रमmat;
पूर्ण

अटल व्योम mipid02_set_fmt_sink(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा mipid02_dev *bridge = to_mipid02_dev(sd);
	काष्ठा v4l2_mbus_framefmt *fmt;

	क्रमmat->क्रमmat.code = get_fmt_code(क्रमmat->क्रमmat.code);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
	अन्यथा
		fmt = &bridge->fmt;

	*fmt = क्रमmat->क्रमmat;
पूर्ण

अटल पूर्णांक mipid02_set_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा mipid02_dev *bridge = to_mipid02_dev(sd);
	काष्ठा i2c_client *client = bridge->i2c_client;
	पूर्णांक ret = 0;

	dev_dbg(&client->dev, "%s for %d", __func__, क्रमmat->pad);

	अगर (क्रमmat->pad >= MIPID02_PAD_NB)
		वापस -EINVAL;
	/* second CSI-2 pad not yet supported */
	अगर (क्रमmat->pad == MIPID02_SINK_1)
		वापस -EINVAL;

	mutex_lock(&bridge->lock);

	अगर (bridge->streaming) अणु
		ret = -EBUSY;
		जाओ error;
	पूर्ण

	अगर (क्रमmat->pad == MIPID02_SOURCE)
		mipid02_set_fmt_source(sd, cfg, क्रमmat);
	अन्यथा
		mipid02_set_fmt_sink(sd, cfg, क्रमmat);

error:
	mutex_unlock(&bridge->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops mipid02_video_ops = अणु
	.s_stream = mipid02_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mipid02_pad_ops = अणु
	.क्रमागत_mbus_code = mipid02_क्रमागत_mbus_code,
	.get_fmt = mipid02_get_fmt,
	.set_fmt = mipid02_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mipid02_subdev_ops = अणु
	.video = &mipid02_video_ops,
	.pad = &mipid02_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations mipid02_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल पूर्णांक mipid02_async_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
			       काष्ठा v4l2_subdev *s_subdev,
			       काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा mipid02_dev *bridge = to_mipid02_dev(notअगरier->sd);
	काष्ठा i2c_client *client = bridge->i2c_client;
	पूर्णांक source_pad;
	पूर्णांक ret;

	dev_dbg(&client->dev, "sensor_async_bound call %p", s_subdev);

	source_pad = media_entity_get_fwnode_pad(&s_subdev->entity,
						 s_subdev->fwnode,
						 MEDIA_PAD_FL_SOURCE);
	अगर (source_pad < 0) अणु
		dev_err(&client->dev, "Couldn't find output pad for subdev %s\n",
			s_subdev->name);
		वापस source_pad;
	पूर्ण

	ret = media_create_pad_link(&s_subdev->entity, source_pad,
				    &bridge->sd.entity, 0,
				    MEDIA_LNK_FL_ENABLED |
				    MEDIA_LNK_FL_IMMUTABLE);
	अगर (ret) अणु
		dev_err(&client->dev, "Couldn't create media link %d", ret);
		वापस ret;
	पूर्ण

	bridge->s_subdev = s_subdev;

	वापस 0;
पूर्ण

अटल व्योम mipid02_async_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
				 काष्ठा v4l2_subdev *s_subdev,
				 काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा mipid02_dev *bridge = to_mipid02_dev(notअगरier->sd);

	bridge->s_subdev = शून्य;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations mipid02_notअगरier_ops = अणु
	.bound		= mipid02_async_bound,
	.unbind		= mipid02_async_unbind,
पूर्ण;

अटल पूर्णांक mipid02_parse_rx_ep(काष्ठा mipid02_dev *bridge)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep = अणु .bus_type = V4L2_MBUS_CSI2_DPHY पूर्ण;
	काष्ठा i2c_client *client = bridge->i2c_client;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा device_node *ep_node;
	पूर्णांक ret;

	/* parse rx (endpoपूर्णांक 0) */
	ep_node = of_graph_get_endpoपूर्णांक_by_regs(bridge->i2c_client->dev.of_node,
						0, 0);
	अगर (!ep_node) अणु
		dev_err(&client->dev, "unable to find port0 ep");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep_node), &ep);
	अगर (ret) अणु
		dev_err(&client->dev, "Could not parse v4l2 endpoint %d\n",
			ret);
		जाओ error_of_node_put;
	पूर्ण

	/* करो some sanity checks */
	अगर (ep.bus.mipi_csi2.num_data_lanes > 2) अणु
		dev_err(&client->dev, "max supported data lanes is 2 / got %d",
			ep.bus.mipi_csi2.num_data_lanes);
		ret = -EINVAL;
		जाओ error_of_node_put;
	पूर्ण

	/* रेजिस्टर it क्रम later use */
	bridge->rx = ep;

	/* रेजिस्टर async notअगरier so we get noticed when sensor is connected */
	v4l2_async_notअगरier_init(&bridge->notअगरier);
	asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
					&bridge->notअगरier,
					of_fwnode_handle(ep_node),
					काष्ठा v4l2_async_subdev);
	of_node_put(ep_node);

	अगर (IS_ERR(asd)) अणु
		dev_err(&client->dev, "fail to register asd to notifier %ld",
			PTR_ERR(asd));
		वापस PTR_ERR(asd);
	पूर्ण
	bridge->notअगरier.ops = &mipid02_notअगरier_ops;

	ret = v4l2_async_subdev_notअगरier_रेजिस्टर(&bridge->sd,
						  &bridge->notअगरier);
	अगर (ret)
		v4l2_async_notअगरier_cleanup(&bridge->notअगरier);

	वापस ret;

error_of_node_put:
	of_node_put(ep_node);
error:

	वापस ret;
पूर्ण

अटल पूर्णांक mipid02_parse_tx_ep(काष्ठा mipid02_dev *bridge)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep = अणु .bus_type = V4L2_MBUS_PARALLEL पूर्ण;
	काष्ठा i2c_client *client = bridge->i2c_client;
	काष्ठा device_node *ep_node;
	पूर्णांक ret;

	/* parse tx (endpoपूर्णांक 2) */
	ep_node = of_graph_get_endpoपूर्णांक_by_regs(bridge->i2c_client->dev.of_node,
						2, 0);
	अगर (!ep_node) अणु
		dev_err(&client->dev, "unable to find port1 ep");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep_node), &ep);
	अगर (ret) अणु
		dev_err(&client->dev, "Could not parse v4l2 endpoint\n");
		जाओ error_of_node_put;
	पूर्ण

	of_node_put(ep_node);
	bridge->tx = ep;

	वापस 0;

error_of_node_put:
	of_node_put(ep_node);
error:

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mipid02_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा mipid02_dev *bridge;
	u32 clk_freq;
	पूर्णांक ret;

	bridge = devm_kzalloc(dev, माप(*bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस -ENOMEM;

	init_क्रमmat(&bridge->fmt);

	bridge->i2c_client = client;
	v4l2_i2c_subdev_init(&bridge->sd, client, &mipid02_subdev_ops);

	/* got and check घड़ी */
	bridge->xclk = devm_clk_get(dev, "xclk");
	अगर (IS_ERR(bridge->xclk)) अणु
		dev_err(dev, "failed to get xclk\n");
		वापस PTR_ERR(bridge->xclk);
	पूर्ण

	clk_freq = clk_get_rate(bridge->xclk);
	अगर (clk_freq < 6000000 || clk_freq > 27000000) अणु
		dev_err(dev, "xclk freq must be in 6-27 Mhz range. got %d Hz\n",
			clk_freq);
		वापस -EINVAL;
	पूर्ण

	bridge->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						     GPIOD_OUT_HIGH);

	अगर (IS_ERR(bridge->reset_gpio)) अणु
		dev_err(dev, "failed to get reset GPIO\n");
		वापस PTR_ERR(bridge->reset_gpio);
	पूर्ण

	ret = mipid02_get_regulators(bridge);
	अगर (ret) अणु
		dev_err(dev, "failed to get regulators %d", ret);
		वापस ret;
	पूर्ण

	mutex_init(&bridge->lock);
	bridge->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	bridge->sd.entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	bridge->sd.entity.ops = &mipid02_subdev_entity_ops;
	bridge->pad[0].flags = MEDIA_PAD_FL_SINK;
	bridge->pad[1].flags = MEDIA_PAD_FL_SINK;
	bridge->pad[2].flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&bridge->sd.entity, MIPID02_PAD_NB,
				     bridge->pad);
	अगर (ret) अणु
		dev_err(&client->dev, "pads init failed %d", ret);
		जाओ mutex_cleanup;
	पूर्ण

	/* enable घड़ी, घातer and reset device अगर available */
	ret = mipid02_set_घातer_on(bridge);
	अगर (ret)
		जाओ entity_cleanup;

	ret = mipid02_detect(bridge);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to detect mipid02 %d", ret);
		जाओ घातer_off;
	पूर्ण

	ret = mipid02_parse_tx_ep(bridge);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to parse tx %d", ret);
		जाओ घातer_off;
	पूर्ण

	ret = mipid02_parse_rx_ep(bridge);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to parse rx %d", ret);
		जाओ घातer_off;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev(&bridge->sd);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "v4l2_async_register_subdev failed %d",
			    ret);
		जाओ unरेजिस्टर_notअगरier;
	पूर्ण

	dev_info(&client->dev, "mipid02 device probe successfully");

	वापस 0;

unरेजिस्टर_notअगरier:
	v4l2_async_notअगरier_unरेजिस्टर(&bridge->notअगरier);
	v4l2_async_notअगरier_cleanup(&bridge->notअगरier);
घातer_off:
	mipid02_set_घातer_off(bridge);
entity_cleanup:
	media_entity_cleanup(&bridge->sd.entity);
mutex_cleanup:
	mutex_destroy(&bridge->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mipid02_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा mipid02_dev *bridge = to_mipid02_dev(sd);

	v4l2_async_notअगरier_unरेजिस्टर(&bridge->notअगरier);
	v4l2_async_notअगरier_cleanup(&bridge->notअगरier);
	v4l2_async_unरेजिस्टर_subdev(&bridge->sd);
	mipid02_set_घातer_off(bridge);
	media_entity_cleanup(&bridge->sd.entity);
	mutex_destroy(&bridge->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mipid02_dt_ids[] = अणु
	अणु .compatible = "st,st-mipid02" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mipid02_dt_ids);

अटल काष्ठा i2c_driver mipid02_i2c_driver = अणु
	.driver = अणु
		.name  = "st-mipid02",
		.of_match_table = mipid02_dt_ids,
	पूर्ण,
	.probe_new = mipid02_probe,
	.हटाओ = mipid02_हटाओ,
पूर्ण;

module_i2c_driver(mipid02_i2c_driver);

MODULE_AUTHOR("Mickael Guene <mickael.guene@st.com>");
MODULE_DESCRIPTION("STMicroelectronics MIPID02 CSI-2 bridge driver");
MODULE_LICENSE("GPL v2");
