<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __ACL_DOT_H__
#घोषणा __ACL_DOT_H__

#समावेश "incore.h"

#घोषणा GFS2_ACL_MAX_ENTRIES(sdp) ((300 << (sdp)->sd_sb.sb_bsize_shअगरt) >> 12)

बाह्य काष्ठा posix_acl *gfs2_get_acl(काष्ठा inode *inode, पूर्णांक type);
बाह्य पूर्णांक __gfs2_set_acl(काष्ठा inode *inode, काष्ठा posix_acl *acl, पूर्णांक type);
बाह्य पूर्णांक gfs2_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
			काष्ठा posix_acl *acl, पूर्णांक type);

#पूर्ण_अगर /* __ACL_DOT_H__ */
