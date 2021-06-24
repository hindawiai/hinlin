<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved
 * Copyright 1999-2000 Jeremy Fitzhardinge <jeremy@goop.org>
 * Copyright 2001-2006 Ian Kent <raven@themaw.net>
 */

#समावेश "autofs_i.h"

/* Check अगर a dentry can be expired */
अटल अंतरभूत पूर्णांक स्वतःfs_can_expire(काष्ठा dentry *dentry,
				    अचिन्हित दीर्घ समयout, अचिन्हित पूर्णांक how)
अणु
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);

	/* dentry in the process of being deleted */
	अगर (ino == शून्य)
		वापस 0;

	अगर (!(how & AUTOFS_EXP_IMMEDIATE)) अणु
		/* Too young to die */
		अगर (!समयout || समय_after(ino->last_used + समयout, jअगरfies))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/* Check a mount poपूर्णांक क्रम busyness */
अटल पूर्णांक स्वतःfs_mount_busy(काष्ठा vfsmount *mnt,
			     काष्ठा dentry *dentry, अचिन्हित पूर्णांक how)
अणु
	काष्ठा dentry *top = dentry;
	काष्ठा path path = अणु.mnt = mnt, .dentry = dentryपूर्ण;
	पूर्णांक status = 1;

	pr_debug("dentry %p %pd\n", dentry, dentry);

	path_get(&path);

	अगर (!follow_करोwn_one(&path))
		जाओ करोne;

	अगर (is_स्वतःfs_dentry(path.dentry)) अणु
		काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(path.dentry->d_sb);

		/* This is an स्वतःfs submount, we can't expire it */
		अगर (स्वतःfs_type_indirect(sbi->type))
			जाओ करोne;
	पूर्ण

	/* Not a submount, has a क्रमced expire been requested */
	अगर (how & AUTOFS_EXP_FORCED) अणु
		status = 0;
		जाओ करोne;
	पूर्ण

	/* Update the expiry counter अगर fs is busy */
	अगर (!may_umount_tree(path.mnt)) अणु
		काष्ठा स्वतःfs_info *ino;

		ino = स्वतःfs_dentry_ino(top);
		ino->last_used = jअगरfies;
		जाओ करोne;
	पूर्ण

	status = 0;
करोne:
	pr_debug("returning = %d\n", status);
	path_put(&path);
	वापस status;
पूर्ण

/* p->d_lock held */
अटल काष्ठा dentry *positive_after(काष्ठा dentry *p, काष्ठा dentry *child)
अणु
	अगर (child)
		child = list_next_entry(child, d_child);
	अन्यथा
		child = list_first_entry(&p->d_subdirs, काष्ठा dentry, d_child);

	list_क्रम_each_entry_from(child, &p->d_subdirs, d_child) अणु
		spin_lock_nested(&child->d_lock, DENTRY_D_LOCK_NESTED);
		अगर (simple_positive(child)) अणु
			dget_dlock(child);
			spin_unlock(&child->d_lock);
			वापस child;
		पूर्ण
		spin_unlock(&child->d_lock);
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Calculate and dget next entry in the subdirs list under root.
 */
अटल काष्ठा dentry *get_next_positive_subdir(काष्ठा dentry *prev,
					       काष्ठा dentry *root)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(root->d_sb);
	काष्ठा dentry *q;

	spin_lock(&sbi->lookup_lock);
	spin_lock(&root->d_lock);
	q = positive_after(root, prev);
	spin_unlock(&root->d_lock);
	spin_unlock(&sbi->lookup_lock);
	dput(prev);
	वापस q;
पूर्ण

/*
 * Calculate and dget next entry in top करोwn tree traversal.
 */
अटल काष्ठा dentry *get_next_positive_dentry(काष्ठा dentry *prev,
					       काष्ठा dentry *root)
अणु
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(root->d_sb);
	काष्ठा dentry *p = prev, *ret = शून्य, *d = शून्य;

	अगर (prev == शून्य)
		वापस dget(root);

	spin_lock(&sbi->lookup_lock);
	spin_lock(&p->d_lock);
	जबतक (1) अणु
		काष्ठा dentry *parent;

		ret = positive_after(p, d);
		अगर (ret || p == root)
			अवरोध;
		parent = p->d_parent;
		spin_unlock(&p->d_lock);
		spin_lock(&parent->d_lock);
		d = p;
		p = parent;
	पूर्ण
	spin_unlock(&p->d_lock);
	spin_unlock(&sbi->lookup_lock);
	dput(prev);
	वापस ret;
पूर्ण

/*
 * Check a direct mount poपूर्णांक क्रम busyness.
 * Direct mounts have similar expiry semantics to tree mounts.
 * The tree is not busy अगरf no mountpoपूर्णांकs are busy and there are no
 * स्वतःfs submounts.
 */
अटल पूर्णांक स्वतःfs_direct_busy(काष्ठा vfsmount *mnt,
			      काष्ठा dentry *top,
			      अचिन्हित दीर्घ समयout,
			      अचिन्हित पूर्णांक how)
अणु
	pr_debug("top %p %pd\n", top, top);

	/* Forced expire, user space handles busy mounts */
	अगर (how & AUTOFS_EXP_FORCED)
		वापस 0;

	/* If it's busy update the expiry counters */
	अगर (!may_umount_tree(mnt)) अणु
		काष्ठा स्वतःfs_info *ino;

		ino = स्वतःfs_dentry_ino(top);
		अगर (ino)
			ino->last_used = jअगरfies;
		वापस 1;
	पूर्ण

	/* Timeout of a direct mount is determined by its top dentry */
	अगर (!स्वतःfs_can_expire(top, समयout, how))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * Check a directory tree of mount poपूर्णांकs क्रम busyness
 * The tree is not busy अगरf no mountpoपूर्णांकs are busy
 */
अटल पूर्णांक स्वतःfs_tree_busy(काष्ठा vfsmount *mnt,
			    काष्ठा dentry *top,
			    अचिन्हित दीर्घ समयout,
			    अचिन्हित पूर्णांक how)
अणु
	काष्ठा स्वतःfs_info *top_ino = स्वतःfs_dentry_ino(top);
	काष्ठा dentry *p;

	pr_debug("top %p %pd\n", top, top);

	/* Negative dentry - give up */
	अगर (!simple_positive(top))
		वापस 1;

	p = शून्य;
	जबतक ((p = get_next_positive_dentry(p, top))) अणु
		pr_debug("dentry %p %pd\n", p, p);

		/*
		 * Is someone visiting anywhere in the subtree ?
		 * If there's no mount we need to check the usage
		 * count क्रम the स्वतःfs dentry.
		 * If the fs is busy update the expiry counter.
		 */
		अगर (d_mountpoपूर्णांक(p)) अणु
			अगर (स्वतःfs_mount_busy(mnt, p, how)) अणु
				top_ino->last_used = jअगरfies;
				dput(p);
				वापस 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(p);
			अचिन्हित पूर्णांक ino_count = READ_ONCE(ino->count);

			/* allow क्रम dget above and top is alपढ़ोy dgot */
			अगर (p == top)
				ino_count += 2;
			अन्यथा
				ino_count++;

			अगर (d_count(p) > ino_count) अणु
				top_ino->last_used = jअगरfies;
				dput(p);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Forced expire, user space handles busy mounts */
	अगर (how & AUTOFS_EXP_FORCED)
		वापस 0;

	/* Timeout of a tree mount is ultimately determined by its top dentry */
	अगर (!स्वतःfs_can_expire(top, समयout, how))
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा dentry *स्वतःfs_check_leaves(काष्ठा vfsmount *mnt,
					  काष्ठा dentry *parent,
					  अचिन्हित दीर्घ समयout,
					  अचिन्हित पूर्णांक how)
अणु
	काष्ठा dentry *p;

	pr_debug("parent %p %pd\n", parent, parent);

	p = शून्य;
	जबतक ((p = get_next_positive_dentry(p, parent))) अणु
		pr_debug("dentry %p %pd\n", p, p);

		अगर (d_mountpoपूर्णांक(p)) अणु
			/* Can we umount this guy */
			अगर (स्वतःfs_mount_busy(mnt, p, how))
				जारी;

			/* This isn't a submount so अगर a क्रमced expire
			 * has been requested, user space handles busy
			 * mounts */
			अगर (how & AUTOFS_EXP_FORCED)
				वापस p;

			/* Can we expire this guy */
			अगर (स्वतःfs_can_expire(p, समयout, how))
				वापस p;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* Check अगर we can expire a direct mount (possibly a tree) */
अटल काष्ठा dentry *स्वतःfs_expire_direct(काष्ठा super_block *sb,
					   काष्ठा vfsmount *mnt,
					   काष्ठा स्वतःfs_sb_info *sbi,
					   अचिन्हित पूर्णांक how)
अणु
	काष्ठा dentry *root = dget(sb->s_root);
	काष्ठा स्वतःfs_info *ino;
	अचिन्हित दीर्घ समयout;

	अगर (!root)
		वापस शून्य;

	समयout = sbi->exp_समयout;

	अगर (!स्वतःfs_direct_busy(mnt, root, समयout, how)) अणु
		spin_lock(&sbi->fs_lock);
		ino = स्वतःfs_dentry_ino(root);
		/* No poपूर्णांक expiring a pending mount */
		अगर (ino->flags & AUTOFS_INF_PENDING) अणु
			spin_unlock(&sbi->fs_lock);
			जाओ out;
		पूर्ण
		ino->flags |= AUTOFS_INF_WANT_EXPIRE;
		spin_unlock(&sbi->fs_lock);
		synchronize_rcu();
		अगर (!स्वतःfs_direct_busy(mnt, root, समयout, how)) अणु
			spin_lock(&sbi->fs_lock);
			ino->flags |= AUTOFS_INF_EXPIRING;
			init_completion(&ino->expire_complete);
			spin_unlock(&sbi->fs_lock);
			वापस root;
		पूर्ण
		spin_lock(&sbi->fs_lock);
		ino->flags &= ~AUTOFS_INF_WANT_EXPIRE;
		spin_unlock(&sbi->fs_lock);
	पूर्ण
out:
	dput(root);

	वापस शून्य;
पूर्ण

/* Check अगर 'dentry' should expire, or वापस a nearby
 * dentry that is suitable.
 * If वापसed dentry is dअगरferent from arg dentry,
 * then a dget() reference was taken, अन्यथा not.
 */
अटल काष्ठा dentry *should_expire(काष्ठा dentry *dentry,
				    काष्ठा vfsmount *mnt,
				    अचिन्हित दीर्घ समयout,
				    अचिन्हित पूर्णांक how)
अणु
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);
	अचिन्हित पूर्णांक ino_count;

	/* No poपूर्णांक expiring a pending mount */
	अगर (ino->flags & AUTOFS_INF_PENDING)
		वापस शून्य;

	/*
	 * Case 1: (i) indirect mount or top level pseuकरो direct mount
	 *	   (स्वतःfs-4.1).
	 *	   (ii) indirect mount with offset mount, check the "/"
	 *	   offset (स्वतःfs-5.0+).
	 */
	अगर (d_mountpoपूर्णांक(dentry)) अणु
		pr_debug("checking mountpoint %p %pd\n", dentry, dentry);

		/* Can we umount this guy */
		अगर (स्वतःfs_mount_busy(mnt, dentry, how))
			वापस शून्य;

		/* This isn't a submount so अगर a क्रमced expire
		 * has been requested, user space handles busy
		 * mounts */
		अगर (how & AUTOFS_EXP_FORCED)
			वापस dentry;

		/* Can we expire this guy */
		अगर (स्वतःfs_can_expire(dentry, समयout, how))
			वापस dentry;
		वापस शून्य;
	पूर्ण

	अगर (d_is_symlink(dentry)) अणु
		pr_debug("checking symlink %p %pd\n", dentry, dentry);

		/* Forced expire, user space handles busy mounts */
		अगर (how & AUTOFS_EXP_FORCED)
			वापस dentry;

		/*
		 * A symlink can't be "busy" in the usual sense so
		 * just check last used क्रम expire समयout.
		 */
		अगर (स्वतःfs_can_expire(dentry, समयout, how))
			वापस dentry;
		वापस शून्य;
	पूर्ण

	अगर (simple_empty(dentry))
		वापस शून्य;

	/* Case 2: tree mount, expire अगरf entire tree is not busy */
	अगर (!(how & AUTOFS_EXP_LEAVES)) अणु
		/* Not a क्रमced expire? */
		अगर (!(how & AUTOFS_EXP_FORCED)) अणु
			/* ref-walk currently on this dentry? */
			ino_count = READ_ONCE(ino->count) + 1;
			अगर (d_count(dentry) > ino_count)
				वापस शून्य;
		पूर्ण

		अगर (!स्वतःfs_tree_busy(mnt, dentry, समयout, how))
			वापस dentry;
	/*
	 * Case 3: pseuकरो direct mount, expire inभागidual leaves
	 *	   (स्वतःfs-4.1).
	 */
	पूर्ण अन्यथा अणु
		काष्ठा dentry *expired;

		/* Not a क्रमced expire? */
		अगर (!(how & AUTOFS_EXP_FORCED)) अणु
			/* ref-walk currently on this dentry? */
			ino_count = READ_ONCE(ino->count) + 1;
			अगर (d_count(dentry) > ino_count)
				वापस शून्य;
		पूर्ण

		expired = स्वतःfs_check_leaves(mnt, dentry, समयout, how);
		अगर (expired) अणु
			अगर (expired == dentry)
				dput(dentry);
			वापस expired;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Find an eligible tree to समय-out
 * A tree is eligible अगर :-
 *  - it is unused by any user process
 *  - it has been unused क्रम exp_समयout समय
 */
अटल काष्ठा dentry *स्वतःfs_expire_indirect(काष्ठा super_block *sb,
					     काष्ठा vfsmount *mnt,
					     काष्ठा स्वतःfs_sb_info *sbi,
					     अचिन्हित पूर्णांक how)
अणु
	अचिन्हित दीर्घ समयout;
	काष्ठा dentry *root = sb->s_root;
	काष्ठा dentry *dentry;
	काष्ठा dentry *expired;
	काष्ठा dentry *found;
	काष्ठा स्वतःfs_info *ino;

	अगर (!root)
		वापस शून्य;

	समयout = sbi->exp_समयout;

	dentry = शून्य;
	जबतक ((dentry = get_next_positive_subdir(dentry, root))) अणु
		spin_lock(&sbi->fs_lock);
		ino = स्वतःfs_dentry_ino(dentry);
		अगर (ino->flags & AUTOFS_INF_WANT_EXPIRE) अणु
			spin_unlock(&sbi->fs_lock);
			जारी;
		पूर्ण
		spin_unlock(&sbi->fs_lock);

		expired = should_expire(dentry, mnt, समयout, how);
		अगर (!expired)
			जारी;

		spin_lock(&sbi->fs_lock);
		ino = स्वतःfs_dentry_ino(expired);
		ino->flags |= AUTOFS_INF_WANT_EXPIRE;
		spin_unlock(&sbi->fs_lock);
		synchronize_rcu();

		/* Make sure a reference is not taken on found अगर
		 * things have changed.
		 */
		how &= ~AUTOFS_EXP_LEAVES;
		found = should_expire(expired, mnt, समयout, how);
		अगर (found != expired) अणु // something has changed, जारी
			dput(found);
			जाओ next;
		पूर्ण

		अगर (expired != dentry)
			dput(dentry);

		spin_lock(&sbi->fs_lock);
		जाओ found;
next:
		spin_lock(&sbi->fs_lock);
		ino->flags &= ~AUTOFS_INF_WANT_EXPIRE;
		spin_unlock(&sbi->fs_lock);
		अगर (expired != dentry)
			dput(expired);
	पूर्ण
	वापस शून्य;

found:
	pr_debug("returning %p %pd\n", expired, expired);
	ino->flags |= AUTOFS_INF_EXPIRING;
	init_completion(&ino->expire_complete);
	spin_unlock(&sbi->fs_lock);
	वापस expired;
पूर्ण

पूर्णांक स्वतःfs_expire_रुको(स्थिर काष्ठा path *path, पूर्णांक rcu_walk)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा स्वतःfs_sb_info *sbi = स्वतःfs_sbi(dentry->d_sb);
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);
	पूर्णांक status;
	पूर्णांक state;

	/* Block on any pending expire */
	अगर (!(ino->flags & AUTOFS_INF_WANT_EXPIRE))
		वापस 0;
	अगर (rcu_walk)
		वापस -ECHILD;

retry:
	spin_lock(&sbi->fs_lock);
	state = ino->flags & (AUTOFS_INF_WANT_EXPIRE | AUTOFS_INF_EXPIRING);
	अगर (state == AUTOFS_INF_WANT_EXPIRE) अणु
		spin_unlock(&sbi->fs_lock);
		/*
		 * Possibly being selected क्रम expire, रुको until
		 * it's selected or not.
		 */
		schedule_समयout_unपूर्णांकerruptible(HZ/10);
		जाओ retry;
	पूर्ण
	अगर (state & AUTOFS_INF_EXPIRING) अणु
		spin_unlock(&sbi->fs_lock);

		pr_debug("waiting for expire %p name=%pd\n", dentry, dentry);

		status = स्वतःfs_रुको(sbi, path, NFY_NONE);
		रुको_क्रम_completion(&ino->expire_complete);

		pr_debug("expire done status=%d\n", status);

		अगर (d_unhashed(dentry))
			वापस -EAGAIN;

		वापस status;
	पूर्ण
	spin_unlock(&sbi->fs_lock);

	वापस 0;
पूर्ण

/* Perक्रमm an expiry operation */
पूर्णांक स्वतःfs_expire_run(काष्ठा super_block *sb,
		      काष्ठा vfsmount *mnt,
		      काष्ठा स्वतःfs_sb_info *sbi,
		      काष्ठा स्वतःfs_packet_expire __user *pkt_p)
अणु
	काष्ठा स्वतःfs_packet_expire pkt;
	काष्ठा स्वतःfs_info *ino;
	काष्ठा dentry *dentry;
	पूर्णांक ret = 0;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.hdr.proto_version = sbi->version;
	pkt.hdr.type = स्वतःfs_ptype_expire;

	dentry = स्वतःfs_expire_indirect(sb, mnt, sbi, 0);
	अगर (!dentry)
		वापस -EAGAIN;

	pkt.len = dentry->d_name.len;
	स_नकल(pkt.name, dentry->d_name.name, pkt.len);
	pkt.name[pkt.len] = '\0';

	अगर (copy_to_user(pkt_p, &pkt, माप(काष्ठा स्वतःfs_packet_expire)))
		ret = -EFAULT;

	spin_lock(&sbi->fs_lock);
	ino = स्वतःfs_dentry_ino(dentry);
	/* aव्योम rapid-fire expire attempts अगर expiry fails */
	ino->last_used = jअगरfies;
	ino->flags &= ~(AUTOFS_INF_EXPIRING|AUTOFS_INF_WANT_EXPIRE);
	complete_all(&ino->expire_complete);
	spin_unlock(&sbi->fs_lock);

	dput(dentry);

	वापस ret;
पूर्ण

पूर्णांक स्वतःfs_करो_expire_multi(काष्ठा super_block *sb, काष्ठा vfsmount *mnt,
			   काष्ठा स्वतःfs_sb_info *sbi, अचिन्हित पूर्णांक how)
अणु
	काष्ठा dentry *dentry;
	पूर्णांक ret = -EAGAIN;

	अगर (स्वतःfs_type_trigger(sbi->type))
		dentry = स्वतःfs_expire_direct(sb, mnt, sbi, how);
	अन्यथा
		dentry = स्वतःfs_expire_indirect(sb, mnt, sbi, how);

	अगर (dentry) अणु
		काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(dentry);
		स्थिर काष्ठा path path = अणु .mnt = mnt, .dentry = dentry पूर्ण;

		/* This is synchronous because it makes the daemon a
		 * little easier
		 */
		ret = स्वतःfs_रुको(sbi, &path, NFY_EXPIRE);

		spin_lock(&sbi->fs_lock);
		/* aव्योम rapid-fire expire attempts अगर expiry fails */
		ino->last_used = jअगरfies;
		ino->flags &= ~(AUTOFS_INF_EXPIRING|AUTOFS_INF_WANT_EXPIRE);
		complete_all(&ino->expire_complete);
		spin_unlock(&sbi->fs_lock);
		dput(dentry);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Call repeatedly until it वापसs -EAGAIN, meaning there's nothing
 * more to be करोne.
 */
पूर्णांक स्वतःfs_expire_multi(काष्ठा super_block *sb, काष्ठा vfsmount *mnt,
			काष्ठा स्वतःfs_sb_info *sbi, पूर्णांक __user *arg)
अणु
	अचिन्हित पूर्णांक how = 0;

	अगर (arg && get_user(how, arg))
		वापस -EFAULT;

	वापस स्वतःfs_करो_expire_multi(sb, mnt, sbi, how);
पूर्ण
