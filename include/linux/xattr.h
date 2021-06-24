<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
  File: linux/xattr.h

  Extended attributes handling.

  Copyright (C) 2001 by Andreas Gruenbacher <a.gruenbacher@computer.org>
  Copyright (c) 2001-2002 Silicon Graphics, Inc.  All Rights Reserved.
  Copyright (c) 2004 Red Hat, Inc., James Morris <jmorris@redhat.com>
*/
#अगर_अघोषित _LINUX_XATTR_H
#घोषणा _LINUX_XATTR_H


#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/user_namespace.h>
#समावेश <uapi/linux/xattr.h>

काष्ठा inode;
काष्ठा dentry;

/*
 * काष्ठा xattr_handler: When @name is set, match attributes with exactly that
 * name.  When @prefix is set instead, match attributes with that prefix and
 * with a non-empty suffix.
 */
काष्ठा xattr_handler अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *prefix;
	पूर्णांक flags;      /* fs निजी flags */
	bool (*list)(काष्ठा dentry *dentry);
	पूर्णांक (*get)(स्थिर काष्ठा xattr_handler *, काष्ठा dentry *dentry,
		   काष्ठा inode *inode, स्थिर अक्षर *name, व्योम *buffer,
		   माप_प्रकार size);
	पूर्णांक (*set)(स्थिर काष्ठा xattr_handler *,
		   काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		   काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *buffer,
		   माप_प्रकार size, पूर्णांक flags);
पूर्ण;

स्थिर अक्षर *xattr_full_name(स्थिर काष्ठा xattr_handler *, स्थिर अक्षर *);

काष्ठा xattr अणु
	स्थिर अक्षर *name;
	व्योम *value;
	माप_प्रकार value_len;
पूर्ण;

sमाप_प्रकार __vfs_getxattr(काष्ठा dentry *, काष्ठा inode *, स्थिर अक्षर *, व्योम *, माप_प्रकार);
sमाप_प्रकार vfs_getxattr(काष्ठा user_namespace *, काष्ठा dentry *, स्थिर अक्षर *,
		     व्योम *, माप_प्रकार);
sमाप_प्रकार vfs_listxattr(काष्ठा dentry *d, अक्षर *list, माप_प्रकार size);
पूर्णांक __vfs_setxattr(काष्ठा user_namespace *, काष्ठा dentry *, काष्ठा inode *,
		   स्थिर अक्षर *, स्थिर व्योम *, माप_प्रकार, पूर्णांक);
पूर्णांक __vfs_setxattr_noperm(काष्ठा user_namespace *, काष्ठा dentry *,
			  स्थिर अक्षर *, स्थिर व्योम *, माप_प्रकार, पूर्णांक);
पूर्णांक __vfs_setxattr_locked(काष्ठा user_namespace *, काष्ठा dentry *,
			  स्थिर अक्षर *, स्थिर व्योम *, माप_प्रकार, पूर्णांक,
			  काष्ठा inode **);
पूर्णांक vfs_setxattr(काष्ठा user_namespace *, काष्ठा dentry *, स्थिर अक्षर *,
		 स्थिर व्योम *, माप_प्रकार, पूर्णांक);
पूर्णांक __vfs_हटाओxattr(काष्ठा user_namespace *, काष्ठा dentry *, स्थिर अक्षर *);
पूर्णांक __vfs_हटाओxattr_locked(काष्ठा user_namespace *, काष्ठा dentry *,
			     स्थिर अक्षर *, काष्ठा inode **);
पूर्णांक vfs_हटाओxattr(काष्ठा user_namespace *, काष्ठा dentry *, स्थिर अक्षर *);

sमाप_प्रकार generic_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार buffer_size);
sमाप_प्रकार vfs_getxattr_alloc(काष्ठा user_namespace *mnt_userns,
			   काष्ठा dentry *dentry, स्थिर अक्षर *name,
			   अक्षर **xattr_value, माप_प्रकार size, gfp_t flags);

पूर्णांक xattr_supported_namespace(काष्ठा inode *inode, स्थिर अक्षर *prefix);

अटल अंतरभूत स्थिर अक्षर *xattr_prefix(स्थिर काष्ठा xattr_handler *handler)
अणु
	वापस handler->prefix ?: handler->name;
पूर्ण

काष्ठा simple_xattrs अणु
	काष्ठा list_head head;
	spinlock_t lock;
पूर्ण;

काष्ठा simple_xattr अणु
	काष्ठा list_head list;
	अक्षर *name;
	माप_प्रकार size;
	अक्षर value[];
पूर्ण;

/*
 * initialize the simple_xattrs काष्ठाure
 */
अटल अंतरभूत व्योम simple_xattrs_init(काष्ठा simple_xattrs *xattrs)
अणु
	INIT_LIST_HEAD(&xattrs->head);
	spin_lock_init(&xattrs->lock);
पूर्ण

/*
 * मुक्त all the xattrs
 */
अटल अंतरभूत व्योम simple_xattrs_मुक्त(काष्ठा simple_xattrs *xattrs)
अणु
	काष्ठा simple_xattr *xattr, *node;

	list_क्रम_each_entry_safe(xattr, node, &xattrs->head, list) अणु
		kमुक्त(xattr->name);
		kvमुक्त(xattr);
	पूर्ण
पूर्ण

काष्ठा simple_xattr *simple_xattr_alloc(स्थिर व्योम *value, माप_प्रकार size);
पूर्णांक simple_xattr_get(काष्ठा simple_xattrs *xattrs, स्थिर अक्षर *name,
		     व्योम *buffer, माप_प्रकार size);
पूर्णांक simple_xattr_set(काष्ठा simple_xattrs *xattrs, स्थिर अक्षर *name,
		     स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags,
		     sमाप_प्रकार *हटाओd_size);
sमाप_प्रकार simple_xattr_list(काष्ठा inode *inode, काष्ठा simple_xattrs *xattrs, अक्षर *buffer,
			  माप_प्रकार size);
व्योम simple_xattr_list_add(काष्ठा simple_xattrs *xattrs,
			   काष्ठा simple_xattr *new_xattr);

#पूर्ण_अगर	/* _LINUX_XATTR_H */
