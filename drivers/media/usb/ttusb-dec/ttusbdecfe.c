<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TTUSB DEC Frontend Driver
 *
 * Copyright (C) 2003-2004 Alex Woods <linux-dvb@giblets.org>
 */

#समावेश <media/dvb_frontend.h>
#समावेश "ttusbdecfe.h"


#घोषणा LOF_HI			10600000
#घोषणा LOF_LO			9750000

काष्ठा ttusbdecfe_state अणु

	/* configuration settings */
	स्थिर काष्ठा ttusbdecfe_config* config;

	काष्ठा dvb_frontend frontend;

	u8 hi_band;
	u8 voltage;
पूर्ण;


अटल पूर्णांक ttusbdecfe_dvbs_पढ़ो_status(काष्ठा dvb_frontend *fe,
				       क्रमागत fe_status *status)
अणु
	*status = FE_HAS_SIGNAL | FE_HAS_VITERBI |
		FE_HAS_SYNC | FE_HAS_CARRIER | FE_HAS_LOCK;
	वापस 0;
पूर्ण


अटल पूर्णांक ttusbdecfe_dvbt_पढ़ो_status(काष्ठा dvb_frontend *fe,
				       क्रमागत fe_status *status)
अणु
	काष्ठा ttusbdecfe_state* state = fe->demodulator_priv;
	u8 b[] = अणु 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00 पूर्ण;
	u8 result[4];
	पूर्णांक len, ret;

	*status=0;

	ret=state->config->send_command(fe, 0x73, माप(b), b, &len, result);
	अगर(ret)
		वापस ret;

	अगर(len != 4) अणु
		prपूर्णांकk(KERN_ERR "%s: unexpected reply\n", __func__);
		वापस -EIO;
	पूर्ण

	चयन(result[3]) अणु
		हाल 1:  /* not tuned yet */
		हाल 2:  /* no संकेत/no lock*/
			अवरोध;
		हाल 3:	 /* संकेत found and locked*/
			*status = FE_HAS_SIGNAL | FE_HAS_VITERBI |
			FE_HAS_SYNC | FE_HAS_CARRIER | FE_HAS_LOCK;
			अवरोध;
		हाल 4:
			*status = FE_TIMEDOUT;
			अवरोध;
		शेष:
			pr_info("%s: returned unknown value: %d\n",
				__func__, result[3]);
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ttusbdecfe_dvbt_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ttusbdecfe_state* state = (काष्ठा ttusbdecfe_state*) fe->demodulator_priv;
	u8 b[] = अणु 0x00, 0x00, 0x00, 0x03,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x01,
		   0x00, 0x00, 0x00, 0xff,
		   0x00, 0x00, 0x00, 0xff पूर्ण;

	__be32 freq = htonl(p->frequency / 1000);
	स_नकल(&b[4], &freq, माप (u32));
	state->config->send_command(fe, 0x71, माप(b), b, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक ttusbdecfe_dvbt_get_tune_settings(काष्ठा dvb_frontend* fe,
					काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
		fesettings->min_delay_ms = 1500;
		/* Drअगरt compensation makes no sense क्रम DVB-T */
		fesettings->step_size = 0;
		fesettings->max_drअगरt = 0;
		वापस 0;
पूर्ण

अटल पूर्णांक ttusbdecfe_dvbs_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ttusbdecfe_state* state = (काष्ठा ttusbdecfe_state*) fe->demodulator_priv;

	u8 b[] = अणु 0x00, 0x00, 0x00, 0x01,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x01,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00 पूर्ण;
	__be32 freq;
	__be32 sym_rate;
	__be32 band;
	__be32 lnb_voltage;

	freq = htonl(p->frequency +
	       (state->hi_band ? LOF_HI : LOF_LO));
	स_नकल(&b[4], &freq, माप(u32));
	sym_rate = htonl(p->symbol_rate);
	स_नकल(&b[12], &sym_rate, माप(u32));
	band = htonl(state->hi_band ? LOF_HI : LOF_LO);
	स_नकल(&b[24], &band, माप(u32));
	lnb_voltage = htonl(state->voltage);
	स_नकल(&b[28], &lnb_voltage, माप(u32));

	state->config->send_command(fe, 0x71, माप(b), b, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक ttusbdecfe_dvbs_diseqc_send_master_cmd(काष्ठा dvb_frontend* fe, काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा ttusbdecfe_state* state = (काष्ठा ttusbdecfe_state*) fe->demodulator_priv;
	u8 b[] = अणु 0x00, 0xff, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00 पूर्ण;

	अगर (cmd->msg_len > माप(b) - 4)
		वापस -EINVAL;

	स_नकल(&b[4], cmd->msg, cmd->msg_len);

	state->config->send_command(fe, 0x72,
				    माप(b) - (6 - cmd->msg_len), b,
				    शून्य, शून्य);

	वापस 0;
पूर्ण


अटल पूर्णांक ttusbdecfe_dvbs_set_tone(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा ttusbdecfe_state* state = (काष्ठा ttusbdecfe_state*) fe->demodulator_priv;

	state->hi_band = (SEC_TONE_ON == tone);

	वापस 0;
पूर्ण


अटल पूर्णांक ttusbdecfe_dvbs_set_voltage(काष्ठा dvb_frontend *fe,
				       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा ttusbdecfe_state* state = (काष्ठा ttusbdecfe_state*) fe->demodulator_priv;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		state->voltage = 13;
		अवरोध;
	हाल SEC_VOLTAGE_18:
		state->voltage = 18;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ttusbdecfe_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा ttusbdecfe_state* state = (काष्ठा ttusbdecfe_state*) fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ttusbdecfe_dvbt_ops;

काष्ठा dvb_frontend* ttusbdecfe_dvbt_attach(स्थिर काष्ठा ttusbdecfe_config* config)
अणु
	काष्ठा ttusbdecfe_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kदो_स्मृति(माप(काष्ठा ttusbdecfe_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	/* setup the state */
	state->config = config;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &ttusbdecfe_dvbt_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ttusbdecfe_dvbs_ops;

काष्ठा dvb_frontend* ttusbdecfe_dvbs_attach(स्थिर काष्ठा ttusbdecfe_config* config)
अणु
	काष्ठा ttusbdecfe_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kदो_स्मृति(माप(काष्ठा ttusbdecfe_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	/* setup the state */
	state->config = config;
	state->voltage = 0;
	state->hi_band = 0;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &ttusbdecfe_dvbs_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ttusbdecfe_dvbt_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "TechnoTrend/Hauppauge DEC2000-t Frontend",
		.frequency_min_hz	=  51 * MHz,
		.frequency_max_hz	= 858 * MHz,
		.frequency_stepsize_hz	= 62500,
		.caps =	FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.release = ttusbdecfe_release,

	.set_frontend = ttusbdecfe_dvbt_set_frontend,

	.get_tune_settings = ttusbdecfe_dvbt_get_tune_settings,

	.पढ़ो_status = ttusbdecfe_dvbt_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा dvb_frontend_ops ttusbdecfe_dvbs_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name			= "TechnoTrend/Hauppauge DEC3000-s Frontend",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.frequency_stepsize_hz	=  125 * kHz,
		.symbol_rate_min        = 1000000,  /* guessed */
		.symbol_rate_max        = 45000000, /* guessed */
		.caps =	FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK
	पूर्ण,

	.release = ttusbdecfe_release,

	.set_frontend = ttusbdecfe_dvbs_set_frontend,

	.पढ़ो_status = ttusbdecfe_dvbs_पढ़ो_status,

	.diseqc_send_master_cmd = ttusbdecfe_dvbs_diseqc_send_master_cmd,
	.set_voltage = ttusbdecfe_dvbs_set_voltage,
	.set_tone = ttusbdecfe_dvbs_set_tone,
पूर्ण;

MODULE_DESCRIPTION("TTUSB DEC DVB-T/S Demodulator driver");
MODULE_AUTHOR("Alex Woods/Andrew de Quincey");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(ttusbdecfe_dvbt_attach);
EXPORT_SYMBOL(ttusbdecfe_dvbs_attach);
