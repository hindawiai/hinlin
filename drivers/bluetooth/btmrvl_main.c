<शैली गुरु>
/**
 * Marvell Bluetooth driver
 *
 * Copyright (C) 2009, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 **/

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <linux/mmc/sdio_func.h>

#समावेश "btmrvl_drv.h"
#समावेश "btmrvl_sdio.h"

#घोषणा VERSION "1.0"

/*
 * This function is called by पूर्णांकerface specअगरic पूर्णांकerrupt handler.
 * It updates Power Save & Host Sleep states, and wakes up the मुख्य
 * thपढ़ो.
 */
व्योम bपंचांगrvl_पूर्णांकerrupt(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	priv->adapter->ps_state = PS_AWAKE;

	priv->adapter->wakeup_tries = 0;

	priv->adapter->पूर्णांक_count++;

	अगर (priv->adapter->hs_state == HS_ACTIVATED) अणु
		BT_DBG("BT: HS DEACTIVATED in ISR!");
		priv->adapter->hs_state = HS_DEACTIVATED;
	पूर्ण

	wake_up_पूर्णांकerruptible(&priv->मुख्य_thपढ़ो.रुको_q);
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_पूर्णांकerrupt);

bool bपंचांगrvl_check_evtpkt(काष्ठा bपंचांगrvl_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_event_hdr *hdr = (व्योम *) skb->data;

	अगर (hdr->evt == HCI_EV_CMD_COMPLETE) अणु
		काष्ठा hci_ev_cmd_complete *ec;
		u16 opcode;

		ec = (व्योम *) (skb->data + HCI_EVENT_HDR_SIZE);
		opcode = __le16_to_cpu(ec->opcode);

		अगर (priv->bपंचांगrvl_dev.sendcmdflag) अणु
			priv->bपंचांगrvl_dev.sendcmdflag = false;
			priv->adapter->cmd_complete = true;
			wake_up_पूर्णांकerruptible(&priv->adapter->cmd_रुको_q);

			अगर (hci_opcode_ogf(opcode) == 0x3F) अणु
				BT_DBG("vendor event skipped: opcode=%#4.4x",
				       opcode);
				kमुक्त_skb(skb);
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_check_evtpkt);

पूर्णांक bपंचांगrvl_process_event(काष्ठा bपंचांगrvl_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा bपंचांगrvl_adapter *adapter = priv->adapter;
	काष्ठा bपंचांगrvl_event *event;
	पूर्णांक ret = 0;

	event = (काष्ठा bपंचांगrvl_event *) skb->data;
	अगर (event->ec != 0xff) अणु
		BT_DBG("Not Marvell Event=%x", event->ec);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	चयन (event->data[0]) अणु
	हाल BT_EVENT_AUTO_SLEEP_MODE:
		अगर (!event->data[2]) अणु
			अगर (event->data[1] == BT_PS_ENABLE)
				adapter->psmode = 1;
			अन्यथा
				adapter->psmode = 0;
			BT_DBG("PS Mode:%s",
				(adapter->psmode) ? "Enable" : "Disable");
		पूर्ण अन्यथा अणु
			BT_DBG("PS Mode command failed");
		पूर्ण
		अवरोध;

	हाल BT_EVENT_HOST_SLEEP_CONFIG:
		अगर (!event->data[3])
			BT_DBG("gpio=%x, gap=%x", event->data[1],
							event->data[2]);
		अन्यथा
			BT_DBG("HSCFG command failed");
		अवरोध;

	हाल BT_EVENT_HOST_SLEEP_ENABLE:
		अगर (!event->data[1]) अणु
			adapter->hs_state = HS_ACTIVATED;
			अगर (adapter->psmode)
				adapter->ps_state = PS_SLEEP;
			wake_up_पूर्णांकerruptible(&adapter->event_hs_रुको_q);
			BT_DBG("HS ACTIVATED!");
		पूर्ण अन्यथा अणु
			BT_DBG("HS Enable failed");
		पूर्ण
		अवरोध;

	हाल BT_EVENT_MODULE_CFG_REQ:
		अगर (priv->bपंचांगrvl_dev.sendcmdflag &&
				event->data[1] == MODULE_BRINGUP_REQ) अणु
			BT_DBG("EVENT:%s",
				((event->data[2] == MODULE_BROUGHT_UP) ||
				(event->data[2] == MODULE_ALREADY_UP)) ?
				"Bring-up succeed" : "Bring-up failed");

			अगर (event->length > 3 && event->data[3])
				priv->bपंचांगrvl_dev.dev_type = HCI_AMP;
			अन्यथा
				priv->bपंचांगrvl_dev.dev_type = HCI_PRIMARY;

			BT_DBG("dev_type: %d", priv->bपंचांगrvl_dev.dev_type);
		पूर्ण अन्यथा अगर (priv->bपंचांगrvl_dev.sendcmdflag &&
				event->data[1] == MODULE_SHUTDOWN_REQ) अणु
			BT_DBG("EVENT:%s", (event->data[2]) ?
				"Shutdown failed" : "Shutdown succeed");
		पूर्ण अन्यथा अणु
			BT_DBG("BT_CMD_MODULE_CFG_REQ resp for APP");
			ret = -EINVAL;
		पूर्ण
		अवरोध;

	हाल BT_EVENT_POWER_STATE:
		अगर (event->data[1] == BT_PS_SLEEP)
			adapter->ps_state = PS_SLEEP;
		BT_DBG("EVENT:%s",
			(adapter->ps_state) ? "PS_SLEEP" : "PS_AWAKE");
		अवरोध;

	शेष:
		BT_DBG("Unknown Event=%d", event->data[0]);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

निकास:
	अगर (!ret)
		kमुक्त_skb(skb);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_process_event);

अटल पूर्णांक bपंचांगrvl_send_sync_cmd(काष्ठा bपंचांगrvl_निजी *priv, u16 opcode,
				स्थिर व्योम *param, u8 len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा hci_command_hdr *hdr;

	अगर (priv->surprise_हटाओd) अणु
		BT_ERR("Card is removed");
		वापस -EFAULT;
	पूर्ण

	skb = bt_skb_alloc(HCI_COMMAND_HDR_SIZE + len, GFP_KERNEL);
	अगर (!skb) अणु
		BT_ERR("No free skb");
		वापस -ENOMEM;
	पूर्ण

	hdr = skb_put(skb, HCI_COMMAND_HDR_SIZE);
	hdr->opcode = cpu_to_le16(opcode);
	hdr->plen = len;

	अगर (len)
		skb_put_data(skb, param, len);

	hci_skb_pkt_type(skb) = MRVL_VENDOR_PKT;

	skb_queue_head(&priv->adapter->tx_queue, skb);

	priv->bपंचांगrvl_dev.sendcmdflag = true;

	priv->adapter->cmd_complete = false;

	wake_up_पूर्णांकerruptible(&priv->मुख्य_thपढ़ो.रुको_q);

	अगर (!रुको_event_पूर्णांकerruptible_समयout(priv->adapter->cmd_रुको_q,
					      priv->adapter->cmd_complete ||
					      priv->surprise_हटाओd,
					      WAIT_UNTIL_CMD_RESP))
		वापस -ETIMEDOUT;

	अगर (priv->surprise_हटाओd)
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक bपंचांगrvl_send_module_cfg_cmd(काष्ठा bपंचांगrvl_निजी *priv, u8 subcmd)
अणु
	पूर्णांक ret;

	ret = bपंचांगrvl_send_sync_cmd(priv, BT_CMD_MODULE_CFG_REQ, &subcmd, 1);
	अगर (ret)
		BT_ERR("module_cfg_cmd(%x) failed", subcmd);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_send_module_cfg_cmd);

अटल पूर्णांक bपंचांगrvl_enable_sco_routing_to_host(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	पूर्णांक ret;
	u8 subcmd = 0;

	ret = bपंचांगrvl_send_sync_cmd(priv, BT_CMD_ROUTE_SCO_TO_HOST, &subcmd, 1);
	अगर (ret)
		BT_ERR("BT_CMD_ROUTE_SCO_TO_HOST command failed: %#x", ret);

	वापस ret;
पूर्ण

पूर्णांक bपंचांगrvl_pscan_winकरोw_reporting(काष्ठा bपंचांगrvl_निजी *priv, u8 subcmd)
अणु
	काष्ठा bपंचांगrvl_sdio_card *card = priv->bपंचांगrvl_dev.card;
	पूर्णांक ret;

	अगर (!card->support_pscan_win_report)
		वापस 0;

	ret = bपंचांगrvl_send_sync_cmd(priv, BT_CMD_PSCAN_WIN_REPORT_ENABLE,
				   &subcmd, 1);
	अगर (ret)
		BT_ERR("PSCAN_WIN_REPORT_ENABLE command failed: %#x", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_pscan_winकरोw_reporting);

पूर्णांक bपंचांगrvl_send_hscfg_cmd(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	पूर्णांक ret;
	u8 param[2];

	param[0] = (priv->bपंचांगrvl_dev.gpio_gap & 0xff00) >> 8;
	param[1] = (u8) (priv->bपंचांगrvl_dev.gpio_gap & 0x00ff);

	BT_DBG("Sending HSCFG Command, gpio=0x%x, gap=0x%x",
	       param[0], param[1]);

	ret = bपंचांगrvl_send_sync_cmd(priv, BT_CMD_HOST_SLEEP_CONFIG, param, 2);
	अगर (ret)
		BT_ERR("HSCFG command failed");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_send_hscfg_cmd);

पूर्णांक bपंचांगrvl_enable_ps(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	पूर्णांक ret;
	u8 param;

	अगर (priv->bपंचांगrvl_dev.psmode)
		param = BT_PS_ENABLE;
	अन्यथा
		param = BT_PS_DISABLE;

	ret = bपंचांगrvl_send_sync_cmd(priv, BT_CMD_AUTO_SLEEP_MODE, &param, 1);
	अगर (ret)
		BT_ERR("PSMODE command failed");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_enable_ps);

पूर्णांक bपंचांगrvl_enable_hs(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	काष्ठा bपंचांगrvl_adapter *adapter = priv->adapter;
	पूर्णांक ret;

	ret = bपंचांगrvl_send_sync_cmd(priv, BT_CMD_HOST_SLEEP_ENABLE, शून्य, 0);
	अगर (ret) अणु
		BT_ERR("Host sleep enable command failed");
		वापस ret;
	पूर्ण

	ret = रुको_event_पूर्णांकerruptible_समयout(adapter->event_hs_रुको_q,
					       adapter->hs_state ||
					       priv->surprise_हटाओd,
					       WAIT_UNTIL_HS_STATE_CHANGED);
	अगर (ret < 0 || priv->surprise_हटाओd) अणु
		BT_ERR("event_hs_wait_q terminated (%d): %d,%d,%d",
		       ret, adapter->hs_state, adapter->ps_state,
		       adapter->wakeup_tries);
	पूर्ण अन्यथा अगर (!ret) अणु
		BT_ERR("hs_enable timeout: %d,%d,%d", adapter->hs_state,
		       adapter->ps_state, adapter->wakeup_tries);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		BT_DBG("host sleep enabled: %d,%d,%d", adapter->hs_state,
		       adapter->ps_state, adapter->wakeup_tries);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_enable_hs);

पूर्णांक bपंचांगrvl_prepare_command(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	पूर्णांक ret = 0;

	अगर (priv->bपंचांगrvl_dev.hscfgcmd) अणु
		priv->bपंचांगrvl_dev.hscfgcmd = 0;
		bपंचांगrvl_send_hscfg_cmd(priv);
	पूर्ण

	अगर (priv->bपंचांगrvl_dev.pscmd) अणु
		priv->bपंचांगrvl_dev.pscmd = 0;
		bपंचांगrvl_enable_ps(priv);
	पूर्ण

	अगर (priv->bपंचांगrvl_dev.hscmd) अणु
		priv->bपंचांगrvl_dev.hscmd = 0;

		अगर (priv->bपंचांगrvl_dev.hsmode) अणु
			ret = bपंचांगrvl_enable_hs(priv);
		पूर्ण अन्यथा अणु
			ret = priv->hw_wakeup_firmware(priv);
			priv->adapter->hs_state = HS_DEACTIVATED;
			BT_DBG("BT: HS DEACTIVATED due to host activity!");
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_tx_pkt(काष्ठा bपंचांगrvl_निजी *priv, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = 0;

	अगर (!skb || !skb->data)
		वापस -EINVAL;

	अगर (!skb->len || ((skb->len + BTM_HEADER_LEN) > BTM_UPLD_SIZE)) अणु
		BT_ERR("Tx Error: Bad skb length %d : %d",
						skb->len, BTM_UPLD_SIZE);
		वापस -EINVAL;
	पूर्ण

	skb_push(skb, BTM_HEADER_LEN);

	/* header type: byte[3]
	 * HCI_COMMAND = 1, ACL_DATA = 2, SCO_DATA = 3, 0xFE = Venकरोr
	 * header length: byte[2][1][0]
	 */

	skb->data[0] = (skb->len & 0x0000ff);
	skb->data[1] = (skb->len & 0x00ff00) >> 8;
	skb->data[2] = (skb->len & 0xff0000) >> 16;
	skb->data[3] = hci_skb_pkt_type(skb);

	अगर (priv->hw_host_to_card)
		ret = priv->hw_host_to_card(priv, skb->data, skb->len);

	वापस ret;
पूर्ण

अटल व्योम bपंचांगrvl_init_adapter(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	पूर्णांक buf_size;

	skb_queue_head_init(&priv->adapter->tx_queue);

	priv->adapter->ps_state = PS_AWAKE;

	buf_size = ALIGN_SZ(SDIO_BLOCK_SIZE, BTSDIO_DMA_ALIGN);
	priv->adapter->hw_regs_buf = kzalloc(buf_size, GFP_KERNEL);
	अगर (!priv->adapter->hw_regs_buf) अणु
		priv->adapter->hw_regs = शून्य;
		BT_ERR("Unable to allocate buffer for hw_regs.");
	पूर्ण अन्यथा अणु
		priv->adapter->hw_regs =
			(u8 *)ALIGN_ADDR(priv->adapter->hw_regs_buf,
					 BTSDIO_DMA_ALIGN);
		BT_DBG("hw_regs_buf=%p hw_regs=%p",
		       priv->adapter->hw_regs_buf, priv->adapter->hw_regs);
	पूर्ण

	init_रुकोqueue_head(&priv->adapter->cmd_रुको_q);
	init_रुकोqueue_head(&priv->adapter->event_hs_रुको_q);
पूर्ण

अटल व्योम bपंचांगrvl_मुक्त_adapter(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	skb_queue_purge(&priv->adapter->tx_queue);

	kमुक्त(priv->adapter->hw_regs_buf);
	kमुक्त(priv->adapter);

	priv->adapter = शून्य;
पूर्ण

अटल पूर्णांक bपंचांगrvl_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = hci_get_drvdata(hdev);

	BT_DBG("type=%d, len=%d", hci_skb_pkt_type(skb), skb->len);

	अगर (priv->adapter->is_suspending || priv->adapter->is_suspended) अणु
		BT_ERR("%s: Device is suspending or suspended", __func__);
		वापस -EBUSY;
	पूर्ण

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		अवरोध;

	हाल HCI_ACLDATA_PKT:
		hdev->stat.acl_tx++;
		अवरोध;

	हाल HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		अवरोध;
	पूर्ण

	skb_queue_tail(&priv->adapter->tx_queue, skb);

	अगर (!priv->adapter->is_suspended)
		wake_up_पूर्णांकerruptible(&priv->मुख्य_thपढ़ो.रुको_q);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = hci_get_drvdata(hdev);

	skb_queue_purge(&priv->adapter->tx_queue);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = hci_get_drvdata(hdev);

	skb_queue_purge(&priv->adapter->tx_queue);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_खोलो(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_करोwnload_cal_data(काष्ठा bपंचांगrvl_निजी *priv,
				    u8 *data, पूर्णांक len)
अणु
	पूर्णांक ret;

	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = len;

	prपूर्णांक_hex_dump_bytes("Calibration data: ",
			     DUMP_PREFIX_OFFSET, data, BT_CAL_HDR_LEN + len);

	ret = bपंचांगrvl_send_sync_cmd(priv, BT_CMD_LOAD_CONFIG_DATA, data,
				   BT_CAL_HDR_LEN + len);
	अगर (ret)
		BT_ERR("Failed to download calibration data");

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_check_device_tree(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	काष्ठा device_node *dt_node;
	काष्ठा bपंचांगrvl_sdio_card *card = priv->bपंचांगrvl_dev.card;
	u8 cal_data[BT_CAL_HDR_LEN + BT_CAL_DATA_SIZE];
	पूर्णांक ret = 0;
	u16 gpio, gap;

	अगर (card->plt_of_node) अणु
		dt_node = card->plt_of_node;
		ret = of_property_पढ़ो_u16(dt_node, "marvell,wakeup-pin",
					   &gpio);
		अगर (ret)
			gpio = (priv->bपंचांगrvl_dev.gpio_gap & 0xff00) >> 8;

		ret = of_property_पढ़ो_u16(dt_node, "marvell,wakeup-gap-ms",
					   &gap);
		अगर (ret)
			gap = (u8)(priv->bपंचांगrvl_dev.gpio_gap & 0x00ff);

		priv->bपंचांगrvl_dev.gpio_gap = (gpio << 8) + gap;

		ret = of_property_पढ़ो_u8_array(dt_node, "marvell,cal-data",
						cal_data + BT_CAL_HDR_LEN,
						BT_CAL_DATA_SIZE);
		अगर (ret)
			वापस ret;

		BT_DBG("Use cal data from device tree");
		ret = bपंचांगrvl_करोwnload_cal_data(priv, cal_data,
					       BT_CAL_DATA_SIZE);
		अगर (ret)
			BT_ERR("Fail to download calibrate data");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_setup(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = hci_get_drvdata(hdev);
	पूर्णांक ret;

	ret = bपंचांगrvl_send_module_cfg_cmd(priv, MODULE_BRINGUP_REQ);
	अगर (ret)
		वापस ret;

	priv->bपंचांगrvl_dev.gpio_gap = 0xfffe;

	bपंचांगrvl_check_device_tree(priv);

	bपंचांगrvl_enable_sco_routing_to_host(priv);

	bपंचांगrvl_pscan_winकरोw_reporting(priv, 0x01);

	priv->bपंचांगrvl_dev.psmode = 1;
	bपंचांगrvl_enable_ps(priv);

	bपंचांगrvl_send_hscfg_cmd(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा sk_buff *skb;
	दीर्घ ret;
	u8 buf[8];

	buf[0] = MRVL_VENDOR_PKT;
	buf[1] = माप(bdaddr_t);
	स_नकल(buf + 2, bdaddr, माप(bdaddr_t));

	skb = __hci_cmd_sync(hdev, BT_CMD_SET_BDADDR, माप(buf), buf,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		ret = PTR_ERR(skb);
		BT_ERR("%s: changing btmrvl device address failed (%ld)",
		       hdev->name, ret);
		वापस ret;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल bool bपंचांगrvl_prevent_wake(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = hci_get_drvdata(hdev);
	काष्ठा bपंचांगrvl_sdio_card *card = priv->bपंचांगrvl_dev.card;

	वापस !device_may_wakeup(&card->func->dev);
पूर्ण

/*
 * This function handles the event generated by firmware, rx data
 * received from firmware, and tx data sent from kernel.
 */
अटल पूर्णांक bपंचांगrvl_service_मुख्य_thपढ़ो(व्योम *data)
अणु
	काष्ठा bपंचांगrvl_thपढ़ो *thपढ़ो = data;
	काष्ठा bपंचांगrvl_निजी *priv = thपढ़ो->priv;
	काष्ठा bपंचांगrvl_adapter *adapter = priv->adapter;
	रुको_queue_entry_t रुको;
	काष्ठा sk_buff *skb;
	uदीर्घ flags;

	init_रुकोqueue_entry(&रुको, current);

	क्रम (;;) अणु
		add_रुको_queue(&thपढ़ो->रुको_q, &रुको);

		set_current_state(TASK_INTERRUPTIBLE);
		अगर (kthपढ़ो_should_stop() || priv->surprise_हटाओd) अणु
			BT_DBG("main_thread: break from main thread");
			अवरोध;
		पूर्ण

		अगर (adapter->wakeup_tries ||
				((!adapter->पूर्णांक_count) &&
				(!priv->bपंचांगrvl_dev.tx_dnld_rdy ||
				skb_queue_empty(&adapter->tx_queue)))) अणु
			BT_DBG("main_thread is sleeping...");
			schedule();
		पूर्ण

		set_current_state(TASK_RUNNING);

		हटाओ_रुको_queue(&thपढ़ो->रुको_q, &रुको);

		BT_DBG("main_thread woke up");

		अगर (kthपढ़ो_should_stop() || priv->surprise_हटाओd) अणु
			BT_DBG("main_thread: break from main thread");
			अवरोध;
		पूर्ण

		spin_lock_irqsave(&priv->driver_lock, flags);
		अगर (adapter->पूर्णांक_count) अणु
			adapter->पूर्णांक_count = 0;
			spin_unlock_irqrestore(&priv->driver_lock, flags);
			priv->hw_process_पूर्णांक_status(priv);
		पूर्ण अन्यथा अगर (adapter->ps_state == PS_SLEEP &&
					!skb_queue_empty(&adapter->tx_queue)) अणु
			spin_unlock_irqrestore(&priv->driver_lock, flags);
			adapter->wakeup_tries++;
			priv->hw_wakeup_firmware(priv);
			जारी;
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&priv->driver_lock, flags);
		पूर्ण

		अगर (adapter->ps_state == PS_SLEEP)
			जारी;

		अगर (!priv->bपंचांगrvl_dev.tx_dnld_rdy ||
		    priv->adapter->is_suspended)
			जारी;

		skb = skb_dequeue(&adapter->tx_queue);
		अगर (skb) अणु
			अगर (bपंचांगrvl_tx_pkt(priv, skb))
				priv->bपंचांगrvl_dev.hcidev->stat.err_tx++;
			अन्यथा
				priv->bपंचांगrvl_dev.hcidev->stat.byte_tx += skb->len;

			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bपंचांगrvl_रेजिस्टर_hdev(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	काष्ठा hci_dev *hdev = शून्य;
	काष्ठा bपंचांगrvl_sdio_card *card = priv->bपंचांगrvl_dev.card;
	पूर्णांक ret;

	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		BT_ERR("Can not allocate HCI device");
		जाओ err_hdev;
	पूर्ण

	priv->bपंचांगrvl_dev.hcidev = hdev;
	hci_set_drvdata(hdev, priv);

	hdev->bus   = HCI_SDIO;
	hdev->खोलो  = bपंचांगrvl_खोलो;
	hdev->बंद = bपंचांगrvl_बंद;
	hdev->flush = bपंचांगrvl_flush;
	hdev->send  = bपंचांगrvl_send_frame;
	hdev->setup = bपंचांगrvl_setup;
	hdev->set_bdaddr = bपंचांगrvl_set_bdaddr;
	hdev->prevent_wake = bपंचांगrvl_prevent_wake;
	SET_HCIDEV_DEV(hdev, &card->func->dev);

	hdev->dev_type = priv->bपंचांगrvl_dev.dev_type;

	ret = hci_रेजिस्टर_dev(hdev);
	अगर (ret < 0) अणु
		BT_ERR("Can not register HCI device");
		जाओ err_hci_रेजिस्टर_dev;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	bपंचांगrvl_debugfs_init(hdev);
#पूर्ण_अगर

	वापस 0;

err_hci_रेजिस्टर_dev:
	hci_मुक्त_dev(hdev);

err_hdev:
	/* Stop the thपढ़ो servicing the पूर्णांकerrupts */
	kthपढ़ो_stop(priv->मुख्य_thपढ़ो.task);

	bपंचांगrvl_मुक्त_adapter(priv);
	kमुक्त(priv);

	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_रेजिस्टर_hdev);

काष्ठा bपंचांगrvl_निजी *bपंचांगrvl_add_card(व्योम *card)
अणु
	काष्ठा bपंचांगrvl_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		BT_ERR("Can not allocate priv");
		जाओ err_priv;
	पूर्ण

	priv->adapter = kzalloc(माप(*priv->adapter), GFP_KERNEL);
	अगर (!priv->adapter) अणु
		BT_ERR("Allocate buffer for btmrvl_adapter failed!");
		जाओ err_adapter;
	पूर्ण

	bपंचांगrvl_init_adapter(priv);

	BT_DBG("Starting kthread...");
	priv->मुख्य_thपढ़ो.priv = priv;
	spin_lock_init(&priv->driver_lock);

	init_रुकोqueue_head(&priv->मुख्य_thपढ़ो.रुको_q);
	priv->मुख्य_thपढ़ो.task = kthपढ़ो_run(bपंचांगrvl_service_मुख्य_thपढ़ो,
				&priv->मुख्य_thपढ़ो, "btmrvl_main_service");
	अगर (IS_ERR(priv->मुख्य_thपढ़ो.task))
		जाओ err_thपढ़ो;

	priv->bपंचांगrvl_dev.card = card;
	priv->bपंचांगrvl_dev.tx_dnld_rdy = true;

	वापस priv;

err_thपढ़ो:
	bपंचांगrvl_मुक्त_adapter(priv);

err_adapter:
	kमुक्त(priv);

err_priv:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_add_card);

पूर्णांक bपंचांगrvl_हटाओ_card(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	काष्ठा hci_dev *hdev;

	hdev = priv->bपंचांगrvl_dev.hcidev;

	wake_up_पूर्णांकerruptible(&priv->adapter->cmd_रुको_q);
	wake_up_पूर्णांकerruptible(&priv->adapter->event_hs_रुको_q);

	kthपढ़ो_stop(priv->मुख्य_thपढ़ो.task);

#अगर_घोषित CONFIG_DEBUG_FS
	bपंचांगrvl_debugfs_हटाओ(hdev);
#पूर्ण_अगर

	hci_unरेजिस्टर_dev(hdev);

	hci_मुक्त_dev(hdev);

	priv->bपंचांगrvl_dev.hcidev = शून्य;

	bपंचांगrvl_मुक्त_adapter(priv);

	kमुक्त(priv);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bपंचांगrvl_हटाओ_card);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell Bluetooth driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL v2");
