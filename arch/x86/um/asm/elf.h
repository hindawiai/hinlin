<शैली गुरु>
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */
#अगर_अघोषित __UM_ELF_X86_H
#घोषणा __UM_ELF_X86_H

#समावेश <यंत्र/user.h>
#समावेश <skas.h>

#अगर_घोषित CONFIG_X86_32

#घोषणा R_386_NONE	0
#घोषणा R_386_32	1
#घोषणा R_386_PC32	2
#घोषणा R_386_GOT32	3
#घोषणा R_386_PLT32	4
#घोषणा R_386_COPY	5
#घोषणा R_386_GLOB_DAT	6
#घोषणा R_386_JMP_SLOT	7
#घोषणा R_386_RELATIVE	8
#घोषणा R_386_GOTOFF	9
#घोषणा R_386_GOTPC	10
#घोषणा R_386_NUM	11

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) \
	(((x)->e_machine == EM_386) || ((x)->e_machine == EM_486))

#घोषणा ELF_CLASS	ELFCLASS32
#घोषणा ELF_DATA        ELFDATA2LSB
#घोषणा ELF_ARCH        EM_386

#घोषणा ELF_PLAT_INIT(regs, load_addr) करो अणु \
	PT_REGS_BX(regs) = 0; \
	PT_REGS_CX(regs) = 0; \
	PT_REGS_DX(regs) = 0; \
	PT_REGS_SI(regs) = 0; \
	PT_REGS_DI(regs) = 0; \
	PT_REGS_BP(regs) = 0; \
	PT_REGS_AX(regs) = 0; \
पूर्ण जबतक (0)

/* Shamelessly stolen from include/यंत्र-i386/elf.h */

#घोषणा ELF_CORE_COPY_REGS(pr_reg, regs) करो अणु	\
	pr_reg[0] = PT_REGS_BX(regs);		\
	pr_reg[1] = PT_REGS_CX(regs);		\
	pr_reg[2] = PT_REGS_DX(regs);		\
	pr_reg[3] = PT_REGS_SI(regs);		\
	pr_reg[4] = PT_REGS_DI(regs);		\
	pr_reg[5] = PT_REGS_BP(regs);		\
	pr_reg[6] = PT_REGS_AX(regs);		\
	pr_reg[7] = PT_REGS_DS(regs);		\
	pr_reg[8] = PT_REGS_ES(regs);		\
	/* fake once used fs and gs selectors? */	\
	pr_reg[9] = PT_REGS_DS(regs);		\
	pr_reg[10] = PT_REGS_DS(regs);		\
	pr_reg[11] = PT_REGS_SYSCALL_NR(regs);	\
	pr_reg[12] = PT_REGS_IP(regs);		\
	pr_reg[13] = PT_REGS_CS(regs);		\
	pr_reg[14] = PT_REGS_EFLAGS(regs);	\
	pr_reg[15] = PT_REGS_SP(regs);		\
	pr_reg[16] = PT_REGS_SS(regs);		\
पूर्ण जबतक (0);

बाह्य अक्षर * elf_aux_platक्रमm;
#घोषणा ELF_PLATFORM (elf_aux_platक्रमm)

बाह्य अचिन्हित दीर्घ vsyscall_ehdr;
बाह्य अचिन्हित दीर्घ vsyscall_end;
बाह्य अचिन्हित दीर्घ __kernel_vsyscall;

/*
 * This is the range that is पढ़ोable by user mode, and things
 * acting like user mode such as get_user_pages.
 */
#घोषणा FIXADDR_USER_START      vsyscall_ehdr
#घोषणा FIXADDR_USER_END        vsyscall_end


/*
 * Architecture-neutral AT_ values in 0-17, leave some room
 * क्रम more of them, start the x86-specअगरic ones at 32.
 */
#घोषणा AT_SYSINFO		32
#घोषणा AT_SYSINFO_EHDR		33

#घोषणा ARCH_DLINFO						\
करो अणु								\
	अगर ( vsyscall_ehdr ) अणु					\
		NEW_AUX_ENT(AT_SYSINFO,	__kernel_vsyscall);	\
		NEW_AUX_ENT(AT_SYSINFO_EHDR, vsyscall_ehdr);	\
	पूर्ण							\
पूर्ण जबतक (0)

#अन्यथा

/* x86-64 relocation types, taken from यंत्र-x86_64/elf.h */
#घोषणा R_X86_64_NONE		0	/* No reloc */
#घोषणा R_X86_64_64		1	/* Direct 64 bit  */
#घोषणा R_X86_64_PC32		2	/* PC relative 32 bit चिन्हित */
#घोषणा R_X86_64_GOT32		3	/* 32 bit GOT entry */
#घोषणा R_X86_64_PLT32		4	/* 32 bit PLT address */
#घोषणा R_X86_64_COPY		5	/* Copy symbol at runसमय */
#घोषणा R_X86_64_GLOB_DAT	6	/* Create GOT entry */
#घोषणा R_X86_64_JUMP_SLOT	7	/* Create PLT entry */
#घोषणा R_X86_64_RELATIVE	8	/* Adjust by program base */
#घोषणा R_X86_64_GOTPCREL	9	/* 32 bit चिन्हित pc relative
					   offset to GOT */
#घोषणा R_X86_64_32		10	/* Direct 32 bit zero extended */
#घोषणा R_X86_64_32S		11	/* Direct 32 bit sign extended */
#घोषणा R_X86_64_16		12	/* Direct 16 bit zero extended */
#घोषणा R_X86_64_PC16		13	/* 16 bit sign extended pc relative */
#घोषणा R_X86_64_8		14	/* Direct 8 bit sign extended  */
#घोषणा R_X86_64_PC8		15	/* 8 bit sign extended pc relative */
#घोषणा R_X86_64_PC64		24	/* Place relative 64-bit चिन्हित */

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) \
	((x)->e_machine == EM_X86_64)

#घोषणा ELF_CLASS	ELFCLASS64
#घोषणा ELF_DATA        ELFDATA2LSB
#घोषणा ELF_ARCH        EM_X86_64

#घोषणा ELF_PLAT_INIT(regs, load_addr)    करो अणु \
	PT_REGS_BX(regs) = 0; \
	PT_REGS_CX(regs) = 0; \
	PT_REGS_DX(regs) = 0; \
	PT_REGS_SI(regs) = 0; \
	PT_REGS_DI(regs) = 0; \
	PT_REGS_BP(regs) = 0; \
	PT_REGS_AX(regs) = 0; \
	PT_REGS_R8(regs) = 0; \
	PT_REGS_R9(regs) = 0; \
	PT_REGS_R10(regs) = 0; \
	PT_REGS_R11(regs) = 0; \
	PT_REGS_R12(regs) = 0; \
	PT_REGS_R13(regs) = 0; \
	PT_REGS_R14(regs) = 0; \
	PT_REGS_R15(regs) = 0; \
पूर्ण जबतक (0)

#घोषणा ELF_CORE_COPY_REGS(pr_reg, _regs)		\
	(pr_reg)[0] = (_regs)->regs.gp[0];			\
	(pr_reg)[1] = (_regs)->regs.gp[1];			\
	(pr_reg)[2] = (_regs)->regs.gp[2];			\
	(pr_reg)[3] = (_regs)->regs.gp[3];			\
	(pr_reg)[4] = (_regs)->regs.gp[4];			\
	(pr_reg)[5] = (_regs)->regs.gp[5];			\
	(pr_reg)[6] = (_regs)->regs.gp[6];			\
	(pr_reg)[7] = (_regs)->regs.gp[7];			\
	(pr_reg)[8] = (_regs)->regs.gp[8];			\
	(pr_reg)[9] = (_regs)->regs.gp[9];			\
	(pr_reg)[10] = (_regs)->regs.gp[10];			\
	(pr_reg)[11] = (_regs)->regs.gp[11];			\
	(pr_reg)[12] = (_regs)->regs.gp[12];			\
	(pr_reg)[13] = (_regs)->regs.gp[13];			\
	(pr_reg)[14] = (_regs)->regs.gp[14];			\
	(pr_reg)[15] = (_regs)->regs.gp[15];			\
	(pr_reg)[16] = (_regs)->regs.gp[16];			\
	(pr_reg)[17] = (_regs)->regs.gp[17];			\
	(pr_reg)[18] = (_regs)->regs.gp[18];			\
	(pr_reg)[19] = (_regs)->regs.gp[19];			\
	(pr_reg)[20] = (_regs)->regs.gp[20];			\
	(pr_reg)[21] = current->thपढ़ो.arch.fs;			\
	(pr_reg)[22] = 0;					\
	(pr_reg)[23] = 0;					\
	(pr_reg)[24] = 0;					\
	(pr_reg)[25] = 0;					\
	(pr_reg)[26] = 0;

#घोषणा ELF_PLATFORM "x86_64"

/* No user-accessible fixmap addresses, i.e. vsyscall */
#घोषणा FIXADDR_USER_START      0
#घोषणा FIXADDR_USER_END        0

#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES 1
काष्ठा linux_binprm;
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
	पूर्णांक uses_पूर्णांकerp);

बाह्य अचिन्हित दीर्घ um_vdso_addr;
#घोषणा AT_SYSINFO_EHDR 33
#घोषणा ARCH_DLINFO	NEW_AUX_ENT(AT_SYSINFO_EHDR, um_vdso_addr)

#पूर्ण_अगर

प्रकार अचिन्हित दीर्घ elf_greg_t;

#घोषणा ELF_NGREG (माप(काष्ठा user_regs_काष्ठा) / माप(elf_greg_t))
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार काष्ठा user_i387_काष्ठा elf_fpregset_t;

काष्ठा task_काष्ठा;

बाह्य पूर्णांक elf_core_copy_fpregs(काष्ठा task_काष्ठा *t, elf_fpregset_t *fpu);

#घोषणा ELF_CORE_COPY_FPREGS(t, fpu) elf_core_copy_fpregs(t, fpu)

#घोषणा ELF_EXEC_PAGESIZE 4096

#घोषणा ELF_ET_DYN_BASE (TASK_SIZE / 3 * 2)

बाह्य दीर्घ elf_aux_hwcap;
#घोषणा ELF_HWCAP (elf_aux_hwcap)

#घोषणा SET_PERSONALITY(ex) करो अणुपूर्ण जबतक(0)

#पूर्ण_अगर
