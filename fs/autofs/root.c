<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved
 * Copyright 1999-2000 Jeremy Fitzhardinge <jeremy@goop.org>
 * Copyright 2001-2006 Ian Kent <raven@themaw.net>
 */

#समावेश <linux/capability.h>
#समावेश <linux/compat.h>

#समावेश "autofs_i.h"

अटल पूर्णांक स्वतःfs_dir_symlink(काष्ठा user_namespace *, काष्ठा inode *,
			      काष्ठा dentry *, स्थिर अक्षर *);
अटल पूर्णांक स्वतःfs_dir_unlink(काष्ठा inode *, काष्ठा dentry *);
अटल पूर्णांक स्वतःfs_dir_सूची_हटाओ(काष्ठा inode *, काष्ठा dentry *);
अटल पूर्णांक स्वतःfs_dir_सूची_गढ़ो(काष्ठा user_namespace *, काष्ठा inode *,
			    काष्ठा dentry *, umode_t);
अटल दीर्घ स्वतःfs_root_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ स्वतःfs_root_compat_ioctl(काष्ठा file *,
				     अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#पूर्ण_अगर
अटल पूर्णांक स्वतःfs_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल काष्ठा dentry *स्वतःfs_lookup(काष्ठा inode *,
				    काष्ठा dentry *, अचिन्हित पूर्णांक);
अटल काष्ठा vfsmount *स्वतःfs_d_स्वतःmount(काष्ठा path *);
अटल पूर्णांक स्वतःfs_d_manage(स्थिर काष्ठा path *, bool);
अटल व्योम स्वतःfs_dentry_release(काष्ठा dentry *);

स्थिर काष्ठा file_operations स्वतःfs_root_operations = अणु
	.खोलो		= dcache_dir_खोलो,
	.release	= dcache_dir_बंद,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= dcache_सूची_पढ़ो,
	.llseek		= dcache_dir_lseek,
	.unlocked_ioctl	= स्वतःfs_root_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= स्वतःfs_root_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा file_operations स्वतःfs_dir_operations = अणु
	.खोलो		= स्वतःfs_dir_खोलो,
	.release	= dcache_dir_बंद,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= dcache_सूची_पढ़ो,
	.llseek		= dcache_dir_lseek,
पूर्ण;

स्थिर काष्ठा inode_operations स्वतःfs_dir_inode_operations = अणु
	.lookup		= स्वतःfs_lookup,
	.unlink		= स्वतःfs_dir_unlink,
	.symlink	= स्वतःfs_dir_symlink,
	.सूची_गढ़ो		= स्वतःfs_dir_सूची_गढ़ो,
	.सूची_हटाओ		= स्वतःfs_dir_सूची_हटाओ,
पूर्ण;

स्थिर काष्ठा dentry_operations स्वतःfs_dentry_operations = अणु
	.d_स्वतःmount	= स्वतःfs_d_स्वतःmount,
	.d_manage	= स्वतःfs_d_manage,
	.d_release	= स्वतःfs_dentry_release,
पूर्ण;

अटल व्योम स्वतःfs_del_active(काष्ठा dentry *dentry)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);
	काष्ठा स्वतःfs_info *ino;

	ino = स्वतःfs_dentry_ino(dentry);
	spin_lock(&sbi->lookup_lock);
	list_del_init(&ino->active);
	spin_unlock(&sbi->lookup_lock);
पूर्ण

अटल पूर्णांक स्वतःfs_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);

	pr_debug("file=%p dentry=%p %pd\n", file, dentry, dentry);

	अगर (स्वतःfs_oz_mode(sbi))
		जाओ out;

	/*
	 * An empty directory in an स्वतःfs file प्रणाली is always a
	 * mount poपूर्णांक. The daemon must have failed to mount this
	 * during lookup so it करोesn't exist. This can happen, क्रम
	 * example, अगर user space वापसs an incorrect status क्रम a
	 * mount request. Otherwise we're करोing a सूची_पढ़ो on the
	 * स्वतःfs file प्रणाली so just let the libfs routines handle
	 * it.
	 */
	spin_lock(&sbi->lookup_lock);
	अगर (!path_is_mountpoपूर्णांक(&file->f_path) && simple_empty(dentry)) अणु
		spin_unlock(&sbi->lookup_lock);
		वापस -ENOENT;
	पूर्ण
	spin_unlock(&sbi->lookup_lock);

out:
	वापस dcache_dir_खोलो(inode, file);
पूर्ण

अटल व्योम स्वतःfs_dentry_release(काष्ठा dentry *de)
अणु
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(de);
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(de->d_sb);

	pr_debug("releasing %p\n", de);

	अगर (!ino)
		वापस;

	अगर (sbi) अणु
		spin_lock(&sbi->lookup_lock);
		अगर (!list_empty(&ino->active))
			list_del(&ino->active);
		अगर (!list_empty(&ino->expiring))
			list_del(&ino->expiring);
		spin_unlock(&sbi->lookup_lock);
	पूर्ण

	स्वतःfs_मुक्त_ino(ino);
पूर्ण

अटल काष्ठा dentry *स्वतःfs_lookup_active(काष्ठा dentry *dentry)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);
	काष्ठा dentry *parent = dentry->d_parent;
	स्थिर काष्ठा qstr *name = &dentry->d_name;
	अचिन्हित पूर्णांक len = name->len;
	अचिन्हित पूर्णांक hash = name->hash;
	स्थिर अचिन्हित अक्षर *str = name->name;
	काष्ठा list_head *p, *head;

	head = &sbi->active_list;
	अगर (list_empty(head))
		वापस शून्य;
	spin_lock(&sbi->lookup_lock);
	list_क्रम_each(p, head) अणु
		काष्ठा स्वतःfs_info *ino;
		काष्ठा dentry *active;
		स्थिर काष्ठा qstr *qstr;

		ino = list_entry(p, काष्ठा स्वतःfs_info, active);
		active = ino->dentry;

		spin_lock(&active->d_lock);

		/* Alपढ़ोy gone? */
		अगर ((पूर्णांक) d_count(active) <= 0)
			जाओ next;

		qstr = &active->d_name;

		अगर (active->d_name.hash != hash)
			जाओ next;
		अगर (active->d_parent != parent)
			जाओ next;

		अगर (qstr->len != len)
			जाओ next;
		अगर (स_भेद(qstr->name, str, len))
			जाओ next;

		अगर (d_unhashed(active)) अणु
			dget_dlock(active);
			spin_unlock(&active->d_lock);
			spin_unlock(&sbi->lookup_lock);
			वापस active;
		पूर्ण
next:
		spin_unlock(&active->d_lock);
	पूर्ण
	spin_unlock(&sbi->lookup_lock);

	वापस शून्य;
पूर्ण

अटल काष्ठा dentry *स्वतःfs_lookup_expiring(काष्ठा dentry *dentry,
					     bool rcu_walk)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);
	काष्ठा dentry *parent = dentry->d_parent;
	स्थिर काष्ठा qstr *name = &dentry->d_name;
	अचिन्हित पूर्णांक len = name->len;
	अचिन्हित पूर्णांक hash = name->hash;
	स्थिर अचिन्हित अक्षर *str = name->name;
	काष्ठा list_head *p, *head;

	head = &sbi->expiring_list;
	अगर (list_empty(head))
		वापस शून्य;
	spin_lock(&sbi->lookup_lock);
	list_क्रम_each(p, head) अणु
		काष्ठा स्वतःfs_info *ino;
		काष्ठा dentry *expiring;
		स्थिर काष्ठा qstr *qstr;

		अगर (rcu_walk) अणु
			spin_unlock(&sbi->lookup_lock);
			वापस ERR_PTR(-ECHILD);
		पूर्ण

		ino = list_entry(p, काष्ठा स्वतःfs_info, expiring);
		expiring = ino->dentry;

		spin_lock(&expiring->d_lock);

		/* We've alपढ़ोy been dentry_iput or unlinked */
		अगर (d_really_is_negative(expiring))
			जाओ next;

		qstr = &expiring->d_name;

		अगर (expiring->d_name.hash != hash)
			जाओ next;
		अगर (expiring->d_parent != parent)
			जाओ next;

		अगर (qstr->len != len)
			जाओ next;
		अगर (स_भेद(qstr->name, str, len))
			जाओ next;

		अगर (d_unhashed(expiring)) अणु
			dget_dlock(expiring);
			spin_unlock(&expiring->d_lock);
			spin_unlock(&sbi->lookup_lock);
			वापस expiring;
		पूर्ण
next:
		spin_unlock(&expiring->d_lock);
	पूर्ण
	spin_unlock(&sbi->lookup_lock);

	वापस शून्य;
पूर्ण

अटल पूर्णांक स्वतःfs_mount_रुको(स्थिर काष्ठा path *path, bool rcu_walk)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(path->dentry->d_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(path->dentry);
	पूर्णांक status = 0;

	अगर (ino->flags & AUTOFS_INF_PENDING) अणु
		अगर (rcu_walk)
			वापस -ECHILD;
		pr_debug("waiting for mount name=%pd\n", path->dentry);
		status = स्वतःfs_रुको(sbi, path, NFY_MOUNT);
		pr_debug("mount wait done status=%d\n", status);
		ino->last_used = jअगरfies;
		वापस status;
	पूर्ण
	अगर (!(sbi->flags & AUTOFS_SBI_STRICTEXPIRE))
		ino->last_used = jअगरfies;
	वापस status;
पूर्ण

अटल पूर्णांक करो_expire_रुको(स्थिर काष्ठा path *path, bool rcu_walk)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा dentry *expiring;

	expiring = स्वतःfs_lookup_expiring(dentry, rcu_walk);
	अगर (IS_ERR(expiring))
		वापस PTR_ERR(expiring);
	अगर (!expiring)
		वापस स्वतःfs_expire_रुको(path, rcu_walk);
	अन्यथा अणु
		स्थिर काष्ठा path this = अणु .mnt = path->mnt, .dentry = expiring पूर्ण;
		/*
		 * If we are racing with expire the request might not
		 * be quite complete, but the directory has been हटाओd
		 * so it must have been successful, just रुको क्रम it.
		 */
		स्वतःfs_expire_रुको(&this, 0);
		स्वतःfs_del_expiring(expiring);
		dput(expiring);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा dentry *स्वतःfs_mountpoपूर्णांक_changed(काष्ठा path *path)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);

	/*
	 * If this is an indirect mount the dentry could have gone away
	 * as a result of an expire and a new one created.
	 */
	अगर (स्वतःfs_type_indirect(sbi->type) && d_unhashed(dentry)) अणु
		काष्ठा dentry *parent = dentry->d_parent;
		काष्ठा स्वतःfs_info *ino;
		काष्ठा dentry *new;

		new = d_lookup(parent, &dentry->d_name);
		अगर (!new)
			वापस शून्य;
		ino = स्वतःfs_dentry_ino(new);
		ino->last_used = jअगरfies;
		dput(path->dentry);
		path->dentry = new;
	पूर्ण
	वापस path->dentry;
पूर्ण

अटल काष्ठा vfsmount *स्वतःfs_d_स्वतःmount(काष्ठा path *path)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);
	पूर्णांक status;

	pr_debug("dentry=%p %pd\n", dentry, dentry);

	/* The daemon never triggers a mount. */
	अगर (स्वतःfs_oz_mode(sbi))
		वापस शून्य;

	/*
	 * If an expire request is pending everyone must रुको.
	 * If the expire fails we're still mounted so जारी
	 * the follow and वापस. A वापस of -EAGAIN (which only
	 * happens with indirect mounts) means the expire completed
	 * and the directory was हटाओd, so just go ahead and try
	 * the mount.
	 */
	status = करो_expire_रुको(path, 0);
	अगर (status && status != -EAGAIN)
		वापस शून्य;

	/* Callback to the daemon to perक्रमm the mount or रुको */
	spin_lock(&sbi->fs_lock);
	अगर (ino->flags & AUTOFS_INF_PENDING) अणु
		spin_unlock(&sbi->fs_lock);
		status = स्वतःfs_mount_रुको(path, 0);
		अगर (status)
			वापस ERR_PTR(status);
		जाओ करोne;
	पूर्ण

	/*
	 * If the dentry is a symlink it's equivalent to a directory
	 * having path_is_mountpoपूर्णांक() true, so there's no need to call
	 * back to the daemon.
	 */
	अगर (d_really_is_positive(dentry) && d_is_symlink(dentry)) अणु
		spin_unlock(&sbi->fs_lock);
		जाओ करोne;
	पूर्ण

	अगर (!path_is_mountpoपूर्णांक(path)) अणु
		/*
		 * It's possible that user space hasn't हटाओd directories
		 * after umounting a rootless multi-mount, although it
		 * should. For v5 path_has_submounts() is sufficient to
		 * handle this because the leaves of the directory tree under
		 * the mount never trigger mounts themselves (they have an
		 * स्वतःfs trigger mount mounted on them). But v4 pseuकरो direct
		 * mounts करो need the leaves to trigger mounts. In this हाल
		 * we have no choice but to use the list_empty() check and
		 * require user space behave.
		 */
		अगर (sbi->version > 4) अणु
			अगर (path_has_submounts(path)) अणु
				spin_unlock(&sbi->fs_lock);
				जाओ करोne;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!simple_empty(dentry)) अणु
				spin_unlock(&sbi->fs_lock);
				जाओ करोne;
			पूर्ण
		पूर्ण
		ino->flags |= AUTOFS_INF_PENDING;
		spin_unlock(&sbi->fs_lock);
		status = स्वतःfs_mount_रुको(path, 0);
		spin_lock(&sbi->fs_lock);
		ino->flags &= ~AUTOFS_INF_PENDING;
		अगर (status) अणु
			spin_unlock(&sbi->fs_lock);
			वापस ERR_PTR(status);
		पूर्ण
	पूर्ण
	spin_unlock(&sbi->fs_lock);
करोne:
	/* Mount succeeded, check अगर we ended up with a new dentry */
	dentry = स्वतःfs_mountpoपूर्णांक_changed(path);
	अगर (!dentry)
		वापस ERR_PTR(-ENOENT);

	वापस शून्य;
पूर्ण

अटल पूर्णांक स्वतःfs_d_manage(स्थिर काष्ठा path *path, bool rcu_walk)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);
	पूर्णांक status;

	pr_debug("dentry=%p %pd\n", dentry, dentry);

	/* The daemon never रुकोs. */
	अगर (स्वतःfs_oz_mode(sbi)) अणु
		अगर (!path_is_mountpoपूर्णांक(path))
			वापस -EISसूची;
		वापस 0;
	पूर्ण

	/* Wait क्रम pending expires */
	अगर (करो_expire_रुको(path, rcu_walk) == -ECHILD)
		वापस -ECHILD;

	/*
	 * This dentry may be under स्थिरruction so रुको on mount
	 * completion.
	 */
	status = स्वतःfs_mount_रुको(path, rcu_walk);
	अगर (status)
		वापस status;

	अगर (rcu_walk) अणु
		/* We करोn't need fs_lock in rcu_walk mode,
		 * just testing 'AUTOFS_INFO_NO_RCU' is enough.
		 * simple_empty() takes a spinlock, so leave it
		 * to last.
		 * We only वापस -EISसूची when certain this isn't
		 * a mount-trap.
		 */
		काष्ठा inode *inode;

		अगर (ino->flags & AUTOFS_INF_WANT_EXPIRE)
			वापस 0;
		अगर (path_is_mountpoपूर्णांक(path))
			वापस 0;
		inode = d_inode_rcu(dentry);
		अगर (inode && S_ISLNK(inode->i_mode))
			वापस -EISसूची;
		अगर (list_empty(&dentry->d_subdirs))
			वापस 0;
		अगर (!simple_empty(dentry))
			वापस -EISसूची;
		वापस 0;
	पूर्ण

	spin_lock(&sbi->fs_lock);
	/*
	 * If the dentry has been selected क्रम expire जबतक we slept
	 * on the lock then it might go away. We'll deal with that in
	 * ->d_स्वतःmount() and रुको on a new mount अगर the expire
	 * succeeds or वापस here अगर it करोesn't (since there's no
	 * mount to follow with a rootless multi-mount).
	 */
	अगर (!(ino->flags & AUTOFS_INF_EXPIRING)) अणु
		/*
		 * Any needed mounting has been completed and the path
		 * updated so check अगर this is a rootless multi-mount so
		 * we can aव्योम needless calls ->d_स्वतःmount() and aव्योम
		 * an incorrect ELOOP error वापस.
		 */
		अगर ((!path_is_mountpoपूर्णांक(path) && !simple_empty(dentry)) ||
		    (d_really_is_positive(dentry) && d_is_symlink(dentry)))
			status = -EISसूची;
	पूर्ण
	spin_unlock(&sbi->fs_lock);

	वापस status;
पूर्ण

/* Lookups in the root directory */
अटल काष्ठा dentry *स्वतःfs_lookup(काष्ठा inode *dir,
				    काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा स्वतःfs_sb_info *sbi;
	काष्ठा स्वतःfs_info *ino;
	काष्ठा dentry *active;

	pr_debug("name = %pd\n", dentry);

	/* File name too दीर्घ to exist */
	अगर (dentry->d_name.len > NAME_MAX)
		वापस ERR_PTR(-ENAMETOOLONG);

	sbi = स्वतःfs_sbi(dir->i_sb);

	pr_debug("pid = %u, pgrp = %u, catatonic = %d, oz_mode = %d\n",
		 current->pid, task_pgrp_nr(current),
		 sbi->flags & AUTOFS_SBI_CATATONIC,
		 स्वतःfs_oz_mode(sbi));

	active = स्वतःfs_lookup_active(dentry);
	अगर (active)
		वापस active;
	अन्यथा अणु
		/*
		 * A dentry that is not within the root can never trigger a
		 * mount operation, unless the directory alपढ़ोy exists, so we
		 * can वापस fail immediately.  The daemon however करोes need
		 * to create directories within the file प्रणाली.
		 */
		अगर (!स्वतःfs_oz_mode(sbi) && !IS_ROOT(dentry->d_parent))
			वापस ERR_PTR(-ENOENT);

		ino = स्वतःfs_new_ino(sbi);
		अगर (!ino)
			वापस ERR_PTR(-ENOMEM);

		spin_lock(&sbi->lookup_lock);
		spin_lock(&dentry->d_lock);
		/* Mark entries in the root as mount triggers */
		अगर (IS_ROOT(dentry->d_parent) &&
		    स्वतःfs_type_indirect(sbi->type))
			__managed_dentry_set_managed(dentry);
		dentry->d_fsdata = ino;
		ino->dentry = dentry;

		list_add(&ino->active, &sbi->active_list);
		spin_unlock(&sbi->lookup_lock);
		spin_unlock(&dentry->d_lock);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक स्वतःfs_dir_symlink(काष्ठा user_namespace *mnt_userns,
			      काष्ठा inode *dir, काष्ठा dentry *dentry,
			      स्थिर अक्षर *symname)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dir->i_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);
	काष्ठा स्वतःfs_info *p_ino;
	काष्ठा inode *inode;
	माप_प्रकार size = म_माप(symname);
	अक्षर *cp;

	pr_debug("%s <- %pd\n", symname, dentry);

	अगर (!स्वतःfs_oz_mode(sbi))
		वापस -EACCES;

	/* स्वतःfs_oz_mode() needs to allow path walks when the
	 * स्वतःfs mount is catatonic but the state of an स्वतःfs
	 * file प्रणाली needs to be preserved over restarts.
	 */
	अगर (sbi->flags & AUTOFS_SBI_CATATONIC)
		वापस -EACCES;

	BUG_ON(!ino);

	स्वतःfs_clean_ino(ino);

	स्वतःfs_del_active(dentry);

	cp = kदो_स्मृति(size + 1, GFP_KERNEL);
	अगर (!cp)
		वापस -ENOMEM;

	म_नकल(cp, symname);

	inode = स्वतःfs_get_inode(dir->i_sb, S_IFLNK | 0555);
	अगर (!inode) अणु
		kमुक्त(cp);
		वापस -ENOMEM;
	पूर्ण
	inode->i_निजी = cp;
	inode->i_size = size;
	d_add(dentry, inode);

	dget(dentry);
	ino->count++;
	p_ino = स्वतःfs_dentry_ino(dentry->d_parent);
	p_ino->count++;

	dir->i_mसमय = current_समय(dir);

	वापस 0;
पूर्ण

/*
 * NOTE!
 *
 * Normal fileप्रणालीs would करो a "d_delete()" to tell the VFS dcache
 * that the file no दीर्घer exists. However, करोing that means that the
 * VFS layer can turn the dentry पूर्णांकo a negative dentry.  We करोn't want
 * this, because the unlink is probably the result of an expire.
 * We simply d_drop it and add it to a expiring list in the super block,
 * which allows the dentry lookup to check क्रम an incomplete expire.
 *
 * If a process is blocked on the dentry रुकोing क्रम the expire to finish,
 * it will invalidate the dentry and try to mount with a new one.
 *
 * Also see स्वतःfs_dir_सूची_हटाओ()..
 */
अटल पूर्णांक स्वतःfs_dir_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dir->i_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);
	काष्ठा स्वतःfs_info *p_ino;

	अगर (!स्वतःfs_oz_mode(sbi))
		वापस -EACCES;

	/* स्वतःfs_oz_mode() needs to allow path walks when the
	 * स्वतःfs mount is catatonic but the state of an स्वतःfs
	 * file प्रणाली needs to be preserved over restarts.
	 */
	अगर (sbi->flags & AUTOFS_SBI_CATATONIC)
		वापस -EACCES;

	ino->count--;
	p_ino = स्वतःfs_dentry_ino(dentry->d_parent);
	p_ino->count--;
	dput(ino->dentry);

	d_inode(dentry)->i_size = 0;
	clear_nlink(d_inode(dentry));

	dir->i_mसमय = current_समय(dir);

	spin_lock(&sbi->lookup_lock);
	__स्वतःfs_add_expiring(dentry);
	d_drop(dentry);
	spin_unlock(&sbi->lookup_lock);

	वापस 0;
पूर्ण

/*
 * Version 4 of स्वतःfs provides a pseuकरो direct mount implementation
 * that relies on directories at the leaves of a directory tree under
 * an indirect mount to trigger mounts. To allow क्रम this we need to
 * set the DMANAGED_AUTOMOUNT and DMANAGED_TRANSIT flags on the leaves
 * of the directory tree. There is no need to clear the स्वतःmount flag
 * following a mount or restore it after an expire because these mounts
 * are always covered. However, it is necessary to ensure that these
 * flags are clear on non-empty directories to aव्योम unnecessary calls
 * during path walks.
 */
अटल व्योम स्वतःfs_set_leaf_स्वतःmount_flags(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *parent;

	/* root and dentrys in the root are alपढ़ोy handled */
	अगर (IS_ROOT(dentry->d_parent))
		वापस;

	managed_dentry_set_managed(dentry);

	parent = dentry->d_parent;
	/* only consider parents below dentrys in the root */
	अगर (IS_ROOT(parent->d_parent))
		वापस;
	managed_dentry_clear_managed(parent);
पूर्ण

अटल व्योम स्वतःfs_clear_leaf_स्वतःmount_flags(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *parent;

	/* flags क्रम dentrys in the root are handled अन्यथाwhere */
	अगर (IS_ROOT(dentry->d_parent))
		वापस;

	managed_dentry_clear_managed(dentry);

	parent = dentry->d_parent;
	/* only consider parents below dentrys in the root */
	अगर (IS_ROOT(parent->d_parent))
		वापस;
	अगर (स्वतःfs_dentry_ino(parent)->count == 2)
		managed_dentry_set_managed(parent);
पूर्ण

अटल पूर्णांक स्वतःfs_dir_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dir->i_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);
	काष्ठा स्वतःfs_info *p_ino;

	pr_debug("dentry %p, removing %pd\n", dentry, dentry);

	अगर (!स्वतःfs_oz_mode(sbi))
		वापस -EACCES;

	/* स्वतःfs_oz_mode() needs to allow path walks when the
	 * स्वतःfs mount is catatonic but the state of an स्वतःfs
	 * file प्रणाली needs to be preserved over restarts.
	 */
	अगर (sbi->flags & AUTOFS_SBI_CATATONIC)
		वापस -EACCES;

	अगर (ino->count != 1)
		वापस -ENOTEMPTY;

	spin_lock(&sbi->lookup_lock);
	__स्वतःfs_add_expiring(dentry);
	d_drop(dentry);
	spin_unlock(&sbi->lookup_lock);

	अगर (sbi->version < 5)
		स्वतःfs_clear_leaf_स्वतःmount_flags(dentry);

	ino->count--;
	p_ino = स्वतःfs_dentry_ino(dentry->d_parent);
	p_ino->count--;
	dput(ino->dentry);
	d_inode(dentry)->i_size = 0;
	clear_nlink(d_inode(dentry));

	अगर (dir->i_nlink)
		drop_nlink(dir);

	वापस 0;
पूर्ण

अटल पूर्णांक स्वतःfs_dir_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *dir, काष्ठा dentry *dentry,
			    umode_t mode)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dir->i_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);
	काष्ठा स्वतःfs_info *p_ino;
	काष्ठा inode *inode;

	अगर (!स्वतःfs_oz_mode(sbi))
		वापस -EACCES;

	/* स्वतःfs_oz_mode() needs to allow path walks when the
	 * स्वतःfs mount is catatonic but the state of an स्वतःfs
	 * file प्रणाली needs to be preserved over restarts.
	 */
	अगर (sbi->flags & AUTOFS_SBI_CATATONIC)
		वापस -EACCES;

	pr_debug("dentry %p, creating %pd\n", dentry, dentry);

	BUG_ON(!ino);

	स्वतःfs_clean_ino(ino);

	स्वतःfs_del_active(dentry);

	inode = स्वतःfs_get_inode(dir->i_sb, S_IFसूची | mode);
	अगर (!inode)
		वापस -ENOMEM;
	d_add(dentry, inode);

	अगर (sbi->version < 5)
		स्वतःfs_set_leaf_स्वतःmount_flags(dentry);

	dget(dentry);
	ino->count++;
	p_ino = स्वतःfs_dentry_ino(dentry->d_parent);
	p_ino->count++;
	inc_nlink(dir);
	dir->i_mसमय = current_समय(dir);

	वापस 0;
पूर्ण

/* Get/set समयout ioctl() operation */
#अगर_घोषित CONFIG_COMPAT
अटल अंतरभूत पूर्णांक स्वतःfs_compat_get_set_समयout(काष्ठा स्वतःfs_sb_info *sbi,
						 compat_uदीर्घ_t __user *p)
अणु
	अचिन्हित दीर्घ nसमयout;
	पूर्णांक rv;

	rv = get_user(nसमयout, p);
	अगर (rv)
		जाओ error;

	rv = put_user(sbi->exp_समयout/HZ, p);
	अगर (rv)
		जाओ error;

	अगर (nसमयout > अच_पूर्णांक_उच्च/HZ)
		sbi->exp_समयout = 0;
	अन्यथा
		sbi->exp_समयout = nसमयout * HZ;

	वापस 0;
error:
	वापस rv;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक स्वतःfs_get_set_समयout(काष्ठा स्वतःfs_sb_info *sbi,
					  अचिन्हित दीर्घ __user *p)
अणु
	अचिन्हित दीर्घ nसमयout;
	पूर्णांक rv;

	rv = get_user(nसमयout, p);
	अगर (rv)
		जाओ error;

	rv = put_user(sbi->exp_समयout/HZ, p);
	अगर (rv)
		जाओ error;

	अगर (nसमयout > अच_दीर्घ_उच्च/HZ)
		sbi->exp_समयout = 0;
	अन्यथा
		sbi->exp_समयout = nसमयout * HZ;

	वापस 0;
error:
	वापस rv;
पूर्ण

/* Return protocol version */
अटल अंतरभूत पूर्णांक स्वतःfs_get_protover(काष्ठा स्वतःfs_sb_info *sbi,
				       पूर्णांक __user *p)
अणु
	वापस put_user(sbi->version, p);
पूर्ण

/* Return protocol sub version */
अटल अंतरभूत पूर्णांक स्वतःfs_get_protosubver(काष्ठा स्वतःfs_sb_info *sbi,
					  पूर्णांक __user *p)
अणु
	वापस put_user(sbi->sub_version, p);
पूर्ण

/*
* Tells the daemon whether it can umount the स्वतःfs mount.
*/
अटल अंतरभूत पूर्णांक स्वतःfs_ask_umount(काष्ठा vfsmount *mnt, पूर्णांक __user *p)
अणु
	पूर्णांक status = 0;

	अगर (may_umount(mnt))
		status = 1;

	pr_debug("may umount %d\n", status);

	status = put_user(status, p);

	वापस status;
पूर्ण

/* Identअगरy स्वतःfs_dentries - this is so we can tell अगर there's
 * an extra dentry refcount or not.  We only hold a refcount on the
 * dentry अगर its non-negative (ie, d_inode != शून्य)
 */
पूर्णांक is_स्वतःfs_dentry(काष्ठा dentry *dentry)
अणु
	वापस dentry && d_really_is_positive(dentry) &&
		dentry->d_op == &स्वतःfs_dentry_operations &&
		dentry->d_fsdata != शून्य;
पूर्ण

/*
 * ioctl()'s on the root directory is the chief method क्रम the daemon to
 * generate kernel reactions
 */
अटल पूर्णांक स्वतःfs_root_ioctl_unlocked(काष्ठा inode *inode, काष्ठा file *filp,
				       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(inode->i_sb);
	व्योम __user *p = (व्योम __user *)arg;

	pr_debug("cmd = 0x%08x, arg = 0x%08lx, sbi = %p, pgrp = %u\n",
		 cmd, arg, sbi, task_pgrp_nr(current));

	अगर (_IOC_TYPE(cmd) != _IOC_TYPE(AUTOFS_IOC_FIRST) ||
	     _IOC_NR(cmd) - _IOC_NR(AUTOFS_IOC_FIRST) >= AUTOFS_IOC_COUNT)
		वापस -ENOTTY;

	अगर (!स्वतःfs_oz_mode(sbi) && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल AUTOFS_IOC_READY:	/* Wait queue: go ahead and retry */
		वापस स्वतःfs_रुको_release(sbi, (स्वतःfs_wqt_t) arg, 0);
	हाल AUTOFS_IOC_FAIL:	/* Wait queue: fail with ENOENT */
		वापस स्वतःfs_रुको_release(sbi, (स्वतःfs_wqt_t) arg, -ENOENT);
	हाल AUTOFS_IOC_CATATONIC: /* Enter catatonic mode (daemon shutकरोwn) */
		स्वतःfs_catatonic_mode(sbi);
		वापस 0;
	हाल AUTOFS_IOC_PROTOVER: /* Get protocol version */
		वापस स्वतःfs_get_protover(sbi, p);
	हाल AUTOFS_IOC_PROTOSUBVER: /* Get protocol sub version */
		वापस स्वतःfs_get_protosubver(sbi, p);
	हाल AUTOFS_IOC_SETTIMEOUT:
		वापस स्वतःfs_get_set_समयout(sbi, p);
#अगर_घोषित CONFIG_COMPAT
	हाल AUTOFS_IOC_SETTIMEOUT32:
		वापस स्वतःfs_compat_get_set_समयout(sbi, p);
#पूर्ण_अगर

	हाल AUTOFS_IOC_ASKUMOUNT:
		वापस स्वतःfs_ask_umount(filp->f_path.mnt, p);

	/* वापस a single thing to expire */
	हाल AUTOFS_IOC_EXPIRE:
		वापस स्वतःfs_expire_run(inode->i_sb, filp->f_path.mnt, sbi, p);
	/* same as above, but can send multiple expires through pipe */
	हाल AUTOFS_IOC_EXPIRE_MULTI:
		वापस स्वतःfs_expire_multi(inode->i_sb,
					   filp->f_path.mnt, sbi, p);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल दीर्घ स्वतःfs_root_ioctl(काष्ठा file *filp,
			       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);

	वापस स्वतःfs_root_ioctl_unlocked(inode, filp, cmd, arg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ स्वतःfs_root_compat_ioctl(काष्ठा file *filp,
				      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक ret;

	अगर (cmd == AUTOFS_IOC_READY || cmd == AUTOFS_IOC_FAIL)
		ret = स्वतःfs_root_ioctl_unlocked(inode, filp, cmd, arg);
	अन्यथा
		ret = स्वतःfs_root_ioctl_unlocked(inode, filp, cmd,
					      (अचिन्हित दीर्घ) compat_ptr(arg));

	वापस ret;
पूर्ण
#पूर्ण_अगर
