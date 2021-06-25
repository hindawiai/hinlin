<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  The NFC Controller Interface is the communication protocol between an
 *  NFC Controller (NFCC) and a Device Host (DH).
 *
 *  Copyright (C) 2014 Marvell International Ltd.
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
#समावेश <linux/nfc.h>

/* Handle NCI Notअगरication packets */

अटल व्योम nci_core_reset_ntf_packet(काष्ठा nci_dev *ndev,
				      काष्ठा sk_buff *skb)
अणु
	/* Handle NCI 2.x core reset notअगरication */
	काष्ठा nci_core_reset_ntf *ntf = (व्योम *)skb->data;

	ndev->nci_ver = ntf->nci_ver;
	pr_debug("nci_ver 0x%x, config_status 0x%x\n",
		 ntf->nci_ver, ntf->config_status);

	ndev->manufact_id = ntf->manufact_id;
	ndev->manufact_specअगरic_info =
		__le32_to_cpu(ntf->manufact_specअगरic_info);

	nci_req_complete(ndev, NCI_STATUS_OK);
पूर्ण

अटल व्योम nci_core_conn_credits_ntf_packet(काष्ठा nci_dev *ndev,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_core_conn_credit_ntf *ntf = (व्योम *) skb->data;
	काष्ठा nci_conn_info	*conn_info;
	पूर्णांक i;

	pr_debug("num_entries %d\n", ntf->num_entries);

	अगर (ntf->num_entries > NCI_MAX_NUM_CONN)
		ntf->num_entries = NCI_MAX_NUM_CONN;

	/* update the credits */
	क्रम (i = 0; i < ntf->num_entries; i++) अणु
		ntf->conn_entries[i].conn_id =
			nci_conn_id(&ntf->conn_entries[i].conn_id);

		pr_debug("entry[%d]: conn_id %d, credits %d\n",
			 i, ntf->conn_entries[i].conn_id,
			 ntf->conn_entries[i].credits);

		conn_info = nci_get_conn_info_by_conn_id(ndev,
							 ntf->conn_entries[i].conn_id);
		अगर (!conn_info)
			वापस;

		atomic_add(ntf->conn_entries[i].credits,
			   &conn_info->credits_cnt);
	पूर्ण

	/* trigger the next tx */
	अगर (!skb_queue_empty(&ndev->tx_q))
		queue_work(ndev->tx_wq, &ndev->tx_work);
पूर्ण

अटल व्योम nci_core_generic_error_ntf_packet(काष्ठा nci_dev *ndev,
					      काष्ठा sk_buff *skb)
अणु
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);

	अगर (atomic_पढ़ो(&ndev->state) == NCI_W4_HOST_SELECT) अणु
		/* Activation failed, so complete the request
		   (the state reमुख्यs the same) */
		nci_req_complete(ndev, status);
	पूर्ण
पूर्ण

अटल व्योम nci_core_conn_पूर्णांकf_error_ntf_packet(काष्ठा nci_dev *ndev,
						काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_core_पूर्णांकf_error_ntf *ntf = (व्योम *) skb->data;

	ntf->conn_id = nci_conn_id(&ntf->conn_id);

	pr_debug("status 0x%x, conn_id %d\n", ntf->status, ntf->conn_id);

	/* complete the data exchange transaction, अगर exists */
	अगर (test_bit(NCI_DATA_EXCHANGE, &ndev->flags))
		nci_data_exchange_complete(ndev, शून्य, ntf->conn_id, -EIO);
पूर्ण

अटल __u8 *nci_extract_rf_params_nfca_passive_poll(काष्ठा nci_dev *ndev,
			काष्ठा rf_tech_specअगरic_params_nfca_poll *nfca_poll,
						     __u8 *data)
अणु
	nfca_poll->sens_res = __le16_to_cpu(*((__le16 *)data));
	data += 2;

	nfca_poll->nfcid1_len = min_t(__u8, *data++, NFC_NFCID1_MAXSIZE);

	pr_debug("sens_res 0x%x, nfcid1_len %d\n",
		 nfca_poll->sens_res, nfca_poll->nfcid1_len);

	स_नकल(nfca_poll->nfcid1, data, nfca_poll->nfcid1_len);
	data += nfca_poll->nfcid1_len;

	nfca_poll->sel_res_len = *data++;

	अगर (nfca_poll->sel_res_len != 0)
		nfca_poll->sel_res = *data++;

	pr_debug("sel_res_len %d, sel_res 0x%x\n",
		 nfca_poll->sel_res_len,
		 nfca_poll->sel_res);

	वापस data;
पूर्ण

अटल __u8 *nci_extract_rf_params_nfcb_passive_poll(काष्ठा nci_dev *ndev,
			काष्ठा rf_tech_specअगरic_params_nfcb_poll *nfcb_poll,
						     __u8 *data)
अणु
	nfcb_poll->sensb_res_len = min_t(__u8, *data++, NFC_SENSB_RES_MAXSIZE);

	pr_debug("sensb_res_len %d\n", nfcb_poll->sensb_res_len);

	स_नकल(nfcb_poll->sensb_res, data, nfcb_poll->sensb_res_len);
	data += nfcb_poll->sensb_res_len;

	वापस data;
पूर्ण

अटल __u8 *nci_extract_rf_params_nfcf_passive_poll(काष्ठा nci_dev *ndev,
			काष्ठा rf_tech_specअगरic_params_nfcf_poll *nfcf_poll,
						     __u8 *data)
अणु
	nfcf_poll->bit_rate = *data++;
	nfcf_poll->sensf_res_len = min_t(__u8, *data++, NFC_SENSF_RES_MAXSIZE);

	pr_debug("bit_rate %d, sensf_res_len %d\n",
		 nfcf_poll->bit_rate, nfcf_poll->sensf_res_len);

	स_नकल(nfcf_poll->sensf_res, data, nfcf_poll->sensf_res_len);
	data += nfcf_poll->sensf_res_len;

	वापस data;
पूर्ण

अटल __u8 *nci_extract_rf_params_nfcv_passive_poll(काष्ठा nci_dev *ndev,
			काष्ठा rf_tech_specअगरic_params_nfcv_poll *nfcv_poll,
						     __u8 *data)
अणु
	++data;
	nfcv_poll->dsfid = *data++;
	स_नकल(nfcv_poll->uid, data, NFC_ISO15693_UID_MAXSIZE);
	data += NFC_ISO15693_UID_MAXSIZE;
	वापस data;
पूर्ण

अटल __u8 *nci_extract_rf_params_nfcf_passive_listen(काष्ठा nci_dev *ndev,
			काष्ठा rf_tech_specअगरic_params_nfcf_listen *nfcf_listen,
						     __u8 *data)
अणु
	nfcf_listen->local_nfcid2_len = min_t(__u8, *data++,
					      NFC_NFCID2_MAXSIZE);
	स_नकल(nfcf_listen->local_nfcid2, data, nfcf_listen->local_nfcid2_len);
	data += nfcf_listen->local_nfcid2_len;

	वापस data;
पूर्ण

अटल __u32 nci_get_prop_rf_protocol(काष्ठा nci_dev *ndev, __u8 rf_protocol)
अणु
	अगर (ndev->ops->get_rfprotocol)
		वापस ndev->ops->get_rfprotocol(ndev, rf_protocol);
	वापस 0;
पूर्ण

अटल पूर्णांक nci_add_new_protocol(काष्ठा nci_dev *ndev,
				काष्ठा nfc_target *target,
				__u8 rf_protocol,
				__u8 rf_tech_and_mode,
				व्योम *params)
अणु
	काष्ठा rf_tech_specअगरic_params_nfca_poll *nfca_poll;
	काष्ठा rf_tech_specअगरic_params_nfcb_poll *nfcb_poll;
	काष्ठा rf_tech_specअगरic_params_nfcf_poll *nfcf_poll;
	काष्ठा rf_tech_specअगरic_params_nfcv_poll *nfcv_poll;
	__u32 protocol;

	अगर (rf_protocol == NCI_RF_PROTOCOL_T1T)
		protocol = NFC_PROTO_JEWEL_MASK;
	अन्यथा अगर (rf_protocol == NCI_RF_PROTOCOL_T2T)
		protocol = NFC_PROTO_MIFARE_MASK;
	अन्यथा अगर (rf_protocol == NCI_RF_PROTOCOL_ISO_DEP)
		अगर (rf_tech_and_mode == NCI_NFC_A_PASSIVE_POLL_MODE)
			protocol = NFC_PROTO_ISO14443_MASK;
		अन्यथा
			protocol = NFC_PROTO_ISO14443_B_MASK;
	अन्यथा अगर (rf_protocol == NCI_RF_PROTOCOL_T3T)
		protocol = NFC_PROTO_FELICA_MASK;
	अन्यथा अगर (rf_protocol == NCI_RF_PROTOCOL_NFC_DEP)
		protocol = NFC_PROTO_NFC_DEP_MASK;
	अन्यथा अगर (rf_protocol == NCI_RF_PROTOCOL_T5T)
		protocol = NFC_PROTO_ISO15693_MASK;
	अन्यथा
		protocol = nci_get_prop_rf_protocol(ndev, rf_protocol);

	अगर (!(protocol & ndev->poll_prots)) अणु
		pr_err("the target found does not have the desired protocol\n");
		वापस -EPROTO;
	पूर्ण

	अगर (rf_tech_and_mode == NCI_NFC_A_PASSIVE_POLL_MODE) अणु
		nfca_poll = (काष्ठा rf_tech_specअगरic_params_nfca_poll *)params;

		target->sens_res = nfca_poll->sens_res;
		target->sel_res = nfca_poll->sel_res;
		target->nfcid1_len = nfca_poll->nfcid1_len;
		अगर (target->nfcid1_len > 0) अणु
			स_नकल(target->nfcid1, nfca_poll->nfcid1,
			       target->nfcid1_len);
		पूर्ण
	पूर्ण अन्यथा अगर (rf_tech_and_mode == NCI_NFC_B_PASSIVE_POLL_MODE) अणु
		nfcb_poll = (काष्ठा rf_tech_specअगरic_params_nfcb_poll *)params;

		target->sensb_res_len = nfcb_poll->sensb_res_len;
		अगर (target->sensb_res_len > 0) अणु
			स_नकल(target->sensb_res, nfcb_poll->sensb_res,
			       target->sensb_res_len);
		पूर्ण
	पूर्ण अन्यथा अगर (rf_tech_and_mode == NCI_NFC_F_PASSIVE_POLL_MODE) अणु
		nfcf_poll = (काष्ठा rf_tech_specअगरic_params_nfcf_poll *)params;

		target->sensf_res_len = nfcf_poll->sensf_res_len;
		अगर (target->sensf_res_len > 0) अणु
			स_नकल(target->sensf_res, nfcf_poll->sensf_res,
			       target->sensf_res_len);
		पूर्ण
	पूर्ण अन्यथा अगर (rf_tech_and_mode == NCI_NFC_V_PASSIVE_POLL_MODE) अणु
		nfcv_poll = (काष्ठा rf_tech_specअगरic_params_nfcv_poll *)params;

		target->is_iso15693 = 1;
		target->iso15693_dsfid = nfcv_poll->dsfid;
		स_नकल(target->iso15693_uid, nfcv_poll->uid, NFC_ISO15693_UID_MAXSIZE);
	पूर्ण अन्यथा अणु
		pr_err("unsupported rf_tech_and_mode 0x%x\n", rf_tech_and_mode);
		वापस -EPROTO;
	पूर्ण

	target->supported_protocols |= protocol;

	pr_debug("protocol 0x%x\n", protocol);

	वापस 0;
पूर्ण

अटल व्योम nci_add_new_target(काष्ठा nci_dev *ndev,
			       काष्ठा nci_rf_discover_ntf *ntf)
अणु
	काष्ठा nfc_target *target;
	पूर्णांक i, rc;

	क्रम (i = 0; i < ndev->n_tarमाला_लो; i++) अणु
		target = &ndev->tarमाला_लो[i];
		अगर (target->logical_idx == ntf->rf_discovery_id) अणु
			/* This target alपढ़ोy exists, add the new protocol */
			nci_add_new_protocol(ndev, target, ntf->rf_protocol,
					     ntf->rf_tech_and_mode,
					     &ntf->rf_tech_specअगरic_params);
			वापस;
		पूर्ण
	पूर्ण

	/* This is a new target, check अगर we've enough room */
	अगर (ndev->n_tarमाला_लो == NCI_MAX_DISCOVERED_TARGETS) अणु
		pr_debug("not enough room, ignoring new target...\n");
		वापस;
	पूर्ण

	target = &ndev->tarमाला_लो[ndev->n_tarमाला_लो];

	rc = nci_add_new_protocol(ndev, target, ntf->rf_protocol,
				  ntf->rf_tech_and_mode,
				  &ntf->rf_tech_specअगरic_params);
	अगर (!rc) अणु
		target->logical_idx = ntf->rf_discovery_id;
		ndev->n_tarमाला_लो++;

		pr_debug("logical idx %d, n_targets %d\n", target->logical_idx,
			 ndev->n_tarमाला_लो);
	पूर्ण
पूर्ण

व्योम nci_clear_target_list(काष्ठा nci_dev *ndev)
अणु
	स_रखो(ndev->tarमाला_लो, 0,
	       (माप(काष्ठा nfc_target)*NCI_MAX_DISCOVERED_TARGETS));

	ndev->n_tarमाला_लो = 0;
पूर्ण

अटल व्योम nci_rf_discover_ntf_packet(काष्ठा nci_dev *ndev,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_rf_discover_ntf ntf;
	__u8 *data = skb->data;
	bool add_target = true;

	ntf.rf_discovery_id = *data++;
	ntf.rf_protocol = *data++;
	ntf.rf_tech_and_mode = *data++;
	ntf.rf_tech_specअगरic_params_len = *data++;

	pr_debug("rf_discovery_id %d\n", ntf.rf_discovery_id);
	pr_debug("rf_protocol 0x%x\n", ntf.rf_protocol);
	pr_debug("rf_tech_and_mode 0x%x\n", ntf.rf_tech_and_mode);
	pr_debug("rf_tech_specific_params_len %d\n",
		 ntf.rf_tech_specअगरic_params_len);

	अगर (ntf.rf_tech_specअगरic_params_len > 0) अणु
		चयन (ntf.rf_tech_and_mode) अणु
		हाल NCI_NFC_A_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfca_passive_poll(ndev,
				&(ntf.rf_tech_specअगरic_params.nfca_poll), data);
			अवरोध;

		हाल NCI_NFC_B_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcb_passive_poll(ndev,
				&(ntf.rf_tech_specअगरic_params.nfcb_poll), data);
			अवरोध;

		हाल NCI_NFC_F_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcf_passive_poll(ndev,
				&(ntf.rf_tech_specअगरic_params.nfcf_poll), data);
			अवरोध;

		हाल NCI_NFC_V_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcv_passive_poll(ndev,
				&(ntf.rf_tech_specअगरic_params.nfcv_poll), data);
			अवरोध;

		शेष:
			pr_err("unsupported rf_tech_and_mode 0x%x\n",
			       ntf.rf_tech_and_mode);
			data += ntf.rf_tech_specअगरic_params_len;
			add_target = false;
		पूर्ण
	पूर्ण

	ntf.ntf_type = *data++;
	pr_debug("ntf_type %d\n", ntf.ntf_type);

	अगर (add_target == true)
		nci_add_new_target(ndev, &ntf);

	अगर (ntf.ntf_type == NCI_DISCOVER_NTF_TYPE_MORE) अणु
		atomic_set(&ndev->state, NCI_W4_ALL_DISCOVERIES);
	पूर्ण अन्यथा अणु
		atomic_set(&ndev->state, NCI_W4_HOST_SELECT);
		nfc_tarमाला_लो_found(ndev->nfc_dev, ndev->tarमाला_लो,
				  ndev->n_tarमाला_लो);
	पूर्ण
पूर्ण

अटल पूर्णांक nci_extract_activation_params_iso_dep(काष्ठा nci_dev *ndev,
			काष्ठा nci_rf_पूर्णांकf_activated_ntf *ntf, __u8 *data)
अणु
	काष्ठा activation_params_nfca_poll_iso_dep *nfca_poll;
	काष्ठा activation_params_nfcb_poll_iso_dep *nfcb_poll;

	चयन (ntf->activation_rf_tech_and_mode) अणु
	हाल NCI_NFC_A_PASSIVE_POLL_MODE:
		nfca_poll = &ntf->activation_params.nfca_poll_iso_dep;
		nfca_poll->rats_res_len = min_t(__u8, *data++, 20);
		pr_debug("rats_res_len %d\n", nfca_poll->rats_res_len);
		अगर (nfca_poll->rats_res_len > 0) अणु
			स_नकल(nfca_poll->rats_res,
			       data, nfca_poll->rats_res_len);
		पूर्ण
		अवरोध;

	हाल NCI_NFC_B_PASSIVE_POLL_MODE:
		nfcb_poll = &ntf->activation_params.nfcb_poll_iso_dep;
		nfcb_poll->attrib_res_len = min_t(__u8, *data++, 50);
		pr_debug("attrib_res_len %d\n", nfcb_poll->attrib_res_len);
		अगर (nfcb_poll->attrib_res_len > 0) अणु
			स_नकल(nfcb_poll->attrib_res,
			       data, nfcb_poll->attrib_res_len);
		पूर्ण
		अवरोध;

	शेष:
		pr_err("unsupported activation_rf_tech_and_mode 0x%x\n",
		       ntf->activation_rf_tech_and_mode);
		वापस NCI_STATUS_RF_PROTOCOL_ERROR;
	पूर्ण

	वापस NCI_STATUS_OK;
पूर्ण

अटल पूर्णांक nci_extract_activation_params_nfc_dep(काष्ठा nci_dev *ndev,
			काष्ठा nci_rf_पूर्णांकf_activated_ntf *ntf, __u8 *data)
अणु
	काष्ठा activation_params_poll_nfc_dep *poll;
	काष्ठा activation_params_listen_nfc_dep *listen;

	चयन (ntf->activation_rf_tech_and_mode) अणु
	हाल NCI_NFC_A_PASSIVE_POLL_MODE:
	हाल NCI_NFC_F_PASSIVE_POLL_MODE:
		poll = &ntf->activation_params.poll_nfc_dep;
		poll->atr_res_len = min_t(__u8, *data++,
					  NFC_ATR_RES_MAXSIZE - 2);
		pr_debug("atr_res_len %d\n", poll->atr_res_len);
		अगर (poll->atr_res_len > 0)
			स_नकल(poll->atr_res, data, poll->atr_res_len);
		अवरोध;

	हाल NCI_NFC_A_PASSIVE_LISTEN_MODE:
	हाल NCI_NFC_F_PASSIVE_LISTEN_MODE:
		listen = &ntf->activation_params.listen_nfc_dep;
		listen->atr_req_len = min_t(__u8, *data++,
					    NFC_ATR_REQ_MAXSIZE - 2);
		pr_debug("atr_req_len %d\n", listen->atr_req_len);
		अगर (listen->atr_req_len > 0)
			स_नकल(listen->atr_req, data, listen->atr_req_len);
		अवरोध;

	शेष:
		pr_err("unsupported activation_rf_tech_and_mode 0x%x\n",
		       ntf->activation_rf_tech_and_mode);
		वापस NCI_STATUS_RF_PROTOCOL_ERROR;
	पूर्ण

	वापस NCI_STATUS_OK;
पूर्ण

अटल व्योम nci_target_स्वतः_activated(काष्ठा nci_dev *ndev,
				      काष्ठा nci_rf_पूर्णांकf_activated_ntf *ntf)
अणु
	काष्ठा nfc_target *target;
	पूर्णांक rc;

	target = &ndev->tarमाला_लो[ndev->n_tarमाला_लो];

	rc = nci_add_new_protocol(ndev, target, ntf->rf_protocol,
				  ntf->activation_rf_tech_and_mode,
				  &ntf->rf_tech_specअगरic_params);
	अगर (rc)
		वापस;

	target->logical_idx = ntf->rf_discovery_id;
	ndev->n_tarमाला_लो++;

	pr_debug("logical idx %d, n_targets %d\n",
		 target->logical_idx, ndev->n_tarमाला_लो);

	nfc_tarमाला_लो_found(ndev->nfc_dev, ndev->tarमाला_लो, ndev->n_tarमाला_लो);
पूर्ण

अटल पूर्णांक nci_store_general_bytes_nfc_dep(काष्ठा nci_dev *ndev,
		काष्ठा nci_rf_पूर्णांकf_activated_ntf *ntf)
अणु
	ndev->remote_gb_len = 0;

	अगर (ntf->activation_params_len <= 0)
		वापस NCI_STATUS_OK;

	चयन (ntf->activation_rf_tech_and_mode) अणु
	हाल NCI_NFC_A_PASSIVE_POLL_MODE:
	हाल NCI_NFC_F_PASSIVE_POLL_MODE:
		ndev->remote_gb_len = min_t(__u8,
			(ntf->activation_params.poll_nfc_dep.atr_res_len
						- NFC_ATR_RES_GT_OFFSET),
			NFC_ATR_RES_GB_MAXSIZE);
		स_नकल(ndev->remote_gb,
		       (ntf->activation_params.poll_nfc_dep.atr_res
						+ NFC_ATR_RES_GT_OFFSET),
		       ndev->remote_gb_len);
		अवरोध;

	हाल NCI_NFC_A_PASSIVE_LISTEN_MODE:
	हाल NCI_NFC_F_PASSIVE_LISTEN_MODE:
		ndev->remote_gb_len = min_t(__u8,
			(ntf->activation_params.listen_nfc_dep.atr_req_len
						- NFC_ATR_REQ_GT_OFFSET),
			NFC_ATR_REQ_GB_MAXSIZE);
		स_नकल(ndev->remote_gb,
		       (ntf->activation_params.listen_nfc_dep.atr_req
						+ NFC_ATR_REQ_GT_OFFSET),
		       ndev->remote_gb_len);
		अवरोध;

	शेष:
		pr_err("unsupported activation_rf_tech_and_mode 0x%x\n",
		       ntf->activation_rf_tech_and_mode);
		वापस NCI_STATUS_RF_PROTOCOL_ERROR;
	पूर्ण

	वापस NCI_STATUS_OK;
पूर्ण

अटल व्योम nci_rf_पूर्णांकf_activated_ntf_packet(काष्ठा nci_dev *ndev,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_conn_info    *conn_info;
	काष्ठा nci_rf_पूर्णांकf_activated_ntf ntf;
	__u8 *data = skb->data;
	पूर्णांक err = NCI_STATUS_OK;

	ntf.rf_discovery_id = *data++;
	ntf.rf_पूर्णांकerface = *data++;
	ntf.rf_protocol = *data++;
	ntf.activation_rf_tech_and_mode = *data++;
	ntf.max_data_pkt_payload_size = *data++;
	ntf.initial_num_credits = *data++;
	ntf.rf_tech_specअगरic_params_len = *data++;

	pr_debug("rf_discovery_id %d\n", ntf.rf_discovery_id);
	pr_debug("rf_interface 0x%x\n", ntf.rf_पूर्णांकerface);
	pr_debug("rf_protocol 0x%x\n", ntf.rf_protocol);
	pr_debug("activation_rf_tech_and_mode 0x%x\n",
		 ntf.activation_rf_tech_and_mode);
	pr_debug("max_data_pkt_payload_size 0x%x\n",
		 ntf.max_data_pkt_payload_size);
	pr_debug("initial_num_credits 0x%x\n",
		 ntf.initial_num_credits);
	pr_debug("rf_tech_specific_params_len %d\n",
		 ntf.rf_tech_specअगरic_params_len);

	/* If this contains a value of 0x00 (NFCEE Direct RF
	 * Interface) then all following parameters SHALL contain a
	 * value of 0 and SHALL be ignored.
	 */
	अगर (ntf.rf_पूर्णांकerface == NCI_RF_INTERFACE_NFCEE_सूचीECT)
		जाओ listen;

	अगर (ntf.rf_tech_specअगरic_params_len > 0) अणु
		चयन (ntf.activation_rf_tech_and_mode) अणु
		हाल NCI_NFC_A_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfca_passive_poll(ndev,
				&(ntf.rf_tech_specअगरic_params.nfca_poll), data);
			अवरोध;

		हाल NCI_NFC_B_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcb_passive_poll(ndev,
				&(ntf.rf_tech_specअगरic_params.nfcb_poll), data);
			अवरोध;

		हाल NCI_NFC_F_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcf_passive_poll(ndev,
				&(ntf.rf_tech_specअगरic_params.nfcf_poll), data);
			अवरोध;

		हाल NCI_NFC_V_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcv_passive_poll(ndev,
				&(ntf.rf_tech_specअगरic_params.nfcv_poll), data);
			अवरोध;

		हाल NCI_NFC_A_PASSIVE_LISTEN_MODE:
			/* no RF technology specअगरic parameters */
			अवरोध;

		हाल NCI_NFC_F_PASSIVE_LISTEN_MODE:
			data = nci_extract_rf_params_nfcf_passive_listen(ndev,
				&(ntf.rf_tech_specअगरic_params.nfcf_listen),
				data);
			अवरोध;

		शेष:
			pr_err("unsupported activation_rf_tech_and_mode 0x%x\n",
			       ntf.activation_rf_tech_and_mode);
			err = NCI_STATUS_RF_PROTOCOL_ERROR;
			जाओ निकास;
		पूर्ण
	पूर्ण

	ntf.data_exch_rf_tech_and_mode = *data++;
	ntf.data_exch_tx_bit_rate = *data++;
	ntf.data_exch_rx_bit_rate = *data++;
	ntf.activation_params_len = *data++;

	pr_debug("data_exch_rf_tech_and_mode 0x%x\n",
		 ntf.data_exch_rf_tech_and_mode);
	pr_debug("data_exch_tx_bit_rate 0x%x\n", ntf.data_exch_tx_bit_rate);
	pr_debug("data_exch_rx_bit_rate 0x%x\n", ntf.data_exch_rx_bit_rate);
	pr_debug("activation_params_len %d\n", ntf.activation_params_len);

	अगर (ntf.activation_params_len > 0) अणु
		चयन (ntf.rf_पूर्णांकerface) अणु
		हाल NCI_RF_INTERFACE_ISO_DEP:
			err = nci_extract_activation_params_iso_dep(ndev,
								    &ntf, data);
			अवरोध;

		हाल NCI_RF_INTERFACE_NFC_DEP:
			err = nci_extract_activation_params_nfc_dep(ndev,
								    &ntf, data);
			अवरोध;

		हाल NCI_RF_INTERFACE_FRAME:
			/* no activation params */
			अवरोध;

		शेष:
			pr_err("unsupported rf_interface 0x%x\n",
			       ntf.rf_पूर्णांकerface);
			err = NCI_STATUS_RF_PROTOCOL_ERROR;
			अवरोध;
		पूर्ण
	पूर्ण

निकास:
	अगर (err == NCI_STATUS_OK) अणु
		conn_info = ndev->rf_conn_info;
		अगर (!conn_info)
			वापस;

		conn_info->max_pkt_payload_len = ntf.max_data_pkt_payload_size;
		conn_info->initial_num_credits = ntf.initial_num_credits;

		/* set the available credits to initial value */
		atomic_set(&conn_info->credits_cnt,
			   conn_info->initial_num_credits);

		/* store general bytes to be reported later in dep_link_up */
		अगर (ntf.rf_पूर्णांकerface == NCI_RF_INTERFACE_NFC_DEP) अणु
			err = nci_store_general_bytes_nfc_dep(ndev, &ntf);
			अगर (err != NCI_STATUS_OK)
				pr_err("unable to store general bytes\n");
		पूर्ण
	पूर्ण

	अगर (!(ntf.activation_rf_tech_and_mode & NCI_RF_TECH_MODE_LISTEN_MASK)) अणु
		/* Poll mode */
		अगर (atomic_पढ़ो(&ndev->state) == NCI_DISCOVERY) अणु
			/* A single target was found and activated
			 * स्वतःmatically */
			atomic_set(&ndev->state, NCI_POLL_ACTIVE);
			अगर (err == NCI_STATUS_OK)
				nci_target_स्वतः_activated(ndev, &ntf);
		पूर्ण अन्यथा अणु	/* ndev->state == NCI_W4_HOST_SELECT */
			/* A selected target was activated, so complete the
			 * request */
			atomic_set(&ndev->state, NCI_POLL_ACTIVE);
			nci_req_complete(ndev, err);
		पूर्ण
	पूर्ण अन्यथा अणु
listen:
		/* Listen mode */
		atomic_set(&ndev->state, NCI_LISTEN_ACTIVE);
		अगर (err == NCI_STATUS_OK &&
		    ntf.rf_protocol == NCI_RF_PROTOCOL_NFC_DEP) अणु
			err = nfc_पंचांग_activated(ndev->nfc_dev,
					       NFC_PROTO_NFC_DEP_MASK,
					       NFC_COMM_PASSIVE,
					       ndev->remote_gb,
					       ndev->remote_gb_len);
			अगर (err != NCI_STATUS_OK)
				pr_err("error when signaling tm activation\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nci_rf_deactivate_ntf_packet(काष्ठा nci_dev *ndev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_conn_info    *conn_info;
	काष्ठा nci_rf_deactivate_ntf *ntf = (व्योम *) skb->data;

	pr_debug("entry, type 0x%x, reason 0x%x\n", ntf->type, ntf->reason);

	conn_info = ndev->rf_conn_info;
	अगर (!conn_info)
		वापस;

	/* drop tx data queue */
	skb_queue_purge(&ndev->tx_q);

	/* drop partial rx data packet */
	अगर (ndev->rx_data_reassembly) अणु
		kमुक्त_skb(ndev->rx_data_reassembly);
		ndev->rx_data_reassembly = शून्य;
	पूर्ण

	/* complete the data exchange transaction, अगर exists */
	अगर (test_bit(NCI_DATA_EXCHANGE, &ndev->flags))
		nci_data_exchange_complete(ndev, शून्य, NCI_STATIC_RF_CONN_ID,
					   -EIO);

	चयन (ntf->type) अणु
	हाल NCI_DEACTIVATE_TYPE_IDLE_MODE:
		nci_clear_target_list(ndev);
		atomic_set(&ndev->state, NCI_IDLE);
		अवरोध;
	हाल NCI_DEACTIVATE_TYPE_SLEEP_MODE:
	हाल NCI_DEACTIVATE_TYPE_SLEEP_AF_MODE:
		atomic_set(&ndev->state, NCI_W4_HOST_SELECT);
		अवरोध;
	हाल NCI_DEACTIVATE_TYPE_DISCOVERY:
		nci_clear_target_list(ndev);
		atomic_set(&ndev->state, NCI_DISCOVERY);
		अवरोध;
	पूर्ण

	nci_req_complete(ndev, NCI_STATUS_OK);
पूर्ण

अटल व्योम nci_nfcee_discover_ntf_packet(काष्ठा nci_dev *ndev,
					  काष्ठा sk_buff *skb)
अणु
	u8 status = NCI_STATUS_OK;
	काष्ठा nci_nfcee_discover_ntf   *nfcee_ntf =
				(काष्ठा nci_nfcee_discover_ntf *)skb->data;

	pr_debug("\n");

	/* NFCForum NCI 9.2.1 HCI Network Specअगरic Handling
	 * If the NFCC supports the HCI Network, it SHALL वापस one,
	 * and only one, NFCEE_DISCOVER_NTF with a Protocol type of
	 * ै HCI Accessै , even अगर the HCI Network contains multiple NFCEEs.
	 */
	ndev->hci_dev->nfcee_id = nfcee_ntf->nfcee_id;
	ndev->cur_params.id = nfcee_ntf->nfcee_id;

	nci_req_complete(ndev, status);
पूर्ण

अटल व्योम nci_nfcee_action_ntf_packet(काष्ठा nci_dev *ndev,
					काष्ठा sk_buff *skb)
अणु
	pr_debug("\n");
पूर्ण

व्योम nci_ntf_packet(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	__u16 ntf_opcode = nci_opcode(skb->data);

	pr_debug("NCI RX: MT=ntf, PBF=%d, GID=0x%x, OID=0x%x, plen=%d\n",
		 nci_pbf(skb->data),
		 nci_opcode_gid(ntf_opcode),
		 nci_opcode_oid(ntf_opcode),
		 nci_plen(skb->data));

	/* strip the nci control header */
	skb_pull(skb, NCI_CTRL_HDR_SIZE);

	अगर (nci_opcode_gid(ntf_opcode) == NCI_GID_PROPRIETARY) अणु
		अगर (nci_prop_ntf_packet(ndev, ntf_opcode, skb) == -ENOTSUPP) अणु
			pr_err("unsupported ntf opcode 0x%x\n",
			       ntf_opcode);
		पूर्ण

		जाओ end;
	पूर्ण

	चयन (ntf_opcode) अणु
	हाल NCI_OP_CORE_RESET_NTF:
		nci_core_reset_ntf_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_CORE_CONN_CREDITS_NTF:
		nci_core_conn_credits_ntf_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_CORE_GENERIC_ERROR_NTF:
		nci_core_generic_error_ntf_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_CORE_INTF_ERROR_NTF:
		nci_core_conn_पूर्णांकf_error_ntf_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_RF_DISCOVER_NTF:
		nci_rf_discover_ntf_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_RF_INTF_ACTIVATED_NTF:
		nci_rf_पूर्णांकf_activated_ntf_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_RF_DEACTIVATE_NTF:
		nci_rf_deactivate_ntf_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_NFCEE_DISCOVER_NTF:
		nci_nfcee_discover_ntf_packet(ndev, skb);
		अवरोध;

	हाल NCI_OP_RF_NFCEE_ACTION_NTF:
		nci_nfcee_action_ntf_packet(ndev, skb);
		अवरोध;

	शेष:
		pr_err("unknown ntf opcode 0x%x\n", ntf_opcode);
		अवरोध;
	पूर्ण

	nci_core_ntf_packet(ndev, ntf_opcode, skb);
end:
	kमुक्त_skb(skb);
पूर्ण
