<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  The NFC Controller Interface is the communication protocol between an
 *  NFC Controller (NFCC) and a Device Host (DH).
 *
 *  Copyright (C) 2011 Texas Instruments, Inc.
 *
 *  Written by Ilan Elias <ilane@ti.com>
 *
 *  Acknowledgements:
 *  This file is based on hci_event.c, which was written
 *  by Maxim Krasnyansky.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": %s: " fmt, __func__

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/skbuff.h>

#समावेश "../nfc.h"
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>

/* Handle NCI Response packets */

अटल व्योम nci_core_reset_rsp_packet(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_core_reset_rsp *rsp = (व्योम *) skb->data;

	pr_debug("status 0x%x\n", rsp->status);

	/* Handle NCI 1.x ver */
	अगर (skb->len != 1) अणु
		अगर (rsp->status == NCI_STATUS_OK) अणु
			ndev->nci_ver = rsp->nci_ver;
			pr_debug("nci_ver 0x%x, config_status 0x%x\n",
				 rsp->nci_ver, rsp->config_status);
		पूर्ण

		nci_req_complete(ndev, rsp->status);
	पूर्ण
पूर्ण

अटल u8 nci_core_init_rsp_packet_v1(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_core_init_rsp_1 *rsp_1 = (व्योम *) skb->data;
	काष्ठा nci_core_init_rsp_2 *rsp_2;

	pr_debug("status 0x%x\n", rsp_1->status);

	अगर (rsp_1->status != NCI_STATUS_OK)
		वापस rsp_1->status;

	ndev->nfcc_features = __le32_to_cpu(rsp_1->nfcc_features);
	ndev->num_supported_rf_पूर्णांकerfaces = rsp_1->num_supported_rf_पूर्णांकerfaces;

	ndev->num_supported_rf_पूर्णांकerfaces =
		min((पूर्णांक)ndev->num_supported_rf_पूर्णांकerfaces,
		    NCI_MAX_SUPPORTED_RF_INTERFACES);

	स_नकल(ndev->supported_rf_पूर्णांकerfaces,
	       rsp_1->supported_rf_पूर्णांकerfaces,
	       ndev->num_supported_rf_पूर्णांकerfaces);

	rsp_2 = (व्योम *) (skb->data + 6 + rsp_1->num_supported_rf_पूर्णांकerfaces);

	ndev->max_logical_connections = rsp_2->max_logical_connections;
	ndev->max_routing_table_size =
		__le16_to_cpu(rsp_2->max_routing_table_size);
	ndev->max_ctrl_pkt_payload_len =
		rsp_2->max_ctrl_pkt_payload_len;
	ndev->max_size_क्रम_large_params =
		__le16_to_cpu(rsp_2->max_size_क्रम_large_params);
	ndev->manufact_id =
		rsp_2->manufact_id;
	ndev->manufact_specअगरic_info =
		__le32_to_cpu(rsp_2->manufact_specअगरic_info);

	वापस NCI_STATUS_OK;
पूर्ण

अटल u8 nci_core_init_rsp_packet_v2(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_core_init_rsp_nci_ver2 *rsp = (व्योम *)skb->data;
	u8 *supported_rf_पूर्णांकerface = rsp->supported_rf_पूर्णांकerfaces;
	u8 rf_पूर्णांकerface_idx = 0;
	u8 rf_extension_cnt = 0;

	pr_debug("status %x\n", rsp->status);

	अगर (rsp->status != NCI_STATUS_OK)
		वापस rsp->status;

	ndev->nfcc_features = __le32_to_cpu(rsp->nfcc_features);
	ndev->num_supported_rf_पूर्णांकerfaces = rsp->num_supported_rf_पूर्णांकerfaces;

	ndev->num_supported_rf_पूर्णांकerfaces =
		min((पूर्णांक)ndev->num_supported_rf_पूर्णांकerfaces,
		    NCI_MAX_SUPPORTED_RF_INTERFACES);

	जबतक (rf_पूर्णांकerface_idx < ndev->num_supported_rf_पूर्णांकerfaces) अणु
		ndev->supported_rf_पूर्णांकerfaces[rf_पूर्णांकerface_idx++] = *supported_rf_पूर्णांकerface++;

		/* skip rf extension parameters */
		rf_extension_cnt = *supported_rf_पूर्णांकerface++;
		supported_rf_पूर्णांकerface += rf_extension_cnt;
	पूर्ण

	ndev->max_logical_connections = rsp->max_logical_connections;
	ndev->max_routing_table_size =
			__le16_to_cpu(rsp->max_routing_table_size);
	ndev->max_ctrl_pkt_payload_len =
			rsp->max_ctrl_pkt_payload_len;
	ndev->max_size_क्रम_large_params = NCI_MAX_LARGE_PARAMS_NCI_v2;

	वापस NCI_STATUS_OK;
पूर्ण

अटल व्योम nci_core_init_rsp_packet(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	u8 status = 0;

	अगर (!(ndev->nci_ver & NCI_VER_2_MASK))
		status = nci_core_init_rsp_packet_v1(ndev, skb);
	अन्यथा
		status = nci_core_init_rsp_packet_v2(ndev, skb);

	अगर (status != NCI_STATUS_OK)
		जाओ निकास;

	pr_debug("nfcc_features 0x%x\n",
		 ndev->nfcc_features);
	pr_debug("num_supported_rf_interfaces %d\n",
		 ndev->num_supported_rf_पूर्णांकerfaces);
	pr_debug("supported_rf_interfaces[0] 0x%x\n",
		 ndev->supported_rf_पूर्णांकerfaces[0]);
	pr_debug("supported_rf_interfaces[1] 0x%x\n",
		 ndev->supported_rf_पूर्णांकerfaces[1]);
	pr_debug("supported_rf_interfaces[2] 0x%x\n",
		 ndev->supported_rf_पूर्णांकerfaces[2]);
	pr_debug("supported_rf_interfaces[3] 0x%x\n",
		 ndev->supported_rf_पूर्णांकerfaces[3]);
	pr_debug("max_logical_connections %d\n",
		 ndev->max_logical_connections);
	pr_debug("max_routing_table_size %d\n",
		 ndev->max_routing_table_size);
	pr_debug("max_ctrl_pkt_payload_len %d\n",
		 ndev->max_ctrl_pkt_payload_len);
	pr_debug("max_size_for_large_params %d\n",
		 ndev->max_size_क्रम_large_params);
	pr_debug("manufact_id 0x%x\n",
		 ndev->manufact_id);
	pr_debug("manufact_specific_info 0x%x\n",
		 ndev->manufact_specअगरic_info);

निकास:
	nci_req_complete(ndev, status);
पूर्ण

अटल व्योम nci_core_set_config_rsp_packet(काष्ठा nci_dev *ndev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_core_set_config_rsp *rsp = (व्योम *) skb->data;

	pr_debug("status 0x%x\n", rsp->status);

	nci_req_complete(ndev, rsp->status);
पूर्ण

अटल व्योम nci_rf_disc_map_rsp_packet(काष्ठा nci_dev *ndev,
				       काष्ठा sk_buff *skb)
अणु
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);

	nci_req_complete(ndev, status);
पूर्ण

अटल व्योम nci_rf_disc_rsp_packet(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_conn_info    *conn_info;
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);

	अगर (status == NCI_STATUS_OK) अणु
		atomic_set(&ndev->state, NCI_DISCOVERY);

		conn_info = ndev->rf_conn_info;
		अगर (!conn_info) अणु
			conn_info = devm_kzalloc(&ndev->nfc_dev->dev,
						 माप(काष्ठा nci_conn_info),
						 GFP_KERNEL);
			अगर (!conn_info) अणु
				status = NCI_STATUS_REJECTED;
				जाओ निकास;
			पूर्ण
			conn_info->conn_id = NCI_STATIC_RF_CONN_ID;
			INIT_LIST_HEAD(&conn_info->list);
			list_add(&conn_info->list, &ndev->conn_info_list);
			ndev->rf_conn_info = conn_info;
		पूर्ण
	पूर्ण

निकास:
	nci_req_complete(ndev, status);
पूर्ण

अटल व्योम nci_rf_disc_select_rsp_packet(काष्ठा nci_dev *ndev,
					  काष्ठा sk_buff *skb)
अणु
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);

	/* Complete the request on पूर्णांकf_activated_ntf or generic_error_ntf */
	अगर (status != NCI_STATUS_OK)
		nci_req_complete(ndev, status);
पूर्ण

अटल व्योम nci_rf_deactivate_rsp_packet(काष्ठा nci_dev *ndev,
					 काष्ठा sk_buff *skb)
अणु
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);

	/* If target was active, complete the request only in deactivate_ntf */
	अगर ((status != NCI_STATUS_OK) ||
	    (atomic_पढ़ो(&ndev->state) != NCI_POLL_ACTIVE)) अणु
		nci_clear_target_list(ndev);
		atomic_set(&ndev->state, NCI_IDLE);
		nci_req_complete(ndev, status);
	पूर्ण
पूर्ण

अटल व्योम nci_nfcee_discover_rsp_packet(काष्ठा nci_dev *ndev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_nfcee_discover_rsp *discover_rsp;

	अगर (skb->len != 2) अणु
		nci_req_complete(ndev, NCI_STATUS_NFCEE_PROTOCOL_ERROR);
		वापस;
	पूर्ण

	discover_rsp = (काष्ठा nci_nfcee_discover_rsp *)skb->data;

	अगर (discover_rsp->status != NCI_STATUS_OK ||
	    discover_rsp->num_nfcee == 0)
		nci_req_complete(ndev, discover_rsp->status);
पूर्ण

अटल व्योम nci_nfcee_mode_set_rsp_packet(काष्ठा nci_dev *ndev,
					  काष्ठा sk_buff *skb)
अणु
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);
	nci_req_complete(ndev, status);
पूर्ण

अटल व्योम nci_core_conn_create_rsp_packet(काष्ठा nci_dev *ndev,
					    काष्ठा sk_buff *skb)
अणु
	__u8 status = skb->data[0];
	काष्ठा nci_conn_info *conn_info = शून्य;
	काष्ठा nci_core_conn_create_rsp *rsp;

	pr_debug("status 0x%x\n", status);

	अगर (status == NCI_STATUS_OK) अणु
		rsp = (काष्ठा nci_core_conn_create_rsp *)skb->data;

		conn_info = devm_kzalloc(&ndev->nfc_dev->dev,
					 माप(*conn_info), GFP_KERNEL);
		अगर (!conn_info) अणु
			status = NCI_STATUS_REJECTED;
			जाओ निकास;
		पूर्ण

		conn_info->dest_params = devm_kzalloc(&ndev->nfc_dev->dev,
						माप(काष्ठा dest_spec_params),
						GFP_KERNEL);
		अगर (!conn_info->dest_params) अणु
			status = NCI_STATUS_REJECTED;
			जाओ मुक्त_conn_info;
		पूर्ण

		conn_info->dest_type = ndev->cur_dest_type;
		conn_info->dest_params->id = ndev->cur_params.id;
		conn_info->dest_params->protocol = ndev->cur_params.protocol;
		conn_info->conn_id = rsp->conn_id;

		/* Note: data_exchange_cb and data_exchange_cb_context need to
		 * be specअगरy out of nci_core_conn_create_rsp_packet
		 */

		INIT_LIST_HEAD(&conn_info->list);
		list_add(&conn_info->list, &ndev->conn_info_list);

		अगर (ndev->cur_params.id == ndev->hci_dev->nfcee_id)
			ndev->hci_dev->conn_info = conn_info;

		conn_info->conn_id = rsp->conn_id;
		conn_info->max_pkt_payload_len = rsp->max_ctrl_pkt_payload_len;
		atomic_set(&conn_info->credits_cnt, rsp->credits_cnt);
	पूर्ण

मुक्त_conn_info:
	अगर (status == NCI_STATUS_REJECTED)
		devm_kमुक्त(&ndev->nfc_dev->dev, conn_info);
निकास:

	nci_req_complete(ndev, status);
पूर्ण

अटल व्योम nci_core_conn_बंद_rsp_packet(काष्ठा nci_dev *ndev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_conn_info *conn_info;
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);
	अगर (status == NCI_STATUS_OK) अणु
		conn_info = nci_get_conn_info_by_conn_id(ndev,
							 ndev->cur_conn_id);
		अगर (conn_info) अणु
			list_del(&conn_info->list);
			devm_kमुक्त(&ndev->nfc_dev->dev, conn_info);
		पूर्ण
	पूर्ण
	nci_req_complete(ndev, status);
पूर्ण

व्योम nci_rsp_packet(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	__u16 rsp_opcode = nci_opcode(skb->data);

	/* we got a rsp, stop the cmd समयr */
	del_समयr(&ndev->cmd_समयr);

	pr_debug("NCI RX: MT=rsp, PBF=%d, GID=0x%x, OID=0x%x, plen=%d\n",
		 nci_pbf(skb->data),
		 nci_opcode_gid(rsp_opcode),
		 nci_opcode_oid(rsp_opcode),
		 nci_plen(skb->data));

	/* strip the nci control header */
	skb_pull(skb, NCI_CTRL_HDR_SIZE);

	अगर (nci_opcode_gid(rsp_opcode) == NCI_GID_PROPRIETARY) अणु
		अगर (nci_prop_rsp_packet(ndev, rsp_opcode, skb) == -ENOTSUPP) अणु
			pr_err("unsupported rsp opcode 0x%x\n",
			       rsp_opcode);
		पूर्ण

		जाओ end;
	पूर्ण

	चयन (rsp_opcode) अणु
	हाल NCI_OP_CORE_RESET_RSP:
		nci_core_reset_rsp_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_CORE_INIT_RSP:
		nci_core_init_rsp_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_CORE_SET_CONFIG_RSP:
		nci_core_set_config_rsp_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_CORE_CONN_CREATE_RSP:
		nci_core_conn_create_rsp_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_CORE_CONN_CLOSE_RSP:
		nci_core_conn_बंद_rsp_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_RF_DISCOVER_MAP_RSP:
		nci_rf_disc_map_rsp_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_RF_DISCOVER_RSP:
		nci_rf_disc_rsp_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_RF_DISCOVER_SELECT_RSP:
		nci_rf_disc_select_rsp_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_RF_DEACTIVATE_RSP:
		nci_rf_deactivate_rsp_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_NFCEE_DISCOVER_RSP:
		nci_nfcee_discover_rsp_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_NFCEE_MODE_SET_RSP:
		nci_nfcee_mode_set_rsp_packet(ndev, skb);
		अवरोध;

	शेष:
		pr_err("unknown rsp opcode 0x%x\n", rsp_opcode);
		अवरोध;
	पूर्ण

	nci_core_rsp_packet(ndev, rsp_opcode, skb);
end:
	kमुक्त_skb(skb);

	/* trigger the next cmd */
	atomic_set(&ndev->cmd_cnt, 1);
	अगर (!skb_queue_empty(&ndev->cmd_q))
		queue_work(ndev->cmd_wq, &ndev->cmd_work);
पूर्ण
