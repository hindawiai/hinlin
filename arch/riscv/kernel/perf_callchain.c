<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2019 Hangzhou C-SKY Microप्रणालीs co.,ltd. */

#समावेश <linux/perf_event.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/stacktrace.h>

/*
 * Get the वापस address क्रम a single stackframe and वापस a poपूर्णांकer to the
 * next frame tail.
 */
अटल अचिन्हित दीर्घ user_backtrace(काष्ठा perf_callchain_entry_ctx *entry,
				    अचिन्हित दीर्घ fp, अचिन्हित दीर्घ reg_ra)
अणु
	काष्ठा stackframe buftail;
	अचिन्हित दीर्घ ra = 0;
	अचिन्हित दीर्घ *user_frame_tail =
			(अचिन्हित दीर्घ *)(fp - माप(काष्ठा stackframe));

	/* Check accessibility of one काष्ठा frame_tail beyond */
	अगर (!access_ok(user_frame_tail, माप(buftail)))
		वापस 0;
	अगर (__copy_from_user_inatomic(&buftail, user_frame_tail,
				      माप(buftail)))
		वापस 0;

	अगर (reg_ra != 0)
		ra = reg_ra;
	अन्यथा
		ra = buftail.ra;

	fp = buftail.fp;
	अगर (ra != 0)
		perf_callchain_store(entry, ra);
	अन्यथा
		वापस 0;

	वापस fp;
पूर्ण

/*
 * This will be called when the target is in user mode
 * This function will only be called when we use
 * "PERF_SAMPLE_CALLCHAIN" in
 * kernel/events/core.c:perf_prepare_sample()
 *
 * How to trigger perf_callchain_[user/kernel] :
 * $ perf record -e cpu-घड़ी --call-graph fp ./program
 * $ perf report --call-graph
 *
 * On RISC-V platक्रमm, the program being sampled and the C library
 * need to be compiled with -fno-omit-frame-poपूर्णांकer, otherwise
 * the user stack will not contain function frame.
 */
व्योम perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry,
			 काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ fp = 0;

	/* RISC-V करोes not support perf in guest mode. */
	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest())
		वापस;

	fp = regs->s0;
	perf_callchain_store(entry, regs->epc);

	fp = user_backtrace(entry, fp, regs->ra);
	जबतक (fp && !(fp & 0x3) && entry->nr < entry->max_stack)
		fp = user_backtrace(entry, fp, 0);
पूर्ण

अटल bool fill_callchain(व्योम *entry, अचिन्हित दीर्घ pc)
अणु
	वापस perf_callchain_store(entry, pc);
पूर्ण

व्योम perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry,
			   काष्ठा pt_regs *regs)
अणु
	/* RISC-V करोes not support perf in guest mode. */
	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		pr_warn("RISC-V does not support perf in guest mode!");
		वापस;
	पूर्ण

	walk_stackframe(शून्य, regs, fill_callchain, entry);
पूर्ण
