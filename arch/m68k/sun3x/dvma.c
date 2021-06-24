<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Virtual DMA allocation
 *
 * (C) 1999 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 *
 * 11/26/2000 -- disabled the existing code because it didn't work क्रम
 * me in 2.4.  Replaced with a signअगरicantly more primitive version
 * similar to the sun3 code.  the old functionality was probably more
 * desirable, but....   -- Sam Creasey (sammy@oh.verio.com)
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/sun3x.h>
#समावेश <यंत्र/dvma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/tlbflush.h>

/* IOMMU support */

#घोषणा IOMMU_ADDR_MASK            0x03ffe000
#घोषणा IOMMU_CACHE_INHIBIT        0x00000040
#घोषणा IOMMU_FULL_BLOCK           0x00000020
#घोषणा IOMMU_MODIFIED             0x00000010
#घोषणा IOMMU_USED                 0x00000008
#घोषणा IOMMU_WRITE_PROTECT        0x00000004
#घोषणा IOMMU_DT_MASK              0x00000003
#घोषणा IOMMU_DT_INVALID           0x00000000
#घोषणा IOMMU_DT_VALID             0x00000001
#घोषणा IOMMU_DT_BAD               0x00000002


अटल अस्थिर अचिन्हित दीर्घ *iommu_pte = (अचिन्हित दीर्घ *)SUN3X_IOMMU;


#घोषणा dvma_entry_paddr(index)		(iommu_pte[index] & IOMMU_ADDR_MASK)
#घोषणा dvma_entry_vaddr(index,paddr)	((index << DVMA_PAGE_SHIFT) |  \
					 (paddr & (DVMA_PAGE_SIZE-1)))
#अगर 0
#घोषणा dvma_entry_set(index,addr)	(iommu_pte[index] =            \
					    (addr & IOMMU_ADDR_MASK) | \
				             IOMMU_DT_VALID | IOMMU_CACHE_INHIBIT)
#अन्यथा
#घोषणा dvma_entry_set(index,addr)	(iommu_pte[index] =            \
					    (addr & IOMMU_ADDR_MASK) | \
				             IOMMU_DT_VALID)
#पूर्ण_अगर
#घोषणा dvma_entry_clr(index)		(iommu_pte[index] = IOMMU_DT_INVALID)
#घोषणा dvma_entry_hash(addr)		((addr >> DVMA_PAGE_SHIFT) ^ \
					 ((addr & 0x03c00000) >>     \
						(DVMA_PAGE_SHIFT+4)))

#अगर_घोषित DEBUG
/* code to prपूर्णांक out a dvma mapping क्रम debugging purposes */
व्योम dvma_prपूर्णांक (अचिन्हित दीर्घ dvma_addr)
अणु

	अचिन्हित दीर्घ index;

	index = dvma_addr >> DVMA_PAGE_SHIFT;

	pr_info("idx %lx dvma_addr %08lx paddr %08lx\n", index, dvma_addr,
		dvma_entry_paddr(index));
पूर्ण
#पूर्ण_अगर


/* create a भव mapping क्रम a page asचिन्हित within the IOMMU
   so that the cpu can reach it easily */
अंतरभूत पूर्णांक dvma_map_cpu(अचिन्हित दीर्घ kaddr,
			       अचिन्हित दीर्घ vaddr, पूर्णांक len)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	अचिन्हित दीर्घ end;
	पूर्णांक ret = 0;

	kaddr &= PAGE_MASK;
	vaddr &= PAGE_MASK;

	end = PAGE_ALIGN(vaddr + len);

	pr_debug("dvma: mapping kern %08lx to virt %08lx\n", kaddr, vaddr);
	pgd = pgd_offset_k(vaddr);
	p4d = p4d_offset(pgd, vaddr);
	pud = pud_offset(p4d, vaddr);

	करो अणु
		pmd_t *pmd;
		अचिन्हित दीर्घ end2;

		अगर((pmd = pmd_alloc(&init_mm, pud, vaddr)) == शून्य) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		अगर((end & PGसूची_MASK) > (vaddr & PGसूची_MASK))
			end2 = (vaddr + (PGसूची_SIZE-1)) & PGसूची_MASK;
		अन्यथा
			end2 = end;

		करो अणु
			pte_t *pte;
			अचिन्हित दीर्घ end3;

			अगर((pte = pte_alloc_kernel(pmd, vaddr)) == शून्य) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			अगर((end2 & PMD_MASK) > (vaddr & PMD_MASK))
				end3 = (vaddr + (PMD_SIZE-1)) & PMD_MASK;
			अन्यथा
				end3 = end2;

			करो अणु
				pr_debug("mapping %08lx phys to %08lx\n",
					 __pa(kaddr), vaddr);
				set_pte(pte, pfn_pte(virt_to_pfn(kaddr),
						     PAGE_KERNEL));
				pte++;
				kaddr += PAGE_SIZE;
				vaddr += PAGE_SIZE;
			पूर्ण जबतक(vaddr < end3);

		पूर्ण जबतक(vaddr < end2);

	पूर्ण जबतक(vaddr < end);

	flush_tlb_all();

 out:
	वापस ret;
पूर्ण


अंतरभूत पूर्णांक dvma_map_iommu(अचिन्हित दीर्घ kaddr, अचिन्हित दीर्घ baddr,
				 पूर्णांक len)
अणु
	अचिन्हित दीर्घ end, index;

	index = baddr >> DVMA_PAGE_SHIFT;
	end = ((baddr+len) >> DVMA_PAGE_SHIFT);

	अगर(len & ~DVMA_PAGE_MASK)
		end++;

	क्रम(; index < end ; index++) अणु
//		अगर(dvma_entry_use(index))
//			BUG();
//		pr_info("mapping pa %lx to ba %lx\n", __pa(kaddr),
//			index << DVMA_PAGE_SHIFT);

		dvma_entry_set(index, __pa(kaddr));

		iommu_pte[index] |= IOMMU_FULL_BLOCK;
//		dvma_entry_inc(index);

		kaddr += DVMA_PAGE_SIZE;
	पूर्ण

#अगर_घोषित DEBUG
	क्रम(index = (baddr >> DVMA_PAGE_SHIFT); index < end; index++)
		dvma_prपूर्णांक(index << DVMA_PAGE_SHIFT);
#पूर्ण_अगर
	वापस 0;

पूर्ण

व्योम dvma_unmap_iommu(अचिन्हित दीर्घ baddr, पूर्णांक len)
अणु

	पूर्णांक index, end;


	index = baddr >> DVMA_PAGE_SHIFT;
	end = (DVMA_PAGE_ALIGN(baddr+len) >> DVMA_PAGE_SHIFT);

	क्रम(; index < end ; index++) अणु
		pr_debug("freeing bus mapping %08x\n",
			 index << DVMA_PAGE_SHIFT);
#अगर 0
		अगर(!dvma_entry_use(index))
			pr_info("dvma_unmap freeing unused entry %04x\n",
				index);
		अन्यथा
			dvma_entry_dec(index);
#पूर्ण_अगर
		dvma_entry_clr(index);
	पूर्ण

पूर्ण
