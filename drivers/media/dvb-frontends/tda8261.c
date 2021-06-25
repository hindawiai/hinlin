<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	TDA8261 8PSK/QPSK tuner driver
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/


#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "tda8261.h"

काष्ठा tda8261_state अणु
	काष्ठा dvb_frontend		*fe;
	काष्ठा i2c_adapter		*i2c;
	स्थिर काष्ठा tda8261_config	*config;

	/* state cache */
	u32 frequency;
	u32 bandwidth;
पूर्ण;

अटल पूर्णांक tda8261_पढ़ो(काष्ठा tda8261_state *state, u8 *buf)
अणु
	स्थिर काष्ठा tda8261_config *config = state->config;
	पूर्णांक err = 0;
	काष्ठा i2c_msg msg = अणु .addr	= config->addr, .flags = I2C_M_RD,.buf = buf,  .len = 1 पूर्ण;

	अगर ((err = i2c_transfer(state->i2c, &msg, 1)) != 1)
		pr_err("%s: read error, err=%d\n", __func__, err);

	वापस err;
पूर्ण

अटल पूर्णांक tda8261_ग_लिखो(काष्ठा tda8261_state *state, u8 *buf)
अणु
	स्थिर काष्ठा tda8261_config *config = state->config;
	पूर्णांक err = 0;
	काष्ठा i2c_msg msg = अणु .addr = config->addr, .flags = 0, .buf = buf, .len = 4 पूर्ण;

	अगर ((err = i2c_transfer(state->i2c, &msg, 1)) != 1)
		pr_err("%s: write error, err=%d\n", __func__, err);

	वापस err;
पूर्ण

अटल पूर्णांक tda8261_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा tda8261_state *state = fe->tuner_priv;
	u8 result = 0;
	पूर्णांक err = 0;

	*status = 0;

	अगर ((err = tda8261_पढ़ो(state, &result)) < 0) अणु
		pr_err("%s: I/O Error\n", __func__);
		वापस err;
	पूर्ण
	अगर ((result >> 6) & 0x01) अणु
		pr_debug("%s: Tuner Phase Locked\n", __func__);
		*status = 1;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर u32 भाग_प्रकारab[] = अणु 2000, 1000,  500,  250,  125 पूर्ण; /* kHz */
अटल स्थिर u8  ref_भाग[] = अणु 0x00, 0x01, 0x02, 0x05, 0x07 पूर्ण;

अटल पूर्णांक tda8261_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tda8261_state *state = fe->tuner_priv;

	*frequency = state->frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक tda8261_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा tda8261_state *state = fe->tuner_priv;
	स्थिर काष्ठा tda8261_config *config = state->config;
	u32 frequency, N, status = 0;
	u8 buf[4];
	पूर्णांक err = 0;

	/*
	 * N = Max VCO Frequency / Channel Spacing
	 * Max VCO Frequency = VCO frequency + (channel spacing - 1)
	 * (to account क्रम half channel spacing on either side)
	 */
	frequency = c->frequency;
	अगर ((frequency < 950000) || (frequency > 2150000)) अणु
		pr_warn("%s: Frequency beyond limits, frequency=%d\n",
			__func__, frequency);
		वापस -EINVAL;
	पूर्ण
	N = (frequency + (भाग_प्रकारab[config->step_size] - 1)) / भाग_प्रकारab[config->step_size];
	pr_debug("%s: Step size=%d, Divider=%d, PG=0x%02x (%d)\n",
		__func__, config->step_size, भाग_प्रकारab[config->step_size], N, N);

	buf[0] = (N >> 8) & 0xff;
	buf[1] = N & 0xff;
	buf[2] = (0x01 << 7) | ((ref_भाग[config->step_size] & 0x07) << 1);

	अगर (frequency < 1450000)
		buf[3] = 0x00;
	अन्यथा अगर (frequency < 2000000)
		buf[3] = 0x40;
	अन्यथा अगर (frequency < 2150000)
		buf[3] = 0x80;

	/* Set params */
	err = tda8261_ग_लिखो(state, buf);
	अगर (err < 0) अणु
		pr_err("%s: I/O Error\n", __func__);
		वापस err;
	पूर्ण
	/* sleep क्रम some समय */
	pr_debug("%s: Waiting to Phase LOCK\n", __func__);
	msleep(20);
	/* check status */
	अगर ((err = tda8261_get_status(fe, &status)) < 0) अणु
		pr_err("%s: I/O Error\n", __func__);
		वापस err;
	पूर्ण
	अगर (status == 1) अणु
		pr_debug("%s: Tuner Phase locked: status=%d\n", __func__,
			 status);
		state->frequency = frequency; /* cache successful state */
	पूर्ण अन्यथा अणु
		pr_debug("%s: No Phase lock: status=%d\n", __func__, status);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tda8261_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda8261_state *state = fe->tuner_priv;

	fe->tuner_priv = शून्य;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tda8261_ops = अणु

	.info = अणु
		.name		   = "TDA8261",
		.frequency_min_hz  =  950 * MHz,
		.frequency_max_hz  = 2150 * MHz,
	पूर्ण,

	.set_params	= tda8261_set_params,
	.get_frequency	= tda8261_get_frequency,
	.get_status	= tda8261_get_status,
	.release	= tda8261_release
पूर्ण;

काष्ठा dvb_frontend *tda8261_attach(काष्ठा dvb_frontend *fe,
				    स्थिर काष्ठा tda8261_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा tda8261_state *state = शून्य;

	अगर ((state = kzalloc(माप (काष्ठा tda8261_state), GFP_KERNEL)) == शून्य)
		जाओ निकास;

	state->config		= config;
	state->i2c		= i2c;
	state->fe		= fe;
	fe->tuner_priv		= state;
	fe->ops.tuner_ops	= tda8261_ops;

	fe->ops.tuner_ops.info.frequency_step_hz = भाग_प्रकारab[config->step_size] * kHz;

	pr_info("%s: Attaching TDA8261 8PSK/QPSK tuner\n", __func__);

	वापस fe;

निकास:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

EXPORT_SYMBOL(tda8261_attach);

MODULE_AUTHOR("Manu Abraham");
MODULE_DESCRIPTION("TDA8261 8PSK/QPSK Tuner");
MODULE_LICENSE("GPL");
