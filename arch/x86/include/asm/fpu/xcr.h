<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_FPU_XCR_H
#घोषणा _ASM_X86_FPU_XCR_H

/*
 * MXCSR and XCR definitions:
 */

अटल अंतरभूत व्योम ldmxcsr(u32 mxcsr)
अणु
	यंत्र अस्थिर("ldmxcsr %0" :: "m" (mxcsr));
पूर्ण

बाह्य अचिन्हित पूर्णांक mxcsr_feature_mask;

#घोषणा XCR_XFEATURE_ENABLED_MASK	0x00000000

अटल अंतरभूत u64 xgetbv(u32 index)
अणु
	u32 eax, edx;

	यंत्र अस्थिर("xgetbv" : "=a" (eax), "=d" (edx) : "c" (index));
	वापस eax + ((u64)edx << 32);
पूर्ण

अटल अंतरभूत व्योम xsetbv(u32 index, u64 value)
अणु
	u32 eax = value;
	u32 edx = value >> 32;

	यंत्र अस्थिर("xsetbv" :: "a" (eax), "d" (edx), "c" (index));
पूर्ण

#पूर्ण_अगर /* _ASM_X86_FPU_XCR_H */
