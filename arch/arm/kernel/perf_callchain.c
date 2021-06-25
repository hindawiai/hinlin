<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ARM callchain support
 *
 * Copyright (C) 2009 picoChip Designs, Ltd., Jamie Iles
 * Copyright (C) 2010 ARM Ltd., Will Deacon <will.deacon@arm.com>
 *
 * This code is based on the ARM OProfile backtrace code.
 */
#समावेश <linux/perf_event.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/stacktrace.h>

/*
 * The रेजिस्टरs we're पूर्णांकerested in are at the end of the variable
 * length saved रेजिस्टर काष्ठाure. The fp poपूर्णांकs at the end of this
 * काष्ठाure so the address of this काष्ठा is:
 * (काष्ठा frame_tail *)(xxx->fp)-1
 *
 * This code has been adapted from the ARM OProfile support.
 */
काष्ठा frame_tail अणु
	काष्ठा frame_tail __user *fp;
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ lr;
पूर्ण __attribute__((packed));

/*
 * Get the वापस address क्रम a single stackframe and वापस a poपूर्णांकer to the
 * next frame tail.
 */
अटल काष्ठा frame_tail __user *
user_backtrace(काष्ठा frame_tail __user *tail,
	       काष्ठा perf_callchain_entry_ctx *entry)
अणु
	काष्ठा frame_tail buftail;
	अचिन्हित दीर्घ err;

	अगर (!access_ok(tail, माप(buftail)))
		वापस शून्य;

	pagefault_disable();
	err = __copy_from_user_inatomic(&buftail, tail, माप(buftail));
	pagefault_enable();

	अगर (err)
		वापस शून्य;

	perf_callchain_store(entry, buftail.lr);

	/*
	 * Frame poपूर्णांकers should strictly progress back up the stack
	 * (towards higher addresses).
	 */
	अगर (tail + 1 >= buftail.fp)
		वापस शून्य;

	वापस buftail.fp - 1;
पूर्ण

व्योम
perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry, काष्ठा pt_regs *regs)
अणु
	काष्ठा frame_tail __user *tail;

	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		/* We करोn't support guest os callchain now */
		वापस;
	पूर्ण

	perf_callchain_store(entry, regs->ARM_pc);

	अगर (!current->mm)
		वापस;

	tail = (काष्ठा frame_tail __user *)regs->ARM_fp - 1;

	जबतक ((entry->nr < entry->max_stack) &&
	       tail && !((अचिन्हित दीर्घ)tail & 0x3))
		tail = user_backtrace(tail, entry);
पूर्ण

/*
 * Gets called by walk_stackframe() क्रम every stackframe. This will be called
 * whist unwinding the stackframe and is like a subroutine वापस so we use
 * the PC.
 */
अटल पूर्णांक
callchain_trace(काष्ठा stackframe *fr,
		व्योम *data)
अणु
	काष्ठा perf_callchain_entry_ctx *entry = data;
	perf_callchain_store(entry, fr->pc);
	वापस 0;
पूर्ण

व्योम
perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry, काष्ठा pt_regs *regs)
अणु
	काष्ठा stackframe fr;

	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		/* We करोn't support guest os callchain now */
		वापस;
	पूर्ण

	arm_get_current_stackframe(regs, &fr);
	walk_stackframe(&fr, callchain_trace, entry);
पूर्ण

अचिन्हित दीर्घ perf_inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest())
		वापस perf_guest_cbs->get_guest_ip();

	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

अचिन्हित दीर्घ perf_misc_flags(काष्ठा pt_regs *regs)
अणु
	पूर्णांक misc = 0;

	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		अगर (perf_guest_cbs->is_user_mode())
			misc |= PERF_RECORD_MISC_GUEST_USER;
		अन्यथा
			misc |= PERF_RECORD_MISC_GUEST_KERNEL;
	पूर्ण अन्यथा अणु
		अगर (user_mode(regs))
			misc |= PERF_RECORD_MISC_USER;
		अन्यथा
			misc |= PERF_RECORD_MISC_KERNEL;
	पूर्ण

	वापस misc;
पूर्ण
