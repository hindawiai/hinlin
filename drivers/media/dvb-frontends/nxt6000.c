<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	NxtWave Communications - NXT6000 demodulator driver

    Copyright (C) 2002-2003 Florian Schirmer <jolt@tuxbox.org>
    Copyright (C) 2003 Paul Andreassen <paul@andreassen.com.au>

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "nxt6000_priv.h"
#समावेश "nxt6000.h"



काष्ठा nxt6000_state अणु
	काष्ठा i2c_adapter* i2c;
	/* configuration settings */
	स्थिर काष्ठा nxt6000_config* config;
	काष्ठा dvb_frontend frontend;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

अटल पूर्णांक nxt6000_ग_लिखोreg(काष्ठा nxt6000_state* state, u8 reg, u8 data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु.addr = state->config->demod_address,.flags = 0,.buf = buf,.len = 2 पूर्ण;
	पूर्णांक ret;

	अगर ((ret = i2c_transfer(state->i2c, &msg, 1)) != 1)
		dprपूर्णांकk("nxt6000: nxt6000_write error (reg: 0x%02X, data: 0x%02X, ret: %d)\n", reg, data, ret);

	वापस (ret != 1) ? -EIO : 0;
पूर्ण

अटल u8 nxt6000_पढ़ोreg(काष्ठा nxt6000_state* state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msgs[] = अणु
		अणु.addr = state->config->demod_address,.flags = 0,.buf = b0,.len = 1पूर्ण,
		अणु.addr = state->config->demod_address,.flags = I2C_M_RD,.buf = b1,.len = 1पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msgs, 2);

	अगर (ret != 2)
		dprपूर्णांकk("nxt6000: nxt6000_read error (reg: 0x%02X, ret: %d)\n", reg, ret);

	वापस b1[0];
पूर्ण

अटल व्योम nxt6000_reset(काष्ठा nxt6000_state* state)
अणु
	u8 val;

	val = nxt6000_पढ़ोreg(state, OFDM_COR_CTL);

	nxt6000_ग_लिखोreg(state, OFDM_COR_CTL, val & ~COREACT);
	nxt6000_ग_लिखोreg(state, OFDM_COR_CTL, val | COREACT);
पूर्ण

अटल पूर्णांक nxt6000_set_bandwidth(काष्ठा nxt6000_state *state, u32 bandwidth)
अणु
	u16 nominal_rate;
	पूर्णांक result;

	चयन (bandwidth) अणु
	हाल 6000000:
		nominal_rate = 0x55B7;
		अवरोध;

	हाल 7000000:
		nominal_rate = 0x6400;
		अवरोध;

	हाल 8000000:
		nominal_rate = 0x7249;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((result = nxt6000_ग_लिखोreg(state, OFDM_TRL_NOMINALRATE_1, nominal_rate & 0xFF)) < 0)
		वापस result;

	वापस nxt6000_ग_लिखोreg(state, OFDM_TRL_NOMINALRATE_2, (nominal_rate >> 8) & 0xFF);
पूर्ण

अटल पूर्णांक nxt6000_set_guard_पूर्णांकerval(काष्ठा nxt6000_state *state,
				      क्रमागत fe_guard_पूर्णांकerval guard_पूर्णांकerval)
अणु
	चयन (guard_पूर्णांकerval) अणु

	हाल GUARD_INTERVAL_1_32:
		वापस nxt6000_ग_लिखोreg(state, OFDM_COR_MODEGUARD, 0x00 | (nxt6000_पढ़ोreg(state, OFDM_COR_MODEGUARD) & ~0x03));

	हाल GUARD_INTERVAL_1_16:
		वापस nxt6000_ग_लिखोreg(state, OFDM_COR_MODEGUARD, 0x01 | (nxt6000_पढ़ोreg(state, OFDM_COR_MODEGUARD) & ~0x03));

	हाल GUARD_INTERVAL_AUTO:
	हाल GUARD_INTERVAL_1_8:
		वापस nxt6000_ग_लिखोreg(state, OFDM_COR_MODEGUARD, 0x02 | (nxt6000_पढ़ोreg(state, OFDM_COR_MODEGUARD) & ~0x03));

	हाल GUARD_INTERVAL_1_4:
		वापस nxt6000_ग_लिखोreg(state, OFDM_COR_MODEGUARD, 0x03 | (nxt6000_पढ़ोreg(state, OFDM_COR_MODEGUARD) & ~0x03));

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nxt6000_set_inversion(काष्ठा nxt6000_state *state,
				 क्रमागत fe_spectral_inversion inversion)
अणु
	चयन (inversion) अणु

	हाल INVERSION_OFF:
		वापस nxt6000_ग_लिखोreg(state, OFDM_ITB_CTL, 0x00);

	हाल INVERSION_ON:
		वापस nxt6000_ग_लिखोreg(state, OFDM_ITB_CTL, ITBINV);

	शेष:
		वापस -EINVAL;

	पूर्ण
पूर्ण

अटल पूर्णांक
nxt6000_set_transmission_mode(काष्ठा nxt6000_state *state,
			      क्रमागत fe_transmit_mode transmission_mode)
अणु
	पूर्णांक result;

	चयन (transmission_mode) अणु

	हाल TRANSMISSION_MODE_2K:
		अगर ((result = nxt6000_ग_लिखोreg(state, EN_DMD_RACQ, 0x00 | (nxt6000_पढ़ोreg(state, EN_DMD_RACQ) & ~0x03))) < 0)
			वापस result;

		वापस nxt6000_ग_लिखोreg(state, OFDM_COR_MODEGUARD, (0x00 << 2) | (nxt6000_पढ़ोreg(state, OFDM_COR_MODEGUARD) & ~0x04));

	हाल TRANSMISSION_MODE_8K:
	हाल TRANSMISSION_MODE_AUTO:
		अगर ((result = nxt6000_ग_लिखोreg(state, EN_DMD_RACQ, 0x02 | (nxt6000_पढ़ोreg(state, EN_DMD_RACQ) & ~0x03))) < 0)
			वापस result;

		वापस nxt6000_ग_लिखोreg(state, OFDM_COR_MODEGUARD, (0x01 << 2) | (nxt6000_पढ़ोreg(state, OFDM_COR_MODEGUARD) & ~0x04));

	शेष:
		वापस -EINVAL;

	पूर्ण
पूर्ण

अटल व्योम nxt6000_setup(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा nxt6000_state* state = fe->demodulator_priv;

	nxt6000_ग_लिखोreg(state, RS_COR_SYNC_PARAM, SYNC_PARAM);
	nxt6000_ग_लिखोreg(state, BER_CTRL, /*(1 << 2) | */ (0x01 << 1) | 0x01);
	nxt6000_ग_लिखोreg(state, VIT_BERTIME_2, 0x00);  // BER Timer = 0x000200 * 256 = 131072 bits
	nxt6000_ग_लिखोreg(state, VIT_BERTIME_1, 0x02);  //
	nxt6000_ग_लिखोreg(state, VIT_BERTIME_0, 0x00);  //
	nxt6000_ग_लिखोreg(state, VIT_COR_INTEN, 0x98); // Enable BER पूर्णांकerrupts
	nxt6000_ग_लिखोreg(state, VIT_COR_CTL, 0x82);   // Enable BER measurement
	nxt6000_ग_लिखोreg(state, VIT_COR_CTL, VIT_COR_RESYNC | 0x02 );
	nxt6000_ग_लिखोreg(state, OFDM_COR_CTL, (0x01 << 5) | (nxt6000_पढ़ोreg(state, OFDM_COR_CTL) & 0x0F));
	nxt6000_ग_लिखोreg(state, OFDM_COR_MODEGUARD, FORCEMODE8K | 0x02);
	nxt6000_ग_लिखोreg(state, OFDM_AGC_CTL, AGCLAST | INITIAL_AGC_BW);
	nxt6000_ग_लिखोreg(state, OFDM_ITB_FREQ_1, 0x06);
	nxt6000_ग_लिखोreg(state, OFDM_ITB_FREQ_2, 0x31);
	nxt6000_ग_लिखोreg(state, OFDM_CAS_CTL, (0x01 << 7) | (0x02 << 3) | 0x04);
	nxt6000_ग_लिखोreg(state, CAS_FREQ, 0xBB);	/* CHECKME */
	nxt6000_ग_लिखोreg(state, OFDM_SYR_CTL, 1 << 2);
	nxt6000_ग_लिखोreg(state, OFDM_PPM_CTL_1, PPM256);
	nxt6000_ग_लिखोreg(state, OFDM_TRL_NOMINALRATE_1, 0x49);
	nxt6000_ग_लिखोreg(state, OFDM_TRL_NOMINALRATE_2, 0x72);
	nxt6000_ग_लिखोreg(state, ANALOG_CONTROL_0, 1 << 5);
	nxt6000_ग_लिखोreg(state, EN_DMD_RACQ, (1 << 7) | (3 << 4) | 2);
	nxt6000_ग_लिखोreg(state, DIAG_CONFIG, TB_SET);

	अगर (state->config->घड़ी_inversion)
		nxt6000_ग_लिखोreg(state, SUB_DIAG_MODE_SEL, CLKINVERSION);
	अन्यथा
		nxt6000_ग_लिखोreg(state, SUB_DIAG_MODE_SEL, 0);

	nxt6000_ग_लिखोreg(state, TS_FORMAT, 0);
पूर्ण

अटल व्योम nxt6000_dump_status(काष्ठा nxt6000_state *state)
अणु
	u8 val;

#अगर 0
	pr_info("RS_COR_STAT: 0x%02X\n",
		nxt6000_पढ़ोreg(fe, RS_COR_STAT));
	pr_info("VIT_SYNC_STATUS: 0x%02X\n",
		nxt6000_पढ़ोreg(fe, VIT_SYNC_STATUS));
	pr_info("OFDM_COR_STAT: 0x%02X\n",
		nxt6000_पढ़ोreg(fe, OFDM_COR_STAT));
	pr_info("OFDM_SYR_STAT: 0x%02X\n",
		nxt6000_पढ़ोreg(fe, OFDM_SYR_STAT));
	pr_info("OFDM_TPS_RCVD_1: 0x%02X\n",
		nxt6000_पढ़ोreg(fe, OFDM_TPS_RCVD_1));
	pr_info("OFDM_TPS_RCVD_2: 0x%02X\n",
		nxt6000_पढ़ोreg(fe, OFDM_TPS_RCVD_2));
	pr_info("OFDM_TPS_RCVD_3: 0x%02X\n",
		nxt6000_पढ़ोreg(fe, OFDM_TPS_RCVD_3));
	pr_info("OFDM_TPS_RCVD_4: 0x%02X\n",
		nxt6000_पढ़ोreg(fe, OFDM_TPS_RCVD_4));
	pr_info("OFDM_TPS_RESERVED_1: 0x%02X\n",
		nxt6000_पढ़ोreg(fe, OFDM_TPS_RESERVED_1));
	pr_info("OFDM_TPS_RESERVED_2: 0x%02X\n",
		nxt6000_पढ़ोreg(fe, OFDM_TPS_RESERVED_2));
#पूर्ण_अगर
	pr_info("NXT6000 status:");

	val = nxt6000_पढ़ोreg(state, RS_COR_STAT);

	pr_cont(" DATA DESCR LOCK: %d,", val & 0x01);
	pr_cont(" DATA SYNC LOCK: %d,", (val >> 1) & 0x01);

	val = nxt6000_पढ़ोreg(state, VIT_SYNC_STATUS);

	pr_cont(" VITERBI LOCK: %d,", (val >> 7) & 0x01);

	चयन ((val >> 4) & 0x07) अणु

	हाल 0x00:
		pr_cont(" VITERBI CODERATE: 1/2,");
		अवरोध;

	हाल 0x01:
		pr_cont(" VITERBI CODERATE: 2/3,");
		अवरोध;

	हाल 0x02:
		pr_cont(" VITERBI CODERATE: 3/4,");
		अवरोध;

	हाल 0x03:
		pr_cont(" VITERBI CODERATE: 5/6,");
		अवरोध;

	हाल 0x04:
		pr_cont(" VITERBI CODERATE: 7/8,");
		अवरोध;

	शेष:
		pr_cont(" VITERBI CODERATE: Reserved,");

	पूर्ण

	val = nxt6000_पढ़ोreg(state, OFDM_COR_STAT);

	pr_cont(" CHCTrack: %d,", (val >> 7) & 0x01);
	pr_cont(" TPSLock: %d,", (val >> 6) & 0x01);
	pr_cont(" SYRLock: %d,", (val >> 5) & 0x01);
	pr_cont(" AGCLock: %d,", (val >> 4) & 0x01);

	चयन (val & 0x0F) अणु

	हाल 0x00:
		pr_cont(" CoreState: IDLE,");
		अवरोध;

	हाल 0x02:
		pr_cont(" CoreState: WAIT_AGC,");
		अवरोध;

	हाल 0x03:
		pr_cont(" CoreState: WAIT_SYR,");
		अवरोध;

	हाल 0x04:
		pr_cont(" CoreState: WAIT_PPM,");
		अवरोध;

	हाल 0x01:
		pr_cont(" CoreState: WAIT_TRL,");
		अवरोध;

	हाल 0x05:
		pr_cont(" CoreState: WAIT_TPS,");
		अवरोध;

	हाल 0x06:
		pr_cont(" CoreState: MONITOR_TPS,");
		अवरोध;

	शेष:
		pr_cont(" CoreState: Reserved,");

	पूर्ण

	val = nxt6000_पढ़ोreg(state, OFDM_SYR_STAT);

	pr_cont(" SYRLock: %d,", (val >> 4) & 0x01);
	pr_cont(" SYRMode: %s,", (val >> 2) & 0x01 ? "8K" : "2K");

	चयन ((val >> 4) & 0x03) अणु

	हाल 0x00:
		pr_cont(" SYRGuard: 1/32,");
		अवरोध;

	हाल 0x01:
		pr_cont(" SYRGuard: 1/16,");
		अवरोध;

	हाल 0x02:
		pr_cont(" SYRGuard: 1/8,");
		अवरोध;

	हाल 0x03:
		pr_cont(" SYRGuard: 1/4,");
		अवरोध;
	पूर्ण

	val = nxt6000_पढ़ोreg(state, OFDM_TPS_RCVD_3);

	चयन ((val >> 4) & 0x07) अणु

	हाल 0x00:
		pr_cont(" TPSLP: 1/2,");
		अवरोध;

	हाल 0x01:
		pr_cont(" TPSLP: 2/3,");
		अवरोध;

	हाल 0x02:
		pr_cont(" TPSLP: 3/4,");
		अवरोध;

	हाल 0x03:
		pr_cont(" TPSLP: 5/6,");
		अवरोध;

	हाल 0x04:
		pr_cont(" TPSLP: 7/8,");
		अवरोध;

	शेष:
		pr_cont(" TPSLP: Reserved,");

	पूर्ण

	चयन (val & 0x07) अणु

	हाल 0x00:
		pr_cont(" TPSHP: 1/2,");
		अवरोध;

	हाल 0x01:
		pr_cont(" TPSHP: 2/3,");
		अवरोध;

	हाल 0x02:
		pr_cont(" TPSHP: 3/4,");
		अवरोध;

	हाल 0x03:
		pr_cont(" TPSHP: 5/6,");
		अवरोध;

	हाल 0x04:
		pr_cont(" TPSHP: 7/8,");
		अवरोध;

	शेष:
		pr_cont(" TPSHP: Reserved,");

	पूर्ण

	val = nxt6000_पढ़ोreg(state, OFDM_TPS_RCVD_4);

	pr_cont(" TPSMode: %s,", val & 0x01 ? "8K" : "2K");

	चयन ((val >> 4) & 0x03) अणु

	हाल 0x00:
		pr_cont(" TPSGuard: 1/32,");
		अवरोध;

	हाल 0x01:
		pr_cont(" TPSGuard: 1/16,");
		अवरोध;

	हाल 0x02:
		pr_cont(" TPSGuard: 1/8,");
		अवरोध;

	हाल 0x03:
		pr_cont(" TPSGuard: 1/4,");
		अवरोध;

	पूर्ण

	/* Strange magic required to gain access to RF_AGC_STATUS */
	nxt6000_पढ़ोreg(state, RF_AGC_VAL_1);
	val = nxt6000_पढ़ोreg(state, RF_AGC_STATUS);
	val = nxt6000_पढ़ोreg(state, RF_AGC_STATUS);

	pr_cont(" RF AGC LOCK: %d,", (val >> 4) & 0x01);
	pr_cont("\n");
पूर्ण

अटल पूर्णांक nxt6000_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	u8 core_status;
	काष्ठा nxt6000_state* state = fe->demodulator_priv;

	*status = 0;

	core_status = nxt6000_पढ़ोreg(state, OFDM_COR_STAT);

	अगर (core_status & AGCLOCKED)
		*status |= FE_HAS_SIGNAL;

	अगर (nxt6000_पढ़ोreg(state, OFDM_SYR_STAT) & GI14_SYR_LOCK)
		*status |= FE_HAS_CARRIER;

	अगर (nxt6000_पढ़ोreg(state, VIT_SYNC_STATUS) & VITINSYNC)
		*status |= FE_HAS_VITERBI;

	अगर (nxt6000_पढ़ोreg(state, RS_COR_STAT) & RSCORESTATUS)
		*status |= FE_HAS_SYNC;

	अगर ((core_status & TPSLOCKED) && (*status == (FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC)))
		*status |= FE_HAS_LOCK;

	अगर (debug)
		nxt6000_dump_status(state);

	वापस 0;
पूर्ण

अटल पूर्णांक nxt6000_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा nxt6000_state* state = fe->demodulator_priv;

	nxt6000_reset(state);
	nxt6000_setup(fe);

	वापस 0;
पूर्ण

अटल पूर्णांक nxt6000_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा nxt6000_state* state = fe->demodulator_priv;
	पूर्णांक result;

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	result = nxt6000_set_bandwidth(state, p->bandwidth_hz);
	अगर (result < 0)
		वापस result;

	result = nxt6000_set_guard_पूर्णांकerval(state, p->guard_पूर्णांकerval);
	अगर (result < 0)
		वापस result;

	result = nxt6000_set_transmission_mode(state, p->transmission_mode);
	अगर (result < 0)
		वापस result;

	result = nxt6000_set_inversion(state, p->inversion);
	अगर (result < 0)
		वापस result;

	msleep(500);
	वापस 0;
पूर्ण

अटल व्योम nxt6000_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा nxt6000_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल पूर्णांक nxt6000_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा nxt6000_state* state = fe->demodulator_priv;

	*snr = nxt6000_पढ़ोreg( state, OFDM_CHC_SNR) / 8;

	वापस 0;
पूर्ण

अटल पूर्णांक nxt6000_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा nxt6000_state* state = fe->demodulator_priv;

	nxt6000_ग_लिखोreg( state, VIT_COR_INTSTAT, 0x18 );

	*ber = (nxt6000_पढ़ोreg( state, VIT_BER_1 ) << 8 ) |
		nxt6000_पढ़ोreg( state, VIT_BER_0 );

	nxt6000_ग_लिखोreg( state, VIT_COR_INTSTAT, 0x18); // Clear BER Done पूर्णांकerrupts

	वापस 0;
पूर्ण

अटल पूर्णांक nxt6000_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* संकेत_strength)
अणु
	काष्ठा nxt6000_state* state = fe->demodulator_priv;

	*संकेत_strength = (लघु) (511 -
		(nxt6000_पढ़ोreg(state, AGC_GAIN_1) +
		((nxt6000_पढ़ोreg(state, AGC_GAIN_2) & 0x03) << 8)));

	वापस 0;
पूर्ण

अटल पूर्णांक nxt6000_fe_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 500;
	वापस 0;
पूर्ण

अटल पूर्णांक nxt6000_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा nxt6000_state* state = fe->demodulator_priv;

	अगर (enable) अणु
		वापस nxt6000_ग_लिखोreg(state, ENABLE_TUNER_IIC, 0x01);
	पूर्ण अन्यथा अणु
		वापस nxt6000_ग_लिखोreg(state, ENABLE_TUNER_IIC, 0x00);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops nxt6000_ops;

काष्ठा dvb_frontend* nxt6000_attach(स्थिर काष्ठा nxt6000_config* config,
				    काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा nxt6000_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा nxt6000_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check अगर the demod is there */
	अगर (nxt6000_पढ़ोreg(state, OFDM_MSC_REV) != NXT6000ASICDEVICE) जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &nxt6000_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops nxt6000_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "NxtWave NXT6000 DVB-T",
		.frequency_min_hz = 0,
		.frequency_max_hz = 863250 * kHz,
		.frequency_stepsize_hz = 62500,
		/*.frequency_tolerance = *//* FIXME: 12% of SR */
		.symbol_rate_min = 0,	/* FIXME */
		.symbol_rate_max = 9360000,	/* FIXME */
		.symbol_rate_tolerance = 4000,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 | FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 | FE_CAN_FEC_8_9 | FE_CAN_FEC_AUTO |
			FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.release = nxt6000_release,

	.init = nxt6000_init,
	.i2c_gate_ctrl = nxt6000_i2c_gate_ctrl,

	.get_tune_settings = nxt6000_fe_get_tune_settings,

	.set_frontend = nxt6000_set_frontend,

	.पढ़ो_status = nxt6000_पढ़ो_status,
	.पढ़ो_ber = nxt6000_पढ़ो_ber,
	.पढ़ो_संकेत_strength = nxt6000_पढ़ो_संकेत_strength,
	.पढ़ो_snr = nxt6000_पढ़ो_snr,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("NxtWave NXT6000 DVB-T demodulator driver");
MODULE_AUTHOR("Florian Schirmer");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(nxt6000_attach);
