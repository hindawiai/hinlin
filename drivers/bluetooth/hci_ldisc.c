<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth HCI UART driver
 *
 *  Copyright (C) 2000-2001  Qualcomm Incorporated
 *  Copyright (C) 2002-2003  Maxim Krasnyansky <maxk@qualcomm.com>
 *  Copyright (C) 2004-2005  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 */

#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/poll.h>

#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/firmware.h>
#समावेश <linux/serdev.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btintel.h"
#समावेश "btbcm.h"
#समावेश "hci_uart.h"

#घोषणा VERSION "2.3"

अटल स्थिर काष्ठा hci_uart_proto *hup[HCI_UART_MAX_PROTO];

पूर्णांक hci_uart_रेजिस्टर_proto(स्थिर काष्ठा hci_uart_proto *p)
अणु
	अगर (p->id >= HCI_UART_MAX_PROTO)
		वापस -EINVAL;

	अगर (hup[p->id])
		वापस -EEXIST;

	hup[p->id] = p;

	BT_INFO("HCI UART protocol %s registered", p->name);

	वापस 0;
पूर्ण

पूर्णांक hci_uart_unरेजिस्टर_proto(स्थिर काष्ठा hci_uart_proto *p)
अणु
	अगर (p->id >= HCI_UART_MAX_PROTO)
		वापस -EINVAL;

	अगर (!hup[p->id])
		वापस -EINVAL;

	hup[p->id] = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto *hci_uart_get_proto(अचिन्हित पूर्णांक id)
अणु
	अगर (id >= HCI_UART_MAX_PROTO)
		वापस शून्य;

	वापस hup[id];
पूर्ण

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
		percpu_करोwn_पढ़ो(&hu->proto_lock);

		अगर (test_bit(HCI_UART_PROTO_READY, &hu->flags))
			skb = hu->proto->dequeue(hu);

		percpu_up_पढ़ो(&hu->proto_lock);
	पूर्ण अन्यथा अणु
		hu->tx_skb = शून्य;
	पूर्ण

	वापस skb;
पूर्ण

पूर्णांक hci_uart_tx_wakeup(काष्ठा hci_uart *hu)
अणु
	/* This may be called in an IRQ context, so we can't sleep. Thereक्रमe
	 * we try to acquire the lock only, and अगर that fails we assume the
	 * tty is being बंदd because that is the only समय the ग_लिखो lock is
	 * acquired. If, however, at some poपूर्णांक in the future the ग_लिखो lock
	 * is also acquired in other situations, then this must be revisited.
	 */
	अगर (!percpu_करोwn_पढ़ो_trylock(&hu->proto_lock))
		वापस 0;

	अगर (!test_bit(HCI_UART_PROTO_READY, &hu->flags))
		जाओ no_schedule;

	set_bit(HCI_UART_TX_WAKEUP, &hu->tx_state);
	अगर (test_and_set_bit(HCI_UART_SENDING, &hu->tx_state))
		जाओ no_schedule;

	BT_DBG("");

	schedule_work(&hu->ग_लिखो_work);

no_schedule:
	percpu_up_पढ़ो(&hu->proto_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hci_uart_tx_wakeup);

अटल व्योम hci_uart_ग_लिखो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_uart *hu = container_of(work, काष्ठा hci_uart, ग_लिखो_work);
	काष्ठा tty_काष्ठा *tty = hu->tty;
	काष्ठा hci_dev *hdev = hu->hdev;
	काष्ठा sk_buff *skb;

	/* REVISIT: should we cope with bad skbs or ->ग_लिखो() वापसing
	 * and error value ?
	 */

restart:
	clear_bit(HCI_UART_TX_WAKEUP, &hu->tx_state);

	जबतक ((skb = hci_uart_dequeue(hu))) अणु
		पूर्णांक len;

		set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		len = tty->ops->ग_लिखो(tty, skb->data, skb->len);
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
	अगर (test_bit(HCI_UART_TX_WAKEUP, &hu->tx_state))
		जाओ restart;

	wake_up_bit(&hu->tx_state, HCI_UART_SENDING);
पूर्ण

व्योम hci_uart_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_uart *hu = container_of(work, काष्ठा hci_uart, init_पढ़ोy);
	पूर्णांक err;
	काष्ठा hci_dev *hdev;

	अगर (!test_and_clear_bit(HCI_UART_INIT_PENDING, &hu->hdev_flags))
		वापस;

	err = hci_रेजिस्टर_dev(hu->hdev);
	अगर (err < 0) अणु
		BT_ERR("Can't register HCI device");
		clear_bit(HCI_UART_PROTO_READY, &hu->flags);
		hu->proto->बंद(hu);
		hdev = hu->hdev;
		hu->hdev = शून्य;
		hci_मुक्त_dev(hdev);
		वापस;
	पूर्ण

	set_bit(HCI_UART_REGISTERED, &hu->flags);
पूर्ण

पूर्णांक hci_uart_init_पढ़ोy(काष्ठा hci_uart *hu)
अणु
	अगर (!test_bit(HCI_UART_INIT_PENDING, &hu->hdev_flags))
		वापस -EALREADY;

	schedule_work(&hu->init_पढ़ोy);

	वापस 0;
पूर्ण

पूर्णांक hci_uart_रुको_until_sent(काष्ठा hci_uart *hu)
अणु
	वापस रुको_on_bit_समयout(&hu->tx_state, HCI_UART_SENDING,
				   TASK_INTERRUPTIBLE,
				   msecs_to_jअगरfies(2000));
पूर्ण

/* ------- Interface to HCI layer ------ */
/* Reset device */
अटल पूर्णांक hci_uart_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu  = hci_get_drvdata(hdev);
	काष्ठा tty_काष्ठा *tty = hu->tty;

	BT_DBG("hdev %p tty %p", hdev, tty);

	अगर (hu->tx_skb) अणु
		kमुक्त_skb(hu->tx_skb); hu->tx_skb = शून्य;
	पूर्ण

	/* Flush any pending अक्षरacters in the driver and discipline. */
	tty_ldisc_flush(tty);
	tty_driver_flush_buffer(tty);

	percpu_करोwn_पढ़ो(&hu->proto_lock);

	अगर (test_bit(HCI_UART_PROTO_READY, &hu->flags))
		hu->proto->flush(hu);

	percpu_up_पढ़ो(&hu->proto_lock);

	वापस 0;
पूर्ण

/* Initialize device */
अटल पूर्णांक hci_uart_खोलो(काष्ठा hci_dev *hdev)
अणु
	BT_DBG("%s %p", hdev->name, hdev);

	/* Unकरो clearing this from hci_uart_बंद() */
	hdev->flush = hci_uart_flush;

	वापस 0;
पूर्ण

/* Close device */
अटल पूर्णांक hci_uart_बंद(काष्ठा hci_dev *hdev)
अणु
	BT_DBG("hdev %p", hdev);

	hci_uart_flush(hdev);
	hdev->flush = शून्य;
	वापस 0;
पूर्ण

/* Send frames from HCI layer */
अटल पूर्णांक hci_uart_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);

	BT_DBG("%s: type %d len %d", hdev->name, hci_skb_pkt_type(skb),
	       skb->len);

	percpu_करोwn_पढ़ो(&hu->proto_lock);

	अगर (!test_bit(HCI_UART_PROTO_READY, &hu->flags)) अणु
		percpu_up_पढ़ो(&hu->proto_lock);
		वापस -EUNATCH;
	पूर्ण

	hu->proto->enqueue(hu, skb);
	percpu_up_पढ़ो(&hu->proto_lock);

	hci_uart_tx_wakeup(hu);

	वापस 0;
पूर्ण

/* Check the underlying device or tty has flow control support */
bool hci_uart_has_flow_control(काष्ठा hci_uart *hu)
अणु
	/* serdev nodes check अगर the needed operations are present */
	अगर (hu->serdev)
		वापस true;

	अगर (hu->tty->driver->ops->tiocmget && hu->tty->driver->ops->tiocmset)
		वापस true;

	वापस false;
पूर्ण

/* Flow control or un-flow control the device */
व्योम hci_uart_set_flow_control(काष्ठा hci_uart *hu, bool enable)
अणु
	काष्ठा tty_काष्ठा *tty = hu->tty;
	काष्ठा ktermios ktermios;
	पूर्णांक status;
	अचिन्हित पूर्णांक set = 0;
	अचिन्हित पूर्णांक clear = 0;

	अगर (hu->serdev) अणु
		serdev_device_set_flow_control(hu->serdev, !enable);
		serdev_device_set_rts(hu->serdev, !enable);
		वापस;
	पूर्ण

	अगर (enable) अणु
		/* Disable hardware flow control */
		ktermios = tty->termios;
		ktermios.c_cflag &= ~CRTSCTS;
		status = tty_set_termios(tty, &ktermios);
		BT_DBG("Disabling hardware flow control: %s",
		       status ? "failed" : "success");

		/* Clear RTS to prevent the device from sending */
		/* Most UARTs need OUT2 to enable पूर्णांकerrupts */
		status = tty->driver->ops->tiocmget(tty);
		BT_DBG("Current tiocm 0x%x", status);

		set &= ~(TIOCM_OUT2 | TIOCM_RTS);
		clear = ~set;
		set &= TIOCM_DTR | TIOCM_RTS | TIOCM_OUT1 |
		       TIOCM_OUT2 | TIOCM_LOOP;
		clear &= TIOCM_DTR | TIOCM_RTS | TIOCM_OUT1 |
			 TIOCM_OUT2 | TIOCM_LOOP;
		status = tty->driver->ops->tiocmset(tty, set, clear);
		BT_DBG("Clearing RTS: %s", status ? "failed" : "success");
	पूर्ण अन्यथा अणु
		/* Set RTS to allow the device to send again */
		status = tty->driver->ops->tiocmget(tty);
		BT_DBG("Current tiocm 0x%x", status);

		set |= (TIOCM_OUT2 | TIOCM_RTS);
		clear = ~set;
		set &= TIOCM_DTR | TIOCM_RTS | TIOCM_OUT1 |
		       TIOCM_OUT2 | TIOCM_LOOP;
		clear &= TIOCM_DTR | TIOCM_RTS | TIOCM_OUT1 |
			 TIOCM_OUT2 | TIOCM_LOOP;
		status = tty->driver->ops->tiocmset(tty, set, clear);
		BT_DBG("Setting RTS: %s", status ? "failed" : "success");

		/* Re-enable hardware flow control */
		ktermios = tty->termios;
		ktermios.c_cflag |= CRTSCTS;
		status = tty_set_termios(tty, &ktermios);
		BT_DBG("Enabling hardware flow control: %s",
		       status ? "failed" : "success");
	पूर्ण
पूर्ण

व्योम hci_uart_set_speeds(काष्ठा hci_uart *hu, अचिन्हित पूर्णांक init_speed,
			 अचिन्हित पूर्णांक oper_speed)
अणु
	hu->init_speed = init_speed;
	hu->oper_speed = oper_speed;
पूर्ण

व्योम hci_uart_set_baudrate(काष्ठा hci_uart *hu, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा tty_काष्ठा *tty = hu->tty;
	काष्ठा ktermios ktermios;

	ktermios = tty->termios;
	ktermios.c_cflag &= ~CBAUD;
	tty_termios_encode_baud_rate(&ktermios, speed, speed);

	/* tty_set_termios() वापस not checked as it is always 0 */
	tty_set_termios(tty, &ktermios);

	BT_DBG("%s: New tty speeds: %d/%d", hu->hdev->name,
	       tty->termios.c_ispeed, tty->termios.c_ospeed);
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
		hci_uart_set_baudrate(hu, speed);

	/* Operational speed अगर any */
	अगर (hu->oper_speed)
		speed = hu->oper_speed;
	अन्यथा अगर (hu->proto->oper_speed)
		speed = hu->proto->oper_speed;
	अन्यथा
		speed = 0;

	अगर (hu->proto->set_baudrate && speed) अणु
		err = hu->proto->set_baudrate(hu, speed);
		अगर (!err)
			hci_uart_set_baudrate(hu, speed);
	पूर्ण

	अगर (hu->proto->setup)
		वापस hu->proto->setup(hu);

	अगर (!test_bit(HCI_UART_VND_DETECT, &hu->hdev_flags))
		वापस 0;

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_LOCAL_VERSION, 0, शून्य,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		BT_ERR("%s: Reading local version information failed (%ld)",
		       hdev->name, PTR_ERR(skb));
		वापस 0;
	पूर्ण

	अगर (skb->len != माप(*ver)) अणु
		BT_ERR("%s: Event length mismatch for version information",
		       hdev->name);
		जाओ करोne;
	पूर्ण

	ver = (काष्ठा hci_rp_पढ़ो_local_version *)skb->data;

	चयन (le16_to_cpu(ver->manufacturer)) अणु
#अगर_घोषित CONFIG_BT_HCIUART_INTEL
	हाल 2:
		hdev->set_bdaddr = btपूर्णांकel_set_bdaddr;
		btपूर्णांकel_check_bdaddr(hdev);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_BCM
	हाल 15:
		hdev->set_bdaddr = btbcm_set_bdaddr;
		btbcm_check_bdaddr(hdev);
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण

करोne:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/* ------ LDISC part ------ */
/* hci_uart_tty_खोलो
 *
 *     Called when line discipline changed to HCI_UART.
 *
 * Arguments:
 *     tty    poपूर्णांकer to tty info काष्ठाure
 * Return Value:
 *     0 अगर success, otherwise error code
 */
अटल पूर्णांक hci_uart_tty_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hci_uart *hu;

	BT_DBG("tty %p", tty);

	/* Error अगर the tty has no ग_लिखो op instead of leaving an exploitable
	 * hole
	 */
	अगर (tty->ops->ग_लिखो == शून्य)
		वापस -EOPNOTSUPP;

	hu = kzalloc(माप(काष्ठा hci_uart), GFP_KERNEL);
	अगर (!hu) अणु
		BT_ERR("Can't allocate control structure");
		वापस -ENखाता;
	पूर्ण

	tty->disc_data = hu;
	hu->tty = tty;
	tty->receive_room = 65536;

	/* disable alignment support by शेष */
	hu->alignment = 1;
	hu->padding = 0;

	INIT_WORK(&hu->init_पढ़ोy, hci_uart_init_work);
	INIT_WORK(&hu->ग_लिखो_work, hci_uart_ग_लिखो_work);

	percpu_init_rwsem(&hu->proto_lock);

	/* Flush any pending अक्षरacters in the driver */
	tty_driver_flush_buffer(tty);

	वापस 0;
पूर्ण

/* hci_uart_tty_बंद()
 *
 *    Called when the line discipline is changed to something
 *    अन्यथा, the tty is बंदd, or the tty detects a hangup.
 */
अटल व्योम hci_uart_tty_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hci_uart *hu = tty->disc_data;
	काष्ठा hci_dev *hdev;

	BT_DBG("tty %p", tty);

	/* Detach from the tty */
	tty->disc_data = शून्य;

	अगर (!hu)
		वापस;

	hdev = hu->hdev;
	अगर (hdev)
		hci_uart_बंद(hdev);

	अगर (test_bit(HCI_UART_PROTO_READY, &hu->flags)) अणु
		percpu_करोwn_ग_लिखो(&hu->proto_lock);
		clear_bit(HCI_UART_PROTO_READY, &hu->flags);
		percpu_up_ग_लिखो(&hu->proto_lock);

		cancel_work_sync(&hu->init_पढ़ोy);
		cancel_work_sync(&hu->ग_लिखो_work);

		अगर (hdev) अणु
			अगर (test_bit(HCI_UART_REGISTERED, &hu->flags))
				hci_unरेजिस्टर_dev(hdev);
			hci_मुक्त_dev(hdev);
		पूर्ण
		hu->proto->बंद(hu);
	पूर्ण
	clear_bit(HCI_UART_PROTO_SET, &hu->flags);

	percpu_मुक्त_rwsem(&hu->proto_lock);

	kमुक्त(hu);
पूर्ण

/* hci_uart_tty_wakeup()
 *
 *    Callback क्रम transmit wakeup. Called when low level
 *    device driver can accept more send data.
 *
 * Arguments:        tty    poपूर्णांकer to associated tty instance data
 * Return Value:    None
 */
अटल व्योम hci_uart_tty_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hci_uart *hu = tty->disc_data;

	BT_DBG("");

	अगर (!hu)
		वापस;

	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

	अगर (tty != hu->tty)
		वापस;

	अगर (test_bit(HCI_UART_PROTO_READY, &hu->flags))
		hci_uart_tx_wakeup(hu);
पूर्ण

/* hci_uart_tty_receive()
 *
 *     Called by tty low level driver when receive data is
 *     available.
 *
 * Arguments:  tty          poपूर्णांकer to tty isntance data
 *             data         poपूर्णांकer to received data
 *             flags        poपूर्णांकer to flags क्रम data
 *             count        count of received data in bytes
 *
 * Return Value:    None
 */
अटल व्योम hci_uart_tty_receive(काष्ठा tty_काष्ठा *tty, स्थिर u8 *data,
				 अक्षर *flags, पूर्णांक count)
अणु
	काष्ठा hci_uart *hu = tty->disc_data;

	अगर (!hu || tty != hu->tty)
		वापस;

	percpu_करोwn_पढ़ो(&hu->proto_lock);

	अगर (!test_bit(HCI_UART_PROTO_READY, &hu->flags)) अणु
		percpu_up_पढ़ो(&hu->proto_lock);
		वापस;
	पूर्ण

	/* It करोes not need a lock here as it is alपढ़ोy रक्षित by a mutex in
	 * tty caller
	 */
	hu->proto->recv(hu, data, count);
	percpu_up_पढ़ो(&hu->proto_lock);

	अगर (hu->hdev)
		hu->hdev->stat.byte_rx += count;

	tty_unthrottle(tty);
पूर्ण

अटल पूर्णांक hci_uart_रेजिस्टर_dev(काष्ठा hci_uart *hu)
अणु
	काष्ठा hci_dev *hdev;
	पूर्णांक err;

	BT_DBG("");

	/* Initialize and रेजिस्टर HCI device */
	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		BT_ERR("Can't allocate HCI device");
		वापस -ENOMEM;
	पूर्ण

	hu->hdev = hdev;

	hdev->bus = HCI_UART;
	hci_set_drvdata(hdev, hu);

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
	SET_HCIDEV_DEV(hdev, hu->tty->dev);

	अगर (test_bit(HCI_UART_RAW_DEVICE, &hu->hdev_flags))
		set_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks);

	अगर (test_bit(HCI_UART_EXT_CONFIG, &hu->hdev_flags))
		set_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks);

	अगर (!test_bit(HCI_UART_RESET_ON_INIT, &hu->hdev_flags))
		set_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);

	अगर (test_bit(HCI_UART_CREATE_AMP, &hu->hdev_flags))
		hdev->dev_type = HCI_AMP;
	अन्यथा
		hdev->dev_type = HCI_PRIMARY;

	/* Only call खोलो() क्रम the protocol after hdev is fully initialized as
	 * खोलो() (or a समयr/workqueue it starts) may attempt to reference it.
	 */
	err = hu->proto->खोलो(hu);
	अगर (err) अणु
		hu->hdev = शून्य;
		hci_मुक्त_dev(hdev);
		वापस err;
	पूर्ण

	अगर (test_bit(HCI_UART_INIT_PENDING, &hu->hdev_flags))
		वापस 0;

	अगर (hci_रेजिस्टर_dev(hdev) < 0) अणु
		BT_ERR("Can't register HCI device");
		hu->proto->बंद(hu);
		hu->hdev = शून्य;
		hci_मुक्त_dev(hdev);
		वापस -ENODEV;
	पूर्ण

	set_bit(HCI_UART_REGISTERED, &hu->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक hci_uart_set_proto(काष्ठा hci_uart *hu, पूर्णांक id)
अणु
	स्थिर काष्ठा hci_uart_proto *p;
	पूर्णांक err;

	p = hci_uart_get_proto(id);
	अगर (!p)
		वापस -EPROTONOSUPPORT;

	hu->proto = p;

	err = hci_uart_रेजिस्टर_dev(hu);
	अगर (err) अणु
		वापस err;
	पूर्ण

	set_bit(HCI_UART_PROTO_READY, &hu->flags);
	वापस 0;
पूर्ण

अटल पूर्णांक hci_uart_set_flags(काष्ठा hci_uart *hu, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ valid_flags = BIT(HCI_UART_RAW_DEVICE) |
				    BIT(HCI_UART_RESET_ON_INIT) |
				    BIT(HCI_UART_CREATE_AMP) |
				    BIT(HCI_UART_INIT_PENDING) |
				    BIT(HCI_UART_EXT_CONFIG) |
				    BIT(HCI_UART_VND_DETECT);

	अगर (flags & ~valid_flags)
		वापस -EINVAL;

	hu->hdev_flags = flags;

	वापस 0;
पूर्ण

/* hci_uart_tty_ioctl()
 *
 *    Process IOCTL प्रणाली call क्रम the tty device.
 *
 * Arguments:
 *
 *    tty        poपूर्णांकer to tty instance data
 *    file       poपूर्णांकer to खोलो file object क्रम device
 *    cmd        IOCTL command code
 *    arg        argument क्रम IOCTL call (cmd dependent)
 *
 * Return Value:    Command dependent
 */
अटल पूर्णांक hci_uart_tty_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hci_uart *hu = tty->disc_data;
	पूर्णांक err = 0;

	BT_DBG("");

	/* Verअगरy the status of the device */
	अगर (!hu)
		वापस -EBADF;

	चयन (cmd) अणु
	हाल HCIUARTSETPROTO:
		अगर (!test_and_set_bit(HCI_UART_PROTO_SET, &hu->flags)) अणु
			err = hci_uart_set_proto(hu, arg);
			अगर (err)
				clear_bit(HCI_UART_PROTO_SET, &hu->flags);
		पूर्ण अन्यथा
			err = -EBUSY;
		अवरोध;

	हाल HCIUARTGETPROTO:
		अगर (test_bit(HCI_UART_PROTO_SET, &hu->flags))
			err = hu->proto->id;
		अन्यथा
			err = -EUNATCH;
		अवरोध;

	हाल HCIUARTGETDEVICE:
		अगर (test_bit(HCI_UART_REGISTERED, &hu->flags))
			err = hu->hdev->id;
		अन्यथा
			err = -EUNATCH;
		अवरोध;

	हाल HCIUARTSETFLAGS:
		अगर (test_bit(HCI_UART_PROTO_SET, &hu->flags))
			err = -EBUSY;
		अन्यथा
			err = hci_uart_set_flags(hu, arg);
		अवरोध;

	हाल HCIUARTGETFLAGS:
		err = hu->hdev_flags;
		अवरोध;

	शेष:
		err = n_tty_ioctl_helper(tty, file, cmd, arg);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/*
 * We करोn't provide पढ़ो/ग_लिखो/poll पूर्णांकerface क्रम user space.
 */
अटल sमाप_प्रकार hci_uart_tty_पढ़ो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
				 अचिन्हित अक्षर *buf, माप_प्रकार nr,
				 व्योम **cookie, अचिन्हित दीर्घ offset)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार hci_uart_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
				  स्थिर अचिन्हित अक्षर *data, माप_प्रकार count)
अणु
	वापस 0;
पूर्ण

अटल __poll_t hci_uart_tty_poll(काष्ठा tty_काष्ठा *tty,
				      काष्ठा file *filp, poll_table *रुको)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा tty_ldisc_ops hci_uart_ldisc = अणु
	.owner		= THIS_MODULE,
	.name		= "n_hci",
	.खोलो		= hci_uart_tty_खोलो,
	.बंद		= hci_uart_tty_बंद,
	.पढ़ो		= hci_uart_tty_पढ़ो,
	.ग_लिखो		= hci_uart_tty_ग_लिखो,
	.ioctl		= hci_uart_tty_ioctl,
	.compat_ioctl	= hci_uart_tty_ioctl,
	.poll		= hci_uart_tty_poll,
	.receive_buf	= hci_uart_tty_receive,
	.ग_लिखो_wakeup	= hci_uart_tty_wakeup,
पूर्ण;

अटल पूर्णांक __init hci_uart_init(व्योम)
अणु
	पूर्णांक err;

	BT_INFO("HCI UART driver ver %s", VERSION);

	/* Register the tty discipline */
	err = tty_रेजिस्टर_ldisc(N_HCI, &hci_uart_ldisc);
	अगर (err) अणु
		BT_ERR("HCI line discipline registration failed. (%d)", err);
		वापस err;
	पूर्ण

#अगर_घोषित CONFIG_BT_HCIUART_H4
	h4_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_BCSP
	bcsp_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_LL
	ll_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_ATH3K
	ath_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_3WIRE
	h5_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_INTEL
	पूर्णांकel_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_BCM
	bcm_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_QCA
	qca_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_AG6XX
	ag6xx_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_MRVL
	mrvl_init();
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __निकास hci_uart_निकास(व्योम)
अणु
	पूर्णांक err;

#अगर_घोषित CONFIG_BT_HCIUART_H4
	h4_deinit();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_BCSP
	bcsp_deinit();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_LL
	ll_deinit();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_ATH3K
	ath_deinit();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_3WIRE
	h5_deinit();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_INTEL
	पूर्णांकel_deinit();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_BCM
	bcm_deinit();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_QCA
	qca_deinit();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_AG6XX
	ag6xx_deinit();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BT_HCIUART_MRVL
	mrvl_deinit();
#पूर्ण_अगर

	/* Release tty registration of line discipline */
	err = tty_unरेजिस्टर_ldisc(N_HCI);
	अगर (err)
		BT_ERR("Can't unregister HCI line discipline (%d)", err);
पूर्ण

module_init(hci_uart_init);
module_निकास(hci_uart_निकास);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth HCI UART driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_HCI);
