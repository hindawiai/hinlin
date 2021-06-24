<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/mmu.c
 *
 *  Copyright (C) 1995-2005 Russell King
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/mman.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/memblock.h>
#समावेश <linux/fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cachetype.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/highस्मृति.स>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/procinfo.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/kasan_def.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/fixmap.h>

#समावेश "fault.h"
#समावेश "mm.h"
#समावेश "tcm.h"

बाह्य अचिन्हित दीर्घ __atags_poपूर्णांकer;

/*
 * empty_zero_page is a special page that is used क्रम
 * zero-initialized data and COW.
 */
काष्ठा page *empty_zero_page;
EXPORT_SYMBOL(empty_zero_page);

/*
 * The pmd table क्रम the upper-most set of pages.
 */
pmd_t *top_pmd;

pmdval_t user_pmd_table = _PAGE_USER_TABLE;

#घोषणा CPOLICY_UNCACHED	0
#घोषणा CPOLICY_BUFFERED	1
#घोषणा CPOLICY_WRITETHROUGH	2
#घोषणा CPOLICY_WRITEBACK	3
#घोषणा CPOLICY_WRITEALLOC	4

अटल अचिन्हित पूर्णांक cachepolicy __initdata = CPOLICY_WRITEBACK;
अटल अचिन्हित पूर्णांक ecc_mask __initdata = 0;
pgprot_t pgprot_user;
pgprot_t pgprot_kernel;

EXPORT_SYMBOL(pgprot_user);
EXPORT_SYMBOL(pgprot_kernel);

काष्ठा cachepolicy अणु
	स्थिर अक्षर	policy[16];
	अचिन्हित पूर्णांक	cr_mask;
	pmdval_t	pmd;
	pteval_t	pte;
पूर्ण;

अटल काष्ठा cachepolicy cache_policies[] __initdata = अणु
	अणु
		.policy		= "uncached",
		.cr_mask	= CR_W|CR_C,
		.pmd		= PMD_SECT_UNCACHED,
		.pte		= L_PTE_MT_UNCACHED,
	पूर्ण, अणु
		.policy		= "buffered",
		.cr_mask	= CR_C,
		.pmd		= PMD_SECT_BUFFERED,
		.pte		= L_PTE_MT_BUFFERABLE,
	पूर्ण, अणु
		.policy		= "writethrough",
		.cr_mask	= 0,
		.pmd		= PMD_SECT_WT,
		.pte		= L_PTE_MT_WRITETHROUGH,
	पूर्ण, अणु
		.policy		= "writeback",
		.cr_mask	= 0,
		.pmd		= PMD_SECT_WB,
		.pte		= L_PTE_MT_WRITEBACK,
	पूर्ण, अणु
		.policy		= "writealloc",
		.cr_mask	= 0,
		.pmd		= PMD_SECT_WBWA,
		.pte		= L_PTE_MT_WRITEALLOC,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_CPU_CP15
अटल अचिन्हित दीर्घ initial_pmd_value __initdata = 0;

/*
 * Initialise the cache_policy variable with the initial state specअगरied
 * via the "pmd" value.  This is used to ensure that on ARMv6 and later,
 * the C code sets the page tables up with the same policy as the head
 * assembly code, which aव्योमs an illegal state where the TLBs can get
 * confused.  See comments in early_cachepolicy() क्रम more inक्रमmation.
 */
व्योम __init init_शेष_cache_policy(अचिन्हित दीर्घ pmd)
अणु
	पूर्णांक i;

	initial_pmd_value = pmd;

	pmd &= PMD_SECT_CACHE_MASK;

	क्रम (i = 0; i < ARRAY_SIZE(cache_policies); i++)
		अगर (cache_policies[i].pmd == pmd) अणु
			cachepolicy = i;
			अवरोध;
		पूर्ण

	अगर (i == ARRAY_SIZE(cache_policies))
		pr_err("ERROR: could not find cache policy\n");
पूर्ण

/*
 * These are useful क्रम identअगरying cache coherency problems by allowing
 * the cache or the cache and ग_लिखोbuffer to be turned off.  (Note: the
 * ग_लिखो buffer should not be on and the cache off).
 */
अटल पूर्णांक __init early_cachepolicy(अक्षर *p)
अणु
	पूर्णांक i, selected = -1;

	क्रम (i = 0; i < ARRAY_SIZE(cache_policies); i++) अणु
		पूर्णांक len = म_माप(cache_policies[i].policy);

		अगर (स_भेद(p, cache_policies[i].policy, len) == 0) अणु
			selected = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (selected == -1)
		pr_err("ERROR: unknown or unsupported cache policy\n");

	/*
	 * This restriction is partly to करो with the way we boot; it is
	 * unpredictable to have memory mapped using two dअगरferent sets of
	 * memory attributes (shared, type, and cache attribs).  We can not
	 * change these attributes once the initial assembly has setup the
	 * page tables.
	 */
	अगर (cpu_architecture() >= CPU_ARCH_ARMv6 && selected != cachepolicy) अणु
		pr_warn("Only cachepolicy=%s supported on ARMv6 and later\n",
			cache_policies[cachepolicy].policy);
		वापस 0;
	पूर्ण

	अगर (selected != cachepolicy) अणु
		अचिन्हित दीर्घ cr = __clear_cr(cache_policies[selected].cr_mask);
		cachepolicy = selected;
		flush_cache_all();
		set_cr(cr);
	पूर्ण
	वापस 0;
पूर्ण
early_param("cachepolicy", early_cachepolicy);

अटल पूर्णांक __init early_nocache(अक्षर *__unused)
अणु
	अक्षर *p = "buffered";
	pr_warn("nocache is deprecated; use cachepolicy=%s\n", p);
	early_cachepolicy(p);
	वापस 0;
पूर्ण
early_param("nocache", early_nocache);

अटल पूर्णांक __init early_noग_लिखो(अक्षर *__unused)
अणु
	अक्षर *p = "uncached";
	pr_warn("nowb is deprecated; use cachepolicy=%s\n", p);
	early_cachepolicy(p);
	वापस 0;
पूर्ण
early_param("nowb", early_noग_लिखो);

#अगर_अघोषित CONFIG_ARM_LPAE
अटल पूर्णांक __init early_ecc(अक्षर *p)
अणु
	अगर (स_भेद(p, "on", 2) == 0)
		ecc_mask = PMD_PROTECTION;
	अन्यथा अगर (स_भेद(p, "off", 3) == 0)
		ecc_mask = 0;
	वापस 0;
पूर्ण
early_param("ecc", early_ecc);
#पूर्ण_अगर

#अन्यथा /* अगरdef CONFIG_CPU_CP15 */

अटल पूर्णांक __init early_cachepolicy(अक्षर *p)
अणु
	pr_warn("cachepolicy kernel parameter not supported without cp15\n");
पूर्ण
early_param("cachepolicy", early_cachepolicy);

अटल पूर्णांक __init noalign_setup(अक्षर *__unused)
अणु
	pr_warn("noalign kernel parameter not supported without cp15\n");
पूर्ण
__setup("noalign", noalign_setup);

#पूर्ण_अगर /* अगरdef CONFIG_CPU_CP15 / अन्यथा */

#घोषणा PROT_PTE_DEVICE		L_PTE_PRESENT|L_PTE_YOUNG|L_PTE_सूचीTY|L_PTE_XN
#घोषणा PROT_PTE_S2_DEVICE	PROT_PTE_DEVICE
#घोषणा PROT_SECT_DEVICE	PMD_TYPE_SECT|PMD_SECT_AP_WRITE

अटल काष्ठा mem_type mem_types[] __ro_after_init = अणु
	[MT_DEVICE] = अणु		  /* Strongly ordered / ARMv6 shared device */
		.prot_pte	= PROT_PTE_DEVICE | L_PTE_MT_DEV_SHARED |
				  L_PTE_SHARED,
		.prot_l1	= PMD_TYPE_TABLE,
		.prot_sect	= PROT_SECT_DEVICE | PMD_SECT_S,
		.करोमुख्य		= DOMAIN_IO,
	पूर्ण,
	[MT_DEVICE_NONSHARED] = अणु /* ARMv6 non-shared device */
		.prot_pte	= PROT_PTE_DEVICE | L_PTE_MT_DEV_NONSHARED,
		.prot_l1	= PMD_TYPE_TABLE,
		.prot_sect	= PROT_SECT_DEVICE,
		.करोमुख्य		= DOMAIN_IO,
	पूर्ण,
	[MT_DEVICE_CACHED] = अणु	  /* ioremap_cache */
		.prot_pte	= PROT_PTE_DEVICE | L_PTE_MT_DEV_CACHED,
		.prot_l1	= PMD_TYPE_TABLE,
		.prot_sect	= PROT_SECT_DEVICE | PMD_SECT_WB,
		.करोमुख्य		= DOMAIN_IO,
	पूर्ण,
	[MT_DEVICE_WC] = अणु	/* ioremap_wc */
		.prot_pte	= PROT_PTE_DEVICE | L_PTE_MT_DEV_WC,
		.prot_l1	= PMD_TYPE_TABLE,
		.prot_sect	= PROT_SECT_DEVICE,
		.करोमुख्य		= DOMAIN_IO,
	पूर्ण,
	[MT_UNCACHED] = अणु
		.prot_pte	= PROT_PTE_DEVICE,
		.prot_l1	= PMD_TYPE_TABLE,
		.prot_sect	= PMD_TYPE_SECT | PMD_SECT_XN,
		.करोमुख्य		= DOMAIN_IO,
	पूर्ण,
	[MT_CACHECLEAN] = अणु
		.prot_sect = PMD_TYPE_SECT | PMD_SECT_XN,
		.करोमुख्य    = DOMAIN_KERNEL,
	पूर्ण,
#अगर_अघोषित CONFIG_ARM_LPAE
	[MT_MINICLEAN] = अणु
		.prot_sect = PMD_TYPE_SECT | PMD_SECT_XN | PMD_SECT_MINICACHE,
		.करोमुख्य    = DOMAIN_KERNEL,
	पूर्ण,
#पूर्ण_अगर
	[MT_LOW_VECTORS] = अणु
		.prot_pte  = L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_सूचीTY |
				L_PTE_RDONLY,
		.prot_l1   = PMD_TYPE_TABLE,
		.करोमुख्य    = DOMAIN_VECTORS,
	पूर्ण,
	[MT_HIGH_VECTORS] = अणु
		.prot_pte  = L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_सूचीTY |
				L_PTE_USER | L_PTE_RDONLY,
		.prot_l1   = PMD_TYPE_TABLE,
		.करोमुख्य    = DOMAIN_VECTORS,
	पूर्ण,
	[MT_MEMORY_RWX] = अणु
		.prot_pte  = L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_सूचीTY,
		.prot_l1   = PMD_TYPE_TABLE,
		.prot_sect = PMD_TYPE_SECT | PMD_SECT_AP_WRITE,
		.करोमुख्य    = DOMAIN_KERNEL,
	पूर्ण,
	[MT_MEMORY_RW] = अणु
		.prot_pte  = L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_सूचीTY |
			     L_PTE_XN,
		.prot_l1   = PMD_TYPE_TABLE,
		.prot_sect = PMD_TYPE_SECT | PMD_SECT_AP_WRITE,
		.करोमुख्य    = DOMAIN_KERNEL,
	पूर्ण,
	[MT_ROM] = अणु
		.prot_sect = PMD_TYPE_SECT,
		.करोमुख्य    = DOMAIN_KERNEL,
	पूर्ण,
	[MT_MEMORY_RWX_NONCACHED] = अणु
		.prot_pte  = L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_सूचीTY |
				L_PTE_MT_BUFFERABLE,
		.prot_l1   = PMD_TYPE_TABLE,
		.prot_sect = PMD_TYPE_SECT | PMD_SECT_AP_WRITE,
		.करोमुख्य    = DOMAIN_KERNEL,
	पूर्ण,
	[MT_MEMORY_RW_DTCM] = अणु
		.prot_pte  = L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_सूचीTY |
				L_PTE_XN,
		.prot_l1   = PMD_TYPE_TABLE,
		.prot_sect = PMD_TYPE_SECT | PMD_SECT_XN,
		.करोमुख्य    = DOMAIN_KERNEL,
	पूर्ण,
	[MT_MEMORY_RWX_ITCM] = अणु
		.prot_pte  = L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_सूचीTY,
		.prot_l1   = PMD_TYPE_TABLE,
		.करोमुख्य    = DOMAIN_KERNEL,
	पूर्ण,
	[MT_MEMORY_RW_SO] = अणु
		.prot_pte  = L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_सूचीTY |
				L_PTE_MT_UNCACHED | L_PTE_XN,
		.prot_l1   = PMD_TYPE_TABLE,
		.prot_sect = PMD_TYPE_SECT | PMD_SECT_AP_WRITE | PMD_SECT_S |
				PMD_SECT_UNCACHED | PMD_SECT_XN,
		.करोमुख्य    = DOMAIN_KERNEL,
	पूर्ण,
	[MT_MEMORY_DMA_READY] = अणु
		.prot_pte  = L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_सूचीTY |
				L_PTE_XN,
		.prot_l1   = PMD_TYPE_TABLE,
		.करोमुख्य    = DOMAIN_KERNEL,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा mem_type *get_mem_type(अचिन्हित पूर्णांक type)
अणु
	वापस type < ARRAY_SIZE(mem_types) ? &mem_types[type] : शून्य;
पूर्ण
EXPORT_SYMBOL(get_mem_type);

अटल pte_t *(*pte_offset_fixmap)(pmd_t *dir, अचिन्हित दीर्घ addr);

अटल pte_t bm_pte[PTRS_PER_PTE + PTE_HWTABLE_PTRS]
	__aligned(PTE_HWTABLE_OFF + PTE_HWTABLE_SIZE) __initdata;

अटल pte_t * __init pte_offset_early_fixmap(pmd_t *dir, अचिन्हित दीर्घ addr)
अणु
	वापस &bm_pte[pte_index(addr)];
पूर्ण

अटल pte_t *pte_offset_late_fixmap(pmd_t *dir, अचिन्हित दीर्घ addr)
अणु
	वापस pte_offset_kernel(dir, addr);
पूर्ण

अटल अंतरभूत pmd_t * __init fixmap_pmd(अचिन्हित दीर्घ addr)
अणु
	वापस pmd_off_k(addr);
पूर्ण

व्योम __init early_fixmap_init(व्योम)
अणु
	pmd_t *pmd;

	/*
	 * The early fixmap range spans multiple pmds, क्रम which
	 * we are not prepared:
	 */
	BUILD_BUG_ON((__fix_to_virt(__end_of_early_ioremap_region) >> PMD_SHIFT)
		     != FIXADDR_TOP >> PMD_SHIFT);

	pmd = fixmap_pmd(FIXADDR_TOP);
	pmd_populate_kernel(&init_mm, pmd, bm_pte);

	pte_offset_fixmap = pte_offset_early_fixmap;
पूर्ण

/*
 * To aव्योम TLB flush broadcasts, this uses local_flush_tlb_kernel_range().
 * As a result, this can only be called with preemption disabled, as under
 * stop_machine().
 */
व्योम __set_fixmap(क्रमागत fixed_addresses idx, phys_addr_t phys, pgprot_t prot)
अणु
	अचिन्हित दीर्घ vaddr = __fix_to_virt(idx);
	pte_t *pte = pte_offset_fixmap(pmd_off_k(vaddr), vaddr);

	/* Make sure fixmap region करोes not exceed available allocation. */
	BUILD_BUG_ON(__fix_to_virt(__end_of_fixed_addresses) < FIXADDR_START);
	BUG_ON(idx >= __end_of_fixed_addresses);

	/* we only support device mappings until pgprot_kernel has been set */
	अगर (WARN_ON(pgprot_val(prot) != pgprot_val(FIXMAP_PAGE_IO) &&
		    pgprot_val(pgprot_kernel) == 0))
		वापस;

	अगर (pgprot_val(prot))
		set_pte_at(शून्य, vaddr, pte,
			pfn_pte(phys >> PAGE_SHIFT, prot));
	अन्यथा
		pte_clear(शून्य, vaddr, pte);
	local_flush_tlb_kernel_range(vaddr, vaddr + PAGE_SIZE);
पूर्ण

/*
 * Adjust the PMD section entries according to the CPU in use.
 */
अटल व्योम __init build_mem_type_table(व्योम)
अणु
	काष्ठा cachepolicy *cp;
	अचिन्हित पूर्णांक cr = get_cr();
	pteval_t user_pgprot, kern_pgprot, vecs_pgprot;
	पूर्णांक cpu_arch = cpu_architecture();
	पूर्णांक i;

	अगर (cpu_arch < CPU_ARCH_ARMv6) अणु
#अगर defined(CONFIG_CPU_DCACHE_DISABLE)
		अगर (cachepolicy > CPOLICY_BUFFERED)
			cachepolicy = CPOLICY_BUFFERED;
#या_अगर defined(CONFIG_CPU_DCACHE_WRITETHROUGH)
		अगर (cachepolicy > CPOLICY_WRITETHROUGH)
			cachepolicy = CPOLICY_WRITETHROUGH;
#पूर्ण_अगर
	पूर्ण
	अगर (cpu_arch < CPU_ARCH_ARMv5) अणु
		अगर (cachepolicy >= CPOLICY_WRITEALLOC)
			cachepolicy = CPOLICY_WRITEBACK;
		ecc_mask = 0;
	पूर्ण

	अगर (is_smp()) अणु
		अगर (cachepolicy != CPOLICY_WRITEALLOC) अणु
			pr_warn("Forcing write-allocate cache policy for SMP\n");
			cachepolicy = CPOLICY_WRITEALLOC;
		पूर्ण
		अगर (!(initial_pmd_value & PMD_SECT_S)) अणु
			pr_warn("Forcing shared mappings for SMP\n");
			initial_pmd_value |= PMD_SECT_S;
		पूर्ण
	पूर्ण

	/*
	 * Strip out features not present on earlier architectures.
	 * Pre-ARMv5 CPUs करोn't have TEX bits.  Pre-ARMv6 CPUs or those
	 * without extended page tables करोn't have the 'Shared' bit.
	 */
	अगर (cpu_arch < CPU_ARCH_ARMv5)
		क्रम (i = 0; i < ARRAY_SIZE(mem_types); i++)
			mem_types[i].prot_sect &= ~PMD_SECT_TEX(7);
	अगर ((cpu_arch < CPU_ARCH_ARMv6 || !(cr & CR_XP)) && !cpu_is_xsc3())
		क्रम (i = 0; i < ARRAY_SIZE(mem_types); i++)
			mem_types[i].prot_sect &= ~PMD_SECT_S;

	/*
	 * ARMv5 and lower, bit 4 must be set क्रम page tables (was: cache
	 * "update-able on write" bit on ARM610).  However, Xscale and
	 * Xscale3 require this bit to be cleared.
	 */
	अगर (cpu_is_xscale_family()) अणु
		क्रम (i = 0; i < ARRAY_SIZE(mem_types); i++) अणु
			mem_types[i].prot_sect &= ~PMD_BIT4;
			mem_types[i].prot_l1 &= ~PMD_BIT4;
		पूर्ण
	पूर्ण अन्यथा अगर (cpu_arch < CPU_ARCH_ARMv6) अणु
		क्रम (i = 0; i < ARRAY_SIZE(mem_types); i++) अणु
			अगर (mem_types[i].prot_l1)
				mem_types[i].prot_l1 |= PMD_BIT4;
			अगर (mem_types[i].prot_sect)
				mem_types[i].prot_sect |= PMD_BIT4;
		पूर्ण
	पूर्ण

	/*
	 * Mark the device areas according to the CPU/architecture.
	 */
	अगर (cpu_is_xsc3() || (cpu_arch >= CPU_ARCH_ARMv6 && (cr & CR_XP))) अणु
		अगर (!cpu_is_xsc3()) अणु
			/*
			 * Mark device regions on ARMv6+ as execute-never
			 * to prevent speculative inकाष्ठाion fetches.
			 */
			mem_types[MT_DEVICE].prot_sect |= PMD_SECT_XN;
			mem_types[MT_DEVICE_NONSHARED].prot_sect |= PMD_SECT_XN;
			mem_types[MT_DEVICE_CACHED].prot_sect |= PMD_SECT_XN;
			mem_types[MT_DEVICE_WC].prot_sect |= PMD_SECT_XN;

			/* Also setup NX memory mapping */
			mem_types[MT_MEMORY_RW].prot_sect |= PMD_SECT_XN;
		पूर्ण
		अगर (cpu_arch >= CPU_ARCH_ARMv7 && (cr & CR_TRE)) अणु
			/*
			 * For ARMv7 with TEX remapping,
			 * - shared device is SXCB=1100
			 * - nonshared device is SXCB=0100
			 * - ग_लिखो combine device mem is SXCB=0001
			 * (Uncached Normal memory)
			 */
			mem_types[MT_DEVICE].prot_sect |= PMD_SECT_TEX(1);
			mem_types[MT_DEVICE_NONSHARED].prot_sect |= PMD_SECT_TEX(1);
			mem_types[MT_DEVICE_WC].prot_sect |= PMD_SECT_BUFFERABLE;
		पूर्ण अन्यथा अगर (cpu_is_xsc3()) अणु
			/*
			 * For Xscale3,
			 * - shared device is TEXCB=00101
			 * - nonshared device is TEXCB=01000
			 * - ग_लिखो combine device mem is TEXCB=00100
			 * (Inner/Outer Uncacheable in xsc3 parlance)
			 */
			mem_types[MT_DEVICE].prot_sect |= PMD_SECT_TEX(1) | PMD_SECT_BUFFERED;
			mem_types[MT_DEVICE_NONSHARED].prot_sect |= PMD_SECT_TEX(2);
			mem_types[MT_DEVICE_WC].prot_sect |= PMD_SECT_TEX(1);
		पूर्ण अन्यथा अणु
			/*
			 * For ARMv6 and ARMv7 without TEX remapping,
			 * - shared device is TEXCB=00001
			 * - nonshared device is TEXCB=01000
			 * - ग_लिखो combine device mem is TEXCB=00100
			 * (Uncached Normal in ARMv6 parlance).
			 */
			mem_types[MT_DEVICE].prot_sect |= PMD_SECT_BUFFERED;
			mem_types[MT_DEVICE_NONSHARED].prot_sect |= PMD_SECT_TEX(2);
			mem_types[MT_DEVICE_WC].prot_sect |= PMD_SECT_TEX(1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * On others, ग_लिखो combining is "Uncached/Buffered"
		 */
		mem_types[MT_DEVICE_WC].prot_sect |= PMD_SECT_BUFFERABLE;
	पूर्ण

	/*
	 * Now deal with the memory-type mappings
	 */
	cp = &cache_policies[cachepolicy];
	vecs_pgprot = kern_pgprot = user_pgprot = cp->pte;

#अगर_अघोषित CONFIG_ARM_LPAE
	/*
	 * We करोn't use करोमुख्यs on ARMv6 (since this causes problems with
	 * v6/v7 kernels), so we must use a separate memory type क्रम user
	 * r/o, kernel r/w to map the vectors page.
	 */
	अगर (cpu_arch == CPU_ARCH_ARMv6)
		vecs_pgprot |= L_PTE_MT_VECTORS;

	/*
	 * Check is it with support क्रम the PXN bit
	 * in the Short-descriptor translation table क्रमmat descriptors.
	 */
	अगर (cpu_arch == CPU_ARCH_ARMv7 &&
		(पढ़ो_cpuid_ext(CPUID_EXT_MMFR0) & 0xF) >= 4) अणु
		user_pmd_table |= PMD_PXNTABLE;
	पूर्ण
#पूर्ण_अगर

	/*
	 * ARMv6 and above have extended page tables.
	 */
	अगर (cpu_arch >= CPU_ARCH_ARMv6 && (cr & CR_XP)) अणु
#अगर_अघोषित CONFIG_ARM_LPAE
		/*
		 * Mark cache clean areas and XIP ROM पढ़ो only
		 * from SVC mode and no access from userspace.
		 */
		mem_types[MT_ROM].prot_sect |= PMD_SECT_APX|PMD_SECT_AP_WRITE;
		mem_types[MT_MINICLEAN].prot_sect |= PMD_SECT_APX|PMD_SECT_AP_WRITE;
		mem_types[MT_CACHECLEAN].prot_sect |= PMD_SECT_APX|PMD_SECT_AP_WRITE;
#पूर्ण_अगर

		/*
		 * If the initial page tables were created with the S bit
		 * set, then we need to करो the same here क्रम the same
		 * reasons given in early_cachepolicy().
		 */
		अगर (initial_pmd_value & PMD_SECT_S) अणु
			user_pgprot |= L_PTE_SHARED;
			kern_pgprot |= L_PTE_SHARED;
			vecs_pgprot |= L_PTE_SHARED;
			mem_types[MT_DEVICE_WC].prot_sect |= PMD_SECT_S;
			mem_types[MT_DEVICE_WC].prot_pte |= L_PTE_SHARED;
			mem_types[MT_DEVICE_CACHED].prot_sect |= PMD_SECT_S;
			mem_types[MT_DEVICE_CACHED].prot_pte |= L_PTE_SHARED;
			mem_types[MT_MEMORY_RWX].prot_sect |= PMD_SECT_S;
			mem_types[MT_MEMORY_RWX].prot_pte |= L_PTE_SHARED;
			mem_types[MT_MEMORY_RW].prot_sect |= PMD_SECT_S;
			mem_types[MT_MEMORY_RW].prot_pte |= L_PTE_SHARED;
			mem_types[MT_MEMORY_DMA_READY].prot_pte |= L_PTE_SHARED;
			mem_types[MT_MEMORY_RWX_NONCACHED].prot_sect |= PMD_SECT_S;
			mem_types[MT_MEMORY_RWX_NONCACHED].prot_pte |= L_PTE_SHARED;
		पूर्ण
	पूर्ण

	/*
	 * Non-cacheable Normal - पूर्णांकended क्रम memory areas that must
	 * not cause dirty cache line ग_लिखोbacks when used
	 */
	अगर (cpu_arch >= CPU_ARCH_ARMv6) अणु
		अगर (cpu_arch >= CPU_ARCH_ARMv7 && (cr & CR_TRE)) अणु
			/* Non-cacheable Normal is XCB = 001 */
			mem_types[MT_MEMORY_RWX_NONCACHED].prot_sect |=
				PMD_SECT_BUFFERED;
		पूर्ण अन्यथा अणु
			/* For both ARMv6 and non-TEX-remapping ARMv7 */
			mem_types[MT_MEMORY_RWX_NONCACHED].prot_sect |=
				PMD_SECT_TEX(1);
		पूर्ण
	पूर्ण अन्यथा अणु
		mem_types[MT_MEMORY_RWX_NONCACHED].prot_sect |= PMD_SECT_BUFFERABLE;
	पूर्ण

#अगर_घोषित CONFIG_ARM_LPAE
	/*
	 * Do not generate access flag faults क्रम the kernel mappings.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(mem_types); i++) अणु
		mem_types[i].prot_pte |= PTE_EXT_AF;
		अगर (mem_types[i].prot_sect)
			mem_types[i].prot_sect |= PMD_SECT_AF;
	पूर्ण
	kern_pgprot |= PTE_EXT_AF;
	vecs_pgprot |= PTE_EXT_AF;

	/*
	 * Set PXN क्रम user mappings
	 */
	user_pgprot |= PTE_EXT_PXN;
#पूर्ण_अगर

	क्रम (i = 0; i < 16; i++) अणु
		pteval_t v = pgprot_val(protection_map[i]);
		protection_map[i] = __pgprot(v | user_pgprot);
	पूर्ण

	mem_types[MT_LOW_VECTORS].prot_pte |= vecs_pgprot;
	mem_types[MT_HIGH_VECTORS].prot_pte |= vecs_pgprot;

	pgprot_user   = __pgprot(L_PTE_PRESENT | L_PTE_YOUNG | user_pgprot);
	pgprot_kernel = __pgprot(L_PTE_PRESENT | L_PTE_YOUNG |
				 L_PTE_सूचीTY | kern_pgprot);

	mem_types[MT_LOW_VECTORS].prot_l1 |= ecc_mask;
	mem_types[MT_HIGH_VECTORS].prot_l1 |= ecc_mask;
	mem_types[MT_MEMORY_RWX].prot_sect |= ecc_mask | cp->pmd;
	mem_types[MT_MEMORY_RWX].prot_pte |= kern_pgprot;
	mem_types[MT_MEMORY_RW].prot_sect |= ecc_mask | cp->pmd;
	mem_types[MT_MEMORY_RW].prot_pte |= kern_pgprot;
	mem_types[MT_MEMORY_DMA_READY].prot_pte |= kern_pgprot;
	mem_types[MT_MEMORY_RWX_NONCACHED].prot_sect |= ecc_mask;
	mem_types[MT_ROM].prot_sect |= cp->pmd;

	चयन (cp->pmd) अणु
	हाल PMD_SECT_WT:
		mem_types[MT_CACHECLEAN].prot_sect |= PMD_SECT_WT;
		अवरोध;
	हाल PMD_SECT_WB:
	हाल PMD_SECT_WBWA:
		mem_types[MT_CACHECLEAN].prot_sect |= PMD_SECT_WB;
		अवरोध;
	पूर्ण
	pr_info("Memory policy: %sData cache %s\n",
		ecc_mask ? "ECC enabled, " : "", cp->policy);

	क्रम (i = 0; i < ARRAY_SIZE(mem_types); i++) अणु
		काष्ठा mem_type *t = &mem_types[i];
		अगर (t->prot_l1)
			t->prot_l1 |= PMD_DOMAIN(t->करोमुख्य);
		अगर (t->prot_sect)
			t->prot_sect |= PMD_DOMAIN(t->करोमुख्य);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ARM_DMA_MEM_BUFFERABLE
pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
			      अचिन्हित दीर्घ size, pgprot_t vma_prot)
अणु
	अगर (!pfn_valid(pfn))
		वापस pgprot_noncached(vma_prot);
	अन्यथा अगर (file->f_flags & O_SYNC)
		वापस pgprot_ग_लिखोcombine(vma_prot);
	वापस vma_prot;
पूर्ण
EXPORT_SYMBOL(phys_mem_access_prot);
#पूर्ण_अगर

#घोषणा vectors_base()	(vectors_high() ? 0xffff0000 : 0)

अटल व्योम __init *early_alloc(अचिन्हित दीर्घ sz)
अणु
	व्योम *ptr = memblock_alloc(sz, sz);

	अगर (!ptr)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, sz, sz);

	वापस ptr;
पूर्ण

अटल व्योम *__init late_alloc(अचिन्हित दीर्घ sz)
अणु
	व्योम *ptr = (व्योम *)__get_मुक्त_pages(GFP_PGTABLE_KERNEL, get_order(sz));

	अगर (!ptr || !pgtable_pte_page_ctor(virt_to_page(ptr)))
		BUG();
	वापस ptr;
पूर्ण

अटल pte_t * __init arm_pte_alloc(pmd_t *pmd, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ prot,
				व्योम *(*alloc)(अचिन्हित दीर्घ sz))
अणु
	अगर (pmd_none(*pmd)) अणु
		pte_t *pte = alloc(PTE_HWTABLE_OFF + PTE_HWTABLE_SIZE);
		__pmd_populate(pmd, __pa(pte), prot);
	पूर्ण
	BUG_ON(pmd_bad(*pmd));
	वापस pte_offset_kernel(pmd, addr);
पूर्ण

अटल pte_t * __init early_pte_alloc(pmd_t *pmd, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ prot)
अणु
	वापस arm_pte_alloc(pmd, addr, prot, early_alloc);
पूर्ण

अटल व्योम __init alloc_init_pte(pmd_t *pmd, अचिन्हित दीर्घ addr,
				  अचिन्हित दीर्घ end, अचिन्हित दीर्घ pfn,
				  स्थिर काष्ठा mem_type *type,
				  व्योम *(*alloc)(अचिन्हित दीर्घ sz),
				  bool ng)
अणु
	pte_t *pte = arm_pte_alloc(pmd, addr, type->prot_l1, alloc);
	करो अणु
		set_pte_ext(pte, pfn_pte(pfn, __pgprot(type->prot_pte)),
			    ng ? PTE_EXT_NG : 0);
		pfn++;
	पूर्ण जबतक (pte++, addr += PAGE_SIZE, addr != end);
पूर्ण

अटल व्योम __init __map_init_section(pmd_t *pmd, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ end, phys_addr_t phys,
			स्थिर काष्ठा mem_type *type, bool ng)
अणु
	pmd_t *p = pmd;

#अगर_अघोषित CONFIG_ARM_LPAE
	/*
	 * In classic MMU क्रमmat, puds and pmds are folded in to
	 * the pgds. pmd_offset gives the PGD entry. PGDs refer to a
	 * group of L1 entries making up one logical poपूर्णांकer to
	 * an L2 table (2MB), where as PMDs refer to the inभागidual
	 * L1 entries (1MB). Hence increment to get the correct
	 * offset क्रम odd 1MB sections.
	 * (See arch/arm/include/यंत्र/pgtable-2level.h)
	 */
	अगर (addr & SECTION_SIZE)
		pmd++;
#पूर्ण_अगर
	करो अणु
		*pmd = __pmd(phys | type->prot_sect | (ng ? PMD_SECT_nG : 0));
		phys += SECTION_SIZE;
	पूर्ण जबतक (pmd++, addr += SECTION_SIZE, addr != end);

	flush_pmd_entry(p);
पूर्ण

अटल व्योम __init alloc_init_pmd(pud_t *pud, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, phys_addr_t phys,
				      स्थिर काष्ठा mem_type *type,
				      व्योम *(*alloc)(अचिन्हित दीर्घ sz), bool ng)
अणु
	pmd_t *pmd = pmd_offset(pud, addr);
	अचिन्हित दीर्घ next;

	करो अणु
		/*
		 * With LPAE, we must loop over to map
		 * all the pmds क्रम the given range.
		 */
		next = pmd_addr_end(addr, end);

		/*
		 * Try a section mapping - addr, next and phys must all be
		 * aligned to a section boundary.
		 */
		अगर (type->prot_sect &&
				((addr | next | phys) & ~SECTION_MASK) == 0) अणु
			__map_init_section(pmd, addr, next, phys, type, ng);
		पूर्ण अन्यथा अणु
			alloc_init_pte(pmd, addr, next,
				       __phys_to_pfn(phys), type, alloc, ng);
		पूर्ण

		phys += next - addr;

	पूर्ण जबतक (pmd++, addr = next, addr != end);
पूर्ण

अटल व्योम __init alloc_init_pud(p4d_t *p4d, अचिन्हित दीर्घ addr,
				  अचिन्हित दीर्घ end, phys_addr_t phys,
				  स्थिर काष्ठा mem_type *type,
				  व्योम *(*alloc)(अचिन्हित दीर्घ sz), bool ng)
अणु
	pud_t *pud = pud_offset(p4d, addr);
	अचिन्हित दीर्घ next;

	करो अणु
		next = pud_addr_end(addr, end);
		alloc_init_pmd(pud, addr, next, phys, type, alloc, ng);
		phys += next - addr;
	पूर्ण जबतक (pud++, addr = next, addr != end);
पूर्ण

अटल व्योम __init alloc_init_p4d(pgd_t *pgd, अचिन्हित दीर्घ addr,
				  अचिन्हित दीर्घ end, phys_addr_t phys,
				  स्थिर काष्ठा mem_type *type,
				  व्योम *(*alloc)(अचिन्हित दीर्घ sz), bool ng)
अणु
	p4d_t *p4d = p4d_offset(pgd, addr);
	अचिन्हित दीर्घ next;

	करो अणु
		next = p4d_addr_end(addr, end);
		alloc_init_pud(p4d, addr, next, phys, type, alloc, ng);
		phys += next - addr;
	पूर्ण जबतक (p4d++, addr = next, addr != end);
पूर्ण

#अगर_अघोषित CONFIG_ARM_LPAE
अटल व्योम __init create_36bit_mapping(काष्ठा mm_काष्ठा *mm,
					काष्ठा map_desc *md,
					स्थिर काष्ठा mem_type *type,
					bool ng)
अणु
	अचिन्हित दीर्घ addr, length, end;
	phys_addr_t phys;
	pgd_t *pgd;

	addr = md->भव;
	phys = __pfn_to_phys(md->pfn);
	length = PAGE_ALIGN(md->length);

	अगर (!(cpu_architecture() >= CPU_ARCH_ARMv6 || cpu_is_xsc3())) अणु
		pr_err("MM: CPU does not support supersection mapping for 0x%08llx at 0x%08lx\n",
		       (दीर्घ दीर्घ)__pfn_to_phys((u64)md->pfn), addr);
		वापस;
	पूर्ण

	/* N.B.	ARMv6 supersections are only defined to work with करोमुख्य 0.
	 *	Since करोमुख्य assignments can in fact be arbitrary, the
	 *	'domain == 0' check below is required to insure that ARMv6
	 *	supersections are only allocated क्रम करोमुख्य 0 regardless
	 *	of the actual करोमुख्य assignments in use.
	 */
	अगर (type->करोमुख्य) अणु
		pr_err("MM: invalid domain in supersection mapping for 0x%08llx at 0x%08lx\n",
		       (दीर्घ दीर्घ)__pfn_to_phys((u64)md->pfn), addr);
		वापस;
	पूर्ण

	अगर ((addr | length | __pfn_to_phys(md->pfn)) & ~SUPERSECTION_MASK) अणु
		pr_err("MM: cannot create mapping for 0x%08llx at 0x%08lx invalid alignment\n",
		       (दीर्घ दीर्घ)__pfn_to_phys((u64)md->pfn), addr);
		वापस;
	पूर्ण

	/*
	 * Shअगरt bits [35:32] of address पूर्णांकo bits [23:20] of PMD
	 * (See ARMv6 spec).
	 */
	phys |= (((md->pfn >> (32 - PAGE_SHIFT)) & 0xF) << 20);

	pgd = pgd_offset(mm, addr);
	end = addr + length;
	करो अणु
		p4d_t *p4d = p4d_offset(pgd, addr);
		pud_t *pud = pud_offset(p4d, addr);
		pmd_t *pmd = pmd_offset(pud, addr);
		पूर्णांक i;

		क्रम (i = 0; i < 16; i++)
			*pmd++ = __pmd(phys | type->prot_sect | PMD_SECT_SUPER |
				       (ng ? PMD_SECT_nG : 0));

		addr += SUPERSECTION_SIZE;
		phys += SUPERSECTION_SIZE;
		pgd += SUPERSECTION_SIZE >> PGसूची_SHIFT;
	पूर्ण जबतक (addr != end);
पूर्ण
#पूर्ण_अगर	/* !CONFIG_ARM_LPAE */

अटल व्योम __init __create_mapping(काष्ठा mm_काष्ठा *mm, काष्ठा map_desc *md,
				    व्योम *(*alloc)(अचिन्हित दीर्घ sz),
				    bool ng)
अणु
	अचिन्हित दीर्घ addr, length, end;
	phys_addr_t phys;
	स्थिर काष्ठा mem_type *type;
	pgd_t *pgd;

	type = &mem_types[md->type];

#अगर_अघोषित CONFIG_ARM_LPAE
	/*
	 * Catch 36-bit addresses
	 */
	अगर (md->pfn >= 0x100000) अणु
		create_36bit_mapping(mm, md, type, ng);
		वापस;
	पूर्ण
#पूर्ण_अगर

	addr = md->भव & PAGE_MASK;
	phys = __pfn_to_phys(md->pfn);
	length = PAGE_ALIGN(md->length + (md->भव & ~PAGE_MASK));

	अगर (type->prot_l1 == 0 && ((addr | phys | length) & ~SECTION_MASK)) अणु
		pr_warn("BUG: map for 0x%08llx at 0x%08lx can not be mapped using pages, ignoring.\n",
			(दीर्घ दीर्घ)__pfn_to_phys(md->pfn), addr);
		वापस;
	पूर्ण

	pgd = pgd_offset(mm, addr);
	end = addr + length;
	करो अणु
		अचिन्हित दीर्घ next = pgd_addr_end(addr, end);

		alloc_init_p4d(pgd, addr, next, phys, type, alloc, ng);

		phys += next - addr;
		addr = next;
	पूर्ण जबतक (pgd++, addr != end);
पूर्ण

/*
 * Create the page directory entries and any necessary
 * page tables क्रम the mapping specअगरied by `md'.  We
 * are able to cope here with varying sizes and address
 * offsets, and we take full advantage of sections and
 * supersections.
 */
अटल व्योम __init create_mapping(काष्ठा map_desc *md)
अणु
	अगर (md->भव != vectors_base() && md->भव < TASK_SIZE) अणु
		pr_warn("BUG: not creating mapping for 0x%08llx at 0x%08lx in user region\n",
			(दीर्घ दीर्घ)__pfn_to_phys((u64)md->pfn), md->भव);
		वापस;
	पूर्ण

	अगर (md->type == MT_DEVICE &&
	    md->भव >= PAGE_OFFSET && md->भव < FIXADDR_START &&
	    (md->भव < VMALLOC_START || md->भव >= VMALLOC_END)) अणु
		pr_warn("BUG: mapping for 0x%08llx at 0x%08lx out of vmalloc space\n",
			(दीर्घ दीर्घ)__pfn_to_phys((u64)md->pfn), md->भव);
	पूर्ण

	__create_mapping(&init_mm, md, early_alloc, false);
पूर्ण

व्योम __init create_mapping_late(काष्ठा mm_काष्ठा *mm, काष्ठा map_desc *md,
				bool ng)
अणु
#अगर_घोषित CONFIG_ARM_LPAE
	p4d_t *p4d;
	pud_t *pud;

	p4d = p4d_alloc(mm, pgd_offset(mm, md->भव), md->भव);
	अगर (WARN_ON(!p4d))
		वापस;
	pud = pud_alloc(mm, p4d, md->भव);
	अगर (WARN_ON(!pud))
		वापस;
	pmd_alloc(mm, pud, 0);
#पूर्ण_अगर
	__create_mapping(mm, md, late_alloc, ng);
पूर्ण

/*
 * Create the architecture specअगरic mappings
 */
व्योम __init iotable_init(काष्ठा map_desc *io_desc, पूर्णांक nr)
अणु
	काष्ठा map_desc *md;
	काष्ठा vm_काष्ठा *vm;
	काष्ठा अटल_vm *svm;

	अगर (!nr)
		वापस;

	svm = memblock_alloc(माप(*svm) * nr, __alignof__(*svm));
	अगर (!svm)
		panic("%s: Failed to allocate %zu bytes align=0x%zx\n",
		      __func__, माप(*svm) * nr, __alignof__(*svm));

	क्रम (md = io_desc; nr; md++, nr--) अणु
		create_mapping(md);

		vm = &svm->vm;
		vm->addr = (व्योम *)(md->भव & PAGE_MASK);
		vm->size = PAGE_ALIGN(md->length + (md->भव & ~PAGE_MASK));
		vm->phys_addr = __pfn_to_phys(md->pfn);
		vm->flags = VM_IOREMAP | VM_ARM_STATIC_MAPPING;
		vm->flags |= VM_ARM_MTYPE(md->type);
		vm->caller = iotable_init;
		add_अटल_vm_early(svm++);
	पूर्ण
पूर्ण

व्योम __init vm_reserve_area_early(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size,
				  व्योम *caller)
अणु
	काष्ठा vm_काष्ठा *vm;
	काष्ठा अटल_vm *svm;

	svm = memblock_alloc(माप(*svm), __alignof__(*svm));
	अगर (!svm)
		panic("%s: Failed to allocate %zu bytes align=0x%zx\n",
		      __func__, माप(*svm), __alignof__(*svm));

	vm = &svm->vm;
	vm->addr = (व्योम *)addr;
	vm->size = size;
	vm->flags = VM_IOREMAP | VM_ARM_EMPTY_MAPPING;
	vm->caller = caller;
	add_अटल_vm_early(svm);
पूर्ण

#अगर_अघोषित CONFIG_ARM_LPAE

/*
 * The Linux PMD is made of two consecutive section entries covering 2MB
 * (see definition in include/यंत्र/pgtable-2level.h).  However a call to
 * create_mapping() may optimize अटल mappings by using inभागidual
 * 1MB section mappings.  This leaves the actual PMD potentially half
 * initialized अगर the top or bottom section entry isn't used, leaving it
 * खोलो to problems अगर a subsequent ioremap() or vदो_स्मृति() tries to use
 * the भव space left मुक्त by that unused section entry.
 *
 * Let's aव्योम the issue by inserting dummy vm entries covering the unused
 * PMD halves once the अटल mappings are in place.
 */

अटल व्योम __init pmd_empty_section_gap(अचिन्हित दीर्घ addr)
अणु
	vm_reserve_area_early(addr, SECTION_SIZE, pmd_empty_section_gap);
पूर्ण

अटल व्योम __init fill_pmd_gaps(व्योम)
अणु
	काष्ठा अटल_vm *svm;
	काष्ठा vm_काष्ठा *vm;
	अचिन्हित दीर्घ addr, next = 0;
	pmd_t *pmd;

	list_क्रम_each_entry(svm, &अटल_vmlist, list) अणु
		vm = &svm->vm;
		addr = (अचिन्हित दीर्घ)vm->addr;
		अगर (addr < next)
			जारी;

		/*
		 * Check अगर this vm starts on an odd section boundary.
		 * If so and the first section entry क्रम this PMD is मुक्त
		 * then we block the corresponding भव address.
		 */
		अगर ((addr & ~PMD_MASK) == SECTION_SIZE) अणु
			pmd = pmd_off_k(addr);
			अगर (pmd_none(*pmd))
				pmd_empty_section_gap(addr & PMD_MASK);
		पूर्ण

		/*
		 * Then check अगर this vm ends on an odd section boundary.
		 * If so and the second section entry क्रम this PMD is empty
		 * then we block the corresponding भव address.
		 */
		addr += vm->size;
		अगर ((addr & ~PMD_MASK) == SECTION_SIZE) अणु
			pmd = pmd_off_k(addr) + 1;
			अगर (pmd_none(*pmd))
				pmd_empty_section_gap(addr);
		पूर्ण

		/* no need to look at any vm entry until we hit the next PMD */
		next = (addr + PMD_SIZE - 1) & PMD_MASK;
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा fill_pmd_gaps() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर defined(CONFIG_PCI) && !defined(CONFIG_NEED_MACH_IO_H)
अटल व्योम __init pci_reserve_io(व्योम)
अणु
	काष्ठा अटल_vm *svm;

	svm = find_अटल_vm_vaddr((व्योम *)PCI_IO_VIRT_BASE);
	अगर (svm)
		वापस;

	vm_reserve_area_early(PCI_IO_VIRT_BASE, SZ_2M, pci_reserve_io);
पूर्ण
#अन्यथा
#घोषणा pci_reserve_io() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_LL
व्योम __init debug_ll_io_init(व्योम)
अणु
	काष्ठा map_desc map;

	debug_ll_addr(&map.pfn, &map.भव);
	अगर (!map.pfn || !map.भव)
		वापस;
	map.pfn = __phys_to_pfn(map.pfn);
	map.भव &= PAGE_MASK;
	map.length = PAGE_SIZE;
	map.type = MT_DEVICE;
	iotable_init(&map, 1);
पूर्ण
#पूर्ण_अगर

अटल व्योम * __initdata vदो_स्मृति_min =
	(व्योम *)(VMALLOC_END - (240 << 20) - VMALLOC_OFFSET);

/*
 * vदो_स्मृति=size क्रमces the vदो_स्मृति area to be exactly 'size'
 * bytes. This can be used to increase (or decrease) the vदो_स्मृति
 * area - the शेष is 240m.
 */
अटल पूर्णांक __init early_vदो_स्मृति(अक्षर *arg)
अणु
	अचिन्हित दीर्घ vदो_स्मृति_reserve = memparse(arg, शून्य);

	अगर (vदो_स्मृति_reserve < SZ_16M) अणु
		vदो_स्मृति_reserve = SZ_16M;
		pr_warn("vmalloc area too small, limiting to %luMB\n",
			vदो_स्मृति_reserve >> 20);
	पूर्ण

	अगर (vदो_स्मृति_reserve > VMALLOC_END - (PAGE_OFFSET + SZ_32M)) अणु
		vदो_स्मृति_reserve = VMALLOC_END - (PAGE_OFFSET + SZ_32M);
		pr_warn("vmalloc area is too big, limiting to %luMB\n",
			vदो_स्मृति_reserve >> 20);
	पूर्ण

	vदो_स्मृति_min = (व्योम *)(VMALLOC_END - vदो_स्मृति_reserve);
	वापस 0;
पूर्ण
early_param("vmalloc", early_vदो_स्मृति);

phys_addr_t arm_lowmem_limit __initdata = 0;

व्योम __init adjust_lowmem_bounds(व्योम)
अणु
	phys_addr_t block_start, block_end, memblock_limit = 0;
	u64 vदो_स्मृति_limit, i;
	phys_addr_t lowmem_limit = 0;

	/*
	 * Let's use our own (unoptimized) equivalent of __pa() that is
	 * not affected by wrap-arounds when माप(phys_addr_t) == 4.
	 * The result is used as the upper bound on physical memory address
	 * and may itself be outside the valid range क्रम which phys_addr_t
	 * and thereक्रमe __pa() is defined.
	 */
	vदो_स्मृति_limit = (u64)(uपूर्णांकptr_t)vदो_स्मृति_min - PAGE_OFFSET + PHYS_OFFSET;

	/*
	 * The first usable region must be PMD aligned. Mark its start
	 * as MEMBLOCK_NOMAP अगर it isn't
	 */
	क्रम_each_mem_range(i, &block_start, &block_end) अणु
		अगर (!IS_ALIGNED(block_start, PMD_SIZE)) अणु
			phys_addr_t len;

			len = round_up(block_start, PMD_SIZE) - block_start;
			memblock_mark_nomap(block_start, len);
		पूर्ण
		अवरोध;
	पूर्ण

	क्रम_each_mem_range(i, &block_start, &block_end) अणु
		अगर (block_start < vदो_स्मृति_limit) अणु
			अगर (block_end > lowmem_limit)
				/*
				 * Compare as u64 to ensure vदो_स्मृति_limit करोes
				 * not get truncated. block_end should always
				 * fit in phys_addr_t so there should be no
				 * issue with assignment.
				 */
				lowmem_limit = min_t(u64,
							 vदो_स्मृति_limit,
							 block_end);

			/*
			 * Find the first non-pmd-aligned page, and poपूर्णांक
			 * memblock_limit at it. This relies on rounding the
			 * limit करोwn to be pmd-aligned, which happens at the
			 * end of this function.
			 *
			 * With this algorithm, the start or end of almost any
			 * bank can be non-pmd-aligned. The only exception is
			 * that the start of the bank 0 must be section-
			 * aligned, since otherwise memory would need to be
			 * allocated when mapping the start of bank 0, which
			 * occurs beक्रमe any मुक्त memory is mapped.
			 */
			अगर (!memblock_limit) अणु
				अगर (!IS_ALIGNED(block_start, PMD_SIZE))
					memblock_limit = block_start;
				अन्यथा अगर (!IS_ALIGNED(block_end, PMD_SIZE))
					memblock_limit = lowmem_limit;
			पूर्ण

		पूर्ण
	पूर्ण

	arm_lowmem_limit = lowmem_limit;

	high_memory = __va(arm_lowmem_limit - 1) + 1;

	अगर (!memblock_limit)
		memblock_limit = arm_lowmem_limit;

	/*
	 * Round the memblock limit करोwn to a pmd size.  This
	 * helps to ensure that we will allocate memory from the
	 * last full pmd, which should be mapped.
	 */
	memblock_limit = round_करोwn(memblock_limit, PMD_SIZE);

	अगर (!IS_ENABLED(CONFIG_HIGHMEM) || cache_is_vipt_aliasing()) अणु
		अगर (memblock_end_of_DRAM() > arm_lowmem_limit) अणु
			phys_addr_t end = memblock_end_of_DRAM();

			pr_notice("Ignoring RAM at %pa-%pa\n",
				  &memblock_limit, &end);
			pr_notice("Consider using a HIGHMEM enabled kernel.\n");

			memblock_हटाओ(memblock_limit, end - memblock_limit);
		पूर्ण
	पूर्ण

	memblock_set_current_limit(memblock_limit);
पूर्ण

अटल अंतरभूत व्योम prepare_page_table(व्योम)
अणु
	अचिन्हित दीर्घ addr;
	phys_addr_t end;

	/*
	 * Clear out all the mappings below the kernel image.
	 */
#अगर_घोषित CONFIG_KASAN
	/*
	 * KASan's shaकरोw memory inserts itself between the TASK_SIZE
	 * and MODULES_VADDR. Do not clear the KASan shaकरोw memory mappings.
	 */
	क्रम (addr = 0; addr < KASAN_SHADOW_START; addr += PMD_SIZE)
		pmd_clear(pmd_off_k(addr));
	/*
	 * Skip over the KASan shaकरोw area. KASAN_SHADOW_END is someबार
	 * equal to MODULES_VADDR and then we निकास the pmd clearing. If we
	 * are using a thumb-compiled kernel, there there will be 8MB more
	 * to clear as KASan always offset to 16 MB below MODULES_VADDR.
	 */
	क्रम (addr = KASAN_SHADOW_END; addr < MODULES_VADDR; addr += PMD_SIZE)
		pmd_clear(pmd_off_k(addr));
#अन्यथा
	क्रम (addr = 0; addr < MODULES_VADDR; addr += PMD_SIZE)
		pmd_clear(pmd_off_k(addr));
#पूर्ण_अगर

#अगर_घोषित CONFIG_XIP_KERNEL
	/* The XIP kernel is mapped in the module area -- skip over it */
	addr = ((अचिन्हित दीर्घ)_exiprom + PMD_SIZE - 1) & PMD_MASK;
#पूर्ण_अगर
	क्रम ( ; addr < PAGE_OFFSET; addr += PMD_SIZE)
		pmd_clear(pmd_off_k(addr));

	/*
	 * Find the end of the first block of lowmem.
	 */
	end = memblock.memory.regions[0].base + memblock.memory.regions[0].size;
	अगर (end >= arm_lowmem_limit)
		end = arm_lowmem_limit;

	/*
	 * Clear out all the kernel space mappings, except क्रम the first
	 * memory bank, up to the vदो_स्मृति region.
	 */
	क्रम (addr = __phys_to_virt(end);
	     addr < VMALLOC_START; addr += PMD_SIZE)
		pmd_clear(pmd_off_k(addr));
पूर्ण

#अगर_घोषित CONFIG_ARM_LPAE
/* the first page is reserved क्रम pgd */
#घोषणा SWAPPER_PG_सूची_SIZE	(PAGE_SIZE + \
				 PTRS_PER_PGD * PTRS_PER_PMD * माप(pmd_t))
#अन्यथा
#घोषणा SWAPPER_PG_सूची_SIZE	(PTRS_PER_PGD * माप(pgd_t))
#पूर्ण_अगर

/*
 * Reserve the special regions of memory
 */
व्योम __init arm_mm_memblock_reserve(व्योम)
अणु
	/*
	 * Reserve the page tables.  These are alपढ़ोy in use,
	 * and can only be in node 0.
	 */
	memblock_reserve(__pa(swapper_pg_dir), SWAPPER_PG_सूची_SIZE);

#अगर_घोषित CONFIG_SA1111
	/*
	 * Because of the SA1111 DMA bug, we want to preserve our
	 * precious DMA-able memory...
	 */
	memblock_reserve(PHYS_OFFSET, __pa(swapper_pg_dir) - PHYS_OFFSET);
#पूर्ण_अगर
पूर्ण

/*
 * Set up the device mappings.  Since we clear out the page tables क्रम all
 * mappings above VMALLOC_START, except early fixmap, we might हटाओ debug
 * device mappings.  This means earlycon can be used to debug this function
 * Any other function or debugging method which may touch any device _will_
 * crash the kernel.
 */
अटल व्योम __init devicemaps_init(स्थिर काष्ठा machine_desc *mdesc)
अणु
	काष्ठा map_desc map;
	अचिन्हित दीर्घ addr;
	व्योम *vectors;

	/*
	 * Allocate the vector page early.
	 */
	vectors = early_alloc(PAGE_SIZE * 2);

	early_trap_init(vectors);

	/*
	 * Clear page table except top pmd used by early fixmaps
	 */
	क्रम (addr = VMALLOC_START; addr < (FIXADDR_TOP & PMD_MASK); addr += PMD_SIZE)
		pmd_clear(pmd_off_k(addr));

	अगर (__atags_poपूर्णांकer) अणु
		/* create a पढ़ो-only mapping of the device tree */
		map.pfn = __phys_to_pfn(__atags_poपूर्णांकer & SECTION_MASK);
		map.भव = FDT_FIXED_BASE;
		map.length = FDT_FIXED_SIZE;
		map.type = MT_ROM;
		create_mapping(&map);
	पूर्ण

	/*
	 * Map the kernel अगर it is XIP.
	 * It is always first in the modulearea.
	 */
#अगर_घोषित CONFIG_XIP_KERNEL
	map.pfn = __phys_to_pfn(CONFIG_XIP_PHYS_ADDR & SECTION_MASK);
	map.भव = MODULES_VADDR;
	map.length = ((अचिन्हित दीर्घ)_exiprom - map.भव + ~SECTION_MASK) & SECTION_MASK;
	map.type = MT_ROM;
	create_mapping(&map);
#पूर्ण_अगर

	/*
	 * Map the cache flushing regions.
	 */
#अगर_घोषित FLUSH_BASE
	map.pfn = __phys_to_pfn(FLUSH_BASE_PHYS);
	map.भव = FLUSH_BASE;
	map.length = SZ_1M;
	map.type = MT_CACHECLEAN;
	create_mapping(&map);
#पूर्ण_अगर
#अगर_घोषित FLUSH_BASE_MINICACHE
	map.pfn = __phys_to_pfn(FLUSH_BASE_PHYS + SZ_1M);
	map.भव = FLUSH_BASE_MINICACHE;
	map.length = SZ_1M;
	map.type = MT_MINICLEAN;
	create_mapping(&map);
#पूर्ण_अगर

	/*
	 * Create a mapping क्रम the machine vectors at the high-vectors
	 * location (0xffff0000).  If we aren't using high-vectors, also
	 * create a mapping at the low-vectors भव address.
	 */
	map.pfn = __phys_to_pfn(virt_to_phys(vectors));
	map.भव = 0xffff0000;
	map.length = PAGE_SIZE;
#अगर_घोषित CONFIG_KUSER_HELPERS
	map.type = MT_HIGH_VECTORS;
#अन्यथा
	map.type = MT_LOW_VECTORS;
#पूर्ण_अगर
	create_mapping(&map);

	अगर (!vectors_high()) अणु
		map.भव = 0;
		map.length = PAGE_SIZE * 2;
		map.type = MT_LOW_VECTORS;
		create_mapping(&map);
	पूर्ण

	/* Now create a kernel पढ़ो-only mapping */
	map.pfn += 1;
	map.भव = 0xffff0000 + PAGE_SIZE;
	map.length = PAGE_SIZE;
	map.type = MT_LOW_VECTORS;
	create_mapping(&map);

	/*
	 * Ask the machine support to map in the अटलally mapped devices.
	 */
	अगर (mdesc->map_io)
		mdesc->map_io();
	अन्यथा
		debug_ll_io_init();
	fill_pmd_gaps();

	/* Reserve fixed i/o space in VMALLOC region */
	pci_reserve_io();

	/*
	 * Finally flush the caches and tlb to ensure that we're in a
	 * consistent state wrt the ग_लिखोbuffer.  This also ensures that
	 * any ग_लिखो-allocated cache lines in the vector page are written
	 * back.  After this poपूर्णांक, we can start to touch devices again.
	 */
	local_flush_tlb_all();
	flush_cache_all();

	/* Enable asynchronous पातs */
	early_abt_enable();
पूर्ण

अटल व्योम __init kmap_init(व्योम)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	pkmap_page_table = early_pte_alloc(pmd_off_k(PKMAP_BASE),
		PKMAP_BASE, _PAGE_KERNEL_TABLE);
#पूर्ण_अगर

	early_pte_alloc(pmd_off_k(FIXADDR_START), FIXADDR_START,
			_PAGE_KERNEL_TABLE);
पूर्ण

अटल व्योम __init map_lowmem(व्योम)
अणु
	phys_addr_t kernel_x_start = round_करोwn(__pa(KERNEL_START), SECTION_SIZE);
	phys_addr_t kernel_x_end = round_up(__pa(__init_end), SECTION_SIZE);
	phys_addr_t start, end;
	u64 i;

	/* Map all the lowmem memory banks. */
	क्रम_each_mem_range(i, &start, &end) अणु
		काष्ठा map_desc map;

		अगर (end > arm_lowmem_limit)
			end = arm_lowmem_limit;
		अगर (start >= end)
			अवरोध;

		अगर (end < kernel_x_start) अणु
			map.pfn = __phys_to_pfn(start);
			map.भव = __phys_to_virt(start);
			map.length = end - start;
			map.type = MT_MEMORY_RWX;

			create_mapping(&map);
		पूर्ण अन्यथा अगर (start >= kernel_x_end) अणु
			map.pfn = __phys_to_pfn(start);
			map.भव = __phys_to_virt(start);
			map.length = end - start;
			map.type = MT_MEMORY_RW;

			create_mapping(&map);
		पूर्ण अन्यथा अणु
			/* This better cover the entire kernel */
			अगर (start < kernel_x_start) अणु
				map.pfn = __phys_to_pfn(start);
				map.भव = __phys_to_virt(start);
				map.length = kernel_x_start - start;
				map.type = MT_MEMORY_RW;

				create_mapping(&map);
			पूर्ण

			map.pfn = __phys_to_pfn(kernel_x_start);
			map.भव = __phys_to_virt(kernel_x_start);
			map.length = kernel_x_end - kernel_x_start;
			map.type = MT_MEMORY_RWX;

			create_mapping(&map);

			अगर (kernel_x_end < end) अणु
				map.pfn = __phys_to_pfn(kernel_x_end);
				map.भव = __phys_to_virt(kernel_x_end);
				map.length = end - kernel_x_end;
				map.type = MT_MEMORY_RW;

				create_mapping(&map);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ARM_PV_FIXUP
प्रकार व्योम pgtables_remap(दीर्घ दीर्घ offset, अचिन्हित दीर्घ pgd);
pgtables_remap lpae_pgtables_remap_यंत्र;

/*
 * early_paging_init() recreates boot समय page table setup, allowing machines
 * to चयन over to a high (>4G) address space on LPAE प्रणालीs
 */
अटल व्योम __init early_paging_init(स्थिर काष्ठा machine_desc *mdesc)
अणु
	pgtables_remap *lpae_pgtables_remap;
	अचिन्हित दीर्घ pa_pgd;
	अचिन्हित पूर्णांक cr, ttbcr;
	दीर्घ दीर्घ offset;

	अगर (!mdesc->pv_fixup)
		वापस;

	offset = mdesc->pv_fixup();
	अगर (offset == 0)
		वापस;

	/*
	 * Get the address of the remap function in the 1:1 identity
	 * mapping setup by the early page table assembly code.  We
	 * must get this prior to the pv update.  The following barrier
	 * ensures that this is complete beक्रमe we fixup any P:V offsets.
	 */
	lpae_pgtables_remap = (pgtables_remap *)(अचिन्हित दीर्घ)__pa(lpae_pgtables_remap_यंत्र);
	pa_pgd = __pa(swapper_pg_dir);
	barrier();

	pr_info("Switching physical address space to 0x%08llx\n",
		(u64)PHYS_OFFSET + offset);

	/* Re-set the phys pfn offset, and the pv offset */
	__pv_offset += offset;
	__pv_phys_pfn_offset += PFN_DOWN(offset);

	/* Run the patch stub to update the स्थिरants */
	fixup_pv_table(&__pv_table_begin,
		(&__pv_table_end - &__pv_table_begin) << 2);

	/*
	 * We changing not only the भव to physical mapping, but also
	 * the physical addresses used to access memory.  We need to flush
	 * all levels of cache in the प्रणाली with caching disabled to
	 * ensure that all data is written back, and nothing is prefetched
	 * पूर्णांकo the caches.  We also need to prevent the TLB walkers
	 * allocating पूर्णांकo the caches too.  Note that this is ARMv7 LPAE
	 * specअगरic.
	 */
	cr = get_cr();
	set_cr(cr & ~(CR_I | CR_C));
	यंत्र("mrc p15, 0, %0, c2, c0, 2" : "=r" (ttbcr));
	यंत्र अस्थिर("mcr p15, 0, %0, c2, c0, 2"
		: : "r" (ttbcr & ~(3 << 8 | 3 << 10)));
	flush_cache_all();

	/*
	 * Fixup the page tables - this must be in the idmap region as
	 * we need to disable the MMU to करो this safely, and hence it
	 * needs to be assembly.  It's fairly simple, as we're using the
	 * temporary tables setup by the initial assembly code.
	 */
	lpae_pgtables_remap(offset, pa_pgd);

	/* Re-enable the caches and cacheable TLB walks */
	यंत्र अस्थिर("mcr p15, 0, %0, c2, c0, 2" : : "r" (ttbcr));
	set_cr(cr);
पूर्ण

#अन्यथा

अटल व्योम __init early_paging_init(स्थिर काष्ठा machine_desc *mdesc)
अणु
	दीर्घ दीर्घ offset;

	अगर (!mdesc->pv_fixup)
		वापस;

	offset = mdesc->pv_fixup();
	अगर (offset == 0)
		वापस;

	pr_crit("Physical address space modification is only to support Keystone2.\n");
	pr_crit("Please enable ARM_LPAE and ARM_PATCH_PHYS_VIRT support to use this\n");
	pr_crit("feature. Your kernel may crash now, have a good day.\n");
	add_taपूर्णांक(TAINT_CPU_OUT_OF_SPEC, LOCKDEP_STILL_OK);
पूर्ण

#पूर्ण_अगर

अटल व्योम __init early_fixmap_shutकरोwn(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ va = fix_to_virt(__end_of_permanent_fixed_addresses - 1);

	pte_offset_fixmap = pte_offset_late_fixmap;
	pmd_clear(fixmap_pmd(va));
	local_flush_tlb_kernel_page(va);

	क्रम (i = 0; i < __end_of_permanent_fixed_addresses; i++) अणु
		pte_t *pte;
		काष्ठा map_desc map;

		map.भव = fix_to_virt(i);
		pte = pte_offset_early_fixmap(pmd_off_k(map.भव), map.भव);

		/* Only i/o device mappings are supported ATM */
		अगर (pte_none(*pte) ||
		    (pte_val(*pte) & L_PTE_MT_MASK) != L_PTE_MT_DEV_SHARED)
			जारी;

		map.pfn = pte_pfn(*pte);
		map.type = MT_DEVICE;
		map.length = PAGE_SIZE;

		create_mapping(&map);
	पूर्ण
पूर्ण

/*
 * paging_init() sets up the page tables, initialises the zone memory
 * maps, and sets up the zero page, bad page and bad page tables.
 */
व्योम __init paging_init(स्थिर काष्ठा machine_desc *mdesc)
अणु
	व्योम *zero_page;

	prepare_page_table();
	map_lowmem();
	memblock_set_current_limit(arm_lowmem_limit);
	dma_contiguous_remap();
	early_fixmap_shutकरोwn();
	devicemaps_init(mdesc);
	kmap_init();
	tcm_init();

	top_pmd = pmd_off_k(0xffff0000);

	/* allocate the zero page. */
	zero_page = early_alloc(PAGE_SIZE);

	booपंचांगem_init();

	empty_zero_page = virt_to_page(zero_page);
	__flush_dcache_page(शून्य, empty_zero_page);
पूर्ण

व्योम __init early_mm_init(स्थिर काष्ठा machine_desc *mdesc)
अणु
	build_mem_type_table();
	early_paging_init(mdesc);
पूर्ण

व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep, pte_t pteval)
अणु
	अचिन्हित दीर्घ ext = 0;

	अगर (addr < TASK_SIZE && pte_valid_user(pteval)) अणु
		अगर (!pte_special(pteval))
			__sync_icache_dcache(pteval);
		ext |= PTE_EXT_NG;
	पूर्ण

	set_pte_ext(ptep, pteval, ext);
पूर्ण
