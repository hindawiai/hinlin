<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pid.c PID controller क्रम testing cooling devices
 *
 * Copyright (C) 2012 Intel Corporation. All rights reserved.
 *
 * Author Name Jacob Pan <jacob.jun.pan@linux.पूर्णांकel.com>
 */

#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानक_निवेशt.h>
#समावेश <sys/types.h>
#समावेश <dirent.h>
#समावेश <libपूर्णांकl.h>
#समावेश <प्रकार.स>
#समावेश <निश्चित.स>
#समावेश <समय.स>
#समावेश <सीमा.स>
#समावेश <गणित.स>
#समावेश <sys/स्थिति.स>
#समावेश <syslog.h>

#समावेश "tmon.h"

/**************************************************************************
 * PID (Proportional-Integral-Derivative) controller is commonly used in
 * linear control प्रणाली, consider the the process.
 * G(s) = U(s)/E(s)
 * kp = proportional gain
 * ki = पूर्णांकegral gain
 * kd = derivative gain
 * Ts
 * We use type C Alan Bradley equation which takes set poपूर्णांक off the
 * output dependency in P and D term.
 *
 *   y[k] = y[k-1] - kp*(x[k] - x[k-1]) + Ki*Ts*e[k] - Kd*(x[k]
 *          - 2*x[k-1]+x[k-2])/Ts
 *
 *
 ***********************************************************************/
काष्ठा pid_params p_param;
/* cached data from previous loop */
अटल द्विगुन xk_1, xk_2; /* input temperature x[k-#] */

/*
 * TODO: make PID parameters tuned स्वतःmatically,
 * 1. use CPU burn to produce खोलो loop unit step response
 * 2. calculate PID based on Ziegler-Nichols rule
 *
 * add a flag क्रम tuning PID
 */
पूर्णांक init_thermal_controller(व्योम)
अणु
	पूर्णांक ret = 0;

	/* init pid params */
	p_param.ts = tickसमय;
	/* TODO: get it from TUI tuning tab */
	p_param.kp = .36;
	p_param.ki = 5.0;
	p_param.kd = 0.19;

	p_param.t_target = target_temp_user;

	वापस ret;
पूर्ण

व्योम controller_reset(व्योम)
अणु
	/* TODO: relax control data when not over thermal limit */
	syslog(LOG_DEBUG, "TC inactive, relax p-state\n");
	p_param.y_k = 0.0;
	xk_1 = 0.0;
	xk_2 = 0.0;
	set_ctrl_state(0);
पूर्ण

/* To be called at समय पूर्णांकerval Ts. Type C PID controller.
 *    y[k] = y[k-1] - kp*(x[k] - x[k-1]) + Ki*Ts*e[k] - Kd*(x[k]
 *          - 2*x[k-1]+x[k-2])/Ts
 * TODO: add low pass filter क्रम D term
 */
#घोषणा GUARD_BAND (2)
व्योम controller_handler(स्थिर द्विगुन xk, द्विगुन *yk)
अणु
	द्विगुन ek;
	द्विगुन p_term, i_term, d_term;

	ek = p_param.t_target - xk; /* error */
	अगर (ek >= 3.0) अणु
		syslog(LOG_DEBUG, "PID: %3.1f Below set point %3.1f, stop\n",
			xk, p_param.t_target);
		controller_reset();
		*yk = 0.0;
		वापस;
	पूर्ण
	/* compute पूर्णांकermediate PID terms */
	p_term = -p_param.kp * (xk - xk_1);
	i_term = p_param.kp * p_param.ki * p_param.ts * ek;
	d_term = -p_param.kp * p_param.kd * (xk - 2 * xk_1 + xk_2) / p_param.ts;
	/* compute output */
	*yk += p_term + i_term + d_term;
	/* update sample data */
	xk_1 = xk;
	xk_2 = xk_1;

	/* clamp output adjusपंचांगent range */
	अगर (*yk < -LIMIT_HIGH)
		*yk = -LIMIT_HIGH;
	अन्यथा अगर (*yk > -LIMIT_LOW)
		*yk = -LIMIT_LOW;

	p_param.y_k = *yk;

	set_ctrl_state(lround(भ_असल(p_param.y_k)));

पूर्ण
