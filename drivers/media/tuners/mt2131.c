<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Microtune MT2131 "QAM/8VSB single chip tuner"
 *
 *  Copyright (c) 2006 Steven Toth <stoth@linuxtv.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>

#समावेश "mt2131.h"
#समावेश "mt2131_priv.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

#घोषणा dprपूर्णांकk(level,fmt, arg...) अगर (debug >= level) \
	prपूर्णांकk(KERN_INFO "%s: " fmt, "mt2131", ## arg)

अटल u8 mt2131_config1[] = अणु
	0x01,
	0x50, 0x00, 0x50, 0x80, 0x00, 0x49, 0xfa, 0x88,
	0x08, 0x77, 0x41, 0x04, 0x00, 0x00, 0x00, 0x32,
	0x7f, 0xda, 0x4c, 0x00, 0x10, 0xaa, 0x78, 0x80,
	0xff, 0x68, 0xa0, 0xff, 0xdd, 0x00, 0x00
पूर्ण;

अटल u8 mt2131_config2[] = अणु
	0x10,
	0x7f, 0xc8, 0x0a, 0x5f, 0x00, 0x04
पूर्ण;

अटल पूर्णांक mt2131_पढ़ोreg(काष्ठा mt2131_priv *priv, u8 reg, u8 *val)
अणु
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = priv->cfg->i2c_address, .flags = 0,
		  .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = priv->cfg->i2c_address, .flags = I2C_M_RD,
		  .buf = val,  .len = 1 पूर्ण,
	पूर्ण;

	अगर (i2c_transfer(priv->i2c, msg, 2) != 2) अणु
		prपूर्णांकk(KERN_WARNING "mt2131 I2C read failed\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt2131_ग_लिखोreg(काष्ठा mt2131_priv *priv, u8 reg, u8 val)
अणु
	u8 buf[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = priv->cfg->i2c_address, .flags = 0,
			       .buf = buf, .len = 2 पूर्ण;

	अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
		prपूर्णांकk(KERN_WARNING "mt2131 I2C write failed\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt2131_ग_लिखोregs(काष्ठा mt2131_priv *priv,u8 *buf, u8 len)
अणु
	काष्ठा i2c_msg msg = अणु .addr = priv->cfg->i2c_address,
			       .flags = 0, .buf = buf, .len = len पूर्ण;

	अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
		prपूर्णांकk(KERN_WARNING "mt2131 I2C write failed (len=%i)\n",
		       (पूर्णांक)len);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt2131_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा mt2131_priv *priv;
	पूर्णांक ret=0, i;
	u32 freq;
	u8  अगर_band_center;
	u32 f_lo1, f_lo2;
	u32 भाग1, num1, भाग2, num2;
	u8  b[8];
	u8 lockval = 0;

	priv = fe->tuner_priv;

	freq = c->frequency / 1000;  /* Hz -> kHz */
	dprपूर्णांकk(1, "%s() freq=%d\n", __func__, freq);

	f_lo1 = freq + MT2131_IF1 * 1000;
	f_lo1 = (f_lo1 / 250) * 250;
	f_lo2 = f_lo1 - freq - MT2131_IF2;

	priv->frequency =  (f_lo1 - f_lo2 - MT2131_IF2) * 1000;

	/* Frequency LO1 = 16MHz * (DIV1 + NUM1/8192 ) */
	num1 = f_lo1 * 64 / (MT2131_FREF / 128);
	भाग1 = num1 / 8192;
	num1 &= 0x1fff;

	/* Frequency LO2 = 16MHz * (DIV2 + NUM2/8192 ) */
	num2 = f_lo2 * 64 / (MT2131_FREF / 128);
	भाग2 = num2 / 8192;
	num2 &= 0x1fff;

	अगर (freq <=   82500) अगर_band_center = 0x00; अन्यथा
	अगर (freq <=  137500) अगर_band_center = 0x01; अन्यथा
	अगर (freq <=  192500) अगर_band_center = 0x02; अन्यथा
	अगर (freq <=  247500) अगर_band_center = 0x03; अन्यथा
	अगर (freq <=  302500) अगर_band_center = 0x04; अन्यथा
	अगर (freq <=  357500) अगर_band_center = 0x05; अन्यथा
	अगर (freq <=  412500) अगर_band_center = 0x06; अन्यथा
	अगर (freq <=  467500) अगर_band_center = 0x07; अन्यथा
	अगर (freq <=  522500) अगर_band_center = 0x08; अन्यथा
	अगर (freq <=  577500) अगर_band_center = 0x09; अन्यथा
	अगर (freq <=  632500) अगर_band_center = 0x0A; अन्यथा
	अगर (freq <=  687500) अगर_band_center = 0x0B; अन्यथा
	अगर (freq <=  742500) अगर_band_center = 0x0C; अन्यथा
	अगर (freq <=  797500) अगर_band_center = 0x0D; अन्यथा
	अगर (freq <=  852500) अगर_band_center = 0x0E; अन्यथा
	अगर (freq <=  907500) अगर_band_center = 0x0F; अन्यथा
	अगर (freq <=  962500) अगर_band_center = 0x10; अन्यथा
	अगर (freq <= 1017500) अगर_band_center = 0x11; अन्यथा
	अगर (freq <= 1072500) अगर_band_center = 0x12; अन्यथा अगर_band_center = 0x13;

	b[0] = 1;
	b[1] = (num1 >> 5) & 0xFF;
	b[2] = (num1 & 0x1F);
	b[3] = भाग1;
	b[4] = (num2 >> 5) & 0xFF;
	b[5] = num2 & 0x1F;
	b[6] = भाग2;

	dprपूर्णांकk(1, "IF1: %dMHz IF2: %dMHz\n", MT2131_IF1, MT2131_IF2);
	dprपूर्णांकk(1, "PLL freq=%dkHz  band=%d\n", (पूर्णांक)freq, (पूर्णांक)अगर_band_center);
	dprपूर्णांकk(1, "PLL f_lo1=%dkHz  f_lo2=%dkHz\n", (पूर्णांक)f_lo1, (पूर्णांक)f_lo2);
	dprपूर्णांकk(1, "PLL div1=%d  num1=%d  div2=%d  num2=%d\n",
		(पूर्णांक)भाग1, (पूर्णांक)num1, (पूर्णांक)भाग2, (पूर्णांक)num2);
	dprपूर्णांकk(1, "PLL [1..6]: %2x %2x %2x %2x %2x %2x\n",
		(पूर्णांक)b[1], (पूर्णांक)b[2], (पूर्णांक)b[3], (पूर्णांक)b[4], (पूर्णांक)b[5],
		(पूर्णांक)b[6]);

	ret = mt2131_ग_लिखोregs(priv,b,7);
	अगर (ret < 0)
		वापस ret;

	mt2131_ग_लिखोreg(priv, 0x0b, अगर_band_center);

	/* Wait क्रम lock */
	i = 0;
	करो अणु
		mt2131_पढ़ोreg(priv, 0x08, &lockval);
		अगर ((lockval & 0x88) == 0x88)
			अवरोध;
		msleep(4);
		i++;
	पूर्ण जबतक (i < 10);

	वापस ret;
पूर्ण

अटल पूर्णांक mt2131_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा mt2131_priv *priv = fe->tuner_priv;
	dprपूर्णांकk(1, "%s()\n", __func__);
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक mt2131_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा mt2131_priv *priv = fe->tuner_priv;
	u8 lock_status = 0;
	u8 afc_status = 0;

	*status = 0;

	mt2131_पढ़ोreg(priv, 0x08, &lock_status);
	अगर ((lock_status & 0x88) == 0x88)
		*status = TUNER_STATUS_LOCKED;

	mt2131_पढ़ोreg(priv, 0x09, &afc_status);
	dprपूर्णांकk(1, "%s() - LO Status = 0x%x, AFC Status = 0x%x\n",
		__func__, lock_status, afc_status);

	वापस 0;
पूर्ण

अटल पूर्णांक mt2131_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mt2131_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर ((ret = mt2131_ग_लिखोregs(priv, mt2131_config1,
				    माप(mt2131_config1))) < 0)
		वापस ret;

	mt2131_ग_लिखोreg(priv, 0x0b, 0x09);
	mt2131_ग_लिखोreg(priv, 0x15, 0x47);
	mt2131_ग_लिखोreg(priv, 0x07, 0xf2);
	mt2131_ग_लिखोreg(priv, 0x0b, 0x01);

	अगर ((ret = mt2131_ग_लिखोregs(priv, mt2131_config2,
				    माप(mt2131_config2))) < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल व्योम mt2131_release(काष्ठा dvb_frontend *fe)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops mt2131_tuner_ops = अणु
	.info = अणु
		.name              = "Microtune MT2131",
		.frequency_min_hz  =  48 * MHz,
		.frequency_max_hz  = 860 * MHz,
		.frequency_step_hz =  50 * kHz,
	पूर्ण,

	.release       = mt2131_release,
	.init          = mt2131_init,

	.set_params    = mt2131_set_params,
	.get_frequency = mt2131_get_frequency,
	.get_status    = mt2131_get_status
पूर्ण;

काष्ठा dvb_frontend * mt2131_attach(काष्ठा dvb_frontend *fe,
				    काष्ठा i2c_adapter *i2c,
				    काष्ठा mt2131_config *cfg, u16 अगर1)
अणु
	काष्ठा mt2131_priv *priv = शून्य;
	u8 id = 0;

	dprपूर्णांकk(1, "%s()\n", __func__);

	priv = kzalloc(माप(काष्ठा mt2131_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->cfg = cfg;
	priv->i2c = i2c;

	अगर (mt2131_पढ़ोreg(priv, 0, &id) != 0) अणु
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण
	अगर ( (id != 0x3E) && (id != 0x3F) ) अणु
		prपूर्णांकk(KERN_ERR "MT2131: Device not found at addr 0x%02x\n",
		       cfg->i2c_address);
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	prपूर्णांकk(KERN_INFO "MT2131: successfully identified at address 0x%02x\n",
	       cfg->i2c_address);
	स_नकल(&fe->ops.tuner_ops, &mt2131_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	fe->tuner_priv = priv;
	वापस fe;
पूर्ण
EXPORT_SYMBOL(mt2131_attach);

MODULE_AUTHOR("Steven Toth");
MODULE_DESCRIPTION("Microtune MT2131 silicon tuner driver");
MODULE_LICENSE("GPL");
