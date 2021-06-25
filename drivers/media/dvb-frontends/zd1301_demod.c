<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ZyDAS ZD1301 driver (demodulator)
 *
 * Copyright (C) 2015 Antti Palosaari <crope@iki.fi>
 */

#समावेश "zd1301_demod.h"

अटल u8 zd1301_demod_gain = 0x38;
module_param_named(gain, zd1301_demod_gain, byte, 0644);
MODULE_PARM_DESC(gain, "gain (value: 0x00 - 0x70, default: 0x38)");

काष्ठा zd1301_demod_dev अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा dvb_frontend frontend;
	काष्ठा i2c_adapter adapter;
	u8 gain;
पूर्ण;

अटल पूर्णांक zd1301_demod_wreg(काष्ठा zd1301_demod_dev *dev, u16 reg, u8 val)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा zd1301_demod_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;

	वापस pdata->reg_ग_लिखो(pdata->reg_priv, reg, val);
पूर्ण

अटल पूर्णांक zd1301_demod_rreg(काष्ठा zd1301_demod_dev *dev, u16 reg, u8 *val)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा zd1301_demod_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;

	वापस pdata->reg_पढ़ो(pdata->reg_priv, reg, val);
पूर्ण

अटल पूर्णांक zd1301_demod_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zd1301_demod_dev *dev = fe->demodulator_priv;
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	u32 अगर_frequency;
	u8 r6a50_val;

	dev_dbg(&pdev->dev, "frequency=%u bandwidth_hz=%u\n",
		c->frequency, c->bandwidth_hz);

	/* Program tuner */
	अगर (fe->ops.tuner_ops.set_params &&
	    fe->ops.tuner_ops.get_अगर_frequency) अणु
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (ret)
			जाओ err;
		ret = fe->ops.tuner_ops.get_अगर_frequency(fe, &अगर_frequency);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	dev_dbg(&pdev->dev, "if_frequency=%u\n", अगर_frequency);
	अगर (अगर_frequency != 36150000) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		r6a50_val = 0x78;
		अवरोध;
	हाल 7000000:
		r6a50_val = 0x68;
		अवरोध;
	हाल 8000000:
		r6a50_val = 0x58;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = zd1301_demod_wreg(dev, 0x6a60, 0x11);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a47, 0x46);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a48, 0x46);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a4a, 0x15);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a4b, 0x63);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a5b, 0x99);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a3b, 0x10);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6806, 0x01);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a41, 0x08);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a42, 0x46);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a44, 0x14);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a45, 0x67);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a38, 0x00);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a4c, 0x52);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a49, 0x2a);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6840, 0x2e);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a50, r6a50_val);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a38, 0x07);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&pdev->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक zd1301_demod_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zd1301_demod_dev *dev = fe->demodulator_priv;
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "\n");

	ret = zd1301_demod_wreg(dev, 0x6a43, 0x70);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x684e, 0x00);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6849, 0x00);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x68e2, 0xd7);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x68e0, 0x39);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6840, 0x21);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&pdev->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक zd1301_demod_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zd1301_demod_dev *dev = fe->demodulator_priv;
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "\n");

	ret = zd1301_demod_wreg(dev, 0x6840, 0x26);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x68e0, 0xff);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x68e2, 0xd8);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6849, 0x4e);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x684e, 0x01);
	अगर (ret)
		जाओ err;
	ret = zd1301_demod_wreg(dev, 0x6a43, zd1301_demod_gain);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&pdev->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक zd1301_demod_get_tune_settings(काष्ठा dvb_frontend *fe,
					  काष्ठा dvb_frontend_tune_settings *settings)
अणु
	काष्ठा zd1301_demod_dev *dev = fe->demodulator_priv;
	काष्ठा platक्रमm_device *pdev = dev->pdev;

	dev_dbg(&pdev->dev, "\n");

	/* ~180ms seems to be enough */
	settings->min_delay_ms = 400;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1301_demod_पढ़ो_status(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_status *status)
अणु
	काष्ठा zd1301_demod_dev *dev = fe->demodulator_priv;
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret;
	u8 u8पंचांगp;

	ret = zd1301_demod_rreg(dev, 0x6a24, &u8पंचांगp);
	अगर (ret)
		जाओ err;
	अगर (u8पंचांगp > 0x00 && u8पंचांगp < 0x20)
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI |
			  FE_HAS_SYNC | FE_HAS_LOCK;
	अन्यथा
		*status = 0;

	dev_dbg(&pdev->dev, "lock byte=%02x\n", u8पंचांगp);

	/*
	 * Interesting रेजिस्टरs here are:
	 * 0x6a05: get some gain value
	 * 0x6a06: get about same gain value than set to 0x6a43
	 * 0x6a07: get some gain value
	 * 0x6a43: set gain value by driver
	 * 0x6a24: get demod lock bits (FSM stage?)
	 *
	 * Driver should implement some kind of algorithm to calculate suitable
	 * value क्रम रेजिस्टर 0x6a43, based likely values from रेजिस्टर 0x6a05
	 * and 0x6a07. Looks like gain रेजिस्टर 0x6a43 value could be from
	 * range 0x00 - 0x70.
	 */

	अगर (dev->gain != zd1301_demod_gain) अणु
		dev->gain = zd1301_demod_gain;

		ret = zd1301_demod_wreg(dev, 0x6a43, dev->gain);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&pdev->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops zd1301_demod_ops = अणु
	.delsys = अणुSYS_DVBTपूर्ण,
	.info = अणु
		.name = "ZyDAS ZD1301",
		.caps = FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO |
			FE_CAN_MUTE_TS
	पूर्ण,

	.sleep = zd1301_demod_sleep,
	.init = zd1301_demod_init,
	.set_frontend = zd1301_demod_set_frontend,
	.get_tune_settings = zd1301_demod_get_tune_settings,
	.पढ़ो_status = zd1301_demod_पढ़ो_status,
पूर्ण;

काष्ठा dvb_frontend *zd1301_demod_get_dvb_frontend(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zd1301_demod_dev *dev = platक्रमm_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "\n");

	वापस &dev->frontend;
पूर्ण
EXPORT_SYMBOL(zd1301_demod_get_dvb_frontend);

अटल पूर्णांक zd1301_demod_i2c_master_xfer(काष्ठा i2c_adapter *adapter,
					काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा zd1301_demod_dev *dev = i2c_get_adapdata(adapter);
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	पूर्णांक ret, i;
	अचिन्हित दीर्घ समयout;
	u8 u8पंचांगp;

	#घोषणा I2C_XFER_TIMEOUT 5
	#घोषणा ZD1301_IS_I2C_XFER_WRITE_READ(_msg, _num) \
		(_num == 2 && !(_msg[0].flags & I2C_M_RD) && (_msg[1].flags & I2C_M_RD))
	#घोषणा ZD1301_IS_I2C_XFER_WRITE(_msg, _num) \
		(_num == 1 && !(_msg[0].flags & I2C_M_RD))
	#घोषणा ZD1301_IS_I2C_XFER_READ(_msg, _num) \
		(_num == 1 && (_msg[0].flags & I2C_M_RD))
	अगर (ZD1301_IS_I2C_XFER_WRITE_READ(msg, num)) अणु
		dev_dbg(&pdev->dev, "write&read msg[0].len=%u msg[1].len=%u\n",
			msg[0].len, msg[1].len);
		अगर (msg[0].len > 1 || msg[1].len > 8) अणु
			ret = -EOPNOTSUPP;
			जाओ err;
		पूर्ण

		ret = zd1301_demod_wreg(dev, 0x6811, 0x80);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6812, 0x05);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6813, msg[1].addr << 1);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6801, msg[0].buf[0]);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6802, 0x00);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6803, 0x06);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6805, 0x00);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6804, msg[1].len);
		अगर (ret)
			जाओ err;

		/* Poll xfer पढ़ोy */
		समयout = jअगरfies + msecs_to_jअगरfies(I2C_XFER_TIMEOUT);
		क्रम (u8पंचांगp = 1; !समय_after(jअगरfies, समयout) && u8पंचांगp;) अणु
			usleep_range(500, 800);

			ret = zd1301_demod_rreg(dev, 0x6804, &u8पंचांगp);
			अगर (ret)
				जाओ err;
		पूर्ण

		क्रम (i = 0; i < msg[1].len; i++) अणु
			ret = zd1301_demod_rreg(dev, 0x0600 + i, &msg[1].buf[i]);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण अन्यथा अगर (ZD1301_IS_I2C_XFER_WRITE(msg, num)) अणु
		dev_dbg(&pdev->dev, "write msg[0].len=%u\n", msg[0].len);
		अगर (msg[0].len > 1 + 8) अणु
			ret = -EOPNOTSUPP;
			जाओ err;
		पूर्ण

		ret = zd1301_demod_wreg(dev, 0x6811, 0x80);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6812, 0x01);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6813, msg[0].addr << 1);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6800, msg[0].buf[0]);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6802, 0x00);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6803, 0x06);
		अगर (ret)
			जाओ err;

		क्रम (i = 0; i < msg[0].len - 1; i++) अणु
			ret = zd1301_demod_wreg(dev, 0x0600 + i, msg[0].buf[1 + i]);
			अगर (ret)
				जाओ err;
		पूर्ण

		ret = zd1301_demod_wreg(dev, 0x6805, 0x80);
		अगर (ret)
			जाओ err;
		ret = zd1301_demod_wreg(dev, 0x6804, msg[0].len - 1);
		अगर (ret)
			जाओ err;

		/* Poll xfer पढ़ोy */
		समयout = jअगरfies + msecs_to_jअगरfies(I2C_XFER_TIMEOUT);
		क्रम (u8पंचांगp = 1; !समय_after(jअगरfies, समयout) && u8पंचांगp;) अणु
			usleep_range(500, 800);

			ret = zd1301_demod_rreg(dev, 0x6804, &u8पंचांगp);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&pdev->dev, "unknown msg[0].len=%u\n", msg[0].len);
		ret = -EOPNOTSUPP;
		जाओ err;
	पूर्ण

	वापस num;
err:
	dev_dbg(&pdev->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल u32 zd1301_demod_i2c_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm zd1301_demod_i2c_algorithm = अणु
	.master_xfer   = zd1301_demod_i2c_master_xfer,
	.functionality = zd1301_demod_i2c_functionality,
पूर्ण;

काष्ठा i2c_adapter *zd1301_demod_get_i2c_adapter(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zd1301_demod_dev *dev = platक्रमm_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "\n");

	वापस &dev->adapter;
पूर्ण
EXPORT_SYMBOL(zd1301_demod_get_i2c_adapter);

/* Platक्रमm driver पूर्णांकerface */
अटल पूर्णांक zd1301_demod_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zd1301_demod_dev *dev;
	काष्ठा zd1301_demod_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "\n");

	अगर (!pdata) अणु
		ret = -EINVAL;
		dev_err(&pdev->dev, "cannot proceed without platform data\n");
		जाओ err;
	पूर्ण
	अगर (!pdev->dev.parent->driver) अणु
		ret = -EINVAL;
		dev_dbg(&pdev->dev, "no parent device\n");
		जाओ err;
	पूर्ण

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* Setup the state */
	dev->pdev = pdev;
	dev->gain = zd1301_demod_gain;

	/* Sleep */
	ret = zd1301_demod_wreg(dev, 0x6840, 0x21);
	अगर (ret)
		जाओ err_kमुक्त;
	ret = zd1301_demod_wreg(dev, 0x6a38, 0x07);
	अगर (ret)
		जाओ err_kमुक्त;

	/* Create I2C adapter */
	strscpy(dev->adapter.name, "ZyDAS ZD1301 demod",
		माप(dev->adapter.name));
	dev->adapter.algo = &zd1301_demod_i2c_algorithm;
	dev->adapter.algo_data = शून्य;
	dev->adapter.dev.parent = pdev->dev.parent;
	i2c_set_adapdata(&dev->adapter, dev);
	ret = i2c_add_adapter(&dev->adapter);
	अगर (ret) अणु
		dev_err(&pdev->dev, "I2C adapter add failed %d\n", ret);
		जाओ err_kमुक्त;
	पूर्ण

	/* Create dvb frontend */
	स_नकल(&dev->frontend.ops, &zd1301_demod_ops, माप(dev->frontend.ops));
	dev->frontend.demodulator_priv = dev;
	platक्रमm_set_drvdata(pdev, dev);
	dev_info(&pdev->dev, "ZyDAS ZD1301 demod attached\n");

	वापस 0;
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&pdev->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक zd1301_demod_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zd1301_demod_dev *dev = platक्रमm_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "\n");

	i2c_del_adapter(&dev->adapter);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver zd1301_demod_driver = अणु
	.driver = अणु
		.name                = "zd1301_demod",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe          = zd1301_demod_probe,
	.हटाओ         = zd1301_demod_हटाओ,
पूर्ण;
module_platक्रमm_driver(zd1301_demod_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("ZyDAS ZD1301 demodulator driver");
MODULE_LICENSE("GPL");
