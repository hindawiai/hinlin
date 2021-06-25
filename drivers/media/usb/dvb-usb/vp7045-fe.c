<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB frontend part of the Linux driver क्रम TwinhanDTV Alpha/MagicBoxII USB2.0
 * DVB-T receiver.
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * Thanks to Twinhan who kindly provided hardware and inक्रमmation.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "vp7045.h"

/* It is a Zarlink MT352 within a Samsung Tuner (DNOS404ZH102A) - 040929 - AAT
 *
 * Programming is hidden inside the firmware, so set_frontend is very easy.
 * Even though there is a Firmware command that one can use to access the demod
 * via its रेजिस्टरs. This is used क्रम status inक्रमmation.
 */

काष्ठा vp7045_fe_state अणु
	काष्ठा dvb_frontend fe;
	काष्ठा dvb_usb_device *d;
पूर्ण;

अटल पूर्णांक vp7045_fe_पढ़ो_status(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_status *status)
अणु
	काष्ठा vp7045_fe_state *state = fe->demodulator_priv;
	u8 s0 = vp7045_पढ़ो_reg(state->d,0x00),
	   s1 = vp7045_पढ़ो_reg(state->d,0x01),
	   s3 = vp7045_पढ़ो_reg(state->d,0x03);

	*status = 0;
	अगर (s0 & (1 << 4))
		*status |= FE_HAS_CARRIER;
	अगर (s0 & (1 << 1))
		*status |= FE_HAS_VITERBI;
	अगर (s0 & (1 << 5))
		*status |= FE_HAS_LOCK;
	अगर (s1 & (1 << 1))
		*status |= FE_HAS_SYNC;
	अगर (s3 & (1 << 6))
		*status |= FE_HAS_SIGNAL;

	अगर ((*status & (FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC)) !=
			(FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC))
		*status &= ~FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक vp7045_fe_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32 *ber)
अणु
	काष्ठा vp7045_fe_state *state = fe->demodulator_priv;
	*ber = (vp7045_पढ़ो_reg(state->d, 0x0D) << 16) |
	       (vp7045_पढ़ो_reg(state->d, 0x0E) << 8) |
		vp7045_पढ़ो_reg(state->d, 0x0F);
	वापस 0;
पूर्ण

अटल पूर्णांक vp7045_fe_पढ़ो_unc_blocks(काष्ठा dvb_frontend* fe, u32 *unc)
अणु
	काष्ठा vp7045_fe_state *state = fe->demodulator_priv;
	*unc = (vp7045_पढ़ो_reg(state->d, 0x10) << 8) |
		    vp7045_पढ़ो_reg(state->d, 0x11);
	वापस 0;
पूर्ण

अटल पूर्णांक vp7045_fe_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16 *strength)
अणु
	काष्ठा vp7045_fe_state *state = fe->demodulator_priv;
	u16 संकेत = (vp7045_पढ़ो_reg(state->d, 0x14) << 8) |
		vp7045_पढ़ो_reg(state->d, 0x15);

	*strength = ~संकेत;
	वापस 0;
पूर्ण

अटल पूर्णांक vp7045_fe_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16 *snr)
अणु
	काष्ठा vp7045_fe_state *state = fe->demodulator_priv;
	u8 _snr = vp7045_पढ़ो_reg(state->d, 0x09);
	*snr = (_snr << 8) | _snr;
	वापस 0;
पूर्ण

अटल पूर्णांक vp7045_fe_init(काष्ठा dvb_frontend* fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vp7045_fe_sleep(काष्ठा dvb_frontend* fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vp7045_fe_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 800;
	वापस 0;
पूर्ण

अटल पूर्णांक vp7045_fe_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fep = &fe->dtv_property_cache;
	काष्ठा vp7045_fe_state *state = fe->demodulator_priv;
	u8 buf[5];
	u32 freq = fep->frequency / 1000;

	buf[0] = (freq >> 16) & 0xff;
	buf[1] = (freq >>  8) & 0xff;
	buf[2] =  freq        & 0xff;
	buf[3] = 0;

	चयन (fep->bandwidth_hz) अणु
	हाल 8000000:
		buf[4] = 8;
		अवरोध;
	हाल 7000000:
		buf[4] = 7;
		अवरोध;
	हाल 6000000:
		buf[4] = 6;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	vp7045_usb_op(state->d,LOCK_TUNER_COMMAND,buf,5,शून्य,0,200);
	वापस 0;
पूर्ण

अटल व्योम vp7045_fe_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा vp7045_fe_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops vp7045_fe_ops;

काष्ठा dvb_frontend * vp7045_fe_attach(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा vp7045_fe_state *s = kzalloc(माप(काष्ठा vp7045_fe_state), GFP_KERNEL);
	अगर (s == शून्य)
		जाओ error;

	s->d = d;
	स_नकल(&s->fe.ops, &vp7045_fe_ops, माप(काष्ठा dvb_frontend_ops));
	s->fe.demodulator_priv = s;

	वापस &s->fe;
error:
	वापस शून्य;
पूर्ण


अटल स्थिर काष्ठा dvb_frontend_ops vp7045_fe_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "Twinhan VP7045/46 USB DVB-T",
		.frequency_min_hz	=  44250 * kHz,
		.frequency_max_hz	= 867250 * kHz,
		.frequency_stepsize_hz	=      1 * kHz,
		.caps = FE_CAN_INVERSION_AUTO |
				FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
				FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
				FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
				FE_CAN_TRANSMISSION_MODE_AUTO |
				FE_CAN_GUARD_INTERVAL_AUTO |
				FE_CAN_RECOVER |
				FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.release = vp7045_fe_release,

	.init = vp7045_fe_init,
	.sleep = vp7045_fe_sleep,

	.set_frontend = vp7045_fe_set_frontend,
	.get_tune_settings = vp7045_fe_get_tune_settings,

	.पढ़ो_status = vp7045_fe_पढ़ो_status,
	.पढ़ो_ber = vp7045_fe_पढ़ो_ber,
	.पढ़ो_संकेत_strength = vp7045_fe_पढ़ो_संकेत_strength,
	.पढ़ो_snr = vp7045_fe_पढ़ो_snr,
	.पढ़ो_ucblocks = vp7045_fe_पढ़ो_unc_blocks,
पूर्ण;
