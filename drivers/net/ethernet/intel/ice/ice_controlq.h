<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_CONTROLQ_H_
#घोषणा _ICE_CONTROLQ_H_

#समावेश "ice_adminq_cmd.h"

/* Maximum buffer lengths क्रम all control queue types */
#घोषणा ICE_AQ_MAX_BUF_LEN 4096
#घोषणा ICE_MBXQ_MAX_BUF_LEN 4096

#घोषणा ICE_CTL_Q_DESC(R, i) \
	(&(((काष्ठा ice_aq_desc *)((R).desc_buf.va))[i]))

#घोषणा ICE_CTL_Q_DESC_UNUSED(R) \
	((u16)((((R)->next_to_clean > (R)->next_to_use) ? 0 : (R)->count) + \
	       (R)->next_to_clean - (R)->next_to_use - 1))

/* Defines that help manage the driver vs FW API checks.
 * Take a look at ice_aq_ver_check in ice_controlq.c क्रम actual usage.
 */
#घोषणा EXP_FW_API_VER_BRANCH		0x00
#घोषणा EXP_FW_API_VER_MAJOR		0x01
#घोषणा EXP_FW_API_VER_MINOR		0x05

/* Dअगरferent control queue types: These are मुख्यly क्रम SW consumption. */
क्रमागत ice_ctl_q अणु
	ICE_CTL_Q_UNKNOWN = 0,
	ICE_CTL_Q_ADMIN,
	ICE_CTL_Q_MAILBOX,
पूर्ण;

/* Control Queue समयout settings - max delay 1s */
#घोषणा ICE_CTL_Q_SQ_CMD_TIMEOUT	10000 /* Count 10000 बार */
#घोषणा ICE_CTL_Q_SQ_CMD_USEC		100   /* Check every 100usec */
#घोषणा ICE_CTL_Q_ADMIN_INIT_TIMEOUT	10    /* Count 10 बार */
#घोषणा ICE_CTL_Q_ADMIN_INIT_MSEC	100   /* Check every 100msec */

काष्ठा ice_ctl_q_ring अणु
	व्योम *dma_head;			/* Virtual address to DMA head */
	काष्ठा ice_dma_mem desc_buf;	/* descriptor ring memory */
	व्योम *cmd_buf;			/* command buffer memory */

	जोड़ अणु
		काष्ठा ice_dma_mem *sq_bi;
		काष्ठा ice_dma_mem *rq_bi;
	पूर्ण r;

	u16 count;		/* Number of descriptors */

	/* used क्रम पूर्णांकerrupt processing */
	u16 next_to_use;
	u16 next_to_clean;

	/* used क्रम queue tracking */
	u32 head;
	u32 tail;
	u32 len;
	u32 bah;
	u32 bal;
	u32 len_mask;
	u32 len_ena_mask;
	u32 len_crit_mask;
	u32 head_mask;
पूर्ण;

/* sq transaction details */
काष्ठा ice_sq_cd अणु
	काष्ठा ice_aq_desc *wb_desc;
पूर्ण;

#घोषणा ICE_CTL_Q_DETAILS(R, i) (&(((काष्ठा ice_sq_cd *)((R).cmd_buf))[i]))

/* rq event inक्रमmation */
काष्ठा ice_rq_event_info अणु
	काष्ठा ice_aq_desc desc;
	u16 msg_len;
	u16 buf_len;
	u8 *msg_buf;
पूर्ण;

/* Control Queue inक्रमmation */
काष्ठा ice_ctl_q_info अणु
	क्रमागत ice_ctl_q qtype;
	काष्ठा ice_ctl_q_ring rq;	/* receive queue */
	काष्ठा ice_ctl_q_ring sq;	/* send queue */
	u32 sq_cmd_समयout;		/* send queue cmd ग_लिखो back समयout */
	u16 num_rq_entries;		/* receive queue depth */
	u16 num_sq_entries;		/* send queue depth */
	u16 rq_buf_size;		/* receive queue buffer size */
	u16 sq_buf_size;		/* send queue buffer size */
	क्रमागत ice_aq_err sq_last_status;	/* last status on send queue */
	काष्ठा mutex sq_lock;		/* Send queue lock */
	काष्ठा mutex rq_lock;		/* Receive queue lock */
पूर्ण;

#पूर्ण_अगर /* _ICE_CONTROLQ_H_ */
