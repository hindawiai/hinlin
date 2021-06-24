<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	TDA665x tuner driver
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "tda665x.h"

काष्ठा tda665x_state अणु
	काष्ठा dvb_frontend		*fe;
	काष्ठा i2c_adapter		*i2c;
	स्थिर काष्ठा tda665x_config	*config;

	u32 frequency;
	u32 bandwidth;
पूर्ण;

अटल पूर्णांक tda665x_पढ़ो(काष्ठा tda665x_state *state, u8 *buf)
अणु
	स्थिर काष्ठा tda665x_config *config = state->config;
	पूर्णांक err = 0;
	काष्ठा i2c_msg msg = अणु .addr = config->addr, .flags = I2C_M_RD, .buf = buf, .len = 2 पूर्ण;

	err = i2c_transfer(state->i2c, &msg, 1);
	अगर (err != 1)
		जाओ निकास;

	वापस err;
निकास:
	prपूर्णांकk(KERN_ERR "%s: I/O Error err=<%d>\n", __func__, err);
	वापस err;
पूर्ण

अटल पूर्णांक tda665x_ग_लिखो(काष्ठा tda665x_state *state, u8 *buf, u8 length)
अणु
	स्थिर काष्ठा tda665x_config *config = state->config;
	पूर्णांक err = 0;
	काष्ठा i2c_msg msg = अणु .addr = config->addr, .flags = 0, .buf = buf, .len = length पूर्ण;

	err = i2c_transfer(state->i2c, &msg, 1);
	अगर (err != 1)
		जाओ निकास;

	वापस err;
निकास:
	prपूर्णांकk(KERN_ERR "%s: I/O Error err=<%d>\n", __func__, err);
	वापस err;
पूर्ण

अटल पूर्णांक tda665x_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tda665x_state *state = fe->tuner_priv;

	*frequency = state->frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक tda665x_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा tda665x_state *state = fe->tuner_priv;
	u8 result = 0;
	पूर्णांक err = 0;

	*status = 0;

	err = tda665x_पढ़ो(state, &result);
	अगर (err < 0)
		जाओ निकास;

	अगर ((result >> 6) & 0x01) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Tuner Phase Locked\n", __func__);
		*status = 1;
	पूर्ण

	वापस err;
निकास:
	prपूर्णांकk(KERN_ERR "%s: I/O Error\n", __func__);
	वापस err;
पूर्ण

अटल पूर्णांक tda665x_set_frequency(काष्ठा dvb_frontend *fe,
				 u32 new_frequency)
अणु
	काष्ठा tda665x_state *state = fe->tuner_priv;
	स्थिर काष्ठा tda665x_config *config = state->config;
	u32 frequency, status = 0;
	u8 buf[4];
	पूर्णांक err = 0;

	अगर ((new_frequency < config->frequency_max)
	    || (new_frequency > config->frequency_min)) अणु
		prपूर्णांकk(KERN_ERR "%s: Frequency beyond limits, frequency=%d\n",
		       __func__, new_frequency);
		वापस -EINVAL;
	पूर्ण

	frequency = new_frequency;

	frequency += config->frequency_offst;
	frequency *= config->ref_multiplier;
	frequency += config->ref_भागider >> 1;
	frequency /= config->ref_भागider;

	buf[0] = (u8) ((frequency & 0x7f00) >> 8);
	buf[1] = (u8) (frequency & 0x00ff) >> 0;
	buf[2] = 0x80 | 0x40 | 0x02;
	buf[3] = 0x00;

	/* restore frequency */
	frequency = new_frequency;

	अगर (frequency < 153000000) अणु
		/* VHF-L */
		buf[3] |= 0x01; /* fc, Low Band, 47 - 153 MHz */
		अगर (frequency < 68000000)
			buf[3] |= 0x40; /* 83uA */
		अगर (frequency < 1040000000)
			buf[3] |= 0x60; /* 122uA */
		अगर (frequency < 1250000000)
			buf[3] |= 0x80; /* 163uA */
		अन्यथा
			buf[3] |= 0xa0; /* 254uA */
	पूर्ण अन्यथा अगर (frequency < 438000000) अणु
		/* VHF-H */
		buf[3] |= 0x02; /* fc, Mid Band, 153 - 438 MHz */
		अगर (frequency < 230000000)
			buf[3] |= 0x40;
		अगर (frequency < 300000000)
			buf[3] |= 0x60;
		अन्यथा
			buf[3] |= 0x80;
	पूर्ण अन्यथा अणु
		/* UHF */
		buf[3] |= 0x04; /* fc, High Band, 438 - 862 MHz */
		अगर (frequency < 470000000)
			buf[3] |= 0x60;
		अगर (frequency < 526000000)
			buf[3] |= 0x80;
		अन्यथा
			buf[3] |= 0xa0;
	पूर्ण

	/* Set params */
	err = tda665x_ग_लिखो(state, buf, 5);
	अगर (err < 0)
		जाओ निकास;

	/* sleep क्रम some समय */
	prपूर्णांकk(KERN_DEBUG "%s: Waiting to Phase LOCK\n", __func__);
	msleep(20);
	/* check status */
	err = tda665x_get_status(fe, &status);
	अगर (err < 0)
		जाओ निकास;

	अगर (status == 1) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Tuner Phase locked: status=%d\n",
		       __func__, status);
		state->frequency = frequency; /* cache successful state */
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "%s: No Phase lock: status=%d\n",
		       __func__, status);
	पूर्ण

	वापस 0;
निकास:
	prपूर्णांकk(KERN_ERR "%s: I/O Error\n", __func__);
	वापस err;
पूर्ण

अटल पूर्णांक tda665x_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	tda665x_set_frequency(fe, c->frequency);

	वापस 0;
पूर्ण

अटल व्योम tda665x_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda665x_state *state = fe->tuner_priv;

	fe->tuner_priv = शून्य;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tda665x_ops = अणु
	.get_status	= tda665x_get_status,
	.set_params	= tda665x_set_params,
	.get_frequency	= tda665x_get_frequency,
	.release	= tda665x_release
पूर्ण;

काष्ठा dvb_frontend *tda665x_attach(काष्ठा dvb_frontend *fe,
				    स्थिर काष्ठा tda665x_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा tda665x_state *state = शून्य;
	काष्ठा dvb_tuner_info *info;

	state = kzalloc(माप(काष्ठा tda665x_state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	state->config		= config;
	state->i2c		= i2c;
	state->fe		= fe;
	fe->tuner_priv		= state;
	fe->ops.tuner_ops	= tda665x_ops;
	info			 = &fe->ops.tuner_ops.info;

	स_नकल(info->name, config->name, माप(config->name));
	info->frequency_min_hz	= config->frequency_min;
	info->frequency_max_hz	= config->frequency_max;
	info->frequency_step_hz	= config->frequency_offst;

	prपूर्णांकk(KERN_DEBUG "%s: Attaching TDA665x (%s) tuner\n", __func__, info->name);

	वापस fe;
पूर्ण
EXPORT_SYMBOL(tda665x_attach);

MODULE_DESCRIPTION("TDA665x driver");
MODULE_AUTHOR("Manu Abraham");
MODULE_LICENSE("GPL");
