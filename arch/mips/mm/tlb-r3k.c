<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r2300.c: R2000 and R3000 specअगरic mmu/cache code.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 *
 * with a lot of changes to make this thing work क्रम R3000s
 * Tx39XX R4k style caches added. HK
 * Copyright (C) 1998, 1999, 2000 Harald Koerfgen
 * Copyright (C) 1998 Gleb Raiko & Vladimir Roganov
 * Copyright (C) 2002  Ralf Baechle
 * Copyright (C) 2002  Maciej W. Rozycki
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbmisc.h>
#समावेश <यंत्र/isadep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>

#अघोषित DEBUG_TLB

बाह्य व्योम build_tlb_refill_handler(व्योम);

/* CP0 hazard aव्योमance. */
#घोषणा BARRIER				\
	__यंत्र__ __अस्थिर__(		\
		".set	push\n\t"	\
		".set	noreorder\n\t"	\
		"nop\n\t"		\
		".set	pop\n\t")

पूर्णांक r3k_have_wired_reg;			/* Should be in cpu_data? */

/* TLB operations. */
अटल व्योम local_flush_tlb_from(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ old_ctx;

	old_ctx = पढ़ो_c0_entryhi() & cpu_asid_mask(&current_cpu_data);
	ग_लिखो_c0_entrylo0(0);
	जबतक (entry < current_cpu_data.tlbsize) अणु
		ग_लिखो_c0_index(entry << 8);
		ग_लिखो_c0_entryhi((entry | 0x80000) << 12);
		entry++;				/* BARRIER */
		tlb_ग_लिखो_indexed();
	पूर्ण
	ग_लिखो_c0_entryhi(old_ctx);
पूर्ण

व्योम local_flush_tlb_all(व्योम)
अणु
	अचिन्हित दीर्घ flags;

#अगर_घोषित DEBUG_TLB
	prपूर्णांकk("[tlball]");
#पूर्ण_अगर
	local_irq_save(flags);
	local_flush_tlb_from(r3k_have_wired_reg ? पढ़ो_c0_wired() : 8);
	local_irq_restore(flags);
पूर्ण

व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ asid_mask = cpu_asid_mask(&current_cpu_data);
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	पूर्णांक cpu = smp_processor_id();

	अगर (cpu_context(cpu, mm) != 0) अणु
		अचिन्हित दीर्घ size, flags;

#अगर_घोषित DEBUG_TLB
		prपूर्णांकk("[tlbrange<%lu,0x%08lx,0x%08lx>]",
			cpu_context(cpu, mm) & asid_mask, start, end);
#पूर्ण_अगर
		local_irq_save(flags);
		size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
		अगर (size <= current_cpu_data.tlbsize) अणु
			पूर्णांक oldpid = पढ़ो_c0_entryhi() & asid_mask;
			पूर्णांक newpid = cpu_context(cpu, mm) & asid_mask;

			start &= PAGE_MASK;
			end += PAGE_SIZE - 1;
			end &= PAGE_MASK;
			जबतक (start < end) अणु
				पूर्णांक idx;

				ग_लिखो_c0_entryhi(start | newpid);
				start += PAGE_SIZE;	/* BARRIER */
				tlb_probe();
				idx = पढ़ो_c0_index();
				ग_लिखो_c0_entrylo0(0);
				ग_लिखो_c0_entryhi(KSEG0);
				अगर (idx < 0)		/* BARRIER */
					जारी;
				tlb_ग_लिखो_indexed();
			पूर्ण
			ग_लिखो_c0_entryhi(oldpid);
		पूर्ण अन्यथा अणु
			drop_mmu_context(mm);
		पूर्ण
		local_irq_restore(flags);
	पूर्ण
पूर्ण

व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ size, flags;

#अगर_घोषित DEBUG_TLB
	prपूर्णांकk("[tlbrange<%lu,0x%08lx,0x%08lx>]", start, end);
#पूर्ण_अगर
	local_irq_save(flags);
	size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	अगर (size <= current_cpu_data.tlbsize) अणु
		पूर्णांक pid = पढ़ो_c0_entryhi();

		start &= PAGE_MASK;
		end += PAGE_SIZE - 1;
		end &= PAGE_MASK;

		जबतक (start < end) अणु
			पूर्णांक idx;

			ग_लिखो_c0_entryhi(start);
			start += PAGE_SIZE;		/* BARRIER */
			tlb_probe();
			idx = पढ़ो_c0_index();
			ग_लिखो_c0_entrylo0(0);
			ग_लिखो_c0_entryhi(KSEG0);
			अगर (idx < 0)			/* BARRIER */
				जारी;
			tlb_ग_लिखो_indexed();
		पूर्ण
		ग_लिखो_c0_entryhi(pid);
	पूर्ण अन्यथा अणु
		local_flush_tlb_all();
	पूर्ण
	local_irq_restore(flags);
पूर्ण

व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	अचिन्हित दीर्घ asid_mask = cpu_asid_mask(&current_cpu_data);
	पूर्णांक cpu = smp_processor_id();

	अगर (cpu_context(cpu, vma->vm_mm) != 0) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक oldpid, newpid, idx;

#अगर_घोषित DEBUG_TLB
		prपूर्णांकk("[tlbpage<%lu,0x%08lx>]", cpu_context(cpu, vma->vm_mm), page);
#पूर्ण_अगर
		newpid = cpu_context(cpu, vma->vm_mm) & asid_mask;
		page &= PAGE_MASK;
		local_irq_save(flags);
		oldpid = पढ़ो_c0_entryhi() & asid_mask;
		ग_लिखो_c0_entryhi(page | newpid);
		BARRIER;
		tlb_probe();
		idx = पढ़ो_c0_index();
		ग_लिखो_c0_entrylo0(0);
		ग_लिखो_c0_entryhi(KSEG0);
		अगर (idx < 0)				/* BARRIER */
			जाओ finish;
		tlb_ग_लिखो_indexed();

finish:
		ग_लिखो_c0_entryhi(oldpid);
		local_irq_restore(flags);
	पूर्ण
पूर्ण

व्योम __update_tlb(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, pte_t pte)
अणु
	अचिन्हित दीर्घ asid_mask = cpu_asid_mask(&current_cpu_data);
	अचिन्हित दीर्घ flags;
	पूर्णांक idx, pid;

	/*
	 * Handle debugger faulting in क्रम debugee.
	 */
	अगर (current->active_mm != vma->vm_mm)
		वापस;

	pid = पढ़ो_c0_entryhi() & asid_mask;

#अगर_घोषित DEBUG_TLB
	अगर ((pid != (cpu_context(cpu, vma->vm_mm) & asid_mask)) || (cpu_context(cpu, vma->vm_mm) == 0)) अणु
		prपूर्णांकk("update_mmu_cache: Wheee, bogus tlbpid mmpid=%lu tlbpid=%d\n",
		       (cpu_context(cpu, vma->vm_mm)), pid);
	पूर्ण
#पूर्ण_अगर

	local_irq_save(flags);
	address &= PAGE_MASK;
	ग_लिखो_c0_entryhi(address | pid);
	BARRIER;
	tlb_probe();
	idx = पढ़ो_c0_index();
	ग_लिखो_c0_entrylo0(pte_val(pte));
	ग_लिखो_c0_entryhi(address | pid);
	अगर (idx < 0) अणु					/* BARRIER */
		tlb_ग_लिखो_अक्रमom();
	पूर्ण अन्यथा अणु
		tlb_ग_लिखो_indexed();
	पूर्ण
	ग_लिखो_c0_entryhi(pid);
	local_irq_restore(flags);
पूर्ण

व्योम add_wired_entry(अचिन्हित दीर्घ entrylo0, अचिन्हित दीर्घ entrylo1,
		     अचिन्हित दीर्घ entryhi, अचिन्हित दीर्घ pagemask)
अणु
	अचिन्हित दीर्घ asid_mask = cpu_asid_mask(&current_cpu_data);
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ old_ctx;
	अटल अचिन्हित दीर्घ wired = 0;

	अगर (r3k_have_wired_reg) अणु			/* TX39XX */
		अचिन्हित दीर्घ old_pagemask;
		अचिन्हित दीर्घ w;

#अगर_घोषित DEBUG_TLB
		prपूर्णांकk("[tlbwired<entry lo0 %8x, hi %8x\n, pagemask %8x>]\n",
		       entrylo0, entryhi, pagemask);
#पूर्ण_अगर

		local_irq_save(flags);
		/* Save old context and create impossible VPN2 value */
		old_ctx = पढ़ो_c0_entryhi() & asid_mask;
		old_pagemask = पढ़ो_c0_pagemask();
		w = पढ़ो_c0_wired();
		ग_लिखो_c0_wired(w + 1);
		ग_लिखो_c0_index(w << 8);
		ग_लिखो_c0_pagemask(pagemask);
		ग_लिखो_c0_entryhi(entryhi);
		ग_लिखो_c0_entrylo0(entrylo0);
		BARRIER;
		tlb_ग_लिखो_indexed();

		ग_लिखो_c0_entryhi(old_ctx);
		ग_लिखो_c0_pagemask(old_pagemask);
		local_flush_tlb_all();
		local_irq_restore(flags);

	पूर्ण अन्यथा अगर (wired < 8) अणु
#अगर_घोषित DEBUG_TLB
		prपूर्णांकk("[tlbwired<entry lo0 %8x, hi %8x\n>]\n",
		       entrylo0, entryhi);
#पूर्ण_अगर

		local_irq_save(flags);
		old_ctx = पढ़ो_c0_entryhi() & asid_mask;
		ग_लिखो_c0_entrylo0(entrylo0);
		ग_लिखो_c0_entryhi(entryhi);
		ग_लिखो_c0_index(wired);
		wired++;				/* BARRIER */
		tlb_ग_लिखो_indexed();
		ग_लिखो_c0_entryhi(old_ctx);
		local_flush_tlb_all();
		local_irq_restore(flags);
	पूर्ण
पूर्ण

व्योम tlb_init(व्योम)
अणु
	चयन (current_cpu_type()) अणु
	हाल CPU_TX3922:
	हाल CPU_TX3927:
		r3k_have_wired_reg = 1;
		ग_लिखो_c0_wired(0);		/* Set to 8 on reset... */
		अवरोध;
	पूर्ण
	local_flush_tlb_from(0);
	build_tlb_refill_handler();
पूर्ण
