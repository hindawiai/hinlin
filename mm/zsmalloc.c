<शैली गुरु>
/*
 * zsदो_स्मृति memory allocator
 *
 * Copyright (C) 2011  Nitin Gupta
 * Copyright (C) 2012, 2013 Minchan Kim
 *
 * This code is released using a dual license strategy: BSD/GPL
 * You can choose the license that better fits your requirements.
 *
 * Released under the terms of 3-clause BSD License
 * Released under the terms of GNU General Public License Version 2.0
 */

/*
 * Following is how we use various fields and flags of underlying
 * काष्ठा page(s) to क्रमm a zspage.
 *
 * Usage of काष्ठा page fields:
 *	page->निजी: poपूर्णांकs to zspage
 *	page->मुक्तlist(index): links together all component pages of a zspage
 *		For the huge page, this is always 0, so we use this field
 *		to store handle.
 *	page->units: first object offset in a subpage of zspage
 *
 * Usage of काष्ठा page flags:
 *	PG_निजी: identअगरies the first component page
 *	PG_owner_priv_1: identअगरies the huge component page
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/magic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/preempt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/shrinker.h>
#समावेश <linux/types.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/zsदो_स्मृति.h>
#समावेश <linux/zpool.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/migrate.h>
#समावेश <linux/रुको.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/fs.h>

#घोषणा ZSPAGE_MAGIC	0x58

/*
 * This must be घातer of 2 and greater than or equal to माप(link_मुक्त).
 * These two conditions ensure that any 'struct link_free' itself doesn't
 * span more than 1 page which aव्योमs complex हाल of mapping 2 pages simply
 * to restore link_मुक्त poपूर्णांकer values.
 */
#घोषणा ZS_ALIGN		8

/*
 * A single 'zspage' is composed of up to 2^N discontiguous 0-order (single)
 * pages. ZS_MAX_ZSPAGE_ORDER defines upper limit on N.
 */
#घोषणा ZS_MAX_ZSPAGE_ORDER 2
#घोषणा ZS_MAX_PAGES_PER_ZSPAGE (_AC(1, UL) << ZS_MAX_ZSPAGE_ORDER)

#घोषणा ZS_HANDLE_SIZE (माप(अचिन्हित दीर्घ))

/*
 * Object location (<PFN>, <obj_idx>) is encoded as
 * a single (अचिन्हित दीर्घ) handle value.
 *
 * Note that object index <obj_idx> starts from 0.
 *
 * This is made more complicated by various memory models and PAE.
 */

#अगर_अघोषित MAX_POSSIBLE_PHYSMEM_BITS
#अगर_घोषित MAX_PHYSMEM_BITS
#घोषणा MAX_POSSIBLE_PHYSMEM_BITS MAX_PHYSMEM_BITS
#अन्यथा
/*
 * If this definition of MAX_PHYSMEM_BITS is used, OBJ_INDEX_BITS will just
 * be PAGE_SHIFT
 */
#घोषणा MAX_POSSIBLE_PHYSMEM_BITS BITS_PER_LONG
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा _PFN_BITS		(MAX_POSSIBLE_PHYSMEM_BITS - PAGE_SHIFT)

/*
 * Memory क्रम allocating क्रम handle keeps object position by
 * encoding <page, obj_idx> and the encoded value has a room
 * in least bit(ie, look at obj_to_location).
 * We use the bit to synchronize between object access by
 * user and migration.
 */
#घोषणा HANDLE_PIN_BIT	0

/*
 * Head in allocated object should have OBJ_ALLOCATED_TAG
 * to identअगरy the object was allocated or not.
 * It's okay to add the status bit in the least bit because
 * header keeps handle which is 4byte-aligned address so we
 * have room क्रम two bit at least.
 */
#घोषणा OBJ_ALLOCATED_TAG 1
#घोषणा OBJ_TAG_BITS 1
#घोषणा OBJ_INDEX_BITS	(BITS_PER_LONG - _PFN_BITS - OBJ_TAG_BITS)
#घोषणा OBJ_INDEX_MASK	((_AC(1, UL) << OBJ_INDEX_BITS) - 1)

#घोषणा FULLNESS_BITS	2
#घोषणा CLASS_BITS	8
#घोषणा ISOLATED_BITS	3
#घोषणा MAGIC_VAL_BITS	8

#घोषणा MAX(a, b) ((a) >= (b) ? (a) : (b))
/* ZS_MIN_ALLOC_SIZE must be multiple of ZS_ALIGN */
#घोषणा ZS_MIN_ALLOC_SIZE \
	MAX(32, (ZS_MAX_PAGES_PER_ZSPAGE << PAGE_SHIFT >> OBJ_INDEX_BITS))
/* each chunk includes extra space to keep handle */
#घोषणा ZS_MAX_ALLOC_SIZE	PAGE_SIZE

/*
 * On प्रणालीs with 4K page size, this gives 255 size classes! There is a
 * trader-off here:
 *  - Large number of size classes is potentially wasteful as मुक्त page are
 *    spपढ़ो across these classes
 *  - Small number of size classes causes large पूर्णांकernal fragmentation
 *  - Probably its better to use specअगरic size classes (empirically
 *    determined). NOTE: all those class sizes must be set as multiple of
 *    ZS_ALIGN to make sure link_मुक्त itself never has to span 2 pages.
 *
 *  ZS_MIN_ALLOC_SIZE and ZS_SIZE_CLASS_DELTA must be multiple of ZS_ALIGN
 *  (reason above)
 */
#घोषणा ZS_SIZE_CLASS_DELTA	(PAGE_SIZE >> CLASS_BITS)
#घोषणा ZS_SIZE_CLASSES	(DIV_ROUND_UP(ZS_MAX_ALLOC_SIZE - ZS_MIN_ALLOC_SIZE, \
				      ZS_SIZE_CLASS_DELTA) + 1)

क्रमागत fullness_group अणु
	ZS_EMPTY,
	ZS_ALMOST_EMPTY,
	ZS_ALMOST_FULL,
	ZS_FULL,
	NR_ZS_FULLNESS,
पूर्ण;

क्रमागत zs_stat_type अणु
	CLASS_EMPTY,
	CLASS_ALMOST_EMPTY,
	CLASS_ALMOST_FULL,
	CLASS_FULL,
	OBJ_ALLOCATED,
	OBJ_USED,
	NR_ZS_STAT_TYPE,
पूर्ण;

काष्ठा zs_size_stat अणु
	अचिन्हित दीर्घ objs[NR_ZS_STAT_TYPE];
पूर्ण;

#अगर_घोषित CONFIG_ZSMALLOC_STAT
अटल काष्ठा dentry *zs_stat_root;
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPACTION
अटल काष्ठा vfsmount *zsदो_स्मृति_mnt;
#पूर्ण_अगर

/*
 * We assign a page to ZS_ALMOST_EMPTY fullness group when:
 *	n <= N / f, where
 * n = number of allocated objects
 * N = total number of objects zspage can store
 * f = fullness_threshold_frac
 *
 * Similarly, we assign zspage to:
 *	ZS_ALMOST_FULL	when n > N / f
 *	ZS_EMPTY	when n == 0
 *	ZS_FULL		when n == N
 *
 * (see: fix_fullness_group())
 */
अटल स्थिर पूर्णांक fullness_threshold_frac = 4;
अटल माप_प्रकार huge_class_size;

काष्ठा size_class अणु
	spinlock_t lock;
	काष्ठा list_head fullness_list[NR_ZS_FULLNESS];
	/*
	 * Size of objects stored in this class. Must be multiple
	 * of ZS_ALIGN.
	 */
	पूर्णांक size;
	पूर्णांक objs_per_zspage;
	/* Number of PAGE_SIZE sized pages to combine to क्रमm a 'zspage' */
	पूर्णांक pages_per_zspage;

	अचिन्हित पूर्णांक index;
	काष्ठा zs_size_stat stats;
पूर्ण;

/* huge object: pages_per_zspage == 1 && maxobj_per_zspage == 1 */
अटल व्योम SetPageHugeObject(काष्ठा page *page)
अणु
	SetPageOwnerPriv1(page);
पूर्ण

अटल व्योम ClearPageHugeObject(काष्ठा page *page)
अणु
	ClearPageOwnerPriv1(page);
पूर्ण

अटल पूर्णांक PageHugeObject(काष्ठा page *page)
अणु
	वापस PageOwnerPriv1(page);
पूर्ण

/*
 * Placed within मुक्त objects to क्रमm a singly linked list.
 * For every zspage, zspage->मुक्तobj gives head of this list.
 *
 * This must be घातer of 2 and less than or equal to ZS_ALIGN
 */
काष्ठा link_मुक्त अणु
	जोड़ अणु
		/*
		 * Free object index;
		 * It's valid क्रम non-allocated object
		 */
		अचिन्हित दीर्घ next;
		/*
		 * Handle of allocated object.
		 */
		अचिन्हित दीर्घ handle;
	पूर्ण;
पूर्ण;

काष्ठा zs_pool अणु
	स्थिर अक्षर *name;

	काष्ठा size_class *size_class[ZS_SIZE_CLASSES];
	काष्ठा kmem_cache *handle_cachep;
	काष्ठा kmem_cache *zspage_cachep;

	atomic_दीर्घ_t pages_allocated;

	काष्ठा zs_pool_stats stats;

	/* Compact classes */
	काष्ठा shrinker shrinker;

#अगर_घोषित CONFIG_ZSMALLOC_STAT
	काष्ठा dentry *stat_dentry;
#पूर्ण_अगर
#अगर_घोषित CONFIG_COMPACTION
	काष्ठा inode *inode;
	काष्ठा work_काष्ठा मुक्त_work;
	/* A रुको queue क्रम when migration races with async_मुक्त_zspage() */
	काष्ठा रुको_queue_head migration_रुको;
	atomic_दीर्घ_t isolated_pages;
	bool destroying;
#पूर्ण_अगर
पूर्ण;

काष्ठा zspage अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक fullness:FULLNESS_BITS;
		अचिन्हित पूर्णांक class:CLASS_BITS + 1;
		अचिन्हित पूर्णांक isolated:ISOLATED_BITS;
		अचिन्हित पूर्णांक magic:MAGIC_VAL_BITS;
	पूर्ण;
	अचिन्हित पूर्णांक inuse;
	अचिन्हित पूर्णांक मुक्तobj;
	काष्ठा page *first_page;
	काष्ठा list_head list; /* fullness list */
#अगर_घोषित CONFIG_COMPACTION
	rwlock_t lock;
#पूर्ण_अगर
पूर्ण;

काष्ठा mapping_area अणु
	अक्षर *vm_buf; /* copy buffer क्रम objects that span pages */
	अक्षर *vm_addr; /* address of kmap_atomic()'ed pages */
	क्रमागत zs_mapmode vm_mm; /* mapping mode */
पूर्ण;

#अगर_घोषित CONFIG_COMPACTION
अटल पूर्णांक zs_रेजिस्टर_migration(काष्ठा zs_pool *pool);
अटल व्योम zs_unरेजिस्टर_migration(काष्ठा zs_pool *pool);
अटल व्योम migrate_lock_init(काष्ठा zspage *zspage);
अटल व्योम migrate_पढ़ो_lock(काष्ठा zspage *zspage);
अटल व्योम migrate_पढ़ो_unlock(काष्ठा zspage *zspage);
अटल व्योम kick_deferred_मुक्त(काष्ठा zs_pool *pool);
अटल व्योम init_deferred_मुक्त(काष्ठा zs_pool *pool);
अटल व्योम SetZsPageMovable(काष्ठा zs_pool *pool, काष्ठा zspage *zspage);
#अन्यथा
अटल पूर्णांक zsदो_स्मृति_mount(व्योम) अणु वापस 0; पूर्ण
अटल व्योम zsदो_स्मृति_unmount(व्योम) अणुपूर्ण
अटल पूर्णांक zs_रेजिस्टर_migration(काष्ठा zs_pool *pool) अणु वापस 0; पूर्ण
अटल व्योम zs_unरेजिस्टर_migration(काष्ठा zs_pool *pool) अणुपूर्ण
अटल व्योम migrate_lock_init(काष्ठा zspage *zspage) अणुपूर्ण
अटल व्योम migrate_पढ़ो_lock(काष्ठा zspage *zspage) अणुपूर्ण
अटल व्योम migrate_पढ़ो_unlock(काष्ठा zspage *zspage) अणुपूर्ण
अटल व्योम kick_deferred_मुक्त(काष्ठा zs_pool *pool) अणुपूर्ण
अटल व्योम init_deferred_मुक्त(काष्ठा zs_pool *pool) अणुपूर्ण
अटल व्योम SetZsPageMovable(काष्ठा zs_pool *pool, काष्ठा zspage *zspage) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक create_cache(काष्ठा zs_pool *pool)
अणु
	pool->handle_cachep = kmem_cache_create("zs_handle", ZS_HANDLE_SIZE,
					0, 0, शून्य);
	अगर (!pool->handle_cachep)
		वापस 1;

	pool->zspage_cachep = kmem_cache_create("zspage", माप(काष्ठा zspage),
					0, 0, शून्य);
	अगर (!pool->zspage_cachep) अणु
		kmem_cache_destroy(pool->handle_cachep);
		pool->handle_cachep = शून्य;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम destroy_cache(काष्ठा zs_pool *pool)
अणु
	kmem_cache_destroy(pool->handle_cachep);
	kmem_cache_destroy(pool->zspage_cachep);
पूर्ण

अटल अचिन्हित दीर्घ cache_alloc_handle(काष्ठा zs_pool *pool, gfp_t gfp)
अणु
	वापस (अचिन्हित दीर्घ)kmem_cache_alloc(pool->handle_cachep,
			gfp & ~(__GFP_HIGHMEM|__GFP_MOVABLE));
पूर्ण

अटल व्योम cache_मुक्त_handle(काष्ठा zs_pool *pool, अचिन्हित दीर्घ handle)
अणु
	kmem_cache_मुक्त(pool->handle_cachep, (व्योम *)handle);
पूर्ण

अटल काष्ठा zspage *cache_alloc_zspage(काष्ठा zs_pool *pool, gfp_t flags)
अणु
	वापस kmem_cache_zalloc(pool->zspage_cachep,
			flags & ~(__GFP_HIGHMEM|__GFP_MOVABLE));
पूर्ण

अटल व्योम cache_मुक्त_zspage(काष्ठा zs_pool *pool, काष्ठा zspage *zspage)
अणु
	kmem_cache_मुक्त(pool->zspage_cachep, zspage);
पूर्ण

अटल व्योम record_obj(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ obj)
अणु
	/*
	 * lsb of @obj represents handle lock जबतक other bits
	 * represent object value the handle is poपूर्णांकing so
	 * updating shouldn't करो store tearing.
	 */
	WRITE_ONCE(*(अचिन्हित दीर्घ *)handle, obj);
पूर्ण

/* zpool driver */

#अगर_घोषित CONFIG_ZPOOL

अटल व्योम *zs_zpool_create(स्थिर अक्षर *name, gfp_t gfp,
			     स्थिर काष्ठा zpool_ops *zpool_ops,
			     काष्ठा zpool *zpool)
अणु
	/*
	 * Ignore global gfp flags: zs_दो_स्मृति() may be invoked from
	 * dअगरferent contexts and its caller must provide a valid
	 * gfp mask.
	 */
	वापस zs_create_pool(name);
पूर्ण

अटल व्योम zs_zpool_destroy(व्योम *pool)
अणु
	zs_destroy_pool(pool);
पूर्ण

अटल पूर्णांक zs_zpool_दो_स्मृति(व्योम *pool, माप_प्रकार size, gfp_t gfp,
			अचिन्हित दीर्घ *handle)
अणु
	*handle = zs_दो_स्मृति(pool, size, gfp);
	वापस *handle ? 0 : -1;
पूर्ण
अटल व्योम zs_zpool_मुक्त(व्योम *pool, अचिन्हित दीर्घ handle)
अणु
	zs_मुक्त(pool, handle);
पूर्ण

अटल व्योम *zs_zpool_map(व्योम *pool, अचिन्हित दीर्घ handle,
			क्रमागत zpool_mapmode mm)
अणु
	क्रमागत zs_mapmode zs_mm;

	चयन (mm) अणु
	हाल ZPOOL_MM_RO:
		zs_mm = ZS_MM_RO;
		अवरोध;
	हाल ZPOOL_MM_WO:
		zs_mm = ZS_MM_WO;
		अवरोध;
	हाल ZPOOL_MM_RW:
	शेष:
		zs_mm = ZS_MM_RW;
		अवरोध;
	पूर्ण

	वापस zs_map_object(pool, handle, zs_mm);
पूर्ण
अटल व्योम zs_zpool_unmap(व्योम *pool, अचिन्हित दीर्घ handle)
अणु
	zs_unmap_object(pool, handle);
पूर्ण

अटल u64 zs_zpool_total_size(व्योम *pool)
अणु
	वापस zs_get_total_pages(pool) << PAGE_SHIFT;
पूर्ण

अटल काष्ठा zpool_driver zs_zpool_driver = अणु
	.type =			  "zsmalloc",
	.owner =		  THIS_MODULE,
	.create =		  zs_zpool_create,
	.destroy =		  zs_zpool_destroy,
	.दो_स्मृति_support_movable = true,
	.दो_स्मृति =		  zs_zpool_दो_स्मृति,
	.मुक्त =			  zs_zpool_मुक्त,
	.map =			  zs_zpool_map,
	.unmap =		  zs_zpool_unmap,
	.total_size =		  zs_zpool_total_size,
पूर्ण;

MODULE_ALIAS("zpool-zsmalloc");
#पूर्ण_अगर /* CONFIG_ZPOOL */

/* per-cpu VM mapping areas क्रम zspage accesses that cross page boundaries */
अटल DEFINE_PER_CPU(काष्ठा mapping_area, zs_map_area);

अटल bool is_zspage_isolated(काष्ठा zspage *zspage)
अणु
	वापस zspage->isolated;
पूर्ण

अटल __maybe_unused पूर्णांक is_first_page(काष्ठा page *page)
अणु
	वापस PagePrivate(page);
पूर्ण

/* Protected by class->lock */
अटल अंतरभूत पूर्णांक get_zspage_inuse(काष्ठा zspage *zspage)
अणु
	वापस zspage->inuse;
पूर्ण


अटल अंतरभूत व्योम mod_zspage_inuse(काष्ठा zspage *zspage, पूर्णांक val)
अणु
	zspage->inuse += val;
पूर्ण

अटल अंतरभूत काष्ठा page *get_first_page(काष्ठा zspage *zspage)
अणु
	काष्ठा page *first_page = zspage->first_page;

	VM_BUG_ON_PAGE(!is_first_page(first_page), first_page);
	वापस first_page;
पूर्ण

अटल अंतरभूत पूर्णांक get_first_obj_offset(काष्ठा page *page)
अणु
	वापस page->units;
पूर्ण

अटल अंतरभूत व्योम set_first_obj_offset(काष्ठा page *page, पूर्णांक offset)
अणु
	page->units = offset;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_मुक्तobj(काष्ठा zspage *zspage)
अणु
	वापस zspage->मुक्तobj;
पूर्ण

अटल अंतरभूत व्योम set_मुक्तobj(काष्ठा zspage *zspage, अचिन्हित पूर्णांक obj)
अणु
	zspage->मुक्तobj = obj;
पूर्ण

अटल व्योम get_zspage_mapping(काष्ठा zspage *zspage,
				अचिन्हित पूर्णांक *class_idx,
				क्रमागत fullness_group *fullness)
अणु
	BUG_ON(zspage->magic != ZSPAGE_MAGIC);

	*fullness = zspage->fullness;
	*class_idx = zspage->class;
पूर्ण

अटल व्योम set_zspage_mapping(काष्ठा zspage *zspage,
				अचिन्हित पूर्णांक class_idx,
				क्रमागत fullness_group fullness)
अणु
	zspage->class = class_idx;
	zspage->fullness = fullness;
पूर्ण

/*
 * zsदो_स्मृति भागides the pool पूर्णांकo various size classes where each
 * class मुख्यtains a list of zspages where each zspage is भागided
 * पूर्णांकo equal sized chunks. Each allocation falls पूर्णांकo one of these
 * classes depending on its size. This function वापसs index of the
 * size class which has chunk size big enough to hold the given size.
 */
अटल पूर्णांक get_size_class_index(पूर्णांक size)
अणु
	पूर्णांक idx = 0;

	अगर (likely(size > ZS_MIN_ALLOC_SIZE))
		idx = DIV_ROUND_UP(size - ZS_MIN_ALLOC_SIZE,
				ZS_SIZE_CLASS_DELTA);

	वापस min_t(पूर्णांक, ZS_SIZE_CLASSES - 1, idx);
पूर्ण

/* type can be of क्रमागत type zs_stat_type or fullness_group */
अटल अंतरभूत व्योम zs_stat_inc(काष्ठा size_class *class,
				पूर्णांक type, अचिन्हित दीर्घ cnt)
अणु
	class->stats.objs[type] += cnt;
पूर्ण

/* type can be of क्रमागत type zs_stat_type or fullness_group */
अटल अंतरभूत व्योम zs_stat_dec(काष्ठा size_class *class,
				पूर्णांक type, अचिन्हित दीर्घ cnt)
अणु
	class->stats.objs[type] -= cnt;
पूर्ण

/* type can be of क्रमागत type zs_stat_type or fullness_group */
अटल अंतरभूत अचिन्हित दीर्घ zs_stat_get(काष्ठा size_class *class,
				पूर्णांक type)
अणु
	वापस class->stats.objs[type];
पूर्ण

#अगर_घोषित CONFIG_ZSMALLOC_STAT

अटल व्योम __init zs_stat_init(व्योम)
अणु
	अगर (!debugfs_initialized()) अणु
		pr_warn("debugfs not available, stat dir not created\n");
		वापस;
	पूर्ण

	zs_stat_root = debugfs_create_dir("zsmalloc", शून्य);
पूर्ण

अटल व्योम __निकास zs_stat_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(zs_stat_root);
पूर्ण

अटल अचिन्हित दीर्घ zs_can_compact(काष्ठा size_class *class);

अटल पूर्णांक zs_stats_size_show(काष्ठा seq_file *s, व्योम *v)
अणु
	पूर्णांक i;
	काष्ठा zs_pool *pool = s->निजी;
	काष्ठा size_class *class;
	पूर्णांक objs_per_zspage;
	अचिन्हित दीर्घ class_almost_full, class_almost_empty;
	अचिन्हित दीर्घ obj_allocated, obj_used, pages_used, मुक्तable;
	अचिन्हित दीर्घ total_class_almost_full = 0, total_class_almost_empty = 0;
	अचिन्हित दीर्घ total_objs = 0, total_used_objs = 0, total_pages = 0;
	अचिन्हित दीर्घ total_मुक्तable = 0;

	seq_म_लिखो(s, " %5s %5s %11s %12s %13s %10s %10s %16s %8s\n",
			"class", "size", "almost_full", "almost_empty",
			"obj_allocated", "obj_used", "pages_used",
			"pages_per_zspage", "freeable");

	क्रम (i = 0; i < ZS_SIZE_CLASSES; i++) अणु
		class = pool->size_class[i];

		अगर (class->index != i)
			जारी;

		spin_lock(&class->lock);
		class_almost_full = zs_stat_get(class, CLASS_ALMOST_FULL);
		class_almost_empty = zs_stat_get(class, CLASS_ALMOST_EMPTY);
		obj_allocated = zs_stat_get(class, OBJ_ALLOCATED);
		obj_used = zs_stat_get(class, OBJ_USED);
		मुक्तable = zs_can_compact(class);
		spin_unlock(&class->lock);

		objs_per_zspage = class->objs_per_zspage;
		pages_used = obj_allocated / objs_per_zspage *
				class->pages_per_zspage;

		seq_म_लिखो(s, " %5u %5u %11lu %12lu %13lu"
				" %10lu %10lu %16d %8lu\n",
			i, class->size, class_almost_full, class_almost_empty,
			obj_allocated, obj_used, pages_used,
			class->pages_per_zspage, मुक्तable);

		total_class_almost_full += class_almost_full;
		total_class_almost_empty += class_almost_empty;
		total_objs += obj_allocated;
		total_used_objs += obj_used;
		total_pages += pages_used;
		total_मुक्तable += मुक्तable;
	पूर्ण

	seq_माला_दो(s, "\n");
	seq_म_लिखो(s, " %5s %5s %11lu %12lu %13lu %10lu %10lu %16s %8lu\n",
			"Total", "", total_class_almost_full,
			total_class_almost_empty, total_objs,
			total_used_objs, total_pages, "", total_मुक्तable);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(zs_stats_size);

अटल व्योम zs_pool_stat_create(काष्ठा zs_pool *pool, स्थिर अक्षर *name)
अणु
	अगर (!zs_stat_root) अणु
		pr_warn("no root stat dir, not creating <%s> stat dir\n", name);
		वापस;
	पूर्ण

	pool->stat_dentry = debugfs_create_dir(name, zs_stat_root);

	debugfs_create_file("classes", S_IFREG | 0444, pool->stat_dentry, pool,
			    &zs_stats_size_fops);
पूर्ण

अटल व्योम zs_pool_stat_destroy(काष्ठा zs_pool *pool)
अणु
	debugfs_हटाओ_recursive(pool->stat_dentry);
पूर्ण

#अन्यथा /* CONFIG_ZSMALLOC_STAT */
अटल व्योम __init zs_stat_init(व्योम)
अणु
पूर्ण

अटल व्योम __निकास zs_stat_निकास(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम zs_pool_stat_create(काष्ठा zs_pool *pool, स्थिर अक्षर *name)
अणु
पूर्ण

अटल अंतरभूत व्योम zs_pool_stat_destroy(काष्ठा zs_pool *pool)
अणु
पूर्ण
#पूर्ण_अगर


/*
 * For each size class, zspages are भागided पूर्णांकo dअगरferent groups
 * depending on how "full" they are. This was करोne so that we could
 * easily find empty or nearly empty zspages when we try to shrink
 * the pool (not yet implemented). This function वापसs fullness
 * status of the given page.
 */
अटल क्रमागत fullness_group get_fullness_group(काष्ठा size_class *class,
						काष्ठा zspage *zspage)
अणु
	पूर्णांक inuse, objs_per_zspage;
	क्रमागत fullness_group fg;

	inuse = get_zspage_inuse(zspage);
	objs_per_zspage = class->objs_per_zspage;

	अगर (inuse == 0)
		fg = ZS_EMPTY;
	अन्यथा अगर (inuse == objs_per_zspage)
		fg = ZS_FULL;
	अन्यथा अगर (inuse <= 3 * objs_per_zspage / fullness_threshold_frac)
		fg = ZS_ALMOST_EMPTY;
	अन्यथा
		fg = ZS_ALMOST_FULL;

	वापस fg;
पूर्ण

/*
 * Each size class मुख्यtains various मुक्तlists and zspages are asचिन्हित
 * to one of these मुक्तlists based on the number of live objects they
 * have. This functions inserts the given zspage पूर्णांकo the मुक्तlist
 * identअगरied by <class, fullness_group>.
 */
अटल व्योम insert_zspage(काष्ठा size_class *class,
				काष्ठा zspage *zspage,
				क्रमागत fullness_group fullness)
अणु
	काष्ठा zspage *head;

	zs_stat_inc(class, fullness, 1);
	head = list_first_entry_or_null(&class->fullness_list[fullness],
					काष्ठा zspage, list);
	/*
	 * We want to see more ZS_FULL pages and less almost empty/full.
	 * Put pages with higher ->inuse first.
	 */
	अगर (head && get_zspage_inuse(zspage) < get_zspage_inuse(head))
		list_add(&zspage->list, &head->list);
	अन्यथा
		list_add(&zspage->list, &class->fullness_list[fullness]);
पूर्ण

/*
 * This function हटाओs the given zspage from the मुक्तlist identअगरied
 * by <class, fullness_group>.
 */
अटल व्योम हटाओ_zspage(काष्ठा size_class *class,
				काष्ठा zspage *zspage,
				क्रमागत fullness_group fullness)
अणु
	VM_BUG_ON(list_empty(&class->fullness_list[fullness]));
	VM_BUG_ON(is_zspage_isolated(zspage));

	list_del_init(&zspage->list);
	zs_stat_dec(class, fullness, 1);
पूर्ण

/*
 * Each size class मुख्यtains zspages in dअगरferent fullness groups depending
 * on the number of live objects they contain. When allocating or मुक्तing
 * objects, the fullness status of the page can change, say, from ALMOST_FULL
 * to ALMOST_EMPTY when मुक्तing an object. This function checks अगर such
 * a status change has occurred क्रम the given page and accordingly moves the
 * page from the मुक्तlist of the old fullness group to that of the new
 * fullness group.
 */
अटल क्रमागत fullness_group fix_fullness_group(काष्ठा size_class *class,
						काष्ठा zspage *zspage)
अणु
	पूर्णांक class_idx;
	क्रमागत fullness_group currfg, newfg;

	get_zspage_mapping(zspage, &class_idx, &currfg);
	newfg = get_fullness_group(class, zspage);
	अगर (newfg == currfg)
		जाओ out;

	अगर (!is_zspage_isolated(zspage)) अणु
		हटाओ_zspage(class, zspage, currfg);
		insert_zspage(class, zspage, newfg);
	पूर्ण

	set_zspage_mapping(zspage, class_idx, newfg);

out:
	वापस newfg;
पूर्ण

/*
 * We have to decide on how many pages to link together
 * to क्रमm a zspage क्रम each size class. This is important
 * to reduce wastage due to unusable space left at end of
 * each zspage which is given as:
 *     wastage = Zp % class_size
 *     usage = Zp - wastage
 * where Zp = zspage size = k * PAGE_SIZE where k = 1, 2, ...
 *
 * For example, क्रम size class of 3/8 * PAGE_SIZE, we should
 * link together 3 PAGE_SIZE sized pages to क्रमm a zspage
 * since then we can perfectly fit in 8 such objects.
 */
अटल पूर्णांक get_pages_per_zspage(पूर्णांक class_size)
अणु
	पूर्णांक i, max_usedpc = 0;
	/* zspage order which gives maximum used size per KB */
	पूर्णांक max_usedpc_order = 1;

	क्रम (i = 1; i <= ZS_MAX_PAGES_PER_ZSPAGE; i++) अणु
		पूर्णांक zspage_size;
		पूर्णांक waste, usedpc;

		zspage_size = i * PAGE_SIZE;
		waste = zspage_size % class_size;
		usedpc = (zspage_size - waste) * 100 / zspage_size;

		अगर (usedpc > max_usedpc) अणु
			max_usedpc = usedpc;
			max_usedpc_order = i;
		पूर्ण
	पूर्ण

	वापस max_usedpc_order;
पूर्ण

अटल काष्ठा zspage *get_zspage(काष्ठा page *page)
अणु
	काष्ठा zspage *zspage = (काष्ठा zspage *)page_निजी(page);

	BUG_ON(zspage->magic != ZSPAGE_MAGIC);
	वापस zspage;
पूर्ण

अटल काष्ठा page *get_next_page(काष्ठा page *page)
अणु
	अगर (unlikely(PageHugeObject(page)))
		वापस शून्य;

	वापस page->मुक्तlist;
पूर्ण

/**
 * obj_to_location - get (<page>, <obj_idx>) from encoded object value
 * @obj: the encoded object value
 * @page: page object resides in zspage
 * @obj_idx: object index
 */
अटल व्योम obj_to_location(अचिन्हित दीर्घ obj, काष्ठा page **page,
				अचिन्हित पूर्णांक *obj_idx)
अणु
	obj >>= OBJ_TAG_BITS;
	*page = pfn_to_page(obj >> OBJ_INDEX_BITS);
	*obj_idx = (obj & OBJ_INDEX_MASK);
पूर्ण

/**
 * location_to_obj - get obj value encoded from (<page>, <obj_idx>)
 * @page: page object resides in zspage
 * @obj_idx: object index
 */
अटल अचिन्हित दीर्घ location_to_obj(काष्ठा page *page, अचिन्हित पूर्णांक obj_idx)
अणु
	अचिन्हित दीर्घ obj;

	obj = page_to_pfn(page) << OBJ_INDEX_BITS;
	obj |= obj_idx & OBJ_INDEX_MASK;
	obj <<= OBJ_TAG_BITS;

	वापस obj;
पूर्ण

अटल अचिन्हित दीर्घ handle_to_obj(अचिन्हित दीर्घ handle)
अणु
	वापस *(अचिन्हित दीर्घ *)handle;
पूर्ण

अटल अचिन्हित दीर्घ obj_to_head(काष्ठा page *page, व्योम *obj)
अणु
	अगर (unlikely(PageHugeObject(page))) अणु
		VM_BUG_ON_PAGE(!is_first_page(page), page);
		वापस page->index;
	पूर्ण अन्यथा
		वापस *(अचिन्हित दीर्घ *)obj;
पूर्ण

अटल अंतरभूत पूर्णांक testpin_tag(अचिन्हित दीर्घ handle)
अणु
	वापस bit_spin_is_locked(HANDLE_PIN_BIT, (अचिन्हित दीर्घ *)handle);
पूर्ण

अटल अंतरभूत पूर्णांक trypin_tag(अचिन्हित दीर्घ handle)
अणु
	वापस bit_spin_trylock(HANDLE_PIN_BIT, (अचिन्हित दीर्घ *)handle);
पूर्ण

अटल व्योम pin_tag(अचिन्हित दीर्घ handle) __acquires(bitlock)
अणु
	bit_spin_lock(HANDLE_PIN_BIT, (अचिन्हित दीर्घ *)handle);
पूर्ण

अटल व्योम unpin_tag(अचिन्हित दीर्घ handle) __releases(bitlock)
अणु
	bit_spin_unlock(HANDLE_PIN_BIT, (अचिन्हित दीर्घ *)handle);
पूर्ण

अटल व्योम reset_page(काष्ठा page *page)
अणु
	__ClearPageMovable(page);
	ClearPagePrivate(page);
	set_page_निजी(page, 0);
	page_mapcount_reset(page);
	ClearPageHugeObject(page);
	page->मुक्तlist = शून्य;
पूर्ण

अटल पूर्णांक trylock_zspage(काष्ठा zspage *zspage)
अणु
	काष्ठा page *cursor, *fail;

	क्रम (cursor = get_first_page(zspage); cursor != शून्य; cursor =
					get_next_page(cursor)) अणु
		अगर (!trylock_page(cursor)) अणु
			fail = cursor;
			जाओ unlock;
		पूर्ण
	पूर्ण

	वापस 1;
unlock:
	क्रम (cursor = get_first_page(zspage); cursor != fail; cursor =
					get_next_page(cursor))
		unlock_page(cursor);

	वापस 0;
पूर्ण

अटल व्योम __मुक्त_zspage(काष्ठा zs_pool *pool, काष्ठा size_class *class,
				काष्ठा zspage *zspage)
अणु
	काष्ठा page *page, *next;
	क्रमागत fullness_group fg;
	अचिन्हित पूर्णांक class_idx;

	get_zspage_mapping(zspage, &class_idx, &fg);

	निश्चित_spin_locked(&class->lock);

	VM_BUG_ON(get_zspage_inuse(zspage));
	VM_BUG_ON(fg != ZS_EMPTY);

	next = page = get_first_page(zspage);
	करो अणु
		VM_BUG_ON_PAGE(!PageLocked(page), page);
		next = get_next_page(page);
		reset_page(page);
		unlock_page(page);
		dec_zone_page_state(page, NR_ZSPAGES);
		put_page(page);
		page = next;
	पूर्ण जबतक (page != शून्य);

	cache_मुक्त_zspage(pool, zspage);

	zs_stat_dec(class, OBJ_ALLOCATED, class->objs_per_zspage);
	atomic_दीर्घ_sub(class->pages_per_zspage,
					&pool->pages_allocated);
पूर्ण

अटल व्योम मुक्त_zspage(काष्ठा zs_pool *pool, काष्ठा size_class *class,
				काष्ठा zspage *zspage)
अणु
	VM_BUG_ON(get_zspage_inuse(zspage));
	VM_BUG_ON(list_empty(&zspage->list));

	अगर (!trylock_zspage(zspage)) अणु
		kick_deferred_मुक्त(pool);
		वापस;
	पूर्ण

	हटाओ_zspage(class, zspage, ZS_EMPTY);
	__मुक्त_zspage(pool, class, zspage);
पूर्ण

/* Initialize a newly allocated zspage */
अटल व्योम init_zspage(काष्ठा size_class *class, काष्ठा zspage *zspage)
अणु
	अचिन्हित पूर्णांक मुक्तobj = 1;
	अचिन्हित दीर्घ off = 0;
	काष्ठा page *page = get_first_page(zspage);

	जबतक (page) अणु
		काष्ठा page *next_page;
		काष्ठा link_मुक्त *link;
		व्योम *vaddr;

		set_first_obj_offset(page, off);

		vaddr = kmap_atomic(page);
		link = (काष्ठा link_मुक्त *)vaddr + off / माप(*link);

		जबतक ((off += class->size) < PAGE_SIZE) अणु
			link->next = मुक्तobj++ << OBJ_TAG_BITS;
			link += class->size / माप(*link);
		पूर्ण

		/*
		 * We now come to the last (full or partial) object on this
		 * page, which must poपूर्णांक to the first object on the next
		 * page (अगर present)
		 */
		next_page = get_next_page(page);
		अगर (next_page) अणु
			link->next = मुक्तobj++ << OBJ_TAG_BITS;
		पूर्ण अन्यथा अणु
			/*
			 * Reset OBJ_TAG_BITS bit to last link to tell
			 * whether it's allocated object or not.
			 */
			link->next = -1UL << OBJ_TAG_BITS;
		पूर्ण
		kunmap_atomic(vaddr);
		page = next_page;
		off %= PAGE_SIZE;
	पूर्ण

	set_मुक्तobj(zspage, 0);
पूर्ण

अटल व्योम create_page_chain(काष्ठा size_class *class, काष्ठा zspage *zspage,
				काष्ठा page *pages[])
अणु
	पूर्णांक i;
	काष्ठा page *page;
	काष्ठा page *prev_page = शून्य;
	पूर्णांक nr_pages = class->pages_per_zspage;

	/*
	 * Allocate inभागidual pages and link them together as:
	 * 1. all pages are linked together using page->मुक्तlist
	 * 2. each sub-page poपूर्णांक to zspage using page->निजी
	 *
	 * we set PG_निजी to identअगरy the first page (i.e. no other sub-page
	 * has this flag set).
	 */
	क्रम (i = 0; i < nr_pages; i++) अणु
		page = pages[i];
		set_page_निजी(page, (अचिन्हित दीर्घ)zspage);
		page->मुक्तlist = शून्य;
		अगर (i == 0) अणु
			zspage->first_page = page;
			SetPagePrivate(page);
			अगर (unlikely(class->objs_per_zspage == 1 &&
					class->pages_per_zspage == 1))
				SetPageHugeObject(page);
		पूर्ण अन्यथा अणु
			prev_page->मुक्तlist = page;
		पूर्ण
		prev_page = page;
	पूर्ण
पूर्ण

/*
 * Allocate a zspage क्रम the given size class
 */
अटल काष्ठा zspage *alloc_zspage(काष्ठा zs_pool *pool,
					काष्ठा size_class *class,
					gfp_t gfp)
अणु
	पूर्णांक i;
	काष्ठा page *pages[ZS_MAX_PAGES_PER_ZSPAGE];
	काष्ठा zspage *zspage = cache_alloc_zspage(pool, gfp);

	अगर (!zspage)
		वापस शून्य;

	zspage->magic = ZSPAGE_MAGIC;
	migrate_lock_init(zspage);

	क्रम (i = 0; i < class->pages_per_zspage; i++) अणु
		काष्ठा page *page;

		page = alloc_page(gfp);
		अगर (!page) अणु
			जबतक (--i >= 0) अणु
				dec_zone_page_state(pages[i], NR_ZSPAGES);
				__मुक्त_page(pages[i]);
			पूर्ण
			cache_मुक्त_zspage(pool, zspage);
			वापस शून्य;
		पूर्ण

		inc_zone_page_state(page, NR_ZSPAGES);
		pages[i] = page;
	पूर्ण

	create_page_chain(class, zspage, pages);
	init_zspage(class, zspage);

	वापस zspage;
पूर्ण

अटल काष्ठा zspage *find_get_zspage(काष्ठा size_class *class)
अणु
	पूर्णांक i;
	काष्ठा zspage *zspage;

	क्रम (i = ZS_ALMOST_FULL; i >= ZS_EMPTY; i--) अणु
		zspage = list_first_entry_or_null(&class->fullness_list[i],
				काष्ठा zspage, list);
		अगर (zspage)
			अवरोध;
	पूर्ण

	वापस zspage;
पूर्ण

अटल अंतरभूत पूर्णांक __zs_cpu_up(काष्ठा mapping_area *area)
अणु
	/*
	 * Make sure we करोn't leak memory अगर a cpu UP notअगरication
	 * and zs_init() race and both call zs_cpu_up() on the same cpu
	 */
	अगर (area->vm_buf)
		वापस 0;
	area->vm_buf = kदो_स्मृति(ZS_MAX_ALLOC_SIZE, GFP_KERNEL);
	अगर (!area->vm_buf)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __zs_cpu_करोwn(काष्ठा mapping_area *area)
अणु
	kमुक्त(area->vm_buf);
	area->vm_buf = शून्य;
पूर्ण

अटल व्योम *__zs_map_object(काष्ठा mapping_area *area,
			काष्ठा page *pages[2], पूर्णांक off, पूर्णांक size)
अणु
	पूर्णांक sizes[2];
	व्योम *addr;
	अक्षर *buf = area->vm_buf;

	/* disable page faults to match kmap_atomic() वापस conditions */
	pagefault_disable();

	/* no पढ़ो fastpath */
	अगर (area->vm_mm == ZS_MM_WO)
		जाओ out;

	sizes[0] = PAGE_SIZE - off;
	sizes[1] = size - sizes[0];

	/* copy object to per-cpu buffer */
	addr = kmap_atomic(pages[0]);
	स_नकल(buf, addr + off, sizes[0]);
	kunmap_atomic(addr);
	addr = kmap_atomic(pages[1]);
	स_नकल(buf + sizes[0], addr, sizes[1]);
	kunmap_atomic(addr);
out:
	वापस area->vm_buf;
पूर्ण

अटल व्योम __zs_unmap_object(काष्ठा mapping_area *area,
			काष्ठा page *pages[2], पूर्णांक off, पूर्णांक size)
अणु
	पूर्णांक sizes[2];
	व्योम *addr;
	अक्षर *buf;

	/* no ग_लिखो fastpath */
	अगर (area->vm_mm == ZS_MM_RO)
		जाओ out;

	buf = area->vm_buf;
	buf = buf + ZS_HANDLE_SIZE;
	size -= ZS_HANDLE_SIZE;
	off += ZS_HANDLE_SIZE;

	sizes[0] = PAGE_SIZE - off;
	sizes[1] = size - sizes[0];

	/* copy per-cpu buffer to object */
	addr = kmap_atomic(pages[0]);
	स_नकल(addr + off, buf, sizes[0]);
	kunmap_atomic(addr);
	addr = kmap_atomic(pages[1]);
	स_नकल(addr, buf + sizes[0], sizes[1]);
	kunmap_atomic(addr);

out:
	/* enable page faults to match kunmap_atomic() वापस conditions */
	pagefault_enable();
पूर्ण

अटल पूर्णांक zs_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा mapping_area *area;

	area = &per_cpu(zs_map_area, cpu);
	वापस __zs_cpu_up(area);
पूर्ण

अटल पूर्णांक zs_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा mapping_area *area;

	area = &per_cpu(zs_map_area, cpu);
	__zs_cpu_करोwn(area);
	वापस 0;
पूर्ण

अटल bool can_merge(काष्ठा size_class *prev, पूर्णांक pages_per_zspage,
					पूर्णांक objs_per_zspage)
अणु
	अगर (prev->pages_per_zspage == pages_per_zspage &&
		prev->objs_per_zspage == objs_per_zspage)
		वापस true;

	वापस false;
पूर्ण

अटल bool zspage_full(काष्ठा size_class *class, काष्ठा zspage *zspage)
अणु
	वापस get_zspage_inuse(zspage) == class->objs_per_zspage;
पूर्ण

अचिन्हित दीर्घ zs_get_total_pages(काष्ठा zs_pool *pool)
अणु
	वापस atomic_दीर्घ_पढ़ो(&pool->pages_allocated);
पूर्ण
EXPORT_SYMBOL_GPL(zs_get_total_pages);

/**
 * zs_map_object - get address of allocated object from handle.
 * @pool: pool from which the object was allocated
 * @handle: handle वापसed from zs_दो_स्मृति
 * @mm: mapping mode to use
 *
 * Beक्रमe using an object allocated from zs_दो_स्मृति, it must be mapped using
 * this function. When करोne with the object, it must be unmapped using
 * zs_unmap_object.
 *
 * Only one object can be mapped per cpu at a समय. There is no protection
 * against nested mappings.
 *
 * This function वापसs with preemption and page faults disabled.
 */
व्योम *zs_map_object(काष्ठा zs_pool *pool, अचिन्हित दीर्घ handle,
			क्रमागत zs_mapmode mm)
अणु
	काष्ठा zspage *zspage;
	काष्ठा page *page;
	अचिन्हित दीर्घ obj, off;
	अचिन्हित पूर्णांक obj_idx;

	अचिन्हित पूर्णांक class_idx;
	क्रमागत fullness_group fg;
	काष्ठा size_class *class;
	काष्ठा mapping_area *area;
	काष्ठा page *pages[2];
	व्योम *ret;

	/*
	 * Because we use per-cpu mapping areas shared among the
	 * pools/users, we can't allow mapping in पूर्णांकerrupt context
	 * because it can corrupt another users mappings.
	 */
	BUG_ON(in_पूर्णांकerrupt());

	/* From now on, migration cannot move the object */
	pin_tag(handle);

	obj = handle_to_obj(handle);
	obj_to_location(obj, &page, &obj_idx);
	zspage = get_zspage(page);

	/* migration cannot move any subpage in this zspage */
	migrate_पढ़ो_lock(zspage);

	get_zspage_mapping(zspage, &class_idx, &fg);
	class = pool->size_class[class_idx];
	off = (class->size * obj_idx) & ~PAGE_MASK;

	area = &get_cpu_var(zs_map_area);
	area->vm_mm = mm;
	अगर (off + class->size <= PAGE_SIZE) अणु
		/* this object is contained entirely within a page */
		area->vm_addr = kmap_atomic(page);
		ret = area->vm_addr + off;
		जाओ out;
	पूर्ण

	/* this object spans two pages */
	pages[0] = page;
	pages[1] = get_next_page(page);
	BUG_ON(!pages[1]);

	ret = __zs_map_object(area, pages, off, class->size);
out:
	अगर (likely(!PageHugeObject(page)))
		ret += ZS_HANDLE_SIZE;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zs_map_object);

व्योम zs_unmap_object(काष्ठा zs_pool *pool, अचिन्हित दीर्घ handle)
अणु
	काष्ठा zspage *zspage;
	काष्ठा page *page;
	अचिन्हित दीर्घ obj, off;
	अचिन्हित पूर्णांक obj_idx;

	अचिन्हित पूर्णांक class_idx;
	क्रमागत fullness_group fg;
	काष्ठा size_class *class;
	काष्ठा mapping_area *area;

	obj = handle_to_obj(handle);
	obj_to_location(obj, &page, &obj_idx);
	zspage = get_zspage(page);
	get_zspage_mapping(zspage, &class_idx, &fg);
	class = pool->size_class[class_idx];
	off = (class->size * obj_idx) & ~PAGE_MASK;

	area = this_cpu_ptr(&zs_map_area);
	अगर (off + class->size <= PAGE_SIZE)
		kunmap_atomic(area->vm_addr);
	अन्यथा अणु
		काष्ठा page *pages[2];

		pages[0] = page;
		pages[1] = get_next_page(page);
		BUG_ON(!pages[1]);

		__zs_unmap_object(area, pages, off, class->size);
	पूर्ण
	put_cpu_var(zs_map_area);

	migrate_पढ़ो_unlock(zspage);
	unpin_tag(handle);
पूर्ण
EXPORT_SYMBOL_GPL(zs_unmap_object);

/**
 * zs_huge_class_size() - Returns the size (in bytes) of the first huge
 *                        zsदो_स्मृति &size_class.
 * @pool: zsदो_स्मृति pool to use
 *
 * The function वापसs the size of the first huge class - any object of equal
 * or bigger size will be stored in zspage consisting of a single physical
 * page.
 *
 * Context: Any context.
 *
 * Return: the size (in bytes) of the first huge zsदो_स्मृति &size_class.
 */
माप_प्रकार zs_huge_class_size(काष्ठा zs_pool *pool)
अणु
	वापस huge_class_size;
पूर्ण
EXPORT_SYMBOL_GPL(zs_huge_class_size);

अटल अचिन्हित दीर्घ obj_दो_स्मृति(काष्ठा size_class *class,
				काष्ठा zspage *zspage, अचिन्हित दीर्घ handle)
अणु
	पूर्णांक i, nr_page, offset;
	अचिन्हित दीर्घ obj;
	काष्ठा link_मुक्त *link;

	काष्ठा page *m_page;
	अचिन्हित दीर्घ m_offset;
	व्योम *vaddr;

	handle |= OBJ_ALLOCATED_TAG;
	obj = get_मुक्तobj(zspage);

	offset = obj * class->size;
	nr_page = offset >> PAGE_SHIFT;
	m_offset = offset & ~PAGE_MASK;
	m_page = get_first_page(zspage);

	क्रम (i = 0; i < nr_page; i++)
		m_page = get_next_page(m_page);

	vaddr = kmap_atomic(m_page);
	link = (काष्ठा link_मुक्त *)vaddr + m_offset / माप(*link);
	set_मुक्तobj(zspage, link->next >> OBJ_TAG_BITS);
	अगर (likely(!PageHugeObject(m_page)))
		/* record handle in the header of allocated chunk */
		link->handle = handle;
	अन्यथा
		/* record handle to page->index */
		zspage->first_page->index = handle;

	kunmap_atomic(vaddr);
	mod_zspage_inuse(zspage, 1);
	zs_stat_inc(class, OBJ_USED, 1);

	obj = location_to_obj(m_page, obj);

	वापस obj;
पूर्ण


/**
 * zs_दो_स्मृति - Allocate block of given size from pool.
 * @pool: pool to allocate from
 * @size: size of block to allocate
 * @gfp: gfp flags when allocating object
 *
 * On success, handle to the allocated object is वापसed,
 * otherwise 0.
 * Allocation requests with size > ZS_MAX_ALLOC_SIZE will fail.
 */
अचिन्हित दीर्घ zs_दो_स्मृति(काष्ठा zs_pool *pool, माप_प्रकार size, gfp_t gfp)
अणु
	अचिन्हित दीर्घ handle, obj;
	काष्ठा size_class *class;
	क्रमागत fullness_group newfg;
	काष्ठा zspage *zspage;

	अगर (unlikely(!size || size > ZS_MAX_ALLOC_SIZE))
		वापस 0;

	handle = cache_alloc_handle(pool, gfp);
	अगर (!handle)
		वापस 0;

	/* extra space in chunk to keep the handle */
	size += ZS_HANDLE_SIZE;
	class = pool->size_class[get_size_class_index(size)];

	spin_lock(&class->lock);
	zspage = find_get_zspage(class);
	अगर (likely(zspage)) अणु
		obj = obj_दो_स्मृति(class, zspage, handle);
		/* Now move the zspage to another fullness group, अगर required */
		fix_fullness_group(class, zspage);
		record_obj(handle, obj);
		spin_unlock(&class->lock);

		वापस handle;
	पूर्ण

	spin_unlock(&class->lock);

	zspage = alloc_zspage(pool, class, gfp);
	अगर (!zspage) अणु
		cache_मुक्त_handle(pool, handle);
		वापस 0;
	पूर्ण

	spin_lock(&class->lock);
	obj = obj_दो_स्मृति(class, zspage, handle);
	newfg = get_fullness_group(class, zspage);
	insert_zspage(class, zspage, newfg);
	set_zspage_mapping(zspage, class->index, newfg);
	record_obj(handle, obj);
	atomic_दीर्घ_add(class->pages_per_zspage,
				&pool->pages_allocated);
	zs_stat_inc(class, OBJ_ALLOCATED, class->objs_per_zspage);

	/* We completely set up zspage so mark them as movable */
	SetZsPageMovable(pool, zspage);
	spin_unlock(&class->lock);

	वापस handle;
पूर्ण
EXPORT_SYMBOL_GPL(zs_दो_स्मृति);

अटल व्योम obj_मुक्त(काष्ठा size_class *class, अचिन्हित दीर्घ obj)
अणु
	काष्ठा link_मुक्त *link;
	काष्ठा zspage *zspage;
	काष्ठा page *f_page;
	अचिन्हित दीर्घ f_offset;
	अचिन्हित पूर्णांक f_objidx;
	व्योम *vaddr;

	obj &= ~OBJ_ALLOCATED_TAG;
	obj_to_location(obj, &f_page, &f_objidx);
	f_offset = (class->size * f_objidx) & ~PAGE_MASK;
	zspage = get_zspage(f_page);

	vaddr = kmap_atomic(f_page);

	/* Insert this object in containing zspage's मुक्तlist */
	link = (काष्ठा link_मुक्त *)(vaddr + f_offset);
	link->next = get_मुक्तobj(zspage) << OBJ_TAG_BITS;
	kunmap_atomic(vaddr);
	set_मुक्तobj(zspage, f_objidx);
	mod_zspage_inuse(zspage, -1);
	zs_stat_dec(class, OBJ_USED, 1);
पूर्ण

व्योम zs_मुक्त(काष्ठा zs_pool *pool, अचिन्हित दीर्घ handle)
अणु
	काष्ठा zspage *zspage;
	काष्ठा page *f_page;
	अचिन्हित दीर्घ obj;
	अचिन्हित पूर्णांक f_objidx;
	पूर्णांक class_idx;
	काष्ठा size_class *class;
	क्रमागत fullness_group fullness;
	bool isolated;

	अगर (unlikely(!handle))
		वापस;

	pin_tag(handle);
	obj = handle_to_obj(handle);
	obj_to_location(obj, &f_page, &f_objidx);
	zspage = get_zspage(f_page);

	migrate_पढ़ो_lock(zspage);

	get_zspage_mapping(zspage, &class_idx, &fullness);
	class = pool->size_class[class_idx];

	spin_lock(&class->lock);
	obj_मुक्त(class, obj);
	fullness = fix_fullness_group(class, zspage);
	अगर (fullness != ZS_EMPTY) अणु
		migrate_पढ़ो_unlock(zspage);
		जाओ out;
	पूर्ण

	isolated = is_zspage_isolated(zspage);
	migrate_पढ़ो_unlock(zspage);
	/* If zspage is isolated, zs_page_putback will मुक्त the zspage */
	अगर (likely(!isolated))
		मुक्त_zspage(pool, class, zspage);
out:

	spin_unlock(&class->lock);
	unpin_tag(handle);
	cache_मुक्त_handle(pool, handle);
पूर्ण
EXPORT_SYMBOL_GPL(zs_मुक्त);

अटल व्योम zs_object_copy(काष्ठा size_class *class, अचिन्हित दीर्घ dst,
				अचिन्हित दीर्घ src)
अणु
	काष्ठा page *s_page, *d_page;
	अचिन्हित पूर्णांक s_objidx, d_objidx;
	अचिन्हित दीर्घ s_off, d_off;
	व्योम *s_addr, *d_addr;
	पूर्णांक s_size, d_size, size;
	पूर्णांक written = 0;

	s_size = d_size = class->size;

	obj_to_location(src, &s_page, &s_objidx);
	obj_to_location(dst, &d_page, &d_objidx);

	s_off = (class->size * s_objidx) & ~PAGE_MASK;
	d_off = (class->size * d_objidx) & ~PAGE_MASK;

	अगर (s_off + class->size > PAGE_SIZE)
		s_size = PAGE_SIZE - s_off;

	अगर (d_off + class->size > PAGE_SIZE)
		d_size = PAGE_SIZE - d_off;

	s_addr = kmap_atomic(s_page);
	d_addr = kmap_atomic(d_page);

	जबतक (1) अणु
		size = min(s_size, d_size);
		स_नकल(d_addr + d_off, s_addr + s_off, size);
		written += size;

		अगर (written == class->size)
			अवरोध;

		s_off += size;
		s_size -= size;
		d_off += size;
		d_size -= size;

		अगर (s_off >= PAGE_SIZE) अणु
			kunmap_atomic(d_addr);
			kunmap_atomic(s_addr);
			s_page = get_next_page(s_page);
			s_addr = kmap_atomic(s_page);
			d_addr = kmap_atomic(d_page);
			s_size = class->size - written;
			s_off = 0;
		पूर्ण

		अगर (d_off >= PAGE_SIZE) अणु
			kunmap_atomic(d_addr);
			d_page = get_next_page(d_page);
			d_addr = kmap_atomic(d_page);
			d_size = class->size - written;
			d_off = 0;
		पूर्ण
	पूर्ण

	kunmap_atomic(d_addr);
	kunmap_atomic(s_addr);
पूर्ण

/*
 * Find alloced object in zspage from index object and
 * वापस handle.
 */
अटल अचिन्हित दीर्घ find_alloced_obj(काष्ठा size_class *class,
					काष्ठा page *page, पूर्णांक *obj_idx)
अणु
	अचिन्हित दीर्घ head;
	पूर्णांक offset = 0;
	पूर्णांक index = *obj_idx;
	अचिन्हित दीर्घ handle = 0;
	व्योम *addr = kmap_atomic(page);

	offset = get_first_obj_offset(page);
	offset += class->size * index;

	जबतक (offset < PAGE_SIZE) अणु
		head = obj_to_head(page, addr + offset);
		अगर (head & OBJ_ALLOCATED_TAG) अणु
			handle = head & ~OBJ_ALLOCATED_TAG;
			अगर (trypin_tag(handle))
				अवरोध;
			handle = 0;
		पूर्ण

		offset += class->size;
		index++;
	पूर्ण

	kunmap_atomic(addr);

	*obj_idx = index;

	वापस handle;
पूर्ण

काष्ठा zs_compact_control अणु
	/* Source spage क्रम migration which could be a subpage of zspage */
	काष्ठा page *s_page;
	/* Destination page क्रम migration which should be a first page
	 * of zspage. */
	काष्ठा page *d_page;
	 /* Starting object index within @s_page which used क्रम live object
	  * in the subpage. */
	पूर्णांक obj_idx;
पूर्ण;

अटल पूर्णांक migrate_zspage(काष्ठा zs_pool *pool, काष्ठा size_class *class,
				काष्ठा zs_compact_control *cc)
अणु
	अचिन्हित दीर्घ used_obj, मुक्त_obj;
	अचिन्हित दीर्घ handle;
	काष्ठा page *s_page = cc->s_page;
	काष्ठा page *d_page = cc->d_page;
	पूर्णांक obj_idx = cc->obj_idx;
	पूर्णांक ret = 0;

	जबतक (1) अणु
		handle = find_alloced_obj(class, s_page, &obj_idx);
		अगर (!handle) अणु
			s_page = get_next_page(s_page);
			अगर (!s_page)
				अवरोध;
			obj_idx = 0;
			जारी;
		पूर्ण

		/* Stop अगर there is no more space */
		अगर (zspage_full(class, get_zspage(d_page))) अणु
			unpin_tag(handle);
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		used_obj = handle_to_obj(handle);
		मुक्त_obj = obj_दो_स्मृति(class, get_zspage(d_page), handle);
		zs_object_copy(class, मुक्त_obj, used_obj);
		obj_idx++;
		/*
		 * record_obj updates handle's value to मुक्त_obj and it will
		 * invalidate lock bit(ie, HANDLE_PIN_BIT) of handle, which
		 * अवरोधs synchronization using pin_tag(e,g, zs_मुक्त) so
		 * let's keep the lock bit.
		 */
		मुक्त_obj |= BIT(HANDLE_PIN_BIT);
		record_obj(handle, मुक्त_obj);
		unpin_tag(handle);
		obj_मुक्त(class, used_obj);
	पूर्ण

	/* Remember last position in this iteration */
	cc->s_page = s_page;
	cc->obj_idx = obj_idx;

	वापस ret;
पूर्ण

अटल काष्ठा zspage *isolate_zspage(काष्ठा size_class *class, bool source)
अणु
	पूर्णांक i;
	काष्ठा zspage *zspage;
	क्रमागत fullness_group fg[2] = अणुZS_ALMOST_EMPTY, ZS_ALMOST_FULLपूर्ण;

	अगर (!source) अणु
		fg[0] = ZS_ALMOST_FULL;
		fg[1] = ZS_ALMOST_EMPTY;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		zspage = list_first_entry_or_null(&class->fullness_list[fg[i]],
							काष्ठा zspage, list);
		अगर (zspage) अणु
			VM_BUG_ON(is_zspage_isolated(zspage));
			हटाओ_zspage(class, zspage, fg[i]);
			वापस zspage;
		पूर्ण
	पूर्ण

	वापस zspage;
पूर्ण

/*
 * putback_zspage - add @zspage पूर्णांकo right class's fullness list
 * @class: destination class
 * @zspage: target page
 *
 * Return @zspage's fullness_group
 */
अटल क्रमागत fullness_group putback_zspage(काष्ठा size_class *class,
			काष्ठा zspage *zspage)
अणु
	क्रमागत fullness_group fullness;

	VM_BUG_ON(is_zspage_isolated(zspage));

	fullness = get_fullness_group(class, zspage);
	insert_zspage(class, zspage, fullness);
	set_zspage_mapping(zspage, class->index, fullness);

	वापस fullness;
पूर्ण

#अगर_घोषित CONFIG_COMPACTION
/*
 * To prevent zspage destroy during migration, zspage मुक्तing should
 * hold locks of all pages in the zspage.
 */
अटल व्योम lock_zspage(काष्ठा zspage *zspage)
अणु
	काष्ठा page *page = get_first_page(zspage);

	करो अणु
		lock_page(page);
	पूर्ण जबतक ((page = get_next_page(page)) != शून्य);
पूर्ण

अटल पूर्णांक zs_init_fs_context(काष्ठा fs_context *fc)
अणु
	वापस init_pseuकरो(fc, ZSMALLOC_MAGIC) ? 0 : -ENOMEM;
पूर्ण

अटल काष्ठा file_प्रणाली_type zsदो_स्मृति_fs = अणु
	.name		= "zsmalloc",
	.init_fs_context = zs_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;

अटल पूर्णांक zsदो_स्मृति_mount(व्योम)
अणु
	पूर्णांक ret = 0;

	zsदो_स्मृति_mnt = kern_mount(&zsदो_स्मृति_fs);
	अगर (IS_ERR(zsदो_स्मृति_mnt))
		ret = PTR_ERR(zsदो_स्मृति_mnt);

	वापस ret;
पूर्ण

अटल व्योम zsदो_स्मृति_unmount(व्योम)
अणु
	kern_unmount(zsदो_स्मृति_mnt);
पूर्ण

अटल व्योम migrate_lock_init(काष्ठा zspage *zspage)
अणु
	rwlock_init(&zspage->lock);
पूर्ण

अटल व्योम migrate_पढ़ो_lock(काष्ठा zspage *zspage) __acquires(&zspage->lock)
अणु
	पढ़ो_lock(&zspage->lock);
पूर्ण

अटल व्योम migrate_पढ़ो_unlock(काष्ठा zspage *zspage) __releases(&zspage->lock)
अणु
	पढ़ो_unlock(&zspage->lock);
पूर्ण

अटल व्योम migrate_ग_लिखो_lock(काष्ठा zspage *zspage)
अणु
	ग_लिखो_lock(&zspage->lock);
पूर्ण

अटल व्योम migrate_ग_लिखो_unlock(काष्ठा zspage *zspage)
अणु
	ग_लिखो_unlock(&zspage->lock);
पूर्ण

/* Number of isolated subpage क्रम *page migration* in this zspage */
अटल व्योम inc_zspage_isolation(काष्ठा zspage *zspage)
अणु
	zspage->isolated++;
पूर्ण

अटल व्योम dec_zspage_isolation(काष्ठा zspage *zspage)
अणु
	zspage->isolated--;
पूर्ण

अटल व्योम putback_zspage_deferred(काष्ठा zs_pool *pool,
				    काष्ठा size_class *class,
				    काष्ठा zspage *zspage)
अणु
	क्रमागत fullness_group fg;

	fg = putback_zspage(class, zspage);
	अगर (fg == ZS_EMPTY)
		schedule_work(&pool->मुक्त_work);

पूर्ण

अटल अंतरभूत व्योम zs_pool_dec_isolated(काष्ठा zs_pool *pool)
अणु
	VM_BUG_ON(atomic_दीर्घ_पढ़ो(&pool->isolated_pages) <= 0);
	atomic_दीर्घ_dec(&pool->isolated_pages);
	/*
	 * There's no possibility of racing, since रुको_क्रम_isolated_drain()
	 * checks the isolated count under &class->lock after enqueuing
	 * on migration_रुको.
	 */
	अगर (atomic_दीर्घ_पढ़ो(&pool->isolated_pages) == 0 && pool->destroying)
		wake_up_all(&pool->migration_रुको);
पूर्ण

अटल व्योम replace_sub_page(काष्ठा size_class *class, काष्ठा zspage *zspage,
				काष्ठा page *newpage, काष्ठा page *oldpage)
अणु
	काष्ठा page *page;
	काष्ठा page *pages[ZS_MAX_PAGES_PER_ZSPAGE] = अणुशून्य, पूर्ण;
	पूर्णांक idx = 0;

	page = get_first_page(zspage);
	करो अणु
		अगर (page == oldpage)
			pages[idx] = newpage;
		अन्यथा
			pages[idx] = page;
		idx++;
	पूर्ण जबतक ((page = get_next_page(page)) != शून्य);

	create_page_chain(class, zspage, pages);
	set_first_obj_offset(newpage, get_first_obj_offset(oldpage));
	अगर (unlikely(PageHugeObject(oldpage)))
		newpage->index = oldpage->index;
	__SetPageMovable(newpage, page_mapping(oldpage));
पूर्ण

अटल bool zs_page_isolate(काष्ठा page *page, isolate_mode_t mode)
अणु
	काष्ठा zs_pool *pool;
	काष्ठा size_class *class;
	पूर्णांक class_idx;
	क्रमागत fullness_group fullness;
	काष्ठा zspage *zspage;
	काष्ठा address_space *mapping;

	/*
	 * Page is locked so zspage couldn't be destroyed. For detail, look at
	 * lock_zspage in मुक्त_zspage.
	 */
	VM_BUG_ON_PAGE(!PageMovable(page), page);
	VM_BUG_ON_PAGE(PageIsolated(page), page);

	zspage = get_zspage(page);

	/*
	 * Without class lock, fullness could be stale जबतक class_idx is okay
	 * because class_idx is स्थिरant unless page is मुक्तd so we should get
	 * fullness again under class lock.
	 */
	get_zspage_mapping(zspage, &class_idx, &fullness);
	mapping = page_mapping(page);
	pool = mapping->निजी_data;
	class = pool->size_class[class_idx];

	spin_lock(&class->lock);
	अगर (get_zspage_inuse(zspage) == 0) अणु
		spin_unlock(&class->lock);
		वापस false;
	पूर्ण

	/* zspage is isolated क्रम object migration */
	अगर (list_empty(&zspage->list) && !is_zspage_isolated(zspage)) अणु
		spin_unlock(&class->lock);
		वापस false;
	पूर्ण

	/*
	 * If this is first समय isolation क्रम the zspage, isolate zspage from
	 * size_class to prevent further object allocation from the zspage.
	 */
	अगर (!list_empty(&zspage->list) && !is_zspage_isolated(zspage)) अणु
		get_zspage_mapping(zspage, &class_idx, &fullness);
		atomic_दीर्घ_inc(&pool->isolated_pages);
		हटाओ_zspage(class, zspage, fullness);
	पूर्ण

	inc_zspage_isolation(zspage);
	spin_unlock(&class->lock);

	वापस true;
पूर्ण

अटल पूर्णांक zs_page_migrate(काष्ठा address_space *mapping, काष्ठा page *newpage,
		काष्ठा page *page, क्रमागत migrate_mode mode)
अणु
	काष्ठा zs_pool *pool;
	काष्ठा size_class *class;
	पूर्णांक class_idx;
	क्रमागत fullness_group fullness;
	काष्ठा zspage *zspage;
	काष्ठा page *dummy;
	व्योम *s_addr, *d_addr, *addr;
	पूर्णांक offset, pos;
	अचिन्हित दीर्घ handle, head;
	अचिन्हित दीर्घ old_obj, new_obj;
	अचिन्हित पूर्णांक obj_idx;
	पूर्णांक ret = -EAGAIN;

	/*
	 * We cannot support the _NO_COPY हाल here, because copy needs to
	 * happen under the zs lock, which करोes not work with
	 * MIGRATE_SYNC_NO_COPY workflow.
	 */
	अगर (mode == MIGRATE_SYNC_NO_COPY)
		वापस -EINVAL;

	VM_BUG_ON_PAGE(!PageMovable(page), page);
	VM_BUG_ON_PAGE(!PageIsolated(page), page);

	zspage = get_zspage(page);

	/* Concurrent compactor cannot migrate any subpage in zspage */
	migrate_ग_लिखो_lock(zspage);
	get_zspage_mapping(zspage, &class_idx, &fullness);
	pool = mapping->निजी_data;
	class = pool->size_class[class_idx];
	offset = get_first_obj_offset(page);

	spin_lock(&class->lock);
	अगर (!get_zspage_inuse(zspage)) अणु
		/*
		 * Set "offset" to end of the page so that every loops
		 * skips unnecessary object scanning.
		 */
		offset = PAGE_SIZE;
	पूर्ण

	pos = offset;
	s_addr = kmap_atomic(page);
	जबतक (pos < PAGE_SIZE) अणु
		head = obj_to_head(page, s_addr + pos);
		अगर (head & OBJ_ALLOCATED_TAG) अणु
			handle = head & ~OBJ_ALLOCATED_TAG;
			अगर (!trypin_tag(handle))
				जाओ unpin_objects;
		पूर्ण
		pos += class->size;
	पूर्ण

	/*
	 * Here, any user cannot access all objects in the zspage so let's move.
	 */
	d_addr = kmap_atomic(newpage);
	स_नकल(d_addr, s_addr, PAGE_SIZE);
	kunmap_atomic(d_addr);

	क्रम (addr = s_addr + offset; addr < s_addr + pos;
					addr += class->size) अणु
		head = obj_to_head(page, addr);
		अगर (head & OBJ_ALLOCATED_TAG) अणु
			handle = head & ~OBJ_ALLOCATED_TAG;
			BUG_ON(!testpin_tag(handle));

			old_obj = handle_to_obj(handle);
			obj_to_location(old_obj, &dummy, &obj_idx);
			new_obj = (अचिन्हित दीर्घ)location_to_obj(newpage,
								obj_idx);
			new_obj |= BIT(HANDLE_PIN_BIT);
			record_obj(handle, new_obj);
		पूर्ण
	पूर्ण

	replace_sub_page(class, zspage, newpage, page);
	get_page(newpage);

	dec_zspage_isolation(zspage);

	/*
	 * Page migration is करोne so let's putback isolated zspage to
	 * the list अगर @page is final isolated subpage in the zspage.
	 */
	अगर (!is_zspage_isolated(zspage)) अणु
		/*
		 * We cannot race with zs_destroy_pool() here because we रुको
		 * क्रम isolation to hit zero beक्रमe we start destroying.
		 * Also, we ensure that everyone can see pool->destroying beक्रमe
		 * we start रुकोing.
		 */
		putback_zspage_deferred(pool, class, zspage);
		zs_pool_dec_isolated(pool);
	पूर्ण

	अगर (page_zone(newpage) != page_zone(page)) अणु
		dec_zone_page_state(page, NR_ZSPAGES);
		inc_zone_page_state(newpage, NR_ZSPAGES);
	पूर्ण

	reset_page(page);
	put_page(page);
	page = newpage;

	ret = MIGRATEPAGE_SUCCESS;
unpin_objects:
	क्रम (addr = s_addr + offset; addr < s_addr + pos;
						addr += class->size) अणु
		head = obj_to_head(page, addr);
		अगर (head & OBJ_ALLOCATED_TAG) अणु
			handle = head & ~OBJ_ALLOCATED_TAG;
			BUG_ON(!testpin_tag(handle));
			unpin_tag(handle);
		पूर्ण
	पूर्ण
	kunmap_atomic(s_addr);
	spin_unlock(&class->lock);
	migrate_ग_लिखो_unlock(zspage);

	वापस ret;
पूर्ण

अटल व्योम zs_page_putback(काष्ठा page *page)
अणु
	काष्ठा zs_pool *pool;
	काष्ठा size_class *class;
	पूर्णांक class_idx;
	क्रमागत fullness_group fg;
	काष्ठा address_space *mapping;
	काष्ठा zspage *zspage;

	VM_BUG_ON_PAGE(!PageMovable(page), page);
	VM_BUG_ON_PAGE(!PageIsolated(page), page);

	zspage = get_zspage(page);
	get_zspage_mapping(zspage, &class_idx, &fg);
	mapping = page_mapping(page);
	pool = mapping->निजी_data;
	class = pool->size_class[class_idx];

	spin_lock(&class->lock);
	dec_zspage_isolation(zspage);
	अगर (!is_zspage_isolated(zspage)) अणु
		/*
		 * Due to page_lock, we cannot मुक्त zspage immediately
		 * so let's defer.
		 */
		putback_zspage_deferred(pool, class, zspage);
		zs_pool_dec_isolated(pool);
	पूर्ण
	spin_unlock(&class->lock);
पूर्ण

अटल स्थिर काष्ठा address_space_operations zsदो_स्मृति_aops = अणु
	.isolate_page = zs_page_isolate,
	.migratepage = zs_page_migrate,
	.putback_page = zs_page_putback,
पूर्ण;

अटल पूर्णांक zs_रेजिस्टर_migration(काष्ठा zs_pool *pool)
अणु
	pool->inode = alloc_anon_inode(zsदो_स्मृति_mnt->mnt_sb);
	अगर (IS_ERR(pool->inode)) अणु
		pool->inode = शून्य;
		वापस 1;
	पूर्ण

	pool->inode->i_mapping->निजी_data = pool;
	pool->inode->i_mapping->a_ops = &zsदो_स्मृति_aops;
	वापस 0;
पूर्ण

अटल bool pool_isolated_are_drained(काष्ठा zs_pool *pool)
अणु
	वापस atomic_दीर्घ_पढ़ो(&pool->isolated_pages) == 0;
पूर्ण

/* Function क्रम resolving migration */
अटल व्योम रुको_क्रम_isolated_drain(काष्ठा zs_pool *pool)
अणु

	/*
	 * We're in the process of destroying the pool, so there are no
	 * active allocations. zs_page_isolate() fails क्रम completely मुक्त
	 * zspages, so we need only रुको क्रम the zs_pool's isolated
	 * count to hit zero.
	 */
	रुको_event(pool->migration_रुको,
		   pool_isolated_are_drained(pool));
पूर्ण

अटल व्योम zs_unरेजिस्टर_migration(काष्ठा zs_pool *pool)
अणु
	pool->destroying = true;
	/*
	 * We need a memory barrier here to ensure global visibility of
	 * pool->destroying. Thus pool->isolated pages will either be 0 in which
	 * हाल we करोn't care, or it will be > 0 and pool->destroying will
	 * ensure that we wake up once isolation hits 0.
	 */
	smp_mb();
	रुको_क्रम_isolated_drain(pool); /* This can block */
	flush_work(&pool->मुक्त_work);
	iput(pool->inode);
पूर्ण

/*
 * Caller should hold page_lock of all pages in the zspage
 * In here, we cannot use zspage meta data.
 */
अटल व्योम async_मुक्त_zspage(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i;
	काष्ठा size_class *class;
	अचिन्हित पूर्णांक class_idx;
	क्रमागत fullness_group fullness;
	काष्ठा zspage *zspage, *पंचांगp;
	LIST_HEAD(मुक्त_pages);
	काष्ठा zs_pool *pool = container_of(work, काष्ठा zs_pool,
					मुक्त_work);

	क्रम (i = 0; i < ZS_SIZE_CLASSES; i++) अणु
		class = pool->size_class[i];
		अगर (class->index != i)
			जारी;

		spin_lock(&class->lock);
		list_splice_init(&class->fullness_list[ZS_EMPTY], &मुक्त_pages);
		spin_unlock(&class->lock);
	पूर्ण


	list_क्रम_each_entry_safe(zspage, पंचांगp, &मुक्त_pages, list) अणु
		list_del(&zspage->list);
		lock_zspage(zspage);

		get_zspage_mapping(zspage, &class_idx, &fullness);
		VM_BUG_ON(fullness != ZS_EMPTY);
		class = pool->size_class[class_idx];
		spin_lock(&class->lock);
		__मुक्त_zspage(pool, pool->size_class[class_idx], zspage);
		spin_unlock(&class->lock);
	पूर्ण
पूर्ण;

अटल व्योम kick_deferred_मुक्त(काष्ठा zs_pool *pool)
अणु
	schedule_work(&pool->मुक्त_work);
पूर्ण

अटल व्योम init_deferred_मुक्त(काष्ठा zs_pool *pool)
अणु
	INIT_WORK(&pool->मुक्त_work, async_मुक्त_zspage);
पूर्ण

अटल व्योम SetZsPageMovable(काष्ठा zs_pool *pool, काष्ठा zspage *zspage)
अणु
	काष्ठा page *page = get_first_page(zspage);

	करो अणु
		WARN_ON(!trylock_page(page));
		__SetPageMovable(page, pool->inode->i_mapping);
		unlock_page(page);
	पूर्ण जबतक ((page = get_next_page(page)) != शून्य);
पूर्ण
#पूर्ण_अगर

/*
 *
 * Based on the number of unused allocated objects calculate
 * and वापस the number of pages that we can मुक्त.
 */
अटल अचिन्हित दीर्घ zs_can_compact(काष्ठा size_class *class)
अणु
	अचिन्हित दीर्घ obj_wasted;
	अचिन्हित दीर्घ obj_allocated = zs_stat_get(class, OBJ_ALLOCATED);
	अचिन्हित दीर्घ obj_used = zs_stat_get(class, OBJ_USED);

	अगर (obj_allocated <= obj_used)
		वापस 0;

	obj_wasted = obj_allocated - obj_used;
	obj_wasted /= class->objs_per_zspage;

	वापस obj_wasted * class->pages_per_zspage;
पूर्ण

अटल अचिन्हित दीर्घ __zs_compact(काष्ठा zs_pool *pool,
				  काष्ठा size_class *class)
अणु
	काष्ठा zs_compact_control cc;
	काष्ठा zspage *src_zspage;
	काष्ठा zspage *dst_zspage = शून्य;
	अचिन्हित दीर्घ pages_मुक्तd = 0;

	spin_lock(&class->lock);
	जबतक ((src_zspage = isolate_zspage(class, true))) अणु

		अगर (!zs_can_compact(class))
			अवरोध;

		cc.obj_idx = 0;
		cc.s_page = get_first_page(src_zspage);

		जबतक ((dst_zspage = isolate_zspage(class, false))) अणु
			cc.d_page = get_first_page(dst_zspage);
			/*
			 * If there is no more space in dst_page, resched
			 * and see अगर anyone had allocated another zspage.
			 */
			अगर (!migrate_zspage(pool, class, &cc))
				अवरोध;

			putback_zspage(class, dst_zspage);
		पूर्ण

		/* Stop अगर we couldn't find slot */
		अगर (dst_zspage == शून्य)
			अवरोध;

		putback_zspage(class, dst_zspage);
		अगर (putback_zspage(class, src_zspage) == ZS_EMPTY) अणु
			मुक्त_zspage(pool, class, src_zspage);
			pages_मुक्तd += class->pages_per_zspage;
		पूर्ण
		spin_unlock(&class->lock);
		cond_resched();
		spin_lock(&class->lock);
	पूर्ण

	अगर (src_zspage)
		putback_zspage(class, src_zspage);

	spin_unlock(&class->lock);

	वापस pages_मुक्तd;
पूर्ण

अचिन्हित दीर्घ zs_compact(काष्ठा zs_pool *pool)
अणु
	पूर्णांक i;
	काष्ठा size_class *class;
	अचिन्हित दीर्घ pages_मुक्तd = 0;

	क्रम (i = ZS_SIZE_CLASSES - 1; i >= 0; i--) अणु
		class = pool->size_class[i];
		अगर (!class)
			जारी;
		अगर (class->index != i)
			जारी;
		pages_मुक्तd += __zs_compact(pool, class);
	पूर्ण
	atomic_दीर्घ_add(pages_मुक्तd, &pool->stats.pages_compacted);

	वापस pages_मुक्तd;
पूर्ण
EXPORT_SYMBOL_GPL(zs_compact);

व्योम zs_pool_stats(काष्ठा zs_pool *pool, काष्ठा zs_pool_stats *stats)
अणु
	स_नकल(stats, &pool->stats, माप(काष्ठा zs_pool_stats));
पूर्ण
EXPORT_SYMBOL_GPL(zs_pool_stats);

अटल अचिन्हित दीर्घ zs_shrinker_scan(काष्ठा shrinker *shrinker,
		काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ pages_मुक्तd;
	काष्ठा zs_pool *pool = container_of(shrinker, काष्ठा zs_pool,
			shrinker);

	/*
	 * Compact classes and calculate compaction delta.
	 * Can run concurrently with a manually triggered
	 * (by user) compaction.
	 */
	pages_मुक्तd = zs_compact(pool);

	वापस pages_मुक्तd ? pages_मुक्तd : SHRINK_STOP;
पूर्ण

अटल अचिन्हित दीर्घ zs_shrinker_count(काष्ठा shrinker *shrinker,
		काष्ठा shrink_control *sc)
अणु
	पूर्णांक i;
	काष्ठा size_class *class;
	अचिन्हित दीर्घ pages_to_मुक्त = 0;
	काष्ठा zs_pool *pool = container_of(shrinker, काष्ठा zs_pool,
			shrinker);

	क्रम (i = ZS_SIZE_CLASSES - 1; i >= 0; i--) अणु
		class = pool->size_class[i];
		अगर (!class)
			जारी;
		अगर (class->index != i)
			जारी;

		pages_to_मुक्त += zs_can_compact(class);
	पूर्ण

	वापस pages_to_मुक्त;
पूर्ण

अटल व्योम zs_unरेजिस्टर_shrinker(काष्ठा zs_pool *pool)
अणु
	unरेजिस्टर_shrinker(&pool->shrinker);
पूर्ण

अटल पूर्णांक zs_रेजिस्टर_shrinker(काष्ठा zs_pool *pool)
अणु
	pool->shrinker.scan_objects = zs_shrinker_scan;
	pool->shrinker.count_objects = zs_shrinker_count;
	pool->shrinker.batch = 0;
	pool->shrinker.seeks = DEFAULT_SEEKS;

	वापस रेजिस्टर_shrinker(&pool->shrinker);
पूर्ण

/**
 * zs_create_pool - Creates an allocation pool to work from.
 * @name: pool name to be created
 *
 * This function must be called beक्रमe anything when using
 * the zsदो_स्मृति allocator.
 *
 * On success, a poपूर्णांकer to the newly created pool is वापसed,
 * otherwise शून्य.
 */
काष्ठा zs_pool *zs_create_pool(स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	काष्ठा zs_pool *pool;
	काष्ठा size_class *prev_class = शून्य;

	pool = kzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस शून्य;

	init_deferred_मुक्त(pool);

	pool->name = kstrdup(name, GFP_KERNEL);
	अगर (!pool->name)
		जाओ err;

#अगर_घोषित CONFIG_COMPACTION
	init_रुकोqueue_head(&pool->migration_रुको);
#पूर्ण_अगर

	अगर (create_cache(pool))
		जाओ err;

	/*
	 * Iterate reversely, because, size of size_class that we want to use
	 * क्रम merging should be larger or equal to current size.
	 */
	क्रम (i = ZS_SIZE_CLASSES - 1; i >= 0; i--) अणु
		पूर्णांक size;
		पूर्णांक pages_per_zspage;
		पूर्णांक objs_per_zspage;
		काष्ठा size_class *class;
		पूर्णांक fullness = 0;

		size = ZS_MIN_ALLOC_SIZE + i * ZS_SIZE_CLASS_DELTA;
		अगर (size > ZS_MAX_ALLOC_SIZE)
			size = ZS_MAX_ALLOC_SIZE;
		pages_per_zspage = get_pages_per_zspage(size);
		objs_per_zspage = pages_per_zspage * PAGE_SIZE / size;

		/*
		 * We iterate from biggest करोwn to smallest classes,
		 * so huge_class_size holds the size of the first huge
		 * class. Any object bigger than or equal to that will
		 * endup in the huge class.
		 */
		अगर (pages_per_zspage != 1 && objs_per_zspage != 1 &&
				!huge_class_size) अणु
			huge_class_size = size;
			/*
			 * The object uses ZS_HANDLE_SIZE bytes to store the
			 * handle. We need to subtract it, because zs_दो_स्मृति()
			 * unconditionally adds handle size beक्रमe it perक्रमms
			 * size class search - so object may be smaller than
			 * huge class size, yet it still can end up in the huge
			 * class because it grows by ZS_HANDLE_SIZE extra bytes
			 * right beक्रमe class lookup.
			 */
			huge_class_size -= (ZS_HANDLE_SIZE - 1);
		पूर्ण

		/*
		 * size_class is used क्रम normal zsदो_स्मृति operation such
		 * as alloc/मुक्त क्रम that size. Although it is natural that we
		 * have one size_class क्रम each size, there is a chance that we
		 * can get more memory utilization अगर we use one size_class क्रम
		 * many dअगरferent sizes whose size_class have same
		 * अक्षरacteristics. So, we makes size_class poपूर्णांक to
		 * previous size_class अगर possible.
		 */
		अगर (prev_class) अणु
			अगर (can_merge(prev_class, pages_per_zspage, objs_per_zspage)) अणु
				pool->size_class[i] = prev_class;
				जारी;
			पूर्ण
		पूर्ण

		class = kzalloc(माप(काष्ठा size_class), GFP_KERNEL);
		अगर (!class)
			जाओ err;

		class->size = size;
		class->index = i;
		class->pages_per_zspage = pages_per_zspage;
		class->objs_per_zspage = objs_per_zspage;
		spin_lock_init(&class->lock);
		pool->size_class[i] = class;
		क्रम (fullness = ZS_EMPTY; fullness < NR_ZS_FULLNESS;
							fullness++)
			INIT_LIST_HEAD(&class->fullness_list[fullness]);

		prev_class = class;
	पूर्ण

	/* debug only, करोn't पात अगर it fails */
	zs_pool_stat_create(pool, name);

	अगर (zs_रेजिस्टर_migration(pool))
		जाओ err;

	/*
	 * Not critical since shrinker is only used to trigger पूर्णांकernal
	 * defragmentation of the pool which is pretty optional thing.  If
	 * registration fails we still can use the pool normally and user can
	 * trigger compaction manually. Thus, ignore वापस code.
	 */
	zs_रेजिस्टर_shrinker(pool);

	वापस pool;

err:
	zs_destroy_pool(pool);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(zs_create_pool);

व्योम zs_destroy_pool(काष्ठा zs_pool *pool)
अणु
	पूर्णांक i;

	zs_unरेजिस्टर_shrinker(pool);
	zs_unरेजिस्टर_migration(pool);
	zs_pool_stat_destroy(pool);

	क्रम (i = 0; i < ZS_SIZE_CLASSES; i++) अणु
		पूर्णांक fg;
		काष्ठा size_class *class = pool->size_class[i];

		अगर (!class)
			जारी;

		अगर (class->index != i)
			जारी;

		क्रम (fg = ZS_EMPTY; fg < NR_ZS_FULLNESS; fg++) अणु
			अगर (!list_empty(&class->fullness_list[fg])) अणु
				pr_info("Freeing non-empty class with size %db, fullness group %d\n",
					class->size, fg);
			पूर्ण
		पूर्ण
		kमुक्त(class);
	पूर्ण

	destroy_cache(pool);
	kमुक्त(pool->name);
	kमुक्त(pool);
पूर्ण
EXPORT_SYMBOL_GPL(zs_destroy_pool);

अटल पूर्णांक __init zs_init(व्योम)
अणु
	पूर्णांक ret;

	ret = zsदो_स्मृति_mount();
	अगर (ret)
		जाओ out;

	ret = cpuhp_setup_state(CPUHP_MM_ZS_PREPARE, "mm/zsmalloc:prepare",
				zs_cpu_prepare, zs_cpu_dead);
	अगर (ret)
		जाओ hp_setup_fail;

#अगर_घोषित CONFIG_ZPOOL
	zpool_रेजिस्टर_driver(&zs_zpool_driver);
#पूर्ण_अगर

	zs_stat_init();

	वापस 0;

hp_setup_fail:
	zsदो_स्मृति_unmount();
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास zs_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_ZPOOL
	zpool_unरेजिस्टर_driver(&zs_zpool_driver);
#पूर्ण_अगर
	zsदो_स्मृति_unmount();
	cpuhp_हटाओ_state(CPUHP_MM_ZS_PREPARE);

	zs_stat_निकास();
पूर्ण

module_init(zs_init);
module_निकास(zs_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Nitin Gupta <ngupta@vflare.org>");
