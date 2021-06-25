<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "relocs.h"

#घोषणा ELF_BITS 32

#घोषणा ELF_MACHINE		EM_386
#घोषणा ELF_MACHINE_NAME	"i386"
#घोषणा SHT_REL_TYPE		SHT_REL
#घोषणा Elf_Rel			ElfW(Rel)

#घोषणा ELF_CLASS		ELFCLASS32
#घोषणा ELF_R_SYM(val)		ELF32_R_SYM(val)
#घोषणा ELF_R_TYPE(val)		ELF32_R_TYPE(val)
#घोषणा ELF_ST_TYPE(o)		ELF32_ST_TYPE(o)
#घोषणा ELF_ST_BIND(o)		ELF32_ST_BIND(o)
#घोषणा ELF_ST_VISIBILITY(o)	ELF32_ST_VISIBILITY(o)

#समावेश "relocs.c"
