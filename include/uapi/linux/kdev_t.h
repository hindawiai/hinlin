<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_KDEV_T_H
#घोषणा _UAPI_LINUX_KDEV_T_H
#अगर_अघोषित __KERNEL__

/*
Some programs want their definitions of MAJOR and MINOR and MKDEV
from the kernel sources. These must be the बाह्यally visible ones.
*/
#घोषणा MAJOR(dev)	((dev)>>8)
#घोषणा MINOR(dev)	((dev) & 0xff)
#घोषणा MKDEV(ma,mi)	((ma)<<8 | (mi))
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _UAPI_LINUX_KDEV_T_H */
