<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  c8sectpfe-dvb.c - C8SECTPFE STi DVB driver
 *
 * Copyright (c) STMicroelectronics 2015
 *
 *  Author Peter Grअगरfin <peter.grअगरfin@linaro.org>
 *
 */
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/version.h>

#समावेश <dt-bindings/media/c8sectpfe.h>

#समावेश "c8sectpfe-common.h"
#समावेश "c8sectpfe-core.h"
#समावेश "c8sectpfe-dvb.h"

#समावेश "dvb-pll.h"
#समावेश "lnbh24.h"
#समावेश "stv0367.h"
#समावेश "stv0367_priv.h"
#समावेश "stv6110x.h"
#समावेश "stv090x.h"
#समावेश "tda18212.h"

अटल अंतरभूत स्थिर अक्षर *dvb_card_str(अचिन्हित पूर्णांक c)
अणु
	चयन (c) अणु
	हाल STV0367_TDA18212_NIMA_1:	वापस "STV0367_TDA18212_NIMA_1";
	हाल STV0367_TDA18212_NIMA_2:	वापस "STV0367_TDA18212_NIMA_2";
	हाल STV0367_TDA18212_NIMB_1:	वापस "STV0367_TDA18212_NIMB_1";
	हाल STV0367_TDA18212_NIMB_2:	वापस "STV0367_TDA18212_NIMB_2";
	हाल STV0903_6110_LNB24_NIMA:	वापस "STV0903_6110_LNB24_NIMA";
	हाल STV0903_6110_LNB24_NIMB:	वापस "STV0903_6110_LNB24_NIMB";
	शेष:			वापस "unknown dvb frontend card";
	पूर्ण
पूर्ण

अटल काष्ठा stv090x_config stv090x_config = अणु
	.device                 = STV0903,
	.demod_mode             = STV090x_SINGLE,
	.clk_mode               = STV090x_CLK_EXT,
	.xtal                   = 16000000,
	.address                = 0x69,

	.ts1_mode               = STV090x_TSMODE_SERIAL_CONTINUOUS,
	.ts2_mode               = STV090x_TSMODE_SERIAL_CONTINUOUS,

	.repeater_level         = STV090x_RPTLEVEL_64,

	.tuner_init             = शून्य,
	.tuner_set_mode         = शून्य,
	.tuner_set_frequency    = शून्य,
	.tuner_get_frequency    = शून्य,
	.tuner_set_bandwidth    = शून्य,
	.tuner_get_bandwidth    = शून्य,
	.tuner_set_bbgain       = शून्य,
	.tuner_get_bbgain       = शून्य,
	.tuner_set_refclk       = शून्य,
	.tuner_get_status       = शून्य,
पूर्ण;

अटल काष्ठा stv6110x_config stv6110x_config = अणु
	.addr                   = 0x60,
	.refclk                 = 16000000,
पूर्ण;

#घोषणा NIMA 0
#घोषणा NIMB 1

अटल काष्ठा stv0367_config stv0367_tda18212_config[] = अणु
	अणु
		.demod_address = 0x1c,
		.xtal = 16000000,
		.अगर_khz = 4500,
		.अगर_iq_mode = FE_TER_NORMAL_IF_TUNER,
		.ts_mode = STV0367_SERIAL_PUNCT_CLOCK,
		.clk_pol = STV0367_CLOCKPOLARITY_DEFAULT,
	पूर्ण, अणु
		.demod_address = 0x1d,
		.xtal = 16000000,
		.अगर_khz = 4500,
		.अगर_iq_mode = FE_TER_NORMAL_IF_TUNER,
		.ts_mode = STV0367_SERIAL_PUNCT_CLOCK,
		.clk_pol = STV0367_CLOCKPOLARITY_DEFAULT,
	पूर्ण, अणु
		.demod_address = 0x1e,
		.xtal = 16000000,
		.अगर_khz = 4500,
		.अगर_iq_mode = FE_TER_NORMAL_IF_TUNER,
		.ts_mode = STV0367_SERIAL_PUNCT_CLOCK,
		.clk_pol = STV0367_CLOCKPOLARITY_DEFAULT,
	पूर्ण,
पूर्ण;

अटल काष्ठा tda18212_config tda18212_conf = अणु
	.अगर_dvbt_6 = 4150,
	.अगर_dvbt_7 = 4150,
	.अगर_dvbt_8 = 4500,
	.अगर_dvbc = 5000,
पूर्ण;

पूर्णांक c8sectpfe_frontend_attach(काष्ठा dvb_frontend **fe,
		काष्ठा c8sectpfe *c8sectpfe,
		काष्ठा channel_info *tsin, पूर्णांक chan_num)
अणु
	काष्ठा tda18212_config *tda18212;
	स्थिर काष्ठा stv6110x_devctl *fe2;
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info tda18212_info = अणु
		.type = "tda18212",
		.addr = 0x60,
	पूर्ण;

	अगर (!tsin)
		वापस -EINVAL;

	चयन (tsin->dvb_card) अणु

	हाल STV0367_TDA18212_NIMA_1:
	हाल STV0367_TDA18212_NIMA_2:
	हाल STV0367_TDA18212_NIMB_1:
	हाल STV0367_TDA18212_NIMB_2:
		अगर (tsin->dvb_card == STV0367_TDA18212_NIMA_1)
			*fe = dvb_attach(stv0367ter_attach,
				 &stv0367_tda18212_config[0],
					tsin->i2c_adapter);
		अन्यथा अगर (tsin->dvb_card == STV0367_TDA18212_NIMB_1)
			*fe = dvb_attach(stv0367ter_attach,
				 &stv0367_tda18212_config[1],
					tsin->i2c_adapter);
		अन्यथा
			*fe = dvb_attach(stv0367ter_attach,
				 &stv0367_tda18212_config[2],
					tsin->i2c_adapter);

		अगर (!*fe) अणु
			dev_err(c8sectpfe->device,
				"%s: stv0367ter_attach failed for NIM card %s\n"
				, __func__, dvb_card_str(tsin->dvb_card));
			वापस -ENODEV;
		पूर्ण

		/*
		 * init the demod so that i2c gate_ctrl
		 * to the tuner works correctly
		 */
		(*fe)->ops.init(*fe);

		/* Allocate the tda18212 काष्ठाure */
		tda18212 = devm_kzalloc(c8sectpfe->device,
					माप(काष्ठा tda18212_config),
					GFP_KERNEL);
		अगर (!tda18212) अणु
			dev_err(c8sectpfe->device,
				"%s: devm_kzalloc failed\n", __func__);
			वापस -ENOMEM;
		पूर्ण

		स_नकल(tda18212, &tda18212_conf,
			माप(काष्ठा tda18212_config));

		tda18212->fe = (*fe);

		tda18212_info.platक्रमm_data = tda18212;

		/* attach tuner */
		request_module("tda18212");
		client = i2c_new_client_device(tsin->i2c_adapter,
					       &tda18212_info);
		अगर (!i2c_client_has_driver(client)) अणु
			dvb_frontend_detach(*fe);
			वापस -ENODEV;
		पूर्ण

		अगर (!try_module_get(client->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client);
			dvb_frontend_detach(*fe);
			वापस -ENODEV;
		पूर्ण

		tsin->i2c_client = client;

		अवरोध;

	हाल STV0903_6110_LNB24_NIMA:
		*fe = dvb_attach(stv090x_attach,	&stv090x_config,
				tsin->i2c_adapter, STV090x_DEMODULATOR_0);
		अगर (!*fe) अणु
			dev_err(c8sectpfe->device, "%s: stv090x_attach failed\n"
				"\tfor NIM card %s\n",
				__func__, dvb_card_str(tsin->dvb_card));
			वापस -ENODEV;
		पूर्ण

		fe2 = dvb_attach(stv6110x_attach, *fe,
					&stv6110x_config, tsin->i2c_adapter);
		अगर (!fe2) अणु
			dev_err(c8sectpfe->device,
				"%s: stv6110x_attach failed for NIM card %s\n"
				, __func__, dvb_card_str(tsin->dvb_card));
			वापस -ENODEV;
		पूर्ण

		stv090x_config.tuner_init = fe2->tuner_init;
		stv090x_config.tuner_set_mode = fe2->tuner_set_mode;
		stv090x_config.tuner_set_frequency = fe2->tuner_set_frequency;
		stv090x_config.tuner_get_frequency = fe2->tuner_get_frequency;
		stv090x_config.tuner_set_bandwidth = fe2->tuner_set_bandwidth;
		stv090x_config.tuner_get_bandwidth = fe2->tuner_get_bandwidth;
		stv090x_config.tuner_set_bbgain = fe2->tuner_set_bbgain;
		stv090x_config.tuner_get_bbgain = fe2->tuner_get_bbgain;
		stv090x_config.tuner_set_refclk = fe2->tuner_set_refclk;
		stv090x_config.tuner_get_status = fe2->tuner_get_status;

		dvb_attach(lnbh24_attach, *fe, tsin->i2c_adapter, 0, 0, 0x9);
		अवरोध;

	शेष:
		dev_err(c8sectpfe->device,
			"%s: DVB frontend card %s not yet supported\n",
			__func__, dvb_card_str(tsin->dvb_card));
		वापस -ENODEV;
	पूर्ण

	(*fe)->id = chan_num;

	dev_info(c8sectpfe->device,
			"DVB frontend card %s successfully attached",
			dvb_card_str(tsin->dvb_card));
	वापस 0;
पूर्ण
