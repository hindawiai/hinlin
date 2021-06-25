<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2005-2008 Red Hat, Inc.  All rights reserved.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modअगरy, copy, or redistribute it subject to the terms and conditions
 * of the GNU General Public License v.2.
 */

#अगर_अघोषित _UAPI__DLM_PLOCK_DOT_H__
#घोषणा _UAPI__DLM_PLOCK_DOT_H__

#समावेश <linux/types.h>

#घोषणा DLM_PLOCK_MISC_NAME		"dlm_plock"

#घोषणा DLM_PLOCK_VERSION_MAJOR	1
#घोषणा DLM_PLOCK_VERSION_MINOR	2
#घोषणा DLM_PLOCK_VERSION_PATCH	0

क्रमागत अणु
	DLM_PLOCK_OP_LOCK = 1,
	DLM_PLOCK_OP_UNLOCK,
	DLM_PLOCK_OP_GET,
पूर्ण;

#घोषणा DLM_PLOCK_FL_CLOSE 1

काष्ठा dlm_plock_info अणु
	__u32 version[3];
	__u8 optype;
	__u8 ex;
	__u8 रुको;
	__u8 flags;
	__u32 pid;
	__s32 nodeid;
	__s32 rv;
	__u32 fsid;
	__u64 number;
	__u64 start;
	__u64 end;
	__u64 owner;
पूर्ण;


#पूर्ण_अगर /* _UAPI__DLM_PLOCK_DOT_H__ */
