<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1999 Cort Dougan <cort@cs.nmt.edu>
 */
#अगर_अघोषित _ASM_POWERPC_SWITCH_TO_H
#घोषणा _ASM_POWERPC_SWITCH_TO_H

#समावेश <linux/sched.h>
#समावेश <यंत्र/reg.h>

काष्ठा thपढ़ो_काष्ठा;
काष्ठा task_काष्ठा;
काष्ठा pt_regs;

बाह्य काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *,
	काष्ठा task_काष्ठा *);
#घोषणा चयन_to(prev, next, last)	((last) = __चयन_to((prev), (next)))

बाह्य काष्ठा task_काष्ठा *_चयन(काष्ठा thपढ़ो_काष्ठा *prev,
				   काष्ठा thपढ़ो_काष्ठा *next);

बाह्य व्योम चयन_booke_debug_regs(काष्ठा debug_reg *new_debug);

बाह्य पूर्णांक emulate_altivec(काष्ठा pt_regs *);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
व्योम restore_math(काष्ठा pt_regs *regs);
#अन्यथा
अटल अंतरभूत व्योम restore_math(काष्ठा pt_regs *regs)
अणु
पूर्ण
#पूर्ण_अगर

व्योम restore_पंचांग_state(काष्ठा pt_regs *regs);

बाह्य व्योम flush_all_to_thपढ़ो(काष्ठा task_काष्ठा *);
बाह्य व्योम giveup_all(काष्ठा task_काष्ठा *);

#अगर_घोषित CONFIG_PPC_FPU
बाह्य व्योम enable_kernel_fp(व्योम);
बाह्य व्योम flush_fp_to_thपढ़ो(काष्ठा task_काष्ठा *);
बाह्य व्योम giveup_fpu(काष्ठा task_काष्ठा *);
बाह्य व्योम save_fpu(काष्ठा task_काष्ठा *);
अटल अंतरभूत व्योम disable_kernel_fp(व्योम)
अणु
	msr_check_and_clear(MSR_FP);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम save_fpu(काष्ठा task_काष्ठा *t) अणु पूर्ण
अटल अंतरभूत व्योम flush_fp_to_thपढ़ो(काष्ठा task_काष्ठा *t) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ALTIVEC
बाह्य व्योम enable_kernel_altivec(व्योम);
बाह्य व्योम flush_altivec_to_thपढ़ो(काष्ठा task_काष्ठा *);
बाह्य व्योम giveup_altivec(काष्ठा task_काष्ठा *);
बाह्य व्योम save_altivec(काष्ठा task_काष्ठा *);
अटल अंतरभूत व्योम disable_kernel_altivec(व्योम)
अणु
	msr_check_and_clear(MSR_VEC);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम save_altivec(काष्ठा task_काष्ठा *t) अणु पूर्ण
अटल अंतरभूत व्योम __giveup_altivec(काष्ठा task_काष्ठा *t) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_VSX
बाह्य व्योम enable_kernel_vsx(व्योम);
बाह्य व्योम flush_vsx_to_thपढ़ो(काष्ठा task_काष्ठा *);
अटल अंतरभूत व्योम disable_kernel_vsx(व्योम)
अणु
	msr_check_and_clear(MSR_FP|MSR_VEC|MSR_VSX);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम enable_kernel_vsx(व्योम)
अणु
	BUILD_BUG();
पूर्ण

अटल अंतरभूत व्योम disable_kernel_vsx(व्योम)
अणु
	BUILD_BUG();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPE
बाह्य व्योम enable_kernel_spe(व्योम);
बाह्य व्योम flush_spe_to_thपढ़ो(काष्ठा task_काष्ठा *);
बाह्य व्योम giveup_spe(काष्ठा task_काष्ठा *);
बाह्य व्योम __giveup_spe(काष्ठा task_काष्ठा *);
अटल अंतरभूत व्योम disable_kernel_spe(व्योम)
अणु
	msr_check_and_clear(MSR_SPE);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __giveup_spe(काष्ठा task_काष्ठा *t) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम clear_task_ebb(काष्ठा task_काष्ठा *t)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
    /* EBB perf events are not inherited, so clear all EBB state. */
    t->thपढ़ो.ebbrr = 0;
    t->thपढ़ो.ebbhr = 0;
    t->thपढ़ो.bescr = 0;
    t->thपढ़ो.mmcr2 = 0;
    t->thपढ़ो.mmcr0 = 0;
    t->thपढ़ो.siar = 0;
    t->thपढ़ो.sdar = 0;
    t->thपढ़ो.sier = 0;
    t->thपढ़ो.used_ebb = 0;
#पूर्ण_अगर
पूर्ण

बाह्य पूर्णांक set_thपढ़ो_tidr(काष्ठा task_काष्ठा *t);

#पूर्ण_अगर /* _ASM_POWERPC_SWITCH_TO_H */
