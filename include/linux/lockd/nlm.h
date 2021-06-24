<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/lockd/nlm.h
 *
 * Declarations क्रम the Network Lock Manager protocol.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित LINUX_LOCKD_NLM_H
#घोषणा LINUX_LOCKD_NLM_H


/* Maximum file offset in file_lock.fl_end */
# define NLM_OFFSET_MAX		((s32) 0x7fffffff)
# define NLM4_OFFSET_MAX	((s64) ((~(u64)0) >> 1))

/* Return states क्रम NLM */
क्रमागत अणु
	NLM_LCK_GRANTED			= 0,
	NLM_LCK_DENIED			= 1,
	NLM_LCK_DENIED_NOLOCKS		= 2,
	NLM_LCK_BLOCKED			= 3,
	NLM_LCK_DENIED_GRACE_PERIOD	= 4,
#अगर_घोषित CONFIG_LOCKD_V4
	NLM_DEADLCK			= 5,
	NLM_ROFS			= 6,
	NLM_STALE_FH			= 7,
	NLM_FBIG			= 8,
	NLM_FAILED			= 9,
#पूर्ण_अगर
पूर्ण;

#घोषणा NLM_PROGRAM		100021

#घोषणा NLMPROC_शून्य		0
#घोषणा NLMPROC_TEST		1
#घोषणा NLMPROC_LOCK		2
#घोषणा NLMPROC_CANCEL		3
#घोषणा NLMPROC_UNLOCK		4
#घोषणा NLMPROC_GRANTED		5
#घोषणा NLMPROC_TEST_MSG	6
#घोषणा NLMPROC_LOCK_MSG	7
#घोषणा NLMPROC_CANCEL_MSG	8
#घोषणा NLMPROC_UNLOCK_MSG	9
#घोषणा NLMPROC_GRANTED_MSG	10
#घोषणा NLMPROC_TEST_RES	11
#घोषणा NLMPROC_LOCK_RES	12
#घोषणा NLMPROC_CANCEL_RES	13
#घोषणा NLMPROC_UNLOCK_RES	14
#घोषणा NLMPROC_GRANTED_RES	15
#घोषणा NLMPROC_NSM_NOTIFY	16		/* statd callback */
#घोषणा NLMPROC_SHARE		20
#घोषणा NLMPROC_UNSHARE		21
#घोषणा NLMPROC_NM_LOCK		22
#घोषणा NLMPROC_FREE_ALL	23

#पूर्ण_अगर /* LINUX_LOCKD_NLM_H */
