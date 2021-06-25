<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_TRANS_H__
#घोषणा	__XFS_TRANS_H__

/* kernel only transaction subप्रणाली defines */

काष्ठा xfs_buf;
काष्ठा xfs_buftarg;
काष्ठा xfs_efd_log_item;
काष्ठा xfs_efi_log_item;
काष्ठा xfs_inode;
काष्ठा xfs_item_ops;
काष्ठा xfs_log_iovec;
काष्ठा xfs_mount;
काष्ठा xfs_trans;
काष्ठा xfs_trans_res;
काष्ठा xfs_dquot_acct;
काष्ठा xfs_rud_log_item;
काष्ठा xfs_rui_log_item;
काष्ठा xfs_btree_cur;
काष्ठा xfs_cui_log_item;
काष्ठा xfs_cud_log_item;
काष्ठा xfs_bui_log_item;
काष्ठा xfs_bud_log_item;

काष्ठा xfs_log_item अणु
	काष्ठा list_head		li_ail;		/* AIL poपूर्णांकers */
	काष्ठा list_head		li_trans;	/* transaction list */
	xfs_lsn_t			li_lsn;		/* last on-disk lsn */
	काष्ठा xfs_mount		*li_mountp;	/* ptr to fs mount */
	काष्ठा xfs_ail			*li_ailp;	/* ptr to AIL */
	uपूर्णांक				li_type;	/* item type */
	अचिन्हित दीर्घ			li_flags;	/* misc flags */
	काष्ठा xfs_buf			*li_buf;	/* real buffer poपूर्णांकer */
	काष्ठा list_head		li_bio_list;	/* buffer item list */
	स्थिर काष्ठा xfs_item_ops	*li_ops;	/* function list */

	/* delayed logging */
	काष्ठा list_head		li_cil;		/* CIL poपूर्णांकers */
	काष्ठा xfs_log_vec		*li_lv;		/* active log vector */
	काष्ठा xfs_log_vec		*li_lv_shaकरोw;	/* standby vector */
	xfs_lsn_t			li_seq;		/* CIL commit seq */
पूर्ण;

/*
 * li_flags use the (set/test/clear)_bit atomic पूर्णांकerfaces because updates can
 * race with each other and we करोn't want to have to use the AIL lock to
 * serialise all updates.
 */
#घोषणा	XFS_LI_IN_AIL	0
#घोषणा	XFS_LI_ABORTED	1
#घोषणा	XFS_LI_FAILED	2
#घोषणा	XFS_LI_सूचीTY	3	/* log item dirty in transaction */

#घोषणा XFS_LI_FLAGS \
	अणु (1 << XFS_LI_IN_AIL),		"IN_AIL" पूर्ण, \
	अणु (1 << XFS_LI_ABORTED),	"ABORTED" पूर्ण, \
	अणु (1 << XFS_LI_FAILED),		"FAILED" पूर्ण, \
	अणु (1 << XFS_LI_सूचीTY),		"DIRTY" पूर्ण

काष्ठा xfs_item_ops अणु
	अचिन्हित flags;
	व्योम (*iop_size)(काष्ठा xfs_log_item *, पूर्णांक *, पूर्णांक *);
	व्योम (*iop_क्रमmat)(काष्ठा xfs_log_item *, काष्ठा xfs_log_vec *);
	व्योम (*iop_pin)(काष्ठा xfs_log_item *);
	व्योम (*iop_unpin)(काष्ठा xfs_log_item *, पूर्णांक हटाओ);
	uपूर्णांक (*iop_push)(काष्ठा xfs_log_item *, काष्ठा list_head *);
	व्योम (*iop_committing)(काष्ठा xfs_log_item *, xfs_lsn_t commit_lsn);
	व्योम (*iop_release)(काष्ठा xfs_log_item *);
	xfs_lsn_t (*iop_committed)(काष्ठा xfs_log_item *, xfs_lsn_t);
	पूर्णांक (*iop_recover)(काष्ठा xfs_log_item *lip,
			   काष्ठा list_head *capture_list);
	bool (*iop_match)(काष्ठा xfs_log_item *item, uपूर्णांक64_t id);
	काष्ठा xfs_log_item *(*iop_relog)(काष्ठा xfs_log_item *पूर्णांकent,
			काष्ठा xfs_trans *tp);
पूर्ण;

/* Is this log item a deferred action पूर्णांकent? */
अटल अंतरभूत bool
xlog_item_is_पूर्णांकent(काष्ठा xfs_log_item *lip)
अणु
	वापस lip->li_ops->iop_recover != शून्य &&
	       lip->li_ops->iop_match != शून्य;
पूर्ण

/* Is this a log पूर्णांकent-करोne item? */
अटल अंतरभूत bool
xlog_item_is_पूर्णांकent_करोne(काष्ठा xfs_log_item *lip)
अणु
	वापस lip->li_ops->iop_unpin == शून्य &&
	       lip->li_ops->iop_push == शून्य;
पूर्ण

/*
 * Release the log item as soon as committed.  This is क्रम items just logging
 * पूर्णांकents that never need to be written back in place.
 */
#घोषणा XFS_ITEM_RELEASE_WHEN_COMMITTED	(1 << 0)

व्योम	xfs_log_item_init(काष्ठा xfs_mount *mp, काष्ठा xfs_log_item *item,
			  पूर्णांक type, स्थिर काष्ठा xfs_item_ops *ops);

/*
 * Return values क्रम the iop_push() routines.
 */
#घोषणा XFS_ITEM_SUCCESS	0
#घोषणा XFS_ITEM_PINNED		1
#घोषणा XFS_ITEM_LOCKED		2
#घोषणा XFS_ITEM_FLUSHING	3

/*
 * Deferred operation item relogging limits.
 */
#घोषणा XFS_DEFER_OPS_NR_INODES	2	/* join up to two inodes */
#घोषणा XFS_DEFER_OPS_NR_BUFS	2	/* join up to two buffers */

/*
 * This is the काष्ठाure मुख्यtained क्रम every active transaction.
 */
प्रकार काष्ठा xfs_trans अणु
	अचिन्हित पूर्णांक		t_magic;	/* magic number */
	अचिन्हित पूर्णांक		t_log_res;	/* amt of log space resvd */
	अचिन्हित पूर्णांक		t_log_count;	/* count क्रम perm log res */
	अचिन्हित पूर्णांक		t_blk_res;	/* # of blocks resvd */
	अचिन्हित पूर्णांक		t_blk_res_used;	/* # of resvd blocks used */
	अचिन्हित पूर्णांक		t_rtx_res;	/* # of rt extents resvd */
	अचिन्हित पूर्णांक		t_rtx_res_used;	/* # of resvd rt extents used */
	अचिन्हित पूर्णांक		t_flags;	/* misc flags */
	xfs_fsblock_t		t_firstblock;	/* first block allocated */
	काष्ठा xlog_ticket	*t_ticket;	/* log mgr ticket */
	काष्ठा xfs_mount	*t_mountp;	/* ptr to fs mount काष्ठा */
	काष्ठा xfs_dquot_acct   *t_dqinfo;	/* acctg info क्रम dquots */
	पूर्णांक64_t			t_icount_delta;	/* superblock icount change */
	पूर्णांक64_t			t_अगरree_delta;	/* superblock अगरree change */
	पूर्णांक64_t			t_fdblocks_delta; /* superblock fdblocks chg */
	पूर्णांक64_t			t_res_fdblocks_delta; /* on-disk only chg */
	पूर्णांक64_t			t_frextents_delta;/* superblock मुक्तxtents chg*/
	पूर्णांक64_t			t_res_frextents_delta; /* on-disk only chg */
	पूर्णांक64_t			t_dblocks_delta;/* superblock dblocks change */
	पूर्णांक64_t			t_agcount_delta;/* superblock agcount change */
	पूर्णांक64_t			t_imaxpct_delta;/* superblock imaxpct change */
	पूर्णांक64_t			t_rextsize_delta;/* superblock rextsize chg */
	पूर्णांक64_t			t_rbmblocks_delta;/* superblock rbmblocks chg */
	पूर्णांक64_t			t_rblocks_delta;/* superblock rblocks change */
	पूर्णांक64_t			t_rextents_delta;/* superblocks rextents chg */
	पूर्णांक64_t			t_rextslog_delta;/* superblocks rextslog chg */
	काष्ठा list_head	t_items;	/* log item descriptors */
	काष्ठा list_head	t_busy;		/* list of busy extents */
	काष्ठा list_head	t_dfops;	/* deferred operations */
	अचिन्हित दीर्घ		t_pflags;	/* saved process flags state */
पूर्ण xfs_trans_t;

/*
 * XFS transaction mechanism exported पूर्णांकerfaces that are
 * actually macros.
 */
#घोषणा	xfs_trans_set_sync(tp)		((tp)->t_flags |= XFS_TRANS_SYNC)

/*
 * XFS transaction mechanism exported पूर्णांकerfaces.
 */
पूर्णांक		xfs_trans_alloc(काष्ठा xfs_mount *mp, काष्ठा xfs_trans_res *resp,
			uपूर्णांक blocks, uपूर्णांक rtextents, uपूर्णांक flags,
			काष्ठा xfs_trans **tpp);
पूर्णांक		xfs_trans_alloc_empty(काष्ठा xfs_mount *mp,
			काष्ठा xfs_trans **tpp);
व्योम		xfs_trans_mod_sb(xfs_trans_t *, uपूर्णांक, पूर्णांक64_t);

पूर्णांक xfs_trans_get_buf_map(काष्ठा xfs_trans *tp, काष्ठा xfs_buftarg *target,
		काष्ठा xfs_buf_map *map, पूर्णांक nmaps, xfs_buf_flags_t flags,
		काष्ठा xfs_buf **bpp);

अटल अंतरभूत पूर्णांक
xfs_trans_get_buf(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buftarg	*target,
	xfs_daddr_t		blkno,
	पूर्णांक			numblks,
	uपूर्णांक			flags,
	काष्ठा xfs_buf		**bpp)
अणु
	DEFINE_SINGLE_BUF_MAP(map, blkno, numblks);
	वापस xfs_trans_get_buf_map(tp, target, &map, 1, flags, bpp);
पूर्ण

पूर्णांक		xfs_trans_पढ़ो_buf_map(काष्ठा xfs_mount *mp,
				       काष्ठा xfs_trans *tp,
				       काष्ठा xfs_buftarg *target,
				       काष्ठा xfs_buf_map *map, पूर्णांक nmaps,
				       xfs_buf_flags_t flags,
				       काष्ठा xfs_buf **bpp,
				       स्थिर काष्ठा xfs_buf_ops *ops);

अटल अंतरभूत पूर्णांक
xfs_trans_पढ़ो_buf(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buftarg	*target,
	xfs_daddr_t		blkno,
	पूर्णांक			numblks,
	xfs_buf_flags_t		flags,
	काष्ठा xfs_buf		**bpp,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	DEFINE_SINGLE_BUF_MAP(map, blkno, numblks);
	वापस xfs_trans_पढ़ो_buf_map(mp, tp, target, &map, 1,
				      flags, bpp, ops);
पूर्ण

काष्ठा xfs_buf	*xfs_trans_माला_लोb(काष्ठा xfs_trans *);

व्योम		xfs_trans_brअन्यथा(xfs_trans_t *, काष्ठा xfs_buf *);
व्योम		xfs_trans_bjoin(xfs_trans_t *, काष्ठा xfs_buf *);
व्योम		xfs_trans_bhold(xfs_trans_t *, काष्ठा xfs_buf *);
व्योम		xfs_trans_bhold_release(xfs_trans_t *, काष्ठा xfs_buf *);
व्योम		xfs_trans_binval(xfs_trans_t *, काष्ठा xfs_buf *);
व्योम		xfs_trans_inode_buf(xfs_trans_t *, काष्ठा xfs_buf *);
व्योम		xfs_trans_stale_inode_buf(xfs_trans_t *, काष्ठा xfs_buf *);
bool		xfs_trans_ordered_buf(xfs_trans_t *, काष्ठा xfs_buf *);
व्योम		xfs_trans_dquot_buf(xfs_trans_t *, काष्ठा xfs_buf *, uपूर्णांक);
व्योम		xfs_trans_inode_alloc_buf(xfs_trans_t *, काष्ठा xfs_buf *);
व्योम		xfs_trans_ichgसमय(काष्ठा xfs_trans *, काष्ठा xfs_inode *, पूर्णांक);
व्योम		xfs_trans_ijoin(काष्ठा xfs_trans *, काष्ठा xfs_inode *, uपूर्णांक);
व्योम		xfs_trans_log_buf(काष्ठा xfs_trans *, काष्ठा xfs_buf *, uपूर्णांक,
				  uपूर्णांक);
व्योम		xfs_trans_dirty_buf(काष्ठा xfs_trans *, काष्ठा xfs_buf *);
bool		xfs_trans_buf_is_dirty(काष्ठा xfs_buf *bp);
व्योम		xfs_trans_log_inode(xfs_trans_t *, काष्ठा xfs_inode *, uपूर्णांक);

पूर्णांक		xfs_trans_commit(काष्ठा xfs_trans *);
पूर्णांक		xfs_trans_roll(काष्ठा xfs_trans **);
पूर्णांक		xfs_trans_roll_inode(काष्ठा xfs_trans **, काष्ठा xfs_inode *);
व्योम		xfs_trans_cancel(xfs_trans_t *);
पूर्णांक		xfs_trans_ail_init(काष्ठा xfs_mount *);
व्योम		xfs_trans_ail_destroy(काष्ठा xfs_mount *);

व्योम		xfs_trans_buf_set_type(काष्ठा xfs_trans *, काष्ठा xfs_buf *,
				       क्रमागत xfs_blft);
व्योम		xfs_trans_buf_copy_type(काष्ठा xfs_buf *dst_bp,
					काष्ठा xfs_buf *src_bp);

बाह्य kmem_zone_t	*xfs_trans_zone;

अटल अंतरभूत काष्ठा xfs_log_item *
xfs_trans_item_relog(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_trans	*tp)
अणु
	वापस lip->li_ops->iop_relog(lip, tp);
पूर्ण

काष्ठा xfs_dquot;

पूर्णांक xfs_trans_alloc_inode(काष्ठा xfs_inode *ip, काष्ठा xfs_trans_res *resv,
		अचिन्हित पूर्णांक dblocks, अचिन्हित पूर्णांक rblocks, bool क्रमce,
		काष्ठा xfs_trans **tpp);
पूर्णांक xfs_trans_alloc_icreate(काष्ठा xfs_mount *mp, काष्ठा xfs_trans_res *resv,
		काष्ठा xfs_dquot *udqp, काष्ठा xfs_dquot *gdqp,
		काष्ठा xfs_dquot *pdqp, अचिन्हित पूर्णांक dblocks,
		काष्ठा xfs_trans **tpp);
पूर्णांक xfs_trans_alloc_ichange(काष्ठा xfs_inode *ip, काष्ठा xfs_dquot *udqp,
		काष्ठा xfs_dquot *gdqp, काष्ठा xfs_dquot *pdqp, bool क्रमce,
		काष्ठा xfs_trans **tpp);

अटल अंतरभूत व्योम
xfs_trans_set_context(
	काष्ठा xfs_trans	*tp)
अणु
	ASSERT(current->journal_info == शून्य);
	tp->t_pflags = meदो_स्मृति_nofs_save();
	current->journal_info = tp;
पूर्ण

अटल अंतरभूत व्योम
xfs_trans_clear_context(
	काष्ठा xfs_trans	*tp)
अणु
	अगर (current->journal_info == tp) अणु
		meदो_स्मृति_nofs_restore(tp->t_pflags);
		current->journal_info = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
xfs_trans_चयन_context(
	काष्ठा xfs_trans	*old_tp,
	काष्ठा xfs_trans	*new_tp)
अणु
	ASSERT(current->journal_info == old_tp);
	new_tp->t_pflags = old_tp->t_pflags;
	old_tp->t_pflags = 0;
	current->journal_info = new_tp;
पूर्ण

#पूर्ण_अगर	/* __XFS_TRANS_H__ */
