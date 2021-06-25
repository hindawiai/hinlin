<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic stack depot क्रम storing stack traces.
 *
 * Some debugging tools need to save stack traces of certain events which can
 * be later presented to the user. For example, KASAN needs to safe alloc and
 * मुक्त stacks क्रम each object, but storing two stack traces per object
 * requires too much memory (e.g. SLUB_DEBUG needs 256 bytes per object क्रम
 * that).
 *
 * Instead, stack depot मुख्यtains a hashtable of unique stacktraces. Since alloc
 * and मुक्त stacks repeat a lot, we save about 100x space.
 * Stacks are never हटाओd from depot, so we store them contiguously one after
 * another in a contiguos memory allocation.
 *
 * Author: Alexander Potapenko <glider@google.com>
 * Copyright (C) 2016 Google, Inc.
 *
 * Based on code by Dmitry Chernenkov.
 */

#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jhash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/stackdepot.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/memblock.h>

#घोषणा DEPOT_STACK_BITS (माप(depot_stack_handle_t) * 8)

#घोषणा STACK_ALLOC_शून्य_PROTECTION_BITS 1
#घोषणा STACK_ALLOC_ORDER 2 /* 'Slab' size order क्रम stack depot, 4 pages */
#घोषणा STACK_ALLOC_SIZE (1LL << (PAGE_SHIFT + STACK_ALLOC_ORDER))
#घोषणा STACK_ALLOC_ALIGN 4
#घोषणा STACK_ALLOC_OFFSET_BITS (STACK_ALLOC_ORDER + PAGE_SHIFT - \
					STACK_ALLOC_ALIGN)
#घोषणा STACK_ALLOC_INDEX_BITS (DEPOT_STACK_BITS - \
		STACK_ALLOC_शून्य_PROTECTION_BITS - STACK_ALLOC_OFFSET_BITS)
#घोषणा STACK_ALLOC_SLABS_CAP 8192
#घोषणा STACK_ALLOC_MAX_SLABS \
	(((1LL << (STACK_ALLOC_INDEX_BITS)) < STACK_ALLOC_SLABS_CAP) ? \
	 (1LL << (STACK_ALLOC_INDEX_BITS)) : STACK_ALLOC_SLABS_CAP)

/* The compact काष्ठाure to store the reference to stacks. */
जोड़ handle_parts अणु
	depot_stack_handle_t handle;
	काष्ठा अणु
		u32 slabindex : STACK_ALLOC_INDEX_BITS;
		u32 offset : STACK_ALLOC_OFFSET_BITS;
		u32 valid : STACK_ALLOC_शून्य_PROTECTION_BITS;
	पूर्ण;
पूर्ण;

काष्ठा stack_record अणु
	काष्ठा stack_record *next;	/* Link in the hashtable */
	u32 hash;			/* Hash in the hastable */
	u32 size;			/* Number of frames in the stack */
	जोड़ handle_parts handle;
	अचिन्हित दीर्घ entries[];	/* Variable-sized array of entries. */
पूर्ण;

अटल व्योम *stack_sद_असल[STACK_ALLOC_MAX_SLABS];

अटल पूर्णांक depot_index;
अटल पूर्णांक next_slab_inited;
अटल माप_प्रकार depot_offset;
अटल DEFINE_RAW_SPINLOCK(depot_lock);

अटल bool init_stack_slab(व्योम **pपुनः_स्मृति)
अणु
	अगर (!*pपुनः_स्मृति)
		वापस false;
	/*
	 * This smp_load_acquire() pairs with smp_store_release() to
	 * |next_slab_inited| below and in depot_alloc_stack().
	 */
	अगर (smp_load_acquire(&next_slab_inited))
		वापस true;
	अगर (stack_sद_असल[depot_index] == शून्य) अणु
		stack_sद_असल[depot_index] = *pपुनः_स्मृति;
		*pपुनः_स्मृति = शून्य;
	पूर्ण अन्यथा अणु
		/* If this is the last depot slab, करो not touch the next one. */
		अगर (depot_index + 1 < STACK_ALLOC_MAX_SLABS) अणु
			stack_sद_असल[depot_index + 1] = *pपुनः_स्मृति;
			*pपुनः_स्मृति = शून्य;
		पूर्ण
		/*
		 * This smp_store_release pairs with smp_load_acquire() from
		 * |next_slab_inited| above and in stack_depot_save().
		 */
		smp_store_release(&next_slab_inited, 1);
	पूर्ण
	वापस true;
पूर्ण

/* Allocation of a new stack in raw storage */
अटल काष्ठा stack_record *depot_alloc_stack(अचिन्हित दीर्घ *entries, पूर्णांक size,
		u32 hash, व्योम **pपुनः_स्मृति, gfp_t alloc_flags)
अणु
	काष्ठा stack_record *stack;
	माप_प्रकार required_size = काष्ठा_size(stack, entries, size);

	required_size = ALIGN(required_size, 1 << STACK_ALLOC_ALIGN);

	अगर (unlikely(depot_offset + required_size > STACK_ALLOC_SIZE)) अणु
		अगर (unlikely(depot_index + 1 >= STACK_ALLOC_MAX_SLABS)) अणु
			WARN_ONCE(1, "Stack depot reached limit capacity");
			वापस शून्य;
		पूर्ण
		depot_index++;
		depot_offset = 0;
		/*
		 * smp_store_release() here pairs with smp_load_acquire() from
		 * |next_slab_inited| in stack_depot_save() and
		 * init_stack_slab().
		 */
		अगर (depot_index + 1 < STACK_ALLOC_MAX_SLABS)
			smp_store_release(&next_slab_inited, 0);
	पूर्ण
	init_stack_slab(pपुनः_स्मृति);
	अगर (stack_sद_असल[depot_index] == शून्य)
		वापस शून्य;

	stack = stack_sद_असल[depot_index] + depot_offset;

	stack->hash = hash;
	stack->size = size;
	stack->handle.slabindex = depot_index;
	stack->handle.offset = depot_offset >> STACK_ALLOC_ALIGN;
	stack->handle.valid = 1;
	स_नकल(stack->entries, entries, flex_array_size(stack, entries, size));
	depot_offset += required_size;

	वापस stack;
पूर्ण

#घोषणा STACK_HASH_SIZE (1L << CONFIG_STACK_HASH_ORDER)
#घोषणा STACK_HASH_MASK (STACK_HASH_SIZE - 1)
#घोषणा STACK_HASH_SEED 0x9747b28c

अटल bool stack_depot_disable;
अटल काष्ठा stack_record **stack_table;

अटल पूर्णांक __init is_stack_depot_disabled(अक्षर *str)
अणु
	पूर्णांक ret;

	ret = kstrtobool(str, &stack_depot_disable);
	अगर (!ret && stack_depot_disable) अणु
		pr_info("Stack Depot is disabled\n");
		stack_table = शून्य;
	पूर्ण
	वापस 0;
पूर्ण
early_param("stack_depot_disable", is_stack_depot_disabled);

पूर्णांक __init stack_depot_init(व्योम)
अणु
	अगर (!stack_depot_disable) अणु
		माप_प्रकार size = (STACK_HASH_SIZE * माप(काष्ठा stack_record *));
		पूर्णांक i;

		stack_table = memblock_alloc(size, size);
		क्रम (i = 0; i < STACK_HASH_SIZE;  i++)
			stack_table[i] = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

/* Calculate hash क्रम a stack */
अटल अंतरभूत u32 hash_stack(अचिन्हित दीर्घ *entries, अचिन्हित पूर्णांक size)
अणु
	वापस jhash2((u32 *)entries,
		      array_size(size,  माप(*entries)) / माप(u32),
		      STACK_HASH_SEED);
पूर्ण

/* Use our own, non-instrumented version of स_भेद().
 *
 * We actually करोn't care about the order, just the equality.
 */
अटल अंतरभूत
पूर्णांक stackdepot_स_भेद(स्थिर अचिन्हित दीर्घ *u1, स्थिर अचिन्हित दीर्घ *u2,
			अचिन्हित पूर्णांक n)
अणु
	क्रम ( ; n-- ; u1++, u2++) अणु
		अगर (*u1 != *u2)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Find a stack that is equal to the one stored in entries in the hash */
अटल अंतरभूत काष्ठा stack_record *find_stack(काष्ठा stack_record *bucket,
					     अचिन्हित दीर्घ *entries, पूर्णांक size,
					     u32 hash)
अणु
	काष्ठा stack_record *found;

	क्रम (found = bucket; found; found = found->next) अणु
		अगर (found->hash == hash &&
		    found->size == size &&
		    !stackdepot_स_भेद(entries, found->entries, size))
			वापस found;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * stack_depot_fetch - Fetch stack entries from a depot
 *
 * @handle:		Stack depot handle which was वापसed from
 *			stack_depot_save().
 * @entries:		Poपूर्णांकer to store the entries address
 *
 * Return: The number of trace entries क्रम this depot.
 */
अचिन्हित पूर्णांक stack_depot_fetch(depot_stack_handle_t handle,
			       अचिन्हित दीर्घ **entries)
अणु
	जोड़ handle_parts parts = अणु .handle = handle पूर्ण;
	व्योम *slab;
	माप_प्रकार offset = parts.offset << STACK_ALLOC_ALIGN;
	काष्ठा stack_record *stack;

	*entries = शून्य;
	अगर (parts.slabindex > depot_index) अणु
		WARN(1, "slab index %d out of bounds (%d) for stack id %08x\n",
			parts.slabindex, depot_index, handle);
		वापस 0;
	पूर्ण
	slab = stack_sद_असल[parts.slabindex];
	अगर (!slab)
		वापस 0;
	stack = slab + offset;

	*entries = stack->entries;
	वापस stack->size;
पूर्ण
EXPORT_SYMBOL_GPL(stack_depot_fetch);

/**
 * stack_depot_save - Save a stack trace from an array
 *
 * @entries:		Poपूर्णांकer to storage array
 * @nr_entries:		Size of the storage array
 * @alloc_flags:	Allocation gfp flags
 *
 * Return: The handle of the stack काष्ठा stored in depot
 */
depot_stack_handle_t stack_depot_save(अचिन्हित दीर्घ *entries,
				      अचिन्हित पूर्णांक nr_entries,
				      gfp_t alloc_flags)
अणु
	काष्ठा stack_record *found = शून्य, **bucket;
	depot_stack_handle_t retval = 0;
	काष्ठा page *page = शून्य;
	व्योम *pपुनः_स्मृति = शून्य;
	अचिन्हित दीर्घ flags;
	u32 hash;

	अगर (unlikely(nr_entries == 0) || stack_depot_disable)
		जाओ fast_निकास;

	hash = hash_stack(entries, nr_entries);
	bucket = &stack_table[hash & STACK_HASH_MASK];

	/*
	 * Fast path: look the stack trace up without locking.
	 * The smp_load_acquire() here pairs with smp_store_release() to
	 * |bucket| below.
	 */
	found = find_stack(smp_load_acquire(bucket), entries,
			   nr_entries, hash);
	अगर (found)
		जाओ निकास;

	/*
	 * Check अगर the current or the next stack slab need to be initialized.
	 * If so, allocate the memory - we won't be able to करो that under the
	 * lock.
	 *
	 * The smp_load_acquire() here pairs with smp_store_release() to
	 * |next_slab_inited| in depot_alloc_stack() and init_stack_slab().
	 */
	अगर (unlikely(!smp_load_acquire(&next_slab_inited))) अणु
		/*
		 * Zero out zone modअगरiers, as we करोn't have specअगरic zone
		 * requirements. Keep the flags related to allocation in atomic
		 * contexts and I/O.
		 */
		alloc_flags &= ~GFP_ZONEMASK;
		alloc_flags &= (GFP_ATOMIC | GFP_KERNEL);
		alloc_flags |= __GFP_NOWARN;
		page = alloc_pages(alloc_flags, STACK_ALLOC_ORDER);
		अगर (page)
			pपुनः_स्मृति = page_address(page);
	पूर्ण

	raw_spin_lock_irqsave(&depot_lock, flags);

	found = find_stack(*bucket, entries, nr_entries, hash);
	अगर (!found) अणु
		काष्ठा stack_record *new =
			depot_alloc_stack(entries, nr_entries,
					  hash, &pपुनः_स्मृति, alloc_flags);
		अगर (new) अणु
			new->next = *bucket;
			/*
			 * This smp_store_release() pairs with
			 * smp_load_acquire() from |bucket| above.
			 */
			smp_store_release(bucket, new);
			found = new;
		पूर्ण
	पूर्ण अन्यथा अगर (pपुनः_स्मृति) अणु
		/*
		 * We didn't need to store this stack trace, but let's keep
		 * the pपुनः_स्मृतिated memory क्रम the future.
		 */
		WARN_ON(!init_stack_slab(&pपुनः_स्मृति));
	पूर्ण

	raw_spin_unlock_irqrestore(&depot_lock, flags);
निकास:
	अगर (pपुनः_स्मृति) अणु
		/* Nobody used this memory, ok to मुक्त it. */
		मुक्त_pages((अचिन्हित दीर्घ)pपुनः_स्मृति, STACK_ALLOC_ORDER);
	पूर्ण
	अगर (found)
		retval = found->handle.handle;
fast_निकास:
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(stack_depot_save);

अटल अंतरभूत पूर्णांक in_irqentry_text(अचिन्हित दीर्घ ptr)
अणु
	वापस (ptr >= (अचिन्हित दीर्घ)&__irqentry_text_start &&
		ptr < (अचिन्हित दीर्घ)&__irqentry_text_end) ||
		(ptr >= (अचिन्हित दीर्घ)&__softirqentry_text_start &&
		 ptr < (अचिन्हित दीर्घ)&__softirqentry_text_end);
पूर्ण

अचिन्हित पूर्णांक filter_irq_stacks(अचिन्हित दीर्घ *entries,
					     अचिन्हित पूर्णांक nr_entries)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nr_entries; i++) अणु
		अगर (in_irqentry_text(entries[i])) अणु
			/* Include the irqentry function पूर्णांकo the stack. */
			वापस i + 1;
		पूर्ण
	पूर्ण
	वापस nr_entries;
पूर्ण
EXPORT_SYMBOL_GPL(filter_irq_stacks);
