<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * IOCTLs क्रम Remoteproc's अक्षरacter device पूर्णांकerface.
 *
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _UAPI_REMOTEPROC_CDEV_H_
#घोषणा _UAPI_REMOTEPROC_CDEV_H_

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा RPROC_MAGIC	0xB7

/*
 * The RPROC_SET_SHUTDOWN_ON_RELEASE ioctl allows to enable/disable the shutकरोwn of a remote
 * processor स्वतःmatically when the controlling userpsace बंदs the अक्षर device पूर्णांकerface.
 *
 * input parameter: पूर्णांकeger
 *   0		: disable स्वतःmatic shutकरोwn
 *   other	: enable स्वतःmatic shutकरोwn
 */
#घोषणा RPROC_SET_SHUTDOWN_ON_RELEASE _IOW(RPROC_MAGIC, 1, __s32)

/*
 * The RPROC_GET_SHUTDOWN_ON_RELEASE ioctl माला_लो inक्रमmation about whether the स्वतःmatic shutकरोwn of
 * a remote processor is enabled or disabled when the controlling userspace बंदs the अक्षर device
 * पूर्णांकerface.
 *
 * output parameter: पूर्णांकeger
 *   0		: स्वतःmatic shutकरोwn disable
 *   other	: स्वतःmatic shutकरोwn enable
 */
#घोषणा RPROC_GET_SHUTDOWN_ON_RELEASE _IOR(RPROC_MAGIC, 2, __s32)

#पूर्ण_अगर
