<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  IBM System z Huge TLB Page Support क्रम Kernel.
 *
 *    Copyright IBM Corp. 2007,2020
 *    Author(s): Gerald Schaefer <gerald.schaefer@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "hugetlb"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/security.h>

/*
 * If the bit selected by single-bit biपंचांगask "a" is set within "x", move
 * it to the position indicated by single-bit biपंचांगask "b".
 */
#घोषणा move_set_bit(x, a, b)	(((x) & (a)) >> ilog2(a) << ilog2(b))

अटल अंतरभूत अचिन्हित दीर्घ __pte_to_rste(pte_t pte)
अणु
	अचिन्हित दीर्घ rste;

	/*
	 * Convert encoding		  pte bits	pmd / pud bits
	 *				lIR.uswrdy.p	dy..R...I...wr
	 * empty			010.000000.0 -> 00..0...1...00
	 * prot-none, clean, old	111.000000.1 -> 00..1...1...00
	 * prot-none, clean, young	111.000001.1 -> 01..1...1...00
	 * prot-none, dirty, old	111.000010.1 -> 10..1...1...00
	 * prot-none, dirty, young	111.000011.1 -> 11..1...1...00
	 * पढ़ो-only, clean, old	111.000100.1 -> 00..1...1...01
	 * पढ़ो-only, clean, young	101.000101.1 -> 01..1...0...01
	 * पढ़ो-only, dirty, old	111.000110.1 -> 10..1...1...01
	 * पढ़ो-only, dirty, young	101.000111.1 -> 11..1...0...01
	 * पढ़ो-ग_लिखो, clean, old	111.001100.1 -> 00..1...1...11
	 * पढ़ो-ग_लिखो, clean, young	101.001101.1 -> 01..1...0...11
	 * पढ़ो-ग_लिखो, dirty, old	110.001110.1 -> 10..0...1...11
	 * पढ़ो-ग_लिखो, dirty, young	100.001111.1 -> 11..0...0...11
	 * HW-bits: R पढ़ो-only, I invalid
	 * SW-bits: p present, y young, d dirty, r पढ़ो, w ग_लिखो, s special,
	 *	    u unused, l large
	 */
	अगर (pte_present(pte)) अणु
		rste = pte_val(pte) & PAGE_MASK;
		rste |= move_set_bit(pte_val(pte), _PAGE_READ,
				     _SEGMENT_ENTRY_READ);
		rste |= move_set_bit(pte_val(pte), _PAGE_WRITE,
				     _SEGMENT_ENTRY_WRITE);
		rste |= move_set_bit(pte_val(pte), _PAGE_INVALID,
				     _SEGMENT_ENTRY_INVALID);
		rste |= move_set_bit(pte_val(pte), _PAGE_PROTECT,
				     _SEGMENT_ENTRY_PROTECT);
		rste |= move_set_bit(pte_val(pte), _PAGE_सूचीTY,
				     _SEGMENT_ENTRY_सूचीTY);
		rste |= move_set_bit(pte_val(pte), _PAGE_YOUNG,
				     _SEGMENT_ENTRY_YOUNG);
#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
		rste |= move_set_bit(pte_val(pte), _PAGE_SOFT_सूचीTY,
				     _SEGMENT_ENTRY_SOFT_सूचीTY);
#पूर्ण_अगर
		rste |= move_set_bit(pte_val(pte), _PAGE_NOEXEC,
				     _SEGMENT_ENTRY_NOEXEC);
	पूर्ण अन्यथा
		rste = _SEGMENT_ENTRY_EMPTY;
	वापस rste;
पूर्ण

अटल अंतरभूत pte_t __rste_to_pte(अचिन्हित दीर्घ rste)
अणु
	पूर्णांक present;
	pte_t pte;

	अगर ((rste & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R3)
		present = pud_present(__pud(rste));
	अन्यथा
		present = pmd_present(__pmd(rste));

	/*
	 * Convert encoding		pmd / pud bits	    pte bits
	 *				dy..R...I...wr	  lIR.uswrdy.p
	 * empty			00..0...1...00 -> 010.000000.0
	 * prot-none, clean, old	00..1...1...00 -> 111.000000.1
	 * prot-none, clean, young	01..1...1...00 -> 111.000001.1
	 * prot-none, dirty, old	10..1...1...00 -> 111.000010.1
	 * prot-none, dirty, young	11..1...1...00 -> 111.000011.1
	 * पढ़ो-only, clean, old	00..1...1...01 -> 111.000100.1
	 * पढ़ो-only, clean, young	01..1...0...01 -> 101.000101.1
	 * पढ़ो-only, dirty, old	10..1...1...01 -> 111.000110.1
	 * पढ़ो-only, dirty, young	11..1...0...01 -> 101.000111.1
	 * पढ़ो-ग_लिखो, clean, old	00..1...1...11 -> 111.001100.1
	 * पढ़ो-ग_लिखो, clean, young	01..1...0...11 -> 101.001101.1
	 * पढ़ो-ग_लिखो, dirty, old	10..0...1...11 -> 110.001110.1
	 * पढ़ो-ग_लिखो, dirty, young	11..0...0...11 -> 100.001111.1
	 * HW-bits: R पढ़ो-only, I invalid
	 * SW-bits: p present, y young, d dirty, r पढ़ो, w ग_लिखो, s special,
	 *	    u unused, l large
	 */
	अगर (present) अणु
		pte_val(pte) = rste & _SEGMENT_ENTRY_ORIGIN_LARGE;
		pte_val(pte) |= _PAGE_LARGE | _PAGE_PRESENT;
		pte_val(pte) |= move_set_bit(rste, _SEGMENT_ENTRY_READ,
					     _PAGE_READ);
		pte_val(pte) |= move_set_bit(rste, _SEGMENT_ENTRY_WRITE,
					     _PAGE_WRITE);
		pte_val(pte) |= move_set_bit(rste, _SEGMENT_ENTRY_INVALID,
					     _PAGE_INVALID);
		pte_val(pte) |= move_set_bit(rste, _SEGMENT_ENTRY_PROTECT,
					     _PAGE_PROTECT);
		pte_val(pte) |= move_set_bit(rste, _SEGMENT_ENTRY_सूचीTY,
					     _PAGE_सूचीTY);
		pte_val(pte) |= move_set_bit(rste, _SEGMENT_ENTRY_YOUNG,
					     _PAGE_YOUNG);
#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
		pte_val(pte) |= move_set_bit(rste, _SEGMENT_ENTRY_SOFT_सूचीTY,
					     _PAGE_SOFT_सूचीTY);
#पूर्ण_अगर
		pte_val(pte) |= move_set_bit(rste, _SEGMENT_ENTRY_NOEXEC,
					     _PAGE_NOEXEC);
	पूर्ण अन्यथा
		pte_val(pte) = _PAGE_INVALID;
	वापस pte;
पूर्ण

अटल व्योम clear_huge_pte_skeys(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ rste)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ size, paddr;

	अगर (!mm_uses_skeys(mm) ||
	    rste & _SEGMENT_ENTRY_INVALID)
		वापस;

	अगर ((rste & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R3) अणु
		page = pud_page(__pud(rste));
		size = PUD_SIZE;
		paddr = rste & PUD_MASK;
	पूर्ण अन्यथा अणु
		page = pmd_page(__pmd(rste));
		size = PMD_SIZE;
		paddr = rste & PMD_MASK;
	पूर्ण

	अगर (!test_and_set_bit(PG_arch_1, &page->flags))
		__storage_key_init_range(paddr, paddr + size - 1);
पूर्ण

व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t pte)
अणु
	अचिन्हित दीर्घ rste;

	rste = __pte_to_rste(pte);
	अगर (!MACHINE_HAS_NX)
		rste &= ~_SEGMENT_ENTRY_NOEXEC;

	/* Set correct table type क्रम 2G hugepages */
	अगर ((pte_val(*ptep) & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R3) अणु
		अगर (likely(pte_present(pte)))
			rste |= _REGION3_ENTRY_LARGE;
		rste |= _REGION_ENTRY_TYPE_R3;
	पूर्ण अन्यथा अगर (likely(pte_present(pte)))
		rste |= _SEGMENT_ENTRY_LARGE;

	clear_huge_pte_skeys(mm, rste);
	pte_val(*ptep) = rste;
पूर्ण

pte_t huge_ptep_get(pte_t *ptep)
अणु
	वापस __rste_to_pte(pte_val(*ptep));
पूर्ण

pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
			      अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t pte = huge_ptep_get(ptep);
	pmd_t *pmdp = (pmd_t *) ptep;
	pud_t *pudp = (pud_t *) ptep;

	अगर ((pte_val(*ptep) & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R3)
		pudp_xchg_direct(mm, addr, pudp, __pud(_REGION3_ENTRY_EMPTY));
	अन्यथा
		pmdp_xchg_direct(mm, addr, pmdp, __pmd(_SEGMENT_ENTRY_EMPTY));
	वापस pte;
पूर्ण

pte_t *huge_pte_alloc(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp = शून्य;

	pgdp = pgd_offset(mm, addr);
	p4dp = p4d_alloc(mm, pgdp, addr);
	अगर (p4dp) अणु
		pudp = pud_alloc(mm, p4dp, addr);
		अगर (pudp) अणु
			अगर (sz == PUD_SIZE)
				वापस (pte_t *) pudp;
			अन्यथा अगर (sz == PMD_SIZE)
				pmdp = pmd_alloc(mm, pudp, addr);
		पूर्ण
	पूर्ण
	वापस (pte_t *) pmdp;
पूर्ण

pte_t *huge_pte_offset(काष्ठा mm_काष्ठा *mm,
		       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp = शून्य;

	pgdp = pgd_offset(mm, addr);
	अगर (pgd_present(*pgdp)) अणु
		p4dp = p4d_offset(pgdp, addr);
		अगर (p4d_present(*p4dp)) अणु
			pudp = pud_offset(p4dp, addr);
			अगर (pud_present(*pudp)) अणु
				अगर (pud_large(*pudp))
					वापस (pte_t *) pudp;
				pmdp = pmd_offset(pudp, addr);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस (pte_t *) pmdp;
पूर्ण

पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस pmd_large(pmd);
पूर्ण

पूर्णांक pud_huge(pud_t pud)
अणु
	वापस pud_large(pud);
पूर्ण

काष्ठा page *
follow_huge_pud(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
		pud_t *pud, पूर्णांक flags)
अणु
	अगर (flags & FOLL_GET)
		वापस शून्य;

	वापस pud_page(*pud) + ((address & ~PUD_MASK) >> PAGE_SHIFT);
पूर्ण

bool __init arch_hugetlb_valid_size(अचिन्हित दीर्घ size)
अणु
	अगर (MACHINE_HAS_EDAT1 && size == PMD_SIZE)
		वापस true;
	अन्यथा अगर (MACHINE_HAS_EDAT2 && size == PUD_SIZE)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल अचिन्हित दीर्घ hugetlb_get_unmapped_area_bottomup(काष्ठा file *file,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(file);
	काष्ठा vm_unmapped_area_info info;

	info.flags = 0;
	info.length = len;
	info.low_limit = current->mm->mmap_base;
	info.high_limit = TASK_SIZE;
	info.align_mask = PAGE_MASK & ~huge_page_mask(h);
	info.align_offset = 0;
	वापस vm_unmapped_area(&info);
पूर्ण

अटल अचिन्हित दीर्घ hugetlb_get_unmapped_area_topकरोwn(काष्ठा file *file,
		अचिन्हित दीर्घ addr0, अचिन्हित दीर्घ len,
		अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(file);
	काष्ठा vm_unmapped_area_info info;
	अचिन्हित दीर्घ addr;

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = max(PAGE_SIZE, mmap_min_addr);
	info.high_limit = current->mm->mmap_base;
	info.align_mask = PAGE_MASK & ~huge_page_mask(h);
	info.align_offset = 0;
	addr = vm_unmapped_area(&info);

	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	अगर (addr & ~PAGE_MASK) अणु
		VM_BUG_ON(addr != -ENOMEM);
		info.flags = 0;
		info.low_limit = TASK_UNMAPPED_BASE;
		info.high_limit = TASK_SIZE;
		addr = vm_unmapped_area(&info);
	पूर्ण

	वापस addr;
पूर्ण

अचिन्हित दीर्घ hugetlb_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(file);
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;

	अगर (len & ~huge_page_mask(h))
		वापस -EINVAL;
	अगर (len > TASK_SIZE - mmap_min_addr)
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED) अणु
		अगर (prepare_hugepage_range(file, addr, len))
			वापस -EINVAL;
		जाओ check_asce_limit;
	पूर्ण

	अगर (addr) अणु
		addr = ALIGN(addr, huge_page_size(h));
		vma = find_vma(mm, addr);
		अगर (TASK_SIZE - len >= addr && addr >= mmap_min_addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			जाओ check_asce_limit;
	पूर्ण

	अगर (mm->get_unmapped_area == arch_get_unmapped_area)
		addr = hugetlb_get_unmapped_area_bottomup(file, addr, len,
				pgoff, flags);
	अन्यथा
		addr = hugetlb_get_unmapped_area_topकरोwn(file, addr, len,
				pgoff, flags);
	अगर (offset_in_page(addr))
		वापस addr;

check_asce_limit:
	वापस check_asce_limit(mm, addr, len);
पूर्ण
