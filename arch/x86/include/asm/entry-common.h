<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _ASM_X86_ENTRY_COMMON_H
#घोषणा _ASM_X86_ENTRY_COMMON_H

#समावेश <linux/अक्रमomize_kstack.h>
#समावेश <linux/user-वापस-notअगरier.h>

#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/io_biपंचांगap.h>
#समावेश <यंत्र/fpu/api.h>

/* Check that the stack and regs on entry from user mode are sane. */
अटल __always_अंतरभूत व्योम arch_check_user_regs(काष्ठा pt_regs *regs)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_ENTRY)) अणु
		/*
		 * Make sure that the entry code gave us a sensible EFLAGS
		 * रेजिस्टर.  Native because we want to check the actual CPU
		 * state, not the पूर्णांकerrupt state as imagined by Xen.
		 */
		अचिन्हित दीर्घ flags = native_save_fl();
		अचिन्हित दीर्घ mask = X86_EFLAGS_DF | X86_EFLAGS_NT;

		/*
		 * For !SMAP hardware we patch out CLAC on entry.
		 */
		अगर (boot_cpu_has(X86_FEATURE_SMAP) ||
		    (IS_ENABLED(CONFIG_64_BIT) && boot_cpu_has(X86_FEATURE_XENPV)))
			mask |= X86_EFLAGS_AC;

		WARN_ON_ONCE(flags & mask);

		/* We think we came from user mode. Make sure pt_regs agrees. */
		WARN_ON_ONCE(!user_mode(regs));

		/*
		 * All entries from user mode (except #DF) should be on the
		 * normal thपढ़ो stack and should have user pt_regs in the
		 * correct location.
		 */
		WARN_ON_ONCE(!on_thपढ़ो_stack());
		WARN_ON_ONCE(regs != task_pt_regs(current));
	पूर्ण
पूर्ण
#घोषणा arch_check_user_regs arch_check_user_regs

अटल अंतरभूत व्योम arch_निकास_to_user_mode_prepare(काष्ठा pt_regs *regs,
						  अचिन्हित दीर्घ ti_work)
अणु
	अगर (ti_work & _TIF_USER_RETURN_NOTIFY)
		fire_user_वापस_notअगरiers();

	अगर (unlikely(ti_work & _TIF_IO_BITMAP))
		tss_update_io_biपंचांगap();

	fpregs_निश्चित_state_consistent();
	अगर (unlikely(ti_work & _TIF_NEED_FPU_LOAD))
		चयन_fpu_वापस();

#अगर_घोषित CONFIG_COMPAT
	/*
	 * Compat syscalls set TS_COMPAT.  Make sure we clear it beक्रमe
	 * वापसing to user mode.  We need to clear it *after* संकेत
	 * handling, because syscall restart has a fixup क्रम compat
	 * syscalls.  The fixup is exercised by the ptrace_syscall_32
	 * selftest.
	 *
	 * We also need to clear TS_REGS_POKED_I386: the 32-bit tracer
	 * special हाल only applies after poking regs and beक्रमe the
	 * very next वापस to user mode.
	 */
	current_thपढ़ो_info()->status &= ~(TS_COMPAT | TS_I386_REGS_POKED);
#पूर्ण_अगर

	/*
	 * Ultimately, this value will get limited by KSTACK_OFFSET_MAX(),
	 * but not enough क्रम x86 stack utilization comक्रमt. To keep
	 * reasonable stack head room, reduce the maximum offset to 8 bits.
	 *
	 * The actual entropy will be further reduced by the compiler when
	 * applying stack alignment स्थिरraपूर्णांकs (see cc_stack_align4/8 in
	 * arch/x86/Makefile), which will हटाओ the 3 (x86_64) or 2 (ia32)
	 * low bits from any entropy chosen here.
	 *
	 * Thereक्रमe, final stack offset entropy will be 5 (x86_64) or
	 * 6 (ia32) bits.
	 */
	choose_अक्रमom_kstack_offset(rdtsc() & 0xFF);
पूर्ण
#घोषणा arch_निकास_to_user_mode_prepare arch_निकास_to_user_mode_prepare

अटल __always_अंतरभूत व्योम arch_निकास_to_user_mode(व्योम)
अणु
	mds_user_clear_cpu_buffers();
पूर्ण
#घोषणा arch_निकास_to_user_mode arch_निकास_to_user_mode

#पूर्ण_अगर
