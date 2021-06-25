<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/dcache.h>
#समावेश <linux/path.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/namei.h>
#समावेश <linux/pid.h>
#समावेश <linux/security.h>
#समावेश <linux/file.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>

#समावेश <linux/proc_fs.h>

#समावेश "../mount.h"
#समावेश "internal.h"
#समावेश "fd.h"

अटल पूर्णांक seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा files_काष्ठा *files = शून्य;
	पूर्णांक f_flags = 0, ret = -ENOENT;
	काष्ठा file *file = शून्य;
	काष्ठा task_काष्ठा *task;

	task = get_proc_task(m->निजी);
	अगर (!task)
		वापस -ENOENT;

	task_lock(task);
	files = task->files;
	अगर (files) अणु
		अचिन्हित पूर्णांक fd = proc_fd(m->निजी);

		spin_lock(&files->file_lock);
		file = files_lookup_fd_locked(files, fd);
		अगर (file) अणु
			काष्ठा fdtable *fdt = files_fdtable(files);

			f_flags = file->f_flags;
			अगर (बंद_on_exec(fd, fdt))
				f_flags |= O_CLOEXEC;

			get_file(file);
			ret = 0;
		पूर्ण
		spin_unlock(&files->file_lock);
	पूर्ण
	task_unlock(task);
	put_task_काष्ठा(task);

	अगर (ret)
		वापस ret;

	seq_म_लिखो(m, "pos:\t%lli\nflags:\t0%o\nmnt_id:\t%i\n",
		   (दीर्घ दीर्घ)file->f_pos, f_flags,
		   real_mount(file->f_path.mnt)->mnt_id);

	/* show_fd_locks() never deferences files so a stale value is safe */
	show_fd_locks(m, file, files);
	अगर (seq_has_overflowed(m))
		जाओ out;

	अगर (file->f_op->show_fdinfo)
		file->f_op->show_fdinfo(m, file);

out:
	fput(file);
	वापस 0;
पूर्ण

अटल पूर्णांक seq_fdinfo_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, seq_show, inode);
पूर्ण

अटल स्थिर काष्ठा file_operations proc_fdinfo_file_operations = अणु
	.खोलो		= seq_fdinfo_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल bool tid_fd_mode(काष्ठा task_काष्ठा *task, अचिन्हित fd, भ_शेषe_t *mode)
अणु
	काष्ठा file *file;

	rcu_पढ़ो_lock();
	file = task_lookup_fd_rcu(task, fd);
	अगर (file)
		*mode = file->f_mode;
	rcu_पढ़ो_unlock();
	वापस !!file;
पूर्ण

अटल व्योम tid_fd_update_inode(काष्ठा task_काष्ठा *task, काष्ठा inode *inode,
				भ_शेषe_t f_mode)
अणु
	task_dump_owner(task, 0, &inode->i_uid, &inode->i_gid);

	अगर (S_ISLNK(inode->i_mode)) अणु
		अचिन्हित i_mode = S_IFLNK;
		अगर (f_mode & FMODE_READ)
			i_mode |= S_IRUSR | S_IXUSR;
		अगर (f_mode & FMODE_WRITE)
			i_mode |= S_IWUSR | S_IXUSR;
		inode->i_mode = i_mode;
	पूर्ण
	security_task_to_inode(task, inode);
पूर्ण

अटल पूर्णांक tid_fd_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा inode *inode;
	अचिन्हित पूर्णांक fd;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	inode = d_inode(dentry);
	task = get_proc_task(inode);
	fd = proc_fd(inode);

	अगर (task) अणु
		भ_शेषe_t f_mode;
		अगर (tid_fd_mode(task, fd, &f_mode)) अणु
			tid_fd_update_inode(task, inode, f_mode);
			put_task_काष्ठा(task);
			वापस 1;
		पूर्ण
		put_task_काष्ठा(task);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dentry_operations tid_fd_dentry_operations = अणु
	.d_revalidate	= tid_fd_revalidate,
	.d_delete	= pid_delete_dentry,
पूर्ण;

अटल पूर्णांक proc_fd_link(काष्ठा dentry *dentry, काष्ठा path *path)
अणु
	काष्ठा task_काष्ठा *task;
	पूर्णांक ret = -ENOENT;

	task = get_proc_task(d_inode(dentry));
	अगर (task) अणु
		अचिन्हित पूर्णांक fd = proc_fd(d_inode(dentry));
		काष्ठा file *fd_file;

		fd_file = fget_task(task, fd);
		अगर (fd_file) अणु
			*path = fd_file->f_path;
			path_get(&fd_file->f_path);
			ret = 0;
			fput(fd_file);
		पूर्ण
		put_task_काष्ठा(task);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा fd_data अणु
	भ_शेषe_t mode;
	अचिन्हित fd;
पूर्ण;

अटल काष्ठा dentry *proc_fd_instantiate(काष्ठा dentry *dentry,
	काष्ठा task_काष्ठा *task, स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा fd_data *data = ptr;
	काष्ठा proc_inode *ei;
	काष्ठा inode *inode;

	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFLNK);
	अगर (!inode)
		वापस ERR_PTR(-ENOENT);

	ei = PROC_I(inode);
	ei->fd = data->fd;

	inode->i_op = &proc_pid_link_inode_operations;
	inode->i_size = 64;

	ei->op.proc_get_link = proc_fd_link;
	tid_fd_update_inode(task, inode, data->mode);

	d_set_d_op(dentry, &tid_fd_dentry_operations);
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल काष्ठा dentry *proc_lookupfd_common(काष्ठा inode *dir,
					   काष्ठा dentry *dentry,
					   instantiate_t instantiate)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(dir);
	काष्ठा fd_data data = अणु.fd = name_to_पूर्णांक(&dentry->d_name)पूर्ण;
	काष्ठा dentry *result = ERR_PTR(-ENOENT);

	अगर (!task)
		जाओ out_no_task;
	अगर (data.fd == ~0U)
		जाओ out;
	अगर (!tid_fd_mode(task, data.fd, &data.mode))
		जाओ out;

	result = instantiate(dentry, task, &data);
out:
	put_task_काष्ठा(task);
out_no_task:
	वापस result;
पूर्ण

अटल पूर्णांक proc_पढ़ोfd_common(काष्ठा file *file, काष्ठा dir_context *ctx,
			      instantiate_t instantiate)
अणु
	काष्ठा task_काष्ठा *p = get_proc_task(file_inode(file));
	अचिन्हित पूर्णांक fd;

	अगर (!p)
		वापस -ENOENT;

	अगर (!dir_emit_करोts(file, ctx))
		जाओ out;

	rcu_पढ़ो_lock();
	क्रम (fd = ctx->pos - 2;; fd++) अणु
		काष्ठा file *f;
		काष्ठा fd_data data;
		अक्षर name[10 + 1];
		अचिन्हित पूर्णांक len;

		f = task_lookup_next_fd_rcu(p, &fd);
		ctx->pos = fd + 2LL;
		अगर (!f)
			अवरोध;
		data.mode = f->f_mode;
		rcu_पढ़ो_unlock();
		data.fd = fd;

		len = snम_लिखो(name, माप(name), "%u", fd);
		अगर (!proc_fill_cache(file, ctx,
				     name, len, instantiate, p,
				     &data))
			जाओ out;
		cond_resched();
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();
out:
	put_task_काष्ठा(p);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_पढ़ोfd(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	वापस proc_पढ़ोfd_common(file, ctx, proc_fd_instantiate);
पूर्ण

स्थिर काष्ठा file_operations proc_fd_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= proc_पढ़ोfd,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल काष्ठा dentry *proc_lookupfd(काष्ठा inode *dir, काष्ठा dentry *dentry,
				    अचिन्हित पूर्णांक flags)
अणु
	वापस proc_lookupfd_common(dir, dentry, proc_fd_instantiate);
पूर्ण

/*
 * /proc/pid/fd needs a special permission handler so that a process can still
 * access /proc/self/fd after it has executed a setuid().
 */
पूर्णांक proc_fd_permission(काष्ठा user_namespace *mnt_userns,
		       काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा task_काष्ठा *p;
	पूर्णांक rv;

	rv = generic_permission(&init_user_ns, inode, mask);
	अगर (rv == 0)
		वापस rv;

	rcu_पढ़ो_lock();
	p = pid_task(proc_pid(inode), PIDTYPE_PID);
	अगर (p && same_thपढ़ो_group(p, current))
		rv = 0;
	rcu_पढ़ो_unlock();

	वापस rv;
पूर्ण

स्थिर काष्ठा inode_operations proc_fd_inode_operations = अणु
	.lookup		= proc_lookupfd,
	.permission	= proc_fd_permission,
	.setattr	= proc_setattr,
पूर्ण;

अटल काष्ठा dentry *proc_fdinfo_instantiate(काष्ठा dentry *dentry,
	काष्ठा task_काष्ठा *task, स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा fd_data *data = ptr;
	काष्ठा proc_inode *ei;
	काष्ठा inode *inode;

	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFREG | S_IRUSR);
	अगर (!inode)
		वापस ERR_PTR(-ENOENT);

	ei = PROC_I(inode);
	ei->fd = data->fd;

	inode->i_fop = &proc_fdinfo_file_operations;
	tid_fd_update_inode(task, inode, 0);

	d_set_d_op(dentry, &tid_fd_dentry_operations);
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल काष्ठा dentry *
proc_lookupfdinfo(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस proc_lookupfd_common(dir, dentry, proc_fdinfo_instantiate);
पूर्ण

अटल पूर्णांक proc_पढ़ोfdinfo(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	वापस proc_पढ़ोfd_common(file, ctx,
				  proc_fdinfo_instantiate);
पूर्ण

स्थिर काष्ठा inode_operations proc_fdinfo_inode_operations = अणु
	.lookup		= proc_lookupfdinfo,
	.setattr	= proc_setattr,
पूर्ण;

स्थिर काष्ठा file_operations proc_fdinfo_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= proc_पढ़ोfdinfo,
	.llseek		= generic_file_llseek,
पूर्ण;
