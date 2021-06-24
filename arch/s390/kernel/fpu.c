<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * In-kernel vector facility support functions
 *
 * Copyright IBM Corp. 2015
 * Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/fpu/types.h>
#समावेश <यंत्र/fpu/api.h>

यंत्र(".include \"asm/vx-insn.h\"\n");

व्योम __kernel_fpu_begin(काष्ठा kernel_fpu *state, u32 flags)
अणु
	/*
	 * Limit the save to the FPU/vector रेजिस्टरs alपढ़ोy
	 * in use by the previous context
	 */
	flags &= state->mask;

	अगर (flags & KERNEL_FPC)
		/* Save भग्नing poपूर्णांक control */
		यंत्र अस्थिर("stfpc %0" : "=Q" (state->fpc));

	अगर (!MACHINE_HAS_VX) अणु
		अगर (flags & KERNEL_VXR_V0V7) अणु
			/* Save भग्नing-poपूर्णांक रेजिस्टरs */
			यंत्र अस्थिर("std 0,%0" : "=Q" (state->fprs[0]));
			यंत्र अस्थिर("std 1,%0" : "=Q" (state->fprs[1]));
			यंत्र अस्थिर("std 2,%0" : "=Q" (state->fprs[2]));
			यंत्र अस्थिर("std 3,%0" : "=Q" (state->fprs[3]));
			यंत्र अस्थिर("std 4,%0" : "=Q" (state->fprs[4]));
			यंत्र अस्थिर("std 5,%0" : "=Q" (state->fprs[5]));
			यंत्र अस्थिर("std 6,%0" : "=Q" (state->fprs[6]));
			यंत्र अस्थिर("std 7,%0" : "=Q" (state->fprs[7]));
			यंत्र अस्थिर("std 8,%0" : "=Q" (state->fprs[8]));
			यंत्र अस्थिर("std 9,%0" : "=Q" (state->fprs[9]));
			यंत्र अस्थिर("std 10,%0" : "=Q" (state->fprs[10]));
			यंत्र अस्थिर("std 11,%0" : "=Q" (state->fprs[11]));
			यंत्र अस्थिर("std 12,%0" : "=Q" (state->fprs[12]));
			यंत्र अस्थिर("std 13,%0" : "=Q" (state->fprs[13]));
			यंत्र अस्थिर("std 14,%0" : "=Q" (state->fprs[14]));
			यंत्र अस्थिर("std 15,%0" : "=Q" (state->fprs[15]));
		पूर्ण
		वापस;
	पूर्ण

	/* Test and save vector रेजिस्टरs */
	यंत्र अस्थिर (
		/*
		 * Test अगर any vector रेजिस्टर must be saved and, अगर so,
		 * test अगर all रेजिस्टर can be saved.
		 */
		"	la	1,%[vxrs]\n"	/* load save area */
		"	tmll	%[m],30\n"	/* KERNEL_VXR */
		"	jz	7f\n"		/* no work -> करोne */
		"	jo	5f\n"		/* -> save V0..V31 */
		/*
		 * Test क्रम special हाल KERNEL_FPU_MID only. In this
		 * हाल a vsपंचांग V8..V23 is the best inकाष्ठाion
		 */
		"	chi	%[m],12\n"	/* KERNEL_VXR_MID */
		"	jne	0f\n"		/* -> save V8..V23 */
		"	VSTM	8,23,128,1\n"	/* vsपंचांग %v8,%v23,128(%r1) */
		"	j	7f\n"
		/* Test and save the first half of 16 vector रेजिस्टरs */
		"0:	tmll	%[m],6\n"	/* KERNEL_VXR_LOW */
		"	jz	3f\n"		/* -> KERNEL_VXR_HIGH */
		"	jo	2f\n"		/* 11 -> save V0..V15 */
		"	brc	2,1f\n"		/* 10 -> save V8..V15 */
		"	VSTM	0,7,0,1\n"	/* vsपंचांग %v0,%v7,0(%r1) */
		"	j	3f\n"
		"1:	VSTM	8,15,128,1\n"	/* vsपंचांग %v8,%v15,128(%r1) */
		"	j	3f\n"
		"2:	VSTM	0,15,0,1\n"	/* vsपंचांग %v0,%v15,0(%r1) */
		/* Test and save the second half of 16 vector रेजिस्टरs */
		"3:	tmll	%[m],24\n"	/* KERNEL_VXR_HIGH */
		"	jz	7f\n"
		"	jo	6f\n"		/* 11 -> save V16..V31 */
		"	brc	2,4f\n"		/* 10 -> save V24..V31 */
		"	VSTM	16,23,256,1\n"	/* vsपंचांग %v16,%v23,256(%r1) */
		"	j	7f\n"
		"4:	VSTM	24,31,384,1\n"	/* vsपंचांग %v24,%v31,384(%r1) */
		"	j	7f\n"
		"5:	VSTM	0,15,0,1\n"	/* vsपंचांग %v0,%v15,0(%r1) */
		"6:	VSTM	16,31,256,1\n"	/* vsपंचांग %v16,%v31,256(%r1) */
		"7:"
		: [vxrs] "=Q" (*(काष्ठा vx_array *) &state->vxrs)
		: [m] "d" (flags)
		: "1", "cc");
पूर्ण
EXPORT_SYMBOL(__kernel_fpu_begin);

व्योम __kernel_fpu_end(काष्ठा kernel_fpu *state, u32 flags)
अणु
	/*
	 * Limit the restore to the FPU/vector रेजिस्टरs of the
	 * previous context that have been overwritte by the
	 * current context
	 */
	flags &= state->mask;

	अगर (flags & KERNEL_FPC)
		/* Restore भग्नing-poपूर्णांक controls */
		यंत्र अस्थिर("lfpc %0" : : "Q" (state->fpc));

	अगर (!MACHINE_HAS_VX) अणु
		अगर (flags & KERNEL_VXR_V0V7) अणु
			/* Restore भग्नing-poपूर्णांक रेजिस्टरs */
			यंत्र अस्थिर("ld 0,%0" : : "Q" (state->fprs[0]));
			यंत्र अस्थिर("ld 1,%0" : : "Q" (state->fprs[1]));
			यंत्र अस्थिर("ld 2,%0" : : "Q" (state->fprs[2]));
			यंत्र अस्थिर("ld 3,%0" : : "Q" (state->fprs[3]));
			यंत्र अस्थिर("ld 4,%0" : : "Q" (state->fprs[4]));
			यंत्र अस्थिर("ld 5,%0" : : "Q" (state->fprs[5]));
			यंत्र अस्थिर("ld 6,%0" : : "Q" (state->fprs[6]));
			यंत्र अस्थिर("ld 7,%0" : : "Q" (state->fprs[7]));
			यंत्र अस्थिर("ld 8,%0" : : "Q" (state->fprs[8]));
			यंत्र अस्थिर("ld 9,%0" : : "Q" (state->fprs[9]));
			यंत्र अस्थिर("ld 10,%0" : : "Q" (state->fprs[10]));
			यंत्र अस्थिर("ld 11,%0" : : "Q" (state->fprs[11]));
			यंत्र अस्थिर("ld 12,%0" : : "Q" (state->fprs[12]));
			यंत्र अस्थिर("ld 13,%0" : : "Q" (state->fprs[13]));
			यंत्र अस्थिर("ld 14,%0" : : "Q" (state->fprs[14]));
			यंत्र अस्थिर("ld 15,%0" : : "Q" (state->fprs[15]));
		पूर्ण
		वापस;
	पूर्ण

	/* Test and restore (load) vector रेजिस्टरs */
	यंत्र अस्थिर (
		/*
		 * Test अगर any vector रेजिस्टर must be loaded and, अगर so,
		 * test अगर all रेजिस्टरs can be loaded at once.
		 */
		"	la	1,%[vxrs]\n"	/* load restore area */
		"	tmll	%[m],30\n"	/* KERNEL_VXR */
		"	jz	7f\n"		/* no work -> करोne */
		"	jo	5f\n"		/* -> restore V0..V31 */
		/*
		 * Test क्रम special हाल KERNEL_FPU_MID only. In this
		 * हाल a vlm V8..V23 is the best inकाष्ठाion
		 */
		"	chi	%[m],12\n"	/* KERNEL_VXR_MID */
		"	jne	0f\n"		/* -> restore V8..V23 */
		"	VLM	8,23,128,1\n"	/* vlm %v8,%v23,128(%r1) */
		"	j	7f\n"
		/* Test and restore the first half of 16 vector रेजिस्टरs */
		"0:	tmll	%[m],6\n"	/* KERNEL_VXR_LOW */
		"	jz	3f\n"		/* -> KERNEL_VXR_HIGH */
		"	jo	2f\n"		/* 11 -> restore V0..V15 */
		"	brc	2,1f\n"		/* 10 -> restore V8..V15 */
		"	VLM	0,7,0,1\n"	/* vlm %v0,%v7,0(%r1) */
		"	j	3f\n"
		"1:	VLM	8,15,128,1\n"	/* vlm %v8,%v15,128(%r1) */
		"	j	3f\n"
		"2:	VLM	0,15,0,1\n"	/* vlm %v0,%v15,0(%r1) */
		/* Test and restore the second half of 16 vector रेजिस्टरs */
		"3:	tmll	%[m],24\n"	/* KERNEL_VXR_HIGH */
		"	jz	7f\n"
		"	jo	6f\n"		/* 11 -> restore V16..V31 */
		"	brc	2,4f\n"		/* 10 -> restore V24..V31 */
		"	VLM	16,23,256,1\n"	/* vlm %v16,%v23,256(%r1) */
		"	j	7f\n"
		"4:	VLM	24,31,384,1\n"	/* vlm %v24,%v31,384(%r1) */
		"	j	7f\n"
		"5:	VLM	0,15,0,1\n"	/* vlm %v0,%v15,0(%r1) */
		"6:	VLM	16,31,256,1\n"	/* vlm %v16,%v31,256(%r1) */
		"7:"
		: [vxrs] "=Q" (*(काष्ठा vx_array *) &state->vxrs)
		: [m] "d" (flags)
		: "1", "cc");
पूर्ण
EXPORT_SYMBOL(__kernel_fpu_end);

व्योम __load_fpu_regs(व्योम)
अणु
	काष्ठा fpu *state = &current->thपढ़ो.fpu;
	अचिन्हित दीर्घ *regs = current->thपढ़ो.fpu.regs;

	यंत्र अस्थिर("lfpc %0" : : "Q" (state->fpc));
	अगर (likely(MACHINE_HAS_VX)) अणु
		यंत्र अस्थिर("lgr	1,%0\n"
			     "VLM	0,15,0,1\n"
			     "VLM	16,31,256,1\n"
			     :
			     : "d" (regs)
			     : "1", "cc", "memory");
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर("ld 0,%0" : : "Q" (regs[0]));
		यंत्र अस्थिर("ld 1,%0" : : "Q" (regs[1]));
		यंत्र अस्थिर("ld 2,%0" : : "Q" (regs[2]));
		यंत्र अस्थिर("ld 3,%0" : : "Q" (regs[3]));
		यंत्र अस्थिर("ld 4,%0" : : "Q" (regs[4]));
		यंत्र अस्थिर("ld 5,%0" : : "Q" (regs[5]));
		यंत्र अस्थिर("ld 6,%0" : : "Q" (regs[6]));
		यंत्र अस्थिर("ld 7,%0" : : "Q" (regs[7]));
		यंत्र अस्थिर("ld 8,%0" : : "Q" (regs[8]));
		यंत्र अस्थिर("ld 9,%0" : : "Q" (regs[9]));
		यंत्र अस्थिर("ld 10,%0" : : "Q" (regs[10]));
		यंत्र अस्थिर("ld 11,%0" : : "Q" (regs[11]));
		यंत्र अस्थिर("ld 12,%0" : : "Q" (regs[12]));
		यंत्र अस्थिर("ld 13,%0" : : "Q" (regs[13]));
		यंत्र अस्थिर("ld 14,%0" : : "Q" (regs[14]));
		यंत्र अस्थिर("ld 15,%0" : : "Q" (regs[15]));
	पूर्ण
	clear_cpu_flag(CIF_FPU);
पूर्ण
EXPORT_SYMBOL(__load_fpu_regs);

व्योम load_fpu_regs(व्योम)
अणु
	raw_local_irq_disable();
	__load_fpu_regs();
	raw_local_irq_enable();
पूर्ण
EXPORT_SYMBOL(load_fpu_regs);

व्योम save_fpu_regs(व्योम)
अणु
	अचिन्हित दीर्घ flags, *regs;
	काष्ठा fpu *state;

	local_irq_save(flags);

	अगर (test_cpu_flag(CIF_FPU))
		जाओ out;

	state = &current->thपढ़ो.fpu;
	regs = current->thपढ़ो.fpu.regs;

	यंत्र अस्थिर("stfpc %0" : "=Q" (state->fpc));
	अगर (likely(MACHINE_HAS_VX)) अणु
		यंत्र अस्थिर("lgr	1,%0\n"
			     "VSTM	0,15,0,1\n"
			     "VSTM	16,31,256,1\n"
			     :
			     : "d" (regs)
			     : "1", "cc", "memory");
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर("std 0,%0" : "=Q" (regs[0]));
		यंत्र अस्थिर("std 1,%0" : "=Q" (regs[1]));
		यंत्र अस्थिर("std 2,%0" : "=Q" (regs[2]));
		यंत्र अस्थिर("std 3,%0" : "=Q" (regs[3]));
		यंत्र अस्थिर("std 4,%0" : "=Q" (regs[4]));
		यंत्र अस्थिर("std 5,%0" : "=Q" (regs[5]));
		यंत्र अस्थिर("std 6,%0" : "=Q" (regs[6]));
		यंत्र अस्थिर("std 7,%0" : "=Q" (regs[7]));
		यंत्र अस्थिर("std 8,%0" : "=Q" (regs[8]));
		यंत्र अस्थिर("std 9,%0" : "=Q" (regs[9]));
		यंत्र अस्थिर("std 10,%0" : "=Q" (regs[10]));
		यंत्र अस्थिर("std 11,%0" : "=Q" (regs[11]));
		यंत्र अस्थिर("std 12,%0" : "=Q" (regs[12]));
		यंत्र अस्थिर("std 13,%0" : "=Q" (regs[13]));
		यंत्र अस्थिर("std 14,%0" : "=Q" (regs[14]));
		यंत्र अस्थिर("std 15,%0" : "=Q" (regs[15]));
	पूर्ण
	set_cpu_flag(CIF_FPU);
out:
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(save_fpu_regs);
