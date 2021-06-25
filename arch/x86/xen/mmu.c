<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/pfn.h>
#समावेश <यंत्र/xen/page.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <xen/पूर्णांकerface/memory.h>

#समावेश "multicalls.h"
#समावेश "mmu.h"

अचिन्हित दीर्घ arbitrary_virt_to_mfn(व्योम *vaddr)
अणु
	xmaddr_t maddr = arbitrary_virt_to_machine(vaddr);

	वापस PFN_DOWN(maddr.maddr);
पूर्ण

xmaddr_t arbitrary_virt_to_machine(व्योम *vaddr)
अणु
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)vaddr;
	अचिन्हित पूर्णांक level;
	pte_t *pte;
	अचिन्हित offset;

	/*
	 * अगर the PFN is in the linear mapped vaddr range, we can just use
	 * the (quick) virt_to_machine() p2m lookup
	 */
	अगर (virt_addr_valid(vaddr))
		वापस virt_to_machine(vaddr);

	/* otherwise we have to करो a (slower) full page-table walk */

	pte = lookup_address(address, &level);
	BUG_ON(pte == शून्य);
	offset = address & ~PAGE_MASK;
	वापस XMADDR(((phys_addr_t)pte_mfn(*pte) << PAGE_SHIFT) + offset);
पूर्ण
EXPORT_SYMBOL_GPL(arbitrary_virt_to_machine);

/* Returns: 0 success */
पूर्णांक xen_unmap_करोमुख्य_gfn_range(काष्ठा vm_area_काष्ठा *vma,
			       पूर्णांक nr, काष्ठा page **pages)
अणु
	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस xen_xlate_unmap_gfn_range(vma, nr, pages);

	अगर (!pages)
		वापस 0;

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(xen_unmap_करोमुख्य_gfn_range);
