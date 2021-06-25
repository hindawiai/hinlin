<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_TLBFLUSH_H
#घोषणा _ASM_IA64_TLBFLUSH_H

/*
 * Copyright (C) 2002 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */


#समावेश <linux/mm.h>

#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/page.h>

काष्ठा ia64_tr_entry अणु
	u64 अगरa;
	u64 itir;
	u64 pte;
	u64 rr;
पूर्ण; /*Record क्रम tr entry!*/

बाह्य पूर्णांक ia64_itr_entry(u64 target_mask, u64 va, u64 pte, u64 log_size);
बाह्य व्योम ia64_ptr_entry(u64 target_mask, पूर्णांक slot);
बाह्य काष्ठा ia64_tr_entry *ia64_idtrs[NR_CPUS];

/*
 region रेजिस्टर macros
*/
#घोषणा RR_TO_VE(val)   (((val) >> 0) & 0x0000000000000001)
#घोषणा RR_VE(val)     (((val) & 0x0000000000000001) << 0)
#घोषणा RR_VE_MASK     0x0000000000000001L
#घोषणा RR_VE_SHIFT    0
#घोषणा RR_TO_PS(val)  (((val) >> 2) & 0x000000000000003f)
#घोषणा RR_PS(val)     (((val) & 0x000000000000003f) << 2)
#घोषणा RR_PS_MASK     0x00000000000000fcL
#घोषणा RR_PS_SHIFT    2
#घोषणा RR_RID_MASK    0x00000000ffffff00L
#घोषणा RR_TO_RID(val)         ((val >> 8) & 0xffffff)

/*
 * Now क्रम some TLB flushing routines.  This is the kind of stuff that
 * can be very expensive, so try to aव्योम them whenever possible.
 */
बाह्य व्योम setup_ptcg_sem(पूर्णांक max_purges, पूर्णांक from_palo);

/*
 * Flush everything (kernel mapping may also have changed due to
 * vदो_स्मृति/vमुक्त).
 */
बाह्य व्योम local_flush_tlb_all (व्योम);

#अगर_घोषित CONFIG_SMP
  बाह्य व्योम smp_flush_tlb_all (व्योम);
  बाह्य व्योम smp_flush_tlb_mm (काष्ठा mm_काष्ठा *mm);
  बाह्य व्योम smp_flush_tlb_cpumask (cpumask_t xcpumask);
# define flush_tlb_all()	smp_flush_tlb_all()
#अन्यथा
# define flush_tlb_all()	local_flush_tlb_all()
# define smp_flush_tlb_cpumask(m) local_flush_tlb_all()
#पूर्ण_अगर

अटल अंतरभूत व्योम
local_finish_flush_tlb_mm (काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm == current->active_mm)
		activate_context(mm);
पूर्ण

/*
 * Flush a specअगरied user mapping.  This is called, e.g., as a result of विभाजन() and
 * निकास().  विभाजन() ends up here because the copy-on-ग_लिखो mechanism needs to ग_लिखो-protect
 * the PTEs of the parent task.
 */
अटल अंतरभूत व्योम
flush_tlb_mm (काष्ठा mm_काष्ठा *mm)
अणु
	अगर (!mm)
		वापस;

	set_bit(mm->context, ia64_ctx.flushmap);
	mm->context = 0;

	अगर (atomic_पढ़ो(&mm->mm_users) == 0)
		वापस;		/* happens as a result of निकास_mmap() */

#अगर_घोषित CONFIG_SMP
	smp_flush_tlb_mm(mm);
#अन्यथा
	local_finish_flush_tlb_mm(mm);
#पूर्ण_अगर
पूर्ण

बाह्य व्योम flush_tlb_range (काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

/*
 * Page-granular tlb flush.
 */
अटल अंतरभूत व्योम
flush_tlb_page (काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
#अगर_घोषित CONFIG_SMP
	flush_tlb_range(vma, (addr & PAGE_MASK), (addr & PAGE_MASK) + PAGE_SIZE);
#अन्यथा
	अगर (vma->vm_mm == current->active_mm)
		ia64_ptcl(addr, (PAGE_SHIFT << 2));
	अन्यथा
		vma->vm_mm->context = 0;
#पूर्ण_अगर
पूर्ण

/*
 * Flush the local TLB. Invoked from another cpu using an IPI.
 */
#अगर_घोषित CONFIG_SMP
व्योम smp_local_flush_tlb(व्योम);
#अन्यथा
#घोषणा smp_local_flush_tlb()
#पूर्ण_अगर

अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end)
अणु
	flush_tlb_all();	/* XXX fix me */
पूर्ण

#पूर्ण_अगर /* _ASM_IA64_TLBFLUSH_H */
