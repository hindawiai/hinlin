<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * i2c tv tuner chip device type database.
 *
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <media/tuner.h>
#समावेश <media/tuner-types.h>

/* ---------------------------------------------------------------------- */

/*
 *	The भग्नs in the tuner काष्ठा are computed at compile समय
 *	by gcc and cast back to पूर्णांकegers. Thus we करोn't violate the
 *	"no float in kernel" rule.
 *
 *	A tuner_range may be referenced by multiple tuner_params काष्ठाs.
 *	There are many duplicates in here. Reusing tuner_range काष्ठाs,
 *	rather than defining new ones क्रम each tuner, will cut करोwn on
 *	memory usage, and is preferred when possible.
 *
 *	Each tuner_params array may contain one or more elements, one
 *	क्रम each video standard.
 *
 *	FIXME: tuner_params काष्ठा contains an element, tda988x. We must
 *	set this क्रम all tuners that contain a tda988x chip, and then we
 *	can हटाओ this setting from the various card काष्ठाs.
 *
 *	FIXME: Right now, all tuners are using the first tuner_params[]
 *	array element क्रम analog mode. In the future, we will be merging
 *	similar tuner definitions together, such that each tuner definition
 *	will have a tuner_params काष्ठा क्रम each available video standard.
 *	At that poपूर्णांक, the tuner_params[] array element will be chosen
 *	based on the video standard in use.
 */

/* The following was taken from dvb-pll.c: */

/* Set AGC TOP value to 103 dBuV:
 *	0x80 = Control Byte
 *	0x40 = 250 uA अक्षरge pump (irrelevant)
 *	0x18 = Aux Byte to follow
 *	0x06 = 64.5 kHz भागider (irrelevant)
 *	0x01 = Disable Vt (aka sleep)
 *
 *	0x00 = AGC Time स्थिरant 2s Iagc = 300 nA (vs 0x80 = 9 nA)
 *	0x50 = AGC Take over poपूर्णांक = 103 dBuV
 */
अटल u8 tua603x_agc103[] = अणु 2, 0x80|0x40|0x18|0x06|0x01, 0x00|0x50 पूर्ण;

/*	0x04 = 166.67 kHz भागider
 *
 *	0x80 = AGC Time स्थिरant 50ms Iagc = 9 uA
 *	0x20 = AGC Take over poपूर्णांक = 112 dBuV
 */
अटल u8 tua603x_agc112[] = अणु 2, 0x80|0x40|0x18|0x04|0x01, 0x80|0x20 पूर्ण;

/* 0-9 */
/* ------------ TUNER_TEMIC_PAL - TEMIC PAL ------------ */

अटल काष्ठा tuner_range tuner_temic_pal_ranges[] = अणु
	अणु 16 * 140.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 463.25 /*MHz*/, 0x8e, 0x04, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x01, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_temic_pal_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_pal_ranges,
		.count  = ARRAY_SIZE(tuner_temic_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_PAL_I - Philips PAL_I ------------ */

अटल काष्ठा tuner_range tuner_philips_pal_i_ranges[] = अणु
	अणु 16 * 140.25 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 463.25 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_pal_i_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_philips_pal_i_ranges,
		.count  = ARRAY_SIZE(tuner_philips_pal_i_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_NTSC - Philips NTSC ------------ */

अटल काष्ठा tuner_range tuner_philips_ntsc_ranges[] = अणु
	अणु 16 * 157.25 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 451.25 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_ntsc_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_philips_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_philips_ntsc_ranges),
		.cb_first_अगर_lower_freq = 1,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_SECAM - Philips SECAM ------------ */

अटल काष्ठा tuner_range tuner_philips_secam_ranges[] = अणु
	अणु 16 * 168.25 /*MHz*/, 0x8e, 0xa7, पूर्ण,
	अणु 16 * 447.25 /*MHz*/, 0x8e, 0x97, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_secam_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_SECAM,
		.ranges = tuner_philips_secam_ranges,
		.count  = ARRAY_SIZE(tuner_philips_secam_ranges),
		.cb_first_अगर_lower_freq = 1,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_PAL - Philips PAL ------------ */

अटल काष्ठा tuner_range tuner_philips_pal_ranges[] = अणु
	अणु 16 * 168.25 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 447.25 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_pal_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_philips_pal_ranges,
		.count  = ARRAY_SIZE(tuner_philips_pal_ranges),
		.cb_first_अगर_lower_freq = 1,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_NTSC - TEMIC NTSC ------------ */

अटल काष्ठा tuner_range tuner_temic_ntsc_ranges[] = अणु
	अणु 16 * 157.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 463.25 /*MHz*/, 0x8e, 0x04, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x01, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_temic_ntsc_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_temic_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_temic_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_PAL_I - TEMIC PAL_I ------------ */

अटल काष्ठा tuner_range tuner_temic_pal_i_ranges[] = अणु
	अणु 16 * 170.00 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 450.00 /*MHz*/, 0x8e, 0x04, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x01, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_temic_pal_i_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_pal_i_ranges,
		.count  = ARRAY_SIZE(tuner_temic_pal_i_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_4036FY5_NTSC - TEMIC NTSC ------------ */

अटल काष्ठा tuner_range tuner_temic_4036fy5_ntsc_ranges[] = अणु
	अणु 16 * 157.25 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 463.25 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_temic_4036fy5_ntsc_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_temic_4036fy5_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_temic_4036fy5_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_ALPS_TSBH1_NTSC - TEMIC NTSC ------------ */

अटल काष्ठा tuner_range tuner_alps_tsb_1_ranges[] = अणु
	अणु 16 * 137.25 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 385.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_alps_tsbh1_ntsc_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_alps_tsb_1_ranges,
		.count  = ARRAY_SIZE(tuner_alps_tsb_1_ranges),
	पूर्ण,
पूर्ण;

/* 10-19 */
/* ------------ TUNER_ALPS_TSBE1_PAL - TEMIC PAL ------------ */

अटल काष्ठा tuner_params tuner_alps_tsb_1_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_alps_tsb_1_ranges,
		.count  = ARRAY_SIZE(tuner_alps_tsb_1_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_ALPS_TSBB5_PAL_I - Alps PAL_I ------------ */

अटल काष्ठा tuner_range tuner_alps_tsb_5_pal_ranges[] = अणु
	अणु 16 * 133.25 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 351.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_alps_tsbb5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_alps_tsb_5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_alps_tsb_5_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_ALPS_TSBE5_PAL - Alps PAL ------------ */

अटल काष्ठा tuner_params tuner_alps_tsbe5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_alps_tsb_5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_alps_tsb_5_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_ALPS_TSBC5_PAL - Alps PAL ------------ */

अटल काष्ठा tuner_params tuner_alps_tsbc5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_alps_tsb_5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_alps_tsb_5_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_4006FH5_PAL - TEMIC PAL ------------ */

अटल काष्ठा tuner_range tuner_lg_pal_ranges[] = अणु
	अणु 16 * 170.00 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 450.00 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_temic_4006fh5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_lg_pal_ranges,
		.count  = ARRAY_SIZE(tuner_lg_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_ALPS_TSHC6_NTSC - Alps NTSC ------------ */

अटल काष्ठा tuner_range tuner_alps_tshc6_ntsc_ranges[] = अणु
	अणु 16 * 137.25 /*MHz*/, 0x8e, 0x14, पूर्ण,
	अणु 16 * 385.25 /*MHz*/, 0x8e, 0x12, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x11, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_alps_tshc6_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_alps_tshc6_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_alps_tshc6_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_PAL_DK - TEMIC PAL ------------ */

अटल काष्ठा tuner_range tuner_temic_pal_dk_ranges[] = अणु
	अणु 16 * 168.25 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 456.25 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_temic_pal_dk_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_pal_dk_ranges,
		.count  = ARRAY_SIZE(tuner_temic_pal_dk_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_NTSC_M - Philips NTSC ------------ */

अटल काष्ठा tuner_range tuner_philips_ntsc_m_ranges[] = अणु
	अणु 16 * 160.00 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 454.00 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_ntsc_m_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_philips_ntsc_m_ranges,
		.count  = ARRAY_SIZE(tuner_philips_ntsc_m_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_4066FY5_PAL_I - TEMIC PAL_I ------------ */

अटल काष्ठा tuner_range tuner_temic_40x6f_5_pal_ranges[] = अणु
	अणु 16 * 169.00 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 454.00 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_temic_4066fy5_pal_i_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_40x6f_5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_temic_40x6f_5_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_4006FN5_MULTI_PAL - TEMIC PAL ------------ */

अटल काष्ठा tuner_params tuner_temic_4006fn5_multi_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_40x6f_5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_temic_40x6f_5_pal_ranges),
	पूर्ण,
पूर्ण;

/* 20-29 */
/* ------------ TUNER_TEMIC_4009FR5_PAL - TEMIC PAL ------------ */

अटल काष्ठा tuner_range tuner_temic_4009f_5_pal_ranges[] = अणु
	अणु 16 * 141.00 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 464.00 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_temic_4009f_5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_4009f_5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_temic_4009f_5_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_4039FR5_NTSC - TEMIC NTSC ------------ */

अटल काष्ठा tuner_range tuner_temic_4x3x_f_5_ntsc_ranges[] = अणु
	अणु 16 * 158.00 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 453.00 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_temic_4039fr5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_temic_4x3x_f_5_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_temic_4x3x_f_5_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_4046FM5 - TEMIC PAL ------------ */

अटल काष्ठा tuner_params tuner_temic_4046fm5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_40x6f_5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_temic_40x6f_5_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_PAL_DK - Philips PAL ------------ */

अटल काष्ठा tuner_params tuner_philips_pal_dk_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_lg_pal_ranges,
		.count  = ARRAY_SIZE(tuner_lg_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_FQ1216ME - Philips PAL ------------ */

अटल काष्ठा tuner_params tuner_philips_fq1216me_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_lg_pal_ranges,
		.count  = ARRAY_SIZE(tuner_lg_pal_ranges),
		.has_tda9887 = 1,
		.port1_active = 1,
		.port2_active = 1,
		.port2_invert_क्रम_secam_lc = 1,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_LG_PAL_I_FM - LGINNOTEK PAL_I ------------ */

अटल काष्ठा tuner_params tuner_lg_pal_i_fm_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_lg_pal_ranges,
		.count  = ARRAY_SIZE(tuner_lg_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_LG_PAL_I - LGINNOTEK PAL_I ------------ */

अटल काष्ठा tuner_params tuner_lg_pal_i_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_lg_pal_ranges,
		.count  = ARRAY_SIZE(tuner_lg_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_LG_NTSC_FM - LGINNOTEK NTSC ------------ */

अटल काष्ठा tuner_range tuner_lg_ntsc_fm_ranges[] = अणु
	अणु 16 * 210.00 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 497.00 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_lg_ntsc_fm_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_lg_ntsc_fm_ranges,
		.count  = ARRAY_SIZE(tuner_lg_ntsc_fm_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_LG_PAL_FM - LGINNOTEK PAL ------------ */

अटल काष्ठा tuner_params tuner_lg_pal_fm_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_lg_pal_ranges,
		.count  = ARRAY_SIZE(tuner_lg_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_LG_PAL - LGINNOTEK PAL ------------ */

अटल काष्ठा tuner_params tuner_lg_pal_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_lg_pal_ranges,
		.count  = ARRAY_SIZE(tuner_lg_pal_ranges),
	पूर्ण,
पूर्ण;

/* 30-39 */
/* ------------ TUNER_TEMIC_4009FN5_MULTI_PAL_FM - TEMIC PAL ------------ */

अटल काष्ठा tuner_params tuner_temic_4009_fn5_multi_pal_fm_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_4009f_5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_temic_4009f_5_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_SHARP_2U5JF5540_NTSC - SHARP NTSC ------------ */

अटल काष्ठा tuner_range tuner_sharp_2u5jf5540_ntsc_ranges[] = अणु
	अणु 16 * 137.25 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 317.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_sharp_2u5jf5540_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_sharp_2u5jf5540_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_sharp_2u5jf5540_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_Samsung_PAL_TCPM9091PD27 - Samsung PAL ------------ */

अटल काष्ठा tuner_range tuner_samsung_pal_tcpm9091pd27_ranges[] = अणु
	अणु 16 * 169 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 464 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99     , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_samsung_pal_tcpm9091pd27_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_samsung_pal_tcpm9091pd27_ranges,
		.count  = ARRAY_SIZE(tuner_samsung_pal_tcpm9091pd27_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_4106FH5 - TEMIC PAL ------------ */

अटल काष्ठा tuner_params tuner_temic_4106fh5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_4009f_5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_temic_4009f_5_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_4012FY5 - TEMIC PAL ------------ */

अटल काष्ठा tuner_params tuner_temic_4012fy5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_pal_ranges,
		.count  = ARRAY_SIZE(tuner_temic_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TEMIC_4136FY5 - TEMIC NTSC ------------ */

अटल काष्ठा tuner_params tuner_temic_4136_fy5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_temic_4x3x_f_5_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_temic_4x3x_f_5_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_LG_PAL_NEW_TAPC - LGINNOTEK PAL ------------ */

अटल काष्ठा tuner_range tuner_lg_new_tapc_ranges[] = अणु
	अणु 16 * 170.00 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 450.00 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_lg_pal_new_tapc_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_lg_new_tapc_ranges,
		.count  = ARRAY_SIZE(tuner_lg_new_tapc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_FM1216ME_MK3 - Philips PAL ------------ */

अटल काष्ठा tuner_range tuner_fm1216me_mk3_pal_ranges[] = अणु
	अणु 16 * 158.00 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 442.00 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_fm1216me_mk3_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_fm1216me_mk3_pal_ranges,
		.count  = ARRAY_SIZE(tuner_fm1216me_mk3_pal_ranges),
		.cb_first_अगर_lower_freq = 1,
		.has_tda9887 = 1,
		.port1_active = 1,
		.port2_active = 1,
		.port2_invert_क्रम_secam_lc = 1,
		.port1_fm_high_sensitivity = 1,
		.शेष_top_mid = -2,
		.शेष_top_secam_mid = -2,
		.शेष_top_secam_high = -2,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_FM1216MK5 - Philips PAL ------------ */

अटल काष्ठा tuner_range tuner_fm1216mk5_pal_ranges[] = अणु
	अणु 16 * 158.00 /*MHz*/, 0xce, 0x01, पूर्ण,
	अणु 16 * 441.00 /*MHz*/, 0xce, 0x02, पूर्ण,
	अणु 16 * 864.00        , 0xce, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_fm1216mk5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_fm1216mk5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_fm1216mk5_pal_ranges),
		.cb_first_अगर_lower_freq = 1,
		.has_tda9887 = 1,
		.port1_active = 1,
		.port2_active = 1,
		.port2_invert_क्रम_secam_lc = 1,
		.port1_fm_high_sensitivity = 1,
		.शेष_top_mid = -2,
		.शेष_top_secam_mid = -2,
		.शेष_top_secam_high = -2,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_LG_NTSC_NEW_TAPC - LGINNOTEK NTSC ------------ */

अटल काष्ठा tuner_params tuner_lg_ntsc_new_tapc_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_lg_new_tapc_ranges,
		.count  = ARRAY_SIZE(tuner_lg_new_tapc_ranges),
	पूर्ण,
पूर्ण;

/* 40-49 */
/* ------------ TUNER_HITACHI_NTSC - HITACHI NTSC ------------ */

अटल काष्ठा tuner_params tuner_hitachi_ntsc_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_lg_new_tapc_ranges,
		.count  = ARRAY_SIZE(tuner_lg_new_tapc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_PAL_MK - Philips PAL ------------ */

अटल काष्ठा tuner_range tuner_philips_pal_mk_pal_ranges[] = अणु
	अणु 16 * 140.25 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 463.25 /*MHz*/, 0x8e, 0xc2, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0xcf, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_pal_mk_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_philips_pal_mk_pal_ranges,
		.count  = ARRAY_SIZE(tuner_philips_pal_mk_pal_ranges),
	पूर्ण,
पूर्ण;

/* ---- TUNER_PHILIPS_FCV1236D - Philips FCV1236D (ATSC/NTSC) ---- */

अटल काष्ठा tuner_range tuner_philips_fcv1236d_ntsc_ranges[] = अणु
	अणु 16 * 157.25 /*MHz*/, 0x8e, 0xa2, पूर्ण,
	अणु 16 * 451.25 /*MHz*/, 0x8e, 0x92, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x32, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_range tuner_philips_fcv1236d_atsc_ranges[] = अणु
	अणु 16 * 159.00 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 453.00 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_fcv1236d_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_philips_fcv1236d_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_philips_fcv1236d_ntsc_ranges),
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_philips_fcv1236d_atsc_ranges,
		.count  = ARRAY_SIZE(tuner_philips_fcv1236d_atsc_ranges),
		.अगरfreq = 16 * 44.00,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_FM1236_MK3 - Philips NTSC ------------ */

अटल काष्ठा tuner_range tuner_fm1236_mk3_ntsc_ranges[] = अणु
	अणु 16 * 160.00 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 442.00 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_fm1236_mk3_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_fm1236_mk3_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_fm1236_mk3_ntsc_ranges),
		.cb_first_अगर_lower_freq = 1,
		.has_tda9887 = 1,
		.port1_active = 1,
		.port2_active = 1,
		.port1_fm_high_sensitivity = 1,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_4IN1 - Philips NTSC ------------ */

अटल काष्ठा tuner_params tuner_philips_4in1_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_fm1236_mk3_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_fm1236_mk3_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_MICROTUNE_4049FM5 - Microtune PAL ------------ */

अटल काष्ठा tuner_params tuner_microtune_4049_fm5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_temic_4009f_5_pal_ranges,
		.count  = ARRAY_SIZE(tuner_temic_4009f_5_pal_ranges),
		.has_tda9887 = 1,
		.port1_invert_क्रम_secam_lc = 1,
		.शेष_pll_gating_18 = 1,
		.fm_gain_normal=1,
		.radio_अगर = 1, /* 33.3 MHz */
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PANASONIC_VP27 - Panasonic NTSC ------------ */

अटल काष्ठा tuner_range tuner_panasonic_vp27_ntsc_ranges[] = अणु
	अणु 16 * 160.00 /*MHz*/, 0xce, 0x01, पूर्ण,
	अणु 16 * 454.00 /*MHz*/, 0xce, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0xce, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_panasonic_vp27_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_panasonic_vp27_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_panasonic_vp27_ntsc_ranges),
		.has_tda9887 = 1,
		.पूर्णांकercarrier_mode = 1,
		.शेष_top_low = -3,
		.शेष_top_mid = -3,
		.शेष_top_high = -3,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TNF_8831BGFF - Philips PAL ------------ */

अटल काष्ठा tuner_range tuner_tnf_8831bgff_pal_ranges[] = अणु
	अणु 16 * 161.25 /*MHz*/, 0x8e, 0xa0, पूर्ण,
	अणु 16 * 463.25 /*MHz*/, 0x8e, 0x90, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x30, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_tnf_8831bgff_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_tnf_8831bgff_pal_ranges,
		.count  = ARRAY_SIZE(tuner_tnf_8831bgff_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_MICROTUNE_4042FI5 - Microtune NTSC ------------ */

अटल काष्ठा tuner_range tuner_microtune_4042fi5_ntsc_ranges[] = अणु
	अणु 16 * 162.00 /*MHz*/, 0x8e, 0xa2, पूर्ण,
	अणु 16 * 457.00 /*MHz*/, 0x8e, 0x94, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x31, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_range tuner_microtune_4042fi5_atsc_ranges[] = अणु
	अणु 16 * 162.00 /*MHz*/, 0x8e, 0xa1, पूर्ण,
	अणु 16 * 457.00 /*MHz*/, 0x8e, 0x91, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x31, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_microtune_4042fi5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_microtune_4042fi5_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_microtune_4042fi5_ntsc_ranges),
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_microtune_4042fi5_atsc_ranges,
		.count  = ARRAY_SIZE(tuner_microtune_4042fi5_atsc_ranges),
		.अगरfreq = 16 * 44.00 /*MHz*/,
	पूर्ण,
पूर्ण;

/* 50-59 */
/* ------------ TUNER_TCL_2002N - TCL NTSC ------------ */

अटल काष्ठा tuner_range tuner_tcl_2002n_ntsc_ranges[] = अणु
	अणु 16 * 172.00 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 448.00 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_tcl_2002n_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_tcl_2002n_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_tcl_2002n_ntsc_ranges),
		.cb_first_अगर_lower_freq = 1,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_FM1256_IH3 - Philips PAL ------------ */

अटल काष्ठा tuner_params tuner_philips_fm1256_ih3_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_fm1236_mk3_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_fm1236_mk3_ntsc_ranges),
		.radio_अगर = 1, /* 33.3 MHz */
	पूर्ण,
पूर्ण;

/* ------------ TUNER_THOMSON_DTT7610 - THOMSON ATSC ------------ */

/* single range used क्रम both ntsc and atsc */
अटल काष्ठा tuner_range tuner_thomson_dtt7610_ntsc_ranges[] = अणु
	अणु 16 * 157.25 /*MHz*/, 0x8e, 0x39, पूर्ण,
	अणु 16 * 454.00 /*MHz*/, 0x8e, 0x3a, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x3c, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_thomson_dtt7610_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_thomson_dtt7610_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_thomson_dtt7610_ntsc_ranges),
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_thomson_dtt7610_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_thomson_dtt7610_ntsc_ranges),
		.अगरfreq = 16 * 44.00 /*MHz*/,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_FQ1286 - Philips NTSC ------------ */

अटल काष्ठा tuner_range tuner_philips_fq1286_ntsc_ranges[] = अणु
	अणु 16 * 160.00 /*MHz*/, 0x8e, 0x41, पूर्ण,
	अणु 16 * 454.00 /*MHz*/, 0x8e, 0x42, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_fq1286_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_philips_fq1286_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_philips_fq1286_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TCL_2002MB - TCL PAL ------------ */

अटल काष्ठा tuner_range tuner_tcl_2002mb_pal_ranges[] = अणु
	अणु 16 * 170.00 /*MHz*/, 0xce, 0x01, पूर्ण,
	अणु 16 * 450.00 /*MHz*/, 0xce, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0xce, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_tcl_2002mb_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_tcl_2002mb_pal_ranges,
		.count  = ARRAY_SIZE(tuner_tcl_2002mb_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_FQ1216AME_MK4 - Philips PAL ------------ */

अटल काष्ठा tuner_range tuner_philips_fq12_6a___mk4_pal_ranges[] = अणु
	अणु 16 * 160.00 /*MHz*/, 0xce, 0x01, पूर्ण,
	अणु 16 * 442.00 /*MHz*/, 0xce, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0xce, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_fq1216ame_mk4_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_philips_fq12_6a___mk4_pal_ranges,
		.count  = ARRAY_SIZE(tuner_philips_fq12_6a___mk4_pal_ranges),
		.has_tda9887 = 1,
		.port1_active = 1,
		.port2_invert_क्रम_secam_lc = 1,
		.शेष_top_mid = -2,
		.शेष_top_secam_low = -2,
		.शेष_top_secam_mid = -2,
		.शेष_top_secam_high = -2,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_FQ1236A_MK4 - Philips NTSC ------------ */

अटल काष्ठा tuner_params tuner_philips_fq1236a_mk4_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_fm1236_mk3_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_fm1236_mk3_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_YMEC_TVF_8531MF - Philips NTSC ------------ */

अटल काष्ठा tuner_params tuner_ymec_tvf_8531mf_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_philips_ntsc_m_ranges,
		.count  = ARRAY_SIZE(tuner_philips_ntsc_m_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_YMEC_TVF_5533MF - Philips NTSC ------------ */

अटल काष्ठा tuner_range tuner_ymec_tvf_5533mf_ntsc_ranges[] = अणु
	अणु 16 * 160.00 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 454.00 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_ymec_tvf_5533mf_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_ymec_tvf_5533mf_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_ymec_tvf_5533mf_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* 60-69 */
/* ------------ TUNER_THOMSON_DTT761X - THOMSON ATSC ------------ */
/* DTT 7611 7611A 7612 7613 7613A 7614 7615 7615A */

अटल काष्ठा tuner_range tuner_thomson_dtt761x_ntsc_ranges[] = अणु
	अणु 16 * 145.25 /*MHz*/, 0x8e, 0x39, पूर्ण,
	अणु 16 * 415.25 /*MHz*/, 0x8e, 0x3a, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x3c, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_range tuner_thomson_dtt761x_atsc_ranges[] = अणु
	अणु 16 * 147.00 /*MHz*/, 0x8e, 0x39, पूर्ण,
	अणु 16 * 417.00 /*MHz*/, 0x8e, 0x3a, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x3c, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_thomson_dtt761x_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_thomson_dtt761x_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_thomson_dtt761x_ntsc_ranges),
		.has_tda9887 = 1,
		.fm_gain_normal = 1,
		.radio_अगर = 2, /* 41.3 MHz */
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_thomson_dtt761x_atsc_ranges,
		.count  = ARRAY_SIZE(tuner_thomson_dtt761x_atsc_ranges),
		.अगरfreq = 16 * 44.00, /*MHz*/
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TENA_9533_DI - Philips PAL ------------ */

अटल काष्ठा tuner_range tuner_tena_9533_di_pal_ranges[] = अणु
	अणु 16 * 160.25 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 464.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_tena_9533_di_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_tena_9533_di_pal_ranges,
		.count  = ARRAY_SIZE(tuner_tena_9533_di_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TENA_TNF_5337 - Tena tnf5337MFD STD M/N ------------ */

अटल काष्ठा tuner_range tuner_tena_tnf_5337_ntsc_ranges[] = अणु
	अणु 16 * 166.25 /*MHz*/, 0x86, 0x01, पूर्ण,
	अणु 16 * 466.25 /*MHz*/, 0x86, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x86, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_tena_tnf_5337_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_tena_tnf_5337_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_tena_tnf_5337_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_FMD1216ME(X)_MK3 - Philips PAL ------------ */

अटल काष्ठा tuner_range tuner_philips_fmd1216me_mk3_pal_ranges[] = अणु
	अणु 16 * 160.00 /*MHz*/, 0x86, 0x51, पूर्ण,
	अणु 16 * 442.00 /*MHz*/, 0x86, 0x52, पूर्ण,
	अणु 16 * 999.99        , 0x86, 0x54, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_range tuner_philips_fmd1216me_mk3_dvb_ranges[] = अणु
	अणु 16 * 143.87 /*MHz*/, 0xbc, 0x41 पूर्ण,
	अणु 16 * 158.87 /*MHz*/, 0xf4, 0x41 पूर्ण,
	अणु 16 * 329.87 /*MHz*/, 0xbc, 0x42 पूर्ण,
	अणु 16 * 441.87 /*MHz*/, 0xf4, 0x42 पूर्ण,
	अणु 16 * 625.87 /*MHz*/, 0xbc, 0x44 पूर्ण,
	अणु 16 * 803.87 /*MHz*/, 0xf4, 0x44 पूर्ण,
	अणु 16 * 999.99        , 0xfc, 0x44 पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_fmd1216me_mk3_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_philips_fmd1216me_mk3_pal_ranges,
		.count  = ARRAY_SIZE(tuner_philips_fmd1216me_mk3_pal_ranges),
		.has_tda9887 = 1,
		.port1_active = 1,
		.port2_active = 1,
		.port2_fm_high_sensitivity = 1,
		.port2_invert_क्रम_secam_lc = 1,
		.port1_set_क्रम_fm_mono = 1,
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_philips_fmd1216me_mk3_dvb_ranges,
		.count  = ARRAY_SIZE(tuner_philips_fmd1216me_mk3_dvb_ranges),
		.अगरfreq = 16 * 36.125, /*MHz*/
	पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_fmd1216mex_mk3_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_philips_fmd1216me_mk3_pal_ranges,
		.count  = ARRAY_SIZE(tuner_philips_fmd1216me_mk3_pal_ranges),
		.has_tda9887 = 1,
		.port1_active = 1,
		.port2_active = 1,
		.port2_fm_high_sensitivity = 1,
		.port2_invert_क्रम_secam_lc = 1,
		.port1_set_क्रम_fm_mono = 1,
		.radio_अगर = 1,
		.fm_gain_normal = 1,
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_philips_fmd1216me_mk3_dvb_ranges,
		.count  = ARRAY_SIZE(tuner_philips_fmd1216me_mk3_dvb_ranges),
		.अगरfreq = 16 * 36.125, /*MHz*/
	पूर्ण,
पूर्ण;

/* ------ TUNER_LG_TDVS_H06XF - LG INNOTEK / INFINEON ATSC ----- */

अटल काष्ठा tuner_range tuner_tua6034_ntsc_ranges[] = अणु
	अणु 16 * 165.00 /*MHz*/, 0x8e, 0x01 पूर्ण,
	अणु 16 * 450.00 /*MHz*/, 0x8e, 0x02 पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x04 पूर्ण,
पूर्ण;

अटल काष्ठा tuner_range tuner_tua6034_atsc_ranges[] = अणु
	अणु 16 * 165.00 /*MHz*/, 0xce, 0x01 पूर्ण,
	अणु 16 * 450.00 /*MHz*/, 0xce, 0x02 पूर्ण,
	अणु 16 * 999.99        , 0xce, 0x04 पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_lg_tdvs_h06xf_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_tua6034_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_tua6034_ntsc_ranges),
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_tua6034_atsc_ranges,
		.count  = ARRAY_SIZE(tuner_tua6034_atsc_ranges),
		.अगरfreq = 16 * 44.00,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_YMEC_TVF66T5_B_DFF - Philips PAL ------------ */

अटल काष्ठा tuner_range tuner_ymec_tvf66t5_b_dff_pal_ranges[] = अणु
	अणु 16 * 160.25 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 464.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_ymec_tvf66t5_b_dff_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_ymec_tvf66t5_b_dff_pal_ranges,
		.count  = ARRAY_SIZE(tuner_ymec_tvf66t5_b_dff_pal_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_LG_NTSC_TALN_MINI - LGINNOTEK NTSC ------------ */

अटल काष्ठा tuner_range tuner_lg_taln_ntsc_ranges[] = अणु
	अणु 16 * 137.25 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 373.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_range tuner_lg_taln_pal_secam_ranges[] = अणु
	अणु 16 * 150.00 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 425.00 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_lg_taln_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_lg_taln_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_lg_taln_ntsc_ranges),
	पूर्ण,अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_lg_taln_pal_secam_ranges,
		.count  = ARRAY_SIZE(tuner_lg_taln_pal_secam_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_TD1316 - Philips PAL ------------ */

अटल काष्ठा tuner_range tuner_philips_td1316_pal_ranges[] = अणु
	अणु 16 * 160.00 /*MHz*/, 0xc8, 0xa1, पूर्ण,
	अणु 16 * 442.00 /*MHz*/, 0xc8, 0xa2, पूर्ण,
	अणु 16 * 999.99        , 0xc8, 0xa4, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_range tuner_philips_td1316_dvb_ranges[] = अणु
	अणु 16 *  93.834 /*MHz*/, 0xca, 0x60, पूर्ण,
	अणु 16 * 123.834 /*MHz*/, 0xca, 0xa0, पूर्ण,
	अणु 16 * 163.834 /*MHz*/, 0xca, 0xc0, पूर्ण,
	अणु 16 * 253.834 /*MHz*/, 0xca, 0x60, पूर्ण,
	अणु 16 * 383.834 /*MHz*/, 0xca, 0xa0, पूर्ण,
	अणु 16 * 443.834 /*MHz*/, 0xca, 0xc0, पूर्ण,
	अणु 16 * 583.834 /*MHz*/, 0xca, 0x60, पूर्ण,
	अणु 16 * 793.834 /*MHz*/, 0xca, 0xa0, पूर्ण,
	अणु 16 * 999.999        , 0xca, 0xe0, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_td1316_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_philips_td1316_pal_ranges,
		.count  = ARRAY_SIZE(tuner_philips_td1316_pal_ranges),
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_philips_td1316_dvb_ranges,
		.count  = ARRAY_SIZE(tuner_philips_td1316_dvb_ranges),
		.अगरfreq = 16 * 36.166667 /*MHz*/,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_TUV1236D - Philips ATSC ------------ */

अटल काष्ठा tuner_range tuner_tuv1236d_ntsc_ranges[] = अणु
	अणु 16 * 157.25 /*MHz*/, 0xce, 0x01, पूर्ण,
	अणु 16 * 454.00 /*MHz*/, 0xce, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0xce, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_range tuner_tuv1236d_atsc_ranges[] = अणु
	अणु 16 * 157.25 /*MHz*/, 0xc6, 0x41, पूर्ण,
	अणु 16 * 454.00 /*MHz*/, 0xc6, 0x42, पूर्ण,
	अणु 16 * 999.99        , 0xc6, 0x44, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_tuv1236d_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_tuv1236d_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_tuv1236d_ntsc_ranges),
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_tuv1236d_atsc_ranges,
		.count  = ARRAY_SIZE(tuner_tuv1236d_atsc_ranges),
		.अगरfreq = 16 * 44.00,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TNF_xxx5  - Texas Instruments--------- */
/* This is known to work with Tenna TVF58t5-MFF and TVF5835 MFF
 *	but it is expected to work also with other Tenna/Ymec
 *	models based on TI SN 761677 chip on both PAL and NTSC
 */

अटल काष्ठा tuner_range tuner_tnf_5335_d_अगर_pal_ranges[] = अणु
	अणु 16 * 168.25 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 471.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_range tuner_tnf_5335mf_ntsc_ranges[] = अणु
	अणु 16 * 169.25 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 469.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_tnf_5335mf_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_tnf_5335mf_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_tnf_5335mf_ntsc_ranges),
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_tnf_5335_d_अगर_pal_ranges,
		.count  = ARRAY_SIZE(tuner_tnf_5335_d_अगर_pal_ranges),
	पूर्ण,
पूर्ण;

/* 70-79 */
/* ------------ TUNER_SAMSUNG_TCPN_2121P30A - Samsung NTSC ------------ */

/* '+ 4' turns on the Low Noise Amplअगरier */
अटल काष्ठा tuner_range tuner_samsung_tcpn_2121p30a_ntsc_ranges[] = अणु
	अणु 16 * 130.00 /*MHz*/, 0xce, 0x01 + 4, पूर्ण,
	अणु 16 * 364.50 /*MHz*/, 0xce, 0x02 + 4, पूर्ण,
	अणु 16 * 999.99        , 0xce, 0x08 + 4, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_samsung_tcpn_2121p30a_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_samsung_tcpn_2121p30a_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_samsung_tcpn_2121p30a_ntsc_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_THOMSON_FE6600 - DViCO Hybrid PAL ------------ */

अटल काष्ठा tuner_range tuner_thomson_fe6600_pal_ranges[] = अणु
	अणु 16 * 160.00 /*MHz*/, 0xfe, 0x11, पूर्ण,
	अणु 16 * 442.00 /*MHz*/, 0xf6, 0x12, पूर्ण,
	अणु 16 * 999.99        , 0xf6, 0x18, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_range tuner_thomson_fe6600_dvb_ranges[] = अणु
	अणु 16 * 250.00 /*MHz*/, 0xb4, 0x12, पूर्ण,
	अणु 16 * 455.00 /*MHz*/, 0xfe, 0x11, पूर्ण,
	अणु 16 * 775.50 /*MHz*/, 0xbc, 0x18, पूर्ण,
	अणु 16 * 999.99        , 0xf4, 0x18, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_thomson_fe6600_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_thomson_fe6600_pal_ranges,
		.count  = ARRAY_SIZE(tuner_thomson_fe6600_pal_ranges),
	पूर्ण,
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_thomson_fe6600_dvb_ranges,
		.count  = ARRAY_SIZE(tuner_thomson_fe6600_dvb_ranges),
		.अगरfreq = 16 * 36.125 /*MHz*/,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_SAMSUNG_TCPG_6121P30A - Samsung PAL ------------ */

/* '+ 4' turns on the Low Noise Amplअगरier */
अटल काष्ठा tuner_range tuner_samsung_tcpg_6121p30a_pal_ranges[] = अणु
	अणु 16 * 146.25 /*MHz*/, 0xce, 0x01 + 4, पूर्ण,
	अणु 16 * 428.50 /*MHz*/, 0xce, 0x02 + 4, पूर्ण,
	अणु 16 * 999.99        , 0xce, 0x08 + 4, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_samsung_tcpg_6121p30a_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_samsung_tcpg_6121p30a_pal_ranges,
		.count  = ARRAY_SIZE(tuner_samsung_tcpg_6121p30a_pal_ranges),
		.has_tda9887 = 1,
		.port1_active = 1,
		.port2_active = 1,
		.port2_invert_क्रम_secam_lc = 1,
	पूर्ण,
पूर्ण;

/* ------------ TUNER_TCL_MF02GIP-5N-E - TCL MF02GIP-5N ------------ */

अटल काष्ठा tuner_range tuner_tcl_mf02gip_5n_ntsc_ranges[] = अणु
	अणु 16 * 172.00 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 448.00 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_tcl_mf02gip_5n_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_tcl_mf02gip_5n_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_tcl_mf02gip_5n_ntsc_ranges),
		.cb_first_अगर_lower_freq = 1,
	पूर्ण,
पूर्ण;

/* 80-89 */
/* --------- TUNER_PHILIPS_FQ1216LME_MK3 -- active loopthrough, no FM ------- */

अटल काष्ठा tuner_params tuner_fq1216lme_mk3_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_fm1216me_mk3_pal_ranges,
		.count  = ARRAY_SIZE(tuner_fm1216me_mk3_pal_ranges),
		.cb_first_अगर_lower_freq = 1, /* not specअगरied, but safe to करो */
		.has_tda9887 = 1, /* TDA9886 */
		.port1_active = 1,
		.port2_active = 1,
		.port2_invert_क्रम_secam_lc = 1,
		.शेष_top_low = 4,
		.शेष_top_mid = 4,
		.शेष_top_high = 4,
		.शेष_top_secam_low = 4,
		.शेष_top_secam_mid = 4,
		.शेष_top_secam_high = 4,
	पूर्ण,
पूर्ण;

/* ----- TUNER_PARTSNIC_PTI_5NF05 - Partsnic (Daewoo) PTI-5NF05 NTSC ----- */

अटल काष्ठा tuner_range tuner_partsnic_pti_5nf05_ranges[] = अणु
	/* The datasheet specअगरied channel ranges and the bandचयन byte */
	/* The control byte value of 0x8e is just a guess */
	अणु 16 * 133.25 /*MHz*/, 0x8e, 0x01, पूर्ण, /* Channels    2 -    B */
	अणु 16 * 367.25 /*MHz*/, 0x8e, 0x02, पूर्ण, /* Channels    C - W+11 */
	अणु 16 * 999.99        , 0x8e, 0x08, पूर्ण, /* Channels W+12 -   69 */
पूर्ण;

अटल काष्ठा tuner_params tuner_partsnic_pti_5nf05_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_partsnic_pti_5nf05_ranges,
		.count  = ARRAY_SIZE(tuner_partsnic_pti_5nf05_ranges),
		.cb_first_अगर_lower_freq = 1, /* not specअगरied but safe to करो */
	पूर्ण,
पूर्ण;

/* --------- TUNER_PHILIPS_CU1216L - DVB-C NIM ------------------------- */

अटल काष्ठा tuner_range tuner_cu1216l_ranges[] = अणु
	अणु 16 * 160.25 /*MHz*/, 0xce, 0x01 पूर्ण,
	अणु 16 * 444.25 /*MHz*/, 0xce, 0x02 पूर्ण,
	अणु 16 * 999.99        , 0xce, 0x04 पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_philips_cu1216l_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_DIGITAL,
		.ranges = tuner_cu1216l_ranges,
		.count  = ARRAY_SIZE(tuner_cu1216l_ranges),
		.अगरfreq = 16 * 36.125, /*MHz*/
	पूर्ण,
पूर्ण;

/* ---------------------- TUNER_SONY_BTF_PXN01Z ------------------------ */

अटल काष्ठा tuner_range tuner_sony_btf_pxn01z_ranges[] = अणु
	अणु 16 * 137.25 /*MHz*/, 0x8e, 0x01, पूर्ण,
	अणु 16 * 367.25 /*MHz*/, 0x8e, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0x8e, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_sony_btf_pxn01z_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_sony_btf_pxn01z_ranges,
		.count  = ARRAY_SIZE(tuner_sony_btf_pxn01z_ranges),
	पूर्ण,
पूर्ण;

/* ------------ TUNER_PHILIPS_FQ1236_MK5 - Philips NTSC ------------ */

अटल काष्ठा tuner_params tuner_philips_fq1236_mk5_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_fm1236_mk3_ntsc_ranges,
		.count  = ARRAY_SIZE(tuner_fm1236_mk3_ntsc_ranges),
		.has_tda9887 = 1, /* TDA9885, no FM radio */
	पूर्ण,
पूर्ण;

/* --------- Sony BTF-PG472Z PAL/SECAM ------- */

अटल काष्ठा tuner_range tuner_sony_btf_pg472z_ranges[] = अणु
	अणु 16 * 144.25 /*MHz*/, 0xc6, 0x01, पूर्ण,
	अणु 16 * 427.25 /*MHz*/, 0xc6, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0xc6, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_sony_btf_pg472z_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_PAL,
		.ranges = tuner_sony_btf_pg472z_ranges,
		.count  = ARRAY_SIZE(tuner_sony_btf_pg472z_ranges),
		.has_tda9887 = 1,
		.port1_active = 1,
		.port2_invert_क्रम_secam_lc = 1,
	पूर्ण,
पूर्ण;

/* 90-99 */
/* --------- Sony BTF-PG467Z NTSC-M-JP ------- */

अटल काष्ठा tuner_range tuner_sony_btf_pg467z_ranges[] = अणु
	अणु 16 * 220.25 /*MHz*/, 0xc6, 0x01, पूर्ण,
	अणु 16 * 467.25 /*MHz*/, 0xc6, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0xc6, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_sony_btf_pg467z_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_sony_btf_pg467z_ranges,
		.count  = ARRAY_SIZE(tuner_sony_btf_pg467z_ranges),
	पूर्ण,
पूर्ण;

/* --------- Sony BTF-PG463Z NTSC-M ------- */

अटल काष्ठा tuner_range tuner_sony_btf_pg463z_ranges[] = अणु
	अणु 16 * 130.25 /*MHz*/, 0xc6, 0x01, पूर्ण,
	अणु 16 * 364.25 /*MHz*/, 0xc6, 0x02, पूर्ण,
	अणु 16 * 999.99        , 0xc6, 0x04, पूर्ण,
पूर्ण;

अटल काष्ठा tuner_params tuner_sony_btf_pg463z_params[] = अणु
	अणु
		.type   = TUNER_PARAM_TYPE_NTSC,
		.ranges = tuner_sony_btf_pg463z_ranges,
		.count  = ARRAY_SIZE(tuner_sony_btf_pg463z_ranges),
	पूर्ण,
पूर्ण;

/* --------------------------------------------------------------------- */

काष्ठा tunertype tuners[] = अणु
	/* 0-9 */
	[TUNER_TEMIC_PAL] = अणु /* TEMIC PAL */
		.name   = "Temic PAL (4002 FH5)",
		.params = tuner_temic_pal_params,
		.count  = ARRAY_SIZE(tuner_temic_pal_params),
	पूर्ण,
	[TUNER_PHILIPS_PAL_I] = अणु /* Philips PAL_I */
		.name   = "Philips PAL_I (FI1246 and compatibles)",
		.params = tuner_philips_pal_i_params,
		.count  = ARRAY_SIZE(tuner_philips_pal_i_params),
	पूर्ण,
	[TUNER_PHILIPS_NTSC] = अणु /* Philips NTSC */
		.name   = "Philips NTSC (FI1236,FM1236 and compatibles)",
		.params = tuner_philips_ntsc_params,
		.count  = ARRAY_SIZE(tuner_philips_ntsc_params),
	पूर्ण,
	[TUNER_PHILIPS_SECAM] = अणु /* Philips SECAM */
		.name   = "Philips (SECAM+PAL_BG) (FI1216MF, FM1216MF, FR1216MF)",
		.params = tuner_philips_secam_params,
		.count  = ARRAY_SIZE(tuner_philips_secam_params),
	पूर्ण,
	[TUNER_ABSENT] = अणु /* Tuner Absent */
		.name   = "NoTuner",
	पूर्ण,
	[TUNER_PHILIPS_PAL] = अणु /* Philips PAL */
		.name   = "Philips PAL_BG (FI1216 and compatibles)",
		.params = tuner_philips_pal_params,
		.count  = ARRAY_SIZE(tuner_philips_pal_params),
	पूर्ण,
	[TUNER_TEMIC_NTSC] = अणु /* TEMIC NTSC */
		.name   = "Temic NTSC (4032 FY5)",
		.params = tuner_temic_ntsc_params,
		.count  = ARRAY_SIZE(tuner_temic_ntsc_params),
	पूर्ण,
	[TUNER_TEMIC_PAL_I] = अणु /* TEMIC PAL_I */
		.name   = "Temic PAL_I (4062 FY5)",
		.params = tuner_temic_pal_i_params,
		.count  = ARRAY_SIZE(tuner_temic_pal_i_params),
	पूर्ण,
	[TUNER_TEMIC_4036FY5_NTSC] = अणु /* TEMIC NTSC */
		.name   = "Temic NTSC (4036 FY5)",
		.params = tuner_temic_4036fy5_ntsc_params,
		.count  = ARRAY_SIZE(tuner_temic_4036fy5_ntsc_params),
	पूर्ण,
	[TUNER_ALPS_TSBH1_NTSC] = अणु /* TEMIC NTSC */
		.name   = "Alps HSBH1",
		.params = tuner_alps_tsbh1_ntsc_params,
		.count  = ARRAY_SIZE(tuner_alps_tsbh1_ntsc_params),
	पूर्ण,

	/* 10-19 */
	[TUNER_ALPS_TSBE1_PAL] = अणु /* TEMIC PAL */
		.name   = "Alps TSBE1",
		.params = tuner_alps_tsb_1_params,
		.count  = ARRAY_SIZE(tuner_alps_tsb_1_params),
	पूर्ण,
	[TUNER_ALPS_TSBB5_PAL_I] = अणु /* Alps PAL_I */
		.name   = "Alps TSBB5",
		.params = tuner_alps_tsbb5_params,
		.count  = ARRAY_SIZE(tuner_alps_tsbb5_params),
	पूर्ण,
	[TUNER_ALPS_TSBE5_PAL] = अणु /* Alps PAL */
		.name   = "Alps TSBE5",
		.params = tuner_alps_tsbe5_params,
		.count  = ARRAY_SIZE(tuner_alps_tsbe5_params),
	पूर्ण,
	[TUNER_ALPS_TSBC5_PAL] = अणु /* Alps PAL */
		.name   = "Alps TSBC5",
		.params = tuner_alps_tsbc5_params,
		.count  = ARRAY_SIZE(tuner_alps_tsbc5_params),
	पूर्ण,
	[TUNER_TEMIC_4006FH5_PAL] = अणु /* TEMIC PAL */
		.name   = "Temic PAL_BG (4006FH5)",
		.params = tuner_temic_4006fh5_params,
		.count  = ARRAY_SIZE(tuner_temic_4006fh5_params),
	पूर्ण,
	[TUNER_ALPS_TSHC6_NTSC] = अणु /* Alps NTSC */
		.name   = "Alps TSCH6",
		.params = tuner_alps_tshc6_params,
		.count  = ARRAY_SIZE(tuner_alps_tshc6_params),
	पूर्ण,
	[TUNER_TEMIC_PAL_DK] = अणु /* TEMIC PAL */
		.name   = "Temic PAL_DK (4016 FY5)",
		.params = tuner_temic_pal_dk_params,
		.count  = ARRAY_SIZE(tuner_temic_pal_dk_params),
	पूर्ण,
	[TUNER_PHILIPS_NTSC_M] = अणु /* Philips NTSC */
		.name   = "Philips NTSC_M (MK2)",
		.params = tuner_philips_ntsc_m_params,
		.count  = ARRAY_SIZE(tuner_philips_ntsc_m_params),
	पूर्ण,
	[TUNER_TEMIC_4066FY5_PAL_I] = अणु /* TEMIC PAL_I */
		.name   = "Temic PAL_I (4066 FY5)",
		.params = tuner_temic_4066fy5_pal_i_params,
		.count  = ARRAY_SIZE(tuner_temic_4066fy5_pal_i_params),
	पूर्ण,
	[TUNER_TEMIC_4006FN5_MULTI_PAL] = अणु /* TEMIC PAL */
		.name   = "Temic PAL* auto (4006 FN5)",
		.params = tuner_temic_4006fn5_multi_params,
		.count  = ARRAY_SIZE(tuner_temic_4006fn5_multi_params),
	पूर्ण,

	/* 20-29 */
	[TUNER_TEMIC_4009FR5_PAL] = अणु /* TEMIC PAL */
		.name   = "Temic PAL_BG (4009 FR5) or PAL_I (4069 FR5)",
		.params = tuner_temic_4009f_5_params,
		.count  = ARRAY_SIZE(tuner_temic_4009f_5_params),
	पूर्ण,
	[TUNER_TEMIC_4039FR5_NTSC] = अणु /* TEMIC NTSC */
		.name   = "Temic NTSC (4039 FR5)",
		.params = tuner_temic_4039fr5_params,
		.count  = ARRAY_SIZE(tuner_temic_4039fr5_params),
	पूर्ण,
	[TUNER_TEMIC_4046FM5] = अणु /* TEMIC PAL */
		.name   = "Temic PAL/SECAM multi (4046 FM5)",
		.params = tuner_temic_4046fm5_params,
		.count  = ARRAY_SIZE(tuner_temic_4046fm5_params),
	पूर्ण,
	[TUNER_PHILIPS_PAL_DK] = अणु /* Philips PAL */
		.name   = "Philips PAL_DK (FI1256 and compatibles)",
		.params = tuner_philips_pal_dk_params,
		.count  = ARRAY_SIZE(tuner_philips_pal_dk_params),
	पूर्ण,
	[TUNER_PHILIPS_FQ1216ME] = अणु /* Philips PAL */
		.name   = "Philips PAL/SECAM multi (FQ1216ME)",
		.params = tuner_philips_fq1216me_params,
		.count  = ARRAY_SIZE(tuner_philips_fq1216me_params),
	पूर्ण,
	[TUNER_LG_PAL_I_FM] = अणु /* LGINNOTEK PAL_I */
		.name   = "LG PAL_I+FM (TAPC-I001D)",
		.params = tuner_lg_pal_i_fm_params,
		.count  = ARRAY_SIZE(tuner_lg_pal_i_fm_params),
	पूर्ण,
	[TUNER_LG_PAL_I] = अणु /* LGINNOTEK PAL_I */
		.name   = "LG PAL_I (TAPC-I701D)",
		.params = tuner_lg_pal_i_params,
		.count  = ARRAY_SIZE(tuner_lg_pal_i_params),
	पूर्ण,
	[TUNER_LG_NTSC_FM] = अणु /* LGINNOTEK NTSC */
		.name   = "LG NTSC+FM (TPI8NSR01F)",
		.params = tuner_lg_ntsc_fm_params,
		.count  = ARRAY_SIZE(tuner_lg_ntsc_fm_params),
	पूर्ण,
	[TUNER_LG_PAL_FM] = अणु /* LGINNOTEK PAL */
		.name   = "LG PAL_BG+FM (TPI8PSB01D)",
		.params = tuner_lg_pal_fm_params,
		.count  = ARRAY_SIZE(tuner_lg_pal_fm_params),
	पूर्ण,
	[TUNER_LG_PAL] = अणु /* LGINNOTEK PAL */
		.name   = "LG PAL_BG (TPI8PSB11D)",
		.params = tuner_lg_pal_params,
		.count  = ARRAY_SIZE(tuner_lg_pal_params),
	पूर्ण,

	/* 30-39 */
	[TUNER_TEMIC_4009FN5_MULTI_PAL_FM] = अणु /* TEMIC PAL */
		.name   = "Temic PAL* auto + FM (4009 FN5)",
		.params = tuner_temic_4009_fn5_multi_pal_fm_params,
		.count  = ARRAY_SIZE(tuner_temic_4009_fn5_multi_pal_fm_params),
	पूर्ण,
	[TUNER_SHARP_2U5JF5540_NTSC] = अणु /* SHARP NTSC */
		.name   = "SHARP NTSC_JP (2U5JF5540)",
		.params = tuner_sharp_2u5jf5540_params,
		.count  = ARRAY_SIZE(tuner_sharp_2u5jf5540_params),
	पूर्ण,
	[TUNER_Samsung_PAL_TCPM9091PD27] = अणु /* Samsung PAL */
		.name   = "Samsung PAL TCPM9091PD27",
		.params = tuner_samsung_pal_tcpm9091pd27_params,
		.count  = ARRAY_SIZE(tuner_samsung_pal_tcpm9091pd27_params),
	पूर्ण,
	[TUNER_MT2032] = अणु /* Microtune PAL|NTSC */
		.name   = "MT20xx universal",
		/* see mt20xx.c क्रम details */ पूर्ण,
	[TUNER_TEMIC_4106FH5] = अणु /* TEMIC PAL */
		.name   = "Temic PAL_BG (4106 FH5)",
		.params = tuner_temic_4106fh5_params,
		.count  = ARRAY_SIZE(tuner_temic_4106fh5_params),
	पूर्ण,
	[TUNER_TEMIC_4012FY5] = अणु /* TEMIC PAL */
		.name   = "Temic PAL_DK/SECAM_L (4012 FY5)",
		.params = tuner_temic_4012fy5_params,
		.count  = ARRAY_SIZE(tuner_temic_4012fy5_params),
	पूर्ण,
	[TUNER_TEMIC_4136FY5] = अणु /* TEMIC NTSC */
		.name   = "Temic NTSC (4136 FY5)",
		.params = tuner_temic_4136_fy5_params,
		.count  = ARRAY_SIZE(tuner_temic_4136_fy5_params),
	पूर्ण,
	[TUNER_LG_PAL_NEW_TAPC] = अणु /* LGINNOTEK PAL */
		.name   = "LG PAL (newer TAPC series)",
		.params = tuner_lg_pal_new_tapc_params,
		.count  = ARRAY_SIZE(tuner_lg_pal_new_tapc_params),
	पूर्ण,
	[TUNER_PHILIPS_FM1216ME_MK3] = अणु /* Philips PAL */
		.name   = "Philips PAL/SECAM multi (FM1216ME MK3)",
		.params = tuner_fm1216me_mk3_params,
		.count  = ARRAY_SIZE(tuner_fm1216me_mk3_params),
	पूर्ण,
	[TUNER_LG_NTSC_NEW_TAPC] = अणु /* LGINNOTEK NTSC */
		.name   = "LG NTSC (newer TAPC series)",
		.params = tuner_lg_ntsc_new_tapc_params,
		.count  = ARRAY_SIZE(tuner_lg_ntsc_new_tapc_params),
	पूर्ण,

	/* 40-49 */
	[TUNER_HITACHI_NTSC] = अणु /* HITACHI NTSC */
		.name   = "HITACHI V7-J180AT",
		.params = tuner_hitachi_ntsc_params,
		.count  = ARRAY_SIZE(tuner_hitachi_ntsc_params),
	पूर्ण,
	[TUNER_PHILIPS_PAL_MK] = अणु /* Philips PAL */
		.name   = "Philips PAL_MK (FI1216 MK)",
		.params = tuner_philips_pal_mk_params,
		.count  = ARRAY_SIZE(tuner_philips_pal_mk_params),
	पूर्ण,
	[TUNER_PHILIPS_FCV1236D] = अणु /* Philips ATSC */
		.name   = "Philips FCV1236D ATSC/NTSC dual in",
		.params = tuner_philips_fcv1236d_params,
		.count  = ARRAY_SIZE(tuner_philips_fcv1236d_params),
		.min = 16 *  53.00,
		.max = 16 * 803.00,
		.stepsize = 62500,
	पूर्ण,
	[TUNER_PHILIPS_FM1236_MK3] = अणु /* Philips NTSC */
		.name   = "Philips NTSC MK3 (FM1236MK3 or FM1236/F)",
		.params = tuner_fm1236_mk3_params,
		.count  = ARRAY_SIZE(tuner_fm1236_mk3_params),
	पूर्ण,
	[TUNER_PHILIPS_4IN1] = अणु /* Philips NTSC */
		.name   = "Philips 4 in 1 (ATI TV Wonder Pro/Conexant)",
		.params = tuner_philips_4in1_params,
		.count  = ARRAY_SIZE(tuner_philips_4in1_params),
	पूर्ण,
	[TUNER_MICROTUNE_4049FM5] = अणु /* Microtune PAL */
		.name   = "Microtune 4049 FM5",
		.params = tuner_microtune_4049_fm5_params,
		.count  = ARRAY_SIZE(tuner_microtune_4049_fm5_params),
	पूर्ण,
	[TUNER_PANASONIC_VP27] = अणु /* Panasonic NTSC */
		.name   = "Panasonic VP27s/ENGE4324D",
		.params = tuner_panasonic_vp27_params,
		.count  = ARRAY_SIZE(tuner_panasonic_vp27_params),
	पूर्ण,
	[TUNER_LG_NTSC_TAPE] = अणु /* LGINNOTEK NTSC */
		.name   = "LG NTSC (TAPE series)",
		.params = tuner_fm1236_mk3_params,
		.count  = ARRAY_SIZE(tuner_fm1236_mk3_params),
	पूर्ण,
	[TUNER_TNF_8831BGFF] = अणु /* Philips PAL */
		.name   = "Tenna TNF 8831 BGFF)",
		.params = tuner_tnf_8831bgff_params,
		.count  = ARRAY_SIZE(tuner_tnf_8831bgff_params),
	पूर्ण,
	[TUNER_MICROTUNE_4042FI5] = अणु /* Microtune NTSC */
		.name   = "Microtune 4042 FI5 ATSC/NTSC dual in",
		.params = tuner_microtune_4042fi5_params,
		.count  = ARRAY_SIZE(tuner_microtune_4042fi5_params),
		.min    = 16 *  57.00,
		.max    = 16 * 858.00,
		.stepsize = 62500,
	पूर्ण,

	/* 50-59 */
	[TUNER_TCL_2002N] = अणु /* TCL NTSC */
		.name   = "TCL 2002N",
		.params = tuner_tcl_2002n_params,
		.count  = ARRAY_SIZE(tuner_tcl_2002n_params),
	पूर्ण,
	[TUNER_PHILIPS_FM1256_IH3] = अणु /* Philips PAL */
		.name   = "Philips PAL/SECAM_D (FM 1256 I-H3)",
		.params = tuner_philips_fm1256_ih3_params,
		.count  = ARRAY_SIZE(tuner_philips_fm1256_ih3_params),
	पूर्ण,
	[TUNER_THOMSON_DTT7610] = अणु /* THOMSON ATSC */
		.name   = "Thomson DTT 7610 (ATSC/NTSC)",
		.params = tuner_thomson_dtt7610_params,
		.count  = ARRAY_SIZE(tuner_thomson_dtt7610_params),
		.min    = 16 *  44.00,
		.max    = 16 * 958.00,
		.stepsize = 62500,
	पूर्ण,
	[TUNER_PHILIPS_FQ1286] = अणु /* Philips NTSC */
		.name   = "Philips FQ1286",
		.params = tuner_philips_fq1286_params,
		.count  = ARRAY_SIZE(tuner_philips_fq1286_params),
	पूर्ण,
	[TUNER_PHILIPS_TDA8290] = अणु /* Philips PAL|NTSC */
		.name   = "Philips/NXP TDA 8290/8295 + 8275/8275A/18271",
		/* see tda8290.c क्रम details */ पूर्ण,
	[TUNER_TCL_2002MB] = अणु /* TCL PAL */
		.name   = "TCL 2002MB",
		.params = tuner_tcl_2002mb_params,
		.count  = ARRAY_SIZE(tuner_tcl_2002mb_params),
	पूर्ण,
	[TUNER_PHILIPS_FQ1216AME_MK4] = अणु /* Philips PAL */
		.name   = "Philips PAL/SECAM multi (FQ1216AME MK4)",
		.params = tuner_philips_fq1216ame_mk4_params,
		.count  = ARRAY_SIZE(tuner_philips_fq1216ame_mk4_params),
	पूर्ण,
	[TUNER_PHILIPS_FQ1236A_MK4] = अणु /* Philips NTSC */
		.name   = "Philips FQ1236A MK4",
		.params = tuner_philips_fq1236a_mk4_params,
		.count  = ARRAY_SIZE(tuner_philips_fq1236a_mk4_params),
	पूर्ण,
	[TUNER_YMEC_TVF_8531MF] = अणु /* Philips NTSC */
		.name   = "Ymec TVision TVF-8531MF/8831MF/8731MF",
		.params = tuner_ymec_tvf_8531mf_params,
		.count  = ARRAY_SIZE(tuner_ymec_tvf_8531mf_params),
	पूर्ण,
	[TUNER_YMEC_TVF_5533MF] = अणु /* Philips NTSC */
		.name   = "Ymec TVision TVF-5533MF",
		.params = tuner_ymec_tvf_5533mf_params,
		.count  = ARRAY_SIZE(tuner_ymec_tvf_5533mf_params),
	पूर्ण,

	/* 60-69 */
	[TUNER_THOMSON_DTT761X] = अणु /* THOMSON ATSC */
		/* DTT 7611 7611A 7612 7613 7613A 7614 7615 7615A */
		.name   = "Thomson DTT 761X (ATSC/NTSC)",
		.params = tuner_thomson_dtt761x_params,
		.count  = ARRAY_SIZE(tuner_thomson_dtt761x_params),
		.min    = 16 *  57.00,
		.max    = 16 * 863.00,
		.stepsize = 62500,
		.initdata = tua603x_agc103,
	पूर्ण,
	[TUNER_TENA_9533_DI] = अणु /* Philips PAL */
		.name   = "Tena TNF9533-D/IF/TNF9533-B/DF",
		.params = tuner_tena_9533_di_params,
		.count  = ARRAY_SIZE(tuner_tena_9533_di_params),
	पूर्ण,
	[TUNER_TEA5767] = अणु /* Philips RADIO */
		.name   = "Philips TEA5767HN FM Radio",
		/* see tea5767.c क्रम details */
	पूर्ण,
	[TUNER_PHILIPS_FMD1216ME_MK3] = अणु /* Philips PAL */
		.name   = "Philips FMD1216ME MK3 Hybrid Tuner",
		.params = tuner_philips_fmd1216me_mk3_params,
		.count  = ARRAY_SIZE(tuner_philips_fmd1216me_mk3_params),
		.min = 16 *  50.87,
		.max = 16 * 858.00,
		.stepsize = 166667,
		.initdata = tua603x_agc112,
		.sleepdata = (u8[])अणु 4, 0x9c, 0x60, 0x85, 0x54 पूर्ण,
	पूर्ण,
	[TUNER_LG_TDVS_H06XF] = अणु /* LGINNOTEK ATSC */
		.name   = "LG TDVS-H06xF", /* H061F, H062F & H064F */
		.params = tuner_lg_tdvs_h06xf_params,
		.count  = ARRAY_SIZE(tuner_lg_tdvs_h06xf_params),
		.min    = 16 *  54.00,
		.max    = 16 * 863.00,
		.stepsize = 62500,
		.initdata = tua603x_agc103,
	पूर्ण,
	[TUNER_YMEC_TVF66T5_B_DFF] = अणु /* Philips PAL */
		.name   = "Ymec TVF66T5-B/DFF",
		.params = tuner_ymec_tvf66t5_b_dff_params,
		.count  = ARRAY_SIZE(tuner_ymec_tvf66t5_b_dff_params),
	पूर्ण,
	[TUNER_LG_TALN] = अणु /* LGINNOTEK NTSC / PAL / SECAM */
		.name   = "LG TALN series",
		.params = tuner_lg_taln_params,
		.count  = ARRAY_SIZE(tuner_lg_taln_params),
	पूर्ण,
	[TUNER_PHILIPS_TD1316] = अणु /* Philips PAL */
		.name   = "Philips TD1316 Hybrid Tuner",
		.params = tuner_philips_td1316_params,
		.count  = ARRAY_SIZE(tuner_philips_td1316_params),
		.min    = 16 *  87.00,
		.max    = 16 * 895.00,
		.stepsize = 166667,
	पूर्ण,
	[TUNER_PHILIPS_TUV1236D] = अणु /* Philips ATSC */
		.name   = "Philips TUV1236D ATSC/NTSC dual in",
		.params = tuner_tuv1236d_params,
		.count  = ARRAY_SIZE(tuner_tuv1236d_params),
		.min    = 16 *  54.00,
		.max    = 16 * 864.00,
		.stepsize = 62500,
	पूर्ण,
	[TUNER_TNF_5335MF] = अणु /* Tenna PAL/NTSC */
		.name   = "Tena TNF 5335 and similar models",
		.params = tuner_tnf_5335mf_params,
		.count  = ARRAY_SIZE(tuner_tnf_5335mf_params),
	पूर्ण,

	/* 70-79 */
	[TUNER_SAMSUNG_TCPN_2121P30A] = अणु /* Samsung NTSC */
		.name   = "Samsung TCPN 2121P30A",
		.params = tuner_samsung_tcpn_2121p30a_params,
		.count  = ARRAY_SIZE(tuner_samsung_tcpn_2121p30a_params),
	पूर्ण,
	[TUNER_XC2028] = अणु /* Xceive 2028 */
		.name   = "Xceive xc2028/xc3028 tuner",
		/* see tuner-xc2028.c क्रम details */
	पूर्ण,
	[TUNER_THOMSON_FE6600] = अणु /* Thomson PAL / DVB-T */
		.name   = "Thomson FE6600",
		.params = tuner_thomson_fe6600_params,
		.count  = ARRAY_SIZE(tuner_thomson_fe6600_params),
		.min    = 16 *  44.25,
		.max    = 16 * 858.00,
		.stepsize = 166667,
	पूर्ण,
	[TUNER_SAMSUNG_TCPG_6121P30A] = अणु /* Samsung PAL */
		.name   = "Samsung TCPG 6121P30A",
		.params = tuner_samsung_tcpg_6121p30a_params,
		.count  = ARRAY_SIZE(tuner_samsung_tcpg_6121p30a_params),
	पूर्ण,
	[TUNER_TDA9887] = अणु /* Philips TDA 9887 IF PLL Demodulator.
				This chip is part of some modern tuners */
		.name   = "Philips TDA988[5,6,7] IF PLL Demodulator",
		/* see tda9887.c क्रम details */
	पूर्ण,
	[TUNER_TEA5761] = अणु /* Philips RADIO */
		.name   = "Philips TEA5761 FM Radio",
		/* see tea5767.c क्रम details */
	पूर्ण,
	[TUNER_XC5000] = अणु /* Xceive 5000 */
		.name   = "Xceive 5000 tuner",
		/* see xc5000.c क्रम details */
	पूर्ण,
	[TUNER_XC4000] = अणु /* Xceive 4000 */
		.name   = "Xceive 4000 tuner",
		/* see xc4000.c क्रम details */
	पूर्ण,
	[TUNER_TCL_MF02GIP_5N] = अणु /* TCL tuner MF02GIP-5N-E */
		.name   = "TCL tuner MF02GIP-5N-E",
		.params = tuner_tcl_mf02gip_5n_params,
		.count  = ARRAY_SIZE(tuner_tcl_mf02gip_5n_params),
	पूर्ण,
	[TUNER_PHILIPS_FMD1216MEX_MK3] = अणु /* Philips PAL */
		.name   = "Philips FMD1216MEX MK3 Hybrid Tuner",
		.params = tuner_philips_fmd1216mex_mk3_params,
		.count  = ARRAY_SIZE(tuner_philips_fmd1216mex_mk3_params),
		.min = 16 *  50.87,
		.max = 16 * 858.00,
		.stepsize = 166667,
		.initdata = tua603x_agc112,
		.sleepdata = (u8[])अणु 4, 0x9c, 0x60, 0x85, 0x54 पूर्ण,
	पूर्ण,
		[TUNER_PHILIPS_FM1216MK5] = अणु /* Philips PAL */
		.name   = "Philips PAL/SECAM multi (FM1216 MK5)",
		.params = tuner_fm1216mk5_params,
		.count  = ARRAY_SIZE(tuner_fm1216mk5_params),
	पूर्ण,

	/* 80-89 */
	[TUNER_PHILIPS_FQ1216LME_MK3] = अणु /* PAL/SECAM, Loop-thru, no FM */
		.name = "Philips FQ1216LME MK3 PAL/SECAM w/active loopthrough",
		.params = tuner_fq1216lme_mk3_params,
		.count  = ARRAY_SIZE(tuner_fq1216lme_mk3_params),
	पूर्ण,

	[TUNER_PARTSNIC_PTI_5NF05] = अणु
		.name = "Partsnic (Daewoo) PTI-5NF05",
		.params = tuner_partsnic_pti_5nf05_params,
		.count  = ARRAY_SIZE(tuner_partsnic_pti_5nf05_params),
	पूर्ण,
	[TUNER_PHILIPS_CU1216L] = अणु
		.name = "Philips CU1216L",
		.params = tuner_philips_cu1216l_params,
		.count  = ARRAY_SIZE(tuner_philips_cu1216l_params),
		.stepsize = 62500,
	पूर्ण,
	[TUNER_NXP_TDA18271] = अणु
		.name   = "NXP TDA18271",
		/* see tda18271-fe.c क्रम details */
	पूर्ण,
	[TUNER_SONY_BTF_PXN01Z] = अणु
		.name   = "Sony BTF-Pxn01Z",
		.params = tuner_sony_btf_pxn01z_params,
		.count  = ARRAY_SIZE(tuner_sony_btf_pxn01z_params),
	पूर्ण,
	[TUNER_PHILIPS_FQ1236_MK5] = अणु /* NTSC, TDA9885, no FM radio */
		.name   = "Philips FQ1236 MK5",
		.params = tuner_philips_fq1236_mk5_params,
		.count  = ARRAY_SIZE(tuner_philips_fq1236_mk5_params),
	पूर्ण,
	[TUNER_TENA_TNF_5337] = अणु /* Tena 5337 MFD */
		.name   = "Tena TNF5337 MFD",
		.params = tuner_tena_tnf_5337_params,
		.count  = ARRAY_SIZE(tuner_tena_tnf_5337_params),
	पूर्ण,
	[TUNER_XC5000C] = अणु /* Xceive 5000C */
		.name   = "Xceive 5000C tuner",
		/* see xc5000.c क्रम details */
	पूर्ण,
	[TUNER_SONY_BTF_PG472Z] = अणु
		.name   = "Sony BTF-PG472Z PAL/SECAM",
		.params = tuner_sony_btf_pg472z_params,
		.count  = ARRAY_SIZE(tuner_sony_btf_pg472z_params),
	पूर्ण,

	/* 90-99 */
	[TUNER_SONY_BTF_PK467Z] = अणु
		.name   = "Sony BTF-PK467Z NTSC-M-JP",
		.params = tuner_sony_btf_pg467z_params,
		.count  = ARRAY_SIZE(tuner_sony_btf_pg467z_params),
	पूर्ण,
	[TUNER_SONY_BTF_PB463Z] = अणु
		.name   = "Sony BTF-PB463Z NTSC-M",
		.params = tuner_sony_btf_pg463z_params,
		.count  = ARRAY_SIZE(tuner_sony_btf_pg463z_params),
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(tuners);

अचिन्हित स्थिर पूर्णांक tuner_count = ARRAY_SIZE(tuners);
EXPORT_SYMBOL(tuner_count);

MODULE_DESCRIPTION("Simple tuner device type database");
MODULE_AUTHOR("Ralph Metzler, Gerd Knorr, Gunther Mayer");
MODULE_LICENSE("GPL");
