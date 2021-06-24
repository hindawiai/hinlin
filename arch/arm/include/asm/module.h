<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARM_MODULE_H
#घोषणा _ASM_ARM_MODULE_H

#समावेश <यंत्र-generic/module.h>

काष्ठा unwind_table;

#अगर_घोषित CONFIG_ARM_UNWIND
क्रमागत अणु
	ARM_SEC_INIT,
	ARM_SEC_DEVINIT,
	ARM_SEC_CORE,
	ARM_SEC_EXIT,
	ARM_SEC_DEVEXIT,
	ARM_SEC_HOT,
	ARM_SEC_UNLIKELY,
	ARM_SEC_MAX,
पूर्ण;
#पूर्ण_अगर

काष्ठा mod_plt_sec अणु
	काष्ठा elf32_shdr	*plt;
	पूर्णांक			plt_count;
पूर्ण;

काष्ठा mod_arch_specअगरic अणु
#अगर_घोषित CONFIG_ARM_UNWIND
	काष्ठा unwind_table *unwind[ARM_SEC_MAX];
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_MODULE_PLTS
	काष्ठा mod_plt_sec	core;
	काष्ठा mod_plt_sec	init;
#पूर्ण_अगर
पूर्ण;

काष्ठा module;
u32 get_module_plt(काष्ठा module *mod, अचिन्हित दीर्घ loc, Elf32_Addr val);

#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा HAVE_ARCH_KALLSYMS_SYMBOL_VALUE
अटल अंतरभूत अचिन्हित दीर्घ kallsyms_symbol_value(स्थिर Elf_Sym *sym)
अणु
	अगर (ELF_ST_TYPE(sym->st_info) == STT_FUNC)
		वापस sym->st_value & ~1;

	वापस sym->st_value;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_ARM_MODULE_H */
