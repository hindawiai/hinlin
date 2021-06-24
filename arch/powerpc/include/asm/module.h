<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_MODULE_H
#घोषणा _ASM_POWERPC_MODULE_H
#अगर_घोषित __KERNEL__

#समावेश <linux/list.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र-generic/module.h>

#अगर_अघोषित __घातerpc64__
/*
 * Thanks to Paul M क्रम explaining this.
 *
 * PPC can only करो rel jumps += 32MB, and often the kernel and other
 * modules are further away than this.  So, we jump to a table of
 * trampolines attached to the module (the Procedure Linkage Table)
 * whenever that happens.
 */

काष्ठा ppc_plt_entry अणु
	/* 16 byte jump inकाष्ठाion sequence (4 inकाष्ठाions) */
	अचिन्हित पूर्णांक jump[4];
पूर्ण;
#पूर्ण_अगर	/* __घातerpc64__ */


काष्ठा mod_arch_specअगरic अणु
#अगर_घोषित __घातerpc64__
	अचिन्हित पूर्णांक stubs_section;	/* Index of stubs section in module */
	अचिन्हित पूर्णांक toc_section;	/* What section is the TOC? */
	bool toc_fixed;			/* Have we fixed up .TOC.? */

	/* For module function descriptor dereference */
	अचिन्हित दीर्घ start_opd;
	अचिन्हित दीर्घ end_opd;
#अन्यथा /* घातerpc64 */
	/* Indices of PLT sections within module. */
	अचिन्हित पूर्णांक core_plt_section;
	अचिन्हित पूर्णांक init_plt_section;
#पूर्ण_अगर /* घातerpc64 */

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	अचिन्हित दीर्घ tramp;
#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	अचिन्हित दीर्घ tramp_regs;
#पूर्ण_अगर
#पूर्ण_अगर

	/* List of BUG addresses, source line numbers and filenames */
	काष्ठा list_head bug_list;
	काष्ठा bug_entry *bug_table;
	अचिन्हित पूर्णांक num_bugs;
पूर्ण;

/*
 * Select ELF headers.
 * Make empty section क्रम module_frob_arch_sections to expand.
 */

#अगर_घोषित __घातerpc64__
#    अगरdef MODULE
	यंत्र(".section .stubs,\"ax\",@nobits; .align 3; .previous");
#    endअगर
#अन्यथा
#    अगरdef MODULE
	यंत्र(".section .plt,\"ax\",@nobits; .align 3; .previous");
	यंत्र(".section .init.plt,\"ax\",@nobits; .align 3; .previous");
#    endअगर	/* MODULE */
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
#    अगरdef MODULE
	यंत्र(".section .ftrace.tramp,\"ax\",@nobits; .align 3; .previous");
#    endअगर	/* MODULE */

पूर्णांक module_trampoline_target(काष्ठा module *mod, अचिन्हित दीर्घ trampoline,
			     अचिन्हित दीर्घ *target);
पूर्णांक module_finalize_ftrace(काष्ठा module *mod, स्थिर Elf_Shdr *sechdrs);
#अन्यथा
अटल अंतरभूत पूर्णांक module_finalize_ftrace(काष्ठा module *mod, स्थिर Elf_Shdr *sechdrs)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_MODULE_H */
