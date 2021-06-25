<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Block Translation Table library
 * Copyright (c) 2014-2015, Intel Corporation.
 */

#अगर_अघोषित _LINUX_BTT_H
#घोषणा _LINUX_BTT_H

#समावेश <linux/types.h>

#घोषणा BTT_SIG_LEN 16
#घोषणा BTT_SIG "BTT_ARENA_INFO\0"
#घोषणा MAP_ENT_SIZE 4
#घोषणा MAP_TRIM_SHIFT 31
#घोषणा MAP_TRIM_MASK (1 << MAP_TRIM_SHIFT)
#घोषणा MAP_ERR_SHIFT 30
#घोषणा MAP_ERR_MASK (1 << MAP_ERR_SHIFT)
#घोषणा MAP_LBA_MASK (~((1 << MAP_TRIM_SHIFT) | (1 << MAP_ERR_SHIFT)))
#घोषणा MAP_ENT_NORMAL 0xC0000000
#घोषणा LOG_GRP_SIZE माप(काष्ठा log_group)
#घोषणा LOG_ENT_SIZE माप(काष्ठा log_entry)
#घोषणा ARENA_MIN_SIZE (1UL << 24)	/* 16 MB */
#घोषणा ARENA_MAX_SIZE (1ULL << 39)	/* 512 GB */
#घोषणा RTT_VALID (1UL << 31)
#घोषणा RTT_INVALID 0
#घोषणा BTT_PG_SIZE 4096
#घोषणा BTT_DEFAULT_NFREE ND_MAX_LANES
#घोषणा LOG_SEQ_INIT 1

#घोषणा IB_FLAG_ERROR 0x00000001
#घोषणा IB_FLAG_ERROR_MASK 0x00000001

#घोषणा ent_lba(ent) (ent & MAP_LBA_MASK)
#घोषणा ent_e_flag(ent) (!!(ent & MAP_ERR_MASK))
#घोषणा ent_z_flag(ent) (!!(ent & MAP_TRIM_MASK))
#घोषणा set_e_flag(ent) (ent |= MAP_ERR_MASK)
/* 'normal' is both e and z flags set */
#घोषणा ent_normal(ent) (ent_e_flag(ent) && ent_z_flag(ent))

क्रमागत btt_init_state अणु
	INIT_UNCHECKED = 0,
	INIT_NOTFOUND,
	INIT_READY
पूर्ण;

/*
 * A log group represents one log 'lane', and consists of four log entries.
 * Two of the four entries are valid entries, and the reमुख्यing two are
 * padding. Due to an old bug in the padding location, we need to perक्रमm a
 * test to determine the padding scheme being used, and use that scheme
 * thereafter.
 *
 * In kernels prior to 4.15, 'log group' would have actual log entries at
 * indices (0, 2) and padding at indices (1, 3), where as the correct/updated
 * क्रमmat has log entries at indices (0, 1) and padding at indices (2, 3).
 *
 * Old (pre 4.15) क्रमmat:
 * +-----------------+-----------------+
 * |      ent[0]     |      ent[1]     |
 * |       16B       |       16B       |
 * | lba/old/new/seq |       pad       |
 * +-----------------------------------+
 * |      ent[2]     |      ent[3]     |
 * |       16B       |       16B       |
 * | lba/old/new/seq |       pad       |
 * +-----------------+-----------------+
 *
 * New क्रमmat:
 * +-----------------+-----------------+
 * |      ent[0]     |      ent[1]     |
 * |       16B       |       16B       |
 * | lba/old/new/seq | lba/old/new/seq |
 * +-----------------------------------+
 * |      ent[2]     |      ent[3]     |
 * |       16B       |       16B       |
 * |       pad       |       pad       |
 * +-----------------+-----------------+
 *
 * We detect during start-up which क्रमmat is in use, and set
 * arena->log_index[(0, 1)] with the detected क्रमmat.
 */

काष्ठा log_entry अणु
	__le32 lba;
	__le32 old_map;
	__le32 new_map;
	__le32 seq;
पूर्ण;

काष्ठा log_group अणु
	काष्ठा log_entry ent[4];
पूर्ण;

काष्ठा btt_sb अणु
	u8 signature[BTT_SIG_LEN];
	u8 uuid[16];
	u8 parent_uuid[16];
	__le32 flags;
	__le16 version_major;
	__le16 version_minor;
	__le32 बाह्यal_lbasize;
	__le32 बाह्यal_nlba;
	__le32 पूर्णांकernal_lbasize;
	__le32 पूर्णांकernal_nlba;
	__le32 nमुक्त;
	__le32 infosize;
	__le64 nextoff;
	__le64 dataoff;
	__le64 mapoff;
	__le64 logoff;
	__le64 info2off;
	u8 padding[3968];
	__le64 checksum;
पूर्ण;

काष्ठा मुक्त_entry अणु
	u32 block;
	u8 sub;
	u8 seq;
	u8 has_err;
पूर्ण;

काष्ठा aligned_lock अणु
	जोड़ अणु
		spinlock_t lock;
		u8 cacheline_padding[L1_CACHE_BYTES];
	पूर्ण;
पूर्ण;

/**
 * काष्ठा arena_info - handle क्रम an arena
 * @size:		Size in bytes this arena occupies on the raw device.
 *			This includes arena metadata.
 * @बाह्यal_lba_start:	The first बाह्यal LBA in this arena.
 * @पूर्णांकernal_nlba:	Number of पूर्णांकernal blocks available in the arena
 *			including nमुक्त reserved blocks
 * @पूर्णांकernal_lbasize:	Internal and बाह्यal lba sizes may be dअगरferent as
 *			we can round up 'odd' बाह्यal lbasizes such as 520B
 *			to be aligned.
 * @बाह्यal_nlba:	Number of blocks contributed by the arena to the number
 *			reported to upper layers. (पूर्णांकernal_nlba - nमुक्त)
 * @बाह्यal_lbasize:	LBA size as exposed to upper layers.
 * @nमुक्त:		A reserve number of 'free' blocks that is used to
 *			handle incoming ग_लिखोs.
 * @version_major:	Metadata layout version major.
 * @version_minor:	Metadata layout version minor.
 * @sector_size:	The Linux sector size - 512 or 4096
 * @nextoff:		Offset in bytes to the start of the next arena.
 * @infooff:		Offset in bytes to the info block of this arena.
 * @dataoff:		Offset in bytes to the data area of this arena.
 * @mapoff:		Offset in bytes to the map area of this arena.
 * @logoff:		Offset in bytes to the log area of this arena.
 * @info2off:		Offset in bytes to the backup info block of this arena.
 * @मुक्तlist:		Poपूर्णांकer to in-memory list of मुक्त blocks
 * @rtt:		Poपूर्णांकer to in-memory "Read Tracking Table"
 * @map_locks:		Spinlocks protecting concurrent map ग_लिखोs
 * @nd_btt:		Poपूर्णांकer to parent nd_btt काष्ठाure.
 * @list:		List head क्रम list of arenas
 * @debugfs_dir:	Debugfs dentry
 * @flags:		Arena flags - may signअगरy error states.
 * @err_lock:		Mutex क्रम synchronizing error clearing.
 * @log_index:		Indices of the valid log entries in a log_group
 *
 * arena_info is a per-arena handle. Once an arena is narrowed करोwn क्रम an
 * IO, this काष्ठा is passed around क्रम the duration of the IO.
 */
काष्ठा arena_info अणु
	u64 size;			/* Total bytes क्रम this arena */
	u64 बाह्यal_lba_start;
	u32 पूर्णांकernal_nlba;
	u32 पूर्णांकernal_lbasize;
	u32 बाह्यal_nlba;
	u32 बाह्यal_lbasize;
	u32 nमुक्त;
	u16 version_major;
	u16 version_minor;
	u32 sector_size;
	/* Byte offsets to the dअगरferent on-media काष्ठाures */
	u64 nextoff;
	u64 infooff;
	u64 dataoff;
	u64 mapoff;
	u64 logoff;
	u64 info2off;
	/* Poपूर्णांकers to other in-memory काष्ठाures क्रम this arena */
	काष्ठा मुक्त_entry *मुक्तlist;
	u32 *rtt;
	काष्ठा aligned_lock *map_locks;
	काष्ठा nd_btt *nd_btt;
	काष्ठा list_head list;
	काष्ठा dentry *debugfs_dir;
	/* Arena flags */
	u32 flags;
	काष्ठा mutex err_lock;
	पूर्णांक log_index[2];
पूर्ण;

काष्ठा badblocks;

/**
 * काष्ठा btt - handle क्रम a BTT instance
 * @btt_disk:		Poपूर्णांकer to the gendisk क्रम BTT device
 * @btt_queue:		Poपूर्णांकer to the request queue क्रम the BTT device
 * @arena_list:		Head of the list of arenas
 * @debugfs_dir:	Debugfs dentry
 * @nd_btt:		Parent nd_btt काष्ठा
 * @nlba:		Number of logical blocks exposed to the	upper layers
 *			after removing the amount of space needed by metadata
 * @rawsize:		Total size in bytes of the available backing device
 * @lbasize:		LBA size as requested and presented to upper layers.
 *			This is sector_size + size of any metadata.
 * @sector_size:	The Linux sector size - 512 or 4096
 * @lanes:		Per-lane spinlocks
 * @init_lock:		Mutex used क्रम the BTT initialization
 * @init_state:		Flag describing the initialization state क्रम the BTT
 * @num_arenas:		Number of arenas in the BTT instance
 * @phys_bb:		Poपूर्णांकer to the namespace's badblocks काष्ठाure
 */
काष्ठा btt अणु
	काष्ठा gendisk *btt_disk;
	काष्ठा request_queue *btt_queue;
	काष्ठा list_head arena_list;
	काष्ठा dentry *debugfs_dir;
	काष्ठा nd_btt *nd_btt;
	u64 nlba;
	अचिन्हित दीर्घ दीर्घ rawsize;
	u32 lbasize;
	u32 sector_size;
	काष्ठा nd_region *nd_region;
	काष्ठा mutex init_lock;
	पूर्णांक init_state;
	पूर्णांक num_arenas;
	काष्ठा badblocks *phys_bb;
पूर्ण;

bool nd_btt_arena_is_valid(काष्ठा nd_btt *nd_btt, काष्ठा btt_sb *super);
पूर्णांक nd_btt_version(काष्ठा nd_btt *nd_btt, काष्ठा nd_namespace_common *ndns,
		काष्ठा btt_sb *btt_sb);

#पूर्ण_अगर
