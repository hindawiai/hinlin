<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * nop tracer
 *
 * Copyright (C) 2008 Steven Noonan <steven@uplinkद_असल.net>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/ftrace.h>

#समावेश "trace.h"

/* Our two options */
क्रमागत अणु
	TRACE_NOP_OPT_ACCEPT = 0x1,
	TRACE_NOP_OPT_REFUSE = 0x2
पूर्ण;

/* Options क्रम the tracer (see trace_options file) */
अटल काष्ठा tracer_opt nop_opts[] = अणु
	/* Option that will be accepted by set_flag callback */
	अणु TRACER_OPT(test_nop_accept, TRACE_NOP_OPT_ACCEPT) पूर्ण,
	/* Option that will be refused by set_flag callback */
	अणु TRACER_OPT(test_nop_refuse, TRACE_NOP_OPT_REFUSE) पूर्ण,
	अणु पूर्ण /* Always set a last empty entry */
पूर्ण;

अटल काष्ठा tracer_flags nop_flags = अणु
	/* You can check your flags value here when you want. */
	.val = 0, /* By शेष: all flags disabled */
	.opts = nop_opts
पूर्ण;

अटल काष्ठा trace_array	*ctx_trace;

अटल व्योम start_nop_trace(काष्ठा trace_array *tr)
अणु
	/* Nothing to करो! */
पूर्ण

अटल व्योम stop_nop_trace(काष्ठा trace_array *tr)
अणु
	/* Nothing to करो! */
पूर्ण

अटल पूर्णांक nop_trace_init(काष्ठा trace_array *tr)
अणु
	ctx_trace = tr;
	start_nop_trace(tr);
	वापस 0;
पूर्ण

अटल व्योम nop_trace_reset(काष्ठा trace_array *tr)
अणु
	stop_nop_trace(tr);
पूर्ण

/* It only serves as a संकेत handler and a callback to
 * accept or refuse the setting of a flag.
 * If you करोn't implement it, then the flag setting will be
 * स्वतःmatically accepted.
 */
अटल पूर्णांक nop_set_flag(काष्ठा trace_array *tr, u32 old_flags, u32 bit, पूर्णांक set)
अणु
	/*
	 * Note that you करोn't need to update nop_flags.val yourself.
	 * The tracing Api will करो it स्वतःmatically अगर you वापस 0
	 */
	अगर (bit == TRACE_NOP_OPT_ACCEPT) अणु
		prपूर्णांकk(KERN_DEBUG "nop_test_accept flag set to %d: we accept."
			" Now cat trace_options to see the result\n",
			set);
		वापस 0;
	पूर्ण

	अगर (bit == TRACE_NOP_OPT_REFUSE) अणु
		prपूर्णांकk(KERN_DEBUG "nop_test_refuse flag set to %d: we refuse."
			" Now cat trace_options to see the result\n",
			set);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


काष्ठा tracer nop_trace __पढ़ो_mostly =
अणु
	.name		= "nop",
	.init		= nop_trace_init,
	.reset		= nop_trace_reset,
#अगर_घोषित CONFIG_FTRACE_SELFTEST
	.selftest	= trace_selftest_startup_nop,
#पूर्ण_अगर
	.flags		= &nop_flags,
	.set_flag	= nop_set_flag,
	.allow_instances = true,
पूर्ण;

