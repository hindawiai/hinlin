<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* Copyright (c) 2015 6WIND S.A.
 * Author: Nicolas Dichtel <nicolas.dichtel@6wind.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */
#अगर_अघोषित _UAPI_LINUX_NET_NAMESPACE_H_
#घोषणा _UAPI_LINUX_NET_NAMESPACE_H_

/* Attributes of RTM_NEWNSID/RTM_GETNSID messages */
क्रमागत अणु
	NETNSA_NONE,
#घोषणा NETNSA_NSID_NOT_ASSIGNED -1
	NETNSA_NSID,
	NETNSA_PID,
	NETNSA_FD,
	NETNSA_TARGET_NSID,
	NETNSA_CURRENT_NSID,
	__NETNSA_MAX,
पूर्ण;

#घोषणा NETNSA_MAX		(__NETNSA_MAX - 1)

#पूर्ण_अगर /* _UAPI_LINUX_NET_NAMESPACE_H_ */
