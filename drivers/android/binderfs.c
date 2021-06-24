<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/compiler_types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/gfp.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/namei.h>
#समावेश <linux/magic.h>
#समावेश <linux/major.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/xarray.h>
#समावेश <uapi/यंत्र-generic/त्रुटि_सं-base.h>
#समावेश <uapi/linux/android/binder.h>
#समावेश <uapi/linux/android/binderfs.h>

#समावेश "binder_internal.h"

#घोषणा FIRST_INODE 1
#घोषणा SECOND_INODE 2
#घोषणा INODE_OFFSET 3
#घोषणा INTSTRLEN 21
#घोषणा BINDERFS_MAX_MINOR (1U << MINORBITS)
/* Ensure that the initial ipc namespace always has devices available. */
#घोषणा BINDERFS_MAX_MINOR_CAPPED (BINDERFS_MAX_MINOR - 4)

अटल dev_t binderfs_dev;
अटल DEFINE_MUTEX(binderfs_minors_mutex);
अटल DEFINE_IDA(binderfs_minors);

क्रमागत binderfs_param अणु
	Opt_max,
	Opt_stats_mode,
पूर्ण;

क्रमागत binderfs_stats_mode अणु
	binderfs_stats_mode_unset,
	binderfs_stats_mode_global,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table binderfs_param_stats[] = अणु
	अणु "global", binderfs_stats_mode_global पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec binderfs_fs_parameters[] = अणु
	fsparam_u32("max",	Opt_max),
	fsparam_क्रमागत("stats",	Opt_stats_mode, binderfs_param_stats),
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत काष्ठा binderfs_info *BINDERFS_SB(स्थिर काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

bool is_binderfs_device(स्थिर काष्ठा inode *inode)
अणु
	अगर (inode->i_sb->s_magic == BINDERFS_SUPER_MAGIC)
		वापस true;

	वापस false;
पूर्ण

/**
 * binderfs_binder_device_create - allocate inode from super block of a
 *                                 binderfs mount
 * @ref_inode: inode from wich the super block will be taken
 * @userp:     buffer to copy inक्रमmation about new device क्रम userspace to
 * @req:       काष्ठा binderfs_device as copied from userspace
 *
 * This function allocates a new binder_device and reserves a new minor
 * number क्रम it.
 * Minor numbers are limited and tracked globally in binderfs_minors. The
 * function will stash a काष्ठा binder_device क्रम the specअगरic binder
 * device in i_निजी of the inode.
 * It will go on to allocate a new inode from the super block of the
 * fileप्रणाली mount, stash a काष्ठा binder_device in its i_निजी field
 * and attach a dentry to that inode.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure
 */
अटल पूर्णांक binderfs_binder_device_create(काष्ठा inode *ref_inode,
					 काष्ठा binderfs_device __user *userp,
					 काष्ठा binderfs_device *req)
अणु
	पूर्णांक minor, ret;
	काष्ठा dentry *dentry, *root;
	काष्ठा binder_device *device;
	अक्षर *name = शून्य;
	माप_प्रकार name_len;
	काष्ठा inode *inode = शून्य;
	काष्ठा super_block *sb = ref_inode->i_sb;
	काष्ठा binderfs_info *info = sb->s_fs_info;
#अगर defined(CONFIG_IPC_NS)
	bool use_reserve = (info->ipc_ns == &init_ipc_ns);
#अन्यथा
	bool use_reserve = true;
#पूर्ण_अगर

	/* Reserve new minor number क्रम the new device. */
	mutex_lock(&binderfs_minors_mutex);
	अगर (++info->device_count <= info->mount_opts.max)
		minor = ida_alloc_max(&binderfs_minors,
				      use_reserve ? BINDERFS_MAX_MINOR :
						    BINDERFS_MAX_MINOR_CAPPED,
				      GFP_KERNEL);
	अन्यथा
		minor = -ENOSPC;
	अगर (minor < 0) अणु
		--info->device_count;
		mutex_unlock(&binderfs_minors_mutex);
		वापस minor;
	पूर्ण
	mutex_unlock(&binderfs_minors_mutex);

	ret = -ENOMEM;
	device = kzalloc(माप(*device), GFP_KERNEL);
	अगर (!device)
		जाओ err;

	inode = new_inode(sb);
	अगर (!inode)
		जाओ err;

	inode->i_ino = minor + INODE_OFFSET;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	init_special_inode(inode, S_IFCHR | 0600,
			   MKDEV(MAJOR(binderfs_dev), minor));
	inode->i_fop = &binder_fops;
	inode->i_uid = info->root_uid;
	inode->i_gid = info->root_gid;

	req->name[BINDERFS_MAX_NAME] = '\0'; /* NUL-terminate */
	name_len = म_माप(req->name);
	/* Make sure to include terminating NUL byte */
	name = kmemdup(req->name, name_len + 1, GFP_KERNEL);
	अगर (!name)
		जाओ err;

	refcount_set(&device->ref, 1);
	device->binderfs_inode = inode;
	device->context.binder_context_mgr_uid = INVALID_UID;
	device->context.name = name;
	device->miscdev.name = name;
	device->miscdev.minor = minor;
	mutex_init(&device->context.context_mgr_node_lock);

	req->major = MAJOR(binderfs_dev);
	req->minor = minor;

	अगर (userp && copy_to_user(userp, req, माप(*req))) अणु
		ret = -EFAULT;
		जाओ err;
	पूर्ण

	root = sb->s_root;
	inode_lock(d_inode(root));

	/* look it up */
	dentry = lookup_one_len(name, root, name_len);
	अगर (IS_ERR(dentry)) अणु
		inode_unlock(d_inode(root));
		ret = PTR_ERR(dentry);
		जाओ err;
	पूर्ण

	अगर (d_really_is_positive(dentry)) अणु
		/* alपढ़ोy exists */
		dput(dentry);
		inode_unlock(d_inode(root));
		ret = -EEXIST;
		जाओ err;
	पूर्ण

	inode->i_निजी = device;
	d_instantiate(dentry, inode);
	fsnotअगरy_create(root->d_inode, dentry);
	inode_unlock(d_inode(root));

	वापस 0;

err:
	kमुक्त(name);
	kमुक्त(device);
	mutex_lock(&binderfs_minors_mutex);
	--info->device_count;
	ida_मुक्त(&binderfs_minors, minor);
	mutex_unlock(&binderfs_minors_mutex);
	iput(inode);

	वापस ret;
पूर्ण

/**
 * binderfs_ctl_ioctl - handle binder device node allocation requests
 *
 * The request handler क्रम the binder-control device. All requests operate on
 * the binderfs mount the binder-control device resides in:
 * - BINDER_CTL_ADD
 *   Allocate a new binder device.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure
 */
अटल दीर्घ binder_ctl_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा binderfs_device __user *device = (काष्ठा binderfs_device __user *)arg;
	काष्ठा binderfs_device device_req;

	चयन (cmd) अणु
	हाल BINDER_CTL_ADD:
		ret = copy_from_user(&device_req, device, माप(device_req));
		अगर (ret) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ret = binderfs_binder_device_create(inode, device, &device_req);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम binderfs_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा binder_device *device = inode->i_निजी;
	काष्ठा binderfs_info *info = BINDERFS_SB(inode->i_sb);

	clear_inode(inode);

	अगर (!S_ISCHR(inode->i_mode) || !device)
		वापस;

	mutex_lock(&binderfs_minors_mutex);
	--info->device_count;
	ida_मुक्त(&binderfs_minors, device->miscdev.minor);
	mutex_unlock(&binderfs_minors_mutex);

	अगर (refcount_dec_and_test(&device->ref)) अणु
		kमुक्त(device->context.name);
		kमुक्त(device);
	पूर्ण
पूर्ण

अटल पूर्णांक binderfs_fs_context_parse_param(काष्ठा fs_context *fc,
					   काष्ठा fs_parameter *param)
अणु
	पूर्णांक opt;
	काष्ठा binderfs_mount_opts *ctx = fc->fs_निजी;
	काष्ठा fs_parse_result result;

	opt = fs_parse(fc, binderfs_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_max:
		अगर (result.uपूर्णांक_32 > BINDERFS_MAX_MINOR)
			वापस invalfc(fc, "Bad value for '%s'", param->key);

		ctx->max = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_stats_mode:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		ctx->stats_mode = result.uपूर्णांक_32;
		अवरोध;
	शेष:
		वापस invalfc(fc, "Unsupported parameter '%s'", param->key);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक binderfs_fs_context_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा binderfs_mount_opts *ctx = fc->fs_निजी;
	काष्ठा binderfs_info *info = BINDERFS_SB(fc->root->d_sb);

	अगर (info->mount_opts.stats_mode != ctx->stats_mode)
		वापस invalfc(fc, "Binderfs stats mode cannot be changed during a remount");

	info->mount_opts.stats_mode = ctx->stats_mode;
	info->mount_opts.max = ctx->max;
	वापस 0;
पूर्ण

अटल पूर्णांक binderfs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा binderfs_info *info = BINDERFS_SB(root->d_sb);

	अगर (info->mount_opts.max <= BINDERFS_MAX_MINOR)
		seq_म_लिखो(seq, ",max=%d", info->mount_opts.max);

	चयन (info->mount_opts.stats_mode) अणु
	हाल binderfs_stats_mode_unset:
		अवरोध;
	हाल binderfs_stats_mode_global:
		seq_म_लिखो(seq, ",stats=global");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम binderfs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा binderfs_info *info = sb->s_fs_info;

	अगर (info && info->ipc_ns)
		put_ipc_ns(info->ipc_ns);

	kमुक्त(info);
	sb->s_fs_info = शून्य;
पूर्ण

अटल स्थिर काष्ठा super_operations binderfs_super_ops = अणु
	.evict_inode    = binderfs_evict_inode,
	.show_options	= binderfs_show_options,
	.statfs         = simple_statfs,
	.put_super	= binderfs_put_super,
पूर्ण;

अटल अंतरभूत bool is_binderfs_control_device(स्थिर काष्ठा dentry *dentry)
अणु
	काष्ठा binderfs_info *info = dentry->d_sb->s_fs_info;

	वापस info->control_dentry == dentry;
पूर्ण

अटल पूर्णांक binderfs_नाम(काष्ठा user_namespace *mnt_userns,
			   काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			   काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			   अचिन्हित पूर्णांक flags)
अणु
	अगर (is_binderfs_control_device(old_dentry) ||
	    is_binderfs_control_device(new_dentry))
		वापस -EPERM;

	वापस simple_नाम(&init_user_ns, old_dir, old_dentry, new_dir,
			     new_dentry, flags);
पूर्ण

अटल पूर्णांक binderfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	अगर (is_binderfs_control_device(dentry))
		वापस -EPERM;

	वापस simple_unlink(dir, dentry);
पूर्ण

अटल स्थिर काष्ठा file_operations binder_ctl_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= nonseekable_खोलो,
	.unlocked_ioctl	= binder_ctl_ioctl,
	.compat_ioctl	= binder_ctl_ioctl,
	.llseek		= noop_llseek,
पूर्ण;

/**
 * binderfs_binder_ctl_create - create a new binder-control device
 * @sb: super block of the binderfs mount
 *
 * This function creates a new binder-control device node in the binderfs mount
 * referred to by @sb.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure
 */
अटल पूर्णांक binderfs_binder_ctl_create(काष्ठा super_block *sb)
अणु
	पूर्णांक minor, ret;
	काष्ठा dentry *dentry;
	काष्ठा binder_device *device;
	काष्ठा inode *inode = शून्य;
	काष्ठा dentry *root = sb->s_root;
	काष्ठा binderfs_info *info = sb->s_fs_info;
#अगर defined(CONFIG_IPC_NS)
	bool use_reserve = (info->ipc_ns == &init_ipc_ns);
#अन्यथा
	bool use_reserve = true;
#पूर्ण_अगर

	device = kzalloc(माप(*device), GFP_KERNEL);
	अगर (!device)
		वापस -ENOMEM;

	/* If we have alपढ़ोy created a binder-control node, वापस. */
	अगर (info->control_dentry) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	ret = -ENOMEM;
	inode = new_inode(sb);
	अगर (!inode)
		जाओ out;

	/* Reserve a new minor number क्रम the new device. */
	mutex_lock(&binderfs_minors_mutex);
	minor = ida_alloc_max(&binderfs_minors,
			      use_reserve ? BINDERFS_MAX_MINOR :
					    BINDERFS_MAX_MINOR_CAPPED,
			      GFP_KERNEL);
	mutex_unlock(&binderfs_minors_mutex);
	अगर (minor < 0) अणु
		ret = minor;
		जाओ out;
	पूर्ण

	inode->i_ino = SECOND_INODE;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	init_special_inode(inode, S_IFCHR | 0600,
			   MKDEV(MAJOR(binderfs_dev), minor));
	inode->i_fop = &binder_ctl_fops;
	inode->i_uid = info->root_uid;
	inode->i_gid = info->root_gid;

	refcount_set(&device->ref, 1);
	device->binderfs_inode = inode;
	device->miscdev.minor = minor;

	dentry = d_alloc_name(root, "binder-control");
	अगर (!dentry)
		जाओ out;

	inode->i_निजी = device;
	info->control_dentry = dentry;
	d_add(dentry, inode);

	वापस 0;

out:
	kमुक्त(device);
	iput(inode);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा inode_operations binderfs_dir_inode_operations = अणु
	.lookup = simple_lookup,
	.नाम = binderfs_नाम,
	.unlink = binderfs_unlink,
पूर्ण;

अटल काष्ठा inode *binderfs_make_inode(काष्ठा super_block *sb, पूर्णांक mode)
अणु
	काष्ठा inode *ret;

	ret = new_inode(sb);
	अगर (ret) अणु
		ret->i_ino = iunique(sb, BINDERFS_MAX_MINOR + INODE_OFFSET);
		ret->i_mode = mode;
		ret->i_aसमय = ret->i_mसमय = ret->i_स_समय = current_समय(ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा dentry *binderfs_create_dentry(काष्ठा dentry *parent,
					     स्थिर अक्षर *name)
अणु
	काष्ठा dentry *dentry;

	dentry = lookup_one_len(name, parent, म_माप(name));
	अगर (IS_ERR(dentry))
		वापस dentry;

	/* Return error अगर the file/dir alपढ़ोy exists. */
	अगर (d_really_is_positive(dentry)) अणु
		dput(dentry);
		वापस ERR_PTR(-EEXIST);
	पूर्ण

	वापस dentry;
पूर्ण

व्योम binderfs_हटाओ_file(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *parent_inode;

	parent_inode = d_inode(dentry->d_parent);
	inode_lock(parent_inode);
	अगर (simple_positive(dentry)) अणु
		dget(dentry);
		simple_unlink(parent_inode, dentry);
		d_delete(dentry);
		dput(dentry);
	पूर्ण
	inode_unlock(parent_inode);
पूर्ण

काष्ठा dentry *binderfs_create_file(काष्ठा dentry *parent, स्थिर अक्षर *name,
				    स्थिर काष्ठा file_operations *fops,
				    व्योम *data)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *new_inode, *parent_inode;
	काष्ठा super_block *sb;

	parent_inode = d_inode(parent);
	inode_lock(parent_inode);

	dentry = binderfs_create_dentry(parent, name);
	अगर (IS_ERR(dentry))
		जाओ out;

	sb = parent_inode->i_sb;
	new_inode = binderfs_make_inode(sb, S_IFREG | 0444);
	अगर (!new_inode) अणु
		dput(dentry);
		dentry = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	new_inode->i_fop = fops;
	new_inode->i_निजी = data;
	d_instantiate(dentry, new_inode);
	fsnotअगरy_create(parent_inode, dentry);

out:
	inode_unlock(parent_inode);
	वापस dentry;
पूर्ण

अटल काष्ठा dentry *binderfs_create_dir(काष्ठा dentry *parent,
					  स्थिर अक्षर *name)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *new_inode, *parent_inode;
	काष्ठा super_block *sb;

	parent_inode = d_inode(parent);
	inode_lock(parent_inode);

	dentry = binderfs_create_dentry(parent, name);
	अगर (IS_ERR(dentry))
		जाओ out;

	sb = parent_inode->i_sb;
	new_inode = binderfs_make_inode(sb, S_IFसूची | 0755);
	अगर (!new_inode) अणु
		dput(dentry);
		dentry = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	new_inode->i_fop = &simple_dir_operations;
	new_inode->i_op = &simple_dir_inode_operations;

	set_nlink(new_inode, 2);
	d_instantiate(dentry, new_inode);
	inc_nlink(parent_inode);
	fsnotअगरy_सूची_गढ़ो(parent_inode, dentry);

out:
	inode_unlock(parent_inode);
	वापस dentry;
पूर्ण

अटल पूर्णांक init_binder_logs(काष्ठा super_block *sb)
अणु
	काष्ठा dentry *binder_logs_root_dir, *dentry, *proc_log_dir;
	काष्ठा binderfs_info *info;
	पूर्णांक ret = 0;

	binder_logs_root_dir = binderfs_create_dir(sb->s_root,
						   "binder_logs");
	अगर (IS_ERR(binder_logs_root_dir)) अणु
		ret = PTR_ERR(binder_logs_root_dir);
		जाओ out;
	पूर्ण

	dentry = binderfs_create_file(binder_logs_root_dir, "stats",
				      &binder_stats_fops, शून्य);
	अगर (IS_ERR(dentry)) अणु
		ret = PTR_ERR(dentry);
		जाओ out;
	पूर्ण

	dentry = binderfs_create_file(binder_logs_root_dir, "state",
				      &binder_state_fops, शून्य);
	अगर (IS_ERR(dentry)) अणु
		ret = PTR_ERR(dentry);
		जाओ out;
	पूर्ण

	dentry = binderfs_create_file(binder_logs_root_dir, "transactions",
				      &binder_transactions_fops, शून्य);
	अगर (IS_ERR(dentry)) अणु
		ret = PTR_ERR(dentry);
		जाओ out;
	पूर्ण

	dentry = binderfs_create_file(binder_logs_root_dir,
				      "transaction_log",
				      &binder_transaction_log_fops,
				      &binder_transaction_log);
	अगर (IS_ERR(dentry)) अणु
		ret = PTR_ERR(dentry);
		जाओ out;
	पूर्ण

	dentry = binderfs_create_file(binder_logs_root_dir,
				      "failed_transaction_log",
				      &binder_transaction_log_fops,
				      &binder_transaction_log_failed);
	अगर (IS_ERR(dentry)) अणु
		ret = PTR_ERR(dentry);
		जाओ out;
	पूर्ण

	proc_log_dir = binderfs_create_dir(binder_logs_root_dir, "proc");
	अगर (IS_ERR(proc_log_dir)) अणु
		ret = PTR_ERR(proc_log_dir);
		जाओ out;
	पूर्ण
	info = sb->s_fs_info;
	info->proc_log_dir = proc_log_dir;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक binderfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	पूर्णांक ret;
	काष्ठा binderfs_info *info;
	काष्ठा binderfs_mount_opts *ctx = fc->fs_निजी;
	काष्ठा inode *inode = शून्य;
	काष्ठा binderfs_device device_info = अणुपूर्ण;
	स्थिर अक्षर *name;
	माप_प्रकार len;

	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;

	/*
	 * The binderfs fileप्रणाली can be mounted by userns root in a
	 * non-initial userns. By शेष such mounts have the SB_I_NODEV flag
	 * set in s_अगरlags to prevent security issues where userns root can
	 * just create अक्रमom device nodes via mknod() since it owns the
	 * fileप्रणाली mount. But binderfs करोes not allow to create any files
	 * including devices nodes. The only way to create binder devices nodes
	 * is through the binder-control device which userns root is explicitly
	 * allowed to करो. So removing the SB_I_NODEV flag from s_अगरlags is both
	 * necessary and safe.
	 */
	sb->s_अगरlags &= ~SB_I_NODEV;
	sb->s_अगरlags |= SB_I_NOEXEC;
	sb->s_magic = BINDERFS_SUPER_MAGIC;
	sb->s_op = &binderfs_super_ops;
	sb->s_समय_gran = 1;

	sb->s_fs_info = kzalloc(माप(काष्ठा binderfs_info), GFP_KERNEL);
	अगर (!sb->s_fs_info)
		वापस -ENOMEM;
	info = sb->s_fs_info;

	info->ipc_ns = get_ipc_ns(current->nsproxy->ipc_ns);

	info->root_gid = make_kgid(sb->s_user_ns, 0);
	अगर (!gid_valid(info->root_gid))
		info->root_gid = GLOBAL_ROOT_GID;
	info->root_uid = make_kuid(sb->s_user_ns, 0);
	अगर (!uid_valid(info->root_uid))
		info->root_uid = GLOBAL_ROOT_UID;
	info->mount_opts.max = ctx->max;
	info->mount_opts.stats_mode = ctx->stats_mode;

	inode = new_inode(sb);
	अगर (!inode)
		वापस -ENOMEM;

	inode->i_ino = FIRST_INODE;
	inode->i_fop = &simple_dir_operations;
	inode->i_mode = S_IFसूची | 0755;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	inode->i_op = &binderfs_dir_inode_operations;
	set_nlink(inode, 2);

	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root)
		वापस -ENOMEM;

	ret = binderfs_binder_ctl_create(sb);
	अगर (ret)
		वापस ret;

	name = binder_devices_param;
	क्रम (len = म_खोज(name, ","); len > 0; len = म_खोज(name, ",")) अणु
		strscpy(device_info.name, name, len + 1);
		ret = binderfs_binder_device_create(inode, शून्य, &device_info);
		अगर (ret)
			वापस ret;
		name += len;
		अगर (*name == ',')
			name++;
	पूर्ण

	अगर (info->mount_opts.stats_mode == binderfs_stats_mode_global)
		वापस init_binder_logs(sb);

	वापस 0;
पूर्ण

अटल पूर्णांक binderfs_fs_context_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_nodev(fc, binderfs_fill_super);
पूर्ण

अटल व्योम binderfs_fs_context_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा binderfs_mount_opts *ctx = fc->fs_निजी;

	kमुक्त(ctx);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations binderfs_fs_context_ops = अणु
	.मुक्त		= binderfs_fs_context_मुक्त,
	.get_tree	= binderfs_fs_context_get_tree,
	.parse_param	= binderfs_fs_context_parse_param,
	.reconfigure	= binderfs_fs_context_reconfigure,
पूर्ण;

अटल पूर्णांक binderfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा binderfs_mount_opts *ctx;

	ctx = kzalloc(माप(काष्ठा binderfs_mount_opts), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->max = BINDERFS_MAX_MINOR;
	ctx->stats_mode = binderfs_stats_mode_unset;

	fc->fs_निजी = ctx;
	fc->ops = &binderfs_fs_context_ops;

	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type binder_fs_type = अणु
	.name			= "binder",
	.init_fs_context	= binderfs_init_fs_context,
	.parameters		= binderfs_fs_parameters,
	.समाप्त_sb		= समाप्त_litter_super,
	.fs_flags		= FS_USERNS_MOUNT,
पूर्ण;

पूर्णांक __init init_binderfs(व्योम)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *name;
	माप_प्रकार len;

	/* Verअगरy that the शेष binderfs device names are valid. */
	name = binder_devices_param;
	क्रम (len = म_खोज(name, ","); len > 0; len = म_खोज(name, ",")) अणु
		अगर (len > BINDERFS_MAX_NAME)
			वापस -E2BIG;
		name += len;
		अगर (*name == ',')
			name++;
	पूर्ण

	/* Allocate new major number क्रम binderfs. */
	ret = alloc_chrdev_region(&binderfs_dev, 0, BINDERFS_MAX_MINOR,
				  "binder");
	अगर (ret)
		वापस ret;

	ret = रेजिस्टर_fileप्रणाली(&binder_fs_type);
	अगर (ret) अणु
		unरेजिस्टर_chrdev_region(binderfs_dev, BINDERFS_MAX_MINOR);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
