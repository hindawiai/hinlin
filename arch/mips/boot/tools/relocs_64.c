<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "relocs.h"

#घोषणा ELF_BITS 64

#घोषणा ELF_MACHINE             EM_MIPS
#घोषणा ELF_MACHINE_NAME        "MIPS64"
#घोषणा SHT_REL_TYPE            SHT_RELA
#घोषणा Elf_Rel                 Elf64_Rela

प्रकार uपूर्णांक8_t Elf64_Byte;

प्रकार जोड़ अणु
	काष्ठा अणु
		Elf64_Word r_sym;	/* Symbol index.  */
		Elf64_Byte r_ssym;	/* Special symbol.  */
		Elf64_Byte r_type3;	/* Third relocation.  */
		Elf64_Byte r_type2;	/* Second relocation.  */
		Elf64_Byte r_type;	/* First relocation.  */
	पूर्ण fields;
	Elf64_Xword unused;
पूर्ण Elf64_Mips_Rela;

#घोषणा ELF_CLASS               ELFCLASS64
#घोषणा ELF_R_SYM(val)          (((Elf64_Mips_Rela *)(&val))->fields.r_sym)
#घोषणा ELF_R_TYPE(val)         (((Elf64_Mips_Rela *)(&val))->fields.r_type)
#घोषणा ELF_ST_TYPE(o)          ELF64_ST_TYPE(o)
#घोषणा ELF_ST_BIND(o)          ELF64_ST_BIND(o)
#घोषणा ELF_ST_VISIBILITY(o)    ELF64_ST_VISIBILITY(o)

#समावेश "relocs.c"
