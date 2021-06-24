<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Netlink event notअगरications क्रम SELinux.
 *
 * Author: James Morris <jmorris@redhat.com>
 *
 * Copyright (C) 2004 Red Hat, Inc., James Morris <jmorris@redhat.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2,
 * as published by the Free Software Foundation.
 */
#अगर_अघोषित _LINUX_SELINUX_NETLINK_H
#घोषणा _LINUX_SELINUX_NETLINK_H

#समावेश <linux/types.h>

/* Message types. */
#घोषणा SELNL_MSG_BASE 0x10
क्रमागत अणु
	SELNL_MSG_SETENFORCE = SELNL_MSG_BASE,
	SELNL_MSG_POLICYLOAD,
	SELNL_MSG_MAX
पूर्ण;

#अगर_अघोषित __KERNEL__
/* Multicast groups - backwards compatiblility क्रम userspace */
#घोषणा SELNL_GRP_NONE		0x00000000
#घोषणा SELNL_GRP_AVC		0x00000001	/* AVC notअगरications */
#घोषणा SELNL_GRP_ALL		0xffffffff
#पूर्ण_अगर

क्रमागत selinux_nlgroups अणु
	SELNLGRP_NONE,
#घोषणा SELNLGRP_NONE	SELNLGRP_NONE
	SELNLGRP_AVC,
#घोषणा SELNLGRP_AVC	SELNLGRP_AVC
	__SELNLGRP_MAX
पूर्ण;
#घोषणा SELNLGRP_MAX	(__SELNLGRP_MAX - 1)

/* Message काष्ठाures */
काष्ठा selnl_msg_setenक्रमce अणु
	__s32		val;
पूर्ण;

काष्ठा selnl_msg_policyload अणु
	__u32	seqno;
पूर्ण;

#पूर्ण_अगर /* _LINUX_SELINUX_NETLINK_H */
