<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_DA_FORMAT_H__
#घोषणा __XFS_DA_FORMAT_H__

/*
 * This काष्ठाure is common to both leaf nodes and non-leaf nodes in the Btree.
 *
 * It is used to manage a करोubly linked list of all blocks at the same
 * level in the Btree, and to identअगरy which type of block this is.
 */
#घोषणा XFS_DA_NODE_MAGIC	0xfebe	/* magic number: non-leaf blocks */
#घोषणा XFS_ATTR_LEAF_MAGIC	0xfbee	/* magic number: attribute leaf blks */
#घोषणा XFS_सूची2_LEAF1_MAGIC	0xd2f1	/* magic number: v2 dirlf single blks */
#घोषणा XFS_सूची2_LEAFN_MAGIC	0xd2ff	/* magic number: v2 dirlf multi blks */

प्रकार काष्ठा xfs_da_blkinfo अणु
	__be32		क्रमw;			/* previous block in list */
	__be32		back;			/* following block in list */
	__be16		magic;			/* validity check on block */
	__be16		pad;			/* unused */
पूर्ण xfs_da_blkinfo_t;

/*
 * CRC enabled directory काष्ठाure types
 *
 * The headers change size क्रम the additional verअगरication inक्रमmation, but
 * otherwise the tree layouts and contents are unchanged. Hence the da btree
 * code can use the काष्ठा xfs_da_blkinfo क्रम manipulating the tree links and
 * magic numbers without modअगरication क्रम both v2 and v3 nodes.
 */
#घोषणा XFS_DA3_NODE_MAGIC	0x3ebe	/* magic number: non-leaf blocks */
#घोषणा XFS_ATTR3_LEAF_MAGIC	0x3bee	/* magic number: attribute leaf blks */
#घोषणा XFS_सूची3_LEAF1_MAGIC	0x3df1	/* magic number: v3 dirlf single blks */
#घोषणा XFS_सूची3_LEAFN_MAGIC	0x3dff	/* magic number: v3 dirlf multi blks */

काष्ठा xfs_da3_blkinfo अणु
	/*
	 * the node link manipulation code relies on the fact that the first
	 * element of this काष्ठाure is the काष्ठा xfs_da_blkinfo so it can
	 * ignore the dअगरferences in the rest of the काष्ठाures.
	 */
	काष्ठा xfs_da_blkinfo	hdr;
	__be32			crc;	/* CRC of block */
	__be64			blkno;	/* first block of the buffer */
	__be64			lsn;	/* sequence number of last ग_लिखो */
	uuid_t			uuid;	/* fileप्रणाली we beदीर्घ to */
	__be64			owner;	/* inode that owns the block */
पूर्ण;

/*
 * This is the काष्ठाure of the root and पूर्णांकermediate nodes in the Btree.
 * The leaf nodes are defined above.
 *
 * Entries are not packed.
 *
 * Since we have duplicate keys, use a binary search but always follow
 * all match in the block, not just the first match found.
 */
#घोषणा XFS_DA_NODE_MAXDEPTH	5	/* max depth of Btree */

प्रकार काष्ठा xfs_da_node_hdr अणु
	काष्ठा xfs_da_blkinfo	info;	/* block type, links, etc. */
	__be16			__count; /* count of active entries */
	__be16			__level; /* level above leaves (leaf == 0) */
पूर्ण xfs_da_node_hdr_t;

काष्ठा xfs_da3_node_hdr अणु
	काष्ठा xfs_da3_blkinfo	info;	/* block type, links, etc. */
	__be16			__count; /* count of active entries */
	__be16			__level; /* level above leaves (leaf == 0) */
	__be32			__pad32;
पूर्ण;

#घोषणा XFS_DA3_NODE_CRC_OFF	(दुरत्व(काष्ठा xfs_da3_node_hdr, info.crc))

प्रकार काष्ठा xfs_da_node_entry अणु
	__be32	hashval;	/* hash value क्रम this descendant */
	__be32	beक्रमe;		/* Btree block beक्रमe this key */
पूर्ण xfs_da_node_entry_t;

प्रकार काष्ठा xfs_da_पूर्णांकnode अणु
	काष्ठा xfs_da_node_hdr	hdr;
	काष्ठा xfs_da_node_entry __btree[];
पूर्ण xfs_da_पूर्णांकnode_t;

काष्ठा xfs_da3_पूर्णांकnode अणु
	काष्ठा xfs_da3_node_hdr	hdr;
	काष्ठा xfs_da_node_entry __btree[];
पूर्ण;

/*
 * Directory version 2.
 *
 * There are 4 possible क्रमmats:
 *  - लघुक्रमm - embedded पूर्णांकo the inode
 *  - single block - data with embedded leaf at the end
 *  - multiple data blocks, single leaf+मुक्तindex block
 *  - data blocks, node and leaf blocks (btree), मुक्तindex blocks
 *
 * Note: many node blocks काष्ठाures and स्थिरants are shared with the attr
 * code and defined in xfs_da_btree.h.
 */

#घोषणा	XFS_सूची2_BLOCK_MAGIC	0x58443242	/* XD2B: single block dirs */
#घोषणा	XFS_सूची2_DATA_MAGIC	0x58443244	/* XD2D: multiblock dirs */
#घोषणा	XFS_सूची2_FREE_MAGIC	0x58443246	/* XD2F: मुक्त index blocks */

/*
 * Directory Version 3 With CRCs.
 *
 * The tree क्रमmats are the same as क्रम version 2 directories.  The dअगरference
 * is in the block header and dirent क्रमmats. In many हालs the v3 काष्ठाures
 * use v2 definitions as they are no dअगरferent and this makes code sharing much
 * easier.
 *
 * Also, the xfs_dir3_*() functions handle both v2 and v3 क्रमmats - अगर the
 * क्रमmat is v2 then they चयन to the existing v2 code, or the क्रमmat is v3
 * they implement the v3 functionality. This means the existing dir2 is a mix of
 * xfs_dir2/xfs_dir3 calls and functions. The xfs_dir3 functions are called
 * where there is a dअगरference in the क्रमmats, otherwise the code is unchanged.
 *
 * Where it is possible, the code decides what to करो based on the magic numbers
 * in the blocks rather than feature bits in the superblock. This means the code
 * is as independent of the बाह्यal XFS code as possible as करोesn't require
 * passing काष्ठा xfs_mount poपूर्णांकers पूर्णांकo places where it isn't really
 * necessary.
 *
 * Version 3 includes:
 *
 *	- a larger block header क्रम CRC and identअगरication purposes and so the
 *	offsets of all the काष्ठाures inside the blocks are dअगरferent.
 *
 *	- new magic numbers to be able to detect the v2/v3 types on the fly.
 */

#घोषणा	XFS_सूची3_BLOCK_MAGIC	0x58444233	/* XDB3: single block dirs */
#घोषणा	XFS_सूची3_DATA_MAGIC	0x58444433	/* XDD3: multiblock dirs */
#घोषणा	XFS_सूची3_FREE_MAGIC	0x58444633	/* XDF3: मुक्त index blocks */

/*
 * Dirents in version 3 directories have a file type field. Additions to this
 * list are an on-disk क्रमmat change, requiring feature bits. Valid values
 * are as follows:
 */
#घोषणा XFS_सूची3_FT_UNKNOWN		0
#घोषणा XFS_सूची3_FT_REG_खाता		1
#घोषणा XFS_सूची3_FT_सूची			2
#घोषणा XFS_सूची3_FT_CHRDEV		3
#घोषणा XFS_सूची3_FT_BLKDEV		4
#घोषणा XFS_सूची3_FT_FIFO		5
#घोषणा XFS_सूची3_FT_SOCK		6
#घोषणा XFS_सूची3_FT_SYMLINK		7
#घोषणा XFS_सूची3_FT_WHT			8

#घोषणा XFS_सूची3_FT_MAX			9

/*
 * Byte offset in data block and लघुक्रमm entry.
 */
प्रकार uपूर्णांक16_t	xfs_dir2_data_off_t;
#घोषणा	शून्यDATAOFF	0xffffU
प्रकार uपूर्णांक		xfs_dir2_data_aoff_t;	/* argument क्रमm */

/*
 * Offset in data space of a data entry.
 */
प्रकार uपूर्णांक32_t	xfs_dir2_dataptr_t;
#घोषणा	XFS_सूची2_MAX_DATAPTR	((xfs_dir2_dataptr_t)0xffffffff)
#घोषणा	XFS_सूची2_शून्य_DATAPTR	((xfs_dir2_dataptr_t)0)

/*
 * Byte offset in a directory.
 */
प्रकार	xfs_off_t	xfs_dir2_off_t;

/*
 * Directory block number (logical dirblk in file)
 */
प्रकार uपूर्णांक32_t	xfs_dir2_db_t;

#घोषणा XFS_INO32_SIZE	4
#घोषणा XFS_INO64_SIZE	8
#घोषणा XFS_INO64_DIFF	(XFS_INO64_SIZE - XFS_INO32_SIZE)

#घोषणा	XFS_सूची2_MAX_SHORT_INUM	((xfs_ino_t)0xffffffffULL)

/*
 * Directory layout when stored पूर्णांकernal to an inode.
 *
 * Small directories are packed as tightly as possible so as to fit पूर्णांकo the
 * literal area of the inode.  These "shortform" directories consist of a
 * single xfs_dir2_sf_hdr header followed by zero or more xfs_dir2_sf_entry
 * काष्ठाures.  Due the dअगरferent inode number storage size and the variable
 * length name field in the xfs_dir2_sf_entry all these काष्ठाure are
 * variable length, and the accessors in this file should be used to iterate
 * over them.
 */
प्रकार काष्ठा xfs_dir2_sf_hdr अणु
	uपूर्णांक8_t			count;		/* count of entries */
	uपूर्णांक8_t			i8count;	/* count of 8-byte inode #s */
	uपूर्णांक8_t			parent[8];	/* parent dir inode number */
पूर्ण __packed xfs_dir2_sf_hdr_t;

प्रकार काष्ठा xfs_dir2_sf_entry अणु
	__u8			namelen;	/* actual name length */
	__u8			offset[2];	/* saved offset */
	__u8			name[];		/* name, variable size */
	/*
	 * A single byte containing the file type field follows the inode
	 * number क्रम version 3 directory entries.
	 *
	 * A 64-bit or 32-bit inode number follows here, at a variable offset
	 * after the name.
	 */
पूर्ण __packed xfs_dir2_sf_entry_t;

अटल अंतरभूत पूर्णांक xfs_dir2_sf_hdr_size(पूर्णांक i8count)
अणु
	वापस माप(काष्ठा xfs_dir2_sf_hdr) -
		(i8count == 0) * XFS_INO64_DIFF;
पूर्ण

अटल अंतरभूत xfs_dir2_data_aoff_t
xfs_dir2_sf_get_offset(xfs_dir2_sf_entry_t *sfep)
अणु
	वापस get_unaligned_be16(sfep->offset);
पूर्ण

अटल अंतरभूत व्योम
xfs_dir2_sf_put_offset(xfs_dir2_sf_entry_t *sfep, xfs_dir2_data_aoff_t off)
अणु
	put_unaligned_be16(off, sfep->offset);
पूर्ण

अटल अंतरभूत काष्ठा xfs_dir2_sf_entry *
xfs_dir2_sf_firstentry(काष्ठा xfs_dir2_sf_hdr *hdr)
अणु
	वापस (काष्ठा xfs_dir2_sf_entry *)
		((अक्षर *)hdr + xfs_dir2_sf_hdr_size(hdr->i8count));
पूर्ण

/*
 * Data block काष्ठाures.
 *
 * A pure data block looks like the following drawing on disk:
 *
 *    +-------------------------------------------------+
 *    | xfs_dir2_data_hdr_t                             |
 *    +-------------------------------------------------+
 *    | xfs_dir2_data_entry_t OR xfs_dir2_data_unused_t |
 *    | xfs_dir2_data_entry_t OR xfs_dir2_data_unused_t |
 *    | xfs_dir2_data_entry_t OR xfs_dir2_data_unused_t |
 *    | ...                                             |
 *    +-------------------------------------------------+
 *    | unused space                                    |
 *    +-------------------------------------------------+
 *
 * As all the entries are variable size काष्ठाures the accessors below should
 * be used to iterate over them.
 *
 * In addition to the pure data blocks क्रम the data and node क्रमmats,
 * most काष्ठाures are also used क्रम the combined data/मुक्तspace "block"
 * क्रमmat below.
 */

#घोषणा	XFS_सूची2_DATA_ALIGN_LOG	3		/* i.e., 8 bytes */
#घोषणा	XFS_सूची2_DATA_ALIGN	(1 << XFS_सूची2_DATA_ALIGN_LOG)
#घोषणा	XFS_सूची2_DATA_FREE_TAG	0xffff
#घोषणा	XFS_सूची2_DATA_FD_COUNT	3

/*
 * Directory address space भागided पूर्णांकo sections,
 * spaces separated by 32GB.
 */
#घोषणा	XFS_सूची2_SPACE_SIZE	(1ULL << (32 + XFS_सूची2_DATA_ALIGN_LOG))
#घोषणा	XFS_सूची2_DATA_SPACE	0
#घोषणा	XFS_सूची2_DATA_OFFSET	(XFS_सूची2_DATA_SPACE * XFS_सूची2_SPACE_SIZE)

/*
 * Describe a मुक्त area in the data block.
 *
 * The मुक्तspace will be क्रमmatted as a xfs_dir2_data_unused_t.
 */
प्रकार काष्ठा xfs_dir2_data_मुक्त अणु
	__be16			offset;		/* start of मुक्तspace */
	__be16			length;		/* length of मुक्तspace */
पूर्ण xfs_dir2_data_मुक्त_t;

/*
 * Header क्रम the data blocks.
 *
 * The code knows that XFS_सूची2_DATA_FD_COUNT is 3.
 */
प्रकार काष्ठा xfs_dir2_data_hdr अणु
	__be32			magic;		/* XFS_सूची2_DATA_MAGIC or */
						/* XFS_सूची2_BLOCK_MAGIC */
	xfs_dir2_data_मुक्त_t	bestमुक्त[XFS_सूची2_DATA_FD_COUNT];
पूर्ण xfs_dir2_data_hdr_t;

/*
 * define a काष्ठाure क्रम all the verअगरication fields we are adding to the
 * directory block काष्ठाures. This will be used in several काष्ठाures.
 * The magic number must be the first entry to align with all the dir2
 * काष्ठाures so we determine how to decode them just by the magic number.
 */
काष्ठा xfs_dir3_blk_hdr अणु
	__be32			magic;	/* magic number */
	__be32			crc;	/* CRC of block */
	__be64			blkno;	/* first block of the buffer */
	__be64			lsn;	/* sequence number of last ग_लिखो */
	uuid_t			uuid;	/* fileप्रणाली we beदीर्घ to */
	__be64			owner;	/* inode that owns the block */
पूर्ण;

काष्ठा xfs_dir3_data_hdr अणु
	काष्ठा xfs_dir3_blk_hdr	hdr;
	xfs_dir2_data_मुक्त_t	best_मुक्त[XFS_सूची2_DATA_FD_COUNT];
	__be32			pad;	/* 64 bit alignment */
पूर्ण;

#घोषणा XFS_सूची3_DATA_CRC_OFF  दुरत्व(काष्ठा xfs_dir3_data_hdr, hdr.crc)

/*
 * Active entry in a data block.
 *
 * Aligned to 8 bytes.  After the variable length name field there is a
 * 2 byte tag field, which can be accessed using xfs_dir3_data_entry_tag_p.
 *
 * For dir3 काष्ठाures, there is file type field between the name and the tag.
 * This can only be manipulated by helper functions. It is packed hard against
 * the end of the name so any padding क्रम rounding is between the file type and
 * the tag.
 */
प्रकार काष्ठा xfs_dir2_data_entry अणु
	__be64			inumber;	/* inode number */
	__u8			namelen;	/* name length */
	__u8			name[];		/* name bytes, no null */
     /* __u8			filetype; */	/* type of inode we poपूर्णांक to */
     /*	__be16                  tag; */		/* starting offset of us */
पूर्ण xfs_dir2_data_entry_t;

/*
 * Unused entry in a data block.
 *
 * Aligned to 8 bytes.  Tag appears as the last 2 bytes and must be accessed
 * using xfs_dir2_data_unused_tag_p.
 */
प्रकार काष्ठा xfs_dir2_data_unused अणु
	__be16			मुक्तtag;	/* XFS_सूची2_DATA_FREE_TAG */
	__be16			length;		/* total मुक्त length */
						/* variable offset */
	__be16			tag;		/* starting offset of us */
पूर्ण xfs_dir2_data_unused_t;

/*
 * Poपूर्णांकer to a मुक्तspace's tag word.
 */
अटल अंतरभूत __be16 *
xfs_dir2_data_unused_tag_p(काष्ठा xfs_dir2_data_unused *dup)
अणु
	वापस (__be16 *)((अक्षर *)dup +
			be16_to_cpu(dup->length) - माप(__be16));
पूर्ण

/*
 * Leaf block काष्ठाures.
 *
 * A pure leaf block looks like the following drawing on disk:
 *
 *    +---------------------------+
 *    | xfs_dir2_leaf_hdr_t       |
 *    +---------------------------+
 *    | xfs_dir2_leaf_entry_t     |
 *    | xfs_dir2_leaf_entry_t     |
 *    | xfs_dir2_leaf_entry_t     |
 *    | xfs_dir2_leaf_entry_t     |
 *    | ...                       |
 *    +---------------------------+
 *    | xfs_dir2_data_off_t       |
 *    | xfs_dir2_data_off_t       |
 *    | xfs_dir2_data_off_t       |
 *    | ...                       |
 *    +---------------------------+
 *    | xfs_dir2_leaf_tail_t      |
 *    +---------------------------+
 *
 * The xfs_dir2_data_off_t members (bests) and tail are at the end of the block
 * क्रम single-leaf (magic = XFS_सूची2_LEAF1_MAGIC) blocks only, but not present
 * क्रम directories with separate leaf nodes and मुक्त space blocks
 * (magic = XFS_सूची2_LEAFN_MAGIC).
 *
 * As all the entries are variable size काष्ठाures the accessors below should
 * be used to iterate over them.
 */

/*
 * Offset of the leaf/node space.  First block in this space
 * is the btree root.
 */
#घोषणा	XFS_सूची2_LEAF_SPACE	1
#घोषणा	XFS_सूची2_LEAF_OFFSET	(XFS_सूची2_LEAF_SPACE * XFS_सूची2_SPACE_SIZE)

/*
 * Leaf block header.
 */
प्रकार काष्ठा xfs_dir2_leaf_hdr अणु
	xfs_da_blkinfo_t	info;		/* header क्रम da routines */
	__be16			count;		/* count of entries */
	__be16			stale;		/* count of stale entries */
पूर्ण xfs_dir2_leaf_hdr_t;

काष्ठा xfs_dir3_leaf_hdr अणु
	काष्ठा xfs_da3_blkinfo	info;		/* header क्रम da routines */
	__be16			count;		/* count of entries */
	__be16			stale;		/* count of stale entries */
	__be32			pad;		/* 64 bit alignment */
पूर्ण;

/*
 * Leaf block entry.
 */
प्रकार काष्ठा xfs_dir2_leaf_entry अणु
	__be32			hashval;	/* hash value of name */
	__be32			address;	/* address of data entry */
पूर्ण xfs_dir2_leaf_entry_t;

/*
 * Leaf block tail.
 */
प्रकार काष्ठा xfs_dir2_leaf_tail अणु
	__be32			bestcount;
पूर्ण xfs_dir2_leaf_tail_t;

/*
 * Leaf block.
 */
प्रकार काष्ठा xfs_dir2_leaf अणु
	xfs_dir2_leaf_hdr_t	hdr;			/* leaf header */
	xfs_dir2_leaf_entry_t	__ents[];		/* entries */
पूर्ण xfs_dir2_leaf_t;

काष्ठा xfs_dir3_leaf अणु
	काष्ठा xfs_dir3_leaf_hdr	hdr;		/* leaf header */
	काष्ठा xfs_dir2_leaf_entry	__ents[];	/* entries */
पूर्ण;

#घोषणा XFS_सूची3_LEAF_CRC_OFF  दुरत्व(काष्ठा xfs_dir3_leaf_hdr, info.crc)

/*
 * Get address of the bests array in the single-leaf block.
 */
अटल अंतरभूत __be16 *
xfs_dir2_leaf_bests_p(काष्ठा xfs_dir2_leaf_tail *ltp)
अणु
	वापस (__be16 *)ltp - be32_to_cpu(ltp->bestcount);
पूर्ण

/*
 * Free space block definitions क्रम the node क्रमmat.
 */

/*
 * Offset of the मुक्तspace index.
 */
#घोषणा	XFS_सूची2_FREE_SPACE	2
#घोषणा	XFS_सूची2_FREE_OFFSET	(XFS_सूची2_FREE_SPACE * XFS_सूची2_SPACE_SIZE)

प्रकार	काष्ठा xfs_dir2_मुक्त_hdr अणु
	__be32			magic;		/* XFS_सूची2_FREE_MAGIC */
	__be32			firstdb;	/* db of first entry */
	__be32			nvalid;		/* count of valid entries */
	__be32			nused;		/* count of used entries */
पूर्ण xfs_dir2_मुक्त_hdr_t;

प्रकार काष्ठा xfs_dir2_मुक्त अणु
	xfs_dir2_मुक्त_hdr_t	hdr;		/* block header */
	__be16			bests[];	/* best मुक्त counts */
						/* unused entries are -1 */
पूर्ण xfs_dir2_मुक्त_t;

काष्ठा xfs_dir3_मुक्त_hdr अणु
	काष्ठा xfs_dir3_blk_hdr	hdr;
	__be32			firstdb;	/* db of first entry */
	__be32			nvalid;		/* count of valid entries */
	__be32			nused;		/* count of used entries */
	__be32			pad;		/* 64 bit alignment */
पूर्ण;

काष्ठा xfs_dir3_मुक्त अणु
	काष्ठा xfs_dir3_मुक्त_hdr hdr;
	__be16			bests[];	/* best मुक्त counts */
						/* unused entries are -1 */
पूर्ण;

#घोषणा XFS_सूची3_FREE_CRC_OFF  दुरत्व(काष्ठा xfs_dir3_मुक्त, hdr.hdr.crc)

/*
 * Single block क्रमmat.
 *
 * The single block क्रमmat looks like the following drawing on disk:
 *
 *    +-------------------------------------------------+
 *    | xfs_dir2_data_hdr_t                             |
 *    +-------------------------------------------------+
 *    | xfs_dir2_data_entry_t OR xfs_dir2_data_unused_t |
 *    | xfs_dir2_data_entry_t OR xfs_dir2_data_unused_t |
 *    | xfs_dir2_data_entry_t OR xfs_dir2_data_unused_t :
 *    | ...                                             |
 *    +-------------------------------------------------+
 *    | unused space                                    |
 *    +-------------------------------------------------+
 *    | ...                                             |
 *    | xfs_dir2_leaf_entry_t                           |
 *    | xfs_dir2_leaf_entry_t                           |
 *    +-------------------------------------------------+
 *    | xfs_dir2_block_tail_t                           |
 *    +-------------------------------------------------+
 *
 * As all the entries are variable size काष्ठाures the accessors below should
 * be used to iterate over them.
 */

प्रकार काष्ठा xfs_dir2_block_tail अणु
	__be32		count;			/* count of leaf entries */
	__be32		stale;			/* count of stale lf entries */
पूर्ण xfs_dir2_block_tail_t;

/*
 * Poपूर्णांकer to the leaf entries embedded in a data block (1-block क्रमmat)
 */
अटल अंतरभूत काष्ठा xfs_dir2_leaf_entry *
xfs_dir2_block_leaf_p(काष्ठा xfs_dir2_block_tail *btp)
अणु
	वापस ((काष्ठा xfs_dir2_leaf_entry *)btp) - be32_to_cpu(btp->count);
पूर्ण


/*
 * Attribute storage layout
 *
 * Attribute lists are काष्ठाured around Btrees where all the data
 * elements are in the leaf nodes.  Attribute names are hashed पूर्णांकo an पूर्णांक,
 * then that पूर्णांक is used as the index पूर्णांकo the Btree.  Since the hashval
 * of an attribute name may not be unique, we may have duplicate keys.  The
 * पूर्णांकernal links in the Btree are logical block offsets पूर्णांकo the file.
 *
 * Struct leaf_entry's are packed from the top.  Name/values grow from the
 * bottom but are not packed.  The मुक्तmap contains run-length-encoded entries
 * क्रम the मुक्त bytes after the leaf_entry's, but only the N largest such,
 * smaller runs are dropped.  When the मुक्तmap करोesn't show enough space
 * क्रम an allocation, we compact the name/value area and try again.  If we
 * still करोn't have enough space, then we have to split the block.  The
 * name/value काष्ठाs (both local and remote versions) must be 32bit aligned.
 *
 * Since we have duplicate hash keys, क्रम each key that matches, compare
 * the actual name string.  The root and पूर्णांकermediate node search always
 * takes the first-in-the-block key match found, so we should only have
 * to work "forw"ard.  If none matches, जारी with the "forw"ard leaf
 * nodes until the hash key changes or the attribute name is found.
 *
 * We store the fact that an attribute is a ROOT/USER/SECURE attribute in
 * the leaf_entry.  The namespaces are independent only because we also look
 * at the namespace bit when we are looking क्रम a matching attribute name.
 *
 * We also store an "incomplete" bit in the leaf_entry.  It shows that an
 * attribute is in the middle of being created and should not be shown to
 * the user अगर we crash during the समय that the bit is set.  We clear the
 * bit when we have finished setting up the attribute.  We करो this because
 * we cannot create some large attributes inside a single transaction, and we
 * need some indication that we weren't finished अगर we crash in the middle.
 */
#घोषणा XFS_ATTR_LEAF_MAPSIZE	3	/* how many मुक्तspace slots */

/*
 * Entries are packed toward the top as tight as possible.
 */
काष्ठा xfs_attr_लघुक्रमm अणु
	काष्ठा xfs_attr_sf_hdr अणु	/* स्थिरant-काष्ठाure header block */
		__be16	totsize;	/* total bytes in लघुक्रमm list */
		__u8	count;	/* count of active entries */
		__u8	padding;
	पूर्ण hdr;
	काष्ठा xfs_attr_sf_entry अणु
		uपूर्णांक8_t namelen;	/* actual length of name (no शून्य) */
		uपूर्णांक8_t valuelen;	/* actual length of value (no शून्य) */
		uपूर्णांक8_t flags;	/* flags bits (see xfs_attr_leaf.h) */
		uपूर्णांक8_t nameval[];	/* name & value bytes concatenated */
	पूर्ण list[1];			/* variable sized array */
पूर्ण;

प्रकार काष्ठा xfs_attr_leaf_map अणु	/* RLE map of मुक्त bytes */
	__be16	base;			  /* base of मुक्त region */
	__be16	size;			  /* length of मुक्त region */
पूर्ण xfs_attr_leaf_map_t;

प्रकार काष्ठा xfs_attr_leaf_hdr अणु	/* स्थिरant-काष्ठाure header block */
	xfs_da_blkinfo_t info;		/* block type, links, etc. */
	__be16	count;			/* count of active leaf_entry's */
	__be16	usedbytes;		/* num bytes of names/values stored */
	__be16	firstused;		/* first used byte in name area */
	__u8	holes;			/* != 0 अगर blk needs compaction */
	__u8	pad1;
	xfs_attr_leaf_map_t मुक्तmap[XFS_ATTR_LEAF_MAPSIZE];
					/* N largest मुक्त regions */
पूर्ण xfs_attr_leaf_hdr_t;

प्रकार काष्ठा xfs_attr_leaf_entry अणु	/* sorted on key, not name */
	__be32	hashval;		/* hash value of name */
	__be16	nameidx;		/* index पूर्णांकo buffer of name/value */
	__u8	flags;			/* LOCAL/ROOT/SECURE/INCOMPLETE flag */
	__u8	pad2;			/* unused pad byte */
पूर्ण xfs_attr_leaf_entry_t;

प्रकार काष्ठा xfs_attr_leaf_name_local अणु
	__be16	valuelen;		/* number of bytes in value */
	__u8	namelen;		/* length of name bytes */
	__u8	nameval[1];		/* name/value bytes */
पूर्ण xfs_attr_leaf_name_local_t;

प्रकार काष्ठा xfs_attr_leaf_name_remote अणु
	__be32	valueblk;		/* block number of value bytes */
	__be32	valuelen;		/* number of bytes in value */
	__u8	namelen;		/* length of name bytes */
	__u8	name[1];		/* name bytes */
पूर्ण xfs_attr_leaf_name_remote_t;

प्रकार काष्ठा xfs_attr_leafblock अणु
	xfs_attr_leaf_hdr_t	hdr;	/* स्थिरant-काष्ठाure header block */
	xfs_attr_leaf_entry_t	entries[1];	/* sorted on key, not name */
	/*
	 * The rest of the block contains the following काष्ठाures after the
	 * leaf entries, growing from the bottom up. The variables are never
	 * referenced and definining them can actually make gcc optimize away
	 * accesses to the 'entries' array above index 0 so don't करो that.
	 *
	 * xfs_attr_leaf_name_local_t namelist;
	 * xfs_attr_leaf_name_remote_t valuelist;
	 */
पूर्ण xfs_attr_leafblock_t;

/*
 * CRC enabled leaf काष्ठाures. Called "version 3" काष्ठाures to match the
 * version number of the directory and dablk काष्ठाures क्रम this feature, and
 * attr2 is alपढ़ोy taken by the variable inode attribute विभाजन size feature.
 */
काष्ठा xfs_attr3_leaf_hdr अणु
	काष्ठा xfs_da3_blkinfo	info;
	__be16			count;
	__be16			usedbytes;
	__be16			firstused;
	__u8			holes;
	__u8			pad1;
	काष्ठा xfs_attr_leaf_map मुक्तmap[XFS_ATTR_LEAF_MAPSIZE];
	__be32			pad2;		/* 64 bit alignment */
पूर्ण;

#घोषणा XFS_ATTR3_LEAF_CRC_OFF	(दुरत्व(काष्ठा xfs_attr3_leaf_hdr, info.crc))

काष्ठा xfs_attr3_leafblock अणु
	काष्ठा xfs_attr3_leaf_hdr	hdr;
	काष्ठा xfs_attr_leaf_entry	entries[1];

	/*
	 * The rest of the block contains the following काष्ठाures after the
	 * leaf entries, growing from the bottom up. The variables are never
	 * referenced, the locations accessed purely from helper functions.
	 *
	 * काष्ठा xfs_attr_leaf_name_local
	 * काष्ठा xfs_attr_leaf_name_remote
	 */
पूर्ण;

/*
 * Special value to represent fs block size in the leaf header firstused field.
 * Only used when block size overflows the 2-bytes available on disk.
 */
#घोषणा XFS_ATTR3_LEAF_शून्यOFF	0

/*
 * Flags used in the leaf_entry[i].flags field.
 */
#घोषणा	XFS_ATTR_LOCAL_BIT	0	/* attr is stored locally */
#घोषणा	XFS_ATTR_ROOT_BIT	1	/* limit access to trusted attrs */
#घोषणा	XFS_ATTR_SECURE_BIT	2	/* limit access to secure attrs */
#घोषणा	XFS_ATTR_INCOMPLETE_BIT	7	/* attr in middle of create/delete */
#घोषणा XFS_ATTR_LOCAL		(1 << XFS_ATTR_LOCAL_BIT)
#घोषणा XFS_ATTR_ROOT		(1 << XFS_ATTR_ROOT_BIT)
#घोषणा XFS_ATTR_SECURE		(1 << XFS_ATTR_SECURE_BIT)
#घोषणा XFS_ATTR_INCOMPLETE	(1 << XFS_ATTR_INCOMPLETE_BIT)
#घोषणा XFS_ATTR_NSP_ONDISK_MASK	(XFS_ATTR_ROOT | XFS_ATTR_SECURE)

/*
 * Alignment क्रम namelist and valuelist entries (since they are mixed
 * there can be only one alignment value)
 */
#घोषणा	XFS_ATTR_LEAF_NAME_ALIGN	((uपूर्णांक)माप(xfs_dablk_t))

अटल अंतरभूत पूर्णांक
xfs_attr3_leaf_hdr_size(काष्ठा xfs_attr_leafblock *leafp)
अणु
	अगर (leafp->hdr.info.magic == cpu_to_be16(XFS_ATTR3_LEAF_MAGIC))
		वापस माप(काष्ठा xfs_attr3_leaf_hdr);
	वापस माप(काष्ठा xfs_attr_leaf_hdr);
पूर्ण

अटल अंतरभूत काष्ठा xfs_attr_leaf_entry *
xfs_attr3_leaf_entryp(xfs_attr_leafblock_t *leafp)
अणु
	अगर (leafp->hdr.info.magic == cpu_to_be16(XFS_ATTR3_LEAF_MAGIC))
		वापस &((काष्ठा xfs_attr3_leafblock *)leafp)->entries[0];
	वापस &leafp->entries[0];
पूर्ण

/*
 * Cast typed poपूर्णांकers क्रम "local" and "remote" name/value काष्ठाs.
 */
अटल अंतरभूत अक्षर *
xfs_attr3_leaf_name(xfs_attr_leafblock_t *leafp, पूर्णांक idx)
अणु
	काष्ठा xfs_attr_leaf_entry *entries = xfs_attr3_leaf_entryp(leafp);

	वापस &((अक्षर *)leafp)[be16_to_cpu(entries[idx].nameidx)];
पूर्ण

अटल अंतरभूत xfs_attr_leaf_name_remote_t *
xfs_attr3_leaf_name_remote(xfs_attr_leafblock_t *leafp, पूर्णांक idx)
अणु
	वापस (xfs_attr_leaf_name_remote_t *)xfs_attr3_leaf_name(leafp, idx);
पूर्ण

अटल अंतरभूत xfs_attr_leaf_name_local_t *
xfs_attr3_leaf_name_local(xfs_attr_leafblock_t *leafp, पूर्णांक idx)
अणु
	वापस (xfs_attr_leaf_name_local_t *)xfs_attr3_leaf_name(leafp, idx);
पूर्ण

/*
 * Calculate total bytes used (including trailing pad क्रम alignment) क्रम
 * a "local" name/value काष्ठाure, a "remote" name/value काष्ठाure, and
 * a poपूर्णांकer which might be either.
 */
अटल अंतरभूत पूर्णांक xfs_attr_leaf_entsize_remote(पूर्णांक nlen)
अणु
	वापस round_up(माप(काष्ठा xfs_attr_leaf_name_remote) - 1 +
			nlen, XFS_ATTR_LEAF_NAME_ALIGN);
पूर्ण

अटल अंतरभूत पूर्णांक xfs_attr_leaf_entsize_local(पूर्णांक nlen, पूर्णांक vlen)
अणु
	वापस round_up(माप(काष्ठा xfs_attr_leaf_name_local) - 1 +
			nlen + vlen, XFS_ATTR_LEAF_NAME_ALIGN);
पूर्ण

अटल अंतरभूत पूर्णांक xfs_attr_leaf_entsize_local_max(पूर्णांक bsize)
अणु
	वापस (((bsize) >> 1) + ((bsize) >> 2));
पूर्ण



/*
 * Remote attribute block क्रमmat definition
 *
 * There is one of these headers per fileप्रणाली block in a remote attribute.
 * This is करोne to ensure there is a 1:1 mapping between the attribute value
 * length and the number of blocks needed to store the attribute. This makes the
 * verअगरication of a buffer a little more complex, but greatly simplअगरies the
 * allocation, पढ़ोing and writing of these attributes as we करोn't have to guess
 * the number of blocks needed to store the attribute data.
 */
#घोषणा XFS_ATTR3_RMT_MAGIC	0x5841524d	/* XARM */

काष्ठा xfs_attr3_rmt_hdr अणु
	__be32	rm_magic;
	__be32	rm_offset;
	__be32	rm_bytes;
	__be32	rm_crc;
	uuid_t	rm_uuid;
	__be64	rm_owner;
	__be64	rm_blkno;
	__be64	rm_lsn;
पूर्ण;

#घोषणा XFS_ATTR3_RMT_CRC_OFF	दुरत्व(काष्ठा xfs_attr3_rmt_hdr, rm_crc)

#घोषणा XFS_ATTR3_RMT_BUF_SPACE(mp, bufsize)	\
	((bufsize) - (xfs_sb_version_hascrc(&(mp)->m_sb) ? \
			माप(काष्ठा xfs_attr3_rmt_hdr) : 0))

/* Number of bytes in a directory block. */
अटल अंतरभूत अचिन्हित पूर्णांक xfs_dir2_dirblock_bytes(काष्ठा xfs_sb *sbp)
अणु
	वापस 1 << (sbp->sb_blocklog + sbp->sb_dirblklog);
पूर्ण

xfs_failaddr_t xfs_da3_blkinfo_verअगरy(काष्ठा xfs_buf *bp,
				      काष्ठा xfs_da3_blkinfo *hdr3);

#पूर्ण_अगर /* __XFS_DA_FORMAT_H__ */
