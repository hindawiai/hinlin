<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    tda18271-fe.c - driver क्रम the Philips / NXP TDA18271 silicon tuner

    Copyright (C) 2007, 2008 Michael Krufky <mkrufky@linuxtv.org>

*/

#समावेश "tda18271-priv.h"
#समावेश "tda8290.h"

#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>

पूर्णांक tda18271_debug;
module_param_named(debug, tda18271_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debug level (info=1, map=2, reg=4, adv=8, cal=16 (or-able))");

अटल पूर्णांक tda18271_cal_on_startup = -1;
module_param_named(cal, tda18271_cal_on_startup, पूर्णांक, 0644);
MODULE_PARM_DESC(cal, "perform RF tracking filter calibration on startup");

अटल DEFINE_MUTEX(tda18271_list_mutex);
अटल LIST_HEAD(hybrid_tuner_instance_list);

/*---------------------------------------------------------------------*/

अटल पूर्णांक tda18271_toggle_output(काष्ठा dvb_frontend *fe, पूर्णांक standby)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;

	पूर्णांक ret = tda18271_set_standby_mode(fe, standby ? 1 : 0,
			priv->output_opt & TDA18271_OUTPUT_LT_OFF ? 1 : 0,
			priv->output_opt & TDA18271_OUTPUT_XT_OFF ? 1 : 0);

	अगर (tda_fail(ret))
		जाओ fail;

	tda_dbg("%s mode: xtal oscillator %s, slave tuner loop through %s\n",
		standby ? "standby" : "active",
		priv->output_opt & TDA18271_OUTPUT_XT_OFF ? "off" : "on",
		priv->output_opt & TDA18271_OUTPUT_LT_OFF ? "off" : "on");
fail:
	वापस ret;
पूर्ण

/*---------------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक अक्षरge_pump_source(काष्ठा dvb_frontend *fe, पूर्णांक क्रमce)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	वापस tda18271_अक्षरge_pump_source(fe,
					   (priv->role == TDA18271_SLAVE) ?
					   TDA18271_CAL_PLL :
					   TDA18271_MAIN_PLL, क्रमce);
पूर्ण

अटल अंतरभूत व्योम tda18271_set_अगर_notch(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;

	चयन (priv->mode) अणु
	हाल TDA18271_ANALOG:
		regs[R_MPD]  &= ~0x80; /* IF notch = 0 */
		अवरोध;
	हाल TDA18271_DIGITAL:
		regs[R_MPD]  |= 0x80; /* IF notch = 1 */
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक tda18271_channel_configuration(काष्ठा dvb_frontend *fe,
					  काष्ठा tda18271_std_map_item *map,
					  u32 freq, u32 bw)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	पूर्णांक ret;
	u32 N;

	/* update TV broadcast parameters */

	/* set standard */
	regs[R_EP3]  &= ~0x1f; /* clear std bits */
	regs[R_EP3]  |= (map->agc_mode << 3) | map->std;

	अगर (priv->id == TDA18271HDC2) अणु
		/* set rfagc to high speed mode */
		regs[R_EP3] &= ~0x04;
	पूर्ण

	/* set cal mode to normal */
	regs[R_EP4]  &= ~0x03;

	/* update IF output level */
	regs[R_EP4]  &= ~0x1c; /* clear अगर level bits */
	regs[R_EP4]  |= (map->अगर_lvl << 2);

	/* update FM_RFn */
	regs[R_EP4]  &= ~0x80;
	regs[R_EP4]  |= map->fm_rfn << 7;

	/* update rf top / अगर top */
	regs[R_EB22]  = 0x00;
	regs[R_EB22] |= map->rfagc_top;
	ret = tda18271_ग_लिखो_regs(fe, R_EB22, 1);
	अगर (tda_fail(ret))
		जाओ fail;

	/* --------------------------------------------------------------- */

	/* disable Power Level Indicator */
	regs[R_EP1]  |= 0x40;

	/* make sure thermometer is off */
	regs[R_TM]   &= ~0x10;

	/* frequency dependent parameters */

	tda18271_calc_ir_measure(fe, &freq);

	tda18271_calc_bp_filter(fe, &freq);

	tda18271_calc_rf_band(fe, &freq);

	tda18271_calc_gain_taper(fe, &freq);

	/* --------------------------------------------------------------- */

	/* dual tuner and agc1 extra configuration */

	चयन (priv->role) अणु
	हाल TDA18271_MASTER:
		regs[R_EB1]  |= 0x04; /* मुख्य vco */
		अवरोध;
	हाल TDA18271_SLAVE:
		regs[R_EB1]  &= ~0x04; /* cal vco */
		अवरोध;
	पूर्ण

	/* agc1 always active */
	regs[R_EB1]  &= ~0x02;

	/* agc1 has priority on agc2 */
	regs[R_EB1]  &= ~0x01;

	ret = tda18271_ग_लिखो_regs(fe, R_EB1, 1);
	अगर (tda_fail(ret))
		जाओ fail;

	/* --------------------------------------------------------------- */

	N = map->अगर_freq * 1000 + freq;

	चयन (priv->role) अणु
	हाल TDA18271_MASTER:
		tda18271_calc_मुख्य_pll(fe, N);
		tda18271_set_अगर_notch(fe);
		tda18271_ग_लिखो_regs(fe, R_MPD, 4);
		अवरोध;
	हाल TDA18271_SLAVE:
		tda18271_calc_cal_pll(fe, N);
		tda18271_ग_लिखो_regs(fe, R_CPD, 4);

		regs[R_MPD] = regs[R_CPD] & 0x7f;
		tda18271_set_अगर_notch(fe);
		tda18271_ग_लिखो_regs(fe, R_MPD, 1);
		अवरोध;
	पूर्ण

	ret = tda18271_ग_लिखो_regs(fe, R_TM, 7);
	अगर (tda_fail(ret))
		जाओ fail;

	/* क्रमce अक्षरge pump source */
	अक्षरge_pump_source(fe, 1);

	msleep(1);

	/* वापस pll to normal operation */
	अक्षरge_pump_source(fe, 0);

	msleep(20);

	अगर (priv->id == TDA18271HDC2) अणु
		/* set rfagc to normal speed mode */
		अगर (map->fm_rfn)
			regs[R_EP3] &= ~0x04;
		अन्यथा
			regs[R_EP3] |= 0x04;
		ret = tda18271_ग_लिखो_regs(fe, R_EP3, 1);
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18271_पढ़ो_thermometer(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	पूर्णांक पंचांग;

	/* चयन thermometer on */
	regs[R_TM]   |= 0x10;
	tda18271_ग_लिखो_regs(fe, R_TM, 1);

	/* पढ़ो thermometer info */
	tda18271_पढ़ो_regs(fe);

	अगर ((((regs[R_TM] & 0x0f) == 0x00) && ((regs[R_TM] & 0x20) == 0x20)) ||
	    (((regs[R_TM] & 0x0f) == 0x08) && ((regs[R_TM] & 0x20) == 0x00))) अणु

		अगर ((regs[R_TM] & 0x20) == 0x20)
			regs[R_TM] &= ~0x20;
		अन्यथा
			regs[R_TM] |= 0x20;

		tda18271_ग_लिखो_regs(fe, R_TM, 1);

		msleep(10); /* temperature sensing */

		/* पढ़ो thermometer info */
		tda18271_पढ़ो_regs(fe);
	पूर्ण

	पंचांग = tda18271_lookup_thermometer(fe);

	/* चयन thermometer off */
	regs[R_TM]   &= ~0x10;
	tda18271_ग_लिखो_regs(fe, R_TM, 1);

	/* set CAL mode to normal */
	regs[R_EP4]  &= ~0x03;
	tda18271_ग_लिखो_regs(fe, R_EP4, 1);

	वापस पंचांग;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक tda18271c2_rf_tracking_filters_correction(काष्ठा dvb_frontend *fe,
						     u32 freq)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	काष्ठा tda18271_rf_tracking_filter_cal *map = priv->rf_cal_state;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	पूर्णांक i, ret;
	u8 पंचांग_current, dc_over_dt, rf_tab;
	s32 rfcal_comp, approx;

	/* घातer up */
	ret = tda18271_set_standby_mode(fe, 0, 0, 0);
	अगर (tda_fail(ret))
		जाओ fail;

	/* पढ़ो die current temperature */
	पंचांग_current = tda18271_पढ़ो_thermometer(fe);

	/* frequency dependent parameters */

	tda18271_calc_rf_cal(fe, &freq);
	rf_tab = regs[R_EB14];

	i = tda18271_lookup_rf_band(fe, &freq, शून्य);
	अगर (tda_fail(i))
		वापस i;

	अगर ((0 == map[i].rf3) || (freq / 1000 < map[i].rf2)) अणु
		approx = map[i].rf_a1 * (s32)(freq / 1000 - map[i].rf1) +
			map[i].rf_b1 + rf_tab;
	पूर्ण अन्यथा अणु
		approx = map[i].rf_a2 * (s32)(freq / 1000 - map[i].rf2) +
			map[i].rf_b2 + rf_tab;
	पूर्ण

	अगर (approx < 0)
		approx = 0;
	अगर (approx > 255)
		approx = 255;

	tda18271_lookup_map(fe, RF_CAL_DC_OVER_DT, &freq, &dc_over_dt);

	/* calculate temperature compensation */
	rfcal_comp = dc_over_dt * (s32)(पंचांग_current - priv->पंचांग_rfcal) / 1000;

	regs[R_EB14] = (अचिन्हित अक्षर)(approx + rfcal_comp);
	ret = tda18271_ग_लिखो_regs(fe, R_EB14, 1);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18271_por(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	पूर्णांक ret;

	/* घातer up detector 1 */
	regs[R_EB12] &= ~0x20;
	ret = tda18271_ग_लिखो_regs(fe, R_EB12, 1);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_EB18] &= ~0x80; /* turn agc1 loop on */
	regs[R_EB18] &= ~0x03; /* set agc1_gain to  6 dB */
	ret = tda18271_ग_लिखो_regs(fe, R_EB18, 1);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_EB21] |= 0x03; /* set agc2_gain to -6 dB */

	/* POR mode */
	ret = tda18271_set_standby_mode(fe, 1, 0, 0);
	अगर (tda_fail(ret))
		जाओ fail;

	/* disable 1.5 MHz low pass filter */
	regs[R_EB23] &= ~0x04; /* क्रमcelp_fc2_en = 0 */
	regs[R_EB23] &= ~0x02; /* XXX: lp_fc[2] = 0 */
	ret = tda18271_ग_लिखो_regs(fe, R_EB21, 3);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18271_calibrate_rf(काष्ठा dvb_frontend *fe, u32 freq)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	u32 N;

	/* set CAL mode to normal */
	regs[R_EP4]  &= ~0x03;
	tda18271_ग_लिखो_regs(fe, R_EP4, 1);

	/* चयन off agc1 */
	regs[R_EP3]  |= 0x40; /* sm_lt = 1 */

	regs[R_EB18] |= 0x03; /* set agc1_gain to 15 dB */
	tda18271_ग_लिखो_regs(fe, R_EB18, 1);

	/* frequency dependent parameters */

	tda18271_calc_bp_filter(fe, &freq);
	tda18271_calc_gain_taper(fe, &freq);
	tda18271_calc_rf_band(fe, &freq);
	tda18271_calc_km(fe, &freq);

	tda18271_ग_लिखो_regs(fe, R_EP1, 3);
	tda18271_ग_लिखो_regs(fe, R_EB13, 1);

	/* मुख्य pll अक्षरge pump source */
	tda18271_अक्षरge_pump_source(fe, TDA18271_MAIN_PLL, 1);

	/* cal pll अक्षरge pump source */
	tda18271_अक्षरge_pump_source(fe, TDA18271_CAL_PLL, 1);

	/* क्रमce dcdc converter to 0 V */
	regs[R_EB14] = 0x00;
	tda18271_ग_लिखो_regs(fe, R_EB14, 1);

	/* disable plls lock */
	regs[R_EB20] &= ~0x20;
	tda18271_ग_लिखो_regs(fe, R_EB20, 1);

	/* set CAL mode to RF tracking filter calibration */
	regs[R_EP4]  |= 0x03;
	tda18271_ग_लिखो_regs(fe, R_EP4, 2);

	/* --------------------------------------------------------------- */

	/* set the पूर्णांकernal calibration संकेत */
	N = freq;

	tda18271_calc_cal_pll(fe, N);
	tda18271_ग_लिखो_regs(fe, R_CPD, 4);

	/* करोwnconvert पूर्णांकernal calibration */
	N += 1000000;

	tda18271_calc_मुख्य_pll(fe, N);
	tda18271_ग_लिखो_regs(fe, R_MPD, 4);

	msleep(5);

	tda18271_ग_लिखो_regs(fe, R_EP2, 1);
	tda18271_ग_लिखो_regs(fe, R_EP1, 1);
	tda18271_ग_लिखो_regs(fe, R_EP2, 1);
	tda18271_ग_लिखो_regs(fe, R_EP1, 1);

	/* --------------------------------------------------------------- */

	/* normal operation क्रम the मुख्य pll */
	tda18271_अक्षरge_pump_source(fe, TDA18271_MAIN_PLL, 0);

	/* normal operation क्रम the cal pll  */
	tda18271_अक्षरge_pump_source(fe, TDA18271_CAL_PLL, 0);

	msleep(10); /* plls locking */

	/* launch the rf tracking filters calibration */
	regs[R_EB20]  |= 0x20;
	tda18271_ग_लिखो_regs(fe, R_EB20, 1);

	msleep(60); /* calibration */

	/* --------------------------------------------------------------- */

	/* set CAL mode to normal */
	regs[R_EP4]  &= ~0x03;

	/* चयन on agc1 */
	regs[R_EP3]  &= ~0x40; /* sm_lt = 0 */

	regs[R_EB18] &= ~0x03; /* set agc1_gain to  6 dB */
	tda18271_ग_लिखो_regs(fe, R_EB18, 1);

	tda18271_ग_लिखो_regs(fe, R_EP3, 2);

	/* synchronization */
	tda18271_ग_लिखो_regs(fe, R_EP1, 1);

	/* get calibration result */
	tda18271_पढ़ो_extended(fe);

	वापस regs[R_EB14];
पूर्ण

अटल पूर्णांक tda18271_घातerscan(काष्ठा dvb_frontend *fe,
			      u32 *freq_in, u32 *freq_out)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	पूर्णांक sgn, bcal, count, रुको, ret;
	u8 cid_target;
	u16 count_limit;
	u32 freq;

	freq = *freq_in;

	tda18271_calc_rf_band(fe, &freq);
	tda18271_calc_rf_cal(fe, &freq);
	tda18271_calc_gain_taper(fe, &freq);
	tda18271_lookup_cid_target(fe, &freq, &cid_target, &count_limit);

	tda18271_ग_लिखो_regs(fe, R_EP2, 1);
	tda18271_ग_लिखो_regs(fe, R_EB14, 1);

	/* करोwnconvert frequency */
	freq += 1000000;

	tda18271_calc_मुख्य_pll(fe, freq);
	tda18271_ग_लिखो_regs(fe, R_MPD, 4);

	msleep(5); /* pll locking */

	/* detection mode */
	regs[R_EP4]  &= ~0x03;
	regs[R_EP4]  |= 0x01;
	tda18271_ग_लिखो_regs(fe, R_EP4, 1);

	/* launch घातer detection measurement */
	tda18271_ग_लिखो_regs(fe, R_EP2, 1);

	/* पढ़ो घातer detection info, stored in EB10 */
	ret = tda18271_पढ़ो_extended(fe);
	अगर (tda_fail(ret))
		वापस ret;

	/* algorithm initialization */
	sgn = 1;
	*freq_out = *freq_in;
	bcal = 0;
	count = 0;
	रुको = false;

	जबतक ((regs[R_EB10] & 0x3f) < cid_target) अणु
		/* करोwnconvert updated freq to 1 MHz */
		freq = *freq_in + (sgn * count) + 1000000;

		tda18271_calc_मुख्य_pll(fe, freq);
		tda18271_ग_लिखो_regs(fe, R_MPD, 4);

		अगर (रुको) अणु
			msleep(5); /* pll locking */
			रुको = false;
		पूर्ण अन्यथा
			udelay(100); /* pll locking */

		/* launch घातer detection measurement */
		tda18271_ग_लिखो_regs(fe, R_EP2, 1);

		/* पढ़ो घातer detection info, stored in EB10 */
		ret = tda18271_पढ़ो_extended(fe);
		अगर (tda_fail(ret))
			वापस ret;

		count += 200;

		अगर (count <= count_limit)
			जारी;

		अगर (sgn <= 0)
			अवरोध;

		sgn = -1 * sgn;
		count = 200;
		रुको = true;
	पूर्ण

	अगर ((regs[R_EB10] & 0x3f) >= cid_target) अणु
		bcal = 1;
		*freq_out = freq - 1000000;
	पूर्ण अन्यथा
		bcal = 0;

	tda_cal("bcal = %d, freq_in = %d, freq_out = %d (freq = %d)\n",
		bcal, *freq_in, *freq_out, freq);

	वापस bcal;
पूर्ण

अटल पूर्णांक tda18271_घातerscan_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	पूर्णांक ret;

	/* set standard to digital */
	regs[R_EP3]  &= ~0x1f; /* clear std bits */
	regs[R_EP3]  |= 0x12;

	/* set cal mode to normal */
	regs[R_EP4]  &= ~0x03;

	/* update IF output level */
	regs[R_EP4]  &= ~0x1c; /* clear अगर level bits */

	ret = tda18271_ग_लिखो_regs(fe, R_EP3, 2);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_EB18] &= ~0x03; /* set agc1_gain to   6 dB */
	ret = tda18271_ग_लिखो_regs(fe, R_EB18, 1);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_EB21] &= ~0x03; /* set agc2_gain to -15 dB */

	/* 1.5 MHz low pass filter */
	regs[R_EB23] |= 0x04; /* क्रमcelp_fc2_en = 1 */
	regs[R_EB23] |= 0x02; /* lp_fc[2] = 1 */

	ret = tda18271_ग_लिखो_regs(fe, R_EB21, 3);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18271_rf_tracking_filters_init(काष्ठा dvb_frontend *fe, u32 freq)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	काष्ठा tda18271_rf_tracking_filter_cal *map = priv->rf_cal_state;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	पूर्णांक bcal, rf, i;
	s32 भागisor, भागidend;
#घोषणा RF1 0
#घोषणा RF2 1
#घोषणा RF3 2
	u32 rf_शेष[3];
	u32 rf_freq[3];
	s32 prog_cal[3];
	s32 prog_tab[3];

	i = tda18271_lookup_rf_band(fe, &freq, शून्य);

	अगर (tda_fail(i))
		वापस i;

	rf_शेष[RF1] = 1000 * map[i].rf1_def;
	rf_शेष[RF2] = 1000 * map[i].rf2_def;
	rf_शेष[RF3] = 1000 * map[i].rf3_def;

	क्रम (rf = RF1; rf <= RF3; rf++) अणु
		अगर (0 == rf_शेष[rf])
			वापस 0;
		tda_cal("freq = %d, rf = %d\n", freq, rf);

		/* look क्रम optimized calibration frequency */
		bcal = tda18271_घातerscan(fe, &rf_शेष[rf], &rf_freq[rf]);
		अगर (tda_fail(bcal))
			वापस bcal;

		tda18271_calc_rf_cal(fe, &rf_freq[rf]);
		prog_tab[rf] = (s32)regs[R_EB14];

		अगर (1 == bcal)
			prog_cal[rf] =
				(s32)tda18271_calibrate_rf(fe, rf_freq[rf]);
		अन्यथा
			prog_cal[rf] = prog_tab[rf];

		चयन (rf) अणु
		हाल RF1:
			map[i].rf_a1 = 0;
			map[i].rf_b1 = (prog_cal[RF1] - prog_tab[RF1]);
			map[i].rf1   = rf_freq[RF1] / 1000;
			अवरोध;
		हाल RF2:
			भागidend = (prog_cal[RF2] - prog_tab[RF2] -
				    prog_cal[RF1] + prog_tab[RF1]);
			भागisor = (s32)(rf_freq[RF2] - rf_freq[RF1]) / 1000;
			map[i].rf_a1 = (भागidend / भागisor);
			map[i].rf2   = rf_freq[RF2] / 1000;
			अवरोध;
		हाल RF3:
			भागidend = (prog_cal[RF3] - prog_tab[RF3] -
				    prog_cal[RF2] + prog_tab[RF2]);
			भागisor = (s32)(rf_freq[RF3] - rf_freq[RF2]) / 1000;
			map[i].rf_a2 = (भागidend / भागisor);
			map[i].rf_b2 = (prog_cal[RF2] - prog_tab[RF2]);
			map[i].rf3   = rf_freq[RF3] / 1000;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda18271_calc_rf_filter_curve(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	tda_info("performing RF tracking filter calibration\n");

	/* रुको क्रम die temperature stabilization */
	msleep(200);

	ret = tda18271_घातerscan_init(fe);
	अगर (tda_fail(ret))
		जाओ fail;

	/* rf band calibration */
	क्रम (i = 0; priv->rf_cal_state[i].rfmax != 0; i++) अणु
		ret =
		tda18271_rf_tracking_filters_init(fe, 1000 *
						  priv->rf_cal_state[i].rfmax);
		अगर (tda_fail(ret))
			जाओ fail;
	पूर्ण

	priv->पंचांग_rfcal = tda18271_पढ़ो_thermometer(fe);
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक tda18271c2_rf_cal_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	पूर्णांक ret;

	/* test RF_CAL_OK to see अगर we need init */
	अगर ((regs[R_EP1] & 0x10) == 0)
		priv->cal_initialized = false;

	अगर (priv->cal_initialized)
		वापस 0;

	ret = tda18271_calc_rf_filter_curve(fe);
	अगर (tda_fail(ret))
		जाओ fail;

	ret = tda18271_por(fe);
	अगर (tda_fail(ret))
		जाओ fail;

	tda_info("RF tracking filter calibration complete\n");

	priv->cal_initialized = true;
	जाओ end;
fail:
	tda_info("RF tracking filter calibration failed!\n");
end:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18271c1_rf_tracking_filter_calibration(काष्ठा dvb_frontend *fe,
						     u32 freq, u32 bw)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	पूर्णांक ret;
	u32 N = 0;

	/* calculate bp filter */
	tda18271_calc_bp_filter(fe, &freq);
	tda18271_ग_लिखो_regs(fe, R_EP1, 1);

	regs[R_EB4]  &= 0x07;
	regs[R_EB4]  |= 0x60;
	tda18271_ग_लिखो_regs(fe, R_EB4, 1);

	regs[R_EB7]   = 0x60;
	tda18271_ग_लिखो_regs(fe, R_EB7, 1);

	regs[R_EB14]  = 0x00;
	tda18271_ग_लिखो_regs(fe, R_EB14, 1);

	regs[R_EB20]  = 0xcc;
	tda18271_ग_लिखो_regs(fe, R_EB20, 1);

	/* set cal mode to RF tracking filter calibration */
	regs[R_EP4]  |= 0x03;

	/* calculate cal pll */

	चयन (priv->mode) अणु
	हाल TDA18271_ANALOG:
		N = freq - 1250000;
		अवरोध;
	हाल TDA18271_DIGITAL:
		N = freq + bw / 2;
		अवरोध;
	पूर्ण

	tda18271_calc_cal_pll(fe, N);

	/* calculate मुख्य pll */

	चयन (priv->mode) अणु
	हाल TDA18271_ANALOG:
		N = freq - 250000;
		अवरोध;
	हाल TDA18271_DIGITAL:
		N = freq + bw / 2 + 1000000;
		अवरोध;
	पूर्ण

	tda18271_calc_मुख्य_pll(fe, N);

	ret = tda18271_ग_लिखो_regs(fe, R_EP3, 11);
	अगर (tda_fail(ret))
		वापस ret;

	msleep(5); /* RF tracking filter calibration initialization */

	/* search क्रम K,M,CO क्रम RF calibration */
	tda18271_calc_km(fe, &freq);
	tda18271_ग_लिखो_regs(fe, R_EB13, 1);

	/* search क्रम rf band */
	tda18271_calc_rf_band(fe, &freq);

	/* search क्रम gain taper */
	tda18271_calc_gain_taper(fe, &freq);

	tda18271_ग_लिखो_regs(fe, R_EP2, 1);
	tda18271_ग_लिखो_regs(fe, R_EP1, 1);
	tda18271_ग_लिखो_regs(fe, R_EP2, 1);
	tda18271_ग_लिखो_regs(fe, R_EP1, 1);

	regs[R_EB4]  &= 0x07;
	regs[R_EB4]  |= 0x40;
	tda18271_ग_लिखो_regs(fe, R_EB4, 1);

	regs[R_EB7]   = 0x40;
	tda18271_ग_लिखो_regs(fe, R_EB7, 1);
	msleep(10); /* pll locking */

	regs[R_EB20]  = 0xec;
	tda18271_ग_लिखो_regs(fe, R_EB20, 1);
	msleep(60); /* RF tracking filter calibration completion */

	regs[R_EP4]  &= ~0x03; /* set cal mode to normal */
	tda18271_ग_लिखो_regs(fe, R_EP4, 1);

	tda18271_ग_लिखो_regs(fe, R_EP1, 1);

	/* RF tracking filter correction क्रम VHF_Low band */
	अगर (0 == tda18271_calc_rf_cal(fe, &freq))
		tda18271_ग_लिखो_regs(fe, R_EB14, 1);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक tda18271_ir_cal_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	पूर्णांक ret;

	ret = tda18271_पढ़ो_regs(fe);
	अगर (tda_fail(ret))
		जाओ fail;

	/* test IR_CAL_OK to see अगर we need init */
	अगर ((regs[R_EP1] & 0x08) == 0)
		ret = tda18271_init_regs(fe);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18271_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	mutex_lock(&priv->lock);

	/* full घातer up */
	ret = tda18271_set_standby_mode(fe, 0, 0, 0);
	अगर (tda_fail(ret))
		जाओ fail;

	/* initialization */
	ret = tda18271_ir_cal_init(fe);
	अगर (tda_fail(ret))
		जाओ fail;

	अगर (priv->id == TDA18271HDC2)
		tda18271c2_rf_cal_init(fe);
fail:
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tda18271_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	mutex_lock(&priv->lock);

	/* enter standby mode, with required output features enabled */
	ret = tda18271_toggle_output(fe, 1);

	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक tda18271_agc(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	पूर्णांक ret = 0;

	चयन (priv->config) अणु
	हाल TDA8290_LNA_OFF:
		/* no बाह्यal agc configuration required */
		अगर (tda18271_debug & DBG_ADV)
			tda_dbg("no agc configuration provided\n");
		अवरोध;
	हाल TDA8290_LNA_ON_BRIDGE:
		/* चयन with GPIO of saa713x */
		tda_dbg("invoking callback\n");
		अगर (fe->callback)
			ret = fe->callback(priv->i2c_props.adap->algo_data,
					   DVB_FRONTEND_COMPONENT_TUNER,
					   TDA18271_CALLBACK_CMD_AGC_ENABLE,
					   priv->mode);
		अवरोध;
	हाल TDA8290_LNA_GP0_HIGH_ON:
	हाल TDA8290_LNA_GP0_HIGH_OFF:
	शेष:
		/* n/a - currently not supported */
		tda_err("unsupported configuration: %d\n", priv->config);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tda18271_tune(काष्ठा dvb_frontend *fe,
			 काष्ठा tda18271_std_map_item *map, u32 freq, u32 bw)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	tda_dbg("freq = %d, ifc = %d, bw = %d, agc_mode = %d, std = %d\n",
		freq, map->अगर_freq, bw, map->agc_mode, map->std);

	ret = tda18271_agc(fe);
	अगर (tda_fail(ret))
		tda_warn("failed to configure agc\n");

	ret = tda18271_init(fe);
	अगर (tda_fail(ret))
		जाओ fail;

	mutex_lock(&priv->lock);

	चयन (priv->id) अणु
	हाल TDA18271HDC1:
		tda18271c1_rf_tracking_filter_calibration(fe, freq, bw);
		अवरोध;
	हाल TDA18271HDC2:
		tda18271c2_rf_tracking_filters_correction(fe, freq);
		अवरोध;
	पूर्ण
	ret = tda18271_channel_configuration(fe, map, freq, bw);

	mutex_unlock(&priv->lock);
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक tda18271_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys = c->delivery_प्रणाली;
	u32 bw = c->bandwidth_hz;
	u32 freq = c->frequency;
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	काष्ठा tda18271_std_map *std_map = &priv->std;
	काष्ठा tda18271_std_map_item *map;
	पूर्णांक ret;

	priv->mode = TDA18271_DIGITAL;

	चयन (delsys) अणु
	हाल SYS_ATSC:
		map = &std_map->atsc_6;
		bw = 6000000;
		अवरोध;
	हाल SYS_ISDBT:
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		अगर (bw <= 6000000) अणु
			map = &std_map->dvbt_6;
		पूर्ण अन्यथा अगर (bw <= 7000000) अणु
			map = &std_map->dvbt_7;
		पूर्ण अन्यथा अणु
			map = &std_map->dvbt_8;
		पूर्ण
		अवरोध;
	हाल SYS_DVBC_ANNEX_B:
		bw = 6000000;
		fallthrough;
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_C:
		अगर (bw <= 6000000) अणु
			map = &std_map->qam_6;
		पूर्ण अन्यथा अगर (bw <= 7000000) अणु
			map = &std_map->qam_7;
		पूर्ण अन्यथा अणु
			map = &std_map->qam_8;
		पूर्ण
		अवरोध;
	शेष:
		tda_warn("modulation type not supported!\n");
		वापस -EINVAL;
	पूर्ण

	/* When tuning digital, the analog demod must be tri-stated */
	अगर (fe->ops.analog_ops.standby)
		fe->ops.analog_ops.standby(fe);

	ret = tda18271_tune(fe, map, freq, bw);

	अगर (tda_fail(ret))
		जाओ fail;

	priv->अगर_freq   = map->अगर_freq;
	priv->frequency = freq;
	priv->bandwidth = bw;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक tda18271_set_analog_params(काष्ठा dvb_frontend *fe,
				      काष्ठा analog_parameters *params)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	काष्ठा tda18271_std_map *std_map = &priv->std;
	काष्ठा tda18271_std_map_item *map;
	अक्षर *mode;
	पूर्णांक ret;
	u32 freq = params->frequency * 125 *
		((params->mode == V4L2_TUNER_RADIO) ? 1 : 1000) / 2;

	priv->mode = TDA18271_ANALOG;

	अगर (params->mode == V4L2_TUNER_RADIO) अणु
		map = &std_map->fm_radio;
		mode = "fm";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_MN) अणु
		map = &std_map->atv_mn;
		mode = "MN";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_B) अणु
		map = &std_map->atv_b;
		mode = "B";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_GH) अणु
		map = &std_map->atv_gh;
		mode = "GH";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_PAL_I) अणु
		map = &std_map->atv_i;
		mode = "I";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_DK) अणु
		map = &std_map->atv_dk;
		mode = "DK";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_SECAM_L) अणु
		map = &std_map->atv_l;
		mode = "L";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_SECAM_LC) अणु
		map = &std_map->atv_lc;
		mode = "L'";
	पूर्ण अन्यथा अणु
		map = &std_map->atv_i;
		mode = "xx";
	पूर्ण

	tda_dbg("setting tda18271 to system %s\n", mode);

	ret = tda18271_tune(fe, map, freq, 0);

	अगर (tda_fail(ret))
		जाओ fail;

	priv->अगर_freq   = map->अगर_freq;
	priv->frequency = freq;
	priv->bandwidth = 0;
fail:
	वापस ret;
पूर्ण

अटल व्योम tda18271_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;

	mutex_lock(&tda18271_list_mutex);

	अगर (priv)
		hybrid_tuner_release_state(priv);

	mutex_unlock(&tda18271_list_mutex);

	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक tda18271_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक tda18271_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	*bandwidth = priv->bandwidth;
	वापस 0;
पूर्ण

अटल पूर्णांक tda18271_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	*frequency = (u32)priv->अगर_freq * 1000;
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

#घोषणा tda18271_update_std(std_cfg, name) करो अणु				\
	अगर (map->std_cfg.अगर_freq +					\
		map->std_cfg.agc_mode + map->std_cfg.std +		\
		map->std_cfg.अगर_lvl + map->std_cfg.rfagc_top > 0) अणु	\
		tda_dbg("Using custom std config for %s\n", name);	\
		स_नकल(&std->std_cfg, &map->std_cfg,			\
			माप(काष्ठा tda18271_std_map_item));		\
	पूर्ण पूर्ण जबतक (0)

#घोषणा tda18271_dump_std_item(std_cfg, name) करो अणु			\
	tda_dbg("(%s) if_freq = %d, agc_mode = %d, std = %d, "		\
		"if_lvl = %d, rfagc_top = 0x%02x\n",			\
		name, std->std_cfg.अगर_freq,				\
		std->std_cfg.agc_mode, std->std_cfg.std,		\
		std->std_cfg.अगर_lvl, std->std_cfg.rfagc_top);		\
	पूर्ण जबतक (0)

अटल पूर्णांक tda18271_dump_std_map(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	काष्ठा tda18271_std_map *std = &priv->std;

	tda_dbg("========== STANDARD MAP SETTINGS ==========\n");
	tda18271_dump_std_item(fm_radio, "  fm  ");
	tda18271_dump_std_item(atv_b,  "atv b ");
	tda18271_dump_std_item(atv_dk, "atv dk");
	tda18271_dump_std_item(atv_gh, "atv gh");
	tda18271_dump_std_item(atv_i,  "atv i ");
	tda18271_dump_std_item(atv_l,  "atv l ");
	tda18271_dump_std_item(atv_lc, "atv l'");
	tda18271_dump_std_item(atv_mn, "atv mn");
	tda18271_dump_std_item(atsc_6, "atsc 6");
	tda18271_dump_std_item(dvbt_6, "dvbt 6");
	tda18271_dump_std_item(dvbt_7, "dvbt 7");
	tda18271_dump_std_item(dvbt_8, "dvbt 8");
	tda18271_dump_std_item(qam_6,  "qam 6 ");
	tda18271_dump_std_item(qam_7,  "qam 7 ");
	tda18271_dump_std_item(qam_8,  "qam 8 ");

	वापस 0;
पूर्ण

अटल पूर्णांक tda18271_update_std_map(काष्ठा dvb_frontend *fe,
				   काष्ठा tda18271_std_map *map)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	काष्ठा tda18271_std_map *std = &priv->std;

	अगर (!map)
		वापस -EINVAL;

	tda18271_update_std(fm_radio, "fm");
	tda18271_update_std(atv_b,  "atv b");
	tda18271_update_std(atv_dk, "atv dk");
	tda18271_update_std(atv_gh, "atv gh");
	tda18271_update_std(atv_i,  "atv i");
	tda18271_update_std(atv_l,  "atv l");
	tda18271_update_std(atv_lc, "atv l'");
	tda18271_update_std(atv_mn, "atv mn");
	tda18271_update_std(atsc_6, "atsc 6");
	tda18271_update_std(dvbt_6, "dvbt 6");
	tda18271_update_std(dvbt_7, "dvbt 7");
	tda18271_update_std(dvbt_8, "dvbt 8");
	tda18271_update_std(qam_6,  "qam 6");
	tda18271_update_std(qam_7,  "qam 7");
	tda18271_update_std(qam_8,  "qam 8");

	वापस 0;
पूर्ण

अटल पूर्णांक tda18271_get_id(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	अक्षर *name;
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	ret = tda18271_पढ़ो_regs(fe);
	mutex_unlock(&priv->lock);

	अगर (ret) अणु
		tda_info("Error reading device ID @ %d-%04x, bailing out.\n",
			 i2c_adapter_id(priv->i2c_props.adap),
			 priv->i2c_props.addr);
		वापस -EIO;
	पूर्ण

	चयन (regs[R_ID] & 0x7f) अणु
	हाल 3:
		name = "TDA18271HD/C1";
		priv->id = TDA18271HDC1;
		अवरोध;
	हाल 4:
		name = "TDA18271HD/C2";
		priv->id = TDA18271HDC2;
		अवरोध;
	शेष:
		tda_info("Unknown device (%i) detected @ %d-%04x, device not supported.\n",
			 regs[R_ID], i2c_adapter_id(priv->i2c_props.adap),
			 priv->i2c_props.addr);
		वापस -EINVAL;
	पूर्ण

	tda_info("%s detected @ %d-%04x\n", name,
		 i2c_adapter_id(priv->i2c_props.adap), priv->i2c_props.addr);

	वापस 0;
पूर्ण

अटल पूर्णांक tda18271_setup_configuration(काष्ठा dvb_frontend *fe,
					काष्ठा tda18271_config *cfg)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;

	priv->gate = (cfg) ? cfg->gate : TDA18271_GATE_AUTO;
	priv->role = (cfg) ? cfg->role : TDA18271_MASTER;
	priv->config = (cfg) ? cfg->config : 0;
	priv->small_i2c = (cfg) ?
		cfg->small_i2c : TDA18271_39_BYTE_CHUNK_INIT;
	priv->output_opt = (cfg) ?
		cfg->output_opt : TDA18271_OUTPUT_LT_XT_ON;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक tda18271_need_cal_on_startup(काष्ठा tda18271_config *cfg)
अणु
	/* tda18271_cal_on_startup == -1 when cal module option is unset */
	वापस ((tda18271_cal_on_startup == -1) ?
		/* honor configuration setting */
		((cfg) && (cfg->rf_cal_on_startup)) :
		/* module option overrides configuration setting */
		(tda18271_cal_on_startup)) ? 1 : 0;
पूर्ण

अटल पूर्णांक tda18271_set_config(काष्ठा dvb_frontend *fe, व्योम *priv_cfg)
अणु
	काष्ठा tda18271_config *cfg = (काष्ठा tda18271_config *) priv_cfg;

	tda18271_setup_configuration(fe, cfg);

	अगर (tda18271_need_cal_on_startup(cfg))
		tda18271_init(fe);

	/* override शेष std map with values in config काष्ठा */
	अगर ((cfg) && (cfg->std_map))
		tda18271_update_std_map(fe, cfg->std_map);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tda18271_tuner_ops = अणु
	.info = अणु
		.name = "NXP TDA18271HD",
		.frequency_min_hz  =  45 * MHz,
		.frequency_max_hz  = 864 * MHz,
		.frequency_step_hz = 62500
	पूर्ण,
	.init              = tda18271_init,
	.sleep             = tda18271_sleep,
	.set_params        = tda18271_set_params,
	.set_analog_params = tda18271_set_analog_params,
	.release           = tda18271_release,
	.set_config        = tda18271_set_config,
	.get_frequency     = tda18271_get_frequency,
	.get_bandwidth     = tda18271_get_bandwidth,
	.get_अगर_frequency  = tda18271_get_अगर_frequency,
पूर्ण;

काष्ठा dvb_frontend *tda18271_attach(काष्ठा dvb_frontend *fe, u8 addr,
				     काष्ठा i2c_adapter *i2c,
				     काष्ठा tda18271_config *cfg)
अणु
	काष्ठा tda18271_priv *priv = शून्य;
	पूर्णांक instance, ret;

	mutex_lock(&tda18271_list_mutex);

	instance = hybrid_tuner_request_state(काष्ठा tda18271_priv, priv,
					      hybrid_tuner_instance_list,
					      i2c, addr, "tda18271");
	चयन (instance) अणु
	हाल 0:
		जाओ fail;
	हाल 1:
		/* new tuner instance */
		fe->tuner_priv = priv;

		tda18271_setup_configuration(fe, cfg);

		priv->cal_initialized = false;
		mutex_init(&priv->lock);

		ret = tda18271_get_id(fe);
		अगर (tda_fail(ret))
			जाओ fail;

		ret = tda18271_assign_map_layout(fe);
		अगर (tda_fail(ret))
			जाओ fail;

		/* अगर delay_cal is set, delay IR & RF calibration until init()
		 * module option 'cal' overrides this delay */
		अगर ((cfg->delay_cal) && (!tda18271_need_cal_on_startup(cfg)))
			अवरोध;

		mutex_lock(&priv->lock);
		tda18271_init_regs(fe);

		अगर ((tda18271_need_cal_on_startup(cfg)) &&
		    (priv->id == TDA18271HDC2))
			tda18271c2_rf_cal_init(fe);

		/* enter standby mode, with required output features enabled */
		ret = tda18271_toggle_output(fe, 1);
		tda_fail(ret);

		mutex_unlock(&priv->lock);
		अवरोध;
	शेष:
		/* existing tuner instance */
		fe->tuner_priv = priv;

		/* allow dvb driver to override configuration settings */
		अगर (cfg) अणु
			अगर (cfg->gate != TDA18271_GATE_ANALOG)
				priv->gate = cfg->gate;
			अगर (cfg->role)
				priv->role = cfg->role;
			अगर (cfg->config)
				priv->config = cfg->config;
			अगर (cfg->small_i2c)
				priv->small_i2c = cfg->small_i2c;
			अगर (cfg->output_opt)
				priv->output_opt = cfg->output_opt;
			अगर (cfg->std_map)
				tda18271_update_std_map(fe, cfg->std_map);
		पूर्ण
		अगर (tda18271_need_cal_on_startup(cfg))
			tda18271_init(fe);
		अवरोध;
	पूर्ण

	/* override शेष std map with values in config काष्ठा */
	अगर ((cfg) && (cfg->std_map))
		tda18271_update_std_map(fe, cfg->std_map);

	mutex_unlock(&tda18271_list_mutex);

	स_नकल(&fe->ops.tuner_ops, &tda18271_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	अगर (tda18271_debug & (DBG_MAP | DBG_ADV))
		tda18271_dump_std_map(fe);

	वापस fe;
fail:
	mutex_unlock(&tda18271_list_mutex);

	tda18271_release(fe);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(tda18271_attach);
MODULE_DESCRIPTION("NXP TDA18271HD analog / digital tuner driver");
MODULE_AUTHOR("Michael Krufky <mkrufky@linuxtv.org>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.4");
