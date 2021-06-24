<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम NXP PN533 NFC Chip - core functions
 *
 * Copyright (C) 2011 Instituto Nokia de Tecnologia
 * Copyright (C) 2012-2013 Tieto Poland
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/nfc.h>
#समावेश <linux/netdevice.h>
#समावेश <net/nfc/nfc.h>
#समावेश "pn533.h"

#घोषणा VERSION "0.3"

/* How much समय we spend listening क्रम initiators */
#घोषणा PN533_LISTEN_TIME 2
/* Delay between each poll frame (ms) */
#घोषणा PN533_POLL_INTERVAL 10

/* काष्ठाs क्रम pn533 commands */

/* PN533_CMD_GET_FIRMWARE_VERSION */
काष्ठा pn533_fw_version अणु
	u8 ic;
	u8 ver;
	u8 rev;
	u8 support;
पूर्ण;

/* PN533_CMD_RF_CONFIGURATION */
#घोषणा PN533_CFGITEM_RF_FIELD    0x01
#घोषणा PN533_CFGITEM_TIMING      0x02
#घोषणा PN533_CFGITEM_MAX_RETRIES 0x05
#घोषणा PN533_CFGITEM_PASORI      0x82

#घोषणा PN533_CFGITEM_RF_FIELD_AUTO_RFCA 0x2
#घोषणा PN533_CFGITEM_RF_FIELD_ON        0x1
#घोषणा PN533_CFGITEM_RF_FIELD_OFF       0x0

#घोषणा PN533_CONFIG_TIMING_102 0xb
#घोषणा PN533_CONFIG_TIMING_204 0xc
#घोषणा PN533_CONFIG_TIMING_409 0xd
#घोषणा PN533_CONFIG_TIMING_819 0xe

#घोषणा PN533_CONFIG_MAX_RETRIES_NO_RETRY 0x00
#घोषणा PN533_CONFIG_MAX_RETRIES_ENDLESS 0xFF

काष्ठा pn533_config_max_retries अणु
	u8 mx_rty_atr;
	u8 mx_rty_psl;
	u8 mx_rty_passive_act;
पूर्ण __packed;

काष्ठा pn533_config_timing अणु
	u8 rfu;
	u8 atr_res_समयout;
	u8 dep_समयout;
पूर्ण __packed;

/* PN533_CMD_IN_LIST_PASSIVE_TARGET */

/* felica commands opcode */
#घोषणा PN533_FELICA_OPC_SENSF_REQ 0
#घोषणा PN533_FELICA_OPC_SENSF_RES 1
/* felica SENSF_REQ parameters */
#घोषणा PN533_FELICA_SENSF_SC_ALL 0xFFFF
#घोषणा PN533_FELICA_SENSF_RC_NO_SYSTEM_CODE 0
#घोषणा PN533_FELICA_SENSF_RC_SYSTEM_CODE 1
#घोषणा PN533_FELICA_SENSF_RC_ADVANCED_PROTOCOL 2

/* type B initiator_data values */
#घोषणा PN533_TYPE_B_AFI_ALL_FAMILIES 0
#घोषणा PN533_TYPE_B_POLL_METHOD_TIMESLOT 0
#घोषणा PN533_TYPE_B_POLL_METHOD_PROBABILISTIC 1

जोड़ pn533_cmd_poll_initdata अणु
	काष्ठा अणु
		u8 afi;
		u8 polling_method;
	पूर्ण __packed type_b;
	काष्ठा अणु
		u8 opcode;
		__be16 sc;
		u8 rc;
		u8 tsn;
	पूर्ण __packed felica;
पूर्ण;

काष्ठा pn533_poll_modulations अणु
	काष्ठा अणु
		u8 maxtg;
		u8 brty;
		जोड़ pn533_cmd_poll_initdata initiator_data;
	पूर्ण __packed data;
	u8 len;
पूर्ण;

अटल स्थिर काष्ठा pn533_poll_modulations poll_mod[] = अणु
	[PN533_POLL_MOD_106KBPS_A] = अणु
		.data = अणु
			.maxtg = 1,
			.brty = 0,
		पूर्ण,
		.len = 2,
	पूर्ण,
	[PN533_POLL_MOD_212KBPS_FELICA] = अणु
		.data = अणु
			.maxtg = 1,
			.brty = 1,
			.initiator_data.felica = अणु
				.opcode = PN533_FELICA_OPC_SENSF_REQ,
				.sc = PN533_FELICA_SENSF_SC_ALL,
				.rc = PN533_FELICA_SENSF_RC_SYSTEM_CODE,
				.tsn = 0x03,
			पूर्ण,
		पूर्ण,
		.len = 7,
	पूर्ण,
	[PN533_POLL_MOD_424KBPS_FELICA] = अणु
		.data = अणु
			.maxtg = 1,
			.brty = 2,
			.initiator_data.felica = अणु
				.opcode = PN533_FELICA_OPC_SENSF_REQ,
				.sc = PN533_FELICA_SENSF_SC_ALL,
				.rc = PN533_FELICA_SENSF_RC_SYSTEM_CODE,
				.tsn = 0x03,
			पूर्ण,
		 पूर्ण,
		.len = 7,
	पूर्ण,
	[PN533_POLL_MOD_106KBPS_JEWEL] = अणु
		.data = अणु
			.maxtg = 1,
			.brty = 4,
		पूर्ण,
		.len = 2,
	पूर्ण,
	[PN533_POLL_MOD_847KBPS_B] = अणु
		.data = अणु
			.maxtg = 1,
			.brty = 8,
			.initiator_data.type_b = अणु
				.afi = PN533_TYPE_B_AFI_ALL_FAMILIES,
				.polling_method =
					PN533_TYPE_B_POLL_METHOD_TIMESLOT,
			पूर्ण,
		पूर्ण,
		.len = 3,
	पूर्ण,
	[PN533_LISTEN_MOD] = अणु
		.len = 0,
	पूर्ण,
पूर्ण;

/* PN533_CMD_IN_ATR */

काष्ठा pn533_cmd_activate_response अणु
	u8 status;
	u8 nfcid3t[10];
	u8 didt;
	u8 bst;
	u8 brt;
	u8 to;
	u8 ppt;
	/* optional */
	u8 gt[];
पूर्ण __packed;

काष्ठा pn533_cmd_jump_dep_response अणु
	u8 status;
	u8 tg;
	u8 nfcid3t[10];
	u8 didt;
	u8 bst;
	u8 brt;
	u8 to;
	u8 ppt;
	/* optional */
	u8 gt[];
पूर्ण __packed;

काष्ठा pn532_स्वतःpoll_resp अणु
	u8 type;
	u8 ln;
	u8 tg;
	u8 tgdata[];
पूर्ण;

/* PN532_CMD_IN_AUTOPOLL */
#घोषणा PN532_AUTOPOLL_POLLNR_INFINITE	0xff
#घोषणा PN532_AUTOPOLL_PERIOD		0x03 /* in units of 150 ms */

#घोषणा PN532_AUTOPOLL_TYPE_GENERIC_106		0x00
#घोषणा PN532_AUTOPOLL_TYPE_GENERIC_212		0x01
#घोषणा PN532_AUTOPOLL_TYPE_GENERIC_424		0x02
#घोषणा PN532_AUTOPOLL_TYPE_JEWEL		0x04
#घोषणा PN532_AUTOPOLL_TYPE_MIFARE		0x10
#घोषणा PN532_AUTOPOLL_TYPE_FELICA212		0x11
#घोषणा PN532_AUTOPOLL_TYPE_FELICA424		0x12
#घोषणा PN532_AUTOPOLL_TYPE_ISOA		0x20
#घोषणा PN532_AUTOPOLL_TYPE_ISOB		0x23
#घोषणा PN532_AUTOPOLL_TYPE_DEP_PASSIVE_106	0x40
#घोषणा PN532_AUTOPOLL_TYPE_DEP_PASSIVE_212	0x41
#घोषणा PN532_AUTOPOLL_TYPE_DEP_PASSIVE_424	0x42
#घोषणा PN532_AUTOPOLL_TYPE_DEP_ACTIVE_106	0x80
#घोषणा PN532_AUTOPOLL_TYPE_DEP_ACTIVE_212	0x81
#घोषणा PN532_AUTOPOLL_TYPE_DEP_ACTIVE_424	0x82

/* PN533_TG_INIT_AS_TARGET */
#घोषणा PN533_INIT_TARGET_PASSIVE 0x1
#घोषणा PN533_INIT_TARGET_DEP 0x2

#घोषणा PN533_INIT_TARGET_RESP_FRAME_MASK 0x3
#घोषणा PN533_INIT_TARGET_RESP_ACTIVE     0x1
#घोषणा PN533_INIT_TARGET_RESP_DEP        0x4

/* The rule: value(high byte) + value(low byte) + checksum = 0 */
अटल अंतरभूत u8 pn533_ext_checksum(u16 value)
अणु
	वापस ~(u8)(((value & 0xFF00) >> 8) + (u8)(value & 0xFF)) + 1;
पूर्ण

/* The rule: value + checksum = 0 */
अटल अंतरभूत u8 pn533_std_checksum(u8 value)
अणु
	वापस ~value + 1;
पूर्ण

/* The rule: sum(data elements) + checksum = 0 */
अटल u8 pn533_std_data_checksum(u8 *data, पूर्णांक datalen)
अणु
	u8 sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < datalen; i++)
		sum += data[i];

	वापस pn533_std_checksum(sum);
पूर्ण

अटल व्योम pn533_std_tx_frame_init(व्योम *_frame, u8 cmd_code)
अणु
	काष्ठा pn533_std_frame *frame = _frame;

	frame->preamble = 0;
	frame->start_frame = cpu_to_be16(PN533_STD_FRAME_SOF);
	PN533_STD_FRAME_IDENTIFIER(frame) = PN533_STD_FRAME_सूची_OUT;
	PN533_FRAME_CMD(frame) = cmd_code;
	frame->datalen = 2;
पूर्ण

अटल व्योम pn533_std_tx_frame_finish(व्योम *_frame)
अणु
	काष्ठा pn533_std_frame *frame = _frame;

	frame->datalen_checksum = pn533_std_checksum(frame->datalen);

	PN533_STD_FRAME_CHECKSUM(frame) =
		pn533_std_data_checksum(frame->data, frame->datalen);

	PN533_STD_FRAME_POSTAMBLE(frame) = 0;
पूर्ण

अटल व्योम pn533_std_tx_update_payload_len(व्योम *_frame, पूर्णांक len)
अणु
	काष्ठा pn533_std_frame *frame = _frame;

	frame->datalen += len;
पूर्ण

अटल bool pn533_std_rx_frame_is_valid(व्योम *_frame, काष्ठा pn533 *dev)
अणु
	u8 checksum;
	काष्ठा pn533_std_frame *stdf = _frame;

	अगर (stdf->start_frame != cpu_to_be16(PN533_STD_FRAME_SOF))
		वापस false;

	अगर (likely(!PN533_STD_IS_EXTENDED(stdf))) अणु
		/* Standard frame code */
		dev->ops->rx_header_len = PN533_STD_FRAME_HEADER_LEN;

		checksum = pn533_std_checksum(stdf->datalen);
		अगर (checksum != stdf->datalen_checksum)
			वापस false;

		checksum = pn533_std_data_checksum(stdf->data, stdf->datalen);
		अगर (checksum != PN533_STD_FRAME_CHECKSUM(stdf))
			वापस false;
	पूर्ण अन्यथा अणु
		/* Extended */
		काष्ठा pn533_ext_frame *eअगर = _frame;

		dev->ops->rx_header_len = PN533_EXT_FRAME_HEADER_LEN;

		checksum = pn533_ext_checksum(be16_to_cpu(eअगर->datalen));
		अगर (checksum != eअगर->datalen_checksum)
			वापस false;

		/* check data checksum */
		checksum = pn533_std_data_checksum(eअगर->data,
						   be16_to_cpu(eअगर->datalen));
		अगर (checksum != PN533_EXT_FRAME_CHECKSUM(eअगर))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool pn533_rx_frame_is_ack(व्योम *_frame)
अणु
	काष्ठा pn533_std_frame *frame = _frame;

	अगर (frame->start_frame != cpu_to_be16(PN533_STD_FRAME_SOF))
		वापस false;

	अगर (frame->datalen != 0 || frame->datalen_checksum != 0xFF)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(pn533_rx_frame_is_ack);

अटल अंतरभूत पूर्णांक pn533_std_rx_frame_size(व्योम *frame)
अणु
	काष्ठा pn533_std_frame *f = frame;

	/* check क्रम Extended Inक्रमmation frame */
	अगर (PN533_STD_IS_EXTENDED(f)) अणु
		काष्ठा pn533_ext_frame *eअगर = frame;

		वापस माप(काष्ठा pn533_ext_frame)
			+ be16_to_cpu(eअगर->datalen) + PN533_STD_FRAME_TAIL_LEN;
	पूर्ण

	वापस माप(काष्ठा pn533_std_frame) + f->datalen +
	       PN533_STD_FRAME_TAIL_LEN;
पूर्ण

अटल u8 pn533_std_get_cmd_code(व्योम *frame)
अणु
	काष्ठा pn533_std_frame *f = frame;
	काष्ठा pn533_ext_frame *eअगर = frame;

	अगर (PN533_STD_IS_EXTENDED(f))
		वापस PN533_FRAME_CMD(eअगर);
	अन्यथा
		वापस PN533_FRAME_CMD(f);
पूर्ण

bool pn533_rx_frame_is_cmd_response(काष्ठा pn533 *dev, व्योम *frame)
अणु
	वापस (dev->ops->get_cmd_code(frame) ==
				PN533_CMD_RESPONSE(dev->cmd->code));
पूर्ण
EXPORT_SYMBOL_GPL(pn533_rx_frame_is_cmd_response);


अटल काष्ठा pn533_frame_ops pn533_std_frame_ops = अणु
	.tx_frame_init = pn533_std_tx_frame_init,
	.tx_frame_finish = pn533_std_tx_frame_finish,
	.tx_update_payload_len = pn533_std_tx_update_payload_len,
	.tx_header_len = PN533_STD_FRAME_HEADER_LEN,
	.tx_tail_len = PN533_STD_FRAME_TAIL_LEN,

	.rx_is_frame_valid = pn533_std_rx_frame_is_valid,
	.rx_frame_size = pn533_std_rx_frame_size,
	.rx_header_len = PN533_STD_FRAME_HEADER_LEN,
	.rx_tail_len = PN533_STD_FRAME_TAIL_LEN,

	.max_payload_len =  PN533_STD_FRAME_MAX_PAYLOAD_LEN,
	.get_cmd_code = pn533_std_get_cmd_code,
पूर्ण;

अटल व्योम pn533_build_cmd_frame(काष्ठा pn533 *dev, u8 cmd_code,
				  काष्ठा sk_buff *skb)
अणु
	/* payload is alपढ़ोy there, just update datalen */
	पूर्णांक payload_len = skb->len;
	काष्ठा pn533_frame_ops *ops = dev->ops;


	skb_push(skb, ops->tx_header_len);
	skb_put(skb, ops->tx_tail_len);

	ops->tx_frame_init(skb->data, cmd_code);
	ops->tx_update_payload_len(skb->data, payload_len);
	ops->tx_frame_finish(skb->data);
पूर्ण

अटल पूर्णांक pn533_send_async_complete(काष्ठा pn533 *dev)
अणु
	काष्ठा pn533_cmd *cmd = dev->cmd;
	काष्ठा sk_buff *resp;
	पूर्णांक status, rc = 0;

	अगर (!cmd) अणु
		dev_dbg(dev->dev, "%s: cmd not set\n", __func__);
		जाओ करोne;
	पूर्ण

	dev_kमुक्त_skb(cmd->req);

	status = cmd->status;
	resp = cmd->resp;

	अगर (status < 0) अणु
		rc = cmd->complete_cb(dev, cmd->complete_cb_context,
				      ERR_PTR(status));
		dev_kमुक्त_skb(resp);
		जाओ करोne;
	पूर्ण

	/* when no response is set we got पूर्णांकerrupted */
	अगर (!resp)
		resp = ERR_PTR(-EINTR);

	अगर (!IS_ERR(resp)) अणु
		skb_pull(resp, dev->ops->rx_header_len);
		skb_trim(resp, resp->len - dev->ops->rx_tail_len);
	पूर्ण

	rc = cmd->complete_cb(dev, cmd->complete_cb_context, resp);

करोne:
	kमुक्त(cmd);
	dev->cmd = शून्य;
	वापस rc;
पूर्ण

अटल पूर्णांक __pn533_send_async(काष्ठा pn533 *dev, u8 cmd_code,
			      काष्ठा sk_buff *req,
			      pn533_send_async_complete_t complete_cb,
			      व्योम *complete_cb_context)
अणु
	काष्ठा pn533_cmd *cmd;
	पूर्णांक rc = 0;

	dev_dbg(dev->dev, "Sending command 0x%x\n", cmd_code);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->code = cmd_code;
	cmd->req = req;
	cmd->complete_cb = complete_cb;
	cmd->complete_cb_context = complete_cb_context;

	pn533_build_cmd_frame(dev, cmd_code, req);

	mutex_lock(&dev->cmd_lock);

	अगर (!dev->cmd_pending) अणु
		dev->cmd = cmd;
		rc = dev->phy_ops->send_frame(dev, req);
		अगर (rc) अणु
			dev->cmd = शून्य;
			जाओ error;
		पूर्ण

		dev->cmd_pending = 1;
		जाओ unlock;
	पूर्ण

	dev_dbg(dev->dev, "%s Queueing command 0x%x\n",
		__func__, cmd_code);

	INIT_LIST_HEAD(&cmd->queue);
	list_add_tail(&cmd->queue, &dev->cmd_queue);

	जाओ unlock;

error:
	kमुक्त(cmd);
unlock:
	mutex_unlock(&dev->cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक pn533_send_data_async(काष्ठा pn533 *dev, u8 cmd_code,
				 काष्ठा sk_buff *req,
				 pn533_send_async_complete_t complete_cb,
				 व्योम *complete_cb_context)
अणु
	वापस __pn533_send_async(dev, cmd_code, req, complete_cb,
				complete_cb_context);
पूर्ण

अटल पूर्णांक pn533_send_cmd_async(काष्ठा pn533 *dev, u8 cmd_code,
				काष्ठा sk_buff *req,
				pn533_send_async_complete_t complete_cb,
				व्योम *complete_cb_context)
अणु
	वापस __pn533_send_async(dev, cmd_code, req, complete_cb,
				complete_cb_context);
पूर्ण

/*
 * pn533_send_cmd_direct_async
 *
 * The function sends a priority cmd directly to the chip omitting the cmd
 * queue. It's पूर्णांकended to be used by chaining mechanism of received responses
 * where the host has to request every single chunk of data beक्रमe scheduling
 * next cmd from the queue.
 */
अटल पूर्णांक pn533_send_cmd_direct_async(काष्ठा pn533 *dev, u8 cmd_code,
				       काष्ठा sk_buff *req,
				       pn533_send_async_complete_t complete_cb,
				       व्योम *complete_cb_context)
अणु
	काष्ठा pn533_cmd *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->code = cmd_code;
	cmd->req = req;
	cmd->complete_cb = complete_cb;
	cmd->complete_cb_context = complete_cb_context;

	pn533_build_cmd_frame(dev, cmd_code, req);

	dev->cmd = cmd;
	rc = dev->phy_ops->send_frame(dev, req);
	अगर (rc < 0) अणु
		dev->cmd = शून्य;
		kमुक्त(cmd);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम pn533_wq_cmd_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pn533 *dev = container_of(work, काष्ठा pn533, cmd_complete_work);
	पूर्णांक rc;

	rc = pn533_send_async_complete(dev);
	अगर (rc != -EINPROGRESS)
		queue_work(dev->wq, &dev->cmd_work);
पूर्ण

अटल व्योम pn533_wq_cmd(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pn533 *dev = container_of(work, काष्ठा pn533, cmd_work);
	काष्ठा pn533_cmd *cmd;
	पूर्णांक rc;

	mutex_lock(&dev->cmd_lock);

	अगर (list_empty(&dev->cmd_queue)) अणु
		dev->cmd_pending = 0;
		mutex_unlock(&dev->cmd_lock);
		वापस;
	पूर्ण

	cmd = list_first_entry(&dev->cmd_queue, काष्ठा pn533_cmd, queue);

	list_del(&cmd->queue);

	mutex_unlock(&dev->cmd_lock);

	dev->cmd = cmd;
	rc = dev->phy_ops->send_frame(dev, cmd->req);
	अगर (rc < 0) अणु
		dev->cmd = शून्य;
		dev_kमुक्त_skb(cmd->req);
		kमुक्त(cmd);
		वापस;
	पूर्ण

पूर्ण

काष्ठा pn533_sync_cmd_response अणु
	काष्ठा sk_buff *resp;
	काष्ठा completion करोne;
पूर्ण;

अटल पूर्णांक pn533_send_sync_complete(काष्ठा pn533 *dev, व्योम *_arg,
				    काष्ठा sk_buff *resp)
अणु
	काष्ठा pn533_sync_cmd_response *arg = _arg;

	arg->resp = resp;
	complete(&arg->करोne);

	वापस 0;
पूर्ण

/*  pn533_send_cmd_sync
 *
 *  Please note the req parameter is मुक्तd inside the function to
 *  limit a number of वापस value पूर्णांकerpretations by the caller.
 *
 *  1. negative in हाल of error during TX path -> req should be मुक्तd
 *
 *  2. negative in हाल of error during RX path -> req should not be मुक्तd
 *     as it's been alपढ़ोy मुक्तd at the beginning of RX path by
 *     async_complete_cb.
 *
 *  3. valid poपूर्णांकer in हाल of successful RX path
 *
 *  A caller has to check a वापस value with IS_ERR macro. If the test pass,
 *  the वापसed poपूर्णांकer is valid.
 *
 */
अटल काष्ठा sk_buff *pn533_send_cmd_sync(काष्ठा pn533 *dev, u8 cmd_code,
					       काष्ठा sk_buff *req)
अणु
	पूर्णांक rc;
	काष्ठा pn533_sync_cmd_response arg;

	init_completion(&arg.करोne);

	rc = pn533_send_cmd_async(dev, cmd_code, req,
				  pn533_send_sync_complete, &arg);
	अगर (rc) अणु
		dev_kमुक्त_skb(req);
		वापस ERR_PTR(rc);
	पूर्ण

	रुको_क्रम_completion(&arg.करोne);

	वापस arg.resp;
पूर्ण

अटल काष्ठा sk_buff *pn533_alloc_skb(काष्ठा pn533 *dev, अचिन्हित पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(dev->ops->tx_header_len +
			size +
			dev->ops->tx_tail_len, GFP_KERNEL);

	अगर (skb)
		skb_reserve(skb, dev->ops->tx_header_len);

	वापस skb;
पूर्ण

काष्ठा pn533_target_type_a अणु
	__be16 sens_res;
	u8 sel_res;
	u8 nfcid_len;
	u8 nfcid_data[];
पूर्ण __packed;


#घोषणा PN533_TYPE_A_SENS_RES_NFCID1(x) ((u8)((be16_to_cpu(x) & 0x00C0) >> 6))
#घोषणा PN533_TYPE_A_SENS_RES_SSD(x) ((u8)((be16_to_cpu(x) & 0x001F) >> 0))
#घोषणा PN533_TYPE_A_SENS_RES_PLATCONF(x) ((u8)((be16_to_cpu(x) & 0x0F00) >> 8))

#घोषणा PN533_TYPE_A_SENS_RES_SSD_JEWEL 0x00
#घोषणा PN533_TYPE_A_SENS_RES_PLATCONF_JEWEL 0x0C

#घोषणा PN533_TYPE_A_SEL_PROT(x) (((x) & 0x60) >> 5)
#घोषणा PN533_TYPE_A_SEL_CASCADE(x) (((x) & 0x04) >> 2)

#घोषणा PN533_TYPE_A_SEL_PROT_MIFARE 0
#घोषणा PN533_TYPE_A_SEL_PROT_ISO14443 1
#घोषणा PN533_TYPE_A_SEL_PROT_DEP 2
#घोषणा PN533_TYPE_A_SEL_PROT_ISO14443_DEP 3

अटल bool pn533_target_type_a_is_valid(काष्ठा pn533_target_type_a *type_a,
							पूर्णांक target_data_len)
अणु
	u8 ssd;
	u8 platconf;

	अगर (target_data_len < माप(काष्ठा pn533_target_type_a))
		वापस false;

	/*
	 * The length check of nfcid[] and ats[] are not being perक्रमmed because
	 * the values are not being used
	 */

	/* Requirement 4.6.3.3 from NFC Forum Digital Spec */
	ssd = PN533_TYPE_A_SENS_RES_SSD(type_a->sens_res);
	platconf = PN533_TYPE_A_SENS_RES_PLATCONF(type_a->sens_res);

	अगर ((ssd == PN533_TYPE_A_SENS_RES_SSD_JEWEL &&
	     platconf != PN533_TYPE_A_SENS_RES_PLATCONF_JEWEL) ||
	    (ssd != PN533_TYPE_A_SENS_RES_SSD_JEWEL &&
	     platconf == PN533_TYPE_A_SENS_RES_PLATCONF_JEWEL))
		वापस false;

	/* Requirements 4.8.2.1, 4.8.2.3, 4.8.2.5 and 4.8.2.7 from NFC Forum */
	अगर (PN533_TYPE_A_SEL_CASCADE(type_a->sel_res) != 0)
		वापस false;

	अगर (type_a->nfcid_len > NFC_NFCID1_MAXSIZE)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक pn533_target_found_type_a(काष्ठा nfc_target *nfc_tgt, u8 *tgt_data,
							पूर्णांक tgt_data_len)
अणु
	काष्ठा pn533_target_type_a *tgt_type_a;

	tgt_type_a = (काष्ठा pn533_target_type_a *)tgt_data;

	अगर (!pn533_target_type_a_is_valid(tgt_type_a, tgt_data_len))
		वापस -EPROTO;

	चयन (PN533_TYPE_A_SEL_PROT(tgt_type_a->sel_res)) अणु
	हाल PN533_TYPE_A_SEL_PROT_MIFARE:
		nfc_tgt->supported_protocols = NFC_PROTO_MIFARE_MASK;
		अवरोध;
	हाल PN533_TYPE_A_SEL_PROT_ISO14443:
		nfc_tgt->supported_protocols = NFC_PROTO_ISO14443_MASK;
		अवरोध;
	हाल PN533_TYPE_A_SEL_PROT_DEP:
		nfc_tgt->supported_protocols = NFC_PROTO_NFC_DEP_MASK;
		अवरोध;
	हाल PN533_TYPE_A_SEL_PROT_ISO14443_DEP:
		nfc_tgt->supported_protocols = NFC_PROTO_ISO14443_MASK |
							NFC_PROTO_NFC_DEP_MASK;
		अवरोध;
	पूर्ण

	nfc_tgt->sens_res = be16_to_cpu(tgt_type_a->sens_res);
	nfc_tgt->sel_res = tgt_type_a->sel_res;
	nfc_tgt->nfcid1_len = tgt_type_a->nfcid_len;
	स_नकल(nfc_tgt->nfcid1, tgt_type_a->nfcid_data, nfc_tgt->nfcid1_len);

	वापस 0;
पूर्ण

काष्ठा pn533_target_felica अणु
	u8 pol_res;
	u8 opcode;
	u8 nfcid2[NFC_NFCID2_MAXSIZE];
	u8 pad[8];
	/* optional */
	u8 syst_code[];
पूर्ण __packed;

#घोषणा PN533_FELICA_SENSF_NFCID2_DEP_B1 0x01
#घोषणा PN533_FELICA_SENSF_NFCID2_DEP_B2 0xFE

अटल bool pn533_target_felica_is_valid(काष्ठा pn533_target_felica *felica,
							पूर्णांक target_data_len)
अणु
	अगर (target_data_len < माप(काष्ठा pn533_target_felica))
		वापस false;

	अगर (felica->opcode != PN533_FELICA_OPC_SENSF_RES)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक pn533_target_found_felica(काष्ठा nfc_target *nfc_tgt, u8 *tgt_data,
							पूर्णांक tgt_data_len)
अणु
	काष्ठा pn533_target_felica *tgt_felica;

	tgt_felica = (काष्ठा pn533_target_felica *)tgt_data;

	अगर (!pn533_target_felica_is_valid(tgt_felica, tgt_data_len))
		वापस -EPROTO;

	अगर ((tgt_felica->nfcid2[0] == PN533_FELICA_SENSF_NFCID2_DEP_B1) &&
	    (tgt_felica->nfcid2[1] == PN533_FELICA_SENSF_NFCID2_DEP_B2))
		nfc_tgt->supported_protocols = NFC_PROTO_NFC_DEP_MASK;
	अन्यथा
		nfc_tgt->supported_protocols = NFC_PROTO_FELICA_MASK;

	स_नकल(nfc_tgt->sensf_res, &tgt_felica->opcode, 9);
	nfc_tgt->sensf_res_len = 9;

	स_नकल(nfc_tgt->nfcid2, tgt_felica->nfcid2, NFC_NFCID2_MAXSIZE);
	nfc_tgt->nfcid2_len = NFC_NFCID2_MAXSIZE;

	वापस 0;
पूर्ण

काष्ठा pn533_target_jewel अणु
	__be16 sens_res;
	u8 jewelid[4];
पूर्ण __packed;

अटल bool pn533_target_jewel_is_valid(काष्ठा pn533_target_jewel *jewel,
							पूर्णांक target_data_len)
अणु
	u8 ssd;
	u8 platconf;

	अगर (target_data_len < माप(काष्ठा pn533_target_jewel))
		वापस false;

	/* Requirement 4.6.3.3 from NFC Forum Digital Spec */
	ssd = PN533_TYPE_A_SENS_RES_SSD(jewel->sens_res);
	platconf = PN533_TYPE_A_SENS_RES_PLATCONF(jewel->sens_res);

	अगर ((ssd == PN533_TYPE_A_SENS_RES_SSD_JEWEL &&
	     platconf != PN533_TYPE_A_SENS_RES_PLATCONF_JEWEL) ||
	    (ssd != PN533_TYPE_A_SENS_RES_SSD_JEWEL &&
	     platconf == PN533_TYPE_A_SENS_RES_PLATCONF_JEWEL))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक pn533_target_found_jewel(काष्ठा nfc_target *nfc_tgt, u8 *tgt_data,
							पूर्णांक tgt_data_len)
अणु
	काष्ठा pn533_target_jewel *tgt_jewel;

	tgt_jewel = (काष्ठा pn533_target_jewel *)tgt_data;

	अगर (!pn533_target_jewel_is_valid(tgt_jewel, tgt_data_len))
		वापस -EPROTO;

	nfc_tgt->supported_protocols = NFC_PROTO_JEWEL_MASK;
	nfc_tgt->sens_res = be16_to_cpu(tgt_jewel->sens_res);
	nfc_tgt->nfcid1_len = 4;
	स_नकल(nfc_tgt->nfcid1, tgt_jewel->jewelid, nfc_tgt->nfcid1_len);

	वापस 0;
पूर्ण

काष्ठा pn533_type_b_prot_info अणु
	u8 bitrate;
	u8 fsci_type;
	u8 fwi_adc_fo;
पूर्ण __packed;

#घोषणा PN533_TYPE_B_PROT_FCSI(x) (((x) & 0xF0) >> 4)
#घोषणा PN533_TYPE_B_PROT_TYPE(x) (((x) & 0x0F) >> 0)
#घोषणा PN533_TYPE_B_PROT_TYPE_RFU_MASK 0x8

काष्ठा pn533_type_b_sens_res अणु
	u8 opcode;
	u8 nfcid[4];
	u8 appdata[4];
	काष्ठा pn533_type_b_prot_info prot_info;
पूर्ण __packed;

#घोषणा PN533_TYPE_B_OPC_SENSB_RES 0x50

काष्ठा pn533_target_type_b अणु
	काष्ठा pn533_type_b_sens_res sensb_res;
	u8 attrib_res_len;
	u8 attrib_res[];
पूर्ण __packed;

अटल bool pn533_target_type_b_is_valid(काष्ठा pn533_target_type_b *type_b,
							पूर्णांक target_data_len)
अणु
	अगर (target_data_len < माप(काष्ठा pn533_target_type_b))
		वापस false;

	अगर (type_b->sensb_res.opcode != PN533_TYPE_B_OPC_SENSB_RES)
		वापस false;

	अगर (PN533_TYPE_B_PROT_TYPE(type_b->sensb_res.prot_info.fsci_type) &
						PN533_TYPE_B_PROT_TYPE_RFU_MASK)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक pn533_target_found_type_b(काष्ठा nfc_target *nfc_tgt, u8 *tgt_data,
							पूर्णांक tgt_data_len)
अणु
	काष्ठा pn533_target_type_b *tgt_type_b;

	tgt_type_b = (काष्ठा pn533_target_type_b *)tgt_data;

	अगर (!pn533_target_type_b_is_valid(tgt_type_b, tgt_data_len))
		वापस -EPROTO;

	nfc_tgt->supported_protocols = NFC_PROTO_ISO14443_B_MASK;

	वापस 0;
पूर्ण

अटल व्योम pn533_poll_reset_mod_list(काष्ठा pn533 *dev);
अटल पूर्णांक pn533_target_found(काष्ठा pn533 *dev, u8 tg, u8 *tgdata,
			      पूर्णांक tgdata_len)
अणु
	काष्ठा nfc_target nfc_tgt;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s: modulation=%d\n",
		__func__, dev->poll_mod_curr);

	अगर (tg != 1)
		वापस -EPROTO;

	स_रखो(&nfc_tgt, 0, माप(काष्ठा nfc_target));

	चयन (dev->poll_mod_curr) अणु
	हाल PN533_POLL_MOD_106KBPS_A:
		rc = pn533_target_found_type_a(&nfc_tgt, tgdata, tgdata_len);
		अवरोध;
	हाल PN533_POLL_MOD_212KBPS_FELICA:
	हाल PN533_POLL_MOD_424KBPS_FELICA:
		rc = pn533_target_found_felica(&nfc_tgt, tgdata, tgdata_len);
		अवरोध;
	हाल PN533_POLL_MOD_106KBPS_JEWEL:
		rc = pn533_target_found_jewel(&nfc_tgt, tgdata, tgdata_len);
		अवरोध;
	हाल PN533_POLL_MOD_847KBPS_B:
		rc = pn533_target_found_type_b(&nfc_tgt, tgdata, tgdata_len);
		अवरोध;
	शेष:
		nfc_err(dev->dev,
			"Unknown current poll modulation\n");
		वापस -EPROTO;
	पूर्ण

	अगर (rc)
		वापस rc;

	अगर (!(nfc_tgt.supported_protocols & dev->poll_protocols)) अणु
		dev_dbg(dev->dev,
			"The Tg found doesn't have the desired protocol\n");
		वापस -EAGAIN;
	पूर्ण

	dev_dbg(dev->dev,
		"Target found - supported protocols: 0x%x\n",
		nfc_tgt.supported_protocols);

	dev->tgt_available_prots = nfc_tgt.supported_protocols;

	pn533_poll_reset_mod_list(dev);
	nfc_tarमाला_लो_found(dev->nfc_dev, &nfc_tgt, 1);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pn533_poll_next_mod(काष्ठा pn533 *dev)
अणु
	dev->poll_mod_curr = (dev->poll_mod_curr + 1) % dev->poll_mod_count;
पूर्ण

अटल व्योम pn533_poll_reset_mod_list(काष्ठा pn533 *dev)
अणु
	dev->poll_mod_count = 0;
पूर्ण

अटल व्योम pn533_poll_add_mod(काष्ठा pn533 *dev, u8 mod_index)
अणु
	dev->poll_mod_active[dev->poll_mod_count] =
		(काष्ठा pn533_poll_modulations *)&poll_mod[mod_index];
	dev->poll_mod_count++;
पूर्ण

अटल व्योम pn533_poll_create_mod_list(काष्ठा pn533 *dev,
				       u32 im_protocols, u32 पंचांग_protocols)
अणु
	pn533_poll_reset_mod_list(dev);

	अगर ((im_protocols & NFC_PROTO_MIFARE_MASK) ||
	    (im_protocols & NFC_PROTO_ISO14443_MASK) ||
	    (im_protocols & NFC_PROTO_NFC_DEP_MASK))
		pn533_poll_add_mod(dev, PN533_POLL_MOD_106KBPS_A);

	अगर (im_protocols & NFC_PROTO_FELICA_MASK ||
	    im_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
		pn533_poll_add_mod(dev, PN533_POLL_MOD_212KBPS_FELICA);
		pn533_poll_add_mod(dev, PN533_POLL_MOD_424KBPS_FELICA);
	पूर्ण

	अगर (im_protocols & NFC_PROTO_JEWEL_MASK)
		pn533_poll_add_mod(dev, PN533_POLL_MOD_106KBPS_JEWEL);

	अगर (im_protocols & NFC_PROTO_ISO14443_B_MASK)
		pn533_poll_add_mod(dev, PN533_POLL_MOD_847KBPS_B);

	अगर (पंचांग_protocols)
		pn533_poll_add_mod(dev, PN533_LISTEN_MOD);
पूर्ण

अटल पूर्णांक pn533_start_poll_complete(काष्ठा pn533 *dev, काष्ठा sk_buff *resp)
अणु
	u8 nbtg, tg, *tgdata;
	पूर्णांक rc, tgdata_len;

	/* Toggle the DEP polling */
	अगर (dev->poll_protocols & NFC_PROTO_NFC_DEP_MASK)
		dev->poll_dep = 1;

	nbtg = resp->data[0];
	tg = resp->data[1];
	tgdata = &resp->data[2];
	tgdata_len = resp->len - 2;  /* nbtg + tg */

	अगर (nbtg) अणु
		rc = pn533_target_found(dev, tg, tgdata, tgdata_len);

		/* We must stop the poll after a valid target found */
		अगर (rc == 0)
			वापस 0;
	पूर्ण

	वापस -EAGAIN;
पूर्ण

अटल काष्ठा sk_buff *pn533_alloc_poll_tg_frame(काष्ठा pn533 *dev)
अणु
	काष्ठा sk_buff *skb;
	u8 *felica, *nfcid3;

	u8 *gbytes = dev->gb;
	माप_प्रकार gbytes_len = dev->gb_len;

	u8 felica_params[18] = अणु0x1, 0xfe, /* DEP */
				0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* अक्रमom */
				0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
				0xff, 0xffपूर्ण; /* System code */

	u8 mअगरare_params[6] = अणु0x1, 0x1, /* SENS_RES */
			       0x0, 0x0, 0x0,
			       0x40पूर्ण; /* SEL_RES क्रम DEP */

	अचिन्हित पूर्णांक skb_len = 36 + /*
				     * mode (1), mअगरare (6),
				     * felica (18), nfcid3 (10), gb_len (1)
				     */
			       gbytes_len +
			       1;  /* len Tk*/

	skb = pn533_alloc_skb(dev, skb_len);
	अगर (!skb)
		वापस शून्य;

	/* DEP support only */
	skb_put_u8(skb, PN533_INIT_TARGET_DEP);

	/* MIFARE params */
	skb_put_data(skb, mअगरare_params, 6);

	/* Felica params */
	felica = skb_put_data(skb, felica_params, 18);
	get_अक्रमom_bytes(felica + 2, 6);

	/* NFCID3 */
	nfcid3 = skb_put_zero(skb, 10);
	स_नकल(nfcid3, felica, 8);

	/* General bytes */
	skb_put_u8(skb, gbytes_len);

	skb_put_data(skb, gbytes, gbytes_len);

	/* Len Tk */
	skb_put_u8(skb, 0);

	वापस skb;
पूर्ण

अटल व्योम pn533_wq_पंचांग_mi_recv(काष्ठा work_काष्ठा *work);
अटल काष्ठा sk_buff *pn533_build_response(काष्ठा pn533 *dev);

अटल पूर्णांक pn533_पंचांग_get_data_complete(काष्ठा pn533 *dev, व्योम *arg,
				      काष्ठा sk_buff *resp)
अणु
	काष्ठा sk_buff *skb;
	u8 status, ret, mi;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (IS_ERR(resp)) अणु
		skb_queue_purge(&dev->resp_q);
		वापस PTR_ERR(resp);
	पूर्ण

	status = resp->data[0];

	ret = status & PN533_CMD_RET_MASK;
	mi = status & PN533_CMD_MI_MASK;

	skb_pull(resp, माप(status));

	अगर (ret != PN533_CMD_RET_SUCCESS) अणु
		rc = -EIO;
		जाओ error;
	पूर्ण

	skb_queue_tail(&dev->resp_q, resp);

	अगर (mi) अणु
		queue_work(dev->wq, &dev->mi_पंचांग_rx_work);
		वापस -EINPROGRESS;
	पूर्ण

	skb = pn533_build_response(dev);
	अगर (!skb) अणु
		rc = -EIO;
		जाओ error;
	पूर्ण

	वापस nfc_पंचांग_data_received(dev->nfc_dev, skb);

error:
	nfc_पंचांग_deactivated(dev->nfc_dev);
	dev->tgt_mode = 0;
	skb_queue_purge(&dev->resp_q);
	dev_kमुक्त_skb(resp);

	वापस rc;
पूर्ण

अटल व्योम pn533_wq_पंचांग_mi_recv(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pn533 *dev = container_of(work, काष्ठा pn533, mi_पंचांग_rx_work);
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	skb = pn533_alloc_skb(dev, 0);
	अगर (!skb)
		वापस;

	rc = pn533_send_cmd_direct_async(dev,
					PN533_CMD_TG_GET_DATA,
					skb,
					pn533_पंचांग_get_data_complete,
					शून्य);

	अगर (rc < 0)
		dev_kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक pn533_पंचांग_send_complete(काष्ठा pn533 *dev, व्योम *arg,
				  काष्ठा sk_buff *resp);
अटल व्योम pn533_wq_पंचांग_mi_send(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pn533 *dev = container_of(work, काष्ठा pn533, mi_पंचांग_tx_work);
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	/* Grab the first skb in the queue */
	skb = skb_dequeue(&dev->fragment_skb);
	अगर (skb == शून्य) अणु	/* No more data */
		/* Reset the queue क्रम future use */
		skb_queue_head_init(&dev->fragment_skb);
		जाओ error;
	पूर्ण

	/* last entry - हटाओ MI bit */
	अगर (skb_queue_len(&dev->fragment_skb) == 0) अणु
		rc = pn533_send_cmd_direct_async(dev, PN533_CMD_TG_SET_DATA,
					skb, pn533_पंचांग_send_complete, शून्य);
	पूर्ण अन्यथा
		rc = pn533_send_cmd_direct_async(dev,
					PN533_CMD_TG_SET_META_DATA,
					skb, pn533_पंचांग_send_complete, शून्य);

	अगर (rc == 0) /* success */
		वापस;

	dev_err(dev->dev,
		"Error %d when trying to perform set meta data_exchange", rc);

	dev_kमुक्त_skb(skb);

error:
	dev->phy_ops->send_ack(dev, GFP_KERNEL);
	queue_work(dev->wq, &dev->cmd_work);
पूर्ण

अटल व्योम pn533_wq_tg_get_data(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pn533 *dev = container_of(work, काष्ठा pn533, tg_work);
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	skb = pn533_alloc_skb(dev, 0);
	अगर (!skb)
		वापस;

	rc = pn533_send_data_async(dev, PN533_CMD_TG_GET_DATA, skb,
				   pn533_पंचांग_get_data_complete, शून्य);

	अगर (rc < 0)
		dev_kमुक्त_skb(skb);
पूर्ण

#घोषणा ATR_REQ_GB_OFFSET 17
अटल पूर्णांक pn533_init_target_complete(काष्ठा pn533 *dev, काष्ठा sk_buff *resp)
अणु
	u8 mode, *cmd, comm_mode = NFC_COMM_PASSIVE, *gb;
	माप_प्रकार gb_len;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (resp->len < ATR_REQ_GB_OFFSET + 1)
		वापस -EINVAL;

	mode = resp->data[0];
	cmd = &resp->data[1];

	dev_dbg(dev->dev, "Target mode 0x%x len %d\n",
		mode, resp->len);

	अगर ((mode & PN533_INIT_TARGET_RESP_FRAME_MASK) ==
	    PN533_INIT_TARGET_RESP_ACTIVE)
		comm_mode = NFC_COMM_ACTIVE;

	अगर ((mode & PN533_INIT_TARGET_RESP_DEP) == 0)  /* Only DEP supported */
		वापस -EOPNOTSUPP;

	gb = cmd + ATR_REQ_GB_OFFSET;
	gb_len = resp->len - (ATR_REQ_GB_OFFSET + 1);

	rc = nfc_पंचांग_activated(dev->nfc_dev, NFC_PROTO_NFC_DEP_MASK,
			      comm_mode, gb, gb_len);
	अगर (rc < 0) अणु
		nfc_err(dev->dev,
			"Error when signaling target activation\n");
		वापस rc;
	पूर्ण

	dev->tgt_mode = 1;
	queue_work(dev->wq, &dev->tg_work);

	वापस 0;
पूर्ण

अटल व्योम pn533_listen_mode_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा pn533 *dev = from_समयr(dev, t, listen_समयr);

	dev_dbg(dev->dev, "Listen mode timeout\n");

	dev->cancel_listen = 1;

	pn533_poll_next_mod(dev);

	queue_delayed_work(dev->wq, &dev->poll_work,
			   msecs_to_jअगरfies(PN533_POLL_INTERVAL));
पूर्ण

अटल पूर्णांक pn533_rf_complete(काष्ठा pn533 *dev, व्योम *arg,
			     काष्ठा sk_buff *resp)
अणु
	पूर्णांक rc = 0;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);

		nfc_err(dev->dev, "RF setting error %d\n", rc);

		वापस rc;
	पूर्ण

	queue_delayed_work(dev->wq, &dev->poll_work,
			   msecs_to_jअगरfies(PN533_POLL_INTERVAL));

	dev_kमुक्त_skb(resp);
	वापस rc;
पूर्ण

अटल व्योम pn533_wq_rf(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pn533 *dev = container_of(work, काष्ठा pn533, rf_work);
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	skb = pn533_alloc_skb(dev, 2);
	अगर (!skb)
		वापस;

	skb_put_u8(skb, PN533_CFGITEM_RF_FIELD);
	skb_put_u8(skb, PN533_CFGITEM_RF_FIELD_AUTO_RFCA);

	rc = pn533_send_cmd_async(dev, PN533_CMD_RF_CONFIGURATION, skb,
				  pn533_rf_complete, शून्य);
	अगर (rc < 0) अणु
		dev_kमुक्त_skb(skb);
		nfc_err(dev->dev, "RF setting error %d\n", rc);
	पूर्ण
पूर्ण

अटल पूर्णांक pn533_poll_dep_complete(काष्ठा pn533 *dev, व्योम *arg,
				   काष्ठा sk_buff *resp)
अणु
	काष्ठा pn533_cmd_jump_dep_response *rsp;
	काष्ठा nfc_target nfc_target;
	u8 target_gt_len;
	पूर्णांक rc;

	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	rsp = (काष्ठा pn533_cmd_jump_dep_response *)resp->data;

	rc = rsp->status & PN533_CMD_RET_MASK;
	अगर (rc != PN533_CMD_RET_SUCCESS) अणु
		/* Not target found, turn radio off */
		queue_work(dev->wq, &dev->rf_work);

		dev_kमुक्त_skb(resp);
		वापस 0;
	पूर्ण

	dev_dbg(dev->dev, "Creating new target");

	nfc_target.supported_protocols = NFC_PROTO_NFC_DEP_MASK;
	nfc_target.nfcid1_len = 10;
	स_नकल(nfc_target.nfcid1, rsp->nfcid3t, nfc_target.nfcid1_len);
	rc = nfc_tarमाला_लो_found(dev->nfc_dev, &nfc_target, 1);
	अगर (rc)
		जाओ error;

	dev->tgt_available_prots = 0;
	dev->tgt_active_prot = NFC_PROTO_NFC_DEP;

	/* ATR_RES general bytes are located at offset 17 */
	target_gt_len = resp->len - 17;
	rc = nfc_set_remote_general_bytes(dev->nfc_dev,
					  rsp->gt, target_gt_len);
	अगर (!rc) अणु
		rc = nfc_dep_link_is_up(dev->nfc_dev,
					dev->nfc_dev->tarमाला_लो[0].idx,
					0, NFC_RF_INITIATOR);

		अगर (!rc)
			pn533_poll_reset_mod_list(dev);
	पूर्ण
error:
	dev_kमुक्त_skb(resp);
	वापस rc;
पूर्ण

#घोषणा PASSIVE_DATA_LEN 5
अटल पूर्णांक pn533_poll_dep(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	काष्ठा sk_buff *skb;
	पूर्णांक rc, skb_len;
	u8 *next, nfcid3[NFC_NFCID3_MAXSIZE];
	u8 passive_data[PASSIVE_DATA_LEN] = अणु0x00, 0xff, 0xff, 0x00, 0x3पूर्ण;

	dev_dbg(dev->dev, "%s", __func__);

	अगर (!dev->gb) अणु
		dev->gb = nfc_get_local_general_bytes(nfc_dev, &dev->gb_len);

		अगर (!dev->gb || !dev->gb_len) अणु
			dev->poll_dep = 0;
			queue_work(dev->wq, &dev->rf_work);
		पूर्ण
	पूर्ण

	skb_len = 3 + dev->gb_len; /* ActPass + BR + Next */
	skb_len += PASSIVE_DATA_LEN;

	/* NFCID3 */
	skb_len += NFC_NFCID3_MAXSIZE;
	nfcid3[0] = 0x1;
	nfcid3[1] = 0xfe;
	get_अक्रमom_bytes(nfcid3 + 2, 6);

	skb = pn533_alloc_skb(dev, skb_len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, 0x01);  /* Active */
	skb_put_u8(skb, 0x02);  /* 424 kbps */

	next = skb_put(skb, 1);  /* Next */
	*next = 0;

	/* Copy passive data */
	skb_put_data(skb, passive_data, PASSIVE_DATA_LEN);
	*next |= 1;

	/* Copy NFCID3 (which is NFCID2 from SENSF_RES) */
	skb_put_data(skb, nfcid3, NFC_NFCID3_MAXSIZE);
	*next |= 2;

	skb_put_data(skb, dev->gb, dev->gb_len);
	*next |= 4; /* We have some Gi */

	rc = pn533_send_cmd_async(dev, PN533_CMD_IN_JUMP_FOR_DEP, skb,
				  pn533_poll_dep_complete, शून्य);

	अगर (rc < 0)
		dev_kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल पूर्णांक pn533_स्वतःpoll_complete(काष्ठा pn533 *dev, व्योम *arg,
			       काष्ठा sk_buff *resp)
अणु
	काष्ठा pn532_स्वतःpoll_resp *apr;
	काष्ठा nfc_target nfc_tgt;
	u8 nbtg;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);

		nfc_err(dev->dev, "%s  autopoll complete error %d\n",
			__func__, rc);

		अगर (rc == -ENOENT) अणु
			अगर (dev->poll_mod_count != 0)
				वापस rc;
			जाओ stop_poll;
		पूर्ण अन्यथा अगर (rc < 0) अणु
			nfc_err(dev->dev,
				"Error %d when running autopoll\n", rc);
			जाओ stop_poll;
		पूर्ण
	पूर्ण

	nbtg = resp->data[0];
	अगर ((nbtg > 2) || (nbtg <= 0))
		वापस -EAGAIN;

	apr = (काष्ठा pn532_स्वतःpoll_resp *)&resp->data[1];
	जबतक (nbtg--) अणु
		स_रखो(&nfc_tgt, 0, माप(काष्ठा nfc_target));
		चयन (apr->type) अणु
		हाल PN532_AUTOPOLL_TYPE_ISOA:
			dev_dbg(dev->dev, "ISOA\n");
			rc = pn533_target_found_type_a(&nfc_tgt, apr->tgdata,
						       apr->ln - 1);
			अवरोध;
		हाल PN532_AUTOPOLL_TYPE_FELICA212:
		हाल PN532_AUTOPOLL_TYPE_FELICA424:
			dev_dbg(dev->dev, "FELICA\n");
			rc = pn533_target_found_felica(&nfc_tgt, apr->tgdata,
						       apr->ln - 1);
			अवरोध;
		हाल PN532_AUTOPOLL_TYPE_JEWEL:
			dev_dbg(dev->dev, "JEWEL\n");
			rc = pn533_target_found_jewel(&nfc_tgt, apr->tgdata,
						      apr->ln - 1);
			अवरोध;
		हाल PN532_AUTOPOLL_TYPE_ISOB:
			dev_dbg(dev->dev, "ISOB\n");
			rc = pn533_target_found_type_b(&nfc_tgt, apr->tgdata,
						       apr->ln - 1);
			अवरोध;
		हाल PN532_AUTOPOLL_TYPE_MIFARE:
			dev_dbg(dev->dev, "Mifare\n");
			rc = pn533_target_found_type_a(&nfc_tgt, apr->tgdata,
						       apr->ln - 1);
			अवरोध;
		शेष:
			nfc_err(dev->dev,
				    "Unknown current poll modulation\n");
			rc = -EPROTO;
		पूर्ण

		अगर (rc)
			जाओ करोne;

		अगर (!(nfc_tgt.supported_protocols & dev->poll_protocols)) अणु
			nfc_err(dev->dev,
				    "The Tg found doesn't have the desired protocol\n");
			rc = -EAGAIN;
			जाओ करोne;
		पूर्ण

		dev->tgt_available_prots = nfc_tgt.supported_protocols;
		apr = (काष्ठा pn532_स्वतःpoll_resp *)
			(apr->tgdata + (apr->ln - 1));
	पूर्ण

	pn533_poll_reset_mod_list(dev);
	nfc_tarमाला_लो_found(dev->nfc_dev, &nfc_tgt, 1);

करोne:
	dev_kमुक्त_skb(resp);
	वापस rc;

stop_poll:
	nfc_err(dev->dev, "autopoll operation has been stopped\n");

	pn533_poll_reset_mod_list(dev);
	dev->poll_protocols = 0;
	वापस rc;
पूर्ण

अटल पूर्णांक pn533_poll_complete(काष्ठा pn533 *dev, व्योम *arg,
			       काष्ठा sk_buff *resp)
अणु
	काष्ठा pn533_poll_modulations *cur_mod;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);

		nfc_err(dev->dev, "%s  Poll complete error %d\n",
			__func__, rc);

		अगर (rc == -ENOENT) अणु
			अगर (dev->poll_mod_count != 0)
				वापस rc;
			जाओ stop_poll;
		पूर्ण अन्यथा अगर (rc < 0) अणु
			nfc_err(dev->dev,
				"Error %d when running poll\n", rc);
			जाओ stop_poll;
		पूर्ण
	पूर्ण

	cur_mod = dev->poll_mod_active[dev->poll_mod_curr];

	अगर (cur_mod->len == 0) अणु /* Target mode */
		del_समयr(&dev->listen_समयr);
		rc = pn533_init_target_complete(dev, resp);
		जाओ करोne;
	पूर्ण

	/* Initiator mode */
	rc = pn533_start_poll_complete(dev, resp);
	अगर (!rc)
		जाओ करोne;

	अगर (!dev->poll_mod_count) अणु
		dev_dbg(dev->dev, "Polling has been stopped\n");
		जाओ करोne;
	पूर्ण

	pn533_poll_next_mod(dev);
	/* Not target found, turn radio off */
	queue_work(dev->wq, &dev->rf_work);

करोne:
	dev_kमुक्त_skb(resp);
	वापस rc;

stop_poll:
	nfc_err(dev->dev, "Polling operation has been stopped\n");

	pn533_poll_reset_mod_list(dev);
	dev->poll_protocols = 0;
	वापस rc;
पूर्ण

अटल काष्ठा sk_buff *pn533_alloc_poll_in_frame(काष्ठा pn533 *dev,
					काष्ठा pn533_poll_modulations *mod)
अणु
	काष्ठा sk_buff *skb;

	skb = pn533_alloc_skb(dev, mod->len);
	अगर (!skb)
		वापस शून्य;

	skb_put_data(skb, &mod->data, mod->len);

	वापस skb;
पूर्ण

अटल पूर्णांक pn533_send_poll_frame(काष्ठा pn533 *dev)
अणु
	काष्ठा pn533_poll_modulations *mod;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;
	u8 cmd_code;

	mod = dev->poll_mod_active[dev->poll_mod_curr];

	dev_dbg(dev->dev, "%s mod len %d\n",
		__func__, mod->len);

	अगर ((dev->poll_protocols & NFC_PROTO_NFC_DEP_MASK) && dev->poll_dep)  अणु
		dev->poll_dep = 0;
		वापस pn533_poll_dep(dev->nfc_dev);
	पूर्ण

	अगर (mod->len == 0) अणु  /* Listen mode */
		cmd_code = PN533_CMD_TG_INIT_AS_TARGET;
		skb = pn533_alloc_poll_tg_frame(dev);
	पूर्ण अन्यथा अणु  /* Polling mode */
		cmd_code =  PN533_CMD_IN_LIST_PASSIVE_TARGET;
		skb = pn533_alloc_poll_in_frame(dev, mod);
	पूर्ण

	अगर (!skb) अणु
		nfc_err(dev->dev, "Failed to allocate skb\n");
		वापस -ENOMEM;
	पूर्ण

	rc = pn533_send_cmd_async(dev, cmd_code, skb, pn533_poll_complete,
				  शून्य);
	अगर (rc < 0) अणु
		dev_kमुक्त_skb(skb);
		nfc_err(dev->dev, "Polling loop error %d\n", rc);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम pn533_wq_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pn533 *dev = container_of(work, काष्ठा pn533, poll_work.work);
	काष्ठा pn533_poll_modulations *cur_mod;
	पूर्णांक rc;

	cur_mod = dev->poll_mod_active[dev->poll_mod_curr];

	dev_dbg(dev->dev,
		"%s cancel_listen %d modulation len %d\n",
		__func__, dev->cancel_listen, cur_mod->len);

	अगर (dev->cancel_listen == 1) अणु
		dev->cancel_listen = 0;
		dev->phy_ops->पात_cmd(dev, GFP_ATOMIC);
	पूर्ण

	rc = pn533_send_poll_frame(dev);
	अगर (rc)
		वापस;

	अगर (cur_mod->len == 0 && dev->poll_mod_count > 1)
		mod_समयr(&dev->listen_समयr, jअगरfies + PN533_LISTEN_TIME * HZ);
पूर्ण

अटल पूर्णांक pn533_start_poll(काष्ठा nfc_dev *nfc_dev,
			    u32 im_protocols, u32 पंचांग_protocols)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	काष्ठा pn533_poll_modulations *cur_mod;
	काष्ठा sk_buff *skb;
	u8 अक्रम_mod;
	पूर्णांक rc;

	dev_dbg(dev->dev,
		"%s: im protocols 0x%x tm protocols 0x%x\n",
		__func__, im_protocols, पंचांग_protocols);

	अगर (dev->tgt_active_prot) अणु
		nfc_err(dev->dev,
			"Cannot poll with a target already activated\n");
		वापस -EBUSY;
	पूर्ण

	अगर (dev->tgt_mode) अणु
		nfc_err(dev->dev,
			"Cannot poll while already being activated\n");
		वापस -EBUSY;
	पूर्ण

	अगर (पंचांग_protocols) अणु
		dev->gb = nfc_get_local_general_bytes(nfc_dev, &dev->gb_len);
		अगर (dev->gb == शून्य)
			पंचांग_protocols = 0;
	पूर्ण

	dev->poll_protocols = im_protocols;
	dev->listen_protocols = पंचांग_protocols;
	अगर (dev->device_type == PN533_DEVICE_PN532_AUTOPOLL) अणु
		skb = pn533_alloc_skb(dev, 4 + 6);
		अगर (!skb)
			वापस -ENOMEM;

		*((u8 *)skb_put(skb, माप(u8))) =
			PN532_AUTOPOLL_POLLNR_INFINITE;
		*((u8 *)skb_put(skb, माप(u8))) = PN532_AUTOPOLL_PERIOD;

		अगर ((im_protocols & NFC_PROTO_MIFARE_MASK) &&
				(im_protocols & NFC_PROTO_ISO14443_MASK) &&
				(im_protocols & NFC_PROTO_NFC_DEP_MASK))
			*((u8 *)skb_put(skb, माप(u8))) =
				PN532_AUTOPOLL_TYPE_GENERIC_106;
		अन्यथा अणु
			अगर (im_protocols & NFC_PROTO_MIFARE_MASK)
				*((u8 *)skb_put(skb, माप(u8))) =
					PN532_AUTOPOLL_TYPE_MIFARE;

			अगर (im_protocols & NFC_PROTO_ISO14443_MASK)
				*((u8 *)skb_put(skb, माप(u8))) =
					PN532_AUTOPOLL_TYPE_ISOA;

			अगर (im_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
				*((u8 *)skb_put(skb, माप(u8))) =
					PN532_AUTOPOLL_TYPE_DEP_PASSIVE_106;
				*((u8 *)skb_put(skb, माप(u8))) =
					PN532_AUTOPOLL_TYPE_DEP_PASSIVE_212;
				*((u8 *)skb_put(skb, माप(u8))) =
					PN532_AUTOPOLL_TYPE_DEP_PASSIVE_424;
			पूर्ण
		पूर्ण

		अगर (im_protocols & NFC_PROTO_FELICA_MASK ||
				im_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
			*((u8 *)skb_put(skb, माप(u8))) =
				PN532_AUTOPOLL_TYPE_FELICA212;
			*((u8 *)skb_put(skb, माप(u8))) =
				PN532_AUTOPOLL_TYPE_FELICA424;
		पूर्ण

		अगर (im_protocols & NFC_PROTO_JEWEL_MASK)
			*((u8 *)skb_put(skb, माप(u8))) =
				PN532_AUTOPOLL_TYPE_JEWEL;

		अगर (im_protocols & NFC_PROTO_ISO14443_B_MASK)
			*((u8 *)skb_put(skb, माप(u8))) =
				PN532_AUTOPOLL_TYPE_ISOB;

		अगर (पंचांग_protocols)
			*((u8 *)skb_put(skb, माप(u8))) =
				PN532_AUTOPOLL_TYPE_DEP_ACTIVE_106;

		rc = pn533_send_cmd_async(dev, PN533_CMD_IN_AUTOPOLL, skb,
				pn533_स्वतःpoll_complete, शून्य);

		अगर (rc < 0)
			dev_kमुक्त_skb(skb);
		अन्यथा
			dev->poll_mod_count++;

		वापस rc;
	पूर्ण

	pn533_poll_create_mod_list(dev, im_protocols, पंचांग_protocols);

	/* Do not always start polling from the same modulation */
	get_अक्रमom_bytes(&अक्रम_mod, माप(अक्रम_mod));
	अक्रम_mod %= dev->poll_mod_count;
	dev->poll_mod_curr = अक्रम_mod;

	cur_mod = dev->poll_mod_active[dev->poll_mod_curr];

	rc = pn533_send_poll_frame(dev);

	/* Start listen समयr */
	अगर (!rc && cur_mod->len == 0 && dev->poll_mod_count > 1)
		mod_समयr(&dev->listen_समयr, jअगरfies + PN533_LISTEN_TIME * HZ);

	वापस rc;
पूर्ण

अटल व्योम pn533_stop_poll(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);

	del_समयr(&dev->listen_समयr);

	अगर (!dev->poll_mod_count) अणु
		dev_dbg(dev->dev,
			"Polling operation was not running\n");
		वापस;
	पूर्ण

	dev->phy_ops->पात_cmd(dev, GFP_KERNEL);
	flush_delayed_work(&dev->poll_work);
	pn533_poll_reset_mod_list(dev);
पूर्ण

अटल पूर्णांक pn533_activate_target_nfcdep(काष्ठा pn533 *dev)
अणु
	काष्ठा pn533_cmd_activate_response *rsp;
	u16 gt_len;
	पूर्णांक rc;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;

	dev_dbg(dev->dev, "%s\n", __func__);

	skb = pn533_alloc_skb(dev, माप(u8) * 2); /*TG + Next*/
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, 1); /* TG */
	skb_put_u8(skb, 0); /* Next */

	resp = pn533_send_cmd_sync(dev, PN533_CMD_IN_ATR, skb);
	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	rsp = (काष्ठा pn533_cmd_activate_response *)resp->data;
	rc = rsp->status & PN533_CMD_RET_MASK;
	अगर (rc != PN533_CMD_RET_SUCCESS) अणु
		nfc_err(dev->dev,
			"Target activation failed (error 0x%x)\n", rc);
		dev_kमुक्त_skb(resp);
		वापस -EIO;
	पूर्ण

	/* ATR_RES general bytes are located at offset 16 */
	gt_len = resp->len - 16;
	rc = nfc_set_remote_general_bytes(dev->nfc_dev, rsp->gt, gt_len);

	dev_kमुक्त_skb(resp);
	वापस rc;
पूर्ण

अटल पूर्णांक pn533_activate_target(काष्ठा nfc_dev *nfc_dev,
				 काष्ठा nfc_target *target, u32 protocol)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s: protocol=%u\n", __func__, protocol);

	अगर (dev->poll_mod_count) अणु
		nfc_err(dev->dev,
			"Cannot activate while polling\n");
		वापस -EBUSY;
	पूर्ण

	अगर (dev->tgt_active_prot) अणु
		nfc_err(dev->dev,
			"There is already an active target\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!dev->tgt_available_prots) अणु
		nfc_err(dev->dev,
			"There is no available target to activate\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(dev->tgt_available_prots & (1 << protocol))) अणु
		nfc_err(dev->dev,
			"Target doesn't support requested proto %u\n",
			protocol);
		वापस -EINVAL;
	पूर्ण

	अगर (protocol == NFC_PROTO_NFC_DEP) अणु
		rc = pn533_activate_target_nfcdep(dev);
		अगर (rc) अणु
			nfc_err(dev->dev,
				"Activating target with DEP failed %d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	dev->tgt_active_prot = protocol;
	dev->tgt_available_prots = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक pn533_deactivate_target_complete(काष्ठा pn533 *dev, व्योम *arg,
			     काष्ठा sk_buff *resp)
अणु
	पूर्णांक rc = 0;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);

		nfc_err(dev->dev, "Target release error %d\n", rc);

		वापस rc;
	पूर्ण

	rc = resp->data[0] & PN533_CMD_RET_MASK;
	अगर (rc != PN533_CMD_RET_SUCCESS)
		nfc_err(dev->dev,
			"Error 0x%x when releasing the target\n", rc);

	dev_kमुक्त_skb(resp);
	वापस rc;
पूर्ण

अटल व्योम pn533_deactivate_target(काष्ठा nfc_dev *nfc_dev,
				    काष्ठा nfc_target *target, u8 mode)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (!dev->tgt_active_prot) अणु
		nfc_err(dev->dev, "There is no active target\n");
		वापस;
	पूर्ण

	dev->tgt_active_prot = 0;
	skb_queue_purge(&dev->resp_q);

	skb = pn533_alloc_skb(dev, माप(u8));
	अगर (!skb)
		वापस;

	skb_put_u8(skb, 1); /* TG*/

	rc = pn533_send_cmd_async(dev, PN533_CMD_IN_RELEASE, skb,
				  pn533_deactivate_target_complete, शून्य);
	अगर (rc < 0) अणु
		dev_kमुक्त_skb(skb);
		nfc_err(dev->dev, "Target release error %d\n", rc);
	पूर्ण
पूर्ण


अटल पूर्णांक pn533_in_dep_link_up_complete(काष्ठा pn533 *dev, व्योम *arg,
					 काष्ठा sk_buff *resp)
अणु
	काष्ठा pn533_cmd_jump_dep_response *rsp;
	u8 target_gt_len;
	पूर्णांक rc;
	u8 active = *(u8 *)arg;

	kमुक्त(arg);

	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	अगर (dev->tgt_available_prots &&
	    !(dev->tgt_available_prots & (1 << NFC_PROTO_NFC_DEP))) अणु
		nfc_err(dev->dev,
			"The target does not support DEP\n");
		rc =  -EINVAL;
		जाओ error;
	पूर्ण

	rsp = (काष्ठा pn533_cmd_jump_dep_response *)resp->data;

	rc = rsp->status & PN533_CMD_RET_MASK;
	अगर (rc != PN533_CMD_RET_SUCCESS) अणु
		nfc_err(dev->dev,
			"Bringing DEP link up failed (error 0x%x)\n", rc);
		जाओ error;
	पूर्ण

	अगर (!dev->tgt_available_prots) अणु
		काष्ठा nfc_target nfc_target;

		dev_dbg(dev->dev, "Creating new target\n");

		nfc_target.supported_protocols = NFC_PROTO_NFC_DEP_MASK;
		nfc_target.nfcid1_len = 10;
		स_नकल(nfc_target.nfcid1, rsp->nfcid3t, nfc_target.nfcid1_len);
		rc = nfc_tarमाला_लो_found(dev->nfc_dev, &nfc_target, 1);
		अगर (rc)
			जाओ error;

		dev->tgt_available_prots = 0;
	पूर्ण

	dev->tgt_active_prot = NFC_PROTO_NFC_DEP;

	/* ATR_RES general bytes are located at offset 17 */
	target_gt_len = resp->len - 17;
	rc = nfc_set_remote_general_bytes(dev->nfc_dev,
					  rsp->gt, target_gt_len);
	अगर (rc == 0)
		rc = nfc_dep_link_is_up(dev->nfc_dev,
					dev->nfc_dev->tarमाला_लो[0].idx,
					!active, NFC_RF_INITIATOR);

error:
	dev_kमुक्त_skb(resp);
	वापस rc;
पूर्ण

अटल पूर्णांक pn533_rf_field(काष्ठा nfc_dev *nfc_dev, u8 rf);
अटल पूर्णांक pn533_dep_link_up(काष्ठा nfc_dev *nfc_dev, काष्ठा nfc_target *target,
			     u8 comm_mode, u8 *gb, माप_प्रकार gb_len)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	काष्ठा sk_buff *skb;
	पूर्णांक rc, skb_len;
	u8 *next, *arg, nfcid3[NFC_NFCID3_MAXSIZE];
	u8 passive_data[PASSIVE_DATA_LEN] = अणु0x00, 0xff, 0xff, 0x00, 0x3पूर्ण;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (dev->poll_mod_count) अणु
		nfc_err(dev->dev,
			"Cannot bring the DEP link up while polling\n");
		वापस -EBUSY;
	पूर्ण

	अगर (dev->tgt_active_prot) अणु
		nfc_err(dev->dev,
			"There is already an active target\n");
		वापस -EBUSY;
	पूर्ण

	skb_len = 3 + gb_len; /* ActPass + BR + Next */
	skb_len += PASSIVE_DATA_LEN;

	/* NFCID3 */
	skb_len += NFC_NFCID3_MAXSIZE;
	अगर (target && !target->nfcid2_len) अणु
		nfcid3[0] = 0x1;
		nfcid3[1] = 0xfe;
		get_अक्रमom_bytes(nfcid3 + 2, 6);
	पूर्ण

	skb = pn533_alloc_skb(dev, skb_len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, !comm_mode);  /* ActPass */
	skb_put_u8(skb, 0x02);  /* 424 kbps */

	next = skb_put(skb, 1);  /* Next */
	*next = 0;

	/* Copy passive data */
	skb_put_data(skb, passive_data, PASSIVE_DATA_LEN);
	*next |= 1;

	/* Copy NFCID3 (which is NFCID2 from SENSF_RES) */
	अगर (target && target->nfcid2_len)
		स_नकल(skb_put(skb, NFC_NFCID3_MAXSIZE), target->nfcid2,
		       target->nfcid2_len);
	अन्यथा
		skb_put_data(skb, nfcid3, NFC_NFCID3_MAXSIZE);
	*next |= 2;

	अगर (gb != शून्य && gb_len > 0) अणु
		skb_put_data(skb, gb, gb_len);
		*next |= 4; /* We have some Gi */
	पूर्ण अन्यथा अणु
		*next = 0;
	पूर्ण

	arg = kदो_स्मृति(माप(*arg), GFP_KERNEL);
	अगर (!arg) अणु
		dev_kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	*arg = !comm_mode;

	pn533_rf_field(dev->nfc_dev, 0);

	rc = pn533_send_cmd_async(dev, PN533_CMD_IN_JUMP_FOR_DEP, skb,
				  pn533_in_dep_link_up_complete, arg);

	अगर (rc < 0) अणु
		dev_kमुक्त_skb(skb);
		kमुक्त(arg);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक pn533_dep_link_करोwn(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);

	dev_dbg(dev->dev, "%s\n", __func__);

	pn533_poll_reset_mod_list(dev);

	अगर (dev->tgt_mode || dev->tgt_active_prot)
		dev->phy_ops->पात_cmd(dev, GFP_KERNEL);

	dev->tgt_active_prot = 0;
	dev->tgt_mode = 0;

	skb_queue_purge(&dev->resp_q);

	वापस 0;
पूर्ण

काष्ठा pn533_data_exchange_arg अणु
	data_exchange_cb_t cb;
	व्योम *cb_context;
पूर्ण;

अटल काष्ठा sk_buff *pn533_build_response(काष्ठा pn533 *dev)
अणु
	काष्ठा sk_buff *skb, *पंचांगp, *t;
	अचिन्हित पूर्णांक skb_len = 0, पंचांगp_len = 0;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (skb_queue_empty(&dev->resp_q))
		वापस शून्य;

	अगर (skb_queue_len(&dev->resp_q) == 1) अणु
		skb = skb_dequeue(&dev->resp_q);
		जाओ out;
	पूर्ण

	skb_queue_walk_safe(&dev->resp_q, पंचांगp, t)
		skb_len += पंचांगp->len;

	dev_dbg(dev->dev, "%s total length %d\n",
		__func__, skb_len);

	skb = alloc_skb(skb_len, GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ out;

	skb_put(skb, skb_len);

	skb_queue_walk_safe(&dev->resp_q, पंचांगp, t) अणु
		स_नकल(skb->data + पंचांगp_len, पंचांगp->data, पंचांगp->len);
		पंचांगp_len += पंचांगp->len;
	पूर्ण

out:
	skb_queue_purge(&dev->resp_q);

	वापस skb;
पूर्ण

अटल पूर्णांक pn533_data_exchange_complete(काष्ठा pn533 *dev, व्योम *_arg,
					काष्ठा sk_buff *resp)
अणु
	काष्ठा pn533_data_exchange_arg *arg = _arg;
	काष्ठा sk_buff *skb;
	पूर्णांक rc = 0;
	u8 status, ret, mi;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		जाओ _error;
	पूर्ण

	status = resp->data[0];
	ret = status & PN533_CMD_RET_MASK;
	mi = status & PN533_CMD_MI_MASK;

	skb_pull(resp, माप(status));

	अगर (ret != PN533_CMD_RET_SUCCESS) अणु
		nfc_err(dev->dev,
			"Exchanging data failed (error 0x%x)\n", ret);
		rc = -EIO;
		जाओ error;
	पूर्ण

	skb_queue_tail(&dev->resp_q, resp);

	अगर (mi) अणु
		dev->cmd_complete_mi_arg = arg;
		queue_work(dev->wq, &dev->mi_rx_work);
		वापस -EINPROGRESS;
	पूर्ण

	/* Prepare क्रम the next round */
	अगर (skb_queue_len(&dev->fragment_skb) > 0) अणु
		dev->cmd_complete_dep_arg = arg;
		queue_work(dev->wq, &dev->mi_tx_work);

		वापस -EINPROGRESS;
	पूर्ण

	skb = pn533_build_response(dev);
	अगर (!skb) अणु
		rc = -ENOMEM;
		जाओ error;
	पूर्ण

	arg->cb(arg->cb_context, skb, 0);
	kमुक्त(arg);
	वापस 0;

error:
	dev_kमुक्त_skb(resp);
_error:
	skb_queue_purge(&dev->resp_q);
	arg->cb(arg->cb_context, शून्य, rc);
	kमुक्त(arg);
	वापस rc;
पूर्ण

/*
 * Receive an incoming pn533 frame. skb contains only header and payload.
 * If skb == शून्य, it is a notअगरication that the link below is dead.
 */
व्योम pn533_recv_frame(काष्ठा pn533 *dev, काष्ठा sk_buff *skb, पूर्णांक status)
अणु
	अगर (!dev->cmd)
		जाओ sched_wq;

	dev->cmd->status = status;

	अगर (status != 0) अणु
		dev_dbg(dev->dev, "%s: Error received: %d\n", __func__, status);
		जाओ sched_wq;
	पूर्ण

	अगर (skb == शून्य) अणु
		pr_err("NULL Frame -> link is dead\n");
		जाओ sched_wq;
	पूर्ण

	अगर (pn533_rx_frame_is_ack(skb->data)) अणु
		dev_dbg(dev->dev, "%s: Received ACK frame\n", __func__);
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	prपूर्णांक_hex_dump_debug("PN533 RX: ", DUMP_PREFIX_NONE, 16, 1, skb->data,
			     dev->ops->rx_frame_size(skb->data), false);

	अगर (!dev->ops->rx_is_frame_valid(skb->data, dev)) अणु
		nfc_err(dev->dev, "Received an invalid frame\n");
		dev->cmd->status = -EIO;
	पूर्ण अन्यथा अगर (!pn533_rx_frame_is_cmd_response(dev, skb->data)) अणु
		nfc_err(dev->dev, "It it not the response to the last command\n");
		dev->cmd->status = -EIO;
	पूर्ण

	dev->cmd->resp = skb;

sched_wq:
	queue_work(dev->wq, &dev->cmd_complete_work);
पूर्ण
EXPORT_SYMBOL(pn533_recv_frame);

/* Split the Tx skb पूर्णांकo small chunks */
अटल पूर्णांक pn533_fill_fragment_skbs(काष्ठा pn533 *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *frag;
	पूर्णांक  frag_size;

	करो अणु
		/* Reमुख्यing size */
		अगर (skb->len > PN533_CMD_DATAFRAME_MAXLEN)
			frag_size = PN533_CMD_DATAFRAME_MAXLEN;
		अन्यथा
			frag_size = skb->len;

		/* Allocate and reserve */
		frag = pn533_alloc_skb(dev, frag_size);
		अगर (!frag) अणु
			skb_queue_purge(&dev->fragment_skb);
			अवरोध;
		पूर्ण

		अगर (!dev->tgt_mode) अणु
			/* Reserve the TG/MI byte */
			skb_reserve(frag, 1);

			/* MI + TG */
			अगर (frag_size  == PN533_CMD_DATAFRAME_MAXLEN)
				*(u8 *)skb_push(frag, माप(u8)) =
						(PN533_CMD_MI_MASK | 1);
			अन्यथा
				*(u8 *)skb_push(frag, माप(u8)) =  1; /* TG */
		पूर्ण

		skb_put_data(frag, skb->data, frag_size);

		/* Reduce the size of incoming buffer */
		skb_pull(skb, frag_size);

		/* Add this to skb_queue */
		skb_queue_tail(&dev->fragment_skb, frag);

	पूर्ण जबतक (skb->len > 0);

	dev_kमुक्त_skb(skb);

	वापस skb_queue_len(&dev->fragment_skb);
पूर्ण

अटल पूर्णांक pn533_transceive(काष्ठा nfc_dev *nfc_dev,
			    काष्ठा nfc_target *target, काष्ठा sk_buff *skb,
			    data_exchange_cb_t cb, व्योम *cb_context)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	काष्ठा pn533_data_exchange_arg *arg = शून्य;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (!dev->tgt_active_prot) अणु
		nfc_err(dev->dev,
			"Can't exchange data if there is no active target\n");
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	arg = kदो_स्मृति(माप(*arg), GFP_KERNEL);
	अगर (!arg) अणु
		rc = -ENOMEM;
		जाओ error;
	पूर्ण

	arg->cb = cb;
	arg->cb_context = cb_context;

	चयन (dev->device_type) अणु
	हाल PN533_DEVICE_PASORI:
		अगर (dev->tgt_active_prot == NFC_PROTO_FELICA) अणु
			rc = pn533_send_data_async(dev, PN533_CMD_IN_COMM_THRU,
						   skb,
						   pn533_data_exchange_complete,
						   arg);

			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		/* jumbo frame ? */
		अगर (skb->len > PN533_CMD_DATAEXCH_DATA_MAXLEN) अणु
			rc = pn533_fill_fragment_skbs(dev, skb);
			अगर (rc <= 0)
				जाओ error;

			skb = skb_dequeue(&dev->fragment_skb);
			अगर (!skb) अणु
				rc = -EIO;
				जाओ error;
			पूर्ण
		पूर्ण अन्यथा अणु
			*(u8 *)skb_push(skb, माप(u8)) =  1; /* TG */
		पूर्ण

		rc = pn533_send_data_async(dev, PN533_CMD_IN_DATA_EXCHANGE,
					   skb, pn533_data_exchange_complete,
					   arg);

		अवरोध;
	पूर्ण

	अगर (rc < 0) /* rc from send_async */
		जाओ error;

	वापस 0;

error:
	kमुक्त(arg);
	dev_kमुक्त_skb(skb);
	वापस rc;
पूर्ण

अटल पूर्णांक pn533_पंचांग_send_complete(काष्ठा pn533 *dev, व्योम *arg,
				  काष्ठा sk_buff *resp)
अणु
	u8 status;

	dev_dbg(dev->dev, "%s\n", __func__);

	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	status = resp->data[0];

	/* Prepare क्रम the next round */
	अगर (skb_queue_len(&dev->fragment_skb) > 0) अणु
		queue_work(dev->wq, &dev->mi_पंचांग_tx_work);
		वापस -EINPROGRESS;
	पूर्ण
	dev_kमुक्त_skb(resp);

	अगर (status != 0) अणु
		nfc_पंचांग_deactivated(dev->nfc_dev);

		dev->tgt_mode = 0;

		वापस 0;
	पूर्ण

	queue_work(dev->wq, &dev->tg_work);

	वापस 0;
पूर्ण

अटल पूर्णांक pn533_पंचांग_send(काष्ठा nfc_dev *nfc_dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	/* let's split in multiple chunks if size's too big */
	अगर (skb->len > PN533_CMD_DATAEXCH_DATA_MAXLEN) अणु
		rc = pn533_fill_fragment_skbs(dev, skb);
		अगर (rc <= 0)
			जाओ error;

		/* get the first skb */
		skb = skb_dequeue(&dev->fragment_skb);
		अगर (!skb) अणु
			rc = -EIO;
			जाओ error;
		पूर्ण

		rc = pn533_send_data_async(dev, PN533_CMD_TG_SET_META_DATA, skb,
						pn533_पंचांग_send_complete, शून्य);
	पूर्ण अन्यथा अणु
		/* Send th skb */
		rc = pn533_send_data_async(dev, PN533_CMD_TG_SET_DATA, skb,
						pn533_पंचांग_send_complete, शून्य);
	पूर्ण

error:
	अगर (rc < 0) अणु
		dev_kमुक्त_skb(skb);
		skb_queue_purge(&dev->fragment_skb);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम pn533_wq_mi_recv(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pn533 *dev = container_of(work, काष्ठा pn533, mi_rx_work);
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	skb = pn533_alloc_skb(dev, PN533_CMD_DATAEXCH_HEAD_LEN);
	अगर (!skb)
		जाओ error;

	चयन (dev->device_type) अणु
	हाल PN533_DEVICE_PASORI:
		अगर (dev->tgt_active_prot == NFC_PROTO_FELICA) अणु
			rc = pn533_send_cmd_direct_async(dev,
						PN533_CMD_IN_COMM_THRU,
						skb,
						pn533_data_exchange_complete,
						 dev->cmd_complete_mi_arg);

			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		skb_put_u8(skb, 1); /*TG*/

		rc = pn533_send_cmd_direct_async(dev,
						 PN533_CMD_IN_DATA_EXCHANGE,
						 skb,
						 pn533_data_exchange_complete,
						 dev->cmd_complete_mi_arg);

		अवरोध;
	पूर्ण

	अगर (rc == 0) /* success */
		वापस;

	nfc_err(dev->dev,
		"Error %d when trying to perform data_exchange\n", rc);

	dev_kमुक्त_skb(skb);
	kमुक्त(dev->cmd_complete_mi_arg);

error:
	dev->phy_ops->send_ack(dev, GFP_KERNEL);
	queue_work(dev->wq, &dev->cmd_work);
पूर्ण

अटल व्योम pn533_wq_mi_send(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pn533 *dev = container_of(work, काष्ठा pn533, mi_tx_work);
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	dev_dbg(dev->dev, "%s\n", __func__);

	/* Grab the first skb in the queue */
	skb = skb_dequeue(&dev->fragment_skb);

	अगर (skb == शून्य) अणु	/* No more data */
		/* Reset the queue क्रम future use */
		skb_queue_head_init(&dev->fragment_skb);
		जाओ error;
	पूर्ण

	चयन (dev->device_type) अणु
	हाल PN533_DEVICE_PASORI:
		अगर (dev->tgt_active_prot != NFC_PROTO_FELICA) अणु
			rc = -EIO;
			अवरोध;
		पूर्ण

		rc = pn533_send_cmd_direct_async(dev, PN533_CMD_IN_COMM_THRU,
						 skb,
						 pn533_data_exchange_complete,
						 dev->cmd_complete_dep_arg);

		अवरोध;

	शेष:
		/* Still some fragments? */
		rc = pn533_send_cmd_direct_async(dev,
						 PN533_CMD_IN_DATA_EXCHANGE,
						 skb,
						 pn533_data_exchange_complete,
						 dev->cmd_complete_dep_arg);

		अवरोध;
	पूर्ण

	अगर (rc == 0) /* success */
		वापस;

	nfc_err(dev->dev,
		"Error %d when trying to perform data_exchange\n", rc);

	dev_kमुक्त_skb(skb);
	kमुक्त(dev->cmd_complete_dep_arg);

error:
	dev->phy_ops->send_ack(dev, GFP_KERNEL);
	queue_work(dev->wq, &dev->cmd_work);
पूर्ण

अटल पूर्णांक pn533_set_configuration(काष्ठा pn533 *dev, u8 cfgitem, u8 *cfgdata,
								u8 cfgdata_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;
	पूर्णांक skb_len;

	dev_dbg(dev->dev, "%s\n", __func__);

	skb_len = माप(cfgitem) + cfgdata_len; /* cfgitem + cfgdata */

	skb = pn533_alloc_skb(dev, skb_len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, cfgitem);
	skb_put_data(skb, cfgdata, cfgdata_len);

	resp = pn533_send_cmd_sync(dev, PN533_CMD_RF_CONFIGURATION, skb);
	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	dev_kमुक्त_skb(resp);
	वापस 0;
पूर्ण

अटल पूर्णांक pn533_get_firmware_version(काष्ठा pn533 *dev,
				      काष्ठा pn533_fw_version *fv)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;

	skb = pn533_alloc_skb(dev, 0);
	अगर (!skb)
		वापस -ENOMEM;

	resp = pn533_send_cmd_sync(dev, PN533_CMD_GET_FIRMWARE_VERSION, skb);
	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	fv->ic = resp->data[0];
	fv->ver = resp->data[1];
	fv->rev = resp->data[2];
	fv->support = resp->data[3];

	dev_kमुक्त_skb(resp);
	वापस 0;
पूर्ण

अटल पूर्णांक pn533_pasori_fw_reset(काष्ठा pn533 *dev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;

	dev_dbg(dev->dev, "%s\n", __func__);

	skb = pn533_alloc_skb(dev, माप(u8));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, 0x1);

	resp = pn533_send_cmd_sync(dev, 0x18, skb);
	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	dev_kमुक्त_skb(resp);

	वापस 0;
पूर्ण

अटल पूर्णांक pn533_rf_field(काष्ठा nfc_dev *nfc_dev, u8 rf)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	u8 rf_field = !!rf;
	पूर्णांक rc;

	rf_field |= PN533_CFGITEM_RF_FIELD_AUTO_RFCA;

	rc = pn533_set_configuration(dev, PN533_CFGITEM_RF_FIELD,
				     (u8 *)&rf_field, 1);
	अगर (rc) अणु
		nfc_err(dev->dev, "Error on setting RF field\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pn532_sam_configuration(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;

	skb = pn533_alloc_skb(dev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, 0x01);

	resp = pn533_send_cmd_sync(dev, PN533_CMD_SAM_CONFIGURATION, skb);
	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	dev_kमुक्त_skb(resp);
	वापस 0;
पूर्ण

अटल पूर्णांक pn533_dev_up(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	पूर्णांक rc;

	अगर (dev->phy_ops->dev_up) अणु
		rc = dev->phy_ops->dev_up(dev);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर ((dev->device_type == PN533_DEVICE_PN532) ||
		(dev->device_type == PN533_DEVICE_PN532_AUTOPOLL)) अणु
		rc = pn532_sam_configuration(nfc_dev);

		अगर (rc)
			वापस rc;
	पूर्ण

	वापस pn533_rf_field(nfc_dev, 1);
पूर्ण

अटल पूर्णांक pn533_dev_करोwn(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा pn533 *dev = nfc_get_drvdata(nfc_dev);
	पूर्णांक ret;

	ret = pn533_rf_field(nfc_dev, 0);
	अगर (dev->phy_ops->dev_करोwn && !ret)
		ret = dev->phy_ops->dev_करोwn(dev);

	वापस ret;
पूर्ण

अटल काष्ठा nfc_ops pn533_nfc_ops = अणु
	.dev_up = pn533_dev_up,
	.dev_करोwn = pn533_dev_करोwn,
	.dep_link_up = pn533_dep_link_up,
	.dep_link_करोwn = pn533_dep_link_करोwn,
	.start_poll = pn533_start_poll,
	.stop_poll = pn533_stop_poll,
	.activate_target = pn533_activate_target,
	.deactivate_target = pn533_deactivate_target,
	.im_transceive = pn533_transceive,
	.पंचांग_send = pn533_पंचांग_send,
पूर्ण;

अटल पूर्णांक pn533_setup(काष्ठा pn533 *dev)
अणु
	काष्ठा pn533_config_max_retries max_retries;
	काष्ठा pn533_config_timing timing;
	u8 pasori_cfg[3] = अणु0x08, 0x01, 0x08पूर्ण;
	पूर्णांक rc;

	चयन (dev->device_type) अणु
	हाल PN533_DEVICE_STD:
	हाल PN533_DEVICE_PASORI:
	हाल PN533_DEVICE_ACR122U:
	हाल PN533_DEVICE_PN532:
	हाल PN533_DEVICE_PN532_AUTOPOLL:
		max_retries.mx_rty_atr = 0x2;
		max_retries.mx_rty_psl = 0x1;
		max_retries.mx_rty_passive_act =
			PN533_CONFIG_MAX_RETRIES_NO_RETRY;

		timing.rfu = PN533_CONFIG_TIMING_102;
		timing.atr_res_समयout = PN533_CONFIG_TIMING_102;
		timing.dep_समयout = PN533_CONFIG_TIMING_204;

		अवरोध;

	शेष:
		nfc_err(dev->dev, "Unknown device type %d\n",
			dev->device_type);
		वापस -EINVAL;
	पूर्ण

	rc = pn533_set_configuration(dev, PN533_CFGITEM_MAX_RETRIES,
				     (u8 *)&max_retries, माप(max_retries));
	अगर (rc) अणु
		nfc_err(dev->dev,
			"Error on setting MAX_RETRIES config\n");
		वापस rc;
	पूर्ण


	rc = pn533_set_configuration(dev, PN533_CFGITEM_TIMING,
				     (u8 *)&timing, माप(timing));
	अगर (rc) अणु
		nfc_err(dev->dev, "Error on setting RF timings\n");
		वापस rc;
	पूर्ण

	चयन (dev->device_type) अणु
	हाल PN533_DEVICE_STD:
	हाल PN533_DEVICE_PN532:
	हाल PN533_DEVICE_PN532_AUTOPOLL:
		अवरोध;

	हाल PN533_DEVICE_PASORI:
		pn533_pasori_fw_reset(dev);

		rc = pn533_set_configuration(dev, PN533_CFGITEM_PASORI,
					     pasori_cfg, 3);
		अगर (rc) अणु
			nfc_err(dev->dev,
				"Error while settings PASORI config\n");
			वापस rc;
		पूर्ण

		pn533_pasori_fw_reset(dev);

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pn533_finalize_setup(काष्ठा pn533 *dev)
अणु

	काष्ठा pn533_fw_version fw_ver;
	पूर्णांक rc;

	स_रखो(&fw_ver, 0, माप(fw_ver));

	rc = pn533_get_firmware_version(dev, &fw_ver);
	अगर (rc) अणु
		nfc_err(dev->dev, "Unable to get FW version\n");
		वापस rc;
	पूर्ण

	nfc_info(dev->dev, "NXP PN5%02X firmware ver %d.%d now attached\n",
		fw_ver.ic, fw_ver.ver, fw_ver.rev);

	rc = pn533_setup(dev);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pn533_finalize_setup);

काष्ठा pn533 *pn53x_common_init(u32 device_type,
				क्रमागत pn533_protocol_type protocol_type,
				व्योम *phy,
				काष्ठा pn533_phy_ops *phy_ops,
				काष्ठा pn533_frame_ops *fops,
				काष्ठा device *dev)
अणु
	काष्ठा pn533 *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	priv->phy = phy;
	priv->phy_ops = phy_ops;
	priv->dev = dev;
	अगर (fops != शून्य)
		priv->ops = fops;
	अन्यथा
		priv->ops = &pn533_std_frame_ops;

	priv->protocol_type = protocol_type;
	priv->device_type = device_type;

	mutex_init(&priv->cmd_lock);

	INIT_WORK(&priv->cmd_work, pn533_wq_cmd);
	INIT_WORK(&priv->cmd_complete_work, pn533_wq_cmd_complete);
	INIT_WORK(&priv->mi_rx_work, pn533_wq_mi_recv);
	INIT_WORK(&priv->mi_tx_work, pn533_wq_mi_send);
	INIT_WORK(&priv->tg_work, pn533_wq_tg_get_data);
	INIT_WORK(&priv->mi_पंचांग_rx_work, pn533_wq_पंचांग_mi_recv);
	INIT_WORK(&priv->mi_पंचांग_tx_work, pn533_wq_पंचांग_mi_send);
	INIT_DELAYED_WORK(&priv->poll_work, pn533_wq_poll);
	INIT_WORK(&priv->rf_work, pn533_wq_rf);
	priv->wq = alloc_ordered_workqueue("pn533", 0);
	अगर (priv->wq == शून्य)
		जाओ error;

	समयr_setup(&priv->listen_समयr, pn533_listen_mode_समयr, 0);

	skb_queue_head_init(&priv->resp_q);
	skb_queue_head_init(&priv->fragment_skb);

	INIT_LIST_HEAD(&priv->cmd_queue);
	वापस priv;

error:
	kमुक्त(priv);
	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL_GPL(pn53x_common_init);

व्योम pn53x_common_clean(काष्ठा pn533 *priv)
अणु
	काष्ठा pn533_cmd *cmd, *n;

	flush_delayed_work(&priv->poll_work);
	destroy_workqueue(priv->wq);

	skb_queue_purge(&priv->resp_q);

	del_समयr(&priv->listen_समयr);

	list_क्रम_each_entry_safe(cmd, n, &priv->cmd_queue, queue) अणु
		list_del(&cmd->queue);
		kमुक्त(cmd);
	पूर्ण

	kमुक्त(priv);
पूर्ण
EXPORT_SYMBOL_GPL(pn53x_common_clean);

पूर्णांक pn532_i2c_nfc_alloc(काष्ठा pn533 *priv, u32 protocols,
			काष्ठा device *parent)
अणु
	priv->nfc_dev = nfc_allocate_device(&pn533_nfc_ops, protocols,
					   priv->ops->tx_header_len +
					   PN533_CMD_DATAEXCH_HEAD_LEN,
					   priv->ops->tx_tail_len);
	अगर (!priv->nfc_dev)
		वापस -ENOMEM;

	nfc_set_parent_dev(priv->nfc_dev, parent);
	nfc_set_drvdata(priv->nfc_dev, priv);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pn532_i2c_nfc_alloc);

पूर्णांक pn53x_रेजिस्टर_nfc(काष्ठा pn533 *priv, u32 protocols,
			काष्ठा device *parent)
अणु
	पूर्णांक rc;

	rc = pn532_i2c_nfc_alloc(priv, protocols, parent);
	अगर (rc)
		वापस rc;

	rc = nfc_रेजिस्टर_device(priv->nfc_dev);
	अगर (rc)
		nfc_मुक्त_device(priv->nfc_dev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pn53x_रेजिस्टर_nfc);

व्योम pn53x_unरेजिस्टर_nfc(काष्ठा pn533 *priv)
अणु
	nfc_unरेजिस्टर_device(priv->nfc_dev);
	nfc_मुक्त_device(priv->nfc_dev);
पूर्ण
EXPORT_SYMBOL_GPL(pn53x_unरेजिस्टर_nfc);

MODULE_AUTHOR("Lauro Ramos Venancio <lauro.venancio@openbossa.org>");
MODULE_AUTHOR("Aloisio Almeida Jr <aloisio.almeida@openbossa.org>");
MODULE_AUTHOR("Waldemar Rymarkiewicz <waldemar.rymarkiewicz@tieto.com>");
MODULE_DESCRIPTION("PN533 driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
