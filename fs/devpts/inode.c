<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- --------------------------------------------------------- *
 *
 * linux/fs/devpts/inode.c
 *
 *  Copyright 1998-2004 H. Peter Anvin -- All Rights Reserved
 *
 * ------------------------------------------------------------------------- */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>
#समावेश <linux/mount.h>
#समावेश <linux/tty.h>
#समावेश <linux/mutex.h>
#समावेश <linux/magic.h>
#समावेश <linux/idr.h>
#समावेश <linux/devpts_fs.h>
#समावेश <linux/parser.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/seq_file.h>

#घोषणा DEVPTS_DEFAULT_MODE 0600
/*
 * pपंचांगx is a new node in /dev/pts and will be unused in legacy (single-
 * instance) mode. To prevent surprises in user space, set permissions of
 * pपंचांगx to 0. Use 'chmod' or remount with '-o ptmxmode' to set meaningful
 * permissions.
 */
#घोषणा DEVPTS_DEFAULT_PTMX_MODE 0000
#घोषणा PTMX_MINOR	2

/*
 * sysctl support क्रम setting limits on the number of Unix98 ptys allocated.
 * Otherwise one can eat up all kernel memory by खोलोing /dev/pपंचांगx repeatedly.
 */
अटल पूर्णांक pty_limit = NR_UNIX98_PTY_DEFAULT;
अटल पूर्णांक pty_reserve = NR_UNIX98_PTY_RESERVE;
अटल पूर्णांक pty_limit_min;
अटल पूर्णांक pty_limit_max = पूर्णांक_उच्च;
अटल atomic_t pty_count = ATOMIC_INIT(0);

अटल काष्ठा ctl_table pty_table[] = अणु
	अणु
		.procname	= "max",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.data		= &pty_limit,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &pty_limit_min,
		.extra2		= &pty_limit_max,
	पूर्ण, अणु
		.procname	= "reserve",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.data		= &pty_reserve,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &pty_limit_min,
		.extra2		= &pty_limit_max,
	पूर्ण, अणु
		.procname	= "nr",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0444,
		.data		= &pty_count,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table pty_kern_table[] = अणु
	अणु
		.procname	= "pty",
		.mode		= 0555,
		.child		= pty_table,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table pty_root_table[] = अणु
	अणु
		.procname	= "kernel",
		.mode		= 0555,
		.child		= pty_kern_table,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा pts_mount_opts अणु
	पूर्णांक setuid;
	पूर्णांक setgid;
	kuid_t   uid;
	kgid_t   gid;
	umode_t mode;
	umode_t pपंचांगxmode;
	पूर्णांक reserve;
	पूर्णांक max;
पूर्ण;

क्रमागत अणु
	Opt_uid, Opt_gid, Opt_mode, Opt_pपंचांगxmode, Opt_newinstance,  Opt_max,
	Opt_err
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_uid, "uid=%u"पूर्ण,
	अणुOpt_gid, "gid=%u"पूर्ण,
	अणुOpt_mode, "mode=%o"पूर्ण,
	अणुOpt_pपंचांगxmode, "ptmxmode=%o"पूर्ण,
	अणुOpt_newinstance, "newinstance"पूर्ण,
	अणुOpt_max, "max=%d"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

काष्ठा pts_fs_info अणु
	काष्ठा ida allocated_ptys;
	काष्ठा pts_mount_opts mount_opts;
	काष्ठा super_block *sb;
	काष्ठा dentry *pपंचांगx_dentry;
पूर्ण;

अटल अंतरभूत काष्ठा pts_fs_info *DEVPTS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल पूर्णांक devpts_pपंचांगx_path(काष्ठा path *path)
अणु
	काष्ठा super_block *sb;
	पूर्णांक err;

	/* Is a devpts fileप्रणाली at "pts" in the same directory? */
	err = path_pts(path);
	अगर (err)
		वापस err;

	/* Is the path the root of a devpts fileप्रणाली? */
	sb = path->mnt->mnt_sb;
	अगर ((sb->s_magic != DEVPTS_SUPER_MAGIC) ||
	    (path->mnt->mnt_root != sb->s_root))
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * Try to find a suitable devpts fileप्रणाली. We support the following
 * scenarios:
 * - The pपंचांगx device node is located in the same directory as the devpts
 *   mount where the pts device nodes are located.
 *   This is e.g. the हाल when calling खोलो on the /dev/pts/pपंचांगx device
 *   node when the devpts fileप्रणाली is mounted at /dev/pts.
 * - The pपंचांगx device node is located outside the devpts fileप्रणाली mount
 *   where the pts device nodes are located. For example, the pपंचांगx device
 *   is a symlink, separate device node, or bind-mount.
 *   A supported scenario is bind-mounting /dev/pts/pपंचांगx to /dev/pपंचांगx and
 *   then calling खोलो on /dev/pपंचांगx. In this हाल a suitable pts
 *   subdirectory can be found in the common parent directory /dev of the
 *   devpts mount and the pपंचांगx bind-mount, after resolving the /dev/pपंचांगx
 *   bind-mount.
 *   If no suitable pts subdirectory can be found this function will fail.
 *   This is e.g. the हाल when bind-mounting /dev/pts/pपंचांगx to /pपंचांगx.
 */
काष्ठा vfsmount *devpts_mntget(काष्ठा file *filp, काष्ठा pts_fs_info *fsi)
अणु
	काष्ठा path path;
	पूर्णांक err = 0;

	path = filp->f_path;
	path_get(&path);

	/* Walk upward जबतक the start poपूर्णांक is a bind mount of
	 * a single file.
	 */
	जबतक (path.mnt->mnt_root == path.dentry)
		अगर (follow_up(&path) == 0)
			अवरोध;

	/* devpts_pपंचांगx_path() finds a devpts fs or वापसs an error. */
	अगर ((path.mnt->mnt_sb->s_magic != DEVPTS_SUPER_MAGIC) ||
	    (DEVPTS_SB(path.mnt->mnt_sb) != fsi))
		err = devpts_pपंचांगx_path(&path);
	dput(path.dentry);
	अगर (!err) अणु
		अगर (DEVPTS_SB(path.mnt->mnt_sb) == fsi)
			वापस path.mnt;

		err = -ENODEV;
	पूर्ण

	mntput(path.mnt);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा pts_fs_info *devpts_acquire(काष्ठा file *filp)
अणु
	काष्ठा pts_fs_info *result;
	काष्ठा path path;
	काष्ठा super_block *sb;

	path = filp->f_path;
	path_get(&path);

	/* Has the devpts fileप्रणाली alपढ़ोy been found? */
	अगर (path.mnt->mnt_sb->s_magic != DEVPTS_SUPER_MAGIC) अणु
		पूर्णांक err;

		err = devpts_pपंचांगx_path(&path);
		अगर (err) अणु
			result = ERR_PTR(err);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * pty code needs to hold extra references in हाल of last /dev/tty बंद
	 */
	sb = path.mnt->mnt_sb;
	atomic_inc(&sb->s_active);
	result = DEVPTS_SB(sb);

out:
	path_put(&path);
	वापस result;
पूर्ण

व्योम devpts_release(काष्ठा pts_fs_info *fsi)
अणु
	deactivate_super(fsi->sb);
पूर्ण

#घोषणा PARSE_MOUNT	0
#घोषणा PARSE_REMOUNT	1

/*
 * parse_mount_options():
 *	Set @opts to mount options specअगरied in @data. If an option is not
 *	specअगरied in @data, set it to its शेष value.
 *
 * Note: @data may be शून्य (in which हाल all options are set to शेष).
 */
अटल पूर्णांक parse_mount_options(अक्षर *data, पूर्णांक op, काष्ठा pts_mount_opts *opts)
अणु
	अक्षर *p;
	kuid_t uid;
	kgid_t gid;

	opts->setuid  = 0;
	opts->setgid  = 0;
	opts->uid     = GLOBAL_ROOT_UID;
	opts->gid     = GLOBAL_ROOT_GID;
	opts->mode    = DEVPTS_DEFAULT_MODE;
	opts->pपंचांगxmode = DEVPTS_DEFAULT_PTMX_MODE;
	opts->max     = NR_UNIX98_PTY_MAX;

	/* Only allow instances mounted from the initial mount
	 * namespace to tap the reserve pool of ptys.
	 */
	अगर (op == PARSE_MOUNT)
		opts->reserve =
			(current->nsproxy->mnt_ns == init_task.nsproxy->mnt_ns);

	जबतक ((p = strsep(&data, ",")) != शून्य) अणु
		substring_t args[MAX_OPT_ARGS];
		पूर्णांक token;
		पूर्णांक option;

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
			opts->setuid = 1;
			अवरोध;
		हाल Opt_gid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस -EINVAL;
			gid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(gid))
				वापस -EINVAL;
			opts->gid = gid;
			opts->setgid = 1;
			अवरोध;
		हाल Opt_mode:
			अगर (match_octal(&args[0], &option))
				वापस -EINVAL;
			opts->mode = option & S_IALLUGO;
			अवरोध;
		हाल Opt_pपंचांगxmode:
			अगर (match_octal(&args[0], &option))
				वापस -EINVAL;
			opts->pपंचांगxmode = option & S_IALLUGO;
			अवरोध;
		हाल Opt_newinstance:
			अवरोध;
		हाल Opt_max:
			अगर (match_पूर्णांक(&args[0], &option) ||
			    option < 0 || option > NR_UNIX98_PTY_MAX)
				वापस -EINVAL;
			opts->max = option;
			अवरोध;
		शेष:
			pr_err("called with bogus options\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mknod_pपंचांगx(काष्ठा super_block *sb)
अणु
	पूर्णांक mode;
	पूर्णांक rc = -ENOMEM;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	काष्ठा dentry *root = sb->s_root;
	काष्ठा pts_fs_info *fsi = DEVPTS_SB(sb);
	काष्ठा pts_mount_opts *opts = &fsi->mount_opts;
	kuid_t pपंचांगx_uid = current_fsuid();
	kgid_t pपंचांगx_gid = current_fsgid();

	inode_lock(d_inode(root));

	/* If we have alपढ़ोy created pपंचांगx node, वापस */
	अगर (fsi->pपंचांगx_dentry) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	dentry = d_alloc_name(root, "ptmx");
	अगर (!dentry) अणु
		pr_err("Unable to alloc dentry for ptmx node\n");
		जाओ out;
	पूर्ण

	/*
	 * Create a new 'ptmx' node in this mount of devpts.
	 */
	inode = new_inode(sb);
	अगर (!inode) अणु
		pr_err("Unable to alloc inode for ptmx node\n");
		dput(dentry);
		जाओ out;
	पूर्ण

	inode->i_ino = 2;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);

	mode = S_IFCHR|opts->pपंचांगxmode;
	init_special_inode(inode, mode, MKDEV(TTYAUX_MAJOR, 2));
	inode->i_uid = pपंचांगx_uid;
	inode->i_gid = pपंचांगx_gid;

	d_add(dentry, inode);

	fsi->pपंचांगx_dentry = dentry;
	rc = 0;
out:
	inode_unlock(d_inode(root));
	वापस rc;
पूर्ण

अटल व्योम update_pपंचांगx_mode(काष्ठा pts_fs_info *fsi)
अणु
	काष्ठा inode *inode;
	अगर (fsi->pपंचांगx_dentry) अणु
		inode = d_inode(fsi->pपंचांगx_dentry);
		inode->i_mode = S_IFCHR|fsi->mount_opts.pपंचांगxmode;
	पूर्ण
पूर्ण

अटल पूर्णांक devpts_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	पूर्णांक err;
	काष्ठा pts_fs_info *fsi = DEVPTS_SB(sb);
	काष्ठा pts_mount_opts *opts = &fsi->mount_opts;

	err = parse_mount_options(data, PARSE_REMOUNT, opts);

	/*
	 * parse_mount_options() restores options to शेष values
	 * beक्रमe parsing and may have changed pपंचांगxmode. So, update the
	 * mode in the inode too. Bogus options करोn't fail the remount,
	 * so करो this even on error वापस.
	 */
	update_pपंचांगx_mode(fsi);

	वापस err;
पूर्ण

अटल पूर्णांक devpts_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा pts_fs_info *fsi = DEVPTS_SB(root->d_sb);
	काष्ठा pts_mount_opts *opts = &fsi->mount_opts;

	अगर (opts->setuid)
		seq_म_लिखो(seq, ",uid=%u",
			   from_kuid_munged(&init_user_ns, opts->uid));
	अगर (opts->setgid)
		seq_म_लिखो(seq, ",gid=%u",
			   from_kgid_munged(&init_user_ns, opts->gid));
	seq_म_लिखो(seq, ",mode=%03o", opts->mode);
	seq_म_लिखो(seq, ",ptmxmode=%03o", opts->pपंचांगxmode);
	अगर (opts->max < NR_UNIX98_PTY_MAX)
		seq_म_लिखो(seq, ",max=%d", opts->max);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations devpts_sops = अणु
	.statfs		= simple_statfs,
	.remount_fs	= devpts_remount,
	.show_options	= devpts_show_options,
पूर्ण;

अटल व्योम *new_pts_fs_info(काष्ठा super_block *sb)
अणु
	काष्ठा pts_fs_info *fsi;

	fsi = kzalloc(माप(काष्ठा pts_fs_info), GFP_KERNEL);
	अगर (!fsi)
		वापस शून्य;

	ida_init(&fsi->allocated_ptys);
	fsi->mount_opts.mode = DEVPTS_DEFAULT_MODE;
	fsi->mount_opts.pपंचांगxmode = DEVPTS_DEFAULT_PTMX_MODE;
	fsi->sb = sb;

	वापस fsi;
पूर्ण

अटल पूर्णांक
devpts_fill_super(काष्ठा super_block *s, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा inode *inode;
	पूर्णांक error;

	s->s_अगरlags &= ~SB_I_NODEV;
	s->s_blocksize = 1024;
	s->s_blocksize_bits = 10;
	s->s_magic = DEVPTS_SUPER_MAGIC;
	s->s_op = &devpts_sops;
	s->s_d_op = &simple_dentry_operations;
	s->s_समय_gran = 1;

	error = -ENOMEM;
	s->s_fs_info = new_pts_fs_info(s);
	अगर (!s->s_fs_info)
		जाओ fail;

	error = parse_mount_options(data, PARSE_MOUNT, &DEVPTS_SB(s)->mount_opts);
	अगर (error)
		जाओ fail;

	error = -ENOMEM;
	inode = new_inode(s);
	अगर (!inode)
		जाओ fail;
	inode->i_ino = 1;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	inode->i_mode = S_IFसूची | S_IRUGO | S_IXUGO | S_IWUSR;
	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	set_nlink(inode, 2);

	s->s_root = d_make_root(inode);
	अगर (!s->s_root) अणु
		pr_err("get root dentry failed\n");
		जाओ fail;
	पूर्ण

	error = mknod_pपंचांगx(s);
	अगर (error)
		जाओ fail_dput;

	वापस 0;
fail_dput:
	dput(s->s_root);
	s->s_root = शून्य;
fail:
	वापस error;
पूर्ण

/*
 * devpts_mount()
 *
 *     Mount a new (निजी) instance of devpts.  PTYs created in this
 *     instance are independent of the PTYs in other devpts instances.
 */
अटल काष्ठा dentry *devpts_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_nodev(fs_type, flags, data, devpts_fill_super);
पूर्ण

अटल व्योम devpts_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा pts_fs_info *fsi = DEVPTS_SB(sb);

	अगर (fsi)
		ida_destroy(&fsi->allocated_ptys);
	kमुक्त(fsi);
	समाप्त_litter_super(sb);
पूर्ण

अटल काष्ठा file_प्रणाली_type devpts_fs_type = अणु
	.name		= "devpts",
	.mount		= devpts_mount,
	.समाप्त_sb	= devpts_समाप्त_sb,
	.fs_flags	= FS_USERNS_MOUNT,
पूर्ण;

/*
 * The normal naming convention is simply /dev/pts/<number>; this conक्रमms
 * to the System V naming convention
 */

पूर्णांक devpts_new_index(काष्ठा pts_fs_info *fsi)
अणु
	पूर्णांक index = -ENOSPC;

	अगर (atomic_inc_वापस(&pty_count) >= (pty_limit -
			  (fsi->mount_opts.reserve ? 0 : pty_reserve)))
		जाओ out;

	index = ida_alloc_max(&fsi->allocated_ptys, fsi->mount_opts.max - 1,
			GFP_KERNEL);

out:
	अगर (index < 0)
		atomic_dec(&pty_count);
	वापस index;
पूर्ण

व्योम devpts_समाप्त_index(काष्ठा pts_fs_info *fsi, पूर्णांक idx)
अणु
	ida_मुक्त(&fsi->allocated_ptys, idx);
	atomic_dec(&pty_count);
पूर्ण

/**
 * devpts_pty_new -- create a new inode in /dev/pts/
 * @pपंचांगx_inode: inode of the master
 * @device: major+minor of the node to be created
 * @index: used as a name of the node
 * @priv: what's given back by devpts_get_priv
 *
 * The created inode is वापसed. Remove it from /dev/pts/ by devpts_pty_समाप्त.
 */
काष्ठा dentry *devpts_pty_new(काष्ठा pts_fs_info *fsi, पूर्णांक index, व्योम *priv)
अणु
	काष्ठा dentry *dentry;
	काष्ठा super_block *sb = fsi->sb;
	काष्ठा inode *inode;
	काष्ठा dentry *root;
	काष्ठा pts_mount_opts *opts;
	अक्षर s[12];

	root = sb->s_root;
	opts = &fsi->mount_opts;

	inode = new_inode(sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	inode->i_ino = index + 3;
	inode->i_uid = opts->setuid ? opts->uid : current_fsuid();
	inode->i_gid = opts->setgid ? opts->gid : current_fsgid();
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	init_special_inode(inode, S_IFCHR|opts->mode, MKDEV(UNIX98_PTY_SLAVE_MAJOR, index));

	प्र_लिखो(s, "%d", index);

	dentry = d_alloc_name(root, s);
	अगर (dentry) अणु
		dentry->d_fsdata = priv;
		d_add(dentry, inode);
		fsnotअगरy_create(d_inode(root), dentry);
	पूर्ण अन्यथा अणु
		iput(inode);
		dentry = ERR_PTR(-ENOMEM);
	पूर्ण

	वापस dentry;
पूर्ण

/**
 * devpts_get_priv -- get निजी data क्रम a slave
 * @pts_inode: inode of the slave
 *
 * Returns whatever was passed as priv in devpts_pty_new क्रम a given inode.
 */
व्योम *devpts_get_priv(काष्ठा dentry *dentry)
अणु
	अगर (dentry->d_sb->s_magic != DEVPTS_SUPER_MAGIC)
		वापस शून्य;
	वापस dentry->d_fsdata;
पूर्ण

/**
 * devpts_pty_समाप्त -- हटाओ inode क्रमm /dev/pts/
 * @inode: inode of the slave to be हटाओd
 *
 * This is an inverse operation of devpts_pty_new.
 */
व्योम devpts_pty_समाप्त(काष्ठा dentry *dentry)
अणु
	WARN_ON_ONCE(dentry->d_sb->s_magic != DEVPTS_SUPER_MAGIC);

	dentry->d_fsdata = शून्य;
	drop_nlink(dentry->d_inode);
	fsnotअगरy_unlink(d_inode(dentry->d_parent), dentry);
	d_drop(dentry);
	dput(dentry);	/* d_alloc_name() in devpts_pty_new() */
पूर्ण

अटल पूर्णांक __init init_devpts_fs(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_fileप्रणाली(&devpts_fs_type);
	अगर (!err) अणु
		रेजिस्टर_sysctl_table(pty_root_table);
	पूर्ण
	वापस err;
पूर्ण
module_init(init_devpts_fs)
