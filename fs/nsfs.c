<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/magic.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/nsfs.h>
#समावेश <linux/uaccess.h>

#समावेश "internal.h"

अटल काष्ठा vfsmount *nsfs_mnt;

अटल दीर्घ ns_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl,
			अचिन्हित दीर्घ arg);
अटल स्थिर काष्ठा file_operations ns_file_operations = अणु
	.llseek		= no_llseek,
	.unlocked_ioctl = ns_ioctl,
पूर्ण;

अटल अक्षर *ns_dname(काष्ठा dentry *dentry, अक्षर *buffer, पूर्णांक buflen)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	स्थिर काष्ठा proc_ns_operations *ns_ops = dentry->d_fsdata;

	वापस dynamic_dname(dentry, buffer, buflen, "%s:[%lu]",
		ns_ops->name, inode->i_ino);
पूर्ण

अटल व्योम ns_prune_dentry(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	अगर (inode) अणु
		काष्ठा ns_common *ns = inode->i_निजी;
		atomic_दीर्घ_set(&ns->stashed, 0);
	पूर्ण
पूर्ण

स्थिर काष्ठा dentry_operations ns_dentry_operations =
अणु
	.d_prune	= ns_prune_dentry,
	.d_delete	= always_delete_dentry,
	.d_dname	= ns_dname,
पूर्ण;

अटल व्योम nsfs_evict(काष्ठा inode *inode)
अणु
	काष्ठा ns_common *ns = inode->i_निजी;
	clear_inode(inode);
	ns->ops->put(ns);
पूर्ण

अटल पूर्णांक __ns_get_path(काष्ठा path *path, काष्ठा ns_common *ns)
अणु
	काष्ठा vfsmount *mnt = nsfs_mnt;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	अचिन्हित दीर्घ d;

	rcu_पढ़ो_lock();
	d = atomic_दीर्घ_पढ़ो(&ns->stashed);
	अगर (!d)
		जाओ slow;
	dentry = (काष्ठा dentry *)d;
	अगर (!lockref_get_not_dead(&dentry->d_lockref))
		जाओ slow;
	rcu_पढ़ो_unlock();
	ns->ops->put(ns);
got_it:
	path->mnt = mntget(mnt);
	path->dentry = dentry;
	वापस 0;
slow:
	rcu_पढ़ो_unlock();
	inode = new_inode_pseuकरो(mnt->mnt_sb);
	अगर (!inode) अणु
		ns->ops->put(ns);
		वापस -ENOMEM;
	पूर्ण
	inode->i_ino = ns->inum;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	inode->i_flags |= S_IMMUTABLE;
	inode->i_mode = S_IFREG | S_IRUGO;
	inode->i_fop = &ns_file_operations;
	inode->i_निजी = ns;

	dentry = d_alloc_anon(mnt->mnt_sb);
	अगर (!dentry) अणु
		iput(inode);
		वापस -ENOMEM;
	पूर्ण
	d_instantiate(dentry, inode);
	dentry->d_fsdata = (व्योम *)ns->ops;
	d = atomic_दीर्घ_cmpxchg(&ns->stashed, 0, (अचिन्हित दीर्घ)dentry);
	अगर (d) अणु
		d_delete(dentry);	/* make sure ->d_prune() करोes nothing */
		dput(dentry);
		cpu_relax();
		वापस -EAGAIN;
	पूर्ण
	जाओ got_it;
पूर्ण

पूर्णांक ns_get_path_cb(काष्ठा path *path, ns_get_path_helper_t *ns_get_cb,
		     व्योम *निजी_data)
अणु
	पूर्णांक ret;

	करो अणु
		काष्ठा ns_common *ns = ns_get_cb(निजी_data);
		अगर (!ns)
			वापस -ENOENT;
		ret = __ns_get_path(path, ns);
	पूर्ण जबतक (ret == -EAGAIN);

	वापस ret;
पूर्ण

काष्ठा ns_get_path_task_args अणु
	स्थिर काष्ठा proc_ns_operations *ns_ops;
	काष्ठा task_काष्ठा *task;
पूर्ण;

अटल काष्ठा ns_common *ns_get_path_task(व्योम *निजी_data)
अणु
	काष्ठा ns_get_path_task_args *args = निजी_data;

	वापस args->ns_ops->get(args->task);
पूर्ण

पूर्णांक ns_get_path(काष्ठा path *path, काष्ठा task_काष्ठा *task,
		  स्थिर काष्ठा proc_ns_operations *ns_ops)
अणु
	काष्ठा ns_get_path_task_args args = अणु
		.ns_ops	= ns_ops,
		.task	= task,
	पूर्ण;

	वापस ns_get_path_cb(path, ns_get_path_task, &args);
पूर्ण

पूर्णांक खोलो_related_ns(काष्ठा ns_common *ns,
		   काष्ठा ns_common *(*get_ns)(काष्ठा ns_common *ns))
अणु
	काष्ठा path path = अणुपूर्ण;
	काष्ठा file *f;
	पूर्णांक err;
	पूर्णांक fd;

	fd = get_unused_fd_flags(O_CLOEXEC);
	अगर (fd < 0)
		वापस fd;

	करो अणु
		काष्ठा ns_common *relative;

		relative = get_ns(ns);
		अगर (IS_ERR(relative)) अणु
			put_unused_fd(fd);
			वापस PTR_ERR(relative);
		पूर्ण

		err = __ns_get_path(&path, relative);
	पूर्ण जबतक (err == -EAGAIN);

	अगर (err) अणु
		put_unused_fd(fd);
		वापस err;
	पूर्ण

	f = dentry_खोलो(&path, O_RDONLY, current_cred());
	path_put(&path);
	अगर (IS_ERR(f)) अणु
		put_unused_fd(fd);
		fd = PTR_ERR(f);
	पूर्ण अन्यथा
		fd_install(fd, f);

	वापस fd;
पूर्ण
EXPORT_SYMBOL_GPL(खोलो_related_ns);

अटल दीर्घ ns_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा user_namespace *user_ns;
	काष्ठा ns_common *ns = get_proc_ns(file_inode(filp));
	uid_t __user *argp;
	uid_t uid;

	चयन (ioctl) अणु
	हाल NS_GET_USERNS:
		वापस खोलो_related_ns(ns, ns_get_owner);
	हाल NS_GET_PARENT:
		अगर (!ns->ops->get_parent)
			वापस -EINVAL;
		वापस खोलो_related_ns(ns, ns->ops->get_parent);
	हाल NS_GET_NSTYPE:
		वापस ns->ops->type;
	हाल NS_GET_OWNER_UID:
		अगर (ns->ops->type != CLONE_NEWUSER)
			वापस -EINVAL;
		user_ns = container_of(ns, काष्ठा user_namespace, ns);
		argp = (uid_t __user *) arg;
		uid = from_kuid_munged(current_user_ns(), user_ns->owner);
		वापस put_user(uid, argp);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

पूर्णांक ns_get_name(अक्षर *buf, माप_प्रकार size, काष्ठा task_काष्ठा *task,
			स्थिर काष्ठा proc_ns_operations *ns_ops)
अणु
	काष्ठा ns_common *ns;
	पूर्णांक res = -ENOENT;
	स्थिर अक्षर *name;
	ns = ns_ops->get(task);
	अगर (ns) अणु
		name = ns_ops->real_ns_name ? : ns_ops->name;
		res = snम_लिखो(buf, size, "%s:[%u]", name, ns->inum);
		ns_ops->put(ns);
	पूर्ण
	वापस res;
पूर्ण

bool proc_ns_file(स्थिर काष्ठा file *file)
अणु
	वापस file->f_op == &ns_file_operations;
पूर्ण

काष्ठा file *proc_ns_fget(पूर्णांक fd)
अणु
	काष्ठा file *file;

	file = fget(fd);
	अगर (!file)
		वापस ERR_PTR(-EBADF);

	अगर (file->f_op != &ns_file_operations)
		जाओ out_invalid;

	वापस file;

out_invalid:
	fput(file);
	वापस ERR_PTR(-EINVAL);
पूर्ण

/**
 * ns_match() - Returns true अगर current namespace matches dev/ino provided.
 * @ns_common: current ns
 * @dev: dev_t from nsfs that will be matched against current nsfs
 * @ino: ino_t from nsfs that will be matched against current nsfs
 *
 * Return: true अगर dev and ino matches the current nsfs.
 */
bool ns_match(स्थिर काष्ठा ns_common *ns, dev_t dev, ino_t ino)
अणु
	वापस (ns->inum == ino) && (nsfs_mnt->mnt_sb->s_dev == dev);
पूर्ण


अटल पूर्णांक nsfs_show_path(काष्ठा seq_file *seq, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	स्थिर काष्ठा proc_ns_operations *ns_ops = dentry->d_fsdata;

	seq_म_लिखो(seq, "%s:[%lu]", ns_ops->name, inode->i_ino);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations nsfs_ops = अणु
	.statfs = simple_statfs,
	.evict_inode = nsfs_evict,
	.show_path = nsfs_show_path,
पूर्ण;

अटल पूर्णांक nsfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा pseuकरो_fs_context *ctx = init_pseuकरो(fc, NSFS_MAGIC);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->ops = &nsfs_ops;
	ctx->करोps = &ns_dentry_operations;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type nsfs = अणु
	.name = "nsfs",
	.init_fs_context = nsfs_init_fs_context,
	.समाप्त_sb = समाप्त_anon_super,
पूर्ण;

व्योम __init nsfs_init(व्योम)
अणु
	nsfs_mnt = kern_mount(&nsfs);
	अगर (IS_ERR(nsfs_mnt))
		panic("can't set nsfs up\n");
	nsfs_mnt->mnt_sb->s_flags &= ~SB_NOUSER;
पूर्ण
