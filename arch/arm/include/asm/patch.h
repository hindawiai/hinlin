<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARM_KERNEL_PATCH_H
#घोषणा _ARM_KERNEL_PATCH_H

व्योम patch_text(व्योम *addr, अचिन्हित पूर्णांक insn);
व्योम __patch_text_real(व्योम *addr, अचिन्हित पूर्णांक insn, bool remap);

अटल अंतरभूत व्योम __patch_text(व्योम *addr, अचिन्हित पूर्णांक insn)
अणु
	__patch_text_real(addr, insn, true);
पूर्ण

अटल अंतरभूत व्योम __patch_text_early(व्योम *addr, अचिन्हित पूर्णांक insn)
अणु
	__patch_text_real(addr, insn, false);
पूर्ण

#पूर्ण_अगर
