<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_DQUOT_ITEM_H__
#घोषणा __XFS_DQUOT_ITEM_H__

काष्ठा xfs_dquot;
काष्ठा xfs_trans;
काष्ठा xfs_mount;
काष्ठा xfs_qoff_logitem;

काष्ठा xfs_dq_logitem अणु
	काष्ठा xfs_log_item	qli_item;	/* common portion */
	काष्ठा xfs_dquot	*qli_dquot;	/* dquot ptr */
	xfs_lsn_t		qli_flush_lsn;	/* lsn at last flush */
पूर्ण;

काष्ठा xfs_qoff_logitem अणु
	काष्ठा xfs_log_item	qql_item;	/* common portion */
	काष्ठा xfs_qoff_logitem *qql_start_lip;	/* qoff-start logitem, अगर any */
	अचिन्हित पूर्णांक		qql_flags;
पूर्ण;


व्योम xfs_qm_dquot_logitem_init(काष्ठा xfs_dquot *dqp);
काष्ठा xfs_qoff_logitem	*xfs_qm_qoff_logitem_init(काष्ठा xfs_mount *mp,
		काष्ठा xfs_qoff_logitem *start,
		uपूर्णांक flags);
व्योम xfs_qm_qoff_logitem_rअन्यथा(काष्ठा xfs_qoff_logitem *);
काष्ठा xfs_qoff_logitem	*xfs_trans_get_qoff_item(काष्ठा xfs_trans *tp,
		काष्ठा xfs_qoff_logitem *startqoff,
		uपूर्णांक flags);
व्योम xfs_trans_log_quotaoff_item(काष्ठा xfs_trans *tp,
		काष्ठा xfs_qoff_logitem *qlp);

#पूर्ण_अगर	/* __XFS_DQUOT_ITEM_H__ */
