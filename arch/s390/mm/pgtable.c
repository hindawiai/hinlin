<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2007, 2011
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#समावेश <linux/swapops.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/ksm.h>
#समावेश <linux/mman.h>

#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/page-states.h>

pgprot_t pgprot_ग_लिखोcombine(pgprot_t prot)
अणु
	/*
	 * mio_wb_bit_mask may be set on a dअगरferent CPU, but it is only set
	 * once at init and only पढ़ो afterwards.
	 */
	वापस __pgprot(pgprot_val(prot) | mio_wb_bit_mask);
पूर्ण
EXPORT_SYMBOL_GPL(pgprot_ग_लिखोcombine);

pgprot_t pgprot_ग_लिखोthrough(pgprot_t prot)
अणु
	/*
	 * mio_wb_bit_mask may be set on a dअगरferent CPU, but it is only set
	 * once at init and only पढ़ो afterwards.
	 */
	वापस __pgprot(pgprot_val(prot) & ~mio_wb_bit_mask);
पूर्ण
EXPORT_SYMBOL_GPL(pgprot_ग_लिखोthrough);

अटल अंतरभूत व्योम ptep_ipte_local(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				   pte_t *ptep, पूर्णांक nodat)
अणु
	अचिन्हित दीर्घ opt, asce;

	अगर (MACHINE_HAS_TLB_GUEST) अणु
		opt = 0;
		asce = READ_ONCE(mm->context.gmap_asce);
		अगर (asce == 0UL || nodat)
			opt |= IPTE_NODAT;
		अगर (asce != -1UL) अणु
			asce = asce ? : mm->context.asce;
			opt |= IPTE_GUEST_ASCE;
		पूर्ण
		__ptep_ipte(addr, ptep, opt, asce, IPTE_LOCAL);
	पूर्ण अन्यथा अणु
		__ptep_ipte(addr, ptep, 0, 0, IPTE_LOCAL);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ptep_ipte_global(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				    pte_t *ptep, पूर्णांक nodat)
अणु
	अचिन्हित दीर्घ opt, asce;

	अगर (MACHINE_HAS_TLB_GUEST) अणु
		opt = 0;
		asce = READ_ONCE(mm->context.gmap_asce);
		अगर (asce == 0UL || nodat)
			opt |= IPTE_NODAT;
		अगर (asce != -1UL) अणु
			asce = asce ? : mm->context.asce;
			opt |= IPTE_GUEST_ASCE;
		पूर्ण
		__ptep_ipte(addr, ptep, opt, asce, IPTE_GLOBAL);
	पूर्ण अन्यथा अणु
		__ptep_ipte(addr, ptep, 0, 0, IPTE_GLOBAL);
	पूर्ण
पूर्ण

अटल अंतरभूत pte_t ptep_flush_direct(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ addr, pte_t *ptep,
				      पूर्णांक nodat)
अणु
	pte_t old;

	old = *ptep;
	अगर (unlikely(pte_val(old) & _PAGE_INVALID))
		वापस old;
	atomic_inc(&mm->context.flush_count);
	अगर (MACHINE_HAS_TLB_LC &&
	    cpumask_equal(mm_cpumask(mm), cpumask_of(smp_processor_id())))
		ptep_ipte_local(mm, addr, ptep, nodat);
	अन्यथा
		ptep_ipte_global(mm, addr, ptep, nodat);
	atomic_dec(&mm->context.flush_count);
	वापस old;
पूर्ण

अटल अंतरभूत pte_t ptep_flush_lazy(काष्ठा mm_काष्ठा *mm,
				    अचिन्हित दीर्घ addr, pte_t *ptep,
				    पूर्णांक nodat)
अणु
	pte_t old;

	old = *ptep;
	अगर (unlikely(pte_val(old) & _PAGE_INVALID))
		वापस old;
	atomic_inc(&mm->context.flush_count);
	अगर (cpumask_equal(&mm->context.cpu_attach_mask,
			  cpumask_of(smp_processor_id()))) अणु
		pte_val(*ptep) |= _PAGE_INVALID;
		mm->context.flush_mm = 1;
	पूर्ण अन्यथा
		ptep_ipte_global(mm, addr, ptep, nodat);
	atomic_dec(&mm->context.flush_count);
	वापस old;
पूर्ण

अटल अंतरभूत pgste_t pgste_get_lock(pte_t *ptep)
अणु
	अचिन्हित दीर्घ new = 0;
#अगर_घोषित CONFIG_PGSTE
	अचिन्हित दीर्घ old;

	यंत्र(
		"	lg	%0,%2\n"
		"0:	lgr	%1,%0\n"
		"	nihh	%0,0xff7f\n"	/* clear PCL bit in old */
		"	oihh	%1,0x0080\n"	/* set PCL bit in new */
		"	csg	%0,%1,%2\n"
		"	jl	0b\n"
		: "=&d" (old), "=&d" (new), "=Q" (ptep[PTRS_PER_PTE])
		: "Q" (ptep[PTRS_PER_PTE]) : "cc", "memory");
#पूर्ण_अगर
	वापस __pgste(new);
पूर्ण

अटल अंतरभूत व्योम pgste_set_unlock(pte_t *ptep, pgste_t pgste)
अणु
#अगर_घोषित CONFIG_PGSTE
	यंत्र(
		"	nihh	%1,0xff7f\n"	/* clear PCL bit */
		"	stg	%1,%0\n"
		: "=Q" (ptep[PTRS_PER_PTE])
		: "d" (pgste_val(pgste)), "Q" (ptep[PTRS_PER_PTE])
		: "cc", "memory");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत pgste_t pgste_get(pte_t *ptep)
अणु
	अचिन्हित दीर्घ pgste = 0;
#अगर_घोषित CONFIG_PGSTE
	pgste = *(अचिन्हित दीर्घ *)(ptep + PTRS_PER_PTE);
#पूर्ण_अगर
	वापस __pgste(pgste);
पूर्ण

अटल अंतरभूत व्योम pgste_set(pte_t *ptep, pgste_t pgste)
अणु
#अगर_घोषित CONFIG_PGSTE
	*(pgste_t *)(ptep + PTRS_PER_PTE) = pgste;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत pgste_t pgste_update_all(pte_t pte, pgste_t pgste,
				       काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_PGSTE
	अचिन्हित दीर्घ address, bits, skey;

	अगर (!mm_uses_skeys(mm) || pte_val(pte) & _PAGE_INVALID)
		वापस pgste;
	address = pte_val(pte) & PAGE_MASK;
	skey = (अचिन्हित दीर्घ) page_get_storage_key(address);
	bits = skey & (_PAGE_CHANGED | _PAGE_REFERENCED);
	/* Transfer page changed & referenced bit to guest bits in pgste */
	pgste_val(pgste) |= bits << 48;		/* GR bit & GC bit */
	/* Copy page access key and fetch protection bit to pgste */
	pgste_val(pgste) &= ~(PGSTE_ACC_BITS | PGSTE_FP_BIT);
	pgste_val(pgste) |= (skey & (_PAGE_ACC_BITS | _PAGE_FP_BIT)) << 56;
#पूर्ण_अगर
	वापस pgste;

पूर्ण

अटल अंतरभूत व्योम pgste_set_key(pte_t *ptep, pgste_t pgste, pte_t entry,
				 काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_PGSTE
	अचिन्हित दीर्घ address;
	अचिन्हित दीर्घ nkey;

	अगर (!mm_uses_skeys(mm) || pte_val(entry) & _PAGE_INVALID)
		वापस;
	VM_BUG_ON(!(pte_val(*ptep) & _PAGE_INVALID));
	address = pte_val(entry) & PAGE_MASK;
	/*
	 * Set page access key and fetch protection bit from pgste.
	 * The guest C/R inक्रमmation is still in the PGSTE, set real
	 * key C/R to 0.
	 */
	nkey = (pgste_val(pgste) & (PGSTE_ACC_BITS | PGSTE_FP_BIT)) >> 56;
	nkey |= (pgste_val(pgste) & (PGSTE_GR_BIT | PGSTE_GC_BIT)) >> 48;
	page_set_storage_key(address, nkey, 0);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत pgste_t pgste_set_pte(pte_t *ptep, pgste_t pgste, pte_t entry)
अणु
#अगर_घोषित CONFIG_PGSTE
	अगर ((pte_val(entry) & _PAGE_PRESENT) &&
	    (pte_val(entry) & _PAGE_WRITE) &&
	    !(pte_val(entry) & _PAGE_INVALID)) अणु
		अगर (!MACHINE_HAS_ESOP) अणु
			/*
			 * Without enhanced suppression-on-protection क्रमce
			 * the dirty bit on क्रम all writable ptes.
			 */
			pte_val(entry) |= _PAGE_सूचीTY;
			pte_val(entry) &= ~_PAGE_PROTECT;
		पूर्ण
		अगर (!(pte_val(entry) & _PAGE_PROTECT))
			/* This pte allows ग_लिखो access, set user-dirty */
			pgste_val(pgste) |= PGSTE_UC_BIT;
	पूर्ण
#पूर्ण_अगर
	*ptep = entry;
	वापस pgste;
पूर्ण

अटल अंतरभूत pgste_t pgste_pte_notअगरy(काष्ठा mm_काष्ठा *mm,
				       अचिन्हित दीर्घ addr,
				       pte_t *ptep, pgste_t pgste)
अणु
#अगर_घोषित CONFIG_PGSTE
	अचिन्हित दीर्घ bits;

	bits = pgste_val(pgste) & (PGSTE_IN_BIT | PGSTE_VSIE_BIT);
	अगर (bits) अणु
		pgste_val(pgste) ^= bits;
		ptep_notअगरy(mm, addr, ptep, bits);
	पूर्ण
#पूर्ण_अगर
	वापस pgste;
पूर्ण

अटल अंतरभूत pgste_t ptep_xchg_start(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pgste_t pgste = __pgste(0);

	अगर (mm_has_pgste(mm)) अणु
		pgste = pgste_get_lock(ptep);
		pgste = pgste_pte_notअगरy(mm, addr, ptep, pgste);
	पूर्ण
	वापस pgste;
पूर्ण

अटल अंतरभूत pte_t ptep_xchg_commit(काष्ठा mm_काष्ठा *mm,
				    अचिन्हित दीर्घ addr, pte_t *ptep,
				    pgste_t pgste, pte_t old, pte_t new)
अणु
	अगर (mm_has_pgste(mm)) अणु
		अगर (pte_val(old) & _PAGE_INVALID)
			pgste_set_key(ptep, pgste, new, mm);
		अगर (pte_val(new) & _PAGE_INVALID) अणु
			pgste = pgste_update_all(old, pgste, mm);
			अगर ((pgste_val(pgste) & _PGSTE_GPS_USAGE_MASK) ==
			    _PGSTE_GPS_USAGE_UNUSED)
				pte_val(old) |= _PAGE_UNUSED;
		पूर्ण
		pgste = pgste_set_pte(ptep, pgste, new);
		pgste_set_unlock(ptep, pgste);
	पूर्ण अन्यथा अणु
		*ptep = new;
	पूर्ण
	वापस old;
पूर्ण

pte_t ptep_xchg_direct(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		       pte_t *ptep, pte_t new)
अणु
	pgste_t pgste;
	pte_t old;
	पूर्णांक nodat;

	preempt_disable();
	pgste = ptep_xchg_start(mm, addr, ptep);
	nodat = !!(pgste_val(pgste) & _PGSTE_GPS_NODAT);
	old = ptep_flush_direct(mm, addr, ptep, nodat);
	old = ptep_xchg_commit(mm, addr, ptep, pgste, old, new);
	preempt_enable();
	वापस old;
पूर्ण
EXPORT_SYMBOL(ptep_xchg_direct);

pte_t ptep_xchg_lazy(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t new)
अणु
	pgste_t pgste;
	pte_t old;
	पूर्णांक nodat;

	preempt_disable();
	pgste = ptep_xchg_start(mm, addr, ptep);
	nodat = !!(pgste_val(pgste) & _PGSTE_GPS_NODAT);
	old = ptep_flush_lazy(mm, addr, ptep, nodat);
	old = ptep_xchg_commit(mm, addr, ptep, pgste, old, new);
	preempt_enable();
	वापस old;
पूर्ण
EXPORT_SYMBOL(ptep_xchg_lazy);

pte_t ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			     pte_t *ptep)
अणु
	pgste_t pgste;
	pte_t old;
	पूर्णांक nodat;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	preempt_disable();
	pgste = ptep_xchg_start(mm, addr, ptep);
	nodat = !!(pgste_val(pgste) & _PGSTE_GPS_NODAT);
	old = ptep_flush_lazy(mm, addr, ptep, nodat);
	अगर (mm_has_pgste(mm)) अणु
		pgste = pgste_update_all(old, pgste, mm);
		pgste_set(ptep, pgste);
	पूर्ण
	वापस old;
पूर्ण

व्योम ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			     pte_t *ptep, pte_t old_pte, pte_t pte)
अणु
	pgste_t pgste;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर (!MACHINE_HAS_NX)
		pte_val(pte) &= ~_PAGE_NOEXEC;
	अगर (mm_has_pgste(mm)) अणु
		pgste = pgste_get(ptep);
		pgste_set_key(ptep, pgste, pte, mm);
		pgste = pgste_set_pte(ptep, pgste, pte);
		pgste_set_unlock(ptep, pgste);
	पूर्ण अन्यथा अणु
		*ptep = pte;
	पूर्ण
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम pmdp_idte_local(काष्ठा mm_काष्ठा *mm,
				   अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	अगर (MACHINE_HAS_TLB_GUEST)
		__pmdp_idte(addr, pmdp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_LOCAL);
	अन्यथा
		__pmdp_idte(addr, pmdp, 0, 0, IDTE_LOCAL);
	अगर (mm_has_pgste(mm) && mm->context.allow_gmap_hpage_1m)
		gmap_pmdp_idte_local(mm, addr);
पूर्ण

अटल अंतरभूत व्योम pmdp_idte_global(काष्ठा mm_काष्ठा *mm,
				    अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	अगर (MACHINE_HAS_TLB_GUEST) अणु
		__pmdp_idte(addr, pmdp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_GLOBAL);
		अगर (mm_has_pgste(mm) && mm->context.allow_gmap_hpage_1m)
			gmap_pmdp_idte_global(mm, addr);
	पूर्ण अन्यथा अगर (MACHINE_HAS_IDTE) अणु
		__pmdp_idte(addr, pmdp, 0, 0, IDTE_GLOBAL);
		अगर (mm_has_pgste(mm) && mm->context.allow_gmap_hpage_1m)
			gmap_pmdp_idte_global(mm, addr);
	पूर्ण अन्यथा अणु
		__pmdp_csp(pmdp);
		अगर (mm_has_pgste(mm) && mm->context.allow_gmap_hpage_1m)
			gmap_pmdp_csp(mm, addr);
	पूर्ण
पूर्ण

अटल अंतरभूत pmd_t pmdp_flush_direct(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	pmd_t old;

	old = *pmdp;
	अगर (pmd_val(old) & _SEGMENT_ENTRY_INVALID)
		वापस old;
	atomic_inc(&mm->context.flush_count);
	अगर (MACHINE_HAS_TLB_LC &&
	    cpumask_equal(mm_cpumask(mm), cpumask_of(smp_processor_id())))
		pmdp_idte_local(mm, addr, pmdp);
	अन्यथा
		pmdp_idte_global(mm, addr, pmdp);
	atomic_dec(&mm->context.flush_count);
	वापस old;
पूर्ण

अटल अंतरभूत pmd_t pmdp_flush_lazy(काष्ठा mm_काष्ठा *mm,
				    अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	pmd_t old;

	old = *pmdp;
	अगर (pmd_val(old) & _SEGMENT_ENTRY_INVALID)
		वापस old;
	atomic_inc(&mm->context.flush_count);
	अगर (cpumask_equal(&mm->context.cpu_attach_mask,
			  cpumask_of(smp_processor_id()))) अणु
		pmd_val(*pmdp) |= _SEGMENT_ENTRY_INVALID;
		mm->context.flush_mm = 1;
		अगर (mm_has_pgste(mm))
			gmap_pmdp_invalidate(mm, addr);
	पूर्ण अन्यथा अणु
		pmdp_idte_global(mm, addr, pmdp);
	पूर्ण
	atomic_dec(&mm->context.flush_count);
	वापस old;
पूर्ण

#अगर_घोषित CONFIG_PGSTE
अटल pmd_t *pmd_alloc_map(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(mm, addr);
	p4d = p4d_alloc(mm, pgd, addr);
	अगर (!p4d)
		वापस शून्य;
	pud = pud_alloc(mm, p4d, addr);
	अगर (!pud)
		वापस शून्य;
	pmd = pmd_alloc(mm, pud, addr);
	वापस pmd;
पूर्ण
#पूर्ण_अगर

pmd_t pmdp_xchg_direct(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		       pmd_t *pmdp, pmd_t new)
अणु
	pmd_t old;

	preempt_disable();
	old = pmdp_flush_direct(mm, addr, pmdp);
	*pmdp = new;
	preempt_enable();
	वापस old;
पूर्ण
EXPORT_SYMBOL(pmdp_xchg_direct);

pmd_t pmdp_xchg_lazy(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pmd_t *pmdp, pmd_t new)
अणु
	pmd_t old;

	preempt_disable();
	old = pmdp_flush_lazy(mm, addr, pmdp);
	*pmdp = new;
	preempt_enable();
	वापस old;
पूर्ण
EXPORT_SYMBOL(pmdp_xchg_lazy);

अटल अंतरभूत व्योम pudp_idte_local(काष्ठा mm_काष्ठा *mm,
				   अचिन्हित दीर्घ addr, pud_t *pudp)
अणु
	अगर (MACHINE_HAS_TLB_GUEST)
		__pudp_idte(addr, pudp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_LOCAL);
	अन्यथा
		__pudp_idte(addr, pudp, 0, 0, IDTE_LOCAL);
पूर्ण

अटल अंतरभूत व्योम pudp_idte_global(काष्ठा mm_काष्ठा *mm,
				    अचिन्हित दीर्घ addr, pud_t *pudp)
अणु
	अगर (MACHINE_HAS_TLB_GUEST)
		__pudp_idte(addr, pudp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_GLOBAL);
	अन्यथा अगर (MACHINE_HAS_IDTE)
		__pudp_idte(addr, pudp, 0, 0, IDTE_GLOBAL);
	अन्यथा
		/*
		 * Invalid bit position is the same क्रम pmd and pud, so we can
		 * re-use _pmd_csp() here
		 */
		__pmdp_csp((pmd_t *) pudp);
पूर्ण

अटल अंतरभूत pud_t pudp_flush_direct(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ addr, pud_t *pudp)
अणु
	pud_t old;

	old = *pudp;
	अगर (pud_val(old) & _REGION_ENTRY_INVALID)
		वापस old;
	atomic_inc(&mm->context.flush_count);
	अगर (MACHINE_HAS_TLB_LC &&
	    cpumask_equal(mm_cpumask(mm), cpumask_of(smp_processor_id())))
		pudp_idte_local(mm, addr, pudp);
	अन्यथा
		pudp_idte_global(mm, addr, pudp);
	atomic_dec(&mm->context.flush_count);
	वापस old;
पूर्ण

pud_t pudp_xchg_direct(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		       pud_t *pudp, pud_t new)
अणु
	pud_t old;

	preempt_disable();
	old = pudp_flush_direct(mm, addr, pudp);
	*pudp = new;
	preempt_enable();
	वापस old;
पूर्ण
EXPORT_SYMBOL(pudp_xchg_direct);

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
व्योम pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				pgtable_t pgtable)
अणु
	काष्ठा list_head *lh = (काष्ठा list_head *) pgtable;

	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));

	/* FIFO */
	अगर (!pmd_huge_pte(mm, pmdp))
		INIT_LIST_HEAD(lh);
	अन्यथा
		list_add(lh, (काष्ठा list_head *) pmd_huge_pte(mm, pmdp));
	pmd_huge_pte(mm, pmdp) = pgtable;
पूर्ण

pgtable_t pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp)
अणु
	काष्ठा list_head *lh;
	pgtable_t pgtable;
	pte_t *ptep;

	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));

	/* FIFO */
	pgtable = pmd_huge_pte(mm, pmdp);
	lh = (काष्ठा list_head *) pgtable;
	अगर (list_empty(lh))
		pmd_huge_pte(mm, pmdp) = शून्य;
	अन्यथा अणु
		pmd_huge_pte(mm, pmdp) = (pgtable_t) lh->next;
		list_del(lh);
	पूर्ण
	ptep = (pte_t *) pgtable;
	pte_val(*ptep) = _PAGE_INVALID;
	ptep++;
	pte_val(*ptep) = _PAGE_INVALID;
	वापस pgtable;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#अगर_घोषित CONFIG_PGSTE
व्योम ptep_set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t entry)
अणु
	pgste_t pgste;

	/* the mm_has_pgste() check is करोne in set_pte_at() */
	preempt_disable();
	pgste = pgste_get_lock(ptep);
	pgste_val(pgste) &= ~_PGSTE_GPS_ZERO;
	pgste_set_key(ptep, pgste, entry, mm);
	pgste = pgste_set_pte(ptep, pgste, entry);
	pgste_set_unlock(ptep, pgste);
	preempt_enable();
पूर्ण

व्योम ptep_set_notअगरy(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pgste_t pgste;

	preempt_disable();
	pgste = pgste_get_lock(ptep);
	pgste_val(pgste) |= PGSTE_IN_BIT;
	pgste_set_unlock(ptep, pgste);
	preempt_enable();
पूर्ण

/**
 * ptep_क्रमce_prot - change access rights of a locked pte
 * @mm: poपूर्णांकer to the process mm_काष्ठा
 * @addr: भव address in the guest address space
 * @ptep: poपूर्णांकer to the page table entry
 * @prot: indicates guest access rights: PROT_NONE, PROT_READ or PROT_WRITE
 * @bit: pgste bit to set (e.g. क्रम notअगरication)
 *
 * Returns 0 अगर the access rights were changed and -EAGAIN अगर the current
 * and requested access rights are incompatible.
 */
पूर्णांक ptep_क्रमce_prot(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		    pte_t *ptep, पूर्णांक prot, अचिन्हित दीर्घ bit)
अणु
	pte_t entry;
	pgste_t pgste;
	पूर्णांक pte_i, pte_p, nodat;

	pgste = pgste_get_lock(ptep);
	entry = *ptep;
	/* Check pte entry after all locks have been acquired */
	pte_i = pte_val(entry) & _PAGE_INVALID;
	pte_p = pte_val(entry) & _PAGE_PROTECT;
	अगर ((pte_i && (prot != PROT_NONE)) ||
	    (pte_p && (prot & PROT_WRITE))) अणु
		pgste_set_unlock(ptep, pgste);
		वापस -EAGAIN;
	पूर्ण
	/* Change access rights and set pgste bit */
	nodat = !!(pgste_val(pgste) & _PGSTE_GPS_NODAT);
	अगर (prot == PROT_NONE && !pte_i) अणु
		ptep_flush_direct(mm, addr, ptep, nodat);
		pgste = pgste_update_all(entry, pgste, mm);
		pte_val(entry) |= _PAGE_INVALID;
	पूर्ण
	अगर (prot == PROT_READ && !pte_p) अणु
		ptep_flush_direct(mm, addr, ptep, nodat);
		pte_val(entry) &= ~_PAGE_INVALID;
		pte_val(entry) |= _PAGE_PROTECT;
	पूर्ण
	pgste_val(pgste) |= bit;
	pgste = pgste_set_pte(ptep, pgste, entry);
	pgste_set_unlock(ptep, pgste);
	वापस 0;
पूर्ण

पूर्णांक ptep_shaकरोw_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ saddr,
		    pte_t *sptep, pte_t *tptep, pte_t pte)
अणु
	pgste_t spgste, tpgste;
	pte_t spte, tpte;
	पूर्णांक rc = -EAGAIN;

	अगर (!(pte_val(*tptep) & _PAGE_INVALID))
		वापस 0;	/* alपढ़ोy shaकरोwed */
	spgste = pgste_get_lock(sptep);
	spte = *sptep;
	अगर (!(pte_val(spte) & _PAGE_INVALID) &&
	    !((pte_val(spte) & _PAGE_PROTECT) &&
	      !(pte_val(pte) & _PAGE_PROTECT))) अणु
		pgste_val(spgste) |= PGSTE_VSIE_BIT;
		tpgste = pgste_get_lock(tptep);
		pte_val(tpte) = (pte_val(spte) & PAGE_MASK) |
				(pte_val(pte) & _PAGE_PROTECT);
		/* करोn't touch the storage key - it beदीर्घs to parent pgste */
		tpgste = pgste_set_pte(tptep, tpgste, tpte);
		pgste_set_unlock(tptep, tpgste);
		rc = 1;
	पूर्ण
	pgste_set_unlock(sptep, spgste);
	वापस rc;
पूर्ण

व्योम ptep_unshaकरोw_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ saddr, pte_t *ptep)
अणु
	pgste_t pgste;
	पूर्णांक nodat;

	pgste = pgste_get_lock(ptep);
	/* notअगरier is called by the caller */
	nodat = !!(pgste_val(pgste) & _PGSTE_GPS_NODAT);
	ptep_flush_direct(mm, saddr, ptep, nodat);
	/* करोn't touch the storage key - it beदीर्घs to parent pgste */
	pgste = pgste_set_pte(ptep, pgste, __pte(_PAGE_INVALID));
	pgste_set_unlock(ptep, pgste);
पूर्ण

अटल व्योम ptep_zap_swap_entry(काष्ठा mm_काष्ठा *mm, swp_entry_t entry)
अणु
	अगर (!non_swap_entry(entry))
		dec_mm_counter(mm, MM_SWAPENTS);
	अन्यथा अगर (is_migration_entry(entry)) अणु
		काष्ठा page *page = migration_entry_to_page(entry);

		dec_mm_counter(mm, mm_counter(page));
	पूर्ण
	मुक्त_swap_and_cache(entry);
पूर्ण

व्योम ptep_zap_unused(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, पूर्णांक reset)
अणु
	अचिन्हित दीर्घ pgstev;
	pgste_t pgste;
	pte_t pte;

	/* Zap unused and logically-zero pages */
	preempt_disable();
	pgste = pgste_get_lock(ptep);
	pgstev = pgste_val(pgste);
	pte = *ptep;
	अगर (!reset && pte_swap(pte) &&
	    ((pgstev & _PGSTE_GPS_USAGE_MASK) == _PGSTE_GPS_USAGE_UNUSED ||
	     (pgstev & _PGSTE_GPS_ZERO))) अणु
		ptep_zap_swap_entry(mm, pte_to_swp_entry(pte));
		pte_clear(mm, addr, ptep);
	पूर्ण
	अगर (reset)
		pgste_val(pgste) &= ~_PGSTE_GPS_USAGE_MASK;
	pgste_set_unlock(ptep, pgste);
	preempt_enable();
पूर्ण

व्योम ptep_zap_key(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ ptev;
	pgste_t pgste;

	/* Clear storage key ACC and F, but set R/C */
	preempt_disable();
	pgste = pgste_get_lock(ptep);
	pgste_val(pgste) &= ~(PGSTE_ACC_BITS | PGSTE_FP_BIT);
	pgste_val(pgste) |= PGSTE_GR_BIT | PGSTE_GC_BIT;
	ptev = pte_val(*ptep);
	अगर (!(ptev & _PAGE_INVALID) && (ptev & _PAGE_WRITE))
		page_set_storage_key(ptev & PAGE_MASK, PAGE_DEFAULT_KEY, 1);
	pgste_set_unlock(ptep, pgste);
	preempt_enable();
पूर्ण

/*
 * Test and reset अगर a guest page is dirty
 */
bool ptep_test_and_clear_uc(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		       pte_t *ptep)
अणु
	pgste_t pgste;
	pte_t pte;
	bool dirty;
	पूर्णांक nodat;

	pgste = pgste_get_lock(ptep);
	dirty = !!(pgste_val(pgste) & PGSTE_UC_BIT);
	pgste_val(pgste) &= ~PGSTE_UC_BIT;
	pte = *ptep;
	अगर (dirty && (pte_val(pte) & _PAGE_PRESENT)) अणु
		pgste = pgste_pte_notअगरy(mm, addr, ptep, pgste);
		nodat = !!(pgste_val(pgste) & _PGSTE_GPS_NODAT);
		ptep_ipte_global(mm, addr, ptep, nodat);
		अगर (MACHINE_HAS_ESOP || !(pte_val(pte) & _PAGE_WRITE))
			pte_val(pte) |= _PAGE_PROTECT;
		अन्यथा
			pte_val(pte) |= _PAGE_INVALID;
		*ptep = pte;
	पूर्ण
	pgste_set_unlock(ptep, pgste);
	वापस dirty;
पूर्ण
EXPORT_SYMBOL_GPL(ptep_test_and_clear_uc);

पूर्णांक set_guest_storage_key(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			  अचिन्हित अक्षर key, bool nq)
अणु
	अचिन्हित दीर्घ keyul, paddr;
	spinlock_t *ptl;
	pgste_t old, new;
	pmd_t *pmdp;
	pte_t *ptep;

	pmdp = pmd_alloc_map(mm, addr);
	अगर (unlikely(!pmdp))
		वापस -EFAULT;

	ptl = pmd_lock(mm, pmdp);
	अगर (!pmd_present(*pmdp)) अणु
		spin_unlock(ptl);
		वापस -EFAULT;
	पूर्ण

	अगर (pmd_large(*pmdp)) अणु
		paddr = pmd_val(*pmdp) & HPAGE_MASK;
		paddr |= addr & ~HPAGE_MASK;
		/*
		 * Huge pmds need quiescing operations, they are
		 * always mapped.
		 */
		page_set_storage_key(paddr, key, 1);
		spin_unlock(ptl);
		वापस 0;
	पूर्ण
	spin_unlock(ptl);

	ptep = pte_alloc_map_lock(mm, pmdp, addr, &ptl);
	अगर (unlikely(!ptep))
		वापस -EFAULT;

	new = old = pgste_get_lock(ptep);
	pgste_val(new) &= ~(PGSTE_GR_BIT | PGSTE_GC_BIT |
			    PGSTE_ACC_BITS | PGSTE_FP_BIT);
	keyul = (अचिन्हित दीर्घ) key;
	pgste_val(new) |= (keyul & (_PAGE_CHANGED | _PAGE_REFERENCED)) << 48;
	pgste_val(new) |= (keyul & (_PAGE_ACC_BITS | _PAGE_FP_BIT)) << 56;
	अगर (!(pte_val(*ptep) & _PAGE_INVALID)) अणु
		अचिन्हित दीर्घ bits, skey;

		paddr = pte_val(*ptep) & PAGE_MASK;
		skey = (अचिन्हित दीर्घ) page_get_storage_key(paddr);
		bits = skey & (_PAGE_CHANGED | _PAGE_REFERENCED);
		skey = key & (_PAGE_ACC_BITS | _PAGE_FP_BIT);
		/* Set storage key ACC and FP */
		page_set_storage_key(paddr, skey, !nq);
		/* Merge host changed & referenced पूर्णांकo pgste  */
		pgste_val(new) |= bits << 52;
	पूर्ण
	/* changing the guest storage key is considered a change of the page */
	अगर ((pgste_val(new) ^ pgste_val(old)) &
	    (PGSTE_ACC_BITS | PGSTE_FP_BIT | PGSTE_GR_BIT | PGSTE_GC_BIT))
		pgste_val(new) |= PGSTE_UC_BIT;

	pgste_set_unlock(ptep, new);
	pte_unmap_unlock(ptep, ptl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(set_guest_storage_key);

/**
 * Conditionally set a guest storage key (handling csske).
 * oldkey will be updated when either mr or mc is set and a poपूर्णांकer is given.
 *
 * Returns 0 अगर a guests storage key update wasn't necessary, 1 अगर the guest
 * storage key was updated and -EFAULT on access errors.
 */
पूर्णांक cond_set_guest_storage_key(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			       अचिन्हित अक्षर key, अचिन्हित अक्षर *oldkey,
			       bool nq, bool mr, bool mc)
अणु
	अचिन्हित अक्षर पंचांगp, mask = _PAGE_ACC_BITS | _PAGE_FP_BIT;
	पूर्णांक rc;

	/* we can drop the pgste lock between getting and setting the key */
	अगर (mr | mc) अणु
		rc = get_guest_storage_key(current->mm, addr, &पंचांगp);
		अगर (rc)
			वापस rc;
		अगर (oldkey)
			*oldkey = पंचांगp;
		अगर (!mr)
			mask |= _PAGE_REFERENCED;
		अगर (!mc)
			mask |= _PAGE_CHANGED;
		अगर (!((पंचांगp ^ key) & mask))
			वापस 0;
	पूर्ण
	rc = set_guest_storage_key(current->mm, addr, key, nq);
	वापस rc < 0 ? rc : 1;
पूर्ण
EXPORT_SYMBOL(cond_set_guest_storage_key);

/**
 * Reset a guest reference bit (rrbe), वापसing the reference and changed bit.
 *
 * Returns < 0 in हाल of error, otherwise the cc to be reported to the guest.
 */
पूर्णांक reset_guest_reference_bit(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	spinlock_t *ptl;
	अचिन्हित दीर्घ paddr;
	pgste_t old, new;
	pmd_t *pmdp;
	pte_t *ptep;
	पूर्णांक cc = 0;

	pmdp = pmd_alloc_map(mm, addr);
	अगर (unlikely(!pmdp))
		वापस -EFAULT;

	ptl = pmd_lock(mm, pmdp);
	अगर (!pmd_present(*pmdp)) अणु
		spin_unlock(ptl);
		वापस -EFAULT;
	पूर्ण

	अगर (pmd_large(*pmdp)) अणु
		paddr = pmd_val(*pmdp) & HPAGE_MASK;
		paddr |= addr & ~HPAGE_MASK;
		cc = page_reset_referenced(paddr);
		spin_unlock(ptl);
		वापस cc;
	पूर्ण
	spin_unlock(ptl);

	ptep = pte_alloc_map_lock(mm, pmdp, addr, &ptl);
	अगर (unlikely(!ptep))
		वापस -EFAULT;

	new = old = pgste_get_lock(ptep);
	/* Reset guest reference bit only */
	pgste_val(new) &= ~PGSTE_GR_BIT;

	अगर (!(pte_val(*ptep) & _PAGE_INVALID)) अणु
		paddr = pte_val(*ptep) & PAGE_MASK;
		cc = page_reset_referenced(paddr);
		/* Merge real referenced bit पूर्णांकo host-set */
		pgste_val(new) |= ((अचिन्हित दीर्घ) cc << 53) & PGSTE_HR_BIT;
	पूर्ण
	/* Reflect guest's logical view, not physical */
	cc |= (pgste_val(old) & (PGSTE_GR_BIT | PGSTE_GC_BIT)) >> 49;
	/* Changing the guest storage key is considered a change of the page */
	अगर ((pgste_val(new) ^ pgste_val(old)) & PGSTE_GR_BIT)
		pgste_val(new) |= PGSTE_UC_BIT;

	pgste_set_unlock(ptep, new);
	pte_unmap_unlock(ptep, ptl);
	वापस cc;
पूर्ण
EXPORT_SYMBOL(reset_guest_reference_bit);

पूर्णांक get_guest_storage_key(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			  अचिन्हित अक्षर *key)
अणु
	अचिन्हित दीर्घ paddr;
	spinlock_t *ptl;
	pgste_t pgste;
	pmd_t *pmdp;
	pte_t *ptep;

	pmdp = pmd_alloc_map(mm, addr);
	अगर (unlikely(!pmdp))
		वापस -EFAULT;

	ptl = pmd_lock(mm, pmdp);
	अगर (!pmd_present(*pmdp)) अणु
		/* Not yet mapped memory has a zero key */
		spin_unlock(ptl);
		*key = 0;
		वापस 0;
	पूर्ण

	अगर (pmd_large(*pmdp)) अणु
		paddr = pmd_val(*pmdp) & HPAGE_MASK;
		paddr |= addr & ~HPAGE_MASK;
		*key = page_get_storage_key(paddr);
		spin_unlock(ptl);
		वापस 0;
	पूर्ण
	spin_unlock(ptl);

	ptep = pte_alloc_map_lock(mm, pmdp, addr, &ptl);
	अगर (unlikely(!ptep))
		वापस -EFAULT;

	pgste = pgste_get_lock(ptep);
	*key = (pgste_val(pgste) & (PGSTE_ACC_BITS | PGSTE_FP_BIT)) >> 56;
	paddr = pte_val(*ptep) & PAGE_MASK;
	अगर (!(pte_val(*ptep) & _PAGE_INVALID))
		*key = page_get_storage_key(paddr);
	/* Reflect guest's logical view, not physical */
	*key |= (pgste_val(pgste) & (PGSTE_GR_BIT | PGSTE_GC_BIT)) >> 48;
	pgste_set_unlock(ptep, pgste);
	pte_unmap_unlock(ptep, ptl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_guest_storage_key);

/**
 * pgste_perक्रमm_essa - perक्रमm ESSA actions on the PGSTE.
 * @mm: the memory context. It must have PGSTEs, no check is perक्रमmed here!
 * @hva: the host भव address of the page whose PGSTE is to be processed
 * @orc: the specअगरic action to perक्रमm, see the ESSA_SET_* macros.
 * @oldpte: the PTE will be saved there अगर the poपूर्णांकer is not शून्य.
 * @oldpgste: the old PGSTE will be saved there अगर the poपूर्णांकer is not शून्य.
 *
 * Return: 1 अगर the page is to be added to the CBRL, otherwise 0,
 *	   or < 0 in हाल of error. -EINVAL is वापसed क्रम invalid values
 *	   of orc, -EFAULT क्रम invalid addresses.
 */
पूर्णांक pgste_perक्रमm_essa(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ hva, पूर्णांक orc,
			अचिन्हित दीर्घ *oldpte, अचिन्हित दीर्घ *oldpgste)
अणु
	अचिन्हित दीर्घ pgstev;
	spinlock_t *ptl;
	pgste_t pgste;
	pte_t *ptep;
	पूर्णांक res = 0;

	WARN_ON_ONCE(orc > ESSA_MAX);
	अगर (unlikely(orc > ESSA_MAX))
		वापस -EINVAL;
	ptep = get_locked_pte(mm, hva, &ptl);
	अगर (unlikely(!ptep))
		वापस -EFAULT;
	pgste = pgste_get_lock(ptep);
	pgstev = pgste_val(pgste);
	अगर (oldpte)
		*oldpte = pte_val(*ptep);
	अगर (oldpgste)
		*oldpgste = pgstev;

	चयन (orc) अणु
	हाल ESSA_GET_STATE:
		अवरोध;
	हाल ESSA_SET_STABLE:
		pgstev &= ~(_PGSTE_GPS_USAGE_MASK | _PGSTE_GPS_NODAT);
		pgstev |= _PGSTE_GPS_USAGE_STABLE;
		अवरोध;
	हाल ESSA_SET_UNUSED:
		pgstev &= ~_PGSTE_GPS_USAGE_MASK;
		pgstev |= _PGSTE_GPS_USAGE_UNUSED;
		अगर (pte_val(*ptep) & _PAGE_INVALID)
			res = 1;
		अवरोध;
	हाल ESSA_SET_VOLATILE:
		pgstev &= ~_PGSTE_GPS_USAGE_MASK;
		pgstev |= _PGSTE_GPS_USAGE_VOLATILE;
		अगर (pte_val(*ptep) & _PAGE_INVALID)
			res = 1;
		अवरोध;
	हाल ESSA_SET_POT_VOLATILE:
		pgstev &= ~_PGSTE_GPS_USAGE_MASK;
		अगर (!(pte_val(*ptep) & _PAGE_INVALID)) अणु
			pgstev |= _PGSTE_GPS_USAGE_POT_VOLATILE;
			अवरोध;
		पूर्ण
		अगर (pgstev & _PGSTE_GPS_ZERO) अणु
			pgstev |= _PGSTE_GPS_USAGE_VOLATILE;
			अवरोध;
		पूर्ण
		अगर (!(pgstev & PGSTE_GC_BIT)) अणु
			pgstev |= _PGSTE_GPS_USAGE_VOLATILE;
			res = 1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ESSA_SET_STABLE_RESIDENT:
		pgstev &= ~_PGSTE_GPS_USAGE_MASK;
		pgstev |= _PGSTE_GPS_USAGE_STABLE;
		/*
		 * Since the resident state can go away any समय after this
		 * call, we will not make this page resident. We can revisit
		 * this decision अगर a guest will ever start using this.
		 */
		अवरोध;
	हाल ESSA_SET_STABLE_IF_RESIDENT:
		अगर (!(pte_val(*ptep) & _PAGE_INVALID)) अणु
			pgstev &= ~_PGSTE_GPS_USAGE_MASK;
			pgstev |= _PGSTE_GPS_USAGE_STABLE;
		पूर्ण
		अवरोध;
	हाल ESSA_SET_STABLE_NODAT:
		pgstev &= ~_PGSTE_GPS_USAGE_MASK;
		pgstev |= _PGSTE_GPS_USAGE_STABLE | _PGSTE_GPS_NODAT;
		अवरोध;
	शेष:
		/* we should never get here! */
		अवरोध;
	पूर्ण
	/* If we are discarding a page, set it to logical zero */
	अगर (res)
		pgstev |= _PGSTE_GPS_ZERO;

	pgste_val(pgste) = pgstev;
	pgste_set_unlock(ptep, pgste);
	pte_unmap_unlock(ptep, ptl);
	वापस res;
पूर्ण
EXPORT_SYMBOL(pgste_perक्रमm_essa);

/**
 * set_pgste_bits - set specअगरic PGSTE bits.
 * @mm: the memory context. It must have PGSTEs, no check is perक्रमmed here!
 * @hva: the host भव address of the page whose PGSTE is to be processed
 * @bits: a biपंचांगask representing the bits that will be touched
 * @value: the values of the bits to be written. Only the bits in the mask
 *	   will be written.
 *
 * Return: 0 on success, < 0 in हाल of error.
 */
पूर्णांक set_pgste_bits(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ hva,
			अचिन्हित दीर्घ bits, अचिन्हित दीर्घ value)
अणु
	spinlock_t *ptl;
	pgste_t new;
	pte_t *ptep;

	ptep = get_locked_pte(mm, hva, &ptl);
	अगर (unlikely(!ptep))
		वापस -EFAULT;
	new = pgste_get_lock(ptep);

	pgste_val(new) &= ~bits;
	pgste_val(new) |= value & bits;

	pgste_set_unlock(ptep, new);
	pte_unmap_unlock(ptep, ptl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(set_pgste_bits);

/**
 * get_pgste - get the current PGSTE क्रम the given address.
 * @mm: the memory context. It must have PGSTEs, no check is perक्रमmed here!
 * @hva: the host भव address of the page whose PGSTE is to be processed
 * @pgstep: will be written with the current PGSTE क्रम the given address.
 *
 * Return: 0 on success, < 0 in हाल of error.
 */
पूर्णांक get_pgste(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ hva, अचिन्हित दीर्घ *pgstep)
अणु
	spinlock_t *ptl;
	pte_t *ptep;

	ptep = get_locked_pte(mm, hva, &ptl);
	अगर (unlikely(!ptep))
		वापस -EFAULT;
	*pgstep = pgste_val(pgste_get(ptep));
	pte_unmap_unlock(ptep, ptl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_pgste);
#पूर्ण_अगर
