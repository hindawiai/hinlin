<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASMSPARC_ELF_H
#घोषणा __ASMSPARC_ELF_H

/*
 * ELF रेजिस्टर definitions..
 */

#समावेश <यंत्र/ptrace.h>

/*
 * Sparc section types
 */
#घोषणा STT_REGISTER		13

/*
 * Sparc ELF relocation types
 */
#घोषणा	R_SPARC_NONE		0
#घोषणा	R_SPARC_8		1
#घोषणा	R_SPARC_16		2
#घोषणा	R_SPARC_32		3
#घोषणा	R_SPARC_DISP8		4
#घोषणा	R_SPARC_DISP16		5
#घोषणा	R_SPARC_DISP32		6
#घोषणा	R_SPARC_WDISP30		7
#घोषणा	R_SPARC_WDISP22		8
#घोषणा	R_SPARC_HI22		9
#घोषणा	R_SPARC_22		10
#घोषणा	R_SPARC_13		11
#घोषणा	R_SPARC_LO10		12
#घोषणा	R_SPARC_GOT10		13
#घोषणा	R_SPARC_GOT13		14
#घोषणा	R_SPARC_GOT22		15
#घोषणा	R_SPARC_PC10		16
#घोषणा	R_SPARC_PC22		17
#घोषणा	R_SPARC_WPLT30		18
#घोषणा	R_SPARC_COPY		19
#घोषणा	R_SPARC_GLOB_DAT	20
#घोषणा	R_SPARC_JMP_SLOT	21
#घोषणा	R_SPARC_RELATIVE	22
#घोषणा	R_SPARC_UA32		23
#घोषणा R_SPARC_PLT32		24
#घोषणा R_SPARC_HIPLT22		25
#घोषणा R_SPARC_LOPLT10		26
#घोषणा R_SPARC_PCPLT32		27
#घोषणा R_SPARC_PCPLT22		28
#घोषणा R_SPARC_PCPLT10		29
#घोषणा R_SPARC_10		30
#घोषणा R_SPARC_11		31
#घोषणा R_SPARC_64		32
#घोषणा R_SPARC_OLO10		33
#घोषणा R_SPARC_WDISP16		40
#घोषणा R_SPARC_WDISP19		41
#घोषणा R_SPARC_7		43
#घोषणा R_SPARC_5		44
#घोषणा R_SPARC_6		45

/* Bits present in AT_HWCAP, primarily क्रम Sparc32.  */

#घोषणा HWCAP_SPARC_FLUSH       1    /* CPU supports flush inकाष्ठाion. */
#घोषणा HWCAP_SPARC_STBAR       2
#घोषणा HWCAP_SPARC_SWAP        4
#घोषणा HWCAP_SPARC_MULDIV      8
#घोषणा HWCAP_SPARC_V9		16
#घोषणा HWCAP_SPARC_ULTRA3	32

#घोषणा CORE_DUMP_USE_REGSET

/* Format is:
 * 	G0 --> G7
 *	O0 --> O7
 *	L0 --> L7
 *	I0 --> I7
 *	PSR, PC, nPC, Y, WIM, TBR
 */
प्रकार अचिन्हित दीर्घ elf_greg_t;
#घोषणा ELF_NGREG 38
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार काष्ठा अणु
	जोड़ अणु
		अचिन्हित दीर्घ	pr_regs[32];
		द्विगुन		pr_dregs[16];
	पूर्ण pr_fr;
	अचिन्हित दीर्घ __unused;
	अचिन्हित दीर्घ	pr_fsr;
	अचिन्हित अक्षर	pr_qcnt;
	अचिन्हित अक्षर	pr_q_entrysize;
	अचिन्हित अक्षर	pr_en;
	अचिन्हित पूर्णांक	pr_q[64];
पूर्ण elf_fpregset_t;

#समावेश <यंत्र/mbus.h>

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) ((x)->e_machine == EM_SPARC)

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_ARCH	EM_SPARC
#घोषणा ELF_CLASS	ELFCLASS32
#घोषणा ELF_DATA	ELFDATA2MSB

#घोषणा ELF_EXEC_PAGESIZE	4096


/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.  */

#घोषणा ELF_ET_DYN_BASE         (TASK_UNMAPPED_BASE)

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this cpu supports.  This can NOT be करोne in userspace
   on Sparc.  */

/* Most sun4m's have them all.  */
#घोषणा ELF_HWCAP	(HWCAP_SPARC_FLUSH | HWCAP_SPARC_STBAR | \
			 HWCAP_SPARC_SWAP | HWCAP_SPARC_MULDIV)

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo. */

#घोषणा ELF_PLATFORM	(शून्य)

#पूर्ण_अगर /* !(__ASMSPARC_ELF_H) */
