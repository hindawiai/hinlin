<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  inode.c - part of tracefs, a pseuकरो file प्रणाली क्रम activating tracing
 *
 * Based on debugfs by: Greg Kroah-Harपंचांगan <greg@kroah.com>
 *
 *  Copyright (C) 2014 Red Hat Inc, author: Steven Rostedt <srostedt@redhat.com>
 *
 * tracefs is the file प्रणाली that is used by the tracing infraकाष्ठाure.
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/kobject.h>
#समावेश <linux/namei.h>
#समावेश <linux/tracefs.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/security.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/parser.h>
#समावेश <linux/magic.h>
#समावेश <linux/slab.h>

#घोषणा TRACEFS_DEFAULT_MODE	0700

अटल काष्ठा vfsmount *tracefs_mount;
अटल पूर्णांक tracefs_mount_count;
अटल bool tracefs_रेजिस्टरed;

अटल sमाप_प्रकार शेष_पढ़ो_file(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार शेष_ग_लिखो_file(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations tracefs_file_operations = अणु
	.पढ़ो =		शेष_पढ़ो_file,
	.ग_लिखो =	शेष_ग_लिखो_file,
	.खोलो =		simple_खोलो,
	.llseek =	noop_llseek,
पूर्ण;

अटल काष्ठा tracefs_dir_ops अणु
	पूर्णांक (*सूची_गढ़ो)(स्थिर अक्षर *name);
	पूर्णांक (*सूची_हटाओ)(स्थिर अक्षर *name);
पूर्ण tracefs_ops __ro_after_init;

अटल अक्षर *get_dname(काष्ठा dentry *dentry)
अणु
	स्थिर अक्षर *dname;
	अक्षर *name;
	पूर्णांक len = dentry->d_name.len;

	dname = dentry->d_name.name;
	name = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!name)
		वापस शून्य;
	स_नकल(name, dname, len);
	name[len] = 0;
	वापस name;
पूर्ण

अटल पूर्णांक tracefs_syscall_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns,
				 काष्ठा inode *inode, काष्ठा dentry *dentry,
				 umode_t mode)
अणु
	अक्षर *name;
	पूर्णांक ret;

	name = get_dname(dentry);
	अगर (!name)
		वापस -ENOMEM;

	/*
	 * The सूची_गढ़ो call can call the generic functions that create
	 * the files within the tracefs प्रणाली. It is up to the inभागidual
	 * सूची_गढ़ो routine to handle races.
	 */
	inode_unlock(inode);
	ret = tracefs_ops.सूची_गढ़ो(name);
	inode_lock(inode);

	kमुक्त(name);

	वापस ret;
पूर्ण

अटल पूर्णांक tracefs_syscall_सूची_हटाओ(काष्ठा inode *inode, काष्ठा dentry *dentry)
अणु
	अक्षर *name;
	पूर्णांक ret;

	name = get_dname(dentry);
	अगर (!name)
		वापस -ENOMEM;

	/*
	 * The सूची_हटाओ call can call the generic functions that create
	 * the files within the tracefs प्रणाली. It is up to the inभागidual
	 * सूची_हटाओ routine to handle races.
	 * This समय we need to unlock not only the parent (inode) but
	 * also the directory that is being deleted.
	 */
	inode_unlock(inode);
	inode_unlock(dentry->d_inode);

	ret = tracefs_ops.सूची_हटाओ(name);

	inode_lock_nested(inode, I_MUTEX_PARENT);
	inode_lock(dentry->d_inode);

	kमुक्त(name);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा inode_operations tracefs_dir_inode_operations = अणु
	.lookup		= simple_lookup,
	.सूची_गढ़ो		= tracefs_syscall_सूची_गढ़ो,
	.सूची_हटाओ		= tracefs_syscall_सूची_हटाओ,
पूर्ण;

अटल काष्ठा inode *tracefs_get_inode(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode = new_inode(sb);
	अगर (inode) अणु
		inode->i_ino = get_next_ino();
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	पूर्ण
	वापस inode;
पूर्ण

काष्ठा tracefs_mount_opts अणु
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

काष्ठा tracefs_fs_info अणु
	काष्ठा tracefs_mount_opts mount_opts;
पूर्ण;

अटल पूर्णांक tracefs_parse_options(अक्षर *data, काष्ठा tracefs_mount_opts *opts)
अणु
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक option;
	पूर्णांक token;
	kuid_t uid;
	kgid_t gid;
	अक्षर *p;

	opts->mode = TRACEFS_DEFAULT_MODE;

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
		 * but traditionally tracefs has ignored all mount options
		 */
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tracefs_apply_options(काष्ठा super_block *sb)
अणु
	काष्ठा tracefs_fs_info *fsi = sb->s_fs_info;
	काष्ठा inode *inode = sb->s_root->d_inode;
	काष्ठा tracefs_mount_opts *opts = &fsi->mount_opts;

	inode->i_mode &= ~S_IALLUGO;
	inode->i_mode |= opts->mode;

	inode->i_uid = opts->uid;
	inode->i_gid = opts->gid;

	वापस 0;
पूर्ण

अटल पूर्णांक tracefs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	पूर्णांक err;
	काष्ठा tracefs_fs_info *fsi = sb->s_fs_info;

	sync_fileप्रणाली(sb);
	err = tracefs_parse_options(data, &fsi->mount_opts);
	अगर (err)
		जाओ fail;

	tracefs_apply_options(sb);

fail:
	वापस err;
पूर्ण

अटल पूर्णांक tracefs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा tracefs_fs_info *fsi = root->d_sb->s_fs_info;
	काष्ठा tracefs_mount_opts *opts = &fsi->mount_opts;

	अगर (!uid_eq(opts->uid, GLOBAL_ROOT_UID))
		seq_म_लिखो(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, opts->uid));
	अगर (!gid_eq(opts->gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, opts->gid));
	अगर (opts->mode != TRACEFS_DEFAULT_MODE)
		seq_म_लिखो(m, ",mode=%o", opts->mode);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations tracefs_super_operations = अणु
	.statfs		= simple_statfs,
	.remount_fs	= tracefs_remount,
	.show_options	= tracefs_show_options,
पूर्ण;

अटल पूर्णांक trace_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	अटल स्थिर काष्ठा tree_descr trace_files[] = अणुअणु""पूर्णपूर्ण;
	काष्ठा tracefs_fs_info *fsi;
	पूर्णांक err;

	fsi = kzalloc(माप(काष्ठा tracefs_fs_info), GFP_KERNEL);
	sb->s_fs_info = fsi;
	अगर (!fsi) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	err = tracefs_parse_options(data, &fsi->mount_opts);
	अगर (err)
		जाओ fail;

	err  =  simple_fill_super(sb, TRACEFS_MAGIC, trace_files);
	अगर (err)
		जाओ fail;

	sb->s_op = &tracefs_super_operations;

	tracefs_apply_options(sb);

	वापस 0;

fail:
	kमुक्त(fsi);
	sb->s_fs_info = शून्य;
	वापस err;
पूर्ण

अटल काष्ठा dentry *trace_mount(काष्ठा file_प्रणाली_type *fs_type,
			पूर्णांक flags, स्थिर अक्षर *dev_name,
			व्योम *data)
अणु
	वापस mount_single(fs_type, flags, data, trace_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type trace_fs_type = अणु
	.owner =	THIS_MODULE,
	.name =		"tracefs",
	.mount =	trace_mount,
	.समाप्त_sb =	समाप्त_litter_super,
पूर्ण;
MODULE_ALIAS_FS("tracefs");

अटल काष्ठा dentry *start_creating(स्थिर अक्षर *name, काष्ठा dentry *parent)
अणु
	काष्ठा dentry *dentry;
	पूर्णांक error;

	pr_debug("tracefs: creating file '%s'\n",name);

	error = simple_pin_fs(&trace_fs_type, &tracefs_mount,
			      &tracefs_mount_count);
	अगर (error)
		वापस ERR_PTR(error);

	/* If the parent is not specअगरied, we create it in the root.
	 * We need the root dentry to करो this, which is in the super
	 * block. A poपूर्णांकer to that is in the काष्ठा vfsmount that we
	 * have around.
	 */
	अगर (!parent)
		parent = tracefs_mount->mnt_root;

	inode_lock(parent->d_inode);
	अगर (unlikely(IS_DEADसूची(parent->d_inode)))
		dentry = ERR_PTR(-ENOENT);
	अन्यथा
		dentry = lookup_one_len(name, parent, म_माप(name));
	अगर (!IS_ERR(dentry) && dentry->d_inode) अणु
		dput(dentry);
		dentry = ERR_PTR(-EEXIST);
	पूर्ण

	अगर (IS_ERR(dentry)) अणु
		inode_unlock(parent->d_inode);
		simple_release_fs(&tracefs_mount, &tracefs_mount_count);
	पूर्ण

	वापस dentry;
पूर्ण

अटल काष्ठा dentry *failed_creating(काष्ठा dentry *dentry)
अणु
	inode_unlock(dentry->d_parent->d_inode);
	dput(dentry);
	simple_release_fs(&tracefs_mount, &tracefs_mount_count);
	वापस शून्य;
पूर्ण

अटल काष्ठा dentry *end_creating(काष्ठा dentry *dentry)
अणु
	inode_unlock(dentry->d_parent->d_inode);
	वापस dentry;
पूर्ण

/**
 * tracefs_create_file - create a file in the tracefs fileप्रणाली
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is शून्य, then the
 *          file will be created in the root of the tracefs fileप्रणाली.
 * @data: a poपूर्णांकer to something that the caller will want to get to later
 *        on.  The inode.i_निजी poपूर्णांकer will poपूर्णांक to this value on
 *        the खोलो() call.
 * @fops: a poपूर्णांकer to a काष्ठा file_operations that should be used क्रम
 *        this file.
 *
 * This is the basic "create a file" function क्रम tracefs.  It allows क्रम a
 * wide range of flexibility in creating a file, or a directory (अगर you want
 * to create a directory, the tracefs_create_dir() function is
 * recommended to be used instead.)
 *
 * This function will वापस a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the tracefs_हटाओ() function when the file is
 * to be हटाओd (no स्वतःmatic cleanup happens अगर your module is unloaded,
 * you are responsible here.)  If an error occurs, %शून्य will be वापसed.
 *
 * If tracefs is not enabled in the kernel, the value -%ENODEV will be
 * वापसed.
 */
काष्ठा dentry *tracefs_create_file(स्थिर अक्षर *name, umode_t mode,
				   काष्ठा dentry *parent, व्योम *data,
				   स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;

	अगर (security_locked_करोwn(LOCKDOWN_TRACEFS))
		वापस शून्य;

	अगर (!(mode & S_IFMT))
		mode |= S_IFREG;
	BUG_ON(!S_ISREG(mode));
	dentry = start_creating(name, parent);

	अगर (IS_ERR(dentry))
		वापस शून्य;

	inode = tracefs_get_inode(dentry->d_sb);
	अगर (unlikely(!inode))
		वापस failed_creating(dentry);

	inode->i_mode = mode;
	inode->i_fop = fops ? fops : &tracefs_file_operations;
	inode->i_निजी = data;
	d_instantiate(dentry, inode);
	fsnotअगरy_create(dentry->d_parent->d_inode, dentry);
	वापस end_creating(dentry);
पूर्ण

अटल काष्ठा dentry *__create_dir(स्थिर अक्षर *name, काष्ठा dentry *parent,
				   स्थिर काष्ठा inode_operations *ops)
अणु
	काष्ठा dentry *dentry = start_creating(name, parent);
	काष्ठा inode *inode;

	अगर (IS_ERR(dentry))
		वापस शून्य;

	inode = tracefs_get_inode(dentry->d_sb);
	अगर (unlikely(!inode))
		वापस failed_creating(dentry);

	inode->i_mode = S_IFसूची | S_IRWXU | S_IRUGO | S_IXUGO;
	inode->i_op = ops;
	inode->i_fop = &simple_dir_operations;

	/* directory inodes start off with i_nlink == 2 (क्रम "." entry) */
	inc_nlink(inode);
	d_instantiate(dentry, inode);
	inc_nlink(dentry->d_parent->d_inode);
	fsnotअगरy_सूची_गढ़ो(dentry->d_parent->d_inode, dentry);
	वापस end_creating(dentry);
पूर्ण

/**
 * tracefs_create_dir - create a directory in the tracefs fileप्रणाली
 * @name: a poपूर्णांकer to a string containing the name of the directory to
 *        create.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is शून्य, then the
 *          directory will be created in the root of the tracefs fileप्रणाली.
 *
 * This function creates a directory in tracefs with the given name.
 *
 * This function will वापस a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the tracefs_हटाओ() function when the file is
 * to be हटाओd. If an error occurs, %शून्य will be वापसed.
 *
 * If tracing is not enabled in the kernel, the value -%ENODEV will be
 * वापसed.
 */
काष्ठा dentry *tracefs_create_dir(स्थिर अक्षर *name, काष्ठा dentry *parent)
अणु
	वापस __create_dir(name, parent, &simple_dir_inode_operations);
पूर्ण

/**
 * tracefs_create_instance_dir - create the tracing instances directory
 * @name: The name of the instances directory to create
 * @parent: The parent directory that the instances directory will exist
 * @सूची_गढ़ो: The function to call when a सूची_गढ़ो is perक्रमmed.
 * @सूची_हटाओ: The function to call when a सूची_हटाओ is perक्रमmed.
 *
 * Only one instances directory is allowed.
 *
 * The instances directory is special as it allows क्रम सूची_गढ़ो and सूची_हटाओ to
 * to be करोne by userspace. When a सूची_गढ़ो or सूची_हटाओ is perक्रमmed, the inode
 * locks are released and the methods passed in (@सूची_गढ़ो and @सूची_हटाओ) are
 * called without locks and with the name of the directory being created
 * within the instances directory.
 *
 * Returns the dentry of the instances directory.
 */
__init काष्ठा dentry *tracefs_create_instance_dir(स्थिर अक्षर *name,
					  काष्ठा dentry *parent,
					  पूर्णांक (*सूची_गढ़ो)(स्थिर अक्षर *name),
					  पूर्णांक (*सूची_हटाओ)(स्थिर अक्षर *name))
अणु
	काष्ठा dentry *dentry;

	/* Only allow one instance of the instances directory. */
	अगर (WARN_ON(tracefs_ops.सूची_गढ़ो || tracefs_ops.सूची_हटाओ))
		वापस शून्य;

	dentry = __create_dir(name, parent, &tracefs_dir_inode_operations);
	अगर (!dentry)
		वापस शून्य;

	tracefs_ops.सूची_गढ़ो = सूची_गढ़ो;
	tracefs_ops.सूची_हटाओ = सूची_हटाओ;

	वापस dentry;
पूर्ण

अटल व्योम हटाओ_one(काष्ठा dentry *victim)
अणु
	simple_release_fs(&tracefs_mount, &tracefs_mount_count);
पूर्ण

/**
 * tracefs_हटाओ - recursively हटाओs a directory
 * @dentry: a poपूर्णांकer to a the dentry of the directory to be हटाओd.
 *
 * This function recursively हटाओs a directory tree in tracefs that
 * was previously created with a call to another tracefs function
 * (like tracefs_create_file() or variants thereof.)
 */
व्योम tracefs_हटाओ(काष्ठा dentry *dentry)
अणु
	अगर (IS_ERR_OR_शून्य(dentry))
		वापस;

	simple_pin_fs(&trace_fs_type, &tracefs_mount, &tracefs_mount_count);
	simple_recursive_removal(dentry, हटाओ_one);
	simple_release_fs(&tracefs_mount, &tracefs_mount_count);
पूर्ण

/**
 * tracefs_initialized - Tells whether tracefs has been रेजिस्टरed
 */
bool tracefs_initialized(व्योम)
अणु
	वापस tracefs_रेजिस्टरed;
पूर्ण

अटल पूर्णांक __init tracefs_init(व्योम)
अणु
	पूर्णांक retval;

	retval = sysfs_create_mount_poपूर्णांक(kernel_kobj, "tracing");
	अगर (retval)
		वापस -EINVAL;

	retval = रेजिस्टर_fileप्रणाली(&trace_fs_type);
	अगर (!retval)
		tracefs_रेजिस्टरed = true;

	वापस retval;
पूर्ण
core_initcall(tracefs_init);
