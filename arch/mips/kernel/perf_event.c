<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux perक्रमmance counter support क्रम MIPS.
 *
 * Copyright (C) 2010 MIPS Technologies, Inc.
 * Author: Deng-Cheng Zhu
 *
 * This code is based on the implementation क्रम ARM, which is in turn
 * based on the sparc64 perf event code and the x86 code. Perक्रमmance
 * counter access is based on the MIPS Oprofile code. And the callchain
 * support references the code of MIPS stacktrace.c.
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/stacktrace.h>

/* Callchain handling code. */

/*
 * Leave userspace callchain empty क्रम now. When we find a way to trace
 * the user stack callchains, we will add it here.
 */

अटल व्योम save_raw_perf_callchain(काष्ठा perf_callchain_entry_ctx *entry,
				    अचिन्हित दीर्घ reg29)
अणु
	अचिन्हित दीर्घ *sp = (अचिन्हित दीर्घ *)reg29;
	अचिन्हित दीर्घ addr;

	जबतक (!kstack_end(sp)) अणु
		addr = *sp++;
		अगर (__kernel_text_address(addr)) अणु
			perf_callchain_store(entry, addr);
			अगर (entry->nr >= entry->max_stack)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry,
			   काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sp = regs->regs[29];
#अगर_घोषित CONFIG_KALLSYMS
	अचिन्हित दीर्घ ra = regs->regs[31];
	अचिन्हित दीर्घ pc = regs->cp0_epc;

	अगर (raw_show_trace || !__kernel_text_address(pc)) अणु
		अचिन्हित दीर्घ stack_page =
			(अचिन्हित दीर्घ)task_stack_page(current);
		अगर (stack_page && sp >= stack_page &&
		    sp <= stack_page + THREAD_SIZE - 32)
			save_raw_perf_callchain(entry, sp);
		वापस;
	पूर्ण
	करो अणु
		perf_callchain_store(entry, pc);
		अगर (entry->nr >= entry->max_stack)
			अवरोध;
		pc = unwind_stack(current, &sp, pc, &ra);
	पूर्ण जबतक (pc);
#अन्यथा
	save_raw_perf_callchain(entry, sp);
#पूर्ण_अगर
पूर्ण
