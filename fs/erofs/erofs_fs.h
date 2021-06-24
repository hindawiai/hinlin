<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only OR Apache-2.0 */
/*
 * EROFS (Enhanced ROM File System) on-disk क्रमmat definition
 *
 * Copyright (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#अगर_अघोषित __EROFS_FS_H
#घोषणा __EROFS_FS_H

#घोषणा EROFS_SUPER_OFFSET      1024

#घोषणा EROFS_FEATURE_COMPAT_SB_CHKSUM          0x00000001

/*
 * Any bits that aren't in EROFS_ALL_FEATURE_INCOMPAT should
 * be incompatible with this kernel version.
 */
#घोषणा EROFS_FEATURE_INCOMPAT_LZ4_0PADDING	0x00000001
#घोषणा EROFS_FEATURE_INCOMPAT_COMPR_CFGS	0x00000002
#घोषणा EROFS_FEATURE_INCOMPAT_BIG_PCLUSTER	0x00000002
#घोषणा EROFS_ALL_FEATURE_INCOMPAT		\
	(EROFS_FEATURE_INCOMPAT_LZ4_0PADDING | \
	 EROFS_FEATURE_INCOMPAT_COMPR_CFGS | \
	 EROFS_FEATURE_INCOMPAT_BIG_PCLUSTER)

#घोषणा EROFS_SB_EXTSLOT_SIZE	16

/* erofs on-disk super block (currently 128 bytes) */
काष्ठा erofs_super_block अणु
	__le32 magic;           /* file प्रणाली magic number */
	__le32 checksum;        /* crc32c(super_block) */
	__le32 feature_compat;
	__u8 blkszbits;         /* support block_size == PAGE_SIZE only */
	__u8 sb_extslots;	/* superblock size = 128 + sb_extslots * 16 */

	__le16 root_nid;	/* nid of root directory */
	__le64 inos;            /* total valid ino # (== f_files - f_favail) */

	__le64 build_समय;      /* inode v1 समय derivation */
	__le32 build_समय_nsec;	/* inode v1 समय derivation in nano scale */
	__le32 blocks;          /* used क्रम statfs */
	__le32 meta_blkaddr;	/* start block address of metadata area */
	__le32 xattr_blkaddr;	/* start block address of shared xattr area */
	__u8 uuid[16];          /* 128-bit uuid क्रम volume */
	__u8 volume_name[16];   /* volume name */
	__le32 feature_incompat;
	जोड़ अणु
		/* biपंचांगap क्रम available compression algorithms */
		__le16 available_compr_algs;
		/* customized sliding winकरोw size instead of 64k by शेष */
		__le16 lz4_max_distance;
	पूर्ण __packed u1;
	__u8 reserved2[42];
पूर्ण;

/*
 * erofs inode datalayout (i_क्रमmat in on-disk inode):
 * 0 - inode plain without अंतरभूत data A:
 * inode, [xattrs], ... | ... | no-holed data
 * 1 - inode VLE compression B (legacy):
 * inode, [xattrs], extents ... | ...
 * 2 - inode plain with अंतरभूत data C:
 * inode, [xattrs], last_अंतरभूत_data, ... | ... | no-holed data
 * 3 - inode compression D:
 * inode, [xattrs], map_header, extents ... | ...
 * 4~7 - reserved
 */
क्रमागत अणु
	EROFS_INODE_FLAT_PLAIN			= 0,
	EROFS_INODE_FLAT_COMPRESSION_LEGACY	= 1,
	EROFS_INODE_FLAT_INLINE			= 2,
	EROFS_INODE_FLAT_COMPRESSION		= 3,
	EROFS_INODE_DATALAYOUT_MAX
पूर्ण;

अटल अंतरभूत bool erofs_inode_is_data_compressed(अचिन्हित पूर्णांक datamode)
अणु
	वापस datamode == EROFS_INODE_FLAT_COMPRESSION ||
		datamode == EROFS_INODE_FLAT_COMPRESSION_LEGACY;
पूर्ण

/* bit definitions of inode i_advise */
#घोषणा EROFS_I_VERSION_BITS            1
#घोषणा EROFS_I_DATALAYOUT_BITS         3

#घोषणा EROFS_I_VERSION_BIT             0
#घोषणा EROFS_I_DATALAYOUT_BIT          1

#घोषणा EROFS_I_ALL	\
	((1 << (EROFS_I_DATALAYOUT_BIT + EROFS_I_DATALAYOUT_BITS)) - 1)

/* 32-byte reduced क्रमm of an ondisk inode */
काष्ठा erofs_inode_compact अणु
	__le16 i_क्रमmat;	/* inode क्रमmat hपूर्णांकs */

/* 1 header + n-1 * 4 bytes अंतरभूत xattr to keep continuity */
	__le16 i_xattr_icount;
	__le16 i_mode;
	__le16 i_nlink;
	__le32 i_size;
	__le32 i_reserved;
	जोड़ अणु
		/* file total compressed blocks क्रम data mapping 1 */
		__le32 compressed_blocks;
		__le32 raw_blkaddr;

		/* क्रम device files, used to indicate old/new device # */
		__le32 rdev;
	पूर्ण i_u;
	__le32 i_ino;           /* only used क्रम 32-bit stat compatibility */
	__le16 i_uid;
	__le16 i_gid;
	__le32 i_reserved2;
पूर्ण;

/* 32 bytes on-disk inode */
#घोषणा EROFS_INODE_LAYOUT_COMPACT	0
/* 64 bytes on-disk inode */
#घोषणा EROFS_INODE_LAYOUT_EXTENDED	1

/* 64-byte complete क्रमm of an ondisk inode */
काष्ठा erofs_inode_extended अणु
	__le16 i_क्रमmat;	/* inode क्रमmat hपूर्णांकs */

/* 1 header + n-1 * 4 bytes अंतरभूत xattr to keep continuity */
	__le16 i_xattr_icount;
	__le16 i_mode;
	__le16 i_reserved;
	__le64 i_size;
	जोड़ अणु
		/* file total compressed blocks क्रम data mapping 1 */
		__le32 compressed_blocks;
		__le32 raw_blkaddr;

		/* क्रम device files, used to indicate old/new device # */
		__le32 rdev;
	पूर्ण i_u;

	/* only used क्रम 32-bit stat compatibility */
	__le32 i_ino;

	__le32 i_uid;
	__le32 i_gid;
	__le64 i_स_समय;
	__le32 i_स_समय_nsec;
	__le32 i_nlink;
	__u8   i_reserved2[16];
पूर्ण;

#घोषणा EROFS_MAX_SHARED_XATTRS         (128)
/* h_shared_count between 129 ... 255 are special # */
#घोषणा EROFS_SHARED_XATTR_EXTENT       (255)

/*
 * अंतरभूत xattrs (n == i_xattr_icount):
 * erofs_xattr_ibody_header(1) + (n - 1) * 4 bytes
 *          12 bytes           /                   \
 *                            /                     \
 *                           /-----------------------\
 *                           |  erofs_xattr_entries+ |
 *                           +-----------------------+
 * अंतरभूत xattrs must starts in erofs_xattr_ibody_header,
 * क्रम पढ़ो-only fs, no need to पूर्णांकroduce h_refcount
 */
काष्ठा erofs_xattr_ibody_header अणु
	__le32 h_reserved;
	__u8   h_shared_count;
	__u8   h_reserved2[7];
	__le32 h_shared_xattrs[0];      /* shared xattr id array */
पूर्ण;

/* Name indexes */
#घोषणा EROFS_XATTR_INDEX_USER              1
#घोषणा EROFS_XATTR_INDEX_POSIX_ACL_ACCESS  2
#घोषणा EROFS_XATTR_INDEX_POSIX_ACL_DEFAULT 3
#घोषणा EROFS_XATTR_INDEX_TRUSTED           4
#घोषणा EROFS_XATTR_INDEX_LUSTRE            5
#घोषणा EROFS_XATTR_INDEX_SECURITY          6

/* xattr entry (क्रम both अंतरभूत & shared xattrs) */
काष्ठा erofs_xattr_entry अणु
	__u8   e_name_len;      /* length of name */
	__u8   e_name_index;    /* attribute name index */
	__le16 e_value_size;    /* size of attribute value */
	/* followed by e_name and e_value */
	अक्षर   e_name[0];       /* attribute name */
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक erofs_xattr_ibody_size(__le16 i_xattr_icount)
अणु
	अगर (!i_xattr_icount)
		वापस 0;

	वापस माप(काष्ठा erofs_xattr_ibody_header) +
		माप(__u32) * (le16_to_cpu(i_xattr_icount) - 1);
पूर्ण

#घोषणा EROFS_XATTR_ALIGN(size) round_up(size, माप(काष्ठा erofs_xattr_entry))

अटल अंतरभूत अचिन्हित पूर्णांक erofs_xattr_entry_size(काष्ठा erofs_xattr_entry *e)
अणु
	वापस EROFS_XATTR_ALIGN(माप(काष्ठा erofs_xattr_entry) +
				 e->e_name_len + le16_to_cpu(e->e_value_size));
पूर्ण

/* maximum supported size of a physical compression cluster */
#घोषणा Z_EROFS_PCLUSTER_MAX_SIZE	(1024 * 1024)

/* available compression algorithm types (क्रम h_algorithmtype) */
क्रमागत अणु
	Z_EROFS_COMPRESSION_LZ4	= 0,
	Z_EROFS_COMPRESSION_MAX
पूर्ण;
#घोषणा Z_EROFS_ALL_COMPR_ALGS		(1 << (Z_EROFS_COMPRESSION_MAX - 1))

/* 14 bytes (+ length field = 16 bytes) */
काष्ठा z_erofs_lz4_cfgs अणु
	__le16 max_distance;
	__le16 max_pclusterblks;
	u8 reserved[10];
पूर्ण __packed;

/*
 * bit 0 : COMPACTED_2B indexes (0 - off; 1 - on)
 *  e.g. क्रम 4k logical cluster size,      4B        अगर compacted 2B is off;
 *                                  (4B) + 2B + (4B) अगर compacted 2B is on.
 * bit 1 : HEAD1 big pcluster (0 - off; 1 - on)
 * bit 2 : HEAD2 big pcluster (0 - off; 1 - on)
 */
#घोषणा Z_EROFS_ADVISE_COMPACTED_2B		0x0001
#घोषणा Z_EROFS_ADVISE_BIG_PCLUSTER_1		0x0002
#घोषणा Z_EROFS_ADVISE_BIG_PCLUSTER_2		0x0004

काष्ठा z_erofs_map_header अणु
	__le32	h_reserved1;
	__le16	h_advise;
	/*
	 * bit 0-3 : algorithm type of head 1 (logical cluster type 01);
	 * bit 4-7 : algorithm type of head 2 (logical cluster type 11).
	 */
	__u8	h_algorithmtype;
	/*
	 * bit 0-2 : logical cluster bits - 12, e.g. 0 क्रम 4096;
	 * bit 3-7 : reserved.
	 */
	__u8	h_clusterbits;
पूर्ण;

#घोषणा Z_EROFS_VLE_LEGACY_HEADER_PADDING       8

/*
 * Fixed-sized output compression ondisk Logical Extent cluster type:
 *    0 - literal (uncompressed) cluster
 *    1 - compressed cluster (क्रम the head logical cluster)
 *    2 - compressed cluster (क्रम the other logical clusters)
 *
 * In detail,
 *    0 - literal (uncompressed) cluster,
 *        di_advise = 0
 *        di_clusterofs = the literal data offset of the cluster
 *        di_blkaddr = the blkaddr of the literal cluster
 *
 *    1 - compressed cluster (क्रम the head logical cluster)
 *        di_advise = 1
 *        di_clusterofs = the decompressed data offset of the cluster
 *        di_blkaddr = the blkaddr of the compressed cluster
 *
 *    2 - compressed cluster (क्रम the other logical clusters)
 *        di_advise = 2
 *        di_clusterofs =
 *           the decompressed data offset in its own head cluster
 *        di_u.delta[0] = distance to its corresponding head cluster
 *        di_u.delta[1] = distance to its corresponding tail cluster
 *                (di_advise could be 0, 1 or 2)
 */
क्रमागत अणु
	Z_EROFS_VLE_CLUSTER_TYPE_PLAIN		= 0,
	Z_EROFS_VLE_CLUSTER_TYPE_HEAD		= 1,
	Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD	= 2,
	Z_EROFS_VLE_CLUSTER_TYPE_RESERVED	= 3,
	Z_EROFS_VLE_CLUSTER_TYPE_MAX
पूर्ण;

#घोषणा Z_EROFS_VLE_DI_CLUSTER_TYPE_BITS        2
#घोषणा Z_EROFS_VLE_DI_CLUSTER_TYPE_BIT         0

/*
 * D0_CBLKCNT will be marked _only_ at the 1st non-head lcluster to store the
 * compressed block count of a compressed extent (in logical clusters, aka.
 * block count of a pcluster).
 */
#घोषणा Z_EROFS_VLE_DI_D0_CBLKCNT		(1 << 11)

काष्ठा z_erofs_vle_decompressed_index अणु
	__le16 di_advise;
	/* where to decompress in the head cluster */
	__le16 di_clusterofs;

	जोड़ अणु
		/* क्रम the head cluster */
		__le32 blkaddr;
		/*
		 * क्रम the rest clusters
		 * eg. क्रम 4k page-sized cluster, maximum 4K*64k = 256M)
		 * [0] - poपूर्णांकing to the head cluster
		 * [1] - poपूर्णांकing to the tail cluster
		 */
		__le16 delta[2];
	पूर्ण di_u;
पूर्ण;

#घोषणा Z_EROFS_VLE_LEGACY_INDEX_ALIGN(size) \
	(round_up(size, माप(काष्ठा z_erofs_vle_decompressed_index)) + \
	 माप(काष्ठा z_erofs_map_header) + Z_EROFS_VLE_LEGACY_HEADER_PADDING)

/* dirent sorts in alphabet order, thus we can करो binary search */
काष्ठा erofs_dirent अणु
	__le64 nid;     /* node number */
	__le16 nameoff; /* start offset of file name */
	__u8 file_type; /* file type */
	__u8 reserved;  /* reserved */
पूर्ण __packed;

/*
 * EROFS file types should match generic FT_* types and
 * it seems no need to add BUILD_BUG_ONs since potential
 * unmatchness will अवरोध other fses as well...
 */

#घोषणा EROFS_NAME_LEN      255

/* check the EROFS on-disk layout strictly at compile समय */
अटल अंतरभूत व्योम erofs_check_ondisk_layout_definitions(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा erofs_super_block) != 128);
	BUILD_BUG_ON(माप(काष्ठा erofs_inode_compact) != 32);
	BUILD_BUG_ON(माप(काष्ठा erofs_inode_extended) != 64);
	BUILD_BUG_ON(माप(काष्ठा erofs_xattr_ibody_header) != 12);
	BUILD_BUG_ON(माप(काष्ठा erofs_xattr_entry) != 4);
	BUILD_BUG_ON(माप(काष्ठा z_erofs_map_header) != 8);
	BUILD_BUG_ON(माप(काष्ठा z_erofs_vle_decompressed_index) != 8);
	BUILD_BUG_ON(माप(काष्ठा erofs_dirent) != 12);

	BUILD_BUG_ON(BIT(Z_EROFS_VLE_DI_CLUSTER_TYPE_BITS) <
		     Z_EROFS_VLE_CLUSTER_TYPE_MAX - 1);
पूर्ण

#पूर्ण_अगर

