<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BLKPG_H
#घोषणा _LINUX_BLKPG_H

/*
 * Partition table and disk geometry handling
 */

#समावेश <linux/compat.h>
#समावेश <uapi/linux/blkpg.h>

#अगर_घोषित CONFIG_COMPAT
/* For 32-bit/64-bit compatibility of काष्ठा blkpg_ioctl_arg */
काष्ठा blkpg_compat_ioctl_arg अणु
	compat_पूर्णांक_t op;
	compat_पूर्णांक_t flags;
	compat_पूर्णांक_t datalen;
	compat_uptr_t data;
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_BLKPG_H */
