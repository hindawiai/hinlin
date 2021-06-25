<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fanotअगरy.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/init.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/poll.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/compat.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/memcontrol.h>
#समावेश <linux/statfs.h>
#समावेश <linux/exportfs.h>

#समावेश <यंत्र/ioctls.h>

#समावेश "../../mount.h"
#समावेश "../fdinfo.h"
#समावेश "fanotify.h"

#घोषणा FANOTIFY_DEFAULT_MAX_EVENTS	16384
#घोषणा FANOTIFY_OLD_DEFAULT_MAX_MARKS	8192
#घोषणा FANOTIFY_DEFAULT_MAX_GROUPS	128

/*
 * Legacy fanotअगरy marks limits (8192) is per group and we पूर्णांकroduced a tunable
 * limit of marks per user, similar to inotअगरy.  Effectively, the legacy limit
 * of fanotअगरy marks per user is <max marks per group> * <max groups per user>.
 * This शेष limit (1M) also happens to match the increased limit of inotअगरy
 * max_user_watches since v5.10.
 */
#घोषणा FANOTIFY_DEFAULT_MAX_USER_MARKS	\
	(FANOTIFY_OLD_DEFAULT_MAX_MARKS * FANOTIFY_DEFAULT_MAX_GROUPS)

/*
 * Most of the memory cost of adding an inode mark is pinning the marked inode.
 * The size of the fileप्रणाली inode काष्ठा is not unअगरorm across fileप्रणालीs,
 * so द्विगुन the size of a VFS inode is used as a conservative approximation.
 */
#घोषणा INODE_MARK_COST	(2 * माप(काष्ठा inode))

/* configurable via /proc/sys/fs/fanotअगरy/ */
अटल पूर्णांक fanotअगरy_max_queued_events __पढ़ो_mostly;

#अगर_घोषित CONFIG_SYSCTL

#समावेश <linux/sysctl.h>

काष्ठा ctl_table fanotअगरy_table[] = अणु
	अणु
		.procname	= "max_user_groups",
		.data	= &init_user_ns.ucount_max[UCOUNT_FANOTIFY_GROUPS],
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "max_user_marks",
		.data	= &init_user_ns.ucount_max[UCOUNT_FANOTIFY_MARKS],
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "max_queued_events",
		.data		= &fanotअगरy_max_queued_events,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO
	पूर्ण,
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_SYSCTL */

/*
 * All flags that may be specअगरied in parameter event_f_flags of fanotअगरy_init.
 *
 * Internal and बाह्यal खोलो flags are stored together in field f_flags of
 * काष्ठा file. Only बाह्यal खोलो flags shall be allowed in event_f_flags.
 * Internal flags like FMODE_NONOTIFY, FMODE_EXEC, FMODE_NOCMTIME shall be
 * excluded.
 */
#घोषणा	FANOTIFY_INIT_ALL_EVENT_F_BITS				( \
		O_ACCMODE	| O_APPEND	| O_NONBLOCK	| \
		__O_SYNC	| O_DSYNC	| O_CLOEXEC     | \
		O_LARGEखाता	| O_NOATIME	)

बाह्य स्थिर काष्ठा fsnotअगरy_ops fanotअगरy_fsnotअगरy_ops;

काष्ठा kmem_cache *fanotअगरy_mark_cache __पढ़ो_mostly;
काष्ठा kmem_cache *fanotअगरy_fid_event_cachep __पढ़ो_mostly;
काष्ठा kmem_cache *fanotअगरy_path_event_cachep __पढ़ो_mostly;
काष्ठा kmem_cache *fanotअगरy_perm_event_cachep __पढ़ो_mostly;

#घोषणा FANOTIFY_EVENT_ALIGN 4
#घोषणा FANOTIFY_INFO_HDR_LEN \
	(माप(काष्ठा fanotअगरy_event_info_fid) + माप(काष्ठा file_handle))

अटल पूर्णांक fanotअगरy_fid_info_len(पूर्णांक fh_len, पूर्णांक name_len)
अणु
	पूर्णांक info_len = fh_len;

	अगर (name_len)
		info_len += name_len + 1;

	वापस roundup(FANOTIFY_INFO_HDR_LEN + info_len, FANOTIFY_EVENT_ALIGN);
पूर्ण

अटल पूर्णांक fanotअगरy_event_info_len(अचिन्हित पूर्णांक fid_mode,
				   काष्ठा fanotअगरy_event *event)
अणु
	काष्ठा fanotअगरy_info *info = fanotअगरy_event_info(event);
	पूर्णांक dir_fh_len = fanotअगरy_event_dir_fh_len(event);
	पूर्णांक fh_len = fanotअगरy_event_object_fh_len(event);
	पूर्णांक info_len = 0;
	पूर्णांक करोt_len = 0;

	अगर (dir_fh_len) अणु
		info_len += fanotअगरy_fid_info_len(dir_fh_len, info->name_len);
	पूर्ण अन्यथा अगर ((fid_mode & FAN_REPORT_NAME) && (event->mask & FAN_ONसूची)) अणु
		/*
		 * With group flag FAN_REPORT_NAME, अगर name was not recorded in
		 * event on a directory, we will report the name ".".
		 */
		करोt_len = 1;
	पूर्ण

	अगर (fh_len)
		info_len += fanotअगरy_fid_info_len(fh_len, करोt_len);

	वापस info_len;
पूर्ण

/*
 * Remove an hashed event from merge hash table.
 */
अटल व्योम fanotअगरy_unhash_event(काष्ठा fsnotअगरy_group *group,
				  काष्ठा fanotअगरy_event *event)
अणु
	निश्चित_spin_locked(&group->notअगरication_lock);

	pr_debug("%s: group=%p event=%p bucket=%u\n", __func__,
		 group, event, fanotअगरy_event_hash_bucket(group, event));

	अगर (WARN_ON_ONCE(hlist_unhashed(&event->merge_list)))
		वापस;

	hlist_del_init(&event->merge_list);
पूर्ण

/*
 * Get an fanotअगरy notअगरication event अगर one exists and is small
 * enough to fit in "count". Return an error poपूर्णांकer अगर the count
 * is not large enough. When permission event is dequeued, its state is
 * updated accordingly.
 */
अटल काष्ठा fanotअगरy_event *get_one_event(काष्ठा fsnotअगरy_group *group,
					    माप_प्रकार count)
अणु
	माप_प्रकार event_size = FAN_EVENT_METADATA_LEN;
	काष्ठा fanotअगरy_event *event = शून्य;
	काष्ठा fsnotअगरy_event *fsn_event;
	अचिन्हित पूर्णांक fid_mode = FAN_GROUP_FLAG(group, FANOTIFY_FID_BITS);

	pr_debug("%s: group=%p count=%zd\n", __func__, group, count);

	spin_lock(&group->notअगरication_lock);
	fsn_event = fsnotअगरy_peek_first_event(group);
	अगर (!fsn_event)
		जाओ out;

	event = FANOTIFY_E(fsn_event);
	अगर (fid_mode)
		event_size += fanotअगरy_event_info_len(fid_mode, event);

	अगर (event_size > count) अणु
		event = ERR_PTR(-EINVAL);
		जाओ out;
	पूर्ण

	/*
	 * Held the notअगरication_lock the whole समय, so this is the
	 * same event we peeked above.
	 */
	fsnotअगरy_हटाओ_first_event(group);
	अगर (fanotअगरy_is_perm_event(event->mask))
		FANOTIFY_PERM(event)->state = FAN_EVENT_REPORTED;
	अगर (fanotअगरy_is_hashed_event(event->mask))
		fanotअगरy_unhash_event(group, event);
out:
	spin_unlock(&group->notअगरication_lock);
	वापस event;
पूर्ण

अटल पूर्णांक create_fd(काष्ठा fsnotअगरy_group *group, काष्ठा path *path,
		     काष्ठा file **file)
अणु
	पूर्णांक client_fd;
	काष्ठा file *new_file;

	client_fd = get_unused_fd_flags(group->fanotअगरy_data.f_flags);
	अगर (client_fd < 0)
		वापस client_fd;

	/*
	 * we need a new file handle क्रम the userspace program so it can पढ़ो even अगर it was
	 * originally खोलोed O_WRONLY.
	 */
	new_file = dentry_खोलो(path,
			       group->fanotअगरy_data.f_flags | FMODE_NONOTIFY,
			       current_cred());
	अगर (IS_ERR(new_file)) अणु
		/*
		 * we still send an event even अगर we can't खोलो the file.  this
		 * can happen when say tasks are gone and we try to खोलो their
		 * /proc files or we try to खोलो a WRONLY file like in sysfs
		 * we just send the त्रुटि_सं to userspace since there isn't much
		 * अन्यथा we can करो.
		 */
		put_unused_fd(client_fd);
		client_fd = PTR_ERR(new_file);
	पूर्ण अन्यथा अणु
		*file = new_file;
	पूर्ण

	वापस client_fd;
पूर्ण

/*
 * Finish processing of permission event by setting it to ANSWERED state and
 * drop group->notअगरication_lock.
 */
अटल व्योम finish_permission_event(काष्ठा fsnotअगरy_group *group,
				    काष्ठा fanotअगरy_perm_event *event,
				    अचिन्हित पूर्णांक response)
				    __releases(&group->notअगरication_lock)
अणु
	bool destroy = false;

	निश्चित_spin_locked(&group->notअगरication_lock);
	event->response = response;
	अगर (event->state == FAN_EVENT_CANCELED)
		destroy = true;
	अन्यथा
		event->state = FAN_EVENT_ANSWERED;
	spin_unlock(&group->notअगरication_lock);
	अगर (destroy)
		fsnotअगरy_destroy_event(group, &event->fae.fse);
पूर्ण

अटल पूर्णांक process_access_response(काष्ठा fsnotअगरy_group *group,
				   काष्ठा fanotअगरy_response *response_काष्ठा)
अणु
	काष्ठा fanotअगरy_perm_event *event;
	पूर्णांक fd = response_काष्ठा->fd;
	पूर्णांक response = response_काष्ठा->response;

	pr_debug("%s: group=%p fd=%d response=%d\n", __func__, group,
		 fd, response);
	/*
	 * make sure the response is valid, अगर invalid we करो nothing and either
	 * userspace can send a valid response or we will clean it up after the
	 * समयout
	 */
	चयन (response & ~FAN_AUDIT) अणु
	हाल FAN_ALLOW:
	हाल FAN_DENY:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (fd < 0)
		वापस -EINVAL;

	अगर ((response & FAN_AUDIT) && !FAN_GROUP_FLAG(group, FAN_ENABLE_AUDIT))
		वापस -EINVAL;

	spin_lock(&group->notअगरication_lock);
	list_क्रम_each_entry(event, &group->fanotअगरy_data.access_list,
			    fae.fse.list) अणु
		अगर (event->fd != fd)
			जारी;

		list_del_init(&event->fae.fse.list);
		finish_permission_event(group, event, response);
		wake_up(&group->fanotअगरy_data.access_रुकोq);
		वापस 0;
	पूर्ण
	spin_unlock(&group->notअगरication_lock);

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक copy_info_to_user(__kernel_fsid_t *fsid, काष्ठा fanotअगरy_fh *fh,
			     पूर्णांक info_type, स्थिर अक्षर *name, माप_प्रकार name_len,
			     अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा fanotअगरy_event_info_fid info = अणु पूर्ण;
	काष्ठा file_handle handle = अणु पूर्ण;
	अचिन्हित अक्षर bounce[FANOTIFY_INLINE_FH_LEN], *fh_buf;
	माप_प्रकार fh_len = fh ? fh->len : 0;
	माप_प्रकार info_len = fanotअगरy_fid_info_len(fh_len, name_len);
	माप_प्रकार len = info_len;

	pr_debug("%s: fh_len=%zu name_len=%zu, info_len=%zu, count=%zu\n",
		 __func__, fh_len, name_len, info_len, count);

	अगर (!fh_len)
		वापस 0;

	अगर (WARN_ON_ONCE(len < माप(info) || len > count))
		वापस -EFAULT;

	/*
	 * Copy event info fid header followed by variable sized file handle
	 * and optionally followed by variable sized filename.
	 */
	चयन (info_type) अणु
	हाल FAN_EVENT_INFO_TYPE_FID:
	हाल FAN_EVENT_INFO_TYPE_DFID:
		अगर (WARN_ON_ONCE(name_len))
			वापस -EFAULT;
		अवरोध;
	हाल FAN_EVENT_INFO_TYPE_DFID_NAME:
		अगर (WARN_ON_ONCE(!name || !name_len))
			वापस -EFAULT;
		अवरोध;
	शेष:
		वापस -EFAULT;
	पूर्ण

	info.hdr.info_type = info_type;
	info.hdr.len = len;
	info.fsid = *fsid;
	अगर (copy_to_user(buf, &info, माप(info)))
		वापस -EFAULT;

	buf += माप(info);
	len -= माप(info);
	अगर (WARN_ON_ONCE(len < माप(handle)))
		वापस -EFAULT;

	handle.handle_type = fh->type;
	handle.handle_bytes = fh_len;
	अगर (copy_to_user(buf, &handle, माप(handle)))
		वापस -EFAULT;

	buf += माप(handle);
	len -= माप(handle);
	अगर (WARN_ON_ONCE(len < fh_len))
		वापस -EFAULT;

	/*
	 * For an अंतरभूत fh and अंतरभूत file name, copy through stack to exclude
	 * the copy from usercopy hardening protections.
	 */
	fh_buf = fanotअगरy_fh_buf(fh);
	अगर (fh_len <= FANOTIFY_INLINE_FH_LEN) अणु
		स_नकल(bounce, fh_buf, fh_len);
		fh_buf = bounce;
	पूर्ण
	अगर (copy_to_user(buf, fh_buf, fh_len))
		वापस -EFAULT;

	buf += fh_len;
	len -= fh_len;

	अगर (name_len) अणु
		/* Copy the filename with terminating null */
		name_len++;
		अगर (WARN_ON_ONCE(len < name_len))
			वापस -EFAULT;

		अगर (copy_to_user(buf, name, name_len))
			वापस -EFAULT;

		buf += name_len;
		len -= name_len;
	पूर्ण

	/* Pad with 0's */
	WARN_ON_ONCE(len < 0 || len >= FANOTIFY_EVENT_ALIGN);
	अगर (len > 0 && clear_user(buf, len))
		वापस -EFAULT;

	वापस info_len;
पूर्ण

अटल sमाप_प्रकार copy_event_to_user(काष्ठा fsnotअगरy_group *group,
				  काष्ठा fanotअगरy_event *event,
				  अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा fanotअगरy_event_metadata metadata;
	काष्ठा path *path = fanotअगरy_event_path(event);
	काष्ठा fanotअगरy_info *info = fanotअगरy_event_info(event);
	अचिन्हित पूर्णांक fid_mode = FAN_GROUP_FLAG(group, FANOTIFY_FID_BITS);
	काष्ठा file *f = शून्य;
	पूर्णांक ret, fd = FAN_NOFD;
	पूर्णांक info_type = 0;

	pr_debug("%s: group=%p event=%p\n", __func__, group, event);

	metadata.event_len = FAN_EVENT_METADATA_LEN +
				fanotअगरy_event_info_len(fid_mode, event);
	metadata.metadata_len = FAN_EVENT_METADATA_LEN;
	metadata.vers = FANOTIFY_METADATA_VERSION;
	metadata.reserved = 0;
	metadata.mask = event->mask & FANOTIFY_OUTGOING_EVENTS;
	metadata.pid = pid_vnr(event->pid);
	/*
	 * For an unprivileged listener, event->pid can be used to identअगरy the
	 * events generated by the listener process itself, without disclosing
	 * the pids of other processes.
	 */
	अगर (FAN_GROUP_FLAG(group, FANOTIFY_UNPRIV) &&
	    task_tgid(current) != event->pid)
		metadata.pid = 0;

	/*
	 * For now, fid mode is required क्रम an unprivileged listener and
	 * fid mode करोes not report fd in events.  Keep this check anyway
	 * क्रम safety in हाल fid mode requirement is relaxed in the future
	 * to allow unprivileged listener to get events with no fd and no fid.
	 */
	अगर (!FAN_GROUP_FLAG(group, FANOTIFY_UNPRIV) &&
	    path && path->mnt && path->dentry) अणु
		fd = create_fd(group, path, &f);
		अगर (fd < 0)
			वापस fd;
	पूर्ण
	metadata.fd = fd;

	ret = -EFAULT;
	/*
	 * Sanity check copy size in हाल get_one_event() and
	 * event_len sizes ever get out of sync.
	 */
	अगर (WARN_ON_ONCE(metadata.event_len > count))
		जाओ out_बंद_fd;

	अगर (copy_to_user(buf, &metadata, FAN_EVENT_METADATA_LEN))
		जाओ out_बंद_fd;

	buf += FAN_EVENT_METADATA_LEN;
	count -= FAN_EVENT_METADATA_LEN;

	अगर (fanotअगरy_is_perm_event(event->mask))
		FANOTIFY_PERM(event)->fd = fd;

	अगर (f)
		fd_install(fd, f);

	/* Event info records order is: dir fid + name, child fid */
	अगर (fanotअगरy_event_dir_fh_len(event)) अणु
		info_type = info->name_len ? FAN_EVENT_INFO_TYPE_DFID_NAME :
					     FAN_EVENT_INFO_TYPE_DFID;
		ret = copy_info_to_user(fanotअगरy_event_fsid(event),
					fanotअगरy_info_dir_fh(info),
					info_type, fanotअगरy_info_name(info),
					info->name_len, buf, count);
		अगर (ret < 0)
			जाओ out_बंद_fd;

		buf += ret;
		count -= ret;
	पूर्ण

	अगर (fanotअगरy_event_object_fh_len(event)) अणु
		स्थिर अक्षर *करोt = शून्य;
		पूर्णांक करोt_len = 0;

		अगर (fid_mode == FAN_REPORT_FID || info_type) अणु
			/*
			 * With only group flag FAN_REPORT_FID only type FID is
			 * reported. Second info record type is always FID.
			 */
			info_type = FAN_EVENT_INFO_TYPE_FID;
		पूर्ण अन्यथा अगर ((fid_mode & FAN_REPORT_NAME) &&
			   (event->mask & FAN_ONसूची)) अणु
			/*
			 * With group flag FAN_REPORT_NAME, अगर name was not
			 * recorded in an event on a directory, report the
			 * name "." with info type DFID_NAME.
			 */
			info_type = FAN_EVENT_INFO_TYPE_DFID_NAME;
			करोt = ".";
			करोt_len = 1;
		पूर्ण अन्यथा अगर ((event->mask & ALL_FSNOTIFY_सूचीENT_EVENTS) ||
			   (event->mask & FAN_ONसूची)) अणु
			/*
			 * With group flag FAN_REPORT_सूची_FID, a single info
			 * record has type DFID क्रम directory entry modअगरication
			 * event and क्रम event on a directory.
			 */
			info_type = FAN_EVENT_INFO_TYPE_DFID;
		पूर्ण अन्यथा अणु
			/*
			 * With group flags FAN_REPORT_सूची_FID|FAN_REPORT_FID,
			 * a single info record has type FID क्रम event on a
			 * non-directory, when there is no directory to report.
			 * For example, on FAN_DELETE_SELF event.
			 */
			info_type = FAN_EVENT_INFO_TYPE_FID;
		पूर्ण

		ret = copy_info_to_user(fanotअगरy_event_fsid(event),
					fanotअगरy_event_object_fh(event),
					info_type, करोt, करोt_len, buf, count);
		अगर (ret < 0)
			जाओ out_बंद_fd;

		buf += ret;
		count -= ret;
	पूर्ण

	वापस metadata.event_len;

out_बंद_fd:
	अगर (fd != FAN_NOFD) अणु
		put_unused_fd(fd);
		fput(f);
	पूर्ण
	वापस ret;
पूर्ण

/* पूर्णांकofiy userspace file descriptor functions */
अटल __poll_t fanotअगरy_poll(काष्ठा file *file, poll_table *रुको)
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

अटल sमाप_प्रकार fanotअगरy_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			     माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा fsnotअगरy_group *group;
	काष्ठा fanotअगरy_event *event;
	अक्षर __user *start;
	पूर्णांक ret;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	start = buf;
	group = file->निजी_data;

	pr_debug("%s: group=%p\n", __func__, group);

	add_रुको_queue(&group->notअगरication_रुकोq, &रुको);
	जबतक (1) अणु
		/*
		 * User can supply arbitrarily large buffer. Aव्योम softlockups
		 * in हाल there are lots of available events.
		 */
		cond_resched();
		event = get_one_event(group, count);
		अगर (IS_ERR(event)) अणु
			ret = PTR_ERR(event);
			अवरोध;
		पूर्ण

		अगर (!event) अणु
			ret = -EAGAIN;
			अगर (file->f_flags & O_NONBLOCK)
				अवरोध;

			ret = -ERESTARTSYS;
			अगर (संकेत_pending(current))
				अवरोध;

			अगर (start != buf)
				अवरोध;

			रुको_woken(&रुको, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
			जारी;
		पूर्ण

		ret = copy_event_to_user(group, event, buf, count);
		अगर (unlikely(ret == -EOPENSTALE)) अणु
			/*
			 * We cannot report events with stale fd so drop it.
			 * Setting ret to 0 will जारी the event loop and
			 * करो the right thing अगर there are no more events to
			 * पढ़ो (i.e. वापस bytes पढ़ो, -EAGAIN or रुको).
			 */
			ret = 0;
		पूर्ण

		/*
		 * Permission events get queued to रुको क्रम response.  Other
		 * events can be destroyed now.
		 */
		अगर (!fanotअगरy_is_perm_event(event->mask)) अणु
			fsnotअगरy_destroy_event(group, &event->fse);
		पूर्ण अन्यथा अणु
			अगर (ret <= 0) अणु
				spin_lock(&group->notअगरication_lock);
				finish_permission_event(group,
					FANOTIFY_PERM(event), FAN_DENY);
				wake_up(&group->fanotअगरy_data.access_रुकोq);
			पूर्ण अन्यथा अणु
				spin_lock(&group->notअगरication_lock);
				list_add_tail(&event->fse.list,
					&group->fanotअगरy_data.access_list);
				spin_unlock(&group->notअगरication_lock);
			पूर्ण
		पूर्ण
		अगर (ret < 0)
			अवरोध;
		buf += ret;
		count -= ret;
	पूर्ण
	हटाओ_रुको_queue(&group->notअगरication_रुकोq, &रुको);

	अगर (start != buf && ret != -EFAULT)
		ret = buf - start;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार fanotअगरy_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा fanotअगरy_response response = अणु .fd = -1, .response = -1 पूर्ण;
	काष्ठा fsnotअगरy_group *group;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_FANOTIFY_ACCESS_PERMISSIONS))
		वापस -EINVAL;

	group = file->निजी_data;

	अगर (count < माप(response))
		वापस -EINVAL;

	count = माप(response);

	pr_debug("%s: group=%p count=%zu\n", __func__, group, count);

	अगर (copy_from_user(&response, buf, count))
		वापस -EFAULT;

	ret = process_access_response(group, &response);
	अगर (ret < 0)
		count = ret;

	वापस count;
पूर्ण

अटल पूर्णांक fanotअगरy_release(काष्ठा inode *ignored, काष्ठा file *file)
अणु
	काष्ठा fsnotअगरy_group *group = file->निजी_data;
	काष्ठा fsnotअगरy_event *fsn_event;

	/*
	 * Stop new events from arriving in the notअगरication queue. since
	 * userspace cannot use fanotअगरy fd anymore, no event can enter or
	 * leave access_list by now either.
	 */
	fsnotअगरy_group_stop_queueing(group);

	/*
	 * Process all permission events on access_list and notअगरication queue
	 * and simulate reply from userspace.
	 */
	spin_lock(&group->notअगरication_lock);
	जबतक (!list_empty(&group->fanotअगरy_data.access_list)) अणु
		काष्ठा fanotअगरy_perm_event *event;

		event = list_first_entry(&group->fanotअगरy_data.access_list,
				काष्ठा fanotअगरy_perm_event, fae.fse.list);
		list_del_init(&event->fae.fse.list);
		finish_permission_event(group, event, FAN_ALLOW);
		spin_lock(&group->notअगरication_lock);
	पूर्ण

	/*
	 * Destroy all non-permission events. For permission events just
	 * dequeue them and set the response. They will be मुक्तd once the
	 * response is consumed and fanotअगरy_get_response() वापसs.
	 */
	जबतक ((fsn_event = fsnotअगरy_हटाओ_first_event(group))) अणु
		काष्ठा fanotअगरy_event *event = FANOTIFY_E(fsn_event);

		अगर (!(event->mask & FANOTIFY_PERM_EVENTS)) अणु
			spin_unlock(&group->notअगरication_lock);
			fsnotअगरy_destroy_event(group, fsn_event);
		पूर्ण अन्यथा अणु
			finish_permission_event(group, FANOTIFY_PERM(event),
						FAN_ALLOW);
		पूर्ण
		spin_lock(&group->notअगरication_lock);
	पूर्ण
	spin_unlock(&group->notअगरication_lock);

	/* Response क्रम all permission events it set, wakeup रुकोers */
	wake_up(&group->fanotअगरy_data.access_रुकोq);

	/* matches the fanotअगरy_init->fsnotअगरy_alloc_group */
	fsnotअगरy_destroy_group(group);

	वापस 0;
पूर्ण

अटल दीर्घ fanotअगरy_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा fsnotअगरy_group *group;
	काष्ठा fsnotअगरy_event *fsn_event;
	व्योम __user *p;
	पूर्णांक ret = -ENOTTY;
	माप_प्रकार send_len = 0;

	group = file->निजी_data;

	p = (व्योम __user *) arg;

	चयन (cmd) अणु
	हाल FIONREAD:
		spin_lock(&group->notअगरication_lock);
		list_क्रम_each_entry(fsn_event, &group->notअगरication_list, list)
			send_len += FAN_EVENT_METADATA_LEN;
		spin_unlock(&group->notअगरication_lock);
		ret = put_user(send_len, (पूर्णांक __user *) p);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fanotअगरy_fops = अणु
	.show_fdinfo	= fanotअगरy_show_fdinfo,
	.poll		= fanotअगरy_poll,
	.पढ़ो		= fanotअगरy_पढ़ो,
	.ग_लिखो		= fanotअगरy_ग_लिखो,
	.fasync		= शून्य,
	.release	= fanotअगरy_release,
	.unlocked_ioctl	= fanotअगरy_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.llseek		= noop_llseek,
पूर्ण;

अटल पूर्णांक fanotअगरy_find_path(पूर्णांक dfd, स्थिर अक्षर __user *filename,
			      काष्ठा path *path, अचिन्हित पूर्णांक flags, __u64 mask,
			      अचिन्हित पूर्णांक obj_type)
अणु
	पूर्णांक ret;

	pr_debug("%s: dfd=%d filename=%p flags=%x\n", __func__,
		 dfd, filename, flags);

	अगर (filename == शून्य) अणु
		काष्ठा fd f = fdget(dfd);

		ret = -EBADF;
		अगर (!f.file)
			जाओ out;

		ret = -ENOTसूची;
		अगर ((flags & FAN_MARK_ONLYसूची) &&
		    !(S_ISसूची(file_inode(f.file)->i_mode))) अणु
			fdput(f);
			जाओ out;
		पूर्ण

		*path = f.file->f_path;
		path_get(path);
		fdput(f);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक lookup_flags = 0;

		अगर (!(flags & FAN_MARK_DONT_FOLLOW))
			lookup_flags |= LOOKUP_FOLLOW;
		अगर (flags & FAN_MARK_ONLYसूची)
			lookup_flags |= LOOKUP_सूचीECTORY;

		ret = user_path_at(dfd, filename, lookup_flags, path);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* you can only watch an inode अगर you have पढ़ो permissions on it */
	ret = path_permission(path, MAY_READ);
	अगर (ret) अणु
		path_put(path);
		जाओ out;
	पूर्ण

	ret = security_path_notअगरy(path, mask, obj_type);
	अगर (ret)
		path_put(path);

out:
	वापस ret;
पूर्ण

अटल __u32 fanotअगरy_mark_हटाओ_from_mask(काष्ठा fsnotअगरy_mark *fsn_mark,
					    __u32 mask, अचिन्हित पूर्णांक flags,
					    __u32 umask, पूर्णांक *destroy)
अणु
	__u32 oldmask = 0;

	/* umask bits cannot be हटाओd by user */
	mask &= ~umask;
	spin_lock(&fsn_mark->lock);
	अगर (!(flags & FAN_MARK_IGNORED_MASK)) अणु
		oldmask = fsn_mark->mask;
		fsn_mark->mask &= ~mask;
	पूर्ण अन्यथा अणु
		fsn_mark->ignored_mask &= ~mask;
	पूर्ण
	/*
	 * We need to keep the mark around even अगर reमुख्यing mask cannot
	 * result in any events (e.g. mask == FAN_ONसूची) to support incremenal
	 * changes to the mask.
	 * Destroy mark when only umask bits reमुख्य.
	 */
	*destroy = !((fsn_mark->mask | fsn_mark->ignored_mask) & ~umask);
	spin_unlock(&fsn_mark->lock);

	वापस mask & oldmask;
पूर्ण

अटल पूर्णांक fanotअगरy_हटाओ_mark(काष्ठा fsnotअगरy_group *group,
				fsnotअगरy_connp_t *connp, __u32 mask,
				अचिन्हित पूर्णांक flags, __u32 umask)
अणु
	काष्ठा fsnotअगरy_mark *fsn_mark = शून्य;
	__u32 हटाओd;
	पूर्णांक destroy_mark;

	mutex_lock(&group->mark_mutex);
	fsn_mark = fsnotअगरy_find_mark(connp, group);
	अगर (!fsn_mark) अणु
		mutex_unlock(&group->mark_mutex);
		वापस -ENOENT;
	पूर्ण

	हटाओd = fanotअगरy_mark_हटाओ_from_mask(fsn_mark, mask, flags,
						 umask, &destroy_mark);
	अगर (हटाओd & fsnotअगरy_conn_mask(fsn_mark->connector))
		fsnotअगरy_recalc_mask(fsn_mark->connector);
	अगर (destroy_mark)
		fsnotअगरy_detach_mark(fsn_mark);
	mutex_unlock(&group->mark_mutex);
	अगर (destroy_mark)
		fsnotअगरy_मुक्त_mark(fsn_mark);

	/* matches the fsnotअगरy_find_mark() */
	fsnotअगरy_put_mark(fsn_mark);
	वापस 0;
पूर्ण

अटल पूर्णांक fanotअगरy_हटाओ_vfsmount_mark(काष्ठा fsnotअगरy_group *group,
					 काष्ठा vfsmount *mnt, __u32 mask,
					 अचिन्हित पूर्णांक flags, __u32 umask)
अणु
	वापस fanotअगरy_हटाओ_mark(group, &real_mount(mnt)->mnt_fsnotअगरy_marks,
				    mask, flags, umask);
पूर्ण

अटल पूर्णांक fanotअगरy_हटाओ_sb_mark(काष्ठा fsnotअगरy_group *group,
				   काष्ठा super_block *sb, __u32 mask,
				   अचिन्हित पूर्णांक flags, __u32 umask)
अणु
	वापस fanotअगरy_हटाओ_mark(group, &sb->s_fsnotअगरy_marks, mask,
				    flags, umask);
पूर्ण

अटल पूर्णांक fanotअगरy_हटाओ_inode_mark(काष्ठा fsnotअगरy_group *group,
				      काष्ठा inode *inode, __u32 mask,
				      अचिन्हित पूर्णांक flags, __u32 umask)
अणु
	वापस fanotअगरy_हटाओ_mark(group, &inode->i_fsnotअगरy_marks, mask,
				    flags, umask);
पूर्ण

अटल __u32 fanotअगरy_mark_add_to_mask(काष्ठा fsnotअगरy_mark *fsn_mark,
				       __u32 mask,
				       अचिन्हित पूर्णांक flags)
अणु
	__u32 oldmask = -1;

	spin_lock(&fsn_mark->lock);
	अगर (!(flags & FAN_MARK_IGNORED_MASK)) अणु
		oldmask = fsn_mark->mask;
		fsn_mark->mask |= mask;
	पूर्ण अन्यथा अणु
		fsn_mark->ignored_mask |= mask;
		अगर (flags & FAN_MARK_IGNORED_SURV_MODIFY)
			fsn_mark->flags |= FSNOTIFY_MARK_FLAG_IGNORED_SURV_MODIFY;
	पूर्ण
	spin_unlock(&fsn_mark->lock);

	वापस mask & ~oldmask;
पूर्ण

अटल काष्ठा fsnotअगरy_mark *fanotअगरy_add_new_mark(काष्ठा fsnotअगरy_group *group,
						   fsnotअगरy_connp_t *connp,
						   अचिन्हित पूर्णांक type,
						   __kernel_fsid_t *fsid)
अणु
	काष्ठा ucounts *ucounts = group->fanotअगरy_data.ucounts;
	काष्ठा fsnotअगरy_mark *mark;
	पूर्णांक ret;

	/*
	 * Enक्रमce per user marks limits per user in all containing user ns.
	 * A group with FAN_UNLIMITED_MARKS करोes not contribute to mark count
	 * in the limited groups account.
	 */
	अगर (!FAN_GROUP_FLAG(group, FAN_UNLIMITED_MARKS) &&
	    !inc_ucount(ucounts->ns, ucounts->uid, UCOUNT_FANOTIFY_MARKS))
		वापस ERR_PTR(-ENOSPC);

	mark = kmem_cache_alloc(fanotअगरy_mark_cache, GFP_KERNEL);
	अगर (!mark) अणु
		ret = -ENOMEM;
		जाओ out_dec_ucounts;
	पूर्ण

	fsnotअगरy_init_mark(mark, group);
	ret = fsnotअगरy_add_mark_locked(mark, connp, type, 0, fsid);
	अगर (ret) अणु
		fsnotअगरy_put_mark(mark);
		जाओ out_dec_ucounts;
	पूर्ण

	वापस mark;

out_dec_ucounts:
	अगर (!FAN_GROUP_FLAG(group, FAN_UNLIMITED_MARKS))
		dec_ucount(ucounts, UCOUNT_FANOTIFY_MARKS);
	वापस ERR_PTR(ret);
पूर्ण


अटल पूर्णांक fanotअगरy_add_mark(काष्ठा fsnotअगरy_group *group,
			     fsnotअगरy_connp_t *connp, अचिन्हित पूर्णांक type,
			     __u32 mask, अचिन्हित पूर्णांक flags,
			     __kernel_fsid_t *fsid)
अणु
	काष्ठा fsnotअगरy_mark *fsn_mark;
	__u32 added;

	mutex_lock(&group->mark_mutex);
	fsn_mark = fsnotअगरy_find_mark(connp, group);
	अगर (!fsn_mark) अणु
		fsn_mark = fanotअगरy_add_new_mark(group, connp, type, fsid);
		अगर (IS_ERR(fsn_mark)) अणु
			mutex_unlock(&group->mark_mutex);
			वापस PTR_ERR(fsn_mark);
		पूर्ण
	पूर्ण
	added = fanotअगरy_mark_add_to_mask(fsn_mark, mask, flags);
	अगर (added & ~fsnotअगरy_conn_mask(fsn_mark->connector))
		fsnotअगरy_recalc_mask(fsn_mark->connector);
	mutex_unlock(&group->mark_mutex);

	fsnotअगरy_put_mark(fsn_mark);
	वापस 0;
पूर्ण

अटल पूर्णांक fanotअगरy_add_vfsmount_mark(काष्ठा fsnotअगरy_group *group,
				      काष्ठा vfsmount *mnt, __u32 mask,
				      अचिन्हित पूर्णांक flags, __kernel_fsid_t *fsid)
अणु
	वापस fanotअगरy_add_mark(group, &real_mount(mnt)->mnt_fsnotअगरy_marks,
				 FSNOTIFY_OBJ_TYPE_VFSMOUNT, mask, flags, fsid);
पूर्ण

अटल पूर्णांक fanotअगरy_add_sb_mark(काष्ठा fsnotअगरy_group *group,
				काष्ठा super_block *sb, __u32 mask,
				अचिन्हित पूर्णांक flags, __kernel_fsid_t *fsid)
अणु
	वापस fanotअगरy_add_mark(group, &sb->s_fsnotअगरy_marks,
				 FSNOTIFY_OBJ_TYPE_SB, mask, flags, fsid);
पूर्ण

अटल पूर्णांक fanotअगरy_add_inode_mark(काष्ठा fsnotअगरy_group *group,
				   काष्ठा inode *inode, __u32 mask,
				   अचिन्हित पूर्णांक flags, __kernel_fsid_t *fsid)
अणु
	pr_debug("%s: group=%p inode=%p\n", __func__, group, inode);

	/*
	 * If some other task has this inode खोलो क्रम ग_लिखो we should not add
	 * an ignored mark, unless that ignored mark is supposed to survive
	 * modअगरication changes anyway.
	 */
	अगर ((flags & FAN_MARK_IGNORED_MASK) &&
	    !(flags & FAN_MARK_IGNORED_SURV_MODIFY) &&
	    inode_is_खोलो_क्रम_ग_लिखो(inode))
		वापस 0;

	वापस fanotअगरy_add_mark(group, &inode->i_fsnotअगरy_marks,
				 FSNOTIFY_OBJ_TYPE_INODE, mask, flags, fsid);
पूर्ण

अटल काष्ठा fsnotअगरy_event *fanotअगरy_alloc_overflow_event(व्योम)
अणु
	काष्ठा fanotअगरy_event *oevent;

	oevent = kदो_स्मृति(माप(*oevent), GFP_KERNEL_ACCOUNT);
	अगर (!oevent)
		वापस शून्य;

	fanotअगरy_init_event(oevent, 0, FS_Q_OVERFLOW);
	oevent->type = FANOTIFY_EVENT_TYPE_OVERFLOW;

	वापस &oevent->fse;
पूर्ण

अटल काष्ठा hlist_head *fanotअगरy_alloc_merge_hash(व्योम)
अणु
	काष्ठा hlist_head *hash;

	hash = kदो_स्मृति(माप(काष्ठा hlist_head) << FANOTIFY_HTABLE_BITS,
		       GFP_KERNEL_ACCOUNT);
	अगर (!hash)
		वापस शून्य;

	__hash_init(hash, FANOTIFY_HTABLE_SIZE);

	वापस hash;
पूर्ण

/* fanotअगरy syscalls */
SYSCALL_DEFINE2(fanotअगरy_init, अचिन्हित पूर्णांक, flags, अचिन्हित पूर्णांक, event_f_flags)
अणु
	काष्ठा fsnotअगरy_group *group;
	पूर्णांक f_flags, fd;
	अचिन्हित पूर्णांक fid_mode = flags & FANOTIFY_FID_BITS;
	अचिन्हित पूर्णांक class = flags & FANOTIFY_CLASS_BITS;
	अचिन्हित पूर्णांक पूर्णांकernal_flags = 0;

	pr_debug("%s: flags=%x event_f_flags=%x\n",
		 __func__, flags, event_f_flags);

	अगर (!capable(CAP_SYS_ADMIN)) अणु
		/*
		 * An unprivileged user can setup an fanotअगरy group with
		 * limited functionality - an unprivileged group is limited to
		 * notअगरication events with file handles and it cannot use
		 * unlimited queue/marks.
		 */
		अगर ((flags & FANOTIFY_ADMIN_INIT_FLAGS) || !fid_mode)
			वापस -EPERM;

		/*
		 * Setting the पूर्णांकernal flag FANOTIFY_UNPRIV on the group
		 * prevents setting mount/fileप्रणाली marks on this group and
		 * prevents reporting pid and खोलो fd in events.
		 */
		पूर्णांकernal_flags |= FANOTIFY_UNPRIV;
	पूर्ण

#अगर_घोषित CONFIG_AUDITSYSCALL
	अगर (flags & ~(FANOTIFY_INIT_FLAGS | FAN_ENABLE_AUDIT))
#अन्यथा
	अगर (flags & ~FANOTIFY_INIT_FLAGS)
#पूर्ण_अगर
		वापस -EINVAL;

	अगर (event_f_flags & ~FANOTIFY_INIT_ALL_EVENT_F_BITS)
		वापस -EINVAL;

	चयन (event_f_flags & O_ACCMODE) अणु
	हाल O_RDONLY:
	हाल O_RDWR:
	हाल O_WRONLY:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (fid_mode && class != FAN_CLASS_NOTIF)
		वापस -EINVAL;

	/*
	 * Child name is reported with parent fid so requires dir fid.
	 * We can report both child fid and dir fid with or without name.
	 */
	अगर ((fid_mode & FAN_REPORT_NAME) && !(fid_mode & FAN_REPORT_सूची_FID))
		वापस -EINVAL;

	f_flags = O_RDWR | FMODE_NONOTIFY;
	अगर (flags & FAN_CLOEXEC)
		f_flags |= O_CLOEXEC;
	अगर (flags & FAN_NONBLOCK)
		f_flags |= O_NONBLOCK;

	/* fsnotअगरy_alloc_group takes a ref.  Dropped in fanotअगरy_release */
	group = fsnotअगरy_alloc_user_group(&fanotअगरy_fsnotअगरy_ops);
	अगर (IS_ERR(group)) अणु
		वापस PTR_ERR(group);
	पूर्ण

	/* Enक्रमce groups limits per user in all containing user ns */
	group->fanotअगरy_data.ucounts = inc_ucount(current_user_ns(),
						  current_euid(),
						  UCOUNT_FANOTIFY_GROUPS);
	अगर (!group->fanotअगरy_data.ucounts) अणु
		fd = -EMखाता;
		जाओ out_destroy_group;
	पूर्ण

	group->fanotअगरy_data.flags = flags | पूर्णांकernal_flags;
	group->memcg = get_mem_cgroup_from_mm(current->mm);

	group->fanotअगरy_data.merge_hash = fanotअगरy_alloc_merge_hash();
	अगर (!group->fanotअगरy_data.merge_hash) अणु
		fd = -ENOMEM;
		जाओ out_destroy_group;
	पूर्ण

	group->overflow_event = fanotअगरy_alloc_overflow_event();
	अगर (unlikely(!group->overflow_event)) अणु
		fd = -ENOMEM;
		जाओ out_destroy_group;
	पूर्ण

	अगर (क्रमce_o_largefile())
		event_f_flags |= O_LARGEखाता;
	group->fanotअगरy_data.f_flags = event_f_flags;
	init_रुकोqueue_head(&group->fanotअगरy_data.access_रुकोq);
	INIT_LIST_HEAD(&group->fanotअगरy_data.access_list);
	चयन (class) अणु
	हाल FAN_CLASS_NOTIF:
		group->priority = FS_PRIO_0;
		अवरोध;
	हाल FAN_CLASS_CONTENT:
		group->priority = FS_PRIO_1;
		अवरोध;
	हाल FAN_CLASS_PRE_CONTENT:
		group->priority = FS_PRIO_2;
		अवरोध;
	शेष:
		fd = -EINVAL;
		जाओ out_destroy_group;
	पूर्ण

	अगर (flags & FAN_UNLIMITED_QUEUE) अणु
		fd = -EPERM;
		अगर (!capable(CAP_SYS_ADMIN))
			जाओ out_destroy_group;
		group->max_events = अच_पूर्णांक_उच्च;
	पूर्ण अन्यथा अणु
		group->max_events = fanotअगरy_max_queued_events;
	पूर्ण

	अगर (flags & FAN_UNLIMITED_MARKS) अणु
		fd = -EPERM;
		अगर (!capable(CAP_SYS_ADMIN))
			जाओ out_destroy_group;
	पूर्ण

	अगर (flags & FAN_ENABLE_AUDIT) अणु
		fd = -EPERM;
		अगर (!capable(CAP_AUDIT_WRITE))
			जाओ out_destroy_group;
	पूर्ण

	fd = anon_inode_getfd("[fanotify]", &fanotअगरy_fops, group, f_flags);
	अगर (fd < 0)
		जाओ out_destroy_group;

	वापस fd;

out_destroy_group:
	fsnotअगरy_destroy_group(group);
	वापस fd;
पूर्ण

/* Check अगर fileप्रणाली can encode a unique fid */
अटल पूर्णांक fanotअगरy_test_fid(काष्ठा path *path, __kernel_fsid_t *fsid)
अणु
	__kernel_fsid_t root_fsid;
	पूर्णांक err;

	/*
	 * Make sure path is not in fileप्रणाली with zero fsid (e.g. पंचांगpfs).
	 */
	err = vfs_get_fsid(path->dentry, fsid);
	अगर (err)
		वापस err;

	अगर (!fsid->val[0] && !fsid->val[1])
		वापस -ENODEV;

	/*
	 * Make sure path is not inside a fileप्रणाली subvolume (e.g. btrfs)
	 * which uses a dअगरferent fsid than sb root.
	 */
	err = vfs_get_fsid(path->dentry->d_sb->s_root, &root_fsid);
	अगर (err)
		वापस err;

	अगर (root_fsid.val[0] != fsid->val[0] ||
	    root_fsid.val[1] != fsid->val[1])
		वापस -EXDEV;

	/*
	 * We need to make sure that the file प्रणाली supports at least
	 * encoding a file handle so user can use name_to_handle_at() to
	 * compare fid वापसed with event to the file handle of watched
	 * objects. However, name_to_handle_at() requires that the
	 * fileप्रणाली also supports decoding file handles.
	 */
	अगर (!path->dentry->d_sb->s_export_op ||
	    !path->dentry->d_sb->s_export_op->fh_to_dentry)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक fanotअगरy_events_supported(काष्ठा path *path, __u64 mask)
अणु
	/*
	 * Some fileप्रणालीs such as 'proc' acquire unusual locks when खोलोing
	 * files. For them fanotअगरy permission events have high chances of
	 * deadlocking the प्रणाली - खोलो करोne when reporting fanotअगरy event
	 * blocks on this "unusual" lock जबतक another process holding the lock
	 * रुकोs क्रम fanotअगरy permission event to be answered. Just disallow
	 * permission events क्रम such fileप्रणालीs.
	 */
	अगर (mask & FANOTIFY_PERM_EVENTS &&
	    path->mnt->mnt_sb->s_type->fs_flags & FS_DISALLOW_NOTIFY_PERM)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_fanotअगरy_mark(पूर्णांक fanotअगरy_fd, अचिन्हित पूर्णांक flags, __u64 mask,
			    पूर्णांक dfd, स्थिर अक्षर  __user *pathname)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा vfsmount *mnt = शून्य;
	काष्ठा fsnotअगरy_group *group;
	काष्ठा fd f;
	काष्ठा path path;
	__kernel_fsid_t __fsid, *fsid = शून्य;
	u32 valid_mask = FANOTIFY_EVENTS | FANOTIFY_EVENT_FLAGS;
	अचिन्हित पूर्णांक mark_type = flags & FANOTIFY_MARK_TYPE_BITS;
	bool ignored = flags & FAN_MARK_IGNORED_MASK;
	अचिन्हित पूर्णांक obj_type, fid_mode;
	u32 umask = 0;
	पूर्णांक ret;

	pr_debug("%s: fanotify_fd=%d flags=%x dfd=%d pathname=%p mask=%llx\n",
		 __func__, fanotअगरy_fd, flags, dfd, pathname, mask);

	/* we only use the lower 32 bits as of right now. */
	अगर (upper_32_bits(mask))
		वापस -EINVAL;

	अगर (flags & ~FANOTIFY_MARK_FLAGS)
		वापस -EINVAL;

	चयन (mark_type) अणु
	हाल FAN_MARK_INODE:
		obj_type = FSNOTIFY_OBJ_TYPE_INODE;
		अवरोध;
	हाल FAN_MARK_MOUNT:
		obj_type = FSNOTIFY_OBJ_TYPE_VFSMOUNT;
		अवरोध;
	हाल FAN_MARK_खाताSYSTEM:
		obj_type = FSNOTIFY_OBJ_TYPE_SB;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (flags & (FAN_MARK_ADD | FAN_MARK_REMOVE | FAN_MARK_FLUSH)) अणु
	हाल FAN_MARK_ADD:
	हाल FAN_MARK_REMOVE:
		अगर (!mask)
			वापस -EINVAL;
		अवरोध;
	हाल FAN_MARK_FLUSH:
		अगर (flags & ~(FANOTIFY_MARK_TYPE_BITS | FAN_MARK_FLUSH))
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_FANOTIFY_ACCESS_PERMISSIONS))
		valid_mask |= FANOTIFY_PERM_EVENTS;

	अगर (mask & ~valid_mask)
		वापस -EINVAL;

	/* Event flags (ONसूची, ON_CHILD) are meaningless in ignored mask */
	अगर (ignored)
		mask &= ~FANOTIFY_EVENT_FLAGS;

	f = fdget(fanotअगरy_fd);
	अगर (unlikely(!f.file))
		वापस -EBADF;

	/* verअगरy that this is indeed an fanotअगरy instance */
	ret = -EINVAL;
	अगर (unlikely(f.file->f_op != &fanotअगरy_fops))
		जाओ fput_and_out;
	group = f.file->निजी_data;

	/*
	 * An unprivileged user is not allowed to setup mount nor fileप्रणाली
	 * marks.  This also includes setting up such marks by a group that
	 * was initialized by an unprivileged user.
	 */
	ret = -EPERM;
	अगर ((!capable(CAP_SYS_ADMIN) ||
	     FAN_GROUP_FLAG(group, FANOTIFY_UNPRIV)) &&
	    mark_type != FAN_MARK_INODE)
		जाओ fput_and_out;

	/*
	 * group->priority == FS_PRIO_0 == FAN_CLASS_NOTIF.  These are not
	 * allowed to set permissions events.
	 */
	ret = -EINVAL;
	अगर (mask & FANOTIFY_PERM_EVENTS &&
	    group->priority == FS_PRIO_0)
		जाओ fput_and_out;

	/*
	 * Events with data type inode करो not carry enough inक्रमmation to report
	 * event->fd, so we करो not allow setting a mask क्रम inode events unless
	 * group supports reporting fid.
	 * inode events are not supported on a mount mark, because they करो not
	 * carry enough inक्रमmation (i.e. path) to be filtered by mount poपूर्णांक.
	 */
	fid_mode = FAN_GROUP_FLAG(group, FANOTIFY_FID_BITS);
	अगर (mask & FANOTIFY_INODE_EVENTS &&
	    (!fid_mode || mark_type == FAN_MARK_MOUNT))
		जाओ fput_and_out;

	अगर (flags & FAN_MARK_FLUSH) अणु
		ret = 0;
		अगर (mark_type == FAN_MARK_MOUNT)
			fsnotअगरy_clear_vfsmount_marks_by_group(group);
		अन्यथा अगर (mark_type == FAN_MARK_खाताSYSTEM)
			fsnotअगरy_clear_sb_marks_by_group(group);
		अन्यथा
			fsnotअगरy_clear_inode_marks_by_group(group);
		जाओ fput_and_out;
	पूर्ण

	ret = fanotअगरy_find_path(dfd, pathname, &path, flags,
			(mask & ALL_FSNOTIFY_EVENTS), obj_type);
	अगर (ret)
		जाओ fput_and_out;

	अगर (flags & FAN_MARK_ADD) अणु
		ret = fanotअगरy_events_supported(&path, mask);
		अगर (ret)
			जाओ path_put_and_out;
	पूर्ण

	अगर (fid_mode) अणु
		ret = fanotअगरy_test_fid(&path, &__fsid);
		अगर (ret)
			जाओ path_put_and_out;

		fsid = &__fsid;
	पूर्ण

	/* inode held in place by reference to path; group by fget on fd */
	अगर (mark_type == FAN_MARK_INODE)
		inode = path.dentry->d_inode;
	अन्यथा
		mnt = path.mnt;

	/* Mask out FAN_EVENT_ON_CHILD flag क्रम sb/mount/non-dir marks */
	अगर (mnt || !S_ISसूची(inode->i_mode)) अणु
		mask &= ~FAN_EVENT_ON_CHILD;
		umask = FAN_EVENT_ON_CHILD;
		/*
		 * If group needs to report parent fid, रेजिस्टर क्रम getting
		 * events with parent/name info क्रम non-directory.
		 */
		अगर ((fid_mode & FAN_REPORT_सूची_FID) &&
		    (flags & FAN_MARK_ADD) && !ignored)
			mask |= FAN_EVENT_ON_CHILD;
	पूर्ण

	/* create/update an inode mark */
	चयन (flags & (FAN_MARK_ADD | FAN_MARK_REMOVE)) अणु
	हाल FAN_MARK_ADD:
		अगर (mark_type == FAN_MARK_MOUNT)
			ret = fanotअगरy_add_vfsmount_mark(group, mnt, mask,
							 flags, fsid);
		अन्यथा अगर (mark_type == FAN_MARK_खाताSYSTEM)
			ret = fanotअगरy_add_sb_mark(group, mnt->mnt_sb, mask,
						   flags, fsid);
		अन्यथा
			ret = fanotअगरy_add_inode_mark(group, inode, mask,
						      flags, fsid);
		अवरोध;
	हाल FAN_MARK_REMOVE:
		अगर (mark_type == FAN_MARK_MOUNT)
			ret = fanotअगरy_हटाओ_vfsmount_mark(group, mnt, mask,
							    flags, umask);
		अन्यथा अगर (mark_type == FAN_MARK_खाताSYSTEM)
			ret = fanotअगरy_हटाओ_sb_mark(group, mnt->mnt_sb, mask,
						      flags, umask);
		अन्यथा
			ret = fanotअगरy_हटाओ_inode_mark(group, inode, mask,
							 flags, umask);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

path_put_and_out:
	path_put(&path);
fput_and_out:
	fdput(f);
	वापस ret;
पूर्ण

#अगर_अघोषित CONFIG_ARCH_SPLIT_ARG64
SYSCALL_DEFINE5(fanotअगरy_mark, पूर्णांक, fanotअगरy_fd, अचिन्हित पूर्णांक, flags,
			      __u64, mask, पूर्णांक, dfd,
			      स्थिर अक्षर  __user *, pathname)
अणु
	वापस करो_fanotअगरy_mark(fanotअगरy_fd, flags, mask, dfd, pathname);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_SPLIT_ARG64) || defined(CONFIG_COMPAT)
SYSCALL32_DEFINE6(fanotअगरy_mark,
				पूर्णांक, fanotअगरy_fd, अचिन्हित पूर्णांक, flags,
				SC_ARG64(mask), पूर्णांक, dfd,
				स्थिर अक्षर  __user *, pathname)
अणु
	वापस करो_fanotअगरy_mark(fanotअगरy_fd, flags, SC_VAL64(__u64, mask),
				dfd, pathname);
पूर्ण
#पूर्ण_अगर

/*
 * fanotअगरy_user_setup - Our initialization function.  Note that we cannot वापस
 * error because we have compiled-in VFS hooks.  So an (unlikely) failure here
 * must result in panic().
 */
अटल पूर्णांक __init fanotअगरy_user_setup(व्योम)
अणु
	काष्ठा sysinfo si;
	पूर्णांक max_marks;

	si_meminfo(&si);
	/*
	 * Allow up to 1% of addressable memory to be accounted क्रम per user
	 * marks limited to the range [8192, 1048576]. mount and sb marks are
	 * a lot cheaper than inode marks, but there is no reason क्रम a user
	 * to have many of those, so calculate by the cost of inode marks.
	 */
	max_marks = (((si.totalram - si.totalhigh) / 100) << PAGE_SHIFT) /
		    INODE_MARK_COST;
	max_marks = clamp(max_marks, FANOTIFY_OLD_DEFAULT_MAX_MARKS,
				     FANOTIFY_DEFAULT_MAX_USER_MARKS);

	BUILD_BUG_ON(FANOTIFY_INIT_FLAGS & FANOTIFY_INTERNAL_GROUP_FLAGS);
	BUILD_BUG_ON(HWEIGHT32(FANOTIFY_INIT_FLAGS) != 10);
	BUILD_BUG_ON(HWEIGHT32(FANOTIFY_MARK_FLAGS) != 9);

	fanotअगरy_mark_cache = KMEM_CACHE(fsnotअगरy_mark,
					 SLAB_PANIC|SLAB_ACCOUNT);
	fanotअगरy_fid_event_cachep = KMEM_CACHE(fanotअगरy_fid_event,
					       SLAB_PANIC);
	fanotअगरy_path_event_cachep = KMEM_CACHE(fanotअगरy_path_event,
						SLAB_PANIC);
	अगर (IS_ENABLED(CONFIG_FANOTIFY_ACCESS_PERMISSIONS)) अणु
		fanotअगरy_perm_event_cachep =
			KMEM_CACHE(fanotअगरy_perm_event, SLAB_PANIC);
	पूर्ण

	fanotअगरy_max_queued_events = FANOTIFY_DEFAULT_MAX_EVENTS;
	init_user_ns.ucount_max[UCOUNT_FANOTIFY_GROUPS] =
					FANOTIFY_DEFAULT_MAX_GROUPS;
	init_user_ns.ucount_max[UCOUNT_FANOTIFY_MARKS] = max_marks;

	वापस 0;
पूर्ण
device_initcall(fanotअगरy_user_setup);
