<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Kernel Electric-Fence (KFENCE). For more info please see
 * Documentation/dev-tools/kfence.rst.
 *
 * Copyright (C) 2020, Google LLC.
 */

#अगर_अघोषित MM_KFENCE_KFENCE_H
#घोषणा MM_KFENCE_KFENCE_H

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश "../slab.h" /* क्रम काष्ठा kmem_cache */

/*
 * Get the canary byte pattern क्रम @addr. Use a pattern that varies based on the
 * lower 3 bits of the address, to detect memory corruptions with higher
 * probability, where similar स्थिरants are used.
 */
#घोषणा KFENCE_CANARY_PATTERN(addr) ((u8)0xaa ^ (u8)((अचिन्हित दीर्घ)(addr) & 0x7))

/* Maximum stack depth क्रम reports. */
#घोषणा KFENCE_STACK_DEPTH 64

/* KFENCE object states. */
क्रमागत kfence_object_state अणु
	KFENCE_OBJECT_UNUSED,		/* Object is unused. */
	KFENCE_OBJECT_ALLOCATED,	/* Object is currently allocated. */
	KFENCE_OBJECT_FREED,		/* Object was allocated, and then मुक्तd. */
पूर्ण;

/* Alloc/मुक्त tracking inक्रमmation. */
काष्ठा kfence_track अणु
	pid_t pid;
	पूर्णांक num_stack_entries;
	अचिन्हित दीर्घ stack_entries[KFENCE_STACK_DEPTH];
पूर्ण;

/* KFENCE metadata per guarded allocation. */
काष्ठा kfence_metadata अणु
	काष्ठा list_head list;		/* Freelist node; access under kfence_मुक्तlist_lock. */
	काष्ठा rcu_head rcu_head;	/* For delayed मुक्तing. */

	/*
	 * Lock protecting below data; to ensure consistency of the below data,
	 * since the following may execute concurrently: __kfence_alloc(),
	 * __kfence_मुक्त(), kfence_handle_page_fault(). However, note that we
	 * cannot grab the same metadata off the मुक्तlist twice, and multiple
	 * __kfence_alloc() cannot run concurrently on the same metadata.
	 */
	raw_spinlock_t lock;

	/* The current state of the object; see above. */
	क्रमागत kfence_object_state state;

	/*
	 * Allocated object address; cannot be calculated from size, because of
	 * alignment requirements.
	 *
	 * Invariant: ALIGN_DOWN(addr, PAGE_SIZE) is स्थिरant.
	 */
	अचिन्हित दीर्घ addr;

	/*
	 * The size of the original allocation.
	 */
	माप_प्रकार size;

	/*
	 * The kmem_cache cache of the last allocation; शून्य अगर never allocated
	 * or the cache has alपढ़ोy been destroyed.
	 */
	काष्ठा kmem_cache *cache;

	/*
	 * In हाल of an invalid access, the page that was unरक्षित; we
	 * optimistically only store one address.
	 */
	अचिन्हित दीर्घ unरक्षित_page;

	/* Allocation and मुक्त stack inक्रमmation. */
	काष्ठा kfence_track alloc_track;
	काष्ठा kfence_track मुक्त_track;
पूर्ण;

बाह्य काष्ठा kfence_metadata kfence_metadata[CONFIG_KFENCE_NUM_OBJECTS];

/* KFENCE error types क्रम report generation. */
क्रमागत kfence_error_type अणु
	KFENCE_ERROR_OOB,		/* Detected a out-of-bounds access. */
	KFENCE_ERROR_UAF,		/* Detected a use-after-मुक्त access. */
	KFENCE_ERROR_CORRUPTION,	/* Detected a memory corruption on मुक्त. */
	KFENCE_ERROR_INVALID,		/* Invalid access of unknown type. */
	KFENCE_ERROR_INVALID_FREE,	/* Invalid मुक्त. */
पूर्ण;

व्योम kfence_report_error(अचिन्हित दीर्घ address, bool is_ग_लिखो, काष्ठा pt_regs *regs,
			 स्थिर काष्ठा kfence_metadata *meta, क्रमागत kfence_error_type type);

व्योम kfence_prपूर्णांक_object(काष्ठा seq_file *seq, स्थिर काष्ठा kfence_metadata *meta);

#पूर्ण_अगर /* MM_KFENCE_KFENCE_H */
