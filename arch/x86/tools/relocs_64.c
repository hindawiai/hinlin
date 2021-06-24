<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "relocs.h"

#घोषणा ELF_BITS 64

#घोषणा ELF_MACHINE             EM_X86_64
#घोषणा ELF_MACHINE_NAME        "x86_64"
#घोषणा SHT_REL_TYPE            SHT_RELA
#घोषणा Elf_Rel                 Elf64_Rela

#घोषणा ELF_CLASS               ELFCLASS64
#घोषणा ELF_R_SYM(val)          ELF64_R_SYM(val)
#घोषणा ELF_R_TYPE(val)         ELF64_R_TYPE(val)
#घोषणा ELF_ST_TYPE(o)          ELF64_ST_TYPE(o)
#घोषणा ELF_ST_BIND(o)          ELF64_ST_BIND(o)
#घोषणा ELF_ST_VISIBILITY(o)    ELF64_ST_VISIBILITY(o)

#समावेश "relocs.c"
