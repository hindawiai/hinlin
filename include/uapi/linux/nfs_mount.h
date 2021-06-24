<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_NFS_MOUNT_H
#घोषणा _LINUX_NFS_MOUNT_H

/*
 *  linux/include/linux/nfs_mount.h
 *
 *  Copyright (C) 1992  Rick Sladkey
 *
 *  काष्ठाure passed from user-space to kernel-space during an nfs mount
 */
#समावेश <linux/in.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs2.h>
#समावेश <linux/nfs3.h>

/*
 * WARNING!  Do not delete or change the order of these fields.  If
 * a new field is required then add it to the end.  The version field
 * tracks which fields are present.  This will ensure some measure of
 * mount-to-kernel version compatibility.  Some of these aren't used yet
 * but here they are anyway.
 */
#घोषणा NFS_MOUNT_VERSION	6
#घोषणा NFS_MAX_CONTEXT_LEN	256

काष्ठा nfs_mount_data अणु
	पूर्णांक		version;		/* 1 */
	पूर्णांक		fd;			/* 1 */
	काष्ठा nfs2_fh	old_root;		/* 1 */
	पूर्णांक		flags;			/* 1 */
	पूर्णांक		rsize;			/* 1 */
	पूर्णांक		wsize;			/* 1 */
	पूर्णांक		समयo;			/* 1 */
	पूर्णांक		retrans;		/* 1 */
	पूर्णांक		acregmin;		/* 1 */
	पूर्णांक		acregmax;		/* 1 */
	पूर्णांक		acdirmin;		/* 1 */
	पूर्णांक		acdirmax;		/* 1 */
	काष्ठा sockaddr_in addr;		/* 1 */
	अक्षर		hostname[NFS_MAXNAMLEN + 1];		/* 1 */
	पूर्णांक		namlen;			/* 2 */
	अचिन्हित पूर्णांक	bsize;			/* 3 */
	काष्ठा nfs3_fh	root;			/* 4 */
	पूर्णांक		pseuकरोflavor;		/* 5 */
	अक्षर		context[NFS_MAX_CONTEXT_LEN + 1];	/* 6 */
पूर्ण;

/* bits in the flags field visible to user space */

#घोषणा NFS_MOUNT_SOFT		0x0001	/* 1 */
#घोषणा NFS_MOUNT_INTR		0x0002	/* 1 */ /* now unused, but ABI */
#घोषणा NFS_MOUNT_SECURE	0x0004	/* 1 */
#घोषणा NFS_MOUNT_POSIX		0x0008	/* 1 */
#घोषणा NFS_MOUNT_NOCTO		0x0010	/* 1 */
#घोषणा NFS_MOUNT_NOAC		0x0020	/* 1 */
#घोषणा NFS_MOUNT_TCP		0x0040	/* 2 */
#घोषणा NFS_MOUNT_VER3		0x0080	/* 3 */
#घोषणा NFS_MOUNT_KERBEROS	0x0100	/* 3 */
#घोषणा NFS_MOUNT_NONLM		0x0200	/* 3 */
#घोषणा NFS_MOUNT_BROKEN_SUID	0x0400	/* 4 */
#घोषणा NFS_MOUNT_NOACL		0x0800	/* 4 */
#घोषणा NFS_MOUNT_STRICTLOCK	0x1000	/* reserved क्रम NFSv4 */
#घोषणा NFS_MOUNT_SECFLAVOUR	0x2000	/* 5 non-text parsed mount data only */
#घोषणा NFS_MOUNT_NORसूचीPLUS	0x4000	/* 5 */
#घोषणा NFS_MOUNT_UNSHARED	0x8000	/* 5 */
#घोषणा NFS_MOUNT_FLAGMASK	0xFFFF

#पूर्ण_अगर
