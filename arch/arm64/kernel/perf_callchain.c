<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arm64 callchain support
 *
 * Copyright (C) 2015 ARM Limited
 */
#समावेश <linux/perf_event.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/poपूर्णांकer_auth.h>
#समावेश <यंत्र/stacktrace.h>

काष्ठा frame_tail अणु
	काष्ठा frame_tail	__user *fp;
	अचिन्हित दीर्घ		lr;
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
	अचिन्हित दीर्घ lr;

	/* Also check accessibility of one काष्ठा frame_tail beyond */
	अगर (!access_ok(tail, माप(buftail)))
		वापस शून्य;

	pagefault_disable();
	err = __copy_from_user_inatomic(&buftail, tail, माप(buftail));
	pagefault_enable();

	अगर (err)
		वापस शून्य;

	lr = ptrauth_strip_insn_pac(buftail.lr);

	perf_callchain_store(entry, lr);

	/*
	 * Frame poपूर्णांकers should strictly progress back up the stack
	 * (towards higher addresses).
	 */
	अगर (tail >= buftail.fp)
		वापस शून्य;

	वापस buftail.fp;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/*
 * The रेजिस्टरs we're पूर्णांकerested in are at the end of the variable
 * length saved रेजिस्टर काष्ठाure. The fp poपूर्णांकs at the end of this
 * काष्ठाure so the address of this काष्ठा is:
 * (काष्ठा compat_frame_tail *)(xxx->fp)-1
 *
 * This code has been adapted from the ARM OProfile support.
 */
काष्ठा compat_frame_tail अणु
	compat_uptr_t	fp; /* a (काष्ठा compat_frame_tail *) in compat mode */
	u32		sp;
	u32		lr;
पूर्ण __attribute__((packed));

अटल काष्ठा compat_frame_tail __user *
compat_user_backtrace(काष्ठा compat_frame_tail __user *tail,
		      काष्ठा perf_callchain_entry_ctx *entry)
अणु
	काष्ठा compat_frame_tail buftail;
	अचिन्हित दीर्घ err;

	/* Also check accessibility of one काष्ठा frame_tail beyond */
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
	अगर (tail + 1 >= (काष्ठा compat_frame_tail __user *)
			compat_ptr(buftail.fp))
		वापस शून्य;

	वापस (काष्ठा compat_frame_tail __user *)compat_ptr(buftail.fp) - 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

व्योम perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry,
			 काष्ठा pt_regs *regs)
अणु
	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		/* We करोn't support guest os callchain now */
		वापस;
	पूर्ण

	perf_callchain_store(entry, regs->pc);

	अगर (!compat_user_mode(regs)) अणु
		/* AARCH64 mode */
		काष्ठा frame_tail __user *tail;

		tail = (काष्ठा frame_tail __user *)regs->regs[29];

		जबतक (entry->nr < entry->max_stack &&
		       tail && !((अचिन्हित दीर्घ)tail & 0xf))
			tail = user_backtrace(tail, entry);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_COMPAT
		/* AARCH32 compat mode */
		काष्ठा compat_frame_tail __user *tail;

		tail = (काष्ठा compat_frame_tail __user *)regs->compat_fp - 1;

		जबतक ((entry->nr < entry->max_stack) &&
			tail && !((अचिन्हित दीर्घ)tail & 0x3))
			tail = compat_user_backtrace(tail, entry);
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * Gets called by walk_stackframe() क्रम every stackframe. This will be called
 * whist unwinding the stackframe and is like a subroutine वापस so we use
 * the PC.
 */
अटल bool callchain_trace(व्योम *data, अचिन्हित दीर्घ pc)
अणु
	काष्ठा perf_callchain_entry_ctx *entry = data;
	perf_callchain_store(entry, pc);
	वापस true;
पूर्ण

व्योम perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry,
			   काष्ठा pt_regs *regs)
अणु
	काष्ठा stackframe frame;

	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		/* We करोn't support guest os callchain now */
		वापस;
	पूर्ण

	start_backtrace(&frame, regs->regs[29], regs->pc);
	walk_stackframe(current, &frame, callchain_trace, entry);
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
