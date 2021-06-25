<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_INSN_H
#घोषणा __ASM_ARM_INSN_H

अटल अंतरभूत अचिन्हित दीर्घ
arm_gen_nop(व्योम)
अणु
#अगर_घोषित CONFIG_THUMB2_KERNEL
	वापस 0xf3af8000; /* nop.w */
#अन्यथा
	वापस 0xe1a00000; /* mov r0, r0 */
#पूर्ण_अगर
पूर्ण

अचिन्हित दीर्घ
__arm_gen_branch(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr, bool link);

अटल अंतरभूत अचिन्हित दीर्घ
arm_gen_branch(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr)
अणु
	वापस __arm_gen_branch(pc, addr, false);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
arm_gen_branch_link(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr)
अणु
	वापस __arm_gen_branch(pc, addr, true);
पूर्ण

#पूर्ण_अगर
