<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/module.h>
#समावेश <linux/kobject.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/genhd.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "sys.h"
#समावेश "super.h"
#समावेश "glock.h"
#समावेश "quota.h"
#समावेश "util.h"
#समावेश "glops.h"
#समावेश "recovery.h"

काष्ठा gfs2_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा gfs2_sbd *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा gfs2_sbd *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल sमाप_प्रकार gfs2_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा gfs2_sbd *sdp = container_of(kobj, काष्ठा gfs2_sbd, sd_kobj);
	काष्ठा gfs2_attr *a = container_of(attr, काष्ठा gfs2_attr, attr);
	वापस a->show ? a->show(sdp, buf) : 0;
पूर्ण

अटल sमाप_प्रकार gfs2_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा gfs2_sbd *sdp = container_of(kobj, काष्ठा gfs2_sbd, sd_kobj);
	काष्ठा gfs2_attr *a = container_of(attr, काष्ठा gfs2_attr, attr);
	वापस a->store ? a->store(sdp, buf, len) : len;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops gfs2_attr_ops = अणु
	.show  = gfs2_attr_show,
	.store = gfs2_attr_store,
पूर्ण;


अटल काष्ठा kset *gfs2_kset;

अटल sमाप_प्रकार id_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%u:%u\n",
			MAJOR(sdp->sd_vfs->s_dev), MINOR(sdp->sd_vfs->s_dev));
पूर्ण

अटल sमाप_प्रकार status_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	अचिन्हित दीर्घ f = sdp->sd_flags;
	sमाप_प्रकार s;

	s = snम_लिखो(buf, PAGE_SIZE,
		     "Journal Checked:          %d\n"
		     "Journal Live:             %d\n"
		     "Journal ID:               %d\n"
		     "Spectator:                %d\n"
		     "Withdrawn:                %d\n"
		     "No barriers:              %d\n"
		     "No recovery:              %d\n"
		     "Demote:                   %d\n"
		     "No Journal ID:            %d\n"
		     "Mounted RO:               %d\n"
		     "RO Recovery:              %d\n"
		     "Skip DLM Unlock:          %d\n"
		     "Force AIL Flush:          %d\n"
		     "FS Frozen:                %d\n"
		     "Withdrawing:              %d\n"
		     "Withdraw In Prog:         %d\n"
		     "Remote Withdraw:          %d\n"
		     "Withdraw Recovery:        %d\n"
		     "sd_log_error:             %d\n"
		     "sd_log_flush_lock:        %d\n"
		     "sd_log_num_revoke:        %u\n"
		     "sd_log_in_flight:         %d\n"
		     "sd_log_blks_needed:       %d\n"
		     "sd_log_blks_free:         %d\n"
		     "sd_log_flush_head:        %d\n"
		     "sd_log_flush_tail:        %d\n"
		     "sd_log_blks_reserved:     %d\n"
		     "sd_log_revokes_available: %d\n",
		     test_bit(SDF_JOURNAL_CHECKED, &f),
		     test_bit(SDF_JOURNAL_LIVE, &f),
		     (sdp->sd_jdesc ? sdp->sd_jdesc->jd_jid : 0),
		     (sdp->sd_args.ar_spectator ? 1 : 0),
		     test_bit(SDF_WITHDRAWN, &f),
		     test_bit(SDF_NOBARRIERS, &f),
		     test_bit(SDF_NORECOVERY, &f),
		     test_bit(SDF_DEMOTE, &f),
		     test_bit(SDF_NOJOURNALID, &f),
		     (sb_rकरोnly(sdp->sd_vfs) ? 1 : 0),
		     test_bit(SDF_RORECOVERY, &f),
		     test_bit(SDF_SKIP_DLM_UNLOCK, &f),
		     test_bit(SDF_FORCE_AIL_FLUSH, &f),
		     test_bit(SDF_FS_FROZEN, &f),
		     test_bit(SDF_WITHDRAWING, &f),
		     test_bit(SDF_WITHDRAW_IN_PROG, &f),
		     test_bit(SDF_REMOTE_WITHDRAW, &f),
		     test_bit(SDF_WITHDRAW_RECOVERY, &f),
		     sdp->sd_log_error,
		     rwsem_is_locked(&sdp->sd_log_flush_lock),
		     sdp->sd_log_num_revoke,
		     atomic_पढ़ो(&sdp->sd_log_in_flight),
		     atomic_पढ़ो(&sdp->sd_log_blks_needed),
		     atomic_पढ़ो(&sdp->sd_log_blks_मुक्त),
		     sdp->sd_log_flush_head,
		     sdp->sd_log_flush_tail,
		     sdp->sd_log_blks_reserved,
		     atomic_पढ़ो(&sdp->sd_log_revokes_available));
	वापस s;
पूर्ण

अटल sमाप_प्रकार fsname_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", sdp->sd_fsname);
पूर्ण

अटल sमाप_प्रकार uuid_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	काष्ठा super_block *s = sdp->sd_vfs;

	buf[0] = '\0';
	अगर (uuid_is_null(&s->s_uuid))
		वापस 0;
	वापस snम_लिखो(buf, PAGE_SIZE, "%pUB\n", &s->s_uuid);
पूर्ण

अटल sमाप_प्रकार मुक्तze_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	काष्ठा super_block *sb = sdp->sd_vfs;
	पूर्णांक frozen = (sb->s_ग_लिखोrs.frozen == SB_UNFROZEN) ? 0 : 1;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", frozen);
पूर्ण

अटल sमाप_प्रकार मुक्तze_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक error, n;

	error = kstrtoपूर्णांक(buf, 0, &n);
	अगर (error)
		वापस error;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	चयन (n) अणु
	हाल 0:
		error = thaw_super(sdp->sd_vfs);
		अवरोध;
	हाल 1:
		error = मुक्तze_super(sdp->sd_vfs);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (error) अणु
		fs_warn(sdp, "freeze %d error %d\n", n, error);
		वापस error;
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार withdraw_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक b = gfs2_withdrawn(sdp);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", b);
पूर्ण

अटल sमाप_प्रकार withdraw_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक error, val;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	error = kstrtoपूर्णांक(buf, 0, &val);
	अगर (error)
		वापस error;

	अगर (val != 1)
		वापस -EINVAL;

	gfs2_lm(sdp, "withdrawing from cluster at user's request\n");
	gfs2_withdraw(sdp);

	वापस len;
पूर्ण

अटल sमाप_प्रकार statfs_sync_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf,
				 माप_प्रकार len)
अणु
	पूर्णांक error, val;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	error = kstrtoपूर्णांक(buf, 0, &val);
	अगर (error)
		वापस error;

	अगर (val != 1)
		वापस -EINVAL;

	gfs2_statfs_sync(sdp->sd_vfs, 0);
	वापस len;
पूर्ण

अटल sमाप_प्रकार quota_sync_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf,
				माप_प्रकार len)
अणु
	पूर्णांक error, val;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	error = kstrtoपूर्णांक(buf, 0, &val);
	अगर (error)
		वापस error;

	अगर (val != 1)
		वापस -EINVAL;

	gfs2_quota_sync(sdp->sd_vfs, 0);
	वापस len;
पूर्ण

अटल sमाप_प्रकार quota_refresh_user_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf,
					माप_प्रकार len)
अणु
	काष्ठा kqid qid;
	पूर्णांक error;
	u32 id;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	error = kstrtou32(buf, 0, &id);
	अगर (error)
		वापस error;

	qid = make_kqid(current_user_ns(), USRQUOTA, id);
	अगर (!qid_valid(qid))
		वापस -EINVAL;

	error = gfs2_quota_refresh(sdp, qid);
	वापस error ? error : len;
पूर्ण

अटल sमाप_प्रकार quota_refresh_group_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf,
					 माप_प्रकार len)
अणु
	काष्ठा kqid qid;
	पूर्णांक error;
	u32 id;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	error = kstrtou32(buf, 0, &id);
	अगर (error)
		वापस error;

	qid = make_kqid(current_user_ns(), GRPQUOTA, id);
	अगर (!qid_valid(qid))
		वापस -EINVAL;

	error = gfs2_quota_refresh(sdp, qid);
	वापस error ? error : len;
पूर्ण

अटल sमाप_प्रकार demote_rq_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा gfs2_glock *gl;
	स्थिर काष्ठा gfs2_glock_operations *glops;
	अचिन्हित पूर्णांक glmode;
	अचिन्हित पूर्णांक gltype;
	अचिन्हित दीर्घ दीर्घ glnum;
	अक्षर mode[16];
	पूर्णांक rv;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	rv = माला_पूछो(buf, "%u:%llu %15s", &gltype, &glnum,
		    mode);
	अगर (rv != 3)
		वापस -EINVAL;

	अगर (म_भेद(mode, "EX") == 0)
		glmode = LM_ST_UNLOCKED;
	अन्यथा अगर ((म_भेद(mode, "CW") == 0) || (म_भेद(mode, "DF") == 0))
		glmode = LM_ST_DEFERRED;
	अन्यथा अगर ((म_भेद(mode, "PR") == 0) || (म_भेद(mode, "SH") == 0))
		glmode = LM_ST_SHARED;
	अन्यथा
		वापस -EINVAL;

	अगर (gltype > LM_TYPE_JOURNAL)
		वापस -EINVAL;
	अगर (gltype == LM_TYPE_NONDISK && glnum == GFS2_FREEZE_LOCK)
		glops = &gfs2_मुक्तze_glops;
	अन्यथा
		glops = gfs2_glops_list[gltype];
	अगर (glops == शून्य)
		वापस -EINVAL;
	अगर (!test_and_set_bit(SDF_DEMOTE, &sdp->sd_flags))
		fs_info(sdp, "demote interface used\n");
	rv = gfs2_glock_get(sdp, glnum, glops, 0, &gl);
	अगर (rv)
		वापस rv;
	gfs2_glock_cb(gl, glmode);
	gfs2_glock_put(gl);
	वापस len;
पूर्ण


#घोषणा GFS2_ATTR(name, mode, show, store) \
अटल काष्ठा gfs2_attr gfs2_attr_##name = __ATTR(name, mode, show, store)

GFS2_ATTR(id,                  0444, id_show,       शून्य);
GFS2_ATTR(fsname,              0444, fsname_show,   शून्य);
GFS2_ATTR(uuid,                0444, uuid_show,     शून्य);
GFS2_ATTR(मुक्तze,              0644, मुक्तze_show,   मुक्तze_store);
GFS2_ATTR(withdraw,            0644, withdraw_show, withdraw_store);
GFS2_ATTR(statfs_sync,         0200, शून्य,          statfs_sync_store);
GFS2_ATTR(quota_sync,          0200, शून्य,          quota_sync_store);
GFS2_ATTR(quota_refresh_user,  0200, शून्य,          quota_refresh_user_store);
GFS2_ATTR(quota_refresh_group, 0200, शून्य,          quota_refresh_group_store);
GFS2_ATTR(demote_rq,           0200, शून्य,	    demote_rq_store);
GFS2_ATTR(status,              0400, status_show,   शून्य);

अटल काष्ठा attribute *gfs2_attrs[] = अणु
	&gfs2_attr_id.attr,
	&gfs2_attr_fsname.attr,
	&gfs2_attr_uuid.attr,
	&gfs2_attr_मुक्तze.attr,
	&gfs2_attr_withdraw.attr,
	&gfs2_attr_statfs_sync.attr,
	&gfs2_attr_quota_sync.attr,
	&gfs2_attr_quota_refresh_user.attr,
	&gfs2_attr_quota_refresh_group.attr,
	&gfs2_attr_demote_rq.attr,
	&gfs2_attr_status.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(gfs2);

अटल व्योम gfs2_sbd_release(काष्ठा kobject *kobj)
अणु
	काष्ठा gfs2_sbd *sdp = container_of(kobj, काष्ठा gfs2_sbd, sd_kobj);

	complete(&sdp->sd_kobj_unरेजिस्टर);
पूर्ण

अटल काष्ठा kobj_type gfs2_ktype = अणु
	.release = gfs2_sbd_release,
	.शेष_groups = gfs2_groups,
	.sysfs_ops     = &gfs2_attr_ops,
पूर्ण;


/*
 * lock_module. Originally from lock_dlm
 */

अटल sमाप_प्रकार proto_name_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	स्थिर काष्ठा lm_lockops *ops = sdp->sd_lockकाष्ठा.ls_ops;
	वापस प्र_लिखो(buf, "%s\n", ops->lm_proto_name);
पूर्ण

अटल sमाप_प्रकार block_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	sमाप_प्रकार ret;
	पूर्णांक val = 0;

	अगर (test_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags))
		val = 1;
	ret = प्र_लिखो(buf, "%d\n", val);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार block_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	पूर्णांक ret, val;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val == 1)
		set_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags);
	अन्यथा अगर (val == 0) अणु
		clear_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags);
		smp_mb__after_atomic();
		gfs2_glock_thaw(sdp);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस len;
पूर्ण

अटल sमाप_प्रकार wdack_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	पूर्णांक val = completion_करोne(&sdp->sd_wdack) ? 1 : 0;

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार wdack_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक ret, val;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर ((val == 1) &&
	    !म_भेद(sdp->sd_lockकाष्ठा.ls_ops->lm_proto_name, "lock_dlm"))
		complete(&sdp->sd_wdack);
	अन्यथा
		वापस -EINVAL;
	वापस len;
पूर्ण

अटल sमाप_प्रकार lkfirst_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	वापस प्र_लिखो(buf, "%d\n", ls->ls_first);
पूर्ण

अटल sमाप_प्रकार lkfirst_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित first;
	पूर्णांक rv;

	rv = माला_पूछो(buf, "%u", &first);
	अगर (rv != 1 || first > 1)
		वापस -EINVAL;
	rv = रुको_क्रम_completion_समाप्तable(&sdp->sd_locking_init);
	अगर (rv)
		वापस rv;
	spin_lock(&sdp->sd_jindex_spin);
	rv = -EBUSY;
	अगर (test_bit(SDF_NOJOURNALID, &sdp->sd_flags) == 0)
		जाओ out;
	rv = -EINVAL;
	अगर (sdp->sd_args.ar_spectator)
		जाओ out;
	अगर (sdp->sd_lockकाष्ठा.ls_ops->lm_mount == शून्य)
		जाओ out;
	sdp->sd_lockकाष्ठा.ls_first = first;
	rv = 0;
out:
        spin_unlock(&sdp->sd_jindex_spin);
        वापस rv ? rv : len;
पूर्ण

अटल sमाप_प्रकार first_करोne_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	वापस प्र_लिखो(buf, "%d\n", !!test_bit(DFL_FIRST_MOUNT_DONE, &ls->ls_recover_flags));
पूर्ण

पूर्णांक gfs2_recover_set(काष्ठा gfs2_sbd *sdp, अचिन्हित jid)
अणु
	काष्ठा gfs2_jdesc *jd;
	पूर्णांक rv;

	/* Wait क्रम our primary journal to be initialized */
	रुको_क्रम_completion(&sdp->sd_journal_पढ़ोy);

	spin_lock(&sdp->sd_jindex_spin);
	rv = -EBUSY;
	/**
	 * If we're a spectator, we use journal0, but it's not really ours.
	 * So we need to रुको क्रम its recovery too. If we skip it we'd never
	 * queue work to the recovery workqueue, and so its completion would
	 * never clear the DFL_BLOCK_LOCKS flag, so all our locks would
	 * permanently stop working.
	 */
	अगर (!sdp->sd_jdesc)
		जाओ out;
	अगर (sdp->sd_jdesc->jd_jid == jid && !sdp->sd_args.ar_spectator)
		जाओ out;
	rv = -ENOENT;
	list_क्रम_each_entry(jd, &sdp->sd_jindex_list, jd_list) अणु
		अगर (jd->jd_jid != jid && !sdp->sd_args.ar_spectator)
			जारी;
		rv = gfs2_recover_journal(jd, false);
		अवरोध;
	पूर्ण
out:
	spin_unlock(&sdp->sd_jindex_spin);
	वापस rv;
पूर्ण

अटल sमाप_प्रकार recover_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित jid;
	पूर्णांक rv;

	rv = माला_पूछो(buf, "%u", &jid);
	अगर (rv != 1)
		वापस -EINVAL;

	अगर (test_bit(SDF_NORECOVERY, &sdp->sd_flags)) अणु
		rv = -ESHUTDOWN;
		जाओ out;
	पूर्ण

	rv = gfs2_recover_set(sdp, jid);
out:
	वापस rv ? rv : len;
पूर्ण

अटल sमाप_प्रकार recover_करोne_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	वापस प्र_लिखो(buf, "%d\n", ls->ls_recover_jid_करोne);
पूर्ण

अटल sमाप_प्रकार recover_status_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	वापस प्र_लिखो(buf, "%d\n", ls->ls_recover_jid_status);
पूर्ण

अटल sमाप_प्रकार jid_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", sdp->sd_lockकाष्ठा.ls_jid);
पूर्ण

अटल sमाप_प्रकार jid_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
        पूर्णांक jid;
	पूर्णांक rv;

	rv = माला_पूछो(buf, "%d", &jid);
	अगर (rv != 1)
		वापस -EINVAL;
	rv = रुको_क्रम_completion_समाप्तable(&sdp->sd_locking_init);
	अगर (rv)
		वापस rv;
	spin_lock(&sdp->sd_jindex_spin);
	rv = -EINVAL;
	अगर (sdp->sd_lockकाष्ठा.ls_ops->lm_mount == शून्य)
		जाओ out;
	rv = -EBUSY;
	अगर (test_bit(SDF_NOJOURNALID, &sdp->sd_flags) == 0)
		जाओ out;
	rv = 0;
	अगर (sdp->sd_args.ar_spectator && jid > 0)
		rv = jid = -EINVAL;
	sdp->sd_lockकाष्ठा.ls_jid = jid;
	clear_bit(SDF_NOJOURNALID, &sdp->sd_flags);
	smp_mb__after_atomic();
	wake_up_bit(&sdp->sd_flags, SDF_NOJOURNALID);
out:
	spin_unlock(&sdp->sd_jindex_spin);
	वापस rv ? rv : len;
पूर्ण

#घोषणा GDLM_ATTR(_name,_mode,_show,_store) \
अटल काष्ठा gfs2_attr gdlm_attr_##_name = __ATTR(_name,_mode,_show,_store)

GDLM_ATTR(proto_name,		0444, proto_name_show,		शून्य);
GDLM_ATTR(block,		0644, block_show,		block_store);
GDLM_ATTR(withdraw,		0644, wdack_show,		wdack_store);
GDLM_ATTR(jid,			0644, jid_show,			jid_store);
GDLM_ATTR(first,		0644, lkfirst_show,		lkfirst_store);
GDLM_ATTR(first_करोne,		0444, first_करोne_show,		शून्य);
GDLM_ATTR(recover,		0600, शून्य,			recover_store);
GDLM_ATTR(recover_करोne,		0444, recover_करोne_show,	शून्य);
GDLM_ATTR(recover_status,	0444, recover_status_show,	शून्य);

अटल काष्ठा attribute *lock_module_attrs[] = अणु
	&gdlm_attr_proto_name.attr,
	&gdlm_attr_block.attr,
	&gdlm_attr_withdraw.attr,
	&gdlm_attr_jid.attr,
	&gdlm_attr_first.attr,
	&gdlm_attr_first_करोne.attr,
	&gdlm_attr_recover.attr,
	&gdlm_attr_recover_करोne.attr,
	&gdlm_attr_recover_status.attr,
	शून्य,
पूर्ण;

/*
 * get and set काष्ठा gfs2_tune fields
 */

अटल sमाप_प्रकार quota_scale_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%u %u\n",
			sdp->sd_tune.gt_quota_scale_num,
			sdp->sd_tune.gt_quota_scale_den);
पूर्ण

अटल sमाप_प्रकार quota_scale_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf,
				 माप_प्रकार len)
अणु
	काष्ठा gfs2_tune *gt = &sdp->sd_tune;
	अचिन्हित पूर्णांक x, y;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (माला_पूछो(buf, "%u %u", &x, &y) != 2 || !y)
		वापस -EINVAL;

	spin_lock(&gt->gt_spin);
	gt->gt_quota_scale_num = x;
	gt->gt_quota_scale_den = y;
	spin_unlock(&gt->gt_spin);
	वापस len;
पूर्ण

अटल sमाप_प्रकार tune_set(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक *field,
			पूर्णांक check_zero, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा gfs2_tune *gt = &sdp->sd_tune;
	अचिन्हित पूर्णांक x;
	पूर्णांक error;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	error = kstrtouपूर्णांक(buf, 0, &x);
	अगर (error)
		वापस error;

	अगर (check_zero && !x)
		वापस -EINVAL;

	spin_lock(&gt->gt_spin);
	*field = x;
	spin_unlock(&gt->gt_spin);
	वापस len;
पूर्ण

#घोषणा TUNE_ATTR_3(name, show, store)                                        \
अटल काष्ठा gfs2_attr tune_attr_##name = __ATTR(name, 0644, show, store)

#घोषणा TUNE_ATTR_2(name, store)                                              \
अटल sमाप_प्रकार name##_show(काष्ठा gfs2_sbd *sdp, अक्षर *buf)                   \
अणु                                                                             \
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", sdp->sd_tune.gt_##name);      \
पूर्ण                                                                             \
TUNE_ATTR_3(name, name##_show, store)

#घोषणा TUNE_ATTR(name, check_zero)                                           \
अटल sमाप_प्रकार name##_store(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *buf, माप_प्रकार len)\
अणु                                                                             \
	वापस tune_set(sdp, &sdp->sd_tune.gt_##name, check_zero, buf, len);  \
पूर्ण                                                                             \
TUNE_ATTR_2(name, name##_store)

TUNE_ATTR(quota_warn_period, 0);
TUNE_ATTR(quota_quantum, 0);
TUNE_ATTR(max_पढ़ोahead, 0);
TUNE_ATTR(complain_secs, 0);
TUNE_ATTR(statfs_slow, 0);
TUNE_ATTR(new_files_jdata, 0);
TUNE_ATTR(statfs_quantum, 1);
TUNE_ATTR_3(quota_scale, quota_scale_show, quota_scale_store);

अटल काष्ठा attribute *tune_attrs[] = अणु
	&tune_attr_quota_warn_period.attr,
	&tune_attr_quota_quantum.attr,
	&tune_attr_max_पढ़ोahead.attr,
	&tune_attr_complain_secs.attr,
	&tune_attr_statfs_slow.attr,
	&tune_attr_statfs_quantum.attr,
	&tune_attr_quota_scale.attr,
	&tune_attr_new_files_jdata.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group tune_group = अणु
	.name = "tune",
	.attrs = tune_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lock_module_group = अणु
	.name = "lock_module",
	.attrs = lock_module_attrs,
पूर्ण;

पूर्णांक gfs2_sys_fs_add(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा super_block *sb = sdp->sd_vfs;
	पूर्णांक error;
	अक्षर ro[20];
	अक्षर spectator[20];
	अक्षर *envp[] = अणु ro, spectator, शून्य पूर्ण;

	प्र_लिखो(ro, "RDONLY=%d", sb_rकरोnly(sb));
	प्र_लिखो(spectator, "SPECTATOR=%d", sdp->sd_args.ar_spectator ? 1 : 0);

	init_completion(&sdp->sd_kobj_unरेजिस्टर);
	sdp->sd_kobj.kset = gfs2_kset;
	error = kobject_init_and_add(&sdp->sd_kobj, &gfs2_ktype, शून्य,
				     "%s", sdp->sd_table_name);
	अगर (error)
		जाओ fail_reg;

	error = sysfs_create_group(&sdp->sd_kobj, &tune_group);
	अगर (error)
		जाओ fail_reg;

	error = sysfs_create_group(&sdp->sd_kobj, &lock_module_group);
	अगर (error)
		जाओ fail_tune;

	error = sysfs_create_link(&sdp->sd_kobj,
				  &disk_to_dev(sb->s_bdev->bd_disk)->kobj,
				  "device");
	अगर (error)
		जाओ fail_lock_module;

	kobject_uevent_env(&sdp->sd_kobj, KOBJ_ADD, envp);
	वापस 0;

fail_lock_module:
	sysfs_हटाओ_group(&sdp->sd_kobj, &lock_module_group);
fail_tune:
	sysfs_हटाओ_group(&sdp->sd_kobj, &tune_group);
fail_reg:
	fs_err(sdp, "error %d adding sysfs files\n", error);
	kobject_put(&sdp->sd_kobj);
	रुको_क्रम_completion(&sdp->sd_kobj_unरेजिस्टर);
	sb->s_fs_info = शून्य;
	वापस error;
पूर्ण

व्योम gfs2_sys_fs_del(काष्ठा gfs2_sbd *sdp)
अणु
	sysfs_हटाओ_link(&sdp->sd_kobj, "device");
	sysfs_हटाओ_group(&sdp->sd_kobj, &tune_group);
	sysfs_हटाओ_group(&sdp->sd_kobj, &lock_module_group);
	kobject_put(&sdp->sd_kobj);
	रुको_क्रम_completion(&sdp->sd_kobj_unरेजिस्टर);
पूर्ण

अटल पूर्णांक gfs2_uevent(काष्ठा kset *kset, काष्ठा kobject *kobj,
		       काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा gfs2_sbd *sdp = container_of(kobj, काष्ठा gfs2_sbd, sd_kobj);
	काष्ठा super_block *s = sdp->sd_vfs;

	add_uevent_var(env, "LOCKTABLE=%s", sdp->sd_table_name);
	add_uevent_var(env, "LOCKPROTO=%s", sdp->sd_proto_name);
	अगर (!test_bit(SDF_NOJOURNALID, &sdp->sd_flags))
		add_uevent_var(env, "JOURNALID=%d", sdp->sd_lockकाष्ठा.ls_jid);
	अगर (!uuid_is_null(&s->s_uuid))
		add_uevent_var(env, "UUID=%pUB", &s->s_uuid);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kset_uevent_ops gfs2_uevent_ops = अणु
	.uevent = gfs2_uevent,
पूर्ण;

पूर्णांक gfs2_sys_init(व्योम)
अणु
	gfs2_kset = kset_create_and_add("gfs2", &gfs2_uevent_ops, fs_kobj);
	अगर (!gfs2_kset)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम gfs2_sys_uninit(व्योम)
अणु
	kset_unरेजिस्टर(gfs2_kset);
पूर्ण

