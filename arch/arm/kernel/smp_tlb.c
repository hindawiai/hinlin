<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/smp_tlb.c
 *
 *  Copyright (C) 2002 ARM Limited, All Rights Reserved.
 */
#समावेश <linux/preempt.h>
#समावेश <linux/smp.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>

/**********************************************************************/

/*
 * TLB operations
 */
काष्ठा tlb_args अणु
	काष्ठा vm_area_काष्ठा *ta_vma;
	अचिन्हित दीर्घ ta_start;
	अचिन्हित दीर्घ ta_end;
पूर्ण;

अटल अंतरभूत व्योम ipi_flush_tlb_all(व्योम *ignored)
अणु
	local_flush_tlb_all();
पूर्ण

अटल अंतरभूत व्योम ipi_flush_tlb_mm(व्योम *arg)
अणु
	काष्ठा mm_काष्ठा *mm = (काष्ठा mm_काष्ठा *)arg;

	local_flush_tlb_mm(mm);
पूर्ण

अटल अंतरभूत व्योम ipi_flush_tlb_page(व्योम *arg)
अणु
	काष्ठा tlb_args *ta = (काष्ठा tlb_args *)arg;
	अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();

	local_flush_tlb_page(ta->ta_vma, ta->ta_start);

	uaccess_restore(__ua_flags);
पूर्ण

अटल अंतरभूत व्योम ipi_flush_tlb_kernel_page(व्योम *arg)
अणु
	काष्ठा tlb_args *ta = (काष्ठा tlb_args *)arg;

	local_flush_tlb_kernel_page(ta->ta_start);
पूर्ण

अटल अंतरभूत व्योम ipi_flush_tlb_range(व्योम *arg)
अणु
	काष्ठा tlb_args *ta = (काष्ठा tlb_args *)arg;
	अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();

	local_flush_tlb_range(ta->ta_vma, ta->ta_start, ta->ta_end);

	uaccess_restore(__ua_flags);
पूर्ण

अटल अंतरभूत व्योम ipi_flush_tlb_kernel_range(व्योम *arg)
अणु
	काष्ठा tlb_args *ta = (काष्ठा tlb_args *)arg;

	local_flush_tlb_kernel_range(ta->ta_start, ta->ta_end);
पूर्ण

अटल अंतरभूत व्योम ipi_flush_bp_all(व्योम *ignored)
अणु
	local_flush_bp_all();
पूर्ण

#अगर_घोषित CONFIG_ARM_ERRATA_798181
bool (*erratum_a15_798181_handler)(व्योम);

अटल bool erratum_a15_798181_partial(व्योम)
अणु
	यंत्र("mcr p15, 0, %0, c8, c3, 1" : : "r" (0));
	dsb(ish);
	वापस false;
पूर्ण

अटल bool erratum_a15_798181_broadcast(व्योम)
अणु
	यंत्र("mcr p15, 0, %0, c8, c3, 1" : : "r" (0));
	dsb(ish);
	वापस true;
पूर्ण

व्योम erratum_a15_798181_init(व्योम)
अणु
	अचिन्हित पूर्णांक midr = पढ़ो_cpuid_id();
	अचिन्हित पूर्णांक revidr = पढ़ो_cpuid(CPUID_REVIDR);

	/* Brahma-B15 r0p0..r0p2 affected
	 * Cortex-A15 r0p0..r3p3 w/o ECO fix affected
	 * Fixes applied to A15 with respect to the revision and revidr are:
	 *
	 * r0p0-r2p1: No fixes applied
	 * r2p2,r2p3:
	 *	REVIDR[4]: 798181 Moving a भव page that is being accessed
	 *		   by an active process can lead to unexpected behavior
	 *	REVIDR[9]: Not defined
	 * r2p4,r3p0,r3p1,r3p2:
	 *	REVIDR[4]: 798181 Moving a भव page that is being accessed
	 *		   by an active process can lead to unexpected behavior
	 *	REVIDR[9]: 798181 Moving a भव page that is being accessed
	 *		   by an active process can lead to unexpected behavior
	 *		   - This is an update to a previously released ECO.
	 * r3p3:
	 *	REVIDR[4]: Reserved
	 *	REVIDR[9]: 798181 Moving a भव page that is being accessed
	 *		   by an active process can lead to unexpected behavior
	 *		   - This is an update to a previously released ECO.
	 *
	 * Handling:
	 *	REVIDR[9] set -> No WA
	 *	REVIDR[4] set, REVIDR[9] cleared -> Partial WA
	 *	Both cleared -> Full WA
	 */
	अगर ((midr & 0xff0ffff0) == 0x420f00f0 && midr <= 0x420f00f2) अणु
		erratum_a15_798181_handler = erratum_a15_798181_broadcast;
	पूर्ण अन्यथा अगर ((midr & 0xff0ffff0) == 0x410fc0f0 && midr < 0x412fc0f2) अणु
		erratum_a15_798181_handler = erratum_a15_798181_broadcast;
	पूर्ण अन्यथा अगर ((midr & 0xff0ffff0) == 0x410fc0f0 && midr < 0x412fc0f4) अणु
		अगर (revidr & 0x10)
			erratum_a15_798181_handler =
				erratum_a15_798181_partial;
		अन्यथा
			erratum_a15_798181_handler =
				erratum_a15_798181_broadcast;
	पूर्ण अन्यथा अगर ((midr & 0xff0ffff0) == 0x410fc0f0 && midr < 0x413fc0f3) अणु
		अगर ((revidr & 0x210) == 0)
			erratum_a15_798181_handler =
				erratum_a15_798181_broadcast;
		अन्यथा अगर (revidr & 0x10)
			erratum_a15_798181_handler =
				erratum_a15_798181_partial;
	पूर्ण अन्यथा अगर ((midr & 0xff0ffff0) == 0x410fc0f0 && midr < 0x414fc0f0) अणु
		अगर ((revidr & 0x200) == 0)
			erratum_a15_798181_handler =
				erratum_a15_798181_partial;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम ipi_flush_tlb_a15_erratum(व्योम *arg)
अणु
	dmb();
पूर्ण

अटल व्योम broadcast_tlb_a15_erratum(व्योम)
अणु
	अगर (!erratum_a15_798181())
		वापस;

	smp_call_function(ipi_flush_tlb_a15_erratum, शून्य, 1);
पूर्ण

अटल व्योम broadcast_tlb_mm_a15_erratum(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक this_cpu;
	cpumask_t mask = अणु CPU_BITS_NONE पूर्ण;

	अगर (!erratum_a15_798181())
		वापस;

	this_cpu = get_cpu();
	a15_erratum_get_cpumask(this_cpu, mm, &mask);
	smp_call_function_many(&mask, ipi_flush_tlb_a15_erratum, शून्य, 1);
	put_cpu();
पूर्ण

व्योम flush_tlb_all(व्योम)
अणु
	अगर (tlb_ops_need_broadcast())
		on_each_cpu(ipi_flush_tlb_all, शून्य, 1);
	अन्यथा
		__flush_tlb_all();
	broadcast_tlb_a15_erratum();
पूर्ण

व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (tlb_ops_need_broadcast())
		on_each_cpu_mask(mm_cpumask(mm), ipi_flush_tlb_mm, mm, 1);
	अन्यथा
		__flush_tlb_mm(mm);
	broadcast_tlb_mm_a15_erratum(mm);
पूर्ण

व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ uaddr)
अणु
	अगर (tlb_ops_need_broadcast()) अणु
		काष्ठा tlb_args ta;
		ta.ta_vma = vma;
		ta.ta_start = uaddr;
		on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_flush_tlb_page,
					&ta, 1);
	पूर्ण अन्यथा
		__flush_tlb_page(vma, uaddr);
	broadcast_tlb_mm_a15_erratum(vma->vm_mm);
पूर्ण

व्योम flush_tlb_kernel_page(अचिन्हित दीर्घ kaddr)
अणु
	अगर (tlb_ops_need_broadcast()) अणु
		काष्ठा tlb_args ta;
		ta.ta_start = kaddr;
		on_each_cpu(ipi_flush_tlb_kernel_page, &ta, 1);
	पूर्ण अन्यथा
		__flush_tlb_kernel_page(kaddr);
	broadcast_tlb_a15_erratum();
पूर्ण

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
                     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (tlb_ops_need_broadcast()) अणु
		काष्ठा tlb_args ta;
		ta.ta_vma = vma;
		ta.ta_start = start;
		ta.ta_end = end;
		on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_flush_tlb_range,
					&ta, 1);
	पूर्ण अन्यथा
		local_flush_tlb_range(vma, start, end);
	broadcast_tlb_mm_a15_erratum(vma->vm_mm);
पूर्ण

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (tlb_ops_need_broadcast()) अणु
		काष्ठा tlb_args ta;
		ta.ta_start = start;
		ta.ta_end = end;
		on_each_cpu(ipi_flush_tlb_kernel_range, &ta, 1);
	पूर्ण अन्यथा
		local_flush_tlb_kernel_range(start, end);
	broadcast_tlb_a15_erratum();
पूर्ण

व्योम flush_bp_all(व्योम)
अणु
	अगर (tlb_ops_need_broadcast())
		on_each_cpu(ipi_flush_bp_all, शून्य, 1);
	अन्यथा
		__flush_bp_all();
पूर्ण
