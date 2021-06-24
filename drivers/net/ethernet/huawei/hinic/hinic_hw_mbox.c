<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/completion.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_mgmt.h"
#समावेश "hinic_hw_csr.h"
#समावेश "hinic_hw_dev.h"
#समावेश "hinic_hw_mbox.h"

#घोषणा HINIC_MBOX_INT_DST_FUNC_SHIFT				0
#घोषणा HINIC_MBOX_INT_DST_AEQN_SHIFT				10
#घोषणा HINIC_MBOX_INT_SRC_RESP_AEQN_SHIFT			12
#घोषणा HINIC_MBOX_INT_STAT_DMA_SHIFT				14
/* The size of data to be sended (unit of 4 bytes) */
#घोषणा HINIC_MBOX_INT_TX_SIZE_SHIFT				20
/* SO_RO(strong order, relax order) */
#घोषणा HINIC_MBOX_INT_STAT_DMA_SO_RO_SHIFT			25
#घोषणा HINIC_MBOX_INT_WB_EN_SHIFT				28

#घोषणा HINIC_MBOX_INT_DST_FUNC_MASK				0x3FF
#घोषणा HINIC_MBOX_INT_DST_AEQN_MASK				0x3
#घोषणा HINIC_MBOX_INT_SRC_RESP_AEQN_MASK			0x3
#घोषणा HINIC_MBOX_INT_STAT_DMA_MASK				0x3F
#घोषणा HINIC_MBOX_INT_TX_SIZE_MASK				0x1F
#घोषणा HINIC_MBOX_INT_STAT_DMA_SO_RO_MASK			0x3
#घोषणा HINIC_MBOX_INT_WB_EN_MASK				0x1

#घोषणा HINIC_MBOX_INT_SET(val, field)	\
			(((val) & HINIC_MBOX_INT_##field##_MASK) << \
			HINIC_MBOX_INT_##field##_SHIFT)

क्रमागत hinic_mbox_tx_status अणु
	TX_NOT_DONE = 1,
पूर्ण;

#घोषणा HINIC_MBOX_CTRL_TRIGGER_AEQE_SHIFT			0

/* specअगरies the issue request क्रम the message data.
 * 0 - Tx request is करोne;
 * 1 - Tx request is in process.
 */
#घोषणा HINIC_MBOX_CTRL_TX_STATUS_SHIFT				1

#घोषणा HINIC_MBOX_CTRL_TRIGGER_AEQE_MASK			0x1
#घोषणा HINIC_MBOX_CTRL_TX_STATUS_MASK				0x1

#घोषणा HINIC_MBOX_CTRL_SET(val, field)	\
			(((val) & HINIC_MBOX_CTRL_##field##_MASK) << \
			HINIC_MBOX_CTRL_##field##_SHIFT)

#घोषणा HINIC_MBOX_HEADER_MSG_LEN_SHIFT				0
#घोषणा HINIC_MBOX_HEADER_MODULE_SHIFT				11
#घोषणा HINIC_MBOX_HEADER_SEG_LEN_SHIFT				16
#घोषणा HINIC_MBOX_HEADER_NO_ACK_SHIFT				22
#घोषणा HINIC_MBOX_HEADER_SEQID_SHIFT				24
#घोषणा HINIC_MBOX_HEADER_LAST_SHIFT				30

/* specअगरies the mailbox message direction
 * 0 - send
 * 1 - receive
 */
#घोषणा HINIC_MBOX_HEADER_सूचीECTION_SHIFT			31
#घोषणा HINIC_MBOX_HEADER_CMD_SHIFT				32
#घोषणा HINIC_MBOX_HEADER_MSG_ID_SHIFT				40
#घोषणा HINIC_MBOX_HEADER_STATUS_SHIFT				48
#घोषणा HINIC_MBOX_HEADER_SRC_GLB_FUNC_IDX_SHIFT		54

#घोषणा HINIC_MBOX_HEADER_MSG_LEN_MASK				0x7FF
#घोषणा HINIC_MBOX_HEADER_MODULE_MASK				0x1F
#घोषणा HINIC_MBOX_HEADER_SEG_LEN_MASK				0x3F
#घोषणा HINIC_MBOX_HEADER_NO_ACK_MASK				0x1
#घोषणा HINIC_MBOX_HEADER_SEQID_MASK				0x3F
#घोषणा HINIC_MBOX_HEADER_LAST_MASK				0x1
#घोषणा HINIC_MBOX_HEADER_सूचीECTION_MASK			0x1
#घोषणा HINIC_MBOX_HEADER_CMD_MASK				0xFF
#घोषणा HINIC_MBOX_HEADER_MSG_ID_MASK				0xFF
#घोषणा HINIC_MBOX_HEADER_STATUS_MASK				0x3F
#घोषणा HINIC_MBOX_HEADER_SRC_GLB_FUNC_IDX_MASK			0x3FF

#घोषणा HINIC_MBOX_HEADER_GET(val, field)	\
			(((val) >> HINIC_MBOX_HEADER_##field##_SHIFT) & \
			HINIC_MBOX_HEADER_##field##_MASK)
#घोषणा HINIC_MBOX_HEADER_SET(val, field)	\
			((u64)((val) & HINIC_MBOX_HEADER_##field##_MASK) << \
			HINIC_MBOX_HEADER_##field##_SHIFT)

#घोषणा MBOX_SEGLEN_MASK			\
		HINIC_MBOX_HEADER_SET(HINIC_MBOX_HEADER_SEG_LEN_MASK, SEG_LEN)

#घोषणा HINIC_MBOX_SEG_LEN			48
#घोषणा HINIC_MBOX_COMP_TIME			8000U
#घोषणा MBOX_MSG_POLLING_TIMEOUT		8000

#घोषणा HINIC_MBOX_DATA_SIZE			2040

#घोषणा MBOX_MAX_BUF_SZ				2048UL
#घोषणा MBOX_HEADER_SZ				8

#घोषणा MBOX_INFO_SZ				4

/* MBOX size is 64B, 8B क्रम mbox_header, 4B reserved */
#घोषणा MBOX_SEG_LEN				48
#घोषणा MBOX_SEG_LEN_ALIGN			4
#घोषणा MBOX_WB_STATUS_LEN			16UL

/* mbox ग_लिखो back status is 16B, only first 4B is used */
#घोषणा MBOX_WB_STATUS_ERRCODE_MASK		0xFFFF
#घोषणा MBOX_WB_STATUS_MASK			0xFF
#घोषणा MBOX_WB_ERROR_CODE_MASK			0xFF00
#घोषणा MBOX_WB_STATUS_FINISHED_SUCCESS		0xFF
#घोषणा MBOX_WB_STATUS_FINISHED_WITH_ERR	0xFE
#घोषणा MBOX_WB_STATUS_NOT_FINISHED		0x00

#घोषणा MBOX_STATUS_FINISHED(wb)	\
	(((wb) & MBOX_WB_STATUS_MASK) != MBOX_WB_STATUS_NOT_FINISHED)
#घोषणा MBOX_STATUS_SUCCESS(wb)		\
	(((wb) & MBOX_WB_STATUS_MASK) == MBOX_WB_STATUS_FINISHED_SUCCESS)
#घोषणा MBOX_STATUS_ERRCODE(wb)		\
	((wb) & MBOX_WB_ERROR_CODE_MASK)

#घोषणा SEQ_ID_START_VAL			0
#घोषणा SEQ_ID_MAX_VAL				42

#घोषणा DST_AEQ_IDX_DEFAULT_VAL			0
#घोषणा SRC_AEQ_IDX_DEFAULT_VAL			0
#घोषणा NO_DMA_ATTRIBUTE_VAL			0

#घोषणा HINIC_MGMT_RSP_AEQN			0
#घोषणा HINIC_MBOX_RSP_AEQN			2
#घोषणा HINIC_MBOX_RECV_AEQN			0

#घोषणा MBOX_MSG_NO_DATA_LEN			1

#घोषणा MBOX_BODY_FROM_HDR(header)	((u8 *)(header) + MBOX_HEADER_SZ)
#घोषणा MBOX_AREA(hwअगर)			\
	((hwअगर)->cfg_regs_bar + HINIC_FUNC_CSR_MAILBOX_DATA_OFF)

#घोषणा IS_PF_OR_PPF_SRC(src_func_idx)	((src_func_idx) < HINIC_MAX_PF_FUNCS)

#घोषणा MBOX_RESPONSE_ERROR		0x1
#घोषणा MBOX_MSG_ID_MASK		0xFF
#घोषणा MBOX_MSG_ID(func_to_func)	((func_to_func)->send_msg_id)
#घोषणा MBOX_MSG_ID_INC(func_to_func_mbox) (MBOX_MSG_ID(func_to_func_mbox) = \
			(MBOX_MSG_ID(func_to_func_mbox) + 1) & MBOX_MSG_ID_MASK)

#घोषणा FUNC_ID_OFF_SET_8B		8

/* max message counter रुको to process क्रम one function */
#घोषणा HINIC_MAX_MSG_CNT_TO_PROCESS	10

#घोषणा HINIC_QUEUE_MIN_DEPTH		6
#घोषणा HINIC_QUEUE_MAX_DEPTH		12
#घोषणा HINIC_MAX_RX_BUFFER_SIZE		15

क्रमागत hinic_hwअगर_direction_type अणु
	HINIC_HWIF_सूचीECT_SEND	= 0,
	HINIC_HWIF_RESPONSE	= 1,
पूर्ण;

क्रमागत mbox_send_mod अणु
	MBOX_SEND_MSG_INT,
पूर्ण;

क्रमागत mbox_seg_type अणु
	NOT_LAST_SEG,
	LAST_SEG,
पूर्ण;

क्रमागत mbox_ordering_type अणु
	STRONG_ORDER,
पूर्ण;

क्रमागत mbox_ग_लिखो_back_type अणु
	WRITE_BACK = 1,
पूर्ण;

क्रमागत mbox_aeq_trig_type अणु
	NOT_TRIGGER,
	TRIGGER,
पूर्ण;

अटल bool check_func_id(काष्ठा hinic_hwdev *hwdev, u16 src_func_idx,
			  स्थिर व्योम *buf_in, u16 in_size, u16 offset)
अणु
	u16 func_idx;

	अगर (in_size < offset + माप(func_idx)) अणु
		dev_warn(&hwdev->hwअगर->pdev->dev,
			 "Receive mailbox msg len: %d less than %d Bytes is invalid\n",
			 in_size, offset);
		वापस false;
	पूर्ण

	func_idx = *((u16 *)((u8 *)buf_in + offset));

	अगर (src_func_idx != func_idx) अणु
		dev_warn(&hwdev->hwअगर->pdev->dev,
			 "Receive mailbox function id: 0x%x not equal to msg function id: 0x%x\n",
			 src_func_idx, func_idx);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool hinic_mbox_check_func_id_8B(काष्ठा hinic_hwdev *hwdev, u16 func_idx,
				 व्योम *buf_in, u16 in_size)
अणु
	वापस check_func_id(hwdev, func_idx, buf_in, in_size,
			     FUNC_ID_OFF_SET_8B);
पूर्ण

/**
 * hinic_रेजिस्टर_pf_mbox_cb - रेजिस्टर mbox callback क्रम pf
 * @hwdev: the poपूर्णांकer to hw device
 * @mod:	specअगरic mod that the callback will handle
 * @callback:	callback function
 * Return: 0 - success, negative - failure
 */
पूर्णांक hinic_रेजिस्टर_pf_mbox_cb(काष्ठा hinic_hwdev *hwdev,
			      क्रमागत hinic_mod_type mod,
			      hinic_pf_mbox_cb callback)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func = hwdev->func_to_func;

	अगर (mod >= HINIC_MOD_MAX)
		वापस -EFAULT;

	func_to_func->pf_mbox_cb[mod] = callback;

	set_bit(HINIC_PF_MBOX_CB_REG, &func_to_func->pf_mbox_cb_state[mod]);

	वापस 0;
पूर्ण

/**
 * hinic_रेजिस्टर_vf_mbox_cb - रेजिस्टर mbox callback क्रम vf
 * @hwdev: the poपूर्णांकer to hw device
 * @mod:	specअगरic mod that the callback will handle
 * @callback:	callback function
 * Return: 0 - success, negative - failure
 */
पूर्णांक hinic_रेजिस्टर_vf_mbox_cb(काष्ठा hinic_hwdev *hwdev,
			      क्रमागत hinic_mod_type mod,
			      hinic_vf_mbox_cb callback)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func = hwdev->func_to_func;

	अगर (mod >= HINIC_MOD_MAX)
		वापस -EFAULT;

	func_to_func->vf_mbox_cb[mod] = callback;

	set_bit(HINIC_VF_MBOX_CB_REG, &func_to_func->vf_mbox_cb_state[mod]);

	वापस 0;
पूर्ण

/**
 * hinic_unरेजिस्टर_pf_mbox_cb - unरेजिस्टर the mbox callback क्रम pf
 * @hwdev:	the poपूर्णांकer to hw device
 * @mod:	specअगरic mod that the callback will handle
 */
व्योम hinic_unरेजिस्टर_pf_mbox_cb(काष्ठा hinic_hwdev *hwdev,
				 क्रमागत hinic_mod_type mod)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func = hwdev->func_to_func;

	clear_bit(HINIC_PF_MBOX_CB_REG, &func_to_func->pf_mbox_cb_state[mod]);

	जबतक (test_bit(HINIC_PF_MBOX_CB_RUNNING,
			&func_to_func->pf_mbox_cb_state[mod]))
		usleep_range(900, 1000);

	func_to_func->pf_mbox_cb[mod] = शून्य;
पूर्ण

/**
 * hinic_unरेजिस्टर_vf_mbox_cb - unरेजिस्टर the mbox callback क्रम vf
 * @hwdev:	the poपूर्णांकer to hw device
 * @mod:	specअगरic mod that the callback will handle
 */
व्योम hinic_unरेजिस्टर_vf_mbox_cb(काष्ठा hinic_hwdev *hwdev,
				 क्रमागत hinic_mod_type mod)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func = hwdev->func_to_func;

	clear_bit(HINIC_VF_MBOX_CB_REG, &func_to_func->vf_mbox_cb_state[mod]);

	जबतक (test_bit(HINIC_VF_MBOX_CB_RUNNING,
			&func_to_func->vf_mbox_cb_state[mod]))
		usleep_range(900, 1000);

	func_to_func->vf_mbox_cb[mod] = शून्य;
पूर्ण

अटल पूर्णांक recv_vf_mbox_handler(काष्ठा hinic_mbox_func_to_func *func_to_func,
				काष्ठा hinic_recv_mbox *recv_mbox,
				व्योम *buf_out, u16 *out_size)
अणु
	hinic_vf_mbox_cb cb;
	पूर्णांक ret = 0;

	अगर (recv_mbox->mod >= HINIC_MOD_MAX) अणु
		dev_err(&func_to_func->hwअगर->pdev->dev, "Receive illegal mbox message, mod = %d\n",
			recv_mbox->mod);
		वापस -EINVAL;
	पूर्ण

	set_bit(HINIC_VF_MBOX_CB_RUNNING,
		&func_to_func->vf_mbox_cb_state[recv_mbox->mod]);

	cb = func_to_func->vf_mbox_cb[recv_mbox->mod];
	अगर (cb && test_bit(HINIC_VF_MBOX_CB_REG,
			   &func_to_func->vf_mbox_cb_state[recv_mbox->mod])) अणु
		cb(func_to_func->hwdev, recv_mbox->cmd, recv_mbox->mbox,
		   recv_mbox->mbox_len, buf_out, out_size);
	पूर्ण अन्यथा अणु
		dev_err(&func_to_func->hwअगर->pdev->dev, "VF mbox cb is not registered\n");
		ret = -EINVAL;
	पूर्ण

	clear_bit(HINIC_VF_MBOX_CB_RUNNING,
		  &func_to_func->vf_mbox_cb_state[recv_mbox->mod]);

	वापस ret;
पूर्ण

अटल पूर्णांक
recv_pf_from_vf_mbox_handler(काष्ठा hinic_mbox_func_to_func *func_to_func,
			     काष्ठा hinic_recv_mbox *recv_mbox,
			     u16 src_func_idx, व्योम *buf_out,
			     u16 *out_size)
अणु
	hinic_pf_mbox_cb cb;
	u16 vf_id = 0;
	पूर्णांक ret;

	अगर (recv_mbox->mod >= HINIC_MOD_MAX) अणु
		dev_err(&func_to_func->hwअगर->pdev->dev, "Receive illegal mbox message, mod = %d\n",
			recv_mbox->mod);
		वापस -EINVAL;
	पूर्ण

	set_bit(HINIC_PF_MBOX_CB_RUNNING,
		&func_to_func->pf_mbox_cb_state[recv_mbox->mod]);

	cb = func_to_func->pf_mbox_cb[recv_mbox->mod];
	अगर (cb && test_bit(HINIC_PF_MBOX_CB_REG,
			   &func_to_func->pf_mbox_cb_state[recv_mbox->mod])) अणु
		vf_id = src_func_idx -
			hinic_glb_pf_vf_offset(func_to_func->hwअगर);
		ret = cb(func_to_func->hwdev, vf_id, recv_mbox->cmd,
			 recv_mbox->mbox, recv_mbox->mbox_len,
			 buf_out, out_size);
	पूर्ण अन्यथा अणु
		dev_err(&func_to_func->hwअगर->pdev->dev, "PF mbox mod(0x%x) cb is not registered\n",
			recv_mbox->mod);
		ret = -EINVAL;
	पूर्ण

	clear_bit(HINIC_PF_MBOX_CB_RUNNING,
		  &func_to_func->pf_mbox_cb_state[recv_mbox->mod]);

	वापस ret;
पूर्ण

अटल bool check_mbox_seq_id_and_seg_len(काष्ठा hinic_recv_mbox *recv_mbox,
					  u8 seq_id, u8 seg_len)
अणु
	अगर (seq_id > SEQ_ID_MAX_VAL || seg_len > MBOX_SEG_LEN)
		वापस false;

	अगर (seq_id == 0) अणु
		recv_mbox->seq_id = seq_id;
	पूर्ण अन्यथा अणु
		अगर (seq_id != recv_mbox->seq_id + 1)
			वापस false;

		recv_mbox->seq_id = seq_id;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम resp_mbox_handler(काष्ठा hinic_mbox_func_to_func *func_to_func,
			      काष्ठा hinic_recv_mbox *recv_mbox)
अणु
	spin_lock(&func_to_func->mbox_lock);
	अगर (recv_mbox->msg_info.msg_id == func_to_func->send_msg_id &&
	    func_to_func->event_flag == EVENT_START)
		complete(&recv_mbox->recv_करोne);
	अन्यथा
		dev_err(&func_to_func->hwअगर->pdev->dev,
			"Mbox response timeout, current send msg id(0x%x), recv msg id(0x%x), status(0x%x)\n",
			func_to_func->send_msg_id, recv_mbox->msg_info.msg_id,
			recv_mbox->msg_info.status);
	spin_unlock(&func_to_func->mbox_lock);
पूर्ण

अटल व्योम recv_func_mbox_handler(काष्ठा hinic_mbox_func_to_func *func_to_func,
				   काष्ठा hinic_recv_mbox *recv_mbox,
				   u16 src_func_idx);

अटल व्योम recv_func_mbox_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hinic_mbox_work *mbox_work =
			container_of(work, काष्ठा hinic_mbox_work, work);
	काष्ठा hinic_recv_mbox *recv_mbox;

	recv_func_mbox_handler(mbox_work->func_to_func, mbox_work->recv_mbox,
			       mbox_work->src_func_idx);

	recv_mbox =
		&mbox_work->func_to_func->mbox_send[mbox_work->src_func_idx];

	atomic_dec(&recv_mbox->msg_cnt);

	kमुक्त(mbox_work);
पूर्ण

अटल व्योम recv_mbox_handler(काष्ठा hinic_mbox_func_to_func *func_to_func,
			      व्योम *header, काष्ठा hinic_recv_mbox *recv_mbox)
अणु
	व्योम *mbox_body = MBOX_BODY_FROM_HDR(header);
	काष्ठा hinic_recv_mbox *rcv_mbox_temp = शून्य;
	u64 mbox_header = *((u64 *)header);
	काष्ठा hinic_mbox_work *mbox_work;
	u8 seq_id, seg_len;
	u16 src_func_idx;
	पूर्णांक pos;

	seq_id = HINIC_MBOX_HEADER_GET(mbox_header, SEQID);
	seg_len = HINIC_MBOX_HEADER_GET(mbox_header, SEG_LEN);
	src_func_idx = HINIC_MBOX_HEADER_GET(mbox_header, SRC_GLB_FUNC_IDX);

	अगर (!check_mbox_seq_id_and_seg_len(recv_mbox, seq_id, seg_len)) अणु
		dev_err(&func_to_func->hwअगर->pdev->dev,
			"Mailbox sequence and segment check fail, src func id: 0x%x, front id: 0x%x, current id: 0x%x, seg len: 0x%x\n",
			src_func_idx, recv_mbox->seq_id, seq_id, seg_len);
		recv_mbox->seq_id = SEQ_ID_MAX_VAL;
		वापस;
	पूर्ण

	pos = seq_id * MBOX_SEG_LEN;
	स_नकल((u8 *)recv_mbox->mbox + pos, mbox_body,
	       HINIC_MBOX_HEADER_GET(mbox_header, SEG_LEN));

	अगर (!HINIC_MBOX_HEADER_GET(mbox_header, LAST))
		वापस;

	recv_mbox->cmd = HINIC_MBOX_HEADER_GET(mbox_header, CMD);
	recv_mbox->mod = HINIC_MBOX_HEADER_GET(mbox_header, MODULE);
	recv_mbox->mbox_len = HINIC_MBOX_HEADER_GET(mbox_header, MSG_LEN);
	recv_mbox->ack_type = HINIC_MBOX_HEADER_GET(mbox_header, NO_ACK);
	recv_mbox->msg_info.msg_id = HINIC_MBOX_HEADER_GET(mbox_header, MSG_ID);
	recv_mbox->msg_info.status = HINIC_MBOX_HEADER_GET(mbox_header, STATUS);
	recv_mbox->seq_id = SEQ_ID_MAX_VAL;

	अगर (HINIC_MBOX_HEADER_GET(mbox_header, सूचीECTION) ==
	    HINIC_HWIF_RESPONSE) अणु
		resp_mbox_handler(func_to_func, recv_mbox);
		वापस;
	पूर्ण

	अगर (atomic_पढ़ो(&recv_mbox->msg_cnt) > HINIC_MAX_MSG_CNT_TO_PROCESS) अणु
		dev_warn(&func_to_func->hwअगर->pdev->dev,
			 "This function(%u) have %d message wait to process,can't add to work queue\n",
			 src_func_idx, atomic_पढ़ो(&recv_mbox->msg_cnt));
		वापस;
	पूर्ण

	rcv_mbox_temp = kmemdup(recv_mbox, माप(*rcv_mbox_temp), GFP_KERNEL);
	अगर (!rcv_mbox_temp)
		वापस;

	rcv_mbox_temp->mbox = kmemdup(recv_mbox->mbox, MBOX_MAX_BUF_SZ,
				      GFP_KERNEL);
	अगर (!rcv_mbox_temp->mbox)
		जाओ err_alloc_rcv_mbox_msg;

	rcv_mbox_temp->buf_out = kzalloc(MBOX_MAX_BUF_SZ, GFP_KERNEL);
	अगर (!rcv_mbox_temp->buf_out)
		जाओ err_alloc_rcv_mbox_buf;

	mbox_work = kzalloc(माप(*mbox_work), GFP_KERNEL);
	अगर (!mbox_work)
		जाओ err_alloc_mbox_work;

	mbox_work->func_to_func = func_to_func;
	mbox_work->recv_mbox = rcv_mbox_temp;
	mbox_work->src_func_idx = src_func_idx;

	atomic_inc(&recv_mbox->msg_cnt);
	INIT_WORK(&mbox_work->work, recv_func_mbox_work_handler);
	queue_work(func_to_func->workq, &mbox_work->work);

	वापस;

err_alloc_mbox_work:
	kमुक्त(rcv_mbox_temp->buf_out);

err_alloc_rcv_mbox_buf:
	kमुक्त(rcv_mbox_temp->mbox);

err_alloc_rcv_mbox_msg:
	kमुक्त(rcv_mbox_temp);
पूर्ण

अटल पूर्णांक set_vf_mbox_अक्रमom_id(काष्ठा hinic_hwdev *hwdev, u16 func_id)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func = hwdev->func_to_func;
	काष्ठा hinic_set_अक्रमom_id अक्रम_info = अणु0पूर्ण;
	u16 out_size = माप(अक्रम_info);
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक ret;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	अक्रम_info.version = HINIC_CMD_VER_FUNC_ID;
	अक्रम_info.func_idx = func_id;
	अक्रम_info.vf_in_pf = func_id - hinic_glb_pf_vf_offset(hwdev->hwअगर);
	अक्रम_info.अक्रमom_id = get_अक्रमom_u32();

	func_to_func->vf_mbx_अक्रम_id[func_id] = अक्रम_info.अक्रमom_id;

	ret = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_MGMT_CMD_SET_VF_RANDOM_ID,
				&अक्रम_info, माप(अक्रम_info),
				&अक्रम_info, &out_size, HINIC_MGMT_MSG_SYNC);
	अगर ((अक्रम_info.status != HINIC_MGMT_CMD_UNSUPPORTED &&
	     अक्रम_info.status) || !out_size || ret) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Set VF random id failed, err: %d, status: 0x%x, out size: 0x%x\n",
			ret, अक्रम_info.status, out_size);
		वापस -EIO;
	पूर्ण

	अगर (अक्रम_info.status == HINIC_MGMT_CMD_UNSUPPORTED)
		वापस अक्रम_info.status;

	func_to_func->vf_mbx_old_अक्रम_id[func_id] =
				func_to_func->vf_mbx_अक्रम_id[func_id];

	वापस 0;
पूर्ण

अटल व्योम update_अक्रमom_id_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hinic_mbox_work *mbox_work =
			container_of(work, काष्ठा hinic_mbox_work, work);
	काष्ठा hinic_mbox_func_to_func *func_to_func;
	u16 src = mbox_work->src_func_idx;

	func_to_func = mbox_work->func_to_func;

	अगर (set_vf_mbox_अक्रमom_id(func_to_func->hwdev, src))
		dev_warn(&func_to_func->hwdev->hwअगर->pdev->dev, "Update VF id: 0x%x random id failed\n",
			 mbox_work->src_func_idx);

	kमुक्त(mbox_work);
पूर्ण

अटल bool check_vf_mbox_अक्रमom_id(काष्ठा hinic_mbox_func_to_func *func_to_func,
				    u8 *header)
अणु
	काष्ठा hinic_hwdev *hwdev = func_to_func->hwdev;
	काष्ठा hinic_mbox_work *mbox_work = शून्य;
	u64 mbox_header = *((u64 *)header);
	u16 offset, src;
	u32 अक्रमom_id;
	पूर्णांक vf_in_pf;

	src = HINIC_MBOX_HEADER_GET(mbox_header, SRC_GLB_FUNC_IDX);

	अगर (IS_PF_OR_PPF_SRC(src) || !func_to_func->support_vf_अक्रमom)
		वापस true;

	अगर (!HINIC_IS_PPF(hwdev->hwअगर)) अणु
		offset = hinic_glb_pf_vf_offset(hwdev->hwअगर);
		vf_in_pf = src - offset;

		अगर (vf_in_pf < 1 || vf_in_pf > hwdev->nic_cap.max_vf) अणु
			dev_warn(&hwdev->hwअगर->pdev->dev,
				 "Receive vf id(0x%x) is invalid, vf id should be from 0x%x to 0x%x\n",
				 src, offset + 1,
				 hwdev->nic_cap.max_vf + offset);
			वापस false;
		पूर्ण
	पूर्ण

	अक्रमom_id = be32_to_cpu(*(u32 *)(header + MBOX_SEG_LEN +
					 MBOX_HEADER_SZ));

	अगर (अक्रमom_id == func_to_func->vf_mbx_अक्रम_id[src] ||
	    अक्रमom_id == func_to_func->vf_mbx_old_अक्रम_id[src])
		वापस true;

	dev_warn(&hwdev->hwअगर->pdev->dev,
		 "The mailbox random id(0x%x) of func_id(0x%x) doesn't match with pf reservation(0x%x)\n",
		 अक्रमom_id, src, func_to_func->vf_mbx_अक्रम_id[src]);

	mbox_work = kzalloc(माप(*mbox_work), GFP_KERNEL);
	अगर (!mbox_work)
		वापस false;

	mbox_work->func_to_func = func_to_func;
	mbox_work->src_func_idx = src;

	INIT_WORK(&mbox_work->work, update_अक्रमom_id_work_handler);
	queue_work(func_to_func->workq, &mbox_work->work);

	वापस false;
पूर्ण

व्योम hinic_mbox_func_aeqe_handler(व्योम *handle, व्योम *header, u8 size)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func;
	u64 mbox_header = *((u64 *)header);
	काष्ठा hinic_recv_mbox *recv_mbox;
	u64 src, dir;

	func_to_func = ((काष्ठा hinic_hwdev *)handle)->func_to_func;

	dir = HINIC_MBOX_HEADER_GET(mbox_header, सूचीECTION);
	src = HINIC_MBOX_HEADER_GET(mbox_header, SRC_GLB_FUNC_IDX);

	अगर (src >= HINIC_MAX_FUNCTIONS) अणु
		dev_err(&func_to_func->hwअगर->pdev->dev,
			"Mailbox source function id:%u is invalid\n", (u32)src);
		वापस;
	पूर्ण

	अगर (!check_vf_mbox_अक्रमom_id(func_to_func, header))
		वापस;

	recv_mbox = (dir == HINIC_HWIF_सूचीECT_SEND) ?
		    &func_to_func->mbox_send[src] :
		    &func_to_func->mbox_resp[src];

	recv_mbox_handler(func_to_func, (u64 *)header, recv_mbox);
पूर्ण

व्योम hinic_mbox_self_aeqe_handler(व्योम *handle, व्योम *header, u8 size)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func;
	काष्ठा hinic_send_mbox *send_mbox;

	func_to_func = ((काष्ठा hinic_hwdev *)handle)->func_to_func;
	send_mbox = &func_to_func->send_mbox;

	complete(&send_mbox->send_करोne);
पूर्ण

अटल व्योम clear_mbox_status(काष्ठा hinic_send_mbox *mbox)
अणु
	*mbox->wb_status = 0;

	/* clear mailbox ग_लिखो back status */
	wmb();
पूर्ण

अटल व्योम mbox_copy_header(काष्ठा hinic_hwdev *hwdev,
			     काष्ठा hinic_send_mbox *mbox, u64 *header)
अणु
	u32 i, idx_max = MBOX_HEADER_SZ / माप(u32);
	u32 *data = (u32 *)header;

	क्रम (i = 0; i < idx_max; i++)
		__raw_ग_लिखोl(*(data + i), mbox->data + i * माप(u32));
पूर्ण

अटल व्योम mbox_copy_send_data(काष्ठा hinic_hwdev *hwdev,
				काष्ठा hinic_send_mbox *mbox, व्योम *seg,
				u16 seg_len)
अणु
	u8 mbox_max_buf[MBOX_SEG_LEN] = अणु0पूर्ण;
	u32 data_len, chk_sz = माप(u32);
	u32 *data = seg;
	u32 i, idx_max;

	/* The mbox message should be aligned in 4 bytes. */
	अगर (seg_len % chk_sz) अणु
		स_नकल(mbox_max_buf, seg, seg_len);
		data = (u32 *)mbox_max_buf;
	पूर्ण

	data_len = seg_len;
	idx_max = ALIGN(data_len, chk_sz) / chk_sz;

	क्रम (i = 0; i < idx_max; i++)
		__raw_ग_लिखोl(*(data + i),
			     mbox->data + MBOX_HEADER_SZ + i * माप(u32));
पूर्ण

अटल व्योम ग_लिखो_mbox_msg_attr(काष्ठा hinic_mbox_func_to_func *func_to_func,
				u16 dst_func, u16 dst_aeqn, u16 seg_len,
				पूर्णांक poll)
अणु
	u16 rsp_aeq = (dst_aeqn == 0) ? 0 : HINIC_MBOX_RSP_AEQN;
	u32 mbox_पूर्णांक, mbox_ctrl;

	mbox_पूर्णांक = HINIC_MBOX_INT_SET(dst_func, DST_FUNC) |
		   HINIC_MBOX_INT_SET(dst_aeqn, DST_AEQN) |
		   HINIC_MBOX_INT_SET(rsp_aeq, SRC_RESP_AEQN) |
		   HINIC_MBOX_INT_SET(NO_DMA_ATTRIBUTE_VAL, STAT_DMA) |
		   HINIC_MBOX_INT_SET(ALIGN(MBOX_SEG_LEN + MBOX_HEADER_SZ +
				      MBOX_INFO_SZ, MBOX_SEG_LEN_ALIGN) >> 2,
				      TX_SIZE) |
		   HINIC_MBOX_INT_SET(STRONG_ORDER, STAT_DMA_SO_RO) |
		   HINIC_MBOX_INT_SET(WRITE_BACK, WB_EN);

	hinic_hwअगर_ग_लिखो_reg(func_to_func->hwअगर,
			     HINIC_FUNC_CSR_MAILBOX_INT_OFFSET_OFF, mbox_पूर्णांक);

	wmb(); /* writing the mbox पूर्णांक attributes */
	mbox_ctrl = HINIC_MBOX_CTRL_SET(TX_NOT_DONE, TX_STATUS);

	अगर (poll)
		mbox_ctrl |= HINIC_MBOX_CTRL_SET(NOT_TRIGGER, TRIGGER_AEQE);
	अन्यथा
		mbox_ctrl |= HINIC_MBOX_CTRL_SET(TRIGGER, TRIGGER_AEQE);

	hinic_hwअगर_ग_लिखो_reg(func_to_func->hwअगर,
			     HINIC_FUNC_CSR_MAILBOX_CONTROL_OFF, mbox_ctrl);
पूर्ण

अटल व्योम dump_mox_reg(काष्ठा hinic_hwdev *hwdev)
अणु
	u32 val;

	val = hinic_hwअगर_पढ़ो_reg(hwdev->hwअगर,
				  HINIC_FUNC_CSR_MAILBOX_CONTROL_OFF);
	dev_err(&hwdev->hwअगर->pdev->dev, "Mailbox control reg: 0x%x\n", val);

	val = hinic_hwअगर_पढ़ो_reg(hwdev->hwअगर,
				  HINIC_FUNC_CSR_MAILBOX_INT_OFFSET_OFF);
	dev_err(&hwdev->hwअगर->pdev->dev, "Mailbox interrupt offset: 0x%x\n",
		val);
पूर्ण

अटल u16 get_mbox_status(काष्ठा hinic_send_mbox *mbox)
अणु
	/* ग_लिखो back is 16B, but only use first 4B */
	u64 wb_val = be64_to_cpu(*mbox->wb_status);

	rmb(); /* verअगरy पढ़ोing beक्रमe check */

	वापस (u16)(wb_val & MBOX_WB_STATUS_ERRCODE_MASK);
पूर्ण

अटल पूर्णांक
रुको_क्रम_mbox_seg_completion(काष्ठा hinic_mbox_func_to_func *func_to_func,
			     पूर्णांक poll, u16 *wb_status)
अणु
	काष्ठा hinic_send_mbox *send_mbox = &func_to_func->send_mbox;
	काष्ठा hinic_hwdev *hwdev = func_to_func->hwdev;
	काष्ठा completion *करोne = &send_mbox->send_करोne;
	u32 cnt = 0;
	अचिन्हित दीर्घ jअगर;

	अगर (poll) अणु
		जबतक (cnt < MBOX_MSG_POLLING_TIMEOUT) अणु
			*wb_status = get_mbox_status(send_mbox);
			अगर (MBOX_STATUS_FINISHED(*wb_status))
				अवरोध;

			usleep_range(900, 1000);
			cnt++;
		पूर्ण

		अगर (cnt == MBOX_MSG_POLLING_TIMEOUT) अणु
			dev_err(&hwdev->hwअगर->pdev->dev, "Send mailbox segment timeout, wb status: 0x%x\n",
				*wb_status);
			dump_mox_reg(hwdev);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		jअगर = msecs_to_jअगरfies(HINIC_MBOX_COMP_TIME);
		अगर (!रुको_क्रम_completion_समयout(करोne, jअगर)) अणु
			dev_err(&hwdev->hwअगर->pdev->dev, "Send mailbox segment timeout\n");
			dump_mox_reg(hwdev);
			hinic_dump_aeq_info(hwdev);
			वापस -ETIMEDOUT;
		पूर्ण

		*wb_status = get_mbox_status(send_mbox);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक send_mbox_seg(काष्ठा hinic_mbox_func_to_func *func_to_func,
			 u64 header, u16 dst_func, व्योम *seg, u16 seg_len,
			 पूर्णांक poll, व्योम *msg_info)
अणु
	काष्ठा hinic_send_mbox *send_mbox = &func_to_func->send_mbox;
	u16 seq_dir = HINIC_MBOX_HEADER_GET(header, सूचीECTION);
	काष्ठा hinic_hwdev *hwdev = func_to_func->hwdev;
	काष्ठा completion *करोne = &send_mbox->send_करोne;
	u8 num_aeqs = hwdev->hwअगर->attr.num_aeqs;
	u16 dst_aeqn, wb_status = 0, errcode;

	अगर (num_aeqs >= 4)
		dst_aeqn = (seq_dir == HINIC_HWIF_सूचीECT_SEND) ?
			   HINIC_MBOX_RECV_AEQN : HINIC_MBOX_RSP_AEQN;
	अन्यथा
		dst_aeqn = 0;

	अगर (!poll)
		init_completion(करोne);

	clear_mbox_status(send_mbox);

	mbox_copy_header(hwdev, send_mbox, &header);

	mbox_copy_send_data(hwdev, send_mbox, seg, seg_len);

	ग_लिखो_mbox_msg_attr(func_to_func, dst_func, dst_aeqn, seg_len, poll);

	wmb(); /* writing the mbox msg attributes */

	अगर (रुको_क्रम_mbox_seg_completion(func_to_func, poll, &wb_status))
		वापस -ETIMEDOUT;

	अगर (!MBOX_STATUS_SUCCESS(wb_status)) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Send mailbox segment to function %d error, wb status: 0x%x\n",
			dst_func, wb_status);
		errcode = MBOX_STATUS_ERRCODE(wb_status);
		वापस errcode ? errcode : -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक send_mbox_to_func(काष्ठा hinic_mbox_func_to_func *func_to_func,
			     क्रमागत hinic_mod_type mod, u16 cmd, व्योम *msg,
			     u16 msg_len, u16 dst_func,
			     क्रमागत hinic_hwअगर_direction_type direction,
			     क्रमागत hinic_mbox_ack_type ack_type,
			     काष्ठा mbox_msg_info *msg_info)
अणु
	काष्ठा hinic_hwdev *hwdev = func_to_func->hwdev;
	u16 seg_len = MBOX_SEG_LEN;
	u8 *msg_seg = (u8 *)msg;
	u16 left = msg_len;
	u32 seq_id = 0;
	u64 header = 0;
	पूर्णांक err = 0;

	करोwn(&func_to_func->msg_send_sem);

	header = HINIC_MBOX_HEADER_SET(msg_len, MSG_LEN) |
		 HINIC_MBOX_HEADER_SET(mod, MODULE) |
		 HINIC_MBOX_HEADER_SET(seg_len, SEG_LEN) |
		 HINIC_MBOX_HEADER_SET(ack_type, NO_ACK) |
		 HINIC_MBOX_HEADER_SET(SEQ_ID_START_VAL, SEQID) |
		 HINIC_MBOX_HEADER_SET(NOT_LAST_SEG, LAST) |
		 HINIC_MBOX_HEADER_SET(direction, सूचीECTION) |
		 HINIC_MBOX_HEADER_SET(cmd, CMD) |
		 /* The vf's offset to it's associated pf */
		 HINIC_MBOX_HEADER_SET(msg_info->msg_id, MSG_ID) |
		 HINIC_MBOX_HEADER_SET(msg_info->status, STATUS) |
		 HINIC_MBOX_HEADER_SET(hinic_global_func_id_hw(hwdev->hwअगर),
				       SRC_GLB_FUNC_IDX);

	जबतक (!(HINIC_MBOX_HEADER_GET(header, LAST))) अणु
		अगर (left <= HINIC_MBOX_SEG_LEN) अणु
			header &= ~MBOX_SEGLEN_MASK;
			header |= HINIC_MBOX_HEADER_SET(left, SEG_LEN);
			header |= HINIC_MBOX_HEADER_SET(LAST_SEG, LAST);

			seg_len = left;
		पूर्ण

		err = send_mbox_seg(func_to_func, header, dst_func, msg_seg,
				    seg_len, MBOX_SEND_MSG_INT, msg_info);
		अगर (err) अणु
			dev_err(&hwdev->hwअगर->pdev->dev, "Failed to send mbox seg, seq_id=0x%llx\n",
				HINIC_MBOX_HEADER_GET(header, SEQID));
			जाओ err_send_mbox_seg;
		पूर्ण

		left -= HINIC_MBOX_SEG_LEN;
		msg_seg += HINIC_MBOX_SEG_LEN;

		seq_id++;
		header &= ~(HINIC_MBOX_HEADER_SET(HINIC_MBOX_HEADER_SEQID_MASK,
						  SEQID));
		header |= HINIC_MBOX_HEADER_SET(seq_id, SEQID);
	पूर्ण

err_send_mbox_seg:
	up(&func_to_func->msg_send_sem);

	वापस err;
पूर्ण

अटल व्योम
response_क्रम_recv_func_mbox(काष्ठा hinic_mbox_func_to_func *func_to_func,
			    काष्ठा hinic_recv_mbox *recv_mbox, पूर्णांक err,
			    u16 out_size, u16 src_func_idx)
अणु
	काष्ठा mbox_msg_info msg_info = अणु0पूर्ण;

	अगर (recv_mbox->ack_type == MBOX_ACK) अणु
		msg_info.msg_id = recv_mbox->msg_info.msg_id;
		अगर (err == HINIC_MBOX_PF_BUSY_ACTIVE_FW)
			msg_info.status = HINIC_MBOX_PF_BUSY_ACTIVE_FW;
		अन्यथा अगर (err == HINIC_MBOX_VF_CMD_ERROR)
			msg_info.status = HINIC_MBOX_VF_CMD_ERROR;
		अन्यथा अगर (err)
			msg_info.status = HINIC_MBOX_PF_SEND_ERR;

		/* अगर no data needs to response, set out_size to 1 */
		अगर (!out_size || err)
			out_size = MBOX_MSG_NO_DATA_LEN;

		send_mbox_to_func(func_to_func, recv_mbox->mod, recv_mbox->cmd,
				  recv_mbox->buf_out, out_size, src_func_idx,
				  HINIC_HWIF_RESPONSE, MBOX_ACK,
				  &msg_info);
	पूर्ण
पूर्ण

अटल व्योम recv_func_mbox_handler(काष्ठा hinic_mbox_func_to_func *func_to_func,
				   काष्ठा hinic_recv_mbox *recv_mbox,
				   u16 src_func_idx)
अणु
	व्योम *buf_out = recv_mbox->buf_out;
	u16 out_size = MBOX_MAX_BUF_SZ;
	पूर्णांक err = 0;

	अगर (HINIC_IS_VF(func_to_func->hwअगर)) अणु
		err = recv_vf_mbox_handler(func_to_func, recv_mbox, buf_out,
					   &out_size);
	पूर्ण अन्यथा अणु
		अगर (IS_PF_OR_PPF_SRC(src_func_idx))
			dev_warn(&func_to_func->hwअगर->pdev->dev,
				 "Unsupported pf2pf mbox msg\n");
		अन्यथा
			err = recv_pf_from_vf_mbox_handler(func_to_func,
							   recv_mbox,
							   src_func_idx,
							   buf_out, &out_size);
	पूर्ण

	response_क्रम_recv_func_mbox(func_to_func, recv_mbox, err, out_size,
				    src_func_idx);
	kमुक्त(recv_mbox->buf_out);
	kमुक्त(recv_mbox->mbox);
	kमुक्त(recv_mbox);
पूर्ण

अटल व्योम set_mbox_to_func_event(काष्ठा hinic_mbox_func_to_func *func_to_func,
				   क्रमागत mbox_event_state event_flag)
अणु
	spin_lock(&func_to_func->mbox_lock);
	func_to_func->event_flag = event_flag;
	spin_unlock(&func_to_func->mbox_lock);
पूर्ण

अटल पूर्णांक mbox_resp_info_handler(काष्ठा hinic_mbox_func_to_func *func_to_func,
				  काष्ठा hinic_recv_mbox *mbox_क्रम_resp,
				  क्रमागत hinic_mod_type mod, u16 cmd,
				  व्योम *buf_out, u16 *out_size)
अणु
	पूर्णांक err;

	अगर (mbox_क्रम_resp->msg_info.status) अणु
		err = mbox_क्रम_resp->msg_info.status;
		अगर (err != HINIC_MBOX_PF_BUSY_ACTIVE_FW)
			dev_err(&func_to_func->hwअगर->pdev->dev, "Mbox response error(0x%x)\n",
				mbox_क्रम_resp->msg_info.status);
		वापस err;
	पूर्ण

	अगर (buf_out && out_size) अणु
		अगर (*out_size < mbox_क्रम_resp->mbox_len) अणु
			dev_err(&func_to_func->hwअगर->pdev->dev,
				"Invalid response mbox message length: %d for mod %d cmd %d, should less than: %d\n",
				mbox_क्रम_resp->mbox_len, mod, cmd, *out_size);
			वापस -EFAULT;
		पूर्ण

		अगर (mbox_क्रम_resp->mbox_len)
			स_नकल(buf_out, mbox_क्रम_resp->mbox,
			       mbox_क्रम_resp->mbox_len);

		*out_size = mbox_क्रम_resp->mbox_len;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_mbox_to_func(काष्ठा hinic_mbox_func_to_func *func_to_func,
		       क्रमागत hinic_mod_type mod, u16 cmd, u16 dst_func,
		       व्योम *buf_in, u16 in_size, व्योम *buf_out,
		       u16 *out_size, u32 समयout)
अणु
	काष्ठा hinic_recv_mbox *mbox_क्रम_resp;
	काष्ठा mbox_msg_info msg_info = अणु0पूर्ण;
	अचिन्हित दीर्घ समयo;
	पूर्णांक err;

	mbox_क्रम_resp = &func_to_func->mbox_resp[dst_func];

	करोwn(&func_to_func->mbox_send_sem);

	init_completion(&mbox_क्रम_resp->recv_करोne);

	msg_info.msg_id = MBOX_MSG_ID_INC(func_to_func);

	set_mbox_to_func_event(func_to_func, EVENT_START);

	err = send_mbox_to_func(func_to_func, mod, cmd, buf_in, in_size,
				dst_func, HINIC_HWIF_सूचीECT_SEND, MBOX_ACK,
				&msg_info);
	अगर (err) अणु
		dev_err(&func_to_func->hwअगर->pdev->dev, "Send mailbox failed, msg_id: %d\n",
			msg_info.msg_id);
		set_mbox_to_func_event(func_to_func, EVENT_FAIL);
		जाओ err_send_mbox;
	पूर्ण

	समयo = msecs_to_jअगरfies(समयout ? समयout : HINIC_MBOX_COMP_TIME);
	अगर (!रुको_क्रम_completion_समयout(&mbox_क्रम_resp->recv_करोne, समयo)) अणु
		set_mbox_to_func_event(func_to_func, EVENT_TIMEOUT);
		dev_err(&func_to_func->hwअगर->pdev->dev,
			"Send mbox msg timeout, msg_id: %d\n", msg_info.msg_id);
		hinic_dump_aeq_info(func_to_func->hwdev);
		err = -ETIMEDOUT;
		जाओ err_send_mbox;
	पूर्ण

	set_mbox_to_func_event(func_to_func, EVENT_END);

	err = mbox_resp_info_handler(func_to_func, mbox_क्रम_resp, mod, cmd,
				     buf_out, out_size);

err_send_mbox:
	up(&func_to_func->mbox_send_sem);

	वापस err;
पूर्ण

अटल पूर्णांक mbox_func_params_valid(काष्ठा hinic_mbox_func_to_func *func_to_func,
				  व्योम *buf_in, u16 in_size)
अणु
	अगर (in_size > HINIC_MBOX_DATA_SIZE) अणु
		dev_err(&func_to_func->hwअगर->pdev->dev,
			"Mbox msg len(%d) exceed limit(%d)\n",
			in_size, HINIC_MBOX_DATA_SIZE);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_mbox_to_pf(काष्ठा hinic_hwdev *hwdev,
		     क्रमागत hinic_mod_type mod, u8 cmd, व्योम *buf_in,
		     u16 in_size, व्योम *buf_out, u16 *out_size, u32 समयout)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func = hwdev->func_to_func;
	पूर्णांक err = mbox_func_params_valid(func_to_func, buf_in, in_size);

	अगर (err)
		वापस err;

	अगर (!HINIC_IS_VF(hwdev->hwअगर)) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Params error, func_type: %d\n",
			HINIC_FUNC_TYPE(hwdev->hwअगर));
		वापस -EINVAL;
	पूर्ण

	वापस hinic_mbox_to_func(func_to_func, mod, cmd,
				  hinic_pf_id_of_vf_hw(hwdev->hwअगर), buf_in,
				  in_size, buf_out, out_size, समयout);
पूर्ण

पूर्णांक hinic_mbox_to_vf(काष्ठा hinic_hwdev *hwdev,
		     क्रमागत hinic_mod_type mod, u16 vf_id, u8 cmd, व्योम *buf_in,
		     u16 in_size, व्योम *buf_out, u16 *out_size, u32 समयout)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func;
	u16 dst_func_idx;
	पूर्णांक err;

	अगर (!hwdev)
		वापस -EINVAL;

	func_to_func = hwdev->func_to_func;
	err = mbox_func_params_valid(func_to_func, buf_in, in_size);
	अगर (err)
		वापस err;

	अगर (HINIC_IS_VF(hwdev->hwअगर)) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Params error, func_type: %d\n",
			HINIC_FUNC_TYPE(hwdev->hwअगर));
		वापस -EINVAL;
	पूर्ण

	अगर (!vf_id) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"VF id(%d) error!\n", vf_id);
		वापस -EINVAL;
	पूर्ण

	/* vf_offset_to_pf + vf_id is the vf's global function id of vf in
	 * this pf
	 */
	dst_func_idx = hinic_glb_pf_vf_offset(hwdev->hwअगर) + vf_id;

	वापस hinic_mbox_to_func(func_to_func, mod, cmd, dst_func_idx, buf_in,
				  in_size, buf_out, out_size, समयout);
पूर्ण

अटल पूर्णांक init_mbox_info(काष्ठा hinic_recv_mbox *mbox_info)
अणु
	पूर्णांक err;

	mbox_info->seq_id = SEQ_ID_MAX_VAL;

	mbox_info->mbox = kzalloc(MBOX_MAX_BUF_SZ, GFP_KERNEL);
	अगर (!mbox_info->mbox)
		वापस -ENOMEM;

	mbox_info->buf_out = kzalloc(MBOX_MAX_BUF_SZ, GFP_KERNEL);
	अगर (!mbox_info->buf_out) अणु
		err = -ENOMEM;
		जाओ err_alloc_buf_out;
	पूर्ण

	atomic_set(&mbox_info->msg_cnt, 0);

	वापस 0;

err_alloc_buf_out:
	kमुक्त(mbox_info->mbox);

	वापस err;
पूर्ण

अटल व्योम clean_mbox_info(काष्ठा hinic_recv_mbox *mbox_info)
अणु
	kमुक्त(mbox_info->buf_out);
	kमुक्त(mbox_info->mbox);
पूर्ण

अटल पूर्णांक alloc_mbox_info(काष्ठा hinic_hwdev *hwdev,
			   काष्ठा hinic_recv_mbox *mbox_info)
अणु
	u16 func_idx, i;
	पूर्णांक err;

	क्रम (func_idx = 0; func_idx < HINIC_MAX_FUNCTIONS; func_idx++) अणु
		err = init_mbox_info(&mbox_info[func_idx]);
		अगर (err) अणु
			dev_err(&hwdev->hwअगर->pdev->dev, "Failed to init function %d mbox info\n",
				func_idx);
			जाओ err_init_mbox_info;
		पूर्ण
	पूर्ण

	वापस 0;

err_init_mbox_info:
	क्रम (i = 0; i < func_idx; i++)
		clean_mbox_info(&mbox_info[i]);

	वापस err;
पूर्ण

अटल व्योम मुक्त_mbox_info(काष्ठा hinic_recv_mbox *mbox_info)
अणु
	u16 func_idx;

	क्रम (func_idx = 0; func_idx < HINIC_MAX_FUNCTIONS; func_idx++)
		clean_mbox_info(&mbox_info[func_idx]);
पूर्ण

अटल व्योम prepare_send_mbox(काष्ठा hinic_mbox_func_to_func *func_to_func)
अणु
	काष्ठा hinic_send_mbox *send_mbox = &func_to_func->send_mbox;

	send_mbox->data = MBOX_AREA(func_to_func->hwअगर);
पूर्ण

अटल पूर्णांक alloc_mbox_wb_status(काष्ठा hinic_mbox_func_to_func *func_to_func)
अणु
	काष्ठा hinic_send_mbox *send_mbox = &func_to_func->send_mbox;
	काष्ठा hinic_hwdev *hwdev = func_to_func->hwdev;
	u32 addr_h, addr_l;

	send_mbox->wb_vaddr = dma_alloc_coherent(&hwdev->hwअगर->pdev->dev,
						 MBOX_WB_STATUS_LEN,
						 &send_mbox->wb_paddr,
						 GFP_KERNEL);
	अगर (!send_mbox->wb_vaddr)
		वापस -ENOMEM;

	send_mbox->wb_status = send_mbox->wb_vaddr;

	addr_h = upper_32_bits(send_mbox->wb_paddr);
	addr_l = lower_32_bits(send_mbox->wb_paddr);

	hinic_hwअगर_ग_लिखो_reg(hwdev->hwअगर, HINIC_FUNC_CSR_MAILBOX_RESULT_H_OFF,
			     addr_h);
	hinic_hwअगर_ग_लिखो_reg(hwdev->hwअगर, HINIC_FUNC_CSR_MAILBOX_RESULT_L_OFF,
			     addr_l);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_mbox_wb_status(काष्ठा hinic_mbox_func_to_func *func_to_func)
अणु
	काष्ठा hinic_send_mbox *send_mbox = &func_to_func->send_mbox;
	काष्ठा hinic_hwdev *hwdev = func_to_func->hwdev;

	hinic_hwअगर_ग_लिखो_reg(hwdev->hwअगर, HINIC_FUNC_CSR_MAILBOX_RESULT_H_OFF,
			     0);
	hinic_hwअगर_ग_लिखो_reg(hwdev->hwअगर, HINIC_FUNC_CSR_MAILBOX_RESULT_L_OFF,
			     0);

	dma_मुक्त_coherent(&hwdev->hwअगर->pdev->dev, MBOX_WB_STATUS_LEN,
			  send_mbox->wb_vaddr,
			  send_mbox->wb_paddr);
पूर्ण

bool hinic_mbox_check_cmd_valid(काष्ठा hinic_hwdev *hwdev,
				काष्ठा vf_cmd_check_handle *cmd_handle,
				u16 vf_id, u8 cmd, व्योम *buf_in,
				u16 in_size, u8 size)
अणु
	u16 src_idx = vf_id + hinic_glb_pf_vf_offset(hwdev->hwअगर);
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (cmd == cmd_handle[i].cmd) अणु
			अगर (cmd_handle[i].check_cmd)
				वापस cmd_handle[i].check_cmd(hwdev, src_idx,
							       buf_in, in_size);
			अन्यथा
				वापस true;
		पूर्ण
	पूर्ण

	dev_err(&hwdev->hwअगर->pdev->dev,
		"PF Receive VF(%d) unsupported cmd(0x%x)\n",
		vf_id + hinic_glb_pf_vf_offset(hwdev->hwअगर), cmd);

	वापस false;
पूर्ण

अटल bool hinic_cmdq_check_vf_ctxt(काष्ठा hinic_hwdev *hwdev,
				     काष्ठा hinic_cmdq_ctxt *cmdq_ctxt)
अणु
	काष्ठा hinic_cmdq_ctxt_info *ctxt_info = &cmdq_ctxt->ctxt_info;
	u64 curr_pg_pfn, wq_block_pfn;

	अगर (cmdq_ctxt->ppf_idx != HINIC_HWIF_PPF_IDX(hwdev->hwअगर) ||
	    cmdq_ctxt->cmdq_type > HINIC_MAX_CMDQ_TYPES)
		वापस false;

	curr_pg_pfn = HINIC_CMDQ_CTXT_PAGE_INFO_GET
		(ctxt_info->curr_wqe_page_pfn, CURR_WQE_PAGE_PFN);
	wq_block_pfn = HINIC_CMDQ_CTXT_BLOCK_INFO_GET
		(ctxt_info->wq_block_pfn, WQ_BLOCK_PFN);
	/* VF must use 0-level CLA */
	अगर (curr_pg_pfn != wq_block_pfn)
		वापस false;

	वापस true;
पूर्ण

अटल bool check_cmdq_ctxt(काष्ठा hinic_hwdev *hwdev, u16 func_idx,
			    व्योम *buf_in, u16 in_size)
अणु
	अगर (!hinic_mbox_check_func_id_8B(hwdev, func_idx, buf_in, in_size))
		वापस false;

	वापस hinic_cmdq_check_vf_ctxt(hwdev, buf_in);
पूर्ण

#घोषणा HW_CTX_QPS_VALID(hw_ctxt)   \
		((hw_ctxt)->rq_depth >= HINIC_QUEUE_MIN_DEPTH &&	\
		(hw_ctxt)->rq_depth <= HINIC_QUEUE_MAX_DEPTH &&	\
		(hw_ctxt)->sq_depth >= HINIC_QUEUE_MIN_DEPTH &&	\
		(hw_ctxt)->sq_depth <= HINIC_QUEUE_MAX_DEPTH &&	\
		(hw_ctxt)->rx_buf_sz_idx <= HINIC_MAX_RX_BUFFER_SIZE)

अटल bool hw_ctxt_qps_param_valid(काष्ठा hinic_cmd_hw_ioctxt *hw_ctxt)
अणु
	अगर (HW_CTX_QPS_VALID(hw_ctxt))
		वापस true;

	अगर (!hw_ctxt->rq_depth && !hw_ctxt->sq_depth &&
	    !hw_ctxt->rx_buf_sz_idx)
		वापस true;

	वापस false;
पूर्ण

अटल bool check_hwctxt(काष्ठा hinic_hwdev *hwdev, u16 func_idx,
			 व्योम *buf_in, u16 in_size)
अणु
	काष्ठा hinic_cmd_hw_ioctxt *hw_ctxt = buf_in;

	अगर (!hinic_mbox_check_func_id_8B(hwdev, func_idx, buf_in, in_size))
		वापस false;

	अगर (hw_ctxt->ppf_idx != HINIC_HWIF_PPF_IDX(hwdev->hwअगर))
		वापस false;

	अगर (hw_ctxt->set_cmdq_depth) अणु
		अगर (hw_ctxt->cmdq_depth >= HINIC_QUEUE_MIN_DEPTH &&
		    hw_ctxt->cmdq_depth <= HINIC_QUEUE_MAX_DEPTH)
			वापस true;

		वापस false;
	पूर्ण

	वापस hw_ctxt_qps_param_valid(hw_ctxt);
पूर्ण

अटल bool check_set_wq_page_size(काष्ठा hinic_hwdev *hwdev, u16 func_idx,
				   व्योम *buf_in, u16 in_size)
अणु
	काष्ठा hinic_wq_page_size *page_size_info = buf_in;

	अगर (!hinic_mbox_check_func_id_8B(hwdev, func_idx, buf_in, in_size))
		वापस false;

	अगर (page_size_info->ppf_idx != HINIC_HWIF_PPF_IDX(hwdev->hwअगर))
		वापस false;

	अगर (((1U << page_size_info->page_size) * SZ_4K) !=
	    HINIC_DEFAULT_WQ_PAGE_SIZE)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा vf_cmd_check_handle hw_cmd_support_vf[] = अणु
	अणुHINIC_COMM_CMD_START_FLR, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_COMM_CMD_DMA_ATTR_SET, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_COMM_CMD_CMDQ_CTXT_SET, check_cmdq_ctxtपूर्ण,
	अणुHINIC_COMM_CMD_CMDQ_CTXT_GET, check_cmdq_ctxtपूर्ण,
	अणुHINIC_COMM_CMD_HWCTXT_SET, check_hwctxtपूर्ण,
	अणुHINIC_COMM_CMD_HWCTXT_GET, check_hwctxtपूर्ण,
	अणुHINIC_COMM_CMD_SQ_HI_CI_SET, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_COMM_CMD_RES_STATE_SET, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_COMM_CMD_IO_RES_CLEAR, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_COMM_CMD_CEQ_CTRL_REG_WR_BY_UP, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_COMM_CMD_MSI_CTRL_REG_WR_BY_UP, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_COMM_CMD_MSI_CTRL_REG_RD_BY_UP, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_COMM_CMD_L2NIC_RESET, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_COMM_CMD_PAGESIZE_SET, check_set_wq_page_sizeपूर्ण,
पूर्ण;

अटल पूर्णांक comm_pf_mbox_handler(व्योम *handle, u16 vf_id, u8 cmd, व्योम *buf_in,
				u16 in_size, व्योम *buf_out, u16 *out_size)
अणु
	u8 size = ARRAY_SIZE(hw_cmd_support_vf);
	काष्ठा hinic_hwdev *hwdev = handle;
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err = 0;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	अगर (!hinic_mbox_check_cmd_valid(handle, hw_cmd_support_vf, vf_id, cmd,
					buf_in, in_size, size)) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"PF Receive VF: %d common cmd: 0x%x or mbox len: 0x%x is invalid\n",
			vf_id + hinic_glb_pf_vf_offset(hwdev->hwअगर), cmd,
			in_size);
		वापस HINIC_MBOX_VF_CMD_ERROR;
	पूर्ण

	अगर (cmd == HINIC_COMM_CMD_START_FLR) अणु
		*out_size = 0;
	पूर्ण अन्यथा अणु
		err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
					cmd, buf_in, in_size, buf_out, out_size,
					HINIC_MGMT_MSG_SYNC);
		अगर (err && err != HINIC_MBOX_PF_BUSY_ACTIVE_FW)
			dev_err(&hwdev->hwअगर->pdev->dev,
				"PF mbox common callback handler err: %d\n",
				err);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक hinic_func_to_func_init(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func;
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err;

	pfhwdev =  container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);
	func_to_func = kzalloc(माप(*func_to_func), GFP_KERNEL);
	अगर (!func_to_func)
		वापस -ENOMEM;

	hwdev->func_to_func = func_to_func;
	func_to_func->hwdev = hwdev;
	func_to_func->hwअगर = hwdev->hwअगर;
	sema_init(&func_to_func->mbox_send_sem, 1);
	sema_init(&func_to_func->msg_send_sem, 1);
	spin_lock_init(&func_to_func->mbox_lock);
	func_to_func->workq = create_singlethपढ़ो_workqueue(HINIC_MBOX_WQ_NAME);
	अगर (!func_to_func->workq) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to initialize MBOX workqueue\n");
		err = -ENOMEM;
		जाओ err_create_mbox_workq;
	पूर्ण

	err = alloc_mbox_info(hwdev, func_to_func->mbox_send);
	अगर (err) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to alloc mem for mbox_active\n");
		जाओ err_alloc_mbox_क्रम_send;
	पूर्ण

	err = alloc_mbox_info(hwdev, func_to_func->mbox_resp);
	अगर (err) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to alloc mem for mbox_passive\n");
		जाओ err_alloc_mbox_क्रम_resp;
	पूर्ण

	err = alloc_mbox_wb_status(func_to_func);
	अगर (err) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to alloc mbox write back status\n");
		जाओ err_alloc_wb_status;
	पूर्ण

	prepare_send_mbox(func_to_func);

	hinic_aeq_रेजिस्टर_hw_cb(&hwdev->aeqs, HINIC_MBX_FROM_FUNC,
				 &pfhwdev->hwdev, hinic_mbox_func_aeqe_handler);
	hinic_aeq_रेजिस्टर_hw_cb(&hwdev->aeqs, HINIC_MBX_SEND_RSLT,
				 &pfhwdev->hwdev, hinic_mbox_self_aeqe_handler);

	अगर (!HINIC_IS_VF(hwdev->hwअगर))
		hinic_रेजिस्टर_pf_mbox_cb(hwdev, HINIC_MOD_COMM,
					  comm_pf_mbox_handler);

	वापस 0;

err_alloc_wb_status:
	मुक्त_mbox_info(func_to_func->mbox_resp);

err_alloc_mbox_क्रम_resp:
	मुक्त_mbox_info(func_to_func->mbox_send);

err_alloc_mbox_क्रम_send:
	destroy_workqueue(func_to_func->workq);

err_create_mbox_workq:
	kमुक्त(func_to_func);

	वापस err;
पूर्ण

व्योम hinic_func_to_func_मुक्त(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_mbox_func_to_func *func_to_func = hwdev->func_to_func;

	hinic_aeq_unरेजिस्टर_hw_cb(&hwdev->aeqs, HINIC_MBX_FROM_FUNC);
	hinic_aeq_unरेजिस्टर_hw_cb(&hwdev->aeqs, HINIC_MBX_SEND_RSLT);

	hinic_unरेजिस्टर_pf_mbox_cb(hwdev, HINIC_MOD_COMM);
	/* destroy workqueue beक्रमe मुक्त related mbox resources in हाल of
	 * illegal resource access
	 */
	destroy_workqueue(func_to_func->workq);

	मुक्त_mbox_wb_status(func_to_func);
	मुक्त_mbox_info(func_to_func->mbox_resp);
	मुक्त_mbox_info(func_to_func->mbox_send);

	kमुक्त(func_to_func);
पूर्ण

पूर्णांक hinic_vf_mbox_अक्रमom_id_init(काष्ठा hinic_hwdev *hwdev)
अणु
	u16 vf_offset;
	u8 vf_in_pf;
	पूर्णांक err = 0;

	अगर (HINIC_IS_VF(hwdev->hwअगर))
		वापस 0;

	vf_offset = hinic_glb_pf_vf_offset(hwdev->hwअगर);

	क्रम (vf_in_pf = 1; vf_in_pf <= hwdev->nic_cap.max_vf; vf_in_pf++) अणु
		err = set_vf_mbox_अक्रमom_id(hwdev, vf_offset + vf_in_pf);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (err == HINIC_MGMT_CMD_UNSUPPORTED) अणु
		hwdev->func_to_func->support_vf_अक्रमom = false;
		err = 0;
		dev_warn(&hwdev->hwअगर->pdev->dev, "Mgmt is unsupported to set VF%d random id\n",
			 vf_in_pf - 1);
	पूर्ण अन्यथा अगर (!err) अणु
		hwdev->func_to_func->support_vf_अक्रमom = true;
	पूर्ण

	वापस err;
पूर्ण
