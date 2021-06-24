<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_CTREE_H
#घोषणा BTRFS_CTREE_H

#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/fs.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/completion.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <trace/events/btrfs.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/btrfs.h>
#समावेश <linux/btrfs_tree.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/security.h>
#समावेश <linux/sizes.h>
#समावेश <linux/dynamic_debug.h>
#समावेश <linux/refcount.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/iomap.h>
#समावेश "extent-io-tree.h"
#समावेश "extent_io.h"
#समावेश "extent_map.h"
#समावेश "async-thread.h"
#समावेश "block-rsv.h"
#समावेश "locking.h"

काष्ठा btrfs_trans_handle;
काष्ठा btrfs_transaction;
काष्ठा btrfs_pending_snapshot;
काष्ठा btrfs_delayed_ref_root;
काष्ठा btrfs_space_info;
काष्ठा btrfs_block_group;
बाह्य काष्ठा kmem_cache *btrfs_trans_handle_cachep;
बाह्य काष्ठा kmem_cache *btrfs_bit_radix_cachep;
बाह्य काष्ठा kmem_cache *btrfs_path_cachep;
बाह्य काष्ठा kmem_cache *btrfs_मुक्त_space_cachep;
बाह्य काष्ठा kmem_cache *btrfs_मुक्त_space_biपंचांगap_cachep;
काष्ठा btrfs_ordered_sum;
काष्ठा btrfs_ref;

#घोषणा BTRFS_MAGIC 0x4D5F53665248425FULL /* ascii _BHRfS_M, no null */

/*
 * Maximum number of mirrors that can be available क्रम all profiles counting
 * the target device of dev-replace as one. During an active device replace
 * procedure, the target device of the copy operation is a mirror क्रम the
 * fileप्रणाली data as well that can be used to पढ़ो data in order to repair
 * पढ़ो errors on other disks.
 *
 * Current value is derived from RAID1C4 with 4 copies.
 */
#घोषणा BTRFS_MAX_MIRRORS (4 + 1)

#घोषणा BTRFS_MAX_LEVEL 8

#घोषणा BTRFS_OLDEST_GENERATION	0ULL

/*
 * we can actually store much bigger names, but lets not confuse the rest
 * of linux
 */
#घोषणा BTRFS_NAME_LEN 255

/*
 * Theoretical limit is larger, but we keep this करोwn to a sane
 * value. That should limit greatly the possibility of collisions on
 * inode ref items.
 */
#घोषणा BTRFS_LINK_MAX 65535U

#घोषणा BTRFS_EMPTY_सूची_SIZE 0

/* ioprio of पढ़ोahead is set to idle */
#घोषणा BTRFS_IOPRIO_READA (IOPRIO_PRIO_VALUE(IOPRIO_CLASS_IDLE, 0))

#घोषणा BTRFS_सूचीTY_METADATA_THRESH	SZ_32M

/*
 * Use large batch size to reduce overhead of metadata updates.  On the पढ़ोer
 * side, we only पढ़ो it when we are बंद to ENOSPC and the पढ़ो overhead is
 * mostly related to the number of CPUs, so it is OK to use arbitrary large
 * value here.
 */
#घोषणा BTRFS_TOTAL_BYTES_PINNED_BATCH	SZ_128M

#घोषणा BTRFS_MAX_EXTENT_SIZE SZ_128M

/*
 * Deltas are an effective way to populate global statistics.  Give macro names
 * to make it clear what we're करोing.  An example is discard_extents in
 * btrfs_मुक्त_space_ctl.
 */
#घोषणा BTRFS_STAT_NR_ENTRIES	2
#घोषणा BTRFS_STAT_CURR		0
#घोषणा BTRFS_STAT_PREV		1

/*
 * Count how many BTRFS_MAX_EXTENT_SIZE cover the @size
 */
अटल अंतरभूत u32 count_max_extents(u64 size)
अणु
	वापस भाग_u64(size + BTRFS_MAX_EXTENT_SIZE - 1, BTRFS_MAX_EXTENT_SIZE);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ btrfs_chunk_item_size(पूर्णांक num_stripes)
अणु
	BUG_ON(num_stripes == 0);
	वापस माप(काष्ठा btrfs_chunk) +
		माप(काष्ठा btrfs_stripe) * (num_stripes - 1);
पूर्ण

/*
 * Runसमय (in-memory) states of fileप्रणाली
 */
क्रमागत अणु
	/* Global indicator of serious fileप्रणाली errors */
	BTRFS_FS_STATE_ERROR,
	/*
	 * Fileप्रणाली is being remounted, allow to skip some operations, like
	 * defrag
	 */
	BTRFS_FS_STATE_REMOUNTING,
	/* Fileप्रणाली in RO mode */
	BTRFS_FS_STATE_RO,
	/* Track अगर a transaction पात has been reported on this fileप्रणाली */
	BTRFS_FS_STATE_TRANS_ABORTED,
	/*
	 * Bio operations should be blocked on this fileप्रणाली because a source
	 * or target device is being destroyed as part of a device replace
	 */
	BTRFS_FS_STATE_DEV_REPLACING,
	/* The btrfs_fs_info created क्रम self-tests */
	BTRFS_FS_STATE_DUMMY_FS_INFO,
पूर्ण;

#घोषणा BTRFS_BACKREF_REV_MAX		256
#घोषणा BTRFS_BACKREF_REV_SHIFT		56
#घोषणा BTRFS_BACKREF_REV_MASK		(((u64)BTRFS_BACKREF_REV_MAX - 1) << \
					 BTRFS_BACKREF_REV_SHIFT)

#घोषणा BTRFS_OLD_BACKREF_REV		0
#घोषणा BTRFS_MIXED_BACKREF_REV		1

/*
 * every tree block (leaf or node) starts with this header.
 */
काष्ठा btrfs_header अणु
	/* these first four must match the super block */
	u8 csum[BTRFS_CSUM_SIZE];
	u8 fsid[BTRFS_FSID_SIZE]; /* FS specअगरic uuid */
	__le64 bytenr; /* which block this node is supposed to live in */
	__le64 flags;

	/* allowed to be dअगरferent from the super from here on करोwn */
	u8 chunk_tree_uuid[BTRFS_UUID_SIZE];
	__le64 generation;
	__le64 owner;
	__le32 nritems;
	u8 level;
पूर्ण __attribute__ ((__packed__));

/*
 * this is a very generous portion of the super block, giving us
 * room to translate 14 chunks with 3 stripes each.
 */
#घोषणा BTRFS_SYSTEM_CHUNK_ARRAY_SIZE 2048

/*
 * just in हाल we somehow lose the roots and are not able to mount,
 * we store an array of the roots from previous transactions
 * in the super.
 */
#घोषणा BTRFS_NUM_BACKUP_ROOTS 4
काष्ठा btrfs_root_backup अणु
	__le64 tree_root;
	__le64 tree_root_gen;

	__le64 chunk_root;
	__le64 chunk_root_gen;

	__le64 extent_root;
	__le64 extent_root_gen;

	__le64 fs_root;
	__le64 fs_root_gen;

	__le64 dev_root;
	__le64 dev_root_gen;

	__le64 csum_root;
	__le64 csum_root_gen;

	__le64 total_bytes;
	__le64 bytes_used;
	__le64 num_devices;
	/* future */
	__le64 unused_64[4];

	u8 tree_root_level;
	u8 chunk_root_level;
	u8 extent_root_level;
	u8 fs_root_level;
	u8 dev_root_level;
	u8 csum_root_level;
	/* future and to align */
	u8 unused_8[10];
पूर्ण __attribute__ ((__packed__));

/*
 * the super block basically lists the मुख्य trees of the FS
 * it currently lacks any block count etc etc
 */
काष्ठा btrfs_super_block अणु
	/* the first 4 fields must match काष्ठा btrfs_header */
	u8 csum[BTRFS_CSUM_SIZE];
	/* FS specअगरic UUID, visible to user */
	u8 fsid[BTRFS_FSID_SIZE];
	__le64 bytenr; /* this block number */
	__le64 flags;

	/* allowed to be dअगरferent from the btrfs_header from here own करोwn */
	__le64 magic;
	__le64 generation;
	__le64 root;
	__le64 chunk_root;
	__le64 log_root;

	/* this will help find the new super based on the log root */
	__le64 log_root_transid;
	__le64 total_bytes;
	__le64 bytes_used;
	__le64 root_dir_objectid;
	__le64 num_devices;
	__le32 sectorsize;
	__le32 nodesize;
	__le32 __unused_leafsize;
	__le32 stripesize;
	__le32 sys_chunk_array_size;
	__le64 chunk_root_generation;
	__le64 compat_flags;
	__le64 compat_ro_flags;
	__le64 incompat_flags;
	__le16 csum_type;
	u8 root_level;
	u8 chunk_root_level;
	u8 log_root_level;
	काष्ठा btrfs_dev_item dev_item;

	अक्षर label[BTRFS_LABEL_SIZE];

	__le64 cache_generation;
	__le64 uuid_tree_generation;

	/* the UUID written पूर्णांकo btree blocks */
	u8 metadata_uuid[BTRFS_FSID_SIZE];

	/* future expansion */
	__le64 reserved[28];
	u8 sys_chunk_array[BTRFS_SYSTEM_CHUNK_ARRAY_SIZE];
	काष्ठा btrfs_root_backup super_roots[BTRFS_NUM_BACKUP_ROOTS];
पूर्ण __attribute__ ((__packed__));

/*
 * Compat flags that we support.  If any incompat flags are set other than the
 * ones specअगरied below then we will fail to mount
 */
#घोषणा BTRFS_FEATURE_COMPAT_SUPP		0ULL
#घोषणा BTRFS_FEATURE_COMPAT_SAFE_SET		0ULL
#घोषणा BTRFS_FEATURE_COMPAT_SAFE_CLEAR		0ULL

#घोषणा BTRFS_FEATURE_COMPAT_RO_SUPP			\
	(BTRFS_FEATURE_COMPAT_RO_FREE_SPACE_TREE |	\
	 BTRFS_FEATURE_COMPAT_RO_FREE_SPACE_TREE_VALID)

#घोषणा BTRFS_FEATURE_COMPAT_RO_SAFE_SET	0ULL
#घोषणा BTRFS_FEATURE_COMPAT_RO_SAFE_CLEAR	0ULL

#घोषणा BTRFS_FEATURE_INCOMPAT_SUPP			\
	(BTRFS_FEATURE_INCOMPAT_MIXED_BACKREF |		\
	 BTRFS_FEATURE_INCOMPAT_DEFAULT_SUBVOL |	\
	 BTRFS_FEATURE_INCOMPAT_MIXED_GROUPS |		\
	 BTRFS_FEATURE_INCOMPAT_BIG_METADATA |		\
	 BTRFS_FEATURE_INCOMPAT_COMPRESS_LZO |		\
	 BTRFS_FEATURE_INCOMPAT_COMPRESS_ZSTD |		\
	 BTRFS_FEATURE_INCOMPAT_RAID56 |		\
	 BTRFS_FEATURE_INCOMPAT_EXTENDED_IREF |		\
	 BTRFS_FEATURE_INCOMPAT_SKINNY_METADATA |	\
	 BTRFS_FEATURE_INCOMPAT_NO_HOLES	|	\
	 BTRFS_FEATURE_INCOMPAT_METADATA_UUID	|	\
	 BTRFS_FEATURE_INCOMPAT_RAID1C34	|	\
	 BTRFS_FEATURE_INCOMPAT_ZONED)

#घोषणा BTRFS_FEATURE_INCOMPAT_SAFE_SET			\
	(BTRFS_FEATURE_INCOMPAT_EXTENDED_IREF)
#घोषणा BTRFS_FEATURE_INCOMPAT_SAFE_CLEAR		0ULL

/*
 * A leaf is full of items. offset and size tell us where to find
 * the item in the leaf (relative to the start of the data area)
 */
काष्ठा btrfs_item अणु
	काष्ठा btrfs_disk_key key;
	__le32 offset;
	__le32 size;
पूर्ण __attribute__ ((__packed__));

/*
 * leaves have an item area and a data area:
 * [item0, item1....itemN] [मुक्त space] [dataN...data1, data0]
 *
 * The data is separate from the items to get the keys बंदr together
 * during searches.
 */
काष्ठा btrfs_leaf अणु
	काष्ठा btrfs_header header;
	काष्ठा btrfs_item items[];
पूर्ण __attribute__ ((__packed__));

/*
 * all non-leaf blocks are nodes, they hold only keys and poपूर्णांकers to
 * other blocks
 */
काष्ठा btrfs_key_ptr अणु
	काष्ठा btrfs_disk_key key;
	__le64 blockptr;
	__le64 generation;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_node अणु
	काष्ठा btrfs_header header;
	काष्ठा btrfs_key_ptr ptrs[];
पूर्ण __attribute__ ((__packed__));

/* Read ahead values क्रम काष्ठा btrfs_path.पढ़ोa */
क्रमागत अणु
	READA_NONE,
	READA_BACK,
	READA_FORWARD,
	/*
	 * Similar to READA_FORWARD but unlike it:
	 *
	 * 1) It will trigger पढ़ोahead even क्रम leaves that are not बंद to
	 *    each other on disk;
	 * 2) It also triggers पढ़ोahead क्रम nodes;
	 * 3) During a search, even when a node or leaf is alपढ़ोy in memory, it
	 *    will still trigger पढ़ोahead क्रम other nodes and leaves that follow
	 *    it.
	 *
	 * This is meant to be used only when we know we are iterating over the
	 * entire tree or a very large part of it.
	 */
	READA_FORWARD_ALWAYS,
पूर्ण;

/*
 * btrfs_paths remember the path taken from the root करोwn to the leaf.
 * level 0 is always the leaf, and nodes[1...BTRFS_MAX_LEVEL] will poपूर्णांक
 * to any other levels that are present.
 *
 * The slots array records the index of the item or block poपूर्णांकer
 * used जबतक walking the tree.
 */
काष्ठा btrfs_path अणु
	काष्ठा extent_buffer *nodes[BTRFS_MAX_LEVEL];
	पूर्णांक slots[BTRFS_MAX_LEVEL];
	/* अगर there is real range locking, this locks field will change */
	u8 locks[BTRFS_MAX_LEVEL];
	u8 पढ़ोa;
	/* keep some upper locks as we walk करोwn */
	u8 lowest_level;

	/*
	 * set by btrfs_split_item, tells search_slot to keep all locks
	 * and to क्रमce calls to keep space in the nodes
	 */
	अचिन्हित पूर्णांक search_क्रम_split:1;
	अचिन्हित पूर्णांक keep_locks:1;
	अचिन्हित पूर्णांक skip_locking:1;
	अचिन्हित पूर्णांक search_commit_root:1;
	अचिन्हित पूर्णांक need_commit_sem:1;
	अचिन्हित पूर्णांक skip_release_on_error:1;
	/*
	 * Indicate that new item (btrfs_search_slot) is extending alपढ़ोy
	 * existing item and ins_len contains only the data size and not item
	 * header (ie. माप(काष्ठा btrfs_item) is not included).
	 */
	अचिन्हित पूर्णांक search_क्रम_extension:1;
पूर्ण;
#घोषणा BTRFS_MAX_EXTENT_ITEM_SIZE(r) ((BTRFS_LEAF_DATA_SIZE(r->fs_info) >> 4) - \
					माप(काष्ठा btrfs_item))
काष्ठा btrfs_dev_replace अणु
	u64 replace_state;	/* see #घोषणा above */
	समय64_t समय_started;	/* seconds since 1-Jan-1970 */
	समय64_t समय_stopped;	/* seconds since 1-Jan-1970 */
	atomic64_t num_ग_लिखो_errors;
	atomic64_t num_uncorrectable_पढ़ो_errors;

	u64 cursor_left;
	u64 committed_cursor_left;
	u64 cursor_left_last_ग_लिखो_of_item;
	u64 cursor_right;

	u64 cont_पढ़ोing_from_srcdev_mode;	/* see #घोषणा above */

	पूर्णांक is_valid;
	पूर्णांक item_needs_ग_लिखोback;
	काष्ठा btrfs_device *srcdev;
	काष्ठा btrfs_device *tgtdev;

	काष्ठा mutex lock_finishing_cancel_unmount;
	काष्ठा rw_semaphore rwsem;

	काष्ठा btrfs_scrub_progress scrub_progress;

	काष्ठा percpu_counter bio_counter;
	रुको_queue_head_t replace_रुको;
पूर्ण;

/*
 * मुक्त clusters are used to claim मुक्त space in relatively large chunks,
 * allowing us to करो less seeky ग_लिखोs. They are used क्रम all metadata
 * allocations. In ssd_spपढ़ो mode they are also used क्रम data allocations.
 */
काष्ठा btrfs_मुक्त_cluster अणु
	spinlock_t lock;
	spinlock_t refill_lock;
	काष्ठा rb_root root;

	/* largest extent in this cluster */
	u64 max_size;

	/* first extent starting offset */
	u64 winकरोw_start;

	/* We did a full search and couldn't create a cluster */
	bool fragmented;

	काष्ठा btrfs_block_group *block_group;
	/*
	 * when a cluster is allocated from a block group, we put the
	 * cluster onto a list in the block group so that it can
	 * be मुक्तd beक्रमe the block group is मुक्तd.
	 */
	काष्ठा list_head block_group_list;
पूर्ण;

क्रमागत btrfs_caching_type अणु
	BTRFS_CACHE_NO,
	BTRFS_CACHE_STARTED,
	BTRFS_CACHE_FAST,
	BTRFS_CACHE_FINISHED,
	BTRFS_CACHE_ERROR,
पूर्ण;

/*
 * Tree to record all locked full stripes of a RAID5/6 block group
 */
काष्ठा btrfs_full_stripe_locks_tree अणु
	काष्ठा rb_root root;
	काष्ठा mutex lock;
पूर्ण;

/* Discard control. */
/*
 * Async discard uses multiple lists to dअगरferentiate the discard filter
 * parameters.  Index 0 is क्रम completely मुक्त block groups where we need to
 * ensure the entire block group is trimmed without being lossy.  Indices
 * afterwards represent monotonically decreasing discard filter sizes to
 * prioritize what should be discarded next.
 */
#घोषणा BTRFS_NR_DISCARD_LISTS		3
#घोषणा BTRFS_DISCARD_INDEX_UNUSED	0
#घोषणा BTRFS_DISCARD_INDEX_START	1

काष्ठा btrfs_discard_ctl अणु
	काष्ठा workqueue_काष्ठा *discard_workers;
	काष्ठा delayed_work work;
	spinlock_t lock;
	काष्ठा btrfs_block_group *block_group;
	काष्ठा list_head discard_list[BTRFS_NR_DISCARD_LISTS];
	u64 prev_discard;
	u64 prev_discard_समय;
	atomic_t discardable_extents;
	atomic64_t discardable_bytes;
	u64 max_discard_size;
	u64 delay_ms;
	u32 iops_limit;
	u32 kbps_limit;
	u64 discard_extent_bytes;
	u64 discard_biपंचांगap_bytes;
	atomic64_t discard_bytes_saved;
पूर्ण;

क्रमागत btrfs_orphan_cleanup_state अणु
	ORPHAN_CLEANUP_STARTED	= 1,
	ORPHAN_CLEANUP_DONE	= 2,
पूर्ण;

व्योम btrfs_init_async_reclaim_work(काष्ठा btrfs_fs_info *fs_info);

/* fs_info */
काष्ठा reloc_control;
काष्ठा btrfs_device;
काष्ठा btrfs_fs_devices;
काष्ठा btrfs_balance_control;
काष्ठा btrfs_delayed_root;

/*
 * Block group or device which contains an active swapfile. Used क्रम preventing
 * unsafe operations जबतक a swapfile is active.
 *
 * These are sorted on (ptr, inode) (note that a block group or device can
 * contain more than one swapfile). We compare the poपूर्णांकer values because we
 * करोn't actually care what the object is, we just need a quick check whether
 * the object exists in the rbtree.
 */
काष्ठा btrfs_swapfile_pin अणु
	काष्ठा rb_node node;
	व्योम *ptr;
	काष्ठा inode *inode;
	/*
	 * If true, ptr poपूर्णांकs to a काष्ठा btrfs_block_group. Otherwise, ptr
	 * poपूर्णांकs to a काष्ठा btrfs_device.
	 */
	bool is_block_group;
	/*
	 * Only used when 'is_block_group' is true and it is the number of
	 * extents used by a swapfile क्रम this block group ('ptr' field).
	 */
	पूर्णांक bg_extent_count;
पूर्ण;

bool btrfs_pinned_by_swapfile(काष्ठा btrfs_fs_info *fs_info, व्योम *ptr);

क्रमागत अणु
	BTRFS_FS_BARRIER,
	BTRFS_FS_CLOSING_START,
	BTRFS_FS_CLOSING_DONE,
	BTRFS_FS_LOG_RECOVERING,
	BTRFS_FS_OPEN,
	BTRFS_FS_QUOTA_ENABLED,
	BTRFS_FS_UPDATE_UUID_TREE_GEN,
	BTRFS_FS_CREATING_FREE_SPACE_TREE,
	BTRFS_FS_BTREE_ERR,
	BTRFS_FS_LOG1_ERR,
	BTRFS_FS_LOG2_ERR,
	BTRFS_FS_QUOTA_OVERRIDE,
	/* Used to record पूर्णांकernally whether fs has been frozen */
	BTRFS_FS_FROZEN,
	/*
	 * Indicate that balance has been set up from the ioctl and is in the
	 * मुख्य phase. The fs_info::balance_ctl is initialized.
	 * Set and cleared जबतक holding fs_info::balance_mutex.
	 */
	BTRFS_FS_BALANCE_RUNNING,

	/* Indicate that the cleaner thपढ़ो is awake and करोing something. */
	BTRFS_FS_CLEANER_RUNNING,

	/*
	 * The checksumming has an optimized version and is considered fast,
	 * so we करोn't need to offload checksums to workqueues.
	 */
	BTRFS_FS_CSUM_IMPL_FAST,

	/* Indicate that the discard workqueue can service discards. */
	BTRFS_FS_DISCARD_RUNNING,

	/* Indicate that we need to cleanup space cache v1 */
	BTRFS_FS_CLEANUP_SPACE_CACHE_V1,

	/* Indicate that we can't trust the मुक्त space tree क्रम caching yet */
	BTRFS_FS_FREE_SPACE_TREE_UNTRUSTED,

	/* Indicate whether there are any tree modअगरication log users */
	BTRFS_FS_TREE_MOD_LOG_USERS,

#अगर BITS_PER_LONG == 32
	/* Indicate अगर we have error/warn message prपूर्णांकed on 32bit प्रणालीs */
	BTRFS_FS_32BIT_ERROR,
	BTRFS_FS_32BIT_WARN,
#पूर्ण_अगर
पूर्ण;

/*
 * Exclusive operations (device replace, resize, device add/हटाओ, balance)
 */
क्रमागत btrfs_exclusive_operation अणु
	BTRFS_EXCLOP_NONE,
	BTRFS_EXCLOP_BALANCE,
	BTRFS_EXCLOP_DEV_ADD,
	BTRFS_EXCLOP_DEV_REMOVE,
	BTRFS_EXCLOP_DEV_REPLACE,
	BTRFS_EXCLOP_RESIZE,
	BTRFS_EXCLOP_SWAP_ACTIVATE,
पूर्ण;

काष्ठा btrfs_fs_info अणु
	u8 chunk_tree_uuid[BTRFS_UUID_SIZE];
	अचिन्हित दीर्घ flags;
	काष्ठा btrfs_root *extent_root;
	काष्ठा btrfs_root *tree_root;
	काष्ठा btrfs_root *chunk_root;
	काष्ठा btrfs_root *dev_root;
	काष्ठा btrfs_root *fs_root;
	काष्ठा btrfs_root *csum_root;
	काष्ठा btrfs_root *quota_root;
	काष्ठा btrfs_root *uuid_root;
	काष्ठा btrfs_root *मुक्त_space_root;
	काष्ठा btrfs_root *data_reloc_root;

	/* the log root tree is a directory of all the other log roots */
	काष्ठा btrfs_root *log_root_tree;

	spinlock_t fs_roots_radix_lock;
	काष्ठा radix_tree_root fs_roots_radix;

	/* block group cache stuff */
	spinlock_t block_group_cache_lock;
	u64 first_logical_byte;
	काष्ठा rb_root block_group_cache_tree;

	/* keep track of unallocated space */
	atomic64_t मुक्त_chunk_space;

	/* Track ranges which are used by log trees blocks/logged data extents */
	काष्ठा extent_io_tree excluded_extents;

	/* logical->physical extent mapping */
	काष्ठा extent_map_tree mapping_tree;

	/*
	 * block reservation क्रम extent, checksum, root tree and
	 * delayed dir index item
	 */
	काष्ठा btrfs_block_rsv global_block_rsv;
	/* block reservation क्रम metadata operations */
	काष्ठा btrfs_block_rsv trans_block_rsv;
	/* block reservation क्रम chunk tree */
	काष्ठा btrfs_block_rsv chunk_block_rsv;
	/* block reservation क्रम delayed operations */
	काष्ठा btrfs_block_rsv delayed_block_rsv;
	/* block reservation क्रम delayed refs */
	काष्ठा btrfs_block_rsv delayed_refs_rsv;

	काष्ठा btrfs_block_rsv empty_block_rsv;

	u64 generation;
	u64 last_trans_committed;
	u64 avg_delayed_ref_runसमय;

	/*
	 * this is updated to the current trans every समय a full commit
	 * is required instead of the faster लघु fsync log commits
	 */
	u64 last_trans_log_full_commit;
	अचिन्हित दीर्घ mount_opt;
	/*
	 * Track requests क्रम actions that need to be करोne during transaction
	 * commit (like क्रम some mount options).
	 */
	अचिन्हित दीर्घ pending_changes;
	अचिन्हित दीर्घ compress_type:4;
	अचिन्हित पूर्णांक compress_level;
	u32 commit_पूर्णांकerval;
	/*
	 * It is a suggestive number, the पढ़ो side is safe even it माला_लो a
	 * wrong number because we will ग_लिखो out the data पूर्णांकo a regular
	 * extent. The ग_लिखो side(mount/remount) is under ->s_umount lock,
	 * so it is also safe.
	 */
	u64 max_अंतरभूत;

	काष्ठा btrfs_transaction *running_transaction;
	रुको_queue_head_t transaction_throttle;
	रुको_queue_head_t transaction_रुको;
	रुको_queue_head_t transaction_blocked_रुको;
	रुको_queue_head_t async_submit_रुको;

	/*
	 * Used to protect the incompat_flags, compat_flags, compat_ro_flags
	 * when they are updated.
	 *
	 * Because we करो not clear the flags क्रम ever, so we needn't use
	 * the lock on the पढ़ो side.
	 *
	 * We also needn't use the lock when we mount the fs, because
	 * there is no other task which will update the flag.
	 */
	spinlock_t super_lock;
	काष्ठा btrfs_super_block *super_copy;
	काष्ठा btrfs_super_block *super_क्रम_commit;
	काष्ठा super_block *sb;
	काष्ठा inode *btree_inode;
	काष्ठा mutex tree_log_mutex;
	काष्ठा mutex transaction_kthपढ़ो_mutex;
	काष्ठा mutex cleaner_mutex;
	काष्ठा mutex chunk_mutex;

	/*
	 * this is taken to make sure we करोn't set block groups ro after
	 * the मुक्त space cache has been allocated on them
	 */
	काष्ठा mutex ro_block_group_mutex;

	/* this is used during पढ़ो/modअगरy/ग_लिखो to make sure
	 * no two ios are trying to mod the same stripe at the same
	 * समय
	 */
	काष्ठा btrfs_stripe_hash_table *stripe_hash_table;

	/*
	 * this protects the ordered operations list only जबतक we are
	 * processing all of the entries on it.  This way we make
	 * sure the commit code करोesn't find the list temporarily empty
	 * because another function happens to be करोing non-रुकोing preflush
	 * beक्रमe jumping पूर्णांकo the मुख्य commit.
	 */
	काष्ठा mutex ordered_operations_mutex;

	काष्ठा rw_semaphore commit_root_sem;

	काष्ठा rw_semaphore cleanup_work_sem;

	काष्ठा rw_semaphore subvol_sem;

	spinlock_t trans_lock;
	/*
	 * the reloc mutex goes with the trans lock, it is taken
	 * during commit to protect us from the relocation code
	 */
	काष्ठा mutex reloc_mutex;

	काष्ठा list_head trans_list;
	काष्ठा list_head dead_roots;
	काष्ठा list_head caching_block_groups;

	spinlock_t delayed_iput_lock;
	काष्ठा list_head delayed_iमाला_दो;
	atomic_t nr_delayed_iमाला_दो;
	रुको_queue_head_t delayed_iमाला_दो_रुको;

	atomic64_t tree_mod_seq;

	/* this protects tree_mod_log and tree_mod_seq_list */
	rwlock_t tree_mod_log_lock;
	काष्ठा rb_root tree_mod_log;
	काष्ठा list_head tree_mod_seq_list;

	atomic_t async_delalloc_pages;

	/*
	 * this is used to protect the following list -- ordered_roots.
	 */
	spinlock_t ordered_root_lock;

	/*
	 * all fs/file tree roots in which there are data=ordered extents
	 * pending ग_लिखोback are added पूर्णांकo this list.
	 *
	 * these can span multiple transactions and basically include
	 * every dirty data page that isn't from nodatacow
	 */
	काष्ठा list_head ordered_roots;

	काष्ठा mutex delalloc_root_mutex;
	spinlock_t delalloc_root_lock;
	/* all fs/file tree roots that have delalloc inodes. */
	काष्ठा list_head delalloc_roots;

	/*
	 * there is a pool of worker thपढ़ोs क्रम checksumming during ग_लिखोs
	 * and a pool क्रम checksumming after पढ़ोs.  This is because पढ़ोers
	 * can run with FS locks held, and the ग_लिखोrs may be रुकोing क्रम
	 * those locks.  We करोn't want ordering in the pending list to cause
	 * deadlocks, and so the two are serviced separately.
	 *
	 * A third pool करोes submit_bio to aव्योम deadlocking with the other
	 * two
	 */
	काष्ठा btrfs_workqueue *workers;
	काष्ठा btrfs_workqueue *delalloc_workers;
	काष्ठा btrfs_workqueue *flush_workers;
	काष्ठा btrfs_workqueue *endio_workers;
	काष्ठा btrfs_workqueue *endio_meta_workers;
	काष्ठा btrfs_workqueue *endio_raid56_workers;
	काष्ठा btrfs_workqueue *rmw_workers;
	काष्ठा btrfs_workqueue *endio_meta_ग_लिखो_workers;
	काष्ठा btrfs_workqueue *endio_ग_लिखो_workers;
	काष्ठा btrfs_workqueue *endio_मुक्तspace_worker;
	काष्ठा btrfs_workqueue *caching_workers;
	काष्ठा btrfs_workqueue *पढ़ोahead_workers;

	/*
	 * fixup workers take dirty pages that didn't properly go through
	 * the cow mechanism and make them safe to ग_लिखो.  It happens
	 * क्रम the sys_munmap function call path
	 */
	काष्ठा btrfs_workqueue *fixup_workers;
	काष्ठा btrfs_workqueue *delayed_workers;

	काष्ठा task_काष्ठा *transaction_kthपढ़ो;
	काष्ठा task_काष्ठा *cleaner_kthपढ़ो;
	u32 thपढ़ो_pool_size;

	काष्ठा kobject *space_info_kobj;
	काष्ठा kobject *qgroups_kobj;

	u64 total_pinned;

	/* used to keep from writing metadata until there is a nice batch */
	काष्ठा percpu_counter dirty_metadata_bytes;
	काष्ठा percpu_counter delalloc_bytes;
	काष्ठा percpu_counter ordered_bytes;
	s32 dirty_metadata_batch;
	s32 delalloc_batch;

	काष्ठा list_head dirty_cowonly_roots;

	काष्ठा btrfs_fs_devices *fs_devices;

	/*
	 * The space_info list is effectively पढ़ो only after initial
	 * setup.  It is populated at mount समय and cleaned up after
	 * all block groups are हटाओd.  RCU is used to protect it.
	 */
	काष्ठा list_head space_info;

	काष्ठा btrfs_space_info *data_sinfo;

	काष्ठा reloc_control *reloc_ctl;

	/* data_alloc_cluster is only used in ssd_spपढ़ो mode */
	काष्ठा btrfs_मुक्त_cluster data_alloc_cluster;

	/* all metadata allocations go through this cluster */
	काष्ठा btrfs_मुक्त_cluster meta_alloc_cluster;

	/* स्वतः defrag inodes go here */
	spinlock_t defrag_inodes_lock;
	काष्ठा rb_root defrag_inodes;
	atomic_t defrag_running;

	/* Used to protect avail_अणुdata, metadata, प्रणालीपूर्ण_alloc_bits */
	seqlock_t profiles_lock;
	/*
	 * these three are in extended क्रमmat (availability of single
	 * chunks is denoted by BTRFS_AVAIL_ALLOC_BIT_SINGLE bit, other
	 * types are denoted by corresponding BTRFS_BLOCK_GROUP_* bits)
	 */
	u64 avail_data_alloc_bits;
	u64 avail_metadata_alloc_bits;
	u64 avail_प्रणाली_alloc_bits;

	/* restriper state */
	spinlock_t balance_lock;
	काष्ठा mutex balance_mutex;
	atomic_t balance_छोड़ो_req;
	atomic_t balance_cancel_req;
	काष्ठा btrfs_balance_control *balance_ctl;
	रुको_queue_head_t balance_रुको_q;

	u32 data_chunk_allocations;
	u32 metadata_ratio;

	व्योम *bdev_holder;

	/* निजी scrub inक्रमmation */
	काष्ठा mutex scrub_lock;
	atomic_t scrubs_running;
	atomic_t scrub_छोड़ो_req;
	atomic_t scrubs_छोड़ोd;
	atomic_t scrub_cancel_req;
	रुको_queue_head_t scrub_छोड़ो_रुको;
	/*
	 * The worker poपूर्णांकers are शून्य अगरf the refcount is 0, ie. scrub is not
	 * running.
	 */
	refcount_t scrub_workers_refcnt;
	काष्ठा btrfs_workqueue *scrub_workers;
	काष्ठा btrfs_workqueue *scrub_wr_completion_workers;
	काष्ठा btrfs_workqueue *scrub_parity_workers;

	काष्ठा btrfs_discard_ctl discard_ctl;

#अगर_घोषित CONFIG_BTRFS_FS_CHECK_INTEGRITY
	u32 check_पूर्णांकegrity_prपूर्णांक_mask;
#पूर्ण_अगर
	/* is qgroup tracking in a consistent state? */
	u64 qgroup_flags;

	/* holds configuration and tracking. Protected by qgroup_lock */
	काष्ठा rb_root qgroup_tree;
	spinlock_t qgroup_lock;

	/*
	 * used to aव्योम frequently calling ulist_alloc()/ulist_मुक्त()
	 * when करोing qgroup accounting, it must be रक्षित by qgroup_lock.
	 */
	काष्ठा ulist *qgroup_ulist;

	/*
	 * Protect user change क्रम quota operations. If a transaction is needed,
	 * it must be started beक्रमe locking this lock.
	 */
	काष्ठा mutex qgroup_ioctl_lock;

	/* list of dirty qgroups to be written at next commit */
	काष्ठा list_head dirty_qgroups;

	/* used by qgroup क्रम an efficient tree traversal */
	u64 qgroup_seq;

	/* qgroup rescan items */
	काष्ठा mutex qgroup_rescan_lock; /* protects the progress item */
	काष्ठा btrfs_key qgroup_rescan_progress;
	काष्ठा btrfs_workqueue *qgroup_rescan_workers;
	काष्ठा completion qgroup_rescan_completion;
	काष्ठा btrfs_work qgroup_rescan_work;
	bool qgroup_rescan_running;	/* रक्षित by qgroup_rescan_lock */

	/* fileप्रणाली state */
	अचिन्हित दीर्घ fs_state;

	काष्ठा btrfs_delayed_root *delayed_root;

	/* पढ़ोahead tree */
	spinlock_t पढ़ोa_lock;
	काष्ठा radix_tree_root पढ़ोa_tree;

	/* पढ़ोahead works cnt */
	atomic_t पढ़ोa_works_cnt;

	/* Extent buffer radix tree */
	spinlock_t buffer_lock;
	/* Entries are eb->start / sectorsize */
	काष्ठा radix_tree_root buffer_radix;

	/* next backup root to be overwritten */
	पूर्णांक backup_root_index;

	/* device replace state */
	काष्ठा btrfs_dev_replace dev_replace;

	काष्ठा semaphore uuid_tree_rescan_sem;

	/* Used to reclaim the metadata space in the background. */
	काष्ठा work_काष्ठा async_reclaim_work;
	काष्ठा work_काष्ठा async_data_reclaim_work;
	काष्ठा work_काष्ठा preempt_reclaim_work;

	/* Reclaim partially filled block groups in the background */
	काष्ठा work_काष्ठा reclaim_bgs_work;
	काष्ठा list_head reclaim_bgs;
	पूर्णांक bg_reclaim_threshold;

	spinlock_t unused_bgs_lock;
	काष्ठा list_head unused_bgs;
	काष्ठा mutex unused_bg_unpin_mutex;
	/* Protect block groups that are going to be deleted */
	काष्ठा mutex reclaim_bgs_lock;

	/* Cached block sizes */
	u32 nodesize;
	u32 sectorsize;
	/* ilog2 of sectorsize, use to aव्योम 64bit भागision */
	u32 sectorsize_bits;
	u32 csum_size;
	u32 csums_per_leaf;
	u32 stripesize;

	/* Block groups and devices containing active swapfiles. */
	spinlock_t swapfile_pins_lock;
	काष्ठा rb_root swapfile_pins;

	काष्ठा crypto_shash *csum_shash;

	/*
	 * Number of send operations in progress.
	 * Updated जबतक holding fs_info::balance_mutex.
	 */
	पूर्णांक send_in_progress;

	/* Type of exclusive operation running */
	अचिन्हित दीर्घ exclusive_operation;

	/*
	 * Zone size > 0 when in ZONED mode, otherwise it's used क्रम a check
	 * अगर the mode is enabled
	 */
	जोड़ अणु
		u64 zone_size;
		u64 zoned;
	पूर्ण;

	/* Max size to emit ZONE_APPEND ग_लिखो command */
	u64 max_zone_append_size;
	काष्ठा mutex zoned_meta_io_lock;
	spinlock_t treelog_bg_lock;
	u64 treelog_bg;

#अगर_घोषित CONFIG_BTRFS_FS_REF_VERIFY
	spinlock_t ref_verअगरy_lock;
	काष्ठा rb_root block_tree;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BTRFS_DEBUG
	काष्ठा kobject *debug_kobj;
	काष्ठा kobject *discard_debug_kobj;
	काष्ठा list_head allocated_roots;

	spinlock_t eb_leak_lock;
	काष्ठा list_head allocated_ebs;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा btrfs_fs_info *btrfs_sb(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

/*
 * The state of btrfs root
 */
क्रमागत अणु
	/*
	 * btrfs_record_root_in_trans is a multi-step process, and it can race
	 * with the balancing code.   But the race is very small, and only the
	 * first समय the root is added to each transaction.  So IN_TRANS_SETUP
	 * is used to tell us when more checks are required
	 */
	BTRFS_ROOT_IN_TRANS_SETUP,

	/*
	 * Set अगर tree blocks of this root can be shared by other roots.
	 * Only subvolume trees and their reloc trees have this bit set.
	 * Conflicts with TRACK_सूचीTY bit.
	 *
	 * This affects two things:
	 *
	 * - How balance works
	 *   For shareable roots, we need to use reloc tree and करो path
	 *   replacement क्रम balance, and need various pre/post hooks क्रम
	 *   snapshot creation to handle them.
	 *
	 *   While क्रम non-shareable trees, we just simply करो a tree search
	 *   with COW.
	 *
	 * - How dirty roots are tracked
	 *   For shareable roots, btrfs_record_root_in_trans() is needed to
	 *   track them, जबतक non-subvolume roots have TRACK_सूचीTY bit, they
	 *   करोn't need to set this manually.
	 */
	BTRFS_ROOT_SHAREABLE,
	BTRFS_ROOT_TRACK_सूचीTY,
	BTRFS_ROOT_IN_RADIX,
	BTRFS_ROOT_ORPHAN_ITEM_INSERTED,
	BTRFS_ROOT_DEFRAG_RUNNING,
	BTRFS_ROOT_FORCE_COW,
	BTRFS_ROOT_MULTI_LOG_TASKS,
	BTRFS_ROOT_सूचीTY,
	BTRFS_ROOT_DELETING,

	/*
	 * Reloc tree is orphan, only kept here क्रम qgroup delayed subtree scan
	 *
	 * Set क्रम the subvolume tree owning the reloc tree.
	 */
	BTRFS_ROOT_DEAD_RELOC_TREE,
	/* Mark dead root stored on device whose cleanup needs to be resumed */
	BTRFS_ROOT_DEAD_TREE,
	/* The root has a log tree. Used क्रम subvolume roots and the tree root. */
	BTRFS_ROOT_HAS_LOG_TREE,
	/* Qgroup flushing is in progress */
	BTRFS_ROOT_QGROUP_FLUSHING,
पूर्ण;

/*
 * Record swapped tree blocks of a subvolume tree क्रम delayed subtree trace
 * code. For detail check comment in fs/btrfs/qgroup.c.
 */
काष्ठा btrfs_qgroup_swapped_blocks अणु
	spinlock_t lock;
	/* RM_EMPTY_ROOT() of above blocks[] */
	bool swapped;
	काष्ठा rb_root blocks[BTRFS_MAX_LEVEL];
पूर्ण;

/*
 * in ram representation of the tree.  extent_root is used क्रम all allocations
 * and क्रम the extent tree extent_root root.
 */
काष्ठा btrfs_root अणु
	काष्ठा extent_buffer *node;

	काष्ठा extent_buffer *commit_root;
	काष्ठा btrfs_root *log_root;
	काष्ठा btrfs_root *reloc_root;

	अचिन्हित दीर्घ state;
	काष्ठा btrfs_root_item root_item;
	काष्ठा btrfs_key root_key;
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा extent_io_tree dirty_log_pages;

	काष्ठा mutex objectid_mutex;

	spinlock_t accounting_lock;
	काष्ठा btrfs_block_rsv *block_rsv;

	काष्ठा mutex log_mutex;
	रुको_queue_head_t log_ग_लिखोr_रुको;
	रुको_queue_head_t log_commit_रुको[2];
	काष्ठा list_head log_ctxs[2];
	/* Used only क्रम log trees of subvolumes, not क्रम the log root tree */
	atomic_t log_ग_लिखोrs;
	atomic_t log_commit[2];
	/* Used only क्रम log trees of subvolumes, not क्रम the log root tree */
	atomic_t log_batch;
	पूर्णांक log_transid;
	/* No matter the commit succeeds or not*/
	पूर्णांक log_transid_committed;
	/* Just be updated when the commit succeeds. */
	पूर्णांक last_log_commit;
	pid_t log_start_pid;

	u64 last_trans;

	u32 type;

	u64 मुक्त_objectid;

	काष्ठा btrfs_key defrag_progress;
	काष्ठा btrfs_key defrag_max;

	/* The dirty list is only used by non-shareable roots */
	काष्ठा list_head dirty_list;

	काष्ठा list_head root_list;

	spinlock_t log_extents_lock[2];
	काष्ठा list_head logged_list[2];

	पूर्णांक orphan_cleanup_state;

	spinlock_t inode_lock;
	/* red-black tree that keeps track of in-memory inodes */
	काष्ठा rb_root inode_tree;

	/*
	 * radix tree that keeps track of delayed nodes of every inode,
	 * रक्षित by inode_lock
	 */
	काष्ठा radix_tree_root delayed_nodes_tree;
	/*
	 * right now this just माला_लो used so that a root has its own devid
	 * क्रम stat.  It may be used क्रम more later
	 */
	dev_t anon_dev;

	spinlock_t root_item_lock;
	refcount_t refs;

	काष्ठा mutex delalloc_mutex;
	spinlock_t delalloc_lock;
	/*
	 * all of the inodes that have delalloc bytes.  It is possible क्रम
	 * this list to be empty even when there is still dirty data=ordered
	 * extents रुकोing to finish IO.
	 */
	काष्ठा list_head delalloc_inodes;
	काष्ठा list_head delalloc_root;
	u64 nr_delalloc_inodes;

	काष्ठा mutex ordered_extent_mutex;
	/*
	 * this is used by the balancing code to रुको क्रम all the pending
	 * ordered extents
	 */
	spinlock_t ordered_extent_lock;

	/*
	 * all of the data=ordered extents pending ग_लिखोback
	 * these can span multiple transactions and basically include
	 * every dirty data page that isn't from nodatacow
	 */
	काष्ठा list_head ordered_extents;
	काष्ठा list_head ordered_root;
	u64 nr_ordered_extents;

	/*
	 * Not empty अगर this subvolume root has gone through tree block swap
	 * (relocation)
	 *
	 * Will be used by reloc_control::dirty_subvol_roots.
	 */
	काष्ठा list_head reloc_dirty_list;

	/*
	 * Number of currently running SEND ioctls to prevent
	 * manipulation with the पढ़ो-only status via SUBVOL_SETFLAGS
	 */
	पूर्णांक send_in_progress;
	/*
	 * Number of currently running deduplication operations that have a
	 * destination inode beदीर्घing to this root. Protected by the lock
	 * root_item_lock.
	 */
	पूर्णांक dedupe_in_progress;
	/* For exclusion of snapshot creation and nocow ग_लिखोs */
	काष्ठा btrfs_drew_lock snapshot_lock;

	atomic_t snapshot_क्रमce_cow;

	/* For qgroup metadata reserved space */
	spinlock_t qgroup_meta_rsv_lock;
	u64 qgroup_meta_rsv_pertrans;
	u64 qgroup_meta_rsv_pपुनः_स्मृति;
	रुको_queue_head_t qgroup_flush_रुको;

	/* Number of active swapfiles */
	atomic_t nr_swapfiles;

	/* Record pairs of swapped blocks क्रम qgroup */
	काष्ठा btrfs_qgroup_swapped_blocks swapped_blocks;

	/* Used only by log trees, when logging csum items */
	काष्ठा extent_io_tree log_csum_range;

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
	u64 alloc_bytenr;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BTRFS_DEBUG
	काष्ठा list_head leak_list;
#पूर्ण_अगर
पूर्ण;

/*
 * Structure that conveys inक्रमmation about an extent that is going to replace
 * all the extents in a file range.
 */
काष्ठा btrfs_replace_extent_info अणु
	u64 disk_offset;
	u64 disk_len;
	u64 data_offset;
	u64 data_len;
	u64 file_offset;
	/* Poपूर्णांकer to a file extent item of type regular or pपुनः_स्मृति. */
	अक्षर *extent_buf;
	/*
	 * Set to true when attempting to replace a file range with a new extent
	 * described by this काष्ठाure, set to false when attempting to clone an
	 * existing extent पूर्णांकo a file range.
	 */
	bool is_new_extent;
	/* Meaningful only अगर is_new_extent is true. */
	पूर्णांक qgroup_reserved;
	/*
	 * Meaningful only अगर is_new_extent is true.
	 * Used to track how many extent items we have alपढ़ोy inserted in a
	 * subvolume tree that refer to the extent described by this काष्ठाure,
	 * so that we know when to create a new delayed ref or update an existing
	 * one.
	 */
	पूर्णांक insertions;
पूर्ण;

/* Arguments क्रम btrfs_drop_extents() */
काष्ठा btrfs_drop_extents_args अणु
	/* Input parameters */

	/*
	 * If शून्य, btrfs_drop_extents() will allocate and मुक्त its own path.
	 * If 'replace_extent' is true, this must not be शून्य. Also the path
	 * is always released except अगर 'replace_extent' is true and
	 * btrfs_drop_extents() sets 'extent_inserted' to true, in which हाल
	 * the path is kept locked.
	 */
	काष्ठा btrfs_path *path;
	/* Start offset of the range to drop extents from */
	u64 start;
	/* End (exclusive, last byte + 1) of the range to drop extents from */
	u64 end;
	/* If true drop all the extent maps in the range */
	bool drop_cache;
	/*
	 * If true it means we want to insert a new extent after dropping all
	 * the extents in the range. If this is true, the 'extent_item_size'
	 * parameter must be set as well and the 'extent_inserted' field will
	 * be set to true by btrfs_drop_extents() अगर it could insert the new
	 * extent.
	 * Note: when this is set to true the path must not be शून्य.
	 */
	bool replace_extent;
	/*
	 * Used अगर 'replace_extent' is true. Size of the file extent item to
	 * insert after dropping all existing extents in the range
	 */
	u32 extent_item_size;

	/* Output parameters */

	/*
	 * Set to the minimum between the input parameter 'end' and the end
	 * (exclusive, last byte + 1) of the last dropped extent. This is always
	 * set even अगर btrfs_drop_extents() वापसs an error.
	 */
	u64 drop_end;
	/*
	 * The number of allocated bytes found in the range. This can be smaller
	 * than the range's length when there are holes in the range.
	 */
	u64 bytes_found;
	/*
	 * Only set अगर 'replace_extent' is true. Set to true अगर we were able
	 * to insert a replacement extent after dropping all extents in the
	 * range, otherwise set to false by btrfs_drop_extents().
	 * Also, अगर btrfs_drop_extents() has set this to true it means it
	 * वापसed with the path locked, otherwise अगर it has set this to
	 * false it has वापसed with the path released.
	 */
	bool extent_inserted;
पूर्ण;

काष्ठा btrfs_file_निजी अणु
	व्योम *filldir_buf;
पूर्ण;


अटल अंतरभूत u32 BTRFS_LEAF_DATA_SIZE(स्थिर काष्ठा btrfs_fs_info *info)
अणु

	वापस info->nodesize - माप(काष्ठा btrfs_header);
पूर्ण

#घोषणा BTRFS_LEAF_DATA_OFFSET		दुरत्व(काष्ठा btrfs_leaf, items)

अटल अंतरभूत u32 BTRFS_MAX_ITEM_SIZE(स्थिर काष्ठा btrfs_fs_info *info)
अणु
	वापस BTRFS_LEAF_DATA_SIZE(info) - माप(काष्ठा btrfs_item);
पूर्ण

अटल अंतरभूत u32 BTRFS_NODEPTRS_PER_BLOCK(स्थिर काष्ठा btrfs_fs_info *info)
अणु
	वापस BTRFS_LEAF_DATA_SIZE(info) / माप(काष्ठा btrfs_key_ptr);
पूर्ण

#घोषणा BTRFS_खाता_EXTENT_INLINE_DATA_START		\
		(दुरत्व(काष्ठा btrfs_file_extent_item, disk_bytenr))
अटल अंतरभूत u32 BTRFS_MAX_INLINE_DATA_SIZE(स्थिर काष्ठा btrfs_fs_info *info)
अणु
	वापस BTRFS_MAX_ITEM_SIZE(info) -
	       BTRFS_खाता_EXTENT_INLINE_DATA_START;
पूर्ण

अटल अंतरभूत u32 BTRFS_MAX_XATTR_SIZE(स्थिर काष्ठा btrfs_fs_info *info)
अणु
	वापस BTRFS_MAX_ITEM_SIZE(info) - माप(काष्ठा btrfs_dir_item);
पूर्ण

/*
 * Flags क्रम mount options.
 *
 * Note: करोn't क्रमget to add new options to btrfs_show_options()
 */
#घोषणा BTRFS_MOUNT_NODATASUM		(1 << 0)
#घोषणा BTRFS_MOUNT_NODATACOW		(1 << 1)
#घोषणा BTRFS_MOUNT_NOBARRIER		(1 << 2)
#घोषणा BTRFS_MOUNT_SSD			(1 << 3)
#घोषणा BTRFS_MOUNT_DEGRADED		(1 << 4)
#घोषणा BTRFS_MOUNT_COMPRESS		(1 << 5)
#घोषणा BTRFS_MOUNT_NOTREELOG           (1 << 6)
#घोषणा BTRFS_MOUNT_FLUSHONCOMMIT       (1 << 7)
#घोषणा BTRFS_MOUNT_SSD_SPREAD		(1 << 8)
#घोषणा BTRFS_MOUNT_NOSSD		(1 << 9)
#घोषणा BTRFS_MOUNT_DISCARD_SYNC	(1 << 10)
#घोषणा BTRFS_MOUNT_FORCE_COMPRESS      (1 << 11)
#घोषणा BTRFS_MOUNT_SPACE_CACHE		(1 << 12)
#घोषणा BTRFS_MOUNT_CLEAR_CACHE		(1 << 13)
#घोषणा BTRFS_MOUNT_USER_SUBVOL_RM_ALLOWED (1 << 14)
#घोषणा BTRFS_MOUNT_ENOSPC_DEBUG	 (1 << 15)
#घोषणा BTRFS_MOUNT_AUTO_DEFRAG		(1 << 16)
/* bit 17 is मुक्त */
#घोषणा BTRFS_MOUNT_USEBACKUPROOT	(1 << 18)
#घोषणा BTRFS_MOUNT_SKIP_BALANCE	(1 << 19)
#घोषणा BTRFS_MOUNT_CHECK_INTEGRITY	(1 << 20)
#घोषणा BTRFS_MOUNT_CHECK_INTEGRITY_INCLUDING_EXTENT_DATA (1 << 21)
#घोषणा BTRFS_MOUNT_PANIC_ON_FATAL_ERROR	(1 << 22)
#घोषणा BTRFS_MOUNT_RESCAN_UUID_TREE	(1 << 23)
#घोषणा BTRFS_MOUNT_FRAGMENT_DATA	(1 << 24)
#घोषणा BTRFS_MOUNT_FRAGMENT_METADATA	(1 << 25)
#घोषणा BTRFS_MOUNT_FREE_SPACE_TREE	(1 << 26)
#घोषणा BTRFS_MOUNT_NOLOGREPLAY		(1 << 27)
#घोषणा BTRFS_MOUNT_REF_VERIFY		(1 << 28)
#घोषणा BTRFS_MOUNT_DISCARD_ASYNC	(1 << 29)
#घोषणा BTRFS_MOUNT_IGNOREBADROOTS	(1 << 30)
#घोषणा BTRFS_MOUNT_IGNOREDATACSUMS	(1 << 31)

#घोषणा BTRFS_DEFAULT_COMMIT_INTERVAL	(30)
#घोषणा BTRFS_DEFAULT_MAX_INLINE	(2048)

#घोषणा btrfs_clear_opt(o, opt)		((o) &= ~BTRFS_MOUNT_##opt)
#घोषणा btrfs_set_opt(o, opt)		((o) |= BTRFS_MOUNT_##opt)
#घोषणा btrfs_raw_test_opt(o, opt)	((o) & BTRFS_MOUNT_##opt)
#घोषणा btrfs_test_opt(fs_info, opt)	((fs_info)->mount_opt & \
					 BTRFS_MOUNT_##opt)

#घोषणा btrfs_set_and_info(fs_info, opt, fmt, args...)			\
करो अणु									\
	अगर (!btrfs_test_opt(fs_info, opt))				\
		btrfs_info(fs_info, fmt, ##args);			\
	btrfs_set_opt(fs_info->mount_opt, opt);				\
पूर्ण जबतक (0)

#घोषणा btrfs_clear_and_info(fs_info, opt, fmt, args...)		\
करो अणु									\
	अगर (btrfs_test_opt(fs_info, opt))				\
		btrfs_info(fs_info, fmt, ##args);			\
	btrfs_clear_opt(fs_info->mount_opt, opt);			\
पूर्ण जबतक (0)

/*
 * Requests क्रम changes that need to be करोne during transaction commit.
 *
 * Internal mount options that are used क्रम special handling of the real
 * mount options (eg. cannot be set during remount and have to be set during
 * transaction commit)
 */

#घोषणा BTRFS_PENDING_COMMIT			(0)

#घोषणा btrfs_test_pending(info, opt)	\
	test_bit(BTRFS_PENDING_##opt, &(info)->pending_changes)
#घोषणा btrfs_set_pending(info, opt)	\
	set_bit(BTRFS_PENDING_##opt, &(info)->pending_changes)
#घोषणा btrfs_clear_pending(info, opt)	\
	clear_bit(BTRFS_PENDING_##opt, &(info)->pending_changes)

/*
 * Helpers क्रम setting pending mount option changes.
 *
 * Expects corresponding macros
 * BTRFS_PENDING_SET_ and CLEAR_ + लघु mount option name
 */
#घोषणा btrfs_set_pending_and_info(info, opt, fmt, args...)            \
करो अणु                                                                   \
       अगर (!btrfs_raw_test_opt((info)->mount_opt, opt)) अणु              \
               btrfs_info((info), fmt, ##args);                        \
               btrfs_set_pending((info), SET_##opt);                   \
               btrfs_clear_pending((info), CLEAR_##opt);               \
       पूर्ण                                                               \
पूर्ण जबतक(0)

#घोषणा btrfs_clear_pending_and_info(info, opt, fmt, args...)          \
करो अणु                                                                   \
       अगर (btrfs_raw_test_opt((info)->mount_opt, opt)) अणु               \
               btrfs_info((info), fmt, ##args);                        \
               btrfs_set_pending((info), CLEAR_##opt);                 \
               btrfs_clear_pending((info), SET_##opt);                 \
       पूर्ण                                                               \
पूर्ण जबतक(0)

/*
 * Inode flags
 */
#घोषणा BTRFS_INODE_NODATASUM		(1 << 0)
#घोषणा BTRFS_INODE_NODATACOW		(1 << 1)
#घोषणा BTRFS_INODE_READONLY		(1 << 2)
#घोषणा BTRFS_INODE_NOCOMPRESS		(1 << 3)
#घोषणा BTRFS_INODE_PREALLOC		(1 << 4)
#घोषणा BTRFS_INODE_SYNC		(1 << 5)
#घोषणा BTRFS_INODE_IMMUTABLE		(1 << 6)
#घोषणा BTRFS_INODE_APPEND		(1 << 7)
#घोषणा BTRFS_INODE_NODUMP		(1 << 8)
#घोषणा BTRFS_INODE_NOATIME		(1 << 9)
#घोषणा BTRFS_INODE_सूचीSYNC		(1 << 10)
#घोषणा BTRFS_INODE_COMPRESS		(1 << 11)

#घोषणा BTRFS_INODE_ROOT_ITEM_INIT	(1 << 31)

#घोषणा BTRFS_INODE_FLAG_MASK						\
	(BTRFS_INODE_NODATASUM |					\
	 BTRFS_INODE_NODATACOW |					\
	 BTRFS_INODE_READONLY |						\
	 BTRFS_INODE_NOCOMPRESS |					\
	 BTRFS_INODE_PREALLOC |						\
	 BTRFS_INODE_SYNC |						\
	 BTRFS_INODE_IMMUTABLE |					\
	 BTRFS_INODE_APPEND |						\
	 BTRFS_INODE_NODUMP |						\
	 BTRFS_INODE_NOATIME |						\
	 BTRFS_INODE_सूचीSYNC |						\
	 BTRFS_INODE_COMPRESS |						\
	 BTRFS_INODE_ROOT_ITEM_INIT)

काष्ठा btrfs_map_token अणु
	काष्ठा extent_buffer *eb;
	अक्षर *kaddr;
	अचिन्हित दीर्घ offset;
पूर्ण;

#घोषणा BTRFS_BYTES_TO_BLKS(fs_info, bytes) \
				((bytes) >> (fs_info)->sectorsize_bits)

अटल अंतरभूत व्योम btrfs_init_map_token(काष्ठा btrfs_map_token *token,
					काष्ठा extent_buffer *eb)
अणु
	token->eb = eb;
	token->kaddr = page_address(eb->pages[0]);
	token->offset = 0;
पूर्ण

/* some macros to generate set/get functions क्रम the काष्ठा fields.  This
 * assumes there is a lefoo_to_cpu क्रम every type, so lets make a simple
 * one क्रम u8:
 */
#घोषणा le8_to_cpu(v) (v)
#घोषणा cpu_to_le8(v) (v)
#घोषणा __le8 u8

अटल अंतरभूत u8 get_unaligned_le8(स्थिर व्योम *p)
अणु
       वापस *(u8 *)p;
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le8(u8 val, व्योम *p)
अणु
       *(u8 *)p = val;
पूर्ण

#घोषणा पढ़ो_eb_member(eb, ptr, type, member, result) (\
	पढ़ो_extent_buffer(eb, (अक्षर *)(result),			\
			   ((अचिन्हित दीर्घ)(ptr)) +			\
			    दुरत्व(type, member),			\
			   माप(((type *)0)->member)))

#घोषणा ग_लिखो_eb_member(eb, ptr, type, member, result) (\
	ग_लिखो_extent_buffer(eb, (अक्षर *)(result),			\
			   ((अचिन्हित दीर्घ)(ptr)) +			\
			    दुरत्व(type, member),			\
			   माप(((type *)0)->member)))

#घोषणा DECLARE_BTRFS_SETGET_BITS(bits)					\
u##bits btrfs_get_token_##bits(काष्ठा btrfs_map_token *token,		\
			       स्थिर व्योम *ptr, अचिन्हित दीर्घ off);	\
व्योम btrfs_set_token_##bits(काष्ठा btrfs_map_token *token,		\
			    स्थिर व्योम *ptr, अचिन्हित दीर्घ off,		\
			    u##bits val);				\
u##bits btrfs_get_##bits(स्थिर काष्ठा extent_buffer *eb,		\
			 स्थिर व्योम *ptr, अचिन्हित दीर्घ off);		\
व्योम btrfs_set_##bits(स्थिर काष्ठा extent_buffer *eb, व्योम *ptr,	\
		      अचिन्हित दीर्घ off, u##bits val);

DECLARE_BTRFS_SETGET_BITS(8)
DECLARE_BTRFS_SETGET_BITS(16)
DECLARE_BTRFS_SETGET_BITS(32)
DECLARE_BTRFS_SETGET_BITS(64)

#घोषणा BTRFS_SETGET_FUNCS(name, type, member, bits)			\
अटल अंतरभूत u##bits btrfs_##name(स्थिर काष्ठा extent_buffer *eb,	\
				   स्थिर type *s)			\
अणु									\
	BUILD_BUG_ON(माप(u##bits) != माप(((type *)0))->member);	\
	वापस btrfs_get_##bits(eb, s, दुरत्व(type, member));		\
पूर्ण									\
अटल अंतरभूत व्योम btrfs_set_##name(स्थिर काष्ठा extent_buffer *eb, type *s, \
				    u##bits val)			\
अणु									\
	BUILD_BUG_ON(माप(u##bits) != माप(((type *)0))->member);	\
	btrfs_set_##bits(eb, s, दुरत्व(type, member), val);		\
पूर्ण									\
अटल अंतरभूत u##bits btrfs_token_##name(काष्ठा btrfs_map_token *token,	\
					 स्थिर type *s)			\
अणु									\
	BUILD_BUG_ON(माप(u##bits) != माप(((type *)0))->member);	\
	वापस btrfs_get_token_##bits(token, s, दुरत्व(type, member));\
पूर्ण									\
अटल अंतरभूत व्योम btrfs_set_token_##name(काष्ठा btrfs_map_token *token,\
					  type *s, u##bits val)		\
अणु									\
	BUILD_BUG_ON(माप(u##bits) != माप(((type *)0))->member);	\
	btrfs_set_token_##bits(token, s, दुरत्व(type, member), val);	\
पूर्ण

#घोषणा BTRFS_SETGET_HEADER_FUNCS(name, type, member, bits)		\
अटल अंतरभूत u##bits btrfs_##name(स्थिर काष्ठा extent_buffer *eb)	\
अणु									\
	स्थिर type *p = page_address(eb->pages[0]) +			\
			offset_in_page(eb->start);			\
	वापस get_unaligned_le##bits(&p->member);			\
पूर्ण									\
अटल अंतरभूत व्योम btrfs_set_##name(स्थिर काष्ठा extent_buffer *eb,	\
				    u##bits val)			\
अणु									\
	type *p = page_address(eb->pages[0]) + offset_in_page(eb->start); \
	put_unaligned_le##bits(val, &p->member);			\
पूर्ण

#घोषणा BTRFS_SETGET_STACK_FUNCS(name, type, member, bits)		\
अटल अंतरभूत u##bits btrfs_##name(स्थिर type *s)			\
अणु									\
	वापस get_unaligned_le##bits(&s->member);			\
पूर्ण									\
अटल अंतरभूत व्योम btrfs_set_##name(type *s, u##bits val)		\
अणु									\
	put_unaligned_le##bits(val, &s->member);			\
पूर्ण

अटल अंतरभूत u64 btrfs_device_total_bytes(स्थिर काष्ठा extent_buffer *eb,
					   काष्ठा btrfs_dev_item *s)
अणु
	BUILD_BUG_ON(माप(u64) !=
		     माप(((काष्ठा btrfs_dev_item *)0))->total_bytes);
	वापस btrfs_get_64(eb, s, दुरत्व(काष्ठा btrfs_dev_item,
					    total_bytes));
पूर्ण
अटल अंतरभूत व्योम btrfs_set_device_total_bytes(स्थिर काष्ठा extent_buffer *eb,
						काष्ठा btrfs_dev_item *s,
						u64 val)
अणु
	BUILD_BUG_ON(माप(u64) !=
		     माप(((काष्ठा btrfs_dev_item *)0))->total_bytes);
	WARN_ON(!IS_ALIGNED(val, eb->fs_info->sectorsize));
	btrfs_set_64(eb, s, दुरत्व(काष्ठा btrfs_dev_item, total_bytes), val);
पूर्ण


BTRFS_SETGET_FUNCS(device_type, काष्ठा btrfs_dev_item, type, 64);
BTRFS_SETGET_FUNCS(device_bytes_used, काष्ठा btrfs_dev_item, bytes_used, 64);
BTRFS_SETGET_FUNCS(device_io_align, काष्ठा btrfs_dev_item, io_align, 32);
BTRFS_SETGET_FUNCS(device_io_width, काष्ठा btrfs_dev_item, io_width, 32);
BTRFS_SETGET_FUNCS(device_start_offset, काष्ठा btrfs_dev_item,
		   start_offset, 64);
BTRFS_SETGET_FUNCS(device_sector_size, काष्ठा btrfs_dev_item, sector_size, 32);
BTRFS_SETGET_FUNCS(device_id, काष्ठा btrfs_dev_item, devid, 64);
BTRFS_SETGET_FUNCS(device_group, काष्ठा btrfs_dev_item, dev_group, 32);
BTRFS_SETGET_FUNCS(device_seek_speed, काष्ठा btrfs_dev_item, seek_speed, 8);
BTRFS_SETGET_FUNCS(device_bandwidth, काष्ठा btrfs_dev_item, bandwidth, 8);
BTRFS_SETGET_FUNCS(device_generation, काष्ठा btrfs_dev_item, generation, 64);

BTRFS_SETGET_STACK_FUNCS(stack_device_type, काष्ठा btrfs_dev_item, type, 64);
BTRFS_SETGET_STACK_FUNCS(stack_device_total_bytes, काष्ठा btrfs_dev_item,
			 total_bytes, 64);
BTRFS_SETGET_STACK_FUNCS(stack_device_bytes_used, काष्ठा btrfs_dev_item,
			 bytes_used, 64);
BTRFS_SETGET_STACK_FUNCS(stack_device_io_align, काष्ठा btrfs_dev_item,
			 io_align, 32);
BTRFS_SETGET_STACK_FUNCS(stack_device_io_width, काष्ठा btrfs_dev_item,
			 io_width, 32);
BTRFS_SETGET_STACK_FUNCS(stack_device_sector_size, काष्ठा btrfs_dev_item,
			 sector_size, 32);
BTRFS_SETGET_STACK_FUNCS(stack_device_id, काष्ठा btrfs_dev_item, devid, 64);
BTRFS_SETGET_STACK_FUNCS(stack_device_group, काष्ठा btrfs_dev_item,
			 dev_group, 32);
BTRFS_SETGET_STACK_FUNCS(stack_device_seek_speed, काष्ठा btrfs_dev_item,
			 seek_speed, 8);
BTRFS_SETGET_STACK_FUNCS(stack_device_bandwidth, काष्ठा btrfs_dev_item,
			 bandwidth, 8);
BTRFS_SETGET_STACK_FUNCS(stack_device_generation, काष्ठा btrfs_dev_item,
			 generation, 64);

अटल अंतरभूत अचिन्हित दीर्घ btrfs_device_uuid(काष्ठा btrfs_dev_item *d)
अणु
	वापस (अचिन्हित दीर्घ)d + दुरत्व(काष्ठा btrfs_dev_item, uuid);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ btrfs_device_fsid(काष्ठा btrfs_dev_item *d)
अणु
	वापस (अचिन्हित दीर्घ)d + दुरत्व(काष्ठा btrfs_dev_item, fsid);
पूर्ण

BTRFS_SETGET_FUNCS(chunk_length, काष्ठा btrfs_chunk, length, 64);
BTRFS_SETGET_FUNCS(chunk_owner, काष्ठा btrfs_chunk, owner, 64);
BTRFS_SETGET_FUNCS(chunk_stripe_len, काष्ठा btrfs_chunk, stripe_len, 64);
BTRFS_SETGET_FUNCS(chunk_io_align, काष्ठा btrfs_chunk, io_align, 32);
BTRFS_SETGET_FUNCS(chunk_io_width, काष्ठा btrfs_chunk, io_width, 32);
BTRFS_SETGET_FUNCS(chunk_sector_size, काष्ठा btrfs_chunk, sector_size, 32);
BTRFS_SETGET_FUNCS(chunk_type, काष्ठा btrfs_chunk, type, 64);
BTRFS_SETGET_FUNCS(chunk_num_stripes, काष्ठा btrfs_chunk, num_stripes, 16);
BTRFS_SETGET_FUNCS(chunk_sub_stripes, काष्ठा btrfs_chunk, sub_stripes, 16);
BTRFS_SETGET_FUNCS(stripe_devid, काष्ठा btrfs_stripe, devid, 64);
BTRFS_SETGET_FUNCS(stripe_offset, काष्ठा btrfs_stripe, offset, 64);

अटल अंतरभूत अक्षर *btrfs_stripe_dev_uuid(काष्ठा btrfs_stripe *s)
अणु
	वापस (अक्षर *)s + दुरत्व(काष्ठा btrfs_stripe, dev_uuid);
पूर्ण

BTRFS_SETGET_STACK_FUNCS(stack_chunk_length, काष्ठा btrfs_chunk, length, 64);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_owner, काष्ठा btrfs_chunk, owner, 64);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_stripe_len, काष्ठा btrfs_chunk,
			 stripe_len, 64);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_io_align, काष्ठा btrfs_chunk,
			 io_align, 32);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_io_width, काष्ठा btrfs_chunk,
			 io_width, 32);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_sector_size, काष्ठा btrfs_chunk,
			 sector_size, 32);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_type, काष्ठा btrfs_chunk, type, 64);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_num_stripes, काष्ठा btrfs_chunk,
			 num_stripes, 16);
BTRFS_SETGET_STACK_FUNCS(stack_chunk_sub_stripes, काष्ठा btrfs_chunk,
			 sub_stripes, 16);
BTRFS_SETGET_STACK_FUNCS(stack_stripe_devid, काष्ठा btrfs_stripe, devid, 64);
BTRFS_SETGET_STACK_FUNCS(stack_stripe_offset, काष्ठा btrfs_stripe, offset, 64);

अटल अंतरभूत काष्ठा btrfs_stripe *btrfs_stripe_nr(काष्ठा btrfs_chunk *c,
						   पूर्णांक nr)
अणु
	अचिन्हित दीर्घ offset = (अचिन्हित दीर्घ)c;
	offset += दुरत्व(काष्ठा btrfs_chunk, stripe);
	offset += nr * माप(काष्ठा btrfs_stripe);
	वापस (काष्ठा btrfs_stripe *)offset;
पूर्ण

अटल अंतरभूत अक्षर *btrfs_stripe_dev_uuid_nr(काष्ठा btrfs_chunk *c, पूर्णांक nr)
अणु
	वापस btrfs_stripe_dev_uuid(btrfs_stripe_nr(c, nr));
पूर्ण

अटल अंतरभूत u64 btrfs_stripe_offset_nr(स्थिर काष्ठा extent_buffer *eb,
					 काष्ठा btrfs_chunk *c, पूर्णांक nr)
अणु
	वापस btrfs_stripe_offset(eb, btrfs_stripe_nr(c, nr));
पूर्ण

अटल अंतरभूत u64 btrfs_stripe_devid_nr(स्थिर काष्ठा extent_buffer *eb,
					 काष्ठा btrfs_chunk *c, पूर्णांक nr)
अणु
	वापस btrfs_stripe_devid(eb, btrfs_stripe_nr(c, nr));
पूर्ण

/* काष्ठा btrfs_block_group_item */
BTRFS_SETGET_STACK_FUNCS(stack_block_group_used, काष्ठा btrfs_block_group_item,
			 used, 64);
BTRFS_SETGET_FUNCS(block_group_used, काष्ठा btrfs_block_group_item,
			 used, 64);
BTRFS_SETGET_STACK_FUNCS(stack_block_group_chunk_objectid,
			काष्ठा btrfs_block_group_item, chunk_objectid, 64);

BTRFS_SETGET_FUNCS(block_group_chunk_objectid,
		   काष्ठा btrfs_block_group_item, chunk_objectid, 64);
BTRFS_SETGET_FUNCS(block_group_flags,
		   काष्ठा btrfs_block_group_item, flags, 64);
BTRFS_SETGET_STACK_FUNCS(stack_block_group_flags,
			काष्ठा btrfs_block_group_item, flags, 64);

/* काष्ठा btrfs_मुक्त_space_info */
BTRFS_SETGET_FUNCS(मुक्त_space_extent_count, काष्ठा btrfs_मुक्त_space_info,
		   extent_count, 32);
BTRFS_SETGET_FUNCS(मुक्त_space_flags, काष्ठा btrfs_मुक्त_space_info, flags, 32);

/* काष्ठा btrfs_inode_ref */
BTRFS_SETGET_FUNCS(inode_ref_name_len, काष्ठा btrfs_inode_ref, name_len, 16);
BTRFS_SETGET_FUNCS(inode_ref_index, काष्ठा btrfs_inode_ref, index, 64);

/* काष्ठा btrfs_inode_extref */
BTRFS_SETGET_FUNCS(inode_extref_parent, काष्ठा btrfs_inode_extref,
		   parent_objectid, 64);
BTRFS_SETGET_FUNCS(inode_extref_name_len, काष्ठा btrfs_inode_extref,
		   name_len, 16);
BTRFS_SETGET_FUNCS(inode_extref_index, काष्ठा btrfs_inode_extref, index, 64);

/* काष्ठा btrfs_inode_item */
BTRFS_SETGET_FUNCS(inode_generation, काष्ठा btrfs_inode_item, generation, 64);
BTRFS_SETGET_FUNCS(inode_sequence, काष्ठा btrfs_inode_item, sequence, 64);
BTRFS_SETGET_FUNCS(inode_transid, काष्ठा btrfs_inode_item, transid, 64);
BTRFS_SETGET_FUNCS(inode_size, काष्ठा btrfs_inode_item, size, 64);
BTRFS_SETGET_FUNCS(inode_nbytes, काष्ठा btrfs_inode_item, nbytes, 64);
BTRFS_SETGET_FUNCS(inode_block_group, काष्ठा btrfs_inode_item, block_group, 64);
BTRFS_SETGET_FUNCS(inode_nlink, काष्ठा btrfs_inode_item, nlink, 32);
BTRFS_SETGET_FUNCS(inode_uid, काष्ठा btrfs_inode_item, uid, 32);
BTRFS_SETGET_FUNCS(inode_gid, काष्ठा btrfs_inode_item, gid, 32);
BTRFS_SETGET_FUNCS(inode_mode, काष्ठा btrfs_inode_item, mode, 32);
BTRFS_SETGET_FUNCS(inode_rdev, काष्ठा btrfs_inode_item, rdev, 64);
BTRFS_SETGET_FUNCS(inode_flags, काष्ठा btrfs_inode_item, flags, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_generation, काष्ठा btrfs_inode_item,
			 generation, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_sequence, काष्ठा btrfs_inode_item,
			 sequence, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_transid, काष्ठा btrfs_inode_item,
			 transid, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_size, काष्ठा btrfs_inode_item, size, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_nbytes, काष्ठा btrfs_inode_item,
			 nbytes, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_block_group, काष्ठा btrfs_inode_item,
			 block_group, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_nlink, काष्ठा btrfs_inode_item, nlink, 32);
BTRFS_SETGET_STACK_FUNCS(stack_inode_uid, काष्ठा btrfs_inode_item, uid, 32);
BTRFS_SETGET_STACK_FUNCS(stack_inode_gid, काष्ठा btrfs_inode_item, gid, 32);
BTRFS_SETGET_STACK_FUNCS(stack_inode_mode, काष्ठा btrfs_inode_item, mode, 32);
BTRFS_SETGET_STACK_FUNCS(stack_inode_rdev, काष्ठा btrfs_inode_item, rdev, 64);
BTRFS_SETGET_STACK_FUNCS(stack_inode_flags, काष्ठा btrfs_inode_item, flags, 64);
BTRFS_SETGET_FUNCS(बारpec_sec, काष्ठा btrfs_बारpec, sec, 64);
BTRFS_SETGET_FUNCS(बारpec_nsec, काष्ठा btrfs_बारpec, nsec, 32);
BTRFS_SETGET_STACK_FUNCS(stack_बारpec_sec, काष्ठा btrfs_बारpec, sec, 64);
BTRFS_SETGET_STACK_FUNCS(stack_बारpec_nsec, काष्ठा btrfs_बारpec, nsec, 32);

/* काष्ठा btrfs_dev_extent */
BTRFS_SETGET_FUNCS(dev_extent_chunk_tree, काष्ठा btrfs_dev_extent,
		   chunk_tree, 64);
BTRFS_SETGET_FUNCS(dev_extent_chunk_objectid, काष्ठा btrfs_dev_extent,
		   chunk_objectid, 64);
BTRFS_SETGET_FUNCS(dev_extent_chunk_offset, काष्ठा btrfs_dev_extent,
		   chunk_offset, 64);
BTRFS_SETGET_FUNCS(dev_extent_length, काष्ठा btrfs_dev_extent, length, 64);
BTRFS_SETGET_FUNCS(extent_refs, काष्ठा btrfs_extent_item, refs, 64);
BTRFS_SETGET_FUNCS(extent_generation, काष्ठा btrfs_extent_item,
		   generation, 64);
BTRFS_SETGET_FUNCS(extent_flags, काष्ठा btrfs_extent_item, flags, 64);

BTRFS_SETGET_FUNCS(tree_block_level, काष्ठा btrfs_tree_block_info, level, 8);

अटल अंतरभूत व्योम btrfs_tree_block_key(स्थिर काष्ठा extent_buffer *eb,
					काष्ठा btrfs_tree_block_info *item,
					काष्ठा btrfs_disk_key *key)
अणु
	पढ़ो_eb_member(eb, item, काष्ठा btrfs_tree_block_info, key, key);
पूर्ण

अटल अंतरभूत व्योम btrfs_set_tree_block_key(स्थिर काष्ठा extent_buffer *eb,
					    काष्ठा btrfs_tree_block_info *item,
					    काष्ठा btrfs_disk_key *key)
अणु
	ग_लिखो_eb_member(eb, item, काष्ठा btrfs_tree_block_info, key, key);
पूर्ण

BTRFS_SETGET_FUNCS(extent_data_ref_root, काष्ठा btrfs_extent_data_ref,
		   root, 64);
BTRFS_SETGET_FUNCS(extent_data_ref_objectid, काष्ठा btrfs_extent_data_ref,
		   objectid, 64);
BTRFS_SETGET_FUNCS(extent_data_ref_offset, काष्ठा btrfs_extent_data_ref,
		   offset, 64);
BTRFS_SETGET_FUNCS(extent_data_ref_count, काष्ठा btrfs_extent_data_ref,
		   count, 32);

BTRFS_SETGET_FUNCS(shared_data_ref_count, काष्ठा btrfs_shared_data_ref,
		   count, 32);

BTRFS_SETGET_FUNCS(extent_अंतरभूत_ref_type, काष्ठा btrfs_extent_अंतरभूत_ref,
		   type, 8);
BTRFS_SETGET_FUNCS(extent_अंतरभूत_ref_offset, काष्ठा btrfs_extent_अंतरभूत_ref,
		   offset, 64);

अटल अंतरभूत u32 btrfs_extent_अंतरभूत_ref_size(पूर्णांक type)
अणु
	अगर (type == BTRFS_TREE_BLOCK_REF_KEY ||
	    type == BTRFS_SHARED_BLOCK_REF_KEY)
		वापस माप(काष्ठा btrfs_extent_अंतरभूत_ref);
	अगर (type == BTRFS_SHARED_DATA_REF_KEY)
		वापस माप(काष्ठा btrfs_shared_data_ref) +
		       माप(काष्ठा btrfs_extent_अंतरभूत_ref);
	अगर (type == BTRFS_EXTENT_DATA_REF_KEY)
		वापस माप(काष्ठा btrfs_extent_data_ref) +
		       दुरत्व(काष्ठा btrfs_extent_अंतरभूत_ref, offset);
	वापस 0;
पूर्ण

/* काष्ठा btrfs_node */
BTRFS_SETGET_FUNCS(key_blockptr, काष्ठा btrfs_key_ptr, blockptr, 64);
BTRFS_SETGET_FUNCS(key_generation, काष्ठा btrfs_key_ptr, generation, 64);
BTRFS_SETGET_STACK_FUNCS(stack_key_blockptr, काष्ठा btrfs_key_ptr,
			 blockptr, 64);
BTRFS_SETGET_STACK_FUNCS(stack_key_generation, काष्ठा btrfs_key_ptr,
			 generation, 64);

अटल अंतरभूत u64 btrfs_node_blockptr(स्थिर काष्ठा extent_buffer *eb, पूर्णांक nr)
अणु
	अचिन्हित दीर्घ ptr;
	ptr = दुरत्व(काष्ठा btrfs_node, ptrs) +
		माप(काष्ठा btrfs_key_ptr) * nr;
	वापस btrfs_key_blockptr(eb, (काष्ठा btrfs_key_ptr *)ptr);
पूर्ण

अटल अंतरभूत व्योम btrfs_set_node_blockptr(स्थिर काष्ठा extent_buffer *eb,
					   पूर्णांक nr, u64 val)
अणु
	अचिन्हित दीर्घ ptr;
	ptr = दुरत्व(काष्ठा btrfs_node, ptrs) +
		माप(काष्ठा btrfs_key_ptr) * nr;
	btrfs_set_key_blockptr(eb, (काष्ठा btrfs_key_ptr *)ptr, val);
पूर्ण

अटल अंतरभूत u64 btrfs_node_ptr_generation(स्थिर काष्ठा extent_buffer *eb, पूर्णांक nr)
अणु
	अचिन्हित दीर्घ ptr;
	ptr = दुरत्व(काष्ठा btrfs_node, ptrs) +
		माप(काष्ठा btrfs_key_ptr) * nr;
	वापस btrfs_key_generation(eb, (काष्ठा btrfs_key_ptr *)ptr);
पूर्ण

अटल अंतरभूत व्योम btrfs_set_node_ptr_generation(स्थिर काष्ठा extent_buffer *eb,
						 पूर्णांक nr, u64 val)
अणु
	अचिन्हित दीर्घ ptr;
	ptr = दुरत्व(काष्ठा btrfs_node, ptrs) +
		माप(काष्ठा btrfs_key_ptr) * nr;
	btrfs_set_key_generation(eb, (काष्ठा btrfs_key_ptr *)ptr, val);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ btrfs_node_key_ptr_offset(पूर्णांक nr)
अणु
	वापस दुरत्व(काष्ठा btrfs_node, ptrs) +
		माप(काष्ठा btrfs_key_ptr) * nr;
पूर्ण

व्योम btrfs_node_key(स्थिर काष्ठा extent_buffer *eb,
		    काष्ठा btrfs_disk_key *disk_key, पूर्णांक nr);

अटल अंतरभूत व्योम btrfs_set_node_key(स्थिर काष्ठा extent_buffer *eb,
				      काष्ठा btrfs_disk_key *disk_key, पूर्णांक nr)
अणु
	अचिन्हित दीर्घ ptr;
	ptr = btrfs_node_key_ptr_offset(nr);
	ग_लिखो_eb_member(eb, (काष्ठा btrfs_key_ptr *)ptr,
		       काष्ठा btrfs_key_ptr, key, disk_key);
पूर्ण

/* काष्ठा btrfs_item */
BTRFS_SETGET_FUNCS(item_offset, काष्ठा btrfs_item, offset, 32);
BTRFS_SETGET_FUNCS(item_size, काष्ठा btrfs_item, size, 32);
BTRFS_SETGET_STACK_FUNCS(stack_item_offset, काष्ठा btrfs_item, offset, 32);
BTRFS_SETGET_STACK_FUNCS(stack_item_size, काष्ठा btrfs_item, size, 32);

अटल अंतरभूत अचिन्हित दीर्घ btrfs_item_nr_offset(पूर्णांक nr)
अणु
	वापस दुरत्व(काष्ठा btrfs_leaf, items) +
		माप(काष्ठा btrfs_item) * nr;
पूर्ण

अटल अंतरभूत काष्ठा btrfs_item *btrfs_item_nr(पूर्णांक nr)
अणु
	वापस (काष्ठा btrfs_item *)btrfs_item_nr_offset(nr);
पूर्ण

अटल अंतरभूत u32 btrfs_item_end(स्थिर काष्ठा extent_buffer *eb,
				 काष्ठा btrfs_item *item)
अणु
	वापस btrfs_item_offset(eb, item) + btrfs_item_size(eb, item);
पूर्ण

अटल अंतरभूत u32 btrfs_item_end_nr(स्थिर काष्ठा extent_buffer *eb, पूर्णांक nr)
अणु
	वापस btrfs_item_end(eb, btrfs_item_nr(nr));
पूर्ण

अटल अंतरभूत u32 btrfs_item_offset_nr(स्थिर काष्ठा extent_buffer *eb, पूर्णांक nr)
अणु
	वापस btrfs_item_offset(eb, btrfs_item_nr(nr));
पूर्ण

अटल अंतरभूत u32 btrfs_item_size_nr(स्थिर काष्ठा extent_buffer *eb, पूर्णांक nr)
अणु
	वापस btrfs_item_size(eb, btrfs_item_nr(nr));
पूर्ण

अटल अंतरभूत व्योम btrfs_item_key(स्थिर काष्ठा extent_buffer *eb,
			   काष्ठा btrfs_disk_key *disk_key, पूर्णांक nr)
अणु
	काष्ठा btrfs_item *item = btrfs_item_nr(nr);
	पढ़ो_eb_member(eb, item, काष्ठा btrfs_item, key, disk_key);
पूर्ण

अटल अंतरभूत व्योम btrfs_set_item_key(काष्ठा extent_buffer *eb,
			       काष्ठा btrfs_disk_key *disk_key, पूर्णांक nr)
अणु
	काष्ठा btrfs_item *item = btrfs_item_nr(nr);
	ग_लिखो_eb_member(eb, item, काष्ठा btrfs_item, key, disk_key);
पूर्ण

BTRFS_SETGET_FUNCS(dir_log_end, काष्ठा btrfs_dir_log_item, end, 64);

/*
 * काष्ठा btrfs_root_ref
 */
BTRFS_SETGET_FUNCS(root_ref_dirid, काष्ठा btrfs_root_ref, dirid, 64);
BTRFS_SETGET_FUNCS(root_ref_sequence, काष्ठा btrfs_root_ref, sequence, 64);
BTRFS_SETGET_FUNCS(root_ref_name_len, काष्ठा btrfs_root_ref, name_len, 16);

/* काष्ठा btrfs_dir_item */
BTRFS_SETGET_FUNCS(dir_data_len, काष्ठा btrfs_dir_item, data_len, 16);
BTRFS_SETGET_FUNCS(dir_type, काष्ठा btrfs_dir_item, type, 8);
BTRFS_SETGET_FUNCS(dir_name_len, काष्ठा btrfs_dir_item, name_len, 16);
BTRFS_SETGET_FUNCS(dir_transid, काष्ठा btrfs_dir_item, transid, 64);
BTRFS_SETGET_STACK_FUNCS(stack_dir_type, काष्ठा btrfs_dir_item, type, 8);
BTRFS_SETGET_STACK_FUNCS(stack_dir_data_len, काष्ठा btrfs_dir_item,
			 data_len, 16);
BTRFS_SETGET_STACK_FUNCS(stack_dir_name_len, काष्ठा btrfs_dir_item,
			 name_len, 16);
BTRFS_SETGET_STACK_FUNCS(stack_dir_transid, काष्ठा btrfs_dir_item,
			 transid, 64);

अटल अंतरभूत व्योम btrfs_dir_item_key(स्थिर काष्ठा extent_buffer *eb,
				      स्थिर काष्ठा btrfs_dir_item *item,
				      काष्ठा btrfs_disk_key *key)
अणु
	पढ़ो_eb_member(eb, item, काष्ठा btrfs_dir_item, location, key);
पूर्ण

अटल अंतरभूत व्योम btrfs_set_dir_item_key(काष्ठा extent_buffer *eb,
					  काष्ठा btrfs_dir_item *item,
					  स्थिर काष्ठा btrfs_disk_key *key)
अणु
	ग_लिखो_eb_member(eb, item, काष्ठा btrfs_dir_item, location, key);
पूर्ण

BTRFS_SETGET_FUNCS(मुक्त_space_entries, काष्ठा btrfs_मुक्त_space_header,
		   num_entries, 64);
BTRFS_SETGET_FUNCS(मुक्त_space_biपंचांगaps, काष्ठा btrfs_मुक्त_space_header,
		   num_biपंचांगaps, 64);
BTRFS_SETGET_FUNCS(मुक्त_space_generation, काष्ठा btrfs_मुक्त_space_header,
		   generation, 64);

अटल अंतरभूत व्योम btrfs_मुक्त_space_key(स्थिर काष्ठा extent_buffer *eb,
					स्थिर काष्ठा btrfs_मुक्त_space_header *h,
					काष्ठा btrfs_disk_key *key)
अणु
	पढ़ो_eb_member(eb, h, काष्ठा btrfs_मुक्त_space_header, location, key);
पूर्ण

अटल अंतरभूत व्योम btrfs_set_मुक्त_space_key(काष्ठा extent_buffer *eb,
					    काष्ठा btrfs_मुक्त_space_header *h,
					    स्थिर काष्ठा btrfs_disk_key *key)
अणु
	ग_लिखो_eb_member(eb, h, काष्ठा btrfs_मुक्त_space_header, location, key);
पूर्ण

/* काष्ठा btrfs_disk_key */
BTRFS_SETGET_STACK_FUNCS(disk_key_objectid, काष्ठा btrfs_disk_key,
			 objectid, 64);
BTRFS_SETGET_STACK_FUNCS(disk_key_offset, काष्ठा btrfs_disk_key, offset, 64);
BTRFS_SETGET_STACK_FUNCS(disk_key_type, काष्ठा btrfs_disk_key, type, 8);

#अगर_घोषित __LITTLE_ENDIAN

/*
 * Optimized helpers क्रम little-endian architectures where CPU and on-disk
 * काष्ठाures have the same endianness and we can skip conversions.
 */

अटल अंतरभूत व्योम btrfs_disk_key_to_cpu(काष्ठा btrfs_key *cpu_key,
					 स्थिर काष्ठा btrfs_disk_key *disk_key)
अणु
	स_नकल(cpu_key, disk_key, माप(काष्ठा btrfs_key));
पूर्ण

अटल अंतरभूत व्योम btrfs_cpu_key_to_disk(काष्ठा btrfs_disk_key *disk_key,
					 स्थिर काष्ठा btrfs_key *cpu_key)
अणु
	स_नकल(disk_key, cpu_key, माप(काष्ठा btrfs_key));
पूर्ण

अटल अंतरभूत व्योम btrfs_node_key_to_cpu(स्थिर काष्ठा extent_buffer *eb,
					 काष्ठा btrfs_key *cpu_key, पूर्णांक nr)
अणु
	काष्ठा btrfs_disk_key *disk_key = (काष्ठा btrfs_disk_key *)cpu_key;

	btrfs_node_key(eb, disk_key, nr);
पूर्ण

अटल अंतरभूत व्योम btrfs_item_key_to_cpu(स्थिर काष्ठा extent_buffer *eb,
					 काष्ठा btrfs_key *cpu_key, पूर्णांक nr)
अणु
	काष्ठा btrfs_disk_key *disk_key = (काष्ठा btrfs_disk_key *)cpu_key;

	btrfs_item_key(eb, disk_key, nr);
पूर्ण

अटल अंतरभूत व्योम btrfs_dir_item_key_to_cpu(स्थिर काष्ठा extent_buffer *eb,
					     स्थिर काष्ठा btrfs_dir_item *item,
					     काष्ठा btrfs_key *cpu_key)
अणु
	काष्ठा btrfs_disk_key *disk_key = (काष्ठा btrfs_disk_key *)cpu_key;

	btrfs_dir_item_key(eb, item, disk_key);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम btrfs_disk_key_to_cpu(काष्ठा btrfs_key *cpu,
					 स्थिर काष्ठा btrfs_disk_key *disk)
अणु
	cpu->offset = le64_to_cpu(disk->offset);
	cpu->type = disk->type;
	cpu->objectid = le64_to_cpu(disk->objectid);
पूर्ण

अटल अंतरभूत व्योम btrfs_cpu_key_to_disk(काष्ठा btrfs_disk_key *disk,
					 स्थिर काष्ठा btrfs_key *cpu)
अणु
	disk->offset = cpu_to_le64(cpu->offset);
	disk->type = cpu->type;
	disk->objectid = cpu_to_le64(cpu->objectid);
पूर्ण

अटल अंतरभूत व्योम btrfs_node_key_to_cpu(स्थिर काष्ठा extent_buffer *eb,
					 काष्ठा btrfs_key *key, पूर्णांक nr)
अणु
	काष्ठा btrfs_disk_key disk_key;
	btrfs_node_key(eb, &disk_key, nr);
	btrfs_disk_key_to_cpu(key, &disk_key);
पूर्ण

अटल अंतरभूत व्योम btrfs_item_key_to_cpu(स्थिर काष्ठा extent_buffer *eb,
					 काष्ठा btrfs_key *key, पूर्णांक nr)
अणु
	काष्ठा btrfs_disk_key disk_key;
	btrfs_item_key(eb, &disk_key, nr);
	btrfs_disk_key_to_cpu(key, &disk_key);
पूर्ण

अटल अंतरभूत व्योम btrfs_dir_item_key_to_cpu(स्थिर काष्ठा extent_buffer *eb,
					     स्थिर काष्ठा btrfs_dir_item *item,
					     काष्ठा btrfs_key *key)
अणु
	काष्ठा btrfs_disk_key disk_key;
	btrfs_dir_item_key(eb, item, &disk_key);
	btrfs_disk_key_to_cpu(key, &disk_key);
पूर्ण

#पूर्ण_अगर

/* काष्ठा btrfs_header */
BTRFS_SETGET_HEADER_FUNCS(header_bytenr, काष्ठा btrfs_header, bytenr, 64);
BTRFS_SETGET_HEADER_FUNCS(header_generation, काष्ठा btrfs_header,
			  generation, 64);
BTRFS_SETGET_HEADER_FUNCS(header_owner, काष्ठा btrfs_header, owner, 64);
BTRFS_SETGET_HEADER_FUNCS(header_nritems, काष्ठा btrfs_header, nritems, 32);
BTRFS_SETGET_HEADER_FUNCS(header_flags, काष्ठा btrfs_header, flags, 64);
BTRFS_SETGET_HEADER_FUNCS(header_level, काष्ठा btrfs_header, level, 8);
BTRFS_SETGET_STACK_FUNCS(stack_header_generation, काष्ठा btrfs_header,
			 generation, 64);
BTRFS_SETGET_STACK_FUNCS(stack_header_owner, काष्ठा btrfs_header, owner, 64);
BTRFS_SETGET_STACK_FUNCS(stack_header_nritems, काष्ठा btrfs_header,
			 nritems, 32);
BTRFS_SETGET_STACK_FUNCS(stack_header_bytenr, काष्ठा btrfs_header, bytenr, 64);

अटल अंतरभूत पूर्णांक btrfs_header_flag(स्थिर काष्ठा extent_buffer *eb, u64 flag)
अणु
	वापस (btrfs_header_flags(eb) & flag) == flag;
पूर्ण

अटल अंतरभूत व्योम btrfs_set_header_flag(काष्ठा extent_buffer *eb, u64 flag)
अणु
	u64 flags = btrfs_header_flags(eb);
	btrfs_set_header_flags(eb, flags | flag);
पूर्ण

अटल अंतरभूत व्योम btrfs_clear_header_flag(काष्ठा extent_buffer *eb, u64 flag)
अणु
	u64 flags = btrfs_header_flags(eb);
	btrfs_set_header_flags(eb, flags & ~flag);
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_header_backref_rev(स्थिर काष्ठा extent_buffer *eb)
अणु
	u64 flags = btrfs_header_flags(eb);
	वापस flags >> BTRFS_BACKREF_REV_SHIFT;
पूर्ण

अटल अंतरभूत व्योम btrfs_set_header_backref_rev(काष्ठा extent_buffer *eb,
						पूर्णांक rev)
अणु
	u64 flags = btrfs_header_flags(eb);
	flags &= ~BTRFS_BACKREF_REV_MASK;
	flags |= (u64)rev << BTRFS_BACKREF_REV_SHIFT;
	btrfs_set_header_flags(eb, flags);
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_is_leaf(स्थिर काष्ठा extent_buffer *eb)
अणु
	वापस btrfs_header_level(eb) == 0;
पूर्ण

/* काष्ठा btrfs_root_item */
BTRFS_SETGET_FUNCS(disk_root_generation, काष्ठा btrfs_root_item,
		   generation, 64);
BTRFS_SETGET_FUNCS(disk_root_refs, काष्ठा btrfs_root_item, refs, 32);
BTRFS_SETGET_FUNCS(disk_root_bytenr, काष्ठा btrfs_root_item, bytenr, 64);
BTRFS_SETGET_FUNCS(disk_root_level, काष्ठा btrfs_root_item, level, 8);

BTRFS_SETGET_STACK_FUNCS(root_generation, काष्ठा btrfs_root_item,
			 generation, 64);
BTRFS_SETGET_STACK_FUNCS(root_bytenr, काष्ठा btrfs_root_item, bytenr, 64);
BTRFS_SETGET_STACK_FUNCS(root_drop_level, काष्ठा btrfs_root_item, drop_level, 8);
BTRFS_SETGET_STACK_FUNCS(root_level, काष्ठा btrfs_root_item, level, 8);
BTRFS_SETGET_STACK_FUNCS(root_dirid, काष्ठा btrfs_root_item, root_dirid, 64);
BTRFS_SETGET_STACK_FUNCS(root_refs, काष्ठा btrfs_root_item, refs, 32);
BTRFS_SETGET_STACK_FUNCS(root_flags, काष्ठा btrfs_root_item, flags, 64);
BTRFS_SETGET_STACK_FUNCS(root_used, काष्ठा btrfs_root_item, bytes_used, 64);
BTRFS_SETGET_STACK_FUNCS(root_limit, काष्ठा btrfs_root_item, byte_limit, 64);
BTRFS_SETGET_STACK_FUNCS(root_last_snapshot, काष्ठा btrfs_root_item,
			 last_snapshot, 64);
BTRFS_SETGET_STACK_FUNCS(root_generation_v2, काष्ठा btrfs_root_item,
			 generation_v2, 64);
BTRFS_SETGET_STACK_FUNCS(root_ctransid, काष्ठा btrfs_root_item,
			 ctransid, 64);
BTRFS_SETGET_STACK_FUNCS(root_otransid, काष्ठा btrfs_root_item,
			 otransid, 64);
BTRFS_SETGET_STACK_FUNCS(root_stransid, काष्ठा btrfs_root_item,
			 stransid, 64);
BTRFS_SETGET_STACK_FUNCS(root_rtransid, काष्ठा btrfs_root_item,
			 rtransid, 64);

अटल अंतरभूत bool btrfs_root_पढ़ोonly(स्थिर काष्ठा btrfs_root *root)
अणु
	वापस (root->root_item.flags & cpu_to_le64(BTRFS_ROOT_SUBVOL_RDONLY)) != 0;
पूर्ण

अटल अंतरभूत bool btrfs_root_dead(स्थिर काष्ठा btrfs_root *root)
अणु
	वापस (root->root_item.flags & cpu_to_le64(BTRFS_ROOT_SUBVOL_DEAD)) != 0;
पूर्ण

/* काष्ठा btrfs_root_backup */
BTRFS_SETGET_STACK_FUNCS(backup_tree_root, काष्ठा btrfs_root_backup,
		   tree_root, 64);
BTRFS_SETGET_STACK_FUNCS(backup_tree_root_gen, काष्ठा btrfs_root_backup,
		   tree_root_gen, 64);
BTRFS_SETGET_STACK_FUNCS(backup_tree_root_level, काष्ठा btrfs_root_backup,
		   tree_root_level, 8);

BTRFS_SETGET_STACK_FUNCS(backup_chunk_root, काष्ठा btrfs_root_backup,
		   chunk_root, 64);
BTRFS_SETGET_STACK_FUNCS(backup_chunk_root_gen, काष्ठा btrfs_root_backup,
		   chunk_root_gen, 64);
BTRFS_SETGET_STACK_FUNCS(backup_chunk_root_level, काष्ठा btrfs_root_backup,
		   chunk_root_level, 8);

BTRFS_SETGET_STACK_FUNCS(backup_extent_root, काष्ठा btrfs_root_backup,
		   extent_root, 64);
BTRFS_SETGET_STACK_FUNCS(backup_extent_root_gen, काष्ठा btrfs_root_backup,
		   extent_root_gen, 64);
BTRFS_SETGET_STACK_FUNCS(backup_extent_root_level, काष्ठा btrfs_root_backup,
		   extent_root_level, 8);

BTRFS_SETGET_STACK_FUNCS(backup_fs_root, काष्ठा btrfs_root_backup,
		   fs_root, 64);
BTRFS_SETGET_STACK_FUNCS(backup_fs_root_gen, काष्ठा btrfs_root_backup,
		   fs_root_gen, 64);
BTRFS_SETGET_STACK_FUNCS(backup_fs_root_level, काष्ठा btrfs_root_backup,
		   fs_root_level, 8);

BTRFS_SETGET_STACK_FUNCS(backup_dev_root, काष्ठा btrfs_root_backup,
		   dev_root, 64);
BTRFS_SETGET_STACK_FUNCS(backup_dev_root_gen, काष्ठा btrfs_root_backup,
		   dev_root_gen, 64);
BTRFS_SETGET_STACK_FUNCS(backup_dev_root_level, काष्ठा btrfs_root_backup,
		   dev_root_level, 8);

BTRFS_SETGET_STACK_FUNCS(backup_csum_root, काष्ठा btrfs_root_backup,
		   csum_root, 64);
BTRFS_SETGET_STACK_FUNCS(backup_csum_root_gen, काष्ठा btrfs_root_backup,
		   csum_root_gen, 64);
BTRFS_SETGET_STACK_FUNCS(backup_csum_root_level, काष्ठा btrfs_root_backup,
		   csum_root_level, 8);
BTRFS_SETGET_STACK_FUNCS(backup_total_bytes, काष्ठा btrfs_root_backup,
		   total_bytes, 64);
BTRFS_SETGET_STACK_FUNCS(backup_bytes_used, काष्ठा btrfs_root_backup,
		   bytes_used, 64);
BTRFS_SETGET_STACK_FUNCS(backup_num_devices, काष्ठा btrfs_root_backup,
		   num_devices, 64);

/* काष्ठा btrfs_balance_item */
BTRFS_SETGET_FUNCS(balance_flags, काष्ठा btrfs_balance_item, flags, 64);

अटल अंतरभूत व्योम btrfs_balance_data(स्थिर काष्ठा extent_buffer *eb,
				      स्थिर काष्ठा btrfs_balance_item *bi,
				      काष्ठा btrfs_disk_balance_args *ba)
अणु
	पढ़ो_eb_member(eb, bi, काष्ठा btrfs_balance_item, data, ba);
पूर्ण

अटल अंतरभूत व्योम btrfs_set_balance_data(काष्ठा extent_buffer *eb,
				  काष्ठा btrfs_balance_item *bi,
				  स्थिर काष्ठा btrfs_disk_balance_args *ba)
अणु
	ग_लिखो_eb_member(eb, bi, काष्ठा btrfs_balance_item, data, ba);
पूर्ण

अटल अंतरभूत व्योम btrfs_balance_meta(स्थिर काष्ठा extent_buffer *eb,
				      स्थिर काष्ठा btrfs_balance_item *bi,
				      काष्ठा btrfs_disk_balance_args *ba)
अणु
	पढ़ो_eb_member(eb, bi, काष्ठा btrfs_balance_item, meta, ba);
पूर्ण

अटल अंतरभूत व्योम btrfs_set_balance_meta(काष्ठा extent_buffer *eb,
				  काष्ठा btrfs_balance_item *bi,
				  स्थिर काष्ठा btrfs_disk_balance_args *ba)
अणु
	ग_लिखो_eb_member(eb, bi, काष्ठा btrfs_balance_item, meta, ba);
पूर्ण

अटल अंतरभूत व्योम btrfs_balance_sys(स्थिर काष्ठा extent_buffer *eb,
				     स्थिर काष्ठा btrfs_balance_item *bi,
				     काष्ठा btrfs_disk_balance_args *ba)
अणु
	पढ़ो_eb_member(eb, bi, काष्ठा btrfs_balance_item, sys, ba);
पूर्ण

अटल अंतरभूत व्योम btrfs_set_balance_sys(काष्ठा extent_buffer *eb,
				 काष्ठा btrfs_balance_item *bi,
				 स्थिर काष्ठा btrfs_disk_balance_args *ba)
अणु
	ग_लिखो_eb_member(eb, bi, काष्ठा btrfs_balance_item, sys, ba);
पूर्ण

अटल अंतरभूत व्योम
btrfs_disk_balance_args_to_cpu(काष्ठा btrfs_balance_args *cpu,
			       स्थिर काष्ठा btrfs_disk_balance_args *disk)
अणु
	स_रखो(cpu, 0, माप(*cpu));

	cpu->profiles = le64_to_cpu(disk->profiles);
	cpu->usage = le64_to_cpu(disk->usage);
	cpu->devid = le64_to_cpu(disk->devid);
	cpu->pstart = le64_to_cpu(disk->pstart);
	cpu->pend = le64_to_cpu(disk->pend);
	cpu->vstart = le64_to_cpu(disk->vstart);
	cpu->vend = le64_to_cpu(disk->vend);
	cpu->target = le64_to_cpu(disk->target);
	cpu->flags = le64_to_cpu(disk->flags);
	cpu->limit = le64_to_cpu(disk->limit);
	cpu->stripes_min = le32_to_cpu(disk->stripes_min);
	cpu->stripes_max = le32_to_cpu(disk->stripes_max);
पूर्ण

अटल अंतरभूत व्योम
btrfs_cpu_balance_args_to_disk(काष्ठा btrfs_disk_balance_args *disk,
			       स्थिर काष्ठा btrfs_balance_args *cpu)
अणु
	स_रखो(disk, 0, माप(*disk));

	disk->profiles = cpu_to_le64(cpu->profiles);
	disk->usage = cpu_to_le64(cpu->usage);
	disk->devid = cpu_to_le64(cpu->devid);
	disk->pstart = cpu_to_le64(cpu->pstart);
	disk->pend = cpu_to_le64(cpu->pend);
	disk->vstart = cpu_to_le64(cpu->vstart);
	disk->vend = cpu_to_le64(cpu->vend);
	disk->target = cpu_to_le64(cpu->target);
	disk->flags = cpu_to_le64(cpu->flags);
	disk->limit = cpu_to_le64(cpu->limit);
	disk->stripes_min = cpu_to_le32(cpu->stripes_min);
	disk->stripes_max = cpu_to_le32(cpu->stripes_max);
पूर्ण

/* काष्ठा btrfs_super_block */
BTRFS_SETGET_STACK_FUNCS(super_bytenr, काष्ठा btrfs_super_block, bytenr, 64);
BTRFS_SETGET_STACK_FUNCS(super_flags, काष्ठा btrfs_super_block, flags, 64);
BTRFS_SETGET_STACK_FUNCS(super_generation, काष्ठा btrfs_super_block,
			 generation, 64);
BTRFS_SETGET_STACK_FUNCS(super_root, काष्ठा btrfs_super_block, root, 64);
BTRFS_SETGET_STACK_FUNCS(super_sys_array_size,
			 काष्ठा btrfs_super_block, sys_chunk_array_size, 32);
BTRFS_SETGET_STACK_FUNCS(super_chunk_root_generation,
			 काष्ठा btrfs_super_block, chunk_root_generation, 64);
BTRFS_SETGET_STACK_FUNCS(super_root_level, काष्ठा btrfs_super_block,
			 root_level, 8);
BTRFS_SETGET_STACK_FUNCS(super_chunk_root, काष्ठा btrfs_super_block,
			 chunk_root, 64);
BTRFS_SETGET_STACK_FUNCS(super_chunk_root_level, काष्ठा btrfs_super_block,
			 chunk_root_level, 8);
BTRFS_SETGET_STACK_FUNCS(super_log_root, काष्ठा btrfs_super_block,
			 log_root, 64);
BTRFS_SETGET_STACK_FUNCS(super_log_root_transid, काष्ठा btrfs_super_block,
			 log_root_transid, 64);
BTRFS_SETGET_STACK_FUNCS(super_log_root_level, काष्ठा btrfs_super_block,
			 log_root_level, 8);
BTRFS_SETGET_STACK_FUNCS(super_total_bytes, काष्ठा btrfs_super_block,
			 total_bytes, 64);
BTRFS_SETGET_STACK_FUNCS(super_bytes_used, काष्ठा btrfs_super_block,
			 bytes_used, 64);
BTRFS_SETGET_STACK_FUNCS(super_sectorsize, काष्ठा btrfs_super_block,
			 sectorsize, 32);
BTRFS_SETGET_STACK_FUNCS(super_nodesize, काष्ठा btrfs_super_block,
			 nodesize, 32);
BTRFS_SETGET_STACK_FUNCS(super_stripesize, काष्ठा btrfs_super_block,
			 stripesize, 32);
BTRFS_SETGET_STACK_FUNCS(super_root_dir, काष्ठा btrfs_super_block,
			 root_dir_objectid, 64);
BTRFS_SETGET_STACK_FUNCS(super_num_devices, काष्ठा btrfs_super_block,
			 num_devices, 64);
BTRFS_SETGET_STACK_FUNCS(super_compat_flags, काष्ठा btrfs_super_block,
			 compat_flags, 64);
BTRFS_SETGET_STACK_FUNCS(super_compat_ro_flags, काष्ठा btrfs_super_block,
			 compat_ro_flags, 64);
BTRFS_SETGET_STACK_FUNCS(super_incompat_flags, काष्ठा btrfs_super_block,
			 incompat_flags, 64);
BTRFS_SETGET_STACK_FUNCS(super_csum_type, काष्ठा btrfs_super_block,
			 csum_type, 16);
BTRFS_SETGET_STACK_FUNCS(super_cache_generation, काष्ठा btrfs_super_block,
			 cache_generation, 64);
BTRFS_SETGET_STACK_FUNCS(super_magic, काष्ठा btrfs_super_block, magic, 64);
BTRFS_SETGET_STACK_FUNCS(super_uuid_tree_generation, काष्ठा btrfs_super_block,
			 uuid_tree_generation, 64);

पूर्णांक btrfs_super_csum_size(स्थिर काष्ठा btrfs_super_block *s);
स्थिर अक्षर *btrfs_super_csum_name(u16 csum_type);
स्थिर अक्षर *btrfs_super_csum_driver(u16 csum_type);
माप_प्रकार __attribute_स्थिर__ btrfs_get_num_csums(व्योम);


/*
 * The leaf data grows from end-to-front in the node.
 * this वापसs the address of the start of the last item,
 * which is the stop of the leaf data stack
 */
अटल अंतरभूत अचिन्हित पूर्णांक leaf_data_end(स्थिर काष्ठा extent_buffer *leaf)
अणु
	u32 nr = btrfs_header_nritems(leaf);

	अगर (nr == 0)
		वापस BTRFS_LEAF_DATA_SIZE(leaf->fs_info);
	वापस btrfs_item_offset_nr(leaf, nr - 1);
पूर्ण

/* काष्ठा btrfs_file_extent_item */
BTRFS_SETGET_STACK_FUNCS(stack_file_extent_type, काष्ठा btrfs_file_extent_item,
			 type, 8);
BTRFS_SETGET_STACK_FUNCS(stack_file_extent_disk_bytenr,
			 काष्ठा btrfs_file_extent_item, disk_bytenr, 64);
BTRFS_SETGET_STACK_FUNCS(stack_file_extent_offset,
			 काष्ठा btrfs_file_extent_item, offset, 64);
BTRFS_SETGET_STACK_FUNCS(stack_file_extent_generation,
			 काष्ठा btrfs_file_extent_item, generation, 64);
BTRFS_SETGET_STACK_FUNCS(stack_file_extent_num_bytes,
			 काष्ठा btrfs_file_extent_item, num_bytes, 64);
BTRFS_SETGET_STACK_FUNCS(stack_file_extent_ram_bytes,
			 काष्ठा btrfs_file_extent_item, ram_bytes, 64);
BTRFS_SETGET_STACK_FUNCS(stack_file_extent_disk_num_bytes,
			 काष्ठा btrfs_file_extent_item, disk_num_bytes, 64);
BTRFS_SETGET_STACK_FUNCS(stack_file_extent_compression,
			 काष्ठा btrfs_file_extent_item, compression, 8);

अटल अंतरभूत अचिन्हित दीर्घ
btrfs_file_extent_अंतरभूत_start(स्थिर काष्ठा btrfs_file_extent_item *e)
अणु
	वापस (अचिन्हित दीर्घ)e + BTRFS_खाता_EXTENT_INLINE_DATA_START;
पूर्ण

अटल अंतरभूत u32 btrfs_file_extent_calc_अंतरभूत_size(u32 datasize)
अणु
	वापस BTRFS_खाता_EXTENT_INLINE_DATA_START + datasize;
पूर्ण

BTRFS_SETGET_FUNCS(file_extent_type, काष्ठा btrfs_file_extent_item, type, 8);
BTRFS_SETGET_FUNCS(file_extent_disk_bytenr, काष्ठा btrfs_file_extent_item,
		   disk_bytenr, 64);
BTRFS_SETGET_FUNCS(file_extent_generation, काष्ठा btrfs_file_extent_item,
		   generation, 64);
BTRFS_SETGET_FUNCS(file_extent_disk_num_bytes, काष्ठा btrfs_file_extent_item,
		   disk_num_bytes, 64);
BTRFS_SETGET_FUNCS(file_extent_offset, काष्ठा btrfs_file_extent_item,
		  offset, 64);
BTRFS_SETGET_FUNCS(file_extent_num_bytes, काष्ठा btrfs_file_extent_item,
		   num_bytes, 64);
BTRFS_SETGET_FUNCS(file_extent_ram_bytes, काष्ठा btrfs_file_extent_item,
		   ram_bytes, 64);
BTRFS_SETGET_FUNCS(file_extent_compression, काष्ठा btrfs_file_extent_item,
		   compression, 8);
BTRFS_SETGET_FUNCS(file_extent_encryption, काष्ठा btrfs_file_extent_item,
		   encryption, 8);
BTRFS_SETGET_FUNCS(file_extent_other_encoding, काष्ठा btrfs_file_extent_item,
		   other_encoding, 16);

/*
 * this वापसs the number of bytes used by the item on disk, minus the
 * size of any extent headers.  If a file is compressed on disk, this is
 * the compressed size
 */
अटल अंतरभूत u32 btrfs_file_extent_अंतरभूत_item_len(
						स्थिर काष्ठा extent_buffer *eb,
						काष्ठा btrfs_item *e)
अणु
	वापस btrfs_item_size(eb, e) - BTRFS_खाता_EXTENT_INLINE_DATA_START;
पूर्ण

/* btrfs_qgroup_status_item */
BTRFS_SETGET_FUNCS(qgroup_status_generation, काष्ठा btrfs_qgroup_status_item,
		   generation, 64);
BTRFS_SETGET_FUNCS(qgroup_status_version, काष्ठा btrfs_qgroup_status_item,
		   version, 64);
BTRFS_SETGET_FUNCS(qgroup_status_flags, काष्ठा btrfs_qgroup_status_item,
		   flags, 64);
BTRFS_SETGET_FUNCS(qgroup_status_rescan, काष्ठा btrfs_qgroup_status_item,
		   rescan, 64);

/* btrfs_qgroup_info_item */
BTRFS_SETGET_FUNCS(qgroup_info_generation, काष्ठा btrfs_qgroup_info_item,
		   generation, 64);
BTRFS_SETGET_FUNCS(qgroup_info_rfer, काष्ठा btrfs_qgroup_info_item, rfer, 64);
BTRFS_SETGET_FUNCS(qgroup_info_rfer_cmpr, काष्ठा btrfs_qgroup_info_item,
		   rfer_cmpr, 64);
BTRFS_SETGET_FUNCS(qgroup_info_excl, काष्ठा btrfs_qgroup_info_item, excl, 64);
BTRFS_SETGET_FUNCS(qgroup_info_excl_cmpr, काष्ठा btrfs_qgroup_info_item,
		   excl_cmpr, 64);

BTRFS_SETGET_STACK_FUNCS(stack_qgroup_info_generation,
			 काष्ठा btrfs_qgroup_info_item, generation, 64);
BTRFS_SETGET_STACK_FUNCS(stack_qgroup_info_rfer, काष्ठा btrfs_qgroup_info_item,
			 rfer, 64);
BTRFS_SETGET_STACK_FUNCS(stack_qgroup_info_rfer_cmpr,
			 काष्ठा btrfs_qgroup_info_item, rfer_cmpr, 64);
BTRFS_SETGET_STACK_FUNCS(stack_qgroup_info_excl, काष्ठा btrfs_qgroup_info_item,
			 excl, 64);
BTRFS_SETGET_STACK_FUNCS(stack_qgroup_info_excl_cmpr,
			 काष्ठा btrfs_qgroup_info_item, excl_cmpr, 64);

/* btrfs_qgroup_limit_item */
BTRFS_SETGET_FUNCS(qgroup_limit_flags, काष्ठा btrfs_qgroup_limit_item,
		   flags, 64);
BTRFS_SETGET_FUNCS(qgroup_limit_max_rfer, काष्ठा btrfs_qgroup_limit_item,
		   max_rfer, 64);
BTRFS_SETGET_FUNCS(qgroup_limit_max_excl, काष्ठा btrfs_qgroup_limit_item,
		   max_excl, 64);
BTRFS_SETGET_FUNCS(qgroup_limit_rsv_rfer, काष्ठा btrfs_qgroup_limit_item,
		   rsv_rfer, 64);
BTRFS_SETGET_FUNCS(qgroup_limit_rsv_excl, काष्ठा btrfs_qgroup_limit_item,
		   rsv_excl, 64);

/* btrfs_dev_replace_item */
BTRFS_SETGET_FUNCS(dev_replace_src_devid,
		   काष्ठा btrfs_dev_replace_item, src_devid, 64);
BTRFS_SETGET_FUNCS(dev_replace_cont_पढ़ोing_from_srcdev_mode,
		   काष्ठा btrfs_dev_replace_item, cont_पढ़ोing_from_srcdev_mode,
		   64);
BTRFS_SETGET_FUNCS(dev_replace_replace_state, काष्ठा btrfs_dev_replace_item,
		   replace_state, 64);
BTRFS_SETGET_FUNCS(dev_replace_समय_started, काष्ठा btrfs_dev_replace_item,
		   समय_started, 64);
BTRFS_SETGET_FUNCS(dev_replace_समय_stopped, काष्ठा btrfs_dev_replace_item,
		   समय_stopped, 64);
BTRFS_SETGET_FUNCS(dev_replace_num_ग_लिखो_errors, काष्ठा btrfs_dev_replace_item,
		   num_ग_लिखो_errors, 64);
BTRFS_SETGET_FUNCS(dev_replace_num_uncorrectable_पढ़ो_errors,
		   काष्ठा btrfs_dev_replace_item, num_uncorrectable_पढ़ो_errors,
		   64);
BTRFS_SETGET_FUNCS(dev_replace_cursor_left, काष्ठा btrfs_dev_replace_item,
		   cursor_left, 64);
BTRFS_SETGET_FUNCS(dev_replace_cursor_right, काष्ठा btrfs_dev_replace_item,
		   cursor_right, 64);

BTRFS_SETGET_STACK_FUNCS(stack_dev_replace_src_devid,
			 काष्ठा btrfs_dev_replace_item, src_devid, 64);
BTRFS_SETGET_STACK_FUNCS(stack_dev_replace_cont_पढ़ोing_from_srcdev_mode,
			 काष्ठा btrfs_dev_replace_item,
			 cont_पढ़ोing_from_srcdev_mode, 64);
BTRFS_SETGET_STACK_FUNCS(stack_dev_replace_replace_state,
			 काष्ठा btrfs_dev_replace_item, replace_state, 64);
BTRFS_SETGET_STACK_FUNCS(stack_dev_replace_समय_started,
			 काष्ठा btrfs_dev_replace_item, समय_started, 64);
BTRFS_SETGET_STACK_FUNCS(stack_dev_replace_समय_stopped,
			 काष्ठा btrfs_dev_replace_item, समय_stopped, 64);
BTRFS_SETGET_STACK_FUNCS(stack_dev_replace_num_ग_लिखो_errors,
			 काष्ठा btrfs_dev_replace_item, num_ग_लिखो_errors, 64);
BTRFS_SETGET_STACK_FUNCS(stack_dev_replace_num_uncorrectable_पढ़ो_errors,
			 काष्ठा btrfs_dev_replace_item,
			 num_uncorrectable_पढ़ो_errors, 64);
BTRFS_SETGET_STACK_FUNCS(stack_dev_replace_cursor_left,
			 काष्ठा btrfs_dev_replace_item, cursor_left, 64);
BTRFS_SETGET_STACK_FUNCS(stack_dev_replace_cursor_right,
			 काष्ठा btrfs_dev_replace_item, cursor_right, 64);

/* helper function to cast पूर्णांकo the data area of the leaf. */
#घोषणा btrfs_item_ptr(leaf, slot, type) \
	((type *)(BTRFS_LEAF_DATA_OFFSET + \
	btrfs_item_offset_nr(leaf, slot)))

#घोषणा btrfs_item_ptr_offset(leaf, slot) \
	((अचिन्हित दीर्घ)(BTRFS_LEAF_DATA_OFFSET + \
	btrfs_item_offset_nr(leaf, slot)))

अटल अंतरभूत u32 btrfs_crc32c(u32 crc, स्थिर व्योम *address, अचिन्हित length)
अणु
	वापस crc32c(crc, address, length);
पूर्ण

अटल अंतरभूत व्योम btrfs_crc32c_final(u32 crc, u8 *result)
अणु
	put_unaligned_le32(~crc, result);
पूर्ण

अटल अंतरभूत u64 btrfs_name_hash(स्थिर अक्षर *name, पूर्णांक len)
अणु
       वापस crc32c((u32)~1, name, len);
पूर्ण

/*
 * Figure the key offset of an extended inode ref
 */
अटल अंतरभूत u64 btrfs_extref_hash(u64 parent_objectid, स्थिर अक्षर *name,
                                   पूर्णांक len)
अणु
       वापस (u64) crc32c(parent_objectid, name, len);
पूर्ण

अटल अंतरभूत gfp_t btrfs_alloc_ग_लिखो_mask(काष्ठा address_space *mapping)
अणु
	वापस mapping_gfp_स्थिरraपूर्णांक(mapping, ~__GFP_FS);
पूर्ण

/* extent-tree.c */

क्रमागत btrfs_अंतरभूत_ref_type अणु
	BTRFS_REF_TYPE_INVALID,
	BTRFS_REF_TYPE_BLOCK,
	BTRFS_REF_TYPE_DATA,
	BTRFS_REF_TYPE_ANY,
पूर्ण;

पूर्णांक btrfs_get_extent_अंतरभूत_ref_type(स्थिर काष्ठा extent_buffer *eb,
				     काष्ठा btrfs_extent_अंतरभूत_ref *iref,
				     क्रमागत btrfs_अंतरभूत_ref_type is_data);
u64 hash_extent_data_ref(u64 root_objectid, u64 owner, u64 offset);

/*
 * Take the number of bytes to be checksummmed and figure out how many leaves
 * it would require to store the csums क्रम that many bytes.
 */
अटल अंतरभूत u64 btrfs_csum_bytes_to_leaves(
			स्थिर काष्ठा btrfs_fs_info *fs_info, u64 csum_bytes)
अणु
	स्थिर u64 num_csums = csum_bytes >> fs_info->sectorsize_bits;

	वापस DIV_ROUND_UP_ULL(num_csums, fs_info->csums_per_leaf);
पूर्ण

/*
 * Use this अगर we would be adding new items, as we could split nodes as we cow
 * करोwn the tree.
 */
अटल अंतरभूत u64 btrfs_calc_insert_metadata_size(काष्ठा btrfs_fs_info *fs_info,
						  अचिन्हित num_items)
अणु
	वापस (u64)fs_info->nodesize * BTRFS_MAX_LEVEL * 2 * num_items;
पूर्ण

/*
 * Doing a truncate or a modअगरication won't result in new nodes or leaves, just
 * what we need क्रम COW.
 */
अटल अंतरभूत u64 btrfs_calc_metadata_size(काष्ठा btrfs_fs_info *fs_info,
						 अचिन्हित num_items)
अणु
	वापस (u64)fs_info->nodesize * BTRFS_MAX_LEVEL * num_items;
पूर्ण

पूर्णांक btrfs_add_excluded_extent(काष्ठा btrfs_fs_info *fs_info,
			      u64 start, u64 num_bytes);
व्योम btrfs_मुक्त_excluded_extents(काष्ठा btrfs_block_group *cache);
पूर्णांक btrfs_run_delayed_refs(काष्ठा btrfs_trans_handle *trans,
			   अचिन्हित दीर्घ count);
व्योम btrfs_cleanup_ref_head_accounting(काष्ठा btrfs_fs_info *fs_info,
				  काष्ठा btrfs_delayed_ref_root *delayed_refs,
				  काष्ठा btrfs_delayed_ref_head *head);
पूर्णांक btrfs_lookup_data_extent(काष्ठा btrfs_fs_info *fs_info, u64 start, u64 len);
पूर्णांक btrfs_lookup_extent_info(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			     u64 offset, पूर्णांक metadata, u64 *refs, u64 *flags);
पूर्णांक btrfs_pin_extent(काष्ठा btrfs_trans_handle *trans, u64 bytenr, u64 num,
		     पूर्णांक reserved);
पूर्णांक btrfs_pin_extent_क्रम_log_replay(काष्ठा btrfs_trans_handle *trans,
				    u64 bytenr, u64 num_bytes);
पूर्णांक btrfs_exclude_logged_extents(काष्ठा extent_buffer *eb);
पूर्णांक btrfs_cross_ref_exist(काष्ठा btrfs_root *root,
			  u64 objectid, u64 offset, u64 bytenr, bool strict);
काष्ठा extent_buffer *btrfs_alloc_tree_block(काष्ठा btrfs_trans_handle *trans,
					     काष्ठा btrfs_root *root,
					     u64 parent, u64 root_objectid,
					     स्थिर काष्ठा btrfs_disk_key *key,
					     पूर्णांक level, u64 hपूर्णांक,
					     u64 empty_size,
					     क्रमागत btrfs_lock_nesting nest);
व्योम btrfs_मुक्त_tree_block(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   काष्ठा extent_buffer *buf,
			   u64 parent, पूर्णांक last_ref);
पूर्णांक btrfs_alloc_reserved_file_extent(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_root *root, u64 owner,
				     u64 offset, u64 ram_bytes,
				     काष्ठा btrfs_key *ins);
पूर्णांक btrfs_alloc_logged_file_extent(काष्ठा btrfs_trans_handle *trans,
				   u64 root_objectid, u64 owner, u64 offset,
				   काष्ठा btrfs_key *ins);
पूर्णांक btrfs_reserve_extent(काष्ठा btrfs_root *root, u64 ram_bytes, u64 num_bytes,
			 u64 min_alloc_size, u64 empty_size, u64 hपूर्णांक_byte,
			 काष्ठा btrfs_key *ins, पूर्णांक is_data, पूर्णांक delalloc);
पूर्णांक btrfs_inc_ref(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		  काष्ठा extent_buffer *buf, पूर्णांक full_backref);
पूर्णांक btrfs_dec_ref(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		  काष्ठा extent_buffer *buf, पूर्णांक full_backref);
पूर्णांक btrfs_set_disk_extent_flags(काष्ठा btrfs_trans_handle *trans,
				काष्ठा extent_buffer *eb, u64 flags,
				पूर्णांक level, पूर्णांक is_data);
पूर्णांक btrfs_मुक्त_extent(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_ref *ref);

पूर्णांक btrfs_मुक्त_reserved_extent(काष्ठा btrfs_fs_info *fs_info,
			       u64 start, u64 len, पूर्णांक delalloc);
पूर्णांक btrfs_pin_reserved_extent(काष्ठा btrfs_trans_handle *trans, u64 start,
			      u64 len);
पूर्णांक btrfs_finish_extent_commit(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_inc_extent_ref(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_ref *generic_ref);

व्योम btrfs_clear_space_info_full(काष्ठा btrfs_fs_info *info);

/*
 * Dअगरferent levels क्रम to flush space when करोing space reservations.
 *
 * The higher the level, the more methods we try to reclaim space.
 */
क्रमागत btrfs_reserve_flush_क्रमागत अणु
	/* If we are in the transaction, we can't flush anything.*/
	BTRFS_RESERVE_NO_FLUSH,

	/*
	 * Flush space by:
	 * - Running delayed inode items
	 * - Allocating a new chunk
	 */
	BTRFS_RESERVE_FLUSH_LIMIT,

	/*
	 * Flush space by:
	 * - Running delayed inode items
	 * - Running delayed refs
	 * - Running delalloc and रुकोing क्रम ordered extents
	 * - Allocating a new chunk
	 */
	BTRFS_RESERVE_FLUSH_EVICT,

	/*
	 * Flush space by above mentioned methods and by:
	 * - Running delayed iमाला_दो
	 * - Commiting transaction
	 *
	 * Can be पूर्णांकerruped by fatal संकेत.
	 */
	BTRFS_RESERVE_FLUSH_DATA,
	BTRFS_RESERVE_FLUSH_FREE_SPACE_INODE,
	BTRFS_RESERVE_FLUSH_ALL,

	/*
	 * Pretty much the same as FLUSH_ALL, but can also steal space from
	 * global rsv.
	 *
	 * Can be पूर्णांकerruped by fatal संकेत.
	 */
	BTRFS_RESERVE_FLUSH_ALL_STEAL,
पूर्ण;

क्रमागत btrfs_flush_state अणु
	FLUSH_DELAYED_ITEMS_NR	=	1,
	FLUSH_DELAYED_ITEMS	=	2,
	FLUSH_DELAYED_REFS_NR	=	3,
	FLUSH_DELAYED_REFS	=	4,
	FLUSH_DELALLOC		=	5,
	FLUSH_DELALLOC_WAIT	=	6,
	ALLOC_CHUNK		=	7,
	ALLOC_CHUNK_FORCE	=	8,
	RUN_DELAYED_IPUTS	=	9,
	COMMIT_TRANS		=	10,
	FORCE_COMMIT_TRANS	=	11,
पूर्ण;

पूर्णांक btrfs_subvolume_reserve_metadata(काष्ठा btrfs_root *root,
				     काष्ठा btrfs_block_rsv *rsv,
				     पूर्णांक nitems, bool use_global_rsv);
व्योम btrfs_subvolume_release_metadata(काष्ठा btrfs_root *root,
				      काष्ठा btrfs_block_rsv *rsv);
व्योम btrfs_delalloc_release_extents(काष्ठा btrfs_inode *inode, u64 num_bytes);

पूर्णांक btrfs_delalloc_reserve_metadata(काष्ठा btrfs_inode *inode, u64 num_bytes);
u64 btrfs_account_ro_block_groups_मुक्त_space(काष्ठा btrfs_space_info *sinfo);
पूर्णांक btrfs_error_unpin_extent_range(काष्ठा btrfs_fs_info *fs_info,
				   u64 start, u64 end);
पूर्णांक btrfs_discard_extent(काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			 u64 num_bytes, u64 *actual_bytes);
पूर्णांक btrfs_trim_fs(काष्ठा btrfs_fs_info *fs_info, काष्ठा fstrim_range *range);

पूर्णांक btrfs_init_space_info(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_delayed_refs_qgroup_accounting(काष्ठा btrfs_trans_handle *trans,
					 काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_start_ग_लिखो_no_snapshotting(काष्ठा btrfs_root *root);
व्योम btrfs_end_ग_लिखो_no_snapshotting(काष्ठा btrfs_root *root);
व्योम btrfs_रुको_क्रम_snapshot_creation(काष्ठा btrfs_root *root);

/* ctree.c */
पूर्णांक btrfs_bin_search(काष्ठा extent_buffer *eb, स्थिर काष्ठा btrfs_key *key,
		     पूर्णांक *slot);
पूर्णांक __pure btrfs_comp_cpu_keys(स्थिर काष्ठा btrfs_key *k1, स्थिर काष्ठा btrfs_key *k2);
पूर्णांक btrfs_previous_item(काष्ठा btrfs_root *root,
			काष्ठा btrfs_path *path, u64 min_objectid,
			पूर्णांक type);
पूर्णांक btrfs_previous_extent_item(काष्ठा btrfs_root *root,
			काष्ठा btrfs_path *path, u64 min_objectid);
व्योम btrfs_set_item_key_safe(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा btrfs_path *path,
			     स्थिर काष्ठा btrfs_key *new_key);
काष्ठा extent_buffer *btrfs_root_node(काष्ठा btrfs_root *root);
पूर्णांक btrfs_find_next_key(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			काष्ठा btrfs_key *key, पूर्णांक lowest_level,
			u64 min_trans);
पूर्णांक btrfs_search_क्रमward(काष्ठा btrfs_root *root, काष्ठा btrfs_key *min_key,
			 काष्ठा btrfs_path *path,
			 u64 min_trans);
काष्ठा extent_buffer *btrfs_पढ़ो_node_slot(काष्ठा extent_buffer *parent,
					   पूर्णांक slot);

पूर्णांक btrfs_cow_block(काष्ठा btrfs_trans_handle *trans,
		    काष्ठा btrfs_root *root, काष्ठा extent_buffer *buf,
		    काष्ठा extent_buffer *parent, पूर्णांक parent_slot,
		    काष्ठा extent_buffer **cow_ret,
		    क्रमागत btrfs_lock_nesting nest);
पूर्णांक btrfs_copy_root(काष्ठा btrfs_trans_handle *trans,
		      काष्ठा btrfs_root *root,
		      काष्ठा extent_buffer *buf,
		      काष्ठा extent_buffer **cow_ret, u64 new_root_objectid);
पूर्णांक btrfs_block_can_be_shared(काष्ठा btrfs_root *root,
			      काष्ठा extent_buffer *buf);
व्योम btrfs_extend_item(काष्ठा btrfs_path *path, u32 data_size);
व्योम btrfs_truncate_item(काष्ठा btrfs_path *path, u32 new_size, पूर्णांक from_end);
पूर्णांक btrfs_split_item(काष्ठा btrfs_trans_handle *trans,
		     काष्ठा btrfs_root *root,
		     काष्ठा btrfs_path *path,
		     स्थिर काष्ठा btrfs_key *new_key,
		     अचिन्हित दीर्घ split_offset);
पूर्णांक btrfs_duplicate_item(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_root *root,
			 काष्ठा btrfs_path *path,
			 स्थिर काष्ठा btrfs_key *new_key);
पूर्णांक btrfs_find_item(काष्ठा btrfs_root *fs_root, काष्ठा btrfs_path *path,
		u64 inum, u64 ioff, u8 key_type, काष्ठा btrfs_key *found_key);
पूर्णांक btrfs_search_slot(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		      स्थिर काष्ठा btrfs_key *key, काष्ठा btrfs_path *p,
		      पूर्णांक ins_len, पूर्णांक cow);
पूर्णांक btrfs_search_old_slot(काष्ठा btrfs_root *root, स्थिर काष्ठा btrfs_key *key,
			  काष्ठा btrfs_path *p, u64 समय_seq);
पूर्णांक btrfs_search_slot_क्रम_पढ़ो(काष्ठा btrfs_root *root,
			       स्थिर काष्ठा btrfs_key *key,
			       काष्ठा btrfs_path *p, पूर्णांक find_higher,
			       पूर्णांक वापस_any);
पूर्णांक btrfs_पुनः_स्मृति_node(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_root *root, काष्ठा extent_buffer *parent,
		       पूर्णांक start_slot, u64 *last_ret,
		       काष्ठा btrfs_key *progress);
व्योम btrfs_release_path(काष्ठा btrfs_path *p);
काष्ठा btrfs_path *btrfs_alloc_path(व्योम);
व्योम btrfs_मुक्त_path(काष्ठा btrfs_path *p);

पूर्णांक btrfs_del_items(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		   काष्ठा btrfs_path *path, पूर्णांक slot, पूर्णांक nr);
अटल अंतरभूत पूर्णांक btrfs_del_item(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_root *root,
				 काष्ठा btrfs_path *path)
अणु
	वापस btrfs_del_items(trans, root, path, path->slots[0], 1);
पूर्ण

व्योम setup_items_क्रम_insert(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			    स्थिर काष्ठा btrfs_key *cpu_key, u32 *data_size,
			    पूर्णांक nr);
पूर्णांक btrfs_insert_item(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		      स्थिर काष्ठा btrfs_key *key, व्योम *data, u32 data_size);
पूर्णांक btrfs_insert_empty_items(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root,
			     काष्ठा btrfs_path *path,
			     स्थिर काष्ठा btrfs_key *cpu_key, u32 *data_size,
			     पूर्णांक nr);

अटल अंतरभूत पूर्णांक btrfs_insert_empty_item(काष्ठा btrfs_trans_handle *trans,
					  काष्ठा btrfs_root *root,
					  काष्ठा btrfs_path *path,
					  स्थिर काष्ठा btrfs_key *key,
					  u32 data_size)
अणु
	वापस btrfs_insert_empty_items(trans, root, path, key, &data_size, 1);
पूर्ण

पूर्णांक btrfs_next_leaf(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path);
पूर्णांक btrfs_prev_leaf(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path);
पूर्णांक btrfs_next_old_leaf(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			u64 समय_seq);
अटल अंतरभूत पूर्णांक btrfs_next_old_item(काष्ठा btrfs_root *root,
				      काष्ठा btrfs_path *p, u64 समय_seq)
अणु
	++p->slots[0];
	अगर (p->slots[0] >= btrfs_header_nritems(p->nodes[0]))
		वापस btrfs_next_old_leaf(root, p, समय_seq);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक btrfs_next_item(काष्ठा btrfs_root *root, काष्ठा btrfs_path *p)
अणु
	वापस btrfs_next_old_item(root, p, 0);
पूर्ण
पूर्णांक btrfs_leaf_मुक्त_space(काष्ठा extent_buffer *leaf);
पूर्णांक __must_check btrfs_drop_snapshot(काष्ठा btrfs_root *root, पूर्णांक update_ref,
				     पूर्णांक क्रम_reloc);
पूर्णांक btrfs_drop_subtree(काष्ठा btrfs_trans_handle *trans,
			काष्ठा btrfs_root *root,
			काष्ठा extent_buffer *node,
			काष्ठा extent_buffer *parent);
अटल अंतरभूत पूर्णांक btrfs_fs_closing(काष्ठा btrfs_fs_info *fs_info)
अणु
	/*
	 * Do it this way so we only ever करो one test_bit in the normal हाल.
	 */
	अगर (test_bit(BTRFS_FS_CLOSING_START, &fs_info->flags)) अणु
		अगर (test_bit(BTRFS_FS_CLOSING_DONE, &fs_info->flags))
			वापस 2;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * If we remount the fs to be R/O or umount the fs, the cleaner needn't करो
 * anything except sleeping. This function is used to check the status of
 * the fs.
 * We check क्रम BTRFS_FS_STATE_RO to aव्योम races with a concurrent remount,
 * since setting and checking क्रम SB_RDONLY in the superblock's flags is not
 * atomic.
 */
अटल अंतरभूत पूर्णांक btrfs_need_cleaner_sleep(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस test_bit(BTRFS_FS_STATE_RO, &fs_info->fs_state) ||
		btrfs_fs_closing(fs_info);
पूर्ण

अटल अंतरभूत व्योम btrfs_set_sb_rकरोnly(काष्ठा super_block *sb)
अणु
	sb->s_flags |= SB_RDONLY;
	set_bit(BTRFS_FS_STATE_RO, &btrfs_sb(sb)->fs_state);
पूर्ण

अटल अंतरभूत व्योम btrfs_clear_sb_rकरोnly(काष्ठा super_block *sb)
अणु
	sb->s_flags &= ~SB_RDONLY;
	clear_bit(BTRFS_FS_STATE_RO, &btrfs_sb(sb)->fs_state);
पूर्ण

/* root-item.c */
पूर्णांक btrfs_add_root_ref(काष्ठा btrfs_trans_handle *trans, u64 root_id,
		       u64 ref_id, u64 dirid, u64 sequence, स्थिर अक्षर *name,
		       पूर्णांक name_len);
पूर्णांक btrfs_del_root_ref(काष्ठा btrfs_trans_handle *trans, u64 root_id,
		       u64 ref_id, u64 dirid, u64 *sequence, स्थिर अक्षर *name,
		       पूर्णांक name_len);
पूर्णांक btrfs_del_root(काष्ठा btrfs_trans_handle *trans,
		   स्थिर काष्ठा btrfs_key *key);
पूर्णांक btrfs_insert_root(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		      स्थिर काष्ठा btrfs_key *key,
		      काष्ठा btrfs_root_item *item);
पूर्णांक __must_check btrfs_update_root(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_root *root,
				   काष्ठा btrfs_key *key,
				   काष्ठा btrfs_root_item *item);
पूर्णांक btrfs_find_root(काष्ठा btrfs_root *root, स्थिर काष्ठा btrfs_key *search_key,
		    काष्ठा btrfs_path *path, काष्ठा btrfs_root_item *root_item,
		    काष्ठा btrfs_key *root_key);
पूर्णांक btrfs_find_orphan_roots(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_set_root_node(काष्ठा btrfs_root_item *item,
			 काष्ठा extent_buffer *node);
व्योम btrfs_check_and_init_root_item(काष्ठा btrfs_root_item *item);
व्योम btrfs_update_root_बार(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root);

/* uuid-tree.c */
पूर्णांक btrfs_uuid_tree_add(काष्ठा btrfs_trans_handle *trans, u8 *uuid, u8 type,
			u64 subid);
पूर्णांक btrfs_uuid_tree_हटाओ(काष्ठा btrfs_trans_handle *trans, u8 *uuid, u8 type,
			u64 subid);
पूर्णांक btrfs_uuid_tree_iterate(काष्ठा btrfs_fs_info *fs_info);

/* dir-item.c */
पूर्णांक btrfs_check_dir_item_collision(काष्ठा btrfs_root *root, u64 dir,
			  स्थिर अक्षर *name, पूर्णांक name_len);
पूर्णांक btrfs_insert_dir_item(काष्ठा btrfs_trans_handle *trans, स्थिर अक्षर *name,
			  पूर्णांक name_len, काष्ठा btrfs_inode *dir,
			  काष्ठा btrfs_key *location, u8 type, u64 index);
काष्ठा btrfs_dir_item *btrfs_lookup_dir_item(काष्ठा btrfs_trans_handle *trans,
					     काष्ठा btrfs_root *root,
					     काष्ठा btrfs_path *path, u64 dir,
					     स्थिर अक्षर *name, पूर्णांक name_len,
					     पूर्णांक mod);
काष्ठा btrfs_dir_item *
btrfs_lookup_dir_index_item(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_root *root,
			    काष्ठा btrfs_path *path, u64 dir,
			    u64 objectid, स्थिर अक्षर *name, पूर्णांक name_len,
			    पूर्णांक mod);
काष्ठा btrfs_dir_item *
btrfs_search_dir_index_item(काष्ठा btrfs_root *root,
			    काष्ठा btrfs_path *path, u64 dirid,
			    स्थिर अक्षर *name, पूर्णांक name_len);
पूर्णांक btrfs_delete_one_dir_name(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_root *root,
			      काष्ठा btrfs_path *path,
			      काष्ठा btrfs_dir_item *di);
पूर्णांक btrfs_insert_xattr_item(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_root *root,
			    काष्ठा btrfs_path *path, u64 objectid,
			    स्थिर अक्षर *name, u16 name_len,
			    स्थिर व्योम *data, u16 data_len);
काष्ठा btrfs_dir_item *btrfs_lookup_xattr(काष्ठा btrfs_trans_handle *trans,
					  काष्ठा btrfs_root *root,
					  काष्ठा btrfs_path *path, u64 dir,
					  स्थिर अक्षर *name, u16 name_len,
					  पूर्णांक mod);
काष्ठा btrfs_dir_item *btrfs_match_dir_item_name(काष्ठा btrfs_fs_info *fs_info,
						 काष्ठा btrfs_path *path,
						 स्थिर अक्षर *name,
						 पूर्णांक name_len);

/* orphan.c */
पूर्णांक btrfs_insert_orphan_item(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root, u64 offset);
पूर्णांक btrfs_del_orphan_item(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *root, u64 offset);
पूर्णांक btrfs_find_orphan_item(काष्ठा btrfs_root *root, u64 offset);

/* inode-item.c */
पूर्णांक btrfs_insert_inode_ref(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   स्थिर अक्षर *name, पूर्णांक name_len,
			   u64 inode_objectid, u64 ref_objectid, u64 index);
पूर्णांक btrfs_del_inode_ref(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   स्थिर अक्षर *name, पूर्णांक name_len,
			   u64 inode_objectid, u64 ref_objectid, u64 *index);
पूर्णांक btrfs_insert_empty_inode(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root,
			     काष्ठा btrfs_path *path, u64 objectid);
पूर्णांक btrfs_lookup_inode(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root
		       *root, काष्ठा btrfs_path *path,
		       काष्ठा btrfs_key *location, पूर्णांक mod);

काष्ठा btrfs_inode_extref *
btrfs_lookup_inode_extref(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *root,
			  काष्ठा btrfs_path *path,
			  स्थिर अक्षर *name, पूर्णांक name_len,
			  u64 inode_objectid, u64 ref_objectid, पूर्णांक ins_len,
			  पूर्णांक cow);

काष्ठा btrfs_inode_ref *btrfs_find_name_in_backref(काष्ठा extent_buffer *leaf,
						   पूर्णांक slot, स्थिर अक्षर *name,
						   पूर्णांक name_len);
काष्ठा btrfs_inode_extref *btrfs_find_name_in_ext_backref(
		काष्ठा extent_buffer *leaf, पूर्णांक slot, u64 ref_objectid,
		स्थिर अक्षर *name, पूर्णांक name_len);
/* file-item.c */
काष्ठा btrfs_dio_निजी;
पूर्णांक btrfs_del_csums(काष्ठा btrfs_trans_handle *trans,
		    काष्ठा btrfs_root *root, u64 bytenr, u64 len);
blk_status_t btrfs_lookup_bio_sums(काष्ठा inode *inode, काष्ठा bio *bio, u8 *dst);
पूर्णांक btrfs_insert_file_extent(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root,
			     u64 objectid, u64 pos,
			     u64 disk_offset, u64 disk_num_bytes,
			     u64 num_bytes, u64 offset, u64 ram_bytes,
			     u8 compression, u8 encryption, u16 other_encoding);
पूर्णांक btrfs_lookup_file_extent(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root,
			     काष्ठा btrfs_path *path, u64 objectid,
			     u64 bytenr, पूर्णांक mod);
पूर्णांक btrfs_csum_file_blocks(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   काष्ठा btrfs_ordered_sum *sums);
blk_status_t btrfs_csum_one_bio(काष्ठा btrfs_inode *inode, काष्ठा bio *bio,
				u64 file_start, पूर्णांक contig);
पूर्णांक btrfs_lookup_csums_range(काष्ठा btrfs_root *root, u64 start, u64 end,
			     काष्ठा list_head *list, पूर्णांक search_commit);
व्योम btrfs_extent_item_to_extent_map(काष्ठा btrfs_inode *inode,
				     स्थिर काष्ठा btrfs_path *path,
				     काष्ठा btrfs_file_extent_item *fi,
				     स्थिर bool new_अंतरभूत,
				     काष्ठा extent_map *em);
पूर्णांक btrfs_inode_clear_file_extent_range(काष्ठा btrfs_inode *inode, u64 start,
					u64 len);
पूर्णांक btrfs_inode_set_file_extent_range(काष्ठा btrfs_inode *inode, u64 start,
				      u64 len);
व्योम btrfs_inode_safe_disk_i_size_ग_लिखो(काष्ठा btrfs_inode *inode, u64 new_i_size);
u64 btrfs_file_extent_end(स्थिर काष्ठा btrfs_path *path);

/* inode.c */
blk_status_t btrfs_submit_data_bio(काष्ठा inode *inode, काष्ठा bio *bio,
				   पूर्णांक mirror_num, अचिन्हित दीर्घ bio_flags);
पूर्णांक btrfs_verअगरy_data_csum(काष्ठा btrfs_io_bio *io_bio, u32 bio_offset,
			   काष्ठा page *page, u64 start, u64 end);
काष्ठा extent_map *btrfs_get_extent_fiemap(काष्ठा btrfs_inode *inode,
					   u64 start, u64 len);
noअंतरभूत पूर्णांक can_nocow_extent(काष्ठा inode *inode, u64 offset, u64 *len,
			      u64 *orig_start, u64 *orig_block_len,
			      u64 *ram_bytes, bool strict);

व्योम __btrfs_del_delalloc_inode(काष्ठा btrfs_root *root,
				काष्ठा btrfs_inode *inode);
काष्ठा inode *btrfs_lookup_dentry(काष्ठा inode *dir, काष्ठा dentry *dentry);
पूर्णांक btrfs_set_inode_index(काष्ठा btrfs_inode *dir, u64 *index);
पूर्णांक btrfs_unlink_inode(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_root *root,
		       काष्ठा btrfs_inode *dir, काष्ठा btrfs_inode *inode,
		       स्थिर अक्षर *name, पूर्णांक name_len);
पूर्णांक btrfs_add_link(काष्ठा btrfs_trans_handle *trans,
		   काष्ठा btrfs_inode *parent_inode, काष्ठा btrfs_inode *inode,
		   स्थिर अक्षर *name, पूर्णांक name_len, पूर्णांक add_backref, u64 index);
पूर्णांक btrfs_delete_subvolume(काष्ठा inode *dir, काष्ठा dentry *dentry);
पूर्णांक btrfs_truncate_block(काष्ठा btrfs_inode *inode, loff_t from, loff_t len,
			 पूर्णांक front);
पूर्णांक btrfs_truncate_inode_items(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       काष्ठा btrfs_inode *inode, u64 new_size,
			       u32 min_type);

पूर्णांक btrfs_start_delalloc_snapshot(काष्ठा btrfs_root *root, bool in_reclaim_context);
पूर्णांक btrfs_start_delalloc_roots(काष्ठा btrfs_fs_info *fs_info, दीर्घ nr,
			       bool in_reclaim_context);
पूर्णांक btrfs_set_extent_delalloc(काष्ठा btrfs_inode *inode, u64 start, u64 end,
			      अचिन्हित पूर्णांक extra_bits,
			      काष्ठा extent_state **cached_state);
पूर्णांक btrfs_create_subvol_root(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *new_root,
			     काष्ठा btrfs_root *parent_root);
 व्योम btrfs_set_delalloc_extent(काष्ठा inode *inode, काष्ठा extent_state *state,
			       अचिन्हित *bits);
व्योम btrfs_clear_delalloc_extent(काष्ठा inode *inode,
				 काष्ठा extent_state *state, अचिन्हित *bits);
व्योम btrfs_merge_delalloc_extent(काष्ठा inode *inode, काष्ठा extent_state *new,
				 काष्ठा extent_state *other);
व्योम btrfs_split_delalloc_extent(काष्ठा inode *inode,
				 काष्ठा extent_state *orig, u64 split);
पूर्णांक btrfs_bio_fits_in_stripe(काष्ठा page *page, माप_प्रकार size, काष्ठा bio *bio,
			     अचिन्हित दीर्घ bio_flags);
bool btrfs_bio_fits_in_ordered_extent(काष्ठा page *page, काष्ठा bio *bio,
				      अचिन्हित पूर्णांक size);
व्योम btrfs_set_range_ग_लिखोback(काष्ठा extent_io_tree *tree, u64 start, u64 end);
vm_fault_t btrfs_page_mkग_लिखो(काष्ठा vm_fault *vmf);
पूर्णांक btrfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page);
व्योम btrfs_evict_inode(काष्ठा inode *inode);
पूर्णांक btrfs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc);
काष्ठा inode *btrfs_alloc_inode(काष्ठा super_block *sb);
व्योम btrfs_destroy_inode(काष्ठा inode *inode);
व्योम btrfs_मुक्त_inode(काष्ठा inode *inode);
पूर्णांक btrfs_drop_inode(काष्ठा inode *inode);
पूर्णांक __init btrfs_init_cachep(व्योम);
व्योम __cold btrfs_destroy_cachep(व्योम);
काष्ठा inode *btrfs_iget_path(काष्ठा super_block *s, u64 ino,
			      काष्ठा btrfs_root *root, काष्ठा btrfs_path *path);
काष्ठा inode *btrfs_iget(काष्ठा super_block *s, u64 ino, काष्ठा btrfs_root *root);
काष्ठा extent_map *btrfs_get_extent(काष्ठा btrfs_inode *inode,
				    काष्ठा page *page, माप_प्रकार pg_offset,
				    u64 start, u64 end);
पूर्णांक btrfs_update_inode(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_root *root, काष्ठा btrfs_inode *inode);
पूर्णांक btrfs_update_inode_fallback(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_root *root, काष्ठा btrfs_inode *inode);
पूर्णांक btrfs_orphan_add(काष्ठा btrfs_trans_handle *trans,
		काष्ठा btrfs_inode *inode);
पूर्णांक btrfs_orphan_cleanup(काष्ठा btrfs_root *root);
पूर्णांक btrfs_cont_expand(काष्ठा btrfs_inode *inode, loff_t oldsize, loff_t size);
व्योम btrfs_add_delayed_iput(काष्ठा inode *inode);
व्योम btrfs_run_delayed_iमाला_दो(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_रुको_on_delayed_iमाला_दो(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_pपुनः_स्मृति_file_range(काष्ठा inode *inode, पूर्णांक mode,
			      u64 start, u64 num_bytes, u64 min_size,
			      loff_t actual_len, u64 *alloc_hपूर्णांक);
पूर्णांक btrfs_pपुनः_स्मृति_file_range_trans(काष्ठा inode *inode,
				    काष्ठा btrfs_trans_handle *trans, पूर्णांक mode,
				    u64 start, u64 num_bytes, u64 min_size,
				    loff_t actual_len, u64 *alloc_hपूर्णांक);
पूर्णांक btrfs_run_delalloc_range(काष्ठा btrfs_inode *inode, काष्ठा page *locked_page,
		u64 start, u64 end, पूर्णांक *page_started, अचिन्हित दीर्घ *nr_written,
		काष्ठा ग_लिखोback_control *wbc);
पूर्णांक btrfs_ग_लिखोpage_cow_fixup(काष्ठा page *page, u64 start, u64 end);
व्योम btrfs_ग_लिखोpage_endio_finish_ordered(काष्ठा page *page, u64 start,
					  u64 end, पूर्णांक uptodate);
बाह्य स्थिर काष्ठा dentry_operations btrfs_dentry_operations;
बाह्य स्थिर काष्ठा iomap_ops btrfs_dio_iomap_ops;
बाह्य स्थिर काष्ठा iomap_dio_ops btrfs_dio_ops;

/* Inode locking type flags, by शेष the exclusive lock is taken */
#घोषणा BTRFS_ILOCK_SHARED	(1U << 0)
#घोषणा BTRFS_ILOCK_TRY 	(1U << 1)
#घोषणा BTRFS_ILOCK_MMAP	(1U << 2)

पूर्णांक btrfs_inode_lock(काष्ठा inode *inode, अचिन्हित पूर्णांक ilock_flags);
व्योम btrfs_inode_unlock(काष्ठा inode *inode, अचिन्हित पूर्णांक ilock_flags);
व्योम btrfs_update_inode_bytes(काष्ठा btrfs_inode *inode,
			      स्थिर u64 add_bytes,
			      स्थिर u64 del_bytes);

/* ioctl.c */
दीर्घ btrfs_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ btrfs_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक btrfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्णांक btrfs_fileattr_set(काष्ठा user_namespace *mnt_userns,
		       काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्णांक btrfs_ioctl_get_supported_features(व्योम __user *arg);
व्योम btrfs_sync_inode_flags_to_i_flags(काष्ठा inode *inode);
पूर्णांक __pure btrfs_is_empty_uuid(u8 *uuid);
पूर्णांक btrfs_defrag_file(काष्ठा inode *inode, काष्ठा file *file,
		      काष्ठा btrfs_ioctl_defrag_range_args *range,
		      u64 newer_than, अचिन्हित दीर्घ max_pages);
व्योम btrfs_get_block_group_info(काष्ठा list_head *groups_list,
				काष्ठा btrfs_ioctl_space_info *space);
व्योम btrfs_update_ioctl_balance_args(काष्ठा btrfs_fs_info *fs_info,
			       काष्ठा btrfs_ioctl_balance_args *bargs);
bool btrfs_exclop_start(काष्ठा btrfs_fs_info *fs_info,
			क्रमागत btrfs_exclusive_operation type);
व्योम btrfs_exclop_finish(काष्ठा btrfs_fs_info *fs_info);

/* file.c */
पूर्णांक __init btrfs_स्वतः_defrag_init(व्योम);
व्योम __cold btrfs_स्वतः_defrag_निकास(व्योम);
पूर्णांक btrfs_add_inode_defrag(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_inode *inode);
पूर्णांक btrfs_run_defrag_inodes(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_cleanup_defrag_inodes(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_sync_file(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync);
व्योम btrfs_drop_extent_cache(काष्ठा btrfs_inode *inode, u64 start, u64 end,
			     पूर्णांक skip_pinned);
बाह्य स्थिर काष्ठा file_operations btrfs_file_operations;
पूर्णांक btrfs_drop_extents(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_root *root, काष्ठा btrfs_inode *inode,
		       काष्ठा btrfs_drop_extents_args *args);
पूर्णांक btrfs_replace_file_extents(काष्ठा btrfs_inode *inode,
			   काष्ठा btrfs_path *path, स्थिर u64 start,
			   स्थिर u64 end,
			   काष्ठा btrfs_replace_extent_info *extent_info,
			   काष्ठा btrfs_trans_handle **trans_out);
पूर्णांक btrfs_mark_extent_written(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_inode *inode, u64 start, u64 end);
पूर्णांक btrfs_release_file(काष्ठा inode *inode, काष्ठा file *file);
पूर्णांक btrfs_dirty_pages(काष्ठा btrfs_inode *inode, काष्ठा page **pages,
		      माप_प्रकार num_pages, loff_t pos, माप_प्रकार ग_लिखो_bytes,
		      काष्ठा extent_state **cached, bool noreserve);
पूर्णांक btrfs_fdataग_लिखो_range(काष्ठा inode *inode, loff_t start, loff_t end);
पूर्णांक btrfs_check_nocow_lock(काष्ठा btrfs_inode *inode, loff_t pos,
			   माप_प्रकार *ग_लिखो_bytes);
व्योम btrfs_check_nocow_unlock(काष्ठा btrfs_inode *inode);

/* tree-defrag.c */
पूर्णांक btrfs_defrag_leaves(काष्ठा btrfs_trans_handle *trans,
			काष्ठा btrfs_root *root);

/* super.c */
पूर्णांक btrfs_parse_options(काष्ठा btrfs_fs_info *info, अक्षर *options,
			अचिन्हित दीर्घ new_flags);
पूर्णांक btrfs_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको);
अक्षर *btrfs_get_subvol_name_from_objectid(काष्ठा btrfs_fs_info *fs_info,
					  u64 subvol_objectid);

अटल अंतरभूत __म_लिखो(2, 3) __cold
व्योम btrfs_no_prपूर्णांकk(स्थिर काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *fmt, ...)
अणु
पूर्ण

#अगर_घोषित CONFIG_PRINTK
__म_लिखो(2, 3)
__cold
व्योम btrfs_prपूर्णांकk(स्थिर काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *fmt, ...);
#अन्यथा
#घोषणा btrfs_prपूर्णांकk(fs_info, fmt, args...) \
	btrfs_no_prपूर्णांकk(fs_info, fmt, ##args)
#पूर्ण_अगर

#घोषणा btrfs_emerg(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk(fs_info, KERN_EMERG fmt, ##args)
#घोषणा btrfs_alert(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk(fs_info, KERN_ALERT fmt, ##args)
#घोषणा btrfs_crit(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk(fs_info, KERN_CRIT fmt, ##args)
#घोषणा btrfs_err(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk(fs_info, KERN_ERR fmt, ##args)
#घोषणा btrfs_warn(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk(fs_info, KERN_WARNING fmt, ##args)
#घोषणा btrfs_notice(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk(fs_info, KERN_NOTICE fmt, ##args)
#घोषणा btrfs_info(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk(fs_info, KERN_INFO fmt, ##args)

/*
 * Wrappers that use prपूर्णांकk_in_rcu
 */
#घोषणा btrfs_emerg_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_in_rcu(fs_info, KERN_EMERG fmt, ##args)
#घोषणा btrfs_alert_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_in_rcu(fs_info, KERN_ALERT fmt, ##args)
#घोषणा btrfs_crit_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_in_rcu(fs_info, KERN_CRIT fmt, ##args)
#घोषणा btrfs_err_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_in_rcu(fs_info, KERN_ERR fmt, ##args)
#घोषणा btrfs_warn_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_in_rcu(fs_info, KERN_WARNING fmt, ##args)
#घोषणा btrfs_notice_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_in_rcu(fs_info, KERN_NOTICE fmt, ##args)
#घोषणा btrfs_info_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_in_rcu(fs_info, KERN_INFO fmt, ##args)

/*
 * Wrappers that use a ratelimited prपूर्णांकk_in_rcu
 */
#घोषणा btrfs_emerg_rl_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_rl_in_rcu(fs_info, KERN_EMERG fmt, ##args)
#घोषणा btrfs_alert_rl_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_rl_in_rcu(fs_info, KERN_ALERT fmt, ##args)
#घोषणा btrfs_crit_rl_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_rl_in_rcu(fs_info, KERN_CRIT fmt, ##args)
#घोषणा btrfs_err_rl_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_rl_in_rcu(fs_info, KERN_ERR fmt, ##args)
#घोषणा btrfs_warn_rl_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_rl_in_rcu(fs_info, KERN_WARNING fmt, ##args)
#घोषणा btrfs_notice_rl_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_rl_in_rcu(fs_info, KERN_NOTICE fmt, ##args)
#घोषणा btrfs_info_rl_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_rl_in_rcu(fs_info, KERN_INFO fmt, ##args)

/*
 * Wrappers that use a ratelimited prपूर्णांकk
 */
#घोषणा btrfs_emerg_rl(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_ratelimited(fs_info, KERN_EMERG fmt, ##args)
#घोषणा btrfs_alert_rl(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_ratelimited(fs_info, KERN_ALERT fmt, ##args)
#घोषणा btrfs_crit_rl(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_ratelimited(fs_info, KERN_CRIT fmt, ##args)
#घोषणा btrfs_err_rl(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_ratelimited(fs_info, KERN_ERR fmt, ##args)
#घोषणा btrfs_warn_rl(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_ratelimited(fs_info, KERN_WARNING fmt, ##args)
#घोषणा btrfs_notice_rl(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_ratelimited(fs_info, KERN_NOTICE fmt, ##args)
#घोषणा btrfs_info_rl(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_ratelimited(fs_info, KERN_INFO fmt, ##args)

#अगर defined(CONFIG_DYNAMIC_DEBUG)
#घोषणा btrfs_debug(fs_info, fmt, args...)				\
	_dynamic_func_call_no_desc(fmt, btrfs_prपूर्णांकk,			\
				   fs_info, KERN_DEBUG fmt, ##args)
#घोषणा btrfs_debug_in_rcu(fs_info, fmt, args...)			\
	_dynamic_func_call_no_desc(fmt, btrfs_prपूर्णांकk_in_rcu,		\
				   fs_info, KERN_DEBUG fmt, ##args)
#घोषणा btrfs_debug_rl_in_rcu(fs_info, fmt, args...)			\
	_dynamic_func_call_no_desc(fmt, btrfs_prपूर्णांकk_rl_in_rcu,		\
				   fs_info, KERN_DEBUG fmt, ##args)
#घोषणा btrfs_debug_rl(fs_info, fmt, args...)				\
	_dynamic_func_call_no_desc(fmt, btrfs_prपूर्णांकk_ratelimited,	\
				   fs_info, KERN_DEBUG fmt, ##args)
#या_अगर defined(DEBUG)
#घोषणा btrfs_debug(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk(fs_info, KERN_DEBUG fmt, ##args)
#घोषणा btrfs_debug_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_in_rcu(fs_info, KERN_DEBUG fmt, ##args)
#घोषणा btrfs_debug_rl_in_rcu(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_rl_in_rcu(fs_info, KERN_DEBUG fmt, ##args)
#घोषणा btrfs_debug_rl(fs_info, fmt, args...) \
	btrfs_prपूर्णांकk_ratelimited(fs_info, KERN_DEBUG fmt, ##args)
#अन्यथा
#घोषणा btrfs_debug(fs_info, fmt, args...) \
	btrfs_no_prपूर्णांकk(fs_info, KERN_DEBUG fmt, ##args)
#घोषणा btrfs_debug_in_rcu(fs_info, fmt, args...) \
	btrfs_no_prपूर्णांकk_in_rcu(fs_info, KERN_DEBUG fmt, ##args)
#घोषणा btrfs_debug_rl_in_rcu(fs_info, fmt, args...) \
	btrfs_no_prपूर्णांकk_in_rcu(fs_info, KERN_DEBUG fmt, ##args)
#घोषणा btrfs_debug_rl(fs_info, fmt, args...) \
	btrfs_no_prपूर्णांकk(fs_info, KERN_DEBUG fmt, ##args)
#पूर्ण_अगर

#घोषणा btrfs_prपूर्णांकk_in_rcu(fs_info, fmt, args...)	\
करो अणु							\
	rcu_पढ़ो_lock();				\
	btrfs_prपूर्णांकk(fs_info, fmt, ##args);		\
	rcu_पढ़ो_unlock();				\
पूर्ण जबतक (0)

#घोषणा btrfs_no_prपूर्णांकk_in_rcu(fs_info, fmt, args...)	\
करो अणु							\
	rcu_पढ़ो_lock();				\
	btrfs_no_prपूर्णांकk(fs_info, fmt, ##args);		\
	rcu_पढ़ो_unlock();				\
पूर्ण जबतक (0)

#घोषणा btrfs_prपूर्णांकk_ratelimited(fs_info, fmt, args...)		\
करो अणु								\
	अटल DEFINE_RATELIMIT_STATE(_rs,			\
		DEFAULT_RATELIMIT_INTERVAL,			\
		DEFAULT_RATELIMIT_BURST);       		\
	अगर (__ratelimit(&_rs))					\
		btrfs_prपूर्णांकk(fs_info, fmt, ##args);		\
पूर्ण जबतक (0)

#घोषणा btrfs_prपूर्णांकk_rl_in_rcu(fs_info, fmt, args...)		\
करो अणु								\
	rcu_पढ़ो_lock();					\
	btrfs_prपूर्णांकk_ratelimited(fs_info, fmt, ##args);		\
	rcu_पढ़ो_unlock();					\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_BTRFS_ASSERT
__cold __noवापस
अटल अंतरभूत व्योम निश्चितfail(स्थिर अक्षर *expr, स्थिर अक्षर *file, पूर्णांक line)
अणु
	pr_err("assertion failed: %s, in %s:%d\n", expr, file, line);
	BUG();
पूर्ण

#घोषणा ASSERT(expr)						\
	(likely(expr) ? (व्योम)0 : निश्चितfail(#expr, __खाता__, __LINE__))

#अन्यथा
अटल अंतरभूत व्योम निश्चितfail(स्थिर अक्षर *expr, स्थिर अक्षर* file, पूर्णांक line) अणु पूर्ण
#घोषणा ASSERT(expr)	(व्योम)(expr)
#पूर्ण_अगर

#अगर BITS_PER_LONG == 32
#घोषणा BTRFS_32BIT_MAX_खाता_SIZE (((u64)अच_दीर्घ_उच्च + 1) << PAGE_SHIFT)
/*
 * The warning threshold is 5/8th of the MAX_LFS_खाताSIZE that limits the logical
 * addresses of extents.
 *
 * For 4K page size it's about 10T, for 64K it's 160T.
 */
#घोषणा BTRFS_32BIT_EARLY_WARN_THRESHOLD (BTRFS_32BIT_MAX_खाता_SIZE * 5 / 8)
व्योम btrfs_warn_32bit_limit(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_err_32bit_limit(काष्ठा btrfs_fs_info *fs_info);
#पूर्ण_अगर

/*
 * Get the correct offset inside the page of extent buffer.
 *
 * @eb:		target extent buffer
 * @start:	offset inside the extent buffer
 *
 * Will handle both sectorsize == PAGE_SIZE and sectorsize < PAGE_SIZE हालs.
 */
अटल अंतरभूत माप_प्रकार get_eb_offset_in_page(स्थिर काष्ठा extent_buffer *eb,
					   अचिन्हित दीर्घ offset)
अणु
	/*
	 * For sectorsize == PAGE_SIZE हाल, eb->start will always be aligned
	 * to PAGE_SIZE, thus adding it won't cause any dअगरference.
	 *
	 * For sectorsize < PAGE_SIZE, we must only पढ़ो the data that beदीर्घs
	 * to the eb, thus we have to take the eb->start पूर्णांकo consideration.
	 */
	वापस offset_in_page(offset + eb->start);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_eb_page_index(अचिन्हित दीर्घ offset)
अणु
	/*
	 * For sectorsize == PAGE_SIZE हाल, plain >> PAGE_SHIFT is enough.
	 *
	 * For sectorsize < PAGE_SIZE हाल, we only support 64K PAGE_SIZE,
	 * and have ensured that all tree blocks are contained in one page,
	 * thus we always get index == 0.
	 */
	वापस offset >> PAGE_SHIFT;
पूर्ण

/*
 * Use that क्रम functions that are conditionally exported क्रम sanity tests but
 * otherwise अटल
 */
#अगर_अघोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
#घोषणा EXPORT_FOR_TESTS अटल
#अन्यथा
#घोषणा EXPORT_FOR_TESTS
#पूर्ण_अगर

__cold
अटल अंतरभूत व्योम btrfs_prपूर्णांक_v0_err(काष्ठा btrfs_fs_info *fs_info)
अणु
	btrfs_err(fs_info,
"Unsupported V0 extent filesystem detected. Aborting. Please re-create your filesystem with a newer kernel");
पूर्ण

__म_लिखो(5, 6)
__cold
व्योम __btrfs_handle_fs_error(काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *function,
		     अचिन्हित पूर्णांक line, पूर्णांक त्रुटि_सं, स्थिर अक्षर *fmt, ...);

स्थिर अक्षर * __attribute_स्थिर__ btrfs_decode_error(पूर्णांक त्रुटि_सं);

__cold
व्योम __btrfs_पात_transaction(काष्ठा btrfs_trans_handle *trans,
			       स्थिर अक्षर *function,
			       अचिन्हित पूर्णांक line, पूर्णांक त्रुटि_सं);

/*
 * Call btrfs_पात_transaction as early as possible when an error condition is
 * detected, that way the exact line number is reported.
 */
#घोषणा btrfs_पात_transaction(trans, त्रुटि_सं)		\
करो अणु								\
	/* Report first पात since mount */			\
	अगर (!test_and_set_bit(BTRFS_FS_STATE_TRANS_ABORTED,	\
			&((trans)->fs_info->fs_state))) अणु	\
		अगर ((त्रुटि_सं) != -EIO && (त्रुटि_सं) != -EROFS) अणु		\
			WARN(1, KERN_DEBUG				\
			"BTRFS: Transaction aborted (error %d)\n",	\
			(त्रुटि_सं));					\
		पूर्ण अन्यथा अणु						\
			btrfs_debug((trans)->fs_info,			\
				    "Transaction aborted (error %d)", \
				  (त्रुटि_सं));			\
		पूर्ण						\
	पूर्ण							\
	__btrfs_पात_transaction((trans), __func__,		\
				  __LINE__, (त्रुटि_सं));		\
पूर्ण जबतक (0)

#घोषणा btrfs_handle_fs_error(fs_info, त्रुटि_सं, fmt, args...)		\
करो अणु								\
	__btrfs_handle_fs_error((fs_info), __func__, __LINE__,	\
			  (त्रुटि_सं), fmt, ##args);		\
पूर्ण जबतक (0)

__म_लिखो(5, 6)
__cold
व्योम __btrfs_panic(काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *function,
		   अचिन्हित पूर्णांक line, पूर्णांक त्रुटि_सं, स्थिर अक्षर *fmt, ...);
/*
 * If BTRFS_MOUNT_PANIC_ON_FATAL_ERROR is in mount_opt, __btrfs_panic
 * will panic().  Otherwise we BUG() here.
 */
#घोषणा btrfs_panic(fs_info, त्रुटि_सं, fmt, args...)			\
करो अणु									\
	__btrfs_panic(fs_info, __func__, __LINE__, त्रुटि_सं, fmt, ##args);	\
	BUG();								\
पूर्ण जबतक (0)


/* compatibility and incompatibility defines */

#घोषणा btrfs_set_fs_incompat(__fs_info, opt) \
	__btrfs_set_fs_incompat((__fs_info), BTRFS_FEATURE_INCOMPAT_##opt, \
				#opt)

अटल अंतरभूत व्योम __btrfs_set_fs_incompat(काष्ठा btrfs_fs_info *fs_info,
					   u64 flag, स्थिर अक्षर* name)
अणु
	काष्ठा btrfs_super_block *disk_super;
	u64 features;

	disk_super = fs_info->super_copy;
	features = btrfs_super_incompat_flags(disk_super);
	अगर (!(features & flag)) अणु
		spin_lock(&fs_info->super_lock);
		features = btrfs_super_incompat_flags(disk_super);
		अगर (!(features & flag)) अणु
			features |= flag;
			btrfs_set_super_incompat_flags(disk_super, features);
			btrfs_info(fs_info,
				"setting incompat feature flag for %s (0x%llx)",
				name, flag);
		पूर्ण
		spin_unlock(&fs_info->super_lock);
	पूर्ण
पूर्ण

#घोषणा btrfs_clear_fs_incompat(__fs_info, opt) \
	__btrfs_clear_fs_incompat((__fs_info), BTRFS_FEATURE_INCOMPAT_##opt, \
				  #opt)

अटल अंतरभूत व्योम __btrfs_clear_fs_incompat(काष्ठा btrfs_fs_info *fs_info,
					     u64 flag, स्थिर अक्षर* name)
अणु
	काष्ठा btrfs_super_block *disk_super;
	u64 features;

	disk_super = fs_info->super_copy;
	features = btrfs_super_incompat_flags(disk_super);
	अगर (features & flag) अणु
		spin_lock(&fs_info->super_lock);
		features = btrfs_super_incompat_flags(disk_super);
		अगर (features & flag) अणु
			features &= ~flag;
			btrfs_set_super_incompat_flags(disk_super, features);
			btrfs_info(fs_info,
				"clearing incompat feature flag for %s (0x%llx)",
				name, flag);
		पूर्ण
		spin_unlock(&fs_info->super_lock);
	पूर्ण
पूर्ण

#घोषणा btrfs_fs_incompat(fs_info, opt) \
	__btrfs_fs_incompat((fs_info), BTRFS_FEATURE_INCOMPAT_##opt)

अटल अंतरभूत bool __btrfs_fs_incompat(काष्ठा btrfs_fs_info *fs_info, u64 flag)
अणु
	काष्ठा btrfs_super_block *disk_super;
	disk_super = fs_info->super_copy;
	वापस !!(btrfs_super_incompat_flags(disk_super) & flag);
पूर्ण

#घोषणा btrfs_set_fs_compat_ro(__fs_info, opt) \
	__btrfs_set_fs_compat_ro((__fs_info), BTRFS_FEATURE_COMPAT_RO_##opt, \
				 #opt)

अटल अंतरभूत व्योम __btrfs_set_fs_compat_ro(काष्ठा btrfs_fs_info *fs_info,
					    u64 flag, स्थिर अक्षर *name)
अणु
	काष्ठा btrfs_super_block *disk_super;
	u64 features;

	disk_super = fs_info->super_copy;
	features = btrfs_super_compat_ro_flags(disk_super);
	अगर (!(features & flag)) अणु
		spin_lock(&fs_info->super_lock);
		features = btrfs_super_compat_ro_flags(disk_super);
		अगर (!(features & flag)) अणु
			features |= flag;
			btrfs_set_super_compat_ro_flags(disk_super, features);
			btrfs_info(fs_info,
				"setting compat-ro feature flag for %s (0x%llx)",
				name, flag);
		पूर्ण
		spin_unlock(&fs_info->super_lock);
	पूर्ण
पूर्ण

#घोषणा btrfs_clear_fs_compat_ro(__fs_info, opt) \
	__btrfs_clear_fs_compat_ro((__fs_info), BTRFS_FEATURE_COMPAT_RO_##opt, \
				   #opt)

अटल अंतरभूत व्योम __btrfs_clear_fs_compat_ro(काष्ठा btrfs_fs_info *fs_info,
					      u64 flag, स्थिर अक्षर *name)
अणु
	काष्ठा btrfs_super_block *disk_super;
	u64 features;

	disk_super = fs_info->super_copy;
	features = btrfs_super_compat_ro_flags(disk_super);
	अगर (features & flag) अणु
		spin_lock(&fs_info->super_lock);
		features = btrfs_super_compat_ro_flags(disk_super);
		अगर (features & flag) अणु
			features &= ~flag;
			btrfs_set_super_compat_ro_flags(disk_super, features);
			btrfs_info(fs_info,
				"clearing compat-ro feature flag for %s (0x%llx)",
				name, flag);
		पूर्ण
		spin_unlock(&fs_info->super_lock);
	पूर्ण
पूर्ण

#घोषणा btrfs_fs_compat_ro(fs_info, opt) \
	__btrfs_fs_compat_ro((fs_info), BTRFS_FEATURE_COMPAT_RO_##opt)

अटल अंतरभूत पूर्णांक __btrfs_fs_compat_ro(काष्ठा btrfs_fs_info *fs_info, u64 flag)
अणु
	काष्ठा btrfs_super_block *disk_super;
	disk_super = fs_info->super_copy;
	वापस !!(btrfs_super_compat_ro_flags(disk_super) & flag);
पूर्ण

/* acl.c */
#अगर_घोषित CONFIG_BTRFS_FS_POSIX_ACL
काष्ठा posix_acl *btrfs_get_acl(काष्ठा inode *inode, पूर्णांक type);
पूर्णांक btrfs_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		  काष्ठा posix_acl *acl, पूर्णांक type);
पूर्णांक btrfs_init_acl(काष्ठा btrfs_trans_handle *trans,
		   काष्ठा inode *inode, काष्ठा inode *dir);
#अन्यथा
#घोषणा btrfs_get_acl शून्य
#घोषणा btrfs_set_acl शून्य
अटल अंतरभूत पूर्णांक btrfs_init_acl(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* relocation.c */
पूर्णांक btrfs_relocate_block_group(काष्ठा btrfs_fs_info *fs_info, u64 group_start);
पूर्णांक btrfs_init_reloc_root(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *root);
पूर्णांक btrfs_update_reloc_root(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_root *root);
पूर्णांक btrfs_recover_relocation(काष्ठा btrfs_root *root);
पूर्णांक btrfs_reloc_clone_csums(काष्ठा btrfs_inode *inode, u64 file_pos, u64 len);
पूर्णांक btrfs_reloc_cow_block(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *root, काष्ठा extent_buffer *buf,
			  काष्ठा extent_buffer *cow);
व्योम btrfs_reloc_pre_snapshot(काष्ठा btrfs_pending_snapshot *pending,
			      u64 *bytes_to_reserve);
पूर्णांक btrfs_reloc_post_snapshot(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_pending_snapshot *pending);
पूर्णांक btrfs_should_cancel_balance(काष्ठा btrfs_fs_info *fs_info);
काष्ठा btrfs_root *find_reloc_root(काष्ठा btrfs_fs_info *fs_info,
				   u64 bytenr);
पूर्णांक btrfs_should_ignore_reloc_root(काष्ठा btrfs_root *root);

/* scrub.c */
पूर्णांक btrfs_scrub_dev(काष्ठा btrfs_fs_info *fs_info, u64 devid, u64 start,
		    u64 end, काष्ठा btrfs_scrub_progress *progress,
		    पूर्णांक पढ़ोonly, पूर्णांक is_dev_replace);
व्योम btrfs_scrub_छोड़ो(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_scrub_जारी(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_scrub_cancel(काष्ठा btrfs_fs_info *info);
पूर्णांक btrfs_scrub_cancel_dev(काष्ठा btrfs_device *dev);
पूर्णांक btrfs_scrub_progress(काष्ठा btrfs_fs_info *fs_info, u64 devid,
			 काष्ठा btrfs_scrub_progress *progress);
अटल अंतरभूत व्योम btrfs_init_full_stripe_locks_tree(
			काष्ठा btrfs_full_stripe_locks_tree *locks_root)
अणु
	locks_root->root = RB_ROOT;
	mutex_init(&locks_root->lock);
पूर्ण

/* dev-replace.c */
व्योम btrfs_bio_counter_inc_blocked(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_bio_counter_inc_noblocked(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_bio_counter_sub(काष्ठा btrfs_fs_info *fs_info, s64 amount);

अटल अंतरभूत व्योम btrfs_bio_counter_dec(काष्ठा btrfs_fs_info *fs_info)
अणु
	btrfs_bio_counter_sub(fs_info, 1);
पूर्ण

/* पढ़ोa.c */
काष्ठा पढ़ोa_control अणु
	काष्ठा btrfs_fs_info	*fs_info;		/* tree to prefetch */
	काष्ठा btrfs_key	key_start;
	काष्ठा btrfs_key	key_end;	/* exclusive */
	atomic_t		elems;
	काष्ठा kref		refcnt;
	रुको_queue_head_t	रुको;
पूर्ण;
काष्ठा पढ़ोa_control *btrfs_पढ़ोa_add(काष्ठा btrfs_root *root,
			      काष्ठा btrfs_key *start, काष्ठा btrfs_key *end);
पूर्णांक btrfs_पढ़ोa_रुको(व्योम *handle);
व्योम btrfs_पढ़ोa_detach(व्योम *handle);
पूर्णांक btree_पढ़ोahead_hook(काष्ठा extent_buffer *eb, पूर्णांक err);
व्योम btrfs_पढ़ोa_हटाओ_dev(काष्ठा btrfs_device *dev);
व्योम btrfs_पढ़ोa_unकरो_हटाओ_dev(काष्ठा btrfs_device *dev);

अटल अंतरभूत पूर्णांक is_fstree(u64 rootid)
अणु
	अगर (rootid == BTRFS_FS_TREE_OBJECTID ||
	    ((s64)rootid >= (s64)BTRFS_FIRST_FREE_OBJECTID &&
	      !btrfs_qgroup_level(rootid)))
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_defrag_cancelled(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस संकेत_pending(current);
पूर्ण

/* Sanity test specअगरic functions */
#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
व्योम btrfs_test_destroy_inode(काष्ठा inode *inode);
अटल अंतरभूत पूर्णांक btrfs_is_testing(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस test_bit(BTRFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक btrfs_is_testing(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool btrfs_is_zoned(स्थिर काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस fs_info->zoned != 0;
पूर्ण

#पूर्ण_अगर
