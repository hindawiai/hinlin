<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *
 *  Derived from "include/asm-i386/elf.h"
 */

#अगर_अघोषित __ASMS390_ELF_H
#घोषणा __ASMS390_ELF_H

/* s390 relocations defined by the ABIs */
#घोषणा R_390_NONE		0	/* No reloc.  */
#घोषणा R_390_8			1	/* Direct 8 bit.  */
#घोषणा R_390_12		2	/* Direct 12 bit.  */
#घोषणा R_390_16		3	/* Direct 16 bit.  */
#घोषणा R_390_32		4	/* Direct 32 bit.  */
#घोषणा R_390_PC32		5	/* PC relative 32 bit.	*/
#घोषणा R_390_GOT12		6	/* 12 bit GOT offset.  */
#घोषणा R_390_GOT32		7	/* 32 bit GOT offset.  */
#घोषणा R_390_PLT32		8	/* 32 bit PC relative PLT address.  */
#घोषणा R_390_COPY		9	/* Copy symbol at runसमय.  */
#घोषणा R_390_GLOB_DAT		10	/* Create GOT entry.  */
#घोषणा R_390_JMP_SLOT		11	/* Create PLT entry.  */
#घोषणा R_390_RELATIVE		12	/* Adjust by program base.  */
#घोषणा R_390_GOTOFF32		13	/* 32 bit offset to GOT.	 */
#घोषणा R_390_GOTPC		14	/* 32 bit PC rel. offset to GOT.  */
#घोषणा R_390_GOT16		15	/* 16 bit GOT offset.  */
#घोषणा R_390_PC16		16	/* PC relative 16 bit.	*/
#घोषणा R_390_PC16DBL		17	/* PC relative 16 bit shअगरted by 1.  */
#घोषणा R_390_PLT16DBL		18	/* 16 bit PC rel. PLT shअगरted by 1.  */
#घोषणा R_390_PC32DBL		19	/* PC relative 32 bit shअगरted by 1.  */
#घोषणा R_390_PLT32DBL		20	/* 32 bit PC rel. PLT shअगरted by 1.  */
#घोषणा R_390_GOTPCDBL		21	/* 32 bit PC rel. GOT shअगरted by 1.  */
#घोषणा R_390_64		22	/* Direct 64 bit.  */
#घोषणा R_390_PC64		23	/* PC relative 64 bit.	*/
#घोषणा R_390_GOT64		24	/* 64 bit GOT offset.  */
#घोषणा R_390_PLT64		25	/* 64 bit PC relative PLT address.  */
#घोषणा R_390_GOTENT		26	/* 32 bit PC rel. to GOT entry >> 1. */
#घोषणा R_390_GOTOFF16		27	/* 16 bit offset to GOT. */
#घोषणा R_390_GOTOFF64		28	/* 64 bit offset to GOT. */
#घोषणा R_390_GOTPLT12		29	/* 12 bit offset to jump slot.	*/
#घोषणा R_390_GOTPLT16		30	/* 16 bit offset to jump slot.	*/
#घोषणा R_390_GOTPLT32		31	/* 32 bit offset to jump slot.	*/
#घोषणा R_390_GOTPLT64		32	/* 64 bit offset to jump slot.	*/
#घोषणा R_390_GOTPLTENT		33	/* 32 bit rel. offset to jump slot.  */
#घोषणा R_390_PLTOFF16		34	/* 16 bit offset from GOT to PLT. */
#घोषणा R_390_PLTOFF32		35	/* 32 bit offset from GOT to PLT. */
#घोषणा R_390_PLTOFF64		36	/* 16 bit offset from GOT to PLT. */
#घोषणा R_390_TLS_LOAD		37	/* Tag क्रम load insn in TLS code. */
#घोषणा R_390_TLS_GDCALL	38	/* Tag क्रम function call in general
                                           dynamic TLS code.  */
#घोषणा R_390_TLS_LDCALL	39	/* Tag क्रम function call in local
                                           dynamic TLS code.  */
#घोषणा R_390_TLS_GD32		40	/* Direct 32 bit क्रम general dynamic
                                           thपढ़ो local data.  */
#घोषणा R_390_TLS_GD64		41	/* Direct 64 bit क्रम general dynamic
                                           thपढ़ो local data.  */
#घोषणा R_390_TLS_GOTIE12	42	/* 12 bit GOT offset क्रम अटल TLS
                                           block offset.  */
#घोषणा R_390_TLS_GOTIE32	43	/* 32 bit GOT offset क्रम अटल TLS
                                           block offset.  */
#घोषणा R_390_TLS_GOTIE64	44	/* 64 bit GOT offset क्रम अटल TLS
                                           block offset.  */
#घोषणा R_390_TLS_LDM32		45	/* Direct 32 bit क्रम local dynamic
                                           thपढ़ो local data in LD code.  */
#घोषणा R_390_TLS_LDM64		46	/* Direct 64 bit क्रम local dynamic
                                           thपढ़ो local data in LD code.  */
#घोषणा R_390_TLS_IE32		47	/* 32 bit address of GOT entry क्रम
                                           negated अटल TLS block offset.  */
#घोषणा R_390_TLS_IE64		48	/* 64 bit address of GOT entry क्रम
                                           negated अटल TLS block offset.  */
#घोषणा R_390_TLS_IEENT		49	/* 32 bit rel. offset to GOT entry क्रम
                                           negated अटल TLS block offset.  */
#घोषणा R_390_TLS_LE32		50	/* 32 bit negated offset relative to
                                           अटल TLS block.  */
#घोषणा R_390_TLS_LE64		51	/* 64 bit negated offset relative to
                                           अटल TLS block.  */
#घोषणा R_390_TLS_LDO32		52	/* 32 bit offset relative to TLS
                                           block.  */
#घोषणा R_390_TLS_LDO64		53	/* 64 bit offset relative to TLS
                                           block.  */
#घोषणा R_390_TLS_DTPMOD	54	/* ID of module containing symbol.  */
#घोषणा R_390_TLS_DTPOFF	55	/* Offset in TLS block.  */
#घोषणा R_390_TLS_TPOFF		56	/* Negate offset in अटल TLS
                                           block.  */
#घोषणा R_390_20		57	/* Direct 20 bit.  */
#घोषणा R_390_GOT20		58	/* 20 bit GOT offset.  */
#घोषणा R_390_GOTPLT20		59	/* 20 bit offset to jump slot.  */
#घोषणा R_390_TLS_GOTIE20	60	/* 20 bit GOT offset क्रम अटल TLS
					   block offset.  */
/* Keep this the last entry.  */
#घोषणा R_390_NUM	61

/* Bits present in AT_HWCAP. */
#घोषणा HWCAP_S390_ESAN3	1
#घोषणा HWCAP_S390_ZARCH	2
#घोषणा HWCAP_S390_STFLE	4
#घोषणा HWCAP_S390_MSA		8
#घोषणा HWCAP_S390_LDISP	16
#घोषणा HWCAP_S390_EIMM		32
#घोषणा HWCAP_S390_DFP		64
#घोषणा HWCAP_S390_HPAGE	128
#घोषणा HWCAP_S390_ETF3EH	256
#घोषणा HWCAP_S390_HIGH_GPRS	512
#घोषणा HWCAP_S390_TE		1024
#घोषणा HWCAP_S390_VXRS		2048
#घोषणा HWCAP_S390_VXRS_BCD	4096
#घोषणा HWCAP_S390_VXRS_EXT	8192
#घोषणा HWCAP_S390_GS		16384
#घोषणा HWCAP_S390_VXRS_EXT2	32768
#घोषणा HWCAP_S390_VXRS_PDE	65536
#घोषणा HWCAP_S390_SORT		131072
#घोषणा HWCAP_S390_DFLT		262144

/* Internal bits, not exposed via elf */
#घोषणा HWCAP_INT_SIE		1UL

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS64
#घोषणा ELF_DATA	ELFDATA2MSB
#घोषणा ELF_ARCH	EM_S390

/* s390 specअगरic phdr types */
#घोषणा PT_S390_PGSTE	0x70000000

/*
 * ELF रेजिस्टर definitions..
 */

#समावेश <linux/compat.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/user.h>

प्रकार s390_fp_regs elf_fpregset_t;
प्रकार s390_regs elf_gregset_t;

प्रकार s390_fp_regs compat_elf_fpregset_t;
प्रकार s390_compat_regs compat_elf_gregset_t;

#समावेश <linux/sched/mm.h>	/* क्रम task_काष्ठा */
#समावेश <यंत्र/mmu_context.h>

#समावेश <यंत्र/vdso.h>

बाह्य अचिन्हित पूर्णांक vdso_enabled;

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) \
	(((x)->e_machine == EM_S390 || (x)->e_machine == EM_S390_OLD) \
         && (x)->e_ident[EI_CLASS] == ELF_CLASS) 
#घोषणा compat_elf_check_arch(x) \
	(((x)->e_machine == EM_S390 || (x)->e_machine == EM_S390_OLD) \
	 && (x)->e_ident[EI_CLASS] == ELF_CLASS)
#घोषणा compat_start_thपढ़ो	start_thपढ़ो31

काष्ठा arch_elf_state अणु
	पूर्णांक rc;
पूर्ण;

#घोषणा INIT_ARCH_ELF_STATE अणु .rc = 0 पूर्ण

#घोषणा arch_check_elf(ehdr, पूर्णांकerp, पूर्णांकerp_ehdr, state) (0)
#अगर_घोषित CONFIG_PGSTE
#घोषणा arch_elf_pt_proc(ehdr, phdr, elf, पूर्णांकerp, state)	\
(अणु								\
	काष्ठा arch_elf_state *_state = state;			\
	अगर ((phdr)->p_type == PT_S390_PGSTE &&			\
	    !page_table_allocate_pgste &&			\
	    !test_thपढ़ो_flag(TIF_PGSTE) &&			\
	    !current->mm->context.alloc_pgste) अणु		\
		set_thपढ़ो_flag(TIF_PGSTE);			\
		set_pt_regs_flag(task_pt_regs(current),		\
				 PIF_SYSCALL_RESTART);		\
		_state->rc = -EAGAIN;				\
	पूर्ण							\
	_state->rc;						\
पूर्ण)
#अन्यथा
#घोषणा arch_elf_pt_proc(ehdr, phdr, elf, पूर्णांकerp, state)	\
(अणु								\
	(state)->rc;						\
पूर्ण)
#पूर्ण_अगर

/* For SVR4/S390 the function poपूर्णांकer to be रेजिस्टरed with `निकास_पर` is
   passed in R14. */
#घोषणा ELF_PLAT_INIT(_r, load_addr) \
	करो अणु \
		_r->gprs[14] = 0; \
	पूर्ण जबतक (0)

#घोषणा CORE_DUMP_USE_REGSET
#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk. 64-bit
   tasks are aligned to 4GB. */
#घोषणा ELF_ET_DYN_BASE (is_compat_task() ? \
				(STACK_TOP / 3 * 2) : \
				(STACK_TOP / 3 * 2) & ~((1UL << 32) - 1))

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this CPU supports. */

बाह्य अचिन्हित दीर्घ elf_hwcap;
#घोषणा ELF_HWCAP (elf_hwcap)

/* Internal hardware capabilities, not exposed via elf */

बाह्य अचिन्हित दीर्घ पूर्णांक_hwcap;

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo.

   For the moment, we have only optimizations क्रम the Intel generations,
   but that could change... */

#घोषणा ELF_PLATFORM_SIZE 8
बाह्य अक्षर elf_platक्रमm[];
#घोषणा ELF_PLATFORM (elf_platक्रमm)

#अगर_अघोषित CONFIG_COMPAT
#घोषणा SET_PERSONALITY(ex) \
करो अणु								\
	set_personality(PER_LINUX |				\
		(current->personality & (~PER_MASK)));		\
	current->thपढ़ो.sys_call_table = sys_call_table;	\
पूर्ण जबतक (0)
#अन्यथा /* CONFIG_COMPAT */
#घोषणा SET_PERSONALITY(ex)					\
करो अणु								\
	अगर (personality(current->personality) != PER_LINUX32)	\
		set_personality(PER_LINUX |			\
			(current->personality & ~PER_MASK));	\
	अगर ((ex).e_ident[EI_CLASS] == ELFCLASS32) अणु		\
		set_thपढ़ो_flag(TIF_31BIT);			\
		current->thपढ़ो.sys_call_table =		\
			sys_call_table_emu;			\
	पूर्ण अन्यथा अणु						\
		clear_thपढ़ो_flag(TIF_31BIT);			\
		current->thपढ़ो.sys_call_table =		\
			sys_call_table;				\
	पूर्ण							\
पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_COMPAT */

/*
 * Cache aliasing on the latest machines calls क्रम a mapping granularity
 * of 512KB क्रम the anonymous mapping base. For 64-bit processes use a
 * 512KB alignment and a अक्रमomization of up to 1GB. For 31-bit processes
 * the भव address space is limited, use no alignment and limit the
 * अक्रमomization to 8MB.
 * For the additional अक्रमomization of the program अवरोध use 32MB क्रम
 * 64-bit and 8MB क्रम 31-bit.
 */
#घोषणा BRK_RND_MASK	(is_compat_task() ? 0x7ffUL : 0x1fffUL)
#घोषणा MMAP_RND_MASK	(is_compat_task() ? 0x7ffUL : 0x3ff80UL)
#घोषणा MMAP_ALIGN_MASK	(is_compat_task() ? 0 : 0x7fUL)
#घोषणा STACK_RND_MASK	MMAP_RND_MASK

/* update AT_VECTOR_SIZE_ARCH अगर the number of NEW_AUX_ENT entries changes */
#घोषणा ARCH_DLINFO							    \
करो अणु									    \
	अगर (vdso_enabled)						    \
		NEW_AUX_ENT(AT_SYSINFO_EHDR,				    \
			    (अचिन्हित दीर्घ)current->mm->context.vdso_base); \
पूर्ण जबतक (0)

काष्ठा linux_binprm;

#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES 1
पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *, पूर्णांक);

#पूर्ण_अगर
