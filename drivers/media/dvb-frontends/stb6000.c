<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
  /*
     Driver क्रम ST STB6000 DVBS Silicon tuner

     Copyright (C) 2008 Igor M. Liplianin (liplianin@me.by)


  */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <यंत्र/types.h>

#समावेश "stb6000.h"

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_DEBUG "stb6000: " args); \
	पूर्ण जबतक (0)

काष्ठा stb6000_priv अणु
	/* i2c details */
	पूर्णांक i2c_address;
	काष्ठा i2c_adapter *i2c;
	u32 frequency;
पूर्ण;

अटल व्योम stb6000_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक stb6000_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stb6000_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	u8 buf[] = अणु 10, 0 पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = priv->i2c_address,
		.flags = 0,
		.buf = buf,
		.len = 2
	पूर्ण;

	dprपूर्णांकk("%s:\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	ret = i2c_transfer(priv->i2c, &msg, 1);
	अगर (ret != 1)
		dprपूर्णांकk("%s: i2c error\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस (ret == 1) ? 0 : ret;
पूर्ण

अटल पूर्णांक stb6000_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा stb6000_priv *priv = fe->tuner_priv;
	अचिन्हित पूर्णांक n, m;
	पूर्णांक ret;
	u32 freq_mhz;
	पूर्णांक bandwidth;
	u8 buf[12];
	काष्ठा i2c_msg msg = अणु
		.addr = priv->i2c_address,
		.flags = 0,
		.buf = buf,
		.len = 12
	पूर्ण;

	dprपूर्णांकk("%s:\n", __func__);

	freq_mhz = p->frequency / 1000;
	bandwidth = p->symbol_rate / 1000000;

	अगर (bandwidth > 31)
		bandwidth = 31;

	अगर ((freq_mhz > 949) && (freq_mhz < 2151)) अणु
		buf[0] = 0x01;
		buf[1] = 0xac;
		अगर (freq_mhz < 1950)
			buf[1] = 0xaa;
		अगर (freq_mhz < 1800)
			buf[1] = 0xa8;
		अगर (freq_mhz < 1650)
			buf[1] = 0xa6;
		अगर (freq_mhz < 1530)
			buf[1] = 0xa5;
		अगर (freq_mhz < 1470)
			buf[1] = 0xa4;
		अगर (freq_mhz < 1370)
			buf[1] = 0xa2;
		अगर (freq_mhz < 1300)
			buf[1] = 0xa1;
		अगर (freq_mhz < 1200)
			buf[1] = 0xa0;
		अगर (freq_mhz < 1075)
			buf[1] = 0xbc;
		अगर (freq_mhz < 1000)
			buf[1] = 0xba;
		अगर (freq_mhz < 1075) अणु
			n = freq_mhz / 8; /* vco=lo*4 */
			m = 2;
		पूर्ण अन्यथा अणु
			n = freq_mhz / 16; /* vco=lo*2 */
			m = 1;
		पूर्ण
		buf[2] = n >> 1;
		buf[3] = (अचिन्हित अक्षर)(((n & 1) << 7) |
					(m * freq_mhz - n * 16) | 0x60);
		buf[4] = 0x04;
		buf[5] = 0x0e;

		buf[6] = (अचिन्हित अक्षर)(bandwidth);

		buf[7] = 0xd8;
		buf[8] = 0xd0;
		buf[9] = 0x50;
		buf[10] = 0xeb;
		buf[11] = 0x4f;

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = i2c_transfer(priv->i2c, &msg, 1);
		अगर (ret != 1)
			dprपूर्णांकk("%s: i2c error\n", __func__);

		udelay(10);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);

		buf[0] = 0x07;
		buf[1] = 0xdf;
		buf[2] = 0xd0;
		buf[3] = 0x50;
		buf[4] = 0xfb;
		msg.len = 5;

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = i2c_transfer(priv->i2c, &msg, 1);
		अगर (ret != 1)
			dprपूर्णांकk("%s: i2c error\n", __func__);

		udelay(10);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);

		priv->frequency = freq_mhz * 1000;

		वापस (ret == 1) ? 0 : ret;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक stb6000_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा stb6000_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops stb6000_tuner_ops = अणु
	.info = अणु
		.name = "ST STB6000",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz
	पूर्ण,
	.release = stb6000_release,
	.sleep = stb6000_sleep,
	.set_params = stb6000_set_params,
	.get_frequency = stb6000_get_frequency,
पूर्ण;

काष्ठा dvb_frontend *stb6000_attach(काष्ठा dvb_frontend *fe, पूर्णांक addr,
						काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा stb6000_priv *priv = शून्य;
	u8 b0[] = अणु 0 पूर्ण;
	u8 b1[] = अणु 0, 0 पूर्ण;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = addr,
			.flags = 0,
			.buf = b0,
			.len = 0
		पूर्ण, अणु
			.addr = addr,
			.flags = I2C_M_RD,
			.buf = b1,
			.len = 2
		पूर्ण
	पूर्ण;
	पूर्णांक ret;

	dprपूर्णांकk("%s:\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* is some i2c device here ? */
	ret = i2c_transfer(i2c, msg, 2);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (ret != 2)
		वापस शून्य;

	priv = kzalloc(माप(काष्ठा stb6000_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->i2c_address = addr;
	priv->i2c = i2c;

	स_नकल(&fe->ops.tuner_ops, &stb6000_tuner_ops,
				माप(काष्ठा dvb_tuner_ops));

	fe->tuner_priv = priv;

	वापस fe;
पूर्ण
EXPORT_SYMBOL(stb6000_attach);

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("DVB STB6000 driver");
MODULE_AUTHOR("Igor M. Liplianin <liplianin@me.by>");
MODULE_LICENSE("GPL");
