<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2017 National Instruments Corp.
 *
 * Author: Julia Cartwright <julia@ni.com>
 *
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/futex.h>

#समावेश "event-parse.h"

#घोषणा ARRAY_SIZE(_a) (माप(_a) / माप((_a)[0]))

काष्ठा futex_args अणु
	अचिन्हित दीर्घ दीर्घ	uaddr;
	अचिन्हित दीर्घ दीर्घ	op;
	अचिन्हित दीर्घ दीर्घ	val;
	अचिन्हित दीर्घ दीर्घ	uसमय; /* or val2 */
	अचिन्हित दीर्घ दीर्घ	uaddr2;
	अचिन्हित दीर्घ दीर्घ	val3;
पूर्ण;

काष्ठा futex_op अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*fmt_val;
	स्थिर अक्षर	*fmt_uसमय;
	स्थिर अक्षर	*fmt_uaddr2;
	स्थिर अक्षर	*fmt_val3;
पूर्ण;

अटल स्थिर काष्ठा futex_op futex_op_tbl[] = अणु
	अणु            "FUTEX_WAIT", " val=0x%08llx", " utime=0x%08llx",               शून्य,             शून्य पूर्ण,
	अणु            "FUTEX_WAKE",     " val=%llu",              शून्य,               शून्य,             शून्य पूर्ण,
	अणु              "FUTEX_FD",     " val=%llu",              शून्य,               शून्य,             शून्य पूर्ण,
	अणु         "FUTEX_REQUEUE",     " val=%llu",      " val2=%llu", " uaddr2=0x%08llx",             शून्य पूर्ण,
	अणु     "FUTEX_CMP_REQUEUE",     " val=%llu",      " val2=%llu", " uaddr2=0x%08llx", " val3=0x%08llx" पूर्ण,
	अणु         "FUTEX_WAKE_OP",     " val=%llu",      " val2=%llu", " uaddr2=0x%08llx", " val3=0x%08llx" पूर्ण,
	अणु         "FUTEX_LOCK_PI",            शून्य, " utime=0x%08llx",               शून्य,             शून्य पूर्ण,
	अणु       "FUTEX_UNLOCK_PI",            शून्य,              शून्य,               शून्य,             शून्य पूर्ण,
	अणु      "FUTEX_TRYLOCK_PI",            शून्य,              शून्य,               शून्य,             शून्य पूर्ण,
	अणु     "FUTEX_WAIT_BITSET", " val=0x%08llx", " utime=0x%08llx",               शून्य, " val3=0x%08llx" पूर्ण,
	अणु     "FUTEX_WAKE_BITSET",     " val=%llu",              शून्य,               शून्य, " val3=0x%08llx" पूर्ण,
	अणु "FUTEX_WAIT_REQUEUE_PI", " val=0x%08llx", " utime=0x%08llx", " uaddr2=0x%08llx", " val3=0x%08llx" पूर्ण,
	अणु  "FUTEX_CMP_REQUEUE_PI",     " val=%llu",      " val2=%llu", " uaddr2=0x%08llx", " val3=0x%08llx" पूर्ण,
पूर्ण;


अटल व्योम futex_prपूर्णांक(काष्ठा trace_seq *s, स्थिर काष्ठा futex_args *args,
			स्थिर काष्ठा futex_op *fop)
अणु
	trace_seq_म_लिखो(s, " uaddr=0x%08llx", args->uaddr);

	अगर (fop->fmt_val)
		trace_seq_म_लिखो(s, fop->fmt_val, args->val);

	अगर (fop->fmt_uसमय)
		trace_seq_म_लिखो(s,fop->fmt_uसमय, args->uसमय);

	अगर (fop->fmt_uaddr2)
		trace_seq_म_लिखो(s, fop->fmt_uaddr2, args->uaddr2);

	अगर (fop->fmt_val3)
		trace_seq_म_लिखो(s, fop->fmt_val3, args->val3);
पूर्ण

अटल पूर्णांक futex_handler(काष्ठा trace_seq *s, काष्ठा tep_record *record,
			 काष्ठा tep_event *event, व्योम *context)
अणु
	स्थिर काष्ठा futex_op *fop;
	काष्ठा futex_args args;
	अचिन्हित दीर्घ दीर्घ cmd;

	अगर (tep_get_field_val(s, event, "uaddr", record, &args.uaddr, 1))
		वापस 1;

	अगर (tep_get_field_val(s, event, "op", record, &args.op, 1))
		वापस 1;

	अगर (tep_get_field_val(s, event, "val", record, &args.val, 1))
		वापस 1;

	अगर (tep_get_field_val(s, event, "utime", record, &args.uसमय, 1))
		वापस 1;

	अगर (tep_get_field_val(s, event, "uaddr2", record, &args.uaddr2, 1))
		वापस 1;

	अगर (tep_get_field_val(s, event, "val3", record, &args.val3, 1))
		वापस 1;

	cmd = args.op & FUTEX_CMD_MASK;
	अगर (cmd >= ARRAY_SIZE(futex_op_tbl))
		वापस 1;

	fop = &futex_op_tbl[cmd];

	trace_seq_म_लिखो(s, "op=%s", fop->name);

	अगर (args.op & FUTEX_PRIVATE_FLAG)
		trace_seq_माला_दो(s, "|FUTEX_PRIVATE_FLAG");

	अगर (args.op & FUTEX_CLOCK_REALTIME)
		trace_seq_माला_दो(s, "|FUTEX_CLOCK_REALTIME");

	futex_prपूर्णांक(s, &args, fop);
	वापस 0;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_event_handler(tep, -1, "syscalls", "sys_enter_futex",
				   futex_handler, शून्य);
	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_event_handler(tep, -1, "syscalls", "sys_enter_futex",
				     futex_handler, शून्य);
पूर्ण
