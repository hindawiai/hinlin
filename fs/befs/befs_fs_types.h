<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs/befs/befs_fs_types.h
 *
 * Copyright (C) 2001 Will Dyson (will@cs.earlham.edu)
 *
 *
 *
 * from linux/include/linux/befs_fs.h
 *
 * Copyright (C) 1999 Makoto Kato (m_kato@ga2.so-net.ne.jp)
 *
 */

#अगर_अघोषित _LINUX_BEFS_FS_TYPES
#घोषणा _LINUX_BEFS_FS_TYPES

#अगर_घोषित __KERNEL__
#समावेश <linux/types.h>
#पूर्ण_अगर /*__KERNEL__*/

#घोषणा PACKED __attribute__ ((__packed__))

/*
 * Max name lengths of BFS
 */

#घोषणा BEFS_NAME_LEN 255

#घोषणा BEFS_SYMLINK_LEN 144
#घोषणा BEFS_NUM_सूचीECT_BLOCKS 12
#घोषणा B_OS_NAME_LENGTH 32

/* The datastream blocks mapped by the द्विगुन-indirect
 * block are always 4 fs blocks दीर्घ.
 * This eliminates the need क्रम linear searches among
 * the potentially huge number of indirect blocks
 *
 * Err. Should that be 4 fs blocks or 4k???
 * It matters on large blocksize volumes
 */
#घोषणा BEFS_DBLINसूची_BRUN_LEN 4

/*
 * Flags of superblock
 */

क्रमागत super_flags अणु
	BEFS_BYTESEX_BE,
	BEFS_BYTESEX_LE,
	BEFS_CLEAN = 0x434c454e,
	BEFS_सूचीTY = 0x44495254,
	BEFS_SUPER_MAGIC1 = 0x42465331,	/* BFS1 */
	BEFS_SUPER_MAGIC2 = 0xdd121031,
	BEFS_SUPER_MAGIC3 = 0x15b6830e,
पूर्ण;

#घोषणा BEFS_BYTEORDER_NATIVE 0x42494745
#घोषणा BEFS_BYTEORDER_NATIVE_LE ((__क्रमce fs32)cpu_to_le32(BEFS_BYTEORDER_NATIVE))
#घोषणा BEFS_BYTEORDER_NATIVE_BE ((__क्रमce fs32)cpu_to_be32(BEFS_BYTEORDER_NATIVE))

#घोषणा BEFS_SUPER_MAGIC BEFS_SUPER_MAGIC1
#घोषणा BEFS_SUPER_MAGIC1_LE ((__क्रमce fs32)cpu_to_le32(BEFS_SUPER_MAGIC1))
#घोषणा BEFS_SUPER_MAGIC1_BE ((__क्रमce fs32)cpu_to_be32(BEFS_SUPER_MAGIC1))

/*
 * Flags of inode
 */

#घोषणा BEFS_INODE_MAGIC1 0x3bbe0ad9

क्रमागत inode_flags अणु
	BEFS_INODE_IN_USE = 0x00000001,
	BEFS_ATTR_INODE = 0x00000004,
	BEFS_INODE_LOGGED = 0x00000008,
	BEFS_INODE_DELETED = 0x00000010,
	BEFS_LONG_SYMLINK = 0x00000040,
	BEFS_PERMANENT_FLAG = 0x0000ffff,
	BEFS_INODE_NO_CREATE = 0x00010000,
	BEFS_INODE_WAS_WRITTEN = 0x00020000,
	BEFS_NO_TRANSACTION = 0x00040000,
पूर्ण;
/*
 * On-Disk dataकाष्ठाures of BeFS
 */

प्रकार u64 __bitwise fs64;
प्रकार u32 __bitwise fs32;
प्रकार u16 __bitwise fs16;

प्रकार u64 befs_off_t;
प्रकार fs64 befs_समय_प्रकार;

/* Block runs */
प्रकार काष्ठा अणु
	fs32 allocation_group;
	fs16 start;
	fs16 len;
पूर्ण PACKED befs_disk_block_run;

प्रकार काष्ठा अणु
	u32 allocation_group;
	u16 start;
	u16 len;
पूर्ण PACKED befs_block_run;

प्रकार befs_disk_block_run befs_disk_inode_addr;
प्रकार befs_block_run befs_inode_addr;

/*
 * The Superblock Structure
 */
प्रकार काष्ठा अणु
	अक्षर name[B_OS_NAME_LENGTH];
	fs32 magic1;
	fs32 fs_byte_order;

	fs32 block_size;
	fs32 block_shअगरt;

	fs64 num_blocks;
	fs64 used_blocks;

	fs32 inode_size;

	fs32 magic2;
	fs32 blocks_per_ag;
	fs32 ag_shअगरt;
	fs32 num_ags;

	fs32 flags;

	befs_disk_block_run log_blocks;
	fs64 log_start;
	fs64 log_end;

	fs32 magic3;
	befs_disk_inode_addr root_dir;
	befs_disk_inode_addr indices;

पूर्ण PACKED befs_super_block;

/*
 * Note: the indirect and dbl_indir block_runs may
 * be दीर्घer than one block!
 */
प्रकार काष्ठा अणु
	befs_disk_block_run direct[BEFS_NUM_सूचीECT_BLOCKS];
	fs64 max_direct_range;
	befs_disk_block_run indirect;
	fs64 max_indirect_range;
	befs_disk_block_run द्विगुन_indirect;
	fs64 max_द्विगुन_indirect_range;
	fs64 size;
पूर्ण PACKED befs_disk_data_stream;

प्रकार काष्ठा अणु
	befs_block_run direct[BEFS_NUM_सूचीECT_BLOCKS];
	befs_off_t max_direct_range;
	befs_block_run indirect;
	befs_off_t max_indirect_range;
	befs_block_run द्विगुन_indirect;
	befs_off_t max_द्विगुन_indirect_range;
	befs_off_t size;
पूर्ण PACKED befs_data_stream;

/* Attribute */
प्रकार काष्ठा अणु
	fs32 type;
	fs16 name_size;
	fs16 data_size;
	अक्षर name[1];
पूर्ण PACKED befs_small_data;

/* Inode काष्ठाure */
प्रकार काष्ठा अणु
	fs32 magic1;
	befs_disk_inode_addr inode_num;
	fs32 uid;
	fs32 gid;
	fs32 mode;
	fs32 flags;
	befs_समय_प्रकार create_समय;
	befs_समय_प्रकार last_modअगरied_समय;
	befs_disk_inode_addr parent;
	befs_disk_inode_addr attributes;
	fs32 type;

	fs32 inode_size;
	fs32 etc;		/* not use */

	जोड़ अणु
		befs_disk_data_stream datastream;
		अक्षर symlink[BEFS_SYMLINK_LEN];
	पूर्ण data;

	fs32 pad[4];		/* not use */
	befs_small_data small_data[1];
पूर्ण PACKED befs_inode;

/*
 * B+tree superblock
 */

#घोषणा BEFS_BTREE_MAGIC 0x69f6c2e8

क्रमागत btree_types अणु
	BTREE_STRING_TYPE = 0,
	BTREE_INT32_TYPE = 1,
	BTREE_UINT32_TYPE = 2,
	BTREE_INT64_TYPE = 3,
	BTREE_UINT64_TYPE = 4,
	BTREE_FLOAT_TYPE = 5,
	BTREE_DOUBLE_TYPE = 6
पूर्ण;

प्रकार काष्ठा अणु
	fs32 magic;
	fs32 node_size;
	fs32 max_depth;
	fs32 data_type;
	fs64 root_node_ptr;
	fs64 मुक्त_node_ptr;
	fs64 max_size;
पूर्ण PACKED befs_disk_btree_super;

प्रकार काष्ठा अणु
	u32 magic;
	u32 node_size;
	u32 max_depth;
	u32 data_type;
	befs_off_t root_node_ptr;
	befs_off_t मुक्त_node_ptr;
	befs_off_t max_size;
पूर्ण PACKED befs_btree_super;

/*
 * Header काष्ठाure of each btree node
 */
प्रकार काष्ठा अणु
	fs64 left;
	fs64 right;
	fs64 overflow;
	fs16 all_key_count;
	fs16 all_key_length;
पूर्ण PACKED befs_btree_nodehead;

प्रकार काष्ठा अणु
	befs_off_t left;
	befs_off_t right;
	befs_off_t overflow;
	u16 all_key_count;
	u16 all_key_length;
पूर्ण PACKED befs_host_btree_nodehead;

#पूर्ण_अगर				/* _LINUX_BEFS_FS_TYPES */
