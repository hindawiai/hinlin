<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmकरोमुख्य.c
 *
 * defines करोमुख्य join / leave apis
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "../cluster/heartbeat.h"
#समावेश "../cluster/nodemanager.h"
#समावेश "../cluster/tcp.h"

#समावेश "dlmapi.h"
#समावेश "dlmcommon.h"
#समावेश "dlmdomain.h"
#समावेश "dlmdebug.h"

#घोषणा MLOG_MASK_PREFIX (ML_DLM|ML_DLM_DOMAIN)
#समावेश "../cluster/masklog.h"

/*
 * ocfs2 node maps are array of दीर्घ पूर्णांक, which limits to send them मुक्तly
 * across the wire due to endianness issues. To workaround this, we convert
 * दीर्घ पूर्णांकs to byte arrays. Following 3 routines are helper functions to
 * set/test/copy bits within those array of bytes
 */
अटल अंतरभूत व्योम byte_set_bit(u8 nr, u8 map[])
अणु
	map[nr >> 3] |= (1UL << (nr & 7));
पूर्ण

अटल अंतरभूत पूर्णांक byte_test_bit(u8 nr, u8 map[])
अणु
	वापस ((1UL << (nr & 7)) & (map[nr >> 3])) != 0;
पूर्ण

अटल अंतरभूत व्योम byte_copymap(u8 dmap[], अचिन्हित दीर्घ smap[],
			अचिन्हित पूर्णांक sz)
अणु
	अचिन्हित पूर्णांक nn;

	अगर (!sz)
		वापस;

	स_रखो(dmap, 0, ((sz + 7) >> 3));
	क्रम (nn = 0 ; nn < sz; nn++)
		अगर (test_bit(nn, smap))
			byte_set_bit(nn, dmap);
पूर्ण

अटल व्योम dlm_मुक्त_pagevec(व्योम **vec, पूर्णांक pages)
अणु
	जबतक (pages--)
		मुक्त_page((अचिन्हित दीर्घ)vec[pages]);
	kमुक्त(vec);
पूर्ण

अटल व्योम **dlm_alloc_pagevec(पूर्णांक pages)
अणु
	व्योम **vec = kदो_स्मृति_array(pages, माप(व्योम *), GFP_KERNEL);
	पूर्णांक i;

	अगर (!vec)
		वापस शून्य;

	क्रम (i = 0; i < pages; i++)
		अगर (!(vec[i] = (व्योम *)__get_मुक्त_page(GFP_KERNEL)))
			जाओ out_मुक्त;

	mlog(0, "Allocated DLM hash pagevec; %d pages (%lu expected), %lu buckets per page\n",
	     pages, (अचिन्हित दीर्घ)DLM_HASH_PAGES,
	     (अचिन्हित दीर्घ)DLM_BUCKETS_PER_PAGE);
	वापस vec;
out_मुक्त:
	dlm_मुक्त_pagevec(vec, i);
	वापस शून्य;
पूर्ण

/*
 *
 * spinlock lock ordering: अगर multiple locks are needed, obey this ordering:
 *    dlm_करोमुख्य_lock
 *    काष्ठा dlm_ctxt->spinlock
 *    काष्ठा dlm_lock_resource->spinlock
 *    काष्ठा dlm_ctxt->master_lock
 *    काष्ठा dlm_ctxt->ast_lock
 *    dlm_master_list_entry->spinlock
 *    dlm_lock->spinlock
 *
 */

DEFINE_SPINLOCK(dlm_करोमुख्य_lock);
LIST_HEAD(dlm_करोमुख्यs);
अटल DECLARE_WAIT_QUEUE_HEAD(dlm_करोमुख्य_events);

/*
 * The supported protocol version क्रम DLM communication.  Running करोमुख्यs
 * will have a negotiated version with the same major number and a minor
 * number equal or smaller.  The dlm_ctxt->dlm_locking_proto field should
 * be used to determine what a running करोमुख्य is actually using.
 *
 * New in version 1.1:
 *	- Message DLM_QUERY_REGION added to support global heartbeat
 *	- Message DLM_QUERY_NODEINFO added to allow online node हटाओs
 * New in version 1.2:
 * 	- Message DLM_BEGIN_EXIT_DOMAIN_MSG added to mark start of निकास करोमुख्य
 * New in version 1.3:
 *	- Message DLM_DEREF_LOCKRES_DONE added to inक्रमm non-master that the
 *	  refmap is cleared
 */
अटल स्थिर काष्ठा dlm_protocol_version dlm_protocol = अणु
	.pv_major = 1,
	.pv_minor = 3,
पूर्ण;

#घोषणा DLM_DOMAIN_BACKOFF_MS 200

अटल पूर्णांक dlm_query_join_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				  व्योम **ret_data);
अटल पूर्णांक dlm_निश्चित_joined_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				     व्योम **ret_data);
अटल पूर्णांक dlm_cancel_join_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				   व्योम **ret_data);
अटल पूर्णांक dlm_query_region_handler(काष्ठा o2net_msg *msg, u32 len,
				    व्योम *data, व्योम **ret_data);
अटल पूर्णांक dlm_निकास_करोमुख्य_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				   व्योम **ret_data);
अटल पूर्णांक dlm_protocol_compare(काष्ठा dlm_protocol_version *existing,
				काष्ठा dlm_protocol_version *request);

अटल व्योम dlm_unरेजिस्टर_करोमुख्य_handlers(काष्ठा dlm_ctxt *dlm);

व्योम __dlm_unhash_lockres(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res)
अणु
	अगर (hlist_unhashed(&res->hash_node))
		वापस;

	mlog(0, "%s: Unhash res %.*s\n", dlm->name, res->lockname.len,
	     res->lockname.name);
	hlist_del_init(&res->hash_node);
	dlm_lockres_put(res);
पूर्ण

व्योम __dlm_insert_lockres(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res)
अणु
	काष्ठा hlist_head *bucket;

	निश्चित_spin_locked(&dlm->spinlock);

	bucket = dlm_lockres_hash(dlm, res->lockname.hash);

	/* get a reference क्रम our hashtable */
	dlm_lockres_get(res);

	hlist_add_head(&res->hash_node, bucket);

	mlog(0, "%s: Hash res %.*s\n", dlm->name, res->lockname.len,
	     res->lockname.name);
पूर्ण

काष्ठा dlm_lock_resource * __dlm_lookup_lockres_full(काष्ठा dlm_ctxt *dlm,
						     स्थिर अक्षर *name,
						     अचिन्हित पूर्णांक len,
						     अचिन्हित पूर्णांक hash)
अणु
	काष्ठा hlist_head *bucket;
	काष्ठा dlm_lock_resource *res;

	mlog(0, "%.*s\n", len, name);

	निश्चित_spin_locked(&dlm->spinlock);

	bucket = dlm_lockres_hash(dlm, hash);

	hlist_क्रम_each_entry(res, bucket, hash_node) अणु
		अगर (res->lockname.name[0] != name[0])
			जारी;
		अगर (unlikely(res->lockname.len != len))
			जारी;
		अगर (स_भेद(res->lockname.name + 1, name + 1, len - 1))
			जारी;
		dlm_lockres_get(res);
		वापस res;
	पूर्ण
	वापस शून्य;
पूर्ण

/* पूर्णांकended to be called by functions which करो not care about lock
 * resources which are being purged (most net _handler functions).
 * this will वापस शून्य क्रम any lock resource which is found but
 * currently in the process of dropping its mastery reference.
 * use __dlm_lookup_lockres_full when you need the lock resource
 * regardless (e.g. dlm_get_lock_resource) */
काष्ठा dlm_lock_resource * __dlm_lookup_lockres(काष्ठा dlm_ctxt *dlm,
						स्थिर अक्षर *name,
						अचिन्हित पूर्णांक len,
						अचिन्हित पूर्णांक hash)
अणु
	काष्ठा dlm_lock_resource *res = शून्य;

	mlog(0, "%.*s\n", len, name);

	निश्चित_spin_locked(&dlm->spinlock);

	res = __dlm_lookup_lockres_full(dlm, name, len, hash);
	अगर (res) अणु
		spin_lock(&res->spinlock);
		अगर (res->state & DLM_LOCK_RES_DROPPING_REF) अणु
			spin_unlock(&res->spinlock);
			dlm_lockres_put(res);
			वापस शून्य;
		पूर्ण
		spin_unlock(&res->spinlock);
	पूर्ण

	वापस res;
पूर्ण

काष्ठा dlm_lock_resource * dlm_lookup_lockres(काष्ठा dlm_ctxt *dlm,
				    स्थिर अक्षर *name,
				    अचिन्हित पूर्णांक len)
अणु
	काष्ठा dlm_lock_resource *res;
	अचिन्हित पूर्णांक hash = dlm_lockid_hash(name, len);

	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres(dlm, name, len, hash);
	spin_unlock(&dlm->spinlock);
	वापस res;
पूर्ण

अटल काष्ठा dlm_ctxt * __dlm_lookup_करोमुख्य_full(स्थिर अक्षर *करोमुख्य, पूर्णांक len)
अणु
	काष्ठा dlm_ctxt *पंचांगp;

	निश्चित_spin_locked(&dlm_करोमुख्य_lock);

	/* पंचांगp->name here is always शून्य terminated,
	 * but करोमुख्य may not be! */
	list_क्रम_each_entry(पंचांगp, &dlm_करोमुख्यs, list) अणु
		अगर (म_माप(पंचांगp->name) == len &&
		    स_भेद(पंचांगp->name, करोमुख्य, len)==0)
			वापस पंचांगp;
	पूर्ण

	वापस शून्य;
पूर्ण

/* For null terminated करोमुख्य strings ONLY */
अटल काष्ठा dlm_ctxt * __dlm_lookup_करोमुख्य(स्थिर अक्षर *करोमुख्य)
अणु
	निश्चित_spin_locked(&dlm_करोमुख्य_lock);

	वापस __dlm_lookup_करोमुख्य_full(करोमुख्य, म_माप(करोमुख्य));
पूर्ण


/* वापसs true on one of two conditions:
 * 1) the करोमुख्य करोes not exist
 * 2) the करोमुख्य exists and it's state is "joined" */
अटल पूर्णांक dlm_रुको_on_करोमुख्य_helper(स्थिर अक्षर *करोमुख्य)
अणु
	पूर्णांक ret = 0;
	काष्ठा dlm_ctxt *पंचांगp = शून्य;

	spin_lock(&dlm_करोमुख्य_lock);

	पंचांगp = __dlm_lookup_करोमुख्य(करोमुख्य);
	अगर (!पंचांगp)
		ret = 1;
	अन्यथा अगर (पंचांगp->dlm_state == DLM_CTXT_JOINED)
		ret = 1;

	spin_unlock(&dlm_करोमुख्य_lock);
	वापस ret;
पूर्ण

अटल व्योम dlm_मुक्त_ctxt_mem(काष्ठा dlm_ctxt *dlm)
अणु
	dlm_destroy_debugfs_subroot(dlm);

	अगर (dlm->lockres_hash)
		dlm_मुक्त_pagevec((व्योम **)dlm->lockres_hash, DLM_HASH_PAGES);

	अगर (dlm->master_hash)
		dlm_मुक्त_pagevec((व्योम **)dlm->master_hash, DLM_HASH_PAGES);

	kमुक्त(dlm->name);
	kमुक्त(dlm);
पूर्ण

/* A little strange - this function will be called जबतक holding
 * dlm_करोमुख्य_lock and is expected to be holding it on the way out. We
 * will however drop and reacquire it multiple बार */
अटल व्योम dlm_ctxt_release(काष्ठा kref *kref)
अणु
	काष्ठा dlm_ctxt *dlm;

	dlm = container_of(kref, काष्ठा dlm_ctxt, dlm_refs);

	BUG_ON(dlm->num_joins);
	BUG_ON(dlm->dlm_state == DLM_CTXT_JOINED);

	/* we may still be in the list अगर we hit an error during join. */
	list_del_init(&dlm->list);

	spin_unlock(&dlm_करोमुख्य_lock);

	mlog(0, "freeing memory from domain %s\n", dlm->name);

	wake_up(&dlm_करोमुख्य_events);

	dlm_मुक्त_ctxt_mem(dlm);

	spin_lock(&dlm_करोमुख्य_lock);
पूर्ण

व्योम dlm_put(काष्ठा dlm_ctxt *dlm)
अणु
	spin_lock(&dlm_करोमुख्य_lock);
	kref_put(&dlm->dlm_refs, dlm_ctxt_release);
	spin_unlock(&dlm_करोमुख्य_lock);
पूर्ण

अटल व्योम __dlm_get(काष्ठा dlm_ctxt *dlm)
अणु
	kref_get(&dlm->dlm_refs);
पूर्ण

/* given a questionable reference to a dlm object, माला_लो a reference अगर
 * it can find it in the list, otherwise वापसs शून्य in which हाल
 * you shouldn't trust your poपूर्णांकer. */
काष्ठा dlm_ctxt *dlm_grab(काष्ठा dlm_ctxt *dlm)
अणु
	काष्ठा dlm_ctxt *target;
	काष्ठा dlm_ctxt *ret = शून्य;

	spin_lock(&dlm_करोमुख्य_lock);

	list_क्रम_each_entry(target, &dlm_करोमुख्यs, list) अणु
		अगर (target == dlm) अणु
			__dlm_get(target);
			ret = target;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&dlm_करोमुख्य_lock);

	वापस ret;
पूर्ण

पूर्णांक dlm_करोमुख्य_fully_joined(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक ret;

	spin_lock(&dlm_करोमुख्य_lock);
	ret = (dlm->dlm_state == DLM_CTXT_JOINED) ||
		(dlm->dlm_state == DLM_CTXT_IN_SHUTDOWN);
	spin_unlock(&dlm_करोमुख्य_lock);

	वापस ret;
पूर्ण

अटल व्योम dlm_destroy_dlm_worker(काष्ठा dlm_ctxt *dlm)
अणु
	अगर (dlm->dlm_worker) अणु
		destroy_workqueue(dlm->dlm_worker);
		dlm->dlm_worker = शून्य;
	पूर्ण
पूर्ण

अटल व्योम dlm_complete_dlm_shutकरोwn(काष्ठा dlm_ctxt *dlm)
अणु
	dlm_unरेजिस्टर_करोमुख्य_handlers(dlm);
	dlm_complete_thपढ़ो(dlm);
	dlm_complete_recovery_thपढ़ो(dlm);
	dlm_destroy_dlm_worker(dlm);

	/* We've left the करोमुख्य. Now we can take ourselves out of the
	 * list and allow the kref stuff to help us मुक्त the
	 * memory. */
	spin_lock(&dlm_करोमुख्य_lock);
	list_del_init(&dlm->list);
	spin_unlock(&dlm_करोमुख्य_lock);

	/* Wake up anyone रुकोing क्रम us to हटाओ this करोमुख्य */
	wake_up(&dlm_करोमुख्य_events);
पूर्ण

अटल पूर्णांक dlm_migrate_all_locks(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक i, num, n, ret = 0;
	काष्ठा dlm_lock_resource *res;
	काष्ठा hlist_node *iter;
	काष्ठा hlist_head *bucket;
	पूर्णांक dropped;

	mlog(0, "Migrating locks from domain %s\n", dlm->name);

	num = 0;
	spin_lock(&dlm->spinlock);
	क्रम (i = 0; i < DLM_HASH_BUCKETS; i++) अणु
reकरो_bucket:
		n = 0;
		bucket = dlm_lockres_hash(dlm, i);
		iter = bucket->first;
		जबतक (iter) अणु
			n++;
			res = hlist_entry(iter, काष्ठा dlm_lock_resource,
					  hash_node);
			dlm_lockres_get(res);
			/* migrate, अगर necessary.  this will drop the dlm
			 * spinlock and retake it अगर it करोes migration. */
			dropped = dlm_empty_lockres(dlm, res);

			spin_lock(&res->spinlock);
			अगर (dropped)
				__dlm_lockres_calc_usage(dlm, res);
			अन्यथा
				iter = res->hash_node.next;
			spin_unlock(&res->spinlock);

			dlm_lockres_put(res);

			अगर (dropped) अणु
				cond_resched_lock(&dlm->spinlock);
				जाओ reकरो_bucket;
			पूर्ण
		पूर्ण
		cond_resched_lock(&dlm->spinlock);
		num += n;
	पूर्ण

	अगर (!num) अणु
		अगर (dlm->reco.state & DLM_RECO_STATE_ACTIVE) अणु
			mlog(0, "%s: perhaps there are more lock resources "
			     "need to be migrated after dlm recovery\n", dlm->name);
			ret = -EAGAIN;
		पूर्ण अन्यथा अणु
			mlog(0, "%s: we won't do dlm recovery after migrating "
			     "all lock resources\n", dlm->name);
			dlm->migrate_करोne = 1;
		पूर्ण
	पूर्ण

	spin_unlock(&dlm->spinlock);
	wake_up(&dlm->dlm_thपढ़ो_wq);

	/* let the dlm thपढ़ो take care of purging, keep scanning until
	 * nothing reमुख्यs in the hash */
	अगर (num) अणु
		mlog(0, "%s: %d lock resources in hash last pass\n",
		     dlm->name, num);
		ret = -EAGAIN;
	पूर्ण
	mlog(0, "DONE Migrating locks from domain %s\n", dlm->name);
	वापस ret;
पूर्ण

अटल पूर्णांक dlm_no_joining_node(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक ret;

	spin_lock(&dlm->spinlock);
	ret = dlm->joining_node == DLM_LOCK_RES_OWNER_UNKNOWN;
	spin_unlock(&dlm->spinlock);

	वापस ret;
पूर्ण

अटल पूर्णांक dlm_begin_निकास_करोमुख्य_handler(काष्ठा o2net_msg *msg, u32 len,
					 व्योम *data, व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	अचिन्हित पूर्णांक node;
	काष्ठा dlm_निकास_करोमुख्य *निकास_msg = (काष्ठा dlm_निकास_करोमुख्य *) msg->buf;

	अगर (!dlm_grab(dlm))
		वापस 0;

	node = निकास_msg->node_idx;
	mlog(0, "%s: Node %u sent a begin exit domain message\n", dlm->name, node);

	spin_lock(&dlm->spinlock);
	set_bit(node, dlm->निकास_करोमुख्य_map);
	spin_unlock(&dlm->spinlock);

	dlm_put(dlm);

	वापस 0;
पूर्ण

अटल व्योम dlm_mark_करोमुख्य_leaving(काष्ठा dlm_ctxt *dlm)
अणु
	/* Yikes, a द्विगुन spinlock! I need करोमुख्य_lock क्रम the dlm
	 * state and the dlm spinlock क्रम join state... Sorry! */
again:
	spin_lock(&dlm_करोमुख्य_lock);
	spin_lock(&dlm->spinlock);

	अगर (dlm->joining_node != DLM_LOCK_RES_OWNER_UNKNOWN) अणु
		mlog(0, "Node %d is joining, we wait on it.\n",
			  dlm->joining_node);
		spin_unlock(&dlm->spinlock);
		spin_unlock(&dlm_करोमुख्य_lock);

		रुको_event(dlm->dlm_join_events, dlm_no_joining_node(dlm));
		जाओ again;
	पूर्ण

	dlm->dlm_state = DLM_CTXT_LEAVING;
	spin_unlock(&dlm->spinlock);
	spin_unlock(&dlm_करोमुख्य_lock);
पूर्ण

अटल व्योम __dlm_prपूर्णांक_nodes(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक node = -1, num = 0;

	निश्चित_spin_locked(&dlm->spinlock);

	prपूर्णांकk("( ");
	जबतक ((node = find_next_bit(dlm->करोमुख्य_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) अणु
		prपूर्णांकk("%d ", node);
		++num;
	पूर्ण
	prपूर्णांकk(") %u nodes\n", num);
पूर्ण

अटल पूर्णांक dlm_निकास_करोमुख्य_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				   व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	अचिन्हित पूर्णांक node;
	काष्ठा dlm_निकास_करोमुख्य *निकास_msg = (काष्ठा dlm_निकास_करोमुख्य *) msg->buf;

	mlog(0, "%p %u %p", msg, len, data);

	अगर (!dlm_grab(dlm))
		वापस 0;

	node = निकास_msg->node_idx;

	spin_lock(&dlm->spinlock);
	clear_bit(node, dlm->करोमुख्य_map);
	clear_bit(node, dlm->निकास_करोमुख्य_map);
	prपूर्णांकk(KERN_NOTICE "o2dlm: Node %u leaves domain %s ", node, dlm->name);
	__dlm_prपूर्णांक_nodes(dlm);

	/* notअगरy anything attached to the heartbeat events */
	dlm_hb_event_notअगरy_attached(dlm, node, 0);

	spin_unlock(&dlm->spinlock);

	dlm_put(dlm);

	वापस 0;
पूर्ण

अटल पूर्णांक dlm_send_one_करोमुख्य_निकास(काष्ठा dlm_ctxt *dlm, u32 msg_type,
				    अचिन्हित पूर्णांक node)
अणु
	पूर्णांक status;
	काष्ठा dlm_निकास_करोमुख्य leave_msg;

	mlog(0, "%s: Sending domain exit message %u to node %u\n", dlm->name,
	     msg_type, node);

	स_रखो(&leave_msg, 0, माप(leave_msg));
	leave_msg.node_idx = dlm->node_num;

	status = o2net_send_message(msg_type, dlm->key, &leave_msg,
				    माप(leave_msg), node, शून्य);
	अगर (status < 0)
		mlog(ML_ERROR, "Error %d sending domain exit message %u "
		     "to node %u on domain %s\n", status, msg_type, node,
		     dlm->name);

	वापस status;
पूर्ण

अटल व्योम dlm_begin_निकास_करोमुख्य(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक node = -1;

	/* Support क्रम begin निकास करोमुख्य was added in 1.2 */
	अगर (dlm->dlm_locking_proto.pv_major == 1 &&
	    dlm->dlm_locking_proto.pv_minor < 2)
		वापस;

	/*
	 * Unlike DLM_EXIT_DOMAIN_MSG, DLM_BEGIN_EXIT_DOMAIN_MSG is purely
	 * inक्रमmational. Meaning अगर a node करोes not receive the message,
	 * so be it.
	 */
	spin_lock(&dlm->spinlock);
	जबतक (1) अणु
		node = find_next_bit(dlm->करोमुख्य_map, O2NM_MAX_NODES, node + 1);
		अगर (node >= O2NM_MAX_NODES)
			अवरोध;
		अगर (node == dlm->node_num)
			जारी;

		spin_unlock(&dlm->spinlock);
		dlm_send_one_करोमुख्य_निकास(dlm, DLM_BEGIN_EXIT_DOMAIN_MSG, node);
		spin_lock(&dlm->spinlock);
	पूर्ण
	spin_unlock(&dlm->spinlock);
पूर्ण

अटल व्योम dlm_leave_करोमुख्य(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक node, clear_node, status;

	/* At this poपूर्णांक we've migrated away all our locks and won't
	 * accept mastership of new ones. The dlm is responsible क्रम
	 * almost nothing now. We make sure not to confuse any joining
	 * nodes and then commence shutकरोwn procedure. */

	spin_lock(&dlm->spinlock);
	/* Clear ourselves from the करोमुख्य map */
	clear_bit(dlm->node_num, dlm->करोमुख्य_map);
	जबतक ((node = find_next_bit(dlm->करोमुख्य_map, O2NM_MAX_NODES,
				     0)) < O2NM_MAX_NODES) अणु
		/* Drop the dlm spinlock. This is safe wrt the करोमुख्य_map.
		 * -nodes cannot be added now as the
		 *   query_join_handlers knows to respond with OK_NO_MAP
		 * -we catch the right network errors अगर a node is
		 *   हटाओd from the map जबतक we're sending him the
		 *   निकास message. */
		spin_unlock(&dlm->spinlock);

		clear_node = 1;

		status = dlm_send_one_करोमुख्य_निकास(dlm, DLM_EXIT_DOMAIN_MSG,
						  node);
		अगर (status < 0 &&
		    status != -ENOPROTOOPT &&
		    status != -ENOTCONN) अणु
			mlog(ML_NOTICE, "Error %d sending domain exit message "
			     "to node %d\n", status, node);

			/* Not sure what to करो here but lets sleep क्रम
			 * a bit in हाल this was a transient
			 * error... */
			msleep(DLM_DOMAIN_BACKOFF_MS);
			clear_node = 0;
		पूर्ण

		spin_lock(&dlm->spinlock);
		/* If we're not clearing the node bit then we पूर्णांकend
		 * to loop back around to try again. */
		अगर (clear_node)
			clear_bit(node, dlm->करोमुख्य_map);
	पूर्ण
	spin_unlock(&dlm->spinlock);
पूर्ण

व्योम dlm_unरेजिस्टर_करोमुख्य(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक leave = 0;
	काष्ठा dlm_lock_resource *res;

	spin_lock(&dlm_करोमुख्य_lock);
	BUG_ON(dlm->dlm_state != DLM_CTXT_JOINED);
	BUG_ON(!dlm->num_joins);

	dlm->num_joins--;
	अगर (!dlm->num_joins) अणु
		/* We mark it "in shutdown" now so new रेजिस्टर
		 * requests रुको until we've completely left the
		 * करोमुख्य. Don't use DLM_CTXT_LEAVING yet as we still
		 * want new करोमुख्य joins to communicate with us at
		 * least until we've completed migration of our
		 * resources. */
		dlm->dlm_state = DLM_CTXT_IN_SHUTDOWN;
		leave = 1;
	पूर्ण
	spin_unlock(&dlm_करोमुख्य_lock);

	अगर (leave) अणु
		mlog(0, "shutting down domain %s\n", dlm->name);
		dlm_begin_निकास_करोमुख्य(dlm);

		/* We changed dlm state, notअगरy the thपढ़ो */
		dlm_kick_thपढ़ो(dlm, शून्य);

		जबतक (dlm_migrate_all_locks(dlm)) अणु
			/* Give dlm_thपढ़ो समय to purge the lockres' */
			msleep(500);
			mlog(0, "%s: more migration to do\n", dlm->name);
		पूर्ण

		/* This list should be empty. If not, prपूर्णांक reमुख्यing lockres */
		अगर (!list_empty(&dlm->tracking_list)) अणु
			mlog(ML_ERROR, "Following lockres' are still on the "
			     "tracking list:\n");
			list_क्रम_each_entry(res, &dlm->tracking_list, tracking)
				dlm_prपूर्णांक_one_lock_resource(res);
		पूर्ण

		dlm_mark_करोमुख्य_leaving(dlm);
		dlm_leave_करोमुख्य(dlm);
		prपूर्णांकk(KERN_NOTICE "o2dlm: Leaving domain %s\n", dlm->name);
		dlm_क्रमce_मुक्त_mles(dlm);
		dlm_complete_dlm_shutकरोwn(dlm);
	पूर्ण
	dlm_put(dlm);
पूर्ण
EXPORT_SYMBOL_GPL(dlm_unरेजिस्टर_करोमुख्य);

अटल पूर्णांक dlm_query_join_proto_check(अक्षर *proto_type, पूर्णांक node,
				      काष्ठा dlm_protocol_version *ours,
				      काष्ठा dlm_protocol_version *request)
अणु
	पूर्णांक rc;
	काष्ठा dlm_protocol_version proto = *request;

	अगर (!dlm_protocol_compare(ours, &proto)) अणु
		mlog(0,
		     "node %u wanted to join with %s locking protocol "
		     "%u.%u, we respond with %u.%u\n",
		     node, proto_type,
		     request->pv_major,
		     request->pv_minor,
		     proto.pv_major, proto.pv_minor);
		request->pv_minor = proto.pv_minor;
		rc = 0;
	पूर्ण अन्यथा अणु
		mlog(ML_NOTICE,
		     "Node %u wanted to join with %s locking "
		     "protocol %u.%u, but we have %u.%u, disallowing\n",
		     node, proto_type,
		     request->pv_major,
		     request->pv_minor,
		     ours->pv_major,
		     ours->pv_minor);
		rc = 1;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * काष्ठा dlm_query_join_packet is made up of four one-byte fields.  They
 * are effectively in big-endian order alपढ़ोy.  However, little-endian
 * machines swap them beक्रमe putting the packet on the wire (because
 * query_join's response is a status, and that status is treated as a u32
 * on the wire).  Thus, a big-endian and little-endian machines will treat
 * this काष्ठाure dअगरferently.
 *
 * The solution is to have little-endian machines swap the काष्ठाure when
 * converting from the काष्ठाure to the u32 representation.  This will
 * result in the काष्ठाure having the correct क्रमmat on the wire no matter
 * the host endian क्रमmat.
 */
अटल व्योम dlm_query_join_packet_to_wire(काष्ठा dlm_query_join_packet *packet,
					  u32 *wire)
अणु
	जोड़ dlm_query_join_response response;

	response.packet = *packet;
	*wire = be32_to_cpu(response.पूर्णांकval);
पूर्ण

अटल व्योम dlm_query_join_wire_to_packet(u32 wire,
					  काष्ठा dlm_query_join_packet *packet)
अणु
	जोड़ dlm_query_join_response response;

	response.पूर्णांकval = cpu_to_be32(wire);
	*packet = response.packet;
पूर्ण

अटल पूर्णांक dlm_query_join_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				  व्योम **ret_data)
अणु
	काष्ठा dlm_query_join_request *query;
	काष्ठा dlm_query_join_packet packet = अणु
		.code = JOIN_DISALLOW,
	पूर्ण;
	काष्ठा dlm_ctxt *dlm = शून्य;
	u32 response;
	u8 nodक्रमागत;

	query = (काष्ठा dlm_query_join_request *) msg->buf;

	mlog(0, "node %u wants to join domain %s\n", query->node_idx,
		  query->करोमुख्य);

	/*
	 * If heartbeat करोesn't consider the node live, tell it
	 * to back off and try again.  This gives heartbeat a chance
	 * to catch up.
	 */
	अगर (!o2hb_check_node_heartbeating_no_sem(query->node_idx)) अणु
		mlog(0, "node %u is not in our live map yet\n",
		     query->node_idx);

		packet.code = JOIN_DISALLOW;
		जाओ respond;
	पूर्ण

	packet.code = JOIN_OK_NO_MAP;

	spin_lock(&dlm_करोमुख्य_lock);
	dlm = __dlm_lookup_करोमुख्य_full(query->करोमुख्य, query->name_len);
	अगर (!dlm)
		जाओ unlock_respond;

	/*
	 * There is a small winकरोw where the joining node may not see the
	 * node(s) that just left but still part of the cluster. DISALLOW
	 * join request अगर joining node has dअगरferent node map.
	 */
	nodक्रमागत=0;
	जबतक (nodक्रमागत < O2NM_MAX_NODES) अणु
		अगर (test_bit(nodक्रमागत, dlm->करोमुख्य_map)) अणु
			अगर (!byte_test_bit(nodक्रमागत, query->node_map)) अणु
				mlog(0, "disallow join as node %u does not "
				     "have node %u in its nodemap\n",
				     query->node_idx, nodक्रमागत);
				packet.code = JOIN_DISALLOW;
				जाओ unlock_respond;
			पूर्ण
		पूर्ण
		nodक्रमागत++;
	पूर्ण

	/* Once the dlm ctxt is marked as leaving then we करोn't want
	 * to be put in someone's करोमुख्य map.
	 * Also, explicitly disallow joining at certain troublesome
	 * बार (ie. during recovery). */
	अगर (dlm->dlm_state != DLM_CTXT_LEAVING) अणु
		पूर्णांक bit = query->node_idx;
		spin_lock(&dlm->spinlock);

		अगर (dlm->dlm_state == DLM_CTXT_NEW &&
		    dlm->joining_node == DLM_LOCK_RES_OWNER_UNKNOWN) अणु
			/*If this is a bअक्रम new context and we
			 * haven't started our join process yet, then
			 * the other node won the race. */
			packet.code = JOIN_OK_NO_MAP;
		पूर्ण अन्यथा अगर (dlm->joining_node != DLM_LOCK_RES_OWNER_UNKNOWN) अणु
			/* Disallow parallel joins. */
			packet.code = JOIN_DISALLOW;
		पूर्ण अन्यथा अगर (dlm->reco.state & DLM_RECO_STATE_ACTIVE) अणु
			mlog(0, "node %u trying to join, but recovery "
			     "is ongoing.\n", bit);
			packet.code = JOIN_DISALLOW;
		पूर्ण अन्यथा अगर (test_bit(bit, dlm->recovery_map)) अणु
			mlog(0, "node %u trying to join, but it "
			     "still needs recovery.\n", bit);
			packet.code = JOIN_DISALLOW;
		पूर्ण अन्यथा अगर (test_bit(bit, dlm->करोमुख्य_map)) अणु
			mlog(0, "node %u trying to join, but it "
			     "is still in the domain! needs recovery?\n",
			     bit);
			packet.code = JOIN_DISALLOW;
		पूर्ण अन्यथा अणु
			/* Alright we're fully a part of this करोमुख्य
			 * so we keep some state as to who's joining
			 * and indicate to him that needs to be fixed
			 * up. */

			/* Make sure we speak compatible locking protocols.  */
			अगर (dlm_query_join_proto_check("DLM", bit,
						       &dlm->dlm_locking_proto,
						       &query->dlm_proto)) अणु
				packet.code = JOIN_PROTOCOL_MISMATCH;
			पूर्ण अन्यथा अगर (dlm_query_join_proto_check("fs", bit,
							      &dlm->fs_locking_proto,
							      &query->fs_proto)) अणु
				packet.code = JOIN_PROTOCOL_MISMATCH;
			पूर्ण अन्यथा अणु
				packet.dlm_minor = query->dlm_proto.pv_minor;
				packet.fs_minor = query->fs_proto.pv_minor;
				packet.code = JOIN_OK;
				__dlm_set_joining_node(dlm, query->node_idx);
			पूर्ण
		पूर्ण

		spin_unlock(&dlm->spinlock);
	पूर्ण
unlock_respond:
	spin_unlock(&dlm_करोमुख्य_lock);

respond:
	mlog(0, "We respond with %u\n", packet.code);

	dlm_query_join_packet_to_wire(&packet, &response);
	वापस response;
पूर्ण

अटल पूर्णांक dlm_निश्चित_joined_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				     व्योम **ret_data)
अणु
	काष्ठा dlm_निश्चित_joined *निश्चित;
	काष्ठा dlm_ctxt *dlm = शून्य;

	निश्चित = (काष्ठा dlm_निश्चित_joined *) msg->buf;

	mlog(0, "node %u asserts join on domain %s\n", निश्चित->node_idx,
		  निश्चित->करोमुख्य);

	spin_lock(&dlm_करोमुख्य_lock);
	dlm = __dlm_lookup_करोमुख्य_full(निश्चित->करोमुख्य, निश्चित->name_len);
	/* XXX should we consider no dlm ctxt an error? */
	अगर (dlm) अणु
		spin_lock(&dlm->spinlock);

		/* Alright, this node has officially joined our
		 * करोमुख्य. Set him in the map and clean up our
		 * leftover join state. */
		BUG_ON(dlm->joining_node != निश्चित->node_idx);

		अगर (dlm->reco.state & DLM_RECO_STATE_ACTIVE) अणु
			mlog(0, "dlm recovery is ongoing, disallow join\n");
			spin_unlock(&dlm->spinlock);
			spin_unlock(&dlm_करोमुख्य_lock);
			वापस -EAGAIN;
		पूर्ण

		set_bit(निश्चित->node_idx, dlm->करोमुख्य_map);
		clear_bit(निश्चित->node_idx, dlm->निकास_करोमुख्य_map);
		__dlm_set_joining_node(dlm, DLM_LOCK_RES_OWNER_UNKNOWN);

		prपूर्णांकk(KERN_NOTICE "o2dlm: Node %u joins domain %s ",
		       निश्चित->node_idx, dlm->name);
		__dlm_prपूर्णांक_nodes(dlm);

		/* notअगरy anything attached to the heartbeat events */
		dlm_hb_event_notअगरy_attached(dlm, निश्चित->node_idx, 1);

		spin_unlock(&dlm->spinlock);
	पूर्ण
	spin_unlock(&dlm_करोमुख्य_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक dlm_match_regions(काष्ठा dlm_ctxt *dlm,
			     काष्ठा dlm_query_region *qr,
			     अक्षर *local, पूर्णांक locallen)
अणु
	अक्षर *remote = qr->qr_regions;
	अक्षर *l, *r;
	पूर्णांक localnr, i, j, foundit;
	पूर्णांक status = 0;

	अगर (!o2hb_global_heartbeat_active()) अणु
		अगर (qr->qr_numregions) अणु
			mlog(ML_ERROR, "Domain %s: Joining node %d has global "
			     "heartbeat enabled but local node %d does not\n",
			     qr->qr_करोमुख्य, qr->qr_node, dlm->node_num);
			status = -EINVAL;
		पूर्ण
		जाओ bail;
	पूर्ण

	अगर (o2hb_global_heartbeat_active() && !qr->qr_numregions) अणु
		mlog(ML_ERROR, "Domain %s: Local node %d has global "
		     "heartbeat enabled but joining node %d does not\n",
		     qr->qr_करोमुख्य, dlm->node_num, qr->qr_node);
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	r = remote;
	क्रम (i = 0; i < qr->qr_numregions; ++i) अणु
		mlog(0, "Region %.*s\n", O2HB_MAX_REGION_NAME_LEN, r);
		r += O2HB_MAX_REGION_NAME_LEN;
	पूर्ण

	localnr = min(O2NM_MAX_REGIONS, locallen/O2HB_MAX_REGION_NAME_LEN);
	localnr = o2hb_get_all_regions(local, (u8)localnr);

	/* compare local regions with remote */
	l = local;
	क्रम (i = 0; i < localnr; ++i) अणु
		foundit = 0;
		r = remote;
		क्रम (j = 0; j <= qr->qr_numregions; ++j) अणु
			अगर (!स_भेद(l, r, O2HB_MAX_REGION_NAME_LEN)) अणु
				foundit = 1;
				अवरोध;
			पूर्ण
			r += O2HB_MAX_REGION_NAME_LEN;
		पूर्ण
		अगर (!foundit) अणु
			status = -EINVAL;
			mlog(ML_ERROR, "Domain %s: Region '%.*s' registered "
			     "in local node %d but not in joining node %d\n",
			     qr->qr_करोमुख्य, O2HB_MAX_REGION_NAME_LEN, l,
			     dlm->node_num, qr->qr_node);
			जाओ bail;
		पूर्ण
		l += O2HB_MAX_REGION_NAME_LEN;
	पूर्ण

	/* compare remote with local regions */
	r = remote;
	क्रम (i = 0; i < qr->qr_numregions; ++i) अणु
		foundit = 0;
		l = local;
		क्रम (j = 0; j < localnr; ++j) अणु
			अगर (!स_भेद(r, l, O2HB_MAX_REGION_NAME_LEN)) अणु
				foundit = 1;
				अवरोध;
			पूर्ण
			l += O2HB_MAX_REGION_NAME_LEN;
		पूर्ण
		अगर (!foundit) अणु
			status = -EINVAL;
			mlog(ML_ERROR, "Domain %s: Region '%.*s' registered "
			     "in joining node %d but not in local node %d\n",
			     qr->qr_करोमुख्य, O2HB_MAX_REGION_NAME_LEN, r,
			     qr->qr_node, dlm->node_num);
			जाओ bail;
		पूर्ण
		r += O2HB_MAX_REGION_NAME_LEN;
	पूर्ण

bail:
	वापस status;
पूर्ण

अटल पूर्णांक dlm_send_regions(काष्ठा dlm_ctxt *dlm, अचिन्हित दीर्घ *node_map)
अणु
	काष्ठा dlm_query_region *qr = शून्य;
	पूर्णांक status, ret = 0, i;
	अक्षर *p;

	अगर (find_next_bit(node_map, O2NM_MAX_NODES, 0) >= O2NM_MAX_NODES)
		जाओ bail;

	qr = kzalloc(माप(काष्ठा dlm_query_region), GFP_KERNEL);
	अगर (!qr) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ bail;
	पूर्ण

	qr->qr_node = dlm->node_num;
	qr->qr_namelen = म_माप(dlm->name);
	स_नकल(qr->qr_करोमुख्य, dlm->name, qr->qr_namelen);
	/* अगर local hb, the numregions will be zero */
	अगर (o2hb_global_heartbeat_active())
		qr->qr_numregions = o2hb_get_all_regions(qr->qr_regions,
							 O2NM_MAX_REGIONS);

	p = qr->qr_regions;
	क्रम (i = 0; i < qr->qr_numregions; ++i, p += O2HB_MAX_REGION_NAME_LEN)
		mlog(0, "Region %.*s\n", O2HB_MAX_REGION_NAME_LEN, p);

	i = -1;
	जबतक ((i = find_next_bit(node_map, O2NM_MAX_NODES,
				  i + 1)) < O2NM_MAX_NODES) अणु
		अगर (i == dlm->node_num)
			जारी;

		mlog(0, "Sending regions to node %d\n", i);

		ret = o2net_send_message(DLM_QUERY_REGION, DLM_MOD_KEY, qr,
					 माप(काष्ठा dlm_query_region),
					 i, &status);
		अगर (ret >= 0)
			ret = status;
		अगर (ret) अणु
			mlog(ML_ERROR, "Region mismatch %d, node %d\n",
			     ret, i);
			अवरोध;
		पूर्ण
	पूर्ण

bail:
	kमुक्त(qr);
	वापस ret;
पूर्ण

अटल पूर्णांक dlm_query_region_handler(काष्ठा o2net_msg *msg, u32 len,
				    व्योम *data, व्योम **ret_data)
अणु
	काष्ठा dlm_query_region *qr;
	काष्ठा dlm_ctxt *dlm = शून्य;
	अक्षर *local = शून्य;
	पूर्णांक status = 0;

	qr = (काष्ठा dlm_query_region *) msg->buf;

	mlog(0, "Node %u queries hb regions on domain %s\n", qr->qr_node,
	     qr->qr_करोमुख्य);

	/* buffer used in dlm_mast_regions() */
	local = kदो_स्मृति(माप(qr->qr_regions), GFP_KERNEL);
	अगर (!local)
		वापस -ENOMEM;

	status = -EINVAL;

	spin_lock(&dlm_करोमुख्य_lock);
	dlm = __dlm_lookup_करोमुख्य_full(qr->qr_करोमुख्य, qr->qr_namelen);
	अगर (!dlm) अणु
		mlog(ML_ERROR, "Node %d queried hb regions on domain %s "
		     "before join domain\n", qr->qr_node, qr->qr_करोमुख्य);
		जाओ out_करोमुख्य_lock;
	पूर्ण

	spin_lock(&dlm->spinlock);
	अगर (dlm->joining_node != qr->qr_node) अणु
		mlog(ML_ERROR, "Node %d queried hb regions on domain %s "
		     "but joining node is %d\n", qr->qr_node, qr->qr_करोमुख्य,
		     dlm->joining_node);
		जाओ out_dlm_lock;
	पूर्ण

	/* Support क्रम global heartbeat was added in 1.1 */
	अगर (dlm->dlm_locking_proto.pv_major == 1 &&
	    dlm->dlm_locking_proto.pv_minor == 0) अणु
		mlog(ML_ERROR, "Node %d queried hb regions on domain %s "
		     "but active dlm protocol is %d.%d\n", qr->qr_node,
		     qr->qr_करोमुख्य, dlm->dlm_locking_proto.pv_major,
		     dlm->dlm_locking_proto.pv_minor);
		जाओ out_dlm_lock;
	पूर्ण

	status = dlm_match_regions(dlm, qr, local, माप(qr->qr_regions));

out_dlm_lock:
	spin_unlock(&dlm->spinlock);

out_करोमुख्य_lock:
	spin_unlock(&dlm_करोमुख्य_lock);

	kमुक्त(local);

	वापस status;
पूर्ण

अटल पूर्णांक dlm_match_nodes(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_query_nodeinfo *qn)
अणु
	काष्ठा o2nm_node *local;
	काष्ठा dlm_node_info *remote;
	पूर्णांक i, j;
	पूर्णांक status = 0;

	क्रम (j = 0; j < qn->qn_numnodes; ++j)
		mlog(0, "Node %3d, %pI4:%u\n", qn->qn_nodes[j].ni_nodक्रमागत,
		     &(qn->qn_nodes[j].ni_ipv4_address),
		     ntohs(qn->qn_nodes[j].ni_ipv4_port));

	क्रम (i = 0; i < O2NM_MAX_NODES && !status; ++i) अणु
		local = o2nm_get_node_by_num(i);
		remote = शून्य;
		क्रम (j = 0; j < qn->qn_numnodes; ++j) अणु
			अगर (qn->qn_nodes[j].ni_nodक्रमागत == i) अणु
				remote = &(qn->qn_nodes[j]);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!local && !remote)
			जारी;

		अगर ((local && !remote) || (!local && remote))
			status = -EINVAL;

		अगर (!status &&
		    ((remote->ni_nodक्रमागत != local->nd_num) ||
		     (remote->ni_ipv4_port != local->nd_ipv4_port) ||
		     (remote->ni_ipv4_address != local->nd_ipv4_address)))
			status = -EINVAL;

		अगर (status) अणु
			अगर (remote && !local)
				mlog(ML_ERROR, "Domain %s: Node %d (%pI4:%u) "
				     "registered in joining node %d but not in "
				     "local node %d\n", qn->qn_करोमुख्य,
				     remote->ni_nodक्रमागत,
				     &(remote->ni_ipv4_address),
				     ntohs(remote->ni_ipv4_port),
				     qn->qn_nodक्रमागत, dlm->node_num);
			अगर (local && !remote)
				mlog(ML_ERROR, "Domain %s: Node %d (%pI4:%u) "
				     "registered in local node %d but not in "
				     "joining node %d\n", qn->qn_करोमुख्य,
				     local->nd_num, &(local->nd_ipv4_address),
				     ntohs(local->nd_ipv4_port),
				     dlm->node_num, qn->qn_nodक्रमागत);
			BUG_ON((!local && !remote));
		पूर्ण

		अगर (local)
			o2nm_node_put(local);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक dlm_send_nodeinfo(काष्ठा dlm_ctxt *dlm, अचिन्हित दीर्घ *node_map)
अणु
	काष्ठा dlm_query_nodeinfo *qn = शून्य;
	काष्ठा o2nm_node *node;
	पूर्णांक ret = 0, status, count, i;

	अगर (find_next_bit(node_map, O2NM_MAX_NODES, 0) >= O2NM_MAX_NODES)
		जाओ bail;

	qn = kzalloc(माप(काष्ठा dlm_query_nodeinfo), GFP_KERNEL);
	अगर (!qn) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ bail;
	पूर्ण

	क्रम (i = 0, count = 0; i < O2NM_MAX_NODES; ++i) अणु
		node = o2nm_get_node_by_num(i);
		अगर (!node)
			जारी;
		qn->qn_nodes[count].ni_nodक्रमागत = node->nd_num;
		qn->qn_nodes[count].ni_ipv4_port = node->nd_ipv4_port;
		qn->qn_nodes[count].ni_ipv4_address = node->nd_ipv4_address;
		mlog(0, "Node %3d, %pI4:%u\n", node->nd_num,
		     &(node->nd_ipv4_address), ntohs(node->nd_ipv4_port));
		++count;
		o2nm_node_put(node);
	पूर्ण

	qn->qn_nodक्रमागत = dlm->node_num;
	qn->qn_numnodes = count;
	qn->qn_namelen = म_माप(dlm->name);
	स_नकल(qn->qn_करोमुख्य, dlm->name, qn->qn_namelen);

	i = -1;
	जबतक ((i = find_next_bit(node_map, O2NM_MAX_NODES,
				  i + 1)) < O2NM_MAX_NODES) अणु
		अगर (i == dlm->node_num)
			जारी;

		mlog(0, "Sending nodeinfo to node %d\n", i);

		ret = o2net_send_message(DLM_QUERY_NODEINFO, DLM_MOD_KEY,
					 qn, माप(काष्ठा dlm_query_nodeinfo),
					 i, &status);
		अगर (ret >= 0)
			ret = status;
		अगर (ret) अणु
			mlog(ML_ERROR, "node mismatch %d, node %d\n", ret, i);
			अवरोध;
		पूर्ण
	पूर्ण

bail:
	kमुक्त(qn);
	वापस ret;
पूर्ण

अटल पूर्णांक dlm_query_nodeinfo_handler(काष्ठा o2net_msg *msg, u32 len,
				      व्योम *data, व्योम **ret_data)
अणु
	काष्ठा dlm_query_nodeinfo *qn;
	काष्ठा dlm_ctxt *dlm = शून्य;
	पूर्णांक locked = 0, status = -EINVAL;

	qn = (काष्ठा dlm_query_nodeinfo *) msg->buf;

	mlog(0, "Node %u queries nodes on domain %s\n", qn->qn_nodक्रमागत,
	     qn->qn_करोमुख्य);

	spin_lock(&dlm_करोमुख्य_lock);
	dlm = __dlm_lookup_करोमुख्य_full(qn->qn_करोमुख्य, qn->qn_namelen);
	अगर (!dlm) अणु
		mlog(ML_ERROR, "Node %d queried nodes on domain %s before "
		     "join domain\n", qn->qn_nodक्रमागत, qn->qn_करोमुख्य);
		जाओ bail;
	पूर्ण

	spin_lock(&dlm->spinlock);
	locked = 1;
	अगर (dlm->joining_node != qn->qn_nodक्रमागत) अणु
		mlog(ML_ERROR, "Node %d queried nodes on domain %s but "
		     "joining node is %d\n", qn->qn_nodक्रमागत, qn->qn_करोमुख्य,
		     dlm->joining_node);
		जाओ bail;
	पूर्ण

	/* Support क्रम node query was added in 1.1 */
	अगर (dlm->dlm_locking_proto.pv_major == 1 &&
	    dlm->dlm_locking_proto.pv_minor == 0) अणु
		mlog(ML_ERROR, "Node %d queried nodes on domain %s "
		     "but active dlm protocol is %d.%d\n", qn->qn_nodक्रमागत,
		     qn->qn_करोमुख्य, dlm->dlm_locking_proto.pv_major,
		     dlm->dlm_locking_proto.pv_minor);
		जाओ bail;
	पूर्ण

	status = dlm_match_nodes(dlm, qn);

bail:
	अगर (locked)
		spin_unlock(&dlm->spinlock);
	spin_unlock(&dlm_करोमुख्य_lock);

	वापस status;
पूर्ण

अटल पूर्णांक dlm_cancel_join_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				   व्योम **ret_data)
अणु
	काष्ठा dlm_cancel_join *cancel;
	काष्ठा dlm_ctxt *dlm = शून्य;

	cancel = (काष्ठा dlm_cancel_join *) msg->buf;

	mlog(0, "node %u cancels join on domain %s\n", cancel->node_idx,
		  cancel->करोमुख्य);

	spin_lock(&dlm_करोमुख्य_lock);
	dlm = __dlm_lookup_करोमुख्य_full(cancel->करोमुख्य, cancel->name_len);

	अगर (dlm) अणु
		spin_lock(&dlm->spinlock);

		/* Yikes, this guy wants to cancel his join. No
		 * problem, we simply cleanup our join state. */
		BUG_ON(dlm->joining_node != cancel->node_idx);
		__dlm_set_joining_node(dlm, DLM_LOCK_RES_OWNER_UNKNOWN);

		spin_unlock(&dlm->spinlock);
	पूर्ण
	spin_unlock(&dlm_करोमुख्य_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक dlm_send_one_join_cancel(काष्ठा dlm_ctxt *dlm,
				    अचिन्हित पूर्णांक node)
अणु
	पूर्णांक status;
	काष्ठा dlm_cancel_join cancel_msg;

	स_रखो(&cancel_msg, 0, माप(cancel_msg));
	cancel_msg.node_idx = dlm->node_num;
	cancel_msg.name_len = म_माप(dlm->name);
	स_नकल(cancel_msg.करोमुख्य, dlm->name, cancel_msg.name_len);

	status = o2net_send_message(DLM_CANCEL_JOIN_MSG, DLM_MOD_KEY,
				    &cancel_msg, माप(cancel_msg), node,
				    शून्य);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "Error %d when sending message %u (key 0x%x) to "
		     "node %u\n", status, DLM_CANCEL_JOIN_MSG, DLM_MOD_KEY,
		     node);
		जाओ bail;
	पूर्ण

bail:
	वापस status;
पूर्ण

/* map_size should be in bytes. */
अटल पूर्णांक dlm_send_join_cancels(काष्ठा dlm_ctxt *dlm,
				 अचिन्हित दीर्घ *node_map,
				 अचिन्हित पूर्णांक map_size)
अणु
	पूर्णांक status, पंचांगpstat;
	पूर्णांक node;

	अगर (map_size != (BITS_TO_LONGS(O2NM_MAX_NODES) *
			 माप(अचिन्हित दीर्घ))) अणु
		mlog(ML_ERROR,
		     "map_size %u != BITS_TO_LONGS(O2NM_MAX_NODES) %u\n",
		     map_size, (अचिन्हित)BITS_TO_LONGS(O2NM_MAX_NODES));
		वापस -EINVAL;
	पूर्ण

	status = 0;
	node = -1;
	जबतक ((node = find_next_bit(node_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) अणु
		अगर (node == dlm->node_num)
			जारी;

		पंचांगpstat = dlm_send_one_join_cancel(dlm, node);
		अगर (पंचांगpstat) अणु
			mlog(ML_ERROR, "Error return %d cancelling join on "
			     "node %d\n", पंचांगpstat, node);
			अगर (!status)
				status = पंचांगpstat;
		पूर्ण
	पूर्ण

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल पूर्णांक dlm_request_join(काष्ठा dlm_ctxt *dlm,
			    पूर्णांक node,
			    क्रमागत dlm_query_join_response_code *response)
अणु
	पूर्णांक status;
	काष्ठा dlm_query_join_request join_msg;
	काष्ठा dlm_query_join_packet packet;
	u32 join_resp;

	mlog(0, "querying node %d\n", node);

	स_रखो(&join_msg, 0, माप(join_msg));
	join_msg.node_idx = dlm->node_num;
	join_msg.name_len = म_माप(dlm->name);
	स_नकल(join_msg.करोमुख्य, dlm->name, join_msg.name_len);
	join_msg.dlm_proto = dlm->dlm_locking_proto;
	join_msg.fs_proto = dlm->fs_locking_proto;

	/* copy live node map to join message */
	byte_copymap(join_msg.node_map, dlm->live_nodes_map, O2NM_MAX_NODES);

	status = o2net_send_message(DLM_QUERY_JOIN_MSG, DLM_MOD_KEY, &join_msg,
				    माप(join_msg), node, &join_resp);
	अगर (status < 0 && status != -ENOPROTOOPT) अणु
		mlog(ML_ERROR, "Error %d when sending message %u (key 0x%x) to "
		     "node %u\n", status, DLM_QUERY_JOIN_MSG, DLM_MOD_KEY,
		     node);
		जाओ bail;
	पूर्ण
	dlm_query_join_wire_to_packet(join_resp, &packet);

	/* -ENOPROTOOPT from the net code means the other side isn't
	    listening क्रम our message type -- that's fine, it means
	    his dlm isn't up, so we can consider him a 'yes' but not
	    joined पूर्णांकo the करोमुख्य.  */
	अगर (status == -ENOPROTOOPT) अणु
		status = 0;
		*response = JOIN_OK_NO_MAP;
	पूर्ण अन्यथा अणु
		*response = packet.code;
		चयन (packet.code) अणु
		हाल JOIN_DISALLOW:
		हाल JOIN_OK_NO_MAP:
			अवरोध;
		हाल JOIN_PROTOCOL_MISMATCH:
			mlog(ML_NOTICE,
			     "This node requested DLM locking protocol %u.%u and "
			     "filesystem locking protocol %u.%u.  At least one of "
			     "the protocol versions on node %d is not compatible, "
			     "disconnecting\n",
			     dlm->dlm_locking_proto.pv_major,
			     dlm->dlm_locking_proto.pv_minor,
			     dlm->fs_locking_proto.pv_major,
			     dlm->fs_locking_proto.pv_minor,
			     node);
			status = -EPROTO;
			अवरोध;
		हाल JOIN_OK:
			/* Use the same locking protocol as the remote node */
			dlm->dlm_locking_proto.pv_minor = packet.dlm_minor;
			dlm->fs_locking_proto.pv_minor = packet.fs_minor;
			mlog(0,
			     "Node %d responds JOIN_OK with DLM locking protocol "
			     "%u.%u and fs locking protocol %u.%u\n",
			     node,
			     dlm->dlm_locking_proto.pv_major,
			     dlm->dlm_locking_proto.pv_minor,
			     dlm->fs_locking_proto.pv_major,
			     dlm->fs_locking_proto.pv_minor);
			अवरोध;
		शेष:
			status = -EINVAL;
			mlog(ML_ERROR, "invalid response %d from node %u\n",
			     packet.code, node);
			/* Reset response to JOIN_DISALLOW */
			*response = JOIN_DISALLOW;
			अवरोध;
		पूर्ण
	पूर्ण

	mlog(0, "status %d, node %d response is %d\n", status, node,
	     *response);

bail:
	वापस status;
पूर्ण

अटल पूर्णांक dlm_send_one_join_निश्चित(काष्ठा dlm_ctxt *dlm,
				    अचिन्हित पूर्णांक node)
अणु
	पूर्णांक status;
	पूर्णांक ret;
	काष्ठा dlm_निश्चित_joined निश्चित_msg;

	mlog(0, "Sending join assert to node %u\n", node);

	स_रखो(&निश्चित_msg, 0, माप(निश्चित_msg));
	निश्चित_msg.node_idx = dlm->node_num;
	निश्चित_msg.name_len = म_माप(dlm->name);
	स_नकल(निश्चित_msg.करोमुख्य, dlm->name, निश्चित_msg.name_len);

	status = o2net_send_message(DLM_ASSERT_JOINED_MSG, DLM_MOD_KEY,
				    &निश्चित_msg, माप(निश्चित_msg), node,
				    &ret);
	अगर (status < 0)
		mlog(ML_ERROR, "Error %d when sending message %u (key 0x%x) to "
		     "node %u\n", status, DLM_ASSERT_JOINED_MSG, DLM_MOD_KEY,
		     node);
	अन्यथा
		status = ret;

	वापस status;
पूर्ण

अटल व्योम dlm_send_join_निश्चितs(काष्ठा dlm_ctxt *dlm,
				  अचिन्हित दीर्घ *node_map)
अणु
	पूर्णांक status, node, live;

	status = 0;
	node = -1;
	जबतक ((node = find_next_bit(node_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) अणु
		अगर (node == dlm->node_num)
			जारी;

		करो अणु
			/* It is very important that this message be
			 * received so we spin until either the node
			 * has died or it माला_लो the message. */
			status = dlm_send_one_join_निश्चित(dlm, node);

			spin_lock(&dlm->spinlock);
			live = test_bit(node, dlm->live_nodes_map);
			spin_unlock(&dlm->spinlock);

			अगर (status) अणु
				mlog(ML_ERROR, "Error return %d asserting "
				     "join on node %d\n", status, node);

				/* give us some समय between errors... */
				अगर (live)
					msleep(DLM_DOMAIN_BACKOFF_MS);
			पूर्ण
		पूर्ण जबतक (status && live);
	पूर्ण
पूर्ण

काष्ठा करोमुख्य_join_ctxt अणु
	अचिन्हित दीर्घ live_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित दीर्घ yes_resp_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
पूर्ण;

अटल पूर्णांक dlm_should_restart_join(काष्ठा dlm_ctxt *dlm,
				   काष्ठा करोमुख्य_join_ctxt *ctxt,
				   क्रमागत dlm_query_join_response_code response)
अणु
	पूर्णांक ret;

	अगर (response == JOIN_DISALLOW) अणु
		mlog(0, "Latest response of disallow -- should restart\n");
		वापस 1;
	पूर्ण

	spin_lock(&dlm->spinlock);
	/* For now, we restart the process अगर the node maps have
	 * changed at all */
	ret = स_भेद(ctxt->live_map, dlm->live_nodes_map,
		     माप(dlm->live_nodes_map));
	spin_unlock(&dlm->spinlock);

	अगर (ret)
		mlog(0, "Node maps changed -- should restart\n");

	वापस ret;
पूर्ण

अटल पूर्णांक dlm_try_to_join_करोमुख्य(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक status = 0, पंचांगpstat, node;
	काष्ठा करोमुख्य_join_ctxt *ctxt;
	क्रमागत dlm_query_join_response_code response = JOIN_DISALLOW;

	mlog(0, "%p", dlm);

	ctxt = kzalloc(माप(*ctxt), GFP_KERNEL);
	अगर (!ctxt) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/* group sem locking should work क्रम us here -- we're alपढ़ोy
	 * रेजिस्टरed क्रम heartbeat events so filling this should be
	 * atomic wrt getting those handlers called. */
	o2hb_fill_node_map(dlm->live_nodes_map, माप(dlm->live_nodes_map));

	spin_lock(&dlm->spinlock);
	स_नकल(ctxt->live_map, dlm->live_nodes_map, माप(ctxt->live_map));

	__dlm_set_joining_node(dlm, dlm->node_num);

	spin_unlock(&dlm->spinlock);

	node = -1;
	जबतक ((node = find_next_bit(ctxt->live_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) अणु
		अगर (node == dlm->node_num)
			जारी;

		status = dlm_request_join(dlm, node, &response);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		/* Ok, either we got a response or the node करोesn't have a
		 * dlm up. */
		अगर (response == JOIN_OK)
			set_bit(node, ctxt->yes_resp_map);

		अगर (dlm_should_restart_join(dlm, ctxt, response)) अणु
			status = -EAGAIN;
			जाओ bail;
		पूर्ण
	पूर्ण

	mlog(0, "Yay, done querying nodes!\n");

	/* Yay, everyone agree's we can join the करोमुख्य. My करोमुख्य is
	 * comprised of all nodes who were put in the
	 * yes_resp_map. Copy that पूर्णांकo our करोमुख्य map and send a join
	 * निश्चित message to clean up everyone अन्यथाs state. */
	spin_lock(&dlm->spinlock);
	स_नकल(dlm->करोमुख्य_map, ctxt->yes_resp_map,
	       माप(ctxt->yes_resp_map));
	set_bit(dlm->node_num, dlm->करोमुख्य_map);
	spin_unlock(&dlm->spinlock);

	/* Support क्रम global heartbeat and node info was added in 1.1 */
	अगर (dlm->dlm_locking_proto.pv_major > 1 ||
	    dlm->dlm_locking_proto.pv_minor > 0) अणु
		status = dlm_send_nodeinfo(dlm, ctxt->yes_resp_map);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		status = dlm_send_regions(dlm, ctxt->yes_resp_map);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	dlm_send_join_निश्चितs(dlm, ctxt->yes_resp_map);

	/* Joined state *must* be set beक्रमe the joining node
	 * inक्रमmation, otherwise the query_join handler may पढ़ो no
	 * current joiner but a state of NEW and tell joining nodes
	 * we're not in the करोमुख्य. */
	spin_lock(&dlm_करोमुख्य_lock);
	dlm->dlm_state = DLM_CTXT_JOINED;
	dlm->num_joins++;
	spin_unlock(&dlm_करोमुख्य_lock);

bail:
	spin_lock(&dlm->spinlock);
	__dlm_set_joining_node(dlm, DLM_LOCK_RES_OWNER_UNKNOWN);
	अगर (!status) अणु
		prपूर्णांकk(KERN_NOTICE "o2dlm: Joining domain %s ", dlm->name);
		__dlm_prपूर्णांक_nodes(dlm);
	पूर्ण
	spin_unlock(&dlm->spinlock);

	अगर (ctxt) अणु
		/* Do we need to send a cancel message to any nodes? */
		अगर (status < 0) अणु
			पंचांगpstat = dlm_send_join_cancels(dlm,
							ctxt->yes_resp_map,
							माप(ctxt->yes_resp_map));
			अगर (पंचांगpstat < 0)
				mlog_त्रुटि_सं(पंचांगpstat);
		पूर्ण
		kमुक्त(ctxt);
	पूर्ण

	mlog(0, "returning %d\n", status);
	वापस status;
पूर्ण

अटल व्योम dlm_unरेजिस्टर_करोमुख्य_handlers(काष्ठा dlm_ctxt *dlm)
अणु
	o2hb_unरेजिस्टर_callback(dlm->name, &dlm->dlm_hb_up);
	o2hb_unरेजिस्टर_callback(dlm->name, &dlm->dlm_hb_करोwn);
	o2net_unरेजिस्टर_handler_list(&dlm->dlm_करोमुख्य_handlers);
पूर्ण

अटल पूर्णांक dlm_रेजिस्टर_करोमुख्य_handlers(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक status;

	mlog(0, "registering handlers.\n");

	o2hb_setup_callback(&dlm->dlm_hb_करोwn, O2HB_NODE_DOWN_CB,
			    dlm_hb_node_करोwn_cb, dlm, DLM_HB_NODE_DOWN_PRI);
	o2hb_setup_callback(&dlm->dlm_hb_up, O2HB_NODE_UP_CB,
			    dlm_hb_node_up_cb, dlm, DLM_HB_NODE_UP_PRI);

	status = o2hb_रेजिस्टर_callback(dlm->name, &dlm->dlm_hb_करोwn);
	अगर (status)
		जाओ bail;

	status = o2hb_रेजिस्टर_callback(dlm->name, &dlm->dlm_hb_up);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_MASTER_REQUEST_MSG, dlm->key,
					माप(काष्ठा dlm_master_request),
					dlm_master_request_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_ASSERT_MASTER_MSG, dlm->key,
					माप(काष्ठा dlm_निश्चित_master),
					dlm_निश्चित_master_handler,
					dlm, dlm_निश्चित_master_post_handler,
					&dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_CREATE_LOCK_MSG, dlm->key,
					माप(काष्ठा dlm_create_lock),
					dlm_create_lock_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_CONVERT_LOCK_MSG, dlm->key,
					DLM_CONVERT_LOCK_MAX_LEN,
					dlm_convert_lock_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_UNLOCK_LOCK_MSG, dlm->key,
					DLM_UNLOCK_LOCK_MAX_LEN,
					dlm_unlock_lock_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_PROXY_AST_MSG, dlm->key,
					DLM_PROXY_AST_MAX_LEN,
					dlm_proxy_ast_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_EXIT_DOMAIN_MSG, dlm->key,
					माप(काष्ठा dlm_निकास_करोमुख्य),
					dlm_निकास_करोमुख्य_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_DEREF_LOCKRES_MSG, dlm->key,
					माप(काष्ठा dlm_deref_lockres),
					dlm_deref_lockres_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_MIGRATE_REQUEST_MSG, dlm->key,
					माप(काष्ठा dlm_migrate_request),
					dlm_migrate_request_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_MIG_LOCKRES_MSG, dlm->key,
					DLM_MIG_LOCKRES_MAX_LEN,
					dlm_mig_lockres_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_MASTER_REQUERY_MSG, dlm->key,
					माप(काष्ठा dlm_master_requery),
					dlm_master_requery_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_LOCK_REQUEST_MSG, dlm->key,
					माप(काष्ठा dlm_lock_request),
					dlm_request_all_locks_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_RECO_DATA_DONE_MSG, dlm->key,
					माप(काष्ठा dlm_reco_data_करोne),
					dlm_reco_data_करोne_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_BEGIN_RECO_MSG, dlm->key,
					माप(काष्ठा dlm_begin_reco),
					dlm_begin_reco_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_FINALIZE_RECO_MSG, dlm->key,
					माप(काष्ठा dlm_finalize_reco),
					dlm_finalize_reco_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_BEGIN_EXIT_DOMAIN_MSG, dlm->key,
					माप(काष्ठा dlm_निकास_करोमुख्य),
					dlm_begin_निकास_करोमुख्य_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_DEREF_LOCKRES_DONE, dlm->key,
					माप(काष्ठा dlm_deref_lockres_करोne),
					dlm_deref_lockres_करोne_handler,
					dlm, शून्य, &dlm->dlm_करोमुख्य_handlers);
bail:
	अगर (status)
		dlm_unरेजिस्टर_करोमुख्य_handlers(dlm);

	वापस status;
पूर्ण

अटल पूर्णांक dlm_join_करोमुख्य(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक backoff;
	अचिन्हित पूर्णांक total_backoff = 0;
	अक्षर wq_name[O2NM_MAX_NAME_LEN];

	BUG_ON(!dlm);

	mlog(0, "Join domain %s\n", dlm->name);

	status = dlm_रेजिस्टर_करोमुख्य_handlers(dlm);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = dlm_launch_thपढ़ो(dlm);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = dlm_launch_recovery_thपढ़ो(dlm);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	dlm_debug_init(dlm);

	snम_लिखो(wq_name, O2NM_MAX_NAME_LEN, "dlm_wq-%s", dlm->name);
	dlm->dlm_worker = alloc_workqueue(wq_name, WQ_MEM_RECLAIM, 0);
	अगर (!dlm->dlm_worker) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	करो अणु
		status = dlm_try_to_join_करोमुख्य(dlm);

		/* If we're racing another node to the join, then we
		 * need to back off temporarily and let them
		 * complete. */
#घोषणा	DLM_JOIN_TIMEOUT_MSECS	90000
		अगर (status == -EAGAIN) अणु
			अगर (संकेत_pending(current)) अणु
				status = -ERESTARTSYS;
				जाओ bail;
			पूर्ण

			अगर (total_backoff > DLM_JOIN_TIMEOUT_MSECS) अणु
				status = -ERESTARTSYS;
				mlog(ML_NOTICE, "Timed out joining dlm domain "
				     "%s after %u msecs\n", dlm->name,
				     total_backoff);
				जाओ bail;
			पूर्ण

			/*
			 * <chip> After you!
			 * <dale> No, after you!
			 * <chip> I insist!
			 * <dale> But you first!
			 * ...
			 */
			backoff = (अचिन्हित पूर्णांक)(jअगरfies & 0x3);
			backoff *= DLM_DOMAIN_BACKOFF_MS;
			total_backoff += backoff;
			mlog(0, "backoff %d\n", backoff);
			msleep(backoff);
		पूर्ण
	पूर्ण जबतक (status == -EAGAIN);

	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = 0;
bail:
	wake_up(&dlm_करोमुख्य_events);

	अगर (status) अणु
		dlm_unरेजिस्टर_करोमुख्य_handlers(dlm);
		dlm_complete_thपढ़ो(dlm);
		dlm_complete_recovery_thपढ़ो(dlm);
		dlm_destroy_dlm_worker(dlm);
	पूर्ण

	वापस status;
पूर्ण

अटल काष्ठा dlm_ctxt *dlm_alloc_ctxt(स्थिर अक्षर *करोमुख्य,
				u32 key)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा dlm_ctxt *dlm = शून्य;

	dlm = kzalloc(माप(*dlm), GFP_KERNEL);
	अगर (!dlm) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	dlm->name = kstrdup(करोमुख्य, GFP_KERNEL);
	अगर (dlm->name == शून्य) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	dlm->lockres_hash = (काष्ठा hlist_head **)dlm_alloc_pagevec(DLM_HASH_PAGES);
	अगर (!dlm->lockres_hash) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	क्रम (i = 0; i < DLM_HASH_BUCKETS; i++)
		INIT_HLIST_HEAD(dlm_lockres_hash(dlm, i));

	dlm->master_hash = (काष्ठा hlist_head **)
				dlm_alloc_pagevec(DLM_HASH_PAGES);
	अगर (!dlm->master_hash) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	क्रम (i = 0; i < DLM_HASH_BUCKETS; i++)
		INIT_HLIST_HEAD(dlm_master_hash(dlm, i));

	dlm->key = key;
	dlm->node_num = o2nm_this_node();

	dlm_create_debugfs_subroot(dlm);

	spin_lock_init(&dlm->spinlock);
	spin_lock_init(&dlm->master_lock);
	spin_lock_init(&dlm->ast_lock);
	spin_lock_init(&dlm->track_lock);
	INIT_LIST_HEAD(&dlm->list);
	INIT_LIST_HEAD(&dlm->dirty_list);
	INIT_LIST_HEAD(&dlm->reco.resources);
	INIT_LIST_HEAD(&dlm->reco.node_data);
	INIT_LIST_HEAD(&dlm->purge_list);
	INIT_LIST_HEAD(&dlm->dlm_करोमुख्य_handlers);
	INIT_LIST_HEAD(&dlm->tracking_list);
	dlm->reco.state = 0;

	INIT_LIST_HEAD(&dlm->pending_asts);
	INIT_LIST_HEAD(&dlm->pending_basts);

	mlog(0, "dlm->recovery_map=%p, &(dlm->recovery_map[0])=%p\n",
		  dlm->recovery_map, &(dlm->recovery_map[0]));

	स_रखो(dlm->recovery_map, 0, माप(dlm->recovery_map));
	स_रखो(dlm->live_nodes_map, 0, माप(dlm->live_nodes_map));
	स_रखो(dlm->करोमुख्य_map, 0, माप(dlm->करोमुख्य_map));

	dlm->dlm_thपढ़ो_task = शून्य;
	dlm->dlm_reco_thपढ़ो_task = शून्य;
	dlm->dlm_worker = शून्य;
	init_रुकोqueue_head(&dlm->dlm_thपढ़ो_wq);
	init_रुकोqueue_head(&dlm->dlm_reco_thपढ़ो_wq);
	init_रुकोqueue_head(&dlm->reco.event);
	init_रुकोqueue_head(&dlm->ast_wq);
	init_रुकोqueue_head(&dlm->migration_wq);
	INIT_LIST_HEAD(&dlm->mle_hb_events);

	dlm->joining_node = DLM_LOCK_RES_OWNER_UNKNOWN;
	init_रुकोqueue_head(&dlm->dlm_join_events);

	dlm->migrate_करोne = 0;

	dlm->reco.new_master = O2NM_INVALID_NODE_NUM;
	dlm->reco.dead_node = O2NM_INVALID_NODE_NUM;

	atomic_set(&dlm->res_tot_count, 0);
	atomic_set(&dlm->res_cur_count, 0);
	क्रम (i = 0; i < DLM_MLE_NUM_TYPES; ++i) अणु
		atomic_set(&dlm->mle_tot_count[i], 0);
		atomic_set(&dlm->mle_cur_count[i], 0);
	पूर्ण

	spin_lock_init(&dlm->work_lock);
	INIT_LIST_HEAD(&dlm->work_list);
	INIT_WORK(&dlm->dispatched_work, dlm_dispatch_work);

	kref_init(&dlm->dlm_refs);
	dlm->dlm_state = DLM_CTXT_NEW;

	INIT_LIST_HEAD(&dlm->dlm_eviction_callbacks);

	mlog(0, "context init: refcount %u\n",
		  kref_पढ़ो(&dlm->dlm_refs));

	ret = 0;
leave:
	अगर (ret < 0 && dlm) अणु
		अगर (dlm->master_hash)
			dlm_मुक्त_pagevec((व्योम **)dlm->master_hash,
					DLM_HASH_PAGES);

		अगर (dlm->lockres_hash)
			dlm_मुक्त_pagevec((व्योम **)dlm->lockres_hash,
					DLM_HASH_PAGES);

		kमुक्त(dlm->name);
		kमुक्त(dlm);
		dlm = शून्य;
	पूर्ण
	वापस dlm;
पूर्ण

/*
 * Compare a requested locking protocol version against the current one.
 *
 * If the major numbers are dअगरferent, they are incompatible.
 * If the current minor is greater than the request, they are incompatible.
 * If the current minor is less than or equal to the request, they are
 * compatible, and the requester should run at the current minor version.
 */
अटल पूर्णांक dlm_protocol_compare(काष्ठा dlm_protocol_version *existing,
				काष्ठा dlm_protocol_version *request)
अणु
	अगर (existing->pv_major != request->pv_major)
		वापस 1;

	अगर (existing->pv_minor > request->pv_minor)
		वापस 1;

	अगर (existing->pv_minor < request->pv_minor)
		request->pv_minor = existing->pv_minor;

	वापस 0;
पूर्ण

/*
 * dlm_रेजिस्टर_करोमुख्य: one-समय setup per "domain".
 *
 * The fileप्रणाली passes in the requested locking version via proto.
 * If registration was successful, proto will contain the negotiated
 * locking protocol.
 */
काष्ठा dlm_ctxt * dlm_रेजिस्टर_करोमुख्य(स्थिर अक्षर *करोमुख्य,
			       u32 key,
			       काष्ठा dlm_protocol_version *fs_proto)
अणु
	पूर्णांक ret;
	काष्ठा dlm_ctxt *dlm = शून्य;
	काष्ठा dlm_ctxt *new_ctxt = शून्य;

	अगर (म_माप(करोमुख्य) >= O2NM_MAX_NAME_LEN) अणु
		ret = -ENAMETOOLONG;
		mlog(ML_ERROR, "domain name length too long\n");
		जाओ leave;
	पूर्ण

	mlog(0, "register called for domain \"%s\"\n", करोमुख्य);

retry:
	dlm = शून्य;
	अगर (संकेत_pending(current)) अणु
		ret = -ERESTARTSYS;
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	spin_lock(&dlm_करोमुख्य_lock);

	dlm = __dlm_lookup_करोमुख्य(करोमुख्य);
	अगर (dlm) अणु
		अगर (dlm->dlm_state != DLM_CTXT_JOINED) अणु
			spin_unlock(&dlm_करोमुख्य_lock);

			mlog(0, "This ctxt is not joined yet!\n");
			रुको_event_पूर्णांकerruptible(dlm_करोमुख्य_events,
						 dlm_रुको_on_करोमुख्य_helper(
							 करोमुख्य));
			जाओ retry;
		पूर्ण

		अगर (dlm_protocol_compare(&dlm->fs_locking_proto, fs_proto)) अणु
			spin_unlock(&dlm_करोमुख्य_lock);
			mlog(ML_ERROR,
			     "Requested locking protocol version is not "
			     "compatible with already registered domain "
			     "\"%s\"\n", करोमुख्य);
			ret = -EPROTO;
			जाओ leave;
		पूर्ण

		__dlm_get(dlm);
		dlm->num_joins++;

		spin_unlock(&dlm_करोमुख्य_lock);

		ret = 0;
		जाओ leave;
	पूर्ण

	/* करोesn't exist */
	अगर (!new_ctxt) अणु
		spin_unlock(&dlm_करोमुख्य_lock);

		new_ctxt = dlm_alloc_ctxt(करोमुख्य, key);
		अगर (new_ctxt)
			जाओ retry;

		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	/* a little variable चयन-a-roo here... */
	dlm = new_ctxt;
	new_ctxt = शून्य;

	/* add the new करोमुख्य */
	list_add_tail(&dlm->list, &dlm_करोमुख्यs);
	spin_unlock(&dlm_करोमुख्य_lock);

	/*
	 * Pass the locking protocol version पूर्णांकo the join.  If the join
	 * succeeds, it will have the negotiated protocol set.
	 */
	dlm->dlm_locking_proto = dlm_protocol;
	dlm->fs_locking_proto = *fs_proto;

	ret = dlm_join_करोमुख्य(dlm);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		dlm_put(dlm);
		जाओ leave;
	पूर्ण

	/* Tell the caller what locking protocol we negotiated */
	*fs_proto = dlm->fs_locking_proto;

	ret = 0;
leave:
	अगर (new_ctxt)
		dlm_मुक्त_ctxt_mem(new_ctxt);

	अगर (ret < 0)
		dlm = ERR_PTR(ret);

	वापस dlm;
पूर्ण
EXPORT_SYMBOL_GPL(dlm_रेजिस्टर_करोमुख्य);

अटल LIST_HEAD(dlm_join_handlers);

अटल व्योम dlm_unरेजिस्टर_net_handlers(व्योम)
अणु
	o2net_unरेजिस्टर_handler_list(&dlm_join_handlers);
पूर्ण

अटल पूर्णांक dlm_रेजिस्टर_net_handlers(व्योम)
अणु
	पूर्णांक status = 0;

	status = o2net_रेजिस्टर_handler(DLM_QUERY_JOIN_MSG, DLM_MOD_KEY,
					माप(काष्ठा dlm_query_join_request),
					dlm_query_join_handler,
					शून्य, शून्य, &dlm_join_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_ASSERT_JOINED_MSG, DLM_MOD_KEY,
					माप(काष्ठा dlm_निश्चित_joined),
					dlm_निश्चित_joined_handler,
					शून्य, शून्य, &dlm_join_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_CANCEL_JOIN_MSG, DLM_MOD_KEY,
					माप(काष्ठा dlm_cancel_join),
					dlm_cancel_join_handler,
					शून्य, शून्य, &dlm_join_handlers);
	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_QUERY_REGION, DLM_MOD_KEY,
					माप(काष्ठा dlm_query_region),
					dlm_query_region_handler,
					शून्य, शून्य, &dlm_join_handlers);

	अगर (status)
		जाओ bail;

	status = o2net_रेजिस्टर_handler(DLM_QUERY_NODEINFO, DLM_MOD_KEY,
					माप(काष्ठा dlm_query_nodeinfo),
					dlm_query_nodeinfo_handler,
					शून्य, शून्य, &dlm_join_handlers);
bail:
	अगर (status < 0)
		dlm_unरेजिस्टर_net_handlers();

	वापस status;
पूर्ण

/* Doमुख्य eviction callback handling.
 *
 * The file प्रणाली requires notअगरication of node death *beक्रमe* the
 * dlm completes it's recovery work, otherwise it may be able to
 * acquire locks on resources requiring recovery. Since the dlm can
 * evict a node from it's करोमुख्य *beक्रमe* heartbeat fires, a similar
 * mechanism is required. */

/* Eviction is not expected to happen often, so a per-करोमुख्य lock is
 * not necessary. Eviction callbacks are allowed to sleep क्रम लघु
 * periods of समय. */
अटल DECLARE_RWSEM(dlm_callback_sem);

व्योम dlm_fire_करोमुख्य_eviction_callbacks(काष्ठा dlm_ctxt *dlm,
					पूर्णांक node_num)
अणु
	काष्ठा dlm_eviction_cb *cb;

	करोwn_पढ़ो(&dlm_callback_sem);
	list_क्रम_each_entry(cb, &dlm->dlm_eviction_callbacks, ec_item) अणु
		cb->ec_func(node_num, cb->ec_data);
	पूर्ण
	up_पढ़ो(&dlm_callback_sem);
पूर्ण

व्योम dlm_setup_eviction_cb(काष्ठा dlm_eviction_cb *cb,
			   dlm_eviction_func *f,
			   व्योम *data)
अणु
	INIT_LIST_HEAD(&cb->ec_item);
	cb->ec_func = f;
	cb->ec_data = data;
पूर्ण
EXPORT_SYMBOL_GPL(dlm_setup_eviction_cb);

व्योम dlm_रेजिस्टर_eviction_cb(काष्ठा dlm_ctxt *dlm,
			      काष्ठा dlm_eviction_cb *cb)
अणु
	करोwn_ग_लिखो(&dlm_callback_sem);
	list_add_tail(&cb->ec_item, &dlm->dlm_eviction_callbacks);
	up_ग_लिखो(&dlm_callback_sem);
पूर्ण
EXPORT_SYMBOL_GPL(dlm_रेजिस्टर_eviction_cb);

व्योम dlm_unरेजिस्टर_eviction_cb(काष्ठा dlm_eviction_cb *cb)
अणु
	करोwn_ग_लिखो(&dlm_callback_sem);
	list_del_init(&cb->ec_item);
	up_ग_लिखो(&dlm_callback_sem);
पूर्ण
EXPORT_SYMBOL_GPL(dlm_unरेजिस्टर_eviction_cb);

अटल पूर्णांक __init dlm_init(व्योम)
अणु
	पूर्णांक status;

	status = dlm_init_mle_cache();
	अगर (status) अणु
		mlog(ML_ERROR, "Could not create o2dlm_mle slabcache\n");
		जाओ error;
	पूर्ण

	status = dlm_init_master_caches();
	अगर (status) अणु
		mlog(ML_ERROR, "Could not create o2dlm_lockres and "
		     "o2dlm_lockname slabcaches\n");
		जाओ error;
	पूर्ण

	status = dlm_init_lock_cache();
	अगर (status) अणु
		mlog(ML_ERROR, "Count not create o2dlm_lock slabcache\n");
		जाओ error;
	पूर्ण

	status = dlm_रेजिस्टर_net_handlers();
	अगर (status) अणु
		mlog(ML_ERROR, "Unable to register network handlers\n");
		जाओ error;
	पूर्ण

	dlm_create_debugfs_root();

	वापस 0;
error:
	dlm_unरेजिस्टर_net_handlers();
	dlm_destroy_lock_cache();
	dlm_destroy_master_caches();
	dlm_destroy_mle_cache();
	वापस -1;
पूर्ण

अटल व्योम __निकास dlm_निकास (व्योम)
अणु
	dlm_destroy_debugfs_root();
	dlm_unरेजिस्टर_net_handlers();
	dlm_destroy_lock_cache();
	dlm_destroy_master_caches();
	dlm_destroy_mle_cache();
पूर्ण

MODULE_AUTHOR("Oracle");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OCFS2 Distributed Lock Management");

module_init(dlm_init);
module_निकास(dlm_निकास);
