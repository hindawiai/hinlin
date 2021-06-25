<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	STB0899 Multistandard Frontend driver
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

	Copyright (C) ST Microelectronics

*/

#समावेश <linux/bitops.h>
#समावेश "stb0899_drv.h"
#समावेश "stb0899_priv.h"
#समावेश "stb0899_reg.h"

अटल अंतरभूत u32 stb0899_करो_भाग(u64 n, u32 d)
अणु
	/* wrap करो_भाग() क्रम ease of use */

	करो_भाग(n, d);
	वापस n;
पूर्ण

#अगर 0
/* These functions are currently unused */
/*
 * stb0899_calc_srate
 * Compute symbol rate
 */
अटल u32 stb0899_calc_srate(u32 master_clk, u8 *sfr)
अणु
	u64 पंचांगp;

	/* srate = (SFR * master_clk) >> 20 */

	/* sfr is of size 20 bit, stored with an offset of 4 bit */
	पंचांगp = (((u32)sfr[0]) << 16) | (((u32)sfr[1]) << 8) | sfr[2];
	पंचांगp &= ~0xf;
	पंचांगp *= master_clk;
	पंचांगp >>= 24;

	वापस पंचांगp;
पूर्ण

/*
 * stb0899_get_srate
 * Get the current symbol rate
 */
अटल u32 stb0899_get_srate(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	u8 sfr[3];

	stb0899_पढ़ो_regs(state, STB0899_SFRH, sfr, 3);

	वापस stb0899_calc_srate(पूर्णांकernal->master_clk, sfr);
पूर्ण
#पूर्ण_अगर

/*
 * stb0899_set_srate
 * Set symbol frequency
 * MasterClock: master घड़ी frequency (hz)
 * SymbolRate: symbol rate (bauds)
 * वापस symbol frequency
 */
अटल u32 stb0899_set_srate(काष्ठा stb0899_state *state, u32 master_clk, u32 srate)
अणु
	u32 पंचांगp;
	u8 sfr[3];

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "-->");
	/*
	 * in order to have the maximum precision, the symbol rate entered पूर्णांकo
	 * the chip is computed as the बंदst value of the "true value".
	 * In this purpose, the symbol rate value is rounded (1 is added on the bit
	 * below the LSB )
	 *
	 * srate = (SFR * master_clk) >> 20
	 *      <=>
	 *   SFR = srate << 20 / master_clk
	 *
	 * rounded:
	 *   SFR = (srate << 21 + master_clk) / (2 * master_clk)
	 *
	 * stored as 20 bit number with an offset of 4 bit:
	 *   sfr = SFR << 4;
	 */

	पंचांगp = stb0899_करो_भाग((((u64)srate) << 21) + master_clk, 2 * master_clk);
	पंचांगp <<= 4;

	sfr[0] = पंचांगp >> 16;
	sfr[1] = पंचांगp >>  8;
	sfr[2] = पंचांगp;

	stb0899_ग_लिखो_regs(state, STB0899_SFRH, sfr, 3);

	वापस srate;
पूर्ण

/*
 * stb0899_calc_derot_समय
 * Compute the amount of समय needed by the derotator to lock
 * SymbolRate: Symbol rate
 * वापस: derotator समय स्थिरant (ms)
 */
अटल दीर्घ stb0899_calc_derot_समय(दीर्घ srate)
अणु
	अगर (srate > 0)
		वापस (100000 / (srate / 1000));
	अन्यथा
		वापस 0;
पूर्ण

/*
 * stb0899_carr_width
 * Compute the width of the carrier
 * वापस: width of carrier (kHz or Mhz)
 */
दीर्घ stb0899_carr_width(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;

	वापस (पूर्णांकernal->srate + (पूर्णांकernal->srate * पूर्णांकernal->rolloff) / 100);
पूर्ण

/*
 * stb0899_first_subrange
 * Compute the first subrange of the search
 */
अटल व्योम stb0899_first_subrange(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal	= &state->पूर्णांकernal;
	काष्ठा stb0899_params *params		= &state->params;
	काष्ठा stb0899_config *config		=  state->config;

	पूर्णांक range = 0;
	u32 bandwidth = 0;

	अगर (config->tuner_get_bandwidth) अणु
		stb0899_i2c_gate_ctrl(&state->frontend, 1);
		config->tuner_get_bandwidth(&state->frontend, &bandwidth);
		stb0899_i2c_gate_ctrl(&state->frontend, 0);
		range = bandwidth - stb0899_carr_width(state) / 2;
	पूर्ण

	अगर (range > 0)
		पूर्णांकernal->sub_range = min(पूर्णांकernal->srch_range, range);
	अन्यथा
		पूर्णांकernal->sub_range = 0;

	पूर्णांकernal->freq = params->freq;
	पूर्णांकernal->tuner_offst = 0L;
	पूर्णांकernal->sub_dir = 1;
पूर्ण

/*
 * stb0899_check_पंचांगg
 * check क्रम timing lock
 * पूर्णांकernal.Ttiming: समय to रुको क्रम loop lock
 */
अटल क्रमागत stb0899_status stb0899_check_पंचांगg(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	पूर्णांक lock;
	u8 reg;
	s8 timing;

	msleep(पूर्णांकernal->t_derot);

	stb0899_ग_लिखो_reg(state, STB0899_RTF, 0xf2);
	reg = stb0899_पढ़ो_reg(state, STB0899_TLIR);
	lock = STB0899_GETFIELD(TLIR_TMG_LOCK_IND, reg);
	timing = stb0899_पढ़ो_reg(state, STB0899_RTF);

	अगर (lock >= 42) अणु
		अगर ((lock > 48) && (असल(timing) >= 110)) अणु
			पूर्णांकernal->status = ANALOGCARRIER;
			dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "-->ANALOG Carrier !");
		पूर्ण अन्यथा अणु
			पूर्णांकernal->status = TIMINGOK;
			dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "------->TIMING OK !");
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांकernal->status = NOTIMING;
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "-->NO TIMING !");
	पूर्ण
	वापस पूर्णांकernal->status;
पूर्ण

/*
 * stb0899_search_पंचांगg
 * perक्रमm a fs/2 zig-zag to find timing
 */
अटल क्रमागत stb0899_status stb0899_search_पंचांगg(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	काष्ठा stb0899_params *params = &state->params;

	लघु पूर्णांक derot_step, derot_freq = 0, derot_limit, next_loop = 3;
	पूर्णांक index = 0;
	u8 cfr[2];

	पूर्णांकernal->status = NOTIMING;

	/* timing loop computation & symbol rate optimisation	*/
	derot_limit = (पूर्णांकernal->sub_range / 2L) / पूर्णांकernal->mclk;
	derot_step = (params->srate / 2L) / पूर्णांकernal->mclk;

	जबतक ((stb0899_check_पंचांगg(state) != TIMINGOK) && next_loop) अणु
		index++;
		derot_freq += index * पूर्णांकernal->direction * derot_step;	/* next derot zig zag position	*/

		अगर (असल(derot_freq) > derot_limit)
			next_loop--;

		अगर (next_loop) अणु
			STB0899_SETFIELD_VAL(CFRM, cfr[0], MSB(पूर्णांकernal->inversion * derot_freq));
			STB0899_SETFIELD_VAL(CFRL, cfr[1], LSB(पूर्णांकernal->inversion * derot_freq));
			stb0899_ग_लिखो_regs(state, STB0899_CFRM, cfr, 2); /* derotator frequency		*/
		पूर्ण
		पूर्णांकernal->direction = -पूर्णांकernal->direction;	/* Change zigzag direction		*/
	पूर्ण

	अगर (पूर्णांकernal->status == TIMINGOK) अणु
		stb0899_पढ़ो_regs(state, STB0899_CFRM, cfr, 2); /* get derotator frequency		*/
		पूर्णांकernal->derot_freq = पूर्णांकernal->inversion * MAKEWORD16(cfr[0], cfr[1]);
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "------->TIMING OK ! Derot Freq = %d", पूर्णांकernal->derot_freq);
	पूर्ण

	वापस पूर्णांकernal->status;
पूर्ण

/*
 * stb0899_check_carrier
 * Check क्रम carrier found
 */
अटल क्रमागत stb0899_status stb0899_check_carrier(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	u8 reg;

	msleep(पूर्णांकernal->t_derot); /* रुको क्रम derotator ok	*/

	reg = stb0899_पढ़ो_reg(state, STB0899_CFD);
	STB0899_SETFIELD_VAL(CFD_ON, reg, 1);
	stb0899_ग_लिखो_reg(state, STB0899_CFD, reg);

	reg = stb0899_पढ़ो_reg(state, STB0899_DSTATUS);
	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "--------------------> STB0899_DSTATUS=[0x%02x]", reg);
	अगर (STB0899_GETFIELD(CARRIER_FOUND, reg)) अणु
		पूर्णांकernal->status = CARRIEROK;
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "-------------> CARRIEROK !");
	पूर्ण अन्यथा अणु
		पूर्णांकernal->status = NOCARRIER;
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "-------------> NOCARRIER !");
	पूर्ण

	वापस पूर्णांकernal->status;
पूर्ण

/*
 * stb0899_search_carrier
 * Search क्रम a QPSK carrier with the derotator
 */
अटल क्रमागत stb0899_status stb0899_search_carrier(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;

	लघु पूर्णांक derot_freq = 0, last_derot_freq = 0, derot_limit, next_loop = 3;
	पूर्णांक index = 0;
	u8 cfr[2];
	u8 reg;

	पूर्णांकernal->status = NOCARRIER;
	derot_limit = (पूर्णांकernal->sub_range / 2L) / पूर्णांकernal->mclk;
	derot_freq = पूर्णांकernal->derot_freq;

	reg = stb0899_पढ़ो_reg(state, STB0899_CFD);
	STB0899_SETFIELD_VAL(CFD_ON, reg, 1);
	stb0899_ग_लिखो_reg(state, STB0899_CFD, reg);

	करो अणु
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Derot Freq=%d, mclk=%d", derot_freq, पूर्णांकernal->mclk);
		अगर (stb0899_check_carrier(state) == NOCARRIER) अणु
			index++;
			last_derot_freq = derot_freq;
			derot_freq += index * पूर्णांकernal->direction * पूर्णांकernal->derot_step; /* next zig zag derotator position */

			अगर(असल(derot_freq) > derot_limit)
				next_loop--;

			अगर (next_loop) अणु
				reg = stb0899_पढ़ो_reg(state, STB0899_CFD);
				STB0899_SETFIELD_VAL(CFD_ON, reg, 1);
				stb0899_ग_लिखो_reg(state, STB0899_CFD, reg);

				STB0899_SETFIELD_VAL(CFRM, cfr[0], MSB(पूर्णांकernal->inversion * derot_freq));
				STB0899_SETFIELD_VAL(CFRL, cfr[1], LSB(पूर्णांकernal->inversion * derot_freq));
				stb0899_ग_लिखो_regs(state, STB0899_CFRM, cfr, 2); /* derotator frequency	*/
			पूर्ण
		पूर्ण

		पूर्णांकernal->direction = -पूर्णांकernal->direction; /* Change zigzag direction */
	पूर्ण जबतक ((पूर्णांकernal->status != CARRIEROK) && next_loop);

	अगर (पूर्णांकernal->status == CARRIEROK) अणु
		stb0899_पढ़ो_regs(state, STB0899_CFRM, cfr, 2); /* get derotator frequency */
		पूर्णांकernal->derot_freq = पूर्णांकernal->inversion * MAKEWORD16(cfr[0], cfr[1]);
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "----> CARRIER OK !, Derot Freq=%d", पूर्णांकernal->derot_freq);
	पूर्ण अन्यथा अणु
		पूर्णांकernal->derot_freq = last_derot_freq;
	पूर्ण

	वापस पूर्णांकernal->status;
पूर्ण

/*
 * stb0899_check_data
 * Check क्रम data found
 */
अटल क्रमागत stb0899_status stb0899_check_data(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	काष्ठा stb0899_params *params = &state->params;

	पूर्णांक lock = 0, index = 0, dataTime = 500, loop;
	u8 reg;

	पूर्णांकernal->status = NODATA;

	/* RESET FEC	*/
	reg = stb0899_पढ़ो_reg(state, STB0899_TSTRES);
	STB0899_SETFIELD_VAL(FRESACS, reg, 1);
	stb0899_ग_लिखो_reg(state, STB0899_TSTRES, reg);
	msleep(1);
	reg = stb0899_पढ़ो_reg(state, STB0899_TSTRES);
	STB0899_SETFIELD_VAL(FRESACS, reg, 0);
	stb0899_ग_लिखो_reg(state, STB0899_TSTRES, reg);

	अगर (params->srate <= 2000000)
		dataTime = 2000;
	अन्यथा अगर (params->srate <= 5000000)
		dataTime = 1500;
	अन्यथा अगर (params->srate <= 15000000)
		dataTime = 1000;
	अन्यथा
		dataTime = 500;

	/* clear previous failed END_LOOPVIT */
	stb0899_पढ़ो_reg(state, STB0899_VSTATUS);

	stb0899_ग_लिखो_reg(state, STB0899_DSTATUS2, 0x00); /* क्रमce search loop	*/
	जबतक (1) अणु
		/* WARNING! VIT LOCKED has to be tested beक्रमe VIT_END_LOOOP	*/
		reg = stb0899_पढ़ो_reg(state, STB0899_VSTATUS);
		lock = STB0899_GETFIELD(VSTATUS_LOCKEDVIT, reg);
		loop = STB0899_GETFIELD(VSTATUS_END_LOOPVIT, reg);

		अगर (lock || loop || (index > dataTime))
			अवरोध;
		index++;
	पूर्ण

	अगर (lock) अणु	/* DATA LOCK indicator	*/
		पूर्णांकernal->status = DATAOK;
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "-----------------> DATA OK !");
	पूर्ण

	वापस पूर्णांकernal->status;
पूर्ण

/*
 * stb0899_search_data
 * Search क्रम a QPSK carrier with the derotator
 */
अटल क्रमागत stb0899_status stb0899_search_data(काष्ठा stb0899_state *state)
अणु
	लघु पूर्णांक derot_freq, derot_step, derot_limit, next_loop = 3;
	u8 cfr[2];
	u8 reg;
	पूर्णांक index = 1;

	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	काष्ठा stb0899_params *params = &state->params;

	derot_step = (params->srate / 4L) / पूर्णांकernal->mclk;
	derot_limit = (पूर्णांकernal->sub_range / 2L) / पूर्णांकernal->mclk;
	derot_freq = पूर्णांकernal->derot_freq;

	करो अणु
		अगर ((पूर्णांकernal->status != CARRIEROK) || (stb0899_check_data(state) != DATAOK)) अणु

			derot_freq += index * पूर्णांकernal->direction * derot_step;	/* next zig zag derotator position */
			अगर (असल(derot_freq) > derot_limit)
				next_loop--;

			अगर (next_loop) अणु
				dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Derot freq=%d, mclk=%d", derot_freq, पूर्णांकernal->mclk);
				reg = stb0899_पढ़ो_reg(state, STB0899_CFD);
				STB0899_SETFIELD_VAL(CFD_ON, reg, 1);
				stb0899_ग_लिखो_reg(state, STB0899_CFD, reg);

				STB0899_SETFIELD_VAL(CFRM, cfr[0], MSB(पूर्णांकernal->inversion * derot_freq));
				STB0899_SETFIELD_VAL(CFRL, cfr[1], LSB(पूर्णांकernal->inversion * derot_freq));
				stb0899_ग_लिखो_regs(state, STB0899_CFRM, cfr, 2); /* derotator frequency	*/

				stb0899_check_carrier(state);
				index++;
			पूर्ण
		पूर्ण
		पूर्णांकernal->direction = -पूर्णांकernal->direction; /* change zig zag direction */
	पूर्ण जबतक ((पूर्णांकernal->status != DATAOK) && next_loop);

	अगर (पूर्णांकernal->status == DATAOK) अणु
		stb0899_पढ़ो_regs(state, STB0899_CFRM, cfr, 2); /* get derotator frequency */

		/* store स्वतःdetected IQ swapping as शेष क्रम DVB-S2 tuning */
		reg = stb0899_पढ़ो_reg(state, STB0899_IQSWAP);
		अगर (STB0899_GETFIELD(SYM, reg))
			पूर्णांकernal->inversion = IQ_SWAP_ON;
		अन्यथा
			पूर्णांकernal->inversion = IQ_SWAP_OFF;

		पूर्णांकernal->derot_freq = पूर्णांकernal->inversion * MAKEWORD16(cfr[0], cfr[1]);
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "------> DATAOK ! Derot Freq=%d", पूर्णांकernal->derot_freq);
	पूर्ण

	वापस पूर्णांकernal->status;
पूर्ण

/*
 * stb0899_check_range
 * check अगर the found frequency is in the correct range
 */
अटल क्रमागत stb0899_status stb0899_check_range(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	काष्ठा stb0899_params *params = &state->params;

	पूर्णांक range_offst, tp_freq;

	range_offst = पूर्णांकernal->srch_range / 2000;
	tp_freq = पूर्णांकernal->freq - (पूर्णांकernal->derot_freq * पूर्णांकernal->mclk) / 1000;

	अगर ((tp_freq >= params->freq - range_offst) && (tp_freq <= params->freq + range_offst)) अणु
		पूर्णांकernal->status = RANGEOK;
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "----> RANGEOK !");
	पूर्ण अन्यथा अणु
		पूर्णांकernal->status = OUTOFRANGE;
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "----> OUT OF RANGE !");
	पूर्ण

	वापस पूर्णांकernal->status;
पूर्ण

/*
 * NextSubRange
 * Compute the next subrange of the search
 */
अटल व्योम next_sub_range(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	काष्ठा stb0899_params *params = &state->params;

	दीर्घ old_sub_range;

	अगर (पूर्णांकernal->sub_dir > 0) अणु
		old_sub_range = पूर्णांकernal->sub_range;
		पूर्णांकernal->sub_range = min((पूर्णांकernal->srch_range / 2) -
					  (पूर्णांकernal->tuner_offst + पूर्णांकernal->sub_range / 2),
					   पूर्णांकernal->sub_range);

		अगर (पूर्णांकernal->sub_range < 0)
			पूर्णांकernal->sub_range = 0;

		पूर्णांकernal->tuner_offst += (old_sub_range + पूर्णांकernal->sub_range) / 2;
	पूर्ण

	पूर्णांकernal->freq = params->freq + (पूर्णांकernal->sub_dir * पूर्णांकernal->tuner_offst) / 1000;
	पूर्णांकernal->sub_dir = -पूर्णांकernal->sub_dir;
पूर्ण

/*
 * stb0899_dvbs_algo
 * Search क्रम a संकेत, timing, carrier and data क्रम a
 * given frequency in a given range
 */
क्रमागत stb0899_status stb0899_dvbs_algo(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_params *params		= &state->params;
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal	= &state->पूर्णांकernal;
	काष्ठा stb0899_config *config		= state->config;

	u8 bclc, reg;
	u8 cfr[2];
	u8 eq_स्थिर[10];
	s32 clnI = 3;
	u32 bandwidth = 0;

	/* BETA values rated @ 99MHz	*/
	s32 betaTab[5][4] = अणु
	       /*  5   10   20   30MBps */
		अणु 37,  34,  32,  31 पूर्ण, /* QPSK 1/2	*/
		अणु 37,  35,  33,  31 पूर्ण, /* QPSK 2/3	*/
		अणु 37,  35,  33,  31 पूर्ण, /* QPSK 3/4	*/
		अणु 37,  36,  33,	 32 पूर्ण, /* QPSK 5/6	*/
		अणु 37,  36,  33,	 32 पूर्ण  /* QPSK 7/8	*/
	पूर्ण;

	पूर्णांकernal->direction = 1;

	stb0899_set_srate(state, पूर्णांकernal->master_clk, params->srate);
	/* Carrier loop optimization versus symbol rate क्रम acquisition*/
	अगर (params->srate <= 5000000) अणु
		stb0899_ग_लिखो_reg(state, STB0899_ACLC, 0x89);
		bclc = stb0899_पढ़ो_reg(state, STB0899_BCLC);
		STB0899_SETFIELD_VAL(BETA, bclc, 0x1c);
		stb0899_ग_लिखो_reg(state, STB0899_BCLC, bclc);
		clnI = 0;
	पूर्ण अन्यथा अगर (params->srate <= 15000000) अणु
		stb0899_ग_लिखो_reg(state, STB0899_ACLC, 0xc9);
		bclc = stb0899_पढ़ो_reg(state, STB0899_BCLC);
		STB0899_SETFIELD_VAL(BETA, bclc, 0x22);
		stb0899_ग_लिखो_reg(state, STB0899_BCLC, bclc);
		clnI = 1;
	पूर्ण अन्यथा अगर(params->srate <= 25000000) अणु
		stb0899_ग_लिखो_reg(state, STB0899_ACLC, 0x89);
		bclc = stb0899_पढ़ो_reg(state, STB0899_BCLC);
		STB0899_SETFIELD_VAL(BETA, bclc, 0x27);
		stb0899_ग_लिखो_reg(state, STB0899_BCLC, bclc);
		clnI = 2;
	पूर्ण अन्यथा अणु
		stb0899_ग_लिखो_reg(state, STB0899_ACLC, 0xc8);
		bclc = stb0899_पढ़ो_reg(state, STB0899_BCLC);
		STB0899_SETFIELD_VAL(BETA, bclc, 0x29);
		stb0899_ग_लिखो_reg(state, STB0899_BCLC, bclc);
		clnI = 3;
	पूर्ण

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Set the timing loop to acquisition");
	/* Set the timing loop to acquisition	*/
	stb0899_ग_लिखो_reg(state, STB0899_RTC, 0x46);
	stb0899_ग_लिखो_reg(state, STB0899_CFD, 0xee);

	/* !! WARNING !!
	 * Do not पढ़ो any status variables जबतक acquisition,
	 * If any needed, पढ़ो beक्रमe the acquisition starts
	 * querying status जबतक acquiring causes the
	 * acquisition to go bad and hence no locks.
	 */
	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Derot Percent=%d Srate=%d mclk=%d",
		पूर्णांकernal->derot_percent, params->srate, पूर्णांकernal->mclk);

	/* Initial calculations	*/
	पूर्णांकernal->derot_step = पूर्णांकernal->derot_percent * (params->srate / 1000L) / पूर्णांकernal->mclk; /* DerotStep/1000 * Fsymbol	*/
	पूर्णांकernal->t_derot = stb0899_calc_derot_समय(params->srate);
	पूर्णांकernal->t_data = 500;

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "RESET stream merger");
	/* RESET Stream merger	*/
	reg = stb0899_पढ़ो_reg(state, STB0899_TSTRES);
	STB0899_SETFIELD_VAL(FRESRS, reg, 1);
	stb0899_ग_लिखो_reg(state, STB0899_TSTRES, reg);

	/*
	 * Set KDIVIDER to an पूर्णांकermediate value between
	 * 1/2 and 7/8 क्रम acquisition
	 */
	reg = stb0899_पढ़ो_reg(state, STB0899_DEMAPVIT);
	STB0899_SETFIELD_VAL(DEMAPVIT_KDIVIDER, reg, 60);
	stb0899_ग_लिखो_reg(state, STB0899_DEMAPVIT, reg);

	stb0899_ग_लिखो_reg(state, STB0899_EQON, 0x01); /* Equalizer OFF जबतक acquiring */
	stb0899_ग_लिखो_reg(state, STB0899_VITSYNC, 0x19);

	stb0899_first_subrange(state);
	करो अणु
		/* Initialisations */
		cfr[0] = cfr[1] = 0;
		stb0899_ग_लिखो_regs(state, STB0899_CFRM, cfr, 2); /* RESET derotator frequency	*/

		stb0899_ग_लिखो_reg(state, STB0899_RTF, 0);
		reg = stb0899_पढ़ो_reg(state, STB0899_CFD);
		STB0899_SETFIELD_VAL(CFD_ON, reg, 1);
		stb0899_ग_लिखो_reg(state, STB0899_CFD, reg);

		पूर्णांकernal->derot_freq = 0;
		पूर्णांकernal->status = NOAGC1;

		/* enable tuner I/O */
		stb0899_i2c_gate_ctrl(&state->frontend, 1);

		/* Move tuner to frequency */
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Tuner set frequency");
		अगर (state->config->tuner_set_frequency)
			state->config->tuner_set_frequency(&state->frontend, पूर्णांकernal->freq);

		अगर (state->config->tuner_get_frequency)
			state->config->tuner_get_frequency(&state->frontend, &पूर्णांकernal->freq);

		msleep(पूर्णांकernal->t_agc1 + पूर्णांकernal->t_agc2 + पूर्णांकernal->t_derot); /* AGC1, AGC2 and timing loop	*/
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "current derot freq=%d", पूर्णांकernal->derot_freq);
		पूर्णांकernal->status = AGC1OK;

		/* There is संकेत in the band	*/
		अगर (config->tuner_get_bandwidth)
			config->tuner_get_bandwidth(&state->frontend, &bandwidth);

		/* disable tuner I/O */
		stb0899_i2c_gate_ctrl(&state->frontend, 0);

		अगर (params->srate <= bandwidth / 2)
			stb0899_search_पंचांगg(state); /* For low rates (SCPC)	*/
		अन्यथा
			stb0899_check_पंचांगg(state); /* For high rates (MCPC)	*/

		अगर (पूर्णांकernal->status == TIMINGOK) अणु
			dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
				"TIMING OK ! Derot freq=%d, mclk=%d",
				पूर्णांकernal->derot_freq, पूर्णांकernal->mclk);

			अगर (stb0899_search_carrier(state) == CARRIEROK) अणु	/* Search क्रम carrier	*/
				dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
					"CARRIER OK ! Derot freq=%d, mclk=%d",
					पूर्णांकernal->derot_freq, पूर्णांकernal->mclk);

				अगर (stb0899_search_data(state) == DATAOK) अणु	/* Check क्रम data	*/
					dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
						"DATA OK ! Derot freq=%d, mclk=%d",
						पूर्णांकernal->derot_freq, पूर्णांकernal->mclk);

					अगर (stb0899_check_range(state) == RANGEOK) अणु
						dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
							"RANGE OK ! derot freq=%d, mclk=%d",
							पूर्णांकernal->derot_freq, पूर्णांकernal->mclk);

						पूर्णांकernal->freq = params->freq - ((पूर्णांकernal->derot_freq * पूर्णांकernal->mclk) / 1000);
						reg = stb0899_पढ़ो_reg(state, STB0899_PLPARM);
						पूर्णांकernal->fecrate = STB0899_GETFIELD(VITCURPUN, reg);
						dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
							"freq=%d, internal resultant freq=%d",
							params->freq, पूर्णांकernal->freq);

						dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
							"internal puncture rate=%d",
							पूर्णांकernal->fecrate);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (पूर्णांकernal->status != RANGEOK)
			next_sub_range(state);

	पूर्ण जबतक (पूर्णांकernal->sub_range && पूर्णांकernal->status != RANGEOK);

	/* Set the timing loop to tracking	*/
	stb0899_ग_लिखो_reg(state, STB0899_RTC, 0x33);
	stb0899_ग_लिखो_reg(state, STB0899_CFD, 0xf7);
	/* अगर locked and range ok, set Kभाग	*/
	अगर (पूर्णांकernal->status == RANGEOK) अणु
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Locked & Range OK !");
		stb0899_ग_लिखो_reg(state, STB0899_EQON, 0x41);		/* Equalizer OFF जबतक acquiring	*/
		stb0899_ग_लिखो_reg(state, STB0899_VITSYNC, 0x39);	/* SN to b'11 क्रम acquisition		*/

		/*
		 * Carrier loop optimization versus
		 * symbol Rate/Puncture Rate क्रम Tracking
		 */
		reg = stb0899_पढ़ो_reg(state, STB0899_BCLC);
		चयन (पूर्णांकernal->fecrate) अणु
		हाल STB0899_FEC_1_2:		/* 13	*/
			stb0899_ग_लिखो_reg(state, STB0899_DEMAPVIT, 0x1a);
			STB0899_SETFIELD_VAL(BETA, reg, betaTab[0][clnI]);
			stb0899_ग_लिखो_reg(state, STB0899_BCLC, reg);
			अवरोध;
		हाल STB0899_FEC_2_3:		/* 18	*/
			stb0899_ग_लिखो_reg(state, STB0899_DEMAPVIT, 44);
			STB0899_SETFIELD_VAL(BETA, reg, betaTab[1][clnI]);
			stb0899_ग_लिखो_reg(state, STB0899_BCLC, reg);
			अवरोध;
		हाल STB0899_FEC_3_4:		/* 21	*/
			stb0899_ग_लिखो_reg(state, STB0899_DEMAPVIT, 60);
			STB0899_SETFIELD_VAL(BETA, reg, betaTab[2][clnI]);
			stb0899_ग_लिखो_reg(state, STB0899_BCLC, reg);
			अवरोध;
		हाल STB0899_FEC_5_6:		/* 24	*/
			stb0899_ग_लिखो_reg(state, STB0899_DEMAPVIT, 75);
			STB0899_SETFIELD_VAL(BETA, reg, betaTab[3][clnI]);
			stb0899_ग_लिखो_reg(state, STB0899_BCLC, reg);
			अवरोध;
		हाल STB0899_FEC_6_7:		/* 25	*/
			stb0899_ग_लिखो_reg(state, STB0899_DEMAPVIT, 88);
			stb0899_ग_लिखो_reg(state, STB0899_ACLC, 0x88);
			stb0899_ग_लिखो_reg(state, STB0899_BCLC, 0x9a);
			अवरोध;
		हाल STB0899_FEC_7_8:		/* 26	*/
			stb0899_ग_लिखो_reg(state, STB0899_DEMAPVIT, 94);
			STB0899_SETFIELD_VAL(BETA, reg, betaTab[4][clnI]);
			stb0899_ग_लिखो_reg(state, STB0899_BCLC, reg);
			अवरोध;
		शेष:
			dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Unsupported Puncture Rate");
			अवरोध;
		पूर्ण
		/* release stream merger RESET	*/
		reg = stb0899_पढ़ो_reg(state, STB0899_TSTRES);
		STB0899_SETFIELD_VAL(FRESRS, reg, 0);
		stb0899_ग_लिखो_reg(state, STB0899_TSTRES, reg);

		/* disable carrier detector	*/
		reg = stb0899_पढ़ो_reg(state, STB0899_CFD);
		STB0899_SETFIELD_VAL(CFD_ON, reg, 0);
		stb0899_ग_लिखो_reg(state, STB0899_CFD, reg);

		stb0899_पढ़ो_regs(state, STB0899_EQUAI1, eq_स्थिर, 10);
	पूर्ण

	वापस पूर्णांकernal->status;
पूर्ण

/*
 * stb0899_dvbs2_config_uwp
 * Configure UWP state machine
 */
अटल व्योम stb0899_dvbs2_config_uwp(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	काष्ठा stb0899_config *config = state->config;
	u32 uwp1, uwp2, uwp3, reg;

	uwp1 = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_CNTRL1);
	uwp2 = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_CNTRL2);
	uwp3 = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_CNTRL3);

	STB0899_SETFIELD_VAL(UWP_ESN0_AVE, uwp1, config->esno_ave);
	STB0899_SETFIELD_VAL(UWP_ESN0_QUANT, uwp1, config->esno_quant);
	STB0899_SETFIELD_VAL(UWP_TH_SOF, uwp1, config->uwp_threshold_sof);

	STB0899_SETFIELD_VAL(FE_COARSE_TRK, uwp2, पूर्णांकernal->av_frame_coarse);
	STB0899_SETFIELD_VAL(FE_FINE_TRK, uwp2, पूर्णांकernal->av_frame_fine);
	STB0899_SETFIELD_VAL(UWP_MISS_TH, uwp2, config->miss_threshold);

	STB0899_SETFIELD_VAL(UWP_TH_ACQ, uwp3, config->uwp_threshold_acq);
	STB0899_SETFIELD_VAL(UWP_TH_TRACK, uwp3, config->uwp_threshold_track);

	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_UWP_CNTRL1, STB0899_OFF0_UWP_CNTRL1, uwp1);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_UWP_CNTRL2, STB0899_OFF0_UWP_CNTRL2, uwp2);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_UWP_CNTRL3, STB0899_OFF0_UWP_CNTRL3, uwp3);

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, SOF_SRCH_TO);
	STB0899_SETFIELD_VAL(SOF_SEARCH_TIMEOUT, reg, config->sof_search_समयout);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_SOF_SRCH_TO, STB0899_OFF0_SOF_SRCH_TO, reg);
पूर्ण

/*
 * stb0899_dvbs2_config_csm_स्वतः
 * Set CSM to AUTO mode
 */
अटल व्योम stb0899_dvbs2_config_csm_स्वतः(काष्ठा stb0899_state *state)
अणु
	u32 reg;

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, CSM_CNTRL1);
	STB0899_SETFIELD_VAL(CSM_AUTO_PARAM, reg, 1);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CSM_CNTRL1, STB0899_OFF0_CSM_CNTRL1, reg);
पूर्ण

अटल दीर्घ Log2Int(पूर्णांक number)
अणु
	पूर्णांक i;

	i = 0;
	जबतक ((1 << i) <= असल(number))
		i++;

	अगर (number == 0)
		i = 1;

	वापस i - 1;
पूर्ण

/*
 * stb0899_dvbs2_calc_srate
 * compute BTR_NOM_FREQ क्रम the symbol rate
 */
अटल u32 stb0899_dvbs2_calc_srate(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal	= &state->पूर्णांकernal;
	काष्ठा stb0899_config *config		= state->config;

	u32 dec_ratio, dec_rate, decim, reमुख्य, पूर्णांकval, btr_nom_freq;
	u32 master_clk, srate;

	dec_ratio = (पूर्णांकernal->master_clk * 2) / (5 * पूर्णांकernal->srate);
	dec_ratio = (dec_ratio == 0) ? 1 : dec_ratio;
	dec_rate = Log2Int(dec_ratio);
	decim = 1 << dec_rate;
	master_clk = पूर्णांकernal->master_clk / 1000;
	srate = पूर्णांकernal->srate / 1000;

	अगर (decim <= 4) अणु
		पूर्णांकval = (decim * (1 << (config->btr_nco_bits - 1))) / master_clk;
		reमुख्य = (decim * (1 << (config->btr_nco_bits - 1))) % master_clk;
	पूर्ण अन्यथा अणु
		पूर्णांकval = (1 << (config->btr_nco_bits - 1)) / (master_clk / 100) * decim / 100;
		reमुख्य = (decim * (1 << (config->btr_nco_bits - 1))) % master_clk;
	पूर्ण
	btr_nom_freq = (पूर्णांकval * srate) + ((reमुख्य * srate) / master_clk);

	वापस btr_nom_freq;
पूर्ण

/*
 * stb0899_dvbs2_calc_dev
 * compute the correction to be applied to symbol rate
 */
अटल u32 stb0899_dvbs2_calc_dev(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	u32 dec_ratio, correction, master_clk, srate;

	dec_ratio = (पूर्णांकernal->master_clk * 2) / (5 * पूर्णांकernal->srate);
	dec_ratio = (dec_ratio == 0) ? 1 : dec_ratio;

	master_clk = पूर्णांकernal->master_clk / 1000;	/* क्रम पूर्णांकeger Calculation*/
	srate = पूर्णांकernal->srate / 1000;	/* क्रम पूर्णांकeger Calculation*/
	correction = (512 * master_clk) / (2 * dec_ratio * srate);

	वापस	correction;
पूर्ण

/*
 * stb0899_dvbs2_set_srate
 * Set DVBS2 symbol rate
 */
अटल व्योम stb0899_dvbs2_set_srate(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;

	u32 dec_ratio, dec_rate, win_sel, decim, f_sym, btr_nom_freq;
	u32 correction, freq_adj, band_lim, decim_cntrl, reg;
	u8 anti_alias;

	/*set decimation to 1*/
	dec_ratio = (पूर्णांकernal->master_clk * 2) / (5 * पूर्णांकernal->srate);
	dec_ratio = (dec_ratio == 0) ? 1 : dec_ratio;
	dec_rate = Log2Int(dec_ratio);

	win_sel = 0;
	अगर (dec_rate >= 5)
		win_sel = dec_rate - 4;

	decim = (1 << dec_rate);
	/* (FSamp/Fsymbol *100) क्रम पूर्णांकeger Calculation */
	f_sym = पूर्णांकernal->master_clk / ((decim * पूर्णांकernal->srate) / 1000);

	अगर (f_sym <= 2250)	/* करोn't band limit संकेत going पूर्णांकo btr block*/
		band_lim = 1;
	अन्यथा
		band_lim = 0;	/* band limit संकेत going पूर्णांकo btr block*/

	decim_cntrl = ((win_sel << 3) & 0x18) + ((band_lim << 5) & 0x20) + (dec_rate & 0x7);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_DECIM_CNTRL, STB0899_OFF0_DECIM_CNTRL, decim_cntrl);

	अगर (f_sym <= 3450)
		anti_alias = 0;
	अन्यथा अगर (f_sym <= 4250)
		anti_alias = 1;
	अन्यथा
		anti_alias = 2;

	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_ANTI_ALIAS_SEL, STB0899_OFF0_ANTI_ALIAS_SEL, anti_alias);
	btr_nom_freq = stb0899_dvbs2_calc_srate(state);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_NOM_FREQ, STB0899_OFF0_BTR_NOM_FREQ, btr_nom_freq);

	correction = stb0899_dvbs2_calc_dev(state);
	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, BTR_CNTRL);
	STB0899_SETFIELD_VAL(BTR_FREQ_CORR, reg, correction);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_CNTRL, STB0899_OFF0_BTR_CNTRL, reg);

	/* scale UWP+CSM frequency to sample rate*/
	freq_adj =  पूर्णांकernal->srate / (पूर्णांकernal->master_clk / 4096);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_FREQ_ADJ_SCALE, STB0899_OFF0_FREQ_ADJ_SCALE, freq_adj);
पूर्ण

/*
 * stb0899_dvbs2_set_btr_loopbw
 * set bit timing loop bandwidth as a percentage of the symbol rate
 */
अटल व्योम stb0899_dvbs2_set_btr_loopbw(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal	= &state->पूर्णांकernal;
	काष्ठा stb0899_config *config		= state->config;

	u32 sym_peak = 23, zeta = 707, loopbw_percent = 60;
	s32 dec_ratio, dec_rate, k_btr1_rshft, k_btr1, k_btr0_rshft;
	s32 k_btr0, k_btr2_rshft, k_direct_shअगरt, k_indirect_shअगरt;
	u32 decim, K, wn, k_direct, k_indirect;
	u32 reg;

	dec_ratio = (पूर्णांकernal->master_clk * 2) / (5 * पूर्णांकernal->srate);
	dec_ratio = (dec_ratio == 0) ? 1 : dec_ratio;
	dec_rate = Log2Int(dec_ratio);
	decim = (1 << dec_rate);

	sym_peak *= 576000;
	K = (1 << config->btr_nco_bits) / (पूर्णांकernal->master_clk / 1000);
	K *= (पूर्णांकernal->srate / 1000000) * decim; /*k=k 10^-8*/

	अगर (K != 0) अणु
		K = sym_peak / K;
		wn = (4 * zeta * zeta) + 1000000;
		wn = (2 * (loopbw_percent * 1000) * 40 * zeta) /wn;  /*wn =wn 10^-8*/

		k_indirect = (wn * wn) / K;	/*kindirect = kindirect 10^-6*/
		k_direct   = (2 * wn * zeta) / K;	/*kDirect = kDirect 10^-2*/
		k_direct  *= 100;

		k_direct_shअगरt = Log2Int(k_direct) - Log2Int(10000) - 2;
		k_btr1_rshft = (-1 * k_direct_shअगरt) + config->btr_gain_shअगरt_offset;
		k_btr1 = k_direct / (1 << k_direct_shअगरt);
		k_btr1 /= 10000;

		k_indirect_shअगरt = Log2Int(k_indirect + 15) - 20 /*- 2*/;
		k_btr0_rshft = (-1 * k_indirect_shअगरt) + config->btr_gain_shअगरt_offset;
		k_btr0 = k_indirect * (1 << (-k_indirect_shअगरt));
		k_btr0 /= 1000000;

		k_btr2_rshft = 0;
		अगर (k_btr0_rshft > 15) अणु
			k_btr2_rshft = k_btr0_rshft - 15;
			k_btr0_rshft = 15;
		पूर्ण
		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, BTR_LOOP_GAIN);
		STB0899_SETFIELD_VAL(KBTR0_RSHFT, reg, k_btr0_rshft);
		STB0899_SETFIELD_VAL(KBTR0, reg, k_btr0);
		STB0899_SETFIELD_VAL(KBTR1_RSHFT, reg, k_btr1_rshft);
		STB0899_SETFIELD_VAL(KBTR1, reg, k_btr1);
		STB0899_SETFIELD_VAL(KBTR2_RSHFT, reg, k_btr2_rshft);
		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_LOOP_GAIN, STB0899_OFF0_BTR_LOOP_GAIN, reg);
	पूर्ण अन्यथा
		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_LOOP_GAIN, STB0899_OFF0_BTR_LOOP_GAIN, 0xc4c4f);
पूर्ण

/*
 * stb0899_dvbs2_set_carr_freq
 * set nominal frequency क्रम carrier search
 */
अटल व्योम stb0899_dvbs2_set_carr_freq(काष्ठा stb0899_state *state, s32 carr_freq, u32 master_clk)
अणु
	काष्ठा stb0899_config *config = state->config;
	s32 crl_nom_freq;
	u32 reg;

	crl_nom_freq = (1 << config->crl_nco_bits) / master_clk;
	crl_nom_freq *= carr_freq;
	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, CRL_NOM_FREQ);
	STB0899_SETFIELD_VAL(CRL_NOM_FREQ, reg, crl_nom_freq);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CRL_NOM_FREQ, STB0899_OFF0_CRL_NOM_FREQ, reg);
पूर्ण

/*
 * stb0899_dvbs2_init_calc
 * Initialize DVBS2 UWP, CSM, carrier and timing loops
 */
अटल व्योम stb0899_dvbs2_init_calc(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	s32 steps, step_size;
	u32 range, reg;

	/* config uwp and csm */
	stb0899_dvbs2_config_uwp(state);
	stb0899_dvbs2_config_csm_स्वतः(state);

	/* initialize BTR	*/
	stb0899_dvbs2_set_srate(state);
	stb0899_dvbs2_set_btr_loopbw(state);

	अगर (पूर्णांकernal->srate / 1000000 >= 15)
		step_size = (1 << 17) / 5;
	अन्यथा अगर (पूर्णांकernal->srate / 1000000 >= 10)
		step_size = (1 << 17) / 7;
	अन्यथा अगर (पूर्णांकernal->srate / 1000000 >= 5)
		step_size = (1 << 17) / 10;
	अन्यथा
		step_size = (1 << 17) / 4;

	range = पूर्णांकernal->srch_range / 1000000;
	steps = (10 * range * (1 << 17)) / (step_size * (पूर्णांकernal->srate / 1000000));
	steps = (steps + 6) / 10;
	steps = (steps == 0) ? 1 : steps;
	अगर (steps % 2 == 0)
		stb0899_dvbs2_set_carr_freq(state, पूर्णांकernal->center_freq -
					   (पूर्णांकernal->step_size * (पूर्णांकernal->srate / 20000000)),
					   (पूर्णांकernal->master_clk) / 1000000);
	अन्यथा
		stb0899_dvbs2_set_carr_freq(state, पूर्णांकernal->center_freq, (पूर्णांकernal->master_clk) / 1000000);

	/*Set Carrier Search params (zigzag, num steps and freq step size*/
	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, ACQ_CNTRL2);
	STB0899_SETFIELD_VAL(ZIGZAG, reg, 1);
	STB0899_SETFIELD_VAL(NUM_STEPS, reg, steps);
	STB0899_SETFIELD_VAL(FREQ_STEPSIZE, reg, step_size);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_ACQ_CNTRL2, STB0899_OFF0_ACQ_CNTRL2, reg);
पूर्ण

/*
 * stb0899_dvbs2_btr_init
 * initialize the timing loop
 */
अटल व्योम stb0899_dvbs2_btr_init(काष्ठा stb0899_state *state)
अणु
	u32 reg;

	/* set enable BTR loopback	*/
	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, BTR_CNTRL);
	STB0899_SETFIELD_VAL(INTRP_PHS_SENSE, reg, 1);
	STB0899_SETFIELD_VAL(BTR_ERR_ENA, reg, 1);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_CNTRL, STB0899_OFF0_BTR_CNTRL, reg);

	/* fix btr freq accum at 0	*/
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_FREQ_INIT, STB0899_OFF0_BTR_FREQ_INIT, 0x10000000);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_FREQ_INIT, STB0899_OFF0_BTR_FREQ_INIT, 0x00000000);

	/* fix btr freq accum at 0	*/
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_PHS_INIT, STB0899_OFF0_BTR_PHS_INIT, 0x10000000);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_PHS_INIT, STB0899_OFF0_BTR_PHS_INIT, 0x00000000);
पूर्ण

/*
 * stb0899_dvbs2_reacquire
 * trigger a DVB-S2 acquisition
 */
अटल व्योम stb0899_dvbs2_reacquire(काष्ठा stb0899_state *state)
अणु
	u32 reg = 0;

	/* demod soft reset	*/
	STB0899_SETFIELD_VAL(DVBS2_RESET, reg, 1);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_RESET_CNTRL, STB0899_OFF0_RESET_CNTRL, reg);

	/*Reset Timing Loop	*/
	stb0899_dvbs2_btr_init(state);

	/* reset Carrier loop	*/
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CRL_FREQ_INIT, STB0899_OFF0_CRL_FREQ_INIT, (1 << 30));
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CRL_FREQ_INIT, STB0899_OFF0_CRL_FREQ_INIT, 0);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CRL_LOOP_GAIN, STB0899_OFF0_CRL_LOOP_GAIN, 0);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CRL_PHS_INIT, STB0899_OFF0_CRL_PHS_INIT, (1 << 30));
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CRL_PHS_INIT, STB0899_OFF0_CRL_PHS_INIT, 0);

	/*release demod soft reset	*/
	reg = 0;
	STB0899_SETFIELD_VAL(DVBS2_RESET, reg, 0);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_RESET_CNTRL, STB0899_OFF0_RESET_CNTRL, reg);

	/* start acquisition process	*/
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_ACQUIRE_TRIG, STB0899_OFF0_ACQUIRE_TRIG, 1);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_LOCK_LOST, STB0899_OFF0_LOCK_LOST, 0);

	/* equalizer Init	*/
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_EQUALIZER_INIT, STB0899_OFF0_EQUALIZER_INIT, 1);

	/*Start equilizer	*/
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_EQUALIZER_INIT, STB0899_OFF0_EQUALIZER_INIT, 0);

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, EQ_CNTRL);
	STB0899_SETFIELD_VAL(EQ_SHIFT, reg, 0);
	STB0899_SETFIELD_VAL(EQ_DISABLE_UPDATE, reg, 0);
	STB0899_SETFIELD_VAL(EQ_DELAY, reg, 0x05);
	STB0899_SETFIELD_VAL(EQ_ADAPT_MODE, reg, 0x01);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_EQ_CNTRL, STB0899_OFF0_EQ_CNTRL, reg);

	/* RESET Packet delineator	*/
	stb0899_ग_लिखो_reg(state, STB0899_PDELCTRL, 0x4a);
पूर्ण

/*
 * stb0899_dvbs2_get_dmd_status
 * get DVB-S2 Demod LOCK status
 */
अटल क्रमागत stb0899_status stb0899_dvbs2_get_dmd_status(काष्ठा stb0899_state *state, पूर्णांक समयout)
अणु
	पूर्णांक समय = -10, lock = 0, uwp, csm;
	u32 reg;

	करो अणु
		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_STATUS);
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "DMD_STATUS=[0x%02x]", reg);
		अगर (STB0899_GETFIELD(IF_AGC_LOCK, reg))
			dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "------------->IF AGC LOCKED !");
		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_STAT2);
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "----------->DMD STAT2=[0x%02x]", reg);
		uwp = STB0899_GETFIELD(UWP_LOCK, reg);
		csm = STB0899_GETFIELD(CSM_LOCK, reg);
		अगर (uwp && csm)
			lock = 1;

		समय += 10;
		msleep(10);

	पूर्ण जबतक ((!lock) && (समय <= समयout));

	अगर (lock) अणु
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "----------------> DVB-S2 LOCK !");
		वापस DVBS2_DEMOD_LOCK;
	पूर्ण अन्यथा अणु
		वापस DVBS2_DEMOD_NOLOCK;
	पूर्ण
पूर्ण

/*
 * stb0899_dvbs2_get_data_lock
 * get FEC status
 */
अटल पूर्णांक stb0899_dvbs2_get_data_lock(काष्ठा stb0899_state *state, पूर्णांक समयout)
अणु
	पूर्णांक समय = 0, lock = 0;
	u8 reg;

	जबतक ((!lock) && (समय < समयout)) अणु
		reg = stb0899_पढ़ो_reg(state, STB0899_CFGPDELSTATUS1);
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "---------> CFGPDELSTATUS=[0x%02x]", reg);
		lock = STB0899_GETFIELD(CFGPDELSTATUS_LOCK, reg);
		समय++;
	पूर्ण

	वापस lock;
पूर्ण

/*
 * stb0899_dvbs2_get_fec_status
 * get DVB-S2 FEC LOCK status
 */
अटल क्रमागत stb0899_status stb0899_dvbs2_get_fec_status(काष्ठा stb0899_state *state, पूर्णांक समयout)
अणु
	पूर्णांक समय = 0, Locked;

	करो अणु
		Locked = stb0899_dvbs2_get_data_lock(state, 1);
		समय++;
		msleep(1);

	पूर्ण जबतक ((!Locked) && (समय < समयout));

	अगर (Locked) अणु
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "---------->DVB-S2 FEC LOCK !");
		वापस DVBS2_FEC_LOCK;
	पूर्ण अन्यथा अणु
		वापस DVBS2_FEC_NOLOCK;
	पूर्ण
पूर्ण


/*
 * stb0899_dvbs2_init_csm
 * set parameters क्रम manual mode
 */
अटल व्योम stb0899_dvbs2_init_csm(काष्ठा stb0899_state *state, पूर्णांक pilots, क्रमागत stb0899_modcod modcod)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;

	s32 dvt_tbl = 1, two_pass = 0, agc_gain = 6, agc_shअगरt = 0, loop_shअगरt = 0, phs_dअगरf_thr = 0x80;
	s32 gamma_acq, gamma_rho_acq, gamma_trk, gamma_rho_trk, lock_count_thr;
	u32 csm1, csm2, csm3, csm4;

	अगर (((पूर्णांकernal->master_clk / पूर्णांकernal->srate) <= 4) && (modcod <= 11) && (pilots == 1)) अणु
		चयन (modcod) अणु
		हाल STB0899_QPSK_12:
			gamma_acq		= 25;
			gamma_rho_acq		= 2700;
			gamma_trk		= 12;
			gamma_rho_trk		= 180;
			lock_count_thr		= 8;
			अवरोध;
		हाल STB0899_QPSK_35:
			gamma_acq		= 38;
			gamma_rho_acq		= 7182;
			gamma_trk		= 14;
			gamma_rho_trk		= 308;
			lock_count_thr		= 8;
			अवरोध;
		हाल STB0899_QPSK_23:
			gamma_acq		= 42;
			gamma_rho_acq		= 9408;
			gamma_trk		= 17;
			gamma_rho_trk		= 476;
			lock_count_thr		= 8;
			अवरोध;
		हाल STB0899_QPSK_34:
			gamma_acq		= 53;
			gamma_rho_acq		= 16642;
			gamma_trk		= 19;
			gamma_rho_trk		= 646;
			lock_count_thr		= 8;
			अवरोध;
		हाल STB0899_QPSK_45:
			gamma_acq		= 53;
			gamma_rho_acq		= 17119;
			gamma_trk		= 22;
			gamma_rho_trk		= 880;
			lock_count_thr		= 8;
			अवरोध;
		हाल STB0899_QPSK_56:
			gamma_acq		= 55;
			gamma_rho_acq		= 19250;
			gamma_trk		= 23;
			gamma_rho_trk		= 989;
			lock_count_thr		= 8;
			अवरोध;
		हाल STB0899_QPSK_89:
			gamma_acq		= 60;
			gamma_rho_acq		= 24240;
			gamma_trk		= 24;
			gamma_rho_trk		= 1176;
			lock_count_thr		= 8;
			अवरोध;
		हाल STB0899_QPSK_910:
			gamma_acq		= 66;
			gamma_rho_acq		= 29634;
			gamma_trk		= 24;
			gamma_rho_trk		= 1176;
			lock_count_thr		= 8;
			अवरोध;
		शेष:
			gamma_acq		= 66;
			gamma_rho_acq		= 29634;
			gamma_trk		= 24;
			gamma_rho_trk		= 1176;
			lock_count_thr		= 8;
			अवरोध;
		पूर्ण

		csm1 = STB0899_READ_S2REG(STB0899_S2DEMOD, CSM_CNTRL1);
		STB0899_SETFIELD_VAL(CSM_AUTO_PARAM, csm1, 0);
		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CSM_CNTRL1, STB0899_OFF0_CSM_CNTRL1, csm1);

		csm1 = STB0899_READ_S2REG(STB0899_S2DEMOD, CSM_CNTRL1);
		csm2 = STB0899_READ_S2REG(STB0899_S2DEMOD, CSM_CNTRL2);
		csm3 = STB0899_READ_S2REG(STB0899_S2DEMOD, CSM_CNTRL3);
		csm4 = STB0899_READ_S2REG(STB0899_S2DEMOD, CSM_CNTRL4);

		STB0899_SETFIELD_VAL(CSM_DVT_TABLE, csm1, dvt_tbl);
		STB0899_SETFIELD_VAL(CSM_TWO_PASS, csm1, two_pass);
		STB0899_SETFIELD_VAL(CSM_AGC_GAIN, csm1, agc_gain);
		STB0899_SETFIELD_VAL(CSM_AGC_SHIFT, csm1, agc_shअगरt);
		STB0899_SETFIELD_VAL(FE_LOOP_SHIFT, csm1, loop_shअगरt);
		STB0899_SETFIELD_VAL(CSM_GAMMA_ACQ, csm2, gamma_acq);
		STB0899_SETFIELD_VAL(CSM_GAMMA_RHOACQ, csm2, gamma_rho_acq);
		STB0899_SETFIELD_VAL(CSM_GAMMA_TRACK, csm3, gamma_trk);
		STB0899_SETFIELD_VAL(CSM_GAMMA_RHOTRACK, csm3, gamma_rho_trk);
		STB0899_SETFIELD_VAL(CSM_LOCKCOUNT_THRESH, csm4, lock_count_thr);
		STB0899_SETFIELD_VAL(CSM_PHASEDIFF_THRESH, csm4, phs_dअगरf_thr);

		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CSM_CNTRL1, STB0899_OFF0_CSM_CNTRL1, csm1);
		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CSM_CNTRL2, STB0899_OFF0_CSM_CNTRL2, csm2);
		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CSM_CNTRL3, STB0899_OFF0_CSM_CNTRL3, csm3);
		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CSM_CNTRL4, STB0899_OFF0_CSM_CNTRL4, csm4);
	पूर्ण
पूर्ण

/*
 * stb0899_dvbs2_get_srate
 * get DVB-S2 Symbol Rate
 */
अटल u32 stb0899_dvbs2_get_srate(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	काष्ठा stb0899_config *config = state->config;

	u32 bTrNomFreq, srate, decimRate, पूर्णांकval1, पूर्णांकval2, reg;
	पूर्णांक भाग1, भाग2, rem1, rem2;

	भाग1 = config->btr_nco_bits / 2;
	भाग2 = config->btr_nco_bits - भाग1 - 1;

	bTrNomFreq = STB0899_READ_S2REG(STB0899_S2DEMOD, BTR_NOM_FREQ);

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DECIM_CNTRL);
	decimRate = STB0899_GETFIELD(DECIM_RATE, reg);
	decimRate = (1 << decimRate);

	पूर्णांकval1 = पूर्णांकernal->master_clk / (1 << भाग1);
	पूर्णांकval2 = bTrNomFreq / (1 << भाग2);

	rem1 = पूर्णांकernal->master_clk % (1 << भाग1);
	rem2 = bTrNomFreq % (1 << भाग2);
	/* only क्रम पूर्णांकeger calculation	*/
	srate = (पूर्णांकval1 * पूर्णांकval2) + ((पूर्णांकval1 * rem2) / (1 << भाग2)) + ((पूर्णांकval2 * rem1) / (1 << भाग1));
	srate /= decimRate;	/*symbrate = (btrnomfreq_रेजिस्टर_val*MasterClock)/2^(27+decim_rate_field) */

	वापस	srate;
पूर्ण

/*
 * stb0899_dvbs2_algo
 * Search क्रम संकेत, timing, carrier and data क्रम a given
 * frequency in a given range
 */
क्रमागत stb0899_status stb0899_dvbs2_algo(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	क्रमागत stb0899_modcod modcod;

	s32 offsetfreq, searchTime, FecLockTime, pilots, iqSpectrum;
	पूर्णांक i = 0;
	u32 reg, csm1;

	अगर (पूर्णांकernal->srate <= 2000000) अणु
		searchTime	= 5000;	/* 5000 ms max समय to lock UWP and CSM, SYMB <= 2Mbs		*/
		FecLockTime	= 350;	/* 350  ms max समय to lock FEC, SYMB <= 2Mbs			*/
	पूर्ण अन्यथा अगर (पूर्णांकernal->srate <= 5000000) अणु
		searchTime	= 2500;	/* 2500 ms max समय to lock UWP and CSM, 2Mbs < SYMB <= 5Mbs	*/
		FecLockTime	= 170;	/* 170  ms max समय to lock FEC, 2Mbs< SYMB <= 5Mbs		*/
	पूर्ण अन्यथा अगर (पूर्णांकernal->srate <= 10000000) अणु
		searchTime	= 1500;	/* 1500 ms max समय to lock UWP and CSM, 5Mbs <SYMB <= 10Mbs	*/
		FecLockTime	= 80;	/* 80  ms max समय to lock FEC, 5Mbs< SYMB <= 10Mbs		*/
	पूर्ण अन्यथा अगर (पूर्णांकernal->srate <= 15000000) अणु
		searchTime	= 500;	/* 500 ms max समय to lock UWP and CSM, 10Mbs <SYMB <= 15Mbs	*/
		FecLockTime	= 50;	/* 50  ms max समय to lock FEC, 10Mbs< SYMB <= 15Mbs		*/
	पूर्ण अन्यथा अगर (पूर्णांकernal->srate <= 20000000) अणु
		searchTime	= 300;	/* 300 ms max समय to lock UWP and CSM, 15Mbs < SYMB <= 20Mbs	*/
		FecLockTime	= 30;	/* 50  ms max समय to lock FEC, 15Mbs< SYMB <= 20Mbs		*/
	पूर्ण अन्यथा अगर (पूर्णांकernal->srate <= 25000000) अणु
		searchTime	= 250;	/* 250 ms max समय to lock UWP and CSM, 20 Mbs < SYMB <= 25Mbs	*/
		FecLockTime	= 25;	/* 25 ms max समय to lock FEC, 20Mbs< SYMB <= 25Mbs		*/
	पूर्ण अन्यथा अणु
		searchTime	= 150;	/* 150 ms max समय to lock UWP and CSM, SYMB > 25Mbs		*/
		FecLockTime	= 20;	/* 20 ms max समय to lock FEC, 20Mbs< SYMB <= 25Mbs		*/
	पूर्ण

	/* Maपूर्णांकain Stream Merger in reset during acquisition	*/
	reg = stb0899_पढ़ो_reg(state, STB0899_TSTRES);
	STB0899_SETFIELD_VAL(FRESRS, reg, 1);
	stb0899_ग_लिखो_reg(state, STB0899_TSTRES, reg);

	/* enable tuner I/O */
	stb0899_i2c_gate_ctrl(&state->frontend, 1);

	/* Move tuner to frequency	*/
	अगर (state->config->tuner_set_frequency)
		state->config->tuner_set_frequency(&state->frontend, पूर्णांकernal->freq);
	अगर (state->config->tuner_get_frequency)
		state->config->tuner_get_frequency(&state->frontend, &पूर्णांकernal->freq);

	/* disable tuner I/O */
	stb0899_i2c_gate_ctrl(&state->frontend, 0);

	/* Set IF AGC to acquisition	*/
	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, IF_AGC_CNTRL);
	STB0899_SETFIELD_VAL(IF_LOOP_GAIN, reg,  4);
	STB0899_SETFIELD_VAL(IF_AGC_REF, reg, 32);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_IF_AGC_CNTRL, STB0899_OFF0_IF_AGC_CNTRL, reg);

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, IF_AGC_CNTRL2);
	STB0899_SETFIELD_VAL(IF_AGC_DUMP_PER, reg, 0);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_IF_AGC_CNTRL2, STB0899_OFF0_IF_AGC_CNTRL2, reg);

	/* Initialisation	*/
	stb0899_dvbs2_init_calc(state);

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_CNTRL2);
	चयन (पूर्णांकernal->inversion) अणु
	हाल IQ_SWAP_OFF:
		STB0899_SETFIELD_VAL(SPECTRUM_INVERT, reg, 0);
		अवरोध;
	हाल IQ_SWAP_ON:
		STB0899_SETFIELD_VAL(SPECTRUM_INVERT, reg, 1);
		अवरोध;
	पूर्ण
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_DMD_CNTRL2, STB0899_OFF0_DMD_CNTRL2, reg);
	stb0899_dvbs2_reacquire(state);

	/* Wait क्रम demod lock (UWP and CSM)	*/
	पूर्णांकernal->status = stb0899_dvbs2_get_dmd_status(state, searchTime);

	अगर (पूर्णांकernal->status == DVBS2_DEMOD_LOCK) अणु
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "------------> DVB-S2 DEMOD LOCK !");
		i = 0;
		/* Demod Locked, check FEC status	*/
		पूर्णांकernal->status = stb0899_dvbs2_get_fec_status(state, FecLockTime);

		/*If false lock (UWP and CSM Locked but no FEC) try 3 समय max*/
		जबतक ((पूर्णांकernal->status != DVBS2_FEC_LOCK) && (i < 3)) अणु
			/*	Read the frequency offset*/
			offsetfreq = STB0899_READ_S2REG(STB0899_S2DEMOD, CRL_FREQ);

			/* Set the Nominal frequency to the found frequency offset क्रम the next reacquire*/
			reg = STB0899_READ_S2REG(STB0899_S2DEMOD, CRL_NOM_FREQ);
			STB0899_SETFIELD_VAL(CRL_NOM_FREQ, reg, offsetfreq);
			stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CRL_NOM_FREQ, STB0899_OFF0_CRL_NOM_FREQ, reg);
			stb0899_dvbs2_reacquire(state);
			पूर्णांकernal->status = stb0899_dvbs2_get_fec_status(state, searchTime);
			i++;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकernal->status != DVBS2_FEC_LOCK) अणु
		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_CNTRL2);
		iqSpectrum = STB0899_GETFIELD(SPECTRUM_INVERT, reg);
		/* IQ Spectrum Inversion	*/
		STB0899_SETFIELD_VAL(SPECTRUM_INVERT, reg, !iqSpectrum);
		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_DMD_CNTRL2, STB0899_OFF0_DMD_CNTRL2, reg);
		/* start acquistion process	*/
		stb0899_dvbs2_reacquire(state);

		/* Wait क्रम demod lock (UWP and CSM)	*/
		पूर्णांकernal->status = stb0899_dvbs2_get_dmd_status(state, searchTime);
		अगर (पूर्णांकernal->status == DVBS2_DEMOD_LOCK) अणु
			i = 0;
			/* Demod Locked, check FEC	*/
			पूर्णांकernal->status = stb0899_dvbs2_get_fec_status(state, FecLockTime);
			/*try thrice क्रम false locks, (UWP and CSM Locked but no FEC)	*/
			जबतक ((पूर्णांकernal->status != DVBS2_FEC_LOCK) && (i < 3)) अणु
				/*	Read the frequency offset*/
				offsetfreq = STB0899_READ_S2REG(STB0899_S2DEMOD, CRL_FREQ);

				/* Set the Nominal frequency to the found frequency offset क्रम the next reacquire*/
				reg = STB0899_READ_S2REG(STB0899_S2DEMOD, CRL_NOM_FREQ);
				STB0899_SETFIELD_VAL(CRL_NOM_FREQ, reg, offsetfreq);
				stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CRL_NOM_FREQ, STB0899_OFF0_CRL_NOM_FREQ, reg);

				stb0899_dvbs2_reacquire(state);
				पूर्णांकernal->status = stb0899_dvbs2_get_fec_status(state, searchTime);
				i++;
			पूर्ण
		पूर्ण
/*
		अगर (pParams->DVBS2State == FE_DVBS2_FEC_LOCKED)
			pParams->IQLocked = !iqSpectrum;
*/
	पूर्ण
	अगर (पूर्णांकernal->status == DVBS2_FEC_LOCK) अणु
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "----------------> DVB-S2 FEC Lock !");
		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_STAT2);
		modcod = STB0899_GETFIELD(UWP_DECODE_MOD, reg) >> 2;
		pilots = STB0899_GETFIELD(UWP_DECODE_MOD, reg) & 0x01;

		अगर ((((10 * पूर्णांकernal->master_clk) / (पूर्णांकernal->srate / 10)) <= 410) &&
		      (INRANGE(STB0899_QPSK_23, modcod, STB0899_QPSK_910)) &&
		      (pilots == 1)) अणु

			stb0899_dvbs2_init_csm(state, pilots, modcod);
			/* Wait क्रम UWP,CSM and data LOCK 20ms max	*/
			पूर्णांकernal->status = stb0899_dvbs2_get_fec_status(state, FecLockTime);

			i = 0;
			जबतक ((पूर्णांकernal->status != DVBS2_FEC_LOCK) && (i < 3)) अणु
				csm1 = STB0899_READ_S2REG(STB0899_S2DEMOD, CSM_CNTRL1);
				STB0899_SETFIELD_VAL(CSM_TWO_PASS, csm1, 1);
				stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CSM_CNTRL1, STB0899_OFF0_CSM_CNTRL1, csm1);
				csm1 = STB0899_READ_S2REG(STB0899_S2DEMOD, CSM_CNTRL1);
				STB0899_SETFIELD_VAL(CSM_TWO_PASS, csm1, 0);
				stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_CSM_CNTRL1, STB0899_OFF0_CSM_CNTRL1, csm1);

				पूर्णांकernal->status = stb0899_dvbs2_get_fec_status(state, FecLockTime);
				i++;
			पूर्ण
		पूर्ण

		अगर ((((10 * पूर्णांकernal->master_clk) / (पूर्णांकernal->srate / 10)) <= 410) &&
		      (INRANGE(STB0899_QPSK_12, modcod, STB0899_QPSK_35)) &&
		      (pilots == 1)) अणु

			/* Equalizer Disable update	 */
			reg = STB0899_READ_S2REG(STB0899_S2DEMOD, EQ_CNTRL);
			STB0899_SETFIELD_VAL(EQ_DISABLE_UPDATE, reg, 1);
			stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_EQ_CNTRL, STB0899_OFF0_EQ_CNTRL, reg);
		पूर्ण

		/* slow करोwn the Equalizer once locked	*/
		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, EQ_CNTRL);
		STB0899_SETFIELD_VAL(EQ_SHIFT, reg, 0x02);
		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_EQ_CNTRL, STB0899_OFF0_EQ_CNTRL, reg);

		/* Store संकेत parameters	*/
		offsetfreq = STB0899_READ_S2REG(STB0899_S2DEMOD, CRL_FREQ);

		offsetfreq = sign_extend32(offsetfreq, 29);

		offsetfreq = offsetfreq / ((1 << 30) / 1000);
		offsetfreq *= (पूर्णांकernal->master_clk / 1000000);

		/* store current inversion क्रम next run */
		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_CNTRL2);
		अगर (STB0899_GETFIELD(SPECTRUM_INVERT, reg))
			पूर्णांकernal->inversion = IQ_SWAP_ON;
		अन्यथा
			पूर्णांकernal->inversion = IQ_SWAP_OFF;

		पूर्णांकernal->freq = पूर्णांकernal->freq + offsetfreq;
		पूर्णांकernal->srate = stb0899_dvbs2_get_srate(state);

		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_STAT2);
		पूर्णांकernal->modcod = STB0899_GETFIELD(UWP_DECODE_MOD, reg) >> 2;
		पूर्णांकernal->pilots = STB0899_GETFIELD(UWP_DECODE_MOD, reg) & 0x01;
		पूर्णांकernal->frame_length = (STB0899_GETFIELD(UWP_DECODE_MOD, reg) >> 1) & 0x01;

		 /* Set IF AGC to tracking	*/
		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, IF_AGC_CNTRL);
		STB0899_SETFIELD_VAL(IF_LOOP_GAIN, reg,  3);

		/* अगर QPSK 1/2,QPSK 3/5 or QPSK 2/3 set IF AGC reference to 16 otherwise 32*/
		अगर (INRANGE(STB0899_QPSK_12, पूर्णांकernal->modcod, STB0899_QPSK_23))
			STB0899_SETFIELD_VAL(IF_AGC_REF, reg, 16);

		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_IF_AGC_CNTRL, STB0899_OFF0_IF_AGC_CNTRL, reg);

		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, IF_AGC_CNTRL2);
		STB0899_SETFIELD_VAL(IF_AGC_DUMP_PER, reg, 7);
		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_IF_AGC_CNTRL2, STB0899_OFF0_IF_AGC_CNTRL2, reg);
	पूर्ण

	/* Release Stream Merger Reset		*/
	reg = stb0899_पढ़ो_reg(state, STB0899_TSTRES);
	STB0899_SETFIELD_VAL(FRESRS, reg, 0);
	stb0899_ग_लिखो_reg(state, STB0899_TSTRES, reg);

	वापस पूर्णांकernal->status;
पूर्ण
