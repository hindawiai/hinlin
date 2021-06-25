<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>
#समावेश <net/devlink.h>
#समावेश <यंत्र/barrier.h>

#समावेश "hinic_devlink.h"
#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_eqs.h"
#समावेश "hinic_hw_api_cmd.h"
#समावेश "hinic_hw_mgmt.h"
#समावेश "hinic_hw_dev.h"

#घोषणा SYNC_MSG_ID_MASK                0x1FF

#घोषणा SYNC_MSG_ID(pf_to_mgmt)         ((pf_to_mgmt)->sync_msg_id)

#घोषणा SYNC_MSG_ID_INC(pf_to_mgmt)     (SYNC_MSG_ID(pf_to_mgmt) = \
					((SYNC_MSG_ID(pf_to_mgmt) + 1) & \
					 SYNC_MSG_ID_MASK))

#घोषणा MSG_SZ_IS_VALID(in_size)        ((in_size) <= MAX_MSG_LEN)

#घोषणा MGMT_MSG_LEN_MIN                20
#घोषणा MGMT_MSG_LEN_STEP               16
#घोषणा MGMT_MSG_RSVD_FOR_DEV           8

#घोषणा SEGMENT_LEN                     48

#घोषणा MAX_PF_MGMT_BUF_SIZE            2048

/* Data should be SEG LEN size aligned */
#घोषणा MAX_MSG_LEN                     2016

#घोषणा MSG_NOT_RESP                    0xFFFF

#घोषणा MGMT_MSG_TIMEOUT                5000

#घोषणा SET_FUNC_PORT_MBOX_TIMEOUT	30000

#घोषणा SET_FUNC_PORT_MGMT_TIMEOUT	25000

#घोषणा UPDATE_FW_MGMT_TIMEOUT		20000

#घोषणा mgmt_to_pfhwdev(pf_mgmt)        \
		container_of(pf_mgmt, काष्ठा hinic_pfhwdev, pf_to_mgmt)

क्रमागत msg_segment_type अणु
	NOT_LAST_SEGMENT = 0,
	LAST_SEGMENT     = 1,
पूर्ण;

क्रमागत mgmt_direction_type अणु
	MGMT_सूचीECT_SEND = 0,
	MGMT_RESP        = 1,
पूर्ण;

क्रमागत msg_ack_type अणु
	MSG_ACK         = 0,
	MSG_NO_ACK      = 1,
पूर्ण;

/**
 * hinic_रेजिस्टर_mgmt_msg_cb - रेजिस्टर msg handler क्रम a msg from a module
 * @pf_to_mgmt: PF to MGMT channel
 * @mod: module in the chip that this handler will handle its messages
 * @handle: निजी data क्रम the callback
 * @callback: the handler that will handle messages
 **/
व्योम hinic_रेजिस्टर_mgmt_msg_cb(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
				क्रमागत hinic_mod_type mod,
				व्योम *handle,
				व्योम (*callback)(व्योम *handle,
						 u8 cmd, व्योम *buf_in,
						 u16 in_size, व्योम *buf_out,
						 u16 *out_size))
अणु
	काष्ठा hinic_mgmt_cb *mgmt_cb = &pf_to_mgmt->mgmt_cb[mod];

	mgmt_cb->cb = callback;
	mgmt_cb->handle = handle;
	mgmt_cb->state = HINIC_MGMT_CB_ENABLED;
पूर्ण

/**
 * hinic_unरेजिस्टर_mgmt_msg_cb - unरेजिस्टर msg handler क्रम a msg from a module
 * @pf_to_mgmt: PF to MGMT channel
 * @mod: module in the chip that this handler handles its messages
 **/
व्योम hinic_unरेजिस्टर_mgmt_msg_cb(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
				  क्रमागत hinic_mod_type mod)
अणु
	काष्ठा hinic_mgmt_cb *mgmt_cb = &pf_to_mgmt->mgmt_cb[mod];

	mgmt_cb->state &= ~HINIC_MGMT_CB_ENABLED;

	जबतक (mgmt_cb->state & HINIC_MGMT_CB_RUNNING)
		schedule();

	mgmt_cb->cb = शून्य;
पूर्ण

/**
 * prepare_header - prepare the header of the message
 * @pf_to_mgmt: PF to MGMT channel
 * @msg_len: the length of the message
 * @mod: module in the chip that will get the message
 * @ack_type: ask क्रम response
 * @direction: the direction of the message
 * @cmd: command of the message
 * @msg_id: message id
 *
 * Return the prepared header value
 **/
अटल u64 prepare_header(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
			  u16 msg_len, क्रमागत hinic_mod_type mod,
			  क्रमागत msg_ack_type ack_type,
			  क्रमागत mgmt_direction_type direction,
			  u16 cmd, u16 msg_id)
अणु
	काष्ठा hinic_hwअगर *hwअगर = pf_to_mgmt->hwअगर;

	वापस HINIC_MSG_HEADER_SET(msg_len, MSG_LEN)           |
	       HINIC_MSG_HEADER_SET(mod, MODULE)                |
	       HINIC_MSG_HEADER_SET(SEGMENT_LEN, SEG_LEN)       |
	       HINIC_MSG_HEADER_SET(ack_type, NO_ACK)           |
	       HINIC_MSG_HEADER_SET(0, ASYNC_MGMT_TO_PF)        |
	       HINIC_MSG_HEADER_SET(0, SEQID)                   |
	       HINIC_MSG_HEADER_SET(LAST_SEGMENT, LAST)         |
	       HINIC_MSG_HEADER_SET(direction, सूचीECTION)       |
	       HINIC_MSG_HEADER_SET(cmd, CMD)                   |
	       HINIC_MSG_HEADER_SET(HINIC_HWIF_PCI_INTF(hwअगर), PCI_INTF) |
	       HINIC_MSG_HEADER_SET(HINIC_HWIF_PF_IDX(hwअगर), PF_IDX)     |
	       HINIC_MSG_HEADER_SET(msg_id, MSG_ID);
पूर्ण

/**
 * prepare_mgmt_cmd - prepare the mgmt command
 * @mgmt_cmd: poपूर्णांकer to the command to prepare
 * @header: poपूर्णांकer of the header क्रम the message
 * @msg: the data of the message
 * @msg_len: the length of the message
 **/
अटल व्योम prepare_mgmt_cmd(u8 *mgmt_cmd, u64 *header, u8 *msg, u16 msg_len)
अणु
	स_रखो(mgmt_cmd, 0, MGMT_MSG_RSVD_FOR_DEV);

	mgmt_cmd += MGMT_MSG_RSVD_FOR_DEV;
	स_नकल(mgmt_cmd, header, माप(*header));

	mgmt_cmd += माप(*header);
	स_नकल(mgmt_cmd, msg, msg_len);
पूर्ण

/**
 * mgmt_msg_len - calculate the total message length
 * @msg_data_len: the length of the message data
 *
 * Return the total message length
 **/
अटल u16 mgmt_msg_len(u16 msg_data_len)
अणु
	/* RSVD + HEADER_SIZE + DATA_LEN */
	u16 msg_len = MGMT_MSG_RSVD_FOR_DEV + माप(u64) + msg_data_len;

	अगर (msg_len > MGMT_MSG_LEN_MIN)
		msg_len = MGMT_MSG_LEN_MIN +
			   ALIGN((msg_len - MGMT_MSG_LEN_MIN),
				 MGMT_MSG_LEN_STEP);
	अन्यथा
		msg_len = MGMT_MSG_LEN_MIN;

	वापस msg_len;
पूर्ण

/**
 * send_msg_to_mgmt - send message to mgmt by API CMD
 * @pf_to_mgmt: PF to MGMT channel
 * @mod: module in the chip that will get the message
 * @cmd: command of the message
 * @data: the msg data
 * @data_len: the msg data length
 * @ack_type: ask क्रम response
 * @direction: the direction of the original message
 * @resp_msg_id: msg id to response क्रम
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक send_msg_to_mgmt(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
			    क्रमागत hinic_mod_type mod, u8 cmd,
			    u8 *data, u16 data_len,
			    क्रमागत msg_ack_type ack_type,
			    क्रमागत mgmt_direction_type direction,
			    u16 resp_msg_id)
अणु
	काष्ठा hinic_api_cmd_chain *chain;
	u64 header;
	u16 msg_id;

	msg_id = SYNC_MSG_ID(pf_to_mgmt);

	अगर (direction == MGMT_RESP) अणु
		header = prepare_header(pf_to_mgmt, data_len, mod, ack_type,
					direction, cmd, resp_msg_id);
	पूर्ण अन्यथा अणु
		SYNC_MSG_ID_INC(pf_to_mgmt);
		header = prepare_header(pf_to_mgmt, data_len, mod, ack_type,
					direction, cmd, msg_id);
	पूर्ण

	prepare_mgmt_cmd(pf_to_mgmt->sync_msg_buf, &header, data, data_len);

	chain = pf_to_mgmt->cmd_chain[HINIC_API_CMD_WRITE_TO_MGMT_CPU];
	वापस hinic_api_cmd_ग_लिखो(chain, HINIC_NODE_ID_MGMT,
				   pf_to_mgmt->sync_msg_buf,
				   mgmt_msg_len(data_len));
पूर्ण

/**
 * msg_to_mgmt_sync - send sync message to mgmt
 * @pf_to_mgmt: PF to MGMT channel
 * @mod: module in the chip that will get the message
 * @cmd: command of the message
 * @buf_in: the msg data
 * @in_size: the msg data length
 * @buf_out: response
 * @out_size: response length
 * @direction: the direction of the original message
 * @resp_msg_id: msg id to response क्रम
 * @समयout: समय-out period of रुकोing क्रम response
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक msg_to_mgmt_sync(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
			    क्रमागत hinic_mod_type mod, u8 cmd,
			    u8 *buf_in, u16 in_size,
			    u8 *buf_out, u16 *out_size,
			    क्रमागत mgmt_direction_type direction,
			    u16 resp_msg_id, u32 समयout)
अणु
	काष्ठा hinic_hwअगर *hwअगर = pf_to_mgmt->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_recv_msg *recv_msg;
	काष्ठा completion *recv_करोne;
	अचिन्हित दीर्घ समयo;
	u16 msg_id;
	पूर्णांक err;

	/* Lock the sync_msg_buf */
	करोwn(&pf_to_mgmt->sync_msg_lock);

	recv_msg = &pf_to_mgmt->recv_resp_msg_from_mgmt;
	recv_करोne = &recv_msg->recv_करोne;

	अगर (resp_msg_id == MSG_NOT_RESP)
		msg_id = SYNC_MSG_ID(pf_to_mgmt);
	अन्यथा
		msg_id = resp_msg_id;

	init_completion(recv_करोne);

	err = send_msg_to_mgmt(pf_to_mgmt, mod, cmd, buf_in, in_size,
			       MSG_ACK, direction, resp_msg_id);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to send sync msg to mgmt\n");
		जाओ unlock_sync_msg;
	पूर्ण

	समयo = msecs_to_jअगरfies(समयout ? समयout : MGMT_MSG_TIMEOUT);

	अगर (!रुको_क्रम_completion_समयout(recv_करोne, समयo)) अणु
		dev_err(&pdev->dev, "MGMT timeout, MSG id = %d\n", msg_id);
		hinic_dump_aeq_info(pf_to_mgmt->hwdev);
		err = -ETIMEDOUT;
		जाओ unlock_sync_msg;
	पूर्ण

	smp_rmb();      /* verअगरy पढ़ोing after completion */

	अगर (recv_msg->msg_id != msg_id) अणु
		dev_err(&pdev->dev, "incorrect MSG for id = %d\n", msg_id);
		err = -EFAULT;
		जाओ unlock_sync_msg;
	पूर्ण

	अगर ((buf_out) && (recv_msg->msg_len <= MAX_PF_MGMT_BUF_SIZE)) अणु
		स_नकल(buf_out, recv_msg->msg, recv_msg->msg_len);
		*out_size = recv_msg->msg_len;
	पूर्ण

unlock_sync_msg:
	up(&pf_to_mgmt->sync_msg_lock);
	वापस err;
पूर्ण

/**
 * msg_to_mgmt_async - send message to mgmt without response
 * @pf_to_mgmt: PF to MGMT channel
 * @mod: module in the chip that will get the message
 * @cmd: command of the message
 * @buf_in: the msg data
 * @in_size: the msg data length
 * @direction: the direction of the original message
 * @resp_msg_id: msg id to response क्रम
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक msg_to_mgmt_async(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
			     क्रमागत hinic_mod_type mod, u8 cmd,
			     u8 *buf_in, u16 in_size,
			     क्रमागत mgmt_direction_type direction,
			     u16 resp_msg_id)
अणु
	पूर्णांक err;

	/* Lock the sync_msg_buf */
	करोwn(&pf_to_mgmt->sync_msg_lock);

	err = send_msg_to_mgmt(pf_to_mgmt, mod, cmd, buf_in, in_size,
			       MSG_NO_ACK, direction, resp_msg_id);

	up(&pf_to_mgmt->sync_msg_lock);
	वापस err;
पूर्ण

/**
 * hinic_msg_to_mgmt - send message to mgmt
 * @pf_to_mgmt: PF to MGMT channel
 * @mod: module in the chip that will get the message
 * @cmd: command of the message
 * @buf_in: the msg data
 * @in_size: the msg data length
 * @buf_out: response
 * @out_size: वापसed response length
 * @sync: sync msg or async msg
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_msg_to_mgmt(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
		      क्रमागत hinic_mod_type mod, u8 cmd,
		      व्योम *buf_in, u16 in_size, व्योम *buf_out, u16 *out_size,
		      क्रमागत hinic_mgmt_msg_type sync)
अणु
	काष्ठा hinic_hwअगर *hwअगर = pf_to_mgmt->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u32 समयout = 0;

	अगर (sync != HINIC_MGMT_MSG_SYNC) अणु
		dev_err(&pdev->dev, "Invalid MGMT msg type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!MSG_SZ_IS_VALID(in_size)) अणु
		dev_err(&pdev->dev, "Invalid MGMT msg buffer size\n");
		वापस -EINVAL;
	पूर्ण

	अगर (HINIC_IS_VF(hwअगर)) अणु
		अगर (cmd == HINIC_PORT_CMD_SET_FUNC_STATE)
			समयout = SET_FUNC_PORT_MBOX_TIMEOUT;

		वापस hinic_mbox_to_pf(pf_to_mgmt->hwdev, mod, cmd, buf_in,
					in_size, buf_out, out_size, समयout);
	पूर्ण अन्यथा अणु
		अगर (cmd == HINIC_PORT_CMD_SET_FUNC_STATE)
			समयout = SET_FUNC_PORT_MGMT_TIMEOUT;
		अन्यथा अगर (cmd == HINIC_PORT_CMD_UPDATE_FW)
			समयout = UPDATE_FW_MGMT_TIMEOUT;

		वापस msg_to_mgmt_sync(pf_to_mgmt, mod, cmd, buf_in, in_size,
				buf_out, out_size, MGMT_सूचीECT_SEND,
				MSG_NOT_RESP, समयout);
	पूर्ण
पूर्ण

अटल व्योम recv_mgmt_msg_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hinic_mgmt_msg_handle_work *mgmt_work =
		container_of(work, काष्ठा hinic_mgmt_msg_handle_work, work);
	काष्ठा hinic_pf_to_mgmt *pf_to_mgmt = mgmt_work->pf_to_mgmt;
	काष्ठा pci_dev *pdev = pf_to_mgmt->hwअगर->pdev;
	u8 *buf_out = pf_to_mgmt->mgmt_ack_buf;
	काष्ठा hinic_mgmt_cb *mgmt_cb;
	अचिन्हित दीर्घ cb_state;
	u16 out_size = 0;

	स_रखो(buf_out, 0, MAX_PF_MGMT_BUF_SIZE);

	अगर (mgmt_work->mod >= HINIC_MOD_MAX) अणु
		dev_err(&pdev->dev, "Unknown MGMT MSG module = %d\n",
			mgmt_work->mod);
		kमुक्त(mgmt_work->msg);
		kमुक्त(mgmt_work);
		वापस;
	पूर्ण

	mgmt_cb = &pf_to_mgmt->mgmt_cb[mgmt_work->mod];

	cb_state = cmpxchg(&mgmt_cb->state,
			   HINIC_MGMT_CB_ENABLED,
			   HINIC_MGMT_CB_ENABLED | HINIC_MGMT_CB_RUNNING);

	अगर ((cb_state == HINIC_MGMT_CB_ENABLED) && (mgmt_cb->cb))
		mgmt_cb->cb(mgmt_cb->handle, mgmt_work->cmd,
			    mgmt_work->msg, mgmt_work->msg_len,
			    buf_out, &out_size);
	अन्यथा
		dev_err(&pdev->dev, "No MGMT msg handler, mod: %d, cmd: %d\n",
			mgmt_work->mod, mgmt_work->cmd);

	mgmt_cb->state &= ~HINIC_MGMT_CB_RUNNING;

	अगर (!mgmt_work->async_mgmt_to_pf)
		/* MGMT sent sync msg, send the response */
		msg_to_mgmt_async(pf_to_mgmt, mgmt_work->mod, mgmt_work->cmd,
				  buf_out, out_size, MGMT_RESP,
				  mgmt_work->msg_id);

	kमुक्त(mgmt_work->msg);
	kमुक्त(mgmt_work);
पूर्ण

/**
 * mgmt_recv_msg_handler - handler क्रम message from mgmt cpu
 * @pf_to_mgmt: PF to MGMT channel
 * @recv_msg: received message details
 **/
अटल व्योम mgmt_recv_msg_handler(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
				  काष्ठा hinic_recv_msg *recv_msg)
अणु
	काष्ठा hinic_mgmt_msg_handle_work *mgmt_work = शून्य;

	mgmt_work = kzalloc(माप(*mgmt_work), GFP_KERNEL);
	अगर (!mgmt_work)
		वापस;

	अगर (recv_msg->msg_len) अणु
		mgmt_work->msg = kzalloc(recv_msg->msg_len, GFP_KERNEL);
		अगर (!mgmt_work->msg) अणु
			kमुक्त(mgmt_work);
			वापस;
		पूर्ण
	पूर्ण

	mgmt_work->pf_to_mgmt = pf_to_mgmt;
	mgmt_work->msg_len = recv_msg->msg_len;
	स_नकल(mgmt_work->msg, recv_msg->msg, recv_msg->msg_len);
	mgmt_work->msg_id = recv_msg->msg_id;
	mgmt_work->mod = recv_msg->mod;
	mgmt_work->cmd = recv_msg->cmd;
	mgmt_work->async_mgmt_to_pf = recv_msg->async_mgmt_to_pf;

	INIT_WORK(&mgmt_work->work, recv_mgmt_msg_work_handler);
	queue_work(pf_to_mgmt->workq, &mgmt_work->work);
पूर्ण

/**
 * mgmt_resp_msg_handler - handler क्रम a response message from mgmt cpu
 * @pf_to_mgmt: PF to MGMT channel
 * @recv_msg: received message details
 **/
अटल व्योम mgmt_resp_msg_handler(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
				  काष्ठा hinic_recv_msg *recv_msg)
अणु
	wmb();  /* verअगरy writing all, beक्रमe पढ़ोing */

	complete(&recv_msg->recv_करोne);
पूर्ण

/**
 * recv_mgmt_msg_handler - handler क्रम a message from mgmt cpu
 * @pf_to_mgmt: PF to MGMT channel
 * @header: the header of the message
 * @recv_msg: received message details
 **/
अटल व्योम recv_mgmt_msg_handler(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
				  u64 *header, काष्ठा hinic_recv_msg *recv_msg)
अणु
	काष्ठा hinic_hwअगर *hwअगर = pf_to_mgmt->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक seq_id, seg_len;
	u8 *msg_body;

	seq_id = HINIC_MSG_HEADER_GET(*header, SEQID);
	seg_len = HINIC_MSG_HEADER_GET(*header, SEG_LEN);

	अगर (seq_id >= (MAX_MSG_LEN / SEGMENT_LEN)) अणु
		dev_err(&pdev->dev, "recv big mgmt msg\n");
		वापस;
	पूर्ण

	msg_body = (u8 *)header + माप(*header);
	स_नकल(recv_msg->msg + seq_id * SEGMENT_LEN, msg_body, seg_len);

	अगर (!HINIC_MSG_HEADER_GET(*header, LAST))
		वापस;

	recv_msg->cmd = HINIC_MSG_HEADER_GET(*header, CMD);
	recv_msg->mod = HINIC_MSG_HEADER_GET(*header, MODULE);
	recv_msg->async_mgmt_to_pf = HINIC_MSG_HEADER_GET(*header,
							  ASYNC_MGMT_TO_PF);
	recv_msg->msg_len = HINIC_MSG_HEADER_GET(*header, MSG_LEN);
	recv_msg->msg_id = HINIC_MSG_HEADER_GET(*header, MSG_ID);

	अगर (HINIC_MSG_HEADER_GET(*header, सूचीECTION) == MGMT_RESP)
		mgmt_resp_msg_handler(pf_to_mgmt, recv_msg);
	अन्यथा
		mgmt_recv_msg_handler(pf_to_mgmt, recv_msg);
पूर्ण

/**
 * mgmt_msg_aeqe_handler - handler क्रम a mgmt message event
 * @handle: PF to MGMT channel
 * @data: the header of the message
 * @size: unused
 **/
अटल व्योम mgmt_msg_aeqe_handler(व्योम *handle, व्योम *data, u8 size)
अणु
	काष्ठा hinic_pf_to_mgmt *pf_to_mgmt = handle;
	काष्ठा hinic_recv_msg *recv_msg;
	u64 *header = (u64 *)data;

	recv_msg = HINIC_MSG_HEADER_GET(*header, सूचीECTION) ==
		   MGMT_सूचीECT_SEND ?
		   &pf_to_mgmt->recv_msg_from_mgmt :
		   &pf_to_mgmt->recv_resp_msg_from_mgmt;

	recv_mgmt_msg_handler(pf_to_mgmt, header, recv_msg);
पूर्ण

/**
 * alloc_recv_msg - allocate receive message memory
 * @pf_to_mgmt: PF to MGMT channel
 * @recv_msg: poपूर्णांकer that will hold the allocated data
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक alloc_recv_msg(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
			  काष्ठा hinic_recv_msg *recv_msg)
अणु
	काष्ठा hinic_hwअगर *hwअगर = pf_to_mgmt->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	recv_msg->msg = devm_kzalloc(&pdev->dev, MAX_PF_MGMT_BUF_SIZE,
				     GFP_KERNEL);
	अगर (!recv_msg->msg)
		वापस -ENOMEM;

	recv_msg->buf_out = devm_kzalloc(&pdev->dev, MAX_PF_MGMT_BUF_SIZE,
					 GFP_KERNEL);
	अगर (!recv_msg->buf_out)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * alloc_msg_buf - allocate all the message buffers of PF to MGMT channel
 * @pf_to_mgmt: PF to MGMT channel
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक alloc_msg_buf(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt)
अणु
	काष्ठा hinic_hwअगर *hwअगर = pf_to_mgmt->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	err = alloc_recv_msg(pf_to_mgmt,
			     &pf_to_mgmt->recv_msg_from_mgmt);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate recv msg\n");
		वापस err;
	पूर्ण

	err = alloc_recv_msg(pf_to_mgmt,
			     &pf_to_mgmt->recv_resp_msg_from_mgmt);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate resp recv msg\n");
		वापस err;
	पूर्ण

	pf_to_mgmt->sync_msg_buf = devm_kzalloc(&pdev->dev,
						MAX_PF_MGMT_BUF_SIZE,
						GFP_KERNEL);
	अगर (!pf_to_mgmt->sync_msg_buf)
		वापस -ENOMEM;

	pf_to_mgmt->mgmt_ack_buf = devm_kzalloc(&pdev->dev,
						MAX_PF_MGMT_BUF_SIZE,
						GFP_KERNEL);
	अगर (!pf_to_mgmt->mgmt_ack_buf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * hinic_pf_to_mgmt_init - initialize PF to MGMT channel
 * @pf_to_mgmt: PF to MGMT channel
 * @hwअगर: HW पूर्णांकerface the PF to MGMT will use क्रम accessing HW
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_pf_to_mgmt_init(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt,
			  काष्ठा hinic_hwअगर *hwअगर)
अणु
	काष्ठा hinic_pfhwdev *pfhwdev = mgmt_to_pfhwdev(pf_to_mgmt);
	काष्ठा hinic_hwdev *hwdev = &pfhwdev->hwdev;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	pf_to_mgmt->hwअगर = hwअगर;
	pf_to_mgmt->hwdev = hwdev;

	अगर (HINIC_IS_VF(hwअगर))
		वापस 0;

	err = hinic_health_reporters_create(hwdev->devlink_dev);
	अगर (err)
		वापस err;

	sema_init(&pf_to_mgmt->sync_msg_lock, 1);
	pf_to_mgmt->workq = create_singlethपढ़ो_workqueue("hinic_mgmt");
	अगर (!pf_to_mgmt->workq) अणु
		dev_err(&pdev->dev, "Failed to initialize MGMT workqueue\n");
		hinic_health_reporters_destroy(hwdev->devlink_dev);
		वापस -ENOMEM;
	पूर्ण
	pf_to_mgmt->sync_msg_id = 0;

	err = alloc_msg_buf(pf_to_mgmt);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate msg buffers\n");
		hinic_health_reporters_destroy(hwdev->devlink_dev);
		वापस err;
	पूर्ण

	err = hinic_api_cmd_init(pf_to_mgmt->cmd_chain, hwअगर);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize cmd chains\n");
		hinic_health_reporters_destroy(hwdev->devlink_dev);
		वापस err;
	पूर्ण

	hinic_aeq_रेजिस्टर_hw_cb(&hwdev->aeqs, HINIC_MSG_FROM_MGMT_CPU,
				 pf_to_mgmt,
				 mgmt_msg_aeqe_handler);
	वापस 0;
पूर्ण

/**
 * hinic_pf_to_mgmt_मुक्त - मुक्त PF to MGMT channel
 * @pf_to_mgmt: PF to MGMT channel
 **/
व्योम hinic_pf_to_mgmt_मुक्त(काष्ठा hinic_pf_to_mgmt *pf_to_mgmt)
अणु
	काष्ठा hinic_pfhwdev *pfhwdev = mgmt_to_pfhwdev(pf_to_mgmt);
	काष्ठा hinic_hwdev *hwdev = &pfhwdev->hwdev;

	अगर (HINIC_IS_VF(hwdev->hwअगर))
		वापस;

	hinic_aeq_unरेजिस्टर_hw_cb(&hwdev->aeqs, HINIC_MSG_FROM_MGMT_CPU);
	hinic_api_cmd_मुक्त(pf_to_mgmt->cmd_chain);
	destroy_workqueue(pf_to_mgmt->workq);
	hinic_health_reporters_destroy(hwdev->devlink_dev);
पूर्ण
