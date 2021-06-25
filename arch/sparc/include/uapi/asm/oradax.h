<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later WITH Linux-syscall-note */
/*
 * Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Oracle DAX driver API definitions
 */

#अगर_अघोषित _ORADAX_H
#घोषणा	_ORADAX_H

#समावेश <linux/types.h>

#घोषणा	CCB_KILL 0
#घोषणा	CCB_INFO 1
#घोषणा	CCB_DEQUEUE 2

काष्ठा dax_command अणु
	__u16 command;		/* CCB_KILL/INFO/DEQUEUE */
	__u16 ca_offset;	/* offset पूर्णांकo mmapped completion area */
पूर्ण;

काष्ठा ccb_समाप्त_result अणु
	__u16 action;		/* action taken to समाप्त ccb */
पूर्ण;

काष्ठा ccb_info_result अणु
	__u16 state;		/* state of enqueued ccb */
	__u16 inst_num;		/* dax instance number of enqueued ccb */
	__u16 q_num;		/* queue number of enqueued ccb */
	__u16 q_pos;		/* ccb position in queue */
पूर्ण;

काष्ठा ccb_exec_result अणु
	__u64	status_data;	/* additional status data (e.g. bad VA) */
	__u32	status;		/* one of DAX_SUBMIT_* */
पूर्ण;

जोड़ ccb_result अणु
	काष्ठा ccb_exec_result exec;
	काष्ठा ccb_info_result info;
	काष्ठा ccb_समाप्त_result समाप्त;
पूर्ण;

#घोषणा	DAX_MMAP_LEN		(16 * 1024)
#घोषणा	DAX_MAX_CCBS		15
#घोषणा	DAX_CCB_BUF_MAXLEN	(DAX_MAX_CCBS * 64)
#घोषणा	DAX_NAME		"oradax"

/* CCB_EXEC status */
#घोषणा	DAX_SUBMIT_OK			0
#घोषणा	DAX_SUBMIT_ERR_RETRY		1
#घोषणा	DAX_SUBMIT_ERR_WOULDBLOCK	2
#घोषणा	DAX_SUBMIT_ERR_BUSY		3
#घोषणा	DAX_SUBMIT_ERR_THR_INIT		4
#घोषणा	DAX_SUBMIT_ERR_ARG_INVAL	5
#घोषणा	DAX_SUBMIT_ERR_CCB_INVAL	6
#घोषणा	DAX_SUBMIT_ERR_NO_CA_AVAIL	7
#घोषणा	DAX_SUBMIT_ERR_CCB_ARR_MMU_MISS	8
#घोषणा	DAX_SUBMIT_ERR_NOMAP		9
#घोषणा	DAX_SUBMIT_ERR_NOACCESS		10
#घोषणा	DAX_SUBMIT_ERR_TOOMANY		11
#घोषणा	DAX_SUBMIT_ERR_UNAVAIL		12
#घोषणा	DAX_SUBMIT_ERR_INTERNAL		13

/* CCB_INFO states - must match HV_CCB_STATE_* definitions */
#घोषणा	DAX_CCB_COMPLETED	0
#घोषणा	DAX_CCB_ENQUEUED	1
#घोषणा	DAX_CCB_INPROGRESS	2
#घोषणा	DAX_CCB_NOTFOUND	3

/* CCB_KILL actions - must match HV_CCB_KILL_* definitions */
#घोषणा	DAX_KILL_COMPLETED	0
#घोषणा	DAX_KILL_DEQUEUED	1
#घोषणा	DAX_KILL_KILLED		2
#घोषणा	DAX_KILL_NOTFOUND	3

#पूर्ण_अगर /* _ORADAX_H */
