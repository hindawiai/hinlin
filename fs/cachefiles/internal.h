<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* General netfs cache on cache files पूर्णांकernal defs
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) "CacheFiles: " fmt


#समावेश <linux/fscache-cache.h>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको_bit.h>
#समावेश <linux/cred.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/security.h>

काष्ठा cachefiles_cache;
काष्ठा cachefiles_object;

बाह्य अचिन्हित cachefiles_debug;
#घोषणा CACHEखाताS_DEBUG_KENTER	1
#घोषणा CACHEखाताS_DEBUG_KLEAVE	2
#घोषणा CACHEखाताS_DEBUG_KDEBUG	4

#घोषणा cachefiles_gfp (__GFP_RECLAIM | __GFP_NORETRY | __GFP_NOMEMALLOC)

/*
 * node records
 */
काष्ठा cachefiles_object अणु
	काष्ठा fscache_object		fscache;	/* fscache handle */
	काष्ठा cachefiles_lookup_data	*lookup_data;	/* cached lookup data */
	काष्ठा dentry			*dentry;	/* the file/dir representing this object */
	काष्ठा dentry			*backer;	/* backing file */
	loff_t				i_size;		/* object size */
	अचिन्हित दीर्घ			flags;
#घोषणा CACHEखाताS_OBJECT_ACTIVE	0		/* T अगर marked active */
	atomic_t			usage;		/* object usage count */
	uपूर्णांक8_t				type;		/* object type */
	uपूर्णांक8_t				new;		/* T अगर object new */
	spinlock_t			work_lock;
	काष्ठा rb_node			active_node;	/* link in active tree (dentry is key) */
पूर्ण;

बाह्य काष्ठा kmem_cache *cachefiles_object_jar;

/*
 * Cache files cache definition
 */
काष्ठा cachefiles_cache अणु
	काष्ठा fscache_cache		cache;		/* FS-Cache record */
	काष्ठा vfsmount			*mnt;		/* mountpoपूर्णांक holding the cache */
	काष्ठा dentry			*graveyard;	/* directory पूर्णांकo which dead objects go */
	काष्ठा file			*cachefilesd;	/* manager daemon handle */
	स्थिर काष्ठा cred		*cache_cred;	/* security override क्रम accessing cache */
	काष्ठा mutex			daemon_mutex;	/* command serialisation mutex */
	रुको_queue_head_t		daemon_pollwq;	/* poll रुकोqueue क्रम daemon */
	काष्ठा rb_root			active_nodes;	/* active nodes (can't be culled) */
	rwlock_t			active_lock;	/* lock क्रम active_nodes */
	atomic_t			gravecounter;	/* graveyard uniquअगरier */
	atomic_t			f_released;	/* number of objects released lately */
	atomic_दीर्घ_t			b_released;	/* number of blocks released lately */
	अचिन्हित			frun_percent;	/* when to stop culling (% files) */
	अचिन्हित			fcull_percent;	/* when to start culling (% files) */
	अचिन्हित			fstop_percent;	/* when to stop allocating (% files) */
	अचिन्हित			brun_percent;	/* when to stop culling (% blocks) */
	अचिन्हित			bcull_percent;	/* when to start culling (% blocks) */
	अचिन्हित			bstop_percent;	/* when to stop allocating (% blocks) */
	अचिन्हित			bsize;		/* cache's block size */
	अचिन्हित			bshअगरt;		/* min(ilog2(PAGE_SIZE / bsize), 0) */
	uपूर्णांक64_t			frun;		/* when to stop culling */
	uपूर्णांक64_t			fcull;		/* when to start culling */
	uपूर्णांक64_t			fstop;		/* when to stop allocating */
	sector_t			brun;		/* when to stop culling */
	sector_t			bcull;		/* when to start culling */
	sector_t			bstop;		/* when to stop allocating */
	अचिन्हित दीर्घ			flags;
#घोषणा CACHEखाताS_READY		0	/* T अगर cache prepared */
#घोषणा CACHEखाताS_DEAD			1	/* T अगर cache dead */
#घोषणा CACHEखाताS_CULLING		2	/* T अगर cull engaged */
#घोषणा CACHEखाताS_STATE_CHANGED	3	/* T अगर state changed (poll trigger) */
	अक्षर				*rootस_नाम;	/* name of cache root directory */
	अक्षर				*secctx;	/* LSM security context */
	अक्षर				*tag;		/* cache binding tag */
पूर्ण;

/*
 * backing file पढ़ो tracking
 */
काष्ठा cachefiles_one_पढ़ो अणु
	रुको_queue_entry_t			monitor;	/* link पूर्णांकo monitored रुकोqueue */
	काष्ठा page			*back_page;	/* backing file page we're रुकोing क्रम */
	काष्ठा page			*netfs_page;	/* netfs page we're going to fill */
	काष्ठा fscache_retrieval	*op;		/* retrieval op covering this */
	काष्ठा list_head		op_link;	/* link in op's toकरो list */
पूर्ण;

/*
 * backing file ग_लिखो tracking
 */
काष्ठा cachefiles_one_ग_लिखो अणु
	काष्ठा page			*netfs_page;	/* netfs page to copy */
	काष्ठा cachefiles_object	*object;
	काष्ठा list_head		obj_link;	/* link in object's lists */
	fscache_rw_complete_t		end_io_func;
	व्योम				*context;
पूर्ण;

/*
 * auxiliary data xattr buffer
 */
काष्ठा cachefiles_xattr अणु
	uपूर्णांक16_t			len;
	uपूर्णांक8_t				type;
	uपूर्णांक8_t				data[];
पूर्ण;

#समावेश <trace/events/cachefiles.h>

/*
 * note change of state क्रम daemon
 */
अटल अंतरभूत व्योम cachefiles_state_changed(काष्ठा cachefiles_cache *cache)
अणु
	set_bit(CACHEखाताS_STATE_CHANGED, &cache->flags);
	wake_up_all(&cache->daemon_pollwq);
पूर्ण

/*
 * bind.c
 */
बाह्य पूर्णांक cachefiles_daemon_bind(काष्ठा cachefiles_cache *cache, अक्षर *args);
बाह्य व्योम cachefiles_daemon_unbind(काष्ठा cachefiles_cache *cache);

/*
 * daemon.c
 */
बाह्य स्थिर काष्ठा file_operations cachefiles_daemon_fops;

बाह्य पूर्णांक cachefiles_has_space(काष्ठा cachefiles_cache *cache,
				अचिन्हित fnr, अचिन्हित bnr);

/*
 * पूर्णांकerface.c
 */
बाह्य स्थिर काष्ठा fscache_cache_ops cachefiles_cache_ops;

व्योम cachefiles_put_object(काष्ठा fscache_object *_object,
			   क्रमागत fscache_obj_ref_trace why);

/*
 * key.c
 */
बाह्य अक्षर *cachefiles_cook_key(स्थिर u8 *raw, पूर्णांक keylen, uपूर्णांक8_t type);

/*
 * namei.c
 */
बाह्य व्योम cachefiles_mark_object_inactive(काष्ठा cachefiles_cache *cache,
					    काष्ठा cachefiles_object *object,
					    blkcnt_t i_blocks);
बाह्य पूर्णांक cachefiles_delete_object(काष्ठा cachefiles_cache *cache,
				    काष्ठा cachefiles_object *object);
बाह्य पूर्णांक cachefiles_walk_to_object(काष्ठा cachefiles_object *parent,
				     काष्ठा cachefiles_object *object,
				     स्थिर अक्षर *key,
				     काष्ठा cachefiles_xattr *auxdata);
बाह्य काष्ठा dentry *cachefiles_get_directory(काष्ठा cachefiles_cache *cache,
					       काष्ठा dentry *dir,
					       स्थिर अक्षर *name);

बाह्य पूर्णांक cachefiles_cull(काष्ठा cachefiles_cache *cache, काष्ठा dentry *dir,
			   अक्षर *filename);

बाह्य पूर्णांक cachefiles_check_in_use(काष्ठा cachefiles_cache *cache,
				   काष्ठा dentry *dir, अक्षर *filename);

/*
 * proc.c
 */
#अगर_घोषित CONFIG_CACHEखाताS_HISTOGRAM
बाह्य atomic_t cachefiles_lookup_histogram[HZ];
बाह्य atomic_t cachefiles_सूची_गढ़ो_histogram[HZ];
बाह्य atomic_t cachefiles_create_histogram[HZ];

बाह्य पूर्णांक __init cachefiles_proc_init(व्योम);
बाह्य व्योम cachefiles_proc_cleanup(व्योम);
अटल अंतरभूत
व्योम cachefiles_hist(atomic_t histogram[], अचिन्हित दीर्घ start_jअगर)
अणु
	अचिन्हित दीर्घ jअगर = jअगरfies - start_jअगर;
	अगर (jअगर >= HZ)
		jअगर = HZ - 1;
	atomic_inc(&histogram[jअगर]);
पूर्ण

#अन्यथा
#घोषणा cachefiles_proc_init()		(0)
#घोषणा cachefiles_proc_cleanup()	करो अणुपूर्ण जबतक (0)
#घोषणा cachefiles_hist(hist, start_jअगर) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * rdwr.c
 */
बाह्य पूर्णांक cachefiles_पढ़ो_or_alloc_page(काष्ठा fscache_retrieval *,
					 काष्ठा page *, gfp_t);
बाह्य पूर्णांक cachefiles_पढ़ो_or_alloc_pages(काष्ठा fscache_retrieval *,
					  काष्ठा list_head *, अचिन्हित *,
					  gfp_t);
बाह्य पूर्णांक cachefiles_allocate_page(काष्ठा fscache_retrieval *, काष्ठा page *,
				    gfp_t);
बाह्य पूर्णांक cachefiles_allocate_pages(काष्ठा fscache_retrieval *,
				     काष्ठा list_head *, अचिन्हित *, gfp_t);
बाह्य पूर्णांक cachefiles_ग_लिखो_page(काष्ठा fscache_storage *, काष्ठा page *);
बाह्य व्योम cachefiles_uncache_page(काष्ठा fscache_object *, काष्ठा page *);

/*
 * rdwr2.c
 */
बाह्य पूर्णांक cachefiles_begin_पढ़ो_operation(काष्ठा netfs_पढ़ो_request *,
					   काष्ठा fscache_retrieval *);

/*
 * security.c
 */
बाह्य पूर्णांक cachefiles_get_security_ID(काष्ठा cachefiles_cache *cache);
बाह्य पूर्णांक cachefiles_determine_cache_security(काष्ठा cachefiles_cache *cache,
					       काष्ठा dentry *root,
					       स्थिर काष्ठा cred **_saved_cred);

अटल अंतरभूत व्योम cachefiles_begin_secure(काष्ठा cachefiles_cache *cache,
					   स्थिर काष्ठा cred **_saved_cred)
अणु
	*_saved_cred = override_creds(cache->cache_cred);
पूर्ण

अटल अंतरभूत व्योम cachefiles_end_secure(काष्ठा cachefiles_cache *cache,
					 स्थिर काष्ठा cred *saved_cred)
अणु
	revert_creds(saved_cred);
पूर्ण

/*
 * xattr.c
 */
बाह्य पूर्णांक cachefiles_check_object_type(काष्ठा cachefiles_object *object);
बाह्य पूर्णांक cachefiles_set_object_xattr(काष्ठा cachefiles_object *object,
				       काष्ठा cachefiles_xattr *auxdata);
बाह्य पूर्णांक cachefiles_update_object_xattr(काष्ठा cachefiles_object *object,
					  काष्ठा cachefiles_xattr *auxdata);
बाह्य पूर्णांक cachefiles_check_auxdata(काष्ठा cachefiles_object *object);
बाह्य पूर्णांक cachefiles_check_object_xattr(काष्ठा cachefiles_object *object,
					 काष्ठा cachefiles_xattr *auxdata);
बाह्य पूर्णांक cachefiles_हटाओ_object_xattr(काष्ठा cachefiles_cache *cache,
					  काष्ठा dentry *dentry);


/*
 * error handling
 */

#घोषणा cachefiles_io_error(___cache, FMT, ...)		\
करो अणु							\
	pr_err("I/O Error: " FMT"\n", ##__VA_ARGS__);	\
	fscache_io_error(&(___cache)->cache);		\
	set_bit(CACHEखाताS_DEAD, &(___cache)->flags);	\
पूर्ण जबतक (0)

#घोषणा cachefiles_io_error_obj(object, FMT, ...)			\
करो अणु									\
	काष्ठा cachefiles_cache *___cache;				\
									\
	___cache = container_of((object)->fscache.cache,		\
				काष्ठा cachefiles_cache, cache);	\
	cachefiles_io_error(___cache, FMT, ##__VA_ARGS__);		\
पूर्ण जबतक (0)


/*
 * debug tracing
 */
#घोषणा dbgprपूर्णांकk(FMT, ...) \
	prपूर्णांकk(KERN_DEBUG "[%-6.6s] "FMT"\n", current->comm, ##__VA_ARGS__)

#घोषणा kenter(FMT, ...) dbgprपूर्णांकk("==> %s("FMT")", __func__, ##__VA_ARGS__)
#घोषणा kleave(FMT, ...) dbgprपूर्णांकk("<== %s()"FMT"", __func__, ##__VA_ARGS__)
#घोषणा kdebug(FMT, ...) dbgprपूर्णांकk(FMT, ##__VA_ARGS__)


#अगर defined(__KDEBUG)
#घोषणा _enter(FMT, ...) kenter(FMT, ##__VA_ARGS__)
#घोषणा _leave(FMT, ...) kleave(FMT, ##__VA_ARGS__)
#घोषणा _debug(FMT, ...) kdebug(FMT, ##__VA_ARGS__)

#या_अगर defined(CONFIG_CACHEखाताS_DEBUG)
#घोषणा _enter(FMT, ...)				\
करो अणु							\
	अगर (cachefiles_debug & CACHEखाताS_DEBUG_KENTER)	\
		kenter(FMT, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा _leave(FMT, ...)				\
करो अणु							\
	अगर (cachefiles_debug & CACHEखाताS_DEBUG_KLEAVE)	\
		kleave(FMT, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा _debug(FMT, ...)				\
करो अणु							\
	अगर (cachefiles_debug & CACHEखाताS_DEBUG_KDEBUG)	\
		kdebug(FMT, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

#अन्यथा
#घोषणा _enter(FMT, ...) no_prपूर्णांकk("==> %s("FMT")", __func__, ##__VA_ARGS__)
#घोषणा _leave(FMT, ...) no_prपूर्णांकk("<== %s()"FMT"", __func__, ##__VA_ARGS__)
#घोषणा _debug(FMT, ...) no_prपूर्णांकk(FMT, ##__VA_ARGS__)
#पूर्ण_अगर

#अगर 1 /* defined(__KDEBUGALL) */

#घोषणा ASSERT(X)							\
करो अणु									\
	अगर (unlikely(!(X))) अणु						\
		pr_err("\n");						\
		pr_err("Assertion failed\n");		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा ASSERTCMP(X, OP, Y)						\
करो अणु									\
	अगर (unlikely(!((X) OP (Y)))) अणु					\
		pr_err("\n");						\
		pr_err("Assertion failed\n");		\
		pr_err("%lx " #OP " %lx is false\n",			\
		       (अचिन्हित दीर्घ)(X), (अचिन्हित दीर्घ)(Y));		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा ASSERTIF(C, X)							\
करो अणु									\
	अगर (unlikely((C) && !(X))) अणु					\
		pr_err("\n");						\
		pr_err("Assertion failed\n");		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा ASSERTIFCMP(C, X, OP, Y)					\
करो अणु									\
	अगर (unlikely((C) && !((X) OP (Y)))) अणु				\
		pr_err("\n");						\
		pr_err("Assertion failed\n");		\
		pr_err("%lx " #OP " %lx is false\n",			\
		       (अचिन्हित दीर्घ)(X), (अचिन्हित दीर्घ)(Y));		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#अन्यथा

#घोषणा ASSERT(X)			करो अणुपूर्ण जबतक (0)
#घोषणा ASSERTCMP(X, OP, Y)		करो अणुपूर्ण जबतक (0)
#घोषणा ASSERTIF(C, X)			करो अणुपूर्ण जबतक (0)
#घोषणा ASSERTIFCMP(C, X, OP, Y)	करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर
