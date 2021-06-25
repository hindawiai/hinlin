<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * Changes by Acxiom Corporation to add proc file handler क्रम pvfs2 client
 * parameters, Copyright Acxiom Corporation, 2005.
 *
 * See COPYING in top-level directory.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-debugfs.h"
#समावेश "orangefs-sysfs.h"

/* ORANGEFS_VERSION is a ./configure define */
#अगर_अघोषित ORANGEFS_VERSION
#घोषणा ORANGEFS_VERSION "upstream"
#पूर्ण_अगर

/*
 * global variables declared here
 */

काष्ठा orangefs_stats orangefs_stats;

/* the size of the hash tables क्रम ops in progress */
पूर्णांक hash_table_size = 509;

अटल uदीर्घ module_parm_debug_mask;
__u64 orangefs_gossip_debug_mask;
पूर्णांक op_समयout_secs = ORANGEFS_DEFAULT_OP_TIMEOUT_SECS;
पूर्णांक slot_समयout_secs = ORANGEFS_DEFAULT_SLOT_TIMEOUT_SECS;
पूर्णांक orangefs_cache_समयout_msecs = 500;
पूर्णांक orangefs_dcache_समयout_msecs = 50;
पूर्णांक orangefs_getattr_समयout_msecs = 50;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ORANGEFS Development Team");
MODULE_DESCRIPTION("The Linux Kernel VFS interface to ORANGEFS");
MODULE_PARM_DESC(module_parm_debug_mask, "debugging level (see orangefs-debug.h for values)");
MODULE_PARM_DESC(op_समयout_secs, "Operation timeout in seconds");
MODULE_PARM_DESC(slot_समयout_secs, "Slot timeout in seconds");
MODULE_PARM_DESC(hash_table_size,
		 "size of hash table for operations in progress");

अटल काष्ठा file_प्रणाली_type orangefs_fs_type = अणु
	.name = "pvfs2",
	.mount = orangefs_mount,
	.समाप्त_sb = orangefs_समाप्त_sb,
	.owner = THIS_MODULE,
पूर्ण;

module_param(hash_table_size, पूर्णांक, 0);
module_param(module_parm_debug_mask, uदीर्घ, 0644);
module_param(op_समयout_secs, पूर्णांक, 0);
module_param(slot_समयout_secs, पूर्णांक, 0);

/*
 * Blocks non-priority requests from being queued क्रम servicing.  This
 * could be used क्रम protecting the request list data काष्ठाure, but
 * क्रम now it's only being used to stall the op addition to the request
 * list
 */
DEFINE_MUTEX(orangefs_request_mutex);

/* hash table क्रम storing operations रुकोing क्रम matching करोwncall */
काष्ठा list_head *orangefs_htable_ops_in_progress;
DEFINE_SPINLOCK(orangefs_htable_ops_in_progress_lock);

/* list क्रम queueing upcall operations */
LIST_HEAD(orangefs_request_list);

/* used to protect the above orangefs_request_list */
DEFINE_SPINLOCK(orangefs_request_list_lock);

/* used क्रम incoming request notअगरication */
DECLARE_WAIT_QUEUE_HEAD(orangefs_request_list_रुकोq);

अटल पूर्णांक __init orangefs_init(व्योम)
अणु
	पूर्णांक ret;
	__u32 i = 0;

	अगर (op_समयout_secs < 0)
		op_समयout_secs = 0;

	अगर (slot_समयout_secs < 0)
		slot_समयout_secs = 0;

	/* initialize global book keeping data काष्ठाures */
	ret = op_cache_initialize();
	अगर (ret < 0)
		जाओ out;

	ret = orangefs_inode_cache_initialize();
	अगर (ret < 0)
		जाओ cleanup_op;

	orangefs_htable_ops_in_progress =
	    kसुस्मृति(hash_table_size, माप(काष्ठा list_head), GFP_KERNEL);
	अगर (!orangefs_htable_ops_in_progress) अणु
		ret = -ENOMEM;
		जाओ cleanup_inode;
	पूर्ण

	/* initialize a करोubly linked at each hash table index */
	क्रम (i = 0; i < hash_table_size; i++)
		INIT_LIST_HEAD(&orangefs_htable_ops_in_progress[i]);

	ret = fsid_key_table_initialize();
	अगर (ret < 0)
		जाओ cleanup_progress_table;

	/*
	 * Build the contents of /sys/kernel/debug/orangefs/debug-help
	 * from the keywords in the kernel keyword/mask array.
	 *
	 * The keywords in the client keyword/mask array are
	 * unknown at boot समय.
	 *
	 * orangefs_prepare_debugfs_help_string will be used again
	 * later to rebuild the debug-help-string after the client starts
	 * and passes aदीर्घ the needed info. The argument signअगरies
	 * which समय orangefs_prepare_debugfs_help_string is being
	 * called.
	 */
	ret = orangefs_prepare_debugfs_help_string(1);
	अगर (ret)
		जाओ cleanup_key_table;

	orangefs_debugfs_init(module_parm_debug_mask);

	ret = orangefs_sysfs_init();
	अगर (ret)
		जाओ sysfs_init_failed;

	/* Initialize the orangefsdev subप्रणाली. */
	ret = orangefs_dev_init();
	अगर (ret < 0) अणु
		gossip_err("%s: could not initialize device subsystem %d!\n",
			   __func__,
			   ret);
		जाओ cleanup_device;
	पूर्ण

	ret = रेजिस्टर_fileप्रणाली(&orangefs_fs_type);
	अगर (ret == 0) अणु
		pr_info("%s: module version %s loaded\n",
			__func__,
			ORANGEFS_VERSION);
		जाओ out;
	पूर्ण

	orangefs_sysfs_निकास();

cleanup_device:
	orangefs_dev_cleanup();

sysfs_init_failed:
	orangefs_debugfs_cleanup();

cleanup_key_table:
	fsid_key_table_finalize();

cleanup_progress_table:
	kमुक्त(orangefs_htable_ops_in_progress);

cleanup_inode:
	orangefs_inode_cache_finalize();

cleanup_op:
	op_cache_finalize();

out:
	वापस ret;
पूर्ण

अटल व्योम __निकास orangefs_निकास(व्योम)
अणु
	पूर्णांक i = 0;
	gossip_debug(GOSSIP_INIT_DEBUG, "orangefs: orangefs_exit called\n");

	unरेजिस्टर_fileप्रणाली(&orangefs_fs_type);
	orangefs_debugfs_cleanup();
	orangefs_sysfs_निकास();
	fsid_key_table_finalize();
	orangefs_dev_cleanup();
	BUG_ON(!list_empty(&orangefs_request_list));
	क्रम (i = 0; i < hash_table_size; i++)
		BUG_ON(!list_empty(&orangefs_htable_ops_in_progress[i]));

	orangefs_inode_cache_finalize();
	op_cache_finalize();

	kमुक्त(orangefs_htable_ops_in_progress);

	pr_info("orangefs: module version %s unloaded\n", ORANGEFS_VERSION);
पूर्ण

/*
 * What we करो in this function is to walk the list of operations
 * that are in progress in the hash table and mark them as purged as well.
 */
व्योम purge_inprogress_ops(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hash_table_size; i++) अणु
		काष्ठा orangefs_kernel_op_s *op;
		काष्ठा orangefs_kernel_op_s *next;

		spin_lock(&orangefs_htable_ops_in_progress_lock);
		list_क्रम_each_entry_safe(op,
					 next,
					 &orangefs_htable_ops_in_progress[i],
					 list) अणु
			set_op_state_purged(op);
			gossip_debug(GOSSIP_DEV_DEBUG,
				     "%s: op:%s: op_state:%d: process:%s:\n",
				     __func__,
				     get_opname_string(op),
				     op->op_state,
				     current->comm);
		पूर्ण
		spin_unlock(&orangefs_htable_ops_in_progress_lock);
	पूर्ण
पूर्ण

module_init(orangefs_init);
module_निकास(orangefs_निकास);
