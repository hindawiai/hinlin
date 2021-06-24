<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	STB6100 Silicon Tuner
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

	Copyright (C) ST Microelectronics

*/

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

अटल पूर्णांक stb6100_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा dvb_frontend_ops	*frontend_ops = &fe->ops;
	काष्ठा dvb_tuner_ops	*tuner_ops = &frontend_ops->tuner_ops;
	पूर्णांक err = 0;

	अगर (tuner_ops->get_frequency) अणु
		err = tuner_ops->get_frequency(fe, frequency);
		अगर (err < 0) अणु
			prपूर्णांकk("%s: Invalid parameter\n", __func__);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stb6100_set_frequency(काष्ठा dvb_frontend *fe, u32 frequency)
अणु
	काष्ठा dvb_frontend_ops	*frontend_ops = &fe->ops;
	काष्ठा dvb_tuner_ops	*tuner_ops = &frontend_ops->tuner_ops;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 bw = c->bandwidth_hz;
	पूर्णांक err = 0;

	c->frequency = frequency;
	c->bandwidth_hz = 0;		/* Don't adjust the bandwidth */

	अगर (tuner_ops->set_params) अणु
		err = tuner_ops->set_params(fe);
		c->bandwidth_hz = bw;
		अगर (err < 0) अणु
			prपूर्णांकk("%s: Invalid parameter\n", __func__);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stb6100_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा dvb_frontend_ops	*frontend_ops = &fe->ops;
	काष्ठा dvb_tuner_ops	*tuner_ops = &frontend_ops->tuner_ops;
	पूर्णांक err = 0;

	अगर (tuner_ops->get_bandwidth) अणु
		err = tuner_ops->get_bandwidth(fe, bandwidth);
		अगर (err < 0) अणु
			prपूर्णांकk("%s: Invalid parameter\n", __func__);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stb6100_set_bandwidth(काष्ठा dvb_frontend *fe, u32 bandwidth)
अणु
	काष्ठा dvb_frontend_ops	*frontend_ops = &fe->ops;
	काष्ठा dvb_tuner_ops	*tuner_ops = &frontend_ops->tuner_ops;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 freq = c->frequency;
	पूर्णांक err = 0;

	c->bandwidth_hz = bandwidth;
	c->frequency = 0;		/* Don't adjust the frequency */

	अगर (tuner_ops->set_params) अणु
		err = tuner_ops->set_params(fe);
		c->frequency = freq;
		अगर (err < 0) अणु
			prपूर्णांकk("%s: Invalid parameter\n", __func__);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
