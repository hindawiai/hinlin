<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश <linux/etherdevice.h>
#समावेश <linux/iopoll.h>
#समावेश <net/rtnetlink.h>
#समावेश "hclgevf_cmd.h"
#समावेश "hclgevf_main.h"
#समावेश "hclge_mbx.h"
#समावेश "hnae3.h"

#घोषणा HCLGEVF_NAME	"hclgevf"

#घोषणा HCLGEVF_RESET_MAX_FAIL_CNT	5

अटल पूर्णांक hclgevf_reset_hdev(काष्ठा hclgevf_dev *hdev);
अटल व्योम hclgevf_task_schedule(काष्ठा hclgevf_dev *hdev,
				  अचिन्हित दीर्घ delay);

अटल काष्ठा hnae3_ae_algo ae_algovf;

अटल काष्ठा workqueue_काष्ठा *hclgevf_wq;

अटल स्थिर काष्ठा pci_device_id ae_algovf_pci_tbl[] = अणु
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_VF), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_RDMA_DCB_PFC_VF),
	 HNAE3_DEV_SUPPORT_ROCE_DCB_BITSपूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;

अटल स्थिर u8 hclgevf_hash_key[] = अणु
	0x6D, 0x5A, 0x56, 0xDA, 0x25, 0x5B, 0x0E, 0xC2,
	0x41, 0x67, 0x25, 0x3D, 0x43, 0xA3, 0x8F, 0xB0,
	0xD0, 0xCA, 0x2B, 0xCB, 0xAE, 0x7B, 0x30, 0xB4,
	0x77, 0xCB, 0x2D, 0xA3, 0x80, 0x30, 0xF2, 0x0C,
	0x6A, 0x42, 0xB7, 0x3B, 0xBE, 0xAC, 0x01, 0xFA
पूर्ण;

MODULE_DEVICE_TABLE(pci, ae_algovf_pci_tbl);

अटल स्थिर u32 cmdq_reg_addr_list[] = अणुHCLGEVF_CMDQ_TX_ADDR_L_REG,
					 HCLGEVF_CMDQ_TX_ADDR_H_REG,
					 HCLGEVF_CMDQ_TX_DEPTH_REG,
					 HCLGEVF_CMDQ_TX_TAIL_REG,
					 HCLGEVF_CMDQ_TX_HEAD_REG,
					 HCLGEVF_CMDQ_RX_ADDR_L_REG,
					 HCLGEVF_CMDQ_RX_ADDR_H_REG,
					 HCLGEVF_CMDQ_RX_DEPTH_REG,
					 HCLGEVF_CMDQ_RX_TAIL_REG,
					 HCLGEVF_CMDQ_RX_HEAD_REG,
					 HCLGEVF_VECTOR0_CMDQ_SRC_REG,
					 HCLGEVF_VECTOR0_CMDQ_STATE_REG,
					 HCLGEVF_CMDQ_INTR_EN_REG,
					 HCLGEVF_CMDQ_INTR_GEN_REGपूर्ण;

अटल स्थिर u32 common_reg_addr_list[] = अणुHCLGEVF_MISC_VECTOR_REG_BASE,
					   HCLGEVF_RST_ING,
					   HCLGEVF_GRO_EN_REGपूर्ण;

अटल स्थिर u32 ring_reg_addr_list[] = अणुHCLGEVF_RING_RX_ADDR_L_REG,
					 HCLGEVF_RING_RX_ADDR_H_REG,
					 HCLGEVF_RING_RX_BD_NUM_REG,
					 HCLGEVF_RING_RX_BD_LENGTH_REG,
					 HCLGEVF_RING_RX_MERGE_EN_REG,
					 HCLGEVF_RING_RX_TAIL_REG,
					 HCLGEVF_RING_RX_HEAD_REG,
					 HCLGEVF_RING_RX_FBD_NUM_REG,
					 HCLGEVF_RING_RX_OFFSET_REG,
					 HCLGEVF_RING_RX_FBD_OFFSET_REG,
					 HCLGEVF_RING_RX_STASH_REG,
					 HCLGEVF_RING_RX_BD_ERR_REG,
					 HCLGEVF_RING_TX_ADDR_L_REG,
					 HCLGEVF_RING_TX_ADDR_H_REG,
					 HCLGEVF_RING_TX_BD_NUM_REG,
					 HCLGEVF_RING_TX_PRIORITY_REG,
					 HCLGEVF_RING_TX_TC_REG,
					 HCLGEVF_RING_TX_MERGE_EN_REG,
					 HCLGEVF_RING_TX_TAIL_REG,
					 HCLGEVF_RING_TX_HEAD_REG,
					 HCLGEVF_RING_TX_FBD_NUM_REG,
					 HCLGEVF_RING_TX_OFFSET_REG,
					 HCLGEVF_RING_TX_EBD_NUM_REG,
					 HCLGEVF_RING_TX_EBD_OFFSET_REG,
					 HCLGEVF_RING_TX_BD_ERR_REG,
					 HCLGEVF_RING_EN_REGपूर्ण;

अटल स्थिर u32 tqp_पूर्णांकr_reg_addr_list[] = अणुHCLGEVF_TQP_INTR_CTRL_REG,
					     HCLGEVF_TQP_INTR_GL0_REG,
					     HCLGEVF_TQP_INTR_GL1_REG,
					     HCLGEVF_TQP_INTR_GL2_REG,
					     HCLGEVF_TQP_INTR_RL_REGपूर्ण;

अटल काष्ठा hclgevf_dev *hclgevf_ae_get_hdev(काष्ठा hnae3_handle *handle)
अणु
	अगर (!handle->client)
		वापस container_of(handle, काष्ठा hclgevf_dev, nic);
	अन्यथा अगर (handle->client->type == HNAE3_CLIENT_ROCE)
		वापस container_of(handle, काष्ठा hclgevf_dev, roce);
	अन्यथा
		वापस container_of(handle, काष्ठा hclgevf_dev, nic);
पूर्ण

अटल पूर्णांक hclgevf_tqps_update_stats(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclgevf_desc desc;
	काष्ठा hclgevf_tqp *tqp;
	पूर्णांक status;
	पूर्णांक i;

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		tqp = container_of(kinfo->tqp[i], काष्ठा hclgevf_tqp, q);
		hclgevf_cmd_setup_basic_desc(&desc,
					     HCLGEVF_OPC_QUERY_RX_STATUS,
					     true);

		desc.data[0] = cpu_to_le32(tqp->index & 0x1ff);
		status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
		अगर (status) अणु
			dev_err(&hdev->pdev->dev,
				"Query tqp stat fail, status = %d,queue = %d\n",
				status,	i);
			वापस status;
		पूर्ण
		tqp->tqp_stats.rcb_rx_ring_pktnum_rcd +=
			le32_to_cpu(desc.data[1]);

		hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_QUERY_TX_STATUS,
					     true);

		desc.data[0] = cpu_to_le32(tqp->index & 0x1ff);
		status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
		अगर (status) अणु
			dev_err(&hdev->pdev->dev,
				"Query tqp stat fail, status = %d,queue = %d\n",
				status, i);
			वापस status;
		पूर्ण
		tqp->tqp_stats.rcb_tx_ring_pktnum_rcd +=
			le32_to_cpu(desc.data[1]);
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 *hclgevf_tqps_get_stats(काष्ठा hnae3_handle *handle, u64 *data)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा hclgevf_tqp *tqp;
	u64 *buff = data;
	पूर्णांक i;

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		tqp = container_of(kinfo->tqp[i], काष्ठा hclgevf_tqp, q);
		*buff++ = tqp->tqp_stats.rcb_tx_ring_pktnum_rcd;
	पूर्ण
	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		tqp = container_of(kinfo->tqp[i], काष्ठा hclgevf_tqp, q);
		*buff++ = tqp->tqp_stats.rcb_rx_ring_pktnum_rcd;
	पूर्ण

	वापस buff;
पूर्ण

अटल पूर्णांक hclgevf_tqps_get_sset_count(काष्ठा hnae3_handle *handle, पूर्णांक strset)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;

	वापस kinfo->num_tqps * 2;
पूर्ण

अटल u8 *hclgevf_tqps_get_strings(काष्ठा hnae3_handle *handle, u8 *data)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	u8 *buff = data;
	पूर्णांक i;

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		काष्ठा hclgevf_tqp *tqp = container_of(kinfo->tqp[i],
						       काष्ठा hclgevf_tqp, q);
		snम_लिखो(buff, ETH_GSTRING_LEN, "txq%u_pktnum_rcd",
			 tqp->index);
		buff += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		काष्ठा hclgevf_tqp *tqp = container_of(kinfo->tqp[i],
						       काष्ठा hclgevf_tqp, q);
		snम_लिखो(buff, ETH_GSTRING_LEN, "rxq%u_pktnum_rcd",
			 tqp->index);
		buff += ETH_GSTRING_LEN;
	पूर्ण

	वापस buff;
पूर्ण

अटल व्योम hclgevf_update_stats(काष्ठा hnae3_handle *handle,
				 काष्ठा net_device_stats *net_stats)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	पूर्णांक status;

	status = hclgevf_tqps_update_stats(handle);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"VF update of TQPS stats fail, status = %d.\n",
			status);
पूर्ण

अटल पूर्णांक hclgevf_get_sset_count(काष्ठा hnae3_handle *handle, पूर्णांक strset)
अणु
	अगर (strset == ETH_SS_TEST)
		वापस -EOPNOTSUPP;
	अन्यथा अगर (strset == ETH_SS_STATS)
		वापस hclgevf_tqps_get_sset_count(handle, strset);

	वापस 0;
पूर्ण

अटल व्योम hclgevf_get_strings(काष्ठा hnae3_handle *handle, u32 strset,
				u8 *data)
अणु
	u8 *p = (अक्षर *)data;

	अगर (strset == ETH_SS_STATS)
		p = hclgevf_tqps_get_strings(handle, p);
पूर्ण

अटल व्योम hclgevf_get_stats(काष्ठा hnae3_handle *handle, u64 *data)
अणु
	hclgevf_tqps_get_stats(handle, data);
पूर्ण

अटल व्योम hclgevf_build_send_msg(काष्ठा hclge_vf_to_pf_msg *msg, u8 code,
				   u8 subcode)
अणु
	अगर (msg) अणु
		स_रखो(msg, 0, माप(काष्ठा hclge_vf_to_pf_msg));
		msg->code = code;
		msg->subcode = subcode;
	पूर्ण
पूर्ण

अटल पूर्णांक hclgevf_get_tc_info(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclge_vf_to_pf_msg send_msg;
	u8 resp_msg;
	पूर्णांक status;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_GET_TCINFO, 0);
	status = hclgevf_send_mbx_msg(hdev, &send_msg, true, &resp_msg,
				      माप(resp_msg));
	अगर (status) अणु
		dev_err(&hdev->pdev->dev,
			"VF request to get TC info from PF failed %d",
			status);
		वापस status;
	पूर्ण

	hdev->hw_tc_map = resp_msg;

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_get_port_base_vlan_filter_state(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hnae3_handle *nic = &hdev->nic;
	काष्ठा hclge_vf_to_pf_msg send_msg;
	u8 resp_msg;
	पूर्णांक ret;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_SET_VLAN,
			       HCLGE_MBX_GET_PORT_BASE_VLAN_STATE);
	ret = hclgevf_send_mbx_msg(hdev, &send_msg, true, &resp_msg,
				   माप(u8));
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"VF request to get port based vlan state failed %d",
			ret);
		वापस ret;
	पूर्ण

	nic->port_base_vlan_state = resp_msg;

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_get_queue_info(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा HCLGEVF_TQPS_RSS_INFO_LEN	6
#घोषणा HCLGEVF_TQPS_ALLOC_OFFSET	0
#घोषणा HCLGEVF_TQPS_RSS_SIZE_OFFSET	2
#घोषणा HCLGEVF_TQPS_RX_BUFFER_LEN_OFFSET	4

	u8 resp_msg[HCLGEVF_TQPS_RSS_INFO_LEN];
	काष्ठा hclge_vf_to_pf_msg send_msg;
	पूर्णांक status;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_GET_QINFO, 0);
	status = hclgevf_send_mbx_msg(hdev, &send_msg, true, resp_msg,
				      HCLGEVF_TQPS_RSS_INFO_LEN);
	अगर (status) अणु
		dev_err(&hdev->pdev->dev,
			"VF request to get tqp info from PF failed %d",
			status);
		वापस status;
	पूर्ण

	स_नकल(&hdev->num_tqps, &resp_msg[HCLGEVF_TQPS_ALLOC_OFFSET],
	       माप(u16));
	स_नकल(&hdev->rss_size_max, &resp_msg[HCLGEVF_TQPS_RSS_SIZE_OFFSET],
	       माप(u16));
	स_नकल(&hdev->rx_buf_len, &resp_msg[HCLGEVF_TQPS_RX_BUFFER_LEN_OFFSET],
	       माप(u16));

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_get_queue_depth(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा HCLGEVF_TQPS_DEPTH_INFO_LEN	4
#घोषणा HCLGEVF_TQPS_NUM_TX_DESC_OFFSET	0
#घोषणा HCLGEVF_TQPS_NUM_RX_DESC_OFFSET	2

	u8 resp_msg[HCLGEVF_TQPS_DEPTH_INFO_LEN];
	काष्ठा hclge_vf_to_pf_msg send_msg;
	पूर्णांक ret;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_GET_QDEPTH, 0);
	ret = hclgevf_send_mbx_msg(hdev, &send_msg, true, resp_msg,
				   HCLGEVF_TQPS_DEPTH_INFO_LEN);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"VF request to get tqp depth info from PF failed %d",
			ret);
		वापस ret;
	पूर्ण

	स_नकल(&hdev->num_tx_desc, &resp_msg[HCLGEVF_TQPS_NUM_TX_DESC_OFFSET],
	       माप(u16));
	स_नकल(&hdev->num_rx_desc, &resp_msg[HCLGEVF_TQPS_NUM_RX_DESC_OFFSET],
	       माप(u16));

	वापस 0;
पूर्ण

अटल u16 hclgevf_get_qid_global(काष्ठा hnae3_handle *handle, u16 queue_id)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclge_vf_to_pf_msg send_msg;
	u16 qid_in_pf = 0;
	u8 resp_data[2];
	पूर्णांक ret;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_GET_QID_IN_PF, 0);
	स_नकल(send_msg.data, &queue_id, माप(queue_id));
	ret = hclgevf_send_mbx_msg(hdev, &send_msg, true, resp_data,
				   माप(resp_data));
	अगर (!ret)
		qid_in_pf = *(u16 *)resp_data;

	वापस qid_in_pf;
पूर्ण

अटल पूर्णांक hclgevf_get_pf_media_type(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclge_vf_to_pf_msg send_msg;
	u8 resp_msg[2];
	पूर्णांक ret;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_GET_MEDIA_TYPE, 0);
	ret = hclgevf_send_mbx_msg(hdev, &send_msg, true, resp_msg,
				   माप(resp_msg));
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"VF request to get the pf port media type failed %d",
			ret);
		वापस ret;
	पूर्ण

	hdev->hw.mac.media_type = resp_msg[0];
	hdev->hw.mac.module_type = resp_msg[1];

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_alloc_tqps(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclgevf_tqp *tqp;
	पूर्णांक i;

	hdev->htqp = devm_kसुस्मृति(&hdev->pdev->dev, hdev->num_tqps,
				  माप(काष्ठा hclgevf_tqp), GFP_KERNEL);
	अगर (!hdev->htqp)
		वापस -ENOMEM;

	tqp = hdev->htqp;

	क्रम (i = 0; i < hdev->num_tqps; i++) अणु
		tqp->dev = &hdev->pdev->dev;
		tqp->index = i;

		tqp->q.ae_algo = &ae_algovf;
		tqp->q.buf_size = hdev->rx_buf_len;
		tqp->q.tx_desc_num = hdev->num_tx_desc;
		tqp->q.rx_desc_num = hdev->num_rx_desc;

		/* need an extended offset to configure queues >=
		 * HCLGEVF_TQP_MAX_SIZE_DEV_V2.
		 */
		अगर (i < HCLGEVF_TQP_MAX_SIZE_DEV_V2)
			tqp->q.io_base = hdev->hw.io_base +
					 HCLGEVF_TQP_REG_OFFSET +
					 i * HCLGEVF_TQP_REG_SIZE;
		अन्यथा
			tqp->q.io_base = hdev->hw.io_base +
					 HCLGEVF_TQP_REG_OFFSET +
					 HCLGEVF_TQP_EXT_REG_OFFSET +
					 (i - HCLGEVF_TQP_MAX_SIZE_DEV_V2) *
					 HCLGEVF_TQP_REG_SIZE;

		tqp++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_knic_setup(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hnae3_handle *nic = &hdev->nic;
	काष्ठा hnae3_knic_निजी_info *kinfo;
	u16 new_tqps = hdev->num_tqps;
	अचिन्हित पूर्णांक i;
	u8 num_tc = 0;

	kinfo = &nic->kinfo;
	kinfo->num_tx_desc = hdev->num_tx_desc;
	kinfo->num_rx_desc = hdev->num_rx_desc;
	kinfo->rx_buf_len = hdev->rx_buf_len;
	क्रम (i = 0; i < HCLGEVF_MAX_TC_NUM; i++)
		अगर (hdev->hw_tc_map & BIT(i))
			num_tc++;

	num_tc = num_tc ? num_tc : 1;
	kinfo->tc_info.num_tc = num_tc;
	kinfo->rss_size = min_t(u16, hdev->rss_size_max, new_tqps / num_tc);
	new_tqps = kinfo->rss_size * num_tc;
	kinfo->num_tqps = min(new_tqps, hdev->num_tqps);

	kinfo->tqp = devm_kसुस्मृति(&hdev->pdev->dev, kinfo->num_tqps,
				  माप(काष्ठा hnae3_queue *), GFP_KERNEL);
	अगर (!kinfo->tqp)
		वापस -ENOMEM;

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		hdev->htqp[i].q.handle = &hdev->nic;
		hdev->htqp[i].q.tqp_index = i;
		kinfo->tqp[i] = &hdev->htqp[i].q;
	पूर्ण

	/* after init the max rss_size and tqps, adjust the शेष tqp numbers
	 * and rss size with the actual vector numbers
	 */
	kinfo->num_tqps = min_t(u16, hdev->num_nic_msix - 1, kinfo->num_tqps);
	kinfo->rss_size = min_t(u16, kinfo->num_tqps / num_tc,
				kinfo->rss_size);

	वापस 0;
पूर्ण

अटल व्योम hclgevf_request_link_info(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclge_vf_to_pf_msg send_msg;
	पूर्णांक status;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_GET_LINK_STATUS, 0);
	status = hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"VF failed to fetch link status(%d) from PF", status);
पूर्ण

व्योम hclgevf_update_link_status(काष्ठा hclgevf_dev *hdev, पूर्णांक link_state)
अणु
	काष्ठा hnae3_handle *rhandle = &hdev->roce;
	काष्ठा hnae3_handle *handle = &hdev->nic;
	काष्ठा hnae3_client *rclient;
	काष्ठा hnae3_client *client;

	अगर (test_and_set_bit(HCLGEVF_STATE_LINK_UPDATING, &hdev->state))
		वापस;

	client = handle->client;
	rclient = hdev->roce_client;

	link_state =
		test_bit(HCLGEVF_STATE_DOWN, &hdev->state) ? 0 : link_state;
	अगर (link_state != hdev->hw.mac.link) अणु
		client->ops->link_status_change(handle, !!link_state);
		अगर (rclient && rclient->ops->link_status_change)
			rclient->ops->link_status_change(rhandle, !!link_state);
		hdev->hw.mac.link = link_state;
	पूर्ण

	clear_bit(HCLGEVF_STATE_LINK_UPDATING, &hdev->state);
पूर्ण

अटल व्योम hclgevf_update_link_mode(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा HCLGEVF_ADVERTISING	0
#घोषणा HCLGEVF_SUPPORTED	1

	काष्ठा hclge_vf_to_pf_msg send_msg;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_GET_LINK_MODE, 0);
	send_msg.data[0] = HCLGEVF_ADVERTISING;
	hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);
	send_msg.data[0] = HCLGEVF_SUPPORTED;
	hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);
पूर्ण

अटल पूर्णांक hclgevf_set_handle_info(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hnae3_handle *nic = &hdev->nic;
	पूर्णांक ret;

	nic->ae_algo = &ae_algovf;
	nic->pdev = hdev->pdev;
	nic->numa_node_mask = hdev->numa_node_mask;
	nic->flags |= HNAE3_SUPPORT_VF;

	ret = hclgevf_knic_setup(hdev);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "VF knic setup failed %d\n",
			ret);
	वापस ret;
पूर्ण

अटल व्योम hclgevf_मुक्त_vector(काष्ठा hclgevf_dev *hdev, पूर्णांक vector_id)
अणु
	अगर (hdev->vector_status[vector_id] == HCLGEVF_INVALID_VPORT) अणु
		dev_warn(&hdev->pdev->dev,
			 "vector(vector_id %d) has been freed.\n", vector_id);
		वापस;
	पूर्ण

	hdev->vector_status[vector_id] = HCLGEVF_INVALID_VPORT;
	hdev->num_msi_left += 1;
	hdev->num_msi_used -= 1;
पूर्ण

अटल पूर्णांक hclgevf_get_vector(काष्ठा hnae3_handle *handle, u16 vector_num,
			      काष्ठा hnae3_vector_info *vector_info)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hnae3_vector_info *vector = vector_info;
	पूर्णांक alloc = 0;
	पूर्णांक i, j;

	vector_num = min_t(u16, hdev->num_nic_msix - 1, vector_num);
	vector_num = min(hdev->num_msi_left, vector_num);

	क्रम (j = 0; j < vector_num; j++) अणु
		क्रम (i = HCLGEVF_MISC_VECTOR_NUM + 1; i < hdev->num_msi; i++) अणु
			अगर (hdev->vector_status[i] == HCLGEVF_INVALID_VPORT) अणु
				vector->vector = pci_irq_vector(hdev->pdev, i);
				vector->io_addr = hdev->hw.io_base +
					HCLGEVF_VECTOR_REG_BASE +
					(i - 1) * HCLGEVF_VECTOR_REG_OFFSET;
				hdev->vector_status[i] = 0;
				hdev->vector_irq[i] = vector->vector;

				vector++;
				alloc++;

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	hdev->num_msi_left -= alloc;
	hdev->num_msi_used += alloc;

	वापस alloc;
पूर्ण

अटल पूर्णांक hclgevf_get_vector_index(काष्ठा hclgevf_dev *hdev, पूर्णांक vector)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hdev->num_msi; i++)
		अगर (vector == hdev->vector_irq[i])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hclgevf_set_rss_algo_key(काष्ठा hclgevf_dev *hdev,
				    स्थिर u8 hfunc, स्थिर u8 *key)
अणु
	काष्ठा hclgevf_rss_config_cmd *req;
	अचिन्हित पूर्णांक key_offset = 0;
	काष्ठा hclgevf_desc desc;
	पूर्णांक key_counts;
	पूर्णांक key_size;
	पूर्णांक ret;

	key_counts = HCLGEVF_RSS_KEY_SIZE;
	req = (काष्ठा hclgevf_rss_config_cmd *)desc.data;

	जबतक (key_counts) अणु
		hclgevf_cmd_setup_basic_desc(&desc,
					     HCLGEVF_OPC_RSS_GENERIC_CONFIG,
					     false);

		req->hash_config |= (hfunc & HCLGEVF_RSS_HASH_ALGO_MASK);
		req->hash_config |=
			(key_offset << HCLGEVF_RSS_HASH_KEY_OFFSET_B);

		key_size = min(HCLGEVF_RSS_HASH_KEY_NUM, key_counts);
		स_नकल(req->hash_key,
		       key + key_offset * HCLGEVF_RSS_HASH_KEY_NUM, key_size);

		key_counts -= key_size;
		key_offset++;
		ret = hclgevf_cmd_send(&hdev->hw, &desc, 1);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"Configure RSS config fail, status = %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 hclgevf_get_rss_key_size(काष्ठा hnae3_handle *handle)
अणु
	वापस HCLGEVF_RSS_KEY_SIZE;
पूर्ण

अटल पूर्णांक hclgevf_set_rss_indir_table(काष्ठा hclgevf_dev *hdev)
अणु
	स्थिर u8 *indir = hdev->rss_cfg.rss_indirection_tbl;
	काष्ठा hclgevf_rss_indirection_table_cmd *req;
	काष्ठा hclgevf_desc desc;
	पूर्णांक rss_cfg_tbl_num;
	पूर्णांक status;
	पूर्णांक i, j;

	req = (काष्ठा hclgevf_rss_indirection_table_cmd *)desc.data;
	rss_cfg_tbl_num = hdev->ae_dev->dev_specs.rss_ind_tbl_size /
			  HCLGEVF_RSS_CFG_TBL_SIZE;

	क्रम (i = 0; i < rss_cfg_tbl_num; i++) अणु
		hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_RSS_INसूची_TABLE,
					     false);
		req->start_table_index =
			cpu_to_le16(i * HCLGEVF_RSS_CFG_TBL_SIZE);
		req->rss_set_biपंचांगap = cpu_to_le16(HCLGEVF_RSS_SET_BITMAP_MSK);
		क्रम (j = 0; j < HCLGEVF_RSS_CFG_TBL_SIZE; j++)
			req->rss_result[j] =
				indir[i * HCLGEVF_RSS_CFG_TBL_SIZE + j];

		status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
		अगर (status) अणु
			dev_err(&hdev->pdev->dev,
				"VF failed(=%d) to set RSS indirection table\n",
				status);
			वापस status;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_set_rss_tc_mode(काष्ठा hclgevf_dev *hdev,  u16 rss_size)
अणु
	काष्ठा hclgevf_rss_tc_mode_cmd *req;
	u16 tc_offset[HCLGEVF_MAX_TC_NUM];
	u16 tc_valid[HCLGEVF_MAX_TC_NUM];
	u16 tc_size[HCLGEVF_MAX_TC_NUM];
	काष्ठा hclgevf_desc desc;
	u16 roundup_size;
	अचिन्हित पूर्णांक i;
	पूर्णांक status;

	req = (काष्ठा hclgevf_rss_tc_mode_cmd *)desc.data;

	roundup_size = roundup_घात_of_two(rss_size);
	roundup_size = ilog2(roundup_size);

	क्रम (i = 0; i < HCLGEVF_MAX_TC_NUM; i++) अणु
		tc_valid[i] = !!(hdev->hw_tc_map & BIT(i));
		tc_size[i] = roundup_size;
		tc_offset[i] = rss_size * i;
	पूर्ण

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_RSS_TC_MODE, false);
	क्रम (i = 0; i < HCLGEVF_MAX_TC_NUM; i++) अणु
		u16 mode = 0;

		hnae3_set_bit(mode, HCLGEVF_RSS_TC_VALID_B,
			      (tc_valid[i] & 0x1));
		hnae3_set_field(mode, HCLGEVF_RSS_TC_SIZE_M,
				HCLGEVF_RSS_TC_SIZE_S, tc_size[i]);
		hnae3_set_bit(mode, HCLGEVF_RSS_TC_SIZE_MSB_B,
			      tc_size[i] >> HCLGEVF_RSS_TC_SIZE_MSB_OFFSET &
			      0x1);
		hnae3_set_field(mode, HCLGEVF_RSS_TC_OFFSET_M,
				HCLGEVF_RSS_TC_OFFSET_S, tc_offset[i]);

		req->rss_tc_mode[i] = cpu_to_le16(mode);
	पूर्ण
	status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	अगर (status)
		dev_err(&hdev->pdev->dev,
			"VF failed(=%d) to set rss tc mode\n", status);

	वापस status;
पूर्ण

/* क्रम revision 0x20, vf shared the same rss config with pf */
अटल पूर्णांक hclgevf_get_rss_hash_key(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा HCLGEVF_RSS_MBX_RESP_LEN	8
	काष्ठा hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	u8 resp_msg[HCLGEVF_RSS_MBX_RESP_LEN];
	काष्ठा hclge_vf_to_pf_msg send_msg;
	u16 msg_num, hash_key_index;
	u8 index;
	पूर्णांक ret;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_GET_RSS_KEY, 0);
	msg_num = (HCLGEVF_RSS_KEY_SIZE + HCLGEVF_RSS_MBX_RESP_LEN - 1) /
			HCLGEVF_RSS_MBX_RESP_LEN;
	क्रम (index = 0; index < msg_num; index++) अणु
		send_msg.data[0] = index;
		ret = hclgevf_send_mbx_msg(hdev, &send_msg, true, resp_msg,
					   HCLGEVF_RSS_MBX_RESP_LEN);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"VF get rss hash key from PF failed, ret=%d",
				ret);
			वापस ret;
		पूर्ण

		hash_key_index = HCLGEVF_RSS_MBX_RESP_LEN * index;
		अगर (index == msg_num - 1)
			स_नकल(&rss_cfg->rss_hash_key[hash_key_index],
			       &resp_msg[0],
			       HCLGEVF_RSS_KEY_SIZE - hash_key_index);
		अन्यथा
			स_नकल(&rss_cfg->rss_hash_key[hash_key_index],
			       &resp_msg[0], HCLGEVF_RSS_MBX_RESP_LEN);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_get_rss(काष्ठा hnae3_handle *handle, u32 *indir, u8 *key,
			   u8 *hfunc)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	पूर्णांक i, ret;

	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2) अणु
		/* Get hash algorithm */
		अगर (hfunc) अणु
			चयन (rss_cfg->hash_algo) अणु
			हाल HCLGEVF_RSS_HASH_ALGO_TOEPLITZ:
				*hfunc = ETH_RSS_HASH_TOP;
				अवरोध;
			हाल HCLGEVF_RSS_HASH_ALGO_SIMPLE:
				*hfunc = ETH_RSS_HASH_XOR;
				अवरोध;
			शेष:
				*hfunc = ETH_RSS_HASH_UNKNOWN;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Get the RSS Key required by the user */
		अगर (key)
			स_नकल(key, rss_cfg->rss_hash_key,
			       HCLGEVF_RSS_KEY_SIZE);
	पूर्ण अन्यथा अणु
		अगर (hfunc)
			*hfunc = ETH_RSS_HASH_TOP;
		अगर (key) अणु
			ret = hclgevf_get_rss_hash_key(hdev);
			अगर (ret)
				वापस ret;
			स_नकल(key, rss_cfg->rss_hash_key,
			       HCLGEVF_RSS_KEY_SIZE);
		पूर्ण
	पूर्ण

	अगर (indir)
		क्रम (i = 0; i < hdev->ae_dev->dev_specs.rss_ind_tbl_size; i++)
			indir[i] = rss_cfg->rss_indirection_tbl[i];

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_set_rss(काष्ठा hnae3_handle *handle, स्थिर u32 *indir,
			   स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	पूर्णांक ret, i;

	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2) अणु
		/* Set the RSS Hash Key अगर specअगरअगरed by the user */
		अगर (key) अणु
			चयन (hfunc) अणु
			हाल ETH_RSS_HASH_TOP:
				rss_cfg->hash_algo =
					HCLGEVF_RSS_HASH_ALGO_TOEPLITZ;
				अवरोध;
			हाल ETH_RSS_HASH_XOR:
				rss_cfg->hash_algo =
					HCLGEVF_RSS_HASH_ALGO_SIMPLE;
				अवरोध;
			हाल ETH_RSS_HASH_NO_CHANGE:
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण

			ret = hclgevf_set_rss_algo_key(hdev, rss_cfg->hash_algo,
						       key);
			अगर (ret)
				वापस ret;

			/* Update the shaकरोw RSS key with user specअगरied qids */
			स_नकल(rss_cfg->rss_hash_key, key,
			       HCLGEVF_RSS_KEY_SIZE);
		पूर्ण
	पूर्ण

	/* update the shaकरोw RSS table with user specअगरied qids */
	क्रम (i = 0; i < hdev->ae_dev->dev_specs.rss_ind_tbl_size; i++)
		rss_cfg->rss_indirection_tbl[i] = indir[i];

	/* update the hardware */
	वापस hclgevf_set_rss_indir_table(hdev);
पूर्ण

अटल u8 hclgevf_get_rss_hash_bits(काष्ठा ethtool_rxnfc *nfc)
अणु
	u8 hash_sets = nfc->data & RXH_L4_B_0_1 ? HCLGEVF_S_PORT_BIT : 0;

	अगर (nfc->data & RXH_L4_B_2_3)
		hash_sets |= HCLGEVF_D_PORT_BIT;
	अन्यथा
		hash_sets &= ~HCLGEVF_D_PORT_BIT;

	अगर (nfc->data & RXH_IP_SRC)
		hash_sets |= HCLGEVF_S_IP_BIT;
	अन्यथा
		hash_sets &= ~HCLGEVF_S_IP_BIT;

	अगर (nfc->data & RXH_IP_DST)
		hash_sets |= HCLGEVF_D_IP_BIT;
	अन्यथा
		hash_sets &= ~HCLGEVF_D_IP_BIT;

	अगर (nfc->flow_type == SCTP_V4_FLOW || nfc->flow_type == SCTP_V6_FLOW)
		hash_sets |= HCLGEVF_V_TAG_BIT;

	वापस hash_sets;
पूर्ण

अटल पूर्णांक hclgevf_init_rss_tuple_cmd(काष्ठा hnae3_handle *handle,
				      काष्ठा ethtool_rxnfc *nfc,
				      काष्ठा hclgevf_rss_input_tuple_cmd *req)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	u8 tuple_sets;

	req->ipv4_tcp_en = rss_cfg->rss_tuple_sets.ipv4_tcp_en;
	req->ipv4_udp_en = rss_cfg->rss_tuple_sets.ipv4_udp_en;
	req->ipv4_sctp_en = rss_cfg->rss_tuple_sets.ipv4_sctp_en;
	req->ipv4_fragment_en = rss_cfg->rss_tuple_sets.ipv4_fragment_en;
	req->ipv6_tcp_en = rss_cfg->rss_tuple_sets.ipv6_tcp_en;
	req->ipv6_udp_en = rss_cfg->rss_tuple_sets.ipv6_udp_en;
	req->ipv6_sctp_en = rss_cfg->rss_tuple_sets.ipv6_sctp_en;
	req->ipv6_fragment_en = rss_cfg->rss_tuple_sets.ipv6_fragment_en;

	tuple_sets = hclgevf_get_rss_hash_bits(nfc);
	चयन (nfc->flow_type) अणु
	हाल TCP_V4_FLOW:
		req->ipv4_tcp_en = tuple_sets;
		अवरोध;
	हाल TCP_V6_FLOW:
		req->ipv6_tcp_en = tuple_sets;
		अवरोध;
	हाल UDP_V4_FLOW:
		req->ipv4_udp_en = tuple_sets;
		अवरोध;
	हाल UDP_V6_FLOW:
		req->ipv6_udp_en = tuple_sets;
		अवरोध;
	हाल SCTP_V4_FLOW:
		req->ipv4_sctp_en = tuple_sets;
		अवरोध;
	हाल SCTP_V6_FLOW:
		अगर (hdev->ae_dev->dev_version <= HNAE3_DEVICE_VERSION_V2 &&
		    (nfc->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)))
			वापस -EINVAL;

		req->ipv6_sctp_en = tuple_sets;
		अवरोध;
	हाल IPV4_FLOW:
		req->ipv4_fragment_en = HCLGEVF_RSS_INPUT_TUPLE_OTHER;
		अवरोध;
	हाल IPV6_FLOW:
		req->ipv6_fragment_en = HCLGEVF_RSS_INPUT_TUPLE_OTHER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_set_rss_tuple(काष्ठा hnae3_handle *handle,
				 काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	काष्ठा hclgevf_rss_input_tuple_cmd *req;
	काष्ठा hclgevf_desc desc;
	पूर्णांक ret;

	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)
		वापस -EOPNOTSUPP;

	अगर (nfc->data &
	    ~(RXH_IP_SRC | RXH_IP_DST | RXH_L4_B_0_1 | RXH_L4_B_2_3))
		वापस -EINVAL;

	req = (काष्ठा hclgevf_rss_input_tuple_cmd *)desc.data;
	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_RSS_INPUT_TUPLE, false);

	ret = hclgevf_init_rss_tuple_cmd(handle, nfc, req);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to init rss tuple cmd, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"Set rss tuple fail, status = %d\n", ret);
		वापस ret;
	पूर्ण

	rss_cfg->rss_tuple_sets.ipv4_tcp_en = req->ipv4_tcp_en;
	rss_cfg->rss_tuple_sets.ipv4_udp_en = req->ipv4_udp_en;
	rss_cfg->rss_tuple_sets.ipv4_sctp_en = req->ipv4_sctp_en;
	rss_cfg->rss_tuple_sets.ipv4_fragment_en = req->ipv4_fragment_en;
	rss_cfg->rss_tuple_sets.ipv6_tcp_en = req->ipv6_tcp_en;
	rss_cfg->rss_tuple_sets.ipv6_udp_en = req->ipv6_udp_en;
	rss_cfg->rss_tuple_sets.ipv6_sctp_en = req->ipv6_sctp_en;
	rss_cfg->rss_tuple_sets.ipv6_fragment_en = req->ipv6_fragment_en;
	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_get_rss_tuple_by_flow_type(काष्ठा hclgevf_dev *hdev,
					      पूर्णांक flow_type, u8 *tuple_sets)
अणु
	चयन (flow_type) अणु
	हाल TCP_V4_FLOW:
		*tuple_sets = hdev->rss_cfg.rss_tuple_sets.ipv4_tcp_en;
		अवरोध;
	हाल UDP_V4_FLOW:
		*tuple_sets = hdev->rss_cfg.rss_tuple_sets.ipv4_udp_en;
		अवरोध;
	हाल TCP_V6_FLOW:
		*tuple_sets = hdev->rss_cfg.rss_tuple_sets.ipv6_tcp_en;
		अवरोध;
	हाल UDP_V6_FLOW:
		*tuple_sets = hdev->rss_cfg.rss_tuple_sets.ipv6_udp_en;
		अवरोध;
	हाल SCTP_V4_FLOW:
		*tuple_sets = hdev->rss_cfg.rss_tuple_sets.ipv4_sctp_en;
		अवरोध;
	हाल SCTP_V6_FLOW:
		*tuple_sets = hdev->rss_cfg.rss_tuple_sets.ipv6_sctp_en;
		अवरोध;
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		*tuple_sets = HCLGEVF_S_IP_BIT | HCLGEVF_D_IP_BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 hclgevf_convert_rss_tuple(u8 tuple_sets)
अणु
	u64 tuple_data = 0;

	अगर (tuple_sets & HCLGEVF_D_PORT_BIT)
		tuple_data |= RXH_L4_B_2_3;
	अगर (tuple_sets & HCLGEVF_S_PORT_BIT)
		tuple_data |= RXH_L4_B_0_1;
	अगर (tuple_sets & HCLGEVF_D_IP_BIT)
		tuple_data |= RXH_IP_DST;
	अगर (tuple_sets & HCLGEVF_S_IP_BIT)
		tuple_data |= RXH_IP_SRC;

	वापस tuple_data;
पूर्ण

अटल पूर्णांक hclgevf_get_rss_tuple(काष्ठा hnae3_handle *handle,
				 काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	u8 tuple_sets;
	पूर्णांक ret;

	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)
		वापस -EOPNOTSUPP;

	nfc->data = 0;

	ret = hclgevf_get_rss_tuple_by_flow_type(hdev, nfc->flow_type,
						 &tuple_sets);
	अगर (ret || !tuple_sets)
		वापस ret;

	nfc->data = hclgevf_convert_rss_tuple(tuple_sets);

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_set_rss_input_tuple(काष्ठा hclgevf_dev *hdev,
				       काष्ठा hclgevf_rss_cfg *rss_cfg)
अणु
	काष्ठा hclgevf_rss_input_tuple_cmd *req;
	काष्ठा hclgevf_desc desc;
	पूर्णांक ret;

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_RSS_INPUT_TUPLE, false);

	req = (काष्ठा hclgevf_rss_input_tuple_cmd *)desc.data;

	req->ipv4_tcp_en = rss_cfg->rss_tuple_sets.ipv4_tcp_en;
	req->ipv4_udp_en = rss_cfg->rss_tuple_sets.ipv4_udp_en;
	req->ipv4_sctp_en = rss_cfg->rss_tuple_sets.ipv4_sctp_en;
	req->ipv4_fragment_en = rss_cfg->rss_tuple_sets.ipv4_fragment_en;
	req->ipv6_tcp_en = rss_cfg->rss_tuple_sets.ipv6_tcp_en;
	req->ipv6_udp_en = rss_cfg->rss_tuple_sets.ipv6_udp_en;
	req->ipv6_sctp_en = rss_cfg->rss_tuple_sets.ipv6_sctp_en;
	req->ipv6_fragment_en = rss_cfg->rss_tuple_sets.ipv6_fragment_en;

	ret = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"Configure rss input fail, status = %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hclgevf_get_tc_size(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;

	वापस rss_cfg->rss_size;
पूर्ण

अटल पूर्णांक hclgevf_bind_ring_to_vector(काष्ठा hnae3_handle *handle, bool en,
				       पूर्णांक vector_id,
				       काष्ठा hnae3_ring_chain_node *ring_chain)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclge_vf_to_pf_msg send_msg;
	काष्ठा hnae3_ring_chain_node *node;
	पूर्णांक status;
	पूर्णांक i = 0;

	स_रखो(&send_msg, 0, माप(send_msg));
	send_msg.code = en ? HCLGE_MBX_MAP_RING_TO_VECTOR :
		HCLGE_MBX_UNMAP_RING_TO_VECTOR;
	send_msg.vector_id = vector_id;

	क्रम (node = ring_chain; node; node = node->next) अणु
		send_msg.param[i].ring_type =
				hnae3_get_bit(node->flag, HNAE3_RING_TYPE_B);

		send_msg.param[i].tqp_index = node->tqp_index;
		send_msg.param[i].पूर्णांक_gl_index =
					hnae3_get_field(node->पूर्णांक_gl_idx,
							HNAE3_RING_GL_IDX_M,
							HNAE3_RING_GL_IDX_S);

		i++;
		अगर (i == HCLGE_MBX_MAX_RING_CHAIN_PARAM_NUM || !node->next) अणु
			send_msg.ring_num = i;

			status = hclgevf_send_mbx_msg(hdev, &send_msg, false,
						      शून्य, 0);
			अगर (status) अणु
				dev_err(&hdev->pdev->dev,
					"Map TQP fail, status is %d.\n",
					status);
				वापस status;
			पूर्ण
			i = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_map_ring_to_vector(काष्ठा hnae3_handle *handle, पूर्णांक vector,
				      काष्ठा hnae3_ring_chain_node *ring_chain)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	पूर्णांक vector_id;

	vector_id = hclgevf_get_vector_index(hdev, vector);
	अगर (vector_id < 0) अणु
		dev_err(&handle->pdev->dev,
			"Get vector index fail. ret =%d\n", vector_id);
		वापस vector_id;
	पूर्ण

	वापस hclgevf_bind_ring_to_vector(handle, true, vector_id, ring_chain);
पूर्ण

अटल पूर्णांक hclgevf_unmap_ring_from_vector(
				काष्ठा hnae3_handle *handle,
				पूर्णांक vector,
				काष्ठा hnae3_ring_chain_node *ring_chain)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	पूर्णांक ret, vector_id;

	अगर (test_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state))
		वापस 0;

	vector_id = hclgevf_get_vector_index(hdev, vector);
	अगर (vector_id < 0) अणु
		dev_err(&handle->pdev->dev,
			"Get vector index fail. ret =%d\n", vector_id);
		वापस vector_id;
	पूर्ण

	ret = hclgevf_bind_ring_to_vector(handle, false, vector_id, ring_chain);
	अगर (ret)
		dev_err(&handle->pdev->dev,
			"Unmap ring from vector fail. vector=%d, ret =%d\n",
			vector_id,
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclgevf_put_vector(काष्ठा hnae3_handle *handle, पूर्णांक vector)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	पूर्णांक vector_id;

	vector_id = hclgevf_get_vector_index(hdev, vector);
	अगर (vector_id < 0) अणु
		dev_err(&handle->pdev->dev,
			"hclgevf_put_vector get vector index fail. ret =%d\n",
			vector_id);
		वापस vector_id;
	पूर्ण

	hclgevf_मुक्त_vector(hdev, vector_id);

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_cmd_set_promisc_mode(काष्ठा hclgevf_dev *hdev,
					bool en_uc_pmc, bool en_mc_pmc,
					bool en_bc_pmc)
अणु
	काष्ठा hnae3_handle *handle = &hdev->nic;
	काष्ठा hclge_vf_to_pf_msg send_msg;
	पूर्णांक ret;

	स_रखो(&send_msg, 0, माप(send_msg));
	send_msg.code = HCLGE_MBX_SET_PROMISC_MODE;
	send_msg.en_bc = en_bc_pmc ? 1 : 0;
	send_msg.en_uc = en_uc_pmc ? 1 : 0;
	send_msg.en_mc = en_mc_pmc ? 1 : 0;
	send_msg.en_limit_promisc = test_bit(HNAE3_PFLAG_LIMIT_PROMISC,
					     &handle->priv_flags) ? 1 : 0;

	ret = hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"Set promisc mode fail, status is %d.\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclgevf_set_promisc_mode(काष्ठा hnae3_handle *handle, bool en_uc_pmc,
				    bool en_mc_pmc)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	bool en_bc_pmc;

	en_bc_pmc = hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2;

	वापस hclgevf_cmd_set_promisc_mode(hdev, en_uc_pmc, en_mc_pmc,
					    en_bc_pmc);
पूर्ण

अटल व्योम hclgevf_request_update_promisc_mode(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	set_bit(HCLGEVF_STATE_PROMISC_CHANGED, &hdev->state);
	hclgevf_task_schedule(hdev, 0);
पूर्ण

अटल व्योम hclgevf_sync_promisc_mode(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hnae3_handle *handle = &hdev->nic;
	bool en_uc_pmc = handle->netdev_flags & HNAE3_UPE;
	bool en_mc_pmc = handle->netdev_flags & HNAE3_MPE;
	पूर्णांक ret;

	अगर (test_bit(HCLGEVF_STATE_PROMISC_CHANGED, &hdev->state)) अणु
		ret = hclgevf_set_promisc_mode(handle, en_uc_pmc, en_mc_pmc);
		अगर (!ret)
			clear_bit(HCLGEVF_STATE_PROMISC_CHANGED, &hdev->state);
	पूर्ण
पूर्ण

अटल पूर्णांक hclgevf_tqp_enable_cmd_send(काष्ठा hclgevf_dev *hdev, u16 tqp_id,
				       u16 stream_id, bool enable)
अणु
	काष्ठा hclgevf_cfg_com_tqp_queue_cmd *req;
	काष्ठा hclgevf_desc desc;

	req = (काष्ठा hclgevf_cfg_com_tqp_queue_cmd *)desc.data;

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_CFG_COM_TQP_QUEUE,
				     false);
	req->tqp_id = cpu_to_le16(tqp_id & HCLGEVF_RING_ID_MASK);
	req->stream_id = cpu_to_le16(stream_id);
	अगर (enable)
		req->enable |= 1U << HCLGEVF_TQP_ENABLE_B;

	वापस hclgevf_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclgevf_tqp_enable(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	पूर्णांक ret;
	u16 i;

	क्रम (i = 0; i < handle->kinfo.num_tqps; i++) अणु
		ret = hclgevf_tqp_enable_cmd_send(hdev, i, 0, enable);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hclgevf_reset_tqp_stats(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा hclgevf_tqp *tqp;
	पूर्णांक i;

	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		tqp = container_of(kinfo->tqp[i], काष्ठा hclgevf_tqp, q);
		स_रखो(&tqp->tqp_stats, 0, माप(tqp->tqp_stats));
	पूर्ण
पूर्ण

अटल पूर्णांक hclgevf_get_host_mac_addr(काष्ठा hclgevf_dev *hdev, u8 *p)
अणु
	काष्ठा hclge_vf_to_pf_msg send_msg;
	u8 host_mac[ETH_ALEN];
	पूर्णांक status;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_GET_MAC_ADDR, 0);
	status = hclgevf_send_mbx_msg(hdev, &send_msg, true, host_mac,
				      ETH_ALEN);
	अगर (status) अणु
		dev_err(&hdev->pdev->dev,
			"fail to get VF MAC from host %d", status);
		वापस status;
	पूर्ण

	ether_addr_copy(p, host_mac);

	वापस 0;
पूर्ण

अटल व्योम hclgevf_get_mac_addr(काष्ठा hnae3_handle *handle, u8 *p)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	u8 host_mac_addr[ETH_ALEN];

	अगर (hclgevf_get_host_mac_addr(hdev, host_mac_addr))
		वापस;

	hdev->has_pf_mac = !is_zero_ether_addr(host_mac_addr);
	अगर (hdev->has_pf_mac)
		ether_addr_copy(p, host_mac_addr);
	अन्यथा
		ether_addr_copy(p, hdev->hw.mac.mac_addr);
पूर्ण

अटल पूर्णांक hclgevf_set_mac_addr(काष्ठा hnae3_handle *handle, व्योम *p,
				bool is_first)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	u8 *old_mac_addr = (u8 *)hdev->hw.mac.mac_addr;
	काष्ठा hclge_vf_to_pf_msg send_msg;
	u8 *new_mac_addr = (u8 *)p;
	पूर्णांक status;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_SET_UNICAST, 0);
	send_msg.subcode = HCLGE_MBX_MAC_VLAN_UC_MODIFY;
	ether_addr_copy(send_msg.data, new_mac_addr);
	अगर (is_first && !hdev->has_pf_mac)
		eth_zero_addr(&send_msg.data[ETH_ALEN]);
	अन्यथा
		ether_addr_copy(&send_msg.data[ETH_ALEN], old_mac_addr);
	status = hclgevf_send_mbx_msg(hdev, &send_msg, true, शून्य, 0);
	अगर (!status)
		ether_addr_copy(hdev->hw.mac.mac_addr, new_mac_addr);

	वापस status;
पूर्ण

अटल काष्ठा hclgevf_mac_addr_node *
hclgevf_find_mac_node(काष्ठा list_head *list, स्थिर u8 *mac_addr)
अणु
	काष्ठा hclgevf_mac_addr_node *mac_node, *पंचांगp;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node)
		अगर (ether_addr_equal(mac_addr, mac_node->mac_addr))
			वापस mac_node;

	वापस शून्य;
पूर्ण

अटल व्योम hclgevf_update_mac_node(काष्ठा hclgevf_mac_addr_node *mac_node,
				    क्रमागत HCLGEVF_MAC_NODE_STATE state)
अणु
	चयन (state) अणु
	/* from set_rx_mode or पंचांगp_add_list */
	हाल HCLGEVF_MAC_TO_ADD:
		अगर (mac_node->state == HCLGEVF_MAC_TO_DEL)
			mac_node->state = HCLGEVF_MAC_ACTIVE;
		अवरोध;
	/* only from set_rx_mode */
	हाल HCLGEVF_MAC_TO_DEL:
		अगर (mac_node->state == HCLGEVF_MAC_TO_ADD) अणु
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण अन्यथा अणु
			mac_node->state = HCLGEVF_MAC_TO_DEL;
		पूर्ण
		अवरोध;
	/* only from पंचांगp_add_list, the mac_node->state won't be
	 * HCLGEVF_MAC_ACTIVE
	 */
	हाल HCLGEVF_MAC_ACTIVE:
		अगर (mac_node->state == HCLGEVF_MAC_TO_ADD)
			mac_node->state = HCLGEVF_MAC_ACTIVE;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक hclgevf_update_mac_list(काष्ठा hnae3_handle *handle,
				   क्रमागत HCLGEVF_MAC_NODE_STATE state,
				   क्रमागत HCLGEVF_MAC_ADDR_TYPE mac_type,
				   स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclgevf_mac_addr_node *mac_node;
	काष्ठा list_head *list;

	list = (mac_type == HCLGEVF_MAC_ADDR_UC) ?
	       &hdev->mac_table.uc_mac_list : &hdev->mac_table.mc_mac_list;

	spin_lock_bh(&hdev->mac_table.mac_list_lock);

	/* अगर the mac addr is alपढ़ोy in the mac list, no need to add a new
	 * one पूर्णांकo it, just check the mac addr state, convert it to a new
	 * new state, or just हटाओ it, or करो nothing.
	 */
	mac_node = hclgevf_find_mac_node(list, addr);
	अगर (mac_node) अणु
		hclgevf_update_mac_node(mac_node, state);
		spin_unlock_bh(&hdev->mac_table.mac_list_lock);
		वापस 0;
	पूर्ण
	/* अगर this address is never added, unnecessary to delete */
	अगर (state == HCLGEVF_MAC_TO_DEL) अणु
		spin_unlock_bh(&hdev->mac_table.mac_list_lock);
		वापस -ENOENT;
	पूर्ण

	mac_node = kzalloc(माप(*mac_node), GFP_ATOMIC);
	अगर (!mac_node) अणु
		spin_unlock_bh(&hdev->mac_table.mac_list_lock);
		वापस -ENOMEM;
	पूर्ण

	mac_node->state = state;
	ether_addr_copy(mac_node->mac_addr, addr);
	list_add_tail(&mac_node->node, list);

	spin_unlock_bh(&hdev->mac_table.mac_list_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_add_uc_addr(काष्ठा hnae3_handle *handle,
			       स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस hclgevf_update_mac_list(handle, HCLGEVF_MAC_TO_ADD,
				       HCLGEVF_MAC_ADDR_UC, addr);
पूर्ण

अटल पूर्णांक hclgevf_rm_uc_addr(काष्ठा hnae3_handle *handle,
			      स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस hclgevf_update_mac_list(handle, HCLGEVF_MAC_TO_DEL,
				       HCLGEVF_MAC_ADDR_UC, addr);
पूर्ण

अटल पूर्णांक hclgevf_add_mc_addr(काष्ठा hnae3_handle *handle,
			       स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस hclgevf_update_mac_list(handle, HCLGEVF_MAC_TO_ADD,
				       HCLGEVF_MAC_ADDR_MC, addr);
पूर्ण

अटल पूर्णांक hclgevf_rm_mc_addr(काष्ठा hnae3_handle *handle,
			      स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस hclgevf_update_mac_list(handle, HCLGEVF_MAC_TO_DEL,
				       HCLGEVF_MAC_ADDR_MC, addr);
पूर्ण

अटल पूर्णांक hclgevf_add_del_mac_addr(काष्ठा hclgevf_dev *hdev,
				    काष्ठा hclgevf_mac_addr_node *mac_node,
				    क्रमागत HCLGEVF_MAC_ADDR_TYPE mac_type)
अणु
	काष्ठा hclge_vf_to_pf_msg send_msg;
	u8 code, subcode;

	अगर (mac_type == HCLGEVF_MAC_ADDR_UC) अणु
		code = HCLGE_MBX_SET_UNICAST;
		अगर (mac_node->state == HCLGEVF_MAC_TO_ADD)
			subcode = HCLGE_MBX_MAC_VLAN_UC_ADD;
		अन्यथा
			subcode = HCLGE_MBX_MAC_VLAN_UC_REMOVE;
	पूर्ण अन्यथा अणु
		code = HCLGE_MBX_SET_MULTICAST;
		अगर (mac_node->state == HCLGEVF_MAC_TO_ADD)
			subcode = HCLGE_MBX_MAC_VLAN_MC_ADD;
		अन्यथा
			subcode = HCLGE_MBX_MAC_VLAN_MC_REMOVE;
	पूर्ण

	hclgevf_build_send_msg(&send_msg, code, subcode);
	ether_addr_copy(send_msg.data, mac_node->mac_addr);
	वापस hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);
पूर्ण

अटल व्योम hclgevf_config_mac_list(काष्ठा hclgevf_dev *hdev,
				    काष्ठा list_head *list,
				    क्रमागत HCLGEVF_MAC_ADDR_TYPE mac_type)
अणु
	काष्ठा hclgevf_mac_addr_node *mac_node, *पंचांगp;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node) अणु
		ret = hclgevf_add_del_mac_addr(hdev, mac_node, mac_type);
		अगर  (ret) अणु
			dev_err(&hdev->pdev->dev,
				"failed to configure mac %pM, state = %d, ret = %d\n",
				mac_node->mac_addr, mac_node->state, ret);
			वापस;
		पूर्ण
		अगर (mac_node->state == HCLGEVF_MAC_TO_ADD) अणु
			mac_node->state = HCLGEVF_MAC_ACTIVE;
		पूर्ण अन्यथा अणु
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hclgevf_sync_from_add_list(काष्ठा list_head *add_list,
				       काष्ठा list_head *mac_list)
अणु
	काष्ठा hclgevf_mac_addr_node *mac_node, *पंचांगp, *new_node;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, add_list, node) अणु
		/* अगर the mac address from पंचांगp_add_list is not in the
		 * uc/mc_mac_list, it means have received a TO_DEL request
		 * during the समय winकरोw of sending mac config request to PF
		 * If mac_node state is ACTIVE, then change its state to TO_DEL,
		 * then it will be हटाओd at next समय. If is TO_ADD, it means
		 * send TO_ADD request failed, so just हटाओ the mac node.
		 */
		new_node = hclgevf_find_mac_node(mac_list, mac_node->mac_addr);
		अगर (new_node) अणु
			hclgevf_update_mac_node(new_node, mac_node->state);
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण अन्यथा अगर (mac_node->state == HCLGEVF_MAC_ACTIVE) अणु
			mac_node->state = HCLGEVF_MAC_TO_DEL;
			list_del(&mac_node->node);
			list_add_tail(&mac_node->node, mac_list);
		पूर्ण अन्यथा अणु
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hclgevf_sync_from_del_list(काष्ठा list_head *del_list,
				       काष्ठा list_head *mac_list)
अणु
	काष्ठा hclgevf_mac_addr_node *mac_node, *पंचांगp, *new_node;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, del_list, node) अणु
		new_node = hclgevf_find_mac_node(mac_list, mac_node->mac_addr);
		अगर (new_node) अणु
			/* If the mac addr is exist in the mac list, it means
			 * received a new request TO_ADD during the समय winकरोw
			 * of sending mac addr configurrequest to PF, so just
			 * change the mac state to ACTIVE.
			 */
			new_node->state = HCLGEVF_MAC_ACTIVE;
			list_del(&mac_node->node);
			kमुक्त(mac_node);
		पूर्ण अन्यथा अणु
			list_del(&mac_node->node);
			list_add_tail(&mac_node->node, mac_list);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hclgevf_clear_list(काष्ठा list_head *list)
अणु
	काष्ठा hclgevf_mac_addr_node *mac_node, *पंचांगp;

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node) अणु
		list_del(&mac_node->node);
		kमुक्त(mac_node);
	पूर्ण
पूर्ण

अटल व्योम hclgevf_sync_mac_list(काष्ठा hclgevf_dev *hdev,
				  क्रमागत HCLGEVF_MAC_ADDR_TYPE mac_type)
अणु
	काष्ठा hclgevf_mac_addr_node *mac_node, *पंचांगp, *new_node;
	काष्ठा list_head पंचांगp_add_list, पंचांगp_del_list;
	काष्ठा list_head *list;

	INIT_LIST_HEAD(&पंचांगp_add_list);
	INIT_LIST_HEAD(&पंचांगp_del_list);

	/* move the mac addr to the पंचांगp_add_list and पंचांगp_del_list, then
	 * we can add/delete these mac addr outside the spin lock
	 */
	list = (mac_type == HCLGEVF_MAC_ADDR_UC) ?
		&hdev->mac_table.uc_mac_list : &hdev->mac_table.mc_mac_list;

	spin_lock_bh(&hdev->mac_table.mac_list_lock);

	list_क्रम_each_entry_safe(mac_node, पंचांगp, list, node) अणु
		चयन (mac_node->state) अणु
		हाल HCLGEVF_MAC_TO_DEL:
			list_del(&mac_node->node);
			list_add_tail(&mac_node->node, &पंचांगp_del_list);
			अवरोध;
		हाल HCLGEVF_MAC_TO_ADD:
			new_node = kzalloc(माप(*new_node), GFP_ATOMIC);
			अगर (!new_node)
				जाओ stop_traverse;

			ether_addr_copy(new_node->mac_addr, mac_node->mac_addr);
			new_node->state = mac_node->state;
			list_add_tail(&new_node->node, &पंचांगp_add_list);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

stop_traverse:
	spin_unlock_bh(&hdev->mac_table.mac_list_lock);

	/* delete first, in order to get max mac table space क्रम adding */
	hclgevf_config_mac_list(hdev, &पंचांगp_del_list, mac_type);
	hclgevf_config_mac_list(hdev, &पंचांगp_add_list, mac_type);

	/* अगर some mac addresses were added/deleted fail, move back to the
	 * mac_list, and retry at next समय.
	 */
	spin_lock_bh(&hdev->mac_table.mac_list_lock);

	hclgevf_sync_from_del_list(&पंचांगp_del_list, list);
	hclgevf_sync_from_add_list(&पंचांगp_add_list, list);

	spin_unlock_bh(&hdev->mac_table.mac_list_lock);
पूर्ण

अटल व्योम hclgevf_sync_mac_table(काष्ठा hclgevf_dev *hdev)
अणु
	hclgevf_sync_mac_list(hdev, HCLGEVF_MAC_ADDR_UC);
	hclgevf_sync_mac_list(hdev, HCLGEVF_MAC_ADDR_MC);
पूर्ण

अटल व्योम hclgevf_uninit_mac_list(काष्ठा hclgevf_dev *hdev)
अणु
	spin_lock_bh(&hdev->mac_table.mac_list_lock);

	hclgevf_clear_list(&hdev->mac_table.uc_mac_list);
	hclgevf_clear_list(&hdev->mac_table.mc_mac_list);

	spin_unlock_bh(&hdev->mac_table.mac_list_lock);
पूर्ण

अटल पूर्णांक hclgevf_set_vlan_filter(काष्ठा hnae3_handle *handle,
				   __be16 proto, u16 vlan_id,
				   bool is_समाप्त)
अणु
#घोषणा HCLGEVF_VLAN_MBX_IS_KILL_OFFSET	0
#घोषणा HCLGEVF_VLAN_MBX_VLAN_ID_OFFSET	1
#घोषणा HCLGEVF_VLAN_MBX_PROTO_OFFSET	3

	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclge_vf_to_pf_msg send_msg;
	पूर्णांक ret;

	अगर (vlan_id > HCLGEVF_MAX_VLAN_ID)
		वापस -EINVAL;

	अगर (proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	/* When device is resetting or reset failed, firmware is unable to
	 * handle mailbox. Just record the vlan id, and हटाओ it after
	 * reset finished.
	 */
	अगर ((test_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state) ||
	     test_bit(HCLGEVF_STATE_RST_FAIL, &hdev->state)) && is_समाप्त) अणु
		set_bit(vlan_id, hdev->vlan_del_fail_bmap);
		वापस -EBUSY;
	पूर्ण

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_SET_VLAN,
			       HCLGE_MBX_VLAN_FILTER);
	send_msg.data[HCLGEVF_VLAN_MBX_IS_KILL_OFFSET] = is_समाप्त;
	स_नकल(&send_msg.data[HCLGEVF_VLAN_MBX_VLAN_ID_OFFSET], &vlan_id,
	       माप(vlan_id));
	स_नकल(&send_msg.data[HCLGEVF_VLAN_MBX_PROTO_OFFSET], &proto,
	       माप(proto));
	/* when हटाओ hw vlan filter failed, record the vlan id,
	 * and try to हटाओ it from hw later, to be consistence
	 * with stack.
	 */
	ret = hclgevf_send_mbx_msg(hdev, &send_msg, true, शून्य, 0);
	अगर (is_समाप्त && ret)
		set_bit(vlan_id, hdev->vlan_del_fail_bmap);

	वापस ret;
पूर्ण

अटल व्योम hclgevf_sync_vlan_filter(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा HCLGEVF_MAX_SYNC_COUNT	60
	काष्ठा hnae3_handle *handle = &hdev->nic;
	पूर्णांक ret, sync_cnt = 0;
	u16 vlan_id;

	vlan_id = find_first_bit(hdev->vlan_del_fail_bmap, VLAN_N_VID);
	जबतक (vlan_id != VLAN_N_VID) अणु
		ret = hclgevf_set_vlan_filter(handle, htons(ETH_P_8021Q),
					      vlan_id, true);
		अगर (ret)
			वापस;

		clear_bit(vlan_id, hdev->vlan_del_fail_bmap);
		sync_cnt++;
		अगर (sync_cnt >= HCLGEVF_MAX_SYNC_COUNT)
			वापस;

		vlan_id = find_first_bit(hdev->vlan_del_fail_bmap, VLAN_N_VID);
	पूर्ण
पूर्ण

अटल पूर्णांक hclgevf_en_hw_strip_rxvtag(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclge_vf_to_pf_msg send_msg;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_SET_VLAN,
			       HCLGE_MBX_VLAN_RX_OFF_CFG);
	send_msg.data[0] = enable ? 1 : 0;
	वापस hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);
पूर्ण

अटल पूर्णांक hclgevf_reset_tqp(काष्ठा hnae3_handle *handle)
अणु
#घोषणा HCLGEVF_RESET_ALL_QUEUE_DONE	1U
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclge_vf_to_pf_msg send_msg;
	u8 वापस_status = 0;
	पूर्णांक ret;
	u16 i;

	/* disable vf queue beक्रमe send queue reset msg to PF */
	ret = hclgevf_tqp_enable(handle, false);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "failed to disable tqp, ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_QUEUE_RESET, 0);

	ret = hclgevf_send_mbx_msg(hdev, &send_msg, true, &वापस_status,
				   माप(वापस_status));
	अगर (ret || वापस_status == HCLGEVF_RESET_ALL_QUEUE_DONE)
		वापस ret;

	क्रम (i = 1; i < handle->kinfo.num_tqps; i++) अणु
		hclgevf_build_send_msg(&send_msg, HCLGE_MBX_QUEUE_RESET, 0);
		स_नकल(send_msg.data, &i, माप(i));
		ret = hclgevf_send_mbx_msg(hdev, &send_msg, true, शून्य, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_set_mtu(काष्ठा hnae3_handle *handle, पूर्णांक new_mtu)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclge_vf_to_pf_msg send_msg;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_SET_MTU, 0);
	स_नकल(send_msg.data, &new_mtu, माप(new_mtu));
	वापस hclgevf_send_mbx_msg(hdev, &send_msg, true, शून्य, 0);
पूर्ण

अटल पूर्णांक hclgevf_notअगरy_client(काष्ठा hclgevf_dev *hdev,
				 क्रमागत hnae3_reset_notअगरy_type type)
अणु
	काष्ठा hnae3_client *client = hdev->nic_client;
	काष्ठा hnae3_handle *handle = &hdev->nic;
	पूर्णांक ret;

	अगर (!test_bit(HCLGEVF_STATE_NIC_REGISTERED, &hdev->state) ||
	    !client)
		वापस 0;

	अगर (!client->ops->reset_notअगरy)
		वापस -EOPNOTSUPP;

	ret = client->ops->reset_notअगरy(handle, type);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "notify nic client failed %d(%d)\n",
			type, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclgevf_notअगरy_roce_client(काष्ठा hclgevf_dev *hdev,
				      क्रमागत hnae3_reset_notअगरy_type type)
अणु
	काष्ठा hnae3_client *client = hdev->roce_client;
	काष्ठा hnae3_handle *handle = &hdev->roce;
	पूर्णांक ret;

	अगर (!test_bit(HCLGEVF_STATE_ROCE_REGISTERED, &hdev->state) || !client)
		वापस 0;

	अगर (!client->ops->reset_notअगरy)
		वापस -EOPNOTSUPP;

	ret = client->ops->reset_notअगरy(handle, type);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "notify roce client failed %d(%d)",
			type, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hclgevf_reset_रुको(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा HCLGEVF_RESET_WAIT_US	20000
#घोषणा HCLGEVF_RESET_WAIT_CNT	2000
#घोषणा HCLGEVF_RESET_WAIT_TIMEOUT_US	\
	(HCLGEVF_RESET_WAIT_US * HCLGEVF_RESET_WAIT_CNT)

	u32 val;
	पूर्णांक ret;

	अगर (hdev->reset_type == HNAE3_VF_RESET)
		ret = पढ़ोl_poll_समयout(hdev->hw.io_base +
					 HCLGEVF_VF_RST_ING, val,
					 !(val & HCLGEVF_VF_RST_ING_BIT),
					 HCLGEVF_RESET_WAIT_US,
					 HCLGEVF_RESET_WAIT_TIMEOUT_US);
	अन्यथा
		ret = पढ़ोl_poll_समयout(hdev->hw.io_base +
					 HCLGEVF_RST_ING, val,
					 !(val & HCLGEVF_RST_ING_BITS),
					 HCLGEVF_RESET_WAIT_US,
					 HCLGEVF_RESET_WAIT_TIMEOUT_US);

	/* hardware completion status should be available by this समय */
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"couldn't get reset done status from h/w, timeout!\n");
		वापस ret;
	पूर्ण

	/* we will रुको a bit more to let reset of the stack to complete. This
	 * might happen in हाल reset निश्चितion was made by PF. Yes, this also
	 * means we might end up रुकोing bit more even क्रम VF reset.
	 */
	msleep(5000);

	वापस 0;
पूर्ण

अटल व्योम hclgevf_reset_handshake(काष्ठा hclgevf_dev *hdev, bool enable)
अणु
	u32 reg_val;

	reg_val = hclgevf_पढ़ो_dev(&hdev->hw, HCLGEVF_NIC_CSQ_DEPTH_REG);
	अगर (enable)
		reg_val |= HCLGEVF_NIC_SW_RST_RDY;
	अन्यथा
		reg_val &= ~HCLGEVF_NIC_SW_RST_RDY;

	hclgevf_ग_लिखो_dev(&hdev->hw, HCLGEVF_NIC_CSQ_DEPTH_REG,
			  reg_val);
पूर्ण

अटल पूर्णांक hclgevf_reset_stack(काष्ठा hclgevf_dev *hdev)
अणु
	पूर्णांक ret;

	/* uninitialize the nic client */
	ret = hclgevf_notअगरy_client(hdev, HNAE3_UNINIT_CLIENT);
	अगर (ret)
		वापस ret;

	/* re-initialize the hclge device */
	ret = hclgevf_reset_hdev(hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"hclge device re-init failed, VF is disabled!\n");
		वापस ret;
	पूर्ण

	/* bring up the nic client again */
	ret = hclgevf_notअगरy_client(hdev, HNAE3_INIT_CLIENT);
	अगर (ret)
		वापस ret;

	/* clear handshake status with IMP */
	hclgevf_reset_handshake(hdev, false);

	/* bring up the nic to enable TX/RX again */
	वापस hclgevf_notअगरy_client(hdev, HNAE3_UP_CLIENT);
पूर्ण

अटल पूर्णांक hclgevf_reset_prepare_रुको(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा HCLGEVF_RESET_SYNC_TIME 100

	अगर (hdev->reset_type == HNAE3_VF_FUNC_RESET) अणु
		काष्ठा hclge_vf_to_pf_msg send_msg;
		पूर्णांक ret;

		hclgevf_build_send_msg(&send_msg, HCLGE_MBX_RESET, 0);
		ret = hclgevf_send_mbx_msg(hdev, &send_msg, true, शून्य, 0);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"failed to assert VF reset, ret = %d\n", ret);
			वापस ret;
		पूर्ण
		hdev->rst_stats.vf_func_rst_cnt++;
	पूर्ण

	set_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state);
	/* inक्रमm hardware that preparatory work is करोne */
	msleep(HCLGEVF_RESET_SYNC_TIME);
	hclgevf_reset_handshake(hdev, true);
	dev_info(&hdev->pdev->dev, "prepare reset(%d) wait done\n",
		 hdev->reset_type);

	वापस 0;
पूर्ण

अटल व्योम hclgevf_dump_rst_info(काष्ठा hclgevf_dev *hdev)
अणु
	dev_info(&hdev->pdev->dev, "VF function reset count: %u\n",
		 hdev->rst_stats.vf_func_rst_cnt);
	dev_info(&hdev->pdev->dev, "FLR reset count: %u\n",
		 hdev->rst_stats.flr_rst_cnt);
	dev_info(&hdev->pdev->dev, "VF reset count: %u\n",
		 hdev->rst_stats.vf_rst_cnt);
	dev_info(&hdev->pdev->dev, "reset done count: %u\n",
		 hdev->rst_stats.rst_करोne_cnt);
	dev_info(&hdev->pdev->dev, "HW reset done count: %u\n",
		 hdev->rst_stats.hw_rst_करोne_cnt);
	dev_info(&hdev->pdev->dev, "reset count: %u\n",
		 hdev->rst_stats.rst_cnt);
	dev_info(&hdev->pdev->dev, "reset fail count: %u\n",
		 hdev->rst_stats.rst_fail_cnt);
	dev_info(&hdev->pdev->dev, "vector0 interrupt enable status: 0x%x\n",
		 hclgevf_पढ़ो_dev(&hdev->hw, HCLGEVF_MISC_VECTOR_REG_BASE));
	dev_info(&hdev->pdev->dev, "vector0 interrupt status: 0x%x\n",
		 hclgevf_पढ़ो_dev(&hdev->hw, HCLGEVF_VECTOR0_CMDQ_STATE_REG));
	dev_info(&hdev->pdev->dev, "handshake status: 0x%x\n",
		 hclgevf_पढ़ो_dev(&hdev->hw, HCLGEVF_CMDQ_TX_DEPTH_REG));
	dev_info(&hdev->pdev->dev, "function reset status: 0x%x\n",
		 hclgevf_पढ़ो_dev(&hdev->hw, HCLGEVF_RST_ING));
	dev_info(&hdev->pdev->dev, "hdev state: 0x%lx\n", hdev->state);
पूर्ण

अटल व्योम hclgevf_reset_err_handle(काष्ठा hclgevf_dev *hdev)
अणु
	/* recover handshake status with IMP when reset fail */
	hclgevf_reset_handshake(hdev, true);
	hdev->rst_stats.rst_fail_cnt++;
	dev_err(&hdev->pdev->dev, "failed to reset VF(%u)\n",
		hdev->rst_stats.rst_fail_cnt);

	अगर (hdev->rst_stats.rst_fail_cnt < HCLGEVF_RESET_MAX_FAIL_CNT)
		set_bit(hdev->reset_type, &hdev->reset_pending);

	अगर (hclgevf_is_reset_pending(hdev)) अणु
		set_bit(HCLGEVF_RESET_PENDING, &hdev->reset_state);
		hclgevf_reset_task_schedule(hdev);
	पूर्ण अन्यथा अणु
		set_bit(HCLGEVF_STATE_RST_FAIL, &hdev->state);
		hclgevf_dump_rst_info(hdev);
	पूर्ण
पूर्ण

अटल पूर्णांक hclgevf_reset_prepare(काष्ठा hclgevf_dev *hdev)
अणु
	पूर्णांक ret;

	hdev->rst_stats.rst_cnt++;

	/* perक्रमm reset of the stack & ae device क्रम a client */
	ret = hclgevf_notअगरy_roce_client(hdev, HNAE3_DOWN_CLIENT);
	अगर (ret)
		वापस ret;

	rtnl_lock();
	/* bring करोwn the nic to stop any ongoing TX/RX */
	ret = hclgevf_notअगरy_client(hdev, HNAE3_DOWN_CLIENT);
	rtnl_unlock();
	अगर (ret)
		वापस ret;

	वापस hclgevf_reset_prepare_रुको(hdev);
पूर्ण

अटल पूर्णांक hclgevf_reset_rebuild(काष्ठा hclgevf_dev *hdev)
अणु
	पूर्णांक ret;

	hdev->rst_stats.hw_rst_करोne_cnt++;
	ret = hclgevf_notअगरy_roce_client(hdev, HNAE3_UNINIT_CLIENT);
	अगर (ret)
		वापस ret;

	rtnl_lock();
	/* now, re-initialize the nic client and ae device */
	ret = hclgevf_reset_stack(hdev);
	rtnl_unlock();
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "failed to reset VF stack\n");
		वापस ret;
	पूर्ण

	ret = hclgevf_notअगरy_roce_client(hdev, HNAE3_INIT_CLIENT);
	/* ignore RoCE notअगरy error अगर it fails HCLGEVF_RESET_MAX_FAIL_CNT - 1
	 * बार
	 */
	अगर (ret &&
	    hdev->rst_stats.rst_fail_cnt < HCLGEVF_RESET_MAX_FAIL_CNT - 1)
		वापस ret;

	ret = hclgevf_notअगरy_roce_client(hdev, HNAE3_UP_CLIENT);
	अगर (ret)
		वापस ret;

	hdev->last_reset_समय = jअगरfies;
	hdev->rst_stats.rst_करोne_cnt++;
	hdev->rst_stats.rst_fail_cnt = 0;
	clear_bit(HCLGEVF_STATE_RST_FAIL, &hdev->state);

	वापस 0;
पूर्ण

अटल व्योम hclgevf_reset(काष्ठा hclgevf_dev *hdev)
अणु
	अगर (hclgevf_reset_prepare(hdev))
		जाओ err_reset;

	/* check अगर VF could successfully fetch the hardware reset completion
	 * status from the hardware
	 */
	अगर (hclgevf_reset_रुको(hdev)) अणु
		/* can't करो much in this situation, will disable VF */
		dev_err(&hdev->pdev->dev,
			"failed to fetch H/W reset completion status\n");
		जाओ err_reset;
	पूर्ण

	अगर (hclgevf_reset_rebuild(hdev))
		जाओ err_reset;

	वापस;

err_reset:
	hclgevf_reset_err_handle(hdev);
पूर्ण

अटल क्रमागत hnae3_reset_type hclgevf_get_reset_level(काष्ठा hclgevf_dev *hdev,
						     अचिन्हित दीर्घ *addr)
अणु
	क्रमागत hnae3_reset_type rst_level = HNAE3_NONE_RESET;

	/* वापस the highest priority reset level amongst all */
	अगर (test_bit(HNAE3_VF_RESET, addr)) अणु
		rst_level = HNAE3_VF_RESET;
		clear_bit(HNAE3_VF_RESET, addr);
		clear_bit(HNAE3_VF_PF_FUNC_RESET, addr);
		clear_bit(HNAE3_VF_FUNC_RESET, addr);
	पूर्ण अन्यथा अगर (test_bit(HNAE3_VF_FULL_RESET, addr)) अणु
		rst_level = HNAE3_VF_FULL_RESET;
		clear_bit(HNAE3_VF_FULL_RESET, addr);
		clear_bit(HNAE3_VF_FUNC_RESET, addr);
	पूर्ण अन्यथा अगर (test_bit(HNAE3_VF_PF_FUNC_RESET, addr)) अणु
		rst_level = HNAE3_VF_PF_FUNC_RESET;
		clear_bit(HNAE3_VF_PF_FUNC_RESET, addr);
		clear_bit(HNAE3_VF_FUNC_RESET, addr);
	पूर्ण अन्यथा अगर (test_bit(HNAE3_VF_FUNC_RESET, addr)) अणु
		rst_level = HNAE3_VF_FUNC_RESET;
		clear_bit(HNAE3_VF_FUNC_RESET, addr);
	पूर्ण अन्यथा अगर (test_bit(HNAE3_FLR_RESET, addr)) अणु
		rst_level = HNAE3_FLR_RESET;
		clear_bit(HNAE3_FLR_RESET, addr);
	पूर्ण

	वापस rst_level;
पूर्ण

अटल व्योम hclgevf_reset_event(काष्ठा pci_dev *pdev,
				काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);
	काष्ठा hclgevf_dev *hdev = ae_dev->priv;

	dev_info(&hdev->pdev->dev, "received reset request from VF enet\n");

	अगर (hdev->शेष_reset_request)
		hdev->reset_level =
			hclgevf_get_reset_level(hdev,
						&hdev->शेष_reset_request);
	अन्यथा
		hdev->reset_level = HNAE3_VF_FUNC_RESET;

	/* reset of this VF requested */
	set_bit(HCLGEVF_RESET_REQUESTED, &hdev->reset_state);
	hclgevf_reset_task_schedule(hdev);

	hdev->last_reset_समय = jअगरfies;
पूर्ण

अटल व्योम hclgevf_set_def_reset_request(काष्ठा hnae3_ae_dev *ae_dev,
					  क्रमागत hnae3_reset_type rst_type)
अणु
	काष्ठा hclgevf_dev *hdev = ae_dev->priv;

	set_bit(rst_type, &hdev->शेष_reset_request);
पूर्ण

अटल व्योम hclgevf_enable_vector(काष्ठा hclgevf_misc_vector *vector, bool en)
अणु
	ग_लिखोl(en ? 1 : 0, vector->addr);
पूर्ण

अटल व्योम hclgevf_reset_prepare_general(काष्ठा hnae3_ae_dev *ae_dev,
					  क्रमागत hnae3_reset_type rst_type)
अणु
#घोषणा HCLGEVF_RESET_RETRY_WAIT_MS	500
#घोषणा HCLGEVF_RESET_RETRY_CNT		5

	काष्ठा hclgevf_dev *hdev = ae_dev->priv;
	पूर्णांक retry_cnt = 0;
	पूर्णांक ret;

retry:
	करोwn(&hdev->reset_sem);
	set_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state);
	hdev->reset_type = rst_type;
	ret = hclgevf_reset_prepare(hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "fail to prepare to reset, ret=%d\n",
			ret);
		अगर (hdev->reset_pending ||
		    retry_cnt++ < HCLGEVF_RESET_RETRY_CNT) अणु
			dev_err(&hdev->pdev->dev,
				"reset_pending:0x%lx, retry_cnt:%d\n",
				hdev->reset_pending, retry_cnt);
			clear_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state);
			up(&hdev->reset_sem);
			msleep(HCLGEVF_RESET_RETRY_WAIT_MS);
			जाओ retry;
		पूर्ण
	पूर्ण

	/* disable misc vector beक्रमe reset करोne */
	hclgevf_enable_vector(&hdev->misc_vector, false);

	अगर (hdev->reset_type == HNAE3_FLR_RESET)
		hdev->rst_stats.flr_rst_cnt++;
पूर्ण

अटल व्योम hclgevf_reset_करोne(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclgevf_dev *hdev = ae_dev->priv;
	पूर्णांक ret;

	hclgevf_enable_vector(&hdev->misc_vector, true);

	ret = hclgevf_reset_rebuild(hdev);
	अगर (ret)
		dev_warn(&hdev->pdev->dev, "fail to rebuild, ret=%d\n",
			 ret);

	hdev->reset_type = HNAE3_NONE_RESET;
	clear_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state);
	up(&hdev->reset_sem);
पूर्ण

अटल u32 hclgevf_get_fw_version(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	वापस hdev->fw_version;
पूर्ण

अटल व्योम hclgevf_get_misc_vector(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclgevf_misc_vector *vector = &hdev->misc_vector;

	vector->vector_irq = pci_irq_vector(hdev->pdev,
					    HCLGEVF_MISC_VECTOR_NUM);
	vector->addr = hdev->hw.io_base + HCLGEVF_MISC_VECTOR_REG_BASE;
	/* vector status always valid क्रम Vector 0 */
	hdev->vector_status[HCLGEVF_MISC_VECTOR_NUM] = 0;
	hdev->vector_irq[HCLGEVF_MISC_VECTOR_NUM] = vector->vector_irq;

	hdev->num_msi_left -= 1;
	hdev->num_msi_used += 1;
पूर्ण

व्योम hclgevf_reset_task_schedule(काष्ठा hclgevf_dev *hdev)
अणु
	अगर (!test_bit(HCLGEVF_STATE_REMOVING, &hdev->state) &&
	    !test_and_set_bit(HCLGEVF_STATE_RST_SERVICE_SCHED,
			      &hdev->state))
		mod_delayed_work(hclgevf_wq, &hdev->service_task, 0);
पूर्ण

व्योम hclgevf_mbx_task_schedule(काष्ठा hclgevf_dev *hdev)
अणु
	अगर (!test_bit(HCLGEVF_STATE_REMOVING, &hdev->state) &&
	    !test_and_set_bit(HCLGEVF_STATE_MBX_SERVICE_SCHED,
			      &hdev->state))
		mod_delayed_work(hclgevf_wq, &hdev->service_task, 0);
पूर्ण

अटल व्योम hclgevf_task_schedule(काष्ठा hclgevf_dev *hdev,
				  अचिन्हित दीर्घ delay)
अणु
	अगर (!test_bit(HCLGEVF_STATE_REMOVING, &hdev->state) &&
	    !test_bit(HCLGEVF_STATE_RST_FAIL, &hdev->state))
		mod_delayed_work(hclgevf_wq, &hdev->service_task, delay);
पूर्ण

अटल व्योम hclgevf_reset_service_task(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा	HCLGEVF_MAX_RESET_ATTEMPTS_CNT	3

	अगर (!test_and_clear_bit(HCLGEVF_STATE_RST_SERVICE_SCHED, &hdev->state))
		वापस;

	करोwn(&hdev->reset_sem);
	set_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state);

	अगर (test_and_clear_bit(HCLGEVF_RESET_PENDING,
			       &hdev->reset_state)) अणु
		/* PF has पूर्णांकimated that it is about to reset the hardware.
		 * We now have to poll & check अगर hardware has actually
		 * completed the reset sequence. On hardware reset completion,
		 * VF needs to reset the client and ae device.
		 */
		hdev->reset_attempts = 0;

		hdev->last_reset_समय = jअगरfies;
		जबतक ((hdev->reset_type =
			hclgevf_get_reset_level(hdev, &hdev->reset_pending))
		       != HNAE3_NONE_RESET)
			hclgevf_reset(hdev);
	पूर्ण अन्यथा अगर (test_and_clear_bit(HCLGEVF_RESET_REQUESTED,
				      &hdev->reset_state)) अणु
		/* we could be here when either of below happens:
		 * 1. reset was initiated due to watchकरोg समयout caused by
		 *    a. IMP was earlier reset and our TX got choked करोwn and
		 *       which resulted in watchकरोg reacting and inducing VF
		 *       reset. This also means our cmdq would be unreliable.
		 *    b. problem in TX due to other lower layer(example link
		 *       layer not functioning properly etc.)
		 * 2. VF reset might have been initiated due to some config
		 *    change.
		 *
		 * NOTE: Theres no clear way to detect above हालs than to react
		 * to the response of PF क्रम this reset request. PF will ack the
		 * 1b and 2. हालs but we will not get any पूर्णांकimation about 1a
		 * from PF as cmdq would be in unreliable state i.e. mailbox
		 * communication between PF and VF would be broken.
		 *
		 * अगर we are never geting पूर्णांकo pending state it means either:
		 * 1. PF is not receiving our request which could be due to IMP
		 *    reset
		 * 2. PF is screwed
		 * We cannot करो much क्रम 2. but to check first we can try reset
		 * our PCIe + stack and see अगर it alleviates the problem.
		 */
		अगर (hdev->reset_attempts > HCLGEVF_MAX_RESET_ATTEMPTS_CNT) अणु
			/* prepare क्रम full reset of stack + pcie पूर्णांकerface */
			set_bit(HNAE3_VF_FULL_RESET, &hdev->reset_pending);

			/* "defer" schedule the reset task again */
			set_bit(HCLGEVF_RESET_PENDING, &hdev->reset_state);
		पूर्ण अन्यथा अणु
			hdev->reset_attempts++;

			set_bit(hdev->reset_level, &hdev->reset_pending);
			set_bit(HCLGEVF_RESET_PENDING, &hdev->reset_state);
		पूर्ण
		hclgevf_reset_task_schedule(hdev);
	पूर्ण

	hdev->reset_type = HNAE3_NONE_RESET;
	clear_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state);
	up(&hdev->reset_sem);
पूर्ण

अटल व्योम hclgevf_mailbox_service_task(काष्ठा hclgevf_dev *hdev)
अणु
	अगर (!test_and_clear_bit(HCLGEVF_STATE_MBX_SERVICE_SCHED, &hdev->state))
		वापस;

	अगर (test_and_set_bit(HCLGEVF_STATE_MBX_HANDLING, &hdev->state))
		वापस;

	hclgevf_mbx_async_handler(hdev);

	clear_bit(HCLGEVF_STATE_MBX_HANDLING, &hdev->state);
पूर्ण

अटल व्योम hclgevf_keep_alive(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclge_vf_to_pf_msg send_msg;
	पूर्णांक ret;

	अगर (test_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state))
		वापस;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_KEEP_ALIVE, 0);
	ret = hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"VF sends keep alive cmd failed(=%d)\n", ret);
पूर्ण

अटल व्योम hclgevf_periodic_service_task(काष्ठा hclgevf_dev *hdev)
अणु
	अचिन्हित दीर्घ delta = round_jअगरfies_relative(HZ);
	काष्ठा hnae3_handle *handle = &hdev->nic;

	अगर (test_bit(HCLGEVF_STATE_RST_FAIL, &hdev->state))
		वापस;

	अगर (समय_is_after_jअगरfies(hdev->last_serv_processed + HZ)) अणु
		delta = jअगरfies - hdev->last_serv_processed;

		अगर (delta < round_jअगरfies_relative(HZ)) अणु
			delta = round_jअगरfies_relative(HZ) - delta;
			जाओ out;
		पूर्ण
	पूर्ण

	hdev->serv_processed_cnt++;
	अगर (!(hdev->serv_processed_cnt % HCLGEVF_KEEP_ALIVE_TASK_INTERVAL))
		hclgevf_keep_alive(hdev);

	अगर (test_bit(HCLGEVF_STATE_DOWN, &hdev->state)) अणु
		hdev->last_serv_processed = jअगरfies;
		जाओ out;
	पूर्ण

	अगर (!(hdev->serv_processed_cnt % HCLGEVF_STATS_TIMER_INTERVAL))
		hclgevf_tqps_update_stats(handle);

	/* VF करोes not need to request link status when this bit is set, because
	 * PF will push its link status to VFs when link status changed.
	 */
	अगर (!test_bit(HCLGEVF_STATE_PF_PUSH_LINK_STATUS, &hdev->state))
		hclgevf_request_link_info(hdev);

	hclgevf_update_link_mode(hdev);

	hclgevf_sync_vlan_filter(hdev);

	hclgevf_sync_mac_table(hdev);

	hclgevf_sync_promisc_mode(hdev);

	hdev->last_serv_processed = jअगरfies;

out:
	hclgevf_task_schedule(hdev, delta);
पूर्ण

अटल व्योम hclgevf_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hclgevf_dev *hdev = container_of(work, काष्ठा hclgevf_dev,
						service_task.work);

	hclgevf_reset_service_task(hdev);
	hclgevf_mailbox_service_task(hdev);
	hclgevf_periodic_service_task(hdev);

	/* Handle reset and mbx again in हाल periodical task delays the
	 * handling by calling hclgevf_task_schedule() in
	 * hclgevf_periodic_service_task()
	 */
	hclgevf_reset_service_task(hdev);
	hclgevf_mailbox_service_task(hdev);
पूर्ण

अटल व्योम hclgevf_clear_event_cause(काष्ठा hclgevf_dev *hdev, u32 regclr)
अणु
	hclgevf_ग_लिखो_dev(&hdev->hw, HCLGEVF_VECTOR0_CMDQ_SRC_REG, regclr);
पूर्ण

अटल क्रमागत hclgevf_evt_cause hclgevf_check_evt_cause(काष्ठा hclgevf_dev *hdev,
						      u32 *clearval)
अणु
	u32 val, cmdq_stat_reg, rst_ing_reg;

	/* fetch the events from their corresponding regs */
	cmdq_stat_reg = hclgevf_पढ़ो_dev(&hdev->hw,
					 HCLGEVF_VECTOR0_CMDQ_STATE_REG);
	अगर (BIT(HCLGEVF_VECTOR0_RST_INT_B) & cmdq_stat_reg) अणु
		rst_ing_reg = hclgevf_पढ़ो_dev(&hdev->hw, HCLGEVF_RST_ING);
		dev_info(&hdev->pdev->dev,
			 "receive reset interrupt 0x%x!\n", rst_ing_reg);
		set_bit(HNAE3_VF_RESET, &hdev->reset_pending);
		set_bit(HCLGEVF_RESET_PENDING, &hdev->reset_state);
		set_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state);
		*clearval = ~(1U << HCLGEVF_VECTOR0_RST_INT_B);
		hdev->rst_stats.vf_rst_cnt++;
		/* set up VF hardware reset status, its PF will clear
		 * this status when PF has initialized करोne.
		 */
		val = hclgevf_पढ़ो_dev(&hdev->hw, HCLGEVF_VF_RST_ING);
		hclgevf_ग_लिखो_dev(&hdev->hw, HCLGEVF_VF_RST_ING,
				  val | HCLGEVF_VF_RST_ING_BIT);
		वापस HCLGEVF_VECTOR0_EVENT_RST;
	पूर्ण

	/* check क्रम vector0 mailbox(=CMDQ RX) event source */
	अगर (BIT(HCLGEVF_VECTOR0_RX_CMDQ_INT_B) & cmdq_stat_reg) अणु
		/* क्रम revision 0x21, clearing पूर्णांकerrupt is writing bit 0
		 * to the clear रेजिस्टर, writing bit 1 means to keep the
		 * old value.
		 * क्रम revision 0x20, the clear रेजिस्टर is a पढ़ो & ग_लिखो
		 * रेजिस्टर, so we should just ग_लिखो 0 to the bit we are
		 * handling, and keep other bits as cmdq_stat_reg.
		 */
		अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2)
			*clearval = ~(1U << HCLGEVF_VECTOR0_RX_CMDQ_INT_B);
		अन्यथा
			*clearval = cmdq_stat_reg &
				    ~BIT(HCLGEVF_VECTOR0_RX_CMDQ_INT_B);

		वापस HCLGEVF_VECTOR0_EVENT_MBX;
	पूर्ण

	/* prपूर्णांक other vector0 event source */
	dev_info(&hdev->pdev->dev,
		 "vector 0 interrupt from unknown source, cmdq_src = %#x\n",
		 cmdq_stat_reg);

	वापस HCLGEVF_VECTOR0_EVENT_OTHER;
पूर्ण

अटल irqवापस_t hclgevf_misc_irq_handle(पूर्णांक irq, व्योम *data)
अणु
	क्रमागत hclgevf_evt_cause event_cause;
	काष्ठा hclgevf_dev *hdev = data;
	u32 clearval;

	hclgevf_enable_vector(&hdev->misc_vector, false);
	event_cause = hclgevf_check_evt_cause(hdev, &clearval);

	चयन (event_cause) अणु
	हाल HCLGEVF_VECTOR0_EVENT_RST:
		hclgevf_reset_task_schedule(hdev);
		अवरोध;
	हाल HCLGEVF_VECTOR0_EVENT_MBX:
		hclgevf_mbx_handler(hdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (event_cause != HCLGEVF_VECTOR0_EVENT_OTHER) अणु
		hclgevf_clear_event_cause(hdev, clearval);
		hclgevf_enable_vector(&hdev->misc_vector, true);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hclgevf_configure(काष्ठा hclgevf_dev *hdev)
अणु
	पूर्णांक ret;

	/* get current port based vlan state from PF */
	ret = hclgevf_get_port_base_vlan_filter_state(hdev);
	अगर (ret)
		वापस ret;

	/* get queue configuration from PF */
	ret = hclgevf_get_queue_info(hdev);
	अगर (ret)
		वापस ret;

	/* get queue depth info from PF */
	ret = hclgevf_get_queue_depth(hdev);
	अगर (ret)
		वापस ret;

	ret = hclgevf_get_pf_media_type(hdev);
	अगर (ret)
		वापस ret;

	/* get tc configuration from PF */
	वापस hclgevf_get_tc_info(hdev);
पूर्ण

अटल पूर्णांक hclgevf_alloc_hdev(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा pci_dev *pdev = ae_dev->pdev;
	काष्ठा hclgevf_dev *hdev;

	hdev = devm_kzalloc(&pdev->dev, माप(*hdev), GFP_KERNEL);
	अगर (!hdev)
		वापस -ENOMEM;

	hdev->pdev = pdev;
	hdev->ae_dev = ae_dev;
	ae_dev->priv = hdev;

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_init_roce_base_info(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hnae3_handle *roce = &hdev->roce;
	काष्ठा hnae3_handle *nic = &hdev->nic;

	roce->rinfo.num_vectors = hdev->num_roce_msix;

	अगर (hdev->num_msi_left < roce->rinfo.num_vectors ||
	    hdev->num_msi_left == 0)
		वापस -EINVAL;

	roce->rinfo.base_vector = hdev->roce_base_vector;

	roce->rinfo.netdev = nic->kinfo.netdev;
	roce->rinfo.roce_io_base = hdev->hw.io_base;
	roce->rinfo.roce_mem_base = hdev->hw.mem_base;

	roce->pdev = nic->pdev;
	roce->ae_algo = nic->ae_algo;
	roce->numa_node_mask = nic->numa_node_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_config_gro(काष्ठा hclgevf_dev *hdev, bool en)
अणु
	काष्ठा hclgevf_cfg_gro_status_cmd *req;
	काष्ठा hclgevf_desc desc;
	पूर्णांक ret;

	अगर (!hnae3_dev_gro_supported(hdev))
		वापस 0;

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_GRO_GENERIC_CONFIG,
				     false);
	req = (काष्ठा hclgevf_cfg_gro_status_cmd *)desc.data;

	req->gro_en = en ? 1 : 0;

	ret = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		dev_err(&hdev->pdev->dev,
			"VF GRO hardware config cmd failed, ret = %d.\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hclgevf_rss_init_cfg(काष्ठा hclgevf_dev *hdev)
अणु
	u16 rss_ind_tbl_size = hdev->ae_dev->dev_specs.rss_ind_tbl_size;
	काष्ठा hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	काष्ठा hclgevf_rss_tuple_cfg *tuple_sets;
	u32 i;

	rss_cfg->hash_algo = HCLGEVF_RSS_HASH_ALGO_TOEPLITZ;
	rss_cfg->rss_size = hdev->nic.kinfo.rss_size;
	tuple_sets = &rss_cfg->rss_tuple_sets;
	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2) अणु
		u8 *rss_ind_tbl;

		rss_cfg->hash_algo = HCLGEVF_RSS_HASH_ALGO_SIMPLE;

		rss_ind_tbl = devm_kसुस्मृति(&hdev->pdev->dev, rss_ind_tbl_size,
					   माप(*rss_ind_tbl), GFP_KERNEL);
		अगर (!rss_ind_tbl)
			वापस -ENOMEM;

		rss_cfg->rss_indirection_tbl = rss_ind_tbl;
		स_नकल(rss_cfg->rss_hash_key, hclgevf_hash_key,
		       HCLGEVF_RSS_KEY_SIZE);

		tuple_sets->ipv4_tcp_en = HCLGEVF_RSS_INPUT_TUPLE_OTHER;
		tuple_sets->ipv4_udp_en = HCLGEVF_RSS_INPUT_TUPLE_OTHER;
		tuple_sets->ipv4_sctp_en = HCLGEVF_RSS_INPUT_TUPLE_SCTP;
		tuple_sets->ipv4_fragment_en = HCLGEVF_RSS_INPUT_TUPLE_OTHER;
		tuple_sets->ipv6_tcp_en = HCLGEVF_RSS_INPUT_TUPLE_OTHER;
		tuple_sets->ipv6_udp_en = HCLGEVF_RSS_INPUT_TUPLE_OTHER;
		tuple_sets->ipv6_sctp_en =
			hdev->ae_dev->dev_version <= HNAE3_DEVICE_VERSION_V2 ?
					HCLGEVF_RSS_INPUT_TUPLE_SCTP_NO_PORT :
					HCLGEVF_RSS_INPUT_TUPLE_SCTP;
		tuple_sets->ipv6_fragment_en = HCLGEVF_RSS_INPUT_TUPLE_OTHER;
	पूर्ण

	/* Initialize RSS indirect table */
	क्रम (i = 0; i < rss_ind_tbl_size; i++)
		rss_cfg->rss_indirection_tbl[i] = i % rss_cfg->rss_size;

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_rss_init_hw(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	पूर्णांक ret;

	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2) अणु
		ret = hclgevf_set_rss_algo_key(hdev, rss_cfg->hash_algo,
					       rss_cfg->rss_hash_key);
		अगर (ret)
			वापस ret;

		ret = hclgevf_set_rss_input_tuple(hdev, rss_cfg);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hclgevf_set_rss_indir_table(hdev);
	अगर (ret)
		वापस ret;

	वापस hclgevf_set_rss_tc_mode(hdev, rss_cfg->rss_size);
पूर्ण

अटल पूर्णांक hclgevf_init_vlan_config(काष्ठा hclgevf_dev *hdev)
अणु
	वापस hclgevf_set_vlan_filter(&hdev->nic, htons(ETH_P_8021Q), 0,
				       false);
पूर्ण

अटल व्योम hclgevf_flush_link_update(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा HCLGEVF_FLUSH_LINK_TIMEOUT	100000

	अचिन्हित दीर्घ last = hdev->serv_processed_cnt;
	पूर्णांक i = 0;

	जबतक (test_bit(HCLGEVF_STATE_LINK_UPDATING, &hdev->state) &&
	       i++ < HCLGEVF_FLUSH_LINK_TIMEOUT &&
	       last == hdev->serv_processed_cnt)
		usleep_range(1, 1);
पूर्ण

अटल व्योम hclgevf_set_समयr_task(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	अगर (enable) अणु
		hclgevf_task_schedule(hdev, 0);
	पूर्ण अन्यथा अणु
		set_bit(HCLGEVF_STATE_DOWN, &hdev->state);

		/* flush memory to make sure DOWN is seen by service task */
		smp_mb__beक्रमe_atomic();
		hclgevf_flush_link_update(hdev);
	पूर्ण
पूर्ण

अटल पूर्णांक hclgevf_ae_start(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	clear_bit(HCLGEVF_STATE_DOWN, &hdev->state);
	clear_bit(HCLGEVF_STATE_PF_PUSH_LINK_STATUS, &hdev->state);

	hclgevf_reset_tqp_stats(handle);

	hclgevf_request_link_info(hdev);

	hclgevf_update_link_mode(hdev);

	वापस 0;
पूर्ण

अटल व्योम hclgevf_ae_stop(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	set_bit(HCLGEVF_STATE_DOWN, &hdev->state);

	अगर (hdev->reset_type != HNAE3_VF_RESET)
		hclgevf_reset_tqp(handle);

	hclgevf_reset_tqp_stats(handle);
	hclgevf_update_link_status(hdev, 0);
पूर्ण

अटल पूर्णांक hclgevf_set_alive(काष्ठा hnae3_handle *handle, bool alive)
अणु
#घोषणा HCLGEVF_STATE_ALIVE	1
#घोषणा HCLGEVF_STATE_NOT_ALIVE	0

	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hclge_vf_to_pf_msg send_msg;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_SET_ALIVE, 0);
	send_msg.data[0] = alive ? HCLGEVF_STATE_ALIVE :
				HCLGEVF_STATE_NOT_ALIVE;
	वापस hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);
पूर्ण

अटल पूर्णांक hclgevf_client_start(काष्ठा hnae3_handle *handle)
अणु
	वापस hclgevf_set_alive(handle, true);
पूर्ण

अटल व्योम hclgevf_client_stop(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	पूर्णांक ret;

	ret = hclgevf_set_alive(handle, false);
	अगर (ret)
		dev_warn(&hdev->pdev->dev,
			 "%s failed %d\n", __func__, ret);
पूर्ण

अटल व्योम hclgevf_state_init(काष्ठा hclgevf_dev *hdev)
अणु
	clear_bit(HCLGEVF_STATE_MBX_SERVICE_SCHED, &hdev->state);
	clear_bit(HCLGEVF_STATE_MBX_HANDLING, &hdev->state);
	clear_bit(HCLGEVF_STATE_RST_FAIL, &hdev->state);

	INIT_DELAYED_WORK(&hdev->service_task, hclgevf_service_task);

	mutex_init(&hdev->mbx_resp.mbx_mutex);
	sema_init(&hdev->reset_sem, 1);

	spin_lock_init(&hdev->mac_table.mac_list_lock);
	INIT_LIST_HEAD(&hdev->mac_table.uc_mac_list);
	INIT_LIST_HEAD(&hdev->mac_table.mc_mac_list);

	/* bring the device करोwn */
	set_bit(HCLGEVF_STATE_DOWN, &hdev->state);
पूर्ण

अटल व्योम hclgevf_state_uninit(काष्ठा hclgevf_dev *hdev)
अणु
	set_bit(HCLGEVF_STATE_DOWN, &hdev->state);
	set_bit(HCLGEVF_STATE_REMOVING, &hdev->state);

	अगर (hdev->service_task.work.func)
		cancel_delayed_work_sync(&hdev->service_task);

	mutex_destroy(&hdev->mbx_resp.mbx_mutex);
पूर्ण

अटल पूर्णांक hclgevf_init_msi(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	पूर्णांक vectors;
	पूर्णांक i;

	अगर (hnae3_dev_roce_supported(hdev))
		vectors = pci_alloc_irq_vectors(pdev,
						hdev->roce_base_msix_offset + 1,
						hdev->num_msi,
						PCI_IRQ_MSIX);
	अन्यथा
		vectors = pci_alloc_irq_vectors(pdev, HNAE3_MIN_VECTOR_NUM,
						hdev->num_msi,
						PCI_IRQ_MSI | PCI_IRQ_MSIX);

	अगर (vectors < 0) अणु
		dev_err(&pdev->dev,
			"failed(%d) to allocate MSI/MSI-X vectors\n",
			vectors);
		वापस vectors;
	पूर्ण
	अगर (vectors < hdev->num_msi)
		dev_warn(&hdev->pdev->dev,
			 "requested %u MSI/MSI-X, but allocated %d MSI/MSI-X\n",
			 hdev->num_msi, vectors);

	hdev->num_msi = vectors;
	hdev->num_msi_left = vectors;

	hdev->base_msi_vector = pdev->irq;
	hdev->roce_base_vector = pdev->irq + hdev->roce_base_msix_offset;

	hdev->vector_status = devm_kसुस्मृति(&pdev->dev, hdev->num_msi,
					   माप(u16), GFP_KERNEL);
	अगर (!hdev->vector_status) अणु
		pci_मुक्त_irq_vectors(pdev);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < hdev->num_msi; i++)
		hdev->vector_status[i] = HCLGEVF_INVALID_VPORT;

	hdev->vector_irq = devm_kसुस्मृति(&pdev->dev, hdev->num_msi,
					माप(पूर्णांक), GFP_KERNEL);
	अगर (!hdev->vector_irq) अणु
		devm_kमुक्त(&pdev->dev, hdev->vector_status);
		pci_मुक्त_irq_vectors(pdev);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hclgevf_uninit_msi(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;

	devm_kमुक्त(&pdev->dev, hdev->vector_status);
	devm_kमुक्त(&pdev->dev, hdev->vector_irq);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल पूर्णांक hclgevf_misc_irq_init(काष्ठा hclgevf_dev *hdev)
अणु
	पूर्णांक ret;

	hclgevf_get_misc_vector(hdev);

	snम_लिखो(hdev->misc_vector.name, HNAE3_INT_NAME_LEN, "%s-misc-%s",
		 HCLGEVF_NAME, pci_name(hdev->pdev));
	ret = request_irq(hdev->misc_vector.vector_irq, hclgevf_misc_irq_handle,
			  0, hdev->misc_vector.name, hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "VF failed to request misc irq(%d)\n",
			hdev->misc_vector.vector_irq);
		वापस ret;
	पूर्ण

	hclgevf_clear_event_cause(hdev, 0);

	/* enable misc. vector(vector 0) */
	hclgevf_enable_vector(&hdev->misc_vector, true);

	वापस ret;
पूर्ण

अटल व्योम hclgevf_misc_irq_uninit(काष्ठा hclgevf_dev *hdev)
अणु
	/* disable misc vector(vector 0) */
	hclgevf_enable_vector(&hdev->misc_vector, false);
	synchronize_irq(hdev->misc_vector.vector_irq);
	मुक्त_irq(hdev->misc_vector.vector_irq, hdev);
	hclgevf_मुक्त_vector(hdev, 0);
पूर्ण

अटल व्योम hclgevf_info_show(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा device *dev = &hdev->pdev->dev;

	dev_info(dev, "VF info begin:\n");

	dev_info(dev, "Task queue pairs numbers: %u\n", hdev->num_tqps);
	dev_info(dev, "Desc num per TX queue: %u\n", hdev->num_tx_desc);
	dev_info(dev, "Desc num per RX queue: %u\n", hdev->num_rx_desc);
	dev_info(dev, "Numbers of vports: %u\n", hdev->num_alloc_vport);
	dev_info(dev, "HW tc map: 0x%x\n", hdev->hw_tc_map);
	dev_info(dev, "PF media type of this VF: %u\n",
		 hdev->hw.mac.media_type);

	dev_info(dev, "VF info end.\n");
पूर्ण

अटल पूर्णांक hclgevf_init_nic_client_instance(काष्ठा hnae3_ae_dev *ae_dev,
					    काष्ठा hnae3_client *client)
अणु
	काष्ठा hclgevf_dev *hdev = ae_dev->priv;
	पूर्णांक rst_cnt = hdev->rst_stats.rst_cnt;
	पूर्णांक ret;

	ret = client->ops->init_instance(&hdev->nic);
	अगर (ret)
		वापस ret;

	set_bit(HCLGEVF_STATE_NIC_REGISTERED, &hdev->state);
	अगर (test_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state) ||
	    rst_cnt != hdev->rst_stats.rst_cnt) अणु
		clear_bit(HCLGEVF_STATE_NIC_REGISTERED, &hdev->state);

		client->ops->uninit_instance(&hdev->nic, 0);
		वापस -EBUSY;
	पूर्ण

	hnae3_set_client_init_flag(client, ae_dev, 1);

	अगर (netअगर_msg_drv(&hdev->nic))
		hclgevf_info_show(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_init_roce_client_instance(काष्ठा hnae3_ae_dev *ae_dev,
					     काष्ठा hnae3_client *client)
अणु
	काष्ठा hclgevf_dev *hdev = ae_dev->priv;
	पूर्णांक ret;

	अगर (!hnae3_dev_roce_supported(hdev) || !hdev->roce_client ||
	    !hdev->nic_client)
		वापस 0;

	ret = hclgevf_init_roce_base_info(hdev);
	अगर (ret)
		वापस ret;

	ret = client->ops->init_instance(&hdev->roce);
	अगर (ret)
		वापस ret;

	set_bit(HCLGEVF_STATE_ROCE_REGISTERED, &hdev->state);
	hnae3_set_client_init_flag(client, ae_dev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_init_client_instance(काष्ठा hnae3_client *client,
					काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclgevf_dev *hdev = ae_dev->priv;
	पूर्णांक ret;

	चयन (client->type) अणु
	हाल HNAE3_CLIENT_KNIC:
		hdev->nic_client = client;
		hdev->nic.client = client;

		ret = hclgevf_init_nic_client_instance(ae_dev, client);
		अगर (ret)
			जाओ clear_nic;

		ret = hclgevf_init_roce_client_instance(ae_dev,
							hdev->roce_client);
		अगर (ret)
			जाओ clear_roce;

		अवरोध;
	हाल HNAE3_CLIENT_ROCE:
		अगर (hnae3_dev_roce_supported(hdev)) अणु
			hdev->roce_client = client;
			hdev->roce.client = client;
		पूर्ण

		ret = hclgevf_init_roce_client_instance(ae_dev, client);
		अगर (ret)
			जाओ clear_roce;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;

clear_nic:
	hdev->nic_client = शून्य;
	hdev->nic.client = शून्य;
	वापस ret;
clear_roce:
	hdev->roce_client = शून्य;
	hdev->roce.client = शून्य;
	वापस ret;
पूर्ण

अटल व्योम hclgevf_uninit_client_instance(काष्ठा hnae3_client *client,
					   काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclgevf_dev *hdev = ae_dev->priv;

	/* un-init roce, अगर it exists */
	अगर (hdev->roce_client) अणु
		clear_bit(HCLGEVF_STATE_ROCE_REGISTERED, &hdev->state);
		hdev->roce_client->ops->uninit_instance(&hdev->roce, 0);
		hdev->roce_client = शून्य;
		hdev->roce.client = शून्य;
	पूर्ण

	/* un-init nic/unic, अगर this was not called by roce client */
	अगर (client->ops->uninit_instance && hdev->nic_client &&
	    client->type != HNAE3_CLIENT_ROCE) अणु
		clear_bit(HCLGEVF_STATE_NIC_REGISTERED, &hdev->state);

		client->ops->uninit_instance(&hdev->nic, 0);
		hdev->nic_client = शून्य;
		hdev->nic.client = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक hclgevf_dev_mem_map(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा HCLGEVF_MEM_BAR		4

	काष्ठा pci_dev *pdev = hdev->pdev;
	काष्ठा hclgevf_hw *hw = &hdev->hw;

	/* क्रम device करोes not have device memory, वापस directly */
	अगर (!(pci_select_bars(pdev, IORESOURCE_MEM) & BIT(HCLGEVF_MEM_BAR)))
		वापस 0;

	hw->mem_base = devm_ioremap_wc(&pdev->dev,
				       pci_resource_start(pdev,
							  HCLGEVF_MEM_BAR),
				       pci_resource_len(pdev, HCLGEVF_MEM_BAR));
	अगर (!hw->mem_base) अणु
		dev_err(&pdev->dev, "failed to map device memory\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_pci_init(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	काष्ठा hclgevf_hw *hw;
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable PCI device\n");
		वापस ret;
	पूर्ण

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't set consistent PCI DMA, exiting");
		जाओ err_disable_device;
	पूर्ण

	ret = pci_request_regions(pdev, HCLGEVF_DRIVER_NAME);
	अगर (ret) अणु
		dev_err(&pdev->dev, "PCI request regions failed %d\n", ret);
		जाओ err_disable_device;
	पूर्ण

	pci_set_master(pdev);
	hw = &hdev->hw;
	hw->hdev = hdev;
	hw->io_base = pci_iomap(pdev, 2, 0);
	अगर (!hw->io_base) अणु
		dev_err(&pdev->dev, "can't map configuration register space\n");
		ret = -ENOMEM;
		जाओ err_clr_master;
	पूर्ण

	ret = hclgevf_dev_mem_map(hdev);
	अगर (ret)
		जाओ err_unmap_io_base;

	वापस 0;

err_unmap_io_base:
	pci_iounmap(pdev, hdev->hw.io_base);
err_clr_master:
	pci_clear_master(pdev);
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);

	वापस ret;
पूर्ण

अटल व्योम hclgevf_pci_uninit(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;

	अगर (hdev->hw.mem_base)
		devm_iounmap(&pdev->dev, hdev->hw.mem_base);

	pci_iounmap(pdev, hdev->hw.io_base);
	pci_clear_master(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक hclgevf_query_vf_resource(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclgevf_query_res_cmd *req;
	काष्ठा hclgevf_desc desc;
	पूर्णांक ret;

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_QUERY_VF_RSRC, true);
	ret = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"query vf resource failed, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	req = (काष्ठा hclgevf_query_res_cmd *)desc.data;

	अगर (hnae3_dev_roce_supported(hdev)) अणु
		hdev->roce_base_msix_offset =
		hnae3_get_field(le16_to_cpu(req->msixcap_localid_ba_rocee),
				HCLGEVF_MSIX_OFT_ROCEE_M,
				HCLGEVF_MSIX_OFT_ROCEE_S);
		hdev->num_roce_msix =
		hnae3_get_field(le16_to_cpu(req->vf_पूर्णांकr_vector_number),
				HCLGEVF_VEC_NUM_M, HCLGEVF_VEC_NUM_S);

		/* nic's msix numbers is always equals to the roce's. */
		hdev->num_nic_msix = hdev->num_roce_msix;

		/* VF should have NIC vectors and Roce vectors, NIC vectors
		 * are queued beक्रमe Roce vectors. The offset is fixed to 64.
		 */
		hdev->num_msi = hdev->num_roce_msix +
				hdev->roce_base_msix_offset;
	पूर्ण अन्यथा अणु
		hdev->num_msi =
		hnae3_get_field(le16_to_cpu(req->vf_पूर्णांकr_vector_number),
				HCLGEVF_VEC_NUM_M, HCLGEVF_VEC_NUM_S);

		hdev->num_nic_msix = hdev->num_msi;
	पूर्ण

	अगर (hdev->num_nic_msix < HNAE3_MIN_VECTOR_NUM) अणु
		dev_err(&hdev->pdev->dev,
			"Just %u msi resources, not enough for vf(min:2).\n",
			hdev->num_nic_msix);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hclgevf_set_शेष_dev_specs(काष्ठा hclgevf_dev *hdev)
अणु
#घोषणा HCLGEVF_MAX_NON_TSO_BD_NUM			8U

	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);

	ae_dev->dev_specs.max_non_tso_bd_num =
					HCLGEVF_MAX_NON_TSO_BD_NUM;
	ae_dev->dev_specs.rss_ind_tbl_size = HCLGEVF_RSS_IND_TBL_SIZE;
	ae_dev->dev_specs.rss_key_size = HCLGEVF_RSS_KEY_SIZE;
	ae_dev->dev_specs.max_पूर्णांक_gl = HCLGEVF_DEF_MAX_INT_GL;
	ae_dev->dev_specs.max_frm_size = HCLGEVF_MAC_MAX_FRAME;
पूर्ण

अटल व्योम hclgevf_parse_dev_specs(काष्ठा hclgevf_dev *hdev,
				    काष्ठा hclgevf_desc *desc)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(hdev->pdev);
	काष्ठा hclgevf_dev_specs_0_cmd *req0;
	काष्ठा hclgevf_dev_specs_1_cmd *req1;

	req0 = (काष्ठा hclgevf_dev_specs_0_cmd *)desc[0].data;
	req1 = (काष्ठा hclgevf_dev_specs_1_cmd *)desc[1].data;

	ae_dev->dev_specs.max_non_tso_bd_num = req0->max_non_tso_bd_num;
	ae_dev->dev_specs.rss_ind_tbl_size =
					le16_to_cpu(req0->rss_ind_tbl_size);
	ae_dev->dev_specs.पूर्णांक_ql_max = le16_to_cpu(req0->पूर्णांक_ql_max);
	ae_dev->dev_specs.rss_key_size = le16_to_cpu(req0->rss_key_size);
	ae_dev->dev_specs.max_पूर्णांक_gl = le16_to_cpu(req1->max_पूर्णांक_gl);
	ae_dev->dev_specs.max_frm_size = le16_to_cpu(req1->max_frm_size);
पूर्ण

अटल व्योम hclgevf_check_dev_specs(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hnae3_dev_specs *dev_specs = &hdev->ae_dev->dev_specs;

	अगर (!dev_specs->max_non_tso_bd_num)
		dev_specs->max_non_tso_bd_num = HCLGEVF_MAX_NON_TSO_BD_NUM;
	अगर (!dev_specs->rss_ind_tbl_size)
		dev_specs->rss_ind_tbl_size = HCLGEVF_RSS_IND_TBL_SIZE;
	अगर (!dev_specs->rss_key_size)
		dev_specs->rss_key_size = HCLGEVF_RSS_KEY_SIZE;
	अगर (!dev_specs->max_पूर्णांक_gl)
		dev_specs->max_पूर्णांक_gl = HCLGEVF_DEF_MAX_INT_GL;
	अगर (!dev_specs->max_frm_size)
		dev_specs->max_frm_size = HCLGEVF_MAC_MAX_FRAME;
पूर्ण

अटल पूर्णांक hclgevf_query_dev_specs(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclgevf_desc desc[HCLGEVF_QUERY_DEV_SPECS_BD_NUM];
	पूर्णांक ret;
	पूर्णांक i;

	/* set शेष specअगरications as devices lower than version V3 करो not
	 * support querying specअगरications from firmware.
	 */
	अगर (hdev->ae_dev->dev_version < HNAE3_DEVICE_VERSION_V3) अणु
		hclgevf_set_शेष_dev_specs(hdev);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < HCLGEVF_QUERY_DEV_SPECS_BD_NUM - 1; i++) अणु
		hclgevf_cmd_setup_basic_desc(&desc[i],
					     HCLGEVF_OPC_QUERY_DEV_SPECS, true);
		desc[i].flag |= cpu_to_le16(HCLGEVF_CMD_FLAG_NEXT);
	पूर्ण
	hclgevf_cmd_setup_basic_desc(&desc[i], HCLGEVF_OPC_QUERY_DEV_SPECS,
				     true);

	ret = hclgevf_cmd_send(&hdev->hw, desc, HCLGEVF_QUERY_DEV_SPECS_BD_NUM);
	अगर (ret)
		वापस ret;

	hclgevf_parse_dev_specs(hdev, desc);
	hclgevf_check_dev_specs(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_pci_reset(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	पूर्णांक ret = 0;

	अगर (hdev->reset_type == HNAE3_VF_FULL_RESET &&
	    test_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state)) अणु
		hclgevf_misc_irq_uninit(hdev);
		hclgevf_uninit_msi(hdev);
		clear_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state);
	पूर्ण

	अगर (!test_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state)) अणु
		pci_set_master(pdev);
		ret = hclgevf_init_msi(hdev);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"failed(%d) to init MSI/MSI-X\n", ret);
			वापस ret;
		पूर्ण

		ret = hclgevf_misc_irq_init(hdev);
		अगर (ret) अणु
			hclgevf_uninit_msi(hdev);
			dev_err(&pdev->dev, "failed(%d) to init Misc IRQ(vector0)\n",
				ret);
			वापस ret;
		पूर्ण

		set_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hclgevf_clear_vport_list(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclge_vf_to_pf_msg send_msg;

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_HANDLE_VF_TBL,
			       HCLGE_MBX_VPORT_LIST_CLEAR);
	वापस hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);
पूर्ण

अटल पूर्णांक hclgevf_reset_hdev(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	पूर्णांक ret;

	ret = hclgevf_pci_reset(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pci reset failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclgevf_cmd_init(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cmd failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hclgevf_rss_init_hw(hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed(%d) to initialize RSS\n", ret);
		वापस ret;
	पूर्ण

	ret = hclgevf_config_gro(hdev, true);
	अगर (ret)
		वापस ret;

	ret = hclgevf_init_vlan_config(hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed(%d) to initialize VLAN config\n", ret);
		वापस ret;
	पूर्ण

	set_bit(HCLGEVF_STATE_PROMISC_CHANGED, &hdev->state);

	dev_info(&hdev->pdev->dev, "Reset done\n");

	वापस 0;
पूर्ण

अटल पूर्णांक hclgevf_init_hdev(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	पूर्णांक ret;

	ret = hclgevf_pci_init(hdev);
	अगर (ret)
		वापस ret;

	ret = hclgevf_cmd_queue_init(hdev);
	अगर (ret)
		जाओ err_cmd_queue_init;

	ret = hclgevf_cmd_init(hdev);
	अगर (ret)
		जाओ err_cmd_init;

	/* Get vf resource */
	ret = hclgevf_query_vf_resource(hdev);
	अगर (ret)
		जाओ err_cmd_init;

	ret = hclgevf_query_dev_specs(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to query dev specifications, ret = %d\n", ret);
		जाओ err_cmd_init;
	पूर्ण

	ret = hclgevf_init_msi(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed(%d) to init MSI/MSI-X\n", ret);
		जाओ err_cmd_init;
	पूर्ण

	hclgevf_state_init(hdev);
	hdev->reset_level = HNAE3_VF_FUNC_RESET;
	hdev->reset_type = HNAE3_NONE_RESET;

	ret = hclgevf_misc_irq_init(hdev);
	अगर (ret)
		जाओ err_misc_irq_init;

	set_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state);

	ret = hclgevf_configure(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed(%d) to fetch configuration\n", ret);
		जाओ err_config;
	पूर्ण

	ret = hclgevf_alloc_tqps(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed(%d) to allocate TQPs\n", ret);
		जाओ err_config;
	पूर्ण

	ret = hclgevf_set_handle_info(hdev);
	अगर (ret)
		जाओ err_config;

	ret = hclgevf_config_gro(hdev, true);
	अगर (ret)
		जाओ err_config;

	/* Initialize RSS क्रम this VF */
	ret = hclgevf_rss_init_cfg(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to init rss cfg, ret = %d\n", ret);
		जाओ err_config;
	पूर्ण

	ret = hclgevf_rss_init_hw(hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed(%d) to initialize RSS\n", ret);
		जाओ err_config;
	पूर्ण

	/* ensure vf tbl list as empty beक्रमe init*/
	ret = hclgevf_clear_vport_list(hdev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to clear tbl list configuration, ret = %d.\n",
			ret);
		जाओ err_config;
	पूर्ण

	ret = hclgevf_init_vlan_config(hdev);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed(%d) to initialize VLAN config\n", ret);
		जाओ err_config;
	पूर्ण

	hdev->last_reset_समय = jअगरfies;
	dev_info(&hdev->pdev->dev, "finished initializing %s driver\n",
		 HCLGEVF_DRIVER_NAME);

	hclgevf_task_schedule(hdev, round_jअगरfies_relative(HZ));

	वापस 0;

err_config:
	hclgevf_misc_irq_uninit(hdev);
err_misc_irq_init:
	hclgevf_state_uninit(hdev);
	hclgevf_uninit_msi(hdev);
err_cmd_init:
	hclgevf_cmd_uninit(hdev);
err_cmd_queue_init:
	hclgevf_pci_uninit(hdev);
	clear_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state);
	वापस ret;
पूर्ण

अटल व्योम hclgevf_uninit_hdev(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hclge_vf_to_pf_msg send_msg;

	hclgevf_state_uninit(hdev);

	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_VF_UNINIT, 0);
	hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);

	अगर (test_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state)) अणु
		hclgevf_misc_irq_uninit(hdev);
		hclgevf_uninit_msi(hdev);
	पूर्ण

	hclgevf_cmd_uninit(hdev);
	hclgevf_pci_uninit(hdev);
	hclgevf_uninit_mac_list(hdev);
पूर्ण

अटल पूर्णांक hclgevf_init_ae_dev(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा pci_dev *pdev = ae_dev->pdev;
	पूर्णांक ret;

	ret = hclgevf_alloc_hdev(ae_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "hclge device allocation failed\n");
		वापस ret;
	पूर्ण

	ret = hclgevf_init_hdev(ae_dev->priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "hclge device initialization failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hclgevf_uninit_ae_dev(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	काष्ठा hclgevf_dev *hdev = ae_dev->priv;

	hclgevf_uninit_hdev(hdev);
	ae_dev->priv = शून्य;
पूर्ण

अटल u32 hclgevf_get_max_channels(काष्ठा hclgevf_dev *hdev)
अणु
	काष्ठा hnae3_handle *nic = &hdev->nic;
	काष्ठा hnae3_knic_निजी_info *kinfo = &nic->kinfo;

	वापस min_t(u32, hdev->rss_size_max,
		     hdev->num_tqps / kinfo->tc_info.num_tc);
पूर्ण

/**
 * hclgevf_get_channels - Get the current channels enabled and max supported.
 * @handle: hardware inक्रमmation क्रम network पूर्णांकerface
 * @ch: ethtool channels काष्ठाure
 *
 * We करोn't support separate tx and rx queues as channels. The other count
 * represents how many queues are being used क्रम control. max_combined counts
 * how many queue pairs we can support. They may not be mapped 1 to 1 with
 * q_vectors since we support a lot more queue pairs than q_vectors.
 **/
अटल व्योम hclgevf_get_channels(काष्ठा hnae3_handle *handle,
				 काष्ठा ethtool_channels *ch)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	ch->max_combined = hclgevf_get_max_channels(hdev);
	ch->other_count = 0;
	ch->max_other = 0;
	ch->combined_count = handle->kinfo.rss_size;
पूर्ण

अटल व्योम hclgevf_get_tqps_and_rss_info(काष्ठा hnae3_handle *handle,
					  u16 *alloc_tqps, u16 *max_rss_size)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	*alloc_tqps = hdev->num_tqps;
	*max_rss_size = hdev->rss_size_max;
पूर्ण

अटल व्योम hclgevf_update_rss_size(काष्ठा hnae3_handle *handle,
				    u32 new_tqps_num)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	u16 max_rss_size;

	kinfo->req_rss_size = new_tqps_num;

	max_rss_size = min_t(u16, hdev->rss_size_max,
			     hdev->num_tqps / kinfo->tc_info.num_tc);

	/* Use the user's configuration when it is not larger than
	 * max_rss_size, otherwise, use the maximum specअगरication value.
	 */
	अगर (kinfo->req_rss_size != kinfo->rss_size && kinfo->req_rss_size &&
	    kinfo->req_rss_size <= max_rss_size)
		kinfo->rss_size = kinfo->req_rss_size;
	अन्यथा अगर (kinfo->rss_size > max_rss_size ||
		 (!kinfo->req_rss_size && kinfo->rss_size < max_rss_size))
		kinfo->rss_size = max_rss_size;

	kinfo->num_tqps = kinfo->tc_info.num_tc * kinfo->rss_size;
पूर्ण

अटल पूर्णांक hclgevf_set_channels(काष्ठा hnae3_handle *handle, u32 new_tqps_num,
				bool rxfh_configured)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	u16 cur_rss_size = kinfo->rss_size;
	u16 cur_tqps = kinfo->num_tqps;
	u32 *rss_indir;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	hclgevf_update_rss_size(handle, new_tqps_num);

	ret = hclgevf_set_rss_tc_mode(hdev, kinfo->rss_size);
	अगर (ret)
		वापस ret;

	/* RSS indirection table has been configured by user */
	अगर (rxfh_configured)
		जाओ out;

	/* Reinitializes the rss indirect table according to the new RSS size */
	rss_indir = kसुस्मृति(hdev->ae_dev->dev_specs.rss_ind_tbl_size,
			    माप(u32), GFP_KERNEL);
	अगर (!rss_indir)
		वापस -ENOMEM;

	क्रम (i = 0; i < hdev->ae_dev->dev_specs.rss_ind_tbl_size; i++)
		rss_indir[i] = i % kinfo->rss_size;

	hdev->rss_cfg.rss_size = kinfo->rss_size;

	ret = hclgevf_set_rss(handle, rss_indir, शून्य, 0);
	अगर (ret)
		dev_err(&hdev->pdev->dev, "set rss indir table fail, ret=%d\n",
			ret);

	kमुक्त(rss_indir);

out:
	अगर (!ret)
		dev_info(&hdev->pdev->dev,
			 "Channels changed, rss_size from %u to %u, tqps from %u to %u",
			 cur_rss_size, kinfo->rss_size,
			 cur_tqps, kinfo->rss_size * kinfo->tc_info.num_tc);

	वापस ret;
पूर्ण

अटल पूर्णांक hclgevf_get_status(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	वापस hdev->hw.mac.link;
पूर्ण

अटल व्योम hclgevf_get_ksettings_an_result(काष्ठा hnae3_handle *handle,
					    u8 *स्वतः_neg, u32 *speed,
					    u8 *duplex)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	अगर (speed)
		*speed = hdev->hw.mac.speed;
	अगर (duplex)
		*duplex = hdev->hw.mac.duplex;
	अगर (स्वतः_neg)
		*स्वतः_neg = AUTONEG_DISABLE;
पूर्ण

व्योम hclgevf_update_speed_duplex(काष्ठा hclgevf_dev *hdev, u32 speed,
				 u8 duplex)
अणु
	hdev->hw.mac.speed = speed;
	hdev->hw.mac.duplex = duplex;
पूर्ण

अटल पूर्णांक hclgevf_gro_en(काष्ठा hnae3_handle *handle, bool enable)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	वापस hclgevf_config_gro(hdev, enable);
पूर्ण

अटल व्योम hclgevf_get_media_type(काष्ठा hnae3_handle *handle, u8 *media_type,
				   u8 *module_type)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	अगर (media_type)
		*media_type = hdev->hw.mac.media_type;

	अगर (module_type)
		*module_type = hdev->hw.mac.module_type;
पूर्ण

अटल bool hclgevf_get_hw_reset_stat(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	वापस !!hclgevf_पढ़ो_dev(&hdev->hw, HCLGEVF_RST_ING);
पूर्ण

अटल bool hclgevf_get_cmdq_stat(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	वापस test_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state);
पूर्ण

अटल bool hclgevf_ae_dev_resetting(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	वापस test_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state);
पूर्ण

अटल अचिन्हित दीर्घ hclgevf_ae_dev_reset_cnt(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	वापस hdev->rst_stats.hw_rst_करोne_cnt;
पूर्ण

अटल व्योम hclgevf_get_link_mode(काष्ठा hnae3_handle *handle,
				  अचिन्हित दीर्घ *supported,
				  अचिन्हित दीर्घ *advertising)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	*supported = hdev->hw.mac.supported;
	*advertising = hdev->hw.mac.advertising;
पूर्ण

#घोषणा MAX_SEPARATE_NUM	4
#घोषणा SEPARATOR_VALUE		0xFDFCFBFA
#घोषणा REG_NUM_PER_LINE	4
#घोषणा REG_LEN_PER_LINE	(REG_NUM_PER_LINE * माप(u32))

अटल पूर्णांक hclgevf_get_regs_len(काष्ठा hnae3_handle *handle)
अणु
	पूर्णांक cmdq_lines, common_lines, ring_lines, tqp_पूर्णांकr_lines;
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	cmdq_lines = माप(cmdq_reg_addr_list) / REG_LEN_PER_LINE + 1;
	common_lines = माप(common_reg_addr_list) / REG_LEN_PER_LINE + 1;
	ring_lines = माप(ring_reg_addr_list) / REG_LEN_PER_LINE + 1;
	tqp_पूर्णांकr_lines = माप(tqp_पूर्णांकr_reg_addr_list) / REG_LEN_PER_LINE + 1;

	वापस (cmdq_lines + common_lines + ring_lines * hdev->num_tqps +
		tqp_पूर्णांकr_lines * (hdev->num_msi_used - 1)) * REG_LEN_PER_LINE;
पूर्ण

अटल व्योम hclgevf_get_regs(काष्ठा hnae3_handle *handle, u32 *version,
			     व्योम *data)
अणु
	काष्ठा hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	पूर्णांक i, j, reg_um, separator_num;
	u32 *reg = data;

	*version = hdev->fw_version;

	/* fetching per-VF रेजिस्टरs values from VF PCIe रेजिस्टर space */
	reg_um = माप(cmdq_reg_addr_list) / माप(u32);
	separator_num = MAX_SEPARATE_NUM - reg_um % REG_NUM_PER_LINE;
	क्रम (i = 0; i < reg_um; i++)
		*reg++ = hclgevf_पढ़ो_dev(&hdev->hw, cmdq_reg_addr_list[i]);
	क्रम (i = 0; i < separator_num; i++)
		*reg++ = SEPARATOR_VALUE;

	reg_um = माप(common_reg_addr_list) / माप(u32);
	separator_num = MAX_SEPARATE_NUM - reg_um % REG_NUM_PER_LINE;
	क्रम (i = 0; i < reg_um; i++)
		*reg++ = hclgevf_पढ़ो_dev(&hdev->hw, common_reg_addr_list[i]);
	क्रम (i = 0; i < separator_num; i++)
		*reg++ = SEPARATOR_VALUE;

	reg_um = माप(ring_reg_addr_list) / माप(u32);
	separator_num = MAX_SEPARATE_NUM - reg_um % REG_NUM_PER_LINE;
	क्रम (j = 0; j < hdev->num_tqps; j++) अणु
		क्रम (i = 0; i < reg_um; i++)
			*reg++ = hclgevf_पढ़ो_dev(&hdev->hw,
						  ring_reg_addr_list[i] +
						  0x200 * j);
		क्रम (i = 0; i < separator_num; i++)
			*reg++ = SEPARATOR_VALUE;
	पूर्ण

	reg_um = माप(tqp_पूर्णांकr_reg_addr_list) / माप(u32);
	separator_num = MAX_SEPARATE_NUM - reg_um % REG_NUM_PER_LINE;
	क्रम (j = 0; j < hdev->num_msi_used - 1; j++) अणु
		क्रम (i = 0; i < reg_um; i++)
			*reg++ = hclgevf_पढ़ो_dev(&hdev->hw,
						  tqp_पूर्णांकr_reg_addr_list[i] +
						  4 * j);
		क्रम (i = 0; i < separator_num; i++)
			*reg++ = SEPARATOR_VALUE;
	पूर्ण
पूर्ण

व्योम hclgevf_update_port_base_vlan_info(काष्ठा hclgevf_dev *hdev, u16 state,
					u8 *port_base_vlan_info, u8 data_size)
अणु
	काष्ठा hnae3_handle *nic = &hdev->nic;
	काष्ठा hclge_vf_to_pf_msg send_msg;
	पूर्णांक ret;

	rtnl_lock();

	अगर (test_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state) ||
	    test_bit(HCLGEVF_STATE_RST_FAIL, &hdev->state)) अणु
		dev_warn(&hdev->pdev->dev,
			 "is resetting when updating port based vlan info\n");
		rtnl_unlock();
		वापस;
	पूर्ण

	ret = hclgevf_notअगरy_client(hdev, HNAE3_DOWN_CLIENT);
	अगर (ret) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	/* send msg to PF and रुको update port based vlan info */
	hclgevf_build_send_msg(&send_msg, HCLGE_MBX_SET_VLAN,
			       HCLGE_MBX_PORT_BASE_VLAN_CFG);
	स_नकल(send_msg.data, port_base_vlan_info, data_size);
	ret = hclgevf_send_mbx_msg(hdev, &send_msg, false, शून्य, 0);
	अगर (!ret) अणु
		अगर (state == HNAE3_PORT_BASE_VLAN_DISABLE)
			nic->port_base_vlan_state = state;
		अन्यथा
			nic->port_base_vlan_state = HNAE3_PORT_BASE_VLAN_ENABLE;
	पूर्ण

	hclgevf_notअगरy_client(hdev, HNAE3_UP_CLIENT);
	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा hnae3_ae_ops hclgevf_ops = अणु
	.init_ae_dev = hclgevf_init_ae_dev,
	.uninit_ae_dev = hclgevf_uninit_ae_dev,
	.reset_prepare = hclgevf_reset_prepare_general,
	.reset_करोne = hclgevf_reset_करोne,
	.init_client_instance = hclgevf_init_client_instance,
	.uninit_client_instance = hclgevf_uninit_client_instance,
	.start = hclgevf_ae_start,
	.stop = hclgevf_ae_stop,
	.client_start = hclgevf_client_start,
	.client_stop = hclgevf_client_stop,
	.map_ring_to_vector = hclgevf_map_ring_to_vector,
	.unmap_ring_from_vector = hclgevf_unmap_ring_from_vector,
	.get_vector = hclgevf_get_vector,
	.put_vector = hclgevf_put_vector,
	.reset_queue = hclgevf_reset_tqp,
	.get_mac_addr = hclgevf_get_mac_addr,
	.set_mac_addr = hclgevf_set_mac_addr,
	.add_uc_addr = hclgevf_add_uc_addr,
	.rm_uc_addr = hclgevf_rm_uc_addr,
	.add_mc_addr = hclgevf_add_mc_addr,
	.rm_mc_addr = hclgevf_rm_mc_addr,
	.get_stats = hclgevf_get_stats,
	.update_stats = hclgevf_update_stats,
	.get_strings = hclgevf_get_strings,
	.get_sset_count = hclgevf_get_sset_count,
	.get_rss_key_size = hclgevf_get_rss_key_size,
	.get_rss = hclgevf_get_rss,
	.set_rss = hclgevf_set_rss,
	.get_rss_tuple = hclgevf_get_rss_tuple,
	.set_rss_tuple = hclgevf_set_rss_tuple,
	.get_tc_size = hclgevf_get_tc_size,
	.get_fw_version = hclgevf_get_fw_version,
	.set_vlan_filter = hclgevf_set_vlan_filter,
	.enable_hw_strip_rxvtag = hclgevf_en_hw_strip_rxvtag,
	.reset_event = hclgevf_reset_event,
	.set_शेष_reset_request = hclgevf_set_def_reset_request,
	.set_channels = hclgevf_set_channels,
	.get_channels = hclgevf_get_channels,
	.get_tqps_and_rss_info = hclgevf_get_tqps_and_rss_info,
	.get_regs_len = hclgevf_get_regs_len,
	.get_regs = hclgevf_get_regs,
	.get_status = hclgevf_get_status,
	.get_ksettings_an_result = hclgevf_get_ksettings_an_result,
	.get_media_type = hclgevf_get_media_type,
	.get_hw_reset_stat = hclgevf_get_hw_reset_stat,
	.ae_dev_resetting = hclgevf_ae_dev_resetting,
	.ae_dev_reset_cnt = hclgevf_ae_dev_reset_cnt,
	.set_gro_en = hclgevf_gro_en,
	.set_mtu = hclgevf_set_mtu,
	.get_global_queue_id = hclgevf_get_qid_global,
	.set_समयr_task = hclgevf_set_समयr_task,
	.get_link_mode = hclgevf_get_link_mode,
	.set_promisc_mode = hclgevf_set_promisc_mode,
	.request_update_promisc_mode = hclgevf_request_update_promisc_mode,
	.get_cmdq_stat = hclgevf_get_cmdq_stat,
पूर्ण;

अटल काष्ठा hnae3_ae_algo ae_algovf = अणु
	.ops = &hclgevf_ops,
	.pdev_id_table = ae_algovf_pci_tbl,
पूर्ण;

अटल पूर्णांक hclgevf_init(व्योम)
अणु
	pr_info("%s is initializing\n", HCLGEVF_NAME);

	hclgevf_wq = alloc_workqueue("%s", 0, 0, HCLGEVF_NAME);
	अगर (!hclgevf_wq) अणु
		pr_err("%s: failed to create workqueue\n", HCLGEVF_NAME);
		वापस -ENOMEM;
	पूर्ण

	hnae3_रेजिस्टर_ae_algo(&ae_algovf);

	वापस 0;
पूर्ण

अटल व्योम hclgevf_निकास(व्योम)
अणु
	hnae3_unरेजिस्टर_ae_algo(&ae_algovf);
	destroy_workqueue(hclgevf_wq);
पूर्ण
module_init(hclgevf_init);
module_निकास(hclgevf_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huawei Tech. Co., Ltd.");
MODULE_DESCRIPTION("HCLGEVF Driver");
MODULE_VERSION(HCLGEVF_MOD_VERSION);
