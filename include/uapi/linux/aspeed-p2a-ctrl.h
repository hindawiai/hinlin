<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright 2019 Google Inc
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 * Provides a simple driver to control the ASPEED P2A पूर्णांकerface which allows
 * the host to पढ़ो and ग_लिखो to various regions of the BMC's memory.
 */

#अगर_अघोषित _UAPI_LINUX_ASPEED_P2A_CTRL_H
#घोषणा _UAPI_LINUX_ASPEED_P2A_CTRL_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा ASPEED_P2A_CTRL_READ_ONLY 0
#घोषणा ASPEED_P2A_CTRL_READWRITE 1

/*
 * This driver provides a mechanism क्रम enabling or disabling the पढ़ो-ग_लिखो
 * property of specअगरic winकरोws पूर्णांकo the ASPEED BMC's memory.
 *
 * A user can map a region of the BMC's memory as पढ़ो-only or पढ़ो-ग_लिखो, with
 * the caveat that once any region is mapped, all regions are unlocked क्रम
 * पढ़ोing.
 */

/*
 * Unlock a region of BMC physical memory क्रम access from the host.
 *
 * Also used to पढ़ो back the optional memory-region configuration क्रम the
 * driver.
 */
काष्ठा aspeed_p2a_ctrl_mapping अणु
	__u64 addr;
	__u32 length;
	__u32 flags;
पूर्ण;

#घोषणा __ASPEED_P2A_CTRL_IOCTL_MAGIC 0xb3

/*
 * This IOCTL is meant to configure a region or regions of memory given a
 * starting address and length to be पढ़ोable by the host, or
 * पढ़ोable-ग_लिखोable.
 */
#घोषणा ASPEED_P2A_CTRL_IOCTL_SET_WINDOW _IOW(__ASPEED_P2A_CTRL_IOCTL_MAGIC, \
		0x00, काष्ठा aspeed_p2a_ctrl_mapping)

/*
 * This IOCTL is meant to पढ़ो back to the user the base address and length of
 * the memory-region specअगरied to the driver क्रम use with mmap.
 */
#घोषणा ASPEED_P2A_CTRL_IOCTL_GET_MEMORY_CONFIG \
	_IOWR(__ASPEED_P2A_CTRL_IOCTL_MAGIC, \
		0x01, काष्ठा aspeed_p2a_ctrl_mapping)

#पूर्ण_अगर /* _UAPI_LINUX_ASPEED_P2A_CTRL_H */
