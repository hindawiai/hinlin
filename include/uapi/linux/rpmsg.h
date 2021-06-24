<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (c) 2016, Linaro Ltd.
 */

#अगर_अघोषित _UAPI_RPMSG_H_
#घोषणा _UAPI_RPMSG_H_

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा RPMSG_ADDR_ANY		0xFFFFFFFF

/**
 * काष्ठा rpmsg_endpoपूर्णांक_info - endpoपूर्णांक info representation
 * @name: name of service
 * @src: local address. To set to RPMSG_ADDR_ANY अगर not used.
 * @dst: destination address. To set to RPMSG_ADDR_ANY अगर not used.
 */
काष्ठा rpmsg_endpoपूर्णांक_info अणु
	अक्षर name[32];
	__u32 src;
	__u32 dst;
पूर्ण;

/**
 * Instantiate a new rmpsg अक्षर device endpoपूर्णांक.
 */
#घोषणा RPMSG_CREATE_EPT_IOCTL	_IOW(0xb5, 0x1, काष्ठा rpmsg_endpoपूर्णांक_info)

/**
 * Destroy a rpmsg अक्षर device endpoपूर्णांक created by the RPMSG_CREATE_EPT_IOCTL.
 */
#घोषणा RPMSG_DESTROY_EPT_IOCTL	_IO(0xb5, 0x2)

#पूर्ण_अगर
