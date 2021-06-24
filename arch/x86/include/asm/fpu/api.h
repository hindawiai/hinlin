<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1994 Linus Torvalds
 *
 * Pentium III FXSR, SSE support
 * General FPU state handling cleanups
 *	Gareth Hughes <gareth@valinux.com>, May 2000
 * x86-64 work by Andi Kleen 2002
 */

#अगर_अघोषित _ASM_X86_FPU_API_H
#घोषणा _ASM_X86_FPU_API_H
#समावेश <linux/bottom_half.h>

/*
 * Use kernel_fpu_begin/end() अगर you पूर्णांकend to use FPU in kernel context. It
 * disables preemption so be careful अगर you पूर्णांकend to use it क्रम दीर्घ periods
 * of समय.
 * If you पूर्णांकend to use the FPU in irq/softirq you need to check first with
 * irq_fpu_usable() अगर it is possible.
 */

/* Kernel FPU states to initialize in kernel_fpu_begin_mask() */
#घोषणा KFPU_387	_BITUL(0)	/* 387 state will be initialized */
#घोषणा KFPU_MXCSR	_BITUL(1)	/* MXCSR will be initialized */

बाह्य व्योम kernel_fpu_begin_mask(अचिन्हित पूर्णांक kfpu_mask);
बाह्य व्योम kernel_fpu_end(व्योम);
बाह्य bool irq_fpu_usable(व्योम);
बाह्य व्योम fpregs_mark_activate(व्योम);

/* Code that is unaware of kernel_fpu_begin_mask() can use this */
अटल अंतरभूत व्योम kernel_fpu_begin(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	/*
	 * Any 64-bit code that uses 387 inकाष्ठाions must explicitly request
	 * KFPU_387.
	 */
	kernel_fpu_begin_mask(KFPU_MXCSR);
#अन्यथा
	/*
	 * 32-bit kernel code may use 387 operations as well as SSE2, etc,
	 * as दीर्घ as it checks that the CPU has the required capability.
	 */
	kernel_fpu_begin_mask(KFPU_387 | KFPU_MXCSR);
#पूर्ण_अगर
पूर्ण

/*
 * Use fpregs_lock() जबतक editing CPU's FPU रेजिस्टरs or fpu->state.
 * A context चयन will (and softirq might) save CPU's FPU रेजिस्टरs to
 * fpu->state and set TIF_NEED_FPU_LOAD leaving CPU's FPU रेजिस्टरs in
 * a अक्रमom state.
 *
 * local_bh_disable() protects against both preemption and soft पूर्णांकerrupts
 * on !RT kernels.
 *
 * On RT kernels local_bh_disable() is not sufficient because it only
 * serializes soft पूर्णांकerrupt related sections via a local lock, but stays
 * preemptible. Disabling preemption is the right choice here as bottom
 * half processing is always in thपढ़ो context on RT kernels so it
 * implicitly prevents bottom half processing as well.
 *
 * Disabling preemption also serializes against kernel_fpu_begin().
 */
अटल अंतरभूत व्योम fpregs_lock(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_PREEMPT_RT))
		local_bh_disable();
	अन्यथा
		preempt_disable();
पूर्ण

अटल अंतरभूत व्योम fpregs_unlock(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_PREEMPT_RT))
		local_bh_enable();
	अन्यथा
		preempt_enable();
पूर्ण

#अगर_घोषित CONFIG_X86_DEBUG_FPU
बाह्य व्योम fpregs_निश्चित_state_consistent(व्योम);
#अन्यथा
अटल अंतरभूत व्योम fpregs_निश्चित_state_consistent(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*
 * Load the task FPU state beक्रमe वापसing to userspace.
 */
बाह्य व्योम चयन_fpu_वापस(व्योम);

/*
 * Query the presence of one or more xfeatures. Works on any legacy CPU as well.
 *
 * If 'feature_name' is set then put a human-पढ़ोable description of
 * the feature there as well - this can be used to prपूर्णांक error (or success)
 * messages.
 */
बाह्य पूर्णांक cpu_has_xfeatures(u64 xfeatures_mask, स्थिर अक्षर **feature_name);

/*
 * Tasks that are not using SVA have mm->pasid set to zero to note that they
 * will not have the valid bit set in MSR_IA32_PASID जबतक they are running.
 */
#घोषणा PASID_DISABLED	0

अटल अंतरभूत व्योम update_pasid(व्योम) अणु पूर्ण

#पूर्ण_अगर /* _ASM_X86_FPU_API_H */
