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

#अगर_अघोषित __DLMCONSTANTS_DOT_H__
#घोषणा __DLMCONSTANTS_DOT_H__

/*
 * Constants used by DLM पूर्णांकerface.
 */

#घोषणा DLM_LOCKSPACE_LEN       64
#घोषणा DLM_RESNAME_MAXLEN      64


/*
 * Lock Modes
 */

#घोषणा DLM_LOCK_IV		(-1)	/* invalid */
#घोषणा DLM_LOCK_NL		0	/* null */
#घोषणा DLM_LOCK_CR		1	/* concurrent पढ़ो */
#घोषणा DLM_LOCK_CW		2	/* concurrent ग_लिखो */
#घोषणा DLM_LOCK_PR		3	/* रक्षित पढ़ो */
#घोषणा DLM_LOCK_PW		4	/* रक्षित ग_लिखो */
#घोषणा DLM_LOCK_EX		5	/* exclusive */


/*
 * Flags to dlm_lock
 *
 * DLM_LKF_NOQUEUE
 *
 * Do not queue the lock request on the रुको queue अगर it cannot be granted
 * immediately.  If the lock cannot be granted because of this flag, DLM will
 * either वापस -EAGAIN from the dlm_lock call or will वापस 0 from
 * dlm_lock and -EAGAIN in the lock status block when the AST is executed.
 *
 * DLM_LKF_CANCEL
 *
 * Used to cancel a pending lock request or conversion.  A converting lock is
 * वापसed to its previously granted mode.
 *
 * DLM_LKF_CONVERT
 *
 * Indicates a lock conversion request.  For conversions the name and namelen
 * are ignored and the lock ID in the LKSB is used to identअगरy the lock.
 *
 * DLM_LKF_VALBLK
 *
 * Requests DLM to वापस the current contents of the lock value block in the
 * lock status block.  When this flag is set in a lock conversion from PW or EX
 * modes, DLM assigns the value specअगरied in the lock status block to the lock
 * value block of the lock resource.  The LVB is a DLM_LVB_LEN size array
 * containing application-specअगरic inक्रमmation.
 *
 * DLM_LKF_QUECVT
 *
 * Force a conversion request to be queued, even अगर it is compatible with
 * the granted modes of other locks on the same resource.
 *
 * DLM_LKF_IVVALBLK
 *
 * Invalidate the lock value block.
 *
 * DLM_LKF_CONVDEADLK
 *
 * Allows the dlm to resolve conversion deadlocks पूर्णांकernally by demoting the
 * granted mode of a converting lock to NL.  The DLM_SBF_DEMOTED flag is
 * वापसed क्रम a conversion that's been effected by this.
 *
 * DLM_LKF_PERSISTENT
 *
 * Only relevant to locks originating in userspace.  A persistent lock will not
 * be हटाओd अगर the process holding the lock निकासs.
 *
 * DLM_LKF_NODLCKWT
 *
 * Do not cancel the lock अगर it माला_लो पूर्णांकo conversion deadlock.
 * Exclude this lock from being monitored due to DLM_LSFL_TIMEWARN.
 *
 * DLM_LKF_NODLCKBLK
 *
 * net yet implemented
 *
 * DLM_LKF_EXPEDITE
 *
 * Used only with new requests क्रम NL mode locks.  Tells the lock manager
 * to grant the lock, ignoring other locks in convert and रुको queues.
 *
 * DLM_LKF_NOQUEUEBAST
 *
 * Send blocking AST's beक्रमe वापसing -EAGAIN to the caller.  It is only
 * used aदीर्घ with the NOQUEUE flag.  Blocking AST's are not sent क्रम failed
 * NOQUEUE requests otherwise.
 *
 * DLM_LKF_HEADQUE
 *
 * Add a lock to the head of the convert or रुको queue rather than the tail.
 *
 * DLM_LKF_NOORDER
 *
 * Disregard the standard grant order rules and grant a lock as soon as it
 * is compatible with other granted locks.
 *
 * DLM_LKF_ORPHAN
 *
 * Acquire an orphan lock.
 *
 * DLM_LKF_ALTPR
 *
 * If the requested mode cannot be granted immediately, try to grant the lock
 * in PR mode instead.  If this alternate mode is granted instead of the
 * requested mode, DLM_SBF_ALTMODE is वापसed in the lksb.
 *
 * DLM_LKF_ALTCW
 *
 * The same as ALTPR, but the alternate mode is CW.
 *
 * DLM_LKF_FORCEUNLOCK
 *
 * Unlock the lock even अगर it is converting or रुकोing or has sublocks.
 * Only really क्रम use by the userland device.c code.
 *
 */

#घोषणा DLM_LKF_NOQUEUE		0x00000001
#घोषणा DLM_LKF_CANCEL		0x00000002
#घोषणा DLM_LKF_CONVERT		0x00000004
#घोषणा DLM_LKF_VALBLK		0x00000008
#घोषणा DLM_LKF_QUECVT		0x00000010
#घोषणा DLM_LKF_IVVALBLK	0x00000020
#घोषणा DLM_LKF_CONVDEADLK	0x00000040
#घोषणा DLM_LKF_PERSISTENT	0x00000080
#घोषणा DLM_LKF_NODLCKWT	0x00000100
#घोषणा DLM_LKF_NODLCKBLK	0x00000200
#घोषणा DLM_LKF_EXPEDITE	0x00000400
#घोषणा DLM_LKF_NOQUEUEBAST	0x00000800
#घोषणा DLM_LKF_HEADQUE		0x00001000
#घोषणा DLM_LKF_NOORDER		0x00002000
#घोषणा DLM_LKF_ORPHAN		0x00004000
#घोषणा DLM_LKF_ALTPR		0x00008000
#घोषणा DLM_LKF_ALTCW		0x00010000
#घोषणा DLM_LKF_FORCEUNLOCK	0x00020000
#घोषणा DLM_LKF_TIMEOUT		0x00040000

/*
 * Some वापस codes that are not in त्रुटिसं.स
 */

#घोषणा DLM_ECANCEL		0x10001
#घोषणा DLM_EUNLOCK		0x10002

#पूर्ण_अगर  /* __DLMCONSTANTS_DOT_H__ */
