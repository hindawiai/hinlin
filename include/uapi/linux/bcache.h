<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_BCACHE_H
#घोषणा _LINUX_BCACHE_H

/*
 * Bcache on disk data काष्ठाures
 */

#समावेश <linux/types.h>

#घोषणा BITMASK(name, type, field, offset, size)		\
अटल अंतरभूत __u64 name(स्थिर type *k)				\
अणु वापस (k->field >> offset) & ~(~0ULL << size); पूर्ण		\
								\
अटल अंतरभूत व्योम SET_##name(type *k, __u64 v)			\
अणु								\
	k->field &= ~(~(~0ULL << size) << offset);		\
	k->field |= (v & ~(~0ULL << size)) << offset;		\
पूर्ण

/* Btree keys - all units are in sectors */

काष्ठा bkey अणु
	__u64	high;
	__u64	low;
	__u64	ptr[];
पूर्ण;

#घोषणा KEY_FIELD(name, field, offset, size)				\
	BITMASK(name, काष्ठा bkey, field, offset, size)

#घोषणा PTR_FIELD(name, offset, size)					\
अटल अंतरभूत __u64 name(स्थिर काष्ठा bkey *k, अचिन्हित पूर्णांक i)		\
अणु वापस (k->ptr[i] >> offset) & ~(~0ULL << size); पूर्ण			\
									\
अटल अंतरभूत व्योम SET_##name(काष्ठा bkey *k, अचिन्हित पूर्णांक i, __u64 v)	\
अणु									\
	k->ptr[i] &= ~(~(~0ULL << size) << offset);			\
	k->ptr[i] |= (v & ~(~0ULL << size)) << offset;			\
पूर्ण

#घोषणा KEY_SIZE_BITS		16
#घोषणा KEY_MAX_U64S		8

KEY_FIELD(KEY_PTRS,	high, 60, 3)
KEY_FIELD(HEADER_SIZE,	high, 58, 2)
KEY_FIELD(KEY_CSUM,	high, 56, 2)
KEY_FIELD(KEY_PINNED,	high, 55, 1)
KEY_FIELD(KEY_सूचीTY,	high, 36, 1)

KEY_FIELD(KEY_SIZE,	high, 20, KEY_SIZE_BITS)
KEY_FIELD(KEY_INODE,	high, 0,  20)

/* Next समय I change the on disk क्रमmat, KEY_OFFSET() won't be 64 bits */

अटल अंतरभूत __u64 KEY_OFFSET(स्थिर काष्ठा bkey *k)
अणु
	वापस k->low;
पूर्ण

अटल अंतरभूत व्योम SET_KEY_OFFSET(काष्ठा bkey *k, __u64 v)
अणु
	k->low = v;
पूर्ण

/*
 * The high bit being set is a relic from when we used it to करो binary
 * searches - it told you where a key started. It's not used anymore,
 * and can probably be safely dropped.
 */
#घोषणा KEY(inode, offset, size)					\
((काष्ठा bkey) अणु							\
	.high = (1ULL << 63) | ((__u64) (size) << 20) | (inode),	\
	.low = (offset)							\
पूर्ण)

#घोषणा ZERO_KEY			KEY(0, 0, 0)

#घोषणा MAX_KEY_INODE			(~(~0 << 20))
#घोषणा MAX_KEY_OFFSET			(~0ULL >> 1)
#घोषणा MAX_KEY				KEY(MAX_KEY_INODE, MAX_KEY_OFFSET, 0)

#घोषणा KEY_START(k)			(KEY_OFFSET(k) - KEY_SIZE(k))
#घोषणा START_KEY(k)			KEY(KEY_INODE(k), KEY_START(k), 0)

#घोषणा PTR_DEV_BITS			12

PTR_FIELD(PTR_DEV,			51, PTR_DEV_BITS)
PTR_FIELD(PTR_OFFSET,			8,  43)
PTR_FIELD(PTR_GEN,			0,  8)

#घोषणा PTR_CHECK_DEV			((1 << PTR_DEV_BITS) - 1)

#घोषणा MAKE_PTR(gen, offset, dev)					\
	((((__u64) dev) << 51) | ((__u64) offset) << 8 | gen)

/* Bkey utility code */

अटल अंतरभूत अचिन्हित दीर्घ bkey_u64s(स्थिर काष्ठा bkey *k)
अणु
	वापस (माप(काष्ठा bkey) / माप(__u64)) + KEY_PTRS(k);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ bkey_bytes(स्थिर काष्ठा bkey *k)
अणु
	वापस bkey_u64s(k) * माप(__u64);
पूर्ण

#घोषणा bkey_copy(_dest, _src)	स_नकल(_dest, _src, bkey_bytes(_src))

अटल अंतरभूत व्योम bkey_copy_key(काष्ठा bkey *dest, स्थिर काष्ठा bkey *src)
अणु
	SET_KEY_INODE(dest, KEY_INODE(src));
	SET_KEY_OFFSET(dest, KEY_OFFSET(src));
पूर्ण

अटल अंतरभूत काष्ठा bkey *bkey_next(स्थिर काष्ठा bkey *k)
अणु
	__u64 *d = (व्योम *) k;

	वापस (काष्ठा bkey *) (d + bkey_u64s(k));
पूर्ण

अटल अंतरभूत काष्ठा bkey *bkey_idx(स्थिर काष्ठा bkey *k, अचिन्हित पूर्णांक nr_keys)
अणु
	__u64 *d = (व्योम *) k;

	वापस (काष्ठा bkey *) (d + nr_keys);
पूर्ण
/* Enough क्रम a key with 6 poपूर्णांकers */
#घोषणा BKEY_PAD		8

#घोषणा BKEY_PADDED(key)					\
	जोड़ अणु काष्ठा bkey key; __u64 key ## _pad[BKEY_PAD]; पूर्ण

/* Superblock */

/* Version 0: Cache device
 * Version 1: Backing device
 * Version 2: Seed poपूर्णांकer पूर्णांकo btree node checksum
 * Version 3: Cache device with new UUID क्रमmat
 * Version 4: Backing device with data offset
 */
#घोषणा BCACHE_SB_VERSION_CDEV			0
#घोषणा BCACHE_SB_VERSION_BDEV			1
#घोषणा BCACHE_SB_VERSION_CDEV_WITH_UUID	3
#घोषणा BCACHE_SB_VERSION_BDEV_WITH_OFFSET	4
#घोषणा BCACHE_SB_VERSION_CDEV_WITH_FEATURES	5
#घोषणा BCACHE_SB_VERSION_BDEV_WITH_FEATURES	6
#घोषणा BCACHE_SB_MAX_VERSION			6

#घोषणा SB_SECTOR			8
#घोषणा SB_OFFSET			(SB_SECTOR << SECTOR_SHIFT)
#घोषणा SB_SIZE				4096
#घोषणा SB_LABEL_SIZE			32
#घोषणा SB_JOURNAL_BUCKETS		256U
/* SB_JOURNAL_BUCKETS must be भागisible by BITS_PER_LONG */
#घोषणा MAX_CACHES_PER_SET		8

#घोषणा BDEV_DATA_START_DEFAULT		16	/* sectors */

काष्ठा cache_sb_disk अणु
	__le64			csum;
	__le64			offset;	/* sector where this sb was written */
	__le64			version;

	__u8			magic[16];

	__u8			uuid[16];
	जोड़ अणु
		__u8		set_uuid[16];
		__le64		set_magic;
	पूर्ण;
	__u8			label[SB_LABEL_SIZE];

	__le64			flags;
	__le64			seq;

	__le64			feature_compat;
	__le64			feature_incompat;
	__le64			feature_ro_compat;

	__le64			pad[5];

	जोड़ अणु
	काष्ठा अणु
		/* Cache devices */
		__le64		nbuckets;	/* device size */

		__le16		block_size;	/* sectors */
		__le16		bucket_size;	/* sectors */

		__le16		nr_in_set;
		__le16		nr_this_dev;
	पूर्ण;
	काष्ठा अणु
		/* Backing devices */
		__le64		data_offset;

		/*
		 * block_size from the cache device section is still used by
		 * backing devices, so करोn't add anything here until we fix
		 * things to not need it क्रम backing devices anymore
		 */
	पूर्ण;
	पूर्ण;

	__le32			last_mount;	/* समय overflow in y2106 */

	__le16			first_bucket;
	जोड़ अणु
		__le16		njournal_buckets;
		__le16		keys;
	पूर्ण;
	__le64			d[SB_JOURNAL_BUCKETS];	/* journal buckets */
	__le16			obso_bucket_size_hi;	/* obsoleted */
पूर्ण;

/*
 * This is क्रम in-memory bcache super block.
 * NOTE: cache_sb is NOT exactly mapping to cache_sb_disk, the member
 *       size, ordering and even whole काष्ठा size may be dअगरferent
 *       from cache_sb_disk.
 */
काष्ठा cache_sb अणु
	__u64			offset;	/* sector where this sb was written */
	__u64			version;

	__u8			magic[16];

	__u8			uuid[16];
	जोड़ अणु
		__u8		set_uuid[16];
		__u64		set_magic;
	पूर्ण;
	__u8			label[SB_LABEL_SIZE];

	__u64			flags;
	__u64			seq;

	__u64			feature_compat;
	__u64			feature_incompat;
	__u64			feature_ro_compat;

	जोड़ अणु
	काष्ठा अणु
		/* Cache devices */
		__u64		nbuckets;	/* device size */

		__u16		block_size;	/* sectors */
		__u16		nr_in_set;
		__u16		nr_this_dev;
		__u32		bucket_size;	/* sectors */
	पूर्ण;
	काष्ठा अणु
		/* Backing devices */
		__u64		data_offset;

		/*
		 * block_size from the cache device section is still used by
		 * backing devices, so करोn't add anything here until we fix
		 * things to not need it क्रम backing devices anymore
		 */
	पूर्ण;
	पूर्ण;

	__u32			last_mount;	/* समय overflow in y2106 */

	__u16			first_bucket;
	जोड़ अणु
		__u16		njournal_buckets;
		__u16		keys;
	पूर्ण;
	__u64			d[SB_JOURNAL_BUCKETS];	/* journal buckets */
पूर्ण;

अटल अंतरभूत _Bool SB_IS_BDEV(स्थिर काष्ठा cache_sb *sb)
अणु
	वापस sb->version == BCACHE_SB_VERSION_BDEV
		|| sb->version == BCACHE_SB_VERSION_BDEV_WITH_OFFSET
		|| sb->version == BCACHE_SB_VERSION_BDEV_WITH_FEATURES;
पूर्ण

BITMASK(CACHE_SYNC,			काष्ठा cache_sb, flags, 0, 1);
BITMASK(CACHE_DISCARD,			काष्ठा cache_sb, flags, 1, 1);
BITMASK(CACHE_REPLACEMENT,		काष्ठा cache_sb, flags, 2, 3);
#घोषणा CACHE_REPLACEMENT_LRU		0U
#घोषणा CACHE_REPLACEMENT_FIFO		1U
#घोषणा CACHE_REPLACEMENT_RANDOM	2U

BITMASK(BDEV_CACHE_MODE,		काष्ठा cache_sb, flags, 0, 4);
#घोषणा CACHE_MODE_WRITETHROUGH		0U
#घोषणा CACHE_MODE_WRITEBACK		1U
#घोषणा CACHE_MODE_WRITEAROUND		2U
#घोषणा CACHE_MODE_NONE			3U
BITMASK(BDEV_STATE,			काष्ठा cache_sb, flags, 61, 2);
#घोषणा BDEV_STATE_NONE			0U
#घोषणा BDEV_STATE_CLEAN		1U
#घोषणा BDEV_STATE_सूचीTY		2U
#घोषणा BDEV_STATE_STALE		3U

/*
 * Magic numbers
 *
 * The various other data काष्ठाures have their own magic numbers, which are
 * xored with the first part of the cache set's UUID
 */

#घोषणा JSET_MAGIC			0x245235c1a3625032ULL
#घोषणा PSET_MAGIC			0x6750e15f87337f91ULL
#घोषणा BSET_MAGIC			0x90135c78b99e07f5ULL

अटल अंतरभूत __u64 jset_magic(काष्ठा cache_sb *sb)
अणु
	वापस sb->set_magic ^ JSET_MAGIC;
पूर्ण

अटल अंतरभूत __u64 pset_magic(काष्ठा cache_sb *sb)
अणु
	वापस sb->set_magic ^ PSET_MAGIC;
पूर्ण

अटल अंतरभूत __u64 bset_magic(काष्ठा cache_sb *sb)
अणु
	वापस sb->set_magic ^ BSET_MAGIC;
पूर्ण

/*
 * Journal
 *
 * On disk क्रमmat क्रम a journal entry:
 * seq is monotonically increasing; every journal entry has its own unique
 * sequence number.
 *
 * last_seq is the oldest journal entry that still has keys the btree hasn't
 * flushed to disk yet.
 *
 * version is क्रम on disk क्रमmat changes.
 */

#घोषणा BCACHE_JSET_VERSION_UUIDv1	1
#घोषणा BCACHE_JSET_VERSION_UUID	1	/* Always latest UUID क्रमmat */
#घोषणा BCACHE_JSET_VERSION		1

काष्ठा jset अणु
	__u64			csum;
	__u64			magic;
	__u64			seq;
	__u32			version;
	__u32			keys;

	__u64			last_seq;

	BKEY_PADDED(uuid_bucket);
	BKEY_PADDED(btree_root);
	__u16			btree_level;
	__u16			pad[3];

	__u64			prio_bucket[MAX_CACHES_PER_SET];

	जोड़ अणु
		काष्ठा bkey	start[0];
		__u64		d[0];
	पूर्ण;
पूर्ण;

/* Bucket prios/gens */

काष्ठा prio_set अणु
	__u64			csum;
	__u64			magic;
	__u64			seq;
	__u32			version;
	__u32			pad;

	__u64			next_bucket;

	काष्ठा bucket_disk अणु
		__u16		prio;
		__u8		gen;
	पूर्ण __attribute((packed)) data[];
पूर्ण;

/* UUIDS - per backing device/flash only volume metadata */

काष्ठा uuid_entry अणु
	जोड़ अणु
		काष्ठा अणु
			__u8	uuid[16];
			__u8	label[32];
			__u32	first_reg; /* समय overflow in y2106 */
			__u32	last_reg;
			__u32	invalidated;

			__u32	flags;
			/* Size of flash only volumes */
			__u64	sectors;
		पूर्ण;

		__u8		pad[128];
	पूर्ण;
पूर्ण;

BITMASK(UUID_FLASH_ONLY,	काष्ठा uuid_entry, flags, 0, 1);

/* Btree nodes */

/* Version 1: Seed poपूर्णांकer पूर्णांकo btree node checksum
 */
#घोषणा BCACHE_BSET_CSUM		1
#घोषणा BCACHE_BSET_VERSION		1

/*
 * Btree nodes
 *
 * On disk a btree node is a list/log of these; within each set the keys are
 * sorted
 */
काष्ठा bset अणु
	__u64			csum;
	__u64			magic;
	__u64			seq;
	__u32			version;
	__u32			keys;

	जोड़ अणु
		काष्ठा bkey	start[0];
		__u64		d[0];
	पूर्ण;
पूर्ण;

/* OBSOLETE */

/* UUIDS - per backing device/flash only volume metadata */

काष्ठा uuid_entry_v0 अणु
	__u8		uuid[16];
	__u8		label[32];
	__u32		first_reg;
	__u32		last_reg;
	__u32		invalidated;
	__u32		pad;
पूर्ण;

#पूर्ण_अगर /* _LINUX_BCACHE_H */
