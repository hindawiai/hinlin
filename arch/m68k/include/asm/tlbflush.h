<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_TLBFLUSH_H
#घोषणा _M68K_TLBFLUSH_H

#अगर_घोषित CONFIG_MMU
#अगर_अघोषित CONFIG_SUN3

#समावेश <यंत्र/current.h>
#समावेश <यंत्र/mcfmmu.h>

अटल अंतरभूत व्योम flush_tlb_kernel_page(व्योम *addr)
अणु
	अगर (CPU_IS_COLDFIRE) अणु
		mmu_ग_लिखो(MMUOR, MMUOR_CNL);
	पूर्ण अन्यथा अगर (CPU_IS_040_OR_060) अणु
		mm_segment_t old_fs = get_fs();
		set_fs(KERNEL_DS);
		__यंत्र__ __अस्थिर__(".chip 68040\n\t"
				     "pflush (%0)\n\t"
				     ".chip 68k"
				     : : "a" (addr));
		set_fs(old_fs);
	पूर्ण अन्यथा अगर (CPU_IS_020_OR_030)
		__यंत्र__ __अस्थिर__("pflush #4,#4,(%0)" : : "a" (addr));
पूर्ण

/*
 * flush all user-space atc entries.
 */
अटल अंतरभूत व्योम __flush_tlb(व्योम)
अणु
	अगर (CPU_IS_COLDFIRE) अणु
		mmu_ग_लिखो(MMUOR, MMUOR_CNL);
	पूर्ण अन्यथा अगर (CPU_IS_040_OR_060) अणु
		__यंत्र__ __अस्थिर__(".chip 68040\n\t"
				     "pflushan\n\t"
				     ".chip 68k");
	पूर्ण अन्यथा अगर (CPU_IS_020_OR_030) अणु
		__यंत्र__ __अस्थिर__("pflush #0,#4");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __flush_tlb040_one(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__ __अस्थिर__(".chip 68040\n\t"
			     "pflush (%0)\n\t"
			     ".chip 68k"
			     : : "a" (addr));
पूर्ण

अटल अंतरभूत व्योम __flush_tlb_one(अचिन्हित दीर्घ addr)
अणु
	अगर (CPU_IS_COLDFIRE)
		mmu_ग_लिखो(MMUOR, MMUOR_CNL);
	अन्यथा अगर (CPU_IS_040_OR_060)
		__flush_tlb040_one(addr);
	अन्यथा अगर (CPU_IS_020_OR_030)
		__यंत्र__ __अस्थिर__("pflush #0,#4,(%0)" : : "a" (addr));
पूर्ण

#घोषणा flush_tlb() __flush_tlb()

/*
 * flush all atc entries (both kernel and user-space entries).
 */
अटल अंतरभूत व्योम flush_tlb_all(व्योम)
अणु
	अगर (CPU_IS_COLDFIRE) अणु
		mmu_ग_लिखो(MMUOR, MMUOR_CNL);
	पूर्ण अन्यथा अगर (CPU_IS_040_OR_060) अणु
		__यंत्र__ __अस्थिर__(".chip 68040\n\t"
				     "pflusha\n\t"
				     ".chip 68k");
	पूर्ण अन्यथा अगर (CPU_IS_020_OR_030) अणु
		__यंत्र__ __अस्थिर__("pflusha");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm == current->active_mm)
		__flush_tlb();
पूर्ण

अटल अंतरभूत व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	अगर (vma->vm_mm == current->active_mm) अणु
		mm_segment_t old_fs = क्रमce_uaccess_begin();

		__flush_tlb_one(addr);
		क्रमce_uaccess_end(old_fs);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (vma->vm_mm == current->active_mm)
		__flush_tlb();
पूर्ण

अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	flush_tlb_all();
पूर्ण

#अन्यथा


/* Reserved PMEGs. */
बाह्य अक्षर sun3_reserved_pmeg[SUN3_PMEGS_NUM];
बाह्य अचिन्हित दीर्घ pmeg_vaddr[SUN3_PMEGS_NUM];
बाह्य अचिन्हित अक्षर pmeg_alloc[SUN3_PMEGS_NUM];
बाह्य अचिन्हित अक्षर pmeg_ctx[SUN3_PMEGS_NUM];

/* Flush all userspace mappings one by one...  (why no flush command,
   sun?) */
अटल अंतरभूत व्योम flush_tlb_all(व्योम)
अणु
       अचिन्हित दीर्घ addr;
       अचिन्हित अक्षर ctx, oldctx;

       oldctx = sun3_get_context();
       क्रम(addr = 0x00000000; addr < TASK_SIZE; addr += SUN3_PMEG_SIZE) अणु
	       क्रम(ctx = 0; ctx < 8; ctx++) अणु
		       sun3_put_context(ctx);
		       sun3_put_segmap(addr, SUN3_INVALID_PMEG);
	       पूर्ण
       पूर्ण

       sun3_put_context(oldctx);
       /* erase all of the userspace pmeg maps, we've clobbered them
	  all anyway */
       क्रम(addr = 0; addr < SUN3_INVALID_PMEG; addr++) अणु
	       अगर(pmeg_alloc[addr] == 1) अणु
		       pmeg_alloc[addr] = 0;
		       pmeg_ctx[addr] = 0;
		       pmeg_vaddr[addr] = 0;
	       पूर्ण
       पूर्ण

पूर्ण

/* Clear user TLB entries within the context named in mm */
अटल अंतरभूत व्योम flush_tlb_mm (काष्ठा mm_काष्ठा *mm)
अणु
     अचिन्हित अक्षर oldctx;
     अचिन्हित अक्षर seg;
     अचिन्हित दीर्घ i;

     oldctx = sun3_get_context();
     sun3_put_context(mm->context);

     क्रम(i = 0; i < TASK_SIZE; i += SUN3_PMEG_SIZE) अणु
	     seg = sun3_get_segmap(i);
	     अगर(seg == SUN3_INVALID_PMEG)
		     जारी;

	     sun3_put_segmap(i, SUN3_INVALID_PMEG);
	     pmeg_alloc[seg] = 0;
	     pmeg_ctx[seg] = 0;
	     pmeg_vaddr[seg] = 0;
     पूर्ण

     sun3_put_context(oldctx);

पूर्ण

/* Flush a single TLB page. In this हाल, we're limited to flushing a
   single PMEG */
अटल अंतरभूत व्योम flush_tlb_page (काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ addr)
अणु
	अचिन्हित अक्षर oldctx;
	अचिन्हित अक्षर i;

	oldctx = sun3_get_context();
	sun3_put_context(vma->vm_mm->context);
	addr &= ~SUN3_PMEG_MASK;
	अगर((i = sun3_get_segmap(addr)) != SUN3_INVALID_PMEG)
	अणु
		pmeg_alloc[i] = 0;
		pmeg_ctx[i] = 0;
		pmeg_vaddr[i] = 0;
		sun3_put_segmap (addr,  SUN3_INVALID_PMEG);
	पूर्ण
	sun3_put_context(oldctx);

पूर्ण
/* Flush a range of pages from TLB. */

अटल अंतरभूत व्योम flush_tlb_range (काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित अक्षर seg, oldctx;

	start &= ~SUN3_PMEG_MASK;

	oldctx = sun3_get_context();
	sun3_put_context(mm->context);

	जबतक(start < end)
	अणु
		अगर((seg = sun3_get_segmap(start)) == SUN3_INVALID_PMEG)
		     जाओ next;
		अगर(pmeg_ctx[seg] == mm->context) अणु
			pmeg_alloc[seg] = 0;
			pmeg_ctx[seg] = 0;
			pmeg_vaddr[seg] = 0;
		पूर्ण
		sun3_put_segmap(start, SUN3_INVALID_PMEG);
	next:
		start += SUN3_PMEG_SIZE;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	flush_tlb_all();
पूर्ण

/* Flush kernel page from TLB. */
अटल अंतरभूत व्योम flush_tlb_kernel_page (अचिन्हित दीर्घ addr)
अणु
	sun3_put_segmap (addr & ~(SUN3_PMEG_SIZE - 1), SUN3_INVALID_PMEG);
पूर्ण

#पूर्ण_अगर

#अन्यथा /* !CONFIG_MMU */

/*
 * flush all user-space atc entries.
 */
अटल अंतरभूत व्योम __flush_tlb(व्योम)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम __flush_tlb_one(अचिन्हित दीर्घ addr)
अणु
	BUG();
पूर्ण

#घोषणा flush_tlb() __flush_tlb()

/*
 * flush all atc entries (both kernel and user-space entries).
 */
अटल अंतरभूत व्योम flush_tlb_all(व्योम)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम flush_tlb_range(काष्ठा mm_काष्ठा *mm,
				   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम flush_tlb_kernel_page(अचिन्हित दीर्घ addr)
अणु
	BUG();
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU */

#पूर्ण_अगर /* _M68K_TLBFLUSH_H */
