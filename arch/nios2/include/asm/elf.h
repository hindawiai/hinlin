<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 */

#अगर_अघोषित _ASM_NIOS2_ELF_H
#घोषणा _ASM_NIOS2_ELF_H

#समावेश <uapi/यंत्र/elf.h>

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) ((x)->e_machine == EM_ALTERA_NIOS2)

#घोषणा ELF_PLAT_INIT(_r, load_addr)

#घोषणा CORE_DUMP_USE_REGSET
#घोषणा ELF_EXEC_PAGESIZE	4096

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.  */

#घोषणा ELF_ET_DYN_BASE		0xD0000000UL

/* regs is काष्ठा pt_regs, pr_reg is elf_gregset_t (which is
   now काष्ठा_user_regs, they are dअगरferent) */

#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES	1
काष्ठा linux_binprm;
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
	पूर्णांक uses_पूर्णांकerp);
#घोषणा ELF_CORE_COPY_REGS(pr_reg, regs)				\
अणु करो अणु									\
	/* Bleech. */							\
	pr_reg[0]  = regs->r8;						\
	pr_reg[1]  = regs->r9;						\
	pr_reg[2]  = regs->r10;						\
	pr_reg[3]  = regs->r11;						\
	pr_reg[4]  = regs->r12;						\
	pr_reg[5]  = regs->r13;						\
	pr_reg[6]  = regs->r14;						\
	pr_reg[7]  = regs->r15;						\
	pr_reg[8]  = regs->r1;						\
	pr_reg[9]  = regs->r2;						\
	pr_reg[10] = regs->r3;						\
	pr_reg[11] = regs->r4;						\
	pr_reg[12] = regs->r5;						\
	pr_reg[13] = regs->r6;						\
	pr_reg[14] = regs->r7;						\
	pr_reg[15] = regs->orig_r2;					\
	pr_reg[16] = regs->ra;						\
	pr_reg[17] = regs->fp;						\
	pr_reg[18] = regs->sp;						\
	pr_reg[19] = regs->gp;						\
	pr_reg[20] = regs->estatus;					\
	pr_reg[21] = regs->ea;						\
	pr_reg[22] = regs->orig_r7;					\
	अणु								\
		काष्ठा चयन_stack *sw = ((काष्ठा चयन_stack *)regs) - 1; \
		pr_reg[23] = sw->r16;					\
		pr_reg[24] = sw->r17;					\
		pr_reg[25] = sw->r18;					\
		pr_reg[26] = sw->r19;					\
		pr_reg[27] = sw->r20;					\
		pr_reg[28] = sw->r21;					\
		pr_reg[29] = sw->r22;					\
		pr_reg[30] = sw->r23;					\
		pr_reg[31] = sw->fp;					\
		pr_reg[32] = sw->gp;					\
		pr_reg[33] = sw->ra;					\
	पूर्ण								\
पूर्ण जबतक (0); पूर्ण

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this cpu supports.  */

#घोषणा ELF_HWCAP	(0)

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo.  */

#घोषणा ELF_PLATFORM  (शून्य)

#पूर्ण_अगर /* _ASM_NIOS2_ELF_H */
