<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2019 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_PWORK_H__
#घोषणा __XFS_PWORK_H__

काष्ठा xfs_pwork;
काष्ठा xfs_mount;

प्रकार पूर्णांक (*xfs_pwork_work_fn)(काष्ठा xfs_mount *mp, काष्ठा xfs_pwork *pwork);

/*
 * Parallel work coordination काष्ठाure.
 */
काष्ठा xfs_pwork_ctl अणु
	काष्ठा workqueue_काष्ठा	*wq;
	काष्ठा xfs_mount	*mp;
	xfs_pwork_work_fn	work_fn;
	काष्ठा रुको_queue_head	poll_रुको;
	atomic_t		nr_work;
	पूर्णांक			error;
पूर्ण;

/*
 * Embed this parallel work control item inside your own work काष्ठाure,
 * then queue work with it.
 */
काष्ठा xfs_pwork अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा xfs_pwork_ctl	*pctl;
पूर्ण;

#घोषणा XFS_PWORK_SINGLE_THREADED	अणु .pctl = शून्य पूर्ण

/* Have we been told to पात? */
अटल अंतरभूत bool
xfs_pwork_ctl_want_पात(
	काष्ठा xfs_pwork_ctl	*pctl)
अणु
	वापस pctl && pctl->error;
पूर्ण

/* Have we been told to पात? */
अटल अंतरभूत bool
xfs_pwork_want_पात(
	काष्ठा xfs_pwork	*pwork)
अणु
	वापस xfs_pwork_ctl_want_पात(pwork->pctl);
पूर्ण

पूर्णांक xfs_pwork_init(काष्ठा xfs_mount *mp, काष्ठा xfs_pwork_ctl *pctl,
		xfs_pwork_work_fn work_fn, स्थिर अक्षर *tag);
व्योम xfs_pwork_queue(काष्ठा xfs_pwork_ctl *pctl, काष्ठा xfs_pwork *pwork);
पूर्णांक xfs_pwork_destroy(काष्ठा xfs_pwork_ctl *pctl);
व्योम xfs_pwork_poll(काष्ठा xfs_pwork_ctl *pctl);

#पूर्ण_अगर /* __XFS_PWORK_H__ */
