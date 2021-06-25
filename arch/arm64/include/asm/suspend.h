<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SUSPEND_H
#घोषणा __ASM_SUSPEND_H

#घोषणा NR_CTX_REGS 13
#घोषणा NR_CALLEE_SAVED_REGS 12

/*
 * काष्ठा cpu_suspend_ctx must be 16-byte aligned since it is allocated on
 * the stack, which must be 16-byte aligned on v8
 */
काष्ठा cpu_suspend_ctx अणु
	/*
	 * This काष्ठा must be kept in sync with
	 * cpu_करो_अणुsuspend/resumeपूर्ण in mm/proc.S
	 */
	u64 ctx_regs[NR_CTX_REGS];
	u64 sp;
पूर्ण __aligned(16);

/*
 * Memory to save the cpu state is allocated on the stack by
 * __cpu_suspend_enter()'s caller, and populated by __cpu_suspend_enter().
 * This data must survive until cpu_resume() is called.
 *
 * This काष्ठा desribes the size and the layout of the saved cpu state.
 * The layout of the callee_saved_regs is defined by the implementation
 * of __cpu_suspend_enter(), and cpu_resume(). This काष्ठा must be passed
 * in by the caller as __cpu_suspend_enter()'s stack-frame is gone once it
 * वापसs, and the data would be subsequently corrupted by the call to the
 * finisher.
 */
काष्ठा sleep_stack_data अणु
	काष्ठा cpu_suspend_ctx	प्रणाली_regs;
	अचिन्हित दीर्घ		callee_saved_regs[NR_CALLEE_SAVED_REGS];
पूर्ण;

बाह्य अचिन्हित दीर्घ *sleep_save_stash;

बाह्य पूर्णांक cpu_suspend(अचिन्हित दीर्घ arg, पूर्णांक (*fn)(अचिन्हित दीर्घ));
बाह्य व्योम cpu_resume(व्योम);
पूर्णांक __cpu_suspend_enter(काष्ठा sleep_stack_data *state);
व्योम __cpu_suspend_निकास(व्योम);
व्योम _cpu_resume(व्योम);

पूर्णांक swsusp_arch_suspend(व्योम);
पूर्णांक swsusp_arch_resume(व्योम);
पूर्णांक arch_hibernation_header_save(व्योम *addr, अचिन्हित पूर्णांक max_size);
पूर्णांक arch_hibernation_header_restore(व्योम *addr);

/* Used to resume on the CPU we hibernated on */
पूर्णांक hibernate_resume_nonboot_cpu_disable(व्योम);

#पूर्ण_अगर
