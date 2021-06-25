<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * FPU data काष्ठाures
 *
 * Copyright IBM Corp. 2015
 * Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */

#अगर_अघोषित _ASM_S390_FPU_TYPES_H
#घोषणा _ASM_S390_FPU_TYPES_H

#समावेश <यंत्र/sigcontext.h>

काष्ठा fpu अणु
	__u32 fpc;		/* Floating-poपूर्णांक control */
	व्योम *regs;		/* Poपूर्णांकer to the current save area */
	जोड़ अणु
		/* Floating-poपूर्णांक रेजिस्टर save area */
		freg_t fprs[__NUM_FPRS];
		/* Vector रेजिस्टर save area */
		__vector128 vxrs[__NUM_VXRS];
	पूर्ण;
पूर्ण;

/* VX array काष्ठाure क्रम address opeअक्रम स्थिरraपूर्णांकs in अंतरभूत assemblies */
काष्ठा vx_array अणु __vector128 _[__NUM_VXRS]; पूर्ण;

/* In-kernel FPU state काष्ठाure */
काष्ठा kernel_fpu अणु
	u32	    mask;
	u32	    fpc;
	जोड़ अणु
		freg_t fprs[__NUM_FPRS];
		__vector128 vxrs[__NUM_VXRS];
	पूर्ण;
पूर्ण;

#पूर्ण_अगर /* _ASM_S390_FPU_TYPES_H */
