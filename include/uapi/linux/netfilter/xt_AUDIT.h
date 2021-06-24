<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Header file क्रम iptables xt_AUDIT target
 *
 * (C) 2010-2011 Thomas Graf <tgraf@redhat.com>
 * (C) 2010-2011 Red Hat, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित _XT_AUDIT_TARGET_H
#घोषणा _XT_AUDIT_TARGET_H

#समावेश <linux/types.h>

क्रमागत अणु
	XT_AUDIT_TYPE_ACCEPT = 0,
	XT_AUDIT_TYPE_DROP,
	XT_AUDIT_TYPE_REJECT,
	__XT_AUDIT_TYPE_MAX,
पूर्ण;

#घोषणा XT_AUDIT_TYPE_MAX (__XT_AUDIT_TYPE_MAX - 1)

काष्ठा xt_audit_info अणु
	__u8 type; /* XT_AUDIT_TYPE_* */
पूर्ण;

#पूर्ण_अगर /* _XT_AUDIT_TARGET_H */
