<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2008 Red Hat, Inc., Eric Paris <eparis@redhat.com>
 */

/*
 * fsnotअगरy inode mark locking/lअगरeसमय/and refcnting
 *
 * REFCNT:
 * The group->recnt and mark->refcnt tell how many "things" in the kernel
 * currently are referencing the objects. Both kind of objects typically will
 * live inside the kernel with a refcnt of 2, one क्रम its creation and one क्रम
 * the reference a group and a mark hold to each other.
 * If you are holding the appropriate locks, you can take a reference and the
 * object itself is guaranteed to survive until the reference is dropped.
 *
 * LOCKING:
 * There are 3 locks involved with fsnotअगरy inode marks and they MUST be taken
 * in order as follows:
 *
 * group->mark_mutex
 * mark->lock
 * mark->connector->lock
 *
 * group->mark_mutex protects the marks_list anchored inside a given group and
 * each mark is hooked via the g_list.  It also protects the groups निजी
 * data (i.e group limits).

 * mark->lock protects the marks attributes like its masks and flags.
 * Furthermore it protects the access to a reference of the group that the mark
 * is asचिन्हित to as well as the access to a reference of the inode/vfsmount
 * that is being watched by the mark.
 *
 * mark->connector->lock protects the list of marks anchored inside an
 * inode / vfsmount and each mark is hooked via the i_list.
 *
 * A list of notअगरication marks relating to inode / mnt is contained in
 * fsnotअगरy_mark_connector. That काष्ठाure is alive as दीर्घ as there are any
 * marks in the list and is also रक्षित by fsnotअगरy_mark_srcu. A mark माला_लो
 * detached from fsnotअगरy_mark_connector when last reference to the mark is
 * dropped.  Thus having mark reference is enough to protect mark->connector
 * poपूर्णांकer and to make sure fsnotअगरy_mark_connector cannot disappear. Also
 * because we हटाओ mark from g_list beक्रमe dropping mark reference associated
 * with that, any mark found through g_list is guaranteed to have
 * mark->connector set until we drop group->mark_mutex.
 *
 * LIFETIME:
 * Inode marks survive between when they are added to an inode and when their
 * refcnt==0. Marks are also रक्षित by fsnotअगरy_mark_srcu.
 *
 * The inode mark can be cleared क्रम a number of dअगरferent reasons including:
 * - The inode is unlinked क्रम the last समय.  (fsnotअगरy_inode_हटाओ)
 * - The inode is being evicted from cache. (fsnotअगरy_inode_delete)
 * - The fs the inode is on is unmounted.  (fsnotअगरy_inode_delete/fsnotअगरy_unmount_inodes)
 * - Something explicitly requests that it be हटाओd.  (fsnotअगरy_destroy_mark)
 * - The fsnotअगरy_group associated with the mark is going away and all such marks
 *   need to be cleaned up. (fsnotअगरy_clear_marks_by_group)
 *
 * This has the very पूर्णांकeresting property of being able to run concurrently with
 * any (or all) other directions.
 */

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/srcu.h>
#समावेश <linux/ratelimit.h>

#समावेश <linux/atomic.h>

#समावेश <linux/fsnotअगरy_backend.h>
#समावेश "fsnotify.h"

#घोषणा FSNOTIFY_REAPER_DELAY	(1)	/* 1 jअगरfy */

काष्ठा srcu_काष्ठा fsnotअगरy_mark_srcu;
काष्ठा kmem_cache *fsnotअगरy_mark_connector_cachep;

अटल DEFINE_SPINLOCK(destroy_lock);
अटल LIST_HEAD(destroy_list);
अटल काष्ठा fsnotअगरy_mark_connector *connector_destroy_list;

अटल व्योम fsnotअगरy_mark_destroy_workfn(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(reaper_work, fsnotअगरy_mark_destroy_workfn);

अटल व्योम fsnotअगरy_connector_destroy_workfn(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(connector_reaper_work, fsnotअगरy_connector_destroy_workfn);

व्योम fsnotअगरy_get_mark(काष्ठा fsnotअगरy_mark *mark)
अणु
	WARN_ON_ONCE(!refcount_पढ़ो(&mark->refcnt));
	refcount_inc(&mark->refcnt);
पूर्ण

अटल __u32 *fsnotअगरy_conn_mask_p(काष्ठा fsnotअगरy_mark_connector *conn)
अणु
	अगर (conn->type == FSNOTIFY_OBJ_TYPE_INODE)
		वापस &fsnotअगरy_conn_inode(conn)->i_fsnotअगरy_mask;
	अन्यथा अगर (conn->type == FSNOTIFY_OBJ_TYPE_VFSMOUNT)
		वापस &fsnotअगरy_conn_mount(conn)->mnt_fsnotअगरy_mask;
	अन्यथा अगर (conn->type == FSNOTIFY_OBJ_TYPE_SB)
		वापस &fsnotअगरy_conn_sb(conn)->s_fsnotअगरy_mask;
	वापस शून्य;
पूर्ण

__u32 fsnotअगरy_conn_mask(काष्ठा fsnotअगरy_mark_connector *conn)
अणु
	अगर (WARN_ON(!fsnotअगरy_valid_obj_type(conn->type)))
		वापस 0;

	वापस *fsnotअगरy_conn_mask_p(conn);
पूर्ण

अटल व्योम __fsnotअगरy_recalc_mask(काष्ठा fsnotअगरy_mark_connector *conn)
अणु
	u32 new_mask = 0;
	काष्ठा fsnotअगरy_mark *mark;

	निश्चित_spin_locked(&conn->lock);
	/* We can get detached connector here when inode is getting unlinked. */
	अगर (!fsnotअगरy_valid_obj_type(conn->type))
		वापस;
	hlist_क्रम_each_entry(mark, &conn->list, obj_list) अणु
		अगर (mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED)
			new_mask |= mark->mask;
	पूर्ण
	*fsnotअगरy_conn_mask_p(conn) = new_mask;
पूर्ण

/*
 * Calculate mask of events क्रम a list of marks. The caller must make sure
 * connector and connector->obj cannot disappear under us.  Callers achieve
 * this by holding a mark->lock or mark->group->mark_mutex क्रम a mark on this
 * list.
 */
व्योम fsnotअगरy_recalc_mask(काष्ठा fsnotअगरy_mark_connector *conn)
अणु
	अगर (!conn)
		वापस;

	spin_lock(&conn->lock);
	__fsnotअगरy_recalc_mask(conn);
	spin_unlock(&conn->lock);
	अगर (conn->type == FSNOTIFY_OBJ_TYPE_INODE)
		__fsnotअगरy_update_child_dentry_flags(
					fsnotअगरy_conn_inode(conn));
पूर्ण

/* Free all connectors queued क्रम मुक्तing once SRCU period ends */
अटल व्योम fsnotअगरy_connector_destroy_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fsnotअगरy_mark_connector *conn, *मुक्त;

	spin_lock(&destroy_lock);
	conn = connector_destroy_list;
	connector_destroy_list = शून्य;
	spin_unlock(&destroy_lock);

	synchronize_srcu(&fsnotअगरy_mark_srcu);
	जबतक (conn) अणु
		मुक्त = conn;
		conn = conn->destroy_next;
		kmem_cache_मुक्त(fsnotअगरy_mark_connector_cachep, मुक्त);
	पूर्ण
पूर्ण

अटल व्योम *fsnotअगरy_detach_connector_from_object(
					काष्ठा fsnotअगरy_mark_connector *conn,
					अचिन्हित पूर्णांक *type)
अणु
	काष्ठा inode *inode = शून्य;

	*type = conn->type;
	अगर (conn->type == FSNOTIFY_OBJ_TYPE_DETACHED)
		वापस शून्य;

	अगर (conn->type == FSNOTIFY_OBJ_TYPE_INODE) अणु
		inode = fsnotअगरy_conn_inode(conn);
		inode->i_fsnotअगरy_mask = 0;
		atomic_दीर्घ_inc(&inode->i_sb->s_fsnotअगरy_inode_refs);
	पूर्ण अन्यथा अगर (conn->type == FSNOTIFY_OBJ_TYPE_VFSMOUNT) अणु
		fsnotअगरy_conn_mount(conn)->mnt_fsnotअगरy_mask = 0;
	पूर्ण अन्यथा अगर (conn->type == FSNOTIFY_OBJ_TYPE_SB) अणु
		fsnotअगरy_conn_sb(conn)->s_fsnotअगरy_mask = 0;
	पूर्ण

	rcu_assign_poपूर्णांकer(*(conn->obj), शून्य);
	conn->obj = शून्य;
	conn->type = FSNOTIFY_OBJ_TYPE_DETACHED;

	वापस inode;
पूर्ण

अटल व्योम fsnotअगरy_final_mark_destroy(काष्ठा fsnotअगरy_mark *mark)
अणु
	काष्ठा fsnotअगरy_group *group = mark->group;

	अगर (WARN_ON_ONCE(!group))
		वापस;
	group->ops->मुक्त_mark(mark);
	fsnotअगरy_put_group(group);
पूर्ण

/* Drop object reference originally held by a connector */
अटल व्योम fsnotअगरy_drop_object(अचिन्हित पूर्णांक type, व्योम *objp)
अणु
	काष्ठा inode *inode;
	काष्ठा super_block *sb;

	अगर (!objp)
		वापस;
	/* Currently only inode references are passed to be dropped */
	अगर (WARN_ON_ONCE(type != FSNOTIFY_OBJ_TYPE_INODE))
		वापस;
	inode = objp;
	sb = inode->i_sb;
	iput(inode);
	अगर (atomic_दीर्घ_dec_and_test(&sb->s_fsnotअगरy_inode_refs))
		wake_up_var(&sb->s_fsnotअगरy_inode_refs);
पूर्ण

व्योम fsnotअगरy_put_mark(काष्ठा fsnotअगरy_mark *mark)
अणु
	काष्ठा fsnotअगरy_mark_connector *conn = READ_ONCE(mark->connector);
	व्योम *objp = शून्य;
	अचिन्हित पूर्णांक type = FSNOTIFY_OBJ_TYPE_DETACHED;
	bool मुक्त_conn = false;

	/* Catch marks that were actually never attached to object */
	अगर (!conn) अणु
		अगर (refcount_dec_and_test(&mark->refcnt))
			fsnotअगरy_final_mark_destroy(mark);
		वापस;
	पूर्ण

	/*
	 * We have to be careful so that traversals of obj_list under lock can
	 * safely grab mark reference.
	 */
	अगर (!refcount_dec_and_lock(&mark->refcnt, &conn->lock))
		वापस;

	hlist_del_init_rcu(&mark->obj_list);
	अगर (hlist_empty(&conn->list)) अणु
		objp = fsnotअगरy_detach_connector_from_object(conn, &type);
		मुक्त_conn = true;
	पूर्ण अन्यथा अणु
		__fsnotअगरy_recalc_mask(conn);
	पूर्ण
	WRITE_ONCE(mark->connector, शून्य);
	spin_unlock(&conn->lock);

	fsnotअगरy_drop_object(type, objp);

	अगर (मुक्त_conn) अणु
		spin_lock(&destroy_lock);
		conn->destroy_next = connector_destroy_list;
		connector_destroy_list = conn;
		spin_unlock(&destroy_lock);
		queue_work(प्रणाली_unbound_wq, &connector_reaper_work);
	पूर्ण
	/*
	 * Note that we didn't update flags telling whether inode cares about
	 * what's happening with children. We update these flags from
	 * __fsnotअगरy_parent() lazily when next event happens on one of our
	 * children.
	 */
	spin_lock(&destroy_lock);
	list_add(&mark->g_list, &destroy_list);
	spin_unlock(&destroy_lock);
	queue_delayed_work(प्रणाली_unbound_wq, &reaper_work,
			   FSNOTIFY_REAPER_DELAY);
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy_put_mark);

/*
 * Get mark reference when we found the mark via lockless traversal of object
 * list. Mark can be alपढ़ोy हटाओd from the list by now and on its way to be
 * destroyed once SRCU period ends.
 *
 * Also pin the group so it करोesn't disappear under us.
 */
अटल bool fsnotअगरy_get_mark_safe(काष्ठा fsnotअगरy_mark *mark)
अणु
	अगर (!mark)
		वापस true;

	अगर (refcount_inc_not_zero(&mark->refcnt)) अणु
		spin_lock(&mark->lock);
		अगर (mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED) अणु
			/* mark is attached, group is still alive then */
			atomic_inc(&mark->group->user_रुकोs);
			spin_unlock(&mark->lock);
			वापस true;
		पूर्ण
		spin_unlock(&mark->lock);
		fsnotअगरy_put_mark(mark);
	पूर्ण
	वापस false;
पूर्ण

/*
 * Puts marks and wakes up group deकाष्ठाion अगर necessary.
 *
 * Pairs with fsnotअगरy_get_mark_safe()
 */
अटल व्योम fsnotअगरy_put_mark_wake(काष्ठा fsnotअगरy_mark *mark)
अणु
	अगर (mark) अणु
		काष्ठा fsnotअगरy_group *group = mark->group;

		fsnotअगरy_put_mark(mark);
		/*
		 * We abuse notअगरication_रुकोq on group shutकरोwn क्रम रुकोing क्रम
		 * all marks pinned when रुकोing क्रम userspace.
		 */
		अगर (atomic_dec_and_test(&group->user_रुकोs) && group->shutकरोwn)
			wake_up(&group->notअगरication_रुकोq);
	पूर्ण
पूर्ण

bool fsnotअगरy_prepare_user_रुको(काष्ठा fsnotअगरy_iter_info *iter_info)
	__releases(&fsnotअगरy_mark_srcu)
अणु
	पूर्णांक type;

	fsnotअगरy_क्रमeach_obj_type(type) अणु
		/* This can fail अगर mark is being हटाओd */
		अगर (!fsnotअगरy_get_mark_safe(iter_info->marks[type])) अणु
			__release(&fsnotअगरy_mark_srcu);
			जाओ fail;
		पूर्ण
	पूर्ण

	/*
	 * Now that both marks are pinned by refcount in the inode / vfsmount
	 * lists, we can drop SRCU lock, and safely resume the list iteration
	 * once userspace वापसs.
	 */
	srcu_पढ़ो_unlock(&fsnotअगरy_mark_srcu, iter_info->srcu_idx);

	वापस true;

fail:
	क्रम (type--; type >= 0; type--)
		fsnotअगरy_put_mark_wake(iter_info->marks[type]);
	वापस false;
पूर्ण

व्योम fsnotअगरy_finish_user_रुको(काष्ठा fsnotअगरy_iter_info *iter_info)
	__acquires(&fsnotअगरy_mark_srcu)
अणु
	पूर्णांक type;

	iter_info->srcu_idx = srcu_पढ़ो_lock(&fsnotअगरy_mark_srcu);
	fsnotअगरy_क्रमeach_obj_type(type)
		fsnotअगरy_put_mark_wake(iter_info->marks[type]);
पूर्ण

/*
 * Mark mark as detached, हटाओ it from group list. Mark still stays in object
 * list until its last reference is dropped. Note that we rely on mark being
 * हटाओd from group list beक्रमe corresponding reference to it is dropped. In
 * particular we rely on mark->connector being valid जबतक we hold
 * group->mark_mutex अगर we found the mark through g_list.
 *
 * Must be called with group->mark_mutex held. The caller must either hold
 * reference to the mark or be रक्षित by fsnotअगरy_mark_srcu.
 */
व्योम fsnotअगरy_detach_mark(काष्ठा fsnotअगरy_mark *mark)
अणु
	काष्ठा fsnotअगरy_group *group = mark->group;

	WARN_ON_ONCE(!mutex_is_locked(&group->mark_mutex));
	WARN_ON_ONCE(!srcu_पढ़ो_lock_held(&fsnotअगरy_mark_srcu) &&
		     refcount_पढ़ो(&mark->refcnt) < 1 +
			!!(mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED));

	spin_lock(&mark->lock);
	/* something अन्यथा alपढ़ोy called this function on this mark */
	अगर (!(mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED)) अणु
		spin_unlock(&mark->lock);
		वापस;
	पूर्ण
	mark->flags &= ~FSNOTIFY_MARK_FLAG_ATTACHED;
	list_del_init(&mark->g_list);
	spin_unlock(&mark->lock);

	/* Drop mark reference acquired in fsnotअगरy_add_mark_locked() */
	fsnotअगरy_put_mark(mark);
पूर्ण

/*
 * Free fsnotअगरy mark. The mark is actually only marked as being मुक्तd.  The
 * मुक्तing is actually happening only once last reference to the mark is
 * dropped from a workqueue which first रुकोs क्रम srcu period end.
 *
 * Caller must have a reference to the mark or be रक्षित by
 * fsnotअगरy_mark_srcu.
 */
व्योम fsnotअगरy_मुक्त_mark(काष्ठा fsnotअगरy_mark *mark)
अणु
	काष्ठा fsnotअगरy_group *group = mark->group;

	spin_lock(&mark->lock);
	/* something अन्यथा alपढ़ोy called this function on this mark */
	अगर (!(mark->flags & FSNOTIFY_MARK_FLAG_ALIVE)) अणु
		spin_unlock(&mark->lock);
		वापस;
	पूर्ण
	mark->flags &= ~FSNOTIFY_MARK_FLAG_ALIVE;
	spin_unlock(&mark->lock);

	/*
	 * Some groups like to know that marks are being मुक्तd.  This is a
	 * callback to the group function to let it know that this mark
	 * is being मुक्तd.
	 */
	अगर (group->ops->मुक्तing_mark)
		group->ops->मुक्तing_mark(mark, group);
पूर्ण

व्योम fsnotअगरy_destroy_mark(काष्ठा fsnotअगरy_mark *mark,
			   काष्ठा fsnotअगरy_group *group)
अणु
	mutex_lock_nested(&group->mark_mutex, SINGLE_DEPTH_NESTING);
	fsnotअगरy_detach_mark(mark);
	mutex_unlock(&group->mark_mutex);
	fsnotअगरy_मुक्त_mark(mark);
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy_destroy_mark);

/*
 * Sorting function क्रम lists of fsnotअगरy marks.
 *
 * Fanotअगरy supports dअगरferent notअगरication classes (reflected as priority of
 * notअगरication group). Events shall be passed to notअगरication groups in
 * decreasing priority order. To achieve this marks in notअगरication lists क्रम
 * inodes and vfsmounts are sorted so that priorities of corresponding groups
 * are descending.
 *
 * Furthermore correct handling of the ignore mask requires processing inode
 * and vfsmount marks of each group together. Using the group address as
 * further sort criterion provides a unique sorting order and thus we can
 * merge inode and vfsmount lists of marks in linear समय and find groups
 * present in both lists.
 *
 * A वापस value of 1 signअगरies that b has priority over a.
 * A वापस value of 0 signअगरies that the two marks have to be handled together.
 * A वापस value of -1 signअगरies that a has priority over b.
 */
पूर्णांक fsnotअगरy_compare_groups(काष्ठा fsnotअगरy_group *a, काष्ठा fsnotअगरy_group *b)
अणु
	अगर (a == b)
		वापस 0;
	अगर (!a)
		वापस 1;
	अगर (!b)
		वापस -1;
	अगर (a->priority < b->priority)
		वापस 1;
	अगर (a->priority > b->priority)
		वापस -1;
	अगर (a < b)
		वापस 1;
	वापस -1;
पूर्ण

अटल पूर्णांक fsnotअगरy_attach_connector_to_object(fsnotअगरy_connp_t *connp,
					       अचिन्हित पूर्णांक type,
					       __kernel_fsid_t *fsid)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा fsnotअगरy_mark_connector *conn;

	conn = kmem_cache_alloc(fsnotअगरy_mark_connector_cachep, GFP_KERNEL);
	अगर (!conn)
		वापस -ENOMEM;
	spin_lock_init(&conn->lock);
	INIT_HLIST_HEAD(&conn->list);
	conn->type = type;
	conn->obj = connp;
	/* Cache fsid of fileप्रणाली containing the object */
	अगर (fsid) अणु
		conn->fsid = *fsid;
		conn->flags = FSNOTIFY_CONN_FLAG_HAS_FSID;
	पूर्ण अन्यथा अणु
		conn->fsid.val[0] = conn->fsid.val[1] = 0;
		conn->flags = 0;
	पूर्ण
	अगर (conn->type == FSNOTIFY_OBJ_TYPE_INODE)
		inode = igrab(fsnotअगरy_conn_inode(conn));
	/*
	 * cmpxchg() provides the barrier so that पढ़ोers of *connp can see
	 * only initialized काष्ठाure
	 */
	अगर (cmpxchg(connp, शून्य, conn)) अणु
		/* Someone अन्यथा created list काष्ठाure क्रम us */
		अगर (inode)
			iput(inode);
		kmem_cache_मुक्त(fsnotअगरy_mark_connector_cachep, conn);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Get mark connector, make sure it is alive and वापस with its lock held.
 * This is क्रम users that get connector poपूर्णांकer from inode or mount. Users that
 * hold reference to a mark on the list may directly lock connector->lock as
 * they are sure list cannot go away under them.
 */
अटल काष्ठा fsnotअगरy_mark_connector *fsnotअगरy_grab_connector(
						fsnotअगरy_connp_t *connp)
अणु
	काष्ठा fsnotअगरy_mark_connector *conn;
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&fsnotअगरy_mark_srcu);
	conn = srcu_dereference(*connp, &fsnotअगरy_mark_srcu);
	अगर (!conn)
		जाओ out;
	spin_lock(&conn->lock);
	अगर (conn->type == FSNOTIFY_OBJ_TYPE_DETACHED) अणु
		spin_unlock(&conn->lock);
		srcu_पढ़ो_unlock(&fsnotअगरy_mark_srcu, idx);
		वापस शून्य;
	पूर्ण
out:
	srcu_पढ़ो_unlock(&fsnotअगरy_mark_srcu, idx);
	वापस conn;
पूर्ण

/*
 * Add mark पूर्णांकo proper place in given list of marks. These marks may be used
 * क्रम the fsnotअगरy backend to determine which event types should be delivered
 * to which group and क्रम which inodes. These marks are ordered according to
 * priority, highest number first, and then by the group's location in memory.
 */
अटल पूर्णांक fsnotअगरy_add_mark_list(काष्ठा fsnotअगरy_mark *mark,
				  fsnotअगरy_connp_t *connp, अचिन्हित पूर्णांक type,
				  पूर्णांक allow_dups, __kernel_fsid_t *fsid)
अणु
	काष्ठा fsnotअगरy_mark *lmark, *last = शून्य;
	काष्ठा fsnotअगरy_mark_connector *conn;
	पूर्णांक cmp;
	पूर्णांक err = 0;

	अगर (WARN_ON(!fsnotअगरy_valid_obj_type(type)))
		वापस -EINVAL;

	/* Backend is expected to check क्रम zero fsid (e.g. पंचांगpfs) */
	अगर (fsid && WARN_ON_ONCE(!fsid->val[0] && !fsid->val[1]))
		वापस -ENODEV;

restart:
	spin_lock(&mark->lock);
	conn = fsnotअगरy_grab_connector(connp);
	अगर (!conn) अणु
		spin_unlock(&mark->lock);
		err = fsnotअगरy_attach_connector_to_object(connp, type, fsid);
		अगर (err)
			वापस err;
		जाओ restart;
	पूर्ण अन्यथा अगर (fsid && !(conn->flags & FSNOTIFY_CONN_FLAG_HAS_FSID)) अणु
		conn->fsid = *fsid;
		/* Pairs with smp_rmb() in fanotअगरy_get_fsid() */
		smp_wmb();
		conn->flags |= FSNOTIFY_CONN_FLAG_HAS_FSID;
	पूर्ण अन्यथा अगर (fsid && (conn->flags & FSNOTIFY_CONN_FLAG_HAS_FSID) &&
		   (fsid->val[0] != conn->fsid.val[0] ||
		    fsid->val[1] != conn->fsid.val[1])) अणु
		/*
		 * Backend is expected to check क्रम non unअगरorm fsid
		 * (e.g. btrfs), but maybe we missed something?
		 * Only allow setting conn->fsid once to non zero fsid.
		 * inotअगरy and non-fid fanotअगरy groups करो not set nor test
		 * conn->fsid.
		 */
		pr_warn_ratelimited("%s: fsid mismatch on object of type %u: "
				    "%x.%x != %x.%x\n", __func__, conn->type,
				    fsid->val[0], fsid->val[1],
				    conn->fsid.val[0], conn->fsid.val[1]);
		err = -EXDEV;
		जाओ out_err;
	पूर्ण

	/* is mark the first mark? */
	अगर (hlist_empty(&conn->list)) अणु
		hlist_add_head_rcu(&mark->obj_list, &conn->list);
		जाओ added;
	पूर्ण

	/* should mark be in the middle of the current list? */
	hlist_क्रम_each_entry(lmark, &conn->list, obj_list) अणु
		last = lmark;

		अगर ((lmark->group == mark->group) &&
		    (lmark->flags & FSNOTIFY_MARK_FLAG_ATTACHED) &&
		    !allow_dups) अणु
			err = -EEXIST;
			जाओ out_err;
		पूर्ण

		cmp = fsnotअगरy_compare_groups(lmark->group, mark->group);
		अगर (cmp >= 0) अणु
			hlist_add_beक्रमe_rcu(&mark->obj_list, &lmark->obj_list);
			जाओ added;
		पूर्ण
	पूर्ण

	BUG_ON(last == शून्य);
	/* mark should be the last entry.  last is the current last entry */
	hlist_add_behind_rcu(&mark->obj_list, &last->obj_list);
added:
	/*
	 * Since connector is attached to object using cmpxchg() we are
	 * guaranteed that connector initialization is fully visible by anyone
	 * seeing mark->connector set.
	 */
	WRITE_ONCE(mark->connector, conn);
out_err:
	spin_unlock(&conn->lock);
	spin_unlock(&mark->lock);
	वापस err;
पूर्ण

/*
 * Attach an initialized mark to a given group and fs object.
 * These marks may be used क्रम the fsnotअगरy backend to determine which
 * event types should be delivered to which group.
 */
पूर्णांक fsnotअगरy_add_mark_locked(काष्ठा fsnotअगरy_mark *mark,
			     fsnotअगरy_connp_t *connp, अचिन्हित पूर्णांक type,
			     पूर्णांक allow_dups, __kernel_fsid_t *fsid)
अणु
	काष्ठा fsnotअगरy_group *group = mark->group;
	पूर्णांक ret = 0;

	BUG_ON(!mutex_is_locked(&group->mark_mutex));

	/*
	 * LOCKING ORDER!!!!
	 * group->mark_mutex
	 * mark->lock
	 * mark->connector->lock
	 */
	spin_lock(&mark->lock);
	mark->flags |= FSNOTIFY_MARK_FLAG_ALIVE | FSNOTIFY_MARK_FLAG_ATTACHED;

	list_add(&mark->g_list, &group->marks_list);
	fsnotअगरy_get_mark(mark); /* क्रम g_list */
	spin_unlock(&mark->lock);

	ret = fsnotअगरy_add_mark_list(mark, connp, type, allow_dups, fsid);
	अगर (ret)
		जाओ err;

	अगर (mark->mask)
		fsnotअगरy_recalc_mask(mark->connector);

	वापस ret;
err:
	spin_lock(&mark->lock);
	mark->flags &= ~(FSNOTIFY_MARK_FLAG_ALIVE |
			 FSNOTIFY_MARK_FLAG_ATTACHED);
	list_del_init(&mark->g_list);
	spin_unlock(&mark->lock);

	fsnotअगरy_put_mark(mark);
	वापस ret;
पूर्ण

पूर्णांक fsnotअगरy_add_mark(काष्ठा fsnotअगरy_mark *mark, fsnotअगरy_connp_t *connp,
		      अचिन्हित पूर्णांक type, पूर्णांक allow_dups, __kernel_fsid_t *fsid)
अणु
	पूर्णांक ret;
	काष्ठा fsnotअगरy_group *group = mark->group;

	mutex_lock(&group->mark_mutex);
	ret = fsnotअगरy_add_mark_locked(mark, connp, type, allow_dups, fsid);
	mutex_unlock(&group->mark_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy_add_mark);

/*
 * Given a list of marks, find the mark associated with given group. If found
 * take a reference to that mark and वापस it, अन्यथा वापस शून्य.
 */
काष्ठा fsnotअगरy_mark *fsnotअगरy_find_mark(fsnotअगरy_connp_t *connp,
					 काष्ठा fsnotअगरy_group *group)
अणु
	काष्ठा fsnotअगरy_mark_connector *conn;
	काष्ठा fsnotअगरy_mark *mark;

	conn = fsnotअगरy_grab_connector(connp);
	अगर (!conn)
		वापस शून्य;

	hlist_क्रम_each_entry(mark, &conn->list, obj_list) अणु
		अगर (mark->group == group &&
		    (mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED)) अणु
			fsnotअगरy_get_mark(mark);
			spin_unlock(&conn->lock);
			वापस mark;
		पूर्ण
	पूर्ण
	spin_unlock(&conn->lock);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy_find_mark);

/* Clear any marks in a group with given type mask */
व्योम fsnotअगरy_clear_marks_by_group(काष्ठा fsnotअगरy_group *group,
				   अचिन्हित पूर्णांक type_mask)
अणु
	काष्ठा fsnotअगरy_mark *lmark, *mark;
	LIST_HEAD(to_मुक्त);
	काष्ठा list_head *head = &to_मुक्त;

	/* Skip selection step अगर we want to clear all marks. */
	अगर (type_mask == FSNOTIFY_OBJ_ALL_TYPES_MASK) अणु
		head = &group->marks_list;
		जाओ clear;
	पूर्ण
	/*
	 * We have to be really careful here. Anyसमय we drop mark_mutex, e.g.
	 * fsnotअगरy_clear_marks_by_inode() can come and मुक्त marks. Even in our
	 * to_मुक्त list so we have to use mark_mutex even when accessing that
	 * list. And मुक्तing mark requires us to drop mark_mutex. So we can
	 * reliably मुक्त only the first mark in the list. That's why we first
	 * move marks to मुक्त to to_मुक्त list in one go and then मुक्त marks in
	 * to_मुक्त list one by one.
	 */
	mutex_lock_nested(&group->mark_mutex, SINGLE_DEPTH_NESTING);
	list_क्रम_each_entry_safe(mark, lmark, &group->marks_list, g_list) अणु
		अगर ((1U << mark->connector->type) & type_mask)
			list_move(&mark->g_list, &to_मुक्त);
	पूर्ण
	mutex_unlock(&group->mark_mutex);

clear:
	जबतक (1) अणु
		mutex_lock_nested(&group->mark_mutex, SINGLE_DEPTH_NESTING);
		अगर (list_empty(head)) अणु
			mutex_unlock(&group->mark_mutex);
			अवरोध;
		पूर्ण
		mark = list_first_entry(head, काष्ठा fsnotअगरy_mark, g_list);
		fsnotअगरy_get_mark(mark);
		fsnotअगरy_detach_mark(mark);
		mutex_unlock(&group->mark_mutex);
		fsnotअगरy_मुक्त_mark(mark);
		fsnotअगरy_put_mark(mark);
	पूर्ण
पूर्ण

/* Destroy all marks attached to an object via connector */
व्योम fsnotअगरy_destroy_marks(fsnotअगरy_connp_t *connp)
अणु
	काष्ठा fsnotअगरy_mark_connector *conn;
	काष्ठा fsnotअगरy_mark *mark, *old_mark = शून्य;
	व्योम *objp;
	अचिन्हित पूर्णांक type;

	conn = fsnotअगरy_grab_connector(connp);
	अगर (!conn)
		वापस;
	/*
	 * We have to be careful since we can race with e.g.
	 * fsnotअगरy_clear_marks_by_group() and once we drop the conn->lock, the
	 * list can get modअगरied. However we are holding mark reference and
	 * thus our mark cannot be हटाओd from obj_list so we can जारी
	 * iteration after regaining conn->lock.
	 */
	hlist_क्रम_each_entry(mark, &conn->list, obj_list) अणु
		fsnotअगरy_get_mark(mark);
		spin_unlock(&conn->lock);
		अगर (old_mark)
			fsnotअगरy_put_mark(old_mark);
		old_mark = mark;
		fsnotअगरy_destroy_mark(mark, mark->group);
		spin_lock(&conn->lock);
	पूर्ण
	/*
	 * Detach list from object now so that we करोn't pin inode until all
	 * mark references get dropped. It would lead to strange results such
	 * as delaying inode deletion or blocking unmount.
	 */
	objp = fsnotअगरy_detach_connector_from_object(conn, &type);
	spin_unlock(&conn->lock);
	अगर (old_mark)
		fsnotअगरy_put_mark(old_mark);
	fsnotअगरy_drop_object(type, objp);
पूर्ण

/*
 * Nothing fancy, just initialize lists and locks and counters.
 */
व्योम fsnotअगरy_init_mark(काष्ठा fsnotअगरy_mark *mark,
			काष्ठा fsnotअगरy_group *group)
अणु
	स_रखो(mark, 0, माप(*mark));
	spin_lock_init(&mark->lock);
	refcount_set(&mark->refcnt, 1);
	fsnotअगरy_get_group(group);
	mark->group = group;
	WRITE_ONCE(mark->connector, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy_init_mark);

/*
 * Destroy all marks in destroy_list, रुकोs क्रम SRCU period to finish beक्रमe
 * actually मुक्तing marks.
 */
अटल व्योम fsnotअगरy_mark_destroy_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fsnotअगरy_mark *mark, *next;
	काष्ठा list_head निजी_destroy_list;

	spin_lock(&destroy_lock);
	/* exchange the list head */
	list_replace_init(&destroy_list, &निजी_destroy_list);
	spin_unlock(&destroy_lock);

	synchronize_srcu(&fsnotअगरy_mark_srcu);

	list_क्रम_each_entry_safe(mark, next, &निजी_destroy_list, g_list) अणु
		list_del_init(&mark->g_list);
		fsnotअगरy_final_mark_destroy(mark);
	पूर्ण
पूर्ण

/* Wait क्रम all marks queued क्रम deकाष्ठाion to be actually destroyed */
व्योम fsnotअगरy_रुको_marks_destroyed(व्योम)
अणु
	flush_delayed_work(&reaper_work);
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy_रुको_marks_destroyed);
