<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश "hclge_main.h"
#समावेश "hclge_mbx.h"
#समावेश "hnae3.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "hclge_trace.h"

अटल u16 hclge_त्रुटि_सं_to_resp(पूर्णांक त्रुटि_सं)
अणु
	वापस असल(त्रुटि_सं);
पूर्ण

/* hclge_gen_resp_to_vf: used to generate a synchronous response to VF when PF
 * receives a mailbox message from VF.
 * @vport: poपूर्णांकer to काष्ठा hclge_vport
 * @vf_to_pf_req: poपूर्णांकer to hclge_mbx_vf_to_pf_cmd of the original mailbox
 *		  message
 * @resp_status: indicate to VF whether its request success(0) or failed.
 */
अटल पूर्णांक hclge_gen_resp_to_vf(काष्ठा hclge_vport *vport,
				काष्ठा hclge_mbx_vf_to_pf_cmd *vf_to_pf_req,
				काष्ठा hclge_respond_to_vf_msg *resp_msg)
अणु
	काष्ठा hclge_mbx_pf_to_vf_cmd *resp_pf_to_vf;
	काष्ठा hclge_dev *hdev = vport->back;
	क्रमागत hclge_cmd_status status;
	काष्ठा hclge_desc desc;
	u16 resp;

	resp_pf_to_vf = (काष्ठा hclge_mbx_pf_to_vf_cmd *)desc.data;

	अगर (resp_msg->len > HCLGE_MBX_MAX_RESP_DATA_SIZE) अणु
		dev_err(&hdev->pdev->dev,
			"PF fail to gen resp to VF len %u exceeds max len %u\n",
			resp_msg->len,
			HCLGE_MBX_MAX_RESP_DATA_SIZE);
		/* If resp_msg->len is too दीर्घ, set the value to max length
		 * and वापस the msg to VF
		 */
		resp_msg->len = HCLGE_MBX_MAX_RESP_DATA_SIZE;
	पूर्ण

	hclge_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_MBX_PF_TO_VF, false);

	resp_pf_to_vf->dest_vfid = vf_to_pf_req->mbx_src_vfid;
	resp_pf_to_vf->msg_len = vf_to_pf_req->msg_len;

	resp_pf_to_vf->msg.code = HCLGE_MBX_PF_VF_RESP;
	resp_pf_to_vf->msg.vf_mbx_msg_code = vf_to_pf_req->msg.code;
	resp_pf_to_vf->msg.vf_mbx_msg_subcode = vf_to_pf_req->msg.subcode;
	resp = hclge_त्रुटि_सं_to_resp(resp_msg->status);
	अगर (resp < लघु_उच्च) अणु
		resp_pf_to_vf->msg.resp_status = resp;
	पूर्ण अन्यथा अणु
		dev_warn(&hdev->pdev->dev,
			 "failed to send response to VF, response status %u is out-of-bound\n",
			 resp);
		resp_pf_to_vf->msg.resp_status = EIO;
	पूर्ण

	अगर (resp_msg->len > 0)
		स_नकल(resp_pf_to_vf->msg.resp_data, resp_msg->data,
		       resp_msg->len);

	status = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"failed to send response to VF, status: %d, vfid: %u, code: %u, subcode: %u.\n",
			status, vf_to_pf_req->mbx_src_vfid,
			vf_to_pf_req->msg.code, vf_to_pf_req->msg.subcode);

	वापस status;
पूर्ण

अटल पूर्णांक hclge_send_mbx_msg(काष्ठा hclge_vport *vport, u8 *msg, u16 msg_len,
			      u16 mbx_opcode, u8 dest_vfid)
अणु
	काष्ठा hclge_mbx_pf_to_vf_cmd *resp_pf_to_vf;
	काष्ठा hclge_dev *hdev = vport->back;
	क्रमागत hclge_cmd_status status;
	काष्ठा hclge_desc desc;

	resp_pf_to_vf = (काष्ठा hclge_mbx_pf_to_vf_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_MBX_PF_TO_VF, false);

	resp_pf_to_vf->dest_vfid = dest_vfid;
	resp_pf_to_vf->msg_len = msg_len;
	resp_pf_to_vf->msg.code = mbx_opcode;

	स_नकल(&resp_pf_to_vf->msg.vf_mbx_msg_code, msg, msg_len);

	trace_hclge_pf_mbx_send(hdev, resp_pf_to_vf);

	status = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"failed to send mailbox to VF, status: %d, vfid: %u, opcode: %u\n",
			status, dest_vfid, mbx_opcode);

	वापस status;
पूर्ण

पूर्णांक hclge_inक्रमm_reset_निश्चित_to_vf(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	u16 reset_type;
	u8 msg_data[2];
	u8 dest_vfid;

	BUILD_BUG_ON(HNAE3_MAX_RESET > U16_MAX);

	dest_vfid = (u8)vport->vport_id;

	अगर (hdev->reset_type == HNAE3_FUNC_RESET)
		reset_type = HNAE3_VF_PF_FUNC_RESET;
	अन्यथा अगर (hdev->reset_type == HNAE3_FLR_RESET)
		reset_type = HNAE3_VF_FULL_RESET;
	अन्यथा
		reset_type = HNAE3_VF_FUNC_RESET;

	स_नकल(&msg_data[0], &reset_type, माप(u16));

	/* send this requested info to VF */
	वापस hclge_send_mbx_msg(vport, msg_data, माप(msg_data),
				  HCLGE_MBX_ASSERTING_RESET, dest_vfid);
पूर्ण

अटल व्योम hclge_मुक्त_vector_ring_chain(काष्ठा hnae3_ring_chain_node *head)
अणु
	काष्ठा hnae3_ring_chain_node *chain_पंचांगp, *chain;

	chain = head->next;

	जबतक (chain) अणु
		chain_पंचांगp = chain->next;
		kमुक्त_sensitive(chain);
		chain = chain_पंचांगp;
	पूर्ण
पूर्ण

/* hclge_get_ring_chain_from_mbx: get ring type & tqp id & पूर्णांक_gl idx
 * from mailbox message
 * msg[0]: opcode
 * msg[1]: <not relevant to this function>
 * msg[2]: ring_num
 * msg[3]: first ring type (TX|RX)
 * msg[4]: first tqp id
 * msg[5]: first पूर्णांक_gl idx
 * msg[6] ~ msg[14]: other ring type, tqp id and पूर्णांक_gl idx
 */
अटल पूर्णांक hclge_get_ring_chain_from_mbx(
			काष्ठा hclge_mbx_vf_to_pf_cmd *req,
			काष्ठा hnae3_ring_chain_node *ring_chain,
			काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_ring_chain_node *cur_chain, *new_chain;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ring_num;
	पूर्णांक i;

	ring_num = req->msg.ring_num;

	अगर (ring_num > HCLGE_MBX_MAX_RING_CHAIN_PARAM_NUM)
		वापस -ENOMEM;

	क्रम (i = 0; i < ring_num; i++) अणु
		अगर (req->msg.param[i].tqp_index >= vport->nic.kinfo.rss_size) अणु
			dev_err(&hdev->pdev->dev, "tqp index(%u) is out of range(0-%u)\n",
				req->msg.param[i].tqp_index,
				vport->nic.kinfo.rss_size - 1);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	hnae3_set_bit(ring_chain->flag, HNAE3_RING_TYPE_B,
		      req->msg.param[0].ring_type);
	ring_chain->tqp_index =
		hclge_get_queue_id(vport->nic.kinfo.tqp
				   [req->msg.param[0].tqp_index]);
	hnae3_set_field(ring_chain->पूर्णांक_gl_idx, HNAE3_RING_GL_IDX_M,
			HNAE3_RING_GL_IDX_S, req->msg.param[0].पूर्णांक_gl_index);

	cur_chain = ring_chain;

	क्रम (i = 1; i < ring_num; i++) अणु
		new_chain = kzalloc(माप(*new_chain), GFP_KERNEL);
		अगर (!new_chain)
			जाओ err;

		hnae3_set_bit(new_chain->flag, HNAE3_RING_TYPE_B,
			      req->msg.param[i].ring_type);

		new_chain->tqp_index =
		hclge_get_queue_id(vport->nic.kinfo.tqp
			[req->msg.param[i].tqp_index]);

		hnae3_set_field(new_chain->पूर्णांक_gl_idx, HNAE3_RING_GL_IDX_M,
				HNAE3_RING_GL_IDX_S,
				req->msg.param[i].पूर्णांक_gl_index);

		cur_chain->next = new_chain;
		cur_chain = new_chain;
	पूर्ण

	वापस 0;
err:
	hclge_मुक्त_vector_ring_chain(ring_chain);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक hclge_map_unmap_ring_to_vf_vector(काष्ठा hclge_vport *vport, bool en,
					     काष्ठा hclge_mbx_vf_to_pf_cmd *req)
अणु
	काष्ठा hnae3_ring_chain_node ring_chain;
	पूर्णांक vector_id = req->msg.vector_id;
	पूर्णांक ret;

	स_रखो(&ring_chain, 0, माप(ring_chain));
	ret = hclge_get_ring_chain_from_mbx(req, &ring_chain, vport);
	अगर (ret)
		वापस ret;

	ret = hclge_bind_ring_with_vector(vport, vector_id, en, &ring_chain);

	hclge_मुक्त_vector_ring_chain(&ring_chain);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_set_vf_promisc_mode(काष्ठा hclge_vport *vport,
				     काष्ठा hclge_mbx_vf_to_pf_cmd *req)
अणु
	bool en_bc = req->msg.en_bc ? true : false;
	bool en_uc = req->msg.en_uc ? true : false;
	bool en_mc = req->msg.en_mc ? true : false;
	काष्ठा hnae3_handle *handle = &vport->nic;
	पूर्णांक ret;

	अगर (!vport->vf_info.trusted) अणु
		en_uc = false;
		en_mc = false;
	पूर्ण

	अगर (req->msg.en_limit_promisc)
		set_bit(HNAE3_PFLAG_LIMIT_PROMISC, &handle->priv_flags);
	अन्यथा
		clear_bit(HNAE3_PFLAG_LIMIT_PROMISC,
			  &handle->priv_flags);

	ret = hclge_set_vport_promisc_mode(vport, en_uc, en_mc, en_bc);

	vport->vf_info.promisc_enable = (en_uc || en_mc) ? 1 : 0;

	वापस ret;
पूर्ण

व्योम hclge_inक्रमm_vf_promisc_info(काष्ठा hclge_vport *vport)
अणु
	u8 dest_vfid = (u8)vport->vport_id;
	u8 msg_data[2];

	स_नकल(&msg_data[0], &vport->vf_info.promisc_enable, माप(u16));

	hclge_send_mbx_msg(vport, msg_data, माप(msg_data),
			   HCLGE_MBX_PUSH_PROMISC_INFO, dest_vfid);
पूर्ण

अटल पूर्णांक hclge_set_vf_uc_mac_addr(काष्ठा hclge_vport *vport,
				    काष्ठा hclge_mbx_vf_to_pf_cmd *mbx_req)
अणु
#घोषणा HCLGE_MBX_VF_OLD_MAC_ADDR_OFFSET	6

	स्थिर u8 *mac_addr = (स्थिर u8 *)(mbx_req->msg.data);
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक status;

	अगर (mbx_req->msg.subcode == HCLGE_MBX_MAC_VLAN_UC_MODIFY) अणु
		स्थिर u8 *old_addr = (स्थिर u8 *)
		(&mbx_req->msg.data[HCLGE_MBX_VF_OLD_MAC_ADDR_OFFSET]);

		/* If VF MAC has been configured by the host then it
		 * cannot be overridden by the MAC specअगरied by the VM.
		 */
		अगर (!is_zero_ether_addr(vport->vf_info.mac) &&
		    !ether_addr_equal(mac_addr, vport->vf_info.mac))
			वापस -EPERM;

		अगर (!is_valid_ether_addr(mac_addr))
			वापस -EINVAL;

		spin_lock_bh(&vport->mac_list_lock);
		status = hclge_update_mac_node_क्रम_dev_addr(vport, old_addr,
							    mac_addr);
		spin_unlock_bh(&vport->mac_list_lock);
		hclge_task_schedule(hdev, 0);
	पूर्ण अन्यथा अगर (mbx_req->msg.subcode == HCLGE_MBX_MAC_VLAN_UC_ADD) अणु
		status = hclge_update_mac_list(vport, HCLGE_MAC_TO_ADD,
					       HCLGE_MAC_ADDR_UC, mac_addr);
	पूर्ण अन्यथा अगर (mbx_req->msg.subcode == HCLGE_MBX_MAC_VLAN_UC_REMOVE) अणु
		status = hclge_update_mac_list(vport, HCLGE_MAC_TO_DEL,
					       HCLGE_MAC_ADDR_UC, mac_addr);
	पूर्ण अन्यथा अणु
		dev_err(&hdev->pdev->dev,
			"failed to set unicast mac addr, unknown subcode %u\n",
			mbx_req->msg.subcode);
		वापस -EIO;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक hclge_set_vf_mc_mac_addr(काष्ठा hclge_vport *vport,
				    काष्ठा hclge_mbx_vf_to_pf_cmd *mbx_req)
अणु
	स्थिर u8 *mac_addr = (स्थिर u8 *)(mbx_req->msg.data);
	काष्ठा hclge_dev *hdev = vport->back;

	अगर (mbx_req->msg.subcode == HCLGE_MBX_MAC_VLAN_MC_ADD) अणु
		hclge_update_mac_list(vport, HCLGE_MAC_TO_ADD,
				      HCLGE_MAC_ADDR_MC, mac_addr);
	पूर्ण अन्यथा अगर (mbx_req->msg.subcode == HCLGE_MBX_MAC_VLAN_MC_REMOVE) अणु
		hclge_update_mac_list(vport, HCLGE_MAC_TO_DEL,
				      HCLGE_MAC_ADDR_MC, mac_addr);
	पूर्ण अन्यथा अणु
		dev_err(&hdev->pdev->dev,
			"failed to set mcast mac addr, unknown subcode %u\n",
			mbx_req->msg.subcode);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hclge_push_vf_port_base_vlan_info(काष्ठा hclge_vport *vport, u8 vfid,
				      u16 state, u16 vlan_tag, u16 qos,
				      u16 vlan_proto)
अणु
#घोषणा MSG_DATA_SIZE	8

	u8 msg_data[MSG_DATA_SIZE];

	स_नकल(&msg_data[0], &state, माप(u16));
	स_नकल(&msg_data[2], &vlan_proto, माप(u16));
	स_नकल(&msg_data[4], &qos, माप(u16));
	स_नकल(&msg_data[6], &vlan_tag, माप(u16));

	वापस hclge_send_mbx_msg(vport, msg_data, माप(msg_data),
				  HCLGE_MBX_PUSH_VLAN_INFO, vfid);
पूर्ण

अटल पूर्णांक hclge_set_vf_vlan_cfg(काष्ठा hclge_vport *vport,
				 काष्ठा hclge_mbx_vf_to_pf_cmd *mbx_req,
				 काष्ठा hclge_respond_to_vf_msg *resp_msg)
अणु
#घोषणा HCLGE_MBX_VLAN_STATE_OFFSET	0
#घोषणा HCLGE_MBX_VLAN_INFO_OFFSET	2

	काष्ठा hclge_vf_vlan_cfg *msg_cmd;
	पूर्णांक status = 0;

	msg_cmd = (काष्ठा hclge_vf_vlan_cfg *)&mbx_req->msg;
	अगर (msg_cmd->subcode == HCLGE_MBX_VLAN_FILTER) अणु
		काष्ठा hnae3_handle *handle = &vport->nic;
		u16 vlan, proto;
		bool is_समाप्त;

		is_समाप्त = !!msg_cmd->is_समाप्त;
		vlan =  msg_cmd->vlan;
		proto =  msg_cmd->proto;
		status = hclge_set_vlan_filter(handle, cpu_to_be16(proto),
					       vlan, is_समाप्त);
	पूर्ण अन्यथा अगर (msg_cmd->subcode == HCLGE_MBX_VLAN_RX_OFF_CFG) अणु
		काष्ठा hnae3_handle *handle = &vport->nic;
		bool en = msg_cmd->is_समाप्त ? true : false;

		status = hclge_en_hw_strip_rxvtag(handle, en);
	पूर्ण अन्यथा अगर (msg_cmd->subcode == HCLGE_MBX_PORT_BASE_VLAN_CFG) अणु
		काष्ठा hclge_vlan_info *vlan_info;
		u16 *state;

		state = (u16 *)&mbx_req->msg.data[HCLGE_MBX_VLAN_STATE_OFFSET];
		vlan_info = (काष्ठा hclge_vlan_info *)
			&mbx_req->msg.data[HCLGE_MBX_VLAN_INFO_OFFSET];
		status = hclge_update_port_base_vlan_cfg(vport, *state,
							 vlan_info);
	पूर्ण अन्यथा अगर (msg_cmd->subcode == HCLGE_MBX_GET_PORT_BASE_VLAN_STATE) अणु
		काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(vport->nic.pdev);
		/* vf करोes not need to know about the port based VLAN state
		 * on device HNAE3_DEVICE_VERSION_V3. So always वापस disable
		 * on device HNAE3_DEVICE_VERSION_V3 अगर vf queries the port
		 * based VLAN state.
		 */
		resp_msg->data[0] =
			ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V3 ?
			HNAE3_PORT_BASE_VLAN_DISABLE :
			vport->port_base_vlan_cfg.state;
		resp_msg->len = माप(u8);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक hclge_set_vf_alive(काष्ठा hclge_vport *vport,
			      काष्ठा hclge_mbx_vf_to_pf_cmd *mbx_req)
अणु
	bool alive = !!mbx_req->msg.data[0];
	पूर्णांक ret = 0;

	अगर (alive)
		ret = hclge_vport_start(vport);
	अन्यथा
		hclge_vport_stop(vport);

	वापस ret;
पूर्ण

अटल व्योम hclge_get_vf_tcinfo(काष्ठा hclge_vport *vport,
				काष्ठा hclge_respond_to_vf_msg *resp_msg)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < kinfo->tc_info.num_tc; i++)
		resp_msg->data[0] |= BIT(i);

	resp_msg->len = माप(u8);
पूर्ण

अटल व्योम hclge_get_vf_queue_info(काष्ठा hclge_vport *vport,
				    काष्ठा hclge_respond_to_vf_msg *resp_msg)
अणु
#घोषणा HCLGE_TQPS_RSS_INFO_LEN		6
#घोषणा HCLGE_TQPS_ALLOC_OFFSET		0
#घोषणा HCLGE_TQPS_RSS_SIZE_OFFSET	2
#घोषणा HCLGE_TQPS_RX_BUFFER_LEN_OFFSET	4

	काष्ठा hclge_dev *hdev = vport->back;

	/* get the queue related info */
	स_नकल(&resp_msg->data[HCLGE_TQPS_ALLOC_OFFSET],
	       &vport->alloc_tqps, माप(u16));
	स_नकल(&resp_msg->data[HCLGE_TQPS_RSS_SIZE_OFFSET],
	       &vport->nic.kinfo.rss_size, माप(u16));
	स_नकल(&resp_msg->data[HCLGE_TQPS_RX_BUFFER_LEN_OFFSET],
	       &hdev->rx_buf_len, माप(u16));
	resp_msg->len = HCLGE_TQPS_RSS_INFO_LEN;
पूर्ण

अटल व्योम hclge_get_vf_mac_addr(काष्ठा hclge_vport *vport,
				  काष्ठा hclge_respond_to_vf_msg *resp_msg)
अणु
	ether_addr_copy(resp_msg->data, vport->vf_info.mac);
	resp_msg->len = ETH_ALEN;
पूर्ण

अटल व्योम hclge_get_vf_queue_depth(काष्ठा hclge_vport *vport,
				     काष्ठा hclge_respond_to_vf_msg *resp_msg)
अणु
#घोषणा HCLGE_TQPS_DEPTH_INFO_LEN	4
#घोषणा HCLGE_TQPS_NUM_TX_DESC_OFFSET	0
#घोषणा HCLGE_TQPS_NUM_RX_DESC_OFFSET	2

	काष्ठा hclge_dev *hdev = vport->back;

	/* get the queue depth info */
	स_नकल(&resp_msg->data[HCLGE_TQPS_NUM_TX_DESC_OFFSET],
	       &hdev->num_tx_desc, माप(u16));
	स_नकल(&resp_msg->data[HCLGE_TQPS_NUM_RX_DESC_OFFSET],
	       &hdev->num_rx_desc, माप(u16));
	resp_msg->len = HCLGE_TQPS_DEPTH_INFO_LEN;
पूर्ण

अटल व्योम hclge_get_vf_media_type(काष्ठा hclge_vport *vport,
				    काष्ठा hclge_respond_to_vf_msg *resp_msg)
अणु
#घोषणा HCLGE_VF_MEDIA_TYPE_OFFSET	0
#घोषणा HCLGE_VF_MODULE_TYPE_OFFSET	1
#घोषणा HCLGE_VF_MEDIA_TYPE_LENGTH	2

	काष्ठा hclge_dev *hdev = vport->back;

	resp_msg->data[HCLGE_VF_MEDIA_TYPE_OFFSET] =
		hdev->hw.mac.media_type;
	resp_msg->data[HCLGE_VF_MODULE_TYPE_OFFSET] =
		hdev->hw.mac.module_type;
	resp_msg->len = HCLGE_VF_MEDIA_TYPE_LENGTH;
पूर्ण

पूर्णांक hclge_push_vf_link_status(काष्ठा hclge_vport *vport)
अणु
#घोषणा HCLGE_VF_LINK_STATE_UP		1U
#घोषणा HCLGE_VF_LINK_STATE_DOWN	0U

	काष्ठा hclge_dev *hdev = vport->back;
	u16 link_status;
	u8 msg_data[9];
	u16 duplex;

	/* mac.link can only be 0 or 1 */
	चयन (vport->vf_info.link_state) अणु
	हाल IFLA_VF_LINK_STATE_ENABLE:
		link_status = HCLGE_VF_LINK_STATE_UP;
		अवरोध;
	हाल IFLA_VF_LINK_STATE_DISABLE:
		link_status = HCLGE_VF_LINK_STATE_DOWN;
		अवरोध;
	हाल IFLA_VF_LINK_STATE_AUTO:
	शेष:
		link_status = (u16)hdev->hw.mac.link;
		अवरोध;
	पूर्ण

	duplex = hdev->hw.mac.duplex;
	स_नकल(&msg_data[0], &link_status, माप(u16));
	स_नकल(&msg_data[2], &hdev->hw.mac.speed, माप(u32));
	स_नकल(&msg_data[6], &duplex, माप(u16));
	msg_data[8] = HCLGE_MBX_PUSH_LINK_STATUS_EN;

	/* send this requested info to VF */
	वापस hclge_send_mbx_msg(vport, msg_data, माप(msg_data),
				  HCLGE_MBX_LINK_STAT_CHANGE, vport->vport_id);
पूर्ण

अटल व्योम hclge_get_link_mode(काष्ठा hclge_vport *vport,
				काष्ठा hclge_mbx_vf_to_pf_cmd *mbx_req)
अणु
#घोषणा HCLGE_SUPPORTED   1
	काष्ठा hclge_dev *hdev = vport->back;
	अचिन्हित दीर्घ advertising;
	अचिन्हित दीर्घ supported;
	अचिन्हित दीर्घ send_data;
	u8 msg_data[10] = अणुपूर्ण;
	u8 dest_vfid;

	advertising = hdev->hw.mac.advertising[0];
	supported = hdev->hw.mac.supported[0];
	dest_vfid = mbx_req->mbx_src_vfid;
	msg_data[0] = mbx_req->msg.data[0];

	send_data = msg_data[0] == HCLGE_SUPPORTED ? supported : advertising;

	स_नकल(&msg_data[2], &send_data, माप(अचिन्हित दीर्घ));
	hclge_send_mbx_msg(vport, msg_data, माप(msg_data),
			   HCLGE_MBX_LINK_STAT_MODE, dest_vfid);
पूर्ण

अटल पूर्णांक hclge_mbx_reset_vf_queue(काष्ठा hclge_vport *vport,
				    काष्ठा hclge_mbx_vf_to_pf_cmd *mbx_req,
				    काष्ठा hclge_respond_to_vf_msg *resp_msg)
अणु
#घोषणा HCLGE_RESET_ALL_QUEUE_DONE	1U
	काष्ठा hnae3_handle *handle = &vport->nic;
	काष्ठा hclge_dev *hdev = vport->back;
	u16 queue_id;
	पूर्णांक ret;

	स_नकल(&queue_id, mbx_req->msg.data, माप(queue_id));
	resp_msg->data[0] = HCLGE_RESET_ALL_QUEUE_DONE;
	resp_msg->len = माप(u8);

	/* pf will reset vf's all queues at a समय. So it is unnecessary
	 * to reset queues अगर queue_id > 0, just वापस success.
	 */
	अगर (queue_id > 0)
		वापस 0;

	ret = hclge_reset_tqp(handle);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "failed to reset vf %u queue, ret = %d\n",
			vport->vport_id - HCLGE_VF_VPORT_START_NUM, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclge_reset_vf(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hclge_dev *hdev = vport->back;

	dev_warn(&hdev->pdev->dev, "PF received VF reset request from VF %u!",
		 vport->vport_id);

	वापस hclge_func_reset_cmd(hdev, vport->vport_id);
पूर्ण

अटल व्योम hclge_vf_keep_alive(काष्ठा hclge_vport *vport)
अणु
	vport->last_active_jअगरfies = jअगरfies;
पूर्ण

अटल पूर्णांक hclge_set_vf_mtu(काष्ठा hclge_vport *vport,
			    काष्ठा hclge_mbx_vf_to_pf_cmd *mbx_req)
अणु
	u32 mtu;

	स_नकल(&mtu, mbx_req->msg.data, माप(mtu));

	वापस hclge_set_vport_mtu(vport, mtu);
पूर्ण

अटल व्योम hclge_get_queue_id_in_pf(काष्ठा hclge_vport *vport,
				     काष्ठा hclge_mbx_vf_to_pf_cmd *mbx_req,
				     काष्ठा hclge_respond_to_vf_msg *resp_msg)
अणु
	u16 queue_id, qid_in_pf;

	स_नकल(&queue_id, mbx_req->msg.data, माप(queue_id));
	qid_in_pf = hclge_covert_handle_qid_global(&vport->nic, queue_id);
	स_नकल(resp_msg->data, &qid_in_pf, माप(qid_in_pf));
	resp_msg->len = माप(qid_in_pf);
पूर्ण

अटल व्योम hclge_get_rss_key(काष्ठा hclge_vport *vport,
			      काष्ठा hclge_mbx_vf_to_pf_cmd *mbx_req,
			      काष्ठा hclge_respond_to_vf_msg *resp_msg)
अणु
#घोषणा HCLGE_RSS_MBX_RESP_LEN	8
	काष्ठा hclge_dev *hdev = vport->back;
	u8 index;

	index = mbx_req->msg.data[0];

	/* Check the query index of rss_hash_key from VF, make sure no
	 * more than the size of rss_hash_key.
	 */
	अगर (((index + 1) * HCLGE_RSS_MBX_RESP_LEN) >
	      माप(vport[0].rss_hash_key)) अणु
		dev_warn(&hdev->pdev->dev,
			 "failed to get the rss hash key, the index(%u) invalid !\n",
			 index);
		वापस;
	पूर्ण

	स_नकल(resp_msg->data,
	       &hdev->vport[0].rss_hash_key[index * HCLGE_RSS_MBX_RESP_LEN],
	       HCLGE_RSS_MBX_RESP_LEN);
	resp_msg->len = HCLGE_RSS_MBX_RESP_LEN;
पूर्ण

अटल व्योम hclge_link_fail_parse(काष्ठा hclge_dev *hdev, u8 link_fail_code)
अणु
	चयन (link_fail_code) अणु
	हाल HCLGE_LF_REF_CLOCK_LOST:
		dev_warn(&hdev->pdev->dev, "Reference clock lost!\n");
		अवरोध;
	हाल HCLGE_LF_XSFP_TX_DISABLE:
		dev_warn(&hdev->pdev->dev, "SFP tx is disabled!\n");
		अवरोध;
	हाल HCLGE_LF_XSFP_ABSENT:
		dev_warn(&hdev->pdev->dev, "SFP is absent!\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hclge_handle_link_change_event(काष्ठा hclge_dev *hdev,
					   काष्ठा hclge_mbx_vf_to_pf_cmd *req)
अणु
	hclge_task_schedule(hdev, 0);

	अगर (!req->msg.subcode)
		hclge_link_fail_parse(hdev, req->msg.data[0]);
पूर्ण

अटल bool hclge_cmd_crq_empty(काष्ठा hclge_hw *hw)
अणु
	u32 tail = hclge_पढ़ो_dev(hw, HCLGE_NIC_CRQ_TAIL_REG);

	वापस tail == hw->cmq.crq.next_to_use;
पूर्ण

अटल व्योम hclge_handle_ncsi_error(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = hdev->ae_dev;

	ae_dev->ops->set_शेष_reset_request(ae_dev, HNAE3_GLOBAL_RESET);
	dev_warn(&hdev->pdev->dev, "requesting reset due to NCSI error\n");
	ae_dev->ops->reset_event(hdev->pdev, शून्य);
पूर्ण

अटल व्योम hclge_handle_vf_tbl(काष्ठा hclge_vport *vport,
				काष्ठा hclge_mbx_vf_to_pf_cmd *mbx_req)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_vf_vlan_cfg *msg_cmd;

	msg_cmd = (काष्ठा hclge_vf_vlan_cfg *)&mbx_req->msg;
	अगर (msg_cmd->subcode == HCLGE_MBX_VPORT_LIST_CLEAR) अणु
		hclge_rm_vport_all_mac_table(vport, true, HCLGE_MAC_ADDR_UC);
		hclge_rm_vport_all_mac_table(vport, true, HCLGE_MAC_ADDR_MC);
		hclge_rm_vport_all_vlan_table(vport, true);
	पूर्ण अन्यथा अणु
		dev_warn(&hdev->pdev->dev, "Invalid cmd(%u)\n",
			 msg_cmd->subcode);
	पूर्ण
पूर्ण

व्योम hclge_mbx_handler(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_cmq_ring *crq = &hdev->hw.cmq.crq;
	काष्ठा hclge_respond_to_vf_msg resp_msg;
	काष्ठा hclge_mbx_vf_to_pf_cmd *req;
	काष्ठा hclge_vport *vport;
	काष्ठा hclge_desc *desc;
	bool is_del = false;
	अचिन्हित पूर्णांक flag;
	पूर्णांक ret = 0;

	/* handle all the mailbox requests in the queue */
	जबतक (!hclge_cmd_crq_empty(&hdev->hw)) अणु
		अगर (test_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state)) अणु
			dev_warn(&hdev->pdev->dev,
				 "command queue needs re-initializing\n");
			वापस;
		पूर्ण

		desc = &crq->desc[crq->next_to_use];
		req = (काष्ठा hclge_mbx_vf_to_pf_cmd *)desc->data;

		flag = le16_to_cpu(crq->desc[crq->next_to_use].flag);
		अगर (unlikely(!hnae3_get_bit(flag, HCLGE_CMDQ_RX_OUTVLD_B))) अणु
			dev_warn(&hdev->pdev->dev,
				 "dropped invalid mailbox message, code = %u\n",
				 req->msg.code);

			/* dropping/not processing this invalid message */
			crq->desc[crq->next_to_use].flag = 0;
			hclge_mbx_ring_ptr_move_crq(crq);
			जारी;
		पूर्ण

		vport = &hdev->vport[req->mbx_src_vfid];

		trace_hclge_pf_mbx_get(hdev, req);

		/* clear the resp_msg beक्रमe processing every mailbox message */
		स_रखो(&resp_msg, 0, माप(resp_msg));

		चयन (req->msg.code) अणु
		हाल HCLGE_MBX_MAP_RING_TO_VECTOR:
			ret = hclge_map_unmap_ring_to_vf_vector(vport, true,
								req);
			अवरोध;
		हाल HCLGE_MBX_UNMAP_RING_TO_VECTOR:
			ret = hclge_map_unmap_ring_to_vf_vector(vport, false,
								req);
			अवरोध;
		हाल HCLGE_MBX_SET_PROMISC_MODE:
			ret = hclge_set_vf_promisc_mode(vport, req);
			अगर (ret)
				dev_err(&hdev->pdev->dev,
					"PF fail(%d) to set VF promisc mode\n",
					ret);
			अवरोध;
		हाल HCLGE_MBX_SET_UNICAST:
			ret = hclge_set_vf_uc_mac_addr(vport, req);
			अगर (ret)
				dev_err(&hdev->pdev->dev,
					"PF fail(%d) to set VF UC MAC Addr\n",
					ret);
			अवरोध;
		हाल HCLGE_MBX_SET_MULTICAST:
			ret = hclge_set_vf_mc_mac_addr(vport, req);
			अगर (ret)
				dev_err(&hdev->pdev->dev,
					"PF fail(%d) to set VF MC MAC Addr\n",
					ret);
			अवरोध;
		हाल HCLGE_MBX_SET_VLAN:
			ret = hclge_set_vf_vlan_cfg(vport, req, &resp_msg);
			अगर (ret)
				dev_err(&hdev->pdev->dev,
					"PF failed(%d) to config VF's VLAN\n",
					ret);
			अवरोध;
		हाल HCLGE_MBX_SET_ALIVE:
			ret = hclge_set_vf_alive(vport, req);
			अगर (ret)
				dev_err(&hdev->pdev->dev,
					"PF failed(%d) to set VF's ALIVE\n",
					ret);
			अवरोध;
		हाल HCLGE_MBX_GET_QINFO:
			hclge_get_vf_queue_info(vport, &resp_msg);
			अवरोध;
		हाल HCLGE_MBX_GET_QDEPTH:
			hclge_get_vf_queue_depth(vport, &resp_msg);
			अवरोध;
		हाल HCLGE_MBX_GET_TCINFO:
			hclge_get_vf_tcinfo(vport, &resp_msg);
			अवरोध;
		हाल HCLGE_MBX_GET_LINK_STATUS:
			ret = hclge_push_vf_link_status(vport);
			अगर (ret)
				dev_err(&hdev->pdev->dev,
					"failed to inform link stat to VF, ret = %d\n",
					ret);
			अवरोध;
		हाल HCLGE_MBX_QUEUE_RESET:
			ret = hclge_mbx_reset_vf_queue(vport, req, &resp_msg);
			अवरोध;
		हाल HCLGE_MBX_RESET:
			ret = hclge_reset_vf(vport);
			अवरोध;
		हाल HCLGE_MBX_KEEP_ALIVE:
			hclge_vf_keep_alive(vport);
			अवरोध;
		हाल HCLGE_MBX_SET_MTU:
			ret = hclge_set_vf_mtu(vport, req);
			अगर (ret)
				dev_err(&hdev->pdev->dev,
					"VF fail(%d) to set mtu\n", ret);
			अवरोध;
		हाल HCLGE_MBX_GET_QID_IN_PF:
			hclge_get_queue_id_in_pf(vport, req, &resp_msg);
			अवरोध;
		हाल HCLGE_MBX_GET_RSS_KEY:
			hclge_get_rss_key(vport, req, &resp_msg);
			अवरोध;
		हाल HCLGE_MBX_GET_LINK_MODE:
			hclge_get_link_mode(vport, req);
			अवरोध;
		हाल HCLGE_MBX_GET_VF_FLR_STATUS:
		हाल HCLGE_MBX_VF_UNINIT:
			is_del = req->msg.code == HCLGE_MBX_VF_UNINIT;
			hclge_rm_vport_all_mac_table(vport, is_del,
						     HCLGE_MAC_ADDR_UC);
			hclge_rm_vport_all_mac_table(vport, is_del,
						     HCLGE_MAC_ADDR_MC);
			hclge_rm_vport_all_vlan_table(vport, is_del);
			अवरोध;
		हाल HCLGE_MBX_GET_MEDIA_TYPE:
			hclge_get_vf_media_type(vport, &resp_msg);
			अवरोध;
		हाल HCLGE_MBX_PUSH_LINK_STATUS:
			hclge_handle_link_change_event(hdev, req);
			अवरोध;
		हाल HCLGE_MBX_GET_MAC_ADDR:
			hclge_get_vf_mac_addr(vport, &resp_msg);
			अवरोध;
		हाल HCLGE_MBX_NCSI_ERROR:
			hclge_handle_ncsi_error(hdev);
			अवरोध;
		हाल HCLGE_MBX_HANDLE_VF_TBL:
			hclge_handle_vf_tbl(vport, req);
			अवरोध;
		शेष:
			dev_err(&hdev->pdev->dev,
				"un-supported mailbox message, code = %u\n",
				req->msg.code);
			अवरोध;
		पूर्ण

		/* PF driver should not reply IMP */
		अगर (hnae3_get_bit(req->mbx_need_resp, HCLGE_MBX_NEED_RESP_B) &&
		    req->msg.code < HCLGE_MBX_GET_VF_FLR_STATUS) अणु
			resp_msg.status = ret;
			hclge_gen_resp_to_vf(vport, req, &resp_msg);
		पूर्ण

		crq->desc[crq->next_to_use].flag = 0;
		hclge_mbx_ring_ptr_move_crq(crq);

		/* reinitialize ret after complete the mbx message processing */
		ret = 0;
	पूर्ण

	/* Write back CMDQ_RQ header poपूर्णांकer, M7 need this poपूर्णांकer */
	hclge_ग_लिखो_dev(&hdev->hw, HCLGE_NIC_CRQ_HEAD_REG, crq->next_to_use);
पूर्ण
