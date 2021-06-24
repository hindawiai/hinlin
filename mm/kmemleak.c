<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/kmemleak.c
 *
 * Copyright (C) 2008 ARM Limited
 * Written by Catalin Marinas <catalin.marinas@arm.com>
 *
 * For more inक्रमmation on the algorithm and kmemleak usage, please see
 * Documentation/dev-tools/kmemleak.rst.
 *
 * Notes on locking
 * ----------------
 *
 * The following locks and mutexes are used by kmemleak:
 *
 * - kmemleak_lock (raw_spinlock_t): protects the object_list modअगरications and
 *   accesses to the object_tree_root. The object_list is the मुख्य list
 *   holding the metadata (काष्ठा kmemleak_object) क्रम the allocated memory
 *   blocks. The object_tree_root is a red black tree used to look-up
 *   metadata based on a poपूर्णांकer to the corresponding memory block.  The
 *   kmemleak_object काष्ठाures are added to the object_list and
 *   object_tree_root in the create_object() function called from the
 *   kmemleak_alloc() callback and हटाओd in delete_object() called from the
 *   kmemleak_मुक्त() callback
 * - kmemleak_object.lock (raw_spinlock_t): protects a kmemleak_object.
 *   Accesses to the metadata (e.g. count) are रक्षित by this lock. Note
 *   that some members of this काष्ठाure may be रक्षित by other means
 *   (atomic or kmemleak_lock). This lock is also held when scanning the
 *   corresponding memory block to aव्योम the kernel मुक्तing it via the
 *   kmemleak_मुक्त() callback. This is less heavyweight than holding a global
 *   lock like kmemleak_lock during scanning.
 * - scan_mutex (mutex): ensures that only one thपढ़ो may scan the memory क्रम
 *   unreferenced objects at a समय. The gray_list contains the objects which
 *   are alपढ़ोy referenced or marked as false positives and need to be
 *   scanned. This list is only modअगरied during a scanning episode when the
 *   scan_mutex is held. At the end of a scan, the gray_list is always empty.
 *   Note that the kmemleak_object.use_count is incremented when an object is
 *   added to the gray_list and thereक्रमe cannot be मुक्तd. This mutex also
 *   prevents multiple users of the "kmemleak" debugfs file together with
 *   modअगरications to the memory scanning parameters including the scan_thपढ़ो
 *   poपूर्णांकer
 *
 * Locks and mutexes are acquired/nested in the following order:
 *
 *   scan_mutex [-> object->lock] -> kmemleak_lock -> other_object->lock (SINGLE_DEPTH_NESTING)
 *
 * No kmemleak_lock and object->lock nesting is allowed outside scan_mutex
 * regions.
 *
 * The kmemleak_object काष्ठाures have a use_count incremented or decremented
 * using the get_object()/put_object() functions. When the use_count becomes
 * 0, this count can no दीर्घer be incremented and put_object() schedules the
 * kmemleak_object मुक्तing via an RCU callback. All calls to the get_object()
 * function must be रक्षित by rcu_पढ़ो_lock() to aव्योम accessing a मुक्तd
 * काष्ठाure.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/cache.h>
#समावेश <linux/percpu.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pfn.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/slab.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/err.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/माला.स>
#समावेश <linux/nodemask.h>
#समावेश <linux/mm.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/crc32.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/atomic.h>

#समावेश <linux/kasan.h>
#समावेश <linux/kfence.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/memory_hotplug.h>

/*
 * Kmemleak configuration and common defines.
 */
#घोषणा MAX_TRACE		16	/* stack trace length */
#घोषणा MSECS_MIN_AGE		5000	/* minimum object age क्रम reporting */
#घोषणा SECS_FIRST_SCAN		60	/* delay beक्रमe the first scan */
#घोषणा SECS_SCAN_WAIT		600	/* subsequent स्वतः scanning delay */
#घोषणा MAX_SCAN_SIZE		4096	/* maximum size of a scanned block */

#घोषणा BYTES_PER_POINTER	माप(व्योम *)

/* GFP biपंचांगask क्रम kmemleak पूर्णांकernal allocations */
#घोषणा gfp_kmemleak_mask(gfp)	(((gfp) & (GFP_KERNEL | GFP_ATOMIC)) | \
				 __GFP_NORETRY | __GFP_NOMEMALLOC | \
				 __GFP_NOWARN)

/* scanning area inside a memory block */
काष्ठा kmemleak_scan_area अणु
	काष्ठा hlist_node node;
	अचिन्हित दीर्घ start;
	माप_प्रकार size;
पूर्ण;

#घोषणा KMEMLEAK_GREY	0
#घोषणा KMEMLEAK_BLACK	-1

/*
 * Structure holding the metadata क्रम each allocated memory block.
 * Modअगरications to such objects should be made जबतक holding the
 * object->lock. Insertions or deletions from object_list, gray_list or
 * rb_node are alपढ़ोy रक्षित by the corresponding locks or mutex (see
 * the notes on locking above). These objects are reference-counted
 * (use_count) and मुक्तd using the RCU mechanism.
 */
काष्ठा kmemleak_object अणु
	raw_spinlock_t lock;
	अचिन्हित पूर्णांक flags;		/* object status flags */
	काष्ठा list_head object_list;
	काष्ठा list_head gray_list;
	काष्ठा rb_node rb_node;
	काष्ठा rcu_head rcu;		/* object_list lockless traversal */
	/* object usage count; object मुक्तd when use_count == 0 */
	atomic_t use_count;
	अचिन्हित दीर्घ poपूर्णांकer;
	माप_प्रकार size;
	/* pass surplus references to this poपूर्णांकer */
	अचिन्हित दीर्घ excess_ref;
	/* minimum number of a poपूर्णांकers found beक्रमe it is considered leak */
	पूर्णांक min_count;
	/* the total number of poपूर्णांकers found poपूर्णांकing to this object */
	पूर्णांक count;
	/* checksum क्रम detecting modअगरied objects */
	u32 checksum;
	/* memory ranges to be scanned inside an object (empty क्रम all) */
	काष्ठा hlist_head area_list;
	अचिन्हित दीर्घ trace[MAX_TRACE];
	अचिन्हित पूर्णांक trace_len;
	अचिन्हित दीर्घ jअगरfies;		/* creation बारtamp */
	pid_t pid;			/* pid of the current task */
	अक्षर comm[TASK_COMM_LEN];	/* executable name */
पूर्ण;

/* flag representing the memory block allocation status */
#घोषणा OBJECT_ALLOCATED	(1 << 0)
/* flag set after the first reporting of an unreference object */
#घोषणा OBJECT_REPORTED		(1 << 1)
/* flag set to not scan the object */
#घोषणा OBJECT_NO_SCAN		(1 << 2)
/* flag set to fully scan the object when scan_area allocation failed */
#घोषणा OBJECT_FULL_SCAN	(1 << 3)

#घोषणा HEX_PREFIX		"    "
/* number of bytes to prपूर्णांक per line; must be 16 or 32 */
#घोषणा HEX_ROW_SIZE		16
/* number of bytes to prपूर्णांक at a समय (1, 2, 4, 8) */
#घोषणा HEX_GROUP_SIZE		1
/* include ASCII after the hex output */
#घोषणा HEX_ASCII		1
/* max number of lines to be prपूर्णांकed */
#घोषणा HEX_MAX_LINES		2

/* the list of all allocated objects */
अटल LIST_HEAD(object_list);
/* the list of gray-colored objects (see color_gray comment below) */
अटल LIST_HEAD(gray_list);
/* memory pool allocation */
अटल काष्ठा kmemleak_object mem_pool[CONFIG_DEBUG_KMEMLEAK_MEM_POOL_SIZE];
अटल पूर्णांक mem_pool_मुक्त_count = ARRAY_SIZE(mem_pool);
अटल LIST_HEAD(mem_pool_मुक्त_list);
/* search tree क्रम object boundaries */
अटल काष्ठा rb_root object_tree_root = RB_ROOT;
/* protecting the access to object_list and object_tree_root */
अटल DEFINE_RAW_SPINLOCK(kmemleak_lock);

/* allocation caches क्रम kmemleak पूर्णांकernal data */
अटल काष्ठा kmem_cache *object_cache;
अटल काष्ठा kmem_cache *scan_area_cache;

/* set अगर tracing memory operations is enabled */
अटल पूर्णांक kmemleak_enabled = 1;
/* same as above but only क्रम the kmemleak_मुक्त() callback */
अटल पूर्णांक kmemleak_मुक्त_enabled = 1;
/* set in the late_initcall अगर there were no errors */
अटल पूर्णांक kmemleak_initialized;
/* set अगर a kmemleak warning was issued */
अटल पूर्णांक kmemleak_warning;
/* set अगर a fatal kmemleak error has occurred */
अटल पूर्णांक kmemleak_error;

/* minimum and maximum address that may be valid poपूर्णांकers */
अटल अचिन्हित दीर्घ min_addr = अच_दीर्घ_उच्च;
अटल अचिन्हित दीर्घ max_addr;

अटल काष्ठा task_काष्ठा *scan_thपढ़ो;
/* used to aव्योम reporting of recently allocated objects */
अटल अचिन्हित दीर्घ jअगरfies_min_age;
अटल अचिन्हित दीर्घ jअगरfies_last_scan;
/* delay between स्वतःmatic memory scannings */
अटल चिन्हित दीर्घ jअगरfies_scan_रुको;
/* enables or disables the task stacks scanning */
अटल पूर्णांक kmemleak_stack_scan = 1;
/* protects the memory scanning, parameters and debug/kmemleak file access */
अटल DEFINE_MUTEX(scan_mutex);
/* setting kmemleak=on, will set this var, skipping the disable */
अटल पूर्णांक kmemleak_skip_disable;
/* If there are leaks that can be reported */
अटल bool kmemleak_found_leaks;

अटल bool kmemleak_verbose;
module_param_named(verbose, kmemleak_verbose, bool, 0600);

अटल व्योम kmemleak_disable(व्योम);

/*
 * Prपूर्णांक a warning and dump the stack trace.
 */
#घोषणा kmemleak_warn(x...)	करो अणु		\
	pr_warn(x);				\
	dump_stack();				\
	kmemleak_warning = 1;			\
पूर्ण जबतक (0)

/*
 * Macro invoked when a serious kmemleak condition occurred and cannot be
 * recovered from. Kmemleak will be disabled and further allocation/मुक्तing
 * tracing no दीर्घer available.
 */
#घोषणा kmemleak_stop(x...)	करो अणु	\
	kmemleak_warn(x);		\
	kmemleak_disable();		\
पूर्ण जबतक (0)

#घोषणा warn_or_seq_म_लिखो(seq, fmt, ...)	करो अणु	\
	अगर (seq)					\
		seq_म_लिखो(seq, fmt, ##__VA_ARGS__);	\
	अन्यथा						\
		pr_warn(fmt, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

अटल व्योम warn_or_seq_hex_dump(काष्ठा seq_file *seq, पूर्णांक prefix_type,
				 पूर्णांक rowsize, पूर्णांक groupsize, स्थिर व्योम *buf,
				 माप_प्रकार len, bool ascii)
अणु
	अगर (seq)
		seq_hex_dump(seq, HEX_PREFIX, prefix_type, rowsize, groupsize,
			     buf, len, ascii);
	अन्यथा
		prपूर्णांक_hex_dump(KERN_WARNING, pr_fmt(HEX_PREFIX), prefix_type,
			       rowsize, groupsize, buf, len, ascii);
पूर्ण

/*
 * Prपूर्णांकing of the objects hex dump to the seq file. The number of lines to be
 * prपूर्णांकed is limited to HEX_MAX_LINES to prevent seq file spamming. The
 * actual number of prपूर्णांकed bytes depends on HEX_ROW_SIZE. It must be called
 * with the object->lock held.
 */
अटल व्योम hex_dump_object(काष्ठा seq_file *seq,
			    काष्ठा kmemleak_object *object)
अणु
	स्थिर u8 *ptr = (स्थिर u8 *)object->poपूर्णांकer;
	माप_प्रकार len;

	/* limit the number of lines to HEX_MAX_LINES */
	len = min_t(माप_प्रकार, object->size, HEX_MAX_LINES * HEX_ROW_SIZE);

	warn_or_seq_म_लिखो(seq, "  hex dump (first %zu bytes):\n", len);
	kasan_disable_current();
	warn_or_seq_hex_dump(seq, DUMP_PREFIX_NONE, HEX_ROW_SIZE,
			     HEX_GROUP_SIZE, ptr, len, HEX_ASCII);
	kasan_enable_current();
पूर्ण

/*
 * Object colors, encoded with count and min_count:
 * - white - orphan object, not enough references to it (count < min_count)
 * - gray  - not orphan, not marked as false positive (min_count == 0) or
 *		sufficient references to it (count >= min_count)
 * - black - ignore, it करोesn't contain references (e.g. text section)
 *		(min_count == -1). No function defined क्रम this color.
 * Newly created objects करोn't have any color asचिन्हित (object->count == -1)
 * beक्रमe the next memory scan when they become white.
 */
अटल bool color_white(स्थिर काष्ठा kmemleak_object *object)
अणु
	वापस object->count != KMEMLEAK_BLACK &&
		object->count < object->min_count;
पूर्ण

अटल bool color_gray(स्थिर काष्ठा kmemleak_object *object)
अणु
	वापस object->min_count != KMEMLEAK_BLACK &&
		object->count >= object->min_count;
पूर्ण

/*
 * Objects are considered unreferenced only अगर their color is white, they have
 * not be deleted and have a minimum age to aव्योम false positives caused by
 * poपूर्णांकers temporarily stored in CPU रेजिस्टरs.
 */
अटल bool unreferenced_object(काष्ठा kmemleak_object *object)
अणु
	वापस (color_white(object) && object->flags & OBJECT_ALLOCATED) &&
		समय_beक्रमe_eq(object->jअगरfies + jअगरfies_min_age,
			       jअगरfies_last_scan);
पूर्ण

/*
 * Prपूर्णांकing of the unreferenced objects inक्रमmation to the seq file. The
 * prपूर्णांक_unreferenced function must be called with the object->lock held.
 */
अटल व्योम prपूर्णांक_unreferenced(काष्ठा seq_file *seq,
			       काष्ठा kmemleak_object *object)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक msecs_age = jअगरfies_to_msecs(jअगरfies - object->jअगरfies);

	warn_or_seq_म_लिखो(seq, "unreferenced object 0x%08lx (size %zu):\n",
		   object->poपूर्णांकer, object->size);
	warn_or_seq_म_लिखो(seq, "  comm \"%s\", pid %d, jiffies %lu (age %d.%03ds)\n",
		   object->comm, object->pid, object->jअगरfies,
		   msecs_age / 1000, msecs_age % 1000);
	hex_dump_object(seq, object);
	warn_or_seq_म_लिखो(seq, "  backtrace:\n");

	क्रम (i = 0; i < object->trace_len; i++) अणु
		व्योम *ptr = (व्योम *)object->trace[i];
		warn_or_seq_म_लिखो(seq, "    [<%p>] %pS\n", ptr, ptr);
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक the kmemleak_object inक्रमmation. This function is used मुख्यly क्रम
 * debugging special हालs when kmemleak operations. It must be called with
 * the object->lock held.
 */
अटल व्योम dump_object_info(काष्ठा kmemleak_object *object)
अणु
	pr_notice("Object 0x%08lx (size %zu):\n",
		  object->poपूर्णांकer, object->size);
	pr_notice("  comm \"%s\", pid %d, jiffies %lu\n",
		  object->comm, object->pid, object->jअगरfies);
	pr_notice("  min_count = %d\n", object->min_count);
	pr_notice("  count = %d\n", object->count);
	pr_notice("  flags = 0x%x\n", object->flags);
	pr_notice("  checksum = %u\n", object->checksum);
	pr_notice("  backtrace:\n");
	stack_trace_prपूर्णांक(object->trace, object->trace_len, 4);
पूर्ण

/*
 * Look-up a memory block metadata (kmemleak_object) in the object search
 * tree based on a poपूर्णांकer value. If alias is 0, only values poपूर्णांकing to the
 * beginning of the memory block are allowed. The kmemleak_lock must be held
 * when calling this function.
 */
अटल काष्ठा kmemleak_object *lookup_object(अचिन्हित दीर्घ ptr, पूर्णांक alias)
अणु
	काष्ठा rb_node *rb = object_tree_root.rb_node;

	जबतक (rb) अणु
		काष्ठा kmemleak_object *object =
			rb_entry(rb, काष्ठा kmemleak_object, rb_node);
		अगर (ptr < object->poपूर्णांकer)
			rb = object->rb_node.rb_left;
		अन्यथा अगर (object->poपूर्णांकer + object->size <= ptr)
			rb = object->rb_node.rb_right;
		अन्यथा अगर (object->poपूर्णांकer == ptr || alias)
			वापस object;
		अन्यथा अणु
			kmemleak_warn("Found object by alias at 0x%08lx\n",
				      ptr);
			dump_object_info(object);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Increment the object use_count. Return 1 अगर successful or 0 otherwise. Note
 * that once an object's use_count reached 0, the RCU मुक्तing was alपढ़ोy
 * रेजिस्टरed and the object should no दीर्घer be used. This function must be
 * called under the protection of rcu_पढ़ो_lock().
 */
अटल पूर्णांक get_object(काष्ठा kmemleak_object *object)
अणु
	वापस atomic_inc_not_zero(&object->use_count);
पूर्ण

/*
 * Memory pool allocation and मुक्तing. kmemleak_lock must not be held.
 */
अटल काष्ठा kmemleak_object *mem_pool_alloc(gfp_t gfp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kmemleak_object *object;

	/* try the slab allocator first */
	अगर (object_cache) अणु
		object = kmem_cache_alloc(object_cache, gfp_kmemleak_mask(gfp));
		अगर (object)
			वापस object;
	पूर्ण

	/* slab allocation failed, try the memory pool */
	raw_spin_lock_irqsave(&kmemleak_lock, flags);
	object = list_first_entry_or_null(&mem_pool_मुक्त_list,
					  typeof(*object), object_list);
	अगर (object)
		list_del(&object->object_list);
	अन्यथा अगर (mem_pool_मुक्त_count)
		object = &mem_pool[--mem_pool_मुक्त_count];
	अन्यथा
		pr_warn_once("Memory pool empty, consider increasing CONFIG_DEBUG_KMEMLEAK_MEM_POOL_SIZE\n");
	raw_spin_unlock_irqrestore(&kmemleak_lock, flags);

	वापस object;
पूर्ण

/*
 * Return the object to either the slab allocator or the memory pool.
 */
अटल व्योम mem_pool_मुक्त(काष्ठा kmemleak_object *object)
अणु
	अचिन्हित दीर्घ flags;

	अगर (object < mem_pool || object >= mem_pool + ARRAY_SIZE(mem_pool)) अणु
		kmem_cache_मुक्त(object_cache, object);
		वापस;
	पूर्ण

	/* add the object to the memory pool मुक्त list */
	raw_spin_lock_irqsave(&kmemleak_lock, flags);
	list_add(&object->object_list, &mem_pool_मुक्त_list);
	raw_spin_unlock_irqrestore(&kmemleak_lock, flags);
पूर्ण

/*
 * RCU callback to मुक्त a kmemleak_object.
 */
अटल व्योम मुक्त_object_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा hlist_node *पंचांगp;
	काष्ठा kmemleak_scan_area *area;
	काष्ठा kmemleak_object *object =
		container_of(rcu, काष्ठा kmemleak_object, rcu);

	/*
	 * Once use_count is 0 (guaranteed by put_object), there is no other
	 * code accessing this object, hence no need क्रम locking.
	 */
	hlist_क्रम_each_entry_safe(area, पंचांगp, &object->area_list, node) अणु
		hlist_del(&area->node);
		kmem_cache_मुक्त(scan_area_cache, area);
	पूर्ण
	mem_pool_मुक्त(object);
पूर्ण

/*
 * Decrement the object use_count. Once the count is 0, मुक्त the object using
 * an RCU callback. Since put_object() may be called via the kmemleak_मुक्त() ->
 * delete_object() path, the delayed RCU मुक्तing ensures that there is no
 * recursive call to the kernel allocator. Lock-less RCU object_list traversal
 * is also possible.
 */
अटल व्योम put_object(काष्ठा kmemleak_object *object)
अणु
	अगर (!atomic_dec_and_test(&object->use_count))
		वापस;

	/* should only get here after delete_object was called */
	WARN_ON(object->flags & OBJECT_ALLOCATED);

	/*
	 * It may be too early क्रम the RCU callbacks, however, there is no
	 * concurrent object_list traversal when !object_cache and all objects
	 * came from the memory pool. Free the object directly.
	 */
	अगर (object_cache)
		call_rcu(&object->rcu, मुक्त_object_rcu);
	अन्यथा
		मुक्त_object_rcu(&object->rcu);
पूर्ण

/*
 * Look up an object in the object search tree and increase its use_count.
 */
अटल काष्ठा kmemleak_object *find_and_get_object(अचिन्हित दीर्घ ptr, पूर्णांक alias)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kmemleak_object *object;

	rcu_पढ़ो_lock();
	raw_spin_lock_irqsave(&kmemleak_lock, flags);
	object = lookup_object(ptr, alias);
	raw_spin_unlock_irqrestore(&kmemleak_lock, flags);

	/* check whether the object is still available */
	अगर (object && !get_object(object))
		object = शून्य;
	rcu_पढ़ो_unlock();

	वापस object;
पूर्ण

/*
 * Remove an object from the object_tree_root and object_list. Must be called
 * with the kmemleak_lock held _अगर_ kmemleak is still enabled.
 */
अटल व्योम __हटाओ_object(काष्ठा kmemleak_object *object)
अणु
	rb_erase(&object->rb_node, &object_tree_root);
	list_del_rcu(&object->object_list);
पूर्ण

/*
 * Look up an object in the object search tree and हटाओ it from both
 * object_tree_root and object_list. The वापसed object's use_count should be
 * at least 1, as initially set by create_object().
 */
अटल काष्ठा kmemleak_object *find_and_हटाओ_object(अचिन्हित दीर्घ ptr, पूर्णांक alias)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kmemleak_object *object;

	raw_spin_lock_irqsave(&kmemleak_lock, flags);
	object = lookup_object(ptr, alias);
	अगर (object)
		__हटाओ_object(object);
	raw_spin_unlock_irqrestore(&kmemleak_lock, flags);

	वापस object;
पूर्ण

/*
 * Save stack trace to the given array of MAX_TRACE size.
 */
अटल पूर्णांक __save_stack_trace(अचिन्हित दीर्घ *trace)
अणु
	वापस stack_trace_save(trace, MAX_TRACE, 2);
पूर्ण

/*
 * Create the metadata (काष्ठा kmemleak_object) corresponding to an allocated
 * memory block and add it to the object_list and object_tree_root.
 */
अटल काष्ठा kmemleak_object *create_object(अचिन्हित दीर्घ ptr, माप_प्रकार size,
					     पूर्णांक min_count, gfp_t gfp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kmemleak_object *object, *parent;
	काष्ठा rb_node **link, *rb_parent;
	अचिन्हित दीर्घ untagged_ptr;

	object = mem_pool_alloc(gfp);
	अगर (!object) अणु
		pr_warn("Cannot allocate a kmemleak_object structure\n");
		kmemleak_disable();
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&object->object_list);
	INIT_LIST_HEAD(&object->gray_list);
	INIT_HLIST_HEAD(&object->area_list);
	raw_spin_lock_init(&object->lock);
	atomic_set(&object->use_count, 1);
	object->flags = OBJECT_ALLOCATED;
	object->poपूर्णांकer = ptr;
	object->size = kfence_ksize((व्योम *)ptr) ?: size;
	object->excess_ref = 0;
	object->min_count = min_count;
	object->count = 0;			/* white color initially */
	object->jअगरfies = jअगरfies;
	object->checksum = 0;

	/* task inक्रमmation */
	अगर (in_irq()) अणु
		object->pid = 0;
		म_नकलन(object->comm, "hardirq", माप(object->comm));
	पूर्ण अन्यथा अगर (in_serving_softirq()) अणु
		object->pid = 0;
		म_नकलन(object->comm, "softirq", माप(object->comm));
	पूर्ण अन्यथा अणु
		object->pid = current->pid;
		/*
		 * There is a small chance of a race with set_task_comm(),
		 * however using get_task_comm() here may cause locking
		 * dependency issues with current->alloc_lock. In the worst
		 * हाल, the command line is not correct.
		 */
		म_नकलन(object->comm, current->comm, माप(object->comm));
	पूर्ण

	/* kernel backtrace */
	object->trace_len = __save_stack_trace(object->trace);

	raw_spin_lock_irqsave(&kmemleak_lock, flags);

	untagged_ptr = (अचिन्हित दीर्घ)kasan_reset_tag((व्योम *)ptr);
	min_addr = min(min_addr, untagged_ptr);
	max_addr = max(max_addr, untagged_ptr + size);
	link = &object_tree_root.rb_node;
	rb_parent = शून्य;
	जबतक (*link) अणु
		rb_parent = *link;
		parent = rb_entry(rb_parent, काष्ठा kmemleak_object, rb_node);
		अगर (ptr + size <= parent->poपूर्णांकer)
			link = &parent->rb_node.rb_left;
		अन्यथा अगर (parent->poपूर्णांकer + parent->size <= ptr)
			link = &parent->rb_node.rb_right;
		अन्यथा अणु
			kmemleak_stop("Cannot insert 0x%lx into the object search tree (overlaps existing)\n",
				      ptr);
			/*
			 * No need क्रम parent->lock here since "parent" cannot
			 * be मुक्तd जबतक the kmemleak_lock is held.
			 */
			dump_object_info(parent);
			kmem_cache_मुक्त(object_cache, object);
			object = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण
	rb_link_node(&object->rb_node, rb_parent, link);
	rb_insert_color(&object->rb_node, &object_tree_root);

	list_add_tail_rcu(&object->object_list, &object_list);
out:
	raw_spin_unlock_irqrestore(&kmemleak_lock, flags);
	वापस object;
पूर्ण

/*
 * Mark the object as not allocated and schedule RCU मुक्तing via put_object().
 */
अटल व्योम __delete_object(काष्ठा kmemleak_object *object)
अणु
	अचिन्हित दीर्घ flags;

	WARN_ON(!(object->flags & OBJECT_ALLOCATED));
	WARN_ON(atomic_पढ़ो(&object->use_count) < 1);

	/*
	 * Locking here also ensures that the corresponding memory block
	 * cannot be मुक्तd when it is being scanned.
	 */
	raw_spin_lock_irqsave(&object->lock, flags);
	object->flags &= ~OBJECT_ALLOCATED;
	raw_spin_unlock_irqrestore(&object->lock, flags);
	put_object(object);
पूर्ण

/*
 * Look up the metadata (काष्ठा kmemleak_object) corresponding to ptr and
 * delete it.
 */
अटल व्योम delete_object_full(अचिन्हित दीर्घ ptr)
अणु
	काष्ठा kmemleak_object *object;

	object = find_and_हटाओ_object(ptr, 0);
	अगर (!object) अणु
#अगर_घोषित DEBUG
		kmemleak_warn("Freeing unknown object at 0x%08lx\n",
			      ptr);
#पूर्ण_अगर
		वापस;
	पूर्ण
	__delete_object(object);
पूर्ण

/*
 * Look up the metadata (काष्ठा kmemleak_object) corresponding to ptr and
 * delete it. If the memory block is partially मुक्तd, the function may create
 * additional metadata क्रम the reमुख्यing parts of the block.
 */
अटल व्योम delete_object_part(अचिन्हित दीर्घ ptr, माप_प्रकार size)
अणु
	काष्ठा kmemleak_object *object;
	अचिन्हित दीर्घ start, end;

	object = find_and_हटाओ_object(ptr, 1);
	अगर (!object) अणु
#अगर_घोषित DEBUG
		kmemleak_warn("Partially freeing unknown object at 0x%08lx (size %zu)\n",
			      ptr, size);
#पूर्ण_अगर
		वापस;
	पूर्ण

	/*
	 * Create one or two objects that may result from the memory block
	 * split. Note that partial मुक्तing is only करोne by मुक्त_booपंचांगem() and
	 * this happens beक्रमe kmemleak_init() is called.
	 */
	start = object->poपूर्णांकer;
	end = object->poपूर्णांकer + object->size;
	अगर (ptr > start)
		create_object(start, ptr - start, object->min_count,
			      GFP_KERNEL);
	अगर (ptr + size < end)
		create_object(ptr + size, end - ptr - size, object->min_count,
			      GFP_KERNEL);

	__delete_object(object);
पूर्ण

अटल व्योम __paपूर्णांक_it(काष्ठा kmemleak_object *object, पूर्णांक color)
अणु
	object->min_count = color;
	अगर (color == KMEMLEAK_BLACK)
		object->flags |= OBJECT_NO_SCAN;
पूर्ण

अटल व्योम paपूर्णांक_it(काष्ठा kmemleak_object *object, पूर्णांक color)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&object->lock, flags);
	__paपूर्णांक_it(object, color);
	raw_spin_unlock_irqrestore(&object->lock, flags);
पूर्ण

अटल व्योम paपूर्णांक_ptr(अचिन्हित दीर्घ ptr, पूर्णांक color)
अणु
	काष्ठा kmemleak_object *object;

	object = find_and_get_object(ptr, 0);
	अगर (!object) अणु
		kmemleak_warn("Trying to color unknown object at 0x%08lx as %s\n",
			      ptr,
			      (color == KMEMLEAK_GREY) ? "Grey" :
			      (color == KMEMLEAK_BLACK) ? "Black" : "Unknown");
		वापस;
	पूर्ण
	paपूर्णांक_it(object, color);
	put_object(object);
पूर्ण

/*
 * Mark an object permanently as gray-colored so that it can no दीर्घer be
 * reported as a leak. This is used in general to mark a false positive.
 */
अटल व्योम make_gray_object(अचिन्हित दीर्घ ptr)
अणु
	paपूर्णांक_ptr(ptr, KMEMLEAK_GREY);
पूर्ण

/*
 * Mark the object as black-colored so that it is ignored from scans and
 * reporting.
 */
अटल व्योम make_black_object(अचिन्हित दीर्घ ptr)
अणु
	paपूर्णांक_ptr(ptr, KMEMLEAK_BLACK);
पूर्ण

/*
 * Add a scanning area to the object. If at least one such area is added,
 * kmemleak will only scan these ranges rather than the whole memory block.
 */
अटल व्योम add_scan_area(अचिन्हित दीर्घ ptr, माप_प्रकार size, gfp_t gfp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kmemleak_object *object;
	काष्ठा kmemleak_scan_area *area = शून्य;

	object = find_and_get_object(ptr, 1);
	अगर (!object) अणु
		kmemleak_warn("Adding scan area to unknown object at 0x%08lx\n",
			      ptr);
		वापस;
	पूर्ण

	अगर (scan_area_cache)
		area = kmem_cache_alloc(scan_area_cache, gfp_kmemleak_mask(gfp));

	raw_spin_lock_irqsave(&object->lock, flags);
	अगर (!area) अणु
		pr_warn_once("Cannot allocate a scan area, scanning the full object\n");
		/* mark the object क्रम full scan to aव्योम false positives */
		object->flags |= OBJECT_FULL_SCAN;
		जाओ out_unlock;
	पूर्ण
	अगर (size == SIZE_MAX) अणु
		size = object->poपूर्णांकer + object->size - ptr;
	पूर्ण अन्यथा अगर (ptr + size > object->poपूर्णांकer + object->size) अणु
		kmemleak_warn("Scan area larger than object 0x%08lx\n", ptr);
		dump_object_info(object);
		kmem_cache_मुक्त(scan_area_cache, area);
		जाओ out_unlock;
	पूर्ण

	INIT_HLIST_NODE(&area->node);
	area->start = ptr;
	area->size = size;

	hlist_add_head(&area->node, &object->area_list);
out_unlock:
	raw_spin_unlock_irqrestore(&object->lock, flags);
	put_object(object);
पूर्ण

/*
 * Any surplus references (object alपढ़ोy gray) to 'ptr' are passed to
 * 'excess_ref'. This is used in the vदो_स्मृति() हाल where a poपूर्णांकer to
 * vm_काष्ठा may be used as an alternative reference to the vदो_स्मृति'ed object
 * (see मुक्त_thपढ़ो_stack()).
 */
अटल व्योम object_set_excess_ref(अचिन्हित दीर्घ ptr, अचिन्हित दीर्घ excess_ref)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kmemleak_object *object;

	object = find_and_get_object(ptr, 0);
	अगर (!object) अणु
		kmemleak_warn("Setting excess_ref on unknown object at 0x%08lx\n",
			      ptr);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&object->lock, flags);
	object->excess_ref = excess_ref;
	raw_spin_unlock_irqrestore(&object->lock, flags);
	put_object(object);
पूर्ण

/*
 * Set the OBJECT_NO_SCAN flag क्रम the object corresponding to the give
 * poपूर्णांकer. Such object will not be scanned by kmemleak but references to it
 * are searched.
 */
अटल व्योम object_no_scan(अचिन्हित दीर्घ ptr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kmemleak_object *object;

	object = find_and_get_object(ptr, 0);
	अगर (!object) अणु
		kmemleak_warn("Not scanning unknown object at 0x%08lx\n", ptr);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&object->lock, flags);
	object->flags |= OBJECT_NO_SCAN;
	raw_spin_unlock_irqrestore(&object->lock, flags);
	put_object(object);
पूर्ण

/**
 * kmemleak_alloc - रेजिस्टर a newly allocated object
 * @ptr:	poपूर्णांकer to beginning of the object
 * @size:	size of the object
 * @min_count:	minimum number of references to this object. If during memory
 *		scanning a number of references less than @min_count is found,
 *		the object is reported as a memory leak. If @min_count is 0,
 *		the object is never reported as a leak. If @min_count is -1,
 *		the object is ignored (not scanned and not reported as a leak)
 * @gfp:	kदो_स्मृति() flags used क्रम kmemleak पूर्णांकernal memory allocations
 *
 * This function is called from the kernel allocators when a new object
 * (memory block) is allocated (kmem_cache_alloc, kदो_स्मृति etc.).
 */
व्योम __ref kmemleak_alloc(स्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक min_count,
			  gfp_t gfp)
अणु
	pr_debug("%s(0x%p, %zu, %d)\n", __func__, ptr, size, min_count);

	अगर (kmemleak_enabled && ptr && !IS_ERR(ptr))
		create_object((अचिन्हित दीर्घ)ptr, size, min_count, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(kmemleak_alloc);

/**
 * kmemleak_alloc_percpu - रेजिस्टर a newly allocated __percpu object
 * @ptr:	__percpu poपूर्णांकer to beginning of the object
 * @size:	size of the object
 * @gfp:	flags used क्रम kmemleak पूर्णांकernal memory allocations
 *
 * This function is called from the kernel percpu allocator when a new object
 * (memory block) is allocated (alloc_percpu).
 */
व्योम __ref kmemleak_alloc_percpu(स्थिर व्योम __percpu *ptr, माप_प्रकार size,
				 gfp_t gfp)
अणु
	अचिन्हित पूर्णांक cpu;

	pr_debug("%s(0x%p, %zu)\n", __func__, ptr, size);

	/*
	 * Percpu allocations are only scanned and not reported as leaks
	 * (min_count is set to 0).
	 */
	अगर (kmemleak_enabled && ptr && !IS_ERR(ptr))
		क्रम_each_possible_cpu(cpu)
			create_object((अचिन्हित दीर्घ)per_cpu_ptr(ptr, cpu),
				      size, 0, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(kmemleak_alloc_percpu);

/**
 * kmemleak_vदो_स्मृति - रेजिस्टर a newly vदो_स्मृति'ed object
 * @area:	poपूर्णांकer to vm_काष्ठा
 * @size:	size of the object
 * @gfp:	__vदो_स्मृति() flags used क्रम kmemleak पूर्णांकernal memory allocations
 *
 * This function is called from the vदो_स्मृति() kernel allocator when a new
 * object (memory block) is allocated.
 */
व्योम __ref kmemleak_vदो_स्मृति(स्थिर काष्ठा vm_काष्ठा *area, माप_प्रकार size, gfp_t gfp)
अणु
	pr_debug("%s(0x%p, %zu)\n", __func__, area, size);

	/*
	 * A min_count = 2 is needed because vm_काष्ठा contains a reference to
	 * the भव address of the vदो_स्मृति'ed block.
	 */
	अगर (kmemleak_enabled) अणु
		create_object((अचिन्हित दीर्घ)area->addr, size, 2, gfp);
		object_set_excess_ref((अचिन्हित दीर्घ)area,
				      (अचिन्हित दीर्घ)area->addr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kmemleak_vदो_स्मृति);

/**
 * kmemleak_मुक्त - unरेजिस्टर a previously रेजिस्टरed object
 * @ptr:	poपूर्णांकer to beginning of the object
 *
 * This function is called from the kernel allocators when an object (memory
 * block) is मुक्तd (kmem_cache_मुक्त, kमुक्त, vमुक्त etc.).
 */
व्योम __ref kmemleak_मुक्त(स्थिर व्योम *ptr)
अणु
	pr_debug("%s(0x%p)\n", __func__, ptr);

	अगर (kmemleak_मुक्त_enabled && ptr && !IS_ERR(ptr))
		delete_object_full((अचिन्हित दीर्घ)ptr);
पूर्ण
EXPORT_SYMBOL_GPL(kmemleak_मुक्त);

/**
 * kmemleak_मुक्त_part - partially unरेजिस्टर a previously रेजिस्टरed object
 * @ptr:	poपूर्णांकer to the beginning or inside the object. This also
 *		represents the start of the range to be मुक्तd
 * @size:	size to be unरेजिस्टरed
 *
 * This function is called when only a part of a memory block is मुक्तd
 * (usually from the booपंचांगem allocator).
 */
व्योम __ref kmemleak_मुक्त_part(स्थिर व्योम *ptr, माप_प्रकार size)
अणु
	pr_debug("%s(0x%p)\n", __func__, ptr);

	अगर (kmemleak_enabled && ptr && !IS_ERR(ptr))
		delete_object_part((अचिन्हित दीर्घ)ptr, size);
पूर्ण
EXPORT_SYMBOL_GPL(kmemleak_मुक्त_part);

/**
 * kmemleak_मुक्त_percpu - unरेजिस्टर a previously रेजिस्टरed __percpu object
 * @ptr:	__percpu poपूर्णांकer to beginning of the object
 *
 * This function is called from the kernel percpu allocator when an object
 * (memory block) is मुक्तd (मुक्त_percpu).
 */
व्योम __ref kmemleak_मुक्त_percpu(स्थिर व्योम __percpu *ptr)
अणु
	अचिन्हित पूर्णांक cpu;

	pr_debug("%s(0x%p)\n", __func__, ptr);

	अगर (kmemleak_मुक्त_enabled && ptr && !IS_ERR(ptr))
		क्रम_each_possible_cpu(cpu)
			delete_object_full((अचिन्हित दीर्घ)per_cpu_ptr(ptr,
								      cpu));
पूर्ण
EXPORT_SYMBOL_GPL(kmemleak_मुक्त_percpu);

/**
 * kmemleak_update_trace - update object allocation stack trace
 * @ptr:	poपूर्णांकer to beginning of the object
 *
 * Override the object allocation stack trace क्रम हालs where the actual
 * allocation place is not always useful.
 */
व्योम __ref kmemleak_update_trace(स्थिर व्योम *ptr)
अणु
	काष्ठा kmemleak_object *object;
	अचिन्हित दीर्घ flags;

	pr_debug("%s(0x%p)\n", __func__, ptr);

	अगर (!kmemleak_enabled || IS_ERR_OR_शून्य(ptr))
		वापस;

	object = find_and_get_object((अचिन्हित दीर्घ)ptr, 1);
	अगर (!object) अणु
#अगर_घोषित DEBUG
		kmemleak_warn("Updating stack trace for unknown object at %p\n",
			      ptr);
#पूर्ण_अगर
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&object->lock, flags);
	object->trace_len = __save_stack_trace(object->trace);
	raw_spin_unlock_irqrestore(&object->lock, flags);

	put_object(object);
पूर्ण
EXPORT_SYMBOL(kmemleak_update_trace);

/**
 * kmemleak_not_leak - mark an allocated object as false positive
 * @ptr:	poपूर्णांकer to beginning of the object
 *
 * Calling this function on an object will cause the memory block to no दीर्घer
 * be reported as leak and always be scanned.
 */
व्योम __ref kmemleak_not_leak(स्थिर व्योम *ptr)
अणु
	pr_debug("%s(0x%p)\n", __func__, ptr);

	अगर (kmemleak_enabled && ptr && !IS_ERR(ptr))
		make_gray_object((अचिन्हित दीर्घ)ptr);
पूर्ण
EXPORT_SYMBOL(kmemleak_not_leak);

/**
 * kmemleak_ignore - ignore an allocated object
 * @ptr:	poपूर्णांकer to beginning of the object
 *
 * Calling this function on an object will cause the memory block to be
 * ignored (not scanned and not reported as a leak). This is usually करोne when
 * it is known that the corresponding block is not a leak and करोes not contain
 * any references to other allocated memory blocks.
 */
व्योम __ref kmemleak_ignore(स्थिर व्योम *ptr)
अणु
	pr_debug("%s(0x%p)\n", __func__, ptr);

	अगर (kmemleak_enabled && ptr && !IS_ERR(ptr))
		make_black_object((अचिन्हित दीर्घ)ptr);
पूर्ण
EXPORT_SYMBOL(kmemleak_ignore);

/**
 * kmemleak_scan_area - limit the range to be scanned in an allocated object
 * @ptr:	poपूर्णांकer to beginning or inside the object. This also
 *		represents the start of the scan area
 * @size:	size of the scan area
 * @gfp:	kदो_स्मृति() flags used क्रम kmemleak पूर्णांकernal memory allocations
 *
 * This function is used when it is known that only certain parts of an object
 * contain references to other objects. Kmemleak will only scan these areas
 * reducing the number false negatives.
 */
व्योम __ref kmemleak_scan_area(स्थिर व्योम *ptr, माप_प्रकार size, gfp_t gfp)
अणु
	pr_debug("%s(0x%p)\n", __func__, ptr);

	अगर (kmemleak_enabled && ptr && size && !IS_ERR(ptr))
		add_scan_area((अचिन्हित दीर्घ)ptr, size, gfp);
पूर्ण
EXPORT_SYMBOL(kmemleak_scan_area);

/**
 * kmemleak_no_scan - करो not scan an allocated object
 * @ptr:	poपूर्णांकer to beginning of the object
 *
 * This function notअगरies kmemleak not to scan the given memory block. Useful
 * in situations where it is known that the given object करोes not contain any
 * references to other objects. Kmemleak will not scan such objects reducing
 * the number of false negatives.
 */
व्योम __ref kmemleak_no_scan(स्थिर व्योम *ptr)
अणु
	pr_debug("%s(0x%p)\n", __func__, ptr);

	अगर (kmemleak_enabled && ptr && !IS_ERR(ptr))
		object_no_scan((अचिन्हित दीर्घ)ptr);
पूर्ण
EXPORT_SYMBOL(kmemleak_no_scan);

/**
 * kmemleak_alloc_phys - similar to kmemleak_alloc but taking a physical
 *			 address argument
 * @phys:	physical address of the object
 * @size:	size of the object
 * @min_count:	minimum number of references to this object.
 *              See kmemleak_alloc()
 * @gfp:	kदो_स्मृति() flags used क्रम kmemleak पूर्णांकernal memory allocations
 */
व्योम __ref kmemleak_alloc_phys(phys_addr_t phys, माप_प्रकार size, पूर्णांक min_count,
			       gfp_t gfp)
अणु
	अगर (!IS_ENABLED(CONFIG_HIGHMEM) || PHYS_PFN(phys) < max_low_pfn)
		kmemleak_alloc(__va(phys), size, min_count, gfp);
पूर्ण
EXPORT_SYMBOL(kmemleak_alloc_phys);

/**
 * kmemleak_मुक्त_part_phys - similar to kmemleak_मुक्त_part but taking a
 *			     physical address argument
 * @phys:	physical address अगर the beginning or inside an object. This
 *		also represents the start of the range to be मुक्तd
 * @size:	size to be unरेजिस्टरed
 */
व्योम __ref kmemleak_मुक्त_part_phys(phys_addr_t phys, माप_प्रकार size)
अणु
	अगर (!IS_ENABLED(CONFIG_HIGHMEM) || PHYS_PFN(phys) < max_low_pfn)
		kmemleak_मुक्त_part(__va(phys), size);
पूर्ण
EXPORT_SYMBOL(kmemleak_मुक्त_part_phys);

/**
 * kmemleak_not_leak_phys - similar to kmemleak_not_leak but taking a physical
 *			    address argument
 * @phys:	physical address of the object
 */
व्योम __ref kmemleak_not_leak_phys(phys_addr_t phys)
अणु
	अगर (!IS_ENABLED(CONFIG_HIGHMEM) || PHYS_PFN(phys) < max_low_pfn)
		kmemleak_not_leak(__va(phys));
पूर्ण
EXPORT_SYMBOL(kmemleak_not_leak_phys);

/**
 * kmemleak_ignore_phys - similar to kmemleak_ignore but taking a physical
 *			  address argument
 * @phys:	physical address of the object
 */
व्योम __ref kmemleak_ignore_phys(phys_addr_t phys)
अणु
	अगर (!IS_ENABLED(CONFIG_HIGHMEM) || PHYS_PFN(phys) < max_low_pfn)
		kmemleak_ignore(__va(phys));
पूर्ण
EXPORT_SYMBOL(kmemleak_ignore_phys);

/*
 * Update an object's checksum and वापस true अगर it was modअगरied.
 */
अटल bool update_checksum(काष्ठा kmemleak_object *object)
अणु
	u32 old_csum = object->checksum;

	kasan_disable_current();
	kcsan_disable_current();
	object->checksum = crc32(0, (व्योम *)object->poपूर्णांकer, object->size);
	kasan_enable_current();
	kcsan_enable_current();

	वापस object->checksum != old_csum;
पूर्ण

/*
 * Update an object's references. object->lock must be held by the caller.
 */
अटल व्योम update_refs(काष्ठा kmemleak_object *object)
अणु
	अगर (!color_white(object)) अणु
		/* non-orphan, ignored or new */
		वापस;
	पूर्ण

	/*
	 * Increase the object's reference count (number of poपूर्णांकers to the
	 * memory block). If this count reaches the required minimum, the
	 * object's color will become gray and it will be added to the
	 * gray_list.
	 */
	object->count++;
	अगर (color_gray(object)) अणु
		/* put_object() called when removing from gray_list */
		WARN_ON(!get_object(object));
		list_add_tail(&object->gray_list, &gray_list);
	पूर्ण
पूर्ण

/*
 * Memory scanning is a दीर्घ process and it needs to be पूर्णांकerruptible. This
 * function checks whether such पूर्णांकerrupt condition occurred.
 */
अटल पूर्णांक scan_should_stop(व्योम)
अणु
	अगर (!kmemleak_enabled)
		वापस 1;

	/*
	 * This function may be called from either process or kthपढ़ो context,
	 * hence the need to check क्रम both stop conditions.
	 */
	अगर (current->mm)
		वापस संकेत_pending(current);
	अन्यथा
		वापस kthपढ़ो_should_stop();

	वापस 0;
पूर्ण

/*
 * Scan a memory block (exclusive range) क्रम valid poपूर्णांकers and add those
 * found to the gray list.
 */
अटल व्योम scan_block(व्योम *_start, व्योम *_end,
		       काष्ठा kmemleak_object *scanned)
अणु
	अचिन्हित दीर्घ *ptr;
	अचिन्हित दीर्घ *start = PTR_ALIGN(_start, BYTES_PER_POINTER);
	अचिन्हित दीर्घ *end = _end - (BYTES_PER_POINTER - 1);
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ untagged_ptr;

	raw_spin_lock_irqsave(&kmemleak_lock, flags);
	क्रम (ptr = start; ptr < end; ptr++) अणु
		काष्ठा kmemleak_object *object;
		अचिन्हित दीर्घ poपूर्णांकer;
		अचिन्हित दीर्घ excess_ref;

		अगर (scan_should_stop())
			अवरोध;

		kasan_disable_current();
		poपूर्णांकer = *ptr;
		kasan_enable_current();

		untagged_ptr = (अचिन्हित दीर्घ)kasan_reset_tag((व्योम *)poपूर्णांकer);
		अगर (untagged_ptr < min_addr || untagged_ptr >= max_addr)
			जारी;

		/*
		 * No need क्रम get_object() here since we hold kmemleak_lock.
		 * object->use_count cannot be dropped to 0 जबतक the object
		 * is still present in object_tree_root and object_list
		 * (with updates रक्षित by kmemleak_lock).
		 */
		object = lookup_object(poपूर्णांकer, 1);
		अगर (!object)
			जारी;
		अगर (object == scanned)
			/* self referenced, ignore */
			जारी;

		/*
		 * Aव्योम the lockdep recursive warning on object->lock being
		 * previously acquired in scan_object(). These locks are
		 * enबंदd by scan_mutex.
		 */
		raw_spin_lock_nested(&object->lock, SINGLE_DEPTH_NESTING);
		/* only pass surplus references (object alपढ़ोy gray) */
		अगर (color_gray(object)) अणु
			excess_ref = object->excess_ref;
			/* no need क्रम update_refs() अगर object alपढ़ोy gray */
		पूर्ण अन्यथा अणु
			excess_ref = 0;
			update_refs(object);
		पूर्ण
		raw_spin_unlock(&object->lock);

		अगर (excess_ref) अणु
			object = lookup_object(excess_ref, 0);
			अगर (!object)
				जारी;
			अगर (object == scanned)
				/* circular reference, ignore */
				जारी;
			raw_spin_lock_nested(&object->lock, SINGLE_DEPTH_NESTING);
			update_refs(object);
			raw_spin_unlock(&object->lock);
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&kmemleak_lock, flags);
पूर्ण

/*
 * Scan a large memory block in MAX_SCAN_SIZE chunks to reduce the latency.
 */
#अगर_घोषित CONFIG_SMP
अटल व्योम scan_large_block(व्योम *start, व्योम *end)
अणु
	व्योम *next;

	जबतक (start < end) अणु
		next = min(start + MAX_SCAN_SIZE, end);
		scan_block(start, next, शून्य);
		start = next;
		cond_resched();
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * Scan a memory block corresponding to a kmemleak_object. A condition is
 * that object->use_count >= 1.
 */
अटल व्योम scan_object(काष्ठा kmemleak_object *object)
अणु
	काष्ठा kmemleak_scan_area *area;
	अचिन्हित दीर्घ flags;

	/*
	 * Once the object->lock is acquired, the corresponding memory block
	 * cannot be मुक्तd (the same lock is acquired in delete_object).
	 */
	raw_spin_lock_irqsave(&object->lock, flags);
	अगर (object->flags & OBJECT_NO_SCAN)
		जाओ out;
	अगर (!(object->flags & OBJECT_ALLOCATED))
		/* alपढ़ोy मुक्तd object */
		जाओ out;
	अगर (hlist_empty(&object->area_list) ||
	    object->flags & OBJECT_FULL_SCAN) अणु
		व्योम *start = (व्योम *)object->poपूर्णांकer;
		व्योम *end = (व्योम *)(object->poपूर्णांकer + object->size);
		व्योम *next;

		करो अणु
			next = min(start + MAX_SCAN_SIZE, end);
			scan_block(start, next, object);

			start = next;
			अगर (start >= end)
				अवरोध;

			raw_spin_unlock_irqrestore(&object->lock, flags);
			cond_resched();
			raw_spin_lock_irqsave(&object->lock, flags);
		पूर्ण जबतक (object->flags & OBJECT_ALLOCATED);
	पूर्ण अन्यथा
		hlist_क्रम_each_entry(area, &object->area_list, node)
			scan_block((व्योम *)area->start,
				   (व्योम *)(area->start + area->size),
				   object);
out:
	raw_spin_unlock_irqrestore(&object->lock, flags);
पूर्ण

/*
 * Scan the objects alपढ़ोy referenced (gray objects). More objects will be
 * referenced and, अगर there are no memory leaks, all the objects are scanned.
 */
अटल व्योम scan_gray_list(व्योम)
अणु
	काष्ठा kmemleak_object *object, *पंचांगp;

	/*
	 * The list traversal is safe क्रम both tail additions and removals
	 * from inside the loop. The kmemleak objects cannot be मुक्तd from
	 * outside the loop because their use_count was incremented.
	 */
	object = list_entry(gray_list.next, typeof(*object), gray_list);
	जबतक (&object->gray_list != &gray_list) अणु
		cond_resched();

		/* may add new objects to the list */
		अगर (!scan_should_stop())
			scan_object(object);

		पंचांगp = list_entry(object->gray_list.next, typeof(*object),
				 gray_list);

		/* हटाओ the object from the list and release it */
		list_del(&object->gray_list);
		put_object(object);

		object = पंचांगp;
	पूर्ण
	WARN_ON(!list_empty(&gray_list));
पूर्ण

/*
 * Scan data sections and all the referenced memory blocks allocated via the
 * kernel's standard allocators. This function must be called with the
 * scan_mutex held.
 */
अटल व्योम kmemleak_scan(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kmemleak_object *object;
	पूर्णांक i;
	पूर्णांक new_leaks = 0;

	jअगरfies_last_scan = jअगरfies;

	/* prepare the kmemleak_object's */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(object, &object_list, object_list) अणु
		raw_spin_lock_irqsave(&object->lock, flags);
#अगर_घोषित DEBUG
		/*
		 * With a few exceptions there should be a maximum of
		 * 1 reference to any object at this poपूर्णांक.
		 */
		अगर (atomic_पढ़ो(&object->use_count) > 1) अणु
			pr_debug("object->use_count = %d\n",
				 atomic_पढ़ो(&object->use_count));
			dump_object_info(object);
		पूर्ण
#पूर्ण_अगर
		/* reset the reference count (whiten the object) */
		object->count = 0;
		अगर (color_gray(object) && get_object(object))
			list_add_tail(&object->gray_list, &gray_list);

		raw_spin_unlock_irqrestore(&object->lock, flags);
	पूर्ण
	rcu_पढ़ो_unlock();

#अगर_घोषित CONFIG_SMP
	/* per-cpu sections scanning */
	क्रम_each_possible_cpu(i)
		scan_large_block(__per_cpu_start + per_cpu_offset(i),
				 __per_cpu_end + per_cpu_offset(i));
#पूर्ण_अगर

	/*
	 * Struct page scanning क्रम each node.
	 */
	get_online_mems();
	क्रम_each_online_node(i) अणु
		अचिन्हित दीर्घ start_pfn = node_start_pfn(i);
		अचिन्हित दीर्घ end_pfn = node_end_pfn(i);
		अचिन्हित दीर्घ pfn;

		क्रम (pfn = start_pfn; pfn < end_pfn; pfn++) अणु
			काष्ठा page *page = pfn_to_online_page(pfn);

			अगर (!page)
				जारी;

			/* only scan pages beदीर्घing to this node */
			अगर (page_to_nid(page) != i)
				जारी;
			/* only scan अगर page is in use */
			अगर (page_count(page) == 0)
				जारी;
			scan_block(page, page + 1, शून्य);
			अगर (!(pfn & 63))
				cond_resched();
		पूर्ण
	पूर्ण
	put_online_mems();

	/*
	 * Scanning the task stacks (may पूर्णांकroduce false negatives).
	 */
	अगर (kmemleak_stack_scan) अणु
		काष्ठा task_काष्ठा *p, *g;

		rcu_पढ़ो_lock();
		क्रम_each_process_thपढ़ो(g, p) अणु
			व्योम *stack = try_get_task_stack(p);
			अगर (stack) अणु
				scan_block(stack, stack + THREAD_SIZE, शून्य);
				put_task_stack(p);
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	/*
	 * Scan the objects alपढ़ोy referenced from the sections scanned
	 * above.
	 */
	scan_gray_list();

	/*
	 * Check क्रम new or unreferenced objects modअगरied since the previous
	 * scan and color them gray until the next scan.
	 */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(object, &object_list, object_list) अणु
		raw_spin_lock_irqsave(&object->lock, flags);
		अगर (color_white(object) && (object->flags & OBJECT_ALLOCATED)
		    && update_checksum(object) && get_object(object)) अणु
			/* color it gray temporarily */
			object->count = object->min_count;
			list_add_tail(&object->gray_list, &gray_list);
		पूर्ण
		raw_spin_unlock_irqrestore(&object->lock, flags);
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * Re-scan the gray list क्रम modअगरied unreferenced objects.
	 */
	scan_gray_list();

	/*
	 * If scanning was stopped करो not report any new unreferenced objects.
	 */
	अगर (scan_should_stop())
		वापस;

	/*
	 * Scanning result reporting.
	 */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(object, &object_list, object_list) अणु
		raw_spin_lock_irqsave(&object->lock, flags);
		अगर (unreferenced_object(object) &&
		    !(object->flags & OBJECT_REPORTED)) अणु
			object->flags |= OBJECT_REPORTED;

			अगर (kmemleak_verbose)
				prपूर्णांक_unreferenced(शून्य, object);

			new_leaks++;
		पूर्ण
		raw_spin_unlock_irqrestore(&object->lock, flags);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (new_leaks) अणु
		kmemleak_found_leaks = true;

		pr_info("%d new suspected memory leaks (see /sys/kernel/debug/kmemleak)\n",
			new_leaks);
	पूर्ण

पूर्ण

/*
 * Thपढ़ो function perक्रमming स्वतःmatic memory scanning. Unreferenced objects
 * at the end of a memory scan are reported but only the first समय.
 */
अटल पूर्णांक kmemleak_scan_thपढ़ो(व्योम *arg)
अणु
	अटल पूर्णांक first_run = IS_ENABLED(CONFIG_DEBUG_KMEMLEAK_AUTO_SCAN);

	pr_info("Automatic memory scanning thread started\n");
	set_user_nice(current, 10);

	/*
	 * Wait beक्रमe the first scan to allow the प्रणाली to fully initialize.
	 */
	अगर (first_run) अणु
		चिन्हित दीर्घ समयout = msecs_to_jअगरfies(SECS_FIRST_SCAN * 1000);
		first_run = 0;
		जबतक (समयout && !kthपढ़ो_should_stop())
			समयout = schedule_समयout_पूर्णांकerruptible(समयout);
	पूर्ण

	जबतक (!kthपढ़ो_should_stop()) अणु
		चिन्हित दीर्घ समयout = jअगरfies_scan_रुको;

		mutex_lock(&scan_mutex);
		kmemleak_scan();
		mutex_unlock(&scan_mutex);

		/* रुको beक्रमe the next scan */
		जबतक (समयout && !kthपढ़ो_should_stop())
			समयout = schedule_समयout_पूर्णांकerruptible(समयout);
	पूर्ण

	pr_info("Automatic memory scanning thread ended\n");

	वापस 0;
पूर्ण

/*
 * Start the स्वतःmatic memory scanning thपढ़ो. This function must be called
 * with the scan_mutex held.
 */
अटल व्योम start_scan_thपढ़ो(व्योम)
अणु
	अगर (scan_thपढ़ो)
		वापस;
	scan_thपढ़ो = kthपढ़ो_run(kmemleak_scan_thपढ़ो, शून्य, "kmemleak");
	अगर (IS_ERR(scan_thपढ़ो)) अणु
		pr_warn("Failed to create the scan thread\n");
		scan_thपढ़ो = शून्य;
	पूर्ण
पूर्ण

/*
 * Stop the स्वतःmatic memory scanning thपढ़ो.
 */
अटल व्योम stop_scan_thपढ़ो(व्योम)
अणु
	अगर (scan_thपढ़ो) अणु
		kthपढ़ो_stop(scan_thपढ़ो);
		scan_thपढ़ो = शून्य;
	पूर्ण
पूर्ण

/*
 * Iterate over the object_list and वापस the first valid object at or after
 * the required position with its use_count incremented. The function triggers
 * a memory scanning when the pos argument poपूर्णांकs to the first position.
 */
अटल व्योम *kmemleak_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा kmemleak_object *object;
	loff_t n = *pos;
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&scan_mutex);
	अगर (err < 0)
		वापस ERR_PTR(err);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(object, &object_list, object_list) अणु
		अगर (n-- > 0)
			जारी;
		अगर (get_object(object))
			जाओ out;
	पूर्ण
	object = शून्य;
out:
	वापस object;
पूर्ण

/*
 * Return the next object in the object_list. The function decrements the
 * use_count of the previous object and increases that of the next one.
 */
अटल व्योम *kmemleak_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा kmemleak_object *prev_obj = v;
	काष्ठा kmemleak_object *next_obj = शून्य;
	काष्ठा kmemleak_object *obj = prev_obj;

	++(*pos);

	list_क्रम_each_entry_जारी_rcu(obj, &object_list, object_list) अणु
		अगर (get_object(obj)) अणु
			next_obj = obj;
			अवरोध;
		पूर्ण
	पूर्ण

	put_object(prev_obj);
	वापस next_obj;
पूर्ण

/*
 * Decrement the use_count of the last object required, अगर any.
 */
अटल व्योम kmemleak_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (!IS_ERR(v)) अणु
		/*
		 * kmemleak_seq_start may वापस ERR_PTR अगर the scan_mutex
		 * रुकोing was पूर्णांकerrupted, so only release it अगर !IS_ERR.
		 */
		rcu_पढ़ो_unlock();
		mutex_unlock(&scan_mutex);
		अगर (v)
			put_object(v);
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक the inक्रमmation क्रम an unreferenced object to the seq file.
 */
अटल पूर्णांक kmemleak_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा kmemleak_object *object = v;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&object->lock, flags);
	अगर ((object->flags & OBJECT_REPORTED) && unreferenced_object(object))
		prपूर्णांक_unreferenced(seq, object);
	raw_spin_unlock_irqrestore(&object->lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations kmemleak_seq_ops = अणु
	.start = kmemleak_seq_start,
	.next  = kmemleak_seq_next,
	.stop  = kmemleak_seq_stop,
	.show  = kmemleak_seq_show,
पूर्ण;

अटल पूर्णांक kmemleak_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &kmemleak_seq_ops);
पूर्ण

अटल पूर्णांक dump_str_object_info(स्थिर अक्षर *str)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kmemleak_object *object;
	अचिन्हित दीर्घ addr;

	अगर (kम_से_अदीर्घ(str, 0, &addr))
		वापस -EINVAL;
	object = find_and_get_object(addr, 0);
	अगर (!object) अणु
		pr_info("Unknown object at 0x%08lx\n", addr);
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock_irqsave(&object->lock, flags);
	dump_object_info(object);
	raw_spin_unlock_irqrestore(&object->lock, flags);

	put_object(object);
	वापस 0;
पूर्ण

/*
 * We use grey instead of black to ensure we can करो future scans on the same
 * objects. If we did not करो future scans these black objects could
 * potentially contain references to newly allocated objects in the future and
 * we'd end up with false positives.
 */
अटल व्योम kmemleak_clear(व्योम)
अणु
	काष्ठा kmemleak_object *object;
	अचिन्हित दीर्घ flags;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(object, &object_list, object_list) अणु
		raw_spin_lock_irqsave(&object->lock, flags);
		अगर ((object->flags & OBJECT_REPORTED) &&
		    unreferenced_object(object))
			__paपूर्णांक_it(object, KMEMLEAK_GREY);
		raw_spin_unlock_irqrestore(&object->lock, flags);
	पूर्ण
	rcu_पढ़ो_unlock();

	kmemleak_found_leaks = false;
पूर्ण

अटल व्योम __kmemleak_करो_cleanup(व्योम);

/*
 * File ग_लिखो operation to configure kmemleak at run-समय. The following
 * commands can be written to the /sys/kernel/debug/kmemleak file:
 *   off	- disable kmemleak (irreversible)
 *   stack=on	- enable the task stacks scanning
 *   stack=off	- disable the tasks stacks scanning
 *   scan=on	- start the स्वतःmatic memory scanning thपढ़ो
 *   scan=off	- stop the स्वतःmatic memory scanning thपढ़ो
 *   scan=...	- set the स्वतःmatic memory scanning period in seconds (0 to
 *		  disable it)
 *   scan	- trigger a memory scan
 *   clear	- mark all current reported unreferenced kmemleak objects as
 *		  grey to ignore prपूर्णांकing them, or मुक्त all kmemleak objects
 *		  अगर kmemleak has been disabled.
 *   dump=...	- dump inक्रमmation about the object found at the given address
 */
अटल sमाप_प्रकार kmemleak_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			      माप_प्रकार size, loff_t *ppos)
अणु
	अक्षर buf[64];
	पूर्णांक buf_size;
	पूर्णांक ret;

	buf_size = min(size, (माप(buf) - 1));
	अगर (म_नकलन_from_user(buf, user_buf, buf_size) < 0)
		वापस -EFAULT;
	buf[buf_size] = 0;

	ret = mutex_lock_पूर्णांकerruptible(&scan_mutex);
	अगर (ret < 0)
		वापस ret;

	अगर (म_भेदन(buf, "clear", 5) == 0) अणु
		अगर (kmemleak_enabled)
			kmemleak_clear();
		अन्यथा
			__kmemleak_करो_cleanup();
		जाओ out;
	पूर्ण

	अगर (!kmemleak_enabled) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	अगर (म_भेदन(buf, "off", 3) == 0)
		kmemleak_disable();
	अन्यथा अगर (म_भेदन(buf, "stack=on", 8) == 0)
		kmemleak_stack_scan = 1;
	अन्यथा अगर (म_भेदन(buf, "stack=off", 9) == 0)
		kmemleak_stack_scan = 0;
	अन्यथा अगर (म_भेदन(buf, "scan=on", 7) == 0)
		start_scan_thपढ़ो();
	अन्यथा अगर (म_भेदन(buf, "scan=off", 8) == 0)
		stop_scan_thपढ़ो();
	अन्यथा अगर (म_भेदन(buf, "scan=", 5) == 0) अणु
		अचिन्हित दीर्घ secs;

		ret = kम_से_अदीर्घ(buf + 5, 0, &secs);
		अगर (ret < 0)
			जाओ out;
		stop_scan_thपढ़ो();
		अगर (secs) अणु
			jअगरfies_scan_रुको = msecs_to_jअगरfies(secs * 1000);
			start_scan_thपढ़ो();
		पूर्ण
	पूर्ण अन्यथा अगर (म_भेदन(buf, "scan", 4) == 0)
		kmemleak_scan();
	अन्यथा अगर (म_भेदन(buf, "dump=", 5) == 0)
		ret = dump_str_object_info(buf + 5);
	अन्यथा
		ret = -EINVAL;

out:
	mutex_unlock(&scan_mutex);
	अगर (ret < 0)
		वापस ret;

	/* ignore the rest of the buffer, only one command at a समय */
	*ppos += size;
	वापस size;
पूर्ण

अटल स्थिर काष्ठा file_operations kmemleak_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= kmemleak_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= kmemleak_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;

अटल व्योम __kmemleak_करो_cleanup(व्योम)
अणु
	काष्ठा kmemleak_object *object, *पंचांगp;

	/*
	 * Kmemleak has alपढ़ोy been disabled, no need क्रम RCU list traversal
	 * or kmemleak_lock held.
	 */
	list_क्रम_each_entry_safe(object, पंचांगp, &object_list, object_list) अणु
		__हटाओ_object(object);
		__delete_object(object);
	पूर्ण
पूर्ण

/*
 * Stop the memory scanning thपढ़ो and मुक्त the kmemleak पूर्णांकernal objects अगर
 * no previous scan thपढ़ो (otherwise, kmemleak may still have some useful
 * inक्रमmation on memory leaks).
 */
अटल व्योम kmemleak_करो_cleanup(काष्ठा work_काष्ठा *work)
अणु
	stop_scan_thपढ़ो();

	mutex_lock(&scan_mutex);
	/*
	 * Once it is made sure that kmemleak_scan has stopped, it is safe to no
	 * दीर्घer track object मुक्तing. Ordering of the scan thपढ़ो stopping and
	 * the memory accesses below is guaranteed by the kthपढ़ो_stop()
	 * function.
	 */
	kmemleak_मुक्त_enabled = 0;
	mutex_unlock(&scan_mutex);

	अगर (!kmemleak_found_leaks)
		__kmemleak_करो_cleanup();
	अन्यथा
		pr_info("Kmemleak disabled without freeing internal data. Reclaim the memory with \"echo clear > /sys/kernel/debug/kmemleak\".\n");
पूर्ण

अटल DECLARE_WORK(cleanup_work, kmemleak_करो_cleanup);

/*
 * Disable kmemleak. No memory allocation/मुक्तing will be traced once this
 * function is called. Disabling kmemleak is an irreversible operation.
 */
अटल व्योम kmemleak_disable(व्योम)
अणु
	/* atomically check whether it was alपढ़ोy invoked */
	अगर (cmpxchg(&kmemleak_error, 0, 1))
		वापस;

	/* stop any memory operation tracing */
	kmemleak_enabled = 0;

	/* check whether it is too early क्रम a kernel thपढ़ो */
	अगर (kmemleak_initialized)
		schedule_work(&cleanup_work);
	अन्यथा
		kmemleak_मुक्त_enabled = 0;

	pr_info("Kernel memory leak detector disabled\n");
पूर्ण

/*
 * Allow boot-समय kmemleak disabling (enabled by शेष).
 */
अटल पूर्णांक __init kmemleak_boot_config(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;
	अगर (म_भेद(str, "off") == 0)
		kmemleak_disable();
	अन्यथा अगर (म_भेद(str, "on") == 0)
		kmemleak_skip_disable = 1;
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण
early_param("kmemleak", kmemleak_boot_config);

/*
 * Kmemleak initialization.
 */
व्योम __init kmemleak_init(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_KMEMLEAK_DEFAULT_OFF
	अगर (!kmemleak_skip_disable) अणु
		kmemleak_disable();
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (kmemleak_error)
		वापस;

	jअगरfies_min_age = msecs_to_jअगरfies(MSECS_MIN_AGE);
	jअगरfies_scan_रुको = msecs_to_jअगरfies(SECS_SCAN_WAIT * 1000);

	object_cache = KMEM_CACHE(kmemleak_object, SLAB_NOLEAKTRACE);
	scan_area_cache = KMEM_CACHE(kmemleak_scan_area, SLAB_NOLEAKTRACE);

	/* रेजिस्टर the data/bss sections */
	create_object((अचिन्हित दीर्घ)_sdata, _edata - _sdata,
		      KMEMLEAK_GREY, GFP_ATOMIC);
	create_object((अचिन्हित दीर्घ)__bss_start, __bss_stop - __bss_start,
		      KMEMLEAK_GREY, GFP_ATOMIC);
	/* only रेजिस्टर .data..ro_after_init अगर not within .data */
	अगर (&__start_ro_after_init < &_sdata || &__end_ro_after_init > &_edata)
		create_object((अचिन्हित दीर्घ)__start_ro_after_init,
			      __end_ro_after_init - __start_ro_after_init,
			      KMEMLEAK_GREY, GFP_ATOMIC);
पूर्ण

/*
 * Late initialization function.
 */
अटल पूर्णांक __init kmemleak_late_init(व्योम)
अणु
	kmemleak_initialized = 1;

	debugfs_create_file("kmemleak", 0644, शून्य, शून्य, &kmemleak_fops);

	अगर (kmemleak_error) अणु
		/*
		 * Some error occurred and kmemleak was disabled. There is a
		 * small chance that kmemleak_disable() was called immediately
		 * after setting kmemleak_initialized and we may end up with
		 * two clean-up thपढ़ोs but serialized by scan_mutex.
		 */
		schedule_work(&cleanup_work);
		वापस -ENOMEM;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_DEBUG_KMEMLEAK_AUTO_SCAN)) अणु
		mutex_lock(&scan_mutex);
		start_scan_thपढ़ो();
		mutex_unlock(&scan_mutex);
	पूर्ण

	pr_info("Kernel memory leak detector initialized (mem pool available: %d)\n",
		mem_pool_मुक्त_count);

	वापस 0;
पूर्ण
late_initcall(kmemleak_late_init);
