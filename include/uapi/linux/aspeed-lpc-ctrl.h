<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright 2017 IBM Corp.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_LINUX_ASPEED_LPC_CTRL_H
#घोषणा _UAPI_LINUX_ASPEED_LPC_CTRL_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/* Winकरोw types */
#घोषणा ASPEED_LPC_CTRL_WINDOW_FLASH	1
#घोषणा ASPEED_LPC_CTRL_WINDOW_MEMORY	2

/*
 * This driver provides a winकरोw क्रम the host to access a BMC resource
 * across the BMC <-> Host LPC bus.
 *
 * winकरोw_type: The BMC resource that the host will access through the
 * winकरोw. BMC flash and BMC RAM.
 *
 * winकरोw_id: For each winकरोw type there may be multiple winकरोws,
 * these are referenced by ID.
 *
 * flags: Reserved क्रम future use, this field is expected to be
 * zeroed.
 *
 * addr: Address on the host LPC bus that the specअगरied winकरोw should
 * be mapped. This address must be घातer of two aligned.
 *
 * offset: Offset पूर्णांकo the BMC winकरोw that should be mapped to the
 * host (at addr). This must be a multiple of size.
 *
 * size: The size of the mapping. The smallest possible size is 64K.
 * This must be घातer of two aligned.
 *
 */

काष्ठा aspeed_lpc_ctrl_mapping अणु
	__u8	winकरोw_type;
	__u8	winकरोw_id;
	__u16	flags;
	__u32	addr;
	__u32	offset;
	__u32	size;
पूर्ण;

#घोषणा __ASPEED_LPC_CTRL_IOCTL_MAGIC	0xb2

#घोषणा ASPEED_LPC_CTRL_IOCTL_GET_SIZE	_IOWR(__ASPEED_LPC_CTRL_IOCTL_MAGIC, \
		0x00, काष्ठा aspeed_lpc_ctrl_mapping)

#घोषणा ASPEED_LPC_CTRL_IOCTL_MAP	_IOW(__ASPEED_LPC_CTRL_IOCTL_MAGIC, \
		0x01, काष्ठा aspeed_lpc_ctrl_mapping)

#पूर्ण_अगर /* _UAPI_LINUX_ASPEED_LPC_CTRL_H */
