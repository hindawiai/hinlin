<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2008-2010, Dave Chinner
 * All Rights Reserved.
 */
#अगर_अघोषित XFS_ICREATE_ITEM_H
#घोषणा XFS_ICREATE_ITEM_H	1

/* in memory log item काष्ठाure */
काष्ठा xfs_icreate_item अणु
	काष्ठा xfs_log_item	ic_item;
	काष्ठा xfs_icreate_log	ic_क्रमmat;
पूर्ण;

बाह्य kmem_zone_t *xfs_icreate_zone;	/* inode create item zone */

व्योम xfs_icreate_log(काष्ठा xfs_trans *tp, xfs_agnumber_t agno,
			xfs_agblock_t agbno, अचिन्हित पूर्णांक count,
			अचिन्हित पूर्णांक inode_size, xfs_agblock_t length,
			अचिन्हित पूर्णांक generation);

#पूर्ण_अगर	/* XFS_ICREATE_ITEM_H */
