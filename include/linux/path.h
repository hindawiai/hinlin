<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PATH_H
#घोषणा _LINUX_PATH_H

काष्ठा dentry;
काष्ठा vfsmount;

काष्ठा path अणु
	काष्ठा vfsmount *mnt;
	काष्ठा dentry *dentry;
पूर्ण __अक्रमomize_layout;

बाह्य व्योम path_get(स्थिर काष्ठा path *);
बाह्य व्योम path_put(स्थिर काष्ठा path *);

अटल अंतरभूत पूर्णांक path_equal(स्थिर काष्ठा path *path1, स्थिर काष्ठा path *path2)
अणु
	वापस path1->mnt == path2->mnt && path1->dentry == path2->dentry;
पूर्ण

अटल अंतरभूत व्योम path_put_init(काष्ठा path *path)
अणु
	path_put(path);
	*path = (काष्ठा path) अणु पूर्ण;
पूर्ण

#पूर्ण_अगर  /* _LINUX_PATH_H */
