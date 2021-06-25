<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  inode.c - part of debugfs, a tiny little debug file प्रणाली
 *
 *  Copyright (C) 2004,2019 Greg Kroah-Harपंचांगan <greg@kroah.com>
 *  Copyright (C) 2004 IBM Inc.
 *  Copyright (C) 2019 Linux Foundation <gregkh@linuxfoundation.org>
 *
 *  debugfs is क्रम people to use instead of /proc or /sys.
 *  See ./Documentation/core-api/kernel-api.rst क्रम more details.
 */

#घोषणा pr_fmt(fmt)	"debugfs: " fmt

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/init.h>
#समावेश <linux/kobject.h>
#समावेश <linux/namei.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/parser.h>
#समावेश <linux/magic.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>

#समावेश "internal.h"

#घोषणा DEBUGFS_DEFAULT_MODE	0700

अटल काष्ठा vfsmount *debugfs_mount;
अटल पूर्णांक debugfs_mount_count;
अटल bool debugfs_रेजिस्टरed;
अटल अचिन्हित पूर्णांक debugfs_allow __ro_after_init = DEFAULT_DEBUGFS_ALLOW_BITS;

/*
 * Don't allow access attributes to be changed whilst the kernel is locked करोwn
 * so that we can use the file mode as part of a heuristic to determine whether
 * to lock करोwn inभागidual files.
 */
अटल पूर्णांक debugfs_setattr(काष्ठा user_namespace *mnt_userns,
			   काष्ठा dentry *dentry, काष्ठा iattr *ia)
अणु
	पूर्णांक ret;

	अगर (ia->ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID)) अणु
		ret = security_locked_करोwn(LOCKDOWN_DEBUGFS);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस simple_setattr(&init_user_ns, dentry, ia);
पूर्ण

अटल स्थिर काष्ठा inode_operations debugfs_file_inode_operations = अणु
	.setattr	= debugfs_setattr,
पूर्ण;
अटल स्थिर काष्ठा inode_operations debugfs_dir_inode_operations = अणु
	.lookup		= simple_lookup,
	.setattr	= debugfs_setattr,
पूर्ण;
अटल स्थिर काष्ठा inode_operations debugfs_symlink_inode_operations = अणु
	.get_link	= simple_get_link,
	.setattr	= debugfs_setattr,
पूर्ण;

अटल काष्ठा inode *debugfs_get_inode(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode = new_inode(sb);
	अगर (inode) अणु
		inode->i_ino = get_next_ino();
		inode->i_aसमय = inode->i_mसमय =
			inode->i_स_समय = current_समय(inode);
	पूर्ण
	वापस inode;
पूर्ण

काष्ठा debugfs_mount_opts अणु
	kuid_t uid;
	kgid_t gid;
	umode_t mode;
पूर्ण;

क्रमागत अणु
	Opt_uid,
	Opt_gid,
	Opt_mode,
	Opt_err
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_uid, "uid=%u"पूर्ण,
	अणुOpt_gid, "gid=%u"पूर्ण,
	अणुOpt_mode, "mode=%o"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

काष्ठा debugfs_fs_info अणु
	काष्ठा debugfs_mount_opts mount_opts;
पूर्ण;

अटल पूर्णांक debugfs_parse_options(अक्षर *data, काष्ठा debugfs_mount_opts *opts)
अणु
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक option;
	पूर्णांक token;
	kuid_t uid;
	kgid_t gid;
	अक्षर *p;

	opts->mode = DEBUGFS_DEFAULT_MODE;

	जबतक ((p = strsep(&data, ",")) != शून्य) अणु
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_uid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस -EINVAL;
			uid = make_kuid(current_user_ns(), option);
			अगर (!uid_valid(uid))
				वापस -EINVAL;
			opts->uid = uid;
			अवरोध;
		हाल Opt_gid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस -EINVAL;
			gid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(gid))
				वापस -EINVAL;
			opts->gid = gid;
			अवरोध;
		हाल Opt_mode:
			अगर (match_octal(&args[0], &option))
				वापस -EINVAL;
			opts->mode = option & S_IALLUGO;
			अवरोध;
		/*
		 * We might like to report bad mount options here;
		 * but traditionally debugfs has ignored all mount options
		 */
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_apply_options(काष्ठा super_block *sb)
अणु
	काष्ठा debugfs_fs_info *fsi = sb->s_fs_info;
	काष्ठा inode *inode = d_inode(sb->s_root);
	काष्ठा debugfs_mount_opts *opts = &fsi->mount_opts;

	inode->i_mode &= ~S_IALLUGO;
	inode->i_mode |= opts->mode;

	inode->i_uid = opts->uid;
	inode->i_gid = opts->gid;

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	पूर्णांक err;
	काष्ठा debugfs_fs_info *fsi = sb->s_fs_info;

	sync_fileप्रणाली(sb);
	err = debugfs_parse_options(data, &fsi->mount_opts);
	अगर (err)
		जाओ fail;

	debugfs_apply_options(sb);

fail:
	वापस err;
पूर्ण

अटल पूर्णांक debugfs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा debugfs_fs_info *fsi = root->d_sb->s_fs_info;
	काष्ठा debugfs_mount_opts *opts = &fsi->mount_opts;

	अगर (!uid_eq(opts->uid, GLOBAL_ROOT_UID))
		seq_म_लिखो(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, opts->uid));
	अगर (!gid_eq(opts->gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, opts->gid));
	अगर (opts->mode != DEBUGFS_DEFAULT_MODE)
		seq_म_लिखो(m, ",mode=%o", opts->mode);

	वापस 0;
पूर्ण

अटल व्योम debugfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	अगर (S_ISLNK(inode->i_mode))
		kमुक्त(inode->i_link);
	मुक्त_inode_nonrcu(inode);
पूर्ण

अटल स्थिर काष्ठा super_operations debugfs_super_operations = अणु
	.statfs		= simple_statfs,
	.remount_fs	= debugfs_remount,
	.show_options	= debugfs_show_options,
	.मुक्त_inode	= debugfs_मुक्त_inode,
पूर्ण;

अटल व्योम debugfs_release_dentry(काष्ठा dentry *dentry)
अणु
	व्योम *fsd = dentry->d_fsdata;

	अगर (!((अचिन्हित दीर्घ)fsd & DEBUGFS_FSDATA_IS_REAL_FOPS_BIT))
		kमुक्त(dentry->d_fsdata);
पूर्ण

अटल काष्ठा vfsmount *debugfs_स्वतःmount(काष्ठा path *path)
अणु
	debugfs_स्वतःmount_t f;
	f = (debugfs_स्वतःmount_t)path->dentry->d_fsdata;
	वापस f(path->dentry, d_inode(path->dentry)->i_निजी);
पूर्ण

अटल स्थिर काष्ठा dentry_operations debugfs_करोps = अणु
	.d_delete = always_delete_dentry,
	.d_release = debugfs_release_dentry,
	.d_स्वतःmount = debugfs_स्वतःmount,
पूर्ण;

अटल पूर्णांक debug_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	अटल स्थिर काष्ठा tree_descr debug_files[] = अणुअणु""पूर्णपूर्ण;
	काष्ठा debugfs_fs_info *fsi;
	पूर्णांक err;

	fsi = kzalloc(माप(काष्ठा debugfs_fs_info), GFP_KERNEL);
	sb->s_fs_info = fsi;
	अगर (!fsi) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	err = debugfs_parse_options(data, &fsi->mount_opts);
	अगर (err)
		जाओ fail;

	err  =  simple_fill_super(sb, DEBUGFS_MAGIC, debug_files);
	अगर (err)
		जाओ fail;

	sb->s_op = &debugfs_super_operations;
	sb->s_d_op = &debugfs_करोps;

	debugfs_apply_options(sb);

	वापस 0;

fail:
	kमुक्त(fsi);
	sb->s_fs_info = शून्य;
	वापस err;
पूर्ण

अटल काष्ठा dentry *debug_mount(काष्ठा file_प्रणाली_type *fs_type,
			पूर्णांक flags, स्थिर अक्षर *dev_name,
			व्योम *data)
अणु
	अगर (!(debugfs_allow & DEBUGFS_ALLOW_API))
		वापस ERR_PTR(-EPERM);

	वापस mount_single(fs_type, flags, data, debug_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type debug_fs_type = अणु
	.owner =	THIS_MODULE,
	.name =		"debugfs",
	.mount =	debug_mount,
	.समाप्त_sb =	समाप्त_litter_super,
पूर्ण;
MODULE_ALIAS_FS("debugfs");

/**
 * debugfs_lookup() - look up an existing debugfs file
 * @name: a poपूर्णांकer to a string containing the name of the file to look up.
 * @parent: a poपूर्णांकer to the parent dentry of the file.
 *
 * This function will वापस a poपूर्णांकer to a dentry अगर it succeeds.  If the file
 * करोesn't exist or an error occurs, %शून्य will be वापसed.  The वापसed
 * dentry must be passed to dput() when it is no दीर्घer needed.
 *
 * If debugfs is not enabled in the kernel, the value -%ENODEV will be
 * वापसed.
 */
काष्ठा dentry *debugfs_lookup(स्थिर अक्षर *name, काष्ठा dentry *parent)
अणु
	काष्ठा dentry *dentry;

	अगर (!debugfs_initialized() || IS_ERR_OR_शून्य(name) || IS_ERR(parent))
		वापस शून्य;

	अगर (!parent)
		parent = debugfs_mount->mnt_root;

	dentry = lookup_positive_unlocked(name, parent, म_माप(name));
	अगर (IS_ERR(dentry))
		वापस शून्य;
	वापस dentry;
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_lookup);

अटल काष्ठा dentry *start_creating(स्थिर अक्षर *name, काष्ठा dentry *parent)
अणु
	काष्ठा dentry *dentry;
	पूर्णांक error;

	अगर (!(debugfs_allow & DEBUGFS_ALLOW_API))
		वापस ERR_PTR(-EPERM);

	अगर (!debugfs_initialized())
		वापस ERR_PTR(-ENOENT);

	pr_debug("creating file '%s'\n", name);

	अगर (IS_ERR(parent))
		वापस parent;

	error = simple_pin_fs(&debug_fs_type, &debugfs_mount,
			      &debugfs_mount_count);
	अगर (error) अणु
		pr_err("Unable to pin filesystem for file '%s'\n", name);
		वापस ERR_PTR(error);
	पूर्ण

	/* If the parent is not specअगरied, we create it in the root.
	 * We need the root dentry to करो this, which is in the super
	 * block. A poपूर्णांकer to that is in the काष्ठा vfsmount that we
	 * have around.
	 */
	अगर (!parent)
		parent = debugfs_mount->mnt_root;

	inode_lock(d_inode(parent));
	अगर (unlikely(IS_DEADसूची(d_inode(parent))))
		dentry = ERR_PTR(-ENOENT);
	अन्यथा
		dentry = lookup_one_len(name, parent, म_माप(name));
	अगर (!IS_ERR(dentry) && d_really_is_positive(dentry)) अणु
		अगर (d_is_dir(dentry))
			pr_err("Directory '%s' with parent '%s' already present!\n",
			       name, parent->d_name.name);
		अन्यथा
			pr_err("File '%s' in directory '%s' already present!\n",
			       name, parent->d_name.name);
		dput(dentry);
		dentry = ERR_PTR(-EEXIST);
	पूर्ण

	अगर (IS_ERR(dentry)) अणु
		inode_unlock(d_inode(parent));
		simple_release_fs(&debugfs_mount, &debugfs_mount_count);
	पूर्ण

	वापस dentry;
पूर्ण

अटल काष्ठा dentry *failed_creating(काष्ठा dentry *dentry)
अणु
	inode_unlock(d_inode(dentry->d_parent));
	dput(dentry);
	simple_release_fs(&debugfs_mount, &debugfs_mount_count);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल काष्ठा dentry *end_creating(काष्ठा dentry *dentry)
अणु
	inode_unlock(d_inode(dentry->d_parent));
	वापस dentry;
पूर्ण

अटल काष्ठा dentry *__debugfs_create_file(स्थिर अक्षर *name, umode_t mode,
				काष्ठा dentry *parent, व्योम *data,
				स्थिर काष्ठा file_operations *proxy_fops,
				स्थिर काष्ठा file_operations *real_fops)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;

	अगर (!(mode & S_IFMT))
		mode |= S_IFREG;
	BUG_ON(!S_ISREG(mode));
	dentry = start_creating(name, parent);

	अगर (IS_ERR(dentry))
		वापस dentry;

	अगर (!(debugfs_allow & DEBUGFS_ALLOW_API)) अणु
		failed_creating(dentry);
		वापस ERR_PTR(-EPERM);
	पूर्ण

	inode = debugfs_get_inode(dentry->d_sb);
	अगर (unlikely(!inode)) अणु
		pr_err("out of free dentries, can not create file '%s'\n",
		       name);
		वापस failed_creating(dentry);
	पूर्ण

	inode->i_mode = mode;
	inode->i_निजी = data;

	inode->i_op = &debugfs_file_inode_operations;
	inode->i_fop = proxy_fops;
	dentry->d_fsdata = (व्योम *)((अचिन्हित दीर्घ)real_fops |
				DEBUGFS_FSDATA_IS_REAL_FOPS_BIT);

	d_instantiate(dentry, inode);
	fsnotअगरy_create(d_inode(dentry->d_parent), dentry);
	वापस end_creating(dentry);
पूर्ण

/**
 * debugfs_create_file - create a file in the debugfs fileप्रणाली
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @data: a poपूर्णांकer to something that the caller will want to get to later
 *        on.  The inode.i_निजी poपूर्णांकer will poपूर्णांक to this value on
 *        the खोलो() call.
 * @fops: a poपूर्णांकer to a काष्ठा file_operations that should be used क्रम
 *        this file.
 *
 * This is the basic "create a file" function क्रम debugfs.  It allows क्रम a
 * wide range of flexibility in creating a file, or a directory (अगर you want
 * to create a directory, the debugfs_create_dir() function is
 * recommended to be used instead.)
 *
 * This function will वापस a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the debugfs_हटाओ() function when the file is
 * to be हटाओd (no स्वतःmatic cleanup happens अगर your module is unloaded,
 * you are responsible here.)  If an error occurs, ERR_PTR(-ERROR) will be
 * वापसed.
 *
 * If debugfs is not enabled in the kernel, the value -%ENODEV will be
 * वापसed.
 */
काष्ठा dentry *debugfs_create_file(स्थिर अक्षर *name, umode_t mode,
				   काष्ठा dentry *parent, व्योम *data,
				   स्थिर काष्ठा file_operations *fops)
अणु

	वापस __debugfs_create_file(name, mode, parent, data,
				fops ? &debugfs_full_proxy_file_operations :
					&debugfs_noop_file_operations,
				fops);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_file);

/**
 * debugfs_create_file_unsafe - create a file in the debugfs fileप्रणाली
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @data: a poपूर्णांकer to something that the caller will want to get to later
 *        on.  The inode.i_निजी poपूर्णांकer will poपूर्णांक to this value on
 *        the खोलो() call.
 * @fops: a poपूर्णांकer to a काष्ठा file_operations that should be used क्रम
 *        this file.
 *
 * debugfs_create_file_unsafe() is completely analogous to
 * debugfs_create_file(), the only dअगरference being that the fops
 * handed it will not get रक्षित against file removals by the
 * debugfs core.
 *
 * It is your responsibility to protect your काष्ठा file_operation
 * methods against file removals by means of debugfs_file_get()
 * and debugfs_file_put(). ->खोलो() is still रक्षित by
 * debugfs though.
 *
 * Any काष्ठा file_operations defined by means of
 * DEFINE_DEBUGFS_ATTRIBUTE() is रक्षित against file removals and
 * thus, may be used here.
 */
काष्ठा dentry *debugfs_create_file_unsafe(स्थिर अक्षर *name, umode_t mode,
				   काष्ठा dentry *parent, व्योम *data,
				   स्थिर काष्ठा file_operations *fops)
अणु

	वापस __debugfs_create_file(name, mode, parent, data,
				fops ? &debugfs_खोलो_proxy_file_operations :
					&debugfs_noop_file_operations,
				fops);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_file_unsafe);

/**
 * debugfs_create_file_size - create a file in the debugfs fileप्रणाली
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @data: a poपूर्णांकer to something that the caller will want to get to later
 *        on.  The inode.i_निजी poपूर्णांकer will poपूर्णांक to this value on
 *        the खोलो() call.
 * @fops: a poपूर्णांकer to a काष्ठा file_operations that should be used क्रम
 *        this file.
 * @file_size: initial file size
 *
 * This is the basic "create a file" function क्रम debugfs.  It allows क्रम a
 * wide range of flexibility in creating a file, or a directory (अगर you want
 * to create a directory, the debugfs_create_dir() function is
 * recommended to be used instead.)
 */
व्योम debugfs_create_file_size(स्थिर अक्षर *name, umode_t mode,
			      काष्ठा dentry *parent, व्योम *data,
			      स्थिर काष्ठा file_operations *fops,
			      loff_t file_size)
अणु
	काष्ठा dentry *de = debugfs_create_file(name, mode, parent, data, fops);

	अगर (de)
		d_inode(de)->i_size = file_size;
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_file_size);

/**
 * debugfs_create_dir - create a directory in the debugfs fileप्रणाली
 * @name: a poपूर्णांकer to a string containing the name of the directory to
 *        create.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is शून्य, then the
 *          directory will be created in the root of the debugfs fileप्रणाली.
 *
 * This function creates a directory in debugfs with the given name.
 *
 * This function will वापस a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the debugfs_हटाओ() function when the file is
 * to be हटाओd (no स्वतःmatic cleanup happens अगर your module is unloaded,
 * you are responsible here.)  If an error occurs, ERR_PTR(-ERROR) will be
 * वापसed.
 *
 * If debugfs is not enabled in the kernel, the value -%ENODEV will be
 * वापसed.
 */
काष्ठा dentry *debugfs_create_dir(स्थिर अक्षर *name, काष्ठा dentry *parent)
अणु
	काष्ठा dentry *dentry = start_creating(name, parent);
	काष्ठा inode *inode;

	अगर (IS_ERR(dentry))
		वापस dentry;

	अगर (!(debugfs_allow & DEBUGFS_ALLOW_API)) अणु
		failed_creating(dentry);
		वापस ERR_PTR(-EPERM);
	पूर्ण

	inode = debugfs_get_inode(dentry->d_sb);
	अगर (unlikely(!inode)) अणु
		pr_err("out of free dentries, can not create directory '%s'\n",
		       name);
		वापस failed_creating(dentry);
	पूर्ण

	inode->i_mode = S_IFसूची | S_IRWXU | S_IRUGO | S_IXUGO;
	inode->i_op = &debugfs_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;

	/* directory inodes start off with i_nlink == 2 (क्रम "." entry) */
	inc_nlink(inode);
	d_instantiate(dentry, inode);
	inc_nlink(d_inode(dentry->d_parent));
	fsnotअगरy_सूची_गढ़ो(d_inode(dentry->d_parent), dentry);
	वापस end_creating(dentry);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_dir);

/**
 * debugfs_create_स्वतःmount - create स्वतःmount poपूर्णांक in the debugfs fileप्रणाली
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @f: function to be called when pathname resolution steps on that one.
 * @data: opaque argument to pass to f().
 *
 * @f should वापस what ->d_स्वतःmount() would.
 */
काष्ठा dentry *debugfs_create_स्वतःmount(स्थिर अक्षर *name,
					काष्ठा dentry *parent,
					debugfs_स्वतःmount_t f,
					व्योम *data)
अणु
	काष्ठा dentry *dentry = start_creating(name, parent);
	काष्ठा inode *inode;

	अगर (IS_ERR(dentry))
		वापस dentry;

	अगर (!(debugfs_allow & DEBUGFS_ALLOW_API)) अणु
		failed_creating(dentry);
		वापस ERR_PTR(-EPERM);
	पूर्ण

	inode = debugfs_get_inode(dentry->d_sb);
	अगर (unlikely(!inode)) अणु
		pr_err("out of free dentries, can not create automount '%s'\n",
		       name);
		वापस failed_creating(dentry);
	पूर्ण

	make_empty_dir_inode(inode);
	inode->i_flags |= S_AUTOMOUNT;
	inode->i_निजी = data;
	dentry->d_fsdata = (व्योम *)f;
	/* directory inodes start off with i_nlink == 2 (क्रम "." entry) */
	inc_nlink(inode);
	d_instantiate(dentry, inode);
	inc_nlink(d_inode(dentry->d_parent));
	fsnotअगरy_सूची_गढ़ो(d_inode(dentry->d_parent), dentry);
	वापस end_creating(dentry);
पूर्ण
EXPORT_SYMBOL(debugfs_create_स्वतःmount);

/**
 * debugfs_create_symlink- create a symbolic link in the debugfs fileप्रणाली
 * @name: a poपूर्णांकer to a string containing the name of the symbolic link to
 *        create.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this symbolic link.  This
 *          should be a directory dentry अगर set.  If this parameter is शून्य,
 *          then the symbolic link will be created in the root of the debugfs
 *          fileप्रणाली.
 * @target: a poपूर्णांकer to a string containing the path to the target of the
 *          symbolic link.
 *
 * This function creates a symbolic link with the given name in debugfs that
 * links to the given target path.
 *
 * This function will वापस a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the debugfs_हटाओ() function when the symbolic
 * link is to be हटाओd (no स्वतःmatic cleanup happens अगर your module is
 * unloaded, you are responsible here.)  If an error occurs, ERR_PTR(-ERROR)
 * will be वापसed.
 *
 * If debugfs is not enabled in the kernel, the value -%ENODEV will be
 * वापसed.
 */
काष्ठा dentry *debugfs_create_symlink(स्थिर अक्षर *name, काष्ठा dentry *parent,
				      स्थिर अक्षर *target)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	अक्षर *link = kstrdup(target, GFP_KERNEL);
	अगर (!link)
		वापस ERR_PTR(-ENOMEM);

	dentry = start_creating(name, parent);
	अगर (IS_ERR(dentry)) अणु
		kमुक्त(link);
		वापस dentry;
	पूर्ण

	inode = debugfs_get_inode(dentry->d_sb);
	अगर (unlikely(!inode)) अणु
		pr_err("out of free dentries, can not create symlink '%s'\n",
		       name);
		kमुक्त(link);
		वापस failed_creating(dentry);
	पूर्ण
	inode->i_mode = S_IFLNK | S_IRWXUGO;
	inode->i_op = &debugfs_symlink_inode_operations;
	inode->i_link = link;
	d_instantiate(dentry, inode);
	वापस end_creating(dentry);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_symlink);

अटल व्योम __debugfs_file_हटाओd(काष्ठा dentry *dentry)
अणु
	काष्ठा debugfs_fsdata *fsd;

	/*
	 * Paired with the closing smp_mb() implied by a successful
	 * cmpxchg() in debugfs_file_get(): either
	 * debugfs_file_get() must see a dead dentry or we must see a
	 * debugfs_fsdata instance at ->d_fsdata here (or both).
	 */
	smp_mb();
	fsd = READ_ONCE(dentry->d_fsdata);
	अगर ((अचिन्हित दीर्घ)fsd & DEBUGFS_FSDATA_IS_REAL_FOPS_BIT)
		वापस;
	अगर (!refcount_dec_and_test(&fsd->active_users))
		रुको_क्रम_completion(&fsd->active_users_drained);
पूर्ण

अटल व्योम हटाओ_one(काष्ठा dentry *victim)
अणु
        अगर (d_is_reg(victim))
		__debugfs_file_हटाओd(victim);
	simple_release_fs(&debugfs_mount, &debugfs_mount_count);
पूर्ण

/**
 * debugfs_हटाओ - recursively हटाओs a directory
 * @dentry: a poपूर्णांकer to a the dentry of the directory to be हटाओd.  If this
 *          parameter is शून्य or an error value, nothing will be करोne.
 *
 * This function recursively हटाओs a directory tree in debugfs that
 * was previously created with a call to another debugfs function
 * (like debugfs_create_file() or variants thereof.)
 *
 * This function is required to be called in order क्रम the file to be
 * हटाओd, no स्वतःmatic cleanup of files will happen when a module is
 * हटाओd, you are responsible here.
 */
व्योम debugfs_हटाओ(काष्ठा dentry *dentry)
अणु
	अगर (IS_ERR_OR_शून्य(dentry))
		वापस;

	simple_pin_fs(&debug_fs_type, &debugfs_mount, &debugfs_mount_count);
	simple_recursive_removal(dentry, हटाओ_one);
	simple_release_fs(&debugfs_mount, &debugfs_mount_count);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_हटाओ);

/**
 * debugfs_नाम - नाम a file/directory in the debugfs fileप्रणाली
 * @old_dir: a poपूर्णांकer to the parent dentry क्रम the नामd object. This
 *          should be a directory dentry.
 * @old_dentry: dentry of an object to be नामd.
 * @new_dir: a poपूर्णांकer to the parent dentry where the object should be
 *          moved. This should be a directory dentry.
 * @new_name: a poपूर्णांकer to a string containing the target name.
 *
 * This function नामs a file/directory in debugfs.  The target must not
 * exist क्रम नाम to succeed.
 *
 * This function will वापस a poपूर्णांकer to old_dentry (which is updated to
 * reflect renaming) अगर it succeeds. If an error occurs, %शून्य will be
 * वापसed.
 *
 * If debugfs is not enabled in the kernel, the value -%ENODEV will be
 * वापसed.
 */
काष्ठा dentry *debugfs_नाम(काष्ठा dentry *old_dir, काष्ठा dentry *old_dentry,
		काष्ठा dentry *new_dir, स्थिर अक्षर *new_name)
अणु
	पूर्णांक error;
	काष्ठा dentry *dentry = शून्य, *trap;
	काष्ठा name_snapshot old_name;

	अगर (IS_ERR(old_dir))
		वापस old_dir;
	अगर (IS_ERR(new_dir))
		वापस new_dir;
	अगर (IS_ERR_OR_शून्य(old_dentry))
		वापस old_dentry;

	trap = lock_नाम(new_dir, old_dir);
	/* Source or destination directories करोn't exist? */
	अगर (d_really_is_negative(old_dir) || d_really_is_negative(new_dir))
		जाओ निकास;
	/* Source करोes not exist, cyclic नाम, or mountpoपूर्णांक? */
	अगर (d_really_is_negative(old_dentry) || old_dentry == trap ||
	    d_mountpoपूर्णांक(old_dentry))
		जाओ निकास;
	dentry = lookup_one_len(new_name, new_dir, म_माप(new_name));
	/* Lookup failed, cyclic नाम or target exists? */
	अगर (IS_ERR(dentry) || dentry == trap || d_really_is_positive(dentry))
		जाओ निकास;

	take_dentry_name_snapshot(&old_name, old_dentry);

	error = simple_नाम(&init_user_ns, d_inode(old_dir), old_dentry,
			      d_inode(new_dir), dentry, 0);
	अगर (error) अणु
		release_dentry_name_snapshot(&old_name);
		जाओ निकास;
	पूर्ण
	d_move(old_dentry, dentry);
	fsnotअगरy_move(d_inode(old_dir), d_inode(new_dir), &old_name.name,
		d_is_dir(old_dentry),
		शून्य, old_dentry);
	release_dentry_name_snapshot(&old_name);
	unlock_नाम(new_dir, old_dir);
	dput(dentry);
	वापस old_dentry;
निकास:
	अगर (dentry && !IS_ERR(dentry))
		dput(dentry);
	unlock_नाम(new_dir, old_dir);
	अगर (IS_ERR(dentry))
		वापस dentry;
	वापस ERR_PTR(-EINVAL);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_नाम);

/**
 * debugfs_initialized - Tells whether debugfs has been रेजिस्टरed
 */
bool debugfs_initialized(व्योम)
अणु
	वापस debugfs_रेजिस्टरed;
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_initialized);

अटल पूर्णांक __init debugfs_kernel(अक्षर *str)
अणु
	अगर (str) अणु
		अगर (!म_भेद(str, "on"))
			debugfs_allow = DEBUGFS_ALLOW_API | DEBUGFS_ALLOW_MOUNT;
		अन्यथा अगर (!म_भेद(str, "no-mount"))
			debugfs_allow = DEBUGFS_ALLOW_API;
		अन्यथा अगर (!म_भेद(str, "off"))
			debugfs_allow = 0;
	पूर्ण

	वापस 0;
पूर्ण
early_param("debugfs", debugfs_kernel);
अटल पूर्णांक __init debugfs_init(व्योम)
अणु
	पूर्णांक retval;

	अगर (!(debugfs_allow & DEBUGFS_ALLOW_MOUNT))
		वापस -EPERM;

	retval = sysfs_create_mount_poपूर्णांक(kernel_kobj, "debug");
	अगर (retval)
		वापस retval;

	retval = रेजिस्टर_fileप्रणाली(&debug_fs_type);
	अगर (retval)
		sysfs_हटाओ_mount_poपूर्णांक(kernel_kobj, "debug");
	अन्यथा
		debugfs_रेजिस्टरed = true;

	वापस retval;
पूर्ण
core_initcall(debugfs_init);
