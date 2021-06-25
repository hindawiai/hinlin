<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __LOG_DOT_H__
#घोषणा __LOG_DOT_H__

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश "incore.h"
#समावेश "inode.h"

/*
 * The minimum amount of log space required क्रम a log flush is one block क्रम
 * revokes and one block क्रम the log header.  Log flushes other than
 * GFS2_LOG_HEAD_FLUSH_NORMAL may ग_लिखो one or two more log headers.
 */
#घोषणा GFS2_LOG_FLUSH_MIN_BLOCKS 4

/**
 * gfs2_log_lock - acquire the right to mess with the log manager
 * @sdp: the fileप्रणाली
 *
 */

अटल अंतरभूत व्योम gfs2_log_lock(काष्ठा gfs2_sbd *sdp)
__acquires(&sdp->sd_log_lock)
अणु
	spin_lock(&sdp->sd_log_lock);
पूर्ण

/**
 * gfs2_log_unlock - release the right to mess with the log manager
 * @sdp: the fileप्रणाली
 *
 */

अटल अंतरभूत व्योम gfs2_log_unlock(काष्ठा gfs2_sbd *sdp)
__releases(&sdp->sd_log_lock)
अणु
	spin_unlock(&sdp->sd_log_lock);
पूर्ण

अटल अंतरभूत व्योम gfs2_log_poपूर्णांकers_init(काष्ठा gfs2_sbd *sdp,
					  अचिन्हित पूर्णांक value)
अणु
	अगर (++value == sdp->sd_jdesc->jd_blocks) अणु
		value = 0;
	पूर्ण
	sdp->sd_log_tail = value;
	sdp->sd_log_flush_tail = value;
	sdp->sd_log_head = value;
पूर्ण

अटल अंतरभूत व्योम gfs2_ordered_add_inode(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	अगर (gfs2_is_jdata(ip) || !gfs2_is_ordered(sdp))
		वापस;

	अगर (list_empty(&ip->i_ordered)) अणु
		spin_lock(&sdp->sd_ordered_lock);
		अगर (list_empty(&ip->i_ordered))
			list_add(&ip->i_ordered, &sdp->sd_log_ordered);
		spin_unlock(&sdp->sd_ordered_lock);
	पूर्ण
पूर्ण

बाह्य व्योम gfs2_ordered_del_inode(काष्ठा gfs2_inode *ip);
बाह्य अचिन्हित पूर्णांक gfs2_काष्ठा2blk(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक nकाष्ठा);
बाह्य व्योम gfs2_हटाओ_from_ail(काष्ठा gfs2_bufdata *bd);
बाह्य bool gfs2_log_is_empty(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_log_release_revokes(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक revokes);
बाह्य व्योम gfs2_log_release(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक blks);
बाह्य bool gfs2_log_try_reserve(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr,
				 अचिन्हित पूर्णांक *extra_revokes);
बाह्य व्योम gfs2_log_reserve(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr,
			     अचिन्हित पूर्णांक *extra_revokes);
बाह्य व्योम gfs2_ग_लिखो_log_header(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_jdesc *jd,
				  u64 seq, u32 tail, u32 lblock, u32 flags,
				  पूर्णांक op_flags);
बाह्य व्योम gfs2_log_flush(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_glock *gl,
			   u32 type);
बाह्य व्योम gfs2_log_commit(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *trans);
बाह्य व्योम gfs2_ail1_flush(काष्ठा gfs2_sbd *sdp, काष्ठा ग_लिखोback_control *wbc);
बाह्य व्योम log_flush_रुको(काष्ठा gfs2_sbd *sdp);

बाह्य पूर्णांक gfs2_logd(व्योम *data);
बाह्य व्योम gfs2_add_revoke(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_bufdata *bd);
बाह्य व्योम gfs2_glock_हटाओ_revoke(काष्ठा gfs2_glock *gl);
बाह्य व्योम gfs2_flush_revokes(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_ail_drain(काष्ठा gfs2_sbd *sdp);

#पूर्ण_अगर /* __LOG_DOT_H__ */
