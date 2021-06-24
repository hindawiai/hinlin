<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित SQUASHFS_FS
#घोषणा SQUASHFS_FS
/*
 * Squashfs
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * squashfs_fs.h
 */

#घोषणा SQUASHFS_CACHED_FRAGMENTS	CONFIG_SQUASHFS_FRAGMENT_CACHE_SIZE
#घोषणा SQUASHFS_MAJOR			4
#घोषणा SQUASHFS_MINOR			0
#घोषणा SQUASHFS_START			0

/* size of metadata (inode and directory) blocks */
#घोषणा SQUASHFS_METADATA_SIZE		8192
#घोषणा SQUASHFS_BLOCK_OFFSET		2

/* शेष size of block device I/O */
#अगर_घोषित CONFIG_SQUASHFS_4K_DEVBLK_SIZE
#घोषणा SQUASHFS_DEVBLK_SIZE 4096
#अन्यथा
#घोषणा SQUASHFS_DEVBLK_SIZE 1024
#पूर्ण_अगर

#घोषणा SQUASHFS_खाता_MAX_SIZE		1048576
#घोषणा SQUASHFS_खाता_MAX_LOG		20

/* Max length of filename (not 255) */
#घोषणा SQUASHFS_NAME_LEN		256

/* Max value क्रम directory header count*/
#घोषणा SQUASHFS_सूची_COUNT		256

#घोषणा SQUASHFS_INVALID_FRAG		(0xffffffffU)
#घोषणा SQUASHFS_INVALID_XATTR		(0xffffffffU)
#घोषणा SQUASHFS_INVALID_BLK		(-1LL)

/* Fileप्रणाली flags */
#घोषणा SQUASHFS_NOI			0
#घोषणा SQUASHFS_NOD			1
#घोषणा SQUASHFS_NOF			3
#घोषणा SQUASHFS_NO_FRAG		4
#घोषणा SQUASHFS_ALWAYS_FRAG		5
#घोषणा SQUASHFS_DUPLICATE		6
#घोषणा SQUASHFS_EXPORT			7
#घोषणा SQUASHFS_COMP_OPT		10

#घोषणा SQUASHFS_BIT(flag, bit)		((flag >> bit) & 1)

#घोषणा SQUASHFS_UNCOMPRESSED_INODES(flags)	SQUASHFS_BIT(flags, \
						SQUASHFS_NOI)

#घोषणा SQUASHFS_UNCOMPRESSED_DATA(flags)	SQUASHFS_BIT(flags, \
						SQUASHFS_NOD)

#घोषणा SQUASHFS_UNCOMPRESSED_FRAGMENTS(flags)	SQUASHFS_BIT(flags, \
						SQUASHFS_NOF)

#घोषणा SQUASHFS_NO_FRAGMENTS(flags)		SQUASHFS_BIT(flags, \
						SQUASHFS_NO_FRAG)

#घोषणा SQUASHFS_ALWAYS_FRAGMENTS(flags)	SQUASHFS_BIT(flags, \
						SQUASHFS_ALWAYS_FRAG)

#घोषणा SQUASHFS_DUPLICATES(flags)		SQUASHFS_BIT(flags, \
						SQUASHFS_DUPLICATE)

#घोषणा SQUASHFS_EXPORTABLE(flags)		SQUASHFS_BIT(flags, \
						SQUASHFS_EXPORT)

#घोषणा SQUASHFS_COMP_OPTS(flags)		SQUASHFS_BIT(flags, \
						SQUASHFS_COMP_OPT)

/* Inode types including extended types */
#घोषणा SQUASHFS_सूची_TYPE		1
#घोषणा SQUASHFS_REG_TYPE		2
#घोषणा SQUASHFS_SYMLINK_TYPE		3
#घोषणा SQUASHFS_BLKDEV_TYPE		4
#घोषणा SQUASHFS_CHRDEV_TYPE		5
#घोषणा SQUASHFS_FIFO_TYPE		6
#घोषणा SQUASHFS_SOCKET_TYPE		7
#घोषणा SQUASHFS_Lसूची_TYPE		8
#घोषणा SQUASHFS_LREG_TYPE		9
#घोषणा SQUASHFS_LSYMLINK_TYPE		10
#घोषणा SQUASHFS_LBLKDEV_TYPE		11
#घोषणा SQUASHFS_LCHRDEV_TYPE		12
#घोषणा SQUASHFS_LFIFO_TYPE		13
#घोषणा SQUASHFS_LSOCKET_TYPE		14

/* Max type value stored in directory entry */
#घोषणा SQUASHFS_MAX_सूची_TYPE		7

/* Xattr types */
#घोषणा SQUASHFS_XATTR_USER             0
#घोषणा SQUASHFS_XATTR_TRUSTED          1
#घोषणा SQUASHFS_XATTR_SECURITY         2
#घोषणा SQUASHFS_XATTR_VALUE_OOL        256
#घोषणा SQUASHFS_XATTR_PREFIX_MASK      0xff

/* Flag whether block is compressed or uncompressed, bit is set अगर block is
 * uncompressed */
#घोषणा SQUASHFS_COMPRESSED_BIT		(1 << 15)

#घोषणा SQUASHFS_COMPRESSED_SIZE(B)	(((B) & ~SQUASHFS_COMPRESSED_BIT) ? \
		(B) & ~SQUASHFS_COMPRESSED_BIT :  SQUASHFS_COMPRESSED_BIT)

#घोषणा SQUASHFS_COMPRESSED(B)		(!((B) & SQUASHFS_COMPRESSED_BIT))

#घोषणा SQUASHFS_COMPRESSED_BIT_BLOCK	(1 << 24)

#घोषणा SQUASHFS_COMPRESSED_SIZE_BLOCK(B)	((B) & \
						~SQUASHFS_COMPRESSED_BIT_BLOCK)

#घोषणा SQUASHFS_COMPRESSED_BLOCK(B)	(!((B) & SQUASHFS_COMPRESSED_BIT_BLOCK))

अटल अंतरभूत पूर्णांक squashfs_block_size(__le32 raw)
अणु
	u32 size = le32_to_cpu(raw);
	वापस (size >> 25) ? -EIO : size;
पूर्ण

/*
 * Inode number ops.  Inodes consist of a compressed block number, and an
 * uncompressed offset within that block
 */
#घोषणा SQUASHFS_INODE_BLK(A)		((अचिन्हित पूर्णांक) ((A) >> 16))

#घोषणा SQUASHFS_INODE_OFFSET(A)	((अचिन्हित पूर्णांक) ((A) & 0xffff))

#घोषणा SQUASHFS_MKINODE(A, B)		((दीर्घ दीर्घ)(((दीर्घ दीर्घ) (A)\
					<< 16) + (B)))

/* fragment and fragment table defines */
#घोषणा SQUASHFS_FRAGMENT_BYTES(A)	\
				((A) * माप(काष्ठा squashfs_fragment_entry))

#घोषणा SQUASHFS_FRAGMENT_INDEX(A)	(SQUASHFS_FRAGMENT_BYTES(A) / \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_FRAGMENT_INDEX_OFFSET(A)	(SQUASHFS_FRAGMENT_BYTES(A) % \
						SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_FRAGMENT_INDEXES(A)	((SQUASHFS_FRAGMENT_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_FRAGMENT_INDEX_BYTES(A)	(SQUASHFS_FRAGMENT_INDEXES(A) *\
						माप(u64))

/* inode lookup table defines */
#घोषणा SQUASHFS_LOOKUP_BYTES(A)	((A) * माप(u64))

#घोषणा SQUASHFS_LOOKUP_BLOCK(A)	(SQUASHFS_LOOKUP_BYTES(A) / \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_LOOKUP_BLOCK_OFFSET(A)	(SQUASHFS_LOOKUP_BYTES(A) % \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_LOOKUP_BLOCKS(A)	((SQUASHFS_LOOKUP_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_LOOKUP_BLOCK_BYTES(A)	(SQUASHFS_LOOKUP_BLOCKS(A) *\
					माप(u64))

/* uid/gid lookup table defines */
#घोषणा SQUASHFS_ID_BYTES(A)		((A) * माप(अचिन्हित पूर्णांक))

#घोषणा SQUASHFS_ID_BLOCK(A)		(SQUASHFS_ID_BYTES(A) / \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_ID_BLOCK_OFFSET(A)	(SQUASHFS_ID_BYTES(A) % \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_ID_BLOCKS(A)		((SQUASHFS_ID_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_ID_BLOCK_BYTES(A)	(SQUASHFS_ID_BLOCKS(A) *\
					माप(u64))
/* xattr id lookup table defines */
#घोषणा SQUASHFS_XATTR_BYTES(A)		((A) * माप(काष्ठा squashfs_xattr_id))

#घोषणा SQUASHFS_XATTR_BLOCK(A)		(SQUASHFS_XATTR_BYTES(A) / \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_XATTR_BLOCK_OFFSET(A)	(SQUASHFS_XATTR_BYTES(A) % \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_XATTR_BLOCKS(A)	((SQUASHFS_XATTR_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#घोषणा SQUASHFS_XATTR_BLOCK_BYTES(A)	(SQUASHFS_XATTR_BLOCKS(A) *\
					माप(u64))
#घोषणा SQUASHFS_XATTR_BLK(A)		((अचिन्हित पूर्णांक) ((A) >> 16))

#घोषणा SQUASHFS_XATTR_OFFSET(A)	((अचिन्हित पूर्णांक) ((A) & 0xffff))

/* cached data स्थिरants क्रम fileप्रणाली */
#घोषणा SQUASHFS_CACHED_BLKS		8

/* meta index cache */
#घोषणा SQUASHFS_META_INDEXES	(SQUASHFS_METADATA_SIZE / माप(अचिन्हित पूर्णांक))
#घोषणा SQUASHFS_META_ENTRIES	127
#घोषणा SQUASHFS_META_SLOTS	8

काष्ठा meta_entry अणु
	u64			data_block;
	अचिन्हित पूर्णांक		index_block;
	अचिन्हित लघु		offset;
	अचिन्हित लघु		pad;
पूर्ण;

काष्ठा meta_index अणु
	अचिन्हित पूर्णांक		inode_number;
	अचिन्हित पूर्णांक		offset;
	अचिन्हित लघु		entries;
	अचिन्हित लघु		skip;
	अचिन्हित लघु		locked;
	अचिन्हित लघु		pad;
	काष्ठा meta_entry	meta_entry[SQUASHFS_META_ENTRIES];
पूर्ण;


/*
 * definitions क्रम काष्ठाures on disk
 */
#घोषणा ZLIB_COMPRESSION	1
#घोषणा LZMA_COMPRESSION	2
#घोषणा LZO_COMPRESSION		3
#घोषणा XZ_COMPRESSION		4
#घोषणा LZ4_COMPRESSION		5
#घोषणा ZSTD_COMPRESSION	6

काष्ठा squashfs_super_block अणु
	__le32			s_magic;
	__le32			inodes;
	__le32			mkfs_समय;
	__le32			block_size;
	__le32			fragments;
	__le16			compression;
	__le16			block_log;
	__le16			flags;
	__le16			no_ids;
	__le16			s_major;
	__le16			s_minor;
	__le64			root_inode;
	__le64			bytes_used;
	__le64			id_table_start;
	__le64			xattr_id_table_start;
	__le64			inode_table_start;
	__le64			directory_table_start;
	__le64			fragment_table_start;
	__le64			lookup_table_start;
पूर्ण;

काष्ठा squashfs_dir_index अणु
	__le32			index;
	__le32			start_block;
	__le32			size;
	अचिन्हित अक्षर		name[];
पूर्ण;

काष्ठा squashfs_base_inode अणु
	__le16			inode_type;
	__le16			mode;
	__le16			uid;
	__le16			guid;
	__le32			mसमय;
	__le32			inode_number;
पूर्ण;

काष्ठा squashfs_ipc_inode अणु
	__le16			inode_type;
	__le16			mode;
	__le16			uid;
	__le16			guid;
	__le32			mसमय;
	__le32			inode_number;
	__le32			nlink;
पूर्ण;

काष्ठा squashfs_lipc_inode अणु
	__le16			inode_type;
	__le16			mode;
	__le16			uid;
	__le16			guid;
	__le32			mसमय;
	__le32			inode_number;
	__le32			nlink;
	__le32			xattr;
पूर्ण;

काष्ठा squashfs_dev_inode अणु
	__le16			inode_type;
	__le16			mode;
	__le16			uid;
	__le16			guid;
	__le32			mसमय;
	__le32			inode_number;
	__le32			nlink;
	__le32			rdev;
पूर्ण;

काष्ठा squashfs_ldev_inode अणु
	__le16			inode_type;
	__le16			mode;
	__le16			uid;
	__le16			guid;
	__le32			mसमय;
	__le32			inode_number;
	__le32			nlink;
	__le32			rdev;
	__le32			xattr;
पूर्ण;

काष्ठा squashfs_symlink_inode अणु
	__le16			inode_type;
	__le16			mode;
	__le16			uid;
	__le16			guid;
	__le32			mसमय;
	__le32			inode_number;
	__le32			nlink;
	__le32			symlink_size;
	अक्षर			symlink[];
पूर्ण;

काष्ठा squashfs_reg_inode अणु
	__le16			inode_type;
	__le16			mode;
	__le16			uid;
	__le16			guid;
	__le32			mसमय;
	__le32			inode_number;
	__le32			start_block;
	__le32			fragment;
	__le32			offset;
	__le32			file_size;
	__le16			block_list[];
पूर्ण;

काष्ठा squashfs_lreg_inode अणु
	__le16			inode_type;
	__le16			mode;
	__le16			uid;
	__le16			guid;
	__le32			mसमय;
	__le32			inode_number;
	__le64			start_block;
	__le64			file_size;
	__le64			sparse;
	__le32			nlink;
	__le32			fragment;
	__le32			offset;
	__le32			xattr;
	__le16			block_list[];
पूर्ण;

काष्ठा squashfs_dir_inode अणु
	__le16			inode_type;
	__le16			mode;
	__le16			uid;
	__le16			guid;
	__le32			mसमय;
	__le32			inode_number;
	__le32			start_block;
	__le32			nlink;
	__le16			file_size;
	__le16			offset;
	__le32			parent_inode;
पूर्ण;

काष्ठा squashfs_ldir_inode अणु
	__le16			inode_type;
	__le16			mode;
	__le16			uid;
	__le16			guid;
	__le32			mसमय;
	__le32			inode_number;
	__le32			nlink;
	__le32			file_size;
	__le32			start_block;
	__le32			parent_inode;
	__le16			i_count;
	__le16			offset;
	__le32			xattr;
	काष्ठा squashfs_dir_index	index[];
पूर्ण;

जोड़ squashfs_inode अणु
	काष्ठा squashfs_base_inode		base;
	काष्ठा squashfs_dev_inode		dev;
	काष्ठा squashfs_ldev_inode		ldev;
	काष्ठा squashfs_symlink_inode		symlink;
	काष्ठा squashfs_reg_inode		reg;
	काष्ठा squashfs_lreg_inode		lreg;
	काष्ठा squashfs_dir_inode		dir;
	काष्ठा squashfs_ldir_inode		ldir;
	काष्ठा squashfs_ipc_inode		ipc;
	काष्ठा squashfs_lipc_inode		lipc;
पूर्ण;

काष्ठा squashfs_dir_entry अणु
	__le16			offset;
	__le16			inode_number;
	__le16			type;
	__le16			size;
	अक्षर			name[];
पूर्ण;

काष्ठा squashfs_dir_header अणु
	__le32			count;
	__le32			start_block;
	__le32			inode_number;
पूर्ण;

काष्ठा squashfs_fragment_entry अणु
	__le64			start_block;
	__le32			size;
	अचिन्हित पूर्णांक		unused;
पूर्ण;

काष्ठा squashfs_xattr_entry अणु
	__le16			type;
	__le16			size;
	अक्षर			data[];
पूर्ण;

काष्ठा squashfs_xattr_val अणु
	__le32			vsize;
	अक्षर			value[];
पूर्ण;

काष्ठा squashfs_xattr_id अणु
	__le64			xattr;
	__le32			count;
	__le32			size;
पूर्ण;

काष्ठा squashfs_xattr_id_table अणु
	__le64			xattr_table_start;
	__le32			xattr_ids;
	__le32			unused;
पूर्ण;

#पूर्ण_अगर
