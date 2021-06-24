<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * acl.h
 *
 * Copyright (C) 2004, 2008 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_ACL_H
#घोषणा OCFS2_ACL_H

#समावेश <linux/posix_acl_xattr.h>

काष्ठा ocfs2_acl_entry अणु
	__le16 e_tag;
	__le16 e_perm;
	__le32 e_id;
पूर्ण;

काष्ठा posix_acl *ocfs2_iop_get_acl(काष्ठा inode *inode, पूर्णांक type);
पूर्णांक ocfs2_iop_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		      काष्ठा posix_acl *acl, पूर्णांक type);
बाह्य पूर्णांक ocfs2_acl_chmod(काष्ठा inode *, काष्ठा buffer_head *);
बाह्य पूर्णांक ocfs2_init_acl(handle_t *, काष्ठा inode *, काष्ठा inode *,
			  काष्ठा buffer_head *, काष्ठा buffer_head *,
			  काष्ठा ocfs2_alloc_context *,
			  काष्ठा ocfs2_alloc_context *);

#पूर्ण_अगर /* OCFS2_ACL_H */
