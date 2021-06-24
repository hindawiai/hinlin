<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_KERNEL_PATCH_H
#घोषणा _PARISC_KERNEL_PATCH_H

/* stop machine and patch kernel text */
व्योम patch_text(व्योम *addr, अचिन्हित पूर्णांक insn);
व्योम patch_text_multiple(व्योम *addr, u32 *insn, अचिन्हित पूर्णांक len);

/* patch kernel text with machine alपढ़ोy stopped (e.g. in kgdb) */
व्योम __patch_text(व्योम *addr, u32 insn);
व्योम __patch_text_multiple(व्योम *addr, u32 *insn, अचिन्हित पूर्णांक len);

#पूर्ण_अगर
