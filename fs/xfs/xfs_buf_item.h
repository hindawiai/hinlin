<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_BUF_ITEM_H__
#घोषणा	__XFS_BUF_ITEM_H__

/* kernel only definitions */

/* buf log item flags */
#घोषणा	XFS_BLI_HOLD		0x01
#घोषणा	XFS_BLI_सूचीTY		0x02
#घोषणा	XFS_BLI_STALE		0x04
#घोषणा	XFS_BLI_LOGGED		0x08
#घोषणा	XFS_BLI_INODE_ALLOC_BUF	0x10
#घोषणा XFS_BLI_STALE_INODE	0x20
#घोषणा	XFS_BLI_INODE_BUF	0x40
#घोषणा	XFS_BLI_ORDERED		0x80

#घोषणा XFS_BLI_FLAGS \
	अणु XFS_BLI_HOLD,		"HOLD" पूर्ण, \
	अणु XFS_BLI_सूचीTY,	"DIRTY" पूर्ण, \
	अणु XFS_BLI_STALE,	"STALE" पूर्ण, \
	अणु XFS_BLI_LOGGED,	"LOGGED" पूर्ण, \
	अणु XFS_BLI_INODE_ALLOC_BUF, "INODE_ALLOC" पूर्ण, \
	अणु XFS_BLI_STALE_INODE,	"STALE_INODE" पूर्ण, \
	अणु XFS_BLI_INODE_BUF,	"INODE_BUF" पूर्ण, \
	अणु XFS_BLI_ORDERED,	"ORDERED" पूर्ण


काष्ठा xfs_buf;
काष्ठा xfs_mount;
काष्ठा xfs_buf_log_item;

/*
 * This is the in core log item काष्ठाure used to track inक्रमmation
 * needed to log buffers.  It tracks how many बार the lock has been
 * locked, and which 128 byte chunks of the buffer are dirty.
 */
काष्ठा xfs_buf_log_item अणु
	काष्ठा xfs_log_item	bli_item;	/* common item काष्ठाure */
	काष्ठा xfs_buf		*bli_buf;	/* real buffer poपूर्णांकer */
	अचिन्हित पूर्णांक		bli_flags;	/* misc flags */
	अचिन्हित पूर्णांक		bli_recur;	/* lock recursion count */
	atomic_t		bli_refcount;	/* cnt of tp refs */
	पूर्णांक			bli_क्रमmat_count;	/* count of headers */
	काष्ठा xfs_buf_log_क्रमmat *bli_क्रमmats;	/* array of in-log header ptrs */
	काष्ठा xfs_buf_log_क्रमmat __bli_क्रमmat;	/* embedded in-log header */
पूर्ण;

पूर्णांक	xfs_buf_item_init(काष्ठा xfs_buf *, काष्ठा xfs_mount *);
व्योम	xfs_buf_item_करोne(काष्ठा xfs_buf *bp);
व्योम	xfs_buf_item_rअन्यथा(काष्ठा xfs_buf *);
bool	xfs_buf_item_put(काष्ठा xfs_buf_log_item *);
व्योम	xfs_buf_item_log(काष्ठा xfs_buf_log_item *, uपूर्णांक, uपूर्णांक);
bool	xfs_buf_item_dirty_क्रमmat(काष्ठा xfs_buf_log_item *);
व्योम	xfs_buf_inode_ioकरोne(काष्ठा xfs_buf *);
व्योम	xfs_buf_inode_io_fail(काष्ठा xfs_buf *bp);
#अगर_घोषित CONFIG_XFS_QUOTA
व्योम	xfs_buf_dquot_ioकरोne(काष्ठा xfs_buf *);
व्योम	xfs_buf_dquot_io_fail(काष्ठा xfs_buf *bp);
#अन्यथा
अटल अंतरभूत व्योम xfs_buf_dquot_ioकरोne(काष्ठा xfs_buf *bp)
अणु
पूर्ण
अटल अंतरभूत व्योम xfs_buf_dquot_io_fail(काष्ठा xfs_buf *bp)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_XFS_QUOTA */
व्योम	xfs_buf_ioकरोne(काष्ठा xfs_buf *);
bool	xfs_buf_log_check_iovec(काष्ठा xfs_log_iovec *iovec);

बाह्य kmem_zone_t	*xfs_buf_item_zone;

#पूर्ण_अगर	/* __XFS_BUF_ITEM_H__ */
