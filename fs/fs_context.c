<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Provide a way to create a superblock configuration context within the kernel
 * that allows a superblock to be set up prior to mounting.
 *
 * Copyright (C) 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/slab.h>
#समावेश <linux/magic.h>
#समावेश <linux/security.h>
#समावेश <linux/mnt_namespace.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/user_namespace.h>
#समावेश <net/net_namespace.h>
#समावेश <यंत्र/sections.h>
#समावेश "mount.h"
#समावेश "internal.h"

क्रमागत legacy_fs_param अणु
	LEGACY_FS_UNSET_PARAMS,
	LEGACY_FS_MONOLITHIC_PARAMS,
	LEGACY_FS_INDIVIDUAL_PARAMS,
पूर्ण;

काष्ठा legacy_fs_context अणु
	अक्षर			*legacy_data;	/* Data page क्रम legacy fileप्रणालीs */
	माप_प्रकार			data_size;
	क्रमागत legacy_fs_param	param_type;
पूर्ण;

अटल पूर्णांक legacy_init_fs_context(काष्ठा fs_context *fc);

अटल स्थिर काष्ठा स्थिरant_table common_set_sb_flag[] = अणु
	अणु "dirsync",	SB_सूचीSYNC पूर्ण,
	अणु "lazytime",	SB_LAZYTIME पूर्ण,
	अणु "mand",	SB_MANDLOCK पूर्ण,
	अणु "ro",		SB_RDONLY पूर्ण,
	अणु "sync",	SB_SYNCHRONOUS पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table common_clear_sb_flag[] = अणु
	अणु "async",	SB_SYNCHRONOUS पूर्ण,
	अणु "nolazytime",	SB_LAZYTIME पूर्ण,
	अणु "nomand",	SB_MANDLOCK पूर्ण,
	अणु "rw",		SB_RDONLY पूर्ण,
	अणु पूर्ण,
पूर्ण;

/*
 * Check क्रम a common mount option that manipulates s_flags.
 */
अटल पूर्णांक vfs_parse_sb_flag(काष्ठा fs_context *fc, स्थिर अक्षर *key)
अणु
	अचिन्हित पूर्णांक token;

	token = lookup_स्थिरant(common_set_sb_flag, key, 0);
	अगर (token) अणु
		fc->sb_flags |= token;
		fc->sb_flags_mask |= token;
		वापस 0;
	पूर्ण

	token = lookup_स्थिरant(common_clear_sb_flag, key, 0);
	अगर (token) अणु
		fc->sb_flags &= ~token;
		fc->sb_flags_mask |= token;
		वापस 0;
	पूर्ण

	वापस -ENOPARAM;
पूर्ण

/**
 * vfs_parse_fs_param - Add a single parameter to a superblock config
 * @fc: The fileप्रणाली context to modअगरy
 * @param: The parameter
 *
 * A single mount option in string क्रमm is applied to the fileप्रणाली context
 * being set up.  Certain standard options (क्रम example "ro") are translated
 * पूर्णांकo flag bits without going to the fileप्रणाली.  The active security module
 * is allowed to observe and poach options.  Any other options are passed over
 * to the fileप्रणाली to parse.
 *
 * This may be called multiple बार क्रम a context.
 *
 * Returns 0 on success and a negative error code on failure.  In the event of
 * failure, supplementary error inक्रमmation may have been set.
 */
पूर्णांक vfs_parse_fs_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	पूर्णांक ret;

	अगर (!param->key)
		वापस invalf(fc, "Unnamed parameter\n");

	ret = vfs_parse_sb_flag(fc, param->key);
	अगर (ret != -ENOPARAM)
		वापस ret;

	ret = security_fs_context_parse_param(fc, param);
	अगर (ret != -ENOPARAM)
		/* Param beदीर्घs to the LSM or is disallowed by the LSM; so
		 * करोn't pass to the FS.
		 */
		वापस ret;

	अगर (fc->ops->parse_param) अणु
		ret = fc->ops->parse_param(fc, param);
		अगर (ret != -ENOPARAM)
			वापस ret;
	पूर्ण

	/* If the fileप्रणाली करोesn't take any arguments, give it the
	 * शेष handling of source.
	 */
	अगर (म_भेद(param->key, "source") == 0) अणु
		अगर (param->type != fs_value_is_string)
			वापस invalf(fc, "VFS: Non-string source");
		अगर (fc->source)
			वापस invalf(fc, "VFS: Multiple sources");
		fc->source = param->string;
		param->string = शून्य;
		वापस 0;
	पूर्ण

	वापस invalf(fc, "%s: Unknown parameter '%s'",
		      fc->fs_type->name, param->key);
पूर्ण
EXPORT_SYMBOL(vfs_parse_fs_param);

/**
 * vfs_parse_fs_string - Convenience function to just parse a string.
 */
पूर्णांक vfs_parse_fs_string(काष्ठा fs_context *fc, स्थिर अक्षर *key,
			स्थिर अक्षर *value, माप_प्रकार v_size)
अणु
	पूर्णांक ret;

	काष्ठा fs_parameter param = अणु
		.key	= key,
		.type	= fs_value_is_flag,
		.size	= v_size,
	पूर्ण;

	अगर (value) अणु
		param.string = kmemdup_nul(value, v_size, GFP_KERNEL);
		अगर (!param.string)
			वापस -ENOMEM;
		param.type = fs_value_is_string;
	पूर्ण

	ret = vfs_parse_fs_param(fc, &param);
	kमुक्त(param.string);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfs_parse_fs_string);

/**
 * generic_parse_monolithic - Parse key[=val][,key[=val]]* mount data
 * @ctx: The superblock configuration to fill in.
 * @data: The data to parse
 *
 * Parse a blob of data that's in key[=val][,key[=val]]* क्रमm.  This can be
 * called from the ->monolithic_mount_data() fs_context operation.
 *
 * Returns 0 on success or the error वापसed by the ->parse_option() fs_context
 * operation on failure.
 */
पूर्णांक generic_parse_monolithic(काष्ठा fs_context *fc, व्योम *data)
अणु
	अक्षर *options = data, *key;
	पूर्णांक ret = 0;

	अगर (!options)
		वापस 0;

	ret = security_sb_eat_lsm_opts(options, &fc->security);
	अगर (ret)
		वापस ret;

	जबतक ((key = strsep(&options, ",")) != शून्य) अणु
		अगर (*key) अणु
			माप_प्रकार v_len = 0;
			अक्षर *value = म_अक्षर(key, '=');

			अगर (value) अणु
				अगर (value == key)
					जारी;
				*value++ = 0;
				v_len = म_माप(value);
			पूर्ण
			ret = vfs_parse_fs_string(fc, key, value, v_len);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(generic_parse_monolithic);

/**
 * alloc_fs_context - Create a fileप्रणाली context.
 * @fs_type: The fileप्रणाली type.
 * @reference: The dentry from which this one derives (or शून्य)
 * @sb_flags: Fileप्रणाली/superblock flags (SB_*)
 * @sb_flags_mask: Applicable members of @sb_flags
 * @purpose: The purpose that this configuration shall be used क्रम.
 *
 * Open a fileप्रणाली and create a mount context.  The mount context is
 * initialised with the supplied flags and, अगर a submount/स्वतःmount from
 * another superblock (referred to by @reference) is supplied, may have
 * parameters such as namespaces copied across from that superblock.
 */
अटल काष्ठा fs_context *alloc_fs_context(काष्ठा file_प्रणाली_type *fs_type,
				      काष्ठा dentry *reference,
				      अचिन्हित पूर्णांक sb_flags,
				      अचिन्हित पूर्णांक sb_flags_mask,
				      क्रमागत fs_context_purpose purpose)
अणु
	पूर्णांक (*init_fs_context)(काष्ठा fs_context *);
	काष्ठा fs_context *fc;
	पूर्णांक ret = -ENOMEM;

	fc = kzalloc(माप(काष्ठा fs_context), GFP_KERNEL);
	अगर (!fc)
		वापस ERR_PTR(-ENOMEM);

	fc->purpose	= purpose;
	fc->sb_flags	= sb_flags;
	fc->sb_flags_mask = sb_flags_mask;
	fc->fs_type	= get_fileप्रणाली(fs_type);
	fc->cred	= get_current_cred();
	fc->net_ns	= get_net(current->nsproxy->net_ns);
	fc->log.prefix	= fs_type->name;

	mutex_init(&fc->uapi_mutex);

	चयन (purpose) अणु
	हाल FS_CONTEXT_FOR_MOUNT:
		fc->user_ns = get_user_ns(fc->cred->user_ns);
		अवरोध;
	हाल FS_CONTEXT_FOR_SUBMOUNT:
		fc->user_ns = get_user_ns(reference->d_sb->s_user_ns);
		अवरोध;
	हाल FS_CONTEXT_FOR_RECONFIGURE:
		atomic_inc(&reference->d_sb->s_active);
		fc->user_ns = get_user_ns(reference->d_sb->s_user_ns);
		fc->root = dget(reference);
		अवरोध;
	पूर्ण

	/* TODO: Make all fileप्रणालीs support this unconditionally */
	init_fs_context = fc->fs_type->init_fs_context;
	अगर (!init_fs_context)
		init_fs_context = legacy_init_fs_context;

	ret = init_fs_context(fc);
	अगर (ret < 0)
		जाओ err_fc;
	fc->need_मुक्त = true;
	वापस fc;

err_fc:
	put_fs_context(fc);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा fs_context *fs_context_क्रम_mount(काष्ठा file_प्रणाली_type *fs_type,
					अचिन्हित पूर्णांक sb_flags)
अणु
	वापस alloc_fs_context(fs_type, शून्य, sb_flags, 0,
					FS_CONTEXT_FOR_MOUNT);
पूर्ण
EXPORT_SYMBOL(fs_context_क्रम_mount);

काष्ठा fs_context *fs_context_क्रम_reconfigure(काष्ठा dentry *dentry,
					अचिन्हित पूर्णांक sb_flags,
					अचिन्हित पूर्णांक sb_flags_mask)
अणु
	वापस alloc_fs_context(dentry->d_sb->s_type, dentry, sb_flags,
				sb_flags_mask, FS_CONTEXT_FOR_RECONFIGURE);
पूर्ण
EXPORT_SYMBOL(fs_context_क्रम_reconfigure);

काष्ठा fs_context *fs_context_क्रम_submount(काष्ठा file_प्रणाली_type *type,
					   काष्ठा dentry *reference)
अणु
	वापस alloc_fs_context(type, reference, 0, 0, FS_CONTEXT_FOR_SUBMOUNT);
पूर्ण
EXPORT_SYMBOL(fs_context_क्रम_submount);

व्योम fc_drop_locked(काष्ठा fs_context *fc)
अणु
	काष्ठा super_block *sb = fc->root->d_sb;
	dput(fc->root);
	fc->root = शून्य;
	deactivate_locked_super(sb);
पूर्ण

अटल व्योम legacy_fs_context_मुक्त(काष्ठा fs_context *fc);

/**
 * vfs_dup_fc_config: Duplicate a fileप्रणाली context.
 * @src_fc: The context to copy.
 */
काष्ठा fs_context *vfs_dup_fs_context(काष्ठा fs_context *src_fc)
अणु
	काष्ठा fs_context *fc;
	पूर्णांक ret;

	अगर (!src_fc->ops->dup)
		वापस ERR_PTR(-EOPNOTSUPP);

	fc = kmemdup(src_fc, माप(काष्ठा fs_context), GFP_KERNEL);
	अगर (!fc)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&fc->uapi_mutex);

	fc->fs_निजी	= शून्य;
	fc->s_fs_info	= शून्य;
	fc->source	= शून्य;
	fc->security	= शून्य;
	get_fileप्रणाली(fc->fs_type);
	get_net(fc->net_ns);
	get_user_ns(fc->user_ns);
	get_cred(fc->cred);
	अगर (fc->log.log)
		refcount_inc(&fc->log.log->usage);

	/* Can't call put until we've called ->dup */
	ret = fc->ops->dup(fc, src_fc);
	अगर (ret < 0)
		जाओ err_fc;

	ret = security_fs_context_dup(fc, src_fc);
	अगर (ret < 0)
		जाओ err_fc;
	वापस fc;

err_fc:
	put_fs_context(fc);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(vfs_dup_fs_context);

/**
 * logfc - Log a message to a fileप्रणाली context
 * @fc: The fileप्रणाली context to log to.
 * @fmt: The क्रमmat of the buffer.
 */
व्योम logfc(काष्ठा fc_log *log, स्थिर अक्षर *prefix, अक्षर level, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	काष्ठा va_क्रमmat vaf = अणु.fmt = fmt, .va = &vaपूर्ण;

	बहु_शुरू(va, fmt);
	अगर (!log) अणु
		चयन (level) अणु
		हाल 'w':
			prपूर्णांकk(KERN_WARNING "%s%s%pV\n", prefix ? prefix : "",
						prefix ? ": " : "", &vaf);
			अवरोध;
		हाल 'e':
			prपूर्णांकk(KERN_ERR "%s%s%pV\n", prefix ? prefix : "",
						prefix ? ": " : "", &vaf);
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_NOTICE "%s%s%pV\n", prefix ? prefix : "",
						prefix ? ": " : "", &vaf);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक logsize = ARRAY_SIZE(log->buffer);
		u8 index;
		अक्षर *q = kaप्र_लिखो(GFP_KERNEL, "%c %s%s%pV\n", level,
						prefix ? prefix : "",
						prefix ? ": " : "", &vaf);

		index = log->head & (logsize - 1);
		BUILD_BUG_ON(माप(log->head) != माप(u8) ||
			     माप(log->tail) != माप(u8));
		अगर ((u8)(log->head - log->tail) == logsize) अणु
			/* The buffer is full, discard the oldest message */
			अगर (log->need_मुक्त & (1 << index))
				kमुक्त(log->buffer[index]);
			log->tail++;
		पूर्ण

		log->buffer[index] = q ? q : "OOM: Can't store error string";
		अगर (q)
			log->need_मुक्त |= 1 << index;
		अन्यथा
			log->need_मुक्त &= ~(1 << index);
		log->head++;
	पूर्ण
	बहु_पूर्ण(va);
पूर्ण
EXPORT_SYMBOL(logfc);

/*
 * Free a logging काष्ठाure.
 */
अटल व्योम put_fc_log(काष्ठा fs_context *fc)
अणु
	काष्ठा fc_log *log = fc->log.log;
	पूर्णांक i;

	अगर (log) अणु
		अगर (refcount_dec_and_test(&log->usage)) अणु
			fc->log.log = शून्य;
			क्रम (i = 0; i <= 7; i++)
				अगर (log->need_मुक्त & (1 << i))
					kमुक्त(log->buffer[i]);
			kमुक्त(log);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * put_fs_context - Dispose of a superblock configuration context.
 * @fc: The context to dispose of.
 */
व्योम put_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा super_block *sb;

	अगर (fc->root) अणु
		sb = fc->root->d_sb;
		dput(fc->root);
		fc->root = शून्य;
		deactivate_super(sb);
	पूर्ण

	अगर (fc->need_मुक्त && fc->ops && fc->ops->मुक्त)
		fc->ops->मुक्त(fc);

	security_मुक्त_mnt_opts(&fc->security);
	put_net(fc->net_ns);
	put_user_ns(fc->user_ns);
	put_cred(fc->cred);
	put_fc_log(fc);
	put_fileप्रणाली(fc->fs_type);
	kमुक्त(fc->source);
	kमुक्त(fc);
पूर्ण
EXPORT_SYMBOL(put_fs_context);

/*
 * Free the config क्रम a fileप्रणाली that करोesn't support fs_context.
 */
अटल व्योम legacy_fs_context_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा legacy_fs_context *ctx = fc->fs_निजी;

	अगर (ctx) अणु
		अगर (ctx->param_type == LEGACY_FS_INDIVIDUAL_PARAMS)
			kमुक्त(ctx->legacy_data);
		kमुक्त(ctx);
	पूर्ण
पूर्ण

/*
 * Duplicate a legacy config.
 */
अटल पूर्णांक legacy_fs_context_dup(काष्ठा fs_context *fc, काष्ठा fs_context *src_fc)
अणु
	काष्ठा legacy_fs_context *ctx;
	काष्ठा legacy_fs_context *src_ctx = src_fc->fs_निजी;

	ctx = kmemdup(src_ctx, माप(*src_ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	अगर (ctx->param_type == LEGACY_FS_INDIVIDUAL_PARAMS) अणु
		ctx->legacy_data = kmemdup(src_ctx->legacy_data,
					   src_ctx->data_size, GFP_KERNEL);
		अगर (!ctx->legacy_data) अणु
			kमुक्त(ctx);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	fc->fs_निजी = ctx;
	वापस 0;
पूर्ण

/*
 * Add a parameter to a legacy config.  We build up a comma-separated list of
 * options.
 */
अटल पूर्णांक legacy_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा legacy_fs_context *ctx = fc->fs_निजी;
	अचिन्हित पूर्णांक size = ctx->data_size;
	माप_प्रकार len = 0;

	अगर (म_भेद(param->key, "source") == 0) अणु
		अगर (param->type != fs_value_is_string)
			वापस invalf(fc, "VFS: Legacy: Non-string source");
		अगर (fc->source)
			वापस invalf(fc, "VFS: Legacy: Multiple sources");
		fc->source = param->string;
		param->string = शून्य;
		वापस 0;
	पूर्ण

	अगर (ctx->param_type == LEGACY_FS_MONOLITHIC_PARAMS)
		वापस invalf(fc, "VFS: Legacy: Can't mix monolithic and individual options");

	चयन (param->type) अणु
	हाल fs_value_is_string:
		len = 1 + param->size;
		fallthrough;
	हाल fs_value_is_flag:
		len += म_माप(param->key);
		अवरोध;
	शेष:
		वापस invalf(fc, "VFS: Legacy: Parameter type for '%s' not supported",
			      param->key);
	पूर्ण

	अगर (len > PAGE_SIZE - 2 - size)
		वापस invalf(fc, "VFS: Legacy: Cumulative options too large");
	अगर (म_अक्षर(param->key, ',') ||
	    (param->type == fs_value_is_string &&
	     स_प्रथम(param->string, ',', param->size)))
		वापस invalf(fc, "VFS: Legacy: Option '%s' contained comma",
			      param->key);
	अगर (!ctx->legacy_data) अणु
		ctx->legacy_data = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
		अगर (!ctx->legacy_data)
			वापस -ENOMEM;
	पूर्ण

	ctx->legacy_data[size++] = ',';
	len = म_माप(param->key);
	स_नकल(ctx->legacy_data + size, param->key, len);
	size += len;
	अगर (param->type == fs_value_is_string) अणु
		ctx->legacy_data[size++] = '=';
		स_नकल(ctx->legacy_data + size, param->string, param->size);
		size += param->size;
	पूर्ण
	ctx->legacy_data[size] = '\0';
	ctx->data_size = size;
	ctx->param_type = LEGACY_FS_INDIVIDUAL_PARAMS;
	वापस 0;
पूर्ण

/*
 * Add monolithic mount data.
 */
अटल पूर्णांक legacy_parse_monolithic(काष्ठा fs_context *fc, व्योम *data)
अणु
	काष्ठा legacy_fs_context *ctx = fc->fs_निजी;

	अगर (ctx->param_type != LEGACY_FS_UNSET_PARAMS) अणु
		pr_warn("VFS: Can't mix monolithic and individual options\n");
		वापस -EINVAL;
	पूर्ण

	ctx->legacy_data = data;
	ctx->param_type = LEGACY_FS_MONOLITHIC_PARAMS;
	अगर (!ctx->legacy_data)
		वापस 0;

	अगर (fc->fs_type->fs_flags & FS_BINARY_MOUNTDATA)
		वापस 0;
	वापस security_sb_eat_lsm_opts(ctx->legacy_data, &fc->security);
पूर्ण

/*
 * Get a mountable root with the legacy mount command.
 */
अटल पूर्णांक legacy_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा legacy_fs_context *ctx = fc->fs_निजी;
	काष्ठा super_block *sb;
	काष्ठा dentry *root;

	root = fc->fs_type->mount(fc->fs_type, fc->sb_flags,
				      fc->source, ctx->legacy_data);
	अगर (IS_ERR(root))
		वापस PTR_ERR(root);

	sb = root->d_sb;
	BUG_ON(!sb);

	fc->root = root;
	वापस 0;
पूर्ण

/*
 * Handle remount.
 */
अटल पूर्णांक legacy_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा legacy_fs_context *ctx = fc->fs_निजी;
	काष्ठा super_block *sb = fc->root->d_sb;

	अगर (!sb->s_op->remount_fs)
		वापस 0;

	वापस sb->s_op->remount_fs(sb, &fc->sb_flags,
				    ctx ? ctx->legacy_data : शून्य);
पूर्ण

स्थिर काष्ठा fs_context_operations legacy_fs_context_ops = अणु
	.मुक्त			= legacy_fs_context_मुक्त,
	.dup			= legacy_fs_context_dup,
	.parse_param		= legacy_parse_param,
	.parse_monolithic	= legacy_parse_monolithic,
	.get_tree		= legacy_get_tree,
	.reconfigure		= legacy_reconfigure,
पूर्ण;

/*
 * Initialise a legacy context क्रम a fileप्रणाली that करोesn't support
 * fs_context.
 */
अटल पूर्णांक legacy_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->fs_निजी = kzalloc(माप(काष्ठा legacy_fs_context), GFP_KERNEL);
	अगर (!fc->fs_निजी)
		वापस -ENOMEM;
	fc->ops = &legacy_fs_context_ops;
	वापस 0;
पूर्ण

पूर्णांक parse_monolithic_mount_data(काष्ठा fs_context *fc, व्योम *data)
अणु
	पूर्णांक (*monolithic_mount_data)(काष्ठा fs_context *, व्योम *);

	monolithic_mount_data = fc->ops->parse_monolithic;
	अगर (!monolithic_mount_data)
		monolithic_mount_data = generic_parse_monolithic;

	वापस monolithic_mount_data(fc, data);
पूर्ण

/*
 * Clean up a context after perक्रमming an action on it and put it पूर्णांकo a state
 * from where it can be used to reconfigure a superblock.
 *
 * Note that here we करो only the parts that can't fail; the rest is in
 * finish_clean_context() below and in between those fs_context is marked
 * FS_CONTEXT_AWAITING_RECONF.  The reason क्रम splitup is that after
 * successful mount or remount we need to report success to userland.
 * Trying to करो full reinit (क्रम the sake of possible subsequent remount)
 * and failing to allocate memory would've put us पूर्णांकo a nasty situation.
 * So here we only discard the old state and reinitialization is left
 * until we actually try to reconfigure.
 */
व्योम vfs_clean_context(काष्ठा fs_context *fc)
अणु
	अगर (fc->need_मुक्त && fc->ops && fc->ops->मुक्त)
		fc->ops->मुक्त(fc);
	fc->need_मुक्त = false;
	fc->fs_निजी = शून्य;
	fc->s_fs_info = शून्य;
	fc->sb_flags = 0;
	security_मुक्त_mnt_opts(&fc->security);
	kमुक्त(fc->source);
	fc->source = शून्य;

	fc->purpose = FS_CONTEXT_FOR_RECONFIGURE;
	fc->phase = FS_CONTEXT_AWAITING_RECONF;
पूर्ण

पूर्णांक finish_clean_context(काष्ठा fs_context *fc)
अणु
	पूर्णांक error;

	अगर (fc->phase != FS_CONTEXT_AWAITING_RECONF)
		वापस 0;

	अगर (fc->fs_type->init_fs_context)
		error = fc->fs_type->init_fs_context(fc);
	अन्यथा
		error = legacy_init_fs_context(fc);
	अगर (unlikely(error)) अणु
		fc->phase = FS_CONTEXT_FAILED;
		वापस error;
	पूर्ण
	fc->need_मुक्त = true;
	fc->phase = FS_CONTEXT_RECONF_PARAMS;
	वापस 0;
पूर्ण
