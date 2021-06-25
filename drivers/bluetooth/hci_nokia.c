<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Bluetooth HCI UART H4 driver with Nokia Extensions AKA Nokia H4+
 *
 *  Copyright (C) 2015 Marcel Holपंचांगann <marcel@holपंचांगann.org>
 *  Copyright (C) 2015-2017 Sebastian Reichel <sre@kernel.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/serdev.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "hci_uart.h"
#समावेश "btbcm.h"

#घोषणा VERSION "0.1"

#घोषणा NOKIA_ID_BCM2048	0x04
#घोषणा NOKIA_ID_TI1271		0x31

#घोषणा FIRMWARE_BCM2048	"nokia/bcmfw.bin"
#घोषणा FIRMWARE_TI1271		"nokia/ti1273.bin"

#घोषणा HCI_NOKIA_NEG_PKT	0x06
#घोषणा HCI_NOKIA_ALIVE_PKT	0x07
#घोषणा HCI_NOKIA_RADIO_PKT	0x08

#घोषणा HCI_NOKIA_NEG_HDR_SIZE		1
#घोषणा HCI_NOKIA_MAX_NEG_SIZE		255
#घोषणा HCI_NOKIA_ALIVE_HDR_SIZE	1
#घोषणा HCI_NOKIA_MAX_ALIVE_SIZE	255
#घोषणा HCI_NOKIA_RADIO_HDR_SIZE	2
#घोषणा HCI_NOKIA_MAX_RADIO_SIZE	255

#घोषणा NOKIA_PROTO_PKT		0x44
#घोषणा NOKIA_PROTO_BYTE	0x4c

#घोषणा NOKIA_NEG_REQ		0x00
#घोषणा NOKIA_NEG_ACK		0x20
#घोषणा NOKIA_NEG_NAK		0x40

#घोषणा H4_TYPE_SIZE		1

#घोषणा NOKIA_RECV_ALIVE \
	.type = HCI_NOKIA_ALIVE_PKT, \
	.hlen = HCI_NOKIA_ALIVE_HDR_SIZE, \
	.loff = 0, \
	.lsize = 1, \
	.maxlen = HCI_NOKIA_MAX_ALIVE_SIZE \

#घोषणा NOKIA_RECV_NEG \
	.type = HCI_NOKIA_NEG_PKT, \
	.hlen = HCI_NOKIA_NEG_HDR_SIZE, \
	.loff = 0, \
	.lsize = 1, \
	.maxlen = HCI_NOKIA_MAX_NEG_SIZE \

#घोषणा NOKIA_RECV_RADIO \
	.type = HCI_NOKIA_RADIO_PKT, \
	.hlen = HCI_NOKIA_RADIO_HDR_SIZE, \
	.loff = 1, \
	.lsize = 1, \
	.maxlen = HCI_NOKIA_MAX_RADIO_SIZE \

काष्ठा hci_nokia_neg_hdr अणु
	u8	dlen;
पूर्ण __packed;

काष्ठा hci_nokia_neg_cmd अणु
	u8	ack;
	u16	baud;
	u16	unused1;
	u8	proto;
	u16	sys_clk;
	u16	unused2;
पूर्ण __packed;

#घोषणा NOKIA_ALIVE_REQ   0x55
#घोषणा NOKIA_ALIVE_RESP  0xcc

काष्ठा hci_nokia_alive_hdr अणु
	u8	dlen;
पूर्ण __packed;

काष्ठा hci_nokia_alive_pkt अणु
	u8	mid;
	u8	unused;
पूर्ण __packed;

काष्ठा hci_nokia_neg_evt अणु
	u8	ack;
	u16	baud;
	u16	unused1;
	u8	proto;
	u16	sys_clk;
	u16	unused2;
	u8	man_id;
	u8	ver_id;
पूर्ण __packed;

#घोषणा MAX_BAUD_RATE		3692300
#घोषणा SETUP_BAUD_RATE		921600
#घोषणा INIT_BAUD_RATE		120000

काष्ठा hci_nokia_radio_hdr अणु
	u8	evt;
	u8	dlen;
पूर्ण __packed;

काष्ठा nokia_bt_dev अणु
	काष्ठा hci_uart hu;
	काष्ठा serdev_device *serdev;

	काष्ठा gpio_desc *reset;
	काष्ठा gpio_desc *wakeup_host;
	काष्ठा gpio_desc *wakeup_bt;
	अचिन्हित दीर्घ sysclk_speed;

	पूर्णांक wake_irq;
	काष्ठा sk_buff *rx_skb;
	काष्ठा sk_buff_head txq;
	bdaddr_t bdaddr;

	पूर्णांक init_error;
	काष्ठा completion init_completion;

	u8 man_id;
	u8 ver_id;

	bool initialized;
	bool tx_enabled;
	bool rx_enabled;
पूर्ण;

अटल पूर्णांक nokia_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb);

अटल व्योम nokia_flow_control(काष्ठा serdev_device *serdev, bool enable)
अणु
	अगर (enable) अणु
		serdev_device_set_rts(serdev, true);
		serdev_device_set_flow_control(serdev, true);
	पूर्ण अन्यथा अणु
		serdev_device_set_flow_control(serdev, false);
		serdev_device_set_rts(serdev, false);
	पूर्ण
पूर्ण

अटल irqवापस_t wakeup_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nokia_bt_dev *btdev = data;
	काष्ठा device *dev = &btdev->serdev->dev;
	पूर्णांक wake_state = gpiod_get_value(btdev->wakeup_host);

	अगर (btdev->rx_enabled == wake_state)
		वापस IRQ_HANDLED;

	अगर (wake_state)
		pm_runसमय_get(dev);
	अन्यथा
		pm_runसमय_put(dev);

	btdev->rx_enabled = wake_state;

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक nokia_reset(काष्ठा hci_uart *hu)
अणु
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	काष्ठा device *dev = &btdev->serdev->dev;
	पूर्णांक err;

	/* reset routine */
	gpiod_set_value_cansleep(btdev->reset, 1);
	gpiod_set_value_cansleep(btdev->wakeup_bt, 1);

	msleep(100);

	/* safety check */
	err = gpiod_get_value_cansleep(btdev->wakeup_host);
	अगर (err == 1) अणु
		dev_err(dev, "reset: host wakeup not low!");
		वापस -EPROTO;
	पूर्ण

	/* flush queue */
	serdev_device_ग_लिखो_flush(btdev->serdev);

	/* init uart */
	nokia_flow_control(btdev->serdev, false);
	serdev_device_set_baudrate(btdev->serdev, INIT_BAUD_RATE);

	gpiod_set_value_cansleep(btdev->reset, 0);

	/* रुको क्रम cts */
	err = serdev_device_रुको_क्रम_cts(btdev->serdev, true, 200);
	अगर (err < 0) अणु
		dev_err(dev, "CTS not received: %d", err);
		वापस err;
	पूर्ण

	nokia_flow_control(btdev->serdev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक nokia_send_alive_packet(काष्ठा hci_uart *hu)
अणु
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	काष्ठा device *dev = &btdev->serdev->dev;
	काष्ठा hci_nokia_alive_hdr *hdr;
	काष्ठा hci_nokia_alive_pkt *pkt;
	काष्ठा sk_buff *skb;
	पूर्णांक len;

	init_completion(&btdev->init_completion);

	len = H4_TYPE_SIZE + माप(*hdr) + माप(*pkt);
	skb = bt_skb_alloc(len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hci_skb_pkt_type(skb) = HCI_NOKIA_ALIVE_PKT;
	स_रखो(skb->data, 0x00, len);

	hdr = skb_put(skb, माप(*hdr));
	hdr->dlen = माप(*pkt);
	pkt = skb_put(skb, माप(*pkt));
	pkt->mid = NOKIA_ALIVE_REQ;

	nokia_enqueue(hu, skb);
	hci_uart_tx_wakeup(hu);

	dev_dbg(dev, "Alive sent");

	अगर (!रुको_क्रम_completion_पूर्णांकerruptible_समयout(&btdev->init_completion,
		msecs_to_jअगरfies(1000))) अणु
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (btdev->init_error < 0)
		वापस btdev->init_error;

	वापस 0;
पूर्ण

अटल पूर्णांक nokia_send_negotiation(काष्ठा hci_uart *hu)
अणु
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	काष्ठा device *dev = &btdev->serdev->dev;
	काष्ठा hci_nokia_neg_cmd *neg_cmd;
	काष्ठा hci_nokia_neg_hdr *neg_hdr;
	काष्ठा sk_buff *skb;
	पूर्णांक len, err;
	u16 baud = DIV_ROUND_CLOSEST(btdev->sysclk_speed * 10, SETUP_BAUD_RATE);
	पूर्णांक sysclk = btdev->sysclk_speed / 1000;

	len = H4_TYPE_SIZE + माप(*neg_hdr) + माप(*neg_cmd);
	skb = bt_skb_alloc(len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hci_skb_pkt_type(skb) = HCI_NOKIA_NEG_PKT;

	neg_hdr = skb_put(skb, माप(*neg_hdr));
	neg_hdr->dlen = माप(*neg_cmd);

	neg_cmd = skb_put(skb, माप(*neg_cmd));
	neg_cmd->ack = NOKIA_NEG_REQ;
	neg_cmd->baud = cpu_to_le16(baud);
	neg_cmd->unused1 = 0x0000;
	neg_cmd->proto = NOKIA_PROTO_BYTE;
	neg_cmd->sys_clk = cpu_to_le16(sysclk);
	neg_cmd->unused2 = 0x0000;

	btdev->init_error = 0;
	init_completion(&btdev->init_completion);

	nokia_enqueue(hu, skb);
	hci_uart_tx_wakeup(hu);

	dev_dbg(dev, "Negotiation sent");

	अगर (!रुको_क्रम_completion_पूर्णांकerruptible_समयout(&btdev->init_completion,
		msecs_to_jअगरfies(10000))) अणु
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (btdev->init_error < 0)
		वापस btdev->init_error;

	/* Change to previously negotiated speed. Flow Control
	 * is disabled until bluetooth adapter is पढ़ोy to aव्योम
	 * broken bytes being received.
	 */
	nokia_flow_control(btdev->serdev, false);
	serdev_device_set_baudrate(btdev->serdev, SETUP_BAUD_RATE);
	err = serdev_device_रुको_क्रम_cts(btdev->serdev, true, 200);
	अगर (err < 0) अणु
		dev_err(dev, "CTS not received: %d", err);
		वापस err;
	पूर्ण
	nokia_flow_control(btdev->serdev, true);

	dev_dbg(dev, "Negotiation successful");

	वापस 0;
पूर्ण

अटल पूर्णांक nokia_setup_fw(काष्ठा hci_uart *hu)
अणु
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	काष्ठा device *dev = &btdev->serdev->dev;
	स्थिर अक्षर *fwname;
	स्थिर काष्ठा firmware *fw;
	स्थिर u8 *fw_ptr;
	माप_प्रकार fw_size;
	पूर्णांक err;

	dev_dbg(dev, "setup firmware");

	अगर (btdev->man_id == NOKIA_ID_BCM2048) अणु
		fwname = FIRMWARE_BCM2048;
	पूर्ण अन्यथा अगर (btdev->man_id == NOKIA_ID_TI1271) अणु
		fwname = FIRMWARE_TI1271;
	पूर्ण अन्यथा अणु
		dev_err(dev, "Unsupported bluetooth device!");
		वापस -ENODEV;
	पूर्ण

	err = request_firmware(&fw, fwname, dev);
	अगर (err < 0) अणु
		dev_err(dev, "%s: Failed to load Nokia firmware file (%d)",
			hu->hdev->name, err);
		वापस err;
	पूर्ण

	fw_ptr = fw->data;
	fw_size = fw->size;

	जबतक (fw_size >= 4) अणु
		u16 pkt_size = get_unaligned_le16(fw_ptr);
		u8 pkt_type = fw_ptr[2];
		स्थिर काष्ठा hci_command_hdr *cmd;
		u16 opcode;
		काष्ठा sk_buff *skb;

		चयन (pkt_type) अणु
		हाल HCI_COMMAND_PKT:
			cmd = (काष्ठा hci_command_hdr *)(fw_ptr + 3);
			opcode = le16_to_cpu(cmd->opcode);

			skb = __hci_cmd_sync(hu->hdev, opcode, cmd->plen,
					     fw_ptr + 3 + HCI_COMMAND_HDR_SIZE,
					     HCI_INIT_TIMEOUT);
			अगर (IS_ERR(skb)) अणु
				err = PTR_ERR(skb);
				dev_err(dev, "%s: FW command %04x failed (%d)",
				       hu->hdev->name, opcode, err);
				जाओ करोne;
			पूर्ण
			kमुक्त_skb(skb);
			अवरोध;
		हाल HCI_NOKIA_RADIO_PKT:
		हाल HCI_NOKIA_NEG_PKT:
		हाल HCI_NOKIA_ALIVE_PKT:
			अवरोध;
		पूर्ण

		fw_ptr += pkt_size + 2;
		fw_size -= pkt_size + 2;
	पूर्ण

करोne:
	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक nokia_setup(काष्ठा hci_uart *hu)
अणु
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	काष्ठा device *dev = &btdev->serdev->dev;
	पूर्णांक err;

	btdev->initialized = false;

	nokia_flow_control(btdev->serdev, false);

	pm_runसमय_get_sync(dev);

	अगर (btdev->tx_enabled) अणु
		gpiod_set_value_cansleep(btdev->wakeup_bt, 0);
		pm_runसमय_put(&btdev->serdev->dev);
		btdev->tx_enabled = false;
	पूर्ण

	dev_dbg(dev, "protocol setup");

	/* 0. reset connection */
	err = nokia_reset(hu);
	अगर (err < 0) अणु
		dev_err(dev, "Reset failed: %d", err);
		जाओ out;
	पूर्ण

	/* 1. negotiate speed etc */
	err = nokia_send_negotiation(hu);
	अगर (err < 0) अणु
		dev_err(dev, "Negotiation failed: %d", err);
		जाओ out;
	पूर्ण

	/* 2. verअगरy correct setup using alive packet */
	err = nokia_send_alive_packet(hu);
	अगर (err < 0) अणु
		dev_err(dev, "Alive check failed: %d", err);
		जाओ out;
	पूर्ण

	/* 3. send firmware */
	err = nokia_setup_fw(hu);
	अगर (err < 0) अणु
		dev_err(dev, "Could not setup FW: %d", err);
		जाओ out;
	पूर्ण

	nokia_flow_control(btdev->serdev, false);
	serdev_device_set_baudrate(btdev->serdev, MAX_BAUD_RATE);
	nokia_flow_control(btdev->serdev, true);

	अगर (btdev->man_id == NOKIA_ID_BCM2048) अणु
		hu->hdev->set_bdaddr = btbcm_set_bdaddr;
		set_bit(HCI_QUIRK_INVALID_BDADDR, &hu->hdev->quirks);
		dev_dbg(dev, "bcm2048 has invalid bluetooth address!");
	पूर्ण

	dev_dbg(dev, "protocol setup done!");

	gpiod_set_value_cansleep(btdev->wakeup_bt, 0);
	pm_runसमय_put(dev);
	btdev->tx_enabled = false;
	btdev->initialized = true;

	वापस 0;
out:
	pm_runसमय_put(dev);

	वापस err;
पूर्ण

अटल पूर्णांक nokia_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा device *dev = &hu->serdev->dev;

	dev_dbg(dev, "protocol open");

	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक nokia_flush(काष्ठा hci_uart *hu)
अणु
	काष्ठा nokia_bt_dev *btdev = hu->priv;

	dev_dbg(&btdev->serdev->dev, "flush device");

	skb_queue_purge(&btdev->txq);

	वापस 0;
पूर्ण

अटल पूर्णांक nokia_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	काष्ठा device *dev = &btdev->serdev->dev;

	dev_dbg(dev, "close device");

	btdev->initialized = false;

	skb_queue_purge(&btdev->txq);

	kमुक्त_skb(btdev->rx_skb);

	/* disable module */
	gpiod_set_value(btdev->reset, 1);
	gpiod_set_value(btdev->wakeup_bt, 0);

	pm_runसमय_disable(&btdev->serdev->dev);

	वापस 0;
पूर्ण

/* Enqueue frame क्रम transmittion (padding, crc, etc) */
अटल पूर्णांक nokia_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	पूर्णांक err;

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &bt_cb(skb)->pkt_type, 1);

	/* Packets must be word aligned */
	अगर (skb->len % 2) अणु
		err = skb_pad(skb, 1);
		अगर (err)
			वापस err;
		skb_put(skb, 1);
	पूर्ण

	skb_queue_tail(&btdev->txq, skb);

	वापस 0;
पूर्ण

अटल पूर्णांक nokia_recv_negotiation_packet(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	काष्ठा device *dev = &btdev->serdev->dev;
	काष्ठा hci_nokia_neg_hdr *hdr;
	काष्ठा hci_nokia_neg_evt *evt;
	पूर्णांक ret = 0;

	hdr = (काष्ठा hci_nokia_neg_hdr *)skb->data;
	अगर (hdr->dlen != माप(*evt)) अणु
		btdev->init_error = -EIO;
		ret = -EIO;
		जाओ finish_neg;
	पूर्ण

	evt = skb_pull(skb, माप(*hdr));

	अगर (evt->ack != NOKIA_NEG_ACK) अणु
		dev_err(dev, "Negotiation received: wrong reply");
		btdev->init_error = -EINVAL;
		ret = -EINVAL;
		जाओ finish_neg;
	पूर्ण

	btdev->man_id = evt->man_id;
	btdev->ver_id = evt->ver_id;

	dev_dbg(dev, "Negotiation received: baud=%u:clk=%u:manu=%u:vers=%u",
		evt->baud, evt->sys_clk, evt->man_id, evt->ver_id);

finish_neg:
	complete(&btdev->init_completion);
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक nokia_recv_alive_packet(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	काष्ठा device *dev = &btdev->serdev->dev;
	काष्ठा hci_nokia_alive_hdr *hdr;
	काष्ठा hci_nokia_alive_pkt *pkt;
	पूर्णांक ret = 0;

	hdr = (काष्ठा hci_nokia_alive_hdr *)skb->data;
	अगर (hdr->dlen != माप(*pkt)) अणु
		dev_err(dev, "Corrupted alive message");
		btdev->init_error = -EIO;
		ret = -EIO;
		जाओ finish_alive;
	पूर्ण

	pkt = skb_pull(skb, माप(*hdr));

	अगर (pkt->mid != NOKIA_ALIVE_RESP) अणु
		dev_err(dev, "Alive received: invalid response: 0x%02x!",
			pkt->mid);
		btdev->init_error = -EINVAL;
		ret = -EINVAL;
		जाओ finish_alive;
	पूर्ण

	dev_dbg(dev, "Alive received");

finish_alive:
	complete(&btdev->init_completion);
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक nokia_recv_radio(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	/* Packets received on the dedicated radio channel are
	 * HCI events and so feed them back पूर्णांकo the core.
	 */
	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;
	वापस hci_recv_frame(hdev, skb);
पूर्ण

/* Recv data */
अटल स्थिर काष्ठा h4_recv_pkt nokia_recv_pkts[] = अणु
	अणु H4_RECV_ACL,		.recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_SCO,		.recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_EVENT,	.recv = hci_recv_frame पूर्ण,
	अणु NOKIA_RECV_ALIVE,	.recv = nokia_recv_alive_packet पूर्ण,
	अणु NOKIA_RECV_NEG,	.recv = nokia_recv_negotiation_packet पूर्ण,
	अणु NOKIA_RECV_RADIO,	.recv = nokia_recv_radio पूर्ण,
पूर्ण;

अटल पूर्णांक nokia_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	काष्ठा device *dev = &btdev->serdev->dev;
	पूर्णांक err;

	अगर (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		वापस -EUNATCH;

	btdev->rx_skb = h4_recv_buf(hu->hdev, btdev->rx_skb, data, count,
				  nokia_recv_pkts, ARRAY_SIZE(nokia_recv_pkts));
	अगर (IS_ERR(btdev->rx_skb)) अणु
		err = PTR_ERR(btdev->rx_skb);
		dev_err(dev, "Frame reassembly failed (%d)", err);
		btdev->rx_skb = शून्य;
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा sk_buff *nokia_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा nokia_bt_dev *btdev = hu->priv;
	काष्ठा device *dev = &btdev->serdev->dev;
	काष्ठा sk_buff *result = skb_dequeue(&btdev->txq);

	अगर (!btdev->initialized)
		वापस result;

	अगर (btdev->tx_enabled == !!result)
		वापस result;

	अगर (result) अणु
		pm_runसमय_get_sync(dev);
		gpiod_set_value_cansleep(btdev->wakeup_bt, 1);
	पूर्ण अन्यथा अणु
		serdev_device_रुको_until_sent(btdev->serdev, 0);
		gpiod_set_value_cansleep(btdev->wakeup_bt, 0);
		pm_runसमय_put(dev);
	पूर्ण

	btdev->tx_enabled = !!result;

	वापस result;
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto nokia_proto = अणु
	.id		= HCI_UART_NOKIA,
	.name		= "Nokia",
	.खोलो		= nokia_खोलो,
	.बंद		= nokia_बंद,
	.recv		= nokia_recv,
	.enqueue	= nokia_enqueue,
	.dequeue	= nokia_dequeue,
	.flush		= nokia_flush,
	.setup		= nokia_setup,
	.manufacturer	= 1,
पूर्ण;

अटल पूर्णांक nokia_bluetooth_serdev_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा device *dev = &serdev->dev;
	काष्ठा nokia_bt_dev *btdev;
	काष्ठा clk *sysclk;
	पूर्णांक err = 0;

	btdev = devm_kzalloc(dev, माप(*btdev), GFP_KERNEL);
	अगर (!btdev)
		वापस -ENOMEM;

	btdev->hu.serdev = btdev->serdev = serdev;
	serdev_device_set_drvdata(serdev, btdev);

	btdev->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(btdev->reset)) अणु
		err = PTR_ERR(btdev->reset);
		dev_err(dev, "could not get reset gpio: %d", err);
		वापस err;
	पूर्ण

	btdev->wakeup_host = devm_gpiod_get(dev, "host-wakeup", GPIOD_IN);
	अगर (IS_ERR(btdev->wakeup_host)) अणु
		err = PTR_ERR(btdev->wakeup_host);
		dev_err(dev, "could not get host wakeup gpio: %d", err);
		वापस err;
	पूर्ण

	btdev->wake_irq = gpiod_to_irq(btdev->wakeup_host);

	err = devm_request_thपढ़ोed_irq(dev, btdev->wake_irq, शून्य,
		wakeup_handler,
		IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
		"wakeup", btdev);
	अगर (err) अणु
		dev_err(dev, "could request wakeup irq: %d", err);
		वापस err;
	पूर्ण

	btdev->wakeup_bt = devm_gpiod_get(dev, "bluetooth-wakeup",
					   GPIOD_OUT_LOW);
	अगर (IS_ERR(btdev->wakeup_bt)) अणु
		err = PTR_ERR(btdev->wakeup_bt);
		dev_err(dev, "could not get BT wakeup gpio: %d", err);
		वापस err;
	पूर्ण

	sysclk = devm_clk_get(dev, "sysclk");
	अगर (IS_ERR(sysclk)) अणु
		err = PTR_ERR(sysclk);
		dev_err(dev, "could not get sysclk: %d", err);
		वापस err;
	पूर्ण

	clk_prepare_enable(sysclk);
	btdev->sysclk_speed = clk_get_rate(sysclk);
	clk_disable_unprepare(sysclk);

	skb_queue_head_init(&btdev->txq);

	btdev->hu.priv = btdev;
	btdev->hu.alignment = 2; /* Nokia H4+ is word aligned */

	err = hci_uart_रेजिस्टर_device(&btdev->hu, &nokia_proto);
	अगर (err) अणु
		dev_err(dev, "could not register bluetooth uart: %d", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nokia_bluetooth_serdev_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा nokia_bt_dev *btdev = serdev_device_get_drvdata(serdev);

	hci_uart_unरेजिस्टर_device(&btdev->hu);
पूर्ण

अटल पूर्णांक nokia_bluetooth_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा serdev_device *serdev = to_serdev_device(dev);

	nokia_flow_control(serdev, false);
	वापस 0;
पूर्ण

अटल पूर्णांक nokia_bluetooth_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा serdev_device *serdev = to_serdev_device(dev);

	nokia_flow_control(serdev, true);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops nokia_bluetooth_pm_ops = अणु
	SET_RUNTIME_PM_OPS(nokia_bluetooth_runसमय_suspend,
			   nokia_bluetooth_runसमय_resume,
			   शून्य)
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id nokia_bluetooth_of_match[] = अणु
	अणु .compatible = "nokia,h4p-bluetooth", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, nokia_bluetooth_of_match);
#पूर्ण_अगर

अटल काष्ठा serdev_device_driver nokia_bluetooth_serdev_driver = अणु
	.probe = nokia_bluetooth_serdev_probe,
	.हटाओ = nokia_bluetooth_serdev_हटाओ,
	.driver = अणु
		.name = "nokia-bluetooth",
		.pm = &nokia_bluetooth_pm_ops,
		.of_match_table = of_match_ptr(nokia_bluetooth_of_match),
	पूर्ण,
पूर्ण;

module_serdev_device_driver(nokia_bluetooth_serdev_driver);

MODULE_AUTHOR("Sebastian Reichel <sre@kernel.org>");
MODULE_DESCRIPTION("Bluetooth HCI UART Nokia H4+ driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
