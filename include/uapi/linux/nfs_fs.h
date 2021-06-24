<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  linux/include/linux/nfs_fs.h
 *
 *  Copyright (C) 1992  Rick Sladkey
 *
 *  OS-specअगरic nfs fileप्रणाली definitions and declarations
 */

#अगर_अघोषित _UAPI_LINUX_NFS_FS_H
#घोषणा _UAPI_LINUX_NFS_FS_H

#समावेश <linux/magic.h>

/* Default समयout values */
#घोषणा NFS_DEF_UDP_TIMEO	(11)
#घोषणा NFS_DEF_UDP_RETRANS	(3)
#घोषणा NFS_DEF_TCP_TIMEO	(600)
#घोषणा NFS_DEF_TCP_RETRANS	(2)

#घोषणा NFS_MAX_UDP_TIMEOUT	(60*HZ)
#घोषणा NFS_MAX_TCP_TIMEOUT	(600*HZ)

#घोषणा NFS_DEF_ACREGMIN	(3)
#घोषणा NFS_DEF_ACREGMAX	(60)
#घोषणा NFS_DEF_ACसूचीMIN	(30)
#घोषणा NFS_DEF_ACसूचीMAX	(60)

/*
 * When flushing a cluster of dirty pages, there can be dअगरferent
 * strategies:
 */
#घोषणा FLUSH_SYNC		1	/* file being synced, or contention */
#घोषणा FLUSH_STABLE		4	/* commit to stable storage */
#घोषणा FLUSH_LOWPRI		8	/* low priority background flush */
#घोषणा FLUSH_HIGHPRI		16	/* high priority memory reclaim flush */
#घोषणा FLUSH_COND_STABLE	32	/* conditional stable ग_लिखो - only stable
					 * अगर everything fits in one RPC */


/*
 * NFS debug flags
 */
#घोषणा NFSDBG_VFS		0x0001
#घोषणा NFSDBG_सूचीCACHE		0x0002
#घोषणा NFSDBG_LOOKUPCACHE	0x0004
#घोषणा NFSDBG_PAGECACHE	0x0008
#घोषणा NFSDBG_PROC		0x0010
#घोषणा NFSDBG_XDR		0x0020
#घोषणा NFSDBG_खाता		0x0040
#घोषणा NFSDBG_ROOT		0x0080
#घोषणा NFSDBG_CALLBACK		0x0100
#घोषणा NFSDBG_CLIENT		0x0200
#घोषणा NFSDBG_MOUNT		0x0400
#घोषणा NFSDBG_FSCACHE		0x0800
#घोषणा NFSDBG_PNFS		0x1000
#घोषणा NFSDBG_PNFS_LD		0x2000
#घोषणा NFSDBG_STATE		0x4000
#घोषणा NFSDBG_XATTRCACHE	0x8000
#घोषणा NFSDBG_ALL		0xFFFF


#पूर्ण_अगर /* _UAPI_LINUX_NFS_FS_H */
