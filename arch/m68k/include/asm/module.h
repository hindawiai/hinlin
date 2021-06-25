<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_M68K_MODULE_H
#घोषणा _ASM_M68K_MODULE_H

#समावेश <यंत्र-generic/module.h>

क्रमागत m68k_fixup_type अणु
	m68k_fixup_memoffset,
	m68k_fixup_vnode_shअगरt,
पूर्ण;

काष्ठा m68k_fixup_info अणु
	क्रमागत m68k_fixup_type type;
	व्योम *addr;
पूर्ण;

काष्ठा mod_arch_specअगरic अणु
	काष्ठा m68k_fixup_info *fixup_start, *fixup_end;
पूर्ण;

#अगर_घोषित CONFIG_MMU

#घोषणा MODULE_ARCH_INIT अणु				\
	.fixup_start		= __start_fixup,	\
	.fixup_end		= __stop_fixup,		\
पूर्ण


#घोषणा m68k_fixup(type, addr)			\
	"	.section \".m68k_fixup\",\"aw\"\n"	\
	"	.long " #type "," #addr "\n"	\
	"	.previous\n"

#पूर्ण_अगर /* CONFIG_MMU */

बाह्य काष्ठा m68k_fixup_info __start_fixup[], __stop_fixup[];

काष्ठा module;
बाह्य व्योम module_fixup(काष्ठा module *mod, काष्ठा m68k_fixup_info *start,
			 काष्ठा m68k_fixup_info *end);

#पूर्ण_अगर /* _ASM_M68K_MODULE_H */
