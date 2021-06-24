<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * FCI FC2580 silicon tuner driver
 *
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#समावेश "fc2580_priv.h"

/*
 * TODO:
 * I2C ग_लिखो and पढ़ो works only क्रम one single रेजिस्टर. Multiple रेजिस्टरs
 * could not be accessed using normal रेजिस्टर address स्वतः-increment.
 * There could be (very likely) रेजिस्टर to change that behavior....
 */

/* ग_लिखो single रेजिस्टर conditionally only when value dअगरfers from 0xff
 * XXX: This is special routine meant only क्रम writing fc2580_freq_regs_lut[]
 * values. Do not use क्रम the other purposes. */
अटल पूर्णांक fc2580_wr_reg_ff(काष्ठा fc2580_dev *dev, u8 reg, u8 val)
अणु
	अगर (val == 0xff)
		वापस 0;
	अन्यथा
		वापस regmap_ग_लिखो(dev->regmap, reg, val);
पूर्ण

अटल पूर्णांक fc2580_set_params(काष्ठा fc2580_dev *dev)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uiपंचांगp, भाग_ref, भाग_ref_val, भाग_n, k, k_cw, भाग_out;
	u64 f_vco;
	u8 synth_config;
	अचिन्हित दीर्घ समयout;

	अगर (!dev->active) अणु
		dev_dbg(&client->dev, "tuner is sleeping\n");
		वापस 0;
	पूर्ण

	/*
	 * Fractional-N synthesizer
	 *
	 *                      +---------------------------------------+
	 *                      v                                       |
	 *  Fref   +----+     +----+     +-------+         +----+     +------+     +---+
	 * ------> | /R | --> | PD | --> |  VCO  | ------> | /2 | --> | /N.F | <-- | K |
	 *         +----+     +----+     +-------+         +----+     +------+     +---+
	 *                                 |
	 *                                 |
	 *                                 v
	 *                               +-------+  Fout
	 *                               | /Rout | ------>
	 *                               +-------+
	 */
	क्रम (i = 0; i < ARRAY_SIZE(fc2580_pll_lut); i++) अणु
		अगर (dev->f_frequency <= fc2580_pll_lut[i].freq)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(fc2580_pll_lut)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	#घोषणा DIV_PRE_N 2
	#घोषणा F_REF dev->clk
	भाग_out = fc2580_pll_lut[i].भाग_out;
	f_vco = (u64) dev->f_frequency * भाग_out;
	synth_config = fc2580_pll_lut[i].band;
	अगर (f_vco < 2600000000ULL)
		synth_config |= 0x06;
	अन्यथा
		synth_config |= 0x0e;

	/* select reference भागider R (keep PLL भाग N in valid range) */
	#घोषणा DIV_N_MIN 76
	अगर (f_vco >= भाग_u64((u64) DIV_PRE_N * DIV_N_MIN * F_REF, 1)) अणु
		भाग_ref = 1;
		भाग_ref_val = 0x00;
	पूर्ण अन्यथा अगर (f_vco >= भाग_u64((u64) DIV_PRE_N * DIV_N_MIN * F_REF, 2)) अणु
		भाग_ref = 2;
		भाग_ref_val = 0x10;
	पूर्ण अन्यथा अणु
		भाग_ref = 4;
		भाग_ref_val = 0x20;
	पूर्ण

	/* calculate PLL पूर्णांकeger and fractional control word */
	uiपंचांगp = DIV_PRE_N * F_REF / भाग_ref;
	भाग_n = भाग_u64_rem(f_vco, uiपंचांगp, &k);
	k_cw = भाग_u64((u64) k * 0x100000, uiपंचांगp);

	dev_dbg(&client->dev,
		"frequency=%u bandwidth=%u f_vco=%llu F_REF=%u div_ref=%u div_n=%u k=%u div_out=%u k_cw=%0x\n",
		dev->f_frequency, dev->f_bandwidth, f_vco, F_REF, भाग_ref,
		भाग_n, k, भाग_out, k_cw);

	ret = regmap_ग_लिखो(dev->regmap, 0x02, synth_config);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x18, भाग_ref_val << 0 | k_cw >> 16);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x1a, (k_cw >> 8) & 0xff);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x1b, (k_cw >> 0) & 0xff);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x1c, भाग_n);
	अगर (ret)
		जाओ err;

	/* रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(fc2580_freq_regs_lut); i++) अणु
		अगर (dev->f_frequency <= fc2580_freq_regs_lut[i].freq)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(fc2580_freq_regs_lut)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = fc2580_wr_reg_ff(dev, 0x25, fc2580_freq_regs_lut[i].r25_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x27, fc2580_freq_regs_lut[i].r27_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x28, fc2580_freq_regs_lut[i].r28_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x29, fc2580_freq_regs_lut[i].r29_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x2b, fc2580_freq_regs_lut[i].r2b_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x2c, fc2580_freq_regs_lut[i].r2c_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x2d, fc2580_freq_regs_lut[i].r2d_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x30, fc2580_freq_regs_lut[i].r30_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x44, fc2580_freq_regs_lut[i].r44_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x50, fc2580_freq_regs_lut[i].r50_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x53, fc2580_freq_regs_lut[i].r53_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x5f, fc2580_freq_regs_lut[i].r5f_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x61, fc2580_freq_regs_lut[i].r61_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x62, fc2580_freq_regs_lut[i].r62_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x63, fc2580_freq_regs_lut[i].r63_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x67, fc2580_freq_regs_lut[i].r67_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x68, fc2580_freq_regs_lut[i].r68_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x69, fc2580_freq_regs_lut[i].r69_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x6a, fc2580_freq_regs_lut[i].r6a_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x6b, fc2580_freq_regs_lut[i].r6b_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x6c, fc2580_freq_regs_lut[i].r6c_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x6d, fc2580_freq_regs_lut[i].r6d_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x6e, fc2580_freq_regs_lut[i].r6e_val);
	अगर (ret)
		जाओ err;

	ret = fc2580_wr_reg_ff(dev, 0x6f, fc2580_freq_regs_lut[i].r6f_val);
	अगर (ret)
		जाओ err;

	/* IF filters */
	क्रम (i = 0; i < ARRAY_SIZE(fc2580_अगर_filter_lut); i++) अणु
		अगर (dev->f_bandwidth <= fc2580_अगर_filter_lut[i].freq)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(fc2580_अगर_filter_lut)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, 0x36, fc2580_अगर_filter_lut[i].r36_val);
	अगर (ret)
		जाओ err;

	uiपंचांगp = (अचिन्हित पूर्णांक) 8058000 - (dev->f_bandwidth * 122 / 100 / 2);
	uiपंचांगp = भाग64_u64((u64) dev->clk * uiपंचांगp, 1000000000000ULL);
	ret = regmap_ग_लिखो(dev->regmap, 0x37, uiपंचांगp);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x39, fc2580_अगर_filter_lut[i].r39_val);
	अगर (ret)
		जाओ err;

	समयout = jअगरfies + msecs_to_jअगरfies(30);
	क्रम (uiपंचांगp = ~0xc0; !समय_after(jअगरfies, समयout) && uiपंचांगp != 0xc0;) अणु
		/* trigger filter */
		ret = regmap_ग_लिखो(dev->regmap, 0x2e, 0x09);
		अगर (ret)
			जाओ err;

		/* locked when [7:6] are set (val: d7 6MHz, d5 7MHz, cd 8MHz) */
		ret = regmap_पढ़ो(dev->regmap, 0x2f, &uiपंचांगp);
		अगर (ret)
			जाओ err;
		uiपंचांगp &= 0xc0;

		ret = regmap_ग_लिखो(dev->regmap, 0x2e, 0x01);
		अगर (ret)
			जाओ err;
	पूर्ण
	अगर (uiपंचांगp != 0xc0)
		dev_dbg(&client->dev, "filter did not lock %02x\n", uiपंचांगp);

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक fc2580_init(काष्ठा fc2580_dev *dev)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret, i;

	dev_dbg(&client->dev, "\n");

	क्रम (i = 0; i < ARRAY_SIZE(fc2580_init_reg_vals); i++) अणु
		ret = regmap_ग_लिखो(dev->regmap, fc2580_init_reg_vals[i].reg,
				fc2580_init_reg_vals[i].val);
		अगर (ret)
			जाओ err;
	पूर्ण

	dev->active = true;
	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक fc2580_sleep(काष्ठा fc2580_dev *dev)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	dev->active = false;

	ret = regmap_ग_लिखो(dev->regmap, 0x02, 0x0a);
	अगर (ret)
		जाओ err;
	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

/*
 * DVB API
 */
अटल पूर्णांक fc2580_dvb_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा fc2580_dev *dev = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	dev->f_frequency = c->frequency;
	dev->f_bandwidth = c->bandwidth_hz;
	वापस fc2580_set_params(dev);
पूर्ण

अटल पूर्णांक fc2580_dvb_init(काष्ठा dvb_frontend *fe)
अणु
	वापस fc2580_init(fe->tuner_priv);
पूर्ण

अटल पूर्णांक fc2580_dvb_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस fc2580_sleep(fe->tuner_priv);
पूर्ण

अटल पूर्णांक fc2580_dvb_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	*frequency = 0; /* Zero-IF */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops fc2580_dvb_tuner_ops = अणु
	.info = अणु
		.name             = "FCI FC2580",
		.frequency_min_hz = 174 * MHz,
		.frequency_max_hz = 862 * MHz,
	पूर्ण,

	.init = fc2580_dvb_init,
	.sleep = fc2580_dvb_sleep,
	.set_params = fc2580_dvb_set_params,

	.get_अगर_frequency = fc2580_dvb_get_अगर_frequency,
पूर्ण;

/*
 * V4L2 API
 */
#अगर IS_ENABLED(CONFIG_VIDEO_V4L2)
अटल स्थिर काष्ठा v4l2_frequency_band bands[] = अणु
	अणु
		.type = V4L2_TUNER_RF,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =   130000000,
		.rangehigh  =  2000000000,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा fc2580_dev *fc2580_subdev_to_dev(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा fc2580_dev, subdev);
पूर्ण

अटल पूर्णांक fc2580_standby(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा fc2580_dev *dev = fc2580_subdev_to_dev(sd);
	पूर्णांक ret;

	ret = fc2580_sleep(dev);
	अगर (ret)
		वापस ret;

	वापस fc2580_set_params(dev);
पूर्ण

अटल पूर्णांक fc2580_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *v)
अणु
	काष्ठा fc2580_dev *dev = fc2580_subdev_to_dev(sd);
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "index=%d\n", v->index);

	strscpy(v->name, "FCI FC2580", माप(v->name));
	v->type = V4L2_TUNER_RF;
	v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
	v->rangelow  = bands[0].rangelow;
	v->rangehigh = bands[0].rangehigh;
	वापस 0;
पूर्ण

अटल पूर्णांक fc2580_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा fc2580_dev *dev = fc2580_subdev_to_dev(sd);
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "index=%d\n", v->index);
	वापस 0;
पूर्ण

अटल पूर्णांक fc2580_g_frequency(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_frequency *f)
अणु
	काष्ठा fc2580_dev *dev = fc2580_subdev_to_dev(sd);
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "tuner=%d\n", f->tuner);
	f->frequency = dev->f_frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक fc2580_s_frequency(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा fc2580_dev *dev = fc2580_subdev_to_dev(sd);
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "tuner=%d type=%d frequency=%u\n",
		f->tuner, f->type, f->frequency);

	dev->f_frequency = clamp_t(अचिन्हित पूर्णांक, f->frequency,
				   bands[0].rangelow, bands[0].rangehigh);
	वापस fc2580_set_params(dev);
पूर्ण

अटल पूर्णांक fc2580_क्रमागत_freq_bands(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा fc2580_dev *dev = fc2580_subdev_to_dev(sd);
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

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops fc2580_subdev_tuner_ops = अणु
	.standby                  = fc2580_standby,
	.g_tuner                  = fc2580_g_tuner,
	.s_tuner                  = fc2580_s_tuner,
	.g_frequency              = fc2580_g_frequency,
	.s_frequency              = fc2580_s_frequency,
	.क्रमागत_freq_bands          = fc2580_क्रमागत_freq_bands,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops fc2580_subdev_ops = अणु
	.tuner                    = &fc2580_subdev_tuner_ops,
पूर्ण;

अटल पूर्णांक fc2580_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा fc2580_dev *dev = container_of(ctrl->handler, काष्ठा fc2580_dev, hdl);
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "ctrl: id=%d name=%s cur.val=%d val=%d\n",
		ctrl->id, ctrl->name, ctrl->cur.val, ctrl->val);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_RF_TUNER_BANDWIDTH_AUTO:
	हाल V4L2_CID_RF_TUNER_BANDWIDTH:
		/*
		 * TODO: Auto logic करोes not work 100% correctly as tuner driver
		 * करो not have inक्रमmation to calculate maximum suitable
		 * bandwidth. Calculating it is responsible of master driver.
		 */
		dev->f_bandwidth = dev->bandwidth->val;
		ret = fc2580_set_params(dev);
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "unknown ctrl");
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops fc2580_ctrl_ops = अणु
	.s_ctrl = fc2580_s_ctrl,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा v4l2_subdev *fc2580_get_v4l2_subdev(काष्ठा i2c_client *client)
अणु
	काष्ठा fc2580_dev *dev = i2c_get_clientdata(client);

	अगर (dev->subdev.ops)
		वापस &dev->subdev;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल पूर्णांक fc2580_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा fc2580_dev *dev;
	काष्ठा fc2580_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = pdata->dvb_frontend;
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

	अगर (pdata->clk)
		dev->clk = pdata->clk;
	अन्यथा
		dev->clk = 16384000; /* पूर्णांकernal घड़ी */
	dev->client = client;
	dev->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	/* check अगर the tuner is there */
	ret = regmap_पढ़ो(dev->regmap, 0x01, &uiपंचांगp);
	अगर (ret)
		जाओ err_kमुक्त;

	dev_dbg(&client->dev, "chip_id=%02x\n", uiपंचांगp);

	चयन (uiपंचांगp) अणु
	हाल 0x56:
	हाल 0x5a:
		अवरोध;
	शेष:
		ret = -ENODEV;
		जाओ err_kमुक्त;
	पूर्ण

#अगर IS_ENABLED(CONFIG_VIDEO_V4L2)
	/* Register controls */
	v4l2_ctrl_handler_init(&dev->hdl, 2);
	dev->bandwidth_स्वतः = v4l2_ctrl_new_std(&dev->hdl, &fc2580_ctrl_ops,
						V4L2_CID_RF_TUNER_BANDWIDTH_AUTO,
						0, 1, 1, 1);
	dev->bandwidth = v4l2_ctrl_new_std(&dev->hdl, &fc2580_ctrl_ops,
					   V4L2_CID_RF_TUNER_BANDWIDTH,
					   3000, 10000000, 1, 3000);
	v4l2_ctrl_स्वतः_cluster(2, &dev->bandwidth_स्वतः, 0, false);
	अगर (dev->hdl.error) अणु
		ret = dev->hdl.error;
		dev_err(&client->dev, "Could not initialize controls\n");
		v4l2_ctrl_handler_मुक्त(&dev->hdl);
		जाओ err_kमुक्त;
	पूर्ण
	dev->subdev.ctrl_handler = &dev->hdl;
	dev->f_frequency = bands[0].rangelow;
	dev->f_bandwidth = dev->bandwidth->val;
	v4l2_i2c_subdev_init(&dev->subdev, client, &fc2580_subdev_ops);
#पूर्ण_अगर
	fe->tuner_priv = dev;
	स_नकल(&fe->ops.tuner_ops, &fc2580_dvb_tuner_ops,
	       माप(fe->ops.tuner_ops));
	pdata->get_v4l2_subdev = fc2580_get_v4l2_subdev;
	i2c_set_clientdata(client, dev);

	dev_info(&client->dev, "FCI FC2580 successfully identified\n");
	वापस 0;
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक fc2580_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा fc2580_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

#अगर IS_ENABLED(CONFIG_VIDEO_V4L2)
	v4l2_ctrl_handler_मुक्त(&dev->hdl);
#पूर्ण_अगर
	kमुक्त(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id fc2580_id_table[] = अणु
	अणु"fc2580", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, fc2580_id_table);

अटल काष्ठा i2c_driver fc2580_driver = अणु
	.driver = अणु
		.name	= "fc2580",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= fc2580_probe,
	.हटाओ		= fc2580_हटाओ,
	.id_table	= fc2580_id_table,
पूर्ण;

module_i2c_driver(fc2580_driver);

MODULE_DESCRIPTION("FCI FC2580 silicon tuner driver");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_LICENSE("GPL");
