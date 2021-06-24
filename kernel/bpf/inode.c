<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Minimal file प्रणाली backend क्रम holding eBPF maps and programs,
 * used by bpf(2) object pinning.
 *
 * Authors:
 *
 *	Daniel Borkmann <daniel@iogearbox.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/magic.h>
#समावेश <linux/major.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश "preload/bpf_preload.h"

क्रमागत bpf_type अणु
	BPF_TYPE_UNSPEC	= 0,
	BPF_TYPE_PROG,
	BPF_TYPE_MAP,
	BPF_TYPE_LINK,
पूर्ण;

अटल व्योम *bpf_any_get(व्योम *raw, क्रमागत bpf_type type)
अणु
	चयन (type) अणु
	हाल BPF_TYPE_PROG:
		bpf_prog_inc(raw);
		अवरोध;
	हाल BPF_TYPE_MAP:
		bpf_map_inc_with_uref(raw);
		अवरोध;
	हाल BPF_TYPE_LINK:
		bpf_link_inc(raw);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस raw;
पूर्ण

अटल व्योम bpf_any_put(व्योम *raw, क्रमागत bpf_type type)
अणु
	चयन (type) अणु
	हाल BPF_TYPE_PROG:
		bpf_prog_put(raw);
		अवरोध;
	हाल BPF_TYPE_MAP:
		bpf_map_put_with_uref(raw);
		अवरोध;
	हाल BPF_TYPE_LINK:
		bpf_link_put(raw);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम *bpf_fd_probe_obj(u32 ufd, क्रमागत bpf_type *type)
अणु
	व्योम *raw;

	raw = bpf_map_get_with_uref(ufd);
	अगर (!IS_ERR(raw)) अणु
		*type = BPF_TYPE_MAP;
		वापस raw;
	पूर्ण

	raw = bpf_prog_get(ufd);
	अगर (!IS_ERR(raw)) अणु
		*type = BPF_TYPE_PROG;
		वापस raw;
	पूर्ण

	raw = bpf_link_get_from_fd(ufd);
	अगर (!IS_ERR(raw)) अणु
		*type = BPF_TYPE_LINK;
		वापस raw;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल स्थिर काष्ठा inode_operations bpf_dir_iops;

अटल स्थिर काष्ठा inode_operations bpf_prog_iops = अणु पूर्ण;
अटल स्थिर काष्ठा inode_operations bpf_map_iops  = अणु पूर्ण;
अटल स्थिर काष्ठा inode_operations bpf_link_iops  = अणु पूर्ण;

अटल काष्ठा inode *bpf_get_inode(काष्ठा super_block *sb,
				   स्थिर काष्ठा inode *dir,
				   umode_t mode)
अणु
	काष्ठा inode *inode;

	चयन (mode & S_IFMT) अणु
	हाल S_IFसूची:
	हाल S_IFREG:
	हाल S_IFLNK:
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	inode = new_inode(sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOSPC);

	inode->i_ino = get_next_ino();
	inode->i_aसमय = current_समय(inode);
	inode->i_mसमय = inode->i_aसमय;
	inode->i_स_समय = inode->i_aसमय;

	inode_init_owner(&init_user_ns, inode, dir, mode);

	वापस inode;
पूर्ण

अटल पूर्णांक bpf_inode_type(स्थिर काष्ठा inode *inode, क्रमागत bpf_type *type)
अणु
	*type = BPF_TYPE_UNSPEC;
	अगर (inode->i_op == &bpf_prog_iops)
		*type = BPF_TYPE_PROG;
	अन्यथा अगर (inode->i_op == &bpf_map_iops)
		*type = BPF_TYPE_MAP;
	अन्यथा अगर (inode->i_op == &bpf_link_iops)
		*type = BPF_TYPE_LINK;
	अन्यथा
		वापस -EACCES;

	वापस 0;
पूर्ण

अटल व्योम bpf_dentry_finalize(काष्ठा dentry *dentry, काष्ठा inode *inode,
				काष्ठा inode *dir)
अणु
	d_instantiate(dentry, inode);
	dget(dentry);

	dir->i_mसमय = current_समय(dir);
	dir->i_स_समय = dir->i_mसमय;
पूर्ण

अटल पूर्णांक bpf_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode *inode;

	inode = bpf_get_inode(dir->i_sb, dir, mode | S_IFसूची);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	inode->i_op = &bpf_dir_iops;
	inode->i_fop = &simple_dir_operations;

	inc_nlink(inode);
	inc_nlink(dir);

	bpf_dentry_finalize(dentry, inode, dir);
	वापस 0;
पूर्ण

काष्ठा map_iter अणु
	व्योम *key;
	bool करोne;
पूर्ण;

अटल काष्ठा map_iter *map_iter(काष्ठा seq_file *m)
अणु
	वापस m->निजी;
पूर्ण

अटल काष्ठा bpf_map *seq_file_to_map(काष्ठा seq_file *m)
अणु
	वापस file_inode(m->file)->i_निजी;
पूर्ण

अटल व्योम map_iter_मुक्त(काष्ठा map_iter *iter)
अणु
	अगर (iter) अणु
		kमुक्त(iter->key);
		kमुक्त(iter);
	पूर्ण
पूर्ण

अटल काष्ठा map_iter *map_iter_alloc(काष्ठा bpf_map *map)
अणु
	काष्ठा map_iter *iter;

	iter = kzalloc(माप(*iter), GFP_KERNEL | __GFP_NOWARN);
	अगर (!iter)
		जाओ error;

	iter->key = kzalloc(map->key_size, GFP_KERNEL | __GFP_NOWARN);
	अगर (!iter->key)
		जाओ error;

	वापस iter;

error:
	map_iter_मुक्त(iter);
	वापस शून्य;
पूर्ण

अटल व्योम *map_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा bpf_map *map = seq_file_to_map(m);
	व्योम *key = map_iter(m)->key;
	व्योम *prev_key;

	(*pos)++;
	अगर (map_iter(m)->करोne)
		वापस शून्य;

	अगर (unlikely(v == SEQ_START_TOKEN))
		prev_key = शून्य;
	अन्यथा
		prev_key = key;

	rcu_पढ़ो_lock();
	अगर (map->ops->map_get_next_key(map, prev_key, key)) अणु
		map_iter(m)->करोne = true;
		key = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस key;
पूर्ण

अटल व्योम *map_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अगर (map_iter(m)->करोne)
		वापस शून्य;

	वापस *pos ? map_iter(m)->key : SEQ_START_TOKEN;
पूर्ण

अटल व्योम map_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक map_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा bpf_map *map = seq_file_to_map(m);
	व्योम *key = map_iter(m)->key;

	अगर (unlikely(v == SEQ_START_TOKEN)) अणु
		seq_माला_दो(m, "# WARNING!! The output is for debug purpose only\n");
		seq_माला_दो(m, "# WARNING!! The output format will change\n");
	पूर्ण अन्यथा अणु
		map->ops->map_seq_show_elem(map, key, m);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations bpffs_map_seq_ops = अणु
	.start	= map_seq_start,
	.next	= map_seq_next,
	.show	= map_seq_show,
	.stop	= map_seq_stop,
पूर्ण;

अटल पूर्णांक bpffs_map_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bpf_map *map = inode->i_निजी;
	काष्ठा map_iter *iter;
	काष्ठा seq_file *m;
	पूर्णांक err;

	iter = map_iter_alloc(map);
	अगर (!iter)
		वापस -ENOMEM;

	err = seq_खोलो(file, &bpffs_map_seq_ops);
	अगर (err) अणु
		map_iter_मुक्त(iter);
		वापस err;
	पूर्ण

	m = file->निजी_data;
	m->निजी = iter;

	वापस 0;
पूर्ण

अटल पूर्णांक bpffs_map_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = file->निजी_data;

	map_iter_मुक्त(map_iter(m));

	वापस seq_release(inode, file);
पूर्ण

/* bpffs_map_fops should only implement the basic
 * पढ़ो operation क्रम a BPF map.  The purpose is to
 * provide a simple user पूर्णांकuitive way to करो
 * "cat bpffs/pathto/a-pinned-map".
 *
 * Other operations (e.g. ग_लिखो, lookup...) should be realized by
 * the userspace tools (e.g. bpftool) through the
 * BPF_OBJ_GET_INFO_BY_FD and the map's lookup/update
 * पूर्णांकerface.
 */
अटल स्थिर काष्ठा file_operations bpffs_map_fops = अणु
	.खोलो		= bpffs_map_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.release	= bpffs_map_release,
पूर्ण;

अटल पूर्णांक bpffs_obj_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस -EIO;
पूर्ण

अटल स्थिर काष्ठा file_operations bpffs_obj_fops = अणु
	.खोलो		= bpffs_obj_खोलो,
पूर्ण;

अटल पूर्णांक bpf_mkobj_ops(काष्ठा dentry *dentry, umode_t mode, व्योम *raw,
			 स्थिर काष्ठा inode_operations *iops,
			 स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा inode *dir = dentry->d_parent->d_inode;
	काष्ठा inode *inode = bpf_get_inode(dir->i_sb, dir, mode);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	inode->i_op = iops;
	inode->i_fop = fops;
	inode->i_निजी = raw;

	bpf_dentry_finalize(dentry, inode, dir);
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_mkprog(काष्ठा dentry *dentry, umode_t mode, व्योम *arg)
अणु
	वापस bpf_mkobj_ops(dentry, mode, arg, &bpf_prog_iops,
			     &bpffs_obj_fops);
पूर्ण

अटल पूर्णांक bpf_mkmap(काष्ठा dentry *dentry, umode_t mode, व्योम *arg)
अणु
	काष्ठा bpf_map *map = arg;

	वापस bpf_mkobj_ops(dentry, mode, arg, &bpf_map_iops,
			     bpf_map_support_seq_show(map) ?
			     &bpffs_map_fops : &bpffs_obj_fops);
पूर्ण

अटल पूर्णांक bpf_mklink(काष्ठा dentry *dentry, umode_t mode, व्योम *arg)
अणु
	काष्ठा bpf_link *link = arg;

	वापस bpf_mkobj_ops(dentry, mode, arg, &bpf_link_iops,
			     bpf_link_is_iter(link) ?
			     &bpf_iter_fops : &bpffs_obj_fops);
पूर्ण

अटल काष्ठा dentry *
bpf_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित flags)
अणु
	/* Dots in names (e.g. "/sys/fs/bpf/foo.bar") are reserved क्रम future
	 * extensions. That allows popoulate_bpffs() create special files.
	 */
	अगर ((dir->i_mode & S_IALLUGO) &&
	    म_अक्षर(dentry->d_name.name, '.'))
		वापस ERR_PTR(-EPERM);

	वापस simple_lookup(dir, dentry, flags);
पूर्ण

अटल पूर्णांक bpf_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, स्थिर अक्षर *target)
अणु
	अक्षर *link = kstrdup(target, GFP_USER | __GFP_NOWARN);
	काष्ठा inode *inode;

	अगर (!link)
		वापस -ENOMEM;

	inode = bpf_get_inode(dir->i_sb, dir, S_IRWXUGO | S_IFLNK);
	अगर (IS_ERR(inode)) अणु
		kमुक्त(link);
		वापस PTR_ERR(inode);
	पूर्ण

	inode->i_op = &simple_symlink_inode_operations;
	inode->i_link = link;

	bpf_dentry_finalize(dentry, inode, dir);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations bpf_dir_iops = अणु
	.lookup		= bpf_lookup,
	.सूची_गढ़ो		= bpf_सूची_गढ़ो,
	.symlink	= bpf_symlink,
	.सूची_हटाओ		= simple_सूची_हटाओ,
	.नाम		= simple_नाम,
	.link		= simple_link,
	.unlink		= simple_unlink,
पूर्ण;

/* pin iterator link पूर्णांकo bpffs */
अटल पूर्णांक bpf_iter_link_pin_kernel(काष्ठा dentry *parent,
				    स्थिर अक्षर *name, काष्ठा bpf_link *link)
अणु
	umode_t mode = S_IFREG | S_IRUSR;
	काष्ठा dentry *dentry;
	पूर्णांक ret;

	inode_lock(parent->d_inode);
	dentry = lookup_one_len(name, parent, म_माप(name));
	अगर (IS_ERR(dentry)) अणु
		inode_unlock(parent->d_inode);
		वापस PTR_ERR(dentry);
	पूर्ण
	ret = bpf_mkobj_ops(dentry, mode, link, &bpf_link_iops,
			    &bpf_iter_fops);
	dput(dentry);
	inode_unlock(parent->d_inode);
	वापस ret;
पूर्ण

अटल पूर्णांक bpf_obj_करो_pin(स्थिर अक्षर __user *pathname, व्योम *raw,
			  क्रमागत bpf_type type)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *dir;
	काष्ठा path path;
	umode_t mode;
	पूर्णांक ret;

	dentry = user_path_create(AT_FDCWD, pathname, &path, 0);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	mode = S_IFREG | ((S_IRUSR | S_IWUSR) & ~current_umask());

	ret = security_path_mknod(&path, dentry, mode, 0);
	अगर (ret)
		जाओ out;

	dir = d_inode(path.dentry);
	अगर (dir->i_op != &bpf_dir_iops) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	चयन (type) अणु
	हाल BPF_TYPE_PROG:
		ret = vfs_mkobj(dentry, mode, bpf_mkprog, raw);
		अवरोध;
	हाल BPF_TYPE_MAP:
		ret = vfs_mkobj(dentry, mode, bpf_mkmap, raw);
		अवरोध;
	हाल BPF_TYPE_LINK:
		ret = vfs_mkobj(dentry, mode, bpf_mklink, raw);
		अवरोध;
	शेष:
		ret = -EPERM;
	पूर्ण
out:
	करोne_path_create(&path, dentry);
	वापस ret;
पूर्ण

पूर्णांक bpf_obj_pin_user(u32 ufd, स्थिर अक्षर __user *pathname)
अणु
	क्रमागत bpf_type type;
	व्योम *raw;
	पूर्णांक ret;

	raw = bpf_fd_probe_obj(ufd, &type);
	अगर (IS_ERR(raw))
		वापस PTR_ERR(raw);

	ret = bpf_obj_करो_pin(pathname, raw, type);
	अगर (ret != 0)
		bpf_any_put(raw, type);

	वापस ret;
पूर्ण

अटल व्योम *bpf_obj_करो_get(स्थिर अक्षर __user *pathname,
			    क्रमागत bpf_type *type, पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	काष्ठा path path;
	व्योम *raw;
	पूर्णांक ret;

	ret = user_path_at(AT_FDCWD, pathname, LOOKUP_FOLLOW, &path);
	अगर (ret)
		वापस ERR_PTR(ret);

	inode = d_backing_inode(path.dentry);
	ret = path_permission(&path, ACC_MODE(flags));
	अगर (ret)
		जाओ out;

	ret = bpf_inode_type(inode, type);
	अगर (ret)
		जाओ out;

	raw = bpf_any_get(inode->i_निजी, *type);
	अगर (!IS_ERR(raw))
		touch_aसमय(&path);

	path_put(&path);
	वापस raw;
out:
	path_put(&path);
	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक bpf_obj_get_user(स्थिर अक्षर __user *pathname, पूर्णांक flags)
अणु
	क्रमागत bpf_type type = BPF_TYPE_UNSPEC;
	पूर्णांक f_flags;
	व्योम *raw;
	पूर्णांक ret;

	f_flags = bpf_get_file_flag(flags);
	अगर (f_flags < 0)
		वापस f_flags;

	raw = bpf_obj_करो_get(pathname, &type, f_flags);
	अगर (IS_ERR(raw))
		वापस PTR_ERR(raw);

	अगर (type == BPF_TYPE_PROG)
		ret = (f_flags != O_RDWR) ? -EINVAL : bpf_prog_new_fd(raw);
	अन्यथा अगर (type == BPF_TYPE_MAP)
		ret = bpf_map_new_fd(raw, f_flags);
	अन्यथा अगर (type == BPF_TYPE_LINK)
		ret = (f_flags != O_RDWR) ? -EINVAL : bpf_link_new_fd(raw);
	अन्यथा
		वापस -ENOENT;

	अगर (ret < 0)
		bpf_any_put(raw, type);
	वापस ret;
पूर्ण

अटल काष्ठा bpf_prog *__get_prog_inode(काष्ठा inode *inode, क्रमागत bpf_prog_type type)
अणु
	काष्ठा bpf_prog *prog;
	पूर्णांक ret = inode_permission(&init_user_ns, inode, MAY_READ);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (inode->i_op == &bpf_map_iops)
		वापस ERR_PTR(-EINVAL);
	अगर (inode->i_op == &bpf_link_iops)
		वापस ERR_PTR(-EINVAL);
	अगर (inode->i_op != &bpf_prog_iops)
		वापस ERR_PTR(-EACCES);

	prog = inode->i_निजी;

	ret = security_bpf_prog(prog);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	अगर (!bpf_prog_get_ok(prog, &type, false))
		वापस ERR_PTR(-EINVAL);

	bpf_prog_inc(prog);
	वापस prog;
पूर्ण

काष्ठा bpf_prog *bpf_prog_get_type_path(स्थिर अक्षर *name, क्रमागत bpf_prog_type type)
अणु
	काष्ठा bpf_prog *prog;
	काष्ठा path path;
	पूर्णांक ret = kern_path(name, LOOKUP_FOLLOW, &path);
	अगर (ret)
		वापस ERR_PTR(ret);
	prog = __get_prog_inode(d_backing_inode(path.dentry), type);
	अगर (!IS_ERR(prog))
		touch_aसमय(&path);
	path_put(&path);
	वापस prog;
पूर्ण
EXPORT_SYMBOL(bpf_prog_get_type_path);

/*
 * Display the mount options in /proc/mounts.
 */
अटल पूर्णांक bpf_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	umode_t mode = d_inode(root)->i_mode & S_IALLUGO & ~S_ISVTX;

	अगर (mode != S_IRWXUGO)
		seq_म_लिखो(m, ",mode=%o", mode);
	वापस 0;
पूर्ण

अटल व्योम bpf_मुक्त_inode(काष्ठा inode *inode)
अणु
	क्रमागत bpf_type type;

	अगर (S_ISLNK(inode->i_mode))
		kमुक्त(inode->i_link);
	अगर (!bpf_inode_type(inode, &type))
		bpf_any_put(inode->i_निजी, type);
	मुक्त_inode_nonrcu(inode);
पूर्ण

अटल स्थिर काष्ठा super_operations bpf_super_ops = अणु
	.statfs		= simple_statfs,
	.drop_inode	= generic_delete_inode,
	.show_options	= bpf_show_options,
	.मुक्त_inode	= bpf_मुक्त_inode,
पूर्ण;

क्रमागत अणु
	OPT_MODE,
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec bpf_fs_parameters[] = अणु
	fsparam_u32oct	("mode",			OPT_MODE),
	अणुपूर्ण
पूर्ण;

काष्ठा bpf_mount_opts अणु
	umode_t mode;
पूर्ण;

अटल पूर्णांक bpf_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा bpf_mount_opts *opts = fc->fs_निजी;
	काष्ठा fs_parse_result result;
	पूर्णांक opt;

	opt = fs_parse(fc, bpf_fs_parameters, param, &result);
	अगर (opt < 0)
		/* We might like to report bad mount options here, but
		 * traditionally we've ignored all mount options, so we'd
		 * better जारी to ignore non-existing options क्रम bpf.
		 */
		वापस opt == -ENOPARAM ? 0 : opt;

	चयन (opt) अणु
	हाल OPT_MODE:
		opts->mode = result.uपूर्णांक_32 & S_IALLUGO;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा bpf_preload_ops *bpf_preload_ops;
EXPORT_SYMBOL_GPL(bpf_preload_ops);

अटल bool bpf_preload_mod_get(व्योम)
अणु
	/* If bpf_preload.ko wasn't loaded earlier then load it now.
	 * When bpf_preload is built पूर्णांकo vmlinux the module's __init
	 * function will populate it.
	 */
	अगर (!bpf_preload_ops) अणु
		request_module("bpf_preload");
		अगर (!bpf_preload_ops)
			वापस false;
	पूर्ण
	/* And grab the reference, so the module करोesn't disappear जबतक the
	 * kernel is पूर्णांकeracting with the kernel module and its UMD.
	 */
	अगर (!try_module_get(bpf_preload_ops->owner)) अणु
		pr_err("bpf_preload module get failed.\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम bpf_preload_mod_put(व्योम)
अणु
	अगर (bpf_preload_ops)
		/* now user can "rmmod bpf_preload" अगर necessary */
		module_put(bpf_preload_ops->owner);
पूर्ण

अटल DEFINE_MUTEX(bpf_preload_lock);

अटल पूर्णांक populate_bpffs(काष्ठा dentry *parent)
अणु
	काष्ठा bpf_preload_info objs[BPF_PRELOAD_LINKS] = अणुपूर्ण;
	काष्ठा bpf_link *links[BPF_PRELOAD_LINKS] = अणुपूर्ण;
	पूर्णांक err = 0, i;

	/* grab the mutex to make sure the kernel पूर्णांकeractions with bpf_preload
	 * UMD are serialized
	 */
	mutex_lock(&bpf_preload_lock);

	/* अगर bpf_preload.ko wasn't built पूर्णांकo vmlinux then load it */
	अगर (!bpf_preload_mod_get())
		जाओ out;

	अगर (!bpf_preload_ops->info.tgid) अणु
		/* preload() will start UMD that will load BPF iterator programs */
		err = bpf_preload_ops->preload(objs);
		अगर (err)
			जाओ out_put;
		क्रम (i = 0; i < BPF_PRELOAD_LINKS; i++) अणु
			links[i] = bpf_link_by_id(objs[i].link_id);
			अगर (IS_ERR(links[i])) अणु
				err = PTR_ERR(links[i]);
				जाओ out_put;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < BPF_PRELOAD_LINKS; i++) अणु
			err = bpf_iter_link_pin_kernel(parent,
						       objs[i].link_name, links[i]);
			अगर (err)
				जाओ out_put;
			/* करो not unlink successfully pinned links even
			 * अगर later link fails to pin
			 */
			links[i] = शून्य;
		पूर्ण
		/* finish() will tell UMD process to निकास */
		err = bpf_preload_ops->finish();
		अगर (err)
			जाओ out_put;
	पूर्ण
out_put:
	bpf_preload_mod_put();
out:
	mutex_unlock(&bpf_preload_lock);
	क्रम (i = 0; i < BPF_PRELOAD_LINKS && err; i++)
		अगर (!IS_ERR_OR_शून्य(links[i]))
			bpf_link_put(links[i]);
	वापस err;
पूर्ण

अटल पूर्णांक bpf_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	अटल स्थिर काष्ठा tree_descr bpf_rfiles[] = अणु अणु "" पूर्ण पूर्ण;
	काष्ठा bpf_mount_opts *opts = fc->fs_निजी;
	काष्ठा inode *inode;
	पूर्णांक ret;

	ret = simple_fill_super(sb, BPF_FS_MAGIC, bpf_rfiles);
	अगर (ret)
		वापस ret;

	sb->s_op = &bpf_super_ops;

	inode = sb->s_root->d_inode;
	inode->i_op = &bpf_dir_iops;
	inode->i_mode &= ~S_IALLUGO;
	populate_bpffs(sb->s_root);
	inode->i_mode |= S_ISVTX | opts->mode;
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_nodev(fc, bpf_fill_super);
पूर्ण

अटल व्योम bpf_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	kमुक्त(fc->fs_निजी);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations bpf_context_ops = अणु
	.मुक्त		= bpf_मुक्त_fc,
	.parse_param	= bpf_parse_param,
	.get_tree	= bpf_get_tree,
पूर्ण;

/*
 * Set up the fileप्रणाली mount context.
 */
अटल पूर्णांक bpf_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा bpf_mount_opts *opts;

	opts = kzalloc(माप(काष्ठा bpf_mount_opts), GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;

	opts->mode = S_IRWXUGO;

	fc->fs_निजी = opts;
	fc->ops = &bpf_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type bpf_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "bpf",
	.init_fs_context = bpf_init_fs_context,
	.parameters	= bpf_fs_parameters,
	.समाप्त_sb	= समाप्त_litter_super,
पूर्ण;

अटल पूर्णांक __init bpf_init(व्योम)
अणु
	पूर्णांक ret;

	ret = sysfs_create_mount_poपूर्णांक(fs_kobj, "bpf");
	अगर (ret)
		वापस ret;

	ret = रेजिस्टर_fileप्रणाली(&bpf_fs_type);
	अगर (ret)
		sysfs_हटाओ_mount_poपूर्णांक(fs_kobj, "bpf");

	वापस ret;
पूर्ण
fs_initcall(bpf_init);
