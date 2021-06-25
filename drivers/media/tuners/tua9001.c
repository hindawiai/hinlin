<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Infineon TUA9001 silicon tuner driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 */

#समावेश "tua9001_priv.h"

अटल पूर्णांक tua9001_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tua9001_dev *dev = fe->tuner_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret, i;
	अटल स्थिर काष्ठा tua9001_reg_val data[] = अणु
		अणु0x1e, 0x6512पूर्ण,
		अणु0x25, 0xb888पूर्ण,
		अणु0x39, 0x5460पूर्ण,
		अणु0x3b, 0x00c0पूर्ण,
		अणु0x3a, 0xf000पूर्ण,
		अणु0x08, 0x0000पूर्ण,
		अणु0x32, 0x0030पूर्ण,
		अणु0x41, 0x703aपूर्ण,
		अणु0x40, 0x1c78पूर्ण,
		अणु0x2c, 0x1c00पूर्ण,
		अणु0x36, 0xc013पूर्ण,
		अणु0x37, 0x6f18पूर्ण,
		अणु0x27, 0x0008पूर्ण,
		अणु0x2a, 0x0001पूर्ण,
		अणु0x34, 0x0a40पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	अगर (fe->callback) अणु
		ret = fe->callback(client->adapter,
				   DVB_FRONTEND_COMPONENT_TUNER,
				   TUA9001_CMD_RESETN, 0);
		अगर (ret)
			जाओ err;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data); i++) अणु
		ret = regmap_ग_लिखो(dev->regmap, data[i].reg, data[i].val);
		अगर (ret)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tua9001_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tua9001_dev *dev = fe->tuner_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	अगर (fe->callback) अणु
		ret = fe->callback(client->adapter,
				   DVB_FRONTEND_COMPONENT_TUNER,
				   TUA9001_CMD_RESETN, 1);
		अगर (ret)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tua9001_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tua9001_dev *dev = fe->tuner_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i;
	u16 val;
	काष्ठा tua9001_reg_val data[2];

	dev_dbg(&client->dev,
		"delivery_system=%u frequency=%u bandwidth_hz=%u\n",
		c->delivery_प्रणाली, c->frequency, c->bandwidth_hz);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		चयन (c->bandwidth_hz) अणु
		हाल 8000000:
			val  = 0x0000;
			अवरोध;
		हाल 7000000:
			val  = 0x1000;
			अवरोध;
		हाल 6000000:
			val  = 0x2000;
			अवरोध;
		हाल 5000000:
			val  = 0x3000;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	data[0].reg = 0x04;
	data[0].val = val;
	data[1].reg = 0x1f;
	data[1].val = भाग_u64((u64) (c->frequency - 150000000) * 48, 1000000);

	अगर (fe->callback) अणु
		ret = fe->callback(client->adapter,
				   DVB_FRONTEND_COMPONENT_TUNER,
				   TUA9001_CMD_RXEN, 0);
		अगर (ret)
			जाओ err;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data); i++) अणु
		ret = regmap_ग_लिखो(dev->regmap, data[i].reg, data[i].val);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (fe->callback) अणु
		ret = fe->callback(client->adapter,
				   DVB_FRONTEND_COMPONENT_TUNER,
				   TUA9001_CMD_RXEN, 1);
		अगर (ret)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tua9001_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tua9001_dev *dev = fe->tuner_priv;
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "\n");

	*frequency = 0; /* Zero-IF */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tua9001_tuner_ops = अणु
	.info = अणु
		.name             = "Infineon TUA9001",
		.frequency_min_hz = 170 * MHz,
		.frequency_max_hz = 862 * MHz,
	पूर्ण,

	.init = tua9001_init,
	.sleep = tua9001_sleep,
	.set_params = tua9001_set_params,

	.get_अगर_frequency = tua9001_get_अगर_frequency,
पूर्ण;

अटल पूर्णांक tua9001_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tua9001_dev *dev;
	काष्ठा tua9001_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = pdata->dvb_frontend;
	पूर्णांक ret;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits =  8,
		.val_bits = 16,
	पूर्ण;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev->fe = pdata->dvb_frontend;
	dev->client = client;
	dev->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	अगर (fe->callback) अणु
		ret = fe->callback(client->adapter,
				   DVB_FRONTEND_COMPONENT_TUNER,
				   TUA9001_CMD_CEN, 1);
		अगर (ret)
			जाओ err_kमुक्त;

		ret = fe->callback(client->adapter,
				   DVB_FRONTEND_COMPONENT_TUNER,
				   TUA9001_CMD_RXEN, 0);
		अगर (ret)
			जाओ err_kमुक्त;

		ret = fe->callback(client->adapter,
				   DVB_FRONTEND_COMPONENT_TUNER,
				   TUA9001_CMD_RESETN, 1);
		अगर (ret)
			जाओ err_kमुक्त;
	पूर्ण

	fe->tuner_priv = dev;
	स_नकल(&fe->ops.tuner_ops, &tua9001_tuner_ops,
			माप(काष्ठा dvb_tuner_ops));
	i2c_set_clientdata(client, dev);

	dev_info(&client->dev, "Infineon TUA9001 successfully attached\n");
	वापस 0;
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tua9001_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tua9001_dev *dev = i2c_get_clientdata(client);
	काष्ठा dvb_frontend *fe = dev->fe;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	अगर (fe->callback) अणु
		ret = fe->callback(client->adapter,
				   DVB_FRONTEND_COMPONENT_TUNER,
				   TUA9001_CMD_CEN, 0);
		अगर (ret)
			जाओ err_kमुक्त;
	पूर्ण
	kमुक्त(dev);
	वापस 0;
err_kमुक्त:
	kमुक्त(dev);
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tua9001_id_table[] = अणु
	अणु"tua9001", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tua9001_id_table);

अटल काष्ठा i2c_driver tua9001_driver = अणु
	.driver = अणु
		.name	= "tua9001",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= tua9001_probe,
	.हटाओ		= tua9001_हटाओ,
	.id_table	= tua9001_id_table,
पूर्ण;

module_i2c_driver(tua9001_driver);

MODULE_DESCRIPTION("Infineon TUA9001 silicon tuner driver");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_LICENSE("GPL");
