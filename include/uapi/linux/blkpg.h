<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_BLKPG_H
#घोषणा _UAPI__LINUX_BLKPG_H

#समावेश <linux/compiler.h>
#समावेश <linux/ioctl.h>

#घोषणा BLKPG      _IO(0x12,105)

/* The argument काष्ठाure */
काष्ठा blkpg_ioctl_arg अणु
        पूर्णांक op;
        पूर्णांक flags;
        पूर्णांक datalen;
        व्योम __user *data;
पूर्ण;

/* The subfunctions (क्रम the op field) */
#घोषणा BLKPG_ADD_PARTITION	1
#घोषणा BLKPG_DEL_PARTITION	2
#घोषणा BLKPG_RESIZE_PARTITION	3

/* Sizes of name fields. Unused at present. */
#घोषणा BLKPG_DEVNAMELTH	64
#घोषणा BLKPG_VOLNAMELTH	64

/* The data काष्ठाure क्रम ADD_PARTITION and DEL_PARTITION */
काष्ठा blkpg_partition अणु
	दीर्घ दीर्घ start;		/* starting offset in bytes */
	दीर्घ दीर्घ length;		/* length in bytes */
	पूर्णांक pno;			/* partition number */
	अक्षर devname[BLKPG_DEVNAMELTH];	/* unused / ignored */
	अक्षर volname[BLKPG_VOLNAMELTH];	/* unused / ignore */
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_BLKPG_H */
