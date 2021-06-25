<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KASAN quarantine.
 *
 * Author: Alexander Potapenko <glider@google.com>
 * Copyright (C) 2016 Google, Inc.
 *
 * Based on code by Dmitry Chernenkov.
 */

#समावेश <linux/gfp.h>
#समावेश <linux/hash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/shrinker.h>
#समावेश <linux/slab.h>
#समावेश <linux/srcu.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/cpuhotplug.h>

#समावेश "../slab.h"
#समावेश "kasan.h"

/* Data काष्ठाure and operations क्रम quarantine queues. */

/*
 * Each queue is a single-linked list, which also stores the total size of
 * objects inside of it.
 */
काष्ठा qlist_head अणु
	काष्ठा qlist_node *head;
	काष्ठा qlist_node *tail;
	माप_प्रकार bytes;
	bool offline;
पूर्ण;

#घोषणा QLIST_INIT अणु शून्य, शून्य, 0 पूर्ण

अटल bool qlist_empty(काष्ठा qlist_head *q)
अणु
	वापस !q->head;
पूर्ण

अटल व्योम qlist_init(काष्ठा qlist_head *q)
अणु
	q->head = q->tail = शून्य;
	q->bytes = 0;
पूर्ण

अटल व्योम qlist_put(काष्ठा qlist_head *q, काष्ठा qlist_node *qlink,
		माप_प्रकार size)
अणु
	अगर (unlikely(qlist_empty(q)))
		q->head = qlink;
	अन्यथा
		q->tail->next = qlink;
	q->tail = qlink;
	qlink->next = शून्य;
	q->bytes += size;
पूर्ण

अटल व्योम qlist_move_all(काष्ठा qlist_head *from, काष्ठा qlist_head *to)
अणु
	अगर (unlikely(qlist_empty(from)))
		वापस;

	अगर (qlist_empty(to)) अणु
		*to = *from;
		qlist_init(from);
		वापस;
	पूर्ण

	to->tail->next = from->head;
	to->tail = from->tail;
	to->bytes += from->bytes;

	qlist_init(from);
पूर्ण

#घोषणा QUARANTINE_PERCPU_SIZE (1 << 20)
#घोषणा QUARANTINE_BATCHES \
	(1024 > 4 * CONFIG_NR_CPUS ? 1024 : 4 * CONFIG_NR_CPUS)

/*
 * The object quarantine consists of per-cpu queues and a global queue,
 * guarded by quarantine_lock.
 */
अटल DEFINE_PER_CPU(काष्ठा qlist_head, cpu_quarantine);

/* Round-robin FIFO array of batches. */
अटल काष्ठा qlist_head global_quarantine[QUARANTINE_BATCHES];
अटल पूर्णांक quarantine_head;
अटल पूर्णांक quarantine_tail;
/* Total size of all objects in global_quarantine across all batches. */
अटल अचिन्हित दीर्घ quarantine_size;
अटल DEFINE_RAW_SPINLOCK(quarantine_lock);
DEFINE_STATIC_SRCU(हटाओ_cache_srcu);

/* Maximum size of the global queue. */
अटल अचिन्हित दीर्घ quarantine_max_size;

/*
 * Target size of a batch in global_quarantine.
 * Usually equal to QUARANTINE_PERCPU_SIZE unless we have too much RAM.
 */
अटल अचिन्हित दीर्घ quarantine_batch_size;

/*
 * The fraction of physical memory the quarantine is allowed to occupy.
 * Quarantine करोesn't support memory shrinker with SLAB allocator, so we keep
 * the ratio low to aव्योम OOM.
 */
#घोषणा QUARANTINE_FRACTION 32

अटल काष्ठा kmem_cache *qlink_to_cache(काष्ठा qlist_node *qlink)
अणु
	वापस virt_to_head_page(qlink)->slab_cache;
पूर्ण

अटल व्योम *qlink_to_object(काष्ठा qlist_node *qlink, काष्ठा kmem_cache *cache)
अणु
	काष्ठा kasan_मुक्त_meta *मुक्त_info =
		container_of(qlink, काष्ठा kasan_मुक्त_meta,
			     quarantine_link);

	वापस ((व्योम *)मुक्त_info) - cache->kasan_info.मुक्त_meta_offset;
पूर्ण

अटल व्योम qlink_मुक्त(काष्ठा qlist_node *qlink, काष्ठा kmem_cache *cache)
अणु
	व्योम *object = qlink_to_object(qlink, cache);
	अचिन्हित दीर्घ flags;

	अगर (IS_ENABLED(CONFIG_SLAB))
		local_irq_save(flags);

	/*
	 * As the object now माला_लो मुक्तd from the quarantine, assume that its
	 * मुक्त track is no दीर्घer valid.
	 */
	*(u8 *)kasan_mem_to_shaकरोw(object) = KASAN_KMALLOC_FREE;

	___cache_मुक्त(cache, object, _THIS_IP_);

	अगर (IS_ENABLED(CONFIG_SLAB))
		local_irq_restore(flags);
पूर्ण

अटल व्योम qlist_मुक्त_all(काष्ठा qlist_head *q, काष्ठा kmem_cache *cache)
अणु
	काष्ठा qlist_node *qlink;

	अगर (unlikely(qlist_empty(q)))
		वापस;

	qlink = q->head;
	जबतक (qlink) अणु
		काष्ठा kmem_cache *obj_cache =
			cache ? cache :	qlink_to_cache(qlink);
		काष्ठा qlist_node *next = qlink->next;

		qlink_मुक्त(qlink, obj_cache);
		qlink = next;
	पूर्ण
	qlist_init(q);
पूर्ण

bool kasan_quarantine_put(काष्ठा kmem_cache *cache, व्योम *object)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा qlist_head *q;
	काष्ठा qlist_head temp = QLIST_INIT;
	काष्ठा kasan_मुक्त_meta *meta = kasan_get_मुक्त_meta(cache, object);

	/*
	 * If there's no metadata for this object, don't put it पूर्णांकo
	 * quarantine.
	 */
	अगर (!meta)
		वापस false;

	/*
	 * Note: irq must be disabled until after we move the batch to the
	 * global quarantine. Otherwise kasan_quarantine_हटाओ_cache() can
	 * miss some objects beदीर्घing to the cache अगर they are in our local
	 * temp list. kasan_quarantine_हटाओ_cache() executes on_each_cpu()
	 * at the beginning which ensures that it either sees the objects in
	 * per-cpu lists or in the global quarantine.
	 */
	local_irq_save(flags);

	q = this_cpu_ptr(&cpu_quarantine);
	अगर (q->offline) अणु
		local_irq_restore(flags);
		वापस false;
	पूर्ण
	qlist_put(q, &meta->quarantine_link, cache->size);
	अगर (unlikely(q->bytes > QUARANTINE_PERCPU_SIZE)) अणु
		qlist_move_all(q, &temp);

		raw_spin_lock(&quarantine_lock);
		WRITE_ONCE(quarantine_size, quarantine_size + temp.bytes);
		qlist_move_all(&temp, &global_quarantine[quarantine_tail]);
		अगर (global_quarantine[quarantine_tail].bytes >=
				READ_ONCE(quarantine_batch_size)) अणु
			पूर्णांक new_tail;

			new_tail = quarantine_tail + 1;
			अगर (new_tail == QUARANTINE_BATCHES)
				new_tail = 0;
			अगर (new_tail != quarantine_head)
				quarantine_tail = new_tail;
		पूर्ण
		raw_spin_unlock(&quarantine_lock);
	पूर्ण

	local_irq_restore(flags);

	वापस true;
पूर्ण

व्योम kasan_quarantine_reduce(व्योम)
अणु
	माप_प्रकार total_size, new_quarantine_size, percpu_quarantines;
	अचिन्हित दीर्घ flags;
	पूर्णांक srcu_idx;
	काष्ठा qlist_head to_मुक्त = QLIST_INIT;

	अगर (likely(READ_ONCE(quarantine_size) <=
		   READ_ONCE(quarantine_max_size)))
		वापस;

	/*
	 * srcu critical section ensures that kasan_quarantine_हटाओ_cache()
	 * will not miss objects beदीर्घing to the cache जबतक they are in our
	 * local to_मुक्त list. srcu is chosen because (1) it gives us निजी
	 * grace period करोमुख्य that करोes not पूर्णांकerfere with anything अन्यथा,
	 * and (2) it allows synchronize_srcu() to वापस without रुकोing
	 * अगर there are no pending पढ़ो critical sections (which is the
	 * expected हाल).
	 */
	srcu_idx = srcu_पढ़ो_lock(&हटाओ_cache_srcu);
	raw_spin_lock_irqsave(&quarantine_lock, flags);

	/*
	 * Update quarantine size in हाल of hotplug. Allocate a fraction of
	 * the installed memory to quarantine minus per-cpu queue limits.
	 */
	total_size = (totalram_pages() << PAGE_SHIFT) /
		QUARANTINE_FRACTION;
	percpu_quarantines = QUARANTINE_PERCPU_SIZE * num_online_cpus();
	new_quarantine_size = (total_size < percpu_quarantines) ?
		0 : total_size - percpu_quarantines;
	WRITE_ONCE(quarantine_max_size, new_quarantine_size);
	/* Aim at consuming at most 1/2 of slots in quarantine. */
	WRITE_ONCE(quarantine_batch_size, max((माप_प्रकार)QUARANTINE_PERCPU_SIZE,
		2 * total_size / QUARANTINE_BATCHES));

	अगर (likely(quarantine_size > quarantine_max_size)) अणु
		qlist_move_all(&global_quarantine[quarantine_head], &to_मुक्त);
		WRITE_ONCE(quarantine_size, quarantine_size - to_मुक्त.bytes);
		quarantine_head++;
		अगर (quarantine_head == QUARANTINE_BATCHES)
			quarantine_head = 0;
	पूर्ण

	raw_spin_unlock_irqrestore(&quarantine_lock, flags);

	qlist_मुक्त_all(&to_मुक्त, शून्य);
	srcu_पढ़ो_unlock(&हटाओ_cache_srcu, srcu_idx);
पूर्ण

अटल व्योम qlist_move_cache(काष्ठा qlist_head *from,
				   काष्ठा qlist_head *to,
				   काष्ठा kmem_cache *cache)
अणु
	काष्ठा qlist_node *curr;

	अगर (unlikely(qlist_empty(from)))
		वापस;

	curr = from->head;
	qlist_init(from);
	जबतक (curr) अणु
		काष्ठा qlist_node *next = curr->next;
		काष्ठा kmem_cache *obj_cache = qlink_to_cache(curr);

		अगर (obj_cache == cache)
			qlist_put(to, curr, obj_cache->size);
		अन्यथा
			qlist_put(from, curr, obj_cache->size);

		curr = next;
	पूर्ण
पूर्ण

अटल व्योम per_cpu_हटाओ_cache(व्योम *arg)
अणु
	काष्ठा kmem_cache *cache = arg;
	काष्ठा qlist_head to_मुक्त = QLIST_INIT;
	काष्ठा qlist_head *q;

	q = this_cpu_ptr(&cpu_quarantine);
	qlist_move_cache(q, &to_मुक्त, cache);
	qlist_मुक्त_all(&to_मुक्त, cache);
पूर्ण

/* Free all quarantined objects beदीर्घing to cache. */
व्योम kasan_quarantine_हटाओ_cache(काष्ठा kmem_cache *cache)
अणु
	अचिन्हित दीर्घ flags, i;
	काष्ठा qlist_head to_मुक्त = QLIST_INIT;

	/*
	 * Must be careful to not miss any objects that are being moved from
	 * per-cpu list to the global quarantine in kasan_quarantine_put(),
	 * nor objects being मुक्तd in kasan_quarantine_reduce(). on_each_cpu()
	 * achieves the first goal, जबतक synchronize_srcu() achieves the
	 * second.
	 */
	on_each_cpu(per_cpu_हटाओ_cache, cache, 1);

	raw_spin_lock_irqsave(&quarantine_lock, flags);
	क्रम (i = 0; i < QUARANTINE_BATCHES; i++) अणु
		अगर (qlist_empty(&global_quarantine[i]))
			जारी;
		qlist_move_cache(&global_quarantine[i], &to_मुक्त, cache);
		/* Scanning whole quarantine can take a जबतक. */
		raw_spin_unlock_irqrestore(&quarantine_lock, flags);
		cond_resched();
		raw_spin_lock_irqsave(&quarantine_lock, flags);
	पूर्ण
	raw_spin_unlock_irqrestore(&quarantine_lock, flags);

	qlist_मुक्त_all(&to_मुक्त, cache);

	synchronize_srcu(&हटाओ_cache_srcu);
पूर्ण

अटल पूर्णांक kasan_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	this_cpu_ptr(&cpu_quarantine)->offline = false;
	वापस 0;
पूर्ण

अटल पूर्णांक kasan_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा qlist_head *q;

	q = this_cpu_ptr(&cpu_quarantine);
	/* Ensure the ordering between the writing to q->offline and
	 * qlist_मुक्त_all. Otherwise, cpu_quarantine may be corrupted
	 * by पूर्णांकerrupt.
	 */
	WRITE_ONCE(q->offline, true);
	barrier();
	qlist_मुक्त_all(q, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक __init kasan_cpu_quarantine_init(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "mm/kasan:online",
				kasan_cpu_online, kasan_cpu_offline);
	अगर (ret < 0)
		pr_err("kasan cpu quarantine register failed [%d]\n", ret);
	वापस ret;
पूर्ण
late_initcall(kasan_cpu_quarantine_init);
