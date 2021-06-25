<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Elonics E4000 silicon tuner driver
 *
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#समावेश "e4000_priv.h"

अटल पूर्णांक e4000_init(काष्ठा e4000_dev *dev)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	/* reset */
	ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x01);
	अगर (ret)
		जाओ err;

	/* disable output घड़ी */
	ret = regmap_ग_लिखो(dev->regmap, 0x06, 0x00);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x7a, 0x96);
	अगर (ret)
		जाओ err;

	/* configure gains */
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x7e, "\x01\xfe", 2);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x82, 0x00);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x24, 0x05);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x87, "\x20\x01", 2);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x9f, "\x7f\x07", 2);
	अगर (ret)
		जाओ err;

	/* DC offset control */
	ret = regmap_ग_लिखो(dev->regmap, 0x2d, 0x1f);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x70, "\x01\x01", 2);
	अगर (ret)
		जाओ err;

	/* gain control */
	ret = regmap_ग_लिखो(dev->regmap, 0x1a, 0x17);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x1f, 0x1a);
	अगर (ret)
		जाओ err;

	dev->active = true;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक e4000_sleep(काष्ठा e4000_dev *dev)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	dev->active = false;

	ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x00);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक e4000_set_params(काष्ठा e4000_dev *dev)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक भाग_n, k, k_cw, भाग_out;
	u64 f_vco;
	u8 buf[5], i_data[4], q_data[4];

	अगर (!dev->active) अणु
		dev_dbg(&client->dev, "tuner is sleeping\n");
		वापस 0;
	पूर्ण

	/* gain control manual */
	ret = regmap_ग_लिखो(dev->regmap, 0x1a, 0x00);
	अगर (ret)
		जाओ err;

	/*
	 * Fractional-N synthesizer
	 *
	 *           +----------------------------+
	 *           v                            |
	 *  Fref   +----+     +-------+         +------+     +---+
	 * ------> | PD | --> |  VCO  | ------> | /N.F | <-- | K |
	 *         +----+     +-------+         +------+     +---+
	 *                      |
	 *                      |
	 *                      v
	 *                    +-------+  Fout
	 *                    | /Rout | ------>
	 *                    +-------+
	 */
	क्रम (i = 0; i < ARRAY_SIZE(e4000_pll_lut); i++) अणु
		अगर (dev->f_frequency <= e4000_pll_lut[i].freq)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(e4000_pll_lut)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	#घोषणा F_REF dev->clk
	भाग_out = e4000_pll_lut[i].भाग_out;
	f_vco = (u64) dev->f_frequency * भाग_out;
	/* calculate PLL पूर्णांकeger and fractional control word */
	भाग_n = भाग_u64_rem(f_vco, F_REF, &k);
	k_cw = भाग_u64((u64) k * 0x10000, F_REF);

	dev_dbg(&client->dev,
		"frequency=%u bandwidth=%u f_vco=%llu F_REF=%u div_n=%u k=%u k_cw=%04x div_out=%u\n",
		dev->f_frequency, dev->f_bandwidth, f_vco, F_REF, भाग_n, k,
		k_cw, भाग_out);

	buf[0] = भाग_n;
	buf[1] = (k_cw >> 0) & 0xff;
	buf[2] = (k_cw >> 8) & 0xff;
	buf[3] = 0x00;
	buf[4] = e4000_pll_lut[i].भाग_out_reg;
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x09, buf, 5);
	अगर (ret)
		जाओ err;

	/* LNA filter (RF filter) */
	क्रम (i = 0; i < ARRAY_SIZE(e400_lna_filter_lut); i++) अणु
		अगर (dev->f_frequency <= e400_lna_filter_lut[i].freq)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(e400_lna_filter_lut)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, 0x10, e400_lna_filter_lut[i].val);
	अगर (ret)
		जाओ err;

	/* IF filters */
	क्रम (i = 0; i < ARRAY_SIZE(e4000_अगर_filter_lut); i++) अणु
		अगर (dev->f_bandwidth <= e4000_अगर_filter_lut[i].freq)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(e4000_अगर_filter_lut)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	buf[0] = e4000_अगर_filter_lut[i].reg11_val;
	buf[1] = e4000_अगर_filter_lut[i].reg12_val;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x11, buf, 2);
	अगर (ret)
		जाओ err;

	/* frequency band */
	क्रम (i = 0; i < ARRAY_SIZE(e4000_band_lut); i++) अणु
		अगर (dev->f_frequency <= e4000_band_lut[i].freq)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(e4000_band_lut)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, 0x07, e4000_band_lut[i].reg07_val);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x78, e4000_band_lut[i].reg78_val);
	अगर (ret)
		जाओ err;

	/* DC offset */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (i == 0)
			ret = regmap_bulk_ग_लिखो(dev->regmap, 0x15, "\x00\x7e\x24", 3);
		अन्यथा अगर (i == 1)
			ret = regmap_bulk_ग_लिखो(dev->regmap, 0x15, "\x00\x7f", 2);
		अन्यथा अगर (i == 2)
			ret = regmap_bulk_ग_लिखो(dev->regmap, 0x15, "\x01", 1);
		अन्यथा
			ret = regmap_bulk_ग_लिखो(dev->regmap, 0x16, "\x7e", 1);

		अगर (ret)
			जाओ err;

		ret = regmap_ग_लिखो(dev->regmap, 0x29, 0x01);
		अगर (ret)
			जाओ err;

		ret = regmap_bulk_पढ़ो(dev->regmap, 0x2a, buf, 3);
		अगर (ret)
			जाओ err;

		i_data[i] = (((buf[2] >> 0) & 0x3) << 6) | (buf[0] & 0x3f);
		q_data[i] = (((buf[2] >> 4) & 0x3) << 6) | (buf[1] & 0x3f);
	पूर्ण

	swap(q_data[2], q_data[3]);
	swap(i_data[2], i_data[3]);

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x50, q_data, 4);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x60, i_data, 4);
	अगर (ret)
		जाओ err;

	/* gain control स्वतः */
	ret = regmap_ग_लिखो(dev->regmap, 0x1a, 0x17);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

/*
 * V4L2 API
 */
#अगर IS_ENABLED(CONFIG_VIDEO_V4L2)
अटल स्थिर काष्ठा v4l2_frequency_band bands[] = अणु
	अणु
		.type = V4L2_TUNER_RF,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =    59000000,
		.rangehigh  =  1105000000,
	पूर्ण,
	अणु
		.type = V4L2_TUNER_RF,
		.index = 1,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =  1249000000,
		.rangehigh  =  2208000000UL,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा e4000_dev *e4000_subdev_to_dev(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा e4000_dev, sd);
पूर्ण

अटल पूर्णांक e4000_standby(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा e4000_dev *dev = e4000_subdev_to_dev(sd);
	पूर्णांक ret;

	ret = e4000_sleep(dev);
	अगर (ret)
		वापस ret;

	वापस e4000_set_params(dev);
पूर्ण

अटल पूर्णांक e4000_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *v)
अणु
	काष्ठा e4000_dev *dev = e4000_subdev_to_dev(sd);
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "index=%d\n", v->index);

	strscpy(v->name, "Elonics E4000", माप(v->name));
	v->type = V4L2_TUNER_RF;
	v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
	v->rangelow  = bands[0].rangelow;
	v->rangehigh = bands[1].rangehigh;
	वापस 0;
पूर्ण

अटल पूर्णांक e4000_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा e4000_dev *dev = e4000_subdev_to_dev(sd);
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "index=%d\n", v->index);
	वापस 0;
पूर्ण

अटल पूर्णांक e4000_g_frequency(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_frequency *f)
अणु
	काष्ठा e4000_dev *dev = e4000_subdev_to_dev(sd);
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "tuner=%d\n", f->tuner);
	f->frequency = dev->f_frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक e4000_s_frequency(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा e4000_dev *dev = e4000_subdev_to_dev(sd);
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "tuner=%d type=%d frequency=%u\n",
		f->tuner, f->type, f->frequency);

	dev->f_frequency = clamp_t(अचिन्हित पूर्णांक, f->frequency,
				   bands[0].rangelow, bands[1].rangehigh);
	वापस e4000_set_params(dev);
पूर्ण

अटल पूर्णांक e4000_क्रमागत_freq_bands(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा e4000_dev *dev = e4000_subdev_to_dev(sd);
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "tuner=%d type=%d index=%d\n",
		band->tuner, band->type, band->index);

	अगर (band->index >= ARRAY_SIZE(bands))
		वापस -EINVAL;

	band->capability = bands[band->index].capability;
	band->rangelow = bands[band->index].rangelow;
	band->rangehigh = bands[band->index].rangehigh;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops e4000_subdev_tuner_ops = अणु
	.standby                  = e4000_standby,
	.g_tuner                  = e4000_g_tuner,
	.s_tuner                  = e4000_s_tuner,
	.g_frequency              = e4000_g_frequency,
	.s_frequency              = e4000_s_frequency,
	.क्रमागत_freq_bands          = e4000_क्रमागत_freq_bands,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops e4000_subdev_ops = अणु
	.tuner                    = &e4000_subdev_tuner_ops,
पूर्ण;

अटल पूर्णांक e4000_set_lna_gain(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा e4000_dev *dev = fe->tuner_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 u8पंचांगp;

	dev_dbg(&client->dev, "lna auto=%d->%d val=%d->%d\n",
		dev->lna_gain_स्वतः->cur.val, dev->lna_gain_स्वतः->val,
		dev->lna_gain->cur.val, dev->lna_gain->val);

	अगर (dev->lna_gain_स्वतः->val && dev->अगर_gain_स्वतः->cur.val)
		u8पंचांगp = 0x17;
	अन्यथा अगर (dev->lna_gain_स्वतः->val)
		u8पंचांगp = 0x19;
	अन्यथा अगर (dev->अगर_gain_स्वतः->cur.val)
		u8पंचांगp = 0x16;
	अन्यथा
		u8पंचांगp = 0x10;

	ret = regmap_ग_लिखो(dev->regmap, 0x1a, u8पंचांगp);
	अगर (ret)
		जाओ err;

	अगर (dev->lna_gain_स्वतः->val == false) अणु
		ret = regmap_ग_लिखो(dev->regmap, 0x14, dev->lna_gain->val);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक e4000_set_mixer_gain(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा e4000_dev *dev = fe->tuner_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 u8पंचांगp;

	dev_dbg(&client->dev, "mixer auto=%d->%d val=%d->%d\n",
		dev->mixer_gain_स्वतः->cur.val, dev->mixer_gain_स्वतः->val,
		dev->mixer_gain->cur.val, dev->mixer_gain->val);

	अगर (dev->mixer_gain_स्वतः->val)
		u8पंचांगp = 0x15;
	अन्यथा
		u8पंचांगp = 0x14;

	ret = regmap_ग_लिखो(dev->regmap, 0x20, u8पंचांगp);
	अगर (ret)
		जाओ err;

	अगर (dev->mixer_gain_स्वतः->val == false) अणु
		ret = regmap_ग_लिखो(dev->regmap, 0x15, dev->mixer_gain->val);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक e4000_set_अगर_gain(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा e4000_dev *dev = fe->tuner_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 buf[2];
	u8 u8पंचांगp;

	dev_dbg(&client->dev, "if auto=%d->%d val=%d->%d\n",
		dev->अगर_gain_स्वतः->cur.val, dev->अगर_gain_स्वतः->val,
		dev->अगर_gain->cur.val, dev->अगर_gain->val);

	अगर (dev->अगर_gain_स्वतः->val && dev->lna_gain_स्वतः->cur.val)
		u8पंचांगp = 0x17;
	अन्यथा अगर (dev->lna_gain_स्वतः->cur.val)
		u8पंचांगp = 0x19;
	अन्यथा अगर (dev->अगर_gain_स्वतः->val)
		u8पंचांगp = 0x16;
	अन्यथा
		u8पंचांगp = 0x10;

	ret = regmap_ग_लिखो(dev->regmap, 0x1a, u8पंचांगp);
	अगर (ret)
		जाओ err;

	अगर (dev->अगर_gain_स्वतः->val == false) अणु
		buf[0] = e4000_अगर_gain_lut[dev->अगर_gain->val].reg16_val;
		buf[1] = e4000_अगर_gain_lut[dev->अगर_gain->val].reg17_val;
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x16, buf, 2);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक e4000_pll_lock(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा e4000_dev *dev = fe->tuner_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uiपंचांगp;

	ret = regmap_पढ़ो(dev->regmap, 0x07, &uiपंचांगp);
	अगर (ret)
		जाओ err;

	dev->pll_lock->val = (uiपंचांगp & 0x01);

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक e4000_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा e4000_dev *dev = container_of(ctrl->handler, काष्ठा e4000_dev, hdl);
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	अगर (!dev->active)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल  V4L2_CID_RF_TUNER_PLL_LOCK:
		ret = e4000_pll_lock(dev->fe);
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "unknown ctrl: id=%d name=%s\n",
			ctrl->id, ctrl->name);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक e4000_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा e4000_dev *dev = container_of(ctrl->handler, काष्ठा e4000_dev, hdl);
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	अगर (!dev->active)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_RF_TUNER_BANDWIDTH_AUTO:
	हाल V4L2_CID_RF_TUNER_BANDWIDTH:
		/*
		 * TODO: Auto logic करोes not work 100% correctly as tuner driver
		 * करो not have inक्रमmation to calculate maximum suitable
		 * bandwidth. Calculating it is responsible of master driver.
		 */
		dev->f_bandwidth = dev->bandwidth->val;
		ret = e4000_set_params(dev);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_LNA_GAIN_AUTO:
	हाल  V4L2_CID_RF_TUNER_LNA_GAIN:
		ret = e4000_set_lna_gain(dev->fe);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_MIXER_GAIN_AUTO:
	हाल  V4L2_CID_RF_TUNER_MIXER_GAIN:
		ret = e4000_set_mixer_gain(dev->fe);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_IF_GAIN_AUTO:
	हाल  V4L2_CID_RF_TUNER_IF_GAIN:
		ret = e4000_set_अगर_gain(dev->fe);
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "unknown ctrl: id=%d name=%s\n",
			ctrl->id, ctrl->name);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops e4000_ctrl_ops = अणु
	.g_अस्थिर_ctrl = e4000_g_अस्थिर_ctrl,
	.s_ctrl = e4000_s_ctrl,
पूर्ण;
#पूर्ण_अगर

/*
 * DVB API
 */
अटल पूर्णांक e4000_dvb_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा e4000_dev *dev = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	dev->f_frequency = c->frequency;
	dev->f_bandwidth = c->bandwidth_hz;
	वापस e4000_set_params(dev);
पूर्ण

अटल पूर्णांक e4000_dvb_init(काष्ठा dvb_frontend *fe)
अणु
	वापस e4000_init(fe->tuner_priv);
पूर्ण

अटल पूर्णांक e4000_dvb_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस e4000_sleep(fe->tuner_priv);
पूर्ण

अटल पूर्णांक e4000_dvb_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	*frequency = 0; /* Zero-IF */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops e4000_dvb_tuner_ops = अणु
	.info = अणु
		.name              = "Elonics E4000",
		.frequency_min_hz  = 174 * MHz,
		.frequency_max_hz  = 862 * MHz,
	पूर्ण,

	.init = e4000_dvb_init,
	.sleep = e4000_dvb_sleep,
	.set_params = e4000_dvb_set_params,

	.get_अगर_frequency = e4000_dvb_get_अगर_frequency,
पूर्ण;

अटल पूर्णांक e4000_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा e4000_dev *dev;
	काष्ठा e4000_config *cfg = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = cfg->fe;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uiपंचांगp;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
	पूर्ण;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev->clk = cfg->घड़ी;
	dev->client = client;
	dev->fe = cfg->fe;
	dev->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	/* check अगर the tuner is there */
	ret = regmap_पढ़ो(dev->regmap, 0x02, &uiपंचांगp);
	अगर (ret)
		जाओ err_kमुक्त;

	dev_dbg(&client->dev, "chip id=%02x\n", uiपंचांगp);

	अगर (uiपंचांगp != 0x40) अणु
		ret = -ENODEV;
		जाओ err_kमुक्त;
	पूर्ण

	/* put sleep as chip seems to be in normal mode by शेष */
	ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x00);
	अगर (ret)
		जाओ err_kमुक्त;

#अगर IS_ENABLED(CONFIG_VIDEO_V4L2)
	/* Register controls */
	v4l2_ctrl_handler_init(&dev->hdl, 9);
	dev->bandwidth_स्वतः = v4l2_ctrl_new_std(&dev->hdl, &e4000_ctrl_ops,
			V4L2_CID_RF_TUNER_BANDWIDTH_AUTO, 0, 1, 1, 1);
	dev->bandwidth = v4l2_ctrl_new_std(&dev->hdl, &e4000_ctrl_ops,
			V4L2_CID_RF_TUNER_BANDWIDTH, 4300000, 11000000, 100000, 4300000);
	v4l2_ctrl_स्वतः_cluster(2, &dev->bandwidth_स्वतः, 0, false);
	dev->lna_gain_स्वतः = v4l2_ctrl_new_std(&dev->hdl, &e4000_ctrl_ops,
			V4L2_CID_RF_TUNER_LNA_GAIN_AUTO, 0, 1, 1, 1);
	dev->lna_gain = v4l2_ctrl_new_std(&dev->hdl, &e4000_ctrl_ops,
			V4L2_CID_RF_TUNER_LNA_GAIN, 0, 15, 1, 10);
	v4l2_ctrl_स्वतः_cluster(2, &dev->lna_gain_स्वतः, 0, false);
	dev->mixer_gain_स्वतः = v4l2_ctrl_new_std(&dev->hdl, &e4000_ctrl_ops,
			V4L2_CID_RF_TUNER_MIXER_GAIN_AUTO, 0, 1, 1, 1);
	dev->mixer_gain = v4l2_ctrl_new_std(&dev->hdl, &e4000_ctrl_ops,
			V4L2_CID_RF_TUNER_MIXER_GAIN, 0, 1, 1, 1);
	v4l2_ctrl_स्वतः_cluster(2, &dev->mixer_gain_स्वतः, 0, false);
	dev->अगर_gain_स्वतः = v4l2_ctrl_new_std(&dev->hdl, &e4000_ctrl_ops,
			V4L2_CID_RF_TUNER_IF_GAIN_AUTO, 0, 1, 1, 1);
	dev->अगर_gain = v4l2_ctrl_new_std(&dev->hdl, &e4000_ctrl_ops,
			V4L2_CID_RF_TUNER_IF_GAIN, 0, 54, 1, 0);
	v4l2_ctrl_स्वतः_cluster(2, &dev->अगर_gain_स्वतः, 0, false);
	dev->pll_lock = v4l2_ctrl_new_std(&dev->hdl, &e4000_ctrl_ops,
			V4L2_CID_RF_TUNER_PLL_LOCK,  0, 1, 1, 0);
	अगर (dev->hdl.error) अणु
		ret = dev->hdl.error;
		dev_err(&client->dev, "Could not initialize controls\n");
		v4l2_ctrl_handler_मुक्त(&dev->hdl);
		जाओ err_kमुक्त;
	पूर्ण

	dev->sd.ctrl_handler = &dev->hdl;
	dev->f_frequency = bands[0].rangelow;
	dev->f_bandwidth = dev->bandwidth->val;
	v4l2_i2c_subdev_init(&dev->sd, client, &e4000_subdev_ops);
#पूर्ण_अगर
	fe->tuner_priv = dev;
	स_नकल(&fe->ops.tuner_ops, &e4000_dvb_tuner_ops,
	       माप(fe->ops.tuner_ops));
	v4l2_set_subdevdata(&dev->sd, client);
	i2c_set_clientdata(client, &dev->sd);

	dev_info(&client->dev, "Elonics E4000 successfully identified\n");
	वापस 0;
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक e4000_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा e4000_dev *dev = container_of(sd, काष्ठा e4000_dev, sd);

	dev_dbg(&client->dev, "\n");

#अगर IS_ENABLED(CONFIG_VIDEO_V4L2)
	v4l2_ctrl_handler_मुक्त(&dev->hdl);
#पूर्ण_अगर
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id e4000_id_table[] = अणु
	अणु"e4000", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, e4000_id_table);

अटल काष्ठा i2c_driver e4000_driver = अणु
	.driver = अणु
		.name	= "e4000",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= e4000_probe,
	.हटाओ		= e4000_हटाओ,
	.id_table	= e4000_id_table,
पूर्ण;

module_i2c_driver(e4000_driver);

MODULE_DESCRIPTION("Elonics E4000 silicon tuner driver");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_LICENSE("GPL");
