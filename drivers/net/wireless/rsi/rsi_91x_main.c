<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <net/rsi_91x.h>
#समावेश "rsi_mgmt.h"
#समावेश "rsi_common.h"
#समावेश "rsi_coex.h"
#समावेश "rsi_hal.h"

u32 rsi_zone_enabled = /* INFO_ZONE |
			INIT_ZONE |
			MGMT_TX_ZONE |
			MGMT_RX_ZONE |
			DATA_TX_ZONE |
			DATA_RX_ZONE |
			FSM_ZONE |
			ISR_ZONE | */
			ERR_ZONE |
			0;
EXPORT_SYMBOL_GPL(rsi_zone_enabled);

#अगर_घोषित CONFIG_RSI_COEX
अटल काष्ठा rsi_proto_ops g_proto_ops = अणु
	.coex_send_pkt = rsi_coex_send_pkt,
	.get_host_पूर्णांकf = rsi_get_host_पूर्णांकf,
	.set_bt_context = rsi_set_bt_context,
पूर्ण;
#पूर्ण_अगर

/**
 * rsi_dbg() - This function outमाला_दो inक्रमmational messages.
 * @zone: Zone of पूर्णांकerest क्रम output message.
 * @fmt: म_लिखो-style क्रमmat क्रम output message.
 *
 * Return: none
 */
व्योम rsi_dbg(u32 zone, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (zone & rsi_zone_enabled)
		pr_info("%pV", &vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(rsi_dbg);

अटल अक्षर *opmode_str(पूर्णांक oper_mode)
अणु
	चयन (oper_mode) अणु
	हाल DEV_OPMODE_WIFI_ALONE:
		वापस "Wi-Fi alone";
	हाल DEV_OPMODE_BT_ALONE:
		वापस "BT EDR alone";
	हाल DEV_OPMODE_BT_LE_ALONE:
		वापस "BT LE alone";
	हाल DEV_OPMODE_BT_DUAL:
		वापस "BT Dual";
	हाल DEV_OPMODE_STA_BT:
		वापस "Wi-Fi STA + BT EDR";
	हाल DEV_OPMODE_STA_BT_LE:
		वापस "Wi-Fi STA + BT LE";
	हाल DEV_OPMODE_STA_BT_DUAL:
		वापस "Wi-Fi STA + BT DUAL";
	हाल DEV_OPMODE_AP_BT:
		वापस "Wi-Fi AP + BT EDR";
	हाल DEV_OPMODE_AP_BT_DUAL:
		वापस "Wi-Fi AP + BT DUAL";
	पूर्ण

	वापस "Unknown";
पूर्ण

व्योम rsi_prपूर्णांक_version(काष्ठा rsi_common *common)
अणु
	rsi_dbg(ERR_ZONE, "================================================\n");
	rsi_dbg(ERR_ZONE, "================ RSI Version Info ==============\n");
	rsi_dbg(ERR_ZONE, "================================================\n");
	rsi_dbg(ERR_ZONE, "FW Version\t: %d.%d.%d\n",
		common->lmac_ver.major, common->lmac_ver.minor,
		common->lmac_ver.release_num);
	rsi_dbg(ERR_ZONE, "Operating mode\t: %d [%s]",
		common->oper_mode, opmode_str(common->oper_mode));
	rsi_dbg(ERR_ZONE, "Firmware file\t: %s", common->priv->fw_file_name);
	rsi_dbg(ERR_ZONE, "================================================\n");
पूर्ण

/**
 * rsi_prepare_skb() - This function prepares the skb.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @buffer: Poपूर्णांकer to the packet data.
 * @pkt_len: Length of the packet.
 * @extended_desc: Extended descriptor.
 *
 * Return: Successfully skb.
 */
अटल काष्ठा sk_buff *rsi_prepare_skb(काष्ठा rsi_common *common,
				       u8 *buffer,
				       u32 pkt_len,
				       u8 extended_desc)
अणु
	काष्ठा sk_buff *skb = शून्य;
	u8 payload_offset;

	अगर (WARN(!pkt_len, "%s: Dummy pkt received", __func__))
		वापस शून्य;

	अगर (pkt_len > (RSI_RCV_BUFFER_LEN * 4)) अणु
		rsi_dbg(ERR_ZONE, "%s: Pkt size > max rx buf size %d\n",
			__func__, pkt_len);
		pkt_len = RSI_RCV_BUFFER_LEN * 4;
	पूर्ण

	pkt_len -= extended_desc;
	skb = dev_alloc_skb(pkt_len + FRAME_DESC_SZ);
	अगर (skb == शून्य)
		वापस शून्य;

	payload_offset = (extended_desc + FRAME_DESC_SZ);
	skb_put(skb, pkt_len);
	स_नकल((skb->data), (buffer + payload_offset), skb->len);

	वापस skb;
पूर्ण

/**
 * rsi_पढ़ो_pkt() - This function पढ़ोs frames from the card.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @rx_pkt: Received pkt.
 * @rcv_pkt_len: Received pkt length. In हाल of USB it is 0.
 *
 * Return: 0 on success, -1 on failure.
 */
पूर्णांक rsi_पढ़ो_pkt(काष्ठा rsi_common *common, u8 *rx_pkt, s32 rcv_pkt_len)
अणु
	u8 *frame_desc = शून्य, extended_desc = 0;
	u32 index, length = 0, queueno = 0;
	u16 actual_length = 0, offset;
	काष्ठा sk_buff *skb = शून्य;
#अगर_घोषित CONFIG_RSI_COEX
	u8 bt_pkt_type;
#पूर्ण_अगर

	index = 0;
	करो अणु
		frame_desc = &rx_pkt[index];
		actual_length = *(u16 *)&frame_desc[0];
		offset = *(u16 *)&frame_desc[2];

		queueno = rsi_get_queueno(frame_desc, offset);
		length = rsi_get_length(frame_desc, offset);

		/* Extended descriptor is valid क्रम WLAN queues only */
		अगर (queueno == RSI_WIFI_DATA_Q || queueno == RSI_WIFI_MGMT_Q)
			extended_desc = rsi_get_extended_desc(frame_desc,
							      offset);

		चयन (queueno) अणु
		हाल RSI_COEX_Q:
#अगर_घोषित CONFIG_RSI_COEX
			अगर (common->coex_mode > 1)
				rsi_coex_recv_pkt(common, frame_desc + offset);
			अन्यथा
#पूर्ण_अगर
				rsi_mgmt_pkt_recv(common,
						  (frame_desc + offset));
			अवरोध;

		हाल RSI_WIFI_DATA_Q:
			skb = rsi_prepare_skb(common,
					      (frame_desc + offset),
					      length,
					      extended_desc);
			अगर (skb == शून्य)
				जाओ fail;

			rsi_indicate_pkt_to_os(common, skb);
			अवरोध;

		हाल RSI_WIFI_MGMT_Q:
			rsi_mgmt_pkt_recv(common, (frame_desc + offset));
			अवरोध;

#अगर_घोषित CONFIG_RSI_COEX
		हाल RSI_BT_MGMT_Q:
		हाल RSI_BT_DATA_Q:
#घोषणा BT_RX_PKT_TYPE_OFST	14
#घोषणा BT_CARD_READY_IND	0x89
			bt_pkt_type = frame_desc[offset + BT_RX_PKT_TYPE_OFST];
			अगर (bt_pkt_type == BT_CARD_READY_IND) अणु
				rsi_dbg(INFO_ZONE, "BT Card ready recvd\n");
				अगर (rsi_bt_ops.attach(common, &g_proto_ops))
					rsi_dbg(ERR_ZONE,
						"Failed to attach BT module\n");
			पूर्ण अन्यथा अणु
				अगर (common->bt_adapter)
					rsi_bt_ops.recv_pkt(common->bt_adapter,
							frame_desc + offset);
			पूर्ण
			अवरोध;
#पूर्ण_अगर

		शेष:
			rsi_dbg(ERR_ZONE, "%s: pkt from invalid queue: %d\n",
				__func__,   queueno);
			जाओ fail;
		पूर्ण

		index  += actual_length;
		rcv_pkt_len -= actual_length;
	पूर्ण जबतक (rcv_pkt_len > 0);

	वापस 0;
fail:
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(rsi_पढ़ो_pkt);

/**
 * rsi_tx_scheduler_thपढ़ो() - This function is a kernel thपढ़ो to send the
 *			       packets to the device.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: None.
 */
अटल व्योम rsi_tx_scheduler_thपढ़ो(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	u32 समयout = EVENT_WAIT_FOREVER;

	करो अणु
		अगर (adapter->determine_event_समयout)
			समयout = adapter->determine_event_समयout(adapter);
		rsi_रुको_event(&common->tx_thपढ़ो.event, समयout);
		rsi_reset_event(&common->tx_thपढ़ो.event);

		अगर (common->init_करोne)
			rsi_core_qos_processor(common);
	पूर्ण जबतक (atomic_पढ़ो(&common->tx_thपढ़ो.thपढ़ो_करोne) == 0);
	complete_and_निकास(&common->tx_thपढ़ो.completion, 0);
पूर्ण

#अगर_घोषित CONFIG_RSI_COEX
क्रमागत rsi_host_पूर्णांकf rsi_get_host_पूर्णांकf(व्योम *priv)
अणु
	काष्ठा rsi_common *common = (काष्ठा rsi_common *)priv;

	वापस common->priv->rsi_host_पूर्णांकf;
पूर्ण

व्योम rsi_set_bt_context(व्योम *priv, व्योम *bt_context)
अणु
	काष्ठा rsi_common *common = (काष्ठा rsi_common *)priv;

	common->bt_adapter = bt_context;
पूर्ण
#पूर्ण_अगर

/**
 * rsi_91x_init() - This function initializes os पूर्णांकerface operations.
 * @oper_mode: One of DEV_OPMODE_*.
 *
 * Return: Poपूर्णांकer to the adapter काष्ठाure on success, शून्य on failure .
 */
काष्ठा rsi_hw *rsi_91x_init(u16 oper_mode)
अणु
	काष्ठा rsi_hw *adapter = शून्य;
	काष्ठा rsi_common *common = शून्य;
	u8 ii = 0;

	adapter = kzalloc(माप(*adapter), GFP_KERNEL);
	अगर (!adapter)
		वापस शून्य;

	adapter->priv = kzalloc(माप(*common), GFP_KERNEL);
	अगर (adapter->priv == शून्य) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of memory\n",
			__func__);
		kमुक्त(adapter);
		वापस शून्य;
	पूर्ण अन्यथा अणु
		common = adapter->priv;
		common->priv = adapter;
	पूर्ण

	क्रम (ii = 0; ii < NUM_SOFT_QUEUES; ii++)
		skb_queue_head_init(&common->tx_queue[ii]);

	rsi_init_event(&common->tx_thपढ़ो.event);
	mutex_init(&common->mutex);
	mutex_init(&common->tx_lock);
	mutex_init(&common->rx_lock);
	mutex_init(&common->tx_bus_mutex);

	अगर (rsi_create_kthपढ़ो(common,
			       &common->tx_thपढ़ो,
			       rsi_tx_scheduler_thपढ़ो,
			       "Tx-Thread")) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to init tx thrd\n", __func__);
		जाओ err;
	पूर्ण

	rsi_शेष_ps_params(adapter);
	init_bgscan_params(common);
	spin_lock_init(&adapter->ps_lock);
	समयr_setup(&common->roc_समयr, rsi_roc_समयout, 0);
	init_completion(&common->wlan_init_completion);
	adapter->device_model = RSI_DEV_9113;
	common->oper_mode = oper_mode;

	/* Determine coex mode */
	चयन (common->oper_mode) अणु
	हाल DEV_OPMODE_STA_BT_DUAL:
	हाल DEV_OPMODE_STA_BT:
	हाल DEV_OPMODE_STA_BT_LE:
	हाल DEV_OPMODE_BT_ALONE:
	हाल DEV_OPMODE_BT_LE_ALONE:
	हाल DEV_OPMODE_BT_DUAL:
		common->coex_mode = 2;
		अवरोध;
	हाल DEV_OPMODE_AP_BT_DUAL:
	हाल DEV_OPMODE_AP_BT:
		common->coex_mode = 4;
		अवरोध;
	हाल DEV_OPMODE_WIFI_ALONE:
		common->coex_mode = 1;
		अवरोध;
	शेष:
		common->oper_mode = 1;
		common->coex_mode = 1;
	पूर्ण
	rsi_dbg(INFO_ZONE, "%s: oper_mode = %d, coex_mode = %d\n",
		__func__, common->oper_mode, common->coex_mode);

	adapter->device_model = RSI_DEV_9113;
#अगर_घोषित CONFIG_RSI_COEX
	अगर (common->coex_mode > 1) अणु
		अगर (rsi_coex_attach(common)) अणु
			rsi_dbg(ERR_ZONE, "Failed to init coex module\n");
			जाओ err;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	common->init_करोne = true;
	वापस adapter;

err:
	kमुक्त(common);
	kमुक्त(adapter);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(rsi_91x_init);

/**
 * rsi_91x_deinit() - This function de-पूर्णांकializes os पूर्णांकf operations.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 *
 * Return: None.
 */
व्योम rsi_91x_deinit(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_common *common = adapter->priv;
	u8 ii;

	rsi_dbg(INFO_ZONE, "%s: Performing deinit os ops\n", __func__);

	rsi_समाप्त_thपढ़ो(&common->tx_thपढ़ो);

	क्रम (ii = 0; ii < NUM_SOFT_QUEUES; ii++)
		skb_queue_purge(&common->tx_queue[ii]);

#अगर_घोषित CONFIG_RSI_COEX
	अगर (common->coex_mode > 1) अणु
		अगर (common->bt_adapter) अणु
			rsi_bt_ops.detach(common->bt_adapter);
			common->bt_adapter = शून्य;
		पूर्ण
		rsi_coex_detach(common);
	पूर्ण
#पूर्ण_अगर

	common->init_करोne = false;

	kमुक्त(common);
	kमुक्त(adapter->rsi_dev);
	kमुक्त(adapter);
पूर्ण
EXPORT_SYMBOL_GPL(rsi_91x_deinit);

/**
 * rsi_91x_hal_module_init() - This function is invoked when the module is
 *			       loaded पूर्णांकo the kernel.
 *			       It रेजिस्टरs the client driver.
 * @व्योम: Void.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_91x_hal_module_init(व्योम)
अणु
	rsi_dbg(INIT_ZONE, "%s: Module init called\n", __func__);
	वापस 0;
पूर्ण

/**
 * rsi_91x_hal_module_निकास() - This function is called at the समय of
 *			       removing/unloading the module.
 *			       It unरेजिस्टरs the client driver.
 * @व्योम: Void.
 *
 * Return: None.
 */
अटल व्योम rsi_91x_hal_module_निकास(व्योम)
अणु
	rsi_dbg(INIT_ZONE, "%s: Module exit called\n", __func__);
पूर्ण

module_init(rsi_91x_hal_module_init);
module_निकास(rsi_91x_hal_module_निकास);
MODULE_AUTHOR("Redpine Signals Inc");
MODULE_DESCRIPTION("Station driver for RSI 91x devices");
MODULE_VERSION("0.1");
MODULE_LICENSE("Dual BSD/GPL");
