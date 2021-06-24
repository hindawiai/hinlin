<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Bluetooth HCI serdev driver lib
 *
 *  Copyright (C) 2017  Linaro, Ltd., Rob Herring <robh@kernel.org>
 *
 *  Based on hci_ldisc.c:
 *
 *  Copyright (C) 2000-2001  Qualcomm Incorporated
 *  Copyright (C) 2002-2003  Maxim Krasnyansky <maxk@qualcomm.com>
 *  Copyright (C) 2004-2005  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/serdev.h>
#समावेश <linux/skbuff.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "hci_uart.h"

अटल अंतरभूत व्योम hci_uart_tx_complete(काष्ठा hci_uart *hu, पूर्णांक pkt_type)
अणु
	काष्ठा hci_dev *hdev = hu->hdev;

	/* Update HCI stat counters */
	चयन (pkt_type) अणु
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
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *hci_uart_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा sk_buff *skb = hu->tx_skb;

	अगर (!skb) अणु
		अगर (test_bit(HCI_UART_PROTO_READY, &hu->flags))
			skb = hu->proto->dequeue(hu);
	पूर्ण अन्यथा
		hu->tx_skb = शून्य;

	वापस skb;
पूर्ण

अटल व्योम hci_uart_ग_लिखो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_uart *hu = container_of(work, काष्ठा hci_uart, ग_लिखो_work);
	काष्ठा serdev_device *serdev = hu->serdev;
	काष्ठा hci_dev *hdev = hu->hdev;
	काष्ठा sk_buff *skb;

	/* REVISIT:
	 * should we cope with bad skbs or ->ग_लिखो() वापसing an error value?
	 */
	करो अणु
		clear_bit(HCI_UART_TX_WAKEUP, &hu->tx_state);

		जबतक ((skb = hci_uart_dequeue(hu))) अणु
			पूर्णांक len;

			len = serdev_device_ग_लिखो_buf(serdev,
						      skb->data, skb->len);
			hdev->stat.byte_tx += len;

			skb_pull(skb, len);
			अगर (skb->len) अणु
				hu->tx_skb = skb;
				अवरोध;
			पूर्ण

			hci_uart_tx_complete(hu, hci_skb_pkt_type(skb));
			kमुक्त_skb(skb);
		पूर्ण

		clear_bit(HCI_UART_SENDING, &hu->tx_state);
	पूर्ण जबतक (test_bit(HCI_UART_TX_WAKEUP, &hu->tx_state));
पूर्ण

/* ------- Interface to HCI layer ------ */

/* Reset device */
अटल पूर्णांक hci_uart_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu  = hci_get_drvdata(hdev);

	BT_DBG("hdev %p serdev %p", hdev, hu->serdev);

	अगर (hu->tx_skb) अणु
		kमुक्त_skb(hu->tx_skb); hu->tx_skb = शून्य;
	पूर्ण

	/* Flush any pending अक्षरacters in the driver and discipline. */
	serdev_device_ग_लिखो_flush(hu->serdev);

	अगर (test_bit(HCI_UART_PROTO_READY, &hu->flags))
		hu->proto->flush(hu);

	वापस 0;
पूर्ण

/* Initialize device */
अटल पूर्णांक hci_uart_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	पूर्णांक err;

	BT_DBG("%s %p", hdev->name, hdev);

	/* When Quirk HCI_QUIRK_NON_PERSISTENT_SETUP is set by
	 * driver, BT SoC is completely turned OFF during
	 * BT OFF. Upon next BT ON UART port should be खोलोed.
	 */
	अगर (!test_bit(HCI_UART_PROTO_READY, &hu->flags)) अणु
		err = serdev_device_खोलो(hu->serdev);
		अगर (err)
			वापस err;
		set_bit(HCI_UART_PROTO_READY, &hu->flags);
	पूर्ण

	/* Unकरो clearing this from hci_uart_बंद() */
	hdev->flush = hci_uart_flush;

	वापस 0;
पूर्ण

/* Close device */
अटल पूर्णांक hci_uart_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);

	BT_DBG("hdev %p", hdev);

	अगर (!test_bit(HCI_UART_PROTO_READY, &hu->flags))
		वापस 0;

	hci_uart_flush(hdev);
	hdev->flush = शून्य;

	/* When QUIRK HCI_QUIRK_NON_PERSISTENT_SETUP is set by driver,
	 * BT SOC is completely घातered OFF during BT OFF, holding port
	 * खोलो may drain the battery.
	 */
	अगर (test_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks)) अणु
		clear_bit(HCI_UART_PROTO_READY, &hu->flags);
		serdev_device_बंद(hu->serdev);
	पूर्ण

	वापस 0;
पूर्ण

/* Send frames from HCI layer */
अटल पूर्णांक hci_uart_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);

	BT_DBG("%s: type %d len %d", hdev->name, hci_skb_pkt_type(skb),
	       skb->len);

	hu->proto->enqueue(hu, skb);

	hci_uart_tx_wakeup(hu);

	वापस 0;
पूर्ण

अटल पूर्णांक hci_uart_setup(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा hci_rp_पढ़ो_local_version *ver;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक speed;
	पूर्णांक err;

	/* Init speed अगर any */
	अगर (hu->init_speed)
		speed = hu->init_speed;
	अन्यथा अगर (hu->proto->init_speed)
		speed = hu->proto->init_speed;
	अन्यथा
		speed = 0;

	अगर (speed)
		serdev_device_set_baudrate(hu->serdev, speed);

	/* Operational speed अगर any */
	अगर (hu->oper_speed)
		speed = hu->oper_speed;
	अन्यथा अगर (hu->proto->oper_speed)
		speed = hu->proto->oper_speed;
	अन्यथा
		speed = 0;

	अगर (hu->proto->set_baudrate && speed) अणु
		err = hu->proto->set_baudrate(hu, speed);
		अगर (err)
			bt_dev_err(hdev, "Failed to set baudrate");
		अन्यथा
			serdev_device_set_baudrate(hu->serdev, speed);
	पूर्ण

	अगर (hu->proto->setup)
		वापस hu->proto->setup(hu);

	अगर (!test_bit(HCI_UART_VND_DETECT, &hu->hdev_flags))
		वापस 0;

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_LOCAL_VERSION, 0, शून्य,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Reading local version info failed (%ld)",
			   PTR_ERR(skb));
		वापस 0;
	पूर्ण

	अगर (skb->len != माप(*ver))
		bt_dev_err(hdev, "Event length mismatch for version info");

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/** hci_uart_ग_लिखो_wakeup - transmit buffer wakeup
 * @serdev: serial device
 *
 * This function is called by the serdev framework when it accepts
 * more data being sent.
 */
अटल व्योम hci_uart_ग_लिखो_wakeup(काष्ठा serdev_device *serdev)
अणु
	काष्ठा hci_uart *hu = serdev_device_get_drvdata(serdev);

	BT_DBG("");

	अगर (!hu || serdev != hu->serdev) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (test_bit(HCI_UART_PROTO_READY, &hu->flags))
		hci_uart_tx_wakeup(hu);
पूर्ण

/** hci_uart_receive_buf - receive buffer wakeup
 * @serdev: serial device
 * @data:   poपूर्णांकer to received data
 * @count:  count of received data in bytes
 *
 * This function is called by the serdev framework when it received data
 * in the RX buffer.
 *
 * Return: number of processed bytes
 */
अटल पूर्णांक hci_uart_receive_buf(काष्ठा serdev_device *serdev, स्थिर u8 *data,
				   माप_प्रकार count)
अणु
	काष्ठा hci_uart *hu = serdev_device_get_drvdata(serdev);

	अगर (!hu || serdev != hu->serdev) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण

	अगर (!test_bit(HCI_UART_PROTO_READY, &hu->flags))
		वापस 0;

	/* It करोes not need a lock here as it is alपढ़ोy रक्षित by a mutex in
	 * tty caller
	 */
	hu->proto->recv(hu, data, count);

	अगर (hu->hdev)
		hu->hdev->stat.byte_rx += count;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा serdev_device_ops hci_serdev_client_ops = अणु
	.receive_buf = hci_uart_receive_buf,
	.ग_लिखो_wakeup = hci_uart_ग_लिखो_wakeup,
पूर्ण;

पूर्णांक hci_uart_रेजिस्टर_device(काष्ठा hci_uart *hu,
			     स्थिर काष्ठा hci_uart_proto *p)
अणु
	पूर्णांक err;
	काष्ठा hci_dev *hdev;

	BT_DBG("");

	serdev_device_set_client_ops(hu->serdev, &hci_serdev_client_ops);

	err = serdev_device_खोलो(hu->serdev);
	अगर (err)
		वापस err;

	err = p->खोलो(hu);
	अगर (err)
		जाओ err_खोलो;

	hu->proto = p;
	set_bit(HCI_UART_PROTO_READY, &hu->flags);

	/* Initialize and रेजिस्टर HCI device */
	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		BT_ERR("Can't allocate HCI device");
		err = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	hu->hdev = hdev;

	hdev->bus = HCI_UART;
	hci_set_drvdata(hdev, hu);

	INIT_WORK(&hu->init_पढ़ोy, hci_uart_init_work);
	INIT_WORK(&hu->ग_लिखो_work, hci_uart_ग_लिखो_work);
	percpu_init_rwsem(&hu->proto_lock);

	/* Only when venकरोr specअगरic setup callback is provided, consider
	 * the manufacturer inक्रमmation valid. This aव्योमs filling in the
	 * value क्रम Ericsson when nothing is specअगरied.
	 */
	अगर (hu->proto->setup)
		hdev->manufacturer = hu->proto->manufacturer;

	hdev->खोलो  = hci_uart_खोलो;
	hdev->बंद = hci_uart_बंद;
	hdev->flush = hci_uart_flush;
	hdev->send  = hci_uart_send_frame;
	hdev->setup = hci_uart_setup;
	SET_HCIDEV_DEV(hdev, &hu->serdev->dev);

	अगर (test_bit(HCI_UART_RAW_DEVICE, &hu->hdev_flags))
		set_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks);

	अगर (test_bit(HCI_UART_EXT_CONFIG, &hu->hdev_flags))
		set_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks);

	अगर (test_bit(HCI_UART_CREATE_AMP, &hu->hdev_flags))
		hdev->dev_type = HCI_AMP;
	अन्यथा
		hdev->dev_type = HCI_PRIMARY;

	अगर (test_bit(HCI_UART_INIT_PENDING, &hu->hdev_flags))
		वापस 0;

	अगर (hci_रेजिस्टर_dev(hdev) < 0) अणु
		BT_ERR("Can't register HCI device");
		err = -ENODEV;
		जाओ err_रेजिस्टर;
	पूर्ण

	set_bit(HCI_UART_REGISTERED, &hu->flags);

	वापस 0;

err_रेजिस्टर:
	hci_मुक्त_dev(hdev);
err_alloc:
	clear_bit(HCI_UART_PROTO_READY, &hu->flags);
	p->बंद(hu);
err_खोलो:
	serdev_device_बंद(hu->serdev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(hci_uart_रेजिस्टर_device);

व्योम hci_uart_unरेजिस्टर_device(काष्ठा hci_uart *hu)
अणु
	काष्ठा hci_dev *hdev = hu->hdev;

	cancel_work_sync(&hu->init_पढ़ोy);
	अगर (test_bit(HCI_UART_REGISTERED, &hu->flags))
		hci_unरेजिस्टर_dev(hdev);
	hci_मुक्त_dev(hdev);

	cancel_work_sync(&hu->ग_लिखो_work);

	hu->proto->बंद(hu);

	अगर (test_bit(HCI_UART_PROTO_READY, &hu->flags)) अणु
		clear_bit(HCI_UART_PROTO_READY, &hu->flags);
		serdev_device_बंद(hu->serdev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hci_uart_unरेजिस्टर_device);
