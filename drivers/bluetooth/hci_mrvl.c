<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth HCI UART driver क्रम marvell devices
 *
 *  Copyright (C) 2016  Marvell International Ltd.
 *  Copyright (C) 2016  Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/tty.h>
#समावेश <linux/of.h>
#समावेश <linux/serdev.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "hci_uart.h"

#घोषणा HCI_FW_REQ_PKT 0xA5
#घोषणा HCI_CHIP_VER_PKT 0xAA

#घोषणा MRVL_ACK 0x5A
#घोषणा MRVL_NAK 0xBF
#घोषणा MRVL_RAW_DATA 0x1F

क्रमागत अणु
	STATE_CHIP_VER_PENDING,
	STATE_FW_REQ_PENDING,
पूर्ण;

काष्ठा mrvl_data अणु
	काष्ठा sk_buff *rx_skb;
	काष्ठा sk_buff_head txq;
	काष्ठा sk_buff_head rawq;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक tx_len;
	u8 id, rev;
पूर्ण;

काष्ठा mrvl_serdev अणु
	काष्ठा hci_uart hu;
पूर्ण;

काष्ठा hci_mrvl_pkt अणु
	__le16 lhs;
	__le16 rhs;
पूर्ण __packed;
#घोषणा HCI_MRVL_PKT_SIZE 4

अटल पूर्णांक mrvl_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा mrvl_data *mrvl;
	पूर्णांक ret;

	BT_DBG("hu %p", hu);

	अगर (!hci_uart_has_flow_control(hu))
		वापस -EOPNOTSUPP;

	mrvl = kzalloc(माप(*mrvl), GFP_KERNEL);
	अगर (!mrvl)
		वापस -ENOMEM;

	skb_queue_head_init(&mrvl->txq);
	skb_queue_head_init(&mrvl->rawq);

	set_bit(STATE_CHIP_VER_PENDING, &mrvl->flags);

	hu->priv = mrvl;

	अगर (hu->serdev) अणु
		ret = serdev_device_खोलो(hu->serdev);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	kमुक्त(mrvl);

	वापस ret;
पूर्ण

अटल पूर्णांक mrvl_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा mrvl_data *mrvl = hu->priv;

	BT_DBG("hu %p", hu);

	अगर (hu->serdev)
		serdev_device_बंद(hu->serdev);

	skb_queue_purge(&mrvl->txq);
	skb_queue_purge(&mrvl->rawq);
	kमुक्त_skb(mrvl->rx_skb);
	kमुक्त(mrvl);

	hu->priv = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक mrvl_flush(काष्ठा hci_uart *hu)
अणु
	काष्ठा mrvl_data *mrvl = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&mrvl->txq);
	skb_queue_purge(&mrvl->rawq);

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *mrvl_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा mrvl_data *mrvl = hu->priv;
	काष्ठा sk_buff *skb;

	skb = skb_dequeue(&mrvl->txq);
	अगर (!skb) अणु
		/* Any raw data ? */
		skb = skb_dequeue(&mrvl->rawq);
	पूर्ण अन्यथा अणु
		/* Prepend skb with frame type */
		स_नकल(skb_push(skb, 1), &bt_cb(skb)->pkt_type, 1);
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक mrvl_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	काष्ठा mrvl_data *mrvl = hu->priv;

	skb_queue_tail(&mrvl->txq, skb);
	वापस 0;
पूर्ण

अटल व्योम mrvl_send_ack(काष्ठा hci_uart *hu, अचिन्हित अक्षर type)
अणु
	काष्ठा mrvl_data *mrvl = hu->priv;
	काष्ठा sk_buff *skb;

	/* No H4 payload, only 1 byte header */
	skb = bt_skb_alloc(0, GFP_ATOMIC);
	अगर (!skb) अणु
		bt_dev_err(hu->hdev, "Unable to alloc ack/nak packet");
		वापस;
	पूर्ण
	hci_skb_pkt_type(skb) = type;

	skb_queue_tail(&mrvl->txq, skb);
	hci_uart_tx_wakeup(hu);
पूर्ण

अटल पूर्णांक mrvl_recv_fw_req(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_mrvl_pkt *pkt = (व्योम *)skb->data;
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा mrvl_data *mrvl = hu->priv;
	पूर्णांक ret = 0;

	अगर ((pkt->lhs ^ pkt->rhs) != 0xffff) अणु
		bt_dev_err(hdev, "Corrupted mrvl header");
		mrvl_send_ack(hu, MRVL_NAK);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
	mrvl_send_ack(hu, MRVL_ACK);

	अगर (!test_bit(STATE_FW_REQ_PENDING, &mrvl->flags)) अणु
		bt_dev_err(hdev, "Received unexpected firmware request");
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	mrvl->tx_len = le16_to_cpu(pkt->lhs);

	clear_bit(STATE_FW_REQ_PENDING, &mrvl->flags);
	smp_mb__after_atomic();
	wake_up_bit(&mrvl->flags, STATE_FW_REQ_PENDING);

करोne:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक mrvl_recv_chip_ver(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_mrvl_pkt *pkt = (व्योम *)skb->data;
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा mrvl_data *mrvl = hu->priv;
	u16 version = le16_to_cpu(pkt->lhs);
	पूर्णांक ret = 0;

	अगर ((pkt->lhs ^ pkt->rhs) != 0xffff) अणु
		bt_dev_err(hdev, "Corrupted mrvl header");
		mrvl_send_ack(hu, MRVL_NAK);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
	mrvl_send_ack(hu, MRVL_ACK);

	अगर (!test_bit(STATE_CHIP_VER_PENDING, &mrvl->flags)) अणु
		bt_dev_err(hdev, "Received unexpected chip version");
		जाओ करोne;
	पूर्ण

	mrvl->id = version;
	mrvl->rev = version >> 8;

	bt_dev_info(hdev, "Controller id = %x, rev = %x", mrvl->id, mrvl->rev);

	clear_bit(STATE_CHIP_VER_PENDING, &mrvl->flags);
	smp_mb__after_atomic();
	wake_up_bit(&mrvl->flags, STATE_CHIP_VER_PENDING);

करोne:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

#घोषणा HCI_RECV_CHIP_VER \
	.type = HCI_CHIP_VER_PKT, \
	.hlen = HCI_MRVL_PKT_SIZE, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = HCI_MRVL_PKT_SIZE

#घोषणा HCI_RECV_FW_REQ \
	.type = HCI_FW_REQ_PKT, \
	.hlen = HCI_MRVL_PKT_SIZE, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = HCI_MRVL_PKT_SIZE

अटल स्थिर काष्ठा h4_recv_pkt mrvl_recv_pkts[] = अणु
	अणु H4_RECV_ACL,       .recv = hci_recv_frame     पूर्ण,
	अणु H4_RECV_SCO,       .recv = hci_recv_frame     पूर्ण,
	अणु H4_RECV_EVENT,     .recv = hci_recv_frame     पूर्ण,
	अणु HCI_RECV_FW_REQ,   .recv = mrvl_recv_fw_req   पूर्ण,
	अणु HCI_RECV_CHIP_VER, .recv = mrvl_recv_chip_ver पूर्ण,
पूर्ण;

अटल पूर्णांक mrvl_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा mrvl_data *mrvl = hu->priv;

	अगर (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		वापस -EUNATCH;

	mrvl->rx_skb = h4_recv_buf(hu->hdev, mrvl->rx_skb, data, count,
				    mrvl_recv_pkts,
				    ARRAY_SIZE(mrvl_recv_pkts));
	अगर (IS_ERR(mrvl->rx_skb)) अणु
		पूर्णांक err = PTR_ERR(mrvl->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		mrvl->rx_skb = शून्य;
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक mrvl_load_firmware(काष्ठा hci_dev *hdev, स्थिर अक्षर *name)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा mrvl_data *mrvl = hu->priv;
	स्थिर काष्ठा firmware *fw = शून्य;
	स्थिर u8 *fw_ptr, *fw_max;
	पूर्णांक err;

	err = request_firmware(&fw, name, &hdev->dev);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to load firmware file %s", name);
		वापस err;
	पूर्ण

	fw_ptr = fw->data;
	fw_max = fw->data + fw->size;

	bt_dev_info(hdev, "Loading %s", name);

	set_bit(STATE_FW_REQ_PENDING, &mrvl->flags);

	जबतक (fw_ptr <= fw_max) अणु
		काष्ठा sk_buff *skb;

		/* Controller drives the firmware load by sending firmware
		 * request packets containing the expected fragment size.
		 */
		err = रुको_on_bit_समयout(&mrvl->flags, STATE_FW_REQ_PENDING,
					  TASK_INTERRUPTIBLE,
					  msecs_to_jअगरfies(2000));
		अगर (err == 1) अणु
			bt_dev_err(hdev, "Firmware load interrupted");
			err = -EINTR;
			अवरोध;
		पूर्ण अन्यथा अगर (err) अणु
			bt_dev_err(hdev, "Firmware request timeout");
			err = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		bt_dev_dbg(hdev, "Firmware request, expecting %d bytes",
			   mrvl->tx_len);

		अगर (fw_ptr == fw_max) अणु
			/* Controller requests a null size once firmware is
			 * fully loaded. If controller expects more data, there
			 * is an issue.
			 */
			अगर (!mrvl->tx_len) अणु
				bt_dev_info(hdev, "Firmware loading complete");
			पूर्ण अन्यथा अणु
				bt_dev_err(hdev, "Firmware loading failure");
				err = -EINVAL;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (fw_ptr + mrvl->tx_len > fw_max) अणु
			mrvl->tx_len = fw_max - fw_ptr;
			bt_dev_dbg(hdev, "Adjusting tx_len to %d",
				   mrvl->tx_len);
		पूर्ण

		skb = bt_skb_alloc(mrvl->tx_len, GFP_KERNEL);
		अगर (!skb) अणु
			bt_dev_err(hdev, "Failed to alloc mem for FW packet");
			err = -ENOMEM;
			अवरोध;
		पूर्ण
		bt_cb(skb)->pkt_type = MRVL_RAW_DATA;

		skb_put_data(skb, fw_ptr, mrvl->tx_len);
		fw_ptr += mrvl->tx_len;

		set_bit(STATE_FW_REQ_PENDING, &mrvl->flags);

		skb_queue_tail(&mrvl->rawq, skb);
		hci_uart_tx_wakeup(hu);
	पूर्ण

	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक mrvl_setup(काष्ठा hci_uart *hu)
अणु
	पूर्णांक err;

	hci_uart_set_flow_control(hu, true);

	err = mrvl_load_firmware(hu->hdev, "mrvl/helper_uart_3000000.bin");
	अगर (err) अणु
		bt_dev_err(hu->hdev, "Unable to download firmware helper");
		वापस -EINVAL;
	पूर्ण

	/* Let the final ack go out beक्रमe चयनing the baudrate */
	hci_uart_रुको_until_sent(hu);

	अगर (hu->serdev)
		serdev_device_set_baudrate(hu->serdev, 3000000);
	अन्यथा
		hci_uart_set_baudrate(hu, 3000000);

	hci_uart_set_flow_control(hu, false);

	err = mrvl_load_firmware(hu->hdev, "mrvl/uart8897_bt.bin");
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto mrvl_proto = अणु
	.id		= HCI_UART_MRVL,
	.name		= "Marvell",
	.init_speed	= 115200,
	.खोलो		= mrvl_खोलो,
	.बंद		= mrvl_बंद,
	.flush		= mrvl_flush,
	.setup		= mrvl_setup,
	.recv		= mrvl_recv,
	.enqueue	= mrvl_enqueue,
	.dequeue	= mrvl_dequeue,
पूर्ण;

अटल पूर्णांक mrvl_serdev_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा mrvl_serdev *mrvldev;

	mrvldev = devm_kzalloc(&serdev->dev, माप(*mrvldev), GFP_KERNEL);
	अगर (!mrvldev)
		वापस -ENOMEM;

	mrvldev->hu.serdev = serdev;
	serdev_device_set_drvdata(serdev, mrvldev);

	वापस hci_uart_रेजिस्टर_device(&mrvldev->hu, &mrvl_proto);
पूर्ण

अटल व्योम mrvl_serdev_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा mrvl_serdev *mrvldev = serdev_device_get_drvdata(serdev);

	hci_uart_unरेजिस्टर_device(&mrvldev->hu);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mrvl_bluetooth_of_match[] = अणु
	अणु .compatible = "mrvl,88w8897" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mrvl_bluetooth_of_match);
#पूर्ण_अगर

अटल काष्ठा serdev_device_driver mrvl_serdev_driver = अणु
	.probe = mrvl_serdev_probe,
	.हटाओ = mrvl_serdev_हटाओ,
	.driver = अणु
		.name = "hci_uart_mrvl",
		.of_match_table = of_match_ptr(mrvl_bluetooth_of_match),
	पूर्ण,
पूर्ण;

पूर्णांक __init mrvl_init(व्योम)
अणु
	serdev_device_driver_रेजिस्टर(&mrvl_serdev_driver);

	वापस hci_uart_रेजिस्टर_proto(&mrvl_proto);
पूर्ण

पूर्णांक __निकास mrvl_deinit(व्योम)
अणु
	serdev_device_driver_unरेजिस्टर(&mrvl_serdev_driver);

	वापस hci_uart_unरेजिस्टर_proto(&mrvl_proto);
पूर्ण
