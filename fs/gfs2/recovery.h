<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __RECOVERY_DOT_H__
#घोषणा __RECOVERY_DOT_H__

#समावेश "incore.h"

बाह्य काष्ठा workqueue_काष्ठा *gfs_recovery_wq;

अटल अंतरभूत व्योम gfs2_replay_incr_blk(काष्ठा gfs2_jdesc *jd, u32 *blk)
अणु
	अगर (++*blk == jd->jd_blocks)
	        *blk = 0;
पूर्ण

बाह्य पूर्णांक gfs2_replay_पढ़ो_block(काष्ठा gfs2_jdesc *jd, अचिन्हित पूर्णांक blk,
			   काष्ठा buffer_head **bh);

बाह्य पूर्णांक gfs2_revoke_add(काष्ठा gfs2_jdesc *jd, u64 blkno, अचिन्हित पूर्णांक where);
बाह्य पूर्णांक gfs2_revoke_check(काष्ठा gfs2_jdesc *jd, u64 blkno, अचिन्हित पूर्णांक where);
बाह्य व्योम gfs2_revoke_clean(काष्ठा gfs2_jdesc *jd);

बाह्य पूर्णांक gfs2_recover_journal(काष्ठा gfs2_jdesc *gfs2_jd, bool रुको);
बाह्य व्योम gfs2_recover_func(काष्ठा work_काष्ठा *work);
बाह्य पूर्णांक __get_log_header(काष्ठा gfs2_sbd *sdp,
			    स्थिर काष्ठा gfs2_log_header *lh, अचिन्हित पूर्णांक blkno,
			    काष्ठा gfs2_log_header_host *head);

#पूर्ण_अगर /* __RECOVERY_DOT_H__ */

