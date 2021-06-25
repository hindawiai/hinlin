<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
  /*
     Driver क्रम Philips tda8262/tda8263 DVBS Silicon tuners

     (c) 2006 Andrew de Quincey


  */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <यंत्र/types.h>

#समावेश "tda826x.h"

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "tda826x: " args); \
	पूर्ण जबतक (0)

काष्ठा tda826x_priv अणु
	/* i2c details */
	पूर्णांक i2c_address;
	काष्ठा i2c_adapter *i2c;
	u8 has_loopthrough:1;
	u32 frequency;
पूर्ण;

अटल व्योम tda826x_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक tda826x_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda826x_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	u8 buf [] = अणु 0x00, 0x8d पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_address, .flags = 0, .buf = buf, .len = 2 पूर्ण;

	dprपूर्णांकk("%s:\n", __func__);

	अगर (!priv->has_loopthrough)
		buf[1] = 0xad;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर ((ret = i2c_transfer (priv->i2c, &msg, 1)) != 1) अणु
		dprपूर्णांकk("%s: i2c error\n", __func__);
	पूर्ण
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस (ret == 1) ? 0 : ret;
पूर्ण

अटल पूर्णांक tda826x_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा tda826x_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	u32 भाग;
	u32 ksyms;
	u32 bandwidth;
	u8 buf [11];
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_address, .flags = 0, .buf = buf, .len = 11 पूर्ण;

	dprपूर्णांकk("%s:\n", __func__);

	भाग = (p->frequency + (1000-1)) / 1000;

	/* BW = ((1 + RO) * SR/2 + 5) * 1.3      [SR in MSPS, BW in MHz] */
	/* with R0 = 0.35 and some transक्रमmations: */
	ksyms = p->symbol_rate / 1000;
	bandwidth = (878 * ksyms + 6500000) / 1000000 + 1;
	अगर (bandwidth < 5)
		bandwidth = 5;
	अन्यथा अगर (bandwidth > 36)
		bandwidth = 36;

	buf[0] = 0x00; // subaddress
	buf[1] = 0x09; // घातerकरोwn RSSI + the magic value 1
	अगर (!priv->has_loopthrough)
		buf[1] |= 0x20; // घातer करोwn loopthrough अगर not needed
	buf[2] = (1<<5) | 0x0b; // 1Mhz + 0.45 VCO
	buf[3] = भाग >> 7;
	buf[4] = भाग << 1;
	buf[5] = ((bandwidth - 5) << 3) | 7; /* baseband cut-off */
	buf[6] = 0xfe; // baseband gain 9 db + no RF attenuation
	buf[7] = 0x83; // अक्षरge pumps at high, tests off
	buf[8] = 0x80; // recommended value 4 क्रम AMPVCO + disable ports.
	buf[9] = 0x1a; // normal calसमय + recommended values क्रम SELTH + SELVTL
	buf[10] = 0xd4; // recommended value 13 क्रम BBIAS + unknown bit set on

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर ((ret = i2c_transfer (priv->i2c, &msg, 1)) != 1) अणु
		dprपूर्णांकk("%s: i2c error\n", __func__);
	पूर्ण
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	priv->frequency = भाग * 1000;

	वापस (ret == 1) ? 0 : ret;
पूर्ण

अटल पूर्णांक tda826x_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tda826x_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tda826x_tuner_ops = अणु
	.info = अणु
		.name = "Philips TDA826X",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2175 * MHz
	पूर्ण,
	.release = tda826x_release,
	.sleep = tda826x_sleep,
	.set_params = tda826x_set_params,
	.get_frequency = tda826x_get_frequency,
पूर्ण;

काष्ठा dvb_frontend *tda826x_attach(काष्ठा dvb_frontend *fe, पूर्णांक addr, काष्ठा i2c_adapter *i2c, पूर्णांक has_loopthrough)
अणु
	काष्ठा tda826x_priv *priv = शून्य;
	u8 b1 [] = अणु 0, 0 पूर्ण;
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = addr, .flags = 0,        .buf = शून्य, .len = 0 पूर्ण,
		अणु .addr = addr, .flags = I2C_M_RD, .buf = b1, .len = 2 पूर्ण
	पूर्ण;
	पूर्णांक ret;

	dprपूर्णांकk("%s:\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	ret = i2c_transfer (i2c, msg, 2);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (ret != 2)
		वापस शून्य;
	अगर (!(b1[1] & 0x80))
		वापस शून्य;

	priv = kzalloc(माप(काष्ठा tda826x_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->i2c_address = addr;
	priv->i2c = i2c;
	priv->has_loopthrough = has_loopthrough;

	स_नकल(&fe->ops.tuner_ops, &tda826x_tuner_ops, माप(काष्ठा dvb_tuner_ops));

	fe->tuner_priv = priv;

	वापस fe;
पूर्ण
EXPORT_SYMBOL(tda826x_attach);

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("DVB TDA826x driver");
MODULE_AUTHOR("Andrew de Quincey");
MODULE_LICENSE("GPL");
