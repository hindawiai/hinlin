<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/sbi.h>

व्योम flush_tlb_all(व्योम)
अणु
	sbi_remote_sfence_vma(शून्य, 0, -1);
पूर्ण

/*
 * This function must not be called with cmask being null.
 * Kernel may panic अगर cmask is शून्य.
 */
अटल व्योम __sbi_tlb_flush_range(काष्ठा cpumask *cmask, अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ size)
अणु
	काष्ठा cpumask hmask;
	अचिन्हित पूर्णांक cpuid;

	अगर (cpumask_empty(cmask))
		वापस;

	cpuid = get_cpu();

	अगर (cpumask_any_but(cmask, cpuid) >= nr_cpu_ids) अणु
		/* local cpu is the only cpu present in cpumask */
		अगर (size <= PAGE_SIZE)
			local_flush_tlb_page(start);
		अन्यथा
			local_flush_tlb_all();
	पूर्ण अन्यथा अणु
		riscv_cpuid_to_hartid_mask(cmask, &hmask);
		sbi_remote_sfence_vma(cpumask_bits(&hmask), start, size);
	पूर्ण

	put_cpu();
पूर्ण

व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	__sbi_tlb_flush_range(mm_cpumask(mm), 0, -1);
पूर्ण

व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	__sbi_tlb_flush_range(mm_cpumask(vma->vm_mm), addr, PAGE_SIZE);
पूर्ण

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		     अचिन्हित दीर्घ end)
अणु
	__sbi_tlb_flush_range(mm_cpumask(vma->vm_mm), start, end - start);
पूर्ण
