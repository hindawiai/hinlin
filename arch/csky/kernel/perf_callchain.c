<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2019 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/perf_event.h>
#समावेश <linux/uaccess.h>

/* Kernel callchain */
काष्ठा stackframe अणु
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ lr;
पूर्ण;

अटल पूर्णांक unwind_frame_kernel(काष्ठा stackframe *frame)
अणु
	अचिन्हित दीर्घ low = (अचिन्हित दीर्घ)task_stack_page(current);
	अचिन्हित दीर्घ high = low + THREAD_SIZE;

	अगर (unlikely(frame->fp < low || frame->fp > high))
		वापस -EPERM;

	अगर (kstack_end((व्योम *)frame->fp) || frame->fp & 0x3)
		वापस -EPERM;

	*frame = *(काष्ठा stackframe *)frame->fp;

	अगर (__kernel_text_address(frame->lr)) अणु
		पूर्णांक graph = 0;

		frame->lr = ftrace_graph_ret_addr(शून्य, &graph, frame->lr,
				शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम notrace walk_stackframe(काष्ठा stackframe *fr,
			काष्ठा perf_callchain_entry_ctx *entry)
अणु
	करो अणु
		perf_callchain_store(entry, fr->lr);
	पूर्ण जबतक (unwind_frame_kernel(fr) >= 0);
पूर्ण

/*
 * Get the वापस address क्रम a single stackframe and वापस a poपूर्णांकer to the
 * next frame tail.
 */
अटल अचिन्हित दीर्घ user_backtrace(काष्ठा perf_callchain_entry_ctx *entry,
			अचिन्हित दीर्घ fp, अचिन्हित दीर्घ reg_lr)
अणु
	काष्ठा stackframe buftail;
	अचिन्हित दीर्घ lr = 0;
	अचिन्हित दीर्घ *user_frame_tail = (अचिन्हित दीर्घ *)fp;

	/* Check accessibility of one काष्ठा frame_tail beyond */
	अगर (!access_ok(user_frame_tail, माप(buftail)))
		वापस 0;
	अगर (__copy_from_user_inatomic(&buftail, user_frame_tail,
				      माप(buftail)))
		वापस 0;

	अगर (reg_lr != 0)
		lr = reg_lr;
	अन्यथा
		lr = buftail.lr;

	fp = buftail.fp;
	perf_callchain_store(entry, lr);

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
 * On C-SKY platक्रमm, the program being sampled and the C library
 * need to be compiled with * -mbacktrace, otherwise the user
 * stack will not contain function frame.
 */
व्योम perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry,
			 काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ fp = 0;

	/* C-SKY करोes not support भवization. */
	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest())
		वापस;

	fp = regs->regs[4];
	perf_callchain_store(entry, regs->pc);

	/*
	 * While backtrace from leaf function, lr is normally
	 * not saved inside frame on C-SKY, so get lr from pt_regs
	 * at the sample poपूर्णांक. However, lr value can be incorrect अगर
	 * lr is used as temp रेजिस्टर
	 */
	fp = user_backtrace(entry, fp, regs->lr);

	जबतक (fp && !(fp & 0x3) && entry->nr < entry->max_stack)
		fp = user_backtrace(entry, fp, 0);
पूर्ण

व्योम perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry,
			   काष्ठा pt_regs *regs)
अणु
	काष्ठा stackframe fr;

	/* C-SKY करोes not support भवization. */
	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		pr_warn("C-SKY does not support perf in guest mode!");
		वापस;
	पूर्ण

	fr.fp = regs->regs[4];
	fr.lr = regs->lr;
	walk_stackframe(&fr, entry);
पूर्ण
