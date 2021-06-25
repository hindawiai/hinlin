<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_INODE_ITEM_H__
#घोषणा	__XFS_INODE_ITEM_H__

/* kernel only definitions */

काष्ठा xfs_buf;
काष्ठा xfs_bmbt_rec;
काष्ठा xfs_inode;
काष्ठा xfs_mount;

काष्ठा xfs_inode_log_item अणु
	काष्ठा xfs_log_item	ili_item;	   /* common portion */
	काष्ठा xfs_inode	*ili_inode;	   /* inode ptr */
	अचिन्हित लघु		ili_lock_flags;	   /* inode lock flags */
	/*
	 * The ili_lock protects the पूर्णांकeractions between the dirty state and
	 * the flush state of the inode log item. This allows us to करो atomic
	 * modअगरications of multiple state fields without having to hold a
	 * specअगरic inode lock to serialise them.
	 *
	 * We need atomic changes between inode dirtying, inode flushing and
	 * inode completion, but these all hold dअगरferent combinations of
	 * ILOCK and IFLUSHING and hence we need some other method of
	 * serialising updates to the flush state.
	 */
	spinlock_t		ili_lock;	   /* flush state lock */
	अचिन्हित पूर्णांक		ili_last_fields;   /* fields when flushed */
	अचिन्हित पूर्णांक		ili_fields;	   /* fields to be logged */
	अचिन्हित पूर्णांक		ili_fsync_fields;  /* logged since last fsync */
	xfs_lsn_t		ili_flush_lsn;	   /* lsn at last flush */
	xfs_lsn_t		ili_last_lsn;	   /* lsn at last transaction */
पूर्ण;

अटल अंतरभूत पूर्णांक xfs_inode_clean(काष्ठा xfs_inode *ip)
अणु
	वापस !ip->i_itemp || !(ip->i_itemp->ili_fields & XFS_ILOG_ALL);
पूर्ण

बाह्य व्योम xfs_inode_item_init(काष्ठा xfs_inode *, काष्ठा xfs_mount *);
बाह्य व्योम xfs_inode_item_destroy(काष्ठा xfs_inode *);
बाह्य व्योम xfs_अगरlush_पात(काष्ठा xfs_inode *);
बाह्य पूर्णांक xfs_inode_item_क्रमmat_convert(xfs_log_iovec_t *,
					 काष्ठा xfs_inode_log_क्रमmat *);

बाह्य काष्ठा kmem_zone	*xfs_ili_zone;

#पूर्ण_अगर	/* __XFS_INODE_ITEM_H__ */
