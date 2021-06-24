<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * fs/inotअगरy_user.c - inotअगरy support क्रम userspace
 *
 * Authors:
 *	John McCutchan	<ttb@tentacle.dhs.org>
 *	Robert Love	<rml@novell.com>
 *
 * Copyright (C) 2005 John McCutchan
 * Copyright 2006 Hewlett-Packard Development Company, L.P.
 *
 * Copyright (C) 2009 Eric Paris <Red Hat Inc>
 * inotअगरy was largely reग_लिखोn to make use of the fsnotअगरy infraकाष्ठाure
 */

#समावेश <linux/dcache.h> /* d_unlinked */
#समावेश <linux/fs.h> /* काष्ठा inode */
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/inotअगरy.h>
#समावेश <linux/path.h> /* काष्ठा path */
#समावेश <linux/slab.h> /* kmem_* */
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/user.h>
#समावेश <linux/sched/mm.h>

#समावेश "inotify.h"

/*
 * Check अगर 2 events contain the same inक्रमmation.
 */
अटल bool event_compare(काष्ठा fsnotअगरy_event *old_fsn,
			  काष्ठा fsnotअगरy_event *new_fsn)
अणु
	काष्ठा inotअगरy_event_info *old, *new;

	old = INOTIFY_E(old_fsn);
	new = INOTIFY_E(new_fsn);
	अगर (old->mask & FS_IN_IGNORED)
		वापस false;
	अगर ((old->mask == new->mask) &&
	    (old->wd == new->wd) &&
	    (old->name_len == new->name_len) &&
	    (!old->name_len || !म_भेद(old->name, new->name)))
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक inotअगरy_merge(काष्ठा fsnotअगरy_group *group,
			 काष्ठा fsnotअगरy_event *event)
अणु
	काष्ठा list_head *list = &group->notअगरication_list;
	काष्ठा fsnotअगरy_event *last_event;

	last_event = list_entry(list->prev, काष्ठा fsnotअगरy_event, list);
	वापस event_compare(last_event, event);
पूर्ण

पूर्णांक inotअगरy_handle_inode_event(काष्ठा fsnotअगरy_mark *inode_mark, u32 mask,
			       काष्ठा inode *inode, काष्ठा inode *dir,
			       स्थिर काष्ठा qstr *name, u32 cookie)
अणु
	काष्ठा inotअगरy_inode_mark *i_mark;
	काष्ठा inotअगरy_event_info *event;
	काष्ठा fsnotअगरy_event *fsn_event;
	काष्ठा fsnotअगरy_group *group = inode_mark->group;
	पूर्णांक ret;
	पूर्णांक len = 0;
	पूर्णांक alloc_len = माप(काष्ठा inotअगरy_event_info);
	काष्ठा mem_cgroup *old_memcg;

	अगर (name) अणु
		len = name->len;
		alloc_len += len + 1;
	पूर्ण

	pr_debug("%s: group=%p mark=%p mask=%x\n", __func__, group, inode_mark,
		 mask);

	i_mark = container_of(inode_mark, काष्ठा inotअगरy_inode_mark,
			      fsn_mark);

	/*
	 * Whoever is पूर्णांकerested in the event, pays क्रम the allocation. Do not
	 * trigger OOM समाप्तer in the target monitoring memcg as it may have
	 * security repercussion.
	 */
	old_memcg = set_active_memcg(group->memcg);
	event = kदो_स्मृति(alloc_len, GFP_KERNEL_ACCOUNT | __GFP_RETRY_MAYFAIL);
	set_active_memcg(old_memcg);

	अगर (unlikely(!event)) अणु
		/*
		 * Treat lost event due to ENOMEM the same way as queue
		 * overflow to let userspace know event was lost.
		 */
		fsnotअगरy_queue_overflow(group);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * We now report FS_ISसूची flag with MOVE_SELF and DELETE_SELF events
	 * क्रम fanotअगरy. inotअगरy never reported IN_ISसूची with those events.
	 * It looks like an oversight, but to aव्योम the risk of अवरोधing
	 * existing inotअगरy programs, mask the flag out from those events.
	 */
	अगर (mask & (IN_MOVE_SELF | IN_DELETE_SELF))
		mask &= ~IN_ISसूची;

	fsn_event = &event->fse;
	fsnotअगरy_init_event(fsn_event);
	event->mask = mask;
	event->wd = i_mark->wd;
	event->sync_cookie = cookie;
	event->name_len = len;
	अगर (len)
		म_नकल(event->name, name->name);

	ret = fsnotअगरy_add_event(group, fsn_event, inotअगरy_merge, शून्य);
	अगर (ret) अणु
		/* Our event wasn't used in the end. Free it. */
		fsnotअगरy_destroy_event(group, fsn_event);
	पूर्ण

	अगर (inode_mark->mask & IN_ONESHOT)
		fsnotअगरy_destroy_mark(inode_mark, group);

	वापस 0;
पूर्ण

अटल व्योम inotअगरy_मुक्तing_mark(काष्ठा fsnotअगरy_mark *fsn_mark, काष्ठा fsnotअगरy_group *group)
अणु
	inotअगरy_ignored_and_हटाओ_idr(fsn_mark, group);
पूर्ण

/*
 * This is NEVER supposed to be called.  Inotअगरy marks should either have been
 * हटाओd from the idr when the watch was हटाओd or in the
 * fsnotअगरy_destroy_mark_by_group() call when the inotअगरy instance was being
 * torn करोwn.  This is only called अगर the idr is about to be मुक्तd but there
 * are still marks in it.
 */
अटल पूर्णांक idr_callback(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	काष्ठा fsnotअगरy_mark *fsn_mark;
	काष्ठा inotअगरy_inode_mark *i_mark;
	अटल bool warned = false;

	अगर (warned)
		वापस 0;

	warned = true;
	fsn_mark = p;
	i_mark = container_of(fsn_mark, काष्ठा inotअगरy_inode_mark, fsn_mark);

	WARN(1, "inotify closing but id=%d for fsn_mark=%p in group=%p still in "
		"idr.  Probably leaking memory\n", id, p, data);

	/*
	 * I'm taking the liberty of assuming that the mark in question is a
	 * valid address and I'm dereferencing it.  This might help to figure
	 * out why we got here and the panic is no worse than the original
	 * BUG() that was here.
	 */
	अगर (fsn_mark)
		prपूर्णांकk(KERN_WARNING "fsn_mark->group=%p wd=%d\n",
			fsn_mark->group, i_mark->wd);
	वापस 0;
पूर्ण

अटल व्योम inotअगरy_मुक्त_group_priv(काष्ठा fsnotअगरy_group *group)
अणु
	/* ideally the idr is empty and we won't hit the BUG in the callback */
	idr_क्रम_each(&group->inotअगरy_data.idr, idr_callback, group);
	idr_destroy(&group->inotअगरy_data.idr);
	अगर (group->inotअगरy_data.ucounts)
		dec_inotअगरy_instances(group->inotअगरy_data.ucounts);
पूर्ण

अटल व्योम inotअगरy_मुक्त_event(काष्ठा fsnotअगरy_event *fsn_event)
अणु
	kमुक्त(INOTIFY_E(fsn_event));
पूर्ण

/* ding करोng the mark is dead */
अटल व्योम inotअगरy_मुक्त_mark(काष्ठा fsnotअगरy_mark *fsn_mark)
अणु
	काष्ठा inotअगरy_inode_mark *i_mark;

	i_mark = container_of(fsn_mark, काष्ठा inotअगरy_inode_mark, fsn_mark);

	kmem_cache_मुक्त(inotअगरy_inode_mark_cachep, i_mark);
पूर्ण

स्थिर काष्ठा fsnotअगरy_ops inotअगरy_fsnotअगरy_ops = अणु
	.handle_inode_event = inotअगरy_handle_inode_event,
	.मुक्त_group_priv = inotअगरy_मुक्त_group_priv,
	.मुक्त_event = inotअगरy_मुक्त_event,
	.मुक्तing_mark = inotअगरy_मुक्तing_mark,
	.मुक्त_mark = inotअगरy_मुक्त_mark,
पूर्ण;
