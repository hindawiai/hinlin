<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PROCFS_FD_H__
#घोषणा __PROCFS_FD_H__

#समावेश <linux/fs.h>

बाह्य स्थिर काष्ठा file_operations proc_fd_operations;
बाह्य स्थिर काष्ठा inode_operations proc_fd_inode_operations;

बाह्य स्थिर काष्ठा file_operations proc_fdinfo_operations;
बाह्य स्थिर काष्ठा inode_operations proc_fdinfo_inode_operations;

बाह्य पूर्णांक proc_fd_permission(काष्ठा user_namespace *mnt_userns,
			      काष्ठा inode *inode, पूर्णांक mask);

अटल अंतरभूत अचिन्हित पूर्णांक proc_fd(काष्ठा inode *inode)
अणु
	वापस PROC_I(inode)->fd;
पूर्ण

#पूर्ण_अगर /* __PROCFS_FD_H__ */
