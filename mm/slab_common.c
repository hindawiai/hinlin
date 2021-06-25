<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Slab allocator functions that are independent of the allocator strategy
 *
 * (C) 2012 Christoph Lameter <cl@linux.com>
 */
#समावेश <linux/slab.h>

#समावेश <linux/mm.h>
#समावेश <linux/poison.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/memory.h>
#समावेश <linux/cache.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kfence.h>
#समावेश <linux/module.h>
#समावेश <linux/cpu.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kasan.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/memcontrol.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/kस्मृति.स>

#समावेश "internal.h"

#समावेश "slab.h"

क्रमागत slab_state slab_state;
LIST_HEAD(slab_caches);
DEFINE_MUTEX(slab_mutex);
काष्ठा kmem_cache *kmem_cache;

#अगर_घोषित CONFIG_HARDENED_USERCOPY
bool usercopy_fallback __ro_after_init =
		IS_ENABLED(CONFIG_HARDENED_USERCOPY_FALLBACK);
module_param(usercopy_fallback, bool, 0400);
MODULE_PARM_DESC(usercopy_fallback,
		"WARN instead of reject usercopy whitelist violations");
#पूर्ण_अगर

अटल LIST_HEAD(slab_caches_to_rcu_destroy);
अटल व्योम slab_caches_to_rcu_destroy_workfn(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(slab_caches_to_rcu_destroy_work,
		    slab_caches_to_rcu_destroy_workfn);

/*
 * Set of flags that will prevent slab merging
 */
#घोषणा SLAB_NEVER_MERGE (SLAB_RED_ZONE | SLAB_POISON | SLAB_STORE_USER | \
		SLAB_TRACE | SLAB_TYPESAFE_BY_RCU | SLAB_NOLEAKTRACE | \
		SLAB_FAILSLAB | kasan_never_merge())

#घोषणा SLAB_MERGE_SAME (SLAB_RECLAIM_ACCOUNT | SLAB_CACHE_DMA | \
			 SLAB_CACHE_DMA32 | SLAB_ACCOUNT)

/*
 * Merge control. If this is set then no merging of slab caches will occur.
 */
अटल bool slab_nomerge = !IS_ENABLED(CONFIG_SLAB_MERGE_DEFAULT);

अटल पूर्णांक __init setup_slab_nomerge(अक्षर *str)
अणु
	slab_nomerge = true;
	वापस 1;
पूर्ण

अटल पूर्णांक __init setup_slab_merge(अक्षर *str)
अणु
	slab_nomerge = false;
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_SLUB
__setup_param("slub_nomerge", slub_nomerge, setup_slab_nomerge, 0);
__setup_param("slub_merge", slub_merge, setup_slab_merge, 0);
#पूर्ण_अगर

__setup("slab_nomerge", setup_slab_nomerge);
__setup("slab_merge", setup_slab_merge);

/*
 * Determine the size of a slab object
 */
अचिन्हित पूर्णांक kmem_cache_size(काष्ठा kmem_cache *s)
अणु
	वापस s->object_size;
पूर्ण
EXPORT_SYMBOL(kmem_cache_size);

#अगर_घोषित CONFIG_DEBUG_VM
अटल पूर्णांक kmem_cache_sanity_check(स्थिर अक्षर *name, अचिन्हित पूर्णांक size)
अणु
	अगर (!name || in_पूर्णांकerrupt() || size > KMALLOC_MAX_SIZE) अणु
		pr_err("kmem_cache_create(%s) integrity check failed\n", name);
		वापस -EINVAL;
	पूर्ण

	WARN_ON(म_अक्षर(name, ' '));	/* It confuses parsers */
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक kmem_cache_sanity_check(स्थिर अक्षर *name, अचिन्हित पूर्णांक size)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम __kmem_cache_मुक्त_bulk(काष्ठा kmem_cache *s, माप_प्रकार nr, व्योम **p)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < nr; i++) अणु
		अगर (s)
			kmem_cache_मुक्त(s, p[i]);
		अन्यथा
			kमुक्त(p[i]);
	पूर्ण
पूर्ण

पूर्णांक __kmem_cache_alloc_bulk(काष्ठा kmem_cache *s, gfp_t flags, माप_प्रकार nr,
								व्योम **p)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < nr; i++) अणु
		व्योम *x = p[i] = kmem_cache_alloc(s, flags);
		अगर (!x) अणु
			__kmem_cache_मुक्त_bulk(s, i, p);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस i;
पूर्ण

/*
 * Figure out what the alignment of the objects will be given a set of
 * flags, a user specअगरied alignment and the size of the objects.
 */
अटल अचिन्हित पूर्णांक calculate_alignment(slab_flags_t flags,
		अचिन्हित पूर्णांक align, अचिन्हित पूर्णांक size)
अणु
	/*
	 * If the user wants hardware cache aligned objects then follow that
	 * suggestion अगर the object is sufficiently large.
	 *
	 * The hardware cache alignment cannot override the specअगरied
	 * alignment though. If that is greater then use it.
	 */
	अगर (flags & SLAB_HWCACHE_ALIGN) अणु
		अचिन्हित पूर्णांक ralign;

		ralign = cache_line_size();
		जबतक (size <= ralign / 2)
			ralign /= 2;
		align = max(align, ralign);
	पूर्ण

	अगर (align < ARCH_SLAB_MINALIGN)
		align = ARCH_SLAB_MINALIGN;

	वापस ALIGN(align, माप(व्योम *));
पूर्ण

/*
 * Find a mergeable slab cache
 */
पूर्णांक slab_unmergeable(काष्ठा kmem_cache *s)
अणु
	अगर (slab_nomerge || (s->flags & SLAB_NEVER_MERGE))
		वापस 1;

	अगर (s->ctor)
		वापस 1;

	अगर (s->usersize)
		वापस 1;

	/*
	 * We may have set a slab to be unmergeable during bootstrap.
	 */
	अगर (s->refcount < 0)
		वापस 1;

	वापस 0;
पूर्ण

काष्ठा kmem_cache *find_mergeable(अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक align,
		slab_flags_t flags, स्थिर अक्षर *name, व्योम (*ctor)(व्योम *))
अणु
	काष्ठा kmem_cache *s;

	अगर (slab_nomerge)
		वापस शून्य;

	अगर (ctor)
		वापस शून्य;

	size = ALIGN(size, माप(व्योम *));
	align = calculate_alignment(flags, align, size);
	size = ALIGN(size, align);
	flags = kmem_cache_flags(size, flags, name);

	अगर (flags & SLAB_NEVER_MERGE)
		वापस शून्य;

	list_क्रम_each_entry_reverse(s, &slab_caches, list) अणु
		अगर (slab_unmergeable(s))
			जारी;

		अगर (size > s->size)
			जारी;

		अगर ((flags & SLAB_MERGE_SAME) != (s->flags & SLAB_MERGE_SAME))
			जारी;
		/*
		 * Check अगर alignment is compatible.
		 * Courtesy of Adrian Drzewiecki
		 */
		अगर ((s->size & ~(align - 1)) != s->size)
			जारी;

		अगर (s->size - size >= माप(व्योम *))
			जारी;

		अगर (IS_ENABLED(CONFIG_SLAB) && align &&
			(align > s->align || s->align % align))
			जारी;

		वापस s;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा kmem_cache *create_cache(स्थिर अक्षर *name,
		अचिन्हित पूर्णांक object_size, अचिन्हित पूर्णांक align,
		slab_flags_t flags, अचिन्हित पूर्णांक useroffset,
		अचिन्हित पूर्णांक usersize, व्योम (*ctor)(व्योम *),
		काष्ठा kmem_cache *root_cache)
अणु
	काष्ठा kmem_cache *s;
	पूर्णांक err;

	अगर (WARN_ON(useroffset + usersize > object_size))
		useroffset = usersize = 0;

	err = -ENOMEM;
	s = kmem_cache_zalloc(kmem_cache, GFP_KERNEL);
	अगर (!s)
		जाओ out;

	s->name = name;
	s->size = s->object_size = object_size;
	s->align = align;
	s->ctor = ctor;
	s->useroffset = useroffset;
	s->usersize = usersize;

	err = __kmem_cache_create(s, flags);
	अगर (err)
		जाओ out_मुक्त_cache;

	s->refcount = 1;
	list_add(&s->list, &slab_caches);
out:
	अगर (err)
		वापस ERR_PTR(err);
	वापस s;

out_मुक्त_cache:
	kmem_cache_मुक्त(kmem_cache, s);
	जाओ out;
पूर्ण

/**
 * kmem_cache_create_usercopy - Create a cache with a region suitable
 * क्रम copying to userspace
 * @name: A string which is used in /proc/slabinfo to identअगरy this cache.
 * @size: The size of objects to be created in this cache.
 * @align: The required alignment क्रम the objects.
 * @flags: SLAB flags
 * @useroffset: Usercopy region offset
 * @usersize: Usercopy region size
 * @ctor: A स्थिरructor क्रम the objects.
 *
 * Cannot be called within a पूर्णांकerrupt, but can be पूर्णांकerrupted.
 * The @ctor is run when new pages are allocated by the cache.
 *
 * The flags are
 *
 * %SLAB_POISON - Poison the slab with a known test pattern (a5a5a5a5)
 * to catch references to uninitialised memory.
 *
 * %SLAB_RED_ZONE - Insert `Red` zones around the allocated memory to check
 * क्रम buffer overruns.
 *
 * %SLAB_HWCACHE_ALIGN - Align the objects in this cache to a hardware
 * cacheline.  This can be beneficial अगर you're counting cycles as बंदly
 * as davem.
 *
 * Return: a poपूर्णांकer to the cache on success, शून्य on failure.
 */
काष्ठा kmem_cache *
kmem_cache_create_usercopy(स्थिर अक्षर *name,
		  अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक align,
		  slab_flags_t flags,
		  अचिन्हित पूर्णांक useroffset, अचिन्हित पूर्णांक usersize,
		  व्योम (*ctor)(व्योम *))
अणु
	काष्ठा kmem_cache *s = शून्य;
	स्थिर अक्षर *cache_name;
	पूर्णांक err;

#अगर_घोषित CONFIG_SLUB_DEBUG
	/*
	 * If no slub_debug was enabled globally, the अटल key is not yet
	 * enabled by setup_slub_debug(). Enable it अगर the cache is being
	 * created with any of the debugging flags passed explicitly.
	 */
	अगर (flags & SLAB_DEBUG_FLAGS)
		अटल_branch_enable(&slub_debug_enabled);
#पूर्ण_अगर

	mutex_lock(&slab_mutex);

	err = kmem_cache_sanity_check(name, size);
	अगर (err) अणु
		जाओ out_unlock;
	पूर्ण

	/* Refuse requests with allocator specअगरic flags */
	अगर (flags & ~SLAB_FLAGS_PERMITTED) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/*
	 * Some allocators will स्थिरraपूर्णांक the set of valid flags to a subset
	 * of all flags. We expect them to define CACHE_CREATE_MASK in this
	 * हाल, and we'll just provide them with a sanitized version of the
	 * passed flags.
	 */
	flags &= CACHE_CREATE_MASK;

	/* Fail बंदd on bad usersize of useroffset values. */
	अगर (WARN_ON(!usersize && useroffset) ||
	    WARN_ON(size < usersize || size - usersize < useroffset))
		usersize = useroffset = 0;

	अगर (!usersize)
		s = __kmem_cache_alias(name, size, align, flags, ctor);
	अगर (s)
		जाओ out_unlock;

	cache_name = kstrdup_स्थिर(name, GFP_KERNEL);
	अगर (!cache_name) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	s = create_cache(cache_name, size,
			 calculate_alignment(flags, align, size),
			 flags, useroffset, usersize, ctor, शून्य);
	अगर (IS_ERR(s)) अणु
		err = PTR_ERR(s);
		kमुक्त_स्थिर(cache_name);
	पूर्ण

out_unlock:
	mutex_unlock(&slab_mutex);

	अगर (err) अणु
		अगर (flags & SLAB_PANIC)
			panic("kmem_cache_create: Failed to create slab '%s'. Error %d\n",
				name, err);
		अन्यथा अणु
			pr_warn("kmem_cache_create(%s) failed with error %d\n",
				name, err);
			dump_stack();
		पूर्ण
		वापस शून्य;
	पूर्ण
	वापस s;
पूर्ण
EXPORT_SYMBOL(kmem_cache_create_usercopy);

/**
 * kmem_cache_create - Create a cache.
 * @name: A string which is used in /proc/slabinfo to identअगरy this cache.
 * @size: The size of objects to be created in this cache.
 * @align: The required alignment क्रम the objects.
 * @flags: SLAB flags
 * @ctor: A स्थिरructor क्रम the objects.
 *
 * Cannot be called within a पूर्णांकerrupt, but can be पूर्णांकerrupted.
 * The @ctor is run when new pages are allocated by the cache.
 *
 * The flags are
 *
 * %SLAB_POISON - Poison the slab with a known test pattern (a5a5a5a5)
 * to catch references to uninitialised memory.
 *
 * %SLAB_RED_ZONE - Insert `Red` zones around the allocated memory to check
 * क्रम buffer overruns.
 *
 * %SLAB_HWCACHE_ALIGN - Align the objects in this cache to a hardware
 * cacheline.  This can be beneficial अगर you're counting cycles as बंदly
 * as davem.
 *
 * Return: a poपूर्णांकer to the cache on success, शून्य on failure.
 */
काष्ठा kmem_cache *
kmem_cache_create(स्थिर अक्षर *name, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक align,
		slab_flags_t flags, व्योम (*ctor)(व्योम *))
अणु
	वापस kmem_cache_create_usercopy(name, size, align, flags, 0, 0,
					  ctor);
पूर्ण
EXPORT_SYMBOL(kmem_cache_create);

अटल व्योम slab_caches_to_rcu_destroy_workfn(काष्ठा work_काष्ठा *work)
अणु
	LIST_HEAD(to_destroy);
	काष्ठा kmem_cache *s, *s2;

	/*
	 * On deकाष्ठाion, SLAB_TYPESAFE_BY_RCU kmem_caches are put on the
	 * @slab_caches_to_rcu_destroy list.  The slab pages are मुक्तd
	 * through RCU and the associated kmem_cache are dereferenced
	 * जबतक मुक्तing the pages, so the kmem_caches should be मुक्तd only
	 * after the pending RCU operations are finished.  As rcu_barrier()
	 * is a pretty slow operation, we batch all pending deकाष्ठाions
	 * asynchronously.
	 */
	mutex_lock(&slab_mutex);
	list_splice_init(&slab_caches_to_rcu_destroy, &to_destroy);
	mutex_unlock(&slab_mutex);

	अगर (list_empty(&to_destroy))
		वापस;

	rcu_barrier();

	list_क्रम_each_entry_safe(s, s2, &to_destroy, list) अणु
		kfence_shutकरोwn_cache(s);
#अगर_घोषित SLAB_SUPPORTS_SYSFS
		sysfs_slab_release(s);
#अन्यथा
		slab_kmem_cache_release(s);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक shutकरोwn_cache(काष्ठा kmem_cache *s)
अणु
	/* मुक्त asan quarantined objects */
	kasan_cache_shutकरोwn(s);

	अगर (__kmem_cache_shutकरोwn(s) != 0)
		वापस -EBUSY;

	list_del(&s->list);

	अगर (s->flags & SLAB_TYPESAFE_BY_RCU) अणु
#अगर_घोषित SLAB_SUPPORTS_SYSFS
		sysfs_slab_unlink(s);
#पूर्ण_अगर
		list_add_tail(&s->list, &slab_caches_to_rcu_destroy);
		schedule_work(&slab_caches_to_rcu_destroy_work);
	पूर्ण अन्यथा अणु
		kfence_shutकरोwn_cache(s);
#अगर_घोषित SLAB_SUPPORTS_SYSFS
		sysfs_slab_unlink(s);
		sysfs_slab_release(s);
#अन्यथा
		slab_kmem_cache_release(s);
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

व्योम slab_kmem_cache_release(काष्ठा kmem_cache *s)
अणु
	__kmem_cache_release(s);
	kमुक्त_स्थिर(s->name);
	kmem_cache_मुक्त(kmem_cache, s);
पूर्ण

व्योम kmem_cache_destroy(काष्ठा kmem_cache *s)
अणु
	पूर्णांक err;

	अगर (unlikely(!s))
		वापस;

	mutex_lock(&slab_mutex);

	s->refcount--;
	अगर (s->refcount)
		जाओ out_unlock;

	err = shutकरोwn_cache(s);
	अगर (err) अणु
		pr_err("kmem_cache_destroy %s: Slab cache still has objects\n",
		       s->name);
		dump_stack();
	पूर्ण
out_unlock:
	mutex_unlock(&slab_mutex);
पूर्ण
EXPORT_SYMBOL(kmem_cache_destroy);

/**
 * kmem_cache_shrink - Shrink a cache.
 * @cachep: The cache to shrink.
 *
 * Releases as many sद_असल as possible क्रम a cache.
 * To help debugging, a zero निकास status indicates all sद_असल were released.
 *
 * Return: %0 अगर all sद_असल were released, non-zero otherwise
 */
पूर्णांक kmem_cache_shrink(काष्ठा kmem_cache *cachep)
अणु
	पूर्णांक ret;


	kasan_cache_shrink(cachep);
	ret = __kmem_cache_shrink(cachep);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(kmem_cache_shrink);

bool slab_is_available(व्योम)
अणु
	वापस slab_state >= UP;
पूर्ण

#अगर_घोषित CONFIG_PRINTK
/**
 * kmem_valid_obj - करोes the poपूर्णांकer reference a valid slab object?
 * @object: poपूर्णांकer to query.
 *
 * Return: %true अगर the poपूर्णांकer is to a not-yet-मुक्तd object from
 * kदो_स्मृति() or kmem_cache_alloc(), either %true or %false अगर the poपूर्णांकer
 * is to an alपढ़ोy-मुक्तd object, and %false otherwise.
 */
bool kmem_valid_obj(व्योम *object)
अणु
	काष्ठा page *page;

	/* Some arches consider ZERO_SIZE_PTR to be a valid address. */
	अगर (object < (व्योम *)PAGE_SIZE || !virt_addr_valid(object))
		वापस false;
	page = virt_to_head_page(object);
	वापस PageSlab(page);
पूर्ण
EXPORT_SYMBOL_GPL(kmem_valid_obj);

/**
 * kmem_dump_obj - Prपूर्णांक available slab provenance inक्रमmation
 * @object: slab object क्रम which to find provenance inक्रमmation.
 *
 * This function uses pr_cont(), so that the caller is expected to have
 * prपूर्णांकed out whatever preamble is appropriate.  The provenance inक्रमmation
 * depends on the type of object and on how much debugging is enabled.
 * For a slab-cache object, the fact that it is a slab object is prपूर्णांकed,
 * and, अगर available, the slab name, वापस address, and stack trace from
 * the allocation of that object.
 *
 * This function will splat अगर passed a poपूर्णांकer to a non-slab object.
 * If you are not sure what type of object you have, you should instead
 * use mem_dump_obj().
 */
व्योम kmem_dump_obj(व्योम *object)
अणु
	अक्षर *cp = IS_ENABLED(CONFIG_MMU) ? "" : "/vmalloc";
	पूर्णांक i;
	काष्ठा page *page;
	अचिन्हित दीर्घ ptroffset;
	काष्ठा kmem_obj_info kp = अणु पूर्ण;

	अगर (WARN_ON_ONCE(!virt_addr_valid(object)))
		वापस;
	page = virt_to_head_page(object);
	अगर (WARN_ON_ONCE(!PageSlab(page))) अणु
		pr_cont(" non-slab memory.\n");
		वापस;
	पूर्ण
	kmem_obj_info(&kp, object, page);
	अगर (kp.kp_slab_cache)
		pr_cont(" slab%s %s", cp, kp.kp_slab_cache->name);
	अन्यथा
		pr_cont(" slab%s", cp);
	अगर (kp.kp_objp)
		pr_cont(" start %px", kp.kp_objp);
	अगर (kp.kp_data_offset)
		pr_cont(" data offset %lu", kp.kp_data_offset);
	अगर (kp.kp_objp) अणु
		ptroffset = ((अक्षर *)object - (अक्षर *)kp.kp_objp) - kp.kp_data_offset;
		pr_cont(" pointer offset %lu", ptroffset);
	पूर्ण
	अगर (kp.kp_slab_cache && kp.kp_slab_cache->usersize)
		pr_cont(" size %u", kp.kp_slab_cache->usersize);
	अगर (kp.kp_ret)
		pr_cont(" allocated at %pS\n", kp.kp_ret);
	अन्यथा
		pr_cont("\n");
	क्रम (i = 0; i < ARRAY_SIZE(kp.kp_stack); i++) अणु
		अगर (!kp.kp_stack[i])
			अवरोध;
		pr_info("    %pS\n", kp.kp_stack[i]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kmem_dump_obj);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_SLOB
/* Create a cache during boot when no slab services are available yet */
व्योम __init create_boot_cache(काष्ठा kmem_cache *s, स्थिर अक्षर *name,
		अचिन्हित पूर्णांक size, slab_flags_t flags,
		अचिन्हित पूर्णांक useroffset, अचिन्हित पूर्णांक usersize)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक align = ARCH_KMALLOC_MINALIGN;

	s->name = name;
	s->size = s->object_size = size;

	/*
	 * For घातer of two sizes, guarantee natural alignment क्रम kदो_स्मृति
	 * caches, regardless of SL*B debugging options.
	 */
	अगर (is_घातer_of_2(size))
		align = max(align, size);
	s->align = calculate_alignment(flags, align, size);

	s->useroffset = useroffset;
	s->usersize = usersize;

	err = __kmem_cache_create(s, flags);

	अगर (err)
		panic("Creation of kmalloc slab %s size=%u failed. Reason %d\n",
					name, size, err);

	s->refcount = -1;	/* Exempt from merging क्रम now */
पूर्ण

काष्ठा kmem_cache *__init create_kदो_स्मृति_cache(स्थिर अक्षर *name,
		अचिन्हित पूर्णांक size, slab_flags_t flags,
		अचिन्हित पूर्णांक useroffset, अचिन्हित पूर्णांक usersize)
अणु
	काष्ठा kmem_cache *s = kmem_cache_zalloc(kmem_cache, GFP_NOWAIT);

	अगर (!s)
		panic("Out of memory when creating slab %s\n", name);

	create_boot_cache(s, name, size, flags, useroffset, usersize);
	kasan_cache_create_kदो_स्मृति(s);
	list_add(&s->list, &slab_caches);
	s->refcount = 1;
	वापस s;
पूर्ण

काष्ठा kmem_cache *
kदो_स्मृति_caches[NR_KMALLOC_TYPES][KMALLOC_SHIFT_HIGH + 1] __ro_after_init =
अणु /* initialization क्रम https://bugs.llvm.org/show_bug.cgi?id=42570 */ पूर्ण;
EXPORT_SYMBOL(kदो_स्मृति_caches);

/*
 * Conversion table क्रम small sद_असल sizes / 8 to the index in the
 * kदो_स्मृति array. This is necessary क्रम sद_असल < 192 since we have non घातer
 * of two cache sizes there. The size of larger sद_असल can be determined using
 * fls.
 */
अटल u8 size_index[24] __ro_after_init = अणु
	3,	/* 8 */
	4,	/* 16 */
	5,	/* 24 */
	5,	/* 32 */
	6,	/* 40 */
	6,	/* 48 */
	6,	/* 56 */
	6,	/* 64 */
	1,	/* 72 */
	1,	/* 80 */
	1,	/* 88 */
	1,	/* 96 */
	7,	/* 104 */
	7,	/* 112 */
	7,	/* 120 */
	7,	/* 128 */
	2,	/* 136 */
	2,	/* 144 */
	2,	/* 152 */
	2,	/* 160 */
	2,	/* 168 */
	2,	/* 176 */
	2,	/* 184 */
	2	/* 192 */
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक size_index_elem(अचिन्हित पूर्णांक bytes)
अणु
	वापस (bytes - 1) / 8;
पूर्ण

/*
 * Find the kmem_cache काष्ठाure that serves a given size of
 * allocation
 */
काष्ठा kmem_cache *kदो_स्मृति_slab(माप_प्रकार size, gfp_t flags)
अणु
	अचिन्हित पूर्णांक index;

	अगर (size <= 192) अणु
		अगर (!size)
			वापस ZERO_SIZE_PTR;

		index = size_index[size_index_elem(size)];
	पूर्ण अन्यथा अणु
		अगर (WARN_ON_ONCE(size > KMALLOC_MAX_CACHE_SIZE))
			वापस शून्य;
		index = fls(size - 1);
	पूर्ण

	वापस kदो_स्मृति_caches[kदो_स्मृति_type(flags)][index];
पूर्ण

#अगर_घोषित CONFIG_ZONE_DMA
#घोषणा INIT_KMALLOC_INFO(__size, __लघु_size)			\
अणु								\
	.name[KMALLOC_NORMAL]  = "kmalloc-" #__लघु_size,	\
	.name[KMALLOC_RECLAIM] = "kmalloc-rcl-" #__लघु_size,	\
	.name[KMALLOC_DMA]     = "dma-kmalloc-" #__लघु_size,	\
	.size = __size,						\
पूर्ण
#अन्यथा
#घोषणा INIT_KMALLOC_INFO(__size, __लघु_size)			\
अणु								\
	.name[KMALLOC_NORMAL]  = "kmalloc-" #__लघु_size,	\
	.name[KMALLOC_RECLAIM] = "kmalloc-rcl-" #__लघु_size,	\
	.size = __size,						\
पूर्ण
#पूर्ण_अगर

/*
 * kदो_स्मृति_info[] is to make slub_debug=,kदो_स्मृति-xx option work at boot समय.
 * kदो_स्मृति_index() supports up to 2^26=64MB, so the final entry of the table is
 * kदो_स्मृति-67108864.
 */
स्थिर काष्ठा kदो_स्मृति_info_काष्ठा kदो_स्मृति_info[] __initस्थिर = अणु
	INIT_KMALLOC_INFO(0, 0),
	INIT_KMALLOC_INFO(96, 96),
	INIT_KMALLOC_INFO(192, 192),
	INIT_KMALLOC_INFO(8, 8),
	INIT_KMALLOC_INFO(16, 16),
	INIT_KMALLOC_INFO(32, 32),
	INIT_KMALLOC_INFO(64, 64),
	INIT_KMALLOC_INFO(128, 128),
	INIT_KMALLOC_INFO(256, 256),
	INIT_KMALLOC_INFO(512, 512),
	INIT_KMALLOC_INFO(1024, 1k),
	INIT_KMALLOC_INFO(2048, 2k),
	INIT_KMALLOC_INFO(4096, 4k),
	INIT_KMALLOC_INFO(8192, 8k),
	INIT_KMALLOC_INFO(16384, 16k),
	INIT_KMALLOC_INFO(32768, 32k),
	INIT_KMALLOC_INFO(65536, 64k),
	INIT_KMALLOC_INFO(131072, 128k),
	INIT_KMALLOC_INFO(262144, 256k),
	INIT_KMALLOC_INFO(524288, 512k),
	INIT_KMALLOC_INFO(1048576, 1M),
	INIT_KMALLOC_INFO(2097152, 2M),
	INIT_KMALLOC_INFO(4194304, 4M),
	INIT_KMALLOC_INFO(8388608, 8M),
	INIT_KMALLOC_INFO(16777216, 16M),
	INIT_KMALLOC_INFO(33554432, 32M),
	INIT_KMALLOC_INFO(67108864, 64M)
पूर्ण;

/*
 * Patch up the size_index table अगर we have strange large alignment
 * requirements क्रम the kदो_स्मृति array. This is only the हाल क्रम
 * MIPS it seems. The standard arches will not generate any code here.
 *
 * Largest permitted alignment is 256 bytes due to the way we
 * handle the index determination क्रम the smaller caches.
 *
 * Make sure that nothing crazy happens अगर someone starts tinkering
 * around with ARCH_KMALLOC_MINALIGN
 */
व्योम __init setup_kदो_स्मृति_cache_index_table(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	BUILD_BUG_ON(KMALLOC_MIN_SIZE > 256 ||
		(KMALLOC_MIN_SIZE & (KMALLOC_MIN_SIZE - 1)));

	क्रम (i = 8; i < KMALLOC_MIN_SIZE; i += 8) अणु
		अचिन्हित पूर्णांक elem = size_index_elem(i);

		अगर (elem >= ARRAY_SIZE(size_index))
			अवरोध;
		size_index[elem] = KMALLOC_SHIFT_LOW;
	पूर्ण

	अगर (KMALLOC_MIN_SIZE >= 64) अणु
		/*
		 * The 96 byte size cache is not used अगर the alignment
		 * is 64 byte.
		 */
		क्रम (i = 64 + 8; i <= 96; i += 8)
			size_index[size_index_elem(i)] = 7;

	पूर्ण

	अगर (KMALLOC_MIN_SIZE >= 128) अणु
		/*
		 * The 192 byte sized cache is not used अगर the alignment
		 * is 128 byte. Redirect kदो_स्मृति to use the 256 byte cache
		 * instead.
		 */
		क्रम (i = 128 + 8; i <= 192; i += 8)
			size_index[size_index_elem(i)] = 8;
	पूर्ण
पूर्ण

अटल व्योम __init
new_kदो_स्मृति_cache(पूर्णांक idx, क्रमागत kदो_स्मृति_cache_type type, slab_flags_t flags)
अणु
	अगर (type == KMALLOC_RECLAIM)
		flags |= SLAB_RECLAIM_ACCOUNT;

	kदो_स्मृति_caches[type][idx] = create_kदो_स्मृति_cache(
					kदो_स्मृति_info[idx].name[type],
					kदो_स्मृति_info[idx].size, flags, 0,
					kदो_स्मृति_info[idx].size);
पूर्ण

/*
 * Create the kदो_स्मृति array. Some of the regular kदो_स्मृति arrays
 * may alपढ़ोy have been created because they were needed to
 * enable allocations क्रम slab creation.
 */
व्योम __init create_kदो_स्मृति_caches(slab_flags_t flags)
अणु
	पूर्णांक i;
	क्रमागत kदो_स्मृति_cache_type type;

	क्रम (type = KMALLOC_NORMAL; type <= KMALLOC_RECLAIM; type++) अणु
		क्रम (i = KMALLOC_SHIFT_LOW; i <= KMALLOC_SHIFT_HIGH; i++) अणु
			अगर (!kदो_स्मृति_caches[type][i])
				new_kदो_स्मृति_cache(i, type, flags);

			/*
			 * Caches that are not of the two-to-the-घातer-of size.
			 * These have to be created immediately after the
			 * earlier घातer of two caches
			 */
			अगर (KMALLOC_MIN_SIZE <= 32 && i == 6 &&
					!kदो_स्मृति_caches[type][1])
				new_kदो_स्मृति_cache(1, type, flags);
			अगर (KMALLOC_MIN_SIZE <= 64 && i == 7 &&
					!kदो_स्मृति_caches[type][2])
				new_kदो_स्मृति_cache(2, type, flags);
		पूर्ण
	पूर्ण

	/* Kदो_स्मृति array is now usable */
	slab_state = UP;

#अगर_घोषित CONFIG_ZONE_DMA
	क्रम (i = 0; i <= KMALLOC_SHIFT_HIGH; i++) अणु
		काष्ठा kmem_cache *s = kदो_स्मृति_caches[KMALLOC_NORMAL][i];

		अगर (s) अणु
			kदो_स्मृति_caches[KMALLOC_DMA][i] = create_kदो_स्मृति_cache(
				kदो_स्मृति_info[i].name[KMALLOC_DMA],
				kदो_स्मृति_info[i].size,
				SLAB_CACHE_DMA | flags, 0,
				kदो_स्मृति_info[i].size);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* !CONFIG_SLOB */

gfp_t kदो_स्मृति_fix_flags(gfp_t flags)
अणु
	gfp_t invalid_mask = flags & GFP_SLAB_BUG_MASK;

	flags &= ~GFP_SLAB_BUG_MASK;
	pr_warn("Unexpected gfp: %#x (%pGg). Fixing up to gfp: %#x (%pGg). Fix your code!\n",
			invalid_mask, &invalid_mask, flags, &flags);
	dump_stack();

	वापस flags;
पूर्ण

/*
 * To aव्योम unnecessary overhead, we pass through large allocation requests
 * directly to the page allocator. We use __GFP_COMP, because we will need to
 * know the allocation order to मुक्त the pages properly in kमुक्त.
 */
व्योम *kदो_स्मृति_order(माप_प्रकार size, gfp_t flags, अचिन्हित पूर्णांक order)
अणु
	व्योम *ret = शून्य;
	काष्ठा page *page;

	अगर (unlikely(flags & GFP_SLAB_BUG_MASK))
		flags = kदो_स्मृति_fix_flags(flags);

	flags |= __GFP_COMP;
	page = alloc_pages(flags, order);
	अगर (likely(page)) अणु
		ret = page_address(page);
		mod_lruvec_page_state(page, NR_SLAB_UNRECLAIMABLE_B,
				      PAGE_SIZE << order);
	पूर्ण
	ret = kasan_kदो_स्मृति_large(ret, size, flags);
	/* As ret might get tagged, call kmemleak hook after KASAN. */
	kmemleak_alloc(ret, size, 1, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(kदो_स्मृति_order);

#अगर_घोषित CONFIG_TRACING
व्योम *kदो_स्मृति_order_trace(माप_प्रकार size, gfp_t flags, अचिन्हित पूर्णांक order)
अणु
	व्योम *ret = kदो_स्मृति_order(size, flags, order);
	trace_kदो_स्मृति(_RET_IP_, ret, size, PAGE_SIZE << order, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(kदो_स्मृति_order_trace);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SLAB_FREELIST_RANDOM
/* Ranकरोmize a generic मुक्तlist */
अटल व्योम मुक्तlist_अक्रमomize(काष्ठा rnd_state *state, अचिन्हित पूर्णांक *list,
			       अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक अक्रम;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		list[i] = i;

	/* Fisher-Yates shuffle */
	क्रम (i = count - 1; i > 0; i--) अणु
		अक्रम = pअक्रमom_u32_state(state);
		अक्रम %= (i + 1);
		swap(list[i], list[अक्रम]);
	पूर्ण
पूर्ण

/* Create a अक्रमom sequence per cache */
पूर्णांक cache_अक्रमom_seq_create(काष्ठा kmem_cache *cachep, अचिन्हित पूर्णांक count,
				    gfp_t gfp)
अणु
	काष्ठा rnd_state state;

	अगर (count < 2 || cachep->अक्रमom_seq)
		वापस 0;

	cachep->अक्रमom_seq = kसुस्मृति(count, माप(अचिन्हित पूर्णांक), gfp);
	अगर (!cachep->अक्रमom_seq)
		वापस -ENOMEM;

	/* Get best entropy at this stage of boot */
	pअक्रमom_seed_state(&state, get_अक्रमom_दीर्घ());

	मुक्तlist_अक्रमomize(&state, cachep->अक्रमom_seq, count);
	वापस 0;
पूर्ण

/* Destroy the per-cache अक्रमom मुक्तlist sequence */
व्योम cache_अक्रमom_seq_destroy(काष्ठा kmem_cache *cachep)
अणु
	kमुक्त(cachep->अक्रमom_seq);
	cachep->अक्रमom_seq = शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_SLAB_FREELIST_RANDOM */

#अगर defined(CONFIG_SLAB) || defined(CONFIG_SLUB_DEBUG)
#अगर_घोषित CONFIG_SLAB
#घोषणा SLABINFO_RIGHTS (0600)
#अन्यथा
#घोषणा SLABINFO_RIGHTS (0400)
#पूर्ण_अगर

अटल व्योम prपूर्णांक_slabinfo_header(काष्ठा seq_file *m)
अणु
	/*
	 * Output क्रमmat version, so at least we can change it
	 * without _too_ many complaपूर्णांकs.
	 */
#अगर_घोषित CONFIG_DEBUG_SLAB
	seq_माला_दो(m, "slabinfo - version: 2.1 (statistics)\n");
#अन्यथा
	seq_माला_दो(m, "slabinfo - version: 2.1\n");
#पूर्ण_अगर
	seq_माला_दो(m, "# name            <active_objs> <num_objs> <objsize> <objperslab> <pagesperslab>");
	seq_माला_दो(m, " : tunables <limit> <batchcount> <sharedfactor>");
	seq_माला_दो(m, " : slabdata <active_slabs> <num_slabs> <sharedavail>");
#अगर_घोषित CONFIG_DEBUG_SLAB
	seq_माला_दो(m, " : globalstat <listallocs> <maxobjs> <grown> <reaped> <error> <maxfreeable> <nodeallocs> <remotefrees> <alienoverflow>");
	seq_माला_दो(m, " : cpustat <allochit> <allocmiss> <freehit> <freemiss>");
#पूर्ण_अगर
	seq_अ_दो(m, '\n');
पूर्ण

व्योम *slab_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	mutex_lock(&slab_mutex);
	वापस seq_list_start(&slab_caches, *pos);
पूर्ण

व्योम *slab_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos)
अणु
	वापस seq_list_next(p, &slab_caches, pos);
पूर्ण

व्योम slab_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	mutex_unlock(&slab_mutex);
पूर्ण

अटल व्योम cache_show(काष्ठा kmem_cache *s, काष्ठा seq_file *m)
अणु
	काष्ठा slabinfo sinfo;

	स_रखो(&sinfo, 0, माप(sinfo));
	get_slabinfo(s, &sinfo);

	seq_म_लिखो(m, "%-17s %6lu %6lu %6u %4u %4d",
		   s->name, sinfo.active_objs, sinfo.num_objs, s->size,
		   sinfo.objects_per_slab, (1 << sinfo.cache_order));

	seq_म_लिखो(m, " : tunables %4u %4u %4u",
		   sinfo.limit, sinfo.batchcount, sinfo.shared);
	seq_म_लिखो(m, " : slabdata %6lu %6lu %6lu",
		   sinfo.active_sद_असल, sinfo.num_sद_असल, sinfo.shared_avail);
	slabinfo_show_stats(m, s);
	seq_अ_दो(m, '\n');
पूर्ण

अटल पूर्णांक slab_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा kmem_cache *s = list_entry(p, काष्ठा kmem_cache, list);

	अगर (p == slab_caches.next)
		prपूर्णांक_slabinfo_header(m);
	cache_show(s, m);
	वापस 0;
पूर्ण

व्योम dump_unreclaimable_slab(व्योम)
अणु
	काष्ठा kmem_cache *s;
	काष्ठा slabinfo sinfo;

	/*
	 * Here acquiring slab_mutex is risky since we करोn't prefer to get
	 * sleep in oom path. But, without mutex hold, it may पूर्णांकroduce a
	 * risk of crash.
	 * Use mutex_trylock to protect the list traverse, dump nothing
	 * without acquiring the mutex.
	 */
	अगर (!mutex_trylock(&slab_mutex)) अणु
		pr_warn("excessive unreclaimable slab but cannot dump stats\n");
		वापस;
	पूर्ण

	pr_info("Unreclaimable slab info:\n");
	pr_info("Name                      Used          Total\n");

	list_क्रम_each_entry(s, &slab_caches, list) अणु
		अगर (s->flags & SLAB_RECLAIM_ACCOUNT)
			जारी;

		get_slabinfo(s, &sinfo);

		अगर (sinfo.num_objs > 0)
			pr_info("%-17s %10luKB %10luKB\n", s->name,
				(sinfo.active_objs * s->size) / 1024,
				(sinfo.num_objs * s->size) / 1024);
	पूर्ण
	mutex_unlock(&slab_mutex);
पूर्ण

#अगर defined(CONFIG_MEMCG_KMEM)
पूर्णांक memcg_slab_show(काष्ठा seq_file *m, व्योम *p)
अणु
	/*
	 * Deprecated.
	 * Please, take a look at tools/cgroup/slabinfo.py .
	 */
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * slabinfo_op - iterator that generates /proc/slabinfo
 *
 * Output layout:
 * cache-name
 * num-active-objs
 * total-objs
 * object size
 * num-active-sद_असल
 * total-sद_असल
 * num-pages-per-slab
 * + further values on SMP and with statistics enabled
 */
अटल स्थिर काष्ठा seq_operations slabinfo_op = अणु
	.start = slab_start,
	.next = slab_next,
	.stop = slab_stop,
	.show = slab_show,
पूर्ण;

अटल पूर्णांक slabinfo_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &slabinfo_op);
पूर्ण

अटल स्थिर काष्ठा proc_ops slabinfo_proc_ops = अणु
	.proc_flags	= PROC_ENTRY_PERMANENT,
	.proc_खोलो	= slabinfo_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= slabinfo_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release,
पूर्ण;

अटल पूर्णांक __init slab_proc_init(व्योम)
अणु
	proc_create("slabinfo", SLABINFO_RIGHTS, शून्य, &slabinfo_proc_ops);
	वापस 0;
पूर्ण
module_init(slab_proc_init);

#पूर्ण_अगर /* CONFIG_SLAB || CONFIG_SLUB_DEBUG */

अटल __always_अंतरभूत व्योम *__करो_kपुनः_स्मृति(स्थिर व्योम *p, माप_प्रकार new_size,
					   gfp_t flags)
अणु
	व्योम *ret;
	माप_प्रकार ks;

	/* Don't use instrumented ksize to allow precise KASAN poisoning. */
	अगर (likely(!ZERO_OR_शून्य_PTR(p))) अणु
		अगर (!kasan_check_byte(p))
			वापस शून्य;
		ks = kfence_ksize(p) ?: __ksize(p);
	पूर्ण अन्यथा
		ks = 0;

	/* If the object still fits, repoison it precisely. */
	अगर (ks >= new_size) अणु
		p = kasan_kपुनः_स्मृति((व्योम *)p, new_size, flags);
		वापस (व्योम *)p;
	पूर्ण

	ret = kदो_स्मृति_track_caller(new_size, flags);
	अगर (ret && p) अणु
		/* Disable KASAN checks as the object's redzone is accessed. */
		kasan_disable_current();
		स_नकल(ret, kasan_reset_tag(p), ks);
		kasan_enable_current();
	पूर्ण

	वापस ret;
पूर्ण

/**
 * kपुनः_स्मृति - पुनः_स्मृतिate memory. The contents will reमुख्य unchanged.
 * @p: object to पुनः_स्मृतिate memory क्रम.
 * @new_size: how many bytes of memory are required.
 * @flags: the type of memory to allocate.
 *
 * The contents of the object poपूर्णांकed to are preserved up to the
 * lesser of the new and old sizes (__GFP_ZERO flag is effectively ignored).
 * If @p is %शून्य, kपुनः_स्मृति() behaves exactly like kदो_स्मृति().  If @new_size
 * is 0 and @p is not a %शून्य poपूर्णांकer, the object poपूर्णांकed to is मुक्तd.
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य in हाल of error
 */
व्योम *kपुनः_स्मृति(स्थिर व्योम *p, माप_प्रकार new_size, gfp_t flags)
अणु
	व्योम *ret;

	अगर (unlikely(!new_size)) अणु
		kमुक्त(p);
		वापस ZERO_SIZE_PTR;
	पूर्ण

	ret = __करो_kपुनः_स्मृति(p, new_size, flags);
	अगर (ret && kasan_reset_tag(p) != kasan_reset_tag(ret))
		kमुक्त(p);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(kपुनः_स्मृति);

/**
 * kमुक्त_sensitive - Clear sensitive inक्रमmation in memory beक्रमe मुक्तing
 * @p: object to मुक्त memory of
 *
 * The memory of the object @p poपूर्णांकs to is zeroed beक्रमe मुक्तd.
 * If @p is %शून्य, kमुक्त_sensitive() करोes nothing.
 *
 * Note: this function zeroes the whole allocated buffer which can be a good
 * deal bigger than the requested buffer size passed to kदो_स्मृति(). So be
 * careful when using this function in perक्रमmance sensitive code.
 */
व्योम kमुक्त_sensitive(स्थिर व्योम *p)
अणु
	माप_प्रकार ks;
	व्योम *mem = (व्योम *)p;

	ks = ksize(mem);
	अगर (ks)
		memzero_explicit(mem, ks);
	kमुक्त(mem);
पूर्ण
EXPORT_SYMBOL(kमुक्त_sensitive);

/**
 * ksize - get the actual amount of memory allocated क्रम a given object
 * @objp: Poपूर्णांकer to the object
 *
 * kदो_स्मृति may पूर्णांकernally round up allocations and वापस more memory
 * than requested. ksize() can be used to determine the actual amount of
 * memory allocated. The caller may use this additional memory, even though
 * a smaller amount of memory was initially specअगरied with the kदो_स्मृति call.
 * The caller must guarantee that objp poपूर्णांकs to a valid object previously
 * allocated with either kदो_स्मृति() or kmem_cache_alloc(). The object
 * must not be मुक्तd during the duration of the call.
 *
 * Return: size of the actual memory used by @objp in bytes
 */
माप_प्रकार ksize(स्थिर व्योम *objp)
अणु
	माप_प्रकार size;

	/*
	 * We need to first check that the poपूर्णांकer to the object is valid, and
	 * only then unpoison the memory. The report prपूर्णांकed from ksize() is
	 * more useful, then when it's prपूर्णांकed later when the behaviour could
	 * be undefined due to a potential use-after-मुक्त or द्विगुन-मुक्त.
	 *
	 * We use kasan_check_byte(), which is supported क्रम the hardware
	 * tag-based KASAN mode, unlike kasan_check_पढ़ो/ग_लिखो().
	 *
	 * If the poपूर्णांकed to memory is invalid, we वापस 0 to aव्योम users of
	 * ksize() writing to and potentially corrupting the memory region.
	 *
	 * We want to perक्रमm the check beक्रमe __ksize(), to aव्योम potentially
	 * crashing in __ksize() due to accessing invalid metadata.
	 */
	अगर (unlikely(ZERO_OR_शून्य_PTR(objp)) || !kasan_check_byte(objp))
		वापस 0;

	size = kfence_ksize(objp) ?: __ksize(objp);
	/*
	 * We assume that ksize callers could use whole allocated area,
	 * so we need to unpoison this area.
	 */
	kasan_unpoison_range(objp, size);
	वापस size;
पूर्ण
EXPORT_SYMBOL(ksize);

/* Tracepoपूर्णांकs definitions. */
EXPORT_TRACEPOINT_SYMBOL(kदो_स्मृति);
EXPORT_TRACEPOINT_SYMBOL(kmem_cache_alloc);
EXPORT_TRACEPOINT_SYMBOL(kदो_स्मृति_node);
EXPORT_TRACEPOINT_SYMBOL(kmem_cache_alloc_node);
EXPORT_TRACEPOINT_SYMBOL(kमुक्त);
EXPORT_TRACEPOINT_SYMBOL(kmem_cache_मुक्त);

पूर्णांक should_failslab(काष्ठा kmem_cache *s, gfp_t gfpflags)
अणु
	अगर (__should_failslab(s, gfpflags))
		वापस -ENOMEM;
	वापस 0;
पूर्ण
ALLOW_ERROR_INJECTION(should_failslab, ERRNO);
