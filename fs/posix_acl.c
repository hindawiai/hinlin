<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2002,2003 by Andreas Gruenbacher <a.gruenbacher@computer.org>
 *
 * Fixes from William Schumacher incorporated on 15 March 2001.
 *    (Reported by Charles Bertsch, <CBertsch@microtest.com>).
 */

/*
 *  This file contains generic functions क्रम manipulating
 *  POSIX 1003.1e draft standard 17 ACLs.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/xattr.h>
#समावेश <linux/export.h>
#समावेश <linux/user_namespace.h>

अटल काष्ठा posix_acl **acl_by_type(काष्ठा inode *inode, पूर्णांक type)
अणु
	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		वापस &inode->i_acl;
	हाल ACL_TYPE_DEFAULT:
		वापस &inode->i_शेष_acl;
	शेष:
		BUG();
	पूर्ण
पूर्ण

काष्ठा posix_acl *get_cached_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा posix_acl **p = acl_by_type(inode, type);
	काष्ठा posix_acl *acl;

	क्रम (;;) अणु
		rcu_पढ़ो_lock();
		acl = rcu_dereference(*p);
		अगर (!acl || is_uncached_acl(acl) ||
		    refcount_inc_not_zero(&acl->a_refcount))
			अवरोध;
		rcu_पढ़ो_unlock();
		cpu_relax();
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस acl;
पूर्ण
EXPORT_SYMBOL(get_cached_acl);

काष्ठा posix_acl *get_cached_acl_rcu(काष्ठा inode *inode, पूर्णांक type)
अणु
	वापस rcu_dereference(*acl_by_type(inode, type));
पूर्ण
EXPORT_SYMBOL(get_cached_acl_rcu);

व्योम set_cached_acl(काष्ठा inode *inode, पूर्णांक type, काष्ठा posix_acl *acl)
अणु
	काष्ठा posix_acl **p = acl_by_type(inode, type);
	काष्ठा posix_acl *old;

	old = xchg(p, posix_acl_dup(acl));
	अगर (!is_uncached_acl(old))
		posix_acl_release(old);
पूर्ण
EXPORT_SYMBOL(set_cached_acl);

अटल व्योम __क्रमget_cached_acl(काष्ठा posix_acl **p)
अणु
	काष्ठा posix_acl *old;

	old = xchg(p, ACL_NOT_CACHED);
	अगर (!is_uncached_acl(old))
		posix_acl_release(old);
पूर्ण

व्योम क्रमget_cached_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	__क्रमget_cached_acl(acl_by_type(inode, type));
पूर्ण
EXPORT_SYMBOL(क्रमget_cached_acl);

व्योम क्रमget_all_cached_acls(काष्ठा inode *inode)
अणु
	__क्रमget_cached_acl(&inode->i_acl);
	__क्रमget_cached_acl(&inode->i_शेष_acl);
पूर्ण
EXPORT_SYMBOL(क्रमget_all_cached_acls);

काष्ठा posix_acl *get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	व्योम *sentinel;
	काष्ठा posix_acl **p;
	काष्ठा posix_acl *acl;

	/*
	 * The sentinel is used to detect when another operation like
	 * set_cached_acl() or क्रमget_cached_acl() races with get_acl().
	 * It is guaranteed that is_uncached_acl(sentinel) is true.
	 */

	acl = get_cached_acl(inode, type);
	अगर (!is_uncached_acl(acl))
		वापस acl;

	अगर (!IS_POSIXACL(inode))
		वापस शून्य;

	sentinel = uncached_acl_sentinel(current);
	p = acl_by_type(inode, type);

	/*
	 * If the ACL isn't being पढ़ो yet, set our sentinel.  Otherwise, the
	 * current value of the ACL will not be ACL_NOT_CACHED and so our own
	 * sentinel will not be set; another task will update the cache.  We
	 * could रुको क्रम that other task to complete its job, but it's easier
	 * to just call ->get_acl to fetch the ACL ourself.  (This is going to
	 * be an unlikely race.)
	 */
	अगर (cmpxchg(p, ACL_NOT_CACHED, sentinel) != ACL_NOT_CACHED)
		/* fall through */ ;

	/*
	 * Normally, the ACL वापसed by ->get_acl will be cached.
	 * A fileप्रणाली can prevent that by calling
	 * क्रमget_cached_acl(inode, type) in ->get_acl.
	 *
	 * If the fileप्रणाली करोesn't have a get_acl() function at all, we'll
	 * just create the negative cache entry.
	 */
	अगर (!inode->i_op->get_acl) अणु
		set_cached_acl(inode, type, शून्य);
		वापस शून्य;
	पूर्ण
	acl = inode->i_op->get_acl(inode, type);

	अगर (IS_ERR(acl)) अणु
		/*
		 * Remove our sentinel so that we करोn't block future attempts
		 * to cache the ACL.
		 */
		cmpxchg(p, sentinel, ACL_NOT_CACHED);
		वापस acl;
	पूर्ण

	/*
	 * Cache the result, but only अगर our sentinel is still in place.
	 */
	posix_acl_dup(acl);
	अगर (unlikely(cmpxchg(p, sentinel, acl) != sentinel))
		posix_acl_release(acl);
	वापस acl;
पूर्ण
EXPORT_SYMBOL(get_acl);

/*
 * Init a fresh posix_acl
 */
व्योम
posix_acl_init(काष्ठा posix_acl *acl, पूर्णांक count)
अणु
	refcount_set(&acl->a_refcount, 1);
	acl->a_count = count;
पूर्ण
EXPORT_SYMBOL(posix_acl_init);

/*
 * Allocate a new ACL with the specअगरied number of entries.
 */
काष्ठा posix_acl *
posix_acl_alloc(पूर्णांक count, gfp_t flags)
अणु
	स्थिर माप_प्रकार size = माप(काष्ठा posix_acl) +
	                    count * माप(काष्ठा posix_acl_entry);
	काष्ठा posix_acl *acl = kदो_स्मृति(size, flags);
	अगर (acl)
		posix_acl_init(acl, count);
	वापस acl;
पूर्ण
EXPORT_SYMBOL(posix_acl_alloc);

/*
 * Clone an ACL.
 */
अटल काष्ठा posix_acl *
posix_acl_clone(स्थिर काष्ठा posix_acl *acl, gfp_t flags)
अणु
	काष्ठा posix_acl *clone = शून्य;

	अगर (acl) अणु
		पूर्णांक size = माप(काष्ठा posix_acl) + acl->a_count *
		           माप(काष्ठा posix_acl_entry);
		clone = kmemdup(acl, size, flags);
		अगर (clone)
			refcount_set(&clone->a_refcount, 1);
	पूर्ण
	वापस clone;
पूर्ण

/*
 * Check अगर an acl is valid. Returns 0 अगर it is, or -E... otherwise.
 */
पूर्णांक
posix_acl_valid(काष्ठा user_namespace *user_ns, स्थिर काष्ठा posix_acl *acl)
अणु
	स्थिर काष्ठा posix_acl_entry *pa, *pe;
	पूर्णांक state = ACL_USER_OBJ;
	पूर्णांक needs_mask = 0;

	FOREACH_ACL_ENTRY(pa, acl, pe) अणु
		अगर (pa->e_perm & ~(ACL_READ|ACL_WRITE|ACL_EXECUTE))
			वापस -EINVAL;
		चयन (pa->e_tag) अणु
			हाल ACL_USER_OBJ:
				अगर (state == ACL_USER_OBJ) अणु
					state = ACL_USER;
					अवरोध;
				पूर्ण
				वापस -EINVAL;

			हाल ACL_USER:
				अगर (state != ACL_USER)
					वापस -EINVAL;
				अगर (!kuid_has_mapping(user_ns, pa->e_uid))
					वापस -EINVAL;
				needs_mask = 1;
				अवरोध;

			हाल ACL_GROUP_OBJ:
				अगर (state == ACL_USER) अणु
					state = ACL_GROUP;
					अवरोध;
				पूर्ण
				वापस -EINVAL;

			हाल ACL_GROUP:
				अगर (state != ACL_GROUP)
					वापस -EINVAL;
				अगर (!kgid_has_mapping(user_ns, pa->e_gid))
					वापस -EINVAL;
				needs_mask = 1;
				अवरोध;

			हाल ACL_MASK:
				अगर (state != ACL_GROUP)
					वापस -EINVAL;
				state = ACL_OTHER;
				अवरोध;

			हाल ACL_OTHER:
				अगर (state == ACL_OTHER ||
				    (state == ACL_GROUP && !needs_mask)) अणु
					state = 0;
					अवरोध;
				पूर्ण
				वापस -EINVAL;

			शेष:
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (state == 0)
		वापस 0;
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(posix_acl_valid);

/*
 * Returns 0 अगर the acl can be exactly represented in the traditional
 * file mode permission bits, or अन्यथा 1. Returns -E... on error.
 */
पूर्णांक
posix_acl_equiv_mode(स्थिर काष्ठा posix_acl *acl, umode_t *mode_p)
अणु
	स्थिर काष्ठा posix_acl_entry *pa, *pe;
	umode_t mode = 0;
	पूर्णांक not_equiv = 0;

	/*
	 * A null ACL can always be presented as mode bits.
	 */
	अगर (!acl)
		वापस 0;

	FOREACH_ACL_ENTRY(pa, acl, pe) अणु
		चयन (pa->e_tag) अणु
			हाल ACL_USER_OBJ:
				mode |= (pa->e_perm & S_IRWXO) << 6;
				अवरोध;
			हाल ACL_GROUP_OBJ:
				mode |= (pa->e_perm & S_IRWXO) << 3;
				अवरोध;
			हाल ACL_OTHER:
				mode |= pa->e_perm & S_IRWXO;
				अवरोध;
			हाल ACL_MASK:
				mode = (mode & ~S_IRWXG) |
				       ((pa->e_perm & S_IRWXO) << 3);
				not_equiv = 1;
				अवरोध;
			हाल ACL_USER:
			हाल ACL_GROUP:
				not_equiv = 1;
				अवरोध;
			शेष:
				वापस -EINVAL;
		पूर्ण
	पूर्ण
        अगर (mode_p)
                *mode_p = (*mode_p & ~S_IRWXUGO) | mode;
        वापस not_equiv;
पूर्ण
EXPORT_SYMBOL(posix_acl_equiv_mode);

/*
 * Create an ACL representing the file mode permission bits of an inode.
 */
काष्ठा posix_acl *
posix_acl_from_mode(umode_t mode, gfp_t flags)
अणु
	काष्ठा posix_acl *acl = posix_acl_alloc(3, flags);
	अगर (!acl)
		वापस ERR_PTR(-ENOMEM);

	acl->a_entries[0].e_tag  = ACL_USER_OBJ;
	acl->a_entries[0].e_perm = (mode & S_IRWXU) >> 6;

	acl->a_entries[1].e_tag  = ACL_GROUP_OBJ;
	acl->a_entries[1].e_perm = (mode & S_IRWXG) >> 3;

	acl->a_entries[2].e_tag  = ACL_OTHER;
	acl->a_entries[2].e_perm = (mode & S_IRWXO);
	वापस acl;
पूर्ण
EXPORT_SYMBOL(posix_acl_from_mode);

/*
 * Return 0 अगर current is granted want access to the inode
 * by the acl. Returns -E... otherwise.
 */
पूर्णांक
posix_acl_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		     स्थिर काष्ठा posix_acl *acl, पूर्णांक want)
अणु
	स्थिर काष्ठा posix_acl_entry *pa, *pe, *mask_obj;
	पूर्णांक found = 0;
	kuid_t uid;
	kgid_t gid;

	want &= MAY_READ | MAY_WRITE | MAY_EXEC;

	FOREACH_ACL_ENTRY(pa, acl, pe) अणु
                चयन(pa->e_tag) अणु
                        हाल ACL_USER_OBJ:
				/* (May have been checked alपढ़ोy) */
				uid = i_uid_पूर्णांकo_mnt(mnt_userns, inode);
				अगर (uid_eq(uid, current_fsuid()))
                                        जाओ check_perm;
                                अवरोध;
                        हाल ACL_USER:
				uid = kuid_पूर्णांकo_mnt(mnt_userns, pa->e_uid);
				अगर (uid_eq(uid, current_fsuid()))
                                        जाओ mask;
				अवरोध;
                        हाल ACL_GROUP_OBJ:
				gid = i_gid_पूर्णांकo_mnt(mnt_userns, inode);
				अगर (in_group_p(gid)) अणु
					found = 1;
					अगर ((pa->e_perm & want) == want)
						जाओ mask;
                                पूर्ण
				अवरोध;
                        हाल ACL_GROUP:
				gid = kgid_पूर्णांकo_mnt(mnt_userns, pa->e_gid);
				अगर (in_group_p(gid)) अणु
					found = 1;
					अगर ((pa->e_perm & want) == want)
						जाओ mask;
                                पूर्ण
                                अवरोध;
                        हाल ACL_MASK:
                                अवरोध;
                        हाल ACL_OTHER:
				अगर (found)
					वापस -EACCES;
				अन्यथा
					जाओ check_perm;
			शेष:
				वापस -EIO;
                पूर्ण
        पूर्ण
	वापस -EIO;

mask:
	क्रम (mask_obj = pa+1; mask_obj != pe; mask_obj++) अणु
		अगर (mask_obj->e_tag == ACL_MASK) अणु
			अगर ((pa->e_perm & mask_obj->e_perm & want) == want)
				वापस 0;
			वापस -EACCES;
		पूर्ण
	पूर्ण

check_perm:
	अगर ((pa->e_perm & want) == want)
		वापस 0;
	वापस -EACCES;
पूर्ण

/*
 * Modअगरy acl when creating a new inode. The caller must ensure the acl is
 * only referenced once.
 *
 * mode_p initially must contain the mode parameter to the खोलो() / creat()
 * प्रणाली calls. All permissions that are not granted by the acl are हटाओd.
 * The permissions in the acl are changed to reflect the mode_p parameter.
 */
अटल पूर्णांक posix_acl_create_masq(काष्ठा posix_acl *acl, umode_t *mode_p)
अणु
	काष्ठा posix_acl_entry *pa, *pe;
	काष्ठा posix_acl_entry *group_obj = शून्य, *mask_obj = शून्य;
	umode_t mode = *mode_p;
	पूर्णांक not_equiv = 0;

	/* निश्चित(atomic_पढ़ो(acl->a_refcount) == 1); */

	FOREACH_ACL_ENTRY(pa, acl, pe) अणु
                चयन(pa->e_tag) अणु
                        हाल ACL_USER_OBJ:
				pa->e_perm &= (mode >> 6) | ~S_IRWXO;
				mode &= (pa->e_perm << 6) | ~S_IRWXU;
				अवरोध;

			हाल ACL_USER:
			हाल ACL_GROUP:
				not_equiv = 1;
				अवरोध;

                        हाल ACL_GROUP_OBJ:
				group_obj = pa;
                                अवरोध;

                        हाल ACL_OTHER:
				pa->e_perm &= mode | ~S_IRWXO;
				mode &= pa->e_perm | ~S_IRWXO;
                                अवरोध;

                        हाल ACL_MASK:
				mask_obj = pa;
				not_equiv = 1;
                                अवरोध;

			शेष:
				वापस -EIO;
                पूर्ण
        पूर्ण

	अगर (mask_obj) अणु
		mask_obj->e_perm &= (mode >> 3) | ~S_IRWXO;
		mode &= (mask_obj->e_perm << 3) | ~S_IRWXG;
	पूर्ण अन्यथा अणु
		अगर (!group_obj)
			वापस -EIO;
		group_obj->e_perm &= (mode >> 3) | ~S_IRWXO;
		mode &= (group_obj->e_perm << 3) | ~S_IRWXG;
	पूर्ण

	*mode_p = (*mode_p & ~S_IRWXUGO) | mode;
        वापस not_equiv;
पूर्ण

/*
 * Modअगरy the ACL क्रम the chmod syscall.
 */
अटल पूर्णांक __posix_acl_chmod_masq(काष्ठा posix_acl *acl, umode_t mode)
अणु
	काष्ठा posix_acl_entry *group_obj = शून्य, *mask_obj = शून्य;
	काष्ठा posix_acl_entry *pa, *pe;

	/* निश्चित(atomic_पढ़ो(acl->a_refcount) == 1); */

	FOREACH_ACL_ENTRY(pa, acl, pe) अणु
		चयन(pa->e_tag) अणु
			हाल ACL_USER_OBJ:
				pa->e_perm = (mode & S_IRWXU) >> 6;
				अवरोध;

			हाल ACL_USER:
			हाल ACL_GROUP:
				अवरोध;

			हाल ACL_GROUP_OBJ:
				group_obj = pa;
				अवरोध;

			हाल ACL_MASK:
				mask_obj = pa;
				अवरोध;

			हाल ACL_OTHER:
				pa->e_perm = (mode & S_IRWXO);
				अवरोध;

			शेष:
				वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (mask_obj) अणु
		mask_obj->e_perm = (mode & S_IRWXG) >> 3;
	पूर्ण अन्यथा अणु
		अगर (!group_obj)
			वापस -EIO;
		group_obj->e_perm = (mode & S_IRWXG) >> 3;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
__posix_acl_create(काष्ठा posix_acl **acl, gfp_t gfp, umode_t *mode_p)
अणु
	काष्ठा posix_acl *clone = posix_acl_clone(*acl, gfp);
	पूर्णांक err = -ENOMEM;
	अगर (clone) अणु
		err = posix_acl_create_masq(clone, mode_p);
		अगर (err < 0) अणु
			posix_acl_release(clone);
			clone = शून्य;
		पूर्ण
	पूर्ण
	posix_acl_release(*acl);
	*acl = clone;
	वापस err;
पूर्ण
EXPORT_SYMBOL(__posix_acl_create);

पूर्णांक
__posix_acl_chmod(काष्ठा posix_acl **acl, gfp_t gfp, umode_t mode)
अणु
	काष्ठा posix_acl *clone = posix_acl_clone(*acl, gfp);
	पूर्णांक err = -ENOMEM;
	अगर (clone) अणु
		err = __posix_acl_chmod_masq(clone, mode);
		अगर (err) अणु
			posix_acl_release(clone);
			clone = शून्य;
		पूर्ण
	पूर्ण
	posix_acl_release(*acl);
	*acl = clone;
	वापस err;
पूर्ण
EXPORT_SYMBOL(__posix_acl_chmod);

/**
 * posix_acl_chmod - chmod a posix acl
 *
 * @mnt_userns:	user namespace of the mount @inode was found from
 * @inode:	inode to check permissions on
 * @mode:	the new mode of @inode
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 */
पूर्णांक
 posix_acl_chmod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		    umode_t mode)
अणु
	काष्ठा posix_acl *acl;
	पूर्णांक ret = 0;

	अगर (!IS_POSIXACL(inode))
		वापस 0;
	अगर (!inode->i_op->set_acl)
		वापस -EOPNOTSUPP;

	acl = get_acl(inode, ACL_TYPE_ACCESS);
	अगर (IS_ERR_OR_शून्य(acl)) अणु
		अगर (acl == ERR_PTR(-EOPNOTSUPP))
			वापस 0;
		वापस PTR_ERR(acl);
	पूर्ण

	ret = __posix_acl_chmod(&acl, GFP_KERNEL, mode);
	अगर (ret)
		वापस ret;
	ret = inode->i_op->set_acl(mnt_userns, inode, acl, ACL_TYPE_ACCESS);
	posix_acl_release(acl);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(posix_acl_chmod);

पूर्णांक
posix_acl_create(काष्ठा inode *dir, umode_t *mode,
		काष्ठा posix_acl **शेष_acl, काष्ठा posix_acl **acl)
अणु
	काष्ठा posix_acl *p;
	काष्ठा posix_acl *clone;
	पूर्णांक ret;

	*acl = शून्य;
	*शेष_acl = शून्य;

	अगर (S_ISLNK(*mode) || !IS_POSIXACL(dir))
		वापस 0;

	p = get_acl(dir, ACL_TYPE_DEFAULT);
	अगर (!p || p == ERR_PTR(-EOPNOTSUPP)) अणु
		*mode &= ~current_umask();
		वापस 0;
	पूर्ण
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	ret = -ENOMEM;
	clone = posix_acl_clone(p, GFP_NOFS);
	अगर (!clone)
		जाओ err_release;

	ret = posix_acl_create_masq(clone, mode);
	अगर (ret < 0)
		जाओ err_release_clone;

	अगर (ret == 0)
		posix_acl_release(clone);
	अन्यथा
		*acl = clone;

	अगर (!S_ISसूची(*mode))
		posix_acl_release(p);
	अन्यथा
		*शेष_acl = p;

	वापस 0;

err_release_clone:
	posix_acl_release(clone);
err_release:
	posix_acl_release(p);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(posix_acl_create);

/**
 * posix_acl_update_mode  -  update mode in set_acl
 * @mnt_userns:	user namespace of the mount @inode was found from
 * @inode:	target inode
 * @mode_p:	mode (poपूर्णांकer) क्रम update
 * @acl:	acl poपूर्णांकer
 *
 * Update the file mode when setting an ACL: compute the new file permission
 * bits based on the ACL.  In addition, अगर the ACL is equivalent to the new
 * file mode, set *@acl to शून्य to indicate that no ACL should be set.
 *
 * As with chmod, clear the setgid bit अगर the caller is not in the owning group
 * or capable of CAP_FSETID (see inode_change_ok).
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 *
 * Called from set_acl inode operations.
 */
पूर्णांक posix_acl_update_mode(काष्ठा user_namespace *mnt_userns,
			  काष्ठा inode *inode, umode_t *mode_p,
			  काष्ठा posix_acl **acl)
अणु
	umode_t mode = inode->i_mode;
	पूर्णांक error;

	error = posix_acl_equiv_mode(*acl, &mode);
	अगर (error < 0)
		वापस error;
	अगर (error == 0)
		*acl = शून्य;
	अगर (!in_group_p(i_gid_पूर्णांकo_mnt(mnt_userns, inode)) &&
	    !capable_wrt_inode_uidgid(mnt_userns, inode, CAP_FSETID))
		mode &= ~S_ISGID;
	*mode_p = mode;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(posix_acl_update_mode);

/*
 * Fix up the uids and gids in posix acl extended attributes in place.
 */
अटल व्योम posix_acl_fix_xattr_userns(
	काष्ठा user_namespace *to, काष्ठा user_namespace *from,
	काष्ठा user_namespace *mnt_userns,
	व्योम *value, माप_प्रकार size, bool from_user)
अणु
	काष्ठा posix_acl_xattr_header *header = value;
	काष्ठा posix_acl_xattr_entry *entry = (व्योम *)(header + 1), *end;
	पूर्णांक count;
	kuid_t uid;
	kgid_t gid;

	अगर (!value)
		वापस;
	अगर (size < माप(काष्ठा posix_acl_xattr_header))
		वापस;
	अगर (header->a_version != cpu_to_le32(POSIX_ACL_XATTR_VERSION))
		वापस;

	count = posix_acl_xattr_count(size);
	अगर (count < 0)
		वापस;
	अगर (count == 0)
		वापस;

	क्रम (end = entry + count; entry != end; entry++) अणु
		चयन(le16_to_cpu(entry->e_tag)) अणु
		हाल ACL_USER:
			uid = make_kuid(from, le32_to_cpu(entry->e_id));
			अगर (from_user)
				uid = kuid_from_mnt(mnt_userns, uid);
			अन्यथा
				uid = kuid_पूर्णांकo_mnt(mnt_userns, uid);
			entry->e_id = cpu_to_le32(from_kuid(to, uid));
			अवरोध;
		हाल ACL_GROUP:
			gid = make_kgid(from, le32_to_cpu(entry->e_id));
			अगर (from_user)
				gid = kgid_from_mnt(mnt_userns, gid);
			अन्यथा
				gid = kgid_पूर्णांकo_mnt(mnt_userns, gid);
			entry->e_id = cpu_to_le32(from_kgid(to, gid));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम posix_acl_fix_xattr_from_user(काष्ठा user_namespace *mnt_userns,
				   व्योम *value, माप_प्रकार size)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	अगर ((user_ns == &init_user_ns) && (mnt_userns == &init_user_ns))
		वापस;
	posix_acl_fix_xattr_userns(&init_user_ns, user_ns, mnt_userns, value,
				   size, true);
पूर्ण

व्योम posix_acl_fix_xattr_to_user(काष्ठा user_namespace *mnt_userns,
				 व्योम *value, माप_प्रकार size)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	अगर ((user_ns == &init_user_ns) && (mnt_userns == &init_user_ns))
		वापस;
	posix_acl_fix_xattr_userns(user_ns, &init_user_ns, mnt_userns, value,
				   size, false);
पूर्ण

/*
 * Convert from extended attribute to in-memory representation.
 */
काष्ठा posix_acl *
posix_acl_from_xattr(काष्ठा user_namespace *user_ns,
		     स्थिर व्योम *value, माप_प्रकार size)
अणु
	स्थिर काष्ठा posix_acl_xattr_header *header = value;
	स्थिर काष्ठा posix_acl_xattr_entry *entry = (स्थिर व्योम *)(header + 1), *end;
	पूर्णांक count;
	काष्ठा posix_acl *acl;
	काष्ठा posix_acl_entry *acl_e;

	अगर (!value)
		वापस शून्य;
	अगर (size < माप(काष्ठा posix_acl_xattr_header))
		 वापस ERR_PTR(-EINVAL);
	अगर (header->a_version != cpu_to_le32(POSIX_ACL_XATTR_VERSION))
		वापस ERR_PTR(-EOPNOTSUPP);

	count = posix_acl_xattr_count(size);
	अगर (count < 0)
		वापस ERR_PTR(-EINVAL);
	अगर (count == 0)
		वापस शून्य;
	
	acl = posix_acl_alloc(count, GFP_NOFS);
	अगर (!acl)
		वापस ERR_PTR(-ENOMEM);
	acl_e = acl->a_entries;
	
	क्रम (end = entry + count; entry != end; acl_e++, entry++) अणु
		acl_e->e_tag  = le16_to_cpu(entry->e_tag);
		acl_e->e_perm = le16_to_cpu(entry->e_perm);

		चयन(acl_e->e_tag) अणु
			हाल ACL_USER_OBJ:
			हाल ACL_GROUP_OBJ:
			हाल ACL_MASK:
			हाल ACL_OTHER:
				अवरोध;

			हाल ACL_USER:
				acl_e->e_uid =
					make_kuid(user_ns,
						  le32_to_cpu(entry->e_id));
				अगर (!uid_valid(acl_e->e_uid))
					जाओ fail;
				अवरोध;
			हाल ACL_GROUP:
				acl_e->e_gid =
					make_kgid(user_ns,
						  le32_to_cpu(entry->e_id));
				अगर (!gid_valid(acl_e->e_gid))
					जाओ fail;
				अवरोध;

			शेष:
				जाओ fail;
		पूर्ण
	पूर्ण
	वापस acl;

fail:
	posix_acl_release(acl);
	वापस ERR_PTR(-EINVAL);
पूर्ण
EXPORT_SYMBOL (posix_acl_from_xattr);

/*
 * Convert from in-memory to extended attribute representation.
 */
पूर्णांक
posix_acl_to_xattr(काष्ठा user_namespace *user_ns, स्थिर काष्ठा posix_acl *acl,
		   व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा posix_acl_xattr_header *ext_acl = buffer;
	काष्ठा posix_acl_xattr_entry *ext_entry;
	पूर्णांक real_size, n;

	real_size = posix_acl_xattr_size(acl->a_count);
	अगर (!buffer)
		वापस real_size;
	अगर (real_size > size)
		वापस -दुस्फल;

	ext_entry = (व्योम *)(ext_acl + 1);
	ext_acl->a_version = cpu_to_le32(POSIX_ACL_XATTR_VERSION);

	क्रम (n=0; n < acl->a_count; n++, ext_entry++) अणु
		स्थिर काष्ठा posix_acl_entry *acl_e = &acl->a_entries[n];
		ext_entry->e_tag  = cpu_to_le16(acl_e->e_tag);
		ext_entry->e_perm = cpu_to_le16(acl_e->e_perm);
		चयन(acl_e->e_tag) अणु
		हाल ACL_USER:
			ext_entry->e_id =
				cpu_to_le32(from_kuid(user_ns, acl_e->e_uid));
			अवरोध;
		हाल ACL_GROUP:
			ext_entry->e_id =
				cpu_to_le32(from_kgid(user_ns, acl_e->e_gid));
			अवरोध;
		शेष:
			ext_entry->e_id = cpu_to_le32(ACL_UNDEFINED_ID);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस real_size;
पूर्ण
EXPORT_SYMBOL (posix_acl_to_xattr);

अटल पूर्णांक
posix_acl_xattr_get(स्थिर काष्ठा xattr_handler *handler,
		    काष्ठा dentry *unused, काष्ठा inode *inode,
		    स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	काष्ठा posix_acl *acl;
	पूर्णांक error;

	अगर (!IS_POSIXACL(inode))
		वापस -EOPNOTSUPP;
	अगर (S_ISLNK(inode->i_mode))
		वापस -EOPNOTSUPP;

	acl = get_acl(inode, handler->flags);
	अगर (IS_ERR(acl))
		वापस PTR_ERR(acl);
	अगर (acl == शून्य)
		वापस -ENODATA;

	error = posix_acl_to_xattr(&init_user_ns, acl, value, size);
	posix_acl_release(acl);

	वापस error;
पूर्ण

पूर्णांक
set_posix_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
	      पूर्णांक type, काष्ठा posix_acl *acl)
अणु
	अगर (!IS_POSIXACL(inode))
		वापस -EOPNOTSUPP;
	अगर (!inode->i_op->set_acl)
		वापस -EOPNOTSUPP;

	अगर (type == ACL_TYPE_DEFAULT && !S_ISसूची(inode->i_mode))
		वापस acl ? -EACCES : 0;
	अगर (!inode_owner_or_capable(mnt_userns, inode))
		वापस -EPERM;

	अगर (acl) अणु
		पूर्णांक ret = posix_acl_valid(inode->i_sb->s_user_ns, acl);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस inode->i_op->set_acl(mnt_userns, inode, acl, type);
पूर्ण
EXPORT_SYMBOL(set_posix_acl);

अटल पूर्णांक
posix_acl_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			   काष्ठा user_namespace *mnt_userns,
			   काष्ठा dentry *unused, काष्ठा inode *inode,
			   स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size,
			   पूर्णांक flags)
अणु
	काष्ठा posix_acl *acl = शून्य;
	पूर्णांक ret;

	अगर (value) अणु
		acl = posix_acl_from_xattr(&init_user_ns, value, size);
		अगर (IS_ERR(acl))
			वापस PTR_ERR(acl);
	पूर्ण
	ret = set_posix_acl(mnt_userns, inode, handler->flags, acl);
	posix_acl_release(acl);
	वापस ret;
पूर्ण

अटल bool
posix_acl_xattr_list(काष्ठा dentry *dentry)
अणु
	वापस IS_POSIXACL(d_backing_inode(dentry));
पूर्ण

स्थिर काष्ठा xattr_handler posix_acl_access_xattr_handler = अणु
	.name = XATTR_NAME_POSIX_ACL_ACCESS,
	.flags = ACL_TYPE_ACCESS,
	.list = posix_acl_xattr_list,
	.get = posix_acl_xattr_get,
	.set = posix_acl_xattr_set,
पूर्ण;
EXPORT_SYMBOL_GPL(posix_acl_access_xattr_handler);

स्थिर काष्ठा xattr_handler posix_acl_शेष_xattr_handler = अणु
	.name = XATTR_NAME_POSIX_ACL_DEFAULT,
	.flags = ACL_TYPE_DEFAULT,
	.list = posix_acl_xattr_list,
	.get = posix_acl_xattr_get,
	.set = posix_acl_xattr_set,
पूर्ण;
EXPORT_SYMBOL_GPL(posix_acl_शेष_xattr_handler);

पूर्णांक simple_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		   काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक error;

	अगर (type == ACL_TYPE_ACCESS) अणु
		error = posix_acl_update_mode(mnt_userns, inode,
				&inode->i_mode, &acl);
		अगर (error)
			वापस error;
	पूर्ण

	inode->i_स_समय = current_समय(inode);
	set_cached_acl(inode, type, acl);
	वापस 0;
पूर्ण

पूर्णांक simple_acl_create(काष्ठा inode *dir, काष्ठा inode *inode)
अणु
	काष्ठा posix_acl *शेष_acl, *acl;
	पूर्णांक error;

	error = posix_acl_create(dir, &inode->i_mode, &शेष_acl, &acl);
	अगर (error)
		वापस error;

	set_cached_acl(inode, ACL_TYPE_DEFAULT, शेष_acl);
	set_cached_acl(inode, ACL_TYPE_ACCESS, acl);

	अगर (शेष_acl)
		posix_acl_release(शेष_acl);
	अगर (acl)
		posix_acl_release(acl);
	वापस 0;
पूर्ण
