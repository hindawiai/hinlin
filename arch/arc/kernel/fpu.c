<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fpu.c - save/restore of Floating Poपूर्णांक Unit Registers on task चयन
 *
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/sched.h>
#समावेश <यंत्र/fpu.h>

#अगर_घोषित CONFIG_ISA_ARCOMPACT

/*
 * To save/restore FPU regs, simplest scheme would use LR/SR insns.
 * However since SR serializes the pipeline, an alternate "hack" can be used
 * which uses the FPU Exchange insn (DEXCL) to r/w FPU regs.
 *
 * Store to 64bit dpfp1 reg from a pair of core regs:
 *   dexcl1 0, r1, r0  ; where r1:r0 is the 64 bit val
 *
 * Read from dpfp1 पूर्णांकo pair of core regs (w/o clobbering dpfp1)
 *   mov_s    r3, 0
 *   daddh11  r1, r3, r3   ; get "hi" पूर्णांकo r1 (dpfp1 unchanged)
 *   dexcl1   r0, r1, r3   ; get "low" पूर्णांकo r0 (dpfp1 low clobbered)
 *   dexcl1    0, r1, r0   ; restore dpfp1 to orig value
 *
 * However we can tweak the पढ़ो, so that पढ़ो-out of outgoing task's FPU regs
 * and ग_लिखो of incoming task's regs happen in one shot. So all the work is
 * करोne beक्रमe context चयन
 */

व्योम fpu_save_restore(काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	अचिन्हित पूर्णांक *saveto = &prev->thपढ़ो.fpu.aux_dpfp[0].l;
	अचिन्हित पूर्णांक *पढ़ोfrom = &next->thपढ़ो.fpu.aux_dpfp[0].l;

	स्थिर अचिन्हित पूर्णांक zero = 0;

	__यंत्र__ __अस्थिर__(
		"daddh11  %0, %2, %2\n"
		"dexcl1   %1, %3, %4\n"
		: "=&r" (*(saveto + 1)), /* early clobber must here */
		  "=&r" (*(saveto))
		: "r" (zero), "r" (*(पढ़ोfrom + 1)), "r" (*(पढ़ोfrom))
	);

	__यंत्र__ __अस्थिर__(
		"daddh22  %0, %2, %2\n"
		"dexcl2   %1, %3, %4\n"
		: "=&r"(*(saveto + 3)),	/* early clobber must here */
		  "=&r"(*(saveto + 2))
		: "r" (zero), "r" (*(पढ़ोfrom + 3)), "r" (*(पढ़ोfrom + 2))
	);
पूर्ण

#अन्यथा

व्योम fpu_init_task(काष्ठा pt_regs *regs)
अणु
	/* शेष rounding mode */
	ग_लिखो_aux_reg(ARC_REG_FPU_CTRL, 0x100);

	/* set "Write enable" to allow explicit ग_लिखो to exception flags */
	ग_लिखो_aux_reg(ARC_REG_FPU_STATUS, 0x80000000);
पूर्ण

व्योम fpu_save_restore(काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	काष्ठा arc_fpu *save = &prev->thपढ़ो.fpu;
	काष्ठा arc_fpu *restore = &next->thपढ़ो.fpu;

	save->ctrl = पढ़ो_aux_reg(ARC_REG_FPU_CTRL);
	save->status = पढ़ो_aux_reg(ARC_REG_FPU_STATUS);

	ग_लिखो_aux_reg(ARC_REG_FPU_CTRL, restore->ctrl);
	ग_लिखो_aux_reg(ARC_REG_FPU_STATUS, restore->status);
पूर्ण

#पूर्ण_अगर
