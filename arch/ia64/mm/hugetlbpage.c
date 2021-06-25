<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IA-64 Huge TLB Page Support क्रम Kernel.
 *
 * Copyright (C) 2002-2004 Rohit Seth <rohit.seth@पूर्णांकel.com>
 * Copyright (C) 2003-2004 Ken Chen <kenneth.w.chen@पूर्णांकel.com>
 *
 * Sep, 2003: add numa support
 * Feb, 2004: dynamic hugetlb page size via boot parameter
 */

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/module.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/log2.h>
#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>

अचिन्हित पूर्णांक hpage_shअगरt = HPAGE_SHIFT_DEFAULT;
EXPORT_SYMBOL(hpage_shअगरt);

pte_t *
huge_pte_alloc(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
	       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	अचिन्हित दीर्घ taddr = htlbpage_to_page(addr);
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = शून्य;

	pgd = pgd_offset(mm, taddr);
	p4d = p4d_offset(pgd, taddr);
	pud = pud_alloc(mm, p4d, taddr);
	अगर (pud) अणु
		pmd = pmd_alloc(mm, pud, taddr);
		अगर (pmd)
			pte = pte_alloc_map(mm, pmd, taddr);
	पूर्ण
	वापस pte;
पूर्ण

pte_t *
huge_pte_offset (काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	अचिन्हित दीर्घ taddr = htlbpage_to_page(addr);
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = शून्य;

	pgd = pgd_offset(mm, taddr);
	अगर (pgd_present(*pgd)) अणु
		p4d = p4d_offset(pgd, addr);
		अगर (p4d_present(*p4d)) अणु
			pud = pud_offset(p4d, taddr);
			अगर (pud_present(*pud)) अणु
				pmd = pmd_offset(pud, taddr);
				अगर (pmd_present(*pmd))
					pte = pte_offset_map(pmd, taddr);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस pte;
पूर्ण

#घोषणा mk_pte_huge(entry) अणु pte_val(entry) |= _PAGE_P; पूर्ण

/*
 * Don't actually need to करो any preparation, but need to make sure
 * the address is in the right region.
 */
पूर्णांक prepare_hugepage_range(काष्ठा file *file,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	अगर (len & ~HPAGE_MASK)
		वापस -EINVAL;
	अगर (addr & ~HPAGE_MASK)
		वापस -EINVAL;
	अगर (REGION_NUMBER(addr) != RGN_HPAGE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

काष्ठा page *follow_huge_addr(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, पूर्णांक ग_लिखो)
अणु
	काष्ठा page *page;
	pte_t *ptep;

	अगर (REGION_NUMBER(addr) != RGN_HPAGE)
		वापस ERR_PTR(-EINVAL);

	ptep = huge_pte_offset(mm, addr, HPAGE_SIZE);
	अगर (!ptep || pte_none(*ptep))
		वापस शून्य;
	page = pte_page(*ptep);
	page += ((addr & ~HPAGE_MASK) >> PAGE_SHIFT);
	वापस page;
पूर्ण
पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

पूर्णांक pud_huge(pud_t pud)
अणु
	वापस 0;
पूर्ण

व्योम hugetlb_मुक्त_pgd_range(काष्ठा mmu_gather *tlb,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	/*
	 * This is called to मुक्त hugetlb page tables.
	 *
	 * The offset of these addresses from the base of the hugetlb
	 * region must be scaled करोwn by HPAGE_SIZE/PAGE_SIZE so that
	 * the standard मुक्त_pgd_range will मुक्त the right page tables.
	 *
	 * If न्यूनमान and उच्चमानing are also in the hugetlb region, they
	 * must likewise be scaled करोwn; but अगर outside, left unchanged.
	 */

	addr = htlbpage_to_page(addr);
	end  = htlbpage_to_page(end);
	अगर (REGION_NUMBER(न्यूनमान) == RGN_HPAGE)
		न्यूनमान = htlbpage_to_page(न्यूनमान);
	अगर (REGION_NUMBER(उच्चमानing) == RGN_HPAGE)
		उच्चमानing = htlbpage_to_page(उच्चमानing);

	मुक्त_pgd_range(tlb, addr, end, न्यूनमान, उच्चमानing);
पूर्ण

अचिन्हित दीर्घ hugetlb_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा vm_unmapped_area_info info;

	अगर (len > RGN_MAP_LIMIT)
		वापस -ENOMEM;
	अगर (len & ~HPAGE_MASK)
		वापस -EINVAL;

	/* Handle MAP_FIXED */
	अगर (flags & MAP_FIXED) अणु
		अगर (prepare_hugepage_range(file, addr, len))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	/* This code assumes that RGN_HPAGE != 0. */
	अगर ((REGION_NUMBER(addr) != RGN_HPAGE) || (addr & (HPAGE_SIZE - 1)))
		addr = HPAGE_REGION_BASE;

	info.flags = 0;
	info.length = len;
	info.low_limit = addr;
	info.high_limit = HPAGE_REGION_BASE + RGN_MAP_LIMIT;
	info.align_mask = PAGE_MASK & (HPAGE_SIZE - 1);
	info.align_offset = 0;
	वापस vm_unmapped_area(&info);
पूर्ण

अटल पूर्णांक __init hugetlb_setup_sz(अक्षर *str)
अणु
	u64 tr_pages;
	अचिन्हित दीर्घ दीर्घ size;

	अगर (ia64_pal_vm_page_size(&tr_pages, शून्य) != 0)
		/*
		 * shouldn't happen, but just in हाल.
		 */
		tr_pages = 0x15557000UL;

	size = memparse(str, &str);
	अगर (*str || !is_घातer_of_2(size) || !(tr_pages & size) ||
		size <= PAGE_SIZE ||
		size >= (1UL << PAGE_SHIFT << MAX_ORDER)) अणु
		prपूर्णांकk(KERN_WARNING "Invalid huge page size specified\n");
		वापस 1;
	पूर्ण

	hpage_shअगरt = __ffs(size);
	/*
	 * boot cpu alपढ़ोy executed ia64_mmu_init, and has HPAGE_SHIFT_DEFAULT
	 * override here with new page shअगरt.
	 */
	ia64_set_rr(HPAGE_REGION_BASE, hpage_shअगरt << 2);
	वापस 0;
पूर्ण
early_param("hugepagesz", hugetlb_setup_sz);
