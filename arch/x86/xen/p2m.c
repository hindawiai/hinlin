<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Xen leaves the responsibility क्रम मुख्यtaining p2m mappings to the
 * guests themselves, but it must also access and update the p2m array
 * during suspend/resume when all the pages are पुनः_स्मृतिated.
 *
 * The logical flat p2m table is mapped to a linear kernel memory area.
 * For accesses by Xen a three-level tree linked via mfns only is set up to
 * allow the address space to be sparse.
 *
 *               Xen
 *                |
 *          p2m_top_mfn
 *              /   \
 * p2m_mid_mfn p2m_mid_mfn
 *         /           /
 *  p2m p2m p2m ...
 *
 * The p2m_mid_mfn pages are mapped by p2m_top_mfn_p.
 *
 * The p2m_top_mfn level is limited to 1 page, so the maximum representable
 * pseuकरो-physical address space is:
 *  P2M_TOP_PER_PAGE * P2M_MID_PER_PAGE * P2M_PER_PAGE pages
 *
 * P2M_PER_PAGE depends on the architecture, as a mfn is always
 * अचिन्हित दीर्घ (8 bytes on 64-bit, 4 bytes on 32), leading to
 * 512 and 1024 entries respectively.
 *
 * In लघु, these काष्ठाures contain the Machine Frame Number (MFN) of the PFN.
 *
 * However not all entries are filled with MFNs. Specअगरically क्रम all other
 * leaf entries, or क्रम the top  root, or middle one, क्रम which there is a व्योम
 * entry, we assume it is  "missing". So (क्रम example)
 *  pfn_to_mfn(0x90909090)=INVALID_P2M_ENTRY.
 * We have a dedicated page p2m_missing with all entries being
 * INVALID_P2M_ENTRY. This page may be referenced multiple बार in the p2m
 * list/tree in हाल there are multiple areas with P2M_PER_PAGE invalid pfns.
 *
 * We also have the possibility of setting 1-1 mappings on certain regions, so
 * that:
 *  pfn_to_mfn(0xc0000)=0xc0000
 *
 * The benefit of this is, that we can assume क्रम non-RAM regions (think
 * PCI BARs, or ACPI spaces), we can create mappings easily because we
 * get the PFN value to match the MFN.
 *
 * For this to work efficiently we have one new page p2m_identity. All entries
 * in p2m_identity are set to INVALID_P2M_ENTRY type (Xen toolstack only
 * recognizes that and MFNs, no other fancy value).
 *
 * On lookup we spot that the entry poपूर्णांकs to p2m_identity and वापस the
 * identity value instead of dereferencing and वापसing INVALID_P2M_ENTRY.
 * If the entry poपूर्णांकs to an allocated page, we just proceed as beक्रमe and
 * वापस the PFN. If the PFN has IDENTITY_FRAME_BIT set we unmask that in
 * appropriate functions (pfn_to_mfn).
 *
 * The reason क्रम having the IDENTITY_FRAME_BIT instead of just वापसing the
 * PFN is that we could find ourselves where pfn_to_mfn(pfn)==pfn क्रम a
 * non-identity pfn. To protect ourselves against we elect to set (and get) the
 * IDENTITY_FRAME_BIT on all identity mapped PFNs.
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/xen/page.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <xen/balloon.h>
#समावेश <xen/grant_table.h>

#समावेश "multicalls.h"
#समावेश "xen-ops.h"

#घोषणा P2M_MID_PER_PAGE	(PAGE_SIZE / माप(अचिन्हित दीर्घ *))
#घोषणा P2M_TOP_PER_PAGE	(PAGE_SIZE / माप(अचिन्हित दीर्घ **))

#घोषणा MAX_P2M_PFN	(P2M_TOP_PER_PAGE * P2M_MID_PER_PAGE * P2M_PER_PAGE)

#घोषणा PMDS_PER_MID_PAGE	(P2M_MID_PER_PAGE / PTRS_PER_PTE)

अचिन्हित दीर्घ *xen_p2m_addr __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(xen_p2m_addr);
अचिन्हित दीर्घ xen_p2m_size __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(xen_p2m_size);
अचिन्हित दीर्घ xen_max_p2m_pfn __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(xen_max_p2m_pfn);

#अगर_घोषित CONFIG_XEN_MEMORY_HOTPLUG_LIMIT
#घोषणा P2M_LIMIT CONFIG_XEN_MEMORY_HOTPLUG_LIMIT
#अन्यथा
#घोषणा P2M_LIMIT 0
#पूर्ण_अगर

अटल DEFINE_SPINLOCK(p2m_update_lock);

अटल अचिन्हित दीर्घ *p2m_mid_missing_mfn;
अटल अचिन्हित दीर्घ *p2m_top_mfn;
अटल अचिन्हित दीर्घ **p2m_top_mfn_p;
अटल अचिन्हित दीर्घ *p2m_missing;
अटल अचिन्हित दीर्घ *p2m_identity;
अटल pte_t *p2m_missing_pte;
अटल pte_t *p2m_identity_pte;

/*
 * Hपूर्णांक at last populated PFN.
 *
 * Used to set HYPERVISOR_shared_info->arch.max_pfn so the toolstack
 * can aव्योम scanning the whole P2M (which may be sized to account क्रम
 * hotplugged memory).
 */
अटल अचिन्हित दीर्घ xen_p2m_last_pfn;

अटल अंतरभूत अचिन्हित p2m_top_index(अचिन्हित दीर्घ pfn)
अणु
	BUG_ON(pfn >= MAX_P2M_PFN);
	वापस pfn / (P2M_MID_PER_PAGE * P2M_PER_PAGE);
पूर्ण

अटल अंतरभूत अचिन्हित p2m_mid_index(अचिन्हित दीर्घ pfn)
अणु
	वापस (pfn / P2M_PER_PAGE) % P2M_MID_PER_PAGE;
पूर्ण

अटल अंतरभूत अचिन्हित p2m_index(अचिन्हित दीर्घ pfn)
अणु
	वापस pfn % P2M_PER_PAGE;
पूर्ण

अटल व्योम p2m_top_mfn_init(अचिन्हित दीर्घ *top)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < P2M_TOP_PER_PAGE; i++)
		top[i] = virt_to_mfn(p2m_mid_missing_mfn);
पूर्ण

अटल व्योम p2m_top_mfn_p_init(अचिन्हित दीर्घ **top)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < P2M_TOP_PER_PAGE; i++)
		top[i] = p2m_mid_missing_mfn;
पूर्ण

अटल व्योम p2m_mid_mfn_init(अचिन्हित दीर्घ *mid, अचिन्हित दीर्घ *leaf)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < P2M_MID_PER_PAGE; i++)
		mid[i] = virt_to_mfn(leaf);
पूर्ण

अटल व्योम p2m_init(अचिन्हित दीर्घ *p2m)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < P2M_PER_PAGE; i++)
		p2m[i] = INVALID_P2M_ENTRY;
पूर्ण

अटल व्योम p2m_init_identity(अचिन्हित दीर्घ *p2m, अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < P2M_PER_PAGE; i++)
		p2m[i] = IDENTITY_FRAME(pfn + i);
पूर्ण

अटल व्योम * __ref alloc_p2m_page(व्योम)
अणु
	अगर (unlikely(!slab_is_available())) अणु
		व्योम *ptr = memblock_alloc(PAGE_SIZE, PAGE_SIZE);

		अगर (!ptr)
			panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
			      __func__, PAGE_SIZE, PAGE_SIZE);

		वापस ptr;
	पूर्ण

	वापस (व्योम *)__get_मुक्त_page(GFP_KERNEL);
पूर्ण

अटल व्योम __ref मुक्त_p2m_page(व्योम *p)
अणु
	अगर (unlikely(!slab_is_available())) अणु
		memblock_मुक्त((अचिन्हित दीर्घ)p, PAGE_SIZE);
		वापस;
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ)p);
पूर्ण

/*
 * Build the parallel p2m_top_mfn and p2m_mid_mfn काष्ठाures
 *
 * This is called both at boot समय, and after resuming from suspend:
 * - At boot समय we're called rather early, and must use alloc_booपंचांगem*()
 *   to allocate memory.
 *
 * - After resume we're called from within stop_machine, but the mfn
 *   tree should alपढ़ोy be completely allocated.
 */
व्योम __ref xen_build_mfn_list_list(व्योम)
अणु
	अचिन्हित दीर्घ pfn, mfn;
	pte_t *ptep;
	अचिन्हित पूर्णांक level, topidx, mididx;
	अचिन्हित दीर्घ *mid_mfn_p;

	अगर (xen_start_info->flags & SIF_VIRT_P2M_4TOOLS)
		वापस;

	/* Pre-initialize p2m_top_mfn to be completely missing */
	अगर (p2m_top_mfn == शून्य) अणु
		p2m_mid_missing_mfn = alloc_p2m_page();
		p2m_mid_mfn_init(p2m_mid_missing_mfn, p2m_missing);

		p2m_top_mfn_p = alloc_p2m_page();
		p2m_top_mfn_p_init(p2m_top_mfn_p);

		p2m_top_mfn = alloc_p2m_page();
		p2m_top_mfn_init(p2m_top_mfn);
	पूर्ण अन्यथा अणु
		/* Reinitialise, mfn's all change after migration */
		p2m_mid_mfn_init(p2m_mid_missing_mfn, p2m_missing);
	पूर्ण

	क्रम (pfn = 0; pfn < xen_max_p2m_pfn && pfn < MAX_P2M_PFN;
	     pfn += P2M_PER_PAGE) अणु
		topidx = p2m_top_index(pfn);
		mididx = p2m_mid_index(pfn);

		mid_mfn_p = p2m_top_mfn_p[topidx];
		ptep = lookup_address((अचिन्हित दीर्घ)(xen_p2m_addr + pfn),
				      &level);
		BUG_ON(!ptep || level != PG_LEVEL_4K);
		mfn = pte_mfn(*ptep);
		ptep = (pte_t *)((अचिन्हित दीर्घ)ptep & ~(PAGE_SIZE - 1));

		/* Don't bother allocating any mfn mid levels अगर
		 * they're just missing, just update the stored mfn,
		 * since all could have changed over a migrate.
		 */
		अगर (ptep == p2m_missing_pte || ptep == p2m_identity_pte) अणु
			BUG_ON(mididx);
			BUG_ON(mid_mfn_p != p2m_mid_missing_mfn);
			p2m_top_mfn[topidx] = virt_to_mfn(p2m_mid_missing_mfn);
			pfn += (P2M_MID_PER_PAGE - 1) * P2M_PER_PAGE;
			जारी;
		पूर्ण

		अगर (mid_mfn_p == p2m_mid_missing_mfn) अणु
			mid_mfn_p = alloc_p2m_page();
			p2m_mid_mfn_init(mid_mfn_p, p2m_missing);

			p2m_top_mfn_p[topidx] = mid_mfn_p;
		पूर्ण

		p2m_top_mfn[topidx] = virt_to_mfn(mid_mfn_p);
		mid_mfn_p[mididx] = mfn;
	पूर्ण
पूर्ण

व्योम xen_setup_mfn_list_list(व्योम)
अणु
	BUG_ON(HYPERVISOR_shared_info == &xen_dummy_shared_info);

	अगर (xen_start_info->flags & SIF_VIRT_P2M_4TOOLS)
		HYPERVISOR_shared_info->arch.pfn_to_mfn_frame_list_list = ~0UL;
	अन्यथा
		HYPERVISOR_shared_info->arch.pfn_to_mfn_frame_list_list =
			virt_to_mfn(p2m_top_mfn);
	HYPERVISOR_shared_info->arch.max_pfn = xen_p2m_last_pfn;
	HYPERVISOR_shared_info->arch.p2m_generation = 0;
	HYPERVISOR_shared_info->arch.p2m_vaddr = (अचिन्हित दीर्घ)xen_p2m_addr;
	HYPERVISOR_shared_info->arch.p2m_cr3 =
		xen_pfn_to_cr3(virt_to_mfn(swapper_pg_dir));
पूर्ण

/* Set up p2m_top to poपूर्णांक to the करोमुख्य-builder provided p2m pages */
व्योम __init xen_build_dynamic_phys_to_machine(व्योम)
अणु
	अचिन्हित दीर्घ pfn;

	xen_p2m_addr = (अचिन्हित दीर्घ *)xen_start_info->mfn_list;
	xen_p2m_size = ALIGN(xen_start_info->nr_pages, P2M_PER_PAGE);

	क्रम (pfn = xen_start_info->nr_pages; pfn < xen_p2m_size; pfn++)
		xen_p2m_addr[pfn] = INVALID_P2M_ENTRY;

	xen_max_p2m_pfn = xen_p2m_size;
पूर्ण

#घोषणा P2M_TYPE_IDENTITY	0
#घोषणा P2M_TYPE_MISSING	1
#घोषणा P2M_TYPE_PFN		2
#घोषणा P2M_TYPE_UNKNOWN	3

अटल पूर्णांक xen_p2m_elem_type(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ mfn;

	अगर (pfn >= xen_p2m_size)
		वापस P2M_TYPE_IDENTITY;

	mfn = xen_p2m_addr[pfn];

	अगर (mfn == INVALID_P2M_ENTRY)
		वापस P2M_TYPE_MISSING;

	अगर (mfn & IDENTITY_FRAME_BIT)
		वापस P2M_TYPE_IDENTITY;

	वापस P2M_TYPE_PFN;
पूर्ण

अटल व्योम __init xen_rebuild_p2m_list(अचिन्हित दीर्घ *p2m)
अणु
	अचिन्हित पूर्णांक i, chunk;
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ *mfns;
	pte_t *ptep;
	pmd_t *pmdp;
	पूर्णांक type;

	p2m_missing = alloc_p2m_page();
	p2m_init(p2m_missing);
	p2m_identity = alloc_p2m_page();
	p2m_init(p2m_identity);

	p2m_missing_pte = alloc_p2m_page();
	paravirt_alloc_pte(&init_mm, __pa(p2m_missing_pte) >> PAGE_SHIFT);
	p2m_identity_pte = alloc_p2m_page();
	paravirt_alloc_pte(&init_mm, __pa(p2m_identity_pte) >> PAGE_SHIFT);
	क्रम (i = 0; i < PTRS_PER_PTE; i++) अणु
		set_pte(p2m_missing_pte + i,
			pfn_pte(PFN_DOWN(__pa(p2m_missing)), PAGE_KERNEL_RO));
		set_pte(p2m_identity_pte + i,
			pfn_pte(PFN_DOWN(__pa(p2m_identity)), PAGE_KERNEL_RO));
	पूर्ण

	क्रम (pfn = 0; pfn < xen_max_p2m_pfn; pfn += chunk) अणु
		/*
		 * Try to map missing/identity PMDs or p2m-pages अगर possible.
		 * We have to respect the काष्ठाure of the mfn_list_list
		 * which will be built just afterwards.
		 * Chunk size to test is one p2m page अगर we are in the middle
		 * of a mfn_list_list mid page and the complete mid page area
		 * अगर we are at index 0 of the mid page. Please note that a
		 * mid page might cover more than one PMD, e.g. on 32 bit PAE
		 * kernels.
		 */
		chunk = (pfn & (P2M_PER_PAGE * P2M_MID_PER_PAGE - 1)) ?
			P2M_PER_PAGE : P2M_PER_PAGE * P2M_MID_PER_PAGE;

		type = xen_p2m_elem_type(pfn);
		i = 0;
		अगर (type != P2M_TYPE_PFN)
			क्रम (i = 1; i < chunk; i++)
				अगर (xen_p2m_elem_type(pfn + i) != type)
					अवरोध;
		अगर (i < chunk)
			/* Reset to minimal chunk size. */
			chunk = P2M_PER_PAGE;

		अगर (type == P2M_TYPE_PFN || i < chunk) अणु
			/* Use initial p2m page contents. */
			mfns = alloc_p2m_page();
			copy_page(mfns, xen_p2m_addr + pfn);
			ptep = populate_extra_pte((अचिन्हित दीर्घ)(p2m + pfn));
			set_pte(ptep,
				pfn_pte(PFN_DOWN(__pa(mfns)), PAGE_KERNEL));
			जारी;
		पूर्ण

		अगर (chunk == P2M_PER_PAGE) अणु
			/* Map complete missing or identity p2m-page. */
			mfns = (type == P2M_TYPE_MISSING) ?
				p2m_missing : p2m_identity;
			ptep = populate_extra_pte((अचिन्हित दीर्घ)(p2m + pfn));
			set_pte(ptep,
				pfn_pte(PFN_DOWN(__pa(mfns)), PAGE_KERNEL_RO));
			जारी;
		पूर्ण

		/* Complete missing or identity PMD(s) can be mapped. */
		ptep = (type == P2M_TYPE_MISSING) ?
			p2m_missing_pte : p2m_identity_pte;
		क्रम (i = 0; i < PMDS_PER_MID_PAGE; i++) अणु
			pmdp = populate_extra_pmd(
				(अचिन्हित दीर्घ)(p2m + pfn) + i * PMD_SIZE);
			set_pmd(pmdp, __pmd(__pa(ptep) | _KERNPG_TABLE));
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init xen_vदो_स्मृति_p2m_tree(व्योम)
अणु
	अटल काष्ठा vm_काष्ठा vm;
	अचिन्हित दीर्घ p2m_limit;

	xen_p2m_last_pfn = xen_max_p2m_pfn;

	p2m_limit = (phys_addr_t)P2M_LIMIT * 1024 * 1024 * 1024 / PAGE_SIZE;
	vm.flags = VM_ALLOC;
	vm.size = ALIGN(माप(अचिन्हित दीर्घ) * max(xen_max_p2m_pfn, p2m_limit),
			PMD_SIZE * PMDS_PER_MID_PAGE);
	vm_area_रेजिस्टर_early(&vm, PMD_SIZE * PMDS_PER_MID_PAGE);
	pr_notice("p2m virtual area at %p, size is %lx\n", vm.addr, vm.size);

	xen_max_p2m_pfn = vm.size / माप(अचिन्हित दीर्घ);

	xen_rebuild_p2m_list(vm.addr);

	xen_p2m_addr = vm.addr;
	xen_p2m_size = xen_max_p2m_pfn;

	xen_inv_extra_mem();
पूर्ण

अचिन्हित दीर्घ get_phys_to_machine(अचिन्हित दीर्घ pfn)
अणु
	pte_t *ptep;
	अचिन्हित पूर्णांक level;

	अगर (unlikely(pfn >= xen_p2m_size)) अणु
		अगर (pfn < xen_max_p2m_pfn)
			वापस xen_chk_extra_mem(pfn);

		वापस IDENTITY_FRAME(pfn);
	पूर्ण

	ptep = lookup_address((अचिन्हित दीर्घ)(xen_p2m_addr + pfn), &level);
	BUG_ON(!ptep || level != PG_LEVEL_4K);

	/*
	 * The INVALID_P2M_ENTRY is filled in both p2m_*identity
	 * and in p2m_*missing, so वापसing the INVALID_P2M_ENTRY
	 * would be wrong.
	 */
	अगर (pte_pfn(*ptep) == PFN_DOWN(__pa(p2m_identity)))
		वापस IDENTITY_FRAME(pfn);

	वापस xen_p2m_addr[pfn];
पूर्ण
EXPORT_SYMBOL_GPL(get_phys_to_machine);

/*
 * Allocate new pmd(s). It is checked whether the old pmd is still in place.
 * If not, nothing is changed. This is okay as the only reason क्रम allocating
 * a new pmd is to replace p2m_missing_pte or p2m_identity_pte by a inभागidual
 * pmd.
 */
अटल pte_t *alloc_p2m_pmd(अचिन्हित दीर्घ addr, pte_t *pte_pg)
अणु
	pte_t *ptechk;
	pte_t *pte_newpg[PMDS_PER_MID_PAGE];
	pmd_t *pmdp;
	अचिन्हित पूर्णांक level;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ vaddr;
	पूर्णांक i;

	/* Do all allocations first to bail out in error हाल. */
	क्रम (i = 0; i < PMDS_PER_MID_PAGE; i++) अणु
		pte_newpg[i] = alloc_p2m_page();
		अगर (!pte_newpg[i]) अणु
			क्रम (i--; i >= 0; i--)
				मुक्त_p2m_page(pte_newpg[i]);

			वापस शून्य;
		पूर्ण
	पूर्ण

	vaddr = addr & ~(PMD_SIZE * PMDS_PER_MID_PAGE - 1);

	क्रम (i = 0; i < PMDS_PER_MID_PAGE; i++) अणु
		copy_page(pte_newpg[i], pte_pg);
		paravirt_alloc_pte(&init_mm, __pa(pte_newpg[i]) >> PAGE_SHIFT);

		pmdp = lookup_pmd_address(vaddr);
		BUG_ON(!pmdp);

		spin_lock_irqsave(&p2m_update_lock, flags);

		ptechk = lookup_address(vaddr, &level);
		अगर (ptechk == pte_pg) अणु
			HYPERVISOR_shared_info->arch.p2m_generation++;
			wmb(); /* Tools are synchronizing via p2m_generation. */
			set_pmd(pmdp,
				__pmd(__pa(pte_newpg[i]) | _KERNPG_TABLE));
			wmb(); /* Tools are synchronizing via p2m_generation. */
			HYPERVISOR_shared_info->arch.p2m_generation++;
			pte_newpg[i] = शून्य;
		पूर्ण

		spin_unlock_irqrestore(&p2m_update_lock, flags);

		अगर (pte_newpg[i]) अणु
			paravirt_release_pte(__pa(pte_newpg[i]) >> PAGE_SHIFT);
			मुक्त_p2m_page(pte_newpg[i]);
		पूर्ण

		vaddr += PMD_SIZE;
	पूर्ण

	वापस lookup_address(addr, &level);
पूर्ण

/*
 * Fully allocate the p2m काष्ठाure क्रम a given pfn.  We need to check
 * that both the top and mid levels are allocated, and make sure the
 * parallel mfn tree is kept in sync.  We may race with other cpus, so
 * the new pages are installed with cmpxchg; अगर we lose the race then
 * simply मुक्त the page we allocated and use the one that's there.
 */
पूर्णांक xen_alloc_p2m_entry(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित topidx;
	अचिन्हित दीर्घ *top_mfn_p, *mid_mfn;
	pte_t *ptep, *pte_pg;
	अचिन्हित पूर्णांक level;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)(xen_p2m_addr + pfn);
	अचिन्हित दीर्घ p2m_pfn;

	ptep = lookup_address(addr, &level);
	BUG_ON(!ptep || level != PG_LEVEL_4K);
	pte_pg = (pte_t *)((अचिन्हित दीर्घ)ptep & ~(PAGE_SIZE - 1));

	अगर (pte_pg == p2m_missing_pte || pte_pg == p2m_identity_pte) अणु
		/* PMD level is missing, allocate a new one */
		ptep = alloc_p2m_pmd(addr, pte_pg);
		अगर (!ptep)
			वापस -ENOMEM;
	पूर्ण

	अगर (p2m_top_mfn && pfn < MAX_P2M_PFN) अणु
		topidx = p2m_top_index(pfn);
		top_mfn_p = &p2m_top_mfn[topidx];
		mid_mfn = READ_ONCE(p2m_top_mfn_p[topidx]);

		BUG_ON(virt_to_mfn(mid_mfn) != *top_mfn_p);

		अगर (mid_mfn == p2m_mid_missing_mfn) अणु
			/* Separately check the mid mfn level */
			अचिन्हित दीर्घ missing_mfn;
			अचिन्हित दीर्घ mid_mfn_mfn;
			अचिन्हित दीर्घ old_mfn;

			mid_mfn = alloc_p2m_page();
			अगर (!mid_mfn)
				वापस -ENOMEM;

			p2m_mid_mfn_init(mid_mfn, p2m_missing);

			missing_mfn = virt_to_mfn(p2m_mid_missing_mfn);
			mid_mfn_mfn = virt_to_mfn(mid_mfn);
			old_mfn = cmpxchg(top_mfn_p, missing_mfn, mid_mfn_mfn);
			अगर (old_mfn != missing_mfn) अणु
				मुक्त_p2m_page(mid_mfn);
				mid_mfn = mfn_to_virt(old_mfn);
			पूर्ण अन्यथा अणु
				p2m_top_mfn_p[topidx] = mid_mfn;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		mid_mfn = शून्य;
	पूर्ण

	p2m_pfn = pte_pfn(READ_ONCE(*ptep));
	अगर (p2m_pfn == PFN_DOWN(__pa(p2m_identity)) ||
	    p2m_pfn == PFN_DOWN(__pa(p2m_missing))) अणु
		/* p2m leaf page is missing */
		अचिन्हित दीर्घ *p2m;

		p2m = alloc_p2m_page();
		अगर (!p2m)
			वापस -ENOMEM;

		अगर (p2m_pfn == PFN_DOWN(__pa(p2m_missing)))
			p2m_init(p2m);
		अन्यथा
			p2m_init_identity(p2m, pfn & ~(P2M_PER_PAGE - 1));

		spin_lock_irqsave(&p2m_update_lock, flags);

		अगर (pte_pfn(*ptep) == p2m_pfn) अणु
			HYPERVISOR_shared_info->arch.p2m_generation++;
			wmb(); /* Tools are synchronizing via p2m_generation. */
			set_pte(ptep,
				pfn_pte(PFN_DOWN(__pa(p2m)), PAGE_KERNEL));
			wmb(); /* Tools are synchronizing via p2m_generation. */
			HYPERVISOR_shared_info->arch.p2m_generation++;
			अगर (mid_mfn)
				mid_mfn[p2m_mid_index(pfn)] = virt_to_mfn(p2m);
			p2m = शून्य;
		पूर्ण

		spin_unlock_irqrestore(&p2m_update_lock, flags);

		अगर (p2m)
			मुक्त_p2m_page(p2m);
	पूर्ण

	/* Expanded the p2m? */
	अगर (pfn > xen_p2m_last_pfn) अणु
		xen_p2m_last_pfn = pfn;
		HYPERVISOR_shared_info->arch.max_pfn = xen_p2m_last_pfn;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xen_alloc_p2m_entry);

अचिन्हित दीर्घ __init set_phys_range_identity(अचिन्हित दीर्घ pfn_s,
				      अचिन्हित दीर्घ pfn_e)
अणु
	अचिन्हित दीर्घ pfn;

	अगर (unlikely(pfn_s >= xen_p2m_size))
		वापस 0;

	अगर (pfn_s > pfn_e)
		वापस 0;

	अगर (pfn_e > xen_p2m_size)
		pfn_e = xen_p2m_size;

	क्रम (pfn = pfn_s; pfn < pfn_e; pfn++)
		xen_p2m_addr[pfn] = IDENTITY_FRAME(pfn);

	वापस pfn - pfn_s;
पूर्ण

bool __set_phys_to_machine(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ mfn)
अणु
	pte_t *ptep;
	अचिन्हित पूर्णांक level;

	/* Only invalid entries allowed above the highest p2m covered frame. */
	अगर (unlikely(pfn >= xen_p2m_size))
		वापस mfn == INVALID_P2M_ENTRY;

	/*
	 * The पूर्णांकerface requires atomic updates on p2m elements.
	 * xen_safe_ग_लिखो_uदीर्घ() is using an atomic store via यंत्र().
	 */
	अगर (likely(!xen_safe_ग_लिखो_uदीर्घ(xen_p2m_addr + pfn, mfn)))
		वापस true;

	ptep = lookup_address((अचिन्हित दीर्घ)(xen_p2m_addr + pfn), &level);
	BUG_ON(!ptep || level != PG_LEVEL_4K);

	अगर (pte_pfn(*ptep) == PFN_DOWN(__pa(p2m_missing)))
		वापस mfn == INVALID_P2M_ENTRY;

	अगर (pte_pfn(*ptep) == PFN_DOWN(__pa(p2m_identity)))
		वापस mfn == IDENTITY_FRAME(pfn);

	वापस false;
पूर्ण

bool set_phys_to_machine(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ mfn)
अणु
	अगर (unlikely(!__set_phys_to_machine(pfn, mfn))) अणु
		पूर्णांक ret;

		ret = xen_alloc_p2m_entry(pfn);
		अगर (ret < 0)
			वापस false;

		वापस __set_phys_to_machine(pfn, mfn);
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक set_क्रमeign_p2m_mapping(काष्ठा gnttab_map_grant_ref *map_ops,
			    काष्ठा gnttab_map_grant_ref *kmap_ops,
			    काष्ठा page **pages, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i, ret = 0;
	pte_t *pte;

	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस 0;

	अगर (kmap_ops) अणु
		ret = HYPERVISOR_grant_table_op(GNTTABOP_map_grant_ref,
						kmap_ops, count);
		अगर (ret)
			जाओ out;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		अचिन्हित दीर्घ mfn, pfn;
		काष्ठा gnttab_unmap_grant_ref unmap[2];
		पूर्णांक rc;

		/* Do not add to override अगर the map failed. */
		अगर (map_ops[i].status != GNTST_okay ||
		    (kmap_ops && kmap_ops[i].status != GNTST_okay))
			जारी;

		अगर (map_ops[i].flags & GNTMAP_contains_pte) अणु
			pte = (pte_t *)(mfn_to_virt(PFN_DOWN(map_ops[i].host_addr)) +
				(map_ops[i].host_addr & ~PAGE_MASK));
			mfn = pte_mfn(*pte);
		पूर्ण अन्यथा अणु
			mfn = PFN_DOWN(map_ops[i].dev_bus_addr);
		पूर्ण
		pfn = page_to_pfn(pages[i]);

		WARN(pfn_to_mfn(pfn) != INVALID_P2M_ENTRY, "page must be ballooned");

		अगर (likely(set_phys_to_machine(pfn, FOREIGN_FRAME(mfn))))
			जारी;

		/*
		 * Signal an error क्रम this slot. This in turn requires
		 * immediate unmapping.
		 */
		map_ops[i].status = GNTST_general_error;
		unmap[0].host_addr = map_ops[i].host_addr,
		unmap[0].handle = map_ops[i].handle;
		map_ops[i].handle = INVALID_GRANT_HANDLE;
		अगर (map_ops[i].flags & GNTMAP_device_map)
			unmap[0].dev_bus_addr = map_ops[i].dev_bus_addr;
		अन्यथा
			unmap[0].dev_bus_addr = 0;

		अगर (kmap_ops) अणु
			kmap_ops[i].status = GNTST_general_error;
			unmap[1].host_addr = kmap_ops[i].host_addr,
			unmap[1].handle = kmap_ops[i].handle;
			kmap_ops[i].handle = INVALID_GRANT_HANDLE;
			अगर (kmap_ops[i].flags & GNTMAP_device_map)
				unmap[1].dev_bus_addr = kmap_ops[i].dev_bus_addr;
			अन्यथा
				unmap[1].dev_bus_addr = 0;
		पूर्ण

		/*
		 * Pre-populate both status fields, to be recognizable in
		 * the log message below.
		 */
		unmap[0].status = 1;
		unmap[1].status = 1;

		rc = HYPERVISOR_grant_table_op(GNTTABOP_unmap_grant_ref,
					       unmap, 1 + !!kmap_ops);
		अगर (rc || unmap[0].status != GNTST_okay ||
		    unmap[1].status != GNTST_okay)
			pr_err_once("gnttab unmap failed: rc=%d st0=%d st1=%d\n",
				    rc, unmap[0].status, unmap[1].status);
	पूर्ण

out:
	वापस ret;
पूर्ण

पूर्णांक clear_क्रमeign_p2m_mapping(काष्ठा gnttab_unmap_grant_ref *unmap_ops,
			      काष्ठा gnttab_unmap_grant_ref *kunmap_ops,
			      काष्ठा page **pages, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i, ret = 0;

	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस 0;

	क्रम (i = 0; i < count; i++) अणु
		अचिन्हित दीर्घ mfn = __pfn_to_mfn(page_to_pfn(pages[i]));
		अचिन्हित दीर्घ pfn = page_to_pfn(pages[i]);

		अगर (mfn != INVALID_P2M_ENTRY && (mfn & FOREIGN_FRAME_BIT))
			set_phys_to_machine(pfn, INVALID_P2M_ENTRY);
		अन्यथा
			ret = -EINVAL;
	पूर्ण
	अगर (kunmap_ops)
		ret = HYPERVISOR_grant_table_op(GNTTABOP_unmap_grant_ref,
						kunmap_ops, count) ?: ret;

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_XEN_DEBUG_FS
#समावेश <linux/debugfs.h>
#समावेश "debugfs.h"
अटल पूर्णांक p2m_dump_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अटल स्थिर अक्षर * स्थिर type_name[] = अणु
				[P2M_TYPE_IDENTITY] = "identity",
				[P2M_TYPE_MISSING] = "missing",
				[P2M_TYPE_PFN] = "pfn",
				[P2M_TYPE_UNKNOWN] = "abnormal"पूर्ण;
	अचिन्हित दीर्घ pfn, first_pfn;
	पूर्णांक type, prev_type;

	prev_type = xen_p2m_elem_type(0);
	first_pfn = 0;

	क्रम (pfn = 0; pfn < xen_p2m_size; pfn++) अणु
		type = xen_p2m_elem_type(pfn);
		अगर (type != prev_type) अणु
			seq_म_लिखो(m, " [0x%lx->0x%lx] %s\n", first_pfn, pfn,
				   type_name[prev_type]);
			prev_type = type;
			first_pfn = pfn;
		पूर्ण
	पूर्ण
	seq_म_लिखो(m, " [0x%lx->0x%lx] %s\n", first_pfn, pfn,
		   type_name[prev_type]);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(p2m_dump);

अटल काष्ठा dentry *d_mmu_debug;

अटल पूर्णांक __init xen_p2m_debugfs(व्योम)
अणु
	काष्ठा dentry *d_xen = xen_init_debugfs();

	d_mmu_debug = debugfs_create_dir("mmu", d_xen);

	debugfs_create_file("p2m", 0600, d_mmu_debug, शून्य, &p2m_dump_fops);
	वापस 0;
पूर्ण
fs_initcall(xen_p2m_debugfs);
#पूर्ण_अगर /* CONFIG_XEN_DEBUG_FS */
