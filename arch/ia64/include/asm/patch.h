<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_PATCH_H
#घोषणा _ASM_IA64_PATCH_H

/*
 * Copyright (C) 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * There are a number of reasons क्रम patching inकाष्ठाions.  Rather than duplicating code
 * all over the place, we put the common stuff here.  Reasons क्रम patching: in-kernel
 * module-loader, भव-to-physical patch-list, McKinley Errata 9 workaround, and gate
 * shared library.  Unकरोubtedly, some of these reasons will disappear and others will
 * be added over समय.
 */
#समावेश <linux/elf.h>
#समावेश <linux/types.h>

बाह्य व्योम ia64_patch (u64 insn_addr, u64 mask, u64 val);	/* patch any insn slot */
बाह्य व्योम ia64_patch_imm64 (u64 insn_addr, u64 val);		/* patch "movl" w/असल. value*/
बाह्य व्योम ia64_patch_imm60 (u64 insn_addr, u64 val);		/* patch "brl" w/ip-rel value */

बाह्य व्योम ia64_patch_mckinley_e9 (अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम ia64_patch_vtop (अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम ia64_patch_phys_stack_reg(अचिन्हित दीर्घ val);
बाह्य व्योम ia64_patch_rse (अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम ia64_patch_gate (व्योम);

#पूर्ण_अगर /* _ASM_IA64_PATCH_H */
