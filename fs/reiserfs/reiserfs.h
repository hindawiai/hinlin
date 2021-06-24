<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 1996, 1997, 1998 Hans Reiser, see reiserfs/README क्रम
 * licensing and copyright details
 */

#समावेश <linux/reiserfs_fs.h>

#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/bug.h>
#समावेश <linux/workqueue.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/bitops.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/buffer_head.h>

/* the 32 bit compat definitions with पूर्णांक argument */
#घोषणा REISERFS_IOC32_UNPACK		_IOW(0xCD, 1, पूर्णांक)
#घोषणा REISERFS_IOC32_GETVERSION	FS_IOC32_GETVERSION
#घोषणा REISERFS_IOC32_SETVERSION	FS_IOC32_SETVERSION

काष्ठा reiserfs_journal_list;

/* biपंचांगasks क्रम i_flags field in reiserfs-specअगरic part of inode */
प्रकार क्रमागत अणु
	/*
	 * this says what क्रमmat of key करो all items (but stat data) of
	 * an object have.  If this is set, that क्रमmat is 3.6 otherwise - 3.5
	 */
	i_item_key_version_mask = 0x0001,

	/*
	 * If this is unset, object has 3.5 stat data, otherwise,
	 * it has 3.6 stat data with 64bit size, 32bit nlink etc.
	 */
	i_stat_data_version_mask = 0x0002,

	/* file might need tail packing on बंद */
	i_pack_on_बंद_mask = 0x0004,

	/* करोn't pack tail of file */
	i_nopack_mask = 0x0008,

	/*
	 * If either of these are set, "safe link" was created क्रम this
	 * file during truncate or unlink. Safe link is used to aव्योम
	 * leakage of disk space on crash with some files खोलो, but unlinked.
	 */
	i_link_saved_unlink_mask = 0x0010,
	i_link_saved_truncate_mask = 0x0020,

	i_has_xattr_dir = 0x0040,
	i_data_log = 0x0080,
पूर्ण reiserfs_inode_flags;

काष्ठा reiserfs_inode_info अणु
	__u32 i_key[4];		/* key is still 4 32 bit पूर्णांकegers */

	/*
	 * transient inode flags that are never stored on disk. Biपंचांगasks
	 * क्रम this field are defined above.
	 */
	__u32 i_flags;

	/* offset of first byte stored in direct item. */
	__u32 i_first_direct_byte;

	/* copy of persistent inode flags पढ़ो from sd_attrs. */
	__u32 i_attrs;

	/* first unused block of a sequence of unused blocks */
	पूर्णांक i_pपुनः_स्मृति_block;
	पूर्णांक i_pपुनः_स्मृति_count;	/* length of that sequence */

	/* per-transaction list of inodes which  have pपुनः_स्मृतिated blocks */
	काष्ठा list_head i_pपुनः_स्मृति_list;

	/*
	 * new_packing_locality is created; new blocks क्रम the contents
	 * of this directory should be displaced
	 */
	अचिन्हित new_packing_locality:1;

	/*
	 * we use these क्रम fsync or O_SYNC to decide which transaction
	 * needs to be committed in order क्रम this inode to be properly
	 * flushed
	 */
	अचिन्हित पूर्णांक i_trans_id;

	काष्ठा reiserfs_journal_list *i_jl;
	atomic_t खोलोers;
	काष्ठा mutex tailpack;
#अगर_घोषित CONFIG_REISERFS_FS_XATTR
	काष्ठा rw_semaphore i_xattr_sem;
#पूर्ण_अगर
#अगर_घोषित CONFIG_QUOTA
	काष्ठा dquot *i_dquot[MAXQUOTAS];
#पूर्ण_अगर

	काष्ठा inode vfs_inode;
पूर्ण;

प्रकार क्रमागत अणु
	reiserfs_attrs_cleared = 0x00000001,
पूर्ण reiserfs_super_block_flags;

/*
 * काष्ठा reiserfs_super_block accessors/mutators since this is a disk
 * काष्ठाure, it will always be in little endian क्रमmat.
 */
#घोषणा sb_block_count(sbp)         (le32_to_cpu((sbp)->s_v1.s_block_count))
#घोषणा set_sb_block_count(sbp,v)   ((sbp)->s_v1.s_block_count = cpu_to_le32(v))
#घोषणा sb_मुक्त_blocks(sbp)         (le32_to_cpu((sbp)->s_v1.s_मुक्त_blocks))
#घोषणा set_sb_मुक्त_blocks(sbp,v)   ((sbp)->s_v1.s_मुक्त_blocks = cpu_to_le32(v))
#घोषणा sb_root_block(sbp)          (le32_to_cpu((sbp)->s_v1.s_root_block))
#घोषणा set_sb_root_block(sbp,v)    ((sbp)->s_v1.s_root_block = cpu_to_le32(v))

#घोषणा sb_jp_journal_1st_block(sbp)  \
              (le32_to_cpu((sbp)->s_v1.s_journal.jp_journal_1st_block))
#घोषणा set_sb_jp_journal_1st_block(sbp,v) \
              ((sbp)->s_v1.s_journal.jp_journal_1st_block = cpu_to_le32(v))
#घोषणा sb_jp_journal_dev(sbp) \
              (le32_to_cpu((sbp)->s_v1.s_journal.jp_journal_dev))
#घोषणा set_sb_jp_journal_dev(sbp,v) \
              ((sbp)->s_v1.s_journal.jp_journal_dev = cpu_to_le32(v))
#घोषणा sb_jp_journal_size(sbp) \
              (le32_to_cpu((sbp)->s_v1.s_journal.jp_journal_size))
#घोषणा set_sb_jp_journal_size(sbp,v) \
              ((sbp)->s_v1.s_journal.jp_journal_size = cpu_to_le32(v))
#घोषणा sb_jp_journal_trans_max(sbp) \
              (le32_to_cpu((sbp)->s_v1.s_journal.jp_journal_trans_max))
#घोषणा set_sb_jp_journal_trans_max(sbp,v) \
              ((sbp)->s_v1.s_journal.jp_journal_trans_max = cpu_to_le32(v))
#घोषणा sb_jp_journal_magic(sbp) \
              (le32_to_cpu((sbp)->s_v1.s_journal.jp_journal_magic))
#घोषणा set_sb_jp_journal_magic(sbp,v) \
              ((sbp)->s_v1.s_journal.jp_journal_magic = cpu_to_le32(v))
#घोषणा sb_jp_journal_max_batch(sbp) \
              (le32_to_cpu((sbp)->s_v1.s_journal.jp_journal_max_batch))
#घोषणा set_sb_jp_journal_max_batch(sbp,v) \
              ((sbp)->s_v1.s_journal.jp_journal_max_batch = cpu_to_le32(v))
#घोषणा sb_jp_jourmal_max_commit_age(sbp) \
              (le32_to_cpu((sbp)->s_v1.s_journal.jp_journal_max_commit_age))
#घोषणा set_sb_jp_journal_max_commit_age(sbp,v) \
              ((sbp)->s_v1.s_journal.jp_journal_max_commit_age = cpu_to_le32(v))

#घोषणा sb_blocksize(sbp)          (le16_to_cpu((sbp)->s_v1.s_blocksize))
#घोषणा set_sb_blocksize(sbp,v)    ((sbp)->s_v1.s_blocksize = cpu_to_le16(v))
#घोषणा sb_oid_maxsize(sbp)        (le16_to_cpu((sbp)->s_v1.s_oid_maxsize))
#घोषणा set_sb_oid_maxsize(sbp,v)  ((sbp)->s_v1.s_oid_maxsize = cpu_to_le16(v))
#घोषणा sb_oid_cursize(sbp)        (le16_to_cpu((sbp)->s_v1.s_oid_cursize))
#घोषणा set_sb_oid_cursize(sbp,v)  ((sbp)->s_v1.s_oid_cursize = cpu_to_le16(v))
#घोषणा sb_umount_state(sbp)       (le16_to_cpu((sbp)->s_v1.s_umount_state))
#घोषणा set_sb_umount_state(sbp,v) ((sbp)->s_v1.s_umount_state = cpu_to_le16(v))
#घोषणा sb_fs_state(sbp)           (le16_to_cpu((sbp)->s_v1.s_fs_state))
#घोषणा set_sb_fs_state(sbp,v)     ((sbp)->s_v1.s_fs_state = cpu_to_le16(v))
#घोषणा sb_hash_function_code(sbp) \
              (le32_to_cpu((sbp)->s_v1.s_hash_function_code))
#घोषणा set_sb_hash_function_code(sbp,v) \
              ((sbp)->s_v1.s_hash_function_code = cpu_to_le32(v))
#घोषणा sb_tree_height(sbp)        (le16_to_cpu((sbp)->s_v1.s_tree_height))
#घोषणा set_sb_tree_height(sbp,v)  ((sbp)->s_v1.s_tree_height = cpu_to_le16(v))
#घोषणा sb_bmap_nr(sbp)            (le16_to_cpu((sbp)->s_v1.s_bmap_nr))
#घोषणा set_sb_bmap_nr(sbp,v)      ((sbp)->s_v1.s_bmap_nr = cpu_to_le16(v))
#घोषणा sb_version(sbp)            (le16_to_cpu((sbp)->s_v1.s_version))
#घोषणा set_sb_version(sbp,v)      ((sbp)->s_v1.s_version = cpu_to_le16(v))

#घोषणा sb_mnt_count(sbp)	   (le16_to_cpu((sbp)->s_mnt_count))
#घोषणा set_sb_mnt_count(sbp, v)   ((sbp)->s_mnt_count = cpu_to_le16(v))

#घोषणा sb_reserved_क्रम_journal(sbp) \
              (le16_to_cpu((sbp)->s_v1.s_reserved_क्रम_journal))
#घोषणा set_sb_reserved_क्रम_journal(sbp,v) \
              ((sbp)->s_v1.s_reserved_क्रम_journal = cpu_to_le16(v))

/* LOGGING -- */

/*
 * These all पूर्णांकerelate क्रम perक्रमmance.
 *
 * If the journal block count is smaller than n transactions, you lose speed.
 * I करोn't know what n is yet, I'm guessing 8-16.
 *
 * typical transaction size depends on the application, how often fsync is
 * called, and how many metadata blocks you dirty in a 30 second period.
 * The more small files (<16k) you use, the larger your transactions will
 * be.
 *
 * If your journal fills faster than dirty buffers get flushed to disk, it
 * must flush them beक्रमe allowing the journal to wrap, which slows things
 * करोwn.  If you need high speed meta data updates, the journal should be
 * big enough to prevent wrapping beक्रमe dirty meta blocks get to disk.
 *
 * If the batch max is smaller than the transaction max, you'll waste space
 * at the end of the journal because journal_end sets the next transaction
 * to start at 0 अगर the next transaction has any chance of wrapping.
 *
 * The large the batch max age, the better the speed, and the more meta
 * data changes you'll lose after a crash.
 */

/* करोn't mess with these क्रम a जबतक */
/* we have a node size define somewhere in reiserfs_fs.h. -Hans */
#घोषणा JOURNAL_BLOCK_SIZE  4096	/* BUG gotta get rid of this */
#घोषणा JOURNAL_MAX_CNODE   1500	/* max cnodes to allocate. */
#घोषणा JOURNAL_HASH_SIZE 8192

/* number of copies of the biपंचांगaps to have भग्नing.  Must be >= 2 */
#घोषणा JOURNAL_NUM_BITMAPS 5

/*
 * One of these क्रम every block in every transaction
 * Each one is in two hash tables.  First, a hash of the current transaction,
 * and after journal_end, a hash of all the in memory transactions.
 * next and prev are used by the current transaction (journal_hash).
 * hnext and hprev are used by journal_list_hash.  If a block is in more
 * than one transaction, the journal_list_hash links it in multiple बार.
 * This allows flush_journal_list to हटाओ just the cnode beदीर्घing to a
 * given transaction.
 */
काष्ठा reiserfs_journal_cnode अणु
	काष्ठा buffer_head *bh;	/* real buffer head */
	काष्ठा super_block *sb;	/* dev of real buffer head */

	/* block number of real buffer head, == 0 when buffer on disk */
	__u32 blocknr;

	अचिन्हित दीर्घ state;

	/* journal list this cnode lives in */
	काष्ठा reiserfs_journal_list *jlist;

	काष्ठा reiserfs_journal_cnode *next;	/* next in transaction list */
	काष्ठा reiserfs_journal_cnode *prev;	/* prev in transaction list */
	काष्ठा reiserfs_journal_cnode *hprev;	/* prev in hash list */
	काष्ठा reiserfs_journal_cnode *hnext;	/* next in hash list */
पूर्ण;

काष्ठा reiserfs_biपंचांगap_node अणु
	पूर्णांक id;
	अक्षर *data;
	काष्ठा list_head list;
पूर्ण;

काष्ठा reiserfs_list_biपंचांगap अणु
	काष्ठा reiserfs_journal_list *journal_list;
	काष्ठा reiserfs_biपंचांगap_node **biपंचांगaps;
पूर्ण;

/*
 * one of these क्रम each transaction.  The most important part here is the
 * j_realblock.  this list of cnodes is used to hash all the blocks in all
 * the commits, to mark all the real buffer heads dirty once all the commits
 * hit the disk, and to make sure every real block in a transaction is on
 * disk beक्रमe allowing the log area to be overwritten
 */
काष्ठा reiserfs_journal_list अणु
	अचिन्हित दीर्घ j_start;
	अचिन्हित दीर्घ j_state;
	अचिन्हित दीर्घ j_len;
	atomic_t j_nonzerolen;
	atomic_t j_commit_left;

	/* all commits older than this on disk */
	atomic_t j_older_commits_करोne;

	काष्ठा mutex j_commit_mutex;
	अचिन्हित पूर्णांक j_trans_id;
	समय64_t j_बारtamp; /* ग_लिखो-only but useful क्रम crash dump analysis */
	काष्ठा reiserfs_list_biपंचांगap *j_list_biपंचांगap;
	काष्ठा buffer_head *j_commit_bh;	/* commit buffer head */
	काष्ठा reiserfs_journal_cnode *j_realblock;
	काष्ठा reiserfs_journal_cnode *j_मुक्तdlist;	/* list of buffers that were मुक्तd during this trans.  मुक्त each of these on flush */
	/* समय ordered list of all active transactions */
	काष्ठा list_head j_list;

	/*
	 * समय ordered list of all transactions we haven't tried
	 * to flush yet
	 */
	काष्ठा list_head j_working_list;

	/* list of tail conversion tarमाला_लो in need of flush beक्रमe commit */
	काष्ठा list_head j_tail_bh_list;

	/* list of data=ordered buffers in need of flush beक्रमe commit */
	काष्ठा list_head j_bh_list;
	पूर्णांक j_refcount;
पूर्ण;

काष्ठा reiserfs_journal अणु
	काष्ठा buffer_head **j_ap_blocks;	/* journal blocks on disk */
	/* newest journal block */
	काष्ठा reiserfs_journal_cnode *j_last;

	/* oldest journal block.  start here क्रम traverse */
	काष्ठा reiserfs_journal_cnode *j_first;

	काष्ठा block_device *j_dev_bd;
	भ_शेषe_t j_dev_mode;

	/* first block on s_dev of reserved area journal */
	पूर्णांक j_1st_reserved_block;

	अचिन्हित दीर्घ j_state;
	अचिन्हित पूर्णांक j_trans_id;
	अचिन्हित दीर्घ j_mount_id;

	/* start of current रुकोing commit (index पूर्णांकo j_ap_blocks) */
	अचिन्हित दीर्घ j_start;
	अचिन्हित दीर्घ j_len;	/* length of current रुकोing commit */

	/* number of buffers requested by journal_begin() */
	अचिन्हित दीर्घ j_len_alloc;

	atomic_t j_wcount;	/* count of ग_लिखोrs क्रम current commit */

	/* batch count. allows turning X transactions पूर्णांकo 1 */
	अचिन्हित दीर्घ j_bcount;

	/* first unflushed transactions offset */
	अचिन्हित दीर्घ j_first_unflushed_offset;

	/* last fully flushed journal बारtamp */
	अचिन्हित j_last_flush_trans_id;

	काष्ठा buffer_head *j_header_bh;

	समय64_t j_trans_start_समय;	/* समय this transaction started */
	काष्ठा mutex j_mutex;
	काष्ठा mutex j_flush_mutex;

	/* रुको क्रम current transaction to finish beक्रमe starting new one */
	रुको_queue_head_t j_join_रुको;

	atomic_t j_jlock;		/* lock क्रम j_join_रुको */
	पूर्णांक j_list_biपंचांगap_index;	/* number of next list biपंचांगap to use */

	/* no more journal begins allowed. MUST sleep on j_join_रुको */
	पूर्णांक j_must_रुको;

	/* next journal_end will flush all journal list */
	पूर्णांक j_next_full_flush;

	/* next journal_end will flush all async commits */
	पूर्णांक j_next_async_flush;

	पूर्णांक j_cnode_used;	/* number of cnodes on the used list */
	पूर्णांक j_cnode_मुक्त;	/* number of cnodes on the मुक्त list */

	/* max number of blocks in a transaction.  */
	अचिन्हित पूर्णांक j_trans_max;

	/* max number of blocks to batch पूर्णांकo a trans */
	अचिन्हित पूर्णांक j_max_batch;

	/* in seconds, how old can an async commit be */
	अचिन्हित पूर्णांक j_max_commit_age;

	/* in seconds, how old can a transaction be */
	अचिन्हित पूर्णांक j_max_trans_age;

	/* the शेष क्रम the max commit age */
	अचिन्हित पूर्णांक j_शेष_max_commit_age;

	काष्ठा reiserfs_journal_cnode *j_cnode_मुक्त_list;

	/* orig poपूर्णांकer वापसed from vदो_स्मृति */
	काष्ठा reiserfs_journal_cnode *j_cnode_मुक्त_orig;

	काष्ठा reiserfs_journal_list *j_current_jl;
	पूर्णांक j_मुक्त_biपंचांगap_nodes;
	पूर्णांक j_used_biपंचांगap_nodes;

	पूर्णांक j_num_lists;	/* total number of active transactions */
	पूर्णांक j_num_work_lists;	/* number that need attention from kreiserfsd */

	/* debugging to make sure things are flushed in order */
	अचिन्हित पूर्णांक j_last_flush_id;

	/* debugging to make sure things are committed in order */
	अचिन्हित पूर्णांक j_last_commit_id;

	काष्ठा list_head j_biपंचांगap_nodes;
	काष्ठा list_head j_dirty_buffers;
	spinlock_t j_dirty_buffers_lock;	/* protects j_dirty_buffers */

	/* list of all active transactions */
	काष्ठा list_head j_journal_list;

	/* lists that haven't been touched by ग_लिखोback attempts */
	काष्ठा list_head j_working_list;

	/* hash table क्रम real buffer heads in current trans */
	काष्ठा reiserfs_journal_cnode *j_hash_table[JOURNAL_HASH_SIZE];

	/* hash table क्रम all the real buffer heads in all the transactions */
	काष्ठा reiserfs_journal_cnode *j_list_hash_table[JOURNAL_HASH_SIZE];

	/* array of biपंचांगaps to record the deleted blocks */
	काष्ठा reiserfs_list_biपंचांगap j_list_biपंचांगap[JOURNAL_NUM_BITMAPS];

	/* list of inodes which have pपुनः_स्मृतिated blocks */
	काष्ठा list_head j_pपुनः_स्मृति_list;
	पूर्णांक j_persistent_trans;
	अचिन्हित दीर्घ j_max_trans_size;
	अचिन्हित दीर्घ j_max_batch_size;

	पूर्णांक j_त्रुटि_सं;

	/* when flushing ordered buffers, throttle new ordered ग_लिखोrs */
	काष्ठा delayed_work j_work;
	काष्ठा super_block *j_work_sb;
	atomic_t j_async_throttle;
पूर्ण;

क्रमागत journal_state_bits अणु
	J_WRITERS_BLOCKED = 1,	/* set when new ग_लिखोrs not allowed */
	J_WRITERS_QUEUED,    /* set when log is full due to too many ग_लिखोrs */
	J_ABORTED,           /* set when log is पातed */
पूर्ण;

/* ick.  magic string to find desc blocks in the journal */
#घोषणा JOURNAL_DESC_MAGIC "ReIsErLB"

प्रकार __u32(*hashf_t) (स्थिर चिन्हित अक्षर *, पूर्णांक);

काष्ठा reiserfs_biपंचांगap_info अणु
	__u32 मुक्त_count;
पूर्ण;

काष्ठा proc_dir_entry;

#अगर defined( CONFIG_PROC_FS ) && defined( CONFIG_REISERFS_PROC_INFO )
प्रकार अचिन्हित दीर्घ पूर्णांक stat_cnt_t;
प्रकार काष्ठा reiserfs_proc_info_data अणु
	spinlock_t lock;
	पूर्णांक निकासing;
	पूर्णांक max_hash_collisions;

	stat_cnt_t bपढ़ोs;
	stat_cnt_t bपढ़ो_miss;
	stat_cnt_t search_by_key;
	stat_cnt_t search_by_key_fs_changed;
	stat_cnt_t search_by_key_restarted;

	stat_cnt_t insert_item_restarted;
	stat_cnt_t paste_पूर्णांकo_item_restarted;
	stat_cnt_t cut_from_item_restarted;
	stat_cnt_t delete_solid_item_restarted;
	stat_cnt_t delete_item_restarted;

	stat_cnt_t leaked_oid;
	stat_cnt_t leaves_removable;

	/*
	 * balances per level.
	 * Use explicit 5 as MAX_HEIGHT is not visible yet.
	 */
	stat_cnt_t balance_at[5];	/* XXX */
	/* sbk == search_by_key */
	stat_cnt_t sbk_पढ़ो_at[5];	/* XXX */
	stat_cnt_t sbk_fs_changed[5];
	stat_cnt_t sbk_restarted[5];
	stat_cnt_t items_at[5];	/* XXX */
	stat_cnt_t मुक्त_at[5];	/* XXX */
	stat_cnt_t can_node_be_हटाओd[5];	/* XXX */
	दीर्घ पूर्णांक lnum[5];	/* XXX */
	दीर्घ पूर्णांक rnum[5];	/* XXX */
	दीर्घ पूर्णांक lbytes[5];	/* XXX */
	दीर्घ पूर्णांक rbytes[5];	/* XXX */
	stat_cnt_t get_neighbors[5];
	stat_cnt_t get_neighbors_restart[5];
	stat_cnt_t need_l_neighbor[5];
	stat_cnt_t need_r_neighbor[5];

	stat_cnt_t मुक्त_block;
	काष्ठा __scan_biपंचांगap_stats अणु
		stat_cnt_t call;
		stat_cnt_t रुको;
		stat_cnt_t bmap;
		stat_cnt_t retry;
		stat_cnt_t in_journal_hपूर्णांक;
		stat_cnt_t in_journal_nohपूर्णांक;
		stat_cnt_t stolen;
	पूर्ण scan_biपंचांगap;
	काष्ठा __journal_stats अणु
		stat_cnt_t in_journal;
		stat_cnt_t in_journal_biपंचांगap;
		stat_cnt_t in_journal_reusable;
		stat_cnt_t lock_journal;
		stat_cnt_t lock_journal_रुको;
		stat_cnt_t journal_being;
		stat_cnt_t journal_relock_ग_लिखोrs;
		stat_cnt_t journal_relock_wcount;
		stat_cnt_t mark_dirty;
		stat_cnt_t mark_dirty_alपढ़ोy;
		stat_cnt_t mark_dirty_notjournal;
		stat_cnt_t restore_prepared;
		stat_cnt_t prepare;
		stat_cnt_t prepare_retry;
	पूर्ण journal;
पूर्ण reiserfs_proc_info_data_t;
#अन्यथा
प्रकार काष्ठा reiserfs_proc_info_data अणु
पूर्ण reiserfs_proc_info_data_t;
#पूर्ण_अगर

/* Number of quota types we support */
#घोषणा REISERFS_MAXQUOTAS 2

/* reiserfs जोड़ of in-core super block data */
काष्ठा reiserfs_sb_info अणु
	/* Buffer containing the super block */
	काष्ठा buffer_head *s_sbh;

	/* Poपूर्णांकer to the on-disk super block in the buffer */
	काष्ठा reiserfs_super_block *s_rs;
	काष्ठा reiserfs_biपंचांगap_info *s_ap_biपंचांगap;

	/* poपूर्णांकer to journal inक्रमmation */
	काष्ठा reiserfs_journal *s_journal;

	अचिन्हित लघु s_mount_state;	/* reiserfs state (valid, invalid) */

	/* Serialize ग_लिखोrs access, replace the old bkl */
	काष्ठा mutex lock;

	/* Owner of the lock (can be recursive) */
	काष्ठा task_काष्ठा *lock_owner;

	/* Depth of the lock, start from -1 like the bkl */
	पूर्णांक lock_depth;

	काष्ठा workqueue_काष्ठा *commit_wq;

	/* Comment? -Hans */
	व्योम (*end_io_handler) (काष्ठा buffer_head *, पूर्णांक);

	/*
	 * poपूर्णांकer to function which is used to sort names in directory.
	 * Set on mount
	 */
	hashf_t s_hash_function;

	/* reiserfs's mount options are set here */
	अचिन्हित दीर्घ s_mount_opt;

	/* This is a काष्ठाure that describes block allocator options */
	काष्ठा अणु
		/* Bitfield क्रम enable/disable kind of options */
		अचिन्हित दीर्घ bits;

		/*
		 * size started from which we consider file
		 * to be a large one (in blocks)
		 */
		अचिन्हित दीर्घ large_file_size;

		पूर्णांक border;	/* percentage of disk, border takes */

		/*
		 * Minimal file size (in blocks) starting
		 * from which we करो pपुनः_स्मृतिations
		 */
		पूर्णांक pपुनः_स्मृतिmin;

		/*
		 * Number of blocks we try to pपुनः_स्मृति when file
		 * reaches pपुनः_स्मृतिmin size (in blocks) or pपुनः_स्मृति_list
		 is empty.
		 */
		पूर्णांक pपुनः_स्मृतिsize;
	पूर्ण s_alloc_options;

	/* Comment? -Hans */
	रुको_queue_head_t s_रुको;
	/* increased by one every समय the  tree माला_लो re-balanced */
	atomic_t s_generation_counter;

	/* File प्रणाली properties. Currently holds on-disk FS क्रमmat */
	अचिन्हित दीर्घ s_properties;

	/* session statistics */
	पूर्णांक s_disk_पढ़ोs;
	पूर्णांक s_disk_ग_लिखोs;
	पूर्णांक s_fix_nodes;
	पूर्णांक s_करो_balance;
	पूर्णांक s_unneeded_left_neighbor;
	पूर्णांक s_good_search_by_key_पढ़ोa;
	पूर्णांक s_bmaps;
	पूर्णांक s_bmaps_without_search;
	पूर्णांक s_direct2indirect;
	पूर्णांक s_indirect2direct;

	/*
	 * set up when it's ok क्रम reiserfs_पढ़ो_inode2() to पढ़ो from
	 * disk inode with nlink==0. Currently this is only used during
	 * finish_unfinished() processing at mount समय
	 */
	पूर्णांक s_is_unlinked_ok;

	reiserfs_proc_info_data_t s_proc_info_data;
	काष्ठा proc_dir_entry *procdir;

	/* amount of blocks reserved क्रम further allocations */
	पूर्णांक reserved_blocks;


	/* this lock on now only used to protect reserved_blocks variable */
	spinlock_t biपंचांगap_lock;
	काष्ठा dentry *priv_root;	/* root of /.reiserfs_priv */
	काष्ठा dentry *xattr_root;	/* root of /.reiserfs_priv/xattrs */
	पूर्णांक j_त्रुटि_सं;

	पूर्णांक work_queued;              /* non-zero delayed work is queued */
	काष्ठा delayed_work old_work; /* old transactions flush delayed work */
	spinlock_t old_work_lock;     /* protects old_work and work_queued */

#अगर_घोषित CONFIG_QUOTA
	अक्षर *s_qf_names[REISERFS_MAXQUOTAS];
	पूर्णांक s_jquota_fmt;
#पूर्ण_अगर
	अक्षर *s_jdev;		/* Stored jdev क्रम mount option showing */
#अगर_घोषित CONFIG_REISERFS_CHECK

	/*
	 * Detects whether more than one copy of tb exists per superblock
	 * as a means of checking whether करो_balance is executing
	 * concurrently against another tree पढ़ोer/ग_लिखोr on a same
	 * mount poपूर्णांक.
	 */
	काष्ठा tree_balance *cur_tb;
#पूर्ण_अगर
पूर्ण;

/* Definitions of reiserfs on-disk properties: */
#घोषणा REISERFS_3_5 0
#घोषणा REISERFS_3_6 1
#घोषणा REISERFS_OLD_FORMAT 2

/* Mount options */
क्रमागत reiserfs_mount_options अणु
	/* large tails will be created in a session */
	REISERFS_LARGETAIL,
	/*
	 * small (क्रम files less than block size) tails will
	 * be created in a session
	 */
	REISERFS_SMALLTAIL,

	/* replay journal and वापस 0. Use by fsck */
	REPLAYONLY,

	/*
	 * -o conv: causes conversion of old क्रमmat super block to the
	 * new क्रमmat. If not specअगरied - old partition will be dealt
	 * with in a manner of 3.5.x
	 */
	REISERFS_CONVERT,

	/*
	 * -o hash=अणुtea, rupasov, r5, detectपूर्ण is meant क्रम properly mounting
	 * reiserfs disks from 3.5.19 or earlier.  99% of the समय, this
	 * option is not required.  If the normal स्वतःdection code can't
	 * determine which hash to use (because both hashes had the same
	 * value क्रम a file) use this option to क्रमce a specअगरic hash.
	 * It won't allow you to override the existing hash on the FS, so
	 * अगर you have a tea hash disk, and mount with -o hash=rupasov,
	 * the mount will fail.
	 */
	FORCE_TEA_HASH,		/* try to क्रमce tea hash on mount */
	FORCE_RUPASOV_HASH,	/* try to क्रमce rupasov hash on mount */
	FORCE_R5_HASH,		/* try to क्रमce rupasov hash on mount */
	FORCE_HASH_DETECT,	/* try to detect hash function on mount */

	REISERFS_DATA_LOG,
	REISERFS_DATA_ORDERED,
	REISERFS_DATA_WRITEBACK,

	/*
	 * used क्रम testing experimental features, makes benchmarking new
	 * features with and without more convenient, should never be used by
	 * users in any code shipped to users (ideally)
	 */

	REISERFS_NO_BORDER,
	REISERFS_NO_UNHASHED_RELOCATION,
	REISERFS_HASHED_RELOCATION,
	REISERFS_ATTRS,
	REISERFS_XATTRS_USER,
	REISERFS_POSIXACL,
	REISERFS_EXPOSE_PRIVROOT,
	REISERFS_BARRIER_NONE,
	REISERFS_BARRIER_FLUSH,

	/* Actions on error */
	REISERFS_ERROR_PANIC,
	REISERFS_ERROR_RO,
	REISERFS_ERROR_CONTINUE,

	REISERFS_USRQUOTA,	/* User quota option specअगरied */
	REISERFS_GRPQUOTA,	/* Group quota option specअगरied */

	REISERFS_TEST1,
	REISERFS_TEST2,
	REISERFS_TEST3,
	REISERFS_TEST4,
	REISERFS_UNSUPPORTED_OPT,
पूर्ण;

#घोषणा reiserfs_r5_hash(s) (REISERFS_SB(s)->s_mount_opt & (1 << FORCE_R5_HASH))
#घोषणा reiserfs_rupasov_hash(s) (REISERFS_SB(s)->s_mount_opt & (1 << FORCE_RUPASOV_HASH))
#घोषणा reiserfs_tea_hash(s) (REISERFS_SB(s)->s_mount_opt & (1 << FORCE_TEA_HASH))
#घोषणा reiserfs_hash_detect(s) (REISERFS_SB(s)->s_mount_opt & (1 << FORCE_HASH_DETECT))
#घोषणा reiserfs_no_border(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_NO_BORDER))
#घोषणा reiserfs_no_unhashed_relocation(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_NO_UNHASHED_RELOCATION))
#घोषणा reiserfs_hashed_relocation(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_HASHED_RELOCATION))
#घोषणा reiserfs_test4(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_TEST4))

#घोषणा have_large_tails(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_LARGETAIL))
#घोषणा have_small_tails(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_SMALLTAIL))
#घोषणा replay_only(s) (REISERFS_SB(s)->s_mount_opt & (1 << REPLAYONLY))
#घोषणा reiserfs_attrs(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_ATTRS))
#घोषणा old_क्रमmat_only(s) (REISERFS_SB(s)->s_properties & (1 << REISERFS_3_5))
#घोषणा convert_reiserfs(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_CONVERT))
#घोषणा reiserfs_data_log(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_DATA_LOG))
#घोषणा reiserfs_data_ordered(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_DATA_ORDERED))
#घोषणा reiserfs_data_ग_लिखोback(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_DATA_WRITEBACK))
#घोषणा reiserfs_xattrs_user(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_XATTRS_USER))
#घोषणा reiserfs_posixacl(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_POSIXACL))
#घोषणा reiserfs_expose_privroot(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_EXPOSE_PRIVROOT))
#घोषणा reiserfs_xattrs_optional(s) (reiserfs_xattrs_user(s) || reiserfs_posixacl(s))
#घोषणा reiserfs_barrier_none(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_BARRIER_NONE))
#घोषणा reiserfs_barrier_flush(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_BARRIER_FLUSH))

#घोषणा reiserfs_error_panic(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_ERROR_PANIC))
#घोषणा reiserfs_error_ro(s) (REISERFS_SB(s)->s_mount_opt & (1 << REISERFS_ERROR_RO))

व्योम reiserfs_file_buffer(काष्ठा buffer_head *bh, पूर्णांक list);
बाह्य काष्ठा file_प्रणाली_type reiserfs_fs_type;
पूर्णांक reiserfs_resize(काष्ठा super_block *, अचिन्हित दीर्घ);

#घोषणा CARRY_ON                0
#घोषणा SCHEDULE_OCCURRED       1

#घोषणा SB_BUFFER_WITH_SB(s) (REISERFS_SB(s)->s_sbh)
#घोषणा SB_JOURNAL(s) (REISERFS_SB(s)->s_journal)
#घोषणा SB_JOURNAL_1st_RESERVED_BLOCK(s) (SB_JOURNAL(s)->j_1st_reserved_block)
#घोषणा SB_JOURNAL_LEN_FREE(s) (SB_JOURNAL(s)->j_journal_len_मुक्त)
#घोषणा SB_AP_BITMAP(s) (REISERFS_SB(s)->s_ap_biपंचांगap)

#घोषणा SB_DISK_JOURNAL_HEAD(s) (SB_JOURNAL(s)->j_header_bh->)

#घोषणा reiserfs_is_journal_पातed(journal) (unlikely (__reiserfs_is_journal_पातed (journal)))
अटल अंतरभूत पूर्णांक __reiserfs_is_journal_पातed(काष्ठा reiserfs_journal
						*journal)
अणु
	वापस test_bit(J_ABORTED, &journal->j_state);
पूर्ण

/*
 * Locking primitives. The ग_लिखो lock is a per superblock
 * special mutex that has properties बंद to the Big Kernel Lock
 * which was used in the previous locking scheme.
 */
व्योम reiserfs_ग_लिखो_lock(काष्ठा super_block *s);
व्योम reiserfs_ग_लिखो_unlock(काष्ठा super_block *s);
पूर्णांक __must_check reiserfs_ग_लिखो_unlock_nested(काष्ठा super_block *s);
व्योम reiserfs_ग_लिखो_lock_nested(काष्ठा super_block *s, पूर्णांक depth);

#अगर_घोषित CONFIG_REISERFS_CHECK
व्योम reiserfs_lock_check_recursive(काष्ठा super_block *s);
#अन्यथा
अटल अंतरभूत व्योम reiserfs_lock_check_recursive(काष्ठा super_block *s) अणु पूर्ण
#पूर्ण_अगर

/*
 * Several mutexes depend on the ग_लिखो lock.
 * However someबार we want to relax the ग_लिखो lock जबतक we hold
 * these mutexes, according to the release/reacquire on schedule()
 * properties of the Bkl that were used.
 * Reiserfs perक्रमmances and locking were based on this scheme.
 * Now that the ग_लिखो lock is a mutex and not the bkl anymore, करोing so
 * may result in a deadlock:
 *
 * A acquire ग_लिखो_lock
 * A acquire j_commit_mutex
 * A release ग_लिखो_lock and रुको क्रम something
 * B acquire ग_लिखो_lock
 * B can't acquire j_commit_mutex and sleep
 * A can't acquire ग_लिखो lock anymore
 * deadlock
 *
 * What we करो here is aव्योमing such deadlock by playing the same game
 * than the Bkl: अगर we can't acquire a mutex that depends on the ग_लिखो lock,
 * we release the ग_लिखो lock, रुको a bit and then retry.
 *
 * The mutexes concerned by this hack are:
 * - The commit mutex of a journal list
 * - The flush mutex
 * - The journal lock
 * - The inode mutex
 */
अटल अंतरभूत व्योम reiserfs_mutex_lock_safe(काष्ठा mutex *m,
					    काष्ठा super_block *s)
अणु
	पूर्णांक depth;

	depth = reiserfs_ग_लिखो_unlock_nested(s);
	mutex_lock(m);
	reiserfs_ग_लिखो_lock_nested(s, depth);
पूर्ण

अटल अंतरभूत व्योम
reiserfs_mutex_lock_nested_safe(काष्ठा mutex *m, अचिन्हित पूर्णांक subclass,
				काष्ठा super_block *s)
अणु
	पूर्णांक depth;

	depth = reiserfs_ग_लिखो_unlock_nested(s);
	mutex_lock_nested(m, subclass);
	reiserfs_ग_लिखो_lock_nested(s, depth);
पूर्ण

अटल अंतरभूत व्योम
reiserfs_करोwn_पढ़ो_safe(काष्ठा rw_semaphore *sem, काष्ठा super_block *s)
अणु
       पूर्णांक depth;
       depth = reiserfs_ग_लिखो_unlock_nested(s);
       करोwn_पढ़ो(sem);
       reiserfs_ग_लिखो_lock_nested(s, depth);
पूर्ण

/*
 * When we schedule, we usually want to also release the ग_लिखो lock,
 * according to the previous bkl based locking scheme of reiserfs.
 */
अटल अंतरभूत व्योम reiserfs_cond_resched(काष्ठा super_block *s)
अणु
	अगर (need_resched()) अणु
		पूर्णांक depth;

		depth = reiserfs_ग_लिखो_unlock_nested(s);
		schedule();
		reiserfs_ग_लिखो_lock_nested(s, depth);
	पूर्ण
पूर्ण

काष्ठा fid;

/*
 * in पढ़ोing the #घोषणाs, it may help to understand that they employ
 *  the following abbreviations:
 *
 *  B = Buffer
 *  I = Item header
 *  H = Height within the tree (should be changed to LEV)
 *  N = Number of the item in the node
 *  STAT = stat data
 *  DEH = Directory Entry Header
 *  EC = Entry Count
 *  E = Entry number
 *  UL = Unचिन्हित Long
 *  BLKH = BLocK Header
 *  UNFM = UNForMatted node
 *  DC = Disk Child
 *  P = Path
 *
 *  These #घोषणाs are named by concatenating these abbreviations,
 *  where first comes the arguments, and last comes the वापस value,
 *  of the macro.
 */

#घोषणा USE_INODE_GENERATION_COUNTER

#घोषणा REISERFS_PREALLOCATE
#घोषणा DISPLACE_NEW_PACKING_LOCALITIES
#घोषणा PREALLOCATION_SIZE 9

/* n must be घातer of 2 */
#घोषणा _ROUND_UP(x,n) (((x)+(n)-1u) & ~((n)-1u))

/*
 * to be ok क्रम alpha and others we have to align काष्ठाures to 8 byte
 * boundary.
 * FIXME: करो not change 4 by anything अन्यथा: there is code which relies on that
 */
#घोषणा ROUND_UP(x) _ROUND_UP(x,8LL)

/*
 * debug levels.  Right now, CONFIG_REISERFS_CHECK means prपूर्णांक all debug
 * messages.
 */
#घोषणा REISERFS_DEBUG_CODE 5	/* extra messages to help find/debug errors */

व्योम __reiserfs_warning(काष्ठा super_block *s, स्थिर अक्षर *id,
			 स्थिर अक्षर *func, स्थिर अक्षर *fmt, ...);
#घोषणा reiserfs_warning(s, id, fmt, args...) \
	 __reiserfs_warning(s, id, __func__, fmt, ##args)
/* निश्चितions handling */

/* always check a condition and panic अगर it's false. */
#घोषणा __RASSERT(cond, scond, क्रमmat, args...)			\
करो अणु									\
	अगर (!(cond))							\
		reiserfs_panic(शून्य, "assertion failure", "(" #cond ") at " \
			       __खाता__ ":%i:%s: " क्रमmat "\n",		\
			       __LINE__, __func__ , ##args);		\
पूर्ण जबतक (0)

#घोषणा RASSERT(cond, क्रमmat, args...) __RASSERT(cond, #cond, क्रमmat, ##args)

#अगर defined( CONFIG_REISERFS_CHECK )
#घोषणा RFALSE(cond, क्रमmat, args...) __RASSERT(!(cond), "!(" #cond ")", क्रमmat, ##args)
#अन्यथा
#घोषणा RFALSE( cond, क्रमmat, args... ) करो अणु;पूर्ण जबतक( 0 )
#पूर्ण_अगर

#घोषणा CONSTF __attribute_स्थिर__
/*
 * Disk Data Structures
 */

/***************************************************************************
 *                             SUPER BLOCK                                 *
 ***************************************************************************/

/*
 * Structure of super block on disk, a version of which in RAM is often
 * accessed as REISERFS_SB(s)->s_rs. The version in RAM is part of a larger
 * काष्ठाure containing fields never written to disk.
 */
#घोषणा UNSET_HASH 0	/* Detect hash on disk */
#घोषणा TEA_HASH  1
#घोषणा YURA_HASH 2
#घोषणा R5_HASH   3
#घोषणा DEFAULT_HASH R5_HASH

काष्ठा journal_params अणु
	/* where करोes journal start from on its * device */
	__le32 jp_journal_1st_block;

	/* journal device st_rdev */
	__le32 jp_journal_dev;

	/* size of the journal */
	__le32 jp_journal_size;

	/* max number of blocks in a transaction. */
	__le32 jp_journal_trans_max;

	/*
	 * अक्रमom value made on fs creation
	 * (this was sb_journal_block_count)
	 */
	__le32 jp_journal_magic;

	/* max number of blocks to batch पूर्णांकo a trans */
	__le32 jp_journal_max_batch;

	/* in seconds, how old can an async  commit be */
	__le32 jp_journal_max_commit_age;

	/* in seconds, how old can a transaction be */
	__le32 jp_journal_max_trans_age;
पूर्ण;

/* this is the super from 3.5.X, where X >= 10 */
काष्ठा reiserfs_super_block_v1 अणु
	__le32 s_block_count;	/* blocks count         */
	__le32 s_मुक्त_blocks;	/* मुक्त blocks count    */
	__le32 s_root_block;	/* root block number    */
	काष्ठा journal_params s_journal;
	__le16 s_blocksize;	/* block size */

	/* max size of object id array, see get_objectid() commentary  */
	__le16 s_oid_maxsize;
	__le16 s_oid_cursize;	/* current size of object id array */

	/* this is set to 1 when fileप्रणाली was umounted, to 2 - when not */
	__le16 s_umount_state;

	/*
	 * reiserfs magic string indicates that file प्रणाली is reiserfs:
	 * "ReIsErFs" or "ReIsEr2Fs" or "ReIsEr3Fs"
	 */
	अक्षर s_magic[10];

	/*
	 * it is set to used by fsck to mark which
	 * phase of rebuilding is करोne
	 */
	__le16 s_fs_state;
	/*
	 * indicate, what hash function is being use
	 * to sort names in a directory
	 */
	__le32 s_hash_function_code;
	__le16 s_tree_height;	/* height of disk tree */

	/*
	 * amount of biपंचांगap blocks needed to address
	 * each block of file प्रणाली
	 */
	__le16 s_bmap_nr;

	/*
	 * this field is only reliable on fileप्रणाली with non-standard journal
	 */
	__le16 s_version;

	/*
	 * size in blocks of journal area on मुख्य device, we need to
	 * keep after making fs with non-standard journal
	 */
	__le16 s_reserved_क्रम_journal;
पूर्ण __attribute__ ((__packed__));

#घोषणा SB_SIZE_V1 (माप(काष्ठा reiserfs_super_block_v1))

/* this is the on disk super block */
काष्ठा reiserfs_super_block अणु
	काष्ठा reiserfs_super_block_v1 s_v1;
	__le32 s_inode_generation;

	/* Right now used only by inode-attributes, अगर enabled */
	__le32 s_flags;

	अचिन्हित अक्षर s_uuid[16];	/* fileप्रणाली unique identअगरier */
	अचिन्हित अक्षर s_label[16];	/* fileप्रणाली volume label */
	__le16 s_mnt_count;		/* Count of mounts since last fsck */
	__le16 s_max_mnt_count;		/* Maximum mounts beक्रमe check */
	__le32 s_lastcheck;		/* Timestamp of last fsck */
	__le32 s_check_पूर्णांकerval;	/* Interval between checks */

	/*
	 * zero filled by mkreiserfs and reiserfs_convert_objectid_map_v1()
	 * so any additions must be updated there as well. */
	अक्षर s_unused[76];
पूर्ण __attribute__ ((__packed__));

#घोषणा SB_SIZE (माप(काष्ठा reiserfs_super_block))

#घोषणा REISERFS_VERSION_1 0
#घोषणा REISERFS_VERSION_2 2

/* on-disk super block fields converted to cpu क्रमm */
#घोषणा SB_DISK_SUPER_BLOCK(s) (REISERFS_SB(s)->s_rs)
#घोषणा SB_V1_DISK_SUPER_BLOCK(s) (&(SB_DISK_SUPER_BLOCK(s)->s_v1))
#घोषणा SB_BLOCKSIZE(s) \
        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_blocksize))
#घोषणा SB_BLOCK_COUNT(s) \
        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_block_count))
#घोषणा SB_FREE_BLOCKS(s) \
        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_मुक्त_blocks))
#घोषणा SB_REISERFS_MAGIC(s) \
        (SB_V1_DISK_SUPER_BLOCK(s)->s_magic)
#घोषणा SB_ROOT_BLOCK(s) \
        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_root_block))
#घोषणा SB_TREE_HEIGHT(s) \
        le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_tree_height))
#घोषणा SB_REISERFS_STATE(s) \
        le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_umount_state))
#घोषणा SB_VERSION(s) le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_version))
#घोषणा SB_BMAP_NR(s) le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_bmap_nr))

#घोषणा PUT_SB_BLOCK_COUNT(s, val) \
   करो अणु SB_V1_DISK_SUPER_BLOCK(s)->s_block_count = cpu_to_le32(val); पूर्ण जबतक (0)
#घोषणा PUT_SB_FREE_BLOCKS(s, val) \
   करो अणु SB_V1_DISK_SUPER_BLOCK(s)->s_मुक्त_blocks = cpu_to_le32(val); पूर्ण जबतक (0)
#घोषणा PUT_SB_ROOT_BLOCK(s, val) \
   करो अणु SB_V1_DISK_SUPER_BLOCK(s)->s_root_block = cpu_to_le32(val); पूर्ण जबतक (0)
#घोषणा PUT_SB_TREE_HEIGHT(s, val) \
   करो अणु SB_V1_DISK_SUPER_BLOCK(s)->s_tree_height = cpu_to_le16(val); पूर्ण जबतक (0)
#घोषणा PUT_SB_REISERFS_STATE(s, val) \
   करो अणु SB_V1_DISK_SUPER_BLOCK(s)->s_umount_state = cpu_to_le16(val); पूर्ण जबतक (0)
#घोषणा PUT_SB_VERSION(s, val) \
   करो अणु SB_V1_DISK_SUPER_BLOCK(s)->s_version = cpu_to_le16(val); पूर्ण जबतक (0)
#घोषणा PUT_SB_BMAP_NR(s, val) \
   करो अणु SB_V1_DISK_SUPER_BLOCK(s)->s_bmap_nr = cpu_to_le16 (val); पूर्ण जबतक (0)

#घोषणा SB_ONDISK_JP(s) (&SB_V1_DISK_SUPER_BLOCK(s)->s_journal)
#घोषणा SB_ONDISK_JOURNAL_SIZE(s) \
         le32_to_cpu ((SB_ONDISK_JP(s)->jp_journal_size))
#घोषणा SB_ONDISK_JOURNAL_1st_BLOCK(s) \
         le32_to_cpu ((SB_ONDISK_JP(s)->jp_journal_1st_block))
#घोषणा SB_ONDISK_JOURNAL_DEVICE(s) \
         le32_to_cpu ((SB_ONDISK_JP(s)->jp_journal_dev))
#घोषणा SB_ONDISK_RESERVED_FOR_JOURNAL(s) \
         le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_reserved_क्रम_journal))

#घोषणा is_block_in_log_or_reserved_area(s, block) \
         block >= SB_JOURNAL_1st_RESERVED_BLOCK(s) \
         && block < SB_JOURNAL_1st_RESERVED_BLOCK(s) +  \
         ((!is_reiserfs_jr(SB_DISK_SUPER_BLOCK(s)) ? \
         SB_ONDISK_JOURNAL_SIZE(s) + 1 : SB_ONDISK_RESERVED_FOR_JOURNAL(s)))

पूर्णांक is_reiserfs_3_5(काष्ठा reiserfs_super_block *rs);
पूर्णांक is_reiserfs_3_6(काष्ठा reiserfs_super_block *rs);
पूर्णांक is_reiserfs_jr(काष्ठा reiserfs_super_block *rs);

/*
 * ReiserFS leaves the first 64k unused, so that partition labels have
 * enough space.  If someone wants to ग_लिखो a fancy bootloader that
 * needs more than 64k, let us know, and this will be increased in size.
 * This number must be larger than the largest block size on any
 * platक्रमm, or code will अवरोध.  -Hans
 */
#घोषणा REISERFS_DISK_OFFSET_IN_BYTES (64 * 1024)
#घोषणा REISERFS_FIRST_BLOCK unused_define
#घोषणा REISERFS_JOURNAL_OFFSET_IN_BYTES REISERFS_DISK_OFFSET_IN_BYTES

/* the spot क्रम the super in versions 3.5 - 3.5.10 (inclusive) */
#घोषणा REISERFS_OLD_DISK_OFFSET_IN_BYTES (8 * 1024)

/* reiserfs पूर्णांकernal error code (used by search_by_key and fix_nodes)) */
#घोषणा CARRY_ON      0
#घोषणा REPEAT_SEARCH -1
#घोषणा IO_ERROR      -2
#घोषणा NO_DISK_SPACE -3
#घोषणा NO_BALANCING_NEEDED  (-4)
#घोषणा NO_MORE_UNUSED_CONTIGUOUS_BLOCKS (-5)
#घोषणा QUOTA_EXCEEDED -6

प्रकार __u32 b_blocknr_t;
प्रकार __le32 unp_t;

काष्ठा unfm_nodeinfo अणु
	unp_t unfm_nodक्रमागत;
	अचिन्हित लघु unfm_मुक्तspace;
पूर्ण;

/* there are two क्रमmats of keys: 3.5 and 3.6 */
#घोषणा KEY_FORMAT_3_5 0
#घोषणा KEY_FORMAT_3_6 1

/* there are two stat datas */
#घोषणा STAT_DATA_V1 0
#घोषणा STAT_DATA_V2 1

अटल अंतरभूत काष्ठा reiserfs_inode_info *REISERFS_I(स्थिर काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा reiserfs_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा reiserfs_sb_info *REISERFS_SB(स्थिर काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

/*
 * Don't trust REISERFS_SB(sb)->s_bmap_nr, it's a u16
 * which overflows on large file प्रणालीs.
 */
अटल अंतरभूत __u32 reiserfs_bmap_count(काष्ठा super_block *sb)
अणु
	वापस (SB_BLOCK_COUNT(sb) - 1) / (sb->s_blocksize * 8) + 1;
पूर्ण

अटल अंतरभूत पूर्णांक bmap_would_wrap(अचिन्हित bmap_nr)
अणु
	वापस bmap_nr > ((1LL << 16) - 1);
पूर्ण

बाह्य स्थिर काष्ठा xattr_handler *reiserfs_xattr_handlers[];

/*
 * this says about version of key of all items (but stat data) the
 * object consists of
 */
#घोषणा get_inode_item_key_version( inode )                                    \
    ((REISERFS_I(inode)->i_flags & i_item_key_version_mask) ? KEY_FORMAT_3_6 : KEY_FORMAT_3_5)

#घोषणा set_inode_item_key_version( inode, version )                           \
         (अणु अगर((version)==KEY_FORMAT_3_6)                                      \
                REISERFS_I(inode)->i_flags |= i_item_key_version_mask;      \
            अन्यथा                                                               \
                REISERFS_I(inode)->i_flags &= ~i_item_key_version_mask; पूर्ण)

#घोषणा get_inode_sd_version(inode)                                            \
    ((REISERFS_I(inode)->i_flags & i_stat_data_version_mask) ? STAT_DATA_V2 : STAT_DATA_V1)

#घोषणा set_inode_sd_version(inode, version)                                   \
         (अणु अगर((version)==STAT_DATA_V2)                                        \
                REISERFS_I(inode)->i_flags |= i_stat_data_version_mask;     \
            अन्यथा                                                               \
                REISERFS_I(inode)->i_flags &= ~i_stat_data_version_mask; पूर्ण)

/*
 * This is an aggressive tail suppression policy, I am hoping it
 * improves our benchmarks. The principle behind it is that percentage
 * space saving is what matters, not असलolute space saving.  This is
 * non-पूर्णांकuitive, but it helps to understand it अगर you consider that the
 * cost to access 4 blocks is not much more than the cost to access 1
 * block, अगर you have to करो a seek and rotate.  A tail risks a
 * non-linear disk access that is signअगरicant as a percentage of total
 * समय cost क्रम a 4 block file and saves an amount of space that is
 * less signअगरicant as a percentage of space, or so goes the hypothesis.
 * -Hans
 */
#घोषणा STORE_TAIL_IN_UNFM_S1(n_file_size,n_tail_size,n_block_size) \
(\
  (!(n_tail_size)) || \
  (((n_tail_size) > MAX_सूचीECT_ITEM_LEN(n_block_size)) || \
   ( (n_file_size) >= (n_block_size) * 4 ) || \
   ( ( (n_file_size) >= (n_block_size) * 3 ) && \
     ( (n_tail_size) >=   (MAX_सूचीECT_ITEM_LEN(n_block_size))/4) ) || \
   ( ( (n_file_size) >= (n_block_size) * 2 ) && \
     ( (n_tail_size) >=   (MAX_सूचीECT_ITEM_LEN(n_block_size))/2) ) || \
   ( ( (n_file_size) >= (n_block_size) ) && \
     ( (n_tail_size) >=   (MAX_सूचीECT_ITEM_LEN(n_block_size) * 3)/4) ) ) \
)

/*
 * Another strategy क्रम tails, this one means only create a tail अगर all the
 * file would fit पूर्णांकo one सूचीECT item.
 * Primary पूर्णांकention क्रम this one is to increase perक्रमmance by decreasing
 * seeking.
*/
#घोषणा STORE_TAIL_IN_UNFM_S2(n_file_size,n_tail_size,n_block_size) \
(\
  (!(n_tail_size)) || \
  (((n_file_size) > MAX_सूचीECT_ITEM_LEN(n_block_size)) ) \
)

/*
 * values क्रम s_umount_state field
 */
#घोषणा REISERFS_VALID_FS    1
#घोषणा REISERFS_ERROR_FS    2

/*
 * there are 5 item types currently
 */
#घोषणा TYPE_STAT_DATA 0
#घोषणा TYPE_INसूचीECT 1
#घोषणा TYPE_सूचीECT 2
#घोषणा TYPE_सूचीENTRY 3
#घोषणा TYPE_MAXTYPE 3
#घोषणा TYPE_ANY 15		/* FIXME: comment is required */

/***************************************************************************
 *                       KEY & ITEM HEAD                                   *
 ***************************************************************************/

/* * directories use this key as well as old files */
काष्ठा offset_v1 अणु
	__le32 k_offset;
	__le32 k_uniqueness;
पूर्ण __attribute__ ((__packed__));

काष्ठा offset_v2 अणु
	__le64 v;
पूर्ण __attribute__ ((__packed__));

अटल अंतरभूत __u16 offset_v2_k_type(स्थिर काष्ठा offset_v2 *v2)
अणु
	__u8 type = le64_to_cpu(v2->v) >> 60;
	वापस (type <= TYPE_MAXTYPE) ? type : TYPE_ANY;
पूर्ण

अटल अंतरभूत व्योम set_offset_v2_k_type(काष्ठा offset_v2 *v2, पूर्णांक type)
अणु
	v2->v =
	    (v2->v & cpu_to_le64(~0ULL >> 4)) | cpu_to_le64((__u64) type << 60);
पूर्ण

अटल अंतरभूत loff_t offset_v2_k_offset(स्थिर काष्ठा offset_v2 *v2)
अणु
	वापस le64_to_cpu(v2->v) & (~0ULL >> 4);
पूर्ण

अटल अंतरभूत व्योम set_offset_v2_k_offset(काष्ठा offset_v2 *v2, loff_t offset)
अणु
	offset &= (~0ULL >> 4);
	v2->v = (v2->v & cpu_to_le64(15ULL << 60)) | cpu_to_le64(offset);
पूर्ण

/*
 * Key of an item determines its location in the S+tree, and
 * is composed of 4 components
 */
काष्ठा reiserfs_key अणु
	/* packing locality: by शेष parent directory object id */
	__le32 k_dir_id;

	__le32 k_objectid;	/* object identअगरier */
	जोड़ अणु
		काष्ठा offset_v1 k_offset_v1;
		काष्ठा offset_v2 k_offset_v2;
	पूर्ण __attribute__ ((__packed__)) u;
पूर्ण __attribute__ ((__packed__));

काष्ठा in_core_key अणु
	/* packing locality: by शेष parent directory object id */
	__u32 k_dir_id;
	__u32 k_objectid;	/* object identअगरier */
	__u64 k_offset;
	__u8 k_type;
पूर्ण;

काष्ठा cpu_key अणु
	काष्ठा in_core_key on_disk_key;
	पूर्णांक version;
	/* 3 in all हालs but direct2indirect and indirect2direct conversion */
	पूर्णांक key_length;
पूर्ण;

/*
 * Our function क्रम comparing keys can compare keys of dअगरferent
 * lengths.  It takes as a parameter the length of the keys it is to
 * compare.  These defines are used in determining what is to be passed
 * to it as that parameter.
 */
#घोषणा REISERFS_FULL_KEY_LEN     4
#घोषणा REISERFS_SHORT_KEY_LEN    2

/* The result of the key compare */
#घोषणा FIRST_GREATER 1
#घोषणा SECOND_GREATER -1
#घोषणा KEYS_IDENTICAL 0
#घोषणा KEY_FOUND 1
#घोषणा KEY_NOT_FOUND 0

#घोषणा KEY_SIZE (माप(काष्ठा reiserfs_key))

/* वापस values क्रम search_by_key and clones */
#घोषणा ITEM_FOUND 1
#घोषणा ITEM_NOT_FOUND 0
#घोषणा ENTRY_FOUND 1
#घोषणा ENTRY_NOT_FOUND 0
#घोषणा सूचीECTORY_NOT_FOUND -1
#घोषणा REGULAR_खाता_FOUND -2
#घोषणा सूचीECTORY_FOUND -3
#घोषणा BYTE_FOUND 1
#घोषणा BYTE_NOT_FOUND 0
#घोषणा खाता_NOT_FOUND -1

#घोषणा POSITION_FOUND 1
#घोषणा POSITION_NOT_FOUND 0

/* वापस values क्रम reiserfs_find_entry and search_by_entry_key */
#घोषणा NAME_FOUND 1
#घोषणा NAME_NOT_FOUND 0
#घोषणा GOTO_PREVIOUS_ITEM 2
#घोषणा NAME_FOUND_INVISIBLE 3

/*
 * Everything in the fileप्रणाली is stored as a set of items.  The
 * item head contains the key of the item, its मुक्त space (क्रम
 * indirect items) and specअगरies the location of the item itself
 * within the block.
 */

काष्ठा item_head अणु
	/*
	 * Everything in the tree is found by searching क्रम it based on
	 * its key.
	 */
	काष्ठा reiserfs_key ih_key;
	जोड़ अणु
		/*
		 * The मुक्त space in the last unक्रमmatted node of an
		 * indirect item अगर this is an indirect item.  This
		 * equals 0xFFFF अगरf this is a direct item or stat data
		 * item. Note that the key, not this field, is used to
		 * determine the item type, and thus which field this
		 * जोड़ contains.
		 */
		__le16 ih_मुक्त_space_reserved;

		/*
		 * Iff this is a directory item, this field equals the
		 * number of directory entries in the directory item.
		 */
		__le16 ih_entry_count;
	पूर्ण __attribute__ ((__packed__)) u;
	__le16 ih_item_len;	/* total size of the item body */

	/* an offset to the item body within the block */
	__le16 ih_item_location;

	/*
	 * 0 क्रम all old items, 2 क्रम new ones. Highest bit is set by fsck
	 * temporary, cleaned after all करोne
	 */
	__le16 ih_version;
पूर्ण __attribute__ ((__packed__));
/* size of item header     */
#घोषणा IH_SIZE (माप(काष्ठा item_head))

#घोषणा ih_मुक्त_space(ih)            le16_to_cpu((ih)->u.ih_मुक्त_space_reserved)
#घोषणा ih_version(ih)               le16_to_cpu((ih)->ih_version)
#घोषणा ih_entry_count(ih)           le16_to_cpu((ih)->u.ih_entry_count)
#घोषणा ih_location(ih)              le16_to_cpu((ih)->ih_item_location)
#घोषणा ih_item_len(ih)              le16_to_cpu((ih)->ih_item_len)

#घोषणा put_ih_मुक्त_space(ih, val)   करो अणु (ih)->u.ih_मुक्त_space_reserved = cpu_to_le16(val); पूर्ण जबतक(0)
#घोषणा put_ih_version(ih, val)      करो अणु (ih)->ih_version = cpu_to_le16(val); पूर्ण जबतक (0)
#घोषणा put_ih_entry_count(ih, val)  करो अणु (ih)->u.ih_entry_count = cpu_to_le16(val); पूर्ण जबतक (0)
#घोषणा put_ih_location(ih, val)     करो अणु (ih)->ih_item_location = cpu_to_le16(val); पूर्ण जबतक (0)
#घोषणा put_ih_item_len(ih, val)     करो अणु (ih)->ih_item_len = cpu_to_le16(val); पूर्ण जबतक (0)

#घोषणा unreachable_item(ih) (ih_version(ih) & (1 << 15))

#घोषणा get_ih_मुक्त_space(ih) (ih_version (ih) == KEY_FORMAT_3_6 ? 0 : ih_मुक्त_space (ih))
#घोषणा set_ih_मुक्त_space(ih,val) put_ih_मुक्त_space((ih), ((ih_version(ih) == KEY_FORMAT_3_6) ? 0 : (val)))

/*
 * these operate on indirect items, where you've got an array of पूर्णांकs
 * at a possibly unaligned location.  These are a noop on ia32
 *
 * p is the array of __u32, i is the index पूर्णांकo the array, v is the value
 * to store there.
 */
#घोषणा get_block_num(p, i) get_unaligned_le32((p) + (i))
#घोषणा put_block_num(p, i, v) put_unaligned_le32((v), (p) + (i))

/* * in old version uniqueness field shows key type */
#घोषणा V1_SD_UNIQUENESS 0
#घोषणा V1_INसूचीECT_UNIQUENESS 0xfffffffe
#घोषणा V1_सूचीECT_UNIQUENESS 0xffffffff
#घोषणा V1_सूचीENTRY_UNIQUENESS 500
#घोषणा V1_ANY_UNIQUENESS 555	/* FIXME: comment is required */

/* here are conversion routines */
अटल अंतरभूत पूर्णांक uniqueness2type(__u32 uniqueness) CONSTF;
अटल अंतरभूत पूर्णांक uniqueness2type(__u32 uniqueness)
अणु
	चयन ((पूर्णांक)uniqueness) अणु
	हाल V1_SD_UNIQUENESS:
		वापस TYPE_STAT_DATA;
	हाल V1_INसूचीECT_UNIQUENESS:
		वापस TYPE_INसूचीECT;
	हाल V1_सूचीECT_UNIQUENESS:
		वापस TYPE_सूचीECT;
	हाल V1_सूचीENTRY_UNIQUENESS:
		वापस TYPE_सूचीENTRY;
	हाल V1_ANY_UNIQUENESS:
	शेष:
		वापस TYPE_ANY;
	पूर्ण
पूर्ण

अटल अंतरभूत __u32 type2uniqueness(पूर्णांक type) CONSTF;
अटल अंतरभूत __u32 type2uniqueness(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल TYPE_STAT_DATA:
		वापस V1_SD_UNIQUENESS;
	हाल TYPE_INसूचीECT:
		वापस V1_INसूचीECT_UNIQUENESS;
	हाल TYPE_सूचीECT:
		वापस V1_सूचीECT_UNIQUENESS;
	हाल TYPE_सूचीENTRY:
		वापस V1_सूचीENTRY_UNIQUENESS;
	हाल TYPE_ANY:
	शेष:
		वापस V1_ANY_UNIQUENESS;
	पूर्ण
पूर्ण

/*
 * key is poपूर्णांकer to on disk key which is stored in le, result is cpu,
 * there is no way to get version of object from key, so, provide
 * version to these defines
 */
अटल अंतरभूत loff_t le_key_k_offset(पूर्णांक version,
				     स्थिर काष्ठा reiserfs_key *key)
अणु
	वापस (version == KEY_FORMAT_3_5) ?
	    le32_to_cpu(key->u.k_offset_v1.k_offset) :
	    offset_v2_k_offset(&(key->u.k_offset_v2));
पूर्ण

अटल अंतरभूत loff_t le_ih_k_offset(स्थिर काष्ठा item_head *ih)
अणु
	वापस le_key_k_offset(ih_version(ih), &(ih->ih_key));
पूर्ण

अटल अंतरभूत loff_t le_key_k_type(पूर्णांक version, स्थिर काष्ठा reiserfs_key *key)
अणु
	अगर (version == KEY_FORMAT_3_5) अणु
		loff_t val = le32_to_cpu(key->u.k_offset_v1.k_uniqueness);
		वापस uniqueness2type(val);
	पूर्ण अन्यथा
		वापस offset_v2_k_type(&(key->u.k_offset_v2));
पूर्ण

अटल अंतरभूत loff_t le_ih_k_type(स्थिर काष्ठा item_head *ih)
अणु
	वापस le_key_k_type(ih_version(ih), &(ih->ih_key));
पूर्ण

अटल अंतरभूत व्योम set_le_key_k_offset(पूर्णांक version, काष्ठा reiserfs_key *key,
				       loff_t offset)
अणु
	अगर (version == KEY_FORMAT_3_5)
		key->u.k_offset_v1.k_offset = cpu_to_le32(offset);
	अन्यथा
		set_offset_v2_k_offset(&key->u.k_offset_v2, offset);
पूर्ण

अटल अंतरभूत व्योम add_le_key_k_offset(पूर्णांक version, काष्ठा reiserfs_key *key,
				       loff_t offset)
अणु
	set_le_key_k_offset(version, key,
			    le_key_k_offset(version, key) + offset);
पूर्ण

अटल अंतरभूत व्योम add_le_ih_k_offset(काष्ठा item_head *ih, loff_t offset)
अणु
	add_le_key_k_offset(ih_version(ih), &(ih->ih_key), offset);
पूर्ण

अटल अंतरभूत व्योम set_le_ih_k_offset(काष्ठा item_head *ih, loff_t offset)
अणु
	set_le_key_k_offset(ih_version(ih), &(ih->ih_key), offset);
पूर्ण

अटल अंतरभूत व्योम set_le_key_k_type(पूर्णांक version, काष्ठा reiserfs_key *key,
				     पूर्णांक type)
अणु
	अगर (version == KEY_FORMAT_3_5) अणु
		type = type2uniqueness(type);
		key->u.k_offset_v1.k_uniqueness = cpu_to_le32(type);
	पूर्ण अन्यथा
	       set_offset_v2_k_type(&key->u.k_offset_v2, type);
पूर्ण

अटल अंतरभूत व्योम set_le_ih_k_type(काष्ठा item_head *ih, पूर्णांक type)
अणु
	set_le_key_k_type(ih_version(ih), &(ih->ih_key), type);
पूर्ण

अटल अंतरभूत पूर्णांक is_direntry_le_key(पूर्णांक version, काष्ठा reiserfs_key *key)
अणु
	वापस le_key_k_type(version, key) == TYPE_सूचीENTRY;
पूर्ण

अटल अंतरभूत पूर्णांक is_direct_le_key(पूर्णांक version, काष्ठा reiserfs_key *key)
अणु
	वापस le_key_k_type(version, key) == TYPE_सूचीECT;
पूर्ण

अटल अंतरभूत पूर्णांक is_indirect_le_key(पूर्णांक version, काष्ठा reiserfs_key *key)
अणु
	वापस le_key_k_type(version, key) == TYPE_INसूचीECT;
पूर्ण

अटल अंतरभूत पूर्णांक is_statdata_le_key(पूर्णांक version, काष्ठा reiserfs_key *key)
अणु
	वापस le_key_k_type(version, key) == TYPE_STAT_DATA;
पूर्ण

/* item header has version.  */
अटल अंतरभूत पूर्णांक is_direntry_le_ih(काष्ठा item_head *ih)
अणु
	वापस is_direntry_le_key(ih_version(ih), &ih->ih_key);
पूर्ण

अटल अंतरभूत पूर्णांक is_direct_le_ih(काष्ठा item_head *ih)
अणु
	वापस is_direct_le_key(ih_version(ih), &ih->ih_key);
पूर्ण

अटल अंतरभूत पूर्णांक is_indirect_le_ih(काष्ठा item_head *ih)
अणु
	वापस is_indirect_le_key(ih_version(ih), &ih->ih_key);
पूर्ण

अटल अंतरभूत पूर्णांक is_statdata_le_ih(काष्ठा item_head *ih)
अणु
	वापस is_statdata_le_key(ih_version(ih), &ih->ih_key);
पूर्ण

/* key is poपूर्णांकer to cpu key, result is cpu */
अटल अंतरभूत loff_t cpu_key_k_offset(स्थिर काष्ठा cpu_key *key)
अणु
	वापस key->on_disk_key.k_offset;
पूर्ण

अटल अंतरभूत loff_t cpu_key_k_type(स्थिर काष्ठा cpu_key *key)
अणु
	वापस key->on_disk_key.k_type;
पूर्ण

अटल अंतरभूत व्योम set_cpu_key_k_offset(काष्ठा cpu_key *key, loff_t offset)
अणु
	key->on_disk_key.k_offset = offset;
पूर्ण

अटल अंतरभूत व्योम set_cpu_key_k_type(काष्ठा cpu_key *key, पूर्णांक type)
अणु
	key->on_disk_key.k_type = type;
पूर्ण

अटल अंतरभूत व्योम cpu_key_k_offset_dec(काष्ठा cpu_key *key)
अणु
	key->on_disk_key.k_offset--;
पूर्ण

#घोषणा is_direntry_cpu_key(key) (cpu_key_k_type (key) == TYPE_सूचीENTRY)
#घोषणा is_direct_cpu_key(key) (cpu_key_k_type (key) == TYPE_सूचीECT)
#घोषणा is_indirect_cpu_key(key) (cpu_key_k_type (key) == TYPE_INसूचीECT)
#घोषणा is_statdata_cpu_key(key) (cpu_key_k_type (key) == TYPE_STAT_DATA)

/* are these used ? */
#घोषणा is_direntry_cpu_ih(ih) (is_direntry_cpu_key (&((ih)->ih_key)))
#घोषणा is_direct_cpu_ih(ih) (is_direct_cpu_key (&((ih)->ih_key)))
#घोषणा is_indirect_cpu_ih(ih) (is_indirect_cpu_key (&((ih)->ih_key)))
#घोषणा is_statdata_cpu_ih(ih) (is_statdata_cpu_key (&((ih)->ih_key)))

#घोषणा I_K_KEY_IN_ITEM(ih, key, n_blocksize) \
    (!COMP_SHORT_KEYS(ih, key) && \
	  I_OFF_BYTE_IN_ITEM(ih, k_offset(key), n_blocksize))

/* maximal length of item */
#घोषणा MAX_ITEM_LEN(block_size) (block_size - BLKH_SIZE - IH_SIZE)
#घोषणा MIN_ITEM_LEN 1

/* object identअगरier क्रम root dir */
#घोषणा REISERFS_ROOT_OBJECTID 2
#घोषणा REISERFS_ROOT_PARENT_OBJECTID 1

बाह्य काष्ठा reiserfs_key root_key;

/*
 * Picture represents a leaf of the S+tree
 *  ______________________________________________________
 * |      |  Array of     |                   |           |
 * |Block |  Object-Item  |      F r e e      |  Objects- |
 * | head |  Headers      |     S p a c e     |   Items   |
 * |______|_______________|___________________|___________|
 */

/*
 * Header of a disk block.  More precisely, header of a क्रमmatted leaf
 * or पूर्णांकernal node, and not the header of an unक्रमmatted node.
 */
काष्ठा block_head अणु
	__le16 blk_level;	/* Level of a block in the tree. */
	__le16 blk_nr_item;	/* Number of keys/items in a block. */
	__le16 blk_मुक्त_space;	/* Block मुक्त space in bytes. */
	__le16 blk_reserved;
	/* dump this in v4/planA */

	/* kept only क्रम compatibility */
	काष्ठा reiserfs_key blk_right_delim_key;
पूर्ण;

#घोषणा BLKH_SIZE                     (माप(काष्ठा block_head))
#घोषणा blkh_level(p_blkh)            (le16_to_cpu((p_blkh)->blk_level))
#घोषणा blkh_nr_item(p_blkh)          (le16_to_cpu((p_blkh)->blk_nr_item))
#घोषणा blkh_मुक्त_space(p_blkh)       (le16_to_cpu((p_blkh)->blk_मुक्त_space))
#घोषणा blkh_reserved(p_blkh)         (le16_to_cpu((p_blkh)->blk_reserved))
#घोषणा set_blkh_level(p_blkh,val)    ((p_blkh)->blk_level = cpu_to_le16(val))
#घोषणा set_blkh_nr_item(p_blkh,val)  ((p_blkh)->blk_nr_item = cpu_to_le16(val))
#घोषणा set_blkh_मुक्त_space(p_blkh,val) ((p_blkh)->blk_मुक्त_space = cpu_to_le16(val))
#घोषणा set_blkh_reserved(p_blkh,val) ((p_blkh)->blk_reserved = cpu_to_le16(val))
#घोषणा blkh_right_delim_key(p_blkh)  ((p_blkh)->blk_right_delim_key)
#घोषणा set_blkh_right_delim_key(p_blkh,val)  ((p_blkh)->blk_right_delim_key = val)

/* values क्रम blk_level field of the काष्ठा block_head */

/*
 * When node माला_लो हटाओd from the tree its blk_level is set to FREE_LEVEL.
 * It is then  used to see whether the node is still in the tree
 */
#घोषणा FREE_LEVEL 0

#घोषणा DISK_LEAF_NODE_LEVEL  1	/* Leaf node level. */

/*
 * Given the buffer head of a क्रमmatted node, resolve to the
 * block head of that node.
 */
#घोषणा B_BLK_HEAD(bh)			((काष्ठा block_head *)((bh)->b_data))
/* Number of items that are in buffer. */
#घोषणा B_NR_ITEMS(bh)			(blkh_nr_item(B_BLK_HEAD(bh)))
#घोषणा B_LEVEL(bh)			(blkh_level(B_BLK_HEAD(bh)))
#घोषणा B_FREE_SPACE(bh)		(blkh_मुक्त_space(B_BLK_HEAD(bh)))

#घोषणा PUT_B_NR_ITEMS(bh, val)		करो अणु set_blkh_nr_item(B_BLK_HEAD(bh), val); पूर्ण जबतक (0)
#घोषणा PUT_B_LEVEL(bh, val)		करो अणु set_blkh_level(B_BLK_HEAD(bh), val); पूर्ण जबतक (0)
#घोषणा PUT_B_FREE_SPACE(bh, val)	करो अणु set_blkh_मुक्त_space(B_BLK_HEAD(bh), val); पूर्ण जबतक (0)

/* Get right delimiting key. -- little endian */
#घोषणा B_PRIGHT_DELIM_KEY(bh)		(&(blk_right_delim_key(B_BLK_HEAD(bh))))

/* Does the buffer contain a disk leaf. */
#घोषणा B_IS_ITEMS_LEVEL(bh)		(B_LEVEL(bh) == DISK_LEAF_NODE_LEVEL)

/* Does the buffer contain a disk पूर्णांकernal node */
#घोषणा B_IS_KEYS_LEVEL(bh)      (B_LEVEL(bh) > DISK_LEAF_NODE_LEVEL \
					    && B_LEVEL(bh) <= MAX_HEIGHT)

/***************************************************************************
 *                             STAT DATA                                   *
 ***************************************************************************/

/*
 * old stat data is 32 bytes दीर्घ. We are going to distinguish new one by
 * dअगरferent size
*/
काष्ठा stat_data_v1 अणु
	__le16 sd_mode;		/* file type, permissions */
	__le16 sd_nlink;	/* number of hard links */
	__le16 sd_uid;		/* owner */
	__le16 sd_gid;		/* group */
	__le32 sd_size;		/* file size */
	__le32 sd_aसमय;	/* समय of last access */
	__le32 sd_mसमय;	/* समय file was last modअगरied  */

	/*
	 * समय inode (stat data) was last changed
	 * (except changes to sd_aसमय and sd_mसमय)
	 */
	__le32 sd_स_समय;
	जोड़ अणु
		__le32 sd_rdev;
		__le32 sd_blocks;	/* number of blocks file uses */
	पूर्ण __attribute__ ((__packed__)) u;

	/*
	 * first byte of file which is stored in a direct item: except that अगर
	 * it equals 1 it is a symlink and अगर it equals ~(__u32)0 there is no
	 * direct item.  The existence of this field really grates on me.
	 * Let's replace it with a macro based on sd_size and our tail
	 * suppression policy.  Someday.  -Hans
	 */
	__le32 sd_first_direct_byte;
पूर्ण __attribute__ ((__packed__));

#घोषणा SD_V1_SIZE              (माप(काष्ठा stat_data_v1))
#घोषणा stat_data_v1(ih)        (ih_version (ih) == KEY_FORMAT_3_5)
#घोषणा sd_v1_mode(sdp)         (le16_to_cpu((sdp)->sd_mode))
#घोषणा set_sd_v1_mode(sdp,v)   ((sdp)->sd_mode = cpu_to_le16(v))
#घोषणा sd_v1_nlink(sdp)        (le16_to_cpu((sdp)->sd_nlink))
#घोषणा set_sd_v1_nlink(sdp,v)  ((sdp)->sd_nlink = cpu_to_le16(v))
#घोषणा sd_v1_uid(sdp)          (le16_to_cpu((sdp)->sd_uid))
#घोषणा set_sd_v1_uid(sdp,v)    ((sdp)->sd_uid = cpu_to_le16(v))
#घोषणा sd_v1_gid(sdp)          (le16_to_cpu((sdp)->sd_gid))
#घोषणा set_sd_v1_gid(sdp,v)    ((sdp)->sd_gid = cpu_to_le16(v))
#घोषणा sd_v1_size(sdp)         (le32_to_cpu((sdp)->sd_size))
#घोषणा set_sd_v1_size(sdp,v)   ((sdp)->sd_size = cpu_to_le32(v))
#घोषणा sd_v1_aसमय(sdp)        (le32_to_cpu((sdp)->sd_aसमय))
#घोषणा set_sd_v1_aसमय(sdp,v)  ((sdp)->sd_aसमय = cpu_to_le32(v))
#घोषणा sd_v1_mसमय(sdp)        (le32_to_cpu((sdp)->sd_mसमय))
#घोषणा set_sd_v1_mसमय(sdp,v)  ((sdp)->sd_mसमय = cpu_to_le32(v))
#घोषणा sd_v1_स_समय(sdp)        (le32_to_cpu((sdp)->sd_स_समय))
#घोषणा set_sd_v1_स_समय(sdp,v)  ((sdp)->sd_स_समय = cpu_to_le32(v))
#घोषणा sd_v1_rdev(sdp)         (le32_to_cpu((sdp)->u.sd_rdev))
#घोषणा set_sd_v1_rdev(sdp,v)   ((sdp)->u.sd_rdev = cpu_to_le32(v))
#घोषणा sd_v1_blocks(sdp)       (le32_to_cpu((sdp)->u.sd_blocks))
#घोषणा set_sd_v1_blocks(sdp,v) ((sdp)->u.sd_blocks = cpu_to_le32(v))
#घोषणा sd_v1_first_direct_byte(sdp) \
                                (le32_to_cpu((sdp)->sd_first_direct_byte))
#घोषणा set_sd_v1_first_direct_byte(sdp,v) \
                                ((sdp)->sd_first_direct_byte = cpu_to_le32(v))

/* inode flags stored in sd_attrs (nee sd_reserved) */

/*
 * we want common flags to have the same values as in ext2,
 * so chattr(1) will work without problems
 */
#घोषणा REISERFS_IMMUTABLE_FL FS_IMMUTABLE_FL
#घोषणा REISERFS_APPEND_FL    FS_APPEND_FL
#घोषणा REISERFS_SYNC_FL      FS_SYNC_FL
#घोषणा REISERFS_NOATIME_FL   FS_NOATIME_FL
#घोषणा REISERFS_NODUMP_FL    FS_NODUMP_FL
#घोषणा REISERFS_SECRM_FL     FS_SECRM_FL
#घोषणा REISERFS_UNRM_FL      FS_UNRM_FL
#घोषणा REISERFS_COMPR_FL     FS_COMPR_FL
#घोषणा REISERFS_NOTAIL_FL    FS_NOTAIL_FL

/* persistent flags that file inherits from the parent directory */
#घोषणा REISERFS_INHERIT_MASK ( REISERFS_IMMUTABLE_FL |	\
				REISERFS_SYNC_FL |	\
				REISERFS_NOATIME_FL |	\
				REISERFS_NODUMP_FL |	\
				REISERFS_SECRM_FL |	\
				REISERFS_COMPR_FL |	\
				REISERFS_NOTAIL_FL )

/*
 * Stat Data on disk (reiserfs version of UFS disk inode minus the
 * address blocks)
 */
काष्ठा stat_data अणु
	__le16 sd_mode;		/* file type, permissions */
	__le16 sd_attrs;	/* persistent inode flags */
	__le32 sd_nlink;	/* number of hard links */
	__le64 sd_size;		/* file size */
	__le32 sd_uid;		/* owner */
	__le32 sd_gid;		/* group */
	__le32 sd_aसमय;	/* समय of last access */
	__le32 sd_mसमय;	/* समय file was last modअगरied  */

	/*
	 * समय inode (stat data) was last changed
	 * (except changes to sd_aसमय and sd_mसमय)
	 */
	__le32 sd_स_समय;
	__le32 sd_blocks;
	जोड़ अणु
		__le32 sd_rdev;
		__le32 sd_generation;
	पूर्ण __attribute__ ((__packed__)) u;
पूर्ण __attribute__ ((__packed__));

/* this is 44 bytes दीर्घ */
#घोषणा SD_SIZE (माप(काष्ठा stat_data))
#घोषणा SD_V2_SIZE              SD_SIZE
#घोषणा stat_data_v2(ih)        (ih_version (ih) == KEY_FORMAT_3_6)
#घोषणा sd_v2_mode(sdp)         (le16_to_cpu((sdp)->sd_mode))
#घोषणा set_sd_v2_mode(sdp,v)   ((sdp)->sd_mode = cpu_to_le16(v))
/* sd_reserved */
/* set_sd_reserved */
#घोषणा sd_v2_nlink(sdp)        (le32_to_cpu((sdp)->sd_nlink))
#घोषणा set_sd_v2_nlink(sdp,v)  ((sdp)->sd_nlink = cpu_to_le32(v))
#घोषणा sd_v2_size(sdp)         (le64_to_cpu((sdp)->sd_size))
#घोषणा set_sd_v2_size(sdp,v)   ((sdp)->sd_size = cpu_to_le64(v))
#घोषणा sd_v2_uid(sdp)          (le32_to_cpu((sdp)->sd_uid))
#घोषणा set_sd_v2_uid(sdp,v)    ((sdp)->sd_uid = cpu_to_le32(v))
#घोषणा sd_v2_gid(sdp)          (le32_to_cpu((sdp)->sd_gid))
#घोषणा set_sd_v2_gid(sdp,v)    ((sdp)->sd_gid = cpu_to_le32(v))
#घोषणा sd_v2_aसमय(sdp)        (le32_to_cpu((sdp)->sd_aसमय))
#घोषणा set_sd_v2_aसमय(sdp,v)  ((sdp)->sd_aसमय = cpu_to_le32(v))
#घोषणा sd_v2_mसमय(sdp)        (le32_to_cpu((sdp)->sd_mसमय))
#घोषणा set_sd_v2_mसमय(sdp,v)  ((sdp)->sd_mसमय = cpu_to_le32(v))
#घोषणा sd_v2_स_समय(sdp)        (le32_to_cpu((sdp)->sd_स_समय))
#घोषणा set_sd_v2_स_समय(sdp,v)  ((sdp)->sd_स_समय = cpu_to_le32(v))
#घोषणा sd_v2_blocks(sdp)       (le32_to_cpu((sdp)->sd_blocks))
#घोषणा set_sd_v2_blocks(sdp,v) ((sdp)->sd_blocks = cpu_to_le32(v))
#घोषणा sd_v2_rdev(sdp)         (le32_to_cpu((sdp)->u.sd_rdev))
#घोषणा set_sd_v2_rdev(sdp,v)   ((sdp)->u.sd_rdev = cpu_to_le32(v))
#घोषणा sd_v2_generation(sdp)   (le32_to_cpu((sdp)->u.sd_generation))
#घोषणा set_sd_v2_generation(sdp,v) ((sdp)->u.sd_generation = cpu_to_le32(v))
#घोषणा sd_v2_attrs(sdp)         (le16_to_cpu((sdp)->sd_attrs))
#घोषणा set_sd_v2_attrs(sdp,v)   ((sdp)->sd_attrs = cpu_to_le16(v))

/***************************************************************************
 *                      सूचीECTORY STRUCTURE                                *
 ***************************************************************************/
/*
 * Picture represents the काष्ठाure of directory items
 * ________________________________________________
 * |  Array of     |   |     |        |       |   |
 * | directory     |N-1| N-2 | ....   |   1st |0th|
 * | entry headers |   |     |        |       |   |
 * |_______________|___|_____|________|_______|___|
 *                  <----   directory entries         ------>
 *
 * First directory item has k_offset component 1. We store "." and ".."
 * in one item, always, we never split "." and ".." पूर्णांकo dअगरfering
 * items.  This makes, among other things, the code क्रम removing
 * directories simpler.
 */
#घोषणा SD_OFFSET  0
#घोषणा SD_UNIQUENESS 0
#घोषणा DOT_OFFSET 1
#घोषणा DOT_DOT_OFFSET 2
#घोषणा सूचीENTRY_UNIQUENESS 500

#घोषणा FIRST_ITEM_OFFSET 1

/*
 * Q: How to get key of object poपूर्णांकed to by entry from entry?
 *
 * A: Each directory entry has its header. This header has deh_dir_id
 *    and deh_objectid fields, those are key of object, entry poपूर्णांकs to
 */

/*
 * NOT IMPLEMENTED:
 * Directory will someday contain stat data of object
 */

काष्ठा reiserfs_de_head अणु
	__le32 deh_offset;	/* third component of the directory entry key */

	/*
	 * objectid of the parent directory of the object, that is referenced
	 * by directory entry
	 */
	__le32 deh_dir_id;

	/* objectid of the object, that is referenced by directory entry */
	__le32 deh_objectid;
	__le16 deh_location;	/* offset of name in the whole item */

	/*
	 * whether 1) entry contains stat data (क्रम future), and
	 * 2) whether entry is hidden (unlinked)
	 */
	__le16 deh_state;
पूर्ण __attribute__ ((__packed__));
#घोषणा DEH_SIZE                  माप(काष्ठा reiserfs_de_head)
#घोषणा deh_offset(p_deh)         (le32_to_cpu((p_deh)->deh_offset))
#घोषणा deh_dir_id(p_deh)         (le32_to_cpu((p_deh)->deh_dir_id))
#घोषणा deh_objectid(p_deh)       (le32_to_cpu((p_deh)->deh_objectid))
#घोषणा deh_location(p_deh)       (le16_to_cpu((p_deh)->deh_location))
#घोषणा deh_state(p_deh)          (le16_to_cpu((p_deh)->deh_state))

#घोषणा put_deh_offset(p_deh,v)   ((p_deh)->deh_offset = cpu_to_le32((v)))
#घोषणा put_deh_dir_id(p_deh,v)   ((p_deh)->deh_dir_id = cpu_to_le32((v)))
#घोषणा put_deh_objectid(p_deh,v) ((p_deh)->deh_objectid = cpu_to_le32((v)))
#घोषणा put_deh_location(p_deh,v) ((p_deh)->deh_location = cpu_to_le16((v)))
#घोषणा put_deh_state(p_deh,v)    ((p_deh)->deh_state = cpu_to_le16((v)))

/* empty directory contains two entries "." and ".." and their headers */
#घोषणा EMPTY_सूची_SIZE \
(DEH_SIZE * 2 + ROUND_UP (माप(".") - 1) + ROUND_UP (माप("..") - 1))

/* old क्रमmat directories have this size when empty */
#घोषणा EMPTY_सूची_SIZE_V1 (DEH_SIZE * 2 + 3)

#घोषणा DEH_Statdata 0		/* not used now */
#घोषणा DEH_Visible 2

/* 64 bit प्रणालीs (and the S/390) need to be aligned explicitly -jdm */
#अगर BITS_PER_LONG == 64 || defined(__s390__) || defined(__hppa__)
#   define ADDR_UNALIGNED_BITS  (3)
#पूर्ण_अगर

/*
 * These are only used to manipulate deh_state.
 * Because of this, we'll use the ext2_ bit routines,
 * since they are little endian
 */
#अगर_घोषित ADDR_UNALIGNED_BITS

#   define aligned_address(addr)           ((व्योम *)((दीर्घ)(addr) & ~((1UL << ADDR_UNALIGNED_BITS) - 1)))
#   define unaligned_offset(addr)          (((पूर्णांक)((दीर्घ)(addr) & ((1 << ADDR_UNALIGNED_BITS) - 1))) << 3)

#   define set_bit_unaligned(nr, addr)	\
	__test_and_set_bit_le((nr) + unaligned_offset(addr), aligned_address(addr))
#   define clear_bit_unaligned(nr, addr)	\
	__test_and_clear_bit_le((nr) + unaligned_offset(addr), aligned_address(addr))
#   define test_bit_unaligned(nr, addr)	\
	test_bit_le((nr) + unaligned_offset(addr), aligned_address(addr))

#अन्यथा

#   define set_bit_unaligned(nr, addr)	__test_and_set_bit_le(nr, addr)
#   define clear_bit_unaligned(nr, addr)	__test_and_clear_bit_le(nr, addr)
#   define test_bit_unaligned(nr, addr)	test_bit_le(nr, addr)

#पूर्ण_अगर

#घोषणा mark_de_with_sd(deh)        set_bit_unaligned (DEH_Statdata, &((deh)->deh_state))
#घोषणा mark_de_without_sd(deh)     clear_bit_unaligned (DEH_Statdata, &((deh)->deh_state))
#घोषणा mark_de_visible(deh)	    set_bit_unaligned (DEH_Visible, &((deh)->deh_state))
#घोषणा mark_de_hidden(deh)	    clear_bit_unaligned (DEH_Visible, &((deh)->deh_state))

#घोषणा de_with_sd(deh)		    test_bit_unaligned (DEH_Statdata, &((deh)->deh_state))
#घोषणा de_visible(deh)	    	    test_bit_unaligned (DEH_Visible, &((deh)->deh_state))
#घोषणा de_hidden(deh)	    	    !test_bit_unaligned (DEH_Visible, &((deh)->deh_state))

बाह्य व्योम make_empty_dir_item_v1(अक्षर *body, __le32 dirid, __le32 objid,
				   __le32 par_dirid, __le32 par_objid);
बाह्य व्योम make_empty_dir_item(अक्षर *body, __le32 dirid, __le32 objid,
				__le32 par_dirid, __le32 par_objid);

/* two entries per block (at least) */
#घोषणा REISERFS_MAX_NAME(block_size) 255

/*
 * this काष्ठाure is used क्रम operations on directory entries. It is
 * not a disk काष्ठाure.
 *
 * When reiserfs_find_entry or search_by_entry_key find directory
 * entry, they वापस filled reiserfs_dir_entry काष्ठाure
 */
काष्ठा reiserfs_dir_entry अणु
	काष्ठा buffer_head *de_bh;
	पूर्णांक de_item_num;
	काष्ठा item_head *de_ih;
	पूर्णांक de_entry_num;
	काष्ठा reiserfs_de_head *de_deh;
	पूर्णांक de_entrylen;
	पूर्णांक de_namelen;
	अक्षर *de_name;
	अचिन्हित दीर्घ *de_gen_number_bit_string;

	__u32 de_dir_id;
	__u32 de_objectid;

	काष्ठा cpu_key de_entry_key;
पूर्ण;

/*
 * these defines are useful when a particular member of
 * a reiserfs_dir_entry is needed
 */

/* poपूर्णांकer to file name, stored in entry */
#घोषणा B_I_DEH_ENTRY_खाता_NAME(bh, ih, deh) \
				(ih_item_body(bh, ih) + deh_location(deh))

/* length of name */
#घोषणा I_DEH_N_ENTRY_खाता_NAME_LENGTH(ih,deh,entry_num) \
(I_DEH_N_ENTRY_LENGTH (ih, deh, entry_num) - (de_with_sd (deh) ? SD_SIZE : 0))

/* hash value occupies bits from 7 up to 30 */
#घोषणा GET_HASH_VALUE(offset) ((offset) & 0x7fffff80LL)
/* generation number occupies 7 bits starting from 0 up to 6 */
#घोषणा GET_GENERATION_NUMBER(offset) ((offset) & 0x7fLL)
#घोषणा MAX_GENERATION_NUMBER  127

#घोषणा SET_GENERATION_NUMBER(offset,gen_number) (GET_HASH_VALUE(offset)|(gen_number))

/*
 * Picture represents an पूर्णांकernal node of the reiserfs tree
 *  ______________________________________________________
 * |      |  Array of     |  Array of         |  Free     |
 * |block |    keys       |  poपूर्णांकers         | space     |
 * | head |      N        |      N+1          |           |
 * |______|_______________|___________________|___________|
 */

/***************************************************************************
 *                      DISK CHILD                                         *
 ***************************************************************************/
/*
 * Disk child poपूर्णांकer:
 * The poपूर्णांकer from an पूर्णांकernal node of the tree to a node that is on disk.
 */
काष्ठा disk_child अणु
	__le32 dc_block_number;	/* Disk child's block number. */
	__le16 dc_size;		/* Disk child's used space.   */
	__le16 dc_reserved;
पूर्ण;

#घोषणा DC_SIZE (माप(काष्ठा disk_child))
#घोषणा dc_block_number(dc_p)	(le32_to_cpu((dc_p)->dc_block_number))
#घोषणा dc_size(dc_p)		(le16_to_cpu((dc_p)->dc_size))
#घोषणा put_dc_block_number(dc_p, val)   करो अणु (dc_p)->dc_block_number = cpu_to_le32(val); पूर्ण जबतक(0)
#घोषणा put_dc_size(dc_p, val)   करो अणु (dc_p)->dc_size = cpu_to_le16(val); पूर्ण जबतक(0)

/* Get disk child by buffer header and position in the tree node. */
#घोषणा B_N_CHILD(bh, n_pos)  ((काष्ठा disk_child *)\
((bh)->b_data + BLKH_SIZE + B_NR_ITEMS(bh) * KEY_SIZE + DC_SIZE * (n_pos)))

/* Get disk child number by buffer header and position in the tree node. */
#घोषणा B_N_CHILD_NUM(bh, n_pos) (dc_block_number(B_N_CHILD(bh, n_pos)))
#घोषणा PUT_B_N_CHILD_NUM(bh, n_pos, val) \
				(put_dc_block_number(B_N_CHILD(bh, n_pos), val))

 /* maximal value of field child_size in काष्ठाure disk_child */
 /* child size is the combined size of all items and their headers */
#घोषणा MAX_CHILD_SIZE(bh) ((पूर्णांक)( (bh)->b_size - BLKH_SIZE ))

/* amount of used space in buffer (not including block head) */
#घोषणा B_CHILD_SIZE(cur) (MAX_CHILD_SIZE(cur)-(B_FREE_SPACE(cur)))

/* max and min number of keys in पूर्णांकernal node */
#घोषणा MAX_NR_KEY(bh) ( (MAX_CHILD_SIZE(bh)-DC_SIZE)/(KEY_SIZE+DC_SIZE) )
#घोषणा MIN_NR_KEY(bh)    (MAX_NR_KEY(bh)/2)

/***************************************************************************
 *                      PATH STRUCTURES AND DEFINES                        *
 ***************************************************************************/

/*
 * search_by_key fills up the path from the root to the leaf as it descends
 * the tree looking क्रम the key.  It uses reiserfs_bपढ़ो to try to find
 * buffers in the cache given their block number.  If it करोes not find
 * them in the cache it पढ़ोs them from disk.  For each node search_by_key
 * finds using reiserfs_bपढ़ो it then uses bin_search to look through that
 * node.  bin_search will find the position of the block_number of the next
 * node अगर it is looking through an पूर्णांकernal node.  If it is looking through
 * a leaf node bin_search will find the position of the item which has key
 * either equal to given key, or which is the maximal key less than the
 * given key.
 */

काष्ठा path_element अणु
	/* Poपूर्णांकer to the buffer at the path in the tree. */
	काष्ठा buffer_head *pe_buffer;
	/* Position in the tree node which is placed in the buffer above. */
	पूर्णांक pe_position;
पूर्ण;

/*
 * maximal height of a tree. करोn't change this without
 * changing JOURNAL_PER_BALANCE_CNT
 */
#घोषणा MAX_HEIGHT 5

/* Must be equals MAX_HEIGHT + FIRST_PATH_ELEMENT_OFFSET */
#घोषणा EXTENDED_MAX_HEIGHT         7

/* Must be equal to at least 2. */
#घोषणा FIRST_PATH_ELEMENT_OFFSET   2

/* Must be equal to FIRST_PATH_ELEMENT_OFFSET - 1 */
#घोषणा ILLEGAL_PATH_ELEMENT_OFFSET 1

/* this MUST be MAX_HEIGHT + 1. See about FEB below */
#घोषणा MAX_FEB_SIZE 6

/*
 * We need to keep track of who the ancestors of nodes are.  When we
 * perक्रमm a search we record which nodes were visited जबतक
 * descending the tree looking क्रम the node we searched क्रम. This list
 * of nodes is called the path.  This inक्रमmation is used जबतक
 * perक्रमming balancing.  Note that this path inक्रमmation may become
 * invalid, and this means we must check it when using it to see अगर it
 * is still valid. You'll need to पढ़ो search_by_key and the comments
 * in it, especially about decrement_counters_in_path(), to understand
 * this काष्ठाure.
 *
 * Paths make the code so much harder to work with and debug.... An
 * enormous number of bugs are due to them, and trying to ग_लिखो or modअगरy
 * code that uses them just makes my head hurt.  They are based on an
 * excessive efक्रमt to aव्योम disturbing the precious VFS code.:-( The
 * gods only know how we are going to SMP the code that uses them.
 * znodes are the way!
 */

#घोषणा PATH_READA	0x1	/* करो पढ़ो ahead */
#घोषणा PATH_READA_BACK 0x2	/* पढ़ो backwards */

काष्ठा treepath अणु
	पूर्णांक path_length;	/* Length of the array above.   */
	पूर्णांक पढ़ोa;
	/* Array of the path elements.  */
	काष्ठा path_element path_elements[EXTENDED_MAX_HEIGHT];
	पूर्णांक pos_in_item;
पूर्ण;

#घोषणा pos_in_item(path) ((path)->pos_in_item)

#घोषणा INITIALIZE_PATH(var) \
काष्ठा treepath var = अणु.path_length = ILLEGAL_PATH_ELEMENT_OFFSET, .पढ़ोa = 0,पूर्ण

/* Get path element by path and path position. */
#घोषणा PATH_OFFSET_PELEMENT(path, n_offset)  ((path)->path_elements + (n_offset))

/* Get buffer header at the path by path and path position. */
#घोषणा PATH_OFFSET_PBUFFER(path, n_offset)   (PATH_OFFSET_PELEMENT(path, n_offset)->pe_buffer)

/* Get position in the element at the path by path and path position. */
#घोषणा PATH_OFFSET_POSITION(path, n_offset) (PATH_OFFSET_PELEMENT(path, n_offset)->pe_position)

#घोषणा PATH_PLAST_BUFFER(path) (PATH_OFFSET_PBUFFER((path), (path)->path_length))

/*
 * you know, to the person who didn't ग_लिखो this the macro name करोes not
 * at first suggest what it करोes.  Maybe POSITION_FROM_PATH_END? Or
 * maybe we should just focus on dumping paths... -Hans
 */
#घोषणा PATH_LAST_POSITION(path) (PATH_OFFSET_POSITION((path), (path)->path_length))

/*
 * in करो_balance leaf has h == 0 in contrast with path काष्ठाure,
 * where root has level == 0. That is why we need these defines
 */

/* tb->S[h] */
#घोषणा PATH_H_PBUFFER(path, h) \
			PATH_OFFSET_PBUFFER(path, path->path_length - (h))

/* tb->F[h] or tb->S[0]->b_parent */
#घोषणा PATH_H_PPARENT(path, h) PATH_H_PBUFFER(path, (h) + 1)

#घोषणा PATH_H_POSITION(path, h) \
			PATH_OFFSET_POSITION(path, path->path_length - (h))

/* tb->S[h]->b_item_order */
#घोषणा PATH_H_B_ITEM_ORDER(path, h) PATH_H_POSITION(path, h + 1)

#घोषणा PATH_H_PATH_OFFSET(path, n_h) ((path)->path_length - (n_h))

अटल अंतरभूत व्योम *reiserfs_node_data(स्थिर काष्ठा buffer_head *bh)
अणु
	वापस bh->b_data + माप(काष्ठा block_head);
पूर्ण

/* get key from पूर्णांकernal node */
अटल अंतरभूत काष्ठा reiserfs_key *पूर्णांकernal_key(काष्ठा buffer_head *bh,
						पूर्णांक item_num)
अणु
	काष्ठा reiserfs_key *key = reiserfs_node_data(bh);

	वापस &key[item_num];
पूर्ण

/* get the item header from leaf node */
अटल अंतरभूत काष्ठा item_head *item_head(स्थिर काष्ठा buffer_head *bh,
					  पूर्णांक item_num)
अणु
	काष्ठा item_head *ih = reiserfs_node_data(bh);

	वापस &ih[item_num];
पूर्ण

/* get the key from leaf node */
अटल अंतरभूत काष्ठा reiserfs_key *leaf_key(स्थिर काष्ठा buffer_head *bh,
					    पूर्णांक item_num)
अणु
	वापस &item_head(bh, item_num)->ih_key;
पूर्ण

अटल अंतरभूत व्योम *ih_item_body(स्थिर काष्ठा buffer_head *bh,
				 स्थिर काष्ठा item_head *ih)
अणु
	वापस bh->b_data + ih_location(ih);
पूर्ण

/* get item body from leaf node */
अटल अंतरभूत व्योम *item_body(स्थिर काष्ठा buffer_head *bh, पूर्णांक item_num)
अणु
	वापस ih_item_body(bh, item_head(bh, item_num));
पूर्ण

अटल अंतरभूत काष्ठा item_head *tp_item_head(स्थिर काष्ठा treepath *path)
अणु
	वापस item_head(PATH_PLAST_BUFFER(path), PATH_LAST_POSITION(path));
पूर्ण

अटल अंतरभूत व्योम *tp_item_body(स्थिर काष्ठा treepath *path)
अणु
	वापस item_body(PATH_PLAST_BUFFER(path), PATH_LAST_POSITION(path));
पूर्ण

#घोषणा get_last_bh(path) PATH_PLAST_BUFFER(path)
#घोषणा get_item_pos(path) PATH_LAST_POSITION(path)
#घोषणा item_moved(ih,path) comp_items(ih, path)
#घोषणा path_changed(ih,path) comp_items (ih, path)

/* array of the entry headers */
 /* get item body */
#घोषणा B_I_DEH(bh, ih) ((काष्ठा reiserfs_de_head *)(ih_item_body(bh, ih)))

/*
 * length of the directory entry in directory item. This define
 * calculates length of i-th directory entry using directory entry
 * locations from dir entry head. When it calculates length of 0-th
 * directory entry, it uses length of whole item in place of entry
 * location of the non-existent following entry in the calculation.
 * See picture above.
 */
अटल अंतरभूत पूर्णांक entry_length(स्थिर काष्ठा buffer_head *bh,
			       स्थिर काष्ठा item_head *ih, पूर्णांक pos_in_item)
अणु
	काष्ठा reiserfs_de_head *deh;

	deh = B_I_DEH(bh, ih) + pos_in_item;
	अगर (pos_in_item)
		वापस deh_location(deh - 1) - deh_location(deh);

	वापस ih_item_len(ih) - deh_location(deh);
पूर्ण

/***************************************************************************
 *                       MISC                                              *
 ***************************************************************************/

/* Size of poपूर्णांकer to the unक्रमmatted node. */
#घोषणा UNFM_P_SIZE (माप(unp_t))
#घोषणा UNFM_P_SHIFT 2

/* in in-core inode key is stored on le क्रमm */
#घोषणा INODE_PKEY(inode) ((काष्ठा reiserfs_key *)(REISERFS_I(inode)->i_key))

#घोषणा MAX_UL_INT 0xffffffff
#घोषणा MAX_INT    0x7ffffff
#घोषणा MAX_US_INT 0xffff

// reiserfs version 2 has max offset 60 bits. Version 1 - 32 bit offset
अटल अंतरभूत loff_t max_reiserfs_offset(काष्ठा inode *inode)
अणु
	अगर (get_inode_item_key_version(inode) == KEY_FORMAT_3_5)
		वापस (loff_t) U32_MAX;

	वापस (loff_t) ((~(__u64) 0) >> 4);
पूर्ण

#घोषणा MAX_KEY_OBJECTID	MAX_UL_INT

#घोषणा MAX_B_NUM  MAX_UL_INT
#घोषणा MAX_FC_NUM MAX_US_INT

/* the purpose is to detect overflow of an अचिन्हित लघु */
#घोषणा REISERFS_LINK_MAX (MAX_US_INT - 1000)

/*
 * The following defines are used in reiserfs_insert_item
 * and reiserfs_append_item
 */
#घोषणा REISERFS_KERNEL_MEM		0	/* kernel memory mode */
#घोषणा REISERFS_USER_MEM		1	/* user memory mode */

#घोषणा fs_generation(s) (REISERFS_SB(s)->s_generation_counter)
#घोषणा get_generation(s) atomic_पढ़ो (&fs_generation(s))
#घोषणा खाताSYSTEM_CHANGED_TB(tb)  (get_generation((tb)->tb_sb) != (tb)->fs_gen)
#घोषणा __fs_changed(gen,s) (gen != get_generation (s))
#घोषणा fs_changed(gen,s)		\
(अणु					\
	reiserfs_cond_resched(s);	\
	__fs_changed(gen, s);		\
पूर्ण)

/***************************************************************************
 *                  FIXATE NODES                                           *
 ***************************************************************************/

#घोषणा VI_TYPE_LEFT_MERGEABLE 1
#घोषणा VI_TYPE_RIGHT_MERGEABLE 2

/*
 * To make any changes in the tree we always first find node, that
 * contains item to be changed/deleted or place to insert a new
 * item. We call this node S. To करो balancing we need to decide what
 * we will shअगरt to left/right neighbor, or to a new node, where new
 * item will be etc. To make this analysis simpler we build भव
 * node. Virtual node is an array of items, that will replace items of
 * node S. (For instance अगर we are going to delete an item, भव
 * node करोes not contain it). Virtual node keeps inक्रमmation about
 * item sizes and types, mergeability of first and last items, sizes
 * of all entries in directory item. We use this array of items when
 * calculating what we can shअगरt to neighbors and how many nodes we
 * have to have अगर we करो not any shअगरtings, अगर we shअगरt to left/right
 * neighbor or to both.
 */
काष्ठा भव_item अणु
	पूर्णांक vi_index;		/* index in the array of item operations */
	अचिन्हित लघु vi_type;	/* left/right mergeability */

	/* length of item that it will have after balancing */
	अचिन्हित लघु vi_item_len;

	काष्ठा item_head *vi_ih;
	स्थिर अक्षर *vi_item;	/* body of item (old or new) */
	स्थिर व्योम *vi_new_data;	/* 0 always but paste mode */
	व्योम *vi_uarea;		/* item specअगरic area */
पूर्ण;

काष्ठा भव_node अणु
	/* this is a poपूर्णांकer to the मुक्त space in the buffer */
	अक्षर *vn_मुक्त_ptr;

	अचिन्हित लघु vn_nr_item;	/* number of items in भव node */

	/*
	 * size of node , that node would have अगर it has
	 * unlimited size and no balancing is perक्रमmed
	 */
	लघु vn_size;

	/* mode of balancing (paste, insert, delete, cut) */
	लघु vn_mode;

	लघु vn_affected_item_num;
	लघु vn_pos_in_item;

	/* item header of inserted item, 0 क्रम other modes */
	काष्ठा item_head *vn_ins_ih;
	स्थिर व्योम *vn_data;

	/* array of items (including a new one, excluding item to be deleted) */
	काष्ठा भव_item *vn_vi;
पूर्ण;

/* used by directory items when creating भव nodes */
काष्ठा direntry_uarea अणु
	पूर्णांक flags;
	__u16 entry_count;
	__u16 entry_sizes[1];
पूर्ण __attribute__ ((__packed__));

/***************************************************************************
 *                  TREE BALANCE                                           *
 ***************************************************************************/

/*
 * This temporary काष्ठाure is used in tree balance algorithms, and
 * स्थिरructed as we go to the extent that its various parts are
 * needed.  It contains arrays of nodes that can potentially be
 * involved in the balancing of node S, and parameters that define how
 * each of the nodes must be balanced.  Note that in these algorithms
 * क्रम balancing the worst हाल is to need to balance the current node
 * S and the left and right neighbors and all of their parents plus
 * create a new node.  We implement S1 balancing क्रम the leaf nodes
 * and S0 balancing क्रम the पूर्णांकernal nodes (S1 and S0 are defined in
 * our papers.)
 */

/* size of the array of buffers to मुक्त at end of करो_balance */
#घोषणा MAX_FREE_BLOCK 7

/* maximum number of FEB blocknrs on a single level */
#घोषणा MAX_AMOUNT_NEEDED 2

/* someday somebody will prefix every field in this काष्ठा with tb_ */
काष्ठा tree_balance अणु
	पूर्णांक tb_mode;
	पूर्णांक need_balance_dirty;
	काष्ठा super_block *tb_sb;
	काष्ठा reiserfs_transaction_handle *transaction_handle;
	काष्ठा treepath *tb_path;

	/* array of left neighbors of nodes in the path */
	काष्ठा buffer_head *L[MAX_HEIGHT];

	/* array of right neighbors of nodes in the path */
	काष्ठा buffer_head *R[MAX_HEIGHT];

	/* array of fathers of the left neighbors */
	काष्ठा buffer_head *FL[MAX_HEIGHT];

	/* array of fathers of the right neighbors */
	काष्ठा buffer_head *FR[MAX_HEIGHT];
	/* array of common parents of center node and its left neighbor */
	काष्ठा buffer_head *CFL[MAX_HEIGHT];

	/* array of common parents of center node and its right neighbor */
	काष्ठा buffer_head *CFR[MAX_HEIGHT];

	/*
	 * array of empty buffers. Number of buffers in array equals
	 * cur_blknum.
	 */
	काष्ठा buffer_head *FEB[MAX_FEB_SIZE];
	काष्ठा buffer_head *used[MAX_FEB_SIZE];
	काष्ठा buffer_head *thrown[MAX_FEB_SIZE];

	/*
	 * array of number of items which must be shअगरted to the left in
	 * order to balance the current node; क्रम leaves includes item that
	 * will be partially shअगरted; क्रम पूर्णांकernal nodes, it is the number
	 * of child poपूर्णांकers rather than items. It includes the new item
	 * being created. The code someबार subtracts one to get the
	 * number of wholly shअगरted items क्रम other purposes.
	 */
	पूर्णांक lnum[MAX_HEIGHT];

	/* substitute right क्रम left in comment above */
	पूर्णांक rnum[MAX_HEIGHT];

	/*
	 * array indexed by height h mapping the key delimiting L[h] and
	 * S[h] to its item number within the node CFL[h]
	 */
	पूर्णांक lkey[MAX_HEIGHT];

	/* substitute r क्रम l in comment above */
	पूर्णांक rkey[MAX_HEIGHT];

	/*
	 * the number of bytes by we are trying to add or हटाओ from
	 * S[h]. A negative value means removing.
	 */
	पूर्णांक insert_size[MAX_HEIGHT];

	/*
	 * number of nodes that will replace node S[h] after balancing
	 * on the level h of the tree.  If 0 then S is being deleted,
	 * अगर 1 then S is reमुख्यing and no new nodes are being created,
	 * अगर 2 or 3 then 1 or 2 new nodes is being created
	 */
	पूर्णांक blknum[MAX_HEIGHT];

	/* fields that are used only क्रम balancing leaves of the tree */

	/* number of empty blocks having been alपढ़ोy allocated */
	पूर्णांक cur_blknum;

	/* number of items that fall पूर्णांकo left most node when S[0] splits */
	पूर्णांक s0num;

	/*
	 * number of bytes which can flow to the left neighbor from the left
	 * most liquid item that cannot be shअगरted from S[0] entirely
	 * अगर -1 then nothing will be partially shअगरted
	 */
	पूर्णांक lbytes;

	/*
	 * number of bytes which will flow to the right neighbor from the right
	 * most liquid item that cannot be shअगरted from S[0] entirely
	 * अगर -1 then nothing will be partially shअगरted
	 */
	पूर्णांक rbytes;


	/*
	 * index पूर्णांकo the array of item headers in
	 * S[0] of the affected item
	 */
	पूर्णांक item_pos;

	/* new nodes allocated to hold what could not fit पूर्णांकo S */
	काष्ठा buffer_head *S_new[2];

	/*
	 * number of items that will be placed पूर्णांकo nodes in S_new
	 * when S[0] splits
	 */
	पूर्णांक snum[2];

	/*
	 * number of bytes which flow to nodes in S_new when S[0] splits
	 * note: अगर S[0] splits पूर्णांकo 3 nodes, then items करो not need to be cut
	 */
	पूर्णांक sbytes[2];

	पूर्णांक pos_in_item;
	पूर्णांक zeroes_num;

	/*
	 * buffers which are to be मुक्तd after करो_balance finishes
	 * by unfix_nodes
	 */
	काष्ठा buffer_head *buf_to_मुक्त[MAX_FREE_BLOCK];

	/*
	 * kदो_स्मृतिed memory. Used to create भव node and keep
	 * map of dirtied biपंचांगap blocks
	 */
	अक्षर *vn_buf;

	पूर्णांक vn_buf_size;	/* size of the vn_buf */

	/* VN starts after biपंचांगap of biपंचांगap blocks */
	काष्ठा भव_node *tb_vn;

	/*
	 * saved value of `reiserfs_generation' counter see
	 * खाताSYSTEM_CHANGED() macro in reiserfs_fs.h
	 */
	पूर्णांक fs_gen;

#अगर_घोषित DISPLACE_NEW_PACKING_LOCALITIES
	/*
	 * key poपूर्णांकer, to pass to block allocator or
	 * another low-level subप्रणाली
	 */
	काष्ठा in_core_key key;
#पूर्ण_अगर
पूर्ण;

/* These are modes of balancing */

/* When inserting an item. */
#घोषणा M_INSERT	'i'
/*
 * When inserting पूर्णांकo (directories only) or appending onto an alपढ़ोy
 * existent item.
 */
#घोषणा M_PASTE		'p'
/* When deleting an item. */
#घोषणा M_DELETE	'd'
/* When truncating an item or removing an entry from a (directory) item. */
#घोषणा M_CUT		'c'

/* used when balancing on leaf level skipped (in reiserfsck) */
#घोषणा M_INTERNAL	'n'

/*
 * When further balancing is not needed, then करो_balance करोes not need
 * to be called.
 */
#घोषणा M_SKIP_BALANCING		's'
#घोषणा M_CONVERT	'v'

/* modes of leaf_move_items */
#घोषणा LEAF_FROM_S_TO_L 0
#घोषणा LEAF_FROM_S_TO_R 1
#घोषणा LEAF_FROM_R_TO_L 2
#घोषणा LEAF_FROM_L_TO_R 3
#घोषणा LEAF_FROM_S_TO_SNEW 4

#घोषणा FIRST_TO_LAST 0
#घोषणा LAST_TO_FIRST 1

/*
 * used in करो_balance क्रम passing parent of node inक्रमmation that has
 * been gotten from tb काष्ठा
 */
काष्ठा buffer_info अणु
	काष्ठा tree_balance *tb;
	काष्ठा buffer_head *bi_bh;
	काष्ठा buffer_head *bi_parent;
	पूर्णांक bi_position;
पूर्ण;

अटल अंतरभूत काष्ठा super_block *sb_from_tb(काष्ठा tree_balance *tb)
अणु
	वापस tb ? tb->tb_sb : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा super_block *sb_from_bi(काष्ठा buffer_info *bi)
अणु
	वापस bi ? sb_from_tb(bi->tb) : शून्य;
पूर्ण

/*
 * there are 4 types of items: stat data, directory item, indirect, direct.
 * +-------------------+------------+--------------+------------+
 * |                   |  k_offset  | k_uniqueness | mergeable? |
 * +-------------------+------------+--------------+------------+
 * |     stat data     |     0      |      0       |   no       |
 * +-------------------+------------+--------------+------------+
 * | 1st directory item| DOT_OFFSET | सूचीENTRY_ .. |   no       |
 * | non 1st directory | hash value | UNIQUENESS   |   yes      |
 * |     item          |            |              |            |
 * +-------------------+------------+--------------+------------+
 * | indirect item     | offset + 1 |TYPE_INसूचीECT |    [1]	|
 * +-------------------+------------+--------------+------------+
 * | direct item       | offset + 1 |TYPE_सूचीECT   |    [2]     |
 * +-------------------+------------+--------------+------------+
 *
 * [1] अगर this is not the first indirect item of the object
 * [2] अगर this is not the first direct item of the object
*/

काष्ठा item_operations अणु
	पूर्णांक (*bytes_number) (काष्ठा item_head * ih, पूर्णांक block_size);
	व्योम (*decrement_key) (काष्ठा cpu_key *);
	पूर्णांक (*is_left_mergeable) (काष्ठा reiserfs_key * ih,
				  अचिन्हित दीर्घ bsize);
	व्योम (*prपूर्णांक_item) (काष्ठा item_head *, अक्षर *item);
	व्योम (*check_item) (काष्ठा item_head *, अक्षर *item);

	पूर्णांक (*create_vi) (काष्ठा भव_node * vn, काष्ठा भव_item * vi,
			  पूर्णांक is_affected, पूर्णांक insert_size);
	पूर्णांक (*check_left) (काष्ठा भव_item * vi, पूर्णांक मुक्त,
			   पूर्णांक start_skip, पूर्णांक end_skip);
	पूर्णांक (*check_right) (काष्ठा भव_item * vi, पूर्णांक मुक्त);
	पूर्णांक (*part_size) (काष्ठा भव_item * vi, पूर्णांक from, पूर्णांक to);
	पूर्णांक (*unit_num) (काष्ठा भव_item * vi);
	व्योम (*prपूर्णांक_vi) (काष्ठा भव_item * vi);
पूर्ण;

बाह्य काष्ठा item_operations *item_ops[TYPE_ANY + 1];

#घोषणा op_bytes_number(ih,bsize)                    item_ops[le_ih_k_type (ih)]->bytes_number (ih, bsize)
#घोषणा op_is_left_mergeable(key,bsize)              item_ops[le_key_k_type (le_key_version (key), key)]->is_left_mergeable (key, bsize)
#घोषणा op_prपूर्णांक_item(ih,item)                       item_ops[le_ih_k_type (ih)]->prपूर्णांक_item (ih, item)
#घोषणा op_check_item(ih,item)                       item_ops[le_ih_k_type (ih)]->check_item (ih, item)
#घोषणा op_create_vi(vn,vi,is_affected,insert_size)  item_ops[le_ih_k_type ((vi)->vi_ih)]->create_vi (vn,vi,is_affected,insert_size)
#घोषणा op_check_left(vi,मुक्त,start_skip,end_skip) item_ops[(vi)->vi_index]->check_left (vi, मुक्त, start_skip, end_skip)
#घोषणा op_check_right(vi,मुक्त)                      item_ops[(vi)->vi_index]->check_right (vi, मुक्त)
#घोषणा op_part_size(vi,from,to)                     item_ops[(vi)->vi_index]->part_size (vi, from, to)
#घोषणा op_unit_num(vi)				     item_ops[(vi)->vi_index]->unit_num (vi)
#घोषणा op_prपूर्णांक_vi(vi)                              item_ops[(vi)->vi_index]->prपूर्णांक_vi (vi)

#घोषणा COMP_SHORT_KEYS comp_लघु_keys

/* number of blocks poपूर्णांकed to by the indirect item */
#घोषणा I_UNFM_NUM(ih)	(ih_item_len(ih) / UNFM_P_SIZE)

/*
 * the used space within the unक्रमmatted node corresponding
 * to pos within the item poपूर्णांकed to by ih
 */
#घोषणा I_POS_UNFM_SIZE(ih,pos,size) (((pos) == I_UNFM_NUM(ih) - 1 ) ? (size) - ih_मुक्त_space(ih) : (size))

/*
 * number of bytes contained by the direct item or the
 * unक्रमmatted nodes the indirect item poपूर्णांकs to
 */

/* following defines use reiserfs buffer header and item header */

/* get stat-data */
#घोषणा B_I_STAT_DATA(bh, ih) ( (काष्ठा stat_data * )((bh)->b_data + ih_location(ih)) )

/* this is 3976 क्रम size==4096 */
#घोषणा MAX_सूचीECT_ITEM_LEN(size) ((size) - BLKH_SIZE - 2*IH_SIZE - SD_SIZE - UNFM_P_SIZE)

/*
 * indirect items consist of entries which contain blocknrs, pos
 * indicates which entry, and B_I_POS_UNFM_POINTER resolves to the
 * blocknr contained by the entry pos poपूर्णांकs to
 */
#घोषणा B_I_POS_UNFM_POINTER(bh, ih, pos)				\
	le32_to_cpu(*(((unp_t *)ih_item_body(bh, ih)) + (pos)))
#घोषणा PUT_B_I_POS_UNFM_POINTER(bh, ih, pos, val)			\
	(*(((unp_t *)ih_item_body(bh, ih)) + (pos)) = cpu_to_le32(val))

काष्ठा reiserfs_iget_args अणु
	__u32 objectid;
	__u32 dirid;
पूर्ण;

/***************************************************************************
 *                    FUNCTION DECLARATIONS                                *
 ***************************************************************************/

#घोषणा get_journal_desc_magic(bh) (bh->b_data + bh->b_size - 12)

#घोषणा journal_trans_half(blocksize) \
	((blocksize - माप (काष्ठा reiserfs_journal_desc) + माप (__u32) - 12) / माप (__u32))

/* journal.c see journal.c क्रम all the comments here */

/* first block written in a commit.  */
काष्ठा reiserfs_journal_desc अणु
	__le32 j_trans_id;	/* id of commit */

	/* length of commit. len +1 is the commit block */
	__le32 j_len;

	__le32 j_mount_id;	/* mount id of this trans */
	__le32 j_realblock[1];	/* real locations क्रम each block */
पूर्ण;

#घोषणा get_desc_trans_id(d)   le32_to_cpu((d)->j_trans_id)
#घोषणा get_desc_trans_len(d)  le32_to_cpu((d)->j_len)
#घोषणा get_desc_mount_id(d)   le32_to_cpu((d)->j_mount_id)

#घोषणा set_desc_trans_id(d,val)       करो अणु (d)->j_trans_id = cpu_to_le32 (val); पूर्ण जबतक (0)
#घोषणा set_desc_trans_len(d,val)      करो अणु (d)->j_len = cpu_to_le32 (val); पूर्ण जबतक (0)
#घोषणा set_desc_mount_id(d,val)       करो अणु (d)->j_mount_id = cpu_to_le32 (val); पूर्ण जबतक (0)

/* last block written in a commit */
काष्ठा reiserfs_journal_commit अणु
	__le32 j_trans_id;	/* must match j_trans_id from the desc block */
	__le32 j_len;		/* ditto */
	__le32 j_realblock[1];	/* real locations क्रम each block */
पूर्ण;

#घोषणा get_commit_trans_id(c) le32_to_cpu((c)->j_trans_id)
#घोषणा get_commit_trans_len(c)        le32_to_cpu((c)->j_len)
#घोषणा get_commit_mount_id(c) le32_to_cpu((c)->j_mount_id)

#घोषणा set_commit_trans_id(c,val)     करो अणु (c)->j_trans_id = cpu_to_le32 (val); पूर्ण जबतक (0)
#घोषणा set_commit_trans_len(c,val)    करो अणु (c)->j_len = cpu_to_le32 (val); पूर्ण जबतक (0)

/*
 * this header block माला_लो written whenever a transaction is considered
 * fully flushed, and is more recent than the last fully flushed transaction.
 * fully flushed means all the log blocks and all the real blocks are on
 * disk, and this transaction करोes not need to be replayed.
 */
काष्ठा reiserfs_journal_header अणु
	/* id of last fully flushed transaction */
	__le32 j_last_flush_trans_id;

	/* offset in the log of where to start replay after a crash */
	__le32 j_first_unflushed_offset;

	__le32 j_mount_id;
	/* 12 */ काष्ठा journal_params jh_journal;
पूर्ण;

/* biggest tunable defines are right here */
#घोषणा JOURNAL_BLOCK_COUNT 8192	/* number of blocks in the journal */

/* biggest possible single transaction, करोn't change क्रम now (8/3/99) */
#घोषणा JOURNAL_TRANS_MAX_DEFAULT 1024
#घोषणा JOURNAL_TRANS_MIN_DEFAULT 256

/*
 * max blocks to batch पूर्णांकo one transaction,
 * करोn't make this any bigger than 900
 */
#घोषणा JOURNAL_MAX_BATCH_DEFAULT   900
#घोषणा JOURNAL_MIN_RATIO 2
#घोषणा JOURNAL_MAX_COMMIT_AGE 30
#घोषणा JOURNAL_MAX_TRANS_AGE 30
#घोषणा JOURNAL_PER_BALANCE_CNT (3 * (MAX_HEIGHT-2) + 9)
#घोषणा JOURNAL_BLOCKS_PER_OBJECT(sb)  (JOURNAL_PER_BALANCE_CNT * 3 + \
					 2 * (REISERFS_QUOTA_INIT_BLOCKS(sb) + \
					      REISERFS_QUOTA_TRANS_BLOCKS(sb)))

#अगर_घोषित CONFIG_QUOTA
#घोषणा REISERFS_QUOTA_OPTS ((1 << REISERFS_USRQUOTA) | (1 << REISERFS_GRPQUOTA))
/* We need to update data and inode (aसमय) */
#घोषणा REISERFS_QUOTA_TRANS_BLOCKS(s) (REISERFS_SB(s)->s_mount_opt & REISERFS_QUOTA_OPTS ? 2 : 0)
/* 1 balancing, 1 biपंचांगap, 1 data per ग_लिखो + stat data update */
#घोषणा REISERFS_QUOTA_INIT_BLOCKS(s) (REISERFS_SB(s)->s_mount_opt & REISERFS_QUOTA_OPTS ? \
(DQUOT_INIT_ALLOC*(JOURNAL_PER_BALANCE_CNT+2)+DQUOT_INIT_REWRITE+1) : 0)
/* same as with INIT */
#घोषणा REISERFS_QUOTA_DEL_BLOCKS(s) (REISERFS_SB(s)->s_mount_opt & REISERFS_QUOTA_OPTS ? \
(DQUOT_DEL_ALLOC*(JOURNAL_PER_BALANCE_CNT+2)+DQUOT_DEL_REWRITE+1) : 0)
#अन्यथा
#घोषणा REISERFS_QUOTA_TRANS_BLOCKS(s) 0
#घोषणा REISERFS_QUOTA_INIT_BLOCKS(s) 0
#घोषणा REISERFS_QUOTA_DEL_BLOCKS(s) 0
#पूर्ण_अगर

/*
 * both of these can be as low as 1, or as high as you want.  The min is the
 * number of 4k biपंचांगap nodes pपुनः_स्मृतिated on mount. New nodes are allocated
 * as needed, and released when transactions are committed.  On release, अगर
 * the current number of nodes is > max, the node is मुक्तd, otherwise,
 * it is put on a मुक्त list क्रम faster use later.
*/
#घोषणा REISERFS_MIN_BITMAP_NODES 10
#घोषणा REISERFS_MAX_BITMAP_NODES 100

/* these are based on journal hash size of 8192 */
#घोषणा JBH_HASH_SHIFT 13
#घोषणा JBH_HASH_MASK 8191

#घोषणा _jhashfn(sb,block)	\
	(((अचिन्हित दीर्घ)sb>>L1_CACHE_SHIFT) ^ \
	 (((block)<<(JBH_HASH_SHIFT - 6)) ^ ((block) >> 13) ^ ((block) << (JBH_HASH_SHIFT - 12))))
#घोषणा journal_hash(t,sb,block) ((t)[_jhashfn((sb),(block)) & JBH_HASH_MASK])

/* We need these to make journal.c code more पढ़ोable */
#घोषणा journal_find_get_block(s, block) __find_get_block(SB_JOURNAL(s)->j_dev_bd, block, s->s_blocksize)
#घोषणा journal_getblk(s, block) __getblk(SB_JOURNAL(s)->j_dev_bd, block, s->s_blocksize)
#घोषणा journal_bपढ़ो(s, block) __bपढ़ो(SB_JOURNAL(s)->j_dev_bd, block, s->s_blocksize)

क्रमागत reiserfs_bh_state_bits अणु
	BH_JDirty = BH_PrivateStart,	/* buffer is in current transaction */
	BH_JDirty_रुको,
	/*
	 * disk block was taken off मुक्त list beक्रमe being in a
	 * finished transaction, or written to disk. Can be reused immed.
	 */
	BH_JNew,
	BH_JPrepared,
	BH_JRestore_dirty,
	BH_JTest,		/* debugging only will go away */
पूर्ण;

BUFFER_FNS(JDirty, journaled);
TAS_BUFFER_FNS(JDirty, journaled);
BUFFER_FNS(JDirty_रुको, journal_dirty);
TAS_BUFFER_FNS(JDirty_रुको, journal_dirty);
BUFFER_FNS(JNew, journal_new);
TAS_BUFFER_FNS(JNew, journal_new);
BUFFER_FNS(JPrepared, journal_prepared);
TAS_BUFFER_FNS(JPrepared, journal_prepared);
BUFFER_FNS(JRestore_dirty, journal_restore_dirty);
TAS_BUFFER_FNS(JRestore_dirty, journal_restore_dirty);
BUFFER_FNS(JTest, journal_test);
TAS_BUFFER_FNS(JTest, journal_test);

/* transaction handle which is passed around क्रम all journal calls */
काष्ठा reiserfs_transaction_handle अणु
	/*
	 * super क्रम this FS when journal_begin was called. saves calls to
	 * reiserfs_get_super also used by nested transactions to make
	 * sure they are nesting on the right FS _must_ be first
	 * in the handle
	 */
	काष्ठा super_block *t_super;

	पूर्णांक t_refcount;
	पूर्णांक t_blocks_logged;	/* number of blocks this ग_लिखोr has logged */
	पूर्णांक t_blocks_allocated;	/* number of blocks this ग_लिखोr allocated */

	/* sanity check, equals the current trans id */
	अचिन्हित पूर्णांक t_trans_id;

	व्योम *t_handle_save;	/* save existing current->journal_info */

	/*
	 * अगर new block allocation occurres, that block
	 * should be displaced from others
	 */
	अचिन्हित displace_new_blocks:1;

	काष्ठा list_head t_list;
पूर्ण;

/*
 * used to keep track of ordered and tail ग_लिखोs, attached to the buffer
 * head through b_journal_head.
 */
काष्ठा reiserfs_jh अणु
	काष्ठा reiserfs_journal_list *jl;
	काष्ठा buffer_head *bh;
	काष्ठा list_head list;
पूर्ण;

व्योम reiserfs_मुक्त_jh(काष्ठा buffer_head *bh);
पूर्णांक reiserfs_add_tail_list(काष्ठा inode *inode, काष्ठा buffer_head *bh);
पूर्णांक reiserfs_add_ordered_list(काष्ठा inode *inode, काष्ठा buffer_head *bh);
पूर्णांक journal_mark_dirty(काष्ठा reiserfs_transaction_handle *,
		       काष्ठा buffer_head *bh);

अटल अंतरभूत पूर्णांक reiserfs_file_data_log(काष्ठा inode *inode)
अणु
	अगर (reiserfs_data_log(inode->i_sb) ||
	    (REISERFS_I(inode)->i_flags & i_data_log))
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक reiserfs_transaction_running(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_transaction_handle *th = current->journal_info;
	अगर (th && th->t_super == s)
		वापस 1;
	अगर (th && th->t_super == शून्य)
		BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक reiserfs_transaction_मुक्त_space(काष्ठा reiserfs_transaction_handle *th)
अणु
	वापस th->t_blocks_allocated - th->t_blocks_logged;
पूर्ण

काष्ठा reiserfs_transaction_handle *reiserfs_persistent_transaction(काष्ठा
								    super_block
								    *,
								    पूर्णांक count);
पूर्णांक reiserfs_end_persistent_transaction(काष्ठा reiserfs_transaction_handle *);
व्योम reiserfs_vfs_truncate_file(काष्ठा inode *inode);
पूर्णांक reiserfs_commit_page(काष्ठा inode *inode, काष्ठा page *page,
			 अचिन्हित from, अचिन्हित to);
व्योम reiserfs_flush_old_commits(काष्ठा super_block *);
पूर्णांक reiserfs_commit_क्रम_inode(काष्ठा inode *);
पूर्णांक reiserfs_inode_needs_commit(काष्ठा inode *);
व्योम reiserfs_update_inode_transaction(काष्ठा inode *);
व्योम reiserfs_रुको_on_ग_लिखो_block(काष्ठा super_block *s);
व्योम reiserfs_block_ग_लिखोs(काष्ठा reiserfs_transaction_handle *th);
व्योम reiserfs_allow_ग_लिखोs(काष्ठा super_block *s);
व्योम reiserfs_check_lock_depth(काष्ठा super_block *s, अक्षर *caller);
पूर्णांक reiserfs_prepare_क्रम_journal(काष्ठा super_block *, काष्ठा buffer_head *bh,
				 पूर्णांक रुको);
व्योम reiserfs_restore_prepared_buffer(काष्ठा super_block *,
				      काष्ठा buffer_head *bh);
पूर्णांक journal_init(काष्ठा super_block *, स्थिर अक्षर *j_dev_name, पूर्णांक old_क्रमmat,
		 अचिन्हित पूर्णांक);
पूर्णांक journal_release(काष्ठा reiserfs_transaction_handle *, काष्ठा super_block *);
पूर्णांक journal_release_error(काष्ठा reiserfs_transaction_handle *,
			  काष्ठा super_block *);
पूर्णांक journal_end(काष्ठा reiserfs_transaction_handle *);
पूर्णांक journal_end_sync(काष्ठा reiserfs_transaction_handle *);
पूर्णांक journal_mark_मुक्तd(काष्ठा reiserfs_transaction_handle *,
		       काष्ठा super_block *, b_blocknr_t blocknr);
पूर्णांक journal_transaction_should_end(काष्ठा reiserfs_transaction_handle *, पूर्णांक);
पूर्णांक reiserfs_in_journal(काष्ठा super_block *sb, अचिन्हित पूर्णांक bmap_nr,
			 पूर्णांक bit_nr, पूर्णांक searchall, b_blocknr_t *next);
पूर्णांक journal_begin(काष्ठा reiserfs_transaction_handle *,
		  काष्ठा super_block *sb, अचिन्हित दीर्घ);
पूर्णांक journal_join_पात(काष्ठा reiserfs_transaction_handle *,
		       काष्ठा super_block *sb);
व्योम reiserfs_पात_journal(काष्ठा super_block *sb, पूर्णांक त्रुटि_सं);
व्योम reiserfs_पात(काष्ठा super_block *sb, पूर्णांक त्रुटि_सं, स्थिर अक्षर *fmt, ...);
पूर्णांक reiserfs_allocate_list_biपंचांगaps(काष्ठा super_block *s,
				   काष्ठा reiserfs_list_biपंचांगap *, अचिन्हित पूर्णांक);

व्योम reiserfs_schedule_old_flush(काष्ठा super_block *s);
व्योम reiserfs_cancel_old_flush(काष्ठा super_block *s);
व्योम add_save_link(काष्ठा reiserfs_transaction_handle *th,
		   काष्ठा inode *inode, पूर्णांक truncate);
पूर्णांक हटाओ_save_link(काष्ठा inode *inode, पूर्णांक truncate);

/* objectid.c */
__u32 reiserfs_get_unused_objectid(काष्ठा reiserfs_transaction_handle *th);
व्योम reiserfs_release_objectid(काष्ठा reiserfs_transaction_handle *th,
			       __u32 objectid_to_release);
पूर्णांक reiserfs_convert_objectid_map_v1(काष्ठा super_block *);

/* stree.c */
पूर्णांक B_IS_IN_TREE(स्थिर काष्ठा buffer_head *);
बाह्य व्योम copy_item_head(काष्ठा item_head *to,
			   स्थिर काष्ठा item_head *from);

/* first key is in cpu क्रमm, second - le */
बाह्य पूर्णांक comp_लघु_keys(स्थिर काष्ठा reiserfs_key *le_key,
			   स्थिर काष्ठा cpu_key *cpu_key);
बाह्य व्योम le_key2cpu_key(काष्ठा cpu_key *to, स्थिर काष्ठा reiserfs_key *from);

/* both are in le क्रमm */
बाह्य पूर्णांक comp_le_keys(स्थिर काष्ठा reiserfs_key *,
			स्थिर काष्ठा reiserfs_key *);
बाह्य पूर्णांक comp_लघु_le_keys(स्थिर काष्ठा reiserfs_key *,
			      स्थिर काष्ठा reiserfs_key *);

/* * get key version from on disk key - kludge */
अटल अंतरभूत पूर्णांक le_key_version(स्थिर काष्ठा reiserfs_key *key)
अणु
	पूर्णांक type;

	type = offset_v2_k_type(&(key->u.k_offset_v2));
	अगर (type != TYPE_सूचीECT && type != TYPE_INसूचीECT
	    && type != TYPE_सूचीENTRY)
		वापस KEY_FORMAT_3_5;

	वापस KEY_FORMAT_3_6;

पूर्ण

अटल अंतरभूत व्योम copy_key(काष्ठा reiserfs_key *to,
			    स्थिर काष्ठा reiserfs_key *from)
अणु
	स_नकल(to, from, KEY_SIZE);
पूर्ण

पूर्णांक comp_items(स्थिर काष्ठा item_head *stored_ih, स्थिर काष्ठा treepath *path);
स्थिर काष्ठा reiserfs_key *get_rkey(स्थिर काष्ठा treepath *chk_path,
				    स्थिर काष्ठा super_block *sb);
पूर्णांक search_by_key(काष्ठा super_block *, स्थिर काष्ठा cpu_key *,
		  काष्ठा treepath *, पूर्णांक);
#घोषणा search_item(s,key,path) search_by_key (s, key, path, DISK_LEAF_NODE_LEVEL)
पूर्णांक search_क्रम_position_by_key(काष्ठा super_block *sb,
			       स्थिर काष्ठा cpu_key *cpu_key,
			       काष्ठा treepath *search_path);
बाह्य व्योम decrement_bcount(काष्ठा buffer_head *bh);
व्योम decrement_counters_in_path(काष्ठा treepath *search_path);
व्योम pathrअन्यथा(काष्ठा treepath *search_path);
पूर्णांक reiserfs_check_path(काष्ठा treepath *p);
व्योम pathrअन्यथा_and_restore(काष्ठा super_block *s, काष्ठा treepath *search_path);

पूर्णांक reiserfs_insert_item(काष्ठा reiserfs_transaction_handle *th,
			 काष्ठा treepath *path,
			 स्थिर काष्ठा cpu_key *key,
			 काष्ठा item_head *ih,
			 काष्ठा inode *inode, स्थिर अक्षर *body);

पूर्णांक reiserfs_paste_पूर्णांकo_item(काष्ठा reiserfs_transaction_handle *th,
			     काष्ठा treepath *path,
			     स्थिर काष्ठा cpu_key *key,
			     काष्ठा inode *inode,
			     स्थिर अक्षर *body, पूर्णांक paste_size);

पूर्णांक reiserfs_cut_from_item(काष्ठा reiserfs_transaction_handle *th,
			   काष्ठा treepath *path,
			   काष्ठा cpu_key *key,
			   काष्ठा inode *inode,
			   काष्ठा page *page, loff_t new_file_size);

पूर्णांक reiserfs_delete_item(काष्ठा reiserfs_transaction_handle *th,
			 काष्ठा treepath *path,
			 स्थिर काष्ठा cpu_key *key,
			 काष्ठा inode *inode, काष्ठा buffer_head *un_bh);

व्योम reiserfs_delete_solid_item(काष्ठा reiserfs_transaction_handle *th,
				काष्ठा inode *inode, काष्ठा reiserfs_key *key);
पूर्णांक reiserfs_delete_object(काष्ठा reiserfs_transaction_handle *th,
			   काष्ठा inode *inode);
पूर्णांक reiserfs_करो_truncate(काष्ठा reiserfs_transaction_handle *th,
			 काष्ठा inode *inode, काष्ठा page *,
			 पूर्णांक update_बारtamps);

#घोषणा i_block_size(inode) ((inode)->i_sb->s_blocksize)
#घोषणा file_size(inode) ((inode)->i_size)
#घोषणा tail_size(inode) (file_size (inode) & (i_block_size (inode) - 1))

#घोषणा tail_has_to_be_packed(inode) (have_large_tails ((inode)->i_sb)?\
!STORE_TAIL_IN_UNFM_S1(file_size (inode), tail_size(inode), inode->i_sb->s_blocksize):have_small_tails ((inode)->i_sb)?!STORE_TAIL_IN_UNFM_S2(file_size (inode), tail_size(inode), inode->i_sb->s_blocksize):0 )

व्योम padd_item(अक्षर *item, पूर्णांक total_length, पूर्णांक length);

/* inode.c */
/* args क्रम the create parameter of reiserfs_get_block */
#घोषणा GET_BLOCK_NO_CREATE 0	 /* करोn't create new blocks or convert tails */
#घोषणा GET_BLOCK_CREATE 1	 /* add anything you need to find block */
#घोषणा GET_BLOCK_NO_HOLE 2	 /* वापस -ENOENT क्रम file holes */
#घोषणा GET_BLOCK_READ_सूचीECT 4	 /* पढ़ो the tail अगर indirect item not found */
#घोषणा GET_BLOCK_NO_IMUX     8	 /* i_mutex is not held, करोn't pपुनः_स्मृतिate */
#घोषणा GET_BLOCK_NO_DANGLE   16 /* करोn't leave any transactions running */

व्योम reiserfs_पढ़ो_locked_inode(काष्ठा inode *inode,
				काष्ठा reiserfs_iget_args *args);
पूर्णांक reiserfs_find_actor(काष्ठा inode *inode, व्योम *p);
पूर्णांक reiserfs_init_locked_inode(काष्ठा inode *inode, व्योम *p);
व्योम reiserfs_evict_inode(काष्ठा inode *inode);
पूर्णांक reiserfs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc);
पूर्णांक reiserfs_get_block(काष्ठा inode *inode, sector_t block,
		       काष्ठा buffer_head *bh_result, पूर्णांक create);
काष्ठा dentry *reiserfs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
				     पूर्णांक fh_len, पूर्णांक fh_type);
काष्ठा dentry *reiserfs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
				     पूर्णांक fh_len, पूर्णांक fh_type);
पूर्णांक reiserfs_encode_fh(काष्ठा inode *inode, __u32 * data, पूर्णांक *lenp,
		       काष्ठा inode *parent);

पूर्णांक reiserfs_truncate_file(काष्ठा inode *, पूर्णांक update_बारtamps);
व्योम make_cpu_key(काष्ठा cpu_key *cpu_key, काष्ठा inode *inode, loff_t offset,
		  पूर्णांक type, पूर्णांक key_length);
व्योम make_le_item_head(काष्ठा item_head *ih, स्थिर काष्ठा cpu_key *key,
		       पूर्णांक version,
		       loff_t offset, पूर्णांक type, पूर्णांक length, पूर्णांक entry_count);
काष्ठा inode *reiserfs_iget(काष्ठा super_block *s, स्थिर काष्ठा cpu_key *key);

काष्ठा reiserfs_security_handle;
पूर्णांक reiserfs_new_inode(काष्ठा reiserfs_transaction_handle *th,
		       काष्ठा inode *dir, umode_t mode,
		       स्थिर अक्षर *symname, loff_t i_size,
		       काष्ठा dentry *dentry, काष्ठा inode *inode,
		       काष्ठा reiserfs_security_handle *security);

व्योम reiserfs_update_sd_size(काष्ठा reiserfs_transaction_handle *th,
			     काष्ठा inode *inode, loff_t size);

अटल अंतरभूत व्योम reiserfs_update_sd(काष्ठा reiserfs_transaction_handle *th,
				      काष्ठा inode *inode)
अणु
	reiserfs_update_sd_size(th, inode, inode->i_size);
पूर्ण

व्योम sd_attrs_to_i_attrs(__u16 sd_attrs, काष्ठा inode *inode);
पूर्णांक reiserfs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		     काष्ठा iattr *attr);

पूर्णांक __reiserfs_ग_लिखो_begin(काष्ठा page *page, अचिन्हित from, अचिन्हित len);

/* namei.c */
व्योम set_de_name_and_namelen(काष्ठा reiserfs_dir_entry *de);
पूर्णांक search_by_entry_key(काष्ठा super_block *sb, स्थिर काष्ठा cpu_key *key,
			काष्ठा treepath *path, काष्ठा reiserfs_dir_entry *de);
काष्ठा dentry *reiserfs_get_parent(काष्ठा dentry *);

#अगर_घोषित CONFIG_REISERFS_PROC_INFO
पूर्णांक reiserfs_proc_info_init(काष्ठा super_block *sb);
पूर्णांक reiserfs_proc_info_करोne(काष्ठा super_block *sb);
पूर्णांक reiserfs_proc_info_global_init(व्योम);
पूर्णांक reiserfs_proc_info_global_करोne(व्योम);

#घोषणा PROC_EXP( e )   e

#घोषणा __PINFO( sb ) REISERFS_SB(sb) -> s_proc_info_data
#घोषणा PROC_INFO_MAX( sb, field, value )								\
    __PINFO( sb ).field =												\
        max( REISERFS_SB( sb ) -> s_proc_info_data.field, value )
#घोषणा PROC_INFO_INC( sb, field ) ( ++ ( __PINFO( sb ).field ) )
#घोषणा PROC_INFO_ADD( sb, field, val ) ( __PINFO( sb ).field += ( val ) )
#घोषणा PROC_INFO_BH_STAT( sb, bh, level )							\
    PROC_INFO_INC( sb, sbk_पढ़ो_at[ ( level ) ] );						\
    PROC_INFO_ADD( sb, मुक्त_at[ ( level ) ], B_FREE_SPACE( bh ) );	\
    PROC_INFO_ADD( sb, items_at[ ( level ) ], B_NR_ITEMS( bh ) )
#अन्यथा
अटल अंतरभूत पूर्णांक reiserfs_proc_info_init(काष्ठा super_block *sb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक reiserfs_proc_info_करोne(काष्ठा super_block *sb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक reiserfs_proc_info_global_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक reiserfs_proc_info_global_करोne(व्योम)
अणु
	वापस 0;
पूर्ण

#घोषणा PROC_EXP( e )
#घोषणा VOID_V ( ( व्योम ) 0 )
#घोषणा PROC_INFO_MAX( sb, field, value ) VOID_V
#घोषणा PROC_INFO_INC( sb, field ) VOID_V
#घोषणा PROC_INFO_ADD( sb, field, val ) VOID_V
#घोषणा PROC_INFO_BH_STAT(sb, bh, n_node_level) VOID_V
#पूर्ण_अगर

/* dir.c */
बाह्य स्थिर काष्ठा inode_operations reiserfs_dir_inode_operations;
बाह्य स्थिर काष्ठा inode_operations reiserfs_symlink_inode_operations;
बाह्य स्थिर काष्ठा inode_operations reiserfs_special_inode_operations;
बाह्य स्थिर काष्ठा file_operations reiserfs_dir_operations;
पूर्णांक reiserfs_सूची_पढ़ो_inode(काष्ठा inode *, काष्ठा dir_context *);

/* tail_conversion.c */
पूर्णांक direct2indirect(काष्ठा reiserfs_transaction_handle *, काष्ठा inode *,
		    काष्ठा treepath *, काष्ठा buffer_head *, loff_t);
पूर्णांक indirect2direct(काष्ठा reiserfs_transaction_handle *, काष्ठा inode *,
		    काष्ठा page *, काष्ठा treepath *, स्थिर काष्ठा cpu_key *,
		    loff_t, अक्षर *);
व्योम reiserfs_unmap_buffer(काष्ठा buffer_head *);

/* file.c */
बाह्य स्थिर काष्ठा inode_operations reiserfs_file_inode_operations;
बाह्य स्थिर काष्ठा file_operations reiserfs_file_operations;
बाह्य स्थिर काष्ठा address_space_operations reiserfs_address_space_operations;

/* fix_nodes.c */

पूर्णांक fix_nodes(पूर्णांक n_op_mode, काष्ठा tree_balance *tb,
	      काष्ठा item_head *ins_ih, स्थिर व्योम *);
व्योम unfix_nodes(काष्ठा tree_balance *);

/* prपूर्णांकs.c */
व्योम __reiserfs_panic(काष्ठा super_block *s, स्थिर अक्षर *id,
		      स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...)
    __attribute__ ((noवापस));
#घोषणा reiserfs_panic(s, id, fmt, args...) \
	__reiserfs_panic(s, id, __func__, fmt, ##args)
व्योम __reiserfs_error(काष्ठा super_block *s, स्थिर अक्षर *id,
		      स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...);
#घोषणा reiserfs_error(s, id, fmt, args...) \
	 __reiserfs_error(s, id, __func__, fmt, ##args)
व्योम reiserfs_info(काष्ठा super_block *s, स्थिर अक्षर *fmt, ...);
व्योम reiserfs_debug(काष्ठा super_block *s, पूर्णांक level, स्थिर अक्षर *fmt, ...);
व्योम prपूर्णांक_indirect_item(काष्ठा buffer_head *bh, पूर्णांक item_num);
व्योम store_prपूर्णांक_tb(काष्ठा tree_balance *tb);
व्योम prपूर्णांक_cur_tb(अक्षर *mes);
व्योम prपूर्णांक_de(काष्ठा reiserfs_dir_entry *de);
व्योम prपूर्णांक_bi(काष्ठा buffer_info *bi, अक्षर *mes);
#घोषणा PRINT_LEAF_ITEMS 1	/* prपूर्णांक all items */
#घोषणा PRINT_सूचीECTORY_ITEMS 2	/* prपूर्णांक directory items */
#घोषणा PRINT_सूचीECT_ITEMS 4	/* prपूर्णांक contents of direct items */
व्योम prपूर्णांक_block(काष्ठा buffer_head *bh, ...);
व्योम prपूर्णांक_bmap(काष्ठा super_block *s, पूर्णांक silent);
व्योम prपूर्णांक_bmap_block(पूर्णांक i, अक्षर *data, पूर्णांक size, पूर्णांक silent);
/*व्योम prपूर्णांक_super_block (काष्ठा super_block * s, अक्षर * mes);*/
व्योम prपूर्णांक_objectid_map(काष्ठा super_block *s);
व्योम prपूर्णांक_block_head(काष्ठा buffer_head *bh, अक्षर *mes);
व्योम check_leaf(काष्ठा buffer_head *bh);
व्योम check_पूर्णांकernal(काष्ठा buffer_head *bh);
व्योम prपूर्णांक_statistics(काष्ठा super_block *s);
अक्षर *reiserfs_hashname(पूर्णांक code);

/* lbalance.c */
पूर्णांक leaf_move_items(पूर्णांक shअगरt_mode, काष्ठा tree_balance *tb, पूर्णांक mov_num,
		    पूर्णांक mov_bytes, काष्ठा buffer_head *Snew);
पूर्णांक leaf_shअगरt_left(काष्ठा tree_balance *tb, पूर्णांक shअगरt_num, पूर्णांक shअगरt_bytes);
पूर्णांक leaf_shअगरt_right(काष्ठा tree_balance *tb, पूर्णांक shअगरt_num, पूर्णांक shअगरt_bytes);
व्योम leaf_delete_items(काष्ठा buffer_info *cur_bi, पूर्णांक last_first, पूर्णांक first,
		       पूर्णांक del_num, पूर्णांक del_bytes);
व्योम leaf_insert_पूर्णांकo_buf(काष्ठा buffer_info *bi, पूर्णांक beक्रमe,
			  काष्ठा item_head * स्थिर inserted_item_ih,
			  स्थिर अक्षर * स्थिर inserted_item_body,
			  पूर्णांक zeros_number);
व्योम leaf_paste_in_buffer(काष्ठा buffer_info *bi, पूर्णांक pasted_item_num,
			  पूर्णांक pos_in_item, पूर्णांक paste_size,
			  स्थिर अक्षर * स्थिर body, पूर्णांक zeros_number);
व्योम leaf_cut_from_buffer(काष्ठा buffer_info *bi, पूर्णांक cut_item_num,
			  पूर्णांक pos_in_item, पूर्णांक cut_size);
व्योम leaf_paste_entries(काष्ठा buffer_info *bi, पूर्णांक item_num, पूर्णांक beक्रमe,
			पूर्णांक new_entry_count, काष्ठा reiserfs_de_head *new_dehs,
			स्थिर अक्षर *records, पूर्णांक paste_size);
/* ibalance.c */
पूर्णांक balance_पूर्णांकernal(काष्ठा tree_balance *, पूर्णांक, पूर्णांक, काष्ठा item_head *,
		     काष्ठा buffer_head **);

/* करो_balance.c */
व्योम करो_balance_mark_leaf_dirty(काष्ठा tree_balance *tb,
				काष्ठा buffer_head *bh, पूर्णांक flag);
#घोषणा करो_balance_mark_पूर्णांकernal_dirty करो_balance_mark_leaf_dirty
#घोषणा करो_balance_mark_sb_dirty करो_balance_mark_leaf_dirty

व्योम करो_balance(काष्ठा tree_balance *tb, काष्ठा item_head *ih,
		स्थिर अक्षर *body, पूर्णांक flag);
व्योम reiserfs_invalidate_buffer(काष्ठा tree_balance *tb,
				काष्ठा buffer_head *bh);

पूर्णांक get_left_neighbor_position(काष्ठा tree_balance *tb, पूर्णांक h);
पूर्णांक get_right_neighbor_position(काष्ठा tree_balance *tb, पूर्णांक h);
व्योम replace_key(काष्ठा tree_balance *tb, काष्ठा buffer_head *, पूर्णांक,
		 काष्ठा buffer_head *, पूर्णांक);
व्योम make_empty_node(काष्ठा buffer_info *);
काष्ठा buffer_head *get_FEB(काष्ठा tree_balance *);

/* biपंचांगap.c */

/*
 * काष्ठाure contains hपूर्णांकs क्रम block allocator, and it is a container क्रम
 * arguments, such as node, search path, transaction_handle, etc.
 */
काष्ठा __reiserfs_blocknr_hपूर्णांक अणु
	/* inode passed to allocator, अगर we allocate unf. nodes */
	काष्ठा inode *inode;

	sector_t block;		/* file offset, in blocks */
	काष्ठा in_core_key key;

	/*
	 * search path, used by allocator to deternine search_start by
	 * various ways
	 */
	काष्ठा treepath *path;

	/*
	 * transaction handle is needed to log super blocks
	 * and biपंचांगap blocks changes
	 */
	काष्ठा reiserfs_transaction_handle *th;

	b_blocknr_t beg, end;

	/*
	 * a field used to transfer search start value (block number)
	 * between dअगरferent block allocator procedures
	 * (determine_search_start() and others)
	 */
	b_blocknr_t search_start;

	/*
	 * is set in determine_pपुनः_स्मृति_size() function,
	 * used by underlayed function that करो actual allocation
	 */
	पूर्णांक pपुनः_स्मृति_size;

	/*
	 * the allocator uses dअगरferent polices क्रम getting disk
	 * space क्रम क्रमmatted/unक्रमmatted blocks with/without pपुनः_स्मृतिation
	 */
	अचिन्हित क्रमmatted_node:1;
	अचिन्हित pपुनः_स्मृतिate:1;
पूर्ण;

प्रकार काष्ठा __reiserfs_blocknr_hपूर्णांक reiserfs_blocknr_hपूर्णांक_t;

पूर्णांक reiserfs_parse_alloc_options(काष्ठा super_block *, अक्षर *);
व्योम reiserfs_init_alloc_options(काष्ठा super_block *s);

/*
 * given a directory, this will tell you what packing locality
 * to use क्रम a new object underneat it.  The locality is वापसed
 * in disk byte order (le).
 */
__le32 reiserfs_choose_packing(काष्ठा inode *dir);

व्योम show_alloc_options(काष्ठा seq_file *seq, काष्ठा super_block *s);
पूर्णांक reiserfs_init_biपंचांगap_cache(काष्ठा super_block *sb);
व्योम reiserfs_मुक्त_biपंचांगap_cache(काष्ठा super_block *sb);
व्योम reiserfs_cache_biपंचांगap_metadata(काष्ठा super_block *sb, काष्ठा buffer_head *bh, काष्ठा reiserfs_biपंचांगap_info *info);
काष्ठा buffer_head *reiserfs_पढ़ो_biपंचांगap_block(काष्ठा super_block *sb, अचिन्हित पूर्णांक biपंचांगap);
पूर्णांक is_reusable(काष्ठा super_block *s, b_blocknr_t block, पूर्णांक bit_value);
व्योम reiserfs_मुक्त_block(काष्ठा reiserfs_transaction_handle *th, काष्ठा inode *,
			 b_blocknr_t, पूर्णांक क्रम_unक्रमmatted);
पूर्णांक reiserfs_allocate_blocknrs(reiserfs_blocknr_hपूर्णांक_t *, b_blocknr_t *, पूर्णांक,
			       पूर्णांक);
अटल अंतरभूत पूर्णांक reiserfs_new_क्रमm_blocknrs(काष्ठा tree_balance *tb,
					     b_blocknr_t * new_blocknrs,
					     पूर्णांक amount_needed)
अणु
	reiserfs_blocknr_hपूर्णांक_t hपूर्णांक = अणु
		.th = tb->transaction_handle,
		.path = tb->tb_path,
		.inode = शून्य,
		.key = tb->key,
		.block = 0,
		.क्रमmatted_node = 1
	पूर्ण;
	वापस reiserfs_allocate_blocknrs(&hपूर्णांक, new_blocknrs, amount_needed,
					  0);
पूर्ण

अटल अंतरभूत पूर्णांक reiserfs_new_unf_blocknrs(काष्ठा reiserfs_transaction_handle
					    *th, काष्ठा inode *inode,
					    b_blocknr_t * new_blocknrs,
					    काष्ठा treepath *path,
					    sector_t block)
अणु
	reiserfs_blocknr_hपूर्णांक_t hपूर्णांक = अणु
		.th = th,
		.path = path,
		.inode = inode,
		.block = block,
		.क्रमmatted_node = 0,
		.pपुनः_स्मृतिate = 0
	पूर्ण;
	वापस reiserfs_allocate_blocknrs(&hपूर्णांक, new_blocknrs, 1, 0);
पूर्ण

#अगर_घोषित REISERFS_PREALLOCATE
अटल अंतरभूत पूर्णांक reiserfs_new_unf_blocknrs2(काष्ठा reiserfs_transaction_handle
					     *th, काष्ठा inode *inode,
					     b_blocknr_t * new_blocknrs,
					     काष्ठा treepath *path,
					     sector_t block)
अणु
	reiserfs_blocknr_hपूर्णांक_t hपूर्णांक = अणु
		.th = th,
		.path = path,
		.inode = inode,
		.block = block,
		.क्रमmatted_node = 0,
		.pपुनः_स्मृतिate = 1
	पूर्ण;
	वापस reiserfs_allocate_blocknrs(&hपूर्णांक, new_blocknrs, 1, 0);
पूर्ण

व्योम reiserfs_discard_pपुनः_स्मृति(काष्ठा reiserfs_transaction_handle *th,
			       काष्ठा inode *inode);
व्योम reiserfs_discard_all_pपुनः_स्मृति(काष्ठा reiserfs_transaction_handle *th);
#पूर्ण_अगर

/* hashes.c */
__u32 keyed_hash(स्थिर चिन्हित अक्षर *msg, पूर्णांक len);
__u32 yura_hash(स्थिर चिन्हित अक्षर *msg, पूर्णांक len);
__u32 r5_hash(स्थिर चिन्हित अक्षर *msg, पूर्णांक len);

#घोषणा reiserfs_set_le_bit		__set_bit_le
#घोषणा reiserfs_test_and_set_le_bit	__test_and_set_bit_le
#घोषणा reiserfs_clear_le_bit		__clear_bit_le
#घोषणा reiserfs_test_and_clear_le_bit	__test_and_clear_bit_le
#घोषणा reiserfs_test_le_bit		test_bit_le
#घोषणा reiserfs_find_next_zero_le_bit	find_next_zero_bit_le

/*
 * someबार reiserfs_truncate may require to allocate few new blocks
 * to perक्रमm indirect2direct conversion. People probably used to
 * think, that truncate should work without problems on a fileप्रणाली
 * without मुक्त disk space. They may complain that they can not
 * truncate due to lack of मुक्त disk space. This spare space allows us
 * to not worry about it. 500 is probably too much, but it should be
 * असलolutely safe
 */
#घोषणा SPARE_SPACE 500

/* prototypes from ioctl.c */
पूर्णांक reiserfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्णांक reiserfs_fileattr_set(काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, काष्ठा fileattr *fa);
दीर्घ reiserfs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ reiserfs_compat_ioctl(काष्ठा file *filp,
		   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक reiserfs_unpack(काष्ठा inode *inode);
