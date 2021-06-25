<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Fileप्रणाली superblock creation and reconfiguration context.
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_FS_CONTEXT_H
#घोषणा _LINUX_FS_CONTEXT_H

#समावेश <linux/kernel.h>
#समावेश <linux/refcount.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/security.h>
#समावेश <linux/mutex.h>

काष्ठा cred;
काष्ठा dentry;
काष्ठा file_operations;
काष्ठा file_प्रणाली_type;
काष्ठा mnt_namespace;
काष्ठा net;
काष्ठा pid_namespace;
काष्ठा super_block;
काष्ठा user_namespace;
काष्ठा vfsmount;
काष्ठा path;

क्रमागत fs_context_purpose अणु
	FS_CONTEXT_FOR_MOUNT,		/* New superblock क्रम explicit mount */
	FS_CONTEXT_FOR_SUBMOUNT,	/* New superblock क्रम स्वतःmatic submount */
	FS_CONTEXT_FOR_RECONFIGURE,	/* Superblock reconfiguration (remount) */
पूर्ण;

/*
 * Userspace usage phase क्रम fsखोलो/fspick.
 */
क्रमागत fs_context_phase अणु
	FS_CONTEXT_CREATE_PARAMS,	/* Loading params क्रम sb creation */
	FS_CONTEXT_CREATING,		/* A superblock is being created */
	FS_CONTEXT_AWAITING_MOUNT,	/* Superblock created, aरुकोing fsmount() */
	FS_CONTEXT_AWAITING_RECONF,	/* Aरुकोing initialisation क्रम reconfiguration */
	FS_CONTEXT_RECONF_PARAMS,	/* Loading params क्रम reconfiguration */
	FS_CONTEXT_RECONFIGURING,	/* Reconfiguring the superblock */
	FS_CONTEXT_FAILED,		/* Failed to correctly transition a context */
पूर्ण;

/*
 * Type of parameter value.
 */
क्रमागत fs_value_type अणु
	fs_value_is_undefined,
	fs_value_is_flag,		/* Value not given a value */
	fs_value_is_string,		/* Value is a string */
	fs_value_is_blob,		/* Value is a binary blob */
	fs_value_is_filename,		/* Value is a filename* + dirfd */
	fs_value_is_file,		/* Value is a file* */
पूर्ण;

/*
 * Configuration parameter.
 */
काष्ठा fs_parameter अणु
	स्थिर अक्षर		*key;		/* Parameter name */
	क्रमागत fs_value_type	type:8;		/* The type of value here */
	जोड़ अणु
		अक्षर		*string;
		व्योम		*blob;
		काष्ठा filename	*name;
		काष्ठा file	*file;
	पूर्ण;
	माप_प्रकार	size;
	पूर्णांक	dirfd;
पूर्ण;

काष्ठा p_log अणु
	स्थिर अक्षर *prefix;
	काष्ठा fc_log *log;
पूर्ण;

/*
 * Fileप्रणाली context क्रम holding the parameters used in the creation or
 * reconfiguration of a superblock.
 *
 * Superblock creation fills in ->root whereas reconfiguration begins with this
 * alपढ़ोy set.
 *
 * See Documentation/fileप्रणालीs/mount_api.rst
 */
काष्ठा fs_context अणु
	स्थिर काष्ठा fs_context_operations *ops;
	काष्ठा mutex		uapi_mutex;	/* Userspace access mutex */
	काष्ठा file_प्रणाली_type	*fs_type;
	व्योम			*fs_निजी;	/* The fileप्रणाली's context */
	व्योम			*sget_key;
	काष्ठा dentry		*root;		/* The root and superblock */
	काष्ठा user_namespace	*user_ns;	/* The user namespace क्रम this mount */
	काष्ठा net		*net_ns;	/* The network namespace क्रम this mount */
	स्थिर काष्ठा cred	*cred;		/* The mounter's credentials */
	काष्ठा p_log		log;		/* Logging buffer */
	स्थिर अक्षर		*source;	/* The source name (eg. dev path) */
	व्योम			*security;	/* Linux S&M options */
	व्योम			*s_fs_info;	/* Proposed s_fs_info */
	अचिन्हित पूर्णांक		sb_flags;	/* Proposed superblock flags (SB_*) */
	अचिन्हित पूर्णांक		sb_flags_mask;	/* Superblock flags that were changed */
	अचिन्हित पूर्णांक		s_अगरlags;	/* OR'd with sb->s_अगरlags */
	अचिन्हित पूर्णांक		lsm_flags;	/* Inक्रमmation flags from the fs to the LSM */
	क्रमागत fs_context_purpose	purpose:8;
	क्रमागत fs_context_phase	phase:8;	/* The phase the context is in */
	bool			need_मुक्त:1;	/* Need to call ops->मुक्त() */
	bool			global:1;	/* Goes पूर्णांकo &init_user_ns */
	bool			oldapi:1;	/* Coming from mount(2) */
पूर्ण;

काष्ठा fs_context_operations अणु
	व्योम (*मुक्त)(काष्ठा fs_context *fc);
	पूर्णांक (*dup)(काष्ठा fs_context *fc, काष्ठा fs_context *src_fc);
	पूर्णांक (*parse_param)(काष्ठा fs_context *fc, काष्ठा fs_parameter *param);
	पूर्णांक (*parse_monolithic)(काष्ठा fs_context *fc, व्योम *data);
	पूर्णांक (*get_tree)(काष्ठा fs_context *fc);
	पूर्णांक (*reconfigure)(काष्ठा fs_context *fc);
पूर्ण;

/*
 * fs_context manipulation functions.
 */
बाह्य काष्ठा fs_context *fs_context_क्रम_mount(काष्ठा file_प्रणाली_type *fs_type,
						अचिन्हित पूर्णांक sb_flags);
बाह्य काष्ठा fs_context *fs_context_क्रम_reconfigure(काष्ठा dentry *dentry,
						अचिन्हित पूर्णांक sb_flags,
						अचिन्हित पूर्णांक sb_flags_mask);
बाह्य काष्ठा fs_context *fs_context_क्रम_submount(काष्ठा file_प्रणाली_type *fs_type,
						काष्ठा dentry *reference);

बाह्य काष्ठा fs_context *vfs_dup_fs_context(काष्ठा fs_context *fc);
बाह्य पूर्णांक vfs_parse_fs_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param);
बाह्य पूर्णांक vfs_parse_fs_string(काष्ठा fs_context *fc, स्थिर अक्षर *key,
			       स्थिर अक्षर *value, माप_प्रकार v_size);
बाह्य पूर्णांक generic_parse_monolithic(काष्ठा fs_context *fc, व्योम *data);
बाह्य पूर्णांक vfs_get_tree(काष्ठा fs_context *fc);
बाह्य व्योम put_fs_context(काष्ठा fs_context *fc);

/*
 * sget() wrappers to be called from the ->get_tree() op.
 */
क्रमागत vfs_get_super_keying अणु
	vfs_get_single_super,	/* Only one such superblock may exist */
	vfs_get_single_reconf_super, /* As above, but reconfigure अगर it exists */
	vfs_get_keyed_super,	/* Superblocks with dअगरferent s_fs_info keys may exist */
	vfs_get_independent_super, /* Multiple independent superblocks may exist */
पूर्ण;
बाह्य पूर्णांक vfs_get_super(काष्ठा fs_context *fc,
			 क्रमागत vfs_get_super_keying keying,
			 पूर्णांक (*fill_super)(काष्ठा super_block *sb,
					   काष्ठा fs_context *fc));

बाह्य पूर्णांक get_tree_nodev(काष्ठा fs_context *fc,
			 पूर्णांक (*fill_super)(काष्ठा super_block *sb,
					   काष्ठा fs_context *fc));
बाह्य पूर्णांक get_tree_single(काष्ठा fs_context *fc,
			 पूर्णांक (*fill_super)(काष्ठा super_block *sb,
					   काष्ठा fs_context *fc));
बाह्य पूर्णांक get_tree_single_reconf(काष्ठा fs_context *fc,
			 पूर्णांक (*fill_super)(काष्ठा super_block *sb,
					   काष्ठा fs_context *fc));
बाह्य पूर्णांक get_tree_keyed(काष्ठा fs_context *fc,
			 पूर्णांक (*fill_super)(काष्ठा super_block *sb,
					   काष्ठा fs_context *fc),
			 व्योम *key);

बाह्य पूर्णांक get_tree_bdev(काष्ठा fs_context *fc,
			       पूर्णांक (*fill_super)(काष्ठा super_block *sb,
						 काष्ठा fs_context *fc));

बाह्य स्थिर काष्ठा file_operations fscontext_fops;

/*
 * Mount error, warning and inक्रमmational message logging.  This काष्ठाure is
 * shareable between a mount and a subordinate mount.
 */
काष्ठा fc_log अणु
	refcount_t	usage;
	u8		head;		/* Insertion index in buffer[] */
	u8		tail;		/* Removal index in buffer[] */
	u8		need_मुक्त;	/* Mask of kमुक्त'able items in buffer[] */
	काष्ठा module	*owner;		/* Owner module क्रम strings that करोn't then need मुक्तing */
	अक्षर		*buffer[8];
पूर्ण;

बाह्य __attribute__((क्रमmat(म_लिखो, 4, 5)))
व्योम logfc(काष्ठा fc_log *log, स्थिर अक्षर *prefix, अक्षर level, स्थिर अक्षर *fmt, ...);

#घोषणा __logfc(fc, l, fmt, ...) logfc((fc)->log.log, शून्य, \
					l, fmt, ## __VA_ARGS__)
#घोषणा __plog(p, l, fmt, ...) logfc((p)->log, (p)->prefix, \
					l, fmt, ## __VA_ARGS__)
/**
 * infof - Store supplementary inक्रमmational message
 * @fc: The context in which to log the inक्रमmational message
 * @fmt: The क्रमmat string
 *
 * Store the supplementary inक्रमmational message क्रम the process अगर the process
 * has enabled the facility.
 */
#घोषणा infof(fc, fmt, ...) __logfc(fc, 'i', fmt, ## __VA_ARGS__)
#घोषणा info_plog(p, fmt, ...) __plog(p, 'i', fmt, ## __VA_ARGS__)
#घोषणा infofc(p, fmt, ...) __plog((&(fc)->log), 'i', fmt, ## __VA_ARGS__)

/**
 * warnf - Store supplementary warning message
 * @fc: The context in which to log the error message
 * @fmt: The क्रमmat string
 *
 * Store the supplementary warning message क्रम the process अगर the process has
 * enabled the facility.
 */
#घोषणा warnf(fc, fmt, ...) __logfc(fc, 'w', fmt, ## __VA_ARGS__)
#घोषणा warn_plog(p, fmt, ...) __plog(p, 'w', fmt, ## __VA_ARGS__)
#घोषणा warnfc(fc, fmt, ...) __plog((&(fc)->log), 'w', fmt, ## __VA_ARGS__)

/**
 * errorf - Store supplementary error message
 * @fc: The context in which to log the error message
 * @fmt: The क्रमmat string
 *
 * Store the supplementary error message क्रम the process अगर the process has
 * enabled the facility.
 */
#घोषणा errorf(fc, fmt, ...) __logfc(fc, 'e', fmt, ## __VA_ARGS__)
#घोषणा error_plog(p, fmt, ...) __plog(p, 'e', fmt, ## __VA_ARGS__)
#घोषणा errorfc(fc, fmt, ...) __plog((&(fc)->log), 'e', fmt, ## __VA_ARGS__)

/**
 * invalf - Store supplementary invalid argument error message
 * @fc: The context in which to log the error message
 * @fmt: The क्रमmat string
 *
 * Store the supplementary error message क्रम the process अगर the process has
 * enabled the facility and वापस -EINVAL.
 */
#घोषणा invalf(fc, fmt, ...) (errorf(fc, fmt, ## __VA_ARGS__), -EINVAL)
#घोषणा inval_plog(p, fmt, ...) (error_plog(p, fmt, ## __VA_ARGS__), -EINVAL)
#घोषणा invalfc(fc, fmt, ...) (errorfc(fc, fmt, ## __VA_ARGS__), -EINVAL)

#पूर्ण_अगर /* _LINUX_FS_CONTEXT_H */
