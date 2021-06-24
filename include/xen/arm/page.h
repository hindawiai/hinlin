<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARM_XEN_PAGE_H
#घोषणा _ASM_ARM_XEN_PAGE_H

#समावेश <यंत्र/page.h>

#समावेश <linux/pfn.h>
#समावेश <linux/types.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pgtable.h>

#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/grant_table.h>

#घोषणा phys_to_machine_mapping_valid(pfn) (1)

/* Xen machine address */
प्रकार काष्ठा xmaddr अणु
	phys_addr_t maddr;
पूर्ण xmaddr_t;

/* Xen pseuकरो-physical address */
प्रकार काष्ठा xpaddr अणु
	phys_addr_t paddr;
पूर्ण xpaddr_t;

#घोषणा XMADDR(x)	((xmaddr_t) अणु .maddr = (x) पूर्ण)
#घोषणा XPADDR(x)	((xpaddr_t) अणु .paddr = (x) पूर्ण)

#घोषणा INVALID_P2M_ENTRY      (~0UL)

/*
 * The pseuकरो-physical frame (pfn) used in all the helpers is always based
 * on Xen page granularity (i.e 4KB).
 *
 * A Linux page may be split across multiple non-contiguous Xen page so we
 * have to keep track with frame based on 4KB page granularity.
 *
 * PV drivers should never make a direct usage of those helpers (particularly
 * pfn_to_gfn and gfn_to_pfn).
 */

अचिन्हित दीर्घ __pfn_to_mfn(अचिन्हित दीर्घ pfn);
बाह्य काष्ठा rb_root phys_to_mach;

/* Pseuकरो-physical <-> Guest conversion */
अटल अंतरभूत अचिन्हित दीर्घ pfn_to_gfn(अचिन्हित दीर्घ pfn)
अणु
	वापस pfn;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ gfn_to_pfn(अचिन्हित दीर्घ gfn)
अणु
	वापस gfn;
पूर्ण

/* Pseuकरो-physical <-> BUS conversion */
अटल अंतरभूत अचिन्हित दीर्घ pfn_to_bfn(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ mfn;

	अगर (phys_to_mach.rb_node != शून्य) अणु
		mfn = __pfn_to_mfn(pfn);
		अगर (mfn != INVALID_P2M_ENTRY)
			वापस mfn;
	पूर्ण

	वापस pfn;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ bfn_to_pfn(अचिन्हित दीर्घ bfn)
अणु
	वापस bfn;
पूर्ण

#घोषणा bfn_to_local_pfn(bfn)	bfn_to_pfn(bfn)

/* VIRT <-> GUEST conversion */
#घोषणा virt_to_gfn(v)                                                         \
	(अणु                                                                     \
		WARN_ON_ONCE(!virt_addr_valid(v));                              \
		pfn_to_gfn(virt_to_phys(v) >> XEN_PAGE_SHIFT);                 \
	पूर्ण)
#घोषणा gfn_to_virt(m)		(__va(gfn_to_pfn(m) << XEN_PAGE_SHIFT))

#घोषणा percpu_to_gfn(v)	\
	(pfn_to_gfn(per_cpu_ptr_to_phys(v) >> XEN_PAGE_SHIFT))

/* Only used in PV code. But ARM guests are always HVM. */
अटल अंतरभूत xmaddr_t arbitrary_virt_to_machine(व्योम *vaddr)
अणु
	BUG();
पूर्ण

बाह्य पूर्णांक set_क्रमeign_p2m_mapping(काष्ठा gnttab_map_grant_ref *map_ops,
				   काष्ठा gnttab_map_grant_ref *kmap_ops,
				   काष्ठा page **pages, अचिन्हित पूर्णांक count);

बाह्य पूर्णांक clear_क्रमeign_p2m_mapping(काष्ठा gnttab_unmap_grant_ref *unmap_ops,
				     काष्ठा gnttab_unmap_grant_ref *kunmap_ops,
				     काष्ठा page **pages, अचिन्हित पूर्णांक count);

bool __set_phys_to_machine(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ mfn);
bool __set_phys_to_machine_multi(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ mfn,
		अचिन्हित दीर्घ nr_pages);

अटल अंतरभूत bool set_phys_to_machine(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ mfn)
अणु
	वापस __set_phys_to_machine(pfn, mfn);
पूर्ण

#घोषणा xen_remap(cookie, size) ioremap_cache((cookie), (size))
#घोषणा xen_unmap(cookie) iounmap((cookie))

bool xen_arch_need_swiotlb(काष्ठा device *dev,
			   phys_addr_t phys,
			   dma_addr_t dev_addr);
अचिन्हित दीर्घ xen_get_swiotlb_मुक्त_pages(अचिन्हित पूर्णांक order);

#पूर्ण_अगर /* _ASM_ARM_XEN_PAGE_H */
