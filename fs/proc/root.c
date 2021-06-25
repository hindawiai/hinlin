<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/proc/root.c
 *
 *  Copyright (C) 1991, 1992 Linus Torvalds
 *
 *  proc root directory handling functions
 */

#समावेश <linux/uaccess.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/mount.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/cred.h>
#समावेश <linux/magic.h>
#समावेश <linux/slab.h>

#समावेश "internal.h"

काष्ठा proc_fs_context अणु
	काष्ठा pid_namespace	*pid_ns;
	अचिन्हित पूर्णांक		mask;
	क्रमागत proc_hidepid	hidepid;
	पूर्णांक			gid;
	क्रमागत proc_piकरोnly	piकरोnly;
पूर्ण;

क्रमागत proc_param अणु
	Opt_gid,
	Opt_hidepid,
	Opt_subset,
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec proc_fs_parameters[] = अणु
	fsparam_u32("gid",	Opt_gid),
	fsparam_string("hidepid",	Opt_hidepid),
	fsparam_string("subset",	Opt_subset),
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत पूर्णांक valid_hidepid(अचिन्हित पूर्णांक value)
अणु
	वापस (value == HIDEPID_OFF ||
		value == HIDEPID_NO_ACCESS ||
		value == HIDEPID_INVISIBLE ||
		value == HIDEPID_NOT_PTRACEABLE);
पूर्ण

अटल पूर्णांक proc_parse_hidepid_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा proc_fs_context *ctx = fc->fs_निजी;
	काष्ठा fs_parameter_spec hidepid_u32_spec = fsparam_u32("hidepid", Opt_hidepid);
	काष्ठा fs_parse_result result;
	पूर्णांक base = (अचिन्हित दीर्घ)hidepid_u32_spec.data;

	अगर (param->type != fs_value_is_string)
		वापस invalf(fc, "proc: unexpected type of hidepid value\n");

	अगर (!kstrtouपूर्णांक(param->string, base, &result.uपूर्णांक_32)) अणु
		अगर (!valid_hidepid(result.uपूर्णांक_32))
			वापस invalf(fc, "proc: unknown value of hidepid - %s\n", param->string);
		ctx->hidepid = result.uपूर्णांक_32;
		वापस 0;
	पूर्ण

	अगर (!म_भेद(param->string, "off"))
		ctx->hidepid = HIDEPID_OFF;
	अन्यथा अगर (!म_भेद(param->string, "noaccess"))
		ctx->hidepid = HIDEPID_NO_ACCESS;
	अन्यथा अगर (!म_भेद(param->string, "invisible"))
		ctx->hidepid = HIDEPID_INVISIBLE;
	अन्यथा अगर (!म_भेद(param->string, "ptraceable"))
		ctx->hidepid = HIDEPID_NOT_PTRACEABLE;
	अन्यथा
		वापस invalf(fc, "proc: unknown value of hidepid - %s\n", param->string);

	वापस 0;
पूर्ण

अटल पूर्णांक proc_parse_subset_param(काष्ठा fs_context *fc, अक्षर *value)
अणु
	काष्ठा proc_fs_context *ctx = fc->fs_निजी;

	जबतक (value) अणु
		अक्षर *ptr = म_अक्षर(value, ',');

		अगर (ptr != शून्य)
			*ptr++ = '\0';

		अगर (*value != '\0') अणु
			अगर (!म_भेद(value, "pid")) अणु
				ctx->piकरोnly = PROC_PIDONLY_ON;
			पूर्ण अन्यथा अणु
				वापस invalf(fc, "proc: unsupported subset option - %s\n", value);
			पूर्ण
		पूर्ण
		value = ptr;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक proc_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा proc_fs_context *ctx = fc->fs_निजी;
	काष्ठा fs_parse_result result;
	पूर्णांक opt;

	opt = fs_parse(fc, proc_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_gid:
		ctx->gid = result.uपूर्णांक_32;
		अवरोध;

	हाल Opt_hidepid:
		अगर (proc_parse_hidepid_param(fc, param))
			वापस -EINVAL;
		अवरोध;

	हाल Opt_subset:
		अगर (proc_parse_subset_param(fc, param->string) < 0)
			वापस -EINVAL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ctx->mask |= 1 << opt;
	वापस 0;
पूर्ण

अटल व्योम proc_apply_options(काष्ठा proc_fs_info *fs_info,
			       काष्ठा fs_context *fc,
			       काष्ठा user_namespace *user_ns)
अणु
	काष्ठा proc_fs_context *ctx = fc->fs_निजी;

	अगर (ctx->mask & (1 << Opt_gid))
		fs_info->pid_gid = make_kgid(user_ns, ctx->gid);
	अगर (ctx->mask & (1 << Opt_hidepid))
		fs_info->hide_pid = ctx->hidepid;
	अगर (ctx->mask & (1 << Opt_subset))
		fs_info->piकरोnly = ctx->piकरोnly;
पूर्ण

अटल पूर्णांक proc_fill_super(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	काष्ठा proc_fs_context *ctx = fc->fs_निजी;
	काष्ठा inode *root_inode;
	काष्ठा proc_fs_info *fs_info;
	पूर्णांक ret;

	fs_info = kzalloc(माप(*fs_info), GFP_KERNEL);
	अगर (!fs_info)
		वापस -ENOMEM;

	fs_info->pid_ns = get_pid_ns(ctx->pid_ns);
	proc_apply_options(fs_info, fc, current_user_ns());

	/* User space would अवरोध अगर executables or devices appear on proc */
	s->s_अगरlags |= SB_I_USERNS_VISIBLE | SB_I_NOEXEC | SB_I_NODEV;
	s->s_flags |= SB_NOसूचीATIME | SB_NOSUID | SB_NOEXEC;
	s->s_blocksize = 1024;
	s->s_blocksize_bits = 10;
	s->s_magic = PROC_SUPER_MAGIC;
	s->s_op = &proc_sops;
	s->s_समय_gran = 1;
	s->s_fs_info = fs_info;

	/*
	 * procfs isn't actually a stacking fileप्रणाली; however, there is
	 * too much magic going on inside it to permit stacking things on
	 * top of it
	 */
	s->s_stack_depth = खाताSYSTEM_MAX_STACK_DEPTH;

	/* procfs dentries and inodes करोn't require IO to create */
	s->s_shrink.seeks = 0;

	pde_get(&proc_root);
	root_inode = proc_get_inode(s, &proc_root);
	अगर (!root_inode) अणु
		pr_err("proc_fill_super: get root inode failed\n");
		वापस -ENOMEM;
	पूर्ण

	s->s_root = d_make_root(root_inode);
	अगर (!s->s_root) अणु
		pr_err("proc_fill_super: allocate dentry failed\n");
		वापस -ENOMEM;
	पूर्ण

	ret = proc_setup_self(s);
	अगर (ret) अणु
		वापस ret;
	पूर्ण
	वापस proc_setup_thपढ़ो_self(s);
पूर्ण

अटल पूर्णांक proc_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा super_block *sb = fc->root->d_sb;
	काष्ठा proc_fs_info *fs_info = proc_sb_info(sb);

	sync_fileप्रणाली(sb);

	proc_apply_options(fs_info, fc, current_user_ns());
	वापस 0;
पूर्ण

अटल पूर्णांक proc_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_nodev(fc, proc_fill_super);
पूर्ण

अटल व्योम proc_fs_context_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा proc_fs_context *ctx = fc->fs_निजी;

	put_pid_ns(ctx->pid_ns);
	kमुक्त(ctx);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations proc_fs_context_ops = अणु
	.मुक्त		= proc_fs_context_मुक्त,
	.parse_param	= proc_parse_param,
	.get_tree	= proc_get_tree,
	.reconfigure	= proc_reconfigure,
पूर्ण;

अटल पूर्णांक proc_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा proc_fs_context *ctx;

	ctx = kzalloc(माप(काष्ठा proc_fs_context), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->pid_ns = get_pid_ns(task_active_pid_ns(current));
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(ctx->pid_ns->user_ns);
	fc->fs_निजी = ctx;
	fc->ops = &proc_fs_context_ops;
	वापस 0;
पूर्ण

अटल व्योम proc_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा proc_fs_info *fs_info = proc_sb_info(sb);

	अगर (!fs_info) अणु
		समाप्त_anon_super(sb);
		वापस;
	पूर्ण

	dput(fs_info->proc_self);
	dput(fs_info->proc_thपढ़ो_self);

	समाप्त_anon_super(sb);
	put_pid_ns(fs_info->pid_ns);
	kमुक्त(fs_info);
पूर्ण

अटल काष्ठा file_प्रणाली_type proc_fs_type = अणु
	.name			= "proc",
	.init_fs_context	= proc_init_fs_context,
	.parameters		= proc_fs_parameters,
	.समाप्त_sb		= proc_समाप्त_sb,
	.fs_flags		= FS_USERNS_MOUNT | FS_DISALLOW_NOTIFY_PERM,
पूर्ण;

व्योम __init proc_root_init(व्योम)
अणु
	proc_init_kmemcache();
	set_proc_pid_nlink();
	proc_self_init();
	proc_thपढ़ो_self_init();
	proc_symlink("mounts", शून्य, "self/mounts");

	proc_net_init();
	proc_सूची_गढ़ो("fs", शून्य);
	proc_सूची_गढ़ो("driver", शून्य);
	proc_create_mount_poपूर्णांक("fs/nfsd"); /* somewhere क्रम the nfsd fileप्रणाली to be mounted */
#अगर defined(CONFIG_SUN_OPENPROMFS) || defined(CONFIG_SUN_OPENPROMFS_MODULE)
	/* just give it a mountpoपूर्णांक */
	proc_create_mount_poपूर्णांक("openprom");
#पूर्ण_अगर
	proc_tty_init();
	proc_सूची_गढ़ो("bus", शून्य);
	proc_sys_init();

	रेजिस्टर_fileप्रणाली(&proc_fs_type);
पूर्ण

अटल पूर्णांक proc_root_getattr(काष्ठा user_namespace *mnt_userns,
			     स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			     u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	generic_fillattr(&init_user_ns, d_inode(path->dentry), stat);
	stat->nlink = proc_root.nlink + nr_processes();
	वापस 0;
पूर्ण

अटल काष्ठा dentry *proc_root_lookup(काष्ठा inode * dir, काष्ठा dentry * dentry, अचिन्हित पूर्णांक flags)
अणु
	अगर (!proc_pid_lookup(dentry, flags))
		वापस शून्य;

	वापस proc_lookup(dir, dentry, flags);
पूर्ण

अटल पूर्णांक proc_root_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	अगर (ctx->pos < FIRST_PROCESS_ENTRY) अणु
		पूर्णांक error = proc_सूची_पढ़ो(file, ctx);
		अगर (unlikely(error <= 0))
			वापस error;
		ctx->pos = FIRST_PROCESS_ENTRY;
	पूर्ण

	वापस proc_pid_सूची_पढ़ो(file, ctx);
पूर्ण

/*
 * The root /proc directory is special, as it has the
 * <pid> directories. Thus we करोn't use the generic
 * directory handling functions क्रम that..
 */
अटल स्थिर काष्ठा file_operations proc_root_operations = अणु
	.पढ़ो		 = generic_पढ़ो_dir,
	.iterate_shared	 = proc_root_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

/*
 * proc root can करो almost nothing..
 */
अटल स्थिर काष्ठा inode_operations proc_root_inode_operations = अणु
	.lookup		= proc_root_lookup,
	.getattr	= proc_root_getattr,
पूर्ण;

/*
 * This is the root "inode" in the /proc tree..
 */
काष्ठा proc_dir_entry proc_root = अणु
	.low_ino	= PROC_ROOT_INO, 
	.namelen	= 5, 
	.mode		= S_IFसूची | S_IRUGO | S_IXUGO, 
	.nlink		= 2, 
	.refcnt		= REFCOUNT_INIT(1),
	.proc_iops	= &proc_root_inode_operations, 
	.proc_dir_ops	= &proc_root_operations,
	.parent		= &proc_root,
	.subdir		= RB_ROOT,
	.name		= "/proc",
पूर्ण;
