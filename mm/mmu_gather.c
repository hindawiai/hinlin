<शैली गुरु>
#समावेश <linux/gfp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/smp.h>
#समावेश <linux/swap.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlb.h>

#अगर_अघोषित CONFIG_MMU_GATHER_NO_GATHER

अटल bool tlb_next_batch(काष्ठा mmu_gather *tlb)
अणु
	काष्ठा mmu_gather_batch *batch;

	batch = tlb->active;
	अगर (batch->next) अणु
		tlb->active = batch->next;
		वापस true;
	पूर्ण

	अगर (tlb->batch_count == MAX_GATHER_BATCH_COUNT)
		वापस false;

	batch = (व्योम *)__get_मुक्त_pages(GFP_NOWAIT | __GFP_NOWARN, 0);
	अगर (!batch)
		वापस false;

	tlb->batch_count++;
	batch->next = शून्य;
	batch->nr   = 0;
	batch->max  = MAX_GATHER_BATCH;

	tlb->active->next = batch;
	tlb->active = batch;

	वापस true;
पूर्ण

अटल व्योम tlb_batch_pages_flush(काष्ठा mmu_gather *tlb)
अणु
	काष्ठा mmu_gather_batch *batch;

	क्रम (batch = &tlb->local; batch && batch->nr; batch = batch->next) अणु
		मुक्त_pages_and_swap_cache(batch->pages, batch->nr);
		batch->nr = 0;
	पूर्ण
	tlb->active = &tlb->local;
पूर्ण

अटल व्योम tlb_batch_list_मुक्त(काष्ठा mmu_gather *tlb)
अणु
	काष्ठा mmu_gather_batch *batch, *next;

	क्रम (batch = tlb->local.next; batch; batch = next) अणु
		next = batch->next;
		मुक्त_pages((अचिन्हित दीर्घ)batch, 0);
	पूर्ण
	tlb->local.next = शून्य;
पूर्ण

bool __tlb_हटाओ_page_size(काष्ठा mmu_gather *tlb, काष्ठा page *page, पूर्णांक page_size)
अणु
	काष्ठा mmu_gather_batch *batch;

	VM_BUG_ON(!tlb->end);

#अगर_घोषित CONFIG_MMU_GATHER_PAGE_SIZE
	VM_WARN_ON(tlb->page_size != page_size);
#पूर्ण_अगर

	batch = tlb->active;
	/*
	 * Add the page and check अगर we are full. If so
	 * क्रमce a flush.
	 */
	batch->pages[batch->nr++] = page;
	अगर (batch->nr == batch->max) अणु
		अगर (!tlb_next_batch(tlb))
			वापस true;
		batch = tlb->active;
	पूर्ण
	VM_BUG_ON_PAGE(batch->nr > batch->max, page);

	वापस false;
पूर्ण

#पूर्ण_अगर /* MMU_GATHER_NO_GATHER */

#अगर_घोषित CONFIG_MMU_GATHER_TABLE_FREE

अटल व्योम __tlb_हटाओ_table_मुक्त(काष्ठा mmu_table_batch *batch)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < batch->nr; i++)
		__tlb_हटाओ_table(batch->tables[i]);

	मुक्त_page((अचिन्हित दीर्घ)batch);
पूर्ण

#अगर_घोषित CONFIG_MMU_GATHER_RCU_TABLE_FREE

/*
 * Semi RCU मुक्तing of the page directories.
 *
 * This is needed by some architectures to implement software pagetable walkers.
 *
 * gup_fast() and other software pagetable walkers करो a lockless page-table
 * walk and thereक्रमe needs some synchronization with the मुक्तing of the page
 * directories. The chosen means to accomplish that is by disabling IRQs over
 * the walk.
 *
 * Architectures that use IPIs to flush TLBs will then स्वतःmagically DTRT,
 * since we unlink the page, flush TLBs, मुक्त the page. Since the disabling of
 * IRQs delays the completion of the TLB flush we can never observe an alपढ़ोy
 * मुक्तd page.
 *
 * Architectures that करो not have this (PPC) need to delay the मुक्तing by some
 * other means, this is that means.
 *
 * What we करो is batch the मुक्तd directory pages (tables) and RCU मुक्त them.
 * We use the sched RCU variant, as that guarantees that IRQ/preempt disabling
 * holds off grace periods.
 *
 * However, in order to batch these pages we need to allocate storage, this
 * allocation is deep inside the MM code and can thus easily fail on memory
 * pressure. To guarantee progress we fall back to single table मुक्तing, see
 * the implementation of tlb_हटाओ_table_one().
 *
 */

अटल व्योम tlb_हटाओ_table_smp_sync(व्योम *arg)
अणु
	/* Simply deliver the पूर्णांकerrupt */
पूर्ण

अटल व्योम tlb_हटाओ_table_sync_one(व्योम)
अणु
	/*
	 * This isn't an RCU grace period and hence the page-tables cannot be
	 * assumed to be actually RCU-मुक्तd.
	 *
	 * It is however sufficient क्रम software page-table walkers that rely on
	 * IRQ disabling.
	 */
	smp_call_function(tlb_हटाओ_table_smp_sync, शून्य, 1);
पूर्ण

अटल व्योम tlb_हटाओ_table_rcu(काष्ठा rcu_head *head)
अणु
	__tlb_हटाओ_table_मुक्त(container_of(head, काष्ठा mmu_table_batch, rcu));
पूर्ण

अटल व्योम tlb_हटाओ_table_मुक्त(काष्ठा mmu_table_batch *batch)
अणु
	call_rcu(&batch->rcu, tlb_हटाओ_table_rcu);
पूर्ण

#अन्यथा /* !CONFIG_MMU_GATHER_RCU_TABLE_FREE */

अटल व्योम tlb_हटाओ_table_sync_one(व्योम) अणु पूर्ण

अटल व्योम tlb_हटाओ_table_मुक्त(काष्ठा mmu_table_batch *batch)
अणु
	__tlb_हटाओ_table_मुक्त(batch);
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU_GATHER_RCU_TABLE_FREE */

/*
 * If we want tlb_हटाओ_table() to imply TLB invalidates.
 */
अटल अंतरभूत व्योम tlb_table_invalidate(काष्ठा mmu_gather *tlb)
अणु
	अगर (tlb_needs_table_invalidate()) अणु
		/*
		 * Invalidate page-table caches used by hardware walkers. Then
		 * we still need to RCU-sched रुको जबतक मुक्तing the pages
		 * because software walkers can still be in-flight.
		 */
		tlb_flush_mmu_tlbonly(tlb);
	पूर्ण
पूर्ण

अटल व्योम tlb_हटाओ_table_one(व्योम *table)
अणु
	tlb_हटाओ_table_sync_one();
	__tlb_हटाओ_table(table);
पूर्ण

अटल व्योम tlb_table_flush(काष्ठा mmu_gather *tlb)
अणु
	काष्ठा mmu_table_batch **batch = &tlb->batch;

	अगर (*batch) अणु
		tlb_table_invalidate(tlb);
		tlb_हटाओ_table_मुक्त(*batch);
		*batch = शून्य;
	पूर्ण
पूर्ण

व्योम tlb_हटाओ_table(काष्ठा mmu_gather *tlb, व्योम *table)
अणु
	काष्ठा mmu_table_batch **batch = &tlb->batch;

	अगर (*batch == शून्य) अणु
		*batch = (काष्ठा mmu_table_batch *)__get_मुक्त_page(GFP_NOWAIT | __GFP_NOWARN);
		अगर (*batch == शून्य) अणु
			tlb_table_invalidate(tlb);
			tlb_हटाओ_table_one(table);
			वापस;
		पूर्ण
		(*batch)->nr = 0;
	पूर्ण

	(*batch)->tables[(*batch)->nr++] = table;
	अगर ((*batch)->nr == MAX_TABLE_BATCH)
		tlb_table_flush(tlb);
पूर्ण

अटल अंतरभूत व्योम tlb_table_init(काष्ठा mmu_gather *tlb)
अणु
	tlb->batch = शून्य;
पूर्ण

#अन्यथा /* !CONFIG_MMU_GATHER_TABLE_FREE */

अटल अंतरभूत व्योम tlb_table_flush(काष्ठा mmu_gather *tlb) अणु पूर्ण
अटल अंतरभूत व्योम tlb_table_init(काष्ठा mmu_gather *tlb) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_MMU_GATHER_TABLE_FREE */

अटल व्योम tlb_flush_mmu_मुक्त(काष्ठा mmu_gather *tlb)
अणु
	tlb_table_flush(tlb);
#अगर_अघोषित CONFIG_MMU_GATHER_NO_GATHER
	tlb_batch_pages_flush(tlb);
#पूर्ण_अगर
पूर्ण

व्योम tlb_flush_mmu(काष्ठा mmu_gather *tlb)
अणु
	tlb_flush_mmu_tlbonly(tlb);
	tlb_flush_mmu_मुक्त(tlb);
पूर्ण

अटल व्योम __tlb_gather_mmu(काष्ठा mmu_gather *tlb, काष्ठा mm_काष्ठा *mm,
			     bool fullmm)
अणु
	tlb->mm = mm;
	tlb->fullmm = fullmm;

#अगर_अघोषित CONFIG_MMU_GATHER_NO_GATHER
	tlb->need_flush_all = 0;
	tlb->local.next = शून्य;
	tlb->local.nr   = 0;
	tlb->local.max  = ARRAY_SIZE(tlb->__pages);
	tlb->active     = &tlb->local;
	tlb->batch_count = 0;
#पूर्ण_अगर

	tlb_table_init(tlb);
#अगर_घोषित CONFIG_MMU_GATHER_PAGE_SIZE
	tlb->page_size = 0;
#पूर्ण_अगर

	__tlb_reset_range(tlb);
	inc_tlb_flush_pending(tlb->mm);
पूर्ण

/**
 * tlb_gather_mmu - initialize an mmu_gather काष्ठाure क्रम page-table tear-करोwn
 * @tlb: the mmu_gather काष्ठाure to initialize
 * @mm: the mm_काष्ठा of the target address space
 *
 * Called to initialize an (on-stack) mmu_gather काष्ठाure क्रम page-table
 * tear-करोwn from @mm.
 */
व्योम tlb_gather_mmu(काष्ठा mmu_gather *tlb, काष्ठा mm_काष्ठा *mm)
अणु
	__tlb_gather_mmu(tlb, mm, false);
पूर्ण

/**
 * tlb_gather_mmu_fullmm - initialize an mmu_gather काष्ठाure क्रम page-table tear-करोwn
 * @tlb: the mmu_gather काष्ठाure to initialize
 * @mm: the mm_काष्ठा of the target address space
 *
 * In this हाल, @mm is without users and we're going to destroy the
 * full address space (निकास/execve).
 *
 * Called to initialize an (on-stack) mmu_gather काष्ठाure क्रम page-table
 * tear-करोwn from @mm.
 */
व्योम tlb_gather_mmu_fullmm(काष्ठा mmu_gather *tlb, काष्ठा mm_काष्ठा *mm)
अणु
	__tlb_gather_mmu(tlb, mm, true);
पूर्ण

/**
 * tlb_finish_mmu - finish an mmu_gather काष्ठाure
 * @tlb: the mmu_gather काष्ठाure to finish
 *
 * Called at the end of the shootकरोwn operation to मुक्त up any resources that
 * were required.
 */
व्योम tlb_finish_mmu(काष्ठा mmu_gather *tlb)
अणु
	/*
	 * If there are parallel thपढ़ोs are करोing PTE changes on same range
	 * under non-exclusive lock (e.g., mmap_lock पढ़ो-side) but defer TLB
	 * flush by batching, one thपढ़ो may end up seeing inconsistent PTEs
	 * and result in having stale TLB entries.  So flush TLB क्रमcefully
	 * अगर we detect parallel PTE batching thपढ़ोs.
	 *
	 * However, some syscalls, e.g. munmap(), may मुक्त page tables, this
	 * needs क्रमce flush everything in the given range. Otherwise this
	 * may result in having stale TLB entries क्रम some architectures,
	 * e.g. aarch64, that could specअगरy flush what level TLB.
	 */
	अगर (mm_tlb_flush_nested(tlb->mm)) अणु
		/*
		 * The aarch64 yields better perक्रमmance with fullmm by
		 * aव्योमing multiple CPUs spamming TLBI messages at the
		 * same समय.
		 *
		 * On x86 non-fullmm करोesn't yield signअगरicant dअगरference
		 * against fullmm.
		 */
		tlb->fullmm = 1;
		__tlb_reset_range(tlb);
		tlb->मुक्तd_tables = 1;
	पूर्ण

	tlb_flush_mmu(tlb);

#अगर_अघोषित CONFIG_MMU_GATHER_NO_GATHER
	tlb_batch_list_मुक्त(tlb);
#पूर्ण_अगर
	dec_tlb_flush_pending(tlb->mm);
पूर्ण
