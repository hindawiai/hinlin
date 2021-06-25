<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2018 Andes Technology Corporation

#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/user.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/bitfield.h>
#समावेश <यंत्र/fpu.h>

स्थिर काष्ठा fpu_काष्ठा init_fpuregs = अणु
	.fd_regs = अणु[0 ... 31] = sन_अंक64पूर्ण,
	.fpcsr = FPCSR_INIT,
#अगर IS_ENABLED(CONFIG_SUPPORT_DENORMAL_ARITHMETIC)
	.UDF_IEX_trap = 0
#पूर्ण_अगर
पूर्ण;

व्योम save_fpu(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित पूर्णांक fpcfg, fpcsr;

	enable_fpu();
	fpcfg = ((__nds32__fmfcfg() & FPCFG_mskFREG) >> FPCFG_offFREG);
	चयन (fpcfg) अणु
	हाल SP32_DP32_reg:
		यंत्र अस्थिर ("fsdi $fd31, [%0+0xf8]\n\t"
			      "fsdi $fd30, [%0+0xf0]\n\t"
			      "fsdi $fd29, [%0+0xe8]\n\t"
			      "fsdi $fd28, [%0+0xe0]\n\t"
			      "fsdi $fd27, [%0+0xd8]\n\t"
			      "fsdi $fd26, [%0+0xd0]\n\t"
			      "fsdi $fd25, [%0+0xc8]\n\t"
			      "fsdi $fd24, [%0+0xc0]\n\t"
			      "fsdi $fd23, [%0+0xb8]\n\t"
			      "fsdi $fd22, [%0+0xb0]\n\t"
			      "fsdi $fd21, [%0+0xa8]\n\t"
			      "fsdi $fd20, [%0+0xa0]\n\t"
			      "fsdi $fd19, [%0+0x98]\n\t"
			      "fsdi $fd18, [%0+0x90]\n\t"
			      "fsdi $fd17, [%0+0x88]\n\t"
			      "fsdi $fd16, [%0+0x80]\n\t"
			      :	/* no output */
			      : "r" (&tsk->thपढ़ो.fpu)
			      : "memory");
		fallthrough;
	हाल SP32_DP16_reg:
		यंत्र अस्थिर ("fsdi $fd15, [%0+0x78]\n\t"
			      "fsdi $fd14, [%0+0x70]\n\t"
			      "fsdi $fd13, [%0+0x68]\n\t"
			      "fsdi $fd12, [%0+0x60]\n\t"
			      "fsdi $fd11, [%0+0x58]\n\t"
			      "fsdi $fd10, [%0+0x50]\n\t"
			      "fsdi $fd9,  [%0+0x48]\n\t"
			      "fsdi $fd8,  [%0+0x40]\n\t"
			      :	/* no output */
			      : "r" (&tsk->thपढ़ो.fpu)
			      : "memory");
		fallthrough;
	हाल SP16_DP8_reg:
		यंत्र अस्थिर ("fsdi $fd7,  [%0+0x38]\n\t"
			      "fsdi $fd6,  [%0+0x30]\n\t"
			      "fsdi $fd5,  [%0+0x28]\n\t"
			      "fsdi $fd4,  [%0+0x20]\n\t"
			      :	/* no output */
			      : "r" (&tsk->thपढ़ो.fpu)
			      : "memory");
		fallthrough;
	हाल SP8_DP4_reg:
		यंत्र अस्थिर ("fsdi $fd3,  [%1+0x18]\n\t"
			      "fsdi $fd2,  [%1+0x10]\n\t"
			      "fsdi $fd1,  [%1+0x8]\n\t"
			      "fsdi $fd0,  [%1+0x0]\n\t"
			      "fmfcsr	%0\n\t"
			      "swi  %0, [%1+0x100]\n\t"
			      : "=&r" (fpcsr)
			      : "r"(&tsk->thपढ़ो.fpu)
			      : "memory");
	पूर्ण
	disable_fpu();
पूर्ण

व्योम load_fpu(स्थिर काष्ठा fpu_काष्ठा *fpregs)
अणु
	अचिन्हित पूर्णांक fpcfg, fpcsr;

	enable_fpu();
	fpcfg = ((__nds32__fmfcfg() & FPCFG_mskFREG) >> FPCFG_offFREG);
	चयन (fpcfg) अणु
	हाल SP32_DP32_reg:
		यंत्र अस्थिर ("fldi $fd31, [%0+0xf8]\n\t"
			      "fldi $fd30, [%0+0xf0]\n\t"
			      "fldi $fd29, [%0+0xe8]\n\t"
			      "fldi $fd28, [%0+0xe0]\n\t"
			      "fldi $fd27, [%0+0xd8]\n\t"
			      "fldi $fd26, [%0+0xd0]\n\t"
			      "fldi $fd25, [%0+0xc8]\n\t"
			      "fldi $fd24, [%0+0xc0]\n\t"
			      "fldi $fd23, [%0+0xb8]\n\t"
			      "fldi $fd22, [%0+0xb0]\n\t"
			      "fldi $fd21, [%0+0xa8]\n\t"
			      "fldi $fd20, [%0+0xa0]\n\t"
			      "fldi $fd19, [%0+0x98]\n\t"
			      "fldi $fd18, [%0+0x90]\n\t"
			      "fldi $fd17, [%0+0x88]\n\t"
			      "fldi $fd16, [%0+0x80]\n\t"
			      :	/* no output */
			      : "r" (fpregs));
		fallthrough;
	हाल SP32_DP16_reg:
		यंत्र अस्थिर ("fldi $fd15, [%0+0x78]\n\t"
			      "fldi $fd14, [%0+0x70]\n\t"
			      "fldi $fd13, [%0+0x68]\n\t"
			      "fldi $fd12, [%0+0x60]\n\t"
			      "fldi $fd11, [%0+0x58]\n\t"
			      "fldi $fd10, [%0+0x50]\n\t"
			      "fldi $fd9,  [%0+0x48]\n\t"
			      "fldi $fd8,  [%0+0x40]\n\t"
			      :	/* no output */
			      : "r" (fpregs));
		fallthrough;
	हाल SP16_DP8_reg:
		यंत्र अस्थिर ("fldi $fd7,  [%0+0x38]\n\t"
			      "fldi $fd6,  [%0+0x30]\n\t"
			      "fldi $fd5,  [%0+0x28]\n\t"
			      "fldi $fd4,  [%0+0x20]\n\t"
			      :	/* no output */
			      : "r" (fpregs));
		fallthrough;
	हाल SP8_DP4_reg:
		यंत्र अस्थिर ("fldi $fd3,  [%1+0x18]\n\t"
			      "fldi $fd2,  [%1+0x10]\n\t"
			      "fldi $fd1,  [%1+0x8]\n\t"
			      "fldi $fd0,  [%1+0x0]\n\t"
			      "lwi  %0, [%1+0x100]\n\t"
			      "fmtcsr	%0\n\t":"=&r" (fpcsr)
			      : "r"(fpregs));
	पूर्ण
	disable_fpu();
पूर्ण
व्योम store_fpu_क्रम_suspend(व्योम)
अणु
#अगर_घोषित CONFIG_LAZY_FPU
	अगर (last_task_used_math != शून्य)
		save_fpu(last_task_used_math);
	last_task_used_math = शून्य;
#अन्यथा
	अगर (!used_math())
		वापस;
	unlazy_fpu(current);
#पूर्ण_अगर
	clear_fpu(task_pt_regs(current));
पूर्ण
अंतरभूत व्योम करो_fpu_context_चयन(काष्ठा pt_regs *regs)
अणु
	/* Enable to use FPU. */

	अगर (!user_mode(regs)) अणु
		pr_err("BUG: FPU is used in kernel mode.\n");
		BUG();
		वापस;
	पूर्ण

	enable_ptreg_fpu(regs);
#अगर_घोषित CONFIG_LAZY_FPU	//Lazy FPU is used
	अगर (last_task_used_math == current)
		वापस;
	अगर (last_task_used_math != शून्य)
		/* Other processes fpu state, save away */
		save_fpu(last_task_used_math);
	last_task_used_math = current;
#पूर्ण_अगर
	अगर (used_math()) अणु
		load_fpu(&current->thपढ़ो.fpu);
	पूर्ण अन्यथा अणु
		/* First समय FPU user.  */
		load_fpu(&init_fpuregs);
#अगर IS_ENABLED(CONFIG_SUPPORT_DENORMAL_ARITHMETIC)
		current->thपढ़ो.fpu.UDF_IEX_trap = init_fpuregs.UDF_IEX_trap;
#पूर्ण_अगर
		set_used_math();
	पूर्ण

पूर्ण

अंतरभूत व्योम fill_sigfpe_signo(अचिन्हित पूर्णांक fpcsr, पूर्णांक *signo)
अणु
	अगर (fpcsr & FPCSR_mskOVFT)
		*signo = FPE_FLTOVF;
#अगर_अघोषित CONFIG_SUPPORT_DENORMAL_ARITHMETIC
	अन्यथा अगर (fpcsr & FPCSR_mskUDFT)
		*signo = FPE_FLTUND;
#पूर्ण_अगर
	अन्यथा अगर (fpcsr & FPCSR_mskIVOT)
		*signo = FPE_FLTINV;
	अन्यथा अगर (fpcsr & FPCSR_mskDBZT)
		*signo = FPE_FLTDIV;
	अन्यथा अगर (fpcsr & FPCSR_mskIEXT)
		*signo = FPE_FLTRES;
पूर्ण

अंतरभूत व्योम handle_fpu_exception(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक fpcsr;
	पूर्णांक si_code = 0, si_signo = संक_भ_त्रुटि;
#अगर IS_ENABLED(CONFIG_SUPPORT_DENORMAL_ARITHMETIC)
	अचिन्हित दीर्घ reकरो_except = FPCSR_mskDNIT|FPCSR_mskUDFT|FPCSR_mskIEXT;
#अन्यथा
	अचिन्हित दीर्घ reकरो_except = FPCSR_mskDNIT;
#पूर्ण_अगर

	lose_fpu();
	fpcsr = current->thपढ़ो.fpu.fpcsr;

	अगर (fpcsr & reकरो_except) अणु
		si_signo = करो_fpuemu(regs, &current->thपढ़ो.fpu);
		fpcsr = current->thपढ़ो.fpu.fpcsr;
		अगर (!si_signo) अणु
			current->thपढ़ो.fpu.fpcsr &= ~(reकरो_except);
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अगर (fpcsr & FPCSR_mskRIT) अणु
		अगर (!user_mode(regs))
			करो_निकास(संक_अवैध);
		si_signo = संक_अवैध;
	पूर्ण

	चयन (si_signo) अणु
	हाल संक_भ_त्रुटि:
		fill_sigfpe_signo(fpcsr, &si_code);
		अवरोध;
	हाल संक_अवैध:
		show_regs(regs);
		si_code = ILL_COPROC;
		अवरोध;
	हाल SIGBUS:
		si_code = BUS_ADRERR;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	क्रमce_sig_fault(si_signo, si_code,
			(व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs));
करोne:
	own_fpu();
पूर्ण

bool करो_fpu_exception(अचिन्हित पूर्णांक subtype, काष्ठा pt_regs *regs)
अणु
	पूर्णांक करोne = true;
	/* Coprocessor disabled exception */
	अगर (subtype == FPU_DISABLE_EXCEPTION) अणु
		preempt_disable();
		करो_fpu_context_चयन(regs);
		preempt_enable();
	पूर्ण
	/* Coprocessor exception such as underflow and overflow */
	अन्यथा अगर (subtype == FPU_EXCEPTION)
		handle_fpu_exception(regs);
	अन्यथा
		करोne = false;
	वापस करोne;
पूर्ण
