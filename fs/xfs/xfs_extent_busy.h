<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * Copyright (c) 2010 David Chinner.
 * Copyright (c) 2011 Christoph Hellwig.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_EXTENT_BUSY_H__
#घोषणा	__XFS_EXTENT_BUSY_H__

काष्ठा xfs_mount;
काष्ठा xfs_trans;
काष्ठा xfs_alloc_arg;

/*
 * Busy block/extent entry.  Indexed by a rbtree in perag to mark blocks that
 * have been मुक्तd but whose transactions aren't committed to disk yet.
 *
 * Note that we use the transaction ID to record the transaction, not the
 * transaction काष्ठाure itself. See xfs_extent_busy_insert() क्रम details.
 */
काष्ठा xfs_extent_busy अणु
	काष्ठा rb_node	rb_node;	/* ag by-bno indexed search tree */
	काष्ठा list_head list;		/* transaction busy extent list */
	xfs_agnumber_t	agno;
	xfs_agblock_t	bno;
	xfs_extlen_t	length;
	अचिन्हित पूर्णांक	flags;
#घोषणा XFS_EXTENT_BUSY_DISCARDED	0x01	/* undergoing a discard op. */
#घोषणा XFS_EXTENT_BUSY_SKIP_DISCARD	0x02	/* करो not discard */
पूर्ण;

व्योम
xfs_extent_busy_insert(काष्ठा xfs_trans *tp, xfs_agnumber_t agno,
	xfs_agblock_t bno, xfs_extlen_t len, अचिन्हित पूर्णांक flags);

व्योम
xfs_extent_busy_clear(काष्ठा xfs_mount *mp, काष्ठा list_head *list,
	bool करो_discard);

पूर्णांक
xfs_extent_busy_search(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
	xfs_agblock_t bno, xfs_extlen_t len);

व्योम
xfs_extent_busy_reuse(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
	xfs_agblock_t fbno, xfs_extlen_t flen, bool userdata);

bool
xfs_extent_busy_trim(काष्ठा xfs_alloc_arg *args, xfs_agblock_t *bno,
		xfs_extlen_t *len, अचिन्हित *busy_gen);

व्योम
xfs_extent_busy_flush(काष्ठा xfs_mount *mp, काष्ठा xfs_perag *pag,
	अचिन्हित busy_gen);

व्योम
xfs_extent_busy_रुको_all(काष्ठा xfs_mount *mp);

पूर्णांक
xfs_extent_busy_ag_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
	स्थिर काष्ठा list_head *b);

अटल अंतरभूत व्योम xfs_extent_busy_sort(काष्ठा list_head *list)
अणु
	list_sort(शून्य, list, xfs_extent_busy_ag_cmp);
पूर्ण

#पूर्ण_अगर /* __XFS_EXTENT_BUSY_H__ */
