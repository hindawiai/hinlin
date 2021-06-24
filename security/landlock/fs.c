<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Landlock LSM - Fileप्रणाली management and hooks
 *
 * Copyright तऊ 2016-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2018-2020 ANSSI
 */

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bits.h>
#समावेश <linux/compiler_types.h>
#समावेश <linux/dcache.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/path.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/types.h>
#समावेश <linux/रुको_bit.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/linux/landlock.h>

#समावेश "common.h"
#समावेश "cred.h"
#समावेश "fs.h"
#समावेश "limits.h"
#समावेश "object.h"
#समावेश "ruleset.h"
#समावेश "setup.h"

/* Underlying object management */

अटल व्योम release_inode(काष्ठा landlock_object *स्थिर object)
	__releases(object->lock)
अणु
	काष्ठा inode *स्थिर inode = object->underobj;
	काष्ठा super_block *sb;

	अगर (!inode) अणु
		spin_unlock(&object->lock);
		वापस;
	पूर्ण

	/*
	 * Protects against concurrent use by hook_sb_delete() of the reference
	 * to the underlying inode.
	 */
	object->underobj = शून्य;
	/*
	 * Makes sure that अगर the fileप्रणाली is concurrently unmounted,
	 * hook_sb_delete() will रुको क्रम us to finish iput().
	 */
	sb = inode->i_sb;
	atomic_दीर्घ_inc(&landlock_superblock(sb)->inode_refs);
	spin_unlock(&object->lock);
	/*
	 * Because object->underobj was not शून्य, hook_sb_delete() and
	 * get_inode_object() guarantee that it is safe to reset
	 * landlock_inode(inode)->object जबतक it is not शून्य.  It is thereक्रमe
	 * not necessary to lock inode->i_lock.
	 */
	rcu_assign_poपूर्णांकer(landlock_inode(inode)->object, शून्य);
	/*
	 * Now, new rules can safely be tied to @inode with get_inode_object().
	 */

	iput(inode);
	अगर (atomic_दीर्घ_dec_and_test(&landlock_superblock(sb)->inode_refs))
		wake_up_var(&landlock_superblock(sb)->inode_refs);
पूर्ण

अटल स्थिर काष्ठा landlock_object_underops landlock_fs_underops = अणु
	.release = release_inode
पूर्ण;

/* Ruleset management */

अटल काष्ठा landlock_object *get_inode_object(काष्ठा inode *स्थिर inode)
अणु
	काष्ठा landlock_object *object, *new_object;
	काष्ठा landlock_inode_security *inode_sec = landlock_inode(inode);

	rcu_पढ़ो_lock();
retry:
	object = rcu_dereference(inode_sec->object);
	अगर (object) अणु
		अगर (likely(refcount_inc_not_zero(&object->usage))) अणु
			rcu_पढ़ो_unlock();
			वापस object;
		पूर्ण
		/*
		 * We are racing with release_inode(), the object is going
		 * away.  Wait क्रम release_inode(), then retry.
		 */
		spin_lock(&object->lock);
		spin_unlock(&object->lock);
		जाओ retry;
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * If there is no object tied to @inode, then create a new one (without
	 * holding any locks).
	 */
	new_object = landlock_create_object(&landlock_fs_underops, inode);
	अगर (IS_ERR(new_object))
		वापस new_object;

	/*
	 * Protects against concurrent calls to get_inode_object() or
	 * hook_sb_delete().
	 */
	spin_lock(&inode->i_lock);
	अगर (unlikely(rcu_access_poपूर्णांकer(inode_sec->object))) अणु
		/* Someone अन्यथा just created the object, bail out and retry. */
		spin_unlock(&inode->i_lock);
		kमुक्त(new_object);

		rcu_पढ़ो_lock();
		जाओ retry;
	पूर्ण

	/*
	 * @inode will be released by hook_sb_delete() on its superblock
	 * shutकरोwn, or by release_inode() when no more ruleset references the
	 * related object.
	 */
	ihold(inode);
	rcu_assign_poपूर्णांकer(inode_sec->object, new_object);
	spin_unlock(&inode->i_lock);
	वापस new_object;
पूर्ण

/* All access rights that can be tied to files. */
#घोषणा ACCESS_खाता ( \
	LANDLOCK_ACCESS_FS_EXECUTE | \
	LANDLOCK_ACCESS_FS_WRITE_खाता | \
	LANDLOCK_ACCESS_FS_READ_खाता)

/*
 * @path: Should have been checked by get_path_from_fd().
 */
पूर्णांक landlock_append_fs_rule(काष्ठा landlock_ruleset *स्थिर ruleset,
		स्थिर काष्ठा path *स्थिर path, u32 access_rights)
अणु
	पूर्णांक err;
	काष्ठा landlock_object *object;

	/* Files only get access rights that make sense. */
	अगर (!d_is_dir(path->dentry) && (access_rights | ACCESS_खाता) !=
			ACCESS_खाता)
		वापस -EINVAL;
	अगर (WARN_ON_ONCE(ruleset->num_layers != 1))
		वापस -EINVAL;

	/* Transक्रमms relative access rights to असलolute ones. */
	access_rights |= LANDLOCK_MASK_ACCESS_FS & ~ruleset->fs_access_masks[0];
	object = get_inode_object(d_backing_inode(path->dentry));
	अगर (IS_ERR(object))
		वापस PTR_ERR(object);
	mutex_lock(&ruleset->lock);
	err = landlock_insert_rule(ruleset, object, access_rights);
	mutex_unlock(&ruleset->lock);
	/*
	 * No need to check क्रम an error because landlock_insert_rule()
	 * increments the refcount क्रम the new object अगर needed.
	 */
	landlock_put_object(object);
	वापस err;
पूर्ण

/* Access-control management */

अटल अंतरभूत u64 unmask_layers(
		स्थिर काष्ठा landlock_ruleset *स्थिर करोमुख्य,
		स्थिर काष्ठा path *स्थिर path, स्थिर u32 access_request,
		u64 layer_mask)
अणु
	स्थिर काष्ठा landlock_rule *rule;
	स्थिर काष्ठा inode *inode;
	माप_प्रकार i;

	अगर (d_is_negative(path->dentry))
		/* Ignore nonexistent leafs. */
		वापस layer_mask;
	inode = d_backing_inode(path->dentry);
	rcu_पढ़ो_lock();
	rule = landlock_find_rule(करोमुख्य,
			rcu_dereference(landlock_inode(inode)->object));
	rcu_पढ़ो_unlock();
	अगर (!rule)
		वापस layer_mask;

	/*
	 * An access is granted अगर, क्रम each policy layer, at least one rule
	 * encountered on the pathwalk grants the requested accesses,
	 * regardless of their position in the layer stack.  We must then check
	 * the reमुख्यing layers क्रम each inode, from the first added layer to
	 * the last one.
	 */
	क्रम (i = 0; i < rule->num_layers; i++) अणु
		स्थिर काष्ठा landlock_layer *स्थिर layer = &rule->layers[i];
		स्थिर u64 layer_level = BIT_ULL(layer->level - 1);

		/* Checks that the layer grants access to the full request. */
		अगर ((layer->access & access_request) == access_request) अणु
			layer_mask &= ~layer_level;

			अगर (layer_mask == 0)
				वापस layer_mask;
		पूर्ण
	पूर्ण
	वापस layer_mask;
पूर्ण

अटल पूर्णांक check_access_path(स्थिर काष्ठा landlock_ruleset *स्थिर करोमुख्य,
		स्थिर काष्ठा path *स्थिर path, u32 access_request)
अणु
	bool allowed = false;
	काष्ठा path walker_path;
	u64 layer_mask;
	माप_प्रकार i;

	/* Make sure all layers can be checked. */
	BUILD_BUG_ON(BITS_PER_TYPE(layer_mask) < LANDLOCK_MAX_NUM_LAYERS);

	अगर (!access_request)
		वापस 0;
	अगर (WARN_ON_ONCE(!करोमुख्य || !path))
		वापस 0;
	/*
	 * Allows access to pseuकरो fileप्रणालीs that will never be mountable
	 * (e.g. sockfs, pipefs), but can still be reachable through
	 * /proc/<pid>/fd/<file-descriptor> .
	 */
	अगर ((path->dentry->d_sb->s_flags & SB_NOUSER) ||
			(d_is_positive(path->dentry) &&
			 unlikely(IS_PRIVATE(d_backing_inode(path->dentry)))))
		वापस 0;
	अगर (WARN_ON_ONCE(करोमुख्य->num_layers < 1))
		वापस -EACCES;

	/* Saves all layers handling a subset of requested accesses. */
	layer_mask = 0;
	क्रम (i = 0; i < करोमुख्य->num_layers; i++) अणु
		अगर (करोमुख्य->fs_access_masks[i] & access_request)
			layer_mask |= BIT_ULL(i);
	पूर्ण
	/* An access request not handled by the करोमुख्य is allowed. */
	अगर (layer_mask == 0)
		वापस 0;

	walker_path = *path;
	path_get(&walker_path);
	/*
	 * We need to walk through all the hierarchy to not miss any relevant
	 * restriction.
	 */
	जबतक (true) अणु
		काष्ठा dentry *parent_dentry;

		layer_mask = unmask_layers(करोमुख्य, &walker_path,
				access_request, layer_mask);
		अगर (layer_mask == 0) अणु
			/* Stops when a rule from each layer grants access. */
			allowed = true;
			अवरोध;
		पूर्ण

jump_up:
		अगर (walker_path.dentry == walker_path.mnt->mnt_root) अणु
			अगर (follow_up(&walker_path)) अणु
				/* Ignores hidden mount poपूर्णांकs. */
				जाओ jump_up;
			पूर्ण अन्यथा अणु
				/*
				 * Stops at the real root.  Denies access
				 * because not all layers have granted access.
				 */
				allowed = false;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (unlikely(IS_ROOT(walker_path.dentry))) अणु
			/*
			 * Stops at disconnected root directories.  Only allows
			 * access to पूर्णांकernal fileप्रणालीs (e.g. nsfs, which is
			 * reachable through /proc/<pid>/ns/<namespace>).
			 */
			allowed = !!(walker_path.mnt->mnt_flags & MNT_INTERNAL);
			अवरोध;
		पूर्ण
		parent_dentry = dget_parent(walker_path.dentry);
		dput(walker_path.dentry);
		walker_path.dentry = parent_dentry;
	पूर्ण
	path_put(&walker_path);
	वापस allowed ? 0 : -EACCES;
पूर्ण

अटल अंतरभूत पूर्णांक current_check_access_path(स्थिर काष्ठा path *स्थिर path,
		स्थिर u32 access_request)
अणु
	स्थिर काष्ठा landlock_ruleset *स्थिर करोm =
		landlock_get_current_करोमुख्य();

	अगर (!करोm)
		वापस 0;
	वापस check_access_path(करोm, path, access_request);
पूर्ण

/* Inode hooks */

अटल व्योम hook_inode_मुक्त_security(काष्ठा inode *स्थिर inode)
अणु
	/*
	 * All inodes must alपढ़ोy have been untied from their object by
	 * release_inode() or hook_sb_delete().
	 */
	WARN_ON_ONCE(landlock_inode(inode)->object);
पूर्ण

/* Super-block hooks */

/*
 * Release the inodes used in a security policy.
 *
 * Cf. fsnotअगरy_unmount_inodes() and invalidate_inodes()
 */
अटल व्योम hook_sb_delete(काष्ठा super_block *स्थिर sb)
अणु
	काष्ठा inode *inode, *prev_inode = शून्य;

	अगर (!landlock_initialized)
		वापस;

	spin_lock(&sb->s_inode_list_lock);
	list_क्रम_each_entry(inode, &sb->s_inodes, i_sb_list) अणु
		काष्ठा landlock_object *object;

		/* Only handles referenced inodes. */
		अगर (!atomic_पढ़ो(&inode->i_count))
			जारी;

		/*
		 * Protects against concurrent modअगरication of inode (e.g.
		 * from get_inode_object()).
		 */
		spin_lock(&inode->i_lock);
		/*
		 * Checks I_FREEING and I_WILL_FREE  to protect against a race
		 * condition when release_inode() just called iput(), which
		 * could lead to a शून्य dereference of inode->security or a
		 * second call to iput() क्रम the same Landlock object.  Also
		 * checks I_NEW because such inode cannot be tied to an object.
		 */
		अगर (inode->i_state & (I_FREEING | I_WILL_FREE | I_NEW)) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण

		rcu_पढ़ो_lock();
		object = rcu_dereference(landlock_inode(inode)->object);
		अगर (!object) अणु
			rcu_पढ़ो_unlock();
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण
		/* Keeps a reference to this inode until the next loop walk. */
		__iget(inode);
		spin_unlock(&inode->i_lock);

		/*
		 * If there is no concurrent release_inode() ongoing, then we
		 * are in अक्षरge of calling iput() on this inode, otherwise we
		 * will just रुको क्रम it to finish.
		 */
		spin_lock(&object->lock);
		अगर (object->underobj == inode) अणु
			object->underobj = शून्य;
			spin_unlock(&object->lock);
			rcu_पढ़ो_unlock();

			/*
			 * Because object->underobj was not शून्य,
			 * release_inode() and get_inode_object() guarantee
			 * that it is safe to reset
			 * landlock_inode(inode)->object जबतक it is not शून्य.
			 * It is thereक्रमe not necessary to lock inode->i_lock.
			 */
			rcu_assign_poपूर्णांकer(landlock_inode(inode)->object, शून्य);
			/*
			 * At this poपूर्णांक, we own the ihold() reference that was
			 * originally set up by get_inode_object() and the
			 * __iget() reference that we just set in this loop
			 * walk.  Thereक्रमe the following call to iput() will
			 * not sleep nor drop the inode because there is now at
			 * least two references to it.
			 */
			iput(inode);
		पूर्ण अन्यथा अणु
			spin_unlock(&object->lock);
			rcu_पढ़ो_unlock();
		पूर्ण

		अगर (prev_inode) अणु
			/*
			 * At this poपूर्णांक, we still own the __iget() reference
			 * that we just set in this loop walk.  Thereक्रमe we
			 * can drop the list lock and know that the inode won't
			 * disappear from under us until the next loop walk.
			 */
			spin_unlock(&sb->s_inode_list_lock);
			/*
			 * We can now actually put the inode reference from the
			 * previous loop walk, which is not needed anymore.
			 */
			iput(prev_inode);
			cond_resched();
			spin_lock(&sb->s_inode_list_lock);
		पूर्ण
		prev_inode = inode;
	पूर्ण
	spin_unlock(&sb->s_inode_list_lock);

	/* Puts the inode reference from the last loop walk, अगर any. */
	अगर (prev_inode)
		iput(prev_inode);
	/* Waits क्रम pending iput() in release_inode(). */
	रुको_var_event(&landlock_superblock(sb)->inode_refs, !atomic_दीर्घ_पढ़ो(
				&landlock_superblock(sb)->inode_refs));
पूर्ण

/*
 * Because a Landlock security policy is defined according to the fileप्रणाली
 * topology (i.e. the mount namespace), changing it may grant access to files
 * not previously allowed.
 *
 * To make it simple, deny any fileप्रणाली topology modअगरication by landlocked
 * processes.  Non-landlocked processes may still change the namespace of a
 * landlocked process, but this kind of threat must be handled by a प्रणाली-wide
 * access-control security policy.
 *
 * This could be lअगरted in the future अगर Landlock can safely handle mount
 * namespace updates requested by a landlocked process.  Indeed, we could
 * update the current करोमुख्य (which is currently पढ़ो-only) by taking पूर्णांकo
 * account the accesses of the source and the destination of a new mount poपूर्णांक.
 * However, it would also require to make all the child करोमुख्यs dynamically
 * inherit these new स्थिरraपूर्णांकs.  Anyway, क्रम backward compatibility reasons,
 * a dedicated user space option would be required (e.g. as a ruleset flag).
 */
अटल पूर्णांक hook_sb_mount(स्थिर अक्षर *स्थिर dev_name,
		स्थिर काष्ठा path *स्थिर path, स्थिर अक्षर *स्थिर type,
		स्थिर अचिन्हित दीर्घ flags, व्योम *स्थिर data)
अणु
	अगर (!landlock_get_current_करोमुख्य())
		वापस 0;
	वापस -EPERM;
पूर्ण

अटल पूर्णांक hook_move_mount(स्थिर काष्ठा path *स्थिर from_path,
		स्थिर काष्ठा path *स्थिर to_path)
अणु
	अगर (!landlock_get_current_करोमुख्य())
		वापस 0;
	वापस -EPERM;
पूर्ण

/*
 * Removing a mount poपूर्णांक may reveal a previously hidden file hierarchy, which
 * may then grant access to files, which may have previously been क्रमbidden.
 */
अटल पूर्णांक hook_sb_umount(काष्ठा vfsmount *स्थिर mnt, स्थिर पूर्णांक flags)
अणु
	अगर (!landlock_get_current_करोमुख्य())
		वापस 0;
	वापस -EPERM;
पूर्ण

अटल पूर्णांक hook_sb_remount(काष्ठा super_block *स्थिर sb, व्योम *स्थिर mnt_opts)
अणु
	अगर (!landlock_get_current_करोमुख्य())
		वापस 0;
	वापस -EPERM;
पूर्ण

/*
 * pivot_root(2), like mount(2), changes the current mount namespace.  It must
 * then be क्रमbidden क्रम a landlocked process.
 *
 * However, chroot(2) may be allowed because it only changes the relative root
 * directory of the current process.  Moreover, it can be used to restrict the
 * view of the fileप्रणाली.
 */
अटल पूर्णांक hook_sb_pivotroot(स्थिर काष्ठा path *स्थिर old_path,
		स्थिर काष्ठा path *स्थिर new_path)
अणु
	अगर (!landlock_get_current_करोमुख्य())
		वापस 0;
	वापस -EPERM;
पूर्ण

/* Path hooks */

अटल अंतरभूत u32 get_mode_access(स्थिर umode_t mode)
अणु
	चयन (mode & S_IFMT) अणु
	हाल S_IFLNK:
		वापस LANDLOCK_ACCESS_FS_MAKE_SYM;
	हाल 0:
		/* A zero mode translates to S_IFREG. */
	हाल S_IFREG:
		वापस LANDLOCK_ACCESS_FS_MAKE_REG;
	हाल S_IFसूची:
		वापस LANDLOCK_ACCESS_FS_MAKE_सूची;
	हाल S_IFCHR:
		वापस LANDLOCK_ACCESS_FS_MAKE_CHAR;
	हाल S_IFBLK:
		वापस LANDLOCK_ACCESS_FS_MAKE_BLOCK;
	हाल S_IFIFO:
		वापस LANDLOCK_ACCESS_FS_MAKE_FIFO;
	हाल S_IFSOCK:
		वापस LANDLOCK_ACCESS_FS_MAKE_SOCK;
	शेष:
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Creating multiple links or renaming may lead to privilege escalations अगर not
 * handled properly.  Indeed, we must be sure that the source करोesn't gain more
 * privileges by being accessible from the destination.  This is getting more
 * complex when dealing with multiple layers.  The whole picture can be seen as
 * a multilayer partial ordering problem.  A future version of Landlock will
 * deal with that.
 */
अटल पूर्णांक hook_path_link(काष्ठा dentry *स्थिर old_dentry,
		स्थिर काष्ठा path *स्थिर new_dir,
		काष्ठा dentry *स्थिर new_dentry)
अणु
	स्थिर काष्ठा landlock_ruleset *स्थिर करोm =
		landlock_get_current_करोमुख्य();

	अगर (!करोm)
		वापस 0;
	/* The mount poपूर्णांकs are the same क्रम old and new paths, cf. EXDEV. */
	अगर (old_dentry->d_parent != new_dir->dentry)
		/* Gracefully क्रमbids reparenting. */
		वापस -EXDEV;
	अगर (unlikely(d_is_negative(old_dentry)))
		वापस -ENOENT;
	वापस check_access_path(करोm, new_dir,
			get_mode_access(d_backing_inode(old_dentry)->i_mode));
पूर्ण

अटल अंतरभूत u32 maybe_हटाओ(स्थिर काष्ठा dentry *स्थिर dentry)
अणु
	अगर (d_is_negative(dentry))
		वापस 0;
	वापस d_is_dir(dentry) ? LANDLOCK_ACCESS_FS_REMOVE_सूची :
		LANDLOCK_ACCESS_FS_REMOVE_खाता;
पूर्ण

अटल पूर्णांक hook_path_नाम(स्थिर काष्ठा path *स्थिर old_dir,
		काष्ठा dentry *स्थिर old_dentry,
		स्थिर काष्ठा path *स्थिर new_dir,
		काष्ठा dentry *स्थिर new_dentry)
अणु
	स्थिर काष्ठा landlock_ruleset *स्थिर करोm =
		landlock_get_current_करोमुख्य();

	अगर (!करोm)
		वापस 0;
	/* The mount poपूर्णांकs are the same क्रम old and new paths, cf. EXDEV. */
	अगर (old_dir->dentry != new_dir->dentry)
		/* Gracefully क्रमbids reparenting. */
		वापस -EXDEV;
	अगर (unlikely(d_is_negative(old_dentry)))
		वापस -ENOENT;
	/* RENAME_EXCHANGE is handled because directories are the same. */
	वापस check_access_path(करोm, old_dir, maybe_हटाओ(old_dentry) |
			maybe_हटाओ(new_dentry) |
			get_mode_access(d_backing_inode(old_dentry)->i_mode));
पूर्ण

अटल पूर्णांक hook_path_सूची_गढ़ो(स्थिर काष्ठा path *स्थिर dir,
		काष्ठा dentry *स्थिर dentry, स्थिर umode_t mode)
अणु
	वापस current_check_access_path(dir, LANDLOCK_ACCESS_FS_MAKE_सूची);
पूर्ण

अटल पूर्णांक hook_path_mknod(स्थिर काष्ठा path *स्थिर dir,
		काष्ठा dentry *स्थिर dentry, स्थिर umode_t mode,
		स्थिर अचिन्हित पूर्णांक dev)
अणु
	स्थिर काष्ठा landlock_ruleset *स्थिर करोm =
		landlock_get_current_करोमुख्य();

	अगर (!करोm)
		वापस 0;
	वापस check_access_path(करोm, dir, get_mode_access(mode));
पूर्ण

अटल पूर्णांक hook_path_symlink(स्थिर काष्ठा path *स्थिर dir,
		काष्ठा dentry *स्थिर dentry, स्थिर अक्षर *स्थिर old_name)
अणु
	वापस current_check_access_path(dir, LANDLOCK_ACCESS_FS_MAKE_SYM);
पूर्ण

अटल पूर्णांक hook_path_unlink(स्थिर काष्ठा path *स्थिर dir,
		काष्ठा dentry *स्थिर dentry)
अणु
	वापस current_check_access_path(dir, LANDLOCK_ACCESS_FS_REMOVE_खाता);
पूर्ण

अटल पूर्णांक hook_path_सूची_हटाओ(स्थिर काष्ठा path *स्थिर dir,
		काष्ठा dentry *स्थिर dentry)
अणु
	वापस current_check_access_path(dir, LANDLOCK_ACCESS_FS_REMOVE_सूची);
पूर्ण

/* File hooks */

अटल अंतरभूत u32 get_file_access(स्थिर काष्ठा file *स्थिर file)
अणु
	u32 access = 0;

	अगर (file->f_mode & FMODE_READ) अणु
		/* A directory can only be खोलोed in पढ़ो mode. */
		अगर (S_ISसूची(file_inode(file)->i_mode))
			वापस LANDLOCK_ACCESS_FS_READ_सूची;
		access = LANDLOCK_ACCESS_FS_READ_खाता;
	पूर्ण
	अगर (file->f_mode & FMODE_WRITE)
		access |= LANDLOCK_ACCESS_FS_WRITE_खाता;
	/* __FMODE_EXEC is indeed part of f_flags, not f_mode. */
	अगर (file->f_flags & __FMODE_EXEC)
		access |= LANDLOCK_ACCESS_FS_EXECUTE;
	वापस access;
पूर्ण

अटल पूर्णांक hook_file_खोलो(काष्ठा file *स्थिर file)
अणु
	स्थिर काष्ठा landlock_ruleset *स्थिर करोm =
		landlock_get_current_करोमुख्य();

	अगर (!करोm)
		वापस 0;
	/*
	 * Because a file may be खोलोed with O_PATH, get_file_access() may
	 * वापस 0.  This हाल will be handled with a future Landlock
	 * evolution.
	 */
	वापस check_access_path(करोm, &file->f_path, get_file_access(file));
पूर्ण

अटल काष्ठा security_hook_list landlock_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(inode_मुक्त_security, hook_inode_मुक्त_security),

	LSM_HOOK_INIT(sb_delete, hook_sb_delete),
	LSM_HOOK_INIT(sb_mount, hook_sb_mount),
	LSM_HOOK_INIT(move_mount, hook_move_mount),
	LSM_HOOK_INIT(sb_umount, hook_sb_umount),
	LSM_HOOK_INIT(sb_remount, hook_sb_remount),
	LSM_HOOK_INIT(sb_pivotroot, hook_sb_pivotroot),

	LSM_HOOK_INIT(path_link, hook_path_link),
	LSM_HOOK_INIT(path_नाम, hook_path_नाम),
	LSM_HOOK_INIT(path_सूची_गढ़ो, hook_path_सूची_गढ़ो),
	LSM_HOOK_INIT(path_mknod, hook_path_mknod),
	LSM_HOOK_INIT(path_symlink, hook_path_symlink),
	LSM_HOOK_INIT(path_unlink, hook_path_unlink),
	LSM_HOOK_INIT(path_सूची_हटाओ, hook_path_सूची_हटाओ),

	LSM_HOOK_INIT(file_खोलो, hook_file_खोलो),
पूर्ण;

__init व्योम landlock_add_fs_hooks(व्योम)
अणु
	security_add_hooks(landlock_hooks, ARRAY_SIZE(landlock_hooks),
			LANDLOCK_NAME);
पूर्ण
