<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_SUSPEND_IOCTLS_H
#घोषणा _LINUX_SUSPEND_IOCTLS_H

#समावेश <linux/types.h>
/*
 * This काष्ठाure is used to pass the values needed क्रम the identअगरication
 * of the resume swap area from a user space to the kernel via the
 * SNAPSHOT_SET_SWAP_AREA ioctl
 */
काष्ठा resume_swap_area अणु
	__kernel_loff_t offset;
	__u32 dev;
पूर्ण __attribute__((packed));

#घोषणा SNAPSHOT_IOC_MAGIC	'3'
#घोषणा SNAPSHOT_FREEZE			_IO(SNAPSHOT_IOC_MAGIC, 1)
#घोषणा SNAPSHOT_UNFREEZE		_IO(SNAPSHOT_IOC_MAGIC, 2)
#घोषणा SNAPSHOT_ATOMIC_RESTORE		_IO(SNAPSHOT_IOC_MAGIC, 4)
#घोषणा SNAPSHOT_FREE			_IO(SNAPSHOT_IOC_MAGIC, 5)
#घोषणा SNAPSHOT_FREE_SWAP_PAGES	_IO(SNAPSHOT_IOC_MAGIC, 9)
#घोषणा SNAPSHOT_S2RAM			_IO(SNAPSHOT_IOC_MAGIC, 11)
#घोषणा SNAPSHOT_SET_SWAP_AREA		_IOW(SNAPSHOT_IOC_MAGIC, 13, \
							काष्ठा resume_swap_area)
#घोषणा SNAPSHOT_GET_IMAGE_SIZE		_IOR(SNAPSHOT_IOC_MAGIC, 14, __kernel_loff_t)
#घोषणा SNAPSHOT_PLATFORM_SUPPORT	_IO(SNAPSHOT_IOC_MAGIC, 15)
#घोषणा SNAPSHOT_POWER_OFF		_IO(SNAPSHOT_IOC_MAGIC, 16)
#घोषणा SNAPSHOT_CREATE_IMAGE		_IOW(SNAPSHOT_IOC_MAGIC, 17, पूर्णांक)
#घोषणा SNAPSHOT_PREF_IMAGE_SIZE	_IO(SNAPSHOT_IOC_MAGIC, 18)
#घोषणा SNAPSHOT_AVAIL_SWAP_SIZE	_IOR(SNAPSHOT_IOC_MAGIC, 19, __kernel_loff_t)
#घोषणा SNAPSHOT_ALLOC_SWAP_PAGE	_IOR(SNAPSHOT_IOC_MAGIC, 20, __kernel_loff_t)
#घोषणा SNAPSHOT_IOC_MAXNR	20

#पूर्ण_अगर /* _LINUX_SUSPEND_IOCTLS_H */
