<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux-DVB Driver क्रम DiBcom's DiB0070 base-band RF Tuner.
 *
 * Copyright (C) 2005-9 DiBcom (http://www.dibcom.fr/)
 *
 * This code is more or less generated from another driver, please
 * excuse some codingstyle oddities.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>

#समावेश <media/dvb_frontend.h>

#समावेश "dib0070.h"
#समावेश "dibx000_common.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "turn on debugging (default: 0)");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

#घोषणा DIB0070_P1D  0x00
#घोषणा DIB0070_P1F  0x01
#घोषणा DIB0070_P1G  0x03
#घोषणा DIB0070S_P1A 0x02

काष्ठा dib0070_state अणु
	काष्ठा i2c_adapter *i2c;
	काष्ठा dvb_frontend *fe;
	स्थिर काष्ठा dib0070_config *cfg;
	u16 wbd_ff_offset;
	u8 revision;

	क्रमागत frontend_tune_state tune_state;
	u32 current_rf;

	/* क्रम the captrim binary search */
	s8 step;
	u16 adc_dअगरf;

	s8 captrim;
	s8 fcaptrim;
	u16 lo4;

	स्थिर काष्ठा dib0070_tuning *current_tune_table_index;
	स्थिर काष्ठा dib0070_lna_match *lna_match;

	u8  wbd_gain_current;
	u16 wbd_offset_3_3[2];

	/* क्रम the I2C transfer */
	काष्ठा i2c_msg msg[2];
	u8 i2c_ग_लिखो_buffer[3];
	u8 i2c_पढ़ो_buffer[2];
	काष्ठा mutex i2c_buffer_lock;
पूर्ण;

अटल u16 dib0070_पढ़ो_reg(काष्ठा dib0070_state *state, u8 reg)
अणु
	u16 ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस 0;
	पूर्ण

	state->i2c_ग_लिखो_buffer[0] = reg;

	स_रखो(state->msg, 0, 2 * माप(काष्ठा i2c_msg));
	state->msg[0].addr = state->cfg->i2c_address;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_ग_लिखो_buffer;
	state->msg[0].len = 1;
	state->msg[1].addr = state->cfg->i2c_address;
	state->msg[1].flags = I2C_M_RD;
	state->msg[1].buf = state->i2c_पढ़ो_buffer;
	state->msg[1].len = 2;

	अगर (i2c_transfer(state->i2c, state->msg, 2) != 2) अणु
		pr_warn("DiB0070 I2C read failed\n");
		ret = 0;
	पूर्ण अन्यथा
		ret = (state->i2c_पढ़ो_buffer[0] << 8)
			| state->i2c_पढ़ो_buffer[1];

	mutex_unlock(&state->i2c_buffer_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dib0070_ग_लिखो_reg(काष्ठा dib0070_state *state, u8 reg, u16 val)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस -EINVAL;
	पूर्ण
	state->i2c_ग_लिखो_buffer[0] = reg;
	state->i2c_ग_लिखो_buffer[1] = val >> 8;
	state->i2c_ग_लिखो_buffer[2] = val & 0xff;

	स_रखो(state->msg, 0, माप(काष्ठा i2c_msg));
	state->msg[0].addr = state->cfg->i2c_address;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_ग_लिखो_buffer;
	state->msg[0].len = 3;

	अगर (i2c_transfer(state->i2c, state->msg, 1) != 1) अणु
		pr_warn("DiB0070 I2C write failed\n");
		ret = -EREMOTEIO;
	पूर्ण अन्यथा
		ret = 0;

	mutex_unlock(&state->i2c_buffer_lock);
	वापस ret;
पूर्ण

#घोषणा HARD_RESET(state) करो अणु \
    state->cfg->sleep(state->fe, 0); \
    अगर (state->cfg->reset) अणु \
	state->cfg->reset(state->fe,1); msleep(10); \
	state->cfg->reset(state->fe,0); msleep(10); \
    पूर्ण \
पूर्ण जबतक (0)

अटल पूर्णांक dib0070_set_bandwidth(काष्ठा dvb_frontend *fe)
	अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;
	u16 पंचांगp = dib0070_पढ़ो_reg(state, 0x02) & 0x3fff;

	अगर (state->fe->dtv_property_cache.bandwidth_hz/1000 > 7000)
		पंचांगp |= (0 << 14);
	अन्यथा अगर (state->fe->dtv_property_cache.bandwidth_hz/1000 > 6000)
		पंचांगp |= (1 << 14);
	अन्यथा अगर (state->fe->dtv_property_cache.bandwidth_hz/1000 > 5000)
		पंचांगp |= (2 << 14);
	अन्यथा
		पंचांगp |= (3 << 14);

	dib0070_ग_लिखो_reg(state, 0x02, पंचांगp);

	/* sharpen the BB filter in ISDB-T to have higher immunity to adjacent channels */
	अगर (state->fe->dtv_property_cache.delivery_प्रणाली == SYS_ISDBT) अणु
		u16 value = dib0070_पढ़ो_reg(state, 0x17);

		dib0070_ग_लिखो_reg(state, 0x17, value & 0xfffc);
		पंचांगp = dib0070_पढ़ो_reg(state, 0x01) & 0x01ff;
		dib0070_ग_लिखो_reg(state, 0x01, पंचांगp | (60 << 9));

		dib0070_ग_लिखो_reg(state, 0x17, value);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib0070_captrim(काष्ठा dib0070_state *state, क्रमागत frontend_tune_state *tune_state)
अणु
	पूर्णांक8_t step_sign;
	u16 adc;
	पूर्णांक ret = 0;

	अगर (*tune_state == CT_TUNER_STEP_0) अणु
		dib0070_ग_लिखो_reg(state, 0x0f, 0xed10);
		dib0070_ग_लिखो_reg(state, 0x17,    0x0034);

		dib0070_ग_लिखो_reg(state, 0x18, 0x0032);
		state->step = state->captrim = state->fcaptrim = 64;
		state->adc_dअगरf = 3000;
		ret = 20;

		*tune_state = CT_TUNER_STEP_1;
	पूर्ण अन्यथा अगर (*tune_state == CT_TUNER_STEP_1) अणु
		state->step /= 2;
		dib0070_ग_लिखो_reg(state, 0x14, state->lo4 | state->captrim);
		ret = 15;

		*tune_state = CT_TUNER_STEP_2;
	पूर्ण अन्यथा अगर (*tune_state == CT_TUNER_STEP_2) अणु

		adc = dib0070_पढ़ो_reg(state, 0x19);

		dprपूर्णांकk("CAPTRIM=%d; ADC = %hd (ADC) & %dmV\n", state->captrim,
			adc, (u32)adc * (u32)1800 / (u32)1024);

		अगर (adc >= 400) अणु
			adc -= 400;
			step_sign = -1;
		पूर्ण अन्यथा अणु
			adc = 400 - adc;
			step_sign = 1;
		पूर्ण

		अगर (adc < state->adc_dअगरf) अणु
			dprपूर्णांकk("CAPTRIM=%d is closer to target (%hd/%hd)\n",
				state->captrim, adc, state->adc_dअगरf);
			state->adc_dअगरf = adc;
			state->fcaptrim = state->captrim;
		पूर्ण
		state->captrim += (step_sign * state->step);

		अगर (state->step >= 1)
			*tune_state = CT_TUNER_STEP_1;
		अन्यथा
			*tune_state = CT_TUNER_STEP_3;

	पूर्ण अन्यथा अगर (*tune_state == CT_TUNER_STEP_3) अणु
		dib0070_ग_लिखो_reg(state, 0x14, state->lo4 | state->fcaptrim);
		dib0070_ग_लिखो_reg(state, 0x18, 0x07ff);
		*tune_state = CT_TUNER_STEP_4;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dib0070_set_ctrl_lo5(काष्ठा dvb_frontend *fe, u8 vco_bias_trim, u8 hf_भाग_प्रकारrim, u8 cp_current, u8 third_order_filt)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;
	u16 lo5 = (third_order_filt << 14) | (0 << 13) | (1 << 12) | (3 << 9) | (cp_current << 6) | (hf_भाग_प्रकारrim << 3) | (vco_bias_trim << 0);

	dprपूर्णांकk("CTRL_LO5: 0x%x\n", lo5);
	वापस dib0070_ग_लिखो_reg(state, 0x15, lo5);
पूर्ण

व्योम dib0070_ctrl_agc_filter(काष्ठा dvb_frontend *fe, u8 खोलो)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;

	अगर (खोलो) अणु
		dib0070_ग_लिखो_reg(state, 0x1b, 0xff00);
		dib0070_ग_लिखो_reg(state, 0x1a, 0x0000);
	पूर्ण अन्यथा अणु
		dib0070_ग_लिखो_reg(state, 0x1b, 0x4112);
		अगर (state->cfg->vga_filter != 0) अणु
			dib0070_ग_लिखो_reg(state, 0x1a, state->cfg->vga_filter);
			dprपूर्णांकk("vga filter register is set to %x\n", state->cfg->vga_filter);
		पूर्ण अन्यथा
			dib0070_ग_लिखो_reg(state, 0x1a, 0x0009);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(dib0070_ctrl_agc_filter);
काष्ठा dib0070_tuning अणु
	u32 max_freq; /* क्रम every frequency less than or equal to that field: this inक्रमmation is correct */
	u8 चयन_trim;
	u8 vco_band;
	u8 hfभाग;
	u8 vco_multi;
	u8 presc;
	u8 wbdmux;
	u16 tuner_enable;
पूर्ण;

काष्ठा dib0070_lna_match अणु
	u32 max_freq; /* क्रम every frequency less than or equal to that field: this inक्रमmation is correct */
	u8 lna_band;
पूर्ण;

अटल स्थिर काष्ठा dib0070_tuning dib0070s_tuning_table[] = अणु
	अणु     570000, 2, 1, 3, 6, 6, 2, 0x4000 | 0x0800 पूर्ण, /* UHF */
	अणु     700000, 2, 0, 2, 4, 2, 2, 0x4000 | 0x0800 पूर्ण,
	अणु     863999, 2, 1, 2, 4, 2, 2, 0x4000 | 0x0800 पूर्ण,
	अणु    1500000, 0, 1, 1, 2, 2, 4, 0x2000 | 0x0400 पूर्ण, /* LBAND */
	अणु    1600000, 0, 1, 1, 2, 2, 4, 0x2000 | 0x0400 पूर्ण,
	अणु    2000000, 0, 1, 1, 2, 2, 4, 0x2000 | 0x0400 पूर्ण,
	अणु 0xffffffff, 0, 0, 8, 1, 2, 1, 0x8000 | 0x1000 पूर्ण, /* SBAND */
पूर्ण;

अटल स्थिर काष्ठा dib0070_tuning dib0070_tuning_table[] = अणु
	अणु     115000, 1, 0, 7, 24, 2, 1, 0x8000 | 0x1000 पूर्ण, /* FM below 92MHz cannot be tuned */
	अणु     179500, 1, 0, 3, 16, 2, 1, 0x8000 | 0x1000 पूर्ण, /* VHF */
	अणु     189999, 1, 1, 3, 16, 2, 1, 0x8000 | 0x1000 पूर्ण,
	अणु     250000, 1, 0, 6, 12, 2, 1, 0x8000 | 0x1000 पूर्ण,
	अणु     569999, 2, 1, 5,  6, 2, 2, 0x4000 | 0x0800 पूर्ण, /* UHF */
	अणु     699999, 2, 0, 1,  4, 2, 2, 0x4000 | 0x0800 पूर्ण,
	अणु     863999, 2, 1, 1,  4, 2, 2, 0x4000 | 0x0800 पूर्ण,
	अणु 0xffffffff, 0, 1, 0,  2, 2, 4, 0x2000 | 0x0400 पूर्ण, /* LBAND or everything higher than UHF */
पूर्ण;

अटल स्थिर काष्ठा dib0070_lna_match dib0070_lna_flip_chip[] = अणु
	अणु     180000, 0 पूर्ण, /* VHF */
	अणु     188000, 1 पूर्ण,
	अणु     196400, 2 पूर्ण,
	अणु     250000, 3 पूर्ण,
	अणु     550000, 0 पूर्ण, /* UHF */
	अणु     590000, 1 पूर्ण,
	अणु     666000, 3 पूर्ण,
	अणु     864000, 5 पूर्ण,
	अणु    1500000, 0 पूर्ण, /* LBAND or everything higher than UHF */
	अणु    1600000, 1 पूर्ण,
	अणु    2000000, 3 पूर्ण,
	अणु 0xffffffff, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dib0070_lna_match dib0070_lna[] = अणु
	अणु     180000, 0 पूर्ण, /* VHF */
	अणु     188000, 1 पूर्ण,
	अणु     196400, 2 पूर्ण,
	अणु     250000, 3 पूर्ण,
	अणु     550000, 2 पूर्ण, /* UHF */
	अणु     650000, 3 पूर्ण,
	अणु     750000, 5 पूर्ण,
	अणु     850000, 6 पूर्ण,
	अणु     864000, 7 पूर्ण,
	अणु    1500000, 0 पूर्ण, /* LBAND or everything higher than UHF */
	अणु    1600000, 1 पूर्ण,
	अणु    2000000, 3 पूर्ण,
	अणु 0xffffffff, 7 पूर्ण,
पूर्ण;

#घोषणा LPF	100
अटल पूर्णांक dib0070_tune_digital(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;

	स्थिर काष्ठा dib0070_tuning *tune;
	स्थिर काष्ठा dib0070_lna_match *lna_match;

	क्रमागत frontend_tune_state *tune_state = &state->tune_state;
	पूर्णांक ret = 10; /* 1ms is the शेष delay most of the समय */

	u8  band = (u8)BAND_OF_FREQUENCY(fe->dtv_property_cache.frequency/1000);
	u32 freq = fe->dtv_property_cache.frequency/1000 + (band == BAND_VHF ? state->cfg->freq_offset_khz_vhf : state->cfg->freq_offset_khz_uhf);

#अगर_घोषित CONFIG_SYS_ISDBT
	अगर (state->fe->dtv_property_cache.delivery_प्रणाली == SYS_ISDBT && state->fe->dtv_property_cache.isdbt_sb_mode == 1)
			अगर (((state->fe->dtv_property_cache.isdbt_sb_segment_count % 2)
			&& (state->fe->dtv_property_cache.isdbt_sb_segment_idx == ((state->fe->dtv_property_cache.isdbt_sb_segment_count / 2) + 1)))
			|| (((state->fe->dtv_property_cache.isdbt_sb_segment_count % 2) == 0)
				&& (state->fe->dtv_property_cache.isdbt_sb_segment_idx == (state->fe->dtv_property_cache.isdbt_sb_segment_count / 2)))
			|| (((state->fe->dtv_property_cache.isdbt_sb_segment_count % 2) == 0)
				&& (state->fe->dtv_property_cache.isdbt_sb_segment_idx == ((state->fe->dtv_property_cache.isdbt_sb_segment_count / 2) + 1))))
				freq += 850;
#पूर्ण_अगर
	अगर (state->current_rf != freq) अणु

		चयन (state->revision) अणु
		हाल DIB0070S_P1A:
		tune = dib0070s_tuning_table;
		lna_match = dib0070_lna;
		अवरोध;
		शेष:
		tune = dib0070_tuning_table;
		अगर (state->cfg->flip_chip)
			lna_match = dib0070_lna_flip_chip;
		अन्यथा
			lna_match = dib0070_lna;
		अवरोध;
		पूर्ण
		जबतक (freq > tune->max_freq) /* find the right one */
			tune++;
		जबतक (freq > lna_match->max_freq) /* find the right one */
			lna_match++;

		state->current_tune_table_index = tune;
		state->lna_match = lna_match;
	पूर्ण

	अगर (*tune_state == CT_TUNER_START) अणु
		dprपूर्णांकk("Tuning for Band: %d (%d kHz)\n", band, freq);
		अगर (state->current_rf != freq) अणु
			u8 REFDIV;
			u32 FBDiv, Rest, FREF, VCOF_kHz;
			u8 Den;

			state->current_rf = freq;
			state->lo4 = (state->current_tune_table_index->vco_band << 11) | (state->current_tune_table_index->hfभाग << 7);


			dib0070_ग_लिखो_reg(state, 0x17, 0x30);


			VCOF_kHz = state->current_tune_table_index->vco_multi * freq * 2;

			चयन (band) अणु
			हाल BAND_VHF:
				REFDIV = (u8) ((state->cfg->घड़ी_khz + 9999) / 10000);
				अवरोध;
			हाल BAND_FM:
				REFDIV = (u8) ((state->cfg->घड़ी_khz) / 1000);
				अवरोध;
			शेष:
				REFDIV = (u8) (state->cfg->घड़ी_khz  / 10000);
				अवरोध;
			पूर्ण
			FREF = state->cfg->घड़ी_khz / REFDIV;



			चयन (state->revision) अणु
			हाल DIB0070S_P1A:
				FBDiv = (VCOF_kHz / state->current_tune_table_index->presc / FREF);
				Rest  = (VCOF_kHz / state->current_tune_table_index->presc) - FBDiv * FREF;
				अवरोध;

			हाल DIB0070_P1G:
			हाल DIB0070_P1F:
			शेष:
				FBDiv = (freq / (FREF / 2));
				Rest  = 2 * freq - FBDiv * FREF;
				अवरोध;
			पूर्ण

			अगर (Rest < LPF)
				Rest = 0;
			अन्यथा अगर (Rest < 2 * LPF)
				Rest = 2 * LPF;
			अन्यथा अगर (Rest > (FREF - LPF)) अणु
				Rest = 0;
				FBDiv += 1;
			पूर्ण अन्यथा अगर (Rest > (FREF - 2 * LPF))
				Rest = FREF - 2 * LPF;
			Rest = (Rest * 6528) / (FREF / 10);

			Den = 1;
			अगर (Rest > 0) अणु
				state->lo4 |= (1 << 14) | (1 << 12);
				Den = 255;
			पूर्ण


			dib0070_ग_लिखो_reg(state, 0x11, (u16)FBDiv);
			dib0070_ग_लिखो_reg(state, 0x12, (Den << 8) | REFDIV);
			dib0070_ग_लिखो_reg(state, 0x13, (u16) Rest);

			अगर (state->revision == DIB0070S_P1A) अणु

				अगर (band == BAND_SBAND) अणु
					dib0070_set_ctrl_lo5(fe, 2, 4, 3, 0);
					dib0070_ग_लिखो_reg(state, 0x1d, 0xFFFF);
				पूर्ण अन्यथा
					dib0070_set_ctrl_lo5(fe, 5, 4, 3, 1);
			पूर्ण

			dib0070_ग_लिखो_reg(state, 0x20,
				0x0040 | 0x0020 | 0x0010 | 0x0008 | 0x0002 | 0x0001 | state->current_tune_table_index->tuner_enable);

			dprपूर्णांकk("REFDIV: %u, FREF: %d\n", REFDIV, FREF);
			dprपूर्णांकk("FBDIV: %d, Rest: %d\n", FBDiv, Rest);
			dprपूर्णांकk("Num: %u, Den: %u, SD: %d\n", (u16)Rest, Den,
				(state->lo4 >> 12) & 0x1);
			dprपूर्णांकk("HFDIV code: %u\n",
				state->current_tune_table_index->hfभाग);
			dprपूर्णांकk("VCO = %u\n",
				state->current_tune_table_index->vco_band);
			dprपूर्णांकk("VCOF: ((%u*%d) << 1))\n",
				state->current_tune_table_index->vco_multi,
				freq);

			*tune_state = CT_TUNER_STEP_0;
		पूर्ण अन्यथा अणु /* we are alपढ़ोy tuned to this frequency - the configuration is correct  */
			ret = 50; /* wakeup समय */
			*tune_state = CT_TUNER_STEP_5;
		पूर्ण
	पूर्ण अन्यथा अगर ((*tune_state > CT_TUNER_START) && (*tune_state < CT_TUNER_STEP_4)) अणु

		ret = dib0070_captrim(state, tune_state);

	पूर्ण अन्यथा अगर (*tune_state == CT_TUNER_STEP_4) अणु
		स्थिर काष्ठा dib0070_wbd_gain_cfg *पंचांगp = state->cfg->wbd_gain;
		अगर (पंचांगp != शून्य) अणु
			जबतक (freq/1000 > पंचांगp->freq) /* find the right one */
				पंचांगp++;
			dib0070_ग_लिखो_reg(state, 0x0f,
				(0 << 15) | (1 << 14) | (3 << 12)
				| (पंचांगp->wbd_gain_val << 9) | (0 << 8) | (1 << 7)
				| (state->current_tune_table_index->wbdmux << 0));
			state->wbd_gain_current = पंचांगp->wbd_gain_val;
		पूर्ण अन्यथा अणु
			dib0070_ग_लिखो_reg(state, 0x0f,
					  (0 << 15) | (1 << 14) | (3 << 12)
					  | (6 << 9) | (0 << 8) | (1 << 7)
					  | (state->current_tune_table_index->wbdmux << 0));
			state->wbd_gain_current = 6;
		पूर्ण

		dib0070_ग_लिखो_reg(state, 0x06, 0x3fff);
		dib0070_ग_लिखो_reg(state, 0x07,
				  (state->current_tune_table_index->चयन_trim << 11) | (7 << 8) | (state->lna_match->lna_band << 3) | (3 << 0));
		dib0070_ग_लिखो_reg(state, 0x08, (state->lna_match->lna_band << 10) | (3 << 7) | (127));
		dib0070_ग_लिखो_reg(state, 0x0d, 0x0d80);


		dib0070_ग_लिखो_reg(state, 0x18,   0x07ff);
		dib0070_ग_लिखो_reg(state, 0x17, 0x0033);


		*tune_state = CT_TUNER_STEP_5;
	पूर्ण अन्यथा अगर (*tune_state == CT_TUNER_STEP_5) अणु
		dib0070_set_bandwidth(fe);
		*tune_state = CT_TUNER_STOP;
	पूर्ण अन्यथा अणु
		ret = FE_CALLBACK_TIME_NEVER; /* tuner finished, समय to call again infinite */
	पूर्ण
	वापस ret;
पूर्ण


अटल पूर्णांक dib0070_tune(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;
	uपूर्णांक32_t ret;

	state->tune_state = CT_TUNER_START;

	करो अणु
		ret = dib0070_tune_digital(fe);
		अगर (ret != FE_CALLBACK_TIME_NEVER)
			msleep(ret/10);
		अन्यथा
		अवरोध;
	पूर्ण जबतक (state->tune_state != CT_TUNER_STOP);

	वापस 0;
पूर्ण

अटल पूर्णांक dib0070_wakeup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;
	अगर (state->cfg->sleep)
		state->cfg->sleep(fe, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक dib0070_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;
	अगर (state->cfg->sleep)
		state->cfg->sleep(fe, 1);
	वापस 0;
पूर्ण

u8 dib0070_get_rf_output(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;
	वापस (dib0070_पढ़ो_reg(state, 0x07) >> 11) & 0x3;
पूर्ण
EXPORT_SYMBOL(dib0070_get_rf_output);

पूर्णांक dib0070_set_rf_output(काष्ठा dvb_frontend *fe, u8 no)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;
	u16 rxrf2 = dib0070_पढ़ो_reg(state, 0x07) & 0xfe7ff;
	अगर (no > 3)
		no = 3;
	अगर (no < 1)
		no = 1;
	वापस dib0070_ग_लिखो_reg(state, 0x07, rxrf2 | (no << 11));
पूर्ण
EXPORT_SYMBOL(dib0070_set_rf_output);

अटल स्थिर u16 dib0070_p1f_शेषs[] =

अणु
	7, 0x02,
		0x0008,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0002,
		0x0100,

	3, 0x0d,
		0x0d80,
		0x0001,
		0x0000,

	4, 0x11,
		0x0000,
		0x0103,
		0x0000,
		0x0000,

	3, 0x16,
		0x0004 | 0x0040,
		0x0030,
		0x07ff,

	6, 0x1b,
		0x4112,
		0xff00,
		0xc07f,
		0x0000,
		0x0180,
		0x4000 | 0x0800 | 0x0040 | 0x0020 | 0x0010 | 0x0008 | 0x0002 | 0x0001,

	0,
पूर्ण;

अटल u16 dib0070_पढ़ो_wbd_offset(काष्ठा dib0070_state *state, u8 gain)
अणु
	u16 tuner_en = dib0070_पढ़ो_reg(state, 0x20);
	u16 offset;

	dib0070_ग_लिखो_reg(state, 0x18, 0x07ff);
	dib0070_ग_लिखो_reg(state, 0x20, 0x0800 | 0x4000 | 0x0040 | 0x0020 | 0x0010 | 0x0008 | 0x0002 | 0x0001);
	dib0070_ग_लिखो_reg(state, 0x0f, (1 << 14) | (2 << 12) | (gain << 9) | (1 << 8) | (1 << 7) | (0 << 0));
	msleep(9);
	offset = dib0070_पढ़ो_reg(state, 0x19);
	dib0070_ग_लिखो_reg(state, 0x20, tuner_en);
	वापस offset;
पूर्ण

अटल व्योम dib0070_wbd_offset_calibration(काष्ठा dib0070_state *state)
अणु
	u8 gain;
	क्रम (gain = 6; gain < 8; gain++) अणु
		state->wbd_offset_3_3[gain - 6] = ((dib0070_पढ़ो_wbd_offset(state, gain) * 8 * 18 / 33 + 1) / 2);
		dprपूर्णांकk("Gain: %d, WBDOffset (3.3V) = %hd\n", gain, state->wbd_offset_3_3[gain-6]);
	पूर्ण
पूर्ण

u16 dib0070_wbd_offset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;
	स्थिर काष्ठा dib0070_wbd_gain_cfg *पंचांगp = state->cfg->wbd_gain;
	u32 freq = fe->dtv_property_cache.frequency/1000;

	अगर (पंचांगp != शून्य) अणु
		जबतक (freq/1000 > पंचांगp->freq) /* find the right one */
			पंचांगp++;
		state->wbd_gain_current = पंचांगp->wbd_gain_val;
	पूर्ण अन्यथा
		state->wbd_gain_current = 6;

	वापस state->wbd_offset_3_3[state->wbd_gain_current - 6];
पूर्ण
EXPORT_SYMBOL(dib0070_wbd_offset);

#घोषणा pgm_पढ़ो_word(w) (*w)
अटल पूर्णांक dib0070_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;
	u16 l, r, *n;

	HARD_RESET(state);


#अगर_अघोषित FORCE_SBAND_TUNER
	अगर ((dib0070_पढ़ो_reg(state, 0x22) >> 9) & 0x1)
		state->revision = (dib0070_पढ़ो_reg(state, 0x1f) >> 8) & 0xff;
	अन्यथा
#अन्यथा
#warning क्रमcing SBAND
#पूर्ण_अगर
	state->revision = DIB0070S_P1A;

	/* P1F or not */
	dprपूर्णांकk("Revision: %x\n", state->revision);

	अगर (state->revision == DIB0070_P1D) अणु
		dprपूर्णांकk("Error: this driver is not to be used meant for P1D or earlier\n");
		वापस -EINVAL;
	पूर्ण

	n = (u16 *) dib0070_p1f_शेषs;
	l = pgm_पढ़ो_word(n++);
	जबतक (l) अणु
		r = pgm_पढ़ो_word(n++);
		करो अणु
			dib0070_ग_लिखो_reg(state, (u8)r, pgm_पढ़ो_word(n++));
			r++;
		पूर्ण जबतक (--l);
		l = pgm_पढ़ो_word(n++);
	पूर्ण

	अगर (state->cfg->क्रमce_crystal_mode != 0)
		r = state->cfg->क्रमce_crystal_mode;
	अन्यथा अगर (state->cfg->घड़ी_khz >= 24000)
		r = 1;
	अन्यथा
		r = 2;


	r |= state->cfg->osc_buffer_state << 3;

	dib0070_ग_लिखो_reg(state, 0x10, r);
	dib0070_ग_लिखो_reg(state, 0x1f, (1 << 8) | ((state->cfg->घड़ी_pad_drive & 0xf) << 5));

	अगर (state->cfg->invert_iq) अणु
		r = dib0070_पढ़ो_reg(state, 0x02) & 0xffdf;
		dib0070_ग_लिखो_reg(state, 0x02, r | (1 << 5));
	पूर्ण

	अगर (state->revision == DIB0070S_P1A)
		dib0070_set_ctrl_lo5(fe, 2, 4, 3, 0);
	अन्यथा
		dib0070_set_ctrl_lo5(fe, 5, 4, state->cfg->अक्षरge_pump,
				     state->cfg->enable_third_order_filter);

	dib0070_ग_लिखो_reg(state, 0x01, (54 << 9) | 0xc8);

	dib0070_wbd_offset_calibration(state);

	वापस 0;
पूर्ण

अटल पूर्णांक dib0070_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा dib0070_state *state = fe->tuner_priv;

	*frequency = 1000 * state->current_rf;
	वापस 0;
पूर्ण

अटल व्योम dib0070_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops dib0070_ops = अणु
	.info = अणु
		.name              = "DiBcom DiB0070",
		.frequency_min_hz  =  45 * MHz,
		.frequency_max_hz  = 860 * MHz,
		.frequency_step_hz =   1 * kHz,
	पूर्ण,
	.release       = dib0070_release,

	.init          = dib0070_wakeup,
	.sleep         = dib0070_sleep,
	.set_params    = dib0070_tune,

	.get_frequency = dib0070_get_frequency,
//      .get_bandwidth = dib0070_get_bandwidth
पूर्ण;

काष्ठा dvb_frontend *dib0070_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा dib0070_config *cfg)
अणु
	काष्ठा dib0070_state *state = kzalloc(माप(काष्ठा dib0070_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	state->cfg = cfg;
	state->i2c = i2c;
	state->fe  = fe;
	mutex_init(&state->i2c_buffer_lock);
	fe->tuner_priv = state;

	अगर (dib0070_reset(fe) != 0)
		जाओ मुक्त_mem;

	pr_info("DiB0070: successfully identified\n");
	स_नकल(&fe->ops.tuner_ops, &dib0070_ops, माप(काष्ठा dvb_tuner_ops));

	fe->tuner_priv = state;
	वापस fe;

मुक्त_mem:
	kमुक्त(state);
	fe->tuner_priv = शून्य;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dib0070_attach);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for the DiBcom 0070 base-band RF Tuner");
MODULE_LICENSE("GPL");
