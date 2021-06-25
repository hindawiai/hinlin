<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * FPU regset handling methods:
 */
#अगर_अघोषित _ASM_X86_FPU_REGSET_H
#घोषणा _ASM_X86_FPU_REGSET_H

#समावेश <linux/regset.h>

बाह्य user_regset_active_fn regset_fpregs_active, regset_xregset_fpregs_active;
बाह्य user_regset_get2_fn fpregs_get, xfpregs_get, fpregs_soft_get,
				 xstateregs_get;
बाह्य user_regset_set_fn fpregs_set, xfpregs_set, fpregs_soft_set,
				 xstateregs_set;

/*
 * xstateregs_active == regset_fpregs_active. Please refer to the comment
 * at the definition of regset_fpregs_active.
 */
#घोषणा xstateregs_active	regset_fpregs_active

#पूर्ण_अगर /* _ASM_X86_FPU_REGSET_H */
