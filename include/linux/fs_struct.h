<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FS_STRUCT_H
#घोषणा _LINUX_FS_STRUCT_H

#समावेश <linux/path.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/seqlock.h>

काष्ठा fs_काष्ठा अणु
	पूर्णांक users;
	spinlock_t lock;
	seqcount_spinlock_t seq;
	पूर्णांक umask;
	पूर्णांक in_exec;
	काष्ठा path root, pwd;
पूर्ण __अक्रमomize_layout;

बाह्य काष्ठा kmem_cache *fs_cachep;

बाह्य व्योम निकास_fs(काष्ठा task_काष्ठा *);
बाह्य व्योम set_fs_root(काष्ठा fs_काष्ठा *, स्थिर काष्ठा path *);
बाह्य व्योम set_fs_pwd(काष्ठा fs_काष्ठा *, स्थिर काष्ठा path *);
बाह्य काष्ठा fs_काष्ठा *copy_fs_काष्ठा(काष्ठा fs_काष्ठा *);
बाह्य व्योम मुक्त_fs_काष्ठा(काष्ठा fs_काष्ठा *);
बाह्य पूर्णांक unshare_fs_काष्ठा(व्योम);

अटल अंतरभूत व्योम get_fs_root(काष्ठा fs_काष्ठा *fs, काष्ठा path *root)
अणु
	spin_lock(&fs->lock);
	*root = fs->root;
	path_get(root);
	spin_unlock(&fs->lock);
पूर्ण

अटल अंतरभूत व्योम get_fs_pwd(काष्ठा fs_काष्ठा *fs, काष्ठा path *pwd)
अणु
	spin_lock(&fs->lock);
	*pwd = fs->pwd;
	path_get(pwd);
	spin_unlock(&fs->lock);
पूर्ण

बाह्य bool current_chrooted(व्योम);

#पूर्ण_अगर /* _LINUX_FS_STRUCT_H */
