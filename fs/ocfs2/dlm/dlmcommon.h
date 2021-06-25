<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * dlmcommon.h
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित DLMCOMMON_H
#घोषणा DLMCOMMON_H

#समावेश <linux/kref.h>

#घोषणा DLM_HB_NODE_DOWN_PRI     (0xf000000)
#घोषणा DLM_HB_NODE_UP_PRI       (0x8000000)

#घोषणा DLM_LOCKID_NAME_MAX    32

#घोषणा DLM_LOCK_RES_OWNER_UNKNOWN     O2NM_MAX_NODES

#घोषणा DLM_HASH_SIZE_DEFAULT	(1 << 17)
#अगर DLM_HASH_SIZE_DEFAULT < PAGE_SIZE
# define DLM_HASH_PAGES		1
#अन्यथा
# define DLM_HASH_PAGES		(DLM_HASH_SIZE_DEFAULT / PAGE_SIZE)
#पूर्ण_अगर
#घोषणा DLM_BUCKETS_PER_PAGE	(PAGE_SIZE / माप(काष्ठा hlist_head))
#घोषणा DLM_HASH_BUCKETS	(DLM_HASH_PAGES * DLM_BUCKETS_PER_PAGE)

/* Intended to make it easier क्रम us to चयन out hash functions */
#घोषणा dlm_lockid_hash(_n, _l) full_name_hash(शून्य, _n, _l)

क्रमागत dlm_mle_type अणु
	DLM_MLE_BLOCK = 0,
	DLM_MLE_MASTER = 1,
	DLM_MLE_MIGRATION = 2,
	DLM_MLE_NUM_TYPES = 3,
पूर्ण;

काष्ठा dlm_master_list_entry अणु
	काष्ठा hlist_node master_hash_node;
	काष्ठा list_head hb_events;
	काष्ठा dlm_ctxt *dlm;
	spinlock_t spinlock;
	रुको_queue_head_t wq;
	atomic_t woken;
	काष्ठा kref mle_refs;
	पूर्णांक inuse;
	अचिन्हित दीर्घ maybe_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित दीर्घ vote_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित दीर्घ response_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित दीर्घ node_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	u8 master;
	u8 new_master;
	क्रमागत dlm_mle_type type;
	काष्ठा o2hb_callback_func mle_hb_up;
	काष्ठा o2hb_callback_func mle_hb_करोwn;
	काष्ठा dlm_lock_resource *mleres;
	अचिन्हित अक्षर mname[DLM_LOCKID_NAME_MAX];
	अचिन्हित पूर्णांक mnamelen;
	अचिन्हित पूर्णांक mnamehash;
पूर्ण;

क्रमागत dlm_ast_type अणु
	DLM_AST = 0,
	DLM_BAST = 1,
	DLM_ASTUNLOCK = 2,
पूर्ण;


#घोषणा LKM_VALID_FLAGS (LKM_VALBLK | LKM_CONVERT | LKM_UNLOCK | \
			 LKM_CANCEL | LKM_INVVALBLK | LKM_FORCE | \
			 LKM_RECOVERY | LKM_LOCAL | LKM_NOQUEUE)

#घोषणा DLM_RECOVERY_LOCK_NAME       "$RECOVERY"
#घोषणा DLM_RECOVERY_LOCK_NAME_LEN   9

अटल अंतरभूत पूर्णांक dlm_is_recovery_lock(स्थिर अक्षर *lock_name, पूर्णांक name_len)
अणु
	अगर (name_len == DLM_RECOVERY_LOCK_NAME_LEN &&
	    स_भेद(lock_name, DLM_RECOVERY_LOCK_NAME, name_len)==0)
		वापस 1;
	वापस 0;
पूर्ण

#घोषणा DLM_RECO_STATE_ACTIVE    0x0001
#घोषणा DLM_RECO_STATE_FINALIZE  0x0002

काष्ठा dlm_recovery_ctxt
अणु
	काष्ठा list_head resources;
	काष्ठा list_head node_data;
	u8  new_master;
	u8  dead_node;
	u16 state;
	अचिन्हित दीर्घ node_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	रुको_queue_head_t event;
पूर्ण;

क्रमागत dlm_ctxt_state अणु
	DLM_CTXT_NEW = 0,
	DLM_CTXT_JOINED = 1,
	DLM_CTXT_IN_SHUTDOWN = 2,
	DLM_CTXT_LEAVING = 3,
पूर्ण;

काष्ठा dlm_ctxt
अणु
	काष्ठा list_head list;
	काष्ठा hlist_head **lockres_hash;
	काष्ठा list_head dirty_list;
	काष्ठा list_head purge_list;
	काष्ठा list_head pending_asts;
	काष्ठा list_head pending_basts;
	काष्ठा list_head tracking_list;
	अचिन्हित पूर्णांक purge_count;
	spinlock_t spinlock;
	spinlock_t ast_lock;
	spinlock_t track_lock;
	अक्षर *name;
	u8 node_num;
	u32 key;
	u8  joining_node;
	u8 migrate_करोne; /* set to 1 means node has migrated all lock resources */
	रुको_queue_head_t dlm_join_events;
	अचिन्हित दीर्घ live_nodes_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित दीर्घ करोमुख्य_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित दीर्घ निकास_करोमुख्य_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित दीर्घ recovery_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	काष्ठा dlm_recovery_ctxt reco;
	spinlock_t master_lock;
	काष्ठा hlist_head **master_hash;
	काष्ठा list_head mle_hb_events;

	/* these give a really vague idea of the प्रणाली load */
	atomic_t mle_tot_count[DLM_MLE_NUM_TYPES];
	atomic_t mle_cur_count[DLM_MLE_NUM_TYPES];
	atomic_t res_tot_count;
	atomic_t res_cur_count;

	काष्ठा dentry *dlm_debugfs_subroot;

	/* NOTE: Next three are रक्षित by dlm_करोमुख्य_lock */
	काष्ठा kref dlm_refs;
	क्रमागत dlm_ctxt_state dlm_state;
	अचिन्हित पूर्णांक num_joins;

	काष्ठा o2hb_callback_func dlm_hb_up;
	काष्ठा o2hb_callback_func dlm_hb_करोwn;
	काष्ठा task_काष्ठा *dlm_thपढ़ो_task;
	काष्ठा task_काष्ठा *dlm_reco_thपढ़ो_task;
	काष्ठा workqueue_काष्ठा *dlm_worker;
	रुको_queue_head_t dlm_thपढ़ो_wq;
	रुको_queue_head_t dlm_reco_thपढ़ो_wq;
	रुको_queue_head_t ast_wq;
	रुको_queue_head_t migration_wq;

	काष्ठा work_काष्ठा dispatched_work;
	काष्ठा list_head work_list;
	spinlock_t work_lock;
	काष्ठा list_head dlm_करोमुख्य_handlers;
	काष्ठा list_head	dlm_eviction_callbacks;

	/* The fileप्रणाली specअगरies this at करोमुख्य registration.  We
	 * cache it here to know what to tell other nodes. */
	काष्ठा dlm_protocol_version fs_locking_proto;
	/* This is the पूर्णांकer-dlm communication version */
	काष्ठा dlm_protocol_version dlm_locking_proto;
पूर्ण;

अटल अंतरभूत काष्ठा hlist_head *dlm_lockres_hash(काष्ठा dlm_ctxt *dlm, अचिन्हित i)
अणु
	वापस dlm->lockres_hash[(i / DLM_BUCKETS_PER_PAGE) % DLM_HASH_PAGES] + (i % DLM_BUCKETS_PER_PAGE);
पूर्ण

अटल अंतरभूत काष्ठा hlist_head *dlm_master_hash(काष्ठा dlm_ctxt *dlm,
						 अचिन्हित i)
अणु
	वापस dlm->master_hash[(i / DLM_BUCKETS_PER_PAGE) % DLM_HASH_PAGES] +
			(i % DLM_BUCKETS_PER_PAGE);
पूर्ण

/* these keventd work queue items are क्रम less-frequently
 * called functions that cannot be directly called from the
 * net message handlers क्रम some reason, usually because
 * they need to send net messages of their own. */
व्योम dlm_dispatch_work(काष्ठा work_काष्ठा *work);

काष्ठा dlm_lock_resource;
काष्ठा dlm_work_item;

प्रकार व्योम (dlm_workfunc_t)(काष्ठा dlm_work_item *, व्योम *);

काष्ठा dlm_request_all_locks_priv
अणु
	u8 reco_master;
	u8 dead_node;
पूर्ण;

काष्ठा dlm_mig_lockres_priv
अणु
	काष्ठा dlm_lock_resource *lockres;
	u8 real_master;
	u8 extra_ref;
पूर्ण;

काष्ठा dlm_निश्चित_master_priv
अणु
	काष्ठा dlm_lock_resource *lockres;
	u8 request_from;
	u32 flags;
	अचिन्हित ignore_higher:1;
पूर्ण;

काष्ठा dlm_deref_lockres_priv
अणु
	काष्ठा dlm_lock_resource *deref_res;
	u8 deref_node;
पूर्ण;

काष्ठा dlm_work_item
अणु
	काष्ठा list_head list;
	dlm_workfunc_t *func;
	काष्ठा dlm_ctxt *dlm;
	व्योम *data;
	जोड़ अणु
		काष्ठा dlm_request_all_locks_priv ral;
		काष्ठा dlm_mig_lockres_priv ml;
		काष्ठा dlm_निश्चित_master_priv am;
		काष्ठा dlm_deref_lockres_priv dl;
	पूर्ण u;
पूर्ण;

अटल अंतरभूत व्योम dlm_init_work_item(काष्ठा dlm_ctxt *dlm,
				      काष्ठा dlm_work_item *i,
				      dlm_workfunc_t *f, व्योम *data)
अणु
	स_रखो(i, 0, माप(*i));
	i->func = f;
	INIT_LIST_HEAD(&i->list);
	i->data = data;
	i->dlm = dlm;  /* must have alपढ़ोy करोne a dlm_grab on this! */
पूर्ण



अटल अंतरभूत व्योम __dlm_set_joining_node(काष्ठा dlm_ctxt *dlm,
					  u8 node)
अणु
	निश्चित_spin_locked(&dlm->spinlock);

	dlm->joining_node = node;
	wake_up(&dlm->dlm_join_events);
पूर्ण

#घोषणा DLM_LOCK_RES_UNINITED             0x00000001
#घोषणा DLM_LOCK_RES_RECOVERING           0x00000002
#घोषणा DLM_LOCK_RES_READY                0x00000004
#घोषणा DLM_LOCK_RES_सूचीTY                0x00000008
#घोषणा DLM_LOCK_RES_IN_PROGRESS          0x00000010
#घोषणा DLM_LOCK_RES_MIGRATING            0x00000020
#घोषणा DLM_LOCK_RES_DROPPING_REF         0x00000040
#घोषणा DLM_LOCK_RES_BLOCK_सूचीTY          0x00001000
#घोषणा DLM_LOCK_RES_SETREF_INPROG        0x00002000
#घोषणा DLM_LOCK_RES_RECOVERY_WAITING     0x00004000

/* max milliseconds to रुको to sync up a network failure with a node death */
#घोषणा DLM_NODE_DEATH_WAIT_MAX (5 * 1000)

#घोषणा DLM_PURGE_INTERVAL_MS   (8 * 1000)

काष्ठा dlm_lock_resource
अणु
	/* WARNING: Please see the comment in dlm_init_lockres beक्रमe
	 * adding fields here. */
	काष्ठा hlist_node hash_node;
	काष्ठा qstr lockname;
	काष्ठा kref      refs;

	/*
	 * Please keep granted, converting, and blocked in this order,
	 * as some funcs want to iterate over all lists.
	 *
	 * All four lists are रक्षित by the hash's reference.
	 */
	काष्ठा list_head granted;
	काष्ठा list_head converting;
	काष्ठा list_head blocked;
	काष्ठा list_head purge;

	/*
	 * These two lists require you to hold an additional reference
	 * जबतक they are on the list.
	 */
	काष्ठा list_head dirty;
	काष्ठा list_head recovering; // dlm_recovery_ctxt.resources list

	/* Added during init and हटाओd during release */
	काष्ठा list_head tracking;	/* dlm->tracking_list */

	/* unused lock resources have their last_used stamped and are
	 * put on a list क्रम the dlm thपढ़ो to run. */
	अचिन्हित दीर्घ    last_used;

	काष्ठा dlm_ctxt *dlm;

	अचिन्हित migration_pending:1;
	atomic_t asts_reserved;
	spinlock_t spinlock;
	रुको_queue_head_t wq;
	u8  owner;              //node which owns the lock resource, or unknown
	u16 state;
	अक्षर lvb[DLM_LVB_LEN];
	अचिन्हित पूर्णांक inflight_locks;
	अचिन्हित पूर्णांक inflight_निश्चित_workers;
	अचिन्हित दीर्घ refmap[BITS_TO_LONGS(O2NM_MAX_NODES)];
पूर्ण;

काष्ठा dlm_migratable_lock
अणु
	__be64 cookie;

	/* these 3 are just padding क्रम the in-memory काष्ठाure, but
	 * list and flags are actually used when sent over the wire */
	__be16 pad1;
	u8 list;  // 0=granted, 1=converting, 2=blocked
	u8 flags;

	s8 type;
	s8 convert_type;
	s8 highest_blocked;
	u8 node;
पूर्ण;  // 16 bytes

काष्ठा dlm_lock
अणु
	काष्ठा dlm_migratable_lock ml;

	काष्ठा list_head list;
	काष्ठा list_head ast_list;
	काष्ठा list_head bast_list;
	काष्ठा dlm_lock_resource *lockres;
	spinlock_t spinlock;
	काष्ठा kref lock_refs;

	// ast and bast must be callable जबतक holding a spinlock!
	dlm_astlockfunc_t *ast;
	dlm_bastlockfunc_t *bast;
	व्योम *astdata;
	काष्ठा dlm_lockstatus *lksb;
	अचिन्हित ast_pending:1,
		 bast_pending:1,
		 convert_pending:1,
		 lock_pending:1,
		 cancel_pending:1,
		 unlock_pending:1,
		 lksb_kernel_allocated:1;
पूर्ण;

क्रमागत dlm_lockres_list अणु
	DLM_GRANTED_LIST = 0,
	DLM_CONVERTING_LIST = 1,
	DLM_BLOCKED_LIST = 2,
पूर्ण;

अटल अंतरभूत पूर्णांक dlm_lvb_is_empty(अक्षर *lvb)
अणु
	पूर्णांक i;
	क्रम (i=0; i<DLM_LVB_LEN; i++)
		अगर (lvb[i])
			वापस 0;
	वापस 1;
पूर्ण

अटल अंतरभूत अक्षर *dlm_list_in_text(क्रमागत dlm_lockres_list idx)
अणु
	अगर (idx == DLM_GRANTED_LIST)
		वापस "granted";
	अन्यथा अगर (idx == DLM_CONVERTING_LIST)
		वापस "converting";
	अन्यथा अगर (idx == DLM_BLOCKED_LIST)
		वापस "blocked";
	अन्यथा
		वापस "unknown";
पूर्ण

अटल अंतरभूत काष्ठा list_head *
dlm_list_idx_to_ptr(काष्ठा dlm_lock_resource *res, क्रमागत dlm_lockres_list idx)
अणु
	काष्ठा list_head *ret = शून्य;
	अगर (idx == DLM_GRANTED_LIST)
		ret = &res->granted;
	अन्यथा अगर (idx == DLM_CONVERTING_LIST)
		ret = &res->converting;
	अन्यथा अगर (idx == DLM_BLOCKED_LIST)
		ret = &res->blocked;
	अन्यथा
		BUG();
	वापस ret;
पूर्ण




काष्ठा dlm_node_iter
अणु
	अचिन्हित दीर्घ node_map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	पूर्णांक curnode;
पूर्ण;


क्रमागत अणु
	DLM_MASTER_REQUEST_MSG		= 500,
	DLM_UNUSED_MSG1			= 501,
	DLM_ASSERT_MASTER_MSG		= 502,
	DLM_CREATE_LOCK_MSG		= 503,
	DLM_CONVERT_LOCK_MSG		= 504,
	DLM_PROXY_AST_MSG		= 505,
	DLM_UNLOCK_LOCK_MSG		= 506,
	DLM_DEREF_LOCKRES_MSG		= 507,
	DLM_MIGRATE_REQUEST_MSG		= 508,
	DLM_MIG_LOCKRES_MSG		= 509,
	DLM_QUERY_JOIN_MSG		= 510,
	DLM_ASSERT_JOINED_MSG		= 511,
	DLM_CANCEL_JOIN_MSG		= 512,
	DLM_EXIT_DOMAIN_MSG		= 513,
	DLM_MASTER_REQUERY_MSG		= 514,
	DLM_LOCK_REQUEST_MSG		= 515,
	DLM_RECO_DATA_DONE_MSG		= 516,
	DLM_BEGIN_RECO_MSG		= 517,
	DLM_FINALIZE_RECO_MSG		= 518,
	DLM_QUERY_REGION		= 519,
	DLM_QUERY_NODEINFO		= 520,
	DLM_BEGIN_EXIT_DOMAIN_MSG	= 521,
	DLM_DEREF_LOCKRES_DONE		= 522,
पूर्ण;

काष्ठा dlm_reco_node_data
अणु
	पूर्णांक state;
	u8 node_num;
	काष्ठा list_head list;
पूर्ण;

क्रमागत अणु
	DLM_RECO_NODE_DATA_DEAD = -1,
	DLM_RECO_NODE_DATA_INIT = 0,
	DLM_RECO_NODE_DATA_REQUESTING = 1,
	DLM_RECO_NODE_DATA_REQUESTED = 2,
	DLM_RECO_NODE_DATA_RECEIVING = 3,
	DLM_RECO_NODE_DATA_DONE = 4,
	DLM_RECO_NODE_DATA_FINALIZE_SENT = 5,
पूर्ण;


क्रमागत अणु
	DLM_MASTER_RESP_NO = 0,
	DLM_MASTER_RESP_YES = 1,
	DLM_MASTER_RESP_MAYBE = 2,
	DLM_MASTER_RESP_ERROR = 3,
पूर्ण;


काष्ठा dlm_master_request
अणु
	u8 node_idx;
	u8 namelen;
	__be16 pad1;
	__be32 flags;

	u8 name[O2NM_MAX_NAME_LEN];
पूर्ण;

#घोषणा DLM_ASSERT_RESPONSE_REASSERT       0x00000001
#घोषणा DLM_ASSERT_RESPONSE_MASTERY_REF    0x00000002

#घोषणा DLM_ASSERT_MASTER_MLE_CLEANUP      0x00000001
#घोषणा DLM_ASSERT_MASTER_REQUERY          0x00000002
#घोषणा DLM_ASSERT_MASTER_FINISH_MIGRATION 0x00000004
काष्ठा dlm_निश्चित_master
अणु
	u8 node_idx;
	u8 namelen;
	__be16 pad1;
	__be32 flags;

	u8 name[O2NM_MAX_NAME_LEN];
पूर्ण;

#घोषणा DLM_MIGRATE_RESPONSE_MASTERY_REF   0x00000001

काष्ठा dlm_migrate_request
अणु
	u8 master;
	u8 new_master;
	u8 namelen;
	u8 pad1;
	__be32 pad2;
	u8 name[O2NM_MAX_NAME_LEN];
पूर्ण;

काष्ठा dlm_master_requery
अणु
	u8 pad1;
	u8 pad2;
	u8 node_idx;
	u8 namelen;
	__be32 pad3;
	u8 name[O2NM_MAX_NAME_LEN];
पूर्ण;

#घोषणा DLM_MRES_RECOVERY   0x01
#घोषणा DLM_MRES_MIGRATION  0x02
#घोषणा DLM_MRES_ALL_DONE   0x04

/*
 * We would like to get one whole lockres पूर्णांकo a single network
 * message whenever possible.  Generally speaking, there will be
 * at most one dlm_lock on a lockres क्रम each node in the cluster,
 * plus (infrequently) any additional locks coming in from userdlm.
 *
 * काष्ठा _dlm_lockres_page
 * अणु
 * 	dlm_migratable_lockres mres;
 * 	dlm_migratable_lock ml[DLM_MAX_MIGRATABLE_LOCKS];
 * 	u8 pad[DLM_MIG_LOCKRES_RESERVED];
 * पूर्ण;
 *
 * from ../cluster/tcp.h
 *    O2NET_MAX_PAYLOAD_BYTES  (4096 - माप(net_msg))
 *    (roughly 4080 bytes)
 * and माप(dlm_migratable_lockres) = 112 bytes
 * and माप(dlm_migratable_lock) = 16 bytes
 *
 * Choosing DLM_MAX_MIGRATABLE_LOCKS=240 and
 * DLM_MIG_LOCKRES_RESERVED=128 means we have this:
 *
 *  (DLM_MAX_MIGRATABLE_LOCKS * माप(dlm_migratable_lock)) +
 *     माप(dlm_migratable_lockres) + DLM_MIG_LOCKRES_RESERVED =
 *        NET_MAX_PAYLOAD_BYTES
 *  (240 * 16) + 112 + 128 = 4080
 *
 * So a lockres would need more than 240 locks beक्रमe it would
 * use more than one network packet to recover.  Not too bad.
 */
#घोषणा DLM_MAX_MIGRATABLE_LOCKS   240

काष्ठा dlm_migratable_lockres
अणु
	u8 master;
	u8 lockname_len;
	u8 num_locks;    // locks sent in this काष्ठाure
	u8 flags;
	__be32 total_locks; // locks to be sent क्रम this migration cookie
	__be64 mig_cookie;  // cookie क्रम this lockres migration
			 // or zero अगर not needed
	// 16 bytes
	u8 lockname[DLM_LOCKID_NAME_MAX];
	// 48 bytes
	u8 lvb[DLM_LVB_LEN];
	// 112 bytes
	काष्ठा dlm_migratable_lock ml[];  // 16 bytes each, begins at byte 112
पूर्ण;
#घोषणा DLM_MIG_LOCKRES_MAX_LEN  \
	(माप(काष्ठा dlm_migratable_lockres) + \
	 (माप(काष्ठा dlm_migratable_lock) * \
	  DLM_MAX_MIGRATABLE_LOCKS) )

/* from above, 128 bytes
 * क्रम some undetermined future use */
#घोषणा DLM_MIG_LOCKRES_RESERVED   (O2NET_MAX_PAYLOAD_BYTES - \
				    DLM_MIG_LOCKRES_MAX_LEN)

काष्ठा dlm_create_lock
अणु
	__be64 cookie;

	__be32 flags;
	u8 pad1;
	u8 node_idx;
	s8 requested_type;
	u8 namelen;

	u8 name[O2NM_MAX_NAME_LEN];
पूर्ण;

काष्ठा dlm_convert_lock
अणु
	__be64 cookie;

	__be32 flags;
	u8 pad1;
	u8 node_idx;
	s8 requested_type;
	u8 namelen;

	u8 name[O2NM_MAX_NAME_LEN];

	s8 lvb[];
पूर्ण;
#घोषणा DLM_CONVERT_LOCK_MAX_LEN  (माप(काष्ठा dlm_convert_lock)+DLM_LVB_LEN)

काष्ठा dlm_unlock_lock
अणु
	__be64 cookie;

	__be32 flags;
	__be16 pad1;
	u8 node_idx;
	u8 namelen;

	u8 name[O2NM_MAX_NAME_LEN];

	s8 lvb[];
पूर्ण;
#घोषणा DLM_UNLOCK_LOCK_MAX_LEN  (माप(काष्ठा dlm_unlock_lock)+DLM_LVB_LEN)

काष्ठा dlm_proxy_ast
अणु
	__be64 cookie;

	__be32 flags;
	u8 node_idx;
	u8 type;
	u8 blocked_type;
	u8 namelen;

	u8 name[O2NM_MAX_NAME_LEN];

	s8 lvb[];
पूर्ण;
#घोषणा DLM_PROXY_AST_MAX_LEN  (माप(काष्ठा dlm_proxy_ast)+DLM_LVB_LEN)

#घोषणा DLM_MOD_KEY (0x666c6172)
क्रमागत dlm_query_join_response_code अणु
	JOIN_DISALLOW = 0,
	JOIN_OK = 1,
	JOIN_OK_NO_MAP = 2,
	JOIN_PROTOCOL_MISMATCH = 3,
पूर्ण;

काष्ठा dlm_query_join_packet अणु
	u8 code;	/* Response code.  dlm_minor and fs_minor
			   are only valid अगर this is JOIN_OK */
	u8 dlm_minor;	/* The minor version of the protocol the
			   dlm is speaking. */
	u8 fs_minor;	/* The minor version of the protocol the
			   fileप्रणाली is speaking. */
	u8 reserved;
पूर्ण;

जोड़ dlm_query_join_response अणु
	__be32 पूर्णांकval;
	काष्ठा dlm_query_join_packet packet;
पूर्ण;

काष्ठा dlm_lock_request
अणु
	u8 node_idx;
	u8 dead_node;
	__be16 pad1;
	__be32 pad2;
पूर्ण;

काष्ठा dlm_reco_data_करोne
अणु
	u8 node_idx;
	u8 dead_node;
	__be16 pad1;
	__be32 pad2;

	/* unused क्रम now */
	/* eventually we can use this to attempt
	 * lvb recovery based on each node's info */
	u8 reco_lvb[DLM_LVB_LEN];
पूर्ण;

काष्ठा dlm_begin_reco
अणु
	u8 node_idx;
	u8 dead_node;
	__be16 pad1;
	__be32 pad2;
पूर्ण;

काष्ठा dlm_query_join_request
अणु
	u8 node_idx;
	u8 pad1[2];
	u8 name_len;
	काष्ठा dlm_protocol_version dlm_proto;
	काष्ठा dlm_protocol_version fs_proto;
	u8 करोमुख्य[O2NM_MAX_NAME_LEN];
	u8 node_map[BITS_TO_BYTES(O2NM_MAX_NODES)];
पूर्ण;

काष्ठा dlm_निश्चित_joined
अणु
	u8 node_idx;
	u8 pad1[2];
	u8 name_len;
	u8 करोमुख्य[O2NM_MAX_NAME_LEN];
पूर्ण;

काष्ठा dlm_cancel_join
अणु
	u8 node_idx;
	u8 pad1[2];
	u8 name_len;
	u8 करोमुख्य[O2NM_MAX_NAME_LEN];
पूर्ण;

काष्ठा dlm_query_region अणु
	u8 qr_node;
	u8 qr_numregions;
	u8 qr_namelen;
	u8 pad1;
	u8 qr_करोमुख्य[O2NM_MAX_NAME_LEN];
	u8 qr_regions[O2HB_MAX_REGION_NAME_LEN * O2NM_MAX_REGIONS];
पूर्ण;

काष्ठा dlm_node_info अणु
	u8 ni_nodक्रमागत;
	u8 pad1;
	__be16 ni_ipv4_port;
	__be32 ni_ipv4_address;
पूर्ण;

काष्ठा dlm_query_nodeinfo अणु
	u8 qn_nodक्रमागत;
	u8 qn_numnodes;
	u8 qn_namelen;
	u8 pad1;
	u8 qn_करोमुख्य[O2NM_MAX_NAME_LEN];
	काष्ठा dlm_node_info qn_nodes[O2NM_MAX_NODES];
पूर्ण;

काष्ठा dlm_निकास_करोमुख्य
अणु
	u8 node_idx;
	u8 pad1[3];
पूर्ण;

काष्ठा dlm_finalize_reco
अणु
	u8 node_idx;
	u8 dead_node;
	u8 flags;
	u8 pad1;
	__be32 pad2;
पूर्ण;

काष्ठा dlm_deref_lockres
अणु
	u32 pad1;
	u16 pad2;
	u8 node_idx;
	u8 namelen;

	u8 name[O2NM_MAX_NAME_LEN];
पूर्ण;

क्रमागत अणु
	DLM_DEREF_RESPONSE_DONE = 0,
	DLM_DEREF_RESPONSE_INPROG = 1,
पूर्ण;

काष्ठा dlm_deref_lockres_करोne अणु
	u32 pad1;
	u16 pad2;
	u8 node_idx;
	u8 namelen;

	u8 name[O2NM_MAX_NAME_LEN];
पूर्ण;

अटल अंतरभूत क्रमागत dlm_status
__dlm_lockres_state_to_status(काष्ठा dlm_lock_resource *res)
अणु
	क्रमागत dlm_status status = DLM_NORMAL;

	निश्चित_spin_locked(&res->spinlock);

	अगर (res->state & (DLM_LOCK_RES_RECOVERING|
			DLM_LOCK_RES_RECOVERY_WAITING))
		status = DLM_RECOVERING;
	अन्यथा अगर (res->state & DLM_LOCK_RES_MIGRATING)
		status = DLM_MIGRATING;
	अन्यथा अगर (res->state & DLM_LOCK_RES_IN_PROGRESS)
		status = DLM_FORWARD;

	वापस status;
पूर्ण

अटल अंतरभूत u8 dlm_get_lock_cookie_node(u64 cookie)
अणु
	u8 ret;
	cookie >>= 56;
	ret = (u8)(cookie & 0xffULL);
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ dlm_get_lock_cookie_seq(u64 cookie)
अणु
	अचिन्हित दीर्घ दीर्घ ret;
	ret = ((अचिन्हित दीर्घ दीर्घ)cookie) & 0x00ffffffffffffffULL;
	वापस ret;
पूर्ण

काष्ठा dlm_lock * dlm_new_lock(पूर्णांक type, u8 node, u64 cookie,
			       काष्ठा dlm_lockstatus *lksb);
व्योम dlm_lock_get(काष्ठा dlm_lock *lock);
व्योम dlm_lock_put(काष्ठा dlm_lock *lock);

व्योम dlm_lock_attach_lockres(काष्ठा dlm_lock *lock,
			     काष्ठा dlm_lock_resource *res);

पूर्णांक dlm_create_lock_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			    व्योम **ret_data);
पूर्णांक dlm_convert_lock_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			     व्योम **ret_data);
पूर्णांक dlm_proxy_ast_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			  व्योम **ret_data);

व्योम dlm_revert_pending_convert(काष्ठा dlm_lock_resource *res,
				काष्ठा dlm_lock *lock);
व्योम dlm_revert_pending_lock(काष्ठा dlm_lock_resource *res,
			     काष्ठा dlm_lock *lock);

पूर्णांक dlm_unlock_lock_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			    व्योम **ret_data);
व्योम dlm_commit_pending_cancel(काष्ठा dlm_lock_resource *res,
			       काष्ठा dlm_lock *lock);
व्योम dlm_commit_pending_unlock(काष्ठा dlm_lock_resource *res,
			       काष्ठा dlm_lock *lock);

पूर्णांक dlm_launch_thपढ़ो(काष्ठा dlm_ctxt *dlm);
व्योम dlm_complete_thपढ़ो(काष्ठा dlm_ctxt *dlm);
पूर्णांक dlm_launch_recovery_thपढ़ो(काष्ठा dlm_ctxt *dlm);
व्योम dlm_complete_recovery_thपढ़ो(काष्ठा dlm_ctxt *dlm);
व्योम dlm_रुको_क्रम_recovery(काष्ठा dlm_ctxt *dlm);
व्योम dlm_kick_recovery_thपढ़ो(काष्ठा dlm_ctxt *dlm);
पूर्णांक dlm_is_node_dead(काष्ठा dlm_ctxt *dlm, u8 node);
व्योम dlm_रुको_क्रम_node_death(काष्ठा dlm_ctxt *dlm, u8 node, पूर्णांक समयout);
व्योम dlm_रुको_क्रम_node_recovery(काष्ठा dlm_ctxt *dlm, u8 node, पूर्णांक समयout);

व्योम dlm_put(काष्ठा dlm_ctxt *dlm);
काष्ठा dlm_ctxt *dlm_grab(काष्ठा dlm_ctxt *dlm);
पूर्णांक dlm_करोमुख्य_fully_joined(काष्ठा dlm_ctxt *dlm);

व्योम __dlm_lockres_calc_usage(काष्ठा dlm_ctxt *dlm,
			      काष्ठा dlm_lock_resource *res);
व्योम dlm_lockres_calc_usage(काष्ठा dlm_ctxt *dlm,
			    काष्ठा dlm_lock_resource *res);
अटल अंतरभूत व्योम dlm_lockres_get(काष्ठा dlm_lock_resource *res)
अणु
	/* This is called on every lookup, so it might be worth
	 * inlining. */
	kref_get(&res->refs);
पूर्ण
व्योम dlm_lockres_put(काष्ठा dlm_lock_resource *res);
व्योम __dlm_unhash_lockres(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res);
व्योम __dlm_insert_lockres(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res);
काष्ठा dlm_lock_resource * __dlm_lookup_lockres_full(काष्ठा dlm_ctxt *dlm,
						     स्थिर अक्षर *name,
						     अचिन्हित पूर्णांक len,
						     अचिन्हित पूर्णांक hash);
काष्ठा dlm_lock_resource * __dlm_lookup_lockres(काष्ठा dlm_ctxt *dlm,
						स्थिर अक्षर *name,
						अचिन्हित पूर्णांक len,
						अचिन्हित पूर्णांक hash);
काष्ठा dlm_lock_resource * dlm_lookup_lockres(काष्ठा dlm_ctxt *dlm,
					      स्थिर अक्षर *name,
					      अचिन्हित पूर्णांक len);

पूर्णांक dlm_is_host_करोwn(पूर्णांक त्रुटि_सं);

काष्ठा dlm_lock_resource * dlm_get_lock_resource(काष्ठा dlm_ctxt *dlm,
						 स्थिर अक्षर *lockid,
						 पूर्णांक namelen,
						 पूर्णांक flags);
काष्ठा dlm_lock_resource *dlm_new_lockres(काष्ठा dlm_ctxt *dlm,
					  स्थिर अक्षर *name,
					  अचिन्हित पूर्णांक namelen);

व्योम dlm_lockres_set_refmap_bit(काष्ठा dlm_ctxt *dlm,
				काष्ठा dlm_lock_resource *res, पूर्णांक bit);
व्योम dlm_lockres_clear_refmap_bit(काष्ठा dlm_ctxt *dlm,
				  काष्ठा dlm_lock_resource *res, पूर्णांक bit);

व्योम dlm_lockres_drop_inflight_ref(काष्ठा dlm_ctxt *dlm,
				   काष्ठा dlm_lock_resource *res);
व्योम dlm_lockres_grab_inflight_ref(काष्ठा dlm_ctxt *dlm,
				   काष्ठा dlm_lock_resource *res);

व्योम __dlm_lockres_grab_inflight_worker(काष्ठा dlm_ctxt *dlm,
		काष्ठा dlm_lock_resource *res);

व्योम dlm_queue_ast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock *lock);
व्योम __dlm_queue_ast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock *lock);
व्योम __dlm_queue_bast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock *lock);
व्योम dlm_करो_local_ast(काष्ठा dlm_ctxt *dlm,
		      काष्ठा dlm_lock_resource *res,
		      काष्ठा dlm_lock *lock);
पूर्णांक dlm_करो_remote_ast(काष्ठा dlm_ctxt *dlm,
		      काष्ठा dlm_lock_resource *res,
		      काष्ठा dlm_lock *lock);
व्योम dlm_करो_local_bast(काष्ठा dlm_ctxt *dlm,
		       काष्ठा dlm_lock_resource *res,
		       काष्ठा dlm_lock *lock,
		       पूर्णांक blocked_type);
पूर्णांक dlm_send_proxy_ast_msg(काष्ठा dlm_ctxt *dlm,
			   काष्ठा dlm_lock_resource *res,
			   काष्ठा dlm_lock *lock,
			   पूर्णांक msg_type,
			   पूर्णांक blocked_type, पूर्णांक flags);
अटल अंतरभूत पूर्णांक dlm_send_proxy_bast(काष्ठा dlm_ctxt *dlm,
				      काष्ठा dlm_lock_resource *res,
				      काष्ठा dlm_lock *lock,
				      पूर्णांक blocked_type)
अणु
	वापस dlm_send_proxy_ast_msg(dlm, res, lock, DLM_BAST,
				      blocked_type, 0);
पूर्ण

अटल अंतरभूत पूर्णांक dlm_send_proxy_ast(काष्ठा dlm_ctxt *dlm,
				     काष्ठा dlm_lock_resource *res,
				     काष्ठा dlm_lock *lock,
				     पूर्णांक flags)
अणु
	वापस dlm_send_proxy_ast_msg(dlm, res, lock, DLM_AST,
				      0, flags);
पूर्ण

व्योम dlm_prपूर्णांक_one_lock_resource(काष्ठा dlm_lock_resource *res);
व्योम __dlm_prपूर्णांक_one_lock_resource(काष्ठा dlm_lock_resource *res);

व्योम dlm_kick_thपढ़ो(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res);
व्योम __dlm_dirty_lockres(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res);


व्योम dlm_hb_node_करोwn_cb(काष्ठा o2nm_node *node, पूर्णांक idx, व्योम *data);
व्योम dlm_hb_node_up_cb(काष्ठा o2nm_node *node, पूर्णांक idx, व्योम *data);

पूर्णांक dlm_empty_lockres(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res);
पूर्णांक dlm_finish_migration(काष्ठा dlm_ctxt *dlm,
			 काष्ठा dlm_lock_resource *res,
			 u8 old_master);
व्योम dlm_lockres_release_ast(काष्ठा dlm_ctxt *dlm,
			     काष्ठा dlm_lock_resource *res);
व्योम __dlm_lockres_reserve_ast(काष्ठा dlm_lock_resource *res);

पूर्णांक dlm_master_request_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			       व्योम **ret_data);
पूर्णांक dlm_निश्चित_master_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			      व्योम **ret_data);
व्योम dlm_निश्चित_master_post_handler(पूर्णांक status, व्योम *data, व्योम *ret_data);
पूर्णांक dlm_deref_lockres_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			      व्योम **ret_data);
पूर्णांक dlm_deref_lockres_करोne_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			      व्योम **ret_data);
पूर्णांक dlm_migrate_request_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				व्योम **ret_data);
पूर्णांक dlm_mig_lockres_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			    व्योम **ret_data);
पूर्णांक dlm_master_requery_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			       व्योम **ret_data);
पूर्णांक dlm_request_all_locks_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				  व्योम **ret_data);
पूर्णांक dlm_reco_data_करोne_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			       व्योम **ret_data);
पूर्णांक dlm_begin_reco_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			   व्योम **ret_data);
पूर्णांक dlm_finalize_reco_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			      व्योम **ret_data);
पूर्णांक dlm_करो_master_requery(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res,
			  u8 nodक्रमागत, u8 *real_master);

व्योम __dlm_करो_purge_lockres(काष्ठा dlm_ctxt *dlm,
		काष्ठा dlm_lock_resource *res);

पूर्णांक dlm_dispatch_निश्चित_master(काष्ठा dlm_ctxt *dlm,
			       काष्ठा dlm_lock_resource *res,
			       पूर्णांक ignore_higher,
			       u8 request_from,
			       u32 flags);


पूर्णांक dlm_send_one_lockres(काष्ठा dlm_ctxt *dlm,
			 काष्ठा dlm_lock_resource *res,
			 काष्ठा dlm_migratable_lockres *mres,
			 u8 send_to,
			 u8 flags);
व्योम dlm_move_lockres_to_recovery_list(काष्ठा dlm_ctxt *dlm,
				       काष्ठा dlm_lock_resource *res);

/* will निकास holding res->spinlock, but may drop in function */
व्योम __dlm_रुको_on_lockres_flags(काष्ठा dlm_lock_resource *res, पूर्णांक flags);

/* will निकास holding res->spinlock, but may drop in function */
अटल अंतरभूत व्योम __dlm_रुको_on_lockres(काष्ठा dlm_lock_resource *res)
अणु
	__dlm_रुको_on_lockres_flags(res, (DLM_LOCK_RES_IN_PROGRESS|
				    	  DLM_LOCK_RES_RECOVERING|
					  DLM_LOCK_RES_RECOVERY_WAITING|
					  DLM_LOCK_RES_MIGRATING));
पूर्ण

व्योम __dlm_unlink_mle(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_master_list_entry *mle);
व्योम __dlm_insert_mle(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_master_list_entry *mle);

/* create/destroy slab caches */
पूर्णांक dlm_init_master_caches(व्योम);
व्योम dlm_destroy_master_caches(व्योम);

पूर्णांक dlm_init_lock_cache(व्योम);
व्योम dlm_destroy_lock_cache(व्योम);

पूर्णांक dlm_init_mle_cache(व्योम);
व्योम dlm_destroy_mle_cache(व्योम);

व्योम dlm_hb_event_notअगरy_attached(काष्ठा dlm_ctxt *dlm, पूर्णांक idx, पूर्णांक node_up);
पूर्णांक dlm_drop_lockres_ref(काष्ठा dlm_ctxt *dlm,
			 काष्ठा dlm_lock_resource *res);
व्योम dlm_clean_master_list(काष्ठा dlm_ctxt *dlm,
			   u8 dead_node);
व्योम dlm_क्रमce_मुक्त_mles(काष्ठा dlm_ctxt *dlm);
पूर्णांक dlm_lock_basts_flushed(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock *lock);
पूर्णांक __dlm_lockres_has_locks(काष्ठा dlm_lock_resource *res);
पूर्णांक __dlm_lockres_unused(काष्ठा dlm_lock_resource *res);

अटल अंतरभूत स्थिर अक्षर * dlm_lock_mode_name(पूर्णांक mode)
अणु
	चयन (mode) अणु
		हाल LKM_EXMODE:
			वापस "EX";
		हाल LKM_PRMODE:
			वापस "PR";
		हाल LKM_NLMODE:
			वापस "NL";
	पूर्ण
	वापस "UNKNOWN";
पूर्ण


अटल अंतरभूत पूर्णांक dlm_lock_compatible(पूर्णांक existing, पूर्णांक request)
अणु
	/* NO_LOCK compatible with all */
	अगर (request == LKM_NLMODE ||
	    existing == LKM_NLMODE)
		वापस 1;

	/* EX incompatible with all non-NO_LOCK */
	अगर (request == LKM_EXMODE)
		वापस 0;

	/* request must be PR, which is compatible with PR */
	अगर (existing == LKM_PRMODE)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dlm_lock_on_list(काष्ठा list_head *head,
				   काष्ठा dlm_lock *lock)
अणु
	काष्ठा dlm_lock *पंचांगplock;

	list_क्रम_each_entry(पंचांगplock, head, list) अणु
		अगर (पंचांगplock == lock)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


अटल अंतरभूत क्रमागत dlm_status dlm_err_to_dlm_status(पूर्णांक err)
अणु
	क्रमागत dlm_status ret;
	अगर (err == -ENOMEM)
		ret = DLM_SYSERR;
	अन्यथा अगर (err == -ETIMEDOUT || o2net_link_करोwn(err, शून्य))
		ret = DLM_NOLOCKMGR;
	अन्यथा अगर (err == -EINVAL)
		ret = DLM_BADPARAM;
	अन्यथा अगर (err == -ENAMETOOLONG)
		ret = DLM_IVBUFLEN;
	अन्यथा
		ret = DLM_BADARGS;
	वापस ret;
पूर्ण


अटल अंतरभूत व्योम dlm_node_iter_init(अचिन्हित दीर्घ *map,
				      काष्ठा dlm_node_iter *iter)
अणु
	स_नकल(iter->node_map, map, माप(iter->node_map));
	iter->curnode = -1;
पूर्ण

अटल अंतरभूत पूर्णांक dlm_node_iter_next(काष्ठा dlm_node_iter *iter)
अणु
	पूर्णांक bit;
	bit = find_next_bit(iter->node_map, O2NM_MAX_NODES, iter->curnode+1);
	अगर (bit >= O2NM_MAX_NODES) अणु
		iter->curnode = O2NM_MAX_NODES;
		वापस -ENOENT;
	पूर्ण
	iter->curnode = bit;
	वापस bit;
पूर्ण

अटल अंतरभूत व्योम dlm_set_lockres_owner(काष्ठा dlm_ctxt *dlm,
					 काष्ठा dlm_lock_resource *res,
					 u8 owner)
अणु
	निश्चित_spin_locked(&res->spinlock);

	res->owner = owner;
पूर्ण

अटल अंतरभूत व्योम dlm_change_lockres_owner(काष्ठा dlm_ctxt *dlm,
					    काष्ठा dlm_lock_resource *res,
					    u8 owner)
अणु
	निश्चित_spin_locked(&res->spinlock);

	अगर (owner != res->owner)
		dlm_set_lockres_owner(dlm, res, owner);
पूर्ण

#पूर्ण_अगर /* DLMCOMMON_H */
