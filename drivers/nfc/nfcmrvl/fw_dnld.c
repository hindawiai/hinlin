<शैली गुरु>
/*
 * Marvell NFC driver: Firmware करोwnloader
 *
 * Copyright (C) 2015, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available on the worldwide web at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/firmware.h>
#समावेश <linux/nfc.h>
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>
#समावेश "nfcmrvl.h"

#घोषणा FW_DNLD_TIMEOUT			15000

#घोषणा NCI_OP_PROPRIETARY_BOOT_CMD	nci_opcode_pack(NCI_GID_PROPRIETARY, \
							NCI_OP_PROP_BOOT_CMD)

/* FW करोwnload states */

क्रमागत अणु
	STATE_RESET = 0,
	STATE_INIT,
	STATE_SET_REF_CLOCK,
	STATE_SET_HI_CONFIG,
	STATE_OPEN_LC,
	STATE_FW_DNLD,
	STATE_CLOSE_LC,
	STATE_BOOT
पूर्ण;

क्रमागत अणु
	SUBSTATE_WAIT_COMMAND = 0,
	SUBSTATE_WAIT_ACK_CREDIT,
	SUBSTATE_WAIT_NACK_CREDIT,
	SUBSTATE_WAIT_DATA_CREDIT,
पूर्ण;

/*
** Patterns क्रम responses
*/

अटल स्थिर uपूर्णांक8_t nci_pattern_core_reset_ntf[] = अणु
	0x60, 0x00, 0x02, 0xA0, 0x01
पूर्ण;

अटल स्थिर uपूर्णांक8_t nci_pattern_core_init_rsp[] = अणु
	0x40, 0x01, 0x11
पूर्ण;

अटल स्थिर uपूर्णांक8_t nci_pattern_core_set_config_rsp[] = अणु
	0x40, 0x02, 0x02, 0x00, 0x00
पूर्ण;

अटल स्थिर uपूर्णांक8_t nci_pattern_core_conn_create_rsp[] = अणु
	0x40, 0x04, 0x04, 0x00
पूर्ण;

अटल स्थिर uपूर्णांक8_t nci_pattern_core_conn_बंद_rsp[] = अणु
	0x40, 0x05, 0x01, 0x00
पूर्ण;

अटल स्थिर uपूर्णांक8_t nci_pattern_core_conn_credits_ntf[] = अणु
	0x60, 0x06, 0x03, 0x01, NCI_CORE_LC_CONNID_PROP_FW_DL, 0x01
पूर्ण;

अटल स्थिर uपूर्णांक8_t nci_pattern_proprietary_boot_rsp[] = अणु
	0x4F, 0x3A, 0x01, 0x00
पूर्ण;

अटल काष्ठा sk_buff *alloc_lc_skb(काष्ठा nfcmrvl_निजी *priv, uपूर्णांक8_t plen)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nci_data_hdr *hdr;

	skb = nci_skb_alloc(priv->ndev, (NCI_DATA_HDR_SIZE + plen), GFP_KERNEL);
	अगर (!skb) अणु
		pr_err("no memory for data\n");
		वापस शून्य;
	पूर्ण

	hdr = skb_put(skb, NCI_DATA_HDR_SIZE);
	hdr->conn_id = NCI_CORE_LC_CONNID_PROP_FW_DL;
	hdr->rfu = 0;
	hdr->plen = plen;

	nci_mt_set((__u8 *)hdr, NCI_MT_DATA_PKT);
	nci_pbf_set((__u8 *)hdr, NCI_PBF_LAST);

	वापस skb;
पूर्ण

अटल व्योम fw_dnld_over(काष्ठा nfcmrvl_निजी *priv, u32 error)
अणु
	अगर (priv->fw_dnld.fw) अणु
		release_firmware(priv->fw_dnld.fw);
		priv->fw_dnld.fw = शून्य;
		priv->fw_dnld.header = शून्य;
		priv->fw_dnld.binary_config = शून्य;
	पूर्ण

	atomic_set(&priv->ndev->cmd_cnt, 0);

	अगर (समयr_pending(&priv->ndev->cmd_समयr))
		del_समयr_sync(&priv->ndev->cmd_समयr);

	अगर (समयr_pending(&priv->fw_dnld.समयr))
		del_समयr_sync(&priv->fw_dnld.समयr);

	nfc_info(priv->dev, "FW loading over (%d)]\n", error);

	अगर (error != 0) अणु
		/* failed, halt the chip to aव्योम घातer consumption */
		nfcmrvl_chip_halt(priv);
	पूर्ण

	nfc_fw_करोwnload_करोne(priv->ndev->nfc_dev, priv->fw_dnld.name, error);
पूर्ण

अटल व्योम fw_dnld_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा nfcmrvl_निजी *priv = from_समयr(priv, t, fw_dnld.समयr);

	nfc_err(priv->dev, "FW loading timeout");
	priv->fw_dnld.state = STATE_RESET;
	fw_dnld_over(priv, -ETIMEDOUT);
पूर्ण

अटल पूर्णांक process_state_reset(काष्ठा nfcmrvl_निजी *priv,
			       काष्ठा sk_buff *skb)
अणु
	अगर (माप(nci_pattern_core_reset_ntf) != skb->len ||
	    स_भेद(skb->data, nci_pattern_core_reset_ntf,
		   माप(nci_pattern_core_reset_ntf)))
		वापस -EINVAL;

	nfc_info(priv->dev, "BootROM reset, start fw download\n");

	/* Start FW करोwnload state machine */
	priv->fw_dnld.state = STATE_INIT;
	nci_send_cmd(priv->ndev, NCI_OP_CORE_INIT_CMD, 0, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक process_state_init(काष्ठा nfcmrvl_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_core_set_config_cmd cmd;

	अगर (माप(nci_pattern_core_init_rsp) >= skb->len ||
	    स_भेद(skb->data, nci_pattern_core_init_rsp,
		   माप(nci_pattern_core_init_rsp)))
		वापस -EINVAL;

	cmd.num_params = 1;
	cmd.param.id = NFCMRVL_PROP_REF_CLOCK;
	cmd.param.len = 4;
	स_नकल(cmd.param.val, &priv->fw_dnld.header->ref_घड़ी, 4);

	nci_send_cmd(priv->ndev, NCI_OP_CORE_SET_CONFIG_CMD, 3 + cmd.param.len,
		     &cmd);

	priv->fw_dnld.state = STATE_SET_REF_CLOCK;
	वापस 0;
पूर्ण

अटल व्योम create_lc(काष्ठा nfcmrvl_निजी *priv)
अणु
	uपूर्णांक8_t param[2] = अणु NCI_CORE_LC_PROP_FW_DL, 0x0 पूर्ण;

	priv->fw_dnld.state = STATE_OPEN_LC;
	nci_send_cmd(priv->ndev, NCI_OP_CORE_CONN_CREATE_CMD, 2, param);
पूर्ण

अटल पूर्णांक process_state_set_ref_घड़ी(काष्ठा nfcmrvl_निजी *priv,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_core_set_config_cmd cmd;

	अगर (माप(nci_pattern_core_set_config_rsp) != skb->len ||
	    स_भेद(skb->data, nci_pattern_core_set_config_rsp, skb->len))
		वापस -EINVAL;

	cmd.num_params = 1;
	cmd.param.id = NFCMRVL_PROP_SET_HI_CONFIG;

	चयन (priv->phy) अणु
	हाल NFCMRVL_PHY_UART:
		cmd.param.len = 5;
		स_नकल(cmd.param.val,
		       &priv->fw_dnld.binary_config->uart.baudrate,
		       4);
		cmd.param.val[4] =
			priv->fw_dnld.binary_config->uart.flow_control;
		अवरोध;
	हाल NFCMRVL_PHY_I2C:
		cmd.param.len = 5;
		स_नकल(cmd.param.val,
		       &priv->fw_dnld.binary_config->i2c.clk,
		       4);
		cmd.param.val[4] = 0;
		अवरोध;
	हाल NFCMRVL_PHY_SPI:
		cmd.param.len = 5;
		स_नकल(cmd.param.val,
		       &priv->fw_dnld.binary_config->spi.clk,
		       4);
		cmd.param.val[4] = 0;
		अवरोध;
	शेष:
		create_lc(priv);
		वापस 0;
	पूर्ण

	priv->fw_dnld.state = STATE_SET_HI_CONFIG;
	nci_send_cmd(priv->ndev, NCI_OP_CORE_SET_CONFIG_CMD, 3 + cmd.param.len,
		     &cmd);
	वापस 0;
पूर्ण

अटल पूर्णांक process_state_set_hi_config(काष्ठा nfcmrvl_निजी *priv,
				       काष्ठा sk_buff *skb)
अणु
	अगर (माप(nci_pattern_core_set_config_rsp) != skb->len ||
	    स_भेद(skb->data, nci_pattern_core_set_config_rsp, skb->len))
		वापस -EINVAL;

	create_lc(priv);
	वापस 0;
पूर्ण

अटल पूर्णांक process_state_खोलो_lc(काष्ठा nfcmrvl_निजी *priv,
				 काष्ठा sk_buff *skb)
अणु
	अगर (माप(nci_pattern_core_conn_create_rsp) >= skb->len ||
	    स_भेद(skb->data, nci_pattern_core_conn_create_rsp,
		   माप(nci_pattern_core_conn_create_rsp)))
		वापस -EINVAL;

	priv->fw_dnld.state = STATE_FW_DNLD;
	priv->fw_dnld.substate = SUBSTATE_WAIT_COMMAND;
	priv->fw_dnld.offset = priv->fw_dnld.binary_config->offset;
	वापस 0;
पूर्ण

अटल पूर्णांक process_state_fw_dnld(काष्ठा nfcmrvl_निजी *priv,
				 काष्ठा sk_buff *skb)
अणु
	uपूर्णांक16_t len;
	uपूर्णांक16_t comp_len;
	काष्ठा sk_buff *out_skb;

	चयन (priv->fw_dnld.substate) अणु
	हाल SUBSTATE_WAIT_COMMAND:
		/*
		 * Command क्रमmat:
		 * B0..2: NCI header
		 * B3   : Helper command (0xA5)
		 * B4..5: le16 data size
		 * B6..7: le16 data size complement (~)
		 * B8..N: payload
		 */

		/* Remove NCI HDR */
		skb_pull(skb, 3);
		अगर (skb->data[0] != HELPER_CMD_PACKET_FORMAT || skb->len != 5) अणु
			nfc_err(priv->dev, "bad command");
			वापस -EINVAL;
		पूर्ण
		skb_pull(skb, 1);
		len = get_unaligned_le16(skb->data);
		skb_pull(skb, 2);
		comp_len = get_unaligned_le16(skb->data);
		स_नकल(&comp_len, skb->data, 2);
		skb_pull(skb, 2);
		अगर (((~len) & 0xFFFF) != comp_len) अणु
			nfc_err(priv->dev, "bad len complement: %x %x %x",
				len, comp_len, (~len & 0xFFFF));
			out_skb = alloc_lc_skb(priv, 1);
			अगर (!out_skb)
				वापस -ENOMEM;
			skb_put_u8(out_skb, 0xBF);
			nci_send_frame(priv->ndev, out_skb);
			priv->fw_dnld.substate = SUBSTATE_WAIT_NACK_CREDIT;
			वापस 0;
		पूर्ण
		priv->fw_dnld.chunk_len = len;
		out_skb = alloc_lc_skb(priv, 1);
		अगर (!out_skb)
			वापस -ENOMEM;
		skb_put_u8(out_skb, HELPER_ACK_PACKET_FORMAT);
		nci_send_frame(priv->ndev, out_skb);
		priv->fw_dnld.substate = SUBSTATE_WAIT_ACK_CREDIT;
		अवरोध;

	हाल SUBSTATE_WAIT_ACK_CREDIT:
		अगर (माप(nci_pattern_core_conn_credits_ntf) != skb->len ||
		    स_भेद(nci_pattern_core_conn_credits_ntf, skb->data,
			   skb->len)) अणु
			nfc_err(priv->dev, "bad packet: waiting for credit");
			वापस -EINVAL;
		पूर्ण
		अगर (priv->fw_dnld.chunk_len == 0) अणु
			/* FW Loading is करोne */
			uपूर्णांक8_t conn_id = NCI_CORE_LC_CONNID_PROP_FW_DL;

			priv->fw_dnld.state = STATE_CLOSE_LC;
			nci_send_cmd(priv->ndev, NCI_OP_CORE_CONN_CLOSE_CMD,
				     1, &conn_id);
		पूर्ण अन्यथा अणु
			out_skb = alloc_lc_skb(priv, priv->fw_dnld.chunk_len);
			अगर (!out_skb)
				वापस -ENOMEM;
			skb_put_data(out_skb,
				     ((uपूर्णांक8_t *)priv->fw_dnld.fw->data) + priv->fw_dnld.offset,
				     priv->fw_dnld.chunk_len);
			nci_send_frame(priv->ndev, out_skb);
			priv->fw_dnld.substate = SUBSTATE_WAIT_DATA_CREDIT;
		पूर्ण
		अवरोध;

	हाल SUBSTATE_WAIT_DATA_CREDIT:
		अगर (माप(nci_pattern_core_conn_credits_ntf) != skb->len ||
		    स_भेद(nci_pattern_core_conn_credits_ntf, skb->data,
			    skb->len)) अणु
			nfc_err(priv->dev, "bad packet: waiting for credit");
			वापस -EINVAL;
		पूर्ण
		priv->fw_dnld.offset += priv->fw_dnld.chunk_len;
		priv->fw_dnld.chunk_len = 0;
		priv->fw_dnld.substate = SUBSTATE_WAIT_COMMAND;
		अवरोध;

	हाल SUBSTATE_WAIT_NACK_CREDIT:
		अगर (माप(nci_pattern_core_conn_credits_ntf) != skb->len ||
		    स_भेद(nci_pattern_core_conn_credits_ntf, skb->data,
			    skb->len)) अणु
			nfc_err(priv->dev, "bad packet: waiting for credit");
			वापस -EINVAL;
		पूर्ण
		priv->fw_dnld.substate = SUBSTATE_WAIT_COMMAND;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक process_state_बंद_lc(काष्ठा nfcmrvl_निजी *priv,
				  काष्ठा sk_buff *skb)
अणु
	अगर (माप(nci_pattern_core_conn_बंद_rsp) != skb->len ||
	    स_भेद(skb->data, nci_pattern_core_conn_बंद_rsp, skb->len))
		वापस -EINVAL;

	priv->fw_dnld.state = STATE_BOOT;
	nci_send_cmd(priv->ndev, NCI_OP_PROPRIETARY_BOOT_CMD, 0, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक process_state_boot(काष्ठा nfcmrvl_निजी *priv, काष्ठा sk_buff *skb)
अणु
	अगर (माप(nci_pattern_proprietary_boot_rsp) != skb->len ||
	    स_भेद(skb->data, nci_pattern_proprietary_boot_rsp, skb->len))
		वापस -EINVAL;

	/*
	 * Update HI config to use the right configuration क्रम the next
	 * data exchanges.
	 */
	priv->अगर_ops->nci_update_config(priv,
					&priv->fw_dnld.binary_config->config);

	अगर (priv->fw_dnld.binary_config == &priv->fw_dnld.header->helper) अणु
		/*
		 * This is the हाल where an helper was needed and we have
		 * uploaded it. Now we have to रुको the next RESET NTF to start
		 * FW करोwnload.
		 */
		priv->fw_dnld.state = STATE_RESET;
		priv->fw_dnld.binary_config = &priv->fw_dnld.header->firmware;
		nfc_info(priv->dev, "FW loading: helper loaded");
	पूर्ण अन्यथा अणु
		nfc_info(priv->dev, "FW loading: firmware loaded");
		fw_dnld_over(priv, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fw_dnld_rx_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा sk_buff *skb;
	काष्ठा nfcmrvl_fw_dnld *fw_dnld = container_of(work,
						       काष्ठा nfcmrvl_fw_dnld,
						       rx_work);
	काष्ठा nfcmrvl_निजी *priv = container_of(fw_dnld,
						    काष्ठा nfcmrvl_निजी,
						    fw_dnld);

	जबतक ((skb = skb_dequeue(&fw_dnld->rx_q))) अणु
		nfc_send_to_raw_sock(priv->ndev->nfc_dev, skb,
				     RAW_PAYLOAD_NCI, NFC_सूचीECTION_RX);
		चयन (fw_dnld->state) अणु
		हाल STATE_RESET:
			ret = process_state_reset(priv, skb);
			अवरोध;
		हाल STATE_INIT:
			ret = process_state_init(priv, skb);
			अवरोध;
		हाल STATE_SET_REF_CLOCK:
			ret = process_state_set_ref_घड़ी(priv, skb);
			अवरोध;
		हाल STATE_SET_HI_CONFIG:
			ret = process_state_set_hi_config(priv, skb);
			अवरोध;
		हाल STATE_OPEN_LC:
			ret = process_state_खोलो_lc(priv, skb);
			अवरोध;
		हाल STATE_FW_DNLD:
			ret = process_state_fw_dnld(priv, skb);
			अवरोध;
		हाल STATE_CLOSE_LC:
			ret = process_state_बंद_lc(priv, skb);
			अवरोध;
		हाल STATE_BOOT:
			ret = process_state_boot(priv, skb);
			अवरोध;
		शेष:
			ret = -EFAULT;
		पूर्ण

		kमुक्त_skb(skb);

		अगर (ret != 0) अणु
			nfc_err(priv->dev, "FW loading error");
			fw_dnld_over(priv, ret);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक	nfcmrvl_fw_dnld_init(काष्ठा nfcmrvl_निजी *priv)
अणु
	अक्षर name[32];

	INIT_WORK(&priv->fw_dnld.rx_work, fw_dnld_rx_work);
	snम_लिखो(name, माप(name), "%s_nfcmrvl_fw_dnld_rx_wq",
		 dev_name(&priv->ndev->nfc_dev->dev));
	priv->fw_dnld.rx_wq = create_singlethपढ़ो_workqueue(name);
	अगर (!priv->fw_dnld.rx_wq)
		वापस -ENOMEM;
	skb_queue_head_init(&priv->fw_dnld.rx_q);
	वापस 0;
पूर्ण

व्योम	nfcmrvl_fw_dnld_deinit(काष्ठा nfcmrvl_निजी *priv)
अणु
	destroy_workqueue(priv->fw_dnld.rx_wq);
पूर्ण

व्योम	nfcmrvl_fw_dnld_recv_frame(काष्ठा nfcmrvl_निजी *priv,
				   काष्ठा sk_buff *skb)
अणु
	/* Discard command समयr */
	अगर (समयr_pending(&priv->ndev->cmd_समयr))
		del_समयr_sync(&priv->ndev->cmd_समयr);

	/* Allow next command */
	atomic_set(&priv->ndev->cmd_cnt, 1);

	/* Queue and trigger rx work */
	skb_queue_tail(&priv->fw_dnld.rx_q, skb);
	queue_work(priv->fw_dnld.rx_wq, &priv->fw_dnld.rx_work);
पूर्ण

व्योम nfcmrvl_fw_dnld_पात(काष्ठा nfcmrvl_निजी *priv)
अणु
	fw_dnld_over(priv, -EHOSTDOWN);
पूर्ण

पूर्णांक nfcmrvl_fw_dnld_start(काष्ठा nci_dev *ndev, स्थिर अक्षर *firmware_name)
अणु
	काष्ठा nfcmrvl_निजी *priv = nci_get_drvdata(ndev);
	काष्ठा nfcmrvl_fw_dnld *fw_dnld = &priv->fw_dnld;
	पूर्णांक res;

	अगर (!priv->support_fw_dnld)
		वापस -ENOTSUPP;

	अगर (!firmware_name || !firmware_name[0])
		वापस -EINVAL;

	म_नकल(fw_dnld->name, firmware_name);

	/*
	 * Retrieve FW binary file and parse it to initialize FW करोwnload
	 * state machine.
	 */

	/* Retrieve FW binary */
	res = request_firmware(&fw_dnld->fw, firmware_name,
			       &ndev->nfc_dev->dev);
	अगर (res < 0) अणु
		nfc_err(priv->dev, "failed to retrieve FW %s", firmware_name);
		वापस -ENOENT;
	पूर्ण

	fw_dnld->header = (स्थिर काष्ठा nfcmrvl_fw *) priv->fw_dnld.fw->data;

	अगर (fw_dnld->header->magic != NFCMRVL_FW_MAGIC ||
	    fw_dnld->header->phy != priv->phy) अणु
		nfc_err(priv->dev, "bad firmware binary %s magic=0x%x phy=%d",
			firmware_name, fw_dnld->header->magic,
			fw_dnld->header->phy);
		release_firmware(fw_dnld->fw);
		fw_dnld->header = शून्य;
		वापस -EINVAL;
	पूर्ण

	अगर (fw_dnld->header->helper.offset != 0) अणु
		nfc_info(priv->dev, "loading helper");
		fw_dnld->binary_config = &fw_dnld->header->helper;
	पूर्ण अन्यथा अणु
		nfc_info(priv->dev, "loading firmware");
		fw_dnld->binary_config = &fw_dnld->header->firmware;
	पूर्ण

	/* Configure a समयr क्रम समयout */
	समयr_setup(&priv->fw_dnld.समयr, fw_dnld_समयout, 0);
	mod_समयr(&priv->fw_dnld.समयr,
		  jअगरfies + msecs_to_jअगरfies(FW_DNLD_TIMEOUT));

	/* Ronfigure HI to be sure that it is the bootrom values */
	priv->अगर_ops->nci_update_config(priv,
					&fw_dnld->header->bootrom.config);

	/* Allow first command */
	atomic_set(&priv->ndev->cmd_cnt, 1);

	/* First, reset the chip */
	priv->fw_dnld.state = STATE_RESET;
	nfcmrvl_chip_reset(priv);

	/* Now रुको क्रम CORE_RESET_NTF or समयout */

	वापस 0;
पूर्ण
