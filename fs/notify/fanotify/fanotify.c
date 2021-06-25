<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fanotअगरy.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h> /* अच_पूर्णांक_उच्च */
#समावेश <linux/mount.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/user.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/audit.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/statfs.h>
#समावेश <linux/stringhash.h>

#समावेश "fanotify.h"

अटल bool fanotअगरy_path_equal(काष्ठा path *p1, काष्ठा path *p2)
अणु
	वापस p1->mnt == p2->mnt && p1->dentry == p2->dentry;
पूर्ण

अटल अचिन्हित पूर्णांक fanotअगरy_hash_path(स्थिर काष्ठा path *path)
अणु
	वापस hash_ptr(path->dentry, FANOTIFY_EVENT_HASH_BITS) ^
		hash_ptr(path->mnt, FANOTIFY_EVENT_HASH_BITS);
पूर्ण

अटल अंतरभूत bool fanotअगरy_fsid_equal(__kernel_fsid_t *fsid1,
				       __kernel_fsid_t *fsid2)
अणु
	वापस fsid1->val[0] == fsid2->val[0] && fsid1->val[1] == fsid2->val[1];
पूर्ण

अटल अचिन्हित पूर्णांक fanotअगरy_hash_fsid(__kernel_fsid_t *fsid)
अणु
	वापस hash_32(fsid->val[0], FANOTIFY_EVENT_HASH_BITS) ^
		hash_32(fsid->val[1], FANOTIFY_EVENT_HASH_BITS);
पूर्ण

अटल bool fanotअगरy_fh_equal(काष्ठा fanotअगरy_fh *fh1,
			      काष्ठा fanotअगरy_fh *fh2)
अणु
	अगर (fh1->type != fh2->type || fh1->len != fh2->len)
		वापस false;

	वापस !fh1->len ||
		!स_भेद(fanotअगरy_fh_buf(fh1), fanotअगरy_fh_buf(fh2), fh1->len);
पूर्ण

अटल अचिन्हित पूर्णांक fanotअगरy_hash_fh(काष्ठा fanotअगरy_fh *fh)
अणु
	दीर्घ salt = (दीर्घ)fh->type | (दीर्घ)fh->len << 8;

	/*
	 * full_name_hash() works दीर्घ by दीर्घ, so it handles fh buf optimally.
	 */
	वापस full_name_hash((व्योम *)salt, fanotअगरy_fh_buf(fh), fh->len);
पूर्ण

अटल bool fanotअगरy_fid_event_equal(काष्ठा fanotअगरy_fid_event *ffe1,
				     काष्ठा fanotअगरy_fid_event *ffe2)
अणु
	/* Do not merge fid events without object fh */
	अगर (!ffe1->object_fh.len)
		वापस false;

	वापस fanotअगरy_fsid_equal(&ffe1->fsid, &ffe2->fsid) &&
		fanotअगरy_fh_equal(&ffe1->object_fh, &ffe2->object_fh);
पूर्ण

अटल bool fanotअगरy_info_equal(काष्ठा fanotअगरy_info *info1,
				काष्ठा fanotअगरy_info *info2)
अणु
	अगर (info1->dir_fh_totlen != info2->dir_fh_totlen ||
	    info1->file_fh_totlen != info2->file_fh_totlen ||
	    info1->name_len != info2->name_len)
		वापस false;

	अगर (info1->dir_fh_totlen &&
	    !fanotअगरy_fh_equal(fanotअगरy_info_dir_fh(info1),
			       fanotअगरy_info_dir_fh(info2)))
		वापस false;

	अगर (info1->file_fh_totlen &&
	    !fanotअगरy_fh_equal(fanotअगरy_info_file_fh(info1),
			       fanotअगरy_info_file_fh(info2)))
		वापस false;

	वापस !info1->name_len ||
		!स_भेद(fanotअगरy_info_name(info1), fanotअगरy_info_name(info2),
			info1->name_len);
पूर्ण

अटल bool fanotअगरy_name_event_equal(काष्ठा fanotअगरy_name_event *fne1,
				      काष्ठा fanotअगरy_name_event *fne2)
अणु
	काष्ठा fanotअगरy_info *info1 = &fne1->info;
	काष्ठा fanotअगरy_info *info2 = &fne2->info;

	/* Do not merge name events without dir fh */
	अगर (!info1->dir_fh_totlen)
		वापस false;

	अगर (!fanotअगरy_fsid_equal(&fne1->fsid, &fne2->fsid))
		वापस false;

	वापस fanotअगरy_info_equal(info1, info2);
पूर्ण

अटल bool fanotअगरy_should_merge(काष्ठा fanotअगरy_event *old,
				  काष्ठा fanotअगरy_event *new)
अणु
	pr_debug("%s: old=%p new=%p\n", __func__, old, new);

	अगर (old->hash != new->hash ||
	    old->type != new->type || old->pid != new->pid)
		वापस false;

	/*
	 * We want to merge many dirent events in the same dir (i.e.
	 * creates/unlinks/नामs), but we करो not want to merge dirent
	 * events referring to subdirs with dirent events referring to
	 * non subdirs, otherwise, user won't be able to tell from a
	 * mask FAN_CREATE|FAN_DELETE|FAN_ONसूची अगर it describes सूची_गढ़ो+
	 * unlink pair or सूची_हटाओ+create pair of events.
	 */
	अगर ((old->mask & FS_ISसूची) != (new->mask & FS_ISसूची))
		वापस false;

	चयन (old->type) अणु
	हाल FANOTIFY_EVENT_TYPE_PATH:
		वापस fanotअगरy_path_equal(fanotअगरy_event_path(old),
					   fanotअगरy_event_path(new));
	हाल FANOTIFY_EVENT_TYPE_FID:
		वापस fanotअगरy_fid_event_equal(FANOTIFY_FE(old),
						FANOTIFY_FE(new));
	हाल FANOTIFY_EVENT_TYPE_FID_NAME:
		वापस fanotअगरy_name_event_equal(FANOTIFY_NE(old),
						 FANOTIFY_NE(new));
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण

	वापस false;
पूर्ण

/* Limit event merges to limit CPU overhead per event */
#घोषणा FANOTIFY_MAX_MERGE_EVENTS 128

/* and the list better be locked by something too! */
अटल पूर्णांक fanotअगरy_merge(काष्ठा fsnotअगरy_group *group,
			  काष्ठा fsnotअगरy_event *event)
अणु
	काष्ठा fanotअगरy_event *old, *new = FANOTIFY_E(event);
	अचिन्हित पूर्णांक bucket = fanotअगरy_event_hash_bucket(group, new);
	काष्ठा hlist_head *hlist = &group->fanotअगरy_data.merge_hash[bucket];
	पूर्णांक i = 0;

	pr_debug("%s: group=%p event=%p bucket=%u\n", __func__,
		 group, event, bucket);

	/*
	 * Don't merge a permission event with any other event so that we know
	 * the event काष्ठाure we have created in fanotअगरy_handle_event() is the
	 * one we should check क्रम permission response.
	 */
	अगर (fanotअगरy_is_perm_event(new->mask))
		वापस 0;

	hlist_क्रम_each_entry(old, hlist, merge_list) अणु
		अगर (++i > FANOTIFY_MAX_MERGE_EVENTS)
			अवरोध;
		अगर (fanotअगरy_should_merge(old, new)) अणु
			old->mask |= new->mask;
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Wait क्रम response to permission event. The function also takes care of
 * मुक्तing the permission event (or offloads that in हाल the रुको is canceled
 * by a संकेत). The function वापसs 0 in हाल access got allowed by userspace,
 * -EPERM in हाल userspace disallowed the access, and -ERESTARTSYS in हाल
 * the रुको got पूर्णांकerrupted by a संकेत.
 */
अटल पूर्णांक fanotअगरy_get_response(काष्ठा fsnotअगरy_group *group,
				 काष्ठा fanotअगरy_perm_event *event,
				 काष्ठा fsnotअगरy_iter_info *iter_info)
अणु
	पूर्णांक ret;

	pr_debug("%s: group=%p event=%p\n", __func__, group, event);

	ret = रुको_event_समाप्तable(group->fanotअगरy_data.access_रुकोq,
				  event->state == FAN_EVENT_ANSWERED);
	/* Signal pending? */
	अगर (ret < 0) अणु
		spin_lock(&group->notअगरication_lock);
		/* Event reported to userspace and no answer yet? */
		अगर (event->state == FAN_EVENT_REPORTED) अणु
			/* Event will get मुक्तd once userspace answers to it */
			event->state = FAN_EVENT_CANCELED;
			spin_unlock(&group->notअगरication_lock);
			वापस ret;
		पूर्ण
		/* Event not yet reported? Just हटाओ it. */
		अगर (event->state == FAN_EVENT_INIT) अणु
			fsnotअगरy_हटाओ_queued_event(group, &event->fae.fse);
			/* Permission events are not supposed to be hashed */
			WARN_ON_ONCE(!hlist_unhashed(&event->fae.merge_list));
		पूर्ण
		/*
		 * Event may be also answered in हाल संकेत delivery raced
		 * with wakeup. In that हाल we have nothing to करो besides
		 * मुक्तing the event and reporting error.
		 */
		spin_unlock(&group->notअगरication_lock);
		जाओ out;
	पूर्ण

	/* userspace responded, convert to something usable */
	चयन (event->response & ~FAN_AUDIT) अणु
	हाल FAN_ALLOW:
		ret = 0;
		अवरोध;
	हाल FAN_DENY:
	शेष:
		ret = -EPERM;
	पूर्ण

	/* Check अगर the response should be audited */
	अगर (event->response & FAN_AUDIT)
		audit_fanotअगरy(event->response & ~FAN_AUDIT);

	pr_debug("%s: group=%p event=%p about to return ret=%d\n", __func__,
		 group, event, ret);
out:
	fsnotअगरy_destroy_event(group, &event->fae.fse);

	वापस ret;
पूर्ण

/*
 * This function वापसs a mask क्रम an event that only contains the flags
 * that have been specअगरically requested by the user. Flags that may have
 * been included within the event mask, but have not been explicitly
 * requested by the user, will not be present in the वापसed mask.
 */
अटल u32 fanotअगरy_group_event_mask(काष्ठा fsnotअगरy_group *group,
				     काष्ठा fsnotअगरy_iter_info *iter_info,
				     u32 event_mask, स्थिर व्योम *data,
				     पूर्णांक data_type, काष्ठा inode *dir)
अणु
	__u32 marks_mask = 0, marks_ignored_mask = 0;
	__u32 test_mask, user_mask = FANOTIFY_OUTGOING_EVENTS |
				     FANOTIFY_EVENT_FLAGS;
	स्थिर काष्ठा path *path = fsnotअगरy_data_path(data, data_type);
	अचिन्हित पूर्णांक fid_mode = FAN_GROUP_FLAG(group, FANOTIFY_FID_BITS);
	काष्ठा fsnotअगरy_mark *mark;
	पूर्णांक type;

	pr_debug("%s: report_mask=%x mask=%x data=%p data_type=%d\n",
		 __func__, iter_info->report_mask, event_mask, data, data_type);

	अगर (!fid_mode) अणु
		/* Do we have path to खोलो a file descriptor? */
		अगर (!path)
			वापस 0;
		/* Path type events are only relevant क्रम files and dirs */
		अगर (!d_is_reg(path->dentry) && !d_can_lookup(path->dentry))
			वापस 0;
	पूर्ण अन्यथा अगर (!(fid_mode & FAN_REPORT_FID)) अणु
		/* Do we have a directory inode to report? */
		अगर (!dir && !(event_mask & FS_ISसूची))
			वापस 0;
	पूर्ण

	fsnotअगरy_क्रमeach_obj_type(type) अणु
		अगर (!fsnotअगरy_iter_should_report_type(iter_info, type))
			जारी;
		mark = iter_info->marks[type];

		/* Apply ignore mask regardless of ISसूची and ON_CHILD flags */
		marks_ignored_mask |= mark->ignored_mask;

		/*
		 * If the event is on dir and this mark करोesn't care about
		 * events on dir, करोn't send it!
		 */
		अगर (event_mask & FS_ISसूची && !(mark->mask & FS_ISसूची))
			जारी;

		/*
		 * If the event is on a child and this mark is on a parent not
		 * watching children, करोn't send it!
		 */
		अगर (type == FSNOTIFY_OBJ_TYPE_PARENT &&
		    !(mark->mask & FS_EVENT_ON_CHILD))
			जारी;

		marks_mask |= mark->mask;
	पूर्ण

	test_mask = event_mask & marks_mask & ~marks_ignored_mask;

	/*
	 * For dirent modअगरication events (create/delete/move) that करो not carry
	 * the child entry name inक्रमmation, we report FAN_ONसूची क्रम सूची_गढ़ो/सूची_हटाओ
	 * so user can dअगरferentiate them from creat/unlink.
	 *
	 * For backward compatibility and consistency, करो not report FAN_ONसूची
	 * to user in legacy fanotअगरy mode (reporting fd) and report FAN_ONसूची
	 * to user in fid mode क्रम all event types.
	 *
	 * We never report FAN_EVENT_ON_CHILD to user, but we करो pass it in to
	 * fanotअगरy_alloc_event() when group is reporting fid as indication
	 * that event happened on child.
	 */
	अगर (fid_mode) अणु
		/* Do not report event flags without any event */
		अगर (!(test_mask & ~FANOTIFY_EVENT_FLAGS))
			वापस 0;
	पूर्ण अन्यथा अणु
		user_mask &= ~FANOTIFY_EVENT_FLAGS;
	पूर्ण

	वापस test_mask & user_mask;
पूर्ण

/*
 * Check size needed to encode fanotअगरy_fh.
 *
 * Return size of encoded fh without fanotअगरy_fh header.
 * Return 0 on failure to encode.
 */
अटल पूर्णांक fanotअगरy_encode_fh_len(काष्ठा inode *inode)
अणु
	पूर्णांक dwords = 0;

	अगर (!inode)
		वापस 0;

	exportfs_encode_inode_fh(inode, शून्य, &dwords, शून्य);

	वापस dwords << 2;
पूर्ण

/*
 * Encode fanotअगरy_fh.
 *
 * Return total size of encoded fh including fanotअगरy_fh header.
 * Return 0 on failure to encode.
 */
अटल पूर्णांक fanotअगरy_encode_fh(काष्ठा fanotअगरy_fh *fh, काष्ठा inode *inode,
			      अचिन्हित पूर्णांक fh_len, अचिन्हित पूर्णांक *hash,
			      gfp_t gfp)
अणु
	पूर्णांक dwords, type = 0;
	अक्षर *ext_buf = शून्य;
	व्योम *buf = fh->buf;
	पूर्णांक err;

	fh->type = खाताID_ROOT;
	fh->len = 0;
	fh->flags = 0;
	अगर (!inode)
		वापस 0;

	/*
	 * !gpf means pपुनः_स्मृतिated variable size fh, but fh_len could
	 * be zero in that हाल अगर encoding fh len failed.
	 */
	err = -ENOENT;
	अगर (fh_len < 4 || WARN_ON_ONCE(fh_len % 4))
		जाओ out_err;

	/* No बाह्यal buffer in a variable size allocated fh */
	अगर (gfp && fh_len > FANOTIFY_INLINE_FH_LEN) अणु
		/* Treat failure to allocate fh as failure to encode fh */
		err = -ENOMEM;
		ext_buf = kदो_स्मृति(fh_len, gfp);
		अगर (!ext_buf)
			जाओ out_err;

		*fanotअगरy_fh_ext_buf_ptr(fh) = ext_buf;
		buf = ext_buf;
		fh->flags |= FANOTIFY_FH_FLAG_EXT_BUF;
	पूर्ण

	dwords = fh_len >> 2;
	type = exportfs_encode_inode_fh(inode, buf, &dwords, शून्य);
	err = -EINVAL;
	अगर (!type || type == खाताID_INVALID || fh_len != dwords << 2)
		जाओ out_err;

	fh->type = type;
	fh->len = fh_len;

	/* Mix fh पूर्णांकo event merge key */
	*hash ^= fanotअगरy_hash_fh(fh);

	वापस FANOTIFY_FH_HDR_LEN + fh_len;

out_err:
	pr_warn_ratelimited("fanotify: failed to encode fid (type=%d, len=%d, err=%i)\n",
			    type, fh_len, err);
	kमुक्त(ext_buf);
	*fanotअगरy_fh_ext_buf_ptr(fh) = शून्य;
	/* Report the event without a file identअगरier on encode error */
	fh->type = खाताID_INVALID;
	fh->len = 0;
	वापस 0;
पूर्ण

/*
 * The inode to use as identअगरier when reporting fid depends on the event.
 * Report the modअगरied directory inode on dirent modअगरication events.
 * Report the "victim" inode otherwise.
 * For example:
 * FS_ATTRIB reports the child inode even अगर reported on a watched parent.
 * FS_CREATE reports the modअगरied dir inode and not the created inode.
 */
अटल काष्ठा inode *fanotअगरy_fid_inode(u32 event_mask, स्थिर व्योम *data,
					पूर्णांक data_type, काष्ठा inode *dir)
अणु
	अगर (event_mask & ALL_FSNOTIFY_सूचीENT_EVENTS)
		वापस dir;

	वापस fsnotअगरy_data_inode(data, data_type);
पूर्ण

/*
 * The inode to use as identअगरier when reporting dir fid depends on the event.
 * Report the modअगरied directory inode on dirent modअगरication events.
 * Report the "victim" inode अगर "victim" is a directory.
 * Report the parent inode अगर "victim" is not a directory and event is
 * reported to parent.
 * Otherwise, करो not report dir fid.
 */
अटल काष्ठा inode *fanotअगरy_dfid_inode(u32 event_mask, स्थिर व्योम *data,
					 पूर्णांक data_type, काष्ठा inode *dir)
अणु
	काष्ठा inode *inode = fsnotअगरy_data_inode(data, data_type);

	अगर (event_mask & ALL_FSNOTIFY_सूचीENT_EVENTS)
		वापस dir;

	अगर (S_ISसूची(inode->i_mode))
		वापस inode;

	वापस dir;
पूर्ण

अटल काष्ठा fanotअगरy_event *fanotअगरy_alloc_path_event(स्थिर काष्ठा path *path,
							अचिन्हित पूर्णांक *hash,
							gfp_t gfp)
अणु
	काष्ठा fanotअगरy_path_event *pevent;

	pevent = kmem_cache_alloc(fanotअगरy_path_event_cachep, gfp);
	अगर (!pevent)
		वापस शून्य;

	pevent->fae.type = FANOTIFY_EVENT_TYPE_PATH;
	pevent->path = *path;
	*hash ^= fanotअगरy_hash_path(path);
	path_get(path);

	वापस &pevent->fae;
पूर्ण

अटल काष्ठा fanotअगरy_event *fanotअगरy_alloc_perm_event(स्थिर काष्ठा path *path,
							gfp_t gfp)
अणु
	काष्ठा fanotअगरy_perm_event *pevent;

	pevent = kmem_cache_alloc(fanotअगरy_perm_event_cachep, gfp);
	अगर (!pevent)
		वापस शून्य;

	pevent->fae.type = FANOTIFY_EVENT_TYPE_PATH_PERM;
	pevent->response = 0;
	pevent->state = FAN_EVENT_INIT;
	pevent->path = *path;
	path_get(path);

	वापस &pevent->fae;
पूर्ण

अटल काष्ठा fanotअगरy_event *fanotअगरy_alloc_fid_event(काष्ठा inode *id,
						       __kernel_fsid_t *fsid,
						       अचिन्हित पूर्णांक *hash,
						       gfp_t gfp)
अणु
	काष्ठा fanotअगरy_fid_event *ffe;

	ffe = kmem_cache_alloc(fanotअगरy_fid_event_cachep, gfp);
	अगर (!ffe)
		वापस शून्य;

	ffe->fae.type = FANOTIFY_EVENT_TYPE_FID;
	ffe->fsid = *fsid;
	*hash ^= fanotअगरy_hash_fsid(fsid);
	fanotअगरy_encode_fh(&ffe->object_fh, id, fanotअगरy_encode_fh_len(id),
			   hash, gfp);

	वापस &ffe->fae;
पूर्ण

अटल काष्ठा fanotअगरy_event *fanotअगरy_alloc_name_event(काष्ठा inode *id,
							__kernel_fsid_t *fsid,
							स्थिर काष्ठा qstr *name,
							काष्ठा inode *child,
							अचिन्हित पूर्णांक *hash,
							gfp_t gfp)
अणु
	काष्ठा fanotअगरy_name_event *fne;
	काष्ठा fanotअगरy_info *info;
	काष्ठा fanotअगरy_fh *dfh, *ffh;
	अचिन्हित पूर्णांक dir_fh_len = fanotअगरy_encode_fh_len(id);
	अचिन्हित पूर्णांक child_fh_len = fanotअगरy_encode_fh_len(child);
	अचिन्हित पूर्णांक size;

	size = माप(*fne) + FANOTIFY_FH_HDR_LEN + dir_fh_len;
	अगर (child_fh_len)
		size += FANOTIFY_FH_HDR_LEN + child_fh_len;
	अगर (name)
		size += name->len + 1;
	fne = kदो_स्मृति(size, gfp);
	अगर (!fne)
		वापस शून्य;

	fne->fae.type = FANOTIFY_EVENT_TYPE_FID_NAME;
	fne->fsid = *fsid;
	*hash ^= fanotअगरy_hash_fsid(fsid);
	info = &fne->info;
	fanotअगरy_info_init(info);
	dfh = fanotअगरy_info_dir_fh(info);
	info->dir_fh_totlen = fanotअगरy_encode_fh(dfh, id, dir_fh_len, hash, 0);
	अगर (child_fh_len) अणु
		ffh = fanotअगरy_info_file_fh(info);
		info->file_fh_totlen = fanotअगरy_encode_fh(ffh, child,
							child_fh_len, hash, 0);
	पूर्ण
	अगर (name) अणु
		दीर्घ salt = name->len;

		fanotअगरy_info_copy_name(info, name);
		*hash ^= full_name_hash((व्योम *)salt, name->name, name->len);
	पूर्ण

	pr_debug("%s: ino=%lu size=%u dir_fh_len=%u child_fh_len=%u name_len=%u name='%.*s'\n",
		 __func__, id->i_ino, size, dir_fh_len, child_fh_len,
		 info->name_len, info->name_len, fanotअगरy_info_name(info));

	वापस &fne->fae;
पूर्ण

अटल काष्ठा fanotअगरy_event *fanotअगरy_alloc_event(काष्ठा fsnotअगरy_group *group,
						   u32 mask, स्थिर व्योम *data,
						   पूर्णांक data_type, काष्ठा inode *dir,
						   स्थिर काष्ठा qstr *file_name,
						   __kernel_fsid_t *fsid)
अणु
	काष्ठा fanotअगरy_event *event = शून्य;
	gfp_t gfp = GFP_KERNEL_ACCOUNT;
	काष्ठा inode *id = fanotअगरy_fid_inode(mask, data, data_type, dir);
	काष्ठा inode *dirid = fanotअगरy_dfid_inode(mask, data, data_type, dir);
	स्थिर काष्ठा path *path = fsnotअगरy_data_path(data, data_type);
	अचिन्हित पूर्णांक fid_mode = FAN_GROUP_FLAG(group, FANOTIFY_FID_BITS);
	काष्ठा mem_cgroup *old_memcg;
	काष्ठा inode *child = शून्य;
	bool name_event = false;
	अचिन्हित पूर्णांक hash = 0;
	bool ondir = mask & FAN_ONसूची;
	काष्ठा pid *pid;

	अगर ((fid_mode & FAN_REPORT_सूची_FID) && dirid) अणु
		/*
		 * With both flags FAN_REPORT_सूची_FID and FAN_REPORT_FID, we
		 * report the child fid क्रम events reported on a non-dir child
		 * in addition to reporting the parent fid and maybe child name.
		 */
		अगर ((fid_mode & FAN_REPORT_FID) && id != dirid && !ondir)
			child = id;

		id = dirid;

		/*
		 * We record file name only in a group with FAN_REPORT_NAME
		 * and when we have a directory inode to report.
		 *
		 * For directory entry modअगरication event, we record the fid of
		 * the directory and the name of the modअगरied entry.
		 *
		 * For event on non-directory that is reported to parent, we
		 * record the fid of the parent and the name of the child.
		 *
		 * Even अगर not reporting name, we need a variable length
		 * fanotअगरy_name_event अगर reporting both parent and child fids.
		 */
		अगर (!(fid_mode & FAN_REPORT_NAME)) अणु
			name_event = !!child;
			file_name = शून्य;
		पूर्ण अन्यथा अगर ((mask & ALL_FSNOTIFY_सूचीENT_EVENTS) || !ondir) अणु
			name_event = true;
		पूर्ण
	पूर्ण

	/*
	 * For queues with unlimited length lost events are not expected and
	 * can possibly have security implications. Aव्योम losing events when
	 * memory is लघु. For the limited size queues, aव्योम OOM समाप्तer in the
	 * target monitoring memcg as it may have security repercussion.
	 */
	अगर (group->max_events == अच_पूर्णांक_उच्च)
		gfp |= __GFP_NOFAIL;
	अन्यथा
		gfp |= __GFP_RETRY_MAYFAIL;

	/* Whoever is पूर्णांकerested in the event, pays क्रम the allocation. */
	old_memcg = set_active_memcg(group->memcg);

	अगर (fanotअगरy_is_perm_event(mask)) अणु
		event = fanotअगरy_alloc_perm_event(path, gfp);
	पूर्ण अन्यथा अगर (name_event && (file_name || child)) अणु
		event = fanotअगरy_alloc_name_event(id, fsid, file_name, child,
						  &hash, gfp);
	पूर्ण अन्यथा अगर (fid_mode) अणु
		event = fanotअगरy_alloc_fid_event(id, fsid, &hash, gfp);
	पूर्ण अन्यथा अणु
		event = fanotअगरy_alloc_path_event(path, &hash, gfp);
	पूर्ण

	अगर (!event)
		जाओ out;

	अगर (FAN_GROUP_FLAG(group, FAN_REPORT_TID))
		pid = get_pid(task_pid(current));
	अन्यथा
		pid = get_pid(task_tgid(current));

	/* Mix event info, FAN_ONसूची flag and pid पूर्णांकo event merge key */
	hash ^= hash_दीर्घ((अचिन्हित दीर्घ)pid | ondir, FANOTIFY_EVENT_HASH_BITS);
	fanotअगरy_init_event(event, hash, mask);
	event->pid = pid;

out:
	set_active_memcg(old_memcg);
	वापस event;
पूर्ण

/*
 * Get cached fsid of the fileप्रणाली containing the object from any connector.
 * All connectors are supposed to have the same fsid, but we करो not verअगरy that
 * here.
 */
अटल __kernel_fsid_t fanotअगरy_get_fsid(काष्ठा fsnotअगरy_iter_info *iter_info)
अणु
	पूर्णांक type;
	__kernel_fsid_t fsid = अणुपूर्ण;

	fsnotअगरy_क्रमeach_obj_type(type) अणु
		काष्ठा fsnotअगरy_mark_connector *conn;

		अगर (!fsnotअगरy_iter_should_report_type(iter_info, type))
			जारी;

		conn = READ_ONCE(iter_info->marks[type]->connector);
		/* Mark is just getting destroyed or created? */
		अगर (!conn)
			जारी;
		अगर (!(conn->flags & FSNOTIFY_CONN_FLAG_HAS_FSID))
			जारी;
		/* Pairs with smp_wmb() in fsnotअगरy_add_mark_list() */
		smp_rmb();
		fsid = conn->fsid;
		अगर (WARN_ON_ONCE(!fsid.val[0] && !fsid.val[1]))
			जारी;
		वापस fsid;
	पूर्ण

	वापस fsid;
पूर्ण

/*
 * Add an event to hash table क्रम faster merge.
 */
अटल व्योम fanotअगरy_insert_event(काष्ठा fsnotअगरy_group *group,
				  काष्ठा fsnotअगरy_event *fsn_event)
अणु
	काष्ठा fanotअगरy_event *event = FANOTIFY_E(fsn_event);
	अचिन्हित पूर्णांक bucket = fanotअगरy_event_hash_bucket(group, event);
	काष्ठा hlist_head *hlist = &group->fanotअगरy_data.merge_hash[bucket];

	निश्चित_spin_locked(&group->notअगरication_lock);

	pr_debug("%s: group=%p event=%p bucket=%u\n", __func__,
		 group, event, bucket);

	hlist_add_head(&event->merge_list, hlist);
पूर्ण

अटल पूर्णांक fanotअगरy_handle_event(काष्ठा fsnotअगरy_group *group, u32 mask,
				 स्थिर व्योम *data, पूर्णांक data_type,
				 काष्ठा inode *dir,
				 स्थिर काष्ठा qstr *file_name, u32 cookie,
				 काष्ठा fsnotअगरy_iter_info *iter_info)
अणु
	पूर्णांक ret = 0;
	काष्ठा fanotअगरy_event *event;
	काष्ठा fsnotअगरy_event *fsn_event;
	__kernel_fsid_t fsid = अणुपूर्ण;

	BUILD_BUG_ON(FAN_ACCESS != FS_ACCESS);
	BUILD_BUG_ON(FAN_MODIFY != FS_MODIFY);
	BUILD_BUG_ON(FAN_ATTRIB != FS_ATTRIB);
	BUILD_BUG_ON(FAN_CLOSE_NOWRITE != FS_CLOSE_NOWRITE);
	BUILD_BUG_ON(FAN_CLOSE_WRITE != FS_CLOSE_WRITE);
	BUILD_BUG_ON(FAN_OPEN != FS_OPEN);
	BUILD_BUG_ON(FAN_MOVED_TO != FS_MOVED_TO);
	BUILD_BUG_ON(FAN_MOVED_FROM != FS_MOVED_FROM);
	BUILD_BUG_ON(FAN_CREATE != FS_CREATE);
	BUILD_BUG_ON(FAN_DELETE != FS_DELETE);
	BUILD_BUG_ON(FAN_DELETE_SELF != FS_DELETE_SELF);
	BUILD_BUG_ON(FAN_MOVE_SELF != FS_MOVE_SELF);
	BUILD_BUG_ON(FAN_EVENT_ON_CHILD != FS_EVENT_ON_CHILD);
	BUILD_BUG_ON(FAN_Q_OVERFLOW != FS_Q_OVERFLOW);
	BUILD_BUG_ON(FAN_OPEN_PERM != FS_OPEN_PERM);
	BUILD_BUG_ON(FAN_ACCESS_PERM != FS_ACCESS_PERM);
	BUILD_BUG_ON(FAN_ONसूची != FS_ISसूची);
	BUILD_BUG_ON(FAN_OPEN_EXEC != FS_OPEN_EXEC);
	BUILD_BUG_ON(FAN_OPEN_EXEC_PERM != FS_OPEN_EXEC_PERM);

	BUILD_BUG_ON(HWEIGHT32(ALL_FANOTIFY_EVENT_BITS) != 19);

	mask = fanotअगरy_group_event_mask(group, iter_info, mask, data,
					 data_type, dir);
	अगर (!mask)
		वापस 0;

	pr_debug("%s: group=%p mask=%x\n", __func__, group, mask);

	अगर (fanotअगरy_is_perm_event(mask)) अणु
		/*
		 * fsnotअगरy_prepare_user_रुको() fails अगर we race with mark
		 * deletion.  Just let the operation pass in that हाल.
		 */
		अगर (!fsnotअगरy_prepare_user_रुको(iter_info))
			वापस 0;
	पूर्ण

	अगर (FAN_GROUP_FLAG(group, FANOTIFY_FID_BITS)) अणु
		fsid = fanotअगरy_get_fsid(iter_info);
		/* Racing with mark deकाष्ठाion or creation? */
		अगर (!fsid.val[0] && !fsid.val[1])
			वापस 0;
	पूर्ण

	event = fanotअगरy_alloc_event(group, mask, data, data_type, dir,
				     file_name, &fsid);
	ret = -ENOMEM;
	अगर (unlikely(!event)) अणु
		/*
		 * We करोn't queue overflow events क्रम permission events as
		 * there the access is denied and so no event is in fact lost.
		 */
		अगर (!fanotअगरy_is_perm_event(mask))
			fsnotअगरy_queue_overflow(group);
		जाओ finish;
	पूर्ण

	fsn_event = &event->fse;
	ret = fsnotअगरy_add_event(group, fsn_event, fanotअगरy_merge,
				 fanotअगरy_is_hashed_event(mask) ?
				 fanotअगरy_insert_event : शून्य);
	अगर (ret) अणु
		/* Permission events shouldn't be merged */
		BUG_ON(ret == 1 && mask & FANOTIFY_PERM_EVENTS);
		/* Our event wasn't used in the end. Free it. */
		fsnotअगरy_destroy_event(group, fsn_event);

		ret = 0;
	पूर्ण अन्यथा अगर (fanotअगरy_is_perm_event(mask)) अणु
		ret = fanotअगरy_get_response(group, FANOTIFY_PERM(event),
					    iter_info);
	पूर्ण
finish:
	अगर (fanotअगरy_is_perm_event(mask))
		fsnotअगरy_finish_user_रुको(iter_info);

	वापस ret;
पूर्ण

अटल व्योम fanotअगरy_मुक्त_group_priv(काष्ठा fsnotअगरy_group *group)
अणु
	kमुक्त(group->fanotअगरy_data.merge_hash);
	अगर (group->fanotअगरy_data.ucounts)
		dec_ucount(group->fanotअगरy_data.ucounts,
			   UCOUNT_FANOTIFY_GROUPS);
पूर्ण

अटल व्योम fanotअगरy_मुक्त_path_event(काष्ठा fanotअगरy_event *event)
अणु
	path_put(fanotअगरy_event_path(event));
	kmem_cache_मुक्त(fanotअगरy_path_event_cachep, FANOTIFY_PE(event));
पूर्ण

अटल व्योम fanotअगरy_मुक्त_perm_event(काष्ठा fanotअगरy_event *event)
अणु
	path_put(fanotअगरy_event_path(event));
	kmem_cache_मुक्त(fanotअगरy_perm_event_cachep, FANOTIFY_PERM(event));
पूर्ण

अटल व्योम fanotअगरy_मुक्त_fid_event(काष्ठा fanotअगरy_event *event)
अणु
	काष्ठा fanotअगरy_fid_event *ffe = FANOTIFY_FE(event);

	अगर (fanotअगरy_fh_has_ext_buf(&ffe->object_fh))
		kमुक्त(fanotअगरy_fh_ext_buf(&ffe->object_fh));
	kmem_cache_मुक्त(fanotअगरy_fid_event_cachep, ffe);
पूर्ण

अटल व्योम fanotअगरy_मुक्त_name_event(काष्ठा fanotअगरy_event *event)
अणु
	kमुक्त(FANOTIFY_NE(event));
पूर्ण

अटल व्योम fanotअगरy_मुक्त_event(काष्ठा fsnotअगरy_event *fsn_event)
अणु
	काष्ठा fanotअगरy_event *event;

	event = FANOTIFY_E(fsn_event);
	put_pid(event->pid);
	चयन (event->type) अणु
	हाल FANOTIFY_EVENT_TYPE_PATH:
		fanotअगरy_मुक्त_path_event(event);
		अवरोध;
	हाल FANOTIFY_EVENT_TYPE_PATH_PERM:
		fanotअगरy_मुक्त_perm_event(event);
		अवरोध;
	हाल FANOTIFY_EVENT_TYPE_FID:
		fanotअगरy_मुक्त_fid_event(event);
		अवरोध;
	हाल FANOTIFY_EVENT_TYPE_FID_NAME:
		fanotअगरy_मुक्त_name_event(event);
		अवरोध;
	हाल FANOTIFY_EVENT_TYPE_OVERFLOW:
		kमुक्त(event);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल व्योम fanotअगरy_मुक्तing_mark(काष्ठा fsnotअगरy_mark *mark,
				  काष्ठा fsnotअगरy_group *group)
अणु
	अगर (!FAN_GROUP_FLAG(group, FAN_UNLIMITED_MARKS))
		dec_ucount(group->fanotअगरy_data.ucounts, UCOUNT_FANOTIFY_MARKS);
पूर्ण

अटल व्योम fanotअगरy_मुक्त_mark(काष्ठा fsnotअगरy_mark *fsn_mark)
अणु
	kmem_cache_मुक्त(fanotअगरy_mark_cache, fsn_mark);
पूर्ण

स्थिर काष्ठा fsnotअगरy_ops fanotअगरy_fsnotअगरy_ops = अणु
	.handle_event = fanotअगरy_handle_event,
	.मुक्त_group_priv = fanotअगरy_मुक्त_group_priv,
	.मुक्त_event = fanotअगरy_मुक्त_event,
	.मुक्तing_mark = fanotअगरy_मुक्तing_mark,
	.मुक्त_mark = fanotअगरy_मुक्त_mark,
पूर्ण;
