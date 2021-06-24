<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  MMU context allocation क्रम 64-bit kernels.
 *
 *  Copyright (C) 2004 Anton Blanअक्षरd, IBM Corp. <anton@samba.org>
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/pkeys.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/idr.h>
#समावेश <linux/export.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pgभाग.स>

#समावेश "internal.h"

अटल DEFINE_IDA(mmu_context_ida);

अटल पूर्णांक alloc_context_id(पूर्णांक min_id, पूर्णांक max_id)
अणु
	वापस ida_alloc_range(&mmu_context_ida, min_id, max_id, GFP_KERNEL);
पूर्ण

व्योम hash__reserve_context_id(पूर्णांक id)
अणु
	पूर्णांक result = ida_alloc_range(&mmu_context_ida, id, id, GFP_KERNEL);

	WARN(result != id, "mmu: Failed to reserve context id %d (rc %d)\n", id, result);
पूर्ण

पूर्णांक hash__alloc_context_id(व्योम)
अणु
	अचिन्हित दीर्घ max;

	अगर (mmu_has_feature(MMU_FTR_68_BIT_VA))
		max = MAX_USER_CONTEXT;
	अन्यथा
		max = MAX_USER_CONTEXT_65BIT_VA;

	वापस alloc_context_id(MIN_USER_CONTEXT, max);
पूर्ण
EXPORT_SYMBOL_GPL(hash__alloc_context_id);

अटल पूर्णांक पुनः_स्मृति_context_ids(mm_context_t *ctx)
अणु
	पूर्णांक i, id;

	/*
	 * id 0 (aka. ctx->id) is special, we always allocate a new one, even अगर
	 * there wasn't one allocated previously (which happens in the exec
	 * हाल where ctx is newly allocated).
	 *
	 * We have to be a bit careful here. We must keep the existing ids in
	 * the array, so that we can test अगर they're non-zero to decide अगर we
	 * need to allocate a new one. However in हाल of error we must मुक्त the
	 * ids we've allocated but *not* any of the existing ones (or risk a
	 * UAF). That's why we decrement i at the start of the error handling
	 * loop, to skip the id that we just tested but couldn't पुनः_स्मृतिate.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(ctx->extended_id); i++) अणु
		अगर (i == 0 || ctx->extended_id[i]) अणु
			id = hash__alloc_context_id();
			अगर (id < 0)
				जाओ error;

			ctx->extended_id[i] = id;
		पूर्ण
	पूर्ण

	/* The caller expects us to वापस id */
	वापस ctx->id;

error:
	क्रम (i--; i >= 0; i--) अणु
		अगर (ctx->extended_id[i])
			ida_मुक्त(&mmu_context_ida, ctx->extended_id[i]);
	पूर्ण

	वापस id;
पूर्ण

अटल पूर्णांक hash__init_new_context(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक index;

	mm->context.hash_context = kदो_स्मृति(माप(काष्ठा hash_mm_context),
					   GFP_KERNEL);
	अगर (!mm->context.hash_context)
		वापस -ENOMEM;

	/*
	 * The old code would re-promote on विभाजन, we करोn't करो that when using
	 * slices as it could cause problem promoting slices that have been
	 * क्रमced करोwn to 4K.
	 *
	 * For book3s we have MMU_NO_CONTEXT set to be ~0. Hence check
	 * explicitly against context.id == 0. This ensures that we properly
	 * initialize context slice details क्रम newly allocated mm's (which will
	 * have id == 0) and करोn't alter context slice inherited via विभाजन (which
	 * will have id != 0).
	 *
	 * We should not be calling init_new_context() on init_mm. Hence a
	 * check against 0 is OK.
	 */
	अगर (mm->context.id == 0) अणु
		स_रखो(mm->context.hash_context, 0, माप(काष्ठा hash_mm_context));
		slice_init_new_context_exec(mm);
	पूर्ण अन्यथा अणु
		/* This is विभाजन. Copy hash_context details from current->mm */
		स_नकल(mm->context.hash_context, current->mm->context.hash_context, माप(काष्ठा hash_mm_context));
#अगर_घोषित CONFIG_PPC_SUBPAGE_PROT
		/* inherit subpage prot details अगर we have one. */
		अगर (current->mm->context.hash_context->spt) अणु
			mm->context.hash_context->spt = kदो_स्मृति(माप(काष्ठा subpage_prot_table),
								GFP_KERNEL);
			अगर (!mm->context.hash_context->spt) अणु
				kमुक्त(mm->context.hash_context);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	index = पुनः_स्मृति_context_ids(&mm->context);
	अगर (index < 0) अणु
#अगर_घोषित CONFIG_PPC_SUBPAGE_PROT
		kमुक्त(mm->context.hash_context->spt);
#पूर्ण_अगर
		kमुक्त(mm->context.hash_context);
		वापस index;
	पूर्ण

	pkey_mm_init(mm);
	वापस index;
पूर्ण

व्योम hash__setup_new_exec(व्योम)
अणु
	slice_setup_new_exec();

	slb_setup_new_exec();
पूर्ण

अटल पूर्णांक radix__init_new_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ rts_field;
	पूर्णांक index, max_id;

	max_id = (1 << mmu_pid_bits) - 1;
	index = alloc_context_id(mmu_base_pid, max_id);
	अगर (index < 0)
		वापस index;

	/*
	 * set the process table entry,
	 */
	rts_field = radix__get_tree_size();
	process_tb[index].prtb0 = cpu_to_be64(rts_field | __pa(mm->pgd) | RADIX_PGD_INDEX_SIZE);

	/*
	 * Order the above store with subsequent update of the PID
	 * रेजिस्टर (at which poपूर्णांक HW can start loading/caching
	 * the entry) and the corresponding load by the MMU from
	 * the L2 cache.
	 */
	यंत्र अस्थिर("ptesync;isync" : : : "memory");

	mm->context.hash_context = शून्य;

	वापस index;
पूर्ण

पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक index;

	अगर (radix_enabled())
		index = radix__init_new_context(mm);
	अन्यथा
		index = hash__init_new_context(mm);

	अगर (index < 0)
		वापस index;

	mm->context.id = index;

	mm->context.pte_frag = शून्य;
	mm->context.pmd_frag = शून्य;
#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
	mm_iommu_init(mm);
#पूर्ण_अगर
	atomic_set(&mm->context.active_cpus, 0);
	atomic_set(&mm->context.copros, 0);

	वापस 0;
पूर्ण

व्योम __destroy_context(पूर्णांक context_id)
अणु
	ida_मुक्त(&mmu_context_ida, context_id);
पूर्ण
EXPORT_SYMBOL_GPL(__destroy_context);

अटल व्योम destroy_contexts(mm_context_t *ctx)
अणु
	पूर्णांक index, context_id;

	क्रम (index = 0; index < ARRAY_SIZE(ctx->extended_id); index++) अणु
		context_id = ctx->extended_id[index];
		अगर (context_id)
			ida_मुक्त(&mmu_context_ida, context_id);
	पूर्ण
	kमुक्त(ctx->hash_context);
पूर्ण

अटल व्योम pmd_frag_destroy(व्योम *pmd_frag)
अणु
	पूर्णांक count;
	काष्ठा page *page;

	page = virt_to_page(pmd_frag);
	/* drop all the pending references */
	count = ((अचिन्हित दीर्घ)pmd_frag & ~PAGE_MASK) >> PMD_FRAG_SIZE_SHIFT;
	/* We allow PTE_FRAG_NR fragments from a PTE page */
	अगर (atomic_sub_and_test(PMD_FRAG_NR - count, &page->pt_frag_refcount)) अणु
		pgtable_pmd_page_dtor(page);
		__मुक्त_page(page);
	पूर्ण
पूर्ण

अटल व्योम destroy_pagetable_cache(काष्ठा mm_काष्ठा *mm)
अणु
	व्योम *frag;

	frag = mm->context.pte_frag;
	अगर (frag)
		pte_frag_destroy(frag);

	frag = mm->context.pmd_frag;
	अगर (frag)
		pmd_frag_destroy(frag);
	वापस;
पूर्ण

व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
	WARN_ON_ONCE(!list_empty(&mm->context.iommu_group_mem_list));
#पूर्ण_अगर
	/*
	 * For tasks which were successfully initialized we end up calling
	 * arch_निकास_mmap() which clears the process table entry. And
	 * arch_निकास_mmap() is called beक्रमe the required fullmm TLB flush
	 * which करोes a RIC=2 flush. Hence क्रम an initialized task, we करो clear
	 * any cached process table entries.
	 *
	 * The condition below handles the error हाल during task init. We have
	 * set the process table entry early and अगर we fail a task
	 * initialization, we need to ensure the process table entry is zeroed.
	 * We need not worry about process table entry caches because the task
	 * never ran with the PID value.
	 */
	अगर (radix_enabled())
		process_tb[mm->context.id].prtb0 = 0;
	अन्यथा
		subpage_prot_मुक्त(mm);
	destroy_contexts(&mm->context);
	mm->context.id = MMU_NO_CONTEXT;
पूर्ण

व्योम arch_निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	destroy_pagetable_cache(mm);

	अगर (radix_enabled()) अणु
		/*
		 * Radix करोesn't have a valid bit in the process table
		 * entries. However we know that at least P9 implementation
		 * will aव्योम caching an entry with an invalid RTS field,
		 * and 0 is invalid. So this will करो.
		 *
		 * This runs beक्रमe the "fullmm" tlb flush in निकास_mmap,
		 * which करोes a RIC=2 tlbie to clear the process table
		 * entry. See the "fullmm" comments in tlb-radix.c.
		 *
		 * No barrier required here after the store because
		 * this process will करो the invalidate, which starts with
		 * ptesync.
		 */
		process_tb[mm->context.id].prtb0 = 0;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PPC_RADIX_MMU
व्योम radix__चयन_mmu_context(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next)
अणु
	mtspr(SPRN_PID, next->context.id);
	isync();
पूर्ण
#पूर्ण_अगर

/**
 * cleanup_cpu_mmu_context - Clean up MMU details क्रम this CPU (newly offlined)
 *
 * This clears the CPU from mm_cpumask क्रम all processes, and then flushes the
 * local TLB to ensure TLB coherency in हाल the CPU is onlined again.
 *
 * KVM guest translations are not necessarily flushed here. If KVM started
 * using mm_cpumask or the Linux APIs which करो, this would have to be resolved.
 */
#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम cleanup_cpu_mmu_context(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	clear_tasks_mm_cpumask(cpu);
	tlbiel_all();
पूर्ण
#पूर्ण_अगर
