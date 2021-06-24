<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SPARC64_ELF_H
#घोषणा __ASM_SPARC64_ELF_H

/*
 * ELF रेजिस्टर definitions..
 */

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/adi.h>

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
#घोषणा HWCAP_SPARC_FLUSH       0x00000001
#घोषणा HWCAP_SPARC_STBAR       0x00000002
#घोषणा HWCAP_SPARC_SWAP        0x00000004
#घोषणा HWCAP_SPARC_MULDIV      0x00000008
#घोषणा HWCAP_SPARC_V9		0x00000010
#घोषणा HWCAP_SPARC_ULTRA3	0x00000020
#घोषणा HWCAP_SPARC_BLKINIT	0x00000040
#घोषणा HWCAP_SPARC_N2		0x00000080

/* Solaris compatible AT_HWCAP bits. */
#घोषणा AV_SPARC_MUL32		0x00000100 /* 32x32 multiply is efficient */
#घोषणा AV_SPARC_DIV32		0x00000200 /* 32x32 भागide is efficient */
#घोषणा AV_SPARC_FSMULD		0x00000400 /* 'fsmuld' is efficient */
#घोषणा AV_SPARC_V8PLUS		0x00000800 /* v9 insn available to 32bit */
#घोषणा AV_SPARC_POPC		0x00001000 /* 'popc' is efficient */
#घोषणा AV_SPARC_VIS		0x00002000 /* VIS insns available */
#घोषणा AV_SPARC_VIS2		0x00004000 /* VIS2 insns available */
#घोषणा AV_SPARC_ASI_BLK_INIT	0x00008000 /* block init ASIs available */
#घोषणा AV_SPARC_FMAF		0x00010000 /* fused multiply-add */
#घोषणा AV_SPARC_VIS3		0x00020000 /* VIS3 insns available */
#घोषणा AV_SPARC_HPC		0x00040000 /* HPC insns available */
#घोषणा AV_SPARC_RANDOM		0x00080000 /* 'random' insn available */
#घोषणा AV_SPARC_TRANS		0x00100000 /* transaction insns available */
#घोषणा AV_SPARC_FJFMAU		0x00200000 /* unfused multiply-add */
#घोषणा AV_SPARC_IMA		0x00400000 /* पूर्णांकeger multiply-add */
#घोषणा AV_SPARC_ASI_CACHE_SPARING \
				0x00800000 /* cache sparing ASIs available */
#घोषणा AV_SPARC_PAUSE		0x01000000 /* PAUSE available */
#घोषणा AV_SPARC_CBCOND		0x02000000 /* CBCOND insns available */

/* Solaris decided to क्रमागतerate every single crypto inकाष्ठाion type
 * in the AT_HWCAP bits.  This is wasteful, since अगर crypto is present,
 * you still need to look in the CFR रेजिस्टर to see अगर the opcode is
 * really available.  So we simply advertise only "crypto" support.
 */
#घोषणा HWCAP_SPARC_CRYPTO	0x04000000 /* CRYPTO insns available */
#घोषणा HWCAP_SPARC_ADI		0x08000000 /* ADI available */

#घोषणा CORE_DUMP_USE_REGSET

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_ARCH		EM_SPARCV9
#घोषणा ELF_CLASS		ELFCLASS64
#घोषणा ELF_DATA		ELFDATA2MSB

/* Format of 64-bit elf_gregset_t is:
 * 	G0 --> G7
 * 	O0 --> O7
 * 	L0 --> L7
 * 	I0 --> I7
 *	TSTATE
 *	TPC
 *	TNPC
 *	Y
 */
प्रकार अचिन्हित दीर्घ elf_greg_t;
#घोषणा ELF_NGREG 36
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ	pr_regs[32];
	अचिन्हित दीर्घ	pr_fsr;
	अचिन्हित दीर्घ	pr_gsr;
	अचिन्हित दीर्घ	pr_fprs;
पूर्ण elf_fpregset_t;

/* Format of 32-bit elf_gregset_t is:
 * 	G0 --> G7
 *	O0 --> O7
 *	L0 --> L7
 *	I0 --> I7
 *	PSR, PC, nPC, Y, WIM, TBR
 */
प्रकार अचिन्हित पूर्णांक compat_elf_greg_t;
#घोषणा COMPAT_ELF_NGREG 38
प्रकार compat_elf_greg_t compat_elf_gregset_t[COMPAT_ELF_NGREG];

प्रकार काष्ठा अणु
	जोड़ अणु
		अचिन्हित पूर्णांक	pr_regs[32];
		अचिन्हित दीर्घ	pr_dregs[16];
	पूर्ण pr_fr;
	अचिन्हित पूर्णांक __unused;
	अचिन्हित पूर्णांक	pr_fsr;
	अचिन्हित अक्षर	pr_qcnt;
	अचिन्हित अक्षर	pr_q_entrysize;
	अचिन्हित अक्षर	pr_en;
	अचिन्हित पूर्णांक	pr_q[64];
पूर्ण compat_elf_fpregset_t;

/* UltraSparc extensions.  Still unused, but will be eventually.  */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक pr_type;
	अचिन्हित पूर्णांक pr_align;
	जोड़ अणु
		काष्ठा अणु
			जोड़ अणु
				अचिन्हित पूर्णांक	pr_regs[32];
				अचिन्हित दीर्घ	pr_dregs[16];
				दीर्घ द्विगुन	pr_qregs[8];
			पूर्ण pr_xfr;
		पूर्ण pr_v8p;
		अचिन्हित पूर्णांक	pr_xfsr;
		अचिन्हित पूर्णांक	pr_fprs;
		अचिन्हित पूर्णांक	pr_xg[8];
		अचिन्हित पूर्णांक	pr_xo[8];
		अचिन्हित दीर्घ	pr_tstate;
		अचिन्हित पूर्णांक	pr_filler[8];
	पूर्ण pr_un;
पूर्ण elf_xregset_t;

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x)		((x)->e_machine == ELF_ARCH)
#घोषणा compat_elf_check_arch(x)	((x)->e_machine == EM_SPARC || \
					 (x)->e_machine == EM_SPARC32PLUS)
#घोषणा compat_start_thपढ़ो		start_thपढ़ो32

#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.  */

#घोषणा ELF_ET_DYN_BASE		0x0000010000000000UL
#घोषणा COMPAT_ELF_ET_DYN_BASE	0x0000000070000000UL

बाह्य अचिन्हित दीर्घ sparc64_elf_hwcap;
#घोषणा ELF_HWCAP	sparc64_elf_hwcap

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo.  */

#घोषणा ELF_PLATFORM	(शून्य)

#घोषणा SET_PERSONALITY(ex)				\
करो अणु	अगर ((ex).e_ident[EI_CLASS] == ELFCLASS32)	\
		set_thपढ़ो_flag(TIF_32BIT);		\
	अन्यथा						\
		clear_thपढ़ो_flag(TIF_32BIT);		\
	/* flush_thपढ़ो will update pgd cache */	\
	अगर (personality(current->personality) != PER_LINUX32)	\
		set_personality(PER_LINUX |		\
			(current->personality & (~PER_MASK)));	\
पूर्ण जबतक (0)

बाह्य अचिन्हित पूर्णांक vdso_enabled;

#घोषणा	ARCH_DLINFO							\
करो अणु									\
	बाह्य काष्ठा adi_config adi_state;				\
	अगर (vdso_enabled)						\
		NEW_AUX_ENT(AT_SYSINFO_EHDR,				\
			    (अचिन्हित दीर्घ)current->mm->context.vdso);	\
	NEW_AUX_ENT(AT_ADI_BLKSZ, adi_state.caps.blksz);		\
	NEW_AUX_ENT(AT_ADI_NBITS, adi_state.caps.nbits);		\
	NEW_AUX_ENT(AT_ADI_UEONADI, adi_state.caps.ue_on_adi);		\
पूर्ण जबतक (0)

काष्ठा linux_binprm;

#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES	1
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
					पूर्णांक uses_पूर्णांकerp);
#पूर्ण_अगर /* !(__ASM_SPARC64_ELF_H) */
