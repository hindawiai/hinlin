<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_H8300_ELF_H
#घोषणा __ASM_H8300_ELF_H

/*
 * ELF रेजिस्टर definitions..
 */

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/user.h>

प्रकार अचिन्हित दीर्घ elf_greg_t;

#घोषणा ELF_NGREG (माप(काष्ठा user_regs_काष्ठा) / माप(elf_greg_t))
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];
प्रकार अचिन्हित दीर्घ elf_fpregset_t;

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) ((x)->e_machine == EM_H8_300)

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS32
#घोषणा ELF_DATA	ELFDATA2MSB
#घोषणा ELF_ARCH	EM_H8_300
#अगर defined(CONFIG_CPU_H8300H)
#घोषणा ELF_CORE_EFLAGS 0x810000
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_H8S)
#घोषणा ELF_CORE_EFLAGS 0x820000
#पूर्ण_अगर

#घोषणा ELF_PLAT_INIT(_r) करो अणु (_r)->er1 = 0; पूर्ण जबतक (0)

#घोषणा ELF_EXEC_PAGESIZE	4096

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.  */

#घोषणा ELF_ET_DYN_BASE         0xD0000000UL

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this cpu supports.  */

#घोषणा ELF_HWCAP	(0)

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo.  */

#घोषणा ELF_PLATFORM  (शून्य)

#घोषणा R_H8_NONE       0
#घोषणा R_H8_सूची32      1
#घोषणा R_H8_सूची32_28   2
#घोषणा R_H8_सूची32_24   3
#घोषणा R_H8_सूची32_16   4
#घोषणा R_H8_सूची32U     6
#घोषणा R_H8_सूची32U_28  7
#घोषणा R_H8_सूची32U_24  8
#घोषणा R_H8_सूची32U_20  9
#घोषणा R_H8_सूची32U_16 10
#घोषणा R_H8_सूची24     11
#घोषणा R_H8_सूची24_20  12
#घोषणा R_H8_सूची24_16  13
#घोषणा R_H8_सूची24U    14
#घोषणा R_H8_सूची24U_20 15
#घोषणा R_H8_सूची24U_16 16
#घोषणा R_H8_सूची16     17
#घोषणा R_H8_सूची16U    18
#घोषणा R_H8_सूची16S_32 19
#घोषणा R_H8_सूची16S_28 20
#घोषणा R_H8_सूची16S_24 21
#घोषणा R_H8_सूची16S_20 22
#घोषणा R_H8_सूची16S    23
#घोषणा R_H8_सूची8      24
#घोषणा R_H8_सूची8U     25
#घोषणा R_H8_सूची8Z_32  26
#घोषणा R_H8_सूची8Z_28  27
#घोषणा R_H8_सूची8Z_24  28
#घोषणा R_H8_सूची8Z_20  29
#घोषणा R_H8_सूची8Z_16  30
#घोषणा R_H8_PCREL16   31
#घोषणा R_H8_PCREL8    32
#घोषणा R_H8_BPOS      33
#घोषणा R_H8_PCREL32   34
#घोषणा R_H8_GOT32O    35
#घोषणा R_H8_GOT16O    36
#घोषणा R_H8_सूची16A8   59
#घोषणा R_H8_सूची16R8   60
#घोषणा R_H8_सूची24A8   61
#घोषणा R_H8_सूची24R8   62
#घोषणा R_H8_सूची32A16  63
#घोषणा R_H8_ABS32     65
#घोषणा R_H8_ABS32A16 127

#पूर्ण_अगर
