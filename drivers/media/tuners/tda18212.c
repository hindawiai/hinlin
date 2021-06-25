<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NXP TDA18212HN silicon tuner driver
 *
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#समावेश "tda18212.h"
#समावेश <linux/regmap.h>

काष्ठा tda18212_dev अणु
	काष्ठा tda18212_config cfg;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;

	u32 अगर_frequency;
पूर्ण;

अटल पूर्णांक tda18212_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18212_dev *dev = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i;
	u32 अगर_khz;
	u8 buf[9];
	#घोषणा DVBT_6   0
	#घोषणा DVBT_7   1
	#घोषणा DVBT_8   2
	#घोषणा DVBT2_6  3
	#घोषणा DVBT2_7  4
	#घोषणा DVBT2_8  5
	#घोषणा DVBC_6   6
	#घोषणा DVBC_8   7
	#घोषणा ATSC_VSB 8
	#घोषणा ATSC_QAM 9
	अटल स्थिर u8 bw_params[][3] = अणु
		     /* reg:   0f    13    23 */
		[DVBT_6]  = अणु 0xb3, 0x20, 0x03 पूर्ण,
		[DVBT_7]  = अणु 0xb3, 0x31, 0x01 पूर्ण,
		[DVBT_8]  = अणु 0xb3, 0x22, 0x01 पूर्ण,
		[DVBT2_6] = अणु 0xbc, 0x20, 0x03 पूर्ण,
		[DVBT2_7] = अणु 0xbc, 0x72, 0x03 पूर्ण,
		[DVBT2_8] = अणु 0xbc, 0x22, 0x01 पूर्ण,
		[DVBC_6]  = अणु 0x92, 0x50, 0x03 पूर्ण,
		[DVBC_8]  = अणु 0x92, 0x53, 0x03 पूर्ण,
		[ATSC_VSB] = अणु 0x7d, 0x20, 0x63 पूर्ण,
		[ATSC_QAM] = अणु 0x7d, 0x20, 0x63 पूर्ण,
	पूर्ण;

	dev_dbg(&dev->client->dev,
			"delivery_system=%d frequency=%d bandwidth_hz=%d\n",
			c->delivery_प्रणाली, c->frequency,
			c->bandwidth_hz);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
		अगर_khz = dev->cfg.अगर_atsc_vsb;
		i = ATSC_VSB;
		अवरोध;
	हाल SYS_DVBC_ANNEX_B:
		अगर_khz = dev->cfg.अगर_atsc_qam;
		i = ATSC_QAM;
		अवरोध;
	हाल SYS_DVBT:
		चयन (c->bandwidth_hz) अणु
		हाल 6000000:
			अगर_khz = dev->cfg.अगर_dvbt_6;
			i = DVBT_6;
			अवरोध;
		हाल 7000000:
			अगर_khz = dev->cfg.अगर_dvbt_7;
			i = DVBT_7;
			अवरोध;
		हाल 8000000:
			अगर_khz = dev->cfg.अगर_dvbt_8;
			i = DVBT_8;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		अवरोध;
	हाल SYS_DVBT2:
		चयन (c->bandwidth_hz) अणु
		हाल 6000000:
			अगर_khz = dev->cfg.अगर_dvbt2_6;
			i = DVBT2_6;
			अवरोध;
		हाल 7000000:
			अगर_khz = dev->cfg.अगर_dvbt2_7;
			i = DVBT2_7;
			अवरोध;
		हाल 8000000:
			अगर_khz = dev->cfg.अगर_dvbt2_8;
			i = DVBT2_8;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_C:
		अगर_khz = dev->cfg.अगर_dvbc;
		i = DVBC_8;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, 0x23, bw_params[i][2]);
	अगर (ret)
		जाओ error;

	ret = regmap_ग_लिखो(dev->regmap, 0x06, 0x00);
	अगर (ret)
		जाओ error;

	ret = regmap_ग_लिखो(dev->regmap, 0x0f, bw_params[i][0]);
	अगर (ret)
		जाओ error;

	buf[0] = 0x02;
	buf[1] = bw_params[i][1];
	buf[2] = 0x03; /* शेष value */
	buf[3] = DIV_ROUND_CLOSEST(अगर_khz, 50);
	buf[4] = ((c->frequency / 1000) >> 16) & 0xff;
	buf[5] = ((c->frequency / 1000) >>  8) & 0xff;
	buf[6] = ((c->frequency / 1000) >>  0) & 0xff;
	buf[7] = 0xc1;
	buf[8] = 0x01;
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x12, buf, माप(buf));
	अगर (ret)
		जाओ error;

	/* actual IF rounded as it is on रेजिस्टर */
	dev->अगर_frequency = buf[3] * 50 * 1000;

निकास:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	वापस ret;

error:
	dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	जाओ निकास;
पूर्ण

अटल पूर्णांक tda18212_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tda18212_dev *dev = fe->tuner_priv;

	*frequency = dev->अगर_frequency;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tda18212_tuner_ops = अणु
	.info = अणु
		.name              = "NXP TDA18212",

		.frequency_min_hz  =  48 * MHz,
		.frequency_max_hz  = 864 * MHz,
		.frequency_step_hz =   1 * kHz,
	पूर्ण,

	.set_params    = tda18212_set_params,
	.get_अगर_frequency = tda18212_get_अगर_frequency,
पूर्ण;

अटल पूर्णांक tda18212_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tda18212_config *cfg = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = cfg->fe;
	काष्ठा tda18212_dev *dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक chip_id;
	अक्षर *version;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
	पूर्ण;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		ret = -ENOMEM;
		dev_err(&client->dev, "kzalloc() failed\n");
		जाओ err;
	पूर्ण

	स_नकल(&dev->cfg, cfg, माप(काष्ठा tda18212_config));
	dev->client = client;
	dev->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err;
	पूर्ण

	/* check अगर the tuner is there */
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	ret = regmap_पढ़ो(dev->regmap, 0x00, &chip_id);
	dev_dbg(&dev->client->dev, "chip_id=%02x\n", chip_id);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	अगर (ret)
		जाओ err;

	चयन (chip_id) अणु
	हाल 0xc7:
		version = "M"; /* master */
		अवरोध;
	हाल 0x47:
		version = "S"; /* slave */
		अवरोध;
	शेष:
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	dev_info(&dev->client->dev,
			"NXP TDA18212HN/%s successfully identified\n", version);

	fe->tuner_priv = dev;
	स_नकल(&fe->ops.tuner_ops, &tda18212_tuner_ops,
			माप(काष्ठा dvb_tuner_ops));
	i2c_set_clientdata(client, dev);

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	kमुक्त(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक tda18212_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tda18212_dev *dev = i2c_get_clientdata(client);
	काष्ठा dvb_frontend *fe = dev->cfg.fe;

	dev_dbg(&client->dev, "\n");

	स_रखो(&fe->ops.tuner_ops, 0, माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = शून्य;
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tda18212_id[] = अणु
	अणु"tda18212", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tda18212_id);

अटल काष्ठा i2c_driver tda18212_driver = अणु
	.driver = अणु
		.name	= "tda18212",
	पूर्ण,
	.probe		= tda18212_probe,
	.हटाओ		= tda18212_हटाओ,
	.id_table	= tda18212_id,
पूर्ण;

module_i2c_driver(tda18212_driver);

MODULE_DESCRIPTION("NXP TDA18212HN silicon tuner driver");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_LICENSE("GPL");
