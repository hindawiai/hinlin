<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Xen mmu operations
 *
 * This file contains the various mmu fetch and update operations.
 * The most important job they must perक्रमm is the mapping between the
 * करोमुख्य's pfn and the overall machine mfns.
 *
 * Xen allows guests to directly update the pagetable, in a controlled
 * fashion.  In other words, the guest modअगरies the same pagetable
 * that the CPU actually uses, which eliminates the overhead of having
 * a separate shaकरोw pagetable.
 *
 * In order to allow this, it falls on the guest करोमुख्य to map its
 * notion of a "physical" pfn - which is just a करोमुख्य-local linear
 * address - पूर्णांकo a real "machine address" which the CPU's MMU can
 * use.
 *
 * A pgd_t/pmd_t/pte_t will typically contain an mfn, and so can be
 * inserted directly पूर्णांकo the pagetable.  When creating a new
 * pte/pmd/pgd, it converts the passed pfn पूर्णांकo an mfn.  Conversely,
 * when पढ़ोing the content back with __(pgd|pmd|pte)_val, it converts
 * the mfn back पूर्णांकo a pfn.
 *
 * The other स्थिरraपूर्णांक is that all pages which make up a pagetable
 * must be mapped पढ़ो-only in the guest.  This prevents uncontrolled
 * guest updates to the pagetable.  Xen strictly enक्रमces this, and
 * will disallow any pagetable update which will end up mapping a
 * pagetable page RW, and will disallow using any writable page as a
 * pagetable.
 *
 * Naively, when loading %cr3 with the base of a new pagetable, Xen
 * would need to validate the whole pagetable beक्रमe going on.
 * Naturally, this is quite slow.  The solution is to "pin" a
 * pagetable, which enक्रमces all the स्थिरraपूर्णांकs on the pagetable even
 * when it is not actively in use.  This menas that Xen can be assured
 * that it is still valid when you करो load it पूर्णांकo %cr3, and करोesn't
 * need to revalidate it.
 *
 * Jeremy Fitzhardinge <jeremy@xensource.com>, XenSource Inc, 2007
 */
#समावेश <linux/sched/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/bug.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <linux/memblock.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/pgtable.h>
#अगर_घोषित CONFIG_KEXEC_CORE
#समावेश <linux/kexec.h>
#पूर्ण_अगर

#समावेश <trace/events/xen.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/linkage.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/init.h>
#समावेश <यंत्र/memtype.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/tlb.h>

#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <xen/xen.h>
#समावेश <xen/page.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/hvm/hvm_op.h>
#समावेश <xen/पूर्णांकerface/version.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/hvc-console.h>

#समावेश "multicalls.h"
#समावेश "mmu.h"
#समावेश "debugfs.h"

/* l3 pud क्रम userspace vsyscall mapping */
अटल pud_t level3_user_vsyscall[PTRS_PER_PUD] __page_aligned_bss;

/*
 * Protects atomic reservation decrease/increase against concurrent increases.
 * Also protects non-atomic updates of current_pages and balloon lists.
 */
अटल DEFINE_SPINLOCK(xen_reservation_lock);

/*
 * Note about cr3 (pagetable base) values:
 *
 * xen_cr3 contains the current logical cr3 value; it contains the
 * last set cr3.  This may not be the current effective cr3, because
 * its update may be being lazily deferred.  However, a vcpu looking
 * at its own cr3 can use this value knowing that it everything will
 * be self-consistent.
 *
 * xen_current_cr3 contains the actual vcpu cr3; it is set once the
 * hypercall to set the vcpu cr3 is complete (so it may be a little
 * out of date, but it will never be set early).  If one vcpu is
 * looking at another vcpu's cr3 value, it should use this variable.
 */
DEFINE_PER_CPU(अचिन्हित दीर्घ, xen_cr3);	 /* cr3 stored as physaddr */
DEFINE_PER_CPU(अचिन्हित दीर्घ, xen_current_cr3);	 /* actual vcpu cr3 */

अटल phys_addr_t xen_pt_base, xen_pt_size __initdata;

अटल DEFINE_STATIC_KEY_FALSE(xen_काष्ठा_pages_पढ़ोy);

/*
 * Just beyond the highest usermode address.  STACK_TOP_MAX has a
 * redzone above it, so round it up to a PGD boundary.
 */
#घोषणा USER_LIMIT	((STACK_TOP_MAX + PGसूची_SIZE - 1) & PGसूची_MASK)

व्योम make_lowmem_page_पढ़ोonly(व्योम *vaddr)
अणु
	pte_t *pte, ptev;
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)vaddr;
	अचिन्हित पूर्णांक level;

	pte = lookup_address(address, &level);
	अगर (pte == शून्य)
		वापस;		/* vaddr missing */

	ptev = pte_wrprotect(*pte);

	अगर (HYPERVISOR_update_va_mapping(address, ptev, 0))
		BUG();
पूर्ण

व्योम make_lowmem_page_पढ़ोग_लिखो(व्योम *vaddr)
अणु
	pte_t *pte, ptev;
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)vaddr;
	अचिन्हित पूर्णांक level;

	pte = lookup_address(address, &level);
	अगर (pte == शून्य)
		वापस;		/* vaddr missing */

	ptev = pte_mkग_लिखो(*pte);

	अगर (HYPERVISOR_update_va_mapping(address, ptev, 0))
		BUG();
पूर्ण


/*
 * During early boot all page table pages are pinned, but we करो not have काष्ठा
 * pages, so वापस true until काष्ठा pages are पढ़ोy.
 */
अटल bool xen_page_pinned(व्योम *ptr)
अणु
	अगर (अटल_branch_likely(&xen_काष्ठा_pages_पढ़ोy)) अणु
		काष्ठा page *page = virt_to_page(ptr);

		वापस PagePinned(page);
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम xen_extend_mmu_update(स्थिर काष्ठा mmu_update *update)
अणु
	काष्ठा multicall_space mcs;
	काष्ठा mmu_update *u;

	mcs = xen_mc_extend_args(__HYPERVISOR_mmu_update, माप(*u));

	अगर (mcs.mc != शून्य) अणु
		mcs.mc->args[1]++;
	पूर्ण अन्यथा अणु
		mcs = __xen_mc_entry(माप(*u));
		MULTI_mmu_update(mcs.mc, mcs.args, 1, शून्य, DOMID_SELF);
	पूर्ण

	u = mcs.args;
	*u = *update;
पूर्ण

अटल व्योम xen_extend_mmuext_op(स्थिर काष्ठा mmuext_op *op)
अणु
	काष्ठा multicall_space mcs;
	काष्ठा mmuext_op *u;

	mcs = xen_mc_extend_args(__HYPERVISOR_mmuext_op, माप(*u));

	अगर (mcs.mc != शून्य) अणु
		mcs.mc->args[1]++;
	पूर्ण अन्यथा अणु
		mcs = __xen_mc_entry(माप(*u));
		MULTI_mmuext_op(mcs.mc, mcs.args, 1, शून्य, DOMID_SELF);
	पूर्ण

	u = mcs.args;
	*u = *op;
पूर्ण

अटल व्योम xen_set_pmd_hyper(pmd_t *ptr, pmd_t val)
अणु
	काष्ठा mmu_update u;

	preempt_disable();

	xen_mc_batch();

	/* ptr may be ioremapped क्रम 64-bit pagetable setup */
	u.ptr = arbitrary_virt_to_machine(ptr).maddr;
	u.val = pmd_val_ma(val);
	xen_extend_mmu_update(&u);

	xen_mc_issue(PARAVIRT_LAZY_MMU);

	preempt_enable();
पूर्ण

अटल व्योम xen_set_pmd(pmd_t *ptr, pmd_t val)
अणु
	trace_xen_mmu_set_pmd(ptr, val);

	/* If page is not pinned, we can just update the entry
	   directly */
	अगर (!xen_page_pinned(ptr)) अणु
		*ptr = val;
		वापस;
	पूर्ण

	xen_set_pmd_hyper(ptr, val);
पूर्ण

/*
 * Associate a भव page frame with a given physical page frame
 * and protection flags क्रम that frame.
 */
व्योम set_pte_mfn(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ mfn, pgprot_t flags)
अणु
	set_pte_vaddr(vaddr, mfn_pte(mfn, flags));
पूर्ण

अटल bool xen_batched_set_pte(pte_t *ptep, pte_t pteval)
अणु
	काष्ठा mmu_update u;

	अगर (paravirt_get_lazy_mode() != PARAVIRT_LAZY_MMU)
		वापस false;

	xen_mc_batch();

	u.ptr = virt_to_machine(ptep).maddr | MMU_NORMAL_PT_UPDATE;
	u.val = pte_val_ma(pteval);
	xen_extend_mmu_update(&u);

	xen_mc_issue(PARAVIRT_LAZY_MMU);

	वापस true;
पूर्ण

अटल अंतरभूत व्योम __xen_set_pte(pte_t *ptep, pte_t pteval)
अणु
	अगर (!xen_batched_set_pte(ptep, pteval)) अणु
		/*
		 * Could call native_set_pte() here and trap and
		 * emulate the PTE ग_लिखो, but a hypercall is much cheaper.
		 */
		काष्ठा mmu_update u;

		u.ptr = virt_to_machine(ptep).maddr | MMU_NORMAL_PT_UPDATE;
		u.val = pte_val_ma(pteval);
		HYPERVISOR_mmu_update(&u, 1, शून्य, DOMID_SELF);
	पूर्ण
पूर्ण

अटल व्योम xen_set_pte(pte_t *ptep, pte_t pteval)
अणु
	trace_xen_mmu_set_pte(ptep, pteval);
	__xen_set_pte(ptep, pteval);
पूर्ण

pte_t xen_ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	/* Just वापस the pte as-is.  We preserve the bits on commit */
	trace_xen_mmu_ptep_modअगरy_prot_start(vma->vm_mm, addr, ptep, *ptep);
	वापस *ptep;
पूर्ण

व्योम xen_ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				 pte_t *ptep, pte_t pte)
अणु
	काष्ठा mmu_update u;

	trace_xen_mmu_ptep_modअगरy_prot_commit(vma->vm_mm, addr, ptep, pte);
	xen_mc_batch();

	u.ptr = virt_to_machine(ptep).maddr | MMU_PT_UPDATE_PRESERVE_AD;
	u.val = pte_val_ma(pte);
	xen_extend_mmu_update(&u);

	xen_mc_issue(PARAVIRT_LAZY_MMU);
पूर्ण

/* Assume pteval_t is equivalent to all the other *val_t types. */
अटल pteval_t pte_mfn_to_pfn(pteval_t val)
अणु
	अगर (val & _PAGE_PRESENT) अणु
		अचिन्हित दीर्घ mfn = (val & XEN_PTE_MFN_MASK) >> PAGE_SHIFT;
		अचिन्हित दीर्घ pfn = mfn_to_pfn(mfn);

		pteval_t flags = val & PTE_FLAGS_MASK;
		अगर (unlikely(pfn == ~0))
			val = flags & ~_PAGE_PRESENT;
		अन्यथा
			val = ((pteval_t)pfn << PAGE_SHIFT) | flags;
	पूर्ण

	वापस val;
पूर्ण

अटल pteval_t pte_pfn_to_mfn(pteval_t val)
अणु
	अगर (val & _PAGE_PRESENT) अणु
		अचिन्हित दीर्घ pfn = (val & PTE_PFN_MASK) >> PAGE_SHIFT;
		pteval_t flags = val & PTE_FLAGS_MASK;
		अचिन्हित दीर्घ mfn;

		mfn = __pfn_to_mfn(pfn);

		/*
		 * If there's no mfn क्रम the pfn, then just create an
		 * empty non-present pte.  Unक्रमtunately this loses
		 * inक्रमmation about the original pfn, so
		 * pte_mfn_to_pfn is asymmetric.
		 */
		अगर (unlikely(mfn == INVALID_P2M_ENTRY)) अणु
			mfn = 0;
			flags = 0;
		पूर्ण अन्यथा
			mfn &= ~(FOREIGN_FRAME_BIT | IDENTITY_FRAME_BIT);
		val = ((pteval_t)mfn << PAGE_SHIFT) | flags;
	पूर्ण

	वापस val;
पूर्ण

__visible pteval_t xen_pte_val(pte_t pte)
अणु
	pteval_t pteval = pte.pte;

	वापस pte_mfn_to_pfn(pteval);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_pte_val);

__visible pgdval_t xen_pgd_val(pgd_t pgd)
अणु
	वापस pte_mfn_to_pfn(pgd.pgd);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_pgd_val);

__visible pte_t xen_make_pte(pteval_t pte)
अणु
	pte = pte_pfn_to_mfn(pte);

	वापस native_make_pte(pte);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_make_pte);

__visible pgd_t xen_make_pgd(pgdval_t pgd)
अणु
	pgd = pte_pfn_to_mfn(pgd);
	वापस native_make_pgd(pgd);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_make_pgd);

__visible pmdval_t xen_pmd_val(pmd_t pmd)
अणु
	वापस pte_mfn_to_pfn(pmd.pmd);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_pmd_val);

अटल व्योम xen_set_pud_hyper(pud_t *ptr, pud_t val)
अणु
	काष्ठा mmu_update u;

	preempt_disable();

	xen_mc_batch();

	/* ptr may be ioremapped क्रम 64-bit pagetable setup */
	u.ptr = arbitrary_virt_to_machine(ptr).maddr;
	u.val = pud_val_ma(val);
	xen_extend_mmu_update(&u);

	xen_mc_issue(PARAVIRT_LAZY_MMU);

	preempt_enable();
पूर्ण

अटल व्योम xen_set_pud(pud_t *ptr, pud_t val)
अणु
	trace_xen_mmu_set_pud(ptr, val);

	/* If page is not pinned, we can just update the entry
	   directly */
	अगर (!xen_page_pinned(ptr)) अणु
		*ptr = val;
		वापस;
	पूर्ण

	xen_set_pud_hyper(ptr, val);
पूर्ण

__visible pmd_t xen_make_pmd(pmdval_t pmd)
अणु
	pmd = pte_pfn_to_mfn(pmd);
	वापस native_make_pmd(pmd);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_make_pmd);

__visible pudval_t xen_pud_val(pud_t pud)
अणु
	वापस pte_mfn_to_pfn(pud.pud);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_pud_val);

__visible pud_t xen_make_pud(pudval_t pud)
अणु
	pud = pte_pfn_to_mfn(pud);

	वापस native_make_pud(pud);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_make_pud);

अटल pgd_t *xen_get_user_pgd(pgd_t *pgd)
अणु
	pgd_t *pgd_page = (pgd_t *)(((अचिन्हित दीर्घ)pgd) & PAGE_MASK);
	अचिन्हित offset = pgd - pgd_page;
	pgd_t *user_ptr = शून्य;

	अगर (offset < pgd_index(USER_LIMIT)) अणु
		काष्ठा page *page = virt_to_page(pgd_page);
		user_ptr = (pgd_t *)page->निजी;
		अगर (user_ptr)
			user_ptr += offset;
	पूर्ण

	वापस user_ptr;
पूर्ण

अटल व्योम __xen_set_p4d_hyper(p4d_t *ptr, p4d_t val)
अणु
	काष्ठा mmu_update u;

	u.ptr = virt_to_machine(ptr).maddr;
	u.val = p4d_val_ma(val);
	xen_extend_mmu_update(&u);
पूर्ण

/*
 * Raw hypercall-based set_p4d, पूर्णांकended क्रम in early boot beक्रमe
 * there's a page काष्ठाure.  This implies:
 *  1. The only existing pagetable is the kernel's
 *  2. It is always pinned
 *  3. It has no user pagetable attached to it
 */
अटल व्योम __init xen_set_p4d_hyper(p4d_t *ptr, p4d_t val)
अणु
	preempt_disable();

	xen_mc_batch();

	__xen_set_p4d_hyper(ptr, val);

	xen_mc_issue(PARAVIRT_LAZY_MMU);

	preempt_enable();
पूर्ण

अटल व्योम xen_set_p4d(p4d_t *ptr, p4d_t val)
अणु
	pgd_t *user_ptr = xen_get_user_pgd((pgd_t *)ptr);
	pgd_t pgd_val;

	trace_xen_mmu_set_p4d(ptr, (p4d_t *)user_ptr, val);

	/* If page is not pinned, we can just update the entry
	   directly */
	अगर (!xen_page_pinned(ptr)) अणु
		*ptr = val;
		अगर (user_ptr) अणु
			WARN_ON(xen_page_pinned(user_ptr));
			pgd_val.pgd = p4d_val_ma(val);
			*user_ptr = pgd_val;
		पूर्ण
		वापस;
	पूर्ण

	/* If it's pinned, then we can at least batch the kernel and
	   user updates together. */
	xen_mc_batch();

	__xen_set_p4d_hyper(ptr, val);
	अगर (user_ptr)
		__xen_set_p4d_hyper((p4d_t *)user_ptr, val);

	xen_mc_issue(PARAVIRT_LAZY_MMU);
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS >= 5
__visible p4dval_t xen_p4d_val(p4d_t p4d)
अणु
	वापस pte_mfn_to_pfn(p4d.p4d);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_p4d_val);

__visible p4d_t xen_make_p4d(p4dval_t p4d)
अणु
	p4d = pte_pfn_to_mfn(p4d);

	वापस native_make_p4d(p4d);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_make_p4d);
#पूर्ण_अगर  /* CONFIG_PGTABLE_LEVELS >= 5 */

अटल व्योम xen_pmd_walk(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
			 व्योम (*func)(काष्ठा mm_काष्ठा *mm, काष्ठा page *,
				      क्रमागत pt_level),
			 bool last, अचिन्हित दीर्घ limit)
अणु
	पूर्णांक i, nr;

	nr = last ? pmd_index(limit) + 1 : PTRS_PER_PMD;
	क्रम (i = 0; i < nr; i++) अणु
		अगर (!pmd_none(pmd[i]))
			(*func)(mm, pmd_page(pmd[i]), PT_PTE);
	पूर्ण
पूर्ण

अटल व्योम xen_pud_walk(काष्ठा mm_काष्ठा *mm, pud_t *pud,
			 व्योम (*func)(काष्ठा mm_काष्ठा *mm, काष्ठा page *,
				      क्रमागत pt_level),
			 bool last, अचिन्हित दीर्घ limit)
अणु
	पूर्णांक i, nr;

	nr = last ? pud_index(limit) + 1 : PTRS_PER_PUD;
	क्रम (i = 0; i < nr; i++) अणु
		pmd_t *pmd;

		अगर (pud_none(pud[i]))
			जारी;

		pmd = pmd_offset(&pud[i], 0);
		अगर (PTRS_PER_PMD > 1)
			(*func)(mm, virt_to_page(pmd), PT_PMD);
		xen_pmd_walk(mm, pmd, func, last && i == nr - 1, limit);
	पूर्ण
पूर्ण

अटल व्योम xen_p4d_walk(काष्ठा mm_काष्ठा *mm, p4d_t *p4d,
			 व्योम (*func)(काष्ठा mm_काष्ठा *mm, काष्ठा page *,
				      क्रमागत pt_level),
			 bool last, अचिन्हित दीर्घ limit)
अणु
	pud_t *pud;


	अगर (p4d_none(*p4d))
		वापस;

	pud = pud_offset(p4d, 0);
	अगर (PTRS_PER_PUD > 1)
		(*func)(mm, virt_to_page(pud), PT_PUD);
	xen_pud_walk(mm, pud, func, last, limit);
पूर्ण

/*
 * (Yet another) pagetable walker.  This one is पूर्णांकended क्रम pinning a
 * pagetable.  This means that it walks a pagetable and calls the
 * callback function on each page it finds making up the page table,
 * at every level.  It walks the entire pagetable, but it only bothers
 * pinning pte pages which are below limit.  In the normal हाल this
 * will be STACK_TOP_MAX, but at boot we need to pin up to
 * FIXADDR_TOP.
 *
 * We must skip the Xen hole in the middle of the address space, just after
 * the big x86-64 भव hole.
 */
अटल व्योम __xen_pgd_walk(काष्ठा mm_काष्ठा *mm, pgd_t *pgd,
			   व्योम (*func)(काष्ठा mm_काष्ठा *mm, काष्ठा page *,
					क्रमागत pt_level),
			   अचिन्हित दीर्घ limit)
अणु
	पूर्णांक i, nr;
	अचिन्हित hole_low = 0, hole_high = 0;

	/* The limit is the last byte to be touched */
	limit--;
	BUG_ON(limit >= FIXADDR_TOP);

	/*
	 * 64-bit has a great big hole in the middle of the address
	 * space, which contains the Xen mappings.
	 */
	hole_low = pgd_index(GUARD_HOLE_BASE_ADDR);
	hole_high = pgd_index(GUARD_HOLE_END_ADDR);

	nr = pgd_index(limit) + 1;
	क्रम (i = 0; i < nr; i++) अणु
		p4d_t *p4d;

		अगर (i >= hole_low && i < hole_high)
			जारी;

		अगर (pgd_none(pgd[i]))
			जारी;

		p4d = p4d_offset(&pgd[i], 0);
		xen_p4d_walk(mm, p4d, func, i == nr - 1, limit);
	पूर्ण

	/* Do the top level last, so that the callbacks can use it as
	   a cue to करो final things like tlb flushes. */
	(*func)(mm, virt_to_page(pgd), PT_PGD);
पूर्ण

अटल व्योम xen_pgd_walk(काष्ठा mm_काष्ठा *mm,
			 व्योम (*func)(काष्ठा mm_काष्ठा *mm, काष्ठा page *,
				      क्रमागत pt_level),
			 अचिन्हित दीर्घ limit)
अणु
	__xen_pgd_walk(mm, mm->pgd, func, limit);
पूर्ण

/* If we're using split pte locks, then take the page's lock and
   वापस a poपूर्णांकer to it.  Otherwise वापस शून्य. */
अटल spinlock_t *xen_pte_lock(काष्ठा page *page, काष्ठा mm_काष्ठा *mm)
अणु
	spinlock_t *ptl = शून्य;

#अगर USE_SPLIT_PTE_PTLOCKS
	ptl = ptlock_ptr(page);
	spin_lock_nest_lock(ptl, &mm->page_table_lock);
#पूर्ण_अगर

	वापस ptl;
पूर्ण

अटल व्योम xen_pte_unlock(व्योम *v)
अणु
	spinlock_t *ptl = v;
	spin_unlock(ptl);
पूर्ण

अटल व्योम xen_करो_pin(अचिन्हित level, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा mmuext_op op;

	op.cmd = level;
	op.arg1.mfn = pfn_to_mfn(pfn);

	xen_extend_mmuext_op(&op);
पूर्ण

अटल व्योम xen_pin_page(काष्ठा mm_काष्ठा *mm, काष्ठा page *page,
			 क्रमागत pt_level level)
अणु
	अचिन्हित pgfl = TestSetPagePinned(page);

	अगर (!pgfl) अणु
		व्योम *pt = lowmem_page_address(page);
		अचिन्हित दीर्घ pfn = page_to_pfn(page);
		काष्ठा multicall_space mcs = __xen_mc_entry(0);
		spinlock_t *ptl;

		/*
		 * We need to hold the pagetable lock between the समय
		 * we make the pagetable RO and when we actually pin
		 * it.  If we करोn't, then other users may come in and
		 * attempt to update the pagetable by writing it,
		 * which will fail because the memory is RO but not
		 * pinned, so Xen won't do the trap'n'emulate.
		 *
		 * If we're using split pte locks, we can't hold the
		 * entire pagetable's worth of locks during the
		 * traverse, because we may wrap the preempt count (8
		 * bits).  The solution is to mark RO and pin each PTE
		 * page जबतक holding the lock.  This means the number
		 * of locks we end up holding is never more than a
		 * batch size (~32 entries, at present).
		 *
		 * If we're not using split pte locks, we needn't pin
		 * the PTE pages independently, because we're
		 * रक्षित by the overall pagetable lock.
		 */
		ptl = शून्य;
		अगर (level == PT_PTE)
			ptl = xen_pte_lock(page, mm);

		MULTI_update_va_mapping(mcs.mc, (अचिन्हित दीर्घ)pt,
					pfn_pte(pfn, PAGE_KERNEL_RO),
					level == PT_PGD ? UVMF_TLB_FLUSH : 0);

		अगर (ptl) अणु
			xen_करो_pin(MMUEXT_PIN_L1_TABLE, pfn);

			/* Queue a deferred unlock क्रम when this batch
			   is completed. */
			xen_mc_callback(xen_pte_unlock, ptl);
		पूर्ण
	पूर्ण
पूर्ण

/* This is called just after a mm has been created, but it has not
   been used yet.  We need to make sure that its pagetable is all
   पढ़ो-only, and can be pinned. */
अटल व्योम __xen_pgd_pin(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	pgd_t *user_pgd = xen_get_user_pgd(pgd);

	trace_xen_mmu_pgd_pin(mm, pgd);

	xen_mc_batch();

	__xen_pgd_walk(mm, pgd, xen_pin_page, USER_LIMIT);

	xen_करो_pin(MMUEXT_PIN_L4_TABLE, PFN_DOWN(__pa(pgd)));

	अगर (user_pgd) अणु
		xen_pin_page(mm, virt_to_page(user_pgd), PT_PGD);
		xen_करो_pin(MMUEXT_PIN_L4_TABLE,
			   PFN_DOWN(__pa(user_pgd)));
	पूर्ण

	xen_mc_issue(0);
पूर्ण

अटल व्योम xen_pgd_pin(काष्ठा mm_काष्ठा *mm)
अणु
	__xen_pgd_pin(mm, mm->pgd);
पूर्ण

/*
 * On save, we need to pin all pagetables to make sure they get their
 * mfns turned पूर्णांकo pfns.  Search the list क्रम any unpinned pgds and pin
 * them (unpinned pgds are not currently in use, probably because the
 * process is under स्थिरruction or deकाष्ठाion).
 *
 * Expected to be called in stop_machine() ("equivalent to taking
 * every spinlock in the प्रणाली"), so the locking करोesn't really
 * matter all that much.
 */
व्योम xen_mm_pin_all(व्योम)
अणु
	काष्ठा page *page;

	spin_lock(&pgd_lock);

	list_क्रम_each_entry(page, &pgd_list, lru) अणु
		अगर (!PagePinned(page)) अणु
			__xen_pgd_pin(&init_mm, (pgd_t *)page_address(page));
			SetPageSavePinned(page);
		पूर्ण
	पूर्ण

	spin_unlock(&pgd_lock);
पूर्ण

अटल व्योम __init xen_mark_pinned(काष्ठा mm_काष्ठा *mm, काष्ठा page *page,
				   क्रमागत pt_level level)
अणु
	SetPagePinned(page);
पूर्ण

/*
 * The init_mm pagetable is really pinned as soon as its created, but
 * that's beक्रमe we have page काष्ठाures to store the bits.  So करो all
 * the book-keeping now once काष्ठा pages क्रम allocated pages are
 * initialized. This happens only after memblock_मुक्त_all() is called.
 */
अटल व्योम __init xen_after_booपंचांगem(व्योम)
अणु
	अटल_branch_enable(&xen_काष्ठा_pages_पढ़ोy);
	SetPagePinned(virt_to_page(level3_user_vsyscall));
	xen_pgd_walk(&init_mm, xen_mark_pinned, FIXADDR_TOP);
पूर्ण

अटल व्योम xen_unpin_page(काष्ठा mm_काष्ठा *mm, काष्ठा page *page,
			   क्रमागत pt_level level)
अणु
	अचिन्हित pgfl = TestClearPagePinned(page);

	अगर (pgfl) अणु
		व्योम *pt = lowmem_page_address(page);
		अचिन्हित दीर्घ pfn = page_to_pfn(page);
		spinlock_t *ptl = शून्य;
		काष्ठा multicall_space mcs;

		/*
		 * Do the converse to pin_page.  If we're using split
		 * pte locks, we must be holding the lock क्रम जबतक
		 * the pte page is unpinned but still RO to prevent
		 * concurrent updates from seeing it in this
		 * partially-pinned state.
		 */
		अगर (level == PT_PTE) अणु
			ptl = xen_pte_lock(page, mm);

			अगर (ptl)
				xen_करो_pin(MMUEXT_UNPIN_TABLE, pfn);
		पूर्ण

		mcs = __xen_mc_entry(0);

		MULTI_update_va_mapping(mcs.mc, (अचिन्हित दीर्घ)pt,
					pfn_pte(pfn, PAGE_KERNEL),
					level == PT_PGD ? UVMF_TLB_FLUSH : 0);

		अगर (ptl) अणु
			/* unlock when batch completed */
			xen_mc_callback(xen_pte_unlock, ptl);
		पूर्ण
	पूर्ण
पूर्ण

/* Release a pagetables pages back as normal RW */
अटल व्योम __xen_pgd_unpin(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	pgd_t *user_pgd = xen_get_user_pgd(pgd);

	trace_xen_mmu_pgd_unpin(mm, pgd);

	xen_mc_batch();

	xen_करो_pin(MMUEXT_UNPIN_TABLE, PFN_DOWN(__pa(pgd)));

	अगर (user_pgd) अणु
		xen_करो_pin(MMUEXT_UNPIN_TABLE,
			   PFN_DOWN(__pa(user_pgd)));
		xen_unpin_page(mm, virt_to_page(user_pgd), PT_PGD);
	पूर्ण

	__xen_pgd_walk(mm, pgd, xen_unpin_page, USER_LIMIT);

	xen_mc_issue(0);
पूर्ण

अटल व्योम xen_pgd_unpin(काष्ठा mm_काष्ठा *mm)
अणु
	__xen_pgd_unpin(mm, mm->pgd);
पूर्ण

/*
 * On resume, unकरो any pinning करोne at save, so that the rest of the
 * kernel करोesn't see any unexpected pinned pagetables.
 */
व्योम xen_mm_unpin_all(व्योम)
अणु
	काष्ठा page *page;

	spin_lock(&pgd_lock);

	list_क्रम_each_entry(page, &pgd_list, lru) अणु
		अगर (PageSavePinned(page)) अणु
			BUG_ON(!PagePinned(page));
			__xen_pgd_unpin(&init_mm, (pgd_t *)page_address(page));
			ClearPageSavePinned(page);
		पूर्ण
	पूर्ण

	spin_unlock(&pgd_lock);
पूर्ण

अटल व्योम xen_activate_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next)
अणु
	spin_lock(&next->page_table_lock);
	xen_pgd_pin(next);
	spin_unlock(&next->page_table_lock);
पूर्ण

अटल व्योम xen_dup_mmap(काष्ठा mm_काष्ठा *oldmm, काष्ठा mm_काष्ठा *mm)
अणु
	spin_lock(&mm->page_table_lock);
	xen_pgd_pin(mm);
	spin_unlock(&mm->page_table_lock);
पूर्ण

अटल व्योम drop_mm_ref_this_cpu(व्योम *info)
अणु
	काष्ठा mm_काष्ठा *mm = info;

	अगर (this_cpu_पढ़ो(cpu_tlbstate.loaded_mm) == mm)
		leave_mm(smp_processor_id());

	/*
	 * If this cpu still has a stale cr3 reference, then make sure
	 * it has been flushed.
	 */
	अगर (this_cpu_पढ़ो(xen_current_cr3) == __pa(mm->pgd))
		xen_mc_flush();
पूर्ण

#अगर_घोषित CONFIG_SMP
/*
 * Another cpu may still have their %cr3 poपूर्णांकing at the pagetable, so
 * we need to repoपूर्णांक it somewhere अन्यथा beक्रमe we can unpin it.
 */
अटल व्योम xen_drop_mm_ref(काष्ठा mm_काष्ठा *mm)
अणु
	cpumask_var_t mask;
	अचिन्हित cpu;

	drop_mm_ref_this_cpu(mm);

	/* Get the "official" set of cpus referring to our pagetable. */
	अगर (!alloc_cpumask_var(&mask, GFP_ATOMIC)) अणु
		क्रम_each_online_cpu(cpu) अणु
			अगर (per_cpu(xen_current_cr3, cpu) != __pa(mm->pgd))
				जारी;
			smp_call_function_single(cpu, drop_mm_ref_this_cpu, mm, 1);
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * It's possible that a vcpu may have a stale reference to our
	 * cr3, because its in lazy mode, and it hasn't yet flushed
	 * its set of pending hypercalls yet.  In this हाल, we can
	 * look at its actual current cr3 value, and क्रमce it to flush
	 * अगर needed.
	 */
	cpumask_clear(mask);
	क्रम_each_online_cpu(cpu) अणु
		अगर (per_cpu(xen_current_cr3, cpu) == __pa(mm->pgd))
			cpumask_set_cpu(cpu, mask);
	पूर्ण

	smp_call_function_many(mask, drop_mm_ref_this_cpu, mm, 1);
	मुक्त_cpumask_var(mask);
पूर्ण
#अन्यथा
अटल व्योम xen_drop_mm_ref(काष्ठा mm_काष्ठा *mm)
अणु
	drop_mm_ref_this_cpu(mm);
पूर्ण
#पूर्ण_अगर

/*
 * While a process runs, Xen pins its pagetables, which means that the
 * hypervisor क्रमces it to be पढ़ो-only, and it controls all updates
 * to it.  This means that all pagetable updates have to go via the
 * hypervisor, which is moderately expensive.
 *
 * Since we're pulling the pagetable करोwn, we चयन to use init_mm,
 * unpin old process pagetable and mark it all पढ़ो-ग_लिखो, which
 * allows further operations on it to be simple memory accesses.
 *
 * The only subtle poपूर्णांक is that another CPU may be still using the
 * pagetable because of lazy tlb flushing.  This means we need need to
 * चयन all CPUs off this pagetable beक्रमe we can unpin it.
 */
अटल व्योम xen_निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	get_cpu();		/* make sure we करोn't move around */
	xen_drop_mm_ref(mm);
	put_cpu();

	spin_lock(&mm->page_table_lock);

	/* pgd may not be pinned in the error निकास path of execve */
	अगर (xen_page_pinned(mm->pgd))
		xen_pgd_unpin(mm);

	spin_unlock(&mm->page_table_lock);
पूर्ण

अटल व्योम xen_post_allocator_init(व्योम);

अटल व्योम __init pin_pagetable_pfn(अचिन्हित cmd, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा mmuext_op op;

	op.cmd = cmd;
	op.arg1.mfn = pfn_to_mfn(pfn);
	अगर (HYPERVISOR_mmuext_op(&op, 1, शून्य, DOMID_SELF))
		BUG();
पूर्ण

अटल व्योम __init xen_cleanhighmap(अचिन्हित दीर्घ vaddr,
				    अचिन्हित दीर्घ vaddr_end)
अणु
	अचिन्हित दीर्घ kernel_end = roundup((अचिन्हित दीर्घ)_brk_end, PMD_SIZE) - 1;
	pmd_t *pmd = level2_kernel_pgt + pmd_index(vaddr);

	/* NOTE: The loop is more greedy than the cleanup_highmap variant.
	 * We include the PMD passed in on _both_ boundaries. */
	क्रम (; vaddr <= vaddr_end && (pmd < (level2_kernel_pgt + PTRS_PER_PMD));
			pmd++, vaddr += PMD_SIZE) अणु
		अगर (pmd_none(*pmd))
			जारी;
		अगर (vaddr < (अचिन्हित दीर्घ) _text || vaddr > kernel_end)
			set_pmd(pmd, __pmd(0));
	पूर्ण
	/* In हाल we did something silly, we should crash in this function
	 * instead of somewhere later and be confusing. */
	xen_mc_flush();
पूर्ण

/*
 * Make a page range ग_लिखोable and मुक्त it.
 */
अटल व्योम __init xen_मुक्त_ro_pages(अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ size)
अणु
	व्योम *vaddr = __va(paddr);
	व्योम *vaddr_end = vaddr + size;

	क्रम (; vaddr < vaddr_end; vaddr += PAGE_SIZE)
		make_lowmem_page_पढ़ोग_लिखो(vaddr);

	memblock_मुक्त(paddr, size);
पूर्ण

अटल व्योम __init xen_cleanmfnmap_मुक्त_pgtbl(व्योम *pgtbl, bool unpin)
अणु
	अचिन्हित दीर्घ pa = __pa(pgtbl) & PHYSICAL_PAGE_MASK;

	अगर (unpin)
		pin_pagetable_pfn(MMUEXT_UNPIN_TABLE, PFN_DOWN(pa));
	ClearPagePinned(virt_to_page(__va(pa)));
	xen_मुक्त_ro_pages(pa, PAGE_SIZE);
पूर्ण

अटल व्योम __init xen_cleanmfnmap_pmd(pmd_t *pmd, bool unpin)
अणु
	अचिन्हित दीर्घ pa;
	pte_t *pte_tbl;
	पूर्णांक i;

	अगर (pmd_large(*pmd)) अणु
		pa = pmd_val(*pmd) & PHYSICAL_PAGE_MASK;
		xen_मुक्त_ro_pages(pa, PMD_SIZE);
		वापस;
	पूर्ण

	pte_tbl = pte_offset_kernel(pmd, 0);
	क्रम (i = 0; i < PTRS_PER_PTE; i++) अणु
		अगर (pte_none(pte_tbl[i]))
			जारी;
		pa = pte_pfn(pte_tbl[i]) << PAGE_SHIFT;
		xen_मुक्त_ro_pages(pa, PAGE_SIZE);
	पूर्ण
	set_pmd(pmd, __pmd(0));
	xen_cleanmfnmap_मुक्त_pgtbl(pte_tbl, unpin);
पूर्ण

अटल व्योम __init xen_cleanmfnmap_pud(pud_t *pud, bool unpin)
अणु
	अचिन्हित दीर्घ pa;
	pmd_t *pmd_tbl;
	पूर्णांक i;

	अगर (pud_large(*pud)) अणु
		pa = pud_val(*pud) & PHYSICAL_PAGE_MASK;
		xen_मुक्त_ro_pages(pa, PUD_SIZE);
		वापस;
	पूर्ण

	pmd_tbl = pmd_offset(pud, 0);
	क्रम (i = 0; i < PTRS_PER_PMD; i++) अणु
		अगर (pmd_none(pmd_tbl[i]))
			जारी;
		xen_cleanmfnmap_pmd(pmd_tbl + i, unpin);
	पूर्ण
	set_pud(pud, __pud(0));
	xen_cleanmfnmap_मुक्त_pgtbl(pmd_tbl, unpin);
पूर्ण

अटल व्योम __init xen_cleanmfnmap_p4d(p4d_t *p4d, bool unpin)
अणु
	अचिन्हित दीर्घ pa;
	pud_t *pud_tbl;
	पूर्णांक i;

	अगर (p4d_large(*p4d)) अणु
		pa = p4d_val(*p4d) & PHYSICAL_PAGE_MASK;
		xen_मुक्त_ro_pages(pa, P4D_SIZE);
		वापस;
	पूर्ण

	pud_tbl = pud_offset(p4d, 0);
	क्रम (i = 0; i < PTRS_PER_PUD; i++) अणु
		अगर (pud_none(pud_tbl[i]))
			जारी;
		xen_cleanmfnmap_pud(pud_tbl + i, unpin);
	पूर्ण
	set_p4d(p4d, __p4d(0));
	xen_cleanmfnmap_मुक्त_pgtbl(pud_tbl, unpin);
पूर्ण

/*
 * Since it is well isolated we can (and since it is perhaps large we should)
 * also मुक्त the page tables mapping the initial P->M table.
 */
अटल व्योम __init xen_cleanmfnmap(अचिन्हित दीर्घ vaddr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	bool unpin;

	unpin = (vaddr == 2 * PGसूची_SIZE);
	vaddr &= PMD_MASK;
	pgd = pgd_offset_k(vaddr);
	p4d = p4d_offset(pgd, 0);
	अगर (!p4d_none(*p4d))
		xen_cleanmfnmap_p4d(p4d, unpin);
पूर्ण

अटल व्योम __init xen_pagetable_p2m_मुक्त(व्योम)
अणु
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ addr;

	size = PAGE_ALIGN(xen_start_info->nr_pages * माप(अचिन्हित दीर्घ));

	/* No memory or alपढ़ोy called. */
	अगर ((अचिन्हित दीर्घ)xen_p2m_addr == xen_start_info->mfn_list)
		वापस;

	/* using __ka address and sticking INVALID_P2M_ENTRY! */
	स_रखो((व्योम *)xen_start_info->mfn_list, 0xff, size);

	addr = xen_start_info->mfn_list;
	/*
	 * We could be in __ka space.
	 * We roundup to the PMD, which means that अगर anybody at this stage is
	 * using the __ka address of xen_start_info or
	 * xen_start_info->shared_info they are in going to crash. Fortunately
	 * we have alपढ़ोy revectored in xen_setup_kernel_pagetable.
	 */
	size = roundup(size, PMD_SIZE);

	अगर (addr >= __START_KERNEL_map) अणु
		xen_cleanhighmap(addr, addr + size);
		size = PAGE_ALIGN(xen_start_info->nr_pages *
				  माप(अचिन्हित दीर्घ));
		memblock_मुक्त(__pa(addr), size);
	पूर्ण अन्यथा अणु
		xen_cleanmfnmap(addr);
	पूर्ण
पूर्ण

अटल व्योम __init xen_pagetable_cleanhighmap(व्योम)
अणु
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ addr;

	/* At this stage, cleanup_highmap has alपढ़ोy cleaned __ka space
	 * from _brk_limit way up to the max_pfn_mapped (which is the end of
	 * the ramdisk). We जारी on, erasing PMD entries that poपूर्णांक to page
	 * tables - करो note that they are accessible at this stage via __va.
	 * As Xen is aligning the memory end to a 4MB boundary, क्रम good
	 * measure we also round up to PMD_SIZE * 2 - which means that अगर
	 * anybody is using __ka address to the initial boot-stack - and try
	 * to use it - they are going to crash. The xen_start_info has been
	 * taken care of alपढ़ोy in xen_setup_kernel_pagetable. */
	addr = xen_start_info->pt_base;
	size = xen_start_info->nr_pt_frames * PAGE_SIZE;

	xen_cleanhighmap(addr, roundup(addr + size, PMD_SIZE * 2));
	xen_start_info->pt_base = (अचिन्हित दीर्घ)__va(__pa(xen_start_info->pt_base));
पूर्ण

अटल व्योम __init xen_pagetable_p2m_setup(व्योम)
अणु
	xen_vदो_स्मृति_p2m_tree();

	xen_pagetable_p2m_मुक्त();

	xen_pagetable_cleanhighmap();

	/* And revector! Bye bye old array */
	xen_start_info->mfn_list = (अचिन्हित दीर्घ)xen_p2m_addr;
पूर्ण

अटल व्योम __init xen_pagetable_init(व्योम)
अणु
	paging_init();
	xen_post_allocator_init();

	xen_pagetable_p2m_setup();

	/* Allocate and initialize top and mid mfn levels क्रम p2m काष्ठाure */
	xen_build_mfn_list_list();

	/* Remap memory मुक्तd due to conflicts with E820 map */
	xen_remap_memory();
	xen_setup_mfn_list_list();
पूर्ण
अटल व्योम xen_ग_लिखो_cr2(अचिन्हित दीर्घ cr2)
अणु
	this_cpu_पढ़ो(xen_vcpu)->arch.cr2 = cr2;
पूर्ण

अटल noअंतरभूत व्योम xen_flush_tlb(व्योम)
अणु
	काष्ठा mmuext_op *op;
	काष्ठा multicall_space mcs;

	preempt_disable();

	mcs = xen_mc_entry(माप(*op));

	op = mcs.args;
	op->cmd = MMUEXT_TLB_FLUSH_LOCAL;
	MULTI_mmuext_op(mcs.mc, op, 1, शून्य, DOMID_SELF);

	xen_mc_issue(PARAVIRT_LAZY_MMU);

	preempt_enable();
पूर्ण

अटल व्योम xen_flush_tlb_one_user(अचिन्हित दीर्घ addr)
अणु
	काष्ठा mmuext_op *op;
	काष्ठा multicall_space mcs;

	trace_xen_mmu_flush_tlb_one_user(addr);

	preempt_disable();

	mcs = xen_mc_entry(माप(*op));
	op = mcs.args;
	op->cmd = MMUEXT_INVLPG_LOCAL;
	op->arg1.linear_addr = addr & PAGE_MASK;
	MULTI_mmuext_op(mcs.mc, op, 1, शून्य, DOMID_SELF);

	xen_mc_issue(PARAVIRT_LAZY_MMU);

	preempt_enable();
पूर्ण

अटल व्योम xen_flush_tlb_multi(स्थिर काष्ठा cpumask *cpus,
				स्थिर काष्ठा flush_tlb_info *info)
अणु
	काष्ठा अणु
		काष्ठा mmuext_op op;
		DECLARE_BITMAP(mask, NR_CPUS);
	पूर्ण *args;
	काष्ठा multicall_space mcs;
	स्थिर माप_प्रकार mc_entry_size = माप(args->op) +
		माप(args->mask[0]) * BITS_TO_LONGS(num_possible_cpus());

	trace_xen_mmu_flush_tlb_multi(cpus, info->mm, info->start, info->end);

	अगर (cpumask_empty(cpus))
		वापस;		/* nothing to करो */

	mcs = xen_mc_entry(mc_entry_size);
	args = mcs.args;
	args->op.arg2.vcpumask = to_cpumask(args->mask);

	/* Remove any offline CPUs */
	cpumask_and(to_cpumask(args->mask), cpus, cpu_online_mask);

	args->op.cmd = MMUEXT_TLB_FLUSH_MULTI;
	अगर (info->end != TLB_FLUSH_ALL &&
	    (info->end - info->start) <= PAGE_SIZE) अणु
		args->op.cmd = MMUEXT_INVLPG_MULTI;
		args->op.arg1.linear_addr = info->start;
	पूर्ण

	MULTI_mmuext_op(mcs.mc, &args->op, 1, शून्य, DOMID_SELF);

	xen_mc_issue(PARAVIRT_LAZY_MMU);
पूर्ण

अटल अचिन्हित दीर्घ xen_पढ़ो_cr3(व्योम)
अणु
	वापस this_cpu_पढ़ो(xen_cr3);
पूर्ण

अटल व्योम set_current_cr3(व्योम *v)
अणु
	this_cpu_ग_लिखो(xen_current_cr3, (अचिन्हित दीर्घ)v);
पूर्ण

अटल व्योम __xen_ग_लिखो_cr3(bool kernel, अचिन्हित दीर्घ cr3)
अणु
	काष्ठा mmuext_op op;
	अचिन्हित दीर्घ mfn;

	trace_xen_mmu_ग_लिखो_cr3(kernel, cr3);

	अगर (cr3)
		mfn = pfn_to_mfn(PFN_DOWN(cr3));
	अन्यथा
		mfn = 0;

	WARN_ON(mfn == 0 && kernel);

	op.cmd = kernel ? MMUEXT_NEW_BASEPTR : MMUEXT_NEW_USER_BASEPTR;
	op.arg1.mfn = mfn;

	xen_extend_mmuext_op(&op);

	अगर (kernel) अणु
		this_cpu_ग_लिखो(xen_cr3, cr3);

		/* Update xen_current_cr3 once the batch has actually
		   been submitted. */
		xen_mc_callback(set_current_cr3, (व्योम *)cr3);
	पूर्ण
पूर्ण
अटल व्योम xen_ग_लिखो_cr3(अचिन्हित दीर्घ cr3)
अणु
	pgd_t *user_pgd = xen_get_user_pgd(__va(cr3));

	BUG_ON(preemptible());

	xen_mc_batch();  /* disables पूर्णांकerrupts */

	/* Update जबतक पूर्णांकerrupts are disabled, so its atomic with
	   respect to ipis */
	this_cpu_ग_लिखो(xen_cr3, cr3);

	__xen_ग_लिखो_cr3(true, cr3);

	अगर (user_pgd)
		__xen_ग_लिखो_cr3(false, __pa(user_pgd));
	अन्यथा
		__xen_ग_लिखो_cr3(false, 0);

	xen_mc_issue(PARAVIRT_LAZY_CPU);  /* पूर्णांकerrupts restored */
पूर्ण

/*
 * At the start of the day - when Xen launches a guest, it has alपढ़ोy
 * built pagetables क्रम the guest. We diligently look over them
 * in xen_setup_kernel_pagetable and graft as appropriate them in the
 * init_top_pgt and its मित्रs. Then when we are happy we load
 * the new init_top_pgt - and जारी on.
 *
 * The generic code starts (start_kernel) and 'init_mem_mapping' sets
 * up the rest of the pagetables. When it has completed it loads the cr3.
 * N.B. that baremetal would start at 'start_kernel' (and the early
 * #PF handler would create bootstrap pagetables) - so we are running
 * with the same assumptions as what to करो when ग_लिखो_cr3 is executed
 * at this poपूर्णांक.
 *
 * Since there are no user-page tables at all, we have two variants
 * of xen_ग_लिखो_cr3 - the early bootup (this one), and the late one
 * (xen_ग_लिखो_cr3). The reason we have to करो that is that in 64-bit
 * the Linux kernel and user-space are both in ring 3 जबतक the
 * hypervisor is in ring 0.
 */
अटल व्योम __init xen_ग_लिखो_cr3_init(अचिन्हित दीर्घ cr3)
अणु
	BUG_ON(preemptible());

	xen_mc_batch();  /* disables पूर्णांकerrupts */

	/* Update जबतक पूर्णांकerrupts are disabled, so its atomic with
	   respect to ipis */
	this_cpu_ग_लिखो(xen_cr3, cr3);

	__xen_ग_लिखो_cr3(true, cr3);

	xen_mc_issue(PARAVIRT_LAZY_CPU);  /* पूर्णांकerrupts restored */
पूर्ण

अटल पूर्णांक xen_pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *pgd = mm->pgd;
	काष्ठा page *page = virt_to_page(pgd);
	pgd_t *user_pgd;
	पूर्णांक ret = -ENOMEM;

	BUG_ON(PagePinned(virt_to_page(pgd)));
	BUG_ON(page->निजी != 0);

	user_pgd = (pgd_t *)__get_मुक्त_page(GFP_KERNEL | __GFP_ZERO);
	page->निजी = (अचिन्हित दीर्घ)user_pgd;

	अगर (user_pgd != शून्य) अणु
#अगर_घोषित CONFIG_X86_VSYSCALL_EMULATION
		user_pgd[pgd_index(VSYSCALL_ADDR)] =
			__pgd(__pa(level3_user_vsyscall) | _PAGE_TABLE);
#पूर्ण_अगर
		ret = 0;
	पूर्ण

	BUG_ON(PagePinned(virt_to_page(xen_get_user_pgd(pgd))));

	वापस ret;
पूर्ण

अटल व्योम xen_pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	pgd_t *user_pgd = xen_get_user_pgd(pgd);

	अगर (user_pgd)
		मुक्त_page((अचिन्हित दीर्घ)user_pgd);
पूर्ण

/*
 * Init-समय set_pte जबतक स्थिरructing initial pagetables, which
 * करोesn't allow RO page table pages to be remapped RW.
 *
 * If there is no MFN क्रम this PFN then this page is initially
 * ballooned out so clear the PTE (as in decrease_reservation() in
 * drivers/xen/balloon.c).
 *
 * Many of these PTE updates are करोne on unpinned and writable pages
 * and करोing a hypercall क्रम these is unnecessary and expensive.  At
 * this poपूर्णांक it is not possible to tell अगर a page is pinned or not,
 * so always ग_लिखो the PTE directly and rely on Xen trapping and
 * emulating any updates as necessary.
 */
__visible pte_t xen_make_pte_init(pteval_t pte)
अणु
	अचिन्हित दीर्घ pfn;

	/*
	 * Pages beदीर्घing to the initial p2m list mapped outside the शेष
	 * address range must be mapped पढ़ो-only. This region contains the
	 * page tables क्रम mapping the p2m list, too, and page tables MUST be
	 * mapped पढ़ो-only.
	 */
	pfn = (pte & PTE_PFN_MASK) >> PAGE_SHIFT;
	अगर (xen_start_info->mfn_list < __START_KERNEL_map &&
	    pfn >= xen_start_info->first_p2m_pfn &&
	    pfn < xen_start_info->first_p2m_pfn + xen_start_info->nr_p2m_frames)
		pte &= ~_PAGE_RW;

	pte = pte_pfn_to_mfn(pte);
	वापस native_make_pte(pte);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_make_pte_init);

अटल व्योम __init xen_set_pte_init(pte_t *ptep, pte_t pte)
अणु
	__xen_set_pte(ptep, pte);
पूर्ण

/* Early in boot, जबतक setting up the initial pagetable, assume
   everything is pinned. */
अटल व्योम __init xen_alloc_pte_init(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)
अणु
#अगर_घोषित CONFIG_FLATMEM
	BUG_ON(mem_map);	/* should only be used early */
#पूर्ण_अगर
	make_lowmem_page_पढ़ोonly(__va(PFN_PHYS(pfn)));
	pin_pagetable_pfn(MMUEXT_PIN_L1_TABLE, pfn);
पूर्ण

/* Used क्रम pmd and pud */
अटल व्योम __init xen_alloc_pmd_init(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)
अणु
#अगर_घोषित CONFIG_FLATMEM
	BUG_ON(mem_map);	/* should only be used early */
#पूर्ण_अगर
	make_lowmem_page_पढ़ोonly(__va(PFN_PHYS(pfn)));
पूर्ण

/* Early release_pte assumes that all pts are pinned, since there's
   only init_mm and anything attached to that is pinned. */
अटल व्योम __init xen_release_pte_init(अचिन्हित दीर्घ pfn)
अणु
	pin_pagetable_pfn(MMUEXT_UNPIN_TABLE, pfn);
	make_lowmem_page_पढ़ोग_लिखो(__va(PFN_PHYS(pfn)));
पूर्ण

अटल व्योम __init xen_release_pmd_init(अचिन्हित दीर्घ pfn)
अणु
	make_lowmem_page_पढ़ोग_लिखो(__va(PFN_PHYS(pfn)));
पूर्ण

अटल अंतरभूत व्योम __pin_pagetable_pfn(अचिन्हित cmd, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा multicall_space mcs;
	काष्ठा mmuext_op *op;

	mcs = __xen_mc_entry(माप(*op));
	op = mcs.args;
	op->cmd = cmd;
	op->arg1.mfn = pfn_to_mfn(pfn);

	MULTI_mmuext_op(mcs.mc, mcs.args, 1, शून्य, DOMID_SELF);
पूर्ण

अटल अंतरभूत व्योम __set_pfn_prot(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	काष्ठा multicall_space mcs;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)__va(pfn << PAGE_SHIFT);

	mcs = __xen_mc_entry(0);
	MULTI_update_va_mapping(mcs.mc, (अचिन्हित दीर्घ)addr,
				pfn_pte(pfn, prot), 0);
पूर्ण

/* This needs to make sure the new pte page is pinned अगरf its being
   attached to a pinned pagetable. */
अटल अंतरभूत व्योम xen_alloc_ptpage(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn,
				    अचिन्हित level)
अणु
	bool pinned = xen_page_pinned(mm->pgd);

	trace_xen_mmu_alloc_ptpage(mm, pfn, level, pinned);

	अगर (pinned) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		अगर (अटल_branch_likely(&xen_काष्ठा_pages_पढ़ोy))
			SetPagePinned(page);

		xen_mc_batch();

		__set_pfn_prot(pfn, PAGE_KERNEL_RO);

		अगर (level == PT_PTE && USE_SPLIT_PTE_PTLOCKS)
			__pin_pagetable_pfn(MMUEXT_PIN_L1_TABLE, pfn);

		xen_mc_issue(PARAVIRT_LAZY_MMU);
	पूर्ण
पूर्ण

अटल व्योम xen_alloc_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)
अणु
	xen_alloc_ptpage(mm, pfn, PT_PTE);
पूर्ण

अटल व्योम xen_alloc_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)
अणु
	xen_alloc_ptpage(mm, pfn, PT_PMD);
पूर्ण

/* This should never happen until we're OK to use काष्ठा page */
अटल अंतरभूत व्योम xen_release_ptpage(अचिन्हित दीर्घ pfn, अचिन्हित level)
अणु
	काष्ठा page *page = pfn_to_page(pfn);
	bool pinned = PagePinned(page);

	trace_xen_mmu_release_ptpage(pfn, level, pinned);

	अगर (pinned) अणु
		xen_mc_batch();

		अगर (level == PT_PTE && USE_SPLIT_PTE_PTLOCKS)
			__pin_pagetable_pfn(MMUEXT_UNPIN_TABLE, pfn);

		__set_pfn_prot(pfn, PAGE_KERNEL);

		xen_mc_issue(PARAVIRT_LAZY_MMU);

		ClearPagePinned(page);
	पूर्ण
पूर्ण

अटल व्योम xen_release_pte(अचिन्हित दीर्घ pfn)
अणु
	xen_release_ptpage(pfn, PT_PTE);
पूर्ण

अटल व्योम xen_release_pmd(अचिन्हित दीर्घ pfn)
अणु
	xen_release_ptpage(pfn, PT_PMD);
पूर्ण

अटल व्योम xen_alloc_pud(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)
अणु
	xen_alloc_ptpage(mm, pfn, PT_PUD);
पूर्ण

अटल व्योम xen_release_pud(अचिन्हित दीर्घ pfn)
अणु
	xen_release_ptpage(pfn, PT_PUD);
पूर्ण

/*
 * Like __va(), but वापसs address in the kernel mapping (which is
 * all we have until the physical memory mapping has been set up.
 */
अटल व्योम * __init __ka(phys_addr_t paddr)
अणु
	वापस (व्योम *)(paddr + __START_KERNEL_map);
पूर्ण

/* Convert a machine address to physical address */
अटल अचिन्हित दीर्घ __init m2p(phys_addr_t maddr)
अणु
	phys_addr_t paddr;

	maddr &= XEN_PTE_MFN_MASK;
	paddr = mfn_to_pfn(maddr >> PAGE_SHIFT) << PAGE_SHIFT;

	वापस paddr;
पूर्ण

/* Convert a machine address to kernel भव */
अटल व्योम * __init m2v(phys_addr_t maddr)
अणु
	वापस __ka(m2p(maddr));
पूर्ण

/* Set the page permissions on an identity-mapped pages */
अटल व्योम __init set_page_prot_flags(व्योम *addr, pgprot_t prot,
				       अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ pfn = __pa(addr) >> PAGE_SHIFT;
	pte_t pte = pfn_pte(pfn, prot);

	अगर (HYPERVISOR_update_va_mapping((अचिन्हित दीर्घ)addr, pte, flags))
		BUG();
पूर्ण
अटल व्योम __init set_page_prot(व्योम *addr, pgprot_t prot)
अणु
	वापस set_page_prot_flags(addr, prot, UVMF_NONE);
पूर्ण

व्योम __init xen_setup_machphys_mapping(व्योम)
अणु
	काष्ठा xen_machphys_mapping mapping;

	अगर (HYPERVISOR_memory_op(XENMEM_machphys_mapping, &mapping) == 0) अणु
		machine_to_phys_mapping = (अचिन्हित दीर्घ *)mapping.v_start;
		machine_to_phys_nr = mapping.max_mfn + 1;
	पूर्ण अन्यथा अणु
		machine_to_phys_nr = MACH2PHYS_NR_ENTRIES;
	पूर्ण
पूर्ण

अटल व्योम __init convert_pfn_mfn(व्योम *v)
अणु
	pte_t *pte = v;
	पूर्णांक i;

	/* All levels are converted the same way, so just treat them
	   as ptes. */
	क्रम (i = 0; i < PTRS_PER_PTE; i++)
		pte[i] = xen_make_pte(pte[i].pte);
पूर्ण
अटल व्योम __init check_pt_base(अचिन्हित दीर्घ *pt_base, अचिन्हित दीर्घ *pt_end,
				 अचिन्हित दीर्घ addr)
अणु
	अगर (*pt_base == PFN_DOWN(__pa(addr))) अणु
		set_page_prot_flags((व्योम *)addr, PAGE_KERNEL, UVMF_INVLPG);
		clear_page((व्योम *)addr);
		(*pt_base)++;
	पूर्ण
	अगर (*pt_end == PFN_DOWN(__pa(addr))) अणु
		set_page_prot_flags((व्योम *)addr, PAGE_KERNEL, UVMF_INVLPG);
		clear_page((व्योम *)addr);
		(*pt_end)--;
	पूर्ण
पूर्ण
/*
 * Set up the initial kernel pagetable.
 *
 * We can स्थिरruct this by grafting the Xen provided pagetable पूर्णांकo
 * head_64.S's preconstructed pagetables.  We copy the Xen L2's पूर्णांकo
 * level2_ident_pgt, and level2_kernel_pgt.  This means that only the
 * kernel has a physical mapping to start with - but that's enough to
 * get __va working.  We need to fill in the rest of the physical
 * mapping once some sort of allocator has been set up.
 */
व्योम __init xen_setup_kernel_pagetable(pgd_t *pgd, अचिन्हित दीर्घ max_pfn)
अणु
	pud_t *l3;
	pmd_t *l2;
	अचिन्हित दीर्घ addr[3];
	अचिन्हित दीर्घ pt_base, pt_end;
	अचिन्हित i;

	/* max_pfn_mapped is the last pfn mapped in the initial memory
	 * mappings. Considering that on Xen after the kernel mappings we
	 * have the mappings of some pages that करोn't exist in pfn space, we
	 * set max_pfn_mapped to the last real pfn mapped. */
	अगर (xen_start_info->mfn_list < __START_KERNEL_map)
		max_pfn_mapped = xen_start_info->first_p2m_pfn;
	अन्यथा
		max_pfn_mapped = PFN_DOWN(__pa(xen_start_info->mfn_list));

	pt_base = PFN_DOWN(__pa(xen_start_info->pt_base));
	pt_end = pt_base + xen_start_info->nr_pt_frames;

	/* Zap identity mapping */
	init_top_pgt[0] = __pgd(0);

	/* Pre-स्थिरructed entries are in pfn, so convert to mfn */
	/* L4[273] -> level3_ident_pgt  */
	/* L4[511] -> level3_kernel_pgt */
	convert_pfn_mfn(init_top_pgt);

	/* L3_i[0] -> level2_ident_pgt */
	convert_pfn_mfn(level3_ident_pgt);
	/* L3_k[510] -> level2_kernel_pgt */
	/* L3_k[511] -> level2_fixmap_pgt */
	convert_pfn_mfn(level3_kernel_pgt);

	/* L3_k[511][508-FIXMAP_PMD_NUM ... 507] -> level1_fixmap_pgt */
	convert_pfn_mfn(level2_fixmap_pgt);

	/* We get [511][511] and have Xen's version of level2_kernel_pgt */
	l3 = m2v(pgd[pgd_index(__START_KERNEL_map)].pgd);
	l2 = m2v(l3[pud_index(__START_KERNEL_map)].pud);

	addr[0] = (अचिन्हित दीर्घ)pgd;
	addr[1] = (अचिन्हित दीर्घ)l3;
	addr[2] = (अचिन्हित दीर्घ)l2;
	/* Graft it onto L4[273][0]. Note that we creating an aliasing problem:
	 * Both L4[273][0] and L4[511][510] have entries that poपूर्णांक to the same
	 * L2 (PMD) tables. Meaning that अगर you modअगरy it in __va space
	 * it will be also modअगरied in the __ka space! (But अगर you just
	 * modअगरy the PMD table to poपूर्णांक to other PTE's or none, then you
	 * are OK - which is what cleanup_highmap करोes) */
	copy_page(level2_ident_pgt, l2);
	/* Graft it onto L4[511][510] */
	copy_page(level2_kernel_pgt, l2);

	/*
	 * Zap execute permission from the ident map. Due to the sharing of
	 * L1 entries we need to करो this in the L2.
	 */
	अगर (__supported_pte_mask & _PAGE_NX) अणु
		क्रम (i = 0; i < PTRS_PER_PMD; ++i) अणु
			अगर (pmd_none(level2_ident_pgt[i]))
				जारी;
			level2_ident_pgt[i] = pmd_set_flags(level2_ident_pgt[i], _PAGE_NX);
		पूर्ण
	पूर्ण

	/* Copy the initial P->M table mappings अगर necessary. */
	i = pgd_index(xen_start_info->mfn_list);
	अगर (i && i < pgd_index(__START_KERNEL_map))
		init_top_pgt[i] = ((pgd_t *)xen_start_info->pt_base)[i];

	/* Make pagetable pieces RO */
	set_page_prot(init_top_pgt, PAGE_KERNEL_RO);
	set_page_prot(level3_ident_pgt, PAGE_KERNEL_RO);
	set_page_prot(level3_kernel_pgt, PAGE_KERNEL_RO);
	set_page_prot(level3_user_vsyscall, PAGE_KERNEL_RO);
	set_page_prot(level2_ident_pgt, PAGE_KERNEL_RO);
	set_page_prot(level2_kernel_pgt, PAGE_KERNEL_RO);
	set_page_prot(level2_fixmap_pgt, PAGE_KERNEL_RO);

	क्रम (i = 0; i < FIXMAP_PMD_NUM; i++) अणु
		set_page_prot(level1_fixmap_pgt + i * PTRS_PER_PTE,
			      PAGE_KERNEL_RO);
	पूर्ण

	/* Pin करोwn new L4 */
	pin_pagetable_pfn(MMUEXT_PIN_L4_TABLE,
			  PFN_DOWN(__pa_symbol(init_top_pgt)));

	/* Unpin Xen-provided one */
	pin_pagetable_pfn(MMUEXT_UNPIN_TABLE, PFN_DOWN(__pa(pgd)));

	/*
	 * At this stage there can be no user pgd, and no page काष्ठाure to
	 * attach it to, so make sure we just set kernel pgd.
	 */
	xen_mc_batch();
	__xen_ग_लिखो_cr3(true, __pa(init_top_pgt));
	xen_mc_issue(PARAVIRT_LAZY_CPU);

	/* We can't that easily rip out L3 and L2, as the Xen pagetables are
	 * set out this way: [L4], [L1], [L2], [L3], [L1], [L1] ...  क्रम
	 * the initial करोमुख्य. For guests using the toolstack, they are in:
	 * [L4], [L3], [L2], [L1], [L1], order .. So क्रम करोm0 we can only
	 * rip out the [L4] (pgd), but क्रम guests we shave off three pages.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(addr); i++)
		check_pt_base(&pt_base, &pt_end, addr[i]);

	/* Our (by three pages) smaller Xen pagetable that we are using */
	xen_pt_base = PFN_PHYS(pt_base);
	xen_pt_size = (pt_end - pt_base) * PAGE_SIZE;
	memblock_reserve(xen_pt_base, xen_pt_size);

	/* Revector the xen_start_info */
	xen_start_info = (काष्ठा start_info *)__va(__pa(xen_start_info));
पूर्ण

/*
 * Read a value from a physical address.
 */
अटल अचिन्हित दीर्घ __init xen_पढ़ो_phys_uदीर्घ(phys_addr_t addr)
अणु
	अचिन्हित दीर्घ *vaddr;
	अचिन्हित दीर्घ val;

	vaddr = early_memremap_ro(addr, माप(val));
	val = *vaddr;
	early_memunmap(vaddr, माप(val));
	वापस val;
पूर्ण

/*
 * Translate a भव address to a physical one without relying on mapped
 * page tables. Don't rely on big pages being aligned in (guest) physical
 * space!
 */
अटल phys_addr_t __init xen_early_virt_to_phys(अचिन्हित दीर्घ vaddr)
अणु
	phys_addr_t pa;
	pgd_t pgd;
	pud_t pud;
	pmd_t pmd;
	pte_t pte;

	pa = पढ़ो_cr3_pa();
	pgd = native_make_pgd(xen_पढ़ो_phys_uदीर्घ(pa + pgd_index(vaddr) *
						       माप(pgd)));
	अगर (!pgd_present(pgd))
		वापस 0;

	pa = pgd_val(pgd) & PTE_PFN_MASK;
	pud = native_make_pud(xen_पढ़ो_phys_uदीर्घ(pa + pud_index(vaddr) *
						       माप(pud)));
	अगर (!pud_present(pud))
		वापस 0;
	pa = pud_val(pud) & PTE_PFN_MASK;
	अगर (pud_large(pud))
		वापस pa + (vaddr & ~PUD_MASK);

	pmd = native_make_pmd(xen_पढ़ो_phys_uदीर्घ(pa + pmd_index(vaddr) *
						       माप(pmd)));
	अगर (!pmd_present(pmd))
		वापस 0;
	pa = pmd_val(pmd) & PTE_PFN_MASK;
	अगर (pmd_large(pmd))
		वापस pa + (vaddr & ~PMD_MASK);

	pte = native_make_pte(xen_पढ़ो_phys_uदीर्घ(pa + pte_index(vaddr) *
						       माप(pte)));
	अगर (!pte_present(pte))
		वापस 0;
	pa = pte_pfn(pte) << PAGE_SHIFT;

	वापस pa | (vaddr & ~PAGE_MASK);
पूर्ण

/*
 * Find a new area क्रम the hypervisor supplied p2m list and relocate the p2m to
 * this area.
 */
व्योम __init xen_relocate_p2m(व्योम)
अणु
	phys_addr_t size, new_area, pt_phys, pmd_phys, pud_phys;
	अचिन्हित दीर्घ p2m_pfn, p2m_pfn_end, n_frames, pfn, pfn_end;
	पूर्णांक n_pte, n_pt, n_pmd, n_pud, idx_pte, idx_pt, idx_pmd, idx_pud;
	pte_t *pt;
	pmd_t *pmd;
	pud_t *pud;
	pgd_t *pgd;
	अचिन्हित दीर्घ *new_p2m;

	size = PAGE_ALIGN(xen_start_info->nr_pages * माप(अचिन्हित दीर्घ));
	n_pte = roundup(size, PAGE_SIZE) >> PAGE_SHIFT;
	n_pt = roundup(size, PMD_SIZE) >> PMD_SHIFT;
	n_pmd = roundup(size, PUD_SIZE) >> PUD_SHIFT;
	n_pud = roundup(size, P4D_SIZE) >> P4D_SHIFT;
	n_frames = n_pte + n_pt + n_pmd + n_pud;

	new_area = xen_find_मुक्त_area(PFN_PHYS(n_frames));
	अगर (!new_area) अणु
		xen_raw_console_ग_लिखो("Can't find new memory area for p2m needed due to E820 map conflict\n");
		BUG();
	पूर्ण

	/*
	 * Setup the page tables क्रम addressing the new p2m list.
	 * We have asked the hypervisor to map the p2m list at the user address
	 * PUD_SIZE. It may have करोne so, or it may have used a kernel space
	 * address depending on the Xen version.
	 * To aव्योम any possible भव address collision, just use
	 * 2 * PUD_SIZE क्रम the new area.
	 */
	pud_phys = new_area;
	pmd_phys = pud_phys + PFN_PHYS(n_pud);
	pt_phys = pmd_phys + PFN_PHYS(n_pmd);
	p2m_pfn = PFN_DOWN(pt_phys) + n_pt;

	pgd = __va(पढ़ो_cr3_pa());
	new_p2m = (अचिन्हित दीर्घ *)(2 * PGसूची_SIZE);
	क्रम (idx_pud = 0; idx_pud < n_pud; idx_pud++) अणु
		pud = early_memremap(pud_phys, PAGE_SIZE);
		clear_page(pud);
		क्रम (idx_pmd = 0; idx_pmd < min(n_pmd, PTRS_PER_PUD);
				idx_pmd++) अणु
			pmd = early_memremap(pmd_phys, PAGE_SIZE);
			clear_page(pmd);
			क्रम (idx_pt = 0; idx_pt < min(n_pt, PTRS_PER_PMD);
					idx_pt++) अणु
				pt = early_memremap(pt_phys, PAGE_SIZE);
				clear_page(pt);
				क्रम (idx_pte = 0;
				     idx_pte < min(n_pte, PTRS_PER_PTE);
				     idx_pte++) अणु
					pt[idx_pte] = pfn_pte(p2m_pfn,
							      PAGE_KERNEL);
					p2m_pfn++;
				पूर्ण
				n_pte -= PTRS_PER_PTE;
				early_memunmap(pt, PAGE_SIZE);
				make_lowmem_page_पढ़ोonly(__va(pt_phys));
				pin_pagetable_pfn(MMUEXT_PIN_L1_TABLE,
						PFN_DOWN(pt_phys));
				pmd[idx_pt] = __pmd(_PAGE_TABLE | pt_phys);
				pt_phys += PAGE_SIZE;
			पूर्ण
			n_pt -= PTRS_PER_PMD;
			early_memunmap(pmd, PAGE_SIZE);
			make_lowmem_page_पढ़ोonly(__va(pmd_phys));
			pin_pagetable_pfn(MMUEXT_PIN_L2_TABLE,
					PFN_DOWN(pmd_phys));
			pud[idx_pmd] = __pud(_PAGE_TABLE | pmd_phys);
			pmd_phys += PAGE_SIZE;
		पूर्ण
		n_pmd -= PTRS_PER_PUD;
		early_memunmap(pud, PAGE_SIZE);
		make_lowmem_page_पढ़ोonly(__va(pud_phys));
		pin_pagetable_pfn(MMUEXT_PIN_L3_TABLE, PFN_DOWN(pud_phys));
		set_pgd(pgd + 2 + idx_pud, __pgd(_PAGE_TABLE | pud_phys));
		pud_phys += PAGE_SIZE;
	पूर्ण

	/* Now copy the old p2m info to the new area. */
	स_नकल(new_p2m, xen_p2m_addr, size);
	xen_p2m_addr = new_p2m;

	/* Release the old p2m list and set new list info. */
	p2m_pfn = PFN_DOWN(xen_early_virt_to_phys(xen_start_info->mfn_list));
	BUG_ON(!p2m_pfn);
	p2m_pfn_end = p2m_pfn + PFN_DOWN(size);

	अगर (xen_start_info->mfn_list < __START_KERNEL_map) अणु
		pfn = xen_start_info->first_p2m_pfn;
		pfn_end = xen_start_info->first_p2m_pfn +
			  xen_start_info->nr_p2m_frames;
		set_pgd(pgd + 1, __pgd(0));
	पूर्ण अन्यथा अणु
		pfn = p2m_pfn;
		pfn_end = p2m_pfn_end;
	पूर्ण

	memblock_मुक्त(PFN_PHYS(pfn), PAGE_SIZE * (pfn_end - pfn));
	जबतक (pfn < pfn_end) अणु
		अगर (pfn == p2m_pfn) अणु
			pfn = p2m_pfn_end;
			जारी;
		पूर्ण
		make_lowmem_page_पढ़ोग_लिखो(__va(PFN_PHYS(pfn)));
		pfn++;
	पूर्ण

	xen_start_info->mfn_list = (अचिन्हित दीर्घ)xen_p2m_addr;
	xen_start_info->first_p2m_pfn =  PFN_DOWN(new_area);
	xen_start_info->nr_p2m_frames = n_frames;
पूर्ण

व्योम __init xen_reserve_special_pages(व्योम)
अणु
	phys_addr_t paddr;

	memblock_reserve(__pa(xen_start_info), PAGE_SIZE);
	अगर (xen_start_info->store_mfn) अणु
		paddr = PFN_PHYS(mfn_to_pfn(xen_start_info->store_mfn));
		memblock_reserve(paddr, PAGE_SIZE);
	पूर्ण
	अगर (!xen_initial_करोमुख्य()) अणु
		paddr = PFN_PHYS(mfn_to_pfn(xen_start_info->console.करोmU.mfn));
		memblock_reserve(paddr, PAGE_SIZE);
	पूर्ण
पूर्ण

व्योम __init xen_pt_check_e820(व्योम)
अणु
	अगर (xen_is_e820_reserved(xen_pt_base, xen_pt_size)) अणु
		xen_raw_console_ग_लिखो("Xen hypervisor allocated page table memory conflicts with E820 map\n");
		BUG();
	पूर्ण
पूर्ण

अटल अचिन्हित अक्षर dummy_mapping[PAGE_SIZE] __page_aligned_bss;

अटल व्योम xen_set_fixmap(अचिन्हित idx, phys_addr_t phys, pgprot_t prot)
अणु
	pte_t pte;

	phys >>= PAGE_SHIFT;

	चयन (idx) अणु
	हाल FIX_BTMAP_END ... FIX_BTMAP_BEGIN:
#अगर_घोषित CONFIG_X86_VSYSCALL_EMULATION
	हाल VSYSCALL_PAGE:
#पूर्ण_अगर
		/* All local page mappings */
		pte = pfn_pte(phys, prot);
		अवरोध;

#अगर_घोषित CONFIG_X86_LOCAL_APIC
	हाल FIX_APIC_BASE:	/* maps dummy local APIC */
		pte = pfn_pte(PFN_DOWN(__pa(dummy_mapping)), PAGE_KERNEL);
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_IO_APIC
	हाल FIX_IO_APIC_BASE_0 ... FIX_IO_APIC_BASE_END:
		/*
		 * We just करोn't map the IO APIC - all access is via
		 * hypercalls.  Keep the address in the pte क्रम reference.
		 */
		pte = pfn_pte(PFN_DOWN(__pa(dummy_mapping)), PAGE_KERNEL);
		अवरोध;
#पूर्ण_अगर

	हाल FIX_PARAVIRT_BOOTMAP:
		/* This is an MFN, but it isn't an IO mapping from the
		   IO करोमुख्य */
		pte = mfn_pte(phys, prot);
		अवरोध;

	शेष:
		/* By शेष, set_fixmap is used क्रम hardware mappings */
		pte = mfn_pte(phys, prot);
		अवरोध;
	पूर्ण

	__native_set_fixmap(idx, pte);

#अगर_घोषित CONFIG_X86_VSYSCALL_EMULATION
	/* Replicate changes to map the vsyscall page पूर्णांकo the user
	   pagetable vsyscall mapping. */
	अगर (idx == VSYSCALL_PAGE) अणु
		अचिन्हित दीर्घ vaddr = __fix_to_virt(idx);
		set_pte_vaddr_pud(level3_user_vsyscall, vaddr, pte);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init xen_post_allocator_init(व्योम)
अणु
	pv_ops.mmu.set_pte = xen_set_pte;
	pv_ops.mmu.set_pmd = xen_set_pmd;
	pv_ops.mmu.set_pud = xen_set_pud;
	pv_ops.mmu.set_p4d = xen_set_p4d;

	/* This will work as दीर्घ as patching hasn't happened yet
	   (which it hasn't) */
	pv_ops.mmu.alloc_pte = xen_alloc_pte;
	pv_ops.mmu.alloc_pmd = xen_alloc_pmd;
	pv_ops.mmu.release_pte = xen_release_pte;
	pv_ops.mmu.release_pmd = xen_release_pmd;
	pv_ops.mmu.alloc_pud = xen_alloc_pud;
	pv_ops.mmu.release_pud = xen_release_pud;
	pv_ops.mmu.make_pte = PV_CALLEE_SAVE(xen_make_pte);

	pv_ops.mmu.ग_लिखो_cr3 = &xen_ग_लिखो_cr3;
पूर्ण

अटल व्योम xen_leave_lazy_mmu(व्योम)
अणु
	preempt_disable();
	xen_mc_flush();
	paravirt_leave_lazy_mmu();
	preempt_enable();
पूर्ण

अटल स्थिर काष्ठा pv_mmu_ops xen_mmu_ops __initस्थिर = अणु
	.पढ़ो_cr2 = __PV_IS_CALLEE_SAVE(xen_पढ़ो_cr2),
	.ग_लिखो_cr2 = xen_ग_लिखो_cr2,

	.पढ़ो_cr3 = xen_पढ़ो_cr3,
	.ग_लिखो_cr3 = xen_ग_लिखो_cr3_init,

	.flush_tlb_user = xen_flush_tlb,
	.flush_tlb_kernel = xen_flush_tlb,
	.flush_tlb_one_user = xen_flush_tlb_one_user,
	.flush_tlb_multi = xen_flush_tlb_multi,
	.tlb_हटाओ_table = tlb_हटाओ_table,

	.pgd_alloc = xen_pgd_alloc,
	.pgd_मुक्त = xen_pgd_मुक्त,

	.alloc_pte = xen_alloc_pte_init,
	.release_pte = xen_release_pte_init,
	.alloc_pmd = xen_alloc_pmd_init,
	.release_pmd = xen_release_pmd_init,

	.set_pte = xen_set_pte_init,
	.set_pmd = xen_set_pmd_hyper,

	.ptep_modअगरy_prot_start = __ptep_modअगरy_prot_start,
	.ptep_modअगरy_prot_commit = __ptep_modअगरy_prot_commit,

	.pte_val = PV_CALLEE_SAVE(xen_pte_val),
	.pgd_val = PV_CALLEE_SAVE(xen_pgd_val),

	.make_pte = PV_CALLEE_SAVE(xen_make_pte_init),
	.make_pgd = PV_CALLEE_SAVE(xen_make_pgd),

	.set_pud = xen_set_pud_hyper,

	.make_pmd = PV_CALLEE_SAVE(xen_make_pmd),
	.pmd_val = PV_CALLEE_SAVE(xen_pmd_val),

	.pud_val = PV_CALLEE_SAVE(xen_pud_val),
	.make_pud = PV_CALLEE_SAVE(xen_make_pud),
	.set_p4d = xen_set_p4d_hyper,

	.alloc_pud = xen_alloc_pmd_init,
	.release_pud = xen_release_pmd_init,

#अगर CONFIG_PGTABLE_LEVELS >= 5
	.p4d_val = PV_CALLEE_SAVE(xen_p4d_val),
	.make_p4d = PV_CALLEE_SAVE(xen_make_p4d),
#पूर्ण_अगर

	.activate_mm = xen_activate_mm,
	.dup_mmap = xen_dup_mmap,
	.निकास_mmap = xen_निकास_mmap,

	.lazy_mode = अणु
		.enter = paravirt_enter_lazy_mmu,
		.leave = xen_leave_lazy_mmu,
		.flush = paravirt_flush_lazy_mmu,
	पूर्ण,

	.set_fixmap = xen_set_fixmap,
पूर्ण;

व्योम __init xen_init_mmu_ops(व्योम)
अणु
	x86_init.paging.pagetable_init = xen_pagetable_init;
	x86_init.hyper.init_after_booपंचांगem = xen_after_booपंचांगem;

	pv_ops.mmu = xen_mmu_ops;

	स_रखो(dummy_mapping, 0xff, PAGE_SIZE);
पूर्ण

/* Protected by xen_reservation_lock. */
#घोषणा MAX_CONTIG_ORDER 9 /* 2MB */
अटल अचिन्हित दीर्घ discontig_frames[1<<MAX_CONTIG_ORDER];

#घोषणा VOID_PTE (mfn_pte(0, __pgprot(0)))
अटल व्योम xen_zap_pfn_range(अचिन्हित दीर्घ vaddr, अचिन्हित पूर्णांक order,
				अचिन्हित दीर्घ *in_frames,
				अचिन्हित दीर्घ *out_frames)
अणु
	पूर्णांक i;
	काष्ठा multicall_space mcs;

	xen_mc_batch();
	क्रम (i = 0; i < (1UL<<order); i++, vaddr += PAGE_SIZE) अणु
		mcs = __xen_mc_entry(0);

		अगर (in_frames)
			in_frames[i] = virt_to_mfn(vaddr);

		MULTI_update_va_mapping(mcs.mc, vaddr, VOID_PTE, 0);
		__set_phys_to_machine(virt_to_pfn(vaddr), INVALID_P2M_ENTRY);

		अगर (out_frames)
			out_frames[i] = virt_to_pfn(vaddr);
	पूर्ण
	xen_mc_issue(0);
पूर्ण

/*
 * Update the pfn-to-mfn mappings क्रम a भव address range, either to
 * poपूर्णांक to an array of mfns, or contiguously from a single starting
 * mfn.
 */
अटल व्योम xen_remap_exchanged_ptes(अचिन्हित दीर्घ vaddr, पूर्णांक order,
				     अचिन्हित दीर्घ *mfns,
				     अचिन्हित दीर्घ first_mfn)
अणु
	अचिन्हित i, limit;
	अचिन्हित दीर्घ mfn;

	xen_mc_batch();

	limit = 1u << order;
	क्रम (i = 0; i < limit; i++, vaddr += PAGE_SIZE) अणु
		काष्ठा multicall_space mcs;
		अचिन्हित flags;

		mcs = __xen_mc_entry(0);
		अगर (mfns)
			mfn = mfns[i];
		अन्यथा
			mfn = first_mfn + i;

		अगर (i < (limit - 1))
			flags = 0;
		अन्यथा अणु
			अगर (order == 0)
				flags = UVMF_INVLPG | UVMF_ALL;
			अन्यथा
				flags = UVMF_TLB_FLUSH | UVMF_ALL;
		पूर्ण

		MULTI_update_va_mapping(mcs.mc, vaddr,
				mfn_pte(mfn, PAGE_KERNEL), flags);

		set_phys_to_machine(virt_to_pfn(vaddr), mfn);
	पूर्ण

	xen_mc_issue(0);
पूर्ण

/*
 * Perक्रमm the hypercall to exchange a region of our pfns to poपूर्णांक to
 * memory with the required contiguous alignment.  Takes the pfns as
 * input, and populates mfns as output.
 *
 * Returns a success code indicating whether the hypervisor was able to
 * satisfy the request or not.
 */
अटल पूर्णांक xen_exchange_memory(अचिन्हित दीर्घ extents_in, अचिन्हित पूर्णांक order_in,
			       अचिन्हित दीर्घ *pfns_in,
			       अचिन्हित दीर्घ extents_out,
			       अचिन्हित पूर्णांक order_out,
			       अचिन्हित दीर्घ *mfns_out,
			       अचिन्हित पूर्णांक address_bits)
अणु
	दीर्घ rc;
	पूर्णांक success;

	काष्ठा xen_memory_exchange exchange = अणु
		.in = अणु
			.nr_extents   = extents_in,
			.extent_order = order_in,
			.extent_start = pfns_in,
			.करोmid        = DOMID_SELF
		पूर्ण,
		.out = अणु
			.nr_extents   = extents_out,
			.extent_order = order_out,
			.extent_start = mfns_out,
			.address_bits = address_bits,
			.करोmid        = DOMID_SELF
		पूर्ण
	पूर्ण;

	BUG_ON(extents_in << order_in != extents_out << order_out);

	rc = HYPERVISOR_memory_op(XENMEM_exchange, &exchange);
	success = (exchange.nr_exchanged == extents_in);

	BUG_ON(!success && ((exchange.nr_exchanged != 0) || (rc == 0)));
	BUG_ON(success && (rc != 0));

	वापस success;
पूर्ण

पूर्णांक xen_create_contiguous_region(phys_addr_t pstart, अचिन्हित पूर्णांक order,
				 अचिन्हित पूर्णांक address_bits,
				 dma_addr_t *dma_handle)
अणु
	अचिन्हित दीर्घ *in_frames = discontig_frames, out_frame;
	अचिन्हित दीर्घ  flags;
	पूर्णांक            success;
	अचिन्हित दीर्घ vstart = (अचिन्हित दीर्घ)phys_to_virt(pstart);

	/*
	 * Currently an स्वतः-translated guest will not perक्रमm I/O, nor will
	 * it require PAE page directories below 4GB. Thereक्रमe any calls to
	 * this function are redundant and can be ignored.
	 */

	अगर (unlikely(order > MAX_CONTIG_ORDER))
		वापस -ENOMEM;

	स_रखो((व्योम *) vstart, 0, PAGE_SIZE << order);

	spin_lock_irqsave(&xen_reservation_lock, flags);

	/* 1. Zap current PTEs, remembering MFNs. */
	xen_zap_pfn_range(vstart, order, in_frames, शून्य);

	/* 2. Get a new contiguous memory extent. */
	out_frame = virt_to_pfn(vstart);
	success = xen_exchange_memory(1UL << order, 0, in_frames,
				      1, order, &out_frame,
				      address_bits);

	/* 3. Map the new extent in place of old pages. */
	अगर (success)
		xen_remap_exchanged_ptes(vstart, order, शून्य, out_frame);
	अन्यथा
		xen_remap_exchanged_ptes(vstart, order, in_frames, 0);

	spin_unlock_irqrestore(&xen_reservation_lock, flags);

	*dma_handle = virt_to_machine(vstart).maddr;
	वापस success ? 0 : -ENOMEM;
पूर्ण

व्योम xen_destroy_contiguous_region(phys_addr_t pstart, अचिन्हित पूर्णांक order)
अणु
	अचिन्हित दीर्घ *out_frames = discontig_frames, in_frame;
	अचिन्हित दीर्घ  flags;
	पूर्णांक success;
	अचिन्हित दीर्घ vstart;

	अगर (unlikely(order > MAX_CONTIG_ORDER))
		वापस;

	vstart = (अचिन्हित दीर्घ)phys_to_virt(pstart);
	स_रखो((व्योम *) vstart, 0, PAGE_SIZE << order);

	spin_lock_irqsave(&xen_reservation_lock, flags);

	/* 1. Find start MFN of contiguous extent. */
	in_frame = virt_to_mfn(vstart);

	/* 2. Zap current PTEs. */
	xen_zap_pfn_range(vstart, order, शून्य, out_frames);

	/* 3. Do the exchange क्रम non-contiguous MFNs. */
	success = xen_exchange_memory(1, order, &in_frame, 1UL << order,
					0, out_frames, 0);

	/* 4. Map new pages in place of old pages. */
	अगर (success)
		xen_remap_exchanged_ptes(vstart, order, out_frames, 0);
	अन्यथा
		xen_remap_exchanged_ptes(vstart, order, शून्य, in_frame);

	spin_unlock_irqrestore(&xen_reservation_lock, flags);
पूर्ण

अटल noअंतरभूत व्योम xen_flush_tlb_all(व्योम)
अणु
	काष्ठा mmuext_op *op;
	काष्ठा multicall_space mcs;

	preempt_disable();

	mcs = xen_mc_entry(माप(*op));

	op = mcs.args;
	op->cmd = MMUEXT_TLB_FLUSH_ALL;
	MULTI_mmuext_op(mcs.mc, op, 1, शून्य, DOMID_SELF);

	xen_mc_issue(PARAVIRT_LAZY_MMU);

	preempt_enable();
पूर्ण

#घोषणा REMAP_BATCH_SIZE 16

काष्ठा remap_data अणु
	xen_pfn_t *pfn;
	bool contiguous;
	bool no_translate;
	pgprot_t prot;
	काष्ठा mmu_update *mmu_update;
पूर्ण;

अटल पूर्णांक remap_area_pfn_pte_fn(pte_t *ptep, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा remap_data *rmd = data;
	pte_t pte = pte_mkspecial(mfn_pte(*rmd->pfn, rmd->prot));

	/*
	 * If we have a contiguous range, just update the pfn itself,
	 * अन्यथा update poपूर्णांकer to be "next pfn".
	 */
	अगर (rmd->contiguous)
		(*rmd->pfn)++;
	अन्यथा
		rmd->pfn++;

	rmd->mmu_update->ptr = virt_to_machine(ptep).maddr;
	rmd->mmu_update->ptr |= rmd->no_translate ?
		MMU_PT_UPDATE_NO_TRANSLATE :
		MMU_NORMAL_PT_UPDATE;
	rmd->mmu_update->val = pte_val_ma(pte);
	rmd->mmu_update++;

	वापस 0;
पूर्ण

पूर्णांक xen_remap_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		  xen_pfn_t *pfn, पूर्णांक nr, पूर्णांक *err_ptr, pgprot_t prot,
		  अचिन्हित पूर्णांक करोmid, bool no_translate, काष्ठा page **pages)
अणु
	पूर्णांक err = 0;
	काष्ठा remap_data rmd;
	काष्ठा mmu_update mmu_update[REMAP_BATCH_SIZE];
	अचिन्हित दीर्घ range;
	पूर्णांक mapped = 0;

	BUG_ON(!((vma->vm_flags & (VM_PFNMAP | VM_IO)) == (VM_PFNMAP | VM_IO)));

	rmd.pfn = pfn;
	rmd.prot = prot;
	/*
	 * We use the err_ptr to indicate अगर there we are करोing a contiguous
	 * mapping or a discontiguous mapping.
	 */
	rmd.contiguous = !err_ptr;
	rmd.no_translate = no_translate;

	जबतक (nr) अणु
		पूर्णांक index = 0;
		पूर्णांक करोne = 0;
		पूर्णांक batch = min(REMAP_BATCH_SIZE, nr);
		पूर्णांक batch_left = batch;

		range = (अचिन्हित दीर्घ)batch << PAGE_SHIFT;

		rmd.mmu_update = mmu_update;
		err = apply_to_page_range(vma->vm_mm, addr, range,
					  remap_area_pfn_pte_fn, &rmd);
		अगर (err)
			जाओ out;

		/*
		 * We record the error क्रम each page that gives an error, but
		 * जारी mapping until the whole set is करोne
		 */
		करो अणु
			पूर्णांक i;

			err = HYPERVISOR_mmu_update(&mmu_update[index],
						    batch_left, &करोne, करोmid);

			/*
			 * @err_ptr may be the same buffer as @gfn, so
			 * only clear it after each chunk of @gfn is
			 * used.
			 */
			अगर (err_ptr) अणु
				क्रम (i = index; i < index + करोne; i++)
					err_ptr[i] = 0;
			पूर्ण
			अगर (err < 0) अणु
				अगर (!err_ptr)
					जाओ out;
				err_ptr[i] = err;
				करोne++; /* Skip failed frame. */
			पूर्ण अन्यथा
				mapped += करोne;
			batch_left -= करोne;
			index += करोne;
		पूर्ण जबतक (batch_left);

		nr -= batch;
		addr += range;
		अगर (err_ptr)
			err_ptr += batch;
		cond_resched();
	पूर्ण
out:

	xen_flush_tlb_all();

	वापस err < 0 ? err : mapped;
पूर्ण
EXPORT_SYMBOL_GPL(xen_remap_pfn);

#अगर_घोषित CONFIG_KEXEC_CORE
phys_addr_t paddr_vmcoreinfo_note(व्योम)
अणु
	अगर (xen_pv_करोमुख्य())
		वापस virt_to_machine(vmcoreinfo_note).maddr;
	अन्यथा
		वापस __pa(vmcoreinfo_note);
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_CORE */
