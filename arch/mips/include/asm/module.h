<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_MODULE_H
#घोषणा _ASM_MODULE_H

#समावेश <linux/list.h>
#समावेश <linux/elf.h>
#समावेश <यंत्र/extable.h>

काष्ठा mod_arch_specअगरic अणु
	/* Data Bus Error exception tables */
	काष्ठा list_head dbe_list;
	स्थिर काष्ठा exception_table_entry *dbe_start;
	स्थिर काष्ठा exception_table_entry *dbe_end;
	काष्ठा mips_hi16 *r_mips_hi16_list;
पूर्ण;

प्रकार uपूर्णांक8_t Elf64_Byte;		/* Type क्रम a 8-bit quantity.  */

प्रकार काष्ठा अणु
	Elf64_Addr r_offset;			/* Address of relocation.  */
	Elf64_Word r_sym;			/* Symbol index.  */
	Elf64_Byte r_ssym;			/* Special symbol.  */
	Elf64_Byte r_type3;			/* Third relocation.  */
	Elf64_Byte r_type2;			/* Second relocation.  */
	Elf64_Byte r_type;			/* First relocation.  */
पूर्ण Elf64_Mips_Rel;

प्रकार काष्ठा अणु
	Elf64_Addr r_offset;			/* Address of relocation.  */
	Elf64_Word r_sym;			/* Symbol index.  */
	Elf64_Byte r_ssym;			/* Special symbol.  */
	Elf64_Byte r_type3;			/* Third relocation.  */
	Elf64_Byte r_type2;			/* Second relocation.  */
	Elf64_Byte r_type;			/* First relocation.  */
	Elf64_Sxword r_addend;			/* Addend.  */
पूर्ण Elf64_Mips_Rela;

#अगर_घोषित CONFIG_32BIT
#घोषणा Elf_Shdr	Elf32_Shdr
#घोषणा Elf_Sym		Elf32_Sym
#घोषणा Elf_Ehdr	Elf32_Ehdr
#घोषणा Elf_Addr	Elf32_Addr
#घोषणा Elf_Rel		Elf32_Rel
#घोषणा Elf_Rela	Elf32_Rela
#घोषणा ELF_R_TYPE(X)	ELF32_R_TYPE(X)
#घोषणा ELF_R_SYM(X)	ELF32_R_SYM(X)

#घोषणा Elf_Mips_Rel	Elf32_Rel
#घोषणा Elf_Mips_Rela	Elf32_Rela

#घोषणा ELF_MIPS_R_SYM(rel) ELF32_R_SYM((rel).r_info)
#घोषणा ELF_MIPS_R_TYPE(rel) ELF32_R_TYPE((rel).r_info)

#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#घोषणा Elf_Shdr	Elf64_Shdr
#घोषणा Elf_Sym		Elf64_Sym
#घोषणा Elf_Ehdr	Elf64_Ehdr
#घोषणा Elf_Addr	Elf64_Addr
#घोषणा Elf_Rel		Elf64_Rel
#घोषणा Elf_Rela	Elf64_Rela
#घोषणा ELF_R_TYPE(X)	ELF64_R_TYPE(X)
#घोषणा ELF_R_SYM(X)	ELF64_R_SYM(X)

#घोषणा Elf_Mips_Rel	Elf64_Mips_Rel
#घोषणा Elf_Mips_Rela	Elf64_Mips_Rela

#घोषणा ELF_MIPS_R_SYM(rel) ((rel).r_sym)
#घोषणा ELF_MIPS_R_TYPE(rel) ((rel).r_type)

#पूर्ण_अगर

#अगर_घोषित CONFIG_MODULES
/* Given an address, look क्रम it in the exception tables. */
स्थिर काष्ठा exception_table_entry*search_module_dbetables(अचिन्हित दीर्घ addr);
#अन्यथा
/* Given an address, look क्रम it in the exception tables. */
अटल अंतरभूत स्थिर काष्ठा exception_table_entry *
search_module_dbetables(अचिन्हित दीर्घ addr)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_MODULE_H */
