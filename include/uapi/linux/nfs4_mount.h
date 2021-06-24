<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_NFS4_MOUNT_H
#घोषणा _LINUX_NFS4_MOUNT_H

/*
 *  linux/include/linux/nfs4_mount.h
 *
 *  Copyright (C) 2002  Trond Myklebust
 *
 *  काष्ठाure passed from user-space to kernel-space during an nfsv4 mount
 */

/*
 * WARNING!  Do not delete or change the order of these fields.  If
 * a new field is required then add it to the end.  The version field
 * tracks which fields are present.  This will ensure some measure of
 * mount-to-kernel version compatibility.  Some of these aren't used yet
 * but here they are anyway.
 */
#घोषणा NFS4_MOUNT_VERSION	1

काष्ठा nfs_string अणु
	अचिन्हित पूर्णांक len;
	स्थिर अक्षर __user * data;
पूर्ण;

काष्ठा nfs4_mount_data अणु
	पूर्णांक version;				/* 1 */
	पूर्णांक flags;				/* 1 */
	पूर्णांक rsize;				/* 1 */
	पूर्णांक wsize;				/* 1 */
	पूर्णांक समयo;				/* 1 */
	पूर्णांक retrans;				/* 1 */
	पूर्णांक acregmin;				/* 1 */
	पूर्णांक acregmax;				/* 1 */
	पूर्णांक acdirmin;				/* 1 */
	पूर्णांक acdirmax;				/* 1 */

	/* see the definition of 'struct clientaddr4' in RFC3010 */
	काष्ठा nfs_string client_addr;		/* 1 */

	/* Mount path */
	काष्ठा nfs_string mnt_path;		/* 1 */

	/* Server details */
	काष्ठा nfs_string hostname;		/* 1 */
	/* Server IP address */
	अचिन्हित पूर्णांक host_addrlen;		/* 1 */
	काष्ठा sockaddr __user * host_addr;	/* 1 */

	/* Transport protocol to use */
	पूर्णांक proto;				/* 1 */

	/* Pseuकरो-flavours to use क्रम authentication. See RFC2623 */
	पूर्णांक auth_flavourlen;			/* 1 */
	पूर्णांक __user *auth_flavours;		/* 1 */
पूर्ण;

/* bits in the flags field */
/* Note: the fields that correspond to existing NFSv2/v3 mount options
 * 	 should mirror the values from include/linux/nfs_mount.h
 */

#घोषणा NFS4_MOUNT_SOFT		0x0001	/* 1 */
#घोषणा NFS4_MOUNT_INTR		0x0002	/* 1 */
#घोषणा NFS4_MOUNT_NOCTO	0x0010	/* 1 */
#घोषणा NFS4_MOUNT_NOAC		0x0020	/* 1 */
#घोषणा NFS4_MOUNT_STRICTLOCK	0x1000	/* 1 */
#घोषणा NFS4_MOUNT_UNSHARED	0x8000	/* 1 */
#घोषणा NFS4_MOUNT_FLAGMASK	0x9033

#पूर्ण_अगर
