<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_MODULE_H
#घोषणा __ASM_GENERIC_MODULE_H

/*
 * Many architectures just need a simple module
 * loader without arch specअगरic data.
 */
#अगर_अघोषित CONFIG_HAVE_MOD_ARCH_SPECIFIC
काष्ठा mod_arch_specअगरic
अणु
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#घोषणा Elf_Shdr	Elf64_Shdr
#घोषणा Elf_Phdr	Elf64_Phdr
#घोषणा Elf_Sym		Elf64_Sym
#घोषणा Elf_Dyn		Elf64_Dyn
#घोषणा Elf_Ehdr	Elf64_Ehdr
#घोषणा Elf_Addr	Elf64_Addr
#अगर_घोषित CONFIG_MODULES_USE_ELF_REL
#घोषणा Elf_Rel		Elf64_Rel
#पूर्ण_अगर
#अगर_घोषित CONFIG_MODULES_USE_ELF_RELA
#घोषणा Elf_Rela	Elf64_Rela
#पूर्ण_अगर
#घोषणा ELF_R_TYPE(X)	ELF64_R_TYPE(X)
#घोषणा ELF_R_SYM(X)	ELF64_R_SYM(X)

#अन्यथा /* CONFIG_64BIT */

#घोषणा Elf_Shdr	Elf32_Shdr
#घोषणा Elf_Phdr	Elf32_Phdr
#घोषणा Elf_Sym		Elf32_Sym
#घोषणा Elf_Dyn		Elf32_Dyn
#घोषणा Elf_Ehdr	Elf32_Ehdr
#घोषणा Elf_Addr	Elf32_Addr
#अगर_घोषित CONFIG_MODULES_USE_ELF_REL
#घोषणा Elf_Rel		Elf32_Rel
#पूर्ण_अगर
#अगर_घोषित CONFIG_MODULES_USE_ELF_RELA
#घोषणा Elf_Rela	Elf32_Rela
#पूर्ण_अगर
#घोषणा ELF_R_TYPE(X)	ELF32_R_TYPE(X)
#घोषणा ELF_R_SYM(X)	ELF32_R_SYM(X)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_MODULE_H */
