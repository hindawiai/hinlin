<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _OMFS_FS_H
#घोषणा _OMFS_FS_H

/* OMFS On-disk काष्ठाures */

#घोषणा OMFS_MAGIC 0xC2993D87
#घोषणा OMFS_IMAGIC 0xD2

#घोषणा OMFS_सूची 'D'
#घोषणा OMFS_खाता 'F'
#घोषणा OMFS_INODE_NORMAL 'e'
#घोषणा OMFS_INODE_CONTINUATION 'c'
#घोषणा OMFS_INODE_SYSTEM 's'
#घोषणा OMFS_NAMELEN 256
#घोषणा OMFS_सूची_START 0x1b8
#घोषणा OMFS_EXTENT_START 0x1d0
#घोषणा OMFS_EXTENT_CONT 0x40
#घोषणा OMFS_XOR_COUNT 19
#घोषणा OMFS_MAX_BLOCK_SIZE 8192
#घोषणा OMFS_MAX_CLUSTER_SIZE 8
#घोषणा OMFS_MAX_BLOCKS (1ul << 31)

काष्ठा omfs_super_block अणु
	अक्षर s_fill1[256];
	__be64 s_root_block;		/* block number of omfs_root_block */
	__be64 s_num_blocks;		/* total number of FS blocks */
	__be32 s_magic;			/* OMFS_MAGIC */
	__be32 s_blocksize;		/* size of a block */
	__be32 s_mirrors;		/* # of mirrors of प्रणाली blocks */
	__be32 s_sys_blocksize;		/* size of non-data blocks */
पूर्ण;

काष्ठा omfs_header अणु
	__be64 h_self;			/* FS block where this is located */
	__be32 h_body_size;		/* size of useful data after header */
	__be16 h_crc;			/* crc-ccitt of body_size bytes */
	अक्षर h_fill1[2];
	u8 h_version;			/* version, always 1 */
	अक्षर h_type;			/* OMFS_INODE_X */
	u8 h_magic;			/* OMFS_IMAGIC */
	u8 h_check_xor;			/* XOR of header bytes beक्रमe this */
	__be32 h_fill2;
पूर्ण;

काष्ठा omfs_root_block अणु
	काष्ठा omfs_header r_head;	/* header */
	__be64 r_fill1;
	__be64 r_num_blocks;		/* total number of FS blocks */
	__be64 r_root_dir;		/* block # of root directory */
	__be64 r_biपंचांगap;		/* block # of मुक्त space biपंचांगap */
	__be32 r_blocksize;		/* size of a block */
	__be32 r_clustersize;		/* size allocated क्रम data blocks */
	__be64 r_mirrors;		/* # of mirrors of प्रणाली blocks */
	अक्षर r_name[OMFS_NAMELEN];	/* partition label */
पूर्ण;

काष्ठा omfs_inode अणु
	काष्ठा omfs_header i_head;	/* header */
	__be64 i_parent;		/* parent containing this inode */
	__be64 i_sibling;		/* next inode in hash bucket */
	__be64 i_स_समय;			/* स_समय, in milliseconds */
	अक्षर i_fill1[35];
	अक्षर i_type;			/* OMFS_[सूची,खाता] */
	__be32 i_fill2;
	अक्षर i_fill3[64];
	अक्षर i_name[OMFS_NAMELEN];	/* filename */
	__be64 i_size;			/* size of file, in bytes */
पूर्ण;

काष्ठा omfs_extent_entry अणु
	__be64 e_cluster;		/* start location of a set of blocks */
	__be64 e_blocks;		/* number of blocks after e_cluster */
पूर्ण;

काष्ठा omfs_extent अणु
	__be64 e_next;			/* next extent table location */
	__be32 e_extent_count;		/* total # extents in this table */
	__be32 e_fill;
	काष्ठा omfs_extent_entry e_entry;	/* start of extent entries */
पूर्ण;

#पूर्ण_अगर
