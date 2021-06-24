<शैली गुरु>
/*
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#अगर_अघोषित _UAPI_ASM_RISCV_ELF_H
#घोषणा _UAPI_ASM_RISCV_ELF_H

#समावेश <यंत्र/ptrace.h>

/* ELF रेजिस्टर definitions */
प्रकार अचिन्हित दीर्घ elf_greg_t;
प्रकार काष्ठा user_regs_काष्ठा elf_gregset_t;
#घोषणा ELF_NGREG (माप(elf_gregset_t) / माप(elf_greg_t))

/* We करोn't support f without d, or q.  */
प्रकार __u64 elf_fpreg_t;
प्रकार जोड़ __riscv_fp_state elf_fpregset_t;
#घोषणा ELF_NFPREG (माप(काष्ठा __riscv_d_ext_state) / माप(elf_fpreg_t))

#अगर __riscv_xlen == 64
#घोषणा ELF_RISCV_R_SYM(r_info)		ELF64_R_SYM(r_info)
#घोषणा ELF_RISCV_R_TYPE(r_info)	ELF64_R_TYPE(r_info)
#अन्यथा
#घोषणा ELF_RISCV_R_SYM(r_info)		ELF32_R_SYM(r_info)
#घोषणा ELF_RISCV_R_TYPE(r_info)	ELF32_R_TYPE(r_info)
#पूर्ण_अगर

/*
 * RISC-V relocation types
 */

/* Relocation types used by the dynamic linker */
#घोषणा R_RISCV_NONE		0
#घोषणा R_RISCV_32		1
#घोषणा R_RISCV_64		2
#घोषणा R_RISCV_RELATIVE	3
#घोषणा R_RISCV_COPY		4
#घोषणा R_RISCV_JUMP_SLOT	5
#घोषणा R_RISCV_TLS_DTPMOD32	6
#घोषणा R_RISCV_TLS_DTPMOD64	7
#घोषणा R_RISCV_TLS_DTPREL32	8
#घोषणा R_RISCV_TLS_DTPREL64	9
#घोषणा R_RISCV_TLS_TPREL32	10
#घोषणा R_RISCV_TLS_TPREL64	11

/* Relocation types not used by the dynamic linker */
#घोषणा R_RISCV_BRANCH		16
#घोषणा R_RISCV_JAL		17
#घोषणा R_RISCV_CALL		18
#घोषणा R_RISCV_CALL_PLT	19
#घोषणा R_RISCV_GOT_HI20	20
#घोषणा R_RISCV_TLS_GOT_HI20	21
#घोषणा R_RISCV_TLS_GD_HI20	22
#घोषणा R_RISCV_PCREL_HI20	23
#घोषणा R_RISCV_PCREL_LO12_I	24
#घोषणा R_RISCV_PCREL_LO12_S	25
#घोषणा R_RISCV_HI20		26
#घोषणा R_RISCV_LO12_I		27
#घोषणा R_RISCV_LO12_S		28
#घोषणा R_RISCV_TPREL_HI20	29
#घोषणा R_RISCV_TPREL_LO12_I	30
#घोषणा R_RISCV_TPREL_LO12_S	31
#घोषणा R_RISCV_TPREL_ADD	32
#घोषणा R_RISCV_ADD8		33
#घोषणा R_RISCV_ADD16		34
#घोषणा R_RISCV_ADD32		35
#घोषणा R_RISCV_ADD64		36
#घोषणा R_RISCV_SUB8		37
#घोषणा R_RISCV_SUB16		38
#घोषणा R_RISCV_SUB32		39
#घोषणा R_RISCV_SUB64		40
#घोषणा R_RISCV_GNU_VTINHERIT	41
#घोषणा R_RISCV_GNU_VTENTRY	42
#घोषणा R_RISCV_ALIGN		43
#घोषणा R_RISCV_RVC_BRANCH	44
#घोषणा R_RISCV_RVC_JUMP	45
#घोषणा R_RISCV_LUI		46
#घोषणा R_RISCV_GPREL_I		47
#घोषणा R_RISCV_GPREL_S		48
#घोषणा R_RISCV_TPREL_I		49
#घोषणा R_RISCV_TPREL_S		50
#घोषणा R_RISCV_RELAX		51
#घोषणा R_RISCV_SUB6		52
#घोषणा R_RISCV_SET6		53
#घोषणा R_RISCV_SET8		54
#घोषणा R_RISCV_SET16		55
#घोषणा R_RISCV_SET32		56
#घोषणा R_RISCV_32_PCREL	57


#पूर्ण_अगर /* _UAPI_ASM_RISCV_ELF_H */
