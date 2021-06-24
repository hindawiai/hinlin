<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASMm68k_ELF_H
#घोषणा __ASMm68k_ELF_H

/*
 * ELF रेजिस्टर definitions..
 */

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/user.h>

/*
 * 68k ELF relocation types
 */
#घोषणा R_68K_NONE	0
#घोषणा R_68K_32	1
#घोषणा R_68K_16	2
#घोषणा R_68K_8		3
#घोषणा R_68K_PC32	4
#घोषणा R_68K_PC16	5
#घोषणा R_68K_PC8	6
#घोषणा R_68K_GOT32	7
#घोषणा R_68K_GOT16	8
#घोषणा R_68K_GOT8	9
#घोषणा R_68K_GOT32O	10
#घोषणा R_68K_GOT16O	11
#घोषणा R_68K_GOT8O	12
#घोषणा R_68K_PLT32	13
#घोषणा R_68K_PLT16	14
#घोषणा R_68K_PLT8	15
#घोषणा R_68K_PLT32O	16
#घोषणा R_68K_PLT16O	17
#घोषणा R_68K_PLT8O	18
#घोषणा R_68K_COPY	19
#घोषणा R_68K_GLOB_DAT	20
#घोषणा R_68K_JMP_SLOT	21
#घोषणा R_68K_RELATIVE	22

प्रकार अचिन्हित दीर्घ elf_greg_t;

#घोषणा ELF_NGREG (माप(काष्ठा user_regs_काष्ठा) / माप(elf_greg_t))
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार काष्ठा user_m68kfp_काष्ठा elf_fpregset_t;

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) ((x)->e_machine == EM_68K)

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS32
#घोषणा ELF_DATA	ELFDATA2MSB
#घोषणा ELF_ARCH	EM_68K

/* For SVR4/m68k the function poपूर्णांकer to be रेजिस्टरed with `निकास_पर' is
   passed in %a1.  Although my copy of the ABI has no such statement, it
   is actually used on ASV.  */
#घोषणा ELF_PLAT_INIT(_r, load_addr)	_r->a1 = 0

#अगर defined(CONFIG_SUN3) || defined(CONFIG_COLDFIRE)
#घोषणा ELF_EXEC_PAGESIZE	8192
#अन्यथा
#घोषणा ELF_EXEC_PAGESIZE	4096
#पूर्ण_अगर

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.  */

#अगर_अघोषित CONFIG_SUN3
#घोषणा ELF_ET_DYN_BASE         0xD0000000UL
#अन्यथा
#घोषणा ELF_ET_DYN_BASE         0x0D800000UL
#पूर्ण_अगर

#घोषणा ELF_CORE_COPY_REGS(pr_reg, regs)				\
	/* Bleech. */							\
	pr_reg[0] = regs->d1;						\
	pr_reg[1] = regs->d2;						\
	pr_reg[2] = regs->d3;						\
	pr_reg[3] = regs->d4;						\
	pr_reg[4] = regs->d5;						\
	pr_reg[7] = regs->a0;						\
	pr_reg[8] = regs->a1;						\
	pr_reg[9] = regs->a2;						\
	pr_reg[14] = regs->d0;						\
	pr_reg[15] = rdusp();						\
	pr_reg[16] = regs->orig_d0;					\
	pr_reg[17] = regs->sr;						\
	pr_reg[18] = regs->pc;						\
	pr_reg[19] = (regs->क्रमmat << 12) | regs->vector;		\
	अणु								\
	  काष्ठा चयन_stack *sw = ((काष्ठा चयन_stack *)regs) - 1;	\
	  pr_reg[5] = sw->d6;						\
	  pr_reg[6] = sw->d7;						\
	  pr_reg[10] = sw->a3;						\
	  pr_reg[11] = sw->a4;						\
	  pr_reg[12] = sw->a5;						\
	  pr_reg[13] = sw->a6;						\
	पूर्ण

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this cpu supports.  */

#घोषणा ELF_HWCAP	(0)

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo.  */

#घोषणा ELF_PLATFORM  (शून्य)

#पूर्ण_अगर
