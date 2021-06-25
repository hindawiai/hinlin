<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved
 * Copyright 2001-2006 Ian Kent <raven@themaw.net>
 */

#समावेश <linux/sched/संकेत.स>
#समावेश "autofs_i.h"

/* We make this a अटल variable rather than a part of the superblock; it
 * is better अगर we करोn't reassign numbers easily even across fileप्रणालीs
 */
अटल स्वतःfs_wqt_t स्वतःfs_next_रुको_queue = 1;

व्योम स्वतःfs_catatonic_mode(काष्ठा स्वतःfs_sb_info *sbi)
अणु
	काष्ठा स्वतःfs_रुको_queue *wq, *nwq;

	mutex_lock(&sbi->wq_mutex);
	अगर (sbi->flags & AUTOFS_SBI_CATATONIC) अणु
		mutex_unlock(&sbi->wq_mutex);
		वापस;
	पूर्ण

	pr_debug("entering catatonic mode\n");

	sbi->flags |= AUTOFS_SBI_CATATONIC;
	wq = sbi->queues;
	sbi->queues = शून्य;	/* Erase all रुको queues */
	जबतक (wq) अणु
		nwq = wq->next;
		wq->status = -ENOENT; /* Magic is gone - report failure */
		kमुक्त(wq->name.name - wq->offset);
		wq->name.name = शून्य;
		wq->रुको_ctr--;
		wake_up_पूर्णांकerruptible(&wq->queue);
		wq = nwq;
	पूर्ण
	fput(sbi->pipe);	/* Close the pipe */
	sbi->pipe = शून्य;
	sbi->pipefd = -1;
	mutex_unlock(&sbi->wq_mutex);
पूर्ण

अटल पूर्णांक स्वतःfs_ग_लिखो(काष्ठा स्वतःfs_sb_info *sbi,
			काष्ठा file *file, स्थिर व्योम *addr, पूर्णांक bytes)
अणु
	अचिन्हित दीर्घ sigpipe, flags;
	स्थिर अक्षर *data = (स्थिर अक्षर *)addr;
	sमाप_प्रकार wr = 0;

	sigpipe = sigismember(&current->pending.संकेत, SIGPIPE);

	mutex_lock(&sbi->pipe_mutex);
	जबतक (bytes) अणु
		wr = __kernel_ग_लिखो(file, data, bytes, शून्य);
		अगर (wr <= 0)
			अवरोध;
		data += wr;
		bytes -= wr;
	पूर्ण
	mutex_unlock(&sbi->pipe_mutex);

	/* Keep the currently executing process from receiving a
	 * SIGPIPE unless it was alपढ़ोy supposed to get one
	 */
	अगर (wr == -EPIPE && !sigpipe) अणु
		spin_lock_irqsave(&current->sighand->siglock, flags);
		sigdअन्यथाt(&current->pending.संकेत, SIGPIPE);
		recalc_संक_बाकी();
		spin_unlock_irqrestore(&current->sighand->siglock, flags);
	पूर्ण

	/* अगर 'wr' वापसed 0 (impossible) we assume -EIO (safe) */
	वापस bytes == 0 ? 0 : wr < 0 ? wr : -EIO;
पूर्ण

अटल व्योम स्वतःfs_notअगरy_daemon(काष्ठा स्वतःfs_sb_info *sbi,
				 काष्ठा स्वतःfs_रुको_queue *wq,
				 पूर्णांक type)
अणु
	जोड़ अणु
		काष्ठा स्वतःfs_packet_hdr hdr;
		जोड़ स्वतःfs_packet_जोड़ v4_pkt;
		जोड़ स्वतःfs_v5_packet_जोड़ v5_pkt;
	पूर्ण pkt;
	काष्ठा file *pipe = शून्य;
	माप_प्रकार pktsz;
	पूर्णांक ret;

	pr_debug("wait id = 0x%08lx, name = %.*s, type=%d\n",
		 (अचिन्हित दीर्घ) wq->रुको_queue_token,
		 wq->name.len, wq->name.name, type);

	स_रखो(&pkt, 0, माप(pkt)); /* For security reasons */

	pkt.hdr.proto_version = sbi->version;
	pkt.hdr.type = type;

	चयन (type) अणु
	/* Kernel protocol v4 missing and expire packets */
	हाल स्वतःfs_ptype_missing:
	अणु
		काष्ठा स्वतःfs_packet_missing *mp = &pkt.v4_pkt.missing;

		pktsz = माप(*mp);

		mp->रुको_queue_token = wq->रुको_queue_token;
		mp->len = wq->name.len;
		स_नकल(mp->name, wq->name.name, wq->name.len);
		mp->name[wq->name.len] = '\0';
		अवरोध;
	पूर्ण
	हाल स्वतःfs_ptype_expire_multi:
	अणु
		काष्ठा स्वतःfs_packet_expire_multi *ep =
					&pkt.v4_pkt.expire_multi;

		pktsz = माप(*ep);

		ep->रुको_queue_token = wq->रुको_queue_token;
		ep->len = wq->name.len;
		स_नकल(ep->name, wq->name.name, wq->name.len);
		ep->name[wq->name.len] = '\0';
		अवरोध;
	पूर्ण
	/*
	 * Kernel protocol v5 packet क्रम handling indirect and direct
	 * mount missing and expire requests
	 */
	हाल स्वतःfs_ptype_missing_indirect:
	हाल स्वतःfs_ptype_expire_indirect:
	हाल स्वतःfs_ptype_missing_direct:
	हाल स्वतःfs_ptype_expire_direct:
	अणु
		काष्ठा स्वतःfs_v5_packet *packet = &pkt.v5_pkt.v5_packet;
		काष्ठा user_namespace *user_ns = sbi->pipe->f_cred->user_ns;

		pktsz = माप(*packet);

		packet->रुको_queue_token = wq->रुको_queue_token;
		packet->len = wq->name.len;
		स_नकल(packet->name, wq->name.name, wq->name.len);
		packet->name[wq->name.len] = '\0';
		packet->dev = wq->dev;
		packet->ino = wq->ino;
		packet->uid = from_kuid_munged(user_ns, wq->uid);
		packet->gid = from_kgid_munged(user_ns, wq->gid);
		packet->pid = wq->pid;
		packet->tgid = wq->tgid;
		अवरोध;
	पूर्ण
	शेष:
		pr_warn("bad type %d!\n", type);
		mutex_unlock(&sbi->wq_mutex);
		वापस;
	पूर्ण

	pipe = get_file(sbi->pipe);

	mutex_unlock(&sbi->wq_mutex);

	चयन (ret = स्वतःfs_ग_लिखो(sbi, pipe, &pkt, pktsz)) अणु
	हाल 0:
		अवरोध;
	हाल -ENOMEM:
	हाल -ERESTARTSYS:
		/* Just fail this one */
		स्वतःfs_रुको_release(sbi, wq->रुको_queue_token, ret);
		अवरोध;
	शेष:
		स्वतःfs_catatonic_mode(sbi);
		अवरोध;
	पूर्ण
	fput(pipe);
पूर्ण

अटल काष्ठा स्वतःfs_रुको_queue *
स्वतःfs_find_रुको(काष्ठा स्वतःfs_sb_info *sbi, स्थिर काष्ठा qstr *qstr)
अणु
	काष्ठा स्वतःfs_रुको_queue *wq;

	क्रम (wq = sbi->queues; wq; wq = wq->next) अणु
		अगर (wq->name.hash == qstr->hash &&
		    wq->name.len == qstr->len &&
		    wq->name.name &&
		    !स_भेद(wq->name.name, qstr->name, qstr->len))
			अवरोध;
	पूर्ण
	वापस wq;
पूर्ण

/*
 * Check अगर we have a valid request.
 * Returns
 * 1 अगर the request should जारी.
 *   In this हाल we can वापस an स्वतःfs_रुको_queue entry अगर one is
 *   found or शून्य to idicate a new रुको needs to be created.
 * 0 or a negative त्रुटि_सं अगर the request shouldn't जारी.
 */
अटल पूर्णांक validate_request(काष्ठा स्वतःfs_रुको_queue **रुको,
			    काष्ठा स्वतःfs_sb_info *sbi,
			    स्थिर काष्ठा qstr *qstr,
			    स्थिर काष्ठा path *path, क्रमागत स्वतःfs_notअगरy notअगरy)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा स्वतःfs_रुको_queue *wq;
	काष्ठा स्वतःfs_info *ino;

	अगर (sbi->flags & AUTOFS_SBI_CATATONIC)
		वापस -ENOENT;

	/* Wait in progress, जारी; */
	wq = स्वतःfs_find_रुको(sbi, qstr);
	अगर (wq) अणु
		*रुको = wq;
		वापस 1;
	पूर्ण

	*रुको = शून्य;

	/* If we करोn't yet have any info this is a new request */
	ino = स्वतःfs_dentry_ino(dentry);
	अगर (!ino)
		वापस 1;

	/*
	 * If we've been asked to रुको on an existing expire (NFY_NONE)
	 * but there is no रुको in the queue ...
	 */
	अगर (notअगरy == NFY_NONE) अणु
		/*
		 * Either we've betean the pending expire to post it's
		 * रुको or it finished जबतक we रुकोed on the mutex.
		 * So we need to रुको till either, the रुको appears
		 * or the expire finishes.
		 */

		जबतक (ino->flags & AUTOFS_INF_EXPIRING) अणु
			mutex_unlock(&sbi->wq_mutex);
			schedule_समयout_पूर्णांकerruptible(HZ/10);
			अगर (mutex_lock_पूर्णांकerruptible(&sbi->wq_mutex))
				वापस -EINTR;

			अगर (sbi->flags & AUTOFS_SBI_CATATONIC)
				वापस -ENOENT;

			wq = स्वतःfs_find_रुको(sbi, qstr);
			अगर (wq) अणु
				*रुको = wq;
				वापस 1;
			पूर्ण
		पूर्ण

		/*
		 * Not ideal but the status has alपढ़ोy gone. Of the two
		 * हालs where we रुको on NFY_NONE neither depend on the
		 * वापस status of the रुको.
		 */
		वापस 0;
	पूर्ण

	/*
	 * If we've been asked to trigger a mount and the request
	 * completed जबतक we रुकोed on the mutex ...
	 */
	अगर (notअगरy == NFY_MOUNT) अणु
		काष्ठा dentry *new = शून्य;
		काष्ठा path this;
		पूर्णांक valid = 1;

		/*
		 * If the dentry was successfully mounted जबतक we slept
		 * on the रुको queue mutex we can वापस success. If it
		 * isn't mounted (doesn't have submounts क्रम the हाल of
		 * a multi-mount with no mount at it's base) we can
		 * जारी on and create a new request.
		 */
		अगर (!IS_ROOT(dentry)) अणु
			अगर (d_unhashed(dentry) &&
			    d_really_is_positive(dentry)) अणु
				काष्ठा dentry *parent = dentry->d_parent;

				new = d_lookup(parent, &dentry->d_name);
				अगर (new)
					dentry = new;
			पूर्ण
		पूर्ण
		this.mnt = path->mnt;
		this.dentry = dentry;
		अगर (path_has_submounts(&this))
			valid = 0;

		अगर (new)
			dput(new);
		वापस valid;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक स्वतःfs_रुको(काष्ठा स्वतःfs_sb_info *sbi,
		 स्थिर काष्ठा path *path, क्रमागत स्वतःfs_notअगरy notअगरy)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा स्वतःfs_रुको_queue *wq;
	काष्ठा qstr qstr;
	अक्षर *name;
	पूर्णांक status, ret, type;
	अचिन्हित पूर्णांक offset = 0;
	pid_t pid;
	pid_t tgid;

	/* In catatonic mode, we करोn't रुको क्रम nobody */
	अगर (sbi->flags & AUTOFS_SBI_CATATONIC)
		वापस -ENOENT;

	/*
	 * Try translating pids to the namespace of the daemon.
	 *
	 * Zero means failure: we are in an unrelated pid namespace.
	 */
	pid = task_pid_nr_ns(current, ns_of_pid(sbi->oz_pgrp));
	tgid = task_tgid_nr_ns(current, ns_of_pid(sbi->oz_pgrp));
	अगर (pid == 0 || tgid == 0)
		वापस -ENOENT;

	अगर (d_really_is_negative(dentry)) अणु
		/*
		 * A रुको क्रम a negative dentry is invalid क्रम certain
		 * हालs. A direct or offset mount "always" has its mount
		 * poपूर्णांक directory created and so the request dentry must
		 * be positive or the map key करोesn't exist. The situation
		 * is very similar क्रम indirect mounts except only dentrys
		 * in the root of the स्वतःfs file प्रणाली may be negative.
		 */
		अगर (स्वतःfs_type_trigger(sbi->type))
			वापस -ENOENT;
		अन्यथा अगर (!IS_ROOT(dentry->d_parent))
			वापस -ENOENT;
	पूर्ण

	name = kदो_स्मृति(NAME_MAX + 1, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;

	/* If this is a direct mount request create a dummy name */
	अगर (IS_ROOT(dentry) && स्वतःfs_type_trigger(sbi->type)) अणु
		qstr.name = name;
		qstr.len = प्र_लिखो(name, "%p", dentry);
	पूर्ण अन्यथा अणु
		अक्षर *p = dentry_path_raw(dentry, name, NAME_MAX);
		अगर (IS_ERR(p)) अणु
			kमुक्त(name);
			वापस -ENOENT;
		पूर्ण
		qstr.name = ++p; // skip the leading slash
		qstr.len = म_माप(p);
		offset = p - name;
	पूर्ण
	qstr.hash = full_name_hash(dentry, name, qstr.len);

	अगर (mutex_lock_पूर्णांकerruptible(&sbi->wq_mutex)) अणु
		kमुक्त(name);
		वापस -EINTR;
	पूर्ण

	ret = validate_request(&wq, sbi, &qstr, path, notअगरy);
	अगर (ret <= 0) अणु
		अगर (ret != -EINTR)
			mutex_unlock(&sbi->wq_mutex);
		kमुक्त(name);
		वापस ret;
	पूर्ण

	अगर (!wq) अणु
		/* Create a new रुको queue */
		wq = kदो_स्मृति(माप(काष्ठा स्वतःfs_रुको_queue), GFP_KERNEL);
		अगर (!wq) अणु
			kमुक्त(name);
			mutex_unlock(&sbi->wq_mutex);
			वापस -ENOMEM;
		पूर्ण

		wq->रुको_queue_token = स्वतःfs_next_रुको_queue;
		अगर (++स्वतःfs_next_रुको_queue == 0)
			स्वतःfs_next_रुको_queue = 1;
		wq->next = sbi->queues;
		sbi->queues = wq;
		init_रुकोqueue_head(&wq->queue);
		स_नकल(&wq->name, &qstr, माप(काष्ठा qstr));
		wq->offset = offset;
		wq->dev = स्वतःfs_get_dev(sbi);
		wq->ino = स्वतःfs_get_ino(sbi);
		wq->uid = current_uid();
		wq->gid = current_gid();
		wq->pid = pid;
		wq->tgid = tgid;
		wq->status = -EINTR; /* Status वापस अगर पूर्णांकerrupted */
		wq->रुको_ctr = 2;

		अगर (sbi->version < 5) अणु
			अगर (notअगरy == NFY_MOUNT)
				type = स्वतःfs_ptype_missing;
			अन्यथा
				type = स्वतःfs_ptype_expire_multi;
		पूर्ण अन्यथा अणु
			अगर (notअगरy == NFY_MOUNT)
				type = स्वतःfs_type_trigger(sbi->type) ?
					स्वतःfs_ptype_missing_direct :
					 स्वतःfs_ptype_missing_indirect;
			अन्यथा
				type = स्वतःfs_type_trigger(sbi->type) ?
					स्वतःfs_ptype_expire_direct :
					स्वतःfs_ptype_expire_indirect;
		पूर्ण

		pr_debug("new wait id = 0x%08lx, name = %.*s, nfy=%d\n",
			 (अचिन्हित दीर्घ) wq->रुको_queue_token, wq->name.len,
			 wq->name.name, notअगरy);

		/*
		 * स्वतःfs_notअगरy_daemon() may block; it will unlock ->wq_mutex
		 */
		स्वतःfs_notअगरy_daemon(sbi, wq, type);
	पूर्ण अन्यथा अणु
		wq->रुको_ctr++;
		pr_debug("existing wait id = 0x%08lx, name = %.*s, nfy=%d\n",
			 (अचिन्हित दीर्घ) wq->रुको_queue_token, wq->name.len,
			 wq->name.name, notअगरy);
		mutex_unlock(&sbi->wq_mutex);
		kमुक्त(name);
	पूर्ण

	/*
	 * wq->name.name is शून्य अगरf the lock is alपढ़ोy released
	 * or the mount has been made catatonic.
	 */
	रुको_event_समाप्तable(wq->queue, wq->name.name == शून्य);
	status = wq->status;

	/*
	 * For direct and offset mounts we need to track the requester's
	 * uid and gid in the dentry info काष्ठा. This is so it can be
	 * supplied, on request, by the misc device ioctl पूर्णांकerface.
	 * This is needed during daemon resatart when reconnecting
	 * to existing, active, स्वतःfs mounts. The uid and gid (and
	 * related string values) may be used क्रम macro substitution
	 * in स्वतःfs mount maps.
	 */
	अगर (!status) अणु
		काष्ठा स्वतःfs_info *ino;
		काष्ठा dentry *de = शून्य;

		/* direct mount or browsable map */
		ino = स्वतःfs_dentry_ino(dentry);
		अगर (!ino) अणु
			/* If not lookup actual dentry used */
			de = d_lookup(dentry->d_parent, &dentry->d_name);
			अगर (de)
				ino = स्वतःfs_dentry_ino(de);
		पूर्ण

		/* Set mount requester */
		अगर (ino) अणु
			spin_lock(&sbi->fs_lock);
			ino->uid = wq->uid;
			ino->gid = wq->gid;
			spin_unlock(&sbi->fs_lock);
		पूर्ण

		अगर (de)
			dput(de);
	पूर्ण

	/* Are we the last process to need status? */
	mutex_lock(&sbi->wq_mutex);
	अगर (!--wq->रुको_ctr)
		kमुक्त(wq);
	mutex_unlock(&sbi->wq_mutex);

	वापस status;
पूर्ण


पूर्णांक स्वतःfs_रुको_release(काष्ठा स्वतःfs_sb_info *sbi,
			स्वतःfs_wqt_t रुको_queue_token, पूर्णांक status)
अणु
	काष्ठा स्वतःfs_रुको_queue *wq, **wql;

	mutex_lock(&sbi->wq_mutex);
	क्रम (wql = &sbi->queues; (wq = *wql) != शून्य; wql = &wq->next) अणु
		अगर (wq->रुको_queue_token == रुको_queue_token)
			अवरोध;
	पूर्ण

	अगर (!wq) अणु
		mutex_unlock(&sbi->wq_mutex);
		वापस -EINVAL;
	पूर्ण

	*wql = wq->next;	/* Unlink from chain */
	kमुक्त(wq->name.name - wq->offset);
	wq->name.name = शून्य;	/* Do not रुको on this queue */
	wq->status = status;
	wake_up(&wq->queue);
	अगर (!--wq->रुको_ctr)
		kमुक्त(wq);
	mutex_unlock(&sbi->wq_mutex);

	वापस 0;
पूर्ण
