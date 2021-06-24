<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * FPU state and रेजिस्टर content conversion primitives
 *
 * Copyright IBM Corp. 2015
 * Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */

#अगर_अघोषित _ASM_S390_FPU_INTERNAL_H
#घोषणा _ASM_S390_FPU_INTERNAL_H

#समावेश <linux/माला.स>
#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र/fpu/types.h>

अटल अंतरभूत व्योम save_vx_regs(__vector128 *vxrs)
अणु
	यंत्र अस्थिर(
		"	la	1,%0\n"
		"	.word	0xe70f,0x1000,0x003e\n"	/* vsपंचांग 0,15,0(1) */
		"	.word	0xe70f,0x1100,0x0c3e\n"	/* vsपंचांग 16,31,256(1) */
		: "=Q" (*(काष्ठा vx_array *) vxrs) : : "1");
पूर्ण

अटल अंतरभूत व्योम convert_vx_to_fp(freg_t *fprs, __vector128 *vxrs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < __NUM_FPRS; i++)
		fprs[i] = *(freg_t *)(vxrs + i);
पूर्ण

अटल अंतरभूत व्योम convert_fp_to_vx(__vector128 *vxrs, freg_t *fprs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < __NUM_FPRS; i++)
		*(freg_t *)(vxrs + i) = fprs[i];
पूर्ण

अटल अंतरभूत व्योम fpregs_store(_s390_fp_regs *fpregs, काष्ठा fpu *fpu)
अणु
	fpregs->pad = 0;
	fpregs->fpc = fpu->fpc;
	अगर (MACHINE_HAS_VX)
		convert_vx_to_fp((freg_t *)&fpregs->fprs, fpu->vxrs);
	अन्यथा
		स_नकल((freg_t *)&fpregs->fprs, fpu->fprs,
		       माप(fpregs->fprs));
पूर्ण

अटल अंतरभूत व्योम fpregs_load(_s390_fp_regs *fpregs, काष्ठा fpu *fpu)
अणु
	fpu->fpc = fpregs->fpc;
	अगर (MACHINE_HAS_VX)
		convert_fp_to_vx(fpu->vxrs, (freg_t *)&fpregs->fprs);
	अन्यथा
		स_नकल(fpu->fprs, (freg_t *)&fpregs->fprs,
		       माप(fpregs->fprs));
पूर्ण

#पूर्ण_अगर /* _ASM_S390_FPU_INTERNAL_H */
