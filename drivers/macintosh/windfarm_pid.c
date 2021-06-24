<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. Generic PID helpers
 *
 * (c) Copyright 2005 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>

#समावेश "windfarm_pid.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(args...)	prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

व्योम wf_pid_init(काष्ठा wf_pid_state *st, काष्ठा wf_pid_param *param)
अणु
	स_रखो(st, 0, माप(काष्ठा wf_pid_state));
	st->param = *param;
	st->first = 1;
पूर्ण
EXPORT_SYMBOL_GPL(wf_pid_init);

s32 wf_pid_run(काष्ठा wf_pid_state *st, s32 new_sample)
अणु
	s64	error, पूर्णांकeg, deriv;
	s32	target;
	पूर्णांक	i, hlen = st->param.history_len;

	/* Calculate error term */
	error = new_sample - st->param.itarget;

	/* Get samples पूर्णांकo our history buffer */
	अगर (st->first) अणु
		क्रम (i = 0; i < hlen; i++) अणु
			st->samples[i] = new_sample;
			st->errors[i] = error;
		पूर्ण
		st->first = 0;
		st->index = 0;
	पूर्ण अन्यथा अणु
		st->index = (st->index + 1) % hlen;
		st->samples[st->index] = new_sample;
		st->errors[st->index] = error;
	पूर्ण

	/* Calculate पूर्णांकegral term */
	क्रम (i = 0, पूर्णांकeg = 0; i < hlen; i++)
		पूर्णांकeg += st->errors[(st->index + hlen - i) % hlen];
	पूर्णांकeg *= st->param.पूर्णांकerval;

	/* Calculate derivative term */
	deriv = st->errors[st->index] -
		st->errors[(st->index + hlen - 1) % hlen];
	deriv /= st->param.पूर्णांकerval;

	/* Calculate target */
	target = (s32)((पूर्णांकeg * (s64)st->param.gr + deriv * (s64)st->param.gd +
		  error * (s64)st->param.gp) >> 36);
	अगर (st->param.additive)
		target += st->target;
	target = max(target, st->param.min);
	target = min(target, st->param.max);
	st->target = target;

	वापस st->target;
पूर्ण
EXPORT_SYMBOL_GPL(wf_pid_run);

व्योम wf_cpu_pid_init(काष्ठा wf_cpu_pid_state *st,
		     काष्ठा wf_cpu_pid_param *param)
अणु
	स_रखो(st, 0, माप(काष्ठा wf_cpu_pid_state));
	st->param = *param;
	st->first = 1;
पूर्ण
EXPORT_SYMBOL_GPL(wf_cpu_pid_init);

s32 wf_cpu_pid_run(काष्ठा wf_cpu_pid_state *st, s32 new_घातer, s32 new_temp)
अणु
	s64	पूर्णांकeg, deriv, prop;
	s32	error, target, sval, adj;
	पूर्णांक	i, hlen = st->param.history_len;

	/* Calculate error term */
	error = st->param.pmaxadj - new_घातer;

	/* Get samples पूर्णांकo our history buffer */
	अगर (st->first) अणु
		क्रम (i = 0; i < hlen; i++) अणु
			st->घातers[i] = new_घातer;
			st->errors[i] = error;
		पूर्ण
		st->temps[0] = st->temps[1] = new_temp;
		st->first = 0;
		st->index = st->tindex = 0;
	पूर्ण अन्यथा अणु
		st->index = (st->index + 1) % hlen;
		st->घातers[st->index] = new_घातer;
		st->errors[st->index] = error;
		st->tindex = (st->tindex + 1) % 2;
		st->temps[st->tindex] = new_temp;
	पूर्ण

	/* Calculate पूर्णांकegral term */
	क्रम (i = 0, पूर्णांकeg = 0; i < hlen; i++)
		पूर्णांकeg += st->errors[(st->index + hlen - i) % hlen];
	पूर्णांकeg *= st->param.पूर्णांकerval;
	पूर्णांकeg *= st->param.gr;
	sval = st->param.पंचांगax - (s32)(पूर्णांकeg >> 20);
	adj = min(st->param.ttarget, sval);

	DBG("integ: %lx, sval: %lx, adj: %lx\n", पूर्णांकeg, sval, adj);

	/* Calculate derivative term */
	deriv = st->temps[st->tindex] -
		st->temps[(st->tindex + 2 - 1) % 2];
	deriv /= st->param.पूर्णांकerval;
	deriv *= st->param.gd;

	/* Calculate proportional term */
	prop = st->last_delta = (new_temp - adj);
	prop *= st->param.gp;

	DBG("deriv: %lx, prop: %lx\n", deriv, prop);

	/* Calculate target */
	target = st->target + (s32)((deriv + prop) >> 36);
	target = max(target, st->param.min);
	target = min(target, st->param.max);
	st->target = target;

	वापस st->target;
पूर्ण
EXPORT_SYMBOL_GPL(wf_cpu_pid_run);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("PID algorithm for PowerMacs thermal control");
MODULE_LICENSE("GPL");
