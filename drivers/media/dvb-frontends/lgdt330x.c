<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Support क्रम LGDT3302 and LGDT3303 - VSB/QAM
 *
 *    Copyright (C) 2005 Wilson Michaels <wilsonmichaels@earthlink.net>
 */

/*
 *                      NOTES ABOUT THIS DRIVER
 *
 * This Linux driver supports:
 *   DViCO FusionHDTV 3 Gold-Q
 *   DViCO FusionHDTV 3 Gold-T
 *   DViCO FusionHDTV 5 Gold
 *   DViCO FusionHDTV 5 Lite
 *   DViCO FusionHDTV 5 USB Gold
 *   Air2PC/AirStar 2 ATSC 3rd generation (HD5000)
 *   pcHDTV HD5500
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_गणित.स>
#समावेश "lgdt330x_priv.h"
#समावेश "lgdt330x.h"

/* Use Equalizer Mean Squared Error instead of Phaser Tracker MSE */
/* #घोषणा USE_EQMSE */

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off lgdt330x frontend debugging (default:off).");

#घोषणा dprपूर्णांकk(state, fmt, arg...) करो अणु				\
	अगर (debug)							\
		dev_prपूर्णांकk(KERN_DEBUG, &state->client->dev, fmt, ##arg);\
पूर्ण जबतक (0)

काष्ठा lgdt330x_state अणु
	काष्ठा i2c_client *client;

	/* Configuration settings */
	काष्ठा lgdt330x_config config;

	काष्ठा dvb_frontend frontend;

	/* Demodulator निजी data */
	क्रमागत fe_modulation current_modulation;
	u32 snr;	/* Result of last SNR calculation */
	u16 ucblocks;
	अचिन्हित दीर्घ last_stats_समय;

	/* Tuner निजी data */
	u32 current_frequency;
पूर्ण;

अटल पूर्णांक i2c_ग_लिखो_demod_bytes(काष्ठा lgdt330x_state *state,
				 स्थिर u8 *buf, /* data bytes to send */
				 पूर्णांक len  /* number of bytes to send */)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < len - 1; i += 2) अणु
		err = i2c_master_send(state->client, buf, 2);
		अगर (err != 2) अणु
			dev_warn(&state->client->dev,
				 "%s: error (addr %02x <- %02x, err = %i)\n",
				__func__, buf[0], buf[1], err);
			अगर (err < 0)
				वापस err;
			अन्यथा
				वापस -EREMOTEIO;
		पूर्ण
		buf += 2;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This routine ग_लिखोs the रेजिस्टर (reg) to the demod bus
 * then पढ़ोs the data वापसed क्रम (len) bytes.
 */
अटल पूर्णांक i2c_पढ़ो_demod_bytes(काष्ठा lgdt330x_state *state,
				क्रमागत I2C_REG reg, u8 *buf, पूर्णांक len)
अणु
	u8 wr[] = अणु reg पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = state->client->addr,
			.flags = 0,
			.buf = wr,
			.len = 1
		पूर्ण, अणु
			.addr = state->client->addr,
			.flags = I2C_M_RD,
			.buf = buf,
			.len = len
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(state->client->adapter, msg, 2);
	अगर (ret != 2) अणु
		dev_warn(&state->client->dev,
			 "%s: addr 0x%02x select 0x%02x error (ret == %i)\n",
			 __func__, state->client->addr, reg, ret);
		अगर (ret >= 0)
			ret = -EIO;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

/* Software reset */
अटल पूर्णांक lgdt3302_sw_reset(काष्ठा lgdt330x_state *state)
अणु
	u8 ret;
	u8 reset[] = अणु
		IRQ_MASK,
		/*
		 * bit 6 is active low software reset
		 * bits 5-0 are 1 to mask पूर्णांकerrupts
		 */
		0x00
	पूर्ण;

	ret = i2c_ग_लिखो_demod_bytes(state,
				    reset, माप(reset));
	अगर (ret == 0) अणु
		/* क्रमce reset high (inactive) and unmask पूर्णांकerrupts */
		reset[1] = 0x7f;
		ret = i2c_ग_लिखो_demod_bytes(state,
					    reset, माप(reset));
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3303_sw_reset(काष्ठा lgdt330x_state *state)
अणु
	u8 ret;
	u8 reset[] = अणु
		0x02,
		0x00 /* bit 0 is active low software reset */
	पूर्ण;

	ret = i2c_ग_लिखो_demod_bytes(state,
				    reset, माप(reset));
	अगर (ret == 0) अणु
		/* क्रमce reset high (inactive) */
		reset[1] = 0x01;
		ret = i2c_ग_लिखो_demod_bytes(state,
					    reset, माप(reset));
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt330x_sw_reset(काष्ठा lgdt330x_state *state)
अणु
	चयन (state->config.demod_chip) अणु
	हाल LGDT3302:
		वापस lgdt3302_sw_reset(state);
	हाल LGDT3303:
		वापस lgdt3303_sw_reset(state);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल पूर्णांक lgdt330x_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	अक्षर  *chip_name;
	पूर्णांक    err;
	/*
	 * Array of byte pairs <address, value>
	 * to initialize each dअगरferent chip
	 */
	अटल स्थिर u8 lgdt3302_init_data[] = अणु
		/* Use 50MHz param values from spec sheet since xtal is 50 */
		/*
		 * Change the value of NCOCTFV[25:0] of carrier
		 * recovery center frequency रेजिस्टर
		 */
		VSB_CARRIER_FREQ0, 0x00,
		VSB_CARRIER_FREQ1, 0x87,
		VSB_CARRIER_FREQ2, 0x8e,
		VSB_CARRIER_FREQ3, 0x01,
		/*
		 * Change the TPCLK pin polarity
		 * data is valid on falling घड़ी
		 */
		DEMUX_CONTROL, 0xfb,
		/*
		 * Change the value of IFBW[11:0] of
		 * AGC IF/RF loop filter bandwidth रेजिस्टर
		 */
		AGC_RF_BANDWIDTH0, 0x40,
		AGC_RF_BANDWIDTH1, 0x93,
		AGC_RF_BANDWIDTH2, 0x00,
		/*
		 * Change the value of bit 6, 'nINAGCBY' and
		 * 'NSSEL[1:0] of ACG function control रेजिस्टर 2
		 */
		AGC_FUNC_CTRL2, 0xc6,
		/*
		 * Change the value of bit 6 'RFFIX'
		 * of AGC function control रेजिस्टर 3
		 */
		AGC_FUNC_CTRL3, 0x40,
		/*
		 * Set the value of 'INLVTHD' रेजिस्टर 0x2a/0x2c
		 * to 0x7fe
		 */
		AGC_DELAY0, 0x07,
		AGC_DELAY2, 0xfe,
		/*
		 * Change the value of IAGCBW[15:8]
		 * of inner AGC loop filter bandwidth
		 */
		AGC_LOOP_BANDWIDTH0, 0x08,
		AGC_LOOP_BANDWIDTH1, 0x9a
	पूर्ण;
	अटल स्थिर u8 lgdt3303_init_data[] = अणु
		0x4c, 0x14
	पूर्ण;
	अटल स्थिर u8 flip_1_lgdt3303_init_data[] = अणु
		0x4c, 0x14,
		0x87, 0xf3
	पूर्ण;
	अटल स्थिर u8 flip_2_lgdt3303_init_data[] = अणु
		0x4c, 0x14,
		0x87, 0xda
	पूर्ण;

	/*
	 * Hardware reset is करोne using gpio[0] of cx23880x chip.
	 * I'd like to do it here, but don't know how to find chip address.
	 * cx88-cards.c arranges क्रम the reset bit to be inactive (high).
	 * Maybe there needs to be a callable function in cx88-core or
	 * the caller of this function needs to करो it.
	 */

	चयन (state->config.demod_chip) अणु
	हाल LGDT3302:
		chip_name = "LGDT3302";
		err = i2c_ग_लिखो_demod_bytes(state, lgdt3302_init_data,
					    माप(lgdt3302_init_data));
		अवरोध;
	हाल LGDT3303:
		chip_name = "LGDT3303";
		चयन (state->config.घड़ी_polarity_flip) अणु
		हाल 2:
			err = i2c_ग_लिखो_demod_bytes(state,
						    flip_2_lgdt3303_init_data,
						    माप(flip_2_lgdt3303_init_data));
			अवरोध;
		हाल 1:
			err = i2c_ग_लिखो_demod_bytes(state,
						    flip_1_lgdt3303_init_data,
						    माप(flip_1_lgdt3303_init_data));
			अवरोध;
		हाल 0:
		शेष:
			err = i2c_ग_लिखो_demod_bytes(state, lgdt3303_init_data,
						    माप(lgdt3303_init_data));
		पूर्ण
		अवरोध;
	शेष:
		chip_name = "undefined";
		dev_warn(&state->client->dev,
			 "Only LGDT3302 and LGDT3303 are supported chips.\n");
		err = -ENODEV;
	पूर्ण
	dprपूर्णांकk(state, "Initialized the %s chip\n", chip_name);
	अगर (err < 0)
		वापस err;

	p->cnr.len = 1;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_error.len = 1;
	p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_count.len = 1;
	p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	state->last_stats_समय = 0;

	वापस lgdt330x_sw_reset(state);
पूर्ण

अटल पूर्णांक lgdt330x_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;

	*ucblocks = state->ucblocks;

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt330x_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;
	/*
	 * Array of byte pairs <address, value>
	 * to initialize 8VSB क्रम lgdt3303 chip 50 MHz IF
	 */
	अटल स्थिर u8 lgdt3303_8vsb_44_data[] = अणु
		0x04, 0x00,
		0x0d, 0x40,
		0x0e, 0x87,
		0x0f, 0x8e,
		0x10, 0x01,
		0x47, 0x8b
	पूर्ण;
	/*
	 * Array of byte pairs <address, value>
	 * to initialize QAM क्रम lgdt3303 chip
	 */
	अटल स्थिर u8 lgdt3303_qam_data[] = अणु
		0x04, 0x00,
		0x0d, 0x00,
		0x0e, 0x00,
		0x0f, 0x00,
		0x10, 0x00,
		0x51, 0x63,
		0x47, 0x66,
		0x48, 0x66,
		0x4d, 0x1a,
		0x49, 0x08,
		0x4a, 0x9b
	पूर्ण;
	u8 top_ctrl_cfg[]   = अणु TOP_CONTROL, 0x03 पूर्ण;

	पूर्णांक err = 0;
	/* Change only अगर we are actually changing the modulation */
	अगर (state->current_modulation != p->modulation) अणु
		चयन (p->modulation) अणु
		हाल VSB_8:
			dprपूर्णांकk(state, "VSB_8 MODE\n");

			/* Select VSB mode */
			top_ctrl_cfg[1] = 0x03;

			/* Select ANT connector अगर supported by card */
			अगर (state->config.pll_rf_set)
				state->config.pll_rf_set(fe, 1);

			अगर (state->config.demod_chip == LGDT3303) अणु
				err = i2c_ग_लिखो_demod_bytes(state,
							    lgdt3303_8vsb_44_data,
							    माप(lgdt3303_8vsb_44_data));
			पूर्ण
			अवरोध;

		हाल QAM_64:
			dprपूर्णांकk(state, "QAM_64 MODE\n");

			/* Select QAM_64 mode */
			top_ctrl_cfg[1] = 0x00;

			/* Select CABLE connector अगर supported by card */
			अगर (state->config.pll_rf_set)
				state->config.pll_rf_set(fe, 0);

			अगर (state->config.demod_chip == LGDT3303) अणु
				err = i2c_ग_लिखो_demod_bytes(state,
							    lgdt3303_qam_data,
							    माप(lgdt3303_qam_data));
			पूर्ण
			अवरोध;

		हाल QAM_256:
			dprपूर्णांकk(state, "QAM_256 MODE\n");

			/* Select QAM_256 mode */
			top_ctrl_cfg[1] = 0x01;

			/* Select CABLE connector अगर supported by card */
			अगर (state->config.pll_rf_set)
				state->config.pll_rf_set(fe, 0);

			अगर (state->config.demod_chip == LGDT3303) अणु
				err = i2c_ग_लिखो_demod_bytes(state,
							    lgdt3303_qam_data,
							    माप(lgdt3303_qam_data));
			पूर्ण
			अवरोध;
		शेष:
			dev_warn(&state->client->dev,
				 "%s: Modulation type(%d) UNSUPPORTED\n",
				 __func__, p->modulation);
			वापस -1;
		पूर्ण
		अगर (err < 0)
			dev_warn(&state->client->dev,
				 "%s: error blasting bytes to lgdt3303 for modulation type(%d)\n",
				 __func__, p->modulation);

		/*
		 * select serial or parallel MPEG hardware पूर्णांकerface
		 * Serial:   0x04 क्रम LGDT3302 or 0x40 क्रम LGDT3303
		 * Parallel: 0x00
		 */
		top_ctrl_cfg[1] |= state->config.serial_mpeg;

		/* Select the requested mode */
		i2c_ग_लिखो_demod_bytes(state, top_ctrl_cfg,
				      माप(top_ctrl_cfg));
		अगर (state->config.set_ts_params)
			state->config.set_ts_params(fe, 0);
		state->current_modulation = p->modulation;
	पूर्ण

	/* Tune to the specअगरied frequency */
	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* Keep track of the new frequency */
	/*
	 * FIXME this is the wrong way to करो this...
	 * The tuner is shared with the video4linux analog API
	 */
	state->current_frequency = p->frequency;

	lgdt330x_sw_reset(state);
	वापस 0;
पूर्ण

अटल पूर्णांक lgdt330x_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;

	p->frequency = state->current_frequency;
	वापस 0;
पूर्ण

/*
 * Calculate SNR estimation (scaled by 2^24)
 *
 * 8-VSB SNR equations from LGDT3302 and LGDT3303 datasheets, QAM
 * equations from LGDT3303 datasheet.  VSB is the same between the '02
 * and '03, so maybe QAM is too?  Perhaps someone with a newer datasheet
 * that has QAM inक्रमmation could verअगरy?
 *
 * For 8-VSB: (two ways, take your pick)
 * LGDT3302:
 *   SNR_EQ = 10 * log10(25 * 24^2 / EQ_MSE)
 * LGDT3303:
 *   SNR_EQ = 10 * log10(25 * 32^2 / EQ_MSE)
 * LGDT3302 & LGDT3303:
 *   SNR_PT = 10 * log10(25 * 32^2 / PT_MSE)  (we use this one)
 * For 64-QAM:
 *   SNR    = 10 * log10( 688128   / MSEQAM)
 * For 256-QAM:
 *   SNR    = 10 * log10( 696320   / MSEQAM)
 *
 * We re-ग_लिखो the snr equation as:
 *   SNR * 2^24 = 10*(c - पूर्णांकlog10(MSE))
 * Where क्रम 256-QAM, c = log10(696320) * 2^24, and so on.
 */
अटल u32 calculate_snr(u32 mse, u32 c)
अणु
	अगर (mse == 0) /* No संकेत */
		वापस 0;

	mse = पूर्णांकlog10(mse);
	अगर (mse > c) अणु
		/*
		 * Negative SNR, which is possible, but realisticly the
		 * demod will lose lock beक्रमe the संकेत माला_लो this bad.
		 * The API only allows क्रम अचिन्हित values, so just वापस 0
		 */
		वापस 0;
	पूर्ण
	वापस 10 * (c - mse);
पूर्ण

अटल पूर्णांक lgdt3302_पढ़ो_snr(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;
	u8 buf[5];	/* पढ़ो data buffer */
	u32 noise;	/* noise value */
	u32 c;		/* per-modulation SNR calculation स्थिरant */

	चयन (state->current_modulation) अणु
	हाल VSB_8:
		i2c_पढ़ो_demod_bytes(state, LGDT3302_EQPH_ERR0, buf, 5);
#अगर_घोषित USE_EQMSE
		/* Use Equalizer Mean-Square Error Register */
		/* SNR क्रम ranges from -15.61 to +41.58 */
		noise = ((buf[0] & 7) << 16) | (buf[1] << 8) | buf[2];
		c = 69765745; /* log10(25*24^2)*2^24 */
#अन्यथा
		/* Use Phase Tracker Mean-Square Error Register */
		/* SNR क्रम ranges from -13.11 to +44.08 */
		noise = ((buf[0] & 7 << 3) << 13) | (buf[3] << 8) | buf[4];
		c = 73957994; /* log10(25*32^2)*2^24 */
#पूर्ण_अगर
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
		i2c_पढ़ो_demod_bytes(state, CARRIER_MSEQAM1, buf, 2);
		noise = ((buf[0] & 3) << 8) | buf[1];
		c = state->current_modulation == QAM_64 ? 97939837 : 98026066;
		/* log10(688128)*2^24 and log10(696320)*2^24 */
		अवरोध;
	शेष:
		dev_err(&state->client->dev,
			"%s: Modulation set to unsupported value\n",
			__func__);

		state->snr = 0;

		वापस -EREMOTEIO; /* वापस -EDRIVER_IS_GIBBERED; */
	पूर्ण

	state->snr = calculate_snr(noise, c);

	dprपूर्णांकk(state, "noise = 0x%08x, snr = %d.%02d dB\n", noise,
		state->snr >> 24, (((state->snr >> 8) & 0xffff) * 100) >> 16);

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3303_पढ़ो_snr(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;
	u8 buf[5];	/* पढ़ो data buffer */
	u32 noise;	/* noise value */
	u32 c;		/* per-modulation SNR calculation स्थिरant */

	चयन (state->current_modulation) अणु
	हाल VSB_8:
		i2c_पढ़ो_demod_bytes(state, LGDT3303_EQPH_ERR0, buf, 5);
#अगर_घोषित USE_EQMSE
		/* Use Equalizer Mean-Square Error Register */
		/* SNR क्रम ranges from -16.12 to +44.08 */
		noise = ((buf[0] & 0x78) << 13) | (buf[1] << 8) | buf[2];
		c = 73957994; /* log10(25*32^2)*2^24 */
#अन्यथा
		/* Use Phase Tracker Mean-Square Error Register */
		/* SNR क्रम ranges from -13.11 to +44.08 */
		noise = ((buf[0] & 7) << 16) | (buf[3] << 8) | buf[4];
		c = 73957994; /* log10(25*32^2)*2^24 */
#पूर्ण_अगर
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
		i2c_पढ़ो_demod_bytes(state, CARRIER_MSEQAM1, buf, 2);
		noise = (buf[0] << 8) | buf[1];
		c = state->current_modulation == QAM_64 ? 97939837 : 98026066;
		/* log10(688128)*2^24 and log10(696320)*2^24 */
		अवरोध;
	शेष:
		dev_err(&state->client->dev,
			"%s: Modulation set to unsupported value\n",
			__func__);
		state->snr = 0;
		वापस -EREMOTEIO; /* वापस -EDRIVER_IS_GIBBERED; */
	पूर्ण

	state->snr = calculate_snr(noise, c);

	dprपूर्णांकk(state, "noise = 0x%08x, snr = %d.%02d dB\n", noise,
		state->snr >> 24, (((state->snr >> 8) & 0xffff) * 100) >> 16);

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt330x_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;

	*snr = (state->snr) >> 16; /* Convert from 8.24 fixed-poपूर्णांक to 8.8 */

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt330x_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	/* Calculate Strength from SNR up to 35dB */
	/*
	 * Even though the SNR can go higher than 35dB, there is some comक्रमt
	 * factor in having a range of strong संकेतs that can show at 100%
	 */
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;
	u16 snr;
	पूर्णांक ret;

	ret = fe->ops.पढ़ो_snr(fe, &snr);
	अगर (ret != 0)
		वापस ret;
	/* Rather than use the 8.8 value snr, use state->snr which is 8.24 */
	/* scale the range 0 - 35*2^24 पूर्णांकo 0 - 65535 */
	अगर (state->snr >= 8960 * 0x10000)
		*strength = 0xffff;
	अन्यथा
		*strength = state->snr / 8960;

	वापस 0;
पूर्ण


अटल पूर्णांक lgdt3302_पढ़ो_status(काष्ठा dvb_frontend *fe,
				क्रमागत fe_status *status)
अणु
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u8 buf[3];
	पूर्णांक err;

	*status = 0; /* Reset status result */

	/* AGC status रेजिस्टर */
	i2c_पढ़ो_demod_bytes(state, AGC_STATUS, buf, 1);
	dprपूर्णांकk(state, "AGC_STATUS = 0x%02x\n", buf[0]);
	अगर ((buf[0] & 0x0c) == 0x8) अणु
		/*
		 * Test संकेत करोes not exist flag
		 * as well as the AGC lock flag.
		 */
		*status |= FE_HAS_SIGNAL;
	पूर्ण

	/*
	 * You must set the Mask bits to 1 in the IRQ_MASK in order
	 * to see that status bit in the IRQ_STATUS रेजिस्टर.
	 * This is करोne in SwReset();
	 */

	/* संकेत status */
	i2c_पढ़ो_demod_bytes(state, TOP_CONTROL, buf, माप(buf));
	dprपूर्णांकk(state,
		"TOP_CONTROL = 0x%02x, IRO_MASK = 0x%02x, IRQ_STATUS = 0x%02x\n",
		buf[0], buf[1], buf[2]);

	/* sync status */
	अगर ((buf[2] & 0x03) == 0x01)
		*status |= FE_HAS_SYNC;

	/* FEC error status */
	अगर ((buf[2] & 0x0c) == 0x08)
		*status |= FE_HAS_LOCK | FE_HAS_VITERBI;

	/* Carrier Recovery Lock Status Register */
	i2c_पढ़ो_demod_bytes(state, CARRIER_LOCK, buf, 1);
	dprपूर्णांकk(state, "CARRIER_LOCK = 0x%02x\n", buf[0]);
	चयन (state->current_modulation) अणु
	हाल QAM_256:
	हाल QAM_64:
		/* Need to understand why there are 3 lock levels here */
		अगर ((buf[0] & 0x07) == 0x07)
			*status |= FE_HAS_CARRIER;
		अवरोध;
	हाल VSB_8:
		अगर ((buf[0] & 0x80) == 0x80)
			*status |= FE_HAS_CARRIER;
		अवरोध;
	शेष:
		dev_warn(&state->client->dev,
			 "%s: Modulation set to unsupported value\n",
			 __func__);
	पूर्ण

	अगर (!(*status & FE_HAS_LOCK)) अणु
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस 0;
	पूर्ण

	अगर (state->last_stats_समय &&
	    समय_is_after_jअगरfies(state->last_stats_समय))
		वापस 0;

	state->last_stats_समय = jअगरfies + msecs_to_jअगरfies(1000);

	err = lgdt3302_पढ़ो_snr(fe);
	अगर (!err) अणु
		p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		p->cnr.stat[0].svalue = (((u64)state->snr) * 1000) >> 24;
	पूर्ण अन्यथा अणु
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	err = i2c_पढ़ो_demod_bytes(state, LGDT3302_PACKET_ERR_COUNTER1,
					   buf, माप(buf));
	अगर (!err) अणु
		state->ucblocks = (buf[0] << 8) | buf[1];

		dprपूर्णांकk(state, "UCB = 0x%02x\n", state->ucblocks);

		p->block_error.stat[0].uvalue += state->ucblocks;
		/* FIXME: what's the basis क्रम block count */
		p->block_count.stat[0].uvalue += 10000;

		p->block_error.stat[0].scale = FE_SCALE_COUNTER;
		p->block_count.stat[0].scale = FE_SCALE_COUNTER;
	पूर्ण अन्यथा अणु
		p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3303_पढ़ो_status(काष्ठा dvb_frontend *fe,
				क्रमागत fe_status *status)
अणु
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u8 buf[3];
	पूर्णांक err;

	*status = 0; /* Reset status result */

	/* lgdt3303 AGC status रेजिस्टर */
	err = i2c_पढ़ो_demod_bytes(state, 0x58, buf, 1);
	अगर (err < 0)
		वापस err;

	dprपूर्णांकk(state, "AGC_STATUS = 0x%02x\n", buf[0]);
	अगर ((buf[0] & 0x21) == 0x01) अणु
		/*
		 * Test input संकेत करोes not exist flag
		 * as well as the AGC lock flag.
		 */
		*status |= FE_HAS_SIGNAL;
	पूर्ण

	/* Carrier Recovery Lock Status Register */
	i2c_पढ़ो_demod_bytes(state, CARRIER_LOCK, buf, 1);
	dprपूर्णांकk(state, "CARRIER_LOCK = 0x%02x\n", buf[0]);
	चयन (state->current_modulation) अणु
	हाल QAM_256:
	हाल QAM_64:
		/* Need to understand why there are 3 lock levels here */
		अगर ((buf[0] & 0x07) == 0x07)
			*status |= FE_HAS_CARRIER;
		अन्यथा
			अवरोध;
		i2c_पढ़ो_demod_bytes(state, 0x8a, buf, 1);
		dprपूर्णांकk(state, "QAM LOCK = 0x%02x\n", buf[0]);

		अगर ((buf[0] & 0x04) == 0x04)
			*status |= FE_HAS_SYNC;
		अगर ((buf[0] & 0x01) == 0x01)
			*status |= FE_HAS_LOCK;
		अगर ((buf[0] & 0x08) == 0x08)
			*status |= FE_HAS_VITERBI;
		अवरोध;
	हाल VSB_8:
		अगर ((buf[0] & 0x80) == 0x80)
			*status |= FE_HAS_CARRIER;
		अन्यथा
			अवरोध;
		i2c_पढ़ो_demod_bytes(state, 0x38, buf, 1);
		dprपूर्णांकk(state, "8-VSB LOCK = 0x%02x\n", buf[0]);

		अगर ((buf[0] & 0x02) == 0x00)
			*status |= FE_HAS_SYNC;
		अगर ((buf[0] & 0x01) == 0x01)
			*status |= FE_HAS_VITERBI | FE_HAS_LOCK;
		अवरोध;
	शेष:
		dev_warn(&state->client->dev,
			 "%s: Modulation set to unsupported value\n",
			 __func__);
	पूर्ण

	अगर (!(*status & FE_HAS_LOCK)) अणु
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस 0;
	पूर्ण

	अगर (state->last_stats_समय &&
	    समय_is_after_jअगरfies(state->last_stats_समय))
		वापस 0;

	state->last_stats_समय = jअगरfies + msecs_to_jअगरfies(1000);

	err = lgdt3303_पढ़ो_snr(fe);
	अगर (!err) अणु
		p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		p->cnr.stat[0].svalue = (((u64)state->snr) * 1000) >> 24;
	पूर्ण अन्यथा अणु
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	err = i2c_पढ़ो_demod_bytes(state, LGDT3303_PACKET_ERR_COUNTER1,
					   buf, माप(buf));
	अगर (!err) अणु
		state->ucblocks = (buf[0] << 8) | buf[1];

		dprपूर्णांकk(state, "UCB = 0x%02x\n", state->ucblocks);

		p->block_error.stat[0].uvalue += state->ucblocks;
		/* FIXME: what's the basis क्रम block count */
		p->block_count.stat[0].uvalue += 10000;

		p->block_error.stat[0].scale = FE_SCALE_COUNTER;
		p->block_count.stat[0].scale = FE_SCALE_COUNTER;
	पूर्ण अन्यथा अणु
		p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
lgdt330x_get_tune_settings(काष्ठा dvb_frontend *fe,
			   काष्ठा dvb_frontend_tune_settings *fe_tune_settings)
अणु
	/* I have no idea about this - it may not be needed */
	fe_tune_settings->min_delay_ms = 500;
	fe_tune_settings->step_size = 0;
	fe_tune_settings->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल व्योम lgdt330x_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgdt330x_state *state = fe->demodulator_priv;
	काष्ठा i2c_client *client = state->client;

	dev_dbg(&client->dev, "\n");

	i2c_unरेजिस्टर_device(client);
पूर्ण

अटल काष्ठा dvb_frontend *lgdt330x_get_dvb_frontend(काष्ठा i2c_client *client)
अणु
	काष्ठा lgdt330x_state *state = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस &state->frontend;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops lgdt3302_ops;
अटल स्थिर काष्ठा dvb_frontend_ops lgdt3303_ops;

अटल पूर्णांक lgdt330x_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lgdt330x_state *state = शून्य;
	u8 buf[1];

	/* Allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		जाओ error;

	/* Setup the state */
	स_नकल(&state->config, client->dev.platक्रमm_data,
	       माप(state->config));
	i2c_set_clientdata(client, state);
	state->client = client;

	/* Create dvb_frontend */
	चयन (state->config.demod_chip) अणु
	हाल LGDT3302:
		स_नकल(&state->frontend.ops, &lgdt3302_ops,
		       माप(काष्ठा dvb_frontend_ops));
		अवरोध;
	हाल LGDT3303:
		स_नकल(&state->frontend.ops, &lgdt3303_ops,
		       माप(काष्ठा dvb_frontend_ops));
		अवरोध;
	शेष:
		जाओ error;
	पूर्ण
	state->frontend.demodulator_priv = state;

	/* Setup get frontend callback */
	state->config.get_dvb_frontend = lgdt330x_get_dvb_frontend;

	/* Verअगरy communication with demod chip */
	अगर (i2c_पढ़ो_demod_bytes(state, 2, buf, 1))
		जाओ error;

	state->current_frequency = -1;
	state->current_modulation = -1;

	dev_info(&state->client->dev,
		"Demod loaded for LGDT330%s chip\n",
		state->config.demod_chip == LGDT3302 ? "2" : "3");

	वापस 0;

error:
	kमुक्त(state);
	अगर (debug)
		dev_prपूर्णांकk(KERN_DEBUG, &client->dev, "Error loading lgdt330x driver\n");
	वापस -ENODEV;
पूर्ण
काष्ठा dvb_frontend *lgdt330x_attach(स्थिर काष्ठा lgdt330x_config *_config,
				     u8 demod_address,
				     काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info board_info = अणुपूर्ण;
	काष्ठा lgdt330x_config config = *_config;

	strscpy(board_info.type, "lgdt330x", माप(board_info.type));
	board_info.addr = demod_address;
	board_info.platक्रमm_data = &config;
	client = i2c_new_client_device(i2c, &board_info);
	अगर (!i2c_client_has_driver(client))
		वापस शून्य;

	वापस lgdt330x_get_dvb_frontend(client);
पूर्ण
EXPORT_SYMBOL(lgdt330x_attach);

अटल स्थिर काष्ठा dvb_frontend_ops lgdt3302_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name = "LG Electronics LGDT3302 VSB/QAM Frontend",
		.frequency_min_hz =  54 * MHz,
		.frequency_max_hz = 858 * MHz,
		.frequency_stepsize_hz = 62500,
		.symbol_rate_min    = 5056941,	/* QAM 64 */
		.symbol_rate_max    = 10762000,	/* VSB 8  */
		.caps = FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	पूर्ण,
	.init                 = lgdt330x_init,
	.set_frontend         = lgdt330x_set_parameters,
	.get_frontend         = lgdt330x_get_frontend,
	.get_tune_settings    = lgdt330x_get_tune_settings,
	.पढ़ो_status          = lgdt3302_पढ़ो_status,
	.पढ़ो_संकेत_strength = lgdt330x_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = lgdt330x_पढ़ो_snr,
	.पढ़ो_ucblocks        = lgdt330x_पढ़ो_ucblocks,
	.release              = lgdt330x_release,
पूर्ण;

अटल स्थिर काष्ठा dvb_frontend_ops lgdt3303_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name = "LG Electronics LGDT3303 VSB/QAM Frontend",
		.frequency_min_hz =  54 * MHz,
		.frequency_max_hz = 858 * MHz,
		.frequency_stepsize_hz = 62500,
		.symbol_rate_min    = 5056941,	/* QAM 64 */
		.symbol_rate_max    = 10762000,	/* VSB 8  */
		.caps = FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	पूर्ण,
	.init                 = lgdt330x_init,
	.set_frontend         = lgdt330x_set_parameters,
	.get_frontend         = lgdt330x_get_frontend,
	.get_tune_settings    = lgdt330x_get_tune_settings,
	.पढ़ो_status          = lgdt3303_पढ़ो_status,
	.पढ़ो_संकेत_strength = lgdt330x_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = lgdt330x_पढ़ो_snr,
	.पढ़ो_ucblocks        = lgdt330x_पढ़ो_ucblocks,
	.release              = lgdt330x_release,
पूर्ण;

अटल पूर्णांक lgdt330x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lgdt330x_state *state = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	kमुक्त(state);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lgdt330x_id_table[] = अणु
	अणु"lgdt330x", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lgdt330x_id_table);

अटल काष्ठा i2c_driver lgdt330x_driver = अणु
	.driver = अणु
		.name	= "lgdt330x",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= lgdt330x_probe,
	.हटाओ		= lgdt330x_हटाओ,
	.id_table	= lgdt330x_id_table,
पूर्ण;

module_i2c_driver(lgdt330x_driver);


MODULE_DESCRIPTION("LGDT330X (ATSC 8VSB & ITU-T J.83 AnnexB 64/256 QAM) Demodulator Driver");
MODULE_AUTHOR("Wilson Michaels");
MODULE_LICENSE("GPL");
