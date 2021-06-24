<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Microtune MT2060 "Single chip dual conversion broadband tuner"
 *
 *  Copyright (c) 2006 Olivier DANET <odanet@caramail.com>
 */

/* In that file, frequencies are expressed in kiloHertz to aव्योम 32 bits overflows */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>

#समावेश "mt2060.h"
#समावेश "mt2060_priv.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

#घोषणा dprपूर्णांकk(args...) करो अणु अगर (debug) अणुprपूर्णांकk(KERN_DEBUG "MT2060: " args); prपूर्णांकk("\n"); पूर्णपूर्ण जबतक (0)

// Reads a single रेजिस्टर
अटल पूर्णांक mt2060_पढ़ोreg(काष्ठा mt2060_priv *priv, u8 reg, u8 *val)
अणु
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = priv->cfg->i2c_address, .flags = 0, .len = 1 पूर्ण,
		अणु .addr = priv->cfg->i2c_address, .flags = I2C_M_RD, .len = 1 पूर्ण,
	पूर्ण;
	पूर्णांक rc = 0;
	u8 *b;

	b = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	b[0] = reg;
	b[1] = 0;

	msg[0].buf = b;
	msg[1].buf = b + 1;

	अगर (i2c_transfer(priv->i2c, msg, 2) != 2) अणु
		prपूर्णांकk(KERN_WARNING "mt2060 I2C read failed\n");
		rc = -EREMOTEIO;
	पूर्ण
	*val = b[1];
	kमुक्त(b);

	वापस rc;
पूर्ण

// Writes a single रेजिस्टर
अटल पूर्णांक mt2060_ग_लिखोreg(काष्ठा mt2060_priv *priv, u8 reg, u8 val)
अणु
	काष्ठा i2c_msg msg = अणु
		.addr = priv->cfg->i2c_address, .flags = 0, .len = 2
	पूर्ण;
	u8 *buf;
	पूर्णांक rc = 0;

	buf = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = reg;
	buf[1] = val;

	msg.buf = buf;

	अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
		prपूर्णांकk(KERN_WARNING "mt2060 I2C write failed\n");
		rc = -EREMOTEIO;
	पूर्ण
	kमुक्त(buf);
	वापस rc;
पूर्ण

// Writes a set of consecutive रेजिस्टरs
अटल पूर्णांक mt2060_ग_लिखोregs(काष्ठा mt2060_priv *priv,u8 *buf, u8 len)
अणु
	पूर्णांक rem, val_len;
	u8 *xfer_buf;
	पूर्णांक rc = 0;
	काष्ठा i2c_msg msg = अणु
		.addr = priv->cfg->i2c_address, .flags = 0
	पूर्ण;

	xfer_buf = kदो_स्मृति(16, GFP_KERNEL);
	अगर (!xfer_buf)
		वापस -ENOMEM;

	msg.buf = xfer_buf;

	क्रम (rem = len - 1; rem > 0; rem -= priv->i2c_max_regs) अणु
		val_len = min_t(पूर्णांक, rem, priv->i2c_max_regs);
		msg.len = 1 + val_len;
		xfer_buf[0] = buf[0] + len - 1 - rem;
		स_नकल(&xfer_buf[1], &buf[1 + len - 1 - rem], val_len);

		अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
			prपूर्णांकk(KERN_WARNING "mt2060 I2C write failed (len=%i)\n", val_len);
			rc = -EREMOTEIO;
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(xfer_buf);
	वापस rc;
पूर्ण

// Initialisation sequences
// LNABAND=3, NUM1=0x3C, DIV1=0x74, NUM2=0x1080, DIV2=0x49
अटल u8 mt2060_config1[] = अणु
	REG_LO1C1,
	0x3F,	0x74,	0x00,	0x08,	0x93
पूर्ण;

// FMCG=2, GP2=0, GP1=0
अटल u8 mt2060_config2[] = अणु
	REG_MISC_CTRL,
	0x20,	0x1E,	0x30,	0xff,	0x80,	0xff,	0x00,	0x2c,	0x42
पूर्ण;

//  VGAG=3, V1CSE=1

#अगर_घोषित  MT2060_SPURCHECK
/* The function below calculates the frequency offset between the output frequency अगर2
 and the बंदr cross modulation subcarrier between lo1 and lo2 up to the tenth harmonic */
अटल पूर्णांक mt2060_spurcalc(u32 lo1,u32 lo2,u32 अगर2)
अणु
	पूर्णांक I,J;
	पूर्णांक dia,diamin,dअगरf;
	diamin=1000000;
	क्रम (I = 1; I < 10; I++) अणु
		J = ((2*I*lo1)/lo2+1)/2;
		dअगरf = I*(पूर्णांक)lo1-J*(पूर्णांक)lo2;
		अगर (dअगरf < 0) dअगरf=-dअगरf;
		dia = (dअगरf-(पूर्णांक)अगर2);
		अगर (dia < 0) dia=-dia;
		अगर (diamin > dia) diamin=dia;
	पूर्ण
	वापस diamin;
पूर्ण

#घोषणा BANDWIDTH 4000 // kHz

/* Calculates the frequency offset to add to aव्योम spurs. Returns 0 अगर no offset is needed */
अटल पूर्णांक mt2060_spurcheck(u32 lo1,u32 lo2,u32 अगर2)
अणु
	u32 Spur,Sp1,Sp2;
	पूर्णांक I,J;
	I=0;
	J=1000;

	Spur=mt2060_spurcalc(lo1,lo2,अगर2);
	अगर (Spur < BANDWIDTH) अणु
		/* Potential spurs detected */
		dprपूर्णांकk("Spurs before : f_lo1: %d  f_lo2: %d  (kHz)",
			(पूर्णांक)lo1,(पूर्णांक)lo2);
		I=1000;
		Sp1 = mt2060_spurcalc(lo1+I,lo2+I,अगर2);
		Sp2 = mt2060_spurcalc(lo1-I,lo2-I,अगर2);

		अगर (Sp1 < Sp2) अणु
			J=-J; I=-I; Spur=Sp2;
		पूर्ण अन्यथा
			Spur=Sp1;

		जबतक (Spur < BANDWIDTH) अणु
			I += J;
			Spur = mt2060_spurcalc(lo1+I,lo2+I,अगर2);
		पूर्ण
		dprपूर्णांकk("Spurs after  : f_lo1: %d  f_lo2: %d  (kHz)",
			(पूर्णांक)(lo1+I),(पूर्णांक)(lo2+I));
	पूर्ण
	वापस I;
पूर्ण
#पूर्ण_अगर

#घोषणा IF2  36150       // IF2 frequency = 36.150 MHz
#घोषणा FREF 16000       // Quartz oscillator 16 MHz

अटल पूर्णांक mt2060_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा mt2060_priv *priv;
	पूर्णांक i=0;
	u32 freq;
	u8  lnaband;
	u32 f_lo1,f_lo2;
	u32 भाग1,num1,भाग2,num2;
	u8  b[8];
	u32 अगर1;

	priv = fe->tuner_priv;

	अगर1 = priv->अगर1_freq;
	b[0] = REG_LO1B1;
	b[1] = 0xFF;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	mt2060_ग_लिखोregs(priv,b,2);

	freq = c->frequency / 1000; /* Hz -> kHz */

	f_lo1 = freq + अगर1 * 1000;
	f_lo1 = (f_lo1 / 250) * 250;
	f_lo2 = f_lo1 - freq - IF2;
	// From the Comtech datasheet, the step used is 50kHz. The tuner chip could be more precise
	f_lo2 = ((f_lo2 + 25) / 50) * 50;
	priv->frequency =  (f_lo1 - f_lo2 - IF2) * 1000;

#अगर_घोषित MT2060_SPURCHECK
	// LO-related spurs detection and correction
	num1   = mt2060_spurcheck(f_lo1,f_lo2,IF2);
	f_lo1 += num1;
	f_lo2 += num1;
#पूर्ण_अगर
	//Frequency LO1 = 16MHz * (DIV1 + NUM1/64 )
	num1 = f_lo1 / (FREF / 64);
	भाग1 = num1 / 64;
	num1 &= 0x3f;

	// Frequency LO2 = 16MHz * (DIV2 + NUM2/8192 )
	num2 = f_lo2 * 64 / (FREF / 128);
	भाग2 = num2 / 8192;
	num2 &= 0x1fff;

	अगर (freq <=  95000) lnaband = 0xB0; अन्यथा
	अगर (freq <= 180000) lnaband = 0xA0; अन्यथा
	अगर (freq <= 260000) lnaband = 0x90; अन्यथा
	अगर (freq <= 335000) lnaband = 0x80; अन्यथा
	अगर (freq <= 425000) lnaband = 0x70; अन्यथा
	अगर (freq <= 480000) lnaband = 0x60; अन्यथा
	अगर (freq <= 570000) lnaband = 0x50; अन्यथा
	अगर (freq <= 645000) lnaband = 0x40; अन्यथा
	अगर (freq <= 730000) lnaband = 0x30; अन्यथा
	अगर (freq <= 810000) lnaband = 0x20; अन्यथा lnaband = 0x10;

	b[0] = REG_LO1C1;
	b[1] = lnaband | ((num1 >>2) & 0x0F);
	b[2] = भाग1;
	b[3] = (num2 & 0x0F)  | ((num1 & 3) << 4);
	b[4] = num2 >> 4;
	b[5] = ((num2 >>12) & 1) | (भाग2 << 1);

	dprपूर्णांकk("IF1: %dMHz",(पूर्णांक)अगर1);
	dprपूर्णांकk("PLL freq=%dkHz  f_lo1=%dkHz  f_lo2=%dkHz",(पूर्णांक)freq,(पूर्णांक)f_lo1,(पूर्णांक)f_lo2);
	dprपूर्णांकk("PLL div1=%d  num1=%d  div2=%d  num2=%d",(पूर्णांक)भाग1,(पूर्णांक)num1,(पूर्णांक)भाग2,(पूर्णांक)num2);
	dprपूर्णांकk("PLL [1..5]: %2x %2x %2x %2x %2x",(पूर्णांक)b[1],(पूर्णांक)b[2],(पूर्णांक)b[3],(पूर्णांक)b[4],(पूर्णांक)b[5]);

	mt2060_ग_लिखोregs(priv,b,6);

	//Waits क्रम pll lock or समयout
	i = 0;
	करो अणु
		mt2060_पढ़ोreg(priv,REG_LO_STATUS,b);
		अगर ((b[0] & 0x88)==0x88)
			अवरोध;
		msleep(4);
		i++;
	पूर्ण जबतक (i<10);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	वापस 0;
पूर्ण

अटल व्योम mt2060_calibrate(काष्ठा mt2060_priv *priv)
अणु
	u8 b = 0;
	पूर्णांक i = 0;

	अगर (mt2060_ग_लिखोregs(priv,mt2060_config1,माप(mt2060_config1)))
		वापस;
	अगर (mt2060_ग_लिखोregs(priv,mt2060_config2,माप(mt2060_config2)))
		वापस;

	/* initialize the घड़ी output */
	mt2060_ग_लिखोreg(priv, REG_VGAG, (priv->cfg->घड़ी_out << 6) | 0x30);

	करो अणु
		b |= (1 << 6); // FM1SS;
		mt2060_ग_लिखोreg(priv, REG_LO2C1,b);
		msleep(20);

		अगर (i == 0) अणु
			b |= (1 << 7); // FM1CA;
			mt2060_ग_लिखोreg(priv, REG_LO2C1,b);
			b &= ~(1 << 7); // FM1CA;
			msleep(20);
		पूर्ण

		b &= ~(1 << 6); // FM1SS
		mt2060_ग_लिखोreg(priv, REG_LO2C1,b);

		msleep(20);
		i++;
	पूर्ण जबतक (i < 9);

	i = 0;
	जबतक (i++ < 10 && mt2060_पढ़ोreg(priv, REG_MISC_STAT, &b) == 0 && (b & (1 << 6)) == 0)
		msleep(20);

	अगर (i <= 10) अणु
		mt2060_पढ़ोreg(priv, REG_FM_FREQ, &priv->fmfreq); // now find out, what is fmreq used क्रम :)
		dprपूर्णांकk("calibration was successful: %d", (पूर्णांक)priv->fmfreq);
	पूर्ण अन्यथा
		dprपूर्णांकk("FMCAL timed out");
पूर्ण

अटल पूर्णांक mt2060_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा mt2060_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक mt2060_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	*frequency = IF2 * 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक mt2060_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mt2060_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	अगर (priv->sleep) अणु
		ret = mt2060_ग_लिखोreg(priv, REG_MISC_CTRL, 0x20);
		अगर (ret)
			जाओ err_i2c_gate_ctrl;
	पूर्ण

	ret = mt2060_ग_लिखोreg(priv, REG_VGAG,
			      (priv->cfg->घड़ी_out << 6) | 0x33);

err_i2c_gate_ctrl:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	वापस ret;
पूर्ण

अटल पूर्णांक mt2060_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mt2060_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	ret = mt2060_ग_लिखोreg(priv, REG_VGAG,
			      (priv->cfg->घड़ी_out << 6) | 0x30);
	अगर (ret)
		जाओ err_i2c_gate_ctrl;

	अगर (priv->sleep)
		ret = mt2060_ग_लिखोreg(priv, REG_MISC_CTRL, 0xe8);

err_i2c_gate_ctrl:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	वापस ret;
पूर्ण

अटल व्योम mt2060_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops mt2060_tuner_ops = अणु
	.info = अणु
		.name              = "Microtune MT2060",
		.frequency_min_hz  =  48 * MHz,
		.frequency_max_hz  = 860 * MHz,
		.frequency_step_hz =  50 * kHz,
	पूर्ण,

	.release       = mt2060_release,

	.init          = mt2060_init,
	.sleep         = mt2060_sleep,

	.set_params    = mt2060_set_params,
	.get_frequency = mt2060_get_frequency,
	.get_अगर_frequency = mt2060_get_अगर_frequency,
पूर्ण;

/* This functions tries to identअगरy a MT2060 tuner by पढ़ोing the PART/REV रेजिस्टर. This is hasty. */
काष्ठा dvb_frontend * mt2060_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा mt2060_config *cfg, u16 अगर1)
अणु
	काष्ठा mt2060_priv *priv = शून्य;
	u8 id = 0;

	priv = kzalloc(माप(काष्ठा mt2060_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->cfg      = cfg;
	priv->i2c      = i2c;
	priv->अगर1_freq = अगर1;
	priv->i2c_max_regs = ~0;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	अगर (mt2060_पढ़ोreg(priv,REG_PART_REV,&id) != 0) अणु
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	अगर (id != PART_REV) अणु
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण
	prपूर्णांकk(KERN_INFO "MT2060: successfully identified (IF1 = %d)\n", अगर1);
	स_नकल(&fe->ops.tuner_ops, &mt2060_tuner_ops, माप(काष्ठा dvb_tuner_ops));

	fe->tuner_priv = priv;

	mt2060_calibrate(priv);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	वापस fe;
पूर्ण
EXPORT_SYMBOL(mt2060_attach);

अटल पूर्णांक mt2060_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mt2060_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe;
	काष्ठा mt2060_priv *dev;
	पूर्णांक ret;
	u8 chip_id;

	dev_dbg(&client->dev, "\n");

	अगर (!pdata) अणु
		dev_err(&client->dev, "Cannot proceed without platform data\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	dev = devm_kzalloc(&client->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	fe = pdata->dvb_frontend;
	dev->config.i2c_address = client->addr;
	dev->config.घड़ी_out = pdata->घड़ी_out;
	dev->cfg = &dev->config;
	dev->i2c = client->adapter;
	dev->अगर1_freq = pdata->अगर1 ? pdata->अगर1 : 1220;
	dev->client = client;
	dev->i2c_max_regs = pdata->i2c_ग_लिखो_max ? pdata->i2c_ग_लिखो_max - 1 : ~0;
	dev->sleep = true;

	ret = mt2060_पढ़ोreg(dev, REG_PART_REV, &chip_id);
	अगर (ret) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	dev_dbg(&client->dev, "chip id=%02x\n", chip_id);

	अगर (chip_id != PART_REV) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* Power on, calibrate, sleep */
	ret = mt2060_ग_लिखोreg(dev, REG_MISC_CTRL, 0x20);
	अगर (ret)
		जाओ err;
	mt2060_calibrate(dev);
	ret = mt2060_ग_लिखोreg(dev, REG_MISC_CTRL, 0xe8);
	अगर (ret)
		जाओ err;

	dev_info(&client->dev, "Microtune MT2060 successfully identified\n");
	स_नकल(&fe->ops.tuner_ops, &mt2060_tuner_ops, माप(fe->ops.tuner_ops));
	fe->ops.tuner_ops.release = शून्य;
	fe->tuner_priv = dev;
	i2c_set_clientdata(client, dev);

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mt2060_हटाओ(काष्ठा i2c_client *client)
अणु
	dev_dbg(&client->dev, "\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mt2060_id_table[] = अणु
	अणु"mt2060", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mt2060_id_table);

अटल काष्ठा i2c_driver mt2060_driver = अणु
	.driver = अणु
		.name = "mt2060",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= mt2060_probe,
	.हटाओ		= mt2060_हटाओ,
	.id_table	= mt2060_id_table,
पूर्ण;

module_i2c_driver(mt2060_driver);

MODULE_AUTHOR("Olivier DANET");
MODULE_DESCRIPTION("Microtune MT2060 silicon tuner driver");
MODULE_LICENSE("GPL");
