<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_INODE_FORK_H__
#घोषणा	__XFS_INODE_FORK_H__

काष्ठा xfs_inode_log_item;
काष्ठा xfs_dinode;

/*
 * File incore extent inक्रमmation, present क्रम each of data & attr विभाजनs.
 */
काष्ठा xfs_अगरork अणु
	पूर्णांक64_t			अगर_bytes;	/* bytes in अगर_u1 */
	काष्ठा xfs_btree_block	*अगर_broot;	/* file's incore btree root */
	अचिन्हित पूर्णांक		अगर_seq;		/* विभाजन mod counter */
	पूर्णांक			अगर_height;	/* height of the extent tree */
	जोड़ अणु
		व्योम		*अगर_root;	/* extent tree root */
		अक्षर		*अगर_data;	/* अंतरभूत file data */
	पूर्ण अगर_u1;
	लघु			अगर_broot_bytes;	/* bytes allocated क्रम root */
	पूर्णांक8_t			अगर_क्रमmat;	/* क्रमmat of this विभाजन */
	xfs_extnum_t		अगर_nextents;	/* # of extents in this विभाजन */
पूर्ण;

/*
 * Worst-हाल increase in the विभाजन extent count when we're adding a single
 * extent to a विभाजन and there's no possibility of splitting an existing mapping.
 */
#घोषणा XFS_IEXT_ADD_NOSPLIT_CNT	(1)

/*
 * Punching out an extent from the middle of an existing extent can cause the
 * extent count to increase by 1.
 * i.e. | Old extent | Hole | Old extent |
 */
#घोषणा XFS_IEXT_PUNCH_HOLE_CNT		(1)

/*
 * Directory entry addition can cause the following,
 * 1. Data block can be added/हटाओd.
 *    A new extent can cause extent count to increase by 1.
 * 2. Free disk block can be added/हटाओd.
 *    Same behaviour as described above क्रम Data block.
 * 3. Dabtree blocks.
 *    XFS_DA_NODE_MAXDEPTH blocks can be added. Each of these can be new
 *    extents. Hence extent count can increase by XFS_DA_NODE_MAXDEPTH.
 */
#घोषणा XFS_IEXT_सूची_MANIP_CNT(mp) \
	((XFS_DA_NODE_MAXDEPTH + 1 + 1) * (mp)->m_dir_geo->fsbcount)

/*
 * Adding/removing an xattr can cause XFS_DA_NODE_MAXDEPTH extents to
 * be added. One extra extent क्रम dabtree in हाल a local attr is
 * large enough to cause a द्विगुन split.  It can also cause extent
 * count to increase proportional to the size of a remote xattr's
 * value.
 */
#घोषणा XFS_IEXT_ATTR_MANIP_CNT(rmt_blks) \
	(XFS_DA_NODE_MAXDEPTH + max(1, rmt_blks))

/*
 * A ग_लिखो to a sub-पूर्णांकerval of an existing unwritten extent causes the original
 * extent to be split पूर्णांकo 3 extents
 * i.e. | Unwritten | Real | Unwritten |
 * Hence extent count can increase by 2.
 */
#घोषणा XFS_IEXT_WRITE_UNWRITTEN_CNT	(2)


/*
 * Moving an extent to data विभाजन can cause a sub-पूर्णांकerval of an existing extent
 * to be unmapped. This will increase extent count by 1. Mapping in the new
 * extent can increase the extent count by 1 again i.e.
 * | Old extent | New extent | Old extent |
 * Hence number of extents increases by 2.
 */
#घोषणा XFS_IEXT_REFLINK_END_COW_CNT	(2)

/*
 * Removing an initial range of source/करोnor file's extent and adding a new
 * extent (from करोnor/source file) in its place will cause extent count to
 * increase by 1.
 */
#घोषणा XFS_IEXT_SWAP_RMAP_CNT		(1)

/*
 * Fork handling.
 */

#घोषणा XFS_IFORK_Q(ip)			((ip)->i_विभाजनoff != 0)
#घोषणा XFS_IFORK_BOFF(ip)		((पूर्णांक)((ip)->i_विभाजनoff << 3))

#घोषणा XFS_IFORK_PTR(ip,w)		\
	((w) == XFS_DATA_FORK ? \
		&(ip)->i_df : \
		((w) == XFS_ATTR_FORK ? \
			(ip)->i_afp : \
			(ip)->i_cowfp))
#घोषणा XFS_IFORK_DSIZE(ip) \
	(XFS_IFORK_Q(ip) ? XFS_IFORK_BOFF(ip) : XFS_LITINO((ip)->i_mount))
#घोषणा XFS_IFORK_ASIZE(ip) \
	(XFS_IFORK_Q(ip) ? XFS_LITINO((ip)->i_mount) - XFS_IFORK_BOFF(ip) : 0)
#घोषणा XFS_IFORK_SIZE(ip,w) \
	((w) == XFS_DATA_FORK ? \
		XFS_IFORK_DSIZE(ip) : \
		((w) == XFS_ATTR_FORK ? \
			XFS_IFORK_ASIZE(ip) : \
			0))
#घोषणा XFS_IFORK_MAXEXT(ip, w) \
	(XFS_IFORK_SIZE(ip, w) / माप(xfs_bmbt_rec_t))

अटल अंतरभूत bool xfs_अगरork_has_extents(काष्ठा xfs_अगरork *अगरp)
अणु
	वापस अगरp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS ||
		अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE;
पूर्ण

अटल अंतरभूत xfs_extnum_t xfs_अगरork_nextents(काष्ठा xfs_अगरork *अगरp)
अणु
	अगर (!अगरp)
		वापस 0;
	वापस अगरp->अगर_nextents;
पूर्ण

अटल अंतरभूत पूर्णांक8_t xfs_अगरork_क्रमmat(काष्ठा xfs_अगरork *अगरp)
अणु
	अगर (!अगरp)
		वापस XFS_DINODE_FMT_EXTENTS;
	वापस अगरp->अगर_क्रमmat;
पूर्ण

काष्ठा xfs_अगरork *xfs_अगरork_alloc(क्रमागत xfs_dinode_fmt क्रमmat,
				xfs_extnum_t nextents);
काष्ठा xfs_अगरork *xfs_iext_state_to_विभाजन(काष्ठा xfs_inode *ip, पूर्णांक state);

पूर्णांक		xfs_अगरormat_data_विभाजन(काष्ठा xfs_inode *, काष्ठा xfs_dinode *);
पूर्णांक		xfs_अगरormat_attr_विभाजन(काष्ठा xfs_inode *, काष्ठा xfs_dinode *);
व्योम		xfs_अगरlush_विभाजन(काष्ठा xfs_inode *, काष्ठा xfs_dinode *,
				काष्ठा xfs_inode_log_item *, पूर्णांक);
व्योम		xfs_idestroy_विभाजन(काष्ठा xfs_अगरork *अगरp);
व्योम		xfs_idata_पुनः_स्मृति(काष्ठा xfs_inode *ip, पूर्णांक64_t byte_dअगरf,
				पूर्णांक whichविभाजन);
व्योम		xfs_iroot_पुनः_स्मृति(काष्ठा xfs_inode *, पूर्णांक, पूर्णांक);
पूर्णांक		xfs_iपढ़ो_extents(काष्ठा xfs_trans *, काष्ठा xfs_inode *, पूर्णांक);
पूर्णांक		xfs_iextents_copy(काष्ठा xfs_inode *, काष्ठा xfs_bmbt_rec *,
				  पूर्णांक);
व्योम		xfs_init_local_विभाजन(काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन,
				स्थिर व्योम *data, पूर्णांक64_t size);

xfs_extnum_t	xfs_iext_count(काष्ठा xfs_अगरork *अगरp);
व्योम		xfs_iext_insert(काष्ठा xfs_inode *, काष्ठा xfs_iext_cursor *cur,
			काष्ठा xfs_bmbt_irec *, पूर्णांक);
व्योम		xfs_iext_हटाओ(काष्ठा xfs_inode *, काष्ठा xfs_iext_cursor *,
			पूर्णांक);
व्योम		xfs_iext_destroy(काष्ठा xfs_अगरork *);

bool		xfs_iext_lookup_extent(काष्ठा xfs_inode *ip,
			काष्ठा xfs_अगरork *अगरp, xfs_fileoff_t bno,
			काष्ठा xfs_iext_cursor *cur,
			काष्ठा xfs_bmbt_irec *gotp);
bool		xfs_iext_lookup_extent_beक्रमe(काष्ठा xfs_inode *ip,
			काष्ठा xfs_अगरork *अगरp, xfs_fileoff_t *end,
			काष्ठा xfs_iext_cursor *cur,
			काष्ठा xfs_bmbt_irec *gotp);
bool		xfs_iext_get_extent(काष्ठा xfs_अगरork *अगरp,
			काष्ठा xfs_iext_cursor *cur,
			काष्ठा xfs_bmbt_irec *gotp);
व्योम		xfs_iext_update_extent(काष्ठा xfs_inode *ip, पूर्णांक state,
			काष्ठा xfs_iext_cursor *cur,
			काष्ठा xfs_bmbt_irec *gotp);

व्योम		xfs_iext_first(काष्ठा xfs_अगरork *, काष्ठा xfs_iext_cursor *);
व्योम		xfs_iext_last(काष्ठा xfs_अगरork *, काष्ठा xfs_iext_cursor *);
व्योम		xfs_iext_next(काष्ठा xfs_अगरork *, काष्ठा xfs_iext_cursor *);
व्योम		xfs_iext_prev(काष्ठा xfs_अगरork *, काष्ठा xfs_iext_cursor *);

अटल अंतरभूत bool xfs_iext_next_extent(काष्ठा xfs_अगरork *अगरp,
		काष्ठा xfs_iext_cursor *cur, काष्ठा xfs_bmbt_irec *gotp)
अणु
	xfs_iext_next(अगरp, cur);
	वापस xfs_iext_get_extent(अगरp, cur, gotp);
पूर्ण

अटल अंतरभूत bool xfs_iext_prev_extent(काष्ठा xfs_अगरork *अगरp,
		काष्ठा xfs_iext_cursor *cur, काष्ठा xfs_bmbt_irec *gotp)
अणु
	xfs_iext_prev(अगरp, cur);
	वापस xfs_iext_get_extent(अगरp, cur, gotp);
पूर्ण

/*
 * Return the extent after cur in gotp without updating the cursor.
 */
अटल अंतरभूत bool xfs_iext_peek_next_extent(काष्ठा xfs_अगरork *अगरp,
		काष्ठा xfs_iext_cursor *cur, काष्ठा xfs_bmbt_irec *gotp)
अणु
	काष्ठा xfs_iext_cursor ncur = *cur;

	xfs_iext_next(अगरp, &ncur);
	वापस xfs_iext_get_extent(अगरp, &ncur, gotp);
पूर्ण

/*
 * Return the extent beक्रमe cur in gotp without updating the cursor.
 */
अटल अंतरभूत bool xfs_iext_peek_prev_extent(काष्ठा xfs_अगरork *अगरp,
		काष्ठा xfs_iext_cursor *cur, काष्ठा xfs_bmbt_irec *gotp)
अणु
	काष्ठा xfs_iext_cursor ncur = *cur;

	xfs_iext_prev(अगरp, &ncur);
	वापस xfs_iext_get_extent(अगरp, &ncur, gotp);
पूर्ण

#घोषणा क्रम_each_xfs_iext(अगरp, ext, got)		\
	क्रम (xfs_iext_first((अगरp), (ext));		\
	     xfs_iext_get_extent((अगरp), (ext), (got));	\
	     xfs_iext_next((अगरp), (ext)))

बाह्य काष्ठा kmem_zone	*xfs_अगरork_zone;

बाह्य व्योम xfs_अगरork_init_cow(काष्ठा xfs_inode *ip);

पूर्णांक xfs_अगरork_verअगरy_local_data(काष्ठा xfs_inode *ip);
पूर्णांक xfs_अगरork_verअगरy_local_attr(काष्ठा xfs_inode *ip);
पूर्णांक xfs_iext_count_may_overflow(काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन,
		पूर्णांक nr_to_add);

/* वापसs true अगर the विभाजन has extents but they are not पढ़ो in yet. */
अटल अंतरभूत bool xfs_need_iपढ़ो_extents(काष्ठा xfs_अगरork *अगरp)
अणु
	वापस अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE && अगरp->अगर_height == 0;
पूर्ण

#पूर्ण_अगर	/* __XFS_INODE_FORK_H__ */
