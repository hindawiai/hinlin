<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Maxim MAX9286 GMSL Deserializer Driver
 *
 * Copyright (C) 2017-2019 Jacopo Mondi
 * Copyright (C) 2017-2019 Kieran Bingham
 * Copyright (C) 2017-2019 Laurent Pinअक्षरt
 * Copyright (C) 2017-2019 Niklas Sथघderlund
 * Copyright (C) 2016 Renesas Electronics Corporation
 * Copyright (C) 2015 Cogent Embedded, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

/* Register 0x00 */
#घोषणा MAX9286_MSTLINKSEL_AUTO		(7 << 5)
#घोषणा MAX9286_MSTLINKSEL(n)		((n) << 5)
#घोषणा MAX9286_EN_VS_GEN		BIT(4)
#घोषणा MAX9286_LINKEN(n)		(1 << (n))
/* Register 0x01 */
#घोषणा MAX9286_FSYNCMODE_ECU		(3 << 6)
#घोषणा MAX9286_FSYNCMODE_EXT		(2 << 6)
#घोषणा MAX9286_FSYNCMODE_INT_OUT	(1 << 6)
#घोषणा MAX9286_FSYNCMODE_INT_HIZ	(0 << 6)
#घोषणा MAX9286_GPIEN			BIT(5)
#घोषणा MAX9286_ENLMO_RSTFSYNC		BIT(2)
#घोषणा MAX9286_FSYNCMETH_AUTO		(2 << 0)
#घोषणा MAX9286_FSYNCMETH_SEMI_AUTO	(1 << 0)
#घोषणा MAX9286_FSYNCMETH_MANUAL	(0 << 0)
#घोषणा MAX9286_REG_FSYNC_PERIOD_L	0x06
#घोषणा MAX9286_REG_FSYNC_PERIOD_M	0x07
#घोषणा MAX9286_REG_FSYNC_PERIOD_H	0x08
/* Register 0x0a */
#घोषणा MAX9286_FWDCCEN(n)		(1 << ((n) + 4))
#घोषणा MAX9286_REVCCEN(n)		(1 << (n))
/* Register 0x0c */
#घोषणा MAX9286_HVEN			BIT(7)
#घोषणा MAX9286_EDC_6BIT_HAMMING	(2 << 5)
#घोषणा MAX9286_EDC_6BIT_CRC		(1 << 5)
#घोषणा MAX9286_EDC_1BIT_PARITY		(0 << 5)
#घोषणा MAX9286_DESEL			BIT(4)
#घोषणा MAX9286_INVVS			BIT(3)
#घोषणा MAX9286_INVHS			BIT(2)
#घोषणा MAX9286_HVSRC_D0		(2 << 0)
#घोषणा MAX9286_HVSRC_D14		(1 << 0)
#घोषणा MAX9286_HVSRC_D18		(0 << 0)
/* Register 0x0f */
#घोषणा MAX9286_0X0F_RESERVED		BIT(3)
/* Register 0x12 */
#घोषणा MAX9286_CSILANECNT(n)		(((n) - 1) << 6)
#घोषणा MAX9286_CSIDBL			BIT(5)
#घोषणा MAX9286_DBL			BIT(4)
#घोषणा MAX9286_DATATYPE_USER_8BIT	(11 << 0)
#घोषणा MAX9286_DATATYPE_USER_YUV_12BIT	(10 << 0)
#घोषणा MAX9286_DATATYPE_USER_24BIT	(9 << 0)
#घोषणा MAX9286_DATATYPE_RAW14		(8 << 0)
#घोषणा MAX9286_DATATYPE_RAW11		(7 << 0)
#घोषणा MAX9286_DATATYPE_RAW10		(6 << 0)
#घोषणा MAX9286_DATATYPE_RAW8		(5 << 0)
#घोषणा MAX9286_DATATYPE_YUV422_10BIT	(4 << 0)
#घोषणा MAX9286_DATATYPE_YUV422_8BIT	(3 << 0)
#घोषणा MAX9286_DATATYPE_RGB555		(2 << 0)
#घोषणा MAX9286_DATATYPE_RGB565		(1 << 0)
#घोषणा MAX9286_DATATYPE_RGB888		(0 << 0)
/* Register 0x15 */
#घोषणा MAX9286_VC(n)			((n) << 5)
#घोषणा MAX9286_VCTYPE			BIT(4)
#घोषणा MAX9286_CSIOUTEN		BIT(3)
#घोषणा MAX9286_0X15_RESV		(3 << 0)
/* Register 0x1b */
#घोषणा MAX9286_SWITCHIN(n)		(1 << ((n) + 4))
#घोषणा MAX9286_ENEQ(n)			(1 << (n))
/* Register 0x27 */
#घोषणा MAX9286_LOCKED			BIT(7)
/* Register 0x31 */
#घोषणा MAX9286_FSYNC_LOCKED		BIT(6)
/* Register 0x34 */
#घोषणा MAX9286_I2CLOCACK		BIT(7)
#घोषणा MAX9286_I2CSLVSH_1046NS_469NS	(3 << 5)
#घोषणा MAX9286_I2CSLVSH_938NS_352NS	(2 << 5)
#घोषणा MAX9286_I2CSLVSH_469NS_234NS	(1 << 5)
#घोषणा MAX9286_I2CSLVSH_352NS_117NS	(0 << 5)
#घोषणा MAX9286_I2CMSTBT_837KBPS	(7 << 2)
#घोषणा MAX9286_I2CMSTBT_533KBPS	(6 << 2)
#घोषणा MAX9286_I2CMSTBT_339KBPS	(5 << 2)
#घोषणा MAX9286_I2CMSTBT_173KBPS	(4 << 2)
#घोषणा MAX9286_I2CMSTBT_105KBPS	(3 << 2)
#घोषणा MAX9286_I2CMSTBT_84KBPS		(2 << 2)
#घोषणा MAX9286_I2CMSTBT_28KBPS		(1 << 2)
#घोषणा MAX9286_I2CMSTBT_8KBPS		(0 << 2)
#घोषणा MAX9286_I2CSLVTO_NONE		(3 << 0)
#घोषणा MAX9286_I2CSLVTO_1024US		(2 << 0)
#घोषणा MAX9286_I2CSLVTO_256US		(1 << 0)
#घोषणा MAX9286_I2CSLVTO_64US		(0 << 0)
/* Register 0x3b */
#घोषणा MAX9286_REV_TRF(n)		((n) << 4)
#घोषणा MAX9286_REV_AMP(n)		((((n) - 30) / 10) << 1) /* in mV */
#घोषणा MAX9286_REV_AMP_X		BIT(0)
/* Register 0x3f */
#घोषणा MAX9286_EN_REV_CFG		BIT(6)
#घोषणा MAX9286_REV_FLEN(n)		((n) - 20)
/* Register 0x49 */
#घोषणा MAX9286_VIDEO_DETECT_MASK	0x0f
/* Register 0x69 */
#घोषणा MAX9286_LFLTBMONMASKED		BIT(7)
#घोषणा MAX9286_LOCKMONMASKED		BIT(6)
#घोषणा MAX9286_AUTOCOMBACKEN		BIT(5)
#घोषणा MAX9286_AUTOMASKEN		BIT(4)
#घोषणा MAX9286_MASKLINK(n)		((n) << 0)

/*
 * The sink and source pads are created to match the OF graph port numbers so
 * that their indexes can be used पूर्णांकerchangeably.
 */
#घोषणा MAX9286_NUM_GMSL		4
#घोषणा MAX9286_N_SINKS			4
#घोषणा MAX9286_N_PADS			5
#घोषणा MAX9286_SRC_PAD			4

काष्ठा max9286_source अणु
	काष्ठा v4l2_subdev *sd;
	काष्ठा fwnode_handle *fwnode;
पूर्ण;

काष्ठा max9286_asd अणु
	काष्ठा v4l2_async_subdev base;
	काष्ठा max9286_source *source;
पूर्ण;

अटल अंतरभूत काष्ठा max9286_asd *to_max9286_asd(काष्ठा v4l2_async_subdev *asd)
अणु
	वापस container_of(asd, काष्ठा max9286_asd, base);
पूर्ण

काष्ठा max9286_priv अणु
	काष्ठा i2c_client *client;
	काष्ठा gpio_desc *gpiod_pwdn;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pads[MAX9286_N_PADS];
	काष्ठा regulator *regulator;

	काष्ठा gpio_chip gpio;
	u8 gpio_state;

	काष्ठा i2c_mux_core *mux;
	अचिन्हित पूर्णांक mux_channel;
	bool mux_खोलो;

	u32 reverse_channel_mv;

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *pixelrate;

	काष्ठा v4l2_mbus_framefmt fmt[MAX9286_N_SINKS];

	/* Protects controls and fmt काष्ठाures */
	काष्ठा mutex mutex;

	अचिन्हित पूर्णांक nsources;
	अचिन्हित पूर्णांक source_mask;
	अचिन्हित पूर्णांक route_mask;
	अचिन्हित पूर्णांक bound_sources;
	अचिन्हित पूर्णांक csi2_data_lanes;
	काष्ठा max9286_source sources[MAX9286_NUM_GMSL];
	काष्ठा v4l2_async_notअगरier notअगरier;
पूर्ण;

अटल काष्ठा max9286_source *next_source(काष्ठा max9286_priv *priv,
					  काष्ठा max9286_source *source)
अणु
	अगर (!source)
		source = &priv->sources[0];
	अन्यथा
		source++;

	क्रम (; source < &priv->sources[MAX9286_NUM_GMSL]; source++) अणु
		अगर (source->fwnode)
			वापस source;
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा क्रम_each_source(priv, source) \
	क्रम ((source) = शून्य; ((source) = next_source((priv), (source))); )

#घोषणा to_index(priv, source) ((source) - &(priv)->sources[0])

अटल अंतरभूत काष्ठा max9286_priv *sd_to_max9286(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा max9286_priv, sd);
पूर्ण

/* -----------------------------------------------------------------------------
 * I2C IO
 */

अटल पूर्णांक max9286_पढ़ो(काष्ठा max9286_priv *priv, u8 reg)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(priv->client, reg);
	अगर (ret < 0)
		dev_err(&priv->client->dev,
			"%s: register 0x%02x read failed (%d)\n",
			__func__, reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक max9286_ग_लिखो(काष्ठा max9286_priv *priv, u8 reg, u8 val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(priv->client, reg, val);
	अगर (ret < 0)
		dev_err(&priv->client->dev,
			"%s: register 0x%02x write failed (%d)\n",
			__func__, reg, ret);

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * I2C Multiplexer
 */

अटल व्योम max9286_i2c_mux_configure(काष्ठा max9286_priv *priv, u8 conf)
अणु
	max9286_ग_लिखो(priv, 0x0a, conf);

	/*
	 * We must sleep after any change to the क्रमward or reverse channel
	 * configuration.
	 */
	usleep_range(3000, 5000);
पूर्ण

अटल व्योम max9286_i2c_mux_खोलो(काष्ठा max9286_priv *priv)
अणु
	/* Open all channels on the MAX9286 */
	max9286_i2c_mux_configure(priv, 0xff);

	priv->mux_खोलो = true;
पूर्ण

अटल व्योम max9286_i2c_mux_बंद(काष्ठा max9286_priv *priv)
अणु
	/*
	 * Ensure that both the क्रमward and reverse channel are disabled on the
	 * mux, and that the channel ID is invalidated to ensure we reconfigure
	 * on the next max9286_i2c_mux_select() call.
	 */
	max9286_i2c_mux_configure(priv, 0x00);

	priv->mux_खोलो = false;
	priv->mux_channel = -1;
पूर्ण

अटल पूर्णांक max9286_i2c_mux_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा max9286_priv *priv = i2c_mux_priv(muxc);

	/* Channel select is disabled when configured in the खोलोed state. */
	अगर (priv->mux_खोलो)
		वापस 0;

	अगर (priv->mux_channel == chan)
		वापस 0;

	priv->mux_channel = chan;

	max9286_i2c_mux_configure(priv,
				  MAX9286_FWDCCEN(chan) |
				  MAX9286_REVCCEN(chan));

	वापस 0;
पूर्ण

अटल पूर्णांक max9286_i2c_mux_init(काष्ठा max9286_priv *priv)
अणु
	काष्ठा max9286_source *source;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(priv->client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		वापस -ENODEV;

	priv->mux = i2c_mux_alloc(priv->client->adapter, &priv->client->dev,
				  priv->nsources, 0, I2C_MUX_LOCKED,
				  max9286_i2c_mux_select, शून्य);
	अगर (!priv->mux)
		वापस -ENOMEM;

	priv->mux->priv = priv;

	क्रम_each_source(priv, source) अणु
		अचिन्हित पूर्णांक index = to_index(priv, source);

		ret = i2c_mux_add_adapter(priv->mux, 0, index, 0);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	i2c_mux_del_adapters(priv->mux);
	वापस ret;
पूर्ण

अटल व्योम max9286_configure_i2c(काष्ठा max9286_priv *priv, bool localack)
अणु
	u8 config = MAX9286_I2CSLVSH_469NS_234NS | MAX9286_I2CSLVTO_1024US |
		    MAX9286_I2CMSTBT_105KBPS;

	अगर (localack)
		config |= MAX9286_I2CLOCACK;

	max9286_ग_लिखो(priv, 0x34, config);
	usleep_range(3000, 5000);
पूर्ण

अटल व्योम max9286_reverse_channel_setup(काष्ठा max9286_priv *priv,
					  अचिन्हित पूर्णांक chan_amplitude)
अणु
	/* Reverse channel transmission समय: शेष to 1. */
	u8 chan_config = MAX9286_REV_TRF(1);

	/*
	 * Reverse channel setup.
	 *
	 * - Enable custom reverse channel configuration (through रेजिस्टर 0x3f)
	 *   and set the first pulse length to 35 घड़ी cycles.
	 * - Adjust reverse channel amplitude: values > 130 are programmed
	 *   using the additional +100mV REV_AMP_X boost flag
	 */
	max9286_ग_लिखो(priv, 0x3f, MAX9286_EN_REV_CFG | MAX9286_REV_FLEN(35));

	अगर (chan_amplitude > 100) अणु
		/* It is not possible to express values (100 < x < 130) */
		chan_amplitude = max(30U, chan_amplitude - 100);
		chan_config |= MAX9286_REV_AMP_X;
	पूर्ण
	max9286_ग_लिखो(priv, 0x3b, chan_config | MAX9286_REV_AMP(chan_amplitude));
	usleep_range(2000, 2500);
पूर्ण

/*
 * max9286_check_video_links() - Make sure video links are detected and locked
 *
 * Perक्रमms safety checks on video link status. Make sure they are detected
 * and all enabled links are locked.
 *
 * Returns 0 क्रम success, -EIO क्रम errors.
 */
अटल पूर्णांक max9286_check_video_links(काष्ठा max9286_priv *priv)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/*
	 * Make sure valid video links are detected.
	 * The delay is not अक्षरacterized in de-serializer manual, रुको up
	 * to 5 ms.
	 */
	क्रम (i = 0; i < 10; i++) अणु
		ret = max9286_पढ़ो(priv, 0x49);
		अगर (ret < 0)
			वापस -EIO;

		अगर ((ret & MAX9286_VIDEO_DETECT_MASK) == priv->source_mask)
			अवरोध;

		usleep_range(350, 500);
	पूर्ण

	अगर (i == 10) अणु
		dev_err(&priv->client->dev,
			"Unable to detect video links: 0x%02x\n", ret);
		वापस -EIO;
	पूर्ण

	/* Make sure all enabled links are locked (4ms max). */
	क्रम (i = 0; i < 10; i++) अणु
		ret = max9286_पढ़ो(priv, 0x27);
		अगर (ret < 0)
			वापस -EIO;

		अगर (ret & MAX9286_LOCKED)
			अवरोध;

		usleep_range(350, 450);
	पूर्ण

	अगर (i == 10) अणु
		dev_err(&priv->client->dev, "Not all enabled links locked\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * max9286_check_config_link() - Detect and रुको क्रम configuration links
 *
 * Determine अगर the configuration channel is up and settled क्रम a link.
 *
 * Returns 0 क्रम success, -EIO क्रम errors.
 */
अटल पूर्णांक max9286_check_config_link(काष्ठा max9286_priv *priv,
				     अचिन्हित पूर्णांक source_mask)
अणु
	अचिन्हित पूर्णांक conflink_mask = (source_mask & 0x0f) << 4;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/*
	 * Make sure requested configuration links are detected.
	 * The delay is not अक्षरacterized in the chip manual: रुको up
	 * to 5 milliseconds.
	 */
	क्रम (i = 0; i < 10; i++) अणु
		ret = max9286_पढ़ो(priv, 0x49);
		अगर (ret < 0)
			वापस -EIO;

		ret &= 0xf0;
		अगर (ret == conflink_mask)
			अवरोध;

		usleep_range(350, 500);
	पूर्ण

	अगर (ret != conflink_mask) अणु
		dev_err(&priv->client->dev,
			"Unable to detect configuration links: 0x%02x expected 0x%02x\n",
			ret, conflink_mask);
		वापस -EIO;
	पूर्ण

	dev_info(&priv->client->dev,
		 "Successfully detected configuration links after %u loops: 0x%02x\n",
		 i, conflink_mask);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 Subdev
 */

अटल पूर्णांक max9286_set_pixelrate(काष्ठा max9286_priv *priv)
अणु
	काष्ठा max9286_source *source = शून्य;
	u64 pixelrate = 0;

	क्रम_each_source(priv, source) अणु
		काष्ठा v4l2_ctrl *ctrl;
		u64 source_rate = 0;

		/* Pixel rate is mandatory to be reported by sources. */
		ctrl = v4l2_ctrl_find(source->sd->ctrl_handler,
				      V4L2_CID_PIXEL_RATE);
		अगर (!ctrl) अणु
			pixelrate = 0;
			अवरोध;
		पूर्ण

		/* All source must report the same pixel rate. */
		source_rate = v4l2_ctrl_g_ctrl_पूर्णांक64(ctrl);
		अगर (!pixelrate) अणु
			pixelrate = source_rate;
		पूर्ण अन्यथा अगर (pixelrate != source_rate) अणु
			dev_err(&priv->client->dev,
				"Unable to calculate pixel rate\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!pixelrate) अणु
		dev_err(&priv->client->dev,
			"No pixel rate control available in sources\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * The CSI-2 transmitter pixel rate is the single source rate multiplied
	 * by the number of available sources.
	 */
	वापस v4l2_ctrl_s_ctrl_पूर्णांक64(priv->pixelrate,
				      pixelrate * priv->nsources);
पूर्ण

अटल पूर्णांक max9286_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				काष्ठा v4l2_subdev *subdev,
				काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा max9286_priv *priv = sd_to_max9286(notअगरier->sd);
	काष्ठा max9286_source *source = to_max9286_asd(asd)->source;
	अचिन्हित पूर्णांक index = to_index(priv, source);
	अचिन्हित पूर्णांक src_pad;
	पूर्णांक ret;

	ret = media_entity_get_fwnode_pad(&subdev->entity,
					  source->fwnode,
					  MEDIA_PAD_FL_SOURCE);
	अगर (ret < 0) अणु
		dev_err(&priv->client->dev,
			"Failed to find pad for %s\n", subdev->name);
		वापस ret;
	पूर्ण

	priv->bound_sources |= BIT(index);
	source->sd = subdev;
	src_pad = ret;

	ret = media_create_pad_link(&source->sd->entity, src_pad,
				    &priv->sd.entity, index,
				    MEDIA_LNK_FL_ENABLED |
				    MEDIA_LNK_FL_IMMUTABLE);
	अगर (ret) अणु
		dev_err(&priv->client->dev,
			"Unable to link %s:%u -> %s:%u\n",
			source->sd->name, src_pad, priv->sd.name, index);
		वापस ret;
	पूर्ण

	dev_dbg(&priv->client->dev, "Bound %s pad: %u on index %u\n",
		subdev->name, src_pad, index);

	/*
	 * We can only रेजिस्टर v4l2_async_notअगरiers, which करो not provide a
	 * means to रेजिस्टर a complete callback. bound_sources allows us to
	 * identअगरy when all remote serializers have completed their probe.
	 */
	अगर (priv->bound_sources != priv->source_mask)
		वापस 0;

	/*
	 * All enabled sources have probed and enabled their reverse control
	 * channels:
	 *
	 * - Increase the reverse channel amplitude to compensate क्रम the
	 *   remote ends high threshold, अगर not करोne alपढ़ोy
	 * - Verअगरy all configuration links are properly detected
	 * - Disable स्वतः-ack as communication on the control channel are now
	 *   stable.
	 */
	अगर (priv->reverse_channel_mv < 170)
		max9286_reverse_channel_setup(priv, 170);
	max9286_check_config_link(priv, priv->source_mask);

	/*
	 * Re-configure I2C with local acknowledge disabled after cameras have
	 * probed.
	 */
	max9286_configure_i2c(priv, false);

	वापस max9286_set_pixelrate(priv);
पूर्ण

अटल व्योम max9286_notअगरy_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
				  काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा max9286_priv *priv = sd_to_max9286(notअगरier->sd);
	काष्ठा max9286_source *source = to_max9286_asd(asd)->source;
	अचिन्हित पूर्णांक index = to_index(priv, source);

	source->sd = शून्य;
	priv->bound_sources &= ~BIT(index);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations max9286_notअगरy_ops = अणु
	.bound = max9286_notअगरy_bound,
	.unbind = max9286_notअगरy_unbind,
पूर्ण;

अटल पूर्णांक max9286_v4l2_notअगरier_रेजिस्टर(काष्ठा max9286_priv *priv)
अणु
	काष्ठा device *dev = &priv->client->dev;
	काष्ठा max9286_source *source = शून्य;
	पूर्णांक ret;

	अगर (!priv->nsources)
		वापस 0;

	v4l2_async_notअगरier_init(&priv->notअगरier);

	क्रम_each_source(priv, source) अणु
		अचिन्हित पूर्णांक i = to_index(priv, source);
		काष्ठा max9286_asd *mas;

		mas = v4l2_async_notअगरier_add_fwnode_subdev(&priv->notअगरier,
							    source->fwnode,
							    काष्ठा max9286_asd);
		अगर (IS_ERR(mas)) अणु
			dev_err(dev, "Failed to add subdev for source %u: %ld",
				i, PTR_ERR(mas));
			v4l2_async_notअगरier_cleanup(&priv->notअगरier);
			वापस PTR_ERR(mas);
		पूर्ण

		mas->source = source;
	पूर्ण

	priv->notअगरier.ops = &max9286_notअगरy_ops;

	ret = v4l2_async_subdev_notअगरier_रेजिस्टर(&priv->sd, &priv->notअगरier);
	अगर (ret) अणु
		dev_err(dev, "Failed to register subdev_notifier");
		v4l2_async_notअगरier_cleanup(&priv->notअगरier);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max9286_v4l2_notअगरier_unरेजिस्टर(काष्ठा max9286_priv *priv)
अणु
	अगर (!priv->nsources)
		वापस;

	v4l2_async_notअगरier_unरेजिस्टर(&priv->notअगरier);
	v4l2_async_notअगरier_cleanup(&priv->notअगरier);
पूर्ण

अटल पूर्णांक max9286_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा max9286_priv *priv = sd_to_max9286(sd);
	काष्ठा max9286_source *source;
	अचिन्हित पूर्णांक i;
	bool sync = false;
	पूर्णांक ret;

	अगर (enable) अणु
		/*
		 * The frame sync between cameras is transmitted across the
		 * reverse channel as GPIO. We must खोलो all channels जबतक
		 * streaming to allow this synchronisation संकेत to be shared.
		 */
		max9286_i2c_mux_खोलो(priv);

		/* Start all cameras. */
		क्रम_each_source(priv, source) अणु
			ret = v4l2_subdev_call(source->sd, video, s_stream, 1);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = max9286_check_video_links(priv);
		अगर (ret)
			वापस ret;

		/*
		 * Wait until frame synchronization is locked.
		 *
		 * Manual says frame sync locking should take ~6 VTS.
		 * From practical experience at least 8 are required. Give
		 * 12 complete frames समय (~400ms at 30 fps) to achieve frame
		 * locking beक्रमe वापसing error.
		 */
		क्रम (i = 0; i < 40; i++) अणु
			अगर (max9286_पढ़ो(priv, 0x31) & MAX9286_FSYNC_LOCKED) अणु
				sync = true;
				अवरोध;
			पूर्ण
			usleep_range(9000, 11000);
		पूर्ण

		अगर (!sync) अणु
			dev_err(&priv->client->dev,
				"Failed to get frame synchronization\n");
			वापस -EXDEV; /* Invalid cross-device link */
		पूर्ण

		/*
		 * Enable CSI output, VC set according to link number.
		 * Bit 7 must be set (chip manual says it's 0 and reserved).
		 */
		max9286_ग_लिखो(priv, 0x15, 0x80 | MAX9286_VCTYPE |
			      MAX9286_CSIOUTEN | MAX9286_0X15_RESV);
	पूर्ण अन्यथा अणु
		max9286_ग_लिखो(priv, 0x15, MAX9286_VCTYPE | MAX9286_0X15_RESV);

		/* Stop all cameras. */
		क्रम_each_source(priv, source)
			v4l2_subdev_call(source->sd, video, s_stream, 0);

		max9286_i2c_mux_बंद(priv);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max9286_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_UYVY8_1X16;

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
max9286_get_pad_क्रमmat(काष्ठा max9286_priv *priv,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       अचिन्हित पूर्णांक pad, u32 which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&priv->sd, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &priv->fmt[pad];
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक max9286_set_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा max9286_priv *priv = sd_to_max9286(sd);
	काष्ठा v4l2_mbus_framefmt *cfg_fmt;

	अगर (क्रमmat->pad == MAX9286_SRC_PAD)
		वापस -EINVAL;

	/* Refuse non YUV422 क्रमmats as we hardcode DT to 8 bit YUV422 */
	चयन (क्रमmat->क्रमmat.code) अणु
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_VYUY8_1X16:
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
	हाल MEDIA_BUS_FMT_YVYU8_1X16:
		अवरोध;
	शेष:
		क्रमmat->क्रमmat.code = MEDIA_BUS_FMT_UYVY8_1X16;
		अवरोध;
	पूर्ण

	cfg_fmt = max9286_get_pad_क्रमmat(priv, cfg, क्रमmat->pad, क्रमmat->which);
	अगर (!cfg_fmt)
		वापस -EINVAL;

	mutex_lock(&priv->mutex);
	*cfg_fmt = क्रमmat->क्रमmat;
	mutex_unlock(&priv->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक max9286_get_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा max9286_priv *priv = sd_to_max9286(sd);
	काष्ठा v4l2_mbus_framefmt *cfg_fmt;
	अचिन्हित पूर्णांक pad = क्रमmat->pad;

	/*
	 * Multiplexed Stream Support: Support link validation by वापसing the
	 * क्रमmat of the first bound link. All links must have the same क्रमmat,
	 * as we करो not support mixing and matching of cameras connected to the
	 * max9286.
	 */
	अगर (pad == MAX9286_SRC_PAD)
		pad = __ffs(priv->bound_sources);

	cfg_fmt = max9286_get_pad_क्रमmat(priv, cfg, pad, क्रमmat->which);
	अगर (!cfg_fmt)
		वापस -EINVAL;

	mutex_lock(&priv->mutex);
	क्रमmat->क्रमmat = *cfg_fmt;
	mutex_unlock(&priv->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops max9286_video_ops = अणु
	.s_stream	= max9286_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops max9286_pad_ops = अणु
	.क्रमागत_mbus_code = max9286_क्रमागत_mbus_code,
	.get_fmt	= max9286_get_fmt,
	.set_fmt	= max9286_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops max9286_subdev_ops = अणु
	.video		= &max9286_video_ops,
	.pad		= &max9286_pad_ops,
पूर्ण;

अटल व्योम max9286_init_क्रमmat(काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->width		= 1280;
	fmt->height		= 800;
	fmt->code		= MEDIA_BUS_FMT_UYVY8_1X16;
	fmt->colorspace		= V4L2_COLORSPACE_SRGB;
	fmt->field		= V4L2_FIELD_NONE;
	fmt->ycbcr_enc		= V4L2_YCBCR_ENC_DEFAULT;
	fmt->quantization	= V4L2_QUANTIZATION_DEFAULT;
	fmt->xfer_func		= V4L2_XFER_FUNC_DEFAULT;
पूर्ण

अटल पूर्णांक max9286_खोलो(काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX9286_N_SINKS; i++) अणु
		क्रमmat = v4l2_subdev_get_try_क्रमmat(subdev, fh->pad, i);
		max9286_init_क्रमmat(क्रमmat);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops max9286_subdev_पूर्णांकernal_ops = अणु
	.खोलो = max9286_खोलो,
पूर्ण;

अटल पूर्णांक max9286_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	चयन (ctrl->id) अणु
	हाल V4L2_CID_PIXEL_RATE:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops max9286_ctrl_ops = अणु
	.s_ctrl = max9286_s_ctrl,
पूर्ण;

अटल पूर्णांक max9286_v4l2_रेजिस्टर(काष्ठा max9286_priv *priv)
अणु
	काष्ठा device *dev = &priv->client->dev;
	काष्ठा fwnode_handle *ep;
	पूर्णांक ret;
	पूर्णांक i;

	/* Register v4l2 async notअगरiers क्रम connected Camera subdevices */
	ret = max9286_v4l2_notअगरier_रेजिस्टर(priv);
	अगर (ret) अणु
		dev_err(dev, "Unable to register V4L2 async notifiers\n");
		वापस ret;
	पूर्ण

	/* Configure V4L2 क्रम the MAX9286 itself */

	क्रम (i = 0; i < MAX9286_N_SINKS; i++)
		max9286_init_क्रमmat(&priv->fmt[i]);

	v4l2_i2c_subdev_init(&priv->sd, priv->client, &max9286_subdev_ops);
	priv->sd.पूर्णांकernal_ops = &max9286_subdev_पूर्णांकernal_ops;
	priv->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	v4l2_ctrl_handler_init(&priv->ctrls, 1);
	priv->pixelrate = v4l2_ctrl_new_std(&priv->ctrls,
					    &max9286_ctrl_ops,
					    V4L2_CID_PIXEL_RATE,
					    1, पूर्णांक_उच्च, 1, 50000000);

	priv->sd.ctrl_handler = &priv->ctrls;
	ret = priv->ctrls.error;
	अगर (ret)
		जाओ err_async;

	priv->sd.entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;

	priv->pads[MAX9286_SRC_PAD].flags = MEDIA_PAD_FL_SOURCE;
	क्रम (i = 0; i < MAX9286_SRC_PAD; i++)
		priv->pads[i].flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&priv->sd.entity, MAX9286_N_PADS,
				     priv->pads);
	अगर (ret)
		जाओ err_async;

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(dev), MAX9286_SRC_PAD,
					     0, 0);
	अगर (!ep) अणु
		dev_err(dev, "Unable to retrieve endpoint on \"port@4\"\n");
		ret = -ENOENT;
		जाओ err_async;
	पूर्ण
	priv->sd.fwnode = ep;

	ret = v4l2_async_रेजिस्टर_subdev(&priv->sd);
	अगर (ret < 0) अणु
		dev_err(dev, "Unable to register subdevice\n");
		जाओ err_put_node;
	पूर्ण

	वापस 0;

err_put_node:
	fwnode_handle_put(ep);
err_async:
	max9286_v4l2_notअगरier_unरेजिस्टर(priv);

	वापस ret;
पूर्ण

अटल व्योम max9286_v4l2_unरेजिस्टर(काष्ठा max9286_priv *priv)
अणु
	fwnode_handle_put(priv->sd.fwnode);
	v4l2_async_unरेजिस्टर_subdev(&priv->sd);
	max9286_v4l2_notअगरier_unरेजिस्टर(priv);
पूर्ण

/* -----------------------------------------------------------------------------
 * Probe/Remove
 */

अटल पूर्णांक max9286_setup(काष्ठा max9286_priv *priv)
अणु
	/*
	 * Link ordering values क्रम all enabled links combinations. Orders must
	 * be asचिन्हित sequentially from 0 to the number of enabled links
	 * without leaving any hole क्रम disabled links. We thus assign orders to
	 * enabled links first, and use the reमुख्यing order values क्रम disabled
	 * links are all links must have a dअगरferent order value;
	 */
	अटल स्थिर u8 link_order[] = अणु
		(3 << 6) | (2 << 4) | (1 << 2) | (0 << 0), /* xxxx */
		(3 << 6) | (2 << 4) | (1 << 2) | (0 << 0), /* xxx0 */
		(3 << 6) | (2 << 4) | (0 << 2) | (1 << 0), /* xx0x */
		(3 << 6) | (2 << 4) | (1 << 2) | (0 << 0), /* xx10 */
		(3 << 6) | (0 << 4) | (2 << 2) | (1 << 0), /* x0xx */
		(3 << 6) | (1 << 4) | (2 << 2) | (0 << 0), /* x1x0 */
		(3 << 6) | (1 << 4) | (0 << 2) | (2 << 0), /* x10x */
		(3 << 6) | (1 << 4) | (1 << 2) | (0 << 0), /* x210 */
		(0 << 6) | (3 << 4) | (2 << 2) | (1 << 0), /* 0xxx */
		(1 << 6) | (3 << 4) | (2 << 2) | (0 << 0), /* 1xx0 */
		(1 << 6) | (3 << 4) | (0 << 2) | (2 << 0), /* 1x0x */
		(2 << 6) | (3 << 4) | (1 << 2) | (0 << 0), /* 2x10 */
		(1 << 6) | (0 << 4) | (3 << 2) | (2 << 0), /* 10xx */
		(2 << 6) | (1 << 4) | (3 << 2) | (0 << 0), /* 21x0 */
		(2 << 6) | (1 << 4) | (0 << 2) | (3 << 0), /* 210x */
		(3 << 6) | (2 << 4) | (1 << 2) | (0 << 0), /* 3210 */
	पूर्ण;

	/*
	 * Set the I2C bus speed.
	 *
	 * Enable I2C Local Acknowledge during the probe sequences of the camera
	 * only. This should be disabled after the mux is initialised.
	 */
	max9286_configure_i2c(priv, true);
	max9286_reverse_channel_setup(priv, priv->reverse_channel_mv);

	/*
	 * Enable GMSL links, mask unused ones and स्वतःdetect link
	 * used as CSI घड़ी source.
	 */
	max9286_ग_लिखो(priv, 0x00, MAX9286_MSTLINKSEL_AUTO | priv->route_mask);
	max9286_ग_लिखो(priv, 0x0b, link_order[priv->route_mask]);
	max9286_ग_लिखो(priv, 0x69, (0xf & ~priv->route_mask));

	/*
	 * Video क्रमmat setup:
	 * Disable CSI output, VC is set according to Link number.
	 */
	max9286_ग_लिखो(priv, 0x15, MAX9286_VCTYPE | MAX9286_0X15_RESV);

	/* Enable CSI-2 Lane D0-D3 only, DBL mode, YUV422 8-bit. */
	max9286_ग_लिखो(priv, 0x12, MAX9286_CSIDBL | MAX9286_DBL |
		      MAX9286_CSILANECNT(priv->csi2_data_lanes) |
		      MAX9286_DATATYPE_YUV422_8BIT);

	/* Automatic: FRAMESYNC taken from the slowest Link. */
	max9286_ग_लिखो(priv, 0x01, MAX9286_FSYNCMODE_INT_HIZ |
		      MAX9286_FSYNCMETH_AUTO);

	/* Enable HS/VS encoding, use D14/15 क्रम HS/VS, invert VS. */
	max9286_ग_लिखो(priv, 0x0c, MAX9286_HVEN | MAX9286_INVVS |
		      MAX9286_HVSRC_D14);

	/*
	 * The overlap winकरोw seems to provide additional validation by tracking
	 * the delay between vsync and frame sync, generating an error अगर the
	 * delay is bigger than the programmed winकरोw, though it's not yet clear
	 * what value should be set.
	 *
	 * As it's an optional value and can be disabled, we करो so by setting
	 * a 0 overlap value.
	 */
	max9286_ग_लिखो(priv, 0x63, 0);
	max9286_ग_लिखो(priv, 0x64, 0);

	/*
	 * Wait क्रम 2ms to allow the link to resynchronize after the
	 * configuration change.
	 */
	usleep_range(2000, 5000);

	वापस 0;
पूर्ण

अटल व्योम max9286_gpio_set(काष्ठा gpio_chip *chip,
			     अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा max9286_priv *priv = gpiochip_get_data(chip);

	अगर (value)
		priv->gpio_state |= BIT(offset);
	अन्यथा
		priv->gpio_state &= ~BIT(offset);

	max9286_ग_लिखो(priv, 0x0f, MAX9286_0X0F_RESERVED | priv->gpio_state);
पूर्ण

अटल पूर्णांक max9286_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा max9286_priv *priv = gpiochip_get_data(chip);

	वापस priv->gpio_state & BIT(offset);
पूर्ण

अटल पूर्णांक max9286_रेजिस्टर_gpio(काष्ठा max9286_priv *priv)
अणु
	काष्ठा device *dev = &priv->client->dev;
	काष्ठा gpio_chip *gpio = &priv->gpio;
	पूर्णांक ret;

	/* Configure the GPIO */
	gpio->label = dev_name(dev);
	gpio->parent = dev;
	gpio->owner = THIS_MODULE;
	gpio->of_node = dev->of_node;
	gpio->ngpio = 2;
	gpio->base = -1;
	gpio->set = max9286_gpio_set;
	gpio->get = max9286_gpio_get;
	gpio->can_sleep = true;

	/* GPIO values शेष to high */
	priv->gpio_state = BIT(0) | BIT(1);

	ret = devm_gpiochip_add_data(dev, gpio, priv);
	अगर (ret)
		dev_err(dev, "Unable to create gpio_chip\n");

	वापस ret;
पूर्ण

अटल पूर्णांक max9286_init(काष्ठा device *dev)
अणु
	काष्ठा max9286_priv *priv;
	काष्ठा i2c_client *client;
	पूर्णांक ret;

	client = to_i2c_client(dev);
	priv = i2c_get_clientdata(client);

	/* Enable the bus घातer. */
	ret = regulator_enable(priv->regulator);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Unable to turn PoC on\n");
		वापस ret;
	पूर्ण

	ret = max9286_setup(priv);
	अगर (ret) अणु
		dev_err(dev, "Unable to setup max9286\n");
		जाओ err_regulator;
	पूर्ण

	/*
	 * Register all V4L2 पूर्णांकeractions क्रम the MAX9286 and notअगरiers क्रम
	 * any subdevices connected.
	 */
	ret = max9286_v4l2_रेजिस्टर(priv);
	अगर (ret) अणु
		dev_err(dev, "Failed to register with V4L2\n");
		जाओ err_regulator;
	पूर्ण

	ret = max9286_i2c_mux_init(priv);
	अगर (ret) अणु
		dev_err(dev, "Unable to initialize I2C multiplexer\n");
		जाओ err_v4l2_रेजिस्टर;
	पूर्ण

	/* Leave the mux channels disabled until they are selected. */
	max9286_i2c_mux_बंद(priv);

	वापस 0;

err_v4l2_रेजिस्टर:
	max9286_v4l2_unरेजिस्टर(priv);
err_regulator:
	regulator_disable(priv->regulator);

	वापस ret;
पूर्ण

अटल व्योम max9286_cleanup_dt(काष्ठा max9286_priv *priv)
अणु
	काष्ठा max9286_source *source;

	क्रम_each_source(priv, source) अणु
		fwnode_handle_put(source->fwnode);
		source->fwnode = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक max9286_parse_dt(काष्ठा max9286_priv *priv)
अणु
	काष्ठा device *dev = &priv->client->dev;
	काष्ठा device_node *i2c_mux;
	काष्ठा device_node *node = शून्य;
	अचिन्हित पूर्णांक i2c_mux_mask = 0;
	u32 reverse_channel_microvolt;

	/* Balance the of_node_put() perक्रमmed by of_find_node_by_name(). */
	of_node_get(dev->of_node);
	i2c_mux = of_find_node_by_name(dev->of_node, "i2c-mux");
	अगर (!i2c_mux) अणु
		dev_err(dev, "Failed to find i2c-mux node\n");
		वापस -EINVAL;
	पूर्ण

	/* Identअगरy which i2c-mux channels are enabled */
	क्रम_each_child_of_node(i2c_mux, node) अणु
		u32 id = 0;

		of_property_पढ़ो_u32(node, "reg", &id);
		अगर (id >= MAX9286_NUM_GMSL)
			जारी;

		अगर (!of_device_is_available(node)) अणु
			dev_dbg(dev, "Skipping disabled I2C bus port %u\n", id);
			जारी;
		पूर्ण

		i2c_mux_mask |= BIT(id);
	पूर्ण
	of_node_put(node);
	of_node_put(i2c_mux);

	/* Parse the endpoपूर्णांकs */
	क्रम_each_endpoपूर्णांक_of_node(dev->of_node, node) अणु
		काष्ठा max9286_source *source;
		काष्ठा of_endpoपूर्णांक ep;

		of_graph_parse_endpoपूर्णांक(node, &ep);
		dev_dbg(dev, "Endpoint %pOF on port %d",
			ep.local_node, ep.port);

		अगर (ep.port > MAX9286_NUM_GMSL) अणु
			dev_err(dev, "Invalid endpoint %s on port %d",
				of_node_full_name(ep.local_node), ep.port);
			जारी;
		पूर्ण

		/* For the source endpoपूर्णांक just parse the bus configuration. */
		अगर (ep.port == MAX9286_SRC_PAD) अणु
			काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
				.bus_type = V4L2_MBUS_CSI2_DPHY
			पूर्ण;
			पूर्णांक ret;

			ret = v4l2_fwnode_endpoपूर्णांक_parse(
					of_fwnode_handle(node), &vep);
			अगर (ret) अणु
				of_node_put(node);
				वापस ret;
			पूर्ण

			priv->csi2_data_lanes =
				vep.bus.mipi_csi2.num_data_lanes;

			जारी;
		पूर्ण

		/* Skip अगर the corresponding GMSL link is unavailable. */
		अगर (!(i2c_mux_mask & BIT(ep.port)))
			जारी;

		अगर (priv->sources[ep.port].fwnode) अणु
			dev_err(dev,
				"Multiple port endpoints are not supported: %d",
				ep.port);

			जारी;
		पूर्ण

		source = &priv->sources[ep.port];
		source->fwnode = fwnode_graph_get_remote_endpoपूर्णांक(
						of_fwnode_handle(node));
		अगर (!source->fwnode) अणु
			dev_err(dev,
				"Endpoint %pOF has no remote endpoint connection\n",
				ep.local_node);

			जारी;
		पूर्ण

		priv->source_mask |= BIT(ep.port);
		priv->nsources++;
	पूर्ण
	of_node_put(node);

	/*
	 * Parse the initial value of the reverse channel amplitude from
	 * the firmware पूर्णांकerface and convert it to millivolts.
	 *
	 * Default it to 170mV क्रम backward compatibility with DTBs that करो not
	 * provide the property.
	 */
	अगर (of_property_पढ़ो_u32(dev->of_node,
				 "maxim,reverse-channel-microvolt",
				 &reverse_channel_microvolt))
		priv->reverse_channel_mv = 170;
	अन्यथा
		priv->reverse_channel_mv = reverse_channel_microvolt / 1000U;

	priv->route_mask = priv->source_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक max9286_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा max9286_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->mutex);

	priv->client = client;
	i2c_set_clientdata(client, priv);

	priv->gpiod_pwdn = devm_gpiod_get_optional(&client->dev, "enable",
						   GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->gpiod_pwdn))
		वापस PTR_ERR(priv->gpiod_pwdn);

	gpiod_set_consumer_name(priv->gpiod_pwdn, "max9286-pwdn");
	gpiod_set_value_cansleep(priv->gpiod_pwdn, 1);

	/* Wait at least 4ms beक्रमe the I2C lines latch to the address */
	अगर (priv->gpiod_pwdn)
		usleep_range(4000, 5000);

	/*
	 * The MAX9286 starts by शेष with all ports enabled, we disable all
	 * ports early to ensure that all channels are disabled अगर we error out
	 * and keep the bus consistent.
	 */
	max9286_i2c_mux_बंद(priv);

	/*
	 * The MAX9286 initialises with स्वतः-acknowledge enabled by शेष.
	 * This can be invasive to other transactions on the same bus, so
	 * disable it early. It will be enabled only as and when needed.
	 */
	max9286_configure_i2c(priv, false);

	ret = max9286_रेजिस्टर_gpio(priv);
	अगर (ret)
		जाओ err_घातerकरोwn;

	priv->regulator = devm_regulator_get(&client->dev, "poc");
	अगर (IS_ERR(priv->regulator)) अणु
		अगर (PTR_ERR(priv->regulator) != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Unable to get PoC regulator (%ld)\n",
				PTR_ERR(priv->regulator));
		ret = PTR_ERR(priv->regulator);
		जाओ err_घातerकरोwn;
	पूर्ण

	ret = max9286_parse_dt(priv);
	अगर (ret)
		जाओ err_घातerकरोwn;

	ret = max9286_init(&client->dev);
	अगर (ret < 0)
		जाओ err_cleanup_dt;

	वापस 0;

err_cleanup_dt:
	max9286_cleanup_dt(priv);
err_घातerकरोwn:
	gpiod_set_value_cansleep(priv->gpiod_pwdn, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक max9286_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा max9286_priv *priv = i2c_get_clientdata(client);

	i2c_mux_del_adapters(priv->mux);

	max9286_v4l2_unरेजिस्टर(priv);

	regulator_disable(priv->regulator);

	gpiod_set_value_cansleep(priv->gpiod_pwdn, 0);

	max9286_cleanup_dt(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id max9286_dt_ids[] = अणु
	अणु .compatible = "maxim,max9286" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max9286_dt_ids);

अटल काष्ठा i2c_driver max9286_i2c_driver = अणु
	.driver	= अणु
		.name		= "max9286",
		.of_match_table	= of_match_ptr(max9286_dt_ids),
	पूर्ण,
	.probe_new	= max9286_probe,
	.हटाओ		= max9286_हटाओ,
पूर्ण;

module_i2c_driver(max9286_i2c_driver);

MODULE_DESCRIPTION("Maxim MAX9286 GMSL Deserializer Driver");
MODULE_AUTHOR("Jacopo Mondi, Kieran Bingham, Laurent Pinchart, Niklas Sथघderlund, Vladimir Barinov");
MODULE_LICENSE("GPL");
