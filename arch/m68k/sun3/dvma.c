<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/m68k/sun3/dvma.c
 *
 * Written by Sam Creasey
 *
 * Sun3 IOMMU routines used क्रम dvma accesses.
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/list.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sun3mmu.h>
#समावेश <यंत्र/dvma.h>


अटल अचिन्हित दीर्घ ptelist[120];

अटल अचिन्हित दीर्घ dvma_page(अचिन्हित दीर्घ kaddr, अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ pte;
	अचिन्हित दीर्घ j;
	pte_t ptep;

	j = *(अस्थिर अचिन्हित दीर्घ *)kaddr;
	*(अस्थिर अचिन्हित दीर्घ *)kaddr = j;

	ptep = pfn_pte(virt_to_pfn(kaddr), PAGE_KERNEL);
	pte = pte_val(ptep);
//	pr_info("dvma_remap: addr %lx -> %lx pte %08lx\n", kaddr, vaddr, pte);
	अगर(ptelist[(vaddr & 0xff000) >> PAGE_SHIFT] != pte) अणु
		sun3_put_pte(vaddr, pte);
		ptelist[(vaddr & 0xff000) >> PAGE_SHIFT] = pte;
	पूर्ण

	वापस (vaddr + (kaddr & ~PAGE_MASK));

पूर्ण

पूर्णांक dvma_map_iommu(अचिन्हित दीर्घ kaddr, अचिन्हित दीर्घ baddr,
			      पूर्णांक len)
अणु

	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ vaddr;

	vaddr = dvma_btov(baddr);

	end = vaddr + len;

	जबतक(vaddr < end) अणु
		dvma_page(kaddr, vaddr);
		kaddr += PAGE_SIZE;
		vaddr += PAGE_SIZE;
	पूर्ण

	वापस 0;

पूर्ण

व्योम __init sun3_dvma_init(व्योम)
अणु
	स_रखो(ptelist, 0, माप(ptelist));
पूर्ण
