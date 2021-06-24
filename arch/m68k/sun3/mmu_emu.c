<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
** Tablewalk MMU emulator
**
** by Toshiyasu Morita
**
** Started 1/16/98 @ 2:22 am
*/

#समावेश <linux/init.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/delay.h>
#समावेश <linux/memblock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/mm.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sun3mmu.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/dvma.h>


#अघोषित DEBUG_MMU_EMU
#घोषणा DEBUG_PROM_MAPS

/*
** Defines
*/

#घोषणा CONTEXTS_NUM		8
#घोषणा SEGMAPS_PER_CONTEXT_NUM 2048
#घोषणा PAGES_PER_SEGMENT	16
#घोषणा PMEGS_NUM		256
#घोषणा PMEG_MASK		0xFF

/*
** Globals
*/

अचिन्हित दीर्घ m68k_vदो_स्मृति_end;
EXPORT_SYMBOL(m68k_vदो_स्मृति_end);

अचिन्हित दीर्घ pmeg_vaddr[PMEGS_NUM];
अचिन्हित अक्षर pmeg_alloc[PMEGS_NUM];
अचिन्हित अक्षर pmeg_ctx[PMEGS_NUM];

/* poपूर्णांकers to the mm काष्ठाs क्रम each task in each
   context. 0xffffffff is a marker क्रम kernel context */
अटल काष्ठा mm_काष्ठा *ctx_alloc[CONTEXTS_NUM] = अणु
    [0] = (काष्ठा mm_काष्ठा *)0xffffffff
पूर्ण;

/* has this context been mmdrop'd? */
अटल अचिन्हित अक्षर ctx_avail = CONTEXTS_NUM-1;

/* array of pages to be marked off क्रम the rom when we करो mem_init later */
/* 256 pages lets the rom take up to 2mb of physical ram..  I really
   hope it never wants mote than that. */
अचिन्हित दीर्घ rom_pages[256];

/* Prपूर्णांक a PTE value in symbolic क्रमm. For debugging. */
व्योम prपूर्णांक_pte (pte_t pte)
अणु
#अगर 0
	/* Verbose version. */
	अचिन्हित दीर्घ val = pte_val (pte);
	pr_cont(" pte=%lx [addr=%lx",
		val, (val & SUN3_PAGE_PGNUM_MASK) << PAGE_SHIFT);
	अगर (val & SUN3_PAGE_VALID)	pr_cont(" valid");
	अगर (val & SUN3_PAGE_WRITEABLE)	pr_cont(" write");
	अगर (val & SUN3_PAGE_SYSTEM)	pr_cont(" sys");
	अगर (val & SUN3_PAGE_NOCACHE)	pr_cont(" nocache");
	अगर (val & SUN3_PAGE_ACCESSED)	pr_cont(" accessed");
	अगर (val & SUN3_PAGE_MODIFIED)	pr_cont(" modified");
	चयन (val & SUN3_PAGE_TYPE_MASK) अणु
		हाल SUN3_PAGE_TYPE_MEMORY: pr_cont(" memory"); अवरोध;
		हाल SUN3_PAGE_TYPE_IO:     pr_cont(" io");     अवरोध;
		हाल SUN3_PAGE_TYPE_VME16:  pr_cont(" vme16");  अवरोध;
		हाल SUN3_PAGE_TYPE_VME32:  pr_cont(" vme32");  अवरोध;
	पूर्ण
	pr_cont("]\n");
#अन्यथा
	/* Terse version. More likely to fit on a line. */
	अचिन्हित दीर्घ val = pte_val (pte);
	अक्षर flags[7], *type;

	flags[0] = (val & SUN3_PAGE_VALID)     ? 'v' : '-';
	flags[1] = (val & SUN3_PAGE_WRITEABLE) ? 'w' : '-';
	flags[2] = (val & SUN3_PAGE_SYSTEM)    ? 's' : '-';
	flags[3] = (val & SUN3_PAGE_NOCACHE)   ? 'x' : '-';
	flags[4] = (val & SUN3_PAGE_ACCESSED)  ? 'a' : '-';
	flags[5] = (val & SUN3_PAGE_MODIFIED)  ? 'm' : '-';
	flags[6] = '\0';

	चयन (val & SUN3_PAGE_TYPE_MASK) अणु
		हाल SUN3_PAGE_TYPE_MEMORY: type = "memory"; अवरोध;
		हाल SUN3_PAGE_TYPE_IO:     type = "io"    ; अवरोध;
		हाल SUN3_PAGE_TYPE_VME16:  type = "vme16" ; अवरोध;
		हाल SUN3_PAGE_TYPE_VME32:  type = "vme32" ; अवरोध;
		शेष: type = "unknown?"; अवरोध;
	पूर्ण

	pr_cont(" pte=%08lx [%07lx %s %s]\n",
		val, (val & SUN3_PAGE_PGNUM_MASK) << PAGE_SHIFT, flags, type);
#पूर्ण_अगर
पूर्ण

/* Prपूर्णांक the PTE value क्रम a given भव address. For debugging. */
व्योम prपूर्णांक_pte_vaddr (अचिन्हित दीर्घ vaddr)
अणु
	pr_cont(" vaddr=%lx [%02lx]", vaddr, sun3_get_segmap (vaddr));
	prपूर्णांक_pte (__pte (sun3_get_pte (vaddr)));
पूर्ण

/*
 * Initialise the MMU emulator.
 */
व्योम __init mmu_emu_init(अचिन्हित दीर्घ booपंचांगem_end)
अणु
	अचिन्हित दीर्घ seg, num;
	पूर्णांक i,j;

	स_रखो(rom_pages, 0, माप(rom_pages));
	स_रखो(pmeg_vaddr, 0, माप(pmeg_vaddr));
	स_रखो(pmeg_alloc, 0, माप(pmeg_alloc));
	स_रखो(pmeg_ctx, 0, माप(pmeg_ctx));

	/* pmeg align the end of booपंचांगem, adding another pmeg,
	 * later booपंचांगem allocations will likely need it */
	booपंचांगem_end = (booपंचांगem_end + (2 * SUN3_PMEG_SIZE)) & ~SUN3_PMEG_MASK;

	/* mark all of the pmegs used thus far as reserved */
	क्रम (i=0; i < __pa(booपंचांगem_end) / SUN3_PMEG_SIZE ; ++i)
		pmeg_alloc[i] = 2;


	/* I'm thinking that most of the top pmeg's are going to be
	   used क्रम something, and we probably shouldn't risk it */
	क्रम(num = 0xf0; num <= 0xff; num++)
		pmeg_alloc[num] = 2;

	/* liberate all existing mappings in the rest of kernel space */
	क्रम(seg = booपंचांगem_end; seg < 0x0f800000; seg += SUN3_PMEG_SIZE) अणु
		i = sun3_get_segmap(seg);

		अगर(!pmeg_alloc[i]) अणु
#अगर_घोषित DEBUG_MMU_EMU
			pr_info("freed:");
			prपूर्णांक_pte_vaddr (seg);
#पूर्ण_अगर
			sun3_put_segmap(seg, SUN3_INVALID_PMEG);
		पूर्ण
	पूर्ण

	j = 0;
	क्रम (num=0, seg=0x0F800000; seg<0x10000000; seg+=16*PAGE_SIZE) अणु
		अगर (sun3_get_segmap (seg) != SUN3_INVALID_PMEG) अणु
#अगर_घोषित DEBUG_PROM_MAPS
			क्रम(i = 0; i < 16; i++) अणु
				pr_info("mapped:");
				prपूर्णांक_pte_vaddr (seg + (i*PAGE_SIZE));
				अवरोध;
			पूर्ण
#पूर्ण_अगर
			// the lowest mapping here is the end of our
			// vदो_स्मृति region
			अगर (!m68k_vदो_स्मृति_end)
				m68k_vदो_स्मृति_end = seg;

			// mark the segmap alloc'd, and reserve any
			// of the first 0xbff pages the hardware is
			// alपढ़ोy using...  करोes any sun3 support > 24mb?
			pmeg_alloc[sun3_get_segmap(seg)] = 2;
		पूर्ण
	पूर्ण

	dvma_init();


	/* blank everything below the kernel, and we've got the base
	   mapping to start all the contexts off with... */
	क्रम(seg = 0; seg < PAGE_OFFSET; seg += SUN3_PMEG_SIZE)
		sun3_put_segmap(seg, SUN3_INVALID_PMEG);

	set_fs(MAKE_MM_SEG(3));
	क्रम(seg = 0; seg < 0x10000000; seg += SUN3_PMEG_SIZE) अणु
		i = sun3_get_segmap(seg);
		क्रम(j = 1; j < CONTEXTS_NUM; j++)
			(*(romvec->pv_setctxt))(j, (व्योम *)seg, i);
	पूर्ण
	set_fs(KERNEL_DS);

पूर्ण

/* erase the mappings क्रम a dead context.  Uses the pg_dir क्रम hपूर्णांकs
   as the pmeg tables proved somewhat unreliable, and unmapping all of
   TASK_SIZE was much slower and no more stable. */
/* toकरो: find a better way to keep track of the pmegs used by a
   context क्रम when they're cleared */
व्योम clear_context(अचिन्हित दीर्घ context)
अणु
     अचिन्हित अक्षर oldctx;
     अचिन्हित दीर्घ i;

     अगर(context) अणु
	     अगर(!ctx_alloc[context])
		     panic("clear_context: context not allocated\n");

	     ctx_alloc[context]->context = SUN3_INVALID_CONTEXT;
	     ctx_alloc[context] = (काष्ठा mm_काष्ठा *)0;
	     ctx_avail++;
     पूर्ण

     oldctx = sun3_get_context();

     sun3_put_context(context);

     क्रम(i = 0; i < SUN3_INVALID_PMEG; i++) अणु
	     अगर((pmeg_ctx[i] == context) && (pmeg_alloc[i] == 1)) अणु
		     sun3_put_segmap(pmeg_vaddr[i], SUN3_INVALID_PMEG);
		     pmeg_ctx[i] = 0;
		     pmeg_alloc[i] = 0;
		     pmeg_vaddr[i] = 0;
	     पूर्ण
     पूर्ण

     sun3_put_context(oldctx);
पूर्ण

/* माला_लो an empty context.  अगर full, समाप्तs the next context listed to
   die first */
/* This context invalidation scheme is, well, totally arbitrary, I'm
   sure it could be much more पूर्णांकelligent...  but it माला_लो the job करोne
   क्रम now without much overhead in making it's decision. */
/* toकरो: come up with optimized scheme क्रम flushing contexts */
अचिन्हित दीर्घ get_मुक्त_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ new = 1;
	अटल अचिन्हित अक्षर next_to_die = 1;

	अगर(!ctx_avail) अणु
		/* समाप्त someone to get our context */
		new = next_to_die;
		clear_context(new);
		next_to_die = (next_to_die + 1) & 0x7;
		अगर(!next_to_die)
			next_to_die++;
	पूर्ण अन्यथा अणु
		जबतक(new < CONTEXTS_NUM) अणु
			अगर(ctx_alloc[new])
				new++;
			अन्यथा
				अवरोध;
		पूर्ण
		// check to make sure one was really मुक्त...
		अगर(new == CONTEXTS_NUM)
			panic("get_free_context: failed to find free context");
	पूर्ण

	ctx_alloc[new] = mm;
	ctx_avail--;

	वापस new;
पूर्ण

/*
 * Dynamically select a `spare' PMEG and use it to map virtual `vaddr' in
 * `context'. Maintain internal PMEG management structures. This doesn't
 * actually map the physical address, but करोes clear the old mappings.
 */
//toकरो: better allocation scheme? but is extra complनिकासy worthजबतक?
//toकरो: only clear old entries अगर necessary? how to tell?

अंतरभूत व्योम mmu_emu_map_pmeg (पूर्णांक context, पूर्णांक vaddr)
अणु
	अटल अचिन्हित अक्षर curr_pmeg = 128;
	पूर्णांक i;

	/* Round address to PMEG boundary. */
	vaddr &= ~SUN3_PMEG_MASK;

	/* Find a spare one. */
	जबतक (pmeg_alloc[curr_pmeg] == 2)
		++curr_pmeg;


#अगर_घोषित DEBUG_MMU_EMU
	pr_info("mmu_emu_map_pmeg: pmeg %x to context %d vaddr %x\n",
		curr_pmeg, context, vaddr);
#पूर्ण_अगर

	/* Invalidate old mapping क्रम the pmeg, अगर any */
	अगर (pmeg_alloc[curr_pmeg] == 1) अणु
		sun3_put_context(pmeg_ctx[curr_pmeg]);
		sun3_put_segmap (pmeg_vaddr[curr_pmeg], SUN3_INVALID_PMEG);
		sun3_put_context(context);
	पूर्ण

	/* Update PMEG management काष्ठाures. */
	// करोn't take pmeg's away from the kernel...
	अगर(vaddr >= PAGE_OFFSET) अणु
		/* map kernel pmegs पूर्णांकo all contexts */
		अचिन्हित अक्षर i;

		क्रम(i = 0; i < CONTEXTS_NUM; i++) अणु
			sun3_put_context(i);
			sun3_put_segmap (vaddr, curr_pmeg);
		पूर्ण
		sun3_put_context(context);
		pmeg_alloc[curr_pmeg] = 2;
		pmeg_ctx[curr_pmeg] = 0;

	पूर्ण
	अन्यथा अणु
		pmeg_alloc[curr_pmeg] = 1;
		pmeg_ctx[curr_pmeg] = context;
		sun3_put_segmap (vaddr, curr_pmeg);

	पूर्ण
	pmeg_vaddr[curr_pmeg] = vaddr;

	/* Set hardware mapping and clear the old PTE entries. */
	क्रम (i=0; i<SUN3_PMEG_SIZE; i+=SUN3_PTE_SIZE)
		sun3_put_pte (vaddr + i, SUN3_PAGE_SYSTEM);

	/* Consider a dअगरferent one next समय. */
	++curr_pmeg;
पूर्ण

/*
 * Handle a pagefault at भव address `vaddr'; check अगर there should be a
 * page there (specअगरically, whether the software pagetables indicate that
 * there is). This is necessary due to the limited size of the second-level
 * Sun3 hardware pagetables (256 groups of 16 pages). If there should be a
 * mapping present, we select a `spare' PMEG and use it to create a mapping.
 * `पढ़ो_flag' is nonzero क्रम a पढ़ो fault; zero क्रम a ग_लिखो. Returns nonzero
 * अगर we successfully handled the fault.
 */
//toकरो: should we bump minor pagefault counter? अगर so, here or in caller?
//toकरो: possibly अंतरभूत this पूर्णांकo bus_error030 in <यंत्र/buserror.h> ?

// kernel_fault is set when a kernel page couldn't be demand mapped,
// and क्रमces another try using the kernel page table.  basically a
// hack so that vदो_स्मृति would work correctly.

पूर्णांक mmu_emu_handle_fault (अचिन्हित दीर्घ vaddr, पूर्णांक पढ़ो_flag, पूर्णांक kernel_fault)
अणु
	अचिन्हित दीर्घ segment, offset;
	अचिन्हित अक्षर context;
	pte_t *pte;
	pgd_t * crp;

	अगर(current->mm == शून्य) अणु
		crp = swapper_pg_dir;
		context = 0;
	पूर्ण अन्यथा अणु
		context = current->mm->context;
		अगर(kernel_fault)
			crp = swapper_pg_dir;
		अन्यथा
			crp = current->mm->pgd;
	पूर्ण

#अगर_घोषित DEBUG_MMU_EMU
	pr_info("mmu_emu_handle_fault: vaddr=%lx type=%s crp=%p\n",
		vaddr, पढ़ो_flag ? "read" : "write", crp);
#पूर्ण_अगर

	segment = (vaddr >> SUN3_PMEG_SIZE_BITS) & 0x7FF;
	offset  = (vaddr >> SUN3_PTE_SIZE_BITS) & 0xF;

#अगर_घोषित DEBUG_MMU_EMU
	pr_info("mmu_emu_handle_fault: segment=%lx offset=%lx\n", segment,
		offset);
#पूर्ण_अगर

	pte = (pte_t *) pgd_val (*(crp + segment));

//toकरो: next line should check क्रम valid pmd properly.
	अगर (!pte) अणु
//                pr_info("mmu_emu_handle_fault: invalid pmd\n");
                वापस 0;
        पूर्ण

	pte = (pte_t *) __va ((अचिन्हित दीर्घ)(pte + offset));

	/* Make sure this is a valid page */
	अगर (!(pte_val (*pte) & SUN3_PAGE_VALID))
		वापस 0;

	/* Make sure there's a pmeg allocated क्रम the page */
	अगर (sun3_get_segmap (vaddr&~SUN3_PMEG_MASK) == SUN3_INVALID_PMEG)
		mmu_emu_map_pmeg (context, vaddr);

	/* Write the pte value to hardware MMU */
	sun3_put_pte (vaddr&PAGE_MASK, pte_val (*pte));

	/* Update software copy of the pte value */
// I'm not sure this is necessary. If this is required, we ought to simply
// copy this out when we reuse the PMEG or at some other convenient समय.
// Doing it here is fairly meaningless, anyway, as we only know about the
// first access to a given page. --m
	अगर (!पढ़ो_flag) अणु
		अगर (pte_val (*pte) & SUN3_PAGE_WRITEABLE)
			pte_val (*pte) |= (SUN3_PAGE_ACCESSED
					   | SUN3_PAGE_MODIFIED);
		अन्यथा
			वापस 0;	/* Write-protect error. */
	पूर्ण अन्यथा
		pte_val (*pte) |= SUN3_PAGE_ACCESSED;

#अगर_घोषित DEBUG_MMU_EMU
	pr_info("seg:%ld crp:%p ->", get_fs().seg, crp);
	prपूर्णांक_pte_vaddr (vaddr);
	pr_cont("\n");
#पूर्ण_अगर

	वापस 1;
पूर्ण
