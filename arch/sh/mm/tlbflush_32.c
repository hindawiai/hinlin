<शैली गुरु>
/*
 * TLB flushing operations क्रम SH with an MMU.
 *
 *  Copyright (C) 1999  Niibe Yutaka
 *  Copyright (C) 2003  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/mm.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>

व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर (vma->vm_mm && cpu_context(cpu, vma->vm_mm) != NO_CONTEXT) अणु
		अचिन्हित दीर्घ flags;
		अचिन्हित दीर्घ asid;
		अचिन्हित दीर्घ saved_asid = MMU_NO_ASID;

		asid = cpu_asid(cpu, vma->vm_mm);
		page &= PAGE_MASK;

		local_irq_save(flags);
		अगर (vma->vm_mm != current->mm) अणु
			saved_asid = get_asid();
			set_asid(asid);
		पूर्ण
		local_flush_tlb_one(asid, page);
		अगर (saved_asid != MMU_NO_ASID)
			set_asid(saved_asid);
		local_irq_restore(flags);
	पूर्ण
पूर्ण

व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर (cpu_context(cpu, mm) != NO_CONTEXT) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक size;

		local_irq_save(flags);
		size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
		अगर (size > (MMU_NTLB_ENTRIES/4)) अणु /* Too many TLB to flush */
			cpu_context(cpu, mm) = NO_CONTEXT;
			अगर (mm == current->mm)
				activate_context(mm, cpu);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ asid;
			अचिन्हित दीर्घ saved_asid = MMU_NO_ASID;

			asid = cpu_asid(cpu, mm);
			start &= PAGE_MASK;
			end += (PAGE_SIZE - 1);
			end &= PAGE_MASK;
			अगर (mm != current->mm) अणु
				saved_asid = get_asid();
				set_asid(asid);
			पूर्ण
			जबतक (start < end) अणु
				local_flush_tlb_one(asid, start);
				start += PAGE_SIZE;
			पूर्ण
			अगर (saved_asid != MMU_NO_ASID)
				set_asid(saved_asid);
		पूर्ण
		local_irq_restore(flags);
	पूर्ण
पूर्ण

व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ flags;
	पूर्णांक size;

	local_irq_save(flags);
	size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	अगर (size > (MMU_NTLB_ENTRIES/4)) अणु /* Too many TLB to flush */
		local_flush_tlb_all();
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ asid;
		अचिन्हित दीर्घ saved_asid = get_asid();

		asid = cpu_asid(cpu, &init_mm);
		start &= PAGE_MASK;
		end += (PAGE_SIZE - 1);
		end &= PAGE_MASK;
		set_asid(asid);
		जबतक (start < end) अणु
			local_flush_tlb_one(asid, start);
			start += PAGE_SIZE;
		पूर्ण
		set_asid(saved_asid);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/* Invalidate all TLB of this process. */
	/* Instead of invalidating each TLB, we get new MMU context. */
	अगर (cpu_context(cpu, mm) != NO_CONTEXT) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		cpu_context(cpu, mm) = NO_CONTEXT;
		अगर (mm == current->mm)
			activate_context(mm, cpu);
		local_irq_restore(flags);
	पूर्ण
पूर्ण

व्योम __flush_tlb_global(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/*
	 * This is the most deकाष्ठाive of the TLB flushing options,
	 * and will tear करोwn all of the UTLB/ITLB mappings, including
	 * wired entries.
	 */
	__raw_ग_लिखोl(__raw_पढ़ोl(MMUCR) | MMUCR_TI, MMUCR);

	local_irq_restore(flags);
पूर्ण
