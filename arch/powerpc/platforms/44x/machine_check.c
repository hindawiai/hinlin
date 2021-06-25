<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/ptrace.h>

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cacheflush.h>

पूर्णांक machine_check_440A(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ reason = regs->dsisr;

	prपूर्णांकk("Machine check in kernel mode.\n");
	अगर (reason & ESR_IMCP)अणु
		prपूर्णांकk("Instruction Synchronous Machine Check exception\n");
		mtspr(SPRN_ESR, reason & ~ESR_IMCP);
	पूर्ण
	अन्यथा अणु
		u32 mcsr = mfspr(SPRN_MCSR);
		अगर (mcsr & MCSR_IB)
			prपूर्णांकk("Instruction Read PLB Error\n");
		अगर (mcsr & MCSR_DRB)
			prपूर्णांकk("Data Read PLB Error\n");
		अगर (mcsr & MCSR_DWB)
			prपूर्णांकk("Data Write PLB Error\n");
		अगर (mcsr & MCSR_TLBP)
			prपूर्णांकk("TLB Parity Error\n");
		अगर (mcsr & MCSR_ICP)अणु
			flush_inकाष्ठाion_cache();
			prपूर्णांकk("I-Cache Parity Error\n");
		पूर्ण
		अगर (mcsr & MCSR_DCSP)
			prपूर्णांकk("D-Cache Search Parity Error\n");
		अगर (mcsr & MCSR_DCFP)
			prपूर्णांकk("D-Cache Flush Parity Error\n");
		अगर (mcsr & MCSR_IMPE)
			prपूर्णांकk("Machine Check exception is imprecise\n");

		/* Clear MCSR */
		mtspr(SPRN_MCSR, mcsr);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC_47x
पूर्णांक machine_check_47x(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ reason = regs->dsisr;
	u32 mcsr;

	prपूर्णांकk(KERN_ERR "Machine check in kernel mode.\n");
	अगर (reason & ESR_IMCP) अणु
		prपूर्णांकk(KERN_ERR "Instruction Synchronous Machine Check exception\n");
		mtspr(SPRN_ESR, reason & ~ESR_IMCP);
		वापस 0;
	पूर्ण
	mcsr = mfspr(SPRN_MCSR);
	अगर (mcsr & MCSR_IB)
		prपूर्णांकk(KERN_ERR "Instruction Read PLB Error\n");
	अगर (mcsr & MCSR_DRB)
		prपूर्णांकk(KERN_ERR "Data Read PLB Error\n");
	अगर (mcsr & MCSR_DWB)
		prपूर्णांकk(KERN_ERR "Data Write PLB Error\n");
	अगर (mcsr & MCSR_TLBP)
		prपूर्णांकk(KERN_ERR "TLB Parity Error\n");
	अगर (mcsr & MCSR_ICP) अणु
		flush_inकाष्ठाion_cache();
		prपूर्णांकk(KERN_ERR "I-Cache Parity Error\n");
	पूर्ण
	अगर (mcsr & MCSR_DCSP)
		prपूर्णांकk(KERN_ERR "D-Cache Search Parity Error\n");
	अगर (mcsr & PPC47x_MCSR_GPR)
		prपूर्णांकk(KERN_ERR "GPR Parity Error\n");
	अगर (mcsr & PPC47x_MCSR_FPR)
		prपूर्णांकk(KERN_ERR "FPR Parity Error\n");
	अगर (mcsr & PPC47x_MCSR_IPR)
		prपूर्णांकk(KERN_ERR "Machine Check exception is imprecise\n");

	/* Clear MCSR */
	mtspr(SPRN_MCSR, mcsr);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_47x */
