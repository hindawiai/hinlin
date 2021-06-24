<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/proc_namespace.c - handling of /proc/<pid>/अणुmounts,mountinfo,mountstatsपूर्ण
 *
 * In fact, that's a piece of procfs; it's *almost* isolated from
 * the rest of fs/proc, but has rather बंद relationships with
 * fs/namespace.c, thus here instead of fs/proc
 *
 */
#समावेश <linux/mnt_namespace.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/security.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/sched/task.h>

#समावेश "proc/internal.h" /* only क्रम get_proc_task() in ->खोलो() */

#समावेश "pnode.h"
#समावेश "internal.h"

अटल __poll_t mounts_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा proc_mounts *p = m->निजी;
	काष्ठा mnt_namespace *ns = p->ns;
	__poll_t res = EPOLLIN | EPOLLRDNORM;
	पूर्णांक event;

	poll_रुको(file, &p->ns->poll, रुको);

	event = READ_ONCE(ns->event);
	अगर (m->poll_event != event) अणु
		m->poll_event = event;
		res |= EPOLLERR | EPOLLPRI;
	पूर्ण

	वापस res;
पूर्ण

काष्ठा proc_fs_opts अणु
	पूर्णांक flag;
	स्थिर अक्षर *str;
पूर्ण;

अटल पूर्णांक show_sb_opts(काष्ठा seq_file *m, काष्ठा super_block *sb)
अणु
	अटल स्थिर काष्ठा proc_fs_opts fs_opts[] = अणु
		अणु SB_SYNCHRONOUS, ",sync" पूर्ण,
		अणु SB_सूचीSYNC, ",dirsync" पूर्ण,
		अणु SB_MANDLOCK, ",mand" पूर्ण,
		अणु SB_LAZYTIME, ",lazytime" पूर्ण,
		अणु 0, शून्य पूर्ण
	पूर्ण;
	स्थिर काष्ठा proc_fs_opts *fs_infop;

	क्रम (fs_infop = fs_opts; fs_infop->flag; fs_infop++) अणु
		अगर (sb->s_flags & fs_infop->flag)
			seq_माला_दो(m, fs_infop->str);
	पूर्ण

	वापस security_sb_show_options(m, sb);
पूर्ण

अटल व्योम show_mnt_opts(काष्ठा seq_file *m, काष्ठा vfsmount *mnt)
अणु
	अटल स्थिर काष्ठा proc_fs_opts mnt_opts[] = अणु
		अणु MNT_NOSUID, ",nosuid" पूर्ण,
		अणु MNT_NODEV, ",nodev" पूर्ण,
		अणु MNT_NOEXEC, ",noexec" पूर्ण,
		अणु MNT_NOATIME, ",noatime" पूर्ण,
		अणु MNT_NOसूचीATIME, ",nodiratime" पूर्ण,
		अणु MNT_RELATIME, ",relatime" पूर्ण,
		अणु MNT_NOSYMFOLLOW, ",nosymfollow" पूर्ण,
		अणु 0, शून्य पूर्ण
	पूर्ण;
	स्थिर काष्ठा proc_fs_opts *fs_infop;

	क्रम (fs_infop = mnt_opts; fs_infop->flag; fs_infop++) अणु
		अगर (mnt->mnt_flags & fs_infop->flag)
			seq_माला_दो(m, fs_infop->str);
	पूर्ण

	अगर (mnt_user_ns(mnt) != &init_user_ns)
		seq_माला_दो(m, ",idmapped");
पूर्ण

अटल अंतरभूत व्योम mangle(काष्ठा seq_file *m, स्थिर अक्षर *s)
अणु
	seq_escape(m, s, " \t\n\\");
पूर्ण

अटल व्योम show_type(काष्ठा seq_file *m, काष्ठा super_block *sb)
अणु
	mangle(m, sb->s_type->name);
	अगर (sb->s_subtype) अणु
		seq_अ_दो(m, '.');
		mangle(m, sb->s_subtype);
	पूर्ण
पूर्ण

अटल पूर्णांक show_vfsmnt(काष्ठा seq_file *m, काष्ठा vfsmount *mnt)
अणु
	काष्ठा proc_mounts *p = m->निजी;
	काष्ठा mount *r = real_mount(mnt);
	काष्ठा path mnt_path = अणु .dentry = mnt->mnt_root, .mnt = mnt पूर्ण;
	काष्ठा super_block *sb = mnt_path.dentry->d_sb;
	पूर्णांक err;

	अगर (sb->s_op->show_devname) अणु
		err = sb->s_op->show_devname(m, mnt_path.dentry);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		mangle(m, r->mnt_devname ? r->mnt_devname : "none");
	पूर्ण
	seq_अ_दो(m, ' ');
	/* mountpoपूर्णांकs outside of chroot jail will give SEQ_SKIP on this */
	err = seq_path_root(m, &mnt_path, &p->root, " \t\n\\");
	अगर (err)
		जाओ out;
	seq_अ_दो(m, ' ');
	show_type(m, sb);
	seq_माला_दो(m, __mnt_is_पढ़ोonly(mnt) ? " ro" : " rw");
	err = show_sb_opts(m, sb);
	अगर (err)
		जाओ out;
	show_mnt_opts(m, mnt);
	अगर (sb->s_op->show_options)
		err = sb->s_op->show_options(m, mnt_path.dentry);
	seq_माला_दो(m, " 0 0\n");
out:
	वापस err;
पूर्ण

अटल पूर्णांक show_mountinfo(काष्ठा seq_file *m, काष्ठा vfsmount *mnt)
अणु
	काष्ठा proc_mounts *p = m->निजी;
	काष्ठा mount *r = real_mount(mnt);
	काष्ठा super_block *sb = mnt->mnt_sb;
	काष्ठा path mnt_path = अणु .dentry = mnt->mnt_root, .mnt = mnt पूर्ण;
	पूर्णांक err;

	seq_म_लिखो(m, "%i %i %u:%u ", r->mnt_id, r->mnt_parent->mnt_id,
		   MAJOR(sb->s_dev), MINOR(sb->s_dev));
	अगर (sb->s_op->show_path) अणु
		err = sb->s_op->show_path(m, mnt->mnt_root);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		seq_dentry(m, mnt->mnt_root, " \t\n\\");
	पूर्ण
	seq_अ_दो(m, ' ');

	/* mountpoपूर्णांकs outside of chroot jail will give SEQ_SKIP on this */
	err = seq_path_root(m, &mnt_path, &p->root, " \t\n\\");
	अगर (err)
		जाओ out;

	seq_माला_दो(m, mnt->mnt_flags & MNT_READONLY ? " ro" : " rw");
	show_mnt_opts(m, mnt);

	/* Tagged fields ("foo:X" or "bar") */
	अगर (IS_MNT_SHARED(r))
		seq_म_लिखो(m, " shared:%i", r->mnt_group_id);
	अगर (IS_MNT_SLAVE(r)) अणु
		पूर्णांक master = r->mnt_master->mnt_group_id;
		पूर्णांक करोm = get_करोminating_id(r, &p->root);
		seq_म_लिखो(m, " master:%i", master);
		अगर (करोm && करोm != master)
			seq_म_लिखो(m, " propagate_from:%i", करोm);
	पूर्ण
	अगर (IS_MNT_UNBINDABLE(r))
		seq_माला_दो(m, " unbindable");

	/* Fileप्रणाली specअगरic data */
	seq_माला_दो(m, " - ");
	show_type(m, sb);
	seq_अ_दो(m, ' ');
	अगर (sb->s_op->show_devname) अणु
		err = sb->s_op->show_devname(m, mnt->mnt_root);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		mangle(m, r->mnt_devname ? r->mnt_devname : "none");
	पूर्ण
	seq_माला_दो(m, sb_rकरोnly(sb) ? " ro" : " rw");
	err = show_sb_opts(m, sb);
	अगर (err)
		जाओ out;
	अगर (sb->s_op->show_options)
		err = sb->s_op->show_options(m, mnt->mnt_root);
	seq_अ_दो(m, '\n');
out:
	वापस err;
पूर्ण

अटल पूर्णांक show_vfsstat(काष्ठा seq_file *m, काष्ठा vfsmount *mnt)
अणु
	काष्ठा proc_mounts *p = m->निजी;
	काष्ठा mount *r = real_mount(mnt);
	काष्ठा path mnt_path = अणु .dentry = mnt->mnt_root, .mnt = mnt पूर्ण;
	काष्ठा super_block *sb = mnt_path.dentry->d_sb;
	पूर्णांक err;

	/* device */
	अगर (sb->s_op->show_devname) अणु
		seq_माला_दो(m, "device ");
		err = sb->s_op->show_devname(m, mnt_path.dentry);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (r->mnt_devname) अणु
			seq_माला_दो(m, "device ");
			mangle(m, r->mnt_devname);
		पूर्ण अन्यथा
			seq_माला_दो(m, "no device");
	पूर्ण

	/* mount poपूर्णांक */
	seq_माला_दो(m, " mounted on ");
	/* mountpoपूर्णांकs outside of chroot jail will give SEQ_SKIP on this */
	err = seq_path_root(m, &mnt_path, &p->root, " \t\n\\");
	अगर (err)
		जाओ out;
	seq_अ_दो(m, ' ');

	/* file प्रणाली type */
	seq_माला_दो(m, "with fstype ");
	show_type(m, sb);

	/* optional statistics */
	अगर (sb->s_op->show_stats) अणु
		seq_अ_दो(m, ' ');
		err = sb->s_op->show_stats(m, mnt_path.dentry);
	पूर्ण

	seq_अ_दो(m, '\n');
out:
	वापस err;
पूर्ण

अटल पूर्णांक mounts_खोलो_common(काष्ठा inode *inode, काष्ठा file *file,
			      पूर्णांक (*show)(काष्ठा seq_file *, काष्ठा vfsmount *))
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(inode);
	काष्ठा nsproxy *nsp;
	काष्ठा mnt_namespace *ns = शून्य;
	काष्ठा path root;
	काष्ठा proc_mounts *p;
	काष्ठा seq_file *m;
	पूर्णांक ret = -EINVAL;

	अगर (!task)
		जाओ err;

	task_lock(task);
	nsp = task->nsproxy;
	अगर (!nsp || !nsp->mnt_ns) अणु
		task_unlock(task);
		put_task_काष्ठा(task);
		जाओ err;
	पूर्ण
	ns = nsp->mnt_ns;
	get_mnt_ns(ns);
	अगर (!task->fs) अणु
		task_unlock(task);
		put_task_काष्ठा(task);
		ret = -ENOENT;
		जाओ err_put_ns;
	पूर्ण
	get_fs_root(task->fs, &root);
	task_unlock(task);
	put_task_काष्ठा(task);

	ret = seq_खोलो_निजी(file, &mounts_op, माप(काष्ठा proc_mounts));
	अगर (ret)
		जाओ err_put_path;

	m = file->निजी_data;
	m->poll_event = ns->event;

	p = m->निजी;
	p->ns = ns;
	p->root = root;
	p->show = show;
	INIT_LIST_HEAD(&p->cursor.mnt_list);
	p->cursor.mnt.mnt_flags = MNT_CURSOR;

	वापस 0;

 err_put_path:
	path_put(&root);
 err_put_ns:
	put_mnt_ns(ns);
 err:
	वापस ret;
पूर्ण

अटल पूर्णांक mounts_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा proc_mounts *p = m->निजी;
	path_put(&p->root);
	mnt_cursor_del(p->ns, &p->cursor);
	put_mnt_ns(p->ns);
	वापस seq_release_निजी(inode, file);
पूर्ण

अटल पूर्णांक mounts_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस mounts_खोलो_common(inode, file, show_vfsmnt);
पूर्ण

अटल पूर्णांक mountinfo_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस mounts_खोलो_common(inode, file, show_mountinfo);
पूर्ण

अटल पूर्णांक mountstats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस mounts_खोलो_common(inode, file, show_vfsstat);
पूर्ण

स्थिर काष्ठा file_operations proc_mounts_operations = अणु
	.खोलो		= mounts_खोलो,
	.पढ़ो_iter	= seq_पढ़ो_iter,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.llseek		= seq_lseek,
	.release	= mounts_release,
	.poll		= mounts_poll,
पूर्ण;

स्थिर काष्ठा file_operations proc_mountinfo_operations = अणु
	.खोलो		= mountinfo_खोलो,
	.पढ़ो_iter	= seq_पढ़ो_iter,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.llseek		= seq_lseek,
	.release	= mounts_release,
	.poll		= mounts_poll,
पूर्ण;

स्थिर काष्ठा file_operations proc_mountstats_operations = अणु
	.खोलो		= mountstats_खोलो,
	.पढ़ो_iter	= seq_पढ़ो_iter,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.llseek		= seq_lseek,
	.release	= mounts_release,
पूर्ण;
