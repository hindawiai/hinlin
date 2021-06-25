<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common NFS I/O  operations क्रम the pnfs file based
 * layout drivers.
 *
 * Copyright (c) 2014, Primary Data, Inc. All rights reserved.
 *
 * Tom Haynes <loghyr@primarydata.com>
 */

#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/module.h>

#समावेश "nfs4session.h"
#समावेश "internal.h"
#समावेश "pnfs.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PNFS

व्योम pnfs_generic_rw_release(व्योम *data)
अणु
	काष्ठा nfs_pgio_header *hdr = data;

	nfs_put_client(hdr->ds_clp);
	hdr->mds_ops->rpc_release(data);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_rw_release);

/* Fake up some data that will cause nfs_commit_release to retry the ग_लिखोs. */
व्योम pnfs_generic_prepare_to_resend_ग_लिखोs(काष्ठा nfs_commit_data *data)
अणु
	काष्ठा nfs_ग_लिखोverf *verf = data->res.verf;

	data->task.tk_status = 0;
	स_रखो(&verf->verअगरier, 0, माप(verf->verअगरier));
	verf->committed = NFS_UNSTABLE;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_prepare_to_resend_ग_लिखोs);

व्योम pnfs_generic_ग_लिखो_commit_करोne(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_commit_data *wdata = data;

	/* Note this may cause RPC to be resent */
	wdata->mds_ops->rpc_call_करोne(task, data);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_ग_लिखो_commit_करोne);

व्योम pnfs_generic_commit_release(व्योम *calldata)
अणु
	काष्ठा nfs_commit_data *data = calldata;

	data->completion_ops->completion(data);
	pnfs_put_lseg(data->lseg);
	nfs_put_client(data->ds_clp);
	nfs_commitdata_release(data);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_commit_release);

अटल काष्ठा pnfs_layout_segment *
pnfs_मुक्त_bucket_lseg(काष्ठा pnfs_commit_bucket *bucket)
अणु
	अगर (list_empty(&bucket->committing) && list_empty(&bucket->written)) अणु
		काष्ठा pnfs_layout_segment *मुक्तme = bucket->lseg;
		bucket->lseg = शून्य;
		वापस मुक्तme;
	पूर्ण
	वापस शून्य;
पूर्ण

/* The generic layer is about to हटाओ the req from the commit list.
 * If this will make the bucket empty, it will need to put the lseg reference.
 * Note this must be called holding nfsi->commit_mutex
 */
व्योम
pnfs_generic_clear_request_commit(काष्ठा nfs_page *req,
				  काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा pnfs_commit_bucket *bucket = शून्य;

	अगर (!test_and_clear_bit(PG_COMMIT_TO_DS, &req->wb_flags))
		जाओ out;
	cinfo->ds->nwritten--;
	अगर (list_is_singular(&req->wb_list))
		bucket = list_first_entry(&req->wb_list,
					  काष्ठा pnfs_commit_bucket, written);
out:
	nfs_request_हटाओ_commit_list(req, cinfo);
	अगर (bucket)
		pnfs_put_lseg(pnfs_मुक्त_bucket_lseg(bucket));
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_clear_request_commit);

काष्ठा pnfs_commit_array *
pnfs_alloc_commit_array(माप_प्रकार n, gfp_t gfp_flags)
अणु
	काष्ठा pnfs_commit_array *p;
	काष्ठा pnfs_commit_bucket *b;

	p = kदो_स्मृति(काष्ठा_size(p, buckets, n), gfp_flags);
	अगर (!p)
		वापस शून्य;
	p->nbuckets = n;
	INIT_LIST_HEAD(&p->cinfo_list);
	INIT_LIST_HEAD(&p->lseg_list);
	p->lseg = शून्य;
	क्रम (b = &p->buckets[0]; n != 0; b++, n--) अणु
		INIT_LIST_HEAD(&b->written);
		INIT_LIST_HEAD(&b->committing);
		b->lseg = शून्य;
		b->direct_verf.committed = NFS_INVALID_STABLE_HOW;
	पूर्ण
	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_alloc_commit_array);

व्योम
pnfs_मुक्त_commit_array(काष्ठा pnfs_commit_array *p)
अणु
	kमुक्त_rcu(p, rcu);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_मुक्त_commit_array);

अटल काष्ठा pnfs_commit_array *
pnfs_find_commit_array_by_lseg(काष्ठा pnfs_ds_commit_info *fl_cinfo,
		काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा pnfs_commit_array *array;

	list_क्रम_each_entry_rcu(array, &fl_cinfo->commits, cinfo_list) अणु
		अगर (array->lseg == lseg)
			वापस array;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा pnfs_commit_array *
pnfs_add_commit_array(काष्ठा pnfs_ds_commit_info *fl_cinfo,
		काष्ठा pnfs_commit_array *new,
		काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा pnfs_commit_array *array;

	array = pnfs_find_commit_array_by_lseg(fl_cinfo, lseg);
	अगर (array)
		वापस array;
	new->lseg = lseg;
	refcount_set(&new->refcount, 1);
	list_add_rcu(&new->cinfo_list, &fl_cinfo->commits);
	list_add(&new->lseg_list, &lseg->pls_commits);
	वापस new;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_add_commit_array);

अटल काष्ठा pnfs_commit_array *
pnfs_lookup_commit_array(काष्ठा pnfs_ds_commit_info *fl_cinfo,
		काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा pnfs_commit_array *array;

	rcu_पढ़ो_lock();
	array = pnfs_find_commit_array_by_lseg(fl_cinfo, lseg);
	अगर (!array) अणु
		rcu_पढ़ो_unlock();
		fl_cinfo->ops->setup_ds_info(fl_cinfo, lseg);
		rcu_पढ़ो_lock();
		array = pnfs_find_commit_array_by_lseg(fl_cinfo, lseg);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस array;
पूर्ण

अटल व्योम
pnfs_release_commit_array_locked(काष्ठा pnfs_commit_array *array)
अणु
	list_del_rcu(&array->cinfo_list);
	list_del(&array->lseg_list);
	pnfs_मुक्त_commit_array(array);
पूर्ण

अटल व्योम
pnfs_put_commit_array_locked(काष्ठा pnfs_commit_array *array)
अणु
	अगर (refcount_dec_and_test(&array->refcount))
		pnfs_release_commit_array_locked(array);
पूर्ण

अटल व्योम
pnfs_put_commit_array(काष्ठा pnfs_commit_array *array, काष्ठा inode *inode)
अणु
	अगर (refcount_dec_and_lock(&array->refcount, &inode->i_lock)) अणु
		pnfs_release_commit_array_locked(array);
		spin_unlock(&inode->i_lock);
	पूर्ण
पूर्ण

अटल काष्ठा pnfs_commit_array *
pnfs_get_commit_array(काष्ठा pnfs_commit_array *array)
अणु
	अगर (refcount_inc_not_zero(&array->refcount))
		वापस array;
	वापस शून्य;
पूर्ण

अटल व्योम
pnfs_हटाओ_and_मुक्त_commit_array(काष्ठा pnfs_commit_array *array)
अणु
	array->lseg = शून्य;
	list_del_init(&array->lseg_list);
	pnfs_put_commit_array_locked(array);
पूर्ण

व्योम
pnfs_generic_ds_cinfo_release_lseg(काष्ठा pnfs_ds_commit_info *fl_cinfo,
		काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा pnfs_commit_array *array, *पंचांगp;

	list_क्रम_each_entry_safe(array, पंचांगp, &lseg->pls_commits, lseg_list)
		pnfs_हटाओ_and_मुक्त_commit_array(array);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_ds_cinfo_release_lseg);

व्योम
pnfs_generic_ds_cinfo_destroy(काष्ठा pnfs_ds_commit_info *fl_cinfo)
अणु
	काष्ठा pnfs_commit_array *array, *पंचांगp;

	list_क्रम_each_entry_safe(array, पंचांगp, &fl_cinfo->commits, cinfo_list)
		pnfs_हटाओ_and_मुक्त_commit_array(array);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_ds_cinfo_destroy);

/*
 * Locks the nfs_page requests क्रम commit and moves them to
 * @bucket->committing.
 */
अटल पूर्णांक
pnfs_bucket_scan_ds_commit_list(काष्ठा pnfs_commit_bucket *bucket,
				काष्ठा nfs_commit_info *cinfo,
				पूर्णांक max)
अणु
	काष्ठा list_head *src = &bucket->written;
	काष्ठा list_head *dst = &bucket->committing;
	पूर्णांक ret;

	lockdep_निश्चित_held(&NFS_I(cinfo->inode)->commit_mutex);
	ret = nfs_scan_commit_list(src, dst, cinfo, max);
	अगर (ret) अणु
		cinfo->ds->nwritten -= ret;
		cinfo->ds->ncommitting += ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक pnfs_bucket_scan_array(काष्ठा nfs_commit_info *cinfo,
				  काष्ठा pnfs_commit_bucket *buckets,
				  अचिन्हित पूर्णांक nbuckets,
				  पूर्णांक max)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rv = 0, cnt;

	क्रम (i = 0; i < nbuckets && max != 0; i++) अणु
		cnt = pnfs_bucket_scan_ds_commit_list(&buckets[i], cinfo, max);
		rv += cnt;
		max -= cnt;
	पूर्ण
	वापस rv;
पूर्ण

/* Move reqs from written to committing lists, वापसing count
 * of number moved.
 */
पूर्णांक pnfs_generic_scan_commit_lists(काष्ठा nfs_commit_info *cinfo, पूर्णांक max)
अणु
	काष्ठा pnfs_ds_commit_info *fl_cinfo = cinfo->ds;
	काष्ठा pnfs_commit_array *array;
	पूर्णांक rv = 0, cnt;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(array, &fl_cinfo->commits, cinfo_list) अणु
		अगर (!array->lseg || !pnfs_get_commit_array(array))
			जारी;
		rcu_पढ़ो_unlock();
		cnt = pnfs_bucket_scan_array(cinfo, array->buckets,
				array->nbuckets, max);
		rcu_पढ़ो_lock();
		pnfs_put_commit_array(array, cinfo->inode);
		rv += cnt;
		max -= cnt;
		अगर (!max)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_scan_commit_lists);

अटल अचिन्हित पूर्णांक
pnfs_bucket_recover_commit_reqs(काष्ठा list_head *dst,
			        काष्ठा pnfs_commit_bucket *buckets,
				अचिन्हित पूर्णांक nbuckets,
				काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा pnfs_commit_bucket *b;
	काष्ठा pnfs_layout_segment *मुक्तme;
	अचिन्हित पूर्णांक nwritten, ret = 0;
	अचिन्हित पूर्णांक i;

restart:
	क्रम (i = 0, b = buckets; i < nbuckets; i++, b++) अणु
		nwritten = nfs_scan_commit_list(&b->written, dst, cinfo, 0);
		अगर (!nwritten)
			जारी;
		ret += nwritten;
		मुक्तme = pnfs_मुक्त_bucket_lseg(b);
		अगर (मुक्तme) अणु
			pnfs_put_lseg(मुक्तme);
			जाओ restart;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* Pull everything off the committing lists and dump पूर्णांकo @dst.  */
व्योम pnfs_generic_recover_commit_reqs(काष्ठा list_head *dst,
				      काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा pnfs_ds_commit_info *fl_cinfo = cinfo->ds;
	काष्ठा pnfs_commit_array *array;
	अचिन्हित पूर्णांक nwritten;

	lockdep_निश्चित_held(&NFS_I(cinfo->inode)->commit_mutex);
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(array, &fl_cinfo->commits, cinfo_list) अणु
		अगर (!array->lseg || !pnfs_get_commit_array(array))
			जारी;
		rcu_पढ़ो_unlock();
		nwritten = pnfs_bucket_recover_commit_reqs(dst,
							   array->buckets,
							   array->nbuckets,
							   cinfo);
		rcu_पढ़ो_lock();
		pnfs_put_commit_array(array, cinfo->inode);
		fl_cinfo->nwritten -= nwritten;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_recover_commit_reqs);

अटल काष्ठा nfs_page *
pnfs_bucket_search_commit_reqs(काष्ठा pnfs_commit_bucket *buckets,
		अचिन्हित पूर्णांक nbuckets, काष्ठा page *page)
अणु
	काष्ठा nfs_page *req;
	काष्ठा pnfs_commit_bucket *b;
	अचिन्हित पूर्णांक i;

	/* Linearly search the commit lists क्रम each bucket until a matching
	 * request is found */
	क्रम (i = 0, b = buckets; i < nbuckets; i++, b++) अणु
		list_क्रम_each_entry(req, &b->written, wb_list) अणु
			अगर (req->wb_page == page)
				वापस req->wb_head;
		पूर्ण
		list_क्रम_each_entry(req, &b->committing, wb_list) अणु
			अगर (req->wb_page == page)
				वापस req->wb_head;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* pnfs_generic_search_commit_reqs - Search lists in @cinfo क्रम the head reqest
 *				   क्रम @page
 * @cinfo - commit info क्रम current inode
 * @page - page to search क्रम matching head request
 *
 * Returns a the head request अगर one is found, otherwise वापसs शून्य.
 */
काष्ठा nfs_page *
pnfs_generic_search_commit_reqs(काष्ठा nfs_commit_info *cinfo, काष्ठा page *page)
अणु
	काष्ठा pnfs_ds_commit_info *fl_cinfo = cinfo->ds;
	काष्ठा pnfs_commit_array *array;
	काष्ठा nfs_page *req;

	list_क्रम_each_entry(array, &fl_cinfo->commits, cinfo_list) अणु
		req = pnfs_bucket_search_commit_reqs(array->buckets,
				array->nbuckets, page);
		अगर (req)
			वापस req;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_search_commit_reqs);

अटल काष्ठा pnfs_layout_segment *
pnfs_bucket_get_committing(काष्ठा list_head *head,
			   काष्ठा pnfs_commit_bucket *bucket,
			   काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा pnfs_layout_segment *lseg;
	काष्ठा list_head *pos;

	list_क्रम_each(pos, &bucket->committing)
		cinfo->ds->ncommitting--;
	list_splice_init(&bucket->committing, head);
	lseg = pnfs_मुक्त_bucket_lseg(bucket);
	अगर (!lseg)
		lseg = pnfs_get_lseg(bucket->lseg);
	वापस lseg;
पूर्ण

अटल काष्ठा nfs_commit_data *
pnfs_bucket_fetch_commitdata(काष्ठा pnfs_commit_bucket *bucket,
			     काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा nfs_commit_data *data = nfs_commitdata_alloc(false);

	अगर (!data)
		वापस शून्य;
	data->lseg = pnfs_bucket_get_committing(&data->pages, bucket, cinfo);
	वापस data;
पूर्ण

अटल व्योम pnfs_generic_retry_commit(काष्ठा pnfs_commit_bucket *buckets,
				      अचिन्हित पूर्णांक nbuckets,
				      काष्ठा nfs_commit_info *cinfo,
				      अचिन्हित पूर्णांक idx)
अणु
	काष्ठा pnfs_commit_bucket *bucket;
	काष्ठा pnfs_layout_segment *मुक्तme;
	LIST_HEAD(pages);

	क्रम (bucket = buckets; idx < nbuckets; bucket++, idx++) अणु
		अगर (list_empty(&bucket->committing))
			जारी;
		mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
		मुक्तme = pnfs_bucket_get_committing(&pages, bucket, cinfo);
		mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
		nfs_retry_commit(&pages, मुक्तme, cinfo, idx);
		pnfs_put_lseg(मुक्तme);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
pnfs_bucket_alloc_ds_commits(काष्ठा list_head *list,
			     काष्ठा pnfs_commit_bucket *buckets,
			     अचिन्हित पूर्णांक nbuckets,
			     काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा pnfs_commit_bucket *bucket;
	काष्ठा nfs_commit_data *data;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक nreq = 0;

	क्रम (i = 0, bucket = buckets; i < nbuckets; i++, bucket++) अणु
		अगर (list_empty(&bucket->committing))
			जारी;
		mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
		अगर (!list_empty(&bucket->committing)) अणु
			data = pnfs_bucket_fetch_commitdata(bucket, cinfo);
			अगर (!data)
				जाओ out_error;
			data->ds_commit_index = i;
			list_add_tail(&data->list, list);
			atomic_inc(&cinfo->mds->rpcs_out);
			nreq++;
		पूर्ण
		mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
	पूर्ण
	वापस nreq;
out_error:
	mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
	/* Clean up on error */
	pnfs_generic_retry_commit(buckets, nbuckets, cinfo, i);
	वापस nreq;
पूर्ण

अटल अचिन्हित पूर्णांक
pnfs_alloc_ds_commits_list(काष्ठा list_head *list,
			   काष्ठा pnfs_ds_commit_info *fl_cinfo,
			   काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा pnfs_commit_array *array;
	अचिन्हित पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(array, &fl_cinfo->commits, cinfo_list) अणु
		अगर (!array->lseg || !pnfs_get_commit_array(array))
			जारी;
		rcu_पढ़ो_unlock();
		ret += pnfs_bucket_alloc_ds_commits(list, array->buckets,
				array->nbuckets, cinfo);
		rcu_पढ़ो_lock();
		pnfs_put_commit_array(array, cinfo->inode);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/* This follows nfs_commit_list pretty बंदly */
पूर्णांक
pnfs_generic_commit_pagelist(काष्ठा inode *inode, काष्ठा list_head *mds_pages,
			     पूर्णांक how, काष्ठा nfs_commit_info *cinfo,
			     पूर्णांक (*initiate_commit)(काष्ठा nfs_commit_data *data,
						    पूर्णांक how))
अणु
	काष्ठा pnfs_ds_commit_info *fl_cinfo = cinfo->ds;
	काष्ठा nfs_commit_data *data, *पंचांगp;
	LIST_HEAD(list);
	अचिन्हित पूर्णांक nreq = 0;

	अगर (!list_empty(mds_pages)) अणु
		data = nfs_commitdata_alloc(true);
		data->ds_commit_index = -1;
		list_splice_init(mds_pages, &data->pages);
		list_add_tail(&data->list, &list);
		atomic_inc(&cinfo->mds->rpcs_out);
		nreq++;
	पूर्ण

	nreq += pnfs_alloc_ds_commits_list(&list, fl_cinfo, cinfo);
	अगर (nreq == 0)
		जाओ out;

	list_क्रम_each_entry_safe(data, पंचांगp, &list, list) अणु
		list_del(&data->list);
		अगर (data->ds_commit_index < 0) अणु
			nfs_init_commit(data, शून्य, शून्य, cinfo);
			nfs_initiate_commit(NFS_CLIENT(inode), data,
					    NFS_PROTO(data->inode),
					    data->mds_ops, how,
					    RPC_TASK_CRED_NOREF);
		पूर्ण अन्यथा अणु
			nfs_init_commit(data, शून्य, data->lseg, cinfo);
			initiate_commit(data, how);
		पूर्ण
	पूर्ण
out:
	वापस PNFS_ATTEMPTED;
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_generic_commit_pagelist);

/*
 * Data server cache
 *
 * Data servers can be mapped to dअगरferent device ids.
 * nfs4_pnfs_ds reference counting
 *   - set to 1 on allocation
 *   - incremented when a device id maps a data server alपढ़ोy in the cache.
 *   - decremented when deviceid is हटाओd from the cache.
 */
अटल DEFINE_SPINLOCK(nfs4_ds_cache_lock);
अटल LIST_HEAD(nfs4_data_server_cache);

/* Debug routines */
अटल व्योम
prपूर्णांक_ds(काष्ठा nfs4_pnfs_ds *ds)
अणु
	अगर (ds == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "%s NULL device\n", __func__);
		वापस;
	पूर्ण
	prपूर्णांकk(KERN_WARNING "        ds %s\n"
		"        ref count %d\n"
		"        client %p\n"
		"        cl_exchange_flags %x\n",
		ds->ds_remotestr,
		refcount_पढ़ो(&ds->ds_count), ds->ds_clp,
		ds->ds_clp ? ds->ds_clp->cl_exchange_flags : 0);
पूर्ण

अटल bool
same_sockaddr(काष्ठा sockaddr *addr1, काष्ठा sockaddr *addr2)
अणु
	काष्ठा sockaddr_in *a, *b;
	काष्ठा sockaddr_in6 *a6, *b6;

	अगर (addr1->sa_family != addr2->sa_family)
		वापस false;

	चयन (addr1->sa_family) अणु
	हाल AF_INET:
		a = (काष्ठा sockaddr_in *)addr1;
		b = (काष्ठा sockaddr_in *)addr2;

		अगर (a->sin_addr.s_addr == b->sin_addr.s_addr &&
		    a->sin_port == b->sin_port)
			वापस true;
		अवरोध;

	हाल AF_INET6:
		a6 = (काष्ठा sockaddr_in6 *)addr1;
		b6 = (काष्ठा sockaddr_in6 *)addr2;

		/* LINKLOCAL addresses must have matching scope_id */
		अगर (ipv6_addr_src_scope(&a6->sin6_addr) ==
		    IPV6_ADDR_SCOPE_LINKLOCAL &&
		    a6->sin6_scope_id != b6->sin6_scope_id)
			वापस false;

		अगर (ipv6_addr_equal(&a6->sin6_addr, &b6->sin6_addr) &&
		    a6->sin6_port == b6->sin6_port)
			वापस true;
		अवरोध;

	शेष:
		dprपूर्णांकk("%s: unhandled address family: %u\n",
			__func__, addr1->sa_family);
		वापस false;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Checks अगर 'dsaddrs1' contains a subset of 'dsaddrs2'. If it करोes,
 * declare a match.
 */
अटल bool
_same_data_server_addrs_locked(स्थिर काष्ठा list_head *dsaddrs1,
			       स्थिर काष्ठा list_head *dsaddrs2)
अणु
	काष्ठा nfs4_pnfs_ds_addr *da1, *da2;
	काष्ठा sockaddr *sa1, *sa2;
	bool match = false;

	list_क्रम_each_entry(da1, dsaddrs1, da_node) अणु
		sa1 = (काष्ठा sockaddr *)&da1->da_addr;
		match = false;
		list_क्रम_each_entry(da2, dsaddrs2, da_node) अणु
			sa2 = (काष्ठा sockaddr *)&da2->da_addr;
			match = same_sockaddr(sa1, sa2);
			अगर (match)
				अवरोध;
		पूर्ण
		अगर (!match)
			अवरोध;
	पूर्ण
	वापस match;
पूर्ण

/*
 * Lookup DS by addresses.  nfs4_ds_cache_lock is held
 */
अटल काष्ठा nfs4_pnfs_ds *
_data_server_lookup_locked(स्थिर काष्ठा list_head *dsaddrs)
अणु
	काष्ठा nfs4_pnfs_ds *ds;

	list_क्रम_each_entry(ds, &nfs4_data_server_cache, ds_node)
		अगर (_same_data_server_addrs_locked(&ds->ds_addrs, dsaddrs))
			वापस ds;
	वापस शून्य;
पूर्ण

अटल काष्ठा nfs4_pnfs_ds_addr *nfs4_pnfs_ds_addr_alloc(gfp_t gfp_flags)
अणु
	काष्ठा nfs4_pnfs_ds_addr *da = kzalloc(माप(*da), gfp_flags);
	अगर (da)
		INIT_LIST_HEAD(&da->da_node);
	वापस da;
पूर्ण

अटल व्योम nfs4_pnfs_ds_addr_मुक्त(काष्ठा nfs4_pnfs_ds_addr *da)
अणु
	kमुक्त(da->da_remotestr);
	kमुक्त(da->da_netid);
	kमुक्त(da);
पूर्ण

अटल व्योम destroy_ds(काष्ठा nfs4_pnfs_ds *ds)
अणु
	काष्ठा nfs4_pnfs_ds_addr *da;

	dprपूर्णांकk("--> %s\n", __func__);
	अगरdebug(FACILITY)
		prपूर्णांक_ds(ds);

	nfs_put_client(ds->ds_clp);

	जबतक (!list_empty(&ds->ds_addrs)) अणु
		da = list_first_entry(&ds->ds_addrs,
				      काष्ठा nfs4_pnfs_ds_addr,
				      da_node);
		list_del_init(&da->da_node);
		nfs4_pnfs_ds_addr_मुक्त(da);
	पूर्ण

	kमुक्त(ds->ds_remotestr);
	kमुक्त(ds);
पूर्ण

व्योम nfs4_pnfs_ds_put(काष्ठा nfs4_pnfs_ds *ds)
अणु
	अगर (refcount_dec_and_lock(&ds->ds_count,
				&nfs4_ds_cache_lock)) अणु
		list_del_init(&ds->ds_node);
		spin_unlock(&nfs4_ds_cache_lock);
		destroy_ds(ds);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_pnfs_ds_put);

/*
 * Create a string with a human पढ़ोable address and port to aव्योम
 * complicated setup around many dprinks.
 */
अटल अक्षर *
nfs4_pnfs_remotestr(काष्ठा list_head *dsaddrs, gfp_t gfp_flags)
अणु
	काष्ठा nfs4_pnfs_ds_addr *da;
	अक्षर *remotestr;
	माप_प्रकार len;
	अक्षर *p;

	len = 3;        /* '{', '}' and eol */
	list_क्रम_each_entry(da, dsaddrs, da_node) अणु
		len += म_माप(da->da_remotestr) + 1;    /* string plus comma */
	पूर्ण

	remotestr = kzalloc(len, gfp_flags);
	अगर (!remotestr)
		वापस शून्य;

	p = remotestr;
	*(p++) = '{';
	len--;
	list_क्रम_each_entry(da, dsaddrs, da_node) अणु
		माप_प्रकार ll = म_माप(da->da_remotestr);

		अगर (ll > len)
			जाओ out_err;

		स_नकल(p, da->da_remotestr, ll);
		p += ll;
		len -= ll;

		अगर (len < 1)
			जाओ out_err;
		(*p++) = ',';
		len--;
	पूर्ण
	अगर (len < 2)
		जाओ out_err;
	*(p++) = '}';
	*p = '\0';
	वापस remotestr;
out_err:
	kमुक्त(remotestr);
	वापस शून्य;
पूर्ण

/*
 * Given a list of multipath काष्ठा nfs4_pnfs_ds_addr, add it to ds cache अगर
 * uncached and वापस cached काष्ठा nfs4_pnfs_ds.
 */
काष्ठा nfs4_pnfs_ds *
nfs4_pnfs_ds_add(काष्ठा list_head *dsaddrs, gfp_t gfp_flags)
अणु
	काष्ठा nfs4_pnfs_ds *पंचांगp_ds, *ds = शून्य;
	अक्षर *remotestr;

	अगर (list_empty(dsaddrs)) अणु
		dprपूर्णांकk("%s: no addresses defined\n", __func__);
		जाओ out;
	पूर्ण

	ds = kzalloc(माप(*ds), gfp_flags);
	अगर (!ds)
		जाओ out;

	/* this is only used क्रम debugging, so it's ok अगर its शून्य */
	remotestr = nfs4_pnfs_remotestr(dsaddrs, gfp_flags);

	spin_lock(&nfs4_ds_cache_lock);
	पंचांगp_ds = _data_server_lookup_locked(dsaddrs);
	अगर (पंचांगp_ds == शून्य) अणु
		INIT_LIST_HEAD(&ds->ds_addrs);
		list_splice_init(dsaddrs, &ds->ds_addrs);
		ds->ds_remotestr = remotestr;
		refcount_set(&ds->ds_count, 1);
		INIT_LIST_HEAD(&ds->ds_node);
		ds->ds_clp = शून्य;
		list_add(&ds->ds_node, &nfs4_data_server_cache);
		dprपूर्णांकk("%s add new data server %s\n", __func__,
			ds->ds_remotestr);
	पूर्ण अन्यथा अणु
		kमुक्त(remotestr);
		kमुक्त(ds);
		refcount_inc(&पंचांगp_ds->ds_count);
		dprपूर्णांकk("%s data server %s found, inc'ed ds_count to %d\n",
			__func__, पंचांगp_ds->ds_remotestr,
			refcount_पढ़ो(&पंचांगp_ds->ds_count));
		ds = पंचांगp_ds;
	पूर्ण
	spin_unlock(&nfs4_ds_cache_lock);
out:
	वापस ds;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_pnfs_ds_add);

अटल व्योम nfs4_रुको_ds_connect(काष्ठा nfs4_pnfs_ds *ds)
अणु
	might_sleep();
	रुको_on_bit(&ds->ds_state, NFS4DS_CONNECTING,
			TASK_KILLABLE);
पूर्ण

अटल व्योम nfs4_clear_ds_conn_bit(काष्ठा nfs4_pnfs_ds *ds)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(NFS4DS_CONNECTING, &ds->ds_state);
	smp_mb__after_atomic();
	wake_up_bit(&ds->ds_state, NFS4DS_CONNECTING);
पूर्ण

अटल काष्ठा nfs_client *(*get_v3_ds_connect)(
			काष्ठा nfs_server *mds_srv,
			स्थिर काष्ठा sockaddr *ds_addr,
			पूर्णांक ds_addrlen,
			पूर्णांक ds_proto,
			अचिन्हित पूर्णांक ds_समयo,
			अचिन्हित पूर्णांक ds_retrans);

अटल bool load_v3_ds_connect(व्योम)
अणु
	अगर (!get_v3_ds_connect) अणु
		get_v3_ds_connect = symbol_request(nfs3_set_ds_client);
		WARN_ON_ONCE(!get_v3_ds_connect);
	पूर्ण

	वापस(get_v3_ds_connect != शून्य);
पूर्ण

व्योम nfs4_pnfs_v3_ds_connect_unload(व्योम)
अणु
	अगर (get_v3_ds_connect) अणु
		symbol_put(nfs3_set_ds_client);
		get_v3_ds_connect = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक _nfs4_pnfs_v3_ds_connect(काष्ठा nfs_server *mds_srv,
				 काष्ठा nfs4_pnfs_ds *ds,
				 अचिन्हित पूर्णांक समयo,
				 अचिन्हित पूर्णांक retrans)
अणु
	काष्ठा nfs_client *clp = ERR_PTR(-EIO);
	काष्ठा nfs4_pnfs_ds_addr *da;
	पूर्णांक status = 0;

	dprपूर्णांकk("--> %s DS %s\n", __func__, ds->ds_remotestr);

	अगर (!load_v3_ds_connect())
		जाओ out;

	list_क्रम_each_entry(da, &ds->ds_addrs, da_node) अणु
		dprपूर्णांकk("%s: DS %s: trying address %s\n",
			__func__, ds->ds_remotestr, da->da_remotestr);

		अगर (!IS_ERR(clp)) अणु
			काष्ठा xprt_create xprt_args = अणु
				.ident = da->da_transport,
				.net = clp->cl_net,
				.dstaddr = (काष्ठा sockaddr *)&da->da_addr,
				.addrlen = da->da_addrlen,
				.servername = clp->cl_hostname,
			पूर्ण;

			अगर (da->da_transport != clp->cl_proto)
				जारी;
			अगर (da->da_addr.ss_family != clp->cl_addr.ss_family)
				जारी;
			/* Add this address as an alias */
			rpc_clnt_add_xprt(clp->cl_rpcclient, &xprt_args,
					rpc_clnt_test_and_add_xprt, शून्य);
			जारी;
		पूर्ण
		clp = get_v3_ds_connect(mds_srv,
				(काष्ठा sockaddr *)&da->da_addr,
				da->da_addrlen, da->da_transport,
				समयo, retrans);
		अगर (IS_ERR(clp))
			जारी;
		clp->cl_rpcclient->cl_softerr = 0;
		clp->cl_rpcclient->cl_softrtry = 0;
	पूर्ण

	अगर (IS_ERR(clp)) अणु
		status = PTR_ERR(clp);
		जाओ out;
	पूर्ण

	smp_wmb();
	ds->ds_clp = clp;
	dprपूर्णांकk("%s [new] addr: %s\n", __func__, ds->ds_remotestr);
out:
	वापस status;
पूर्ण

अटल पूर्णांक _nfs4_pnfs_v4_ds_connect(काष्ठा nfs_server *mds_srv,
				 काष्ठा nfs4_pnfs_ds *ds,
				 अचिन्हित पूर्णांक समयo,
				 अचिन्हित पूर्णांक retrans,
				 u32 minor_version)
अणु
	काष्ठा nfs_client *clp = ERR_PTR(-EIO);
	काष्ठा nfs4_pnfs_ds_addr *da;
	पूर्णांक status = 0;

	dprपूर्णांकk("--> %s DS %s\n", __func__, ds->ds_remotestr);

	list_क्रम_each_entry(da, &ds->ds_addrs, da_node) अणु
		dprपूर्णांकk("%s: DS %s: trying address %s\n",
			__func__, ds->ds_remotestr, da->da_remotestr);

		अगर (!IS_ERR(clp) && clp->cl_mvops->session_trunk) अणु
			काष्ठा xprt_create xprt_args = अणु
				.ident = da->da_transport,
				.net = clp->cl_net,
				.dstaddr = (काष्ठा sockaddr *)&da->da_addr,
				.addrlen = da->da_addrlen,
				.servername = clp->cl_hostname,
			पूर्ण;
			काष्ठा nfs4_add_xprt_data xprtdata = अणु
				.clp = clp,
			पूर्ण;
			काष्ठा rpc_add_xprt_test rpcdata = अणु
				.add_xprt_test = clp->cl_mvops->session_trunk,
				.data = &xprtdata,
			पूर्ण;

			अगर (da->da_transport != clp->cl_proto)
				जारी;
			अगर (da->da_addr.ss_family != clp->cl_addr.ss_family)
				जारी;
			/**
			* Test this address क्रम session trunking and
			* add as an alias
			*/
			xprtdata.cred = nfs4_get_clid_cred(clp),
			rpc_clnt_add_xprt(clp->cl_rpcclient, &xprt_args,
					  rpc_clnt_setup_test_and_add_xprt,
					  &rpcdata);
			अगर (xprtdata.cred)
				put_cred(xprtdata.cred);
		पूर्ण अन्यथा अणु
			clp = nfs4_set_ds_client(mds_srv,
						(काष्ठा sockaddr *)&da->da_addr,
						da->da_addrlen,
						da->da_transport, समयo,
						retrans, minor_version);
			अगर (IS_ERR(clp))
				जारी;

			status = nfs4_init_ds_session(clp,
					mds_srv->nfs_client->cl_lease_समय);
			अगर (status) अणु
				nfs_put_client(clp);
				clp = ERR_PTR(-EIO);
				जारी;
			पूर्ण

		पूर्ण
	पूर्ण

	अगर (IS_ERR(clp)) अणु
		status = PTR_ERR(clp);
		जाओ out;
	पूर्ण

	smp_wmb();
	ds->ds_clp = clp;
	dprपूर्णांकk("%s [new] addr: %s\n", __func__, ds->ds_remotestr);
out:
	वापस status;
पूर्ण

/*
 * Create an rpc connection to the nfs4_pnfs_ds data server.
 * Currently only supports IPv4 and IPv6 addresses.
 * If connection fails, make devid unavailable and वापस a -त्रुटि_सं.
 */
पूर्णांक nfs4_pnfs_ds_connect(काष्ठा nfs_server *mds_srv, काष्ठा nfs4_pnfs_ds *ds,
			  काष्ठा nfs4_deviceid_node *devid, अचिन्हित पूर्णांक समयo,
			  अचिन्हित पूर्णांक retrans, u32 version, u32 minor_version)
अणु
	पूर्णांक err;

again:
	err = 0;
	अगर (test_and_set_bit(NFS4DS_CONNECTING, &ds->ds_state) == 0) अणु
		अगर (version == 3) अणु
			err = _nfs4_pnfs_v3_ds_connect(mds_srv, ds, समयo,
						       retrans);
		पूर्ण अन्यथा अगर (version == 4) अणु
			err = _nfs4_pnfs_v4_ds_connect(mds_srv, ds, समयo,
						       retrans, minor_version);
		पूर्ण अन्यथा अणु
			dprपूर्णांकk("%s: unsupported DS version %d\n", __func__,
				version);
			err = -EPROTONOSUPPORT;
		पूर्ण

		nfs4_clear_ds_conn_bit(ds);
	पूर्ण अन्यथा अणु
		nfs4_रुको_ds_connect(ds);

		/* what was रुकोed on didn't connect AND didn't mark unavail */
		अगर (!ds->ds_clp && !nfs4_test_deviceid_unavailable(devid))
			जाओ again;
	पूर्ण

	/*
	 * At this poपूर्णांक the ds->ds_clp should be पढ़ोy, but it might have
	 * hit an error.
	 */
	अगर (!err) अणु
		अगर (!ds->ds_clp || !nfs_client_init_is_complete(ds->ds_clp)) अणु
			WARN_ON_ONCE(ds->ds_clp ||
				!nfs4_test_deviceid_unavailable(devid));
			वापस -EINVAL;
		पूर्ण
		err = nfs_client_init_status(ds->ds_clp);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_pnfs_ds_connect);

/*
 * Currently only supports ipv4, ipv6 and one multi-path address.
 */
काष्ठा nfs4_pnfs_ds_addr *
nfs4_decode_mp_ds_addr(काष्ठा net *net, काष्ठा xdr_stream *xdr, gfp_t gfp_flags)
अणु
	काष्ठा nfs4_pnfs_ds_addr *da = शून्य;
	अक्षर *buf, *portstr;
	__be16 port;
	sमाप_प्रकार nlen, rlen;
	पूर्णांक पंचांगp[2];
	अक्षर *netid;
	माप_प्रकार len;
	अक्षर *startsep = "";
	अक्षर *endsep = "";


	/* r_netid */
	nlen = xdr_stream_decode_string_dup(xdr, &netid, XDR_MAX_NETOBJ,
					    gfp_flags);
	अगर (unlikely(nlen < 0))
		जाओ out_err;

	/* r_addr: ip/ip6addr with port in dec octets - see RFC 5665 */
	/* port is ".ABC.DEF", 8 अक्षरs max */
	rlen = xdr_stream_decode_string_dup(xdr, &buf, INET6_ADDRSTRLEN +
					    IPV6_SCOPE_ID_LEN + 8, gfp_flags);
	अगर (unlikely(rlen < 0))
		जाओ out_मुक्त_netid;

	/* replace port '.' with '-' */
	portstr = म_खोजप(buf, '.');
	अगर (!portstr) अणु
		dprपूर्णांकk("%s: Failed finding expected dot in port\n",
			__func__);
		जाओ out_मुक्त_buf;
	पूर्ण
	*portstr = '-';

	/* find '.' between address and port */
	portstr = म_खोजप(buf, '.');
	अगर (!portstr) अणु
		dprपूर्णांकk("%s: Failed finding expected dot between address and "
			"port\n", __func__);
		जाओ out_मुक्त_buf;
	पूर्ण
	*portstr = '\0';

	da = nfs4_pnfs_ds_addr_alloc(gfp_flags);
	अगर (unlikely(!da))
		जाओ out_मुक्त_buf;

	अगर (!rpc_pton(net, buf, portstr-buf, (काष्ठा sockaddr *)&da->da_addr,
		      माप(da->da_addr))) अणु
		dprपूर्णांकk("%s: error parsing address %s\n", __func__, buf);
		जाओ out_मुक्त_da;
	पूर्ण

	portstr++;
	माला_पूछो(portstr, "%d-%d", &पंचांगp[0], &पंचांगp[1]);
	port = htons((पंचांगp[0] << 8) | (पंचांगp[1]));

	चयन (da->da_addr.ss_family) अणु
	हाल AF_INET:
		((काष्ठा sockaddr_in *)&da->da_addr)->sin_port = port;
		da->da_addrlen = माप(काष्ठा sockaddr_in);
		अवरोध;

	हाल AF_INET6:
		((काष्ठा sockaddr_in6 *)&da->da_addr)->sin6_port = port;
		da->da_addrlen = माप(काष्ठा sockaddr_in6);
		startsep = "[";
		endsep = "]";
		अवरोध;

	शेष:
		dprपूर्णांकk("%s: unsupported address family: %u\n",
			__func__, da->da_addr.ss_family);
		जाओ out_मुक्त_da;
	पूर्ण

	da->da_transport = xprt_find_transport_ident(netid);
	अगर (da->da_transport < 0) अणु
		dprपूर्णांकk("%s: ERROR: unknown r_netid \"%s\"\n",
			__func__, netid);
		जाओ out_मुक्त_da;
	पूर्ण

	da->da_netid = netid;

	/* save human पढ़ोable address */
	len = म_माप(startsep) + म_माप(buf) + म_माप(endsep) + 7;
	da->da_remotestr = kzalloc(len, gfp_flags);

	/* शून्य is ok, only used क्रम dprपूर्णांकk */
	अगर (da->da_remotestr)
		snम_लिखो(da->da_remotestr, len, "%s%s%s:%u", startsep,
			 buf, endsep, ntohs(port));

	dprपूर्णांकk("%s: Parsed DS addr %s\n", __func__, da->da_remotestr);
	kमुक्त(buf);
	वापस da;

out_मुक्त_da:
	kमुक्त(da);
out_मुक्त_buf:
	dprपूर्णांकk("%s: Error parsing DS addr: %s\n", __func__, buf);
	kमुक्त(buf);
out_मुक्त_netid:
	kमुक्त(netid);
out_err:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_decode_mp_ds_addr);

व्योम
pnfs_layout_mark_request_commit(काष्ठा nfs_page *req,
				काष्ठा pnfs_layout_segment *lseg,
				काष्ठा nfs_commit_info *cinfo,
				u32 ds_commit_idx)
अणु
	काष्ठा list_head *list;
	काष्ठा pnfs_commit_array *array;
	काष्ठा pnfs_commit_bucket *bucket;

	mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
	array = pnfs_lookup_commit_array(cinfo->ds, lseg);
	अगर (!array || !pnfs_is_valid_lseg(lseg))
		जाओ out_resched;
	bucket = &array->buckets[ds_commit_idx];
	list = &bucket->written;
	/* Non-empty buckets hold a reference on the lseg.  That ref
	 * is normally transferred to the COMMIT call and released
	 * there.  It could also be released अगर the last req is pulled
	 * off due to a reग_लिखो, in which हाल it will be करोne in
	 * pnfs_common_clear_request_commit
	 */
	अगर (!bucket->lseg)
		bucket->lseg = pnfs_get_lseg(lseg);
	set_bit(PG_COMMIT_TO_DS, &req->wb_flags);
	cinfo->ds->nwritten++;

	nfs_request_add_commit_list_locked(req, list, cinfo);
	mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
	nfs_mark_page_unstable(req->wb_page, cinfo);
	वापस;
out_resched:
	mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
	cinfo->completion_ops->resched_ग_लिखो(cinfo, req);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_layout_mark_request_commit);

पूर्णांक
pnfs_nfs_generic_sync(काष्ठा inode *inode, bool datasync)
अणु
	पूर्णांक ret;

	अगर (!pnfs_layoutcommit_outstanding(inode))
		वापस 0;
	ret = nfs_commit_inode(inode, FLUSH_SYNC);
	अगर (ret < 0)
		वापस ret;
	अगर (datasync)
		वापस 0;
	वापस pnfs_layoutcommit_inode(inode, true);
पूर्ण
EXPORT_SYMBOL_GPL(pnfs_nfs_generic_sync);

