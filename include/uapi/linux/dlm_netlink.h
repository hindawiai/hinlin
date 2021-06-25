<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2007 Red Hat, Inc.  All rights reserved.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modअगरy, copy, or redistribute it subject to the terms and conditions
 * of the GNU General Public License v.2.
 */

#अगर_अघोषित _DLM_NETLINK_H
#घोषणा _DLM_NETLINK_H

#समावेश <linux/types.h>
#समावेश <linux/dlmस्थिरants.h>

क्रमागत अणु
	DLM_STATUS_WAITING = 1,
	DLM_STATUS_GRANTED = 2,
	DLM_STATUS_CONVERT = 3,
पूर्ण;

#घोषणा DLM_LOCK_DATA_VERSION 1

काष्ठा dlm_lock_data अणु
	__u16 version;
	__u32 lockspace_id;
	पूर्णांक nodeid;
	पूर्णांक ownpid;
	__u32 id;
	__u32 remid;
	__u64 xid;
	__s8 status;
	__s8 grmode;
	__s8 rqmode;
	अचिन्हित दीर्घ बारtamp;
	पूर्णांक resource_namelen;
	अक्षर resource_name[DLM_RESNAME_MAXLEN];
पूर्ण;

क्रमागत अणु
	DLM_CMD_UNSPEC = 0,
	DLM_CMD_HELLO,		/* user->kernel */
	DLM_CMD_TIMEOUT,	/* kernel->user */
	__DLM_CMD_MAX,
पूर्ण;

#घोषणा DLM_CMD_MAX (__DLM_CMD_MAX - 1)

क्रमागत अणु
	DLM_TYPE_UNSPEC = 0,
	DLM_TYPE_LOCK,
	__DLM_TYPE_MAX,
पूर्ण;

#घोषणा DLM_TYPE_MAX (__DLM_TYPE_MAX - 1)

#घोषणा DLM_GENL_VERSION 0x1
#घोषणा DLM_GENL_NAME "DLM"

#पूर्ण_अगर /* _DLM_NETLINK_H */
