<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
  File: linux/posix_acl.h

  (C) 2002 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/


#अगर_अघोषित __LINUX_POSIX_ACL_H
#घोषणा __LINUX_POSIX_ACL_H

#समावेश <linux/bug.h>
#समावेश <linux/slab.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/refcount.h>
#समावेश <uapi/linux/posix_acl.h>

काष्ठा user_namespace;

काष्ठा posix_acl_entry अणु
	लघु			e_tag;
	अचिन्हित लघु		e_perm;
	जोड़ अणु
		kuid_t		e_uid;
		kgid_t		e_gid;
	पूर्ण;
पूर्ण;

काष्ठा posix_acl अणु
	refcount_t		a_refcount;
	काष्ठा rcu_head		a_rcu;
	अचिन्हित पूर्णांक		a_count;
	काष्ठा posix_acl_entry	a_entries[];
पूर्ण;

#घोषणा FOREACH_ACL_ENTRY(pa, acl, pe) \
	क्रम(pa=(acl)->a_entries, pe=pa+(acl)->a_count; pa<pe; pa++)


/*
 * Duplicate an ACL handle.
 */
अटल अंतरभूत काष्ठा posix_acl *
posix_acl_dup(काष्ठा posix_acl *acl)
अणु
	अगर (acl)
		refcount_inc(&acl->a_refcount);
	वापस acl;
पूर्ण

/*
 * Free an ACL handle.
 */
अटल अंतरभूत व्योम
posix_acl_release(काष्ठा posix_acl *acl)
अणु
	अगर (acl && refcount_dec_and_test(&acl->a_refcount))
		kमुक्त_rcu(acl, a_rcu);
पूर्ण


/* posix_acl.c */

बाह्य व्योम posix_acl_init(काष्ठा posix_acl *, पूर्णांक);
बाह्य काष्ठा posix_acl *posix_acl_alloc(पूर्णांक, gfp_t);
बाह्य काष्ठा posix_acl *posix_acl_from_mode(umode_t, gfp_t);
बाह्य पूर्णांक posix_acl_equiv_mode(स्थिर काष्ठा posix_acl *, umode_t *);
बाह्य पूर्णांक __posix_acl_create(काष्ठा posix_acl **, gfp_t, umode_t *);
बाह्य पूर्णांक __posix_acl_chmod(काष्ठा posix_acl **, gfp_t, umode_t);

बाह्य काष्ठा posix_acl *get_posix_acl(काष्ठा inode *, पूर्णांक);
बाह्य पूर्णांक set_posix_acl(काष्ठा user_namespace *, काष्ठा inode *, पूर्णांक,
			 काष्ठा posix_acl *);

#अगर_घोषित CONFIG_FS_POSIX_ACL
पूर्णांक posix_acl_chmod(काष्ठा user_namespace *, काष्ठा inode *, umode_t);
बाह्य पूर्णांक posix_acl_create(काष्ठा inode *, umode_t *, काष्ठा posix_acl **,
		काष्ठा posix_acl **);
पूर्णांक posix_acl_update_mode(काष्ठा user_namespace *, काष्ठा inode *, umode_t *,
			  काष्ठा posix_acl **);

बाह्य पूर्णांक simple_set_acl(काष्ठा user_namespace *, काष्ठा inode *,
			  काष्ठा posix_acl *, पूर्णांक);
बाह्य पूर्णांक simple_acl_create(काष्ठा inode *, काष्ठा inode *);

काष्ठा posix_acl *get_cached_acl(काष्ठा inode *inode, पूर्णांक type);
काष्ठा posix_acl *get_cached_acl_rcu(काष्ठा inode *inode, पूर्णांक type);
व्योम set_cached_acl(काष्ठा inode *inode, पूर्णांक type, काष्ठा posix_acl *acl);
व्योम क्रमget_cached_acl(काष्ठा inode *inode, पूर्णांक type);
व्योम क्रमget_all_cached_acls(काष्ठा inode *inode);
पूर्णांक posix_acl_valid(काष्ठा user_namespace *, स्थिर काष्ठा posix_acl *);
पूर्णांक posix_acl_permission(काष्ठा user_namespace *, काष्ठा inode *,
			 स्थिर काष्ठा posix_acl *, पूर्णांक);

अटल अंतरभूत व्योम cache_no_acl(काष्ठा inode *inode)
अणु
	inode->i_acl = शून्य;
	inode->i_शेष_acl = शून्य;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक posix_acl_chmod(काष्ठा user_namespace *mnt_userns,
				  काष्ठा inode *inode, umode_t mode)
अणु
	वापस 0;
पूर्ण

#घोषणा simple_set_acl		शून्य

अटल अंतरभूत पूर्णांक simple_acl_create(काष्ठा inode *dir, काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम cache_no_acl(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक posix_acl_create(काष्ठा inode *inode, umode_t *mode,
		काष्ठा posix_acl **शेष_acl, काष्ठा posix_acl **acl)
अणु
	*शेष_acl = *acl = शून्य;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम क्रमget_all_cached_acls(काष्ठा inode *inode)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_FS_POSIX_ACL */

काष्ठा posix_acl *get_acl(काष्ठा inode *inode, पूर्णांक type);

#पूर्ण_अगर  /* __LINUX_POSIX_ACL_H */
