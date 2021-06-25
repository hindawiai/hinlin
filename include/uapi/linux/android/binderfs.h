<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2018 Canonical Ltd.
 *
 */

#अगर_अघोषित _UAPI_LINUX_BINDERFS_H
#घोषणा _UAPI_LINUX_BINDERFS_H

#समावेश <linux/android/binder.h>
#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा BINDERFS_MAX_NAME 255

/**
 * काष्ठा binderfs_device - retrieve inक्रमmation about a new binder device
 * @name:   the name to use क्रम the new binderfs binder device
 * @major:  major number allocated क्रम binderfs binder devices
 * @minor:  minor number allocated क्रम the new binderfs binder device
 *
 */
काष्ठा binderfs_device अणु
	अक्षर name[BINDERFS_MAX_NAME + 1];
	__u32 major;
	__u32 minor;
पूर्ण;

/**
 * Allocate a new binder device.
 */
#घोषणा BINDER_CTL_ADD _IOWR('b', 1, काष्ठा binderfs_device)

#पूर्ण_अगर /* _UAPI_LINUX_BINDERFS_H */

