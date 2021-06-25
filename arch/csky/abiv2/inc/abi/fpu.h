<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_FPU_H
#घोषणा __ASM_CSKY_FPU_H

#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/ptrace.h>

पूर्णांक fpu_libc_helper(काष्ठा pt_regs *regs);
व्योम fpu_fpe(काष्ठा pt_regs *regs);

अटल अंतरभूत व्योम init_fpu(व्योम) अणु mtcr("cr<1, 2>", 0); पूर्ण

व्योम save_to_user_fp(काष्ठा user_fp *user_fp);
व्योम restore_from_user_fp(काष्ठा user_fp *user_fp);

/*
 * Define the fesr bit क्रम fpe handle.
 */
#घोषणा  FPE_ILLE  (1 << 16)    /* Illegal inकाष्ठाion  */
#घोषणा  FPE_FEC   (1 << 7)     /* Input भग्न-poपूर्णांक arithmetic exception */
#घोषणा  FPE_IDC   (1 << 5)     /* Input denormalized exception */
#घोषणा  FPE_IXC   (1 << 4)     /* Inexact exception */
#घोषणा  FPE_UFC   (1 << 3)     /* Underflow exception */
#घोषणा  FPE_OFC   (1 << 2)     /* Overflow exception */
#घोषणा  FPE_DZC   (1 << 1)     /* Divide by zero exception */
#घोषणा  FPE_IOC   (1 << 0)     /* Invalid operation exception */
#घोषणा  FPE_REGULAR_EXCEPTION (FPE_IXC | FPE_UFC | FPE_OFC | FPE_DZC | FPE_IOC)

#अगर_घोषित CONFIG_OPEN_FPU_IDE
#घोषणा IDE_STAT   (1 << 5)
#अन्यथा
#घोषणा IDE_STAT   0
#पूर्ण_अगर

#अगर_घोषित CONFIG_OPEN_FPU_IXE
#घोषणा IXE_STAT   (1 << 4)
#अन्यथा
#घोषणा IXE_STAT   0
#पूर्ण_अगर

#अगर_घोषित CONFIG_OPEN_FPU_UFE
#घोषणा UFE_STAT   (1 << 3)
#अन्यथा
#घोषणा UFE_STAT   0
#पूर्ण_अगर

#अगर_घोषित CONFIG_OPEN_FPU_OFE
#घोषणा OFE_STAT   (1 << 2)
#अन्यथा
#घोषणा OFE_STAT   0
#पूर्ण_अगर

#अगर_घोषित CONFIG_OPEN_FPU_DZE
#घोषणा DZE_STAT   (1 << 1)
#अन्यथा
#घोषणा DZE_STAT   0
#पूर्ण_अगर

#अगर_घोषित CONFIG_OPEN_FPU_IOE
#घोषणा IOE_STAT   (1 << 0)
#अन्यथा
#घोषणा IOE_STAT   0
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_CSKY_FPU_H */
