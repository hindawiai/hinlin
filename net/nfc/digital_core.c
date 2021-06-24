<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NFC Digital Protocol stack
 * Copyright (c) 2013, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) "digital: %s: " fmt, __func__

#समावेश <linux/module.h>

#समावेश "digital.h"

#घोषणा DIGITAL_PROTO_NFCA_RF_TECH \
	(NFC_PROTO_JEWEL_MASK | NFC_PROTO_MIFARE_MASK | \
	NFC_PROTO_NFC_DEP_MASK | NFC_PROTO_ISO14443_MASK)

#घोषणा DIGITAL_PROTO_NFCB_RF_TECH	NFC_PROTO_ISO14443_B_MASK

#घोषणा DIGITAL_PROTO_NFCF_RF_TECH \
	(NFC_PROTO_FELICA_MASK | NFC_PROTO_NFC_DEP_MASK)

#घोषणा DIGITAL_PROTO_ISO15693_RF_TECH	NFC_PROTO_ISO15693_MASK

/* Delay between each poll frame (ms) */
#घोषणा DIGITAL_POLL_INTERVAL 10

काष्ठा digital_cmd अणु
	काष्ठा list_head queue;

	u8 type;
	u8 pending;

	u16 समयout;
	काष्ठा sk_buff *req;
	काष्ठा sk_buff *resp;
	काष्ठा digital_tg_mdaa_params *mdaa_params;

	nfc_digital_cmd_complete_t cmd_cb;
	व्योम *cb_context;
पूर्ण;

काष्ठा sk_buff *digital_skb_alloc(काष्ठा nfc_digital_dev *ddev,
				  अचिन्हित पूर्णांक len)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(len + ddev->tx_headroom + ddev->tx_tailroom,
			GFP_KERNEL);
	अगर (skb)
		skb_reserve(skb, ddev->tx_headroom);

	वापस skb;
पूर्ण

व्योम digital_skb_add_crc(काष्ठा sk_buff *skb, crc_func_t crc_func, u16 init,
			 u8 bitwise_inv, u8 msb_first)
अणु
	u16 crc;

	crc = crc_func(init, skb->data, skb->len);

	अगर (bitwise_inv)
		crc = ~crc;

	अगर (msb_first)
		crc = __fswab16(crc);

	skb_put_u8(skb, crc & 0xFF);
	skb_put_u8(skb, (crc >> 8) & 0xFF);
पूर्ण

पूर्णांक digital_skb_check_crc(काष्ठा sk_buff *skb, crc_func_t crc_func,
			  u16 crc_init, u8 bitwise_inv, u8 msb_first)
अणु
	पूर्णांक rc;
	u16 crc;

	अगर (skb->len <= 2)
		वापस -EIO;

	crc = crc_func(crc_init, skb->data, skb->len - 2);

	अगर (bitwise_inv)
		crc = ~crc;

	अगर (msb_first)
		crc = __swab16(crc);

	rc = (skb->data[skb->len - 2] - (crc & 0xFF)) +
	     (skb->data[skb->len - 1] - ((crc >> 8) & 0xFF));

	अगर (rc)
		वापस -EIO;

	skb_trim(skb, skb->len - 2);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम digital_चयन_rf(काष्ठा nfc_digital_dev *ddev, bool on)
अणु
	ddev->ops->चयन_rf(ddev, on);
पूर्ण

अटल अंतरभूत व्योम digital_पात_cmd(काष्ठा nfc_digital_dev *ddev)
अणु
	ddev->ops->पात_cmd(ddev);
पूर्ण

अटल व्योम digital_wq_cmd_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा digital_cmd *cmd;
	काष्ठा nfc_digital_dev *ddev = container_of(work,
						    काष्ठा nfc_digital_dev,
						    cmd_complete_work);

	mutex_lock(&ddev->cmd_lock);

	cmd = list_first_entry_or_null(&ddev->cmd_queue, काष्ठा digital_cmd,
				       queue);
	अगर (!cmd) अणु
		mutex_unlock(&ddev->cmd_lock);
		वापस;
	पूर्ण

	list_del(&cmd->queue);

	mutex_unlock(&ddev->cmd_lock);

	अगर (!IS_ERR(cmd->resp))
		prपूर्णांक_hex_dump_debug("DIGITAL RX: ", DUMP_PREFIX_NONE, 16, 1,
				     cmd->resp->data, cmd->resp->len, false);

	cmd->cmd_cb(ddev, cmd->cb_context, cmd->resp);

	kमुक्त(cmd->mdaa_params);
	kमुक्त(cmd);

	schedule_work(&ddev->cmd_work);
पूर्ण

अटल व्योम digital_send_cmd_complete(काष्ठा nfc_digital_dev *ddev,
				      व्योम *arg, काष्ठा sk_buff *resp)
अणु
	काष्ठा digital_cmd *cmd = arg;

	cmd->resp = resp;

	schedule_work(&ddev->cmd_complete_work);
पूर्ण

अटल व्योम digital_wq_cmd(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक rc;
	काष्ठा digital_cmd *cmd;
	काष्ठा digital_tg_mdaa_params *params;
	काष्ठा nfc_digital_dev *ddev = container_of(work,
						    काष्ठा nfc_digital_dev,
						    cmd_work);

	mutex_lock(&ddev->cmd_lock);

	cmd = list_first_entry_or_null(&ddev->cmd_queue, काष्ठा digital_cmd,
				       queue);
	अगर (!cmd || cmd->pending) अणु
		mutex_unlock(&ddev->cmd_lock);
		वापस;
	पूर्ण

	cmd->pending = 1;

	mutex_unlock(&ddev->cmd_lock);

	अगर (cmd->req)
		prपूर्णांक_hex_dump_debug("DIGITAL TX: ", DUMP_PREFIX_NONE, 16, 1,
				     cmd->req->data, cmd->req->len, false);

	चयन (cmd->type) अणु
	हाल DIGITAL_CMD_IN_SEND:
		rc = ddev->ops->in_send_cmd(ddev, cmd->req, cmd->समयout,
					    digital_send_cmd_complete, cmd);
		अवरोध;

	हाल DIGITAL_CMD_TG_SEND:
		rc = ddev->ops->tg_send_cmd(ddev, cmd->req, cmd->समयout,
					    digital_send_cmd_complete, cmd);
		अवरोध;

	हाल DIGITAL_CMD_TG_LISTEN:
		rc = ddev->ops->tg_listen(ddev, cmd->समयout,
					  digital_send_cmd_complete, cmd);
		अवरोध;

	हाल DIGITAL_CMD_TG_LISTEN_MDAA:
		params = cmd->mdaa_params;

		rc = ddev->ops->tg_listen_mdaa(ddev, params, cmd->समयout,
					       digital_send_cmd_complete, cmd);
		अवरोध;

	हाल DIGITAL_CMD_TG_LISTEN_MD:
		rc = ddev->ops->tg_listen_md(ddev, cmd->समयout,
					       digital_send_cmd_complete, cmd);
		अवरोध;

	शेष:
		pr_err("Unknown cmd type %d\n", cmd->type);
		वापस;
	पूर्ण

	अगर (!rc)
		वापस;

	pr_err("in_send_command returned err %d\n", rc);

	mutex_lock(&ddev->cmd_lock);
	list_del(&cmd->queue);
	mutex_unlock(&ddev->cmd_lock);

	kमुक्त_skb(cmd->req);
	kमुक्त(cmd->mdaa_params);
	kमुक्त(cmd);

	schedule_work(&ddev->cmd_work);
पूर्ण

पूर्णांक digital_send_cmd(काष्ठा nfc_digital_dev *ddev, u8 cmd_type,
		     काष्ठा sk_buff *skb, काष्ठा digital_tg_mdaa_params *params,
		     u16 समयout, nfc_digital_cmd_complete_t cmd_cb,
		     व्योम *cb_context)
अणु
	काष्ठा digital_cmd *cmd;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->type = cmd_type;
	cmd->समयout = समयout;
	cmd->req = skb;
	cmd->mdaa_params = params;
	cmd->cmd_cb = cmd_cb;
	cmd->cb_context = cb_context;
	INIT_LIST_HEAD(&cmd->queue);

	mutex_lock(&ddev->cmd_lock);
	list_add_tail(&cmd->queue, &ddev->cmd_queue);
	mutex_unlock(&ddev->cmd_lock);

	schedule_work(&ddev->cmd_work);

	वापस 0;
पूर्ण

पूर्णांक digital_in_configure_hw(काष्ठा nfc_digital_dev *ddev, पूर्णांक type, पूर्णांक param)
अणु
	पूर्णांक rc;

	rc = ddev->ops->in_configure_hw(ddev, type, param);
	अगर (rc)
		pr_err("in_configure_hw failed: %d\n", rc);

	वापस rc;
पूर्ण

पूर्णांक digital_tg_configure_hw(काष्ठा nfc_digital_dev *ddev, पूर्णांक type, पूर्णांक param)
अणु
	पूर्णांक rc;

	rc = ddev->ops->tg_configure_hw(ddev, type, param);
	अगर (rc)
		pr_err("tg_configure_hw failed: %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक digital_tg_listen_mdaa(काष्ठा nfc_digital_dev *ddev, u8 rf_tech)
अणु
	काष्ठा digital_tg_mdaa_params *params;

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	params->sens_res = DIGITAL_SENS_RES_NFC_DEP;
	get_अक्रमom_bytes(params->nfcid1, माप(params->nfcid1));
	params->sel_res = DIGITAL_SEL_RES_NFC_DEP;

	params->nfcid2[0] = DIGITAL_SENSF_NFCID2_NFC_DEP_B1;
	params->nfcid2[1] = DIGITAL_SENSF_NFCID2_NFC_DEP_B2;
	get_अक्रमom_bytes(params->nfcid2 + 2, NFC_NFCID2_MAXSIZE - 2);
	params->sc = DIGITAL_SENSF_FELICA_SC;

	वापस digital_send_cmd(ddev, DIGITAL_CMD_TG_LISTEN_MDAA, शून्य, params,
				500, digital_tg_recv_atr_req, शून्य);
पूर्ण

अटल पूर्णांक digital_tg_listen_md(काष्ठा nfc_digital_dev *ddev, u8 rf_tech)
अणु
	वापस digital_send_cmd(ddev, DIGITAL_CMD_TG_LISTEN_MD, शून्य, शून्य, 500,
				digital_tg_recv_md_req, शून्य);
पूर्ण

पूर्णांक digital_target_found(काष्ठा nfc_digital_dev *ddev,
			 काष्ठा nfc_target *target, u8 protocol)
अणु
	पूर्णांक rc;
	u8 framing;
	u8 rf_tech;
	u8 poll_tech_count;
	पूर्णांक (*check_crc)(काष्ठा sk_buff *skb);
	व्योम (*add_crc)(काष्ठा sk_buff *skb);

	rf_tech = ddev->poll_techs[ddev->poll_tech_index].rf_tech;

	चयन (protocol) अणु
	हाल NFC_PROTO_JEWEL:
		framing = NFC_DIGITAL_FRAMING_NFCA_T1T;
		check_crc = digital_skb_check_crc_b;
		add_crc = digital_skb_add_crc_b;
		अवरोध;

	हाल NFC_PROTO_MIFARE:
		framing = NFC_DIGITAL_FRAMING_NFCA_T2T;
		check_crc = digital_skb_check_crc_a;
		add_crc = digital_skb_add_crc_a;
		अवरोध;

	हाल NFC_PROTO_FELICA:
		framing = NFC_DIGITAL_FRAMING_NFCF_T3T;
		check_crc = digital_skb_check_crc_f;
		add_crc = digital_skb_add_crc_f;
		अवरोध;

	हाल NFC_PROTO_NFC_DEP:
		अगर (rf_tech == NFC_DIGITAL_RF_TECH_106A) अणु
			framing = NFC_DIGITAL_FRAMING_NFCA_NFC_DEP;
			check_crc = digital_skb_check_crc_a;
			add_crc = digital_skb_add_crc_a;
		पूर्ण अन्यथा अणु
			framing = NFC_DIGITAL_FRAMING_NFCF_NFC_DEP;
			check_crc = digital_skb_check_crc_f;
			add_crc = digital_skb_add_crc_f;
		पूर्ण
		अवरोध;

	हाल NFC_PROTO_ISO15693:
		framing = NFC_DIGITAL_FRAMING_ISO15693_T5T;
		check_crc = digital_skb_check_crc_b;
		add_crc = digital_skb_add_crc_b;
		अवरोध;

	हाल NFC_PROTO_ISO14443:
		framing = NFC_DIGITAL_FRAMING_NFCA_T4T;
		check_crc = digital_skb_check_crc_a;
		add_crc = digital_skb_add_crc_a;
		अवरोध;

	हाल NFC_PROTO_ISO14443_B:
		framing = NFC_DIGITAL_FRAMING_NFCB_T4T;
		check_crc = digital_skb_check_crc_b;
		add_crc = digital_skb_add_crc_b;
		अवरोध;

	शेष:
		pr_err("Invalid protocol %d\n", protocol);
		वापस -EINVAL;
	पूर्ण

	pr_debug("rf_tech=%d, protocol=%d\n", rf_tech, protocol);

	ddev->curr_rf_tech = rf_tech;

	अगर (DIGITAL_DRV_CAPS_IN_CRC(ddev)) अणु
		ddev->skb_add_crc = digital_skb_add_crc_none;
		ddev->skb_check_crc = digital_skb_check_crc_none;
	पूर्ण अन्यथा अणु
		ddev->skb_add_crc = add_crc;
		ddev->skb_check_crc = check_crc;
	पूर्ण

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING, framing);
	अगर (rc)
		वापस rc;

	target->supported_protocols = (1 << protocol);

	poll_tech_count = ddev->poll_tech_count;
	ddev->poll_tech_count = 0;

	rc = nfc_tarमाला_लो_found(ddev->nfc_dev, target, 1);
	अगर (rc) अणु
		ddev->poll_tech_count = poll_tech_count;
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

व्योम digital_poll_next_tech(काष्ठा nfc_digital_dev *ddev)
अणु
	u8 अक्रम_mod;

	digital_चयन_rf(ddev, 0);

	mutex_lock(&ddev->poll_lock);

	अगर (!ddev->poll_tech_count) अणु
		mutex_unlock(&ddev->poll_lock);
		वापस;
	पूर्ण

	get_अक्रमom_bytes(&अक्रम_mod, माप(अक्रम_mod));
	ddev->poll_tech_index = अक्रम_mod % ddev->poll_tech_count;

	mutex_unlock(&ddev->poll_lock);

	schedule_delayed_work(&ddev->poll_work,
			      msecs_to_jअगरfies(DIGITAL_POLL_INTERVAL));
पूर्ण

अटल व्योम digital_wq_poll(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक rc;
	काष्ठा digital_poll_tech *poll_tech;
	काष्ठा nfc_digital_dev *ddev = container_of(work,
						    काष्ठा nfc_digital_dev,
						    poll_work.work);
	mutex_lock(&ddev->poll_lock);

	अगर (!ddev->poll_tech_count) अणु
		mutex_unlock(&ddev->poll_lock);
		वापस;
	पूर्ण

	poll_tech = &ddev->poll_techs[ddev->poll_tech_index];

	mutex_unlock(&ddev->poll_lock);

	rc = poll_tech->poll_func(ddev, poll_tech->rf_tech);
	अगर (rc)
		digital_poll_next_tech(ddev);
पूर्ण

अटल व्योम digital_add_poll_tech(काष्ठा nfc_digital_dev *ddev, u8 rf_tech,
				  digital_poll_t poll_func)
अणु
	काष्ठा digital_poll_tech *poll_tech;

	अगर (ddev->poll_tech_count >= NFC_DIGITAL_POLL_MODE_COUNT_MAX)
		वापस;

	poll_tech = &ddev->poll_techs[ddev->poll_tech_count++];

	poll_tech->rf_tech = rf_tech;
	poll_tech->poll_func = poll_func;
पूर्ण

/**
 * digital_start_poll - start_poll operation
 * @nfc_dev: device to be polled
 * @im_protocols: bitset of nfc initiator protocols to be used क्रम polling
 * @पंचांग_protocols: bitset of nfc transport protocols to be used क्रम polling
 *
 * For every supported protocol, the corresponding polling function is added
 * to the table of polling technologies (ddev->poll_techs[]) using
 * digital_add_poll_tech().
 * When a polling function fails (by समयout or protocol error) the next one is
 * schedule by digital_poll_next_tech() on the poll workqueue (ddev->poll_work).
 */
अटल पूर्णांक digital_start_poll(काष्ठा nfc_dev *nfc_dev, __u32 im_protocols,
			      __u32 पंचांग_protocols)
अणु
	काष्ठा nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);
	u32 matching_im_protocols, matching_पंचांग_protocols;

	pr_debug("protocols: im 0x%x, tm 0x%x, supported 0x%x\n", im_protocols,
		 पंचांग_protocols, ddev->protocols);

	matching_im_protocols = ddev->protocols & im_protocols;
	matching_पंचांग_protocols = ddev->protocols & पंचांग_protocols;

	अगर (!matching_im_protocols && !matching_पंचांग_protocols) अणु
		pr_err("Unknown protocol\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ddev->poll_tech_count) अणु
		pr_err("Already polling\n");
		वापस -EBUSY;
	पूर्ण

	अगर (ddev->curr_protocol) अणु
		pr_err("A target is already active\n");
		वापस -EBUSY;
	पूर्ण

	ddev->poll_tech_count = 0;
	ddev->poll_tech_index = 0;

	अगर (matching_im_protocols & DIGITAL_PROTO_NFCA_RF_TECH)
		digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_106A,
				      digital_in_send_sens_req);

	अगर (matching_im_protocols & DIGITAL_PROTO_NFCB_RF_TECH)
		digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_106B,
				      digital_in_send_sensb_req);

	अगर (matching_im_protocols & DIGITAL_PROTO_NFCF_RF_TECH) अणु
		digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_212F,
				      digital_in_send_sensf_req);

		digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_424F,
				      digital_in_send_sensf_req);
	पूर्ण

	अगर (matching_im_protocols & DIGITAL_PROTO_ISO15693_RF_TECH)
		digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_ISO15693,
				      digital_in_send_iso15693_inv_req);

	अगर (matching_पंचांग_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
		अगर (ddev->ops->tg_listen_mdaa) अणु
			digital_add_poll_tech(ddev, 0,
					      digital_tg_listen_mdaa);
		पूर्ण अन्यथा अगर (ddev->ops->tg_listen_md) अणु
			digital_add_poll_tech(ddev, 0,
					      digital_tg_listen_md);
		पूर्ण अन्यथा अणु
			digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_106A,
					      digital_tg_listen_nfca);

			digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_212F,
					      digital_tg_listen_nfcf);

			digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_424F,
					      digital_tg_listen_nfcf);
		पूर्ण
	पूर्ण

	अगर (!ddev->poll_tech_count) अणु
		pr_err("Unsupported protocols: im=0x%x, tm=0x%x\n",
		       matching_im_protocols, matching_पंचांग_protocols);
		वापस -EINVAL;
	पूर्ण

	schedule_delayed_work(&ddev->poll_work, 0);

	वापस 0;
पूर्ण

अटल व्योम digital_stop_poll(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);

	mutex_lock(&ddev->poll_lock);

	अगर (!ddev->poll_tech_count) अणु
		pr_err("Polling operation was not running\n");
		mutex_unlock(&ddev->poll_lock);
		वापस;
	पूर्ण

	ddev->poll_tech_count = 0;

	mutex_unlock(&ddev->poll_lock);

	cancel_delayed_work_sync(&ddev->poll_work);

	digital_पात_cmd(ddev);
पूर्ण

अटल पूर्णांक digital_dev_up(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);

	digital_चयन_rf(ddev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक digital_dev_करोwn(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);

	digital_चयन_rf(ddev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक digital_dep_link_up(काष्ठा nfc_dev *nfc_dev,
			       काष्ठा nfc_target *target,
			       __u8 comm_mode, __u8 *gb, माप_प्रकार gb_len)
अणु
	काष्ठा nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);
	पूर्णांक rc;

	rc = digital_in_send_atr_req(ddev, target, comm_mode, gb, gb_len);

	अगर (!rc)
		ddev->curr_protocol = NFC_PROTO_NFC_DEP;

	वापस rc;
पूर्ण

अटल पूर्णांक digital_dep_link_करोwn(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);

	digital_पात_cmd(ddev);

	ddev->curr_protocol = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक digital_activate_target(काष्ठा nfc_dev *nfc_dev,
				   काष्ठा nfc_target *target, __u32 protocol)
अणु
	काष्ठा nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);

	अगर (ddev->poll_tech_count) अणु
		pr_err("Can't activate a target while polling\n");
		वापस -EBUSY;
	पूर्ण

	अगर (ddev->curr_protocol) अणु
		pr_err("A target is already active\n");
		वापस -EBUSY;
	पूर्ण

	ddev->curr_protocol = protocol;

	वापस 0;
पूर्ण

अटल व्योम digital_deactivate_target(काष्ठा nfc_dev *nfc_dev,
				      काष्ठा nfc_target *target,
				      u8 mode)
अणु
	काष्ठा nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);

	अगर (!ddev->curr_protocol) अणु
		pr_err("No active target\n");
		वापस;
	पूर्ण

	digital_पात_cmd(ddev);
	ddev->curr_protocol = 0;
पूर्ण

अटल पूर्णांक digital_tg_send(काष्ठा nfc_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_digital_dev *ddev = nfc_get_drvdata(dev);

	वापस digital_tg_send_dep_res(ddev, skb);
पूर्ण

अटल व्योम digital_in_send_complete(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				     काष्ठा sk_buff *resp)
अणु
	काष्ठा digital_data_exch *data_exch = arg;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ करोne;
	पूर्ण

	अगर (ddev->curr_protocol == NFC_PROTO_MIFARE) अणु
		rc = digital_in_recv_mअगरare_res(resp);
		/* crc check is करोne in digital_in_recv_mअगरare_res() */
		जाओ करोne;
	पूर्ण

	अगर ((ddev->curr_protocol == NFC_PROTO_ISO14443) ||
	    (ddev->curr_protocol == NFC_PROTO_ISO14443_B)) अणु
		rc = digital_in_iso_dep_pull_sod(ddev, resp);
		अगर (rc)
			जाओ करोne;
	पूर्ण

	rc = ddev->skb_check_crc(resp);

करोne:
	अगर (rc) अणु
		kमुक्त_skb(resp);
		resp = शून्य;
	पूर्ण

	data_exch->cb(data_exch->cb_context, resp, rc);

	kमुक्त(data_exch);
पूर्ण

अटल पूर्णांक digital_in_send(काष्ठा nfc_dev *nfc_dev, काष्ठा nfc_target *target,
			   काष्ठा sk_buff *skb, data_exchange_cb_t cb,
			   व्योम *cb_context)
अणु
	काष्ठा nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);
	काष्ठा digital_data_exch *data_exch;
	पूर्णांक rc;

	data_exch = kzalloc(माप(*data_exch), GFP_KERNEL);
	अगर (!data_exch)
		वापस -ENOMEM;

	data_exch->cb = cb;
	data_exch->cb_context = cb_context;

	अगर (ddev->curr_protocol == NFC_PROTO_NFC_DEP) अणु
		rc = digital_in_send_dep_req(ddev, target, skb, data_exch);
		जाओ निकास;
	पूर्ण

	अगर ((ddev->curr_protocol == NFC_PROTO_ISO14443) ||
	    (ddev->curr_protocol == NFC_PROTO_ISO14443_B)) अणु
		rc = digital_in_iso_dep_push_sod(ddev, skb);
		अगर (rc)
			जाओ निकास;
	पूर्ण

	ddev->skb_add_crc(skb);

	rc = digital_in_send_cmd(ddev, skb, 500, digital_in_send_complete,
				 data_exch);

निकास:
	अगर (rc)
		kमुक्त(data_exch);

	वापस rc;
पूर्ण

अटल काष्ठा nfc_ops digital_nfc_ops = अणु
	.dev_up = digital_dev_up,
	.dev_करोwn = digital_dev_करोwn,
	.start_poll = digital_start_poll,
	.stop_poll = digital_stop_poll,
	.dep_link_up = digital_dep_link_up,
	.dep_link_करोwn = digital_dep_link_करोwn,
	.activate_target = digital_activate_target,
	.deactivate_target = digital_deactivate_target,
	.पंचांग_send = digital_tg_send,
	.im_transceive = digital_in_send,
पूर्ण;

काष्ठा nfc_digital_dev *nfc_digital_allocate_device(काष्ठा nfc_digital_ops *ops,
					    __u32 supported_protocols,
					    __u32 driver_capabilities,
					    पूर्णांक tx_headroom, पूर्णांक tx_tailroom)
अणु
	काष्ठा nfc_digital_dev *ddev;

	अगर (!ops->in_configure_hw || !ops->in_send_cmd || !ops->tg_listen ||
	    !ops->tg_configure_hw || !ops->tg_send_cmd || !ops->पात_cmd ||
	    !ops->चयन_rf || (ops->tg_listen_md && !ops->tg_get_rf_tech))
		वापस शून्य;

	ddev = kzalloc(माप(*ddev), GFP_KERNEL);
	अगर (!ddev)
		वापस शून्य;

	ddev->driver_capabilities = driver_capabilities;
	ddev->ops = ops;

	mutex_init(&ddev->cmd_lock);
	INIT_LIST_HEAD(&ddev->cmd_queue);

	INIT_WORK(&ddev->cmd_work, digital_wq_cmd);
	INIT_WORK(&ddev->cmd_complete_work, digital_wq_cmd_complete);

	mutex_init(&ddev->poll_lock);
	INIT_DELAYED_WORK(&ddev->poll_work, digital_wq_poll);

	अगर (supported_protocols & NFC_PROTO_JEWEL_MASK)
		ddev->protocols |= NFC_PROTO_JEWEL_MASK;
	अगर (supported_protocols & NFC_PROTO_MIFARE_MASK)
		ddev->protocols |= NFC_PROTO_MIFARE_MASK;
	अगर (supported_protocols & NFC_PROTO_FELICA_MASK)
		ddev->protocols |= NFC_PROTO_FELICA_MASK;
	अगर (supported_protocols & NFC_PROTO_NFC_DEP_MASK)
		ddev->protocols |= NFC_PROTO_NFC_DEP_MASK;
	अगर (supported_protocols & NFC_PROTO_ISO15693_MASK)
		ddev->protocols |= NFC_PROTO_ISO15693_MASK;
	अगर (supported_protocols & NFC_PROTO_ISO14443_MASK)
		ddev->protocols |= NFC_PROTO_ISO14443_MASK;
	अगर (supported_protocols & NFC_PROTO_ISO14443_B_MASK)
		ddev->protocols |= NFC_PROTO_ISO14443_B_MASK;

	ddev->tx_headroom = tx_headroom + DIGITAL_MAX_HEADER_LEN;
	ddev->tx_tailroom = tx_tailroom + DIGITAL_CRC_LEN;

	ddev->nfc_dev = nfc_allocate_device(&digital_nfc_ops, ddev->protocols,
					    ddev->tx_headroom,
					    ddev->tx_tailroom);
	अगर (!ddev->nfc_dev) अणु
		pr_err("nfc_allocate_device failed\n");
		जाओ मुक्त_dev;
	पूर्ण

	nfc_set_drvdata(ddev->nfc_dev, ddev);

	वापस ddev;

मुक्त_dev:
	kमुक्त(ddev);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(nfc_digital_allocate_device);

व्योम nfc_digital_मुक्त_device(काष्ठा nfc_digital_dev *ddev)
अणु
	nfc_मुक्त_device(ddev->nfc_dev);
	kमुक्त(ddev);
पूर्ण
EXPORT_SYMBOL(nfc_digital_मुक्त_device);

पूर्णांक nfc_digital_रेजिस्टर_device(काष्ठा nfc_digital_dev *ddev)
अणु
	वापस nfc_रेजिस्टर_device(ddev->nfc_dev);
पूर्ण
EXPORT_SYMBOL(nfc_digital_रेजिस्टर_device);

व्योम nfc_digital_unरेजिस्टर_device(काष्ठा nfc_digital_dev *ddev)
अणु
	काष्ठा digital_cmd *cmd, *n;

	nfc_unरेजिस्टर_device(ddev->nfc_dev);

	mutex_lock(&ddev->poll_lock);
	ddev->poll_tech_count = 0;
	mutex_unlock(&ddev->poll_lock);

	cancel_delayed_work_sync(&ddev->poll_work);
	cancel_work_sync(&ddev->cmd_work);
	cancel_work_sync(&ddev->cmd_complete_work);

	list_क्रम_each_entry_safe(cmd, n, &ddev->cmd_queue, queue) अणु
		list_del(&cmd->queue);

		/* Call the command callback अगर any and pass it a ENODEV error.
		 * This gives a chance to the command issuer to मुक्त any
		 * allocated buffer.
		 */
		अगर (cmd->cmd_cb)
			cmd->cmd_cb(ddev, cmd->cb_context, ERR_PTR(-ENODEV));

		kमुक्त(cmd->mdaa_params);
		kमुक्त(cmd);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nfc_digital_unरेजिस्टर_device);

MODULE_LICENSE("GPL");
