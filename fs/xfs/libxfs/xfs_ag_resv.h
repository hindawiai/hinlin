<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_AG_RESV_H__
#घोषणा	__XFS_AG_RESV_H__

पूर्णांक xfs_ag_resv_मुक्त(काष्ठा xfs_perag *pag);
पूर्णांक xfs_ag_resv_init(काष्ठा xfs_perag *pag, काष्ठा xfs_trans *tp);

bool xfs_ag_resv_critical(काष्ठा xfs_perag *pag, क्रमागत xfs_ag_resv_type type);
xfs_extlen_t xfs_ag_resv_needed(काष्ठा xfs_perag *pag,
		क्रमागत xfs_ag_resv_type type);

व्योम xfs_ag_resv_alloc_extent(काष्ठा xfs_perag *pag, क्रमागत xfs_ag_resv_type type,
		काष्ठा xfs_alloc_arg *args);
व्योम xfs_ag_resv_मुक्त_extent(काष्ठा xfs_perag *pag, क्रमागत xfs_ag_resv_type type,
		काष्ठा xfs_trans *tp, xfs_extlen_t len);

/*
 * RMAPBT reservation accounting wrappers. Since rmapbt blocks are sourced from
 * the AGFL, they are allocated one at a समय and the reservation updates करोn't
 * require a transaction.
 */
अटल अंतरभूत व्योम
xfs_ag_resv_rmapbt_alloc(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno)
अणु
	काष्ठा xfs_alloc_arg	args = अणु शून्य पूर्ण;
	काष्ठा xfs_perag	*pag;

	args.len = 1;
	pag = xfs_perag_get(mp, agno);
	xfs_ag_resv_alloc_extent(pag, XFS_AG_RESV_RMAPBT, &args);
	xfs_perag_put(pag);
पूर्ण

#पूर्ण_अगर	/* __XFS_AG_RESV_H__ */
