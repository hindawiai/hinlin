<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASMPARISC_ELF_H
#घोषणा __ASMPARISC_ELF_H

/*
 * ELF रेजिस्टर definitions..
 */

#समावेश <linux/types.h>

#घोषणा EM_PARISC 15

/* HPPA specअगरic definitions.  */

/* Legal values क्रम e_flags field of Elf32_Ehdr.  */

#घोषणा EF_PARISC_TRAPNIL	0x00010000 /* Trap nil poपूर्णांकer dereference.  */
#घोषणा EF_PARISC_EXT		0x00020000 /* Program uses arch. extensions. */
#घोषणा EF_PARISC_LSB		0x00040000 /* Program expects little endian. */
#घोषणा EF_PARISC_WIDE		0x00080000 /* Program expects wide mode.  */
#घोषणा EF_PARISC_NO_KABP	0x00100000 /* No kernel assisted branch
					      prediction.  */
#घोषणा EF_PARISC_LAZYSWAP	0x00400000 /* Allow lazy swapping.  */
#घोषणा EF_PARISC_ARCH		0x0000ffff /* Architecture version.  */

/* Defined values क्रम `e_flags & EF_PARISC_ARCH' are:  */

#घोषणा EFA_PARISC_1_0		    0x020b /* PA-RISC 1.0 big-endian.  */
#घोषणा EFA_PARISC_1_1		    0x0210 /* PA-RISC 1.1 big-endian.  */
#घोषणा EFA_PARISC_2_0		    0x0214 /* PA-RISC 2.0 big-endian.  */

/* Additional section indices.  */

#घोषणा SHN_PARISC_ANSI_COMMON	0xff00	   /* Section क्रम tenatively declared
					      symbols in ANSI C.  */
#घोषणा SHN_PARISC_HUGE_COMMON	0xff01	   /* Common blocks in huge model.  */

/* Legal values क्रम sh_type field of Elf32_Shdr.  */

#घोषणा SHT_PARISC_EXT		0x70000000 /* Contains product specअगरic ext. */
#घोषणा SHT_PARISC_UNWIND	0x70000001 /* Unwind inक्रमmation.  */
#घोषणा SHT_PARISC_DOC		0x70000002 /* Debug info क्रम optimized code. */

/* Legal values क्रम sh_flags field of Elf32_Shdr.  */

#घोषणा SHF_PARISC_SHORT	0x20000000 /* Section with लघु addressing. */
#घोषणा SHF_PARISC_HUGE		0x40000000 /* Section far from gp.  */
#घोषणा SHF_PARISC_SBP		0x80000000 /* Static branch prediction code. */

/* Legal values क्रम ST_TYPE subfield of st_info (symbol type).  */

#घोषणा STT_PARISC_MILLICODE	13	/* Millicode function entry poपूर्णांक.  */

#घोषणा STT_HP_OPAQUE		(STT_LOOS + 0x1)
#घोषणा STT_HP_STUB		(STT_LOOS + 0x2)

/* HPPA relocs.  */

#घोषणा R_PARISC_NONE		0	/* No reloc.  */
#घोषणा R_PARISC_सूची32		1	/* Direct 32-bit reference.  */
#घोषणा R_PARISC_सूची21L		2	/* Left 21 bits of eff. address.  */
#घोषणा R_PARISC_सूची17R		3	/* Right 17 bits of eff. address.  */
#घोषणा R_PARISC_सूची17F		4	/* 17 bits of eff. address.  */
#घोषणा R_PARISC_सूची14R		6	/* Right 14 bits of eff. address.  */
#घोषणा R_PARISC_PCREL32	9	/* 32-bit rel. address.  */
#घोषणा R_PARISC_PCREL21L	10	/* Left 21 bits of rel. address.  */
#घोषणा R_PARISC_PCREL17R	11	/* Right 17 bits of rel. address.  */
#घोषणा R_PARISC_PCREL17F	12	/* 17 bits of rel. address.  */
#घोषणा R_PARISC_PCREL14R	14	/* Right 14 bits of rel. address.  */
#घोषणा R_PARISC_DPREL21L	18	/* Left 21 bits of rel. address.  */
#घोषणा R_PARISC_DPREL14R	22	/* Right 14 bits of rel. address.  */
#घोषणा R_PARISC_GPREL21L	26	/* GP-relative, left 21 bits.  */
#घोषणा R_PARISC_GPREL14R	30	/* GP-relative, right 14 bits.  */
#घोषणा R_PARISC_LTOFF21L	34	/* LT-relative, left 21 bits.  */
#घोषणा R_PARISC_LTOFF14R	38	/* LT-relative, right 14 bits.  */
#घोषणा R_PARISC_SECREL32	41	/* 32 bits section rel. address.  */
#घोषणा R_PARISC_SEGBASE	48	/* No relocation, set segment base.  */
#घोषणा R_PARISC_SEGREL32	49	/* 32 bits segment rel. address.  */
#घोषणा R_PARISC_PLTOFF21L	50	/* PLT rel. address, left 21 bits.  */
#घोषणा R_PARISC_PLTOFF14R	54	/* PLT rel. address, right 14 bits.  */
#घोषणा R_PARISC_LTOFF_FPTR32	57	/* 32 bits LT-rel. function poपूर्णांकer. */
#घोषणा R_PARISC_LTOFF_FPTR21L	58	/* LT-rel. fct ptr, left 21 bits. */
#घोषणा R_PARISC_LTOFF_FPTR14R	62	/* LT-rel. fct ptr, right 14 bits. */
#घोषणा R_PARISC_FPTR64		64	/* 64 bits function address.  */
#घोषणा R_PARISC_PLABEL32	65	/* 32 bits function address.  */
#घोषणा R_PARISC_PCREL64	72	/* 64 bits PC-rel. address.  */
#घोषणा R_PARISC_PCREL22F	74	/* 22 bits PC-rel. address.  */
#घोषणा R_PARISC_PCREL14WR	75	/* PC-rel. address, right 14 bits.  */
#घोषणा R_PARISC_PCREL14DR	76	/* PC rel. address, right 14 bits.  */
#घोषणा R_PARISC_PCREL16F	77	/* 16 bits PC-rel. address.  */
#घोषणा R_PARISC_PCREL16WF	78	/* 16 bits PC-rel. address.  */
#घोषणा R_PARISC_PCREL16DF	79	/* 16 bits PC-rel. address.  */
#घोषणा R_PARISC_सूची64		80	/* 64 bits of eff. address.  */
#घोषणा R_PARISC_सूची14WR	83	/* 14 bits of eff. address.  */
#घोषणा R_PARISC_सूची14DR	84	/* 14 bits of eff. address.  */
#घोषणा R_PARISC_सूची16F		85	/* 16 bits of eff. address.  */
#घोषणा R_PARISC_सूची16WF	86	/* 16 bits of eff. address.  */
#घोषणा R_PARISC_सूची16DF	87	/* 16 bits of eff. address.  */
#घोषणा R_PARISC_GPREL64	88	/* 64 bits of GP-rel. address.  */
#घोषणा R_PARISC_GPREL14WR	91	/* GP-rel. address, right 14 bits.  */
#घोषणा R_PARISC_GPREL14DR	92	/* GP-rel. address, right 14 bits.  */
#घोषणा R_PARISC_GPREL16F	93	/* 16 bits GP-rel. address.  */
#घोषणा R_PARISC_GPREL16WF	94	/* 16 bits GP-rel. address.  */
#घोषणा R_PARISC_GPREL16DF	95	/* 16 bits GP-rel. address.  */
#घोषणा R_PARISC_LTOFF64	96	/* 64 bits LT-rel. address.  */
#घोषणा R_PARISC_LTOFF14WR	99	/* LT-rel. address, right 14 bits.  */
#घोषणा R_PARISC_LTOFF14DR	100	/* LT-rel. address, right 14 bits.  */
#घोषणा R_PARISC_LTOFF16F	101	/* 16 bits LT-rel. address.  */
#घोषणा R_PARISC_LTOFF16WF	102	/* 16 bits LT-rel. address.  */
#घोषणा R_PARISC_LTOFF16DF	103	/* 16 bits LT-rel. address.  */
#घोषणा R_PARISC_SECREL64	104	/* 64 bits section rel. address.  */
#घोषणा R_PARISC_SEGREL64	112	/* 64 bits segment rel. address.  */
#घोषणा R_PARISC_PLTOFF14WR	115	/* PLT-rel. address, right 14 bits.  */
#घोषणा R_PARISC_PLTOFF14DR	116	/* PLT-rel. address, right 14 bits.  */
#घोषणा R_PARISC_PLTOFF16F	117	/* 16 bits LT-rel. address.  */
#घोषणा R_PARISC_PLTOFF16WF	118	/* 16 bits PLT-rel. address.  */
#घोषणा R_PARISC_PLTOFF16DF	119	/* 16 bits PLT-rel. address.  */
#घोषणा R_PARISC_LTOFF_FPTR64	120	/* 64 bits LT-rel. function ptr.  */
#घोषणा R_PARISC_LTOFF_FPTR14WR	123	/* LT-rel. fct. ptr., right 14 bits. */
#घोषणा R_PARISC_LTOFF_FPTR14DR	124	/* LT-rel. fct. ptr., right 14 bits. */
#घोषणा R_PARISC_LTOFF_FPTR16F	125	/* 16 bits LT-rel. function ptr.  */
#घोषणा R_PARISC_LTOFF_FPTR16WF	126	/* 16 bits LT-rel. function ptr.  */
#घोषणा R_PARISC_LTOFF_FPTR16DF	127	/* 16 bits LT-rel. function ptr.  */
#घोषणा R_PARISC_LORESERVE	128
#घोषणा R_PARISC_COPY		128	/* Copy relocation.  */
#घोषणा R_PARISC_IPLT		129	/* Dynamic reloc, imported PLT */
#घोषणा R_PARISC_EPLT		130	/* Dynamic reloc, exported PLT */
#घोषणा R_PARISC_TPREL32	153	/* 32 bits TP-rel. address.  */
#घोषणा R_PARISC_TPREL21L	154	/* TP-rel. address, left 21 bits.  */
#घोषणा R_PARISC_TPREL14R	158	/* TP-rel. address, right 14 bits.  */
#घोषणा R_PARISC_LTOFF_TP21L	162	/* LT-TP-rel. address, left 21 bits. */
#घोषणा R_PARISC_LTOFF_TP14R	166	/* LT-TP-rel. address, right 14 bits.*/
#घोषणा R_PARISC_LTOFF_TP14F	167	/* 14 bits LT-TP-rel. address.  */
#घोषणा R_PARISC_TPREL64	216	/* 64 bits TP-rel. address.  */
#घोषणा R_PARISC_TPREL14WR	219	/* TP-rel. address, right 14 bits.  */
#घोषणा R_PARISC_TPREL14DR	220	/* TP-rel. address, right 14 bits.  */
#घोषणा R_PARISC_TPREL16F	221	/* 16 bits TP-rel. address.  */
#घोषणा R_PARISC_TPREL16WF	222	/* 16 bits TP-rel. address.  */
#घोषणा R_PARISC_TPREL16DF	223	/* 16 bits TP-rel. address.  */
#घोषणा R_PARISC_LTOFF_TP64	224	/* 64 bits LT-TP-rel. address.  */
#घोषणा R_PARISC_LTOFF_TP14WR	227	/* LT-TP-rel. address, right 14 bits.*/
#घोषणा R_PARISC_LTOFF_TP14DR	228	/* LT-TP-rel. address, right 14 bits.*/
#घोषणा R_PARISC_LTOFF_TP16F	229	/* 16 bits LT-TP-rel. address.  */
#घोषणा R_PARISC_LTOFF_TP16WF	230	/* 16 bits LT-TP-rel. address.  */
#घोषणा R_PARISC_LTOFF_TP16DF	231	/* 16 bits LT-TP-rel. address.  */
#घोषणा R_PARISC_HIRESERVE	255

#घोषणा PA_PLABEL_FDESC		0x02	/* bit set अगर PLABEL poपूर्णांकs to
					 * a function descriptor, not
					 * an address */

/* The following are PA function descriptors 
 *
 * addr:	the असलolute address of the function
 * gp:		either the data poपूर्णांकer (r27) क्रम non-PIC code or
 *		the PLT poपूर्णांकer (r19) क्रम PIC code */

/* Format क्रम the Elf32 Function descriptor */
प्रकार काष्ठा elf32_fdesc अणु
	__u32	addr;
	__u32	gp;
पूर्ण Elf32_Fdesc;

/* Format क्रम the Elf64 Function descriptor */
प्रकार काष्ठा elf64_fdesc अणु
	__u64	dummy[2]; /* FIXME: nothing uses these, why waste
			   * the space */
	__u64	addr;
	__u64	gp;
पूर्ण Elf64_Fdesc;

#अगर_घोषित CONFIG_64BIT
#घोषणा Elf_Fdesc	Elf64_Fdesc
#अन्यथा
#घोषणा Elf_Fdesc	Elf32_Fdesc
#पूर्ण_अगर /*CONFIG_64BIT*/

/* Legal values क्रम p_type field of Elf32_Phdr/Elf64_Phdr.  */

#घोषणा PT_HP_TLS		(PT_LOOS + 0x0)
#घोषणा PT_HP_CORE_NONE		(PT_LOOS + 0x1)
#घोषणा PT_HP_CORE_VERSION	(PT_LOOS + 0x2)
#घोषणा PT_HP_CORE_KERNEL	(PT_LOOS + 0x3)
#घोषणा PT_HP_CORE_COMM		(PT_LOOS + 0x4)
#घोषणा PT_HP_CORE_PROC		(PT_LOOS + 0x5)
#घोषणा PT_HP_CORE_LOADABLE	(PT_LOOS + 0x6)
#घोषणा PT_HP_CORE_STACK	(PT_LOOS + 0x7)
#घोषणा PT_HP_CORE_SHM		(PT_LOOS + 0x8)
#घोषणा PT_HP_CORE_MMF		(PT_LOOS + 0x9)
#घोषणा PT_HP_PARALLEL		(PT_LOOS + 0x10)
#घोषणा PT_HP_FASTBIND		(PT_LOOS + 0x11)
#घोषणा PT_HP_OPT_ANNOT		(PT_LOOS + 0x12)
#घोषणा PT_HP_HSL_ANNOT		(PT_LOOS + 0x13)
#घोषणा PT_HP_STACK		(PT_LOOS + 0x14)

#घोषणा PT_PARISC_ARCHEXT	0x70000000
#घोषणा PT_PARISC_UNWIND	0x70000001

/* Legal values क्रम p_flags field of Elf32_Phdr/Elf64_Phdr.  */

#घोषणा PF_PARISC_SBP		0x08000000

#घोषणा PF_HP_PAGE_SIZE		0x00100000
#घोषणा PF_HP_FAR_SHARED	0x00200000
#घोषणा PF_HP_NEAR_SHARED	0x00400000
#घोषणा PF_HP_CODE		0x01000000
#घोषणा PF_HP_MODIFY		0x02000000
#घोषणा PF_HP_LAZYSWAP		0x04000000
#घोषणा PF_HP_SBP		0x08000000

/*
 * This yields a string that ld.so will use to load implementation
 * specअगरic libraries क्रम optimization.  This is more specअगरic in
 * पूर्णांकent than poking at uname or /proc/cpuinfo.
 */

#घोषणा ELF_PLATFORM  ("PARISC")

/*
 * The following definitions are those क्रम 32-bit ELF binaries on a 32-bit
 * kernel and क्रम 64-bit binaries on a 64-bit kernel.  To run 32-bit binaries
 * on a 64-bit kernel, fs/compat_binfmt_elf.c defines ELF_CLASS and then
 * #समावेशs binfmt_elf.c, which then includes this file.
 */
#अगर_अघोषित ELF_CLASS

#अगर_घोषित CONFIG_64BIT
#घोषणा ELF_CLASS	ELFCLASS64
#अन्यथा
#घोषणा ELF_CLASS	ELFCLASS32
#पूर्ण_अगर

प्रकार अचिन्हित दीर्घ elf_greg_t;

#घोषणा SET_PERSONALITY(ex) \
(अणु	\
	set_personality((current->personality & ~PER_MASK) | PER_LINUX); \
	clear_thपढ़ो_flag(TIF_32BIT); \
	current->thपढ़ो.map_base = DEFAULT_MAP_BASE; \
	current->thपढ़ो.task_size = DEFAULT_TASK_SIZE; \
 पूर्ण)

#पूर्ण_अगर /* ! ELF_CLASS */

#घोषणा COMPAT_SET_PERSONALITY(ex) \
(अणु	\
	अगर ((ex).e_ident[EI_CLASS] == ELFCLASS32) अणु \
		set_thपढ़ो_flag(TIF_32BIT); \
		current->thपढ़ो.map_base = DEFAULT_MAP_BASE32; \
		current->thपढ़ो.task_size = DEFAULT_TASK_SIZE32; \
	पूर्ण अन्यथा clear_thपढ़ो_flag(TIF_32BIT); \
 पूर्ण)

/*
 * Fill in general रेजिस्टरs in a core dump.  This saves pretty
 * much the same रेजिस्टरs as hp-ux, although in a dअगरferent order.
 * Registers marked # below are not currently saved in pt_regs, so
 * we use their current values here.
 *
 * 	gr0..gr31
 * 	sr0..sr7
 * 	iaoq0..iaoq1
 * 	iasq0..iasq1
 * 	cr11 (sar)
 * 	cr19 (iir)
 * 	cr20 (isr)
 * 	cr21 (ior)
 *  #	cr22 (ipsw)
 *  #	cr0 (recovery counter)
 *  #	cr24..cr31 (temporary रेजिस्टरs)
 *  #	cr8,9,12,13 (protection IDs)
 *  #	cr10 (scr/ccr)
 *  #	cr15 (ext पूर्णांक enable mask)
 *
 */

#घोषणा ELF_CORE_COPY_REGS(dst, pt)	\
	स_रखो(dst, 0, माप(dst));	/* करोn't leak any "random" bits */ \
	अणु	पूर्णांक i; \
		क्रम (i = 0; i < 32; i++) dst[i] = pt->gr[i]; \
		क्रम (i = 0; i < 8; i++) dst[32 + i] = pt->sr[i]; \
	पूर्ण \
	dst[40] = pt->iaoq[0]; dst[41] = pt->iaoq[1]; \
	dst[42] = pt->iasq[0]; dst[43] = pt->iasq[1]; \
	dst[44] = pt->sar;   dst[45] = pt->iir; \
	dst[46] = pt->isr;   dst[47] = pt->ior; \
	dst[48] = mfctl(22); dst[49] = mfctl(0); \
	dst[50] = mfctl(24); dst[51] = mfctl(25); \
	dst[52] = mfctl(26); dst[53] = mfctl(27); \
	dst[54] = mfctl(28); dst[55] = mfctl(29); \
	dst[56] = mfctl(30); dst[57] = mfctl(31); \
	dst[58] = mfctl( 8); dst[59] = mfctl( 9); \
	dst[60] = mfctl(12); dst[61] = mfctl(13); \
	dst[62] = mfctl(10); dst[63] = mfctl(15);

#घोषणा CORE_DUMP_USE_REGSET

#घोषणा ELF_NGREG 80	/* We only need 64 at present, but leave space
			   क्रम expansion. */
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

#घोषणा ELF_NFPREG 32
प्रकार द्विगुन elf_fpreg_t;
प्रकार elf_fpreg_t elf_fpregset_t[ELF_NFPREG];

काष्ठा task_काष्ठा;

काष्ठा pt_regs;	/* क्रमward declaration... */


#घोषणा elf_check_arch(x)		\
	((x)->e_machine == EM_PARISC && (x)->e_ident[EI_CLASS] == ELF_CLASS)
#घोषणा compat_elf_check_arch(x)	\
	((x)->e_machine == EM_PARISC && (x)->e_ident[EI_CLASS] == ELFCLASS32)

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_DATA	ELFDATA2MSB
#घोषणा ELF_ARCH	EM_PARISC
#घोषणा ELF_OSABI 	ELFOSABI_LINUX

/* %r23 is set by ld.so to a poपूर्णांकer to a function which might be 
   रेजिस्टरed using निकास_पर.  This provides a means क्रम the dynamic
   linker to call DT_FINI functions क्रम shared libraries that have
   been loaded beक्रमe the code runs.

   So that we can use the same startup file with अटल executables,
   we start programs with a value of 0 to indicate that there is no
   such function.  */
#घोषणा ELF_PLAT_INIT(_r, load_addr)       _r->gr[23] = 0

#घोषणा ELF_EXEC_PAGESIZE	4096

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.

   (2 * TASK_SIZE / 3) turns पूर्णांकo something undefined when run through a
   32 bit preprocessor and in some हालs results in the kernel trying to map
   ld.so to the kernel भव base. Use a sane value instead. /Jes 
  */

#घोषणा ELF_ET_DYN_BASE         (TASK_UNMAPPED_BASE + 0x01000000)

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this CPU supports.  This could be करोne in user space,
   but it's not easy, and we've alपढ़ोy करोne it here.  */

#घोषणा ELF_HWCAP	0

/* Masks क्रम stack and mmap अक्रमomization */
#घोषणा BRK_RND_MASK	(is_32bit_task() ? 0x07ffUL : 0x3ffffUL)
#घोषणा MMAP_RND_MASK	(is_32bit_task() ? 0x1fffUL : 0x3ffffUL)
#घोषणा STACK_RND_MASK	MMAP_RND_MASK

काष्ठा mm_काष्ठा;
बाह्य अचिन्हित दीर्घ arch_अक्रमomize_brk(काष्ठा mm_काष्ठा *);
#घोषणा arch_अक्रमomize_brk arch_अक्रमomize_brk

#पूर्ण_अगर
