<शैली गुरु>
/*
 * Open file cache.
 *
 * (c) 2015 - Jeff Layton <jeff.layton@primarydata.com>
 */

#समावेश <linux/hash.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/sched.h>
#समावेश <linux/list_lru.h>
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/seq_file.h>

#समावेश "vfs.h"
#समावेश "nfsd.h"
#समावेश "nfsfh.h"
#समावेश "netns.h"
#समावेश "filecache.h"
#समावेश "trace.h"

#घोषणा NFSDDBG_FACILITY	NFSDDBG_FH

/* FIXME: dynamically size this क्रम the machine somehow? */
#घोषणा NFSD_खाता_HASH_BITS                   12
#घोषणा NFSD_खाता_HASH_SIZE                  (1 << NFSD_खाता_HASH_BITS)
#घोषणा NFSD_LAUNDRETTE_DELAY		     (2 * HZ)

#घोषणा NFSD_खाता_SHUTDOWN		     (1)
#घोषणा NFSD_खाता_LRU_THRESHOLD		     (4096UL)
#घोषणा NFSD_खाता_LRU_LIMIT		     (NFSD_खाता_LRU_THRESHOLD << 2)

/* We only care about NFSD_MAY_READ/WRITE क्रम this cache */
#घोषणा NFSD_खाता_MAY_MASK	(NFSD_MAY_READ|NFSD_MAY_WRITE)

काष्ठा nfsd_fcache_bucket अणु
	काष्ठा hlist_head	nfb_head;
	spinlock_t		nfb_lock;
	अचिन्हित पूर्णांक		nfb_count;
	अचिन्हित पूर्णांक		nfb_maxcount;
पूर्ण;

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, nfsd_file_cache_hits);

काष्ठा nfsd_fcache_disposal अणु
	काष्ठा list_head list;
	काष्ठा work_काष्ठा work;
	काष्ठा net *net;
	spinlock_t lock;
	काष्ठा list_head मुक्तme;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *nfsd_filecache_wq __पढ़ो_mostly;

अटल काष्ठा kmem_cache		*nfsd_file_slab;
अटल काष्ठा kmem_cache		*nfsd_file_mark_slab;
अटल काष्ठा nfsd_fcache_bucket	*nfsd_file_hashtbl;
अटल काष्ठा list_lru			nfsd_file_lru;
अटल दीर्घ				nfsd_file_lru_flags;
अटल काष्ठा fsnotअगरy_group		*nfsd_file_fsnotअगरy_group;
अटल atomic_दीर्घ_t			nfsd_filecache_count;
अटल काष्ठा delayed_work		nfsd_filecache_laundrette;
अटल DEFINE_SPINLOCK(laundrette_lock);
अटल LIST_HEAD(laundrettes);

अटल व्योम nfsd_file_gc(व्योम);

अटल व्योम
nfsd_file_schedule_laundrette(व्योम)
अणु
	दीर्घ count = atomic_दीर्घ_पढ़ो(&nfsd_filecache_count);

	अगर (count == 0 || test_bit(NFSD_खाता_SHUTDOWN, &nfsd_file_lru_flags))
		वापस;

	queue_delayed_work(प्रणाली_wq, &nfsd_filecache_laundrette,
			NFSD_LAUNDRETTE_DELAY);
पूर्ण

अटल व्योम
nfsd_file_slab_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा nfsd_file *nf = container_of(rcu, काष्ठा nfsd_file, nf_rcu);

	put_cred(nf->nf_cred);
	kmem_cache_मुक्त(nfsd_file_slab, nf);
पूर्ण

अटल व्योम
nfsd_file_mark_मुक्त(काष्ठा fsnotअगरy_mark *mark)
अणु
	काष्ठा nfsd_file_mark *nfm = container_of(mark, काष्ठा nfsd_file_mark,
						  nfm_mark);

	kmem_cache_मुक्त(nfsd_file_mark_slab, nfm);
पूर्ण

अटल काष्ठा nfsd_file_mark *
nfsd_file_mark_get(काष्ठा nfsd_file_mark *nfm)
अणु
	अगर (!refcount_inc_not_zero(&nfm->nfm_ref))
		वापस शून्य;
	वापस nfm;
पूर्ण

अटल व्योम
nfsd_file_mark_put(काष्ठा nfsd_file_mark *nfm)
अणु
	अगर (refcount_dec_and_test(&nfm->nfm_ref)) अणु
		fsnotअगरy_destroy_mark(&nfm->nfm_mark, nfsd_file_fsnotअगरy_group);
		fsnotअगरy_put_mark(&nfm->nfm_mark);
	पूर्ण
पूर्ण

अटल काष्ठा nfsd_file_mark *
nfsd_file_mark_find_or_create(काष्ठा nfsd_file *nf)
अणु
	पूर्णांक			err;
	काष्ठा fsnotअगरy_mark	*mark;
	काष्ठा nfsd_file_mark	*nfm = शून्य, *new;
	काष्ठा inode *inode = nf->nf_inode;

	करो अणु
		mutex_lock(&nfsd_file_fsnotअगरy_group->mark_mutex);
		mark = fsnotअगरy_find_mark(&inode->i_fsnotअगरy_marks,
				nfsd_file_fsnotअगरy_group);
		अगर (mark) अणु
			nfm = nfsd_file_mark_get(container_of(mark,
						 काष्ठा nfsd_file_mark,
						 nfm_mark));
			mutex_unlock(&nfsd_file_fsnotअगरy_group->mark_mutex);
			अगर (nfm) अणु
				fsnotअगरy_put_mark(mark);
				अवरोध;
			पूर्ण
			/* Aव्योम soft lockup race with nfsd_file_mark_put() */
			fsnotअगरy_destroy_mark(mark, nfsd_file_fsnotअगरy_group);
			fsnotअगरy_put_mark(mark);
		पूर्ण अन्यथा
			mutex_unlock(&nfsd_file_fsnotअगरy_group->mark_mutex);

		/* allocate a new nfm */
		new = kmem_cache_alloc(nfsd_file_mark_slab, GFP_KERNEL);
		अगर (!new)
			वापस शून्य;
		fsnotअगरy_init_mark(&new->nfm_mark, nfsd_file_fsnotअगरy_group);
		new->nfm_mark.mask = FS_ATTRIB|FS_DELETE_SELF;
		refcount_set(&new->nfm_ref, 1);

		err = fsnotअगरy_add_inode_mark(&new->nfm_mark, inode, 0);

		/*
		 * If the add was successful, then वापस the object.
		 * Otherwise, we need to put the reference we hold on the
		 * nfm_mark. The fsnotअगरy code will take a reference and put
		 * it on failure, so we can't just free it directly. It's also
		 * not safe to call fsnotअगरy_destroy_mark on it as the
		 * mark->group will be शून्य. Thus, we can't let the nfm_ref
		 * counter drive the deकाष्ठाion at this poपूर्णांक.
		 */
		अगर (likely(!err))
			nfm = new;
		अन्यथा
			fsnotअगरy_put_mark(&new->nfm_mark);
	पूर्ण जबतक (unlikely(err == -EEXIST));

	वापस nfm;
पूर्ण

अटल काष्ठा nfsd_file *
nfsd_file_alloc(काष्ठा inode *inode, अचिन्हित पूर्णांक may, अचिन्हित पूर्णांक hashval,
		काष्ठा net *net)
अणु
	काष्ठा nfsd_file *nf;

	nf = kmem_cache_alloc(nfsd_file_slab, GFP_KERNEL);
	अगर (nf) अणु
		INIT_HLIST_NODE(&nf->nf_node);
		INIT_LIST_HEAD(&nf->nf_lru);
		nf->nf_file = शून्य;
		nf->nf_cred = get_current_cred();
		nf->nf_net = net;
		nf->nf_flags = 0;
		nf->nf_inode = inode;
		nf->nf_hashval = hashval;
		refcount_set(&nf->nf_ref, 1);
		nf->nf_may = may & NFSD_खाता_MAY_MASK;
		अगर (may & NFSD_MAY_NOT_BREAK_LEASE) अणु
			अगर (may & NFSD_MAY_WRITE)
				__set_bit(NFSD_खाता_BREAK_WRITE, &nf->nf_flags);
			अगर (may & NFSD_MAY_READ)
				__set_bit(NFSD_खाता_BREAK_READ, &nf->nf_flags);
		पूर्ण
		nf->nf_mark = शून्य;
		init_rwsem(&nf->nf_rwsem);
		trace_nfsd_file_alloc(nf);
	पूर्ण
	वापस nf;
पूर्ण

अटल bool
nfsd_file_मुक्त(काष्ठा nfsd_file *nf)
अणु
	bool flush = false;

	trace_nfsd_file_put_final(nf);
	अगर (nf->nf_mark)
		nfsd_file_mark_put(nf->nf_mark);
	अगर (nf->nf_file) अणु
		get_file(nf->nf_file);
		filp_बंद(nf->nf_file, शून्य);
		fput(nf->nf_file);
		flush = true;
	पूर्ण
	call_rcu(&nf->nf_rcu, nfsd_file_slab_मुक्त);
	वापस flush;
पूर्ण

अटल bool
nfsd_file_check_ग_लिखोback(काष्ठा nfsd_file *nf)
अणु
	काष्ठा file *file = nf->nf_file;
	काष्ठा address_space *mapping;

	अगर (!file || !(file->f_mode & FMODE_WRITE))
		वापस false;
	mapping = file->f_mapping;
	वापस mapping_tagged(mapping, PAGECACHE_TAG_सूचीTY) ||
		mapping_tagged(mapping, PAGECACHE_TAG_WRITEBACK);
पूर्ण

अटल पूर्णांक
nfsd_file_check_ग_लिखो_error(काष्ठा nfsd_file *nf)
अणु
	काष्ठा file *file = nf->nf_file;

	अगर (!file || !(file->f_mode & FMODE_WRITE))
		वापस 0;
	वापस filemap_check_wb_err(file->f_mapping, READ_ONCE(file->f_wb_err));
पूर्ण

अटल व्योम
nfsd_file_करो_unhash(काष्ठा nfsd_file *nf)
अणु
	lockdep_निश्चित_held(&nfsd_file_hashtbl[nf->nf_hashval].nfb_lock);

	trace_nfsd_file_unhash(nf);

	अगर (nfsd_file_check_ग_लिखो_error(nf))
		nfsd_reset_boot_verअगरier(net_generic(nf->nf_net, nfsd_net_id));
	--nfsd_file_hashtbl[nf->nf_hashval].nfb_count;
	hlist_del_rcu(&nf->nf_node);
	atomic_दीर्घ_dec(&nfsd_filecache_count);
पूर्ण

अटल bool
nfsd_file_unhash(काष्ठा nfsd_file *nf)
अणु
	अगर (test_and_clear_bit(NFSD_खाता_HASHED, &nf->nf_flags)) अणु
		nfsd_file_करो_unhash(nf);
		अगर (!list_empty(&nf->nf_lru))
			list_lru_del(&nfsd_file_lru, &nf->nf_lru);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Return true अगर the file was unhashed.
 */
अटल bool
nfsd_file_unhash_and_release_locked(काष्ठा nfsd_file *nf, काष्ठा list_head *dispose)
अणु
	lockdep_निश्चित_held(&nfsd_file_hashtbl[nf->nf_hashval].nfb_lock);

	trace_nfsd_file_unhash_and_release_locked(nf);
	अगर (!nfsd_file_unhash(nf))
		वापस false;
	/* keep final reference क्रम nfsd_file_lru_dispose */
	अगर (refcount_dec_not_one(&nf->nf_ref))
		वापस true;

	list_add(&nf->nf_lru, dispose);
	वापस true;
पूर्ण

अटल व्योम
nfsd_file_put_noref(काष्ठा nfsd_file *nf)
अणु
	trace_nfsd_file_put(nf);

	अगर (refcount_dec_and_test(&nf->nf_ref)) अणु
		WARN_ON(test_bit(NFSD_खाता_HASHED, &nf->nf_flags));
		nfsd_file_मुक्त(nf);
	पूर्ण
पूर्ण

व्योम
nfsd_file_put(काष्ठा nfsd_file *nf)
अणु
	bool is_hashed;

	set_bit(NFSD_खाता_REFERENCED, &nf->nf_flags);
	अगर (refcount_पढ़ो(&nf->nf_ref) > 2 || !nf->nf_file) अणु
		nfsd_file_put_noref(nf);
		वापस;
	पूर्ण

	filemap_flush(nf->nf_file->f_mapping);
	is_hashed = test_bit(NFSD_खाता_HASHED, &nf->nf_flags) != 0;
	nfsd_file_put_noref(nf);
	अगर (is_hashed)
		nfsd_file_schedule_laundrette();
	अगर (atomic_दीर्घ_पढ़ो(&nfsd_filecache_count) >= NFSD_खाता_LRU_LIMIT)
		nfsd_file_gc();
पूर्ण

काष्ठा nfsd_file *
nfsd_file_get(काष्ठा nfsd_file *nf)
अणु
	अगर (likely(refcount_inc_not_zero(&nf->nf_ref)))
		वापस nf;
	वापस शून्य;
पूर्ण

अटल व्योम
nfsd_file_dispose_list(काष्ठा list_head *dispose)
अणु
	काष्ठा nfsd_file *nf;

	जबतक(!list_empty(dispose)) अणु
		nf = list_first_entry(dispose, काष्ठा nfsd_file, nf_lru);
		list_del(&nf->nf_lru);
		nfsd_file_put_noref(nf);
	पूर्ण
पूर्ण

अटल व्योम
nfsd_file_dispose_list_sync(काष्ठा list_head *dispose)
अणु
	bool flush = false;
	काष्ठा nfsd_file *nf;

	जबतक(!list_empty(dispose)) अणु
		nf = list_first_entry(dispose, काष्ठा nfsd_file, nf_lru);
		list_del(&nf->nf_lru);
		अगर (!refcount_dec_and_test(&nf->nf_ref))
			जारी;
		अगर (nfsd_file_मुक्त(nf))
			flush = true;
	पूर्ण
	अगर (flush)
		flush_delayed_fput();
पूर्ण

अटल व्योम
nfsd_file_list_हटाओ_disposal(काष्ठा list_head *dst,
		काष्ठा nfsd_fcache_disposal *l)
अणु
	spin_lock(&l->lock);
	list_splice_init(&l->मुक्तme, dst);
	spin_unlock(&l->lock);
पूर्ण

अटल व्योम
nfsd_file_list_add_disposal(काष्ठा list_head *files, काष्ठा net *net)
अणु
	काष्ठा nfsd_fcache_disposal *l;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(l, &laundrettes, list) अणु
		अगर (l->net == net) अणु
			spin_lock(&l->lock);
			list_splice_tail_init(files, &l->मुक्तme);
			spin_unlock(&l->lock);
			queue_work(nfsd_filecache_wq, &l->work);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
nfsd_file_list_add_pernet(काष्ठा list_head *dst, काष्ठा list_head *src,
		काष्ठा net *net)
अणु
	काष्ठा nfsd_file *nf, *पंचांगp;

	list_क्रम_each_entry_safe(nf, पंचांगp, src, nf_lru) अणु
		अगर (nf->nf_net == net)
			list_move_tail(&nf->nf_lru, dst);
	पूर्ण
पूर्ण

अटल व्योम
nfsd_file_dispose_list_delayed(काष्ठा list_head *dispose)
अणु
	LIST_HEAD(list);
	काष्ठा nfsd_file *nf;

	जबतक(!list_empty(dispose)) अणु
		nf = list_first_entry(dispose, काष्ठा nfsd_file, nf_lru);
		nfsd_file_list_add_pernet(&list, dispose, nf->nf_net);
		nfsd_file_list_add_disposal(&list, nf->nf_net);
	पूर्ण
पूर्ण

/*
 * Note this can deadlock with nfsd_file_cache_purge.
 */
अटल क्रमागत lru_status
nfsd_file_lru_cb(काष्ठा list_head *item, काष्ठा list_lru_one *lru,
		 spinlock_t *lock, व्योम *arg)
	__releases(lock)
	__acquires(lock)
अणु
	काष्ठा list_head *head = arg;
	काष्ठा nfsd_file *nf = list_entry(item, काष्ठा nfsd_file, nf_lru);

	/*
	 * Do a lockless refcount check. The hashtable holds one reference, so
	 * we look to see अगर anything अन्यथा has a reference, or अगर any have
	 * been put since the shrinker last ran. Those करोn't get unhashed and
	 * released.
	 *
	 * Note that in the put path, we set the flag and then decrement the
	 * counter. Here we check the counter and then test and clear the flag.
	 * That order is deliberate to ensure that we can करो this locklessly.
	 */
	अगर (refcount_पढ़ो(&nf->nf_ref) > 1)
		जाओ out_skip;

	/*
	 * Don't throw out files that are still undergoing I/O or
	 * that have uncleared errors pending.
	 */
	अगर (nfsd_file_check_ग_लिखोback(nf))
		जाओ out_skip;

	अगर (test_and_clear_bit(NFSD_खाता_REFERENCED, &nf->nf_flags))
		जाओ out_skip;

	अगर (!test_and_clear_bit(NFSD_खाता_HASHED, &nf->nf_flags))
		जाओ out_skip;

	list_lru_isolate_move(lru, &nf->nf_lru, head);
	वापस LRU_REMOVED;
out_skip:
	वापस LRU_SKIP;
पूर्ण

अटल अचिन्हित दीर्घ
nfsd_file_lru_walk_list(काष्ठा shrink_control *sc)
अणु
	LIST_HEAD(head);
	काष्ठा nfsd_file *nf;
	अचिन्हित दीर्घ ret;

	अगर (sc)
		ret = list_lru_shrink_walk(&nfsd_file_lru, sc,
				nfsd_file_lru_cb, &head);
	अन्यथा
		ret = list_lru_walk(&nfsd_file_lru,
				nfsd_file_lru_cb,
				&head, दीर्घ_उच्च);
	list_क्रम_each_entry(nf, &head, nf_lru) अणु
		spin_lock(&nfsd_file_hashtbl[nf->nf_hashval].nfb_lock);
		nfsd_file_करो_unhash(nf);
		spin_unlock(&nfsd_file_hashtbl[nf->nf_hashval].nfb_lock);
	पूर्ण
	nfsd_file_dispose_list_delayed(&head);
	वापस ret;
पूर्ण

अटल व्योम
nfsd_file_gc(व्योम)
अणु
	nfsd_file_lru_walk_list(शून्य);
पूर्ण

अटल व्योम
nfsd_file_gc_worker(काष्ठा work_काष्ठा *work)
अणु
	nfsd_file_gc();
	nfsd_file_schedule_laundrette();
पूर्ण

अटल अचिन्हित दीर्घ
nfsd_file_lru_count(काष्ठा shrinker *s, काष्ठा shrink_control *sc)
अणु
	वापस list_lru_count(&nfsd_file_lru);
पूर्ण

अटल अचिन्हित दीर्घ
nfsd_file_lru_scan(काष्ठा shrinker *s, काष्ठा shrink_control *sc)
अणु
	वापस nfsd_file_lru_walk_list(sc);
पूर्ण

अटल काष्ठा shrinker	nfsd_file_shrinker = अणु
	.scan_objects = nfsd_file_lru_scan,
	.count_objects = nfsd_file_lru_count,
	.seeks = 1,
पूर्ण;

अटल व्योम
__nfsd_file_बंद_inode(काष्ठा inode *inode, अचिन्हित पूर्णांक hashval,
			काष्ठा list_head *dispose)
अणु
	काष्ठा nfsd_file	*nf;
	काष्ठा hlist_node	*पंचांगp;

	spin_lock(&nfsd_file_hashtbl[hashval].nfb_lock);
	hlist_क्रम_each_entry_safe(nf, पंचांगp, &nfsd_file_hashtbl[hashval].nfb_head, nf_node) अणु
		अगर (inode == nf->nf_inode)
			nfsd_file_unhash_and_release_locked(nf, dispose);
	पूर्ण
	spin_unlock(&nfsd_file_hashtbl[hashval].nfb_lock);
पूर्ण

/**
 * nfsd_file_बंद_inode_sync - attempt to क्रमcibly बंद a nfsd_file
 * @inode: inode of the file to attempt to हटाओ
 *
 * Walk the whole hash bucket, looking क्रम any files that correspond to "inode".
 * If any करो, then unhash them and put the hashtable reference to them and
 * destroy any that had their last reference put. Also ensure that any of the
 * ख_माला_दो also have their final __fput करोne as well.
 */
व्योम
nfsd_file_बंद_inode_sync(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक		hashval = (अचिन्हित पूर्णांक)hash_दीर्घ(inode->i_ino,
						NFSD_खाता_HASH_BITS);
	LIST_HEAD(dispose);

	__nfsd_file_बंद_inode(inode, hashval, &dispose);
	trace_nfsd_file_बंद_inode_sync(inode, hashval, !list_empty(&dispose));
	nfsd_file_dispose_list_sync(&dispose);
पूर्ण

/**
 * nfsd_file_बंद_inode_sync - attempt to क्रमcibly बंद a nfsd_file
 * @inode: inode of the file to attempt to हटाओ
 *
 * Walk the whole hash bucket, looking क्रम any files that correspond to "inode".
 * If any करो, then unhash them and put the hashtable reference to them and
 * destroy any that had their last reference put.
 */
अटल व्योम
nfsd_file_बंद_inode(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक		hashval = (अचिन्हित पूर्णांक)hash_दीर्घ(inode->i_ino,
						NFSD_खाता_HASH_BITS);
	LIST_HEAD(dispose);

	__nfsd_file_बंद_inode(inode, hashval, &dispose);
	trace_nfsd_file_बंद_inode(inode, hashval, !list_empty(&dispose));
	nfsd_file_dispose_list_delayed(&dispose);
पूर्ण

/**
 * nfsd_file_delayed_बंद - बंद unused nfsd_files
 * @work: dummy
 *
 * Walk the LRU list and बंद any entries that have not been used since
 * the last scan.
 *
 * Note this can deadlock with nfsd_file_cache_purge.
 */
अटल व्योम
nfsd_file_delayed_बंद(काष्ठा work_काष्ठा *work)
अणु
	LIST_HEAD(head);
	काष्ठा nfsd_fcache_disposal *l = container_of(work,
			काष्ठा nfsd_fcache_disposal, work);

	nfsd_file_list_हटाओ_disposal(&head, l);
	nfsd_file_dispose_list(&head);
पूर्ण

अटल पूर्णांक
nfsd_file_lease_notअगरier_call(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ arg,
			    व्योम *data)
अणु
	काष्ठा file_lock *fl = data;

	/* Only बंद files क्रम F_SETLEASE leases */
	अगर (fl->fl_flags & FL_LEASE)
		nfsd_file_बंद_inode_sync(file_inode(fl->fl_file));
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block nfsd_file_lease_notअगरier = अणु
	.notअगरier_call = nfsd_file_lease_notअगरier_call,
पूर्ण;

अटल पूर्णांक
nfsd_file_fsnotअगरy_handle_event(काष्ठा fsnotअगरy_mark *mark, u32 mask,
				काष्ठा inode *inode, काष्ठा inode *dir,
				स्थिर काष्ठा qstr *name, u32 cookie)
अणु
	trace_nfsd_file_fsnotअगरy_handle_event(inode, mask);

	/* Should be no marks on non-regular files */
	अगर (!S_ISREG(inode->i_mode)) अणु
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण

	/* करोn't बंद files अगर this was not the last link */
	अगर (mask & FS_ATTRIB) अणु
		अगर (inode->i_nlink)
			वापस 0;
	पूर्ण

	nfsd_file_बंद_inode(inode);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा fsnotअगरy_ops nfsd_file_fsnotअगरy_ops = अणु
	.handle_inode_event = nfsd_file_fsnotअगरy_handle_event,
	.मुक्त_mark = nfsd_file_mark_मुक्त,
पूर्ण;

पूर्णांक
nfsd_file_cache_init(व्योम)
अणु
	पूर्णांक		ret = -ENOMEM;
	अचिन्हित पूर्णांक	i;

	clear_bit(NFSD_खाता_SHUTDOWN, &nfsd_file_lru_flags);

	अगर (nfsd_file_hashtbl)
		वापस 0;

	nfsd_filecache_wq = alloc_workqueue("nfsd_filecache", 0, 0);
	अगर (!nfsd_filecache_wq)
		जाओ out;

	nfsd_file_hashtbl = kसुस्मृति(NFSD_खाता_HASH_SIZE,
				माप(*nfsd_file_hashtbl), GFP_KERNEL);
	अगर (!nfsd_file_hashtbl) अणु
		pr_err("nfsd: unable to allocate nfsd_file_hashtbl\n");
		जाओ out_err;
	पूर्ण

	nfsd_file_slab = kmem_cache_create("nfsd_file",
				माप(काष्ठा nfsd_file), 0, 0, शून्य);
	अगर (!nfsd_file_slab) अणु
		pr_err("nfsd: unable to create nfsd_file_slab\n");
		जाओ out_err;
	पूर्ण

	nfsd_file_mark_slab = kmem_cache_create("nfsd_file_mark",
					माप(काष्ठा nfsd_file_mark), 0, 0, शून्य);
	अगर (!nfsd_file_mark_slab) अणु
		pr_err("nfsd: unable to create nfsd_file_mark_slab\n");
		जाओ out_err;
	पूर्ण


	ret = list_lru_init(&nfsd_file_lru);
	अगर (ret) अणु
		pr_err("nfsd: failed to init nfsd_file_lru: %d\n", ret);
		जाओ out_err;
	पूर्ण

	ret = रेजिस्टर_shrinker(&nfsd_file_shrinker);
	अगर (ret) अणु
		pr_err("nfsd: failed to register nfsd_file_shrinker: %d\n", ret);
		जाओ out_lru;
	पूर्ण

	ret = lease_रेजिस्टर_notअगरier(&nfsd_file_lease_notअगरier);
	अगर (ret) अणु
		pr_err("nfsd: unable to register lease notifier: %d\n", ret);
		जाओ out_shrinker;
	पूर्ण

	nfsd_file_fsnotअगरy_group = fsnotअगरy_alloc_group(&nfsd_file_fsnotअगरy_ops);
	अगर (IS_ERR(nfsd_file_fsnotअगरy_group)) अणु
		pr_err("nfsd: unable to create fsnotify group: %ld\n",
			PTR_ERR(nfsd_file_fsnotअगरy_group));
		ret = PTR_ERR(nfsd_file_fsnotअगरy_group);
		nfsd_file_fsnotअगरy_group = शून्य;
		जाओ out_notअगरier;
	पूर्ण

	क्रम (i = 0; i < NFSD_खाता_HASH_SIZE; i++) अणु
		INIT_HLIST_HEAD(&nfsd_file_hashtbl[i].nfb_head);
		spin_lock_init(&nfsd_file_hashtbl[i].nfb_lock);
	पूर्ण

	INIT_DELAYED_WORK(&nfsd_filecache_laundrette, nfsd_file_gc_worker);
out:
	वापस ret;
out_notअगरier:
	lease_unरेजिस्टर_notअगरier(&nfsd_file_lease_notअगरier);
out_shrinker:
	unरेजिस्टर_shrinker(&nfsd_file_shrinker);
out_lru:
	list_lru_destroy(&nfsd_file_lru);
out_err:
	kmem_cache_destroy(nfsd_file_slab);
	nfsd_file_slab = शून्य;
	kmem_cache_destroy(nfsd_file_mark_slab);
	nfsd_file_mark_slab = शून्य;
	kमुक्त(nfsd_file_hashtbl);
	nfsd_file_hashtbl = शून्य;
	destroy_workqueue(nfsd_filecache_wq);
	nfsd_filecache_wq = शून्य;
	जाओ out;
पूर्ण

/*
 * Note this can deadlock with nfsd_file_lru_cb.
 */
व्योम
nfsd_file_cache_purge(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक		i;
	काष्ठा nfsd_file	*nf;
	काष्ठा hlist_node	*next;
	LIST_HEAD(dispose);
	bool del;

	अगर (!nfsd_file_hashtbl)
		वापस;

	क्रम (i = 0; i < NFSD_खाता_HASH_SIZE; i++) अणु
		काष्ठा nfsd_fcache_bucket *nfb = &nfsd_file_hashtbl[i];

		spin_lock(&nfb->nfb_lock);
		hlist_क्रम_each_entry_safe(nf, next, &nfb->nfb_head, nf_node) अणु
			अगर (net && nf->nf_net != net)
				जारी;
			del = nfsd_file_unhash_and_release_locked(nf, &dispose);

			/*
			 * Deadlock detected! Something marked this entry as
			 * unhased, but hasn't हटाओd it from the hash list.
			 */
			WARN_ON_ONCE(!del);
		पूर्ण
		spin_unlock(&nfb->nfb_lock);
		nfsd_file_dispose_list(&dispose);
	पूर्ण
पूर्ण

अटल काष्ठा nfsd_fcache_disposal *
nfsd_alloc_fcache_disposal(काष्ठा net *net)
अणु
	काष्ठा nfsd_fcache_disposal *l;

	l = kदो_स्मृति(माप(*l), GFP_KERNEL);
	अगर (!l)
		वापस शून्य;
	INIT_WORK(&l->work, nfsd_file_delayed_बंद);
	l->net = net;
	spin_lock_init(&l->lock);
	INIT_LIST_HEAD(&l->मुक्तme);
	वापस l;
पूर्ण

अटल व्योम
nfsd_मुक्त_fcache_disposal(काष्ठा nfsd_fcache_disposal *l)
अणु
	rcu_assign_poपूर्णांकer(l->net, शून्य);
	cancel_work_sync(&l->work);
	nfsd_file_dispose_list(&l->मुक्तme);
	kमुक्त_rcu(l, rcu);
पूर्ण

अटल व्योम
nfsd_add_fcache_disposal(काष्ठा nfsd_fcache_disposal *l)
अणु
	spin_lock(&laundrette_lock);
	list_add_tail_rcu(&l->list, &laundrettes);
	spin_unlock(&laundrette_lock);
पूर्ण

अटल व्योम
nfsd_del_fcache_disposal(काष्ठा nfsd_fcache_disposal *l)
अणु
	spin_lock(&laundrette_lock);
	list_del_rcu(&l->list);
	spin_unlock(&laundrette_lock);
पूर्ण

अटल पूर्णांक
nfsd_alloc_fcache_disposal_net(काष्ठा net *net)
अणु
	काष्ठा nfsd_fcache_disposal *l;

	l = nfsd_alloc_fcache_disposal(net);
	अगर (!l)
		वापस -ENOMEM;
	nfsd_add_fcache_disposal(l);
	वापस 0;
पूर्ण

अटल व्योम
nfsd_मुक्त_fcache_disposal_net(काष्ठा net *net)
अणु
	काष्ठा nfsd_fcache_disposal *l;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(l, &laundrettes, list) अणु
		अगर (l->net != net)
			जारी;
		nfsd_del_fcache_disposal(l);
		rcu_पढ़ो_unlock();
		nfsd_मुक्त_fcache_disposal(l);
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक
nfsd_file_cache_start_net(काष्ठा net *net)
अणु
	वापस nfsd_alloc_fcache_disposal_net(net);
पूर्ण

व्योम
nfsd_file_cache_shutकरोwn_net(काष्ठा net *net)
अणु
	nfsd_file_cache_purge(net);
	nfsd_मुक्त_fcache_disposal_net(net);
पूर्ण

व्योम
nfsd_file_cache_shutकरोwn(व्योम)
अणु
	set_bit(NFSD_खाता_SHUTDOWN, &nfsd_file_lru_flags);

	lease_unरेजिस्टर_notअगरier(&nfsd_file_lease_notअगरier);
	unरेजिस्टर_shrinker(&nfsd_file_shrinker);
	/*
	 * make sure all callers of nfsd_file_lru_cb are करोne beक्रमe
	 * calling nfsd_file_cache_purge
	 */
	cancel_delayed_work_sync(&nfsd_filecache_laundrette);
	nfsd_file_cache_purge(शून्य);
	list_lru_destroy(&nfsd_file_lru);
	rcu_barrier();
	fsnotअगरy_put_group(nfsd_file_fsnotअगरy_group);
	nfsd_file_fsnotअगरy_group = शून्य;
	kmem_cache_destroy(nfsd_file_slab);
	nfsd_file_slab = शून्य;
	fsnotअगरy_रुको_marks_destroyed();
	kmem_cache_destroy(nfsd_file_mark_slab);
	nfsd_file_mark_slab = शून्य;
	kमुक्त(nfsd_file_hashtbl);
	nfsd_file_hashtbl = शून्य;
	destroy_workqueue(nfsd_filecache_wq);
	nfsd_filecache_wq = शून्य;
पूर्ण

अटल bool
nfsd_match_cred(स्थिर काष्ठा cred *c1, स्थिर काष्ठा cred *c2)
अणु
	पूर्णांक i;

	अगर (!uid_eq(c1->fsuid, c2->fsuid))
		वापस false;
	अगर (!gid_eq(c1->fsgid, c2->fsgid))
		वापस false;
	अगर (c1->group_info == शून्य || c2->group_info == शून्य)
		वापस c1->group_info == c2->group_info;
	अगर (c1->group_info->ngroups != c2->group_info->ngroups)
		वापस false;
	क्रम (i = 0; i < c1->group_info->ngroups; i++) अणु
		अगर (!gid_eq(c1->group_info->gid[i], c2->group_info->gid[i]))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल काष्ठा nfsd_file *
nfsd_file_find_locked(काष्ठा inode *inode, अचिन्हित पूर्णांक may_flags,
			अचिन्हित पूर्णांक hashval, काष्ठा net *net)
अणु
	काष्ठा nfsd_file *nf;
	अचिन्हित अक्षर need = may_flags & NFSD_खाता_MAY_MASK;

	hlist_क्रम_each_entry_rcu(nf, &nfsd_file_hashtbl[hashval].nfb_head,
				 nf_node, lockdep_is_held(&nfsd_file_hashtbl[hashval].nfb_lock)) अणु
		अगर (nf->nf_may != need)
			जारी;
		अगर (nf->nf_inode != inode)
			जारी;
		अगर (nf->nf_net != net)
			जारी;
		अगर (!nfsd_match_cred(nf->nf_cred, current_cred()))
			जारी;
		अगर (!test_bit(NFSD_खाता_HASHED, &nf->nf_flags))
			जारी;
		अगर (nfsd_file_get(nf) != शून्य)
			वापस nf;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * nfsd_file_is_cached - are there any cached खोलो files क्रम this fh?
 * @inode: inode of the file to check
 *
 * Scan the hashtable क्रम खोलो files that match this fh. Returns true अगर there
 * are any, and false अगर not.
 */
bool
nfsd_file_is_cached(काष्ठा inode *inode)
अणु
	bool			ret = false;
	काष्ठा nfsd_file	*nf;
	अचिन्हित पूर्णांक		hashval;

        hashval = (अचिन्हित पूर्णांक)hash_दीर्घ(inode->i_ino, NFSD_खाता_HASH_BITS);

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(nf, &nfsd_file_hashtbl[hashval].nfb_head,
				 nf_node) अणु
		अगर (inode == nf->nf_inode) अणु
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	trace_nfsd_file_is_cached(inode, hashval, (पूर्णांक)ret);
	वापस ret;
पूर्ण

__be32
nfsd_file_acquire(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		  अचिन्हित पूर्णांक may_flags, काष्ठा nfsd_file **pnf)
अणु
	__be32	status;
	काष्ठा net *net = SVC_NET(rqstp);
	काष्ठा nfsd_file *nf, *new;
	काष्ठा inode *inode;
	अचिन्हित पूर्णांक hashval;
	bool retry = true;

	/* FIXME: skip this अगर fh_dentry is alपढ़ोy set? */
	status = fh_verअगरy(rqstp, fhp, S_IFREG,
				may_flags|NFSD_MAY_OWNER_OVERRIDE);
	अगर (status != nfs_ok)
		वापस status;

	inode = d_inode(fhp->fh_dentry);
	hashval = (अचिन्हित पूर्णांक)hash_दीर्घ(inode->i_ino, NFSD_खाता_HASH_BITS);
retry:
	rcu_पढ़ो_lock();
	nf = nfsd_file_find_locked(inode, may_flags, hashval, net);
	rcu_पढ़ो_unlock();
	अगर (nf)
		जाओ रुको_क्रम_स्थिरruction;

	new = nfsd_file_alloc(inode, may_flags, hashval, net);
	अगर (!new) अणु
		trace_nfsd_file_acquire(rqstp, hashval, inode, may_flags,
					शून्य, nfserr_jukebox);
		वापस nfserr_jukebox;
	पूर्ण

	spin_lock(&nfsd_file_hashtbl[hashval].nfb_lock);
	nf = nfsd_file_find_locked(inode, may_flags, hashval, net);
	अगर (nf == शून्य)
		जाओ खोलो_file;
	spin_unlock(&nfsd_file_hashtbl[hashval].nfb_lock);
	nfsd_file_slab_मुक्त(&new->nf_rcu);

रुको_क्रम_स्थिरruction:
	रुको_on_bit(&nf->nf_flags, NFSD_खाता_PENDING, TASK_UNINTERRUPTIBLE);

	/* Did स्थिरruction of this file fail? */
	अगर (!test_bit(NFSD_खाता_HASHED, &nf->nf_flags)) अणु
		अगर (!retry) अणु
			status = nfserr_jukebox;
			जाओ out;
		पूर्ण
		retry = false;
		nfsd_file_put_noref(nf);
		जाओ retry;
	पूर्ण

	this_cpu_inc(nfsd_file_cache_hits);

	अगर (!(may_flags & NFSD_MAY_NOT_BREAK_LEASE)) अणु
		bool ग_लिखो = (may_flags & NFSD_MAY_WRITE);

		अगर (test_bit(NFSD_खाता_BREAK_READ, &nf->nf_flags) ||
		    (test_bit(NFSD_खाता_BREAK_WRITE, &nf->nf_flags) && ग_लिखो)) अणु
			status = nfsत्रुटि_सं(nfsd_खोलो_अवरोध_lease(
					file_inode(nf->nf_file), may_flags));
			अगर (status == nfs_ok) अणु
				clear_bit(NFSD_खाता_BREAK_READ, &nf->nf_flags);
				अगर (ग_लिखो)
					clear_bit(NFSD_खाता_BREAK_WRITE,
						  &nf->nf_flags);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	अगर (status == nfs_ok) अणु
		*pnf = nf;
	पूर्ण अन्यथा अणु
		nfsd_file_put(nf);
		nf = शून्य;
	पूर्ण

	trace_nfsd_file_acquire(rqstp, hashval, inode, may_flags, nf, status);
	वापस status;
खोलो_file:
	nf = new;
	/* Take reference क्रम the hashtable */
	refcount_inc(&nf->nf_ref);
	__set_bit(NFSD_खाता_HASHED, &nf->nf_flags);
	__set_bit(NFSD_खाता_PENDING, &nf->nf_flags);
	list_lru_add(&nfsd_file_lru, &nf->nf_lru);
	hlist_add_head_rcu(&nf->nf_node, &nfsd_file_hashtbl[hashval].nfb_head);
	++nfsd_file_hashtbl[hashval].nfb_count;
	nfsd_file_hashtbl[hashval].nfb_maxcount = max(nfsd_file_hashtbl[hashval].nfb_maxcount,
			nfsd_file_hashtbl[hashval].nfb_count);
	spin_unlock(&nfsd_file_hashtbl[hashval].nfb_lock);
	अगर (atomic_दीर्घ_inc_वापस(&nfsd_filecache_count) >= NFSD_खाता_LRU_THRESHOLD)
		nfsd_file_gc();

	nf->nf_mark = nfsd_file_mark_find_or_create(nf);
	अगर (nf->nf_mark)
		status = nfsd_खोलो_verअगरied(rqstp, fhp, S_IFREG,
				may_flags, &nf->nf_file);
	अन्यथा
		status = nfserr_jukebox;
	/*
	 * If स्थिरruction failed, or we raced with a call to unlink()
	 * then unhash.
	 */
	अगर (status != nfs_ok || inode->i_nlink == 0) अणु
		bool करो_मुक्त;
		spin_lock(&nfsd_file_hashtbl[hashval].nfb_lock);
		करो_मुक्त = nfsd_file_unhash(nf);
		spin_unlock(&nfsd_file_hashtbl[hashval].nfb_lock);
		अगर (करो_मुक्त)
			nfsd_file_put_noref(nf);
	पूर्ण
	clear_bit_unlock(NFSD_खाता_PENDING, &nf->nf_flags);
	smp_mb__after_atomic();
	wake_up_bit(&nf->nf_flags, NFSD_खाता_PENDING);
	जाओ out;
पूर्ण

/*
 * Note that fields may be added, हटाओd or reordered in the future. Programs
 * scraping this file क्रम info should test the labels to ensure they're
 * getting the correct field.
 */
अटल पूर्णांक nfsd_file_cache_stats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित पूर्णांक i, count = 0, दीर्घest = 0;
	अचिन्हित दीर्घ hits = 0;

	/*
	 * No need क्रम spinlocks here since we're not terribly पूर्णांकerested in
	 * accuracy. We करो take the nfsd_mutex simply to ensure that we
	 * करोn't end up racing with server shutकरोwn
	 */
	mutex_lock(&nfsd_mutex);
	अगर (nfsd_file_hashtbl) अणु
		क्रम (i = 0; i < NFSD_खाता_HASH_SIZE; i++) अणु
			count += nfsd_file_hashtbl[i].nfb_count;
			दीर्घest = max(दीर्घest, nfsd_file_hashtbl[i].nfb_count);
		पूर्ण
	पूर्ण
	mutex_unlock(&nfsd_mutex);

	क्रम_each_possible_cpu(i)
		hits += per_cpu(nfsd_file_cache_hits, i);

	seq_म_लिखो(m, "total entries: %u\n", count);
	seq_म_लिखो(m, "longest chain: %u\n", दीर्घest);
	seq_म_लिखो(m, "cache hits:    %lu\n", hits);
	वापस 0;
पूर्ण

पूर्णांक nfsd_file_cache_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, nfsd_file_cache_stats_show, शून्य);
पूर्ण
