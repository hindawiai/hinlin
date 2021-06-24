<शैली गुरु>
/*
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

/* Inspired (hugely) by HCI LDISC implementation in Bluetooth.
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

#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>

/* TX states  */
#घोषणा NCI_UART_SENDING	1
#घोषणा NCI_UART_TX_WAKEUP	2

अटल काष्ठा nci_uart *nci_uart_drivers[NCI_UART_DRIVER_MAX];

अटल अंतरभूत काष्ठा sk_buff *nci_uart_dequeue(काष्ठा nci_uart *nu)
अणु
	काष्ठा sk_buff *skb = nu->tx_skb;

	अगर (!skb)
		skb = skb_dequeue(&nu->tx_q);
	अन्यथा
		nu->tx_skb = शून्य;

	वापस skb;
पूर्ण

अटल अंतरभूत पूर्णांक nci_uart_queue_empty(काष्ठा nci_uart *nu)
अणु
	अगर (nu->tx_skb)
		वापस 0;

	वापस skb_queue_empty(&nu->tx_q);
पूर्ण

अटल पूर्णांक nci_uart_tx_wakeup(काष्ठा nci_uart *nu)
अणु
	अगर (test_and_set_bit(NCI_UART_SENDING, &nu->tx_state)) अणु
		set_bit(NCI_UART_TX_WAKEUP, &nu->tx_state);
		वापस 0;
	पूर्ण

	schedule_work(&nu->ग_लिखो_work);

	वापस 0;
पूर्ण

अटल व्योम nci_uart_ग_लिखो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nci_uart *nu = container_of(work, काष्ठा nci_uart, ग_लिखो_work);
	काष्ठा tty_काष्ठा *tty = nu->tty;
	काष्ठा sk_buff *skb;

restart:
	clear_bit(NCI_UART_TX_WAKEUP, &nu->tx_state);

	अगर (nu->ops.tx_start)
		nu->ops.tx_start(nu);

	जबतक ((skb = nci_uart_dequeue(nu))) अणु
		पूर्णांक len;

		set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		len = tty->ops->ग_लिखो(tty, skb->data, skb->len);
		skb_pull(skb, len);
		अगर (skb->len) अणु
			nu->tx_skb = skb;
			अवरोध;
		पूर्ण
		kमुक्त_skb(skb);
	पूर्ण

	अगर (test_bit(NCI_UART_TX_WAKEUP, &nu->tx_state))
		जाओ restart;

	अगर (nu->ops.tx_करोne && nci_uart_queue_empty(nu))
		nu->ops.tx_करोne(nu);

	clear_bit(NCI_UART_SENDING, &nu->tx_state);
पूर्ण

अटल पूर्णांक nci_uart_set_driver(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक driver)
अणु
	काष्ठा nci_uart *nu = शून्य;
	पूर्णांक ret;

	अगर (driver >= NCI_UART_DRIVER_MAX)
		वापस -EINVAL;

	अगर (!nci_uart_drivers[driver])
		वापस -ENOENT;

	nu = kzalloc(माप(*nu), GFP_KERNEL);
	अगर (!nu)
		वापस -ENOMEM;

	स_नकल(nu, nci_uart_drivers[driver], माप(काष्ठा nci_uart));
	nu->tty = tty;
	tty->disc_data = nu;
	skb_queue_head_init(&nu->tx_q);
	INIT_WORK(&nu->ग_लिखो_work, nci_uart_ग_लिखो_work);
	spin_lock_init(&nu->rx_lock);

	ret = nu->ops.खोलो(nu);
	अगर (ret) अणु
		tty->disc_data = शून्य;
		kमुक्त(nu);
	पूर्ण अन्यथा अगर (!try_module_get(nu->owner)) अणु
		nu->ops.बंद(nu);
		tty->disc_data = शून्य;
		kमुक्त(nu);
		वापस -ENOENT;
	पूर्ण
	वापस ret;
पूर्ण

/* ------ LDISC part ------ */

/* nci_uart_tty_खोलो
 *
 *     Called when line discipline changed to NCI_UART.
 *
 * Arguments:
 *     tty    poपूर्णांकer to tty info काष्ठाure
 * Return Value:
 *     0 अगर success, otherwise error code
 */
अटल पूर्णांक nci_uart_tty_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	/* Error अगर the tty has no ग_लिखो op instead of leaving an exploitable
	 * hole
	 */
	अगर (!tty->ops->ग_लिखो)
		वापस -EOPNOTSUPP;

	tty->disc_data = शून्य;
	tty->receive_room = 65536;

	/* Flush any pending अक्षरacters in the driver */
	tty_driver_flush_buffer(tty);

	वापस 0;
पूर्ण

/* nci_uart_tty_बंद()
 *
 *    Called when the line discipline is changed to something
 *    अन्यथा, the tty is बंदd, or the tty detects a hangup.
 */
अटल व्योम nci_uart_tty_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा nci_uart *nu = (व्योम *)tty->disc_data;

	/* Detach from the tty */
	tty->disc_data = शून्य;

	अगर (!nu)
		वापस;

	kमुक्त_skb(nu->tx_skb);
	kमुक्त_skb(nu->rx_skb);

	skb_queue_purge(&nu->tx_q);

	nu->ops.बंद(nu);
	nu->tty = शून्य;
	module_put(nu->owner);

	cancel_work_sync(&nu->ग_लिखो_work);

	kमुक्त(nu);
पूर्ण

/* nci_uart_tty_wakeup()
 *
 *    Callback क्रम transmit wakeup. Called when low level
 *    device driver can accept more send data.
 *
 * Arguments:        tty    poपूर्णांकer to associated tty instance data
 * Return Value:    None
 */
अटल व्योम nci_uart_tty_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा nci_uart *nu = (व्योम *)tty->disc_data;

	अगर (!nu)
		वापस;

	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

	अगर (tty != nu->tty)
		वापस;

	nci_uart_tx_wakeup(nu);
पूर्ण

/* -- Default recv_buf handler --
 *
 * This handler supposes that NCI frames are sent over UART link without any
 * framing. It पढ़ोs NCI header, retrieve the packet size and once all packet
 * bytes are received it passes it to nci_uart driver क्रम processing.
 */
अटल पूर्णांक nci_uart_शेष_recv_buf(काष्ठा nci_uart *nu, स्थिर u8 *data,
				     पूर्णांक count)
अणु
	पूर्णांक chunk_len;

	अगर (!nu->ndev) अणु
		nfc_err(nu->tty->dev,
			"receive data from tty but no NCI dev is attached yet, drop buffer\n");
		वापस 0;
	पूर्ण

	/* Decode all incoming data in packets
	 * and enqueue then क्रम processing.
	 */
	जबतक (count > 0) अणु
		/* If this is the first data of a packet, allocate a buffer */
		अगर (!nu->rx_skb) अणु
			nu->rx_packet_len = -1;
			nu->rx_skb = nci_skb_alloc(nu->ndev,
						   NCI_MAX_PACKET_SIZE,
						   GFP_ATOMIC);
			अगर (!nu->rx_skb)
				वापस -ENOMEM;
		पूर्ण

		/* Eat byte after byte till full packet header is received */
		अगर (nu->rx_skb->len < NCI_CTRL_HDR_SIZE) अणु
			skb_put_u8(nu->rx_skb, *data++);
			--count;
			जारी;
		पूर्ण

		/* Header was received but packet len was not पढ़ो */
		अगर (nu->rx_packet_len < 0)
			nu->rx_packet_len = NCI_CTRL_HDR_SIZE +
				nci_plen(nu->rx_skb->data);

		/* Compute how many bytes are missing and how many bytes can
		 * be consumed.
		 */
		chunk_len = nu->rx_packet_len - nu->rx_skb->len;
		अगर (count < chunk_len)
			chunk_len = count;
		skb_put_data(nu->rx_skb, data, chunk_len);
		data += chunk_len;
		count -= chunk_len;

		/* Check अगर packet is fully received */
		अगर (nu->rx_packet_len == nu->rx_skb->len) अणु
			/* Pass RX packet to driver */
			अगर (nu->ops.recv(nu, nu->rx_skb) != 0)
				nfc_err(nu->tty->dev, "corrupted RX packet\n");
			/* Next packet will be a new one */
			nu->rx_skb = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* nci_uart_tty_receive()
 *
 *     Called by tty low level driver when receive data is
 *     available.
 *
 * Arguments:  tty          poपूर्णांकer to tty instance data
 *             data         poपूर्णांकer to received data
 *             flags        poपूर्णांकer to flags क्रम data
 *             count        count of received data in bytes
 *
 * Return Value:    None
 */
अटल व्योम nci_uart_tty_receive(काष्ठा tty_काष्ठा *tty, स्थिर u8 *data,
				 अक्षर *flags, पूर्णांक count)
अणु
	काष्ठा nci_uart *nu = (व्योम *)tty->disc_data;

	अगर (!nu || tty != nu->tty)
		वापस;

	spin_lock(&nu->rx_lock);
	nci_uart_शेष_recv_buf(nu, data, count);
	spin_unlock(&nu->rx_lock);

	tty_unthrottle(tty);
पूर्ण

/* nci_uart_tty_ioctl()
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
अटल पूर्णांक nci_uart_tty_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा nci_uart *nu = (व्योम *)tty->disc_data;
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल NCIUARTSETDRIVER:
		अगर (!nu)
			वापस nci_uart_set_driver(tty, (अचिन्हित पूर्णांक)arg);
		अन्यथा
			वापस -EBUSY;
		अवरोध;
	शेष:
		err = n_tty_ioctl_helper(tty, file, cmd, arg);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* We करोn't provide पढ़ो/ग_लिखो/poll पूर्णांकerface क्रम user space. */
अटल sमाप_प्रकार nci_uart_tty_पढ़ो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
				 अचिन्हित अक्षर *buf, माप_प्रकार nr,
				 व्योम **cookie, अचिन्हित दीर्घ offset)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार nci_uart_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
				  स्थिर अचिन्हित अक्षर *data, माप_प्रकार count)
अणु
	वापस 0;
पूर्ण

अटल __poll_t nci_uart_tty_poll(काष्ठा tty_काष्ठा *tty,
				      काष्ठा file *filp, poll_table *रुको)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nci_uart_send(काष्ठा nci_uart *nu, काष्ठा sk_buff *skb)
अणु
	/* Queue TX packet */
	skb_queue_tail(&nu->tx_q, skb);

	/* Try to start TX (अगर possible) */
	nci_uart_tx_wakeup(nu);

	वापस 0;
पूर्ण

पूर्णांक nci_uart_रेजिस्टर(काष्ठा nci_uart *nu)
अणु
	अगर (!nu || !nu->ops.खोलो ||
	    !nu->ops.recv || !nu->ops.बंद)
		वापस -EINVAL;

	/* Set the send callback */
	nu->ops.send = nci_uart_send;

	/* Add this driver in the driver list */
	अगर (nci_uart_drivers[nu->driver]) अणु
		pr_err("driver %d is already registered\n", nu->driver);
		वापस -EBUSY;
	पूर्ण
	nci_uart_drivers[nu->driver] = nu;

	pr_info("NCI uart driver '%s [%d]' registered\n", nu->name, nu->driver);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nci_uart_रेजिस्टर);

व्योम nci_uart_unरेजिस्टर(काष्ठा nci_uart *nu)
अणु
	pr_info("NCI uart driver '%s [%d]' unregistered\n", nu->name,
		nu->driver);

	/* Remove this driver from the driver list */
	nci_uart_drivers[nu->driver] = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nci_uart_unरेजिस्टर);

व्योम nci_uart_set_config(काष्ठा nci_uart *nu, पूर्णांक baudrate, पूर्णांक flow_ctrl)
अणु
	काष्ठा ktermios new_termios;

	अगर (!nu->tty)
		वापस;

	करोwn_पढ़ो(&nu->tty->termios_rwsem);
	new_termios = nu->tty->termios;
	up_पढ़ो(&nu->tty->termios_rwsem);
	tty_termios_encode_baud_rate(&new_termios, baudrate, baudrate);

	अगर (flow_ctrl)
		new_termios.c_cflag |= CRTSCTS;
	अन्यथा
		new_termios.c_cflag &= ~CRTSCTS;

	tty_set_termios(nu->tty, &new_termios);
पूर्ण
EXPORT_SYMBOL_GPL(nci_uart_set_config);

अटल काष्ठा tty_ldisc_ops nci_uart_ldisc = अणु
	.owner		= THIS_MODULE,
	.name		= "n_nci",
	.खोलो		= nci_uart_tty_खोलो,
	.बंद		= nci_uart_tty_बंद,
	.पढ़ो		= nci_uart_tty_पढ़ो,
	.ग_लिखो		= nci_uart_tty_ग_लिखो,
	.poll		= nci_uart_tty_poll,
	.receive_buf	= nci_uart_tty_receive,
	.ग_लिखो_wakeup	= nci_uart_tty_wakeup,
	.ioctl		= nci_uart_tty_ioctl,
	.compat_ioctl	= nci_uart_tty_ioctl,
पूर्ण;

अटल पूर्णांक __init nci_uart_init(व्योम)
अणु
	वापस tty_रेजिस्टर_ldisc(N_NCI, &nci_uart_ldisc);
पूर्ण

अटल व्योम __निकास nci_uart_निकास(व्योम)
अणु
	tty_unरेजिस्टर_ldisc(N_NCI);
पूर्ण

module_init(nci_uart_init);
module_निकास(nci_uart_निकास);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("NFC NCI UART driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_NCI);
