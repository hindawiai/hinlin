<शैली गुरु>
/*
 * include/यंत्र-xtensa/elf.h
 *
 * ELF रेजिस्टर definitions
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_ELF_H
#घोषणा _XTENSA_ELF_H

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/coprocessor.h>
#समावेश <linux/elf-em.h>

/* Xtensa processor ELF architecture-magic number */

#घोषणा EM_XTENSA_OLD	0xABC7

/* Xtensa relocations defined by the ABIs */

#घोषणा R_XTENSA_NONE           0
#घोषणा R_XTENSA_32             1
#घोषणा R_XTENSA_RTLD           2
#घोषणा R_XTENSA_GLOB_DAT       3
#घोषणा R_XTENSA_JMP_SLOT       4
#घोषणा R_XTENSA_RELATIVE       5
#घोषणा R_XTENSA_PLT            6
#घोषणा R_XTENSA_OP0            8
#घोषणा R_XTENSA_OP1            9
#घोषणा R_XTENSA_OP2            10
#घोषणा R_XTENSA_ASM_EXPAND	11
#घोषणा R_XTENSA_ASM_SIMPLIFY	12
#घोषणा R_XTENSA_GNU_VTINHERIT	15
#घोषणा R_XTENSA_GNU_VTENTRY	16
#घोषणा R_XTENSA_DIFF8		17
#घोषणा R_XTENSA_DIFF16		18
#घोषणा R_XTENSA_DIFF32		19
#घोषणा R_XTENSA_SLOT0_OP	20
#घोषणा R_XTENSA_SLOT1_OP	21
#घोषणा R_XTENSA_SLOT2_OP	22
#घोषणा R_XTENSA_SLOT3_OP	23
#घोषणा R_XTENSA_SLOT4_OP	24
#घोषणा R_XTENSA_SLOT5_OP	25
#घोषणा R_XTENSA_SLOT6_OP	26
#घोषणा R_XTENSA_SLOT7_OP	27
#घोषणा R_XTENSA_SLOT8_OP	28
#घोषणा R_XTENSA_SLOT9_OP	29
#घोषणा R_XTENSA_SLOT10_OP	30
#घोषणा R_XTENSA_SLOT11_OP	31
#घोषणा R_XTENSA_SLOT12_OP	32
#घोषणा R_XTENSA_SLOT13_OP	33
#घोषणा R_XTENSA_SLOT14_OP	34
#घोषणा R_XTENSA_SLOT0_ALT	35
#घोषणा R_XTENSA_SLOT1_ALT	36
#घोषणा R_XTENSA_SLOT2_ALT	37
#घोषणा R_XTENSA_SLOT3_ALT	38
#घोषणा R_XTENSA_SLOT4_ALT	39
#घोषणा R_XTENSA_SLOT5_ALT	40
#घोषणा R_XTENSA_SLOT6_ALT	41
#घोषणा R_XTENSA_SLOT7_ALT	42
#घोषणा R_XTENSA_SLOT8_ALT	43
#घोषणा R_XTENSA_SLOT9_ALT	44
#घोषणा R_XTENSA_SLOT10_ALT	45
#घोषणा R_XTENSA_SLOT11_ALT	46
#घोषणा R_XTENSA_SLOT12_ALT	47
#घोषणा R_XTENSA_SLOT13_ALT	48
#घोषणा R_XTENSA_SLOT14_ALT	49

/* ELF रेजिस्टर definitions. This is needed क्रम core dump support.  */

प्रकार अचिन्हित दीर्घ elf_greg_t;

प्रकार काष्ठा user_pt_regs xtensa_gregset_t;

#घोषणा ELF_NGREG	(माप(xtensa_gregset_t) / माप(elf_greg_t))

प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

#घोषणा ELF_NFPREG	18

प्रकार अचिन्हित पूर्णांक elf_fpreg_t;
प्रकार elf_fpreg_t elf_fpregset_t[ELF_NFPREG];

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */

#घोषणा elf_check_arch(x) ( ( (x)->e_machine == EM_XTENSA )  || \
			    ( (x)->e_machine == EM_XTENSA_OLD ) )

/*
 * These are used to set parameters in the core dumps.
 */

#अगर_घोषित __XTENSA_EL__
# define ELF_DATA	ELFDATA2LSB
#या_अगर defined(__XTENSA_EB__)
# define ELF_DATA	ELFDATA2MSB
#अन्यथा
# error processor byte order undefined!
#पूर्ण_अगर

#घोषणा ELF_CLASS	ELFCLASS32
#घोषणा ELF_ARCH	EM_XTENSA

#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE
#घोषणा CORE_DUMP_USE_REGSET

/*
 * This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
 * use of this is to invoke "./ld.so someprog" to test out a new version of
 * the loader.  We need to make sure that it is out of the way of the program
 * that it will "exec", and that there is sufficient room क्रम the brk.
 */

#घोषणा ELF_ET_DYN_BASE         (2 * TASK_SIZE / 3)

/*
 * This yields a mask that user programs can use to figure out what
 * inकाष्ठाion set this CPU supports.  This could be करोne in user space,
 * but it's not easy, and we've alपढ़ोy करोne it here.
 */

#घोषणा ELF_HWCAP	(0)

/*
 * This yields a string that ld.so will use to load implementation
 * specअगरic libraries क्रम optimization.  This is more specअगरic in
 * पूर्णांकent than poking at uname or /proc/cpuinfo.
 * For the moment, we have only optimizations क्रम the Intel generations,
 * but that could change...
 */

#घोषणा ELF_PLATFORM  (शून्य)

/*
 * The Xtensa processor ABI says that when the program starts, a2
 * contains a poपूर्णांकer to a function which might be रेजिस्टरed using
 * `निकास_पर'.  This provides a mean क्रम the dynamic linker to call
 * DT_FINI functions क्रम shared libraries that have been loaded beक्रमe
 * the code runs.
 *
 * A value of 0 tells we have no such handler.
 *
 * We might as well make sure everything अन्यथा is cleared too (except
 * क्रम the stack poपूर्णांकer in a1), just to make things more
 * deterministic.  Also, clearing a0 terminates debugger backtraces.
 */

#घोषणा ELF_PLAT_INIT(_r, load_addr) \
	करो अणु _r->areg[0]=0; /*_r->areg[1]=0;*/ _r->areg[2]=0;  _r->areg[3]=0;  \
	     _r->areg[4]=0;  _r->areg[5]=0;    _r->areg[6]=0;  _r->areg[7]=0;  \
	     _r->areg[8]=0;  _r->areg[9]=0;    _r->areg[10]=0; _r->areg[11]=0; \
	     _r->areg[12]=0; _r->areg[13]=0;   _r->areg[14]=0; _r->areg[15]=0; \
	पूर्ण जबतक (0)

प्रकार काष्ठा अणु
	xtregs_opt_t	opt;
	xtregs_user_t	user;
#अगर XTENSA_HAVE_COPROCESSORS
	xtregs_cp0_t	cp0;
	xtregs_cp1_t	cp1;
	xtregs_cp2_t	cp2;
	xtregs_cp3_t	cp3;
	xtregs_cp4_t	cp4;
	xtregs_cp5_t	cp5;
	xtregs_cp6_t	cp6;
	xtregs_cp7_t	cp7;
#पूर्ण_अगर
पूर्ण elf_xtregs_t;

#घोषणा SET_PERSONALITY(ex) \
	set_personality(PER_LINUX_32BIT | (current->personality & (~PER_MASK)))

#पूर्ण_अगर	/* _XTENSA_ELF_H */
