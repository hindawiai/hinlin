<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_LINKAGE_H
#घोषणा _ASM_X86_LINKAGE_H

#समावेश <linux/stringअगरy.h>

#अघोषित notrace
#घोषणा notrace __attribute__((no_instrument_function))

#अगर_घोषित CONFIG_X86_32
#घोषणा यंत्रlinkage CPP_ASMLINKAGE __attribute__((regparm(0)))
#पूर्ण_अगर /* CONFIG_X86_32 */

#अगर_घोषित __ASSEMBLY__

#अगर defined(CONFIG_X86_64) || defined(CONFIG_X86_ALIGNMENT_16)
#घोषणा __ALIGN		.p2align 4, 0x90
#घोषणा __ALIGN_STR	__stringअगरy(__ALIGN)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_LINKAGE_H */

