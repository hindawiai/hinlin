<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Much of this is taken from binutils and GNU libc ...
 */
#अगर_अघोषित _ASM_ELF_H
#घोषणा _ASM_ELF_H

#समावेश <linux/auxvec.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm_types.h>

#समावेश <uapi/linux/elf.h>

#समावेश <यंत्र/current.h>

/* ELF header e_flags defines. */
/* MIPS architecture level. */
#घोषणा EF_MIPS_ARCH_1		0x00000000	/* -mips1 code.	 */
#घोषणा EF_MIPS_ARCH_2		0x10000000	/* -mips2 code.	 */
#घोषणा EF_MIPS_ARCH_3		0x20000000	/* -mips3 code.	 */
#घोषणा EF_MIPS_ARCH_4		0x30000000	/* -mips4 code.	 */
#घोषणा EF_MIPS_ARCH_5		0x40000000	/* -mips5 code.	 */
#घोषणा EF_MIPS_ARCH_32		0x50000000	/* MIPS32 code.	 */
#घोषणा EF_MIPS_ARCH_64		0x60000000	/* MIPS64 code.	 */
#घोषणा EF_MIPS_ARCH_32R2	0x70000000	/* MIPS32 R2 code.  */
#घोषणा EF_MIPS_ARCH_64R2	0x80000000	/* MIPS64 R2 code.  */

/* The ABI of a file. */
#घोषणा EF_MIPS_ABI_O32		0x00001000	/* O32 ABI.  */
#घोषणा EF_MIPS_ABI_O64		0x00002000	/* O32 extended क्रम 64 bit.  */

#घोषणा PT_MIPS_REGINFO		0x70000000
#घोषणा PT_MIPS_RTPROC		0x70000001
#घोषणा PT_MIPS_OPTIONS		0x70000002
#घोषणा PT_MIPS_ABIFLAGS	0x70000003

/* Flags in the e_flags field of the header */
#घोषणा EF_MIPS_NOREORDER	0x00000001
#घोषणा EF_MIPS_PIC		0x00000002
#घोषणा EF_MIPS_CPIC		0x00000004
#घोषणा EF_MIPS_ABI2		0x00000020
#घोषणा EF_MIPS_OPTIONS_FIRST	0x00000080
#घोषणा EF_MIPS_32BITMODE	0x00000100
#घोषणा EF_MIPS_FP64		0x00000200
#घोषणा EF_MIPS_न_अंक2008		0x00000400
#घोषणा EF_MIPS_ABI		0x0000f000
#घोषणा EF_MIPS_ARCH		0xf0000000

#घोषणा DT_MIPS_RLD_VERSION	0x70000001
#घोषणा DT_MIPS_TIME_STAMP	0x70000002
#घोषणा DT_MIPS_ICHECKSUM	0x70000003
#घोषणा DT_MIPS_IVERSION	0x70000004
#घोषणा DT_MIPS_FLAGS		0x70000005
	#घोषणा RHF_NONE	0x00000000
	#घोषणा RHF_HARDWAY	0x00000001
	#घोषणा RHF_NOTPOT	0x00000002
	#घोषणा RHF_SGI_ONLY	0x00000010
#घोषणा DT_MIPS_BASE_ADDRESS	0x70000006
#घोषणा DT_MIPS_CONFLICT	0x70000008
#घोषणा DT_MIPS_LIBLIST		0x70000009
#घोषणा DT_MIPS_LOCAL_GOTNO	0x7000000a
#घोषणा DT_MIPS_CONFLICTNO	0x7000000b
#घोषणा DT_MIPS_LIBLISTNO	0x70000010
#घोषणा DT_MIPS_SYMTABNO	0x70000011
#घोषणा DT_MIPS_UNREFEXTNO	0x70000012
#घोषणा DT_MIPS_GOTSYM		0x70000013
#घोषणा DT_MIPS_HIPAGENO	0x70000014
#घोषणा DT_MIPS_RLD_MAP		0x70000016

#घोषणा R_MIPS_NONE		0
#घोषणा R_MIPS_16		1
#घोषणा R_MIPS_32		2
#घोषणा R_MIPS_REL32		3
#घोषणा R_MIPS_26		4
#घोषणा R_MIPS_HI16		5
#घोषणा R_MIPS_LO16		6
#घोषणा R_MIPS_GPREL16		7
#घोषणा R_MIPS_LITERAL		8
#घोषणा R_MIPS_GOT16		9
#घोषणा R_MIPS_PC16		10
#घोषणा R_MIPS_CALL16		11
#घोषणा R_MIPS_GPREL32		12
/* The reमुख्यing relocs are defined on Irix, although they are not
   in the MIPS ELF ABI.	 */
#घोषणा R_MIPS_UNUSED1		13
#घोषणा R_MIPS_UNUSED2		14
#घोषणा R_MIPS_UNUSED3		15
#घोषणा R_MIPS_SHIFT5		16
#घोषणा R_MIPS_SHIFT6		17
#घोषणा R_MIPS_64		18
#घोषणा R_MIPS_GOT_DISP		19
#घोषणा R_MIPS_GOT_PAGE		20
#घोषणा R_MIPS_GOT_OFST		21
/*
 * The following two relocation types are specअगरied in the MIPS ABI
 * conक्रमmance guide version 1.2 but not yet in the psABI.
 */
#घोषणा R_MIPS_GOTHI16		22
#घोषणा R_MIPS_GOTLO16		23
#घोषणा R_MIPS_SUB		24
#घोषणा R_MIPS_INSERT_A		25
#घोषणा R_MIPS_INSERT_B		26
#घोषणा R_MIPS_DELETE		27
#घोषणा R_MIPS_HIGHER		28
#घोषणा R_MIPS_HIGHEST		29
/*
 * The following two relocation types are specअगरied in the MIPS ABI
 * conक्रमmance guide version 1.2 but not yet in the psABI.
 */
#घोषणा R_MIPS_CALLHI16		30
#घोषणा R_MIPS_CALLLO16		31
/*
 * Introduced क्रम MIPSr6.
 */
#घोषणा R_MIPS_PC21_S2		60
#घोषणा R_MIPS_PC26_S2		61
/*
 * This range is reserved क्रम venकरोr specअगरic relocations.
 */
#घोषणा R_MIPS_LOVENDOR		100
#घोषणा R_MIPS_HIVENDOR		127

#घोषणा SHN_MIPS_ACCOMON	0xff00		/* Allocated common symbols */
#घोषणा SHN_MIPS_TEXT		0xff01		/* Allocated test symbols.  */
#घोषणा SHN_MIPS_DATA		0xff02		/* Allocated data symbols.  */
#घोषणा SHN_MIPS_SCOMMON	0xff03		/* Small common symbols */
#घोषणा SHN_MIPS_SUNDEFINED	0xff04		/* Small undefined symbols */

#घोषणा SHT_MIPS_LIST		0x70000000
#घोषणा SHT_MIPS_CONFLICT	0x70000002
#घोषणा SHT_MIPS_GPTAB		0x70000003
#घोषणा SHT_MIPS_UCODE		0x70000004
#घोषणा SHT_MIPS_DEBUG		0x70000005
#घोषणा SHT_MIPS_REGINFO	0x70000006
#घोषणा SHT_MIPS_PACKAGE	0x70000007
#घोषणा SHT_MIPS_PACKSYM	0x70000008
#घोषणा SHT_MIPS_RELD		0x70000009
#घोषणा SHT_MIPS_IFACE		0x7000000b
#घोषणा SHT_MIPS_CONTENT	0x7000000c
#घोषणा SHT_MIPS_OPTIONS	0x7000000d
#घोषणा SHT_MIPS_SHDR		0x70000010
#घोषणा SHT_MIPS_FDESC		0x70000011
#घोषणा SHT_MIPS_EXTSYM		0x70000012
#घोषणा SHT_MIPS_DENSE		0x70000013
#घोषणा SHT_MIPS_PDESC		0x70000014
#घोषणा SHT_MIPS_LOCSYM		0x70000015
#घोषणा SHT_MIPS_AUXSYM		0x70000016
#घोषणा SHT_MIPS_OPTSYM		0x70000017
#घोषणा SHT_MIPS_LOCSTR		0x70000018
#घोषणा SHT_MIPS_LINE		0x70000019
#घोषणा SHT_MIPS_RFDESC		0x7000001a
#घोषणा SHT_MIPS_DELTASYM	0x7000001b
#घोषणा SHT_MIPS_DELTAINST	0x7000001c
#घोषणा SHT_MIPS_DELTACLASS	0x7000001d
#घोषणा SHT_MIPS_DWARF		0x7000001e
#घोषणा SHT_MIPS_DELTADECL	0x7000001f
#घोषणा SHT_MIPS_SYMBOL_LIB	0x70000020
#घोषणा SHT_MIPS_EVENTS		0x70000021
#घोषणा SHT_MIPS_TRANSLATE	0x70000022
#घोषणा SHT_MIPS_PIXIE		0x70000023
#घोषणा SHT_MIPS_XLATE		0x70000024
#घोषणा SHT_MIPS_XLATE_DEBUG	0x70000025
#घोषणा SHT_MIPS_WHIRL		0x70000026
#घोषणा SHT_MIPS_EH_REGION	0x70000027
#घोषणा SHT_MIPS_XLATE_OLD	0x70000028
#घोषणा SHT_MIPS_PDR_EXCEPTION	0x70000029

#घोषणा SHF_MIPS_GPREL		0x10000000
#घोषणा SHF_MIPS_MERGE		0x20000000
#घोषणा SHF_MIPS_ADDR		0x40000000
#घोषणा SHF_MIPS_STRING		0x80000000
#घोषणा SHF_MIPS_NOSTRIP	0x08000000
#घोषणा SHF_MIPS_LOCAL		0x04000000
#घोषणा SHF_MIPS_NAMES		0x02000000
#घोषणा SHF_MIPS_NODUPES	0x01000000

#घोषणा MIPS_ABI_FP_ANY		0	/* FP ABI करोesn't matter */
#घोषणा MIPS_ABI_FP_DOUBLE	1	/* -mद्विगुन-भग्न */
#घोषणा MIPS_ABI_FP_SINGLE	2	/* -msingle-भग्न */
#घोषणा MIPS_ABI_FP_SOFT	3	/* -msoft-भग्न */
#घोषणा MIPS_ABI_FP_OLD_64	4	/* -mips32r2 -mfp64 */
#घोषणा MIPS_ABI_FP_XX		5	/* -mfpxx */
#घोषणा MIPS_ABI_FP_64		6	/* -mips32r2 -mfp64 */
#घोषणा MIPS_ABI_FP_64A		7	/* -mips32r2 -mfp64 -mno-odd-spreg */

काष्ठा mips_elf_abअगरlags_v0 अणु
	uपूर्णांक16_t version;	/* Version of flags काष्ठाure */
	uपूर्णांक8_t isa_level;	/* The level of the ISA: 1-5, 32, 64 */
	uपूर्णांक8_t isa_rev;	/* The revision of ISA: 0 क्रम MIPS V and below,
				   1-n otherwise */
	uपूर्णांक8_t gpr_size;	/* The size of general purpose रेजिस्टरs */
	uपूर्णांक8_t cpr1_size;	/* The size of co-processor 1 रेजिस्टरs */
	uपूर्णांक8_t cpr2_size;	/* The size of co-processor 2 रेजिस्टरs */
	uपूर्णांक8_t fp_abi;		/* The भग्नing-poपूर्णांक ABI */
	uपूर्णांक32_t isa_ext;	/* Mask of processor-specअगरic extensions */
	uपूर्णांक32_t ases;		/* Mask of ASEs used */
	uपूर्णांक32_t flags1;	/* Mask of general flags */
	uपूर्णांक32_t flags2;
पूर्ण;

/* ELF रेजिस्टर definitions */
#घोषणा ELF_NGREG	45
#घोषणा ELF_NFPREG	33

प्रकार अचिन्हित दीर्घ elf_greg_t;
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार द्विगुन elf_fpreg_t;
प्रकार elf_fpreg_t elf_fpregset_t[ELF_NFPREG];

व्योम mips_dump_regs32(u32 *uregs, स्थिर काष्ठा pt_regs *regs);
व्योम mips_dump_regs64(u64 *uregs, स्थिर काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_32BIT
/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch elf32_check_arch

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS32

#घोषणा ELF_CORE_COPY_REGS(dest, regs) \
	mips_dump_regs32((u32 *)&(dest), (regs));

#पूर्ण_अगर /* CONFIG_32BIT */

#अगर_घोषित CONFIG_64BIT
/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch elf64_check_arch
#घोषणा compat_elf_check_arch elf32_check_arch

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS64

#घोषणा ELF_CORE_COPY_REGS(dest, regs) \
	mips_dump_regs64((u64 *)&(dest), (regs));

#पूर्ण_अगर /* CONFIG_64BIT */

/*
 * These are used to set parameters in the core dumps.
 */
#अगर_घोषित __MIPSEB__
#घोषणा ELF_DATA	ELFDATA2MSB
#या_अगर defined(__MIPSEL__)
#घोषणा ELF_DATA	ELFDATA2LSB
#पूर्ण_अगर
#घोषणा ELF_ARCH	EM_MIPS

/*
 * In order to be sure that we करोn't attempt to execute an O32 binary which
 * requires 64 bit FP (FR=1) on a प्रणाली which करोes not support it we refuse
 * to execute any binary which has bits specअगरied by the following macro set
 * in its ELF header flags.
 */
#अगर_घोषित CONFIG_MIPS_O32_FP64_SUPPORT
# define __MIPS_O32_FP64_MUST_BE_ZERO	0
#अन्यथा
# define __MIPS_O32_FP64_MUST_BE_ZERO	EF_MIPS_FP64
#पूर्ण_अगर

#घोषणा mips_elf_check_machine(x) ((x)->e_machine == EM_MIPS)

#घोषणा vmcore_elf32_check_arch mips_elf_check_machine
#घोषणा vmcore_elf64_check_arch mips_elf_check_machine

/*
 * Return non-zero अगर HDR identअगरies an o32 or n32 ELF binary.
 */
#घोषणा elf32_check_arch(hdr)						\
(अणु									\
	पूर्णांक __res = 1;							\
	काष्ठा elfhdr *__h = (hdr);					\
									\
	अगर (!mips_elf_check_machine(__h))				\
		__res = 0;						\
	अगर (__h->e_ident[EI_CLASS] != ELFCLASS32)			\
		__res = 0;						\
	अगर ((__h->e_flags & EF_MIPS_ABI2) != 0) अणु			\
		अगर (!IS_ENABLED(CONFIG_MIPS32_N32) ||			\
		     (__h->e_flags & EF_MIPS_ABI))			\
			__res = 0;					\
	पूर्ण अन्यथा अणु							\
		अगर (IS_ENABLED(CONFIG_64BIT) && !IS_ENABLED(CONFIG_MIPS32_O32)) \
			__res = 0;					\
		अगर (((__h->e_flags & EF_MIPS_ABI) != 0) &&		\
		    ((__h->e_flags & EF_MIPS_ABI) != EF_MIPS_ABI_O32))	\
			__res = 0;					\
		अगर (__h->e_flags & __MIPS_O32_FP64_MUST_BE_ZERO)	\
			__res = 0;					\
	पूर्ण								\
	__res;								\
पूर्ण)

/*
 * Return non-zero अगर HDR identअगरies an n64 ELF binary.
 */
#घोषणा elf64_check_arch(hdr)						\
(अणु									\
	पूर्णांक __res = 1;							\
	काष्ठा elfhdr *__h = (hdr);					\
									\
	अगर (!mips_elf_check_machine(__h))				\
		__res = 0;						\
	अगर (__h->e_ident[EI_CLASS] != ELFCLASS64)			\
		__res = 0;						\
									\
	__res;								\
पूर्ण)

काष्ठा mips_abi;

बाह्य काष्ठा mips_abi mips_abi;
बाह्य काष्ठा mips_abi mips_abi_32;
बाह्य काष्ठा mips_abi mips_abi_n32;

#अगर_घोषित CONFIG_32BIT

#घोषणा SET_PERSONALITY2(ex, state)					\
करो अणु									\
	clear_thपढ़ो_flag(TIF_HYBRID_FPREGS);				\
	set_thपढ़ो_flag(TIF_32BIT_FPREGS);				\
									\
	current->thपढ़ो.abi = &mips_abi;				\
									\
	mips_set_personality_fp(state);					\
	mips_set_personality_nan(state);				\
									\
	अगर (personality(current->personality) != PER_LINUX)		\
		set_personality(PER_LINUX);				\
पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_32BIT */

#अगर_घोषित CONFIG_64BIT

#अगर_घोषित CONFIG_MIPS32_N32
#घोषणा __SET_PERSONALITY32_N32()					\
	करो अणु								\
		set_thपढ़ो_flag(TIF_32BIT_ADDR);			\
									\
		current->thपढ़ो.abi = &mips_abi_n32;			\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा __SET_PERSONALITY32_N32()					\
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MIPS32_O32
#घोषणा __SET_PERSONALITY32_O32(ex, state)				\
	करो अणु								\
		set_thपढ़ो_flag(TIF_32BIT_REGS);			\
		set_thपढ़ो_flag(TIF_32BIT_ADDR);			\
		clear_thपढ़ो_flag(TIF_HYBRID_FPREGS);			\
		set_thपढ़ो_flag(TIF_32BIT_FPREGS);			\
									\
		current->thपढ़ो.abi = &mips_abi_32;			\
									\
		mips_set_personality_fp(state);				\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा __SET_PERSONALITY32_O32(ex, state)				\
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MIPS32_COMPAT
#घोषणा __SET_PERSONALITY32(ex, state)					\
करो अणु									\
	अगर ((((ex).e_flags & EF_MIPS_ABI2) != 0) &&			\
	     ((ex).e_flags & EF_MIPS_ABI) == 0)				\
		__SET_PERSONALITY32_N32();				\
	अन्यथा								\
		__SET_PERSONALITY32_O32(ex, state);			\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा __SET_PERSONALITY32(ex, state) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा SET_PERSONALITY2(ex, state)					\
करो अणु									\
	अचिन्हित पूर्णांक p;							\
									\
	clear_thपढ़ो_flag(TIF_32BIT_REGS);				\
	clear_thपढ़ो_flag(TIF_32BIT_FPREGS);				\
	clear_thपढ़ो_flag(TIF_HYBRID_FPREGS);				\
	clear_thपढ़ो_flag(TIF_32BIT_ADDR);				\
	current->personality &= ~READ_IMPLIES_EXEC;			\
									\
	अगर ((ex).e_ident[EI_CLASS] == ELFCLASS32)			\
		__SET_PERSONALITY32(ex, state);				\
	अन्यथा								\
		current->thपढ़ो.abi = &mips_abi;			\
									\
	mips_set_personality_nan(state);				\
									\
	p = personality(current->personality);				\
	अगर (p != PER_LINUX32 && p != PER_LINUX)				\
		set_personality(PER_LINUX);				\
पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_64BIT */

#घोषणा CORE_DUMP_USE_REGSET
#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this cpu supports.  This could be करोne in userspace,
   but it's not easy, and we've alपढ़ोy करोne it here.  */

#घोषणा ELF_HWCAP	(elf_hwcap)
बाह्य अचिन्हित पूर्णांक elf_hwcap;
#समावेश <यंत्र/hwcap.h>

/*
 * This yields a string that ld.so will use to load implementation
 * specअगरic libraries क्रम optimization.	 This is more specअगरic in
 * पूर्णांकent than poking at uname or /proc/cpuinfo.
 */

#घोषणा ELF_PLATFORM  __elf_platक्रमm
बाह्य स्थिर अक्षर *__elf_platक्रमm;

#घोषणा ELF_BASE_PLATFORM  __elf_base_platक्रमm
बाह्य स्थिर अक्षर *__elf_base_platक्रमm;

/*
 * See comments in यंत्र-alpha/elf.h, this is the same thing
 * on the MIPS.
 */
#घोषणा ELF_PLAT_INIT(_r, load_addr)	करो अणु \
	_r->regs[1] = _r->regs[2] = _r->regs[3] = _r->regs[4] = 0;	\
	_r->regs[5] = _r->regs[6] = _r->regs[7] = _r->regs[8] = 0;	\
	_r->regs[9] = _r->regs[10] = _r->regs[11] = _r->regs[12] = 0;	\
	_r->regs[13] = _r->regs[14] = _r->regs[15] = _r->regs[16] = 0;	\
	_r->regs[17] = _r->regs[18] = _r->regs[19] = _r->regs[20] = 0;	\
	_r->regs[21] = _r->regs[22] = _r->regs[23] = _r->regs[24] = 0;	\
	_r->regs[25] = _r->regs[26] = _r->regs[27] = _r->regs[28] = 0;	\
	_r->regs[30] = _r->regs[31] = 0;				\
पूर्ण जबतक (0)

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.	We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.	*/

#घोषणा ELF_ET_DYN_BASE		(TASK_SIZE / 3 * 2)

/* update AT_VECTOR_SIZE_ARCH अगर the number of NEW_AUX_ENT entries changes */
#घोषणा ARCH_DLINFO							\
करो अणु									\
	NEW_AUX_ENT(AT_SYSINFO_EHDR,					\
		    (अचिन्हित दीर्घ)current->mm->context.vdso);		\
पूर्ण जबतक (0)

#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES 1
काष्ठा linux_binprm;
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
				       पूर्णांक uses_पूर्णांकerp);

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT

काष्ठा arch_elf_state अणु
	पूर्णांक nan_2008;
	पूर्णांक fp_abi;
	पूर्णांक पूर्णांकerp_fp_abi;
	पूर्णांक overall_fp_mode;
पूर्ण;

#घोषणा MIPS_ABI_FP_UNKNOWN	(-1)	/* Unknown FP ABI (kernel पूर्णांकernal) */

#घोषणा INIT_ARCH_ELF_STATE अणु			\
	.nan_2008 = -1,				\
	.fp_abi = MIPS_ABI_FP_UNKNOWN,		\
	.पूर्णांकerp_fp_abi = MIPS_ABI_FP_UNKNOWN,	\
	.overall_fp_mode = -1,			\
पूर्ण

बाह्य पूर्णांक arch_elf_pt_proc(व्योम *ehdr, व्योम *phdr, काष्ठा file *elf,
			    bool is_पूर्णांकerp, काष्ठा arch_elf_state *state);

बाह्य पूर्णांक arch_check_elf(व्योम *ehdr, bool has_पूर्णांकerpreter, व्योम *पूर्णांकerp_ehdr,
			  काष्ठा arch_elf_state *state);

/* Whether to accept legacy-NaN and 2008-NaN user binaries.  */
बाह्य bool mips_use_nan_legacy;
बाह्य bool mips_use_nan_2008;

बाह्य व्योम mips_set_personality_nan(काष्ठा arch_elf_state *state);
बाह्य व्योम mips_set_personality_fp(काष्ठा arch_elf_state *state);

#अन्यथा /* !CONFIG_MIPS_FP_SUPPORT */

काष्ठा arch_elf_state;

अटल अंतरभूत व्योम mips_set_personality_nan(काष्ठा arch_elf_state *state)
अणु
	/* no-op */
पूर्ण

अटल अंतरभूत व्योम mips_set_personality_fp(काष्ठा arch_elf_state *state)
अणु
	/* no-op */
पूर्ण

#पूर्ण_अगर /* !CONFIG_MIPS_FP_SUPPORT */

#घोषणा elf_पढ़ो_implies_exec(ex, stk) mips_elf_पढ़ो_implies_exec(&(ex), stk)
बाह्य पूर्णांक mips_elf_पढ़ो_implies_exec(व्योम *elf_ex, पूर्णांक exstack);

#पूर्ण_अगर /* _ASM_ELF_H */
