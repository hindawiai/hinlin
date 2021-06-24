<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2011 Red Hat, Inc.  All rights reserved.
**
**  This copyrighted material is made available to anyone wishing to use,
**  modअगरy, copy, or redistribute it subject to the terms and conditions
**  of the GNU General Public License v.2.
**
*******************************************************************************
******************************************************************************/

#अगर_अघोषित _UAPI__DLM_DOT_H__
#घोषणा _UAPI__DLM_DOT_H__

/*
 * Interface to Distributed Lock Manager (DLM)
 * routines and काष्ठाures to use DLM lockspaces
 */

/* Lock levels and flags are here */
#समावेश <linux/dlmस्थिरants.h>
#समावेश <linux/types.h>

प्रकार व्योम dlm_lockspace_t;

/*
 * Lock status block
 *
 * Use this काष्ठाure to specअगरy the contents of the lock value block.  For a
 * conversion request, this काष्ठाure is used to specअगरy the lock ID of the
 * lock.  DLM ग_लिखोs the status of the lock request and the lock ID asचिन्हित
 * to the request in the lock status block.
 *
 * sb_lkid: the वापसed lock ID.  It is set on new (non-conversion) requests.
 * It is available when dlm_lock वापसs.
 *
 * sb_lvbptr: saves or वापसs the contents of the lock's LVB according to rules
 * shown क्रम the DLM_LKF_VALBLK flag.
 *
 * sb_flags: DLM_SBF_DEMOTED is वापसed अगर in the process of promoting a lock,
 * it was first demoted to NL to aव्योम conversion deadlock.
 * DLM_SBF_VALNOTVALID is वापसed अगर the resource's LVB is marked invalid.
 *
 * sb_status: the वापसed status of the lock request set prior to AST
 * execution.  Possible वापस values:
 *
 * 0 अगर lock request was successful
 * -EAGAIN अगर request would block and is flagged DLM_LKF_NOQUEUE
 * -DLM_EUNLOCK अगर unlock request was successful
 * -DLM_ECANCEL अगर a cancel completed successfully
 * -EDEADLK अगर a deadlock was detected
 * -ETIMEDOUT अगर the lock request was canceled due to a समयout
 */

#घोषणा DLM_SBF_DEMOTED		0x01
#घोषणा DLM_SBF_VALNOTVALID	0x02
#घोषणा DLM_SBF_ALTMODE		0x04

काष्ठा dlm_lksb अणु
	पूर्णांक 	 sb_status;
	__u32	 sb_lkid;
	अक्षर 	 sb_flags;
	अक्षर *	 sb_lvbptr;
पूर्ण;

/* dlm_new_lockspace() flags */

#घोषणा DLM_LSFL_TIMEWARN	0x00000002
#घोषणा DLM_LSFL_FS     	0x00000004
#घोषणा DLM_LSFL_NEWEXCL     	0x00000008


#पूर्ण_अगर /* _UAPI__DLM_DOT_H__ */
