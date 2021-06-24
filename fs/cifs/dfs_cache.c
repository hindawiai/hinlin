<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DFS referral cache routines
 *
 * Copyright (c) 2018-2019 Paulo Alcantara <palcantara@suse.de>
 */

#समावेश <linux/jhash.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/nls.h>
#समावेश <linux/workqueue.h>
#समावेश "cifsglob.h"
#समावेश "smb2pdu.h"
#समावेश "smb2proto.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_unicode.h"
#समावेश "smb2glob.h"
#समावेश "fs_context.h"

#समावेश "dfs_cache.h"

#घोषणा CACHE_HTABLE_SIZE 32
#घोषणा CACHE_MAX_ENTRIES 64

#घोषणा IS_INTERLINK_SET(v) ((v) & (DFSREF_REFERRAL_SERVER | \
				    DFSREF_STORAGE_SERVER))

काष्ठा cache_dfs_tgt अणु
	अक्षर *name;
	पूर्णांक path_consumed;
	काष्ठा list_head list;
पूर्ण;

काष्ठा cache_entry अणु
	काष्ठा hlist_node hlist;
	स्थिर अक्षर *path;
	पूर्णांक hdr_flags; /* RESP_GET_DFS_REFERRAL.ReferralHeaderFlags */
	पूर्णांक ttl; /* DFS_REREFERRAL_V3.TimeToLive */
	पूर्णांक srvtype; /* DFS_REREFERRAL_V3.ServerType */
	पूर्णांक ref_flags; /* DFS_REREFERRAL_V3.ReferralEntryFlags */
	काष्ठा बारpec64 eसमय;
	पूर्णांक path_consumed; /* RESP_GET_DFS_REFERRAL.PathConsumed */
	पूर्णांक numtgts;
	काष्ठा list_head tlist;
	काष्ठा cache_dfs_tgt *tgthपूर्णांक;
पूर्ण;

काष्ठा vol_info अणु
	अक्षर *fullpath;
	spinlock_t ctx_lock;
	काष्ठा smb3_fs_context ctx;
	अक्षर *mntdata;
	काष्ठा list_head list;
	काष्ठा list_head rlist;
	काष्ठा kref refcnt;
पूर्ण;

अटल काष्ठा kmem_cache *cache_slab __पढ़ो_mostly;
अटल काष्ठा workqueue_काष्ठा *dfscache_wq __पढ़ो_mostly;

अटल पूर्णांक cache_ttl;
अटल DEFINE_SPINLOCK(cache_ttl_lock);

अटल काष्ठा nls_table *cache_nlsc;

/*
 * Number of entries in the cache
 */
अटल atomic_t cache_count;

अटल काष्ठा hlist_head cache_htable[CACHE_HTABLE_SIZE];
अटल DECLARE_RWSEM(htable_rw_lock);

अटल LIST_HEAD(vol_list);
अटल DEFINE_SPINLOCK(vol_list_lock);

अटल व्योम refresh_cache_worker(काष्ठा work_काष्ठा *work);

अटल DECLARE_DELAYED_WORK(refresh_task, refresh_cache_worker);

अटल पूर्णांक get_normalized_path(स्थिर अक्षर *path, स्थिर अक्षर **npath)
अणु
	अगर (!path || म_माप(path) < 3 || (*path != '\\' && *path != '/'))
		वापस -EINVAL;

	अगर (*path == '\\') अणु
		*npath = path;
	पूर्ण अन्यथा अणु
		अक्षर *s = kstrdup(path, GFP_KERNEL);
		अगर (!s)
			वापस -ENOMEM;
		convert_delimiter(s, '\\');
		*npath = s;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम मुक्त_normalized_path(स्थिर अक्षर *path, स्थिर अक्षर *npath)
अणु
	अगर (path != npath)
		kमुक्त(npath);
पूर्ण

अटल अंतरभूत bool cache_entry_expired(स्थिर काष्ठा cache_entry *ce)
अणु
	काष्ठा बारpec64 ts;

	kसमय_get_coarse_real_ts64(&ts);
	वापस बारpec64_compare(&ts, &ce->eसमय) >= 0;
पूर्ण

अटल अंतरभूत व्योम मुक्त_tgts(काष्ठा cache_entry *ce)
अणु
	काष्ठा cache_dfs_tgt *t, *n;

	list_क्रम_each_entry_safe(t, n, &ce->tlist, list) अणु
		list_del(&t->list);
		kमुक्त(t->name);
		kमुक्त(t);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम flush_cache_ent(काष्ठा cache_entry *ce)
अणु
	hlist_del_init(&ce->hlist);
	kमुक्त(ce->path);
	मुक्त_tgts(ce);
	atomic_dec(&cache_count);
	kmem_cache_मुक्त(cache_slab, ce);
पूर्ण

अटल व्योम flush_cache_ents(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CACHE_HTABLE_SIZE; i++) अणु
		काष्ठा hlist_head *l = &cache_htable[i];
		काष्ठा hlist_node *n;
		काष्ठा cache_entry *ce;

		hlist_क्रम_each_entry_safe(ce, n, l, hlist) अणु
			अगर (!hlist_unhashed(&ce->hlist))
				flush_cache_ent(ce);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * dfs cache /proc file
 */
अटल पूर्णांक dfscache_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;
	काष्ठा cache_entry *ce;
	काष्ठा cache_dfs_tgt *t;

	seq_माला_दो(m, "DFS cache\n---------\n");

	करोwn_पढ़ो(&htable_rw_lock);
	क्रम (i = 0; i < CACHE_HTABLE_SIZE; i++) अणु
		काष्ठा hlist_head *l = &cache_htable[i];

		hlist_क्रम_each_entry(ce, l, hlist) अणु
			अगर (hlist_unhashed(&ce->hlist))
				जारी;

			seq_म_लिखो(m,
				   "cache entry: path=%s,type=%s,ttl=%d,etime=%ld,hdr_flags=0x%x,ref_flags=0x%x,interlink=%s,path_consumed=%d,expired=%s\n",
				   ce->path, ce->srvtype == DFS_TYPE_ROOT ? "root" : "link",
				   ce->ttl, ce->eसमय.tv_nsec, ce->ref_flags, ce->hdr_flags,
				   IS_INTERLINK_SET(ce->hdr_flags) ? "yes" : "no",
				   ce->path_consumed, cache_entry_expired(ce) ? "yes" : "no");

			list_क्रम_each_entry(t, &ce->tlist, list) अणु
				seq_म_लिखो(m, "  %s%s\n",
					   t->name,
					   ce->tgthपूर्णांक == t ? " (target hint)" : "");
			पूर्ण
		पूर्ण
	पूर्ण
	up_पढ़ो(&htable_rw_lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dfscache_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर c;
	पूर्णांक rc;

	rc = get_user(c, buffer);
	अगर (rc)
		वापस rc;

	अगर (c != '0')
		वापस -EINVAL;

	cअगरs_dbg(FYI, "clearing dfs cache\n");

	करोwn_ग_लिखो(&htable_rw_lock);
	flush_cache_ents();
	up_ग_लिखो(&htable_rw_lock);

	वापस count;
पूर्ण

अटल पूर्णांक dfscache_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, dfscache_proc_show, शून्य);
पूर्ण

स्थिर काष्ठा proc_ops dfscache_proc_ops = अणु
	.proc_खोलो	= dfscache_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= dfscache_proc_ग_लिखो,
पूर्ण;

#अगर_घोषित CONFIG_CIFS_DEBUG2
अटल अंतरभूत व्योम dump_tgts(स्थिर काष्ठा cache_entry *ce)
अणु
	काष्ठा cache_dfs_tgt *t;

	cअगरs_dbg(FYI, "target list:\n");
	list_क्रम_each_entry(t, &ce->tlist, list) अणु
		cअगरs_dbg(FYI, "  %s%s\n", t->name,
			 ce->tgthपूर्णांक == t ? " (target hint)" : "");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dump_ce(स्थिर काष्ठा cache_entry *ce)
अणु
	cअगरs_dbg(FYI, "cache entry: path=%s,type=%s,ttl=%d,etime=%ld,hdr_flags=0x%x,ref_flags=0x%x,interlink=%s,path_consumed=%d,expired=%s\n",
		 ce->path,
		 ce->srvtype == DFS_TYPE_ROOT ? "root" : "link", ce->ttl,
		 ce->eसमय.tv_nsec,
		 ce->hdr_flags, ce->ref_flags,
		 IS_INTERLINK_SET(ce->hdr_flags) ? "yes" : "no",
		 ce->path_consumed,
		 cache_entry_expired(ce) ? "yes" : "no");
	dump_tgts(ce);
पूर्ण

अटल अंतरभूत व्योम dump_refs(स्थिर काष्ठा dfs_info3_param *refs, पूर्णांक numrefs)
अणु
	पूर्णांक i;

	cअगरs_dbg(FYI, "DFS referrals returned by the server:\n");
	क्रम (i = 0; i < numrefs; i++) अणु
		स्थिर काष्ठा dfs_info3_param *ref = &refs[i];

		cअगरs_dbg(FYI,
			 "\n"
			 "flags:         0x%x\n"
			 "path_consumed: %d\n"
			 "server_type:   0x%x\n"
			 "ref_flag:      0x%x\n"
			 "path_name:     %s\n"
			 "node_name:     %s\n"
			 "ttl:           %d (%dm)\n",
			 ref->flags, ref->path_consumed, ref->server_type,
			 ref->ref_flag, ref->path_name, ref->node_name,
			 ref->ttl, ref->ttl / 60);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा dump_tgts(e)
#घोषणा dump_ce(e)
#घोषणा dump_refs(r, n)
#पूर्ण_अगर

/**
 * dfs_cache_init - Initialize DFS referral cache.
 *
 * Return zero अगर initialized successfully, otherwise non-zero.
 */
पूर्णांक dfs_cache_init(व्योम)
अणु
	पूर्णांक rc;
	पूर्णांक i;

	dfscache_wq = alloc_workqueue("cifs-dfscache",
				      WQ_FREEZABLE | WQ_MEM_RECLAIM, 1);
	अगर (!dfscache_wq)
		वापस -ENOMEM;

	cache_slab = kmem_cache_create("cifs_dfs_cache",
				       माप(काष्ठा cache_entry), 0,
				       SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!cache_slab) अणु
		rc = -ENOMEM;
		जाओ out_destroy_wq;
	पूर्ण

	क्रम (i = 0; i < CACHE_HTABLE_SIZE; i++)
		INIT_HLIST_HEAD(&cache_htable[i]);

	atomic_set(&cache_count, 0);
	cache_nlsc = load_nls_शेष();

	cअगरs_dbg(FYI, "%s: initialized DFS referral cache\n", __func__);
	वापस 0;

out_destroy_wq:
	destroy_workqueue(dfscache_wq);
	वापस rc;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cache_entry_hash(स्थिर व्योम *data, पूर्णांक size)
अणु
	अचिन्हित पूर्णांक h;

	h = jhash(data, size, 0);
	वापस h & (CACHE_HTABLE_SIZE - 1);
पूर्ण

/* Check whether second path component of @path is SYSVOL or NETLOGON */
अटल अंतरभूत bool is_sysvol_or_netlogon(स्थिर अक्षर *path)
अणु
	स्थिर अक्षर *s;
	अक्षर sep = path[0];

	s = म_अक्षर(path + 1, sep) + 1;
	वापस !strnहालcmp(s, "sysvol", म_माप("sysvol")) ||
		!strnहालcmp(s, "netlogon", म_माप("netlogon"));
पूर्ण

/* Return target hपूर्णांक of a DFS cache entry */
अटल अंतरभूत अक्षर *get_tgt_name(स्थिर काष्ठा cache_entry *ce)
अणु
	काष्ठा cache_dfs_tgt *t = ce->tgthपूर्णांक;

	वापस t ? t->name : ERR_PTR(-ENOENT);
पूर्ण

/* Return expire समय out of a new entry's TTL */
अटल अंतरभूत काष्ठा बारpec64 get_expire_समय(पूर्णांक ttl)
अणु
	काष्ठा बारpec64 ts = अणु
		.tv_sec = ttl,
		.tv_nsec = 0,
	पूर्ण;
	काष्ठा बारpec64 now;

	kसमय_get_coarse_real_ts64(&now);
	वापस बारpec64_add(now, ts);
पूर्ण

/* Allocate a new DFS target */
अटल काष्ठा cache_dfs_tgt *alloc_target(स्थिर अक्षर *name, पूर्णांक path_consumed)
अणु
	काष्ठा cache_dfs_tgt *t;

	t = kदो_स्मृति(माप(*t), GFP_ATOMIC);
	अगर (!t)
		वापस ERR_PTR(-ENOMEM);
	t->name = kstrdup(name, GFP_ATOMIC);
	अगर (!t->name) अणु
		kमुक्त(t);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	t->path_consumed = path_consumed;
	INIT_LIST_HEAD(&t->list);
	वापस t;
पूर्ण

/*
 * Copy DFS referral inक्रमmation to a cache entry and conditionally update
 * target hपूर्णांक.
 */
अटल पूर्णांक copy_ref_data(स्थिर काष्ठा dfs_info3_param *refs, पूर्णांक numrefs,
			 काष्ठा cache_entry *ce, स्थिर अक्षर *tgthपूर्णांक)
अणु
	पूर्णांक i;

	ce->ttl = refs[0].ttl;
	ce->eसमय = get_expire_समय(ce->ttl);
	ce->srvtype = refs[0].server_type;
	ce->hdr_flags = refs[0].flags;
	ce->ref_flags = refs[0].ref_flag;
	ce->path_consumed = refs[0].path_consumed;

	क्रम (i = 0; i < numrefs; i++) अणु
		काष्ठा cache_dfs_tgt *t;

		t = alloc_target(refs[i].node_name, refs[i].path_consumed);
		अगर (IS_ERR(t)) अणु
			मुक्त_tgts(ce);
			वापस PTR_ERR(t);
		पूर्ण
		अगर (tgthपूर्णांक && !strहालcmp(t->name, tgthपूर्णांक)) अणु
			list_add(&t->list, &ce->tlist);
			tgthपूर्णांक = शून्य;
		पूर्ण अन्यथा अणु
			list_add_tail(&t->list, &ce->tlist);
		पूर्ण
		ce->numtgts++;
	पूर्ण

	ce->tgthपूर्णांक = list_first_entry_or_null(&ce->tlist,
					       काष्ठा cache_dfs_tgt, list);

	वापस 0;
पूर्ण

/* Allocate a new cache entry */
अटल काष्ठा cache_entry *alloc_cache_entry(स्थिर अक्षर *path,
					     स्थिर काष्ठा dfs_info3_param *refs,
					     पूर्णांक numrefs)
अणु
	काष्ठा cache_entry *ce;
	पूर्णांक rc;

	ce = kmem_cache_zalloc(cache_slab, GFP_KERNEL);
	अगर (!ce)
		वापस ERR_PTR(-ENOMEM);

	ce->path = kstrdup(path, GFP_KERNEL);
	अगर (!ce->path) अणु
		kmem_cache_मुक्त(cache_slab, ce);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	INIT_HLIST_NODE(&ce->hlist);
	INIT_LIST_HEAD(&ce->tlist);

	rc = copy_ref_data(refs, numrefs, ce, शून्य);
	अगर (rc) अणु
		kमुक्त(ce->path);
		kmem_cache_मुक्त(cache_slab, ce);
		ce = ERR_PTR(rc);
	पूर्ण
	वापस ce;
पूर्ण

/* Must be called with htable_rw_lock held */
अटल व्योम हटाओ_oldest_entry(व्योम)
अणु
	पूर्णांक i;
	काष्ठा cache_entry *ce;
	काष्ठा cache_entry *to_del = शून्य;

	क्रम (i = 0; i < CACHE_HTABLE_SIZE; i++) अणु
		काष्ठा hlist_head *l = &cache_htable[i];

		hlist_क्रम_each_entry(ce, l, hlist) अणु
			अगर (hlist_unhashed(&ce->hlist))
				जारी;
			अगर (!to_del || बारpec64_compare(&ce->eसमय,
							  &to_del->eसमय) < 0)
				to_del = ce;
		पूर्ण
	पूर्ण

	अगर (!to_del) अणु
		cअगरs_dbg(FYI, "%s: no entry to remove\n", __func__);
		वापस;
	पूर्ण

	cअगरs_dbg(FYI, "%s: removing entry\n", __func__);
	dump_ce(to_del);
	flush_cache_ent(to_del);
पूर्ण

/* Add a new DFS cache entry */
अटल पूर्णांक add_cache_entry(स्थिर अक्षर *path, अचिन्हित पूर्णांक hash,
			   काष्ठा dfs_info3_param *refs, पूर्णांक numrefs)
अणु
	काष्ठा cache_entry *ce;

	ce = alloc_cache_entry(path, refs, numrefs);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	spin_lock(&cache_ttl_lock);
	अगर (!cache_ttl) अणु
		cache_ttl = ce->ttl;
		queue_delayed_work(dfscache_wq, &refresh_task, cache_ttl * HZ);
	पूर्ण अन्यथा अणु
		cache_ttl = min_t(पूर्णांक, cache_ttl, ce->ttl);
		mod_delayed_work(dfscache_wq, &refresh_task, cache_ttl * HZ);
	पूर्ण
	spin_unlock(&cache_ttl_lock);

	करोwn_ग_लिखो(&htable_rw_lock);
	hlist_add_head(&ce->hlist, &cache_htable[hash]);
	dump_ce(ce);
	up_ग_लिखो(&htable_rw_lock);

	वापस 0;
पूर्ण

अटल काष्ठा cache_entry *__lookup_cache_entry(स्थिर अक्षर *path)
अणु
	काष्ठा cache_entry *ce;
	अचिन्हित पूर्णांक h;
	bool found = false;

	h = cache_entry_hash(path, म_माप(path));

	hlist_क्रम_each_entry(ce, &cache_htable[h], hlist) अणु
		अगर (!strहालcmp(path, ce->path)) अणु
			found = true;
			dump_ce(ce);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		ce = ERR_PTR(-ENOENT);
	वापस ce;
पूर्ण

/*
 * Find a DFS cache entry in hash table and optionally check prefix path against
 * @path.
 * Use whole path components in the match.
 * Must be called with htable_rw_lock held.
 *
 * Return ERR_PTR(-ENOENT) अगर the entry is not found.
 */
अटल काष्ठा cache_entry *lookup_cache_entry(स्थिर अक्षर *path, अचिन्हित पूर्णांक *hash)
अणु
	काष्ठा cache_entry *ce = ERR_PTR(-ENOENT);
	अचिन्हित पूर्णांक h;
	पूर्णांक cnt = 0;
	अक्षर *npath;
	अक्षर *s, *e;
	अक्षर sep;

	npath = kstrdup(path, GFP_KERNEL);
	अगर (!npath)
		वापस ERR_PTR(-ENOMEM);

	s = npath;
	sep = *npath;
	जबतक ((s = म_अक्षर(s, sep)) && ++cnt < 3)
		s++;

	अगर (cnt < 3) अणु
		h = cache_entry_hash(path, म_माप(path));
		ce = __lookup_cache_entry(path);
		जाओ out;
	पूर्ण
	/*
	 * Handle paths that have more than two path components and are a complete prefix of the DFS
	 * referral request path (@path).
	 *
	 * See MS-DFSC 3.2.5.5 "Receiving a Root Referral Request or Link Referral Request".
	 */
	h = cache_entry_hash(npath, म_माप(npath));
	e = npath + म_माप(npath) - 1;
	जबतक (e > s) अणु
		अक्षर पंचांगp;

		/* skip separators */
		जबतक (e > s && *e == sep)
			e--;
		अगर (e == s)
			जाओ out;

		पंचांगp = *(e+1);
		*(e+1) = 0;

		ce = __lookup_cache_entry(npath);
		अगर (!IS_ERR(ce)) अणु
			h = cache_entry_hash(npath, म_माप(npath));
			अवरोध;
		पूर्ण

		*(e+1) = पंचांगp;
		/* backward until separator */
		जबतक (e > s && *e != sep)
			e--;
	पूर्ण
out:
	अगर (hash)
		*hash = h;
	kमुक्त(npath);
	वापस ce;
पूर्ण

अटल व्योम __vol_release(काष्ठा vol_info *vi)
अणु
	kमुक्त(vi->fullpath);
	kमुक्त(vi->mntdata);
	smb3_cleanup_fs_context_contents(&vi->ctx);
	kमुक्त(vi);
पूर्ण

अटल व्योम vol_release(काष्ठा kref *kref)
अणु
	काष्ठा vol_info *vi = container_of(kref, काष्ठा vol_info, refcnt);

	spin_lock(&vol_list_lock);
	list_del(&vi->list);
	spin_unlock(&vol_list_lock);
	__vol_release(vi);
पूर्ण

अटल अंतरभूत व्योम मुक्त_vol_list(व्योम)
अणु
	काष्ठा vol_info *vi, *nvi;

	list_क्रम_each_entry_safe(vi, nvi, &vol_list, list) अणु
		list_del_init(&vi->list);
		__vol_release(vi);
	पूर्ण
पूर्ण

/**
 * dfs_cache_destroy - destroy DFS referral cache
 */
व्योम dfs_cache_destroy(व्योम)
अणु
	cancel_delayed_work_sync(&refresh_task);
	unload_nls(cache_nlsc);
	मुक्त_vol_list();
	flush_cache_ents();
	kmem_cache_destroy(cache_slab);
	destroy_workqueue(dfscache_wq);

	cअगरs_dbg(FYI, "%s: destroyed DFS referral cache\n", __func__);
पूर्ण

/* Must be called with htable_rw_lock held */
अटल पूर्णांक __update_cache_entry(स्थिर अक्षर *path,
				स्थिर काष्ठा dfs_info3_param *refs,
				पूर्णांक numrefs)
अणु
	पूर्णांक rc;
	काष्ठा cache_entry *ce;
	अक्षर *s, *th = शून्य;

	ce = lookup_cache_entry(path, शून्य);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	अगर (ce->tgthपूर्णांक) अणु
		s = ce->tgthपूर्णांक->name;
		th = kstrdup(s, GFP_ATOMIC);
		अगर (!th)
			वापस -ENOMEM;
	पूर्ण

	मुक्त_tgts(ce);
	ce->numtgts = 0;

	rc = copy_ref_data(refs, numrefs, ce, th);

	kमुक्त(th);

	वापस rc;
पूर्ण

अटल पूर्णांक get_dfs_referral(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			    स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap,
			    स्थिर अक्षर *path,  काष्ठा dfs_info3_param **refs,
			    पूर्णांक *numrefs)
अणु
	cअगरs_dbg(FYI, "%s: get an DFS referral for %s\n", __func__, path);

	अगर (!ses || !ses->server || !ses->server->ops->get_dfs_refer)
		वापस -EOPNOTSUPP;
	अगर (unlikely(!nls_codepage))
		वापस -EINVAL;

	*refs = शून्य;
	*numrefs = 0;

	वापस ses->server->ops->get_dfs_refer(xid, ses, path, refs, numrefs,
					       nls_codepage, remap);
पूर्ण

/* Update an expired cache entry by getting a new DFS referral from server */
अटल पूर्णांक update_cache_entry(स्थिर अक्षर *path,
			      स्थिर काष्ठा dfs_info3_param *refs,
			      पूर्णांक numrefs)
अणु

	पूर्णांक rc;

	करोwn_ग_लिखो(&htable_rw_lock);
	rc = __update_cache_entry(path, refs, numrefs);
	up_ग_लिखो(&htable_rw_lock);

	वापस rc;
पूर्ण

/*
 * Find, create or update a DFS cache entry.
 *
 * If the entry wasn't found, it will create a new one. Or अगर it was found but
 * expired, then it will update the entry accordingly.
 *
 * For पूर्णांकerlinks, __cअगरs_dfs_mount() and expand_dfs_referral() are supposed to
 * handle them properly.
 */
अटल पूर्णांक __dfs_cache_find(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			    स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap,
			    स्थिर अक्षर *path, bool noreq)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक hash;
	काष्ठा cache_entry *ce;
	काष्ठा dfs_info3_param *refs = शून्य;
	पूर्णांक numrefs = 0;
	bool newent = false;

	cअगरs_dbg(FYI, "%s: search path: %s\n", __func__, path);

	करोwn_पढ़ो(&htable_rw_lock);

	ce = lookup_cache_entry(path, &hash);

	/*
	 * If @noreq is set, no requests will be sent to the server. Just वापस
	 * the cache entry.
	 */
	अगर (noreq) अणु
		up_पढ़ो(&htable_rw_lock);
		वापस PTR_ERR_OR_ZERO(ce);
	पूर्ण

	अगर (!IS_ERR(ce)) अणु
		अगर (!cache_entry_expired(ce)) अणु
			dump_ce(ce);
			up_पढ़ो(&htable_rw_lock);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		newent = true;
	पूर्ण

	up_पढ़ो(&htable_rw_lock);

	/*
	 * No entry was found.
	 *
	 * Request a new DFS referral in order to create a new cache entry, or
	 * updating an existing one.
	 */
	rc = get_dfs_referral(xid, ses, nls_codepage, remap, path,
			      &refs, &numrefs);
	अगर (rc)
		वापस rc;

	dump_refs(refs, numrefs);

	अगर (!newent) अणु
		rc = update_cache_entry(path, refs, numrefs);
		जाओ out_मुक्त_refs;
	पूर्ण

	अगर (atomic_पढ़ो(&cache_count) >= CACHE_MAX_ENTRIES) अणु
		cअगरs_dbg(FYI, "%s: reached max cache size (%d)\n",
			 __func__, CACHE_MAX_ENTRIES);
		करोwn_ग_लिखो(&htable_rw_lock);
		हटाओ_oldest_entry();
		up_ग_लिखो(&htable_rw_lock);
	पूर्ण

	rc = add_cache_entry(path, hash, refs, numrefs);
	अगर (!rc)
		atomic_inc(&cache_count);

out_मुक्त_refs:
	मुक्त_dfs_info_array(refs, numrefs);
	वापस rc;
पूर्ण

/*
 * Set up a DFS referral from a given cache entry.
 *
 * Must be called with htable_rw_lock held.
 */
अटल पूर्णांक setup_referral(स्थिर अक्षर *path, काष्ठा cache_entry *ce,
			  काष्ठा dfs_info3_param *ref, स्थिर अक्षर *target)
अणु
	पूर्णांक rc;

	cअगरs_dbg(FYI, "%s: set up new ref\n", __func__);

	स_रखो(ref, 0, माप(*ref));

	ref->path_name = kstrdup(path, GFP_ATOMIC);
	अगर (!ref->path_name)
		वापस -ENOMEM;

	ref->node_name = kstrdup(target, GFP_ATOMIC);
	अगर (!ref->node_name) अणु
		rc = -ENOMEM;
		जाओ err_मुक्त_path;
	पूर्ण

	ref->path_consumed = ce->path_consumed;
	ref->ttl = ce->ttl;
	ref->server_type = ce->srvtype;
	ref->ref_flag = ce->ref_flags;
	ref->flags = ce->hdr_flags;

	वापस 0;

err_मुक्त_path:
	kमुक्त(ref->path_name);
	ref->path_name = शून्य;
	वापस rc;
पूर्ण

/* Return target list of a DFS cache entry */
अटल पूर्णांक get_tarमाला_लो(काष्ठा cache_entry *ce, काष्ठा dfs_cache_tgt_list *tl)
अणु
	पूर्णांक rc;
	काष्ठा list_head *head = &tl->tl_list;
	काष्ठा cache_dfs_tgt *t;
	काष्ठा dfs_cache_tgt_iterator *it, *nit;

	स_रखो(tl, 0, माप(*tl));
	INIT_LIST_HEAD(head);

	list_क्रम_each_entry(t, &ce->tlist, list) अणु
		it = kzalloc(माप(*it), GFP_ATOMIC);
		अगर (!it) अणु
			rc = -ENOMEM;
			जाओ err_मुक्त_it;
		पूर्ण

		it->it_name = kstrdup(t->name, GFP_ATOMIC);
		अगर (!it->it_name) अणु
			kमुक्त(it);
			rc = -ENOMEM;
			जाओ err_मुक्त_it;
		पूर्ण
		it->it_path_consumed = t->path_consumed;

		अगर (ce->tgthपूर्णांक == t)
			list_add(&it->it_list, head);
		अन्यथा
			list_add_tail(&it->it_list, head);
	पूर्ण

	tl->tl_numtgts = ce->numtgts;

	वापस 0;

err_मुक्त_it:
	list_क्रम_each_entry_safe(it, nit, head, it_list) अणु
		kमुक्त(it->it_name);
		kमुक्त(it);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * dfs_cache_find - find a DFS cache entry
 *
 * If it करोesn't find the cache entry, then it will get a DFS referral
 * क्रम @path and create a new entry.
 *
 * In हाल the cache entry exists but expired, it will get a DFS referral
 * क्रम @path and then update the respective cache entry.
 *
 * These parameters are passed करोwn to the get_dfs_refer() call अगर it
 * needs to be issued:
 * @xid: syscall xid
 * @ses: smb session to issue the request on
 * @nls_codepage: अक्षरset conversion
 * @remap: path अक्षरacter remapping type
 * @path: path to lookup in DFS referral cache.
 *
 * @ref: when non-शून्य, store single DFS referral result in it.
 * @tgt_list: when non-शून्य, store complete DFS target list in it.
 *
 * Return zero अगर the target was found, otherwise non-zero.
 */
पूर्णांक dfs_cache_find(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		   स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap,
		   स्थिर अक्षर *path, काष्ठा dfs_info3_param *ref,
		   काष्ठा dfs_cache_tgt_list *tgt_list)
अणु
	पूर्णांक rc;
	स्थिर अक्षर *npath;
	काष्ठा cache_entry *ce;

	rc = get_normalized_path(path, &npath);
	अगर (rc)
		वापस rc;

	rc = __dfs_cache_find(xid, ses, nls_codepage, remap, npath, false);
	अगर (rc)
		जाओ out_मुक्त_path;

	करोwn_पढ़ो(&htable_rw_lock);

	ce = lookup_cache_entry(npath, शून्य);
	अगर (IS_ERR(ce)) अणु
		up_पढ़ो(&htable_rw_lock);
		rc = PTR_ERR(ce);
		जाओ out_मुक्त_path;
	पूर्ण

	अगर (ref)
		rc = setup_referral(path, ce, ref, get_tgt_name(ce));
	अन्यथा
		rc = 0;
	अगर (!rc && tgt_list)
		rc = get_tarमाला_लो(ce, tgt_list);

	up_पढ़ो(&htable_rw_lock);

out_मुक्त_path:
	मुक्त_normalized_path(path, npath);
	वापस rc;
पूर्ण

/**
 * dfs_cache_noreq_find - find a DFS cache entry without sending any requests to
 * the currently connected server.
 *
 * NOTE: This function will neither update a cache entry in हाल it was
 * expired, nor create a new cache entry अगर @path hasn't been found. It heavily
 * relies on an existing cache entry.
 *
 * @path: path to lookup in the DFS referral cache.
 * @ref: when non-शून्य, store single DFS referral result in it.
 * @tgt_list: when non-शून्य, store complete DFS target list in it.
 *
 * Return 0 अगर successful.
 * Return -ENOENT अगर the entry was not found.
 * Return non-zero क्रम other errors.
 */
पूर्णांक dfs_cache_noreq_find(स्थिर अक्षर *path, काष्ठा dfs_info3_param *ref,
			 काष्ठा dfs_cache_tgt_list *tgt_list)
अणु
	पूर्णांक rc;
	स्थिर अक्षर *npath;
	काष्ठा cache_entry *ce;

	rc = get_normalized_path(path, &npath);
	अगर (rc)
		वापस rc;

	cअगरs_dbg(FYI, "%s: path: %s\n", __func__, npath);

	करोwn_पढ़ो(&htable_rw_lock);

	ce = lookup_cache_entry(npath, शून्य);
	अगर (IS_ERR(ce)) अणु
		rc = PTR_ERR(ce);
		जाओ out_unlock;
	पूर्ण

	अगर (ref)
		rc = setup_referral(path, ce, ref, get_tgt_name(ce));
	अन्यथा
		rc = 0;
	अगर (!rc && tgt_list)
		rc = get_tarमाला_लो(ce, tgt_list);

out_unlock:
	up_पढ़ो(&htable_rw_lock);
	मुक्त_normalized_path(path, npath);

	वापस rc;
पूर्ण

/**
 * dfs_cache_update_tgthपूर्णांक - update target hपूर्णांक of a DFS cache entry
 *
 * If it करोesn't find the cache entry, then it will get a DFS referral क्रम @path
 * and create a new entry.
 *
 * In हाल the cache entry exists but expired, it will get a DFS referral
 * क्रम @path and then update the respective cache entry.
 *
 * @xid: syscall id
 * @ses: smb session
 * @nls_codepage: अक्षरset conversion
 * @remap: type of अक्षरacter remapping क्रम paths
 * @path: path to lookup in DFS referral cache.
 * @it: DFS target iterator
 *
 * Return zero अगर the target hपूर्णांक was updated successfully, otherwise non-zero.
 */
पूर्णांक dfs_cache_update_tgthपूर्णांक(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			     स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap,
			     स्थिर अक्षर *path,
			     स्थिर काष्ठा dfs_cache_tgt_iterator *it)
अणु
	पूर्णांक rc;
	स्थिर अक्षर *npath;
	काष्ठा cache_entry *ce;
	काष्ठा cache_dfs_tgt *t;

	rc = get_normalized_path(path, &npath);
	अगर (rc)
		वापस rc;

	cअगरs_dbg(FYI, "%s: update target hint - path: %s\n", __func__, npath);

	rc = __dfs_cache_find(xid, ses, nls_codepage, remap, npath, false);
	अगर (rc)
		जाओ out_मुक्त_path;

	करोwn_ग_लिखो(&htable_rw_lock);

	ce = lookup_cache_entry(npath, शून्य);
	अगर (IS_ERR(ce)) अणु
		rc = PTR_ERR(ce);
		जाओ out_unlock;
	पूर्ण

	t = ce->tgthपूर्णांक;

	अगर (likely(!strहालcmp(it->it_name, t->name)))
		जाओ out_unlock;

	list_क्रम_each_entry(t, &ce->tlist, list) अणु
		अगर (!strहालcmp(t->name, it->it_name)) अणु
			ce->tgthपूर्णांक = t;
			cअगरs_dbg(FYI, "%s: new target hint: %s\n", __func__,
				 it->it_name);
			अवरोध;
		पूर्ण
	पूर्ण

out_unlock:
	up_ग_लिखो(&htable_rw_lock);
out_मुक्त_path:
	मुक्त_normalized_path(path, npath);

	वापस rc;
पूर्ण

/**
 * dfs_cache_noreq_update_tgthपूर्णांक - update target hपूर्णांक of a DFS cache entry
 * without sending any requests to the currently connected server.
 *
 * NOTE: This function will neither update a cache entry in हाल it was
 * expired, nor create a new cache entry अगर @path hasn't been found. It heavily
 * relies on an existing cache entry.
 *
 * @path: path to lookup in DFS referral cache.
 * @it: target iterator which contains the target hपूर्णांक to update the cache
 * entry with.
 *
 * Return zero अगर the target hपूर्णांक was updated successfully, otherwise non-zero.
 */
पूर्णांक dfs_cache_noreq_update_tgthपूर्णांक(स्थिर अक्षर *path,
				   स्थिर काष्ठा dfs_cache_tgt_iterator *it)
अणु
	पूर्णांक rc;
	स्थिर अक्षर *npath;
	काष्ठा cache_entry *ce;
	काष्ठा cache_dfs_tgt *t;

	अगर (!it)
		वापस -EINVAL;

	rc = get_normalized_path(path, &npath);
	अगर (rc)
		वापस rc;

	cअगरs_dbg(FYI, "%s: path: %s\n", __func__, npath);

	करोwn_ग_लिखो(&htable_rw_lock);

	ce = lookup_cache_entry(npath, शून्य);
	अगर (IS_ERR(ce)) अणु
		rc = PTR_ERR(ce);
		जाओ out_unlock;
	पूर्ण

	rc = 0;
	t = ce->tgthपूर्णांक;

	अगर (unlikely(!strहालcmp(it->it_name, t->name)))
		जाओ out_unlock;

	list_क्रम_each_entry(t, &ce->tlist, list) अणु
		अगर (!strहालcmp(t->name, it->it_name)) अणु
			ce->tgthपूर्णांक = t;
			cअगरs_dbg(FYI, "%s: new target hint: %s\n", __func__,
				 it->it_name);
			अवरोध;
		पूर्ण
	पूर्ण

out_unlock:
	up_ग_लिखो(&htable_rw_lock);
	मुक्त_normalized_path(path, npath);

	वापस rc;
पूर्ण

/**
 * dfs_cache_get_tgt_referral - वापसs a DFS referral (@ref) from a given
 * target iterator (@it).
 *
 * @path: path to lookup in DFS referral cache.
 * @it: DFS target iterator.
 * @ref: DFS referral poपूर्णांकer to set up the gathered inक्रमmation.
 *
 * Return zero अगर the DFS referral was set up correctly, otherwise non-zero.
 */
पूर्णांक dfs_cache_get_tgt_referral(स्थिर अक्षर *path,
			       स्थिर काष्ठा dfs_cache_tgt_iterator *it,
			       काष्ठा dfs_info3_param *ref)
अणु
	पूर्णांक rc;
	स्थिर अक्षर *npath;
	काष्ठा cache_entry *ce;

	अगर (!it || !ref)
		वापस -EINVAL;

	rc = get_normalized_path(path, &npath);
	अगर (rc)
		वापस rc;

	cअगरs_dbg(FYI, "%s: path: %s\n", __func__, npath);

	करोwn_पढ़ो(&htable_rw_lock);

	ce = lookup_cache_entry(npath, शून्य);
	अगर (IS_ERR(ce)) अणु
		rc = PTR_ERR(ce);
		जाओ out_unlock;
	पूर्ण

	cअगरs_dbg(FYI, "%s: target name: %s\n", __func__, it->it_name);

	rc = setup_referral(path, ce, ref, it->it_name);

out_unlock:
	up_पढ़ो(&htable_rw_lock);
	मुक्त_normalized_path(path, npath);

	वापस rc;
पूर्ण

/**
 * dfs_cache_add_vol - add a cअगरs context during mount() that will be handled by
 * DFS cache refresh worker.
 *
 * @mntdata: mount data.
 * @ctx: cअगरs context.
 * @fullpath: origin full path.
 *
 * Return zero अगर context was set up correctly, otherwise non-zero.
 */
पूर्णांक dfs_cache_add_vol(अक्षर *mntdata, काष्ठा smb3_fs_context *ctx, स्थिर अक्षर *fullpath)
अणु
	पूर्णांक rc;
	काष्ठा vol_info *vi;

	अगर (!ctx || !fullpath || !mntdata)
		वापस -EINVAL;

	cअगरs_dbg(FYI, "%s: fullpath: %s\n", __func__, fullpath);

	vi = kzalloc(माप(*vi), GFP_KERNEL);
	अगर (!vi)
		वापस -ENOMEM;

	vi->fullpath = kstrdup(fullpath, GFP_KERNEL);
	अगर (!vi->fullpath) अणु
		rc = -ENOMEM;
		जाओ err_मुक्त_vi;
	पूर्ण

	rc = smb3_fs_context_dup(&vi->ctx, ctx);
	अगर (rc)
		जाओ err_मुक्त_fullpath;

	vi->mntdata = mntdata;
	spin_lock_init(&vi->ctx_lock);
	kref_init(&vi->refcnt);

	spin_lock(&vol_list_lock);
	list_add_tail(&vi->list, &vol_list);
	spin_unlock(&vol_list_lock);

	वापस 0;

err_मुक्त_fullpath:
	kमुक्त(vi->fullpath);
err_मुक्त_vi:
	kमुक्त(vi);
	वापस rc;
पूर्ण

/* Must be called with vol_list_lock held */
अटल काष्ठा vol_info *find_vol(स्थिर अक्षर *fullpath)
अणु
	काष्ठा vol_info *vi;

	list_क्रम_each_entry(vi, &vol_list, list) अणु
		cअगरs_dbg(FYI, "%s: vi->fullpath: %s\n", __func__, vi->fullpath);
		अगर (!strहालcmp(vi->fullpath, fullpath))
			वापस vi;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

/**
 * dfs_cache_update_vol - update vol info in DFS cache after failover
 *
 * @fullpath: fullpath to look up in volume list.
 * @server: TCP ses poपूर्णांकer.
 *
 * Return zero अगर volume was updated, otherwise non-zero.
 */
पूर्णांक dfs_cache_update_vol(स्थिर अक्षर *fullpath, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा vol_info *vi;

	अगर (!fullpath || !server)
		वापस -EINVAL;

	cअगरs_dbg(FYI, "%s: fullpath: %s\n", __func__, fullpath);

	spin_lock(&vol_list_lock);
	vi = find_vol(fullpath);
	अगर (IS_ERR(vi)) अणु
		spin_unlock(&vol_list_lock);
		वापस PTR_ERR(vi);
	पूर्ण
	kref_get(&vi->refcnt);
	spin_unlock(&vol_list_lock);

	cअगरs_dbg(FYI, "%s: updating volume info\n", __func__);
	spin_lock(&vi->ctx_lock);
	स_नकल(&vi->ctx.dstaddr, &server->dstaddr,
	       माप(vi->ctx.dstaddr));
	spin_unlock(&vi->ctx_lock);

	kref_put(&vi->refcnt, vol_release);

	वापस 0;
पूर्ण

/**
 * dfs_cache_del_vol - हटाओ volume info in DFS cache during umount()
 *
 * @fullpath: fullpath to look up in volume list.
 */
व्योम dfs_cache_del_vol(स्थिर अक्षर *fullpath)
अणु
	काष्ठा vol_info *vi;

	अगर (!fullpath || !*fullpath)
		वापस;

	cअगरs_dbg(FYI, "%s: fullpath: %s\n", __func__, fullpath);

	spin_lock(&vol_list_lock);
	vi = find_vol(fullpath);
	spin_unlock(&vol_list_lock);

	अगर (!IS_ERR(vi))
		kref_put(&vi->refcnt, vol_release);
पूर्ण

/**
 * dfs_cache_get_tgt_share - parse a DFS target
 *
 * @path: DFS full path
 * @it: DFS target iterator.
 * @share: tree name.
 * @prefix: prefix path.
 *
 * Return zero अगर target was parsed correctly, otherwise non-zero.
 */
पूर्णांक dfs_cache_get_tgt_share(अक्षर *path, स्थिर काष्ठा dfs_cache_tgt_iterator *it,
			    अक्षर **share, अक्षर **prefix)
अणु
	अक्षर *s, sep, *p;
	माप_प्रकार len;
	माप_प्रकार plen1, plen2;

	अगर (!it || !path || !share || !prefix || म_माप(path) < it->it_path_consumed)
		वापस -EINVAL;

	*share = शून्य;
	*prefix = शून्य;

	sep = it->it_name[0];
	अगर (sep != '\\' && sep != '/')
		वापस -EINVAL;

	s = म_अक्षर(it->it_name + 1, sep);
	अगर (!s)
		वापस -EINVAL;

	/* poपूर्णांक to prefix in target node */
	s = म_अक्षरnul(s + 1, sep);

	/* extract target share */
	*share = kstrndup(it->it_name, s - it->it_name, GFP_KERNEL);
	अगर (!*share)
		वापस -ENOMEM;

	/* skip separator */
	अगर (*s)
		s++;
	/* poपूर्णांक to prefix in DFS path */
	p = path + it->it_path_consumed;
	अगर (*p == sep)
		p++;

	/* merge prefix paths from DFS path and target node */
	plen1 = it->it_name + म_माप(it->it_name) - s;
	plen2 = path + म_माप(path) - p;
	अगर (plen1 || plen2) अणु
		len = plen1 + plen2 + 2;
		*prefix = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!*prefix) अणु
			kमुक्त(*share);
			*share = शून्य;
			वापस -ENOMEM;
		पूर्ण
		अगर (plen1)
			scnम_लिखो(*prefix, len, "%.*s%c%.*s", (पूर्णांक)plen1, s, sep, (पूर्णांक)plen2, p);
		अन्यथा
			strscpy(*prefix, p, len);
	पूर्ण
	वापस 0;
पूर्ण

/* Get all tcons that are within a DFS namespace and can be refreshed */
अटल व्योम get_tcons(काष्ठा TCP_Server_Info *server, काष्ठा list_head *head)
अणु
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;

	INIT_LIST_HEAD(head);

	spin_lock(&cअगरs_tcp_ses_lock);
	list_क्रम_each_entry(ses, &server->smb_ses_list, smb_ses_list) अणु
		list_क्रम_each_entry(tcon, &ses->tcon_list, tcon_list) अणु
			अगर (!tcon->need_reconnect && !tcon->need_reखोलो_files &&
			    tcon->dfs_path) अणु
				tcon->tc_count++;
				list_add_tail(&tcon->ulist, head);
			पूर्ण
		पूर्ण
		अगर (ses->tcon_ipc && !ses->tcon_ipc->need_reconnect &&
		    ses->tcon_ipc->dfs_path) अणु
			list_add_tail(&ses->tcon_ipc->ulist, head);
		पूर्ण
	पूर्ण
	spin_unlock(&cअगरs_tcp_ses_lock);
पूर्ण

अटल bool is_dfs_link(स्थिर अक्षर *path)
अणु
	अक्षर *s;

	s = म_अक्षर(path + 1, '\\');
	अगर (!s)
		वापस false;
	वापस !!म_अक्षर(s + 1, '\\');
पूर्ण

अटल अक्षर *get_dfs_root(स्थिर अक्षर *path)
अणु
	अक्षर *s, *npath;

	s = म_अक्षर(path + 1, '\\');
	अगर (!s)
		वापस ERR_PTR(-EINVAL);

	s = म_अक्षर(s + 1, '\\');
	अगर (!s)
		वापस ERR_PTR(-EINVAL);

	npath = kstrndup(path, s - path, GFP_KERNEL);
	अगर (!npath)
		वापस ERR_PTR(-ENOMEM);

	वापस npath;
पूर्ण

अटल अंतरभूत व्योम put_tcp_server(काष्ठा TCP_Server_Info *server)
अणु
	cअगरs_put_tcp_session(server, 0);
पूर्ण

अटल काष्ठा TCP_Server_Info *get_tcp_server(काष्ठा smb3_fs_context *ctx)
अणु
	काष्ठा TCP_Server_Info *server;

	server = cअगरs_find_tcp_session(ctx);
	अगर (IS_ERR_OR_शून्य(server))
		वापस शून्य;

	spin_lock(&GlobalMid_Lock);
	अगर (server->tcpStatus != CअगरsGood) अणु
		spin_unlock(&GlobalMid_Lock);
		put_tcp_server(server);
		वापस शून्य;
	पूर्ण
	spin_unlock(&GlobalMid_Lock);

	वापस server;
पूर्ण

/* Find root SMB session out of a DFS link path */
अटल काष्ठा cअगरs_ses *find_root_ses(काष्ठा vol_info *vi,
				      काष्ठा cअगरs_tcon *tcon,
				      स्थिर अक्षर *path)
अणु
	अक्षर *rpath;
	पूर्णांक rc;
	काष्ठा cache_entry *ce;
	काष्ठा dfs_info3_param ref = अणु0पूर्ण;
	अक्षर *mdata = शून्य, *devname = शून्य;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरs_ses *ses;
	काष्ठा smb3_fs_context ctx = अणुशून्यपूर्ण;

	rpath = get_dfs_root(path);
	अगर (IS_ERR(rpath))
		वापस ERR_CAST(rpath);

	करोwn_पढ़ो(&htable_rw_lock);

	ce = lookup_cache_entry(rpath, शून्य);
	अगर (IS_ERR(ce)) अणु
		up_पढ़ो(&htable_rw_lock);
		ses = ERR_CAST(ce);
		जाओ out;
	पूर्ण

	rc = setup_referral(path, ce, &ref, get_tgt_name(ce));
	अगर (rc) अणु
		up_पढ़ो(&htable_rw_lock);
		ses = ERR_PTR(rc);
		जाओ out;
	पूर्ण

	up_पढ़ो(&htable_rw_lock);

	mdata = cअगरs_compose_mount_options(vi->mntdata, rpath, &ref,
					   &devname);
	मुक्त_dfs_info_param(&ref);

	अगर (IS_ERR(mdata)) अणु
		ses = ERR_CAST(mdata);
		mdata = शून्य;
		जाओ out;
	पूर्ण

	rc = cअगरs_setup_volume_info(&ctx, शून्य, devname);

	अगर (rc) अणु
		ses = ERR_PTR(rc);
		जाओ out;
	पूर्ण

	server = get_tcp_server(&ctx);
	अगर (!server) अणु
		ses = ERR_PTR(-EHOSTDOWN);
		जाओ out;
	पूर्ण

	ses = cअगरs_get_smb_ses(server, &ctx);

out:
	smb3_cleanup_fs_context_contents(&ctx);
	kमुक्त(mdata);
	kमुक्त(rpath);
	kमुक्त(devname);

	वापस ses;
पूर्ण

/* Refresh DFS cache entry from a given tcon */
अटल पूर्णांक refresh_tcon(काष्ठा vol_info *vi, काष्ठा cअगरs_tcon *tcon)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक xid;
	स्थिर अक्षर *path, *npath;
	काष्ठा cache_entry *ce;
	काष्ठा cअगरs_ses *root_ses = शून्य, *ses;
	काष्ठा dfs_info3_param *refs = शून्य;
	पूर्णांक numrefs = 0;

	xid = get_xid();

	path = tcon->dfs_path + 1;

	rc = get_normalized_path(path, &npath);
	अगर (rc)
		जाओ out_मुक्त_xid;

	करोwn_पढ़ो(&htable_rw_lock);

	ce = lookup_cache_entry(npath, शून्य);
	अगर (IS_ERR(ce)) अणु
		rc = PTR_ERR(ce);
		up_पढ़ो(&htable_rw_lock);
		जाओ out_मुक्त_path;
	पूर्ण

	अगर (!cache_entry_expired(ce)) अणु
		up_पढ़ो(&htable_rw_lock);
		जाओ out_मुक्त_path;
	पूर्ण

	up_पढ़ो(&htable_rw_lock);

	/* If it's a DFS Link, then use root SMB session क्रम refreshing it */
	अगर (is_dfs_link(npath)) अणु
		ses = root_ses = find_root_ses(vi, tcon, npath);
		अगर (IS_ERR(ses)) अणु
			rc = PTR_ERR(ses);
			root_ses = शून्य;
			जाओ out_मुक्त_path;
		पूर्ण
	पूर्ण अन्यथा अणु
		ses = tcon->ses;
	पूर्ण

	rc = get_dfs_referral(xid, ses, cache_nlsc, tcon->remap, npath, &refs,
			      &numrefs);
	अगर (!rc) अणु
		dump_refs(refs, numrefs);
		rc = update_cache_entry(npath, refs, numrefs);
		मुक्त_dfs_info_array(refs, numrefs);
	पूर्ण

	अगर (root_ses)
		cअगरs_put_smb_ses(root_ses);

out_मुक्त_path:
	मुक्त_normalized_path(path, npath);

out_मुक्त_xid:
	मुक्त_xid(xid);
	वापस rc;
पूर्ण

/*
 * Worker that will refresh DFS cache based on lowest TTL value from a DFS
 * referral.
 */
अटल व्योम refresh_cache_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vol_info *vi, *nvi;
	काष्ठा TCP_Server_Info *server;
	LIST_HEAD(vols);
	LIST_HEAD(tcons);
	काष्ठा cअगरs_tcon *tcon, *ntcon;
	पूर्णांक rc;

	/*
	 * Find SMB volumes that are eligible (server->tcpStatus == CअगरsGood)
	 * क्रम refreshing.
	 */
	spin_lock(&vol_list_lock);
	list_क्रम_each_entry(vi, &vol_list, list) अणु
		server = get_tcp_server(&vi->ctx);
		अगर (!server)
			जारी;

		kref_get(&vi->refcnt);
		list_add_tail(&vi->rlist, &vols);
		put_tcp_server(server);
	पूर्ण
	spin_unlock(&vol_list_lock);

	/* Walk through all TCONs and refresh any expired cache entry */
	list_क्रम_each_entry_safe(vi, nvi, &vols, rlist) अणु
		spin_lock(&vi->ctx_lock);
		server = get_tcp_server(&vi->ctx);
		spin_unlock(&vi->ctx_lock);

		अगर (!server)
			जाओ next_vol;

		get_tcons(server, &tcons);
		rc = 0;

		list_क्रम_each_entry_safe(tcon, ntcon, &tcons, ulist) अणु
			/*
			 * Skip tcp server अगर any of its tcons failed to refresh
			 * (possibily due to reconnects).
			 */
			अगर (!rc)
				rc = refresh_tcon(vi, tcon);

			list_del_init(&tcon->ulist);
			cअगरs_put_tcon(tcon);
		पूर्ण

		put_tcp_server(server);

next_vol:
		list_del_init(&vi->rlist);
		kref_put(&vi->refcnt, vol_release);
	पूर्ण

	spin_lock(&cache_ttl_lock);
	queue_delayed_work(dfscache_wq, &refresh_task, cache_ttl * HZ);
	spin_unlock(&cache_ttl_lock);
पूर्ण
