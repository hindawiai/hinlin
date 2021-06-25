<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Microtune MT2266 "Direct conversion low power broadband tuner"
 *
 *  Copyright (c) 2007 Olivier DANET <odanet@caramail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "mt2266.h"

#घोषणा I2C_ADDRESS 0x60

#घोषणा REG_PART_REV   0
#घोषणा REG_TUNE       1
#घोषणा REG_BAND       6
#घोषणा REG_BANDWIDTH  8
#घोषणा REG_LOCK       0x12

#घोषणा PART_REV 0x85

काष्ठा mt2266_priv अणु
	काष्ठा mt2266_config *cfg;
	काष्ठा i2c_adapter   *i2c;

	u32 frequency;
	u32 bandwidth;
	u8 band;
पूर्ण;

#घोषणा MT2266_VHF 1
#घोषणा MT2266_UHF 0

/* Here, frequencies are expressed in kiloHertz to aव्योम 32 bits overflows */

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

#घोषणा dprपूर्णांकk(args...) करो अणु अगर (debug) अणुprपूर्णांकk(KERN_DEBUG "MT2266: " args); prपूर्णांकk("\n"); पूर्णपूर्ण जबतक (0)

// Reads a single रेजिस्टर
अटल पूर्णांक mt2266_पढ़ोreg(काष्ठा mt2266_priv *priv, u8 reg, u8 *val)
अणु
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = priv->cfg->i2c_address, .flags = 0,        .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = priv->cfg->i2c_address, .flags = I2C_M_RD, .buf = val,  .len = 1 पूर्ण,
	पूर्ण;
	अगर (i2c_transfer(priv->i2c, msg, 2) != 2) अणु
		prपूर्णांकk(KERN_WARNING "MT2266 I2C read failed\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

// Writes a single रेजिस्टर
अटल पूर्णांक mt2266_ग_लिखोreg(काष्ठा mt2266_priv *priv, u8 reg, u8 val)
अणु
	u8 buf[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = priv->cfg->i2c_address, .flags = 0, .buf = buf, .len = 2
	पूर्ण;
	अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
		prपूर्णांकk(KERN_WARNING "MT2266 I2C write failed\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

// Writes a set of consecutive रेजिस्टरs
अटल पूर्णांक mt2266_ग_लिखोregs(काष्ठा mt2266_priv *priv,u8 *buf, u8 len)
अणु
	काष्ठा i2c_msg msg = अणु
		.addr = priv->cfg->i2c_address, .flags = 0, .buf = buf, .len = len
	पूर्ण;
	अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
		prपूर्णांकk(KERN_WARNING "MT2266 I2C write failed (len=%i)\n",(पूर्णांक)len);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

// Initialisation sequences
अटल u8 mt2266_init1[] = अणु REG_TUNE, 0x00, 0x00, 0x28,
				 0x00, 0x52, 0x99, 0x3f पूर्ण;

अटल u8 mt2266_init2[] = अणु
    0x17, 0x6d, 0x71, 0x61, 0xc0, 0xbf, 0xff, 0xdc, 0x00, 0x0a, 0xd4,
    0x03, 0x64, 0x64, 0x64, 0x64, 0x22, 0xaa, 0xf2, 0x1e, 0x80, 0x14,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7f, 0x5e, 0x3f, 0xff, 0xff,
    0xff, 0x00, 0x77, 0x0f, 0x2d
पूर्ण;

अटल u8 mt2266_init_8mhz[] = अणु REG_BANDWIDTH, 0x22, 0x22, 0x22, 0x22,
						0x22, 0x22, 0x22, 0x22 पूर्ण;

अटल u8 mt2266_init_7mhz[] = अणु REG_BANDWIDTH, 0x32, 0x32, 0x32, 0x32,
						0x32, 0x32, 0x32, 0x32 पूर्ण;

अटल u8 mt2266_init_6mhz[] = अणु REG_BANDWIDTH, 0xa7, 0xa7, 0xa7, 0xa7,
						0xa7, 0xa7, 0xa7, 0xa7 पूर्ण;

अटल u8 mt2266_uhf[] = अणु 0x1d, 0xdc, 0x00, 0x0a, 0xd4, 0x03, 0x64, 0x64,
			   0x64, 0x64, 0x22, 0xaa, 0xf2, 0x1e, 0x80, 0x14 पूर्ण;

अटल u8 mt2266_vhf[] = अणु 0x1d, 0xfe, 0x00, 0x00, 0xb4, 0x03, 0xa5, 0xa5,
			   0xa5, 0xa5, 0x82, 0xaa, 0xf1, 0x17, 0x80, 0x1f पूर्ण;

#घोषणा FREF 30000       // Quartz oscillator 30 MHz

अटल पूर्णांक mt2266_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा mt2266_priv *priv;
	पूर्णांक ret=0;
	u32 freq;
	u32 tune;
	u8  lnaband;
	u8  b[10];
	पूर्णांक i;
	u8 band;

	priv = fe->tuner_priv;

	freq = priv->frequency / 1000; /* Hz -> kHz */
	अगर (freq < 470000 && freq > 230000)
		वापस -EINVAL; /* Gap between VHF and UHF bands */

	priv->frequency = c->frequency;
	tune = 2 * freq * (8192/16) / (FREF/16);
	band = (freq < 300000) ? MT2266_VHF : MT2266_UHF;
	अगर (band == MT2266_VHF)
		tune *= 2;

	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		mt2266_ग_लिखोregs(priv, mt2266_init_6mhz,
				 माप(mt2266_init_6mhz));
		अवरोध;
	हाल 8000000:
		mt2266_ग_लिखोregs(priv, mt2266_init_8mhz,
				 माप(mt2266_init_8mhz));
		अवरोध;
	हाल 7000000:
	शेष:
		mt2266_ग_लिखोregs(priv, mt2266_init_7mhz,
				 माप(mt2266_init_7mhz));
		अवरोध;
	पूर्ण
	priv->bandwidth = c->bandwidth_hz;

	अगर (band == MT2266_VHF && priv->band == MT2266_UHF) अणु
		dprपूर्णांकk("Switch from UHF to VHF");
		mt2266_ग_लिखोreg(priv, 0x05, 0x04);
		mt2266_ग_लिखोreg(priv, 0x19, 0x61);
		mt2266_ग_लिखोregs(priv, mt2266_vhf, माप(mt2266_vhf));
	पूर्ण अन्यथा अगर (band == MT2266_UHF && priv->band == MT2266_VHF) अणु
		dprपूर्णांकk("Switch from VHF to UHF");
		mt2266_ग_लिखोreg(priv, 0x05, 0x52);
		mt2266_ग_लिखोreg(priv, 0x19, 0x61);
		mt2266_ग_लिखोregs(priv, mt2266_uhf, माप(mt2266_uhf));
	पूर्ण
	msleep(10);

	अगर (freq <= 495000)
		lnaband = 0xEE;
	अन्यथा अगर (freq <= 525000)
		lnaband = 0xDD;
	अन्यथा अगर (freq <= 550000)
		lnaband = 0xCC;
	अन्यथा अगर (freq <= 580000)
		lnaband = 0xBB;
	अन्यथा अगर (freq <= 605000)
		lnaband = 0xAA;
	अन्यथा अगर (freq <= 630000)
		lnaband = 0x99;
	अन्यथा अगर (freq <= 655000)
		lnaband = 0x88;
	अन्यथा अगर (freq <= 685000)
		lnaband = 0x77;
	अन्यथा अगर (freq <= 710000)
		lnaband = 0x66;
	अन्यथा अगर (freq <= 735000)
		lnaband = 0x55;
	अन्यथा अगर (freq <= 765000)
		lnaband = 0x44;
	अन्यथा अगर (freq <= 802000)
		lnaband = 0x33;
	अन्यथा अगर (freq <= 840000)
		lnaband = 0x22;
	अन्यथा
		lnaband = 0x11;

	b[0] = REG_TUNE;
	b[1] = (tune >> 8) & 0x1F;
	b[2] = tune & 0xFF;
	b[3] = tune >> 13;
	mt2266_ग_लिखोregs(priv,b,4);

	dprपूर्णांकk("set_parms: tune=%d band=%d %s",
		(पूर्णांक) tune, (पूर्णांक) lnaband,
		(band == MT2266_UHF) ? "UHF" : "VHF");
	dprपूर्णांकk("set_parms: [1..3]: %2x %2x %2x",
		(पूर्णांक) b[1], (पूर्णांक) b[2], (पूर्णांक)b[3]);

	अगर (band == MT2266_UHF) अणु
		b[0] = 0x05;
		b[1] = (priv->band == MT2266_VHF) ? 0x52 : 0x62;
		b[2] = lnaband;
		mt2266_ग_लिखोregs(priv, b, 3);
	पूर्ण

	/* Wait क्रम pll lock or समयout */
	i = 0;
	करो अणु
		mt2266_पढ़ोreg(priv,REG_LOCK,b);
		अगर (b[0] & 0x40)
			अवरोध;
		msleep(10);
		i++;
	पूर्ण जबतक (i<10);
	dprपूर्णांकk("Lock when i=%i",(पूर्णांक)i);

	अगर (band == MT2266_UHF && priv->band == MT2266_VHF)
		mt2266_ग_लिखोreg(priv, 0x05, 0x62);

	priv->band = band;

	वापस ret;
पूर्ण

अटल व्योम mt2266_calibrate(काष्ठा mt2266_priv *priv)
अणु
	mt2266_ग_लिखोreg(priv, 0x11, 0x03);
	mt2266_ग_लिखोreg(priv, 0x11, 0x01);
	mt2266_ग_लिखोregs(priv, mt2266_init1, माप(mt2266_init1));
	mt2266_ग_लिखोregs(priv, mt2266_init2, माप(mt2266_init2));
	mt2266_ग_लिखोreg(priv, 0x33, 0x5e);
	mt2266_ग_लिखोreg(priv, 0x10, 0x10);
	mt2266_ग_लिखोreg(priv, 0x10, 0x00);
	mt2266_ग_लिखोregs(priv, mt2266_init_8mhz, माप(mt2266_init_8mhz));
	msleep(25);
	mt2266_ग_लिखोreg(priv, 0x17, 0x6d);
	mt2266_ग_लिखोreg(priv, 0x1c, 0x00);
	msleep(75);
	mt2266_ग_लिखोreg(priv, 0x17, 0x6d);
	mt2266_ग_लिखोreg(priv, 0x1c, 0xff);
पूर्ण

अटल पूर्णांक mt2266_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा mt2266_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक mt2266_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा mt2266_priv *priv = fe->tuner_priv;
	*bandwidth = priv->bandwidth;
	वापस 0;
पूर्ण

अटल पूर्णांक mt2266_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा mt2266_priv *priv = fe->tuner_priv;
	ret = mt2266_ग_लिखोreg(priv, 0x17, 0x6d);
	अगर (ret < 0)
		वापस ret;
	ret = mt2266_ग_लिखोreg(priv, 0x1c, 0xff);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक mt2266_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mt2266_priv *priv = fe->tuner_priv;
	mt2266_ग_लिखोreg(priv, 0x17, 0x6d);
	mt2266_ग_लिखोreg(priv, 0x1c, 0x00);
	वापस 0;
पूर्ण

अटल व्योम mt2266_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops mt2266_tuner_ops = अणु
	.info = अणु
		.name              = "Microtune MT2266",
		.frequency_min_hz  = 174 * MHz,
		.frequency_max_hz  = 862 * MHz,
		.frequency_step_hz =  50 * kHz,
	पूर्ण,
	.release       = mt2266_release,
	.init          = mt2266_init,
	.sleep         = mt2266_sleep,
	.set_params    = mt2266_set_params,
	.get_frequency = mt2266_get_frequency,
	.get_bandwidth = mt2266_get_bandwidth
पूर्ण;

काष्ठा dvb_frontend * mt2266_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा mt2266_config *cfg)
अणु
	काष्ठा mt2266_priv *priv = शून्य;
	u8 id = 0;

	priv = kzalloc(माप(काष्ठा mt2266_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->cfg      = cfg;
	priv->i2c      = i2c;
	priv->band     = MT2266_UHF;

	अगर (mt2266_पढ़ोreg(priv, 0, &id)) अणु
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण
	अगर (id != PART_REV) अणु
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण
	prपूर्णांकk(KERN_INFO "MT2266: successfully identified\n");
	स_नकल(&fe->ops.tuner_ops, &mt2266_tuner_ops, माप(काष्ठा dvb_tuner_ops));

	fe->tuner_priv = priv;
	mt2266_calibrate(priv);
	वापस fe;
पूर्ण
EXPORT_SYMBOL(mt2266_attach);

MODULE_AUTHOR("Olivier DANET");
MODULE_DESCRIPTION("Microtune MT2266 silicon tuner driver");
MODULE_LICENSE("GPL");
