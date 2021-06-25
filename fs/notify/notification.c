<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2008 Red Hat, Inc., Eric Paris <eparis@redhat.com>
 */

/*
 * Basic idea behind the notअगरication queue: An fsnotअगरy group (like inotअगरy)
 * sends the userspace notअगरication about events asynchronously some समय after
 * the event happened.  When inotअगरy माला_लो an event it will need to add that
 * event to the group notअगरy queue.  Since a single event might need to be on
 * multiple group's notification queues we can't add the event directly to each
 * queue and instead add a small "event_holder" to each queue.  This event_holder
 * has a poपूर्णांकer back to the original event.  Since the majority of events are
 * going to end up on one, and only one, notअगरication queue we embed one
 * event_holder पूर्णांकo each event.  This means we have a single allocation instead
 * of always needing two.  If the embedded event_holder is alपढ़ोy in use by
 * another group a new event_holder (from fsnotअगरy_event_holder_cachep) will be
 * allocated and used.
 */

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/mutex.h>
#समावेश <linux/namei.h>
#समावेश <linux/path.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/atomic.h>

#समावेश <linux/fsnotअगरy_backend.h>
#समावेश "fsnotify.h"

अटल atomic_t fsnotअगरy_sync_cookie = ATOMIC_INIT(0);

/**
 * fsnotअगरy_get_cookie - वापस a unique cookie क्रम use in synchronizing events.
 * Called from fsnotअगरy_move, which is अंतरभूतd पूर्णांकo fileप्रणाली modules.
 */
u32 fsnotअगरy_get_cookie(व्योम)
अणु
	वापस atomic_inc_वापस(&fsnotअगरy_sync_cookie);
पूर्ण
EXPORT_SYMBOL_GPL(fsnotअगरy_get_cookie);

व्योम fsnotअगरy_destroy_event(काष्ठा fsnotअगरy_group *group,
			    काष्ठा fsnotअगरy_event *event)
अणु
	/* Overflow events are per-group and we करोn't want to मुक्त them */
	अगर (!event || event == group->overflow_event)
		वापस;
	/*
	 * If the event is still queued, we have a problem... Do an unreliable
	 * lockless check first to aव्योम locking in the common हाल. The
	 * locking may be necessary क्रम permission events which got हटाओd
	 * from the list by a dअगरferent CPU than the one मुक्तing the event.
	 */
	अगर (!list_empty(&event->list)) अणु
		spin_lock(&group->notअगरication_lock);
		WARN_ON(!list_empty(&event->list));
		spin_unlock(&group->notअगरication_lock);
	पूर्ण
	group->ops->मुक्त_event(event);
पूर्ण

/*
 * Try to add an event to the notअगरication queue.
 * The group can later pull this event off the queue to deal with.
 * The group can use the @merge hook to merge the event with a queued event.
 * The group can use the @insert hook to insert the event पूर्णांकo hash table.
 * The function वापसs:
 * 0 अगर the event was added to a queue
 * 1 अगर the event was merged with some other queued event
 * 2 अगर the event was not queued - either the queue of events has overflown
 *   or the group is shutting करोwn.
 */
पूर्णांक fsnotअगरy_add_event(काष्ठा fsnotअगरy_group *group,
		       काष्ठा fsnotअगरy_event *event,
		       पूर्णांक (*merge)(काष्ठा fsnotअगरy_group *,
				    काष्ठा fsnotअगरy_event *),
		       व्योम (*insert)(काष्ठा fsnotअगरy_group *,
				      काष्ठा fsnotअगरy_event *))
अणु
	पूर्णांक ret = 0;
	काष्ठा list_head *list = &group->notअगरication_list;

	pr_debug("%s: group=%p event=%p\n", __func__, group, event);

	spin_lock(&group->notअगरication_lock);

	अगर (group->shutकरोwn) अणु
		spin_unlock(&group->notअगरication_lock);
		वापस 2;
	पूर्ण

	अगर (event == group->overflow_event ||
	    group->q_len >= group->max_events) अणु
		ret = 2;
		/* Queue overflow event only अगर it isn't alपढ़ोy queued */
		अगर (!list_empty(&group->overflow_event->list)) अणु
			spin_unlock(&group->notअगरication_lock);
			वापस ret;
		पूर्ण
		event = group->overflow_event;
		जाओ queue;
	पूर्ण

	अगर (!list_empty(list) && merge) अणु
		ret = merge(group, event);
		अगर (ret) अणु
			spin_unlock(&group->notअगरication_lock);
			वापस ret;
		पूर्ण
	पूर्ण

queue:
	group->q_len++;
	list_add_tail(&event->list, list);
	अगर (insert)
		insert(group, event);
	spin_unlock(&group->notअगरication_lock);

	wake_up(&group->notअगरication_रुकोq);
	समाप्त_fasync(&group->fsn_fa, SIGIO, POLL_IN);
	वापस ret;
पूर्ण

व्योम fsnotअगरy_हटाओ_queued_event(काष्ठा fsnotअगरy_group *group,
				  काष्ठा fsnotअगरy_event *event)
अणु
	निश्चित_spin_locked(&group->notअगरication_lock);
	/*
	 * We need to init list head क्रम the हाल of overflow event so that
	 * check in fsnotअगरy_add_event() works
	 */
	list_del_init(&event->list);
	group->q_len--;
पूर्ण

/*
 * Return the first event on the notअगरication list without removing it.
 * Returns शून्य अगर the list is empty.
 */
काष्ठा fsnotअगरy_event *fsnotअगरy_peek_first_event(काष्ठा fsnotअगरy_group *group)
अणु
	निश्चित_spin_locked(&group->notअगरication_lock);

	अगर (fsnotअगरy_notअगरy_queue_is_empty(group))
		वापस शून्य;

	वापस list_first_entry(&group->notअगरication_list,
				काष्ठा fsnotअगरy_event, list);
पूर्ण

/*
 * Remove and वापस the first event from the notअगरication list.  It is the
 * responsibility of the caller to destroy the obtained event
 */
काष्ठा fsnotअगरy_event *fsnotअगरy_हटाओ_first_event(काष्ठा fsnotअगरy_group *group)
अणु
	काष्ठा fsnotअगरy_event *event = fsnotअगरy_peek_first_event(group);

	अगर (!event)
		वापस शून्य;

	pr_debug("%s: group=%p event=%p\n", __func__, group, event);

	fsnotअगरy_हटाओ_queued_event(group, event);

	वापस event;
पूर्ण

/*
 * Called when a group is being torn करोwn to clean up any outstanding
 * event notअगरications.
 */
व्योम fsnotअगरy_flush_notअगरy(काष्ठा fsnotअगरy_group *group)
अणु
	काष्ठा fsnotअगरy_event *event;

	spin_lock(&group->notअगरication_lock);
	जबतक (!fsnotअगरy_notअगरy_queue_is_empty(group)) अणु
		event = fsnotअगरy_हटाओ_first_event(group);
		spin_unlock(&group->notअगरication_lock);
		fsnotअगरy_destroy_event(group, event);
		spin_lock(&group->notअगरication_lock);
	पूर्ण
	spin_unlock(&group->notअगरication_lock);
पूर्ण
