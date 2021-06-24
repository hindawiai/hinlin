<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Bluetooth supports क्रम Qualcomm Atheros chips
 *
 *  Copyright (c) 2015 The Linux Foundation. All rights reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btqca.h"

#घोषणा VERSION "0.1"

पूर्णांक qca_पढ़ो_soc_version(काष्ठा hci_dev *hdev, काष्ठा qca_btsoc_version *ver,
			 क्रमागत qca_btsoc_type soc_type)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा edl_event_hdr *edl;
	अक्षर cmd;
	पूर्णांक err = 0;
	u8 event_type = HCI_EV_VENDOR;
	u8 rlen = माप(*edl) + माप(*ver);
	u8 rtype = EDL_APP_VER_RES_EVT;

	bt_dev_dbg(hdev, "QCA Version Request");

	/* Unlike other SoC's sending version command response as payload to
	 * VSE event. WCN3991 sends version command response as a payload to
	 * command complete event.
	 */
	अगर (soc_type >= QCA_WCN3991) अणु
		event_type = 0;
		rlen += 1;
		rtype = EDL_PATCH_VER_REQ_CMD;
	पूर्ण

	cmd = EDL_PATCH_VER_REQ_CMD;
	skb = __hci_cmd_sync_ev(hdev, EDL_PATCH_CMD_OPCODE, EDL_PATCH_CMD_LEN,
				&cmd, event_type, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "Reading QCA version information failed (%d)",
			   err);
		वापस err;
	पूर्ण

	अगर (skb->len != rlen) अणु
		bt_dev_err(hdev, "QCA Version size mismatch len %d", skb->len);
		err = -EILSEQ;
		जाओ out;
	पूर्ण

	edl = (काष्ठा edl_event_hdr *)(skb->data);
	अगर (!edl) अणु
		bt_dev_err(hdev, "QCA TLV with no header");
		err = -EILSEQ;
		जाओ out;
	पूर्ण

	अगर (edl->cresp != EDL_CMD_REQ_RES_EVT ||
	    edl->rtype != rtype) अणु
		bt_dev_err(hdev, "QCA Wrong packet received %d %d", edl->cresp,
			   edl->rtype);
		err = -EIO;
		जाओ out;
	पूर्ण

	अगर (soc_type >= QCA_WCN3991)
		स_नकल(ver, edl->data + 1, माप(*ver));
	अन्यथा
		स_नकल(ver, &edl->data, माप(*ver));

	bt_dev_info(hdev, "QCA Product ID   :0x%08x",
		    le32_to_cpu(ver->product_id));
	bt_dev_info(hdev, "QCA SOC Version  :0x%08x",
		    le32_to_cpu(ver->soc_id));
	bt_dev_info(hdev, "QCA ROM Version  :0x%08x",
		    le16_to_cpu(ver->rom_ver));
	bt_dev_info(hdev, "QCA Patch Version:0x%08x",
		    le16_to_cpu(ver->patch_ver));

	अगर (ver->soc_id == 0 || ver->rom_ver == 0)
		err = -EILSEQ;

out:
	kमुक्त_skb(skb);
	अगर (err)
		bt_dev_err(hdev, "QCA Failed to get version (%d)", err);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(qca_पढ़ो_soc_version);

अटल पूर्णांक qca_पढ़ो_fw_build_info(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा edl_event_hdr *edl;
	अक्षर cmd, build_label[QCA_FW_BUILD_VER_LEN];
	पूर्णांक build_lbl_len, err = 0;

	bt_dev_dbg(hdev, "QCA read fw build info");

	cmd = EDL_GET_BUILD_INFO_CMD;
	skb = __hci_cmd_sync_ev(hdev, EDL_PATCH_CMD_OPCODE, EDL_PATCH_CMD_LEN,
				&cmd, 0, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "Reading QCA fw build info failed (%d)",
			   err);
		वापस err;
	पूर्ण

	edl = (काष्ठा edl_event_hdr *)(skb->data);
	अगर (!edl) अणु
		bt_dev_err(hdev, "QCA read fw build info with no header");
		err = -EILSEQ;
		जाओ out;
	पूर्ण

	अगर (edl->cresp != EDL_CMD_REQ_RES_EVT ||
	    edl->rtype != EDL_GET_BUILD_INFO_CMD) अणु
		bt_dev_err(hdev, "QCA Wrong packet received %d %d", edl->cresp,
			   edl->rtype);
		err = -EIO;
		जाओ out;
	पूर्ण

	build_lbl_len = edl->data[0];
	अगर (build_lbl_len <= QCA_FW_BUILD_VER_LEN - 1) अणु
		स_नकल(build_label, edl->data + 1, build_lbl_len);
		*(build_label + build_lbl_len) = '\0';
	पूर्ण

	hci_set_fw_info(hdev, "%s", build_label);

out:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक qca_send_reset(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	bt_dev_dbg(hdev, "QCA HCI_RESET");

	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "QCA Reset failed (%d)", err);
		वापस err;
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

पूर्णांक qca_send_pre_shutकरोwn_cmd(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	bt_dev_dbg(hdev, "QCA pre shutdown cmd");

	skb = __hci_cmd_sync_ev(hdev, QCA_PRE_SHUTDOWN_CMD, 0,
				शून्य, HCI_EV_CMD_COMPLETE, HCI_INIT_TIMEOUT);

	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "QCA preshutdown_cmd failed (%d)", err);
		वापस err;
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qca_send_pre_shutकरोwn_cmd);

अटल व्योम qca_tlv_check_data(काष्ठा qca_fw_config *config,
		स्थिर काष्ठा firmware *fw, क्रमागत qca_btsoc_type soc_type)
अणु
	स्थिर u8 *data;
	u32 type_len;
	u16 tag_id, tag_len;
	पूर्णांक idx, length;
	काष्ठा tlv_type_hdr *tlv;
	काष्ठा tlv_type_patch *tlv_patch;
	काष्ठा tlv_type_nvm *tlv_nvm;
	uपूर्णांक8_t nvm_baud_rate = config->user_baud_rate;

	tlv = (काष्ठा tlv_type_hdr *)fw->data;

	type_len = le32_to_cpu(tlv->type_len);
	length = (type_len >> 8) & 0x00ffffff;

	BT_DBG("TLV Type\t\t : 0x%x", type_len & 0x000000ff);
	BT_DBG("Length\t\t : %d bytes", length);

	config->dnld_mode = QCA_SKIP_EVT_NONE;
	config->dnld_type = QCA_SKIP_EVT_NONE;

	चयन (config->type) अणु
	हाल TLV_TYPE_PATCH:
		tlv_patch = (काष्ठा tlv_type_patch *)tlv->data;

		/* For Rome version 1.1 to 3.1, all segment commands
		 * are acked by a venकरोr specअगरic event (VSE).
		 * For Rome >= 3.2, the करोwnload mode field indicates
		 * अगर VSE is skipped by the controller.
		 * In हाल VSE is skipped, only the last segment is acked.
		 */
		config->dnld_mode = tlv_patch->करोwnload_mode;
		config->dnld_type = config->dnld_mode;

		BT_DBG("Total Length           : %d bytes",
		       le32_to_cpu(tlv_patch->total_size));
		BT_DBG("Patch Data Length      : %d bytes",
		       le32_to_cpu(tlv_patch->data_length));
		BT_DBG("Signing Format Version : 0x%x",
		       tlv_patch->क्रमmat_version);
		BT_DBG("Signature Algorithm    : 0x%x",
		       tlv_patch->signature);
		BT_DBG("Download mode          : 0x%x",
		       tlv_patch->करोwnload_mode);
		BT_DBG("Reserved               : 0x%x",
		       tlv_patch->reserved1);
		BT_DBG("Product ID             : 0x%04x",
		       le16_to_cpu(tlv_patch->product_id));
		BT_DBG("Rom Build Version      : 0x%04x",
		       le16_to_cpu(tlv_patch->rom_build));
		BT_DBG("Patch Version          : 0x%04x",
		       le16_to_cpu(tlv_patch->patch_version));
		BT_DBG("Reserved               : 0x%x",
		       le16_to_cpu(tlv_patch->reserved2));
		BT_DBG("Patch Entry Address    : 0x%x",
		       le32_to_cpu(tlv_patch->entry));
		अवरोध;

	हाल TLV_TYPE_NVM:
		idx = 0;
		data = tlv->data;
		जबतक (idx < length) अणु
			tlv_nvm = (काष्ठा tlv_type_nvm *)(data + idx);

			tag_id = le16_to_cpu(tlv_nvm->tag_id);
			tag_len = le16_to_cpu(tlv_nvm->tag_len);

			/* Update NVM tags as needed */
			चयन (tag_id) अणु
			हाल EDL_TAG_ID_HCI:
				/* HCI transport layer parameters
				 * enabling software inband sleep
				 * onto controller side.
				 */
				tlv_nvm->data[0] |= 0x80;

				/* UART Baud Rate */
				अगर (soc_type >= QCA_WCN3991)
					tlv_nvm->data[1] = nvm_baud_rate;
				अन्यथा
					tlv_nvm->data[2] = nvm_baud_rate;

				अवरोध;

			हाल EDL_TAG_ID_DEEP_SLEEP:
				/* Sleep enable mask
				 * enabling deep sleep feature on controller.
				 */
				tlv_nvm->data[0] |= 0x01;

				अवरोध;
			पूर्ण

			idx += (माप(u16) + माप(u16) + 8 + tag_len);
		पूर्ण
		अवरोध;

	शेष:
		BT_ERR("Unknown TLV type %d", config->type);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक qca_tlv_send_segment(काष्ठा hci_dev *hdev, पूर्णांक seg_size,
				स्थिर u8 *data, क्रमागत qca_tlv_dnld_mode mode,
				क्रमागत qca_btsoc_type soc_type)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा edl_event_hdr *edl;
	काष्ठा tlv_seg_resp *tlv_resp;
	u8 cmd[MAX_SIZE_PER_TLV_SEGMENT + 2];
	पूर्णांक err = 0;
	u8 event_type = HCI_EV_VENDOR;
	u8 rlen = (माप(*edl) + माप(*tlv_resp));
	u8 rtype = EDL_TVL_DNLD_RES_EVT;

	cmd[0] = EDL_PATCH_TLV_REQ_CMD;
	cmd[1] = seg_size;
	स_नकल(cmd + 2, data, seg_size);

	अगर (mode == QCA_SKIP_EVT_VSE_CC || mode == QCA_SKIP_EVT_VSE)
		वापस __hci_cmd_send(hdev, EDL_PATCH_CMD_OPCODE, seg_size + 2,
				      cmd);

	/* Unlike other SoC's sending version command response as payload to
	 * VSE event. WCN3991 sends version command response as a payload to
	 * command complete event.
	 */
	अगर (soc_type >= QCA_WCN3991) अणु
		event_type = 0;
		rlen = माप(*edl);
		rtype = EDL_PATCH_TLV_REQ_CMD;
	पूर्ण

	skb = __hci_cmd_sync_ev(hdev, EDL_PATCH_CMD_OPCODE, seg_size + 2, cmd,
				event_type, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "QCA Failed to send TLV segment (%d)", err);
		वापस err;
	पूर्ण

	अगर (skb->len != rlen) अणु
		bt_dev_err(hdev, "QCA TLV response size mismatch");
		err = -EILSEQ;
		जाओ out;
	पूर्ण

	edl = (काष्ठा edl_event_hdr *)(skb->data);
	अगर (!edl) अणु
		bt_dev_err(hdev, "TLV with no header");
		err = -EILSEQ;
		जाओ out;
	पूर्ण

	अगर (edl->cresp != EDL_CMD_REQ_RES_EVT || edl->rtype != rtype) अणु
		bt_dev_err(hdev, "QCA TLV with error stat 0x%x rtype 0x%x",
			   edl->cresp, edl->rtype);
		err = -EIO;
	पूर्ण

	अगर (soc_type >= QCA_WCN3991)
		जाओ out;

	tlv_resp = (काष्ठा tlv_seg_resp *)(edl->data);
	अगर (tlv_resp->result) अणु
		bt_dev_err(hdev, "QCA TLV with error stat 0x%x rtype 0x%x (0x%x)",
			   edl->cresp, edl->rtype, tlv_resp->result);
	पूर्ण

out:
	kमुक्त_skb(skb);

	वापस err;
पूर्ण

अटल पूर्णांक qca_inject_cmd_complete_event(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_event_hdr *hdr;
	काष्ठा hci_ev_cmd_complete *evt;
	काष्ठा sk_buff *skb;

	skb = bt_skb_alloc(माप(*hdr) + माप(*evt) + 1, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = skb_put(skb, माप(*hdr));
	hdr->evt = HCI_EV_CMD_COMPLETE;
	hdr->plen = माप(*evt) + 1;

	evt = skb_put(skb, माप(*evt));
	evt->ncmd = 1;
	evt->opcode = cpu_to_le16(QCA_HCI_CC_OPCODE);

	skb_put_u8(skb, QCA_HCI_CC_SUCCESS);

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;

	वापस hci_recv_frame(hdev, skb);
पूर्ण

अटल पूर्णांक qca_करोwnload_firmware(काष्ठा hci_dev *hdev,
				 काष्ठा qca_fw_config *config,
				 क्रमागत qca_btsoc_type soc_type)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर u8 *segment;
	पूर्णांक ret, reमुख्य, i = 0;

	bt_dev_info(hdev, "QCA Downloading %s", config->fwname);

	ret = request_firmware(&fw, config->fwname, &hdev->dev);
	अगर (ret) अणु
		bt_dev_err(hdev, "QCA Failed to request file: %s (%d)",
			   config->fwname, ret);
		वापस ret;
	पूर्ण

	qca_tlv_check_data(config, fw, soc_type);

	segment = fw->data;
	reमुख्य = fw->size;
	जबतक (reमुख्य > 0) अणु
		पूर्णांक segsize = min(MAX_SIZE_PER_TLV_SEGMENT, reमुख्य);

		bt_dev_dbg(hdev, "Send segment %d, size %d", i++, segsize);

		reमुख्य -= segsize;
		/* The last segment is always acked regardless करोwnload mode */
		अगर (!reमुख्य || segsize < MAX_SIZE_PER_TLV_SEGMENT)
			config->dnld_mode = QCA_SKIP_EVT_NONE;

		ret = qca_tlv_send_segment(hdev, segsize, segment,
					   config->dnld_mode, soc_type);
		अगर (ret)
			जाओ out;

		segment += segsize;
	पूर्ण

	/* Latest qualcomm chipsets are not sending a command complete event
	 * क्रम every fw packet sent. They only respond with a venकरोr specअगरic
	 * event क्रम the last packet. This optimization in the chip will
	 * decrease the BT in initialization समय. Here we will inject a command
	 * complete event to aव्योम a command समयout error message.
	 */
	अगर (config->dnld_type == QCA_SKIP_EVT_VSE_CC ||
	    config->dnld_type == QCA_SKIP_EVT_VSE)
		ret = qca_inject_cmd_complete_event(hdev);

out:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक qca_disable_soc_logging(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	u8 cmd[2];
	पूर्णांक err;

	cmd[0] = QCA_DISABLE_LOGGING_SUB_OP;
	cmd[1] = 0x00;
	skb = __hci_cmd_sync_ev(hdev, QCA_DISABLE_LOGGING, माप(cmd), cmd,
				HCI_EV_CMD_COMPLETE, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "QCA Failed to disable soc logging(%d)", err);
		वापस err;
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

पूर्णांक qca_set_bdaddr_rome(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा sk_buff *skb;
	u8 cmd[9];
	पूर्णांक err;

	cmd[0] = EDL_NVM_ACCESS_SET_REQ_CMD;
	cmd[1] = 0x02; 			/* TAG ID */
	cmd[2] = माप(bdaddr_t);	/* size */
	स_नकल(cmd + 3, bdaddr, माप(bdaddr_t));
	skb = __hci_cmd_sync_ev(hdev, EDL_NVM_ACCESS_OPCODE, माप(cmd), cmd,
				HCI_EV_VENDOR, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "QCA Change address command failed (%d)", err);
		वापस err;
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qca_set_bdaddr_rome);

पूर्णांक qca_uart_setup(काष्ठा hci_dev *hdev, uपूर्णांक8_t baudrate,
		   क्रमागत qca_btsoc_type soc_type, काष्ठा qca_btsoc_version ver,
		   स्थिर अक्षर *firmware_name)
अणु
	काष्ठा qca_fw_config config;
	पूर्णांक err;
	u8 rom_ver = 0;
	u32 soc_ver;

	bt_dev_dbg(hdev, "QCA setup on UART");

	soc_ver = get_soc_ver(ver.soc_id, ver.rom_ver);

	bt_dev_info(hdev, "QCA controller version 0x%08x", soc_ver);

	config.user_baud_rate = baudrate;

	/* Download rampatch file */
	config.type = TLV_TYPE_PATCH;
	अगर (qca_is_wcn399x(soc_type)) अणु
		/* Firmware files to करोwnload are based on ROM version.
		 * ROM version is derived from last two bytes of soc_ver.
		 */
		rom_ver = ((soc_ver & 0x00000f00) >> 0x04) |
			    (soc_ver & 0x0000000f);
		snम_लिखो(config.fwname, माप(config.fwname),
			 "qca/crbtfw%02x.tlv", rom_ver);
	पूर्ण अन्यथा अगर (soc_type == QCA_QCA6390) अणु
		rom_ver = ((soc_ver & 0x00000f00) >> 0x04) |
			    (soc_ver & 0x0000000f);
		snम_लिखो(config.fwname, माप(config.fwname),
			 "qca/htbtfw%02x.tlv", rom_ver);
	पूर्ण अन्यथा अणु
		snम_लिखो(config.fwname, माप(config.fwname),
			 "qca/rampatch_%08x.bin", soc_ver);
	पूर्ण

	err = qca_करोwnload_firmware(hdev, &config, soc_type);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "QCA Failed to download patch (%d)", err);
		वापस err;
	पूर्ण

	/* Give the controller some समय to get पढ़ोy to receive the NVM */
	msleep(10);

	/* Download NVM configuration */
	config.type = TLV_TYPE_NVM;
	अगर (firmware_name)
		snम_लिखो(config.fwname, माप(config.fwname),
			 "qca/%s", firmware_name);
	अन्यथा अगर (qca_is_wcn399x(soc_type)) अणु
		अगर (ver.soc_id == QCA_WCN3991_SOC_ID) अणु
			snम_लिखो(config.fwname, माप(config.fwname),
				 "qca/crnv%02xu.bin", rom_ver);
		पूर्ण अन्यथा अणु
			snम_लिखो(config.fwname, माप(config.fwname),
				 "qca/crnv%02x.bin", rom_ver);
		पूर्ण
	पूर्ण
	अन्यथा अगर (soc_type == QCA_QCA6390)
		snम_लिखो(config.fwname, माप(config.fwname),
			 "qca/htnv%02x.bin", rom_ver);
	अन्यथा
		snम_लिखो(config.fwname, माप(config.fwname),
			 "qca/nvm_%08x.bin", soc_ver);

	err = qca_करोwnload_firmware(hdev, &config, soc_type);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "QCA Failed to download NVM (%d)", err);
		वापस err;
	पूर्ण

	अगर (soc_type >= QCA_WCN3991) अणु
		err = qca_disable_soc_logging(hdev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* WCN399x supports the Microsoft venकरोr extension with 0xFD70 as the
	 * VsMsftOpCode.
	 */
	चयन (soc_type) अणु
	हाल QCA_WCN3990:
	हाल QCA_WCN3991:
	हाल QCA_WCN3998:
		hci_set_msft_opcode(hdev, 0xFD70);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Perक्रमm HCI reset */
	err = qca_send_reset(hdev);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "QCA Failed to run HCI_RESET (%d)", err);
		वापस err;
	पूर्ण

	अगर (soc_type == QCA_WCN3991) अणु
		/* get fw build info */
		err = qca_पढ़ो_fw_build_info(hdev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	bt_dev_info(hdev, "QCA setup on UART is completed");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qca_uart_setup);

पूर्णांक qca_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = __hci_cmd_sync_ev(hdev, EDL_WRITE_BD_ADDR_OPCODE, 6, bdaddr,
				HCI_EV_VENDOR, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "QCA Change address cmd failed (%d)", err);
		वापस err;
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qca_set_bdaddr);


MODULE_AUTHOR("Ben Young Tae Kim <ytkim@qca.qualcomm.com>");
MODULE_DESCRIPTION("Bluetooth support for Qualcomm Atheros family ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
