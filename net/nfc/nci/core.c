<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  The NFC Controller Interface is the communication protocol between an
 *  NFC Controller (NFCC) and a Device Host (DH).
 *
 *  Copyright (C) 2011 Texas Instruments, Inc.
 *  Copyright (C) 2014 Marvell International Ltd.
 *
 *  Written by Ilan Elias <ilane@ti.com>
 *
 *  Acknowledgements:
 *  This file is based on hci_core.c, which was written
 *  by Maxim Krasnyansky.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": %s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/completion.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/bitops.h>
#समावेश <linux/skbuff.h>

#समावेश "../nfc.h"
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>
#समावेश <linux/nfc.h>

काष्ठा core_conn_create_data अणु
	पूर्णांक length;
	काष्ठा nci_core_conn_create_cmd *cmd;
पूर्ण;

अटल व्योम nci_cmd_work(काष्ठा work_काष्ठा *work);
अटल व्योम nci_rx_work(काष्ठा work_काष्ठा *work);
अटल व्योम nci_tx_work(काष्ठा work_काष्ठा *work);

काष्ठा nci_conn_info *nci_get_conn_info_by_conn_id(काष्ठा nci_dev *ndev,
						   पूर्णांक conn_id)
अणु
	काष्ठा nci_conn_info *conn_info;

	list_क्रम_each_entry(conn_info, &ndev->conn_info_list, list) अणु
		अगर (conn_info->conn_id == conn_id)
			वापस conn_info;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक nci_get_conn_info_by_dest_type_params(काष्ठा nci_dev *ndev, u8 dest_type,
					  काष्ठा dest_spec_params *params)
अणु
	काष्ठा nci_conn_info *conn_info;

	list_क्रम_each_entry(conn_info, &ndev->conn_info_list, list) अणु
		अगर (conn_info->dest_type == dest_type) अणु
			अगर (!params)
				वापस conn_info->conn_id;

			अगर (params->id == conn_info->dest_params->id &&
			    params->protocol == conn_info->dest_params->protocol)
				वापस conn_info->conn_id;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(nci_get_conn_info_by_dest_type_params);

/* ---- NCI requests ---- */

व्योम nci_req_complete(काष्ठा nci_dev *ndev, पूर्णांक result)
अणु
	अगर (ndev->req_status == NCI_REQ_PEND) अणु
		ndev->req_result = result;
		ndev->req_status = NCI_REQ_DONE;
		complete(&ndev->req_completion);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nci_req_complete);

अटल व्योम nci_req_cancel(काष्ठा nci_dev *ndev, पूर्णांक err)
अणु
	अगर (ndev->req_status == NCI_REQ_PEND) अणु
		ndev->req_result = err;
		ndev->req_status = NCI_REQ_CANCELED;
		complete(&ndev->req_completion);
	पूर्ण
पूर्ण

/* Execute request and रुको क्रम completion. */
अटल पूर्णांक __nci_request(काष्ठा nci_dev *ndev,
			 व्योम (*req)(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt),
			 अचिन्हित दीर्घ opt, __u32 समयout)
अणु
	पूर्णांक rc = 0;
	दीर्घ completion_rc;

	ndev->req_status = NCI_REQ_PEND;

	reinit_completion(&ndev->req_completion);
	req(ndev, opt);
	completion_rc =
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ndev->req_completion,
							  समयout);

	pr_debug("wait_for_completion return %ld\n", completion_rc);

	अगर (completion_rc > 0) अणु
		चयन (ndev->req_status) अणु
		हाल NCI_REQ_DONE:
			rc = nci_to_त्रुटि_सं(ndev->req_result);
			अवरोध;

		हाल NCI_REQ_CANCELED:
			rc = -ndev->req_result;
			अवरोध;

		शेष:
			rc = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("wait_for_completion_interruptible_timeout failed %ld\n",
		       completion_rc);

		rc = ((completion_rc == 0) ? (-ETIMEDOUT) : (completion_rc));
	पूर्ण

	ndev->req_status = ndev->req_result = 0;

	वापस rc;
पूर्ण

अंतरभूत पूर्णांक nci_request(काष्ठा nci_dev *ndev,
		       व्योम (*req)(काष्ठा nci_dev *ndev,
				   अचिन्हित दीर्घ opt),
		       अचिन्हित दीर्घ opt, __u32 समयout)
अणु
	पूर्णांक rc;

	अगर (!test_bit(NCI_UP, &ndev->flags))
		वापस -ENETDOWN;

	/* Serialize all requests */
	mutex_lock(&ndev->req_lock);
	rc = __nci_request(ndev, req, opt, समयout);
	mutex_unlock(&ndev->req_lock);

	वापस rc;
पूर्ण

अटल व्योम nci_reset_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_core_reset_cmd cmd;

	cmd.reset_type = NCI_RESET_TYPE_RESET_CONFIG;
	nci_send_cmd(ndev, NCI_OP_CORE_RESET_CMD, 1, &cmd);
पूर्ण

अटल व्योम nci_init_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	u8 plen = 0;

	अगर (opt)
		plen = माप(काष्ठा nci_core_init_v2_cmd);

	nci_send_cmd(ndev, NCI_OP_CORE_INIT_CMD, plen, (व्योम *)opt);
पूर्ण

अटल व्योम nci_init_complete_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_rf_disc_map_cmd cmd;
	काष्ठा disc_map_config *cfg = cmd.mapping_configs;
	__u8 *num = &cmd.num_mapping_configs;
	पूर्णांक i;

	/* set rf mapping configurations */
	*num = 0;

	/* by शेष mapping is set to NCI_RF_INTERFACE_FRAME */
	क्रम (i = 0; i < ndev->num_supported_rf_पूर्णांकerfaces; i++) अणु
		अगर (ndev->supported_rf_पूर्णांकerfaces[i] ==
		    NCI_RF_INTERFACE_ISO_DEP) अणु
			cfg[*num].rf_protocol = NCI_RF_PROTOCOL_ISO_DEP;
			cfg[*num].mode = NCI_DISC_MAP_MODE_POLL |
				NCI_DISC_MAP_MODE_LISTEN;
			cfg[*num].rf_पूर्णांकerface = NCI_RF_INTERFACE_ISO_DEP;
			(*num)++;
		पूर्ण अन्यथा अगर (ndev->supported_rf_पूर्णांकerfaces[i] ==
			   NCI_RF_INTERFACE_NFC_DEP) अणु
			cfg[*num].rf_protocol = NCI_RF_PROTOCOL_NFC_DEP;
			cfg[*num].mode = NCI_DISC_MAP_MODE_POLL |
				NCI_DISC_MAP_MODE_LISTEN;
			cfg[*num].rf_पूर्णांकerface = NCI_RF_INTERFACE_NFC_DEP;
			(*num)++;
		पूर्ण

		अगर (*num == NCI_MAX_NUM_MAPPING_CONFIGS)
			अवरोध;
	पूर्ण

	nci_send_cmd(ndev, NCI_OP_RF_DISCOVER_MAP_CMD,
		     (1 + ((*num) * माप(काष्ठा disc_map_config))), &cmd);
पूर्ण

काष्ठा nci_set_config_param अणु
	__u8	id;
	माप_प्रकार	len;
	__u8	*val;
पूर्ण;

अटल व्योम nci_set_config_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_set_config_param *param = (काष्ठा nci_set_config_param *)opt;
	काष्ठा nci_core_set_config_cmd cmd;

	BUG_ON(param->len > NCI_MAX_PARAM_LEN);

	cmd.num_params = 1;
	cmd.param.id = param->id;
	cmd.param.len = param->len;
	स_नकल(cmd.param.val, param->val, param->len);

	nci_send_cmd(ndev, NCI_OP_CORE_SET_CONFIG_CMD, (3 + param->len), &cmd);
पूर्ण

काष्ठा nci_rf_discover_param अणु
	__u32	im_protocols;
	__u32	पंचांग_protocols;
पूर्ण;

अटल व्योम nci_rf_discover_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_rf_discover_param *param =
		(काष्ठा nci_rf_discover_param *)opt;
	काष्ठा nci_rf_disc_cmd cmd;

	cmd.num_disc_configs = 0;

	अगर ((cmd.num_disc_configs < NCI_MAX_NUM_RF_CONFIGS) &&
	    (param->im_protocols & NFC_PROTO_JEWEL_MASK ||
	     param->im_protocols & NFC_PROTO_MIFARE_MASK ||
	     param->im_protocols & NFC_PROTO_ISO14443_MASK ||
	     param->im_protocols & NFC_PROTO_NFC_DEP_MASK)) अणु
		cmd.disc_configs[cmd.num_disc_configs].rf_tech_and_mode =
			NCI_NFC_A_PASSIVE_POLL_MODE;
		cmd.disc_configs[cmd.num_disc_configs].frequency = 1;
		cmd.num_disc_configs++;
	पूर्ण

	अगर ((cmd.num_disc_configs < NCI_MAX_NUM_RF_CONFIGS) &&
	    (param->im_protocols & NFC_PROTO_ISO14443_B_MASK)) अणु
		cmd.disc_configs[cmd.num_disc_configs].rf_tech_and_mode =
			NCI_NFC_B_PASSIVE_POLL_MODE;
		cmd.disc_configs[cmd.num_disc_configs].frequency = 1;
		cmd.num_disc_configs++;
	पूर्ण

	अगर ((cmd.num_disc_configs < NCI_MAX_NUM_RF_CONFIGS) &&
	    (param->im_protocols & NFC_PROTO_FELICA_MASK ||
	     param->im_protocols & NFC_PROTO_NFC_DEP_MASK)) अणु
		cmd.disc_configs[cmd.num_disc_configs].rf_tech_and_mode =
			NCI_NFC_F_PASSIVE_POLL_MODE;
		cmd.disc_configs[cmd.num_disc_configs].frequency = 1;
		cmd.num_disc_configs++;
	पूर्ण

	अगर ((cmd.num_disc_configs < NCI_MAX_NUM_RF_CONFIGS) &&
	    (param->im_protocols & NFC_PROTO_ISO15693_MASK)) अणु
		cmd.disc_configs[cmd.num_disc_configs].rf_tech_and_mode =
			NCI_NFC_V_PASSIVE_POLL_MODE;
		cmd.disc_configs[cmd.num_disc_configs].frequency = 1;
		cmd.num_disc_configs++;
	पूर्ण

	अगर ((cmd.num_disc_configs < NCI_MAX_NUM_RF_CONFIGS - 1) &&
	    (param->पंचांग_protocols & NFC_PROTO_NFC_DEP_MASK)) अणु
		cmd.disc_configs[cmd.num_disc_configs].rf_tech_and_mode =
			NCI_NFC_A_PASSIVE_LISTEN_MODE;
		cmd.disc_configs[cmd.num_disc_configs].frequency = 1;
		cmd.num_disc_configs++;
		cmd.disc_configs[cmd.num_disc_configs].rf_tech_and_mode =
			NCI_NFC_F_PASSIVE_LISTEN_MODE;
		cmd.disc_configs[cmd.num_disc_configs].frequency = 1;
		cmd.num_disc_configs++;
	पूर्ण

	nci_send_cmd(ndev, NCI_OP_RF_DISCOVER_CMD,
		     (1 + (cmd.num_disc_configs * माप(काष्ठा disc_config))),
		     &cmd);
पूर्ण

काष्ठा nci_rf_discover_select_param अणु
	__u8	rf_discovery_id;
	__u8	rf_protocol;
पूर्ण;

अटल व्योम nci_rf_discover_select_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_rf_discover_select_param *param =
		(काष्ठा nci_rf_discover_select_param *)opt;
	काष्ठा nci_rf_discover_select_cmd cmd;

	cmd.rf_discovery_id = param->rf_discovery_id;
	cmd.rf_protocol = param->rf_protocol;

	चयन (cmd.rf_protocol) अणु
	हाल NCI_RF_PROTOCOL_ISO_DEP:
		cmd.rf_पूर्णांकerface = NCI_RF_INTERFACE_ISO_DEP;
		अवरोध;

	हाल NCI_RF_PROTOCOL_NFC_DEP:
		cmd.rf_पूर्णांकerface = NCI_RF_INTERFACE_NFC_DEP;
		अवरोध;

	शेष:
		cmd.rf_पूर्णांकerface = NCI_RF_INTERFACE_FRAME;
		अवरोध;
	पूर्ण

	nci_send_cmd(ndev, NCI_OP_RF_DISCOVER_SELECT_CMD,
		     माप(काष्ठा nci_rf_discover_select_cmd), &cmd);
पूर्ण

अटल व्योम nci_rf_deactivate_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_rf_deactivate_cmd cmd;

	cmd.type = opt;

	nci_send_cmd(ndev, NCI_OP_RF_DEACTIVATE_CMD,
		     माप(काष्ठा nci_rf_deactivate_cmd), &cmd);
पूर्ण

काष्ठा nci_cmd_param अणु
	__u16 opcode;
	माप_प्रकार len;
	__u8 *payload;
पूर्ण;

अटल व्योम nci_generic_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_cmd_param *param =
		(काष्ठा nci_cmd_param *)opt;

	nci_send_cmd(ndev, param->opcode, param->len, param->payload);
पूर्ण

पूर्णांक nci_prop_cmd(काष्ठा nci_dev *ndev, __u8 oid, माप_प्रकार len, __u8 *payload)
अणु
	काष्ठा nci_cmd_param param;

	param.opcode = nci_opcode_pack(NCI_GID_PROPRIETARY, oid);
	param.len = len;
	param.payload = payload;

	वापस __nci_request(ndev, nci_generic_req, (अचिन्हित दीर्घ)&param,
			     msecs_to_jअगरfies(NCI_CMD_TIMEOUT));
पूर्ण
EXPORT_SYMBOL(nci_prop_cmd);

पूर्णांक nci_core_cmd(काष्ठा nci_dev *ndev, __u16 opcode, माप_प्रकार len, __u8 *payload)
अणु
	काष्ठा nci_cmd_param param;

	param.opcode = opcode;
	param.len = len;
	param.payload = payload;

	वापस __nci_request(ndev, nci_generic_req, (अचिन्हित दीर्घ)&param,
			     msecs_to_jअगरfies(NCI_CMD_TIMEOUT));
पूर्ण
EXPORT_SYMBOL(nci_core_cmd);

पूर्णांक nci_core_reset(काष्ठा nci_dev *ndev)
अणु
	वापस __nci_request(ndev, nci_reset_req, 0,
			     msecs_to_jअगरfies(NCI_RESET_TIMEOUT));
पूर्ण
EXPORT_SYMBOL(nci_core_reset);

पूर्णांक nci_core_init(काष्ठा nci_dev *ndev)
अणु
	वापस __nci_request(ndev, nci_init_req, 0,
			     msecs_to_jअगरfies(NCI_INIT_TIMEOUT));
पूर्ण
EXPORT_SYMBOL(nci_core_init);

काष्ठा nci_loopback_data अणु
	u8 conn_id;
	काष्ठा sk_buff *data;
पूर्ण;

अटल व्योम nci_send_data_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_loopback_data *data = (काष्ठा nci_loopback_data *)opt;

	nci_send_data(ndev, data->conn_id, data->data);
पूर्ण

अटल व्योम nci_nfcc_loopback_cb(व्योम *context, काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	काष्ठा nci_dev *ndev = (काष्ठा nci_dev *)context;
	काष्ठा nci_conn_info    *conn_info;

	conn_info = nci_get_conn_info_by_conn_id(ndev, ndev->cur_conn_id);
	अगर (!conn_info) अणु
		nci_req_complete(ndev, NCI_STATUS_REJECTED);
		वापस;
	पूर्ण

	conn_info->rx_skb = skb;

	nci_req_complete(ndev, NCI_STATUS_OK);
पूर्ण

पूर्णांक nci_nfcc_loopback(काष्ठा nci_dev *ndev, व्योम *data, माप_प्रकार data_len,
		      काष्ठा sk_buff **resp)
अणु
	पूर्णांक r;
	काष्ठा nci_loopback_data loopback_data;
	काष्ठा nci_conn_info *conn_info;
	काष्ठा sk_buff *skb;
	पूर्णांक conn_id = nci_get_conn_info_by_dest_type_params(ndev,
					NCI_DESTINATION_NFCC_LOOPBACK, शून्य);

	अगर (conn_id < 0) अणु
		r = nci_core_conn_create(ndev, NCI_DESTINATION_NFCC_LOOPBACK,
					 0, 0, शून्य);
		अगर (r != NCI_STATUS_OK)
			वापस r;

		conn_id = nci_get_conn_info_by_dest_type_params(ndev,
					NCI_DESTINATION_NFCC_LOOPBACK,
					शून्य);
	पूर्ण

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	अगर (!conn_info)
		वापस -EPROTO;

	/* store cb and context to be used on receiving data */
	conn_info->data_exchange_cb = nci_nfcc_loopback_cb;
	conn_info->data_exchange_cb_context = ndev;

	skb = nci_skb_alloc(ndev, NCI_DATA_HDR_SIZE + data_len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, NCI_DATA_HDR_SIZE);
	skb_put_data(skb, data, data_len);

	loopback_data.conn_id = conn_id;
	loopback_data.data = skb;

	ndev->cur_conn_id = conn_id;
	r = nci_request(ndev, nci_send_data_req, (अचिन्हित दीर्घ)&loopback_data,
			msecs_to_jअगरfies(NCI_DATA_TIMEOUT));
	अगर (r == NCI_STATUS_OK && resp)
		*resp = conn_info->rx_skb;

	वापस r;
पूर्ण
EXPORT_SYMBOL(nci_nfcc_loopback);

अटल पूर्णांक nci_खोलो_device(काष्ठा nci_dev *ndev)
अणु
	पूर्णांक rc = 0;

	mutex_lock(&ndev->req_lock);

	अगर (test_bit(NCI_UP, &ndev->flags)) अणु
		rc = -EALREADY;
		जाओ करोne;
	पूर्ण

	अगर (ndev->ops->खोलो(ndev)) अणु
		rc = -EIO;
		जाओ करोne;
	पूर्ण

	atomic_set(&ndev->cmd_cnt, 1);

	set_bit(NCI_INIT, &ndev->flags);

	अगर (ndev->ops->init)
		rc = ndev->ops->init(ndev);

	अगर (!rc) अणु
		rc = __nci_request(ndev, nci_reset_req, 0,
				   msecs_to_jअगरfies(NCI_RESET_TIMEOUT));
	पूर्ण

	अगर (!rc && ndev->ops->setup) अणु
		rc = ndev->ops->setup(ndev);
	पूर्ण

	अगर (!rc) अणु
		काष्ठा nci_core_init_v2_cmd nci_init_v2_cmd = अणु
			.feature1 = NCI_FEATURE_DISABLE,
			.feature2 = NCI_FEATURE_DISABLE
		पूर्ण;
		अचिन्हित दीर्घ opt = 0;

		अगर (ndev->nci_ver & NCI_VER_2_MASK)
			opt = (अचिन्हित दीर्घ)&nci_init_v2_cmd;

		rc = __nci_request(ndev, nci_init_req, opt,
				   msecs_to_jअगरfies(NCI_INIT_TIMEOUT));
	पूर्ण

	अगर (!rc && ndev->ops->post_setup)
		rc = ndev->ops->post_setup(ndev);

	अगर (!rc) अणु
		rc = __nci_request(ndev, nci_init_complete_req, 0,
				   msecs_to_jअगरfies(NCI_INIT_TIMEOUT));
	पूर्ण

	clear_bit(NCI_INIT, &ndev->flags);

	अगर (!rc) अणु
		set_bit(NCI_UP, &ndev->flags);
		nci_clear_target_list(ndev);
		atomic_set(&ndev->state, NCI_IDLE);
	पूर्ण अन्यथा अणु
		/* Init failed, cleanup */
		skb_queue_purge(&ndev->cmd_q);
		skb_queue_purge(&ndev->rx_q);
		skb_queue_purge(&ndev->tx_q);

		ndev->ops->बंद(ndev);
		ndev->flags = 0;
	पूर्ण

करोne:
	mutex_unlock(&ndev->req_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक nci_बंद_device(काष्ठा nci_dev *ndev)
अणु
	nci_req_cancel(ndev, ENODEV);
	mutex_lock(&ndev->req_lock);

	अगर (!test_and_clear_bit(NCI_UP, &ndev->flags)) अणु
		del_समयr_sync(&ndev->cmd_समयr);
		del_समयr_sync(&ndev->data_समयr);
		mutex_unlock(&ndev->req_lock);
		वापस 0;
	पूर्ण

	/* Drop RX and TX queues */
	skb_queue_purge(&ndev->rx_q);
	skb_queue_purge(&ndev->tx_q);

	/* Flush RX and TX wq */
	flush_workqueue(ndev->rx_wq);
	flush_workqueue(ndev->tx_wq);

	/* Reset device */
	skb_queue_purge(&ndev->cmd_q);
	atomic_set(&ndev->cmd_cnt, 1);

	set_bit(NCI_INIT, &ndev->flags);
	__nci_request(ndev, nci_reset_req, 0,
		      msecs_to_jअगरfies(NCI_RESET_TIMEOUT));

	/* After this poपूर्णांक our queues are empty
	 * and no works are scheduled.
	 */
	ndev->ops->बंद(ndev);

	clear_bit(NCI_INIT, &ndev->flags);

	/* Flush cmd wq */
	flush_workqueue(ndev->cmd_wq);

	del_समयr_sync(&ndev->cmd_समयr);

	/* Clear flags */
	ndev->flags = 0;

	mutex_unlock(&ndev->req_lock);

	वापस 0;
पूर्ण

/* NCI command समयr function */
अटल व्योम nci_cmd_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा nci_dev *ndev = from_समयr(ndev, t, cmd_समयr);

	atomic_set(&ndev->cmd_cnt, 1);
	queue_work(ndev->cmd_wq, &ndev->cmd_work);
पूर्ण

/* NCI data exchange समयr function */
अटल व्योम nci_data_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा nci_dev *ndev = from_समयr(ndev, t, data_समयr);

	set_bit(NCI_DATA_EXCHANGE_TO, &ndev->flags);
	queue_work(ndev->rx_wq, &ndev->rx_work);
पूर्ण

अटल पूर्णांक nci_dev_up(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	वापस nci_खोलो_device(ndev);
पूर्ण

अटल पूर्णांक nci_dev_करोwn(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	वापस nci_बंद_device(ndev);
पूर्ण

पूर्णांक nci_set_config(काष्ठा nci_dev *ndev, __u8 id, माप_प्रकार len, __u8 *val)
अणु
	काष्ठा nci_set_config_param param;

	अगर (!val || !len)
		वापस 0;

	param.id = id;
	param.len = len;
	param.val = val;

	वापस __nci_request(ndev, nci_set_config_req, (अचिन्हित दीर्घ)&param,
			     msecs_to_jअगरfies(NCI_SET_CONFIG_TIMEOUT));
पूर्ण
EXPORT_SYMBOL(nci_set_config);

अटल व्योम nci_nfcee_discover_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_nfcee_discover_cmd cmd;
	__u8 action = opt;

	cmd.discovery_action = action;

	nci_send_cmd(ndev, NCI_OP_NFCEE_DISCOVER_CMD, 1, &cmd);
पूर्ण

पूर्णांक nci_nfcee_discover(काष्ठा nci_dev *ndev, u8 action)
अणु
	वापस __nci_request(ndev, nci_nfcee_discover_req, action,
				msecs_to_jअगरfies(NCI_CMD_TIMEOUT));
पूर्ण
EXPORT_SYMBOL(nci_nfcee_discover);

अटल व्योम nci_nfcee_mode_set_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_nfcee_mode_set_cmd *cmd =
					(काष्ठा nci_nfcee_mode_set_cmd *)opt;

	nci_send_cmd(ndev, NCI_OP_NFCEE_MODE_SET_CMD,
		     माप(काष्ठा nci_nfcee_mode_set_cmd), cmd);
पूर्ण

पूर्णांक nci_nfcee_mode_set(काष्ठा nci_dev *ndev, u8 nfcee_id, u8 nfcee_mode)
अणु
	काष्ठा nci_nfcee_mode_set_cmd cmd;

	cmd.nfcee_id = nfcee_id;
	cmd.nfcee_mode = nfcee_mode;

	वापस __nci_request(ndev, nci_nfcee_mode_set_req,
			     (अचिन्हित दीर्घ)&cmd,
			     msecs_to_jअगरfies(NCI_CMD_TIMEOUT));
पूर्ण
EXPORT_SYMBOL(nci_nfcee_mode_set);

अटल व्योम nci_core_conn_create_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा core_conn_create_data *data =
					(काष्ठा core_conn_create_data *)opt;

	nci_send_cmd(ndev, NCI_OP_CORE_CONN_CREATE_CMD, data->length, data->cmd);
पूर्ण

पूर्णांक nci_core_conn_create(काष्ठा nci_dev *ndev, u8 destination_type,
			 u8 number_destination_params,
			 माप_प्रकार params_len,
			 काष्ठा core_conn_create_dest_spec_params *params)
अणु
	पूर्णांक r;
	काष्ठा nci_core_conn_create_cmd *cmd;
	काष्ठा core_conn_create_data data;

	data.length = params_len + माप(काष्ठा nci_core_conn_create_cmd);
	cmd = kzalloc(data.length, GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->destination_type = destination_type;
	cmd->number_destination_params = number_destination_params;

	data.cmd = cmd;

	अगर (params) अणु
		स_नकल(cmd->params, params, params_len);
		अगर (params->length > 0)
			स_नकल(&ndev->cur_params,
			       &params->value[DEST_SPEC_PARAMS_ID_INDEX],
			       माप(काष्ठा dest_spec_params));
		अन्यथा
			ndev->cur_params.id = 0;
	पूर्ण अन्यथा अणु
		ndev->cur_params.id = 0;
	पूर्ण
	ndev->cur_dest_type = destination_type;

	r = __nci_request(ndev, nci_core_conn_create_req, (अचिन्हित दीर्घ)&data,
			  msecs_to_jअगरfies(NCI_CMD_TIMEOUT));
	kमुक्त(cmd);
	वापस r;
पूर्ण
EXPORT_SYMBOL(nci_core_conn_create);

अटल व्योम nci_core_conn_बंद_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	__u8 conn_id = opt;

	nci_send_cmd(ndev, NCI_OP_CORE_CONN_CLOSE_CMD, 1, &conn_id);
पूर्ण

पूर्णांक nci_core_conn_बंद(काष्ठा nci_dev *ndev, u8 conn_id)
अणु
	ndev->cur_conn_id = conn_id;
	वापस __nci_request(ndev, nci_core_conn_बंद_req, conn_id,
			     msecs_to_jअगरfies(NCI_CMD_TIMEOUT));
पूर्ण
EXPORT_SYMBOL(nci_core_conn_बंद);

अटल पूर्णांक nci_set_local_general_bytes(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	काष्ठा nci_set_config_param param;
	पूर्णांक rc;

	param.val = nfc_get_local_general_bytes(nfc_dev, &param.len);
	अगर ((param.val == शून्य) || (param.len == 0))
		वापस 0;

	अगर (param.len > NFC_MAX_GT_LEN)
		वापस -EINVAL;

	param.id = NCI_PN_ATR_REQ_GEN_BYTES;

	rc = nci_request(ndev, nci_set_config_req, (अचिन्हित दीर्घ)&param,
			 msecs_to_jअगरfies(NCI_SET_CONFIG_TIMEOUT));
	अगर (rc)
		वापस rc;

	param.id = NCI_LN_ATR_RES_GEN_BYTES;

	वापस nci_request(ndev, nci_set_config_req, (अचिन्हित दीर्घ)&param,
			   msecs_to_jअगरfies(NCI_SET_CONFIG_TIMEOUT));
पूर्ण

अटल पूर्णांक nci_set_listen_parameters(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	पूर्णांक rc;
	__u8 val;

	val = NCI_LA_SEL_INFO_NFC_DEP_MASK;

	rc = nci_set_config(ndev, NCI_LA_SEL_INFO, 1, &val);
	अगर (rc)
		वापस rc;

	val = NCI_LF_PROTOCOL_TYPE_NFC_DEP_MASK;

	rc = nci_set_config(ndev, NCI_LF_PROTOCOL_TYPE, 1, &val);
	अगर (rc)
		वापस rc;

	val = NCI_LF_CON_BITR_F_212 | NCI_LF_CON_BITR_F_424;

	वापस nci_set_config(ndev, NCI_LF_CON_BITR_F, 1, &val);
पूर्ण

अटल पूर्णांक nci_start_poll(काष्ठा nfc_dev *nfc_dev,
			  __u32 im_protocols, __u32 पंचांग_protocols)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	काष्ठा nci_rf_discover_param param;
	पूर्णांक rc;

	अगर ((atomic_पढ़ो(&ndev->state) == NCI_DISCOVERY) ||
	    (atomic_पढ़ो(&ndev->state) == NCI_W4_ALL_DISCOVERIES)) अणु
		pr_err("unable to start poll, since poll is already active\n");
		वापस -EBUSY;
	पूर्ण

	अगर (ndev->target_active_prot) अणु
		pr_err("there is an active target\n");
		वापस -EBUSY;
	पूर्ण

	अगर ((atomic_पढ़ो(&ndev->state) == NCI_W4_HOST_SELECT) ||
	    (atomic_पढ़ो(&ndev->state) == NCI_POLL_ACTIVE)) अणु
		pr_debug("target active or w4 select, implicitly deactivate\n");

		rc = nci_request(ndev, nci_rf_deactivate_req,
				 NCI_DEACTIVATE_TYPE_IDLE_MODE,
				 msecs_to_jअगरfies(NCI_RF_DEACTIVATE_TIMEOUT));
		अगर (rc)
			वापस -EBUSY;
	पूर्ण

	अगर ((im_protocols | पंचांग_protocols) & NFC_PROTO_NFC_DEP_MASK) अणु
		rc = nci_set_local_general_bytes(nfc_dev);
		अगर (rc) अणु
			pr_err("failed to set local general bytes\n");
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (पंचांग_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
		rc = nci_set_listen_parameters(nfc_dev);
		अगर (rc)
			pr_err("failed to set listen parameters\n");
	पूर्ण

	param.im_protocols = im_protocols;
	param.पंचांग_protocols = पंचांग_protocols;
	rc = nci_request(ndev, nci_rf_discover_req, (अचिन्हित दीर्घ)&param,
			 msecs_to_jअगरfies(NCI_RF_DISC_TIMEOUT));

	अगर (!rc)
		ndev->poll_prots = im_protocols;

	वापस rc;
पूर्ण

अटल व्योम nci_stop_poll(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	अगर ((atomic_पढ़ो(&ndev->state) != NCI_DISCOVERY) &&
	    (atomic_पढ़ो(&ndev->state) != NCI_W4_ALL_DISCOVERIES)) अणु
		pr_err("unable to stop poll, since poll is not active\n");
		वापस;
	पूर्ण

	nci_request(ndev, nci_rf_deactivate_req, NCI_DEACTIVATE_TYPE_IDLE_MODE,
		    msecs_to_jअगरfies(NCI_RF_DEACTIVATE_TIMEOUT));
पूर्ण

अटल पूर्णांक nci_activate_target(काष्ठा nfc_dev *nfc_dev,
			       काष्ठा nfc_target *target, __u32 protocol)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	काष्ठा nci_rf_discover_select_param param;
	काष्ठा nfc_target *nci_target = शून्य;
	पूर्णांक i;
	पूर्णांक rc = 0;

	pr_debug("target_idx %d, protocol 0x%x\n", target->idx, protocol);

	अगर ((atomic_पढ़ो(&ndev->state) != NCI_W4_HOST_SELECT) &&
	    (atomic_पढ़ो(&ndev->state) != NCI_POLL_ACTIVE)) अणु
		pr_err("there is no available target to activate\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ndev->target_active_prot) अणु
		pr_err("there is already an active target\n");
		वापस -EBUSY;
	पूर्ण

	क्रम (i = 0; i < ndev->n_tarमाला_लो; i++) अणु
		अगर (ndev->tarमाला_लो[i].idx == target->idx) अणु
			nci_target = &ndev->tarमाला_लो[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!nci_target) अणु
		pr_err("unable to find the selected target\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(nci_target->supported_protocols & (1 << protocol))) अणु
		pr_err("target does not support the requested protocol 0x%x\n",
		       protocol);
		वापस -EINVAL;
	पूर्ण

	अगर (atomic_पढ़ो(&ndev->state) == NCI_W4_HOST_SELECT) अणु
		param.rf_discovery_id = nci_target->logical_idx;

		अगर (protocol == NFC_PROTO_JEWEL)
			param.rf_protocol = NCI_RF_PROTOCOL_T1T;
		अन्यथा अगर (protocol == NFC_PROTO_MIFARE)
			param.rf_protocol = NCI_RF_PROTOCOL_T2T;
		अन्यथा अगर (protocol == NFC_PROTO_FELICA)
			param.rf_protocol = NCI_RF_PROTOCOL_T3T;
		अन्यथा अगर (protocol == NFC_PROTO_ISO14443 ||
			 protocol == NFC_PROTO_ISO14443_B)
			param.rf_protocol = NCI_RF_PROTOCOL_ISO_DEP;
		अन्यथा
			param.rf_protocol = NCI_RF_PROTOCOL_NFC_DEP;

		rc = nci_request(ndev, nci_rf_discover_select_req,
				 (अचिन्हित दीर्घ)&param,
				 msecs_to_jअगरfies(NCI_RF_DISC_SELECT_TIMEOUT));
	पूर्ण

	अगर (!rc)
		ndev->target_active_prot = protocol;

	वापस rc;
पूर्ण

अटल व्योम nci_deactivate_target(काष्ठा nfc_dev *nfc_dev,
				  काष्ठा nfc_target *target,
				  __u8 mode)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	u8 nci_mode = NCI_DEACTIVATE_TYPE_IDLE_MODE;

	pr_debug("entry\n");

	अगर (!ndev->target_active_prot) अणु
		pr_err("unable to deactivate target, no active target\n");
		वापस;
	पूर्ण

	ndev->target_active_prot = 0;

	चयन (mode) अणु
	हाल NFC_TARGET_MODE_SLEEP:
		nci_mode = NCI_DEACTIVATE_TYPE_SLEEP_MODE;
		अवरोध;
	पूर्ण

	अगर (atomic_पढ़ो(&ndev->state) == NCI_POLL_ACTIVE) अणु
		nci_request(ndev, nci_rf_deactivate_req, nci_mode,
			    msecs_to_jअगरfies(NCI_RF_DEACTIVATE_TIMEOUT));
	पूर्ण
पूर्ण

अटल पूर्णांक nci_dep_link_up(काष्ठा nfc_dev *nfc_dev, काष्ठा nfc_target *target,
			   __u8 comm_mode, __u8 *gb, माप_प्रकार gb_len)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	पूर्णांक rc;

	pr_debug("target_idx %d, comm_mode %d\n", target->idx, comm_mode);

	rc = nci_activate_target(nfc_dev, target, NFC_PROTO_NFC_DEP);
	अगर (rc)
		वापस rc;

	rc = nfc_set_remote_general_bytes(nfc_dev, ndev->remote_gb,
					  ndev->remote_gb_len);
	अगर (!rc)
		rc = nfc_dep_link_is_up(nfc_dev, target->idx, NFC_COMM_PASSIVE,
					NFC_RF_INITIATOR);

	वापस rc;
पूर्ण

अटल पूर्णांक nci_dep_link_करोwn(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	पूर्णांक rc;

	pr_debug("entry\n");

	अगर (nfc_dev->rf_mode == NFC_RF_INITIATOR) अणु
		nci_deactivate_target(nfc_dev, शून्य, NCI_DEACTIVATE_TYPE_IDLE_MODE);
	पूर्ण अन्यथा अणु
		अगर (atomic_पढ़ो(&ndev->state) == NCI_LISTEN_ACTIVE ||
		    atomic_पढ़ो(&ndev->state) == NCI_DISCOVERY) अणु
			nci_request(ndev, nci_rf_deactivate_req, 0,
				msecs_to_jअगरfies(NCI_RF_DEACTIVATE_TIMEOUT));
		पूर्ण

		rc = nfc_पंचांग_deactivated(nfc_dev);
		अगर (rc)
			pr_err("error when signaling tm deactivation\n");
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक nci_transceive(काष्ठा nfc_dev *nfc_dev, काष्ठा nfc_target *target,
			  काष्ठा sk_buff *skb,
			  data_exchange_cb_t cb, व्योम *cb_context)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	पूर्णांक rc;
	काष्ठा nci_conn_info    *conn_info;

	conn_info = ndev->rf_conn_info;
	अगर (!conn_info)
		वापस -EPROTO;

	pr_debug("target_idx %d, len %d\n", target->idx, skb->len);

	अगर (!ndev->target_active_prot) अणु
		pr_err("unable to exchange data, no active target\n");
		वापस -EINVAL;
	पूर्ण

	अगर (test_and_set_bit(NCI_DATA_EXCHANGE, &ndev->flags))
		वापस -EBUSY;

	/* store cb and context to be used on receiving data */
	conn_info->data_exchange_cb = cb;
	conn_info->data_exchange_cb_context = cb_context;

	rc = nci_send_data(ndev, NCI_STATIC_RF_CONN_ID, skb);
	अगर (rc)
		clear_bit(NCI_DATA_EXCHANGE, &ndev->flags);

	वापस rc;
पूर्ण

अटल पूर्णांक nci_पंचांग_send(काष्ठा nfc_dev *nfc_dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	पूर्णांक rc;

	rc = nci_send_data(ndev, NCI_STATIC_RF_CONN_ID, skb);
	अगर (rc)
		pr_err("unable to send data\n");

	वापस rc;
पूर्ण

अटल पूर्णांक nci_enable_se(काष्ठा nfc_dev *nfc_dev, u32 se_idx)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	अगर (ndev->ops->enable_se)
		वापस ndev->ops->enable_se(ndev, se_idx);

	वापस 0;
पूर्ण

अटल पूर्णांक nci_disable_se(काष्ठा nfc_dev *nfc_dev, u32 se_idx)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	अगर (ndev->ops->disable_se)
		वापस ndev->ops->disable_se(ndev, se_idx);

	वापस 0;
पूर्ण

अटल पूर्णांक nci_discover_se(काष्ठा nfc_dev *nfc_dev)
अणु
	पूर्णांक r;
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	अगर (ndev->ops->discover_se) अणु
		r = nci_nfcee_discover(ndev, NCI_NFCEE_DISCOVERY_ACTION_ENABLE);
		अगर (r != NCI_STATUS_OK)
			वापस -EPROTO;

		वापस ndev->ops->discover_se(ndev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nci_se_io(काष्ठा nfc_dev *nfc_dev, u32 se_idx,
		     u8 *apdu, माप_प्रकार apdu_length,
		     se_io_cb_t cb, व्योम *cb_context)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	अगर (ndev->ops->se_io)
		वापस ndev->ops->se_io(ndev, se_idx, apdu,
				apdu_length, cb, cb_context);

	वापस 0;
पूर्ण

अटल पूर्णांक nci_fw_करोwnload(काष्ठा nfc_dev *nfc_dev, स्थिर अक्षर *firmware_name)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	अगर (!ndev->ops->fw_करोwnload)
		वापस -ENOTSUPP;

	वापस ndev->ops->fw_करोwnload(ndev, firmware_name);
पूर्ण

अटल काष्ठा nfc_ops nci_nfc_ops = अणु
	.dev_up = nci_dev_up,
	.dev_करोwn = nci_dev_करोwn,
	.start_poll = nci_start_poll,
	.stop_poll = nci_stop_poll,
	.dep_link_up = nci_dep_link_up,
	.dep_link_करोwn = nci_dep_link_करोwn,
	.activate_target = nci_activate_target,
	.deactivate_target = nci_deactivate_target,
	.im_transceive = nci_transceive,
	.पंचांग_send = nci_पंचांग_send,
	.enable_se = nci_enable_se,
	.disable_se = nci_disable_se,
	.discover_se = nci_discover_se,
	.se_io = nci_se_io,
	.fw_करोwnload = nci_fw_करोwnload,
पूर्ण;

/* ---- Interface to NCI drivers ---- */
/**
 * nci_allocate_device - allocate a new nci device
 *
 * @ops: device operations
 * @supported_protocols: NFC protocols supported by the device
 * @tx_headroom: Reserved space at beginning of skb
 * @tx_tailroom: Reserved space at end of skb
 */
काष्ठा nci_dev *nci_allocate_device(काष्ठा nci_ops *ops,
				    __u32 supported_protocols,
				    पूर्णांक tx_headroom, पूर्णांक tx_tailroom)
अणु
	काष्ठा nci_dev *ndev;

	pr_debug("supported_protocols 0x%x\n", supported_protocols);

	अगर (!ops->खोलो || !ops->बंद || !ops->send)
		वापस शून्य;

	अगर (!supported_protocols)
		वापस शून्य;

	ndev = kzalloc(माप(काष्ठा nci_dev), GFP_KERNEL);
	अगर (!ndev)
		वापस शून्य;

	ndev->ops = ops;

	अगर (ops->n_prop_ops > NCI_MAX_PROPRIETARY_CMD) अणु
		pr_err("Too many proprietary commands: %zd\n",
		       ops->n_prop_ops);
		ops->prop_ops = शून्य;
		ops->n_prop_ops = 0;
	पूर्ण

	ndev->tx_headroom = tx_headroom;
	ndev->tx_tailroom = tx_tailroom;
	init_completion(&ndev->req_completion);

	ndev->nfc_dev = nfc_allocate_device(&nci_nfc_ops,
					    supported_protocols,
					    tx_headroom + NCI_DATA_HDR_SIZE,
					    tx_tailroom);
	अगर (!ndev->nfc_dev)
		जाओ मुक्त_nci;

	ndev->hci_dev = nci_hci_allocate(ndev);
	अगर (!ndev->hci_dev)
		जाओ मुक्त_nfc;

	nfc_set_drvdata(ndev->nfc_dev, ndev);

	वापस ndev;

मुक्त_nfc:
	nfc_मुक्त_device(ndev->nfc_dev);
मुक्त_nci:
	kमुक्त(ndev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(nci_allocate_device);

/**
 * nci_मुक्त_device - deallocate nci device
 *
 * @ndev: The nci device to deallocate
 */
व्योम nci_मुक्त_device(काष्ठा nci_dev *ndev)
अणु
	nfc_मुक्त_device(ndev->nfc_dev);
	nci_hci_deallocate(ndev);
	kमुक्त(ndev);
पूर्ण
EXPORT_SYMBOL(nci_मुक्त_device);

/**
 * nci_रेजिस्टर_device - रेजिस्टर a nci device in the nfc subप्रणाली
 *
 * @ndev: The nci device to रेजिस्टर
 */
पूर्णांक nci_रेजिस्टर_device(काष्ठा nci_dev *ndev)
अणु
	पूर्णांक rc;
	काष्ठा device *dev = &ndev->nfc_dev->dev;
	अक्षर name[32];

	ndev->flags = 0;

	INIT_WORK(&ndev->cmd_work, nci_cmd_work);
	snम_लिखो(name, माप(name), "%s_nci_cmd_wq", dev_name(dev));
	ndev->cmd_wq = create_singlethपढ़ो_workqueue(name);
	अगर (!ndev->cmd_wq) अणु
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण

	INIT_WORK(&ndev->rx_work, nci_rx_work);
	snम_लिखो(name, माप(name), "%s_nci_rx_wq", dev_name(dev));
	ndev->rx_wq = create_singlethपढ़ो_workqueue(name);
	अगर (!ndev->rx_wq) अणु
		rc = -ENOMEM;
		जाओ destroy_cmd_wq_निकास;
	पूर्ण

	INIT_WORK(&ndev->tx_work, nci_tx_work);
	snम_लिखो(name, माप(name), "%s_nci_tx_wq", dev_name(dev));
	ndev->tx_wq = create_singlethपढ़ो_workqueue(name);
	अगर (!ndev->tx_wq) अणु
		rc = -ENOMEM;
		जाओ destroy_rx_wq_निकास;
	पूर्ण

	skb_queue_head_init(&ndev->cmd_q);
	skb_queue_head_init(&ndev->rx_q);
	skb_queue_head_init(&ndev->tx_q);

	समयr_setup(&ndev->cmd_समयr, nci_cmd_समयr, 0);
	समयr_setup(&ndev->data_समयr, nci_data_समयr, 0);

	mutex_init(&ndev->req_lock);
	INIT_LIST_HEAD(&ndev->conn_info_list);

	rc = nfc_रेजिस्टर_device(ndev->nfc_dev);
	अगर (rc)
		जाओ destroy_tx_wq_निकास;

	जाओ निकास;

destroy_tx_wq_निकास:
	destroy_workqueue(ndev->tx_wq);

destroy_rx_wq_निकास:
	destroy_workqueue(ndev->rx_wq);

destroy_cmd_wq_निकास:
	destroy_workqueue(ndev->cmd_wq);

निकास:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(nci_रेजिस्टर_device);

/**
 * nci_unरेजिस्टर_device - unरेजिस्टर a nci device in the nfc subप्रणाली
 *
 * @ndev: The nci device to unरेजिस्टर
 */
व्योम nci_unरेजिस्टर_device(काष्ठा nci_dev *ndev)
अणु
	काष्ठा nci_conn_info    *conn_info, *n;

	nci_बंद_device(ndev);

	destroy_workqueue(ndev->cmd_wq);
	destroy_workqueue(ndev->rx_wq);
	destroy_workqueue(ndev->tx_wq);

	list_क्रम_each_entry_safe(conn_info, n, &ndev->conn_info_list, list) अणु
		list_del(&conn_info->list);
		/* conn_info is allocated with devm_kzalloc */
	पूर्ण

	nfc_unरेजिस्टर_device(ndev->nfc_dev);
पूर्ण
EXPORT_SYMBOL(nci_unरेजिस्टर_device);

/**
 * nci_recv_frame - receive frame from NCI drivers
 *
 * @ndev: The nci device
 * @skb: The sk_buff to receive
 */
पूर्णांक nci_recv_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	pr_debug("len %d\n", skb->len);

	अगर (!ndev || (!test_bit(NCI_UP, &ndev->flags) &&
	    !test_bit(NCI_INIT, &ndev->flags))) अणु
		kमुक्त_skb(skb);
		वापस -ENXIO;
	पूर्ण

	/* Queue frame क्रम rx worker thपढ़ो */
	skb_queue_tail(&ndev->rx_q, skb);
	queue_work(ndev->rx_wq, &ndev->rx_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nci_recv_frame);

पूर्णांक nci_send_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	pr_debug("len %d\n", skb->len);

	अगर (!ndev) अणु
		kमुक्त_skb(skb);
		वापस -ENODEV;
	पूर्ण

	/* Get rid of skb owner, prior to sending to the driver. */
	skb_orphan(skb);

	/* Send copy to snअगरfer */
	nfc_send_to_raw_sock(ndev->nfc_dev, skb,
			     RAW_PAYLOAD_NCI, NFC_सूचीECTION_TX);

	वापस ndev->ops->send(ndev, skb);
पूर्ण
EXPORT_SYMBOL(nci_send_frame);

/* Send NCI command */
पूर्णांक nci_send_cmd(काष्ठा nci_dev *ndev, __u16 opcode, __u8 plen, व्योम *payload)
अणु
	काष्ठा nci_ctrl_hdr *hdr;
	काष्ठा sk_buff *skb;

	pr_debug("opcode 0x%x, plen %d\n", opcode, plen);

	skb = nci_skb_alloc(ndev, (NCI_CTRL_HDR_SIZE + plen), GFP_KERNEL);
	अगर (!skb) अणु
		pr_err("no memory for command\n");
		वापस -ENOMEM;
	पूर्ण

	hdr = skb_put(skb, NCI_CTRL_HDR_SIZE);
	hdr->gid = nci_opcode_gid(opcode);
	hdr->oid = nci_opcode_oid(opcode);
	hdr->plen = plen;

	nci_mt_set((__u8 *)hdr, NCI_MT_CMD_PKT);
	nci_pbf_set((__u8 *)hdr, NCI_PBF_LAST);

	अगर (plen)
		skb_put_data(skb, payload, plen);

	skb_queue_tail(&ndev->cmd_q, skb);
	queue_work(ndev->cmd_wq, &ndev->cmd_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nci_send_cmd);

/* Proprietary commands API */
अटल काष्ठा nci_driver_ops *ops_cmd_lookup(काष्ठा nci_driver_ops *ops,
					     माप_प्रकार n_ops,
					     __u16 opcode)
अणु
	माप_प्रकार i;
	काष्ठा nci_driver_ops *op;

	अगर (!ops || !n_ops)
		वापस शून्य;

	क्रम (i = 0; i < n_ops; i++) अणु
		op = &ops[i];
		अगर (op->opcode == opcode)
			वापस op;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक nci_op_rsp_packet(काष्ठा nci_dev *ndev, __u16 rsp_opcode,
			     काष्ठा sk_buff *skb, काष्ठा nci_driver_ops *ops,
			     माप_प्रकार n_ops)
अणु
	काष्ठा nci_driver_ops *op;

	op = ops_cmd_lookup(ops, n_ops, rsp_opcode);
	अगर (!op || !op->rsp)
		वापस -ENOTSUPP;

	वापस op->rsp(ndev, skb);
पूर्ण

अटल पूर्णांक nci_op_ntf_packet(काष्ठा nci_dev *ndev, __u16 ntf_opcode,
			     काष्ठा sk_buff *skb, काष्ठा nci_driver_ops *ops,
			     माप_प्रकार n_ops)
अणु
	काष्ठा nci_driver_ops *op;

	op = ops_cmd_lookup(ops, n_ops, ntf_opcode);
	अगर (!op || !op->ntf)
		वापस -ENOTSUPP;

	वापस op->ntf(ndev, skb);
पूर्ण

पूर्णांक nci_prop_rsp_packet(काष्ठा nci_dev *ndev, __u16 opcode,
			काष्ठा sk_buff *skb)
अणु
	वापस nci_op_rsp_packet(ndev, opcode, skb, ndev->ops->prop_ops,
				 ndev->ops->n_prop_ops);
पूर्ण

पूर्णांक nci_prop_ntf_packet(काष्ठा nci_dev *ndev, __u16 opcode,
			काष्ठा sk_buff *skb)
अणु
	वापस nci_op_ntf_packet(ndev, opcode, skb, ndev->ops->prop_ops,
				 ndev->ops->n_prop_ops);
पूर्ण

पूर्णांक nci_core_rsp_packet(काष्ठा nci_dev *ndev, __u16 opcode,
			काष्ठा sk_buff *skb)
अणु
	वापस nci_op_rsp_packet(ndev, opcode, skb, ndev->ops->core_ops,
				  ndev->ops->n_core_ops);
पूर्ण

पूर्णांक nci_core_ntf_packet(काष्ठा nci_dev *ndev, __u16 opcode,
			काष्ठा sk_buff *skb)
अणु
	वापस nci_op_ntf_packet(ndev, opcode, skb, ndev->ops->core_ops,
				 ndev->ops->n_core_ops);
पूर्ण

/* ---- NCI TX Data worker thपढ़ो ---- */

अटल व्योम nci_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nci_dev *ndev = container_of(work, काष्ठा nci_dev, tx_work);
	काष्ठा nci_conn_info    *conn_info;
	काष्ठा sk_buff *skb;

	conn_info = nci_get_conn_info_by_conn_id(ndev, ndev->cur_conn_id);
	अगर (!conn_info)
		वापस;

	pr_debug("credits_cnt %d\n", atomic_पढ़ो(&conn_info->credits_cnt));

	/* Send queued tx data */
	जबतक (atomic_पढ़ो(&conn_info->credits_cnt)) अणु
		skb = skb_dequeue(&ndev->tx_q);
		अगर (!skb)
			वापस;

		/* Check अगर data flow control is used */
		अगर (atomic_पढ़ो(&conn_info->credits_cnt) !=
		    NCI_DATA_FLOW_CONTROL_NOT_USED)
			atomic_dec(&conn_info->credits_cnt);

		pr_debug("NCI TX: MT=data, PBF=%d, conn_id=%d, plen=%d\n",
			 nci_pbf(skb->data),
			 nci_conn_id(skb->data),
			 nci_plen(skb->data));

		nci_send_frame(ndev, skb);

		mod_समयr(&ndev->data_समयr,
			  jअगरfies + msecs_to_jअगरfies(NCI_DATA_TIMEOUT));
	पूर्ण
पूर्ण

/* ----- NCI RX worker thपढ़ो (data & control) ----- */

अटल व्योम nci_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nci_dev *ndev = container_of(work, काष्ठा nci_dev, rx_work);
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&ndev->rx_q))) अणु

		/* Send copy to snअगरfer */
		nfc_send_to_raw_sock(ndev->nfc_dev, skb,
				     RAW_PAYLOAD_NCI, NFC_सूचीECTION_RX);

		/* Process frame */
		चयन (nci_mt(skb->data)) अणु
		हाल NCI_MT_RSP_PKT:
			nci_rsp_packet(ndev, skb);
			अवरोध;

		हाल NCI_MT_NTF_PKT:
			nci_ntf_packet(ndev, skb);
			अवरोध;

		हाल NCI_MT_DATA_PKT:
			nci_rx_data_packet(ndev, skb);
			अवरोध;

		शेष:
			pr_err("unknown MT 0x%x\n", nci_mt(skb->data));
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
	पूर्ण

	/* check अगर a data exchange समयout has occurred */
	अगर (test_bit(NCI_DATA_EXCHANGE_TO, &ndev->flags)) अणु
		/* complete the data exchange transaction, अगर exists */
		अगर (test_bit(NCI_DATA_EXCHANGE, &ndev->flags))
			nci_data_exchange_complete(ndev, शून्य,
						   ndev->cur_conn_id,
						   -ETIMEDOUT);

		clear_bit(NCI_DATA_EXCHANGE_TO, &ndev->flags);
	पूर्ण
पूर्ण

/* ----- NCI TX CMD worker thपढ़ो ----- */

अटल व्योम nci_cmd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nci_dev *ndev = container_of(work, काष्ठा nci_dev, cmd_work);
	काष्ठा sk_buff *skb;

	pr_debug("cmd_cnt %d\n", atomic_पढ़ो(&ndev->cmd_cnt));

	/* Send queued command */
	अगर (atomic_पढ़ो(&ndev->cmd_cnt)) अणु
		skb = skb_dequeue(&ndev->cmd_q);
		अगर (!skb)
			वापस;

		atomic_dec(&ndev->cmd_cnt);

		pr_debug("NCI TX: MT=cmd, PBF=%d, GID=0x%x, OID=0x%x, plen=%d\n",
			 nci_pbf(skb->data),
			 nci_opcode_gid(nci_opcode(skb->data)),
			 nci_opcode_oid(nci_opcode(skb->data)),
			 nci_plen(skb->data));

		nci_send_frame(ndev, skb);

		mod_समयr(&ndev->cmd_समयr,
			  jअगरfies + msecs_to_jअगरfies(NCI_CMD_TIMEOUT));
	पूर्ण
पूर्ण

MODULE_LICENSE("GPL");
