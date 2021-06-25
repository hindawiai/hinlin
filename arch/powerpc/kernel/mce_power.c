<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Machine check exception handling CPU-side क्रम घातer7 and घातer8
 *
 * Copyright 2013 IBM Corporation
 * Author: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
 */

#अघोषित DEBUG
#घोषणा pr_fmt(fmt) "mce_power: " fmt

#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/extable.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pte-walk.h>
#समावेश <यंत्र/sstep.h>
#समावेश <यंत्र/exception-64s.h>
#समावेश <यंत्र/extable.h>
#समावेश <यंत्र/inst.h>

/*
 * Convert an address related to an mm to a PFN. NOTE: we are in real
 * mode, we could potentially race with page table updates.
 */
अचिन्हित दीर्घ addr_to_pfn(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	pte_t *ptep, pte;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित दीर्घ pfn, flags;
	काष्ठा mm_काष्ठा *mm;

	अगर (user_mode(regs))
		mm = current->mm;
	अन्यथा
		mm = &init_mm;

	local_irq_save(flags);
	ptep = __find_linux_pte(mm->pgd, addr, शून्य, &shअगरt);
	अगर (!ptep) अणु
		pfn = अच_दीर्घ_उच्च;
		जाओ out;
	पूर्ण
	pte = READ_ONCE(*ptep);

	अगर (!pte_present(pte) || pte_special(pte)) अणु
		pfn = अच_दीर्घ_उच्च;
		जाओ out;
	पूर्ण

	अगर (shअगरt <= PAGE_SHIFT)
		pfn = pte_pfn(pte);
	अन्यथा अणु
		अचिन्हित दीर्घ rpnmask = (1ul << shअगरt) - PAGE_SIZE;
		pfn = pte_pfn(__pte(pte_val(pte) | (addr & rpnmask)));
	पूर्ण
out:
	local_irq_restore(flags);
	वापस pfn;
पूर्ण

अटल bool mce_in_guest(व्योम)
अणु
#अगर_घोषित CONFIG_KVM_BOOK3S_HANDLER
	/*
	 * If machine check is hit when in guest context or low level KVM
	 * code, aव्योम looking up any translations or making any attempts
	 * to recover, just record the event and pass to KVM.
	 */
	अगर (get_paca()->kvm_hstate.in_guest)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

/* flush SLBs and reload */
#अगर_घोषित CONFIG_PPC_BOOK3S_64
व्योम flush_and_reload_slb(व्योम)
अणु
	/* Invalidate all SLBs */
	slb_flush_all_realmode();

	अगर (early_radix_enabled())
		वापस;

	/*
	 * This probably shouldn't happen, but it may be possible it's
	 * called in early boot beक्रमe SLB shaकरोws are allocated.
	 */
	अगर (!get_slb_shaकरोw())
		वापस;

	slb_restore_bolted_realmode();
पूर्ण
#पूर्ण_अगर

व्योम flush_erat(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (!early_cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		flush_and_reload_slb();
		वापस;
	पूर्ण
#पूर्ण_अगर
	यंत्र अस्थिर(PPC_ISA_3_0_INVALIDATE_ERAT : : :"memory");
पूर्ण

#घोषणा MCE_FLUSH_SLB 1
#घोषणा MCE_FLUSH_TLB 2
#घोषणा MCE_FLUSH_ERAT 3

अटल पूर्णांक mce_flush(पूर्णांक what)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (what == MCE_FLUSH_SLB) अणु
		flush_and_reload_slb();
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	अगर (what == MCE_FLUSH_ERAT) अणु
		flush_erat();
		वापस 1;
	पूर्ण
	अगर (what == MCE_FLUSH_TLB) अणु
		tlbiel_all();
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा SRR1_MC_LOADSTORE(srr1)	((srr1) & PPC_BIT(42))

काष्ठा mce_ierror_table अणु
	अचिन्हित दीर्घ srr1_mask;
	अचिन्हित दीर्घ srr1_value;
	bool nip_valid; /* nip is a valid indicator of faulting address */
	अचिन्हित पूर्णांक error_type;
	अचिन्हित पूर्णांक error_subtype;
	अचिन्हित पूर्णांक error_class;
	अचिन्हित पूर्णांक initiator;
	अचिन्हित पूर्णांक severity;
	bool sync_error;
पूर्ण;

अटल स्थिर काष्ठा mce_ierror_table mce_p7_ierror_table[] = अणु
अणु 0x00000000001c0000, 0x0000000000040000, true,
  MCE_ERROR_TYPE_UE,  MCE_UE_ERROR_IFETCH, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000001c0000, 0x0000000000080000, true,
  MCE_ERROR_TYPE_SLB, MCE_SLB_ERROR_PARITY, MCE_ECLASS_HARD_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000001c0000, 0x00000000000c0000, true,
  MCE_ERROR_TYPE_SLB, MCE_SLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000001c0000, 0x0000000000100000, true,
  MCE_ERROR_TYPE_SLB, MCE_SLB_ERROR_INDETERMINATE, /* BOTH */
  MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000001c0000, 0x0000000000140000, true,
  MCE_ERROR_TYPE_TLB, MCE_TLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000001c0000, 0x0000000000180000, true,
  MCE_ERROR_TYPE_UE,  MCE_UE_ERROR_PAGE_TABLE_WALK_IFETCH, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000001c0000, 0x00000000001c0000, true,
  MCE_ERROR_TYPE_UE,  MCE_UE_ERROR_IFETCH, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0, 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण;

अटल स्थिर काष्ठा mce_ierror_table mce_p8_ierror_table[] = अणु
अणु 0x00000000081c0000, 0x0000000000040000, true,
  MCE_ERROR_TYPE_UE,  MCE_UE_ERROR_IFETCH, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000080000, true,
  MCE_ERROR_TYPE_SLB, MCE_SLB_ERROR_PARITY, MCE_ECLASS_HARD_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x00000000000c0000, true,
  MCE_ERROR_TYPE_SLB, MCE_SLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000100000, true,
  MCE_ERROR_TYPE_ERAT, MCE_ERAT_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000140000, true,
  MCE_ERROR_TYPE_TLB, MCE_TLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000180000, true,
  MCE_ERROR_TYPE_UE,  MCE_UE_ERROR_PAGE_TABLE_WALK_IFETCH,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x00000000001c0000, true,
  MCE_ERROR_TYPE_UE,  MCE_UE_ERROR_IFETCH, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000008000000, true,
  MCE_ERROR_TYPE_LINK, MCE_LINK_ERROR_IFETCH_TIMEOUT, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000008040000, true,
  MCE_ERROR_TYPE_LINK,MCE_LINK_ERROR_PAGE_TABLE_WALK_IFETCH_TIMEOUT,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0, 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण;

अटल स्थिर काष्ठा mce_ierror_table mce_p9_ierror_table[] = अणु
अणु 0x00000000081c0000, 0x0000000000040000, true,
  MCE_ERROR_TYPE_UE,  MCE_UE_ERROR_IFETCH, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000080000, true,
  MCE_ERROR_TYPE_SLB, MCE_SLB_ERROR_PARITY, MCE_ECLASS_HARD_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x00000000000c0000, true,
  MCE_ERROR_TYPE_SLB, MCE_SLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000100000, true,
  MCE_ERROR_TYPE_ERAT, MCE_ERAT_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000140000, true,
  MCE_ERROR_TYPE_TLB, MCE_TLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000180000, true,
  MCE_ERROR_TYPE_UE,  MCE_UE_ERROR_PAGE_TABLE_WALK_IFETCH, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x00000000001c0000, true,
  MCE_ERROR_TYPE_RA,  MCE_RA_ERROR_IFETCH_FOREIGN, MCE_ECLASS_SOFTWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000008000000, true,
  MCE_ERROR_TYPE_LINK, MCE_LINK_ERROR_IFETCH_TIMEOUT, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000008040000, true,
  MCE_ERROR_TYPE_LINK,MCE_LINK_ERROR_PAGE_TABLE_WALK_IFETCH_TIMEOUT,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x00000000080c0000, true,
  MCE_ERROR_TYPE_RA,  MCE_RA_ERROR_IFETCH, MCE_ECLASS_SOFTWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000008100000, true,
  MCE_ERROR_TYPE_RA,  MCE_RA_ERROR_PAGE_TABLE_WALK_IFETCH, MCE_ECLASS_SOFTWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000008140000, false,
  MCE_ERROR_TYPE_RA,  MCE_RA_ERROR_STORE, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_FATAL, false पूर्ण, /* ASYNC is fatal */
अणु 0x00000000081c0000, 0x0000000008180000, false,
  MCE_ERROR_TYPE_LINK,MCE_LINK_ERROR_STORE_TIMEOUT,
  MCE_INITIATOR_CPU,  MCE_SEV_FATAL, false पूर्ण, /* ASYNC is fatal */
अणु 0x00000000081c0000, 0x00000000081c0000, true, MCE_ECLASS_HARDWARE,
  MCE_ERROR_TYPE_RA,  MCE_RA_ERROR_PAGE_TABLE_WALK_IFETCH_FOREIGN,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0, 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण;

अटल स्थिर काष्ठा mce_ierror_table mce_p10_ierror_table[] = अणु
अणु 0x00000000081c0000, 0x0000000000040000, true,
  MCE_ERROR_TYPE_UE,  MCE_UE_ERROR_IFETCH, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000080000, true,
  MCE_ERROR_TYPE_SLB, MCE_SLB_ERROR_PARITY, MCE_ECLASS_HARD_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x00000000000c0000, true,
  MCE_ERROR_TYPE_SLB, MCE_SLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000100000, true,
  MCE_ERROR_TYPE_ERAT, MCE_ERAT_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000140000, true,
  MCE_ERROR_TYPE_TLB, MCE_TLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000000180000, true,
  MCE_ERROR_TYPE_UE,  MCE_UE_ERROR_PAGE_TABLE_WALK_IFETCH, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x00000000001c0000, true,
  MCE_ERROR_TYPE_RA,  MCE_RA_ERROR_IFETCH_FOREIGN, MCE_ECLASS_SOFTWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000008080000, true,
  MCE_ERROR_TYPE_USER,MCE_USER_ERROR_SCV, MCE_ECLASS_SOFTWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000000081c0000, 0x00000000080c0000, true,
  MCE_ERROR_TYPE_RA,  MCE_RA_ERROR_IFETCH, MCE_ECLASS_SOFTWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000008100000, true,
  MCE_ERROR_TYPE_RA,  MCE_RA_ERROR_PAGE_TABLE_WALK_IFETCH, MCE_ECLASS_SOFTWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000000081c0000, 0x0000000008140000, false,
  MCE_ERROR_TYPE_RA,  MCE_RA_ERROR_STORE, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,  MCE_SEV_FATAL, false पूर्ण, /* ASYNC is fatal */
अणु 0x00000000081c0000, 0x00000000081c0000, true, MCE_ECLASS_HARDWARE,
  MCE_ERROR_TYPE_RA,  MCE_RA_ERROR_PAGE_TABLE_WALK_IFETCH_FOREIGN,
  MCE_INITIATOR_CPU,  MCE_SEV_SEVERE, true पूर्ण,
अणु 0, 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण;

काष्ठा mce_derror_table अणु
	अचिन्हित दीर्घ dsisr_value;
	bool dar_valid; /* dar is a valid indicator of faulting address */
	अचिन्हित पूर्णांक error_type;
	अचिन्हित पूर्णांक error_subtype;
	अचिन्हित पूर्णांक error_class;
	अचिन्हित पूर्णांक initiator;
	अचिन्हित पूर्णांक severity;
	bool sync_error;
पूर्ण;

अटल स्थिर काष्ठा mce_derror_table mce_p7_derror_table[] = अणु
अणु 0x00008000, false,
  MCE_ERROR_TYPE_UE,   MCE_UE_ERROR_LOAD_STORE, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00004000, true,
  MCE_ERROR_TYPE_UE,   MCE_UE_ERROR_PAGE_TABLE_WALK_LOAD_STORE,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000800, true,
  MCE_ERROR_TYPE_ERAT, MCE_ERAT_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000400, true,
  MCE_ERROR_TYPE_TLB,  MCE_TLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000080, true,
  MCE_ERROR_TYPE_SLB,  MCE_SLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000100, true,
  MCE_ERROR_TYPE_SLB,  MCE_SLB_ERROR_PARITY, MCE_ECLASS_HARD_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000040, true,
  MCE_ERROR_TYPE_SLB,  MCE_SLB_ERROR_INDETERMINATE, /* BOTH */
  MCE_ECLASS_HARD_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0, false, 0, 0, 0, 0, 0 पूर्ण पूर्ण;

अटल स्थिर काष्ठा mce_derror_table mce_p8_derror_table[] = अणु
अणु 0x00008000, false,
  MCE_ERROR_TYPE_UE,   MCE_UE_ERROR_LOAD_STORE, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00004000, true,
  MCE_ERROR_TYPE_UE,   MCE_UE_ERROR_PAGE_TABLE_WALK_LOAD_STORE,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00002000, true,
  MCE_ERROR_TYPE_LINK, MCE_LINK_ERROR_LOAD_TIMEOUT, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00001000, true,
  MCE_ERROR_TYPE_LINK, MCE_LINK_ERROR_PAGE_TABLE_WALK_LOAD_STORE_TIMEOUT,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000800, true,
  MCE_ERROR_TYPE_ERAT, MCE_ERAT_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000400, true,
  MCE_ERROR_TYPE_TLB,  MCE_TLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000200, true,
  MCE_ERROR_TYPE_ERAT, MCE_ERAT_ERROR_MULTIHIT, /* SECONDARY ERAT */
  MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000080, true,
  MCE_ERROR_TYPE_SLB,  MCE_SLB_ERROR_MULTIHIT,	/* Beक्रमe PARITY */
  MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000100, true,
  MCE_ERROR_TYPE_SLB,  MCE_SLB_ERROR_PARITY, MCE_ECLASS_HARD_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0, false, 0, 0, 0, 0, 0 पूर्ण पूर्ण;

अटल स्थिर काष्ठा mce_derror_table mce_p9_derror_table[] = अणु
अणु 0x00008000, false,
  MCE_ERROR_TYPE_UE,   MCE_UE_ERROR_LOAD_STORE, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00004000, true,
  MCE_ERROR_TYPE_UE,   MCE_UE_ERROR_PAGE_TABLE_WALK_LOAD_STORE,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00002000, true,
  MCE_ERROR_TYPE_LINK, MCE_LINK_ERROR_LOAD_TIMEOUT, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00001000, true,
  MCE_ERROR_TYPE_LINK, MCE_LINK_ERROR_PAGE_TABLE_WALK_LOAD_STORE_TIMEOUT,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000800, true,
  MCE_ERROR_TYPE_ERAT, MCE_ERAT_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000400, true,
  MCE_ERROR_TYPE_TLB,  MCE_TLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000200, false,
  MCE_ERROR_TYPE_USER, MCE_USER_ERROR_TLBIE, MCE_ECLASS_SOFTWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000080, true,
  MCE_ERROR_TYPE_SLB,  MCE_SLB_ERROR_MULTIHIT,	/* Beक्रमe PARITY */
  MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000100, true,
  MCE_ERROR_TYPE_SLB,  MCE_SLB_ERROR_PARITY, MCE_ECLASS_HARD_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000040, true,
  MCE_ERROR_TYPE_RA,   MCE_RA_ERROR_LOAD, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000020, false,
  MCE_ERROR_TYPE_RA,   MCE_RA_ERROR_PAGE_TABLE_WALK_LOAD_STORE,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000010, false,
  MCE_ERROR_TYPE_RA,   MCE_RA_ERROR_PAGE_TABLE_WALK_LOAD_STORE_FOREIGN,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000008, false,
  MCE_ERROR_TYPE_RA,   MCE_RA_ERROR_LOAD_STORE_FOREIGN, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0, false, 0, 0, 0, 0, 0 पूर्ण पूर्ण;

अटल स्थिर काष्ठा mce_derror_table mce_p10_derror_table[] = अणु
अणु 0x00008000, false,
  MCE_ERROR_TYPE_UE,   MCE_UE_ERROR_LOAD_STORE, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00004000, true,
  MCE_ERROR_TYPE_UE,   MCE_UE_ERROR_PAGE_TABLE_WALK_LOAD_STORE,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000800, true,
  MCE_ERROR_TYPE_ERAT, MCE_ERAT_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000400, true,
  MCE_ERROR_TYPE_TLB,  MCE_TLB_ERROR_MULTIHIT, MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000200, false,
  MCE_ERROR_TYPE_USER, MCE_USER_ERROR_TLBIE, MCE_ECLASS_SOFTWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000080, true,
  MCE_ERROR_TYPE_SLB,  MCE_SLB_ERROR_MULTIHIT,	/* Beक्रमe PARITY */
  MCE_ECLASS_SOFT_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_WARNING, true पूर्ण,
अणु 0x00000100, true,
  MCE_ERROR_TYPE_SLB,  MCE_SLB_ERROR_PARITY, MCE_ECLASS_HARD_INDETERMINATE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000040, true,
  MCE_ERROR_TYPE_RA,   MCE_RA_ERROR_LOAD, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000020, false,
  MCE_ERROR_TYPE_RA,   MCE_RA_ERROR_PAGE_TABLE_WALK_LOAD_STORE,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000010, false,
  MCE_ERROR_TYPE_RA,   MCE_RA_ERROR_PAGE_TABLE_WALK_LOAD_STORE_FOREIGN,
  MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0x00000008, false,
  MCE_ERROR_TYPE_RA,   MCE_RA_ERROR_LOAD_STORE_FOREIGN, MCE_ECLASS_HARDWARE,
  MCE_INITIATOR_CPU,   MCE_SEV_SEVERE, true पूर्ण,
अणु 0, false, 0, 0, 0, 0, 0 पूर्ण पूर्ण;

अटल पूर्णांक mce_find_instr_ea_and_phys(काष्ठा pt_regs *regs, uपूर्णांक64_t *addr,
					uपूर्णांक64_t *phys_addr)
अणु
	/*
	 * Carefully look at the NIP to determine
	 * the inकाष्ठाion to analyse. Reading the NIP
	 * in real-mode is tricky and can lead to recursive
	 * faults
	 */
	काष्ठा ppc_inst instr;
	अचिन्हित दीर्घ pfn, instr_addr;
	काष्ठा inकाष्ठाion_op op;
	काष्ठा pt_regs पंचांगp = *regs;

	pfn = addr_to_pfn(regs, regs->nip);
	अगर (pfn != अच_दीर्घ_उच्च) अणु
		instr_addr = (pfn << PAGE_SHIFT) + (regs->nip & ~PAGE_MASK);
		instr = ppc_inst_पढ़ो((काष्ठा ppc_inst *)instr_addr);
		अगर (!analyse_instr(&op, &पंचांगp, instr)) अणु
			pfn = addr_to_pfn(regs, op.ea);
			*addr = op.ea;
			*phys_addr = (pfn << PAGE_SHIFT);
			वापस 0;
		पूर्ण
		/*
		 * analyse_instr() might fail अगर the inकाष्ठाion
		 * is not a load/store, although this is unexpected
		 * क्रम load/store errors or अगर we got the NIP
		 * wrong
		 */
	पूर्ण
	*addr = 0;
	वापस -1;
पूर्ण

अटल पूर्णांक mce_handle_ierror(काष्ठा pt_regs *regs,
		स्थिर काष्ठा mce_ierror_table table[],
		काष्ठा mce_error_info *mce_err, uपूर्णांक64_t *addr,
		uपूर्णांक64_t *phys_addr)
अणु
	uपूर्णांक64_t srr1 = regs->msr;
	पूर्णांक handled = 0;
	पूर्णांक i;

	*addr = 0;

	क्रम (i = 0; table[i].srr1_mask; i++) अणु
		अगर ((srr1 & table[i].srr1_mask) != table[i].srr1_value)
			जारी;

		अगर (!mce_in_guest()) अणु
			/* attempt to correct the error */
			चयन (table[i].error_type) अणु
			हाल MCE_ERROR_TYPE_SLB:
				अगर (local_paca->in_mce == 1)
					slb_save_contents(local_paca->mce_faulty_slbs);
				handled = mce_flush(MCE_FLUSH_SLB);
				अवरोध;
			हाल MCE_ERROR_TYPE_ERAT:
				handled = mce_flush(MCE_FLUSH_ERAT);
				अवरोध;
			हाल MCE_ERROR_TYPE_TLB:
				handled = mce_flush(MCE_FLUSH_TLB);
				अवरोध;
			पूर्ण
		पूर्ण

		/* now fill in mce_error_info */
		mce_err->error_type = table[i].error_type;
		mce_err->error_class = table[i].error_class;
		चयन (table[i].error_type) अणु
		हाल MCE_ERROR_TYPE_UE:
			mce_err->u.ue_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_SLB:
			mce_err->u.slb_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_ERAT:
			mce_err->u.erat_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_TLB:
			mce_err->u.tlb_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_USER:
			mce_err->u.user_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_RA:
			mce_err->u.ra_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_LINK:
			mce_err->u.link_error_type = table[i].error_subtype;
			अवरोध;
		पूर्ण
		mce_err->sync_error = table[i].sync_error;
		mce_err->severity = table[i].severity;
		mce_err->initiator = table[i].initiator;
		अगर (table[i].nip_valid && !mce_in_guest()) अणु
			*addr = regs->nip;
			अगर (mce_err->sync_error &&
				table[i].error_type == MCE_ERROR_TYPE_UE) अणु
				अचिन्हित दीर्घ pfn;

				अगर (get_paca()->in_mce < MAX_MCE_DEPTH) अणु
					pfn = addr_to_pfn(regs, regs->nip);
					अगर (pfn != अच_दीर्घ_उच्च) अणु
						*phys_addr =
							(pfn << PAGE_SHIFT);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		वापस handled;
	पूर्ण

	mce_err->error_type = MCE_ERROR_TYPE_UNKNOWN;
	mce_err->error_class = MCE_ECLASS_UNKNOWN;
	mce_err->severity = MCE_SEV_SEVERE;
	mce_err->initiator = MCE_INITIATOR_CPU;
	mce_err->sync_error = true;

	वापस 0;
पूर्ण

अटल पूर्णांक mce_handle_derror(काष्ठा pt_regs *regs,
		स्थिर काष्ठा mce_derror_table table[],
		काष्ठा mce_error_info *mce_err, uपूर्णांक64_t *addr,
		uपूर्णांक64_t *phys_addr)
अणु
	uपूर्णांक64_t dsisr = regs->dsisr;
	पूर्णांक handled = 0;
	पूर्णांक found = 0;
	पूर्णांक i;

	*addr = 0;

	क्रम (i = 0; table[i].dsisr_value; i++) अणु
		अगर (!(dsisr & table[i].dsisr_value))
			जारी;

		अगर (!mce_in_guest()) अणु
			/* attempt to correct the error */
			चयन (table[i].error_type) अणु
			हाल MCE_ERROR_TYPE_SLB:
				अगर (local_paca->in_mce == 1)
					slb_save_contents(local_paca->mce_faulty_slbs);
				अगर (mce_flush(MCE_FLUSH_SLB))
					handled = 1;
				अवरोध;
			हाल MCE_ERROR_TYPE_ERAT:
				अगर (mce_flush(MCE_FLUSH_ERAT))
					handled = 1;
				अवरोध;
			हाल MCE_ERROR_TYPE_TLB:
				अगर (mce_flush(MCE_FLUSH_TLB))
					handled = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * Attempt to handle multiple conditions, but only वापस
		 * one. Ensure uncorrectable errors are first in the table
		 * to match.
		 */
		अगर (found)
			जारी;

		/* now fill in mce_error_info */
		mce_err->error_type = table[i].error_type;
		mce_err->error_class = table[i].error_class;
		चयन (table[i].error_type) अणु
		हाल MCE_ERROR_TYPE_UE:
			mce_err->u.ue_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_SLB:
			mce_err->u.slb_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_ERAT:
			mce_err->u.erat_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_TLB:
			mce_err->u.tlb_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_USER:
			mce_err->u.user_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_RA:
			mce_err->u.ra_error_type = table[i].error_subtype;
			अवरोध;
		हाल MCE_ERROR_TYPE_LINK:
			mce_err->u.link_error_type = table[i].error_subtype;
			अवरोध;
		पूर्ण
		mce_err->sync_error = table[i].sync_error;
		mce_err->severity = table[i].severity;
		mce_err->initiator = table[i].initiator;
		अगर (table[i].dar_valid)
			*addr = regs->dar;
		अन्यथा अगर (mce_err->sync_error && !mce_in_guest() &&
				table[i].error_type == MCE_ERROR_TYPE_UE) अणु
			/*
			 * We करो a maximum of 4 nested MCE calls, see
			 * kernel/exception-64s.h
			 */
			अगर (get_paca()->in_mce < MAX_MCE_DEPTH)
				mce_find_instr_ea_and_phys(regs, addr,
							   phys_addr);
		पूर्ण
		found = 1;
	पूर्ण

	अगर (found)
		वापस handled;

	mce_err->error_type = MCE_ERROR_TYPE_UNKNOWN;
	mce_err->error_class = MCE_ECLASS_UNKNOWN;
	mce_err->severity = MCE_SEV_SEVERE;
	mce_err->initiator = MCE_INITIATOR_CPU;
	mce_err->sync_error = true;

	वापस 0;
पूर्ण

अटल दीर्घ mce_handle_ue_error(काष्ठा pt_regs *regs,
				काष्ठा mce_error_info *mce_err)
अणु
	अगर (mce_in_guest())
		वापस 0;

	mce_common_process_ue(regs, mce_err);
	अगर (mce_err->ignore_event)
		वापस 1;

	/*
	 * On specअगरic SCOM पढ़ो via MMIO we may get a machine check
	 * exception with SRR0 poपूर्णांकing inside opal. If that is the
	 * हाल OPAL may have recovery address to re-पढ़ो SCOM data in
	 * dअगरferent way and hence we can recover from this MC.
	 */

	अगर (ppc_md.mce_check_early_recovery) अणु
		अगर (ppc_md.mce_check_early_recovery(regs))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ mce_handle_error(काष्ठा pt_regs *regs,
		स्थिर काष्ठा mce_derror_table dtable[],
		स्थिर काष्ठा mce_ierror_table itable[])
अणु
	काष्ठा mce_error_info mce_err = अणु 0 पूर्ण;
	uपूर्णांक64_t addr, phys_addr = अच_दीर्घ_उच्च;
	uपूर्णांक64_t srr1 = regs->msr;
	दीर्घ handled;

	अगर (SRR1_MC_LOADSTORE(srr1))
		handled = mce_handle_derror(regs, dtable, &mce_err, &addr,
				&phys_addr);
	अन्यथा
		handled = mce_handle_ierror(regs, itable, &mce_err, &addr,
				&phys_addr);

	अगर (!handled && mce_err.error_type == MCE_ERROR_TYPE_UE)
		handled = mce_handle_ue_error(regs, &mce_err);

	save_mce_event(regs, handled, &mce_err, regs->nip, addr, phys_addr);

	वापस handled;
पूर्ण

दीर्घ __machine_check_early_realmode_p7(काष्ठा pt_regs *regs)
अणु
	/* P7 DD1 leaves top bits of DSISR undefined */
	regs->dsisr &= 0x0000ffff;

	वापस mce_handle_error(regs, mce_p7_derror_table, mce_p7_ierror_table);
पूर्ण

दीर्घ __machine_check_early_realmode_p8(काष्ठा pt_regs *regs)
अणु
	वापस mce_handle_error(regs, mce_p8_derror_table, mce_p8_ierror_table);
पूर्ण

दीर्घ __machine_check_early_realmode_p9(काष्ठा pt_regs *regs)
अणु
	/*
	 * On POWER9 DD2.1 and below, it's possible to get a machine check
	 * caused by a paste inकाष्ठाion where only DSISR bit 25 is set. This
	 * will result in the MCE handler seeing an unknown event and the kernel
	 * crashing. An MCE that occurs like this is spurious, so we करोn't need
	 * to करो anything in terms of servicing it. If there is something that
	 * needs to be serviced, the CPU will उठाओ the MCE again with the
	 * correct DSISR so that it can be serviced properly. So detect this
	 * हाल and mark it as handled.
	 */
	अगर (SRR1_MC_LOADSTORE(regs->msr) && regs->dsisr == 0x02000000)
		वापस 1;

	वापस mce_handle_error(regs, mce_p9_derror_table, mce_p9_ierror_table);
पूर्ण

दीर्घ __machine_check_early_realmode_p10(काष्ठा pt_regs *regs)
अणु
	वापस mce_handle_error(regs, mce_p10_derror_table, mce_p10_ierror_table);
पूर्ण
