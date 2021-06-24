<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/sparc/mm/leon_m.c
 *
 * Copyright (C) 2004 Konrad Eisele (eiselekd@web.de, konrad@gaisler.com) Gaisler Research
 * Copyright (C) 2009 Daniel Hellstrom (daniel@gaisler.com) Aeroflex Gaisler AB
 * Copyright (C) 2009 Konrad Eisele (konrad@gaisler.com) Aeroflex Gaisler AB
 *
 * करो srmmu probe in software
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/leon.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "mm_32.h"

पूर्णांक leon_flush_during_चयन = 1;
अटल पूर्णांक srmmu_swprobe_trace;

अटल अंतरभूत अचिन्हित दीर्घ leon_get_ctable_ptr(व्योम)
अणु
	अचिन्हित पूर्णांक retval;

	__यंत्र__ __अस्थिर__("lda [%1] %2, %0\n\t" :
			     "=r" (retval) :
			     "r" (SRMMU_CTXTBL_PTR),
			     "i" (ASI_LEON_MMUREGS));
	वापस (retval & SRMMU_CTX_PMASK) << 4;
पूर्ण


अचिन्हित दीर्घ leon_swprobe(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ *paddr)
अणु

	अचिन्हित पूर्णांक ctxtbl;
	अचिन्हित पूर्णांक pgd, pmd, ped;
	अचिन्हित पूर्णांक ptr;
	अचिन्हित पूर्णांक lvl, pte, paddrbase;
	अचिन्हित पूर्णांक ctx;
	अचिन्हित पूर्णांक paddr_calc;

	paddrbase = 0;

	अगर (srmmu_swprobe_trace)
		prपूर्णांकk(KERN_INFO "swprobe: trace on\n");

	ctxtbl = leon_get_ctable_ptr();
	अगर (!(ctxtbl)) अणु
		अगर (srmmu_swprobe_trace)
			prपूर्णांकk(KERN_INFO "swprobe: leon_get_ctable_ptr returned 0=>0\n");
		वापस 0;
	पूर्ण
	अगर (!_pfn_valid(PFN(ctxtbl))) अणु
		अगर (srmmu_swprobe_trace)
			prपूर्णांकk(KERN_INFO
			       "swprobe: !_pfn_valid(%x)=>0\n",
			       PFN(ctxtbl));
		वापस 0;
	पूर्ण

	ctx = srmmu_get_context();
	अगर (srmmu_swprobe_trace)
		prपूर्णांकk(KERN_INFO "swprobe:  --- ctx (%x) ---\n", ctx);

	pgd = LEON_BYPASS_LOAD_PA(ctxtbl + (ctx * 4));

	अगर (((pgd & SRMMU_ET_MASK) == SRMMU_ET_PTE)) अणु
		अगर (srmmu_swprobe_trace)
			prपूर्णांकk(KERN_INFO "swprobe: pgd is entry level 3\n");
		lvl = 3;
		pte = pgd;
		paddrbase = pgd & _SRMMU_PTE_PMASK_LEON;
		जाओ पढ़ोy;
	पूर्ण
	अगर (((pgd & SRMMU_ET_MASK) != SRMMU_ET_PTD)) अणु
		अगर (srmmu_swprobe_trace)
			prपूर्णांकk(KERN_INFO "swprobe: pgd is invalid => 0\n");
		वापस 0;
	पूर्ण

	अगर (srmmu_swprobe_trace)
		prपूर्णांकk(KERN_INFO "swprobe:  --- pgd (%x) ---\n", pgd);

	ptr = (pgd & SRMMU_PTD_PMASK) << 4;
	ptr += ((((vaddr) >> LEON_PGD_SH) & LEON_PGD_M) * 4);
	अगर (!_pfn_valid(PFN(ptr)))
		वापस 0;

	pmd = LEON_BYPASS_LOAD_PA(ptr);
	अगर (((pmd & SRMMU_ET_MASK) == SRMMU_ET_PTE)) अणु
		अगर (srmmu_swprobe_trace)
			prपूर्णांकk(KERN_INFO "swprobe: pmd is entry level 2\n");
		lvl = 2;
		pte = pmd;
		paddrbase = pmd & _SRMMU_PTE_PMASK_LEON;
		जाओ पढ़ोy;
	पूर्ण
	अगर (((pmd & SRMMU_ET_MASK) != SRMMU_ET_PTD)) अणु
		अगर (srmmu_swprobe_trace)
			prपूर्णांकk(KERN_INFO "swprobe: pmd is invalid => 0\n");
		वापस 0;
	पूर्ण

	अगर (srmmu_swprobe_trace)
		prपूर्णांकk(KERN_INFO "swprobe:  --- pmd (%x) ---\n", pmd);

	ptr = (pmd & SRMMU_PTD_PMASK) << 4;
	ptr += (((vaddr >> LEON_PMD_SH) & LEON_PMD_M) * 4);
	अगर (!_pfn_valid(PFN(ptr))) अणु
		अगर (srmmu_swprobe_trace)
			prपूर्णांकk(KERN_INFO "swprobe: !_pfn_valid(%x)=>0\n",
			       PFN(ptr));
		वापस 0;
	पूर्ण

	ped = LEON_BYPASS_LOAD_PA(ptr);

	अगर (((ped & SRMMU_ET_MASK) == SRMMU_ET_PTE)) अणु
		अगर (srmmu_swprobe_trace)
			prपूर्णांकk(KERN_INFO "swprobe: ped is entry level 1\n");
		lvl = 1;
		pte = ped;
		paddrbase = ped & _SRMMU_PTE_PMASK_LEON;
		जाओ पढ़ोy;
	पूर्ण
	अगर (((ped & SRMMU_ET_MASK) != SRMMU_ET_PTD)) अणु
		अगर (srmmu_swprobe_trace)
			prपूर्णांकk(KERN_INFO "swprobe: ped is invalid => 0\n");
		वापस 0;
	पूर्ण

	अगर (srmmu_swprobe_trace)
		prपूर्णांकk(KERN_INFO "swprobe:  --- ped (%x) ---\n", ped);

	ptr = (ped & SRMMU_PTD_PMASK) << 4;
	ptr += (((vaddr >> LEON_PTE_SH) & LEON_PTE_M) * 4);
	अगर (!_pfn_valid(PFN(ptr)))
		वापस 0;

	ptr = LEON_BYPASS_LOAD_PA(ptr);
	अगर (((ptr & SRMMU_ET_MASK) == SRMMU_ET_PTE)) अणु
		अगर (srmmu_swprobe_trace)
			prपूर्णांकk(KERN_INFO "swprobe: ptr is entry level 0\n");
		lvl = 0;
		pte = ptr;
		paddrbase = ptr & _SRMMU_PTE_PMASK_LEON;
		जाओ पढ़ोy;
	पूर्ण
	अगर (srmmu_swprobe_trace)
		prपूर्णांकk(KERN_INFO "swprobe: ptr is invalid => 0\n");
	वापस 0;

पढ़ोy:
	चयन (lvl) अणु
	हाल 0:
		paddr_calc =
		    (vaddr & ~(-1 << LEON_PTE_SH)) | ((pte & ~0xff) << 4);
		अवरोध;
	हाल 1:
		paddr_calc =
		    (vaddr & ~(-1 << LEON_PMD_SH)) | ((pte & ~0xff) << 4);
		अवरोध;
	हाल 2:
		paddr_calc =
		    (vaddr & ~(-1 << LEON_PGD_SH)) | ((pte & ~0xff) << 4);
		अवरोध;
	शेष:
	हाल 3:
		paddr_calc = vaddr;
		अवरोध;
	पूर्ण
	अगर (srmmu_swprobe_trace)
		prपूर्णांकk(KERN_INFO "swprobe: padde %x\n", paddr_calc);
	अगर (paddr)
		*paddr = paddr_calc;
	वापस pte;
पूर्ण

व्योम leon_flush_icache_all(व्योम)
अणु
	__यंत्र__ __अस्थिर__(" flush ");	/*अगरlush*/
पूर्ण

व्योम leon_flush_dcache_all(व्योम)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_LEON_DFLUSH) : "memory");
पूर्ण

व्योम leon_flush_pcache_all(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	अगर (vma->vm_flags & VM_EXEC)
		leon_flush_icache_all();
	leon_flush_dcache_all();
पूर्ण

व्योम leon_flush_cache_all(व्योम)
अणु
	__यंत्र__ __अस्थिर__(" flush ");	/*अगरlush*/
	__यंत्र__ __अस्थिर__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_LEON_DFLUSH) : "memory");
पूर्ण

व्योम leon_flush_tlb_all(व्योम)
अणु
	leon_flush_cache_all();
	__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t" : : "r"(0x400),
			     "i"(ASI_LEON_MMUFLUSH) : "memory");
पूर्ण

/* get all cache regs */
व्योम leon3_getCacheRegs(काष्ठा leon3_cacheregs *regs)
अणु
	अचिन्हित दीर्घ ccr, iccr, dccr;

	अगर (!regs)
		वापस;
	/* Get Cache regs from "Cache ASI" address 0x0, 0x8 and 0xC */
	__यंत्र__ __अस्थिर__("lda [%%g0] %3, %0\n\t"
			     "mov 0x08, %%g1\n\t"
			     "lda [%%g1] %3, %1\n\t"
			     "mov 0x0c, %%g1\n\t"
			     "lda [%%g1] %3, %2\n\t"
			     : "=r"(ccr), "=r"(iccr), "=r"(dccr)
			       /* output */
			     : "i"(ASI_LEON_CACHEREGS)	/* input */
			     : "g1"	/* clobber list */
	    );
	regs->ccr = ccr;
	regs->iccr = iccr;
	regs->dccr = dccr;
पूर्ण

/* Due to भव cache we need to check cache configuration अगर
 * it is possible to skip flushing in some हालs.
 *
 * Leon2 and Leon3 dअगरfer in their way of telling cache inक्रमmation
 *
 */
पूर्णांक __init leon_flush_needed(व्योम)
अणु
	पूर्णांक flush_needed = -1;
	अचिन्हित पूर्णांक ssize, sets;
	अक्षर *setStr[4] =
	    अणु "direct mapped", "2-way associative", "3-way associative",
		"4-way associative"
	पूर्ण;
	/* leon 3 */
	काष्ठा leon3_cacheregs cregs;
	leon3_getCacheRegs(&cregs);
	sets = (cregs.dccr & LEON3_XCCR_SETS_MASK) >> 24;
	/* (ssize=>realsize) 0=>1k, 1=>2k, 2=>4k, 3=>8k ... */
	ssize = 1 << ((cregs.dccr & LEON3_XCCR_SSIZE_MASK) >> 20);

	prपूर्णांकk(KERN_INFO "CACHE: %s cache, set size %dk\n",
	       sets > 3 ? "unknown" : setStr[sets], ssize);
	अगर ((ssize <= (PAGE_SIZE / 1024)) && (sets == 0)) अणु
		/* Set Size <= Page size  ==>
		   flush on every context चयन not needed. */
		flush_needed = 0;
		prपूर्णांकk(KERN_INFO "CACHE: not flushing on every context switch\n");
	पूर्ण
	वापस flush_needed;
पूर्ण

व्योम leon_चयन_mm(व्योम)
अणु
	flush_tlb_mm((व्योम *)0);
	अगर (leon_flush_during_चयन)
		leon_flush_cache_all();
पूर्ण

अटल व्योम leon_flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	leon_flush_cache_all();
पूर्ण

अटल व्योम leon_flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	leon_flush_pcache_all(vma, page);
पूर्ण

अटल व्योम leon_flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ start,
				   अचिन्हित दीर्घ end)
अणु
	leon_flush_cache_all();
पूर्ण

अटल व्योम leon_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	leon_flush_tlb_all();
पूर्ण

अटल व्योम leon_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ page)
अणु
	leon_flush_tlb_all();
पूर्ण

अटल व्योम leon_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ start,
				 अचिन्हित दीर्घ end)
अणु
	leon_flush_tlb_all();
पूर्ण

अटल व्योम leon_flush_page_to_ram(अचिन्हित दीर्घ page)
अणु
	leon_flush_cache_all();
पूर्ण

अटल व्योम leon_flush_sig_insns(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ page)
अणु
	leon_flush_cache_all();
पूर्ण

अटल व्योम leon_flush_page_क्रम_dma(अचिन्हित दीर्घ page)
अणु
	leon_flush_dcache_all();
पूर्ण

व्योम __init poke_leonsparc(व्योम)
अणु
पूर्ण

अटल स्थिर काष्ठा sparc32_cachetlb_ops leon_ops = अणु
	.cache_all	= leon_flush_cache_all,
	.cache_mm	= leon_flush_cache_mm,
	.cache_page	= leon_flush_cache_page,
	.cache_range	= leon_flush_cache_range,
	.tlb_all	= leon_flush_tlb_all,
	.tlb_mm		= leon_flush_tlb_mm,
	.tlb_page	= leon_flush_tlb_page,
	.tlb_range	= leon_flush_tlb_range,
	.page_to_ram	= leon_flush_page_to_ram,
	.sig_insns	= leon_flush_sig_insns,
	.page_क्रम_dma	= leon_flush_page_क्रम_dma,
पूर्ण;

व्योम __init init_leon(व्योम)
अणु
	srmmu_name = "LEON";
	sparc32_cachetlb_ops = &leon_ops;
	poke_srmmu = poke_leonsparc;

	leon_flush_during_चयन = leon_flush_needed();
पूर्ण
