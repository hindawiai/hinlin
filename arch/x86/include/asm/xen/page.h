<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_XEN_PAGE_H
#घोषणा _ASM_X86_XEN_PAGE_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pfn.h>
#समावेश <linux/mm.h>
#समावेश <linux/device.h>

#समावेश <यंत्र/extable.h>
#समावेश <यंत्र/page.h>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/grant_table.h>
#समावेश <xen/features.h>

/* Xen machine address */
प्रकार काष्ठा xmaddr अणु
	phys_addr_t maddr;
पूर्ण xmaddr_t;

/* Xen pseuकरो-physical address */
प्रकार काष्ठा xpaddr अणु
	phys_addr_t paddr;
पूर्ण xpaddr_t;

#अगर_घोषित CONFIG_X86_64
#घोषणा XEN_PHYSICAL_MASK	__sme_clr((1UL << 52) - 1)
#अन्यथा
#घोषणा XEN_PHYSICAL_MASK	__PHYSICAL_MASK
#पूर्ण_अगर

#घोषणा XEN_PTE_MFN_MASK	((pteval_t)(((चिन्हित दीर्घ)PAGE_MASK) & \
					    XEN_PHYSICAL_MASK))

#घोषणा XMADDR(x)	((xmaddr_t) अणु .maddr = (x) पूर्ण)
#घोषणा XPADDR(x)	((xpaddr_t) अणु .paddr = (x) पूर्ण)

/**** MACHINE <-> PHYSICAL CONVERSION MACROS ****/
#घोषणा INVALID_P2M_ENTRY	(~0UL)
#घोषणा FOREIGN_FRAME_BIT	(1UL<<(BITS_PER_LONG-1))
#घोषणा IDENTITY_FRAME_BIT	(1UL<<(BITS_PER_LONG-2))
#घोषणा FOREIGN_FRAME(m)	((m) | FOREIGN_FRAME_BIT)
#घोषणा IDENTITY_FRAME(m)	((m) | IDENTITY_FRAME_BIT)

#घोषणा P2M_PER_PAGE		(PAGE_SIZE / माप(अचिन्हित दीर्घ))

बाह्य अचिन्हित दीर्घ *machine_to_phys_mapping;
बाह्य अचिन्हित दीर्घ  machine_to_phys_nr;
बाह्य अचिन्हित दीर्घ *xen_p2m_addr;
बाह्य अचिन्हित दीर्घ  xen_p2m_size;
बाह्य अचिन्हित दीर्घ  xen_max_p2m_pfn;

बाह्य पूर्णांक xen_alloc_p2m_entry(अचिन्हित दीर्घ pfn);

बाह्य अचिन्हित दीर्घ get_phys_to_machine(अचिन्हित दीर्घ pfn);
बाह्य bool set_phys_to_machine(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ mfn);
बाह्य bool __set_phys_to_machine(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ mfn);
बाह्य अचिन्हित दीर्घ __init set_phys_range_identity(अचिन्हित दीर्घ pfn_s,
						    अचिन्हित दीर्घ pfn_e);

#अगर_घोषित CONFIG_XEN_PV
बाह्य पूर्णांक set_क्रमeign_p2m_mapping(काष्ठा gnttab_map_grant_ref *map_ops,
				   काष्ठा gnttab_map_grant_ref *kmap_ops,
				   काष्ठा page **pages, अचिन्हित पूर्णांक count);
बाह्य पूर्णांक clear_क्रमeign_p2m_mapping(काष्ठा gnttab_unmap_grant_ref *unmap_ops,
				     काष्ठा gnttab_unmap_grant_ref *kunmap_ops,
				     काष्ठा page **pages, अचिन्हित पूर्णांक count);
#अन्यथा
अटल अंतरभूत पूर्णांक
set_क्रमeign_p2m_mapping(काष्ठा gnttab_map_grant_ref *map_ops,
			काष्ठा gnttab_map_grant_ref *kmap_ops,
			काष्ठा page **pages, अचिन्हित पूर्णांक count)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
clear_क्रमeign_p2m_mapping(काष्ठा gnttab_unmap_grant_ref *unmap_ops,
			  काष्ठा gnttab_unmap_grant_ref *kunmap_ops,
			  काष्ठा page **pages, अचिन्हित पूर्णांक count)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Helper functions to ग_लिखो or पढ़ो अचिन्हित दीर्घ values to/from
 * memory, when the access may fault.
 */
अटल अंतरभूत पूर्णांक xen_safe_ग_लिखो_uदीर्घ(अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ val)
अणु
	पूर्णांक ret = 0;

	यंत्र अस्थिर("1: mov %[val], %[ptr]\n"
		     "2:\n"
		     ".section .fixup, \"ax\"\n"
		     "3: sub $1, %[ret]\n"
		     "   jmp 2b\n"
		     ".previous\n"
		     _ASM_EXTABLE(1b, 3b)
		     : [ret] "+r" (ret), [ptr] "=m" (*addr)
		     : [val] "r" (val));

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक xen_safe_पढ़ो_uदीर्घ(स्थिर अचिन्हित दीर्घ *addr,
				      अचिन्हित दीर्घ *val)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ rval = ~0ul;

	यंत्र अस्थिर("1: mov %[ptr], %[rval]\n"
		     "2:\n"
		     ".section .fixup, \"ax\"\n"
		     "3: sub $1, %[ret]\n"
		     "   jmp 2b\n"
		     ".previous\n"
		     _ASM_EXTABLE(1b, 3b)
		     : [ret] "+r" (ret), [rval] "+r" (rval)
		     : [ptr] "m" (*addr));
	*val = rval;

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_XEN_PV
/*
 * When to use pfn_to_mfn(), __pfn_to_mfn() or get_phys_to_machine():
 * - pfn_to_mfn() वापसs either INVALID_P2M_ENTRY or the mfn. No indicator
 *   bits (identity or क्रमeign) are set.
 * - __pfn_to_mfn() वापसs the found entry of the p2m table. A possibly set
 *   identity or क्रमeign indicator will be still set. __pfn_to_mfn() is
 *   encapsulating get_phys_to_machine() which is called in special हालs only.
 * - get_phys_to_machine() is to be called by __pfn_to_mfn() only in special
 *   हालs needing an extended handling.
 */
अटल अंतरभूत अचिन्हित दीर्घ __pfn_to_mfn(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ mfn;

	अगर (pfn < xen_p2m_size)
		mfn = xen_p2m_addr[pfn];
	अन्यथा अगर (unlikely(pfn < xen_max_p2m_pfn))
		वापस get_phys_to_machine(pfn);
	अन्यथा
		वापस IDENTITY_FRAME(pfn);

	अगर (unlikely(mfn == INVALID_P2M_ENTRY))
		वापस get_phys_to_machine(pfn);

	वापस mfn;
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ __pfn_to_mfn(अचिन्हित दीर्घ pfn)
अणु
	वापस pfn;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ pfn_to_mfn(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ mfn;

	/*
	 * Some x86 code are still using pfn_to_mfn instead of
	 * pfn_to_mfn. This will have to be हटाओd when we figured
	 * out which call.
	 */
	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस pfn;

	mfn = __pfn_to_mfn(pfn);

	अगर (mfn != INVALID_P2M_ENTRY)
		mfn &= ~(FOREIGN_FRAME_BIT | IDENTITY_FRAME_BIT);

	वापस mfn;
पूर्ण

अटल अंतरभूत पूर्णांक phys_to_machine_mapping_valid(अचिन्हित दीर्घ pfn)
अणु
	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस 1;

	वापस __pfn_to_mfn(pfn) != INVALID_P2M_ENTRY;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mfn_to_pfn_no_overrides(अचिन्हित दीर्घ mfn)
अणु
	अचिन्हित दीर्घ pfn;
	पूर्णांक ret;

	अगर (unlikely(mfn >= machine_to_phys_nr))
		वापस ~0;

	/*
	 * The array access can fail (e.g., device space beyond end of RAM).
	 * In such हालs it करोesn't matter what we वापस (we वापस garbage),
	 * but we must handle the fault without crashing!
	 */
	ret = xen_safe_पढ़ो_uदीर्घ(&machine_to_phys_mapping[mfn], &pfn);
	अगर (ret < 0)
		वापस ~0;

	वापस pfn;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mfn_to_pfn(अचिन्हित दीर्घ mfn)
अणु
	अचिन्हित दीर्घ pfn;

	/*
	 * Some x86 code are still using mfn_to_pfn instead of
	 * gfn_to_pfn. This will have to be हटाओd when we figure
	 * out which call.
	 */
	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस mfn;

	pfn = mfn_to_pfn_no_overrides(mfn);
	अगर (__pfn_to_mfn(pfn) != mfn)
		pfn = ~0;

	/*
	 * pfn is ~0 अगर there are no entries in the m2p क्रम mfn or the
	 * entry करोesn't map back to the mfn.
	 */
	अगर (pfn == ~0 && __pfn_to_mfn(mfn) == IDENTITY_FRAME(mfn))
		pfn = mfn;

	वापस pfn;
पूर्ण

अटल अंतरभूत xmaddr_t phys_to_machine(xpaddr_t phys)
अणु
	अचिन्हित offset = phys.paddr & ~PAGE_MASK;
	वापस XMADDR(PFN_PHYS(pfn_to_mfn(PFN_DOWN(phys.paddr))) | offset);
पूर्ण

अटल अंतरभूत xpaddr_t machine_to_phys(xmaddr_t machine)
अणु
	अचिन्हित offset = machine.maddr & ~PAGE_MASK;
	वापस XPADDR(PFN_PHYS(mfn_to_pfn(PFN_DOWN(machine.maddr))) | offset);
पूर्ण

/* Pseuकरो-physical <-> Guest conversion */
अटल अंतरभूत अचिन्हित दीर्घ pfn_to_gfn(अचिन्हित दीर्घ pfn)
अणु
	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस pfn;
	अन्यथा
		वापस pfn_to_mfn(pfn);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ gfn_to_pfn(अचिन्हित दीर्घ gfn)
अणु
	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस gfn;
	अन्यथा
		वापस mfn_to_pfn(gfn);
पूर्ण

/* Pseuकरो-physical <-> Bus conversion */
#घोषणा pfn_to_bfn(pfn)		pfn_to_gfn(pfn)
#घोषणा bfn_to_pfn(bfn)		gfn_to_pfn(bfn)

/*
 * We detect special mappings in one of two ways:
 *  1. If the MFN is an I/O page then Xen will set the m2p entry
 *     to be outside our maximum possible pseuकरोphys range.
 *  2. If the MFN beदीर्घs to a dअगरferent करोमुख्य then we will certainly
 *     not have MFN in our p2m table. Conversely, अगर the page is ours,
 *     then we'll have p2m(m2p(MFN))==MFN.
 * If we detect a special mapping then it करोesn't have a 'struct page'.
 * We क्रमce !pfn_valid() by वापसing an out-of-range poपूर्णांकer.
 *
 * NB. These checks require that, क्रम any MFN that is not in our reservation,
 * there is no PFN such that p2m(PFN) == MFN. Otherwise we can get confused अगर
 * we are क्रमeign-mapping the MFN, and the other करोमुख्य as m2p(MFN) == PFN.
 * Yikes! Various places must poke in INVALID_P2M_ENTRY क्रम safety.
 *
 * NB2. When deliberately mapping क्रमeign pages पूर्णांकo the p2m table, you *must*
 *      use FOREIGN_FRAME(). This will cause pte_pfn() to choke on it, as we
 *      require. In all the हालs we care about, the FOREIGN_FRAME bit is
 *      masked (e.g., pfn_to_mfn()) so behaviour there is correct.
 */
अटल अंतरभूत अचिन्हित दीर्घ bfn_to_local_pfn(अचिन्हित दीर्घ mfn)
अणु
	अचिन्हित दीर्घ pfn;

	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस mfn;

	pfn = mfn_to_pfn(mfn);
	अगर (__pfn_to_mfn(pfn) != mfn)
		वापस -1; /* क्रमce !pfn_valid() */
	वापस pfn;
पूर्ण

/* VIRT <-> MACHINE conversion */
#घोषणा virt_to_machine(v)	(phys_to_machine(XPADDR(__pa(v))))
#घोषणा virt_to_pfn(v)          (PFN_DOWN(__pa(v)))
#घोषणा virt_to_mfn(v)		(pfn_to_mfn(virt_to_pfn(v)))
#घोषणा mfn_to_virt(m)		(__va(mfn_to_pfn(m) << PAGE_SHIFT))

/* VIRT <-> GUEST conversion */
#घोषणा virt_to_gfn(v)		(pfn_to_gfn(virt_to_pfn(v)))
#घोषणा gfn_to_virt(g)		(__va(gfn_to_pfn(g) << PAGE_SHIFT))

अटल अंतरभूत अचिन्हित दीर्घ pte_mfn(pte_t pte)
अणु
	वापस (pte.pte & XEN_PTE_MFN_MASK) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत pte_t mfn_pte(अचिन्हित दीर्घ page_nr, pgprot_t pgprot)
अणु
	pte_t pte;

	pte.pte = ((phys_addr_t)page_nr << PAGE_SHIFT) |
			massage_pgprot(pgprot);

	वापस pte;
पूर्ण

अटल अंतरभूत pteval_t pte_val_ma(pte_t pte)
अणु
	वापस pte.pte;
पूर्ण

अटल अंतरभूत pte_t __pte_ma(pteval_t x)
अणु
	वापस (pte_t) अणु .pte = x पूर्ण;
पूर्ण

#घोषणा pmd_val_ma(v) ((v).pmd)
#अगर_घोषित __PAGETABLE_PUD_FOLDED
#घोषणा pud_val_ma(v) ((v).p4d.pgd.pgd)
#अन्यथा
#घोषणा pud_val_ma(v) ((v).pud)
#पूर्ण_अगर
#घोषणा __pmd_ma(x)	((pmd_t) अणु (x) पूर्ण )

#अगर_घोषित __PAGETABLE_P4D_FOLDED
#घोषणा p4d_val_ma(x)	((x).pgd.pgd)
#अन्यथा
#घोषणा p4d_val_ma(x)	((x).p4d)
#पूर्ण_अगर

xmaddr_t arbitrary_virt_to_machine(व्योम *address);
अचिन्हित दीर्घ arbitrary_virt_to_mfn(व्योम *vaddr);
व्योम make_lowmem_page_पढ़ोonly(व्योम *vaddr);
व्योम make_lowmem_page_पढ़ोग_लिखो(व्योम *vaddr);

#घोषणा xen_remap(cookie, size) ioremap((cookie), (size))
#घोषणा xen_unmap(cookie) iounmap((cookie))

अटल अंतरभूत bool xen_arch_need_swiotlb(काष्ठा device *dev,
					 phys_addr_t phys,
					 dma_addr_t dev_addr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xen_get_swiotlb_मुक्त_pages(अचिन्हित पूर्णांक order)
अणु
	वापस __get_मुक्त_pages(__GFP_NOWARN, order);
पूर्ण

#पूर्ण_अगर /* _ASM_X86_XEN_PAGE_H */
