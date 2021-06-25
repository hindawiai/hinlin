<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _BTRFS_CTREE_H_
#घोषणा _BTRFS_CTREE_H_

#समावेश <linux/btrfs.h>
#समावेश <linux/types.h>
#अगर_घोषित __KERNEL__
#समावेश <linux/मानकघोष.स>
#अन्यथा
#समावेश <मानकघोष.स>
#पूर्ण_अगर

/*
 * This header contains the काष्ठाure definitions and स्थिरants used
 * by file प्रणाली objects that can be retrieved using
 * the BTRFS_IOC_SEARCH_TREE ioctl.  That means basically anything that
 * is needed to describe a leaf node's key or item contents.
 */

/* holds poपूर्णांकers to all of the tree roots */
#घोषणा BTRFS_ROOT_TREE_OBJECTID 1ULL

/* stores inक्रमmation about which extents are in use, and reference counts */
#घोषणा BTRFS_EXTENT_TREE_OBJECTID 2ULL

/*
 * chunk tree stores translations from logical -> physical block numbering
 * the super block poपूर्णांकs to the chunk tree
 */
#घोषणा BTRFS_CHUNK_TREE_OBJECTID 3ULL

/*
 * stores inक्रमmation about which areas of a given device are in use.
 * one per device.  The tree of tree roots poपूर्णांकs to the device tree
 */
#घोषणा BTRFS_DEV_TREE_OBJECTID 4ULL

/* one per subvolume, storing files and directories */
#घोषणा BTRFS_FS_TREE_OBJECTID 5ULL

/* directory objectid inside the root tree */
#घोषणा BTRFS_ROOT_TREE_सूची_OBJECTID 6ULL

/* holds checksums of all the data extents */
#घोषणा BTRFS_CSUM_TREE_OBJECTID 7ULL

/* holds quota configuration and tracking */
#घोषणा BTRFS_QUOTA_TREE_OBJECTID 8ULL

/* क्रम storing items that use the BTRFS_UUID_KEY* types */
#घोषणा BTRFS_UUID_TREE_OBJECTID 9ULL

/* tracks मुक्त space in block groups. */
#घोषणा BTRFS_FREE_SPACE_TREE_OBJECTID 10ULL

/* device stats in the device tree */
#घोषणा BTRFS_DEV_STATS_OBJECTID 0ULL

/* क्रम storing balance parameters in the root tree */
#घोषणा BTRFS_BALANCE_OBJECTID -4ULL

/* orhpan objectid क्रम tracking unlinked/truncated files */
#घोषणा BTRFS_ORPHAN_OBJECTID -5ULL

/* करोes ग_लिखो ahead logging to speed up fsyncs */
#घोषणा BTRFS_TREE_LOG_OBJECTID -6ULL
#घोषणा BTRFS_TREE_LOG_FIXUP_OBJECTID -7ULL

/* क्रम space balancing */
#घोषणा BTRFS_TREE_RELOC_OBJECTID -8ULL
#घोषणा BTRFS_DATA_RELOC_TREE_OBJECTID -9ULL

/*
 * extent checksums all have this objectid
 * this allows them to share the logging tree
 * क्रम fsyncs
 */
#घोषणा BTRFS_EXTENT_CSUM_OBJECTID -10ULL

/* For storing मुक्त space cache */
#घोषणा BTRFS_FREE_SPACE_OBJECTID -11ULL

/*
 * The inode number asचिन्हित to the special inode क्रम storing
 * मुक्त ino cache
 */
#घोषणा BTRFS_FREE_INO_OBJECTID -12ULL

/* dummy objectid represents multiple objectids */
#घोषणा BTRFS_MULTIPLE_OBJECTIDS -255ULL

/*
 * All files have objectids in this range.
 */
#घोषणा BTRFS_FIRST_FREE_OBJECTID 256ULL
#घोषणा BTRFS_LAST_FREE_OBJECTID -256ULL
#घोषणा BTRFS_FIRST_CHUNK_TREE_OBJECTID 256ULL


/*
 * the device items go पूर्णांकo the chunk tree.  The key is in the क्रमm
 * [ 1 BTRFS_DEV_ITEM_KEY device_id ]
 */
#घोषणा BTRFS_DEV_ITEMS_OBJECTID 1ULL

#घोषणा BTRFS_BTREE_INODE_OBJECTID 1

#घोषणा BTRFS_EMPTY_SUBVOL_सूची_OBJECTID 2

#घोषणा BTRFS_DEV_REPLACE_DEVID 0ULL

/*
 * inode items have the data typically वापसed from stat and store other
 * info about object अक्षरacteristics.  There is one क्रम every file and dir in
 * the FS
 */
#घोषणा BTRFS_INODE_ITEM_KEY		1
#घोषणा BTRFS_INODE_REF_KEY		12
#घोषणा BTRFS_INODE_EXTREF_KEY		13
#घोषणा BTRFS_XATTR_ITEM_KEY		24
#घोषणा BTRFS_ORPHAN_ITEM_KEY		48
/* reserve 2-15 बंद to the inode क्रम later flexibility */

/*
 * dir items are the name -> inode poपूर्णांकers in a directory.  There is one
 * क्रम every name in a directory.
 */
#घोषणा BTRFS_सूची_LOG_ITEM_KEY  60
#घोषणा BTRFS_सूची_LOG_INDEX_KEY 72
#घोषणा BTRFS_सूची_ITEM_KEY	84
#घोषणा BTRFS_सूची_INDEX_KEY	96
/*
 * extent data is क्रम file data
 */
#घोषणा BTRFS_EXTENT_DATA_KEY	108

/*
 * extent csums are stored in a separate tree and hold csums क्रम
 * an entire extent on disk.
 */
#घोषणा BTRFS_EXTENT_CSUM_KEY	128

/*
 * root items poपूर्णांक to tree roots.  They are typically in the root
 * tree used by the super block to find all the other trees
 */
#घोषणा BTRFS_ROOT_ITEM_KEY	132

/*
 * root backrefs tie subvols and snapshots to the directory entries that
 * reference them
 */
#घोषणा BTRFS_ROOT_BACKREF_KEY	144

/*
 * root refs make a fast index क्रम listing all of the snapshots and
 * subvolumes referenced by a given root.  They poपूर्णांक directly to the
 * directory item in the root that references the subvol
 */
#घोषणा BTRFS_ROOT_REF_KEY	156

/*
 * extent items are in the extent map tree.  These record which blocks
 * are used, and how many references there are to each block
 */
#घोषणा BTRFS_EXTENT_ITEM_KEY	168

/*
 * The same as the BTRFS_EXTENT_ITEM_KEY, except it's metadata we alपढ़ोy know
 * the length, so we save the level in key->offset instead of the length.
 */
#घोषणा BTRFS_METADATA_ITEM_KEY	169

#घोषणा BTRFS_TREE_BLOCK_REF_KEY	176

#घोषणा BTRFS_EXTENT_DATA_REF_KEY	178

#घोषणा BTRFS_EXTENT_REF_V0_KEY		180

#घोषणा BTRFS_SHARED_BLOCK_REF_KEY	182

#घोषणा BTRFS_SHARED_DATA_REF_KEY	184

/*
 * block groups give us hपूर्णांकs पूर्णांकo the extent allocation trees.  Which
 * blocks are मुक्त etc etc
 */
#घोषणा BTRFS_BLOCK_GROUP_ITEM_KEY 192

/*
 * Every block group is represented in the मुक्त space tree by a मुक्त space info
 * item, which stores some accounting inक्रमmation. It is keyed on
 * (block_group_start, FREE_SPACE_INFO, block_group_length).
 */
#घोषणा BTRFS_FREE_SPACE_INFO_KEY 198

/*
 * A मुक्त space extent tracks an extent of space that is मुक्त in a block group.
 * It is keyed on (start, FREE_SPACE_EXTENT, length).
 */
#घोषणा BTRFS_FREE_SPACE_EXTENT_KEY 199

/*
 * When a block group becomes very fragmented, we convert it to use biपंचांगaps
 * instead of extents. A मुक्त space biपंचांगap is keyed on
 * (start, FREE_SPACE_BITMAP, length); the corresponding item is a biपंचांगap with
 * (length / sectorsize) bits.
 */
#घोषणा BTRFS_FREE_SPACE_BITMAP_KEY 200

#घोषणा BTRFS_DEV_EXTENT_KEY	204
#घोषणा BTRFS_DEV_ITEM_KEY	216
#घोषणा BTRFS_CHUNK_ITEM_KEY	228

/*
 * Records the overall state of the qgroups.
 * There's only one instance of this key present,
 * (0, BTRFS_QGROUP_STATUS_KEY, 0)
 */
#घोषणा BTRFS_QGROUP_STATUS_KEY         240
/*
 * Records the currently used space of the qgroup.
 * One key per qgroup, (0, BTRFS_QGROUP_INFO_KEY, qgroupid).
 */
#घोषणा BTRFS_QGROUP_INFO_KEY           242
/*
 * Contains the user configured limits क्रम the qgroup.
 * One key per qgroup, (0, BTRFS_QGROUP_LIMIT_KEY, qgroupid).
 */
#घोषणा BTRFS_QGROUP_LIMIT_KEY          244
/*
 * Records the child-parent relationship of qgroups. For
 * each relation, 2 keys are present:
 * (childid, BTRFS_QGROUP_RELATION_KEY, parentid)
 * (parentid, BTRFS_QGROUP_RELATION_KEY, childid)
 */
#घोषणा BTRFS_QGROUP_RELATION_KEY       246

/*
 * Obsolete name, see BTRFS_TEMPORARY_ITEM_KEY.
 */
#घोषणा BTRFS_BALANCE_ITEM_KEY	248

/*
 * The key type क्रम tree items that are stored persistently, but करो not need to
 * exist क्रम extended period of समय. The items can exist in any tree.
 *
 * [subtype, BTRFS_TEMPORARY_ITEM_KEY, data]
 *
 * Existing items:
 *
 * - balance status item
 *   (BTRFS_BALANCE_OBJECTID, BTRFS_TEMPORARY_ITEM_KEY, 0)
 */
#घोषणा BTRFS_TEMPORARY_ITEM_KEY	248

/*
 * Obsolete name, see BTRFS_PERSISTENT_ITEM_KEY
 */
#घोषणा BTRFS_DEV_STATS_KEY		249

/*
 * The key type क्रम tree items that are stored persistently and usually exist
 * क्रम a दीर्घ period, eg. fileप्रणाली lअगरeसमय. The item kinds can be status
 * inक्रमmation, stats or preference values. The item can exist in any tree.
 *
 * [subtype, BTRFS_PERSISTENT_ITEM_KEY, data]
 *
 * Existing items:
 *
 * - device statistics, store IO stats in the device tree, one key क्रम all
 *   stats
 *   (BTRFS_DEV_STATS_OBJECTID, BTRFS_DEV_STATS_KEY, 0)
 */
#घोषणा BTRFS_PERSISTENT_ITEM_KEY	249

/*
 * Persistantly stores the device replace state in the device tree.
 * The key is built like this: (0, BTRFS_DEV_REPLACE_KEY, 0).
 */
#घोषणा BTRFS_DEV_REPLACE_KEY	250

/*
 * Stores items that allow to quickly map UUIDs to something अन्यथा.
 * These items are part of the fileप्रणाली UUID tree.
 * The key is built like this:
 * (UUID_upper_64_bits, BTRFS_UUID_KEY*, UUID_lower_64_bits).
 */
#अगर BTRFS_UUID_SIZE != 16
#त्रुटि "UUID items require BTRFS_UUID_SIZE == 16!"
#पूर्ण_अगर
#घोषणा BTRFS_UUID_KEY_SUBVOL	251	/* क्रम UUIDs asचिन्हित to subvols */
#घोषणा BTRFS_UUID_KEY_RECEIVED_SUBVOL	252	/* क्रम UUIDs asचिन्हित to
						 * received subvols */

/*
 * string items are क्रम debugging.  They just store a लघु string of
 * data in the FS
 */
#घोषणा BTRFS_STRING_ITEM_KEY	253

/* Maximum metadata block size (nodesize) */
#घोषणा BTRFS_MAX_METADATA_BLOCKSIZE			65536

/* 32 bytes in various csum fields */
#घोषणा BTRFS_CSUM_SIZE 32

/* csum types */
क्रमागत btrfs_csum_type अणु
	BTRFS_CSUM_TYPE_CRC32	= 0,
	BTRFS_CSUM_TYPE_XXHASH	= 1,
	BTRFS_CSUM_TYPE_SHA256	= 2,
	BTRFS_CSUM_TYPE_BLAKE2	= 3,
पूर्ण;

/*
 * flags definitions क्रम directory entry item type
 *
 * Used by:
 * काष्ठा btrfs_dir_item.type
 *
 * Values 0..7 must match common file type values in fs_types.h.
 */
#घोषणा BTRFS_FT_UNKNOWN	0
#घोषणा BTRFS_FT_REG_खाता	1
#घोषणा BTRFS_FT_सूची		2
#घोषणा BTRFS_FT_CHRDEV		3
#घोषणा BTRFS_FT_BLKDEV		4
#घोषणा BTRFS_FT_FIFO		5
#घोषणा BTRFS_FT_SOCK		6
#घोषणा BTRFS_FT_SYMLINK	7
#घोषणा BTRFS_FT_XATTR		8
#घोषणा BTRFS_FT_MAX		9

/*
 * The key defines the order in the tree, and so it also defines (optimal)
 * block layout.
 *
 * objectid corresponds to the inode number.
 *
 * type tells us things about the object, and is a kind of stream selector.
 * so क्रम a given inode, keys with type of 1 might refer to the inode data,
 * type of 2 may poपूर्णांक to file data in the btree and type == 3 may poपूर्णांक to
 * extents.
 *
 * offset is the starting byte offset क्रम this key in the stream.
 *
 * btrfs_disk_key is in disk byte order.  काष्ठा btrfs_key is always
 * in cpu native order.  Otherwise they are identical and their sizes
 * should be the same (ie both packed)
 */
काष्ठा btrfs_disk_key अणु
	__le64 objectid;
	__u8 type;
	__le64 offset;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_key अणु
	__u64 objectid;
	__u8 type;
	__u64 offset;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_dev_item अणु
	/* the पूर्णांकernal btrfs device id */
	__le64 devid;

	/* size of the device */
	__le64 total_bytes;

	/* bytes used */
	__le64 bytes_used;

	/* optimal io alignment क्रम this device */
	__le32 io_align;

	/* optimal io width क्रम this device */
	__le32 io_width;

	/* minimal io size क्रम this device */
	__le32 sector_size;

	/* type and info about this device */
	__le64 type;

	/* expected generation क्रम this device */
	__le64 generation;

	/*
	 * starting byte of this partition on the device,
	 * to allow क्रम stripe alignment in the future
	 */
	__le64 start_offset;

	/* grouping inक्रमmation क्रम allocation decisions */
	__le32 dev_group;

	/* seek speed 0-100 where 100 is fastest */
	__u8 seek_speed;

	/* bandwidth 0-100 where 100 is fastest */
	__u8 bandwidth;

	/* btrfs generated uuid क्रम this device */
	__u8 uuid[BTRFS_UUID_SIZE];

	/* uuid of FS who owns this device */
	__u8 fsid[BTRFS_UUID_SIZE];
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_stripe अणु
	__le64 devid;
	__le64 offset;
	__u8 dev_uuid[BTRFS_UUID_SIZE];
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_chunk अणु
	/* size of this chunk in bytes */
	__le64 length;

	/* objectid of the root referencing this chunk */
	__le64 owner;

	__le64 stripe_len;
	__le64 type;

	/* optimal io alignment क्रम this chunk */
	__le32 io_align;

	/* optimal io width क्रम this chunk */
	__le32 io_width;

	/* minimal io size क्रम this chunk */
	__le32 sector_size;

	/* 2^16 stripes is quite a lot, a second limit is the size of a single
	 * item in the btree
	 */
	__le16 num_stripes;

	/* sub stripes only matter क्रम raid10 */
	__le16 sub_stripes;
	काष्ठा btrfs_stripe stripe;
	/* additional stripes go here */
पूर्ण __attribute__ ((__packed__));

#घोषणा BTRFS_FREE_SPACE_EXTENT	1
#घोषणा BTRFS_FREE_SPACE_BITMAP	2

काष्ठा btrfs_मुक्त_space_entry अणु
	__le64 offset;
	__le64 bytes;
	__u8 type;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_मुक्त_space_header अणु
	काष्ठा btrfs_disk_key location;
	__le64 generation;
	__le64 num_entries;
	__le64 num_biपंचांगaps;
पूर्ण __attribute__ ((__packed__));

#घोषणा BTRFS_HEADER_FLAG_WRITTEN	(1ULL << 0)
#घोषणा BTRFS_HEADER_FLAG_RELOC		(1ULL << 1)

/* Super block flags */
/* Errors detected */
#घोषणा BTRFS_SUPER_FLAG_ERROR		(1ULL << 2)

#घोषणा BTRFS_SUPER_FLAG_SEEDING	(1ULL << 32)
#घोषणा BTRFS_SUPER_FLAG_METADUMP	(1ULL << 33)
#घोषणा BTRFS_SUPER_FLAG_METADUMP_V2	(1ULL << 34)
#घोषणा BTRFS_SUPER_FLAG_CHANGING_FSID	(1ULL << 35)
#घोषणा BTRFS_SUPER_FLAG_CHANGING_FSID_V2 (1ULL << 36)


/*
 * items in the extent btree are used to record the objectid of the
 * owner of the block and the number of references
 */

काष्ठा btrfs_extent_item अणु
	__le64 refs;
	__le64 generation;
	__le64 flags;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_extent_item_v0 अणु
	__le32 refs;
पूर्ण __attribute__ ((__packed__));


#घोषणा BTRFS_EXTENT_FLAG_DATA		(1ULL << 0)
#घोषणा BTRFS_EXTENT_FLAG_TREE_BLOCK	(1ULL << 1)

/* following flags only apply to tree blocks */

/* use full backrefs क्रम extent poपूर्णांकers in the block */
#घोषणा BTRFS_BLOCK_FLAG_FULL_BACKREF	(1ULL << 8)

/*
 * this flag is only used पूर्णांकernally by scrub and may be changed at any समय
 * it is only declared here to aव्योम collisions
 */
#घोषणा BTRFS_EXTENT_FLAG_SUPER		(1ULL << 48)

काष्ठा btrfs_tree_block_info अणु
	काष्ठा btrfs_disk_key key;
	__u8 level;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_extent_data_ref अणु
	__le64 root;
	__le64 objectid;
	__le64 offset;
	__le32 count;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_shared_data_ref अणु
	__le32 count;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_extent_अंतरभूत_ref अणु
	__u8 type;
	__le64 offset;
पूर्ण __attribute__ ((__packed__));

/* dev extents record मुक्त space on inभागidual devices.  The owner
 * field poपूर्णांकs back to the chunk allocation mapping tree that allocated
 * the extent.  The chunk tree uuid field is a way to द्विगुन check the owner
 */
काष्ठा btrfs_dev_extent अणु
	__le64 chunk_tree;
	__le64 chunk_objectid;
	__le64 chunk_offset;
	__le64 length;
	__u8 chunk_tree_uuid[BTRFS_UUID_SIZE];
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_inode_ref अणु
	__le64 index;
	__le16 name_len;
	/* name goes here */
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_inode_extref अणु
	__le64 parent_objectid;
	__le64 index;
	__le16 name_len;
	__u8   name[0];
	/* name goes here */
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_बारpec अणु
	__le64 sec;
	__le32 nsec;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_inode_item अणु
	/* nfs style generation number */
	__le64 generation;
	/* transid that last touched this inode */
	__le64 transid;
	__le64 size;
	__le64 nbytes;
	__le64 block_group;
	__le32 nlink;
	__le32 uid;
	__le32 gid;
	__le32 mode;
	__le64 rdev;
	__le64 flags;

	/* modअगरication sequence number क्रम NFS */
	__le64 sequence;

	/*
	 * a little future expansion, क्रम more than this we can
	 * just grow the inode item and version it
	 */
	__le64 reserved[4];
	काष्ठा btrfs_बारpec aसमय;
	काष्ठा btrfs_बारpec स_समय;
	काष्ठा btrfs_बारpec mसमय;
	काष्ठा btrfs_बारpec oसमय;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_dir_log_item अणु
	__le64 end;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_dir_item अणु
	काष्ठा btrfs_disk_key location;
	__le64 transid;
	__le16 data_len;
	__le16 name_len;
	__u8 type;
पूर्ण __attribute__ ((__packed__));

#घोषणा BTRFS_ROOT_SUBVOL_RDONLY	(1ULL << 0)

/*
 * Internal in-memory flag that a subvolume has been marked क्रम deletion but
 * still visible as a directory
 */
#घोषणा BTRFS_ROOT_SUBVOL_DEAD		(1ULL << 48)

काष्ठा btrfs_root_item अणु
	काष्ठा btrfs_inode_item inode;
	__le64 generation;
	__le64 root_dirid;
	__le64 bytenr;
	__le64 byte_limit;
	__le64 bytes_used;
	__le64 last_snapshot;
	__le64 flags;
	__le32 refs;
	काष्ठा btrfs_disk_key drop_progress;
	__u8 drop_level;
	__u8 level;

	/*
	 * The following fields appear after subvol_uuids+subvol_बार
	 * were पूर्णांकroduced.
	 */

	/*
	 * This generation number is used to test अगर the new fields are valid
	 * and up to date जबतक पढ़ोing the root item. Every समय the root item
	 * is written out, the "generation" field is copied पूर्णांकo this field. If
	 * anyone ever mounted the fs with an older kernel, we will have
	 * mismatching generation values here and thus must invalidate the
	 * new fields. See btrfs_update_root and btrfs_find_last_root क्रम
	 * details.
	 * the offset of generation_v2 is also used as the start क्रम the स_रखो
	 * when invalidating the fields.
	 */
	__le64 generation_v2;
	__u8 uuid[BTRFS_UUID_SIZE];
	__u8 parent_uuid[BTRFS_UUID_SIZE];
	__u8 received_uuid[BTRFS_UUID_SIZE];
	__le64 ctransid; /* updated when an inode changes */
	__le64 otransid; /* trans when created */
	__le64 stransid; /* trans when sent. non-zero क्रम received subvol */
	__le64 rtransid; /* trans when received. non-zero क्रम received subvol */
	काष्ठा btrfs_बारpec स_समय;
	काष्ठा btrfs_बारpec oसमय;
	काष्ठा btrfs_बारpec sसमय;
	काष्ठा btrfs_बारpec rसमय;
	__le64 reserved[8]; /* क्रम future */
पूर्ण __attribute__ ((__packed__));

/*
 * Btrfs root item used to be smaller than current size.  The old क्रमmat ends
 * at where member generation_v2 is.
 */
अटल अंतरभूत __u32 btrfs_legacy_root_item_size(व्योम)
अणु
	वापस दुरत्व(काष्ठा btrfs_root_item, generation_v2);
पूर्ण

/*
 * this is used क्रम both क्रमward and backward root refs
 */
काष्ठा btrfs_root_ref अणु
	__le64 dirid;
	__le64 sequence;
	__le16 name_len;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_disk_balance_args अणु
	/*
	 * profiles to operate on, single is denoted by
	 * BTRFS_AVAIL_ALLOC_BIT_SINGLE
	 */
	__le64 profiles;

	/*
	 * usage filter
	 * BTRFS_BALANCE_ARGS_USAGE with a single value means '0..N'
	 * BTRFS_BALANCE_ARGS_USAGE_RANGE - range syntax, min..max
	 */
	जोड़ अणु
		__le64 usage;
		काष्ठा अणु
			__le32 usage_min;
			__le32 usage_max;
		पूर्ण;
	पूर्ण;

	/* devid filter */
	__le64 devid;

	/* devid subset filter [pstart..pend) */
	__le64 pstart;
	__le64 pend;

	/* btrfs भव address space subset filter [vstart..vend) */
	__le64 vstart;
	__le64 vend;

	/*
	 * profile to convert to, single is denoted by
	 * BTRFS_AVAIL_ALLOC_BIT_SINGLE
	 */
	__le64 target;

	/* BTRFS_BALANCE_ARGS_* */
	__le64 flags;

	/*
	 * BTRFS_BALANCE_ARGS_LIMIT with value 'limit'
	 * BTRFS_BALANCE_ARGS_LIMIT_RANGE - the extend version can use minimum
	 * and maximum
	 */
	जोड़ अणु
		__le64 limit;
		काष्ठा अणु
			__le32 limit_min;
			__le32 limit_max;
		पूर्ण;
	पूर्ण;

	/*
	 * Process chunks that cross stripes_min..stripes_max devices,
	 * BTRFS_BALANCE_ARGS_STRIPES_RANGE
	 */
	__le32 stripes_min;
	__le32 stripes_max;

	__le64 unused[6];
पूर्ण __attribute__ ((__packed__));

/*
 * store balance parameters to disk so that balance can be properly
 * resumed after crash or unmount
 */
काष्ठा btrfs_balance_item अणु
	/* BTRFS_BALANCE_* */
	__le64 flags;

	काष्ठा btrfs_disk_balance_args data;
	काष्ठा btrfs_disk_balance_args meta;
	काष्ठा btrfs_disk_balance_args sys;

	__le64 unused[4];
पूर्ण __attribute__ ((__packed__));

क्रमागत अणु
	BTRFS_खाता_EXTENT_INLINE   = 0,
	BTRFS_खाता_EXTENT_REG      = 1,
	BTRFS_खाता_EXTENT_PREALLOC = 2,
	BTRFS_NR_खाता_EXTENT_TYPES = 3,
पूर्ण;

काष्ठा btrfs_file_extent_item अणु
	/*
	 * transaction id that created this extent
	 */
	__le64 generation;
	/*
	 * max number of bytes to hold this extent in ram
	 * when we split a compressed extent we can't know how big
	 * each of the resulting pieces will be.  So, this is
	 * an upper limit on the size of the extent in ram instead of
	 * an exact limit.
	 */
	__le64 ram_bytes;

	/*
	 * 32 bits क्रम the various ways we might encode the data,
	 * including compression and encryption.  If any of these
	 * are set to something a given disk क्रमmat करोesn't understand
	 * it is treated like an incompat flag क्रम पढ़ोing and writing,
	 * but not क्रम stat.
	 */
	__u8 compression;
	__u8 encryption;
	__le16 other_encoding; /* spare क्रम later use */

	/* are we अंतरभूत data or a real extent? */
	__u8 type;

	/*
	 * disk space consumed by the extent, checksum blocks are included
	 * in these numbers
	 *
	 * At this offset in the काष्ठाure, the अंतरभूत extent data start.
	 */
	__le64 disk_bytenr;
	__le64 disk_num_bytes;
	/*
	 * the logical offset in file blocks (no csums)
	 * this extent record is क्रम.  This allows a file extent to poपूर्णांक
	 * पूर्णांकo the middle of an existing extent on disk, sharing it
	 * between two snapshots (useful अगर some bytes in the middle of the
	 * extent have changed
	 */
	__le64 offset;
	/*
	 * the logical number of file blocks (no csums included).  This
	 * always reflects the size uncompressed and without encoding.
	 */
	__le64 num_bytes;

पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_csum_item अणु
	__u8 csum;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_dev_stats_item अणु
	/*
	 * grow this item काष्ठा at the end क्रम future enhancements and keep
	 * the existing values unchanged
	 */
	__le64 values[BTRFS_DEV_STAT_VALUES_MAX];
पूर्ण __attribute__ ((__packed__));

#घोषणा BTRFS_DEV_REPLACE_ITEM_CONT_READING_FROM_SRCDEV_MODE_ALWAYS	0
#घोषणा BTRFS_DEV_REPLACE_ITEM_CONT_READING_FROM_SRCDEV_MODE_AVOID	1

काष्ठा btrfs_dev_replace_item अणु
	/*
	 * grow this item काष्ठा at the end क्रम future enhancements and keep
	 * the existing values unchanged
	 */
	__le64 src_devid;
	__le64 cursor_left;
	__le64 cursor_right;
	__le64 cont_पढ़ोing_from_srcdev_mode;

	__le64 replace_state;
	__le64 समय_started;
	__le64 समय_stopped;
	__le64 num_ग_लिखो_errors;
	__le64 num_uncorrectable_पढ़ो_errors;
पूर्ण __attribute__ ((__packed__));

/* dअगरferent types of block groups (and chunks) */
#घोषणा BTRFS_BLOCK_GROUP_DATA		(1ULL << 0)
#घोषणा BTRFS_BLOCK_GROUP_SYSTEM	(1ULL << 1)
#घोषणा BTRFS_BLOCK_GROUP_METADATA	(1ULL << 2)
#घोषणा BTRFS_BLOCK_GROUP_RAID0		(1ULL << 3)
#घोषणा BTRFS_BLOCK_GROUP_RAID1		(1ULL << 4)
#घोषणा BTRFS_BLOCK_GROUP_DUP		(1ULL << 5)
#घोषणा BTRFS_BLOCK_GROUP_RAID10	(1ULL << 6)
#घोषणा BTRFS_BLOCK_GROUP_RAID5         (1ULL << 7)
#घोषणा BTRFS_BLOCK_GROUP_RAID6         (1ULL << 8)
#घोषणा BTRFS_BLOCK_GROUP_RAID1C3       (1ULL << 9)
#घोषणा BTRFS_BLOCK_GROUP_RAID1C4       (1ULL << 10)
#घोषणा BTRFS_BLOCK_GROUP_RESERVED	(BTRFS_AVAIL_ALLOC_BIT_SINGLE | \
					 BTRFS_SPACE_INFO_GLOBAL_RSV)

क्रमागत btrfs_raid_types अणु
	BTRFS_RAID_RAID10,
	BTRFS_RAID_RAID1,
	BTRFS_RAID_DUP,
	BTRFS_RAID_RAID0,
	BTRFS_RAID_SINGLE,
	BTRFS_RAID_RAID5,
	BTRFS_RAID_RAID6,
	BTRFS_RAID_RAID1C3,
	BTRFS_RAID_RAID1C4,
	BTRFS_NR_RAID_TYPES
पूर्ण;

#घोषणा BTRFS_BLOCK_GROUP_TYPE_MASK	(BTRFS_BLOCK_GROUP_DATA |    \
					 BTRFS_BLOCK_GROUP_SYSTEM |  \
					 BTRFS_BLOCK_GROUP_METADATA)

#घोषणा BTRFS_BLOCK_GROUP_PROखाता_MASK	(BTRFS_BLOCK_GROUP_RAID0 |   \
					 BTRFS_BLOCK_GROUP_RAID1 |   \
					 BTRFS_BLOCK_GROUP_RAID1C3 | \
					 BTRFS_BLOCK_GROUP_RAID1C4 | \
					 BTRFS_BLOCK_GROUP_RAID5 |   \
					 BTRFS_BLOCK_GROUP_RAID6 |   \
					 BTRFS_BLOCK_GROUP_DUP |     \
					 BTRFS_BLOCK_GROUP_RAID10)
#घोषणा BTRFS_BLOCK_GROUP_RAID56_MASK	(BTRFS_BLOCK_GROUP_RAID5 |   \
					 BTRFS_BLOCK_GROUP_RAID6)

#घोषणा BTRFS_BLOCK_GROUP_RAID1_MASK	(BTRFS_BLOCK_GROUP_RAID1 |   \
					 BTRFS_BLOCK_GROUP_RAID1C3 | \
					 BTRFS_BLOCK_GROUP_RAID1C4)

/*
 * We need a bit क्रम restriper to be able to tell when chunks of type
 * SINGLE are available.  This "extended" profile क्रमmat is used in
 * fs_info->avail_*_alloc_bits (in-memory) and balance item fields
 * (on-disk).  The corresponding on-disk bit in chunk.type is reserved
 * to aव्योम remappings between two क्रमmats in future.
 */
#घोषणा BTRFS_AVAIL_ALLOC_BIT_SINGLE	(1ULL << 48)

/*
 * A fake block group type that is used to communicate global block reserve
 * size to userspace via the SPACE_INFO ioctl.
 */
#घोषणा BTRFS_SPACE_INFO_GLOBAL_RSV	(1ULL << 49)

#घोषणा BTRFS_EXTENDED_PROखाता_MASK	(BTRFS_BLOCK_GROUP_PROखाता_MASK | \
					 BTRFS_AVAIL_ALLOC_BIT_SINGLE)

अटल अंतरभूत __u64 chunk_to_extended(__u64 flags)
अणु
	अगर ((flags & BTRFS_BLOCK_GROUP_PROखाता_MASK) == 0)
		flags |= BTRFS_AVAIL_ALLOC_BIT_SINGLE;

	वापस flags;
पूर्ण
अटल अंतरभूत __u64 extended_to_chunk(__u64 flags)
अणु
	वापस flags & ~BTRFS_AVAIL_ALLOC_BIT_SINGLE;
पूर्ण

काष्ठा btrfs_block_group_item अणु
	__le64 used;
	__le64 chunk_objectid;
	__le64 flags;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_मुक्त_space_info अणु
	__le32 extent_count;
	__le32 flags;
पूर्ण __attribute__ ((__packed__));

#घोषणा BTRFS_FREE_SPACE_USING_BITMAPS (1ULL << 0)

#घोषणा BTRFS_QGROUP_LEVEL_SHIFT		48
अटल अंतरभूत __u16 btrfs_qgroup_level(__u64 qgroupid)
अणु
	वापस (__u16)(qgroupid >> BTRFS_QGROUP_LEVEL_SHIFT);
पूर्ण

/*
 * is subvolume quota turned on?
 */
#घोषणा BTRFS_QGROUP_STATUS_FLAG_ON		(1ULL << 0)
/*
 * RESCAN is set during the initialization phase
 */
#घोषणा BTRFS_QGROUP_STATUS_FLAG_RESCAN		(1ULL << 1)
/*
 * Some qgroup entries are known to be out of date,
 * either because the configuration has changed in a way that
 * makes a rescan necessary, or because the fs has been mounted
 * with a non-qgroup-aware version.
 * Turning qouta off and on again makes it inconsistent, too.
 */
#घोषणा BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT	(1ULL << 2)

#घोषणा BTRFS_QGROUP_STATUS_VERSION        1

काष्ठा btrfs_qgroup_status_item अणु
	__le64 version;
	/*
	 * the generation is updated during every commit. As older
	 * versions of btrfs are not aware of qgroups, it will be
	 * possible to detect inconsistencies by checking the
	 * generation on mount समय
	 */
	__le64 generation;

	/* flag definitions see above */
	__le64 flags;

	/*
	 * only used during scanning to record the progress
	 * of the scan. It contains a logical address
	 */
	__le64 rescan;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_qgroup_info_item अणु
	__le64 generation;
	__le64 rfer;
	__le64 rfer_cmpr;
	__le64 excl;
	__le64 excl_cmpr;
पूर्ण __attribute__ ((__packed__));

काष्ठा btrfs_qgroup_limit_item अणु
	/*
	 * only updated when any of the other values change
	 */
	__le64 flags;
	__le64 max_rfer;
	__le64 max_excl;
	__le64 rsv_rfer;
	__le64 rsv_excl;
पूर्ण __attribute__ ((__packed__));

#पूर्ण_अगर /* _BTRFS_CTREE_H_ */
