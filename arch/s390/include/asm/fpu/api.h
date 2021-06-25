<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * In-kernel FPU support functions
 *
 *
 * Consider these guidelines beक्रमe using in-kernel FPU functions:
 *
 *  1. Use kernel_fpu_begin() and kernel_fpu_end() to enबंद all in-kernel
 *     use of भग्नing-poपूर्णांक or vector रेजिस्टरs and inकाष्ठाions.
 *
 *  2. For kernel_fpu_begin(), specअगरy the vector रेजिस्टर range you want to
 *     use with the KERNEL_VXR_* स्थिरants. Consider these usage guidelines:
 *
 *     a) If your function typically runs in process-context, use the lower
 *	  half of the vector रेजिस्टरs, क्रम example, specअगरy KERNEL_VXR_LOW.
 *     b) If your function typically runs in soft-irq or hard-irq context,
 *	  prefer using the upper half of the vector रेजिस्टरs, क्रम example,
 *	  specअगरy KERNEL_VXR_HIGH.
 *
 *     If you adhere to these guidelines, an पूर्णांकerrupted process context
 *     करोes not require to save and restore vector रेजिस्टरs because of
 *     disjoपूर्णांक रेजिस्टर ranges.
 *
 *     Also note that the __kernel_fpu_begin()/__kernel_fpu_end() functions
 *     includes logic to save and restore up to 16 vector रेजिस्टरs at once.
 *
 *  3. You can nest kernel_fpu_begin()/kernel_fpu_end() by using dअगरferent
 *     काष्ठा kernel_fpu states.  Vector रेजिस्टरs that are in use by outer
 *     levels are saved and restored.  You can minimize the save and restore
 *     efक्रमt by choosing disjoपूर्णांक vector रेजिस्टर ranges.
 *
 *  5. To use vector भग्नing-poपूर्णांक inकाष्ठाions, specअगरy the KERNEL_FPC
 *     flag to save and restore भग्नing-poपूर्णांक controls in addition to any
 *     vector रेजिस्टर range.
 *
 *  6. To use भग्नing-poपूर्णांक रेजिस्टरs and inकाष्ठाions only, specअगरy the
 *     KERNEL_FPR flag.  This flag triggers a save and restore of vector
 *     रेजिस्टरs V0 to V15 and भग्नing-poपूर्णांक controls.
 *
 * Copyright IBM Corp. 2015
 * Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */

#अगर_अघोषित _ASM_S390_FPU_API_H
#घोषणा _ASM_S390_FPU_API_H

#समावेश <linux/preempt.h>

व्योम save_fpu_regs(व्योम);
व्योम load_fpu_regs(व्योम);
व्योम __load_fpu_regs(व्योम);

अटल अंतरभूत पूर्णांक test_fp_ctl(u32 fpc)
अणु
	u32 orig_fpc;
	पूर्णांक rc;

	यंत्र अस्थिर(
		"	efpc    %1\n"
		"	sfpc	%2\n"
		"0:	sfpc	%1\n"
		"	la	%0,0\n"
		"1:\n"
		EX_TABLE(0b,1b)
		: "=d" (rc), "=&d" (orig_fpc)
		: "d" (fpc), "0" (-EINVAL));
	वापस rc;
पूर्ण

#घोषणा KERNEL_FPC		1
#घोषणा KERNEL_VXR_V0V7		2
#घोषणा KERNEL_VXR_V8V15	4
#घोषणा KERNEL_VXR_V16V23	8
#घोषणा KERNEL_VXR_V24V31	16

#घोषणा KERNEL_VXR_LOW		(KERNEL_VXR_V0V7|KERNEL_VXR_V8V15)
#घोषणा KERNEL_VXR_MID		(KERNEL_VXR_V8V15|KERNEL_VXR_V16V23)
#घोषणा KERNEL_VXR_HIGH		(KERNEL_VXR_V16V23|KERNEL_VXR_V24V31)

#घोषणा KERNEL_VXR		(KERNEL_VXR_LOW|KERNEL_VXR_HIGH)
#घोषणा KERNEL_FPR		(KERNEL_FPC|KERNEL_VXR_V0V7)

काष्ठा kernel_fpu;

/*
 * Note the functions below must be called with preemption disabled.
 * Do not enable preemption beक्रमe calling __kernel_fpu_end() to prevent
 * an corruption of an existing kernel FPU state.
 *
 * Prefer using the kernel_fpu_begin()/kernel_fpu_end() pair of functions.
 */
व्योम __kernel_fpu_begin(काष्ठा kernel_fpu *state, u32 flags);
व्योम __kernel_fpu_end(काष्ठा kernel_fpu *state, u32 flags);


अटल अंतरभूत व्योम kernel_fpu_begin(काष्ठा kernel_fpu *state, u32 flags)
अणु
	preempt_disable();
	state->mask = S390_lowcore.fpu_flags;
	अगर (!test_cpu_flag(CIF_FPU))
		/* Save user space FPU state and रेजिस्टर contents */
		save_fpu_regs();
	अन्यथा अगर (state->mask & flags)
		/* Save FPU/vector रेजिस्टर in-use by the kernel */
		__kernel_fpu_begin(state, flags);
	S390_lowcore.fpu_flags |= flags;
पूर्ण

अटल अंतरभूत व्योम kernel_fpu_end(काष्ठा kernel_fpu *state, u32 flags)
अणु
	S390_lowcore.fpu_flags = state->mask;
	अगर (state->mask & flags)
		/* Restore FPU/vector रेजिस्टर in-use by the kernel */
		__kernel_fpu_end(state, flags);
	preempt_enable();
पूर्ण

#पूर्ण_अगर /* _ASM_S390_FPU_API_H */
