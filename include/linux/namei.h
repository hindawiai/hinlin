<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_NAMEI_H
#घोषणा _LINUX_NAMEI_H

#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/path.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/त्रुटिसं.स>

क्रमागत अणु MAX_NESTED_LINKS = 8 पूर्ण;

#घोषणा MAXSYMLINKS 40

/*
 * Type of the last component on LOOKUP_PARENT
 */
क्रमागत अणुLAST_NORM, LAST_ROOT, LAST_DOT, LAST_DOTDOTपूर्ण;

/* pathwalk mode */
#घोषणा LOOKUP_FOLLOW		0x0001	/* follow links at the end */
#घोषणा LOOKUP_सूचीECTORY	0x0002	/* require a directory */
#घोषणा LOOKUP_AUTOMOUNT	0x0004  /* क्रमce terminal स्वतःmount */
#घोषणा LOOKUP_EMPTY		0x4000	/* accept empty path [user_... only] */
#घोषणा LOOKUP_DOWN		0x8000	/* follow mounts in the starting poपूर्णांक */
#घोषणा LOOKUP_MOUNTPOINT	0x0080	/* follow mounts in the end */

#घोषणा LOOKUP_REVAL		0x0020	/* tell ->d_revalidate() to trust no cache */
#घोषणा LOOKUP_RCU		0x0040	/* RCU pathwalk mode; semi-पूर्णांकernal */

/* These tell fileप्रणाली methods that we are dealing with the final component... */
#घोषणा LOOKUP_OPEN		0x0100	/* ... in खोलो */
#घोषणा LOOKUP_CREATE		0x0200	/* ... in object creation */
#घोषणा LOOKUP_EXCL		0x0400	/* ... in exclusive creation */
#घोषणा LOOKUP_RENAME_TARGET	0x0800	/* ... in destination of नाम() */

/* पूर्णांकernal use only */
#घोषणा LOOKUP_PARENT		0x0010
#घोषणा LOOKUP_JUMPED		0x1000
#घोषणा LOOKUP_ROOT		0x2000
#घोषणा LOOKUP_ROOT_GRABBED	0x0008

/* Scoping flags क्रम lookup. */
#घोषणा LOOKUP_NO_SYMLINKS	0x010000 /* No symlink crossing. */
#घोषणा LOOKUP_NO_MAGICLINKS	0x020000 /* No nd_jump_link() crossing. */
#घोषणा LOOKUP_NO_XDEV		0x040000 /* No mountpoपूर्णांक crossing. */
#घोषणा LOOKUP_BENEATH		0x080000 /* No escaping from starting poपूर्णांक. */
#घोषणा LOOKUP_IN_ROOT		0x100000 /* Treat dirfd as fs root. */
#घोषणा LOOKUP_CACHED		0x200000 /* Only करो cached lookup */
/* LOOKUP_* flags which करो scope-related checks based on the dirfd. */
#घोषणा LOOKUP_IS_SCOPED (LOOKUP_BENEATH | LOOKUP_IN_ROOT)

बाह्य पूर्णांक path_pts(काष्ठा path *path);

बाह्य पूर्णांक user_path_at_empty(पूर्णांक, स्थिर अक्षर __user *, अचिन्हित, काष्ठा path *, पूर्णांक *empty);

अटल अंतरभूत पूर्णांक user_path_at(पूर्णांक dfd, स्थिर अक्षर __user *name, अचिन्हित flags,
		 काष्ठा path *path)
अणु
	वापस user_path_at_empty(dfd, name, flags, path, शून्य);
पूर्ण

बाह्य पूर्णांक kern_path(स्थिर अक्षर *, अचिन्हित, काष्ठा path *);

बाह्य काष्ठा dentry *kern_path_create(पूर्णांक, स्थिर अक्षर *, काष्ठा path *, अचिन्हित पूर्णांक);
बाह्य काष्ठा dentry *user_path_create(पूर्णांक, स्थिर अक्षर __user *, काष्ठा path *, अचिन्हित पूर्णांक);
बाह्य व्योम करोne_path_create(काष्ठा path *, काष्ठा dentry *);
बाह्य काष्ठा dentry *kern_path_locked(स्थिर अक्षर *, काष्ठा path *);

बाह्य काष्ठा dentry *try_lookup_one_len(स्थिर अक्षर *, काष्ठा dentry *, पूर्णांक);
बाह्य काष्ठा dentry *lookup_one_len(स्थिर अक्षर *, काष्ठा dentry *, पूर्णांक);
बाह्य काष्ठा dentry *lookup_one_len_unlocked(स्थिर अक्षर *, काष्ठा dentry *, पूर्णांक);
बाह्य काष्ठा dentry *lookup_positive_unlocked(स्थिर अक्षर *, काष्ठा dentry *, पूर्णांक);

बाह्य पूर्णांक follow_करोwn_one(काष्ठा path *);
बाह्य पूर्णांक follow_करोwn(काष्ठा path *);
बाह्य पूर्णांक follow_up(काष्ठा path *);

बाह्य काष्ठा dentry *lock_नाम(काष्ठा dentry *, काष्ठा dentry *);
बाह्य व्योम unlock_नाम(काष्ठा dentry *, काष्ठा dentry *);

बाह्य पूर्णांक __must_check nd_jump_link(काष्ठा path *path);

अटल अंतरभूत व्योम nd_terminate_link(व्योम *name, माप_प्रकार len, माप_प्रकार maxlen)
अणु
	((अक्षर *) name)[min(len, maxlen)] = '\0';
पूर्ण

/**
 * retry_estale - determine whether the caller should retry an operation
 * @error: the error that would currently be वापसed
 * @flags: flags being used क्रम next lookup attempt
 *
 * Check to see अगर the error code was -ESTALE, and then determine whether
 * to retry the call based on whether "flags" alपढ़ोy has LOOKUP_REVAL set.
 *
 * Returns true अगर the caller should try the operation again.
 */
अटल अंतरभूत bool
retry_estale(स्थिर दीर्घ error, स्थिर अचिन्हित पूर्णांक flags)
अणु
	वापस error == -ESTALE && !(flags & LOOKUP_REVAL);
पूर्ण

#पूर्ण_अगर /* _LINUX_NAMEI_H */
