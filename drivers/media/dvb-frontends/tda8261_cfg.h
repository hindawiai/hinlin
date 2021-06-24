<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	TDA8261 8PSK/QPSK tuner driver
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

अटल पूर्णांक tda8261_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा dvb_frontend_ops	*frontend_ops = &fe->ops;
	काष्ठा dvb_tuner_ops	*tuner_ops = &frontend_ops->tuner_ops;
	पूर्णांक err = 0;

	अगर (tuner_ops->get_frequency) अणु
		err = tuner_ops->get_frequency(fe, frequency);
		अगर (err < 0) अणु
			pr_err("%s: Invalid parameter\n", __func__);
			वापस err;
		पूर्ण
		pr_debug("%s: Frequency=%d\n", __func__, *frequency);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tda8261_set_frequency(काष्ठा dvb_frontend *fe, u32 frequency)
अणु
	काष्ठा dvb_frontend_ops	*frontend_ops = &fe->ops;
	काष्ठा dvb_tuner_ops	*tuner_ops = &frontend_ops->tuner_ops;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक err = 0;

	अगर (tuner_ops->set_params) अणु
		err = tuner_ops->set_params(fe);
		अगर (err < 0) अणु
			pr_err("%s: Invalid parameter\n", __func__);
			वापस err;
		पूर्ण
	पूर्ण
	pr_debug("%s: Frequency=%d\n", __func__, c->frequency);
	वापस 0;
पूर्ण

अटल पूर्णांक tda8261_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	/* FIXME! need to calculate Bandwidth */
	*bandwidth = 40000000;

	वापस 0;
पूर्ण
