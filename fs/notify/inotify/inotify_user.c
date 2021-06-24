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

#समावेश <linux/file.h>
#समावेश <linux/fs.h> /* काष्ठा inode */
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h> /* fs_initcall */
#समावेश <linux/inotअगरy.h>
#समावेश <linux/kernel.h> /* roundup() */
#समावेश <linux/namei.h> /* LOOKUP_FOLLOW */
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h> /* काष्ठा kmem_cache */
#समावेश <linux/syscalls.h>
#समावेश <linux/types.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/poll.h>
#समावेश <linux/रुको.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/security.h>

#समावेश "inotify.h"
#समावेश "../fdinfo.h"

#समावेश <यंत्र/ioctls.h>

/*
 * An inotअगरy watch requires allocating an inotअगरy_inode_mark काष्ठाure as
 * well as pinning the watched inode. Doubling the size of a VFS inode
 * should be more than enough to cover the additional fileप्रणाली inode
 * size increase.
 */
#घोषणा INOTIFY_WATCH_COST	(माप(काष्ठा inotअगरy_inode_mark) + \
				 2 * माप(काष्ठा inode))

/* configurable via /proc/sys/fs/inotअगरy/ */
अटल पूर्णांक inotअगरy_max_queued_events __पढ़ो_mostly;

काष्ठा kmem_cache *inotअगरy_inode_mark_cachep __पढ़ो_mostly;

#अगर_घोषित CONFIG_SYSCTL

#समावेश <linux/sysctl.h>

काष्ठा ctl_table inotअगरy_table[] = अणु
	अणु
		.procname	= "max_user_instances",
		.data		= &init_user_ns.ucount_max[UCOUNT_INOTIFY_INSTANCES],
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "max_user_watches",
		.data		= &init_user_ns.ucount_max[UCOUNT_INOTIFY_WATCHES],
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "max_queued_events",
		.data		= &inotअगरy_max_queued_events,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO
	पूर्ण,
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_SYSCTL */

अटल अंतरभूत __u32 inotअगरy_arg_to_mask(काष्ठा inode *inode, u32 arg)
अणु
	__u32 mask;

	/*
	 * Everything should accept their own ignored and should receive events
	 * when the inode is unmounted.  All directories care about children.
	 */
	mask = (FS_IN_IGNORED | FS_UNMOUNT);
	अगर (S_ISसूची(inode->i_mode))
		mask |= FS_EVENT_ON_CHILD;

	/* mask off the flags used to खोलो the fd */
	mask |= (arg & (IN_ALL_EVENTS | IN_ONESHOT | IN_EXCL_UNLINK));

	वापस mask;
पूर्ण

अटल अंतरभूत u32 inotअगरy_mask_to_arg(__u32 mask)
अणु
	वापस mask & (IN_ALL_EVENTS | IN_ISसूची | IN_UNMOUNT | IN_IGNORED |
		       IN_Q_OVERFLOW);
पूर्ण

/* पूर्णांकofiy userspace file descriptor functions */
अटल __poll_t inotअगरy_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा fsnotअगरy_group *group = file->निजी_data;
	__poll_t ret = 0;

	poll_रुको(file, &group->notअगरication_रुकोq, रुको);
	spin_lock(&group->notअगरication_lock);
	अगर (!fsnotअगरy_notअगरy_queue_is_empty(group))
		ret = EPOLLIN | EPOLLRDNORM;
	spin_unlock(&group->notअगरication_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक round_event_name_len(काष्ठा fsnotअगरy_event *fsn_event)
अणु
	काष्ठा inotअगरy_event_info *event;

	event = INOTIFY_E(fsn_event);
	अगर (!event->name_len)
		वापस 0;
	वापस roundup(event->name_len + 1, माप(काष्ठा inotअगरy_event));
पूर्ण

/*
 * Get an inotअगरy_kernel_event अगर one exists and is small
 * enough to fit in "count". Return an error poपूर्णांकer अगर
 * not large enough.
 *
 * Called with the group->notअगरication_lock held.
 */
अटल काष्ठा fsnotअगरy_event *get_one_event(काष्ठा fsnotअगरy_group *group,
					    माप_प्रकार count)
अणु
	माप_प्रकार event_size = माप(काष्ठा inotअगरy_event);
	काष्ठा fsnotअगरy_event *event;

	event = fsnotअगरy_peek_first_event(group);
	अगर (!event)
		वापस शून्य;

	pr_debug("%s: group=%p event=%p\n", __func__, group, event);

	event_size += round_event_name_len(event);
	अगर (event_size > count)
		वापस ERR_PTR(-EINVAL);

	/* held the notअगरication_lock the whole समय, so this is the
	 * same event we peeked above */
	fsnotअगरy_हटाओ_first_event(group);

	वापस event;
पूर्ण

/*
 * Copy an event to user space, वापसing how much we copied.
 *
 * We alपढ़ोy checked that the event size is smaller than the
 * buffer we had in "get_one_event()" above.
 */
अटल sमाप_प्रकार copy_event_to_user(काष्ठा fsnotअगरy_group *group,
				  काष्ठा fsnotअगरy_event *fsn_event,
				  अक्षर __user *buf)
अणु
	काष्ठा inotअगरy_event inotअगरy_event;
	काष्ठा inotअगरy_event_info *event;
	माप_प्रकार event_size = माप(काष्ठा inotअगरy_event);
	माप_प्रकार name_len;
	माप_प्रकार pad_name_len;

	pr_debug("%s: group=%p event=%p\n", __func__, group, fsn_event);

	event = INOTIFY_E(fsn_event);
	name_len = event->name_len;
	/*
	 * round up name length so it is a multiple of event_size
	 * plus an extra byte क्रम the terminating '\0'.
	 */
	pad_name_len = round_event_name_len(fsn_event);
	inotअगरy_event.len = pad_name_len;
	inotअगरy_event.mask = inotअगरy_mask_to_arg(event->mask);
	inotअगरy_event.wd = event->wd;
	inotअगरy_event.cookie = event->sync_cookie;

	/* send the मुख्य event */
	अगर (copy_to_user(buf, &inotअगरy_event, event_size))
		वापस -EFAULT;

	buf += event_size;

	/*
	 * fsnotअगरy only stores the pathname, so here we have to send the pathname
	 * and then pad that pathname out to a multiple of माप(inotअगरy_event)
	 * with zeros.
	 */
	अगर (pad_name_len) अणु
		/* copy the path name */
		अगर (copy_to_user(buf, event->name, name_len))
			वापस -EFAULT;
		buf += name_len;

		/* fill userspace with 0's */
		अगर (clear_user(buf, pad_name_len - name_len))
			वापस -EFAULT;
		event_size += pad_name_len;
	पूर्ण

	वापस event_size;
पूर्ण

अटल sमाप_प्रकार inotअगरy_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा fsnotअगरy_group *group;
	काष्ठा fsnotअगरy_event *kevent;
	अक्षर __user *start;
	पूर्णांक ret;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	start = buf;
	group = file->निजी_data;

	add_रुको_queue(&group->notअगरication_रुकोq, &रुको);
	जबतक (1) अणु
		spin_lock(&group->notअगरication_lock);
		kevent = get_one_event(group, count);
		spin_unlock(&group->notअगरication_lock);

		pr_debug("%s: group=%p kevent=%p\n", __func__, group, kevent);

		अगर (kevent) अणु
			ret = PTR_ERR(kevent);
			अगर (IS_ERR(kevent))
				अवरोध;
			ret = copy_event_to_user(group, kevent, buf);
			fsnotअगरy_destroy_event(group, kevent);
			अगर (ret < 0)
				अवरोध;
			buf += ret;
			count -= ret;
			जारी;
		पूर्ण

		ret = -EAGAIN;
		अगर (file->f_flags & O_NONBLOCK)
			अवरोध;
		ret = -ERESTARTSYS;
		अगर (संकेत_pending(current))
			अवरोध;

		अगर (start != buf)
			अवरोध;

		रुको_woken(&रुको, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	पूर्ण
	हटाओ_रुको_queue(&group->notअगरication_रुकोq, &रुको);

	अगर (start != buf && ret != -EFAULT)
		ret = buf - start;
	वापस ret;
पूर्ण

अटल पूर्णांक inotअगरy_release(काष्ठा inode *ignored, काष्ठा file *file)
अणु
	काष्ठा fsnotअगरy_group *group = file->निजी_data;

	pr_debug("%s: group=%p\n", __func__, group);

	/* मुक्त this group, matching get was inotअगरy_init->fsnotअगरy_obtain_group */
	fsnotअगरy_destroy_group(group);

	वापस 0;
पूर्ण

अटल दीर्घ inotअगरy_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा fsnotअगरy_group *group;
	काष्ठा fsnotअगरy_event *fsn_event;
	व्योम __user *p;
	पूर्णांक ret = -ENOTTY;
	माप_प्रकार send_len = 0;

	group = file->निजी_data;
	p = (व्योम __user *) arg;

	pr_debug("%s: group=%p cmd=%u\n", __func__, group, cmd);

	चयन (cmd) अणु
	हाल FIONREAD:
		spin_lock(&group->notअगरication_lock);
		list_क्रम_each_entry(fsn_event, &group->notअगरication_list,
				    list) अणु
			send_len += माप(काष्ठा inotअगरy_event);
			send_len += round_event_name_len(fsn_event);
		पूर्ण
		spin_unlock(&group->notअगरication_lock);
		ret = put_user(send_len, (पूर्णांक __user *) p);
		अवरोध;
#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
	हाल INOTIFY_IOC_SETNEXTWD:
		ret = -EINVAL;
		अगर (arg >= 1 && arg <= पूर्णांक_उच्च) अणु
			काष्ठा inotअगरy_group_निजी_data *data;

			data = &group->inotअगरy_data;
			spin_lock(&data->idr_lock);
			idr_set_cursor(&data->idr, (अचिन्हित पूर्णांक)arg);
			spin_unlock(&data->idr_lock);
			ret = 0;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* CONFIG_CHECKPOINT_RESTORE */
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations inotअगरy_fops = अणु
	.show_fdinfo	= inotअगरy_show_fdinfo,
	.poll		= inotअगरy_poll,
	.पढ़ो		= inotअगरy_पढ़ो,
	.fasync		= fsnotअगरy_fasync,
	.release	= inotअगरy_release,
	.unlocked_ioctl	= inotअगरy_ioctl,
	.compat_ioctl	= inotअगरy_ioctl,
	.llseek		= noop_llseek,
पूर्ण;


/*
 * find_inode - resolve a user-given path to a specअगरic inode
 */
अटल पूर्णांक inotअगरy_find_inode(स्थिर अक्षर __user *स_नाम, काष्ठा path *path,
						अचिन्हित पूर्णांक flags, __u64 mask)
अणु
	पूर्णांक error;

	error = user_path_at(AT_FDCWD, स_नाम, flags, path);
	अगर (error)
		वापस error;
	/* you can only watch an inode अगर you have पढ़ो permissions on it */
	error = path_permission(path, MAY_READ);
	अगर (error) अणु
		path_put(path);
		वापस error;
	पूर्ण
	error = security_path_notअगरy(path, mask,
				FSNOTIFY_OBJ_TYPE_INODE);
	अगर (error)
		path_put(path);

	वापस error;
पूर्ण

अटल पूर्णांक inotअगरy_add_to_idr(काष्ठा idr *idr, spinlock_t *idr_lock,
			      काष्ठा inotअगरy_inode_mark *i_mark)
अणु
	पूर्णांक ret;

	idr_preload(GFP_KERNEL);
	spin_lock(idr_lock);

	ret = idr_alloc_cyclic(idr, i_mark, 1, 0, GFP_NOWAIT);
	अगर (ret >= 0) अणु
		/* we added the mark to the idr, take a reference */
		i_mark->wd = ret;
		fsnotअगरy_get_mark(&i_mark->fsn_mark);
	पूर्ण

	spin_unlock(idr_lock);
	idr_preload_end();
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल काष्ठा inotअगरy_inode_mark *inotअगरy_idr_find_locked(काष्ठा fsnotअगरy_group *group,
								पूर्णांक wd)
अणु
	काष्ठा idr *idr = &group->inotअगरy_data.idr;
	spinlock_t *idr_lock = &group->inotअगरy_data.idr_lock;
	काष्ठा inotअगरy_inode_mark *i_mark;

	निश्चित_spin_locked(idr_lock);

	i_mark = idr_find(idr, wd);
	अगर (i_mark) अणु
		काष्ठा fsnotअगरy_mark *fsn_mark = &i_mark->fsn_mark;

		fsnotअगरy_get_mark(fsn_mark);
		/* One ref क्रम being in the idr, one ref we just took */
		BUG_ON(refcount_पढ़ो(&fsn_mark->refcnt) < 2);
	पूर्ण

	वापस i_mark;
पूर्ण

अटल काष्ठा inotअगरy_inode_mark *inotअगरy_idr_find(काष्ठा fsnotअगरy_group *group,
							 पूर्णांक wd)
अणु
	काष्ठा inotअगरy_inode_mark *i_mark;
	spinlock_t *idr_lock = &group->inotअगरy_data.idr_lock;

	spin_lock(idr_lock);
	i_mark = inotअगरy_idr_find_locked(group, wd);
	spin_unlock(idr_lock);

	वापस i_mark;
पूर्ण

/*
 * Remove the mark from the idr (अगर present) and drop the reference
 * on the mark because it was in the idr.
 */
अटल व्योम inotअगरy_हटाओ_from_idr(काष्ठा fsnotअगरy_group *group,
				    काष्ठा inotअगरy_inode_mark *i_mark)
अणु
	काष्ठा idr *idr = &group->inotअगरy_data.idr;
	spinlock_t *idr_lock = &group->inotअगरy_data.idr_lock;
	काष्ठा inotअगरy_inode_mark *found_i_mark = शून्य;
	पूर्णांक wd;

	spin_lock(idr_lock);
	wd = i_mark->wd;

	/*
	 * करोes this i_mark think it is in the idr?  we shouldn't get called
	 * अगर it wasn't....
	 */
	अगर (wd == -1) अणु
		WARN_ONCE(1, "%s: i_mark=%p i_mark->wd=%d i_mark->group=%p\n",
			__func__, i_mark, i_mark->wd, i_mark->fsn_mark.group);
		जाओ out;
	पूर्ण

	/* Lets look in the idr to see अगर we find it */
	found_i_mark = inotअगरy_idr_find_locked(group, wd);
	अगर (unlikely(!found_i_mark)) अणु
		WARN_ONCE(1, "%s: i_mark=%p i_mark->wd=%d i_mark->group=%p\n",
			__func__, i_mark, i_mark->wd, i_mark->fsn_mark.group);
		जाओ out;
	पूर्ण

	/*
	 * We found an mark in the idr at the right wd, but it's
	 * not the mark we were told to हटाओ.  eparis seriously
	 * fucked up somewhere.
	 */
	अगर (unlikely(found_i_mark != i_mark)) अणु
		WARN_ONCE(1, "%s: i_mark=%p i_mark->wd=%d i_mark->group=%p "
			"found_i_mark=%p found_i_mark->wd=%d "
			"found_i_mark->group=%p\n", __func__, i_mark,
			i_mark->wd, i_mark->fsn_mark.group, found_i_mark,
			found_i_mark->wd, found_i_mark->fsn_mark.group);
		जाओ out;
	पूर्ण

	/*
	 * One ref क्रम being in the idr
	 * one ref grabbed by inotअगरy_idr_find
	 */
	अगर (unlikely(refcount_पढ़ो(&i_mark->fsn_mark.refcnt) < 2)) अणु
		prपूर्णांकk(KERN_ERR "%s: i_mark=%p i_mark->wd=%d i_mark->group=%p\n",
			 __func__, i_mark, i_mark->wd, i_mark->fsn_mark.group);
		/* we can't really recover with bad ref cnting.. */
		BUG();
	पूर्ण

	idr_हटाओ(idr, wd);
	/* Removed from the idr, drop that ref. */
	fsnotअगरy_put_mark(&i_mark->fsn_mark);
out:
	i_mark->wd = -1;
	spin_unlock(idr_lock);
	/* match the ref taken by inotअगरy_idr_find_locked() */
	अगर (found_i_mark)
		fsnotअगरy_put_mark(&found_i_mark->fsn_mark);
पूर्ण

/*
 * Send IN_IGNORED क्रम this wd, हटाओ this wd from the idr.
 */
व्योम inotअगरy_ignored_and_हटाओ_idr(काष्ठा fsnotअगरy_mark *fsn_mark,
				    काष्ठा fsnotअगरy_group *group)
अणु
	काष्ठा inotअगरy_inode_mark *i_mark;

	/* Queue ignore event क्रम the watch */
	inotअगरy_handle_inode_event(fsn_mark, FS_IN_IGNORED, शून्य, शून्य, शून्य,
				   0);

	i_mark = container_of(fsn_mark, काष्ठा inotअगरy_inode_mark, fsn_mark);
	/* हटाओ this mark from the idr */
	inotअगरy_हटाओ_from_idr(group, i_mark);

	dec_inotअगरy_watches(group->inotअगरy_data.ucounts);
पूर्ण

अटल पूर्णांक inotअगरy_update_existing_watch(काष्ठा fsnotअगरy_group *group,
					 काष्ठा inode *inode,
					 u32 arg)
अणु
	काष्ठा fsnotअगरy_mark *fsn_mark;
	काष्ठा inotअगरy_inode_mark *i_mark;
	__u32 old_mask, new_mask;
	__u32 mask;
	पूर्णांक add = (arg & IN_MASK_ADD);
	पूर्णांक create = (arg & IN_MASK_CREATE);
	पूर्णांक ret;

	mask = inotअगरy_arg_to_mask(inode, arg);

	fsn_mark = fsnotअगरy_find_mark(&inode->i_fsnotअगरy_marks, group);
	अगर (!fsn_mark)
		वापस -ENOENT;
	अन्यथा अगर (create) अणु
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	i_mark = container_of(fsn_mark, काष्ठा inotअगरy_inode_mark, fsn_mark);

	spin_lock(&fsn_mark->lock);
	old_mask = fsn_mark->mask;
	अगर (add)
		fsn_mark->mask |= mask;
	अन्यथा
		fsn_mark->mask = mask;
	new_mask = fsn_mark->mask;
	spin_unlock(&fsn_mark->lock);

	अगर (old_mask != new_mask) अणु
		/* more bits in old than in new? */
		पूर्णांक dropped = (old_mask & ~new_mask);
		/* more bits in this fsn_mark than the inode's mask? */
		पूर्णांक करो_inode = (new_mask & ~inode->i_fsnotअगरy_mask);

		/* update the inode with this new fsn_mark */
		अगर (dropped || करो_inode)
			fsnotअगरy_recalc_mask(inode->i_fsnotअगरy_marks);

	पूर्ण

	/* वापस the wd */
	ret = i_mark->wd;

out:
	/* match the get from fsnotअगरy_find_mark() */
	fsnotअगरy_put_mark(fsn_mark);

	वापस ret;
पूर्ण

अटल पूर्णांक inotअगरy_new_watch(काष्ठा fsnotअगरy_group *group,
			     काष्ठा inode *inode,
			     u32 arg)
अणु
	काष्ठा inotअगरy_inode_mark *पंचांगp_i_mark;
	__u32 mask;
	पूर्णांक ret;
	काष्ठा idr *idr = &group->inotअगरy_data.idr;
	spinlock_t *idr_lock = &group->inotअगरy_data.idr_lock;

	mask = inotअगरy_arg_to_mask(inode, arg);

	पंचांगp_i_mark = kmem_cache_alloc(inotअगरy_inode_mark_cachep, GFP_KERNEL);
	अगर (unlikely(!पंचांगp_i_mark))
		वापस -ENOMEM;

	fsnotअगरy_init_mark(&पंचांगp_i_mark->fsn_mark, group);
	पंचांगp_i_mark->fsn_mark.mask = mask;
	पंचांगp_i_mark->wd = -1;

	ret = inotअगरy_add_to_idr(idr, idr_lock, पंचांगp_i_mark);
	अगर (ret)
		जाओ out_err;

	/* increment the number of watches the user has */
	अगर (!inc_inotअगरy_watches(group->inotअगरy_data.ucounts)) अणु
		inotअगरy_हटाओ_from_idr(group, पंचांगp_i_mark);
		ret = -ENOSPC;
		जाओ out_err;
	पूर्ण

	/* we are on the idr, now get on the inode */
	ret = fsnotअगरy_add_inode_mark_locked(&पंचांगp_i_mark->fsn_mark, inode, 0);
	अगर (ret) अणु
		/* we failed to get on the inode, get off the idr */
		inotअगरy_हटाओ_from_idr(group, पंचांगp_i_mark);
		जाओ out_err;
	पूर्ण


	/* वापस the watch descriptor क्रम this new mark */
	ret = पंचांगp_i_mark->wd;

out_err:
	/* match the ref from fsnotअगरy_init_mark() */
	fsnotअगरy_put_mark(&पंचांगp_i_mark->fsn_mark);

	वापस ret;
पूर्ण

अटल पूर्णांक inotअगरy_update_watch(काष्ठा fsnotअगरy_group *group, काष्ठा inode *inode, u32 arg)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&group->mark_mutex);
	/* try to update and existing watch with the new arg */
	ret = inotअगरy_update_existing_watch(group, inode, arg);
	/* no mark present, try to add a new one */
	अगर (ret == -ENOENT)
		ret = inotअगरy_new_watch(group, inode, arg);
	mutex_unlock(&group->mark_mutex);

	वापस ret;
पूर्ण

अटल काष्ठा fsnotअगरy_group *inotअगरy_new_group(अचिन्हित पूर्णांक max_events)
अणु
	काष्ठा fsnotअगरy_group *group;
	काष्ठा inotअगरy_event_info *oevent;

	group = fsnotअगरy_alloc_user_group(&inotअगरy_fsnotअगरy_ops);
	अगर (IS_ERR(group))
		वापस group;

	oevent = kदो_स्मृति(माप(काष्ठा inotअगरy_event_info), GFP_KERNEL_ACCOUNT);
	अगर (unlikely(!oevent)) अणु
		fsnotअगरy_destroy_group(group);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	group->overflow_event = &oevent->fse;
	fsnotअगरy_init_event(group->overflow_event);
	oevent->mask = FS_Q_OVERFLOW;
	oevent->wd = -1;
	oevent->sync_cookie = 0;
	oevent->name_len = 0;

	group->max_events = max_events;
	group->memcg = get_mem_cgroup_from_mm(current->mm);

	spin_lock_init(&group->inotअगरy_data.idr_lock);
	idr_init(&group->inotअगरy_data.idr);
	group->inotअगरy_data.ucounts = inc_ucount(current_user_ns(),
						 current_euid(),
						 UCOUNT_INOTIFY_INSTANCES);

	अगर (!group->inotअगरy_data.ucounts) अणु
		fsnotअगरy_destroy_group(group);
		वापस ERR_PTR(-EMखाता);
	पूर्ण

	वापस group;
पूर्ण


/* inotअगरy syscalls */
अटल पूर्णांक करो_inotअगरy_init(पूर्णांक flags)
अणु
	काष्ठा fsnotअगरy_group *group;
	पूर्णांक ret;

	/* Check the IN_* स्थिरants क्रम consistency.  */
	BUILD_BUG_ON(IN_CLOEXEC != O_CLOEXEC);
	BUILD_BUG_ON(IN_NONBLOCK != O_NONBLOCK);

	अगर (flags & ~(IN_CLOEXEC | IN_NONBLOCK))
		वापस -EINVAL;

	/* fsnotअगरy_obtain_group took a reference to group, we put this when we समाप्त the file in the end */
	group = inotअगरy_new_group(inotअगरy_max_queued_events);
	अगर (IS_ERR(group))
		वापस PTR_ERR(group);

	ret = anon_inode_getfd("inotify", &inotअगरy_fops, group,
				  O_RDONLY | flags);
	अगर (ret < 0)
		fsnotअगरy_destroy_group(group);

	वापस ret;
पूर्ण

SYSCALL_DEFINE1(inotअगरy_init1, पूर्णांक, flags)
अणु
	वापस करो_inotअगरy_init(flags);
पूर्ण

SYSCALL_DEFINE0(inotअगरy_init)
अणु
	वापस करो_inotअगरy_init(0);
पूर्ण

SYSCALL_DEFINE3(inotअगरy_add_watch, पूर्णांक, fd, स्थिर अक्षर __user *, pathname,
		u32, mask)
अणु
	काष्ठा fsnotअगरy_group *group;
	काष्ठा inode *inode;
	काष्ठा path path;
	काष्ठा fd f;
	पूर्णांक ret;
	अचिन्हित flags = 0;

	/*
	 * We share a lot of code with fs/dnotअगरy.  We also share
	 * the bit layout between inotअगरy's IN_* and the fsnotअगरy
	 * FS_*.  This check ensures that only the inotअगरy IN_*
	 * bits get passed in and set in watches/events.
	 */
	अगर (unlikely(mask & ~ALL_INOTIFY_BITS))
		वापस -EINVAL;
	/*
	 * Require at least one valid bit set in the mask.
	 * Without _something_ set, we would have no events to
	 * watch क्रम.
	 */
	अगर (unlikely(!(mask & ALL_INOTIFY_BITS)))
		वापस -EINVAL;

	f = fdget(fd);
	अगर (unlikely(!f.file))
		वापस -EBADF;

	/* IN_MASK_ADD and IN_MASK_CREATE करोn't make sense together */
	अगर (unlikely((mask & IN_MASK_ADD) && (mask & IN_MASK_CREATE))) अणु
		ret = -EINVAL;
		जाओ fput_and_out;
	पूर्ण

	/* verअगरy that this is indeed an inotअगरy instance */
	अगर (unlikely(f.file->f_op != &inotअगरy_fops)) अणु
		ret = -EINVAL;
		जाओ fput_and_out;
	पूर्ण

	अगर (!(mask & IN_DONT_FOLLOW))
		flags |= LOOKUP_FOLLOW;
	अगर (mask & IN_ONLYसूची)
		flags |= LOOKUP_सूचीECTORY;

	ret = inotअगरy_find_inode(pathname, &path, flags,
			(mask & IN_ALL_EVENTS));
	अगर (ret)
		जाओ fput_and_out;

	/* inode held in place by reference to path; group by fget on fd */
	inode = path.dentry->d_inode;
	group = f.file->निजी_data;

	/* create/update an inode mark */
	ret = inotअगरy_update_watch(group, inode, mask);
	path_put(&path);
fput_and_out:
	fdput(f);
	वापस ret;
पूर्ण

SYSCALL_DEFINE2(inotअगरy_rm_watch, पूर्णांक, fd, __s32, wd)
अणु
	काष्ठा fsnotअगरy_group *group;
	काष्ठा inotअगरy_inode_mark *i_mark;
	काष्ठा fd f;
	पूर्णांक ret = -EINVAL;

	f = fdget(fd);
	अगर (unlikely(!f.file))
		वापस -EBADF;

	/* verअगरy that this is indeed an inotअगरy instance */
	अगर (unlikely(f.file->f_op != &inotअगरy_fops))
		जाओ out;

	group = f.file->निजी_data;

	i_mark = inotअगरy_idr_find(group, wd);
	अगर (unlikely(!i_mark))
		जाओ out;

	ret = 0;

	fsnotअगरy_destroy_mark(&i_mark->fsn_mark, group);

	/* match ref taken by inotअगरy_idr_find */
	fsnotअगरy_put_mark(&i_mark->fsn_mark);

out:
	fdput(f);
	वापस ret;
पूर्ण

/*
 * inotअगरy_user_setup - Our initialization function.  Note that we cannot वापस
 * error because we have compiled-in VFS hooks.  So an (unlikely) failure here
 * must result in panic().
 */
अटल पूर्णांक __init inotअगरy_user_setup(व्योम)
अणु
	अचिन्हित दीर्घ watches_max;
	काष्ठा sysinfo si;

	si_meminfo(&si);
	/*
	 * Allow up to 1% of addressable memory to be allocated क्रम inotअगरy
	 * watches (per user) limited to the range [8192, 1048576].
	 */
	watches_max = (((si.totalram - si.totalhigh) / 100) << PAGE_SHIFT) /
			INOTIFY_WATCH_COST;
	watches_max = clamp(watches_max, 8192UL, 1048576UL);

	BUILD_BUG_ON(IN_ACCESS != FS_ACCESS);
	BUILD_BUG_ON(IN_MODIFY != FS_MODIFY);
	BUILD_BUG_ON(IN_ATTRIB != FS_ATTRIB);
	BUILD_BUG_ON(IN_CLOSE_WRITE != FS_CLOSE_WRITE);
	BUILD_BUG_ON(IN_CLOSE_NOWRITE != FS_CLOSE_NOWRITE);
	BUILD_BUG_ON(IN_OPEN != FS_OPEN);
	BUILD_BUG_ON(IN_MOVED_FROM != FS_MOVED_FROM);
	BUILD_BUG_ON(IN_MOVED_TO != FS_MOVED_TO);
	BUILD_BUG_ON(IN_CREATE != FS_CREATE);
	BUILD_BUG_ON(IN_DELETE != FS_DELETE);
	BUILD_BUG_ON(IN_DELETE_SELF != FS_DELETE_SELF);
	BUILD_BUG_ON(IN_MOVE_SELF != FS_MOVE_SELF);
	BUILD_BUG_ON(IN_UNMOUNT != FS_UNMOUNT);
	BUILD_BUG_ON(IN_Q_OVERFLOW != FS_Q_OVERFLOW);
	BUILD_BUG_ON(IN_IGNORED != FS_IN_IGNORED);
	BUILD_BUG_ON(IN_EXCL_UNLINK != FS_EXCL_UNLINK);
	BUILD_BUG_ON(IN_ISसूची != FS_ISसूची);
	BUILD_BUG_ON(IN_ONESHOT != FS_IN_ONESHOT);

	BUILD_BUG_ON(HWEIGHT32(ALL_INOTIFY_BITS) != 22);

	inotअगरy_inode_mark_cachep = KMEM_CACHE(inotअगरy_inode_mark,
					       SLAB_PANIC|SLAB_ACCOUNT);

	inotअगरy_max_queued_events = 16384;
	init_user_ns.ucount_max[UCOUNT_INOTIFY_INSTANCES] = 128;
	init_user_ns.ucount_max[UCOUNT_INOTIFY_WATCHES] = watches_max;

	वापस 0;
पूर्ण
fs_initcall(inotअगरy_user_setup);
