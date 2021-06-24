<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2005-2018 Andes Technology Corporation */

#अगर_अघोषित __ASM_NDS32_FPU_H
#घोषणा __ASM_NDS32_FPU_H

#अगर IS_ENABLED(CONFIG_FPU)
#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/preempt.h>
#समावेश <यंत्र/ptrace.h>

बाह्य bool has_fpu;

बाह्य व्योम save_fpu(काष्ठा task_काष्ठा *__tsk);
बाह्य व्योम load_fpu(स्थिर काष्ठा fpu_काष्ठा *fpregs);
बाह्य bool करो_fpu_exception(अचिन्हित पूर्णांक subtype, काष्ठा pt_regs *regs);
बाह्य पूर्णांक करो_fpuemu(काष्ठा pt_regs *regs, काष्ठा fpu_काष्ठा *fpu);

#घोषणा test_tsk_fpu(regs)	(regs->fucop_ctl & FUCOP_CTL_mskCP0EN)

/*
 * Initially load the FPU with संकेतling न_अंकS.  This bit pattern
 * has the property that no matter whether considered as single or as
 * द्विगुन precision, it still represents a संकेतling न_अंक.
 */

#घोषणा sन_अंक64    0xFFFFFFFFFFFFFFFFULL
#घोषणा sन_अंक32    0xFFFFFFFFUL

#अगर IS_ENABLED(CONFIG_SUPPORT_DENORMAL_ARITHMETIC)
/*
 * Denormalized number is unsupported by nds32 FPU. Hence the operation
 * is treated as underflow हालs when the final result is a denormalized
 * number. To enhance precision, underflow exception trap should be
 * enabled by शेष and kerenl will re-execute it by fpu emulator
 * when getting underflow exception.
 */
#घोषणा FPCSR_INIT  (FPCSR_mskUDFE | FPCSR_mskIEXE)
#अन्यथा
#घोषणा FPCSR_INIT  0x0UL
#पूर्ण_अगर

बाह्य स्थिर काष्ठा fpu_काष्ठा init_fpuregs;

अटल अंतरभूत व्योम disable_ptreg_fpu(काष्ठा pt_regs *regs)
अणु
	regs->fucop_ctl &= ~FUCOP_CTL_mskCP0EN;
पूर्ण

अटल अंतरभूत व्योम enable_ptreg_fpu(काष्ठा pt_regs *regs)
अणु
	regs->fucop_ctl |= FUCOP_CTL_mskCP0EN;
पूर्ण

अटल अंतरभूत व्योम enable_fpu(व्योम)
अणु
	अचिन्हित दीर्घ fucop_ctl;

	fucop_ctl = __nds32__mfsr(NDS32_SR_FUCOP_CTL) | FUCOP_CTL_mskCP0EN;
	__nds32__mtsr(fucop_ctl, NDS32_SR_FUCOP_CTL);
	__nds32__isb();
पूर्ण

अटल अंतरभूत व्योम disable_fpu(व्योम)
अणु
	अचिन्हित दीर्घ fucop_ctl;

	fucop_ctl = __nds32__mfsr(NDS32_SR_FUCOP_CTL) & ~FUCOP_CTL_mskCP0EN;
	__nds32__mtsr(fucop_ctl, NDS32_SR_FUCOP_CTL);
	__nds32__isb();
पूर्ण

अटल अंतरभूत व्योम lose_fpu(व्योम)
अणु
	preempt_disable();
#अगर IS_ENABLED(CONFIG_LAZY_FPU)
	अगर (last_task_used_math == current) अणु
		last_task_used_math = शून्य;
#अन्यथा
	अगर (test_tsk_fpu(task_pt_regs(current))) अणु
#पूर्ण_अगर
		save_fpu(current);
	पूर्ण
	disable_ptreg_fpu(task_pt_regs(current));
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम own_fpu(व्योम)
अणु
	preempt_disable();
#अगर IS_ENABLED(CONFIG_LAZY_FPU)
	अगर (last_task_used_math != current) अणु
		अगर (last_task_used_math != शून्य)
			save_fpu(last_task_used_math);
		load_fpu(&current->thपढ़ो.fpu);
		last_task_used_math = current;
	पूर्ण
#अन्यथा
	अगर (!test_tsk_fpu(task_pt_regs(current))) अणु
		load_fpu(&current->thपढ़ो.fpu);
	पूर्ण
#पूर्ण_अगर
	enable_ptreg_fpu(task_pt_regs(current));
	preempt_enable();
पूर्ण

#अगर !IS_ENABLED(CONFIG_LAZY_FPU)
अटल अंतरभूत व्योम unlazy_fpu(काष्ठा task_काष्ठा *tsk)
अणु
	preempt_disable();
	अगर (test_tsk_fpu(task_pt_regs(tsk)))
		save_fpu(tsk);
	preempt_enable();
पूर्ण
#पूर्ण_अगर /* !CONFIG_LAZY_FPU */
अटल अंतरभूत व्योम clear_fpu(काष्ठा pt_regs *regs)
अणु
	preempt_disable();
	अगर (test_tsk_fpu(regs))
		disable_ptreg_fpu(regs);
	preempt_enable();
पूर्ण
#पूर्ण_अगर /* CONFIG_FPU */
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_NDS32_FPU_H */
