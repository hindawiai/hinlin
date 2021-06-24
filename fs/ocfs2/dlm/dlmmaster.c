<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmmod.c
 *
 * standalone DLM module
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */


#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/socket.h>
#समावेश <linux/inet.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>


#समावेश "../cluster/heartbeat.h"
#समावेश "../cluster/nodemanager.h"
#समावेश "../cluster/tcp.h"

#समावेश "dlmapi.h"
#समावेश "dlmcommon.h"
#समावेश "dlmdomain.h"
#समावेश "dlmdebug.h"

#घोषणा MLOG_MASK_PREFIX (ML_DLM|ML_DLM_MASTER)
#समावेश "../cluster/masklog.h"

अटल व्योम dlm_mle_node_करोwn(काष्ठा dlm_ctxt *dlm,
			      काष्ठा dlm_master_list_entry *mle,
			      काष्ठा o2nm_node *node,
			      पूर्णांक idx);
अटल व्योम dlm_mle_node_up(काष्ठा dlm_ctxt *dlm,
			    काष्ठा dlm_master_list_entry *mle,
			    काष्ठा o2nm_node *node,
			    पूर्णांक idx);

अटल व्योम dlm_निश्चित_master_worker(काष्ठा dlm_work_item *item, व्योम *data);
अटल पूर्णांक dlm_करो_निश्चित_master(काष्ठा dlm_ctxt *dlm,
				काष्ठा dlm_lock_resource *res,
				व्योम *nodemap, u32 flags);
अटल व्योम dlm_deref_lockres_worker(काष्ठा dlm_work_item *item, व्योम *data);

अटल अंतरभूत पूर्णांक dlm_mle_equal(काष्ठा dlm_ctxt *dlm,
				काष्ठा dlm_master_list_entry *mle,
				स्थिर अक्षर *name,
				अचिन्हित पूर्णांक namelen)
अणु
	अगर (dlm != mle->dlm)
		वापस 0;

	अगर (namelen != mle->mnamelen ||
	    स_भेद(name, mle->mname, namelen) != 0)
		वापस 0;

	वापस 1;
पूर्ण

अटल काष्ठा kmem_cache *dlm_lockres_cache;
अटल काष्ठा kmem_cache *dlm_lockname_cache;
अटल काष्ठा kmem_cache *dlm_mle_cache;

अटल व्योम dlm_mle_release(काष्ठा kref *kref);
अटल व्योम dlm_init_mle(काष्ठा dlm_master_list_entry *mle,
			क्रमागत dlm_mle_type type,
			काष्ठा dlm_ctxt *dlm,
			काष्ठा dlm_lock_resource *res,
			स्थिर अक्षर *name,
			अचिन्हित पूर्णांक namelen);
अटल व्योम dlm_put_mle(काष्ठा dlm_master_list_entry *mle);
अटल व्योम __dlm_put_mle(काष्ठा dlm_master_list_entry *mle);
अटल पूर्णांक dlm_find_mle(काष्ठा dlm_ctxt *dlm,
			काष्ठा dlm_master_list_entry **mle,
			अक्षर *name, अचिन्हित पूर्णांक namelen);

अटल पूर्णांक dlm_करो_master_request(काष्ठा dlm_lock_resource *res,
				 काष्ठा dlm_master_list_entry *mle, पूर्णांक to);


अटल पूर्णांक dlm_रुको_क्रम_lock_mastery(काष्ठा dlm_ctxt *dlm,
				     काष्ठा dlm_lock_resource *res,
				     काष्ठा dlm_master_list_entry *mle,
				     पूर्णांक *blocked);
अटल पूर्णांक dlm_restart_lock_mastery(काष्ठा dlm_ctxt *dlm,
				    काष्ठा dlm_lock_resource *res,
				    काष्ठा dlm_master_list_entry *mle,
				    पूर्णांक blocked);
अटल पूर्णांक dlm_add_migration_mle(काष्ठा dlm_ctxt *dlm,
				 काष्ठा dlm_lock_resource *res,
				 काष्ठा dlm_master_list_entry *mle,
				 काष्ठा dlm_master_list_entry **oldmle,
				 स्थिर अक्षर *name, अचिन्हित पूर्णांक namelen,
				 u8 new_master, u8 master);

अटल u8 dlm_pick_migration_target(काष्ठा dlm_ctxt *dlm,
				    काष्ठा dlm_lock_resource *res);
अटल व्योम dlm_हटाओ_nonlocal_locks(काष्ठा dlm_ctxt *dlm,
				      काष्ठा dlm_lock_resource *res);
अटल पूर्णांक dlm_mark_lockres_migrating(काष्ठा dlm_ctxt *dlm,
				       काष्ठा dlm_lock_resource *res,
				       u8 target);
अटल पूर्णांक dlm_pre_master_reco_lockres(काष्ठा dlm_ctxt *dlm,
				       काष्ठा dlm_lock_resource *res);


पूर्णांक dlm_is_host_करोwn(पूर्णांक त्रुटि_सं)
अणु
	चयन (त्रुटि_सं) अणु
		हाल -EBADF:
		हाल -ECONNREFUSED:
		हाल -ENOTCONN:
		हाल -ECONNRESET:
		हाल -EPIPE:
		हाल -EHOSTDOWN:
		हाल -EHOSTUNREACH:
		हाल -ETIMEDOUT:
		हाल -ECONNABORTED:
		हाल -ENETDOWN:
		हाल -ENETUNREACH:
		हाल -ENETRESET:
		हाल -ESHUTDOWN:
		हाल -ENOPROTOOPT:
		हाल -EINVAL:   /* अगर वापसed from our tcp code,
				   this means there is no socket */
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * MASTER LIST FUNCTIONS
 */


/*
 * regarding master list entries and heartbeat callbacks:
 *
 * in order to aव्योम sleeping and allocation that occurs in
 * heartbeat, master list entries are simply attached to the
 * dlm's established heartbeat callbacks.  the mle is attached
 * when it is created, and since the dlm->spinlock is held at
 * that समय, any heartbeat event will be properly discovered
 * by the mle.  the mle needs to be detached from the
 * dlm->mle_hb_events list as soon as heartbeat events are no
 * दीर्घer useful to the mle, and beक्रमe the mle is मुक्तd.
 *
 * as a general rule, heartbeat events are no दीर्घer needed by
 * the mle once an "answer" regarding the lock master has been
 * received.
 */
अटल अंतरभूत व्योम __dlm_mle_attach_hb_events(काष्ठा dlm_ctxt *dlm,
					      काष्ठा dlm_master_list_entry *mle)
अणु
	निश्चित_spin_locked(&dlm->spinlock);

	list_add_tail(&mle->hb_events, &dlm->mle_hb_events);
पूर्ण


अटल अंतरभूत व्योम __dlm_mle_detach_hb_events(काष्ठा dlm_ctxt *dlm,
					      काष्ठा dlm_master_list_entry *mle)
अणु
	अगर (!list_empty(&mle->hb_events))
		list_del_init(&mle->hb_events);
पूर्ण


अटल अंतरभूत व्योम dlm_mle_detach_hb_events(काष्ठा dlm_ctxt *dlm,
					    काष्ठा dlm_master_list_entry *mle)
अणु
	spin_lock(&dlm->spinlock);
	__dlm_mle_detach_hb_events(dlm, mle);
	spin_unlock(&dlm->spinlock);
पूर्ण

अटल व्योम dlm_get_mle_inuse(काष्ठा dlm_master_list_entry *mle)
अणु
	काष्ठा dlm_ctxt *dlm;
	dlm = mle->dlm;

	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&dlm->master_lock);
	mle->inuse++;
	kref_get(&mle->mle_refs);
पूर्ण

अटल व्योम dlm_put_mle_inuse(काष्ठा dlm_master_list_entry *mle)
अणु
	काष्ठा dlm_ctxt *dlm;
	dlm = mle->dlm;

	spin_lock(&dlm->spinlock);
	spin_lock(&dlm->master_lock);
	mle->inuse--;
	__dlm_put_mle(mle);
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);

पूर्ण

/* हटाओ from list and मुक्त */
अटल व्योम __dlm_put_mle(काष्ठा dlm_master_list_entry *mle)
अणु
	काष्ठा dlm_ctxt *dlm;
	dlm = mle->dlm;

	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&dlm->master_lock);
	अगर (!kref_पढ़ो(&mle->mle_refs)) अणु
		/* this may or may not crash, but who cares.
		 * it's a BUG. */
		mlog(ML_ERROR, "bad mle: %p\n", mle);
		dlm_prपूर्णांक_one_mle(mle);
		BUG();
	पूर्ण अन्यथा
		kref_put(&mle->mle_refs, dlm_mle_release);
पूर्ण


/* must not have any spinlocks coming in */
अटल व्योम dlm_put_mle(काष्ठा dlm_master_list_entry *mle)
अणु
	काष्ठा dlm_ctxt *dlm;
	dlm = mle->dlm;

	spin_lock(&dlm->spinlock);
	spin_lock(&dlm->master_lock);
	__dlm_put_mle(mle);
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);
पूर्ण

अटल अंतरभूत व्योम dlm_get_mle(काष्ठा dlm_master_list_entry *mle)
अणु
	kref_get(&mle->mle_refs);
पूर्ण

अटल व्योम dlm_init_mle(काष्ठा dlm_master_list_entry *mle,
			क्रमागत dlm_mle_type type,
			काष्ठा dlm_ctxt *dlm,
			काष्ठा dlm_lock_resource *res,
			स्थिर अक्षर *name,
			अचिन्हित पूर्णांक namelen)
अणु
	निश्चित_spin_locked(&dlm->spinlock);

	mle->dlm = dlm;
	mle->type = type;
	INIT_HLIST_NODE(&mle->master_hash_node);
	INIT_LIST_HEAD(&mle->hb_events);
	स_रखो(mle->maybe_map, 0, माप(mle->maybe_map));
	spin_lock_init(&mle->spinlock);
	init_रुकोqueue_head(&mle->wq);
	atomic_set(&mle->woken, 0);
	kref_init(&mle->mle_refs);
	स_रखो(mle->response_map, 0, माप(mle->response_map));
	mle->master = O2NM_MAX_NODES;
	mle->new_master = O2NM_MAX_NODES;
	mle->inuse = 0;

	BUG_ON(mle->type != DLM_MLE_BLOCK &&
	       mle->type != DLM_MLE_MASTER &&
	       mle->type != DLM_MLE_MIGRATION);

	अगर (mle->type == DLM_MLE_MASTER) अणु
		BUG_ON(!res);
		mle->mleres = res;
		स_नकल(mle->mname, res->lockname.name, res->lockname.len);
		mle->mnamelen = res->lockname.len;
		mle->mnamehash = res->lockname.hash;
	पूर्ण अन्यथा अणु
		BUG_ON(!name);
		mle->mleres = शून्य;
		स_नकल(mle->mname, name, namelen);
		mle->mnamelen = namelen;
		mle->mnamehash = dlm_lockid_hash(name, namelen);
	पूर्ण

	atomic_inc(&dlm->mle_tot_count[mle->type]);
	atomic_inc(&dlm->mle_cur_count[mle->type]);

	/* copy off the node_map and रेजिस्टर hb callbacks on our copy */
	स_नकल(mle->node_map, dlm->करोमुख्य_map, माप(mle->node_map));
	स_नकल(mle->vote_map, dlm->करोमुख्य_map, माप(mle->vote_map));
	clear_bit(dlm->node_num, mle->vote_map);
	clear_bit(dlm->node_num, mle->node_map);

	/* attach the mle to the करोमुख्य node up/करोwn events */
	__dlm_mle_attach_hb_events(dlm, mle);
पूर्ण

व्योम __dlm_unlink_mle(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_master_list_entry *mle)
अणु
	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&dlm->master_lock);

	अगर (!hlist_unhashed(&mle->master_hash_node))
		hlist_del_init(&mle->master_hash_node);
पूर्ण

व्योम __dlm_insert_mle(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_master_list_entry *mle)
अणु
	काष्ठा hlist_head *bucket;

	निश्चित_spin_locked(&dlm->master_lock);

	bucket = dlm_master_hash(dlm, mle->mnamehash);
	hlist_add_head(&mle->master_hash_node, bucket);
पूर्ण

/* वापसs 1 अगर found, 0 अगर not */
अटल पूर्णांक dlm_find_mle(काष्ठा dlm_ctxt *dlm,
			काष्ठा dlm_master_list_entry **mle,
			अक्षर *name, अचिन्हित पूर्णांक namelen)
अणु
	काष्ठा dlm_master_list_entry *पंचांगpmle;
	काष्ठा hlist_head *bucket;
	अचिन्हित पूर्णांक hash;

	निश्चित_spin_locked(&dlm->master_lock);

	hash = dlm_lockid_hash(name, namelen);
	bucket = dlm_master_hash(dlm, hash);
	hlist_क्रम_each_entry(पंचांगpmle, bucket, master_hash_node) अणु
		अगर (!dlm_mle_equal(dlm, पंचांगpmle, name, namelen))
			जारी;
		dlm_get_mle(पंचांगpmle);
		*mle = पंचांगpmle;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम dlm_hb_event_notअगरy_attached(काष्ठा dlm_ctxt *dlm, पूर्णांक idx, पूर्णांक node_up)
अणु
	काष्ठा dlm_master_list_entry *mle;

	निश्चित_spin_locked(&dlm->spinlock);

	list_क्रम_each_entry(mle, &dlm->mle_hb_events, hb_events) अणु
		अगर (node_up)
			dlm_mle_node_up(dlm, mle, शून्य, idx);
		अन्यथा
			dlm_mle_node_करोwn(dlm, mle, शून्य, idx);
	पूर्ण
पूर्ण

अटल व्योम dlm_mle_node_करोwn(काष्ठा dlm_ctxt *dlm,
			      काष्ठा dlm_master_list_entry *mle,
			      काष्ठा o2nm_node *node, पूर्णांक idx)
अणु
	spin_lock(&mle->spinlock);

	अगर (!test_bit(idx, mle->node_map))
		mlog(0, "node %u already removed from nodemap!\n", idx);
	अन्यथा
		clear_bit(idx, mle->node_map);

	spin_unlock(&mle->spinlock);
पूर्ण

अटल व्योम dlm_mle_node_up(काष्ठा dlm_ctxt *dlm,
			    काष्ठा dlm_master_list_entry *mle,
			    काष्ठा o2nm_node *node, पूर्णांक idx)
अणु
	spin_lock(&mle->spinlock);

	अगर (test_bit(idx, mle->node_map))
		mlog(0, "node %u already in node map!\n", idx);
	अन्यथा
		set_bit(idx, mle->node_map);

	spin_unlock(&mle->spinlock);
पूर्ण


पूर्णांक dlm_init_mle_cache(व्योम)
अणु
	dlm_mle_cache = kmem_cache_create("o2dlm_mle",
					  माप(काष्ठा dlm_master_list_entry),
					  0, SLAB_HWCACHE_ALIGN,
					  शून्य);
	अगर (dlm_mle_cache == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम dlm_destroy_mle_cache(व्योम)
अणु
	kmem_cache_destroy(dlm_mle_cache);
पूर्ण

अटल व्योम dlm_mle_release(काष्ठा kref *kref)
अणु
	काष्ठा dlm_master_list_entry *mle;
	काष्ठा dlm_ctxt *dlm;

	mle = container_of(kref, काष्ठा dlm_master_list_entry, mle_refs);
	dlm = mle->dlm;

	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&dlm->master_lock);

	mlog(0, "Releasing mle for %.*s, type %d\n", mle->mnamelen, mle->mname,
	     mle->type);

	/* हटाओ from list अगर not alपढ़ोy */
	__dlm_unlink_mle(dlm, mle);

	/* detach the mle from the करोमुख्य node up/करोwn events */
	__dlm_mle_detach_hb_events(dlm, mle);

	atomic_dec(&dlm->mle_cur_count[mle->type]);

	/* NOTE: kमुक्त under spinlock here.
	 * अगर this is bad, we can move this to a मुक्तlist. */
	kmem_cache_मुक्त(dlm_mle_cache, mle);
पूर्ण


/*
 * LOCK RESOURCE FUNCTIONS
 */

पूर्णांक dlm_init_master_caches(व्योम)
अणु
	dlm_lockres_cache = kmem_cache_create("o2dlm_lockres",
					      माप(काष्ठा dlm_lock_resource),
					      0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!dlm_lockres_cache)
		जाओ bail;

	dlm_lockname_cache = kmem_cache_create("o2dlm_lockname",
					       DLM_LOCKID_NAME_MAX, 0,
					       SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!dlm_lockname_cache)
		जाओ bail;

	वापस 0;
bail:
	dlm_destroy_master_caches();
	वापस -ENOMEM;
पूर्ण

व्योम dlm_destroy_master_caches(व्योम)
अणु
	kmem_cache_destroy(dlm_lockname_cache);
	dlm_lockname_cache = शून्य;

	kmem_cache_destroy(dlm_lockres_cache);
	dlm_lockres_cache = शून्य;
पूर्ण

अटल व्योम dlm_lockres_release(काष्ठा kref *kref)
अणु
	काष्ठा dlm_lock_resource *res;
	काष्ठा dlm_ctxt *dlm;

	res = container_of(kref, काष्ठा dlm_lock_resource, refs);
	dlm = res->dlm;

	/* This should not happen -- all lockres' have a name
	 * associated with them at init समय. */
	BUG_ON(!res->lockname.name);

	mlog(0, "destroying lockres %.*s\n", res->lockname.len,
	     res->lockname.name);

	atomic_dec(&dlm->res_cur_count);

	अगर (!hlist_unhashed(&res->hash_node) ||
	    !list_empty(&res->granted) ||
	    !list_empty(&res->converting) ||
	    !list_empty(&res->blocked) ||
	    !list_empty(&res->dirty) ||
	    !list_empty(&res->recovering) ||
	    !list_empty(&res->purge)) अणु
		mlog(ML_ERROR,
		     "Going to BUG for resource %.*s."
		     "  We're on a list! [%c%c%c%c%c%c%c]\n",
		     res->lockname.len, res->lockname.name,
		     !hlist_unhashed(&res->hash_node) ? 'H' : ' ',
		     !list_empty(&res->granted) ? 'G' : ' ',
		     !list_empty(&res->converting) ? 'C' : ' ',
		     !list_empty(&res->blocked) ? 'B' : ' ',
		     !list_empty(&res->dirty) ? 'D' : ' ',
		     !list_empty(&res->recovering) ? 'R' : ' ',
		     !list_empty(&res->purge) ? 'P' : ' ');

		dlm_prपूर्णांक_one_lock_resource(res);
	पूर्ण

	/* By the समय we're ready to blow this guy away, we shouldn't
	 * be on any lists. */
	BUG_ON(!hlist_unhashed(&res->hash_node));
	BUG_ON(!list_empty(&res->granted));
	BUG_ON(!list_empty(&res->converting));
	BUG_ON(!list_empty(&res->blocked));
	BUG_ON(!list_empty(&res->dirty));
	BUG_ON(!list_empty(&res->recovering));
	BUG_ON(!list_empty(&res->purge));

	kmem_cache_मुक्त(dlm_lockname_cache, (व्योम *)res->lockname.name);

	kmem_cache_मुक्त(dlm_lockres_cache, res);
पूर्ण

व्योम dlm_lockres_put(काष्ठा dlm_lock_resource *res)
अणु
	kref_put(&res->refs, dlm_lockres_release);
पूर्ण

अटल व्योम dlm_init_lockres(काष्ठा dlm_ctxt *dlm,
			     काष्ठा dlm_lock_resource *res,
			     स्थिर अक्षर *name, अचिन्हित पूर्णांक namelen)
अणु
	अक्षर *qname;

	/* If we स_रखो here, we lose our reference to the kदो_स्मृति'd
	 * res->lockname.name, so be sure to init every field
	 * correctly! */

	qname = (अक्षर *) res->lockname.name;
	स_नकल(qname, name, namelen);

	res->lockname.len = namelen;
	res->lockname.hash = dlm_lockid_hash(name, namelen);

	init_रुकोqueue_head(&res->wq);
	spin_lock_init(&res->spinlock);
	INIT_HLIST_NODE(&res->hash_node);
	INIT_LIST_HEAD(&res->granted);
	INIT_LIST_HEAD(&res->converting);
	INIT_LIST_HEAD(&res->blocked);
	INIT_LIST_HEAD(&res->dirty);
	INIT_LIST_HEAD(&res->recovering);
	INIT_LIST_HEAD(&res->purge);
	INIT_LIST_HEAD(&res->tracking);
	atomic_set(&res->asts_reserved, 0);
	res->migration_pending = 0;
	res->inflight_locks = 0;
	res->inflight_निश्चित_workers = 0;

	res->dlm = dlm;

	kref_init(&res->refs);

	atomic_inc(&dlm->res_tot_count);
	atomic_inc(&dlm->res_cur_count);

	/* just क्रम consistency */
	spin_lock(&res->spinlock);
	dlm_set_lockres_owner(dlm, res, DLM_LOCK_RES_OWNER_UNKNOWN);
	spin_unlock(&res->spinlock);

	res->state = DLM_LOCK_RES_IN_PROGRESS;

	res->last_used = 0;

	spin_lock(&dlm->track_lock);
	list_add_tail(&res->tracking, &dlm->tracking_list);
	spin_unlock(&dlm->track_lock);

	स_रखो(res->lvb, 0, DLM_LVB_LEN);
	स_रखो(res->refmap, 0, माप(res->refmap));
पूर्ण

काष्ठा dlm_lock_resource *dlm_new_lockres(काष्ठा dlm_ctxt *dlm,
				   स्थिर अक्षर *name,
				   अचिन्हित पूर्णांक namelen)
अणु
	काष्ठा dlm_lock_resource *res = शून्य;

	res = kmem_cache_zalloc(dlm_lockres_cache, GFP_NOFS);
	अगर (!res)
		जाओ error;

	res->lockname.name = kmem_cache_zalloc(dlm_lockname_cache, GFP_NOFS);
	अगर (!res->lockname.name)
		जाओ error;

	dlm_init_lockres(dlm, res, name, namelen);
	वापस res;

error:
	अगर (res)
		kmem_cache_मुक्त(dlm_lockres_cache, res);
	वापस शून्य;
पूर्ण

व्योम dlm_lockres_set_refmap_bit(काष्ठा dlm_ctxt *dlm,
				काष्ठा dlm_lock_resource *res, पूर्णांक bit)
अणु
	निश्चित_spin_locked(&res->spinlock);

	mlog(0, "res %.*s, set node %u, %ps()\n", res->lockname.len,
	     res->lockname.name, bit, __builtin_वापस_address(0));

	set_bit(bit, res->refmap);
पूर्ण

व्योम dlm_lockres_clear_refmap_bit(काष्ठा dlm_ctxt *dlm,
				  काष्ठा dlm_lock_resource *res, पूर्णांक bit)
अणु
	निश्चित_spin_locked(&res->spinlock);

	mlog(0, "res %.*s, clr node %u, %ps()\n", res->lockname.len,
	     res->lockname.name, bit, __builtin_वापस_address(0));

	clear_bit(bit, res->refmap);
पूर्ण

अटल व्योम __dlm_lockres_grab_inflight_ref(काष्ठा dlm_ctxt *dlm,
				   काष्ठा dlm_lock_resource *res)
अणु
	res->inflight_locks++;

	mlog(0, "%s: res %.*s, inflight++: now %u, %ps()\n", dlm->name,
	     res->lockname.len, res->lockname.name, res->inflight_locks,
	     __builtin_वापस_address(0));
पूर्ण

व्योम dlm_lockres_grab_inflight_ref(काष्ठा dlm_ctxt *dlm,
				   काष्ठा dlm_lock_resource *res)
अणु
	निश्चित_spin_locked(&res->spinlock);
	__dlm_lockres_grab_inflight_ref(dlm, res);
पूर्ण

व्योम dlm_lockres_drop_inflight_ref(काष्ठा dlm_ctxt *dlm,
				   काष्ठा dlm_lock_resource *res)
अणु
	निश्चित_spin_locked(&res->spinlock);

	BUG_ON(res->inflight_locks == 0);

	res->inflight_locks--;

	mlog(0, "%s: res %.*s, inflight--: now %u, %ps()\n", dlm->name,
	     res->lockname.len, res->lockname.name, res->inflight_locks,
	     __builtin_वापस_address(0));

	wake_up(&res->wq);
पूर्ण

व्योम __dlm_lockres_grab_inflight_worker(काष्ठा dlm_ctxt *dlm,
		काष्ठा dlm_lock_resource *res)
अणु
	निश्चित_spin_locked(&res->spinlock);
	res->inflight_निश्चित_workers++;
	mlog(0, "%s:%.*s: inflight assert worker++: now %u\n",
			dlm->name, res->lockname.len, res->lockname.name,
			res->inflight_निश्चित_workers);
पूर्ण

अटल व्योम __dlm_lockres_drop_inflight_worker(काष्ठा dlm_ctxt *dlm,
		काष्ठा dlm_lock_resource *res)
अणु
	निश्चित_spin_locked(&res->spinlock);
	BUG_ON(res->inflight_निश्चित_workers == 0);
	res->inflight_निश्चित_workers--;
	mlog(0, "%s:%.*s: inflight assert worker--: now %u\n",
			dlm->name, res->lockname.len, res->lockname.name,
			res->inflight_निश्चित_workers);
पूर्ण

अटल व्योम dlm_lockres_drop_inflight_worker(काष्ठा dlm_ctxt *dlm,
		काष्ठा dlm_lock_resource *res)
अणु
	spin_lock(&res->spinlock);
	__dlm_lockres_drop_inflight_worker(dlm, res);
	spin_unlock(&res->spinlock);
पूर्ण

/*
 * lookup a lock resource by name.
 * may alपढ़ोy exist in the hashtable.
 * lockid is null terminated
 *
 * अगर not, allocate enough क्रम the lockres and क्रम
 * the temporary काष्ठाure used in करोing the mastering.
 *
 * also, करो a lookup in the dlm->master_list to see
 * अगर another node has begun mastering the same lock.
 * अगर so, there should be a block entry in there
 * क्रम this name, and we should *not* attempt to master
 * the lock here.   need to रुको around क्रम that node
 * to निश्चित_master (or die).
 *
 */
काष्ठा dlm_lock_resource * dlm_get_lock_resource(काष्ठा dlm_ctxt *dlm,
					  स्थिर अक्षर *lockid,
					  पूर्णांक namelen,
					  पूर्णांक flags)
अणु
	काष्ठा dlm_lock_resource *पंचांगpres=शून्य, *res=शून्य;
	काष्ठा dlm_master_list_entry *mle = शून्य;
	काष्ठा dlm_master_list_entry *alloc_mle = शून्य;
	पूर्णांक blocked = 0;
	पूर्णांक ret, nodक्रमागत;
	काष्ठा dlm_node_iter iter;
	अचिन्हित पूर्णांक hash;
	पूर्णांक tries = 0;
	पूर्णांक bit, रुको_on_recovery = 0;

	BUG_ON(!lockid);

	hash = dlm_lockid_hash(lockid, namelen);

	mlog(0, "get lockres %s (len %d)\n", lockid, namelen);

lookup:
	spin_lock(&dlm->spinlock);
	पंचांगpres = __dlm_lookup_lockres_full(dlm, lockid, namelen, hash);
	अगर (पंचांगpres) अणु
		spin_unlock(&dlm->spinlock);
		spin_lock(&पंचांगpres->spinlock);

		/*
		 * Right after dlm spinlock was released, dlm_thपढ़ो could have
		 * purged the lockres. Check अगर lockres got unhashed. If so
		 * start over.
		 */
		अगर (hlist_unhashed(&पंचांगpres->hash_node)) अणु
			spin_unlock(&पंचांगpres->spinlock);
			dlm_lockres_put(पंचांगpres);
			पंचांगpres = शून्य;
			जाओ lookup;
		पूर्ण

		/* Wait on the thपढ़ो that is mastering the resource */
		अगर (पंचांगpres->owner == DLM_LOCK_RES_OWNER_UNKNOWN) अणु
			__dlm_रुको_on_lockres(पंचांगpres);
			BUG_ON(पंचांगpres->owner == DLM_LOCK_RES_OWNER_UNKNOWN);
			spin_unlock(&पंचांगpres->spinlock);
			dlm_lockres_put(पंचांगpres);
			पंचांगpres = शून्य;
			जाओ lookup;
		पूर्ण

		/* Wait on the resource purge to complete beक्रमe continuing */
		अगर (पंचांगpres->state & DLM_LOCK_RES_DROPPING_REF) अणु
			BUG_ON(पंचांगpres->owner == dlm->node_num);
			__dlm_रुको_on_lockres_flags(पंचांगpres,
						    DLM_LOCK_RES_DROPPING_REF);
			spin_unlock(&पंचांगpres->spinlock);
			dlm_lockres_put(पंचांगpres);
			पंचांगpres = शून्य;
			जाओ lookup;
		पूर्ण

		/* Grab inflight ref to pin the resource */
		dlm_lockres_grab_inflight_ref(dlm, पंचांगpres);

		spin_unlock(&पंचांगpres->spinlock);
		अगर (res) अणु
			spin_lock(&dlm->track_lock);
			अगर (!list_empty(&res->tracking))
				list_del_init(&res->tracking);
			अन्यथा
				mlog(ML_ERROR, "Resource %.*s not "
						"on the Tracking list\n",
						res->lockname.len,
						res->lockname.name);
			spin_unlock(&dlm->track_lock);
			dlm_lockres_put(res);
		पूर्ण
		res = पंचांगpres;
		जाओ leave;
	पूर्ण

	अगर (!res) अणु
		spin_unlock(&dlm->spinlock);
		mlog(0, "allocating a new resource\n");
		/* nothing found and we need to allocate one. */
		alloc_mle = kmem_cache_alloc(dlm_mle_cache, GFP_NOFS);
		अगर (!alloc_mle)
			जाओ leave;
		res = dlm_new_lockres(dlm, lockid, namelen);
		अगर (!res)
			जाओ leave;
		जाओ lookup;
	पूर्ण

	mlog(0, "no lockres found, allocated our own: %p\n", res);

	अगर (flags & LKM_LOCAL) अणु
		/* caller knows it's safe to assume it's not mastered अन्यथाwhere
		 * DONE!  वापस right away */
		spin_lock(&res->spinlock);
		dlm_change_lockres_owner(dlm, res, dlm->node_num);
		__dlm_insert_lockres(dlm, res);
		dlm_lockres_grab_inflight_ref(dlm, res);
		spin_unlock(&res->spinlock);
		spin_unlock(&dlm->spinlock);
		/* lockres still marked IN_PROGRESS */
		जाओ wake_रुकोers;
	पूर्ण

	/* check master list to see अगर another node has started mastering it */
	spin_lock(&dlm->master_lock);

	/* अगर we found a block, रुको क्रम lock to be mastered by another node */
	blocked = dlm_find_mle(dlm, &mle, (अक्षर *)lockid, namelen);
	अगर (blocked) अणु
		पूर्णांक mig;
		अगर (mle->type == DLM_MLE_MASTER) अणु
			mlog(ML_ERROR, "master entry for nonexistent lock!\n");
			BUG();
		पूर्ण
		mig = (mle->type == DLM_MLE_MIGRATION);
		/* अगर there is a migration in progress, let the migration
		 * finish beक्रमe continuing.  we can रुको क्रम the असलence
		 * of the MIGRATION mle: either the migrate finished or
		 * one of the nodes died and the mle was cleaned up.
		 * अगर there is a BLOCK here, but it alपढ़ोy has a master
		 * set, we are too late.  the master करोes not have a ref
		 * क्रम us in the refmap.  detach the mle and drop it.
		 * either way, go back to the top and start over. */
		अगर (mig || mle->master != O2NM_MAX_NODES) अणु
			BUG_ON(mig && mle->master == dlm->node_num);
			/* we arrived too late.  the master करोes not
			 * have a ref क्रम us. retry. */
			mlog(0, "%s:%.*s: late on %s\n",
			     dlm->name, namelen, lockid,
			     mig ?  "MIGRATION" : "BLOCK");
			spin_unlock(&dlm->master_lock);
			spin_unlock(&dlm->spinlock);

			/* master is known, detach */
			अगर (!mig)
				dlm_mle_detach_hb_events(dlm, mle);
			dlm_put_mle(mle);
			mle = शून्य;
			/* this is lame, but we can't रुको on either
			 * the mle or lockres रुकोqueue here */
			अगर (mig)
				msleep(100);
			जाओ lookup;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* go ahead and try to master lock on this node */
		mle = alloc_mle;
		/* make sure this करोes not get मुक्तd below */
		alloc_mle = शून्य;
		dlm_init_mle(mle, DLM_MLE_MASTER, dlm, res, शून्य, 0);
		set_bit(dlm->node_num, mle->maybe_map);
		__dlm_insert_mle(dlm, mle);

		/* still holding the dlm spinlock, check the recovery map
		 * to see अगर there are any nodes that still need to be
		 * considered.  these will not appear in the mle nodemap
		 * but they might own this lockres.  रुको on them. */
		bit = find_next_bit(dlm->recovery_map, O2NM_MAX_NODES, 0);
		अगर (bit < O2NM_MAX_NODES) अणु
			mlog(0, "%s: res %.*s, At least one node (%d) "
			     "to recover before lock mastery can begin\n",
			     dlm->name, namelen, (अक्षर *)lockid, bit);
			रुको_on_recovery = 1;
		पूर्ण
	पूर्ण

	/* at this poपूर्णांक there is either a DLM_MLE_BLOCK or a
	 * DLM_MLE_MASTER on the master list, so it's safe to add the
	 * lockres to the hashtable.  anyone who finds the lock will
	 * still have to रुको on the IN_PROGRESS. */

	/* finally add the lockres to its hash bucket */
	__dlm_insert_lockres(dlm, res);

	/* since this lockres is new it करोesn't not require the spinlock */
	__dlm_lockres_grab_inflight_ref(dlm, res);

	/* get an extra ref on the mle in हाल this is a BLOCK
	 * अगर so, the creator of the BLOCK may try to put the last
	 * ref at this समय in the निश्चित master handler, so we
	 * need an extra one to keep from a bad ptr deref. */
	dlm_get_mle_inuse(mle);
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);

reकरो_request:
	जबतक (रुको_on_recovery) अणु
		/* any cluster changes that occurred after dropping the
		 * dlm spinlock would be detectable be a change on the mle,
		 * so we only need to clear out the recovery map once. */
		अगर (dlm_is_recovery_lock(lockid, namelen)) अणु
			mlog(0, "%s: Recovery map is not empty, but must "
			     "master $RECOVERY lock now\n", dlm->name);
			अगर (!dlm_pre_master_reco_lockres(dlm, res))
				रुको_on_recovery = 0;
			अन्यथा अणु
				mlog(0, "%s: waiting 500ms for heartbeat state "
				    "change\n", dlm->name);
				msleep(500);
			पूर्ण
			जारी;
		पूर्ण

		dlm_kick_recovery_thपढ़ो(dlm);
		msleep(1000);
		dlm_रुको_क्रम_recovery(dlm);

		spin_lock(&dlm->spinlock);
		bit = find_next_bit(dlm->recovery_map, O2NM_MAX_NODES, 0);
		अगर (bit < O2NM_MAX_NODES) अणु
			mlog(0, "%s: res %.*s, At least one node (%d) "
			     "to recover before lock mastery can begin\n",
			     dlm->name, namelen, (अक्षर *)lockid, bit);
			रुको_on_recovery = 1;
		पूर्ण अन्यथा
			रुको_on_recovery = 0;
		spin_unlock(&dlm->spinlock);

		अगर (रुको_on_recovery)
			dlm_रुको_क्रम_node_recovery(dlm, bit, 10000);
	पूर्ण

	/* must रुको क्रम lock to be mastered अन्यथाwhere */
	अगर (blocked)
		जाओ रुको;

	ret = -EINVAL;
	dlm_node_iter_init(mle->vote_map, &iter);
	जबतक ((nodक्रमागत = dlm_node_iter_next(&iter)) >= 0) अणु
		ret = dlm_करो_master_request(res, mle, nodक्रमागत);
		अगर (ret < 0)
			mlog_त्रुटि_सं(ret);
		अगर (mle->master != O2NM_MAX_NODES) अणु
			/* found a master ! */
			अगर (mle->master <= nodक्रमागत)
				अवरोध;
			/* अगर our master request has not reached the master
			 * yet, keep going until it करोes.  this is how the
			 * master will know that निश्चितs are needed back to
			 * the lower nodes. */
			mlog(0, "%s: res %.*s, Requests only up to %u but "
			     "master is %u, keep going\n", dlm->name, namelen,
			     lockid, nodक्रमागत, mle->master);
		पूर्ण
	पूर्ण

रुको:
	/* keep going until the response map includes all nodes */
	ret = dlm_रुको_क्रम_lock_mastery(dlm, res, mle, &blocked);
	अगर (ret < 0) अणु
		रुको_on_recovery = 1;
		mlog(0, "%s: res %.*s, Node map changed, redo the master "
		     "request now, blocked=%d\n", dlm->name, res->lockname.len,
		     res->lockname.name, blocked);
		अगर (++tries > 20) अणु
			mlog(ML_ERROR, "%s: res %.*s, Spinning on "
			     "dlm_wait_for_lock_mastery, blocked = %d\n",
			     dlm->name, res->lockname.len,
			     res->lockname.name, blocked);
			dlm_prपूर्णांक_one_lock_resource(res);
			dlm_prपूर्णांक_one_mle(mle);
			tries = 0;
		पूर्ण
		जाओ reकरो_request;
	पूर्ण

	mlog(0, "%s: res %.*s, Mastered by %u\n", dlm->name, res->lockname.len,
	     res->lockname.name, res->owner);
	/* make sure we never जारी without this */
	BUG_ON(res->owner == O2NM_MAX_NODES);

	/* master is known, detach अगर not alपढ़ोy detached */
	dlm_mle_detach_hb_events(dlm, mle);
	dlm_put_mle(mle);
	/* put the extra ref */
	dlm_put_mle_inuse(mle);

wake_रुकोers:
	spin_lock(&res->spinlock);
	res->state &= ~DLM_LOCK_RES_IN_PROGRESS;
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);

leave:
	/* need to मुक्त the unused mle */
	अगर (alloc_mle)
		kmem_cache_मुक्त(dlm_mle_cache, alloc_mle);

	वापस res;
पूर्ण


#घोषणा DLM_MASTERY_TIMEOUT_MS   5000

अटल पूर्णांक dlm_रुको_क्रम_lock_mastery(काष्ठा dlm_ctxt *dlm,
				     काष्ठा dlm_lock_resource *res,
				     काष्ठा dlm_master_list_entry *mle,
				     पूर्णांक *blocked)
अणु
	u8 m;
	पूर्णांक ret, bit;
	पूर्णांक map_changed, voting_करोne;
	पूर्णांक निश्चित, sleep;

recheck:
	ret = 0;
	निश्चित = 0;

	/* check अगर another node has alपढ़ोy become the owner */
	spin_lock(&res->spinlock);
	अगर (res->owner != DLM_LOCK_RES_OWNER_UNKNOWN) अणु
		mlog(0, "%s:%.*s: owner is suddenly %u\n", dlm->name,
		     res->lockname.len, res->lockname.name, res->owner);
		spin_unlock(&res->spinlock);
		/* this will cause the master to re-निश्चित across
		 * the whole cluster, मुक्तing up mles */
		अगर (res->owner != dlm->node_num) अणु
			ret = dlm_करो_master_request(res, mle, res->owner);
			अगर (ret < 0) अणु
				/* give recovery a chance to run */
				mlog(ML_ERROR, "link to %u went down?: %d\n", res->owner, ret);
				msleep(500);
				जाओ recheck;
			पूर्ण
		पूर्ण
		ret = 0;
		जाओ leave;
	पूर्ण
	spin_unlock(&res->spinlock);

	spin_lock(&mle->spinlock);
	m = mle->master;
	map_changed = (स_भेद(mle->vote_map, mle->node_map,
			      माप(mle->vote_map)) != 0);
	voting_करोne = (स_भेद(mle->vote_map, mle->response_map,
			     माप(mle->vote_map)) == 0);

	/* restart अगर we hit any errors */
	अगर (map_changed) अणु
		पूर्णांक b;
		mlog(0, "%s: %.*s: node map changed, restarting\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		ret = dlm_restart_lock_mastery(dlm, res, mle, *blocked);
		b = (mle->type == DLM_MLE_BLOCK);
		अगर ((*blocked && !b) || (!*blocked && b)) अणु
			mlog(0, "%s:%.*s: status change: old=%d new=%d\n",
			     dlm->name, res->lockname.len, res->lockname.name,
			     *blocked, b);
			*blocked = b;
		पूर्ण
		spin_unlock(&mle->spinlock);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ leave;
		पूर्ण
		mlog(0, "%s:%.*s: restart lock mastery succeeded, "
		     "rechecking now\n", dlm->name, res->lockname.len,
		     res->lockname.name);
		जाओ recheck;
	पूर्ण अन्यथा अणु
		अगर (!voting_करोne) अणु
			mlog(0, "map not changed and voting not done "
			     "for %s:%.*s\n", dlm->name, res->lockname.len,
			     res->lockname.name);
		पूर्ण
	पूर्ण

	अगर (m != O2NM_MAX_NODES) अणु
		/* another node has करोne an निश्चित!
		 * all करोne! */
		sleep = 0;
	पूर्ण अन्यथा अणु
		sleep = 1;
		/* have all nodes responded? */
		अगर (voting_करोne && !*blocked) अणु
			bit = find_next_bit(mle->maybe_map, O2NM_MAX_NODES, 0);
			अगर (dlm->node_num <= bit) अणु
				/* my node number is lowest.
			 	 * now tell other nodes that I am
				 * mastering this. */
				mle->master = dlm->node_num;
				/* ref was grabbed in get_lock_resource
				 * will be dropped in dlmlock_master */
				निश्चित = 1;
				sleep = 0;
			पूर्ण
			/* अगर voting is करोne, but we have not received
			 * an निश्चित master yet, we must sleep */
		पूर्ण
	पूर्ण

	spin_unlock(&mle->spinlock);

	/* sleep अगर we haven't finished voting yet */
	अगर (sleep) अणु
		अचिन्हित दीर्घ समयo = msecs_to_jअगरfies(DLM_MASTERY_TIMEOUT_MS);
		atomic_set(&mle->woken, 0);
		(व्योम)रुको_event_समयout(mle->wq,
					 (atomic_पढ़ो(&mle->woken) == 1),
					 समयo);
		अगर (res->owner == O2NM_MAX_NODES) अणु
			mlog(0, "%s:%.*s: waiting again\n", dlm->name,
			     res->lockname.len, res->lockname.name);
			जाओ recheck;
		पूर्ण
		mlog(0, "done waiting, master is %u\n", res->owner);
		ret = 0;
		जाओ leave;
	पूर्ण

	ret = 0;   /* करोne */
	अगर (निश्चित) अणु
		m = dlm->node_num;
		mlog(0, "about to master %.*s here, this=%u\n",
		     res->lockname.len, res->lockname.name, m);
		ret = dlm_करो_निश्चित_master(dlm, res, mle->vote_map, 0);
		अगर (ret) अणु
			/* This is a failure in the network path,
			 * not in the response to the निश्चित_master
			 * (any nonzero response is a BUG on this node).
			 * Most likely a socket just got disconnected
			 * due to node death. */
			mlog_त्रुटि_सं(ret);
		पूर्ण
		/* no दीर्घer need to restart lock mastery.
		 * all living nodes have been contacted. */
		ret = 0;
	पूर्ण

	/* set the lockres owner */
	spin_lock(&res->spinlock);
	/* mastery reference obtained either during
	 * निश्चित_master_handler or in get_lock_resource */
	dlm_change_lockres_owner(dlm, res, m);
	spin_unlock(&res->spinlock);

leave:
	वापस ret;
पूर्ण

काष्ठा dlm_biपंचांगap_dअगरf_iter
अणु
	पूर्णांक curnode;
	अचिन्हित दीर्घ *orig_bm;
	अचिन्हित दीर्घ *cur_bm;
	अचिन्हित दीर्घ dअगरf_bm[BITS_TO_LONGS(O2NM_MAX_NODES)];
पूर्ण;

क्रमागत dlm_node_state_change
अणु
	NODE_DOWN = -1,
	NODE_NO_CHANGE = 0,
	NODE_UP
पूर्ण;

अटल व्योम dlm_biपंचांगap_dअगरf_iter_init(काष्ठा dlm_biपंचांगap_dअगरf_iter *iter,
				      अचिन्हित दीर्घ *orig_bm,
				      अचिन्हित दीर्घ *cur_bm)
अणु
	अचिन्हित दीर्घ p1, p2;
	पूर्णांक i;

	iter->curnode = -1;
	iter->orig_bm = orig_bm;
	iter->cur_bm = cur_bm;

	क्रम (i = 0; i < BITS_TO_LONGS(O2NM_MAX_NODES); i++) अणु
       		p1 = *(iter->orig_bm + i);
	       	p2 = *(iter->cur_bm + i);
		iter->dअगरf_bm[i] = (p1 & ~p2) | (p2 & ~p1);
	पूर्ण
पूर्ण

अटल पूर्णांक dlm_biपंचांगap_dअगरf_iter_next(काष्ठा dlm_biपंचांगap_dअगरf_iter *iter,
				     क्रमागत dlm_node_state_change *state)
अणु
	पूर्णांक bit;

	अगर (iter->curnode >= O2NM_MAX_NODES)
		वापस -ENOENT;

	bit = find_next_bit(iter->dअगरf_bm, O2NM_MAX_NODES,
			    iter->curnode+1);
	अगर (bit >= O2NM_MAX_NODES) अणु
		iter->curnode = O2NM_MAX_NODES;
		वापस -ENOENT;
	पूर्ण

	/* अगर it was there in the original then this node died */
	अगर (test_bit(bit, iter->orig_bm))
		*state = NODE_DOWN;
	अन्यथा
		*state = NODE_UP;

	iter->curnode = bit;
	वापस bit;
पूर्ण


अटल पूर्णांक dlm_restart_lock_mastery(काष्ठा dlm_ctxt *dlm,
				    काष्ठा dlm_lock_resource *res,
				    काष्ठा dlm_master_list_entry *mle,
				    पूर्णांक blocked)
अणु
	काष्ठा dlm_biपंचांगap_dअगरf_iter bdi;
	क्रमागत dlm_node_state_change sc;
	पूर्णांक node;
	पूर्णांक ret = 0;

	mlog(0, "something happened such that the "
	     "master process may need to be restarted!\n");

	निश्चित_spin_locked(&mle->spinlock);

	dlm_biपंचांगap_dअगरf_iter_init(&bdi, mle->vote_map, mle->node_map);
	node = dlm_biपंचांगap_dअगरf_iter_next(&bdi, &sc);
	जबतक (node >= 0) अणु
		अगर (sc == NODE_UP) अणु
			/* a node came up.  clear any old vote from
			 * the response map and set it in the vote map
			 * then restart the mastery. */
			mlog(ML_NOTICE, "node %d up while restarting\n", node);

			/* reकरो the master request, but only क्रम the new node */
			mlog(0, "sending request to new node\n");
			clear_bit(node, mle->response_map);
			set_bit(node, mle->vote_map);
		पूर्ण अन्यथा अणु
			mlog(ML_ERROR, "node down! %d\n", node);
			अगर (blocked) अणु
				पूर्णांक lowest = find_next_bit(mle->maybe_map,
						       O2NM_MAX_NODES, 0);

				/* act like it was never there */
				clear_bit(node, mle->maybe_map);

			       	अगर (node == lowest) अणु
					mlog(0, "expected master %u died"
					    " while this node was blocked "
					    "waiting on it!\n", node);
					lowest = find_next_bit(mle->maybe_map,
						       	O2NM_MAX_NODES,
						       	lowest+1);
					अगर (lowest < O2NM_MAX_NODES) अणु
						mlog(0, "%s:%.*s:still "
						     "blocked. waiting on %u "
						     "now\n", dlm->name,
						     res->lockname.len,
						     res->lockname.name,
						     lowest);
					पूर्ण अन्यथा अणु
						/* mle is an MLE_BLOCK, but
						 * there is now nothing left to
						 * block on.  we need to वापस
						 * all the way back out and try
						 * again with an MLE_MASTER.
						 * dlm_करो_local_recovery_cleanup
						 * has alपढ़ोy run, so the mle
						 * refcount is ok */
						mlog(0, "%s:%.*s: no "
						     "longer blocking. try to "
						     "master this here\n",
						     dlm->name,
						     res->lockname.len,
						     res->lockname.name);
						mle->type = DLM_MLE_MASTER;
						mle->mleres = res;
					पूर्ण
				पूर्ण
			पूर्ण

			/* now blank out everything, as अगर we had never
			 * contacted anyone */
			स_रखो(mle->maybe_map, 0, माप(mle->maybe_map));
			स_रखो(mle->response_map, 0, माप(mle->response_map));
			/* reset the vote_map to the current node_map */
			स_नकल(mle->vote_map, mle->node_map,
			       माप(mle->node_map));
			/* put myself पूर्णांकo the maybe map */
			अगर (mle->type != DLM_MLE_BLOCK)
				set_bit(dlm->node_num, mle->maybe_map);
		पूर्ण
		ret = -EAGAIN;
		node = dlm_biपंचांगap_dअगरf_iter_next(&bdi, &sc);
	पूर्ण
	वापस ret;
पूर्ण


/*
 * DLM_MASTER_REQUEST_MSG
 *
 * वापसs: 0 on success,
 *          -त्रुटि_सं on a network error
 *
 * on error, the caller should assume the target node is "dead"
 *
 */

अटल पूर्णांक dlm_करो_master_request(काष्ठा dlm_lock_resource *res,
				 काष्ठा dlm_master_list_entry *mle, पूर्णांक to)
अणु
	काष्ठा dlm_ctxt *dlm = mle->dlm;
	काष्ठा dlm_master_request request;
	पूर्णांक ret, response=0, resend;

	स_रखो(&request, 0, माप(request));
	request.node_idx = dlm->node_num;

	BUG_ON(mle->type == DLM_MLE_MIGRATION);

	request.namelen = (u8)mle->mnamelen;
	स_नकल(request.name, mle->mname, request.namelen);

again:
	ret = o2net_send_message(DLM_MASTER_REQUEST_MSG, dlm->key, &request,
				 माप(request), to, &response);
	अगर (ret < 0)  अणु
		अगर (ret == -ESRCH) अणु
			/* should never happen */
			mlog(ML_ERROR, "TCP stack not ready!\n");
			BUG();
		पूर्ण अन्यथा अगर (ret == -EINVAL) अणु
			mlog(ML_ERROR, "bad args passed to o2net!\n");
			BUG();
		पूर्ण अन्यथा अगर (ret == -ENOMEM) अणु
			mlog(ML_ERROR, "out of memory while trying to send "
			     "network message!  retrying\n");
			/* this is totally crude */
			msleep(50);
			जाओ again;
		पूर्ण अन्यथा अगर (!dlm_is_host_करोwn(ret)) अणु
			/* not a network error. bad. */
			mlog_त्रुटि_सं(ret);
			mlog(ML_ERROR, "unhandled error!");
			BUG();
		पूर्ण
		/* all other errors should be network errors,
		 * and likely indicate node death */
		mlog(ML_ERROR, "link to %d went down!\n", to);
		जाओ out;
	पूर्ण

	ret = 0;
	resend = 0;
	spin_lock(&mle->spinlock);
	चयन (response) अणु
		हाल DLM_MASTER_RESP_YES:
			set_bit(to, mle->response_map);
			mlog(0, "node %u is the master, response=YES\n", to);
			mlog(0, "%s:%.*s: master node %u now knows I have a "
			     "reference\n", dlm->name, res->lockname.len,
			     res->lockname.name, to);
			mle->master = to;
			अवरोध;
		हाल DLM_MASTER_RESP_NO:
			mlog(0, "node %u not master, response=NO\n", to);
			set_bit(to, mle->response_map);
			अवरोध;
		हाल DLM_MASTER_RESP_MAYBE:
			mlog(0, "node %u not master, response=MAYBE\n", to);
			set_bit(to, mle->response_map);
			set_bit(to, mle->maybe_map);
			अवरोध;
		हाल DLM_MASTER_RESP_ERROR:
			mlog(0, "node %u hit an error, resending\n", to);
			resend = 1;
			response = 0;
			अवरोध;
		शेष:
			mlog(ML_ERROR, "bad response! %u\n", response);
			BUG();
	पूर्ण
	spin_unlock(&mle->spinlock);
	अगर (resend) अणु
		/* this is also totally crude */
		msleep(50);
		जाओ again;
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * locks that can be taken here:
 * dlm->spinlock
 * res->spinlock
 * mle->spinlock
 * dlm->master_list
 *
 * अगर possible, TRIM THIS DOWN!!!
 */
पूर्णांक dlm_master_request_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			       व्योम **ret_data)
अणु
	u8 response = DLM_MASTER_RESP_MAYBE;
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_lock_resource *res = शून्य;
	काष्ठा dlm_master_request *request = (काष्ठा dlm_master_request *) msg->buf;
	काष्ठा dlm_master_list_entry *mle = शून्य, *पंचांगpmle = शून्य;
	अक्षर *name;
	अचिन्हित पूर्णांक namelen, hash;
	पूर्णांक found, ret;
	पूर्णांक set_maybe;
	पूर्णांक dispatch_निश्चित = 0;
	पूर्णांक dispatched = 0;

	अगर (!dlm_grab(dlm))
		वापस DLM_MASTER_RESP_NO;

	अगर (!dlm_करोमुख्य_fully_joined(dlm)) अणु
		response = DLM_MASTER_RESP_NO;
		जाओ send_response;
	पूर्ण

	name = request->name;
	namelen = request->namelen;
	hash = dlm_lockid_hash(name, namelen);

	अगर (namelen > DLM_LOCKID_NAME_MAX) अणु
		response = DLM_IVBUFLEN;
		जाओ send_response;
	पूर्ण

way_up_top:
	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres(dlm, name, namelen, hash);
	अगर (res) अणु
		spin_unlock(&dlm->spinlock);

		/* take care of the easy हालs up front */
		spin_lock(&res->spinlock);

		/*
		 * Right after dlm spinlock was released, dlm_thपढ़ो could have
		 * purged the lockres. Check अगर lockres got unhashed. If so
		 * start over.
		 */
		अगर (hlist_unhashed(&res->hash_node)) अणु
			spin_unlock(&res->spinlock);
			dlm_lockres_put(res);
			जाओ way_up_top;
		पूर्ण

		अगर (res->state & (DLM_LOCK_RES_RECOVERING|
				  DLM_LOCK_RES_MIGRATING)) अणु
			spin_unlock(&res->spinlock);
			mlog(0, "returning DLM_MASTER_RESP_ERROR since res is "
			     "being recovered/migrated\n");
			response = DLM_MASTER_RESP_ERROR;
			अगर (mle)
				kmem_cache_मुक्त(dlm_mle_cache, mle);
			जाओ send_response;
		पूर्ण

		अगर (res->owner == dlm->node_num) अणु
			dlm_lockres_set_refmap_bit(dlm, res, request->node_idx);
			spin_unlock(&res->spinlock);
			response = DLM_MASTER_RESP_YES;
			अगर (mle)
				kmem_cache_मुक्त(dlm_mle_cache, mle);

			/* this node is the owner.
			 * there is some extra work that needs to
			 * happen now.  the requesting node has
			 * caused all nodes up to this one to
			 * create mles.  this node now needs to
			 * go back and clean those up. */
			dispatch_निश्चित = 1;
			जाओ send_response;
		पूर्ण अन्यथा अगर (res->owner != DLM_LOCK_RES_OWNER_UNKNOWN) अणु
			spin_unlock(&res->spinlock);
			// mlog(0, "node %u is the master\n", res->owner);
			response = DLM_MASTER_RESP_NO;
			अगर (mle)
				kmem_cache_मुक्त(dlm_mle_cache, mle);
			जाओ send_response;
		पूर्ण

		/* ok, there is no owner.  either this node is
		 * being blocked, or it is actively trying to
		 * master this lock. */
		अगर (!(res->state & DLM_LOCK_RES_IN_PROGRESS)) अणु
			mlog(ML_ERROR, "lock with no owner should be "
			     "in-progress!\n");
			BUG();
		पूर्ण

		// mlog(0, "lockres is in progress...\n");
		spin_lock(&dlm->master_lock);
		found = dlm_find_mle(dlm, &पंचांगpmle, name, namelen);
		अगर (!found) अणु
			mlog(ML_ERROR, "no mle found for this lock!\n");
			BUG();
		पूर्ण
		set_maybe = 1;
		spin_lock(&पंचांगpmle->spinlock);
		अगर (पंचांगpmle->type == DLM_MLE_BLOCK) अणु
			// mlog(0, "this node is waiting for "
			// "lockres to be mastered\n");
			response = DLM_MASTER_RESP_NO;
		पूर्ण अन्यथा अगर (पंचांगpmle->type == DLM_MLE_MIGRATION) अणु
			mlog(0, "node %u is master, but trying to migrate to "
			     "node %u.\n", पंचांगpmle->master, पंचांगpmle->new_master);
			अगर (पंचांगpmle->master == dlm->node_num) अणु
				mlog(ML_ERROR, "no owner on lockres, but this "
				     "node is trying to migrate it to %u?!\n",
				     पंचांगpmle->new_master);
				BUG();
			पूर्ण अन्यथा अणु
				/* the real master can respond on its own */
				response = DLM_MASTER_RESP_NO;
			पूर्ण
		पूर्ण अन्यथा अगर (पंचांगpmle->master != DLM_LOCK_RES_OWNER_UNKNOWN) अणु
			set_maybe = 0;
			अगर (पंचांगpmle->master == dlm->node_num) अणु
				response = DLM_MASTER_RESP_YES;
				/* this node will be the owner.
				 * go back and clean the mles on any
				 * other nodes */
				dispatch_निश्चित = 1;
				dlm_lockres_set_refmap_bit(dlm, res,
							   request->node_idx);
			पूर्ण अन्यथा
				response = DLM_MASTER_RESP_NO;
		पूर्ण अन्यथा अणु
			// mlog(0, "this node is attempting to "
			// "master lockres\n");
			response = DLM_MASTER_RESP_MAYBE;
		पूर्ण
		अगर (set_maybe)
			set_bit(request->node_idx, पंचांगpmle->maybe_map);
		spin_unlock(&पंचांगpmle->spinlock);

		spin_unlock(&dlm->master_lock);
		spin_unlock(&res->spinlock);

		/* keep the mle attached to heartbeat events */
		dlm_put_mle(पंचांगpmle);
		अगर (mle)
			kmem_cache_मुक्त(dlm_mle_cache, mle);
		जाओ send_response;
	पूर्ण

	/*
	 * lockres करोesn't exist on this node
	 * अगर there is an MLE_BLOCK, वापस NO
	 * अगर there is an MLE_MASTER, वापस MAYBE
	 * otherwise, add an MLE_BLOCK, वापस NO
	 */
	spin_lock(&dlm->master_lock);
	found = dlm_find_mle(dlm, &पंचांगpmle, name, namelen);
	अगर (!found) अणु
		/* this lockid has never been seen on this node yet */
		// mlog(0, "no mle found\n");
		अगर (!mle) अणु
			spin_unlock(&dlm->master_lock);
			spin_unlock(&dlm->spinlock);

			mle = kmem_cache_alloc(dlm_mle_cache, GFP_NOFS);
			अगर (!mle) अणु
				response = DLM_MASTER_RESP_ERROR;
				mlog_त्रुटि_सं(-ENOMEM);
				जाओ send_response;
			पूर्ण
			जाओ way_up_top;
		पूर्ण

		// mlog(0, "this is second time thru, already allocated, "
		// "add the block.\n");
		dlm_init_mle(mle, DLM_MLE_BLOCK, dlm, शून्य, name, namelen);
		set_bit(request->node_idx, mle->maybe_map);
		__dlm_insert_mle(dlm, mle);
		response = DLM_MASTER_RESP_NO;
	पूर्ण अन्यथा अणु
		spin_lock(&पंचांगpmle->spinlock);
		अगर (पंचांगpmle->master == dlm->node_num) अणु
			mlog(ML_ERROR, "no lockres, but an mle with this node as master!\n");
			BUG();
		पूर्ण
		अगर (पंचांगpmle->type == DLM_MLE_BLOCK)
			response = DLM_MASTER_RESP_NO;
		अन्यथा अगर (पंचांगpmle->type == DLM_MLE_MIGRATION) अणु
			mlog(0, "migration mle was found (%u->%u)\n",
			     पंचांगpmle->master, पंचांगpmle->new_master);
			/* real master can respond on its own */
			response = DLM_MASTER_RESP_NO;
		पूर्ण अन्यथा
			response = DLM_MASTER_RESP_MAYBE;
		set_bit(request->node_idx, पंचांगpmle->maybe_map);
		spin_unlock(&पंचांगpmle->spinlock);
	पूर्ण
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);

	अगर (found) अणु
		/* keep the mle attached to heartbeat events */
		dlm_put_mle(पंचांगpmle);
	पूर्ण
send_response:
	/*
	 * __dlm_lookup_lockres() grabbed a reference to this lockres.
	 * The reference is released by dlm_निश्चित_master_worker() under
	 * the call to dlm_dispatch_निश्चित_master().  If
	 * dlm_निश्चित_master_worker() isn't called, we drop it here.
	 */
	अगर (dispatch_निश्चित) अणु
		mlog(0, "%u is the owner of %.*s, cleaning everyone else\n",
			     dlm->node_num, res->lockname.len, res->lockname.name);
		spin_lock(&res->spinlock);
		ret = dlm_dispatch_निश्चित_master(dlm, res, 0, request->node_idx,
						 DLM_ASSERT_MASTER_MLE_CLEANUP);
		अगर (ret < 0) अणु
			mlog(ML_ERROR, "failed to dispatch assert master work\n");
			response = DLM_MASTER_RESP_ERROR;
			spin_unlock(&res->spinlock);
			dlm_lockres_put(res);
		पूर्ण अन्यथा अणु
			dispatched = 1;
			__dlm_lockres_grab_inflight_worker(dlm, res);
			spin_unlock(&res->spinlock);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (res)
			dlm_lockres_put(res);
	पूर्ण

	अगर (!dispatched)
		dlm_put(dlm);
	वापस response;
पूर्ण

/*
 * DLM_ASSERT_MASTER_MSG
 */


/*
 * NOTE: this can be used क्रम debugging
 * can periodically run all locks owned by this node
 * and re-निश्चित across the cluster...
 */
अटल पूर्णांक dlm_करो_निश्चित_master(काष्ठा dlm_ctxt *dlm,
				काष्ठा dlm_lock_resource *res,
				व्योम *nodemap, u32 flags)
अणु
	काष्ठा dlm_निश्चित_master निश्चित;
	पूर्णांक to, पंचांगpret;
	काष्ठा dlm_node_iter iter;
	पूर्णांक ret = 0;
	पूर्णांक reनिश्चित;
	स्थिर अक्षर *lockname = res->lockname.name;
	अचिन्हित पूर्णांक namelen = res->lockname.len;

	BUG_ON(namelen > O2NM_MAX_NAME_LEN);

	spin_lock(&res->spinlock);
	res->state |= DLM_LOCK_RES_SETREF_INPROG;
	spin_unlock(&res->spinlock);

again:
	reनिश्चित = 0;

	/* note that अगर this nodemap is empty, it वापसs 0 */
	dlm_node_iter_init(nodemap, &iter);
	जबतक ((to = dlm_node_iter_next(&iter)) >= 0) अणु
		पूर्णांक r = 0;
		काष्ठा dlm_master_list_entry *mle = शून्य;

		mlog(0, "sending assert master to %d (%.*s)\n", to,
		     namelen, lockname);
		स_रखो(&निश्चित, 0, माप(निश्चित));
		निश्चित.node_idx = dlm->node_num;
		निश्चित.namelen = namelen;
		स_नकल(निश्चित.name, lockname, namelen);
		निश्चित.flags = cpu_to_be32(flags);

		पंचांगpret = o2net_send_message(DLM_ASSERT_MASTER_MSG, dlm->key,
					    &निश्चित, माप(निश्चित), to, &r);
		अगर (पंचांगpret < 0) अणु
			mlog(ML_ERROR, "Error %d when sending message %u (key "
			     "0x%x) to node %u\n", पंचांगpret,
			     DLM_ASSERT_MASTER_MSG, dlm->key, to);
			अगर (!dlm_is_host_करोwn(पंचांगpret)) अणु
				mlog(ML_ERROR, "unhandled error=%d!\n", पंचांगpret);
				BUG();
			पूर्ण
			/* a node died.  finish out the rest of the nodes. */
			mlog(0, "link to %d went down!\n", to);
			/* any nonzero status वापस will करो */
			ret = पंचांगpret;
			r = 0;
		पूर्ण अन्यथा अगर (r < 0) अणु
			/* ok, something horribly messed.  समाप्त thyself. */
			mlog(ML_ERROR,"during assert master of %.*s to %u, "
			     "got %d.\n", namelen, lockname, to, r);
			spin_lock(&dlm->spinlock);
			spin_lock(&dlm->master_lock);
			अगर (dlm_find_mle(dlm, &mle, (अक्षर *)lockname,
					 namelen)) अणु
				dlm_prपूर्णांक_one_mle(mle);
				__dlm_put_mle(mle);
			पूर्ण
			spin_unlock(&dlm->master_lock);
			spin_unlock(&dlm->spinlock);
			BUG();
		पूर्ण

		अगर (r & DLM_ASSERT_RESPONSE_REASSERT &&
		    !(r & DLM_ASSERT_RESPONSE_MASTERY_REF)) अणु
				mlog(ML_ERROR, "%.*s: very strange, "
				     "master MLE but no lockres on %u\n",
				     namelen, lockname, to);
		पूर्ण

		अगर (r & DLM_ASSERT_RESPONSE_REASSERT) अणु
			mlog(0, "%.*s: node %u create mles on other "
			     "nodes and requests a re-assert\n",
			     namelen, lockname, to);
			reनिश्चित = 1;
		पूर्ण
		अगर (r & DLM_ASSERT_RESPONSE_MASTERY_REF) अणु
			mlog(0, "%.*s: node %u has a reference to this "
			     "lockres, set the bit in the refmap\n",
			     namelen, lockname, to);
			spin_lock(&res->spinlock);
			dlm_lockres_set_refmap_bit(dlm, res, to);
			spin_unlock(&res->spinlock);
		पूर्ण
	पूर्ण

	अगर (reनिश्चित)
		जाओ again;

	spin_lock(&res->spinlock);
	res->state &= ~DLM_LOCK_RES_SETREF_INPROG;
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);

	वापस ret;
पूर्ण

/*
 * locks that can be taken here:
 * dlm->spinlock
 * res->spinlock
 * mle->spinlock
 * dlm->master_list
 *
 * अगर possible, TRIM THIS DOWN!!!
 */
पूर्णांक dlm_निश्चित_master_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			      व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_master_list_entry *mle = शून्य;
	काष्ठा dlm_निश्चित_master *निश्चित = (काष्ठा dlm_निश्चित_master *)msg->buf;
	काष्ठा dlm_lock_resource *res = शून्य;
	अक्षर *name;
	अचिन्हित पूर्णांक namelen, hash;
	u32 flags;
	पूर्णांक master_request = 0, have_lockres_ref = 0;
	पूर्णांक ret = 0;

	अगर (!dlm_grab(dlm))
		वापस 0;

	name = निश्चित->name;
	namelen = निश्चित->namelen;
	hash = dlm_lockid_hash(name, namelen);
	flags = be32_to_cpu(निश्चित->flags);

	अगर (namelen > DLM_LOCKID_NAME_MAX) अणु
		mlog(ML_ERROR, "Invalid name length!");
		जाओ करोne;
	पूर्ण

	spin_lock(&dlm->spinlock);

	अगर (flags)
		mlog(0, "assert_master with flags: %u\n", flags);

	/* find the MLE */
	spin_lock(&dlm->master_lock);
	अगर (!dlm_find_mle(dlm, &mle, name, namelen)) अणु
		/* not an error, could be master just re-निश्चितing */
		mlog(0, "just got an assert_master from %u, but no "
		     "MLE for it! (%.*s)\n", निश्चित->node_idx,
		     namelen, name);
	पूर्ण अन्यथा अणु
		पूर्णांक bit = find_next_bit (mle->maybe_map, O2NM_MAX_NODES, 0);
		अगर (bit >= O2NM_MAX_NODES) अणु
			/* not necessarily an error, though less likely.
			 * could be master just re-निश्चितing. */
			mlog(0, "no bits set in the maybe_map, but %u "
			     "is asserting! (%.*s)\n", निश्चित->node_idx,
			     namelen, name);
		पूर्ण अन्यथा अगर (bit != निश्चित->node_idx) अणु
			अगर (flags & DLM_ASSERT_MASTER_MLE_CLEANUP) अणु
				mlog(0, "master %u was found, %u should "
				     "back off\n", निश्चित->node_idx, bit);
			पूर्ण अन्यथा अणु
				/* with the fix क्रम bug 569, a higher node
				 * number winning the mastery will respond
				 * YES to mastery requests, but this node
				 * had no way of knowing.  let it pass. */
				mlog(0, "%u is the lowest node, "
				     "%u is asserting. (%.*s)  %u must "
				     "have begun after %u won.\n", bit,
				     निश्चित->node_idx, namelen, name, bit,
				     निश्चित->node_idx);
			पूर्ण
		पूर्ण
		अगर (mle->type == DLM_MLE_MIGRATION) अणु
			अगर (flags & DLM_ASSERT_MASTER_MLE_CLEANUP) अणु
				mlog(0, "%s:%.*s: got cleanup assert"
				     " from %u for migration\n",
				     dlm->name, namelen, name,
				     निश्चित->node_idx);
			पूर्ण अन्यथा अगर (!(flags & DLM_ASSERT_MASTER_FINISH_MIGRATION)) अणु
				mlog(0, "%s:%.*s: got unrelated assert"
				     " from %u for migration, ignoring\n",
				     dlm->name, namelen, name,
				     निश्चित->node_idx);
				__dlm_put_mle(mle);
				spin_unlock(&dlm->master_lock);
				spin_unlock(&dlm->spinlock);
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&dlm->master_lock);

	/* ok everything checks out with the MLE
	 * now check to see अगर there is a lockres */
	res = __dlm_lookup_lockres(dlm, name, namelen, hash);
	अगर (res) अणु
		spin_lock(&res->spinlock);
		अगर (res->state & DLM_LOCK_RES_RECOVERING)  अणु
			mlog(ML_ERROR, "%u asserting but %.*s is "
			     "RECOVERING!\n", निश्चित->node_idx, namelen, name);
			जाओ समाप्त;
		पूर्ण
		अगर (!mle) अणु
			अगर (res->owner != DLM_LOCK_RES_OWNER_UNKNOWN &&
			    res->owner != निश्चित->node_idx) अणु
				mlog(ML_ERROR, "DIE! Mastery assert from %u, "
				     "but current owner is %u! (%.*s)\n",
				     निश्चित->node_idx, res->owner, namelen,
				     name);
				__dlm_prपूर्णांक_one_lock_resource(res);
				BUG();
			पूर्ण
		पूर्ण अन्यथा अगर (mle->type != DLM_MLE_MIGRATION) अणु
			अगर (res->owner != DLM_LOCK_RES_OWNER_UNKNOWN) अणु
				/* owner is just re-निश्चितing */
				अगर (res->owner == निश्चित->node_idx) अणु
					mlog(0, "owner %u re-asserting on "
					     "lock %.*s\n", निश्चित->node_idx,
					     namelen, name);
					जाओ ok;
				पूर्ण
				mlog(ML_ERROR, "got assert_master from "
				     "node %u, but %u is the owner! "
				     "(%.*s)\n", निश्चित->node_idx,
				     res->owner, namelen, name);
				जाओ समाप्त;
			पूर्ण
			अगर (!(res->state & DLM_LOCK_RES_IN_PROGRESS)) अणु
				mlog(ML_ERROR, "got assert from %u, but lock "
				     "with no owner should be "
				     "in-progress! (%.*s)\n",
				     निश्चित->node_idx,
				     namelen, name);
				जाओ समाप्त;
			पूर्ण
		पूर्ण अन्यथा /* mle->type == DLM_MLE_MIGRATION */ अणु
			/* should only be getting an निश्चित from new master */
			अगर (निश्चित->node_idx != mle->new_master) अणु
				mlog(ML_ERROR, "got assert from %u, but "
				     "new master is %u, and old master "
				     "was %u (%.*s)\n",
				     निश्चित->node_idx, mle->new_master,
				     mle->master, namelen, name);
				जाओ समाप्त;
			पूर्ण

		पूर्ण
ok:
		spin_unlock(&res->spinlock);
	पूर्ण

	// mlog(0, "woo!  got an assert_master from node %u!\n",
	// 	     निश्चित->node_idx);
	अगर (mle) अणु
		पूर्णांक extra_ref = 0;
		पूर्णांक nn = -1;
		पूर्णांक rr, err = 0;

		spin_lock(&mle->spinlock);
		अगर (mle->type == DLM_MLE_BLOCK || mle->type == DLM_MLE_MIGRATION)
			extra_ref = 1;
		अन्यथा अणु
			/* MASTER mle: अगर any bits set in the response map
			 * then the calling node needs to re-निश्चित to clear
			 * up nodes that this node contacted */
			जबतक ((nn = find_next_bit (mle->response_map, O2NM_MAX_NODES,
						    nn+1)) < O2NM_MAX_NODES) अणु
				अगर (nn != dlm->node_num && nn != निश्चित->node_idx) अणु
					master_request = 1;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		mle->master = निश्चित->node_idx;
		atomic_set(&mle->woken, 1);
		wake_up(&mle->wq);
		spin_unlock(&mle->spinlock);

		अगर (res) अणु
			पूर्णांक wake = 0;
			spin_lock(&res->spinlock);
			अगर (mle->type == DLM_MLE_MIGRATION) अणु
				mlog(0, "finishing off migration of lockres %.*s, "
			     		"from %u to %u\n",
			       		res->lockname.len, res->lockname.name,
			       		dlm->node_num, mle->new_master);
				res->state &= ~DLM_LOCK_RES_MIGRATING;
				wake = 1;
				dlm_change_lockres_owner(dlm, res, mle->new_master);
				BUG_ON(res->state & DLM_LOCK_RES_सूचीTY);
			पूर्ण अन्यथा अणु
				dlm_change_lockres_owner(dlm, res, mle->master);
			पूर्ण
			spin_unlock(&res->spinlock);
			have_lockres_ref = 1;
			अगर (wake)
				wake_up(&res->wq);
		पूर्ण

		/* master is known, detach अगर not alपढ़ोy detached.
		 * ensures that only one निश्चित_master call will happen
		 * on this mle. */
		spin_lock(&dlm->master_lock);

		rr = kref_पढ़ो(&mle->mle_refs);
		अगर (mle->inuse > 0) अणु
			अगर (extra_ref && rr < 3)
				err = 1;
			अन्यथा अगर (!extra_ref && rr < 2)
				err = 1;
		पूर्ण अन्यथा अणु
			अगर (extra_ref && rr < 2)
				err = 1;
			अन्यथा अगर (!extra_ref && rr < 1)
				err = 1;
		पूर्ण
		अगर (err) अणु
			mlog(ML_ERROR, "%s:%.*s: got assert master from %u "
			     "that will mess up this node, refs=%d, extra=%d, "
			     "inuse=%d\n", dlm->name, namelen, name,
			     निश्चित->node_idx, rr, extra_ref, mle->inuse);
			dlm_prपूर्णांक_one_mle(mle);
		पूर्ण
		__dlm_unlink_mle(dlm, mle);
		__dlm_mle_detach_hb_events(dlm, mle);
		__dlm_put_mle(mle);
		अगर (extra_ref) अणु
			/* the निश्चित master message now balances the extra
		 	 * ref given by the master / migration request message.
		 	 * अगर this is the last put, it will be हटाओd
		 	 * from the list. */
			__dlm_put_mle(mle);
		पूर्ण
		spin_unlock(&dlm->master_lock);
	पूर्ण अन्यथा अगर (res) अणु
		अगर (res->owner != निश्चित->node_idx) अणु
			mlog(0, "assert_master from %u, but current "
			     "owner is %u (%.*s), no mle\n", निश्चित->node_idx,
			     res->owner, namelen, name);
		पूर्ण
	पूर्ण
	spin_unlock(&dlm->spinlock);

करोne:
	ret = 0;
	अगर (res) अणु
		spin_lock(&res->spinlock);
		res->state |= DLM_LOCK_RES_SETREF_INPROG;
		spin_unlock(&res->spinlock);
		*ret_data = (व्योम *)res;
	पूर्ण
	dlm_put(dlm);
	अगर (master_request) अणु
		mlog(0, "need to tell master to reassert\n");
		/* positive. negative would shoot करोwn the node. */
		ret |= DLM_ASSERT_RESPONSE_REASSERT;
		अगर (!have_lockres_ref) अणु
			mlog(ML_ERROR, "strange, got assert from %u, MASTER "
			     "mle present here for %s:%.*s, but no lockres!\n",
			     निश्चित->node_idx, dlm->name, namelen, name);
		पूर्ण
	पूर्ण
	अगर (have_lockres_ref) अणु
		/* let the master know we have a reference to the lockres */
		ret |= DLM_ASSERT_RESPONSE_MASTERY_REF;
		mlog(0, "%s:%.*s: got assert from %u, need a ref\n",
		     dlm->name, namelen, name, निश्चित->node_idx);
	पूर्ण
	वापस ret;

समाप्त:
	/* समाप्त the caller! */
	mlog(ML_ERROR, "Bad message received from another node.  Dumping state "
	     "and killing the other node now!  This node is OK and can continue.\n");
	__dlm_prपूर्णांक_one_lock_resource(res);
	spin_unlock(&res->spinlock);
	spin_lock(&dlm->master_lock);
	अगर (mle)
		__dlm_put_mle(mle);
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);
	*ret_data = (व्योम *)res;
	dlm_put(dlm);
	वापस -EINVAL;
पूर्ण

व्योम dlm_निश्चित_master_post_handler(पूर्णांक status, व्योम *data, व्योम *ret_data)
अणु
	काष्ठा dlm_lock_resource *res = (काष्ठा dlm_lock_resource *)ret_data;

	अगर (ret_data) अणु
		spin_lock(&res->spinlock);
		res->state &= ~DLM_LOCK_RES_SETREF_INPROG;
		spin_unlock(&res->spinlock);
		wake_up(&res->wq);
		dlm_lockres_put(res);
	पूर्ण
	वापस;
पूर्ण

पूर्णांक dlm_dispatch_निश्चित_master(काष्ठा dlm_ctxt *dlm,
			       काष्ठा dlm_lock_resource *res,
			       पूर्णांक ignore_higher, u8 request_from, u32 flags)
अणु
	काष्ठा dlm_work_item *item;
	item = kzalloc(माप(*item), GFP_ATOMIC);
	अगर (!item)
		वापस -ENOMEM;


	/* queue up work क्रम dlm_निश्चित_master_worker */
	dlm_init_work_item(dlm, item, dlm_निश्चित_master_worker, शून्य);
	item->u.am.lockres = res; /* alपढ़ोy have a ref */
	/* can optionally ignore node numbers higher than this node */
	item->u.am.ignore_higher = ignore_higher;
	item->u.am.request_from = request_from;
	item->u.am.flags = flags;

	अगर (ignore_higher)
		mlog(0, "IGNORE HIGHER: %.*s\n", res->lockname.len,
		     res->lockname.name);

	spin_lock(&dlm->work_lock);
	list_add_tail(&item->list, &dlm->work_list);
	spin_unlock(&dlm->work_lock);

	queue_work(dlm->dlm_worker, &dlm->dispatched_work);
	वापस 0;
पूर्ण

अटल व्योम dlm_निश्चित_master_worker(काष्ठा dlm_work_item *item, व्योम *data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	पूर्णांक ret = 0;
	काष्ठा dlm_lock_resource *res;
	अचिन्हित दीर्घ nodemap[BITS_TO_LONGS(O2NM_MAX_NODES)];
	पूर्णांक ignore_higher;
	पूर्णांक bit;
	u8 request_from;
	u32 flags;

	dlm = item->dlm;
	res = item->u.am.lockres;
	ignore_higher = item->u.am.ignore_higher;
	request_from = item->u.am.request_from;
	flags = item->u.am.flags;

	spin_lock(&dlm->spinlock);
	स_नकल(nodemap, dlm->करोमुख्य_map, माप(nodemap));
	spin_unlock(&dlm->spinlock);

	clear_bit(dlm->node_num, nodemap);
	अगर (ignore_higher) अणु
		/* अगर is this just to clear up mles क्रम nodes below
		 * this node, करो not send the message to the original
		 * caller or any node number higher than this */
		clear_bit(request_from, nodemap);
		bit = dlm->node_num;
		जबतक (1) अणु
			bit = find_next_bit(nodemap, O2NM_MAX_NODES,
					    bit+1);
		       	अगर (bit >= O2NM_MAX_NODES)
				अवरोध;
			clear_bit(bit, nodemap);
		पूर्ण
	पूर्ण

	/*
	 * If we're migrating this lock to someone अन्यथा, we are no
	 * दीर्घer allowed to निश्चित out own mastery.  OTOH, we need to
	 * prevent migration from starting जबतक we're still निश्चितing
	 * our करोminance.  The reserved ast delays migration.
	 */
	spin_lock(&res->spinlock);
	अगर (res->state & DLM_LOCK_RES_MIGRATING) अणु
		mlog(0, "Someone asked us to assert mastery, but we're "
		     "in the middle of migration.  Skipping assert, "
		     "the new master will handle that.\n");
		spin_unlock(&res->spinlock);
		जाओ put;
	पूर्ण अन्यथा
		__dlm_lockres_reserve_ast(res);
	spin_unlock(&res->spinlock);

	/* this call now finishes out the nodemap
	 * even अगर one or more nodes die */
	mlog(0, "worker about to master %.*s here, this=%u\n",
		     res->lockname.len, res->lockname.name, dlm->node_num);
	ret = dlm_करो_निश्चित_master(dlm, res, nodemap, flags);
	अगर (ret < 0) अणु
		/* no need to restart, we are करोne */
		अगर (!dlm_is_host_करोwn(ret))
			mlog_त्रुटि_सं(ret);
	पूर्ण

	/* Ok, we've asserted ourselves.  Let's let migration start. */
	dlm_lockres_release_ast(dlm, res);

put:
	dlm_lockres_drop_inflight_worker(dlm, res);

	dlm_lockres_put(res);

	mlog(0, "finished with dlm_assert_master_worker\n");
पूर्ण

/* SPECIAL CASE क्रम the $RECOVERY lock used by the recovery thपढ़ो.
 * We cannot रुको क्रम node recovery to complete to begin mastering this
 * lockres because this lockres is used to kick off recovery! ;-)
 * So, करो a pre-check on all living nodes to see अगर any of those nodes
 * think that $RECOVERY is currently mastered by a dead node.  If so,
 * we रुको a लघु समय to allow that node to get notअगरied by its own
 * heartbeat stack, then check again.  All $RECOVERY lock resources
 * mastered by dead nodes are purged when the heartbeat callback is
 * fired, so we can know क्रम sure that it is safe to जारी once
 * the node वापसs a live node or no node.  */
अटल पूर्णांक dlm_pre_master_reco_lockres(काष्ठा dlm_ctxt *dlm,
				       काष्ठा dlm_lock_resource *res)
अणु
	काष्ठा dlm_node_iter iter;
	पूर्णांक nodक्रमागत;
	पूर्णांक ret = 0;
	u8 master = DLM_LOCK_RES_OWNER_UNKNOWN;

	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->करोमुख्य_map, &iter);
	spin_unlock(&dlm->spinlock);

	जबतक ((nodक्रमागत = dlm_node_iter_next(&iter)) >= 0) अणु
		/* करो not send to self */
		अगर (nodक्रमागत == dlm->node_num)
			जारी;
		ret = dlm_करो_master_requery(dlm, res, nodक्रमागत, &master);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			अगर (!dlm_is_host_करोwn(ret))
				BUG();
			/* host is करोwn, so answer क्रम that node would be
			 * DLM_LOCK_RES_OWNER_UNKNOWN.  जारी. */
			ret = 0;
		पूर्ण

		अगर (master != DLM_LOCK_RES_OWNER_UNKNOWN) अणु
			/* check to see अगर this master is in the recovery map */
			spin_lock(&dlm->spinlock);
			अगर (test_bit(master, dlm->recovery_map)) अणु
				mlog(ML_NOTICE, "%s: node %u has not seen "
				     "node %u go down yet, and thinks the "
				     "dead node is mastering the recovery "
				     "lock.  must wait.\n", dlm->name,
				     nodक्रमागत, master);
				ret = -EAGAIN;
			पूर्ण
			spin_unlock(&dlm->spinlock);
			mlog(0, "%s: reco lock master is %u\n", dlm->name,
			     master);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * DLM_DEREF_LOCKRES_MSG
 */

पूर्णांक dlm_drop_lockres_ref(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res)
अणु
	काष्ठा dlm_deref_lockres deref;
	पूर्णांक ret = 0, r;
	स्थिर अक्षर *lockname;
	अचिन्हित पूर्णांक namelen;

	lockname = res->lockname.name;
	namelen = res->lockname.len;
	BUG_ON(namelen > O2NM_MAX_NAME_LEN);

	स_रखो(&deref, 0, माप(deref));
	deref.node_idx = dlm->node_num;
	deref.namelen = namelen;
	स_नकल(deref.name, lockname, namelen);

	ret = o2net_send_message(DLM_DEREF_LOCKRES_MSG, dlm->key,
				 &deref, माप(deref), res->owner, &r);
	अगर (ret < 0)
		mlog(ML_ERROR, "%s: res %.*s, error %d send DEREF to node %u\n",
		     dlm->name, namelen, lockname, ret, res->owner);
	अन्यथा अगर (r < 0) अणु
		/* BAD.  other node says I did not have a ref. */
		mlog(ML_ERROR, "%s: res %.*s, DEREF to node %u got %d\n",
		     dlm->name, namelen, lockname, res->owner, r);
		dlm_prपूर्णांक_one_lock_resource(res);
		अगर (r == -ENOMEM)
			BUG();
	पूर्ण अन्यथा
		ret = r;

	वापस ret;
पूर्ण

पूर्णांक dlm_deref_lockres_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			      व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_deref_lockres *deref = (काष्ठा dlm_deref_lockres *)msg->buf;
	काष्ठा dlm_lock_resource *res = शून्य;
	अक्षर *name;
	अचिन्हित पूर्णांक namelen;
	पूर्णांक ret = -EINVAL;
	u8 node;
	अचिन्हित पूर्णांक hash;
	काष्ठा dlm_work_item *item;
	पूर्णांक cleared = 0;
	पूर्णांक dispatch = 0;

	अगर (!dlm_grab(dlm))
		वापस 0;

	name = deref->name;
	namelen = deref->namelen;
	node = deref->node_idx;

	अगर (namelen > DLM_LOCKID_NAME_MAX) अणु
		mlog(ML_ERROR, "Invalid name length!");
		जाओ करोne;
	पूर्ण
	अगर (deref->node_idx >= O2NM_MAX_NODES) अणु
		mlog(ML_ERROR, "Invalid node number: %u\n", node);
		जाओ करोne;
	पूर्ण

	hash = dlm_lockid_hash(name, namelen);

	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres_full(dlm, name, namelen, hash);
	अगर (!res) अणु
		spin_unlock(&dlm->spinlock);
		mlog(ML_ERROR, "%s:%.*s: bad lockres name\n",
		     dlm->name, namelen, name);
		जाओ करोne;
	पूर्ण
	spin_unlock(&dlm->spinlock);

	spin_lock(&res->spinlock);
	अगर (res->state & DLM_LOCK_RES_SETREF_INPROG)
		dispatch = 1;
	अन्यथा अणु
		BUG_ON(res->state & DLM_LOCK_RES_DROPPING_REF);
		अगर (test_bit(node, res->refmap)) अणु
			dlm_lockres_clear_refmap_bit(dlm, res, node);
			cleared = 1;
		पूर्ण
	पूर्ण
	spin_unlock(&res->spinlock);

	अगर (!dispatch) अणु
		अगर (cleared)
			dlm_lockres_calc_usage(dlm, res);
		अन्यथा अणु
			mlog(ML_ERROR, "%s:%.*s: node %u trying to drop ref "
		     	"but it is already dropped!\n", dlm->name,
		     	res->lockname.len, res->lockname.name, node);
			dlm_prपूर्णांक_one_lock_resource(res);
		पूर्ण
		ret = DLM_DEREF_RESPONSE_DONE;
		जाओ करोne;
	पूर्ण

	item = kzalloc(माप(*item), GFP_NOFS);
	अगर (!item) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ करोne;
	पूर्ण

	dlm_init_work_item(dlm, item, dlm_deref_lockres_worker, शून्य);
	item->u.dl.deref_res = res;
	item->u.dl.deref_node = node;

	spin_lock(&dlm->work_lock);
	list_add_tail(&item->list, &dlm->work_list);
	spin_unlock(&dlm->work_lock);

	queue_work(dlm->dlm_worker, &dlm->dispatched_work);
	वापस DLM_DEREF_RESPONSE_INPROG;

करोne:
	अगर (res)
		dlm_lockres_put(res);
	dlm_put(dlm);

	वापस ret;
पूर्ण

पूर्णांक dlm_deref_lockres_करोne_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			      व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_deref_lockres_करोne *deref
			= (काष्ठा dlm_deref_lockres_करोne *)msg->buf;
	काष्ठा dlm_lock_resource *res = शून्य;
	अक्षर *name;
	अचिन्हित पूर्णांक namelen;
	पूर्णांक ret = -EINVAL;
	u8 node;
	अचिन्हित पूर्णांक hash;

	अगर (!dlm_grab(dlm))
		वापस 0;

	name = deref->name;
	namelen = deref->namelen;
	node = deref->node_idx;

	अगर (namelen > DLM_LOCKID_NAME_MAX) अणु
		mlog(ML_ERROR, "Invalid name length!");
		जाओ करोne;
	पूर्ण
	अगर (deref->node_idx >= O2NM_MAX_NODES) अणु
		mlog(ML_ERROR, "Invalid node number: %u\n", node);
		जाओ करोne;
	पूर्ण

	hash = dlm_lockid_hash(name, namelen);

	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres_full(dlm, name, namelen, hash);
	अगर (!res) अणु
		spin_unlock(&dlm->spinlock);
		mlog(ML_ERROR, "%s:%.*s: bad lockres name\n",
		     dlm->name, namelen, name);
		जाओ करोne;
	पूर्ण

	spin_lock(&res->spinlock);
	अगर (!(res->state & DLM_LOCK_RES_DROPPING_REF)) अणु
		spin_unlock(&res->spinlock);
		spin_unlock(&dlm->spinlock);
		mlog(ML_NOTICE, "%s:%.*s: node %u sends deref done "
			"but it is already derefed!\n", dlm->name,
			res->lockname.len, res->lockname.name, node);
		ret = 0;
		जाओ करोne;
	पूर्ण

	__dlm_करो_purge_lockres(dlm, res);
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);

	spin_unlock(&dlm->spinlock);

	ret = 0;
करोne:
	अगर (res)
		dlm_lockres_put(res);
	dlm_put(dlm);
	वापस ret;
पूर्ण

अटल व्योम dlm_drop_lockres_ref_करोne(काष्ठा dlm_ctxt *dlm,
		काष्ठा dlm_lock_resource *res, u8 node)
अणु
	काष्ठा dlm_deref_lockres_करोne deref;
	पूर्णांक ret = 0, r;
	स्थिर अक्षर *lockname;
	अचिन्हित पूर्णांक namelen;

	lockname = res->lockname.name;
	namelen = res->lockname.len;
	BUG_ON(namelen > O2NM_MAX_NAME_LEN);

	स_रखो(&deref, 0, माप(deref));
	deref.node_idx = dlm->node_num;
	deref.namelen = namelen;
	स_नकल(deref.name, lockname, namelen);

	ret = o2net_send_message(DLM_DEREF_LOCKRES_DONE, dlm->key,
				 &deref, माप(deref), node, &r);
	अगर (ret < 0) अणु
		mlog(ML_ERROR, "%s: res %.*s, error %d send DEREF DONE "
				" to node %u\n", dlm->name, namelen,
				lockname, ret, node);
	पूर्ण अन्यथा अगर (r < 0) अणु
		/* ignore the error */
		mlog(ML_ERROR, "%s: res %.*s, DEREF to node %u got %d\n",
		     dlm->name, namelen, lockname, node, r);
		dlm_prपूर्णांक_one_lock_resource(res);
	पूर्ण
पूर्ण

अटल व्योम dlm_deref_lockres_worker(काष्ठा dlm_work_item *item, व्योम *data)
अणु
	काष्ठा dlm_ctxt *dlm;
	काष्ठा dlm_lock_resource *res;
	u8 node;
	u8 cleared = 0;

	dlm = item->dlm;
	res = item->u.dl.deref_res;
	node = item->u.dl.deref_node;

	spin_lock(&res->spinlock);
	BUG_ON(res->state & DLM_LOCK_RES_DROPPING_REF);
	__dlm_रुको_on_lockres_flags(res, DLM_LOCK_RES_SETREF_INPROG);
	अगर (test_bit(node, res->refmap)) अणु
		dlm_lockres_clear_refmap_bit(dlm, res, node);
		cleared = 1;
	पूर्ण
	spin_unlock(&res->spinlock);

	dlm_drop_lockres_ref_करोne(dlm, res, node);

	अगर (cleared) अणु
		mlog(0, "%s:%.*s node %u ref dropped in dispatch\n",
		     dlm->name, res->lockname.len, res->lockname.name, node);
		dlm_lockres_calc_usage(dlm, res);
	पूर्ण अन्यथा अणु
		mlog(ML_ERROR, "%s:%.*s: node %u trying to drop ref "
		     "but it is already dropped!\n", dlm->name,
		     res->lockname.len, res->lockname.name, node);
		dlm_prपूर्णांक_one_lock_resource(res);
	पूर्ण

	dlm_lockres_put(res);
पूर्ण

/*
 * A migratable resource is one that is :
 * 1. locally mastered, and,
 * 2. zero local locks, and,
 * 3. one or more non-local locks, or, one or more references
 * Returns 1 अगर yes, 0 अगर not.
 */
अटल पूर्णांक dlm_is_lockres_migratable(काष्ठा dlm_ctxt *dlm,
				      काष्ठा dlm_lock_resource *res)
अणु
	क्रमागत dlm_lockres_list idx;
	पूर्णांक nonlocal = 0, node_ref;
	काष्ठा list_head *queue;
	काष्ठा dlm_lock *lock;
	u64 cookie;

	निश्चित_spin_locked(&res->spinlock);

	/* delay migration when the lockres is in MIGRATING state */
	अगर (res->state & DLM_LOCK_RES_MIGRATING)
		वापस 0;

	/* delay migration when the lockres is in RECOCERING state */
	अगर (res->state & (DLM_LOCK_RES_RECOVERING|
			DLM_LOCK_RES_RECOVERY_WAITING))
		वापस 0;

	अगर (res->owner != dlm->node_num)
		वापस 0;

        क्रम (idx = DLM_GRANTED_LIST; idx <= DLM_BLOCKED_LIST; idx++) अणु
		queue = dlm_list_idx_to_ptr(res, idx);
		list_क्रम_each_entry(lock, queue, list) अणु
			अगर (lock->ml.node != dlm->node_num) अणु
				nonlocal++;
				जारी;
			पूर्ण
			cookie = be64_to_cpu(lock->ml.cookie);
			mlog(0, "%s: Not migratable res %.*s, lock %u:%llu on "
			     "%s list\n", dlm->name, res->lockname.len,
			     res->lockname.name,
			     dlm_get_lock_cookie_node(cookie),
			     dlm_get_lock_cookie_seq(cookie),
			     dlm_list_in_text(idx));
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!nonlocal) अणु
		node_ref = find_next_bit(res->refmap, O2NM_MAX_NODES, 0);
		अगर (node_ref >= O2NM_MAX_NODES)
			वापस 0;
	पूर्ण

	mlog(0, "%s: res %.*s, Migratable\n", dlm->name, res->lockname.len,
	     res->lockname.name);

	वापस 1;
पूर्ण

/*
 * DLM_MIGRATE_LOCKRES
 */


अटल पूर्णांक dlm_migrate_lockres(काष्ठा dlm_ctxt *dlm,
			       काष्ठा dlm_lock_resource *res, u8 target)
अणु
	काष्ठा dlm_master_list_entry *mle = शून्य;
	काष्ठा dlm_master_list_entry *oldmle = शून्य;
 	काष्ठा dlm_migratable_lockres *mres = शून्य;
	पूर्णांक ret = 0;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक namelen;
	पूर्णांक mle_added = 0;
	पूर्णांक wake = 0;

	अगर (!dlm_grab(dlm))
		वापस -EINVAL;

	name = res->lockname.name;
	namelen = res->lockname.len;

	mlog(0, "%s: Migrating %.*s to node %u\n", dlm->name, namelen, name,
	     target);

	/* pपुनः_स्मृतिate up front. अगर this fails, पात */
	ret = -ENOMEM;
	mres = (काष्ठा dlm_migratable_lockres *) __get_मुक्त_page(GFP_NOFS);
	अगर (!mres) अणु
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	mle = kmem_cache_alloc(dlm_mle_cache, GFP_NOFS);
	अगर (!mle) अणु
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण
	ret = 0;

	/*
	 * clear any existing master requests and
	 * add the migration mle to the list
	 */
	spin_lock(&dlm->spinlock);
	spin_lock(&dlm->master_lock);
	ret = dlm_add_migration_mle(dlm, res, mle, &oldmle, name,
				    namelen, target, dlm->node_num);
	/* get an extra reference on the mle.
	 * otherwise the निश्चित_master from the new
	 * master will destroy this.
	 */
	अगर (ret != -EEXIST)
		dlm_get_mle_inuse(mle);

	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);

	अगर (ret == -EEXIST) अणु
		mlog(0, "another process is already migrating it\n");
		जाओ fail;
	पूर्ण
	mle_added = 1;

	/*
	 * set the MIGRATING flag and flush asts
	 * अगर we fail after this we need to re-dirty the lockres
	 */
	अगर (dlm_mark_lockres_migrating(dlm, res, target) < 0) अणु
		mlog(ML_ERROR, "tried to migrate %.*s to %u, but "
		     "the target went down.\n", res->lockname.len,
		     res->lockname.name, target);
		spin_lock(&res->spinlock);
		res->state &= ~DLM_LOCK_RES_MIGRATING;
		wake = 1;
		spin_unlock(&res->spinlock);
		ret = -EINVAL;
	पूर्ण

fail:
	अगर (ret != -EEXIST && oldmle) अणु
		/* master is known, detach अगर not alपढ़ोy detached */
		dlm_mle_detach_hb_events(dlm, oldmle);
		dlm_put_mle(oldmle);
	पूर्ण

	अगर (ret < 0) अणु
		अगर (mle_added) अणु
			dlm_mle_detach_hb_events(dlm, mle);
			dlm_put_mle(mle);
			dlm_put_mle_inuse(mle);
		पूर्ण अन्यथा अगर (mle) अणु
			kmem_cache_मुक्त(dlm_mle_cache, mle);
			mle = शून्य;
		पूर्ण
		जाओ leave;
	पूर्ण

	/*
	 * at this poपूर्णांक, we have a migration target, an mle
	 * in the master list, and the MIGRATING flag set on
	 * the lockres
	 */

	/* now that remote nodes are spinning on the MIGRATING flag,
	 * ensure that all निश्चित_master work is flushed. */
	flush_workqueue(dlm->dlm_worker);

	/* notअगरy new node and send all lock state */
	/* call send_one_lockres with migration flag.
	 * this serves as notice to the target node that a
	 * migration is starting. */
	ret = dlm_send_one_lockres(dlm, res, mres, target,
				   DLM_MRES_MIGRATION);

	अगर (ret < 0) अणु
		mlog(0, "migration to node %u failed with %d\n",
		     target, ret);
		/* migration failed, detach and clean up mle */
		dlm_mle_detach_hb_events(dlm, mle);
		dlm_put_mle(mle);
		dlm_put_mle_inuse(mle);
		spin_lock(&res->spinlock);
		res->state &= ~DLM_LOCK_RES_MIGRATING;
		wake = 1;
		spin_unlock(&res->spinlock);
		अगर (dlm_is_host_करोwn(ret))
			dlm_रुको_क्रम_node_death(dlm, target,
						DLM_NODE_DEATH_WAIT_MAX);
		जाओ leave;
	पूर्ण

	/* at this poपूर्णांक, the target sends a message to all nodes,
	 * (using dlm_करो_migrate_request).  this node is skipped since
	 * we had to put an mle in the list to begin the process.  this
	 * node now रुकोs क्रम target to करो an निश्चित master.  this node
	 * will be the last one notअगरied, ensuring that the migration
	 * is complete everywhere.  अगर the target dies जबतक this is
	 * going on, some nodes could potentially see the target as the
	 * master, so it is important that my recovery finds the migration
	 * mle and sets the master to UNKNOWN. */


	/* रुको क्रम new node to निश्चित master */
	जबतक (1) अणु
		ret = रुको_event_पूर्णांकerruptible_समयout(mle->wq,
					(atomic_पढ़ो(&mle->woken) == 1),
					msecs_to_jअगरfies(5000));

		अगर (ret >= 0) अणु
		       	अगर (atomic_पढ़ो(&mle->woken) == 1 ||
			    res->owner == target)
				अवरोध;

			mlog(0, "%s:%.*s: timed out during migration\n",
			     dlm->name, res->lockname.len, res->lockname.name);
			/* aव्योम hang during shutकरोwn when migrating lockres
			 * to a node which also goes करोwn */
			अगर (dlm_is_node_dead(dlm, target)) अणु
				mlog(0, "%s:%.*s: expected migration "
				     "target %u is no longer up, restarting\n",
				     dlm->name, res->lockname.len,
				     res->lockname.name, target);
				ret = -EINVAL;
				/* migration failed, detach and clean up mle */
				dlm_mle_detach_hb_events(dlm, mle);
				dlm_put_mle(mle);
				dlm_put_mle_inuse(mle);
				spin_lock(&res->spinlock);
				res->state &= ~DLM_LOCK_RES_MIGRATING;
				wake = 1;
				spin_unlock(&res->spinlock);
				जाओ leave;
			पूर्ण
		पूर्ण अन्यथा
			mlog(0, "%s:%.*s: caught signal during migration\n",
			     dlm->name, res->lockname.len, res->lockname.name);
	पूर्ण

	/* all करोne, set the owner, clear the flag */
	spin_lock(&res->spinlock);
	dlm_set_lockres_owner(dlm, res, target);
	res->state &= ~DLM_LOCK_RES_MIGRATING;
	dlm_हटाओ_nonlocal_locks(dlm, res);
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);

	/* master is known, detach अगर not alपढ़ोy detached */
	dlm_mle_detach_hb_events(dlm, mle);
	dlm_put_mle_inuse(mle);
	ret = 0;

	dlm_lockres_calc_usage(dlm, res);

leave:
	/* re-dirty the lockres अगर we failed */
	अगर (ret < 0)
		dlm_kick_thपढ़ो(dlm, res);

	/* wake up रुकोers अगर the MIGRATING flag got set
	 * but migration failed */
	अगर (wake)
		wake_up(&res->wq);

	अगर (mres)
		मुक्त_page((अचिन्हित दीर्घ)mres);

	dlm_put(dlm);

	mlog(0, "%s: Migrating %.*s to %u, returns %d\n", dlm->name, namelen,
	     name, target, ret);
	वापस ret;
पूर्ण

/*
 * Should be called only after beginning the करोमुख्य leave process.
 * There should not be any reमुख्यing locks on nonlocal lock resources,
 * and there should be no local locks left on locally mastered resources.
 *
 * Called with the dlm spinlock held, may drop it to करो migration, but
 * will re-acquire beक्रमe निकास.
 *
 * Returns: 1 अगर dlm->spinlock was dropped/retaken, 0 अगर never dropped
 */
पूर्णांक dlm_empty_lockres(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res)
	__must_hold(&dlm->spinlock)
अणु
	पूर्णांक ret;
	पूर्णांक lock_dropped = 0;
	u8 target = O2NM_MAX_NODES;

	निश्चित_spin_locked(&dlm->spinlock);

	spin_lock(&res->spinlock);
	अगर (dlm_is_lockres_migratable(dlm, res))
		target = dlm_pick_migration_target(dlm, res);
	spin_unlock(&res->spinlock);

	अगर (target == O2NM_MAX_NODES)
		जाओ leave;

	/* Wheee! Migrate lockres here! Will sleep so drop spinlock. */
	spin_unlock(&dlm->spinlock);
	lock_dropped = 1;
	ret = dlm_migrate_lockres(dlm, res, target);
	अगर (ret)
		mlog(0, "%s: res %.*s, Migrate to node %u failed with %d\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     target, ret);
	spin_lock(&dlm->spinlock);
leave:
	वापस lock_dropped;
पूर्ण

पूर्णांक dlm_lock_basts_flushed(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock *lock)
अणु
	पूर्णांक ret;
	spin_lock(&dlm->ast_lock);
	spin_lock(&lock->spinlock);
	ret = (list_empty(&lock->bast_list) && !lock->bast_pending);
	spin_unlock(&lock->spinlock);
	spin_unlock(&dlm->ast_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dlm_migration_can_proceed(काष्ठा dlm_ctxt *dlm,
				     काष्ठा dlm_lock_resource *res,
				     u8 mig_target)
अणु
	पूर्णांक can_proceed;
	spin_lock(&res->spinlock);
	can_proceed = !!(res->state & DLM_LOCK_RES_MIGRATING);
	spin_unlock(&res->spinlock);

	/* target has died, so make the caller अवरोध out of the
	 * रुको_event, but caller must recheck the करोमुख्य_map */
	spin_lock(&dlm->spinlock);
	अगर (!test_bit(mig_target, dlm->करोमुख्य_map))
		can_proceed = 1;
	spin_unlock(&dlm->spinlock);
	वापस can_proceed;
पूर्ण

अटल पूर्णांक dlm_lockres_is_dirty(काष्ठा dlm_ctxt *dlm,
				काष्ठा dlm_lock_resource *res)
अणु
	पूर्णांक ret;
	spin_lock(&res->spinlock);
	ret = !!(res->state & DLM_LOCK_RES_सूचीTY);
	spin_unlock(&res->spinlock);
	वापस ret;
पूर्ण


अटल पूर्णांक dlm_mark_lockres_migrating(काष्ठा dlm_ctxt *dlm,
				       काष्ठा dlm_lock_resource *res,
				       u8 target)
अणु
	पूर्णांक ret = 0;

	mlog(0, "dlm_mark_lockres_migrating: %.*s, from %u to %u\n",
	       res->lockname.len, res->lockname.name, dlm->node_num,
	       target);
	/* need to set MIGRATING flag on lockres.  this is करोne by
	 * ensuring that all asts have been flushed क्रम this lockres. */
	spin_lock(&res->spinlock);
	BUG_ON(res->migration_pending);
	res->migration_pending = 1;
	/* strategy is to reserve an extra ast then release
	 * it below, letting the release करो all of the work */
	__dlm_lockres_reserve_ast(res);
	spin_unlock(&res->spinlock);

	/* now flush all the pending asts */
	dlm_kick_thपढ़ो(dlm, res);
	/* beक्रमe रुकोing on सूचीTY, block processes which may
	 * try to dirty the lockres beक्रमe MIGRATING is set */
	spin_lock(&res->spinlock);
	BUG_ON(res->state & DLM_LOCK_RES_BLOCK_सूचीTY);
	res->state |= DLM_LOCK_RES_BLOCK_सूचीTY;
	spin_unlock(&res->spinlock);
	/* now रुको on any pending asts and the सूचीTY state */
	रुको_event(dlm->ast_wq, !dlm_lockres_is_dirty(dlm, res));
	dlm_lockres_release_ast(dlm, res);

	mlog(0, "about to wait on migration_wq, dirty=%s\n",
	       res->state & DLM_LOCK_RES_सूचीTY ? "yes" : "no");
	/* अगर the extra ref we just put was the final one, this
	 * will pass thru immediately.  otherwise, we need to रुको
	 * क्रम the last ast to finish. */
again:
	ret = रुको_event_पूर्णांकerruptible_समयout(dlm->migration_wq,
		   dlm_migration_can_proceed(dlm, res, target),
		   msecs_to_jअगरfies(1000));
	अगर (ret < 0) अणु
		mlog(0, "woken again: migrating? %s, dead? %s\n",
		       res->state & DLM_LOCK_RES_MIGRATING ? "yes":"no",
		       test_bit(target, dlm->करोमुख्य_map) ? "no":"yes");
	पूर्ण अन्यथा अणु
		mlog(0, "all is well: migrating? %s, dead? %s\n",
		       res->state & DLM_LOCK_RES_MIGRATING ? "yes":"no",
		       test_bit(target, dlm->करोमुख्य_map) ? "no":"yes");
	पूर्ण
	अगर (!dlm_migration_can_proceed(dlm, res, target)) अणु
		mlog(0, "trying again...\n");
		जाओ again;
	पूर्ण

	ret = 0;
	/* did the target go करोwn or die? */
	spin_lock(&dlm->spinlock);
	अगर (!test_bit(target, dlm->करोमुख्य_map)) अणु
		mlog(ML_ERROR, "aha. migration target %u just went down\n",
		     target);
		ret = -EHOSTDOWN;
	पूर्ण
	spin_unlock(&dlm->spinlock);

	/*
	 * अगर target is करोwn, we need to clear DLM_LOCK_RES_BLOCK_सूचीTY क्रम
	 * another try; otherwise, we are sure the MIGRATING state is there,
	 * drop the unneeded state which blocked thपढ़ोs trying to सूचीTY
	 */
	spin_lock(&res->spinlock);
	BUG_ON(!(res->state & DLM_LOCK_RES_BLOCK_सूचीTY));
	res->state &= ~DLM_LOCK_RES_BLOCK_सूचीTY;
	अगर (!ret)
		BUG_ON(!(res->state & DLM_LOCK_RES_MIGRATING));
	अन्यथा
		res->migration_pending = 0;
	spin_unlock(&res->spinlock);

	/*
	 * at this poपूर्णांक:
	 *
	 *   o the DLM_LOCK_RES_MIGRATING flag is set अगर target not करोwn
	 *   o there are no pending asts on this lockres
	 *   o all processes trying to reserve an ast on this
	 *     lockres must रुको क्रम the MIGRATING flag to clear
	 */
	वापस ret;
पूर्ण

/* last step in the migration process.
 * original master calls this to मुक्त all of the dlm_lock
 * काष्ठाures that used to be क्रम other nodes. */
अटल व्योम dlm_हटाओ_nonlocal_locks(काष्ठा dlm_ctxt *dlm,
				      काष्ठा dlm_lock_resource *res)
अणु
	काष्ठा list_head *queue = &res->granted;
	पूर्णांक i, bit;
	काष्ठा dlm_lock *lock, *next;

	निश्चित_spin_locked(&res->spinlock);

	BUG_ON(res->owner == dlm->node_num);

	क्रम (i=0; i<3; i++) अणु
		list_क्रम_each_entry_safe(lock, next, queue, list) अणु
			अगर (lock->ml.node != dlm->node_num) अणु
				mlog(0, "putting lock for node %u\n",
				     lock->ml.node);
				/* be extra careful */
				BUG_ON(!list_empty(&lock->ast_list));
				BUG_ON(!list_empty(&lock->bast_list));
				BUG_ON(lock->ast_pending);
				BUG_ON(lock->bast_pending);
				dlm_lockres_clear_refmap_bit(dlm, res,
							     lock->ml.node);
				list_del_init(&lock->list);
				dlm_lock_put(lock);
				/* In a normal unlock, we would have added a
				 * DLM_UNLOCK_FREE_LOCK action. Force it. */
				dlm_lock_put(lock);
			पूर्ण
		पूर्ण
		queue++;
	पूर्ण
	bit = 0;
	जबतक (1) अणु
		bit = find_next_bit(res->refmap, O2NM_MAX_NODES, bit);
		अगर (bit >= O2NM_MAX_NODES)
			अवरोध;
		/* करो not clear the local node reference, अगर there is a
		 * process holding this, let it drop the ref itself */
		अगर (bit != dlm->node_num) अणु
			mlog(0, "%s:%.*s: node %u had a ref to this "
			     "migrating lockres, clearing\n", dlm->name,
			     res->lockname.len, res->lockname.name, bit);
			dlm_lockres_clear_refmap_bit(dlm, res, bit);
		पूर्ण
		bit++;
	पूर्ण
पूर्ण

/*
 * Pick a node to migrate the lock resource to. This function selects a
 * potential target based first on the locks and then on refmap. It skips
 * nodes that are in the process of निकासing the करोमुख्य.
 */
अटल u8 dlm_pick_migration_target(काष्ठा dlm_ctxt *dlm,
				    काष्ठा dlm_lock_resource *res)
अणु
	क्रमागत dlm_lockres_list idx;
	काष्ठा list_head *queue = &res->granted;
	काष्ठा dlm_lock *lock;
	पूर्णांक noderef;
	u8 nodक्रमागत = O2NM_MAX_NODES;

	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&res->spinlock);

	/* Go through all the locks */
	क्रम (idx = DLM_GRANTED_LIST; idx <= DLM_BLOCKED_LIST; idx++) अणु
		queue = dlm_list_idx_to_ptr(res, idx);
		list_क्रम_each_entry(lock, queue, list) अणु
			अगर (lock->ml.node == dlm->node_num)
				जारी;
			अगर (test_bit(lock->ml.node, dlm->निकास_करोमुख्य_map))
				जारी;
			nodक्रमागत = lock->ml.node;
			जाओ bail;
		पूर्ण
	पूर्ण

	/* Go thru the refmap */
	noderef = -1;
	जबतक (1) अणु
		noderef = find_next_bit(res->refmap, O2NM_MAX_NODES,
					noderef + 1);
		अगर (noderef >= O2NM_MAX_NODES)
			अवरोध;
		अगर (noderef == dlm->node_num)
			जारी;
		अगर (test_bit(noderef, dlm->निकास_करोमुख्य_map))
			जारी;
		nodक्रमागत = noderef;
		जाओ bail;
	पूर्ण

bail:
	वापस nodक्रमागत;
पूर्ण

/* this is called by the new master once all lockres
 * data has been received */
अटल पूर्णांक dlm_करो_migrate_request(काष्ठा dlm_ctxt *dlm,
				  काष्ठा dlm_lock_resource *res,
				  u8 master, u8 new_master,
				  काष्ठा dlm_node_iter *iter)
अणु
	काष्ठा dlm_migrate_request migrate;
	पूर्णांक ret, skip, status = 0;
	पूर्णांक nodक्रमागत;

	स_रखो(&migrate, 0, माप(migrate));
	migrate.namelen = res->lockname.len;
	स_नकल(migrate.name, res->lockname.name, migrate.namelen);
	migrate.new_master = new_master;
	migrate.master = master;

	ret = 0;

	/* send message to all nodes, except the master and myself */
	जबतक ((nodक्रमागत = dlm_node_iter_next(iter)) >= 0) अणु
		अगर (nodक्रमागत == master ||
		    nodक्रमागत == new_master)
			जारी;

		/* We could race निकास करोमुख्य. If निकासed, skip. */
		spin_lock(&dlm->spinlock);
		skip = (!test_bit(nodक्रमागत, dlm->करोमुख्य_map));
		spin_unlock(&dlm->spinlock);
		अगर (skip) अणु
			clear_bit(nodक्रमागत, iter->node_map);
			जारी;
		पूर्ण

		ret = o2net_send_message(DLM_MIGRATE_REQUEST_MSG, dlm->key,
					 &migrate, माप(migrate), nodक्रमागत,
					 &status);
		अगर (ret < 0) अणु
			mlog(ML_ERROR, "%s: res %.*s, Error %d send "
			     "MIGRATE_REQUEST to node %u\n", dlm->name,
			     migrate.namelen, migrate.name, ret, nodक्रमागत);
			अगर (!dlm_is_host_करोwn(ret)) अणु
				mlog(ML_ERROR, "unhandled error=%d!\n", ret);
				BUG();
			पूर्ण
			clear_bit(nodक्रमागत, iter->node_map);
			ret = 0;
		पूर्ण अन्यथा अगर (status < 0) अणु
			mlog(0, "migrate request (node %u) returned %d!\n",
			     nodक्रमागत, status);
			ret = status;
		पूर्ण अन्यथा अगर (status == DLM_MIGRATE_RESPONSE_MASTERY_REF) अणु
			/* during the migration request we लघु-circuited
			 * the mastery of the lockres.  make sure we have
			 * a mastery ref क्रम nodक्रमागत */
			mlog(0, "%s:%.*s: need ref for node %u\n",
			     dlm->name, res->lockname.len, res->lockname.name,
			     nodक्रमागत);
			spin_lock(&res->spinlock);
			dlm_lockres_set_refmap_bit(dlm, res, nodक्रमागत);
			spin_unlock(&res->spinlock);
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

	mlog(0, "returning ret=%d\n", ret);
	वापस ret;
पूर्ण


/* अगर there is an existing mle क्रम this lockres, we now know who the master is.
 * (the one who sent us *this* message) we can clear it up right away.
 * since the process that put the mle on the list still has a reference to it,
 * we can unhash it now, set the master and wake the process.  as a result,
 * we will have no mle in the list to start with.  now we can add an mle क्रम
 * the migration and this should be the only one found क्रम those scanning the
 * list.  */
पूर्णांक dlm_migrate_request_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_lock_resource *res = शून्य;
	काष्ठा dlm_migrate_request *migrate = (काष्ठा dlm_migrate_request *) msg->buf;
	काष्ठा dlm_master_list_entry *mle = शून्य, *oldmle = शून्य;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक namelen, hash;
	पूर्णांक ret = 0;

	अगर (!dlm_grab(dlm))
		वापस 0;

	name = migrate->name;
	namelen = migrate->namelen;
	hash = dlm_lockid_hash(name, namelen);

	/* pपुनः_स्मृतिate.. अगर this fails, पात */
	mle = kmem_cache_alloc(dlm_mle_cache, GFP_NOFS);

	अगर (!mle) अणु
		ret = -ENOMEM;
		जाओ leave;
	पूर्ण

	/* check क्रम pre-existing lock */
	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres(dlm, name, namelen, hash);
	अगर (res) अणु
		spin_lock(&res->spinlock);
		अगर (res->state & DLM_LOCK_RES_RECOVERING) अणु
			/* अगर all is working ok, this can only mean that we got
		 	* a migrate request from a node that we now see as
		 	* dead.  what can we करो here?  drop it to the न्यूनमान? */
			spin_unlock(&res->spinlock);
			mlog(ML_ERROR, "Got a migrate request, but the "
			     "lockres is marked as recovering!");
			kmem_cache_मुक्त(dlm_mle_cache, mle);
			ret = -EINVAL; /* need a better solution */
			जाओ unlock;
		पूर्ण
		res->state |= DLM_LOCK_RES_MIGRATING;
		spin_unlock(&res->spinlock);
	पूर्ण

	spin_lock(&dlm->master_lock);
	/* ignore status.  only nonzero status would BUG. */
	ret = dlm_add_migration_mle(dlm, res, mle, &oldmle,
				    name, namelen,
				    migrate->new_master,
				    migrate->master);

	अगर (ret < 0)
		kmem_cache_मुक्त(dlm_mle_cache, mle);

	spin_unlock(&dlm->master_lock);
unlock:
	spin_unlock(&dlm->spinlock);

	अगर (oldmle) अणु
		/* master is known, detach अगर not alपढ़ोy detached */
		dlm_mle_detach_hb_events(dlm, oldmle);
		dlm_put_mle(oldmle);
	पूर्ण

	अगर (res)
		dlm_lockres_put(res);
leave:
	dlm_put(dlm);
	वापस ret;
पूर्ण

/* must be holding dlm->spinlock and dlm->master_lock
 * when adding a migration mle, we can clear any other mles
 * in the master list because we know with certaपूर्णांकy that
 * the master is "master".  so we हटाओ any old mle from
 * the list after setting it's master field, and then add
 * the new migration mle.  this way we can hold with the rule
 * of having only one mle क्रम a given lock name at all बार. */
अटल पूर्णांक dlm_add_migration_mle(काष्ठा dlm_ctxt *dlm,
				 काष्ठा dlm_lock_resource *res,
				 काष्ठा dlm_master_list_entry *mle,
				 काष्ठा dlm_master_list_entry **oldmle,
				 स्थिर अक्षर *name, अचिन्हित पूर्णांक namelen,
				 u8 new_master, u8 master)
अणु
	पूर्णांक found;
	पूर्णांक ret = 0;

	*oldmle = शून्य;

	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&dlm->master_lock);

	/* caller is responsible क्रम any ref taken here on oldmle */
	found = dlm_find_mle(dlm, oldmle, (अक्षर *)name, namelen);
	अगर (found) अणु
		काष्ठा dlm_master_list_entry *पंचांगp = *oldmle;
		spin_lock(&पंचांगp->spinlock);
		अगर (पंचांगp->type == DLM_MLE_MIGRATION) अणु
			अगर (master == dlm->node_num) अणु
				/* ah another process raced me to it */
				mlog(0, "tried to migrate %.*s, but some "
				     "process beat me to it\n",
				     namelen, name);
				spin_unlock(&पंचांगp->spinlock);
				वापस -EEXIST;
			पूर्ण अन्यथा अणु
				/* bad.  2 NODES are trying to migrate! */
				mlog(ML_ERROR, "migration error  mle: "
				     "master=%u new_master=%u // request: "
				     "master=%u new_master=%u // "
				     "lockres=%.*s\n",
				     पंचांगp->master, पंचांगp->new_master,
				     master, new_master,
				     namelen, name);
				BUG();
			पूर्ण
		पूर्ण अन्यथा अणु
			/* this is essentially what निश्चित_master करोes */
			पंचांगp->master = master;
			atomic_set(&पंचांगp->woken, 1);
			wake_up(&पंचांगp->wq);
			/* हटाओ it so that only one mle will be found */
			__dlm_unlink_mle(dlm, पंचांगp);
			__dlm_mle_detach_hb_events(dlm, पंचांगp);
			अगर (पंचांगp->type == DLM_MLE_MASTER) अणु
				ret = DLM_MIGRATE_RESPONSE_MASTERY_REF;
				mlog(0, "%s:%.*s: master=%u, newmaster=%u, "
						"telling master to get ref "
						"for cleared out mle during "
						"migration\n", dlm->name,
						namelen, name, master,
						new_master);
			पूर्ण
		पूर्ण
		spin_unlock(&पंचांगp->spinlock);
	पूर्ण

	/* now add a migration mle to the tail of the list */
	dlm_init_mle(mle, DLM_MLE_MIGRATION, dlm, res, name, namelen);
	mle->new_master = new_master;
	/* the new master will be sending an निश्चित master क्रम this.
	 * at that poपूर्णांक we will get the refmap reference */
	mle->master = master;
	/* करो this क्रम consistency with other mle types */
	set_bit(new_master, mle->maybe_map);
	__dlm_insert_mle(dlm, mle);

	वापस ret;
पूर्ण

/*
 * Sets the owner of the lockres, associated to the mle, to UNKNOWN
 */
अटल काष्ठा dlm_lock_resource *dlm_reset_mleres_owner(काष्ठा dlm_ctxt *dlm,
					काष्ठा dlm_master_list_entry *mle)
अणु
	काष्ठा dlm_lock_resource *res;

	/* Find the lockres associated to the mle and set its owner to UNK */
	res = __dlm_lookup_lockres(dlm, mle->mname, mle->mnamelen,
				   mle->mnamehash);
	अगर (res) अणु
		spin_unlock(&dlm->master_lock);

		/* move lockres onto recovery list */
		spin_lock(&res->spinlock);
		dlm_set_lockres_owner(dlm, res, DLM_LOCK_RES_OWNER_UNKNOWN);
		dlm_move_lockres_to_recovery_list(dlm, res);
		spin_unlock(&res->spinlock);
		dlm_lockres_put(res);

		/* about to get rid of mle, detach from heartbeat */
		__dlm_mle_detach_hb_events(dlm, mle);

		/* dump the mle */
		spin_lock(&dlm->master_lock);
		__dlm_put_mle(mle);
		spin_unlock(&dlm->master_lock);
	पूर्ण

	वापस res;
पूर्ण

अटल व्योम dlm_clean_migration_mle(काष्ठा dlm_ctxt *dlm,
				    काष्ठा dlm_master_list_entry *mle)
अणु
	__dlm_mle_detach_hb_events(dlm, mle);

	spin_lock(&mle->spinlock);
	__dlm_unlink_mle(dlm, mle);
	atomic_set(&mle->woken, 1);
	spin_unlock(&mle->spinlock);

	wake_up(&mle->wq);
पूर्ण

अटल व्योम dlm_clean_block_mle(काष्ठा dlm_ctxt *dlm,
				काष्ठा dlm_master_list_entry *mle, u8 dead_node)
अणु
	पूर्णांक bit;

	BUG_ON(mle->type != DLM_MLE_BLOCK);

	spin_lock(&mle->spinlock);
	bit = find_next_bit(mle->maybe_map, O2NM_MAX_NODES, 0);
	अगर (bit != dead_node) अणु
		mlog(0, "mle found, but dead node %u would not have been "
		     "master\n", dead_node);
		spin_unlock(&mle->spinlock);
	पूर्ण अन्यथा अणु
		/* Must drop the refcount by one since the निश्चित_master will
		 * never arrive. This may result in the mle being unlinked and
		 * मुक्तd, but there may still be a process रुकोing in the
		 * dlmlock path which is fine. */
		mlog(0, "node %u was expected master\n", dead_node);
		atomic_set(&mle->woken, 1);
		spin_unlock(&mle->spinlock);
		wake_up(&mle->wq);

		/* Do not need events any दीर्घer, so detach from heartbeat */
		__dlm_mle_detach_hb_events(dlm, mle);
		__dlm_put_mle(mle);
	पूर्ण
पूर्ण

व्योम dlm_clean_master_list(काष्ठा dlm_ctxt *dlm, u8 dead_node)
अणु
	काष्ठा dlm_master_list_entry *mle;
	काष्ठा dlm_lock_resource *res;
	काष्ठा hlist_head *bucket;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित पूर्णांक i;

	mlog(0, "dlm=%s, dead node=%u\n", dlm->name, dead_node);
top:
	निश्चित_spin_locked(&dlm->spinlock);

	/* clean the master list */
	spin_lock(&dlm->master_lock);
	क्रम (i = 0; i < DLM_HASH_BUCKETS; i++) अणु
		bucket = dlm_master_hash(dlm, i);
		hlist_क्रम_each_entry_safe(mle, पंचांगp, bucket, master_hash_node) अणु
			BUG_ON(mle->type != DLM_MLE_BLOCK &&
			       mle->type != DLM_MLE_MASTER &&
			       mle->type != DLM_MLE_MIGRATION);

			/* MASTER mles are initiated locally. The रुकोing
			 * process will notice the node map change लघुly.
			 * Let that happen as normal. */
			अगर (mle->type == DLM_MLE_MASTER)
				जारी;

			/* BLOCK mles are initiated by other nodes. Need to
			 * clean up अगर the dead node would have been the
			 * master. */
			अगर (mle->type == DLM_MLE_BLOCK) अणु
				dlm_clean_block_mle(dlm, mle, dead_node);
				जारी;
			पूर्ण

			/* Everything अन्यथा is a MIGRATION mle */

			/* The rule क्रम MIGRATION mles is that the master
			 * becomes UNKNOWN अगर *either* the original or the new
			 * master dies. All UNKNOWN lockres' are sent to
			 * whichever node becomes the recovery master. The new
			 * master is responsible क्रम determining अगर there is
			 * still a master क्रम this lockres, or अगर he needs to
			 * take over mastery. Either way, this node should
			 * expect another message to resolve this. */

			अगर (mle->master != dead_node &&
			    mle->new_master != dead_node)
				जारी;

			अगर (mle->new_master == dead_node && mle->inuse) अणु
				mlog(ML_NOTICE, "%s: target %u died during "
						"migration from %u, the MLE is "
						"still keep used, ignore it!\n",
						dlm->name, dead_node,
						mle->master);
				जारी;
			पूर्ण

			/* If we have reached this poपूर्णांक, this mle needs to be
			 * हटाओd from the list and मुक्तd. */
			dlm_clean_migration_mle(dlm, mle);

			mlog(0, "%s: node %u died during migration from "
			     "%u to %u!\n", dlm->name, dead_node, mle->master,
			     mle->new_master);

			/* If we find a lockres associated with the mle, we've
			 * hit this rare हाल that messes up our lock ordering.
			 * If so, we need to drop the master lock so that we can
			 * take the lockres lock, meaning that we will have to
			 * restart from the head of list. */
			res = dlm_reset_mleres_owner(dlm, mle);
			अगर (res)
				/* restart */
				जाओ top;

			/* This may be the last reference */
			__dlm_put_mle(mle);
		पूर्ण
	पूर्ण
	spin_unlock(&dlm->master_lock);
पूर्ण

पूर्णांक dlm_finish_migration(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res,
			 u8 old_master)
अणु
	काष्ठा dlm_node_iter iter;
	पूर्णांक ret = 0;

	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->करोमुख्य_map, &iter);
	clear_bit(old_master, iter.node_map);
	clear_bit(dlm->node_num, iter.node_map);
	spin_unlock(&dlm->spinlock);

	/* ownership of the lockres is changing.  account क्रम the
	 * mastery reference here since old_master will briefly have
	 * a reference after the migration completes */
	spin_lock(&res->spinlock);
	dlm_lockres_set_refmap_bit(dlm, res, old_master);
	spin_unlock(&res->spinlock);

	mlog(0, "now time to do a migrate request to other nodes\n");
	ret = dlm_करो_migrate_request(dlm, res, old_master,
				     dlm->node_num, &iter);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	mlog(0, "doing assert master of %.*s to all except the original node\n",
	     res->lockname.len, res->lockname.name);
	/* this call now finishes out the nodemap
	 * even अगर one or more nodes die */
	ret = dlm_करो_निश्चित_master(dlm, res, iter.node_map,
				   DLM_ASSERT_MASTER_FINISH_MIGRATION);
	अगर (ret < 0) अणु
		/* no दीर्घer need to retry.  all living nodes contacted. */
		mlog_त्रुटि_सं(ret);
		ret = 0;
	पूर्ण

	स_रखो(iter.node_map, 0, माप(iter.node_map));
	set_bit(old_master, iter.node_map);
	mlog(0, "doing assert master of %.*s back to %u\n",
	     res->lockname.len, res->lockname.name, old_master);
	ret = dlm_करो_निश्चित_master(dlm, res, iter.node_map,
				   DLM_ASSERT_MASTER_FINISH_MIGRATION);
	अगर (ret < 0) अणु
		mlog(0, "assert master to original master failed "
		     "with %d.\n", ret);
		/* the only nonzero status here would be because of
		 * a dead original node.  we're करोne. */
		ret = 0;
	पूर्ण

	/* all करोne, set the owner, clear the flag */
	spin_lock(&res->spinlock);
	dlm_set_lockres_owner(dlm, res, dlm->node_num);
	res->state &= ~DLM_LOCK_RES_MIGRATING;
	spin_unlock(&res->spinlock);
	/* re-dirty it on the new master */
	dlm_kick_thपढ़ो(dlm, res);
	wake_up(&res->wq);
leave:
	वापस ret;
पूर्ण

/*
 * LOCKRES AST REFCOUNT
 * this is पूर्णांकegral to migration
 */

/* क्रम future पूर्णांकent to call an ast, reserve one ahead of समय.
 * this should be called only after रुकोing on the lockres
 * with dlm_रुको_on_lockres, and जबतक still holding the
 * spinlock after the call. */
व्योम __dlm_lockres_reserve_ast(काष्ठा dlm_lock_resource *res)
अणु
	निश्चित_spin_locked(&res->spinlock);
	अगर (res->state & DLM_LOCK_RES_MIGRATING) अणु
		__dlm_prपूर्णांक_one_lock_resource(res);
	पूर्ण
	BUG_ON(res->state & DLM_LOCK_RES_MIGRATING);

	atomic_inc(&res->asts_reserved);
पूर्ण

/*
 * used to drop the reserved ast, either because it went unused,
 * or because the ast/bast was actually called.
 *
 * also, अगर there is a pending migration on this lockres,
 * and this was the last pending ast on the lockres,
 * atomically set the MIGRATING flag beक्रमe we drop the lock.
 * this is how we ensure that migration can proceed with no
 * asts in progress.  note that it is ok अगर the state of the
 * queues is such that a lock should be granted in the future
 * or that a bast should be fired, because the new master will
 * shuffle the lists on this lockres as soon as it is migrated.
 */
व्योम dlm_lockres_release_ast(काष्ठा dlm_ctxt *dlm,
			     काष्ठा dlm_lock_resource *res)
अणु
	अगर (!atomic_dec_and_lock(&res->asts_reserved, &res->spinlock))
		वापस;

	अगर (!res->migration_pending) अणु
		spin_unlock(&res->spinlock);
		वापस;
	पूर्ण

	BUG_ON(res->state & DLM_LOCK_RES_MIGRATING);
	res->migration_pending = 0;
	res->state |= DLM_LOCK_RES_MIGRATING;
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);
	wake_up(&dlm->migration_wq);
पूर्ण

व्योम dlm_क्रमce_मुक्त_mles(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक i;
	काष्ठा hlist_head *bucket;
	काष्ठा dlm_master_list_entry *mle;
	काष्ठा hlist_node *पंचांगp;

	/*
	 * We notअगरied all other nodes that we are निकासing the करोमुख्य and
	 * marked the dlm state to DLM_CTXT_LEAVING. If any mles are still
	 * around we क्रमce मुक्त them and wake any processes that are रुकोing
	 * on the mles
	 */
	spin_lock(&dlm->spinlock);
	spin_lock(&dlm->master_lock);

	BUG_ON(dlm->dlm_state != DLM_CTXT_LEAVING);
	BUG_ON((find_next_bit(dlm->करोमुख्य_map, O2NM_MAX_NODES, 0) < O2NM_MAX_NODES));

	क्रम (i = 0; i < DLM_HASH_BUCKETS; i++) अणु
		bucket = dlm_master_hash(dlm, i);
		hlist_क्रम_each_entry_safe(mle, पंचांगp, bucket, master_hash_node) अणु
			अगर (mle->type != DLM_MLE_BLOCK) अणु
				mlog(ML_ERROR, "bad mle: %p\n", mle);
				dlm_prपूर्णांक_one_mle(mle);
			पूर्ण
			atomic_set(&mle->woken, 1);
			wake_up(&mle->wq);

			__dlm_unlink_mle(dlm, mle);
			__dlm_mle_detach_hb_events(dlm, mle);
			__dlm_put_mle(mle);
		पूर्ण
	पूर्ण
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);
पूर्ण
