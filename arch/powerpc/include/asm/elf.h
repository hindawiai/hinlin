<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ELF रेजिस्टर definitions..
 */
#अगर_अघोषित _ASM_POWERPC_ELF_H
#घोषणा _ASM_POWERPC_ELF_H

#समावेश <linux/sched.h>	/* क्रम task_काष्ठा */
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/माला.स>
#समावेश <uapi/यंत्र/elf.h>

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) ((x)->e_machine == ELF_ARCH)
#घोषणा compat_elf_check_arch(x)	((x)->e_machine == EM_PPC)

#घोषणा CORE_DUMP_USE_REGSET
#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE

/*
 * This is the base location क्रम PIE (ET_DYN with INTERP) loads. On
 * 64-bit, this is उठाओd to 4GB to leave the entire 32-bit address
 * space खोलो क्रम things that want to use the area क्रम 32-bit poपूर्णांकers.
 */
#घोषणा ELF_ET_DYN_BASE		(is_32bit_task() ? 0x000400000UL : \
						   0x100000000UL)

#घोषणा ELF_CORE_EFLAGS (is_elf2_task() ? 2 : 0)

/*
 * Our रेजिस्टरs are always अचिन्हित दीर्घs, whether we're a 32 bit
 * process or 64 bit, on either a 64 bit or 32 bit kernel.
 *
 * This macro relies on elf_regs[i] having the right type to truncate to,
 * either u32 or u64.  It defines the body of the elf_core_copy_regs
 * function, either the native one with elf_gregset_t elf_regs or
 * the 32-bit one with elf_gregset_t32 elf_regs.
 */
#घोषणा PPC_ELF_CORE_COPY_REGS(elf_regs, regs) \
	पूर्णांक i, nregs = min(माप(*regs) / माप(अचिन्हित दीर्घ), \
			   (माप_प्रकार)ELF_NGREG);			  \
	क्रम (i = 0; i < nregs; i++) \
		elf_regs[i] = ((अचिन्हित दीर्घ *) regs)[i]; \
	स_रखो(&elf_regs[i], 0, (ELF_NGREG - i) * माप(elf_regs[0]))

/* Common routine क्रम both 32-bit and 64-bit native processes */
अटल अंतरभूत व्योम ppc_elf_core_copy_regs(elf_gregset_t elf_regs,
					  काष्ठा pt_regs *regs)
अणु
	PPC_ELF_CORE_COPY_REGS(elf_regs, regs);
पूर्ण
#घोषणा ELF_CORE_COPY_REGS(gregs, regs) ppc_elf_core_copy_regs(gregs, regs);

/* ELF_HWCAP yields a mask that user programs can use to figure out what
   inकाष्ठाion set this cpu supports.  This could be करोne in userspace,
   but it's not easy, and we've alपढ़ोy करोne it here.  */
# define ELF_HWCAP	(cur_cpu_spec->cpu_user_features)
# define ELF_HWCAP2	(cur_cpu_spec->cpu_user_features2)

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo.  */

#घोषणा ELF_PLATFORM	(cur_cpu_spec->platक्रमm)

/* While ELF_PLATFORM indicates the ISA supported by the platक्रमm, it
 * may not accurately reflect the underlying behavior of the hardware
 * (as in the हाल of running in Power5+ compatibility mode on a
 * Power6 machine).  ELF_BASE_PLATFORM allows ld.so to load libraries
 * that are tuned क्रम the real hardware.
 */
#घोषणा ELF_BASE_PLATFORM (घातerpc_base_platक्रमm)

#अगर_घोषित __घातerpc64__
# define ELF_PLAT_INIT(_r, load_addr)	करो अणु	\
	_r->gpr[2] = load_addr; 		\
पूर्ण जबतक (0)
#पूर्ण_अगर /* __घातerpc64__ */

#अगर_घोषित __घातerpc64__
# define SET_PERSONALITY(ex)					\
करो अणु								\
	अगर (((ex).e_flags & 0x3) == 2)				\
		set_thपढ़ो_flag(TIF_ELF2ABI);			\
	अन्यथा							\
		clear_thपढ़ो_flag(TIF_ELF2ABI);			\
	अगर ((ex).e_ident[EI_CLASS] == ELFCLASS32)		\
		set_thपढ़ो_flag(TIF_32BIT);			\
	अन्यथा							\
		clear_thपढ़ो_flag(TIF_32BIT);			\
	अगर (personality(current->personality) != PER_LINUX32)	\
		set_personality(PER_LINUX |			\
			(current->personality & (~PER_MASK)));	\
पूर्ण जबतक (0)
/*
 * An executable क्रम which elf_पढ़ो_implies_exec() वापसs TRUE will
 * have the READ_IMPLIES_EXEC personality flag set स्वतःmatically. This
 * is only required to work around bugs in old 32bit toolchains. Since
 * the 64bit ABI has never had these issues करोnt enable the workaround
 * even अगर we have an executable stack.
 */
# define elf_पढ़ो_implies_exec(ex, exec_stk) (is_32bit_task() ? \
		(exec_stk == EXSTACK_DEFAULT) : 0)
#अन्यथा 
# define elf_पढ़ो_implies_exec(ex, exec_stk) (exec_stk == EXSTACK_DEFAULT)
#पूर्ण_अगर /* __घातerpc64__ */

बाह्य पूर्णांक dcache_bsize;
बाह्य पूर्णांक icache_bsize;
बाह्य पूर्णांक ucache_bsize;

/* vDSO has arch_setup_additional_pages */
#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES
काष्ठा linux_binprm;
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
				       पूर्णांक uses_पूर्णांकerp);
#घोषणा VDSO_AUX_ENT(a,b) NEW_AUX_ENT(a,b)

/* 1GB क्रम 64bit, 8MB क्रम 32bit */
#घोषणा STACK_RND_MASK (is_32bit_task() ? \
	(0x7ff >> (PAGE_SHIFT - 12)) : \
	(0x3ffff >> (PAGE_SHIFT - 12)))

#अगर_घोषित CONFIG_SPU_BASE
/* Notes used in ET_CORE. Note name is "SPU/<fd>/<filename>". */
#घोषणा NT_SPU		1

#घोषणा ARCH_HAVE_EXTRA_ELF_NOTES

#पूर्ण_अगर /* CONFIG_SPU_BASE */

#अगर_घोषित CONFIG_PPC64

#घोषणा get_cache_geometry(level) \
	(ppc64_caches.level.assoc << 16 | ppc64_caches.level.line_size)

#घोषणा ARCH_DLINFO_CACHE_GEOMETRY					\
	NEW_AUX_ENT(AT_L1I_CACHESIZE, ppc64_caches.l1i.size);		\
	NEW_AUX_ENT(AT_L1I_CACHEGEOMETRY, get_cache_geometry(l1i));	\
	NEW_AUX_ENT(AT_L1D_CACHESIZE, ppc64_caches.l1d.size);		\
	NEW_AUX_ENT(AT_L1D_CACHEGEOMETRY, get_cache_geometry(l1d));	\
	NEW_AUX_ENT(AT_L2_CACHESIZE, ppc64_caches.l2.size);		\
	NEW_AUX_ENT(AT_L2_CACHEGEOMETRY, get_cache_geometry(l2));	\
	NEW_AUX_ENT(AT_L3_CACHESIZE, ppc64_caches.l3.size);		\
	NEW_AUX_ENT(AT_L3_CACHEGEOMETRY, get_cache_geometry(l3))

#अन्यथा
#घोषणा ARCH_DLINFO_CACHE_GEOMETRY
#पूर्ण_अगर

/*
 * The requirements here are:
 * - keep the final alignment of sp (sp & 0xf)
 * - make sure the 32-bit value at the first 16 byte aligned position of
 *   AUXV is greater than 16 क्रम glibc compatibility.
 *   AT_IGNOREPPC is used क्रम that.
 * - क्रम compatibility with glibc ARCH_DLINFO must always be defined on PPC,
 *   even अगर DLINFO_ARCH_ITEMS goes to zero or is undefined.
 * update AT_VECTOR_SIZE_ARCH अगर the number of NEW_AUX_ENT entries changes
 */
#घोषणा ARCH_DLINFO							\
करो अणु									\
	/* Handle glibc compatibility. */				\
	NEW_AUX_ENT(AT_IGNOREPPC, AT_IGNOREPPC);			\
	NEW_AUX_ENT(AT_IGNOREPPC, AT_IGNOREPPC);			\
	/* Cache size items */						\
	NEW_AUX_ENT(AT_DCACHEBSIZE, dcache_bsize);			\
	NEW_AUX_ENT(AT_ICACHEBSIZE, icache_bsize);			\
	NEW_AUX_ENT(AT_UCACHEBSIZE, 0);					\
	VDSO_AUX_ENT(AT_SYSINFO_EHDR, (अचिन्हित दीर्घ)current->mm->context.vdso);\
	ARCH_DLINFO_CACHE_GEOMETRY;					\
पूर्ण जबतक (0)

/* Relocate the kernel image to @final_address */
व्योम relocate(अचिन्हित दीर्घ final_address);

#पूर्ण_अगर /* _ASM_POWERPC_ELF_H */
