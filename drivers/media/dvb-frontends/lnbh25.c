<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lnbh25.c
 *
 * Driver क्रम LNB supply and control IC LNBH25
 *
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "lnbh25.h"

/**
 * काष्ठा lnbh25_priv - LNBH25 driver निजी data
 * @i2c:		poपूर्णांकer to the I2C adapter काष्ठाure
 * @i2c_address:	I2C address of LNBH25 SEC chip
 * @config:		Registers configuration:
 *			offset 0: 1st रेजिस्टर address, always 0x02 (DATA1)
 *			offset 1: DATA1 रेजिस्टर value
 *			offset 2: DATA2 रेजिस्टर value
 */
काष्ठा lnbh25_priv अणु
	काष्ठा i2c_adapter	*i2c;
	u8			i2c_address;
	u8			config[3];
पूर्ण;

#घोषणा LNBH25_STATUS_OFL	0x1
#घोषणा LNBH25_STATUS_VMON	0x4
#घोषणा LNBH25_VSEL_13		0x03
#घोषणा LNBH25_VSEL_18		0x0a

अटल पूर्णांक lnbh25_पढ़ो_vmon(काष्ठा lnbh25_priv *priv)
अणु
	पूर्णांक i, ret;
	u8 addr = 0x00;
	u8 status[6];
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = priv->i2c_address,
			.flags = 0,
			.len = 1,
			.buf = &addr
		पूर्ण, अणु
			.addr = priv->i2c_address,
			.flags = I2C_M_RD,
			.len = माप(status),
			.buf = status
		पूर्ण
	पूर्ण;

	क्रम (i = 0; i < 2; i++) अणु
		ret = i2c_transfer(priv->i2c, &msg[i], 1);
		अगर (ret >= 0 && ret != 1)
			ret = -EIO;
		अगर (ret < 0) अणु
			dev_dbg(&priv->i2c->dev,
				"%s(): I2C transfer %d failed (%d)\n",
				__func__, i, ret);
			वापस ret;
		पूर्ण
	पूर्ण
	dev_dbg(&priv->i2c->dev, "%s(): %*ph\n",
		__func__, (पूर्णांक) माप(status), status);
	अगर ((status[0] & (LNBH25_STATUS_OFL | LNBH25_STATUS_VMON)) != 0) अणु
		dev_err(&priv->i2c->dev,
			"%s(): voltage in failure state, status reg 0x%x\n",
			__func__, status[0]);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lnbh25_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु
	पूर्णांक ret;
	u8 data1_reg;
	स्थिर अक्षर *vsel;
	काष्ठा lnbh25_priv *priv = fe->sec_priv;
	काष्ठा i2c_msg msg = अणु
		.addr = priv->i2c_address,
		.flags = 0,
		.len = माप(priv->config),
		.buf = priv->config
	पूर्ण;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_OFF:
		data1_reg = 0x00;
		vsel = "Off";
		अवरोध;
	हाल SEC_VOLTAGE_13:
		data1_reg = LNBH25_VSEL_13;
		vsel = "13V";
		अवरोध;
	हाल SEC_VOLTAGE_18:
		data1_reg = LNBH25_VSEL_18;
		vsel = "18V";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	priv->config[1] = data1_reg;
	dev_dbg(&priv->i2c->dev,
		"%s(): %s, I2C 0x%x write [ %02x %02x %02x ]\n",
		__func__, vsel, priv->i2c_address,
		priv->config[0], priv->config[1], priv->config[2]);
	ret = i2c_transfer(priv->i2c, &msg, 1);
	अगर (ret >= 0 && ret != 1)
		ret = -EIO;
	अगर (ret < 0) अणु
		dev_err(&priv->i2c->dev, "%s(): I2C transfer error (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण
	अगर (voltage != SEC_VOLTAGE_OFF) अणु
		msleep(120);
		ret = lnbh25_पढ़ो_vmon(priv);
	पूर्ण अन्यथा अणु
		msleep(20);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम lnbh25_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lnbh25_priv *priv = fe->sec_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	lnbh25_set_voltage(fe, SEC_VOLTAGE_OFF);
	kमुक्त(fe->sec_priv);
	fe->sec_priv = शून्य;
पूर्ण

काष्ठा dvb_frontend *lnbh25_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा lnbh25_config *cfg,
				   काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा lnbh25_priv *priv;

	dev_dbg(&i2c->dev, "%s()\n", __func__);
	priv = kzalloc(माप(काष्ठा lnbh25_priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;
	priv->i2c_address = (cfg->i2c_address >> 1);
	priv->i2c = i2c;
	priv->config[0] = 0x02;
	priv->config[1] = 0x00;
	priv->config[2] = cfg->data2_config;
	fe->sec_priv = priv;
	अगर (lnbh25_set_voltage(fe, SEC_VOLTAGE_OFF)) अणु
		dev_err(&i2c->dev,
			"%s(): no LNBH25 found at I2C addr 0x%02x\n",
			__func__, priv->i2c_address);
		kमुक्त(priv);
		fe->sec_priv = शून्य;
		वापस शून्य;
	पूर्ण

	fe->ops.release_sec = lnbh25_release;
	fe->ops.set_voltage = lnbh25_set_voltage;

	dev_info(&i2c->dev, "%s(): attached at I2C addr 0x%02x\n",
		__func__, priv->i2c_address);
	वापस fe;
पूर्ण
EXPORT_SYMBOL(lnbh25_attach);

MODULE_DESCRIPTION("ST LNBH25 driver");
MODULE_AUTHOR("info@netup.ru");
MODULE_LICENSE("GPL");
