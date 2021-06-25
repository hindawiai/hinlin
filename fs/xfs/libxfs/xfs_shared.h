<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_SHARED_H__
#घोषणा __XFS_SHARED_H__

/*
 * Definitions shared between kernel and userspace that करोn't fit पूर्णांकo any other
 * header file that is shared with userspace.
 */
काष्ठा xfs_अगरork;
काष्ठा xfs_buf;
काष्ठा xfs_buf_ops;
काष्ठा xfs_mount;
काष्ठा xfs_trans;
काष्ठा xfs_inode;

/*
 * Buffer verअगरier operations are widely used, including userspace tools
 */
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_agf_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_agi_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_agf_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_agfl_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_bnobt_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_cntbt_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_rmapbt_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_refcountbt_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_attr3_leaf_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_attr3_rmt_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_bmbt_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_da3_node_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_dquot_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_symlink_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_agi_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_inobt_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_finobt_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_inode_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_inode_buf_ra_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_dquot_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_dquot_buf_ra_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_sb_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_sb_quiet_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_symlink_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_rtbuf_ops;

/* log size calculation functions */
पूर्णांक	xfs_log_calc_unit_res(काष्ठा xfs_mount *mp, पूर्णांक unit_bytes);
पूर्णांक	xfs_log_calc_minimum_size(काष्ठा xfs_mount *);

काष्ठा xfs_trans_res;
व्योम	xfs_log_get_max_trans_res(काष्ठा xfs_mount *mp,
				  काष्ठा xfs_trans_res *max_resp);

/*
 * Values क्रम t_flags.
 */
#घोषणा	XFS_TRANS_सूचीTY		0x01	/* something needs to be logged */
#घोषणा	XFS_TRANS_SB_सूचीTY	0x02	/* superblock is modअगरied */
#घोषणा	XFS_TRANS_PERM_LOG_RES	0x04	/* xact took a permanent log res */
#घोषणा	XFS_TRANS_SYNC		0x08	/* make commit synchronous */
#घोषणा XFS_TRANS_RESERVE	0x20    /* OK to use reserved data blocks */
#घोषणा XFS_TRANS_NO_WRITECOUNT 0x40	/* करो not elevate SB ग_लिखोcount */
#घोषणा XFS_TRANS_RES_FDBLKS	0x80	/* reserve newly मुक्तd blocks */
/*
 * LOWMODE is used by the allocator to activate the lowspace algorithm - when
 * मुक्त space is running low the extent allocator may choose to allocate an
 * extent from an AG without leaving sufficient space क्रम a btree split when
 * inserting the new extent. In this हाल the allocator will enable the
 * lowspace algorithm which is supposed to allow further allocations (such as
 * btree splits and newroots) to allocate from sequential AGs. In order to
 * aव्योम locking AGs out of order the lowspace algorithm will start searching
 * क्रम मुक्त space from AG 0. If the correct transaction reservations have been
 * made then this algorithm will eventually find all the space it needs.
 */
#घोषणा XFS_TRANS_LOWMODE	0x100	/* allocate in low space mode */

/*
 * Field values क्रम xfs_trans_mod_sb.
 */
#घोषणा	XFS_TRANS_SB_ICOUNT		0x00000001
#घोषणा	XFS_TRANS_SB_IFREE		0x00000002
#घोषणा	XFS_TRANS_SB_FDBLOCKS		0x00000004
#घोषणा	XFS_TRANS_SB_RES_FDBLOCKS	0x00000008
#घोषणा	XFS_TRANS_SB_FREXTENTS		0x00000010
#घोषणा	XFS_TRANS_SB_RES_FREXTENTS	0x00000020
#घोषणा	XFS_TRANS_SB_DBLOCKS		0x00000040
#घोषणा	XFS_TRANS_SB_AGCOUNT		0x00000080
#घोषणा	XFS_TRANS_SB_IMAXPCT		0x00000100
#घोषणा	XFS_TRANS_SB_REXTSIZE		0x00000200
#घोषणा	XFS_TRANS_SB_RBMBLOCKS		0x00000400
#घोषणा	XFS_TRANS_SB_RBLOCKS		0x00000800
#घोषणा	XFS_TRANS_SB_REXTENTS		0x00001000
#घोषणा	XFS_TRANS_SB_REXTSLOG		0x00002000

/*
 * Here we centralize the specअगरication of XFS meta-data buffer reference count
 * values.  This determines how hard the buffer cache tries to hold onto the
 * buffer.
 */
#घोषणा	XFS_AGF_REF		4
#घोषणा	XFS_AGI_REF		4
#घोषणा	XFS_AGFL_REF		3
#घोषणा	XFS_INO_BTREE_REF	3
#घोषणा	XFS_ALLOC_BTREE_REF	2
#घोषणा	XFS_BMAP_BTREE_REF	2
#घोषणा	XFS_RMAP_BTREE_REF	2
#घोषणा	XFS_सूची_BTREE_REF	2
#घोषणा	XFS_INO_REF		2
#घोषणा	XFS_ATTR_BTREE_REF	1
#घोषणा	XFS_DQUOT_REF		1
#घोषणा	XFS_REFC_BTREE_REF	1
#घोषणा	XFS_SSB_REF		0

/*
 * Flags क्रम xfs_trans_ichgसमय().
 */
#घोषणा	XFS_ICHGTIME_MOD	0x1	/* data विभाजन modअगरication बारtamp */
#घोषणा	XFS_ICHGTIME_CHG	0x2	/* inode field change बारtamp */
#घोषणा	XFS_ICHGTIME_CREATE	0x4	/* inode create बारtamp */


/*
 * Symlink decoding/encoding functions
 */
पूर्णांक xfs_symlink_blocks(काष्ठा xfs_mount *mp, पूर्णांक pathlen);
पूर्णांक xfs_symlink_hdr_set(काष्ठा xfs_mount *mp, xfs_ino_t ino, uपूर्णांक32_t offset,
			uपूर्णांक32_t size, काष्ठा xfs_buf *bp);
bool xfs_symlink_hdr_ok(xfs_ino_t ino, uपूर्णांक32_t offset,
			uपूर्णांक32_t size, काष्ठा xfs_buf *bp);
व्योम xfs_symlink_local_to_remote(काष्ठा xfs_trans *tp, काष्ठा xfs_buf *bp,
				 काष्ठा xfs_inode *ip, काष्ठा xfs_अगरork *अगरp);
xfs_failaddr_t xfs_symlink_लघुक्रमm_verअगरy(काष्ठा xfs_inode *ip);

/* Computed inode geometry क्रम the fileप्रणाली. */
काष्ठा xfs_ino_geometry अणु
	/* Maximum inode count in this fileप्रणाली. */
	uपूर्णांक64_t	maxicount;

	/* Actual inode cluster buffer size, in bytes. */
	अचिन्हित पूर्णांक	inode_cluster_size;

	/*
	 * Desired inode cluster buffer size, in bytes.  This value is not
	 * rounded up to at least one fileप्रणाली block, which is necessary क्रम
	 * the sole purpose of validating sb_spino_align.  Runसमय code must
	 * only ever use inode_cluster_size.
	 */
	अचिन्हित पूर्णांक	inode_cluster_size_raw;

	/* Inode cluster sizes, adjusted to be at least 1 fsb. */
	अचिन्हित पूर्णांक	inodes_per_cluster;
	अचिन्हित पूर्णांक	blocks_per_cluster;

	/* Inode cluster alignment. */
	अचिन्हित पूर्णांक	cluster_align;
	अचिन्हित पूर्णांक	cluster_align_inodes;
	अचिन्हित पूर्णांक	inoalign_mask;	/* mask sb_inoalignmt अगर used */

	अचिन्हित पूर्णांक	inobt_mxr[2]; /* max inobt btree records */
	अचिन्हित पूर्णांक	inobt_mnr[2]; /* min inobt btree records */
	अचिन्हित पूर्णांक	inobt_maxlevels; /* max inobt btree levels. */

	/* Size of inode allocations under normal operation. */
	अचिन्हित पूर्णांक	ialloc_inos;
	अचिन्हित पूर्णांक	ialloc_blks;

	/* Minimum inode blocks क्रम a sparse allocation. */
	अचिन्हित पूर्णांक	ialloc_min_blks;

	/* stripe unit inode alignment */
	अचिन्हित पूर्णांक	ialloc_align;

	अचिन्हित पूर्णांक	agino_log;	/* #bits क्रम agino in inum */

	/* precomputed शेष inode attribute विभाजन offset */
	अचिन्हित पूर्णांक	attr_विभाजन_offset;

	/* precomputed value क्रम di_flags2 */
	uपूर्णांक64_t	new_dअगरlags2;

पूर्ण;

#पूर्ण_अगर /* __XFS_SHARED_H__ */
