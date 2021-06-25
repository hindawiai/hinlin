<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_MODULE_H
#घोषणा __ASM_MODULE_H

#समावेश <यंत्र-generic/module.h>

#अगर_घोषित CONFIG_ARM64_MODULE_PLTS
काष्ठा mod_plt_sec अणु
	पूर्णांक			plt_shndx;
	पूर्णांक			plt_num_entries;
	पूर्णांक			plt_max_entries;
पूर्ण;

काष्ठा mod_arch_specअगरic अणु
	काष्ठा mod_plt_sec	core;
	काष्ठा mod_plt_sec	init;

	/* क्रम CONFIG_DYNAMIC_FTRACE */
	काष्ठा plt_entry	*ftrace_trampolines;
पूर्ण;
#पूर्ण_अगर

u64 module_emit_plt_entry(काष्ठा module *mod, Elf64_Shdr *sechdrs,
			  व्योम *loc, स्थिर Elf64_Rela *rela,
			  Elf64_Sym *sym);

u64 module_emit_veneer_क्रम_adrp(काष्ठा module *mod, Elf64_Shdr *sechdrs,
				व्योम *loc, u64 val);

#अगर_घोषित CONFIG_RANDOMIZE_BASE
बाह्य u64 module_alloc_base;
#अन्यथा
#घोषणा module_alloc_base	((u64)_etext - MODULES_VSIZE)
#पूर्ण_अगर

काष्ठा plt_entry अणु
	/*
	 * A program that conक्रमms to the AArch64 Procedure Call Standard
	 * (AAPCS64) must assume that a veneer that alters IP0 (x16) and/or
	 * IP1 (x17) may be inserted at any branch inकाष्ठाion that is
	 * exposed to a relocation that supports दीर्घ branches. Since that
	 * is exactly what we are dealing with here, we are मुक्त to use x16
	 * as a scratch रेजिस्टर in the PLT veneers.
	 */
	__le32	adrp;	/* adrp	x16, ....			*/
	__le32	add;	/* add	x16, x16, #0x....		*/
	__le32	br;	/* br	x16				*/
पूर्ण;

अटल अंतरभूत bool is_क्रमbidden_offset_क्रम_adrp(व्योम *place)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_ERRATUM_843419) &&
	       cpus_have_स्थिर_cap(ARM64_WORKAROUND_843419) &&
	       ((u64)place & 0xfff) >= 0xff8;
पूर्ण

काष्ठा plt_entry get_plt_entry(u64 dst, व्योम *pc);
bool plt_entries_equal(स्थिर काष्ठा plt_entry *a, स्थिर काष्ठा plt_entry *b);

अटल अंतरभूत bool plt_entry_is_initialized(स्थिर काष्ठा plt_entry *e)
अणु
	वापस e->adrp || e->add || e->br;
पूर्ण

#पूर्ण_अगर /* __ASM_MODULE_H */
