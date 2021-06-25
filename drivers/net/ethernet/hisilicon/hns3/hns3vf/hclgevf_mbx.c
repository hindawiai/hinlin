<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश "hclge_mbx.h"
#समावेश "hclgevf_main.h"
#समावेश "hnae3.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "hclgevf_trace.h"

अटल पूर्णांक hclgevf_resp_to_त्रुटि_सं(u16 resp_code)
अणु
	वापस resp_code ? -resp_code : 0;
पूर्ण

अटल व्योम hclgevf_reset_mbx_resp_status(काष्ठा hclgevf_dev *hdev)
अणु
	/* this function should be called with mbx_resp.mbx_mutex held
	 * to prtect the received_response from race condition
	 */
	hdev->mbx_resp.received_resp  = false;
	hdev->mbx_resp.origin_mbx_msg = 0;
	hdev->mbx_resp.resp_status    = 0;
	स_रखो(hdev->mbx_resp.additional_info, 0, HCLGE_MBX_MAX_RESP_DATA_SIZE);
पूर्ण

/* hclgevf_get_mbx_resp: used to get a response from PF after VF sends a mailbox
 * message to PF.
 * @hdev: poपूर्णांकer to काष्ठा hclgevf_dev
 * @resp_msg: poपूर्णांकer to store the original message type and response status
 * @len: the resp_msg data array length.
 */
अटल पूर्णांक hclgevf_get_mbx_resp(काष्ठा hclgevf_dev *hdev, u16 code0, u16 code1,
				u8 *resp_data, u16 resp_len)
अणु
#घोषणा HCLGEVF_MAX_TRY_TIMES	500
#घोषणा HCLGEVF_SLEEP_USECOND	1000
	काष्ठा hclgevf_mbx_resp_status *mbx_resp;
	u16 r_code0, r_code1;
	पूर्णांक i = 0;

	अगर (resp_len > HCLGE_MBX_MAX_RESP_DATA_SIZE) अणु
		dev_err(&hdev->pdev->dev,
			"VF mbx response len(=%u) exceeds maximum(=%u)\n",
			resp_len,
			HCLGE_MBX_MAX_RESP_DATA_SIZE);
		वापस -EINVAL;
	पूर्ण

	जबतक ((!hdev->mbx_resp.received_resp) && (i < HCLGEVF_MAX_TRY_TIMES)) अणु
		अगर (test_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state))
			वापस -EIO;

		usleep_range(HCLGEVF_SLEEP_USECOND, HCLGEVF_SLEEP_USECOND * 2);
		i++;
	पूर्ण

	अगर (i >= HCLGEVF_MAX_TRY_TIMES) अणु
		dev_err(&hdev->pdev->dev,
			"VF could not get mbx(%u,%u) resp(=%d) from PF in %d tries\n",
			code0, code1, hdev->mbx_resp.received_resp, i);
		वापस -EIO;
	पूर्ण

	mbx_resp = &hdev->mbx_resp;
	r_code0 = (u16)(mbx_resp->origin_mbx_msg >> 16);
	r_code1 = (u16)(mbx_resp->origin_mbx_msg & 0xff);

	अगर (mbx_resp->resp_status)
		वापस mbx_resp->resp_status;

	अगर (resp_data)
		स_नकल(resp_data, &mbx_resp->additional_info[0], resp_len);

	hclgevf_reset_mbx_resp_status(hdev);

	अगर (!(r_code0 == code0 && r_code1 == code1 && !mbx_resp->resp_status)) अणु
		dev_err(&hdev->pdev->dev,
			"VF could not match resp code(code0=%u,code1=%u), %d\n",
			code0, code1, mbx_resp->resp_status);
		dev_err(&hdev->pdev->dev,
			"VF could not match resp r_code(r_code0=%u,r_code1=%u)\n",
			r_code0, r_code1);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hclgevf_send_mbx_msg(काष्ठा hclgevf_dev *hdev,
			 काष्ठा hclge_vf_to_pf_msg *send_msg, bool need_resp,
			 u8 *resp_data, u16 resp_len)
अणु
	काष्ठा hclge_mbx_vf_to_pf_cmd *req;
	काष्ठा hclgevf_desc desc;
	पूर्णांक status;

	req = (काष्ठा hclge_mbx_vf_to_pf_cmd *)desc.data;

	अगर (!send_msg) अणु
		dev_err(&hdev->pdev->dev,
			"failed to send mbx, msg is NULL\n");
		वापस -EINVAL;
	पूर्ण

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_MBX_VF_TO_PF, false);
	अगर (need_resp)
		hnae3_set_bit(req->mbx_need_resp, HCLGE_MBX_NEED_RESP_B, 1);

	स_नकल(&req->msg, send_msg, माप(काष्ठा hclge_vf_to_pf_msg));

	trace_hclge_vf_mbx_send(hdev, req);

	/* synchronous send */
	अगर (need_resp) अणु
		mutex_lock(&hdev->mbx_resp.mbx_mutex);
		hclgevf_reset_mbx_resp_status(hdev);
		status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
		अगर (status) अणु
			dev_err(&hdev->pdev->dev,
				"VF failed(=%d) to send mbx message to PF\n",
				status);
			mutex_unlock(&hdev->mbx_resp.mbx_mutex);
			वापस status;
		पूर्ण

		status = hclgevf_get_mbx_resp(hdev, send_msg->code,
					      send_msg->subcode, resp_data,
					      resp_len);
		mutex_unlock(&hdev->mbx_resp.mbx_mutex);
	पूर्ण अन्यथा अणु
		/* asynchronous send */
		status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
		अगर (status) अणु
			dev_err(&hdev->pdev->dev,
				"VF failed(=%d) to send mbx message to PF\n",
				status);
			वापस status;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल bool hclgevf_cmd_crq_empty(काष्ठा hclgevf_hw *hw)
अणु
	u32 tail = hclgevf_पढ़ो_dev(hw, HCLGEVF_NIC_CRQ_TAIL_REG);

	वापस tail == hw->cmq.crq.next_to_use;
पूर्ण

व्योम hclgevf_mbx_handler(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclgevf_mbx_resp_status *resp;
	काष्ठा hclge_mbx_pf_to_vf_cmd *req;
	काष्ठा hclgevf_cmq_ring *crq;
	काष्ठा hclgevf_desc *desc;
	u16 *msg_q;
	u16 flag;
	u8 *temp;
	पूर्णांक i;

	resp = &hdev->mbx_resp;
	crq = &hdev->hw.cmq.crq;

	जबतक (!hclgevf_cmd_crq_empty(&hdev->hw)) अणु
		अगर (test_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state)) अणु
			dev_info(&hdev->pdev->dev, "vf crq need init\n");
			वापस;
		पूर्ण

		desc = &crq->desc[crq->next_to_use];
		req = (काष्ठा hclge_mbx_pf_to_vf_cmd *)desc->data;

		flag = le16_to_cpu(crq->desc[crq->next_to_use].flag);
		अगर (unlikely(!hnae3_get_bit(flag, HCLGEVF_CMDQ_RX_OUTVLD_B))) अणु
			dev_warn(&hdev->pdev->dev,
				 "dropped invalid mailbox message, code = %u\n",
				 req->msg.code);

			/* dropping/not processing this invalid message */
			crq->desc[crq->next_to_use].flag = 0;
			hclge_mbx_ring_ptr_move_crq(crq);
			जारी;
		पूर्ण

		trace_hclge_vf_mbx_get(hdev, req);

		/* synchronous messages are समय critical and need preferential
		 * treaपंचांगent. Thereक्रमe, we need to acknowledge all the sync
		 * responses as quickly as possible so that रुकोing tasks करो not
		 * समयout and simultaneously queue the async messages क्रम later
		 * prcessing in context of mailbox task i.e. the slow path.
		 */
		चयन (req->msg.code) अणु
		हाल HCLGE_MBX_PF_VF_RESP:
			अगर (resp->received_resp)
				dev_warn(&hdev->pdev->dev,
					 "VF mbx resp flag not clear(%u)\n",
					 req->msg.vf_mbx_msg_code);
			resp->received_resp = true;

			resp->origin_mbx_msg =
					(req->msg.vf_mbx_msg_code << 16);
			resp->origin_mbx_msg |= req->msg.vf_mbx_msg_subcode;
			resp->resp_status =
				hclgevf_resp_to_त्रुटि_सं(req->msg.resp_status);

			temp = (u8 *)req->msg.resp_data;
			क्रम (i = 0; i < HCLGE_MBX_MAX_RESP_DATA_SIZE; i++) अणु
				resp->additional_info[i] = *temp;
				temp++;
			पूर्ण
			अवरोध;
		हाल HCLGE_MBX_LINK_STAT_CHANGE:
		हाल HCLGE_MBX_ASSERTING_RESET:
		हाल HCLGE_MBX_LINK_STAT_MODE:
		हाल HCLGE_MBX_PUSH_VLAN_INFO:
		हाल HCLGE_MBX_PUSH_PROMISC_INFO:
			/* set this mbx event as pending. This is required as we
			 * might loose पूर्णांकerrupt event when mbx task is busy
			 * handling. This shall be cleared when mbx task just
			 * enters handling state.
			 */
			hdev->mbx_event_pending = true;

			/* we will drop the async msg अगर we find ARQ as full
			 * and जारी with next message
			 */
			अगर (atomic_पढ़ो(&hdev->arq.count) >=
			    HCLGE_MBX_MAX_ARQ_MSG_NUM) अणु
				dev_warn(&hdev->pdev->dev,
					 "Async Q full, dropping msg(%u)\n",
					 req->msg.code);
				अवरोध;
			पूर्ण

			/* tail the async message in arq */
			msg_q = hdev->arq.msg_q[hdev->arq.tail];
			स_नकल(&msg_q[0], &req->msg,
			       HCLGE_MBX_MAX_ARQ_MSG_SIZE * माप(u16));
			hclge_mbx_tail_ptr_move_arq(hdev->arq);
			atomic_inc(&hdev->arq.count);

			hclgevf_mbx_task_schedule(hdev);

			अवरोध;
		शेष:
			dev_err(&hdev->pdev->dev,
				"VF received unsupported(%u) mbx msg from PF\n",
				req->msg.code);
			अवरोध;
		पूर्ण
		crq->desc[crq->next_to_use].flag = 0;
		hclge_mbx_ring_ptr_move_crq(crq);
	पूर्ण

	/* Write back CMDQ_RQ header poपूर्णांकer, M7 need this poपूर्णांकer */
	hclgevf_ग_लिखो_dev(&hdev->hw, HCLGEVF_NIC_CRQ_HEAD_REG,
			  crq->next_to_use);
पूर्ण

अटल व्योम hclgevf_parse_promisc_info(काष्ठा hclgevf_dev *hdev,
				       u16 promisc_info)
अणु
	अगर (!promisc_info)
		dev_info(&hdev->pdev->dev,
			 "Promisc mode is closed by host for being untrusted.\n");
पूर्ण

व्योम hclgevf_mbx_async_handler(काष्ठा hclgevf_dev *hdev)
अणु
	क्रमागत hnae3_reset_type reset_type;
	u16 link_status, state;
	u16 *msg_q, *vlan_info;
	u8 duplex;
	u32 speed;
	u32 tail;
	u8 flag;
	u8 idx;

	/* we can safely clear it now as we are at start of the async message
	 * processing
	 */
	hdev->mbx_event_pending = false;

	tail = hdev->arq.tail;

	/* process all the async queue messages */
	जबतक (tail != hdev->arq.head) अणु
		अगर (test_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state)) अणु
			dev_info(&hdev->pdev->dev,
				 "vf crq need init in async\n");
			वापस;
		पूर्ण

		msg_q = hdev->arq.msg_q[hdev->arq.head];

		चयन (msg_q[0]) अणु
		हाल HCLGE_MBX_LINK_STAT_CHANGE:
			link_status = msg_q[1];
			स_नकल(&speed, &msg_q[2], माप(speed));
			duplex = (u8)msg_q[4];
			flag = (u8)msg_q[5];

			/* update upper layer with new link link status */
			hclgevf_update_link_status(hdev, link_status);
			hclgevf_update_speed_duplex(hdev, speed, duplex);

			अगर (flag & HCLGE_MBX_PUSH_LINK_STATUS_EN)
				set_bit(HCLGEVF_STATE_PF_PUSH_LINK_STATUS,
					&hdev->state);

			अवरोध;
		हाल HCLGE_MBX_LINK_STAT_MODE:
			idx = (u8)msg_q[1];
			अगर (idx)
				स_नकल(&hdev->hw.mac.supported, &msg_q[2],
				       माप(अचिन्हित दीर्घ));
			अन्यथा
				स_नकल(&hdev->hw.mac.advertising, &msg_q[2],
				       माप(अचिन्हित दीर्घ));
			अवरोध;
		हाल HCLGE_MBX_ASSERTING_RESET:
			/* PF has निश्चितed reset hence VF should go in pending
			 * state and poll क्रम the hardware reset status till it
			 * has been completely reset. After this stack should
			 * eventually be re-initialized.
			 */
			reset_type = (क्रमागत hnae3_reset_type)msg_q[1];
			set_bit(reset_type, &hdev->reset_pending);
			set_bit(HCLGEVF_RESET_PENDING, &hdev->reset_state);
			hclgevf_reset_task_schedule(hdev);

			अवरोध;
		हाल HCLGE_MBX_PUSH_VLAN_INFO:
			state = msg_q[1];
			vlan_info = &msg_q[1];
			hclgevf_update_port_base_vlan_info(hdev, state,
							   (u8 *)vlan_info, 8);
			अवरोध;
		हाल HCLGE_MBX_PUSH_PROMISC_INFO:
			hclgevf_parse_promisc_info(hdev, msg_q[1]);
			अवरोध;
		शेष:
			dev_err(&hdev->pdev->dev,
				"fetched unsupported(%u) message from arq\n",
				msg_q[0]);
			अवरोध;
		पूर्ण

		hclge_mbx_head_ptr_move_arq(hdev->arq);
		atomic_dec(&hdev->arq.count);
		msg_q = hdev->arq.msg_q[hdev->arq.head];
	पूर्ण
पूर्ण
