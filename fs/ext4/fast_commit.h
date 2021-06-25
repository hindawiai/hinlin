<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __FAST_COMMIT_H__
#घोषणा __FAST_COMMIT_H__

/*
 * Note this file is present in e2fsprogs/lib/ext2fs/fast_commit.h and
 * linux/fs/ext4/fast_commit.h. These file should always be byte identical.
 */

/* Fast commit tags */
#घोषणा EXT4_FC_TAG_ADD_RANGE		0x0001
#घोषणा EXT4_FC_TAG_DEL_RANGE		0x0002
#घोषणा EXT4_FC_TAG_CREAT		0x0003
#घोषणा EXT4_FC_TAG_LINK		0x0004
#घोषणा EXT4_FC_TAG_UNLINK		0x0005
#घोषणा EXT4_FC_TAG_INODE		0x0006
#घोषणा EXT4_FC_TAG_PAD			0x0007
#घोषणा EXT4_FC_TAG_TAIL		0x0008
#घोषणा EXT4_FC_TAG_HEAD		0x0009

#घोषणा EXT4_FC_SUPPORTED_FEATURES	0x0

/* On disk fast commit tlv value काष्ठाures */

/* Fast commit on disk tag length काष्ठाure */
काष्ठा ext4_fc_tl अणु
	__le16 fc_tag;
	__le16 fc_len;
पूर्ण;

/* Value काष्ठाure क्रम tag EXT4_FC_TAG_HEAD. */
काष्ठा ext4_fc_head अणु
	__le32 fc_features;
	__le32 fc_tid;
पूर्ण;

/* Value काष्ठाure क्रम EXT4_FC_TAG_ADD_RANGE. */
काष्ठा ext4_fc_add_range अणु
	__le32 fc_ino;
	__u8 fc_ex[12];
पूर्ण;

/* Value काष्ठाure क्रम tag EXT4_FC_TAG_DEL_RANGE. */
काष्ठा ext4_fc_del_range अणु
	__le32 fc_ino;
	__le32 fc_lblk;
	__le32 fc_len;
पूर्ण;

/*
 * This is the value काष्ठाure क्रम tags EXT4_FC_TAG_CREAT, EXT4_FC_TAG_LINK
 * and EXT4_FC_TAG_UNLINK.
 */
काष्ठा ext4_fc_dentry_info अणु
	__le32 fc_parent_ino;
	__le32 fc_ino;
	__u8 fc_dname[0];
पूर्ण;

/* Value काष्ठाure क्रम EXT4_FC_TAG_INODE and EXT4_FC_TAG_INODE_PARTIAL. */
काष्ठा ext4_fc_inode अणु
	__le32 fc_ino;
	__u8 fc_raw_inode[0];
पूर्ण;

/* Value काष्ठाure क्रम tag EXT4_FC_TAG_TAIL. */
काष्ठा ext4_fc_tail अणु
	__le32 fc_tid;
	__le32 fc_crc;
पूर्ण;

/*
 * Fast commit reason codes
 */
क्रमागत अणु
	/*
	 * Commit status codes:
	 */
	EXT4_FC_REASON_OK = 0,
	EXT4_FC_REASON_INELIGIBLE,
	EXT4_FC_REASON_ALREADY_COMMITTED,
	EXT4_FC_REASON_FC_START_FAILED,
	EXT4_FC_REASON_FC_FAILED,

	/*
	 * Fast commit ineligiblity reasons:
	 */
	EXT4_FC_REASON_XATTR = 0,
	EXT4_FC_REASON_CROSS_RENAME,
	EXT4_FC_REASON_JOURNAL_FLAG_CHANGE,
	EXT4_FC_REASON_NOMEM,
	EXT4_FC_REASON_SWAP_BOOT,
	EXT4_FC_REASON_RESIZE,
	EXT4_FC_REASON_RENAME_सूची,
	EXT4_FC_REASON_FALLOC_RANGE,
	EXT4_FC_REASON_INODE_JOURNAL_DATA,
	EXT4_FC_COMMIT_FAILED,
	EXT4_FC_REASON_MAX
पूर्ण;

#अगर_घोषित __KERNEL__
/*
 * In memory list of dentry updates that are perक्रमmed on the file
 * प्रणाली used by fast commit code.
 */
काष्ठा ext4_fc_dentry_update अणु
	पूर्णांक fcd_op;		/* Type of update create / unlink / link */
	पूर्णांक fcd_parent;		/* Parent inode number */
	पूर्णांक fcd_ino;		/* Inode number */
	काष्ठा qstr fcd_name;	/* Dirent name */
	अचिन्हित अक्षर fcd_iname[DNAME_INLINE_LEN];	/* Dirent name string */
	काष्ठा list_head fcd_list;
पूर्ण;

काष्ठा ext4_fc_stats अणु
	अचिन्हित पूर्णांक fc_ineligible_reason_count[EXT4_FC_REASON_MAX];
	अचिन्हित दीर्घ fc_num_commits;
	अचिन्हित दीर्घ fc_ineligible_commits;
	अचिन्हित दीर्घ fc_numblks;
पूर्ण;

#घोषणा EXT4_FC_REPLAY_REALLOC_INCREMENT	4

/*
 * Physical block regions added to dअगरferent inodes due to fast commit
 * recovery. These are set during the SCAN phase. During the replay phase,
 * our allocator excludes these from its allocation. This ensures that
 * we करोn't accidentally allocating a block that is going to be used by
 * another inode.
 */
काष्ठा ext4_fc_alloc_region अणु
	ext4_lblk_t lblk;
	ext4_fsblk_t pblk;
	पूर्णांक ino, len;
पूर्ण;

/*
 * Fast commit replay state.
 */
काष्ठा ext4_fc_replay_state अणु
	पूर्णांक fc_replay_num_tags;
	पूर्णांक fc_replay_expected_off;
	पूर्णांक fc_current_pass;
	पूर्णांक fc_cur_tag;
	पूर्णांक fc_crc;
	काष्ठा ext4_fc_alloc_region *fc_regions;
	पूर्णांक fc_regions_size, fc_regions_used, fc_regions_valid;
	पूर्णांक *fc_modअगरied_inodes;
	पूर्णांक fc_modअगरied_inodes_used, fc_modअगरied_inodes_size;
पूर्ण;

#घोषणा region_last(__region) (((__region)->lblk) + ((__region)->len) - 1)
#पूर्ण_अगर

अटल अंतरभूत स्थिर अक्षर *tag2str(__u16 tag)
अणु
	चयन (tag) अणु
	हाल EXT4_FC_TAG_LINK:
		वापस "ADD_ENTRY";
	हाल EXT4_FC_TAG_UNLINK:
		वापस "DEL_ENTRY";
	हाल EXT4_FC_TAG_ADD_RANGE:
		वापस "ADD_RANGE";
	हाल EXT4_FC_TAG_CREAT:
		वापस "CREAT_DENTRY";
	हाल EXT4_FC_TAG_DEL_RANGE:
		वापस "DEL_RANGE";
	हाल EXT4_FC_TAG_INODE:
		वापस "INODE";
	हाल EXT4_FC_TAG_PAD:
		वापस "PAD";
	हाल EXT4_FC_TAG_TAIL:
		वापस "TAIL";
	हाल EXT4_FC_TAG_HEAD:
		वापस "HEAD";
	शेष:
		वापस "ERROR";
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __FAST_COMMIT_H__ */
