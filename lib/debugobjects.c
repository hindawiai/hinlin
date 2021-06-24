<शैली गुरु>
/*
 * Generic infraकाष्ठाure क्रम lअगरeसमय debugging of objects.
 *
 * Started by Thomas Gleixner
 *
 * Copyright (C) 2008, Thomas Gleixner <tglx@linutronix.de>
 *
 * For licencing details see kernel-base/COPYING
 */

#घोषणा pr_fmt(fmt) "ODEBUG: " fmt

#समावेश <linux/debugobjects.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/hash.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/cpu.h>

#घोषणा ODEBUG_HASH_BITS	14
#घोषणा ODEBUG_HASH_SIZE	(1 << ODEBUG_HASH_BITS)

#घोषणा ODEBUG_POOL_SIZE	1024
#घोषणा ODEBUG_POOL_MIN_LEVEL	256
#घोषणा ODEBUG_POOL_PERCPU_SIZE	64
#घोषणा ODEBUG_BATCH_SIZE	16

#घोषणा ODEBUG_CHUNK_SHIFT	PAGE_SHIFT
#घोषणा ODEBUG_CHUNK_SIZE	(1 << ODEBUG_CHUNK_SHIFT)
#घोषणा ODEBUG_CHUNK_MASK	(~(ODEBUG_CHUNK_SIZE - 1))

/*
 * We limit the मुक्तing of debug objects via workqueue at a maximum
 * frequency of 10Hz and about 1024 objects क्रम each मुक्तing operation.
 * So it is मुक्तing at most 10k debug objects per second.
 */
#घोषणा ODEBUG_FREE_WORK_MAX	1024
#घोषणा ODEBUG_FREE_WORK_DELAY	DIV_ROUND_UP(HZ, 10)

काष्ठा debug_bucket अणु
	काष्ठा hlist_head	list;
	raw_spinlock_t		lock;
पूर्ण;

/*
 * Debug object percpu मुक्त list
 * Access is रक्षित by disabling irq
 */
काष्ठा debug_percpu_मुक्त अणु
	काष्ठा hlist_head	मुक्त_objs;
	पूर्णांक			obj_मुक्त;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा debug_percpu_मुक्त, percpu_obj_pool);

अटल काष्ठा debug_bucket	obj_hash[ODEBUG_HASH_SIZE];

अटल काष्ठा debug_obj		obj_अटल_pool[ODEBUG_POOL_SIZE] __initdata;

अटल DEFINE_RAW_SPINLOCK(pool_lock);

अटल HLIST_HEAD(obj_pool);
अटल HLIST_HEAD(obj_to_मुक्त);

/*
 * Because of the presence of percpu मुक्त pools, obj_pool_मुक्त will
 * under-count those in the percpu मुक्त pools. Similarly, obj_pool_used
 * will over-count those in the percpu मुक्त pools. Adjusपंचांगents will be
 * made at debug_stats_show(). Both obj_pool_min_मुक्त and obj_pool_max_used
 * can be off.
 */
अटल पूर्णांक			obj_pool_min_मुक्त = ODEBUG_POOL_SIZE;
अटल पूर्णांक			obj_pool_मुक्त = ODEBUG_POOL_SIZE;
अटल पूर्णांक			obj_pool_used;
अटल पूर्णांक			obj_pool_max_used;
अटल bool			obj_मुक्तing;
/* The number of objs on the global मुक्त list */
अटल पूर्णांक			obj_nr_toमुक्त;

अटल पूर्णांक			debug_objects_maxchain __पढ़ो_mostly;
अटल पूर्णांक __maybe_unused	debug_objects_maxchecked __पढ़ो_mostly;
अटल पूर्णांक			debug_objects_fixups __पढ़ो_mostly;
अटल पूर्णांक			debug_objects_warnings __पढ़ो_mostly;
अटल पूर्णांक			debug_objects_enabled __पढ़ो_mostly
				= CONFIG_DEBUG_OBJECTS_ENABLE_DEFAULT;
अटल पूर्णांक			debug_objects_pool_size __पढ़ो_mostly
				= ODEBUG_POOL_SIZE;
अटल पूर्णांक			debug_objects_pool_min_level __पढ़ो_mostly
				= ODEBUG_POOL_MIN_LEVEL;
अटल स्थिर काष्ठा debug_obj_descr *descr_test  __पढ़ो_mostly;
अटल काष्ठा kmem_cache	*obj_cache __पढ़ो_mostly;

/*
 * Track numbers of kmem_cache_alloc()/मुक्त() calls करोne.
 */
अटल पूर्णांक			debug_objects_allocated;
अटल पूर्णांक			debug_objects_मुक्तd;

अटल व्योम मुक्त_obj_work(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(debug_obj_work, मुक्त_obj_work);

अटल पूर्णांक __init enable_object_debug(अक्षर *str)
अणु
	debug_objects_enabled = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init disable_object_debug(अक्षर *str)
अणु
	debug_objects_enabled = 0;
	वापस 0;
पूर्ण

early_param("debug_objects", enable_object_debug);
early_param("no_debug_objects", disable_object_debug);

अटल स्थिर अक्षर *obj_states[ODEBUG_STATE_MAX] = अणु
	[ODEBUG_STATE_NONE]		= "none",
	[ODEBUG_STATE_INIT]		= "initialized",
	[ODEBUG_STATE_INACTIVE]		= "inactive",
	[ODEBUG_STATE_ACTIVE]		= "active",
	[ODEBUG_STATE_DESTROYED]	= "destroyed",
	[ODEBUG_STATE_NOTAVAILABLE]	= "not available",
पूर्ण;

अटल व्योम fill_pool(व्योम)
अणु
	gfp_t gfp = GFP_ATOMIC | __GFP_NORETRY | __GFP_NOWARN;
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;

	अगर (likely(READ_ONCE(obj_pool_मुक्त) >= debug_objects_pool_min_level))
		वापस;

	/*
	 * Reuse objs from the global मुक्त list; they will be reinitialized
	 * when allocating.
	 *
	 * Both obj_nr_toमुक्त and obj_pool_मुक्त are checked locklessly; the
	 * READ_ONCE()s pair with the WRITE_ONCE()s in pool_lock critical
	 * sections.
	 */
	जबतक (READ_ONCE(obj_nr_toमुक्त) && (READ_ONCE(obj_pool_मुक्त) < obj_pool_min_मुक्त)) अणु
		raw_spin_lock_irqsave(&pool_lock, flags);
		/*
		 * Recheck with the lock held as the worker thपढ़ो might have
		 * won the race and मुक्तd the global मुक्त list alपढ़ोy.
		 */
		जबतक (obj_nr_toमुक्त && (obj_pool_मुक्त < obj_pool_min_मुक्त)) अणु
			obj = hlist_entry(obj_to_मुक्त.first, typeof(*obj), node);
			hlist_del(&obj->node);
			WRITE_ONCE(obj_nr_toमुक्त, obj_nr_toमुक्त - 1);
			hlist_add_head(&obj->node, &obj_pool);
			WRITE_ONCE(obj_pool_मुक्त, obj_pool_मुक्त + 1);
		पूर्ण
		raw_spin_unlock_irqrestore(&pool_lock, flags);
	पूर्ण

	अगर (unlikely(!obj_cache))
		वापस;

	जबतक (READ_ONCE(obj_pool_मुक्त) < debug_objects_pool_min_level) अणु
		काष्ठा debug_obj *new[ODEBUG_BATCH_SIZE];
		पूर्णांक cnt;

		क्रम (cnt = 0; cnt < ODEBUG_BATCH_SIZE; cnt++) अणु
			new[cnt] = kmem_cache_zalloc(obj_cache, gfp);
			अगर (!new[cnt])
				अवरोध;
		पूर्ण
		अगर (!cnt)
			वापस;

		raw_spin_lock_irqsave(&pool_lock, flags);
		जबतक (cnt) अणु
			hlist_add_head(&new[--cnt]->node, &obj_pool);
			debug_objects_allocated++;
			WRITE_ONCE(obj_pool_मुक्त, obj_pool_मुक्त + 1);
		पूर्ण
		raw_spin_unlock_irqrestore(&pool_lock, flags);
	पूर्ण
पूर्ण

/*
 * Lookup an object in the hash bucket.
 */
अटल काष्ठा debug_obj *lookup_object(व्योम *addr, काष्ठा debug_bucket *b)
अणु
	काष्ठा debug_obj *obj;
	पूर्णांक cnt = 0;

	hlist_क्रम_each_entry(obj, &b->list, node) अणु
		cnt++;
		अगर (obj->object == addr)
			वापस obj;
	पूर्ण
	अगर (cnt > debug_objects_maxchain)
		debug_objects_maxchain = cnt;

	वापस शून्य;
पूर्ण

/*
 * Allocate a new object from the hlist
 */
अटल काष्ठा debug_obj *__alloc_object(काष्ठा hlist_head *list)
अणु
	काष्ठा debug_obj *obj = शून्य;

	अगर (list->first) अणु
		obj = hlist_entry(list->first, typeof(*obj), node);
		hlist_del(&obj->node);
	पूर्ण

	वापस obj;
पूर्ण

/*
 * Allocate a new object. If the pool is empty, चयन off the debugger.
 * Must be called with पूर्णांकerrupts disabled.
 */
अटल काष्ठा debug_obj *
alloc_object(व्योम *addr, काष्ठा debug_bucket *b, स्थिर काष्ठा debug_obj_descr *descr)
अणु
	काष्ठा debug_percpu_मुक्त *percpu_pool = this_cpu_ptr(&percpu_obj_pool);
	काष्ठा debug_obj *obj;

	अगर (likely(obj_cache)) अणु
		obj = __alloc_object(&percpu_pool->मुक्त_objs);
		अगर (obj) अणु
			percpu_pool->obj_मुक्त--;
			जाओ init_obj;
		पूर्ण
	पूर्ण

	raw_spin_lock(&pool_lock);
	obj = __alloc_object(&obj_pool);
	अगर (obj) अणु
		obj_pool_used++;
		WRITE_ONCE(obj_pool_मुक्त, obj_pool_मुक्त - 1);

		/*
		 * Looking ahead, allocate one batch of debug objects and
		 * put them पूर्णांकo the percpu मुक्त pool.
		 */
		अगर (likely(obj_cache)) अणु
			पूर्णांक i;

			क्रम (i = 0; i < ODEBUG_BATCH_SIZE; i++) अणु
				काष्ठा debug_obj *obj2;

				obj2 = __alloc_object(&obj_pool);
				अगर (!obj2)
					अवरोध;
				hlist_add_head(&obj2->node,
					       &percpu_pool->मुक्त_objs);
				percpu_pool->obj_मुक्त++;
				obj_pool_used++;
				WRITE_ONCE(obj_pool_मुक्त, obj_pool_मुक्त - 1);
			पूर्ण
		पूर्ण

		अगर (obj_pool_used > obj_pool_max_used)
			obj_pool_max_used = obj_pool_used;

		अगर (obj_pool_मुक्त < obj_pool_min_मुक्त)
			obj_pool_min_मुक्त = obj_pool_मुक्त;
	पूर्ण
	raw_spin_unlock(&pool_lock);

init_obj:
	अगर (obj) अणु
		obj->object = addr;
		obj->descr  = descr;
		obj->state  = ODEBUG_STATE_NONE;
		obj->astate = 0;
		hlist_add_head(&obj->node, &b->list);
	पूर्ण
	वापस obj;
पूर्ण

/*
 * workqueue function to मुक्त objects.
 *
 * To reduce contention on the global pool_lock, the actual मुक्तing of
 * debug objects will be delayed अगर the pool_lock is busy.
 */
अटल व्योम मुक्त_obj_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hlist_node *पंचांगp;
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;
	HLIST_HEAD(toमुक्त);

	WRITE_ONCE(obj_मुक्तing, false);
	अगर (!raw_spin_trylock_irqsave(&pool_lock, flags))
		वापस;

	अगर (obj_pool_मुक्त >= debug_objects_pool_size)
		जाओ मुक्त_objs;

	/*
	 * The objs on the pool list might be allocated beक्रमe the work is
	 * run, so recheck अगर pool list it full or not, अगर not fill pool
	 * list from the global मुक्त list. As it is likely that a workload
	 * may be gearing up to use more and more objects, करोn't मुक्त any
	 * of them until the next round.
	 */
	जबतक (obj_nr_toमुक्त && obj_pool_मुक्त < debug_objects_pool_size) अणु
		obj = hlist_entry(obj_to_मुक्त.first, typeof(*obj), node);
		hlist_del(&obj->node);
		hlist_add_head(&obj->node, &obj_pool);
		WRITE_ONCE(obj_pool_मुक्त, obj_pool_मुक्त + 1);
		WRITE_ONCE(obj_nr_toमुक्त, obj_nr_toमुक्त - 1);
	पूर्ण
	raw_spin_unlock_irqrestore(&pool_lock, flags);
	वापस;

मुक्त_objs:
	/*
	 * Pool list is alपढ़ोy full and there are still objs on the मुक्त
	 * list. Move reमुख्यing मुक्त objs to a temporary list to मुक्त the
	 * memory outside the pool_lock held region.
	 */
	अगर (obj_nr_toमुक्त) अणु
		hlist_move_list(&obj_to_मुक्त, &toमुक्त);
		debug_objects_मुक्तd += obj_nr_toमुक्त;
		WRITE_ONCE(obj_nr_toमुक्त, 0);
	पूर्ण
	raw_spin_unlock_irqrestore(&pool_lock, flags);

	hlist_क्रम_each_entry_safe(obj, पंचांगp, &toमुक्त, node) अणु
		hlist_del(&obj->node);
		kmem_cache_मुक्त(obj_cache, obj);
	पूर्ण
पूर्ण

अटल व्योम __मुक्त_object(काष्ठा debug_obj *obj)
अणु
	काष्ठा debug_obj *objs[ODEBUG_BATCH_SIZE];
	काष्ठा debug_percpu_मुक्त *percpu_pool;
	पूर्णांक lookahead_count = 0;
	अचिन्हित दीर्घ flags;
	bool work;

	local_irq_save(flags);
	अगर (!obj_cache)
		जाओ मुक्त_to_obj_pool;

	/*
	 * Try to मुक्त it पूर्णांकo the percpu pool first.
	 */
	percpu_pool = this_cpu_ptr(&percpu_obj_pool);
	अगर (percpu_pool->obj_मुक्त < ODEBUG_POOL_PERCPU_SIZE) अणु
		hlist_add_head(&obj->node, &percpu_pool->मुक्त_objs);
		percpu_pool->obj_मुक्त++;
		local_irq_restore(flags);
		वापस;
	पूर्ण

	/*
	 * As the percpu pool is full, look ahead and pull out a batch
	 * of objects from the percpu pool and मुक्त them as well.
	 */
	क्रम (; lookahead_count < ODEBUG_BATCH_SIZE; lookahead_count++) अणु
		objs[lookahead_count] = __alloc_object(&percpu_pool->मुक्त_objs);
		अगर (!objs[lookahead_count])
			अवरोध;
		percpu_pool->obj_मुक्त--;
	पूर्ण

मुक्त_to_obj_pool:
	raw_spin_lock(&pool_lock);
	work = (obj_pool_मुक्त > debug_objects_pool_size) && obj_cache &&
	       (obj_nr_toमुक्त < ODEBUG_FREE_WORK_MAX);
	obj_pool_used--;

	अगर (work) अणु
		WRITE_ONCE(obj_nr_toमुक्त, obj_nr_toमुक्त + 1);
		hlist_add_head(&obj->node, &obj_to_मुक्त);
		अगर (lookahead_count) अणु
			WRITE_ONCE(obj_nr_toमुक्त, obj_nr_toमुक्त + lookahead_count);
			obj_pool_used -= lookahead_count;
			जबतक (lookahead_count) अणु
				hlist_add_head(&objs[--lookahead_count]->node,
					       &obj_to_मुक्त);
			पूर्ण
		पूर्ण

		अगर ((obj_pool_मुक्त > debug_objects_pool_size) &&
		    (obj_nr_toमुक्त < ODEBUG_FREE_WORK_MAX)) अणु
			पूर्णांक i;

			/*
			 * Free one more batch of objects from obj_pool.
			 */
			क्रम (i = 0; i < ODEBUG_BATCH_SIZE; i++) अणु
				obj = __alloc_object(&obj_pool);
				hlist_add_head(&obj->node, &obj_to_मुक्त);
				WRITE_ONCE(obj_pool_मुक्त, obj_pool_मुक्त - 1);
				WRITE_ONCE(obj_nr_toमुक्त, obj_nr_toमुक्त + 1);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		WRITE_ONCE(obj_pool_मुक्त, obj_pool_मुक्त + 1);
		hlist_add_head(&obj->node, &obj_pool);
		अगर (lookahead_count) अणु
			WRITE_ONCE(obj_pool_मुक्त, obj_pool_मुक्त + lookahead_count);
			obj_pool_used -= lookahead_count;
			जबतक (lookahead_count) अणु
				hlist_add_head(&objs[--lookahead_count]->node,
					       &obj_pool);
			पूर्ण
		पूर्ण
	पूर्ण
	raw_spin_unlock(&pool_lock);
	local_irq_restore(flags);
पूर्ण

/*
 * Put the object back पूर्णांकo the pool and schedule work to मुक्त objects
 * अगर necessary.
 */
अटल व्योम मुक्त_object(काष्ठा debug_obj *obj)
अणु
	__मुक्त_object(obj);
	अगर (!READ_ONCE(obj_मुक्तing) && READ_ONCE(obj_nr_toमुक्त)) अणु
		WRITE_ONCE(obj_मुक्तing, true);
		schedule_delayed_work(&debug_obj_work, ODEBUG_FREE_WORK_DELAY);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक object_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा debug_percpu_मुक्त *percpu_pool;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा debug_obj *obj;

	/* Remote access is safe as the CPU is dead alपढ़ोy */
	percpu_pool = per_cpu_ptr(&percpu_obj_pool, cpu);
	hlist_क्रम_each_entry_safe(obj, पंचांगp, &percpu_pool->मुक्त_objs, node) अणु
		hlist_del(&obj->node);
		kmem_cache_मुक्त(obj_cache, obj);
	पूर्ण
	percpu_pool->obj_मुक्त = 0;

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * We run out of memory. That means we probably have tons of objects
 * allocated.
 */
अटल व्योम debug_objects_oom(व्योम)
अणु
	काष्ठा debug_bucket *db = obj_hash;
	काष्ठा hlist_node *पंचांगp;
	HLIST_HEAD(मुक्तlist);
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	pr_warn("Out of memory. ODEBUG disabled\n");

	क्रम (i = 0; i < ODEBUG_HASH_SIZE; i++, db++) अणु
		raw_spin_lock_irqsave(&db->lock, flags);
		hlist_move_list(&db->list, &मुक्तlist);
		raw_spin_unlock_irqrestore(&db->lock, flags);

		/* Now मुक्त them */
		hlist_क्रम_each_entry_safe(obj, पंचांगp, &मुक्तlist, node) अणु
			hlist_del(&obj->node);
			मुक्त_object(obj);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * We use the pfn of the address क्रम the hash. That way we can check
 * क्रम मुक्तd objects simply by checking the affected bucket.
 */
अटल काष्ठा debug_bucket *get_bucket(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ hash;

	hash = hash_दीर्घ((addr >> ODEBUG_CHUNK_SHIFT), ODEBUG_HASH_BITS);
	वापस &obj_hash[hash];
पूर्ण

अटल व्योम debug_prपूर्णांक_object(काष्ठा debug_obj *obj, अक्षर *msg)
अणु
	स्थिर काष्ठा debug_obj_descr *descr = obj->descr;
	अटल पूर्णांक limit;

	अगर (limit < 5 && descr != descr_test) अणु
		व्योम *hपूर्णांक = descr->debug_hपूर्णांक ?
			descr->debug_hपूर्णांक(obj->object) : शून्य;
		limit++;
		WARN(1, KERN_ERR "ODEBUG: %s %s (active state %u) "
				 "object type: %s hint: %pS\n",
			msg, obj_states[obj->state], obj->astate,
			descr->name, hपूर्णांक);
	पूर्ण
	debug_objects_warnings++;
पूर्ण

/*
 * Try to repair the damage, so we have a better chance to get useful
 * debug output.
 */
अटल bool
debug_object_fixup(bool (*fixup)(व्योम *addr, क्रमागत debug_obj_state state),
		   व्योम * addr, क्रमागत debug_obj_state state)
अणु
	अगर (fixup && fixup(addr, state)) अणु
		debug_objects_fixups++;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम debug_object_is_on_stack(व्योम *addr, पूर्णांक onstack)
अणु
	पूर्णांक is_on_stack;
	अटल पूर्णांक limit;

	अगर (limit > 4)
		वापस;

	is_on_stack = object_is_on_stack(addr);
	अगर (is_on_stack == onstack)
		वापस;

	limit++;
	अगर (is_on_stack)
		pr_warn("object %p is on stack %p, but NOT annotated.\n", addr,
			 task_stack_page(current));
	अन्यथा
		pr_warn("object %p is NOT on stack %p, but annotated.\n", addr,
			 task_stack_page(current));

	WARN_ON(1);
पूर्ण

अटल व्योम
__debug_object_init(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr, पूर्णांक onstack)
अणु
	क्रमागत debug_obj_state state;
	bool check_stack = false;
	काष्ठा debug_bucket *db;
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;

	fill_pool();

	db = get_bucket((अचिन्हित दीर्घ) addr);

	raw_spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	अगर (!obj) अणु
		obj = alloc_object(addr, db, descr);
		अगर (!obj) अणु
			debug_objects_enabled = 0;
			raw_spin_unlock_irqrestore(&db->lock, flags);
			debug_objects_oom();
			वापस;
		पूर्ण
		check_stack = true;
	पूर्ण

	चयन (obj->state) अणु
	हाल ODEBUG_STATE_NONE:
	हाल ODEBUG_STATE_INIT:
	हाल ODEBUG_STATE_INACTIVE:
		obj->state = ODEBUG_STATE_INIT;
		अवरोध;

	हाल ODEBUG_STATE_ACTIVE:
		state = obj->state;
		raw_spin_unlock_irqrestore(&db->lock, flags);
		debug_prपूर्णांक_object(obj, "init");
		debug_object_fixup(descr->fixup_init, addr, state);
		वापस;

	हाल ODEBUG_STATE_DESTROYED:
		raw_spin_unlock_irqrestore(&db->lock, flags);
		debug_prपूर्णांक_object(obj, "init");
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	raw_spin_unlock_irqrestore(&db->lock, flags);
	अगर (check_stack)
		debug_object_is_on_stack(addr, onstack);
पूर्ण

/**
 * debug_object_init - debug checks when an object is initialized
 * @addr:	address of the object
 * @descr:	poपूर्णांकer to an object specअगरic debug description काष्ठाure
 */
व्योम debug_object_init(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr)
अणु
	अगर (!debug_objects_enabled)
		वापस;

	__debug_object_init(addr, descr, 0);
पूर्ण
EXPORT_SYMBOL_GPL(debug_object_init);

/**
 * debug_object_init_on_stack - debug checks when an object on stack is
 *				initialized
 * @addr:	address of the object
 * @descr:	poपूर्णांकer to an object specअगरic debug description काष्ठाure
 */
व्योम debug_object_init_on_stack(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr)
अणु
	अगर (!debug_objects_enabled)
		वापस;

	__debug_object_init(addr, descr, 1);
पूर्ण
EXPORT_SYMBOL_GPL(debug_object_init_on_stack);

/**
 * debug_object_activate - debug checks when an object is activated
 * @addr:	address of the object
 * @descr:	poपूर्णांकer to an object specअगरic debug description काष्ठाure
 * Returns 0 क्रम success, -EINVAL क्रम check failed.
 */
पूर्णांक debug_object_activate(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr)
अणु
	क्रमागत debug_obj_state state;
	काष्ठा debug_bucket *db;
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	काष्ठा debug_obj o = अणु .object = addr,
			       .state = ODEBUG_STATE_NOTAVAILABLE,
			       .descr = descr पूर्ण;

	अगर (!debug_objects_enabled)
		वापस 0;

	db = get_bucket((अचिन्हित दीर्घ) addr);

	raw_spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	अगर (obj) अणु
		bool prपूर्णांक_object = false;

		चयन (obj->state) अणु
		हाल ODEBUG_STATE_INIT:
		हाल ODEBUG_STATE_INACTIVE:
			obj->state = ODEBUG_STATE_ACTIVE;
			ret = 0;
			अवरोध;

		हाल ODEBUG_STATE_ACTIVE:
			state = obj->state;
			raw_spin_unlock_irqrestore(&db->lock, flags);
			debug_prपूर्णांक_object(obj, "activate");
			ret = debug_object_fixup(descr->fixup_activate, addr, state);
			वापस ret ? 0 : -EINVAL;

		हाल ODEBUG_STATE_DESTROYED:
			prपूर्णांक_object = true;
			ret = -EINVAL;
			अवरोध;
		शेष:
			ret = 0;
			अवरोध;
		पूर्ण
		raw_spin_unlock_irqrestore(&db->lock, flags);
		अगर (prपूर्णांक_object)
			debug_prपूर्णांक_object(obj, "activate");
		वापस ret;
	पूर्ण

	raw_spin_unlock_irqrestore(&db->lock, flags);

	/*
	 * We are here when a अटल object is activated. We
	 * let the type specअगरic code confirm whether this is
	 * true or not. अगर true, we just make sure that the
	 * अटल object is tracked in the object tracker. If
	 * not, this must be a bug, so we try to fix it up.
	 */
	अगर (descr->is_अटल_object && descr->is_अटल_object(addr)) अणु
		/* track this अटल object */
		debug_object_init(addr, descr);
		debug_object_activate(addr, descr);
	पूर्ण अन्यथा अणु
		debug_prपूर्णांक_object(&o, "activate");
		ret = debug_object_fixup(descr->fixup_activate, addr,
					ODEBUG_STATE_NOTAVAILABLE);
		वापस ret ? 0 : -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(debug_object_activate);

/**
 * debug_object_deactivate - debug checks when an object is deactivated
 * @addr:	address of the object
 * @descr:	poपूर्णांकer to an object specअगरic debug description काष्ठाure
 */
व्योम debug_object_deactivate(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr)
अणु
	काष्ठा debug_bucket *db;
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;
	bool prपूर्णांक_object = false;

	अगर (!debug_objects_enabled)
		वापस;

	db = get_bucket((अचिन्हित दीर्घ) addr);

	raw_spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	अगर (obj) अणु
		चयन (obj->state) अणु
		हाल ODEBUG_STATE_INIT:
		हाल ODEBUG_STATE_INACTIVE:
		हाल ODEBUG_STATE_ACTIVE:
			अगर (!obj->astate)
				obj->state = ODEBUG_STATE_INACTIVE;
			अन्यथा
				prपूर्णांक_object = true;
			अवरोध;

		हाल ODEBUG_STATE_DESTROYED:
			prपूर्णांक_object = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	raw_spin_unlock_irqrestore(&db->lock, flags);
	अगर (!obj) अणु
		काष्ठा debug_obj o = अणु .object = addr,
				       .state = ODEBUG_STATE_NOTAVAILABLE,
				       .descr = descr पूर्ण;

		debug_prपूर्णांक_object(&o, "deactivate");
	पूर्ण अन्यथा अगर (prपूर्णांक_object) अणु
		debug_prपूर्णांक_object(obj, "deactivate");
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(debug_object_deactivate);

/**
 * debug_object_destroy - debug checks when an object is destroyed
 * @addr:	address of the object
 * @descr:	poपूर्णांकer to an object specअगरic debug description काष्ठाure
 */
व्योम debug_object_destroy(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr)
अणु
	क्रमागत debug_obj_state state;
	काष्ठा debug_bucket *db;
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;
	bool prपूर्णांक_object = false;

	अगर (!debug_objects_enabled)
		वापस;

	db = get_bucket((अचिन्हित दीर्घ) addr);

	raw_spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	अगर (!obj)
		जाओ out_unlock;

	चयन (obj->state) अणु
	हाल ODEBUG_STATE_NONE:
	हाल ODEBUG_STATE_INIT:
	हाल ODEBUG_STATE_INACTIVE:
		obj->state = ODEBUG_STATE_DESTROYED;
		अवरोध;
	हाल ODEBUG_STATE_ACTIVE:
		state = obj->state;
		raw_spin_unlock_irqrestore(&db->lock, flags);
		debug_prपूर्णांक_object(obj, "destroy");
		debug_object_fixup(descr->fixup_destroy, addr, state);
		वापस;

	हाल ODEBUG_STATE_DESTROYED:
		prपूर्णांक_object = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
out_unlock:
	raw_spin_unlock_irqrestore(&db->lock, flags);
	अगर (prपूर्णांक_object)
		debug_prपूर्णांक_object(obj, "destroy");
पूर्ण
EXPORT_SYMBOL_GPL(debug_object_destroy);

/**
 * debug_object_मुक्त - debug checks when an object is मुक्तd
 * @addr:	address of the object
 * @descr:	poपूर्णांकer to an object specअगरic debug description काष्ठाure
 */
व्योम debug_object_मुक्त(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr)
अणु
	क्रमागत debug_obj_state state;
	काष्ठा debug_bucket *db;
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;

	अगर (!debug_objects_enabled)
		वापस;

	db = get_bucket((अचिन्हित दीर्घ) addr);

	raw_spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	अगर (!obj)
		जाओ out_unlock;

	चयन (obj->state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		state = obj->state;
		raw_spin_unlock_irqrestore(&db->lock, flags);
		debug_prपूर्णांक_object(obj, "free");
		debug_object_fixup(descr->fixup_मुक्त, addr, state);
		वापस;
	शेष:
		hlist_del(&obj->node);
		raw_spin_unlock_irqrestore(&db->lock, flags);
		मुक्त_object(obj);
		वापस;
	पूर्ण
out_unlock:
	raw_spin_unlock_irqrestore(&db->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(debug_object_मुक्त);

/**
 * debug_object_निश्चित_init - debug checks when object should be init-ed
 * @addr:	address of the object
 * @descr:	poपूर्णांकer to an object specअगरic debug description काष्ठाure
 */
व्योम debug_object_निश्चित_init(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr)
अणु
	काष्ठा debug_bucket *db;
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;

	अगर (!debug_objects_enabled)
		वापस;

	db = get_bucket((अचिन्हित दीर्घ) addr);

	raw_spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	अगर (!obj) अणु
		काष्ठा debug_obj o = अणु .object = addr,
				       .state = ODEBUG_STATE_NOTAVAILABLE,
				       .descr = descr पूर्ण;

		raw_spin_unlock_irqrestore(&db->lock, flags);
		/*
		 * Maybe the object is अटल, and we let the type specअगरic
		 * code confirm. Track this अटल object अगर true, अन्यथा invoke
		 * fixup.
		 */
		अगर (descr->is_अटल_object && descr->is_अटल_object(addr)) अणु
			/* Track this अटल object */
			debug_object_init(addr, descr);
		पूर्ण अन्यथा अणु
			debug_prपूर्णांक_object(&o, "assert_init");
			debug_object_fixup(descr->fixup_निश्चित_init, addr,
					   ODEBUG_STATE_NOTAVAILABLE);
		पूर्ण
		वापस;
	पूर्ण

	raw_spin_unlock_irqrestore(&db->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(debug_object_निश्चित_init);

/**
 * debug_object_active_state - debug checks object usage state machine
 * @addr:	address of the object
 * @descr:	poपूर्णांकer to an object specअगरic debug description काष्ठाure
 * @expect:	expected state
 * @next:	state to move to अगर expected state is found
 */
व्योम
debug_object_active_state(व्योम *addr, स्थिर काष्ठा debug_obj_descr *descr,
			  अचिन्हित पूर्णांक expect, अचिन्हित पूर्णांक next)
अणु
	काष्ठा debug_bucket *db;
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;
	bool prपूर्णांक_object = false;

	अगर (!debug_objects_enabled)
		वापस;

	db = get_bucket((अचिन्हित दीर्घ) addr);

	raw_spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	अगर (obj) अणु
		चयन (obj->state) अणु
		हाल ODEBUG_STATE_ACTIVE:
			अगर (obj->astate == expect)
				obj->astate = next;
			अन्यथा
				prपूर्णांक_object = true;
			अवरोध;

		शेष:
			prपूर्णांक_object = true;
			अवरोध;
		पूर्ण
	पूर्ण

	raw_spin_unlock_irqrestore(&db->lock, flags);
	अगर (!obj) अणु
		काष्ठा debug_obj o = अणु .object = addr,
				       .state = ODEBUG_STATE_NOTAVAILABLE,
				       .descr = descr पूर्ण;

		debug_prपूर्णांक_object(&o, "active_state");
	पूर्ण अन्यथा अगर (prपूर्णांक_object) अणु
		debug_prपूर्णांक_object(obj, "active_state");
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(debug_object_active_state);

#अगर_घोषित CONFIG_DEBUG_OBJECTS_FREE
अटल व्योम __debug_check_no_obj_मुक्तd(स्थिर व्योम *address, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ flags, oaddr, saddr, eaddr, paddr, chunks;
	स्थिर काष्ठा debug_obj_descr *descr;
	क्रमागत debug_obj_state state;
	काष्ठा debug_bucket *db;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा debug_obj *obj;
	पूर्णांक cnt, objs_checked = 0;

	saddr = (अचिन्हित दीर्घ) address;
	eaddr = saddr + size;
	paddr = saddr & ODEBUG_CHUNK_MASK;
	chunks = ((eaddr - paddr) + (ODEBUG_CHUNK_SIZE - 1));
	chunks >>= ODEBUG_CHUNK_SHIFT;

	क्रम (;chunks > 0; chunks--, paddr += ODEBUG_CHUNK_SIZE) अणु
		db = get_bucket(paddr);

repeat:
		cnt = 0;
		raw_spin_lock_irqsave(&db->lock, flags);
		hlist_क्रम_each_entry_safe(obj, पंचांगp, &db->list, node) अणु
			cnt++;
			oaddr = (अचिन्हित दीर्घ) obj->object;
			अगर (oaddr < saddr || oaddr >= eaddr)
				जारी;

			चयन (obj->state) अणु
			हाल ODEBUG_STATE_ACTIVE:
				descr = obj->descr;
				state = obj->state;
				raw_spin_unlock_irqrestore(&db->lock, flags);
				debug_prपूर्णांक_object(obj, "free");
				debug_object_fixup(descr->fixup_मुक्त,
						   (व्योम *) oaddr, state);
				जाओ repeat;
			शेष:
				hlist_del(&obj->node);
				__मुक्त_object(obj);
				अवरोध;
			पूर्ण
		पूर्ण
		raw_spin_unlock_irqrestore(&db->lock, flags);

		अगर (cnt > debug_objects_maxchain)
			debug_objects_maxchain = cnt;

		objs_checked += cnt;
	पूर्ण

	अगर (objs_checked > debug_objects_maxchecked)
		debug_objects_maxchecked = objs_checked;

	/* Schedule work to actually kmem_cache_मुक्त() objects */
	अगर (!READ_ONCE(obj_मुक्तing) && READ_ONCE(obj_nr_toमुक्त)) अणु
		WRITE_ONCE(obj_मुक्तing, true);
		schedule_delayed_work(&debug_obj_work, ODEBUG_FREE_WORK_DELAY);
	पूर्ण
पूर्ण

व्योम debug_check_no_obj_मुक्तd(स्थिर व्योम *address, अचिन्हित दीर्घ size)
अणु
	अगर (debug_objects_enabled)
		__debug_check_no_obj_मुक्तd(address, size);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक debug_stats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक cpu, obj_percpu_मुक्त = 0;

	क्रम_each_possible_cpu(cpu)
		obj_percpu_मुक्त += per_cpu(percpu_obj_pool.obj_मुक्त, cpu);

	seq_म_लिखो(m, "max_chain     :%d\n", debug_objects_maxchain);
	seq_म_लिखो(m, "max_checked   :%d\n", debug_objects_maxchecked);
	seq_म_लिखो(m, "warnings      :%d\n", debug_objects_warnings);
	seq_म_लिखो(m, "fixups        :%d\n", debug_objects_fixups);
	seq_म_लिखो(m, "pool_free     :%d\n", READ_ONCE(obj_pool_मुक्त) + obj_percpu_मुक्त);
	seq_म_लिखो(m, "pool_pcp_free :%d\n", obj_percpu_मुक्त);
	seq_म_लिखो(m, "pool_min_free :%d\n", obj_pool_min_मुक्त);
	seq_म_लिखो(m, "pool_used     :%d\n", obj_pool_used - obj_percpu_मुक्त);
	seq_म_लिखो(m, "pool_max_used :%d\n", obj_pool_max_used);
	seq_म_लिखो(m, "on_free_list  :%d\n", READ_ONCE(obj_nr_toमुक्त));
	seq_म_लिखो(m, "objs_allocated:%d\n", debug_objects_allocated);
	seq_म_लिखो(m, "objs_freed    :%d\n", debug_objects_मुक्तd);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debug_stats);

अटल पूर्णांक __init debug_objects_init_debugfs(व्योम)
अणु
	काष्ठा dentry *dbgdir;

	अगर (!debug_objects_enabled)
		वापस 0;

	dbgdir = debugfs_create_dir("debug_objects", शून्य);

	debugfs_create_file("stats", 0444, dbgdir, शून्य, &debug_stats_fops);

	वापस 0;
पूर्ण
__initcall(debug_objects_init_debugfs);

#अन्यथा
अटल अंतरभूत व्योम debug_objects_init_debugfs(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_OBJECTS_SELFTEST

/* Ranकरोm data काष्ठाure क्रम the self test */
काष्ठा self_test अणु
	अचिन्हित दीर्घ	dummy1[6];
	पूर्णांक		अटल_init;
	अचिन्हित दीर्घ	dummy2[3];
पूर्ण;

अटल __initस्थिर स्थिर काष्ठा debug_obj_descr descr_type_test;

अटल bool __init is_अटल_object(व्योम *addr)
अणु
	काष्ठा self_test *obj = addr;

	वापस obj->अटल_init;
पूर्ण

/*
 * fixup_init is called when:
 * - an active object is initialized
 */
अटल bool __init fixup_init(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा self_test *obj = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		debug_object_deactivate(obj, &descr_type_test);
		debug_object_init(obj, &descr_type_test);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * fixup_activate is called when:
 * - an active object is activated
 * - an unknown non-अटल object is activated
 */
अटल bool __init fixup_activate(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा self_test *obj = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_NOTAVAILABLE:
		वापस true;
	हाल ODEBUG_STATE_ACTIVE:
		debug_object_deactivate(obj, &descr_type_test);
		debug_object_activate(obj, &descr_type_test);
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * fixup_destroy is called when:
 * - an active object is destroyed
 */
अटल bool __init fixup_destroy(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा self_test *obj = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		debug_object_deactivate(obj, &descr_type_test);
		debug_object_destroy(obj, &descr_type_test);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * fixup_मुक्त is called when:
 * - an active object is मुक्तd
 */
अटल bool __init fixup_मुक्त(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा self_test *obj = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		debug_object_deactivate(obj, &descr_type_test);
		debug_object_मुक्त(obj, &descr_type_test);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक __init
check_results(व्योम *addr, क्रमागत debug_obj_state state, पूर्णांक fixups, पूर्णांक warnings)
अणु
	काष्ठा debug_bucket *db;
	काष्ठा debug_obj *obj;
	अचिन्हित दीर्घ flags;
	पूर्णांक res = -EINVAL;

	db = get_bucket((अचिन्हित दीर्घ) addr);

	raw_spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	अगर (!obj && state != ODEBUG_STATE_NONE) अणु
		WARN(1, KERN_ERR "ODEBUG: selftest object not found\n");
		जाओ out;
	पूर्ण
	अगर (obj && obj->state != state) अणु
		WARN(1, KERN_ERR "ODEBUG: selftest wrong state: %d != %d\n",
		       obj->state, state);
		जाओ out;
	पूर्ण
	अगर (fixups != debug_objects_fixups) अणु
		WARN(1, KERN_ERR "ODEBUG: selftest fixups failed %d != %d\n",
		       fixups, debug_objects_fixups);
		जाओ out;
	पूर्ण
	अगर (warnings != debug_objects_warnings) अणु
		WARN(1, KERN_ERR "ODEBUG: selftest warnings failed %d != %d\n",
		       warnings, debug_objects_warnings);
		जाओ out;
	पूर्ण
	res = 0;
out:
	raw_spin_unlock_irqrestore(&db->lock, flags);
	अगर (res)
		debug_objects_enabled = 0;
	वापस res;
पूर्ण

अटल __initस्थिर स्थिर काष्ठा debug_obj_descr descr_type_test = अणु
	.name			= "selftest",
	.is_अटल_object	= is_अटल_object,
	.fixup_init		= fixup_init,
	.fixup_activate		= fixup_activate,
	.fixup_destroy		= fixup_destroy,
	.fixup_मुक्त		= fixup_मुक्त,
पूर्ण;

अटल __initdata काष्ठा self_test obj = अणु .अटल_init = 0 पूर्ण;

अटल व्योम __init debug_objects_selftest(व्योम)
अणु
	पूर्णांक fixups, oldfixups, warnings, oldwarnings;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	fixups = oldfixups = debug_objects_fixups;
	warnings = oldwarnings = debug_objects_warnings;
	descr_test = &descr_type_test;

	debug_object_init(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_INIT, fixups, warnings))
		जाओ out;
	debug_object_activate(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_ACTIVE, fixups, warnings))
		जाओ out;
	debug_object_activate(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_ACTIVE, ++fixups, ++warnings))
		जाओ out;
	debug_object_deactivate(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_INACTIVE, fixups, warnings))
		जाओ out;
	debug_object_destroy(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_DESTROYED, fixups, warnings))
		जाओ out;
	debug_object_init(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_DESTROYED, fixups, ++warnings))
		जाओ out;
	debug_object_activate(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_DESTROYED, fixups, ++warnings))
		जाओ out;
	debug_object_deactivate(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_DESTROYED, fixups, ++warnings))
		जाओ out;
	debug_object_मुक्त(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_NONE, fixups, warnings))
		जाओ out;

	obj.अटल_init = 1;
	debug_object_activate(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_ACTIVE, fixups, warnings))
		जाओ out;
	debug_object_init(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_INIT, ++fixups, ++warnings))
		जाओ out;
	debug_object_मुक्त(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_NONE, fixups, warnings))
		जाओ out;

#अगर_घोषित CONFIG_DEBUG_OBJECTS_FREE
	debug_object_init(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_INIT, fixups, warnings))
		जाओ out;
	debug_object_activate(&obj, &descr_type_test);
	अगर (check_results(&obj, ODEBUG_STATE_ACTIVE, fixups, warnings))
		जाओ out;
	__debug_check_no_obj_मुक्तd(&obj, माप(obj));
	अगर (check_results(&obj, ODEBUG_STATE_NONE, ++fixups, ++warnings))
		जाओ out;
#पूर्ण_अगर
	pr_info("selftest passed\n");

out:
	debug_objects_fixups = oldfixups;
	debug_objects_warnings = oldwarnings;
	descr_test = शून्य;

	local_irq_restore(flags);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम debug_objects_selftest(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*
 * Called during early boot to initialize the hash buckets and link
 * the अटल object pool objects पूर्णांकo the poll list. After this call
 * the object tracker is fully operational.
 */
व्योम __init debug_objects_early_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ODEBUG_HASH_SIZE; i++)
		raw_spin_lock_init(&obj_hash[i].lock);

	क्रम (i = 0; i < ODEBUG_POOL_SIZE; i++)
		hlist_add_head(&obj_अटल_pool[i].node, &obj_pool);
पूर्ण

/*
 * Convert the अटलally allocated objects to dynamic ones:
 */
अटल पूर्णांक __init debug_objects_replace_अटल_objects(व्योम)
अणु
	काष्ठा debug_bucket *db = obj_hash;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा debug_obj *obj, *new;
	HLIST_HEAD(objects);
	पूर्णांक i, cnt = 0;

	क्रम (i = 0; i < ODEBUG_POOL_SIZE; i++) अणु
		obj = kmem_cache_zalloc(obj_cache, GFP_KERNEL);
		अगर (!obj)
			जाओ मुक्त;
		hlist_add_head(&obj->node, &objects);
	पूर्ण

	/*
	 * debug_objects_mem_init() is now called early that only one CPU is up
	 * and पूर्णांकerrupts have been disabled, so it is safe to replace the
	 * active object references.
	 */

	/* Remove the अटलally allocated objects from the pool */
	hlist_क्रम_each_entry_safe(obj, पंचांगp, &obj_pool, node)
		hlist_del(&obj->node);
	/* Move the allocated objects to the pool */
	hlist_move_list(&objects, &obj_pool);

	/* Replace the active object references */
	क्रम (i = 0; i < ODEBUG_HASH_SIZE; i++, db++) अणु
		hlist_move_list(&db->list, &objects);

		hlist_क्रम_each_entry(obj, &objects, node) अणु
			new = hlist_entry(obj_pool.first, typeof(*obj), node);
			hlist_del(&new->node);
			/* copy object data */
			*new = *obj;
			hlist_add_head(&new->node, &db->list);
			cnt++;
		पूर्ण
	पूर्ण

	pr_debug("%d of %d active objects replaced\n",
		 cnt, obj_pool_used);
	वापस 0;
मुक्त:
	hlist_क्रम_each_entry_safe(obj, पंचांगp, &objects, node) अणु
		hlist_del(&obj->node);
		kmem_cache_मुक्त(obj_cache, obj);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

/*
 * Called after the kmem_caches are functional to setup a dedicated
 * cache pool, which has the SLAB_DEBUG_OBJECTS flag set. This flag
 * prevents that the debug code is called on kmem_cache_मुक्त() क्रम the
 * debug tracker objects to aव्योम recursive calls.
 */
व्योम __init debug_objects_mem_init(व्योम)
अणु
	पूर्णांक cpu, extras;

	अगर (!debug_objects_enabled)
		वापस;

	/*
	 * Initialize the percpu object pools
	 *
	 * Initialization is not strictly necessary, but was करोne क्रम
	 * completeness.
	 */
	क्रम_each_possible_cpu(cpu)
		INIT_HLIST_HEAD(&per_cpu(percpu_obj_pool.मुक्त_objs, cpu));

	obj_cache = kmem_cache_create("debug_objects_cache",
				      माप (काष्ठा debug_obj), 0,
				      SLAB_DEBUG_OBJECTS | SLAB_NOLEAKTRACE,
				      शून्य);

	अगर (!obj_cache || debug_objects_replace_अटल_objects()) अणु
		debug_objects_enabled = 0;
		kmem_cache_destroy(obj_cache);
		pr_warn("out of memory.\n");
	पूर्ण अन्यथा
		debug_objects_selftest();

#अगर_घोषित CONFIG_HOTPLUG_CPU
	cpuhp_setup_state_nocalls(CPUHP_DEBUG_OBJ_DEAD, "object:offline", शून्य,
					object_cpu_offline);
#पूर्ण_अगर

	/*
	 * Increase the thresholds क्रम allocating and मुक्तing objects
	 * according to the number of possible CPUs available in the प्रणाली.
	 */
	extras = num_possible_cpus() * ODEBUG_BATCH_SIZE;
	debug_objects_pool_size += extras;
	debug_objects_pool_min_level += extras;
पूर्ण
