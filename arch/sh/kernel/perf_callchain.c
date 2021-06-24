<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance event callchain support - SuperH architecture code
 *
 * Copyright (C) 2009  Paul Mundt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/percpu.h>
#समावेश <यंत्र/unwinder.h>
#समावेश <यंत्र/ptrace.h>

अटल व्योम callchain_address(व्योम *data, अचिन्हित दीर्घ addr, पूर्णांक reliable)
अणु
	काष्ठा perf_callchain_entry_ctx *entry = data;

	अगर (reliable)
		perf_callchain_store(entry, addr);
पूर्ण

अटल स्थिर काष्ठा stacktrace_ops callchain_ops = अणु
	.address	= callchain_address,
पूर्ण;

व्योम
perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry, काष्ठा pt_regs *regs)
अणु
	perf_callchain_store(entry, regs->pc);

	unwind_stack(शून्य, regs, शून्य, &callchain_ops, entry);
पूर्ण
