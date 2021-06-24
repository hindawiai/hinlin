<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * xattr.h
 *
 * Copyright (C) 2004, 2008 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_XATTR_H
#घोषणा OCFS2_XATTR_H

#समावेश <linux/init.h>
#समावेश <linux/xattr.h>

क्रमागत ocfs2_xattr_type अणु
	OCFS2_XATTR_INDEX_USER = 1,
	OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS,
	OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT,
	OCFS2_XATTR_INDEX_TRUSTED,
	OCFS2_XATTR_INDEX_SECURITY,
	OCFS2_XATTR_MAX
पूर्ण;

काष्ठा ocfs2_security_xattr_info अणु
	पूर्णांक enable;
	स्थिर अक्षर *name;
	व्योम *value;
	माप_प्रकार value_len;
पूर्ण;

बाह्य स्थिर काष्ठा xattr_handler ocfs2_xattr_user_handler;
बाह्य स्थिर काष्ठा xattr_handler ocfs2_xattr_trusted_handler;
बाह्य स्थिर काष्ठा xattr_handler ocfs2_xattr_security_handler;
बाह्य स्थिर काष्ठा xattr_handler *ocfs2_xattr_handlers[];

sमाप_प्रकार ocfs2_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);
पूर्णांक ocfs2_xattr_get_nolock(काष्ठा inode *, काष्ठा buffer_head *, पूर्णांक,
			   स्थिर अक्षर *, व्योम *, माप_प्रकार);
पूर्णांक ocfs2_xattr_set(काष्ठा inode *, पूर्णांक, स्थिर अक्षर *, स्थिर व्योम *,
		    माप_प्रकार, पूर्णांक);
पूर्णांक ocfs2_xattr_set_handle(handle_t *, काष्ठा inode *, काष्ठा buffer_head *,
			   पूर्णांक, स्थिर अक्षर *, स्थिर व्योम *, माप_प्रकार, पूर्णांक,
			   काष्ठा ocfs2_alloc_context *,
			   काष्ठा ocfs2_alloc_context *);
पूर्णांक ocfs2_has_अंतरभूत_xattr_value_outside(काष्ठा inode *inode,
					 काष्ठा ocfs2_dinode *di);
पूर्णांक ocfs2_xattr_हटाओ(काष्ठा inode *, काष्ठा buffer_head *);
पूर्णांक ocfs2_init_security_get(काष्ठा inode *, काष्ठा inode *,
			    स्थिर काष्ठा qstr *,
			    काष्ठा ocfs2_security_xattr_info *);
पूर्णांक ocfs2_init_security_set(handle_t *, काष्ठा inode *,
			    काष्ठा buffer_head *,
			    काष्ठा ocfs2_security_xattr_info *,
			    काष्ठा ocfs2_alloc_context *,
			    काष्ठा ocfs2_alloc_context *);
पूर्णांक ocfs2_calc_security_init(काष्ठा inode *,
			     काष्ठा ocfs2_security_xattr_info *,
			     पूर्णांक *, पूर्णांक *, काष्ठा ocfs2_alloc_context **);
पूर्णांक ocfs2_calc_xattr_init(काष्ठा inode *, काष्ठा buffer_head *,
			  umode_t, काष्ठा ocfs2_security_xattr_info *,
			  पूर्णांक *, पूर्णांक *, पूर्णांक *);

/*
 * xattrs can live inside an inode, as part of an बाह्यal xattr block,
 * or inside an xattr bucket, which is the leaf of a tree rooted in an
 * xattr block.  Some of the xattr calls, especially the value setting
 * functions, want to treat each of these locations as equal.  Let's wrap
 * them in a काष्ठाure that we can pass around instead of raw buffer_heads.
 */
काष्ठा ocfs2_xattr_value_buf अणु
	काष्ठा buffer_head		*vb_bh;
	ocfs2_journal_access_func	vb_access;
	काष्ठा ocfs2_xattr_value_root	*vb_xv;
पूर्ण;

पूर्णांक ocfs2_xattr_attach_refcount_tree(काष्ठा inode *inode,
				     काष्ठा buffer_head *fe_bh,
				     काष्ठा ocfs2_caching_info *ref_ci,
				     काष्ठा buffer_head *ref_root_bh,
				     काष्ठा ocfs2_cached_dealloc_ctxt *dealloc);
पूर्णांक ocfs2_reflink_xattrs(काष्ठा inode *old_inode,
			 काष्ठा buffer_head *old_bh,
			 काष्ठा inode *new_inode,
			 काष्ठा buffer_head *new_bh,
			 bool preserve_security);
पूर्णांक ocfs2_init_security_and_acl(काष्ठा inode *dir,
				काष्ठा inode *inode,
				स्थिर काष्ठा qstr *qstr);
#पूर्ण_अगर /* OCFS2_XATTR_H */
