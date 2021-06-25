<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Allegro A8293 SEC driver
 *
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#समावेश "a8293.h"

काष्ठा a8293_dev अणु
	काष्ठा i2c_client *client;
	u8 reg[2];
पूर्ण;

अटल पूर्णांक a8293_set_voltage(काष्ठा dvb_frontend *fe,
			     क्रमागत fe_sec_voltage fe_sec_voltage)
अणु
	काष्ठा a8293_dev *dev = fe->sec_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 reg0, reg1;

	dev_dbg(&client->dev, "fe_sec_voltage=%d\n", fe_sec_voltage);

	चयन (fe_sec_voltage) अणु
	हाल SEC_VOLTAGE_OFF:
		/* ENB=0 */
		reg0 = 0x10;
		अवरोध;
	हाल SEC_VOLTAGE_13:
		/* VSEL0=1, VSEL1=0, VSEL2=0, VSEL3=0, ENB=1*/
		reg0 = 0x31;
		अवरोध;
	हाल SEC_VOLTAGE_18:
		/* VSEL0=0, VSEL1=0, VSEL2=0, VSEL3=1, ENB=1*/
		reg0 = 0x38;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	अगर (reg0 != dev->reg[0]) अणु
		ret = i2c_master_send(client, &reg0, 1);
		अगर (ret < 0)
			जाओ err;
		dev->reg[0] = reg0;
	पूर्ण

	/* TMODE=0, TGATE=1 */
	reg1 = 0x82;
	अगर (reg1 != dev->reg[1]) अणु
		ret = i2c_master_send(client, &reg1, 1);
		अगर (ret < 0)
			जाओ err;
		dev->reg[1] = reg1;
	पूर्ण

	usleep_range(1500, 50000);
	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक a8293_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा a8293_dev *dev;
	काष्ठा a8293_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = pdata->dvb_frontend;
	पूर्णांक ret;
	u8 buf[2];

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev->client = client;

	/* check अगर the SEC is there */
	ret = i2c_master_recv(client, buf, 2);
	अगर (ret < 0)
		जाओ err_kमुक्त;

	/* override frontend ops */
	fe->ops.set_voltage = a8293_set_voltage;
	fe->sec_priv = dev;
	i2c_set_clientdata(client, dev);

	dev_info(&client->dev, "Allegro A8293 SEC successfully attached\n");
	वापस 0;
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक a8293_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा a8293_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	kमुक्त(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id a8293_id_table[] = अणु
	अणु"a8293", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, a8293_id_table);

अटल काष्ठा i2c_driver a8293_driver = अणु
	.driver = अणु
		.name	= "a8293",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= a8293_probe,
	.हटाओ		= a8293_हटाओ,
	.id_table	= a8293_id_table,
पूर्ण;

module_i2c_driver(a8293_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Allegro A8293 SEC driver");
MODULE_LICENSE("GPL");
