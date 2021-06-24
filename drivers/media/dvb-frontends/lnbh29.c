<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Driver क्रम LNB supply and control IC STMicroelectronics LNBH29
//
// Copyright (c) 2018 Socionext Inc.

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "lnbh29.h"

/**
 * काष्ठा lnbh29_priv - LNBH29 driver निजी data
 * @i2c:         Poपूर्णांकer to the I2C adapter काष्ठाure
 * @i2c_address: I2C address of LNBH29 chip
 * @config:      Registers configuration
 *               offset 0: 1st रेजिस्टर address, always 0x01 (DATA)
 *               offset 1: DATA रेजिस्टर value
 */
काष्ठा lnbh29_priv अणु
	काष्ठा i2c_adapter *i2c;
	u8 i2c_address;
	u8 config[2];
पूर्ण;

#घोषणा LNBH29_STATUS_OLF     BIT(0)
#घोषणा LNBH29_STATUS_OTF     BIT(1)
#घोषणा LNBH29_STATUS_VMON    BIT(2)
#घोषणा LNBH29_STATUS_PNG     BIT(3)
#घोषणा LNBH29_STATUS_PDO     BIT(4)
#घोषणा LNBH29_VSEL_MASK      GENMASK(2, 0)
#घोषणा LNBH29_VSEL_0         0x00
/* Min: 13.188V, Typ: 13.667V, Max:14V */
#घोषणा LNBH29_VSEL_13        0x03
/* Min: 18.158V, Typ: 18.817V, Max:19.475V */
#घोषणा LNBH29_VSEL_18        0x07

अटल पूर्णांक lnbh29_पढ़ो_vmon(काष्ठा lnbh29_priv *priv)
अणु
	u8 addr = 0x00;
	u8 status[2];
	पूर्णांक ret;
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

	ret = i2c_transfer(priv->i2c, msg, 2);
	अगर (ret >= 0 && ret != 2)
		ret = -EIO;
	अगर (ret < 0) अणु
		dev_dbg(&priv->i2c->dev, "LNBH29 I2C transfer failed (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (status[0] & (LNBH29_STATUS_OLF | LNBH29_STATUS_VMON)) अणु
		dev_err(&priv->i2c->dev,
			"LNBH29 voltage in failure state, status reg 0x%x\n",
			status[0]);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lnbh29_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा lnbh29_priv *priv = fe->sec_priv;
	u8 data_reg;
	पूर्णांक ret;
	काष्ठा i2c_msg msg = अणु
		.addr = priv->i2c_address,
		.flags = 0,
		.len = माप(priv->config),
		.buf = priv->config
	पूर्ण;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_OFF:
		data_reg = LNBH29_VSEL_0;
		अवरोध;
	हाल SEC_VOLTAGE_13:
		data_reg = LNBH29_VSEL_13;
		अवरोध;
	हाल SEC_VOLTAGE_18:
		data_reg = LNBH29_VSEL_18;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	priv->config[1] &= ~LNBH29_VSEL_MASK;
	priv->config[1] |= data_reg;

	ret = i2c_transfer(priv->i2c, &msg, 1);
	अगर (ret >= 0 && ret != 1)
		ret = -EIO;
	अगर (ret < 0) अणु
		dev_err(&priv->i2c->dev, "LNBH29 I2C transfer error (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	/* Soft-start समय (Vout 0V to 18V) is Typ. 6ms. */
	usleep_range(6000, 20000);

	अगर (voltage == SEC_VOLTAGE_OFF)
		वापस 0;

	वापस lnbh29_पढ़ो_vmon(priv);
पूर्ण

अटल व्योम lnbh29_release(काष्ठा dvb_frontend *fe)
अणु
	lnbh29_set_voltage(fe, SEC_VOLTAGE_OFF);
	kमुक्त(fe->sec_priv);
	fe->sec_priv = शून्य;
पूर्ण

काष्ठा dvb_frontend *lnbh29_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा lnbh29_config *cfg,
				   काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा lnbh29_priv *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;

	priv->i2c_address = (cfg->i2c_address >> 1);
	priv->i2c = i2c;
	priv->config[0] = 0x01;
	priv->config[1] = cfg->data_config;
	fe->sec_priv = priv;

	अगर (lnbh29_set_voltage(fe, SEC_VOLTAGE_OFF)) अणु
		dev_err(&i2c->dev, "no LNBH29 found at I2C addr 0x%02x\n",
			priv->i2c_address);
		kमुक्त(priv);
		fe->sec_priv = शून्य;
		वापस शून्य;
	पूर्ण

	fe->ops.release_sec = lnbh29_release;
	fe->ops.set_voltage = lnbh29_set_voltage;

	dev_info(&i2c->dev, "LNBH29 attached at I2C addr 0x%02x\n",
		 priv->i2c_address);

	वापस fe;
पूर्ण
EXPORT_SYMBOL(lnbh29_attach);

MODULE_AUTHOR("Katsuhiro Suzuki <suzuki.katsuhiro@socionext.com>");
MODULE_DESCRIPTION("STMicroelectronics LNBH29 driver");
MODULE_LICENSE("GPL v2");
