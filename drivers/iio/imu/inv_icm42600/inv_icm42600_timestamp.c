<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 Invensense, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/regmap.h>
#समावेश <linux/math64.h>

#समावेश "inv_icm42600.h"
#समावेश "inv_icm42600_timestamp.h"

/* पूर्णांकernal chip period is 32kHz, 31250ns */
#घोषणा INV_ICM42600_TIMESTAMP_PERIOD		31250
/* allow a jitter of +/- 2% */
#घोषणा INV_ICM42600_TIMESTAMP_JITTER		2
/* compute min and max periods accepted */
#घोषणा INV_ICM42600_TIMESTAMP_MIN_PERIOD(_p)		\
	(((_p) * (100 - INV_ICM42600_TIMESTAMP_JITTER)) / 100)
#घोषणा INV_ICM42600_TIMESTAMP_MAX_PERIOD(_p)		\
	(((_p) * (100 + INV_ICM42600_TIMESTAMP_JITTER)) / 100)

/* Add a new value inside an accumulator and update the estimate value */
अटल व्योम inv_update_acc(काष्ठा inv_icm42600_बारtamp_acc *acc, uपूर्णांक32_t val)
अणु
	uपूर्णांक64_t sum = 0;
	माप_प्रकार i;

	acc->values[acc->idx++] = val;
	अगर (acc->idx >= ARRAY_SIZE(acc->values))
		acc->idx = 0;

	/* compute the mean of all stored values, use 0 as empty slot */
	क्रम (i = 0; i < ARRAY_SIZE(acc->values); ++i) अणु
		अगर (acc->values[i] == 0)
			अवरोध;
		sum += acc->values[i];
	पूर्ण

	acc->val = भाग_u64(sum, i);
पूर्ण

व्योम inv_icm42600_बारtamp_init(काष्ठा inv_icm42600_बारtamp *ts,
				 uपूर्णांक32_t period)
अणु
	/* initial odr क्रम sensor after reset is 1kHz */
	स्थिर uपूर्णांक32_t शेष_period = 1000000;

	/* current multiplier and period values after reset */
	ts->mult = शेष_period / INV_ICM42600_TIMESTAMP_PERIOD;
	ts->period = शेष_period;
	/* new set multiplier is the one from chip initialization */
	ts->new_mult = period / INV_ICM42600_TIMESTAMP_PERIOD;

	/* use theoretical value क्रम chip period */
	inv_update_acc(&ts->chip_period, INV_ICM42600_TIMESTAMP_PERIOD);
पूर्ण

पूर्णांक inv_icm42600_बारtamp_setup(काष्ठा inv_icm42600_state *st)
अणु
	अचिन्हित पूर्णांक val;

	/* enable बारtamp रेजिस्टर */
	val = INV_ICM42600_TMST_CONFIG_TMST_TO_REGS_EN |
	      INV_ICM42600_TMST_CONFIG_TMST_EN;
	वापस regmap_update_bits(st->map, INV_ICM42600_REG_TMST_CONFIG,
				  INV_ICM42600_TMST_CONFIG_MASK, val);
पूर्ण

पूर्णांक inv_icm42600_बारtamp_update_odr(काष्ठा inv_icm42600_बारtamp *ts,
				      uपूर्णांक32_t period, bool fअगरo)
अणु
	/* when FIFO is on, prevent odr change अगर one is alपढ़ोy pending */
	अगर (fअगरo && ts->new_mult != 0)
		वापस -EAGAIN;

	ts->new_mult = period / INV_ICM42600_TIMESTAMP_PERIOD;

	वापस 0;
पूर्ण

अटल bool inv_validate_period(uपूर्णांक32_t period, uपूर्णांक32_t mult)
अणु
	स्थिर uपूर्णांक32_t chip_period = INV_ICM42600_TIMESTAMP_PERIOD;
	uपूर्णांक32_t period_min, period_max;

	/* check that period is acceptable */
	period_min = INV_ICM42600_TIMESTAMP_MIN_PERIOD(chip_period) * mult;
	period_max = INV_ICM42600_TIMESTAMP_MAX_PERIOD(chip_period) * mult;
	अगर (period > period_min && period < period_max)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool inv_compute_chip_period(काष्ठा inv_icm42600_बारtamp *ts,
				    uपूर्णांक32_t mult, uपूर्णांक32_t period)
अणु
	uपूर्णांक32_t new_chip_period;

	अगर (!inv_validate_period(period, mult))
		वापस false;

	/* update chip पूर्णांकernal period estimation */
	new_chip_period = period / mult;
	inv_update_acc(&ts->chip_period, new_chip_period);

	वापस true;
पूर्ण

व्योम inv_icm42600_बारtamp_पूर्णांकerrupt(काष्ठा inv_icm42600_बारtamp *ts,
				      uपूर्णांक32_t fअगरo_period, माप_प्रकार fअगरo_nb,
				      माप_प्रकार sensor_nb, पूर्णांक64_t बारtamp)
अणु
	काष्ठा inv_icm42600_बारtamp_पूर्णांकerval *it;
	पूर्णांक64_t delta, पूर्णांकerval;
	स्थिर uपूर्णांक32_t fअगरo_mult = fअगरo_period / INV_ICM42600_TIMESTAMP_PERIOD;
	uपूर्णांक32_t period = ts->period;
	पूर्णांक32_t m;
	bool valid = false;

	अगर (fअगरo_nb == 0)
		वापस;

	/* update पूर्णांकerrupt बारtamp and compute chip and sensor periods */
	it = &ts->it;
	it->lo = it->up;
	it->up = बारtamp;
	delta = it->up - it->lo;
	अगर (it->lo != 0) अणु
		/* compute period: delta समय भागided by number of samples */
		period = भाग_s64(delta, fअगरo_nb);
		valid = inv_compute_chip_period(ts, fअगरo_mult, period);
		/* update sensor period अगर chip पूर्णांकernal period is updated */
		अगर (valid)
			ts->period = ts->mult * ts->chip_period.val;
	पूर्ण

	/* no previous data, compute theoritical value from पूर्णांकerrupt */
	अगर (ts->बारtamp == 0) अणु
		/* elapsed समय: sensor period * sensor samples number */
		पूर्णांकerval = (पूर्णांक64_t)ts->period * (पूर्णांक64_t)sensor_nb;
		ts->बारtamp = it->up - पूर्णांकerval;
		वापस;
	पूर्ण

	/* अगर पूर्णांकerrupt पूर्णांकerval is valid, sync with पूर्णांकerrupt बारtamp */
	अगर (valid) अणु
		/* compute measured fअगरo_period */
		fअगरo_period = fअगरo_mult * ts->chip_period.val;
		/* delta समय between last sample and last पूर्णांकerrupt */
		delta = it->lo - ts->बारtamp;
		/* अगर there are multiple samples, go back to first one */
		जबतक (delta >= (fअगरo_period * 3 / 2))
			delta -= fअगरo_period;
		/* compute maximal adjusपंचांगent value */
		m = INV_ICM42600_TIMESTAMP_MAX_PERIOD(ts->period) - ts->period;
		अगर (delta > m)
			delta = m;
		अन्यथा अगर (delta < -m)
			delta = -m;
		ts->बारtamp += delta;
	पूर्ण
पूर्ण

व्योम inv_icm42600_बारtamp_apply_odr(काष्ठा inv_icm42600_बारtamp *ts,
				      uपूर्णांक32_t fअगरo_period, माप_प्रकार fअगरo_nb,
				      अचिन्हित पूर्णांक fअगरo_no)
अणु
	पूर्णांक64_t पूर्णांकerval;
	uपूर्णांक32_t fअगरo_mult;

	अगर (ts->new_mult == 0)
		वापस;

	/* update to new multiplier and update period */
	ts->mult = ts->new_mult;
	ts->new_mult = 0;
	ts->period = ts->mult * ts->chip_period.val;

	/*
	 * After ODR change the समय पूर्णांकerval with the previous sample is
	 * undertermined (depends when the change occures). So we compute the
	 * बारtamp from the current पूर्णांकerrupt using the new FIFO period, the
	 * total number of samples and the current sample numero.
	 */
	अगर (ts->बारtamp != 0) अणु
		/* compute measured fअगरo period */
		fअगरo_mult = fअगरo_period / INV_ICM42600_TIMESTAMP_PERIOD;
		fअगरo_period = fअगरo_mult * ts->chip_period.val;
		/* computes समय पूर्णांकerval between पूर्णांकerrupt and this sample */
		पूर्णांकerval = (पूर्णांक64_t)(fअगरo_nb - fअगरo_no) * (पूर्णांक64_t)fअगरo_period;
		ts->बारtamp = ts->it.up - पूर्णांकerval;
	पूर्ण
पूर्ण
