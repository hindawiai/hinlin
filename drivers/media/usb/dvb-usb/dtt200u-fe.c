<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Frontend part of the Linux driver क्रम the WideView/ Yakumo/ Hama/
 * Typhoon/ Yuan DVB-T USB2.0 receiver.
 *
 * Copyright (C) 2005 Patrick Boettcher <patrick.boettcher@posteo.de>
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "dtt200u.h"

काष्ठा dtt200u_fe_state अणु
	काष्ठा dvb_usb_device *d;

	क्रमागत fe_status stat;

	काष्ठा dtv_frontend_properties fep;
	काष्ठा dvb_frontend frontend;

	अचिन्हित अक्षर data[80];
	काष्ठा mutex data_mutex;
पूर्ण;

अटल पूर्णांक dtt200u_fe_पढ़ो_status(काष्ठा dvb_frontend *fe,
				  क्रमागत fe_status *stat)
अणु
	काष्ठा dtt200u_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = GET_TUNE_STATUS;

	ret = dvb_usb_generic_rw(state->d, state->data, 1, state->data, 3, 0);
	अगर (ret < 0) अणु
		*stat = 0;
		mutex_unlock(&state->data_mutex);
		वापस ret;
	पूर्ण

	चयन (state->data[0]) अणु
		हाल 0x01:
			*stat = FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
			अवरोध;
		हाल 0x00: /* pending */
			*stat = FE_TIMEDOUT; /* during set_frontend */
			अवरोध;
		शेष:
		हाल 0x02: /* failed */
			*stat = 0;
			अवरोध;
	पूर्ण
	mutex_unlock(&state->data_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dtt200u_fe_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32 *ber)
अणु
	काष्ठा dtt200u_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = GET_VIT_ERR_CNT;

	ret = dvb_usb_generic_rw(state->d, state->data, 1, state->data, 3, 0);
	अगर (ret >= 0)
		*ber = (state->data[0] << 16) | (state->data[1] << 8) | state->data[2];

	mutex_unlock(&state->data_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dtt200u_fe_पढ़ो_unc_blocks(काष्ठा dvb_frontend* fe, u32 *unc)
अणु
	काष्ठा dtt200u_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = GET_RS_UNCOR_BLK_CNT;

	ret = dvb_usb_generic_rw(state->d, state->data, 1, state->data, 2, 0);
	अगर (ret >= 0)
		*unc = (state->data[0] << 8) | state->data[1];

	mutex_unlock(&state->data_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dtt200u_fe_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16 *strength)
अणु
	काष्ठा dtt200u_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = GET_AGC;

	ret = dvb_usb_generic_rw(state->d, state->data, 1, state->data, 1, 0);
	अगर (ret >= 0)
		*strength = (state->data[0] << 8) | state->data[0];

	mutex_unlock(&state->data_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dtt200u_fe_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16 *snr)
अणु
	काष्ठा dtt200u_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = GET_SNR;

	ret = dvb_usb_generic_rw(state->d, state->data, 1, state->data, 1, 0);
	अगर (ret >= 0)
		*snr = ~((state->data[0] << 8) | state->data[0]);

	mutex_unlock(&state->data_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dtt200u_fe_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा dtt200u_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = SET_INIT;

	ret = dvb_usb_generic_ग_लिखो(state->d, state->data, 1);
	mutex_unlock(&state->data_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक dtt200u_fe_sleep(काष्ठा dvb_frontend* fe)
अणु
	वापस dtt200u_fe_init(fe);
पूर्ण

अटल पूर्णांक dtt200u_fe_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1500;
	tune->step_size = 0;
	tune->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक dtt200u_fe_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fep = &fe->dtv_property_cache;
	काष्ठा dtt200u_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u16 freq = fep->frequency / 250000;

	mutex_lock(&state->data_mutex);
	state->data[0] = SET_BANDWIDTH;
	चयन (fep->bandwidth_hz) अणु
	हाल 8000000:
		state->data[1] = 8;
		अवरोध;
	हाल 7000000:
		state->data[1] = 7;
		अवरोध;
	हाल 6000000:
		state->data[1] = 6;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ ret;
	पूर्ण

	ret = dvb_usb_generic_ग_लिखो(state->d, state->data, 2);
	अगर (ret < 0)
		जाओ ret;

	state->data[0] = SET_RF_FREQ;
	state->data[1] = freq & 0xff;
	state->data[2] = (freq >> 8) & 0xff;
	ret = dvb_usb_generic_ग_लिखो(state->d, state->data, 3);
	अगर (ret < 0)
		जाओ ret;

ret:
	mutex_unlock(&state->data_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dtt200u_fe_get_frontend(काष्ठा dvb_frontend* fe,
				   काष्ठा dtv_frontend_properties *fep)
अणु
	काष्ठा dtt200u_fe_state *state = fe->demodulator_priv;

	स_नकल(fep, &state->fep, माप(काष्ठा dtv_frontend_properties));
	वापस 0;
पूर्ण

अटल व्योम dtt200u_fe_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा dtt200u_fe_state *state = (काष्ठा dtt200u_fe_state*) fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops dtt200u_fe_ops;

काष्ठा dvb_frontend* dtt200u_fe_attach(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा dtt200u_fe_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा dtt200u_fe_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	deb_info("attaching frontend dtt200u\n");

	state->d = d;
	mutex_init(&state->data_mutex);

	स_नकल(&state->frontend.ops,&dtt200u_fe_ops,माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	वापस &state->frontend;
error:
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops dtt200u_fe_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "WideView USB DVB-T",
		.frequency_min_hz	=  44250 * kHz,
		.frequency_max_hz	= 867250 * kHz,
		.frequency_stepsize_hz	=    250 * kHz,
		.caps = FE_CAN_INVERSION_AUTO |
				FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
				FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
				FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
				FE_CAN_TRANSMISSION_MODE_AUTO |
				FE_CAN_GUARD_INTERVAL_AUTO |
				FE_CAN_RECOVER |
				FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.release = dtt200u_fe_release,

	.init = dtt200u_fe_init,
	.sleep = dtt200u_fe_sleep,

	.set_frontend = dtt200u_fe_set_frontend,
	.get_frontend = dtt200u_fe_get_frontend,
	.get_tune_settings = dtt200u_fe_get_tune_settings,

	.पढ़ो_status = dtt200u_fe_पढ़ो_status,
	.पढ़ो_ber = dtt200u_fe_पढ़ो_ber,
	.पढ़ो_संकेत_strength = dtt200u_fe_पढ़ो_संकेत_strength,
	.पढ़ो_snr = dtt200u_fe_पढ़ो_snr,
	.पढ़ो_ucblocks = dtt200u_fe_पढ़ो_unc_blocks,
पूर्ण;
