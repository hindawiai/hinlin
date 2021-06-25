<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/compiler.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/nospec.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/अक्रमomize_kstack.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/unistd.h>

दीर्घ compat_arm_syscall(काष्ठा pt_regs *regs, पूर्णांक scno);
दीर्घ sys_ni_syscall(व्योम);

अटल दीर्घ करो_ni_syscall(काष्ठा pt_regs *regs, पूर्णांक scno)
अणु
#अगर_घोषित CONFIG_COMPAT
	दीर्घ ret;
	अगर (is_compat_task()) अणु
		ret = compat_arm_syscall(regs, scno);
		अगर (ret != -ENOSYS)
			वापस ret;
	पूर्ण
#पूर्ण_अगर

	वापस sys_ni_syscall();
पूर्ण

अटल दीर्घ __invoke_syscall(काष्ठा pt_regs *regs, syscall_fn_t syscall_fn)
अणु
	वापस syscall_fn(regs);
पूर्ण

अटल व्योम invoke_syscall(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक scno,
			   अचिन्हित पूर्णांक sc_nr,
			   स्थिर syscall_fn_t syscall_table[])
अणु
	दीर्घ ret;

	add_अक्रमom_kstack_offset();

	अगर (scno < sc_nr) अणु
		syscall_fn_t syscall_fn;
		syscall_fn = syscall_table[array_index_nospec(scno, sc_nr)];
		ret = __invoke_syscall(regs, syscall_fn);
	पूर्ण अन्यथा अणु
		ret = करो_ni_syscall(regs, scno);
	पूर्ण

	अगर (is_compat_task())
		ret = lower_32_bits(ret);

	regs->regs[0] = ret;

	/*
	 * Ultimately, this value will get limited by KSTACK_OFFSET_MAX(),
	 * but not enough क्रम arm64 stack utilization comक्रमt. To keep
	 * reasonable stack head room, reduce the maximum offset to 9 bits.
	 *
	 * The actual entropy will be further reduced by the compiler when
	 * applying stack alignment स्थिरraपूर्णांकs: the AAPCS mandates a
	 * 16-byte (i.e. 4-bit) aligned SP at function boundaries.
	 *
	 * The resulting 5 bits of entropy is seen in SP[8:4].
	 */
	choose_अक्रमom_kstack_offset(get_अक्रमom_पूर्णांक() & 0x1FF);
पूर्ण

अटल अंतरभूत bool has_syscall_work(अचिन्हित दीर्घ flags)
अणु
	वापस unlikely(flags & _TIF_SYSCALL_WORK);
पूर्ण

पूर्णांक syscall_trace_enter(काष्ठा pt_regs *regs);
व्योम syscall_trace_निकास(काष्ठा pt_regs *regs);

अटल व्योम el0_svc_common(काष्ठा pt_regs *regs, पूर्णांक scno, पूर्णांक sc_nr,
			   स्थिर syscall_fn_t syscall_table[])
अणु
	अचिन्हित दीर्घ flags = current_thपढ़ो_info()->flags;

	regs->orig_x0 = regs->regs[0];
	regs->syscallno = scno;

	/*
	 * BTI note:
	 * The architecture करोes not guarantee that SPSR.BTYPE is zero
	 * on taking an SVC, so we could वापस to userspace with a
	 * non-zero BTYPE after the syscall.
	 *
	 * This shouldn't matter except when userspace is explicitly
	 * करोing something stupid, such as setting PROT_BTI on a page
	 * that lacks conक्रमming BTI/PACIxSP inकाष्ठाions, falling
	 * through from one executable page to another with dअगरfering
	 * PROT_BTI, or messing with BTYPE via ptrace: in such हालs,
	 * userspace should not be surprised अगर a संक_अवैध occurs on
	 * syscall वापस.
	 *
	 * So, करोn't touch regs->pstate & PSR_BTYPE_MASK here.
	 * (Similarly क्रम HVC and SMC अन्यथाwhere.)
	 */

	local_daअगर_restore(DAIF_PROCCTX);

	अगर (flags & _TIF_MTE_ASYNC_FAULT) अणु
		/*
		 * Process the asynchronous tag check fault beक्रमe the actual
		 * syscall. करो_notअगरy_resume() will send a संकेत to userspace
		 * beक्रमe the syscall is restarted.
		 */
		regs->regs[0] = -ERESTARTNOINTR;
		वापस;
	पूर्ण

	अगर (has_syscall_work(flags)) अणु
		/*
		 * The de-facto standard way to skip a प्रणाली call using ptrace
		 * is to set the प्रणाली call to -1 (NO_SYSCALL) and set x0 to a
		 * suitable error code क्रम consumption by userspace. However,
		 * this cannot be distinguished from a user-issued syscall(-1)
		 * and so we must set x0 to -ENOSYS here in हाल the tracer करोesn't
		 * issue the skip and we fall पूर्णांकo trace_निकास with x0 preserved.
		 *
		 * This is slightly odd because it also means that अगर a tracer
		 * sets the प्रणाली call number to -1 but करोes not initialise x0,
		 * then x0 will be preserved क्रम all प्रणाली calls apart from a
		 * user-issued syscall(-1). However, requesting a skip and not
		 * setting the वापस value is unlikely to करो anything sensible
		 * anyway.
		 */
		अगर (scno == NO_SYSCALL)
			regs->regs[0] = -ENOSYS;
		scno = syscall_trace_enter(regs);
		अगर (scno == NO_SYSCALL)
			जाओ trace_निकास;
	पूर्ण

	invoke_syscall(regs, scno, sc_nr, syscall_table);

	/*
	 * The tracing status may have changed under our feet, so we have to
	 * check again. However, अगर we were tracing entry, then we always trace
	 * निकास regardless, as the old entry assembly did.
	 */
	अगर (!has_syscall_work(flags) && !IS_ENABLED(CONFIG_DEBUG_RSEQ)) अणु
		local_daअगर_mask();
		flags = current_thपढ़ो_info()->flags;
		अगर (!has_syscall_work(flags) && !(flags & _TIF_SINGLESTEP))
			वापस;
		local_daअगर_restore(DAIF_PROCCTX);
	पूर्ण

trace_निकास:
	syscall_trace_निकास(regs);
पूर्ण

अटल अंतरभूत व्योम sve_user_discard(व्योम)
अणु
	अगर (!प्रणाली_supports_sve())
		वापस;

	clear_thपढ़ो_flag(TIF_SVE);

	/*
	 * task_fpsimd_load() won't be called to update CPACR_EL1 in
	 * ret_to_user unless TIF_FOREIGN_FPSTATE is still set, which only
	 * happens अगर a context चयन or kernel_neon_begin() or context
	 * modअगरication (sigवापस, ptrace) पूर्णांकervenes.
	 * So, ensure that CPACR_EL1 is alपढ़ोy correct क्रम the fast-path हाल.
	 */
	sve_user_disable();
पूर्ण

व्योम करो_el0_svc(काष्ठा pt_regs *regs)
अणु
	sve_user_discard();
	el0_svc_common(regs, regs->regs[8], __NR_syscalls, sys_call_table);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
व्योम करो_el0_svc_compat(काष्ठा pt_regs *regs)
अणु
	el0_svc_common(regs, regs->regs[7], __NR_compat_syscalls,
		       compat_sys_call_table);
पूर्ण
#पूर्ण_अगर
