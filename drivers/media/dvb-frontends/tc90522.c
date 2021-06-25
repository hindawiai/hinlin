<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Toshiba TC90522 Demodulator
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 */

/*
 * NOTICE:
 * This driver is incomplete and lacks init/config of the chips,
 * as the necessary info is not disबंदd.
 * It assumes that users of this driver (such as a PCI bridge of
 * DTV receiver cards) properly init and configure the chip
 * via I2C *beक्रमe* calling this driver's init() function.
 *
 * Currently, PT3 driver is the only one that uses this driver,
 * and contains init/config code in its firmware.
 * Thus some part of the code might be dependent on PT3 specअगरic config.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_गणित.स>
#समावेश "tc90522.h"

#घोषणा TC90522_I2C_THRU_REG 0xfe

#घोषणा TC90522_MODULE_IDX(addr) (((u8)(addr) & 0x02U) >> 1)

काष्ठा tc90522_state अणु
	काष्ठा tc90522_config cfg;
	काष्ठा dvb_frontend fe;
	काष्ठा i2c_client *i2c_client;
	काष्ठा i2c_adapter tuner_i2c;

	bool lna;
पूर्ण;

काष्ठा reg_val अणु
	u8 reg;
	u8 val;
पूर्ण;

अटल पूर्णांक
reg_ग_लिखो(काष्ठा tc90522_state *state, स्थिर काष्ठा reg_val *regs, पूर्णांक num)
अणु
	पूर्णांक i, ret;
	काष्ठा i2c_msg msg;

	ret = 0;
	msg.addr = state->i2c_client->addr;
	msg.flags = 0;
	msg.len = 2;
	क्रम (i = 0; i < num; i++) अणु
		msg.buf = (u8 *)&regs[i];
		ret = i2c_transfer(state->i2c_client->adapter, &msg, 1);
		अगर (ret == 0)
			ret = -EIO;
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक reg_पढ़ो(काष्ठा tc90522_state *state, u8 reg, u8 *val, u8 len)
अणु
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = state->i2c_client->addr,
			.flags = 0,
			.buf = &reg,
			.len = 1,
		पूर्ण,
		अणु
			.addr = state->i2c_client->addr,
			.flags = I2C_M_RD,
			.buf = val,
			.len = len,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(state->i2c_client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret == ARRAY_SIZE(msgs))
		ret = 0;
	अन्यथा अगर (ret >= 0)
		ret = -EIO;
	वापस ret;
पूर्ण

अटल काष्ठा tc90522_state *cfg_to_state(काष्ठा tc90522_config *c)
अणु
	वापस container_of(c, काष्ठा tc90522_state, cfg);
पूर्ण


अटल पूर्णांक tc90522s_set_tsid(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा reg_val set_tsid[] = अणु
		अणु 0x8f, 00 पूर्ण,
		अणु 0x90, 00 पूर्ण
	पूर्ण;

	set_tsid[0].val = (fe->dtv_property_cache.stream_id & 0xff00) >> 8;
	set_tsid[1].val = fe->dtv_property_cache.stream_id & 0xff;
	वापस reg_ग_लिखो(fe->demodulator_priv, set_tsid, ARRAY_SIZE(set_tsid));
पूर्ण

अटल पूर्णांक tc90522t_set_layers(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा reg_val rv;
	u8 laysel;

	laysel = ~fe->dtv_property_cache.isdbt_layer_enabled & 0x07;
	laysel = (laysel & 0x01) << 2 | (laysel & 0x02) | (laysel & 0x04) >> 2;
	rv.reg = 0x71;
	rv.val = laysel;
	वापस reg_ग_लिखो(fe->demodulator_priv, &rv, 1);
पूर्ण

/* frontend ops */

अटल पूर्णांक tc90522s_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा tc90522_state *state;
	पूर्णांक ret;
	u8 reg;

	state = fe->demodulator_priv;
	ret = reg_पढ़ो(state, 0xc3, &reg, 1);
	अगर (ret < 0)
		वापस ret;

	*status = 0;
	अगर (reg & 0x80) /* input level under min ? */
		वापस 0;
	*status |= FE_HAS_SIGNAL;

	अगर (reg & 0x60) /* carrier? */
		वापस 0;
	*status |= FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC;

	अगर (reg & 0x10)
		वापस 0;
	अगर (reg_पढ़ो(state, 0xc5, &reg, 1) < 0 || !(reg & 0x03))
		वापस 0;
	*status |= FE_HAS_LOCK;
	वापस 0;
पूर्ण

अटल पूर्णांक tc90522t_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा tc90522_state *state;
	पूर्णांक ret;
	u8 reg;

	state = fe->demodulator_priv;
	ret = reg_पढ़ो(state, 0x96, &reg, 1);
	अगर (ret < 0)
		वापस ret;

	*status = 0;
	अगर (reg & 0xe0) अणु
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI
				| FE_HAS_SYNC | FE_HAS_LOCK;
		वापस 0;
	पूर्ण

	ret = reg_पढ़ो(state, 0x80, &reg, 1);
	अगर (ret < 0)
		वापस ret;

	अगर (reg & 0xf0)
		वापस 0;
	*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;

	अगर (reg & 0x0c)
		वापस 0;
	*status |= FE_HAS_SYNC | FE_HAS_VITERBI;

	अगर (reg & 0x02)
		वापस 0;
	*status |= FE_HAS_LOCK;
	वापस 0;
पूर्ण

अटल स्थिर क्रमागत fe_code_rate fec_conv_sat[] = अणु
	FEC_NONE, /* unused */
	FEC_1_2, /* क्रम BPSK */
	FEC_1_2, FEC_2_3, FEC_3_4, FEC_5_6, FEC_7_8, /* क्रम QPSK */
	FEC_2_3, /* क्रम 8PSK. (trellis code) */
पूर्ण;

अटल पूर्णांक tc90522s_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा tc90522_state *state;
	काष्ठा dtv_fe_stats *stats;
	पूर्णांक ret, i;
	पूर्णांक layers;
	u8 val[10];
	u32 cndat;

	state = fe->demodulator_priv;
	c->delivery_प्रणाली = SYS_ISDBS;
	c->symbol_rate = 28860000;

	layers = 0;
	ret = reg_पढ़ो(state, 0xe6, val, 5);
	अगर (ret == 0) अणु
		u8 v;

		c->stream_id = val[0] << 8 | val[1];

		/* high/single layer */
		v = (val[2] & 0x70) >> 4;
		c->modulation = (v == 7) ? PSK_8 : QPSK;
		c->fec_inner = fec_conv_sat[v];
		c->layer[0].fec = c->fec_inner;
		c->layer[0].modulation = c->modulation;
		c->layer[0].segment_count = val[3] & 0x3f; /* slots */

		/* low layer */
		v = (val[2] & 0x07);
		c->layer[1].fec = fec_conv_sat[v];
		अगर (v == 0)  /* no low layer */
			c->layer[1].segment_count = 0;
		अन्यथा
			c->layer[1].segment_count = val[4] & 0x3f; /* slots */
		/*
		 * actually, BPSK अगर v==1, but not defined in
		 * क्रमागत fe_modulation
		 */
		c->layer[1].modulation = QPSK;
		layers = (v > 0) ? 2 : 1;
	पूर्ण

	/* statistics */

	stats = &c->strength;
	stats->len = 0;
	/* let the connected tuner set RSSI property cache */
	अगर (fe->ops.tuner_ops.get_rf_strength) अणु
		u16 dummy;

		fe->ops.tuner_ops.get_rf_strength(fe, &dummy);
	पूर्ण

	stats = &c->cnr;
	stats->len = 1;
	stats->stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	cndat = 0;
	ret = reg_पढ़ो(state, 0xbc, val, 2);
	अगर (ret == 0)
		cndat = val[0] << 8 | val[1];
	अगर (cndat >= 3000) अणु
		u32 p, p4;
		s64 cn;

		cndat -= 3000;  /* cndat: 4.12 fixed poपूर्णांक भग्न */
		/*
		 * cnr[mdB] = -1634.6 * P^5 + 14341 * P^4 - 50259 * P^3
		 *                 + 88977 * P^2 - 89565 * P + 58857
		 *  (P = वर्ग_मूल(cndat) / 64)
		 */
		/* p := वर्ग_मूल(cndat) << 8 = P << 14, 2.14 fixed  poपूर्णांक भग्न */
		/* cn = cnr << 3 */
		p = पूर्णांक_वर्ग_मूल(cndat << 16);
		p4 = cndat * cndat;
		cn = भाग64_s64(-16346LL * p4 * p, 10) >> 35;
		cn += (14341LL * p4) >> 21;
		cn -= (50259LL * cndat * p) >> 23;
		cn += (88977LL * cndat) >> 9;
		cn -= (89565LL * p) >> 11;
		cn += 58857  << 3;
		stats->stat[0].svalue = cn >> 3;
		stats->stat[0].scale = FE_SCALE_DECIBEL;
	पूर्ण

	/* per-layer post viterbi BER (or PER? config dependent?) */
	stats = &c->post_bit_error;
	स_रखो(stats, 0, माप(*stats));
	stats->len = layers;
	ret = reg_पढ़ो(state, 0xeb, val, 10);
	अगर (ret < 0)
		क्रम (i = 0; i < layers; i++)
			stats->stat[i].scale = FE_SCALE_NOT_AVAILABLE;
	अन्यथा अणु
		क्रम (i = 0; i < layers; i++) अणु
			stats->stat[i].scale = FE_SCALE_COUNTER;
			stats->stat[i].uvalue = val[i * 5] << 16
				| val[i * 5 + 1] << 8 | val[i * 5 + 2];
		पूर्ण
	पूर्ण
	stats = &c->post_bit_count;
	स_रखो(stats, 0, माप(*stats));
	stats->len = layers;
	अगर (ret < 0)
		क्रम (i = 0; i < layers; i++)
			stats->stat[i].scale = FE_SCALE_NOT_AVAILABLE;
	अन्यथा अणु
		क्रम (i = 0; i < layers; i++) अणु
			stats->stat[i].scale = FE_SCALE_COUNTER;
			stats->stat[i].uvalue =
				val[i * 5 + 3] << 8 | val[i * 5 + 4];
			stats->stat[i].uvalue *= 204 * 8;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर क्रमागत fe_transmit_mode पंचांग_conv[] = अणु
	TRANSMISSION_MODE_2K,
	TRANSMISSION_MODE_4K,
	TRANSMISSION_MODE_8K,
	0
पूर्ण;

अटल स्थिर क्रमागत fe_code_rate fec_conv_ter[] = अणु
	FEC_1_2, FEC_2_3, FEC_3_4, FEC_5_6, FEC_7_8, 0, 0, 0
पूर्ण;

अटल स्थिर क्रमागत fe_modulation mod_conv[] = अणु
	DQPSK, QPSK, QAM_16, QAM_64, 0, 0, 0, 0
पूर्ण;

अटल पूर्णांक tc90522t_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा tc90522_state *state;
	काष्ठा dtv_fe_stats *stats;
	पूर्णांक ret, i;
	पूर्णांक layers;
	u8 val[15], mode;
	u32 cndat;

	state = fe->demodulator_priv;
	c->delivery_प्रणाली = SYS_ISDBT;
	c->bandwidth_hz = 6000000;
	mode = 1;
	ret = reg_पढ़ो(state, 0xb0, val, 1);
	अगर (ret == 0) अणु
		mode = (val[0] & 0xc0) >> 6;
		c->transmission_mode = पंचांग_conv[mode];
		c->guard_पूर्णांकerval = (val[0] & 0x30) >> 4;
	पूर्ण

	ret = reg_पढ़ो(state, 0xb2, val, 6);
	layers = 0;
	अगर (ret == 0) अणु
		u8 v;

		c->isdbt_partial_reception = val[0] & 0x01;
		c->isdbt_sb_mode = (val[0] & 0xc0) == 0x40;

		/* layer A */
		v = (val[2] & 0x78) >> 3;
		अगर (v == 0x0f)
			c->layer[0].segment_count = 0;
		अन्यथा अणु
			layers++;
			c->layer[0].segment_count = v;
			c->layer[0].fec = fec_conv_ter[(val[1] & 0x1c) >> 2];
			c->layer[0].modulation = mod_conv[(val[1] & 0xe0) >> 5];
			v = (val[1] & 0x03) << 1 | (val[2] & 0x80) >> 7;
			c->layer[0].पूर्णांकerleaving = v;
		पूर्ण

		/* layer B */
		v = (val[3] & 0x03) << 2 | (val[4] & 0xc0) >> 6;
		अगर (v == 0x0f)
			c->layer[1].segment_count = 0;
		अन्यथा अणु
			layers++;
			c->layer[1].segment_count = v;
			c->layer[1].fec = fec_conv_ter[(val[3] & 0xe0) >> 5];
			c->layer[1].modulation = mod_conv[(val[2] & 0x07)];
			c->layer[1].पूर्णांकerleaving = (val[3] & 0x1c) >> 2;
		पूर्ण

		/* layer C */
		v = (val[5] & 0x1e) >> 1;
		अगर (v == 0x0f)
			c->layer[2].segment_count = 0;
		अन्यथा अणु
			layers++;
			c->layer[2].segment_count = v;
			c->layer[2].fec = fec_conv_ter[(val[4] & 0x07)];
			c->layer[2].modulation = mod_conv[(val[4] & 0x38) >> 3];
			c->layer[2].पूर्णांकerleaving = (val[5] & 0xe0) >> 5;
		पूर्ण
	पूर्ण

	/* statistics */

	stats = &c->strength;
	stats->len = 0;
	/* let the connected tuner set RSSI property cache */
	अगर (fe->ops.tuner_ops.get_rf_strength) अणु
		u16 dummy;

		fe->ops.tuner_ops.get_rf_strength(fe, &dummy);
	पूर्ण

	stats = &c->cnr;
	stats->len = 1;
	stats->stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	cndat = 0;
	ret = reg_पढ़ो(state, 0x8b, val, 3);
	अगर (ret == 0)
		cndat = val[0] << 16 | val[1] << 8 | val[2];
	अगर (cndat != 0) अणु
		u32 p, पंचांगp;
		s64 cn;

		/*
		 * cnr[mdB] = 0.024 P^4 - 1.6 P^3 + 39.8 P^2 + 549.1 P + 3096.5
		 * (P = 10log10(5505024/cndat))
		 */
		/* cn = cnr << 3 (61.3 fixed poपूर्णांक भग्न */
		/* p = 10log10(5505024/cndat) << 24  (8.24 fixed poपूर्णांक भग्न)*/
		p = पूर्णांकlog10(5505024) - पूर्णांकlog10(cndat);
		p *= 10;

		cn = 24772;
		cn += भाग64_s64(43827LL * p, 10) >> 24;
		पंचांगp = p >> 8;
		cn += भाग64_s64(3184LL * पंचांगp * पंचांगp, 10) >> 32;
		पंचांगp = p >> 13;
		cn -= भाग64_s64(128LL * पंचांगp * पंचांगp * पंचांगp, 10) >> 33;
		पंचांगp = p >> 18;
		cn += भाग64_s64(192LL * पंचांगp * पंचांगp * पंचांगp * पंचांगp, 1000) >> 24;

		stats->stat[0].svalue = cn >> 3;
		stats->stat[0].scale = FE_SCALE_DECIBEL;
	पूर्ण

	/* per-layer post viterbi BER (or PER? config dependent?) */
	stats = &c->post_bit_error;
	स_रखो(stats, 0, माप(*stats));
	stats->len = layers;
	ret = reg_पढ़ो(state, 0x9d, val, 15);
	अगर (ret < 0)
		क्रम (i = 0; i < layers; i++)
			stats->stat[i].scale = FE_SCALE_NOT_AVAILABLE;
	अन्यथा अणु
		क्रम (i = 0; i < layers; i++) अणु
			stats->stat[i].scale = FE_SCALE_COUNTER;
			stats->stat[i].uvalue = val[i * 3] << 16
				| val[i * 3 + 1] << 8 | val[i * 3 + 2];
		पूर्ण
	पूर्ण
	stats = &c->post_bit_count;
	स_रखो(stats, 0, माप(*stats));
	stats->len = layers;
	अगर (ret < 0)
		क्रम (i = 0; i < layers; i++)
			stats->stat[i].scale = FE_SCALE_NOT_AVAILABLE;
	अन्यथा अणु
		क्रम (i = 0; i < layers; i++) अणु
			stats->stat[i].scale = FE_SCALE_COUNTER;
			stats->stat[i].uvalue =
				val[9 + i * 2] << 8 | val[9 + i * 2 + 1];
			stats->stat[i].uvalue *= 204 * 8;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_val reset_sat = अणु 0x03, 0x01 पूर्ण;
अटल स्थिर काष्ठा reg_val reset_ter = अणु 0x01, 0x40 पूर्ण;

अटल पूर्णांक tc90522_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tc90522_state *state;
	पूर्णांक ret;

	state = fe->demodulator_priv;

	अगर (fe->ops.tuner_ops.set_params)
		ret = fe->ops.tuner_ops.set_params(fe);
	अन्यथा
		ret = -ENODEV;
	अगर (ret < 0)
		जाओ failed;

	अगर (fe->ops.delsys[0] == SYS_ISDBS) अणु
		ret = tc90522s_set_tsid(fe);
		अगर (ret < 0)
			जाओ failed;
		ret = reg_ग_लिखो(state, &reset_sat, 1);
	पूर्ण अन्यथा अणु
		ret = tc90522t_set_layers(fe);
		अगर (ret < 0)
			जाओ failed;
		ret = reg_ग_लिखो(state, &reset_ter, 1);
	पूर्ण
	अगर (ret < 0)
		जाओ failed;

	वापस 0;

failed:
	dev_warn(&state->tuner_i2c.dev, "(%s) failed. [adap%d-fe%d]\n",
			__func__, fe->dvb->num, fe->id);
	वापस ret;
पूर्ण

अटल पूर्णांक tc90522_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *settings)
अणु
	अगर (fe->ops.delsys[0] == SYS_ISDBS) अणु
		settings->min_delay_ms = 250;
		settings->step_size = 1000;
		settings->max_drअगरt = settings->step_size * 2;
	पूर्ण अन्यथा अणु
		settings->min_delay_ms = 400;
		settings->step_size = 142857;
		settings->max_drअगरt = settings->step_size;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tc90522_set_अगर_agc(काष्ठा dvb_frontend *fe, bool on)
अणु
	काष्ठा reg_val agc_sat[] = अणु
		अणु 0x0a, 0x00 पूर्ण,
		अणु 0x10, 0x30 पूर्ण,
		अणु 0x11, 0x00 पूर्ण,
		अणु 0x03, 0x01 पूर्ण,
	पूर्ण;
	काष्ठा reg_val agc_ter[] = अणु
		अणु 0x25, 0x00 पूर्ण,
		अणु 0x23, 0x4c पूर्ण,
		अणु 0x01, 0x40 पूर्ण,
	पूर्ण;
	काष्ठा tc90522_state *state;
	काष्ठा reg_val *rv;
	पूर्णांक num;

	state = fe->demodulator_priv;
	अगर (fe->ops.delsys[0] == SYS_ISDBS) अणु
		agc_sat[0].val = on ? 0xff : 0x00;
		agc_sat[1].val |= 0x80;
		agc_sat[1].val |= on ? 0x01 : 0x00;
		agc_sat[2].val |= on ? 0x40 : 0x00;
		rv = agc_sat;
		num = ARRAY_SIZE(agc_sat);
	पूर्ण अन्यथा अणु
		agc_ter[0].val = on ? 0x40 : 0x00;
		agc_ter[1].val |= on ? 0x00 : 0x01;
		rv = agc_ter;
		num = ARRAY_SIZE(agc_ter);
	पूर्ण
	वापस reg_ग_लिखो(state, rv, num);
पूर्ण

अटल स्थिर काष्ठा reg_val sleep_sat = अणु 0x17, 0x01 पूर्ण;
अटल स्थिर काष्ठा reg_val sleep_ter = अणु 0x03, 0x90 पूर्ण;

अटल पूर्णांक tc90522_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tc90522_state *state;
	पूर्णांक ret;

	state = fe->demodulator_priv;
	अगर (fe->ops.delsys[0] == SYS_ISDBS)
		ret = reg_ग_लिखो(state, &sleep_sat, 1);
	अन्यथा अणु
		ret = reg_ग_लिखो(state, &sleep_ter, 1);
		अगर (ret == 0 && fe->ops.set_lna &&
		    fe->dtv_property_cache.lna == LNA_AUTO) अणु
			fe->dtv_property_cache.lna = 0;
			ret = fe->ops.set_lna(fe);
			fe->dtv_property_cache.lna = LNA_AUTO;
		पूर्ण
	पूर्ण
	अगर (ret < 0)
		dev_warn(&state->tuner_i2c.dev,
			"(%s) failed. [adap%d-fe%d]\n",
			__func__, fe->dvb->num, fe->id);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा reg_val wakeup_sat = अणु 0x17, 0x00 पूर्ण;
अटल स्थिर काष्ठा reg_val wakeup_ter = अणु 0x03, 0x80 पूर्ण;

अटल पूर्णांक tc90522_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tc90522_state *state;
	पूर्णांक ret;

	/*
	 * Because the init sequence is not खुला,
	 * the parent device/driver should have init'ed the device beक्रमe.
	 * just wake up the device here.
	 */

	state = fe->demodulator_priv;
	अगर (fe->ops.delsys[0] == SYS_ISDBS)
		ret = reg_ग_लिखो(state, &wakeup_sat, 1);
	अन्यथा अणु
		ret = reg_ग_लिखो(state, &wakeup_ter, 1);
		अगर (ret == 0 && fe->ops.set_lna &&
		    fe->dtv_property_cache.lna == LNA_AUTO) अणु
			fe->dtv_property_cache.lna = 1;
			ret = fe->ops.set_lna(fe);
			fe->dtv_property_cache.lna = LNA_AUTO;
		पूर्ण
	पूर्ण
	अगर (ret < 0) अणु
		dev_warn(&state->tuner_i2c.dev,
			"(%s) failed. [adap%d-fe%d]\n",
			__func__, fe->dvb->num, fe->id);
		वापस ret;
	पूर्ण

	/* prefer 'all-layers' to 'none' as a शेष */
	अगर (fe->dtv_property_cache.isdbt_layer_enabled == 0)
		fe->dtv_property_cache.isdbt_layer_enabled = 7;
	वापस tc90522_set_अगर_agc(fe, true);
पूर्ण


/*
 * tuner I2C adapter functions
 */

अटल पूर्णांक
tc90522_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा tc90522_state *state;
	काष्ठा i2c_msg *new_msgs;
	पूर्णांक i, j;
	पूर्णांक ret, rd_num;
	u8 wbuf[256];
	u8 *p, *bufend;

	अगर (num <= 0)
		वापस -EINVAL;

	rd_num = 0;
	क्रम (i = 0; i < num; i++)
		अगर (msgs[i].flags & I2C_M_RD)
			rd_num++;
	new_msgs = kदो_स्मृति_array(num + rd_num, माप(*new_msgs), GFP_KERNEL);
	अगर (!new_msgs)
		वापस -ENOMEM;

	state = i2c_get_adapdata(adap);
	p = wbuf;
	bufend = wbuf + माप(wbuf);
	क्रम (i = 0, j = 0; i < num; i++, j++) अणु
		new_msgs[j].addr = state->i2c_client->addr;
		new_msgs[j].flags = msgs[i].flags;

		अगर (msgs[i].flags & I2C_M_RD) अणु
			new_msgs[j].flags &= ~I2C_M_RD;
			अगर (p + 2 > bufend)
				अवरोध;
			p[0] = TC90522_I2C_THRU_REG;
			p[1] = msgs[i].addr << 1 | 0x01;
			new_msgs[j].buf = p;
			new_msgs[j].len = 2;
			p += 2;
			j++;
			new_msgs[j].addr = state->i2c_client->addr;
			new_msgs[j].flags = msgs[i].flags;
			new_msgs[j].buf = msgs[i].buf;
			new_msgs[j].len = msgs[i].len;
			जारी;
		पूर्ण

		अगर (p + msgs[i].len + 2 > bufend)
			अवरोध;
		p[0] = TC90522_I2C_THRU_REG;
		p[1] = msgs[i].addr << 1;
		स_नकल(p + 2, msgs[i].buf, msgs[i].len);
		new_msgs[j].buf = p;
		new_msgs[j].len = msgs[i].len + 2;
		p += new_msgs[j].len;
	पूर्ण

	अगर (i < num) अणु
		ret = -ENOMEM;
	पूर्ण अन्यथा अगर (!state->cfg.split_tuner_पढ़ो_i2c || rd_num == 0) अणु
		ret = i2c_transfer(state->i2c_client->adapter, new_msgs, j);
	पूर्ण अन्यथा अणु
		/*
		 * Split transactions at each I2C_M_RD message.
		 * Some of the parent device require this,
		 * such as Friio (see. dvb-usb-gl861).
		 */
		पूर्णांक from, to;

		ret = 0;
		from = 0;
		करो अणु
			पूर्णांक r;

			to = from + 1;
			जबतक (to < j && !(new_msgs[to].flags & I2C_M_RD))
				to++;
			r = i2c_transfer(state->i2c_client->adapter,
					 &new_msgs[from], to - from);
			ret = (r <= 0) ? r : ret + r;
			from = to;
		पूर्ण जबतक (from < j && ret > 0);
	पूर्ण

	अगर (ret >= 0 && ret < j)
		ret = -EIO;
	kमुक्त(new_msgs);
	वापस (ret == j) ? num : ret;
पूर्ण

अटल u32 tc90522_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm tc90522_tuner_i2c_algo = अणु
	.master_xfer   = &tc90522_master_xfer,
	.functionality = &tc90522_functionality,
पूर्ण;


/*
 * I2C driver functions
 */

अटल स्थिर काष्ठा dvb_frontend_ops tc90522_ops_sat = अणु
	.delsys = अणु SYS_ISDBS पूर्ण,
	.info = अणु
		.name = "Toshiba TC90522 ISDB-S module",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
		.caps = FE_CAN_INVERSION_AUTO | FE_CAN_FEC_AUTO |
			FE_CAN_QAM_AUTO | FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO | FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.init = tc90522_init,
	.sleep = tc90522_sleep,
	.set_frontend = tc90522_set_frontend,
	.get_tune_settings = tc90522_get_tune_settings,

	.get_frontend = tc90522s_get_frontend,
	.पढ़ो_status = tc90522s_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा dvb_frontend_ops tc90522_ops_ter = अणु
	.delsys = अणु SYS_ISDBT पूर्ण,
	.info = अणु
		.name = "Toshiba TC90522 ISDB-T module",
		.frequency_min_hz = 470 * MHz,
		.frequency_max_hz = 770 * MHz,
		.frequency_stepsize_hz = 142857,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2  | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6  | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK     | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
			FE_CAN_QAM_AUTO | FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO | FE_CAN_RECOVER |
			FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.init = tc90522_init,
	.sleep = tc90522_sleep,
	.set_frontend = tc90522_set_frontend,
	.get_tune_settings = tc90522_get_tune_settings,

	.get_frontend = tc90522t_get_frontend,
	.पढ़ो_status = tc90522t_पढ़ो_status,
पूर्ण;


अटल पूर्णांक tc90522_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tc90522_state *state;
	काष्ठा tc90522_config *cfg;
	स्थिर काष्ठा dvb_frontend_ops *ops;
	काष्ठा i2c_adapter *adap;
	पूर्णांक ret;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;
	state->i2c_client = client;

	cfg = client->dev.platक्रमm_data;
	स_नकल(&state->cfg, cfg, माप(state->cfg));
	cfg->fe = state->cfg.fe = &state->fe;
	ops =  id->driver_data == 0 ? &tc90522_ops_sat : &tc90522_ops_ter;
	स_नकल(&state->fe.ops, ops, माप(*ops));
	state->fe.demodulator_priv = state;

	adap = &state->tuner_i2c;
	adap->owner = THIS_MODULE;
	adap->algo = &tc90522_tuner_i2c_algo;
	adap->dev.parent = &client->dev;
	strscpy(adap->name, "tc90522_sub", माप(adap->name));
	i2c_set_adapdata(adap, state);
	ret = i2c_add_adapter(adap);
	अगर (ret < 0)
		जाओ मुक्त_state;
	cfg->tuner_i2c = state->cfg.tuner_i2c = adap;

	i2c_set_clientdata(client, &state->cfg);
	dev_info(&client->dev, "Toshiba TC90522 attached.\n");
	वापस 0;
मुक्त_state:
	kमुक्त(state);
	वापस ret;
पूर्ण

अटल पूर्णांक tc90522_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tc90522_state *state;

	state = cfg_to_state(i2c_get_clientdata(client));
	i2c_del_adapter(&state->tuner_i2c);
	kमुक्त(state);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा i2c_device_id tc90522_id[] = अणु
	अणु TC90522_I2C_DEV_SAT, 0 पूर्ण,
	अणु TC90522_I2C_DEV_TER, 1 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tc90522_id);

अटल काष्ठा i2c_driver tc90522_driver = अणु
	.driver = अणु
		.name	= "tc90522",
	पूर्ण,
	.probe		= tc90522_probe,
	.हटाओ		= tc90522_हटाओ,
	.id_table	= tc90522_id,
पूर्ण;

module_i2c_driver(tc90522_driver);

MODULE_DESCRIPTION("Toshiba TC90522 frontend");
MODULE_AUTHOR("Akihiro TSUKADA");
MODULE_LICENSE("GPL");
