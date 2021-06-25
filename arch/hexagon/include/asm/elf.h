<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ELF definitions क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __ASM_ELF_H
#घोषणा __ASM_ELF_H

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/user.h>
#समावेश <linux/elf-em.h>

काष्ठा elf32_hdr;

/*
 * ELF header e_flags defines.
 */

/*  should have stuff like "CPU type" and maybe "ABI version", etc  */

/* Hexagon relocations */
  /* V2 */
#घोषणा R_HEXAGON_NONE           0
#घोषणा R_HEXAGON_B22_PCREL      1
#घोषणा R_HEXAGON_B15_PCREL      2
#घोषणा R_HEXAGON_B7_PCREL       3
#घोषणा R_HEXAGON_LO16           4
#घोषणा R_HEXAGON_HI16           5
#घोषणा R_HEXAGON_32             6
#घोषणा R_HEXAGON_16             7
#घोषणा R_HEXAGON_8              8
#घोषणा R_HEXAGON_GPREL16_0      9
#घोषणा R_HEXAGON_GPREL16_1     10
#घोषणा R_HEXAGON_GPREL16_2     11
#घोषणा R_HEXAGON_GPREL16_3     12
#घोषणा R_HEXAGON_HL16          13
  /* V3 */
#घोषणा R_HEXAGON_B13_PCREL     14
  /* V4 */
#घोषणा R_HEXAGON_B9_PCREL      15
  /* V4 (extenders) */
#घोषणा R_HEXAGON_B32_PCREL_X   16
#घोषणा R_HEXAGON_32_6_X        17
  /* V4 (extended) */
#घोषणा R_HEXAGON_B22_PCREL_X   18
#घोषणा R_HEXAGON_B15_PCREL_X   19
#घोषणा R_HEXAGON_B13_PCREL_X   20
#घोषणा R_HEXAGON_B9_PCREL_X    21
#घोषणा R_HEXAGON_B7_PCREL_X    22
#घोषणा R_HEXAGON_16_X          23
#घोषणा R_HEXAGON_12_X          24
#घोषणा R_HEXAGON_11_X          25
#घोषणा R_HEXAGON_10_X          26
#घोषणा R_HEXAGON_9_X           27
#घोषणा R_HEXAGON_8_X           28
#घोषणा R_HEXAGON_7_X           29
#घोषणा R_HEXAGON_6_X           30
  /* V2 PIC */
#घोषणा R_HEXAGON_32_PCREL      31
#घोषणा R_HEXAGON_COPY          32
#घोषणा R_HEXAGON_GLOB_DAT      33
#घोषणा R_HEXAGON_JMP_SLOT      34
#घोषणा R_HEXAGON_RELATIVE      35
#घोषणा R_HEXAGON_PLT_B22_PCREL 36
#घोषणा R_HEXAGON_GOTOFF_LO16   37
#घोषणा R_HEXAGON_GOTOFF_HI16   38
#घोषणा R_HEXAGON_GOTOFF_32     39
#घोषणा R_HEXAGON_GOT_LO16      40
#घोषणा R_HEXAGON_GOT_HI16      41
#घोषणा R_HEXAGON_GOT_32        42
#घोषणा R_HEXAGON_GOT_16        43

/*
 * ELF रेजिस्टर definitions..
 */
प्रकार अचिन्हित दीर्घ elf_greg_t;

प्रकार काष्ठा user_regs_काष्ठा elf_gregset_t;
#घोषणा ELF_NGREG (माप(elf_gregset_t)/माप(अचिन्हित दीर्घ))

/*  Placeholder  */
प्रकार अचिन्हित दीर्घ elf_fpregset_t;

/*
 * Bypass the whole "regsets" thing क्रम now and use the define.
 */

#अगर CONFIG_HEXAGON_ARCH_VERSION >= 4
#घोषणा CS_COPYREGS(DEST,REGS) \
करो अणु\
	DEST.cs0 = REGS->cs0;\
	DEST.cs1 = REGS->cs1;\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा CS_COPYREGS(DEST,REGS)
#पूर्ण_अगर

#घोषणा ELF_CORE_COPY_REGS(DEST, REGS)	\
करो अणु					\
	DEST.r0 = REGS->r00;		\
	DEST.r1 = REGS->r01;		\
	DEST.r2 = REGS->r02;		\
	DEST.r3 = REGS->r03;		\
	DEST.r4 = REGS->r04;		\
	DEST.r5 = REGS->r05;		\
	DEST.r6 = REGS->r06;		\
	DEST.r7 = REGS->r07;		\
	DEST.r8 = REGS->r08;		\
	DEST.r9 = REGS->r09;		\
	DEST.r10 = REGS->r10;		\
	DEST.r11 = REGS->r11;		\
	DEST.r12 = REGS->r12;		\
	DEST.r13 = REGS->r13;		\
	DEST.r14 = REGS->r14;		\
	DEST.r15 = REGS->r15;		\
	DEST.r16 = REGS->r16;		\
	DEST.r17 = REGS->r17;		\
	DEST.r18 = REGS->r18;		\
	DEST.r19 = REGS->r19;		\
	DEST.r20 = REGS->r20;		\
	DEST.r21 = REGS->r21;		\
	DEST.r22 = REGS->r22;		\
	DEST.r23 = REGS->r23;		\
	DEST.r24 = REGS->r24;		\
	DEST.r25 = REGS->r25;		\
	DEST.r26 = REGS->r26;		\
	DEST.r27 = REGS->r27;		\
	DEST.r28 = REGS->r28;		\
	DEST.r29 = pt_psp(REGS);	\
	DEST.r30 = REGS->r30;		\
	DEST.r31 = REGS->r31;		\
	DEST.sa0 = REGS->sa0;		\
	DEST.lc0 = REGS->lc0;		\
	DEST.sa1 = REGS->sa1;		\
	DEST.lc1 = REGS->lc1;		\
	DEST.m0 = REGS->m0;		\
	DEST.m1 = REGS->m1;		\
	DEST.usr = REGS->usr;		\
	DEST.p3_0 = REGS->preds;	\
	DEST.gp = REGS->gp;		\
	DEST.ugp = REGS->ugp;		\
	CS_COPYREGS(DEST,REGS);		\
	DEST.pc = pt_elr(REGS);		\
	DEST.cause = pt_cause(REGS);	\
	DEST.badva = pt_badva(REGS);	\
पूर्ण जबतक (0);

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 * Checks the machine and ABI type.
 */
#घोषणा elf_check_arch(hdr)	((hdr)->e_machine == EM_HEXAGON)

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS32
#घोषणा ELF_DATA	ELFDATA2LSB
#घोषणा ELF_ARCH	EM_HEXAGON

#अगर CONFIG_HEXAGON_ARCH_VERSION == 2
#घोषणा ELF_CORE_EFLAGS 0x1
#पूर्ण_अगर

#अगर CONFIG_HEXAGON_ARCH_VERSION == 3
#घोषणा ELF_CORE_EFLAGS 0x2
#पूर्ण_अगर

#अगर CONFIG_HEXAGON_ARCH_VERSION == 4
#घोषणा ELF_CORE_EFLAGS 0x3
#पूर्ण_अगर

/*
 * Some architectures have ld.so set up a poपूर्णांकer to a function
 * to be रेजिस्टरed using निकास_पर, to facilitate cleanup.  So that
 * अटल executables will be well-behaved, we would null the रेजिस्टर
 * in question here, in the pt_regs काष्ठाure passed.  For now,
 * leave it a null macro.
 */
#घोषणा ELF_PLAT_INIT(regs, load_addr) करो अणु पूर्ण जबतक (0)

#घोषणा CORE_DUMP_USE_REGSET

/* Hrm is this going to cause problems क्रम changing PAGE_SIZE?  */
#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE

/*
 * This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
 * use of this is to invoke "./ld.so someprog" to test out a new version of
 * the loader.  We need to make sure that it is out of the way of the program
 * that it will "exec", and that there is sufficient room क्रम the brk.
 */
#घोषणा ELF_ET_DYN_BASE         0x08000000UL

/*
 * This yields a mask that user programs can use to figure out what
 * inकाष्ठाion set this cpu supports.
 */
#घोषणा ELF_HWCAP	(0)

/*
 * This yields a string that ld.so will use to load implementation
 * specअगरic libraries क्रम optimization.  This is more specअगरic in
 * पूर्णांकent than poking at uname or /proc/cpuinfo.
 */
#घोषणा ELF_PLATFORM  (शून्य)

#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES 1
काष्ठा linux_binprm;
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
				       पूर्णांक uses_पूर्णांकerp);


#पूर्ण_अगर
