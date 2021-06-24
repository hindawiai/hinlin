<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2003-2006, Cluster File Systems, Inc, info@clusterfs.com
 * Written by Alex Tomas <alex@clusterfs.com>
 */

#अगर_अघोषित _EXT4_EXTENTS
#घोषणा _EXT4_EXTENTS

#समावेश "ext4.h"

/*
 * With AGGRESSIVE_TEST defined, the capacity of index/leaf blocks
 * becomes very small, so index split, in-depth growing and
 * other hard changes happen much more often.
 * This is क्रम debug purposes only.
 */
#घोषणा AGGRESSIVE_TEST_

/*
 * With EXTENTS_STATS defined, the number of blocks and extents
 * are collected in the truncate path. They'll be shown at
 * umount समय.
 */
#घोषणा EXTENTS_STATS__

/*
 * If CHECK_BINSEARCH is defined, then the results of the binary search
 * will also be checked by linear search.
 */
#घोषणा CHECK_BINSEARCH__

/*
 * If EXT_STATS is defined then stats numbers are collected.
 * These number will be displayed at umount समय.
 */
#घोषणा EXT_STATS_


/*
 * ext4_inode has i_block array (60 bytes total).
 * The first 12 bytes store ext4_extent_header;
 * the reमुख्यder stores an array of ext4_extent.
 * For non-inode extent blocks, ext4_extent_tail
 * follows the array.
 */

/*
 * This is the extent tail on-disk काष्ठाure.
 * All other extent काष्ठाures are 12 bytes दीर्घ.  It turns out that
 * block_size % 12 >= 4 क्रम at least all घातers of 2 greater than 512, which
 * covers all valid ext4 block sizes.  Thereक्रमe, this tail काष्ठाure can be
 * crammed पूर्णांकo the end of the block without having to rebalance the tree.
 */
काष्ठा ext4_extent_tail अणु
	__le32	et_checksum;	/* crc32c(uuid+inum+extent_block) */
पूर्ण;

/*
 * This is the extent on-disk काष्ठाure.
 * It's used at the bottom of the tree.
 */
काष्ठा ext4_extent अणु
	__le32	ee_block;	/* first logical block extent covers */
	__le16	ee_len;		/* number of blocks covered by extent */
	__le16	ee_start_hi;	/* high 16 bits of physical block */
	__le32	ee_start_lo;	/* low 32 bits of physical block */
पूर्ण;

/*
 * This is index on-disk काष्ठाure.
 * It's used at all the levels except the bottom.
 */
काष्ठा ext4_extent_idx अणु
	__le32	ei_block;	/* index covers logical blocks from 'block' */
	__le32	ei_leaf_lo;	/* poपूर्णांकer to the physical block of the next *
				 * level. leaf or next index could be there */
	__le16	ei_leaf_hi;	/* high 16 bits of physical block */
	__u16	ei_unused;
पूर्ण;

/*
 * Each block (leaves and indexes), even inode-stored has header.
 */
काष्ठा ext4_extent_header अणु
	__le16	eh_magic;	/* probably will support dअगरferent क्रमmats */
	__le16	eh_entries;	/* number of valid entries */
	__le16	eh_max;		/* capacity of store in entries */
	__le16	eh_depth;	/* has tree real underlying blocks? */
	__le32	eh_generation;	/* generation of the tree */
पूर्ण;

#घोषणा EXT4_EXT_MAGIC		cpu_to_le16(0xf30a)
#घोषणा EXT4_MAX_EXTENT_DEPTH 5

#घोषणा EXT4_EXTENT_TAIL_OFFSET(hdr) \
	(माप(काष्ठा ext4_extent_header) + \
	 (माप(काष्ठा ext4_extent) * le16_to_cpu((hdr)->eh_max)))

अटल अंतरभूत काष्ठा ext4_extent_tail *
find_ext4_extent_tail(काष्ठा ext4_extent_header *eh)
अणु
	वापस (काष्ठा ext4_extent_tail *)(((व्योम *)eh) +
					   EXT4_EXTENT_TAIL_OFFSET(eh));
पूर्ण

/*
 * Array of ext4_ext_path contains path to some extent.
 * Creation/lookup routines use it क्रम traversal/splitting/etc.
 * Truncate uses it to simulate recursive walking.
 */
काष्ठा ext4_ext_path अणु
	ext4_fsblk_t			p_block;
	__u16				p_depth;
	__u16				p_maxdepth;
	काष्ठा ext4_extent		*p_ext;
	काष्ठा ext4_extent_idx		*p_idx;
	काष्ठा ext4_extent_header	*p_hdr;
	काष्ठा buffer_head		*p_bh;
पूर्ण;

/*
 * Used to record a portion of a cluster found at the beginning or end
 * of an extent जबतक traversing the extent tree during space removal.
 * A partial cluster may be हटाओd अगर it करोes not contain blocks shared
 * with extents that aren't being deleted (toमुक्त state).  Otherwise,
 * it cannot be हटाओd (noमुक्त state).
 */
काष्ठा partial_cluster अणु
	ext4_fsblk_t pclu;  /* physical cluster number */
	ext4_lblk_t lblk;   /* logical block number within logical cluster */
	क्रमागत अणुinitial, toमुक्त, noमुक्तपूर्ण state;
पूर्ण;

/*
 * काष्ठाure क्रम बाह्यal API
 */

/*
 * EXT_INIT_MAX_LEN is the maximum number of blocks we can have in an
 * initialized extent. This is 2^15 and not (2^16 - 1), since we use the
 * MSB of ee_len field in the extent dataकाष्ठाure to signअगरy अगर this
 * particular extent is an initialized extent or an unwritten (i.e.
 * pपुनः_स्मृतिated).
 * EXT_UNWRITTEN_MAX_LEN is the maximum number of blocks we can have in an
 * unwritten extent.
 * If ee_len is <= 0x8000, it is an initialized extent. Otherwise, it is an
 * unwritten one. In other words, अगर MSB of ee_len is set, it is an
 * unwritten extent with only one special scenario when ee_len = 0x8000.
 * In this हाल we can not have an unwritten extent of zero length and
 * thus we make it as a special हाल of initialized extent with 0x8000 length.
 * This way we get better extent-to-group alignment क्रम initialized extents.
 * Hence, the maximum number of blocks we can have in an *initialized*
 * extent is 2^15 (32768) and in an *unwritten* extent is 2^15-1 (32767).
 */
#घोषणा EXT_INIT_MAX_LEN	(1UL << 15)
#घोषणा EXT_UNWRITTEN_MAX_LEN	(EXT_INIT_MAX_LEN - 1)


#घोषणा EXT_FIRST_EXTENT(__hdr__) \
	((काष्ठा ext4_extent *) (((अक्षर *) (__hdr__)) +		\
				 माप(काष्ठा ext4_extent_header)))
#घोषणा EXT_FIRST_INDEX(__hdr__) \
	((काष्ठा ext4_extent_idx *) (((अक्षर *) (__hdr__)) +	\
				     माप(काष्ठा ext4_extent_header)))
#घोषणा EXT_HAS_FREE_INDEX(__path__) \
	(le16_to_cpu((__path__)->p_hdr->eh_entries) \
				     < le16_to_cpu((__path__)->p_hdr->eh_max))
#घोषणा EXT_LAST_EXTENT(__hdr__) \
	(EXT_FIRST_EXTENT((__hdr__)) + le16_to_cpu((__hdr__)->eh_entries) - 1)
#घोषणा EXT_LAST_INDEX(__hdr__) \
	(EXT_FIRST_INDEX((__hdr__)) + le16_to_cpu((__hdr__)->eh_entries) - 1)
#घोषणा EXT_MAX_EXTENT(__hdr__)	\
	((le16_to_cpu((__hdr__)->eh_max)) ? \
	((EXT_FIRST_EXTENT((__hdr__)) + le16_to_cpu((__hdr__)->eh_max) - 1)) \
					: 0)
#घोषणा EXT_MAX_INDEX(__hdr__) \
	((le16_to_cpu((__hdr__)->eh_max)) ? \
	((EXT_FIRST_INDEX((__hdr__)) + le16_to_cpu((__hdr__)->eh_max) - 1)) : 0)

अटल अंतरभूत काष्ठा ext4_extent_header *ext_inode_hdr(काष्ठा inode *inode)
अणु
	वापस (काष्ठा ext4_extent_header *) EXT4_I(inode)->i_data;
पूर्ण

अटल अंतरभूत काष्ठा ext4_extent_header *ext_block_hdr(काष्ठा buffer_head *bh)
अणु
	वापस (काष्ठा ext4_extent_header *) bh->b_data;
पूर्ण

अटल अंतरभूत अचिन्हित लघु ext_depth(काष्ठा inode *inode)
अणु
	वापस le16_to_cpu(ext_inode_hdr(inode)->eh_depth);
पूर्ण

अटल अंतरभूत व्योम ext4_ext_mark_unwritten(काष्ठा ext4_extent *ext)
अणु
	/* We can not have an unwritten extent of zero length! */
	BUG_ON((le16_to_cpu(ext->ee_len) & ~EXT_INIT_MAX_LEN) == 0);
	ext->ee_len |= cpu_to_le16(EXT_INIT_MAX_LEN);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_ext_is_unwritten(काष्ठा ext4_extent *ext)
अणु
	/* Extent with ee_len of 0x8000 is treated as an initialized extent */
	वापस (le16_to_cpu(ext->ee_len) > EXT_INIT_MAX_LEN);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_ext_get_actual_len(काष्ठा ext4_extent *ext)
अणु
	वापस (le16_to_cpu(ext->ee_len) <= EXT_INIT_MAX_LEN ?
		le16_to_cpu(ext->ee_len) :
		(le16_to_cpu(ext->ee_len) - EXT_INIT_MAX_LEN));
पूर्ण

अटल अंतरभूत व्योम ext4_ext_mark_initialized(काष्ठा ext4_extent *ext)
अणु
	ext->ee_len = cpu_to_le16(ext4_ext_get_actual_len(ext));
पूर्ण

/*
 * ext4_ext_pblock:
 * combine low and high parts of physical block number पूर्णांकo ext4_fsblk_t
 */
अटल अंतरभूत ext4_fsblk_t ext4_ext_pblock(काष्ठा ext4_extent *ex)
अणु
	ext4_fsblk_t block;

	block = le32_to_cpu(ex->ee_start_lo);
	block |= ((ext4_fsblk_t) le16_to_cpu(ex->ee_start_hi) << 31) << 1;
	वापस block;
पूर्ण

/*
 * ext4_idx_pblock:
 * combine low and high parts of a leaf physical block number पूर्णांकo ext4_fsblk_t
 */
अटल अंतरभूत ext4_fsblk_t ext4_idx_pblock(काष्ठा ext4_extent_idx *ix)
अणु
	ext4_fsblk_t block;

	block = le32_to_cpu(ix->ei_leaf_lo);
	block |= ((ext4_fsblk_t) le16_to_cpu(ix->ei_leaf_hi) << 31) << 1;
	वापस block;
पूर्ण

/*
 * ext4_ext_store_pblock:
 * stores a large physical block number पूर्णांकo an extent काष्ठा,
 * अवरोधing it पूर्णांकo parts
 */
अटल अंतरभूत व्योम ext4_ext_store_pblock(काष्ठा ext4_extent *ex,
					 ext4_fsblk_t pb)
अणु
	ex->ee_start_lo = cpu_to_le32((अचिन्हित दीर्घ) (pb & 0xffffffff));
	ex->ee_start_hi = cpu_to_le16((अचिन्हित दीर्घ) ((pb >> 31) >> 1) &
				      0xffff);
पूर्ण

/*
 * ext4_idx_store_pblock:
 * stores a large physical block number पूर्णांकo an index काष्ठा,
 * अवरोधing it पूर्णांकo parts
 */
अटल अंतरभूत व्योम ext4_idx_store_pblock(काष्ठा ext4_extent_idx *ix,
					 ext4_fsblk_t pb)
अणु
	ix->ei_leaf_lo = cpu_to_le32((अचिन्हित दीर्घ) (pb & 0xffffffff));
	ix->ei_leaf_hi = cpu_to_le16((अचिन्हित दीर्घ) ((pb >> 31) >> 1) &
				     0xffff);
पूर्ण

#पूर्ण_अगर /* _EXT4_EXTENTS */

