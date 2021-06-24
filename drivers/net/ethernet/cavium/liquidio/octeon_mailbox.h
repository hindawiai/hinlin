<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
#अगर_अघोषित __MAILBOX_H__
#घोषणा __MAILBOX_H__

/* Macros क्रम Mail Box Communication */

#घोषणा OCTEON_MBOX_DATA_MAX		32

#घोषणा OCTEON_VF_ACTIVE		0x1
#घोषणा OCTEON_VF_FLR_REQUEST		0x2
#घोषणा OCTEON_PF_CHANGED_VF_MACADDR	0x4
#घोषणा OCTEON_GET_VF_STATS		0x8

/*Macro क्रम Read acknowldgement*/
#घोषणा OCTEON_PFVFACK			0xffffffffffffffffULL
#घोषणा OCTEON_PFVFSIG			0x1122334455667788ULL
#घोषणा OCTEON_PFVFERR			0xDEADDEADDEADDEADULL

#घोषणा LIO_MBOX_WRITE_WAIT_CNT         1000
#घोषणा LIO_MBOX_WRITE_WAIT_TIME        msecs_to_jअगरfies(1)

क्रमागत octeon_mbox_cmd_status अणु
	OCTEON_MBOX_STATUS_SUCCESS = 0,
	OCTEON_MBOX_STATUS_FAILED = 1,
	OCTEON_MBOX_STATUS_BUSY = 2
पूर्ण;

क्रमागत octeon_mbox_message_type अणु
	OCTEON_MBOX_REQUEST = 0,
	OCTEON_MBOX_RESPONSE = 1
पूर्ण;

जोड़ octeon_mbox_message अणु
	u64 u64;
	काष्ठा अणु
		u16 type : 1;
		u16 resp_needed : 1;
		u16 cmd : 6;
		u16 len : 8;
		u8 params[6];
	पूर्ण s;
पूर्ण;

प्रकार व्योम (*octeon_mbox_callback_t)(व्योम *, व्योम *, व्योम *);

काष्ठा octeon_mbox_cmd अणु
	जोड़ octeon_mbox_message msg;
	u64 data[OCTEON_MBOX_DATA_MAX];
	u32 q_no;
	u32 recv_len;
	u32 recv_status;
	octeon_mbox_callback_t fn;
	व्योम *fn_arg;
पूर्ण;

क्रमागत octeon_mbox_state अणु
	OCTEON_MBOX_STATE_IDLE = 1,
	OCTEON_MBOX_STATE_REQUEST_RECEIVING = 2,
	OCTEON_MBOX_STATE_REQUEST_RECEIVED = 4,
	OCTEON_MBOX_STATE_RESPONSE_PENDING = 8,
	OCTEON_MBOX_STATE_RESPONSE_RECEIVING = 16,
	OCTEON_MBOX_STATE_RESPONSE_RECEIVED = 32,
	OCTEON_MBOX_STATE_ERROR = 64
पूर्ण;

काष्ठा octeon_mbox अणु
	/** A spinlock to protect access to this q_mbox. */
	spinlock_t lock;

	काष्ठा octeon_device *oct_dev;

	u32 q_no;

	क्रमागत octeon_mbox_state state;

	काष्ठा cavium_wk mbox_poll_wk;

	/** SLI_MAC_PF_MBOX_INT क्रम PF, SLI_PKT_MBOX_INT क्रम VF. */
	व्योम *mbox_पूर्णांक_reg;

	/** SLI_PKT_PF_VF_MBOX_SIG(0) क्रम PF, SLI_PKT_PF_VF_MBOX_SIG(1) क्रम VF.
	 */
	व्योम *mbox_ग_लिखो_reg;

	/** SLI_PKT_PF_VF_MBOX_SIG(1) क्रम PF, SLI_PKT_PF_VF_MBOX_SIG(0) क्रम VF.
	 */
	व्योम *mbox_पढ़ो_reg;

	काष्ठा octeon_mbox_cmd mbox_req;

	काष्ठा octeon_mbox_cmd mbox_resp;

पूर्ण;

काष्ठा oct_vf_stats_ctx अणु
	atomic_t status;
	काष्ठा oct_vf_stats *stats;
पूर्ण;

पूर्णांक octeon_mbox_पढ़ो(काष्ठा octeon_mbox *mbox);
पूर्णांक octeon_mbox_ग_लिखो(काष्ठा octeon_device *oct,
		      काष्ठा octeon_mbox_cmd *mbox_cmd);
पूर्णांक octeon_mbox_process_message(काष्ठा octeon_mbox *mbox);
पूर्णांक octeon_mbox_cancel(काष्ठा octeon_device *oct, पूर्णांक q_no);

#पूर्ण_अगर
