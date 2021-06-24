<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित MM_SLAB_H
#घोषणा MM_SLAB_H
/*
 * Internal slab definitions
 */

#अगर_घोषित CONFIG_SLOB
/*
 * Common fields provided in kmem_cache by all slab allocators
 * This काष्ठा is either used directly by the allocator (SLOB)
 * or the allocator must include definitions क्रम all fields
 * provided in kmem_cache_common in their definition of kmem_cache.
 *
 * Once we can करो anonymous काष्ठाs (C11 standard) we could put a
 * anonymous काष्ठा definition in these allocators so that the
 * separate allocations in the kmem_cache काष्ठाure of SLAB and
 * SLUB is no दीर्घer needed.
 */
काष्ठा kmem_cache अणु
	अचिन्हित पूर्णांक object_size;/* The original size of the object */
	अचिन्हित पूर्णांक size;	/* The aligned/padded/added on size  */
	अचिन्हित पूर्णांक align;	/* Alignment as calculated */
	slab_flags_t flags;	/* Active flags on the slab */
	अचिन्हित पूर्णांक useroffset;/* Usercopy region offset */
	अचिन्हित पूर्णांक usersize;	/* Usercopy region size */
	स्थिर अक्षर *name;	/* Slab name क्रम sysfs */
	पूर्णांक refcount;		/* Use counter */
	व्योम (*ctor)(व्योम *);	/* Called on object slot creation */
	काष्ठा list_head list;	/* List of all slab caches on the प्रणाली */
पूर्ण;

#पूर्ण_अगर /* CONFIG_SLOB */

#अगर_घोषित CONFIG_SLAB
#समावेश <linux/slab_def.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_SLUB
#समावेश <linux/slub_def.h>
#पूर्ण_अगर

#समावेश <linux/memcontrol.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched/mm.h>

/*
 * State of the slab allocator.
 *
 * This is used to describe the states of the allocator during bootup.
 * Allocators use this to gradually bootstrap themselves. Most allocators
 * have the problem that the काष्ठाures used क्रम managing slab caches are
 * allocated from slab caches themselves.
 */
क्रमागत slab_state अणु
	DOWN,			/* No slab functionality yet */
	PARTIAL,		/* SLUB: kmem_cache_node available */
	PARTIAL_NODE,		/* SLAB: kदो_स्मृति size क्रम node काष्ठा available */
	UP,			/* Slab caches usable but not all extras yet */
	FULL			/* Everything is working */
पूर्ण;

बाह्य क्रमागत slab_state slab_state;

/* The slab cache mutex protects the management काष्ठाures during changes */
बाह्य काष्ठा mutex slab_mutex;

/* The list of all slab caches on the प्रणाली */
बाह्य काष्ठा list_head slab_caches;

/* The slab cache that manages slab cache inक्रमmation */
बाह्य काष्ठा kmem_cache *kmem_cache;

/* A table of kदो_स्मृति cache names and sizes */
बाह्य स्थिर काष्ठा kदो_स्मृति_info_काष्ठा अणु
	स्थिर अक्षर *name[NR_KMALLOC_TYPES];
	अचिन्हित पूर्णांक size;
पूर्ण kदो_स्मृति_info[];

#अगर_अघोषित CONFIG_SLOB
/* Kदो_स्मृति array related functions */
व्योम setup_kदो_स्मृति_cache_index_table(व्योम);
व्योम create_kदो_स्मृति_caches(slab_flags_t);

/* Find the kदो_स्मृति slab corresponding क्रम a certain size */
काष्ठा kmem_cache *kदो_स्मृति_slab(माप_प्रकार, gfp_t);
#पूर्ण_अगर

gfp_t kदो_स्मृति_fix_flags(gfp_t flags);

/* Functions provided by the slab allocators */
पूर्णांक __kmem_cache_create(काष्ठा kmem_cache *, slab_flags_t flags);

काष्ठा kmem_cache *create_kदो_स्मृति_cache(स्थिर अक्षर *name, अचिन्हित पूर्णांक size,
			slab_flags_t flags, अचिन्हित पूर्णांक useroffset,
			अचिन्हित पूर्णांक usersize);
बाह्य व्योम create_boot_cache(काष्ठा kmem_cache *, स्थिर अक्षर *name,
			अचिन्हित पूर्णांक size, slab_flags_t flags,
			अचिन्हित पूर्णांक useroffset, अचिन्हित पूर्णांक usersize);

पूर्णांक slab_unmergeable(काष्ठा kmem_cache *s);
काष्ठा kmem_cache *find_mergeable(अचिन्हित size, अचिन्हित align,
		slab_flags_t flags, स्थिर अक्षर *name, व्योम (*ctor)(व्योम *));
#अगर_अघोषित CONFIG_SLOB
काष्ठा kmem_cache *
__kmem_cache_alias(स्थिर अक्षर *name, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक align,
		   slab_flags_t flags, व्योम (*ctor)(व्योम *));

slab_flags_t kmem_cache_flags(अचिन्हित पूर्णांक object_size,
	slab_flags_t flags, स्थिर अक्षर *name);
#अन्यथा
अटल अंतरभूत काष्ठा kmem_cache *
__kmem_cache_alias(स्थिर अक्षर *name, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक align,
		   slab_flags_t flags, व्योम (*ctor)(व्योम *))
अणु वापस शून्य; पूर्ण

अटल अंतरभूत slab_flags_t kmem_cache_flags(अचिन्हित पूर्णांक object_size,
	slab_flags_t flags, स्थिर अक्षर *name)
अणु
	वापस flags;
पूर्ण
#पूर्ण_अगर


/* Legal flag mask क्रम kmem_cache_create(), क्रम various configurations */
#घोषणा SLAB_CORE_FLAGS (SLAB_HWCACHE_ALIGN | SLAB_CACHE_DMA | \
			 SLAB_CACHE_DMA32 | SLAB_PANIC | \
			 SLAB_TYPESAFE_BY_RCU | SLAB_DEBUG_OBJECTS )

#अगर defined(CONFIG_DEBUG_SLAB)
#घोषणा SLAB_DEBUG_FLAGS (SLAB_RED_ZONE | SLAB_POISON | SLAB_STORE_USER)
#या_अगर defined(CONFIG_SLUB_DEBUG)
#घोषणा SLAB_DEBUG_FLAGS (SLAB_RED_ZONE | SLAB_POISON | SLAB_STORE_USER | \
			  SLAB_TRACE | SLAB_CONSISTENCY_CHECKS)
#अन्यथा
#घोषणा SLAB_DEBUG_FLAGS (0)
#पूर्ण_अगर

#अगर defined(CONFIG_SLAB)
#घोषणा SLAB_CACHE_FLAGS (SLAB_MEM_SPREAD | SLAB_NOLEAKTRACE | \
			  SLAB_RECLAIM_ACCOUNT | SLAB_TEMPORARY | \
			  SLAB_ACCOUNT)
#या_अगर defined(CONFIG_SLUB)
#घोषणा SLAB_CACHE_FLAGS (SLAB_NOLEAKTRACE | SLAB_RECLAIM_ACCOUNT | \
			  SLAB_TEMPORARY | SLAB_ACCOUNT)
#अन्यथा
#घोषणा SLAB_CACHE_FLAGS (0)
#पूर्ण_अगर

/* Common flags available with current configuration */
#घोषणा CACHE_CREATE_MASK (SLAB_CORE_FLAGS | SLAB_DEBUG_FLAGS | SLAB_CACHE_FLAGS)

/* Common flags permitted क्रम kmem_cache_create */
#घोषणा SLAB_FLAGS_PERMITTED (SLAB_CORE_FLAGS | \
			      SLAB_RED_ZONE | \
			      SLAB_POISON | \
			      SLAB_STORE_USER | \
			      SLAB_TRACE | \
			      SLAB_CONSISTENCY_CHECKS | \
			      SLAB_MEM_SPREAD | \
			      SLAB_NOLEAKTRACE | \
			      SLAB_RECLAIM_ACCOUNT | \
			      SLAB_TEMPORARY | \
			      SLAB_ACCOUNT)

bool __kmem_cache_empty(काष्ठा kmem_cache *);
पूर्णांक __kmem_cache_shutकरोwn(काष्ठा kmem_cache *);
व्योम __kmem_cache_release(काष्ठा kmem_cache *);
पूर्णांक __kmem_cache_shrink(काष्ठा kmem_cache *);
व्योम slab_kmem_cache_release(काष्ठा kmem_cache *);

काष्ठा seq_file;
काष्ठा file;

काष्ठा slabinfo अणु
	अचिन्हित दीर्घ active_objs;
	अचिन्हित दीर्घ num_objs;
	अचिन्हित दीर्घ active_sद_असल;
	अचिन्हित दीर्घ num_sद_असल;
	अचिन्हित दीर्घ shared_avail;
	अचिन्हित पूर्णांक limit;
	अचिन्हित पूर्णांक batchcount;
	अचिन्हित पूर्णांक shared;
	अचिन्हित पूर्णांक objects_per_slab;
	अचिन्हित पूर्णांक cache_order;
पूर्ण;

व्योम get_slabinfo(काष्ठा kmem_cache *s, काष्ठा slabinfo *sinfo);
व्योम slabinfo_show_stats(काष्ठा seq_file *m, काष्ठा kmem_cache *s);
sमाप_प्रकार slabinfo_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		       माप_प्रकार count, loff_t *ppos);

/*
 * Generic implementation of bulk operations
 * These are useful क्रम situations in which the allocator cannot
 * perक्रमm optimizations. In that हाल segments of the object listed
 * may be allocated or मुक्तd using these operations.
 */
व्योम __kmem_cache_मुक्त_bulk(काष्ठा kmem_cache *, माप_प्रकार, व्योम **);
पूर्णांक __kmem_cache_alloc_bulk(काष्ठा kmem_cache *, gfp_t, माप_प्रकार, व्योम **);

अटल अंतरभूत क्रमागत node_stat_item cache_vmstat_idx(काष्ठा kmem_cache *s)
अणु
	वापस (s->flags & SLAB_RECLAIM_ACCOUNT) ?
		NR_SLAB_RECLAIMABLE_B : NR_SLAB_UNRECLAIMABLE_B;
पूर्ण

#अगर_घोषित CONFIG_SLUB_DEBUG
#अगर_घोषित CONFIG_SLUB_DEBUG_ON
DECLARE_STATIC_KEY_TRUE(slub_debug_enabled);
#अन्यथा
DECLARE_STATIC_KEY_FALSE(slub_debug_enabled);
#पूर्ण_अगर
बाह्य व्योम prपूर्णांक_tracking(काष्ठा kmem_cache *s, व्योम *object);
#अन्यथा
अटल अंतरभूत व्योम prपूर्णांक_tracking(काष्ठा kmem_cache *s, व्योम *object)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Returns true अगर any of the specअगरied slub_debug flags is enabled क्रम the
 * cache. Use only क्रम flags parsed by setup_slub_debug() as it also enables
 * the अटल key.
 */
अटल अंतरभूत bool kmem_cache_debug_flags(काष्ठा kmem_cache *s, slab_flags_t flags)
अणु
#अगर_घोषित CONFIG_SLUB_DEBUG
	VM_WARN_ON_ONCE(!(flags & SLAB_DEBUG_FLAGS));
	अगर (अटल_branch_unlikely(&slub_debug_enabled))
		वापस s->flags & flags;
#पूर्ण_अगर
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_MEMCG_KMEM
पूर्णांक memcg_alloc_page_obj_cgroups(काष्ठा page *page, काष्ठा kmem_cache *s,
				 gfp_t gfp, bool new_page);

अटल अंतरभूत व्योम memcg_मुक्त_page_obj_cgroups(काष्ठा page *page)
अणु
	kमुक्त(page_objcgs(page));
	page->memcg_data = 0;
पूर्ण

अटल अंतरभूत माप_प्रकार obj_full_size(काष्ठा kmem_cache *s)
अणु
	/*
	 * For each accounted object there is an extra space which is used
	 * to store obj_cgroup membership. Charge it too.
	 */
	वापस s->size + माप(काष्ठा obj_cgroup *);
पूर्ण

/*
 * Returns false अगर the allocation should fail.
 */
अटल अंतरभूत bool memcg_slab_pre_alloc_hook(काष्ठा kmem_cache *s,
					     काष्ठा obj_cgroup **objcgp,
					     माप_प्रकार objects, gfp_t flags)
अणु
	काष्ठा obj_cgroup *objcg;

	अगर (!memcg_kmem_enabled())
		वापस true;

	अगर (!(flags & __GFP_ACCOUNT) && !(s->flags & SLAB_ACCOUNT))
		वापस true;

	objcg = get_obj_cgroup_from_current();
	अगर (!objcg)
		वापस true;

	अगर (obj_cgroup_अक्षरge(objcg, flags, objects * obj_full_size(s))) अणु
		obj_cgroup_put(objcg);
		वापस false;
	पूर्ण

	*objcgp = objcg;
	वापस true;
पूर्ण

अटल अंतरभूत व्योम mod_objcg_state(काष्ठा obj_cgroup *objcg,
				   काष्ठा pglist_data *pgdat,
				   क्रमागत node_stat_item idx, पूर्णांक nr)
अणु
	काष्ठा mem_cgroup *memcg;
	काष्ठा lruvec *lruvec;

	rcu_पढ़ो_lock();
	memcg = obj_cgroup_memcg(objcg);
	lruvec = mem_cgroup_lruvec(memcg, pgdat);
	mod_memcg_lruvec_state(lruvec, idx, nr);
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत व्योम memcg_slab_post_alloc_hook(काष्ठा kmem_cache *s,
					      काष्ठा obj_cgroup *objcg,
					      gfp_t flags, माप_प्रकार size,
					      व्योम **p)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ off;
	माप_प्रकार i;

	अगर (!memcg_kmem_enabled() || !objcg)
		वापस;

	flags &= ~__GFP_ACCOUNT;
	क्रम (i = 0; i < size; i++) अणु
		अगर (likely(p[i])) अणु
			page = virt_to_head_page(p[i]);

			अगर (!page_objcgs(page) &&
			    memcg_alloc_page_obj_cgroups(page, s, flags,
							 false)) अणु
				obj_cgroup_unअक्षरge(objcg, obj_full_size(s));
				जारी;
			पूर्ण

			off = obj_to_index(s, page, p[i]);
			obj_cgroup_get(objcg);
			page_objcgs(page)[off] = objcg;
			mod_objcg_state(objcg, page_pgdat(page),
					cache_vmstat_idx(s), obj_full_size(s));
		पूर्ण अन्यथा अणु
			obj_cgroup_unअक्षरge(objcg, obj_full_size(s));
		पूर्ण
	पूर्ण
	obj_cgroup_put(objcg);
पूर्ण

अटल अंतरभूत व्योम memcg_slab_मुक्त_hook(काष्ठा kmem_cache *s_orig,
					व्योम **p, पूर्णांक objects)
अणु
	काष्ठा kmem_cache *s;
	काष्ठा obj_cgroup **objcgs;
	काष्ठा obj_cgroup *objcg;
	काष्ठा page *page;
	अचिन्हित पूर्णांक off;
	पूर्णांक i;

	अगर (!memcg_kmem_enabled())
		वापस;

	क्रम (i = 0; i < objects; i++) अणु
		अगर (unlikely(!p[i]))
			जारी;

		page = virt_to_head_page(p[i]);
		objcgs = page_objcgs(page);
		अगर (!objcgs)
			जारी;

		अगर (!s_orig)
			s = page->slab_cache;
		अन्यथा
			s = s_orig;

		off = obj_to_index(s, page, p[i]);
		objcg = objcgs[off];
		अगर (!objcg)
			जारी;

		objcgs[off] = शून्य;
		obj_cgroup_unअक्षरge(objcg, obj_full_size(s));
		mod_objcg_state(objcg, page_pgdat(page), cache_vmstat_idx(s),
				-obj_full_size(s));
		obj_cgroup_put(objcg);
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_MEMCG_KMEM */
अटल अंतरभूत काष्ठा mem_cgroup *memcg_from_slab_obj(व्योम *ptr)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक memcg_alloc_page_obj_cgroups(काष्ठा page *page,
					       काष्ठा kmem_cache *s, gfp_t gfp,
					       bool new_page)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम memcg_मुक्त_page_obj_cgroups(काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत bool memcg_slab_pre_alloc_hook(काष्ठा kmem_cache *s,
					     काष्ठा obj_cgroup **objcgp,
					     माप_प्रकार objects, gfp_t flags)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम memcg_slab_post_alloc_hook(काष्ठा kmem_cache *s,
					      काष्ठा obj_cgroup *objcg,
					      gfp_t flags, माप_प्रकार size,
					      व्योम **p)
अणु
पूर्ण

अटल अंतरभूत व्योम memcg_slab_मुक्त_hook(काष्ठा kmem_cache *s,
					व्योम **p, पूर्णांक objects)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMCG_KMEM */

अटल अंतरभूत काष्ठा kmem_cache *virt_to_cache(स्थिर व्योम *obj)
अणु
	काष्ठा page *page;

	page = virt_to_head_page(obj);
	अगर (WARN_ONCE(!PageSlab(page), "%s: Object is not a Slab page!\n",
					__func__))
		वापस शून्य;
	वापस page->slab_cache;
पूर्ण

अटल __always_अंतरभूत व्योम account_slab_page(काष्ठा page *page, पूर्णांक order,
					      काष्ठा kmem_cache *s,
					      gfp_t gfp)
अणु
	अगर (memcg_kmem_enabled() && (s->flags & SLAB_ACCOUNT))
		memcg_alloc_page_obj_cgroups(page, s, gfp, true);

	mod_node_page_state(page_pgdat(page), cache_vmstat_idx(s),
			    PAGE_SIZE << order);
पूर्ण

अटल __always_अंतरभूत व्योम unaccount_slab_page(काष्ठा page *page, पूर्णांक order,
						काष्ठा kmem_cache *s)
अणु
	अगर (memcg_kmem_enabled())
		memcg_मुक्त_page_obj_cgroups(page);

	mod_node_page_state(page_pgdat(page), cache_vmstat_idx(s),
			    -(PAGE_SIZE << order));
पूर्ण

अटल अंतरभूत काष्ठा kmem_cache *cache_from_obj(काष्ठा kmem_cache *s, व्योम *x)
अणु
	काष्ठा kmem_cache *cachep;

	अगर (!IS_ENABLED(CONFIG_SLAB_FREELIST_HARDENED) &&
	    !kmem_cache_debug_flags(s, SLAB_CONSISTENCY_CHECKS))
		वापस s;

	cachep = virt_to_cache(x);
	अगर (WARN(cachep && cachep != s,
		  "%s: Wrong slab cache. %s but object is from %s\n",
		  __func__, s->name, cachep->name))
		prपूर्णांक_tracking(cachep, x);
	वापस cachep;
पूर्ण

अटल अंतरभूत माप_प्रकार slab_ksize(स्थिर काष्ठा kmem_cache *s)
अणु
#अगर_अघोषित CONFIG_SLUB
	वापस s->object_size;

#अन्यथा /* CONFIG_SLUB */
# अगरdef CONFIG_SLUB_DEBUG
	/*
	 * Debugging requires use of the padding between object
	 * and whatever may come after it.
	 */
	अगर (s->flags & (SLAB_RED_ZONE | SLAB_POISON))
		वापस s->object_size;
# endअगर
	अगर (s->flags & SLAB_KASAN)
		वापस s->object_size;
	/*
	 * If we have the need to store the मुक्तlist poपूर्णांकer
	 * back there or track user inक्रमmation then we can
	 * only use the space beक्रमe that inक्रमmation.
	 */
	अगर (s->flags & (SLAB_TYPESAFE_BY_RCU | SLAB_STORE_USER))
		वापस s->inuse;
	/*
	 * Else we can use all the padding etc क्रम the allocation
	 */
	वापस s->size;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा kmem_cache *slab_pre_alloc_hook(काष्ठा kmem_cache *s,
						     काष्ठा obj_cgroup **objcgp,
						     माप_प्रकार size, gfp_t flags)
अणु
	flags &= gfp_allowed_mask;

	might_alloc(flags);

	अगर (should_failslab(s, flags))
		वापस शून्य;

	अगर (!memcg_slab_pre_alloc_hook(s, objcgp, size, flags))
		वापस शून्य;

	वापस s;
पूर्ण

अटल अंतरभूत व्योम slab_post_alloc_hook(काष्ठा kmem_cache *s,
					काष्ठा obj_cgroup *objcg, gfp_t flags,
					माप_प्रकार size, व्योम **p, bool init)
अणु
	माप_प्रकार i;

	flags &= gfp_allowed_mask;

	/*
	 * As memory initialization might be पूर्णांकegrated पूर्णांकo KASAN,
	 * kasan_slab_alloc and initialization स_रखो must be
	 * kept together to aव्योम discrepancies in behavior.
	 *
	 * As p[i] might get tagged, स_रखो and kmemleak hook come after KASAN.
	 */
	क्रम (i = 0; i < size; i++) अणु
		p[i] = kasan_slab_alloc(s, p[i], flags, init);
		अगर (p[i] && init && !kasan_has_पूर्णांकegrated_init())
			स_रखो(p[i], 0, s->object_size);
		kmemleak_alloc_recursive(p[i], s->object_size, 1,
					 s->flags, flags);
	पूर्ण

	memcg_slab_post_alloc_hook(s, objcg, flags, size, p);
पूर्ण

#अगर_अघोषित CONFIG_SLOB
/*
 * The slab lists क्रम all objects.
 */
काष्ठा kmem_cache_node अणु
	spinlock_t list_lock;

#अगर_घोषित CONFIG_SLAB
	काष्ठा list_head sद_असल_partial;	/* partial list first, better यंत्र code */
	काष्ठा list_head sद_असल_full;
	काष्ठा list_head sद_असल_मुक्त;
	अचिन्हित दीर्घ total_sद_असल;	/* length of all slab lists */
	अचिन्हित दीर्घ मुक्त_sद_असल;	/* length of मुक्त slab list only */
	अचिन्हित दीर्घ मुक्त_objects;
	अचिन्हित पूर्णांक मुक्त_limit;
	अचिन्हित पूर्णांक colour_next;	/* Per-node cache coloring */
	काष्ठा array_cache *shared;	/* shared per node */
	काष्ठा alien_cache **alien;	/* on other nodes */
	अचिन्हित दीर्घ next_reap;	/* updated without locking */
	पूर्णांक मुक्त_touched;		/* updated without locking */
#पूर्ण_अगर

#अगर_घोषित CONFIG_SLUB
	अचिन्हित दीर्घ nr_partial;
	काष्ठा list_head partial;
#अगर_घोषित CONFIG_SLUB_DEBUG
	atomic_दीर्घ_t nr_sद_असल;
	atomic_दीर्घ_t total_objects;
	काष्ठा list_head full;
#पूर्ण_अगर
#पूर्ण_अगर

पूर्ण;

अटल अंतरभूत काष्ठा kmem_cache_node *get_node(काष्ठा kmem_cache *s, पूर्णांक node)
अणु
	वापस s->node[node];
पूर्ण

/*
 * Iterator over all nodes. The body will be executed क्रम each node that has
 * a kmem_cache_node काष्ठाure allocated (which is true क्रम all online nodes)
 */
#घोषणा क्रम_each_kmem_cache_node(__s, __node, __n) \
	क्रम (__node = 0; __node < nr_node_ids; __node++) \
		 अगर ((__n = get_node(__s, __node)))

#पूर्ण_अगर

व्योम *slab_start(काष्ठा seq_file *m, loff_t *pos);
व्योम *slab_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos);
व्योम slab_stop(काष्ठा seq_file *m, व्योम *p);
पूर्णांक memcg_slab_show(काष्ठा seq_file *m, व्योम *p);

#अगर defined(CONFIG_SLAB) || defined(CONFIG_SLUB_DEBUG)
व्योम dump_unreclaimable_slab(व्योम);
#अन्यथा
अटल अंतरभूत व्योम dump_unreclaimable_slab(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

व्योम ___cache_मुक्त(काष्ठा kmem_cache *cache, व्योम *x, अचिन्हित दीर्घ addr);

#अगर_घोषित CONFIG_SLAB_FREELIST_RANDOM
पूर्णांक cache_अक्रमom_seq_create(काष्ठा kmem_cache *cachep, अचिन्हित पूर्णांक count,
			gfp_t gfp);
व्योम cache_अक्रमom_seq_destroy(काष्ठा kmem_cache *cachep);
#अन्यथा
अटल अंतरभूत पूर्णांक cache_अक्रमom_seq_create(काष्ठा kmem_cache *cachep,
					अचिन्हित पूर्णांक count, gfp_t gfp)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम cache_अक्रमom_seq_destroy(काष्ठा kmem_cache *cachep) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SLAB_FREELIST_RANDOM */

अटल अंतरभूत bool slab_want_init_on_alloc(gfp_t flags, काष्ठा kmem_cache *c)
अणु
	अगर (अटल_branch_maybe(CONFIG_INIT_ON_ALLOC_DEFAULT_ON,
				&init_on_alloc)) अणु
		अगर (c->ctor)
			वापस false;
		अगर (c->flags & (SLAB_TYPESAFE_BY_RCU | SLAB_POISON))
			वापस flags & __GFP_ZERO;
		वापस true;
	पूर्ण
	वापस flags & __GFP_ZERO;
पूर्ण

अटल अंतरभूत bool slab_want_init_on_मुक्त(काष्ठा kmem_cache *c)
अणु
	अगर (अटल_branch_maybe(CONFIG_INIT_ON_FREE_DEFAULT_ON,
				&init_on_मुक्त))
		वापस !(c->ctor ||
			 (c->flags & (SLAB_TYPESAFE_BY_RCU | SLAB_POISON)));
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_PRINTK
#घोषणा KS_ADDRS_COUNT 16
काष्ठा kmem_obj_info अणु
	व्योम *kp_ptr;
	काष्ठा page *kp_page;
	व्योम *kp_objp;
	अचिन्हित दीर्घ kp_data_offset;
	काष्ठा kmem_cache *kp_slab_cache;
	व्योम *kp_ret;
	व्योम *kp_stack[KS_ADDRS_COUNT];
पूर्ण;
व्योम kmem_obj_info(काष्ठा kmem_obj_info *kpp, व्योम *object, काष्ठा page *page);
#पूर्ण_अगर

#पूर्ण_अगर /* MM_SLAB_H */
