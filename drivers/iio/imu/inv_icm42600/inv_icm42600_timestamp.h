<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2020 Invensense, Inc.
 */

#अगर_अघोषित INV_ICM42600_TIMESTAMP_H_
#घोषणा INV_ICM42600_TIMESTAMP_H_

#समावेश <linux/kernel.h>

काष्ठा inv_icm42600_state;

/**
 * काष्ठा inv_icm42600_बारtamp_पूर्णांकerval - बारtamps पूर्णांकerval
 * @lo:	पूर्णांकerval lower bound
 * @up:	पूर्णांकerval upper bound
 */
काष्ठा inv_icm42600_बारtamp_पूर्णांकerval अणु
	पूर्णांक64_t lo;
	पूर्णांक64_t up;
पूर्ण;

/**
 * काष्ठा inv_icm42600_बारtamp_acc - accumulator क्रम computing an estimation
 * @val:	current estimation of the value, the mean of all values
 * @idx:	current index of the next मुक्त place in values table
 * @values:	table of all measured values, use क्रम computing the mean
 */
काष्ठा inv_icm42600_बारtamp_acc अणु
	uपूर्णांक32_t val;
	माप_प्रकार idx;
	uपूर्णांक32_t values[32];
पूर्ण;

/**
 * काष्ठा inv_icm42600_बारtamp - बारtamp management states
 * @it:			पूर्णांकerrupts पूर्णांकerval बारtamps
 * @बारtamp:		store last बारtamp क्रम computing next data बारtamp
 * @mult:		current पूर्णांकernal period multiplier
 * @new_mult:		new set पूर्णांकernal period multiplier (not yet effective)
 * @period:		measured current period of the sensor
 * @chip_period:	accumulator क्रम computing पूर्णांकernal chip period
 */
काष्ठा inv_icm42600_बारtamp अणु
	काष्ठा inv_icm42600_बारtamp_पूर्णांकerval it;
	पूर्णांक64_t बारtamp;
	uपूर्णांक32_t mult;
	uपूर्णांक32_t new_mult;
	uपूर्णांक32_t period;
	काष्ठा inv_icm42600_बारtamp_acc chip_period;
पूर्ण;

व्योम inv_icm42600_बारtamp_init(काष्ठा inv_icm42600_बारtamp *ts,
				 uपूर्णांक32_t period);

पूर्णांक inv_icm42600_बारtamp_setup(काष्ठा inv_icm42600_state *st);

पूर्णांक inv_icm42600_बारtamp_update_odr(काष्ठा inv_icm42600_बारtamp *ts,
				      uपूर्णांक32_t period, bool fअगरo);

व्योम inv_icm42600_बारtamp_पूर्णांकerrupt(काष्ठा inv_icm42600_बारtamp *ts,
				      uपूर्णांक32_t fअगरo_period, माप_प्रकार fअगरo_nb,
				      माप_प्रकार sensor_nb, पूर्णांक64_t बारtamp);

अटल अंतरभूत पूर्णांक64_t
inv_icm42600_बारtamp_pop(काष्ठा inv_icm42600_बारtamp *ts)
अणु
	ts->बारtamp += ts->period;
	वापस ts->बारtamp;
पूर्ण

व्योम inv_icm42600_बारtamp_apply_odr(काष्ठा inv_icm42600_बारtamp *ts,
				      uपूर्णांक32_t fअगरo_period, माप_प्रकार fअगरo_nb,
				      अचिन्हित पूर्णांक fअगरo_no);

अटल अंतरभूत व्योम
inv_icm42600_बारtamp_reset(काष्ठा inv_icm42600_बारtamp *ts)
अणु
	स्थिर काष्ठा inv_icm42600_बारtamp_पूर्णांकerval पूर्णांकerval_init = अणु0LL, 0LLपूर्ण;

	ts->it = पूर्णांकerval_init;
	ts->बारtamp = 0;
पूर्ण

#पूर्ण_अगर
