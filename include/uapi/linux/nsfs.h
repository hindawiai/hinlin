<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_NSFS_H
#घोषणा __LINUX_NSFS_H

#समावेश <linux/ioctl.h>

#घोषणा NSIO	0xb7

/* Returns a file descriptor that refers to an owning user namespace */
#घोषणा NS_GET_USERNS		_IO(NSIO, 0x1)
/* Returns a file descriptor that refers to a parent namespace */
#घोषणा NS_GET_PARENT		_IO(NSIO, 0x2)
/* Returns the type of namespace (CLONE_NEW* value) referred to by
   file descriptor */
#घोषणा NS_GET_NSTYPE		_IO(NSIO, 0x3)
/* Get owner UID (in the caller's user namespace) क्रम a user namespace */
#घोषणा NS_GET_OWNER_UID	_IO(NSIO, 0x4)

#पूर्ण_अगर /* __LINUX_NSFS_H */
