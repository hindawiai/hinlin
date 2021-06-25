<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * security/tomoyo/common.h
 *
 * Header file क्रम TOMOYO.
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#अगर_अघोषित _SECURITY_TOMOYO_COMMON_H
#घोषणा _SECURITY_TOMOYO_COMMON_H

#घोषणा pr_fmt(fmt) fmt

#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/file.h>
#समावेश <linux/kmod.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/list.h>
#समावेश <linux/cred.h>
#समावेश <linux/poll.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/net.h>
#समावेश <linux/inet.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/un.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <net/sock.h>
#समावेश <net/af_unix.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/udp.h>

/********** Constants definitions. **********/

/*
 * TOMOYO uses this hash only when appending a string पूर्णांकo the string
 * table. Frequency of appending strings is very low. So we करोn't need
 * large (e.g. 64k) hash size. 256 will be sufficient.
 */
#घोषणा TOMOYO_HASH_BITS  8
#घोषणा TOMOYO_MAX_HASH (1u<<TOMOYO_HASH_BITS)

/*
 * TOMOYO checks only SOCK_STREAM, SOCK_DGRAM, SOCK_RAW, SOCK_SEQPACKET.
 * Thereक्रमe, we करोn't need SOCK_MAX.
 */
#घोषणा TOMOYO_SOCK_MAX 6

#घोषणा TOMOYO_EXEC_TMPSIZE     4096

/* Garbage collector is trying to kमुक्त() this element. */
#घोषणा TOMOYO_GC_IN_PROGRESS -1

/* Profile number is an पूर्णांकeger between 0 and 255. */
#घोषणा TOMOYO_MAX_PROखाताS 256

/* Group number is an पूर्णांकeger between 0 and 255. */
#घोषणा TOMOYO_MAX_ACL_GROUPS 256

/* Index numbers क्रम "struct tomoyo_condition". */
क्रमागत tomoyo_conditions_index अणु
	TOMOYO_TASK_UID,             /* current_uid()   */
	TOMOYO_TASK_EUID,            /* current_euid()  */
	TOMOYO_TASK_SUID,            /* current_suid()  */
	TOMOYO_TASK_FSUID,           /* current_fsuid() */
	TOMOYO_TASK_GID,             /* current_gid()   */
	TOMOYO_TASK_EGID,            /* current_egid()  */
	TOMOYO_TASK_SGID,            /* current_sgid()  */
	TOMOYO_TASK_FSGID,           /* current_fsgid() */
	TOMOYO_TASK_PID,             /* sys_getpid()   */
	TOMOYO_TASK_PPID,            /* sys_getppid()  */
	TOMOYO_EXEC_ARGC,            /* "struct linux_binprm *"->argc */
	TOMOYO_EXEC_ENVC,            /* "struct linux_binprm *"->envc */
	TOMOYO_TYPE_IS_SOCKET,       /* S_IFSOCK */
	TOMOYO_TYPE_IS_SYMLINK,      /* S_IFLNK */
	TOMOYO_TYPE_IS_खाता,         /* S_IFREG */
	TOMOYO_TYPE_IS_BLOCK_DEV,    /* S_IFBLK */
	TOMOYO_TYPE_IS_सूचीECTORY,    /* S_IFसूची */
	TOMOYO_TYPE_IS_CHAR_DEV,     /* S_IFCHR */
	TOMOYO_TYPE_IS_FIFO,         /* S_IFIFO */
	TOMOYO_MODE_SETUID,          /* S_ISUID */
	TOMOYO_MODE_SETGID,          /* S_ISGID */
	TOMOYO_MODE_STICKY,          /* S_ISVTX */
	TOMOYO_MODE_OWNER_READ,      /* S_IRUSR */
	TOMOYO_MODE_OWNER_WRITE,     /* S_IWUSR */
	TOMOYO_MODE_OWNER_EXECUTE,   /* S_IXUSR */
	TOMOYO_MODE_GROUP_READ,      /* S_IRGRP */
	TOMOYO_MODE_GROUP_WRITE,     /* S_IWGRP */
	TOMOYO_MODE_GROUP_EXECUTE,   /* S_IXGRP */
	TOMOYO_MODE_OTHERS_READ,     /* S_IROTH */
	TOMOYO_MODE_OTHERS_WRITE,    /* S_IWOTH */
	TOMOYO_MODE_OTHERS_EXECUTE,  /* S_IXOTH */
	TOMOYO_EXEC_REALPATH,
	TOMOYO_SYMLINK_TARGET,
	TOMOYO_PATH1_UID,
	TOMOYO_PATH1_GID,
	TOMOYO_PATH1_INO,
	TOMOYO_PATH1_MAJOR,
	TOMOYO_PATH1_MINOR,
	TOMOYO_PATH1_PERM,
	TOMOYO_PATH1_TYPE,
	TOMOYO_PATH1_DEV_MAJOR,
	TOMOYO_PATH1_DEV_MINOR,
	TOMOYO_PATH2_UID,
	TOMOYO_PATH2_GID,
	TOMOYO_PATH2_INO,
	TOMOYO_PATH2_MAJOR,
	TOMOYO_PATH2_MINOR,
	TOMOYO_PATH2_PERM,
	TOMOYO_PATH2_TYPE,
	TOMOYO_PATH2_DEV_MAJOR,
	TOMOYO_PATH2_DEV_MINOR,
	TOMOYO_PATH1_PARENT_UID,
	TOMOYO_PATH1_PARENT_GID,
	TOMOYO_PATH1_PARENT_INO,
	TOMOYO_PATH1_PARENT_PERM,
	TOMOYO_PATH2_PARENT_UID,
	TOMOYO_PATH2_PARENT_GID,
	TOMOYO_PATH2_PARENT_INO,
	TOMOYO_PATH2_PARENT_PERM,
	TOMOYO_MAX_CONDITION_KEYWORD,
	TOMOYO_NUMBER_UNION,
	TOMOYO_NAME_UNION,
	TOMOYO_ARGV_ENTRY,
	TOMOYO_ENVP_ENTRY,
पूर्ण;


/* Index numbers क्रम stat(). */
क्रमागत tomoyo_path_stat_index अणु
	/* Do not change this order. */
	TOMOYO_PATH1,
	TOMOYO_PATH1_PARENT,
	TOMOYO_PATH2,
	TOMOYO_PATH2_PARENT,
	TOMOYO_MAX_PATH_STAT
पूर्ण;

/* Index numbers क्रम operation mode. */
क्रमागत tomoyo_mode_index अणु
	TOMOYO_CONFIG_DISABLED,
	TOMOYO_CONFIG_LEARNING,
	TOMOYO_CONFIG_PERMISSIVE,
	TOMOYO_CONFIG_ENFORCING,
	TOMOYO_CONFIG_MAX_MODE,
	TOMOYO_CONFIG_WANT_REJECT_LOG =  64,
	TOMOYO_CONFIG_WANT_GRANT_LOG  = 128,
	TOMOYO_CONFIG_USE_DEFAULT     = 255,
पूर्ण;

/* Index numbers क्रम entry type. */
क्रमागत tomoyo_policy_id अणु
	TOMOYO_ID_GROUP,
	TOMOYO_ID_ADDRESS_GROUP,
	TOMOYO_ID_PATH_GROUP,
	TOMOYO_ID_NUMBER_GROUP,
	TOMOYO_ID_TRANSITION_CONTROL,
	TOMOYO_ID_AGGREGATOR,
	TOMOYO_ID_MANAGER,
	TOMOYO_ID_CONDITION,
	TOMOYO_ID_NAME,
	TOMOYO_ID_ACL,
	TOMOYO_ID_DOMAIN,
	TOMOYO_MAX_POLICY
पूर्ण;

/* Index numbers क्रम करोमुख्य's attributes. */
क्रमागत tomoyo_करोमुख्य_info_flags_index अणु
	/* Quota warnning flag.   */
	TOMOYO_DIF_QUOTA_WARNED,
	/*
	 * This करोमुख्य was unable to create a new करोमुख्य at
	 * tomoyo_find_next_करोमुख्य() because the name of the करोमुख्य to be
	 * created was too दीर्घ or it could not allocate memory.
	 * More than one process जारीd execve() without करोमुख्य transition.
	 */
	TOMOYO_DIF_TRANSITION_FAILED,
	TOMOYO_MAX_DOMAIN_INFO_FLAGS
पूर्ण;

/* Index numbers क्रम audit type. */
क्रमागत tomoyo_grant_log अणु
	/* Follow profile's configuration. */
	TOMOYO_GRANTLOG_AUTO,
	/* Do not generate grant log. */
	TOMOYO_GRANTLOG_NO,
	/* Generate grant_log. */
	TOMOYO_GRANTLOG_YES,
पूर्ण;

/* Index numbers क्रम group entries. */
क्रमागत tomoyo_group_id अणु
	TOMOYO_PATH_GROUP,
	TOMOYO_NUMBER_GROUP,
	TOMOYO_ADDRESS_GROUP,
	TOMOYO_MAX_GROUP
पूर्ण;

/* Index numbers क्रम type of numeric values. */
क्रमागत tomoyo_value_type अणु
	TOMOYO_VALUE_TYPE_INVALID,
	TOMOYO_VALUE_TYPE_DECIMAL,
	TOMOYO_VALUE_TYPE_OCTAL,
	TOMOYO_VALUE_TYPE_HEXADECIMAL,
पूर्ण;

/* Index numbers क्रम करोमुख्य transition control keywords. */
क्रमागत tomoyo_transition_type अणु
	/* Do not change this order, */
	TOMOYO_TRANSITION_CONTROL_NO_RESET,
	TOMOYO_TRANSITION_CONTROL_RESET,
	TOMOYO_TRANSITION_CONTROL_NO_INITIALIZE,
	TOMOYO_TRANSITION_CONTROL_INITIALIZE,
	TOMOYO_TRANSITION_CONTROL_NO_KEEP,
	TOMOYO_TRANSITION_CONTROL_KEEP,
	TOMOYO_MAX_TRANSITION_TYPE
पूर्ण;

/* Index numbers क्रम Access Controls. */
क्रमागत tomoyo_acl_entry_type_index अणु
	TOMOYO_TYPE_PATH_ACL,
	TOMOYO_TYPE_PATH2_ACL,
	TOMOYO_TYPE_PATH_NUMBER_ACL,
	TOMOYO_TYPE_MKDEV_ACL,
	TOMOYO_TYPE_MOUNT_ACL,
	TOMOYO_TYPE_INET_ACL,
	TOMOYO_TYPE_UNIX_ACL,
	TOMOYO_TYPE_ENV_ACL,
	TOMOYO_TYPE_MANUAL_TASK_ACL,
पूर्ण;

/* Index numbers क्रम access controls with one pathname. */
क्रमागत tomoyo_path_acl_index अणु
	TOMOYO_TYPE_EXECUTE,
	TOMOYO_TYPE_READ,
	TOMOYO_TYPE_WRITE,
	TOMOYO_TYPE_APPEND,
	TOMOYO_TYPE_UNLINK,
	TOMOYO_TYPE_GETATTR,
	TOMOYO_TYPE_RMसूची,
	TOMOYO_TYPE_TRUNCATE,
	TOMOYO_TYPE_SYMLINK,
	TOMOYO_TYPE_CHROOT,
	TOMOYO_TYPE_UMOUNT,
	TOMOYO_MAX_PATH_OPERATION
पूर्ण;

/* Index numbers क्रम /sys/kernel/security/tomoyo/stat पूर्णांकerface. */
क्रमागत tomoyo_memory_stat_type अणु
	TOMOYO_MEMORY_POLICY,
	TOMOYO_MEMORY_AUDIT,
	TOMOYO_MEMORY_QUERY,
	TOMOYO_MAX_MEMORY_STAT
पूर्ण;

क्रमागत tomoyo_mkdev_acl_index अणु
	TOMOYO_TYPE_MKBLOCK,
	TOMOYO_TYPE_MKCHAR,
	TOMOYO_MAX_MKDEV_OPERATION
पूर्ण;

/* Index numbers क्रम socket operations. */
क्रमागत tomoyo_network_acl_index अणु
	TOMOYO_NETWORK_BIND,    /* bind() operation. */
	TOMOYO_NETWORK_LISTEN,  /* listen() operation. */
	TOMOYO_NETWORK_CONNECT, /* connect() operation. */
	TOMOYO_NETWORK_SEND,    /* send() operation. */
	TOMOYO_MAX_NETWORK_OPERATION
पूर्ण;

/* Index numbers क्रम access controls with two pathnames. */
क्रमागत tomoyo_path2_acl_index अणु
	TOMOYO_TYPE_LINK,
	TOMOYO_TYPE_RENAME,
	TOMOYO_TYPE_PIVOT_ROOT,
	TOMOYO_MAX_PATH2_OPERATION
पूर्ण;

/* Index numbers क्रम access controls with one pathname and one number. */
क्रमागत tomoyo_path_number_acl_index अणु
	TOMOYO_TYPE_CREATE,
	TOMOYO_TYPE_MKसूची,
	TOMOYO_TYPE_MKFIFO,
	TOMOYO_TYPE_MKSOCK,
	TOMOYO_TYPE_IOCTL,
	TOMOYO_TYPE_CHMOD,
	TOMOYO_TYPE_CHOWN,
	TOMOYO_TYPE_CHGRP,
	TOMOYO_MAX_PATH_NUMBER_OPERATION
पूर्ण;

/* Index numbers क्रम /sys/kernel/security/tomoyo/ पूर्णांकerfaces. */
क्रमागत tomoyo_securityfs_पूर्णांकerface_index अणु
	TOMOYO_DOMAINPOLICY,
	TOMOYO_EXCEPTIONPOLICY,
	TOMOYO_PROCESS_STATUS,
	TOMOYO_STAT,
	TOMOYO_AUDIT,
	TOMOYO_VERSION,
	TOMOYO_PROखाता,
	TOMOYO_QUERY,
	TOMOYO_MANAGER
पूर्ण;

/* Index numbers क्रम special mount operations. */
क्रमागत tomoyo_special_mount अणु
	TOMOYO_MOUNT_BIND,            /* mount --bind /source /dest   */
	TOMOYO_MOUNT_MOVE,            /* mount --move /old /new       */
	TOMOYO_MOUNT_REMOUNT,         /* mount -o remount /dir        */
	TOMOYO_MOUNT_MAKE_UNBINDABLE, /* mount --make-unbindable /dir */
	TOMOYO_MOUNT_MAKE_PRIVATE,    /* mount --make-निजी /dir    */
	TOMOYO_MOUNT_MAKE_SLAVE,      /* mount --make-slave /dir      */
	TOMOYO_MOUNT_MAKE_SHARED,     /* mount --make-shared /dir     */
	TOMOYO_MAX_SPECIAL_MOUNT
पूर्ण;

/* Index numbers क्रम functionality. */
क्रमागत tomoyo_mac_index अणु
	TOMOYO_MAC_खाता_EXECUTE,
	TOMOYO_MAC_खाता_OPEN,
	TOMOYO_MAC_खाता_CREATE,
	TOMOYO_MAC_खाता_UNLINK,
	TOMOYO_MAC_खाता_GETATTR,
	TOMOYO_MAC_खाता_MKसूची,
	TOMOYO_MAC_खाता_RMसूची,
	TOMOYO_MAC_खाता_MKFIFO,
	TOMOYO_MAC_खाता_MKSOCK,
	TOMOYO_MAC_खाता_TRUNCATE,
	TOMOYO_MAC_खाता_SYMLINK,
	TOMOYO_MAC_खाता_MKBLOCK,
	TOMOYO_MAC_खाता_MKCHAR,
	TOMOYO_MAC_खाता_LINK,
	TOMOYO_MAC_खाता_RENAME,
	TOMOYO_MAC_खाता_CHMOD,
	TOMOYO_MAC_खाता_CHOWN,
	TOMOYO_MAC_खाता_CHGRP,
	TOMOYO_MAC_खाता_IOCTL,
	TOMOYO_MAC_खाता_CHROOT,
	TOMOYO_MAC_खाता_MOUNT,
	TOMOYO_MAC_खाता_UMOUNT,
	TOMOYO_MAC_खाता_PIVOT_ROOT,
	TOMOYO_MAC_NETWORK_INET_STREAM_BIND,
	TOMOYO_MAC_NETWORK_INET_STREAM_LISTEN,
	TOMOYO_MAC_NETWORK_INET_STREAM_CONNECT,
	TOMOYO_MAC_NETWORK_INET_DGRAM_BIND,
	TOMOYO_MAC_NETWORK_INET_DGRAM_SEND,
	TOMOYO_MAC_NETWORK_INET_RAW_BIND,
	TOMOYO_MAC_NETWORK_INET_RAW_SEND,
	TOMOYO_MAC_NETWORK_UNIX_STREAM_BIND,
	TOMOYO_MAC_NETWORK_UNIX_STREAM_LISTEN,
	TOMOYO_MAC_NETWORK_UNIX_STREAM_CONNECT,
	TOMOYO_MAC_NETWORK_UNIX_DGRAM_BIND,
	TOMOYO_MAC_NETWORK_UNIX_DGRAM_SEND,
	TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_BIND,
	TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_LISTEN,
	TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_CONNECT,
	TOMOYO_MAC_ENVIRON,
	TOMOYO_MAX_MAC_INDEX
पूर्ण;

/* Index numbers क्रम category of functionality. */
क्रमागत tomoyo_mac_category_index अणु
	TOMOYO_MAC_CATEGORY_खाता,
	TOMOYO_MAC_CATEGORY_NETWORK,
	TOMOYO_MAC_CATEGORY_MISC,
	TOMOYO_MAX_MAC_CATEGORY_INDEX
पूर्ण;

/*
 * Retry this request. Returned by tomoyo_supervisor() अगर policy violation has
 * occurred in enक्रमcing mode and the userspace daemon decided to retry.
 *
 * We must choose a positive value in order to distinguish "granted" (which is
 * 0) and "rejected" (which is a negative value) and "retry".
 */
#घोषणा TOMOYO_RETRY_REQUEST 1

/* Index numbers क्रम /sys/kernel/security/tomoyo/stat पूर्णांकerface. */
क्रमागत tomoyo_policy_stat_type अणु
	/* Do not change this order. */
	TOMOYO_STAT_POLICY_UPDATES,
	TOMOYO_STAT_POLICY_LEARNING,   /* == TOMOYO_CONFIG_LEARNING */
	TOMOYO_STAT_POLICY_PERMISSIVE, /* == TOMOYO_CONFIG_PERMISSIVE */
	TOMOYO_STAT_POLICY_ENFORCING,  /* == TOMOYO_CONFIG_ENFORCING */
	TOMOYO_MAX_POLICY_STAT
पूर्ण;

/* Index numbers क्रम profile's PREFERENCE values. */
क्रमागत tomoyo_pref_index अणु
	TOMOYO_PREF_MAX_AUDIT_LOG,
	TOMOYO_PREF_MAX_LEARNING_ENTRY,
	TOMOYO_MAX_PREF
पूर्ण;

/********** Structure definitions. **********/

/* Common header क्रम holding ACL entries. */
काष्ठा tomoyo_acl_head अणु
	काष्ठा list_head list;
	s8 is_deleted; /* true or false or TOMOYO_GC_IN_PROGRESS */
पूर्ण __packed;

/* Common header क्रम shared entries. */
काष्ठा tomoyo_shared_acl_head अणु
	काष्ठा list_head list;
	atomic_t users;
पूर्ण __packed;

काष्ठा tomoyo_policy_namespace;

/* Structure क्रम request info. */
काष्ठा tomoyo_request_info अणु
	/*
	 * For holding parameters specअगरic to operations which deal files.
	 * शून्य अगर not dealing files.
	 */
	काष्ठा tomoyo_obj_info *obj;
	/*
	 * For holding parameters specअगरic to execve() request.
	 * शून्य अगर not dealing execve().
	 */
	काष्ठा tomoyo_execve *ee;
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य;
	/* For holding parameters. */
	जोड़ अणु
		काष्ठा अणु
			स्थिर काष्ठा tomoyo_path_info *filename;
			/* For using wildcards at tomoyo_find_next_करोमुख्य(). */
			स्थिर काष्ठा tomoyo_path_info *matched_path;
			/* One of values in "enum tomoyo_path_acl_index". */
			u8 operation;
		पूर्ण path;
		काष्ठा अणु
			स्थिर काष्ठा tomoyo_path_info *filename1;
			स्थिर काष्ठा tomoyo_path_info *filename2;
			/* One of values in "enum tomoyo_path2_acl_index". */
			u8 operation;
		पूर्ण path2;
		काष्ठा अणु
			स्थिर काष्ठा tomoyo_path_info *filename;
			अचिन्हित पूर्णांक mode;
			अचिन्हित पूर्णांक major;
			अचिन्हित पूर्णांक minor;
			/* One of values in "enum tomoyo_mkdev_acl_index". */
			u8 operation;
		पूर्ण mkdev;
		काष्ठा अणु
			स्थिर काष्ठा tomoyo_path_info *filename;
			अचिन्हित दीर्घ number;
			/*
			 * One of values in
			 * "enum tomoyo_path_number_acl_index".
			 */
			u8 operation;
		पूर्ण path_number;
		काष्ठा अणु
			स्थिर काष्ठा tomoyo_path_info *name;
		पूर्ण environ;
		काष्ठा अणु
			स्थिर __be32 *address;
			u16 port;
			/* One of values smaller than TOMOYO_SOCK_MAX. */
			u8 protocol;
			/* One of values in "enum tomoyo_network_acl_index". */
			u8 operation;
			bool is_ipv6;
		पूर्ण inet_network;
		काष्ठा अणु
			स्थिर काष्ठा tomoyo_path_info *address;
			/* One of values smaller than TOMOYO_SOCK_MAX. */
			u8 protocol;
			/* One of values in "enum tomoyo_network_acl_index". */
			u8 operation;
		पूर्ण unix_network;
		काष्ठा अणु
			स्थिर काष्ठा tomoyo_path_info *type;
			स्थिर काष्ठा tomoyo_path_info *dir;
			स्थिर काष्ठा tomoyo_path_info *dev;
			अचिन्हित दीर्घ flags;
			पूर्णांक need_dev;
		पूर्ण mount;
		काष्ठा अणु
			स्थिर काष्ठा tomoyo_path_info *करोमुख्यname;
		पूर्ण task;
	पूर्ण param;
	काष्ठा tomoyo_acl_info *matched_acl;
	u8 param_type;
	bool granted;
	u8 retry;
	u8 profile;
	u8 mode; /* One of tomoyo_mode_index . */
	u8 type;
पूर्ण;

/* Structure क्रम holding a token. */
काष्ठा tomoyo_path_info अणु
	स्थिर अक्षर *name;
	u32 hash;          /* = full_name_hash(name, म_माप(name)) */
	u16 स्थिर_len;     /* = tomoyo_स्थिर_part_length(name)     */
	bool is_dir;       /* = tomoyo_strendswith(name, "/")      */
	bool is_patterned; /* = tomoyo_path_contains_pattern(name) */
पूर्ण;

/* Structure क्रम holding string data. */
काष्ठा tomoyo_name अणु
	काष्ठा tomoyo_shared_acl_head head;
	काष्ठा tomoyo_path_info entry;
पूर्ण;

/* Structure क्रम holding a word. */
काष्ठा tomoyo_name_जोड़ अणु
	/* Either @filename or @group is शून्य. */
	स्थिर काष्ठा tomoyo_path_info *filename;
	काष्ठा tomoyo_group *group;
पूर्ण;

/* Structure क्रम holding a number. */
काष्ठा tomoyo_number_जोड़ अणु
	अचिन्हित दीर्घ values[2];
	काष्ठा tomoyo_group *group; /* Maybe शून्य. */
	/* One of values in "enum tomoyo_value_type". */
	u8 value_type[2];
पूर्ण;

/* Structure क्रम holding an IP address. */
काष्ठा tomoyo_ipaddr_जोड़ अणु
	काष्ठा in6_addr ip[2]; /* Big endian. */
	काष्ठा tomoyo_group *group; /* Poपूर्णांकer to address group. */
	bool is_ipv6; /* Valid only अगर @group == शून्य. */
पूर्ण;

/* Structure क्रम "path_group"/"number_group"/"address_group" directive. */
काष्ठा tomoyo_group अणु
	काष्ठा tomoyo_shared_acl_head head;
	स्थिर काष्ठा tomoyo_path_info *group_name;
	काष्ठा list_head member_list;
पूर्ण;

/* Structure क्रम "path_group" directive. */
काष्ठा tomoyo_path_group अणु
	काष्ठा tomoyo_acl_head head;
	स्थिर काष्ठा tomoyo_path_info *member_name;
पूर्ण;

/* Structure क्रम "number_group" directive. */
काष्ठा tomoyo_number_group अणु
	काष्ठा tomoyo_acl_head head;
	काष्ठा tomoyo_number_जोड़ number;
पूर्ण;

/* Structure क्रम "address_group" directive. */
काष्ठा tomoyo_address_group अणु
	काष्ठा tomoyo_acl_head head;
	/* Structure क्रम holding an IP address. */
	काष्ठा tomoyo_ipaddr_जोड़ address;
पूर्ण;

/* Subset of "struct stat". Used by conditional ACL and audit logs. */
काष्ठा tomoyo_mini_stat अणु
	kuid_t uid;
	kgid_t gid;
	ino_t ino;
	umode_t mode;
	dev_t dev;
	dev_t rdev;
पूर्ण;

/* Structure क्रम dumping argv[] and envp[] of "struct linux_binprm". */
काष्ठा tomoyo_page_dump अणु
	काष्ठा page *page;    /* Previously dumped page. */
	अक्षर *data;           /* Contents of "page". Size is PAGE_SIZE. */
पूर्ण;

/* Structure क्रम attribute checks in addition to pathname checks. */
काष्ठा tomoyo_obj_info अणु
	/*
	 * True अगर tomoyo_get_attributes() was alपढ़ोy called, false otherwise.
	 */
	bool validate_करोne;
	/* True अगर @stat[] is valid. */
	bool stat_valid[TOMOYO_MAX_PATH_STAT];
	/* First pathname. Initialized with अणु शून्य, शून्य पूर्ण अगर no path. */
	काष्ठा path path1;
	/* Second pathname. Initialized with अणु शून्य, शून्य पूर्ण अगर no path. */
	काष्ठा path path2;
	/*
	 * Inक्रमmation on @path1, @path1's parent directory, @path2, @path2's
	 * parent directory.
	 */
	काष्ठा tomoyo_mini_stat stat[TOMOYO_MAX_PATH_STAT];
	/*
	 * Content of symbolic link to be created. शून्य क्रम operations other
	 * than symlink().
	 */
	काष्ठा tomoyo_path_info *symlink_target;
पूर्ण;

/* Structure क्रम argv[]. */
काष्ठा tomoyo_argv अणु
	अचिन्हित दीर्घ index;
	स्थिर काष्ठा tomoyo_path_info *value;
	bool is_not;
पूर्ण;

/* Structure क्रम envp[]. */
काष्ठा tomoyo_envp अणु
	स्थिर काष्ठा tomoyo_path_info *name;
	स्थिर काष्ठा tomoyo_path_info *value;
	bool is_not;
पूर्ण;

/* Structure क्रम execve() operation. */
काष्ठा tomoyo_execve अणु
	काष्ठा tomoyo_request_info r;
	काष्ठा tomoyo_obj_info obj;
	काष्ठा linux_binprm *bprm;
	स्थिर काष्ठा tomoyo_path_info *transition;
	/* For dumping argv[] and envp[]. */
	काष्ठा tomoyo_page_dump dump;
	/* For temporary use. */
	अक्षर *पंचांगp; /* Size is TOMOYO_EXEC_TMPSIZE bytes */
पूर्ण;

/* Structure क्रम entries which follows "struct tomoyo_condition". */
काष्ठा tomoyo_condition_element अणु
	/*
	 * Left hand opeअक्रम. A "struct tomoyo_argv" क्रम TOMOYO_ARGV_ENTRY, a
	 * "struct tomoyo_envp" क्रम TOMOYO_ENVP_ENTRY is attached to the tail
	 * of the array of this काष्ठा.
	 */
	u8 left;
	/*
	 * Right hand opeअक्रम. A "struct tomoyo_number_union" क्रम
	 * TOMOYO_NUMBER_UNION, a "struct tomoyo_name_union" क्रम
	 * TOMOYO_NAME_UNION is attached to the tail of the array of this
	 * काष्ठा.
	 */
	u8 right;
	/* Equation चालक. True अगर equals or overlaps, false otherwise. */
	bool equals;
पूर्ण;

/* Structure क्रम optional arguments. */
काष्ठा tomoyo_condition अणु
	काष्ठा tomoyo_shared_acl_head head;
	u32 size; /* Memory size allocated क्रम this entry. */
	u16 condc; /* Number of conditions in this काष्ठा. */
	u16 numbers_count; /* Number of "struct tomoyo_number_union values". */
	u16 names_count; /* Number of "struct tomoyo_name_union names". */
	u16 argc; /* Number of "struct tomoyo_argv". */
	u16 envc; /* Number of "struct tomoyo_envp". */
	u8 grant_log; /* One of values in "enum tomoyo_grant_log". */
	स्थिर काष्ठा tomoyo_path_info *transit; /* Maybe शून्य. */
	/*
	 * काष्ठा tomoyo_condition_element condition[condc];
	 * काष्ठा tomoyo_number_जोड़ values[numbers_count];
	 * काष्ठा tomoyo_name_जोड़ names[names_count];
	 * काष्ठा tomoyo_argv argv[argc];
	 * काष्ठा tomoyo_envp envp[envc];
	 */
पूर्ण;

/* Common header क्रम inभागidual entries. */
काष्ठा tomoyo_acl_info अणु
	काष्ठा list_head list;
	काष्ठा tomoyo_condition *cond; /* Maybe शून्य. */
	s8 is_deleted; /* true or false or TOMOYO_GC_IN_PROGRESS */
	u8 type; /* One of values in "enum tomoyo_acl_entry_type_index". */
पूर्ण __packed;

/* Structure क्रम करोमुख्य inक्रमmation. */
काष्ठा tomoyo_करोमुख्य_info अणु
	काष्ठा list_head list;
	काष्ठा list_head acl_info_list;
	/* Name of this करोमुख्य. Never शून्य.          */
	स्थिर काष्ठा tomoyo_path_info *करोमुख्यname;
	/* Namespace क्रम this करोमुख्य. Never शून्य. */
	काष्ठा tomoyo_policy_namespace *ns;
	/* Group numbers to use.   */
	अचिन्हित दीर्घ group[TOMOYO_MAX_ACL_GROUPS / BITS_PER_LONG];
	u8 profile;        /* Profile number to use. */
	bool is_deleted;   /* Delete flag.           */
	bool flags[TOMOYO_MAX_DOMAIN_INFO_FLAGS];
	atomic_t users; /* Number of referring tasks. */
पूर्ण;

/*
 * Structure क्रम "task manual_domain_transition" directive.
 */
काष्ठा tomoyo_task_acl अणु
	काष्ठा tomoyo_acl_info head; /* type = TOMOYO_TYPE_MANUAL_TASK_ACL */
	/* Poपूर्णांकer to करोमुख्यname. */
	स्थिर काष्ठा tomoyo_path_info *करोमुख्यname;
पूर्ण;

/*
 * Structure क्रम "file execute", "file read", "file write", "file append",
 * "file unlink", "file getattr", "file rmdir", "file truncate",
 * "file symlink", "file chroot" and "file unmount" directive.
 */
काष्ठा tomoyo_path_acl अणु
	काष्ठा tomoyo_acl_info head; /* type = TOMOYO_TYPE_PATH_ACL */
	u16 perm; /* Biपंचांगask of values in "enum tomoyo_path_acl_index". */
	काष्ठा tomoyo_name_जोड़ name;
पूर्ण;

/*
 * Structure क्रम "file create", "file mkdir", "file mkfifo", "file mksock",
 * "file ioctl", "file chmod", "file chown" and "file chgrp" directive.
 */
काष्ठा tomoyo_path_number_acl अणु
	काष्ठा tomoyo_acl_info head; /* type = TOMOYO_TYPE_PATH_NUMBER_ACL */
	/* Biपंचांगask of values in "enum tomoyo_path_number_acl_index". */
	u8 perm;
	काष्ठा tomoyo_name_जोड़ name;
	काष्ठा tomoyo_number_जोड़ number;
पूर्ण;

/* Structure क्रम "file mkblock" and "file mkchar" directive. */
काष्ठा tomoyo_mkdev_acl अणु
	काष्ठा tomoyo_acl_info head; /* type = TOMOYO_TYPE_MKDEV_ACL */
	u8 perm; /* Biपंचांगask of values in "enum tomoyo_mkdev_acl_index". */
	काष्ठा tomoyo_name_जोड़ name;
	काष्ठा tomoyo_number_जोड़ mode;
	काष्ठा tomoyo_number_जोड़ major;
	काष्ठा tomoyo_number_जोड़ minor;
पूर्ण;

/*
 * Structure क्रम "file rename", "file link" and "file pivot_root" directive.
 */
काष्ठा tomoyo_path2_acl अणु
	काष्ठा tomoyo_acl_info head; /* type = TOMOYO_TYPE_PATH2_ACL */
	u8 perm; /* Biपंचांगask of values in "enum tomoyo_path2_acl_index". */
	काष्ठा tomoyo_name_जोड़ name1;
	काष्ठा tomoyo_name_जोड़ name2;
पूर्ण;

/* Structure क्रम "file mount" directive. */
काष्ठा tomoyo_mount_acl अणु
	काष्ठा tomoyo_acl_info head; /* type = TOMOYO_TYPE_MOUNT_ACL */
	काष्ठा tomoyo_name_जोड़ dev_name;
	काष्ठा tomoyo_name_जोड़ dir_name;
	काष्ठा tomoyo_name_जोड़ fs_type;
	काष्ठा tomoyo_number_जोड़ flags;
पूर्ण;

/* Structure क्रम "misc env" directive in करोमुख्य policy. */
काष्ठा tomoyo_env_acl अणु
	काष्ठा tomoyo_acl_info head;        /* type = TOMOYO_TYPE_ENV_ACL  */
	स्थिर काष्ठा tomoyo_path_info *env; /* environment variable */
पूर्ण;

/* Structure क्रम "network inet" directive. */
काष्ठा tomoyo_inet_acl अणु
	काष्ठा tomoyo_acl_info head; /* type = TOMOYO_TYPE_INET_ACL */
	u8 protocol;
	u8 perm; /* Biपंचांगask of values in "enum tomoyo_network_acl_index" */
	काष्ठा tomoyo_ipaddr_जोड़ address;
	काष्ठा tomoyo_number_जोड़ port;
पूर्ण;

/* Structure क्रम "network unix" directive. */
काष्ठा tomoyo_unix_acl अणु
	काष्ठा tomoyo_acl_info head; /* type = TOMOYO_TYPE_UNIX_ACL */
	u8 protocol;
	u8 perm; /* Biपंचांगask of values in "enum tomoyo_network_acl_index" */
	काष्ठा tomoyo_name_जोड़ name;
पूर्ण;

/* Structure क्रम holding a line from /sys/kernel/security/tomoyo/ पूर्णांकerface. */
काष्ठा tomoyo_acl_param अणु
	अक्षर *data;
	काष्ठा list_head *list;
	काष्ठा tomoyo_policy_namespace *ns;
	bool is_delete;
पूर्ण;

#घोषणा TOMOYO_MAX_IO_READ_QUEUE 64

/*
 * Structure क्रम पढ़ोing/writing policy via /sys/kernel/security/tomoyo
 * पूर्णांकerfaces.
 */
काष्ठा tomoyo_io_buffer अणु
	व्योम (*पढ़ो)(काष्ठा tomoyo_io_buffer *head);
	पूर्णांक (*ग_लिखो)(काष्ठा tomoyo_io_buffer *head);
	__poll_t (*poll)(काष्ठा file *file, poll_table *रुको);
	/* Exclusive lock क्रम this काष्ठाure.   */
	काष्ठा mutex io_sem;
	अक्षर __user *पढ़ो_user_buf;
	माप_प्रकार पढ़ो_user_buf_avail;
	काष्ठा अणु
		काष्ठा list_head *ns;
		काष्ठा list_head *करोमुख्य;
		काष्ठा list_head *group;
		काष्ठा list_head *acl;
		माप_प्रकार avail;
		अचिन्हित पूर्णांक step;
		अचिन्हित पूर्णांक query_index;
		u16 index;
		u16 cond_index;
		u8 acl_group_index;
		u8 cond_step;
		u8 bit;
		u8 w_pos;
		bool eof;
		bool prपूर्णांक_this_करोमुख्य_only;
		bool prपूर्णांक_transition_related_only;
		bool prपूर्णांक_cond_part;
		स्थिर अक्षर *w[TOMOYO_MAX_IO_READ_QUEUE];
	पूर्ण r;
	काष्ठा अणु
		काष्ठा tomoyo_policy_namespace *ns;
		/* The position currently writing to.   */
		काष्ठा tomoyo_करोमुख्य_info *करोमुख्य;
		/* Bytes available क्रम writing.         */
		माप_प्रकार avail;
		bool is_delete;
	पूर्ण w;
	/* Buffer क्रम पढ़ोing.                  */
	अक्षर *पढ़ो_buf;
	/* Size of पढ़ो buffer.                 */
	माप_प्रकार पढ़ोbuf_size;
	/* Buffer क्रम writing.                  */
	अक्षर *ग_लिखो_buf;
	/* Size of ग_लिखो buffer.                */
	माप_प्रकार ग_लिखोbuf_size;
	/* Type of this पूर्णांकerface.              */
	क्रमागत tomoyo_securityfs_पूर्णांकerface_index type;
	/* Users counter रक्षित by tomoyo_io_buffer_list_lock. */
	u8 users;
	/* List क्रम telling GC not to kमुक्त() elements. */
	काष्ठा list_head list;
पूर्ण;

/*
 * Structure क्रम "initialize_domain"/"no_initialize_domain"/"keep_domain"/
 * "no_keep_domain" keyword.
 */
काष्ठा tomoyo_transition_control अणु
	काष्ठा tomoyo_acl_head head;
	u8 type; /* One of values in "enum tomoyo_transition_type".  */
	/* True अगर the करोमुख्यname is tomoyo_get_last_name(). */
	bool is_last_name;
	स्थिर काष्ठा tomoyo_path_info *करोमुख्यname; /* Maybe शून्य */
	स्थिर काष्ठा tomoyo_path_info *program;    /* Maybe शून्य */
पूर्ण;

/* Structure क्रम "aggregator" keyword. */
काष्ठा tomoyo_aggregator अणु
	काष्ठा tomoyo_acl_head head;
	स्थिर काष्ठा tomoyo_path_info *original_name;
	स्थिर काष्ठा tomoyo_path_info *aggregated_name;
पूर्ण;

/* Structure क्रम policy manager. */
काष्ठा tomoyo_manager अणु
	काष्ठा tomoyo_acl_head head;
	/* A path to program or a करोमुख्यname. */
	स्थिर काष्ठा tomoyo_path_info *manager;
पूर्ण;

काष्ठा tomoyo_preference अणु
	अचिन्हित पूर्णांक learning_max_entry;
	bool enक्रमcing_verbose;
	bool learning_verbose;
	bool permissive_verbose;
पूर्ण;

/* Structure क्रम /sys/kernel/security/tomnoyo/profile पूर्णांकerface. */
काष्ठा tomoyo_profile अणु
	स्थिर काष्ठा tomoyo_path_info *comment;
	काष्ठा tomoyo_preference *learning;
	काष्ठा tomoyo_preference *permissive;
	काष्ठा tomoyo_preference *enक्रमcing;
	काष्ठा tomoyo_preference preference;
	u8 शेष_config;
	u8 config[TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGORY_INDEX];
	अचिन्हित पूर्णांक pref[TOMOYO_MAX_PREF];
पूर्ण;

/* Structure क्रम representing YYYY/MM/DD hh/mm/ss. */
काष्ठा tomoyo_समय अणु
	u16 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 min;
	u8 sec;
पूर्ण;

/* Structure क्रम policy namespace. */
काष्ठा tomoyo_policy_namespace अणु
	/* Profile table. Memory is allocated as needed. */
	काष्ठा tomoyo_profile *profile_ptr[TOMOYO_MAX_PROखाताS];
	/* List of "struct tomoyo_group". */
	काष्ठा list_head group_list[TOMOYO_MAX_GROUP];
	/* List of policy. */
	काष्ठा list_head policy_list[TOMOYO_MAX_POLICY];
	/* The global ACL referred by "use_group" keyword. */
	काष्ठा list_head acl_group[TOMOYO_MAX_ACL_GROUPS];
	/* List क्रम connecting to tomoyo_namespace_list list. */
	काष्ठा list_head namespace_list;
	/* Profile version. Currently only 20150505 is defined. */
	अचिन्हित पूर्णांक profile_version;
	/* Name of this namespace (e.g. "<kernel>", "</usr/sbin/httpd>" ). */
	स्थिर अक्षर *name;
पूर्ण;

/* Structure क्रम "struct task_struct"->security. */
काष्ठा tomoyo_task अणु
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य_info;
	काष्ठा tomoyo_करोमुख्य_info *old_करोमुख्य_info;
पूर्ण;

/********** Function prototypes. **********/

bool tomoyo_address_matches_group(स्थिर bool is_ipv6, स्थिर __be32 *address,
				  स्थिर काष्ठा tomoyo_group *group);
bool tomoyo_compare_number_जोड़(स्थिर अचिन्हित दीर्घ value,
				 स्थिर काष्ठा tomoyo_number_जोड़ *ptr);
bool tomoyo_condition(काष्ठा tomoyo_request_info *r,
		      स्थिर काष्ठा tomoyo_condition *cond);
bool tomoyo_correct_करोमुख्य(स्थिर अचिन्हित अक्षर *करोमुख्यname);
bool tomoyo_correct_path(स्थिर अक्षर *filename);
bool tomoyo_correct_word(स्थिर अक्षर *string);
bool tomoyo_करोमुख्य_def(स्थिर अचिन्हित अक्षर *buffer);
bool tomoyo_करोमुख्य_quota_is_ok(काष्ठा tomoyo_request_info *r);
bool tomoyo_dump_page(काष्ठा linux_binprm *bprm, अचिन्हित दीर्घ pos,
		      काष्ठा tomoyo_page_dump *dump);
bool tomoyo_memory_ok(व्योम *ptr);
bool tomoyo_number_matches_group(स्थिर अचिन्हित दीर्घ min,
				 स्थिर अचिन्हित दीर्घ max,
				 स्थिर काष्ठा tomoyo_group *group);
bool tomoyo_parse_ipaddr_जोड़(काष्ठा tomoyo_acl_param *param,
			       काष्ठा tomoyo_ipaddr_जोड़ *ptr);
bool tomoyo_parse_name_जोड़(काष्ठा tomoyo_acl_param *param,
			     काष्ठा tomoyo_name_जोड़ *ptr);
bool tomoyo_parse_number_जोड़(काष्ठा tomoyo_acl_param *param,
			       काष्ठा tomoyo_number_जोड़ *ptr);
bool tomoyo_path_matches_pattern(स्थिर काष्ठा tomoyo_path_info *filename,
				 स्थिर काष्ठा tomoyo_path_info *pattern);
bool tomoyo_permstr(स्थिर अक्षर *string, स्थिर अक्षर *keyword);
bool tomoyo_str_starts(अक्षर **src, स्थिर अक्षर *find);
अक्षर *tomoyo_encode(स्थिर अक्षर *str);
अक्षर *tomoyo_encode2(स्थिर अक्षर *str, पूर्णांक str_len);
अक्षर *tomoyo_init_log(काष्ठा tomoyo_request_info *r, पूर्णांक len, स्थिर अक्षर *fmt,
		      बहु_सूची args);
अक्षर *tomoyo_पढ़ो_token(काष्ठा tomoyo_acl_param *param);
अक्षर *tomoyo_realpath_from_path(स्थिर काष्ठा path *path);
अक्षर *tomoyo_realpath_nofollow(स्थिर अक्षर *pathname);
स्थिर अक्षर *tomoyo_get_exe(व्योम);
स्थिर अक्षर *tomoyo_yesno(स्थिर अचिन्हित पूर्णांक value);
स्थिर काष्ठा tomoyo_path_info *tomoyo_compare_name_जोड़
(स्थिर काष्ठा tomoyo_path_info *name, स्थिर काष्ठा tomoyo_name_जोड़ *ptr);
स्थिर काष्ठा tomoyo_path_info *tomoyo_get_करोमुख्यname
(काष्ठा tomoyo_acl_param *param);
स्थिर काष्ठा tomoyo_path_info *tomoyo_get_name(स्थिर अक्षर *name);
स्थिर काष्ठा tomoyo_path_info *tomoyo_path_matches_group
(स्थिर काष्ठा tomoyo_path_info *pathname, स्थिर काष्ठा tomoyo_group *group);
पूर्णांक tomoyo_check_खोलो_permission(काष्ठा tomoyo_करोमुख्य_info *करोमुख्य,
				 स्थिर काष्ठा path *path, स्थिर पूर्णांक flag);
व्योम tomoyo_बंद_control(काष्ठा tomoyo_io_buffer *head);
पूर्णांक tomoyo_env_perm(काष्ठा tomoyo_request_info *r, स्थिर अक्षर *env);
पूर्णांक tomoyo_execute_permission(काष्ठा tomoyo_request_info *r,
			      स्थिर काष्ठा tomoyo_path_info *filename);
पूर्णांक tomoyo_find_next_करोमुख्य(काष्ठा linux_binprm *bprm);
पूर्णांक tomoyo_get_mode(स्थिर काष्ठा tomoyo_policy_namespace *ns, स्थिर u8 profile,
		    स्थिर u8 index);
पूर्णांक tomoyo_init_request_info(काष्ठा tomoyo_request_info *r,
			     काष्ठा tomoyo_करोमुख्य_info *करोमुख्य,
			     स्थिर u8 index);
पूर्णांक tomoyo_mkdev_perm(स्थिर u8 operation, स्थिर काष्ठा path *path,
		      स्थिर अचिन्हित पूर्णांक mode, अचिन्हित पूर्णांक dev);
पूर्णांक tomoyo_mount_permission(स्थिर अक्षर *dev_name, स्थिर काष्ठा path *path,
			    स्थिर अक्षर *type, अचिन्हित दीर्घ flags,
			    व्योम *data_page);
पूर्णांक tomoyo_खोलो_control(स्थिर u8 type, काष्ठा file *file);
पूर्णांक tomoyo_path2_perm(स्थिर u8 operation, स्थिर काष्ठा path *path1,
		      स्थिर काष्ठा path *path2);
पूर्णांक tomoyo_path_number_perm(स्थिर u8 operation, स्थिर काष्ठा path *path,
			    अचिन्हित दीर्घ number);
पूर्णांक tomoyo_path_perm(स्थिर u8 operation, स्थिर काष्ठा path *path,
		     स्थिर अक्षर *target);
__poll_t tomoyo_poll_control(काष्ठा file *file, poll_table *रुको);
__poll_t tomoyo_poll_log(काष्ठा file *file, poll_table *रुको);
पूर्णांक tomoyo_socket_bind_permission(काष्ठा socket *sock, काष्ठा sockaddr *addr,
				  पूर्णांक addr_len);
पूर्णांक tomoyo_socket_connect_permission(काष्ठा socket *sock,
				     काष्ठा sockaddr *addr, पूर्णांक addr_len);
पूर्णांक tomoyo_socket_listen_permission(काष्ठा socket *sock);
पूर्णांक tomoyo_socket_sendmsg_permission(काष्ठा socket *sock, काष्ठा msghdr *msg,
				     पूर्णांक size);
पूर्णांक tomoyo_supervisor(काष्ठा tomoyo_request_info *r, स्थिर अक्षर *fmt, ...)
	__म_लिखो(2, 3);
पूर्णांक tomoyo_update_करोमुख्य(काष्ठा tomoyo_acl_info *new_entry, स्थिर पूर्णांक size,
			 काष्ठा tomoyo_acl_param *param,
			 bool (*check_duplicate)
			 (स्थिर काष्ठा tomoyo_acl_info *,
			  स्थिर काष्ठा tomoyo_acl_info *),
			 bool (*merge_duplicate)
			 (काष्ठा tomoyo_acl_info *, काष्ठा tomoyo_acl_info *,
			  स्थिर bool));
पूर्णांक tomoyo_update_policy(काष्ठा tomoyo_acl_head *new_entry, स्थिर पूर्णांक size,
			 काष्ठा tomoyo_acl_param *param,
			 bool (*check_duplicate)
			 (स्थिर काष्ठा tomoyo_acl_head *,
			  स्थिर काष्ठा tomoyo_acl_head *));
पूर्णांक tomoyo_ग_लिखो_aggregator(काष्ठा tomoyo_acl_param *param);
पूर्णांक tomoyo_ग_लिखो_file(काष्ठा tomoyo_acl_param *param);
पूर्णांक tomoyo_ग_लिखो_group(काष्ठा tomoyo_acl_param *param, स्थिर u8 type);
पूर्णांक tomoyo_ग_लिखो_misc(काष्ठा tomoyo_acl_param *param);
पूर्णांक tomoyo_ग_लिखो_inet_network(काष्ठा tomoyo_acl_param *param);
पूर्णांक tomoyo_ग_लिखो_transition_control(काष्ठा tomoyo_acl_param *param,
				    स्थिर u8 type);
पूर्णांक tomoyo_ग_लिखो_unix_network(काष्ठा tomoyo_acl_param *param);
sमाप_प्रकार tomoyo_पढ़ो_control(काष्ठा tomoyo_io_buffer *head, अक्षर __user *buffer,
			    स्थिर पूर्णांक buffer_len);
sमाप_प्रकार tomoyo_ग_लिखो_control(काष्ठा tomoyo_io_buffer *head,
			     स्थिर अक्षर __user *buffer, स्थिर पूर्णांक buffer_len);
काष्ठा tomoyo_condition *tomoyo_get_condition(काष्ठा tomoyo_acl_param *param);
काष्ठा tomoyo_करोमुख्य_info *tomoyo_assign_करोमुख्य(स्थिर अक्षर *करोमुख्यname,
						स्थिर bool transit);
काष्ठा tomoyo_करोमुख्य_info *tomoyo_करोमुख्य(व्योम);
काष्ठा tomoyo_करोमुख्य_info *tomoyo_find_करोमुख्य(स्थिर अक्षर *करोमुख्यname);
काष्ठा tomoyo_group *tomoyo_get_group(काष्ठा tomoyo_acl_param *param,
				      स्थिर u8 idx);
काष्ठा tomoyo_policy_namespace *tomoyo_assign_namespace
(स्थिर अक्षर *करोमुख्यname);
काष्ठा tomoyo_profile *tomoyo_profile(स्थिर काष्ठा tomoyo_policy_namespace *ns,
				      स्थिर u8 profile);
अचिन्हित पूर्णांक tomoyo_check_flags(स्थिर काष्ठा tomoyo_करोमुख्य_info *करोमुख्य,
				स्थिर u8 index);
u8 tomoyo_parse_uदीर्घ(अचिन्हित दीर्घ *result, अक्षर **str);
व्योम *tomoyo_commit_ok(व्योम *data, स्थिर अचिन्हित पूर्णांक size);
व्योम __init tomoyo_load_builtin_policy(व्योम);
व्योम __init tomoyo_mm_init(व्योम);
व्योम tomoyo_check_acl(काष्ठा tomoyo_request_info *r,
		      bool (*check_entry)(काष्ठा tomoyo_request_info *,
					  स्थिर काष्ठा tomoyo_acl_info *));
व्योम tomoyo_check_profile(व्योम);
व्योम tomoyo_convert_समय(समय64_t समय, काष्ठा tomoyo_समय *stamp);
व्योम tomoyo_del_condition(काष्ठा list_head *element);
व्योम tomoyo_fill_path_info(काष्ठा tomoyo_path_info *ptr);
व्योम tomoyo_get_attributes(काष्ठा tomoyo_obj_info *obj);
व्योम tomoyo_init_policy_namespace(काष्ठा tomoyo_policy_namespace *ns);
व्योम tomoyo_load_policy(स्थिर अक्षर *filename);
व्योम tomoyo_normalize_line(अचिन्हित अक्षर *buffer);
व्योम tomoyo_notअगरy_gc(काष्ठा tomoyo_io_buffer *head, स्थिर bool is_रेजिस्टर);
व्योम tomoyo_prपूर्णांक_ip(अक्षर *buf, स्थिर अचिन्हित पूर्णांक size,
		     स्थिर काष्ठा tomoyo_ipaddr_जोड़ *ptr);
व्योम tomoyo_prपूर्णांक_uदीर्घ(अक्षर *buffer, स्थिर पूर्णांक buffer_len,
			स्थिर अचिन्हित दीर्घ value, स्थिर u8 type);
व्योम tomoyo_put_name_जोड़(काष्ठा tomoyo_name_जोड़ *ptr);
व्योम tomoyo_put_number_जोड़(काष्ठा tomoyo_number_जोड़ *ptr);
व्योम tomoyo_पढ़ो_log(काष्ठा tomoyo_io_buffer *head);
व्योम tomoyo_update_stat(स्थिर u8 index);
व्योम tomoyo_warn_oom(स्थिर अक्षर *function);
व्योम tomoyo_ग_लिखो_log(काष्ठा tomoyo_request_info *r, स्थिर अक्षर *fmt, ...)
	__म_लिखो(2, 3);
व्योम tomoyo_ग_लिखो_log2(काष्ठा tomoyo_request_info *r, पूर्णांक len, स्थिर अक्षर *fmt,
		       बहु_सूची args);

/********** External variable definitions. **********/

बाह्य bool tomoyo_policy_loaded;
बाह्य पूर्णांक tomoyo_enabled;
बाह्य स्थिर अक्षर * स्थिर tomoyo_condition_keyword
[TOMOYO_MAX_CONDITION_KEYWORD];
बाह्य स्थिर अक्षर * स्थिर tomoyo_dअगर[TOMOYO_MAX_DOMAIN_INFO_FLAGS];
बाह्य स्थिर अक्षर * स्थिर tomoyo_mac_keywords[TOMOYO_MAX_MAC_INDEX
					      + TOMOYO_MAX_MAC_CATEGORY_INDEX];
बाह्य स्थिर अक्षर * स्थिर tomoyo_mode[TOMOYO_CONFIG_MAX_MODE];
बाह्य स्थिर अक्षर * स्थिर tomoyo_path_keyword[TOMOYO_MAX_PATH_OPERATION];
बाह्य स्थिर अक्षर * स्थिर tomoyo_proto_keyword[TOMOYO_SOCK_MAX];
बाह्य स्थिर अक्षर * स्थिर tomoyo_socket_keyword[TOMOYO_MAX_NETWORK_OPERATION];
बाह्य स्थिर u8 tomoyo_index2category[TOMOYO_MAX_MAC_INDEX];
बाह्य स्थिर u8 tomoyo_pn2mac[TOMOYO_MAX_PATH_NUMBER_OPERATION];
बाह्य स्थिर u8 tomoyo_pnnn2mac[TOMOYO_MAX_MKDEV_OPERATION];
बाह्य स्थिर u8 tomoyo_pp2mac[TOMOYO_MAX_PATH2_OPERATION];
बाह्य काष्ठा list_head tomoyo_condition_list;
बाह्य काष्ठा list_head tomoyo_करोमुख्य_list;
बाह्य काष्ठा list_head tomoyo_name_list[TOMOYO_MAX_HASH];
बाह्य काष्ठा list_head tomoyo_namespace_list;
बाह्य काष्ठा mutex tomoyo_policy_lock;
बाह्य काष्ठा srcu_काष्ठा tomoyo_ss;
बाह्य काष्ठा tomoyo_करोमुख्य_info tomoyo_kernel_करोमुख्य;
बाह्य काष्ठा tomoyo_policy_namespace tomoyo_kernel_namespace;
बाह्य अचिन्हित पूर्णांक tomoyo_memory_quota[TOMOYO_MAX_MEMORY_STAT];
बाह्य अचिन्हित पूर्णांक tomoyo_memory_used[TOMOYO_MAX_MEMORY_STAT];
बाह्य काष्ठा lsm_blob_sizes tomoyo_blob_sizes;

/********** Inlined functions. **********/

/**
 * tomoyo_पढ़ो_lock - Take lock क्रम protecting policy.
 *
 * Returns index number क्रम tomoyo_पढ़ो_unlock().
 */
अटल अंतरभूत पूर्णांक tomoyo_पढ़ो_lock(व्योम)
अणु
	वापस srcu_पढ़ो_lock(&tomoyo_ss);
पूर्ण

/**
 * tomoyo_पढ़ो_unlock - Release lock क्रम protecting policy.
 *
 * @idx: Index number वापसed by tomoyo_पढ़ो_lock().
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_पढ़ो_unlock(पूर्णांक idx)
अणु
	srcu_पढ़ो_unlock(&tomoyo_ss, idx);
पूर्ण

/**
 * tomoyo_sys_getppid - Copy of getppid().
 *
 * Returns parent process's PID.
 *
 * Alpha करोes not have getppid() defined. To be able to build this module on
 * Alpha, I have to copy getppid() from kernel/समयr.c.
 */
अटल अंतरभूत pid_t tomoyo_sys_getppid(व्योम)
अणु
	pid_t pid;

	rcu_पढ़ो_lock();
	pid = task_tgid_vnr(rcu_dereference(current->real_parent));
	rcu_पढ़ो_unlock();
	वापस pid;
पूर्ण

/**
 * tomoyo_sys_getpid - Copy of getpid().
 *
 * Returns current thपढ़ो's PID.
 *
 * Alpha करोes not have getpid() defined. To be able to build this module on
 * Alpha, I have to copy getpid() from kernel/समयr.c.
 */
अटल अंतरभूत pid_t tomoyo_sys_getpid(व्योम)
अणु
	वापस task_tgid_vnr(current);
पूर्ण

/**
 * tomoyo_pathcmp - म_भेद() क्रम "struct tomoyo_path_info" काष्ठाure.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_path_info".
 * @b: Poपूर्णांकer to "struct tomoyo_path_info".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल अंतरभूत bool tomoyo_pathcmp(स्थिर काष्ठा tomoyo_path_info *a,
				  स्थिर काष्ठा tomoyo_path_info *b)
अणु
	वापस a->hash != b->hash || म_भेद(a->name, b->name);
पूर्ण

/**
 * tomoyo_put_name - Drop reference on "struct tomoyo_name".
 *
 * @name: Poपूर्णांकer to "struct tomoyo_path_info". Maybe शून्य.
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_put_name(स्थिर काष्ठा tomoyo_path_info *name)
अणु
	अगर (name) अणु
		काष्ठा tomoyo_name *ptr =
			container_of(name, typeof(*ptr), entry);
		atomic_dec(&ptr->head.users);
	पूर्ण
पूर्ण

/**
 * tomoyo_put_condition - Drop reference on "struct tomoyo_condition".
 *
 * @cond: Poपूर्णांकer to "struct tomoyo_condition". Maybe शून्य.
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_put_condition(काष्ठा tomoyo_condition *cond)
अणु
	अगर (cond)
		atomic_dec(&cond->head.users);
पूर्ण

/**
 * tomoyo_put_group - Drop reference on "struct tomoyo_group".
 *
 * @group: Poपूर्णांकer to "struct tomoyo_group". Maybe शून्य.
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_put_group(काष्ठा tomoyo_group *group)
अणु
	अगर (group)
		atomic_dec(&group->head.users);
पूर्ण

/**
 * tomoyo_task - Get "struct tomoyo_task" क्रम specअगरied thपढ़ो.
 *
 * @task - Poपूर्णांकer to "struct task_struct".
 *
 * Returns poपूर्णांकer to "struct tomoyo_task" क्रम specअगरied thपढ़ो.
 */
अटल अंतरभूत काष्ठा tomoyo_task *tomoyo_task(काष्ठा task_काष्ठा *task)
अणु
	वापस task->security + tomoyo_blob_sizes.lbs_task;
पूर्ण

/**
 * tomoyo_same_name_जोड़ - Check क्रम duplicated "struct tomoyo_name_union" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_name_union".
 * @b: Poपूर्णांकer to "struct tomoyo_name_union".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल अंतरभूत bool tomoyo_same_name_जोड़
(स्थिर काष्ठा tomoyo_name_जोड़ *a, स्थिर काष्ठा tomoyo_name_जोड़ *b)
अणु
	वापस a->filename == b->filename && a->group == b->group;
पूर्ण

/**
 * tomoyo_same_number_जोड़ - Check क्रम duplicated "struct tomoyo_number_union" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_number_union".
 * @b: Poपूर्णांकer to "struct tomoyo_number_union".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल अंतरभूत bool tomoyo_same_number_जोड़
(स्थिर काष्ठा tomoyo_number_जोड़ *a, स्थिर काष्ठा tomoyo_number_जोड़ *b)
अणु
	वापस a->values[0] == b->values[0] && a->values[1] == b->values[1] &&
		a->group == b->group && a->value_type[0] == b->value_type[0] &&
		a->value_type[1] == b->value_type[1];
पूर्ण

/**
 * tomoyo_same_ipaddr_जोड़ - Check क्रम duplicated "struct tomoyo_ipaddr_union" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_ipaddr_union".
 * @b: Poपूर्णांकer to "struct tomoyo_ipaddr_union".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल अंतरभूत bool tomoyo_same_ipaddr_जोड़
(स्थिर काष्ठा tomoyo_ipaddr_जोड़ *a, स्थिर काष्ठा tomoyo_ipaddr_जोड़ *b)
अणु
	वापस !स_भेद(a->ip, b->ip, माप(a->ip)) && a->group == b->group &&
		a->is_ipv6 == b->is_ipv6;
पूर्ण

/**
 * tomoyo_current_namespace - Get "struct tomoyo_policy_namespace" क्रम current thपढ़ो.
 *
 * Returns poपूर्णांकer to "struct tomoyo_policy_namespace" क्रम current thपढ़ो.
 */
अटल अंतरभूत काष्ठा tomoyo_policy_namespace *tomoyo_current_namespace(व्योम)
अणु
	वापस tomoyo_करोमुख्य()->ns;
पूर्ण

#अगर defined(CONFIG_SLOB)

/**
 * tomoyo_round2 - Round up to घातer of 2 क्रम calculating memory usage.
 *
 * @size: Size to be rounded up.
 *
 * Returns @size.
 *
 * Since SLOB करोes not round up, this function simply वापसs @size.
 */
अटल अंतरभूत पूर्णांक tomoyo_round2(माप_प्रकार size)
अणु
	वापस size;
पूर्ण

#अन्यथा

/**
 * tomoyo_round2 - Round up to घातer of 2 क्रम calculating memory usage.
 *
 * @size: Size to be rounded up.
 *
 * Returns rounded size.
 *
 * Strictly speaking, SLAB may be able to allocate (e.g.) 96 bytes instead of
 * (e.g.) 128 bytes.
 */
अटल अंतरभूत पूर्णांक tomoyo_round2(माप_प्रकार size)
अणु
#अगर PAGE_SIZE == 4096
	माप_प्रकार bsize = 32;
#अन्यथा
	माप_प्रकार bsize = 64;
#पूर्ण_अगर
	अगर (!size)
		वापस 0;
	जबतक (size > bsize)
		bsize <<= 1;
	वापस bsize;
पूर्ण

#पूर्ण_अगर

/**
 * list_क्रम_each_cookie - iterate over a list with cookie.
 * @pos:        the &काष्ठा list_head to use as a loop cursor.
 * @head:       the head क्रम your list.
 */
#घोषणा list_क्रम_each_cookie(pos, head)					\
	अगर (!pos)							\
		pos =  srcu_dereference((head)->next, &tomoyo_ss);	\
	क्रम ( ; pos != (head); pos = srcu_dereference(pos->next, &tomoyo_ss))

#पूर्ण_अगर /* !defined(_SECURITY_TOMOYO_COMMON_H) */
