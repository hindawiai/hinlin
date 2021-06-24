<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_IALLOC_H__
#घोषणा	__XFS_IALLOC_H__

काष्ठा xfs_buf;
काष्ठा xfs_dinode;
काष्ठा xfs_imap;
काष्ठा xfs_mount;
काष्ठा xfs_trans;
काष्ठा xfs_btree_cur;

/* Move inodes in clusters of this size */
#घोषणा	XFS_INODE_BIG_CLUSTER_SIZE	8192

काष्ठा xfs_icluster अणु
	bool		deleted;	/* record is deleted */
	xfs_ino_t	first_ino;	/* first inode number */
	uपूर्णांक64_t	alloc;		/* inode phys. allocation biपंचांगap क्रम
					 * sparse chunks */
पूर्ण;

/*
 * Make an inode poपूर्णांकer out of the buffer/offset.
 */
अटल अंतरभूत काष्ठा xfs_dinode *
xfs_make_iptr(काष्ठा xfs_mount *mp, काष्ठा xfs_buf *b, पूर्णांक o)
अणु
	वापस xfs_buf_offset(b, o << (mp)->m_sb.sb_inodelog);
पूर्ण

/*
 * Allocate an inode on disk.
 * Mode is used to tell whether the new inode will need space, and whether
 * it is a directory.
 *
 * There are two phases to inode allocation: selecting an AG and ensuring
 * that it contains मुक्त inodes, followed by allocating one of the मुक्त
 * inodes. xfs_dialloc_select_ag() करोes the क्रमmer and वापसs a locked AGI
 * to the caller, ensuring that followup call to xfs_dialloc_ag() will
 * have मुक्त inodes to allocate from. xfs_dialloc_ag() will वापस the inode
 * number of the मुक्त inode we allocated.
 */
पूर्णांक					/* error */
xfs_dialloc_select_ag(
	काष्ठा xfs_trans **tpp,		/* द्विगुन poपूर्णांकer of transaction */
	xfs_ino_t	parent,		/* parent inode (directory) */
	umode_t		mode,		/* mode bits क्रम new inode */
	काष्ठा xfs_buf	**IO_agbp);

पूर्णांक
xfs_dialloc_ag(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp,
	xfs_ino_t		parent,
	xfs_ino_t		*inop);

/*
 * Free disk inode.  Carefully aव्योमs touching the incore inode, all
 * manipulations incore are the caller's responsibility.
 * The on-disk inode is not changed by this operation, only the
 * btree (मुक्त inode mask) is changed.
 */
पूर्णांक					/* error */
xfs_dअगरree(
	काष्ठा xfs_trans *tp,		/* transaction poपूर्णांकer */
	xfs_ino_t	inode,		/* inode to be मुक्तd */
	काष्ठा xfs_icluster *अगरree);	/* cluster info अगर deleted */

/*
 * Return the location of the inode in imap, क्रम mapping it पूर्णांकo a buffer.
 */
पूर्णांक
xfs_imap(
	काष्ठा xfs_mount *mp,		/* file प्रणाली mount काष्ठाure */
	काष्ठा xfs_trans *tp,		/* transaction poपूर्णांकer */
	xfs_ino_t	ino,		/* inode to locate */
	काष्ठा xfs_imap	*imap,		/* location map काष्ठाure */
	uपूर्णांक		flags);		/* flags क्रम inode btree lookup */

/*
 * Log specअगरied fields क्रम the ag hdr (inode section)
 */
व्योम
xfs_ialloc_log_agi(
	काष्ठा xfs_trans *tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_buf	*bp,		/* allocation group header buffer */
	पूर्णांक		fields);	/* biपंचांगask of fields to log */

/*
 * Read in the allocation group header (inode allocation section)
 */
पूर्णांक					/* error */
xfs_ialloc_पढ़ो_agi(
	काष्ठा xfs_mount *mp,		/* file प्रणाली mount काष्ठाure */
	काष्ठा xfs_trans *tp,		/* transaction poपूर्णांकer */
	xfs_agnumber_t	agno,		/* allocation group number */
	काष्ठा xfs_buf	**bpp);		/* allocation group hdr buf */

/*
 * Read in the allocation group header to initialise the per-ag data
 * in the mount काष्ठाure
 */
पूर्णांक
xfs_ialloc_pagi_init(
	काष्ठा xfs_mount *mp,		/* file प्रणाली mount काष्ठाure */
	काष्ठा xfs_trans *tp,		/* transaction poपूर्णांकer */
        xfs_agnumber_t  agno);		/* allocation group number */

/*
 * Lookup a record by ino in the btree given by cur.
 */
पूर्णांक xfs_inobt_lookup(काष्ठा xfs_btree_cur *cur, xfs_agino_t ino,
		xfs_lookup_t dir, पूर्णांक *stat);

/*
 * Get the data from the poपूर्णांकed-to record.
 */
पूर्णांक xfs_inobt_get_rec(काष्ठा xfs_btree_cur *cur,
		xfs_inobt_rec_incore_t *rec, पूर्णांक *stat);

/*
 * Inode chunk initialisation routine
 */
पूर्णांक xfs_ialloc_inode_init(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
			  काष्ठा list_head *buffer_list, पूर्णांक icount,
			  xfs_agnumber_t agno, xfs_agblock_t agbno,
			  xfs_agblock_t length, अचिन्हित पूर्णांक gen);

पूर्णांक xfs_पढ़ो_agi(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		xfs_agnumber_t agno, काष्ठा xfs_buf **bpp);

जोड़ xfs_btree_rec;
व्योम xfs_inobt_btrec_to_irec(काष्ठा xfs_mount *mp, जोड़ xfs_btree_rec *rec,
		काष्ठा xfs_inobt_rec_incore *irec);
पूर्णांक xfs_ialloc_has_inodes_at_extent(काष्ठा xfs_btree_cur *cur,
		xfs_agblock_t bno, xfs_extlen_t len, bool *exists);
पूर्णांक xfs_ialloc_has_inode_record(काष्ठा xfs_btree_cur *cur, xfs_agino_t low,
		xfs_agino_t high, bool *exists);
पूर्णांक xfs_ialloc_count_inodes(काष्ठा xfs_btree_cur *cur, xfs_agino_t *count,
		xfs_agino_t *मुक्तcount);
पूर्णांक xfs_inobt_insert_rec(काष्ठा xfs_btree_cur *cur, uपूर्णांक16_t holemask,
		uपूर्णांक8_t count, पूर्णांक32_t मुक्तcount, xfs_inoमुक्त_t मुक्त,
		पूर्णांक *stat);

पूर्णांक xfs_ialloc_cluster_alignment(काष्ठा xfs_mount *mp);
व्योम xfs_ialloc_setup_geometry(काष्ठा xfs_mount *mp);
xfs_ino_t xfs_ialloc_calc_rootino(काष्ठा xfs_mount *mp, पूर्णांक sunit);

#पूर्ण_अगर	/* __XFS_IALLOC_H__ */
