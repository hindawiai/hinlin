<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs/f2fs/f2fs.h
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#अगर_अघोषित _LINUX_F2FS_H
#घोषणा _LINUX_F2FS_H

#समावेश <linux/uपन.स>
#समावेश <linux/types.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc32.h>
#समावेश <linux/magic.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/part_स्थिति.स>
#समावेश <crypto/hash.h>

#समावेश <linux/fscrypt.h>
#समावेश <linux/fsverity.h>

#अगर_घोषित CONFIG_F2FS_CHECK_FS
#घोषणा f2fs_bug_on(sbi, condition)	BUG_ON(condition)
#अन्यथा
#घोषणा f2fs_bug_on(sbi, condition)					\
	करो अणु								\
		अगर (WARN_ON(condition))					\
			set_sbi_flag(sbi, SBI_NEED_FSCK);		\
	पूर्ण जबतक (0)
#पूर्ण_अगर

क्रमागत अणु
	FAULT_KMALLOC,
	FAULT_KVMALLOC,
	FAULT_PAGE_ALLOC,
	FAULT_PAGE_GET,
	FAULT_ALLOC_NID,
	FAULT_ORPHAN,
	FAULT_BLOCK,
	FAULT_सूची_DEPTH,
	FAULT_EVICT_INODE,
	FAULT_TRUNCATE,
	FAULT_READ_IO,
	FAULT_CHECKPOINT,
	FAULT_DISCARD,
	FAULT_WRITE_IO,
	FAULT_MAX,
पूर्ण;

#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
#घोषणा F2FS_ALL_FAULT_TYPE		((1 << FAULT_MAX) - 1)

काष्ठा f2fs_fault_info अणु
	atomic_t inject_ops;
	अचिन्हित पूर्णांक inject_rate;
	अचिन्हित पूर्णांक inject_type;
पूर्ण;

बाह्य स्थिर अक्षर *f2fs_fault_name[FAULT_MAX];
#घोषणा IS_FAULT_SET(fi, type) ((fi)->inject_type & (1 << (type)))
#पूर्ण_अगर

/*
 * For mount options
 */
#घोषणा F2FS_MOUNT_DISABLE_ROLL_FORWARD	0x00000002
#घोषणा F2FS_MOUNT_DISCARD		0x00000004
#घोषणा F2FS_MOUNT_NOHEAP		0x00000008
#घोषणा F2FS_MOUNT_XATTR_USER		0x00000010
#घोषणा F2FS_MOUNT_POSIX_ACL		0x00000020
#घोषणा F2FS_MOUNT_DISABLE_EXT_IDENTIFY	0x00000040
#घोषणा F2FS_MOUNT_INLINE_XATTR		0x00000080
#घोषणा F2FS_MOUNT_INLINE_DATA		0x00000100
#घोषणा F2FS_MOUNT_INLINE_DENTRY	0x00000200
#घोषणा F2FS_MOUNT_FLUSH_MERGE		0x00000400
#घोषणा F2FS_MOUNT_NOBARRIER		0x00000800
#घोषणा F2FS_MOUNT_FASTBOOT		0x00001000
#घोषणा F2FS_MOUNT_EXTENT_CACHE		0x00002000
#घोषणा F2FS_MOUNT_DATA_FLUSH		0x00008000
#घोषणा F2FS_MOUNT_FAULT_INJECTION	0x00010000
#घोषणा F2FS_MOUNT_USRQUOTA		0x00080000
#घोषणा F2FS_MOUNT_GRPQUOTA		0x00100000
#घोषणा F2FS_MOUNT_PRJQUOTA		0x00200000
#घोषणा F2FS_MOUNT_QUOTA		0x00400000
#घोषणा F2FS_MOUNT_INLINE_XATTR_SIZE	0x00800000
#घोषणा F2FS_MOUNT_RESERVE_ROOT		0x01000000
#घोषणा F2FS_MOUNT_DISABLE_CHECKPOINT	0x02000000
#घोषणा F2FS_MOUNT_NORECOVERY		0x04000000
#घोषणा F2FS_MOUNT_ATGC			0x08000000
#घोषणा F2FS_MOUNT_MERGE_CHECKPOINT	0x10000000
#घोषणा	F2FS_MOUNT_GC_MERGE		0x20000000

#घोषणा F2FS_OPTION(sbi)	((sbi)->mount_opt)
#घोषणा clear_opt(sbi, option)	(F2FS_OPTION(sbi).opt &= ~F2FS_MOUNT_##option)
#घोषणा set_opt(sbi, option)	(F2FS_OPTION(sbi).opt |= F2FS_MOUNT_##option)
#घोषणा test_opt(sbi, option)	(F2FS_OPTION(sbi).opt & F2FS_MOUNT_##option)

#घोषणा ver_after(a, b)	(typecheck(अचिन्हित दीर्घ दीर्घ, a) &&		\
		typecheck(अचिन्हित दीर्घ दीर्घ, b) &&			\
		((दीर्घ दीर्घ)((a) - (b)) > 0))

प्रकार u32 block_t;	/*
			 * should not change u32, since it is the on-disk block
			 * address क्रमmat, __le32.
			 */
प्रकार u32 nid_t;

#घोषणा COMPRESS_EXT_NUM		16

काष्ठा f2fs_mount_info अणु
	अचिन्हित पूर्णांक opt;
	पूर्णांक ग_लिखो_io_size_bits;		/* Write IO size bits */
	block_t root_reserved_blocks;	/* root reserved blocks */
	kuid_t s_resuid;		/* reserved blocks क्रम uid */
	kgid_t s_resgid;		/* reserved blocks क्रम gid */
	पूर्णांक active_logs;		/* # of active logs */
	पूर्णांक अंतरभूत_xattr_size;		/* अंतरभूत xattr size */
#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
	काष्ठा f2fs_fault_info fault_info;	/* For fault injection */
#पूर्ण_अगर
#अगर_घोषित CONFIG_QUOTA
	/* Names of quota files with journalled quota */
	अक्षर *s_qf_names[MAXQUOTAS];
	पूर्णांक s_jquota_fmt;			/* Format of quota to use */
#पूर्ण_अगर
	/* For which ग_लिखो hपूर्णांकs are passed करोwn to block layer */
	पूर्णांक whपूर्णांक_mode;
	पूर्णांक alloc_mode;			/* segment allocation policy */
	पूर्णांक fsync_mode;			/* fsync policy */
	पूर्णांक fs_mode;			/* fs mode: LFS or ADAPTIVE */
	पूर्णांक bggc_mode;			/* bggc mode: off, on or sync */
	काष्ठा fscrypt_dummy_policy dummy_enc_policy; /* test dummy encryption */
	block_t unusable_cap_perc;	/* percentage क्रम cap */
	block_t unusable_cap;		/* Amount of space allowed to be
					 * unusable when disabling checkpoपूर्णांक
					 */

	/* For compression */
	अचिन्हित अक्षर compress_algorithm;	/* algorithm type */
	अचिन्हित अक्षर compress_log_size;	/* cluster log size */
	अचिन्हित अक्षर compress_level;		/* compress level */
	bool compress_chksum;			/* compressed data chksum */
	अचिन्हित अक्षर compress_ext_cnt;		/* extension count */
	पूर्णांक compress_mode;			/* compression mode */
	अचिन्हित अक्षर extensions[COMPRESS_EXT_NUM][F2FS_EXTENSION_LEN];	/* extensions */
पूर्ण;

#घोषणा F2FS_FEATURE_ENCRYPT		0x0001
#घोषणा F2FS_FEATURE_BLKZONED		0x0002
#घोषणा F2FS_FEATURE_ATOMIC_WRITE	0x0004
#घोषणा F2FS_FEATURE_EXTRA_ATTR		0x0008
#घोषणा F2FS_FEATURE_PRJQUOTA		0x0010
#घोषणा F2FS_FEATURE_INODE_CHKSUM	0x0020
#घोषणा F2FS_FEATURE_FLEXIBLE_INLINE_XATTR	0x0040
#घोषणा F2FS_FEATURE_QUOTA_INO		0x0080
#घोषणा F2FS_FEATURE_INODE_CRTIME	0x0100
#घोषणा F2FS_FEATURE_LOST_FOUND		0x0200
#घोषणा F2FS_FEATURE_VERITY		0x0400
#घोषणा F2FS_FEATURE_SB_CHKSUM		0x0800
#घोषणा F2FS_FEATURE_CASEFOLD		0x1000
#घोषणा F2FS_FEATURE_COMPRESSION	0x2000

#घोषणा __F2FS_HAS_FEATURE(raw_super, mask)				\
	((raw_super->feature & cpu_to_le32(mask)) != 0)
#घोषणा F2FS_HAS_FEATURE(sbi, mask)	__F2FS_HAS_FEATURE(sbi->raw_super, mask)
#घोषणा F2FS_SET_FEATURE(sbi, mask)					\
	(sbi->raw_super->feature |= cpu_to_le32(mask))
#घोषणा F2FS_CLEAR_FEATURE(sbi, mask)					\
	(sbi->raw_super->feature &= ~cpu_to_le32(mask))

/*
 * Default values क्रम user and/or group using reserved blocks
 */
#घोषणा	F2FS_DEF_RESUID		0
#घोषणा	F2FS_DEF_RESGID		0

/*
 * For checkpoपूर्णांक manager
 */
क्रमागत अणु
	NAT_BITMAP,
	SIT_BITMAP
पूर्ण;

#घोषणा	CP_UMOUNT	0x00000001
#घोषणा	CP_FASTBOOT	0x00000002
#घोषणा	CP_SYNC		0x00000004
#घोषणा	CP_RECOVERY	0x00000008
#घोषणा	CP_DISCARD	0x00000010
#घोषणा CP_TRIMMED	0x00000020
#घोषणा CP_PAUSE	0x00000040
#घोषणा CP_RESIZE 	0x00000080

#घोषणा MAX_DISCARD_BLOCKS(sbi)		BLKS_PER_SEC(sbi)
#घोषणा DEF_MAX_DISCARD_REQUEST		8	/* issue 8 discards per round */
#घोषणा DEF_MIN_DISCARD_ISSUE_TIME	50	/* 50 ms, अगर exists */
#घोषणा DEF_MID_DISCARD_ISSUE_TIME	500	/* 500 ms, अगर device busy */
#घोषणा DEF_MAX_DISCARD_ISSUE_TIME	60000	/* 60 s, अगर no candidates */
#घोषणा DEF_DISCARD_URGENT_UTIL		80	/* करो more discard over 80% */
#घोषणा DEF_CP_INTERVAL			60	/* 60 secs */
#घोषणा DEF_IDLE_INTERVAL		5	/* 5 secs */
#घोषणा DEF_DISABLE_INTERVAL		5	/* 5 secs */
#घोषणा DEF_DISABLE_QUICK_INTERVAL	1	/* 1 secs */
#घोषणा DEF_UMOUNT_DISCARD_TIMEOUT	5	/* 5 secs */

काष्ठा cp_control अणु
	पूर्णांक reason;
	__u64 trim_start;
	__u64 trim_end;
	__u64 trim_minlen;
पूर्ण;

/*
 * indicate meta/data type
 */
क्रमागत अणु
	META_CP,
	META_NAT,
	META_SIT,
	META_SSA,
	META_MAX,
	META_POR,
	DATA_GENERIC,		/* check range only */
	DATA_GENERIC_ENHANCE,	/* strong check on range and segment biपंचांगap */
	DATA_GENERIC_ENHANCE_READ,	/*
					 * strong check on range and segment
					 * biपंचांगap but no warning due to race
					 * condition of पढ़ो on truncated area
					 * by extent_cache
					 */
	META_GENERIC,
पूर्ण;

/* क्रम the list of ino */
क्रमागत अणु
	ORPHAN_INO,		/* क्रम orphan ino list */
	APPEND_INO,		/* क्रम append ino list */
	UPDATE_INO,		/* क्रम update ino list */
	TRANS_सूची_INO,		/* क्रम trasactions dir ino list */
	FLUSH_INO,		/* क्रम multiple device flushing */
	MAX_INO_ENTRY,		/* max. list */
पूर्ण;

काष्ठा ino_entry अणु
	काष्ठा list_head list;		/* list head */
	nid_t ino;			/* inode number */
	अचिन्हित पूर्णांक dirty_device;	/* dirty device biपंचांगap */
पूर्ण;

/* क्रम the list of inodes to be GCed */
काष्ठा inode_entry अणु
	काष्ठा list_head list;	/* list head */
	काष्ठा inode *inode;	/* vfs inode poपूर्णांकer */
पूर्ण;

काष्ठा fsync_node_entry अणु
	काष्ठा list_head list;	/* list head */
	काष्ठा page *page;	/* warm node page poपूर्णांकer */
	अचिन्हित पूर्णांक seq_id;	/* sequence id */
पूर्ण;

काष्ठा ckpt_req अणु
	काष्ठा completion रुको;		/* completion क्रम checkpoपूर्णांक करोne */
	काष्ठा llist_node llnode;	/* llist_node to be linked in रुको queue */
	पूर्णांक ret;			/* वापस code of checkpoपूर्णांक */
	kसमय_प्रकार queue_समय;		/* request queued समय */
पूर्ण;

काष्ठा ckpt_req_control अणु
	काष्ठा task_काष्ठा *f2fs_issue_ckpt;	/* checkpoपूर्णांक task */
	पूर्णांक ckpt_thपढ़ो_ioprio;			/* checkpoपूर्णांक merge thपढ़ो ioprio */
	रुको_queue_head_t ckpt_रुको_queue;	/* रुकोing queue क्रम wake-up */
	atomic_t issued_ckpt;		/* # of actually issued ckpts */
	atomic_t total_ckpt;		/* # of total ckpts */
	atomic_t queued_ckpt;		/* # of queued ckpts */
	काष्ठा llist_head issue_list;	/* list क्रम command issue */
	spinlock_t stat_lock;		/* lock क्रम below checkpoपूर्णांक समय stats */
	अचिन्हित पूर्णांक cur_समय;		/* cur रुको समय in msec क्रम currently issued checkpoपूर्णांक */
	अचिन्हित पूर्णांक peak_समय;		/* peak रुको समय in msec until now */
पूर्ण;

/* क्रम the biपंचांगap indicate blocks to be discarded */
काष्ठा discard_entry अणु
	काष्ठा list_head list;	/* list head */
	block_t start_blkaddr;	/* start blockaddr of current segment */
	अचिन्हित अक्षर discard_map[SIT_VBLOCK_MAP_SIZE];	/* segment discard biपंचांगap */
पूर्ण;

/* शेष discard granularity of inner discard thपढ़ो, unit: block count */
#घोषणा DEFAULT_DISCARD_GRANULARITY		16

/* max discard pend list number */
#घोषणा MAX_PLIST_NUM		512
#घोषणा plist_idx(blk_num)	((blk_num) >= MAX_PLIST_NUM ?		\
					(MAX_PLIST_NUM - 1) : ((blk_num) - 1))

क्रमागत अणु
	D_PREP,			/* initial */
	D_PARTIAL,		/* partially submitted */
	D_SUBMIT,		/* all submitted */
	D_DONE,			/* finished */
पूर्ण;

काष्ठा discard_info अणु
	block_t lstart;			/* logical start address */
	block_t len;			/* length */
	block_t start;			/* actual start address in dev */
पूर्ण;

काष्ठा discard_cmd अणु
	काष्ठा rb_node rb_node;		/* rb node located in rb-tree */
	जोड़ अणु
		काष्ठा अणु
			block_t lstart;	/* logical start address */
			block_t len;	/* length */
			block_t start;	/* actual start address in dev */
		पूर्ण;
		काष्ठा discard_info di;	/* discard info */

	पूर्ण;
	काष्ठा list_head list;		/* command list */
	काष्ठा completion रुको;		/* compleation */
	काष्ठा block_device *bdev;	/* bdev */
	अचिन्हित लघु ref;		/* reference count */
	अचिन्हित अक्षर state;		/* state */
	अचिन्हित अक्षर queued;		/* queued discard */
	पूर्णांक error;			/* bio error */
	spinlock_t lock;		/* क्रम state/bio_ref updating */
	अचिन्हित लघु bio_ref;		/* bio reference count */
पूर्ण;

क्रमागत अणु
	DPOLICY_BG,
	DPOLICY_FORCE,
	DPOLICY_FSTRIM,
	DPOLICY_UMOUNT,
	MAX_DPOLICY,
पूर्ण;

काष्ठा discard_policy अणु
	पूर्णांक type;			/* type of discard */
	अचिन्हित पूर्णांक min_पूर्णांकerval;	/* used क्रम candidates exist */
	अचिन्हित पूर्णांक mid_पूर्णांकerval;	/* used क्रम device busy */
	अचिन्हित पूर्णांक max_पूर्णांकerval;	/* used क्रम candidates not exist */
	अचिन्हित पूर्णांक max_requests;	/* # of discards issued per round */
	अचिन्हित पूर्णांक io_aware_gran;	/* minimum granularity discard not be aware of I/O */
	bool io_aware;			/* issue discard in idle समय */
	bool sync;			/* submit discard with REQ_SYNC flag */
	bool ordered;			/* issue discard by lba order */
	bool समयout;			/* discard समयout क्रम put_super */
	अचिन्हित पूर्णांक granularity;	/* discard granularity */
पूर्ण;

काष्ठा discard_cmd_control अणु
	काष्ठा task_काष्ठा *f2fs_issue_discard;	/* discard thपढ़ो */
	काष्ठा list_head entry_list;		/* 4KB discard entry list */
	काष्ठा list_head pend_list[MAX_PLIST_NUM];/* store pending entries */
	काष्ठा list_head रुको_list;		/* store on-flushing entries */
	काष्ठा list_head fstrim_list;		/* in-flight discard from fstrim */
	रुको_queue_head_t discard_रुको_queue;	/* रुकोing queue क्रम wake-up */
	अचिन्हित पूर्णांक discard_wake;		/* to wake up discard thपढ़ो */
	काष्ठा mutex cmd_lock;
	अचिन्हित पूर्णांक nr_discards;		/* # of discards in the list */
	अचिन्हित पूर्णांक max_discards;		/* max. discards to be issued */
	अचिन्हित पूर्णांक discard_granularity;	/* discard granularity */
	अचिन्हित पूर्णांक undiscard_blks;		/* # of undiscard blocks */
	अचिन्हित पूर्णांक next_pos;			/* next discard position */
	atomic_t issued_discard;		/* # of issued discard */
	atomic_t queued_discard;		/* # of queued discard */
	atomic_t discard_cmd_cnt;		/* # of cached cmd count */
	काष्ठा rb_root_cached root;		/* root of discard rb-tree */
	bool rbtree_check;			/* config क्रम consistence check */
पूर्ण;

/* क्रम the list of fsync inodes, used only during recovery */
काष्ठा fsync_inode_entry अणु
	काष्ठा list_head list;	/* list head */
	काष्ठा inode *inode;	/* vfs inode poपूर्णांकer */
	block_t blkaddr;	/* block address locating the last fsync */
	block_t last_dentry;	/* block address locating the last dentry */
पूर्ण;

#घोषणा nats_in_cursum(jnl)		(le16_to_cpu((jnl)->n_nats))
#घोषणा sits_in_cursum(jnl)		(le16_to_cpu((jnl)->n_sits))

#घोषणा nat_in_journal(jnl, i)		((jnl)->nat_j.entries[i].ne)
#घोषणा nid_in_journal(jnl, i)		((jnl)->nat_j.entries[i].nid)
#घोषणा sit_in_journal(jnl, i)		((jnl)->sit_j.entries[i].se)
#घोषणा segno_in_journal(jnl, i)	((jnl)->sit_j.entries[i].segno)

#घोषणा MAX_NAT_JENTRIES(jnl)	(NAT_JOURNAL_ENTRIES - nats_in_cursum(jnl))
#घोषणा MAX_SIT_JENTRIES(jnl)	(SIT_JOURNAL_ENTRIES - sits_in_cursum(jnl))

अटल अंतरभूत पूर्णांक update_nats_in_cursum(काष्ठा f2fs_journal *journal, पूर्णांक i)
अणु
	पूर्णांक beक्रमe = nats_in_cursum(journal);

	journal->n_nats = cpu_to_le16(beक्रमe + i);
	वापस beक्रमe;
पूर्ण

अटल अंतरभूत पूर्णांक update_sits_in_cursum(काष्ठा f2fs_journal *journal, पूर्णांक i)
अणु
	पूर्णांक beक्रमe = sits_in_cursum(journal);

	journal->n_sits = cpu_to_le16(beक्रमe + i);
	वापस beक्रमe;
पूर्ण

अटल अंतरभूत bool __has_cursum_space(काष्ठा f2fs_journal *journal,
							पूर्णांक size, पूर्णांक type)
अणु
	अगर (type == NAT_JOURNAL)
		वापस size <= MAX_NAT_JENTRIES(journal);
	वापस size <= MAX_SIT_JENTRIES(journal);
पूर्ण

/* क्रम अंतरभूत stuff */
#घोषणा DEF_INLINE_RESERVED_SIZE	1
अटल अंतरभूत पूर्णांक get_extra_isize(काष्ठा inode *inode);
अटल अंतरभूत पूर्णांक get_अंतरभूत_xattr_addrs(काष्ठा inode *inode);
#घोषणा MAX_INLINE_DATA(inode)	(माप(__le32) *			\
				(CUR_ADDRS_PER_INODE(inode) -		\
				get_अंतरभूत_xattr_addrs(inode) -	\
				DEF_INLINE_RESERVED_SIZE))

/* क्रम अंतरभूत dir */
#घोषणा NR_INLINE_DENTRY(inode)	(MAX_INLINE_DATA(inode) * BITS_PER_BYTE / \
				((SIZE_OF_सूची_ENTRY + F2FS_SLOT_LEN) * \
				BITS_PER_BYTE + 1))
#घोषणा INLINE_DENTRY_BITMAP_SIZE(inode) \
	DIV_ROUND_UP(NR_INLINE_DENTRY(inode), BITS_PER_BYTE)
#घोषणा INLINE_RESERVED_SIZE(inode)	(MAX_INLINE_DATA(inode) - \
				((SIZE_OF_सूची_ENTRY + F2FS_SLOT_LEN) * \
				NR_INLINE_DENTRY(inode) + \
				INLINE_DENTRY_BITMAP_SIZE(inode)))

/*
 * For INODE and NODE manager
 */
/* क्रम directory operations */

काष्ठा f2fs_filename अणु
	/*
	 * The filename the user specअगरied.  This is शून्य क्रम some
	 * fileप्रणाली-पूर्णांकernal operations, e.g. converting an अंतरभूत directory
	 * to a non-अंतरभूत one, or roll-क्रमward recovering an encrypted dentry.
	 */
	स्थिर काष्ठा qstr *usr_fname;

	/*
	 * The on-disk filename.  For encrypted directories, this is encrypted.
	 * This may be शून्य क्रम lookups in an encrypted dir without the key.
	 */
	काष्ठा fscrypt_str disk_name;

	/* The dirhash of this filename */
	f2fs_hash_t hash;

#अगर_घोषित CONFIG_FS_ENCRYPTION
	/*
	 * For lookups in encrypted directories: either the buffer backing
	 * disk_name, or a buffer that holds the decoded no-key name.
	 */
	काष्ठा fscrypt_str crypto_buf;
#पूर्ण_अगर
#अगर_घोषित CONFIG_UNICODE
	/*
	 * For हालfolded directories: the हालfolded name, but it's left शून्य
	 * अगर the original name is not valid Unicode, अगर the directory is both
	 * हालfolded and encrypted and its encryption key is unavailable, or अगर
	 * the fileप्रणाली is करोing an पूर्णांकernal operation where usr_fname is also
	 * शून्य.  In all these हालs we fall back to treating the name as an
	 * opaque byte sequence.
	 */
	काष्ठा fscrypt_str cf_name;
#पूर्ण_अगर
पूर्ण;

काष्ठा f2fs_dentry_ptr अणु
	काष्ठा inode *inode;
	व्योम *biपंचांगap;
	काष्ठा f2fs_dir_entry *dentry;
	__u8 (*filename)[F2FS_SLOT_LEN];
	पूर्णांक max;
	पूर्णांक nr_biपंचांगap;
पूर्ण;

अटल अंतरभूत व्योम make_dentry_ptr_block(काष्ठा inode *inode,
		काष्ठा f2fs_dentry_ptr *d, काष्ठा f2fs_dentry_block *t)
अणु
	d->inode = inode;
	d->max = NR_DENTRY_IN_BLOCK;
	d->nr_biपंचांगap = SIZE_OF_DENTRY_BITMAP;
	d->biपंचांगap = t->dentry_biपंचांगap;
	d->dentry = t->dentry;
	d->filename = t->filename;
पूर्ण

अटल अंतरभूत व्योम make_dentry_ptr_अंतरभूत(काष्ठा inode *inode,
					काष्ठा f2fs_dentry_ptr *d, व्योम *t)
अणु
	पूर्णांक entry_cnt = NR_INLINE_DENTRY(inode);
	पूर्णांक biपंचांगap_size = INLINE_DENTRY_BITMAP_SIZE(inode);
	पूर्णांक reserved_size = INLINE_RESERVED_SIZE(inode);

	d->inode = inode;
	d->max = entry_cnt;
	d->nr_biपंचांगap = biपंचांगap_size;
	d->biपंचांगap = t;
	d->dentry = t + biपंचांगap_size + reserved_size;
	d->filename = t + biपंचांगap_size + reserved_size +
					SIZE_OF_सूची_ENTRY * entry_cnt;
पूर्ण

/*
 * XATTR_NODE_OFFSET stores xattrs to one node block per file keeping -1
 * as its node offset to distinguish from index node blocks.
 * But some bits are used to mark the node block.
 */
#घोषणा XATTR_NODE_OFFSET	((((अचिन्हित पूर्णांक)-1) << OFFSET_BIT_SHIFT) \
				>> OFFSET_BIT_SHIFT)
क्रमागत अणु
	ALLOC_NODE,			/* allocate a new node page अगर needed */
	LOOKUP_NODE,			/* look up a node without पढ़ोahead */
	LOOKUP_NODE_RA,			/*
					 * look up a node with पढ़ोahead called
					 * by get_data_block.
					 */
पूर्ण;

#घोषणा DEFAULT_RETRY_IO_COUNT	8	/* maximum retry पढ़ो IO count */

/* congestion रुको समयout value, शेष: 20ms */
#घोषणा	DEFAULT_IO_TIMEOUT	(msecs_to_jअगरfies(20))

/* maximum retry quota flush count */
#घोषणा DEFAULT_RETRY_QUOTA_FLUSH_COUNT		8

#घोषणा F2FS_LINK_MAX	0xffffffff	/* maximum link count per file */

#घोषणा MAX_सूची_RA_PAGES	4	/* maximum ra pages of dir */

/* क्रम in-memory extent cache entry */
#घोषणा F2FS_MIN_EXTENT_LEN	64	/* minimum extent length */

/* number of extent info in extent cache we try to shrink */
#घोषणा EXTENT_CACHE_SHRINK_NUMBER	128

काष्ठा rb_entry अणु
	काष्ठा rb_node rb_node;		/* rb node located in rb-tree */
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक ofs;	/* start offset of the entry */
			अचिन्हित पूर्णांक len;	/* length of the entry */
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ key;		/* 64-bits key */
	पूर्ण __packed;
पूर्ण;

काष्ठा extent_info अणु
	अचिन्हित पूर्णांक fofs;		/* start offset in a file */
	अचिन्हित पूर्णांक len;		/* length of the extent */
	u32 blk;			/* start block address of the extent */
पूर्ण;

काष्ठा extent_node अणु
	काष्ठा rb_node rb_node;		/* rb node located in rb-tree */
	काष्ठा extent_info ei;		/* extent info */
	काष्ठा list_head list;		/* node in global extent list of sbi */
	काष्ठा extent_tree *et;		/* extent tree poपूर्णांकer */
पूर्ण;

काष्ठा extent_tree अणु
	nid_t ino;			/* inode number */
	काष्ठा rb_root_cached root;	/* root of extent info rb-tree */
	काष्ठा extent_node *cached_en;	/* recently accessed extent node */
	काष्ठा extent_info largest;	/* largested extent info */
	काष्ठा list_head list;		/* to be used by sbi->zombie_list */
	rwlock_t lock;			/* protect extent info rb-tree */
	atomic_t node_cnt;		/* # of extent node in rb-tree*/
	bool largest_updated;		/* largest extent updated */
पूर्ण;

/*
 * This काष्ठाure is taken from ext4_map_blocks.
 *
 * Note that, however, f2fs uses NEW and MAPPED flags क्रम f2fs_map_blocks().
 */
#घोषणा F2FS_MAP_NEW		(1 << BH_New)
#घोषणा F2FS_MAP_MAPPED		(1 << BH_Mapped)
#घोषणा F2FS_MAP_UNWRITTEN	(1 << BH_Unwritten)
#घोषणा F2FS_MAP_FLAGS		(F2FS_MAP_NEW | F2FS_MAP_MAPPED |\
				F2FS_MAP_UNWRITTEN)

काष्ठा f2fs_map_blocks अणु
	block_t m_pblk;
	block_t m_lblk;
	अचिन्हित पूर्णांक m_len;
	अचिन्हित पूर्णांक m_flags;
	pgoff_t *m_next_pgofs;		/* poपूर्णांक next possible non-hole pgofs */
	pgoff_t *m_next_extent;		/* poपूर्णांक to next possible extent */
	पूर्णांक m_seg_type;
	bool m_may_create;		/* indicate it is from ग_लिखो path */
पूर्ण;

/* क्रम flag in get_data_block */
क्रमागत अणु
	F2FS_GET_BLOCK_DEFAULT,
	F2FS_GET_BLOCK_FIEMAP,
	F2FS_GET_BLOCK_BMAP,
	F2FS_GET_BLOCK_DIO,
	F2FS_GET_BLOCK_PRE_DIO,
	F2FS_GET_BLOCK_PRE_AIO,
	F2FS_GET_BLOCK_PRECACHE,
पूर्ण;

/*
 * i_advise uses FADVISE_XXX_BIT. We can add additional hपूर्णांकs later.
 */
#घोषणा FADVISE_COLD_BIT	0x01
#घोषणा FADVISE_LOST_PINO_BIT	0x02
#घोषणा FADVISE_ENCRYPT_BIT	0x04
#घोषणा FADVISE_ENC_NAME_BIT	0x08
#घोषणा FADVISE_KEEP_SIZE_BIT	0x10
#घोषणा FADVISE_HOT_BIT		0x20
#घोषणा FADVISE_VERITY_BIT	0x40

#घोषणा FADVISE_MODIFIABLE_BITS	(FADVISE_COLD_BIT | FADVISE_HOT_BIT)

#घोषणा file_is_cold(inode)	is_file(inode, FADVISE_COLD_BIT)
#घोषणा file_set_cold(inode)	set_file(inode, FADVISE_COLD_BIT)
#घोषणा file_clear_cold(inode)	clear_file(inode, FADVISE_COLD_BIT)

#घोषणा file_wrong_pino(inode)	is_file(inode, FADVISE_LOST_PINO_BIT)
#घोषणा file_lost_pino(inode)	set_file(inode, FADVISE_LOST_PINO_BIT)
#घोषणा file_got_pino(inode)	clear_file(inode, FADVISE_LOST_PINO_BIT)

#घोषणा file_is_encrypt(inode)	is_file(inode, FADVISE_ENCRYPT_BIT)
#घोषणा file_set_encrypt(inode)	set_file(inode, FADVISE_ENCRYPT_BIT)

#घोषणा file_enc_name(inode)	is_file(inode, FADVISE_ENC_NAME_BIT)
#घोषणा file_set_enc_name(inode) set_file(inode, FADVISE_ENC_NAME_BIT)

#घोषणा file_keep_isize(inode)	is_file(inode, FADVISE_KEEP_SIZE_BIT)
#घोषणा file_set_keep_isize(inode) set_file(inode, FADVISE_KEEP_SIZE_BIT)

#घोषणा file_is_hot(inode)	is_file(inode, FADVISE_HOT_BIT)
#घोषणा file_set_hot(inode)	set_file(inode, FADVISE_HOT_BIT)
#घोषणा file_clear_hot(inode)	clear_file(inode, FADVISE_HOT_BIT)

#घोषणा file_is_verity(inode)	is_file(inode, FADVISE_VERITY_BIT)
#घोषणा file_set_verity(inode)	set_file(inode, FADVISE_VERITY_BIT)

#घोषणा DEF_सूची_LEVEL		0

क्रमागत अणु
	GC_FAILURE_PIN,
	GC_FAILURE_ATOMIC,
	MAX_GC_FAILURE
पूर्ण;

/* used क्रम f2fs_inode_info->flags */
क्रमागत अणु
	FI_NEW_INODE,		/* indicate newly allocated inode */
	FI_सूचीTY_INODE,		/* indicate inode is dirty or not */
	FI_AUTO_RECOVER,	/* indicate inode is recoverable */
	FI_सूचीTY_सूची,		/* indicate directory has dirty pages */
	FI_INC_LINK,		/* need to increment i_nlink */
	FI_ACL_MODE,		/* indicate acl mode */
	FI_NO_ALLOC,		/* should not allocate any blocks */
	FI_FREE_NID,		/* मुक्त allocated nide */
	FI_NO_EXTENT,		/* not to use the extent cache */
	FI_INLINE_XATTR,	/* used क्रम अंतरभूत xattr */
	FI_INLINE_DATA,		/* used क्रम अंतरभूत data*/
	FI_INLINE_DENTRY,	/* used क्रम अंतरभूत dentry */
	FI_APPEND_WRITE,	/* inode has appended data */
	FI_UPDATE_WRITE,	/* inode has in-place-update data */
	FI_NEED_IPU,		/* used क्रम ipu per file */
	FI_ATOMIC_खाता,		/* indicate atomic file */
	FI_ATOMIC_COMMIT,	/* indicate the state of atomical committing */
	FI_VOLATILE_खाता,	/* indicate अस्थिर file */
	FI_FIRST_BLOCK_WRITTEN,	/* indicate #0 data block was written */
	FI_DROP_CACHE,		/* drop dirty page cache */
	FI_DATA_EXIST,		/* indicate data exists */
	FI_INLINE_DOTS,		/* indicate अंतरभूत करोt dentries */
	FI_DO_DEFRAG,		/* indicate defragment is running */
	FI_सूचीTY_खाता,		/* indicate regular/symlink has dirty pages */
	FI_NO_PREALLOC,		/* indicate skipped pपुनः_स्मृतिated blocks */
	FI_HOT_DATA,		/* indicate file is hot */
	FI_EXTRA_ATTR,		/* indicate file has extra attribute */
	FI_PROJ_INHERIT,	/* indicate file inherits projectid */
	FI_PIN_खाता,		/* indicate file should not be gced */
	FI_ATOMIC_REVOKE_REQUEST, /* request to drop atomic data */
	FI_VERITY_IN_PROGRESS,	/* building fs-verity Merkle tree */
	FI_COMPRESSED_खाता,	/* indicate file's data can be compressed */
	FI_COMPRESS_CORRUPT,	/* indicate compressed cluster is corrupted */
	FI_MMAP_खाता,		/* indicate file was mmapped */
	FI_ENABLE_COMPRESS,	/* enable compression in "user" compression mode */
	FI_MAX,			/* max flag, never be used */
पूर्ण;

काष्ठा f2fs_inode_info अणु
	काष्ठा inode vfs_inode;		/* serve a vfs inode */
	अचिन्हित दीर्घ i_flags;		/* keep an inode flags क्रम ioctl */
	अचिन्हित अक्षर i_advise;		/* use to give file attribute hपूर्णांकs */
	अचिन्हित अक्षर i_dir_level;	/* use क्रम dentry level क्रम large dir */
	अचिन्हित पूर्णांक i_current_depth;	/* only क्रम directory depth */
	/* क्रम gc failure statistic */
	अचिन्हित पूर्णांक i_gc_failures[MAX_GC_FAILURE];
	अचिन्हित पूर्णांक i_pino;		/* parent inode number */
	umode_t i_acl_mode;		/* keep file acl mode temporarily */

	/* Use below पूर्णांकernally in f2fs*/
	अचिन्हित दीर्घ flags[BITS_TO_LONGS(FI_MAX)];	/* use to pass per-file flags */
	काष्ठा rw_semaphore i_sem;	/* protect fi info */
	atomic_t dirty_pages;		/* # of dirty pages */
	f2fs_hash_t chash;		/* hash value of given file name */
	अचिन्हित पूर्णांक clevel;		/* maximum level of given file name */
	काष्ठा task_काष्ठा *task;	/* lookup and create consistency */
	काष्ठा task_काष्ठा *cp_task;	/* separate cp/wb IO stats*/
	nid_t i_xattr_nid;		/* node id that contains xattrs */
	loff_t	last_disk_size;		/* lastly written file size */
	spinlock_t i_size_lock;		/* protect last_disk_size */

#अगर_घोषित CONFIG_QUOTA
	काष्ठा dquot *i_dquot[MAXQUOTAS];

	/* quota space reservation, managed पूर्णांकernally by quota code */
	qमाप_प्रकार i_reserved_quota;
#पूर्ण_अगर
	काष्ठा list_head dirty_list;	/* dirty list क्रम dirs and files */
	काष्ठा list_head gdirty_list;	/* linked in global dirty list */
	काष्ठा list_head inmem_ilist;	/* list क्रम inmem inodes */
	काष्ठा list_head inmem_pages;	/* inmemory pages managed by f2fs */
	काष्ठा task_काष्ठा *inmem_task;	/* store inmemory task */
	काष्ठा mutex inmem_lock;	/* lock क्रम inmemory pages */
	काष्ठा extent_tree *extent_tree;	/* cached extent_tree entry */

	/* aव्योम racing between क्रमeground op and gc */
	काष्ठा rw_semaphore i_gc_rwsem[2];
	काष्ठा rw_semaphore i_mmap_sem;
	काष्ठा rw_semaphore i_xattr_sem; /* aव्योम racing between पढ़ोing and changing EAs */

	पूर्णांक i_extra_isize;		/* size of extra space located in i_addr */
	kprojid_t i_projid;		/* id क्रम project quota */
	पूर्णांक i_अंतरभूत_xattr_size;	/* अंतरभूत xattr size */
	काष्ठा बारpec64 i_crसमय;	/* inode creation समय */
	काष्ठा बारpec64 i_disk_समय[4];/* inode disk बार */

	/* क्रम file compress */
	atomic_t i_compr_blocks;		/* # of compressed blocks */
	अचिन्हित अक्षर i_compress_algorithm;	/* algorithm type */
	अचिन्हित अक्षर i_log_cluster_size;	/* log of cluster size */
	अचिन्हित अक्षर i_compress_level;		/* compress level (lz4hc,zstd) */
	अचिन्हित लघु i_compress_flag;		/* compress flag */
	अचिन्हित पूर्णांक i_cluster_size;		/* cluster size */
पूर्ण;

अटल अंतरभूत व्योम get_extent_info(काष्ठा extent_info *ext,
					काष्ठा f2fs_extent *i_ext)
अणु
	ext->fofs = le32_to_cpu(i_ext->fofs);
	ext->blk = le32_to_cpu(i_ext->blk);
	ext->len = le32_to_cpu(i_ext->len);
पूर्ण

अटल अंतरभूत व्योम set_raw_extent(काष्ठा extent_info *ext,
					काष्ठा f2fs_extent *i_ext)
अणु
	i_ext->fofs = cpu_to_le32(ext->fofs);
	i_ext->blk = cpu_to_le32(ext->blk);
	i_ext->len = cpu_to_le32(ext->len);
पूर्ण

अटल अंतरभूत व्योम set_extent_info(काष्ठा extent_info *ei, अचिन्हित पूर्णांक fofs,
						u32 blk, अचिन्हित पूर्णांक len)
अणु
	ei->fofs = fofs;
	ei->blk = blk;
	ei->len = len;
पूर्ण

अटल अंतरभूत bool __is_discard_mergeable(काष्ठा discard_info *back,
			काष्ठा discard_info *front, अचिन्हित पूर्णांक max_len)
अणु
	वापस (back->lstart + back->len == front->lstart) &&
		(back->len + front->len <= max_len);
पूर्ण

अटल अंतरभूत bool __is_discard_back_mergeable(काष्ठा discard_info *cur,
			काष्ठा discard_info *back, अचिन्हित पूर्णांक max_len)
अणु
	वापस __is_discard_mergeable(back, cur, max_len);
पूर्ण

अटल अंतरभूत bool __is_discard_front_mergeable(काष्ठा discard_info *cur,
			काष्ठा discard_info *front, अचिन्हित पूर्णांक max_len)
अणु
	वापस __is_discard_mergeable(cur, front, max_len);
पूर्ण

अटल अंतरभूत bool __is_extent_mergeable(काष्ठा extent_info *back,
						काष्ठा extent_info *front)
अणु
	वापस (back->fofs + back->len == front->fofs &&
			back->blk + back->len == front->blk);
पूर्ण

अटल अंतरभूत bool __is_back_mergeable(काष्ठा extent_info *cur,
						काष्ठा extent_info *back)
अणु
	वापस __is_extent_mergeable(back, cur);
पूर्ण

अटल अंतरभूत bool __is_front_mergeable(काष्ठा extent_info *cur,
						काष्ठा extent_info *front)
अणु
	वापस __is_extent_mergeable(cur, front);
पूर्ण

बाह्य व्योम f2fs_mark_inode_dirty_sync(काष्ठा inode *inode, bool sync);
अटल अंतरभूत व्योम __try_update_largest_extent(काष्ठा extent_tree *et,
						काष्ठा extent_node *en)
अणु
	अगर (en->ei.len > et->largest.len) अणु
		et->largest = en->ei;
		et->largest_updated = true;
	पूर्ण
पूर्ण

/*
 * For मुक्त nid management
 */
क्रमागत nid_state अणु
	FREE_NID,		/* newly added to मुक्त nid list */
	PREALLOC_NID,		/* it is pपुनः_स्मृतिated */
	MAX_NID_STATE,
पूर्ण;

क्रमागत nat_state अणु
	TOTAL_NAT,
	सूचीTY_NAT,
	RECLAIMABLE_NAT,
	MAX_NAT_STATE,
पूर्ण;

काष्ठा f2fs_nm_info अणु
	block_t nat_blkaddr;		/* base disk address of NAT */
	nid_t max_nid;			/* maximum possible node ids */
	nid_t available_nids;		/* # of available node ids */
	nid_t next_scan_nid;		/* the next nid to be scanned */
	अचिन्हित पूर्णांक ram_thresh;	/* control the memory footprपूर्णांक */
	अचिन्हित पूर्णांक ra_nid_pages;	/* # of nid pages to be पढ़ोaheaded */
	अचिन्हित पूर्णांक dirty_nats_ratio;	/* control dirty nats ratio threshold */

	/* NAT cache management */
	काष्ठा radix_tree_root nat_root;/* root of the nat entry cache */
	काष्ठा radix_tree_root nat_set_root;/* root of the nat set cache */
	काष्ठा rw_semaphore nat_tree_lock;	/* protect nat entry tree */
	काष्ठा list_head nat_entries;	/* cached nat entry list (clean) */
	spinlock_t nat_list_lock;	/* protect clean nat entry list */
	अचिन्हित पूर्णांक nat_cnt[MAX_NAT_STATE]; /* the # of cached nat entries */
	अचिन्हित पूर्णांक nat_blocks;	/* # of nat blocks */

	/* मुक्त node ids management */
	काष्ठा radix_tree_root मुक्त_nid_root;/* root of the मुक्त_nid cache */
	काष्ठा list_head मुक्त_nid_list;		/* list क्रम मुक्त nids excluding pपुनः_स्मृतिated nids */
	अचिन्हित पूर्णांक nid_cnt[MAX_NID_STATE];	/* the number of मुक्त node id */
	spinlock_t nid_list_lock;	/* protect nid lists ops */
	काष्ठा mutex build_lock;	/* lock क्रम build मुक्त nids */
	अचिन्हित अक्षर **मुक्त_nid_biपंचांगap;
	अचिन्हित अक्षर *nat_block_biपंचांगap;
	अचिन्हित लघु *मुक्त_nid_count;	/* मुक्त nid count of NAT block */

	/* क्रम checkpoपूर्णांक */
	अक्षर *nat_biपंचांगap;		/* NAT biपंचांगap poपूर्णांकer */

	अचिन्हित पूर्णांक nat_bits_blocks;	/* # of nat bits blocks */
	अचिन्हित अक्षर *nat_bits;	/* NAT bits blocks */
	अचिन्हित अक्षर *full_nat_bits;	/* full NAT pages */
	अचिन्हित अक्षर *empty_nat_bits;	/* empty NAT pages */
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	अक्षर *nat_biपंचांगap_mir;		/* NAT biपंचांगap mirror */
#पूर्ण_अगर
	पूर्णांक biपंचांगap_size;		/* biपंचांगap size */
पूर्ण;

/*
 * this काष्ठाure is used as one of function parameters.
 * all the inक्रमmation are dedicated to a given direct node block determined
 * by the data offset in a file.
 */
काष्ठा dnode_of_data अणु
	काष्ठा inode *inode;		/* vfs inode poपूर्णांकer */
	काष्ठा page *inode_page;	/* its inode page, शून्य is possible */
	काष्ठा page *node_page;		/* cached direct node page */
	nid_t nid;			/* node id of the direct node block */
	अचिन्हित पूर्णांक ofs_in_node;	/* data offset in the node page */
	bool inode_page_locked;		/* inode page is locked or not */
	bool node_changed;		/* is node block changed */
	अक्षर cur_level;			/* level of hole node page */
	अक्षर max_level;			/* level of current page located */
	block_t	data_blkaddr;		/* block address of the node block */
पूर्ण;

अटल अंतरभूत व्योम set_new_dnode(काष्ठा dnode_of_data *dn, काष्ठा inode *inode,
		काष्ठा page *ipage, काष्ठा page *npage, nid_t nid)
अणु
	स_रखो(dn, 0, माप(*dn));
	dn->inode = inode;
	dn->inode_page = ipage;
	dn->node_page = npage;
	dn->nid = nid;
पूर्ण

/*
 * For SIT manager
 *
 * By शेष, there are 6 active log areas across the whole मुख्य area.
 * When considering hot and cold data separation to reduce cleaning overhead,
 * we split 3 क्रम data logs and 3 क्रम node logs as hot, warm, and cold types,
 * respectively.
 * In the current design, you should not change the numbers पूर्णांकentionally.
 * Instead, as a mount option such as active_logs=x, you can use 2, 4, and 6
 * logs inभागidually according to the underlying devices. (शेष: 6)
 * Just in हाल, on-disk layout covers maximum 16 logs that consist of 8 क्रम
 * data and 8 क्रम node logs.
 */
#घोषणा	NR_CURSEG_DATA_TYPE	(3)
#घोषणा NR_CURSEG_NODE_TYPE	(3)
#घोषणा NR_CURSEG_INMEM_TYPE	(2)
#घोषणा NR_CURSEG_PERSIST_TYPE	(NR_CURSEG_DATA_TYPE + NR_CURSEG_NODE_TYPE)
#घोषणा NR_CURSEG_TYPE		(NR_CURSEG_INMEM_TYPE + NR_CURSEG_PERSIST_TYPE)

क्रमागत अणु
	CURSEG_HOT_DATA	= 0,	/* directory entry blocks */
	CURSEG_WARM_DATA,	/* data blocks */
	CURSEG_COLD_DATA,	/* mulसमयdia or GCed data blocks */
	CURSEG_HOT_NODE,	/* direct node blocks of directory files */
	CURSEG_WARM_NODE,	/* direct node blocks of normal files */
	CURSEG_COLD_NODE,	/* indirect node blocks */
	NR_PERSISTENT_LOG,	/* number of persistent log */
	CURSEG_COLD_DATA_PINNED = NR_PERSISTENT_LOG,
				/* pinned file that needs consecutive block address */
	CURSEG_ALL_DATA_ATGC,	/* SSR alloctor in hot/warm/cold data area */
	NO_CHECK_TYPE,		/* number of persistent & inmem log */
पूर्ण;

काष्ठा flush_cmd अणु
	काष्ठा completion रुको;
	काष्ठा llist_node llnode;
	nid_t ino;
	पूर्णांक ret;
पूर्ण;

काष्ठा flush_cmd_control अणु
	काष्ठा task_काष्ठा *f2fs_issue_flush;	/* flush thपढ़ो */
	रुको_queue_head_t flush_रुको_queue;	/* रुकोing queue क्रम wake-up */
	atomic_t issued_flush;			/* # of issued flushes */
	atomic_t queued_flush;			/* # of queued flushes */
	काष्ठा llist_head issue_list;		/* list क्रम command issue */
	काष्ठा llist_node *dispatch_list;	/* list क्रम command dispatch */
पूर्ण;

काष्ठा f2fs_sm_info अणु
	काष्ठा sit_info *sit_info;		/* whole segment inक्रमmation */
	काष्ठा मुक्त_segmap_info *मुक्त_info;	/* मुक्त segment inक्रमmation */
	काष्ठा dirty_seglist_info *dirty_info;	/* dirty segment inक्रमmation */
	काष्ठा curseg_info *curseg_array;	/* active segment inक्रमmation */

	काष्ठा rw_semaphore curseg_lock;	/* क्रम preventing curseg change */

	block_t seg0_blkaddr;		/* block address of 0'th segment */
	block_t मुख्य_blkaddr;		/* start block address of मुख्य area */
	block_t ssa_blkaddr;		/* start block address of SSA area */

	अचिन्हित पूर्णांक segment_count;	/* total # of segments */
	अचिन्हित पूर्णांक मुख्य_segments;	/* # of segments in मुख्य area */
	अचिन्हित पूर्णांक reserved_segments;	/* # of reserved segments */
	अचिन्हित पूर्णांक ovp_segments;	/* # of overprovision segments */

	/* a threshold to reclaim preमुक्त segments */
	अचिन्हित पूर्णांक rec_preमुक्त_segments;

	/* क्रम batched trimming */
	अचिन्हित पूर्णांक trim_sections;		/* # of sections to trim */

	काष्ठा list_head sit_entry_set;	/* sit entry set list */

	अचिन्हित पूर्णांक ipu_policy;	/* in-place-update policy */
	अचिन्हित पूर्णांक min_ipu_util;	/* in-place-update threshold */
	अचिन्हित पूर्णांक min_fsync_blocks;	/* threshold क्रम fsync */
	अचिन्हित पूर्णांक min_seq_blocks;	/* threshold क्रम sequential blocks */
	अचिन्हित पूर्णांक min_hot_blocks;	/* threshold क्रम hot block allocation */
	अचिन्हित पूर्णांक min_ssr_sections;	/* threshold to trigger SSR allocation */

	/* क्रम flush command control */
	काष्ठा flush_cmd_control *fcc_info;

	/* क्रम discard command control */
	काष्ठा discard_cmd_control *dcc_info;
पूर्ण;

/*
 * For superblock
 */
/*
 * COUNT_TYPE क्रम monitoring
 *
 * f2fs monitors the number of several block types such as on-ग_लिखोback,
 * dirty dentry blocks, dirty node blocks, and dirty meta blocks.
 */
#घोषणा WB_DATA_TYPE(p)	(__is_cp_guaranteed(p) ? F2FS_WB_CP_DATA : F2FS_WB_DATA)
क्रमागत count_type अणु
	F2FS_सूचीTY_DENTS,
	F2FS_सूचीTY_DATA,
	F2FS_सूचीTY_QDATA,
	F2FS_सूचीTY_NODES,
	F2FS_सूचीTY_META,
	F2FS_INMEM_PAGES,
	F2FS_सूचीTY_IMETA,
	F2FS_WB_CP_DATA,
	F2FS_WB_DATA,
	F2FS_RD_DATA,
	F2FS_RD_NODE,
	F2FS_RD_META,
	F2FS_DIO_WRITE,
	F2FS_DIO_READ,
	NR_COUNT_TYPE,
पूर्ण;

/*
 * The below are the page types of bios used in submit_bio().
 * The available types are:
 * DATA			User data pages. It operates as async mode.
 * NODE			Node pages. It operates as async mode.
 * META			FS metadata pages such as SIT, NAT, CP.
 * NR_PAGE_TYPE		The number of page types.
 * META_FLUSH		Make sure the previous pages are written
 *			with रुकोing the bio's completion
 * ...			Only can be used with META.
 */
#घोषणा PAGE_TYPE_OF_BIO(type)	((type) > META ? META : (type))
क्रमागत page_type अणु
	DATA,
	NODE,
	META,
	NR_PAGE_TYPE,
	META_FLUSH,
	INMEM,		/* the below types are used by tracepoपूर्णांकs only. */
	INMEM_DROP,
	INMEM_INVALIDATE,
	INMEM_REVOKE,
	IPU,
	OPU,
पूर्ण;

क्रमागत temp_type अणु
	HOT = 0,	/* must be zero क्रम meta bio */
	WARM,
	COLD,
	NR_TEMP_TYPE,
पूर्ण;

क्रमागत need_lock_type अणु
	LOCK_REQ = 0,
	LOCK_DONE,
	LOCK_RETRY,
पूर्ण;

क्रमागत cp_reason_type अणु
	CP_NO_NEEDED,
	CP_NON_REGULAR,
	CP_COMPRESSED,
	CP_HARDLINK,
	CP_SB_NEED_CP,
	CP_WRONG_PINO,
	CP_NO_SPC_ROLL,
	CP_NODE_NEED_CP,
	CP_FASTBOOT_MODE,
	CP_SPEC_LOG_NUM,
	CP_RECOVER_सूची,
पूर्ण;

क्रमागत iostat_type अणु
	/* WRITE IO */
	APP_सूचीECT_IO,			/* app direct ग_लिखो IOs */
	APP_BUFFERED_IO,		/* app buffered ग_लिखो IOs */
	APP_WRITE_IO,			/* app ग_लिखो IOs */
	APP_MAPPED_IO,			/* app mapped IOs */
	FS_DATA_IO,			/* data IOs from kworker/fsync/reclaimer */
	FS_NODE_IO,			/* node IOs from kworker/fsync/reclaimer */
	FS_META_IO,			/* meta IOs from kworker/reclaimer */
	FS_GC_DATA_IO,			/* data IOs from क्रमground gc */
	FS_GC_NODE_IO,			/* node IOs from क्रमground gc */
	FS_CP_DATA_IO,			/* data IOs from checkpoपूर्णांक */
	FS_CP_NODE_IO,			/* node IOs from checkpoपूर्णांक */
	FS_CP_META_IO,			/* meta IOs from checkpoपूर्णांक */

	/* READ IO */
	APP_सूचीECT_READ_IO,		/* app direct पढ़ो IOs */
	APP_BUFFERED_READ_IO,		/* app buffered पढ़ो IOs */
	APP_READ_IO,			/* app पढ़ो IOs */
	APP_MAPPED_READ_IO,		/* app mapped पढ़ो IOs */
	FS_DATA_READ_IO,		/* data पढ़ो IOs */
	FS_GDATA_READ_IO,		/* data पढ़ो IOs from background gc */
	FS_CDATA_READ_IO,		/* compressed data पढ़ो IOs */
	FS_NODE_READ_IO,		/* node पढ़ो IOs */
	FS_META_READ_IO,		/* meta पढ़ो IOs */

	/* other */
	FS_DISCARD,			/* discard */
	NR_IO_TYPE,
पूर्ण;

काष्ठा f2fs_io_info अणु
	काष्ठा f2fs_sb_info *sbi;	/* f2fs_sb_info poपूर्णांकer */
	nid_t ino;		/* inode number */
	क्रमागत page_type type;	/* contains DATA/NODE/META/META_FLUSH */
	क्रमागत temp_type temp;	/* contains HOT/WARM/COLD */
	पूर्णांक op;			/* contains REQ_OP_ */
	पूर्णांक op_flags;		/* req_flag_bits */
	block_t new_blkaddr;	/* new block address to be written */
	block_t old_blkaddr;	/* old block address beक्रमe Cow */
	काष्ठा page *page;	/* page to be written */
	काष्ठा page *encrypted_page;	/* encrypted page */
	काष्ठा page *compressed_page;	/* compressed page */
	काष्ठा list_head list;		/* serialize IOs */
	bool submitted;		/* indicate IO submission */
	पूर्णांक need_lock;		/* indicate we need to lock cp_rwsem */
	bool in_list;		/* indicate fio is in io_list */
	bool is_por;		/* indicate IO is from recovery or not */
	bool retry;		/* need to पुनः_स्मृतिate block address */
	पूर्णांक compr_blocks;	/* # of compressed block addresses */
	bool encrypted;		/* indicate file is encrypted */
	क्रमागत iostat_type io_type;	/* io type */
	काष्ठा ग_लिखोback_control *io_wbc; /* ग_लिखोback control */
	काष्ठा bio **bio;		/* bio क्रम ipu */
	sector_t *last_block;		/* last block number in bio */
	अचिन्हित अक्षर version;		/* version of the node */
पूर्ण;

काष्ठा bio_entry अणु
	काष्ठा bio *bio;
	काष्ठा list_head list;
पूर्ण;

#घोषणा is_पढ़ो_io(rw) ((rw) == READ)
काष्ठा f2fs_bio_info अणु
	काष्ठा f2fs_sb_info *sbi;	/* f2fs superblock */
	काष्ठा bio *bio;		/* bios to merge */
	sector_t last_block_in_bio;	/* last block number */
	काष्ठा f2fs_io_info fio;	/* store buffered io info. */
	काष्ठा rw_semaphore io_rwsem;	/* blocking op क्रम bio */
	spinlock_t io_lock;		/* serialize DATA/NODE IOs */
	काष्ठा list_head io_list;	/* track fios */
	काष्ठा list_head bio_list;	/* bio entry list head */
	काष्ठा rw_semaphore bio_list_lock;	/* lock to protect bio entry list */
पूर्ण;

#घोषणा FDEV(i)				(sbi->devs[i])
#घोषणा RDEV(i)				(raw_super->devs[i])
काष्ठा f2fs_dev_info अणु
	काष्ठा block_device *bdev;
	अक्षर path[MAX_PATH_LEN];
	अचिन्हित पूर्णांक total_segments;
	block_t start_blk;
	block_t end_blk;
#अगर_घोषित CONFIG_BLK_DEV_ZONED
	अचिन्हित पूर्णांक nr_blkz;		/* Total number of zones */
	अचिन्हित दीर्घ *blkz_seq;	/* Biपंचांगap indicating sequential zones */
	block_t *zone_capacity_blocks;  /* Array of zone capacity in blks */
#पूर्ण_अगर
पूर्ण;

क्रमागत inode_type अणु
	सूची_INODE,			/* क्रम dirty dir inode */
	खाता_INODE,			/* क्रम dirty regular/symlink inode */
	सूचीTY_META,			/* क्रम all dirtied inode metadata */
	ATOMIC_खाता,			/* क्रम all atomic files */
	NR_INODE_TYPE,
पूर्ण;

/* क्रम inner inode cache management */
काष्ठा inode_management अणु
	काष्ठा radix_tree_root ino_root;	/* ino entry array */
	spinlock_t ino_lock;			/* क्रम ino entry lock */
	काष्ठा list_head ino_list;		/* inode list head */
	अचिन्हित दीर्घ ino_num;			/* number of entries */
पूर्ण;

/* क्रम GC_AT */
काष्ठा atgc_management अणु
	bool atgc_enabled;			/* ATGC is enabled or not */
	काष्ठा rb_root_cached root;		/* root of victim rb-tree */
	काष्ठा list_head victim_list;		/* linked with all victim entries */
	अचिन्हित पूर्णांक victim_count;		/* victim count in rb-tree */
	अचिन्हित पूर्णांक candidate_ratio;		/* candidate ratio */
	अचिन्हित पूर्णांक max_candidate_count;	/* max candidate count */
	अचिन्हित पूर्णांक age_weight;		/* age weight, vblock_weight = 100 - age_weight */
	अचिन्हित दीर्घ दीर्घ age_threshold;	/* age threshold */
पूर्ण;

/* For s_flag in काष्ठा f2fs_sb_info */
क्रमागत अणु
	SBI_IS_सूचीTY,				/* dirty flag क्रम checkpoपूर्णांक */
	SBI_IS_CLOSE,				/* specअगरy unmounting */
	SBI_NEED_FSCK,				/* need fsck.f2fs to fix */
	SBI_POR_DOING,				/* recovery is करोing or not */
	SBI_NEED_SB_WRITE,			/* need to recover superblock */
	SBI_NEED_CP,				/* need to checkpoपूर्णांक */
	SBI_IS_SHUTDOWN,			/* shutकरोwn by ioctl */
	SBI_IS_RECOVERED,			/* recovered orphan/data */
	SBI_CP_DISABLED,			/* CP was disabled last mount */
	SBI_CP_DISABLED_QUICK,			/* CP was disabled quickly */
	SBI_QUOTA_NEED_FLUSH,			/* need to flush quota info in CP */
	SBI_QUOTA_SKIP_FLUSH,			/* skip flushing quota in current CP */
	SBI_QUOTA_NEED_REPAIR,			/* quota file may be corrupted */
	SBI_IS_RESIZEFS,			/* resizefs is in process */
पूर्ण;

क्रमागत अणु
	CP_TIME,
	REQ_TIME,
	DISCARD_TIME,
	GC_TIME,
	DISABLE_TIME,
	UMOUNT_DISCARD_TIMEOUT,
	MAX_TIME,
पूर्ण;

क्रमागत अणु
	GC_NORMAL,
	GC_IDLE_CB,
	GC_IDLE_GREEDY,
	GC_IDLE_AT,
	GC_URGENT_HIGH,
	GC_URGENT_LOW,
पूर्ण;

क्रमागत अणु
	BGGC_MODE_ON,		/* background gc is on */
	BGGC_MODE_OFF,		/* background gc is off */
	BGGC_MODE_SYNC,		/*
				 * background gc is on, migrating blocks
				 * like क्रमeground gc
				 */
पूर्ण;

क्रमागत अणु
	FS_MODE_ADAPTIVE,	/* use both lfs/ssr allocation */
	FS_MODE_LFS,		/* use lfs allocation only */
पूर्ण;

क्रमागत अणु
	WHINT_MODE_OFF,		/* not pass करोwn ग_लिखो hपूर्णांकs */
	WHINT_MODE_USER,	/* try to pass करोwn hपूर्णांकs given by users */
	WHINT_MODE_FS,		/* pass करोwn hपूर्णांकs with F2FS policy */
पूर्ण;

क्रमागत अणु
	ALLOC_MODE_DEFAULT,	/* stay शेष */
	ALLOC_MODE_REUSE,	/* reuse segments as much as possible */
पूर्ण;

क्रमागत fsync_mode अणु
	FSYNC_MODE_POSIX,	/* fsync follows posix semantics */
	FSYNC_MODE_STRICT,	/* fsync behaves in line with ext4 */
	FSYNC_MODE_NOBARRIER,	/* fsync behaves nobarrier based on posix */
पूर्ण;

क्रमागत अणु
	COMPR_MODE_FS,		/*
				 * स्वतःmatically compress compression
				 * enabled files
				 */
	COMPR_MODE_USER,	/*
				 * स्वतःmatical compression is disabled.
				 * user can control the file compression
				 * using ioctls
				 */
पूर्ण;

/*
 * this value is set in page as a निजी data which indicate that
 * the page is atomically written, and it is in inmem_pages list.
 */
#घोषणा ATOMIC_WRITTEN_PAGE		((अचिन्हित दीर्घ)-1)
#घोषणा DUMMY_WRITTEN_PAGE		((अचिन्हित दीर्घ)-2)

#घोषणा IS_ATOMIC_WRITTEN_PAGE(page)			\
		(page_निजी(page) == ATOMIC_WRITTEN_PAGE)
#घोषणा IS_DUMMY_WRITTEN_PAGE(page)			\
		(page_निजी(page) == DUMMY_WRITTEN_PAGE)

/* For compression */
क्रमागत compress_algorithm_type अणु
	COMPRESS_LZO,
	COMPRESS_LZ4,
	COMPRESS_ZSTD,
	COMPRESS_LZORLE,
	COMPRESS_MAX,
पूर्ण;

क्रमागत compress_flag अणु
	COMPRESS_CHKSUM,
	COMPRESS_MAX_FLAG,
पूर्ण;

#घोषणा COMPRESS_DATA_RESERVED_SIZE		4
काष्ठा compress_data अणु
	__le32 clen;			/* compressed data size */
	__le32 chksum;			/* compressed data chksum */
	__le32 reserved[COMPRESS_DATA_RESERVED_SIZE];	/* reserved */
	u8 cdata[];			/* compressed data */
पूर्ण;

#घोषणा COMPRESS_HEADER_SIZE	(माप(काष्ठा compress_data))

#घोषणा F2FS_COMPRESSED_PAGE_MAGIC	0xF5F2C000

#घोषणा	COMPRESS_LEVEL_OFFSET	8

/* compress context */
काष्ठा compress_ctx अणु
	काष्ठा inode *inode;		/* inode the context beदीर्घ to */
	pgoff_t cluster_idx;		/* cluster index number */
	अचिन्हित पूर्णांक cluster_size;	/* page count in cluster */
	अचिन्हित पूर्णांक log_cluster_size;	/* log of cluster size */
	काष्ठा page **rpages;		/* pages store raw data in cluster */
	अचिन्हित पूर्णांक nr_rpages;		/* total page number in rpages */
	काष्ठा page **cpages;		/* pages store compressed data in cluster */
	अचिन्हित पूर्णांक nr_cpages;		/* total page number in cpages */
	व्योम *rbuf;			/* भव mapped address on rpages */
	काष्ठा compress_data *cbuf;	/* भव mapped address on cpages */
	माप_प्रकार rlen;			/* valid data length in rbuf */
	माप_प्रकार clen;			/* valid data length in cbuf */
	व्योम *निजी;			/* payload buffer क्रम specअगरied compression algorithm */
	व्योम *निजी2;			/* extra payload buffer */
पूर्ण;

/* compress context क्रम ग_लिखो IO path */
काष्ठा compress_io_ctx अणु
	u32 magic;			/* magic number to indicate page is compressed */
	काष्ठा inode *inode;		/* inode the context beदीर्घ to */
	काष्ठा page **rpages;		/* pages store raw data in cluster */
	अचिन्हित पूर्णांक nr_rpages;		/* total page number in rpages */
	atomic_t pending_pages;		/* in-flight compressed page count */
पूर्ण;

/* Context क्रम decompressing one cluster on the पढ़ो IO path */
काष्ठा decompress_io_ctx अणु
	u32 magic;			/* magic number to indicate page is compressed */
	काष्ठा inode *inode;		/* inode the context beदीर्घ to */
	pgoff_t cluster_idx;		/* cluster index number */
	अचिन्हित पूर्णांक cluster_size;	/* page count in cluster */
	अचिन्हित पूर्णांक log_cluster_size;	/* log of cluster size */
	काष्ठा page **rpages;		/* pages store raw data in cluster */
	अचिन्हित पूर्णांक nr_rpages;		/* total page number in rpages */
	काष्ठा page **cpages;		/* pages store compressed data in cluster */
	अचिन्हित पूर्णांक nr_cpages;		/* total page number in cpages */
	काष्ठा page **tpages;		/* temp pages to pad holes in cluster */
	व्योम *rbuf;			/* भव mapped address on rpages */
	काष्ठा compress_data *cbuf;	/* भव mapped address on cpages */
	माप_प्रकार rlen;			/* valid data length in rbuf */
	माप_प्रकार clen;			/* valid data length in cbuf */

	/*
	 * The number of compressed pages reमुख्यing to be पढ़ो in this cluster.
	 * This is initially nr_cpages.  It is decremented by 1 each समय a page
	 * has been पढ़ो (or failed to be पढ़ो).  When it reaches 0, the cluster
	 * is decompressed (or an error is reported).
	 *
	 * If an error occurs beक्रमe all the pages have been submitted क्रम I/O,
	 * then this will never reach 0.  In this हाल the I/O submitter is
	 * responsible क्रम calling f2fs_decompress_end_io() instead.
	 */
	atomic_t reमुख्यing_pages;

	/*
	 * Number of references to this decompress_io_ctx.
	 *
	 * One reference is held क्रम I/O completion.  This reference is dropped
	 * after the pagecache pages are updated and unlocked -- either after
	 * decompression (and verity अगर enabled), or after an error.
	 *
	 * In addition, each compressed page holds a reference जबतक it is in a
	 * bio.  These references are necessary prevent compressed pages from
	 * being मुक्तd जबतक they are still in a bio.
	 */
	refcount_t refcnt;

	bool failed;			/* IO error occurred beक्रमe decompression? */
	bool need_verity;		/* need fs-verity verअगरication after decompression? */
	व्योम *निजी;			/* payload buffer क्रम specअगरied decompression algorithm */
	व्योम *निजी2;			/* extra payload buffer */
	काष्ठा work_काष्ठा verity_work;	/* work to verअगरy the decompressed pages */
पूर्ण;

#घोषणा शून्य_CLUSTER			((अचिन्हित पूर्णांक)(~0))
#घोषणा MIN_COMPRESS_LOG_SIZE		2
#घोषणा MAX_COMPRESS_LOG_SIZE		8
#घोषणा MAX_COMPRESS_WINDOW_SIZE(log_size)	((PAGE_SIZE) << (log_size))

काष्ठा f2fs_sb_info अणु
	काष्ठा super_block *sb;			/* poपूर्णांकer to VFS super block */
	काष्ठा proc_dir_entry *s_proc;		/* proc entry */
	काष्ठा f2fs_super_block *raw_super;	/* raw super block poपूर्णांकer */
	काष्ठा rw_semaphore sb_lock;		/* lock क्रम raw super block */
	पूर्णांक valid_super_block;			/* valid super block no */
	अचिन्हित दीर्घ s_flag;				/* flags क्रम sbi */
	काष्ठा mutex ग_लिखोpages;		/* mutex क्रम ग_लिखोpages() */

#अगर_घोषित CONFIG_BLK_DEV_ZONED
	अचिन्हित पूर्णांक blocks_per_blkz;		/* F2FS blocks per zone */
	अचिन्हित पूर्णांक log_blocks_per_blkz;	/* log2 F2FS blocks per zone */
#पूर्ण_अगर

	/* क्रम node-related operations */
	काष्ठा f2fs_nm_info *nm_info;		/* node manager */
	काष्ठा inode *node_inode;		/* cache node blocks */

	/* क्रम segment-related operations */
	काष्ठा f2fs_sm_info *sm_info;		/* segment manager */

	/* क्रम bio operations */
	काष्ठा f2fs_bio_info *ग_लिखो_io[NR_PAGE_TYPE];	/* क्रम ग_लिखो bios */
	/* keep migration IO order क्रम LFS mode */
	काष्ठा rw_semaphore io_order_lock;
	mempool_t *ग_लिखो_io_dummy;		/* Dummy pages */

	/* क्रम checkpoपूर्णांक */
	काष्ठा f2fs_checkpoपूर्णांक *ckpt;		/* raw checkpoपूर्णांक poपूर्णांकer */
	पूर्णांक cur_cp_pack;			/* reमुख्य current cp pack */
	spinlock_t cp_lock;			/* क्रम flag in ckpt */
	काष्ठा inode *meta_inode;		/* cache meta blocks */
	काष्ठा rw_semaphore cp_global_sem;	/* checkpoपूर्णांक procedure lock */
	काष्ठा rw_semaphore cp_rwsem;		/* blocking FS operations */
	काष्ठा rw_semaphore node_ग_लिखो;		/* locking node ग_लिखोs */
	काष्ठा rw_semaphore node_change;	/* locking node change */
	रुको_queue_head_t cp_रुको;
	अचिन्हित दीर्घ last_समय[MAX_TIME];	/* to store समय in jअगरfies */
	दीर्घ पूर्णांकerval_समय[MAX_TIME];		/* to store thresholds */
	काष्ठा ckpt_req_control cprc_info;	/* क्रम checkpoपूर्णांक request control */

	काष्ठा inode_management im[MAX_INO_ENTRY];	/* manage inode cache */

	spinlock_t fsync_node_lock;		/* क्रम node entry lock */
	काष्ठा list_head fsync_node_list;	/* node list head */
	अचिन्हित पूर्णांक fsync_seg_id;		/* sequence id */
	अचिन्हित पूर्णांक fsync_node_num;		/* number of node entries */

	/* क्रम orphan inode, use 0'th array */
	अचिन्हित पूर्णांक max_orphans;		/* max orphan inodes */

	/* क्रम inode management */
	काष्ठा list_head inode_list[NR_INODE_TYPE];	/* dirty inode list */
	spinlock_t inode_lock[NR_INODE_TYPE];	/* क्रम dirty inode list lock */
	काष्ठा mutex flush_lock;		/* क्रम flush exclusion */

	/* क्रम extent tree cache */
	काष्ठा radix_tree_root extent_tree_root;/* cache extent cache entries */
	काष्ठा mutex extent_tree_lock;	/* locking extent radix tree */
	काष्ठा list_head extent_list;		/* lru list क्रम shrinker */
	spinlock_t extent_lock;			/* locking extent lru list */
	atomic_t total_ext_tree;		/* extent tree count */
	काष्ठा list_head zombie_list;		/* extent zombie tree list */
	atomic_t total_zombie_tree;		/* extent zombie tree count */
	atomic_t total_ext_node;		/* extent info count */

	/* basic fileप्रणाली units */
	अचिन्हित पूर्णांक log_sectors_per_block;	/* log2 sectors per block */
	अचिन्हित पूर्णांक log_blocksize;		/* log2 block size */
	अचिन्हित पूर्णांक blocksize;			/* block size */
	अचिन्हित पूर्णांक root_ino_num;		/* root inode number*/
	अचिन्हित पूर्णांक node_ino_num;		/* node inode number*/
	अचिन्हित पूर्णांक meta_ino_num;		/* meta inode number*/
	अचिन्हित पूर्णांक log_blocks_per_seg;	/* log2 blocks per segment */
	अचिन्हित पूर्णांक blocks_per_seg;		/* blocks per segment */
	अचिन्हित पूर्णांक segs_per_sec;		/* segments per section */
	अचिन्हित पूर्णांक secs_per_zone;		/* sections per zone */
	अचिन्हित पूर्णांक total_sections;		/* total section count */
	अचिन्हित पूर्णांक total_node_count;		/* total node block count */
	अचिन्हित पूर्णांक total_valid_node_count;	/* valid node block count */
	पूर्णांक dir_level;				/* directory level */
	पूर्णांक सूची_पढ़ो_ra;				/* पढ़ोahead inode in सूची_पढ़ो */
	u64 max_io_bytes;			/* max io bytes to merge IOs */

	block_t user_block_count;		/* # of user blocks */
	block_t total_valid_block_count;	/* # of valid blocks */
	block_t discard_blks;			/* discard command candidats */
	block_t last_valid_block_count;		/* क्रम recovery */
	block_t reserved_blocks;		/* configurable reserved blocks */
	block_t current_reserved_blocks;	/* current reserved blocks */

	/* Additional tracking क्रम no checkpoपूर्णांक mode */
	block_t unusable_block_count;		/* # of blocks saved by last cp */

	अचिन्हित पूर्णांक nquota_files;		/* # of quota sysfile */
	काष्ठा rw_semaphore quota_sem;		/* blocking cp क्रम flags */

	/* # of pages, see count_type */
	atomic_t nr_pages[NR_COUNT_TYPE];
	/* # of allocated blocks */
	काष्ठा percpu_counter alloc_valid_block_count;

	/* ग_लिखोback control */
	atomic_t wb_sync_req[META];	/* count # of WB_SYNC thपढ़ोs */

	/* valid inode count */
	काष्ठा percpu_counter total_valid_inode_count;

	काष्ठा f2fs_mount_info mount_opt;	/* mount options */

	/* क्रम cleaning operations */
	काष्ठा rw_semaphore gc_lock;		/*
						 * semaphore क्रम GC, aव्योम
						 * race between GC and GC or CP
						 */
	काष्ठा f2fs_gc_kthपढ़ो	*gc_thपढ़ो;	/* GC thपढ़ो */
	काष्ठा atgc_management am;		/* atgc management */
	अचिन्हित पूर्णांक cur_victim_sec;		/* current victim section num */
	अचिन्हित पूर्णांक gc_mode;			/* current GC state */
	अचिन्हित पूर्णांक next_victim_seg[2];	/* next segment in victim section */

	/* क्रम skip statistic */
	अचिन्हित पूर्णांक atomic_files;		/* # of खोलोed atomic file */
	अचिन्हित दीर्घ दीर्घ skipped_atomic_files[2];	/* FG_GC and BG_GC */
	अचिन्हित दीर्घ दीर्घ skipped_gc_rwsem;		/* FG_GC only */

	/* threshold क्रम gc trials on pinned files */
	u64 gc_pin_file_threshold;
	काष्ठा rw_semaphore pin_sem;

	/* maximum # of trials to find a victim segment क्रम SSR and GC */
	अचिन्हित पूर्णांक max_victim_search;
	/* migration granularity of garbage collection, unit: segment */
	अचिन्हित पूर्णांक migration_granularity;

	/*
	 * क्रम stat inक्रमmation.
	 * one is क्रम the LFS mode, and the other is क्रम the SSR mode.
	 */
#अगर_घोषित CONFIG_F2FS_STAT_FS
	काष्ठा f2fs_stat_info *stat_info;	/* FS status inक्रमmation */
	atomic_t meta_count[META_MAX];		/* # of meta blocks */
	अचिन्हित पूर्णांक segment_count[2];		/* # of allocated segments */
	अचिन्हित पूर्णांक block_count[2];		/* # of allocated blocks */
	atomic_t inplace_count;		/* # of inplace update */
	atomic64_t total_hit_ext;		/* # of lookup extent cache */
	atomic64_t पढ़ो_hit_rbtree;		/* # of hit rbtree extent node */
	atomic64_t पढ़ो_hit_largest;		/* # of hit largest extent node */
	atomic64_t पढ़ो_hit_cached;		/* # of hit cached extent node */
	atomic_t अंतरभूत_xattr;			/* # of अंतरभूत_xattr inodes */
	atomic_t अंतरभूत_inode;			/* # of अंतरभूत_data inodes */
	atomic_t अंतरभूत_dir;			/* # of अंतरभूत_dentry inodes */
	atomic_t compr_inode;			/* # of compressed inodes */
	atomic64_t compr_blocks;		/* # of compressed blocks */
	atomic_t vw_cnt;			/* # of अस्थिर ग_लिखोs */
	atomic_t max_aw_cnt;			/* max # of atomic ग_लिखोs */
	atomic_t max_vw_cnt;			/* max # of अस्थिर ग_लिखोs */
	अचिन्हित पूर्णांक io_skip_bggc;		/* skip background gc क्रम in-flight IO */
	अचिन्हित पूर्णांक other_skip_bggc;		/* skip background gc क्रम other reasons */
	अचिन्हित पूर्णांक ndirty_inode[NR_INODE_TYPE];	/* # of dirty inodes */
#पूर्ण_अगर
	spinlock_t stat_lock;			/* lock क्रम stat operations */

	/* For app/fs IO statistics */
	spinlock_t iostat_lock;
	अचिन्हित दीर्घ दीर्घ rw_iostat[NR_IO_TYPE];
	अचिन्हित दीर्घ दीर्घ prev_rw_iostat[NR_IO_TYPE];
	bool iostat_enable;
	अचिन्हित दीर्घ iostat_next_period;
	अचिन्हित पूर्णांक iostat_period_ms;

	/* to attach REQ_META|REQ_FUA flags */
	अचिन्हित पूर्णांक data_io_flag;
	अचिन्हित पूर्णांक node_io_flag;

	/* For sysfs suppport */
	काष्ठा kobject s_kobj;			/* /sys/fs/f2fs/<devname> */
	काष्ठा completion s_kobj_unरेजिस्टर;

	काष्ठा kobject s_stat_kobj;		/* /sys/fs/f2fs/<devname>/stat */
	काष्ठा completion s_stat_kobj_unरेजिस्टर;

	/* For shrinker support */
	काष्ठा list_head s_list;
	पूर्णांक s_ndevs;				/* number of devices */
	काष्ठा f2fs_dev_info *devs;		/* क्रम device list */
	अचिन्हित पूर्णांक dirty_device;		/* क्रम checkpoपूर्णांक data flush */
	spinlock_t dev_lock;			/* protect dirty_device */
	काष्ठा mutex umount_mutex;
	अचिन्हित पूर्णांक shrinker_run_no;

	/* For ग_लिखो statistics */
	u64 sectors_written_start;
	u64 kbytes_written;

	/* Reference to checksum algorithm driver via cryptoapi */
	काष्ठा crypto_shash *s_chksum_driver;

	/* Precomputed FS UUID checksum क्रम seeding other checksums */
	__u32 s_chksum_seed;

	काष्ठा workqueue_काष्ठा *post_पढ़ो_wq;	/* post पढ़ो workqueue */

	काष्ठा kmem_cache *अंतरभूत_xattr_slab;	/* अंतरभूत xattr entry */
	अचिन्हित पूर्णांक अंतरभूत_xattr_slab_size;	/* शेष अंतरभूत xattr slab size */

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	काष्ठा kmem_cache *page_array_slab;	/* page array entry */
	अचिन्हित पूर्णांक page_array_slab_size;	/* शेष page array slab size */

	/* For runसमय compression statistics */
	u64 compr_written_block;
	u64 compr_saved_block;
	u32 compr_new_inode;
#पूर्ण_अगर
पूर्ण;

काष्ठा f2fs_निजी_dio अणु
	काष्ठा inode *inode;
	व्योम *orig_निजी;
	bio_end_io_t *orig_end_io;
	bool ग_लिखो;
पूर्ण;

#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
#घोषणा f2fs_show_injection_info(sbi, type)					\
	prपूर्णांकk_ratelimited("%sF2FS-fs (%s) : inject %s in %s of %pS\n",	\
		KERN_INFO, sbi->sb->s_id,				\
		f2fs_fault_name[type],					\
		__func__, __builtin_वापस_address(0))
अटल अंतरभूत bool समय_प्रकारo_inject(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	काष्ठा f2fs_fault_info *ffi = &F2FS_OPTION(sbi).fault_info;

	अगर (!ffi->inject_rate)
		वापस false;

	अगर (!IS_FAULT_SET(ffi, type))
		वापस false;

	atomic_inc(&ffi->inject_ops);
	अगर (atomic_पढ़ो(&ffi->inject_ops) >= ffi->inject_rate) अणु
		atomic_set(&ffi->inject_ops, 0);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
#अन्यथा
#घोषणा f2fs_show_injection_info(sbi, type) करो अणु पूर्ण जबतक (0)
अटल अंतरभूत bool समय_प्रकारo_inject(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Test अगर the mounted volume is a multi-device volume.
 *   - For a single regular disk volume, sbi->s_ndevs is 0.
 *   - For a single zoned disk volume, sbi->s_ndevs is 1.
 *   - For a multi-device volume, sbi->s_ndevs is always 2 or more.
 */
अटल अंतरभूत bool f2fs_is_multi_device(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस sbi->s_ndevs > 1;
पूर्ण

अटल अंतरभूत व्योम f2fs_update_समय(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	अचिन्हित दीर्घ now = jअगरfies;

	sbi->last_समय[type] = now;

	/* DISCARD_TIME and GC_TIME are based on REQ_TIME */
	अगर (type == REQ_TIME) अणु
		sbi->last_समय[DISCARD_TIME] = now;
		sbi->last_समय[GC_TIME] = now;
	पूर्ण
पूर्ण

अटल अंतरभूत bool f2fs_समय_over(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	अचिन्हित दीर्घ पूर्णांकerval = sbi->पूर्णांकerval_समय[type] * HZ;

	वापस समय_after(jअगरfies, sbi->last_समय[type] + पूर्णांकerval);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक f2fs_समय_प्रकारo_रुको(काष्ठा f2fs_sb_info *sbi,
						पूर्णांक type)
अणु
	अचिन्हित दीर्घ पूर्णांकerval = sbi->पूर्णांकerval_समय[type] * HZ;
	अचिन्हित पूर्णांक रुको_ms = 0;
	दीर्घ delta;

	delta = (sbi->last_समय[type] + पूर्णांकerval) - jअगरfies;
	अगर (delta > 0)
		रुको_ms = jअगरfies_to_msecs(delta);

	वापस रुको_ms;
पूर्ण

/*
 * Inline functions
 */
अटल अंतरभूत u32 __f2fs_crc32(काष्ठा f2fs_sb_info *sbi, u32 crc,
			      स्थिर व्योम *address, अचिन्हित पूर्णांक length)
अणु
	काष्ठा अणु
		काष्ठा shash_desc shash;
		अक्षर ctx[4];
	पूर्ण desc;
	पूर्णांक err;

	BUG_ON(crypto_shash_descsize(sbi->s_chksum_driver) != माप(desc.ctx));

	desc.shash.tfm = sbi->s_chksum_driver;
	*(u32 *)desc.ctx = crc;

	err = crypto_shash_update(&desc.shash, address, length);
	BUG_ON(err);

	वापस *(u32 *)desc.ctx;
पूर्ण

अटल अंतरभूत u32 f2fs_crc32(काष्ठा f2fs_sb_info *sbi, स्थिर व्योम *address,
			   अचिन्हित पूर्णांक length)
अणु
	वापस __f2fs_crc32(sbi, F2FS_SUPER_MAGIC, address, length);
पूर्ण

अटल अंतरभूत bool f2fs_crc_valid(काष्ठा f2fs_sb_info *sbi, __u32 blk_crc,
				  व्योम *buf, माप_प्रकार buf_size)
अणु
	वापस f2fs_crc32(sbi, buf, buf_size) == blk_crc;
पूर्ण

अटल अंतरभूत u32 f2fs_chksum(काष्ठा f2fs_sb_info *sbi, u32 crc,
			      स्थिर व्योम *address, अचिन्हित पूर्णांक length)
अणु
	वापस __f2fs_crc32(sbi, crc, address, length);
पूर्ण

अटल अंतरभूत काष्ठा f2fs_inode_info *F2FS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा f2fs_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा f2fs_sb_info *F2FS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा f2fs_sb_info *F2FS_I_SB(काष्ठा inode *inode)
अणु
	वापस F2FS_SB(inode->i_sb);
पूर्ण

अटल अंतरभूत काष्ठा f2fs_sb_info *F2FS_M_SB(काष्ठा address_space *mapping)
अणु
	वापस F2FS_I_SB(mapping->host);
पूर्ण

अटल अंतरभूत काष्ठा f2fs_sb_info *F2FS_P_SB(काष्ठा page *page)
अणु
	वापस F2FS_M_SB(page_file_mapping(page));
पूर्ण

अटल अंतरभूत काष्ठा f2fs_super_block *F2FS_RAW_SUPER(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (काष्ठा f2fs_super_block *)(sbi->raw_super);
पूर्ण

अटल अंतरभूत काष्ठा f2fs_checkpoपूर्णांक *F2FS_CKPT(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (काष्ठा f2fs_checkpoपूर्णांक *)(sbi->ckpt);
पूर्ण

अटल अंतरभूत काष्ठा f2fs_node *F2FS_NODE(काष्ठा page *page)
अणु
	वापस (काष्ठा f2fs_node *)page_address(page);
पूर्ण

अटल अंतरभूत काष्ठा f2fs_inode *F2FS_INODE(काष्ठा page *page)
अणु
	वापस &((काष्ठा f2fs_node *)page_address(page))->i;
पूर्ण

अटल अंतरभूत काष्ठा f2fs_nm_info *NM_I(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (काष्ठा f2fs_nm_info *)(sbi->nm_info);
पूर्ण

अटल अंतरभूत काष्ठा f2fs_sm_info *SM_I(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (काष्ठा f2fs_sm_info *)(sbi->sm_info);
पूर्ण

अटल अंतरभूत काष्ठा sit_info *SIT_I(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (काष्ठा sit_info *)(SM_I(sbi)->sit_info);
पूर्ण

अटल अंतरभूत काष्ठा मुक्त_segmap_info *FREE_I(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (काष्ठा मुक्त_segmap_info *)(SM_I(sbi)->मुक्त_info);
पूर्ण

अटल अंतरभूत काष्ठा dirty_seglist_info *सूचीTY_I(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (काष्ठा dirty_seglist_info *)(SM_I(sbi)->dirty_info);
पूर्ण

अटल अंतरभूत काष्ठा address_space *META_MAPPING(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस sbi->meta_inode->i_mapping;
पूर्ण

अटल अंतरभूत काष्ठा address_space *NODE_MAPPING(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस sbi->node_inode->i_mapping;
पूर्ण

अटल अंतरभूत bool is_sbi_flag_set(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक type)
अणु
	वापस test_bit(type, &sbi->s_flag);
पूर्ण

अटल अंतरभूत व्योम set_sbi_flag(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक type)
अणु
	set_bit(type, &sbi->s_flag);
पूर्ण

अटल अंतरभूत व्योम clear_sbi_flag(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक type)
अणु
	clear_bit(type, &sbi->s_flag);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ cur_cp_version(काष्ठा f2fs_checkpoपूर्णांक *cp)
अणु
	वापस le64_to_cpu(cp->checkpoपूर्णांक_ver);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ f2fs_qf_ino(काष्ठा super_block *sb, पूर्णांक type)
अणु
	अगर (type < F2FS_MAX_QUOTAS)
		वापस le32_to_cpu(F2FS_SB(sb)->raw_super->qf_ino[type]);
	वापस 0;
पूर्ण

अटल अंतरभूत __u64 cur_cp_crc(काष्ठा f2fs_checkpoपूर्णांक *cp)
अणु
	माप_प्रकार crc_offset = le32_to_cpu(cp->checksum_offset);
	वापस le32_to_cpu(*((__le32 *)((अचिन्हित अक्षर *)cp + crc_offset)));
पूर्ण

अटल अंतरभूत bool __is_set_ckpt_flags(काष्ठा f2fs_checkpoपूर्णांक *cp, अचिन्हित पूर्णांक f)
अणु
	अचिन्हित पूर्णांक ckpt_flags = le32_to_cpu(cp->ckpt_flags);

	वापस ckpt_flags & f;
पूर्ण

अटल अंतरभूत bool is_set_ckpt_flags(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक f)
अणु
	वापस __is_set_ckpt_flags(F2FS_CKPT(sbi), f);
पूर्ण

अटल अंतरभूत व्योम __set_ckpt_flags(काष्ठा f2fs_checkpoपूर्णांक *cp, अचिन्हित पूर्णांक f)
अणु
	अचिन्हित पूर्णांक ckpt_flags;

	ckpt_flags = le32_to_cpu(cp->ckpt_flags);
	ckpt_flags |= f;
	cp->ckpt_flags = cpu_to_le32(ckpt_flags);
पूर्ण

अटल अंतरभूत व्योम set_ckpt_flags(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक f)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sbi->cp_lock, flags);
	__set_ckpt_flags(F2FS_CKPT(sbi), f);
	spin_unlock_irqrestore(&sbi->cp_lock, flags);
पूर्ण

अटल अंतरभूत व्योम __clear_ckpt_flags(काष्ठा f2fs_checkpoपूर्णांक *cp, अचिन्हित पूर्णांक f)
अणु
	अचिन्हित पूर्णांक ckpt_flags;

	ckpt_flags = le32_to_cpu(cp->ckpt_flags);
	ckpt_flags &= (~f);
	cp->ckpt_flags = cpu_to_le32(ckpt_flags);
पूर्ण

अटल अंतरभूत व्योम clear_ckpt_flags(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक f)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sbi->cp_lock, flags);
	__clear_ckpt_flags(F2FS_CKPT(sbi), f);
	spin_unlock_irqrestore(&sbi->cp_lock, flags);
पूर्ण

अटल अंतरभूत व्योम disable_nat_bits(काष्ठा f2fs_sb_info *sbi, bool lock)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर *nat_bits;

	/*
	 * In order to re-enable nat_bits we need to call fsck.f2fs by
	 * set_sbi_flag(sbi, SBI_NEED_FSCK). But it may give huge cost,
	 * so let's rely on regular fsck or unclean shutकरोwn.
	 */

	अगर (lock)
		spin_lock_irqsave(&sbi->cp_lock, flags);
	__clear_ckpt_flags(F2FS_CKPT(sbi), CP_NAT_BITS_FLAG);
	nat_bits = NM_I(sbi)->nat_bits;
	NM_I(sbi)->nat_bits = शून्य;
	अगर (lock)
		spin_unlock_irqrestore(&sbi->cp_lock, flags);

	kvमुक्त(nat_bits);
पूर्ण

अटल अंतरभूत bool enabled_nat_bits(काष्ठा f2fs_sb_info *sbi,
					काष्ठा cp_control *cpc)
अणु
	bool set = is_set_ckpt_flags(sbi, CP_NAT_BITS_FLAG);

	वापस (cpc) ? (cpc->reason & CP_UMOUNT) && set : set;
पूर्ण

अटल अंतरभूत व्योम f2fs_lock_op(काष्ठा f2fs_sb_info *sbi)
अणु
	करोwn_पढ़ो(&sbi->cp_rwsem);
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_trylock_op(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस करोwn_पढ़ो_trylock(&sbi->cp_rwsem);
पूर्ण

अटल अंतरभूत व्योम f2fs_unlock_op(काष्ठा f2fs_sb_info *sbi)
अणु
	up_पढ़ो(&sbi->cp_rwsem);
पूर्ण

अटल अंतरभूत व्योम f2fs_lock_all(काष्ठा f2fs_sb_info *sbi)
अणु
	करोwn_ग_लिखो(&sbi->cp_rwsem);
पूर्ण

अटल अंतरभूत व्योम f2fs_unlock_all(काष्ठा f2fs_sb_info *sbi)
अणु
	up_ग_लिखो(&sbi->cp_rwsem);
पूर्ण

अटल अंतरभूत पूर्णांक __get_cp_reason(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक reason = CP_SYNC;

	अगर (test_opt(sbi, FASTBOOT))
		reason = CP_FASTBOOT;
	अगर (is_sbi_flag_set(sbi, SBI_IS_CLOSE))
		reason = CP_UMOUNT;
	वापस reason;
पूर्ण

अटल अंतरभूत bool __reमुख्य_node_summaries(पूर्णांक reason)
अणु
	वापस (reason & (CP_UMOUNT | CP_FASTBOOT));
पूर्ण

अटल अंतरभूत bool __exist_node_summaries(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (is_set_ckpt_flags(sbi, CP_UMOUNT_FLAG) ||
			is_set_ckpt_flags(sbi, CP_FASTBOOT_FLAG));
पूर्ण

/*
 * Check whether the inode has blocks or not
 */
अटल अंतरभूत पूर्णांक F2FS_HAS_BLOCKS(काष्ठा inode *inode)
अणु
	block_t xattr_block = F2FS_I(inode)->i_xattr_nid ? 1 : 0;

	वापस (inode->i_blocks >> F2FS_LOG_SECTORS_PER_BLOCK) > xattr_block;
पूर्ण

अटल अंतरभूत bool f2fs_has_xattr_block(अचिन्हित पूर्णांक ofs)
अणु
	वापस ofs == XATTR_NODE_OFFSET;
पूर्ण

अटल अंतरभूत bool __allow_reserved_blocks(काष्ठा f2fs_sb_info *sbi,
					काष्ठा inode *inode, bool cap)
अणु
	अगर (!inode)
		वापस true;
	अगर (!test_opt(sbi, RESERVE_ROOT))
		वापस false;
	अगर (IS_NOQUOTA(inode))
		वापस true;
	अगर (uid_eq(F2FS_OPTION(sbi).s_resuid, current_fsuid()))
		वापस true;
	अगर (!gid_eq(F2FS_OPTION(sbi).s_resgid, GLOBAL_ROOT_GID) &&
					in_group_p(F2FS_OPTION(sbi).s_resgid))
		वापस true;
	अगर (cap && capable(CAP_SYS_RESOURCE))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत व्योम f2fs_i_blocks_ग_लिखो(काष्ठा inode *, block_t, bool, bool);
अटल अंतरभूत पूर्णांक inc_valid_block_count(काष्ठा f2fs_sb_info *sbi,
				 काष्ठा inode *inode, blkcnt_t *count)
अणु
	blkcnt_t dअगरf = 0, release = 0;
	block_t avail_user_block_count;
	पूर्णांक ret;

	ret = dquot_reserve_block(inode, *count);
	अगर (ret)
		वापस ret;

	अगर (समय_प्रकारo_inject(sbi, FAULT_BLOCK)) अणु
		f2fs_show_injection_info(sbi, FAULT_BLOCK);
		release = *count;
		जाओ release_quota;
	पूर्ण

	/*
	 * let's increase this in prior to actual block count change in order
	 * क्रम f2fs_sync_file to aव्योम data races when deciding checkpoपूर्णांक.
	 */
	percpu_counter_add(&sbi->alloc_valid_block_count, (*count));

	spin_lock(&sbi->stat_lock);
	sbi->total_valid_block_count += (block_t)(*count);
	avail_user_block_count = sbi->user_block_count -
					sbi->current_reserved_blocks;

	अगर (!__allow_reserved_blocks(sbi, inode, true))
		avail_user_block_count -= F2FS_OPTION(sbi).root_reserved_blocks;
	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) अणु
		अगर (avail_user_block_count > sbi->unusable_block_count)
			avail_user_block_count -= sbi->unusable_block_count;
		अन्यथा
			avail_user_block_count = 0;
	पूर्ण
	अगर (unlikely(sbi->total_valid_block_count > avail_user_block_count)) अणु
		dअगरf = sbi->total_valid_block_count - avail_user_block_count;
		अगर (dअगरf > *count)
			dअगरf = *count;
		*count -= dअगरf;
		release = dअगरf;
		sbi->total_valid_block_count -= dअगरf;
		अगर (!*count) अणु
			spin_unlock(&sbi->stat_lock);
			जाओ enospc;
		पूर्ण
	पूर्ण
	spin_unlock(&sbi->stat_lock);

	अगर (unlikely(release)) अणु
		percpu_counter_sub(&sbi->alloc_valid_block_count, release);
		dquot_release_reservation_block(inode, release);
	पूर्ण
	f2fs_i_blocks_ग_लिखो(inode, *count, true, true);
	वापस 0;

enospc:
	percpu_counter_sub(&sbi->alloc_valid_block_count, release);
release_quota:
	dquot_release_reservation_block(inode, release);
	वापस -ENOSPC;
पूर्ण

__म_लिखो(2, 3)
व्योम f2fs_prपूर्णांकk(काष्ठा f2fs_sb_info *sbi, स्थिर अक्षर *fmt, ...);

#घोषणा f2fs_err(sbi, fmt, ...)						\
	f2fs_prपूर्णांकk(sbi, KERN_ERR fmt, ##__VA_ARGS__)
#घोषणा f2fs_warn(sbi, fmt, ...)					\
	f2fs_prपूर्णांकk(sbi, KERN_WARNING fmt, ##__VA_ARGS__)
#घोषणा f2fs_notice(sbi, fmt, ...)					\
	f2fs_prपूर्णांकk(sbi, KERN_NOTICE fmt, ##__VA_ARGS__)
#घोषणा f2fs_info(sbi, fmt, ...)					\
	f2fs_prपूर्णांकk(sbi, KERN_INFO fmt, ##__VA_ARGS__)
#घोषणा f2fs_debug(sbi, fmt, ...)					\
	f2fs_prपूर्णांकk(sbi, KERN_DEBUG fmt, ##__VA_ARGS__)

अटल अंतरभूत व्योम dec_valid_block_count(काष्ठा f2fs_sb_info *sbi,
						काष्ठा inode *inode,
						block_t count)
अणु
	blkcnt_t sectors = count << F2FS_LOG_SECTORS_PER_BLOCK;

	spin_lock(&sbi->stat_lock);
	f2fs_bug_on(sbi, sbi->total_valid_block_count < (block_t) count);
	sbi->total_valid_block_count -= (block_t)count;
	अगर (sbi->reserved_blocks &&
		sbi->current_reserved_blocks < sbi->reserved_blocks)
		sbi->current_reserved_blocks = min(sbi->reserved_blocks,
					sbi->current_reserved_blocks + count);
	spin_unlock(&sbi->stat_lock);
	अगर (unlikely(inode->i_blocks < sectors)) अणु
		f2fs_warn(sbi, "Inconsistent i_blocks, ino:%lu, iblocks:%llu, sectors:%llu",
			  inode->i_ino,
			  (अचिन्हित दीर्घ दीर्घ)inode->i_blocks,
			  (अचिन्हित दीर्घ दीर्घ)sectors);
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		वापस;
	पूर्ण
	f2fs_i_blocks_ग_लिखो(inode, count, false, true);
पूर्ण

अटल अंतरभूत व्योम inc_page_count(काष्ठा f2fs_sb_info *sbi, पूर्णांक count_type)
अणु
	atomic_inc(&sbi->nr_pages[count_type]);

	अगर (count_type == F2FS_सूचीTY_DENTS ||
			count_type == F2FS_सूचीTY_NODES ||
			count_type == F2FS_सूचीTY_META ||
			count_type == F2FS_सूचीTY_QDATA ||
			count_type == F2FS_सूचीTY_IMETA)
		set_sbi_flag(sbi, SBI_IS_सूचीTY);
पूर्ण

अटल अंतरभूत व्योम inode_inc_dirty_pages(काष्ठा inode *inode)
अणु
	atomic_inc(&F2FS_I(inode)->dirty_pages);
	inc_page_count(F2FS_I_SB(inode), S_ISसूची(inode->i_mode) ?
				F2FS_सूचीTY_DENTS : F2FS_सूचीTY_DATA);
	अगर (IS_NOQUOTA(inode))
		inc_page_count(F2FS_I_SB(inode), F2FS_सूचीTY_QDATA);
पूर्ण

अटल अंतरभूत व्योम dec_page_count(काष्ठा f2fs_sb_info *sbi, पूर्णांक count_type)
अणु
	atomic_dec(&sbi->nr_pages[count_type]);
पूर्ण

अटल अंतरभूत व्योम inode_dec_dirty_pages(काष्ठा inode *inode)
अणु
	अगर (!S_ISसूची(inode->i_mode) && !S_ISREG(inode->i_mode) &&
			!S_ISLNK(inode->i_mode))
		वापस;

	atomic_dec(&F2FS_I(inode)->dirty_pages);
	dec_page_count(F2FS_I_SB(inode), S_ISसूची(inode->i_mode) ?
				F2FS_सूचीTY_DENTS : F2FS_सूचीTY_DATA);
	अगर (IS_NOQUOTA(inode))
		dec_page_count(F2FS_I_SB(inode), F2FS_सूचीTY_QDATA);
पूर्ण

अटल अंतरभूत s64 get_pages(काष्ठा f2fs_sb_info *sbi, पूर्णांक count_type)
अणु
	वापस atomic_पढ़ो(&sbi->nr_pages[count_type]);
पूर्ण

अटल अंतरभूत पूर्णांक get_dirty_pages(काष्ठा inode *inode)
अणु
	वापस atomic_पढ़ो(&F2FS_I(inode)->dirty_pages);
पूर्ण

अटल अंतरभूत पूर्णांक get_blocktype_secs(काष्ठा f2fs_sb_info *sbi, पूर्णांक block_type)
अणु
	अचिन्हित पूर्णांक pages_per_sec = sbi->segs_per_sec * sbi->blocks_per_seg;
	अचिन्हित पूर्णांक segs = (get_pages(sbi, block_type) + pages_per_sec - 1) >>
						sbi->log_blocks_per_seg;

	वापस segs / sbi->segs_per_sec;
पूर्ण

अटल अंतरभूत block_t valid_user_blocks(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस sbi->total_valid_block_count;
पूर्ण

अटल अंतरभूत block_t discard_blocks(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस sbi->discard_blks;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __biपंचांगap_size(काष्ठा f2fs_sb_info *sbi, पूर्णांक flag)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);

	/* वापस NAT or SIT biपंचांगap */
	अगर (flag == NAT_BITMAP)
		वापस le32_to_cpu(ckpt->nat_ver_biपंचांगap_bytesize);
	अन्यथा अगर (flag == SIT_BITMAP)
		वापस le32_to_cpu(ckpt->sit_ver_biपंचांगap_bytesize);

	वापस 0;
पूर्ण

अटल अंतरभूत block_t __cp_payload(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस le32_to_cpu(F2FS_RAW_SUPER(sbi)->cp_payload);
पूर्ण

अटल अंतरभूत व्योम *__biपंचांगap_ptr(काष्ठा f2fs_sb_info *sbi, पूर्णांक flag)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(sbi);
	व्योम *पंचांगp_ptr = &ckpt->sit_nat_version_biपंचांगap;
	पूर्णांक offset;

	अगर (is_set_ckpt_flags(sbi, CP_LARGE_NAT_BITMAP_FLAG)) अणु
		offset = (flag == SIT_BITMAP) ?
			le32_to_cpu(ckpt->nat_ver_biपंचांगap_bytesize) : 0;
		/*
		 * अगर large_nat_biपंचांगap feature is enabled, leave checksum
		 * protection क्रम all nat/sit biपंचांगaps.
		 */
		वापस पंचांगp_ptr + offset + माप(__le32);
	पूर्ण

	अगर (__cp_payload(sbi) > 0) अणु
		अगर (flag == NAT_BITMAP)
			वापस &ckpt->sit_nat_version_biपंचांगap;
		अन्यथा
			वापस (अचिन्हित अक्षर *)ckpt + F2FS_BLKSIZE;
	पूर्ण अन्यथा अणु
		offset = (flag == NAT_BITMAP) ?
			le32_to_cpu(ckpt->sit_ver_biपंचांगap_bytesize) : 0;
		वापस पंचांगp_ptr + offset;
	पूर्ण
पूर्ण

अटल अंतरभूत block_t __start_cp_addr(काष्ठा f2fs_sb_info *sbi)
अणु
	block_t start_addr = le32_to_cpu(F2FS_RAW_SUPER(sbi)->cp_blkaddr);

	अगर (sbi->cur_cp_pack == 2)
		start_addr += sbi->blocks_per_seg;
	वापस start_addr;
पूर्ण

अटल अंतरभूत block_t __start_cp_next_addr(काष्ठा f2fs_sb_info *sbi)
अणु
	block_t start_addr = le32_to_cpu(F2FS_RAW_SUPER(sbi)->cp_blkaddr);

	अगर (sbi->cur_cp_pack == 1)
		start_addr += sbi->blocks_per_seg;
	वापस start_addr;
पूर्ण

अटल अंतरभूत व्योम __set_cp_next_pack(काष्ठा f2fs_sb_info *sbi)
अणु
	sbi->cur_cp_pack = (sbi->cur_cp_pack == 1) ? 2 : 1;
पूर्ण

अटल अंतरभूत block_t __start_sum_addr(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस le32_to_cpu(F2FS_CKPT(sbi)->cp_pack_start_sum);
पूर्ण

अटल अंतरभूत पूर्णांक inc_valid_node_count(काष्ठा f2fs_sb_info *sbi,
					काष्ठा inode *inode, bool is_inode)
अणु
	block_t	valid_block_count;
	अचिन्हित पूर्णांक valid_node_count, user_block_count;
	पूर्णांक err;

	अगर (is_inode) अणु
		अगर (inode) अणु
			err = dquot_alloc_inode(inode);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = dquot_reserve_block(inode, 1);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (समय_प्रकारo_inject(sbi, FAULT_BLOCK)) अणु
		f2fs_show_injection_info(sbi, FAULT_BLOCK);
		जाओ enospc;
	पूर्ण

	spin_lock(&sbi->stat_lock);

	valid_block_count = sbi->total_valid_block_count +
					sbi->current_reserved_blocks + 1;

	अगर (!__allow_reserved_blocks(sbi, inode, false))
		valid_block_count += F2FS_OPTION(sbi).root_reserved_blocks;
	user_block_count = sbi->user_block_count;
	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		user_block_count -= sbi->unusable_block_count;

	अगर (unlikely(valid_block_count > user_block_count)) अणु
		spin_unlock(&sbi->stat_lock);
		जाओ enospc;
	पूर्ण

	valid_node_count = sbi->total_valid_node_count + 1;
	अगर (unlikely(valid_node_count > sbi->total_node_count)) अणु
		spin_unlock(&sbi->stat_lock);
		जाओ enospc;
	पूर्ण

	sbi->total_valid_node_count++;
	sbi->total_valid_block_count++;
	spin_unlock(&sbi->stat_lock);

	अगर (inode) अणु
		अगर (is_inode)
			f2fs_mark_inode_dirty_sync(inode, true);
		अन्यथा
			f2fs_i_blocks_ग_लिखो(inode, 1, true, true);
	पूर्ण

	percpu_counter_inc(&sbi->alloc_valid_block_count);
	वापस 0;

enospc:
	अगर (is_inode) अणु
		अगर (inode)
			dquot_मुक्त_inode(inode);
	पूर्ण अन्यथा अणु
		dquot_release_reservation_block(inode, 1);
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल अंतरभूत व्योम dec_valid_node_count(काष्ठा f2fs_sb_info *sbi,
					काष्ठा inode *inode, bool is_inode)
अणु
	spin_lock(&sbi->stat_lock);

	f2fs_bug_on(sbi, !sbi->total_valid_block_count);
	f2fs_bug_on(sbi, !sbi->total_valid_node_count);

	sbi->total_valid_node_count--;
	sbi->total_valid_block_count--;
	अगर (sbi->reserved_blocks &&
		sbi->current_reserved_blocks < sbi->reserved_blocks)
		sbi->current_reserved_blocks++;

	spin_unlock(&sbi->stat_lock);

	अगर (is_inode) अणु
		dquot_मुक्त_inode(inode);
	पूर्ण अन्यथा अणु
		अगर (unlikely(inode->i_blocks == 0)) अणु
			f2fs_warn(sbi, "dec_valid_node_count: inconsistent i_blocks, ino:%lu, iblocks:%llu",
				  inode->i_ino,
				  (अचिन्हित दीर्घ दीर्घ)inode->i_blocks);
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			वापस;
		पूर्ण
		f2fs_i_blocks_ग_लिखो(inode, 1, false, true);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक valid_node_count(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस sbi->total_valid_node_count;
पूर्ण

अटल अंतरभूत व्योम inc_valid_inode_count(काष्ठा f2fs_sb_info *sbi)
अणु
	percpu_counter_inc(&sbi->total_valid_inode_count);
पूर्ण

अटल अंतरभूत व्योम dec_valid_inode_count(काष्ठा f2fs_sb_info *sbi)
अणु
	percpu_counter_dec(&sbi->total_valid_inode_count);
पूर्ण

अटल अंतरभूत s64 valid_inode_count(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस percpu_counter_sum_positive(&sbi->total_valid_inode_count);
पूर्ण

अटल अंतरभूत काष्ठा page *f2fs_grab_cache_page(काष्ठा address_space *mapping,
						pgoff_t index, bool क्रम_ग_लिखो)
अणु
	काष्ठा page *page;

	अगर (IS_ENABLED(CONFIG_F2FS_FAULT_INJECTION)) अणु
		अगर (!क्रम_ग_लिखो)
			page = find_get_page_flags(mapping, index,
							FGP_LOCK | FGP_ACCESSED);
		अन्यथा
			page = find_lock_page(mapping, index);
		अगर (page)
			वापस page;

		अगर (समय_प्रकारo_inject(F2FS_M_SB(mapping), FAULT_PAGE_ALLOC)) अणु
			f2fs_show_injection_info(F2FS_M_SB(mapping),
							FAULT_PAGE_ALLOC);
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (!क्रम_ग_लिखो)
		वापस grab_cache_page(mapping, index);
	वापस grab_cache_page_ग_लिखो_begin(mapping, index, AOP_FLAG_NOFS);
पूर्ण

अटल अंतरभूत काष्ठा page *f2fs_pagecache_get_page(
				काष्ठा address_space *mapping, pgoff_t index,
				पूर्णांक fgp_flags, gfp_t gfp_mask)
अणु
	अगर (समय_प्रकारo_inject(F2FS_M_SB(mapping), FAULT_PAGE_GET)) अणु
		f2fs_show_injection_info(F2FS_M_SB(mapping), FAULT_PAGE_GET);
		वापस शून्य;
	पूर्ण

	वापस pagecache_get_page(mapping, index, fgp_flags, gfp_mask);
पूर्ण

अटल अंतरभूत व्योम f2fs_copy_page(काष्ठा page *src, काष्ठा page *dst)
अणु
	अक्षर *src_kaddr = kmap(src);
	अक्षर *dst_kaddr = kmap(dst);

	स_नकल(dst_kaddr, src_kaddr, PAGE_SIZE);
	kunmap(dst);
	kunmap(src);
पूर्ण

अटल अंतरभूत व्योम f2fs_put_page(काष्ठा page *page, पूर्णांक unlock)
अणु
	अगर (!page)
		वापस;

	अगर (unlock) अणु
		f2fs_bug_on(F2FS_P_SB(page), !PageLocked(page));
		unlock_page(page);
	पूर्ण
	put_page(page);
पूर्ण

अटल अंतरभूत व्योम f2fs_put_dnode(काष्ठा dnode_of_data *dn)
अणु
	अगर (dn->node_page)
		f2fs_put_page(dn->node_page, 1);
	अगर (dn->inode_page && dn->node_page != dn->inode_page)
		f2fs_put_page(dn->inode_page, 0);
	dn->node_page = शून्य;
	dn->inode_page = शून्य;
पूर्ण

अटल अंतरभूत काष्ठा kmem_cache *f2fs_kmem_cache_create(स्थिर अक्षर *name,
					माप_प्रकार size)
अणु
	वापस kmem_cache_create(name, size, 0, SLAB_RECLAIM_ACCOUNT, शून्य);
पूर्ण

अटल अंतरभूत व्योम *f2fs_kmem_cache_alloc(काष्ठा kmem_cache *cachep,
						gfp_t flags)
अणु
	व्योम *entry;

	entry = kmem_cache_alloc(cachep, flags);
	अगर (!entry)
		entry = kmem_cache_alloc(cachep, flags | __GFP_NOFAIL);
	वापस entry;
पूर्ण

अटल अंतरभूत bool is_inflight_io(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	अगर (get_pages(sbi, F2FS_RD_DATA) || get_pages(sbi, F2FS_RD_NODE) ||
		get_pages(sbi, F2FS_RD_META) || get_pages(sbi, F2FS_WB_DATA) ||
		get_pages(sbi, F2FS_WB_CP_DATA) ||
		get_pages(sbi, F2FS_DIO_READ) ||
		get_pages(sbi, F2FS_DIO_WRITE))
		वापस true;

	अगर (type != DISCARD_TIME && SM_I(sbi) && SM_I(sbi)->dcc_info &&
			atomic_पढ़ो(&SM_I(sbi)->dcc_info->queued_discard))
		वापस true;

	अगर (SM_I(sbi) && SM_I(sbi)->fcc_info &&
			atomic_पढ़ो(&SM_I(sbi)->fcc_info->queued_flush))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool is_idle(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	अगर (sbi->gc_mode == GC_URGENT_HIGH)
		वापस true;

	अगर (is_inflight_io(sbi, type))
		वापस false;

	अगर (sbi->gc_mode == GC_URGENT_LOW &&
			(type == DISCARD_TIME || type == GC_TIME))
		वापस true;

	वापस f2fs_समय_over(sbi, type);
पूर्ण

अटल अंतरभूत व्योम f2fs_radix_tree_insert(काष्ठा radix_tree_root *root,
				अचिन्हित दीर्घ index, व्योम *item)
अणु
	जबतक (radix_tree_insert(root, index, item))
		cond_resched();
पूर्ण

#घोषणा RAW_IS_INODE(p)	((p)->footer.nid == (p)->footer.ino)

अटल अंतरभूत bool IS_INODE(काष्ठा page *page)
अणु
	काष्ठा f2fs_node *p = F2FS_NODE(page);

	वापस RAW_IS_INODE(p);
पूर्ण

अटल अंतरभूत पूर्णांक offset_in_addr(काष्ठा f2fs_inode *i)
अणु
	वापस (i->i_अंतरभूत & F2FS_EXTRA_ATTR) ?
			(le16_to_cpu(i->i_extra_isize) / माप(__le32)) : 0;
पूर्ण

अटल अंतरभूत __le32 *blkaddr_in_node(काष्ठा f2fs_node *node)
अणु
	वापस RAW_IS_INODE(node) ? node->i.i_addr : node->dn.addr;
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_has_extra_attr(काष्ठा inode *inode);
अटल अंतरभूत block_t data_blkaddr(काष्ठा inode *inode,
			काष्ठा page *node_page, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा f2fs_node *raw_node;
	__le32 *addr_array;
	पूर्णांक base = 0;
	bool is_inode = IS_INODE(node_page);

	raw_node = F2FS_NODE(node_page);

	अगर (is_inode) अणु
		अगर (!inode)
			/* from GC path only */
			base = offset_in_addr(&raw_node->i);
		अन्यथा अगर (f2fs_has_extra_attr(inode))
			base = get_extra_isize(inode);
	पूर्ण

	addr_array = blkaddr_in_node(raw_node);
	वापस le32_to_cpu(addr_array[base + offset]);
पूर्ण

अटल अंतरभूत block_t f2fs_data_blkaddr(काष्ठा dnode_of_data *dn)
अणु
	वापस data_blkaddr(dn->inode, dn->node_page, dn->ofs_in_node);
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_test_bit(अचिन्हित पूर्णांक nr, अक्षर *addr)
अणु
	पूर्णांक mask;

	addr += (nr >> 3);
	mask = 1 << (7 - (nr & 0x07));
	वापस mask & *addr;
पूर्ण

अटल अंतरभूत व्योम f2fs_set_bit(अचिन्हित पूर्णांक nr, अक्षर *addr)
अणु
	पूर्णांक mask;

	addr += (nr >> 3);
	mask = 1 << (7 - (nr & 0x07));
	*addr |= mask;
पूर्ण

अटल अंतरभूत व्योम f2fs_clear_bit(अचिन्हित पूर्णांक nr, अक्षर *addr)
अणु
	पूर्णांक mask;

	addr += (nr >> 3);
	mask = 1 << (7 - (nr & 0x07));
	*addr &= ~mask;
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_test_and_set_bit(अचिन्हित पूर्णांक nr, अक्षर *addr)
अणु
	पूर्णांक mask;
	पूर्णांक ret;

	addr += (nr >> 3);
	mask = 1 << (7 - (nr & 0x07));
	ret = mask & *addr;
	*addr |= mask;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_test_and_clear_bit(अचिन्हित पूर्णांक nr, अक्षर *addr)
अणु
	पूर्णांक mask;
	पूर्णांक ret;

	addr += (nr >> 3);
	mask = 1 << (7 - (nr & 0x07));
	ret = mask & *addr;
	*addr &= ~mask;
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम f2fs_change_bit(अचिन्हित पूर्णांक nr, अक्षर *addr)
अणु
	पूर्णांक mask;

	addr += (nr >> 3);
	mask = 1 << (7 - (nr & 0x07));
	*addr ^= mask;
पूर्ण

/*
 * On-disk inode flags (f2fs_inode::i_flags)
 */
#घोषणा F2FS_COMPR_FL			0x00000004 /* Compress file */
#घोषणा F2FS_SYNC_FL			0x00000008 /* Synchronous updates */
#घोषणा F2FS_IMMUTABLE_FL		0x00000010 /* Immutable file */
#घोषणा F2FS_APPEND_FL			0x00000020 /* ग_लिखोs to file may only append */
#घोषणा F2FS_NODUMP_FL			0x00000040 /* करो not dump file */
#घोषणा F2FS_NOATIME_FL			0x00000080 /* करो not update aसमय */
#घोषणा F2FS_NOCOMP_FL			0x00000400 /* Don't compress */
#घोषणा F2FS_INDEX_FL			0x00001000 /* hash-indexed directory */
#घोषणा F2FS_सूचीSYNC_FL			0x00010000 /* dirsync behaviour (directories only) */
#घोषणा F2FS_PROJINHERIT_FL		0x20000000 /* Create with parents projid */
#घोषणा F2FS_CASEFOLD_FL		0x40000000 /* Casefolded file */

/* Flags that should be inherited by new inodes from their parent. */
#घोषणा F2FS_FL_INHERITED (F2FS_SYNC_FL | F2FS_NODUMP_FL | F2FS_NOATIME_FL | \
			   F2FS_सूचीSYNC_FL | F2FS_PROJINHERIT_FL | \
			   F2FS_CASEFOLD_FL | F2FS_COMPR_FL | F2FS_NOCOMP_FL)

/* Flags that are appropriate क्रम regular files (all but dir-specअगरic ones). */
#घोषणा F2FS_REG_FLMASK		(~(F2FS_सूचीSYNC_FL | F2FS_PROJINHERIT_FL | \
				F2FS_CASEFOLD_FL))

/* Flags that are appropriate क्रम non-directories/regular files. */
#घोषणा F2FS_OTHER_FLMASK	(F2FS_NODUMP_FL | F2FS_NOATIME_FL)

अटल अंतरभूत __u32 f2fs_mask_flags(umode_t mode, __u32 flags)
अणु
	अगर (S_ISसूची(mode))
		वापस flags;
	अन्यथा अगर (S_ISREG(mode))
		वापस flags & F2FS_REG_FLMASK;
	अन्यथा
		वापस flags & F2FS_OTHER_FLMASK;
पूर्ण

अटल अंतरभूत व्योम __mark_inode_dirty_flag(काष्ठा inode *inode,
						पूर्णांक flag, bool set)
अणु
	चयन (flag) अणु
	हाल FI_INLINE_XATTR:
	हाल FI_INLINE_DATA:
	हाल FI_INLINE_DENTRY:
	हाल FI_NEW_INODE:
		अगर (set)
			वापस;
		fallthrough;
	हाल FI_DATA_EXIST:
	हाल FI_INLINE_DOTS:
	हाल FI_PIN_खाता:
		f2fs_mark_inode_dirty_sync(inode, true);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम set_inode_flag(काष्ठा inode *inode, पूर्णांक flag)
अणु
	set_bit(flag, F2FS_I(inode)->flags);
	__mark_inode_dirty_flag(inode, flag, true);
पूर्ण

अटल अंतरभूत पूर्णांक is_inode_flag_set(काष्ठा inode *inode, पूर्णांक flag)
अणु
	वापस test_bit(flag, F2FS_I(inode)->flags);
पूर्ण

अटल अंतरभूत व्योम clear_inode_flag(काष्ठा inode *inode, पूर्णांक flag)
अणु
	clear_bit(flag, F2FS_I(inode)->flags);
	__mark_inode_dirty_flag(inode, flag, false);
पूर्ण

अटल अंतरभूत bool f2fs_verity_in_progress(काष्ठा inode *inode)
अणु
	वापस IS_ENABLED(CONFIG_FS_VERITY) &&
	       is_inode_flag_set(inode, FI_VERITY_IN_PROGRESS);
पूर्ण

अटल अंतरभूत व्योम set_acl_inode(काष्ठा inode *inode, umode_t mode)
अणु
	F2FS_I(inode)->i_acl_mode = mode;
	set_inode_flag(inode, FI_ACL_MODE);
	f2fs_mark_inode_dirty_sync(inode, false);
पूर्ण

अटल अंतरभूत व्योम f2fs_i_links_ग_लिखो(काष्ठा inode *inode, bool inc)
अणु
	अगर (inc)
		inc_nlink(inode);
	अन्यथा
		drop_nlink(inode);
	f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

अटल अंतरभूत व्योम f2fs_i_blocks_ग_लिखो(काष्ठा inode *inode,
					block_t dअगरf, bool add, bool claim)
अणु
	bool clean = !is_inode_flag_set(inode, FI_सूचीTY_INODE);
	bool recover = is_inode_flag_set(inode, FI_AUTO_RECOVER);

	/* add = 1, claim = 1 should be dquot_reserve_block in pair */
	अगर (add) अणु
		अगर (claim)
			dquot_claim_block(inode, dअगरf);
		अन्यथा
			dquot_alloc_block_nofail(inode, dअगरf);
	पूर्ण अन्यथा अणु
		dquot_मुक्त_block(inode, dअगरf);
	पूर्ण

	f2fs_mark_inode_dirty_sync(inode, true);
	अगर (clean || recover)
		set_inode_flag(inode, FI_AUTO_RECOVER);
पूर्ण

अटल अंतरभूत व्योम f2fs_i_size_ग_लिखो(काष्ठा inode *inode, loff_t i_size)
अणु
	bool clean = !is_inode_flag_set(inode, FI_सूचीTY_INODE);
	bool recover = is_inode_flag_set(inode, FI_AUTO_RECOVER);

	अगर (i_size_पढ़ो(inode) == i_size)
		वापस;

	i_size_ग_लिखो(inode, i_size);
	f2fs_mark_inode_dirty_sync(inode, true);
	अगर (clean || recover)
		set_inode_flag(inode, FI_AUTO_RECOVER);
पूर्ण

अटल अंतरभूत व्योम f2fs_i_depth_ग_लिखो(काष्ठा inode *inode, अचिन्हित पूर्णांक depth)
अणु
	F2FS_I(inode)->i_current_depth = depth;
	f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

अटल अंतरभूत व्योम f2fs_i_gc_failures_ग_लिखो(काष्ठा inode *inode,
					अचिन्हित पूर्णांक count)
अणु
	F2FS_I(inode)->i_gc_failures[GC_FAILURE_PIN] = count;
	f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

अटल अंतरभूत व्योम f2fs_i_xnid_ग_लिखो(काष्ठा inode *inode, nid_t xnid)
अणु
	F2FS_I(inode)->i_xattr_nid = xnid;
	f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

अटल अंतरभूत व्योम f2fs_i_pino_ग_लिखो(काष्ठा inode *inode, nid_t pino)
अणु
	F2FS_I(inode)->i_pino = pino;
	f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

अटल अंतरभूत व्योम get_अंतरभूत_info(काष्ठा inode *inode, काष्ठा f2fs_inode *ri)
अणु
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);

	अगर (ri->i_अंतरभूत & F2FS_INLINE_XATTR)
		set_bit(FI_INLINE_XATTR, fi->flags);
	अगर (ri->i_अंतरभूत & F2FS_INLINE_DATA)
		set_bit(FI_INLINE_DATA, fi->flags);
	अगर (ri->i_अंतरभूत & F2FS_INLINE_DENTRY)
		set_bit(FI_INLINE_DENTRY, fi->flags);
	अगर (ri->i_अंतरभूत & F2FS_DATA_EXIST)
		set_bit(FI_DATA_EXIST, fi->flags);
	अगर (ri->i_अंतरभूत & F2FS_INLINE_DOTS)
		set_bit(FI_INLINE_DOTS, fi->flags);
	अगर (ri->i_अंतरभूत & F2FS_EXTRA_ATTR)
		set_bit(FI_EXTRA_ATTR, fi->flags);
	अगर (ri->i_अंतरभूत & F2FS_PIN_खाता)
		set_bit(FI_PIN_खाता, fi->flags);
पूर्ण

अटल अंतरभूत व्योम set_raw_अंतरभूत(काष्ठा inode *inode, काष्ठा f2fs_inode *ri)
अणु
	ri->i_अंतरभूत = 0;

	अगर (is_inode_flag_set(inode, FI_INLINE_XATTR))
		ri->i_अंतरभूत |= F2FS_INLINE_XATTR;
	अगर (is_inode_flag_set(inode, FI_INLINE_DATA))
		ri->i_अंतरभूत |= F2FS_INLINE_DATA;
	अगर (is_inode_flag_set(inode, FI_INLINE_DENTRY))
		ri->i_अंतरभूत |= F2FS_INLINE_DENTRY;
	अगर (is_inode_flag_set(inode, FI_DATA_EXIST))
		ri->i_अंतरभूत |= F2FS_DATA_EXIST;
	अगर (is_inode_flag_set(inode, FI_INLINE_DOTS))
		ri->i_अंतरभूत |= F2FS_INLINE_DOTS;
	अगर (is_inode_flag_set(inode, FI_EXTRA_ATTR))
		ri->i_अंतरभूत |= F2FS_EXTRA_ATTR;
	अगर (is_inode_flag_set(inode, FI_PIN_खाता))
		ri->i_अंतरभूत |= F2FS_PIN_खाता;
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_has_extra_attr(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_EXTRA_ATTR);
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_has_अंतरभूत_xattr(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_INLINE_XATTR);
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_compressed_file(काष्ठा inode *inode)
अणु
	वापस S_ISREG(inode->i_mode) &&
		is_inode_flag_set(inode, FI_COMPRESSED_खाता);
पूर्ण

अटल अंतरभूत bool f2fs_need_compress_data(काष्ठा inode *inode)
अणु
	पूर्णांक compress_mode = F2FS_OPTION(F2FS_I_SB(inode)).compress_mode;

	अगर (!f2fs_compressed_file(inode))
		वापस false;

	अगर (compress_mode == COMPR_MODE_FS)
		वापस true;
	अन्यथा अगर (compress_mode == COMPR_MODE_USER &&
			is_inode_flag_set(inode, FI_ENABLE_COMPRESS))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक addrs_per_inode(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक addrs = CUR_ADDRS_PER_INODE(inode) -
				get_अंतरभूत_xattr_addrs(inode);

	अगर (!f2fs_compressed_file(inode))
		वापस addrs;
	वापस ALIGN_DOWN(addrs, F2FS_I(inode)->i_cluster_size);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक addrs_per_block(काष्ठा inode *inode)
अणु
	अगर (!f2fs_compressed_file(inode))
		वापस DEF_ADDRS_PER_BLOCK;
	वापस ALIGN_DOWN(DEF_ADDRS_PER_BLOCK, F2FS_I(inode)->i_cluster_size);
पूर्ण

अटल अंतरभूत व्योम *अंतरभूत_xattr_addr(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा f2fs_inode *ri = F2FS_INODE(page);

	वापस (व्योम *)&(ri->i_addr[DEF_ADDRS_PER_INODE -
					get_अंतरभूत_xattr_addrs(inode)]);
पूर्ण

अटल अंतरभूत पूर्णांक अंतरभूत_xattr_size(काष्ठा inode *inode)
अणु
	अगर (f2fs_has_अंतरभूत_xattr(inode))
		वापस get_अंतरभूत_xattr_addrs(inode) * माप(__le32);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_has_अंतरभूत_data(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_INLINE_DATA);
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_exist_data(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_DATA_EXIST);
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_has_अंतरभूत_करोts(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_INLINE_DOTS);
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_is_mmap_file(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_MMAP_खाता);
पूर्ण

अटल अंतरभूत bool f2fs_is_pinned_file(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_PIN_खाता);
पूर्ण

अटल अंतरभूत bool f2fs_is_atomic_file(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_ATOMIC_खाता);
पूर्ण

अटल अंतरभूत bool f2fs_is_commit_atomic_ग_लिखो(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_ATOMIC_COMMIT);
पूर्ण

अटल अंतरभूत bool f2fs_is_अस्थिर_file(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_VOLATILE_खाता);
पूर्ण

अटल अंतरभूत bool f2fs_is_first_block_written(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_FIRST_BLOCK_WRITTEN);
पूर्ण

अटल अंतरभूत bool f2fs_is_drop_cache(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_DROP_CACHE);
पूर्ण

अटल अंतरभूत व्योम *अंतरभूत_data_addr(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा f2fs_inode *ri = F2FS_INODE(page);
	पूर्णांक extra_size = get_extra_isize(inode);

	वापस (व्योम *)&(ri->i_addr[extra_size + DEF_INLINE_RESERVED_SIZE]);
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_has_अंतरभूत_dentry(काष्ठा inode *inode)
अणु
	वापस is_inode_flag_set(inode, FI_INLINE_DENTRY);
पूर्ण

अटल अंतरभूत पूर्णांक is_file(काष्ठा inode *inode, पूर्णांक type)
अणु
	वापस F2FS_I(inode)->i_advise & type;
पूर्ण

अटल अंतरभूत व्योम set_file(काष्ठा inode *inode, पूर्णांक type)
अणु
	F2FS_I(inode)->i_advise |= type;
	f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

अटल अंतरभूत व्योम clear_file(काष्ठा inode *inode, पूर्णांक type)
अणु
	F2FS_I(inode)->i_advise &= ~type;
	f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

अटल अंतरभूत bool f2fs_is_समय_consistent(काष्ठा inode *inode)
अणु
	अगर (!बारpec64_equal(F2FS_I(inode)->i_disk_समय, &inode->i_aसमय))
		वापस false;
	अगर (!बारpec64_equal(F2FS_I(inode)->i_disk_समय + 1, &inode->i_स_समय))
		वापस false;
	अगर (!बारpec64_equal(F2FS_I(inode)->i_disk_समय + 2, &inode->i_mसमय))
		वापस false;
	अगर (!बारpec64_equal(F2FS_I(inode)->i_disk_समय + 3,
						&F2FS_I(inode)->i_crसमय))
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool f2fs_skip_inode_update(काष्ठा inode *inode, पूर्णांक dsync)
अणु
	bool ret;

	अगर (dsync) अणु
		काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

		spin_lock(&sbi->inode_lock[सूचीTY_META]);
		ret = list_empty(&F2FS_I(inode)->gdirty_list);
		spin_unlock(&sbi->inode_lock[सूचीTY_META]);
		वापस ret;
	पूर्ण
	अगर (!is_inode_flag_set(inode, FI_AUTO_RECOVER) ||
			file_keep_isize(inode) ||
			i_size_पढ़ो(inode) & ~PAGE_MASK)
		वापस false;

	अगर (!f2fs_is_समय_consistent(inode))
		वापस false;

	spin_lock(&F2FS_I(inode)->i_size_lock);
	ret = F2FS_I(inode)->last_disk_size == i_size_पढ़ो(inode);
	spin_unlock(&F2FS_I(inode)->i_size_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत bool f2fs_पढ़ोonly(काष्ठा super_block *sb)
अणु
	वापस sb_rकरोnly(sb);
पूर्ण

अटल अंतरभूत bool f2fs_cp_error(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस is_set_ckpt_flags(sbi, CP_ERROR_FLAG);
पूर्ण

अटल अंतरभूत bool is_करोt_करोtकरोt(स्थिर u8 *name, माप_प्रकार len)
अणु
	अगर (len == 1 && name[0] == '.')
		वापस true;

	अगर (len == 2 && name[0] == '.' && name[1] == '.')
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool f2fs_may_extent_tree(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

	अगर (!test_opt(sbi, EXTENT_CACHE) ||
			is_inode_flag_set(inode, FI_NO_EXTENT) ||
			is_inode_flag_set(inode, FI_COMPRESSED_खाता))
		वापस false;

	/*
	 * क्रम recovered files during mount करो not create extents
	 * अगर shrinker is not रेजिस्टरed.
	 */
	अगर (list_empty(&sbi->s_list))
		वापस false;

	वापस S_ISREG(inode->i_mode);
पूर्ण

अटल अंतरभूत व्योम *f2fs_kदो_स्मृति(काष्ठा f2fs_sb_info *sbi,
					माप_प्रकार size, gfp_t flags)
अणु
	अगर (समय_प्रकारo_inject(sbi, FAULT_KMALLOC)) अणु
		f2fs_show_injection_info(sbi, FAULT_KMALLOC);
		वापस शून्य;
	पूर्ण

	वापस kदो_स्मृति(size, flags);
पूर्ण

अटल अंतरभूत व्योम *f2fs_kzalloc(काष्ठा f2fs_sb_info *sbi,
					माप_प्रकार size, gfp_t flags)
अणु
	वापस f2fs_kदो_स्मृति(sbi, size, flags | __GFP_ZERO);
पूर्ण

अटल अंतरभूत व्योम *f2fs_kvदो_स्मृति(काष्ठा f2fs_sb_info *sbi,
					माप_प्रकार size, gfp_t flags)
अणु
	अगर (समय_प्रकारo_inject(sbi, FAULT_KVMALLOC)) अणु
		f2fs_show_injection_info(sbi, FAULT_KVMALLOC);
		वापस शून्य;
	पूर्ण

	वापस kvदो_स्मृति(size, flags);
पूर्ण

अटल अंतरभूत व्योम *f2fs_kvzalloc(काष्ठा f2fs_sb_info *sbi,
					माप_प्रकार size, gfp_t flags)
अणु
	वापस f2fs_kvदो_स्मृति(sbi, size, flags | __GFP_ZERO);
पूर्ण

अटल अंतरभूत पूर्णांक get_extra_isize(काष्ठा inode *inode)
अणु
	वापस F2FS_I(inode)->i_extra_isize / माप(__le32);
पूर्ण

अटल अंतरभूत पूर्णांक get_अंतरभूत_xattr_addrs(काष्ठा inode *inode)
अणु
	वापस F2FS_I(inode)->i_अंतरभूत_xattr_size;
पूर्ण

#घोषणा f2fs_get_inode_mode(i) \
	((is_inode_flag_set(i, FI_ACL_MODE)) ? \
	 (F2FS_I(i)->i_acl_mode) : ((i)->i_mode))

#घोषणा F2FS_TOTAL_EXTRA_ATTR_SIZE			\
	(दुरत्व(काष्ठा f2fs_inode, i_extra_end) -	\
	दुरत्व(काष्ठा f2fs_inode, i_extra_isize))	\

#घोषणा F2FS_OLD_ATTRIBUTE_SIZE	(दुरत्व(काष्ठा f2fs_inode, i_addr))
#घोषणा F2FS_FITS_IN_INODE(f2fs_inode, extra_isize, field)		\
		((दुरत्व(typeof(*(f2fs_inode)), field) +	\
		माप((f2fs_inode)->field))			\
		<= (F2FS_OLD_ATTRIBUTE_SIZE + (extra_isize)))	\

#घोषणा DEFAULT_IOSTAT_PERIOD_MS	3000
#घोषणा MIN_IOSTAT_PERIOD_MS		100
/* maximum period of iostat tracing is 1 day */
#घोषणा MAX_IOSTAT_PERIOD_MS		8640000

अटल अंतरभूत व्योम f2fs_reset_iostat(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक i;

	spin_lock(&sbi->iostat_lock);
	क्रम (i = 0; i < NR_IO_TYPE; i++) अणु
		sbi->rw_iostat[i] = 0;
		sbi->prev_rw_iostat[i] = 0;
	पूर्ण
	spin_unlock(&sbi->iostat_lock);
पूर्ण

बाह्य व्योम f2fs_record_iostat(काष्ठा f2fs_sb_info *sbi);

अटल अंतरभूत व्योम f2fs_update_iostat(काष्ठा f2fs_sb_info *sbi,
			क्रमागत iostat_type type, अचिन्हित दीर्घ दीर्घ io_bytes)
अणु
	अगर (!sbi->iostat_enable)
		वापस;
	spin_lock(&sbi->iostat_lock);
	sbi->rw_iostat[type] += io_bytes;

	अगर (type == APP_WRITE_IO || type == APP_सूचीECT_IO)
		sbi->rw_iostat[APP_BUFFERED_IO] =
			sbi->rw_iostat[APP_WRITE_IO] -
			sbi->rw_iostat[APP_सूचीECT_IO];

	अगर (type == APP_READ_IO || type == APP_सूचीECT_READ_IO)
		sbi->rw_iostat[APP_BUFFERED_READ_IO] =
			sbi->rw_iostat[APP_READ_IO] -
			sbi->rw_iostat[APP_सूचीECT_READ_IO];
	spin_unlock(&sbi->iostat_lock);

	f2fs_record_iostat(sbi);
पूर्ण

#घोषणा __is_large_section(sbi)		((sbi)->segs_per_sec > 1)

#घोषणा __is_meta_io(fio) (PAGE_TYPE_OF_BIO((fio)->type) == META)

bool f2fs_is_valid_blkaddr(काष्ठा f2fs_sb_info *sbi,
					block_t blkaddr, पूर्णांक type);
अटल अंतरभूत व्योम verअगरy_blkaddr(काष्ठा f2fs_sb_info *sbi,
					block_t blkaddr, पूर्णांक type)
अणु
	अगर (!f2fs_is_valid_blkaddr(sbi, blkaddr, type)) अणु
		f2fs_err(sbi, "invalid blkaddr: %u, type: %d, run fsck to fix.",
			 blkaddr, type);
		f2fs_bug_on(sbi, 1);
	पूर्ण
पूर्ण

अटल अंतरभूत bool __is_valid_data_blkaddr(block_t blkaddr)
अणु
	अगर (blkaddr == NEW_ADDR || blkaddr == शून्य_ADDR ||
			blkaddr == COMPRESS_ADDR)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत व्योम f2fs_set_page_निजी(काष्ठा page *page,
						अचिन्हित दीर्घ data)
अणु
	अगर (PagePrivate(page))
		वापस;

	attach_page_निजी(page, (व्योम *)data);
पूर्ण

अटल अंतरभूत व्योम f2fs_clear_page_निजी(काष्ठा page *page)
अणु
	detach_page_निजी(page);
पूर्ण

/*
 * file.c
 */
पूर्णांक f2fs_sync_file(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync);
व्योम f2fs_truncate_data_blocks(काष्ठा dnode_of_data *dn);
पूर्णांक f2fs_करो_truncate_blocks(काष्ठा inode *inode, u64 from, bool lock);
पूर्णांक f2fs_truncate_blocks(काष्ठा inode *inode, u64 from, bool lock);
पूर्णांक f2fs_truncate(काष्ठा inode *inode);
पूर्णांक f2fs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		 काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags);
पूर्णांक f2fs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		 काष्ठा iattr *attr);
पूर्णांक f2fs_truncate_hole(काष्ठा inode *inode, pgoff_t pg_start, pgoff_t pg_end);
व्योम f2fs_truncate_data_blocks_range(काष्ठा dnode_of_data *dn, पूर्णांक count);
पूर्णांक f2fs_precache_extents(काष्ठा inode *inode);
पूर्णांक f2fs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्णांक f2fs_fileattr_set(काष्ठा user_namespace *mnt_userns,
		      काष्ठा dentry *dentry, काष्ठा fileattr *fa);
दीर्घ f2fs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ f2fs_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक f2fs_transfer_project_quota(काष्ठा inode *inode, kprojid_t kprojid);
पूर्णांक f2fs_pin_file_control(काष्ठा inode *inode, bool inc);

/*
 * inode.c
 */
व्योम f2fs_set_inode_flags(काष्ठा inode *inode);
bool f2fs_inode_chksum_verअगरy(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page);
व्योम f2fs_inode_chksum_set(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page);
काष्ठा inode *f2fs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino);
काष्ठा inode *f2fs_iget_retry(काष्ठा super_block *sb, अचिन्हित दीर्घ ino);
पूर्णांक f2fs_try_to_मुक्त_nats(काष्ठा f2fs_sb_info *sbi, पूर्णांक nr_shrink);
व्योम f2fs_update_inode(काष्ठा inode *inode, काष्ठा page *node_page);
व्योम f2fs_update_inode_page(काष्ठा inode *inode);
पूर्णांक f2fs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc);
व्योम f2fs_evict_inode(काष्ठा inode *inode);
व्योम f2fs_handle_failed_inode(काष्ठा inode *inode);

/*
 * namei.c
 */
पूर्णांक f2fs_update_extension_list(काष्ठा f2fs_sb_info *sbi, स्थिर अक्षर *name,
							bool hot, bool set);
काष्ठा dentry *f2fs_get_parent(काष्ठा dentry *child);

/*
 * dir.c
 */
अचिन्हित अक्षर f2fs_get_de_type(काष्ठा f2fs_dir_entry *de);
पूर्णांक f2fs_init_हालfolded_name(स्थिर काष्ठा inode *dir,
			      काष्ठा f2fs_filename *fname);
पूर्णांक f2fs_setup_filename(काष्ठा inode *dir, स्थिर काष्ठा qstr *iname,
			पूर्णांक lookup, काष्ठा f2fs_filename *fname);
पूर्णांक f2fs_prepare_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
			काष्ठा f2fs_filename *fname);
व्योम f2fs_मुक्त_filename(काष्ठा f2fs_filename *fname);
काष्ठा f2fs_dir_entry *f2fs_find_target_dentry(स्थिर काष्ठा f2fs_dentry_ptr *d,
			स्थिर काष्ठा f2fs_filename *fname, पूर्णांक *max_slots);
पूर्णांक f2fs_fill_dentries(काष्ठा dir_context *ctx, काष्ठा f2fs_dentry_ptr *d,
			अचिन्हित पूर्णांक start_pos, काष्ठा fscrypt_str *fstr);
व्योम f2fs_करो_make_empty_dir(काष्ठा inode *inode, काष्ठा inode *parent,
			काष्ठा f2fs_dentry_ptr *d);
काष्ठा page *f2fs_init_inode_metadata(काष्ठा inode *inode, काष्ठा inode *dir,
			स्थिर काष्ठा f2fs_filename *fname, काष्ठा page *dpage);
व्योम f2fs_update_parent_metadata(काष्ठा inode *dir, काष्ठा inode *inode,
			अचिन्हित पूर्णांक current_depth);
पूर्णांक f2fs_room_क्रम_filename(स्थिर व्योम *biपंचांगap, पूर्णांक slots, पूर्णांक max_slots);
व्योम f2fs_drop_nlink(काष्ठा inode *dir, काष्ठा inode *inode);
काष्ठा f2fs_dir_entry *__f2fs_find_entry(काष्ठा inode *dir,
					 स्थिर काष्ठा f2fs_filename *fname,
					 काष्ठा page **res_page);
काष्ठा f2fs_dir_entry *f2fs_find_entry(काष्ठा inode *dir,
			स्थिर काष्ठा qstr *child, काष्ठा page **res_page);
काष्ठा f2fs_dir_entry *f2fs_parent_dir(काष्ठा inode *dir, काष्ठा page **p);
ino_t f2fs_inode_by_name(काष्ठा inode *dir, स्थिर काष्ठा qstr *qstr,
			काष्ठा page **page);
व्योम f2fs_set_link(काष्ठा inode *dir, काष्ठा f2fs_dir_entry *de,
			काष्ठा page *page, काष्ठा inode *inode);
bool f2fs_has_enough_room(काष्ठा inode *dir, काष्ठा page *ipage,
			  स्थिर काष्ठा f2fs_filename *fname);
व्योम f2fs_update_dentry(nid_t ino, umode_t mode, काष्ठा f2fs_dentry_ptr *d,
			स्थिर काष्ठा fscrypt_str *name, f2fs_hash_t name_hash,
			अचिन्हित पूर्णांक bit_pos);
पूर्णांक f2fs_add_regular_entry(काष्ठा inode *dir, स्थिर काष्ठा f2fs_filename *fname,
			काष्ठा inode *inode, nid_t ino, umode_t mode);
पूर्णांक f2fs_add_dentry(काष्ठा inode *dir, स्थिर काष्ठा f2fs_filename *fname,
			काष्ठा inode *inode, nid_t ino, umode_t mode);
पूर्णांक f2fs_करो_add_link(काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
			काष्ठा inode *inode, nid_t ino, umode_t mode);
व्योम f2fs_delete_entry(काष्ठा f2fs_dir_entry *dentry, काष्ठा page *page,
			काष्ठा inode *dir, काष्ठा inode *inode);
पूर्णांक f2fs_करो_क्षणिक_ख(काष्ठा inode *inode, काष्ठा inode *dir);
bool f2fs_empty_dir(काष्ठा inode *dir);

अटल अंतरभूत पूर्णांक f2fs_add_link(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	अगर (fscrypt_is_nokey_name(dentry))
		वापस -ENOKEY;
	वापस f2fs_करो_add_link(d_inode(dentry->d_parent), &dentry->d_name,
				inode, inode->i_ino, inode->i_mode);
पूर्ण

/*
 * super.c
 */
पूर्णांक f2fs_inode_dirtied(काष्ठा inode *inode, bool sync);
व्योम f2fs_inode_synced(काष्ठा inode *inode);
पूर्णांक f2fs_enable_quota_files(काष्ठा f2fs_sb_info *sbi, bool rकरोnly);
पूर्णांक f2fs_quota_sync(काष्ठा super_block *sb, पूर्णांक type);
loff_t max_file_blocks(काष्ठा inode *inode);
व्योम f2fs_quota_off_umount(काष्ठा super_block *sb);
पूर्णांक f2fs_commit_super(काष्ठा f2fs_sb_info *sbi, bool recover);
पूर्णांक f2fs_sync_fs(काष्ठा super_block *sb, पूर्णांक sync);
पूर्णांक f2fs_sanity_check_ckpt(काष्ठा f2fs_sb_info *sbi);

/*
 * hash.c
 */
व्योम f2fs_hash_filename(स्थिर काष्ठा inode *dir, काष्ठा f2fs_filename *fname);

/*
 * node.c
 */
काष्ठा node_info;

पूर्णांक f2fs_check_nid_range(काष्ठा f2fs_sb_info *sbi, nid_t nid);
bool f2fs_available_मुक्त_memory(काष्ठा f2fs_sb_info *sbi, पूर्णांक type);
bool f2fs_in_warm_node_list(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page);
व्योम f2fs_init_fsync_node_info(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_del_fsync_node_entry(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page);
व्योम f2fs_reset_fsync_node_info(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_need_dentry_mark(काष्ठा f2fs_sb_info *sbi, nid_t nid);
bool f2fs_is_checkpoपूर्णांकed_node(काष्ठा f2fs_sb_info *sbi, nid_t nid);
bool f2fs_need_inode_block_update(काष्ठा f2fs_sb_info *sbi, nid_t ino);
पूर्णांक f2fs_get_node_info(काष्ठा f2fs_sb_info *sbi, nid_t nid,
						काष्ठा node_info *ni);
pgoff_t f2fs_get_next_page_offset(काष्ठा dnode_of_data *dn, pgoff_t pgofs);
पूर्णांक f2fs_get_dnode_of_data(काष्ठा dnode_of_data *dn, pgoff_t index, पूर्णांक mode);
पूर्णांक f2fs_truncate_inode_blocks(काष्ठा inode *inode, pgoff_t from);
पूर्णांक f2fs_truncate_xattr_node(काष्ठा inode *inode);
पूर्णांक f2fs_रुको_on_node_pages_ग_लिखोback(काष्ठा f2fs_sb_info *sbi,
					अचिन्हित पूर्णांक seq_id);
पूर्णांक f2fs_हटाओ_inode_page(काष्ठा inode *inode);
काष्ठा page *f2fs_new_inode_page(काष्ठा inode *inode);
काष्ठा page *f2fs_new_node_page(काष्ठा dnode_of_data *dn, अचिन्हित पूर्णांक ofs);
व्योम f2fs_ra_node_page(काष्ठा f2fs_sb_info *sbi, nid_t nid);
काष्ठा page *f2fs_get_node_page(काष्ठा f2fs_sb_info *sbi, pgoff_t nid);
काष्ठा page *f2fs_get_node_page_ra(काष्ठा page *parent, पूर्णांक start);
पूर्णांक f2fs_move_node_page(काष्ठा page *node_page, पूर्णांक gc_type);
व्योम f2fs_flush_अंतरभूत_data(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_fsync_node_pages(काष्ठा f2fs_sb_info *sbi, काष्ठा inode *inode,
			काष्ठा ग_लिखोback_control *wbc, bool atomic,
			अचिन्हित पूर्णांक *seq_id);
पूर्णांक f2fs_sync_node_pages(काष्ठा f2fs_sb_info *sbi,
			काष्ठा ग_लिखोback_control *wbc,
			bool करो_balance, क्रमागत iostat_type io_type);
पूर्णांक f2fs_build_मुक्त_nids(काष्ठा f2fs_sb_info *sbi, bool sync, bool mount);
bool f2fs_alloc_nid(काष्ठा f2fs_sb_info *sbi, nid_t *nid);
व्योम f2fs_alloc_nid_करोne(काष्ठा f2fs_sb_info *sbi, nid_t nid);
व्योम f2fs_alloc_nid_failed(काष्ठा f2fs_sb_info *sbi, nid_t nid);
पूर्णांक f2fs_try_to_मुक्त_nids(काष्ठा f2fs_sb_info *sbi, पूर्णांक nr_shrink);
पूर्णांक f2fs_recover_अंतरभूत_xattr(काष्ठा inode *inode, काष्ठा page *page);
पूर्णांक f2fs_recover_xattr_data(काष्ठा inode *inode, काष्ठा page *page);
पूर्णांक f2fs_recover_inode_page(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page);
पूर्णांक f2fs_restore_node_summary(काष्ठा f2fs_sb_info *sbi,
			अचिन्हित पूर्णांक segno, काष्ठा f2fs_summary_block *sum);
पूर्णांक f2fs_flush_nat_entries(काष्ठा f2fs_sb_info *sbi, काष्ठा cp_control *cpc);
पूर्णांक f2fs_build_node_manager(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_destroy_node_manager(काष्ठा f2fs_sb_info *sbi);
पूर्णांक __init f2fs_create_node_manager_caches(व्योम);
व्योम f2fs_destroy_node_manager_caches(व्योम);

/*
 * segment.c
 */
bool f2fs_need_SSR(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_रेजिस्टर_inmem_page(काष्ठा inode *inode, काष्ठा page *page);
व्योम f2fs_drop_inmem_pages_all(काष्ठा f2fs_sb_info *sbi, bool gc_failure);
व्योम f2fs_drop_inmem_pages(काष्ठा inode *inode);
व्योम f2fs_drop_inmem_page(काष्ठा inode *inode, काष्ठा page *page);
पूर्णांक f2fs_commit_inmem_pages(काष्ठा inode *inode);
व्योम f2fs_balance_fs(काष्ठा f2fs_sb_info *sbi, bool need);
व्योम f2fs_balance_fs_bg(काष्ठा f2fs_sb_info *sbi, bool from_bg);
पूर्णांक f2fs_issue_flush(काष्ठा f2fs_sb_info *sbi, nid_t ino);
पूर्णांक f2fs_create_flush_cmd_control(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_flush_device_cache(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_destroy_flush_cmd_control(काष्ठा f2fs_sb_info *sbi, bool मुक्त);
व्योम f2fs_invalidate_blocks(काष्ठा f2fs_sb_info *sbi, block_t addr);
bool f2fs_is_checkpoपूर्णांकed_data(काष्ठा f2fs_sb_info *sbi, block_t blkaddr);
व्योम f2fs_drop_discard_cmd(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_stop_discard_thपढ़ो(काष्ठा f2fs_sb_info *sbi);
bool f2fs_issue_discard_समयout(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_clear_preमुक्त_segments(काष्ठा f2fs_sb_info *sbi,
					काष्ठा cp_control *cpc);
व्योम f2fs_dirty_to_preमुक्त(काष्ठा f2fs_sb_info *sbi);
block_t f2fs_get_unusable_blocks(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_disable_cp_again(काष्ठा f2fs_sb_info *sbi, block_t unusable);
व्योम f2fs_release_discard_addrs(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_npages_क्रम_summary_flush(काष्ठा f2fs_sb_info *sbi, bool क्रम_ra);
bool f2fs_segment_has_मुक्त_slot(काष्ठा f2fs_sb_info *sbi, पूर्णांक segno);
व्योम f2fs_init_inmem_curseg(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_save_inmem_curseg(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_restore_inmem_curseg(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_get_new_segment(काष्ठा f2fs_sb_info *sbi,
			अचिन्हित पूर्णांक *newseg, bool new_sec, पूर्णांक dir);
व्योम f2fs_allocate_segment_क्रम_resize(काष्ठा f2fs_sb_info *sbi, पूर्णांक type,
					अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end);
व्योम f2fs_allocate_new_section(काष्ठा f2fs_sb_info *sbi, पूर्णांक type, bool क्रमce);
व्योम f2fs_allocate_new_segments(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_trim_fs(काष्ठा f2fs_sb_info *sbi, काष्ठा fstrim_range *range);
bool f2fs_exist_trim_candidates(काष्ठा f2fs_sb_info *sbi,
					काष्ठा cp_control *cpc);
काष्ठा page *f2fs_get_sum_page(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno);
व्योम f2fs_update_meta_page(काष्ठा f2fs_sb_info *sbi, व्योम *src,
					block_t blk_addr);
व्योम f2fs_करो_ग_लिखो_meta_page(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page,
						क्रमागत iostat_type io_type);
व्योम f2fs_करो_ग_लिखो_node_page(अचिन्हित पूर्णांक nid, काष्ठा f2fs_io_info *fio);
व्योम f2fs_outplace_ग_लिखो_data(काष्ठा dnode_of_data *dn,
			काष्ठा f2fs_io_info *fio);
पूर्णांक f2fs_inplace_ग_लिखो_data(काष्ठा f2fs_io_info *fio);
व्योम f2fs_करो_replace_block(काष्ठा f2fs_sb_info *sbi, काष्ठा f2fs_summary *sum,
			block_t old_blkaddr, block_t new_blkaddr,
			bool recover_curseg, bool recover_newaddr,
			bool from_gc);
व्योम f2fs_replace_block(काष्ठा f2fs_sb_info *sbi, काष्ठा dnode_of_data *dn,
			block_t old_addr, block_t new_addr,
			अचिन्हित अक्षर version, bool recover_curseg,
			bool recover_newaddr);
व्योम f2fs_allocate_data_block(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page,
			block_t old_blkaddr, block_t *new_blkaddr,
			काष्ठा f2fs_summary *sum, पूर्णांक type,
			काष्ठा f2fs_io_info *fio);
व्योम f2fs_रुको_on_page_ग_लिखोback(काष्ठा page *page,
			क्रमागत page_type type, bool ordered, bool locked);
व्योम f2fs_रुको_on_block_ग_लिखोback(काष्ठा inode *inode, block_t blkaddr);
व्योम f2fs_रुको_on_block_ग_लिखोback_range(काष्ठा inode *inode, block_t blkaddr,
								block_t len);
व्योम f2fs_ग_लिखो_data_summaries(काष्ठा f2fs_sb_info *sbi, block_t start_blk);
व्योम f2fs_ग_लिखो_node_summaries(काष्ठा f2fs_sb_info *sbi, block_t start_blk);
पूर्णांक f2fs_lookup_journal_in_cursum(काष्ठा f2fs_journal *journal, पूर्णांक type,
			अचिन्हित पूर्णांक val, पूर्णांक alloc);
व्योम f2fs_flush_sit_entries(काष्ठा f2fs_sb_info *sbi, काष्ठा cp_control *cpc);
पूर्णांक f2fs_fix_curseg_ग_लिखो_poपूर्णांकer(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_check_ग_लिखो_poपूर्णांकer(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_build_segment_manager(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_destroy_segment_manager(काष्ठा f2fs_sb_info *sbi);
पूर्णांक __init f2fs_create_segment_manager_caches(व्योम);
व्योम f2fs_destroy_segment_manager_caches(व्योम);
पूर्णांक f2fs_rw_hपूर्णांक_to_seg_type(क्रमागत rw_hपूर्णांक hपूर्णांक);
क्रमागत rw_hपूर्णांक f2fs_io_type_to_rw_hपूर्णांक(काष्ठा f2fs_sb_info *sbi,
			क्रमागत page_type type, क्रमागत temp_type temp);
अचिन्हित पूर्णांक f2fs_usable_segs_in_sec(काष्ठा f2fs_sb_info *sbi,
			अचिन्हित पूर्णांक segno);
अचिन्हित पूर्णांक f2fs_usable_blks_in_seg(काष्ठा f2fs_sb_info *sbi,
			अचिन्हित पूर्णांक segno);

/*
 * checkpoपूर्णांक.c
 */
व्योम f2fs_stop_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi, bool end_io);
काष्ठा page *f2fs_grab_meta_page(काष्ठा f2fs_sb_info *sbi, pgoff_t index);
काष्ठा page *f2fs_get_meta_page(काष्ठा f2fs_sb_info *sbi, pgoff_t index);
काष्ठा page *f2fs_get_meta_page_retry(काष्ठा f2fs_sb_info *sbi, pgoff_t index);
काष्ठा page *f2fs_get_पंचांगp_page(काष्ठा f2fs_sb_info *sbi, pgoff_t index);
bool f2fs_is_valid_blkaddr(काष्ठा f2fs_sb_info *sbi,
					block_t blkaddr, पूर्णांक type);
पूर्णांक f2fs_ra_meta_pages(काष्ठा f2fs_sb_info *sbi, block_t start, पूर्णांक nrpages,
			पूर्णांक type, bool sync);
व्योम f2fs_ra_meta_pages_cond(काष्ठा f2fs_sb_info *sbi, pgoff_t index);
दीर्घ f2fs_sync_meta_pages(काष्ठा f2fs_sb_info *sbi, क्रमागत page_type type,
			दीर्घ nr_to_ग_लिखो, क्रमागत iostat_type io_type);
व्योम f2fs_add_ino_entry(काष्ठा f2fs_sb_info *sbi, nid_t ino, पूर्णांक type);
व्योम f2fs_हटाओ_ino_entry(काष्ठा f2fs_sb_info *sbi, nid_t ino, पूर्णांक type);
व्योम f2fs_release_ino_entry(काष्ठा f2fs_sb_info *sbi, bool all);
bool f2fs_exist_written_data(काष्ठा f2fs_sb_info *sbi, nid_t ino, पूर्णांक mode);
व्योम f2fs_set_dirty_device(काष्ठा f2fs_sb_info *sbi, nid_t ino,
					अचिन्हित पूर्णांक devidx, पूर्णांक type);
bool f2fs_is_dirty_device(काष्ठा f2fs_sb_info *sbi, nid_t ino,
					अचिन्हित पूर्णांक devidx, पूर्णांक type);
पूर्णांक f2fs_sync_inode_meta(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_acquire_orphan_inode(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_release_orphan_inode(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_add_orphan_inode(काष्ठा inode *inode);
व्योम f2fs_हटाओ_orphan_inode(काष्ठा f2fs_sb_info *sbi, nid_t ino);
पूर्णांक f2fs_recover_orphan_inodes(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_get_valid_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_update_dirty_page(काष्ठा inode *inode, काष्ठा page *page);
व्योम f2fs_हटाओ_dirty_inode(काष्ठा inode *inode);
पूर्णांक f2fs_sync_dirty_inodes(काष्ठा f2fs_sb_info *sbi, क्रमागत inode_type type);
व्योम f2fs_रुको_on_all_pages(काष्ठा f2fs_sb_info *sbi, पूर्णांक type);
u64 f2fs_get_sectors_written(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_ग_लिखो_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi, काष्ठा cp_control *cpc);
व्योम f2fs_init_ino_entry_info(काष्ठा f2fs_sb_info *sbi);
पूर्णांक __init f2fs_create_checkpoपूर्णांक_caches(व्योम);
व्योम f2fs_destroy_checkpoपूर्णांक_caches(व्योम);
पूर्णांक f2fs_issue_checkpoपूर्णांक(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_start_ckpt_thपढ़ो(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_stop_ckpt_thपढ़ो(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_init_ckpt_req_control(काष्ठा f2fs_sb_info *sbi);

/*
 * data.c
 */
पूर्णांक __init f2fs_init_bioset(व्योम);
व्योम f2fs_destroy_bioset(व्योम);
पूर्णांक f2fs_init_bio_entry_cache(व्योम);
व्योम f2fs_destroy_bio_entry_cache(व्योम);
व्योम f2fs_submit_bio(काष्ठा f2fs_sb_info *sbi,
				काष्ठा bio *bio, क्रमागत page_type type);
व्योम f2fs_submit_merged_ग_लिखो(काष्ठा f2fs_sb_info *sbi, क्रमागत page_type type);
व्योम f2fs_submit_merged_ग_लिखो_cond(काष्ठा f2fs_sb_info *sbi,
				काष्ठा inode *inode, काष्ठा page *page,
				nid_t ino, क्रमागत page_type type);
व्योम f2fs_submit_merged_ipu_ग_लिखो(काष्ठा f2fs_sb_info *sbi,
					काष्ठा bio **bio, काष्ठा page *page);
व्योम f2fs_flush_merged_ग_लिखोs(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_submit_page_bio(काष्ठा f2fs_io_info *fio);
पूर्णांक f2fs_merge_page_bio(काष्ठा f2fs_io_info *fio);
व्योम f2fs_submit_page_ग_लिखो(काष्ठा f2fs_io_info *fio);
काष्ठा block_device *f2fs_target_device(काष्ठा f2fs_sb_info *sbi,
			block_t blk_addr, काष्ठा bio *bio);
पूर्णांक f2fs_target_device_index(काष्ठा f2fs_sb_info *sbi, block_t blkaddr);
व्योम f2fs_set_data_blkaddr(काष्ठा dnode_of_data *dn);
व्योम f2fs_update_data_blkaddr(काष्ठा dnode_of_data *dn, block_t blkaddr);
पूर्णांक f2fs_reserve_new_blocks(काष्ठा dnode_of_data *dn, blkcnt_t count);
पूर्णांक f2fs_reserve_new_block(काष्ठा dnode_of_data *dn);
पूर्णांक f2fs_get_block(काष्ठा dnode_of_data *dn, pgoff_t index);
पूर्णांक f2fs_pपुनः_स्मृतिate_blocks(काष्ठा kiocb *iocb, काष्ठा iov_iter *from);
पूर्णांक f2fs_reserve_block(काष्ठा dnode_of_data *dn, pgoff_t index);
काष्ठा page *f2fs_get_पढ़ो_data_page(काष्ठा inode *inode, pgoff_t index,
			पूर्णांक op_flags, bool क्रम_ग_लिखो);
काष्ठा page *f2fs_find_data_page(काष्ठा inode *inode, pgoff_t index);
काष्ठा page *f2fs_get_lock_data_page(काष्ठा inode *inode, pgoff_t index,
			bool क्रम_ग_लिखो);
काष्ठा page *f2fs_get_new_data_page(काष्ठा inode *inode,
			काष्ठा page *ipage, pgoff_t index, bool new_i_size);
पूर्णांक f2fs_करो_ग_लिखो_data_page(काष्ठा f2fs_io_info *fio);
व्योम f2fs_करो_map_lock(काष्ठा f2fs_sb_info *sbi, पूर्णांक flag, bool lock);
पूर्णांक f2fs_map_blocks(काष्ठा inode *inode, काष्ठा f2fs_map_blocks *map,
			पूर्णांक create, पूर्णांक flag);
पूर्णांक f2fs_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
			u64 start, u64 len);
पूर्णांक f2fs_encrypt_one_page(काष्ठा f2fs_io_info *fio);
bool f2fs_should_update_inplace(काष्ठा inode *inode, काष्ठा f2fs_io_info *fio);
bool f2fs_should_update_outplace(काष्ठा inode *inode, काष्ठा f2fs_io_info *fio);
पूर्णांक f2fs_ग_लिखो_single_data_page(काष्ठा page *page, पूर्णांक *submitted,
				काष्ठा bio **bio, sector_t *last_block,
				काष्ठा ग_लिखोback_control *wbc,
				क्रमागत iostat_type io_type,
				पूर्णांक compr_blocks, bool allow_balance);
व्योम f2fs_invalidate_page(काष्ठा page *page, अचिन्हित पूर्णांक offset,
			अचिन्हित पूर्णांक length);
पूर्णांक f2fs_release_page(काष्ठा page *page, gfp_t रुको);
#अगर_घोषित CONFIG_MIGRATION
पूर्णांक f2fs_migrate_page(काष्ठा address_space *mapping, काष्ठा page *newpage,
			काष्ठा page *page, क्रमागत migrate_mode mode);
#पूर्ण_अगर
bool f2fs_overग_लिखो_io(काष्ठा inode *inode, loff_t pos, माप_प्रकार len);
व्योम f2fs_clear_page_cache_dirty_tag(काष्ठा page *page);
पूर्णांक f2fs_init_post_पढ़ो_processing(व्योम);
व्योम f2fs_destroy_post_पढ़ो_processing(व्योम);
पूर्णांक f2fs_init_post_पढ़ो_wq(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_destroy_post_पढ़ो_wq(काष्ठा f2fs_sb_info *sbi);

/*
 * gc.c
 */
पूर्णांक f2fs_start_gc_thपढ़ो(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_stop_gc_thपढ़ो(काष्ठा f2fs_sb_info *sbi);
block_t f2fs_start_bidx_of_node(अचिन्हित पूर्णांक node_ofs, काष्ठा inode *inode);
पूर्णांक f2fs_gc(काष्ठा f2fs_sb_info *sbi, bool sync, bool background, bool क्रमce,
			अचिन्हित पूर्णांक segno);
व्योम f2fs_build_gc_manager(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_resize_fs(काष्ठा f2fs_sb_info *sbi, __u64 block_count);
पूर्णांक __init f2fs_create_garbage_collection_cache(व्योम);
व्योम f2fs_destroy_garbage_collection_cache(व्योम);

/*
 * recovery.c
 */
पूर्णांक f2fs_recover_fsync_data(काष्ठा f2fs_sb_info *sbi, bool check_only);
bool f2fs_space_क्रम_roll_क्रमward(काष्ठा f2fs_sb_info *sbi);

/*
 * debug.c
 */
#अगर_घोषित CONFIG_F2FS_STAT_FS
काष्ठा f2fs_stat_info अणु
	काष्ठा list_head stat_list;
	काष्ठा f2fs_sb_info *sbi;
	पूर्णांक all_area_segs, sit_area_segs, nat_area_segs, ssa_area_segs;
	पूर्णांक मुख्य_area_segs, मुख्य_area_sections, मुख्य_area_zones;
	अचिन्हित दीर्घ दीर्घ hit_largest, hit_cached, hit_rbtree;
	अचिन्हित दीर्घ दीर्घ hit_total, total_ext;
	पूर्णांक ext_tree, zombie_tree, ext_node;
	पूर्णांक ndirty_node, ndirty_dent, ndirty_meta, ndirty_imeta;
	पूर्णांक ndirty_data, ndirty_qdata;
	पूर्णांक inmem_pages;
	अचिन्हित पूर्णांक ndirty_dirs, ndirty_files, nquota_files, ndirty_all;
	पूर्णांक nats, dirty_nats, sits, dirty_sits;
	पूर्णांक मुक्त_nids, avail_nids, alloc_nids;
	पूर्णांक total_count, utilization;
	पूर्णांक bg_gc, nr_wb_cp_data, nr_wb_data;
	पूर्णांक nr_rd_data, nr_rd_node, nr_rd_meta;
	पूर्णांक nr_dio_पढ़ो, nr_dio_ग_लिखो;
	अचिन्हित पूर्णांक io_skip_bggc, other_skip_bggc;
	पूर्णांक nr_flushing, nr_flushed, flush_list_empty;
	पूर्णांक nr_discarding, nr_discarded;
	पूर्णांक nr_discard_cmd;
	अचिन्हित पूर्णांक undiscard_blks;
	पूर्णांक nr_issued_ckpt, nr_total_ckpt, nr_queued_ckpt;
	अचिन्हित पूर्णांक cur_ckpt_समय, peak_ckpt_समय;
	पूर्णांक अंतरभूत_xattr, अंतरभूत_inode, अंतरभूत_dir, append, update, orphans;
	पूर्णांक compr_inode;
	अचिन्हित दीर्घ दीर्घ compr_blocks;
	पूर्णांक aw_cnt, max_aw_cnt, vw_cnt, max_vw_cnt;
	अचिन्हित पूर्णांक valid_count, valid_node_count, valid_inode_count, discard_blks;
	अचिन्हित पूर्णांक bimodal, avg_vblocks;
	पूर्णांक util_मुक्त, util_valid, util_invalid;
	पूर्णांक rsvd_segs, overp_segs;
	पूर्णांक dirty_count, node_pages, meta_pages;
	पूर्णांक preमुक्त_count, call_count, cp_count, bg_cp_count;
	पूर्णांक tot_segs, node_segs, data_segs, मुक्त_segs, मुक्त_secs;
	पूर्णांक bg_node_segs, bg_data_segs;
	पूर्णांक tot_blks, data_blks, node_blks;
	पूर्णांक bg_data_blks, bg_node_blks;
	अचिन्हित दीर्घ दीर्घ skipped_atomic_files[2];
	पूर्णांक curseg[NR_CURSEG_TYPE];
	पूर्णांक cursec[NR_CURSEG_TYPE];
	पूर्णांक curzone[NR_CURSEG_TYPE];
	अचिन्हित पूर्णांक dirty_seg[NR_CURSEG_TYPE];
	अचिन्हित पूर्णांक full_seg[NR_CURSEG_TYPE];
	अचिन्हित पूर्णांक valid_blks[NR_CURSEG_TYPE];

	अचिन्हित पूर्णांक meta_count[META_MAX];
	अचिन्हित पूर्णांक segment_count[2];
	अचिन्हित पूर्णांक block_count[2];
	अचिन्हित पूर्णांक inplace_count;
	अचिन्हित दीर्घ दीर्घ base_mem, cache_mem, page_mem;
पूर्ण;

अटल अंतरभूत काष्ठा f2fs_stat_info *F2FS_STAT(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (काष्ठा f2fs_stat_info *)sbi->stat_info;
पूर्ण

#घोषणा stat_inc_cp_count(si)		((si)->cp_count++)
#घोषणा stat_inc_bg_cp_count(si)	((si)->bg_cp_count++)
#घोषणा stat_inc_call_count(si)		((si)->call_count++)
#घोषणा stat_inc_bggc_count(si)		((si)->bg_gc++)
#घोषणा stat_io_skip_bggc_count(sbi)	((sbi)->io_skip_bggc++)
#घोषणा stat_other_skip_bggc_count(sbi)	((sbi)->other_skip_bggc++)
#घोषणा stat_inc_dirty_inode(sbi, type)	((sbi)->ndirty_inode[type]++)
#घोषणा stat_dec_dirty_inode(sbi, type)	((sbi)->ndirty_inode[type]--)
#घोषणा stat_inc_total_hit(sbi)		(atomic64_inc(&(sbi)->total_hit_ext))
#घोषणा stat_inc_rbtree_node_hit(sbi)	(atomic64_inc(&(sbi)->पढ़ो_hit_rbtree))
#घोषणा stat_inc_largest_node_hit(sbi)	(atomic64_inc(&(sbi)->पढ़ो_hit_largest))
#घोषणा stat_inc_cached_node_hit(sbi)	(atomic64_inc(&(sbi)->पढ़ो_hit_cached))
#घोषणा stat_inc_अंतरभूत_xattr(inode)					\
	करो अणु								\
		अगर (f2fs_has_अंतरभूत_xattr(inode))			\
			(atomic_inc(&F2FS_I_SB(inode)->अंतरभूत_xattr));	\
	पूर्ण जबतक (0)
#घोषणा stat_dec_अंतरभूत_xattr(inode)					\
	करो अणु								\
		अगर (f2fs_has_अंतरभूत_xattr(inode))			\
			(atomic_dec(&F2FS_I_SB(inode)->अंतरभूत_xattr));	\
	पूर्ण जबतक (0)
#घोषणा stat_inc_अंतरभूत_inode(inode)					\
	करो अणु								\
		अगर (f2fs_has_अंतरभूत_data(inode))			\
			(atomic_inc(&F2FS_I_SB(inode)->अंतरभूत_inode));	\
	पूर्ण जबतक (0)
#घोषणा stat_dec_अंतरभूत_inode(inode)					\
	करो अणु								\
		अगर (f2fs_has_अंतरभूत_data(inode))			\
			(atomic_dec(&F2FS_I_SB(inode)->अंतरभूत_inode));	\
	पूर्ण जबतक (0)
#घोषणा stat_inc_अंतरभूत_dir(inode)					\
	करो अणु								\
		अगर (f2fs_has_अंतरभूत_dentry(inode))			\
			(atomic_inc(&F2FS_I_SB(inode)->अंतरभूत_dir));	\
	पूर्ण जबतक (0)
#घोषणा stat_dec_अंतरभूत_dir(inode)					\
	करो अणु								\
		अगर (f2fs_has_अंतरभूत_dentry(inode))			\
			(atomic_dec(&F2FS_I_SB(inode)->अंतरभूत_dir));	\
	पूर्ण जबतक (0)
#घोषणा stat_inc_compr_inode(inode)					\
	करो अणु								\
		अगर (f2fs_compressed_file(inode))			\
			(atomic_inc(&F2FS_I_SB(inode)->compr_inode));	\
	पूर्ण जबतक (0)
#घोषणा stat_dec_compr_inode(inode)					\
	करो अणु								\
		अगर (f2fs_compressed_file(inode))			\
			(atomic_dec(&F2FS_I_SB(inode)->compr_inode));	\
	पूर्ण जबतक (0)
#घोषणा stat_add_compr_blocks(inode, blocks)				\
		(atomic64_add(blocks, &F2FS_I_SB(inode)->compr_blocks))
#घोषणा stat_sub_compr_blocks(inode, blocks)				\
		(atomic64_sub(blocks, &F2FS_I_SB(inode)->compr_blocks))
#घोषणा stat_inc_meta_count(sbi, blkaddr)				\
	करो अणु								\
		अगर (blkaddr < SIT_I(sbi)->sit_base_addr)		\
			atomic_inc(&(sbi)->meta_count[META_CP]);	\
		अन्यथा अगर (blkaddr < NM_I(sbi)->nat_blkaddr)		\
			atomic_inc(&(sbi)->meta_count[META_SIT]);	\
		अन्यथा अगर (blkaddr < SM_I(sbi)->ssa_blkaddr)		\
			atomic_inc(&(sbi)->meta_count[META_NAT]);	\
		अन्यथा अगर (blkaddr < SM_I(sbi)->मुख्य_blkaddr)		\
			atomic_inc(&(sbi)->meta_count[META_SSA]);	\
	पूर्ण जबतक (0)
#घोषणा stat_inc_seg_type(sbi, curseg)					\
		((sbi)->segment_count[(curseg)->alloc_type]++)
#घोषणा stat_inc_block_count(sbi, curseg)				\
		((sbi)->block_count[(curseg)->alloc_type]++)
#घोषणा stat_inc_inplace_blocks(sbi)					\
		(atomic_inc(&(sbi)->inplace_count))
#घोषणा stat_update_max_atomic_ग_लिखो(inode)				\
	करो अणु								\
		पूर्णांक cur = F2FS_I_SB(inode)->atomic_files;	\
		पूर्णांक max = atomic_पढ़ो(&F2FS_I_SB(inode)->max_aw_cnt);	\
		अगर (cur > max)						\
			atomic_set(&F2FS_I_SB(inode)->max_aw_cnt, cur);	\
	पूर्ण जबतक (0)
#घोषणा stat_inc_अस्थिर_ग_लिखो(inode)					\
		(atomic_inc(&F2FS_I_SB(inode)->vw_cnt))
#घोषणा stat_dec_अस्थिर_ग_लिखो(inode)					\
		(atomic_dec(&F2FS_I_SB(inode)->vw_cnt))
#घोषणा stat_update_max_अस्थिर_ग_लिखो(inode)				\
	करो अणु								\
		पूर्णांक cur = atomic_पढ़ो(&F2FS_I_SB(inode)->vw_cnt);	\
		पूर्णांक max = atomic_पढ़ो(&F2FS_I_SB(inode)->max_vw_cnt);	\
		अगर (cur > max)						\
			atomic_set(&F2FS_I_SB(inode)->max_vw_cnt, cur);	\
	पूर्ण जबतक (0)
#घोषणा stat_inc_seg_count(sbi, type, gc_type)				\
	करो अणु								\
		काष्ठा f2fs_stat_info *si = F2FS_STAT(sbi);		\
		si->tot_segs++;						\
		अगर ((type) == SUM_TYPE_DATA) अणु				\
			si->data_segs++;				\
			si->bg_data_segs += (gc_type == BG_GC) ? 1 : 0;	\
		पूर्ण अन्यथा अणु						\
			si->node_segs++;				\
			si->bg_node_segs += (gc_type == BG_GC) ? 1 : 0;	\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा stat_inc_tot_blk_count(si, blks)				\
	((si)->tot_blks += (blks))

#घोषणा stat_inc_data_blk_count(sbi, blks, gc_type)			\
	करो अणु								\
		काष्ठा f2fs_stat_info *si = F2FS_STAT(sbi);		\
		stat_inc_tot_blk_count(si, blks);			\
		si->data_blks += (blks);				\
		si->bg_data_blks += ((gc_type) == BG_GC) ? (blks) : 0;	\
	पूर्ण जबतक (0)

#घोषणा stat_inc_node_blk_count(sbi, blks, gc_type)			\
	करो अणु								\
		काष्ठा f2fs_stat_info *si = F2FS_STAT(sbi);		\
		stat_inc_tot_blk_count(si, blks);			\
		si->node_blks += (blks);				\
		si->bg_node_blks += ((gc_type) == BG_GC) ? (blks) : 0;	\
	पूर्ण जबतक (0)

पूर्णांक f2fs_build_stats(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_destroy_stats(काष्ठा f2fs_sb_info *sbi);
व्योम __init f2fs_create_root_stats(व्योम);
व्योम f2fs_destroy_root_stats(व्योम);
व्योम f2fs_update_sit_info(काष्ठा f2fs_sb_info *sbi);
#अन्यथा
#घोषणा stat_inc_cp_count(si)				करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_bg_cp_count(si)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_call_count(si)				करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_bggc_count(si)				करो अणु पूर्ण जबतक (0)
#घोषणा stat_io_skip_bggc_count(sbi)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_other_skip_bggc_count(sbi)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_dirty_inode(sbi, type)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_dec_dirty_inode(sbi, type)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_total_hit(sbi)				करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_rbtree_node_hit(sbi)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_largest_node_hit(sbi)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_cached_node_hit(sbi)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_अंतरभूत_xattr(inode)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_dec_अंतरभूत_xattr(inode)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_अंतरभूत_inode(inode)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_dec_अंतरभूत_inode(inode)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_अंतरभूत_dir(inode)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_dec_अंतरभूत_dir(inode)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_compr_inode(inode)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_dec_compr_inode(inode)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_add_compr_blocks(inode, blocks)		करो अणु पूर्ण जबतक (0)
#घोषणा stat_sub_compr_blocks(inode, blocks)		करो अणु पूर्ण जबतक (0)
#घोषणा stat_update_max_atomic_ग_लिखो(inode)		करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_अस्थिर_ग_लिखो(inode)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_dec_अस्थिर_ग_लिखो(inode)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_update_max_अस्थिर_ग_लिखो(inode)		करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_meta_count(sbi, blkaddr)		करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_seg_type(sbi, curseg)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_block_count(sbi, curseg)		करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_inplace_blocks(sbi)			करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_seg_count(sbi, type, gc_type)		करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_tot_blk_count(si, blks)		करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_data_blk_count(sbi, blks, gc_type)	करो अणु पूर्ण जबतक (0)
#घोषणा stat_inc_node_blk_count(sbi, blks, gc_type)	करो अणु पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक f2fs_build_stats(काष्ठा f2fs_sb_info *sbi) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम f2fs_destroy_stats(काष्ठा f2fs_sb_info *sbi) अणु पूर्ण
अटल अंतरभूत व्योम __init f2fs_create_root_stats(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम f2fs_destroy_root_stats(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम f2fs_update_sit_info(काष्ठा f2fs_sb_info *sbi) अणुपूर्ण
#पूर्ण_अगर

बाह्य स्थिर काष्ठा file_operations f2fs_dir_operations;
बाह्य स्थिर काष्ठा file_operations f2fs_file_operations;
बाह्य स्थिर काष्ठा inode_operations f2fs_file_inode_operations;
बाह्य स्थिर काष्ठा address_space_operations f2fs_dblock_aops;
बाह्य स्थिर काष्ठा address_space_operations f2fs_node_aops;
बाह्य स्थिर काष्ठा address_space_operations f2fs_meta_aops;
बाह्य स्थिर काष्ठा inode_operations f2fs_dir_inode_operations;
बाह्य स्थिर काष्ठा inode_operations f2fs_symlink_inode_operations;
बाह्य स्थिर काष्ठा inode_operations f2fs_encrypted_symlink_inode_operations;
बाह्य स्थिर काष्ठा inode_operations f2fs_special_inode_operations;
बाह्य काष्ठा kmem_cache *f2fs_inode_entry_slab;

/*
 * अंतरभूत.c
 */
bool f2fs_may_अंतरभूत_data(काष्ठा inode *inode);
bool f2fs_may_अंतरभूत_dentry(काष्ठा inode *inode);
व्योम f2fs_करो_पढ़ो_अंतरभूत_data(काष्ठा page *page, काष्ठा page *ipage);
व्योम f2fs_truncate_अंतरभूत_inode(काष्ठा inode *inode,
						काष्ठा page *ipage, u64 from);
पूर्णांक f2fs_पढ़ो_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *page);
पूर्णांक f2fs_convert_अंतरभूत_page(काष्ठा dnode_of_data *dn, काष्ठा page *page);
पूर्णांक f2fs_convert_अंतरभूत_inode(काष्ठा inode *inode);
पूर्णांक f2fs_try_convert_अंतरभूत_dir(काष्ठा inode *dir, काष्ठा dentry *dentry);
पूर्णांक f2fs_ग_लिखो_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *page);
पूर्णांक f2fs_recover_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *npage);
काष्ठा f2fs_dir_entry *f2fs_find_in_अंतरभूत_dir(काष्ठा inode *dir,
					स्थिर काष्ठा f2fs_filename *fname,
					काष्ठा page **res_page);
पूर्णांक f2fs_make_empty_अंतरभूत_dir(काष्ठा inode *inode, काष्ठा inode *parent,
			काष्ठा page *ipage);
पूर्णांक f2fs_add_अंतरभूत_entry(काष्ठा inode *dir, स्थिर काष्ठा f2fs_filename *fname,
			काष्ठा inode *inode, nid_t ino, umode_t mode);
व्योम f2fs_delete_अंतरभूत_entry(काष्ठा f2fs_dir_entry *dentry,
				काष्ठा page *page, काष्ठा inode *dir,
				काष्ठा inode *inode);
bool f2fs_empty_अंतरभूत_dir(काष्ठा inode *dir);
पूर्णांक f2fs_पढ़ो_अंतरभूत_dir(काष्ठा file *file, काष्ठा dir_context *ctx,
			काष्ठा fscrypt_str *fstr);
पूर्णांक f2fs_अंतरभूत_data_fiemap(काष्ठा inode *inode,
			काष्ठा fiemap_extent_info *fieinfo,
			__u64 start, __u64 len);

/*
 * shrinker.c
 */
अचिन्हित दीर्घ f2fs_shrink_count(काष्ठा shrinker *shrink,
			काष्ठा shrink_control *sc);
अचिन्हित दीर्घ f2fs_shrink_scan(काष्ठा shrinker *shrink,
			काष्ठा shrink_control *sc);
व्योम f2fs_join_shrinker(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_leave_shrinker(काष्ठा f2fs_sb_info *sbi);

/*
 * extent_cache.c
 */
काष्ठा rb_entry *f2fs_lookup_rb_tree(काष्ठा rb_root_cached *root,
				काष्ठा rb_entry *cached_re, अचिन्हित पूर्णांक ofs);
काष्ठा rb_node **f2fs_lookup_rb_tree_ext(काष्ठा f2fs_sb_info *sbi,
				काष्ठा rb_root_cached *root,
				काष्ठा rb_node **parent,
				अचिन्हित दीर्घ दीर्घ key, bool *left_most);
काष्ठा rb_node **f2fs_lookup_rb_tree_क्रम_insert(काष्ठा f2fs_sb_info *sbi,
				काष्ठा rb_root_cached *root,
				काष्ठा rb_node **parent,
				अचिन्हित पूर्णांक ofs, bool *lefपंचांगost);
काष्ठा rb_entry *f2fs_lookup_rb_tree_ret(काष्ठा rb_root_cached *root,
		काष्ठा rb_entry *cached_re, अचिन्हित पूर्णांक ofs,
		काष्ठा rb_entry **prev_entry, काष्ठा rb_entry **next_entry,
		काष्ठा rb_node ***insert_p, काष्ठा rb_node **insert_parent,
		bool क्रमce, bool *lefपंचांगost);
bool f2fs_check_rb_tree_consistence(काष्ठा f2fs_sb_info *sbi,
				काष्ठा rb_root_cached *root, bool check_key);
अचिन्हित पूर्णांक f2fs_shrink_extent_tree(काष्ठा f2fs_sb_info *sbi, पूर्णांक nr_shrink);
व्योम f2fs_init_extent_tree(काष्ठा inode *inode, काष्ठा page *ipage);
व्योम f2fs_drop_extent_tree(काष्ठा inode *inode);
अचिन्हित पूर्णांक f2fs_destroy_extent_node(काष्ठा inode *inode);
व्योम f2fs_destroy_extent_tree(काष्ठा inode *inode);
bool f2fs_lookup_extent_cache(काष्ठा inode *inode, pgoff_t pgofs,
			काष्ठा extent_info *ei);
व्योम f2fs_update_extent_cache(काष्ठा dnode_of_data *dn);
व्योम f2fs_update_extent_cache_range(काष्ठा dnode_of_data *dn,
			pgoff_t fofs, block_t blkaddr, अचिन्हित पूर्णांक len);
व्योम f2fs_init_extent_cache_info(काष्ठा f2fs_sb_info *sbi);
पूर्णांक __init f2fs_create_extent_cache(व्योम);
व्योम f2fs_destroy_extent_cache(व्योम);

/*
 * sysfs.c
 */
पूर्णांक __init f2fs_init_sysfs(व्योम);
व्योम f2fs_निकास_sysfs(व्योम);
पूर्णांक f2fs_रेजिस्टर_sysfs(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_unरेजिस्टर_sysfs(काष्ठा f2fs_sb_info *sbi);

/* verity.c */
बाह्य स्थिर काष्ठा fsverity_operations f2fs_verityops;

/*
 * crypto support
 */
अटल अंतरभूत bool f2fs_encrypted_file(काष्ठा inode *inode)
अणु
	वापस IS_ENCRYPTED(inode) && S_ISREG(inode->i_mode);
पूर्ण

अटल अंतरभूत व्योम f2fs_set_encrypted_inode(काष्ठा inode *inode)
अणु
#अगर_घोषित CONFIG_FS_ENCRYPTION
	file_set_encrypt(inode);
	f2fs_set_inode_flags(inode);
#पूर्ण_अगर
पूर्ण

/*
 * Returns true अगर the पढ़ोs of the inode's data need to undergo some
 * postprocessing step, like decryption or authenticity verअगरication.
 */
अटल अंतरभूत bool f2fs_post_पढ़ो_required(काष्ठा inode *inode)
अणु
	वापस f2fs_encrypted_file(inode) || fsverity_active(inode) ||
		f2fs_compressed_file(inode);
पूर्ण

/*
 * compress.c
 */
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
bool f2fs_is_compressed_page(काष्ठा page *page);
काष्ठा page *f2fs_compress_control_page(काष्ठा page *page);
पूर्णांक f2fs_prepare_compress_overग_लिखो(काष्ठा inode *inode,
			काष्ठा page **pagep, pgoff_t index, व्योम **fsdata);
bool f2fs_compress_ग_लिखो_end(काष्ठा inode *inode, व्योम *fsdata,
					pgoff_t index, अचिन्हित copied);
पूर्णांक f2fs_truncate_partial_cluster(काष्ठा inode *inode, u64 from, bool lock);
व्योम f2fs_compress_ग_लिखो_end_io(काष्ठा bio *bio, काष्ठा page *page);
bool f2fs_is_compress_backend_पढ़ोy(काष्ठा inode *inode);
पूर्णांक f2fs_init_compress_mempool(व्योम);
व्योम f2fs_destroy_compress_mempool(व्योम);
व्योम f2fs_end_पढ़ो_compressed_page(काष्ठा page *page, bool failed);
bool f2fs_cluster_is_empty(काष्ठा compress_ctx *cc);
bool f2fs_cluster_can_merge_page(काष्ठा compress_ctx *cc, pgoff_t index);
व्योम f2fs_compress_ctx_add_page(काष्ठा compress_ctx *cc, काष्ठा page *page);
पूर्णांक f2fs_ग_लिखो_multi_pages(काष्ठा compress_ctx *cc,
						पूर्णांक *submitted,
						काष्ठा ग_लिखोback_control *wbc,
						क्रमागत iostat_type io_type);
पूर्णांक f2fs_is_compressed_cluster(काष्ठा inode *inode, pgoff_t index);
पूर्णांक f2fs_पढ़ो_multi_pages(काष्ठा compress_ctx *cc, काष्ठा bio **bio_ret,
				अचिन्हित nr_pages, sector_t *last_block_in_bio,
				bool is_पढ़ोahead, bool क्रम_ग_लिखो);
काष्ठा decompress_io_ctx *f2fs_alloc_dic(काष्ठा compress_ctx *cc);
व्योम f2fs_decompress_end_io(काष्ठा decompress_io_ctx *dic, bool failed);
व्योम f2fs_put_page_dic(काष्ठा page *page);
पूर्णांक f2fs_init_compress_ctx(काष्ठा compress_ctx *cc);
व्योम f2fs_destroy_compress_ctx(काष्ठा compress_ctx *cc, bool reuse);
व्योम f2fs_init_compress_info(काष्ठा f2fs_sb_info *sbi);
पूर्णांक f2fs_init_page_array_cache(काष्ठा f2fs_sb_info *sbi);
व्योम f2fs_destroy_page_array_cache(काष्ठा f2fs_sb_info *sbi);
पूर्णांक __init f2fs_init_compress_cache(व्योम);
व्योम f2fs_destroy_compress_cache(व्योम);
#घोषणा inc_compr_inode_stat(inode)					\
	करो अणु								\
		काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);		\
		sbi->compr_new_inode++;					\
	पूर्ण जबतक (0)
#घोषणा add_compr_block_stat(inode, blocks)				\
	करो अणु								\
		काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);		\
		पूर्णांक dअगरf = F2FS_I(inode)->i_cluster_size - blocks;	\
		sbi->compr_written_block += blocks;			\
		sbi->compr_saved_block += dअगरf;				\
	पूर्ण जबतक (0)
#अन्यथा
अटल अंतरभूत bool f2fs_is_compressed_page(काष्ठा page *page) अणु वापस false; पूर्ण
अटल अंतरभूत bool f2fs_is_compress_backend_पढ़ोy(काष्ठा inode *inode)
अणु
	अगर (!f2fs_compressed_file(inode))
		वापस true;
	/* not support compression */
	वापस false;
पूर्ण
अटल अंतरभूत काष्ठा page *f2fs_compress_control_page(काष्ठा page *page)
अणु
	WARN_ON_ONCE(1);
	वापस ERR_PTR(-EINVAL);
पूर्ण
अटल अंतरभूत पूर्णांक f2fs_init_compress_mempool(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम f2fs_destroy_compress_mempool(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम f2fs_end_पढ़ो_compressed_page(काष्ठा page *page, bool failed)
अणु
	WARN_ON_ONCE(1);
पूर्ण
अटल अंतरभूत व्योम f2fs_put_page_dic(काष्ठा page *page)
अणु
	WARN_ON_ONCE(1);
पूर्ण
अटल अंतरभूत पूर्णांक f2fs_init_page_array_cache(काष्ठा f2fs_sb_info *sbi) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम f2fs_destroy_page_array_cache(काष्ठा f2fs_sb_info *sbi) अणु पूर्ण
अटल अंतरभूत पूर्णांक __init f2fs_init_compress_cache(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम f2fs_destroy_compress_cache(व्योम) अणु पूर्ण
#घोषणा inc_compr_inode_stat(inode)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल अंतरभूत व्योम set_compress_context(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

	F2FS_I(inode)->i_compress_algorithm =
			F2FS_OPTION(sbi).compress_algorithm;
	F2FS_I(inode)->i_log_cluster_size =
			F2FS_OPTION(sbi).compress_log_size;
	F2FS_I(inode)->i_compress_flag =
			F2FS_OPTION(sbi).compress_chksum ?
				1 << COMPRESS_CHKSUM : 0;
	F2FS_I(inode)->i_cluster_size =
			1 << F2FS_I(inode)->i_log_cluster_size;
	अगर (F2FS_I(inode)->i_compress_algorithm == COMPRESS_LZ4 &&
			F2FS_OPTION(sbi).compress_level)
		F2FS_I(inode)->i_compress_flag |=
				F2FS_OPTION(sbi).compress_level <<
				COMPRESS_LEVEL_OFFSET;
	F2FS_I(inode)->i_flags |= F2FS_COMPR_FL;
	set_inode_flag(inode, FI_COMPRESSED_खाता);
	stat_inc_compr_inode(inode);
	inc_compr_inode_stat(inode);
	f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

अटल अंतरभूत bool f2fs_disable_compressed_file(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);

	अगर (!f2fs_compressed_file(inode))
		वापस true;
	अगर (S_ISREG(inode->i_mode) &&
		(get_dirty_pages(inode) || atomic_पढ़ो(&fi->i_compr_blocks)))
		वापस false;

	fi->i_flags &= ~F2FS_COMPR_FL;
	stat_dec_compr_inode(inode);
	clear_inode_flag(inode, FI_COMPRESSED_खाता);
	f2fs_mark_inode_dirty_sync(inode, true);
	वापस true;
पूर्ण

#घोषणा F2FS_FEATURE_FUNCS(name, flagname) \
अटल अंतरभूत पूर्णांक f2fs_sb_has_##name(काष्ठा f2fs_sb_info *sbi) \
अणु \
	वापस F2FS_HAS_FEATURE(sbi, F2FS_FEATURE_##flagname); \
पूर्ण

F2FS_FEATURE_FUNCS(encrypt, ENCRYPT);
F2FS_FEATURE_FUNCS(blkzoned, BLKZONED);
F2FS_FEATURE_FUNCS(extra_attr, EXTRA_ATTR);
F2FS_FEATURE_FUNCS(project_quota, PRJQUOTA);
F2FS_FEATURE_FUNCS(inode_chksum, INODE_CHKSUM);
F2FS_FEATURE_FUNCS(flexible_अंतरभूत_xattr, FLEXIBLE_INLINE_XATTR);
F2FS_FEATURE_FUNCS(quota_ino, QUOTA_INO);
F2FS_FEATURE_FUNCS(inode_crसमय, INODE_CRTIME);
F2FS_FEATURE_FUNCS(lost_found, LOST_FOUND);
F2FS_FEATURE_FUNCS(verity, VERITY);
F2FS_FEATURE_FUNCS(sb_chksum, SB_CHKSUM);
F2FS_FEATURE_FUNCS(हालfold, CASEFOLD);
F2FS_FEATURE_FUNCS(compression, COMPRESSION);

#अगर_घोषित CONFIG_BLK_DEV_ZONED
अटल अंतरभूत bool f2fs_blkz_is_seq(काष्ठा f2fs_sb_info *sbi, पूर्णांक devi,
				    block_t blkaddr)
अणु
	अचिन्हित पूर्णांक zno = blkaddr >> sbi->log_blocks_per_blkz;

	वापस test_bit(zno, FDEV(devi).blkz_seq);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool f2fs_hw_should_discard(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस f2fs_sb_has_blkzoned(sbi);
पूर्ण

अटल अंतरभूत bool f2fs_bdev_support_discard(काष्ठा block_device *bdev)
अणु
	वापस blk_queue_discard(bdev_get_queue(bdev)) ||
	       bdev_is_zoned(bdev);
पूर्ण

अटल अंतरभूत bool f2fs_hw_support_discard(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक i;

	अगर (!f2fs_is_multi_device(sbi))
		वापस f2fs_bdev_support_discard(sbi->sb->s_bdev);

	क्रम (i = 0; i < sbi->s_ndevs; i++)
		अगर (f2fs_bdev_support_discard(FDEV(i).bdev))
			वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool f2fs_realसमय_discard_enable(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (test_opt(sbi, DISCARD) && f2fs_hw_support_discard(sbi)) ||
					f2fs_hw_should_discard(sbi);
पूर्ण

अटल अंतरभूत bool f2fs_hw_is_पढ़ोonly(काष्ठा f2fs_sb_info *sbi)
अणु
	पूर्णांक i;

	अगर (!f2fs_is_multi_device(sbi))
		वापस bdev_पढ़ो_only(sbi->sb->s_bdev);

	क्रम (i = 0; i < sbi->s_ndevs; i++)
		अगर (bdev_पढ़ो_only(FDEV(i).bdev))
			वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool f2fs_lfs_mode(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस F2FS_OPTION(sbi).fs_mode == FS_MODE_LFS;
पूर्ण

अटल अंतरभूत bool f2fs_may_compress(काष्ठा inode *inode)
अणु
	अगर (IS_SWAPखाता(inode) || f2fs_is_pinned_file(inode) ||
				f2fs_is_atomic_file(inode) ||
				f2fs_is_अस्थिर_file(inode))
		वापस false;
	वापस S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode);
पूर्ण

अटल अंतरभूत व्योम f2fs_i_compr_blocks_update(काष्ठा inode *inode,
						u64 blocks, bool add)
अणु
	पूर्णांक dअगरf = F2FS_I(inode)->i_cluster_size - blocks;
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);

	/* करोn't update i_compr_blocks अगर saved blocks were released */
	अगर (!add && !atomic_पढ़ो(&fi->i_compr_blocks))
		वापस;

	अगर (add) अणु
		atomic_add(dअगरf, &fi->i_compr_blocks);
		stat_add_compr_blocks(inode, dअगरf);
	पूर्ण अन्यथा अणु
		atomic_sub(dअगरf, &fi->i_compr_blocks);
		stat_sub_compr_blocks(inode, dअगरf);
	पूर्ण
	f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

अटल अंतरभूत पूर्णांक block_unaligned_IO(काष्ठा inode *inode,
				काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	अचिन्हित पूर्णांक i_blkbits = READ_ONCE(inode->i_blkbits);
	अचिन्हित पूर्णांक blocksize_mask = (1 << i_blkbits) - 1;
	loff_t offset = iocb->ki_pos;
	अचिन्हित दीर्घ align = offset | iov_iter_alignment(iter);

	वापस align & blocksize_mask;
पूर्ण

अटल अंतरभूत पूर्णांक allow_outplace_dio(काष्ठा inode *inode,
				काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक rw = iov_iter_rw(iter);

	वापस (f2fs_lfs_mode(sbi) && (rw == WRITE) &&
				!block_unaligned_IO(inode, iocb, iter));
पूर्ण

अटल अंतरभूत bool f2fs_क्रमce_buffered_io(काष्ठा inode *inode,
				काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक rw = iov_iter_rw(iter);

	अगर (f2fs_post_पढ़ो_required(inode))
		वापस true;
	अगर (f2fs_is_multi_device(sbi))
		वापस true;
	/*
	 * क्रम blkzoned device, fallback direct IO to buffered IO, so
	 * all IOs can be serialized by log-काष्ठाured ग_लिखो.
	 */
	अगर (f2fs_sb_has_blkzoned(sbi))
		वापस true;
	अगर (f2fs_lfs_mode(sbi) && (rw == WRITE)) अणु
		अगर (block_unaligned_IO(inode, iocb, iter))
			वापस true;
		अगर (F2FS_IO_ALIGNED(sbi))
			वापस true;
	पूर्ण
	अगर (is_sbi_flag_set(F2FS_I_SB(inode), SBI_CP_DISABLED))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool f2fs_need_verity(स्थिर काष्ठा inode *inode, pgoff_t idx)
अणु
	वापस fsverity_active(inode) &&
	       idx < DIV_ROUND_UP(inode->i_size, PAGE_SIZE);
पूर्ण

#अगर_घोषित CONFIG_F2FS_FAULT_INJECTION
बाह्य व्योम f2fs_build_fault_attr(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक rate,
							अचिन्हित पूर्णांक type);
#अन्यथा
#घोषणा f2fs_build_fault_attr(sbi, rate, type)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल अंतरभूत bool is_journalled_quota(काष्ठा f2fs_sb_info *sbi)
अणु
#अगर_घोषित CONFIG_QUOTA
	अगर (f2fs_sb_has_quota_ino(sbi))
		वापस true;
	अगर (F2FS_OPTION(sbi).s_qf_names[USRQUOTA] ||
		F2FS_OPTION(sbi).s_qf_names[GRPQUOTA] ||
		F2FS_OPTION(sbi).s_qf_names[PRJQUOTA])
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

#घोषणा EFSBADCRC	EBADMSG		/* Bad CRC detected */
#घोषणा EFSCORRUPTED	EUCLEAN		/* Fileप्रणाली is corrupted */

#पूर्ण_अगर /* _LINUX_F2FS_H */
