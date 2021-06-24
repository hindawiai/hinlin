<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2011
 * Author(s): Jan Glauber <jang@linux.vnet.ibm.com>
 */
#समावेश <linux/hugetlb.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/set_memory.h>

अटल अंतरभूत अचिन्हित दीर्घ sske_frame(अचिन्हित दीर्घ addr, अचिन्हित अक्षर skey)
अणु
	यंत्र अस्थिर(".insn rrf,0xb22b0000,%[skey],%[addr],1,0"
		     : [addr] "+a" (addr) : [skey] "d" (skey));
	वापस addr;
पूर्ण

व्योम __storage_key_init_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ boundary, size;

	जबतक (start < end) अणु
		अगर (MACHINE_HAS_EDAT1) अणु
			/* set storage keys क्रम a 1MB frame */
			size = 1UL << 20;
			boundary = (start + size) & ~(size - 1);
			अगर (boundary <= end) अणु
				करो अणु
					start = sske_frame(start, PAGE_DEFAULT_KEY);
				पूर्ण जबतक (start < boundary);
				जारी;
			पूर्ण
		पूर्ण
		page_set_storage_key(start, PAGE_DEFAULT_KEY, 1);
		start += PAGE_SIZE;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
atomic_दीर्घ_t direct_pages_count[PG_सूचीECT_MAP_MAX];

व्योम arch_report_meminfo(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "DirectMap4k:    %8lu kB\n",
		   atomic_दीर्घ_पढ़ो(&direct_pages_count[PG_सूचीECT_MAP_4K]) << 2);
	seq_म_लिखो(m, "DirectMap1M:    %8lu kB\n",
		   atomic_दीर्घ_पढ़ो(&direct_pages_count[PG_सूचीECT_MAP_1M]) << 10);
	seq_म_लिखो(m, "DirectMap2G:    %8lu kB\n",
		   atomic_दीर्घ_पढ़ो(&direct_pages_count[PG_सूचीECT_MAP_2G]) << 21);
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल व्योम pgt_set(अचिन्हित दीर्घ *old, अचिन्हित दीर्घ new, अचिन्हित दीर्घ addr,
		    अचिन्हित दीर्घ dtt)
अणु
	अचिन्हित दीर्घ table, mask;

	mask = 0;
	अगर (MACHINE_HAS_EDAT2) अणु
		चयन (dtt) अणु
		हाल CRDTE_DTT_REGION3:
			mask = ~(PTRS_PER_PUD * माप(pud_t) - 1);
			अवरोध;
		हाल CRDTE_DTT_SEGMENT:
			mask = ~(PTRS_PER_PMD * माप(pmd_t) - 1);
			अवरोध;
		हाल CRDTE_DTT_PAGE:
			mask = ~(PTRS_PER_PTE * माप(pte_t) - 1);
			अवरोध;
		पूर्ण
		table = (अचिन्हित दीर्घ)old & mask;
		crdte(*old, new, table, dtt, addr, S390_lowcore.kernel_asce);
	पूर्ण अन्यथा अगर (MACHINE_HAS_IDTE) अणु
		cspg(old, *old, new);
	पूर्ण अन्यथा अणु
		csp((अचिन्हित पूर्णांक *)old + 1, *old, new);
	पूर्ण
पूर्ण

अटल पूर्णांक walk_pte_level(pmd_t *pmdp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			  अचिन्हित दीर्घ flags)
अणु
	pte_t *ptep, new;

	ptep = pte_offset_kernel(pmdp, addr);
	करो अणु
		new = *ptep;
		अगर (pte_none(new))
			वापस -EINVAL;
		अगर (flags & SET_MEMORY_RO)
			new = pte_wrprotect(new);
		अन्यथा अगर (flags & SET_MEMORY_RW)
			new = pte_mkग_लिखो(pte_सूची_गढ़ोty(new));
		अगर (flags & SET_MEMORY_NX)
			pte_val(new) |= _PAGE_NOEXEC;
		अन्यथा अगर (flags & SET_MEMORY_X)
			pte_val(new) &= ~_PAGE_NOEXEC;
		pgt_set((अचिन्हित दीर्घ *)ptep, pte_val(new), addr, CRDTE_DTT_PAGE);
		ptep++;
		addr += PAGE_SIZE;
		cond_resched();
	पूर्ण जबतक (addr < end);
	वापस 0;
पूर्ण

अटल पूर्णांक split_pmd_page(pmd_t *pmdp, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ pte_addr, prot;
	pte_t *pt_dir, *ptep;
	pmd_t new;
	पूर्णांक i, ro, nx;

	pt_dir = vmem_pte_alloc();
	अगर (!pt_dir)
		वापस -ENOMEM;
	pte_addr = pmd_pfn(*pmdp) << PAGE_SHIFT;
	ro = !!(pmd_val(*pmdp) & _SEGMENT_ENTRY_PROTECT);
	nx = !!(pmd_val(*pmdp) & _SEGMENT_ENTRY_NOEXEC);
	prot = pgprot_val(ro ? PAGE_KERNEL_RO : PAGE_KERNEL);
	अगर (!nx)
		prot &= ~_PAGE_NOEXEC;
	ptep = pt_dir;
	क्रम (i = 0; i < PTRS_PER_PTE; i++) अणु
		pte_val(*ptep) = pte_addr | prot;
		pte_addr += PAGE_SIZE;
		ptep++;
	पूर्ण
	pmd_val(new) = __pa(pt_dir) | _SEGMENT_ENTRY;
	pgt_set((अचिन्हित दीर्घ *)pmdp, pmd_val(new), addr, CRDTE_DTT_SEGMENT);
	update_page_count(PG_सूचीECT_MAP_4K, PTRS_PER_PTE);
	update_page_count(PG_सूचीECT_MAP_1M, -1);
	वापस 0;
पूर्ण

अटल व्योम modअगरy_pmd_page(pmd_t *pmdp, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ flags)
अणु
	pmd_t new = *pmdp;

	अगर (flags & SET_MEMORY_RO)
		new = pmd_wrprotect(new);
	अन्यथा अगर (flags & SET_MEMORY_RW)
		new = pmd_mkग_लिखो(pmd_सूची_गढ़ोty(new));
	अगर (flags & SET_MEMORY_NX)
		pmd_val(new) |= _SEGMENT_ENTRY_NOEXEC;
	अन्यथा अगर (flags & SET_MEMORY_X)
		pmd_val(new) &= ~_SEGMENT_ENTRY_NOEXEC;
	pgt_set((अचिन्हित दीर्घ *)pmdp, pmd_val(new), addr, CRDTE_DTT_SEGMENT);
पूर्ण

अटल पूर्णांक walk_pmd_level(pud_t *pudp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			  अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ next;
	pmd_t *pmdp;
	पूर्णांक rc = 0;

	pmdp = pmd_offset(pudp, addr);
	करो अणु
		अगर (pmd_none(*pmdp))
			वापस -EINVAL;
		next = pmd_addr_end(addr, end);
		अगर (pmd_large(*pmdp)) अणु
			अगर (addr & ~PMD_MASK || addr + PMD_SIZE > next) अणु
				rc = split_pmd_page(pmdp, addr);
				अगर (rc)
					वापस rc;
				जारी;
			पूर्ण
			modअगरy_pmd_page(pmdp, addr, flags);
		पूर्ण अन्यथा अणु
			rc = walk_pte_level(pmdp, addr, next, flags);
			अगर (rc)
				वापस rc;
		पूर्ण
		pmdp++;
		addr = next;
		cond_resched();
	पूर्ण जबतक (addr < end);
	वापस rc;
पूर्ण

अटल पूर्णांक split_pud_page(pud_t *pudp, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ pmd_addr, prot;
	pmd_t *pm_dir, *pmdp;
	pud_t new;
	पूर्णांक i, ro, nx;

	pm_dir = vmem_crst_alloc(_SEGMENT_ENTRY_EMPTY);
	अगर (!pm_dir)
		वापस -ENOMEM;
	pmd_addr = pud_pfn(*pudp) << PAGE_SHIFT;
	ro = !!(pud_val(*pudp) & _REGION_ENTRY_PROTECT);
	nx = !!(pud_val(*pudp) & _REGION_ENTRY_NOEXEC);
	prot = pgprot_val(ro ? SEGMENT_KERNEL_RO : SEGMENT_KERNEL);
	अगर (!nx)
		prot &= ~_SEGMENT_ENTRY_NOEXEC;
	pmdp = pm_dir;
	क्रम (i = 0; i < PTRS_PER_PMD; i++) अणु
		pmd_val(*pmdp) = pmd_addr | prot;
		pmd_addr += PMD_SIZE;
		pmdp++;
	पूर्ण
	pud_val(new) = __pa(pm_dir) | _REGION3_ENTRY;
	pgt_set((अचिन्हित दीर्घ *)pudp, pud_val(new), addr, CRDTE_DTT_REGION3);
	update_page_count(PG_सूचीECT_MAP_1M, PTRS_PER_PMD);
	update_page_count(PG_सूचीECT_MAP_2G, -1);
	वापस 0;
पूर्ण

अटल व्योम modअगरy_pud_page(pud_t *pudp, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ flags)
अणु
	pud_t new = *pudp;

	अगर (flags & SET_MEMORY_RO)
		new = pud_wrprotect(new);
	अन्यथा अगर (flags & SET_MEMORY_RW)
		new = pud_mkग_लिखो(pud_सूची_गढ़ोty(new));
	अगर (flags & SET_MEMORY_NX)
		pud_val(new) |= _REGION_ENTRY_NOEXEC;
	अन्यथा अगर (flags & SET_MEMORY_X)
		pud_val(new) &= ~_REGION_ENTRY_NOEXEC;
	pgt_set((अचिन्हित दीर्घ *)pudp, pud_val(new), addr, CRDTE_DTT_REGION3);
पूर्ण

अटल पूर्णांक walk_pud_level(p4d_t *p4d, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			  अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ next;
	pud_t *pudp;
	पूर्णांक rc = 0;

	pudp = pud_offset(p4d, addr);
	करो अणु
		अगर (pud_none(*pudp))
			वापस -EINVAL;
		next = pud_addr_end(addr, end);
		अगर (pud_large(*pudp)) अणु
			अगर (addr & ~PUD_MASK || addr + PUD_SIZE > next) अणु
				rc = split_pud_page(pudp, addr);
				अगर (rc)
					अवरोध;
				जारी;
			पूर्ण
			modअगरy_pud_page(pudp, addr, flags);
		पूर्ण अन्यथा अणु
			rc = walk_pmd_level(pudp, addr, next, flags);
		पूर्ण
		pudp++;
		addr = next;
		cond_resched();
	पूर्ण जबतक (addr < end && !rc);
	वापस rc;
पूर्ण

अटल पूर्णांक walk_p4d_level(pgd_t *pgd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			  अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ next;
	p4d_t *p4dp;
	पूर्णांक rc = 0;

	p4dp = p4d_offset(pgd, addr);
	करो अणु
		अगर (p4d_none(*p4dp))
			वापस -EINVAL;
		next = p4d_addr_end(addr, end);
		rc = walk_pud_level(p4dp, addr, next, flags);
		p4dp++;
		addr = next;
		cond_resched();
	पूर्ण जबतक (addr < end && !rc);
	वापस rc;
पूर्ण

DEFINE_MUTEX(cpa_mutex);

अटल पूर्णांक change_page_attr(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			    अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ next;
	पूर्णांक rc = -EINVAL;
	pgd_t *pgdp;

	अगर (addr == end)
		वापस 0;
	अगर (end >= MODULES_END)
		वापस -EINVAL;
	mutex_lock(&cpa_mutex);
	pgdp = pgd_offset_k(addr);
	करो अणु
		अगर (pgd_none(*pgdp))
			अवरोध;
		next = pgd_addr_end(addr, end);
		rc = walk_p4d_level(pgdp, addr, next, flags);
		अगर (rc)
			अवरोध;
		cond_resched();
	पूर्ण जबतक (pgdp++, addr = next, addr < end && !rc);
	mutex_unlock(&cpa_mutex);
	वापस rc;
पूर्ण

पूर्णांक __set_memory(अचिन्हित दीर्घ addr, पूर्णांक numpages, अचिन्हित दीर्घ flags)
अणु
	अगर (!MACHINE_HAS_NX)
		flags &= ~(SET_MEMORY_NX | SET_MEMORY_X);
	अगर (!flags)
		वापस 0;
	addr &= PAGE_MASK;
	वापस change_page_attr(addr, addr + numpages * PAGE_SIZE, flags);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC

अटल व्योम ipte_range(pte_t *pte, अचिन्हित दीर्घ address, पूर्णांक nr)
अणु
	पूर्णांक i;

	अगर (test_facility(13)) अणु
		__ptep_ipte_range(address, nr - 1, pte, IPTE_GLOBAL);
		वापस;
	पूर्ण
	क्रम (i = 0; i < nr; i++) अणु
		__ptep_ipte(address, pte, 0, 0, IPTE_GLOBAL);
		address += PAGE_SIZE;
		pte++;
	पूर्ण
पूर्ण

व्योम __kernel_map_pages(काष्ठा page *page, पूर्णांक numpages, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ address;
	पूर्णांक nr, i, j;
	pte_t *pte;

	क्रम (i = 0; i < numpages;) अणु
		address = page_to_phys(page + i);
		pte = virt_to_kpte(address);
		nr = (अचिन्हित दीर्घ)pte >> ilog2(माप(दीर्घ));
		nr = PTRS_PER_PTE - (nr & (PTRS_PER_PTE - 1));
		nr = min(numpages - i, nr);
		अगर (enable) अणु
			क्रम (j = 0; j < nr; j++) अणु
				pte_val(*pte) &= ~_PAGE_INVALID;
				address += PAGE_SIZE;
				pte++;
			पूर्ण
		पूर्ण अन्यथा अणु
			ipte_range(pte, address, nr);
		पूर्ण
		i += nr;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_PAGEALLOC */
