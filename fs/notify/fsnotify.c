<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2008 Red Hat, Inc., Eric Paris <eparis@redhat.com>
 */

#समावेश <linux/dcache.h>
#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/srcu.h>

#समावेश <linux/fsnotअगरy_backend.h>
#समावेश "fsnotify.h"

/*
 * Clear all of the marks on an inode when it is being evicted from core
 */
व्योम __fsnotअगरy_inode_delete(काष्ठा inode *inode)
अणु
	fsnotअगरy_clear_marks_by_inode(inode);
पूर्ण
EXPORT_SYMBOL_GPL(__fsnotअगरy_inode_delete);

व्योम __fsnotअगरy_vfsmount_delete(काष्ठा vfsmount *mnt)
अणु
	fsnotअगरy_clear_marks_by_mount(mnt);
पूर्ण

/**
 * fsnotअगरy_unmount_inodes - an sb is unmounting.  handle any watched inodes.
 * @sb: superblock being unmounted.
 *
 * Called during unmount with no locks held, so needs to be safe against
 * concurrent modअगरiers. We temporarily drop sb->s_inode_list_lock and CAN block.
 */
अटल व्योम fsnotअगरy_unmount_inodes(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode, *iput_inode = शून्य;

	spin_lock(&sb->s_inode_list_lock);
	list_क्रम_each_entry(inode, &sb->s_inodes, i_sb_list) अणु
		/*
		 * We cannot __iget() an inode in state I_FREEING,
		 * I_WILL_FREE, or I_NEW which is fine because by that poपूर्णांक
		 * the inode cannot have any associated watches.
		 */
		spin_lock(&inode->i_lock);
		अगर (inode->i_state & (I_FREEING|I_WILL_FREE|I_NEW)) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण

		/*
		 * If i_count is zero, the inode cannot have any watches and
		 * करोing an __iget/iput with SB_ACTIVE clear would actually
		 * evict all inodes with zero i_count from icache which is
		 * unnecessarily violent and may in fact be illegal to करो.
		 * However, we should have been called /after/ evict_inodes
		 * हटाओd all zero refcount inodes, in any हाल.  Test to
		 * be sure.
		 */
		अगर (!atomic_पढ़ो(&inode->i_count)) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण

		__iget(inode);
		spin_unlock(&inode->i_lock);
		spin_unlock(&sb->s_inode_list_lock);

		अगर (iput_inode)
			iput(iput_inode);

		/* क्रम each watch, send FS_UNMOUNT and then हटाओ it */
		fsnotअगरy_inode(inode, FS_UNMOUNT);

		fsnotअगरy_inode_delete(inode);

		iput_inode = inode;

		cond_resched();
		spin_lock(&sb->s_inode_list_lock);
	पूर्ण
	spin_unlock(&sb->s_inode_list_lock);

	अगर (iput_inode)
		iput(iput_inode);
	/* Wait क्रम outstanding inode references from connectors */
	रुको_var_event(&sb->s_fsnotअगरy_inode_refs,
		       !atomic_दीर्घ_पढ़ो(&sb->s_fsnotअगरy_inode_refs));
पूर्ण

व्योम fsnotअगरy_sb_delete(काष्ठा super_block *sb)
अणु
	fsnotअगरy_unmount_inodes(sb);
	fsnotअगरy_clear_marks_by_sb(sb);
पूर्ण

/*
 * Given an inode, first check अगर we care what happens to our children.  Inotअगरy
 * and dnotअगरy both tell their parents about events.  If we care about any event
 * on a child we run all of our children and set a dentry flag saying that the
 * parent cares.  Thus when an event happens on a child it can quickly tell अगर
 * अगर there is a need to find a parent and send the event to the parent.
 */
व्योम __fsnotअगरy_update_child_dentry_flags(काष्ठा inode *inode)
अणु
	काष्ठा dentry *alias;
	पूर्णांक watched;

	अगर (!S_ISसूची(inode->i_mode))
		वापस;

	/* determine अगर the children should tell inode about their events */
	watched = fsnotअगरy_inode_watches_children(inode);

	spin_lock(&inode->i_lock);
	/* run all of the dentries associated with this inode.  Since this is a
	 * directory, there damn well better only be one item on this list */
	hlist_क्रम_each_entry(alias, &inode->i_dentry, d_u.d_alias) अणु
		काष्ठा dentry *child;

		/* run all of the children of the original inode and fix their
		 * d_flags to indicate parental पूर्णांकerest (their parent is the
		 * original inode) */
		spin_lock(&alias->d_lock);
		list_क्रम_each_entry(child, &alias->d_subdirs, d_child) अणु
			अगर (!child->d_inode)
				जारी;

			spin_lock_nested(&child->d_lock, DENTRY_D_LOCK_NESTED);
			अगर (watched)
				child->d_flags |= DCACHE_FSNOTIFY_PARENT_WATCHED;
			अन्यथा
				child->d_flags &= ~DCACHE_FSNOTIFY_PARENT_WATCHED;
			spin_unlock(&child->d_lock);
		पूर्ण
		spin_unlock(&alias->d_lock);
	पूर्ण
	spin_unlock(&inode->i_lock);
पूर्ण

/* Are inode/sb/mount पूर्णांकerested in parent and name info with this event? */
अटल bool fsnotअगरy_event_needs_parent(काष्ठा inode *inode, काष्ठा mount *mnt,
					__u32 mask)
अणु
	__u32 marks_mask = 0;

	/* We only send parent/name to inode/sb/mount क्रम events on non-dir */
	अगर (mask & FS_ISसूची)
		वापस false;

	/*
	 * All events that are possible on child can also may be reported with
	 * parent/name info to inode/sb/mount.  Otherwise, a watching parent
	 * could result in events reported with unexpected name info to sb/mount.
	 */
	BUILD_BUG_ON(FS_EVENTS_POSS_ON_CHILD & ~FS_EVENTS_POSS_TO_PARENT);

	/* Did either inode/sb/mount subscribe क्रम events with parent/name? */
	marks_mask |= fsnotअगरy_parent_needed_mask(inode->i_fsnotअगरy_mask);
	marks_mask |= fsnotअगरy_parent_needed_mask(inode->i_sb->s_fsnotअगरy_mask);
	अगर (mnt)
		marks_mask |= fsnotअगरy_parent_needed_mask(mnt->mnt_fsnotअगरy_mask);

	/* Did they subscribe क्रम this event with parent/name info? */
	वापस mask & marks_mask;
पूर्ण

/*
 * Notअगरy this dentry's parent about a child's events with child name info
 * अगर parent is watching or अगर inode/sb/mount are पूर्णांकerested in events with
 * parent and name info.
 *
 * Notअगरy only the child without name info अगर parent is not watching and
 * inode/sb/mount are not पूर्णांकerested in events with parent and name info.
 */
पूर्णांक __fsnotअगरy_parent(काष्ठा dentry *dentry, __u32 mask, स्थिर व्योम *data,
		      पूर्णांक data_type)
अणु
	स्थिर काष्ठा path *path = fsnotअगरy_data_path(data, data_type);
	काष्ठा mount *mnt = path ? real_mount(path->mnt) : शून्य;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा dentry *parent;
	bool parent_watched = dentry->d_flags & DCACHE_FSNOTIFY_PARENT_WATCHED;
	bool parent_needed, parent_पूर्णांकerested;
	__u32 p_mask;
	काष्ठा inode *p_inode = शून्य;
	काष्ठा name_snapshot name;
	काष्ठा qstr *file_name = शून्य;
	पूर्णांक ret = 0;

	/*
	 * Do inode/sb/mount care about parent and name info on non-dir?
	 * Do they care about any event at all?
	 */
	अगर (!inode->i_fsnotअगरy_marks && !inode->i_sb->s_fsnotअगरy_marks &&
	    (!mnt || !mnt->mnt_fsnotअगरy_marks) && !parent_watched)
		वापस 0;

	parent = शून्य;
	parent_needed = fsnotअगरy_event_needs_parent(inode, mnt, mask);
	अगर (!parent_watched && !parent_needed)
		जाओ notअगरy;

	/* Does parent inode care about events on children? */
	parent = dget_parent(dentry);
	p_inode = parent->d_inode;
	p_mask = fsnotअगरy_inode_watches_children(p_inode);
	अगर (unlikely(parent_watched && !p_mask))
		__fsnotअगरy_update_child_dentry_flags(p_inode);

	/*
	 * Include parent/name in notअगरication either अगर some notअगरication
	 * groups require parent info or the parent is पूर्णांकerested in this event.
	 */
	parent_पूर्णांकerested = mask & p_mask & ALL_FSNOTIFY_EVENTS;
	अगर (parent_needed || parent_पूर्णांकerested) अणु
		/* When notअगरying parent, child should be passed as data */
		WARN_ON_ONCE(inode != fsnotअगरy_data_inode(data, data_type));

		/* Notअगरy both parent and child with child name info */
		take_dentry_name_snapshot(&name, dentry);
		file_name = &name.name;
		अगर (parent_पूर्णांकerested)
			mask |= FS_EVENT_ON_CHILD;
	पूर्ण

notअगरy:
	ret = fsnotअगरy(mask, data, data_type, p_inode, file_name, inode, 0);

	अगर (file_name)
		release_dentry_name_snapshot(&name);
	dput(parent);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__fsnotअगरy_parent);

अटल पूर्णांक fsnotअगरy_handle_inode_event(काष्ठा fsnotअगरy_group *group,
				       काष्ठा fsnotअगरy_mark *inode_mark,
				       u32 mask, स्थिर व्योम *data, पूर्णांक data_type,
				       काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
				       u32 cookie)
अणु
	स्थिर काष्ठा path *path = fsnotअगरy_data_path(data, data_type);
	काष्ठा inode *inode = fsnotअगरy_data_inode(data, data_type);
	स्थिर काष्ठा fsnotअगरy_ops *ops = group->ops;

	अगर (WARN_ON_ONCE(!ops->handle_inode_event))
		वापस 0;

	अगर ((inode_mark->mask & FS_EXCL_UNLINK) &&
	    path && d_unlinked(path->dentry))
		वापस 0;

	/* Check पूर्णांकerest of this mark in हाल event was sent with two marks */
	अगर (!(mask & inode_mark->mask & ALL_FSNOTIFY_EVENTS))
		वापस 0;

	वापस ops->handle_inode_event(inode_mark, mask, inode, dir, name, cookie);
पूर्ण

अटल पूर्णांक fsnotअगरy_handle_event(काष्ठा fsnotअगरy_group *group, __u32 mask,
				 स्थिर व्योम *data, पूर्णांक data_type,
				 काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
				 u32 cookie, काष्ठा fsnotअगरy_iter_info *iter_info)
अणु
	काष्ठा fsnotअगरy_mark *inode_mark = fsnotअगरy_iter_inode_mark(iter_info);
	काष्ठा fsnotअगरy_mark *parent_mark = fsnotअगरy_iter_parent_mark(iter_info);
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(fsnotअगरy_iter_sb_mark(iter_info)) ||
	    WARN_ON_ONCE(fsnotअगरy_iter_vfsmount_mark(iter_info)))
		वापस 0;

	अगर (parent_mark) अणु
		/*
		 * parent_mark indicates that the parent inode is watching
		 * children and पूर्णांकerested in this event, which is an event
		 * possible on child. But is *this mark* watching children and
		 * पूर्णांकerested in this event?
		 */
		अगर (parent_mark->mask & FS_EVENT_ON_CHILD) अणु
			ret = fsnotअगरy_handle_inode_event(group, parent_mark, mask,
							  data, data_type, dir, name, 0);
			अगर (ret)
				वापस ret;
		पूर्ण
		अगर (!inode_mark)
			वापस 0;
	पूर्ण

	अगर (mask & FS_EVENT_ON_CHILD) अणु
		/*
		 * Some events can be sent on both parent dir and child marks
		 * (e.g. FS_ATTRIB).  If both parent dir and child are
		 * watching, report the event once to parent dir with name (अगर
		 * पूर्णांकerested) and once to child without name (अगर पूर्णांकerested).
		 * The child watcher is expecting an event without a file name
		 * and without the FS_EVENT_ON_CHILD flag.
		 */
		mask &= ~FS_EVENT_ON_CHILD;
		dir = शून्य;
		name = शून्य;
	पूर्ण

	वापस fsnotअगरy_handle_inode_event(group, inode_mark, mask, data, data_type,
					   dir, name, cookie);
पूर्ण

अटल पूर्णांक send_to_group(__u32 mask, स्थिर व्योम *data, पूर्णांक data_type,
			 काष्ठा inode *dir, स्थिर काष्ठा qstr *file_name,
			 u32 cookie, काष्ठा fsnotअगरy_iter_info *iter_info)
अणु
	काष्ठा fsnotअगरy_group *group = शून्य;
	__u32 test_mask = (mask & ALL_FSNOTIFY_EVENTS);
	__u32 marks_mask = 0;
	__u32 marks_ignored_mask = 0;
	काष्ठा fsnotअगरy_mark *mark;
	पूर्णांक type;

	अगर (WARN_ON(!iter_info->report_mask))
		वापस 0;

	/* clear ignored on inode modअगरication */
	अगर (mask & FS_MODIFY) अणु
		fsnotअगरy_क्रमeach_obj_type(type) अणु
			अगर (!fsnotअगरy_iter_should_report_type(iter_info, type))
				जारी;
			mark = iter_info->marks[type];
			अगर (mark &&
			    !(mark->flags & FSNOTIFY_MARK_FLAG_IGNORED_SURV_MODIFY))
				mark->ignored_mask = 0;
		पूर्ण
	पूर्ण

	fsnotअगरy_क्रमeach_obj_type(type) अणु
		अगर (!fsnotअगरy_iter_should_report_type(iter_info, type))
			जारी;
		mark = iter_info->marks[type];
		/* करोes the object mark tell us to करो something? */
		अगर (mark) अणु
			group = mark->group;
			marks_mask |= mark->mask;
			marks_ignored_mask |= mark->ignored_mask;
		पूर्ण
	पूर्ण

	pr_debug("%s: group=%p mask=%x marks_mask=%x marks_ignored_mask=%x data=%p data_type=%d dir=%p cookie=%d\n",
		 __func__, group, mask, marks_mask, marks_ignored_mask,
		 data, data_type, dir, cookie);

	अगर (!(test_mask & marks_mask & ~marks_ignored_mask))
		वापस 0;

	अगर (group->ops->handle_event) अणु
		वापस group->ops->handle_event(group, mask, data, data_type, dir,
						file_name, cookie, iter_info);
	पूर्ण

	वापस fsnotअगरy_handle_event(group, mask, data, data_type, dir,
				     file_name, cookie, iter_info);
पूर्ण

अटल काष्ठा fsnotअगरy_mark *fsnotअगरy_first_mark(काष्ठा fsnotअगरy_mark_connector **connp)
अणु
	काष्ठा fsnotअगरy_mark_connector *conn;
	काष्ठा hlist_node *node = शून्य;

	conn = srcu_dereference(*connp, &fsnotअगरy_mark_srcu);
	अगर (conn)
		node = srcu_dereference(conn->list.first, &fsnotअगरy_mark_srcu);

	वापस hlist_entry_safe(node, काष्ठा fsnotअगरy_mark, obj_list);
पूर्ण

अटल काष्ठा fsnotअगरy_mark *fsnotअगरy_next_mark(काष्ठा fsnotअगरy_mark *mark)
अणु
	काष्ठा hlist_node *node = शून्य;

	अगर (mark)
		node = srcu_dereference(mark->obj_list.next,
					&fsnotअगरy_mark_srcu);

	वापस hlist_entry_safe(node, काष्ठा fsnotअगरy_mark, obj_list);
पूर्ण

/*
 * iter_info is a multi head priority queue of marks.
 * Pick a subset of marks from queue heads, all with the
 * same group and set the report_mask क्रम selected subset.
 * Returns the report_mask of the selected subset.
 */
अटल अचिन्हित पूर्णांक fsnotअगरy_iter_select_report_types(
		काष्ठा fsnotअगरy_iter_info *iter_info)
अणु
	काष्ठा fsnotअगरy_group *max_prio_group = शून्य;
	काष्ठा fsnotअगरy_mark *mark;
	पूर्णांक type;

	/* Choose max prio group among groups of all queue heads */
	fsnotअगरy_क्रमeach_obj_type(type) अणु
		mark = iter_info->marks[type];
		अगर (mark &&
		    fsnotअगरy_compare_groups(max_prio_group, mark->group) > 0)
			max_prio_group = mark->group;
	पूर्ण

	अगर (!max_prio_group)
		वापस 0;

	/* Set the report mask क्रम marks from same group as max prio group */
	iter_info->report_mask = 0;
	fsnotअगरy_क्रमeach_obj_type(type) अणु
		mark = iter_info->marks[type];
		अगर (mark &&
		    fsnotअगरy_compare_groups(max_prio_group, mark->group) == 0)
			fsnotअगरy_iter_set_report_type(iter_info, type);
	पूर्ण

	वापस iter_info->report_mask;
पूर्ण

/*
 * Pop from iter_info multi head queue, the marks that were iterated in the
 * current iteration step.
 */
अटल व्योम fsnotअगरy_iter_next(काष्ठा fsnotअगरy_iter_info *iter_info)
अणु
	पूर्णांक type;

	fsnotअगरy_क्रमeach_obj_type(type) अणु
		अगर (fsnotअगरy_iter_should_report_type(iter_info, type))
			iter_info->marks[type] =
				fsnotअगरy_next_mark(iter_info->marks[type]);
	पूर्ण
पूर्ण

/*
 * fsnotअगरy - This is the मुख्य call to fsnotअगरy.
 *
 * The VFS calls पूर्णांकo hook specअगरic functions in linux/fsnotअगरy.h.
 * Those functions then in turn call here.  Here will call out to all of the
 * रेजिस्टरed fsnotअगरy_group.  Those groups can then use the notअगरication event
 * in whatever means they feel necessary.
 *
 * @mask:	event type and flags
 * @data:	object that event happened on
 * @data_type:	type of object क्रम fanotअगरy_data_XXX() accessors
 * @dir:	optional directory associated with event -
 *		अगर @file_name is not शून्य, this is the directory that
 *		@file_name is relative to
 * @file_name:	optional file name associated with event
 * @inode:	optional inode associated with event -
 *		either @dir or @inode must be non-शून्य.
 *		अगर both are non-शून्य event may be reported to both.
 * @cookie:	inotअगरy नाम cookie
 */
पूर्णांक fsnotअगरy(__u32 mask, स्थिर व्योम *data, पूर्णांक data_type, काष्ठा inode *dir,
	     स्थिर काष्ठा qstr *file_name, काष्ठा inode *inode, u32 cookie)
अणु
	स्थिर काष्ठा path *path = fsnotअगरy_data_path(data, data_type);
	काष्ठा fsnotअगरy_iter_info iter_info = अणुपूर्ण;
	काष्ठा super_block *sb;
	काष्ठा mount *mnt = शून्य;
	काष्ठा inode *parent = शून्य;
	पूर्णांक ret = 0;
	__u32 test_mask, marks_mask;

	अगर (path)
		mnt = real_mount(path->mnt);

	अगर (!inode) अणु
		/* Dirent event - report on TYPE_INODE to dir */
		inode = dir;
	पूर्ण अन्यथा अगर (mask & FS_EVENT_ON_CHILD) अणु
		/*
		 * Event on child - report on TYPE_PARENT to dir अगर it is
		 * watching children and on TYPE_INODE to child.
		 */
		parent = dir;
	पूर्ण
	sb = inode->i_sb;

	/*
	 * Optimization: srcu_पढ़ो_lock() has a memory barrier which can
	 * be expensive.  It protects walking the *_fsnotअगरy_marks lists.
	 * However, अगर we करो not walk the lists, we करो not have to करो
	 * SRCU because we have no references to any objects and करो not
	 * need SRCU to keep them "alive".
	 */
	अगर (!sb->s_fsnotअगरy_marks &&
	    (!mnt || !mnt->mnt_fsnotअगरy_marks) &&
	    (!inode || !inode->i_fsnotअगरy_marks) &&
	    (!parent || !parent->i_fsnotअगरy_marks))
		वापस 0;

	marks_mask = sb->s_fsnotअगरy_mask;
	अगर (mnt)
		marks_mask |= mnt->mnt_fsnotअगरy_mask;
	अगर (inode)
		marks_mask |= inode->i_fsnotअगरy_mask;
	अगर (parent)
		marks_mask |= parent->i_fsnotअगरy_mask;


	/*
	 * अगर this is a modअगरy event we may need to clear the ignored masks
	 * otherwise वापस अगर none of the marks care about this type of event.
	 */
	test_mask = (mask & ALL_FSNOTIFY_EVENTS);
	अगर (!(mask & FS_MODIFY) && !(test_mask & marks_mask))
		वापस 0;

	iter_info.srcu_idx = srcu_पढ़ो_lock(&fsnotअगरy_mark_srcu);

	iter_info.marks[FSNOTIFY_OBJ_TYPE_SB] =
		fsnotअगरy_first_mark(&sb->s_fsnotअगरy_marks);
	अगर (mnt) अणु
		iter_info.marks[FSNOTIFY_OBJ_TYPE_VFSMOUNT] =
			fsnotअगरy_first_mark(&mnt->mnt_fsnotअगरy_marks);
	पूर्ण
	अगर (inode) अणु
		iter_info.marks[FSNOTIFY_OBJ_TYPE_INODE] =
			fsnotअगरy_first_mark(&inode->i_fsnotअगरy_marks);
	पूर्ण
	अगर (parent) अणु
		iter_info.marks[FSNOTIFY_OBJ_TYPE_PARENT] =
			fsnotअगरy_first_mark(&parent->i_fsnotअगरy_marks);
	पूर्ण

	/*
	 * We need to merge inode/vfsmount/sb mark lists so that e.g. inode mark
	 * ignore masks are properly reflected क्रम mount/sb mark notअगरications.
	 * That's why this traversal is so complicated...
	 */
	जबतक (fsnotअगरy_iter_select_report_types(&iter_info)) अणु
		ret = send_to_group(mask, data, data_type, dir, file_name,
				    cookie, &iter_info);

		अगर (ret && (mask & ALL_FSNOTIFY_PERM_EVENTS))
			जाओ out;

		fsnotअगरy_iter_next(&iter_info);
	पूर्ण
	ret = 0;
out:
	srcu_पढ़ो_unlock(&fsnotअगरy_mark_srcu, iter_info.srcu_idx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy);

अटल __init पूर्णांक fsnotअगरy_init(व्योम)
अणु
	पूर्णांक ret;

	BUILD_BUG_ON(HWEIGHT32(ALL_FSNOTIFY_BITS) != 25);

	ret = init_srcu_काष्ठा(&fsnotअगरy_mark_srcu);
	अगर (ret)
		panic("initializing fsnotify_mark_srcu");

	fsnotअगरy_mark_connector_cachep = KMEM_CACHE(fsnotअगरy_mark_connector,
						    SLAB_PANIC);

	वापस 0;
पूर्ण
core_initcall(fsnotअगरy_init);
