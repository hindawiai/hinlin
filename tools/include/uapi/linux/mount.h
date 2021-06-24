<शैली गुरु>
#अगर_अघोषित _UAPI_LINUX_MOUNT_H
#घोषणा _UAPI_LINUX_MOUNT_H

#समावेश <linux/types.h>

/*
 * These are the fs-independent mount-flags: up to 32 flags are supported
 *
 * Usage of these is restricted within the kernel to core mount(2) code and
 * callers of sys_mount() only.  Fileप्रणालीs should be using the SB_*
 * equivalent instead.
 */
#घोषणा MS_RDONLY	 1	/* Mount पढ़ो-only */
#घोषणा MS_NOSUID	 2	/* Ignore suid and sgid bits */
#घोषणा MS_NODEV	 4	/* Disallow access to device special files */
#घोषणा MS_NOEXEC	 8	/* Disallow program execution */
#घोषणा MS_SYNCHRONOUS	16	/* Writes are synced at once */
#घोषणा MS_REMOUNT	32	/* Alter flags of a mounted FS */
#घोषणा MS_MANDLOCK	64	/* Allow mandatory locks on an FS */
#घोषणा MS_सूचीSYNC	128	/* Directory modअगरications are synchronous */
#घोषणा MS_NOSYMFOLLOW	256	/* Do not follow symlinks */
#घोषणा MS_NOATIME	1024	/* Do not update access बार. */
#घोषणा MS_NOसूचीATIME	2048	/* Do not update directory access बार */
#घोषणा MS_BIND		4096
#घोषणा MS_MOVE		8192
#घोषणा MS_REC		16384
#घोषणा MS_VERBOSE	32768	/* War is peace. Verbosity is silence.
				   MS_VERBOSE is deprecated. */
#घोषणा MS_SILENT	32768
#घोषणा MS_POSIXACL	(1<<16)	/* VFS करोes not apply the umask */
#घोषणा MS_UNBINDABLE	(1<<17)	/* change to unbindable */
#घोषणा MS_PRIVATE	(1<<18)	/* change to निजी */
#घोषणा MS_SLAVE	(1<<19)	/* change to slave */
#घोषणा MS_SHARED	(1<<20)	/* change to shared */
#घोषणा MS_RELATIME	(1<<21)	/* Update aसमय relative to mसमय/स_समय. */
#घोषणा MS_KERNMOUNT	(1<<22) /* this is a kern_mount call */
#घोषणा MS_I_VERSION	(1<<23) /* Update inode I_version field */
#घोषणा MS_STRICTATIME	(1<<24) /* Always perक्रमm aसमय updates */
#घोषणा MS_LAZYTIME	(1<<25) /* Update the on-disk [acm]बार lazily */

/* These sb flags are पूर्णांकernal to the kernel */
#घोषणा MS_SUBMOUNT     (1<<26)
#घोषणा MS_NOREMOTELOCK	(1<<27)
#घोषणा MS_NOSEC	(1<<28)
#घोषणा MS_BORN		(1<<29)
#घोषणा MS_ACTIVE	(1<<30)
#घोषणा MS_NOUSER	(1<<31)

/*
 * Superblock flags that can be altered by MS_REMOUNT
 */
#घोषणा MS_RMT_MASK	(MS_RDONLY|MS_SYNCHRONOUS|MS_MANDLOCK|MS_I_VERSION|\
			 MS_LAZYTIME)

/*
 * Old magic mount flag and mask
 */
#घोषणा MS_MGC_VAL 0xC0ED0000
#घोषणा MS_MGC_MSK 0xffff0000

/*
 * खोलो_tree() flags.
 */
#घोषणा OPEN_TREE_CLONE		1		/* Clone the target tree and attach the clone */
#घोषणा OPEN_TREE_CLOEXEC	O_CLOEXEC	/* Close the file on execve() */

/*
 * move_mount() flags.
 */
#घोषणा MOVE_MOUNT_F_SYMLINKS		0x00000001 /* Follow symlinks on from path */
#घोषणा MOVE_MOUNT_F_AUTOMOUNTS		0x00000002 /* Follow स्वतःmounts on from path */
#घोषणा MOVE_MOUNT_F_EMPTY_PATH		0x00000004 /* Empty from path permitted */
#घोषणा MOVE_MOUNT_T_SYMLINKS		0x00000010 /* Follow symlinks on to path */
#घोषणा MOVE_MOUNT_T_AUTOMOUNTS		0x00000020 /* Follow स्वतःmounts on to path */
#घोषणा MOVE_MOUNT_T_EMPTY_PATH		0x00000040 /* Empty to path permitted */
#घोषणा MOVE_MOUNT__MASK		0x00000077

/*
 * fsखोलो() flags.
 */
#घोषणा FSOPEN_CLOEXEC		0x00000001

/*
 * fspick() flags.
 */
#घोषणा FSPICK_CLOEXEC		0x00000001
#घोषणा FSPICK_SYMLINK_NOFOLLOW	0x00000002
#घोषणा FSPICK_NO_AUTOMOUNT	0x00000004
#घोषणा FSPICK_EMPTY_PATH	0x00000008

/*
 * The type of fsconfig() call made.
 */
क्रमागत fsconfig_command अणु
	FSCONFIG_SET_FLAG	= 0,	/* Set parameter, supplying no value */
	FSCONFIG_SET_STRING	= 1,	/* Set parameter, supplying a string value */
	FSCONFIG_SET_BINARY	= 2,	/* Set parameter, supplying a binary blob value */
	FSCONFIG_SET_PATH	= 3,	/* Set parameter, supplying an object by path */
	FSCONFIG_SET_PATH_EMPTY	= 4,	/* Set parameter, supplying an object by (empty) path */
	FSCONFIG_SET_FD		= 5,	/* Set parameter, supplying an object by fd */
	FSCONFIG_CMD_CREATE	= 6,	/* Invoke superblock creation */
	FSCONFIG_CMD_RECONFIGURE = 7,	/* Invoke superblock reconfiguration */
पूर्ण;

/*
 * fsmount() flags.
 */
#घोषणा FSMOUNT_CLOEXEC		0x00000001

/*
 * Mount attributes.
 */
#घोषणा MOUNT_ATTR_RDONLY	0x00000001 /* Mount पढ़ो-only */
#घोषणा MOUNT_ATTR_NOSUID	0x00000002 /* Ignore suid and sgid bits */
#घोषणा MOUNT_ATTR_NODEV	0x00000004 /* Disallow access to device special files */
#घोषणा MOUNT_ATTR_NOEXEC	0x00000008 /* Disallow program execution */
#घोषणा MOUNT_ATTR__ATIME	0x00000070 /* Setting on how aसमय should be updated */
#घोषणा MOUNT_ATTR_RELATIME	0x00000000 /* - Update aसमय relative to mसमय/स_समय. */
#घोषणा MOUNT_ATTR_NOATIME	0x00000010 /* - Do not update access बार. */
#घोषणा MOUNT_ATTR_STRICTATIME	0x00000020 /* - Always perक्रमm aसमय updates */
#घोषणा MOUNT_ATTR_NOसूचीATIME	0x00000080 /* Do not update directory access बार */
#घोषणा MOUNT_ATTR_IDMAP	0x00100000 /* Idmap mount to @userns_fd in काष्ठा mount_attr. */

/*
 * mount_setattr()
 */
काष्ठा mount_attr अणु
	__u64 attr_set;
	__u64 attr_clr;
	__u64 propagation;
	__u64 userns_fd;
पूर्ण;

/* List of all mount_attr versions. */
#घोषणा MOUNT_ATTR_SIZE_VER0	32 /* माप first published काष्ठा */

#पूर्ण_अगर /* _UAPI_LINUX_MOUNT_H */
