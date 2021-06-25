<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _LINUX_BINDER_INTERNAL_H
#घोषणा _LINUX_BINDER_INTERNAL_H

#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/refcount.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/uidgid.h>
#समावेश <uapi/linux/android/binderfs.h>
#समावेश "binder_alloc.h"

काष्ठा binder_context अणु
	काष्ठा binder_node *binder_context_mgr_node;
	काष्ठा mutex context_mgr_node_lock;
	kuid_t binder_context_mgr_uid;
	स्थिर अक्षर *name;
पूर्ण;

/**
 * काष्ठा binder_device - inक्रमmation about a binder device node
 * @hlist:          list of binder devices (only used क्रम devices requested via
 *                  CONFIG_ANDROID_BINDER_DEVICES)
 * @miscdev:        inक्रमmation about a binder अक्षरacter device node
 * @context:        binder context inक्रमmation
 * @binderfs_inode: This is the inode of the root dentry of the super block
 *                  beदीर्घing to a binderfs mount.
 */
काष्ठा binder_device अणु
	काष्ठा hlist_node hlist;
	काष्ठा miscdevice miscdev;
	काष्ठा binder_context context;
	काष्ठा inode *binderfs_inode;
	refcount_t ref;
पूर्ण;

/**
 * binderfs_mount_opts - mount options क्रम binderfs
 * @max: maximum number of allocatable binderfs binder devices
 * @stats_mode: enable binder stats in binderfs.
 */
काष्ठा binderfs_mount_opts अणु
	पूर्णांक max;
	पूर्णांक stats_mode;
पूर्ण;

/**
 * binderfs_info - inक्रमmation about a binderfs mount
 * @ipc_ns:         The ipc namespace the binderfs mount beदीर्घs to.
 * @control_dentry: This records the dentry of this binderfs mount
 *                  binder-control device.
 * @root_uid:       uid that needs to be used when a new binder device is
 *                  created.
 * @root_gid:       gid that needs to be used when a new binder device is
 *                  created.
 * @mount_opts:     The mount options in use.
 * @device_count:   The current number of allocated binder devices.
 * @proc_log_dir:   Poपूर्णांकer to the directory dentry containing process-specअगरic
 *                  logs.
 */
काष्ठा binderfs_info अणु
	काष्ठा ipc_namespace *ipc_ns;
	काष्ठा dentry *control_dentry;
	kuid_t root_uid;
	kgid_t root_gid;
	काष्ठा binderfs_mount_opts mount_opts;
	पूर्णांक device_count;
	काष्ठा dentry *proc_log_dir;
पूर्ण;

बाह्य स्थिर काष्ठा file_operations binder_fops;

बाह्य अक्षर *binder_devices_param;

#अगर_घोषित CONFIG_ANDROID_BINDERFS
बाह्य bool is_binderfs_device(स्थिर काष्ठा inode *inode);
बाह्य काष्ठा dentry *binderfs_create_file(काष्ठा dentry *dir, स्थिर अक्षर *name,
					   स्थिर काष्ठा file_operations *fops,
					   व्योम *data);
बाह्य व्योम binderfs_हटाओ_file(काष्ठा dentry *dentry);
#अन्यथा
अटल अंतरभूत bool is_binderfs_device(स्थिर काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत काष्ठा dentry *binderfs_create_file(काष्ठा dentry *dir,
					   स्थिर अक्षर *name,
					   स्थिर काष्ठा file_operations *fops,
					   व्योम *data)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम binderfs_हटाओ_file(काष्ठा dentry *dentry) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ANDROID_BINDERFS
बाह्य पूर्णांक __init init_binderfs(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक __init init_binderfs(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक binder_stats_show(काष्ठा seq_file *m, व्योम *unused);
DEFINE_SHOW_ATTRIBUTE(binder_stats);

पूर्णांक binder_state_show(काष्ठा seq_file *m, व्योम *unused);
DEFINE_SHOW_ATTRIBUTE(binder_state);

पूर्णांक binder_transactions_show(काष्ठा seq_file *m, व्योम *unused);
DEFINE_SHOW_ATTRIBUTE(binder_transactions);

पूर्णांक binder_transaction_log_show(काष्ठा seq_file *m, व्योम *unused);
DEFINE_SHOW_ATTRIBUTE(binder_transaction_log);

काष्ठा binder_transaction_log_entry अणु
	पूर्णांक debug_id;
	पूर्णांक debug_id_करोne;
	पूर्णांक call_type;
	पूर्णांक from_proc;
	पूर्णांक from_thपढ़ो;
	पूर्णांक target_handle;
	पूर्णांक to_proc;
	पूर्णांक to_thपढ़ो;
	पूर्णांक to_node;
	पूर्णांक data_size;
	पूर्णांक offsets_size;
	पूर्णांक वापस_error_line;
	uपूर्णांक32_t वापस_error;
	uपूर्णांक32_t वापस_error_param;
	अक्षर context_name[BINDERFS_MAX_NAME + 1];
पूर्ण;

काष्ठा binder_transaction_log अणु
	atomic_t cur;
	bool full;
	काष्ठा binder_transaction_log_entry entry[32];
पूर्ण;

क्रमागत binder_stat_types अणु
	BINDER_STAT_PROC,
	BINDER_STAT_THREAD,
	BINDER_STAT_NODE,
	BINDER_STAT_REF,
	BINDER_STAT_DEATH,
	BINDER_STAT_TRANSACTION,
	BINDER_STAT_TRANSACTION_COMPLETE,
	BINDER_STAT_COUNT
पूर्ण;

काष्ठा binder_stats अणु
	atomic_t br[_IOC_NR(BR_ONEWAY_SPAM_SUSPECT) + 1];
	atomic_t bc[_IOC_NR(BC_REPLY_SG) + 1];
	atomic_t obj_created[BINDER_STAT_COUNT];
	atomic_t obj_deleted[BINDER_STAT_COUNT];
पूर्ण;

/**
 * काष्ठा binder_work - work enqueued on a worklist
 * @entry:             node enqueued on list
 * @type:              type of work to be perक्रमmed
 *
 * There are separate work lists क्रम proc, thपढ़ो, and node (async).
 */
काष्ठा binder_work अणु
	काष्ठा list_head entry;

	क्रमागत binder_work_type अणु
		BINDER_WORK_TRANSACTION = 1,
		BINDER_WORK_TRANSACTION_COMPLETE,
		BINDER_WORK_TRANSACTION_ONEWAY_SPAM_SUSPECT,
		BINDER_WORK_RETURN_ERROR,
		BINDER_WORK_NODE,
		BINDER_WORK_DEAD_BINDER,
		BINDER_WORK_DEAD_BINDER_AND_CLEAR,
		BINDER_WORK_CLEAR_DEATH_NOTIFICATION,
	पूर्ण type;
पूर्ण;

काष्ठा binder_error अणु
	काष्ठा binder_work work;
	uपूर्णांक32_t cmd;
पूर्ण;

/**
 * काष्ठा binder_node - binder node bookkeeping
 * @debug_id:             unique ID क्रम debugging
 *                        (invariant after initialized)
 * @lock:                 lock क्रम node fields
 * @work:                 worklist element क्रम node work
 *                        (रक्षित by @proc->inner_lock)
 * @rb_node:              element क्रम proc->nodes tree
 *                        (रक्षित by @proc->inner_lock)
 * @dead_node:            element क्रम binder_dead_nodes list
 *                        (रक्षित by binder_dead_nodes_lock)
 * @proc:                 binder_proc that owns this node
 *                        (invariant after initialized)
 * @refs:                 list of references on this node
 *                        (रक्षित by @lock)
 * @पूर्णांकernal_strong_refs: used to take strong references when
 *                        initiating a transaction
 *                        (रक्षित by @proc->inner_lock अगर @proc
 *                        and by @lock)
 * @local_weak_refs:      weak user refs from local process
 *                        (रक्षित by @proc->inner_lock अगर @proc
 *                        and by @lock)
 * @local_strong_refs:    strong user refs from local process
 *                        (रक्षित by @proc->inner_lock अगर @proc
 *                        and by @lock)
 * @पंचांगp_refs:             temporary kernel refs
 *                        (रक्षित by @proc->inner_lock जबतक @proc
 *                        is valid, and by binder_dead_nodes_lock
 *                        अगर @proc is शून्य. During inc/dec and node release
 *                        it is also रक्षित by @lock to provide safety
 *                        as the node dies and @proc becomes शून्य)
 * @ptr:                  userspace poपूर्णांकer क्रम node
 *                        (invariant, no lock needed)
 * @cookie:               userspace cookie क्रम node
 *                        (invariant, no lock needed)
 * @has_strong_ref:       userspace notअगरied of strong ref
 *                        (रक्षित by @proc->inner_lock अगर @proc
 *                        and by @lock)
 * @pending_strong_ref:   userspace has acked notअगरication of strong ref
 *                        (रक्षित by @proc->inner_lock अगर @proc
 *                        and by @lock)
 * @has_weak_ref:         userspace notअगरied of weak ref
 *                        (रक्षित by @proc->inner_lock अगर @proc
 *                        and by @lock)
 * @pending_weak_ref:     userspace has acked notअगरication of weak ref
 *                        (रक्षित by @proc->inner_lock अगर @proc
 *                        and by @lock)
 * @has_async_transaction: async transaction to node in progress
 *                        (रक्षित by @lock)
 * @accept_fds:           file descriptor operations supported क्रम node
 *                        (invariant after initialized)
 * @min_priority:         minimum scheduling priority
 *                        (invariant after initialized)
 * @txn_security_ctx:     require sender's security context
 *                        (invariant after initialized)
 * @async_toकरो:           list of async work items
 *                        (रक्षित by @proc->inner_lock)
 *
 * Bookkeeping काष्ठाure क्रम binder nodes.
 */
काष्ठा binder_node अणु
	पूर्णांक debug_id;
	spinlock_t lock;
	काष्ठा binder_work work;
	जोड़ अणु
		काष्ठा rb_node rb_node;
		काष्ठा hlist_node dead_node;
	पूर्ण;
	काष्ठा binder_proc *proc;
	काष्ठा hlist_head refs;
	पूर्णांक पूर्णांकernal_strong_refs;
	पूर्णांक local_weak_refs;
	पूर्णांक local_strong_refs;
	पूर्णांक पंचांगp_refs;
	binder_uपूर्णांकptr_t ptr;
	binder_uपूर्णांकptr_t cookie;
	काष्ठा अणु
		/*
		 * bitfield elements रक्षित by
		 * proc inner_lock
		 */
		u8 has_strong_ref:1;
		u8 pending_strong_ref:1;
		u8 has_weak_ref:1;
		u8 pending_weak_ref:1;
	पूर्ण;
	काष्ठा अणु
		/*
		 * invariant after initialization
		 */
		u8 accept_fds:1;
		u8 txn_security_ctx:1;
		u8 min_priority;
	पूर्ण;
	bool has_async_transaction;
	काष्ठा list_head async_toकरो;
पूर्ण;

काष्ठा binder_ref_death अणु
	/**
	 * @work: worklist element क्रम death notअगरications
	 *        (रक्षित by inner_lock of the proc that
	 *        this ref beदीर्घs to)
	 */
	काष्ठा binder_work work;
	binder_uपूर्णांकptr_t cookie;
पूर्ण;

/**
 * काष्ठा binder_ref_data - binder_ref counts and id
 * @debug_id:        unique ID क्रम the ref
 * @desc:            unique userspace handle क्रम ref
 * @strong:          strong ref count (debugging only अगर not locked)
 * @weak:            weak ref count (debugging only अगर not locked)
 *
 * Structure to hold ref count and ref id inक्रमmation. Since
 * the actual ref can only be accessed with a lock, this काष्ठाure
 * is used to वापस inक्रमmation about the ref to callers of
 * ref inc/dec functions.
 */
काष्ठा binder_ref_data अणु
	पूर्णांक debug_id;
	uपूर्णांक32_t desc;
	पूर्णांक strong;
	पूर्णांक weak;
पूर्ण;

/**
 * काष्ठा binder_ref - काष्ठा to track references on nodes
 * @data:        binder_ref_data containing id, handle, and current refcounts
 * @rb_node_desc: node क्रम lookup by @data.desc in proc's rb_tree
 * @rb_node_node: node क्रम lookup by @node in proc's rb_tree
 * @node_entry:  list entry क्रम node->refs list in target node
 *               (रक्षित by @node->lock)
 * @proc:        binder_proc containing ref
 * @node:        binder_node of target node. When cleaning up a
 *               ref क्रम deletion in binder_cleanup_ref, a non-शून्य
 *               @node indicates the node must be मुक्तd
 * @death:       poपूर्णांकer to death notअगरication (ref_death) अगर requested
 *               (रक्षित by @node->lock)
 *
 * Structure to track references from procA to target node (on procB). This
 * काष्ठाure is unsafe to access without holding @proc->outer_lock.
 */
काष्ठा binder_ref अणु
	/* Lookups needed: */
	/*   node + proc => ref (transaction) */
	/*   desc + proc => ref (transaction, inc/dec ref) */
	/*   node => refs + procs (proc निकास) */
	काष्ठा binder_ref_data data;
	काष्ठा rb_node rb_node_desc;
	काष्ठा rb_node rb_node_node;
	काष्ठा hlist_node node_entry;
	काष्ठा binder_proc *proc;
	काष्ठा binder_node *node;
	काष्ठा binder_ref_death *death;
पूर्ण;

/**
 * काष्ठा binder_proc - binder process bookkeeping
 * @proc_node:            element क्रम binder_procs list
 * @thपढ़ोs:              rbtree of binder_thपढ़ोs in this proc
 *                        (रक्षित by @inner_lock)
 * @nodes:                rbtree of binder nodes associated with
 *                        this proc ordered by node->ptr
 *                        (रक्षित by @inner_lock)
 * @refs_by_desc:         rbtree of refs ordered by ref->desc
 *                        (रक्षित by @outer_lock)
 * @refs_by_node:         rbtree of refs ordered by ref->node
 *                        (रक्षित by @outer_lock)
 * @रुकोing_thपढ़ोs:      thपढ़ोs currently रुकोing क्रम proc work
 *                        (रक्षित by @inner_lock)
 * @pid                   PID of group_leader of process
 *                        (invariant after initialized)
 * @tsk                   task_काष्ठा क्रम group_leader of process
 *                        (invariant after initialized)
 * @deferred_work_node:   element क्रम binder_deferred_list
 *                        (रक्षित by binder_deferred_lock)
 * @deferred_work:        biपंचांगap of deferred work to perक्रमm
 *                        (रक्षित by binder_deferred_lock)
 * @outstanding_txns:     number of transactions to be transmitted beक्रमe
 *                        processes in मुक्तze_रुको are woken up
 *                        (रक्षित by @inner_lock)
 * @is_dead:              process is dead and aरुकोing मुक्त
 *                        when outstanding transactions are cleaned up
 *                        (रक्षित by @inner_lock)
 * @is_frozen:            process is frozen and unable to service
 *                        binder transactions
 *                        (रक्षित by @inner_lock)
 * @sync_recv:            process received sync transactions since last frozen
 *                        (रक्षित by @inner_lock)
 * @async_recv:           process received async transactions since last frozen
 *                        (रक्षित by @inner_lock)
 * @मुक्तze_रुको:          रुकोqueue of processes रुकोing क्रम all outstanding
 *                        transactions to be processed
 *                        (रक्षित by @inner_lock)
 * @toकरो:                 list of work क्रम this process
 *                        (रक्षित by @inner_lock)
 * @stats:                per-process binder statistics
 *                        (atomics, no lock needed)
 * @delivered_death:      list of delivered death notअगरication
 *                        (रक्षित by @inner_lock)
 * @max_thपढ़ोs:          cap on number of binder thपढ़ोs
 *                        (रक्षित by @inner_lock)
 * @requested_thपढ़ोs:    number of binder thपढ़ोs requested but not
 *                        yet started. In current implementation, can
 *                        only be 0 or 1.
 *                        (रक्षित by @inner_lock)
 * @requested_thपढ़ोs_started: number binder thपढ़ोs started
 *                        (रक्षित by @inner_lock)
 * @पंचांगp_ref:              temporary reference to indicate proc is in use
 *                        (रक्षित by @inner_lock)
 * @शेष_priority:     शेष scheduler priority
 *                        (invariant after initialized)
 * @debugfs_entry:        debugfs node
 * @alloc:                binder allocator bookkeeping
 * @context:              binder_context क्रम this proc
 *                        (invariant after initialized)
 * @inner_lock:           can nest under outer_lock and/or node lock
 * @outer_lock:           no nesting under innor or node lock
 *                        Lock order: 1) outer, 2) node, 3) inner
 * @binderfs_entry:       process-specअगरic binderfs log file
 * @oneway_spam_detection_enabled: process enabled oneway spam detection
 *                        or not
 *
 * Bookkeeping काष्ठाure क्रम binder processes
 */
काष्ठा binder_proc अणु
	काष्ठा hlist_node proc_node;
	काष्ठा rb_root thपढ़ोs;
	काष्ठा rb_root nodes;
	काष्ठा rb_root refs_by_desc;
	काष्ठा rb_root refs_by_node;
	काष्ठा list_head रुकोing_thपढ़ोs;
	पूर्णांक pid;
	काष्ठा task_काष्ठा *tsk;
	काष्ठा hlist_node deferred_work_node;
	पूर्णांक deferred_work;
	पूर्णांक outstanding_txns;
	bool is_dead;
	bool is_frozen;
	bool sync_recv;
	bool async_recv;
	रुको_queue_head_t मुक्तze_रुको;

	काष्ठा list_head toकरो;
	काष्ठा binder_stats stats;
	काष्ठा list_head delivered_death;
	पूर्णांक max_thपढ़ोs;
	पूर्णांक requested_thपढ़ोs;
	पूर्णांक requested_thपढ़ोs_started;
	पूर्णांक पंचांगp_ref;
	दीर्घ शेष_priority;
	काष्ठा dentry *debugfs_entry;
	काष्ठा binder_alloc alloc;
	काष्ठा binder_context *context;
	spinlock_t inner_lock;
	spinlock_t outer_lock;
	काष्ठा dentry *binderfs_entry;
	bool oneway_spam_detection_enabled;
पूर्ण;

/**
 * काष्ठा binder_thपढ़ो - binder thपढ़ो bookkeeping
 * @proc:                 binder process क्रम this thपढ़ो
 *                        (invariant after initialization)
 * @rb_node:              element क्रम proc->thपढ़ोs rbtree
 *                        (रक्षित by @proc->inner_lock)
 * @रुकोing_thपढ़ो_node:  element क्रम @proc->रुकोing_thपढ़ोs list
 *                        (रक्षित by @proc->inner_lock)
 * @pid:                  PID क्रम this thपढ़ो
 *                        (invariant after initialization)
 * @looper:               biपंचांगap of looping state
 *                        (only accessed by this thपढ़ो)
 * @looper_needs_वापस:  looping thपढ़ो needs to निकास driver
 *                        (no lock needed)
 * @transaction_stack:    stack of in-progress transactions क्रम this thपढ़ो
 *                        (रक्षित by @proc->inner_lock)
 * @toकरो:                 list of work to करो क्रम this thपढ़ो
 *                        (रक्षित by @proc->inner_lock)
 * @process_toकरो:         whether work in @toकरो should be processed
 *                        (रक्षित by @proc->inner_lock)
 * @वापस_error:         transaction errors reported by this thपढ़ो
 *                        (only accessed by this thपढ़ो)
 * @reply_error:          transaction errors reported by target thपढ़ो
 *                        (रक्षित by @proc->inner_lock)
 * @रुको:                 रुको queue क्रम thपढ़ो work
 * @stats:                per-thपढ़ो statistics
 *                        (atomics, no lock needed)
 * @पंचांगp_ref:              temporary reference to indicate thपढ़ो is in use
 *                        (atomic since @proc->inner_lock cannot
 *                        always be acquired)
 * @is_dead:              thपढ़ो is dead and aरुकोing मुक्त
 *                        when outstanding transactions are cleaned up
 *                        (रक्षित by @proc->inner_lock)
 *
 * Bookkeeping काष्ठाure क्रम binder thपढ़ोs.
 */
काष्ठा binder_thपढ़ो अणु
	काष्ठा binder_proc *proc;
	काष्ठा rb_node rb_node;
	काष्ठा list_head रुकोing_thपढ़ो_node;
	पूर्णांक pid;
	पूर्णांक looper;              /* only modअगरied by this thपढ़ो */
	bool looper_need_वापस; /* can be written by other thपढ़ो */
	काष्ठा binder_transaction *transaction_stack;
	काष्ठा list_head toकरो;
	bool process_toकरो;
	काष्ठा binder_error वापस_error;
	काष्ठा binder_error reply_error;
	रुको_queue_head_t रुको;
	काष्ठा binder_stats stats;
	atomic_t पंचांगp_ref;
	bool is_dead;
पूर्ण;

/**
 * काष्ठा binder_txn_fd_fixup - transaction fd fixup list element
 * @fixup_entry:          list entry
 * @file:                 काष्ठा file to be associated with new fd
 * @offset:               offset in buffer data to this fixup
 *
 * List element क्रम fd fixups in a transaction. Since file
 * descriptors need to be allocated in the context of the
 * target process, we pass each fd to be processed in this
 * काष्ठा.
 */
काष्ठा binder_txn_fd_fixup अणु
	काष्ठा list_head fixup_entry;
	काष्ठा file *file;
	माप_प्रकार offset;
पूर्ण;

काष्ठा binder_transaction अणु
	पूर्णांक debug_id;
	काष्ठा binder_work work;
	काष्ठा binder_thपढ़ो *from;
	काष्ठा binder_transaction *from_parent;
	काष्ठा binder_proc *to_proc;
	काष्ठा binder_thपढ़ो *to_thपढ़ो;
	काष्ठा binder_transaction *to_parent;
	अचिन्हित need_reply:1;
	/* अचिन्हित is_dead:1; */       /* not used at the moment */

	काष्ठा binder_buffer *buffer;
	अचिन्हित पूर्णांक    code;
	अचिन्हित पूर्णांक    flags;
	दीर्घ    priority;
	दीर्घ    saved_priority;
	kuid_t  sender_euid;
	काष्ठा list_head fd_fixups;
	binder_uपूर्णांकptr_t security_ctx;
	/**
	 * @lock:  protects @from, @to_proc, and @to_thपढ़ो
	 *
	 * @from, @to_proc, and @to_thपढ़ो can be set to शून्य
	 * during thपढ़ो tearकरोwn
	 */
	spinlock_t lock;
पूर्ण;

/**
 * काष्ठा binder_object - जोड़ of flat binder object types
 * @hdr:   generic object header
 * @fbo:   binder object (nodes and refs)
 * @fकरो:   file descriptor object
 * @bbo:   binder buffer poपूर्णांकer
 * @fdao:  file descriptor array
 *
 * Used क्रम type-independent object copies
 */
काष्ठा binder_object अणु
	जोड़ अणु
		काष्ठा binder_object_header hdr;
		काष्ठा flat_binder_object fbo;
		काष्ठा binder_fd_object fकरो;
		काष्ठा binder_buffer_object bbo;
		काष्ठा binder_fd_array_object fdao;
	पूर्ण;
पूर्ण;

बाह्य काष्ठा binder_transaction_log binder_transaction_log;
बाह्य काष्ठा binder_transaction_log binder_transaction_log_failed;
#पूर्ण_अगर /* _LINUX_BINDER_INTERNAL_H */
