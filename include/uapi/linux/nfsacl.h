<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * File: linux/nfsacl.h
 *
 * (C) 2003 Andreas Gruenbacher <agruen@suse.de>
 */
#अगर_अघोषित _UAPI__LINUX_NFSACL_H
#घोषणा _UAPI__LINUX_NFSACL_H

#घोषणा NFS_ACL_PROGRAM	100227

#घोषणा ACLPROC2_शून्य		0
#घोषणा ACLPROC2_GETACL		1
#घोषणा ACLPROC2_SETACL		2
#घोषणा ACLPROC2_GETATTR	3
#घोषणा ACLPROC2_ACCESS		4

#घोषणा ACLPROC3_शून्य		0
#घोषणा ACLPROC3_GETACL		1
#घोषणा ACLPROC3_SETACL		2


/* Flags क्रम the getacl/setacl mode */
#घोषणा NFS_ACL			0x0001
#घोषणा NFS_ACLCNT		0x0002
#घोषणा NFS_DFACL		0x0004
#घोषणा NFS_DFACLCNT		0x0008
#घोषणा NFS_ACL_MASK		0x000f

/* Flag क्रम Default ACL entries */
#घोषणा NFS_ACL_DEFAULT		0x1000

#पूर्ण_अगर /* _UAPI__LINUX_NFSACL_H */
