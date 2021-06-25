<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/pnode.c
 *
 * (C) Copyright IBM Corporation 2005.
 *	Author : Ram Pai (linuxram@us.ibm.com)
 */
#समावेश <linux/mnt_namespace.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs.h>
#समावेश <linux/nsproxy.h>
#समावेश <uapi/linux/mount.h>
#समावेश "internal.h"
#समावेश "pnode.h"

/* वापस the next shared peer mount of @p */
अटल अंतरभूत काष्ठा mount *next_peer(काष्ठा mount *p)
अणु
	वापस list_entry(p->mnt_share.next, काष्ठा mount, mnt_share);
पूर्ण

अटल अंतरभूत काष्ठा mount *first_slave(काष्ठा mount *p)
अणु
	वापस list_entry(p->mnt_slave_list.next, काष्ठा mount, mnt_slave);
पूर्ण

अटल अंतरभूत काष्ठा mount *last_slave(काष्ठा mount *p)
अणु
	वापस list_entry(p->mnt_slave_list.prev, काष्ठा mount, mnt_slave);
पूर्ण

अटल अंतरभूत काष्ठा mount *next_slave(काष्ठा mount *p)
अणु
	वापस list_entry(p->mnt_slave.next, काष्ठा mount, mnt_slave);
पूर्ण

अटल काष्ठा mount *get_peer_under_root(काष्ठा mount *mnt,
					 काष्ठा mnt_namespace *ns,
					 स्थिर काष्ठा path *root)
अणु
	काष्ठा mount *m = mnt;

	करो अणु
		/* Check the namespace first क्रम optimization */
		अगर (m->mnt_ns == ns && is_path_reachable(m, m->mnt.mnt_root, root))
			वापस m;

		m = next_peer(m);
	पूर्ण जबतक (m != mnt);

	वापस शून्य;
पूर्ण

/*
 * Get ID of बंदst करोminating peer group having a representative
 * under the given root.
 *
 * Caller must hold namespace_sem
 */
पूर्णांक get_करोminating_id(काष्ठा mount *mnt, स्थिर काष्ठा path *root)
अणु
	काष्ठा mount *m;

	क्रम (m = mnt->mnt_master; m != शून्य; m = m->mnt_master) अणु
		काष्ठा mount *d = get_peer_under_root(m, mnt->mnt_ns, root);
		अगर (d)
			वापस d->mnt_group_id;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_make_slave(काष्ठा mount *mnt)
अणु
	काष्ठा mount *master, *slave_mnt;

	अगर (list_empty(&mnt->mnt_share)) अणु
		अगर (IS_MNT_SHARED(mnt)) अणु
			mnt_release_group_id(mnt);
			CLEAR_MNT_SHARED(mnt);
		पूर्ण
		master = mnt->mnt_master;
		अगर (!master) अणु
			काष्ठा list_head *p = &mnt->mnt_slave_list;
			जबतक (!list_empty(p)) अणु
				slave_mnt = list_first_entry(p,
						काष्ठा mount, mnt_slave);
				list_del_init(&slave_mnt->mnt_slave);
				slave_mnt->mnt_master = शून्य;
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा mount *m;
		/*
		 * slave 'mnt' to a peer mount that has the
		 * same root dentry. If none is available then
		 * slave it to anything that is available.
		 */
		क्रम (m = master = next_peer(mnt); m != mnt; m = next_peer(m)) अणु
			अगर (m->mnt.mnt_root == mnt->mnt.mnt_root) अणु
				master = m;
				अवरोध;
			पूर्ण
		पूर्ण
		list_del_init(&mnt->mnt_share);
		mnt->mnt_group_id = 0;
		CLEAR_MNT_SHARED(mnt);
	पूर्ण
	list_क्रम_each_entry(slave_mnt, &mnt->mnt_slave_list, mnt_slave)
		slave_mnt->mnt_master = master;
	list_move(&mnt->mnt_slave, &master->mnt_slave_list);
	list_splice(&mnt->mnt_slave_list, master->mnt_slave_list.prev);
	INIT_LIST_HEAD(&mnt->mnt_slave_list);
	mnt->mnt_master = master;
	वापस 0;
पूर्ण

/*
 * vfsmount lock must be held क्रम ग_लिखो
 */
व्योम change_mnt_propagation(काष्ठा mount *mnt, पूर्णांक type)
अणु
	अगर (type == MS_SHARED) अणु
		set_mnt_shared(mnt);
		वापस;
	पूर्ण
	करो_make_slave(mnt);
	अगर (type != MS_SLAVE) अणु
		list_del_init(&mnt->mnt_slave);
		mnt->mnt_master = शून्य;
		अगर (type == MS_UNBINDABLE)
			mnt->mnt.mnt_flags |= MNT_UNBINDABLE;
		अन्यथा
			mnt->mnt.mnt_flags &= ~MNT_UNBINDABLE;
	पूर्ण
पूर्ण

/*
 * get the next mount in the propagation tree.
 * @m: the mount seen last
 * @origin: the original mount from where the tree walk initiated
 *
 * Note that peer groups क्रमm contiguous segments of slave lists.
 * We rely on that in get_source() to be able to find out अगर
 * vfsmount found जबतक iterating with propagation_next() is
 * a peer of one we'd found earlier.
 */
अटल काष्ठा mount *propagation_next(काष्ठा mount *m,
					 काष्ठा mount *origin)
अणु
	/* are there any slaves of this mount? */
	अगर (!IS_MNT_NEW(m) && !list_empty(&m->mnt_slave_list))
		वापस first_slave(m);

	जबतक (1) अणु
		काष्ठा mount *master = m->mnt_master;

		अगर (master == origin->mnt_master) अणु
			काष्ठा mount *next = next_peer(m);
			वापस (next == origin) ? शून्य : next;
		पूर्ण अन्यथा अगर (m->mnt_slave.next != &master->mnt_slave_list)
			वापस next_slave(m);

		/* back at master */
		m = master;
	पूर्ण
पूर्ण

अटल काष्ठा mount *skip_propagation_subtree(काष्ठा mount *m,
						काष्ठा mount *origin)
अणु
	/*
	 * Advance m such that propagation_next will not वापस
	 * the slaves of m.
	 */
	अगर (!IS_MNT_NEW(m) && !list_empty(&m->mnt_slave_list))
		m = last_slave(m);

	वापस m;
पूर्ण

अटल काष्ठा mount *next_group(काष्ठा mount *m, काष्ठा mount *origin)
अणु
	जबतक (1) अणु
		जबतक (1) अणु
			काष्ठा mount *next;
			अगर (!IS_MNT_NEW(m) && !list_empty(&m->mnt_slave_list))
				वापस first_slave(m);
			next = next_peer(m);
			अगर (m->mnt_group_id == origin->mnt_group_id) अणु
				अगर (next == origin)
					वापस शून्य;
			पूर्ण अन्यथा अगर (m->mnt_slave.next != &next->mnt_slave)
				अवरोध;
			m = next;
		पूर्ण
		/* m is the last peer */
		जबतक (1) अणु
			काष्ठा mount *master = m->mnt_master;
			अगर (m->mnt_slave.next != &master->mnt_slave_list)
				वापस next_slave(m);
			m = next_peer(master);
			अगर (master->mnt_group_id == origin->mnt_group_id)
				अवरोध;
			अगर (master->mnt_slave.next == &m->mnt_slave)
				अवरोध;
			m = master;
		पूर्ण
		अगर (m == origin)
			वापस शून्य;
	पूर्ण
पूर्ण

/* all accesses are serialized by namespace_sem */
अटल काष्ठा mount *last_dest, *first_source, *last_source, *dest_master;
अटल काष्ठा mountpoपूर्णांक *mp;
अटल काष्ठा hlist_head *list;

अटल अंतरभूत bool peers(काष्ठा mount *m1, काष्ठा mount *m2)
अणु
	वापस m1->mnt_group_id == m2->mnt_group_id && m1->mnt_group_id;
पूर्ण

अटल पूर्णांक propagate_one(काष्ठा mount *m)
अणु
	काष्ठा mount *child;
	पूर्णांक type;
	/* skip ones added by this propagate_mnt() */
	अगर (IS_MNT_NEW(m))
		वापस 0;
	/* skip अगर mountpoपूर्णांक isn't covered by it */
	अगर (!is_subdir(mp->m_dentry, m->mnt.mnt_root))
		वापस 0;
	अगर (peers(m, last_dest)) अणु
		type = CL_MAKE_SHARED;
	पूर्ण अन्यथा अणु
		काष्ठा mount *n, *p;
		bool करोne;
		क्रम (n = m; ; n = p) अणु
			p = n->mnt_master;
			अगर (p == dest_master || IS_MNT_MARKED(p))
				अवरोध;
		पूर्ण
		करो अणु
			काष्ठा mount *parent = last_source->mnt_parent;
			अगर (last_source == first_source)
				अवरोध;
			करोne = parent->mnt_master == p;
			अगर (करोne && peers(n, parent))
				अवरोध;
			last_source = last_source->mnt_master;
		पूर्ण जबतक (!करोne);

		type = CL_SLAVE;
		/* beginning of peer group among the slaves? */
		अगर (IS_MNT_SHARED(m))
			type |= CL_MAKE_SHARED;
	पूर्ण
		
	child = copy_tree(last_source, last_source->mnt.mnt_root, type);
	अगर (IS_ERR(child))
		वापस PTR_ERR(child);
	पढ़ो_seqlock_excl(&mount_lock);
	mnt_set_mountpoपूर्णांक(m, mp, child);
	अगर (m->mnt_master != dest_master)
		SET_MNT_MARK(m->mnt_master);
	पढ़ो_sequnlock_excl(&mount_lock);
	last_dest = m;
	last_source = child;
	hlist_add_head(&child->mnt_hash, list);
	वापस count_mounts(m->mnt_ns, child);
पूर्ण

/*
 * mount 'source_mnt' under the destination 'dest_mnt' at
 * dentry 'dest_dentry'. And propagate that mount to
 * all the peer and slave mounts of 'dest_mnt'.
 * Link all the new mounts पूर्णांकo a propagation tree headed at
 * source_mnt. Also link all the new mounts using ->mnt_list
 * headed at source_mnt's ->mnt_list
 *
 * @dest_mnt: destination mount.
 * @dest_dentry: destination dentry.
 * @source_mnt: source mount.
 * @tree_list : list of heads of trees to be attached.
 */
पूर्णांक propagate_mnt(काष्ठा mount *dest_mnt, काष्ठा mountpoपूर्णांक *dest_mp,
		    काष्ठा mount *source_mnt, काष्ठा hlist_head *tree_list)
अणु
	काष्ठा mount *m, *n;
	पूर्णांक ret = 0;

	/*
	 * we करोn't want to bother passing tons of arguments to
	 * propagate_one(); everything is serialized by namespace_sem,
	 * so globals will करो just fine.
	 */
	last_dest = dest_mnt;
	first_source = source_mnt;
	last_source = source_mnt;
	mp = dest_mp;
	list = tree_list;
	dest_master = dest_mnt->mnt_master;

	/* all peers of dest_mnt, except dest_mnt itself */
	क्रम (n = next_peer(dest_mnt); n != dest_mnt; n = next_peer(n)) अणु
		ret = propagate_one(n);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* all slave groups */
	क्रम (m = next_group(dest_mnt, dest_mnt); m;
			m = next_group(m, dest_mnt)) अणु
		/* everything in that slave group */
		n = m;
		करो अणु
			ret = propagate_one(n);
			अगर (ret)
				जाओ out;
			n = next_peer(n);
		पूर्ण जबतक (n != m);
	पूर्ण
out:
	पढ़ो_seqlock_excl(&mount_lock);
	hlist_क्रम_each_entry(n, tree_list, mnt_hash) अणु
		m = n->mnt_parent;
		अगर (m->mnt_master != dest_mnt->mnt_master)
			CLEAR_MNT_MARK(m->mnt_master);
	पूर्ण
	पढ़ो_sequnlock_excl(&mount_lock);
	वापस ret;
पूर्ण

अटल काष्ठा mount *find_topper(काष्ठा mount *mnt)
अणु
	/* If there is exactly one mount covering mnt completely वापस it. */
	काष्ठा mount *child;

	अगर (!list_is_singular(&mnt->mnt_mounts))
		वापस शून्य;

	child = list_first_entry(&mnt->mnt_mounts, काष्ठा mount, mnt_child);
	अगर (child->mnt_mountpoपूर्णांक != mnt->mnt.mnt_root)
		वापस शून्य;

	वापस child;
पूर्ण

/*
 * वापस true अगर the refcount is greater than count
 */
अटल अंतरभूत पूर्णांक करो_refcount_check(काष्ठा mount *mnt, पूर्णांक count)
अणु
	वापस mnt_get_count(mnt) > count;
पूर्ण

/*
 * check अगर the mount 'mnt' can be unmounted successfully.
 * @mnt: the mount to be checked क्रम unmount
 * NOTE: unmounting 'mnt' would naturally propagate to all
 * other mounts its parent propagates to.
 * Check अगर any of these mounts that **करो not have submounts**
 * have more references than 'refcnt'. If so वापस busy.
 *
 * vfsmount lock must be held क्रम ग_लिखो
 */
पूर्णांक propagate_mount_busy(काष्ठा mount *mnt, पूर्णांक refcnt)
अणु
	काष्ठा mount *m, *child, *topper;
	काष्ठा mount *parent = mnt->mnt_parent;

	अगर (mnt == parent)
		वापस करो_refcount_check(mnt, refcnt);

	/*
	 * quickly check अगर the current mount can be unmounted.
	 * If not, we करोn't have to go checking क्रम all other
	 * mounts
	 */
	अगर (!list_empty(&mnt->mnt_mounts) || करो_refcount_check(mnt, refcnt))
		वापस 1;

	क्रम (m = propagation_next(parent, parent); m;
	     		m = propagation_next(m, parent)) अणु
		पूर्णांक count = 1;
		child = __lookup_mnt(&m->mnt, mnt->mnt_mountpoपूर्णांक);
		अगर (!child)
			जारी;

		/* Is there exactly one mount on the child that covers
		 * it completely whose reference should be ignored?
		 */
		topper = find_topper(child);
		अगर (topper)
			count += 1;
		अन्यथा अगर (!list_empty(&child->mnt_mounts))
			जारी;

		अगर (करो_refcount_check(child, count))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Clear MNT_LOCKED when it can be shown to be safe.
 *
 * mount_lock lock must be held क्रम ग_लिखो
 */
व्योम propagate_mount_unlock(काष्ठा mount *mnt)
अणु
	काष्ठा mount *parent = mnt->mnt_parent;
	काष्ठा mount *m, *child;

	BUG_ON(parent == mnt);

	क्रम (m = propagation_next(parent, parent); m;
			m = propagation_next(m, parent)) अणु
		child = __lookup_mnt(&m->mnt, mnt->mnt_mountpoपूर्णांक);
		अगर (child)
			child->mnt.mnt_flags &= ~MNT_LOCKED;
	पूर्ण
पूर्ण

अटल व्योम umount_one(काष्ठा mount *mnt, काष्ठा list_head *to_umount)
अणु
	CLEAR_MNT_MARK(mnt);
	mnt->mnt.mnt_flags |= MNT_UMOUNT;
	list_del_init(&mnt->mnt_child);
	list_del_init(&mnt->mnt_umounting);
	list_move_tail(&mnt->mnt_list, to_umount);
पूर्ण

/*
 * NOTE: unmounting 'mnt' naturally propagates to all other mounts its
 * parent propagates to.
 */
अटल bool __propagate_umount(काष्ठा mount *mnt,
			       काष्ठा list_head *to_umount,
			       काष्ठा list_head *to_restore)
अणु
	bool progress = false;
	काष्ठा mount *child;

	/*
	 * The state of the parent won't change अगर this mount is
	 * alपढ़ोy unmounted or marked as without children.
	 */
	अगर (mnt->mnt.mnt_flags & (MNT_UMOUNT | MNT_MARKED))
		जाओ out;

	/* Verअगरy topper is the only gअक्रमchild that has not been
	 * speculatively unmounted.
	 */
	list_क्रम_each_entry(child, &mnt->mnt_mounts, mnt_child) अणु
		अगर (child->mnt_mountpoपूर्णांक == mnt->mnt.mnt_root)
			जारी;
		अगर (!list_empty(&child->mnt_umounting) && IS_MNT_MARKED(child))
			जारी;
		/* Found a mounted child */
		जाओ children;
	पूर्ण

	/* Mark mounts that can be unmounted अगर not locked */
	SET_MNT_MARK(mnt);
	progress = true;

	/* If a mount is without children and not locked umount it. */
	अगर (!IS_MNT_LOCKED(mnt)) अणु
		umount_one(mnt, to_umount);
	पूर्ण अन्यथा अणु
children:
		list_move_tail(&mnt->mnt_umounting, to_restore);
	पूर्ण
out:
	वापस progress;
पूर्ण

अटल व्योम umount_list(काष्ठा list_head *to_umount,
			काष्ठा list_head *to_restore)
अणु
	काष्ठा mount *mnt, *child, *पंचांगp;
	list_क्रम_each_entry(mnt, to_umount, mnt_list) अणु
		list_क्रम_each_entry_safe(child, पंचांगp, &mnt->mnt_mounts, mnt_child) अणु
			/* topper? */
			अगर (child->mnt_mountpoपूर्णांक == mnt->mnt.mnt_root)
				list_move_tail(&child->mnt_umounting, to_restore);
			अन्यथा
				umount_one(child, to_umount);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम restore_mounts(काष्ठा list_head *to_restore)
अणु
	/* Restore mounts to a clean working state */
	जबतक (!list_empty(to_restore)) अणु
		काष्ठा mount *mnt, *parent;
		काष्ठा mountpoपूर्णांक *mp;

		mnt = list_first_entry(to_restore, काष्ठा mount, mnt_umounting);
		CLEAR_MNT_MARK(mnt);
		list_del_init(&mnt->mnt_umounting);

		/* Should this mount be reparented? */
		mp = mnt->mnt_mp;
		parent = mnt->mnt_parent;
		जबतक (parent->mnt.mnt_flags & MNT_UMOUNT) अणु
			mp = parent->mnt_mp;
			parent = parent->mnt_parent;
		पूर्ण
		अगर (parent != mnt->mnt_parent)
			mnt_change_mountpoपूर्णांक(parent, mp, mnt);
	पूर्ण
पूर्ण

अटल व्योम cleanup_umount_visitations(काष्ठा list_head *visited)
अणु
	जबतक (!list_empty(visited)) अणु
		काष्ठा mount *mnt =
			list_first_entry(visited, काष्ठा mount, mnt_umounting);
		list_del_init(&mnt->mnt_umounting);
	पूर्ण
पूर्ण

/*
 * collect all mounts that receive propagation from the mount in @list,
 * and वापस these additional mounts in the same list.
 * @list: the list of mounts to be unmounted.
 *
 * vfsmount lock must be held क्रम ग_लिखो
 */
पूर्णांक propagate_umount(काष्ठा list_head *list)
अणु
	काष्ठा mount *mnt;
	LIST_HEAD(to_restore);
	LIST_HEAD(to_umount);
	LIST_HEAD(visited);

	/* Find candidates क्रम unmounting */
	list_क्रम_each_entry_reverse(mnt, list, mnt_list) अणु
		काष्ठा mount *parent = mnt->mnt_parent;
		काष्ठा mount *m;

		/*
		 * If this mount has alपढ़ोy been visited it is known that it's
		 * entire peer group and all of their slaves in the propagation
		 * tree क्रम the mountpoपूर्णांक has alपढ़ोy been visited and there is
		 * no need to visit them again.
		 */
		अगर (!list_empty(&mnt->mnt_umounting))
			जारी;

		list_add_tail(&mnt->mnt_umounting, &visited);
		क्रम (m = propagation_next(parent, parent); m;
		     m = propagation_next(m, parent)) अणु
			काष्ठा mount *child = __lookup_mnt(&m->mnt,
							   mnt->mnt_mountpoपूर्णांक);
			अगर (!child)
				जारी;

			अगर (!list_empty(&child->mnt_umounting)) अणु
				/*
				 * If the child has alपढ़ोy been visited it is
				 * know that it's entire peer group and all of
				 * their slaves in the propgation tree क्रम the
				 * mountpoपूर्णांक has alपढ़ोy been visited and there
				 * is no need to visit this subtree again.
				 */
				m = skip_propagation_subtree(m, parent);
				जारी;
			पूर्ण अन्यथा अगर (child->mnt.mnt_flags & MNT_UMOUNT) अणु
				/*
				 * We have come accross an partially unmounted
				 * mount in list that has not been visited yet.
				 * Remember it has been visited and जारी
				 * about our merry way.
				 */
				list_add_tail(&child->mnt_umounting, &visited);
				जारी;
			पूर्ण

			/* Check the child and parents जबतक progress is made */
			जबतक (__propagate_umount(child,
						  &to_umount, &to_restore)) अणु
				/* Is the parent a umount candidate? */
				child = child->mnt_parent;
				अगर (list_empty(&child->mnt_umounting))
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	umount_list(&to_umount, &to_restore);
	restore_mounts(&to_restore);
	cleanup_umount_visitations(&visited);
	list_splice_tail(&to_umount, list);

	वापस 0;
पूर्ण
