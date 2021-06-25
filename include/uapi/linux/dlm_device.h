<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2007 Red Hat, Inc.  All rights reserved.
**
**  This copyrighted material is made available to anyone wishing to use,
**  modअगरy, copy, or redistribute it subject to the terms and conditions
**  of the GNU General Public License v.2.
**
*******************************************************************************
******************************************************************************/

#अगर_अघोषित _LINUX_DLM_DEVICE_H
#घोषणा _LINUX_DLM_DEVICE_H

/* This is the device पूर्णांकerface क्रम dlm, most users will use a library
 * पूर्णांकerface.
 */

#समावेश <linux/dlm.h>
#समावेश <linux/types.h>

#घोषणा DLM_USER_LVB_LEN	32

/* Version of the device पूर्णांकerface */
#घोषणा DLM_DEVICE_VERSION_MAJOR 6
#घोषणा DLM_DEVICE_VERSION_MINOR 0
#घोषणा DLM_DEVICE_VERSION_PATCH 2

/* काष्ठा passed to the lock ग_लिखो */
काष्ठा dlm_lock_params अणु
	__u8 mode;
	__u8 namelen;
	__u16 unused;
	__u32 flags;
	__u32 lkid;
	__u32 parent;
	__u64 xid;
	__u64 समयout;
	व्योम __user *castparam;
	व्योम __user *castaddr;
	व्योम __user *bastparam;
	व्योम __user *bastaddr;
	काष्ठा dlm_lksb __user *lksb;
	अक्षर lvb[DLM_USER_LVB_LEN];
	अक्षर name[0];
पूर्ण;

काष्ठा dlm_lspace_params अणु
	__u32 flags;
	__u32 minor;
	अक्षर name[0];
पूर्ण;

काष्ठा dlm_purge_params अणु
	__u32 nodeid;
	__u32 pid;
पूर्ण;

काष्ठा dlm_ग_लिखो_request अणु
	__u32 version[3];
	__u8 cmd;
	__u8 is64bit;
	__u8 unused[2];

	जोड़  अणु
		काष्ठा dlm_lock_params   lock;
		काष्ठा dlm_lspace_params lspace;
		काष्ठा dlm_purge_params  purge;
	पूर्ण i;
पूर्ण;

काष्ठा dlm_device_version अणु
	__u32 version[3];
पूर्ण;

/* काष्ठा पढ़ो from the "device" fd,
   consists मुख्यly of userspace poपूर्णांकers क्रम the library to use */

काष्ठा dlm_lock_result अणु
	__u32 version[3];
	__u32 length;
	व्योम __user * user_astaddr;
	व्योम __user * user_astparam;
	काष्ठा dlm_lksb __user * user_lksb;
	काष्ठा dlm_lksb lksb;
	__u8 bast_mode;
	__u8 unused[3];
	/* Offsets may be zero अगर no data is present */
	__u32 lvb_offset;
पूर्ण;

/* Commands passed to the device */
#घोषणा DLM_USER_LOCK         1
#घोषणा DLM_USER_UNLOCK       2
#घोषणा DLM_USER_QUERY        3
#घोषणा DLM_USER_CREATE_LOCKSPACE  4
#घोषणा DLM_USER_REMOVE_LOCKSPACE  5
#घोषणा DLM_USER_PURGE        6
#घोषणा DLM_USER_DEADLOCK     7

/* Lockspace flags */
#घोषणा DLM_USER_LSFLG_AUTOFREE   1
#घोषणा DLM_USER_LSFLG_FORCEFREE  2

#पूर्ण_अगर

