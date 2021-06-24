<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/namei.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/*
 * Some corrections by tytso.
 */

/* [Feb 1997 T. Schoebel-Theuer] Complete reग_लिखो of the pathname
 * lookup logic.
 */
/* [Feb-Apr 2000, AV] Reग_लिखो to the new namespace architecture.
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/personality.h>
#समावेश <linux/security.h>
#समावेश <linux/ima.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mount.h>
#समावेश <linux/audit.h>
#समावेश <linux/capability.h>
#समावेश <linux/file.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/device_cgroup.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/hash.h>
#समावेश <linux/bitops.h>
#समावेश <linux/init_task.h>
#समावेश <linux/uaccess.h>

#समावेश "internal.h"
#समावेश "mount.h"

/* [Feb-1997 T. Schoebel-Theuer]
 * Fundamental changes in the pathname lookup mechanisms (namei)
 * were necessary because of omirr.  The reason is that omirr needs
 * to know the _real_ pathname, not the user-supplied one, in हाल
 * of symlinks (and also when transname replacements occur).
 *
 * The new code replaces the old recursive symlink resolution with
 * an iterative one (in हाल of non-nested symlink chains).  It करोes
 * this with calls to <fs>_follow_link().
 * As a side effect, dir_namei(), _namei() and follow_link() are now 
 * replaced with a single function lookup_dentry() that can handle all 
 * the special हालs of the क्रमmer code.
 *
 * With the new dcache, the pathname is stored at each inode, at least as
 * दीर्घ as the refcount of the inode is positive.  As a side effect, the
 * size of the dcache depends on the inode cache and thus is dynamic.
 *
 * [29-Apr-1998 C. Scott Ananian] Updated above description of symlink
 * resolution to correspond with current state of the code.
 *
 * Note that the symlink resolution is not *completely* iterative.
 * There is still a signअगरicant amount of tail- and mid- recursion in
 * the algorithm.  Also, note that <fs>_पढ़ोlink() is not used in
 * lookup_dentry(): lookup_dentry() on the result of <fs>_पढ़ोlink()
 * may वापस dअगरferent results than <fs>_follow_link().  Many भव
 * fileप्रणालीs (including /proc) exhibit this behavior.
 */

/* [24-Feb-97 T. Schoebel-Theuer] Side effects caused by new implementation:
 * New symlink semantics: when खोलो() is called with flags O_CREAT | O_EXCL
 * and the name alपढ़ोy exists in क्रमm of a symlink, try to create the new
 * name indicated by the symlink. The old code always complained that the
 * name alपढ़ोy exists, due to not following the symlink even अगर its target
 * is nonexistent.  The new semantics affects also mknod() and link() when
 * the name is a symlink poपूर्णांकing to a non-existent name.
 *
 * I करोn't know which semantics is the right one, since I have no access
 * to standards. But I found by trial that HP-UX 9.0 has the full "new"
 * semantics implemented, जबतक SunOS 4.1.1 and Solaris (SunOS 5.4) have the
 * "old" one. Personally, I think the new semantics is much more logical.
 * Note that "ln old new" where "new" is a symlink poपूर्णांकing to a non-existing
 * file करोes succeed in both HP-UX and SunOs, but not in Solaris
 * and in the old Linux semantics.
 */

/* [16-Dec-97 Kevin Buhr] For security reasons, we change some symlink
 * semantics.  See the comments in "open_namei" and "do_link" below.
 *
 * [10-Sep-98 Alan Modra] Another symlink change.
 */

/* [Feb-Apr 2000 AV] Complete reग_लिखो. Rules क्रम symlinks:
 *	inside the path - always follow.
 *	in the last component in creation/removal/renaming - never follow.
 *	अगर LOOKUP_FOLLOW passed - follow.
 *	अगर the pathname has trailing slashes - follow.
 *	otherwise - करोn't follow.
 * (applied in that order).
 *
 * [Jun 2000 AV] Inconsistent behaviour of खोलो() in हाल अगर flags==O_CREAT
 * restored क्रम 2.4. This is the last surviving part of old 4.2BSD bug.
 * During the 2.4 we need to fix the userland stuff depending on it -
 * hopefully we will be able to get rid of that wart in 2.5. So far only
 * XEmacs seems to be relying on it...
 */
/*
 * [Sep 2001 AV] Single-semaphore locking scheme (kuकरोs to David Holland)
 * implemented.  Let's see अगर उठाओd priority of ->s_vfs_नाम_mutex gives
 * any extra contention...
 */

/* In order to reduce some races, जबतक at the same समय करोing additional
 * checking and hopefully speeding things up, we copy filenames to the
 * kernel data space beक्रमe using them..
 *
 * POSIX.1 2.4: an empty pathname is invalid (ENOENT).
 * PATH_MAX includes the nul terminator --RR.
 */

#घोषणा EMBEDDED_NAME_MAX	(PATH_MAX - दुरत्व(काष्ठा filename, iname))

काष्ठा filename *
getname_flags(स्थिर अक्षर __user *filename, पूर्णांक flags, पूर्णांक *empty)
अणु
	काष्ठा filename *result;
	अक्षर *kname;
	पूर्णांक len;

	result = audit_reusename(filename);
	अगर (result)
		वापस result;

	result = __getname();
	अगर (unlikely(!result))
		वापस ERR_PTR(-ENOMEM);

	/*
	 * First, try to embed the काष्ठा filename inside the names_cache
	 * allocation
	 */
	kname = (अक्षर *)result->iname;
	result->name = kname;

	len = म_नकलन_from_user(kname, filename, EMBEDDED_NAME_MAX);
	अगर (unlikely(len < 0)) अणु
		__putname(result);
		वापस ERR_PTR(len);
	पूर्ण

	/*
	 * Uh-oh. We have a name that's approaching PATH_MAX. Allocate a
	 * separate काष्ठा filename so we can dedicate the entire
	 * names_cache allocation क्रम the pathname, and re-करो the copy from
	 * userland.
	 */
	अगर (unlikely(len == EMBEDDED_NAME_MAX)) अणु
		स्थिर माप_प्रकार size = दुरत्व(काष्ठा filename, iname[1]);
		kname = (अक्षर *)result;

		/*
		 * size is chosen that way we to guarantee that
		 * result->iname[0] is within the same object and that
		 * kname can't be equal to result->iname, no matter what.
		 */
		result = kzalloc(size, GFP_KERNEL);
		अगर (unlikely(!result)) अणु
			__putname(kname);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		result->name = kname;
		len = म_नकलन_from_user(kname, filename, PATH_MAX);
		अगर (unlikely(len < 0)) अणु
			__putname(kname);
			kमुक्त(result);
			वापस ERR_PTR(len);
		पूर्ण
		अगर (unlikely(len == PATH_MAX)) अणु
			__putname(kname);
			kमुक्त(result);
			वापस ERR_PTR(-ENAMETOOLONG);
		पूर्ण
	पूर्ण

	result->refcnt = 1;
	/* The empty path is special. */
	अगर (unlikely(!len)) अणु
		अगर (empty)
			*empty = 1;
		अगर (!(flags & LOOKUP_EMPTY)) अणु
			putname(result);
			वापस ERR_PTR(-ENOENT);
		पूर्ण
	पूर्ण

	result->uptr = filename;
	result->aname = शून्य;
	audit_getname(result);
	वापस result;
पूर्ण

काष्ठा filename *
getname(स्थिर अक्षर __user * filename)
अणु
	वापस getname_flags(filename, 0, शून्य);
पूर्ण

काष्ठा filename *
getname_kernel(स्थिर अक्षर * filename)
अणु
	काष्ठा filename *result;
	पूर्णांक len = म_माप(filename) + 1;

	result = __getname();
	अगर (unlikely(!result))
		वापस ERR_PTR(-ENOMEM);

	अगर (len <= EMBEDDED_NAME_MAX) अणु
		result->name = (अक्षर *)result->iname;
	पूर्ण अन्यथा अगर (len <= PATH_MAX) अणु
		स्थिर माप_प्रकार size = दुरत्व(काष्ठा filename, iname[1]);
		काष्ठा filename *पंचांगp;

		पंचांगp = kदो_स्मृति(size, GFP_KERNEL);
		अगर (unlikely(!पंचांगp)) अणु
			__putname(result);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		पंचांगp->name = (अक्षर *)result;
		result = पंचांगp;
	पूर्ण अन्यथा अणु
		__putname(result);
		वापस ERR_PTR(-ENAMETOOLONG);
	पूर्ण
	स_नकल((अक्षर *)result->name, filename, len);
	result->uptr = शून्य;
	result->aname = शून्य;
	result->refcnt = 1;
	audit_getname(result);

	वापस result;
पूर्ण

व्योम putname(काष्ठा filename *name)
अणु
	BUG_ON(name->refcnt <= 0);

	अगर (--name->refcnt > 0)
		वापस;

	अगर (name->name != name->iname) अणु
		__putname(name->name);
		kमुक्त(name);
	पूर्ण अन्यथा
		__putname(name);
पूर्ण

/**
 * check_acl - perक्रमm ACL permission checking
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode:	inode to check permissions on
 * @mask:	right to check क्रम (%MAY_READ, %MAY_WRITE, %MAY_EXEC ...)
 *
 * This function perक्रमms the ACL permission checking. Since this function
 * retrieve POSIX acls it needs to know whether it is called from a blocking or
 * non-blocking context and thus cares about the MAY_NOT_BLOCK bit.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
अटल पूर्णांक check_acl(काष्ठा user_namespace *mnt_userns,
		     काष्ठा inode *inode, पूर्णांक mask)
अणु
#अगर_घोषित CONFIG_FS_POSIX_ACL
	काष्ठा posix_acl *acl;

	अगर (mask & MAY_NOT_BLOCK) अणु
		acl = get_cached_acl_rcu(inode, ACL_TYPE_ACCESS);
	        अगर (!acl)
	                वापस -EAGAIN;
		/* no ->get_acl() calls in RCU mode... */
		अगर (is_uncached_acl(acl))
			वापस -ECHILD;
	        वापस posix_acl_permission(mnt_userns, inode, acl, mask);
	पूर्ण

	acl = get_acl(inode, ACL_TYPE_ACCESS);
	अगर (IS_ERR(acl))
		वापस PTR_ERR(acl);
	अगर (acl) अणु
	        पूर्णांक error = posix_acl_permission(mnt_userns, inode, acl, mask);
	        posix_acl_release(acl);
	        वापस error;
	पूर्ण
#पूर्ण_अगर

	वापस -EAGAIN;
पूर्ण

/**
 * acl_permission_check - perक्रमm basic UNIX permission checking
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode:	inode to check permissions on
 * @mask:	right to check क्रम (%MAY_READ, %MAY_WRITE, %MAY_EXEC ...)
 *
 * This function perक्रमms the basic UNIX permission checking. Since this
 * function may retrieve POSIX acls it needs to know whether it is called from a
 * blocking or non-blocking context and thus cares about the MAY_NOT_BLOCK bit.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
अटल पूर्णांक acl_permission_check(काष्ठा user_namespace *mnt_userns,
				काष्ठा inode *inode, पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक mode = inode->i_mode;
	kuid_t i_uid;

	/* Are we the owner? If so, ACL's don't matter */
	i_uid = i_uid_पूर्णांकo_mnt(mnt_userns, inode);
	अगर (likely(uid_eq(current_fsuid(), i_uid))) अणु
		mask &= 7;
		mode >>= 6;
		वापस (mask & ~mode) ? -EACCES : 0;
	पूर्ण

	/* Do we have ACL's? */
	अगर (IS_POSIXACL(inode) && (mode & S_IRWXG)) अणु
		पूर्णांक error = check_acl(mnt_userns, inode, mask);
		अगर (error != -EAGAIN)
			वापस error;
	पूर्ण

	/* Only RWX matters क्रम group/other mode bits */
	mask &= 7;

	/*
	 * Are the group permissions dअगरferent from
	 * the other permissions in the bits we care
	 * about? Need to check group ownership अगर so.
	 */
	अगर (mask & (mode ^ (mode >> 3))) अणु
		kgid_t kgid = i_gid_पूर्णांकo_mnt(mnt_userns, inode);
		अगर (in_group_p(kgid))
			mode >>= 3;
	पूर्ण

	/* Bits in 'mode' clear that we require? */
	वापस (mask & ~mode) ? -EACCES : 0;
पूर्ण

/**
 * generic_permission -  check क्रम access rights on a Posix-like fileप्रणाली
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode:	inode to check access rights क्रम
 * @mask:	right to check क्रम (%MAY_READ, %MAY_WRITE, %MAY_EXEC,
 *		%MAY_NOT_BLOCK ...)
 *
 * Used to check क्रम पढ़ो/ग_लिखो/execute permissions on a file.
 * We use "fsuid" क्रम this, letting us set arbitrary permissions
 * क्रम fileप्रणाली access without changing the "normal" uids which
 * are used क्रम other things.
 *
 * generic_permission is rcu-walk aware. It वापसs -ECHILD in हाल an rcu-walk
 * request cannot be satisfied (eg. requires blocking or too much complनिकासy).
 * It would then be called again in ref-walk mode.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
पूर्णांक generic_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		       पूर्णांक mask)
अणु
	पूर्णांक ret;

	/*
	 * Do the basic permission checks.
	 */
	ret = acl_permission_check(mnt_userns, inode, mask);
	अगर (ret != -EACCES)
		वापस ret;

	अगर (S_ISसूची(inode->i_mode)) अणु
		/* DACs are overridable क्रम directories */
		अगर (!(mask & MAY_WRITE))
			अगर (capable_wrt_inode_uidgid(mnt_userns, inode,
						     CAP_DAC_READ_SEARCH))
				वापस 0;
		अगर (capable_wrt_inode_uidgid(mnt_userns, inode,
					     CAP_DAC_OVERRIDE))
			वापस 0;
		वापस -EACCES;
	पूर्ण

	/*
	 * Searching includes executable on directories, अन्यथा just पढ़ो.
	 */
	mask &= MAY_READ | MAY_WRITE | MAY_EXEC;
	अगर (mask == MAY_READ)
		अगर (capable_wrt_inode_uidgid(mnt_userns, inode,
					     CAP_DAC_READ_SEARCH))
			वापस 0;
	/*
	 * Read/ग_लिखो DACs are always overridable.
	 * Executable DACs are overridable when there is
	 * at least one exec bit set.
	 */
	अगर (!(mask & MAY_EXEC) || (inode->i_mode & S_IXUGO))
		अगर (capable_wrt_inode_uidgid(mnt_userns, inode,
					     CAP_DAC_OVERRIDE))
			वापस 0;

	वापस -EACCES;
पूर्ण
EXPORT_SYMBOL(generic_permission);

/**
 * करो_inode_permission - UNIX permission checking
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode:	inode to check permissions on
 * @mask:	right to check क्रम (%MAY_READ, %MAY_WRITE, %MAY_EXEC ...)
 *
 * We _really_ want to just करो "generic_permission()" without
 * even looking at the inode->i_op values. So we keep a cache
 * flag in inode->i_opflags, that says "this has not special
 * permission function, use the fast हाल".
 */
अटल अंतरभूत पूर्णांक करो_inode_permission(काष्ठा user_namespace *mnt_userns,
				      काष्ठा inode *inode, पूर्णांक mask)
अणु
	अगर (unlikely(!(inode->i_opflags & IOP_FASTPERM))) अणु
		अगर (likely(inode->i_op->permission))
			वापस inode->i_op->permission(mnt_userns, inode, mask);

		/* This माला_लो set once क्रम the inode lअगरeसमय */
		spin_lock(&inode->i_lock);
		inode->i_opflags |= IOP_FASTPERM;
		spin_unlock(&inode->i_lock);
	पूर्ण
	वापस generic_permission(mnt_userns, inode, mask);
पूर्ण

/**
 * sb_permission - Check superblock-level permissions
 * @sb: Superblock of inode to check permission on
 * @inode: Inode to check permission on
 * @mask: Right to check क्रम (%MAY_READ, %MAY_WRITE, %MAY_EXEC)
 *
 * Separate out file-प्रणाली wide checks from inode-specअगरic permission checks.
 */
अटल पूर्णांक sb_permission(काष्ठा super_block *sb, काष्ठा inode *inode, पूर्णांक mask)
अणु
	अगर (unlikely(mask & MAY_WRITE)) अणु
		umode_t mode = inode->i_mode;

		/* Nobody माला_लो ग_लिखो access to a पढ़ो-only fs. */
		अगर (sb_rकरोnly(sb) && (S_ISREG(mode) || S_ISसूची(mode) || S_ISLNK(mode)))
			वापस -EROFS;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * inode_permission - Check क्रम access rights to a given inode
 * @mnt_userns:	User namespace of the mount the inode was found from
 * @inode:	Inode to check permission on
 * @mask:	Right to check क्रम (%MAY_READ, %MAY_WRITE, %MAY_EXEC)
 *
 * Check क्रम पढ़ो/ग_लिखो/execute permissions on an inode.  We use fs[ug]id क्रम
 * this, letting us set arbitrary permissions क्रम fileप्रणाली access without
 * changing the "normal" UIDs which are used क्रम other things.
 *
 * When checking क्रम MAY_APPEND, MAY_WRITE must also be set in @mask.
 */
पूर्णांक inode_permission(काष्ठा user_namespace *mnt_userns,
		     काष्ठा inode *inode, पूर्णांक mask)
अणु
	पूर्णांक retval;

	retval = sb_permission(inode->i_sb, inode, mask);
	अगर (retval)
		वापस retval;

	अगर (unlikely(mask & MAY_WRITE)) अणु
		/*
		 * Nobody माला_लो ग_लिखो access to an immutable file.
		 */
		अगर (IS_IMMUTABLE(inode))
			वापस -EPERM;

		/*
		 * Updating mसमय will likely cause i_uid and i_gid to be
		 * written back improperly अगर their true value is unknown
		 * to the vfs.
		 */
		अगर (HAS_UNMAPPED_ID(mnt_userns, inode))
			वापस -EACCES;
	पूर्ण

	retval = करो_inode_permission(mnt_userns, inode, mask);
	अगर (retval)
		वापस retval;

	retval = devcgroup_inode_permission(inode, mask);
	अगर (retval)
		वापस retval;

	वापस security_inode_permission(inode, mask);
पूर्ण
EXPORT_SYMBOL(inode_permission);

/**
 * path_get - get a reference to a path
 * @path: path to get the reference to
 *
 * Given a path increment the reference count to the dentry and the vfsmount.
 */
व्योम path_get(स्थिर काष्ठा path *path)
अणु
	mntget(path->mnt);
	dget(path->dentry);
पूर्ण
EXPORT_SYMBOL(path_get);

/**
 * path_put - put a reference to a path
 * @path: path to put the reference to
 *
 * Given a path decrement the reference count to the dentry and the vfsmount.
 */
व्योम path_put(स्थिर काष्ठा path *path)
अणु
	dput(path->dentry);
	mntput(path->mnt);
पूर्ण
EXPORT_SYMBOL(path_put);

#घोषणा EMBEDDED_LEVELS 2
काष्ठा nameidata अणु
	काष्ठा path	path;
	काष्ठा qstr	last;
	काष्ठा path	root;
	काष्ठा inode	*inode; /* path.dentry.d_inode */
	अचिन्हित पूर्णांक	flags;
	अचिन्हित	seq, m_seq, r_seq;
	पूर्णांक		last_type;
	अचिन्हित	depth;
	पूर्णांक		total_link_count;
	काष्ठा saved अणु
		काष्ठा path link;
		काष्ठा delayed_call करोne;
		स्थिर अक्षर *name;
		अचिन्हित seq;
	पूर्ण *stack, पूर्णांकernal[EMBEDDED_LEVELS];
	काष्ठा filename	*name;
	काष्ठा nameidata *saved;
	अचिन्हित	root_seq;
	पूर्णांक		dfd;
	kuid_t		dir_uid;
	umode_t		dir_mode;
पूर्ण __अक्रमomize_layout;

अटल व्योम set_nameidata(काष्ठा nameidata *p, पूर्णांक dfd, काष्ठा filename *name)
अणु
	काष्ठा nameidata *old = current->nameidata;
	p->stack = p->पूर्णांकernal;
	p->dfd = dfd;
	p->name = name;
	p->path.mnt = शून्य;
	p->path.dentry = शून्य;
	p->total_link_count = old ? old->total_link_count : 0;
	p->saved = old;
	current->nameidata = p;
पूर्ण

अटल व्योम restore_nameidata(व्योम)
अणु
	काष्ठा nameidata *now = current->nameidata, *old = now->saved;

	current->nameidata = old;
	अगर (old)
		old->total_link_count = now->total_link_count;
	अगर (now->stack != now->पूर्णांकernal)
		kमुक्त(now->stack);
पूर्ण

अटल bool nd_alloc_stack(काष्ठा nameidata *nd)
अणु
	काष्ठा saved *p;

	p= kदो_स्मृति_array(MAXSYMLINKS, माप(काष्ठा saved),
			 nd->flags & LOOKUP_RCU ? GFP_ATOMIC : GFP_KERNEL);
	अगर (unlikely(!p))
		वापस false;
	स_नकल(p, nd->पूर्णांकernal, माप(nd->पूर्णांकernal));
	nd->stack = p;
	वापस true;
पूर्ण

/**
 * path_connected - Verअगरy that a dentry is below mnt.mnt_root
 *
 * Rename can someबार move a file or directory outside of a bind
 * mount, path_connected allows those हालs to be detected.
 */
अटल bool path_connected(काष्ठा vfsmount *mnt, काष्ठा dentry *dentry)
अणु
	काष्ठा super_block *sb = mnt->mnt_sb;

	/* Bind mounts can have disconnected paths */
	अगर (mnt->mnt_root == sb->s_root)
		वापस true;

	वापस is_subdir(dentry, mnt->mnt_root);
पूर्ण

अटल व्योम drop_links(काष्ठा nameidata *nd)
अणु
	पूर्णांक i = nd->depth;
	जबतक (i--) अणु
		काष्ठा saved *last = nd->stack + i;
		करो_delayed_call(&last->करोne);
		clear_delayed_call(&last->करोne);
	पूर्ण
पूर्ण

अटल व्योम terminate_walk(काष्ठा nameidata *nd)
अणु
	drop_links(nd);
	अगर (!(nd->flags & LOOKUP_RCU)) अणु
		पूर्णांक i;
		path_put(&nd->path);
		क्रम (i = 0; i < nd->depth; i++)
			path_put(&nd->stack[i].link);
		अगर (nd->flags & LOOKUP_ROOT_GRABBED) अणु
			path_put(&nd->root);
			nd->flags &= ~LOOKUP_ROOT_GRABBED;
		पूर्ण
	पूर्ण अन्यथा अणु
		nd->flags &= ~LOOKUP_RCU;
		rcu_पढ़ो_unlock();
	पूर्ण
	nd->depth = 0;
	nd->path.mnt = शून्य;
	nd->path.dentry = शून्य;
पूर्ण

/* path_put is needed afterwards regardless of success or failure */
अटल bool __legitimize_path(काष्ठा path *path, अचिन्हित seq, अचिन्हित mseq)
अणु
	पूर्णांक res = __legitimize_mnt(path->mnt, mseq);
	अगर (unlikely(res)) अणु
		अगर (res > 0)
			path->mnt = शून्य;
		path->dentry = शून्य;
		वापस false;
	पूर्ण
	अगर (unlikely(!lockref_get_not_dead(&path->dentry->d_lockref))) अणु
		path->dentry = शून्य;
		वापस false;
	पूर्ण
	वापस !पढ़ो_seqcount_retry(&path->dentry->d_seq, seq);
पूर्ण

अटल अंतरभूत bool legitimize_path(काष्ठा nameidata *nd,
			    काष्ठा path *path, अचिन्हित seq)
अणु
	वापस __legitimize_path(path, seq, nd->m_seq);
पूर्ण

अटल bool legitimize_links(काष्ठा nameidata *nd)
अणु
	पूर्णांक i;
	अगर (unlikely(nd->flags & LOOKUP_CACHED)) अणु
		drop_links(nd);
		nd->depth = 0;
		वापस false;
	पूर्ण
	क्रम (i = 0; i < nd->depth; i++) अणु
		काष्ठा saved *last = nd->stack + i;
		अगर (unlikely(!legitimize_path(nd, &last->link, last->seq))) अणु
			drop_links(nd);
			nd->depth = i + 1;
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल bool legitimize_root(काष्ठा nameidata *nd)
अणु
	/*
	 * For scoped-lookups (where nd->root has been zeroed), we need to
	 * restart the whole lookup from scratch -- because set_root() is wrong
	 * क्रम these lookups (nd->dfd is the root, not the fileप्रणाली root).
	 */
	अगर (!nd->root.mnt && (nd->flags & LOOKUP_IS_SCOPED))
		वापस false;
	/* Nothing to करो अगर nd->root is zero or is managed by the VFS user. */
	अगर (!nd->root.mnt || (nd->flags & LOOKUP_ROOT))
		वापस true;
	nd->flags |= LOOKUP_ROOT_GRABBED;
	वापस legitimize_path(nd, &nd->root, nd->root_seq);
पूर्ण

/*
 * Path walking has 2 modes, rcu-walk and ref-walk (see
 * Documentation/fileप्रणालीs/path-lookup.txt).  In situations when we can't
 * जारी in RCU mode, we attempt to drop out of rcu-walk mode and grab
 * normal reference counts on dentries and vfsmounts to transition to ref-walk
 * mode.  Refcounts are grabbed at the last known good poपूर्णांक beक्रमe rcu-walk
 * got stuck, so ref-walk may जारी from there. If this is not successful
 * (eg. a seqcount has changed), then failure is वापसed and it's up to caller
 * to restart the path walk from the beginning in ref-walk mode.
 */

/**
 * try_to_unlazy - try to चयन to ref-walk mode.
 * @nd: nameidata pathwalk data
 * Returns: true on success, false on failure
 *
 * try_to_unlazy attempts to legitimize the current nd->path and nd->root
 * क्रम ref-walk mode.
 * Must be called from rcu-walk context.
 * Nothing should touch nameidata between try_to_unlazy() failure and
 * terminate_walk().
 */
अटल bool try_to_unlazy(काष्ठा nameidata *nd)
अणु
	काष्ठा dentry *parent = nd->path.dentry;

	BUG_ON(!(nd->flags & LOOKUP_RCU));

	nd->flags &= ~LOOKUP_RCU;
	अगर (unlikely(!legitimize_links(nd)))
		जाओ out1;
	अगर (unlikely(!legitimize_path(nd, &nd->path, nd->seq)))
		जाओ out;
	अगर (unlikely(!legitimize_root(nd)))
		जाओ out;
	rcu_पढ़ो_unlock();
	BUG_ON(nd->inode != parent->d_inode);
	वापस true;

out1:
	nd->path.mnt = शून्य;
	nd->path.dentry = शून्य;
out:
	rcu_पढ़ो_unlock();
	वापस false;
पूर्ण

/**
 * try_to_unlazy_next - try to चयन to ref-walk mode.
 * @nd: nameidata pathwalk data
 * @dentry: next dentry to step पूर्णांकo
 * @seq: seq number to check @dentry against
 * Returns: true on success, false on failure
 *
 * Similar to to try_to_unlazy(), but here we have the next dentry alपढ़ोy
 * picked by rcu-walk and want to legitimize that in addition to the current
 * nd->path and nd->root क्रम ref-walk mode.  Must be called from rcu-walk context.
 * Nothing should touch nameidata between try_to_unlazy_next() failure and
 * terminate_walk().
 */
अटल bool try_to_unlazy_next(काष्ठा nameidata *nd, काष्ठा dentry *dentry, अचिन्हित seq)
अणु
	BUG_ON(!(nd->flags & LOOKUP_RCU));

	nd->flags &= ~LOOKUP_RCU;
	अगर (unlikely(!legitimize_links(nd)))
		जाओ out2;
	अगर (unlikely(!legitimize_mnt(nd->path.mnt, nd->m_seq)))
		जाओ out2;
	अगर (unlikely(!lockref_get_not_dead(&nd->path.dentry->d_lockref)))
		जाओ out1;

	/*
	 * We need to move both the parent and the dentry from the RCU करोमुख्य
	 * to be properly refcounted. And the sequence number in the dentry
	 * validates *both* dentry counters, since we checked the sequence
	 * number of the parent after we got the child sequence number. So we
	 * know the parent must still be valid अगर the child sequence number is
	 */
	अगर (unlikely(!lockref_get_not_dead(&dentry->d_lockref)))
		जाओ out;
	अगर (unlikely(पढ़ो_seqcount_retry(&dentry->d_seq, seq)))
		जाओ out_dput;
	/*
	 * Sequence counts matched. Now make sure that the root is
	 * still valid and get it अगर required.
	 */
	अगर (unlikely(!legitimize_root(nd)))
		जाओ out_dput;
	rcu_पढ़ो_unlock();
	वापस true;

out2:
	nd->path.mnt = शून्य;
out1:
	nd->path.dentry = शून्य;
out:
	rcu_पढ़ो_unlock();
	वापस false;
out_dput:
	rcu_पढ़ो_unlock();
	dput(dentry);
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	अगर (unlikely(dentry->d_flags & DCACHE_OP_REVALIDATE))
		वापस dentry->d_op->d_revalidate(dentry, flags);
	अन्यथा
		वापस 1;
पूर्ण

/**
 * complete_walk - successful completion of path walk
 * @nd:  poपूर्णांकer nameidata
 *
 * If we had been in RCU mode, drop out of it and legitimize nd->path.
 * Revalidate the final result, unless we'd alपढ़ोy करोne that during
 * the path walk or the fileप्रणाली करोesn't ask क्रम it.  Return 0 on
 * success, -error on failure.  In हाल of failure caller करोes not
 * need to drop nd->path.
 */
अटल पूर्णांक complete_walk(काष्ठा nameidata *nd)
अणु
	काष्ठा dentry *dentry = nd->path.dentry;
	पूर्णांक status;

	अगर (nd->flags & LOOKUP_RCU) अणु
		/*
		 * We करोn't want to zero nd->root क्रम scoped-lookups or
		 * बाह्यally-managed nd->root.
		 */
		अगर (!(nd->flags & (LOOKUP_ROOT | LOOKUP_IS_SCOPED)))
			nd->root.mnt = शून्य;
		nd->flags &= ~LOOKUP_CACHED;
		अगर (!try_to_unlazy(nd))
			वापस -ECHILD;
	पूर्ण

	अगर (unlikely(nd->flags & LOOKUP_IS_SCOPED)) अणु
		/*
		 * While the guarantee of LOOKUP_IS_SCOPED is (roughly) "करोn't
		 * ever step outside the root during lookup" and should alपढ़ोy
		 * be guaranteed by the rest of namei, we want to aव्योम a namei
		 * BUG resulting in userspace being given a path that was not
		 * scoped within the root at some poपूर्णांक during the lookup.
		 *
		 * So, करो a final sanity-check to make sure that in the
		 * worst-हाल scenario (a complete bypass of LOOKUP_IS_SCOPED)
		 * we won't silently वापस an fd completely outside of the
		 * requested root to userspace.
		 *
		 * Userspace could move the path outside the root after this
		 * check, but as discussed अन्यथाwhere this is not a concern (the
		 * resolved file was inside the root at some poपूर्णांक).
		 */
		अगर (!path_is_under(&nd->path, &nd->root))
			वापस -EXDEV;
	पूर्ण

	अगर (likely(!(nd->flags & LOOKUP_JUMPED)))
		वापस 0;

	अगर (likely(!(dentry->d_flags & DCACHE_OP_WEAK_REVALIDATE)))
		वापस 0;

	status = dentry->d_op->d_weak_revalidate(dentry, nd->flags);
	अगर (status > 0)
		वापस 0;

	अगर (!status)
		status = -ESTALE;

	वापस status;
पूर्ण

अटल पूर्णांक set_root(काष्ठा nameidata *nd)
अणु
	काष्ठा fs_काष्ठा *fs = current->fs;

	/*
	 * Jumping to the real root in a scoped-lookup is a BUG in namei, but we
	 * still have to ensure it करोesn't happen because it will cause a अवरोधout
	 * from the dirfd.
	 */
	अगर (WARN_ON(nd->flags & LOOKUP_IS_SCOPED))
		वापस -ENOTRECOVERABLE;

	अगर (nd->flags & LOOKUP_RCU) अणु
		अचिन्हित seq;

		करो अणु
			seq = पढ़ो_seqcount_begin(&fs->seq);
			nd->root = fs->root;
			nd->root_seq = __पढ़ो_seqcount_begin(&nd->root.dentry->d_seq);
		पूर्ण जबतक (पढ़ो_seqcount_retry(&fs->seq, seq));
	पूर्ण अन्यथा अणु
		get_fs_root(fs, &nd->root);
		nd->flags |= LOOKUP_ROOT_GRABBED;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nd_jump_root(काष्ठा nameidata *nd)
अणु
	अगर (unlikely(nd->flags & LOOKUP_BENEATH))
		वापस -EXDEV;
	अगर (unlikely(nd->flags & LOOKUP_NO_XDEV)) अणु
		/* Absolute path arguments to path_init() are allowed. */
		अगर (nd->path.mnt != शून्य && nd->path.mnt != nd->root.mnt)
			वापस -EXDEV;
	पूर्ण
	अगर (!nd->root.mnt) अणु
		पूर्णांक error = set_root(nd);
		अगर (error)
			वापस error;
	पूर्ण
	अगर (nd->flags & LOOKUP_RCU) अणु
		काष्ठा dentry *d;
		nd->path = nd->root;
		d = nd->path.dentry;
		nd->inode = d->d_inode;
		nd->seq = nd->root_seq;
		अगर (unlikely(पढ़ो_seqcount_retry(&d->d_seq, nd->seq)))
			वापस -ECHILD;
	पूर्ण अन्यथा अणु
		path_put(&nd->path);
		nd->path = nd->root;
		path_get(&nd->path);
		nd->inode = nd->path.dentry->d_inode;
	पूर्ण
	nd->flags |= LOOKUP_JUMPED;
	वापस 0;
पूर्ण

/*
 * Helper to directly jump to a known parsed path from ->get_link,
 * caller must have taken a reference to path beक्रमehand.
 */
पूर्णांक nd_jump_link(काष्ठा path *path)
अणु
	पूर्णांक error = -ELOOP;
	काष्ठा nameidata *nd = current->nameidata;

	अगर (unlikely(nd->flags & LOOKUP_NO_MAGICLINKS))
		जाओ err;

	error = -EXDEV;
	अगर (unlikely(nd->flags & LOOKUP_NO_XDEV)) अणु
		अगर (nd->path.mnt != path->mnt)
			जाओ err;
	पूर्ण
	/* Not currently safe क्रम scoped-lookups. */
	अगर (unlikely(nd->flags & LOOKUP_IS_SCOPED))
		जाओ err;

	path_put(&nd->path);
	nd->path = *path;
	nd->inode = nd->path.dentry->d_inode;
	nd->flags |= LOOKUP_JUMPED;
	वापस 0;

err:
	path_put(path);
	वापस error;
पूर्ण

अटल अंतरभूत व्योम put_link(काष्ठा nameidata *nd)
अणु
	काष्ठा saved *last = nd->stack + --nd->depth;
	करो_delayed_call(&last->करोne);
	अगर (!(nd->flags & LOOKUP_RCU))
		path_put(&last->link);
पूर्ण

पूर्णांक sysctl_रक्षित_symlinks __पढ़ो_mostly = 0;
पूर्णांक sysctl_रक्षित_hardlinks __पढ़ो_mostly = 0;
पूर्णांक sysctl_रक्षित_fअगरos __पढ़ो_mostly;
पूर्णांक sysctl_रक्षित_regular __पढ़ो_mostly;

/**
 * may_follow_link - Check symlink following क्रम unsafe situations
 * @nd: nameidata pathwalk data
 *
 * In the हाल of the sysctl_रक्षित_symlinks sysctl being enabled,
 * CAP_DAC_OVERRIDE needs to be specअगरically ignored अगर the symlink is
 * in a sticky world-writable directory. This is to protect privileged
 * processes from failing races against path names that may change out
 * from under them by way of other users creating malicious symlinks.
 * It will permit symlinks to be followed only when outside a sticky
 * world-writable directory, or when the uid of the symlink and follower
 * match, or when the directory owner matches the symlink's owner.
 *
 * Returns 0 अगर following the symlink is allowed, -ve on error.
 */
अटल अंतरभूत पूर्णांक may_follow_link(काष्ठा nameidata *nd, स्थिर काष्ठा inode *inode)
अणु
	काष्ठा user_namespace *mnt_userns;
	kuid_t i_uid;

	अगर (!sysctl_रक्षित_symlinks)
		वापस 0;

	mnt_userns = mnt_user_ns(nd->path.mnt);
	i_uid = i_uid_पूर्णांकo_mnt(mnt_userns, inode);
	/* Allowed अगर owner and follower match. */
	अगर (uid_eq(current_cred()->fsuid, i_uid))
		वापस 0;

	/* Allowed अगर parent directory not sticky and world-writable. */
	अगर ((nd->dir_mode & (S_ISVTX|S_IWOTH)) != (S_ISVTX|S_IWOTH))
		वापस 0;

	/* Allowed अगर parent directory and link owner match. */
	अगर (uid_valid(nd->dir_uid) && uid_eq(nd->dir_uid, i_uid))
		वापस 0;

	अगर (nd->flags & LOOKUP_RCU)
		वापस -ECHILD;

	audit_inode(nd->name, nd->stack[0].link.dentry, 0);
	audit_log_path_denied(AUDIT_ANOM_LINK, "follow_link");
	वापस -EACCES;
पूर्ण

/**
 * safe_hardlink_source - Check क्रम safe hardlink conditions
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode: the source inode to hardlink from
 *
 * Return false अगर at least one of the following conditions:
 *    - inode is not a regular file
 *    - inode is setuid
 *    - inode is setgid and group-exec
 *    - access failure क्रम पढ़ो and ग_लिखो
 *
 * Otherwise वापसs true.
 */
अटल bool safe_hardlink_source(काष्ठा user_namespace *mnt_userns,
				 काष्ठा inode *inode)
अणु
	umode_t mode = inode->i_mode;

	/* Special files should not get pinned to the fileप्रणाली. */
	अगर (!S_ISREG(mode))
		वापस false;

	/* Setuid files should not get pinned to the fileप्रणाली. */
	अगर (mode & S_ISUID)
		वापस false;

	/* Executable setgid files should not get pinned to the fileप्रणाली. */
	अगर ((mode & (S_ISGID | S_IXGRP)) == (S_ISGID | S_IXGRP))
		वापस false;

	/* Hardlinking to unपढ़ोable or unwritable sources is dangerous. */
	अगर (inode_permission(mnt_userns, inode, MAY_READ | MAY_WRITE))
		वापस false;

	वापस true;
पूर्ण

/**
 * may_linkat - Check permissions क्रम creating a hardlink
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @link: the source to hardlink from
 *
 * Block hardlink when all of:
 *  - sysctl_रक्षित_hardlinks enabled
 *  - fsuid करोes not match inode
 *  - hardlink source is unsafe (see safe_hardlink_source() above)
 *  - not CAP_FOWNER in a namespace with the inode owner uid mapped
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 *
 * Returns 0 अगर successful, -ve on error.
 */
पूर्णांक may_linkat(काष्ठा user_namespace *mnt_userns, काष्ठा path *link)
अणु
	काष्ठा inode *inode = link->dentry->d_inode;

	/* Inode ग_लिखोback is not safe when the uid or gid are invalid. */
	अगर (!uid_valid(i_uid_पूर्णांकo_mnt(mnt_userns, inode)) ||
	    !gid_valid(i_gid_पूर्णांकo_mnt(mnt_userns, inode)))
		वापस -EOVERFLOW;

	अगर (!sysctl_रक्षित_hardlinks)
		वापस 0;

	/* Source inode owner (or CAP_FOWNER) can hardlink all they like,
	 * otherwise, it must be a safe source.
	 */
	अगर (safe_hardlink_source(mnt_userns, inode) ||
	    inode_owner_or_capable(mnt_userns, inode))
		वापस 0;

	audit_log_path_denied(AUDIT_ANOM_LINK, "linkat");
	वापस -EPERM;
पूर्ण

/**
 * may_create_in_sticky - Check whether an O_CREAT खोलो in a sticky directory
 *			  should be allowed, or not, on files that alपढ़ोy
 *			  exist.
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @nd: nameidata pathwalk data
 * @inode: the inode of the file to खोलो
 *
 * Block an O_CREAT खोलो of a FIFO (or a regular file) when:
 *   - sysctl_रक्षित_fअगरos (or sysctl_रक्षित_regular) is enabled
 *   - the file alपढ़ोy exists
 *   - we are in a sticky directory
 *   - we करोn't own the file
 *   - the owner of the directory करोesn't own the file
 *   - the directory is world writable
 * If the sysctl_रक्षित_fअगरos (or sysctl_रक्षित_regular) is set to 2
 * the directory करोesn't have to be world writable: being group writable will
 * be enough.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 *
 * Returns 0 अगर the खोलो is allowed, -ve on error.
 */
अटल पूर्णांक may_create_in_sticky(काष्ठा user_namespace *mnt_userns,
				काष्ठा nameidata *nd, काष्ठा inode *स्थिर inode)
अणु
	umode_t dir_mode = nd->dir_mode;
	kuid_t dir_uid = nd->dir_uid;

	अगर ((!sysctl_रक्षित_fअगरos && S_ISFIFO(inode->i_mode)) ||
	    (!sysctl_रक्षित_regular && S_ISREG(inode->i_mode)) ||
	    likely(!(dir_mode & S_ISVTX)) ||
	    uid_eq(i_uid_पूर्णांकo_mnt(mnt_userns, inode), dir_uid) ||
	    uid_eq(current_fsuid(), i_uid_पूर्णांकo_mnt(mnt_userns, inode)))
		वापस 0;

	अगर (likely(dir_mode & 0002) ||
	    (dir_mode & 0020 &&
	     ((sysctl_रक्षित_fअगरos >= 2 && S_ISFIFO(inode->i_mode)) ||
	      (sysctl_रक्षित_regular >= 2 && S_ISREG(inode->i_mode))))) अणु
		स्थिर अक्षर *operation = S_ISFIFO(inode->i_mode) ?
					"sticky_create_fifo" :
					"sticky_create_regular";
		audit_log_path_denied(AUDIT_ANOM_CREAT, operation);
		वापस -EACCES;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * follow_up - Find the mountpoपूर्णांक of path's vfsmount
 *
 * Given a path, find the mountpoपूर्णांक of its source file प्रणाली.
 * Replace @path with the path of the mountpoपूर्णांक in the parent mount.
 * Up is towards /.
 *
 * Return 1 अगर we went up a level and 0 अगर we were alपढ़ोy at the
 * root.
 */
पूर्णांक follow_up(काष्ठा path *path)
अणु
	काष्ठा mount *mnt = real_mount(path->mnt);
	काष्ठा mount *parent;
	काष्ठा dentry *mountpoपूर्णांक;

	पढ़ो_seqlock_excl(&mount_lock);
	parent = mnt->mnt_parent;
	अगर (parent == mnt) अणु
		पढ़ो_sequnlock_excl(&mount_lock);
		वापस 0;
	पूर्ण
	mntget(&parent->mnt);
	mountpoपूर्णांक = dget(mnt->mnt_mountpoपूर्णांक);
	पढ़ो_sequnlock_excl(&mount_lock);
	dput(path->dentry);
	path->dentry = mountpoपूर्णांक;
	mntput(path->mnt);
	path->mnt = &parent->mnt;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(follow_up);

अटल bool choose_mountpoपूर्णांक_rcu(काष्ठा mount *m, स्थिर काष्ठा path *root,
				  काष्ठा path *path, अचिन्हित *seqp)
अणु
	जबतक (mnt_has_parent(m)) अणु
		काष्ठा dentry *mountpoपूर्णांक = m->mnt_mountpoपूर्णांक;

		m = m->mnt_parent;
		अगर (unlikely(root->dentry == mountpoपूर्णांक &&
			     root->mnt == &m->mnt))
			अवरोध;
		अगर (mountpoपूर्णांक != m->mnt.mnt_root) अणु
			path->mnt = &m->mnt;
			path->dentry = mountpoपूर्णांक;
			*seqp = पढ़ो_seqcount_begin(&mountpoपूर्णांक->d_seq);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल bool choose_mountpoपूर्णांक(काष्ठा mount *m, स्थिर काष्ठा path *root,
			      काष्ठा path *path)
अणु
	bool found;

	rcu_पढ़ो_lock();
	जबतक (1) अणु
		अचिन्हित seq, mseq = पढ़ो_seqbegin(&mount_lock);

		found = choose_mountpoपूर्णांक_rcu(m, root, path, &seq);
		अगर (unlikely(!found)) अणु
			अगर (!पढ़ो_seqretry(&mount_lock, mseq))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (likely(__legitimize_path(path, seq, mseq)))
				अवरोध;
			rcu_पढ़ो_unlock();
			path_put(path);
			rcu_पढ़ो_lock();
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस found;
पूर्ण

/*
 * Perक्रमm an स्वतःmount
 * - वापस -EISसूची to tell follow_managed() to stop and वापस the path we
 *   were called with.
 */
अटल पूर्णांक follow_स्वतःmount(काष्ठा path *path, पूर्णांक *count, अचिन्हित lookup_flags)
अणु
	काष्ठा dentry *dentry = path->dentry;

	/* We करोn't want to mount if someone's just करोing a stat -
	 * unless they're stat'ing a directory and appended a '/' to
	 * the name.
	 *
	 * We करो, however, want to mount अगर someone wants to खोलो or
	 * create a file of any type under the mountpoपूर्णांक, wants to
	 * traverse through the mountpoपूर्णांक or wants to खोलो the
	 * mounted directory.  Also, स्वतःfs may mark negative dentries
	 * as being स्वतःmount poपूर्णांकs.  These will need the attentions
	 * of the daemon to instantiate them beक्रमe they can be used.
	 */
	अगर (!(lookup_flags & (LOOKUP_PARENT | LOOKUP_सूचीECTORY |
			   LOOKUP_OPEN | LOOKUP_CREATE | LOOKUP_AUTOMOUNT)) &&
	    dentry->d_inode)
		वापस -EISसूची;

	अगर (count && (*count)++ >= MAXSYMLINKS)
		वापस -ELOOP;

	वापस finish_स्वतःmount(dentry->d_op->d_स्वतःmount(path), path);
पूर्ण

/*
 * mount traversal - out-of-line part.  One note on ->d_flags accesses -
 * dentries are pinned but not locked here, so negative dentry can go
 * positive right under us.  Use of smp_load_acquire() provides a barrier
 * sufficient क्रम ->d_inode and ->d_flags consistency.
 */
अटल पूर्णांक __traverse_mounts(काष्ठा path *path, अचिन्हित flags, bool *jumped,
			     पूर्णांक *count, अचिन्हित lookup_flags)
अणु
	काष्ठा vfsmount *mnt = path->mnt;
	bool need_mntput = false;
	पूर्णांक ret = 0;

	जबतक (flags & DCACHE_MANAGED_DENTRY) अणु
		/* Allow the fileप्रणाली to manage the transit without i_mutex
		 * being held. */
		अगर (flags & DCACHE_MANAGE_TRANSIT) अणु
			ret = path->dentry->d_op->d_manage(path, false);
			flags = smp_load_acquire(&path->dentry->d_flags);
			अगर (ret < 0)
				अवरोध;
		पूर्ण

		अगर (flags & DCACHE_MOUNTED) अणु	// something's mounted on it..
			काष्ठा vfsmount *mounted = lookup_mnt(path);
			अगर (mounted) अणु		// ... in our namespace
				dput(path->dentry);
				अगर (need_mntput)
					mntput(path->mnt);
				path->mnt = mounted;
				path->dentry = dget(mounted->mnt_root);
				// here we know it's positive
				flags = path->dentry->d_flags;
				need_mntput = true;
				जारी;
			पूर्ण
		पूर्ण

		अगर (!(flags & DCACHE_NEED_AUTOMOUNT))
			अवरोध;

		// uncovered स्वतःmount poपूर्णांक
		ret = follow_स्वतःmount(path, count, lookup_flags);
		flags = smp_load_acquire(&path->dentry->d_flags);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	अगर (ret == -EISसूची)
		ret = 0;
	// possible अगर you race with several mount --move
	अगर (need_mntput && path->mnt == mnt)
		mntput(path->mnt);
	अगर (!ret && unlikely(d_flags_negative(flags)))
		ret = -ENOENT;
	*jumped = need_mntput;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक traverse_mounts(काष्ठा path *path, bool *jumped,
				  पूर्णांक *count, अचिन्हित lookup_flags)
अणु
	अचिन्हित flags = smp_load_acquire(&path->dentry->d_flags);

	/* fastpath */
	अगर (likely(!(flags & DCACHE_MANAGED_DENTRY))) अणु
		*jumped = false;
		अगर (unlikely(d_flags_negative(flags)))
			वापस -ENOENT;
		वापस 0;
	पूर्ण
	वापस __traverse_mounts(path, flags, jumped, count, lookup_flags);
पूर्ण

पूर्णांक follow_करोwn_one(काष्ठा path *path)
अणु
	काष्ठा vfsmount *mounted;

	mounted = lookup_mnt(path);
	अगर (mounted) अणु
		dput(path->dentry);
		mntput(path->mnt);
		path->mnt = mounted;
		path->dentry = dget(mounted->mnt_root);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(follow_करोwn_one);

/*
 * Follow करोwn to the covering mount currently visible to userspace.  At each
 * poपूर्णांक, the fileप्रणाली owning that dentry may be queried as to whether the
 * caller is permitted to proceed or not.
 */
पूर्णांक follow_करोwn(काष्ठा path *path)
अणु
	काष्ठा vfsmount *mnt = path->mnt;
	bool jumped;
	पूर्णांक ret = traverse_mounts(path, &jumped, शून्य, 0);

	अगर (path->mnt != mnt)
		mntput(mnt);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(follow_करोwn);

/*
 * Try to skip to top of mountpoपूर्णांक pile in rcuwalk mode.  Fail अगर
 * we meet a managed dentry that would need blocking.
 */
अटल bool __follow_mount_rcu(काष्ठा nameidata *nd, काष्ठा path *path,
			       काष्ठा inode **inode, अचिन्हित *seqp)
अणु
	काष्ठा dentry *dentry = path->dentry;
	अचिन्हित पूर्णांक flags = dentry->d_flags;

	अगर (likely(!(flags & DCACHE_MANAGED_DENTRY)))
		वापस true;

	अगर (unlikely(nd->flags & LOOKUP_NO_XDEV))
		वापस false;

	क्रम (;;) अणु
		/*
		 * Don't क्रमget we might have a non-mountpoपूर्णांक managed dentry
		 * that wants to block transit.
		 */
		अगर (unlikely(flags & DCACHE_MANAGE_TRANSIT)) अणु
			पूर्णांक res = dentry->d_op->d_manage(path, true);
			अगर (res)
				वापस res == -EISसूची;
			flags = dentry->d_flags;
		पूर्ण

		अगर (flags & DCACHE_MOUNTED) अणु
			काष्ठा mount *mounted = __lookup_mnt(path->mnt, dentry);
			अगर (mounted) अणु
				path->mnt = &mounted->mnt;
				dentry = path->dentry = mounted->mnt.mnt_root;
				nd->flags |= LOOKUP_JUMPED;
				*seqp = पढ़ो_seqcount_begin(&dentry->d_seq);
				*inode = dentry->d_inode;
				/*
				 * We करोn't need to re-check ->d_seq after this
				 * ->d_inode पढ़ो - there will be an RCU delay
				 * between mount hash removal and ->mnt_root
				 * becoming unpinned.
				 */
				flags = dentry->d_flags;
				जारी;
			पूर्ण
			अगर (पढ़ो_seqretry(&mount_lock, nd->m_seq))
				वापस false;
		पूर्ण
		वापस !(flags & DCACHE_NEED_AUTOMOUNT);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक handle_mounts(काष्ठा nameidata *nd, काष्ठा dentry *dentry,
			  काष्ठा path *path, काष्ठा inode **inode,
			  अचिन्हित पूर्णांक *seqp)
अणु
	bool jumped;
	पूर्णांक ret;

	path->mnt = nd->path.mnt;
	path->dentry = dentry;
	अगर (nd->flags & LOOKUP_RCU) अणु
		अचिन्हित पूर्णांक seq = *seqp;
		अगर (unlikely(!*inode))
			वापस -ENOENT;
		अगर (likely(__follow_mount_rcu(nd, path, inode, seqp)))
			वापस 0;
		अगर (!try_to_unlazy_next(nd, dentry, seq))
			वापस -ECHILD;
		// *path might've been clobbered by __follow_mount_rcu()
		path->mnt = nd->path.mnt;
		path->dentry = dentry;
	पूर्ण
	ret = traverse_mounts(path, &jumped, &nd->total_link_count, nd->flags);
	अगर (jumped) अणु
		अगर (unlikely(nd->flags & LOOKUP_NO_XDEV))
			ret = -EXDEV;
		अन्यथा
			nd->flags |= LOOKUP_JUMPED;
	पूर्ण
	अगर (unlikely(ret)) अणु
		dput(path->dentry);
		अगर (path->mnt != nd->path.mnt)
			mntput(path->mnt);
	पूर्ण अन्यथा अणु
		*inode = d_backing_inode(path->dentry);
		*seqp = 0; /* out of RCU mode, so the value करोesn't matter */
	पूर्ण
	वापस ret;
पूर्ण

/*
 * This looks up the name in dcache and possibly revalidates the found dentry.
 * शून्य is वापसed अगर the dentry करोes not exist in the cache.
 */
अटल काष्ठा dentry *lookup_dcache(स्थिर काष्ठा qstr *name,
				    काष्ठा dentry *dir,
				    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dentry = d_lookup(dir, name);
	अगर (dentry) अणु
		पूर्णांक error = d_revalidate(dentry, flags);
		अगर (unlikely(error <= 0)) अणु
			अगर (!error)
				d_invalidate(dentry);
			dput(dentry);
			वापस ERR_PTR(error);
		पूर्ण
	पूर्ण
	वापस dentry;
पूर्ण

/*
 * Parent directory has inode locked exclusive.  This is one
 * and only हाल when ->lookup() माला_लो called on non in-lookup
 * dentries - as the matter of fact, this only माला_लो called
 * when directory is guaranteed to have no in-lookup children
 * at all.
 */
अटल काष्ठा dentry *__lookup_hash(स्थिर काष्ठा qstr *name,
		काष्ठा dentry *base, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dentry = lookup_dcache(name, base, flags);
	काष्ठा dentry *old;
	काष्ठा inode *dir = base->d_inode;

	अगर (dentry)
		वापस dentry;

	/* Don't create child dentry क्रम a dead directory. */
	अगर (unlikely(IS_DEADसूची(dir)))
		वापस ERR_PTR(-ENOENT);

	dentry = d_alloc(base, name);
	अगर (unlikely(!dentry))
		वापस ERR_PTR(-ENOMEM);

	old = dir->i_op->lookup(dir, dentry, flags);
	अगर (unlikely(old)) अणु
		dput(dentry);
		dentry = old;
	पूर्ण
	वापस dentry;
पूर्ण

अटल काष्ठा dentry *lookup_fast(काष्ठा nameidata *nd,
				  काष्ठा inode **inode,
			          अचिन्हित *seqp)
अणु
	काष्ठा dentry *dentry, *parent = nd->path.dentry;
	पूर्णांक status = 1;

	/*
	 * Rename seqlock is not required here because in the off chance
	 * of a false negative due to a concurrent नाम, the caller is
	 * going to fall back to non-racy lookup.
	 */
	अगर (nd->flags & LOOKUP_RCU) अणु
		अचिन्हित seq;
		dentry = __d_lookup_rcu(parent, &nd->last, &seq);
		अगर (unlikely(!dentry)) अणु
			अगर (!try_to_unlazy(nd))
				वापस ERR_PTR(-ECHILD);
			वापस शून्य;
		पूर्ण

		/*
		 * This sequence count validates that the inode matches
		 * the dentry name inक्रमmation from lookup.
		 */
		*inode = d_backing_inode(dentry);
		अगर (unlikely(पढ़ो_seqcount_retry(&dentry->d_seq, seq)))
			वापस ERR_PTR(-ECHILD);

		/*
		 * This sequence count validates that the parent had no
		 * changes जबतक we did the lookup of the dentry above.
		 *
		 * The memory barrier in पढ़ो_seqcount_begin of child is
		 *  enough, we can use __पढ़ो_seqcount_retry here.
		 */
		अगर (unlikely(__पढ़ो_seqcount_retry(&parent->d_seq, nd->seq)))
			वापस ERR_PTR(-ECHILD);

		*seqp = seq;
		status = d_revalidate(dentry, nd->flags);
		अगर (likely(status > 0))
			वापस dentry;
		अगर (!try_to_unlazy_next(nd, dentry, seq))
			वापस ERR_PTR(-ECHILD);
		अगर (status == -ECHILD)
			/* we'd been told to reकरो it in non-rcu mode */
			status = d_revalidate(dentry, nd->flags);
	पूर्ण अन्यथा अणु
		dentry = __d_lookup(parent, &nd->last);
		अगर (unlikely(!dentry))
			वापस शून्य;
		status = d_revalidate(dentry, nd->flags);
	पूर्ण
	अगर (unlikely(status <= 0)) अणु
		अगर (!status)
			d_invalidate(dentry);
		dput(dentry);
		वापस ERR_PTR(status);
	पूर्ण
	वापस dentry;
पूर्ण

/* Fast lookup failed, करो it the slow way */
अटल काष्ठा dentry *__lookup_slow(स्थिर काष्ठा qstr *name,
				    काष्ठा dentry *dir,
				    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dentry, *old;
	काष्ठा inode *inode = dir->d_inode;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	/* Don't go there if it's alपढ़ोy dead */
	अगर (unlikely(IS_DEADसूची(inode)))
		वापस ERR_PTR(-ENOENT);
again:
	dentry = d_alloc_parallel(dir, name, &wq);
	अगर (IS_ERR(dentry))
		वापस dentry;
	अगर (unlikely(!d_in_lookup(dentry))) अणु
		पूर्णांक error = d_revalidate(dentry, flags);
		अगर (unlikely(error <= 0)) अणु
			अगर (!error) अणु
				d_invalidate(dentry);
				dput(dentry);
				जाओ again;
			पूर्ण
			dput(dentry);
			dentry = ERR_PTR(error);
		पूर्ण
	पूर्ण अन्यथा अणु
		old = inode->i_op->lookup(inode, dentry, flags);
		d_lookup_करोne(dentry);
		अगर (unlikely(old)) अणु
			dput(dentry);
			dentry = old;
		पूर्ण
	पूर्ण
	वापस dentry;
पूर्ण

अटल काष्ठा dentry *lookup_slow(स्थिर काष्ठा qstr *name,
				  काष्ठा dentry *dir,
				  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = dir->d_inode;
	काष्ठा dentry *res;
	inode_lock_shared(inode);
	res = __lookup_slow(name, dir, flags);
	inode_unlock_shared(inode);
	वापस res;
पूर्ण

अटल अंतरभूत पूर्णांक may_lookup(काष्ठा user_namespace *mnt_userns,
			     काष्ठा nameidata *nd)
अणु
	अगर (nd->flags & LOOKUP_RCU) अणु
		पूर्णांक err = inode_permission(mnt_userns, nd->inode, MAY_EXEC|MAY_NOT_BLOCK);
		अगर (err != -ECHILD || !try_to_unlazy(nd))
			वापस err;
	पूर्ण
	वापस inode_permission(mnt_userns, nd->inode, MAY_EXEC);
पूर्ण

अटल पूर्णांक reserve_stack(काष्ठा nameidata *nd, काष्ठा path *link, अचिन्हित seq)
अणु
	अगर (unlikely(nd->total_link_count++ >= MAXSYMLINKS))
		वापस -ELOOP;

	अगर (likely(nd->depth != EMBEDDED_LEVELS))
		वापस 0;
	अगर (likely(nd->stack != nd->पूर्णांकernal))
		वापस 0;
	अगर (likely(nd_alloc_stack(nd)))
		वापस 0;

	अगर (nd->flags & LOOKUP_RCU) अणु
		// we need to grab link beक्रमe we करो unlazy.  And we can't skip
		// unlazy even अगर we fail to grab the link - cleanup needs it
		bool grabbed_link = legitimize_path(nd, link, seq);

		अगर (!try_to_unlazy(nd) != 0 || !grabbed_link)
			वापस -ECHILD;

		अगर (nd_alloc_stack(nd))
			वापस 0;
	पूर्ण
	वापस -ENOMEM;
पूर्ण

क्रमागत अणुWALK_TRAILING = 1, WALK_MORE = 2, WALK_NOFOLLOW = 4पूर्ण;

अटल स्थिर अक्षर *pick_link(काष्ठा nameidata *nd, काष्ठा path *link,
		     काष्ठा inode *inode, अचिन्हित seq, पूर्णांक flags)
अणु
	काष्ठा saved *last;
	स्थिर अक्षर *res;
	पूर्णांक error = reserve_stack(nd, link, seq);

	अगर (unlikely(error)) अणु
		अगर (!(nd->flags & LOOKUP_RCU))
			path_put(link);
		वापस ERR_PTR(error);
	पूर्ण
	last = nd->stack + nd->depth++;
	last->link = *link;
	clear_delayed_call(&last->करोne);
	last->seq = seq;

	अगर (flags & WALK_TRAILING) अणु
		error = may_follow_link(nd, inode);
		अगर (unlikely(error))
			वापस ERR_PTR(error);
	पूर्ण

	अगर (unlikely(nd->flags & LOOKUP_NO_SYMLINKS) ||
			unlikely(link->mnt->mnt_flags & MNT_NOSYMFOLLOW))
		वापस ERR_PTR(-ELOOP);

	अगर (!(nd->flags & LOOKUP_RCU)) अणु
		touch_aसमय(&last->link);
		cond_resched();
	पूर्ण अन्यथा अगर (aसमय_needs_update(&last->link, inode)) अणु
		अगर (!try_to_unlazy(nd))
			वापस ERR_PTR(-ECHILD);
		touch_aसमय(&last->link);
	पूर्ण

	error = security_inode_follow_link(link->dentry, inode,
					   nd->flags & LOOKUP_RCU);
	अगर (unlikely(error))
		वापस ERR_PTR(error);

	res = READ_ONCE(inode->i_link);
	अगर (!res) अणु
		स्थिर अक्षर * (*get)(काष्ठा dentry *, काष्ठा inode *,
				काष्ठा delayed_call *);
		get = inode->i_op->get_link;
		अगर (nd->flags & LOOKUP_RCU) अणु
			res = get(शून्य, inode, &last->करोne);
			अगर (res == ERR_PTR(-ECHILD) && try_to_unlazy(nd))
				res = get(link->dentry, inode, &last->करोne);
		पूर्ण अन्यथा अणु
			res = get(link->dentry, inode, &last->करोne);
		पूर्ण
		अगर (!res)
			जाओ all_करोne;
		अगर (IS_ERR(res))
			वापस res;
	पूर्ण
	अगर (*res == '/') अणु
		error = nd_jump_root(nd);
		अगर (unlikely(error))
			वापस ERR_PTR(error);
		जबतक (unlikely(*++res == '/'))
			;
	पूर्ण
	अगर (*res)
		वापस res;
all_करोne: // pure jump
	put_link(nd);
	वापस शून्य;
पूर्ण

/*
 * Do we need to follow links? We _really_ want to be able
 * to करो this check without having to look at inode->i_op,
 * so we keep a cache of "no, this doesn't need follow_link"
 * क्रम the common हाल.
 */
अटल स्थिर अक्षर *step_पूर्णांकo(काष्ठा nameidata *nd, पूर्णांक flags,
		     काष्ठा dentry *dentry, काष्ठा inode *inode, अचिन्हित seq)
अणु
	काष्ठा path path;
	पूर्णांक err = handle_mounts(nd, dentry, &path, &inode, &seq);

	अगर (err < 0)
		वापस ERR_PTR(err);
	अगर (likely(!d_is_symlink(path.dentry)) ||
	   ((flags & WALK_TRAILING) && !(nd->flags & LOOKUP_FOLLOW)) ||
	   (flags & WALK_NOFOLLOW)) अणु
		/* not a symlink or should not follow */
		अगर (!(nd->flags & LOOKUP_RCU)) अणु
			dput(nd->path.dentry);
			अगर (nd->path.mnt != path.mnt)
				mntput(nd->path.mnt);
		पूर्ण
		nd->path = path;
		nd->inode = inode;
		nd->seq = seq;
		वापस शून्य;
	पूर्ण
	अगर (nd->flags & LOOKUP_RCU) अणु
		/* make sure that d_is_symlink above matches inode */
		अगर (पढ़ो_seqcount_retry(&path.dentry->d_seq, seq))
			वापस ERR_PTR(-ECHILD);
	पूर्ण अन्यथा अणु
		अगर (path.mnt == nd->path.mnt)
			mntget(path.mnt);
	पूर्ण
	वापस pick_link(nd, &path, inode, seq, flags);
पूर्ण

अटल काष्ठा dentry *follow_करोtकरोt_rcu(काष्ठा nameidata *nd,
					काष्ठा inode **inodep,
					अचिन्हित *seqp)
अणु
	काष्ठा dentry *parent, *old;

	अगर (path_equal(&nd->path, &nd->root))
		जाओ in_root;
	अगर (unlikely(nd->path.dentry == nd->path.mnt->mnt_root)) अणु
		काष्ठा path path;
		अचिन्हित seq;
		अगर (!choose_mountpoपूर्णांक_rcu(real_mount(nd->path.mnt),
					   &nd->root, &path, &seq))
			जाओ in_root;
		अगर (unlikely(nd->flags & LOOKUP_NO_XDEV))
			वापस ERR_PTR(-ECHILD);
		nd->path = path;
		nd->inode = path.dentry->d_inode;
		nd->seq = seq;
		अगर (unlikely(पढ़ो_seqretry(&mount_lock, nd->m_seq)))
			वापस ERR_PTR(-ECHILD);
		/* we know that mountpoपूर्णांक was pinned */
	पूर्ण
	old = nd->path.dentry;
	parent = old->d_parent;
	*inodep = parent->d_inode;
	*seqp = पढ़ो_seqcount_begin(&parent->d_seq);
	अगर (unlikely(पढ़ो_seqcount_retry(&old->d_seq, nd->seq)))
		वापस ERR_PTR(-ECHILD);
	अगर (unlikely(!path_connected(nd->path.mnt, parent)))
		वापस ERR_PTR(-ECHILD);
	वापस parent;
in_root:
	अगर (unlikely(पढ़ो_seqretry(&mount_lock, nd->m_seq)))
		वापस ERR_PTR(-ECHILD);
	अगर (unlikely(nd->flags & LOOKUP_BENEATH))
		वापस ERR_PTR(-ECHILD);
	वापस शून्य;
पूर्ण

अटल काष्ठा dentry *follow_करोtकरोt(काष्ठा nameidata *nd,
				 काष्ठा inode **inodep,
				 अचिन्हित *seqp)
अणु
	काष्ठा dentry *parent;

	अगर (path_equal(&nd->path, &nd->root))
		जाओ in_root;
	अगर (unlikely(nd->path.dentry == nd->path.mnt->mnt_root)) अणु
		काष्ठा path path;

		अगर (!choose_mountpoपूर्णांक(real_mount(nd->path.mnt),
				       &nd->root, &path))
			जाओ in_root;
		path_put(&nd->path);
		nd->path = path;
		nd->inode = path.dentry->d_inode;
		अगर (unlikely(nd->flags & LOOKUP_NO_XDEV))
			वापस ERR_PTR(-EXDEV);
	पूर्ण
	/* rare हाल of legitimate dget_parent()... */
	parent = dget_parent(nd->path.dentry);
	अगर (unlikely(!path_connected(nd->path.mnt, parent))) अणु
		dput(parent);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	*seqp = 0;
	*inodep = parent->d_inode;
	वापस parent;

in_root:
	अगर (unlikely(nd->flags & LOOKUP_BENEATH))
		वापस ERR_PTR(-EXDEV);
	dget(nd->path.dentry);
	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *handle_करोts(काष्ठा nameidata *nd, पूर्णांक type)
अणु
	अगर (type == LAST_DOTDOT) अणु
		स्थिर अक्षर *error = शून्य;
		काष्ठा dentry *parent;
		काष्ठा inode *inode;
		अचिन्हित seq;

		अगर (!nd->root.mnt) अणु
			error = ERR_PTR(set_root(nd));
			अगर (error)
				वापस error;
		पूर्ण
		अगर (nd->flags & LOOKUP_RCU)
			parent = follow_करोtकरोt_rcu(nd, &inode, &seq);
		अन्यथा
			parent = follow_करोtकरोt(nd, &inode, &seq);
		अगर (IS_ERR(parent))
			वापस ERR_CAST(parent);
		अगर (unlikely(!parent))
			error = step_पूर्णांकo(nd, WALK_NOFOLLOW,
					 nd->path.dentry, nd->inode, nd->seq);
		अन्यथा
			error = step_पूर्णांकo(nd, WALK_NOFOLLOW,
					 parent, inode, seq);
		अगर (unlikely(error))
			वापस error;

		अगर (unlikely(nd->flags & LOOKUP_IS_SCOPED)) अणु
			/*
			 * If there was a racing नाम or mount aदीर्घ our
			 * path, then we can't be sure that ".." hasn't jumped
			 * above nd->root (and so userspace should retry or use
			 * some fallback).
			 */
			smp_rmb();
			अगर (unlikely(__पढ़ो_seqcount_retry(&mount_lock.seqcount, nd->m_seq)))
				वापस ERR_PTR(-EAGAIN);
			अगर (unlikely(__पढ़ो_seqcount_retry(&नाम_lock.seqcount, nd->r_seq)))
				वापस ERR_PTR(-EAGAIN);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *walk_component(काष्ठा nameidata *nd, पूर्णांक flags)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	अचिन्हित seq;
	/*
	 * "." and ".." are special - ".." especially so because it has
	 * to be able to know about the current root directory and
	 * parent relationships.
	 */
	अगर (unlikely(nd->last_type != LAST_NORM)) अणु
		अगर (!(flags & WALK_MORE) && nd->depth)
			put_link(nd);
		वापस handle_करोts(nd, nd->last_type);
	पूर्ण
	dentry = lookup_fast(nd, &inode, &seq);
	अगर (IS_ERR(dentry))
		वापस ERR_CAST(dentry);
	अगर (unlikely(!dentry)) अणु
		dentry = lookup_slow(&nd->last, nd->path.dentry, nd->flags);
		अगर (IS_ERR(dentry))
			वापस ERR_CAST(dentry);
	पूर्ण
	अगर (!(flags & WALK_MORE) && nd->depth)
		put_link(nd);
	वापस step_पूर्णांकo(nd, flags, dentry, inode, seq);
पूर्ण

/*
 * We can करो the critical dentry name comparison and hashing
 * operations one word at a समय, but we are limited to:
 *
 * - Architectures with fast unaligned word accesses. We could
 *   करो a "get_unaligned()" अगर this helps and is sufficiently
 *   fast.
 *
 * - non-CONFIG_DEBUG_PAGEALLOC configurations (so that we
 *   करो not trap on the (extremely unlikely) हाल of a page
 *   crossing operation.
 *
 * - Furthermore, we need an efficient 64-bit compile क्रम the
 *   64-bit हाल in order to generate the "number of bytes in
 *   the final mask". Again, that could be replaced with a
 *   efficient population count inकाष्ठाion or similar.
 */
#अगर_घोषित CONFIG_DCACHE_WORD_ACCESS

#समावेश <यंत्र/word-at-a-समय.स>

#अगर_घोषित HASH_MIX

/* Architecture provides HASH_MIX and fold_hash() in <यंत्र/hash.h> */

#या_अगर defined(CONFIG_64BIT)
/*
 * Register pressure in the mixing function is an issue, particularly
 * on 32-bit x86, but almost any function requires one state value and
 * one temporary.  Instead, use a function deचिन्हित क्रम two state values
 * and no temporaries.
 *
 * This function cannot create a collision in only two iterations, so
 * we have two iterations to achieve avalanche.  In those two iterations,
 * we have six layers of mixing, which is enough to spपढ़ो one bit's
 * influence out to 2^6 = 64 state bits.
 *
 * Rotate स्थिरants are scored by considering either 64 one-bit input
 * deltas or 64*63/2 = 2016 two-bit input deltas, and finding the
 * probability of that delta causing a change to each of the 128 output
 * bits, using a sample of अक्रमom initial states.
 *
 * The Shannon entropy of the computed probabilities is then summed
 * to produce a score.  Ideally, any input change has a 50% chance of
 * toggling any given output bit.
 *
 * Mixing scores (in bits) क्रम (12,45):
 * Input delta: 1-bit      2-bit
 * 1 round:     713.3    42542.6
 * 2 rounds:   2753.7   140389.8
 * 3 rounds:   5954.1   233458.2
 * 4 rounds:   7862.6   256672.2
 * Perfect:    8192     258048
 *            (64*128) (64*63/2 * 128)
 */
#घोषणा HASH_MIX(x, y, a)	\
	(	x ^= (a),	\
	y ^= x,	x = rol64(x,12),\
	x += y,	y = rol64(y,45),\
	y *= 9			)

/*
 * Fold two दीर्घs पूर्णांकo one 32-bit hash value.  This must be fast, but
 * latency isn't quite as critical, as there is a fair bit of additional
 * work करोne beक्रमe the hash value is used.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fold_hash(अचिन्हित दीर्घ x, अचिन्हित दीर्घ y)
अणु
	y ^= x * GOLDEN_RATIO_64;
	y *= GOLDEN_RATIO_64;
	वापस y >> 32;
पूर्ण

#अन्यथा	/* 32-bit हाल */

/*
 * Mixing scores (in bits) क्रम (7,20):
 * Input delta: 1-bit      2-bit
 * 1 round:     330.3     9201.6
 * 2 rounds:   1246.4    25475.4
 * 3 rounds:   1907.1    31295.1
 * 4 rounds:   2042.3    31718.6
 * Perfect:    2048      31744
 *            (32*64)   (32*31/2 * 64)
 */
#घोषणा HASH_MIX(x, y, a)	\
	(	x ^= (a),	\
	y ^= x,	x = rol32(x, 7),\
	x += y,	y = rol32(y,20),\
	y *= 9			)

अटल अंतरभूत अचिन्हित पूर्णांक fold_hash(अचिन्हित दीर्घ x, अचिन्हित दीर्घ y)
अणु
	/* Use arch-optimized multiply अगर one exists */
	वापस __hash_32(y ^ __hash_32(x));
पूर्ण

#पूर्ण_अगर

/*
 * Return the hash of a string of known length.  This is carfully
 * deचिन्हित to match hash_name(), which is the more critical function.
 * In particular, we must end by hashing a final word containing 0..7
 * payload bytes, to match the way that hash_name() iterates until it
 * finds the delimiter after the name.
 */
अचिन्हित पूर्णांक full_name_hash(स्थिर व्योम *salt, स्थिर अक्षर *name, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ a, x = 0, y = (अचिन्हित दीर्घ)salt;

	क्रम (;;) अणु
		अगर (!len)
			जाओ करोne;
		a = load_unaligned_zeropad(name);
		अगर (len < माप(अचिन्हित दीर्घ))
			अवरोध;
		HASH_MIX(x, y, a);
		name += माप(अचिन्हित दीर्घ);
		len -= माप(अचिन्हित दीर्घ);
	पूर्ण
	x ^= a & bytemask_from_count(len);
करोne:
	वापस fold_hash(x, y);
पूर्ण
EXPORT_SYMBOL(full_name_hash);

/* Return the "hash_len" (hash and length) of a null-terminated string */
u64 hashlen_string(स्थिर व्योम *salt, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ a = 0, x = 0, y = (अचिन्हित दीर्घ)salt;
	अचिन्हित दीर्घ adata, mask, len;
	स्थिर काष्ठा word_at_a_समय स्थिरants = WORD_AT_A_TIME_CONSTANTS;

	len = 0;
	जाओ inside;

	करो अणु
		HASH_MIX(x, y, a);
		len += माप(अचिन्हित दीर्घ);
inside:
		a = load_unaligned_zeropad(name+len);
	पूर्ण जबतक (!has_zero(a, &adata, &स्थिरants));

	adata = prep_zero_mask(a, adata, &स्थिरants);
	mask = create_zero_mask(adata);
	x ^= a & zero_bytemask(mask);

	वापस hashlen_create(fold_hash(x, y), len + find_zero(mask));
पूर्ण
EXPORT_SYMBOL(hashlen_string);

/*
 * Calculate the length and hash of the path component, and
 * वापस the "hash_len" as the result.
 */
अटल अंतरभूत u64 hash_name(स्थिर व्योम *salt, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ a = 0, b, x = 0, y = (अचिन्हित दीर्घ)salt;
	अचिन्हित दीर्घ adata, bdata, mask, len;
	स्थिर काष्ठा word_at_a_समय स्थिरants = WORD_AT_A_TIME_CONSTANTS;

	len = 0;
	जाओ inside;

	करो अणु
		HASH_MIX(x, y, a);
		len += माप(अचिन्हित दीर्घ);
inside:
		a = load_unaligned_zeropad(name+len);
		b = a ^ REPEAT_BYTE('/');
	पूर्ण जबतक (!(has_zero(a, &adata, &स्थिरants) | has_zero(b, &bdata, &स्थिरants)));

	adata = prep_zero_mask(a, adata, &स्थिरants);
	bdata = prep_zero_mask(b, bdata, &स्थिरants);
	mask = create_zero_mask(adata | bdata);
	x ^= a & zero_bytemask(mask);

	वापस hashlen_create(fold_hash(x, y), len + find_zero(mask));
पूर्ण

#अन्यथा	/* !CONFIG_DCACHE_WORD_ACCESS: Slow, byte-at-a-समय version */

/* Return the hash of a string of known length */
अचिन्हित पूर्णांक full_name_hash(स्थिर व्योम *salt, स्थिर अक्षर *name, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ hash = init_name_hash(salt);
	जबतक (len--)
		hash = partial_name_hash((अचिन्हित अक्षर)*name++, hash);
	वापस end_name_hash(hash);
पूर्ण
EXPORT_SYMBOL(full_name_hash);

/* Return the "hash_len" (hash and length) of a null-terminated string */
u64 hashlen_string(स्थिर व्योम *salt, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ hash = init_name_hash(salt);
	अचिन्हित दीर्घ len = 0, c;

	c = (अचिन्हित अक्षर)*name;
	जबतक (c) अणु
		len++;
		hash = partial_name_hash(c, hash);
		c = (अचिन्हित अक्षर)name[len];
	पूर्ण
	वापस hashlen_create(end_name_hash(hash), len);
पूर्ण
EXPORT_SYMBOL(hashlen_string);

/*
 * We know there's a real path component here of at least
 * one अक्षरacter.
 */
अटल अंतरभूत u64 hash_name(स्थिर व्योम *salt, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ hash = init_name_hash(salt);
	अचिन्हित दीर्घ len = 0, c;

	c = (अचिन्हित अक्षर)*name;
	करो अणु
		len++;
		hash = partial_name_hash(c, hash);
		c = (अचिन्हित अक्षर)name[len];
	पूर्ण जबतक (c && c != '/');
	वापस hashlen_create(end_name_hash(hash), len);
पूर्ण

#पूर्ण_अगर

/*
 * Name resolution.
 * This is the basic name resolution function, turning a pathname पूर्णांकo
 * the final dentry. We expect 'base' to be positive and a directory.
 *
 * Returns 0 and nd will have valid dentry and mnt on success.
 * Returns error and drops reference to input namei data on failure.
 */
अटल पूर्णांक link_path_walk(स्थिर अक्षर *name, काष्ठा nameidata *nd)
अणु
	पूर्णांक depth = 0; // depth <= nd->depth
	पूर्णांक err;

	nd->last_type = LAST_ROOT;
	nd->flags |= LOOKUP_PARENT;
	अगर (IS_ERR(name))
		वापस PTR_ERR(name);
	जबतक (*name=='/')
		name++;
	अगर (!*name) अणु
		nd->dir_mode = 0; // लघु-circuit the 'hardening' idiocy
		वापस 0;
	पूर्ण

	/* At this poपूर्णांक we know we have a real path component. */
	क्रम(;;) अणु
		काष्ठा user_namespace *mnt_userns;
		स्थिर अक्षर *link;
		u64 hash_len;
		पूर्णांक type;

		mnt_userns = mnt_user_ns(nd->path.mnt);
		err = may_lookup(mnt_userns, nd);
		अगर (err)
			वापस err;

		hash_len = hash_name(nd->path.dentry, name);

		type = LAST_NORM;
		अगर (name[0] == '.') चयन (hashlen_len(hash_len)) अणु
			हाल 2:
				अगर (name[1] == '.') अणु
					type = LAST_DOTDOT;
					nd->flags |= LOOKUP_JUMPED;
				पूर्ण
				अवरोध;
			हाल 1:
				type = LAST_DOT;
		पूर्ण
		अगर (likely(type == LAST_NORM)) अणु
			काष्ठा dentry *parent = nd->path.dentry;
			nd->flags &= ~LOOKUP_JUMPED;
			अगर (unlikely(parent->d_flags & DCACHE_OP_HASH)) अणु
				काष्ठा qstr this = अणु अणु .hash_len = hash_len पूर्ण, .name = name पूर्ण;
				err = parent->d_op->d_hash(parent, &this);
				अगर (err < 0)
					वापस err;
				hash_len = this.hash_len;
				name = this.name;
			पूर्ण
		पूर्ण

		nd->last.hash_len = hash_len;
		nd->last.name = name;
		nd->last_type = type;

		name += hashlen_len(hash_len);
		अगर (!*name)
			जाओ OK;
		/*
		 * If it wasn't NUL, we know it was '/'. Skip that
		 * slash, and जारी until no more slashes.
		 */
		करो अणु
			name++;
		पूर्ण जबतक (unlikely(*name == '/'));
		अगर (unlikely(!*name)) अणु
OK:
			/* pathname or trailing symlink, करोne */
			अगर (!depth) अणु
				nd->dir_uid = i_uid_पूर्णांकo_mnt(mnt_userns, nd->inode);
				nd->dir_mode = nd->inode->i_mode;
				nd->flags &= ~LOOKUP_PARENT;
				वापस 0;
			पूर्ण
			/* last component of nested symlink */
			name = nd->stack[--depth].name;
			link = walk_component(nd, 0);
		पूर्ण अन्यथा अणु
			/* not the last component */
			link = walk_component(nd, WALK_MORE);
		पूर्ण
		अगर (unlikely(link)) अणु
			अगर (IS_ERR(link))
				वापस PTR_ERR(link);
			/* a symlink to follow */
			nd->stack[depth++].name = name;
			name = link;
			जारी;
		पूर्ण
		अगर (unlikely(!d_can_lookup(nd->path.dentry))) अणु
			अगर (nd->flags & LOOKUP_RCU) अणु
				अगर (!try_to_unlazy(nd))
					वापस -ECHILD;
			पूर्ण
			वापस -ENOTसूची;
		पूर्ण
	पूर्ण
पूर्ण

/* must be paired with terminate_walk() */
अटल स्थिर अक्षर *path_init(काष्ठा nameidata *nd, अचिन्हित flags)
अणु
	पूर्णांक error;
	स्थिर अक्षर *s = nd->name->name;

	/* LOOKUP_CACHED requires RCU, ask caller to retry */
	अगर ((flags & (LOOKUP_RCU | LOOKUP_CACHED)) == LOOKUP_CACHED)
		वापस ERR_PTR(-EAGAIN);

	अगर (!*s)
		flags &= ~LOOKUP_RCU;
	अगर (flags & LOOKUP_RCU)
		rcu_पढ़ो_lock();

	nd->flags = flags | LOOKUP_JUMPED;
	nd->depth = 0;

	nd->m_seq = __पढ़ो_seqcount_begin(&mount_lock.seqcount);
	nd->r_seq = __पढ़ो_seqcount_begin(&नाम_lock.seqcount);
	smp_rmb();

	अगर (flags & LOOKUP_ROOT) अणु
		काष्ठा dentry *root = nd->root.dentry;
		काष्ठा inode *inode = root->d_inode;
		अगर (*s && unlikely(!d_can_lookup(root)))
			वापस ERR_PTR(-ENOTसूची);
		nd->path = nd->root;
		nd->inode = inode;
		अगर (flags & LOOKUP_RCU) अणु
			nd->seq = पढ़ो_seqcount_begin(&nd->path.dentry->d_seq);
			nd->root_seq = nd->seq;
		पूर्ण अन्यथा अणु
			path_get(&nd->path);
		पूर्ण
		वापस s;
	पूर्ण

	nd->root.mnt = शून्य;

	/* Absolute pathname -- fetch the root (LOOKUP_IN_ROOT uses nd->dfd). */
	अगर (*s == '/' && !(flags & LOOKUP_IN_ROOT)) अणु
		error = nd_jump_root(nd);
		अगर (unlikely(error))
			वापस ERR_PTR(error);
		वापस s;
	पूर्ण

	/* Relative pathname -- get the starting-poपूर्णांक it is relative to. */
	अगर (nd->dfd == AT_FDCWD) अणु
		अगर (flags & LOOKUP_RCU) अणु
			काष्ठा fs_काष्ठा *fs = current->fs;
			अचिन्हित seq;

			करो अणु
				seq = पढ़ो_seqcount_begin(&fs->seq);
				nd->path = fs->pwd;
				nd->inode = nd->path.dentry->d_inode;
				nd->seq = __पढ़ो_seqcount_begin(&nd->path.dentry->d_seq);
			पूर्ण जबतक (पढ़ो_seqcount_retry(&fs->seq, seq));
		पूर्ण अन्यथा अणु
			get_fs_pwd(current->fs, &nd->path);
			nd->inode = nd->path.dentry->d_inode;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Caller must check execute permissions on the starting path component */
		काष्ठा fd f = fdget_raw(nd->dfd);
		काष्ठा dentry *dentry;

		अगर (!f.file)
			वापस ERR_PTR(-EBADF);

		dentry = f.file->f_path.dentry;

		अगर (*s && unlikely(!d_can_lookup(dentry))) अणु
			fdput(f);
			वापस ERR_PTR(-ENOTसूची);
		पूर्ण

		nd->path = f.file->f_path;
		अगर (flags & LOOKUP_RCU) अणु
			nd->inode = nd->path.dentry->d_inode;
			nd->seq = पढ़ो_seqcount_begin(&nd->path.dentry->d_seq);
		पूर्ण अन्यथा अणु
			path_get(&nd->path);
			nd->inode = nd->path.dentry->d_inode;
		पूर्ण
		fdput(f);
	पूर्ण

	/* For scoped-lookups we need to set the root to the dirfd as well. */
	अगर (flags & LOOKUP_IS_SCOPED) अणु
		nd->root = nd->path;
		अगर (flags & LOOKUP_RCU) अणु
			nd->root_seq = nd->seq;
		पूर्ण अन्यथा अणु
			path_get(&nd->root);
			nd->flags |= LOOKUP_ROOT_GRABBED;
		पूर्ण
	पूर्ण
	वापस s;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *lookup_last(काष्ठा nameidata *nd)
अणु
	अगर (nd->last_type == LAST_NORM && nd->last.name[nd->last.len])
		nd->flags |= LOOKUP_FOLLOW | LOOKUP_सूचीECTORY;

	वापस walk_component(nd, WALK_TRAILING);
पूर्ण

अटल पूर्णांक handle_lookup_करोwn(काष्ठा nameidata *nd)
अणु
	अगर (!(nd->flags & LOOKUP_RCU))
		dget(nd->path.dentry);
	वापस PTR_ERR(step_पूर्णांकo(nd, WALK_NOFOLLOW,
			nd->path.dentry, nd->inode, nd->seq));
पूर्ण

/* Returns 0 and nd will be valid on success; Retuns error, otherwise. */
अटल पूर्णांक path_lookupat(काष्ठा nameidata *nd, अचिन्हित flags, काष्ठा path *path)
अणु
	स्थिर अक्षर *s = path_init(nd, flags);
	पूर्णांक err;

	अगर (unlikely(flags & LOOKUP_DOWN) && !IS_ERR(s)) अणु
		err = handle_lookup_करोwn(nd);
		अगर (unlikely(err < 0))
			s = ERR_PTR(err);
	पूर्ण

	जबतक (!(err = link_path_walk(s, nd)) &&
	       (s = lookup_last(nd)) != शून्य)
		;
	अगर (!err && unlikely(nd->flags & LOOKUP_MOUNTPOINT)) अणु
		err = handle_lookup_करोwn(nd);
		nd->flags &= ~LOOKUP_JUMPED; // no d_weak_revalidate(), please...
	पूर्ण
	अगर (!err)
		err = complete_walk(nd);

	अगर (!err && nd->flags & LOOKUP_सूचीECTORY)
		अगर (!d_can_lookup(nd->path.dentry))
			err = -ENOTसूची;
	अगर (!err) अणु
		*path = nd->path;
		nd->path.mnt = शून्य;
		nd->path.dentry = शून्य;
	पूर्ण
	terminate_walk(nd);
	वापस err;
पूर्ण

पूर्णांक filename_lookup(पूर्णांक dfd, काष्ठा filename *name, अचिन्हित flags,
		    काष्ठा path *path, काष्ठा path *root)
अणु
	पूर्णांक retval;
	काष्ठा nameidata nd;
	अगर (IS_ERR(name))
		वापस PTR_ERR(name);
	अगर (unlikely(root)) अणु
		nd.root = *root;
		flags |= LOOKUP_ROOT;
	पूर्ण
	set_nameidata(&nd, dfd, name);
	retval = path_lookupat(&nd, flags | LOOKUP_RCU, path);
	अगर (unlikely(retval == -ECHILD))
		retval = path_lookupat(&nd, flags, path);
	अगर (unlikely(retval == -ESTALE))
		retval = path_lookupat(&nd, flags | LOOKUP_REVAL, path);

	अगर (likely(!retval))
		audit_inode(name, path->dentry,
			    flags & LOOKUP_MOUNTPOINT ? AUDIT_INODE_NOEVAL : 0);
	restore_nameidata();
	putname(name);
	वापस retval;
पूर्ण

/* Returns 0 and nd will be valid on success; Retuns error, otherwise. */
अटल पूर्णांक path_parentat(काष्ठा nameidata *nd, अचिन्हित flags,
				काष्ठा path *parent)
अणु
	स्थिर अक्षर *s = path_init(nd, flags);
	पूर्णांक err = link_path_walk(s, nd);
	अगर (!err)
		err = complete_walk(nd);
	अगर (!err) अणु
		*parent = nd->path;
		nd->path.mnt = शून्य;
		nd->path.dentry = शून्य;
	पूर्ण
	terminate_walk(nd);
	वापस err;
पूर्ण

अटल काष्ठा filename *filename_parentat(पूर्णांक dfd, काष्ठा filename *name,
				अचिन्हित पूर्णांक flags, काष्ठा path *parent,
				काष्ठा qstr *last, पूर्णांक *type)
अणु
	पूर्णांक retval;
	काष्ठा nameidata nd;

	अगर (IS_ERR(name))
		वापस name;
	set_nameidata(&nd, dfd, name);
	retval = path_parentat(&nd, flags | LOOKUP_RCU, parent);
	अगर (unlikely(retval == -ECHILD))
		retval = path_parentat(&nd, flags, parent);
	अगर (unlikely(retval == -ESTALE))
		retval = path_parentat(&nd, flags | LOOKUP_REVAL, parent);
	अगर (likely(!retval)) अणु
		*last = nd.last;
		*type = nd.last_type;
		audit_inode(name, parent->dentry, AUDIT_INODE_PARENT);
	पूर्ण अन्यथा अणु
		putname(name);
		name = ERR_PTR(retval);
	पूर्ण
	restore_nameidata();
	वापस name;
पूर्ण

/* करोes lookup, वापसs the object with parent locked */
काष्ठा dentry *kern_path_locked(स्थिर अक्षर *name, काष्ठा path *path)
अणु
	काष्ठा filename *filename;
	काष्ठा dentry *d;
	काष्ठा qstr last;
	पूर्णांक type;

	filename = filename_parentat(AT_FDCWD, getname_kernel(name), 0, path,
				    &last, &type);
	अगर (IS_ERR(filename))
		वापस ERR_CAST(filename);
	अगर (unlikely(type != LAST_NORM)) अणु
		path_put(path);
		putname(filename);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	inode_lock_nested(path->dentry->d_inode, I_MUTEX_PARENT);
	d = __lookup_hash(&last, path->dentry, 0);
	अगर (IS_ERR(d)) अणु
		inode_unlock(path->dentry->d_inode);
		path_put(path);
	पूर्ण
	putname(filename);
	वापस d;
पूर्ण

पूर्णांक kern_path(स्थिर अक्षर *name, अचिन्हित पूर्णांक flags, काष्ठा path *path)
अणु
	वापस filename_lookup(AT_FDCWD, getname_kernel(name),
			       flags, path, शून्य);
पूर्ण
EXPORT_SYMBOL(kern_path);

/**
 * vfs_path_lookup - lookup a file path relative to a dentry-vfsmount pair
 * @dentry:  poपूर्णांकer to dentry of the base directory
 * @mnt: poपूर्णांकer to vfs mount of the base directory
 * @name: poपूर्णांकer to file name
 * @flags: lookup flags
 * @path: poपूर्णांकer to काष्ठा path to fill
 */
पूर्णांक vfs_path_lookup(काष्ठा dentry *dentry, काष्ठा vfsmount *mnt,
		    स्थिर अक्षर *name, अचिन्हित पूर्णांक flags,
		    काष्ठा path *path)
अणु
	काष्ठा path root = अणु.mnt = mnt, .dentry = dentryपूर्ण;
	/* the first argument of filename_lookup() is ignored with root */
	वापस filename_lookup(AT_FDCWD, getname_kernel(name),
			       flags , path, &root);
पूर्ण
EXPORT_SYMBOL(vfs_path_lookup);

अटल पूर्णांक lookup_one_len_common(स्थिर अक्षर *name, काष्ठा dentry *base,
				 पूर्णांक len, काष्ठा qstr *this)
अणु
	this->name = name;
	this->len = len;
	this->hash = full_name_hash(base, name, len);
	अगर (!len)
		वापस -EACCES;

	अगर (unlikely(name[0] == '.')) अणु
		अगर (len < 2 || (len == 2 && name[1] == '.'))
			वापस -EACCES;
	पूर्ण

	जबतक (len--) अणु
		अचिन्हित पूर्णांक c = *(स्थिर अचिन्हित अक्षर *)name++;
		अगर (c == '/' || c == '\0')
			वापस -EACCES;
	पूर्ण
	/*
	 * See अगर the low-level fileप्रणाली might want
	 * to use its own hash..
	 */
	अगर (base->d_flags & DCACHE_OP_HASH) अणु
		पूर्णांक err = base->d_op->d_hash(base, this);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस inode_permission(&init_user_ns, base->d_inode, MAY_EXEC);
पूर्ण

/**
 * try_lookup_one_len - fileप्रणाली helper to lookup single pathname component
 * @name:	pathname component to lookup
 * @base:	base directory to lookup from
 * @len:	maximum length @len should be पूर्णांकerpreted to
 *
 * Look up a dentry by name in the dcache, वापसing शून्य अगर it करोes not
 * currently exist.  The function करोes not try to create a dentry.
 *
 * Note that this routine is purely a helper क्रम fileप्रणाली usage and should
 * not be called by generic code.
 *
 * The caller must hold base->i_mutex.
 */
काष्ठा dentry *try_lookup_one_len(स्थिर अक्षर *name, काष्ठा dentry *base, पूर्णांक len)
अणु
	काष्ठा qstr this;
	पूर्णांक err;

	WARN_ON_ONCE(!inode_is_locked(base->d_inode));

	err = lookup_one_len_common(name, base, len, &this);
	अगर (err)
		वापस ERR_PTR(err);

	वापस lookup_dcache(&this, base, 0);
पूर्ण
EXPORT_SYMBOL(try_lookup_one_len);

/**
 * lookup_one_len - fileप्रणाली helper to lookup single pathname component
 * @name:	pathname component to lookup
 * @base:	base directory to lookup from
 * @len:	maximum length @len should be पूर्णांकerpreted to
 *
 * Note that this routine is purely a helper क्रम fileप्रणाली usage and should
 * not be called by generic code.
 *
 * The caller must hold base->i_mutex.
 */
काष्ठा dentry *lookup_one_len(स्थिर अक्षर *name, काष्ठा dentry *base, पूर्णांक len)
अणु
	काष्ठा dentry *dentry;
	काष्ठा qstr this;
	पूर्णांक err;

	WARN_ON_ONCE(!inode_is_locked(base->d_inode));

	err = lookup_one_len_common(name, base, len, &this);
	अगर (err)
		वापस ERR_PTR(err);

	dentry = lookup_dcache(&this, base, 0);
	वापस dentry ? dentry : __lookup_slow(&this, base, 0);
पूर्ण
EXPORT_SYMBOL(lookup_one_len);

/**
 * lookup_one_len_unlocked - fileप्रणाली helper to lookup single pathname component
 * @name:	pathname component to lookup
 * @base:	base directory to lookup from
 * @len:	maximum length @len should be पूर्णांकerpreted to
 *
 * Note that this routine is purely a helper क्रम fileप्रणाली usage and should
 * not be called by generic code.
 *
 * Unlike lookup_one_len, it should be called without the parent
 * i_mutex held, and will take the i_mutex itself अगर necessary.
 */
काष्ठा dentry *lookup_one_len_unlocked(स्थिर अक्षर *name,
				       काष्ठा dentry *base, पूर्णांक len)
अणु
	काष्ठा qstr this;
	पूर्णांक err;
	काष्ठा dentry *ret;

	err = lookup_one_len_common(name, base, len, &this);
	अगर (err)
		वापस ERR_PTR(err);

	ret = lookup_dcache(&this, base, 0);
	अगर (!ret)
		ret = lookup_slow(&this, base, 0);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(lookup_one_len_unlocked);

/*
 * Like lookup_one_len_unlocked(), except that it yields ERR_PTR(-ENOENT)
 * on negatives.  Returns known positive or ERR_PTR(); that's what
 * most of the users want.  Note that pinned negative with unlocked parent
 * _can_ become positive at any समय, so callers of lookup_one_len_unlocked()
 * need to be very careful; pinned positives have ->d_inode stable, so
 * this one aव्योमs such problems.
 */
काष्ठा dentry *lookup_positive_unlocked(स्थिर अक्षर *name,
				       काष्ठा dentry *base, पूर्णांक len)
अणु
	काष्ठा dentry *ret = lookup_one_len_unlocked(name, base, len);
	अगर (!IS_ERR(ret) && d_flags_negative(smp_load_acquire(&ret->d_flags))) अणु
		dput(ret);
		ret = ERR_PTR(-ENOENT);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(lookup_positive_unlocked);

#अगर_घोषित CONFIG_UNIX98_PTYS
पूर्णांक path_pts(काष्ठा path *path)
अणु
	/* Find something mounted on "pts" in the same directory as
	 * the input path.
	 */
	काष्ठा dentry *parent = dget_parent(path->dentry);
	काष्ठा dentry *child;
	काष्ठा qstr this = QSTR_INIT("pts", 3);

	अगर (unlikely(!path_connected(path->mnt, parent))) अणु
		dput(parent);
		वापस -ENOENT;
	पूर्ण
	dput(path->dentry);
	path->dentry = parent;
	child = d_hash_and_lookup(parent, &this);
	अगर (!child)
		वापस -ENOENT;

	path->dentry = child;
	dput(parent);
	follow_करोwn(path);
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक user_path_at_empty(पूर्णांक dfd, स्थिर अक्षर __user *name, अचिन्हित flags,
		 काष्ठा path *path, पूर्णांक *empty)
अणु
	वापस filename_lookup(dfd, getname_flags(name, flags, empty),
			       flags, path, शून्य);
पूर्ण
EXPORT_SYMBOL(user_path_at_empty);

पूर्णांक __check_sticky(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		   काष्ठा inode *inode)
अणु
	kuid_t fsuid = current_fsuid();

	अगर (uid_eq(i_uid_पूर्णांकo_mnt(mnt_userns, inode), fsuid))
		वापस 0;
	अगर (uid_eq(i_uid_पूर्णांकo_mnt(mnt_userns, dir), fsuid))
		वापस 0;
	वापस !capable_wrt_inode_uidgid(mnt_userns, inode, CAP_FOWNER);
पूर्ण
EXPORT_SYMBOL(__check_sticky);

/*
 *	Check whether we can हटाओ a link victim from directory dir, check
 *  whether the type of victim is right.
 *  1. We can't करो it अगर dir is पढ़ो-only (करोne in permission())
 *  2. We should have ग_लिखो and exec permissions on dir
 *  3. We can't हटाओ anything from append-only dir
 *  4. We can't करो anything with immutable dir (करोne in permission())
 *  5. If the sticky bit on dir is set we should either
 *	a. be owner of dir, or
 *	b. be owner of victim, or
 *	c. have CAP_FOWNER capability
 *  6. If the victim is append-only or immutable we can't करो antyhing with
 *     links poपूर्णांकing to it.
 *  7. If the victim has an unknown uid or gid we can't change the inode.
 *  8. If we were asked to हटाओ a directory and victim isn't one - ENOTसूची.
 *  9. If we were asked to हटाओ a non-directory and victim isn't one - EISसूची.
 * 10. We can't हटाओ a root or mountpoपूर्णांक.
 * 11. We करोn't allow removal of NFS sillyrenamed files; it's handled by
 *     nfs_async_unlink().
 */
अटल पूर्णांक may_delete(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *victim, bool isdir)
अणु
	काष्ठा inode *inode = d_backing_inode(victim);
	पूर्णांक error;

	अगर (d_is_negative(victim))
		वापस -ENOENT;
	BUG_ON(!inode);

	BUG_ON(victim->d_parent->d_inode != dir);

	/* Inode ग_लिखोback is not safe when the uid or gid are invalid. */
	अगर (!uid_valid(i_uid_पूर्णांकo_mnt(mnt_userns, inode)) ||
	    !gid_valid(i_gid_पूर्णांकo_mnt(mnt_userns, inode)))
		वापस -EOVERFLOW;

	audit_inode_child(dir, victim, AUDIT_TYPE_CHILD_DELETE);

	error = inode_permission(mnt_userns, dir, MAY_WRITE | MAY_EXEC);
	अगर (error)
		वापस error;
	अगर (IS_APPEND(dir))
		वापस -EPERM;

	अगर (check_sticky(mnt_userns, dir, inode) || IS_APPEND(inode) ||
	    IS_IMMUTABLE(inode) || IS_SWAPखाता(inode) ||
	    HAS_UNMAPPED_ID(mnt_userns, inode))
		वापस -EPERM;
	अगर (isdir) अणु
		अगर (!d_is_dir(victim))
			वापस -ENOTसूची;
		अगर (IS_ROOT(victim))
			वापस -EBUSY;
	पूर्ण अन्यथा अगर (d_is_dir(victim))
		वापस -EISसूची;
	अगर (IS_DEADसूची(dir))
		वापस -ENOENT;
	अगर (victim->d_flags & DCACHE_NFSFS_RENAMED)
		वापस -EBUSY;
	वापस 0;
पूर्ण

/*	Check whether we can create an object with dentry child in directory
 *  dir.
 *  1. We can't करो it अगर child alपढ़ोy exists (खोलो has special treaपंचांगent क्रम
 *     this हाल, but since we are अंतरभूतd it's OK)
 *  2. We can't करो it अगर dir is पढ़ो-only (करोne in permission())
 *  3. We can't do it if the fs can't represent the fsuid or fsgid.
 *  4. We should have ग_लिखो and exec permissions on dir
 *  5. We can't करो it अगर dir is immutable (करोne in permission())
 */
अटल अंतरभूत पूर्णांक may_create(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *dir, काष्ठा dentry *child)
अणु
	audit_inode_child(dir, child, AUDIT_TYPE_CHILD_CREATE);
	अगर (child->d_inode)
		वापस -EEXIST;
	अगर (IS_DEADसूची(dir))
		वापस -ENOENT;
	अगर (!fsuidgid_has_mapping(dir->i_sb, mnt_userns))
		वापस -EOVERFLOW;

	वापस inode_permission(mnt_userns, dir, MAY_WRITE | MAY_EXEC);
पूर्ण

/*
 * p1 and p2 should be directories on the same fs.
 */
काष्ठा dentry *lock_नाम(काष्ठा dentry *p1, काष्ठा dentry *p2)
अणु
	काष्ठा dentry *p;

	अगर (p1 == p2) अणु
		inode_lock_nested(p1->d_inode, I_MUTEX_PARENT);
		वापस शून्य;
	पूर्ण

	mutex_lock(&p1->d_sb->s_vfs_नाम_mutex);

	p = d_ancestor(p2, p1);
	अगर (p) अणु
		inode_lock_nested(p2->d_inode, I_MUTEX_PARENT);
		inode_lock_nested(p1->d_inode, I_MUTEX_CHILD);
		वापस p;
	पूर्ण

	p = d_ancestor(p1, p2);
	अगर (p) अणु
		inode_lock_nested(p1->d_inode, I_MUTEX_PARENT);
		inode_lock_nested(p2->d_inode, I_MUTEX_CHILD);
		वापस p;
	पूर्ण

	inode_lock_nested(p1->d_inode, I_MUTEX_PARENT);
	inode_lock_nested(p2->d_inode, I_MUTEX_PARENT2);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(lock_नाम);

व्योम unlock_नाम(काष्ठा dentry *p1, काष्ठा dentry *p2)
अणु
	inode_unlock(p1->d_inode);
	अगर (p1 != p2) अणु
		inode_unlock(p2->d_inode);
		mutex_unlock(&p1->d_sb->s_vfs_नाम_mutex);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(unlock_नाम);

/**
 * vfs_create - create new file
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dir:	inode of @dentry
 * @dentry:	poपूर्णांकer to dentry of the base directory
 * @mode:	mode of the new file
 * @want_excl:	whether the file must not yet exist
 *
 * Create a new file.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
पूर्णांक vfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	       काष्ठा dentry *dentry, umode_t mode, bool want_excl)
अणु
	पूर्णांक error = may_create(mnt_userns, dir, dentry);
	अगर (error)
		वापस error;

	अगर (!dir->i_op->create)
		वापस -EACCES;	/* shouldn't it be ENOSYS? */
	mode &= S_IALLUGO;
	mode |= S_IFREG;
	error = security_inode_create(dir, dentry, mode);
	अगर (error)
		वापस error;
	error = dir->i_op->create(mnt_userns, dir, dentry, mode, want_excl);
	अगर (!error)
		fsnotअगरy_create(dir, dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_create);

पूर्णांक vfs_mkobj(काष्ठा dentry *dentry, umode_t mode,
		पूर्णांक (*f)(काष्ठा dentry *, umode_t, व्योम *),
		व्योम *arg)
अणु
	काष्ठा inode *dir = dentry->d_parent->d_inode;
	पूर्णांक error = may_create(&init_user_ns, dir, dentry);
	अगर (error)
		वापस error;

	mode &= S_IALLUGO;
	mode |= S_IFREG;
	error = security_inode_create(dir, dentry, mode);
	अगर (error)
		वापस error;
	error = f(dentry, mode, arg);
	अगर (!error)
		fsnotअगरy_create(dir, dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_mkobj);

bool may_खोलो_dev(स्थिर काष्ठा path *path)
अणु
	वापस !(path->mnt->mnt_flags & MNT_NODEV) &&
		!(path->mnt->mnt_sb->s_अगरlags & SB_I_NODEV);
पूर्ण

अटल पूर्णांक may_खोलो(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		    पूर्णांक acc_mode, पूर्णांक flag)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा inode *inode = dentry->d_inode;
	पूर्णांक error;

	अगर (!inode)
		वापस -ENOENT;

	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFLNK:
		वापस -ELOOP;
	हाल S_IFसूची:
		अगर (acc_mode & MAY_WRITE)
			वापस -EISसूची;
		अगर (acc_mode & MAY_EXEC)
			वापस -EACCES;
		अवरोध;
	हाल S_IFBLK:
	हाल S_IFCHR:
		अगर (!may_खोलो_dev(path))
			वापस -EACCES;
		fallthrough;
	हाल S_IFIFO:
	हाल S_IFSOCK:
		अगर (acc_mode & MAY_EXEC)
			वापस -EACCES;
		flag &= ~O_TRUNC;
		अवरोध;
	हाल S_IFREG:
		अगर ((acc_mode & MAY_EXEC) && path_noexec(path))
			वापस -EACCES;
		अवरोध;
	पूर्ण

	error = inode_permission(mnt_userns, inode, MAY_OPEN | acc_mode);
	अगर (error)
		वापस error;

	/*
	 * An append-only file must be खोलोed in append mode क्रम writing.
	 */
	अगर (IS_APPEND(inode)) अणु
		अगर  ((flag & O_ACCMODE) != O_RDONLY && !(flag & O_APPEND))
			वापस -EPERM;
		अगर (flag & O_TRUNC)
			वापस -EPERM;
	पूर्ण

	/* O_NOATIME can only be set by the owner or superuser */
	अगर (flag & O_NOATIME && !inode_owner_or_capable(mnt_userns, inode))
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक handle_truncate(काष्ठा user_namespace *mnt_userns, काष्ठा file *filp)
अणु
	स्थिर काष्ठा path *path = &filp->f_path;
	काष्ठा inode *inode = path->dentry->d_inode;
	पूर्णांक error = get_ग_लिखो_access(inode);
	अगर (error)
		वापस error;
	/*
	 * Refuse to truncate files with mandatory locks held on them.
	 */
	error = locks_verअगरy_locked(filp);
	अगर (!error)
		error = security_path_truncate(path);
	अगर (!error) अणु
		error = करो_truncate(mnt_userns, path->dentry, 0,
				    ATTR_MTIME|ATTR_CTIME|ATTR_OPEN,
				    filp);
	पूर्ण
	put_ग_लिखो_access(inode);
	वापस error;
पूर्ण

अटल अंतरभूत पूर्णांक खोलो_to_namei_flags(पूर्णांक flag)
अणु
	अगर ((flag & O_ACCMODE) == 3)
		flag--;
	वापस flag;
पूर्ण

अटल पूर्णांक may_o_create(काष्ठा user_namespace *mnt_userns,
			स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
			umode_t mode)
अणु
	पूर्णांक error = security_path_mknod(dir, dentry, mode, 0);
	अगर (error)
		वापस error;

	अगर (!fsuidgid_has_mapping(dir->dentry->d_sb, mnt_userns))
		वापस -EOVERFLOW;

	error = inode_permission(mnt_userns, dir->dentry->d_inode,
				 MAY_WRITE | MAY_EXEC);
	अगर (error)
		वापस error;

	वापस security_inode_create(dir->dentry->d_inode, dentry, mode);
पूर्ण

/*
 * Attempt to atomically look up, create and खोलो a file from a negative
 * dentry.
 *
 * Returns 0 अगर successful.  The file will have been created and attached to
 * @file by the fileप्रणाली calling finish_खोलो().
 *
 * If the file was looked up only or didn't need creating, FMODE_OPENED won't
 * be set.  The caller will need to perक्रमm the खोलो themselves.  @path will
 * have been updated to poपूर्णांक to the new dentry.  This may be negative.
 *
 * Returns an error code otherwise.
 */
अटल काष्ठा dentry *atomic_खोलो(काष्ठा nameidata *nd, काष्ठा dentry *dentry,
				  काष्ठा file *file,
				  पूर्णांक खोलो_flag, umode_t mode)
अणु
	काष्ठा dentry *स्थिर DENTRY_NOT_SET = (व्योम *) -1UL;
	काष्ठा inode *dir =  nd->path.dentry->d_inode;
	पूर्णांक error;

	अगर (nd->flags & LOOKUP_सूचीECTORY)
		खोलो_flag |= O_सूचीECTORY;

	file->f_path.dentry = DENTRY_NOT_SET;
	file->f_path.mnt = nd->path.mnt;
	error = dir->i_op->atomic_खोलो(dir, dentry, file,
				       खोलो_to_namei_flags(खोलो_flag), mode);
	d_lookup_करोne(dentry);
	अगर (!error) अणु
		अगर (file->f_mode & FMODE_OPENED) अणु
			अगर (unlikely(dentry != file->f_path.dentry)) अणु
				dput(dentry);
				dentry = dget(file->f_path.dentry);
			पूर्ण
		पूर्ण अन्यथा अगर (WARN_ON(file->f_path.dentry == DENTRY_NOT_SET)) अणु
			error = -EIO;
		पूर्ण अन्यथा अणु
			अगर (file->f_path.dentry) अणु
				dput(dentry);
				dentry = file->f_path.dentry;
			पूर्ण
			अगर (unlikely(d_is_negative(dentry)))
				error = -ENOENT;
		पूर्ण
	पूर्ण
	अगर (error) अणु
		dput(dentry);
		dentry = ERR_PTR(error);
	पूर्ण
	वापस dentry;
पूर्ण

/*
 * Look up and maybe create and खोलो the last component.
 *
 * Must be called with parent locked (exclusive in O_CREAT हाल).
 *
 * Returns 0 on success, that is, अगर
 *  the file was successfully atomically created (अगर necessary) and खोलोed, or
 *  the file was not completely खोलोed at this समय, though lookups and
 *  creations were perक्रमmed.
 * These हाल are distinguished by presence of FMODE_OPENED on file->f_mode.
 * In the latter हाल dentry वापसed in @path might be negative अगर O_CREAT
 * hadn't been specअगरied.
 *
 * An error code is वापसed on failure.
 */
अटल काष्ठा dentry *lookup_खोलो(काष्ठा nameidata *nd, काष्ठा file *file,
				  स्थिर काष्ठा खोलो_flags *op,
				  bool got_ग_लिखो)
अणु
	काष्ठा user_namespace *mnt_userns;
	काष्ठा dentry *dir = nd->path.dentry;
	काष्ठा inode *dir_inode = dir->d_inode;
	पूर्णांक खोलो_flag = op->खोलो_flag;
	काष्ठा dentry *dentry;
	पूर्णांक error, create_error = 0;
	umode_t mode = op->mode;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	अगर (unlikely(IS_DEADसूची(dir_inode)))
		वापस ERR_PTR(-ENOENT);

	file->f_mode &= ~FMODE_CREATED;
	dentry = d_lookup(dir, &nd->last);
	क्रम (;;) अणु
		अगर (!dentry) अणु
			dentry = d_alloc_parallel(dir, &nd->last, &wq);
			अगर (IS_ERR(dentry))
				वापस dentry;
		पूर्ण
		अगर (d_in_lookup(dentry))
			अवरोध;

		error = d_revalidate(dentry, nd->flags);
		अगर (likely(error > 0))
			अवरोध;
		अगर (error)
			जाओ out_dput;
		d_invalidate(dentry);
		dput(dentry);
		dentry = शून्य;
	पूर्ण
	अगर (dentry->d_inode) अणु
		/* Cached positive dentry: will खोलो in f_op->खोलो */
		वापस dentry;
	पूर्ण

	/*
	 * Checking ग_लिखो permission is tricky, bacuse we करोn't know अगर we are
	 * going to actually need it: O_CREAT खोलोs should work as दीर्घ as the
	 * file exists.  But checking existence अवरोधs atomicity.  The trick is
	 * to check access and अगर not granted clear O_CREAT from the flags.
	 *
	 * Another problem is returing the "right" error value (e.g. क्रम an
	 * O_EXCL खोलो we want to वापस EEXIST not EROFS).
	 */
	अगर (unlikely(!got_ग_लिखो))
		खोलो_flag &= ~O_TRUNC;
	mnt_userns = mnt_user_ns(nd->path.mnt);
	अगर (खोलो_flag & O_CREAT) अणु
		अगर (खोलो_flag & O_EXCL)
			खोलो_flag &= ~O_TRUNC;
		अगर (!IS_POSIXACL(dir->d_inode))
			mode &= ~current_umask();
		अगर (likely(got_ग_लिखो))
			create_error = may_o_create(mnt_userns, &nd->path,
						    dentry, mode);
		अन्यथा
			create_error = -EROFS;
	पूर्ण
	अगर (create_error)
		खोलो_flag &= ~O_CREAT;
	अगर (dir_inode->i_op->atomic_खोलो) अणु
		dentry = atomic_खोलो(nd, dentry, file, खोलो_flag, mode);
		अगर (unlikely(create_error) && dentry == ERR_PTR(-ENOENT))
			dentry = ERR_PTR(create_error);
		वापस dentry;
	पूर्ण

	अगर (d_in_lookup(dentry)) अणु
		काष्ठा dentry *res = dir_inode->i_op->lookup(dir_inode, dentry,
							     nd->flags);
		d_lookup_करोne(dentry);
		अगर (unlikely(res)) अणु
			अगर (IS_ERR(res)) अणु
				error = PTR_ERR(res);
				जाओ out_dput;
			पूर्ण
			dput(dentry);
			dentry = res;
		पूर्ण
	पूर्ण

	/* Negative dentry, just create the file */
	अगर (!dentry->d_inode && (खोलो_flag & O_CREAT)) अणु
		file->f_mode |= FMODE_CREATED;
		audit_inode_child(dir_inode, dentry, AUDIT_TYPE_CHILD_CREATE);
		अगर (!dir_inode->i_op->create) अणु
			error = -EACCES;
			जाओ out_dput;
		पूर्ण

		error = dir_inode->i_op->create(mnt_userns, dir_inode, dentry,
						mode, खोलो_flag & O_EXCL);
		अगर (error)
			जाओ out_dput;
	पूर्ण
	अगर (unlikely(create_error) && !dentry->d_inode) अणु
		error = create_error;
		जाओ out_dput;
	पूर्ण
	वापस dentry;

out_dput:
	dput(dentry);
	वापस ERR_PTR(error);
पूर्ण

अटल स्थिर अक्षर *खोलो_last_lookups(काष्ठा nameidata *nd,
		   काष्ठा file *file, स्थिर काष्ठा खोलो_flags *op)
अणु
	काष्ठा dentry *dir = nd->path.dentry;
	पूर्णांक खोलो_flag = op->खोलो_flag;
	bool got_ग_लिखो = false;
	अचिन्हित seq;
	काष्ठा inode *inode;
	काष्ठा dentry *dentry;
	स्थिर अक्षर *res;

	nd->flags |= op->पूर्णांकent;

	अगर (nd->last_type != LAST_NORM) अणु
		अगर (nd->depth)
			put_link(nd);
		वापस handle_करोts(nd, nd->last_type);
	पूर्ण

	अगर (!(खोलो_flag & O_CREAT)) अणु
		अगर (nd->last.name[nd->last.len])
			nd->flags |= LOOKUP_FOLLOW | LOOKUP_सूचीECTORY;
		/* we _can_ be in RCU mode here */
		dentry = lookup_fast(nd, &inode, &seq);
		अगर (IS_ERR(dentry))
			वापस ERR_CAST(dentry);
		अगर (likely(dentry))
			जाओ finish_lookup;

		BUG_ON(nd->flags & LOOKUP_RCU);
	पूर्ण अन्यथा अणु
		/* create side of things */
		अगर (nd->flags & LOOKUP_RCU) अणु
			अगर (!try_to_unlazy(nd))
				वापस ERR_PTR(-ECHILD);
		पूर्ण
		audit_inode(nd->name, dir, AUDIT_INODE_PARENT);
		/* trailing slashes? */
		अगर (unlikely(nd->last.name[nd->last.len]))
			वापस ERR_PTR(-EISसूची);
	पूर्ण

	अगर (खोलो_flag & (O_CREAT | O_TRUNC | O_WRONLY | O_RDWR)) अणु
		got_ग_लिखो = !mnt_want_ग_लिखो(nd->path.mnt);
		/*
		 * करो _not_ fail yet - we might not need that or fail with
		 * a dअगरferent error; let lookup_खोलो() decide; we'll be
		 * dropping this one anyway.
		 */
	पूर्ण
	अगर (खोलो_flag & O_CREAT)
		inode_lock(dir->d_inode);
	अन्यथा
		inode_lock_shared(dir->d_inode);
	dentry = lookup_खोलो(nd, file, op, got_ग_लिखो);
	अगर (!IS_ERR(dentry) && (file->f_mode & FMODE_CREATED))
		fsnotअगरy_create(dir->d_inode, dentry);
	अगर (खोलो_flag & O_CREAT)
		inode_unlock(dir->d_inode);
	अन्यथा
		inode_unlock_shared(dir->d_inode);

	अगर (got_ग_लिखो)
		mnt_drop_ग_लिखो(nd->path.mnt);

	अगर (IS_ERR(dentry))
		वापस ERR_CAST(dentry);

	अगर (file->f_mode & (FMODE_OPENED | FMODE_CREATED)) अणु
		dput(nd->path.dentry);
		nd->path.dentry = dentry;
		वापस शून्य;
	पूर्ण

finish_lookup:
	अगर (nd->depth)
		put_link(nd);
	res = step_पूर्णांकo(nd, WALK_TRAILING, dentry, inode, seq);
	अगर (unlikely(res))
		nd->flags &= ~(LOOKUP_OPEN|LOOKUP_CREATE|LOOKUP_EXCL);
	वापस res;
पूर्ण

/*
 * Handle the last step of खोलो()
 */
अटल पूर्णांक करो_खोलो(काष्ठा nameidata *nd,
		   काष्ठा file *file, स्थिर काष्ठा खोलो_flags *op)
अणु
	काष्ठा user_namespace *mnt_userns;
	पूर्णांक खोलो_flag = op->खोलो_flag;
	bool करो_truncate;
	पूर्णांक acc_mode;
	पूर्णांक error;

	अगर (!(file->f_mode & (FMODE_OPENED | FMODE_CREATED))) अणु
		error = complete_walk(nd);
		अगर (error)
			वापस error;
	पूर्ण
	अगर (!(file->f_mode & FMODE_CREATED))
		audit_inode(nd->name, nd->path.dentry, 0);
	mnt_userns = mnt_user_ns(nd->path.mnt);
	अगर (खोलो_flag & O_CREAT) अणु
		अगर ((खोलो_flag & O_EXCL) && !(file->f_mode & FMODE_CREATED))
			वापस -EEXIST;
		अगर (d_is_dir(nd->path.dentry))
			वापस -EISसूची;
		error = may_create_in_sticky(mnt_userns, nd,
					     d_backing_inode(nd->path.dentry));
		अगर (unlikely(error))
			वापस error;
	पूर्ण
	अगर ((nd->flags & LOOKUP_सूचीECTORY) && !d_can_lookup(nd->path.dentry))
		वापस -ENOTसूची;

	करो_truncate = false;
	acc_mode = op->acc_mode;
	अगर (file->f_mode & FMODE_CREATED) अणु
		/* Don't check for write permission, don't truncate */
		खोलो_flag &= ~O_TRUNC;
		acc_mode = 0;
	पूर्ण अन्यथा अगर (d_is_reg(nd->path.dentry) && खोलो_flag & O_TRUNC) अणु
		error = mnt_want_ग_लिखो(nd->path.mnt);
		अगर (error)
			वापस error;
		करो_truncate = true;
	पूर्ण
	error = may_खोलो(mnt_userns, &nd->path, acc_mode, खोलो_flag);
	अगर (!error && !(file->f_mode & FMODE_OPENED))
		error = vfs_खोलो(&nd->path, file);
	अगर (!error)
		error = ima_file_check(file, op->acc_mode);
	अगर (!error && करो_truncate)
		error = handle_truncate(mnt_userns, file);
	अगर (unlikely(error > 0)) अणु
		WARN_ON(1);
		error = -EINVAL;
	पूर्ण
	अगर (करो_truncate)
		mnt_drop_ग_लिखो(nd->path.mnt);
	वापस error;
पूर्ण

/**
 * vfs_क्षणिक_ख - create क्षणिक_ख
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dentry:	poपूर्णांकer to dentry of the base directory
 * @mode:	mode of the new क्षणिक_ख
 * @खोलो_flag:	flags
 *
 * Create a temporary file.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
काष्ठा dentry *vfs_क्षणिक_ख(काष्ठा user_namespace *mnt_userns,
			   काष्ठा dentry *dentry, umode_t mode, पूर्णांक खोलो_flag)
अणु
	काष्ठा dentry *child = शून्य;
	काष्ठा inode *dir = dentry->d_inode;
	काष्ठा inode *inode;
	पूर्णांक error;

	/* we want directory to be writable */
	error = inode_permission(mnt_userns, dir, MAY_WRITE | MAY_EXEC);
	अगर (error)
		जाओ out_err;
	error = -EOPNOTSUPP;
	अगर (!dir->i_op->क्षणिक_ख)
		जाओ out_err;
	error = -ENOMEM;
	child = d_alloc(dentry, &slash_name);
	अगर (unlikely(!child))
		जाओ out_err;
	error = dir->i_op->क्षणिक_ख(mnt_userns, dir, child, mode);
	अगर (error)
		जाओ out_err;
	error = -ENOENT;
	inode = child->d_inode;
	अगर (unlikely(!inode))
		जाओ out_err;
	अगर (!(खोलो_flag & O_EXCL)) अणु
		spin_lock(&inode->i_lock);
		inode->i_state |= I_LINKABLE;
		spin_unlock(&inode->i_lock);
	पूर्ण
	ima_post_create_क्षणिक_ख(mnt_userns, inode);
	वापस child;

out_err:
	dput(child);
	वापस ERR_PTR(error);
पूर्ण
EXPORT_SYMBOL(vfs_क्षणिक_ख);

अटल पूर्णांक करो_क्षणिक_ख(काष्ठा nameidata *nd, अचिन्हित flags,
		स्थिर काष्ठा खोलो_flags *op,
		काष्ठा file *file)
अणु
	काष्ठा user_namespace *mnt_userns;
	काष्ठा dentry *child;
	काष्ठा path path;
	पूर्णांक error = path_lookupat(nd, flags | LOOKUP_सूचीECTORY, &path);
	अगर (unlikely(error))
		वापस error;
	error = mnt_want_ग_लिखो(path.mnt);
	अगर (unlikely(error))
		जाओ out;
	mnt_userns = mnt_user_ns(path.mnt);
	child = vfs_क्षणिक_ख(mnt_userns, path.dentry, op->mode, op->खोलो_flag);
	error = PTR_ERR(child);
	अगर (IS_ERR(child))
		जाओ out2;
	dput(path.dentry);
	path.dentry = child;
	audit_inode(nd->name, child, 0);
	/* Don't check क्रम other permissions, the inode was just created */
	error = may_खोलो(mnt_userns, &path, 0, op->खोलो_flag);
	अगर (!error)
		error = vfs_खोलो(&path, file);
out2:
	mnt_drop_ग_लिखो(path.mnt);
out:
	path_put(&path);
	वापस error;
पूर्ण

अटल पूर्णांक करो_o_path(काष्ठा nameidata *nd, अचिन्हित flags, काष्ठा file *file)
अणु
	काष्ठा path path;
	पूर्णांक error = path_lookupat(nd, flags, &path);
	अगर (!error) अणु
		audit_inode(nd->name, path.dentry, 0);
		error = vfs_खोलो(&path, file);
		path_put(&path);
	पूर्ण
	वापस error;
पूर्ण

अटल काष्ठा file *path_खोलोat(काष्ठा nameidata *nd,
			स्थिर काष्ठा खोलो_flags *op, अचिन्हित flags)
अणु
	काष्ठा file *file;
	पूर्णांक error;

	file = alloc_empty_file(op->खोलो_flag, current_cred());
	अगर (IS_ERR(file))
		वापस file;

	अगर (unlikely(file->f_flags & __O_TMPखाता)) अणु
		error = करो_क्षणिक_ख(nd, flags, op, file);
	पूर्ण अन्यथा अगर (unlikely(file->f_flags & O_PATH)) अणु
		error = करो_o_path(nd, flags, file);
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *s = path_init(nd, flags);
		जबतक (!(error = link_path_walk(s, nd)) &&
		       (s = खोलो_last_lookups(nd, file, op)) != शून्य)
			;
		अगर (!error)
			error = करो_खोलो(nd, file, op);
		terminate_walk(nd);
	पूर्ण
	अगर (likely(!error)) अणु
		अगर (likely(file->f_mode & FMODE_OPENED))
			वापस file;
		WARN_ON(1);
		error = -EINVAL;
	पूर्ण
	fput(file);
	अगर (error == -EOPENSTALE) अणु
		अगर (flags & LOOKUP_RCU)
			error = -ECHILD;
		अन्यथा
			error = -ESTALE;
	पूर्ण
	वापस ERR_PTR(error);
पूर्ण

काष्ठा file *करो_filp_खोलो(पूर्णांक dfd, काष्ठा filename *pathname,
		स्थिर काष्ठा खोलो_flags *op)
अणु
	काष्ठा nameidata nd;
	पूर्णांक flags = op->lookup_flags;
	काष्ठा file *filp;

	set_nameidata(&nd, dfd, pathname);
	filp = path_खोलोat(&nd, op, flags | LOOKUP_RCU);
	अगर (unlikely(filp == ERR_PTR(-ECHILD)))
		filp = path_खोलोat(&nd, op, flags);
	अगर (unlikely(filp == ERR_PTR(-ESTALE)))
		filp = path_खोलोat(&nd, op, flags | LOOKUP_REVAL);
	restore_nameidata();
	वापस filp;
पूर्ण

काष्ठा file *करो_file_खोलो_root(काष्ठा dentry *dentry, काष्ठा vfsmount *mnt,
		स्थिर अक्षर *name, स्थिर काष्ठा खोलो_flags *op)
अणु
	काष्ठा nameidata nd;
	काष्ठा file *file;
	काष्ठा filename *filename;
	पूर्णांक flags = op->lookup_flags | LOOKUP_ROOT;

	nd.root.mnt = mnt;
	nd.root.dentry = dentry;

	अगर (d_is_symlink(dentry) && op->पूर्णांकent & LOOKUP_OPEN)
		वापस ERR_PTR(-ELOOP);

	filename = getname_kernel(name);
	अगर (IS_ERR(filename))
		वापस ERR_CAST(filename);

	set_nameidata(&nd, -1, filename);
	file = path_खोलोat(&nd, op, flags | LOOKUP_RCU);
	अगर (unlikely(file == ERR_PTR(-ECHILD)))
		file = path_खोलोat(&nd, op, flags);
	अगर (unlikely(file == ERR_PTR(-ESTALE)))
		file = path_खोलोat(&nd, op, flags | LOOKUP_REVAL);
	restore_nameidata();
	putname(filename);
	वापस file;
पूर्ण

अटल काष्ठा dentry *filename_create(पूर्णांक dfd, काष्ठा filename *name,
				काष्ठा path *path, अचिन्हित पूर्णांक lookup_flags)
अणु
	काष्ठा dentry *dentry = ERR_PTR(-EEXIST);
	काष्ठा qstr last;
	पूर्णांक type;
	पूर्णांक err2;
	पूर्णांक error;
	bool is_dir = (lookup_flags & LOOKUP_सूचीECTORY);

	/*
	 * Note that only LOOKUP_REVAL and LOOKUP_सूचीECTORY matter here. Any
	 * other flags passed in are ignored!
	 */
	lookup_flags &= LOOKUP_REVAL;

	name = filename_parentat(dfd, name, lookup_flags, path, &last, &type);
	अगर (IS_ERR(name))
		वापस ERR_CAST(name);

	/*
	 * Yucky last component or no last component at all?
	 * (foo/., foo/.., /////)
	 */
	अगर (unlikely(type != LAST_NORM))
		जाओ out;

	/* करोn't fail immediately if it's r/o, at least try to report other errors */
	err2 = mnt_want_ग_लिखो(path->mnt);
	/*
	 * Do the final lookup.
	 */
	lookup_flags |= LOOKUP_CREATE | LOOKUP_EXCL;
	inode_lock_nested(path->dentry->d_inode, I_MUTEX_PARENT);
	dentry = __lookup_hash(&last, path->dentry, lookup_flags);
	अगर (IS_ERR(dentry))
		जाओ unlock;

	error = -EEXIST;
	अगर (d_is_positive(dentry))
		जाओ fail;

	/*
	 * Special हाल - lookup gave negative, but... we had foo/bar/
	 * From the vfs_mknod() POV we just have a negative dentry -
	 * all is fine. Let's be bastards - you had / on the end, you've
	 * been asking क्रम (non-existent) directory. -ENOENT क्रम you.
	 */
	अगर (unlikely(!is_dir && last.name[last.len])) अणु
		error = -ENOENT;
		जाओ fail;
	पूर्ण
	अगर (unlikely(err2)) अणु
		error = err2;
		जाओ fail;
	पूर्ण
	putname(name);
	वापस dentry;
fail:
	dput(dentry);
	dentry = ERR_PTR(error);
unlock:
	inode_unlock(path->dentry->d_inode);
	अगर (!err2)
		mnt_drop_ग_लिखो(path->mnt);
out:
	path_put(path);
	putname(name);
	वापस dentry;
पूर्ण

काष्ठा dentry *kern_path_create(पूर्णांक dfd, स्थिर अक्षर *pathname,
				काष्ठा path *path, अचिन्हित पूर्णांक lookup_flags)
अणु
	वापस filename_create(dfd, getname_kernel(pathname),
				path, lookup_flags);
पूर्ण
EXPORT_SYMBOL(kern_path_create);

व्योम करोne_path_create(काष्ठा path *path, काष्ठा dentry *dentry)
अणु
	dput(dentry);
	inode_unlock(path->dentry->d_inode);
	mnt_drop_ग_लिखो(path->mnt);
	path_put(path);
पूर्ण
EXPORT_SYMBOL(करोne_path_create);

अंतरभूत काष्ठा dentry *user_path_create(पूर्णांक dfd, स्थिर अक्षर __user *pathname,
				काष्ठा path *path, अचिन्हित पूर्णांक lookup_flags)
अणु
	वापस filename_create(dfd, getname(pathname), path, lookup_flags);
पूर्ण
EXPORT_SYMBOL(user_path_create);

/**
 * vfs_mknod - create device node or file
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dir:	inode of @dentry
 * @dentry:	poपूर्णांकer to dentry of the base directory
 * @mode:	mode of the new device node or file
 * @dev:	device number of device to create
 *
 * Create a device node or file.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
पूर्णांक vfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	      काष्ठा dentry *dentry, umode_t mode, dev_t dev)
अणु
	bool is_whiteout = S_ISCHR(mode) && dev == WHITEOUT_DEV;
	पूर्णांक error = may_create(mnt_userns, dir, dentry);

	अगर (error)
		वापस error;

	अगर ((S_ISCHR(mode) || S_ISBLK(mode)) && !is_whiteout &&
	    !capable(CAP_MKNOD))
		वापस -EPERM;

	अगर (!dir->i_op->mknod)
		वापस -EPERM;

	error = devcgroup_inode_mknod(mode, dev);
	अगर (error)
		वापस error;

	error = security_inode_mknod(dir, dentry, mode, dev);
	अगर (error)
		वापस error;

	error = dir->i_op->mknod(mnt_userns, dir, dentry, mode, dev);
	अगर (!error)
		fsnotअगरy_create(dir, dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_mknod);

अटल पूर्णांक may_mknod(umode_t mode)
अणु
	चयन (mode & S_IFMT) अणु
	हाल S_IFREG:
	हाल S_IFCHR:
	हाल S_IFBLK:
	हाल S_IFIFO:
	हाल S_IFSOCK:
	हाल 0: /* zero mode translates to S_IFREG */
		वापस 0;
	हाल S_IFसूची:
		वापस -EPERM;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल दीर्घ करो_mknodat(पूर्णांक dfd, स्थिर अक्षर __user *filename, umode_t mode,
		अचिन्हित पूर्णांक dev)
अणु
	काष्ठा user_namespace *mnt_userns;
	काष्ठा dentry *dentry;
	काष्ठा path path;
	पूर्णांक error;
	अचिन्हित पूर्णांक lookup_flags = 0;

	error = may_mknod(mode);
	अगर (error)
		वापस error;
retry:
	dentry = user_path_create(dfd, filename, &path, lookup_flags);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	अगर (!IS_POSIXACL(path.dentry->d_inode))
		mode &= ~current_umask();
	error = security_path_mknod(&path, dentry, mode, dev);
	अगर (error)
		जाओ out;

	mnt_userns = mnt_user_ns(path.mnt);
	चयन (mode & S_IFMT) अणु
		हाल 0: हाल S_IFREG:
			error = vfs_create(mnt_userns, path.dentry->d_inode,
					   dentry, mode, true);
			अगर (!error)
				ima_post_path_mknod(mnt_userns, dentry);
			अवरोध;
		हाल S_IFCHR: हाल S_IFBLK:
			error = vfs_mknod(mnt_userns, path.dentry->d_inode,
					  dentry, mode, new_decode_dev(dev));
			अवरोध;
		हाल S_IFIFO: हाल S_IFSOCK:
			error = vfs_mknod(mnt_userns, path.dentry->d_inode,
					  dentry, mode, 0);
			अवरोध;
	पूर्ण
out:
	करोne_path_create(&path, dentry);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE4(mknodat, पूर्णांक, dfd, स्थिर अक्षर __user *, filename, umode_t, mode,
		अचिन्हित पूर्णांक, dev)
अणु
	वापस करो_mknodat(dfd, filename, mode, dev);
पूर्ण

SYSCALL_DEFINE3(mknod, स्थिर अक्षर __user *, filename, umode_t, mode, अचिन्हित, dev)
अणु
	वापस करो_mknodat(AT_FDCWD, filename, mode, dev);
पूर्ण

/**
 * vfs_सूची_गढ़ो - create directory
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dir:	inode of @dentry
 * @dentry:	poपूर्णांकer to dentry of the base directory
 * @mode:	mode of the new directory
 *
 * Create a directory.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
पूर्णांक vfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	      काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक error = may_create(mnt_userns, dir, dentry);
	अचिन्हित max_links = dir->i_sb->s_max_links;

	अगर (error)
		वापस error;

	अगर (!dir->i_op->सूची_गढ़ो)
		वापस -EPERM;

	mode &= (S_IRWXUGO|S_ISVTX);
	error = security_inode_सूची_गढ़ो(dir, dentry, mode);
	अगर (error)
		वापस error;

	अगर (max_links && dir->i_nlink >= max_links)
		वापस -EMLINK;

	error = dir->i_op->सूची_गढ़ो(mnt_userns, dir, dentry, mode);
	अगर (!error)
		fsnotअगरy_सूची_गढ़ो(dir, dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_सूची_गढ़ो);

अटल दीर्घ करो_सूची_गढ़ोat(पूर्णांक dfd, स्थिर अक्षर __user *pathname, umode_t mode)
अणु
	काष्ठा dentry *dentry;
	काष्ठा path path;
	पूर्णांक error;
	अचिन्हित पूर्णांक lookup_flags = LOOKUP_सूचीECTORY;

retry:
	dentry = user_path_create(dfd, pathname, &path, lookup_flags);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	अगर (!IS_POSIXACL(path.dentry->d_inode))
		mode &= ~current_umask();
	error = security_path_सूची_गढ़ो(&path, dentry, mode);
	अगर (!error) अणु
		काष्ठा user_namespace *mnt_userns;
		mnt_userns = mnt_user_ns(path.mnt);
		error = vfs_सूची_गढ़ो(mnt_userns, path.dentry->d_inode, dentry,
				  mode);
	पूर्ण
	करोne_path_create(&path, dentry);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE3(सूची_गढ़ोat, पूर्णांक, dfd, स्थिर अक्षर __user *, pathname, umode_t, mode)
अणु
	वापस करो_सूची_गढ़ोat(dfd, pathname, mode);
पूर्ण

SYSCALL_DEFINE2(सूची_गढ़ो, स्थिर अक्षर __user *, pathname, umode_t, mode)
अणु
	वापस करो_सूची_गढ़ोat(AT_FDCWD, pathname, mode);
पूर्ण

/**
 * vfs_सूची_हटाओ - हटाओ directory
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dir:	inode of @dentry
 * @dentry:	poपूर्णांकer to dentry of the base directory
 *
 * Remove a directory.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
पूर्णांक vfs_सूची_हटाओ(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry)
अणु
	पूर्णांक error = may_delete(mnt_userns, dir, dentry, 1);

	अगर (error)
		वापस error;

	अगर (!dir->i_op->सूची_हटाओ)
		वापस -EPERM;

	dget(dentry);
	inode_lock(dentry->d_inode);

	error = -EBUSY;
	अगर (is_local_mountpoपूर्णांक(dentry))
		जाओ out;

	error = security_inode_सूची_हटाओ(dir, dentry);
	अगर (error)
		जाओ out;

	error = dir->i_op->सूची_हटाओ(dir, dentry);
	अगर (error)
		जाओ out;

	shrink_dcache_parent(dentry);
	dentry->d_inode->i_flags |= S_DEAD;
	करोnt_mount(dentry);
	detach_mounts(dentry);
	fsnotअगरy_सूची_हटाओ(dir, dentry);

out:
	inode_unlock(dentry->d_inode);
	dput(dentry);
	अगर (!error)
		d_delete(dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_सूची_हटाओ);

दीर्घ करो_सूची_हटाओ(पूर्णांक dfd, काष्ठा filename *name)
अणु
	काष्ठा user_namespace *mnt_userns;
	पूर्णांक error = 0;
	काष्ठा dentry *dentry;
	काष्ठा path path;
	काष्ठा qstr last;
	पूर्णांक type;
	अचिन्हित पूर्णांक lookup_flags = 0;
retry:
	name = filename_parentat(dfd, name, lookup_flags,
				&path, &last, &type);
	अगर (IS_ERR(name))
		वापस PTR_ERR(name);

	चयन (type) अणु
	हाल LAST_DOTDOT:
		error = -ENOTEMPTY;
		जाओ निकास1;
	हाल LAST_DOT:
		error = -EINVAL;
		जाओ निकास1;
	हाल LAST_ROOT:
		error = -EBUSY;
		जाओ निकास1;
	पूर्ण

	error = mnt_want_ग_लिखो(path.mnt);
	अगर (error)
		जाओ निकास1;

	inode_lock_nested(path.dentry->d_inode, I_MUTEX_PARENT);
	dentry = __lookup_hash(&last, path.dentry, lookup_flags);
	error = PTR_ERR(dentry);
	अगर (IS_ERR(dentry))
		जाओ निकास2;
	अगर (!dentry->d_inode) अणु
		error = -ENOENT;
		जाओ निकास3;
	पूर्ण
	error = security_path_सूची_हटाओ(&path, dentry);
	अगर (error)
		जाओ निकास3;
	mnt_userns = mnt_user_ns(path.mnt);
	error = vfs_सूची_हटाओ(mnt_userns, path.dentry->d_inode, dentry);
निकास3:
	dput(dentry);
निकास2:
	inode_unlock(path.dentry->d_inode);
	mnt_drop_ग_लिखो(path.mnt);
निकास1:
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
	putname(name);
	वापस error;
पूर्ण

SYSCALL_DEFINE1(सूची_हटाओ, स्थिर अक्षर __user *, pathname)
अणु
	वापस करो_सूची_हटाओ(AT_FDCWD, getname(pathname));
पूर्ण

/**
 * vfs_unlink - unlink a fileप्रणाली object
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dir:	parent directory
 * @dentry:	victim
 * @delegated_inode: वापसs victim inode, अगर the inode is delegated.
 *
 * The caller must hold dir->i_mutex.
 *
 * If vfs_unlink discovers a delegation, it will वापस -EWOULDBLOCK and
 * वापस a reference to the inode in delegated_inode.  The caller
 * should then अवरोध the delegation on that inode and retry.  Because
 * अवरोधing a delegation may take a दीर्घ समय, the caller should drop
 * dir->i_mutex beक्रमe करोing so.
 *
 * Alternatively, a caller may pass शून्य क्रम delegated_inode.  This may
 * be appropriate क्रम callers that expect the underlying fileप्रणाली not
 * to be NFS exported.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
पूर्णांक vfs_unlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	       काष्ठा dentry *dentry, काष्ठा inode **delegated_inode)
अणु
	काष्ठा inode *target = dentry->d_inode;
	पूर्णांक error = may_delete(mnt_userns, dir, dentry, 0);

	अगर (error)
		वापस error;

	अगर (!dir->i_op->unlink)
		वापस -EPERM;

	inode_lock(target);
	अगर (is_local_mountpoपूर्णांक(dentry))
		error = -EBUSY;
	अन्यथा अणु
		error = security_inode_unlink(dir, dentry);
		अगर (!error) अणु
			error = try_अवरोध_deleg(target, delegated_inode);
			अगर (error)
				जाओ out;
			error = dir->i_op->unlink(dir, dentry);
			अगर (!error) अणु
				करोnt_mount(dentry);
				detach_mounts(dentry);
				fsnotअगरy_unlink(dir, dentry);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	inode_unlock(target);

	/* We करोn't d_delete() NFS sillyनामd files--they still exist. */
	अगर (!error && !(dentry->d_flags & DCACHE_NFSFS_RENAMED)) अणु
		fsnotअगरy_link_count(target);
		d_delete(dentry);
	पूर्ण

	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_unlink);

/*
 * Make sure that the actual truncation of the file will occur outside its
 * directory's i_mutex.  Truncate can take a दीर्घ समय अगर there is a lot of
 * ग_लिखोout happening, and we करोn't want to prevent access to the directory
 * जबतक रुकोing on the I/O.
 */
दीर्घ करो_unlinkat(पूर्णांक dfd, काष्ठा filename *name)
अणु
	पूर्णांक error;
	काष्ठा dentry *dentry;
	काष्ठा path path;
	काष्ठा qstr last;
	पूर्णांक type;
	काष्ठा inode *inode = शून्य;
	काष्ठा inode *delegated_inode = शून्य;
	अचिन्हित पूर्णांक lookup_flags = 0;
retry:
	name = filename_parentat(dfd, name, lookup_flags, &path, &last, &type);
	अगर (IS_ERR(name))
		वापस PTR_ERR(name);

	error = -EISसूची;
	अगर (type != LAST_NORM)
		जाओ निकास1;

	error = mnt_want_ग_लिखो(path.mnt);
	अगर (error)
		जाओ निकास1;
retry_deleg:
	inode_lock_nested(path.dentry->d_inode, I_MUTEX_PARENT);
	dentry = __lookup_hash(&last, path.dentry, lookup_flags);
	error = PTR_ERR(dentry);
	अगर (!IS_ERR(dentry)) अणु
		काष्ठा user_namespace *mnt_userns;

		/* Why not beक्रमe? Because we want correct error value */
		अगर (last.name[last.len])
			जाओ slashes;
		inode = dentry->d_inode;
		अगर (d_is_negative(dentry))
			जाओ slashes;
		ihold(inode);
		error = security_path_unlink(&path, dentry);
		अगर (error)
			जाओ निकास2;
		mnt_userns = mnt_user_ns(path.mnt);
		error = vfs_unlink(mnt_userns, path.dentry->d_inode, dentry,
				   &delegated_inode);
निकास2:
		dput(dentry);
	पूर्ण
	inode_unlock(path.dentry->d_inode);
	अगर (inode)
		iput(inode);	/* truncate the inode here */
	inode = शून्य;
	अगर (delegated_inode) अणु
		error = अवरोध_deleg_रुको(&delegated_inode);
		अगर (!error)
			जाओ retry_deleg;
	पूर्ण
	mnt_drop_ग_लिखो(path.mnt);
निकास1:
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		inode = शून्य;
		जाओ retry;
	पूर्ण
	putname(name);
	वापस error;

slashes:
	अगर (d_is_negative(dentry))
		error = -ENOENT;
	अन्यथा अगर (d_is_dir(dentry))
		error = -EISसूची;
	अन्यथा
		error = -ENOTसूची;
	जाओ निकास2;
पूर्ण

SYSCALL_DEFINE3(unlinkat, पूर्णांक, dfd, स्थिर अक्षर __user *, pathname, पूर्णांक, flag)
अणु
	अगर ((flag & ~AT_REMOVEसूची) != 0)
		वापस -EINVAL;

	अगर (flag & AT_REMOVEसूची)
		वापस करो_सूची_हटाओ(dfd, getname(pathname));
	वापस करो_unlinkat(dfd, getname(pathname));
पूर्ण

SYSCALL_DEFINE1(unlink, स्थिर अक्षर __user *, pathname)
अणु
	वापस करो_unlinkat(AT_FDCWD, getname(pathname));
पूर्ण

/**
 * vfs_symlink - create symlink
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dir:	inode of @dentry
 * @dentry:	poपूर्णांकer to dentry of the base directory
 * @oldname:	name of the file to link to
 *
 * Create a symlink.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
पूर्णांक vfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		काष्ठा dentry *dentry, स्थिर अक्षर *oldname)
अणु
	पूर्णांक error = may_create(mnt_userns, dir, dentry);

	अगर (error)
		वापस error;

	अगर (!dir->i_op->symlink)
		वापस -EPERM;

	error = security_inode_symlink(dir, dentry, oldname);
	अगर (error)
		वापस error;

	error = dir->i_op->symlink(mnt_userns, dir, dentry, oldname);
	अगर (!error)
		fsnotअगरy_create(dir, dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_symlink);

अटल दीर्घ करो_symlinkat(स्थिर अक्षर __user *oldname, पूर्णांक newdfd,
		  स्थिर अक्षर __user *newname)
अणु
	पूर्णांक error;
	काष्ठा filename *from;
	काष्ठा dentry *dentry;
	काष्ठा path path;
	अचिन्हित पूर्णांक lookup_flags = 0;

	from = getname(oldname);
	अगर (IS_ERR(from))
		वापस PTR_ERR(from);
retry:
	dentry = user_path_create(newdfd, newname, &path, lookup_flags);
	error = PTR_ERR(dentry);
	अगर (IS_ERR(dentry))
		जाओ out_putname;

	error = security_path_symlink(&path, dentry, from->name);
	अगर (!error) अणु
		काष्ठा user_namespace *mnt_userns;

		mnt_userns = mnt_user_ns(path.mnt);
		error = vfs_symlink(mnt_userns, path.dentry->d_inode, dentry,
				    from->name);
	पूर्ण
	करोne_path_create(&path, dentry);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
out_putname:
	putname(from);
	वापस error;
पूर्ण

SYSCALL_DEFINE3(symlinkat, स्थिर अक्षर __user *, oldname,
		पूर्णांक, newdfd, स्थिर अक्षर __user *, newname)
अणु
	वापस करो_symlinkat(oldname, newdfd, newname);
पूर्ण

SYSCALL_DEFINE2(symlink, स्थिर अक्षर __user *, oldname, स्थिर अक्षर __user *, newname)
अणु
	वापस करो_symlinkat(oldname, AT_FDCWD, newname);
पूर्ण

/**
 * vfs_link - create a new link
 * @old_dentry:	object to be linked
 * @mnt_userns:	the user namespace of the mount
 * @dir:	new parent
 * @new_dentry:	where to create the new link
 * @delegated_inode: वापसs inode needing a delegation अवरोध
 *
 * The caller must hold dir->i_mutex
 *
 * If vfs_link discovers a delegation on the to-be-linked file in need
 * of अवरोधing, it will वापस -EWOULDBLOCK and वापस a reference to the
 * inode in delegated_inode.  The caller should then अवरोध the delegation
 * and retry.  Because अवरोधing a delegation may take a दीर्घ समय, the
 * caller should drop the i_mutex beक्रमe करोing so.
 *
 * Alternatively, a caller may pass शून्य क्रम delegated_inode.  This may
 * be appropriate क्रम callers that expect the underlying fileप्रणाली not
 * to be NFS exported.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
पूर्णांक vfs_link(काष्ठा dentry *old_dentry, काष्ठा user_namespace *mnt_userns,
	     काष्ठा inode *dir, काष्ठा dentry *new_dentry,
	     काष्ठा inode **delegated_inode)
अणु
	काष्ठा inode *inode = old_dentry->d_inode;
	अचिन्हित max_links = dir->i_sb->s_max_links;
	पूर्णांक error;

	अगर (!inode)
		वापस -ENOENT;

	error = may_create(mnt_userns, dir, new_dentry);
	अगर (error)
		वापस error;

	अगर (dir->i_sb != inode->i_sb)
		वापस -EXDEV;

	/*
	 * A link to an append-only or immutable file cannot be created.
	 */
	अगर (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		वापस -EPERM;
	/*
	 * Updating the link count will likely cause i_uid and i_gid to
	 * be ग_लिखोn back improperly अगर their true value is unknown to
	 * the vfs.
	 */
	अगर (HAS_UNMAPPED_ID(mnt_userns, inode))
		वापस -EPERM;
	अगर (!dir->i_op->link)
		वापस -EPERM;
	अगर (S_ISसूची(inode->i_mode))
		वापस -EPERM;

	error = security_inode_link(old_dentry, dir, new_dentry);
	अगर (error)
		वापस error;

	inode_lock(inode);
	/* Make sure we करोn't allow creating hardlink to an unlinked file */
	अगर (inode->i_nlink == 0 && !(inode->i_state & I_LINKABLE))
		error =  -ENOENT;
	अन्यथा अगर (max_links && inode->i_nlink >= max_links)
		error = -EMLINK;
	अन्यथा अणु
		error = try_अवरोध_deleg(inode, delegated_inode);
		अगर (!error)
			error = dir->i_op->link(old_dentry, dir, new_dentry);
	पूर्ण

	अगर (!error && (inode->i_state & I_LINKABLE)) अणु
		spin_lock(&inode->i_lock);
		inode->i_state &= ~I_LINKABLE;
		spin_unlock(&inode->i_lock);
	पूर्ण
	inode_unlock(inode);
	अगर (!error)
		fsnotअगरy_link(dir, inode, new_dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_link);

/*
 * Hardlinks are often used in delicate situations.  We aव्योम
 * security-related surprises by not following symlinks on the
 * newname.  --KAB
 *
 * We करोn't follow them on the oldname either to be compatible
 * with linux 2.0, and to aव्योम hard-linking to directories
 * and other special files.  --ADM
 */
अटल पूर्णांक करो_linkat(पूर्णांक olddfd, स्थिर अक्षर __user *oldname, पूर्णांक newdfd,
	      स्थिर अक्षर __user *newname, पूर्णांक flags)
अणु
	काष्ठा user_namespace *mnt_userns;
	काष्ठा dentry *new_dentry;
	काष्ठा path old_path, new_path;
	काष्ठा inode *delegated_inode = शून्य;
	पूर्णांक how = 0;
	पूर्णांक error;

	अगर ((flags & ~(AT_SYMLINK_FOLLOW | AT_EMPTY_PATH)) != 0)
		वापस -EINVAL;
	/*
	 * To use null names we require CAP_DAC_READ_SEARCH
	 * This ensures that not everyone will be able to create
	 * handlink using the passed filedescriptor.
	 */
	अगर (flags & AT_EMPTY_PATH) अणु
		अगर (!capable(CAP_DAC_READ_SEARCH))
			वापस -ENOENT;
		how = LOOKUP_EMPTY;
	पूर्ण

	अगर (flags & AT_SYMLINK_FOLLOW)
		how |= LOOKUP_FOLLOW;
retry:
	error = user_path_at(olddfd, oldname, how, &old_path);
	अगर (error)
		वापस error;

	new_dentry = user_path_create(newdfd, newname, &new_path,
					(how & LOOKUP_REVAL));
	error = PTR_ERR(new_dentry);
	अगर (IS_ERR(new_dentry))
		जाओ out;

	error = -EXDEV;
	अगर (old_path.mnt != new_path.mnt)
		जाओ out_dput;
	mnt_userns = mnt_user_ns(new_path.mnt);
	error = may_linkat(mnt_userns, &old_path);
	अगर (unlikely(error))
		जाओ out_dput;
	error = security_path_link(old_path.dentry, &new_path, new_dentry);
	अगर (error)
		जाओ out_dput;
	error = vfs_link(old_path.dentry, mnt_userns, new_path.dentry->d_inode,
			 new_dentry, &delegated_inode);
out_dput:
	करोne_path_create(&new_path, new_dentry);
	अगर (delegated_inode) अणु
		error = अवरोध_deleg_रुको(&delegated_inode);
		अगर (!error) अणु
			path_put(&old_path);
			जाओ retry;
		पूर्ण
	पूर्ण
	अगर (retry_estale(error, how)) अणु
		path_put(&old_path);
		how |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
out:
	path_put(&old_path);

	वापस error;
पूर्ण

SYSCALL_DEFINE5(linkat, पूर्णांक, olddfd, स्थिर अक्षर __user *, oldname,
		पूर्णांक, newdfd, स्थिर अक्षर __user *, newname, पूर्णांक, flags)
अणु
	वापस करो_linkat(olddfd, oldname, newdfd, newname, flags);
पूर्ण

SYSCALL_DEFINE2(link, स्थिर अक्षर __user *, oldname, स्थिर अक्षर __user *, newname)
अणु
	वापस करो_linkat(AT_FDCWD, oldname, AT_FDCWD, newname, 0);
पूर्ण

/**
 * vfs_नाम - नाम a fileप्रणाली object
 * @rd:		poपूर्णांकer to &काष्ठा नामdata info
 *
 * The caller must hold multiple mutexes--see lock_नाम()).
 *
 * If vfs_नाम discovers a delegation in need of अवरोधing at either
 * the source or destination, it will वापस -EWOULDBLOCK and वापस a
 * reference to the inode in delegated_inode.  The caller should then
 * अवरोध the delegation and retry.  Because अवरोधing a delegation may
 * take a दीर्घ समय, the caller should drop all locks beक्रमe करोing
 * so.
 *
 * Alternatively, a caller may pass शून्य क्रम delegated_inode.  This may
 * be appropriate क्रम callers that expect the underlying fileप्रणाली not
 * to be NFS exported.
 *
 * The worst of all namespace operations - renaming directory. "Perverted"
 * करोesn't even start to describe it. Somebody in UCB had a heck of a trip...
 * Problems:
 *
 *	a) we can get पूर्णांकo loop creation.
 *	b) race potential - two innocent नामs can create a loop together.
 *	   That's where 4.4 screws up. Current fix: serialization on
 *	   sb->s_vfs_नाम_mutex. We might be more accurate, but that's another
 *	   story.
 *	c) we have to lock _four_ objects - parents and victim (अगर it exists),
 *	   and source (अगर it is not a directory).
 *	   And that - after we got ->i_mutex on parents (until then we करोn't know
 *	   whether the target exists).  Solution: try to be smart with locking
 *	   order क्रम inodes.  We rely on the fact that tree topology may change
 *	   only under ->s_vfs_नाम_mutex _and_ that parent of the object we
 *	   move will be locked.  Thus we can rank directories by the tree
 *	   (ancestors first) and rank all non-directories after them.
 *	   That works since everybody except नाम करोes "lock parent, lookup,
 *	   lock child" and नाम is under ->s_vfs_नाम_mutex.
 *	   HOWEVER, it relies on the assumption that any object with ->lookup()
 *	   has no more than 1 dentry.  If "hybrid" objects will ever appear,
 *	   we'd better make sure that there's no link(2) क्रम them.
 *	d) conversion from fhandle to dentry may come in the wrong moment - when
 *	   we are removing the target. Solution: we will have to grab ->i_mutex
 *	   in the fhandle_to_dentry code. [FIXME - current nfsfh.c relies on
 *	   ->i_mutex on parents, which works but leads to some truly excessive
 *	   locking].
 */
पूर्णांक vfs_नाम(काष्ठा नामdata *rd)
अणु
	पूर्णांक error;
	काष्ठा inode *old_dir = rd->old_dir, *new_dir = rd->new_dir;
	काष्ठा dentry *old_dentry = rd->old_dentry;
	काष्ठा dentry *new_dentry = rd->new_dentry;
	काष्ठा inode **delegated_inode = rd->delegated_inode;
	अचिन्हित पूर्णांक flags = rd->flags;
	bool is_dir = d_is_dir(old_dentry);
	काष्ठा inode *source = old_dentry->d_inode;
	काष्ठा inode *target = new_dentry->d_inode;
	bool new_is_dir = false;
	अचिन्हित max_links = new_dir->i_sb->s_max_links;
	काष्ठा name_snapshot old_name;

	अगर (source == target)
		वापस 0;

	error = may_delete(rd->old_mnt_userns, old_dir, old_dentry, is_dir);
	अगर (error)
		वापस error;

	अगर (!target) अणु
		error = may_create(rd->new_mnt_userns, new_dir, new_dentry);
	पूर्ण अन्यथा अणु
		new_is_dir = d_is_dir(new_dentry);

		अगर (!(flags & RENAME_EXCHANGE))
			error = may_delete(rd->new_mnt_userns, new_dir,
					   new_dentry, is_dir);
		अन्यथा
			error = may_delete(rd->new_mnt_userns, new_dir,
					   new_dentry, new_is_dir);
	पूर्ण
	अगर (error)
		वापस error;

	अगर (!old_dir->i_op->नाम)
		वापस -EPERM;

	/*
	 * If we are going to change the parent - check ग_लिखो permissions,
	 * we'll need to flip '..'.
	 */
	अगर (new_dir != old_dir) अणु
		अगर (is_dir) अणु
			error = inode_permission(rd->old_mnt_userns, source,
						 MAY_WRITE);
			अगर (error)
				वापस error;
		पूर्ण
		अगर ((flags & RENAME_EXCHANGE) && new_is_dir) अणु
			error = inode_permission(rd->new_mnt_userns, target,
						 MAY_WRITE);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	error = security_inode_नाम(old_dir, old_dentry, new_dir, new_dentry,
				      flags);
	अगर (error)
		वापस error;

	take_dentry_name_snapshot(&old_name, old_dentry);
	dget(new_dentry);
	अगर (!is_dir || (flags & RENAME_EXCHANGE))
		lock_two_nondirectories(source, target);
	अन्यथा अगर (target)
		inode_lock(target);

	error = -EBUSY;
	अगर (is_local_mountpoपूर्णांक(old_dentry) || is_local_mountpoपूर्णांक(new_dentry))
		जाओ out;

	अगर (max_links && new_dir != old_dir) अणु
		error = -EMLINK;
		अगर (is_dir && !new_is_dir && new_dir->i_nlink >= max_links)
			जाओ out;
		अगर ((flags & RENAME_EXCHANGE) && !is_dir && new_is_dir &&
		    old_dir->i_nlink >= max_links)
			जाओ out;
	पूर्ण
	अगर (!is_dir) अणु
		error = try_अवरोध_deleg(source, delegated_inode);
		अगर (error)
			जाओ out;
	पूर्ण
	अगर (target && !new_is_dir) अणु
		error = try_अवरोध_deleg(target, delegated_inode);
		अगर (error)
			जाओ out;
	पूर्ण
	error = old_dir->i_op->नाम(rd->new_mnt_userns, old_dir, old_dentry,
				      new_dir, new_dentry, flags);
	अगर (error)
		जाओ out;

	अगर (!(flags & RENAME_EXCHANGE) && target) अणु
		अगर (is_dir) अणु
			shrink_dcache_parent(new_dentry);
			target->i_flags |= S_DEAD;
		पूर्ण
		करोnt_mount(new_dentry);
		detach_mounts(new_dentry);
	पूर्ण
	अगर (!(old_dir->i_sb->s_type->fs_flags & FS_RENAME_DOES_D_MOVE)) अणु
		अगर (!(flags & RENAME_EXCHANGE))
			d_move(old_dentry, new_dentry);
		अन्यथा
			d_exchange(old_dentry, new_dentry);
	पूर्ण
out:
	अगर (!is_dir || (flags & RENAME_EXCHANGE))
		unlock_two_nondirectories(source, target);
	अन्यथा अगर (target)
		inode_unlock(target);
	dput(new_dentry);
	अगर (!error) अणु
		fsnotअगरy_move(old_dir, new_dir, &old_name.name, is_dir,
			      !(flags & RENAME_EXCHANGE) ? target : शून्य, old_dentry);
		अगर (flags & RENAME_EXCHANGE) अणु
			fsnotअगरy_move(new_dir, old_dir, &old_dentry->d_name,
				      new_is_dir, शून्य, new_dentry);
		पूर्ण
	पूर्ण
	release_dentry_name_snapshot(&old_name);

	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_नाम);

पूर्णांक करो_नामat2(पूर्णांक olddfd, काष्ठा filename *from, पूर्णांक newdfd,
		 काष्ठा filename *to, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा नामdata rd;
	काष्ठा dentry *old_dentry, *new_dentry;
	काष्ठा dentry *trap;
	काष्ठा path old_path, new_path;
	काष्ठा qstr old_last, new_last;
	पूर्णांक old_type, new_type;
	काष्ठा inode *delegated_inode = शून्य;
	अचिन्हित पूर्णांक lookup_flags = 0, target_flags = LOOKUP_RENAME_TARGET;
	bool should_retry = false;
	पूर्णांक error = -EINVAL;

	अगर (flags & ~(RENAME_NOREPLACE | RENAME_EXCHANGE | RENAME_WHITEOUT))
		जाओ put_both;

	अगर ((flags & (RENAME_NOREPLACE | RENAME_WHITEOUT)) &&
	    (flags & RENAME_EXCHANGE))
		जाओ put_both;

	अगर (flags & RENAME_EXCHANGE)
		target_flags = 0;

retry:
	from = filename_parentat(olddfd, from, lookup_flags, &old_path,
					&old_last, &old_type);
	अगर (IS_ERR(from)) अणु
		error = PTR_ERR(from);
		जाओ put_new;
	पूर्ण

	to = filename_parentat(newdfd, to, lookup_flags, &new_path, &new_last,
				&new_type);
	अगर (IS_ERR(to)) अणु
		error = PTR_ERR(to);
		जाओ निकास1;
	पूर्ण

	error = -EXDEV;
	अगर (old_path.mnt != new_path.mnt)
		जाओ निकास2;

	error = -EBUSY;
	अगर (old_type != LAST_NORM)
		जाओ निकास2;

	अगर (flags & RENAME_NOREPLACE)
		error = -EEXIST;
	अगर (new_type != LAST_NORM)
		जाओ निकास2;

	error = mnt_want_ग_लिखो(old_path.mnt);
	अगर (error)
		जाओ निकास2;

retry_deleg:
	trap = lock_नाम(new_path.dentry, old_path.dentry);

	old_dentry = __lookup_hash(&old_last, old_path.dentry, lookup_flags);
	error = PTR_ERR(old_dentry);
	अगर (IS_ERR(old_dentry))
		जाओ निकास3;
	/* source must exist */
	error = -ENOENT;
	अगर (d_is_negative(old_dentry))
		जाओ निकास4;
	new_dentry = __lookup_hash(&new_last, new_path.dentry, lookup_flags | target_flags);
	error = PTR_ERR(new_dentry);
	अगर (IS_ERR(new_dentry))
		जाओ निकास4;
	error = -EEXIST;
	अगर ((flags & RENAME_NOREPLACE) && d_is_positive(new_dentry))
		जाओ निकास5;
	अगर (flags & RENAME_EXCHANGE) अणु
		error = -ENOENT;
		अगर (d_is_negative(new_dentry))
			जाओ निकास5;

		अगर (!d_is_dir(new_dentry)) अणु
			error = -ENOTसूची;
			अगर (new_last.name[new_last.len])
				जाओ निकास5;
		पूर्ण
	पूर्ण
	/* unless the source is a directory trailing slashes give -ENOTसूची */
	अगर (!d_is_dir(old_dentry)) अणु
		error = -ENOTसूची;
		अगर (old_last.name[old_last.len])
			जाओ निकास5;
		अगर (!(flags & RENAME_EXCHANGE) && new_last.name[new_last.len])
			जाओ निकास5;
	पूर्ण
	/* source should not be ancestor of target */
	error = -EINVAL;
	अगर (old_dentry == trap)
		जाओ निकास5;
	/* target should not be an ancestor of source */
	अगर (!(flags & RENAME_EXCHANGE))
		error = -ENOTEMPTY;
	अगर (new_dentry == trap)
		जाओ निकास5;

	error = security_path_नाम(&old_path, old_dentry,
				     &new_path, new_dentry, flags);
	अगर (error)
		जाओ निकास5;

	rd.old_dir	   = old_path.dentry->d_inode;
	rd.old_dentry	   = old_dentry;
	rd.old_mnt_userns  = mnt_user_ns(old_path.mnt);
	rd.new_dir	   = new_path.dentry->d_inode;
	rd.new_dentry	   = new_dentry;
	rd.new_mnt_userns  = mnt_user_ns(new_path.mnt);
	rd.delegated_inode = &delegated_inode;
	rd.flags	   = flags;
	error = vfs_नाम(&rd);
निकास5:
	dput(new_dentry);
निकास4:
	dput(old_dentry);
निकास3:
	unlock_नाम(new_path.dentry, old_path.dentry);
	अगर (delegated_inode) अणु
		error = अवरोध_deleg_रुको(&delegated_inode);
		अगर (!error)
			जाओ retry_deleg;
	पूर्ण
	mnt_drop_ग_लिखो(old_path.mnt);
निकास2:
	अगर (retry_estale(error, lookup_flags))
		should_retry = true;
	path_put(&new_path);
निकास1:
	path_put(&old_path);
	अगर (should_retry) अणु
		should_retry = false;
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
put_both:
	अगर (!IS_ERR(from))
		putname(from);
put_new:
	अगर (!IS_ERR(to))
		putname(to);
	वापस error;
पूर्ण

SYSCALL_DEFINE5(नामat2, पूर्णांक, olddfd, स्थिर अक्षर __user *, oldname,
		पूर्णांक, newdfd, स्थिर अक्षर __user *, newname, अचिन्हित पूर्णांक, flags)
अणु
	वापस करो_नामat2(olddfd, getname(oldname), newdfd, getname(newname),
				flags);
पूर्ण

SYSCALL_DEFINE4(नामat, पूर्णांक, olddfd, स्थिर अक्षर __user *, oldname,
		पूर्णांक, newdfd, स्थिर अक्षर __user *, newname)
अणु
	वापस करो_नामat2(olddfd, getname(oldname), newdfd, getname(newname),
				0);
पूर्ण

SYSCALL_DEFINE2(नाम, स्थिर अक्षर __user *, oldname, स्थिर अक्षर __user *, newname)
अणु
	वापस करो_नामat2(AT_FDCWD, getname(oldname), AT_FDCWD,
				getname(newname), 0);
पूर्ण

पूर्णांक पढ़ोlink_copy(अक्षर __user *buffer, पूर्णांक buflen, स्थिर अक्षर *link)
अणु
	पूर्णांक len = PTR_ERR(link);
	अगर (IS_ERR(link))
		जाओ out;

	len = म_माप(link);
	अगर (len > (अचिन्हित) buflen)
		len = buflen;
	अगर (copy_to_user(buffer, link, len))
		len = -EFAULT;
out:
	वापस len;
पूर्ण

/**
 * vfs_पढ़ोlink - copy symlink body पूर्णांकo userspace buffer
 * @dentry: dentry on which to get symbolic link
 * @buffer: user memory poपूर्णांकer
 * @buflen: size of buffer
 *
 * Does not touch aसमय.  That's up to the caller अगर necessary
 *
 * Does not call security hook.
 */
पूर्णांक vfs_पढ़ोlink(काष्ठा dentry *dentry, अक्षर __user *buffer, पूर्णांक buflen)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	DEFINE_DELAYED_CALL(करोne);
	स्थिर अक्षर *link;
	पूर्णांक res;

	अगर (unlikely(!(inode->i_opflags & IOP_DEFAULT_READLINK))) अणु
		अगर (unlikely(inode->i_op->पढ़ोlink))
			वापस inode->i_op->पढ़ोlink(dentry, buffer, buflen);

		अगर (!d_is_symlink(dentry))
			वापस -EINVAL;

		spin_lock(&inode->i_lock);
		inode->i_opflags |= IOP_DEFAULT_READLINK;
		spin_unlock(&inode->i_lock);
	पूर्ण

	link = READ_ONCE(inode->i_link);
	अगर (!link) अणु
		link = inode->i_op->get_link(dentry, inode, &करोne);
		अगर (IS_ERR(link))
			वापस PTR_ERR(link);
	पूर्ण
	res = पढ़ोlink_copy(buffer, buflen, link);
	करो_delayed_call(&करोne);
	वापस res;
पूर्ण
EXPORT_SYMBOL(vfs_पढ़ोlink);

/**
 * vfs_get_link - get symlink body
 * @dentry: dentry on which to get symbolic link
 * @करोne: caller needs to मुक्त वापसed data with this
 *
 * Calls security hook and i_op->get_link() on the supplied inode.
 *
 * It करोes not touch aसमय.  That's up to the caller अगर necessary.
 *
 * Does not work on "special" symlinks like /proc/$$/fd/N
 */
स्थिर अक्षर *vfs_get_link(काष्ठा dentry *dentry, काष्ठा delayed_call *करोne)
अणु
	स्थिर अक्षर *res = ERR_PTR(-EINVAL);
	काष्ठा inode *inode = d_inode(dentry);

	अगर (d_is_symlink(dentry)) अणु
		res = ERR_PTR(security_inode_पढ़ोlink(dentry));
		अगर (!res)
			res = inode->i_op->get_link(dentry, inode, करोne);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL(vfs_get_link);

/* get the link contents पूर्णांकo pagecache */
स्थिर अक्षर *page_get_link(काष्ठा dentry *dentry, काष्ठा inode *inode,
			  काष्ठा delayed_call *callback)
अणु
	अक्षर *kaddr;
	काष्ठा page *page;
	काष्ठा address_space *mapping = inode->i_mapping;

	अगर (!dentry) अणु
		page = find_get_page(mapping, 0);
		अगर (!page)
			वापस ERR_PTR(-ECHILD);
		अगर (!PageUptodate(page)) अणु
			put_page(page);
			वापस ERR_PTR(-ECHILD);
		पूर्ण
	पूर्ण अन्यथा अणु
		page = पढ़ो_mapping_page(mapping, 0, शून्य);
		अगर (IS_ERR(page))
			वापस (अक्षर*)page;
	पूर्ण
	set_delayed_call(callback, page_put_link, page);
	BUG_ON(mapping_gfp_mask(mapping) & __GFP_HIGHMEM);
	kaddr = page_address(page);
	nd_terminate_link(kaddr, inode->i_size, PAGE_SIZE - 1);
	वापस kaddr;
पूर्ण

EXPORT_SYMBOL(page_get_link);

व्योम page_put_link(व्योम *arg)
अणु
	put_page(arg);
पूर्ण
EXPORT_SYMBOL(page_put_link);

पूर्णांक page_पढ़ोlink(काष्ठा dentry *dentry, अक्षर __user *buffer, पूर्णांक buflen)
अणु
	DEFINE_DELAYED_CALL(करोne);
	पूर्णांक res = पढ़ोlink_copy(buffer, buflen,
				page_get_link(dentry, d_inode(dentry),
					      &करोne));
	करो_delayed_call(&करोne);
	वापस res;
पूर्ण
EXPORT_SYMBOL(page_पढ़ोlink);

/*
 * The nofs argument inकाष्ठाs pagecache_ग_लिखो_begin to pass AOP_FLAG_NOFS
 */
पूर्णांक __page_symlink(काष्ठा inode *inode, स्थिर अक्षर *symname, पूर्णांक len, पूर्णांक nofs)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;
	व्योम *fsdata;
	पूर्णांक err;
	अचिन्हित पूर्णांक flags = 0;
	अगर (nofs)
		flags |= AOP_FLAG_NOFS;

retry:
	err = pagecache_ग_लिखो_begin(शून्य, mapping, 0, len-1,
				flags, &page, &fsdata);
	अगर (err)
		जाओ fail;

	स_नकल(page_address(page), symname, len-1);

	err = pagecache_ग_लिखो_end(शून्य, mapping, 0, len-1, len-1,
							page, fsdata);
	अगर (err < 0)
		जाओ fail;
	अगर (err < len-1)
		जाओ retry;

	mark_inode_dirty(inode);
	वापस 0;
fail:
	वापस err;
पूर्ण
EXPORT_SYMBOL(__page_symlink);

पूर्णांक page_symlink(काष्ठा inode *inode, स्थिर अक्षर *symname, पूर्णांक len)
अणु
	वापस __page_symlink(inode, symname, len,
			!mapping_gfp_स्थिरraपूर्णांक(inode->i_mapping, __GFP_FS));
पूर्ण
EXPORT_SYMBOL(page_symlink);

स्थिर काष्ठा inode_operations page_symlink_inode_operations = अणु
	.get_link	= page_get_link,
पूर्ण;
EXPORT_SYMBOL(page_symlink_inode_operations);
