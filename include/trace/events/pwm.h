<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM pwm

#अगर !defined(_TRACE_PWM_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PWM_H

#समावेश <linux/pwm.h>
#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(pwm,

	TP_PROTO(काष्ठा pwm_device *pwm, स्थिर काष्ठा pwm_state *state),

	TP_ARGS(pwm, state),

	TP_STRUCT__entry(
		__field(काष्ठा pwm_device *, pwm)
		__field(u64, period)
		__field(u64, duty_cycle)
		__field(क्रमागत pwm_polarity, polarity)
		__field(bool, enabled)
	),

	TP_fast_assign(
		__entry->pwm = pwm;
		__entry->period = state->period;
		__entry->duty_cycle = state->duty_cycle;
		__entry->polarity = state->polarity;
		__entry->enabled = state->enabled;
	),

	TP_prपूर्णांकk("%p: period=%llu duty_cycle=%llu polarity=%d enabled=%d",
		  __entry->pwm, __entry->period, __entry->duty_cycle,
		  __entry->polarity, __entry->enabled)

);

DEFINE_EVENT(pwm, pwm_apply,

	TP_PROTO(काष्ठा pwm_device *pwm, स्थिर काष्ठा pwm_state *state),

	TP_ARGS(pwm, state)

);

DEFINE_EVENT(pwm, pwm_get,

	TP_PROTO(काष्ठा pwm_device *pwm, स्थिर काष्ठा pwm_state *state),

	TP_ARGS(pwm, state)

);

#पूर्ण_अगर /* _TRACE_PWM_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
