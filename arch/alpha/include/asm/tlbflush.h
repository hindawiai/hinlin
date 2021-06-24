<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_TLBFLUSH_H
#घोषणा _ALPHA_TLBFLUSH_H

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/compiler.h>

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __MMU_EXTERN_INLINE
#पूर्ण_अगर

बाह्य व्योम __load_new_mm_context(काष्ठा mm_काष्ठा *);


/* Use a few helper functions to hide the ugly broken ASN
   numbers on early Alphas (ev4 and ev45).  */

__EXTERN_INLINE व्योम
ev4_flush_tlb_current(काष्ठा mm_काष्ठा *mm)
अणु
	__load_new_mm_context(mm);
	tbiap();
पूर्ण

__EXTERN_INLINE व्योम
ev5_flush_tlb_current(काष्ठा mm_काष्ठा *mm)
अणु
	__load_new_mm_context(mm);
पूर्ण

/* Flush just one page in the current TLB set.  We need to be very
   careful about the icache here, there is no way to invalidate a
   specअगरic icache page.  */

__EXTERN_INLINE व्योम
ev4_flush_tlb_current_page(काष्ठा mm_काष्ठा * mm,
			   काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ addr)
अणु
	पूर्णांक tbi_flag = 2;
	अगर (vma->vm_flags & VM_EXEC) अणु
		__load_new_mm_context(mm);
		tbi_flag = 3;
	पूर्ण
	tbi(tbi_flag, addr);
पूर्ण

__EXTERN_INLINE व्योम
ev5_flush_tlb_current_page(काष्ठा mm_काष्ठा * mm,
			   काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ addr)
अणु
	अगर (vma->vm_flags & VM_EXEC)
		__load_new_mm_context(mm);
	अन्यथा
		tbi(2, addr);
पूर्ण


#अगर_घोषित CONFIG_ALPHA_GENERIC
# define flush_tlb_current		alpha_mv.mv_flush_tlb_current
# define flush_tlb_current_page		alpha_mv.mv_flush_tlb_current_page
#अन्यथा
# अगरdef CONFIG_ALPHA_EV4
#  define flush_tlb_current		ev4_flush_tlb_current
#  define flush_tlb_current_page	ev4_flush_tlb_current_page
# अन्यथा
#  define flush_tlb_current		ev5_flush_tlb_current
#  define flush_tlb_current_page	ev5_flush_tlb_current_page
# endअगर
#पूर्ण_अगर

#अगर_घोषित __MMU_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __MMU_EXTERN_INLINE
#पूर्ण_अगर

/* Flush current user mapping.  */
अटल अंतरभूत व्योम
flush_tlb(व्योम)
अणु
	flush_tlb_current(current->active_mm);
पूर्ण

/* Flush someone अन्यथा's user mapping.  */
अटल अंतरभूत व्योम
flush_tlb_other(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ *mmc = &mm->context[smp_processor_id()];
	/* Check it's not zero first to aव्योम cacheline ping pong
	   when possible.  */
	अगर (*mmc) *mmc = 0;
पूर्ण

#अगर_अघोषित CONFIG_SMP
/* Flush everything (kernel mapping may also have changed
   due to vदो_स्मृति/vमुक्त).  */
अटल अंतरभूत व्योम flush_tlb_all(व्योम)
अणु
	tbia();
पूर्ण

/* Flush a specअगरied user mapping.  */
अटल अंतरभूत व्योम
flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm == current->active_mm)
		flush_tlb_current(mm);
	अन्यथा
		flush_tlb_other(mm);
पूर्ण

/* Page-granular tlb flush.  */
अटल अंतरभूत व्योम
flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर (mm == current->active_mm)
		flush_tlb_current_page(mm, vma, addr);
	अन्यथा
		flush_tlb_other(mm);
पूर्ण

/* Flush a specअगरied range of user mapping.  On the Alpha we flush
   the whole user tlb.  */
अटल अंतरभूत व्योम
flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ end)
अणु
	flush_tlb_mm(vma->vm_mm);
पूर्ण

#अन्यथा /* CONFIG_SMP */

बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *);
बाह्य व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ);
बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ,
			    अचिन्हित दीर्घ);

#पूर्ण_अगर /* CONFIG_SMP */

अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start,
					अचिन्हित दीर्घ end)
अणु
	flush_tlb_all();
पूर्ण

#पूर्ण_अगर /* _ALPHA_TLBFLUSH_H */
