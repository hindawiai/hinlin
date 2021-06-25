<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TLB flush routines क्रम radix kernels.
 *
 * Copyright 2015-2016, Aneesh Kumar K.V, IBM Corporation.
 */

#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/sched/mm.h>

#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/plpar_wrappers.h>

#समावेश "internal.h"

#घोषणा RIC_FLUSH_TLB 0
#घोषणा RIC_FLUSH_PWC 1
#घोषणा RIC_FLUSH_ALL 2

/*
 * tlbiel inकाष्ठाion क्रम radix, set invalidation
 * i.e., r=1 and is=01 or is=10 or is=11
 */
अटल __always_अंतरभूत व्योम tlbiel_radix_set_isa300(अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक is,
					अचिन्हित पूर्णांक pid,
					अचिन्हित पूर्णांक ric, अचिन्हित पूर्णांक prs)
अणु
	अचिन्हित दीर्घ rb;
	अचिन्हित दीर्घ rs;

	rb = (set << PPC_BITLSHIFT(51)) | (is << PPC_BITLSHIFT(53));
	rs = ((अचिन्हित दीर्घ)pid << PPC_BITLSHIFT(31));

	यंत्र अस्थिर(PPC_TLBIEL(%0, %1, %2, %3, 1)
		     : : "r"(rb), "r"(rs), "i"(ric), "i"(prs)
		     : "memory");
पूर्ण

अटल व्योम tlbiel_all_isa300(अचिन्हित पूर्णांक num_sets, अचिन्हित पूर्णांक is)
अणु
	अचिन्हित पूर्णांक set;

	यंत्र अस्थिर("ptesync": : :"memory");

	/*
	 * Flush the first set of the TLB, and the entire Page Walk Cache
	 * and partition table entries. Then flush the reमुख्यing sets of the
	 * TLB.
	 */

	अगर (early_cpu_has_feature(CPU_FTR_HVMODE)) अणु
		/* MSR[HV] should flush partition scope translations first. */
		tlbiel_radix_set_isa300(0, is, 0, RIC_FLUSH_ALL, 0);

		अगर (!early_cpu_has_feature(CPU_FTR_ARCH_31)) अणु
			क्रम (set = 1; set < num_sets; set++)
				tlbiel_radix_set_isa300(set, is, 0,
							RIC_FLUSH_TLB, 0);
		पूर्ण
	पूर्ण

	/* Flush process scoped entries. */
	tlbiel_radix_set_isa300(0, is, 0, RIC_FLUSH_ALL, 1);

	अगर (!early_cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		क्रम (set = 1; set < num_sets; set++)
			tlbiel_radix_set_isa300(set, is, 0, RIC_FLUSH_TLB, 1);
	पूर्ण

	ppc_after_tlbiel_barrier();
पूर्ण

व्योम radix__tlbiel_all(अचिन्हित पूर्णांक action)
अणु
	अचिन्हित पूर्णांक is;

	चयन (action) अणु
	हाल TLB_INVAL_SCOPE_GLOBAL:
		is = 3;
		अवरोध;
	हाल TLB_INVAL_SCOPE_LPID:
		is = 2;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (early_cpu_has_feature(CPU_FTR_ARCH_300))
		tlbiel_all_isa300(POWER9_TLB_SETS_RADIX, is);
	अन्यथा
		WARN(1, "%s called on pre-POWER9 CPU\n", __func__);

	यंत्र अस्थिर(PPC_ISA_3_0_INVALIDATE_ERAT "; isync" : : :"memory");
पूर्ण

अटल __always_अंतरभूत व्योम __tlbiel_pid(अचिन्हित दीर्घ pid, पूर्णांक set,
				अचिन्हित दीर्घ ric)
अणु
	अचिन्हित दीर्घ rb,rs,prs,r;

	rb = PPC_BIT(53); /* IS = 1 */
	rb |= set << PPC_BITLSHIFT(51);
	rs = ((अचिन्हित दीर्घ)pid) << PPC_BITLSHIFT(31);
	prs = 1; /* process scoped */
	r = 1;   /* radix क्रमmat */

	यंत्र अस्थिर(PPC_TLBIEL(%0, %4, %3, %2, %1)
		     : : "r"(rb), "i"(r), "i"(prs), "i"(ric), "r"(rs) : "memory");
	trace_tlbie(0, 1, rb, rs, ric, prs, r);
पूर्ण

अटल __always_अंतरभूत व्योम __tlbie_pid(अचिन्हित दीर्घ pid, अचिन्हित दीर्घ ric)
अणु
	अचिन्हित दीर्घ rb,rs,prs,r;

	rb = PPC_BIT(53); /* IS = 1 */
	rs = pid << PPC_BITLSHIFT(31);
	prs = 1; /* process scoped */
	r = 1;   /* radix क्रमmat */

	यंत्र अस्थिर(PPC_TLBIE_5(%0, %4, %3, %2, %1)
		     : : "r"(rb), "i"(r), "i"(prs), "i"(ric), "r"(rs) : "memory");
	trace_tlbie(0, 0, rb, rs, ric, prs, r);
पूर्ण

अटल __always_अंतरभूत व्योम __tlbie_lpid(अचिन्हित दीर्घ lpid, अचिन्हित दीर्घ ric)
अणु
	अचिन्हित दीर्घ rb,rs,prs,r;

	rb = PPC_BIT(52); /* IS = 2 */
	rs = lpid;
	prs = 0; /* partition scoped */
	r = 1;   /* radix क्रमmat */

	यंत्र अस्थिर(PPC_TLBIE_5(%0, %4, %3, %2, %1)
		     : : "r"(rb), "i"(r), "i"(prs), "i"(ric), "r"(rs) : "memory");
	trace_tlbie(lpid, 0, rb, rs, ric, prs, r);
पूर्ण

अटल __always_अंतरभूत व्योम __tlbie_lpid_guest(अचिन्हित दीर्घ lpid, अचिन्हित दीर्घ ric)
अणु
	अचिन्हित दीर्घ rb,rs,prs,r;

	rb = PPC_BIT(52); /* IS = 2 */
	rs = lpid;
	prs = 1; /* process scoped */
	r = 1;   /* radix क्रमmat */

	यंत्र अस्थिर(PPC_TLBIE_5(%0, %4, %3, %2, %1)
		     : : "r"(rb), "i"(r), "i"(prs), "i"(ric), "r"(rs) : "memory");
	trace_tlbie(lpid, 0, rb, rs, ric, prs, r);
पूर्ण

अटल __always_अंतरभूत व्योम __tlbiel_va(अचिन्हित दीर्घ va, अचिन्हित दीर्घ pid,
					अचिन्हित दीर्घ ap, अचिन्हित दीर्घ ric)
अणु
	अचिन्हित दीर्घ rb,rs,prs,r;

	rb = va & ~(PPC_BITMASK(52, 63));
	rb |= ap << PPC_BITLSHIFT(58);
	rs = pid << PPC_BITLSHIFT(31);
	prs = 1; /* process scoped */
	r = 1;   /* radix क्रमmat */

	यंत्र अस्थिर(PPC_TLBIEL(%0, %4, %3, %2, %1)
		     : : "r"(rb), "i"(r), "i"(prs), "i"(ric), "r"(rs) : "memory");
	trace_tlbie(0, 1, rb, rs, ric, prs, r);
पूर्ण

अटल __always_अंतरभूत व्योम __tlbie_va(अचिन्हित दीर्घ va, अचिन्हित दीर्घ pid,
				       अचिन्हित दीर्घ ap, अचिन्हित दीर्घ ric)
अणु
	अचिन्हित दीर्घ rb,rs,prs,r;

	rb = va & ~(PPC_BITMASK(52, 63));
	rb |= ap << PPC_BITLSHIFT(58);
	rs = pid << PPC_BITLSHIFT(31);
	prs = 1; /* process scoped */
	r = 1;   /* radix क्रमmat */

	यंत्र अस्थिर(PPC_TLBIE_5(%0, %4, %3, %2, %1)
		     : : "r"(rb), "i"(r), "i"(prs), "i"(ric), "r"(rs) : "memory");
	trace_tlbie(0, 0, rb, rs, ric, prs, r);
पूर्ण

अटल __always_अंतरभूत व्योम __tlbie_lpid_va(अचिन्हित दीर्घ va, अचिन्हित दीर्घ lpid,
					    अचिन्हित दीर्घ ap, अचिन्हित दीर्घ ric)
अणु
	अचिन्हित दीर्घ rb,rs,prs,r;

	rb = va & ~(PPC_BITMASK(52, 63));
	rb |= ap << PPC_BITLSHIFT(58);
	rs = lpid;
	prs = 0; /* partition scoped */
	r = 1;   /* radix क्रमmat */

	यंत्र अस्थिर(PPC_TLBIE_5(%0, %4, %3, %2, %1)
		     : : "r"(rb), "i"(r), "i"(prs), "i"(ric), "r"(rs) : "memory");
	trace_tlbie(lpid, 0, rb, rs, ric, prs, r);
पूर्ण


अटल अंतरभूत व्योम fixup_tlbie_va(अचिन्हित दीर्घ va, अचिन्हित दीर्घ pid,
				  अचिन्हित दीर्घ ap)
अणु
	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_ERAT_BUG)) अणु
		यंत्र अस्थिर("ptesync": : :"memory");
		__tlbie_va(va, 0, ap, RIC_FLUSH_TLB);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_STQ_BUG)) अणु
		यंत्र अस्थिर("ptesync": : :"memory");
		__tlbie_va(va, pid, ap, RIC_FLUSH_TLB);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fixup_tlbie_va_range(अचिन्हित दीर्घ va, अचिन्हित दीर्घ pid,
					अचिन्हित दीर्घ ap)
अणु
	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_ERAT_BUG)) अणु
		यंत्र अस्थिर("ptesync": : :"memory");
		__tlbie_pid(0, RIC_FLUSH_TLB);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_STQ_BUG)) अणु
		यंत्र अस्थिर("ptesync": : :"memory");
		__tlbie_va(va, pid, ap, RIC_FLUSH_TLB);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fixup_tlbie_pid(अचिन्हित दीर्घ pid)
अणु
	/*
	 * We can use any address क्रम the invalidation, pick one which is
	 * probably unused as an optimisation.
	 */
	अचिन्हित दीर्घ va = ((1UL << 52) - 1);

	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_ERAT_BUG)) अणु
		यंत्र अस्थिर("ptesync": : :"memory");
		__tlbie_pid(0, RIC_FLUSH_TLB);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_STQ_BUG)) अणु
		यंत्र अस्थिर("ptesync": : :"memory");
		__tlbie_va(va, pid, mmu_get_ap(MMU_PAGE_64K), RIC_FLUSH_TLB);
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम fixup_tlbie_lpid_va(अचिन्हित दीर्घ va, अचिन्हित दीर्घ lpid,
				       अचिन्हित दीर्घ ap)
अणु
	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_ERAT_BUG)) अणु
		यंत्र अस्थिर("ptesync": : :"memory");
		__tlbie_lpid_va(va, 0, ap, RIC_FLUSH_TLB);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_STQ_BUG)) अणु
		यंत्र अस्थिर("ptesync": : :"memory");
		__tlbie_lpid_va(va, lpid, ap, RIC_FLUSH_TLB);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fixup_tlbie_lpid(अचिन्हित दीर्घ lpid)
अणु
	/*
	 * We can use any address क्रम the invalidation, pick one which is
	 * probably unused as an optimisation.
	 */
	अचिन्हित दीर्घ va = ((1UL << 52) - 1);

	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_ERAT_BUG)) अणु
		यंत्र अस्थिर("ptesync": : :"memory");
		__tlbie_lpid(0, RIC_FLUSH_TLB);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_STQ_BUG)) अणु
		यंत्र अस्थिर("ptesync": : :"memory");
		__tlbie_lpid_va(va, lpid, mmu_get_ap(MMU_PAGE_64K), RIC_FLUSH_TLB);
	पूर्ण
पूर्ण

/*
 * We use 128 set in radix mode and 256 set in hpt mode.
 */
अटल __always_अंतरभूत व्योम _tlbiel_pid(अचिन्हित दीर्घ pid, अचिन्हित दीर्घ ric)
अणु
	पूर्णांक set;

	यंत्र अस्थिर("ptesync": : :"memory");

	/*
	 * Flush the first set of the TLB, and अगर we're करोing a RIC_FLUSH_ALL,
	 * also flush the entire Page Walk Cache.
	 */
	__tlbiel_pid(pid, 0, ric);

	/* For PWC, only one flush is needed */
	अगर (ric == RIC_FLUSH_PWC) अणु
		ppc_after_tlbiel_barrier();
		वापस;
	पूर्ण

	अगर (!cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		/* For the reमुख्यing sets, just flush the TLB */
		क्रम (set = 1; set < POWER9_TLB_SETS_RADIX ; set++)
			__tlbiel_pid(pid, set, RIC_FLUSH_TLB);
	पूर्ण

	ppc_after_tlbiel_barrier();
	यंत्र अस्थिर(PPC_RADIX_INVALIDATE_ERAT_USER "; isync" : : :"memory");
पूर्ण

अटल अंतरभूत व्योम _tlbie_pid(अचिन्हित दीर्घ pid, अचिन्हित दीर्घ ric)
अणु
	यंत्र अस्थिर("ptesync": : :"memory");

	/*
	 * Workaround the fact that the "ric" argument to __tlbie_pid
	 * must be a compile-समय contraपूर्णांक to match the "i" स्थिरraपूर्णांक
	 * in the यंत्र statement.
	 */
	चयन (ric) अणु
	हाल RIC_FLUSH_TLB:
		__tlbie_pid(pid, RIC_FLUSH_TLB);
		fixup_tlbie_pid(pid);
		अवरोध;
	हाल RIC_FLUSH_PWC:
		__tlbie_pid(pid, RIC_FLUSH_PWC);
		अवरोध;
	हाल RIC_FLUSH_ALL:
	शेष:
		__tlbie_pid(pid, RIC_FLUSH_ALL);
		fixup_tlbie_pid(pid);
	पूर्ण
	यंत्र अस्थिर("eieio; tlbsync; ptesync": : :"memory");
पूर्ण

काष्ठा tlbiel_pid अणु
	अचिन्हित दीर्घ pid;
	अचिन्हित दीर्घ ric;
पूर्ण;

अटल व्योम करो_tlbiel_pid(व्योम *info)
अणु
	काष्ठा tlbiel_pid *t = info;

	अगर (t->ric == RIC_FLUSH_TLB)
		_tlbiel_pid(t->pid, RIC_FLUSH_TLB);
	अन्यथा अगर (t->ric == RIC_FLUSH_PWC)
		_tlbiel_pid(t->pid, RIC_FLUSH_PWC);
	अन्यथा
		_tlbiel_pid(t->pid, RIC_FLUSH_ALL);
पूर्ण

अटल अंतरभूत व्योम _tlbiel_pid_multicast(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ pid, अचिन्हित दीर्घ ric)
अणु
	काष्ठा cpumask *cpus = mm_cpumask(mm);
	काष्ठा tlbiel_pid t = अणु .pid = pid, .ric = ric पूर्ण;

	on_each_cpu_mask(cpus, करो_tlbiel_pid, &t, 1);
	/*
	 * Always want the CPU translations to be invalidated with tlbiel in
	 * these paths, so जबतक coprocessors must use tlbie, we can not
	 * optimise away the tlbiel component.
	 */
	अगर (atomic_पढ़ो(&mm->context.copros) > 0)
		_tlbie_pid(pid, RIC_FLUSH_ALL);
पूर्ण

अटल अंतरभूत व्योम _tlbie_lpid(अचिन्हित दीर्घ lpid, अचिन्हित दीर्घ ric)
अणु
	यंत्र अस्थिर("ptesync": : :"memory");

	/*
	 * Workaround the fact that the "ric" argument to __tlbie_pid
	 * must be a compile-समय contraपूर्णांक to match the "i" स्थिरraपूर्णांक
	 * in the यंत्र statement.
	 */
	चयन (ric) अणु
	हाल RIC_FLUSH_TLB:
		__tlbie_lpid(lpid, RIC_FLUSH_TLB);
		fixup_tlbie_lpid(lpid);
		अवरोध;
	हाल RIC_FLUSH_PWC:
		__tlbie_lpid(lpid, RIC_FLUSH_PWC);
		अवरोध;
	हाल RIC_FLUSH_ALL:
	शेष:
		__tlbie_lpid(lpid, RIC_FLUSH_ALL);
		fixup_tlbie_lpid(lpid);
	पूर्ण
	यंत्र अस्थिर("eieio; tlbsync; ptesync": : :"memory");
पूर्ण

अटल __always_अंतरभूत व्योम _tlbie_lpid_guest(अचिन्हित दीर्घ lpid, अचिन्हित दीर्घ ric)
अणु
	/*
	 * Workaround the fact that the "ric" argument to __tlbie_pid
	 * must be a compile-समय contraपूर्णांक to match the "i" स्थिरraपूर्णांक
	 * in the यंत्र statement.
	 */
	चयन (ric) अणु
	हाल RIC_FLUSH_TLB:
		__tlbie_lpid_guest(lpid, RIC_FLUSH_TLB);
		अवरोध;
	हाल RIC_FLUSH_PWC:
		__tlbie_lpid_guest(lpid, RIC_FLUSH_PWC);
		अवरोध;
	हाल RIC_FLUSH_ALL:
	शेष:
		__tlbie_lpid_guest(lpid, RIC_FLUSH_ALL);
	पूर्ण
	fixup_tlbie_lpid(lpid);
	यंत्र अस्थिर("eieio; tlbsync; ptesync": : :"memory");
पूर्ण

अटल अंतरभूत व्योम __tlbiel_va_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				    अचिन्हित दीर्घ pid, अचिन्हित दीर्घ page_size,
				    अचिन्हित दीर्घ psize)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ ap = mmu_get_ap(psize);

	क्रम (addr = start; addr < end; addr += page_size)
		__tlbiel_va(addr, pid, ap, RIC_FLUSH_TLB);
पूर्ण

अटल __always_अंतरभूत व्योम _tlbiel_va(अचिन्हित दीर्घ va, अचिन्हित दीर्घ pid,
				       अचिन्हित दीर्घ psize, अचिन्हित दीर्घ ric)
अणु
	अचिन्हित दीर्घ ap = mmu_get_ap(psize);

	यंत्र अस्थिर("ptesync": : :"memory");
	__tlbiel_va(va, pid, ap, ric);
	ppc_after_tlbiel_barrier();
पूर्ण

अटल अंतरभूत व्योम _tlbiel_va_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				    अचिन्हित दीर्घ pid, अचिन्हित दीर्घ page_size,
				    अचिन्हित दीर्घ psize, bool also_pwc)
अणु
	यंत्र अस्थिर("ptesync": : :"memory");
	अगर (also_pwc)
		__tlbiel_pid(pid, 0, RIC_FLUSH_PWC);
	__tlbiel_va_range(start, end, pid, page_size, psize);
	ppc_after_tlbiel_barrier();
पूर्ण

अटल अंतरभूत व्योम __tlbie_va_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				    अचिन्हित दीर्घ pid, अचिन्हित दीर्घ page_size,
				    अचिन्हित दीर्घ psize)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ ap = mmu_get_ap(psize);

	क्रम (addr = start; addr < end; addr += page_size)
		__tlbie_va(addr, pid, ap, RIC_FLUSH_TLB);

	fixup_tlbie_va_range(addr - page_size, pid, ap);
पूर्ण

अटल __always_अंतरभूत व्योम _tlbie_va(अचिन्हित दीर्घ va, अचिन्हित दीर्घ pid,
				      अचिन्हित दीर्घ psize, अचिन्हित दीर्घ ric)
अणु
	अचिन्हित दीर्घ ap = mmu_get_ap(psize);

	यंत्र अस्थिर("ptesync": : :"memory");
	__tlbie_va(va, pid, ap, ric);
	fixup_tlbie_va(va, pid, ap);
	यंत्र अस्थिर("eieio; tlbsync; ptesync": : :"memory");
पूर्ण

काष्ठा tlbiel_va अणु
	अचिन्हित दीर्घ pid;
	अचिन्हित दीर्घ va;
	अचिन्हित दीर्घ psize;
	अचिन्हित दीर्घ ric;
पूर्ण;

अटल व्योम करो_tlbiel_va(व्योम *info)
अणु
	काष्ठा tlbiel_va *t = info;

	अगर (t->ric == RIC_FLUSH_TLB)
		_tlbiel_va(t->va, t->pid, t->psize, RIC_FLUSH_TLB);
	अन्यथा अगर (t->ric == RIC_FLUSH_PWC)
		_tlbiel_va(t->va, t->pid, t->psize, RIC_FLUSH_PWC);
	अन्यथा
		_tlbiel_va(t->va, t->pid, t->psize, RIC_FLUSH_ALL);
पूर्ण

अटल अंतरभूत व्योम _tlbiel_va_multicast(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ va, अचिन्हित दीर्घ pid,
				अचिन्हित दीर्घ psize, अचिन्हित दीर्घ ric)
अणु
	काष्ठा cpumask *cpus = mm_cpumask(mm);
	काष्ठा tlbiel_va t = अणु .va = va, .pid = pid, .psize = psize, .ric = ric पूर्ण;
	on_each_cpu_mask(cpus, करो_tlbiel_va, &t, 1);
	अगर (atomic_पढ़ो(&mm->context.copros) > 0)
		_tlbie_va(va, pid, psize, RIC_FLUSH_TLB);
पूर्ण

काष्ठा tlbiel_va_range अणु
	अचिन्हित दीर्घ pid;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ page_size;
	अचिन्हित दीर्घ psize;
	bool also_pwc;
पूर्ण;

अटल व्योम करो_tlbiel_va_range(व्योम *info)
अणु
	काष्ठा tlbiel_va_range *t = info;

	_tlbiel_va_range(t->start, t->end, t->pid, t->page_size,
				    t->psize, t->also_pwc);
पूर्ण

अटल __always_अंतरभूत व्योम _tlbie_lpid_va(अचिन्हित दीर्घ va, अचिन्हित दीर्घ lpid,
			      अचिन्हित दीर्घ psize, अचिन्हित दीर्घ ric)
अणु
	अचिन्हित दीर्घ ap = mmu_get_ap(psize);

	यंत्र अस्थिर("ptesync": : :"memory");
	__tlbie_lpid_va(va, lpid, ap, ric);
	fixup_tlbie_lpid_va(va, lpid, ap);
	यंत्र अस्थिर("eieio; tlbsync; ptesync": : :"memory");
पूर्ण

अटल अंतरभूत व्योम _tlbie_va_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				    अचिन्हित दीर्घ pid, अचिन्हित दीर्घ page_size,
				    अचिन्हित दीर्घ psize, bool also_pwc)
अणु
	यंत्र अस्थिर("ptesync": : :"memory");
	अगर (also_pwc)
		__tlbie_pid(pid, RIC_FLUSH_PWC);
	__tlbie_va_range(start, end, pid, page_size, psize);
	यंत्र अस्थिर("eieio; tlbsync; ptesync": : :"memory");
पूर्ण

अटल अंतरभूत व्योम _tlbiel_va_range_multicast(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				अचिन्हित दीर्घ pid, अचिन्हित दीर्घ page_size,
				अचिन्हित दीर्घ psize, bool also_pwc)
अणु
	काष्ठा cpumask *cpus = mm_cpumask(mm);
	काष्ठा tlbiel_va_range t = अणु .start = start, .end = end,
				.pid = pid, .page_size = page_size,
				.psize = psize, .also_pwc = also_pwc पूर्ण;

	on_each_cpu_mask(cpus, करो_tlbiel_va_range, &t, 1);
	अगर (atomic_पढ़ो(&mm->context.copros) > 0)
		_tlbie_va_range(start, end, pid, page_size, psize, also_pwc);
पूर्ण

/*
 * Base TLB flushing operations:
 *
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB's
 *  - flush_tlb_page(vma, vmaddr) flushes one page
 *  - flush_tlb_range(vma, start, end) flushes a range of pages
 *  - flush_tlb_kernel_range(start, end) flushes kernel pages
 *
 *  - local_* variants of page and mm only apply to the current
 *    processor
 */
व्योम radix__local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ pid;

	preempt_disable();
	pid = mm->context.id;
	अगर (pid != MMU_NO_CONTEXT)
		_tlbiel_pid(pid, RIC_FLUSH_TLB);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(radix__local_flush_tlb_mm);

#अगर_अघोषित CONFIG_SMP
व्योम radix__local_flush_all_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ pid;

	preempt_disable();
	pid = mm->context.id;
	अगर (pid != MMU_NO_CONTEXT)
		_tlbiel_pid(pid, RIC_FLUSH_ALL);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(radix__local_flush_all_mm);

अटल व्योम __flush_all_mm(काष्ठा mm_काष्ठा *mm, bool fullmm)
अणु
	radix__local_flush_all_mm(mm);
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

व्योम radix__local_flush_tlb_page_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr,
				       पूर्णांक psize)
अणु
	अचिन्हित दीर्घ pid;

	preempt_disable();
	pid = mm->context.id;
	अगर (pid != MMU_NO_CONTEXT)
		_tlbiel_va(vmaddr, pid, psize, RIC_FLUSH_TLB);
	preempt_enable();
पूर्ण

व्योम radix__local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr)
अणु
#अगर_घोषित CONFIG_HUGETLB_PAGE
	/* need the वापस fix क्रम nohash.c */
	अगर (is_vm_hugetlb_page(vma))
		वापस radix__local_flush_hugetlb_page(vma, vmaddr);
#पूर्ण_अगर
	radix__local_flush_tlb_page_psize(vma->vm_mm, vmaddr, mmu_भव_psize);
पूर्ण
EXPORT_SYMBOL(radix__local_flush_tlb_page);

अटल bool mm_needs_flush_escalation(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * P9 nest MMU has issues with the page walk cache
	 * caching PTEs and not flushing them properly when
	 * RIC = 0 क्रम a PID/LPID invalidate
	 */
	अगर (atomic_पढ़ो(&mm->context.copros) > 0)
		वापस true;
	वापस false;
पूर्ण

/*
 * If always_flush is true, then flush even अगर this CPU can't be हटाओd
 * from mm_cpumask.
 */
व्योम निकास_lazy_flush_tlb(काष्ठा mm_काष्ठा *mm, bool always_flush)
अणु
	अचिन्हित दीर्घ pid = mm->context.id;
	पूर्णांक cpu = smp_processor_id();

	/*
	 * A kthपढ़ो could have करोne a mmget_not_zero() after the flushing CPU
	 * checked mm_cpumask, and be in the process of kthपढ़ो_use_mm when
	 * पूर्णांकerrupted here. In that हाल, current->mm will be set to mm,
	 * because kthपढ़ो_use_mm() setting ->mm and चयनing to the mm is
	 * करोne with पूर्णांकerrupts off.
	 */
	अगर (current->mm == mm)
		जाओ out;

	अगर (current->active_mm == mm) अणु
		WARN_ON_ONCE(current->mm != शून्य);
		/* Is a kernel thपढ़ो and is using mm as the lazy tlb */
		mmgrab(&init_mm);
		current->active_mm = &init_mm;
		चयन_mm_irqs_off(mm, &init_mm, current);
		mmdrop(mm);
	पूर्ण

	/*
	 * This IPI may be initiated from any source including those not
	 * running the mm, so there may be a racing IPI that comes after
	 * this one which finds the cpumask alपढ़ोy clear. Check and aव्योम
	 * underflowing the active_cpus count in that हाल. The race should
	 * not otherwise be a problem, but the TLB must be flushed because
	 * that's what the caller expects.
	 */
	अगर (cpumask_test_cpu(cpu, mm_cpumask(mm))) अणु
		atomic_dec(&mm->context.active_cpus);
		cpumask_clear_cpu(cpu, mm_cpumask(mm));
		always_flush = true;
	पूर्ण

out:
	अगर (always_flush)
		_tlbiel_pid(pid, RIC_FLUSH_ALL);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम करो_निकास_flush_lazy_tlb(व्योम *arg)
अणु
	काष्ठा mm_काष्ठा *mm = arg;
	निकास_lazy_flush_tlb(mm, true);
पूर्ण

अटल व्योम निकास_flush_lazy_tlbs(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * Would be nice अगर this was async so it could be run in
	 * parallel with our local flush, but generic code करोes not
	 * give a good API क्रम it. Could extend the generic code or
	 * make a special घातerpc IPI क्रम flushing TLBs.
	 * For now it's not too perक्रमmance critical.
	 */
	smp_call_function_many(mm_cpumask(mm), करो_निकास_flush_lazy_tlb,
				(व्योम *)mm, 1);
पूर्ण

#अन्यथा /* CONFIG_SMP */
अटल अंतरभूत व्योम निकास_flush_lazy_tlbs(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, mm_cpumask_trim_घड़ी);

/*
 * Interval between flushes at which we send out IPIs to check whether the
 * mm_cpumask can be trimmed क्रम the हाल where it's not a single-thपढ़ोed
 * process flushing its own mm. The पूर्णांकent is to reduce the cost of later
 * flushes. Don't want this to be so low that it adds noticable cost to TLB
 * flushing, or so high that it करोesn't help reduce global TLBIEs.
 */
अटल अचिन्हित दीर्घ tlb_mm_cpumask_trim_समयr = 1073;

अटल bool tick_and_test_trim_घड़ी(व्योम)
अणु
	अगर (__this_cpu_inc_वापस(mm_cpumask_trim_घड़ी) ==
			tlb_mm_cpumask_trim_समयr) अणु
		__this_cpu_ग_लिखो(mm_cpumask_trim_घड़ी, 0);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

क्रमागत tlb_flush_type अणु
	FLUSH_TYPE_NONE,
	FLUSH_TYPE_LOCAL,
	FLUSH_TYPE_GLOBAL,
पूर्ण;

अटल क्रमागत tlb_flush_type flush_type_needed(काष्ठा mm_काष्ठा *mm, bool fullmm)
अणु
	पूर्णांक active_cpus = atomic_पढ़ो(&mm->context.active_cpus);
	पूर्णांक cpu = smp_processor_id();

	अगर (active_cpus == 0)
		वापस FLUSH_TYPE_NONE;
	अगर (active_cpus == 1 && cpumask_test_cpu(cpu, mm_cpumask(mm))) अणु
		अगर (current->mm != mm) अणु
			/*
			 * Asynchronous flush sources may trim करोwn to nothing
			 * अगर the process is not running, so occasionally try
			 * to trim.
			 */
			अगर (tick_and_test_trim_घड़ी()) अणु
				निकास_lazy_flush_tlb(mm, true);
				वापस FLUSH_TYPE_NONE;
			पूर्ण
		पूर्ण
		वापस FLUSH_TYPE_LOCAL;
	पूर्ण

	/* Coprocessors require TLBIE to invalidate nMMU. */
	अगर (atomic_पढ़ो(&mm->context.copros) > 0)
		वापस FLUSH_TYPE_GLOBAL;

	/*
	 * In the fullmm हाल there's no poपूर्णांक करोing the निकास_flush_lazy_tlbs
	 * because the mm is being taken करोwn anyway, and a TLBIE tends to
	 * be faster than an IPI+TLBIEL.
	 */
	अगर (fullmm)
		वापस FLUSH_TYPE_GLOBAL;

	/*
	 * If we are running the only thपढ़ो of a single-thपढ़ोed process,
	 * then we should almost always be able to trim off the rest of the
	 * CPU mask (except in the हाल of use_mm() races), so always try
	 * trimming the mask.
	 */
	अगर (atomic_पढ़ो(&mm->mm_users) <= 1 && current->mm == mm) अणु
		निकास_flush_lazy_tlbs(mm);
		/*
		 * use_mm() race could prevent IPIs from being able to clear
		 * the cpumask here, however those users are established
		 * after our first check (and so after the PTEs are हटाओd),
		 * and the TLB still माला_लो flushed by the IPI, so this CPU
		 * will only require a local flush.
		 */
		वापस FLUSH_TYPE_LOCAL;
	पूर्ण

	/*
	 * Occasionally try to trim करोwn the cpumask. It's possible this can
	 * bring the mask to zero, which results in no flush.
	 */
	अगर (tick_and_test_trim_घड़ी()) अणु
		निकास_flush_lazy_tlbs(mm);
		अगर (current->mm == mm)
			वापस FLUSH_TYPE_LOCAL;
		अगर (cpumask_test_cpu(cpu, mm_cpumask(mm)))
			निकास_lazy_flush_tlb(mm, true);
		वापस FLUSH_TYPE_NONE;
	पूर्ण

	वापस FLUSH_TYPE_GLOBAL;
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम radix__flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ pid;
	क्रमागत tlb_flush_type type;

	pid = mm->context.id;
	अगर (unlikely(pid == MMU_NO_CONTEXT))
		वापस;

	preempt_disable();
	/*
	 * Order loads of mm_cpumask (in flush_type_needed) vs previous
	 * stores to clear ptes beक्रमe the invalidate. See barrier in
	 * चयन_mm_irqs_off
	 */
	smp_mb();
	type = flush_type_needed(mm, false);
	अगर (type == FLUSH_TYPE_LOCAL) अणु
		_tlbiel_pid(pid, RIC_FLUSH_TLB);
	पूर्ण अन्यथा अगर (type == FLUSH_TYPE_GLOBAL) अणु
		अगर (!mmu_has_feature(MMU_FTR_GTSE)) अणु
			अचिन्हित दीर्घ tgt = H_RPTI_TARGET_CMMU;

			अगर (atomic_पढ़ो(&mm->context.copros) > 0)
				tgt |= H_RPTI_TARGET_NMMU;
			pseries_rpt_invalidate(pid, tgt, H_RPTI_TYPE_TLB,
					       H_RPTI_PAGE_ALL, 0, -1UL);
		पूर्ण अन्यथा अगर (cputlb_use_tlbie()) अणु
			अगर (mm_needs_flush_escalation(mm))
				_tlbie_pid(pid, RIC_FLUSH_ALL);
			अन्यथा
				_tlbie_pid(pid, RIC_FLUSH_TLB);
		पूर्ण अन्यथा अणु
			_tlbiel_pid_multicast(mm, pid, RIC_FLUSH_TLB);
		पूर्ण
	पूर्ण
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(radix__flush_tlb_mm);

अटल व्योम __flush_all_mm(काष्ठा mm_काष्ठा *mm, bool fullmm)
अणु
	अचिन्हित दीर्घ pid;
	क्रमागत tlb_flush_type type;

	pid = mm->context.id;
	अगर (unlikely(pid == MMU_NO_CONTEXT))
		वापस;

	preempt_disable();
	smp_mb(); /* see radix__flush_tlb_mm */
	type = flush_type_needed(mm, fullmm);
	अगर (type == FLUSH_TYPE_LOCAL) अणु
		_tlbiel_pid(pid, RIC_FLUSH_ALL);
	पूर्ण अन्यथा अगर (type == FLUSH_TYPE_GLOBAL) अणु
		अगर (!mmu_has_feature(MMU_FTR_GTSE)) अणु
			अचिन्हित दीर्घ tgt = H_RPTI_TARGET_CMMU;
			अचिन्हित दीर्घ type = H_RPTI_TYPE_TLB | H_RPTI_TYPE_PWC |
					     H_RPTI_TYPE_PRT;

			अगर (atomic_पढ़ो(&mm->context.copros) > 0)
				tgt |= H_RPTI_TARGET_NMMU;
			pseries_rpt_invalidate(pid, tgt, type,
					       H_RPTI_PAGE_ALL, 0, -1UL);
		पूर्ण अन्यथा अगर (cputlb_use_tlbie())
			_tlbie_pid(pid, RIC_FLUSH_ALL);
		अन्यथा
			_tlbiel_pid_multicast(mm, pid, RIC_FLUSH_ALL);
	पूर्ण
	preempt_enable();
पूर्ण

व्योम radix__flush_all_mm(काष्ठा mm_काष्ठा *mm)
अणु
	__flush_all_mm(mm, false);
पूर्ण
EXPORT_SYMBOL(radix__flush_all_mm);

व्योम radix__flush_tlb_page_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr,
				 पूर्णांक psize)
अणु
	अचिन्हित दीर्घ pid;
	क्रमागत tlb_flush_type type;

	pid = mm->context.id;
	अगर (unlikely(pid == MMU_NO_CONTEXT))
		वापस;

	preempt_disable();
	smp_mb(); /* see radix__flush_tlb_mm */
	type = flush_type_needed(mm, false);
	अगर (type == FLUSH_TYPE_LOCAL) अणु
		_tlbiel_va(vmaddr, pid, psize, RIC_FLUSH_TLB);
	पूर्ण अन्यथा अगर (type == FLUSH_TYPE_GLOBAL) अणु
		अगर (!mmu_has_feature(MMU_FTR_GTSE)) अणु
			अचिन्हित दीर्घ tgt, pg_sizes, size;

			tgt = H_RPTI_TARGET_CMMU;
			pg_sizes = pमाप_प्रकारo_rpti_pgsize(psize);
			size = 1UL << mmu_pमाप_प्रकारo_shअगरt(psize);

			अगर (atomic_पढ़ो(&mm->context.copros) > 0)
				tgt |= H_RPTI_TARGET_NMMU;
			pseries_rpt_invalidate(pid, tgt, H_RPTI_TYPE_TLB,
					       pg_sizes, vmaddr,
					       vmaddr + size);
		पूर्ण अन्यथा अगर (cputlb_use_tlbie())
			_tlbie_va(vmaddr, pid, psize, RIC_FLUSH_TLB);
		अन्यथा
			_tlbiel_va_multicast(mm, vmaddr, pid, psize, RIC_FLUSH_TLB);
	पूर्ण
	preempt_enable();
पूर्ण

व्योम radix__flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr)
अणु
#अगर_घोषित CONFIG_HUGETLB_PAGE
	अगर (is_vm_hugetlb_page(vma))
		वापस radix__flush_hugetlb_page(vma, vmaddr);
#पूर्ण_अगर
	radix__flush_tlb_page_psize(vma->vm_mm, vmaddr, mmu_भव_psize);
पूर्ण
EXPORT_SYMBOL(radix__flush_tlb_page);

#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम करो_tlbiel_kernel(व्योम *info)
अणु
	_tlbiel_pid(0, RIC_FLUSH_ALL);
पूर्ण

अटल अंतरभूत व्योम _tlbiel_kernel_broadcast(व्योम)
अणु
	on_each_cpu(करो_tlbiel_kernel, शून्य, 1);
	अगर (tlbie_capable) अणु
		/*
		 * Coherent accelerators करोn't refcount kernel memory mappings,
		 * so have to always issue a tlbie क्रम them. This is quite a
		 * slow path anyway.
		 */
		_tlbie_pid(0, RIC_FLUSH_ALL);
	पूर्ण
पूर्ण

/*
 * If kernel TLBIs ever become local rather than global, then
 * drivers/misc/ocxl/link.c:ocxl_link_add_pe will need some work, as it
 * assumes kernel TLBIs are global.
 */
व्योम radix__flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (!mmu_has_feature(MMU_FTR_GTSE)) अणु
		अचिन्हित दीर्घ tgt = H_RPTI_TARGET_CMMU | H_RPTI_TARGET_NMMU;
		अचिन्हित दीर्घ type = H_RPTI_TYPE_TLB | H_RPTI_TYPE_PWC |
				     H_RPTI_TYPE_PRT;

		pseries_rpt_invalidate(0, tgt, type, H_RPTI_PAGE_ALL,
				       start, end);
	पूर्ण अन्यथा अगर (cputlb_use_tlbie())
		_tlbie_pid(0, RIC_FLUSH_ALL);
	अन्यथा
		_tlbiel_kernel_broadcast();
पूर्ण
EXPORT_SYMBOL(radix__flush_tlb_kernel_range);

#घोषणा TLB_FLUSH_ALL -1UL

/*
 * Number of pages above which we invalidate the entire PID rather than
 * flush inभागidual pages, क्रम local and global flushes respectively.
 *
 * tlbie goes out to the पूर्णांकerconnect and inभागidual ops are more costly.
 * It also करोes not iterate over sets like the local tlbiel variant when
 * invalidating a full PID, so it has a far lower threshold to change from
 * inभागidual page flushes to full-pid flushes.
 */
अटल अचिन्हित दीर्घ tlb_single_page_flush_उच्चमानing __पढ़ो_mostly = 33;
अटल अचिन्हित दीर्घ tlb_local_single_page_flush_उच्चमानing __पढ़ो_mostly = POWER9_TLB_SETS_RADIX * 2;

अटल अंतरभूत व्योम __radix__flush_tlb_range(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)

अणु
	अचिन्हित दीर्घ pid;
	अचिन्हित पूर्णांक page_shअगरt = mmu_psize_defs[mmu_भव_psize].shअगरt;
	अचिन्हित दीर्घ page_size = 1UL << page_shअगरt;
	अचिन्हित दीर्घ nr_pages = (end - start) >> page_shअगरt;
	bool fullmm = (end == TLB_FLUSH_ALL);
	bool flush_pid;
	क्रमागत tlb_flush_type type;

	pid = mm->context.id;
	अगर (unlikely(pid == MMU_NO_CONTEXT))
		वापस;

	preempt_disable();
	smp_mb(); /* see radix__flush_tlb_mm */
	type = flush_type_needed(mm, fullmm);
	अगर (type == FLUSH_TYPE_NONE)
		जाओ out;

	अगर (fullmm)
		flush_pid = true;
	अन्यथा अगर (type == FLUSH_TYPE_GLOBAL)
		flush_pid = nr_pages > tlb_single_page_flush_उच्चमानing;
	अन्यथा
		flush_pid = nr_pages > tlb_local_single_page_flush_उच्चमानing;

	अगर (!mmu_has_feature(MMU_FTR_GTSE) && type == FLUSH_TYPE_GLOBAL) अणु
		अचिन्हित दीर्घ tgt = H_RPTI_TARGET_CMMU;
		अचिन्हित दीर्घ pg_sizes = pमाप_प्रकारo_rpti_pgsize(mmu_भव_psize);

		अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE))
			pg_sizes |= pमाप_प्रकारo_rpti_pgsize(MMU_PAGE_2M);
		अगर (atomic_पढ़ो(&mm->context.copros) > 0)
			tgt |= H_RPTI_TARGET_NMMU;
		pseries_rpt_invalidate(pid, tgt, H_RPTI_TYPE_TLB, pg_sizes,
				       start, end);
	पूर्ण अन्यथा अगर (flush_pid) अणु
		अगर (type == FLUSH_TYPE_LOCAL) अणु
			_tlbiel_pid(pid, RIC_FLUSH_TLB);
		पूर्ण अन्यथा अणु
			अगर (cputlb_use_tlbie()) अणु
				अगर (mm_needs_flush_escalation(mm))
					_tlbie_pid(pid, RIC_FLUSH_ALL);
				अन्यथा
					_tlbie_pid(pid, RIC_FLUSH_TLB);
			पूर्ण अन्यथा अणु
				_tlbiel_pid_multicast(mm, pid, RIC_FLUSH_TLB);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		bool hflush = false;
		अचिन्हित दीर्घ hstart, hend;

		अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE)) अणु
			hstart = (start + PMD_SIZE - 1) & PMD_MASK;
			hend = end & PMD_MASK;
			अगर (hstart < hend)
				hflush = true;
		पूर्ण

		अगर (type == FLUSH_TYPE_LOCAL) अणु
			यंत्र अस्थिर("ptesync": : :"memory");
			__tlbiel_va_range(start, end, pid, page_size, mmu_भव_psize);
			अगर (hflush)
				__tlbiel_va_range(hstart, hend, pid,
						PMD_SIZE, MMU_PAGE_2M);
			ppc_after_tlbiel_barrier();
		पूर्ण अन्यथा अगर (cputlb_use_tlbie()) अणु
			यंत्र अस्थिर("ptesync": : :"memory");
			__tlbie_va_range(start, end, pid, page_size, mmu_भव_psize);
			अगर (hflush)
				__tlbie_va_range(hstart, hend, pid,
						PMD_SIZE, MMU_PAGE_2M);
			यंत्र अस्थिर("eieio; tlbsync; ptesync": : :"memory");
		पूर्ण अन्यथा अणु
			_tlbiel_va_range_multicast(mm,
					start, end, pid, page_size, mmu_भव_psize, false);
			अगर (hflush)
				_tlbiel_va_range_multicast(mm,
					hstart, hend, pid, PMD_SIZE, MMU_PAGE_2M, false);
		पूर्ण
	पूर्ण
out:
	preempt_enable();
पूर्ण

व्योम radix__flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		     अचिन्हित दीर्घ end)

अणु
#अगर_घोषित CONFIG_HUGETLB_PAGE
	अगर (is_vm_hugetlb_page(vma))
		वापस radix__flush_hugetlb_tlb_range(vma, start, end);
#पूर्ण_अगर

	__radix__flush_tlb_range(vma->vm_mm, start, end);
पूर्ण
EXPORT_SYMBOL(radix__flush_tlb_range);

अटल पूर्णांक radix_get_mmu_psize(पूर्णांक page_size)
अणु
	पूर्णांक psize;

	अगर (page_size == (1UL << mmu_psize_defs[mmu_भव_psize].shअगरt))
		psize = mmu_भव_psize;
	अन्यथा अगर (page_size == (1UL << mmu_psize_defs[MMU_PAGE_2M].shअगरt))
		psize = MMU_PAGE_2M;
	अन्यथा अगर (page_size == (1UL << mmu_psize_defs[MMU_PAGE_1G].shअगरt))
		psize = MMU_PAGE_1G;
	अन्यथा
		वापस -1;
	वापस psize;
पूर्ण

/*
 * Flush partition scoped LPID address translation क्रम all CPUs.
 */
व्योम radix__flush_tlb_lpid_page(अचिन्हित पूर्णांक lpid,
					अचिन्हित दीर्घ addr,
					अचिन्हित दीर्घ page_size)
अणु
	पूर्णांक psize = radix_get_mmu_psize(page_size);

	_tlbie_lpid_va(addr, lpid, psize, RIC_FLUSH_TLB);
पूर्ण
EXPORT_SYMBOL_GPL(radix__flush_tlb_lpid_page);

/*
 * Flush partition scoped PWC from LPID क्रम all CPUs.
 */
व्योम radix__flush_pwc_lpid(अचिन्हित पूर्णांक lpid)
अणु
	_tlbie_lpid(lpid, RIC_FLUSH_PWC);
पूर्ण
EXPORT_SYMBOL_GPL(radix__flush_pwc_lpid);

/*
 * Flush partition scoped translations from LPID (=LPIDR)
 */
व्योम radix__flush_all_lpid(अचिन्हित पूर्णांक lpid)
अणु
	_tlbie_lpid(lpid, RIC_FLUSH_ALL);
पूर्ण
EXPORT_SYMBOL_GPL(radix__flush_all_lpid);

/*
 * Flush process scoped translations from LPID (=LPIDR)
 */
व्योम radix__flush_all_lpid_guest(अचिन्हित पूर्णांक lpid)
अणु
	_tlbie_lpid_guest(lpid, RIC_FLUSH_ALL);
पूर्ण

अटल व्योम radix__flush_tlb_pwc_range_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ end, पूर्णांक psize);

व्योम radix__tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	पूर्णांक psize = 0;
	काष्ठा mm_काष्ठा *mm = tlb->mm;
	पूर्णांक page_size = tlb->page_size;
	अचिन्हित दीर्घ start = tlb->start;
	अचिन्हित दीर्घ end = tlb->end;

	/*
	 * अगर page size is not something we understand, करो a full mm flush
	 *
	 * A "fullmm" flush must always करो a flush_all_mm (RIC=2) flush
	 * that flushes the process table entry cache upon process tearकरोwn.
	 * See the comment क्रम radix in arch_निकास_mmap().
	 */
	अगर (tlb->fullmm || tlb->need_flush_all) अणु
		__flush_all_mm(mm, true);
	पूर्ण अन्यथा अगर ( (psize = radix_get_mmu_psize(page_size)) == -1) अणु
		अगर (!tlb->मुक्तd_tables)
			radix__flush_tlb_mm(mm);
		अन्यथा
			radix__flush_all_mm(mm);
	पूर्ण अन्यथा अणु
		अगर (!tlb->मुक्तd_tables)
			radix__flush_tlb_range_psize(mm, start, end, psize);
		अन्यथा
			radix__flush_tlb_pwc_range_psize(mm, start, end, psize);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम __radix__flush_tlb_range_psize(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				पूर्णांक psize, bool also_pwc)
अणु
	अचिन्हित दीर्घ pid;
	अचिन्हित पूर्णांक page_shअगरt = mmu_psize_defs[psize].shअगरt;
	अचिन्हित दीर्घ page_size = 1UL << page_shअगरt;
	अचिन्हित दीर्घ nr_pages = (end - start) >> page_shअगरt;
	bool fullmm = (end == TLB_FLUSH_ALL);
	bool flush_pid;
	क्रमागत tlb_flush_type type;

	pid = mm->context.id;
	अगर (unlikely(pid == MMU_NO_CONTEXT))
		वापस;

	fullmm = (end == TLB_FLUSH_ALL);

	preempt_disable();
	smp_mb(); /* see radix__flush_tlb_mm */
	type = flush_type_needed(mm, fullmm);
	अगर (type == FLUSH_TYPE_NONE)
		जाओ out;

	अगर (fullmm)
		flush_pid = true;
	अन्यथा अगर (type == FLUSH_TYPE_GLOBAL)
		flush_pid = nr_pages > tlb_single_page_flush_उच्चमानing;
	अन्यथा
		flush_pid = nr_pages > tlb_local_single_page_flush_उच्चमानing;

	अगर (!mmu_has_feature(MMU_FTR_GTSE) && type == FLUSH_TYPE_GLOBAL) अणु
		अचिन्हित दीर्घ tgt = H_RPTI_TARGET_CMMU;
		अचिन्हित दीर्घ type = H_RPTI_TYPE_TLB;
		अचिन्हित दीर्घ pg_sizes = pमाप_प्रकारo_rpti_pgsize(psize);

		अगर (also_pwc)
			type |= H_RPTI_TYPE_PWC;
		अगर (atomic_पढ़ो(&mm->context.copros) > 0)
			tgt |= H_RPTI_TARGET_NMMU;
		pseries_rpt_invalidate(pid, tgt, type, pg_sizes, start, end);
	पूर्ण अन्यथा अगर (flush_pid) अणु
		अगर (type == FLUSH_TYPE_LOCAL) अणु
			_tlbiel_pid(pid, also_pwc ? RIC_FLUSH_ALL : RIC_FLUSH_TLB);
		पूर्ण अन्यथा अणु
			अगर (cputlb_use_tlbie()) अणु
				अगर (mm_needs_flush_escalation(mm))
					also_pwc = true;

				_tlbie_pid(pid,
					also_pwc ?  RIC_FLUSH_ALL : RIC_FLUSH_TLB);
			पूर्ण अन्यथा अणु
				_tlbiel_pid_multicast(mm, pid,
					also_pwc ?  RIC_FLUSH_ALL : RIC_FLUSH_TLB);
			पूर्ण

		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (type == FLUSH_TYPE_LOCAL)
			_tlbiel_va_range(start, end, pid, page_size, psize, also_pwc);
		अन्यथा अगर (cputlb_use_tlbie())
			_tlbie_va_range(start, end, pid, page_size, psize, also_pwc);
		अन्यथा
			_tlbiel_va_range_multicast(mm,
					start, end, pid, page_size, psize, also_pwc);
	पूर्ण
out:
	preempt_enable();
पूर्ण

व्योम radix__flush_tlb_range_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ end, पूर्णांक psize)
अणु
	वापस __radix__flush_tlb_range_psize(mm, start, end, psize, false);
पूर्ण

अटल व्योम radix__flush_tlb_pwc_range_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ end, पूर्णांक psize)
अणु
	__radix__flush_tlb_range_psize(mm, start, end, psize, true);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
व्योम radix__flush_tlb_collapsed_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ pid, end;
	क्रमागत tlb_flush_type type;

	pid = mm->context.id;
	अगर (unlikely(pid == MMU_NO_CONTEXT))
		वापस;

	/* 4k page size, just blow the world */
	अगर (PAGE_SIZE == 0x1000) अणु
		radix__flush_all_mm(mm);
		वापस;
	पूर्ण

	end = addr + HPAGE_PMD_SIZE;

	/* Otherwise first करो the PWC, then iterate the pages. */
	preempt_disable();
	smp_mb(); /* see radix__flush_tlb_mm */
	type = flush_type_needed(mm, false);
	अगर (type == FLUSH_TYPE_LOCAL) अणु
		_tlbiel_va_range(addr, end, pid, PAGE_SIZE, mmu_भव_psize, true);
	पूर्ण अन्यथा अगर (type == FLUSH_TYPE_GLOBAL) अणु
		अगर (!mmu_has_feature(MMU_FTR_GTSE)) अणु
			अचिन्हित दीर्घ tgt, type, pg_sizes;

			tgt = H_RPTI_TARGET_CMMU;
			type = H_RPTI_TYPE_TLB | H_RPTI_TYPE_PWC |
			       H_RPTI_TYPE_PRT;
			pg_sizes = pमाप_प्रकारo_rpti_pgsize(mmu_भव_psize);

			अगर (atomic_पढ़ो(&mm->context.copros) > 0)
				tgt |= H_RPTI_TARGET_NMMU;
			pseries_rpt_invalidate(pid, tgt, type, pg_sizes,
					       addr, end);
		पूर्ण अन्यथा अगर (cputlb_use_tlbie())
			_tlbie_va_range(addr, end, pid, PAGE_SIZE, mmu_भव_psize, true);
		अन्यथा
			_tlbiel_va_range_multicast(mm,
					addr, end, pid, PAGE_SIZE, mmu_भव_psize, true);
	पूर्ण

	preempt_enable();
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

व्योम radix__flush_pmd_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	radix__flush_tlb_range_psize(vma->vm_mm, start, end, MMU_PAGE_2M);
पूर्ण
EXPORT_SYMBOL(radix__flush_pmd_tlb_range);

व्योम radix__flush_tlb_all(व्योम)
अणु
	अचिन्हित दीर्घ rb,prs,r,rs;
	अचिन्हित दीर्घ ric = RIC_FLUSH_ALL;

	rb = 0x3 << PPC_BITLSHIFT(53); /* IS = 3 */
	prs = 0; /* partition scoped */
	r = 1;   /* radix क्रमmat */
	rs = 1 & ((1UL << 32) - 1); /* any LPID value to flush guest mappings */

	यंत्र अस्थिर("ptesync": : :"memory");
	/*
	 * now flush guest entries by passing PRS = 1 and LPID != 0
	 */
	यंत्र अस्थिर(PPC_TLBIE_5(%0, %4, %3, %2, %1)
		     : : "r"(rb), "i"(r), "i"(1), "i"(ric), "r"(rs) : "memory");
	/*
	 * now flush host entires by passing PRS = 0 and LPID == 0
	 */
	यंत्र अस्थिर(PPC_TLBIE_5(%0, %4, %3, %2, %1)
		     : : "r"(rb), "i"(r), "i"(prs), "i"(ric), "r"(0) : "memory");
	यंत्र अस्थिर("eieio; tlbsync; ptesync": : :"memory");
पूर्ण

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
बाह्य व्योम radix_kvm_prefetch_workaround(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ pid = mm->context.id;

	अगर (unlikely(pid == MMU_NO_CONTEXT))
		वापस;

	अगर (!cpu_has_feature(CPU_FTR_P9_RADIX_PREFETCH_BUG))
		वापस;

	/*
	 * If this context hasn't run on that CPU beक्रमe and KVM is
	 * around, there's a slim chance that the guest on another
	 * CPU just brought in obsolete translation पूर्णांकo the TLB of
	 * this CPU due to a bad prefetch using the guest PID on
	 * the way पूर्णांकo the hypervisor.
	 *
	 * We work around this here. If KVM is possible, we check अगर
	 * any sibling thपढ़ो is in KVM. If it is, the winकरोw may exist
	 * and thus we flush that PID from the core.
	 *
	 * A potential future improvement would be to mark which PIDs
	 * have never been used on the प्रणाली and aव्योम it अगर the PID
	 * is new and the process has no other cpumask bit set.
	 */
	अगर (cpu_has_feature(CPU_FTR_HVMODE) && radix_enabled()) अणु
		पूर्णांक cpu = smp_processor_id();
		पूर्णांक sib = cpu_first_thपढ़ो_sibling(cpu);
		bool flush = false;

		क्रम (; sib <= cpu_last_thपढ़ो_sibling(cpu) && !flush; sib++) अणु
			अगर (sib == cpu)
				जारी;
			अगर (!cpu_possible(sib))
				जारी;
			अगर (paca_ptrs[sib]->kvm_hstate.kvm_vcpu)
				flush = true;
		पूर्ण
		अगर (flush)
			_tlbiel_pid(pid, RIC_FLUSH_ALL);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(radix_kvm_prefetch_workaround);
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */
