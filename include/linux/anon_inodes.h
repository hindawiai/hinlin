<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  include/linux/anon_inodes.h
 *
 *  Copyright (C) 2007  Davide Libenzi <davidel@xmailserver.org>
 *
 */

#अगर_अघोषित _LINUX_ANON_INODES_H
#घोषणा _LINUX_ANON_INODES_H

काष्ठा file_operations;
काष्ठा inode;

काष्ठा file *anon_inode_getfile(स्थिर अक्षर *name,
				स्थिर काष्ठा file_operations *fops,
				व्योम *priv, पूर्णांक flags);
पूर्णांक anon_inode_getfd(स्थिर अक्षर *name, स्थिर काष्ठा file_operations *fops,
		     व्योम *priv, पूर्णांक flags);
पूर्णांक anon_inode_getfd_secure(स्थिर अक्षर *name,
			    स्थिर काष्ठा file_operations *fops,
			    व्योम *priv, पूर्णांक flags,
			    स्थिर काष्ठा inode *context_inode);

#पूर्ण_अगर /* _LINUX_ANON_INODES_H */

