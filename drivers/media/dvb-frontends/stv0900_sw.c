<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * stv0900_sw.c
 *
 * Driver क्रम ST STV0900 satellite demodulator IC.
 *
 * Copyright (C) ST Microelectronics.
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 */

#समावेश "stv0900.h"
#समावेश "stv0900_reg.h"
#समावेश "stv0900_priv.h"

s32 shअगरtx(s32 x, पूर्णांक demod, s32 shअगरt)
अणु
	अगर (demod == 1)
		वापस x - shअगरt;

	वापस x;
पूर्ण

पूर्णांक stv0900_check_संकेत_presence(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	s32	carr_offset,
		agc2_पूर्णांकegr,
		max_carrier;

	पूर्णांक no_संकेत = FALSE;

	carr_offset = (stv0900_पढ़ो_reg(पूर्णांकp, CFR2) << 8)
					| stv0900_पढ़ो_reg(पूर्णांकp, CFR1);
	carr_offset = ge2comp(carr_offset, 16);
	agc2_पूर्णांकegr = (stv0900_पढ़ो_reg(पूर्णांकp, AGC2I1) << 8)
					| stv0900_पढ़ो_reg(पूर्णांकp, AGC2I0);
	max_carrier = पूर्णांकp->srch_range[demod] / 1000;

	max_carrier += (max_carrier / 10);
	max_carrier = 65536 * (max_carrier / 2);
	max_carrier /= पूर्णांकp->mclk / 1000;
	अगर (max_carrier > 0x4000)
		max_carrier = 0x4000;

	अगर ((agc2_पूर्णांकegr > 0x2000)
			|| (carr_offset > (2 * max_carrier))
			|| (carr_offset < (-2 * max_carrier)))
		no_संकेत = TRUE;

	वापस no_संकेत;
पूर्ण

अटल व्योम stv0900_get_sw_loop_params(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				s32 *frequency_inc, s32 *sw_समयout,
				s32 *steps,
				क्रमागत fe_stv0900_demod_num demod)
अणु
	s32 समयout, freq_inc, max_steps, srate, max_carrier;

	क्रमागत fe_stv0900_search_standard	standard;

	srate = पूर्णांकp->symbol_rate[demod];
	max_carrier = पूर्णांकp->srch_range[demod] / 1000;
	max_carrier += max_carrier / 10;
	standard = पूर्णांकp->srch_standard[demod];

	max_carrier = 65536 * (max_carrier / 2);
	max_carrier /= पूर्णांकp->mclk / 1000;

	अगर (max_carrier > 0x4000)
		max_carrier = 0x4000;

	freq_inc = srate;
	freq_inc /= पूर्णांकp->mclk >> 10;
	freq_inc = freq_inc << 6;

	चयन (standard) अणु
	हाल STV0900_SEARCH_DVBS1:
	हाल STV0900_SEARCH_DSS:
		freq_inc *= 3;
		समयout = 20;
		अवरोध;
	हाल STV0900_SEARCH_DVBS2:
		freq_inc *= 4;
		समयout = 25;
		अवरोध;
	हाल STV0900_AUTO_SEARCH:
	शेष:
		freq_inc *= 3;
		समयout = 25;
		अवरोध;
	पूर्ण

	freq_inc /= 100;

	अगर ((freq_inc > max_carrier) || (freq_inc < 0))
		freq_inc = max_carrier / 2;

	समयout *= 27500;

	अगर (srate > 0)
		समयout /= srate / 1000;

	अगर ((समयout > 100) || (समयout < 0))
		समयout = 100;

	max_steps = (max_carrier / freq_inc) + 1;

	अगर ((max_steps > 100) || (max_steps < 0)) अणु
		max_steps =  100;
		freq_inc = max_carrier / max_steps;
	पूर्ण

	*frequency_inc = freq_inc;
	*sw_समयout = समयout;
	*steps = max_steps;

पूर्ण

अटल पूर्णांक stv0900_search_carr_sw_loop(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				s32 FreqIncr, s32 Timeout, पूर्णांक zigzag,
				s32 MaxStep, क्रमागत fe_stv0900_demod_num demod)
अणु
	पूर्णांक	no_संकेत,
		lock = FALSE;
	s32	stepCpt,
		freqOffset,
		max_carrier;

	max_carrier = पूर्णांकp->srch_range[demod] / 1000;
	max_carrier += (max_carrier / 10);

	max_carrier = 65536 * (max_carrier / 2);
	max_carrier /= पूर्णांकp->mclk / 1000;

	अगर (max_carrier > 0x4000)
		max_carrier = 0x4000;

	अगर (zigzag == TRUE)
		freqOffset = 0;
	अन्यथा
		freqOffset = -max_carrier + FreqIncr;

	stepCpt = 0;

	करो अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1c);
		stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, (freqOffset / 256) & 0xff);
		stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, freqOffset & 0xff);
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x18);
		stv0900_ग_लिखो_bits(पूर्णांकp, ALGOSWRST, 1);

		अगर (पूर्णांकp->chip_id == 0x12) अणु
			stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 1);
			stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 0);
		पूर्ण

		अगर (zigzag == TRUE) अणु
			अगर (freqOffset >= 0)
				freqOffset = -freqOffset - 2 * FreqIncr;
			अन्यथा
				freqOffset = -freqOffset;
		पूर्ण अन्यथा
			freqOffset += + 2 * FreqIncr;

		stepCpt++;
		lock = stv0900_get_demod_lock(पूर्णांकp, demod, Timeout);
		no_संकेत = stv0900_check_संकेत_presence(पूर्णांकp, demod);

	पूर्ण जबतक ((lock == FALSE)
			&& (no_संकेत == FALSE)
			&& ((freqOffset - FreqIncr) <  max_carrier)
			&& ((freqOffset + FreqIncr) > -max_carrier)
			&& (stepCpt < MaxStep));

	stv0900_ग_लिखो_bits(पूर्णांकp, ALGOSWRST, 0);

	वापस lock;
पूर्ण

अटल पूर्णांक stv0900_sw_algo(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				क्रमागत fe_stv0900_demod_num demod)
अणु
	पूर्णांक	lock = FALSE,
		no_संकेत,
		zigzag;
	s32	s2fw,
		fqc_inc,
		sft_stp_tout,
		trial_cntr,
		max_steps;

	stv0900_get_sw_loop_params(पूर्णांकp, &fqc_inc, &sft_stp_tout,
					&max_steps, demod);
	चयन (पूर्णांकp->srch_standard[demod]) अणु
	हाल STV0900_SEARCH_DVBS1:
	हाल STV0900_SEARCH_DSS:
		अगर (पूर्णांकp->chip_id >= 0x20)
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x3b);
		अन्यथा
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0xef);

		stv0900_ग_लिखो_reg(पूर्णांकp, DMDCFGMD, 0x49);
		zigzag = FALSE;
		अवरोध;
	हाल STV0900_SEARCH_DVBS2:
		अगर (पूर्णांकp->chip_id >= 0x20)
			stv0900_ग_लिखो_reg(पूर्णांकp, CORRELABS, 0x79);
		अन्यथा
			stv0900_ग_लिखो_reg(पूर्णांकp, CORRELABS, 0x68);

		stv0900_ग_लिखो_reg(पूर्णांकp, DMDCFGMD, 0x89);

		zigzag = TRUE;
		अवरोध;
	हाल STV0900_AUTO_SEARCH:
	शेष:
		अगर (पूर्णांकp->chip_id >= 0x20) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x3b);
			stv0900_ग_लिखो_reg(पूर्णांकp, CORRELABS, 0x79);
		पूर्ण अन्यथा अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0xef);
			stv0900_ग_लिखो_reg(पूर्णांकp, CORRELABS, 0x68);
		पूर्ण

		stv0900_ग_लिखो_reg(पूर्णांकp, DMDCFGMD, 0xc9);
		zigzag = FALSE;
		अवरोध;
	पूर्ण

	trial_cntr = 0;
	करो अणु
		lock = stv0900_search_carr_sw_loop(पूर्णांकp,
						fqc_inc,
						sft_stp_tout,
						zigzag,
						max_steps,
						demod);
		no_संकेत = stv0900_check_संकेत_presence(पूर्णांकp, demod);
		trial_cntr++;
		अगर ((lock == TRUE)
				|| (no_संकेत == TRUE)
				|| (trial_cntr == 2)) अणु

			अगर (पूर्णांकp->chip_id >= 0x20) अणु
				stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x49);
				stv0900_ग_लिखो_reg(पूर्णांकp, CORRELABS, 0x9e);
			पूर्ण अन्यथा अणु
				stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0xed);
				stv0900_ग_लिखो_reg(पूर्णांकp, CORRELABS, 0x88);
			पूर्ण

			अगर ((stv0900_get_bits(पूर्णांकp, HEADER_MODE) ==
						STV0900_DVBS2_FOUND) &&
							(lock == TRUE)) अणु
				msleep(sft_stp_tout);
				s2fw = stv0900_get_bits(पूर्णांकp, FLYWHEEL_CPT);

				अगर (s2fw < 0xd) अणु
					msleep(sft_stp_tout);
					s2fw = stv0900_get_bits(पूर्णांकp,
								FLYWHEEL_CPT);
				पूर्ण

				अगर (s2fw < 0xd) अणु
					lock = FALSE;

					अगर (trial_cntr < 2) अणु
						अगर (पूर्णांकp->chip_id >= 0x20)
							stv0900_ग_लिखो_reg(पूर्णांकp,
								CORRELABS,
								0x79);
						अन्यथा
							stv0900_ग_लिखो_reg(पूर्णांकp,
								CORRELABS,
								0x68);

						stv0900_ग_लिखो_reg(पूर्णांकp,
								DMDCFGMD,
								0x89);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

	पूर्ण जबतक ((lock == FALSE)
		&& (trial_cntr < 2)
		&& (no_संकेत == FALSE));

	वापस lock;
पूर्ण

अटल u32 stv0900_get_symbol_rate(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					u32 mclk,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	s32	rem1, rem2, पूर्णांकval1, पूर्णांकval2, srate;

	srate = (stv0900_get_bits(पूर्णांकp, SYMB_FREQ3) << 24) +
		(stv0900_get_bits(पूर्णांकp, SYMB_FREQ2) << 16) +
		(stv0900_get_bits(पूर्णांकp, SYMB_FREQ1) << 8) +
		(stv0900_get_bits(पूर्णांकp, SYMB_FREQ0));
	dprपूर्णांकk("lock: srate=%d r0=0x%x r1=0x%x r2=0x%x r3=0x%x \n",
		srate, stv0900_get_bits(पूर्णांकp, SYMB_FREQ0),
		stv0900_get_bits(पूर्णांकp, SYMB_FREQ1),
		stv0900_get_bits(पूर्णांकp, SYMB_FREQ2),
		stv0900_get_bits(पूर्णांकp, SYMB_FREQ3));

	पूर्णांकval1 = (mclk) >> 16;
	पूर्णांकval2 = (srate) >> 16;

	rem1 = (mclk) % 0x10000;
	rem2 = (srate) % 0x10000;
	srate =	(पूर्णांकval1 * पूर्णांकval2) +
		((पूर्णांकval1 * rem2) >> 16) +
		((पूर्णांकval2 * rem1) >> 16);

	वापस srate;
पूर्ण

अटल व्योम stv0900_set_symbol_rate(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					u32 mclk, u32 srate,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	u32 symb;

	dprपूर्णांकk("%s: Mclk %d, SR %d, Dmd %d\n", __func__, mclk,
							srate, demod);

	अगर (srate > 60000000) अणु
		symb = srate << 4;
		symb /= (mclk >> 12);
	पूर्ण अन्यथा अगर (srate > 6000000) अणु
		symb = srate << 6;
		symb /= (mclk >> 10);
	पूर्ण अन्यथा अणु
		symb = srate << 9;
		symb /= (mclk >> 7);
	पूर्ण

	stv0900_ग_लिखो_reg(पूर्णांकp, SFRINIT1, (symb >> 8) & 0x7f);
	stv0900_ग_लिखो_reg(पूर्णांकp, SFRINIT1 + 1, (symb & 0xff));
पूर्ण

अटल व्योम stv0900_set_max_symbol_rate(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					u32 mclk, u32 srate,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	u32 symb;

	srate = 105 * (srate / 100);

	अगर (srate > 60000000) अणु
		symb = srate << 4;
		symb /= (mclk >> 12);
	पूर्ण अन्यथा अगर (srate > 6000000) अणु
		symb = srate << 6;
		symb /= (mclk >> 10);
	पूर्ण अन्यथा अणु
		symb = srate << 9;
		symb /= (mclk >> 7);
	पूर्ण

	अगर (symb < 0x7fff) अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRUP1, (symb >> 8) & 0x7f);
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRUP1 + 1, (symb & 0xff));
	पूर्ण अन्यथा अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRUP1, 0x7f);
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRUP1 + 1, 0xff);
	पूर्ण
पूर्ण

अटल व्योम stv0900_set_min_symbol_rate(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					u32 mclk, u32 srate,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	u32	symb;

	srate = 95 * (srate / 100);
	अगर (srate > 60000000) अणु
		symb = srate << 4;
		symb /= (mclk >> 12);

	पूर्ण अन्यथा अगर (srate > 6000000) अणु
		symb = srate << 6;
		symb /= (mclk >> 10);

	पूर्ण अन्यथा अणु
		symb = srate << 9;
		symb /= (mclk >> 7);
	पूर्ण

	stv0900_ग_लिखो_reg(पूर्णांकp, SFRLOW1, (symb >> 8) & 0xff);
	stv0900_ग_लिखो_reg(पूर्णांकp, SFRLOW1 + 1, (symb & 0xff));
पूर्ण

अटल s32 stv0900_get_timing_offst(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					u32 srate,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	s32 timingoffset;


	timingoffset = (stv0900_पढ़ो_reg(पूर्णांकp, TMGREG2) << 16) +
		       (stv0900_पढ़ो_reg(पूर्णांकp, TMGREG2 + 1) << 8) +
		       (stv0900_पढ़ो_reg(पूर्णांकp, TMGREG2 + 2));

	timingoffset = ge2comp(timingoffset, 24);


	अगर (timingoffset == 0)
		timingoffset = 1;

	timingoffset = ((s32)srate * 10) / ((s32)0x1000000 / timingoffset);
	timingoffset /= 320;

	वापस timingoffset;
पूर्ण

अटल व्योम stv0900_set_dvbs2_rolloff(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	s32 rolloff;

	अगर (पूर्णांकp->chip_id == 0x10) अणु
		stv0900_ग_लिखो_bits(पूर्णांकp, MANUALSX_ROLLOFF, 1);
		rolloff = stv0900_पढ़ो_reg(पूर्णांकp, MATSTR1) & 0x03;
		stv0900_ग_लिखो_bits(पूर्णांकp, ROLLOFF_CONTROL, rolloff);
	पूर्ण अन्यथा अगर (पूर्णांकp->chip_id <= 0x20)
		stv0900_ग_लिखो_bits(पूर्णांकp, MANUALSX_ROLLOFF, 0);
	अन्यथा /* cut 3.0 */
		stv0900_ग_लिखो_bits(पूर्णांकp, MANUALS2_ROLLOFF, 0);
पूर्ण

अटल u32 stv0900_carrier_width(u32 srate, क्रमागत fe_stv0900_rolloff ro)
अणु
	u32 rolloff;

	चयन (ro) अणु
	हाल STV0900_20:
		rolloff = 20;
		अवरोध;
	हाल STV0900_25:
		rolloff = 25;
		अवरोध;
	हाल STV0900_35:
	शेष:
		rolloff = 35;
		अवरोध;
	पूर्ण

	वापस srate  + (srate * rolloff) / 100;
पूर्ण

अटल पूर्णांक stv0900_check_timing_lock(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				क्रमागत fe_stv0900_demod_num demod)
अणु
	पूर्णांक timingLock = FALSE;
	s32	i,
		timingcpt = 0;
	u8	car_freq,
		पंचांगg_th_high,
		पंचांगg_th_low;

	car_freq = stv0900_पढ़ो_reg(पूर्णांकp, CARFREQ);
	पंचांगg_th_high = stv0900_पढ़ो_reg(पूर्णांकp, TMGTHRISE);
	पंचांगg_th_low = stv0900_पढ़ो_reg(पूर्णांकp, TMGTHFALL);
	stv0900_ग_लिखो_reg(पूर्णांकp, TMGTHRISE, 0x20);
	stv0900_ग_लिखो_reg(पूर्णांकp, TMGTHFALL, 0x0);
	stv0900_ग_लिखो_bits(पूर्णांकp, CFR_AUTOSCAN, 0);
	stv0900_ग_लिखो_reg(पूर्णांकp, RTC, 0x80);
	stv0900_ग_लिखो_reg(पूर्णांकp, RTCS2, 0x40);
	stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x0);
	stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, 0x0);
	stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, 0x0);
	stv0900_ग_लिखो_reg(पूर्णांकp, AGC2REF, 0x65);
	stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x18);
	msleep(7);

	क्रम (i = 0; i < 10; i++) अणु
		अगर (stv0900_get_bits(पूर्णांकp, TMGLOCK_QUALITY) >= 2)
			timingcpt++;

		msleep(1);
	पूर्ण

	अगर (timingcpt >= 3)
		timingLock = TRUE;

	stv0900_ग_लिखो_reg(पूर्णांकp, AGC2REF, 0x38);
	stv0900_ग_लिखो_reg(पूर्णांकp, RTC, 0x88);
	stv0900_ग_लिखो_reg(पूर्णांकp, RTCS2, 0x68);
	stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, car_freq);
	stv0900_ग_लिखो_reg(पूर्णांकp, TMGTHRISE, पंचांगg_th_high);
	stv0900_ग_लिखो_reg(पूर्णांकp, TMGTHFALL, पंचांगg_th_low);

	वापस	timingLock;
पूर्ण

अटल पूर्णांक stv0900_get_demod_cold_lock(काष्ठा dvb_frontend *fe,
					s32 demod_समयout)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	पूर्णांक	lock = FALSE,
		d = demod;
	s32	srate,
		search_range,
		lockसमयout,
		currier_step,
		nb_steps,
		current_step,
		direction,
		tuner_freq,
		समयout,
		freq;

	srate = पूर्णांकp->symbol_rate[d];
	search_range = पूर्णांकp->srch_range[d];

	अगर (srate >= 10000000)
		lockसमयout = demod_समयout / 3;
	अन्यथा
		lockसमयout = demod_समयout / 2;

	lock = stv0900_get_demod_lock(पूर्णांकp, d, lockसमयout);

	अगर (lock != FALSE)
		वापस lock;

	अगर (srate >= 10000000) अणु
		अगर (stv0900_check_timing_lock(पूर्णांकp, d) == TRUE) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1f);
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x15);
			lock = stv0900_get_demod_lock(पूर्णांकp, d, demod_समयout);
		पूर्ण अन्यथा
			lock = FALSE;

		वापस lock;
	पूर्ण

	अगर (पूर्णांकp->chip_id <= 0x20) अणु
		अगर (srate <= 1000000)
			currier_step = 500;
		अन्यथा अगर (srate <= 4000000)
			currier_step = 1000;
		अन्यथा अगर (srate <= 7000000)
			currier_step = 2000;
		अन्यथा अगर (srate <= 10000000)
			currier_step = 3000;
		अन्यथा
			currier_step = 5000;

		अगर (srate >= 2000000) अणु
			समयout = (demod_समयout / 3);
			अगर (समयout > 1000)
				समयout = 1000;
		पूर्ण अन्यथा
			समयout = (demod_समयout / 2);
	पूर्ण अन्यथा अणु
		/*cut 3.0 */
		currier_step = srate / 4000;
		समयout = (demod_समयout * 3) / 4;
	पूर्ण

	nb_steps = ((search_range / 1000) / currier_step);

	अगर ((nb_steps % 2) != 0)
		nb_steps += 1;

	अगर (nb_steps <= 0)
		nb_steps = 2;
	अन्यथा अगर (nb_steps > 12)
		nb_steps = 12;

	current_step = 1;
	direction = 1;

	अगर (पूर्णांकp->chip_id <= 0x20) अणु
		tuner_freq = पूर्णांकp->freq[d];
		पूर्णांकp->bw[d] = stv0900_carrier_width(पूर्णांकp->symbol_rate[d],
				पूर्णांकp->rolloff) + पूर्णांकp->symbol_rate[d];
	पूर्ण अन्यथा
		tuner_freq = 0;

	जबतक ((current_step <= nb_steps) && (lock == FALSE)) अणु
		अगर (direction > 0)
			tuner_freq += (current_step * currier_step);
		अन्यथा
			tuner_freq -= (current_step * currier_step);

		अगर (पूर्णांकp->chip_id <= 0x20) अणु
			अगर (पूर्णांकp->tuner_type[d] == 3)
				stv0900_set_tuner_स्वतः(पूर्णांकp, tuner_freq,
						पूर्णांकp->bw[d], demod);
			अन्यथा
				stv0900_set_tuner(fe, tuner_freq, पूर्णांकp->bw[d]);

			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1c);
			stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, 0);
			stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, 0);
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1f);
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x15);
		पूर्ण अन्यथा अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1c);
			freq = (tuner_freq * 65536) / (पूर्णांकp->mclk / 1000);
			stv0900_ग_लिखो_bits(पूर्णांकp, CFR_INIT1, MSB(freq));
			stv0900_ग_लिखो_bits(पूर्णांकp, CFR_INIT0, LSB(freq));
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1f);
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x05);
		पूर्ण

		lock = stv0900_get_demod_lock(पूर्णांकp, d, समयout);
		direction *= -1;
		current_step++;
	पूर्ण

	वापस	lock;
पूर्ण

अटल व्योम stv0900_get_lock_समयout(s32 *demod_समयout, s32 *fec_समयout,
					s32 srate,
					क्रमागत fe_stv0900_search_algo algo)
अणु
	चयन (algo) अणु
	हाल STV0900_BLIND_SEARCH:
		अगर (srate <= 1500000) अणु
			(*demod_समयout) = 1500;
			(*fec_समयout) = 400;
		पूर्ण अन्यथा अगर (srate <= 5000000) अणु
			(*demod_समयout) = 1000;
			(*fec_समयout) = 300;
		पूर्ण अन्यथा अणु
			(*demod_समयout) = 700;
			(*fec_समयout) = 100;
		पूर्ण

		अवरोध;
	हाल STV0900_COLD_START:
	हाल STV0900_WARM_START:
	शेष:
		अगर (srate <= 1000000) अणु
			(*demod_समयout) = 3000;
			(*fec_समयout) = 1700;
		पूर्ण अन्यथा अगर (srate <= 2000000) अणु
			(*demod_समयout) = 2500;
			(*fec_समयout) = 1100;
		पूर्ण अन्यथा अगर (srate <= 5000000) अणु
			(*demod_समयout) = 1000;
			(*fec_समयout) = 550;
		पूर्ण अन्यथा अगर (srate <= 10000000) अणु
			(*demod_समयout) = 700;
			(*fec_समयout) = 250;
		पूर्ण अन्यथा अगर (srate <= 20000000) अणु
			(*demod_समयout) = 400;
			(*fec_समयout) = 130;
		पूर्ण अन्यथा अणु
			(*demod_समयout) = 300;
			(*fec_समयout) = 100;
		पूर्ण

		अवरोध;

	पूर्ण

	अगर (algo == STV0900_WARM_START)
		(*demod_समयout) /= 2;
पूर्ण

अटल व्योम stv0900_set_viterbi_tracq(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_demod_num demod)
अणु

	s32 vth_reg = VTH12;

	dprपूर्णांकk("%s\n", __func__);

	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0xd0);
	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x7d);
	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x53);
	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x2f);
	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x24);
	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x1f);
पूर्ण

अटल व्योम stv0900_set_viterbi_standard(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				   क्रमागत fe_stv0900_search_standard standard,
				   क्रमागत fe_stv0900_fec fec,
				   क्रमागत fe_stv0900_demod_num demod)
अणु
	dprपूर्णांकk("%s: ViterbiStandard = ", __func__);

	चयन (standard) अणु
	हाल STV0900_AUTO_SEARCH:
		dprपूर्णांकk("Auto\n");
		stv0900_ग_लिखो_reg(पूर्णांकp, FECM, 0x10);
		stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x3f);
		अवरोध;
	हाल STV0900_SEARCH_DVBS1:
		dprपूर्णांकk("DVBS1\n");
		stv0900_ग_लिखो_reg(पूर्णांकp, FECM, 0x00);
		चयन (fec) अणु
		हाल STV0900_FEC_UNKNOWN:
		शेष:
			stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x2f);
			अवरोध;
		हाल STV0900_FEC_1_2:
			stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x01);
			अवरोध;
		हाल STV0900_FEC_2_3:
			stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x02);
			अवरोध;
		हाल STV0900_FEC_3_4:
			stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x04);
			अवरोध;
		हाल STV0900_FEC_5_6:
			stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x08);
			अवरोध;
		हाल STV0900_FEC_7_8:
			stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x20);
			अवरोध;
		पूर्ण

		अवरोध;
	हाल STV0900_SEARCH_DSS:
		dprपूर्णांकk("DSS\n");
		stv0900_ग_लिखो_reg(पूर्णांकp, FECM, 0x80);
		चयन (fec) अणु
		हाल STV0900_FEC_UNKNOWN:
		शेष:
			stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x13);
			अवरोध;
		हाल STV0900_FEC_1_2:
			stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x01);
			अवरोध;
		हाल STV0900_FEC_2_3:
			stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x02);
			अवरोध;
		हाल STV0900_FEC_6_7:
			stv0900_ग_लिखो_reg(पूर्णांकp, PRVIT, 0x10);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत fe_stv0900_fec stv0900_get_vit_fec(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
						क्रमागत fe_stv0900_demod_num demod)
अणु
	क्रमागत fe_stv0900_fec prate;
	s32 rate_fld = stv0900_get_bits(पूर्णांकp, VIT_CURPUN);

	चयन (rate_fld) अणु
	हाल 13:
		prate = STV0900_FEC_1_2;
		अवरोध;
	हाल 18:
		prate = STV0900_FEC_2_3;
		अवरोध;
	हाल 21:
		prate = STV0900_FEC_3_4;
		अवरोध;
	हाल 24:
		prate = STV0900_FEC_5_6;
		अवरोध;
	हाल 25:
		prate = STV0900_FEC_6_7;
		अवरोध;
	हाल 26:
		prate = STV0900_FEC_7_8;
		अवरोध;
	शेष:
		prate = STV0900_FEC_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस prate;
पूर्ण

अटल व्योम stv0900_set_dvbs1_track_car_loop(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_demod_num demod,
					u32 srate)
अणु
	अगर (पूर्णांकp->chip_id >= 0x30) अणु
		अगर (srate >= 15000000) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, ACLC, 0x2b);
			stv0900_ग_लिखो_reg(पूर्णांकp, BCLC, 0x1a);
		पूर्ण अन्यथा अगर ((srate >= 7000000) && (15000000 > srate)) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, ACLC, 0x0c);
			stv0900_ग_लिखो_reg(पूर्णांकp, BCLC, 0x1b);
		पूर्ण अन्यथा अगर (srate < 7000000) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, ACLC, 0x2c);
			stv0900_ग_लिखो_reg(पूर्णांकp, BCLC, 0x1c);
		पूर्ण

	पूर्ण अन्यथा अणु /*cut 2.0 and 1.x*/
		stv0900_ग_लिखो_reg(पूर्णांकp, ACLC, 0x1a);
		stv0900_ग_लिखो_reg(पूर्णांकp, BCLC, 0x09);
	पूर्ण

पूर्ण

अटल व्योम stv0900_track_optimization(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;

	s32	srate,
		pilots,
		aclc,
		freq1,
		freq0,
		i = 0,
		समयd,
		समयf,
		blind_tun_sw = 0,
		modulation;

	क्रमागत fe_stv0900_modcode foundModcod;

	dprपूर्णांकk("%s\n", __func__);

	srate = stv0900_get_symbol_rate(पूर्णांकp, पूर्णांकp->mclk, demod);
	srate += stv0900_get_timing_offst(पूर्णांकp, srate, demod);

	चयन (पूर्णांकp->result[demod].standard) अणु
	हाल STV0900_DVBS1_STANDARD:
	हाल STV0900_DSS_STANDARD:
		dprपूर्णांकk("%s: found DVB-S or DSS\n", __func__);
		अगर (पूर्णांकp->srch_standard[demod] == STV0900_AUTO_SEARCH) अणु
			stv0900_ग_लिखो_bits(पूर्णांकp, DVBS1_ENABLE, 1);
			stv0900_ग_लिखो_bits(पूर्णांकp, DVBS2_ENABLE, 0);
		पूर्ण

		stv0900_ग_लिखो_bits(पूर्णांकp, ROLLOFF_CONTROL, पूर्णांकp->rolloff);
		stv0900_ग_लिखो_bits(पूर्णांकp, MANUALSX_ROLLOFF, 1);

		अगर (पूर्णांकp->chip_id < 0x30) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, ERRCTRL1, 0x75);
			अवरोध;
		पूर्ण

		अगर (stv0900_get_vit_fec(पूर्णांकp, demod) == STV0900_FEC_1_2) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, GAUSSR0, 0x98);
			stv0900_ग_लिखो_reg(पूर्णांकp, CCIR0, 0x18);
		पूर्ण अन्यथा अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, GAUSSR0, 0x18);
			stv0900_ग_लिखो_reg(पूर्णांकp, CCIR0, 0x18);
		पूर्ण

		stv0900_ग_लिखो_reg(पूर्णांकp, ERRCTRL1, 0x75);
		अवरोध;
	हाल STV0900_DVBS2_STANDARD:
		dprपूर्णांकk("%s: found DVB-S2\n", __func__);
		stv0900_ग_लिखो_bits(पूर्णांकp, DVBS1_ENABLE, 0);
		stv0900_ग_लिखो_bits(पूर्णांकp, DVBS2_ENABLE, 1);
		stv0900_ग_लिखो_reg(पूर्णांकp, ACLC, 0);
		stv0900_ग_लिखो_reg(पूर्णांकp, BCLC, 0);
		अगर (पूर्णांकp->result[demod].frame_len == STV0900_LONG_FRAME) अणु
			foundModcod = stv0900_get_bits(पूर्णांकp, DEMOD_MODCOD);
			pilots = stv0900_get_bits(पूर्णांकp, DEMOD_TYPE) & 0x01;
			aclc = stv0900_get_optim_carr_loop(srate,
							foundModcod,
							pilots,
							पूर्णांकp->chip_id);
			अगर (foundModcod <= STV0900_QPSK_910)
				stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S2Q, aclc);
			अन्यथा अगर (foundModcod <= STV0900_8PSK_910) अणु
				stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S2Q, 0x2a);
				stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S28, aclc);
			पूर्ण

			अगर ((पूर्णांकp->demod_mode == STV0900_SINGLE) &&
					(foundModcod > STV0900_8PSK_910)) अणु
				अगर (foundModcod <= STV0900_16APSK_910) अणु
					stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S2Q, 0x2a);
					stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S216A,
									aclc);
				पूर्ण अन्यथा अगर (foundModcod <= STV0900_32APSK_910) अणु
					stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S2Q, 0x2a);
					stv0900_ग_लिखो_reg(पूर्णांकp,	ACLC2S232A,
									aclc);
				पूर्ण
			पूर्ण

		पूर्ण अन्यथा अणु
			modulation = पूर्णांकp->result[demod].modulation;
			aclc = stv0900_get_optim_लघु_carr_loop(srate,
					modulation, पूर्णांकp->chip_id);
			अगर (modulation == STV0900_QPSK)
				stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S2Q, aclc);
			अन्यथा अगर (modulation == STV0900_8PSK) अणु
				stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S2Q, 0x2a);
				stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S28, aclc);
			पूर्ण अन्यथा अगर (modulation == STV0900_16APSK) अणु
				stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S2Q, 0x2a);
				stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S216A, aclc);
			पूर्ण अन्यथा अगर (modulation == STV0900_32APSK) अणु
				stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S2Q, 0x2a);
				stv0900_ग_लिखो_reg(पूर्णांकp, ACLC2S232A, aclc);
			पूर्ण

		पूर्ण

		अगर (पूर्णांकp->chip_id <= 0x11) अणु
			अगर (पूर्णांकp->demod_mode != STV0900_SINGLE)
				stv0900_activate_s2_modcod(पूर्णांकp, demod);

		पूर्ण

		stv0900_ग_लिखो_reg(पूर्णांकp, ERRCTRL1, 0x67);
		अवरोध;
	हाल STV0900_UNKNOWN_STANDARD:
	शेष:
		dprपूर्णांकk("%s: found unknown standard\n", __func__);
		stv0900_ग_लिखो_bits(पूर्णांकp, DVBS1_ENABLE, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, DVBS2_ENABLE, 1);
		अवरोध;
	पूर्ण

	freq1 = stv0900_पढ़ो_reg(पूर्णांकp, CFR2);
	freq0 = stv0900_पढ़ो_reg(पूर्णांकp, CFR1);
	अगर (पूर्णांकp->srch_algo[demod] == STV0900_BLIND_SEARCH) अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRSTEP, 0x00);
		stv0900_ग_लिखो_bits(पूर्णांकp, SCAN_ENABLE, 0);
		stv0900_ग_लिखो_bits(पूर्णांकp, CFR_AUTOSCAN, 0);
		stv0900_ग_लिखो_reg(पूर्णांकp, TMGCFG2, 0xc1);
		stv0900_set_symbol_rate(पूर्णांकp, पूर्णांकp->mclk, srate, demod);
		blind_tun_sw = 1;
		अगर (पूर्णांकp->result[demod].standard != STV0900_DVBS2_STANDARD)
			stv0900_set_dvbs1_track_car_loop(पूर्णांकp, demod, srate);

	पूर्ण

	अगर (पूर्णांकp->chip_id >= 0x20) अणु
		अगर ((पूर्णांकp->srch_standard[demod] == STV0900_SEARCH_DVBS1) ||
				(पूर्णांकp->srch_standard[demod] ==
							STV0900_SEARCH_DSS) ||
				(पूर्णांकp->srch_standard[demod] ==
							STV0900_AUTO_SEARCH)) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, VAVSRVIT, 0x0a);
			stv0900_ग_लिखो_reg(पूर्णांकp, VITSCALE, 0x0);
		पूर्ण
	पूर्ण

	अगर (पूर्णांकp->chip_id < 0x20)
		stv0900_ग_लिखो_reg(पूर्णांकp, CARHDR, 0x08);

	अगर (पूर्णांकp->chip_id == 0x10)
		stv0900_ग_लिखो_reg(पूर्णांकp, CORRELEXP, 0x0a);

	stv0900_ग_लिखो_reg(पूर्णांकp, AGC2REF, 0x38);

	अगर ((पूर्णांकp->chip_id >= 0x20) ||
			(blind_tun_sw == 1) ||
			(पूर्णांकp->symbol_rate[demod] < 10000000)) अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, freq1);
		stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, freq0);
		पूर्णांकp->bw[demod] = stv0900_carrier_width(srate,
					पूर्णांकp->rolloff) + 10000000;

		अगर ((पूर्णांकp->chip_id >= 0x20) || (blind_tun_sw == 1)) अणु
			अगर (पूर्णांकp->srch_algo[demod] != STV0900_WARM_START) अणु
				अगर (पूर्णांकp->tuner_type[demod] == 3)
					stv0900_set_tuner_स्वतः(पूर्णांकp,
							पूर्णांकp->freq[demod],
							पूर्णांकp->bw[demod],
							demod);
				अन्यथा
					stv0900_set_bandwidth(fe,
							पूर्णांकp->bw[demod]);
			पूर्ण
		पूर्ण

		अगर ((पूर्णांकp->srch_algo[demod] == STV0900_BLIND_SEARCH) ||
				(पूर्णांकp->symbol_rate[demod] < 10000000))
			msleep(50);
		अन्यथा
			msleep(5);

		stv0900_get_lock_समयout(&समयd, &समयf, srate,
						STV0900_WARM_START);

		अगर (stv0900_get_demod_lock(पूर्णांकp, demod, समयd / 2) == FALSE) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1f);
			stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, freq1);
			stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, freq0);
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x18);
			i = 0;
			जबतक ((stv0900_get_demod_lock(पूर्णांकp,
							demod,
							समयd / 2) == FALSE) &&
						(i <= 2)) अणु
				stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1f);
				stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, freq1);
				stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, freq0);
				stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x18);
				i++;
			पूर्ण
		पूर्ण

	पूर्ण

	अगर (पूर्णांकp->chip_id >= 0x20)
		stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x49);

	अगर ((पूर्णांकp->result[demod].standard == STV0900_DVBS1_STANDARD) ||
			(पूर्णांकp->result[demod].standard == STV0900_DSS_STANDARD))
		stv0900_set_viterbi_tracq(पूर्णांकp, demod);

पूर्ण

अटल पूर्णांक stv0900_get_fec_lock(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				क्रमागत fe_stv0900_demod_num demod, s32 समय_out)
अणु
	s32 समयr = 0, lock = 0;

	क्रमागत fe_stv0900_search_state dmd_state;

	dprपूर्णांकk("%s\n", __func__);

	dmd_state = stv0900_get_bits(पूर्णांकp, HEADER_MODE);

	जबतक ((समयr < समय_out) && (lock == 0)) अणु
		चयन (dmd_state) अणु
		हाल STV0900_SEARCH:
		हाल STV0900_PLH_DETECTED:
		शेष:
			lock = 0;
			अवरोध;
		हाल STV0900_DVBS2_FOUND:
			lock = stv0900_get_bits(पूर्णांकp, PKTDELIN_LOCK);
			अवरोध;
		हाल STV0900_DVBS_FOUND:
			lock = stv0900_get_bits(पूर्णांकp, LOCKEDVIT);
			अवरोध;
		पूर्ण

		अगर (lock == 0) अणु
			msleep(10);
			समयr += 10;
		पूर्ण
	पूर्ण

	अगर (lock)
		dprपूर्णांकk("%s: DEMOD FEC LOCK OK\n", __func__);
	अन्यथा
		dprपूर्णांकk("%s: DEMOD FEC LOCK FAIL\n", __func__);

	वापस lock;
पूर्ण

अटल पूर्णांक stv0900_रुको_क्रम_lock(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				क्रमागत fe_stv0900_demod_num demod,
				s32 dmd_समयout, s32 fec_समयout)
अणु

	s32 समयr = 0, lock = 0;

	dprपूर्णांकk("%s\n", __func__);

	lock = stv0900_get_demod_lock(पूर्णांकp, demod, dmd_समयout);

	अगर (lock)
		lock = stv0900_get_fec_lock(पूर्णांकp, demod, fec_समयout);

	अगर (lock) अणु
		lock = 0;

		dprपूर्णांकk("%s: Timer = %d, time_out = %d\n",
				__func__, समयr, fec_समयout);

		जबतक ((समयr < fec_समयout) && (lock == 0)) अणु
			lock = stv0900_get_bits(पूर्णांकp, TSFIFO_LINEOK);
			msleep(1);
			समयr++;
		पूर्ण
	पूर्ण

	अगर (lock)
		dprपूर्णांकk("%s: DEMOD LOCK OK\n", __func__);
	अन्यथा
		dprपूर्णांकk("%s: DEMOD LOCK FAIL\n", __func__);

	अगर (lock)
		वापस TRUE;
	अन्यथा
		वापस FALSE;
पूर्ण

क्रमागत fe_stv0900_tracking_standard stv0900_get_standard(काष्ठा dvb_frontend *fe,
						क्रमागत fe_stv0900_demod_num demod)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_tracking_standard fnd_standard;

	पूर्णांक hdr_mode = stv0900_get_bits(पूर्णांकp, HEADER_MODE);

	चयन (hdr_mode) अणु
	हाल 2:
		fnd_standard = STV0900_DVBS2_STANDARD;
		अवरोध;
	हाल 3:
		अगर (stv0900_get_bits(पूर्णांकp, DSS_DVB) == 1)
			fnd_standard = STV0900_DSS_STANDARD;
		अन्यथा
			fnd_standard = STV0900_DVBS1_STANDARD;

		अवरोध;
	शेष:
		fnd_standard = STV0900_UNKNOWN_STANDARD;
	पूर्ण

	dprपूर्णांकk("%s: standard %d\n", __func__, fnd_standard);

	वापस fnd_standard;
पूर्ण

अटल s32 stv0900_get_carr_freq(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, u32 mclk,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	s32	derot,
		rem1,
		rem2,
		पूर्णांकval1,
		पूर्णांकval2;

	derot = (stv0900_get_bits(पूर्णांकp, CAR_FREQ2) << 16) +
		(stv0900_get_bits(पूर्णांकp, CAR_FREQ1) << 8) +
		(stv0900_get_bits(पूर्णांकp, CAR_FREQ0));

	derot = ge2comp(derot, 24);
	पूर्णांकval1 = mclk >> 12;
	पूर्णांकval2 = derot >> 12;
	rem1 = mclk % 0x1000;
	rem2 = derot % 0x1000;
	derot = (पूर्णांकval1 * पूर्णांकval2) +
		((पूर्णांकval1 * rem2) >> 12) +
		((पूर्णांकval2 * rem1) >> 12);

	वापस derot;
पूर्ण

अटल u32 stv0900_get_tuner_freq(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_ops	*frontend_ops = शून्य;
	काष्ठा dvb_tuner_ops *tuner_ops = शून्य;
	u32 freq = 0;

	frontend_ops = &fe->ops;
	tuner_ops = &frontend_ops->tuner_ops;

	अगर (tuner_ops->get_frequency) अणु
		अगर ((tuner_ops->get_frequency(fe, &freq)) < 0)
			dprपूर्णांकk("%s: Invalid parameter\n", __func__);
		अन्यथा
			dprपूर्णांकk("%s: Frequency=%d\n", __func__, freq);

	पूर्ण

	वापस freq;
पूर्ण

अटल क्रमागत
fe_stv0900_संकेत_type stv0900_get_संकेत_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	क्रमागत fe_stv0900_संकेत_type range = STV0900_OUTOFRANGE;
	काष्ठा stv0900_संकेत_info *result = &पूर्णांकp->result[demod];
	s32	offsetFreq,
		srate_offset;
	पूर्णांक	i = 0,
		d = demod;

	u8 timing;

	msleep(5);
	अगर (पूर्णांकp->srch_algo[d] == STV0900_BLIND_SEARCH) अणु
		timing = stv0900_पढ़ो_reg(पूर्णांकp, TMGREG2);
		i = 0;
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRSTEP, 0x5c);

		जबतक ((i <= 50) && (timing != 0) && (timing != 0xff)) अणु
			timing = stv0900_पढ़ो_reg(पूर्णांकp, TMGREG2);
			msleep(5);
			i += 5;
		पूर्ण
	पूर्ण

	result->standard = stv0900_get_standard(fe, d);
	अगर (पूर्णांकp->tuner_type[demod] == 3)
		result->frequency = stv0900_get_freq_स्वतः(पूर्णांकp, d);
	अन्यथा
		result->frequency = stv0900_get_tuner_freq(fe);

	offsetFreq = stv0900_get_carr_freq(पूर्णांकp, पूर्णांकp->mclk, d) / 1000;
	result->frequency += offsetFreq;
	result->symbol_rate = stv0900_get_symbol_rate(पूर्णांकp, पूर्णांकp->mclk, d);
	srate_offset = stv0900_get_timing_offst(पूर्णांकp, result->symbol_rate, d);
	result->symbol_rate += srate_offset;
	result->fec = stv0900_get_vit_fec(पूर्णांकp, d);
	result->modcode = stv0900_get_bits(पूर्णांकp, DEMOD_MODCOD);
	result->pilot = stv0900_get_bits(पूर्णांकp, DEMOD_TYPE) & 0x01;
	result->frame_len = ((u32)stv0900_get_bits(पूर्णांकp, DEMOD_TYPE)) >> 1;
	result->rolloff = stv0900_get_bits(पूर्णांकp, ROLLOFF_STATUS);

	dprपूर्णांकk("%s: modcode=0x%x \n", __func__, result->modcode);

	चयन (result->standard) अणु
	हाल STV0900_DVBS2_STANDARD:
		result->spectrum = stv0900_get_bits(पूर्णांकp, SPECINV_DEMOD);
		अगर (result->modcode <= STV0900_QPSK_910)
			result->modulation = STV0900_QPSK;
		अन्यथा अगर (result->modcode <= STV0900_8PSK_910)
			result->modulation = STV0900_8PSK;
		अन्यथा अगर (result->modcode <= STV0900_16APSK_910)
			result->modulation = STV0900_16APSK;
		अन्यथा अगर (result->modcode <= STV0900_32APSK_910)
			result->modulation = STV0900_32APSK;
		अन्यथा
			result->modulation = STV0900_UNKNOWN;
		अवरोध;
	हाल STV0900_DVBS1_STANDARD:
	हाल STV0900_DSS_STANDARD:
		result->spectrum = stv0900_get_bits(पूर्णांकp, IQINV);
		result->modulation = STV0900_QPSK;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर ((पूर्णांकp->srch_algo[d] == STV0900_BLIND_SEARCH) ||
				(पूर्णांकp->symbol_rate[d] < 10000000)) अणु
		offsetFreq = result->frequency - पूर्णांकp->freq[d];
		अगर (पूर्णांकp->tuner_type[demod] == 3)
			पूर्णांकp->freq[d] = stv0900_get_freq_स्वतः(पूर्णांकp, d);
		अन्यथा
			पूर्णांकp->freq[d] = stv0900_get_tuner_freq(fe);

		अगर (असल(offsetFreq) <= ((पूर्णांकp->srch_range[d] / 2000) + 500))
			range = STV0900_RANGEOK;
		अन्यथा अगर (असल(offsetFreq) <=
				(stv0900_carrier_width(result->symbol_rate,
						result->rolloff) / 2000))
			range = STV0900_RANGEOK;

	पूर्ण अन्यथा अगर (असल(offsetFreq) <= ((पूर्णांकp->srch_range[d] / 2000) + 500))
		range = STV0900_RANGEOK;

	dprपूर्णांकk("%s: range %d\n", __func__, range);

	वापस range;
पूर्ण

अटल क्रमागत
fe_stv0900_संकेत_type stv0900_dvbs1_acq_workaround(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	क्रमागत fe_stv0900_संकेत_type संकेत_type = STV0900_NODATA;

	s32	srate,
		demod_समयout,
		fec_समयout,
		freq1,
		freq0;

	पूर्णांकp->result[demod].locked = FALSE;

	अगर (stv0900_get_bits(पूर्णांकp, HEADER_MODE) == STV0900_DVBS_FOUND) अणु
		srate = stv0900_get_symbol_rate(पूर्णांकp, पूर्णांकp->mclk, demod);
		srate += stv0900_get_timing_offst(पूर्णांकp, srate, demod);
		अगर (पूर्णांकp->srch_algo[demod] == STV0900_BLIND_SEARCH)
			stv0900_set_symbol_rate(पूर्णांकp, पूर्णांकp->mclk, srate, demod);

		stv0900_get_lock_समयout(&demod_समयout, &fec_समयout,
					srate, STV0900_WARM_START);
		freq1 = stv0900_पढ़ो_reg(पूर्णांकp, CFR2);
		freq0 = stv0900_पढ़ो_reg(पूर्णांकp, CFR1);
		stv0900_ग_लिखो_bits(पूर्णांकp, CFR_AUTOSCAN, 0);
		stv0900_ग_लिखो_bits(पूर्णांकp, SPECINV_CONTROL,
					STV0900_IQ_FORCE_SWAPPED);
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1c);
		stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, freq1);
		stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, freq0);
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x18);
		अगर (stv0900_रुको_क्रम_lock(पूर्णांकp, demod,
				demod_समयout, fec_समयout) == TRUE) अणु
			पूर्णांकp->result[demod].locked = TRUE;
			संकेत_type = stv0900_get_संकेत_params(fe);
			stv0900_track_optimization(fe);
		पूर्ण अन्यथा अणु
			stv0900_ग_लिखो_bits(पूर्णांकp, SPECINV_CONTROL,
					STV0900_IQ_FORCE_NORMAL);
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1c);
			stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, freq1);
			stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, freq0);
			stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x18);
			अगर (stv0900_रुको_क्रम_lock(पूर्णांकp, demod,
					demod_समयout, fec_समयout) == TRUE) अणु
				पूर्णांकp->result[demod].locked = TRUE;
				संकेत_type = stv0900_get_संकेत_params(fe);
				stv0900_track_optimization(fe);
			पूर्ण

		पूर्ण

	पूर्ण अन्यथा
		पूर्णांकp->result[demod].locked = FALSE;

	वापस संकेत_type;
पूर्ण

अटल u16 stv0900_blind_check_agc2_min_level(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	u32 minagc2level = 0xffff,
		agc2level,
		init_freq, freq_step;

	s32 i, j, nb_steps, direction;

	dprपूर्णांकk("%s\n", __func__);

	stv0900_ग_लिखो_reg(पूर्णांकp, AGC2REF, 0x38);
	stv0900_ग_लिखो_bits(पूर्णांकp, SCAN_ENABLE, 0);
	stv0900_ग_लिखो_bits(पूर्णांकp, CFR_AUTOSCAN, 0);

	stv0900_ग_लिखो_bits(पूर्णांकp, AUTO_GUP, 1);
	stv0900_ग_लिखो_bits(पूर्णांकp, AUTO_GLOW, 1);

	stv0900_ग_लिखो_reg(पूर्णांकp, DMDT0M, 0x0);

	stv0900_set_symbol_rate(पूर्णांकp, पूर्णांकp->mclk, 1000000, demod);
	nb_steps = -1 + (पूर्णांकp->srch_range[demod] / 1000000);
	nb_steps /= 2;
	nb_steps = (2 * nb_steps) + 1;

	अगर (nb_steps < 0)
		nb_steps = 1;

	direction = 1;

	freq_step = (1000000 << 8) / (पूर्णांकp->mclk >> 8);

	init_freq = 0;

	क्रम (i = 0; i < nb_steps; i++) अणु
		अगर (direction > 0)
			init_freq = init_freq + (freq_step * i);
		अन्यथा
			init_freq = init_freq - (freq_step * i);

		direction *= -1;
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x5C);
		stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, (init_freq >> 8) & 0xff);
		stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, init_freq  & 0xff);
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x58);
		msleep(10);
		agc2level = 0;

		क्रम (j = 0; j < 10; j++)
			agc2level += (stv0900_पढ़ो_reg(पूर्णांकp, AGC2I1) << 8)
					| stv0900_पढ़ो_reg(पूर्णांकp, AGC2I0);

		agc2level /= 10;

		अगर (agc2level < minagc2level)
			minagc2level = agc2level;

	पूर्ण

	वापस (u16)minagc2level;
पूर्ण

अटल u32 stv0900_search_srate_coarse(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	पूर्णांक timing_lck = FALSE;
	s32 i, timingcpt = 0,
		direction = 1,
		nb_steps,
		current_step = 0,
		tuner_freq;
	u32 agc2_th,
		coarse_srate = 0,
		agc2_पूर्णांकegr = 0,
		currier_step = 1200;

	अगर (पूर्णांकp->chip_id >= 0x30)
		agc2_th = 0x2e00;
	अन्यथा
		agc2_th = 0x1f00;

	stv0900_ग_लिखो_bits(पूर्णांकp, DEMOD_MODE, 0x1f);
	stv0900_ग_लिखो_reg(पूर्णांकp, TMGCFG, 0x12);
	stv0900_ग_लिखो_reg(पूर्णांकp, TMGTHRISE, 0xf0);
	stv0900_ग_लिखो_reg(पूर्णांकp, TMGTHFALL, 0xe0);
	stv0900_ग_लिखो_bits(पूर्णांकp, SCAN_ENABLE, 1);
	stv0900_ग_लिखो_bits(पूर्णांकp, CFR_AUTOSCAN, 1);
	stv0900_ग_लिखो_reg(पूर्णांकp, SFRUP1, 0x83);
	stv0900_ग_लिखो_reg(पूर्णांकp, SFRUP0, 0xc0);
	stv0900_ग_लिखो_reg(पूर्णांकp, SFRLOW1, 0x82);
	stv0900_ग_लिखो_reg(पूर्णांकp, SFRLOW0, 0xa0);
	stv0900_ग_लिखो_reg(पूर्णांकp, DMDT0M, 0x0);
	stv0900_ग_लिखो_reg(पूर्णांकp, AGC2REF, 0x50);

	अगर (पूर्णांकp->chip_id >= 0x30) अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x99);
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRSTEP, 0x98);
	पूर्ण अन्यथा अगर (पूर्णांकp->chip_id >= 0x20) अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x6a);
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRSTEP, 0x95);
	पूर्ण अन्यथा अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0xed);
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRSTEP, 0x73);
	पूर्ण

	अगर (पूर्णांकp->symbol_rate[demod] <= 2000000)
		currier_step = 1000;
	अन्यथा अगर (पूर्णांकp->symbol_rate[demod] <= 5000000)
		currier_step = 2000;
	अन्यथा अगर (पूर्णांकp->symbol_rate[demod] <= 12000000)
		currier_step = 3000;
	अन्यथा
			currier_step = 5000;

	nb_steps = -1 + ((पूर्णांकp->srch_range[demod] / 1000) / currier_step);
	nb_steps /= 2;
	nb_steps = (2 * nb_steps) + 1;

	अगर (nb_steps < 0)
		nb_steps = 1;
	अन्यथा अगर (nb_steps > 10) अणु
		nb_steps = 11;
		currier_step = (पूर्णांकp->srch_range[demod] / 1000) / 10;
	पूर्ण

	current_step = 0;
	direction = 1;

	tuner_freq = पूर्णांकp->freq[demod];

	जबतक ((timing_lck == FALSE) && (current_step < nb_steps)) अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x5f);
		stv0900_ग_लिखो_bits(पूर्णांकp, DEMOD_MODE, 0);

		msleep(50);

		क्रम (i = 0; i < 10; i++) अणु
			अगर (stv0900_get_bits(पूर्णांकp, TMGLOCK_QUALITY) >= 2)
				timingcpt++;

			agc2_पूर्णांकegr += (stv0900_पढ़ो_reg(पूर्णांकp, AGC2I1) << 8) |
					stv0900_पढ़ो_reg(पूर्णांकp, AGC2I0);
		पूर्ण

		agc2_पूर्णांकegr /= 10;
		coarse_srate = stv0900_get_symbol_rate(पूर्णांकp, पूर्णांकp->mclk, demod);
		current_step++;
		direction *= -1;

		dprपूर्णांकk("lock: I2C_DEMOD_MODE_FIELD =0. Search started. tuner freq=%d agc2=0x%x srate_coarse=%d tmg_cpt=%d\n",
			tuner_freq, agc2_पूर्णांकegr, coarse_srate, timingcpt);

		अगर ((timingcpt >= 5) &&
				(agc2_पूर्णांकegr < agc2_th) &&
				(coarse_srate < 55000000) &&
				(coarse_srate > 850000))
			timing_lck = TRUE;
		अन्यथा अगर (current_step < nb_steps) अणु
			अगर (direction > 0)
				tuner_freq += (current_step * currier_step);
			अन्यथा
				tuner_freq -= (current_step * currier_step);

			अगर (पूर्णांकp->tuner_type[demod] == 3)
				stv0900_set_tuner_स्वतः(पूर्णांकp, tuner_freq,
						पूर्णांकp->bw[demod], demod);
			अन्यथा
				stv0900_set_tuner(fe, tuner_freq,
						पूर्णांकp->bw[demod]);
		पूर्ण
	पूर्ण

	अगर (timing_lck == FALSE)
		coarse_srate = 0;
	अन्यथा
		coarse_srate = stv0900_get_symbol_rate(पूर्णांकp, पूर्णांकp->mclk, demod);

	वापस coarse_srate;
पूर्ण

अटल u32 stv0900_search_srate_fine(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	u32	coarse_srate,
		coarse_freq,
		symb,
		symbmax,
		symbmin,
		symbcomp;

	coarse_srate = stv0900_get_symbol_rate(पूर्णांकp, पूर्णांकp->mclk, demod);

	अगर (coarse_srate > 3000000) अणु
		symbmax = 13 * (coarse_srate / 10);
		symbmax = (symbmax / 1000) * 65536;
		symbmax /= (पूर्णांकp->mclk / 1000);

		symbmin = 10 * (coarse_srate / 13);
		symbmin = (symbmin / 1000)*65536;
		symbmin /= (पूर्णांकp->mclk / 1000);

		symb = (coarse_srate / 1000) * 65536;
		symb /= (पूर्णांकp->mclk / 1000);
	पूर्ण अन्यथा अणु
		symbmax = 13 * (coarse_srate / 10);
		symbmax = (symbmax / 100) * 65536;
		symbmax /= (पूर्णांकp->mclk / 100);

		symbmin = 10 * (coarse_srate / 14);
		symbmin = (symbmin / 100) * 65536;
		symbmin /= (पूर्णांकp->mclk / 100);

		symb = (coarse_srate / 100) * 65536;
		symb /= (पूर्णांकp->mclk / 100);
	पूर्ण

	symbcomp = 13 * (coarse_srate / 10);
	coarse_freq = (stv0900_पढ़ो_reg(पूर्णांकp, CFR2) << 8)
		      | stv0900_पढ़ो_reg(पूर्णांकp, CFR1);

	अगर (symbcomp < पूर्णांकp->symbol_rate[demod])
		coarse_srate = 0;
	अन्यथा अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1f);
		stv0900_ग_लिखो_reg(पूर्णांकp, TMGCFG2, 0xc1);
		stv0900_ग_लिखो_reg(पूर्णांकp, TMGTHRISE, 0x20);
		stv0900_ग_लिखो_reg(पूर्णांकp, TMGTHFALL, 0x00);
		stv0900_ग_लिखो_reg(पूर्णांकp, TMGCFG, 0xd2);
		stv0900_ग_लिखो_bits(पूर्णांकp, CFR_AUTOSCAN, 0);
		stv0900_ग_लिखो_reg(पूर्णांकp, AGC2REF, 0x38);

		अगर (पूर्णांकp->chip_id >= 0x30)
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x79);
		अन्यथा अगर (पूर्णांकp->chip_id >= 0x20)
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x49);
		अन्यथा
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0xed);

		stv0900_ग_लिखो_reg(पूर्णांकp, SFRUP1, (symbmax >> 8) & 0x7f);
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRUP0, (symbmax & 0xff));

		stv0900_ग_लिखो_reg(पूर्णांकp, SFRLOW1, (symbmin >> 8) & 0x7f);
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRLOW0, (symbmin & 0xff));

		stv0900_ग_लिखो_reg(पूर्णांकp, SFRINIT1, (symb >> 8) & 0xff);
		stv0900_ग_लिखो_reg(पूर्णांकp, SFRINIT0, (symb & 0xff));

		stv0900_ग_लिखो_reg(पूर्णांकp, DMDT0M, 0x20);
		stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, (coarse_freq >> 8) & 0xff);
		stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, coarse_freq  & 0xff);
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x15);
	पूर्ण

	वापस coarse_srate;
पूर्ण

अटल पूर्णांक stv0900_blind_search_algo(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	u8	k_ref_पंचांगg,
		k_ref_पंचांगg_max,
		k_ref_पंचांगg_min;
	u32	coarse_srate,
		agc2_th;
	पूर्णांक	lock = FALSE,
		coarse_fail = FALSE;
	s32	demod_समयout = 500,
		fec_समयout = 50,
		fail_cpt,
		i,
		agc2_overflow;
	u16	agc2_पूर्णांक;
	u8	dstatus2;

	dprपूर्णांकk("%s\n", __func__);

	अगर (पूर्णांकp->chip_id < 0x20) अणु
		k_ref_पंचांगg_max = 233;
		k_ref_पंचांगg_min = 143;
	पूर्ण अन्यथा अणु
		k_ref_पंचांगg_max = 110;
		k_ref_पंचांगg_min = 10;
	पूर्ण

	अगर (पूर्णांकp->chip_id <= 0x20)
		agc2_th = STV0900_BLIND_SEARCH_AGC2_TH;
	अन्यथा
		agc2_th = STV0900_BLIND_SEARCH_AGC2_TH_CUT30;

	agc2_पूर्णांक = stv0900_blind_check_agc2_min_level(पूर्णांकp, demod);

	dprपूर्णांकk("%s agc2_int=%d agc2_th=%d \n", __func__, agc2_पूर्णांक, agc2_th);
	अगर (agc2_पूर्णांक > agc2_th)
		वापस FALSE;

	अगर (पूर्णांकp->chip_id == 0x10)
		stv0900_ग_लिखो_reg(पूर्णांकp, CORRELEXP, 0xaa);

	अगर (पूर्णांकp->chip_id < 0x20)
		stv0900_ग_लिखो_reg(पूर्णांकp, CARHDR, 0x55);
	अन्यथा
		stv0900_ग_लिखो_reg(पूर्णांकp, CARHDR, 0x20);

	अगर (पूर्णांकp->chip_id <= 0x20)
		stv0900_ग_लिखो_reg(पूर्णांकp, CARCFG, 0xc4);
	अन्यथा
		stv0900_ग_लिखो_reg(पूर्णांकp, CARCFG, 0x6);

	stv0900_ग_लिखो_reg(पूर्णांकp, RTCS2, 0x44);

	अगर (पूर्णांकp->chip_id >= 0x20) अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, EQUALCFG, 0x41);
		stv0900_ग_लिखो_reg(पूर्णांकp, FFECFG, 0x41);
		stv0900_ग_लिखो_reg(पूर्णांकp, VITSCALE, 0x82);
		stv0900_ग_लिखो_reg(पूर्णांकp, VAVSRVIT, 0x0);
	पूर्ण

	k_ref_पंचांगg = k_ref_पंचांगg_max;

	करो अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, KREFTMG, k_ref_पंचांगg);
		अगर (stv0900_search_srate_coarse(fe) != 0) अणु
			coarse_srate = stv0900_search_srate_fine(fe);

			अगर (coarse_srate != 0) अणु
				stv0900_get_lock_समयout(&demod_समयout,
							&fec_समयout,
							coarse_srate,
							STV0900_BLIND_SEARCH);
				lock = stv0900_get_demod_lock(पूर्णांकp,
							demod,
							demod_समयout);
			पूर्ण अन्यथा
				lock = FALSE;
		पूर्ण अन्यथा अणु
			fail_cpt = 0;
			agc2_overflow = 0;

			क्रम (i = 0; i < 10; i++) अणु
				agc2_पूर्णांक = (stv0900_पढ़ो_reg(पूर्णांकp, AGC2I1) << 8)
					| stv0900_पढ़ो_reg(पूर्णांकp, AGC2I0);

				अगर (agc2_पूर्णांक >= 0xff00)
					agc2_overflow++;

				dstatus2 = stv0900_पढ़ो_reg(पूर्णांकp, DSTATUS2);

				अगर (((dstatus2 & 0x1) == 0x1) &&
						((dstatus2 >> 7) == 1))
					fail_cpt++;
			पूर्ण

			अगर ((fail_cpt > 7) || (agc2_overflow > 7))
				coarse_fail = TRUE;

			lock = FALSE;
		पूर्ण
		k_ref_पंचांगg -= 30;
	पूर्ण जबतक ((k_ref_पंचांगg >= k_ref_पंचांगg_min) &&
				(lock == FALSE) &&
				(coarse_fail == FALSE));

	वापस lock;
पूर्ण

अटल व्योम stv0900_set_viterbi_acq(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	s32 vth_reg = VTH12;

	dprपूर्णांकk("%s\n", __func__);

	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x96);
	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x64);
	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x36);
	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x23);
	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x1e);
	stv0900_ग_लिखो_reg(पूर्णांकp, vth_reg++, 0x19);
पूर्ण

अटल व्योम stv0900_set_search_standard(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_demod_num demod)
अणु

	dprपूर्णांकk("%s\n", __func__);

	चयन (पूर्णांकp->srch_standard[demod]) अणु
	हाल STV0900_SEARCH_DVBS1:
		dprपूर्णांकk("Search Standard = DVBS1\n");
		अवरोध;
	हाल STV0900_SEARCH_DSS:
		dprपूर्णांकk("Search Standard = DSS\n");
		अवरोध;
	हाल STV0900_SEARCH_DVBS2:
		dprपूर्णांकk("Search Standard = DVBS2\n");
		अवरोध;
	हाल STV0900_AUTO_SEARCH:
	शेष:
		dprपूर्णांकk("Search Standard = AUTO\n");
		अवरोध;
	पूर्ण

	चयन (पूर्णांकp->srch_standard[demod]) अणु
	हाल STV0900_SEARCH_DVBS1:
	हाल STV0900_SEARCH_DSS:
		stv0900_ग_लिखो_bits(पूर्णांकp, DVBS1_ENABLE, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, DVBS2_ENABLE, 0);
		stv0900_ग_लिखो_bits(पूर्णांकp, STOP_CLKVIT, 0);
		stv0900_set_dvbs1_track_car_loop(पूर्णांकp,
						demod,
						पूर्णांकp->symbol_rate[demod]);
		stv0900_ग_लिखो_reg(पूर्णांकp, CAR2CFG, 0x22);

		stv0900_set_viterbi_acq(पूर्णांकp, demod);
		stv0900_set_viterbi_standard(पूर्णांकp,
					पूर्णांकp->srch_standard[demod],
					पूर्णांकp->fec[demod], demod);

		अवरोध;
	हाल STV0900_SEARCH_DVBS2:
		stv0900_ग_लिखो_bits(पूर्णांकp, DVBS1_ENABLE, 0);
		stv0900_ग_लिखो_bits(पूर्णांकp, DVBS2_ENABLE, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, STOP_CLKVIT, 1);
		stv0900_ग_लिखो_reg(पूर्णांकp, ACLC, 0x1a);
		stv0900_ग_लिखो_reg(पूर्णांकp, BCLC, 0x09);
		अगर (पूर्णांकp->chip_id <= 0x20) /*cut 1.x and 2.0*/
			stv0900_ग_लिखो_reg(पूर्णांकp, CAR2CFG, 0x26);
		अन्यथा
			stv0900_ग_लिखो_reg(पूर्णांकp, CAR2CFG, 0x66);

		अगर (पूर्णांकp->demod_mode != STV0900_SINGLE) अणु
			अगर (पूर्णांकp->chip_id <= 0x11)
				stv0900_stop_all_s2_modcod(पूर्णांकp, demod);
			अन्यथा
				stv0900_activate_s2_modcod(पूर्णांकp, demod);

		पूर्ण अन्यथा
			stv0900_activate_s2_modcod_single(पूर्णांकp, demod);

		stv0900_set_viterbi_tracq(पूर्णांकp, demod);

		अवरोध;
	हाल STV0900_AUTO_SEARCH:
	शेष:
		stv0900_ग_लिखो_bits(पूर्णांकp, DVBS1_ENABLE, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, DVBS2_ENABLE, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, STOP_CLKVIT, 0);
		stv0900_ग_लिखो_reg(पूर्णांकp, ACLC, 0x1a);
		stv0900_ग_लिखो_reg(पूर्णांकp, BCLC, 0x09);
		stv0900_set_dvbs1_track_car_loop(पूर्णांकp,
						demod,
						पूर्णांकp->symbol_rate[demod]);
		अगर (पूर्णांकp->chip_id <= 0x20) /*cut 1.x and 2.0*/
			stv0900_ग_लिखो_reg(पूर्णांकp, CAR2CFG, 0x26);
		अन्यथा
			stv0900_ग_लिखो_reg(पूर्णांकp, CAR2CFG, 0x66);

		अगर (पूर्णांकp->demod_mode != STV0900_SINGLE) अणु
			अगर (पूर्णांकp->chip_id <= 0x11)
				stv0900_stop_all_s2_modcod(पूर्णांकp, demod);
			अन्यथा
				stv0900_activate_s2_modcod(पूर्णांकp, demod);

		पूर्ण अन्यथा
			stv0900_activate_s2_modcod_single(पूर्णांकp, demod);

		stv0900_set_viterbi_tracq(पूर्णांकp, demod);
		stv0900_set_viterbi_standard(पूर्णांकp,
						पूर्णांकp->srch_standard[demod],
						पूर्णांकp->fec[demod], demod);

		अवरोध;
	पूर्ण
पूर्ण

क्रमागत fe_stv0900_संकेत_type stv0900_algo(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;

	s32 demod_समयout = 500, fec_समयout = 50;
	s32 aq_घातer, agc1_घातer, i;

	पूर्णांक lock = FALSE, low_sr = FALSE;

	क्रमागत fe_stv0900_संकेत_type संकेत_type = STV0900_NOCARRIER;
	क्रमागत fe_stv0900_search_algo algo;
	पूर्णांक no_संकेत = FALSE;

	dprपूर्णांकk("%s\n", __func__);

	algo = पूर्णांकp->srch_algo[demod];
	stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 1);
	stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x5c);
	अगर (पूर्णांकp->chip_id >= 0x20) अणु
		अगर (पूर्णांकp->symbol_rate[demod] > 5000000)
			stv0900_ग_लिखो_reg(पूर्णांकp, CORRELABS, 0x9e);
		अन्यथा
			stv0900_ग_लिखो_reg(पूर्णांकp, CORRELABS, 0x82);
	पूर्ण अन्यथा
		stv0900_ग_लिखो_reg(पूर्णांकp, CORRELABS, 0x88);

	stv0900_get_lock_समयout(&demod_समयout, &fec_समयout,
				पूर्णांकp->symbol_rate[demod],
				पूर्णांकp->srch_algo[demod]);

	अगर (पूर्णांकp->srch_algo[demod] == STV0900_BLIND_SEARCH) अणु
		पूर्णांकp->bw[demod] = 2 * 36000000;

		stv0900_ग_लिखो_reg(पूर्णांकp, TMGCFG2, 0xc0);
		stv0900_ग_लिखो_reg(पूर्णांकp, CORRELMANT, 0x70);

		stv0900_set_symbol_rate(पूर्णांकp, पूर्णांकp->mclk, 1000000, demod);
	पूर्ण अन्यथा अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDT0M, 0x20);
		stv0900_ग_लिखो_reg(पूर्णांकp, TMGCFG, 0xd2);

		अगर (पूर्णांकp->symbol_rate[demod] < 2000000)
			stv0900_ग_लिखो_reg(पूर्णांकp, CORRELMANT, 0x63);
		अन्यथा
			stv0900_ग_लिखो_reg(पूर्णांकp, CORRELMANT, 0x70);

		stv0900_ग_लिखो_reg(पूर्णांकp, AGC2REF, 0x38);

		पूर्णांकp->bw[demod] =
				stv0900_carrier_width(पूर्णांकp->symbol_rate[demod],
								पूर्णांकp->rolloff);
		अगर (पूर्णांकp->chip_id >= 0x20) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, KREFTMG, 0x5a);

			अगर (पूर्णांकp->srch_algo[demod] == STV0900_COLD_START) अणु
				पूर्णांकp->bw[demod] += 10000000;
				पूर्णांकp->bw[demod] *= 15;
				पूर्णांकp->bw[demod] /= 10;
			पूर्ण अन्यथा अगर (पूर्णांकp->srch_algo[demod] == STV0900_WARM_START)
				पूर्णांकp->bw[demod] += 10000000;

		पूर्ण अन्यथा अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, KREFTMG, 0xc1);
			पूर्णांकp->bw[demod] += 10000000;
			पूर्णांकp->bw[demod] *= 15;
			पूर्णांकp->bw[demod] /= 10;
		पूर्ण

		stv0900_ग_लिखो_reg(पूर्णांकp, TMGCFG2, 0xc1);

		stv0900_set_symbol_rate(पूर्णांकp, पूर्णांकp->mclk,
					पूर्णांकp->symbol_rate[demod], demod);
		stv0900_set_max_symbol_rate(पूर्णांकp, पूर्णांकp->mclk,
					पूर्णांकp->symbol_rate[demod], demod);
		stv0900_set_min_symbol_rate(पूर्णांकp, पूर्णांकp->mclk,
					पूर्णांकp->symbol_rate[demod], demod);
		अगर (पूर्णांकp->symbol_rate[demod] >= 10000000)
			low_sr = FALSE;
		अन्यथा
			low_sr = TRUE;

	पूर्ण

	अगर (पूर्णांकp->tuner_type[demod] == 3)
		stv0900_set_tuner_स्वतः(पूर्णांकp, पूर्णांकp->freq[demod],
				पूर्णांकp->bw[demod], demod);
	अन्यथा
		stv0900_set_tuner(fe, पूर्णांकp->freq[demod], पूर्णांकp->bw[demod]);

	agc1_घातer = MAKEWORD(stv0900_get_bits(पूर्णांकp, AGCIQ_VALUE1),
				stv0900_get_bits(पूर्णांकp, AGCIQ_VALUE0));

	aq_घातer = 0;

	अगर (agc1_घातer == 0) अणु
		क्रम (i = 0; i < 5; i++)
			aq_घातer += (stv0900_get_bits(पूर्णांकp, POWER_I) +
					stv0900_get_bits(पूर्णांकp, POWER_Q)) / 2;

		aq_घातer /= 5;
	पूर्ण

	अगर ((agc1_घातer == 0) && (aq_घातer < IQPOWER_THRESHOLD)) अणु
		पूर्णांकp->result[demod].locked = FALSE;
		संकेत_type = STV0900_NOAGC1;
		dprपूर्णांकk("%s: NO AGC1, POWERI, POWERQ\n", __func__);
	पूर्ण अन्यथा अणु
		stv0900_ग_लिखो_bits(पूर्णांकp, SPECINV_CONTROL,
					पूर्णांकp->srch_iq_inv[demod]);
		अगर (पूर्णांकp->chip_id <= 0x20) /*cut 2.0*/
			stv0900_ग_लिखो_bits(पूर्णांकp, MANUALSX_ROLLOFF, 1);
		अन्यथा /*cut 3.0*/
			stv0900_ग_लिखो_bits(पूर्णांकp, MANUALS2_ROLLOFF, 1);

		stv0900_set_search_standard(पूर्णांकp, demod);

		अगर (पूर्णांकp->srch_algo[demod] != STV0900_BLIND_SEARCH)
			stv0900_start_search(पूर्णांकp, demod);
	पूर्ण

	अगर (संकेत_type == STV0900_NOAGC1)
		वापस संकेत_type;

	अगर (पूर्णांकp->chip_id == 0x12) अणु
		stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 0);
		msleep(3);
		stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 0);
	पूर्ण

	अगर (algo == STV0900_BLIND_SEARCH)
		lock = stv0900_blind_search_algo(fe);
	अन्यथा अगर (algo == STV0900_COLD_START)
		lock = stv0900_get_demod_cold_lock(fe, demod_समयout);
	अन्यथा अगर (algo == STV0900_WARM_START)
		lock = stv0900_get_demod_lock(पूर्णांकp, demod, demod_समयout);

	अगर ((lock == FALSE) && (algo == STV0900_COLD_START)) अणु
		अगर (low_sr == FALSE) अणु
			अगर (stv0900_check_timing_lock(पूर्णांकp, demod) == TRUE)
				lock = stv0900_sw_algo(पूर्णांकp, demod);
		पूर्ण
	पूर्ण

	अगर (lock == TRUE)
		संकेत_type = stv0900_get_संकेत_params(fe);

	अगर ((lock == TRUE) && (संकेत_type == STV0900_RANGEOK)) अणु
		stv0900_track_optimization(fe);
		अगर (पूर्णांकp->chip_id <= 0x11) अणु
			अगर ((stv0900_get_standard(fe, 0) ==
						STV0900_DVBS1_STANDARD) &&
			   (stv0900_get_standard(fe, 1) ==
						STV0900_DVBS1_STANDARD)) अणु
				msleep(20);
				stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 0);
			पूर्ण अन्यथा अणु
				stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 0);
				msleep(3);
				stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 1);
				stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 0);
			पूर्ण

		पूर्ण अन्यथा अगर (पूर्णांकp->chip_id >= 0x20) अणु
			stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 0);
			msleep(3);
			stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 1);
			stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 0);
		पूर्ण

		अगर (stv0900_रुको_क्रम_lock(पूर्णांकp, demod,
					fec_समयout, fec_समयout) == TRUE) अणु
			lock = TRUE;
			पूर्णांकp->result[demod].locked = TRUE;
			अगर (पूर्णांकp->result[demod].standard ==
						STV0900_DVBS2_STANDARD) अणु
				stv0900_set_dvbs2_rolloff(पूर्णांकp, demod);
				stv0900_ग_लिखो_bits(पूर्णांकp, RESET_UPKO_COUNT, 1);
				stv0900_ग_लिखो_bits(पूर्णांकp, RESET_UPKO_COUNT, 0);
				stv0900_ग_लिखो_reg(पूर्णांकp, ERRCTRL1, 0x67);
			पूर्ण अन्यथा अणु
				stv0900_ग_लिखो_reg(पूर्णांकp, ERRCTRL1, 0x75);
			पूर्ण

			stv0900_ग_लिखो_reg(पूर्णांकp, FBERCPT4, 0);
			stv0900_ग_लिखो_reg(पूर्णांकp, ERRCTRL2, 0xc1);
		पूर्ण अन्यथा अणु
			lock = FALSE;
			संकेत_type = STV0900_NODATA;
			no_संकेत = stv0900_check_संकेत_presence(पूर्णांकp, demod);

			पूर्णांकp->result[demod].locked = FALSE;
		पूर्ण
	पूर्ण

	अगर ((संकेत_type != STV0900_NODATA) || (no_संकेत != FALSE))
		वापस संकेत_type;

	अगर (पूर्णांकp->chip_id > 0x11) अणु
		पूर्णांकp->result[demod].locked = FALSE;
		वापस संकेत_type;
	पूर्ण

	अगर ((stv0900_get_bits(पूर्णांकp, HEADER_MODE) == STV0900_DVBS_FOUND) &&
	   (पूर्णांकp->srch_iq_inv[demod] <= STV0900_IQ_AUTO_NORMAL_FIRST))
		संकेत_type = stv0900_dvbs1_acq_workaround(fe);

	वापस संकेत_type;
पूर्ण

