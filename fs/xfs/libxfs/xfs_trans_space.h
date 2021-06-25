<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_TRANS_SPACE_H__
#घोषणा __XFS_TRANS_SPACE_H__

/*
 * Components of space reservations.
 */

/* Worst हाल number of rmaps that can be held in a block. */
#घोषणा XFS_MAX_CONTIG_RMAPS_PER_BLOCK(mp)    \
		(((mp)->m_rmap_mxr[0]) - ((mp)->m_rmap_mnr[0]))

/* Adding one rmap could split every level up to the top of the tree. */
#घोषणा XFS_RMAPADD_SPACE_RES(mp) ((mp)->m_rmap_maxlevels)

/* Blocks we might need to add "b" rmaps to a tree. */
#घोषणा XFS_NRMAPADD_SPACE_RES(mp, b)\
	(((b + XFS_MAX_CONTIG_RMAPS_PER_BLOCK(mp) - 1) / \
	  XFS_MAX_CONTIG_RMAPS_PER_BLOCK(mp)) * \
	  XFS_RMAPADD_SPACE_RES(mp))

#घोषणा XFS_MAX_CONTIG_EXTENTS_PER_BLOCK(mp)    \
		(((mp)->m_alloc_mxr[0]) - ((mp)->m_alloc_mnr[0]))
#घोषणा	XFS_EXTENTADD_SPACE_RES(mp,w)	(XFS_BM_MAXLEVELS(mp,w) - 1)
#घोषणा XFS_NEXTENTADD_SPACE_RES(mp,b,w)\
	(((b + XFS_MAX_CONTIG_EXTENTS_PER_BLOCK(mp) - 1) / \
	  XFS_MAX_CONTIG_EXTENTS_PER_BLOCK(mp)) * \
	  XFS_EXTENTADD_SPACE_RES(mp,w))

/* Blocks we might need to add "b" mappings & rmappings to a file. */
#घोषणा XFS_SWAP_RMAP_SPACE_RES(mp,b,w)\
	(XFS_NEXTENTADD_SPACE_RES((mp), (b), (w)) + \
	 XFS_NRMAPADD_SPACE_RES((mp), (b)))

#घोषणा	XFS_DAENTER_1B(mp,w)	\
	((w) == XFS_DATA_FORK ? (mp)->m_dir_geo->fsbcount : 1)
#घोषणा	XFS_DAENTER_DBS(mp,w)	\
	(XFS_DA_NODE_MAXDEPTH + (((w) == XFS_DATA_FORK) ? 2 : 0))
#घोषणा	XFS_DAENTER_BLOCKS(mp,w)	\
	(XFS_DAENTER_1B(mp,w) * XFS_DAENTER_DBS(mp,w))
#घोषणा	XFS_DAENTER_BMAP1B(mp,w)	\
	XFS_NEXTENTADD_SPACE_RES(mp, XFS_DAENTER_1B(mp, w), w)
#घोषणा	XFS_DAENTER_BMAPS(mp,w)		\
	(XFS_DAENTER_DBS(mp,w) * XFS_DAENTER_BMAP1B(mp,w))
#घोषणा	XFS_DAENTER_SPACE_RES(mp,w)	\
	(XFS_DAENTER_BLOCKS(mp,w) + XFS_DAENTER_BMAPS(mp,w))
#घोषणा	XFS_DAREMOVE_SPACE_RES(mp,w)	XFS_DAENTER_BMAPS(mp,w)
#घोषणा	XFS_सूचीENTER_MAX_SPLIT(mp,nl)	1
#घोषणा	XFS_सूचीENTER_SPACE_RES(mp,nl)	\
	(XFS_DAENTER_SPACE_RES(mp, XFS_DATA_FORK) * \
	 XFS_सूचीENTER_MAX_SPLIT(mp,nl))
#घोषणा	XFS_सूचीREMOVE_SPACE_RES(mp)	\
	XFS_DAREMOVE_SPACE_RES(mp, XFS_DATA_FORK)
#घोषणा	XFS_IALLOC_SPACE_RES(mp)	\
	(M_IGEO(mp)->ialloc_blks + \
	 ((xfs_sb_version_hasfinobt(&mp->m_sb) ? 2 : 1) * \
	  M_IGEO(mp)->inobt_maxlevels))

/*
 * Space reservation values क्रम various transactions.
 */
#घोषणा	XFS_ADDAFORK_SPACE_RES(mp)	\
	((mp)->m_dir_geo->fsbcount + XFS_DAENTER_BMAP1B(mp, XFS_DATA_FORK))
#घोषणा	XFS_ATTRRM_SPACE_RES(mp)	\
	XFS_DAREMOVE_SPACE_RES(mp, XFS_ATTR_FORK)
/* This macro is not used - see अंतरभूत code in xfs_attr_set */
#घोषणा	XFS_ATTRSET_SPACE_RES(mp, v)	\
	(XFS_DAENTER_SPACE_RES(mp, XFS_ATTR_FORK) + XFS_B_TO_FSB(mp, v))
#घोषणा	XFS_CREATE_SPACE_RES(mp,nl)	\
	(XFS_IALLOC_SPACE_RES(mp) + XFS_सूचीENTER_SPACE_RES(mp,nl))
#घोषणा	XFS_DIOSTRAT_SPACE_RES(mp, v)	\
	(XFS_EXTENTADD_SPACE_RES(mp, XFS_DATA_FORK) + (v))
#घोषणा	XFS_GROWFS_SPACE_RES(mp)	\
	(2 * (mp)->m_ag_maxlevels)
#घोषणा	XFS_GROWFSRT_SPACE_RES(mp,b)	\
	((b) + XFS_EXTENTADD_SPACE_RES(mp, XFS_DATA_FORK))
#घोषणा	XFS_LINK_SPACE_RES(mp,nl)	\
	XFS_सूचीENTER_SPACE_RES(mp,nl)
#घोषणा	XFS_MKसूची_SPACE_RES(mp,nl)	\
	(XFS_IALLOC_SPACE_RES(mp) + XFS_सूचीENTER_SPACE_RES(mp,nl))
#घोषणा	XFS_QM_DQALLOC_SPACE_RES(mp)	\
	(XFS_EXTENTADD_SPACE_RES(mp, XFS_DATA_FORK) + \
	 XFS_DQUOT_CLUSTER_SIZE_FSB)
#घोषणा	XFS_QM_QINOCREATE_SPACE_RES(mp)	\
	XFS_IALLOC_SPACE_RES(mp)
#घोषणा	XFS_REMOVE_SPACE_RES(mp)	\
	XFS_सूचीREMOVE_SPACE_RES(mp)
#घोषणा	XFS_RENAME_SPACE_RES(mp,nl)	\
	(XFS_सूचीREMOVE_SPACE_RES(mp) + XFS_सूचीENTER_SPACE_RES(mp,nl))
#घोषणा	XFS_SYMLINK_SPACE_RES(mp,nl,b)	\
	(XFS_IALLOC_SPACE_RES(mp) + XFS_सूचीENTER_SPACE_RES(mp,nl) + (b))
#घोषणा XFS_IFREE_SPACE_RES(mp)		\
	(xfs_sb_version_hasfinobt(&mp->m_sb) ? \
			M_IGEO(mp)->inobt_maxlevels : 0)


#पूर्ण_अगर	/* __XFS_TRANS_SPACE_H__ */
