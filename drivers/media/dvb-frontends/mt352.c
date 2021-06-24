<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Zarlink DVB-T MT352 demodulator
 *
 *  Written by Holger Waechtler <holger@qanu.de>
 *	 and Daniel Mack <daniel@qanu.de>
 *
 *  AVerMedia AVerTV DVB-T 771 support by
 *       Wolfram Joost <dbox2@frokaschwei.de>
 *
 *  Support क्रम Samsung TDTC9251DH01C(M) tuner
 *  Copyright (C) 2004 Antonio Mancuso <antonio.mancuso@digitaltelevision.it>
 *                     Amauri  Celani  <acelani@essegi.net>
 *
 *  DVICO FusionHDTV DVB-T1 and DVICO FusionHDTV DVB-T Lite support by
 *       Christopher Pascoe <c.pascoe@itee.uq.edu.au>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "mt352_priv.h"
#समावेश "mt352.h"

काष्ठा mt352_state अणु
	काष्ठा i2c_adapter* i2c;
	काष्ठा dvb_frontend frontend;

	/* configuration settings */
	काष्ठा mt352_config config;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "mt352: " args); \
	पूर्ण जबतक (0)

अटल पूर्णांक mt352_single_ग_लिखो(काष्ठा dvb_frontend *fe, u8 reg, u8 val)
अणु
	काष्ठा mt352_state* state = fe->demodulator_priv;
	u8 buf[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config.demod_address, .flags = 0,
			       .buf = buf, .len = 2 पूर्ण;
	पूर्णांक err = i2c_transfer(state->i2c, &msg, 1);
	अगर (err != 1) अणु
		prपूर्णांकk("mt352_write() to reg %x failed (err = %d)!\n", reg, err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _mt352_ग_लिखो(काष्ठा dvb_frontend* fe, स्थिर u8 ibuf[], पूर्णांक ilen)
अणु
	पूर्णांक err,i;
	क्रम (i=0; i < ilen-1; i++)
		अगर ((err = mt352_single_ग_लिखो(fe,ibuf[0]+i,ibuf[i+1])))
			वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक mt352_पढ़ो_रेजिस्टर(काष्ठा mt352_state* state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0 [] = अणु reg पूर्ण;
	u8 b1 [] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config.demod_address,
				    .flags = 0,
				    .buf = b0, .len = 1 पूर्ण,
				  अणु .addr = state->config.demod_address,
				    .flags = I2C_M_RD,
				    .buf = b1, .len = 1 पूर्ण पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) अणु
		prपूर्णांकk("%s: readreg error (reg=%d, ret==%i)\n",
		       __func__, reg, ret);
		वापस ret;
	पूर्ण

	वापस b1[0];
पूर्ण

अटल पूर्णांक mt352_sleep(काष्ठा dvb_frontend* fe)
अणु
	अटल u8 mt352_softकरोwn[] = अणु CLOCK_CTL, 0x20, 0x08 पूर्ण;

	_mt352_ग_लिखो(fe, mt352_softकरोwn, माप(mt352_softकरोwn));
	वापस 0;
पूर्ण

अटल व्योम mt352_calc_nominal_rate(काष्ठा mt352_state* state,
				    u32 bandwidth,
				    अचिन्हित अक्षर *buf)
अणु
	u32 adc_घड़ी = 20480; /* 20.340 MHz */
	u32 bw,value;

	चयन (bandwidth) अणु
	हाल 6000000:
		bw = 6;
		अवरोध;
	हाल 7000000:
		bw = 7;
		अवरोध;
	हाल 8000000:
	शेष:
		bw = 8;
		अवरोध;
	पूर्ण
	अगर (state->config.adc_घड़ी)
		adc_घड़ी = state->config.adc_घड़ी;

	value = 64 * bw * (1<<16) / (7 * 8);
	value = value * 1000 / adc_घड़ी;
	dprपूर्णांकk("%s: bw %d, adc_clock %d => 0x%x\n",
		__func__, bw, adc_घड़ी, value);
	buf[0] = msb(value);
	buf[1] = lsb(value);
पूर्ण

अटल व्योम mt352_calc_input_freq(काष्ठा mt352_state* state,
				  अचिन्हित अक्षर *buf)
अणु
	पूर्णांक adc_घड़ी = 20480; /* 20.480000 MHz */
	पूर्णांक अगर2       = 36167; /* 36.166667 MHz */
	पूर्णांक अगरe,value;

	अगर (state->config.adc_घड़ी)
		adc_घड़ी = state->config.adc_घड़ी;
	अगर (state->config.अगर2)
		अगर2 = state->config.अगर2;

	अगर (adc_घड़ी >= अगर2 * 2)
		अगरe = अगर2;
	अन्यथा अणु
		अगरe = adc_घड़ी - (अगर2 % adc_घड़ी);
		अगर (अगरe > adc_घड़ी / 2)
			अगरe = adc_घड़ी - अगरe;
	पूर्ण
	value = -16374 * अगरe / adc_घड़ी;
	dprपूर्णांकk("%s: if2 %d, ife %d, adc_clock %d => %d / 0x%x\n",
		__func__, अगर2, अगरe, adc_घड़ी, value, value & 0x3fff);
	buf[0] = msb(value);
	buf[1] = lsb(value);
पूर्ण

अटल पूर्णांक mt352_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *op = &fe->dtv_property_cache;
	काष्ठा mt352_state* state = fe->demodulator_priv;
	अचिन्हित अक्षर buf[13];
	अटल अचिन्हित अक्षर tuner_go[] = अणु 0x5d, 0x01 पूर्ण;
	अटल अचिन्हित अक्षर fsm_go[]   = अणु 0x5e, 0x01 पूर्ण;
	अचिन्हित पूर्णांक tps = 0;

	चयन (op->code_rate_HP) अणु
		हाल FEC_2_3:
			tps |= (1 << 7);
			अवरोध;
		हाल FEC_3_4:
			tps |= (2 << 7);
			अवरोध;
		हाल FEC_5_6:
			tps |= (3 << 7);
			अवरोध;
		हाल FEC_7_8:
			tps |= (4 << 7);
			अवरोध;
		हाल FEC_1_2:
		हाल FEC_AUTO:
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	चयन (op->code_rate_LP) अणु
		हाल FEC_2_3:
			tps |= (1 << 4);
			अवरोध;
		हाल FEC_3_4:
			tps |= (2 << 4);
			अवरोध;
		हाल FEC_5_6:
			tps |= (3 << 4);
			अवरोध;
		हाल FEC_7_8:
			tps |= (4 << 4);
			अवरोध;
		हाल FEC_1_2:
		हाल FEC_AUTO:
			अवरोध;
		हाल FEC_NONE:
			अगर (op->hierarchy == HIERARCHY_AUTO ||
			    op->hierarchy == HIERARCHY_NONE)
				अवरोध;
			fallthrough;
		शेष:
			वापस -EINVAL;
	पूर्ण

	चयन (op->modulation) अणु
		हाल QPSK:
			अवरोध;
		हाल QAM_AUTO:
		हाल QAM_16:
			tps |= (1 << 13);
			अवरोध;
		हाल QAM_64:
			tps |= (2 << 13);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	चयन (op->transmission_mode) अणु
		हाल TRANSMISSION_MODE_2K:
		हाल TRANSMISSION_MODE_AUTO:
			अवरोध;
		हाल TRANSMISSION_MODE_8K:
			tps |= (1 << 0);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	चयन (op->guard_पूर्णांकerval) अणु
		हाल GUARD_INTERVAL_1_32:
		हाल GUARD_INTERVAL_AUTO:
			अवरोध;
		हाल GUARD_INTERVAL_1_16:
			tps |= (1 << 2);
			अवरोध;
		हाल GUARD_INTERVAL_1_8:
			tps |= (2 << 2);
			अवरोध;
		हाल GUARD_INTERVAL_1_4:
			tps |= (3 << 2);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	चयन (op->hierarchy) अणु
		हाल HIERARCHY_AUTO:
		हाल HIERARCHY_NONE:
			अवरोध;
		हाल HIERARCHY_1:
			tps |= (1 << 10);
			अवरोध;
		हाल HIERARCHY_2:
			tps |= (2 << 10);
			अवरोध;
		हाल HIERARCHY_4:
			tps |= (3 << 10);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण


	buf[0] = TPS_GIVEN_1; /* TPS_GIVEN_1 and following रेजिस्टरs */

	buf[1] = msb(tps);      /* TPS_GIVEN_(1|0) */
	buf[2] = lsb(tps);

	buf[3] = 0x50;  // old
//	buf[3] = 0xf4;  // pinnacle

	mt352_calc_nominal_rate(state, op->bandwidth_hz, buf+4);
	mt352_calc_input_freq(state, buf+6);

	अगर (state->config.no_tuner) अणु
		अगर (fe->ops.tuner_ops.set_params) अणु
			fe->ops.tuner_ops.set_params(fe);
			अगर (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 0);
		पूर्ण

		_mt352_ग_लिखो(fe, buf, 8);
		_mt352_ग_लिखो(fe, fsm_go, 2);
	पूर्ण अन्यथा अणु
		अगर (fe->ops.tuner_ops.calc_regs) अणु
			fe->ops.tuner_ops.calc_regs(fe, buf+8, 5);
			buf[8] <<= 1;
			_mt352_ग_लिखो(fe, buf, माप(buf));
			_mt352_ग_लिखो(fe, tuner_go, 2);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt352_get_parameters(काष्ठा dvb_frontend* fe,
				काष्ठा dtv_frontend_properties *op)
अणु
	काष्ठा mt352_state* state = fe->demodulator_priv;
	u16 tps;
	u16 भाग;
	u8 trl;
	अटल स्थिर u8 tps_fec_to_api[8] =
	अणु
		FEC_1_2,
		FEC_2_3,
		FEC_3_4,
		FEC_5_6,
		FEC_7_8,
		FEC_AUTO,
		FEC_AUTO,
		FEC_AUTO
	पूर्ण;

	अगर ( (mt352_पढ़ो_रेजिस्टर(state,0x00) & 0xC0) != 0xC0 )
		वापस -EINVAL;

	/* Use TPS_RECEIVED-रेजिस्टरs, not the TPS_CURRENT-रेजिस्टरs because
	 * the mt352 someबार works with the wrong parameters
	 */
	tps = (mt352_पढ़ो_रेजिस्टर(state, TPS_RECEIVED_1) << 8) | mt352_पढ़ो_रेजिस्टर(state, TPS_RECEIVED_0);
	भाग = (mt352_पढ़ो_रेजिस्टर(state, CHAN_START_1) << 8) | mt352_पढ़ो_रेजिस्टर(state, CHAN_START_0);
	trl = mt352_पढ़ो_रेजिस्टर(state, TRL_NOMINAL_RATE_1);

	op->code_rate_HP = tps_fec_to_api[(tps >> 7) & 7];
	op->code_rate_LP = tps_fec_to_api[(tps >> 4) & 7];

	चयन ( (tps >> 13) & 3)
	अणु
		हाल 0:
			op->modulation = QPSK;
			अवरोध;
		हाल 1:
			op->modulation = QAM_16;
			अवरोध;
		हाल 2:
			op->modulation = QAM_64;
			अवरोध;
		शेष:
			op->modulation = QAM_AUTO;
			अवरोध;
	पूर्ण

	op->transmission_mode = (tps & 0x01) ? TRANSMISSION_MODE_8K : TRANSMISSION_MODE_2K;

	चयन ( (tps >> 2) & 3)
	अणु
		हाल 0:
			op->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
			अवरोध;
		हाल 1:
			op->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
			अवरोध;
		हाल 2:
			op->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
			अवरोध;
		हाल 3:
			op->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
			अवरोध;
		शेष:
			op->guard_पूर्णांकerval = GUARD_INTERVAL_AUTO;
			अवरोध;
	पूर्ण

	चयन ( (tps >> 10) & 7)
	अणु
		हाल 0:
			op->hierarchy = HIERARCHY_NONE;
			अवरोध;
		हाल 1:
			op->hierarchy = HIERARCHY_1;
			अवरोध;
		हाल 2:
			op->hierarchy = HIERARCHY_2;
			अवरोध;
		हाल 3:
			op->hierarchy = HIERARCHY_4;
			अवरोध;
		शेष:
			op->hierarchy = HIERARCHY_AUTO;
			अवरोध;
	पूर्ण

	op->frequency = (500 * (भाग - IF_FREQUENCYx6)) / 3 * 1000;

	अगर (trl == 0x72)
		op->bandwidth_hz = 8000000;
	अन्यथा अगर (trl == 0x64)
		op->bandwidth_hz = 7000000;
	अन्यथा
		op->bandwidth_hz = 6000000;


	अगर (mt352_पढ़ो_रेजिस्टर(state, STATUS_2) & 0x02)
		op->inversion = INVERSION_OFF;
	अन्यथा
		op->inversion = INVERSION_ON;

	वापस 0;
पूर्ण

अटल पूर्णांक mt352_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा mt352_state* state = fe->demodulator_priv;
	पूर्णांक s0, s1, s3;

	/* FIXME:
	 *
	 * The MT352 design manual from Zarlink states (page 46-47):
	 *
	 * Notes about the TUNER_GO रेजिस्टर:
	 *
	 * If the Read_Tuner_Byte (bit-1) is activated, then the tuner status
	 * byte is copied from the tuner to the STATUS_3 रेजिस्टर and
	 * completion of the पढ़ो operation is indicated by bit-5 of the
	 * INTERRUPT_3 रेजिस्टर.
	 */

	अगर ((s0 = mt352_पढ़ो_रेजिस्टर(state, STATUS_0)) < 0)
		वापस -EREMOTEIO;
	अगर ((s1 = mt352_पढ़ो_रेजिस्टर(state, STATUS_1)) < 0)
		वापस -EREMOTEIO;
	अगर ((s3 = mt352_पढ़ो_रेजिस्टर(state, STATUS_3)) < 0)
		वापस -EREMOTEIO;

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

अटल पूर्णांक mt352_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा mt352_state* state = fe->demodulator_priv;

	*ber = (mt352_पढ़ो_रेजिस्टर (state, RS_ERR_CNT_2) << 16) |
	       (mt352_पढ़ो_रेजिस्टर (state, RS_ERR_CNT_1) << 8) |
	       (mt352_पढ़ो_रेजिस्टर (state, RS_ERR_CNT_0));

	वापस 0;
पूर्ण

अटल पूर्णांक mt352_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा mt352_state* state = fe->demodulator_priv;

	/* align the 12 bit AGC gain with the most signअगरicant bits */
	u16 संकेत = ((mt352_पढ़ो_रेजिस्टर(state, AGC_GAIN_1) & 0x0f) << 12) |
		(mt352_पढ़ो_रेजिस्टर(state, AGC_GAIN_0) << 4);

	/* inverse of gain is संकेत strength */
	*strength = ~संकेत;
	वापस 0;
पूर्ण

अटल पूर्णांक mt352_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा mt352_state* state = fe->demodulator_priv;

	u8 _snr = mt352_पढ़ो_रेजिस्टर (state, SNR);
	*snr = (_snr << 8) | _snr;

	वापस 0;
पूर्ण

अटल पूर्णांक mt352_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा mt352_state* state = fe->demodulator_priv;

	*ucblocks = (mt352_पढ़ो_रेजिस्टर (state,  RS_UBC_1) << 8) |
		    (mt352_पढ़ो_रेजिस्टर (state,  RS_UBC_0));

	वापस 0;
पूर्ण

अटल पूर्णांक mt352_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* fe_tune_settings)
अणु
	fe_tune_settings->min_delay_ms = 800;
	fe_tune_settings->step_size = 0;
	fe_tune_settings->max_drअगरt = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक mt352_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा mt352_state* state = fe->demodulator_priv;

	अटल u8 mt352_reset_attach [] = अणु RESET, 0xC0 पूर्ण;

	dprपूर्णांकk("%s: hello\n",__func__);

	अगर ((mt352_पढ़ो_रेजिस्टर(state, CLOCK_CTL) & 0x10) == 0 ||
	    (mt352_पढ़ो_रेजिस्टर(state, CONFIG) & 0x20) == 0) अणु

		/* Do a "hard" reset */
		_mt352_ग_लिखो(fe, mt352_reset_attach, माप(mt352_reset_attach));
		वापस state->config.demod_init(fe);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt352_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा mt352_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops mt352_ops;

काष्ठा dvb_frontend* mt352_attach(स्थिर काष्ठा mt352_config* config,
				  काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा mt352_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा mt352_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->i2c = i2c;
	स_नकल(&state->config,config,माप(काष्ठा mt352_config));

	/* check अगर the demod is there */
	अगर (mt352_पढ़ो_रेजिस्टर(state, CHIP_ID) != ID_MT352) जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &mt352_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops mt352_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "Zarlink MT352 DVB-T",
		.frequency_min_hz	= 174 * MHz,
		.frequency_max_hz	= 862 * MHz,
		.frequency_stepsize_hz	= 166667,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO | FE_CAN_RECOVER |
			FE_CAN_MUTE_TS
	पूर्ण,

	.release = mt352_release,

	.init = mt352_init,
	.sleep = mt352_sleep,
	.ग_लिखो = _mt352_ग_लिखो,

	.set_frontend = mt352_set_parameters,
	.get_frontend = mt352_get_parameters,
	.get_tune_settings = mt352_get_tune_settings,

	.पढ़ो_status = mt352_पढ़ो_status,
	.पढ़ो_ber = mt352_पढ़ो_ber,
	.पढ़ो_संकेत_strength = mt352_पढ़ो_संकेत_strength,
	.पढ़ो_snr = mt352_पढ़ो_snr,
	.पढ़ो_ucblocks = mt352_पढ़ो_ucblocks,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Zarlink MT352 DVB-T Demodulator driver");
MODULE_AUTHOR("Holger Waechtler, Daniel Mack, Antonio Mancuso");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(mt352_attach);
