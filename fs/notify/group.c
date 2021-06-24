<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2008 Red Hat, Inc., Eric Paris <eparis@redhat.com>
 */

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/srcu.h>
#समावेश <linux/rculist.h>
#समावेश <linux/रुको.h>
#समावेश <linux/memcontrol.h>

#समावेश <linux/fsnotअगरy_backend.h>
#समावेश "fsnotify.h"

#समावेश <linux/atomic.h>

/*
 * Final मुक्तing of a group
 */
अटल व्योम fsnotअगरy_final_destroy_group(काष्ठा fsnotअगरy_group *group)
अणु
	अगर (group->ops->मुक्त_group_priv)
		group->ops->मुक्त_group_priv(group);

	mem_cgroup_put(group->memcg);
	mutex_destroy(&group->mark_mutex);

	kमुक्त(group);
पूर्ण

/*
 * Stop queueing new events क्रम this group. Once this function वापसs
 * fsnotअगरy_add_event() will not add any new events to the group's queue.
 */
व्योम fsnotअगरy_group_stop_queueing(काष्ठा fsnotअगरy_group *group)
अणु
	spin_lock(&group->notअगरication_lock);
	group->shutकरोwn = true;
	spin_unlock(&group->notअगरication_lock);
पूर्ण

/*
 * Trying to get rid of a group. Remove all marks, flush all events and release
 * the group reference.
 * Note that another thपढ़ो calling fsnotअगरy_clear_marks_by_group() may still
 * hold a ref to the group.
 */
व्योम fsnotअगरy_destroy_group(काष्ठा fsnotअगरy_group *group)
अणु
	/*
	 * Stop queueing new events. The code below is careful enough to not
	 * require this but fanotअगरy needs to stop queuing events even beक्रमe
	 * fsnotअगरy_destroy_group() is called and this makes the other callers
	 * of fsnotअगरy_destroy_group() to see the same behavior.
	 */
	fsnotअगरy_group_stop_queueing(group);

	/* Clear all marks क्रम this group and queue them क्रम deकाष्ठाion */
	fsnotअगरy_clear_marks_by_group(group, FSNOTIFY_OBJ_ALL_TYPES_MASK);

	/*
	 * Some marks can still be pinned when रुकोing क्रम response from
	 * userspace. Wait क्रम those now. fsnotअगरy_prepare_user_रुको() will
	 * not succeed now so this रुको is race-मुक्त.
	 */
	रुको_event(group->notअगरication_रुकोq, !atomic_पढ़ो(&group->user_रुकोs));

	/*
	 * Wait until all marks get really destroyed. We could actually destroy
	 * them ourselves instead of रुकोing क्रम worker to करो it, however that
	 * would be racy as worker can alपढ़ोy be processing some marks beक्रमe
	 * we even entered fsnotअगरy_destroy_group().
	 */
	fsnotअगरy_रुको_marks_destroyed();

	/*
	 * Since we have रुकोed क्रम fsnotअगरy_mark_srcu in
	 * fsnotअगरy_mark_destroy_list() there can be no outstanding event
	 * notअगरication against this group. So clearing the notअगरication queue
	 * of all events is reliable now.
	 */
	fsnotअगरy_flush_notअगरy(group);

	/*
	 * Destroy overflow event (we cannot use fsnotअगरy_destroy_event() as
	 * that deliberately ignores overflow events.
	 */
	अगर (group->overflow_event)
		group->ops->मुक्त_event(group->overflow_event);

	fsnotअगरy_put_group(group);
पूर्ण

/*
 * Get reference to a group.
 */
व्योम fsnotअगरy_get_group(काष्ठा fsnotअगरy_group *group)
अणु
	refcount_inc(&group->refcnt);
पूर्ण

/*
 * Drop a reference to a group.  Free it अगर it's through.
 */
व्योम fsnotअगरy_put_group(काष्ठा fsnotअगरy_group *group)
अणु
	अगर (refcount_dec_and_test(&group->refcnt))
		fsnotअगरy_final_destroy_group(group);
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy_put_group);

अटल काष्ठा fsnotअगरy_group *__fsnotअगरy_alloc_group(
				स्थिर काष्ठा fsnotअगरy_ops *ops, gfp_t gfp)
अणु
	काष्ठा fsnotअगरy_group *group;

	group = kzalloc(माप(काष्ठा fsnotअगरy_group), gfp);
	अगर (!group)
		वापस ERR_PTR(-ENOMEM);

	/* set to 0 when there a no बाह्यal references to this group */
	refcount_set(&group->refcnt, 1);
	atomic_set(&group->user_रुकोs, 0);

	spin_lock_init(&group->notअगरication_lock);
	INIT_LIST_HEAD(&group->notअगरication_list);
	init_रुकोqueue_head(&group->notअगरication_रुकोq);
	group->max_events = अच_पूर्णांक_उच्च;

	mutex_init(&group->mark_mutex);
	INIT_LIST_HEAD(&group->marks_list);

	group->ops = ops;

	वापस group;
पूर्ण

/*
 * Create a new fsnotअगरy_group and hold a reference क्रम the group वापसed.
 */
काष्ठा fsnotअगरy_group *fsnotअगरy_alloc_group(स्थिर काष्ठा fsnotअगरy_ops *ops)
अणु
	वापस __fsnotअगरy_alloc_group(ops, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy_alloc_group);

/*
 * Create a new fsnotअगरy_group and hold a reference क्रम the group वापसed.
 */
काष्ठा fsnotअगरy_group *fsnotअगरy_alloc_user_group(स्थिर काष्ठा fsnotअगरy_ops *ops)
अणु
	वापस __fsnotअगरy_alloc_group(ops, GFP_KERNEL_ACCOUNT);
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy_alloc_user_group);

पूर्णांक fsnotअगरy_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा fsnotअगरy_group *group = file->निजी_data;

	वापस fasync_helper(fd, file, on, &group->fsn_fa) >= 0 ? 0 : -EIO;
पूर्ण
