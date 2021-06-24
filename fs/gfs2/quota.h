<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __QUOTA_DOT_H__
#घोषणा __QUOTA_DOT_H__

#समावेश <linux/list_lru.h>

काष्ठा gfs2_inode;
काष्ठा gfs2_sbd;

#घोषणा NO_UID_QUOTA_CHANGE INVALID_UID
#घोषणा NO_GID_QUOTA_CHANGE INVALID_GID

बाह्य पूर्णांक gfs2_qa_get(काष्ठा gfs2_inode *ip);
बाह्य व्योम gfs2_qa_put(काष्ठा gfs2_inode *ip);
बाह्य पूर्णांक gfs2_quota_hold(काष्ठा gfs2_inode *ip, kuid_t uid, kgid_t gid);
बाह्य व्योम gfs2_quota_unhold(काष्ठा gfs2_inode *ip);

बाह्य पूर्णांक gfs2_quota_lock(काष्ठा gfs2_inode *ip, kuid_t uid, kgid_t gid);
बाह्य व्योम gfs2_quota_unlock(काष्ठा gfs2_inode *ip);

बाह्य पूर्णांक gfs2_quota_check(काष्ठा gfs2_inode *ip, kuid_t uid, kgid_t gid,
			    काष्ठा gfs2_alloc_parms *ap);
बाह्य व्योम gfs2_quota_change(काष्ठा gfs2_inode *ip, s64 change,
			      kuid_t uid, kgid_t gid);

बाह्य पूर्णांक gfs2_quota_sync(काष्ठा super_block *sb, पूर्णांक type);
बाह्य पूर्णांक gfs2_quota_refresh(काष्ठा gfs2_sbd *sdp, काष्ठा kqid qid);

बाह्य पूर्णांक gfs2_quota_init(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_quota_cleanup(काष्ठा gfs2_sbd *sdp);
बाह्य पूर्णांक gfs2_quotad(व्योम *data);

बाह्य व्योम gfs2_wake_up_statfs(काष्ठा gfs2_sbd *sdp);

अटल अंतरभूत पूर्णांक gfs2_quota_lock_check(काष्ठा gfs2_inode *ip,
					काष्ठा gfs2_alloc_parms *ap)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	पूर्णांक ret;

	ap->allowed = अच_पूर्णांक_उच्च; /* Assume we are permitted a whole lot */
	अगर (capable(CAP_SYS_RESOURCE) ||
	    sdp->sd_args.ar_quota == GFS2_QUOTA_OFF)
		वापस 0;
	ret = gfs2_quota_lock(ip, NO_UID_QUOTA_CHANGE, NO_GID_QUOTA_CHANGE);
	अगर (ret)
		वापस ret;
	अगर (sdp->sd_args.ar_quota != GFS2_QUOTA_ON)
		वापस 0;
	ret = gfs2_quota_check(ip, ip->i_inode.i_uid, ip->i_inode.i_gid, ap);
	अगर (ret)
		gfs2_quota_unlock(ip);
	वापस ret;
पूर्ण

बाह्य स्थिर काष्ठा quotactl_ops gfs2_quotactl_ops;
बाह्य काष्ठा shrinker gfs2_qd_shrinker;
बाह्य काष्ठा list_lru gfs2_qd_lru;
बाह्य व्योम __init gfs2_quota_hash_init(व्योम);

#पूर्ण_अगर /* __QUOTA_DOT_H__ */
