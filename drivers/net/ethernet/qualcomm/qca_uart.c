<शैली गुरु>
/*
 *   Copyright (c) 2011, 2012, Qualcomm Atheros Communications Inc.
 *   Copyright (c) 2017, I2SE GmbH
 *
 *   Permission to use, copy, modअगरy, and/or distribute this software
 *   क्रम any purpose with or without fee is hereby granted, provided
 *   that the above copyright notice and this permission notice appear
 *   in all copies.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, सूचीECT, INसूचीECT, OR
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*   This module implements the Qualcomm Atheros UART protocol क्रम
 *   kernel-based UART device; it is essentially an Ethernet-to-UART
 *   serial converter;
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/sched.h>
#समावेश <linux/serdev.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>

#समावेश "qca_7k_common.h"

#घोषणा QCAUART_DRV_VERSION "0.1.0"
#घोषणा QCAUART_DRV_NAME "qcauart"
#घोषणा QCAUART_TX_TIMEOUT (1 * HZ)

काष्ठा qcauart अणु
	काष्ठा net_device *net_dev;
	spinlock_t lock;			/* transmit lock */
	काष्ठा work_काष्ठा tx_work;		/* Flushes transmit buffer   */

	काष्ठा serdev_device *serdev;
	काष्ठा qcafrm_handle frm_handle;
	काष्ठा sk_buff *rx_skb;

	अचिन्हित अक्षर *tx_head;			/* poपूर्णांकer to next XMIT byte */
	पूर्णांक tx_left;				/* bytes left in XMIT queue  */
	अचिन्हित अक्षर *tx_buffer;
पूर्ण;

अटल पूर्णांक
qca_tty_receive(काष्ठा serdev_device *serdev, स्थिर अचिन्हित अक्षर *data,
		माप_प्रकार count)
अणु
	काष्ठा qcauart *qca = serdev_device_get_drvdata(serdev);
	काष्ठा net_device *netdev = qca->net_dev;
	काष्ठा net_device_stats *n_stats = &netdev->stats;
	माप_प्रकार i;

	अगर (!qca->rx_skb) अणु
		qca->rx_skb = netdev_alloc_skb_ip_align(netdev,
							netdev->mtu +
							VLAN_ETH_HLEN);
		अगर (!qca->rx_skb) अणु
			n_stats->rx_errors++;
			n_stats->rx_dropped++;
			वापस 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		s32 retcode;

		retcode = qcafrm_fsm_decode(&qca->frm_handle,
					    qca->rx_skb->data,
					    skb_tailroom(qca->rx_skb),
					    data[i]);

		चयन (retcode) अणु
		हाल QCAFRM_GATHER:
		हाल QCAFRM_NOHEAD:
			अवरोध;
		हाल QCAFRM_NOTAIL:
			netdev_dbg(netdev, "recv: no RX tail\n");
			n_stats->rx_errors++;
			n_stats->rx_dropped++;
			अवरोध;
		हाल QCAFRM_INVLEN:
			netdev_dbg(netdev, "recv: invalid RX length\n");
			n_stats->rx_errors++;
			n_stats->rx_dropped++;
			अवरोध;
		शेष:
			n_stats->rx_packets++;
			n_stats->rx_bytes += retcode;
			skb_put(qca->rx_skb, retcode);
			qca->rx_skb->protocol = eth_type_trans(
						qca->rx_skb, qca->rx_skb->dev);
			qca->rx_skb->ip_summed = CHECKSUM_UNNECESSARY;
			netअगर_rx_ni(qca->rx_skb);
			qca->rx_skb = netdev_alloc_skb_ip_align(netdev,
								netdev->mtu +
								VLAN_ETH_HLEN);
			अगर (!qca->rx_skb) अणु
				netdev_dbg(netdev, "recv: out of RX resources\n");
				n_stats->rx_errors++;
				वापस i;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण

/* Write out any reमुख्यing transmit buffer. Scheduled when tty is writable */
अटल व्योम qcauart_transmit(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qcauart *qca = container_of(work, काष्ठा qcauart, tx_work);
	काष्ठा net_device_stats *n_stats = &qca->net_dev->stats;
	पूर्णांक written;

	spin_lock_bh(&qca->lock);

	/* First make sure we're connected. */
	अगर (!netअगर_running(qca->net_dev)) अणु
		spin_unlock_bh(&qca->lock);
		वापस;
	पूर्ण

	अगर (qca->tx_left <= 0)  अणु
		/* Now serial buffer is almost मुक्त & we can start
		 * transmission of another packet
		 */
		n_stats->tx_packets++;
		spin_unlock_bh(&qca->lock);
		netअगर_wake_queue(qca->net_dev);
		वापस;
	पूर्ण

	written = serdev_device_ग_लिखो_buf(qca->serdev, qca->tx_head,
					  qca->tx_left);
	अगर (written > 0) अणु
		qca->tx_left -= written;
		qca->tx_head += written;
	पूर्ण
	spin_unlock_bh(&qca->lock);
पूर्ण

/* Called by the driver when there's room क्रम more data.
 * Schedule the transmit.
 */
अटल व्योम qca_tty_wakeup(काष्ठा serdev_device *serdev)
अणु
	काष्ठा qcauart *qca = serdev_device_get_drvdata(serdev);

	schedule_work(&qca->tx_work);
पूर्ण

अटल स्थिर काष्ठा serdev_device_ops qca_serdev_ops = अणु
	.receive_buf = qca_tty_receive,
	.ग_लिखो_wakeup = qca_tty_wakeup,
पूर्ण;

अटल पूर्णांक qcauart_netdev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा qcauart *qca = netdev_priv(dev);

	netअगर_start_queue(qca->net_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक qcauart_netdev_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा qcauart *qca = netdev_priv(dev);

	netअगर_stop_queue(dev);
	flush_work(&qca->tx_work);

	spin_lock_bh(&qca->lock);
	qca->tx_left = 0;
	spin_unlock_bh(&qca->lock);

	वापस 0;
पूर्ण

अटल netdev_tx_t
qcauart_netdev_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा net_device_stats *n_stats = &dev->stats;
	काष्ठा qcauart *qca = netdev_priv(dev);
	u8 pad_len = 0;
	पूर्णांक written;
	u8 *pos;

	spin_lock(&qca->lock);

	WARN_ON(qca->tx_left);

	अगर (!netअगर_running(dev))  अणु
		spin_unlock(&qca->lock);
		netdev_warn(qca->net_dev, "xmit: iface is down\n");
		जाओ out;
	पूर्ण

	pos = qca->tx_buffer;

	अगर (skb->len < QCAFRM_MIN_LEN)
		pad_len = QCAFRM_MIN_LEN - skb->len;

	pos += qcafrm_create_header(pos, skb->len + pad_len);

	स_नकल(pos, skb->data, skb->len);
	pos += skb->len;

	अगर (pad_len) अणु
		स_रखो(pos, 0, pad_len);
		pos += pad_len;
	पूर्ण

	pos += qcafrm_create_footer(pos);

	netअगर_stop_queue(qca->net_dev);

	written = serdev_device_ग_लिखो_buf(qca->serdev, qca->tx_buffer,
					  pos - qca->tx_buffer);
	अगर (written > 0) अणु
		qca->tx_left = (pos - qca->tx_buffer) - written;
		qca->tx_head = qca->tx_buffer + written;
		n_stats->tx_bytes += written;
	पूर्ण
	spin_unlock(&qca->lock);

	netअगर_trans_update(dev);
out:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम qcauart_netdev_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा qcauart *qca = netdev_priv(dev);

	netdev_info(qca->net_dev, "Transmit timeout at %ld, latency %ld\n",
		    jअगरfies, dev_trans_start(dev));
	dev->stats.tx_errors++;
	dev->stats.tx_dropped++;
पूर्ण

अटल पूर्णांक qcauart_netdev_init(काष्ठा net_device *dev)
अणु
	काष्ठा qcauart *qca = netdev_priv(dev);
	माप_प्रकार len;

	/* Finish setting up the device info. */
	dev->mtu = QCAFRM_MAX_MTU;
	dev->type = ARPHRD_ETHER;

	len = QCAFRM_HEADER_LEN + QCAFRM_MAX_LEN + QCAFRM_FOOTER_LEN;
	qca->tx_buffer = devm_kदो_स्मृति(&qca->serdev->dev, len, GFP_KERNEL);
	अगर (!qca->tx_buffer)
		वापस -ENOMEM;

	qca->rx_skb = netdev_alloc_skb_ip_align(qca->net_dev,
						qca->net_dev->mtu +
						VLAN_ETH_HLEN);
	अगर (!qca->rx_skb)
		वापस -ENOBUFS;

	वापस 0;
पूर्ण

अटल व्योम qcauart_netdev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा qcauart *qca = netdev_priv(dev);

	dev_kमुक्त_skb(qca->rx_skb);
पूर्ण

अटल स्थिर काष्ठा net_device_ops qcauart_netdev_ops = अणु
	.nकरो_init = qcauart_netdev_init,
	.nकरो_uninit = qcauart_netdev_uninit,
	.nकरो_खोलो = qcauart_netdev_खोलो,
	.nकरो_stop = qcauart_netdev_बंद,
	.nकरो_start_xmit = qcauart_netdev_xmit,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_tx_समयout = qcauart_netdev_tx_समयout,
	.nकरो_validate_addr = eth_validate_addr,
पूर्ण;

अटल व्योम qcauart_netdev_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &qcauart_netdev_ops;
	dev->watchकरोg_समयo = QCAUART_TX_TIMEOUT;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->tx_queue_len = 100;

	/* MTU range: 46 - 1500 */
	dev->min_mtu = QCAFRM_MIN_MTU;
	dev->max_mtu = QCAFRM_MAX_MTU;
पूर्ण

अटल स्थिर काष्ठा of_device_id qca_uart_of_match[] = अणु
	अणु
	 .compatible = "qca,qca7000",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qca_uart_of_match);

अटल पूर्णांक qca_uart_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा net_device *qcauart_dev = alloc_etherdev(माप(काष्ठा qcauart));
	काष्ठा qcauart *qca;
	u32 speed = 115200;
	पूर्णांक ret;

	अगर (!qcauart_dev)
		वापस -ENOMEM;

	qcauart_netdev_setup(qcauart_dev);
	SET_NETDEV_DEV(qcauart_dev, &serdev->dev);

	qca = netdev_priv(qcauart_dev);
	अगर (!qca) अणु
		pr_err("qca_uart: Fail to retrieve private structure\n");
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण
	qca->net_dev = qcauart_dev;
	qca->serdev = serdev;
	qcafrm_fsm_init_uart(&qca->frm_handle);

	spin_lock_init(&qca->lock);
	INIT_WORK(&qca->tx_work, qcauart_transmit);

	of_property_पढ़ो_u32(serdev->dev.of_node, "current-speed", &speed);

	ret = of_get_mac_address(serdev->dev.of_node, qca->net_dev->dev_addr);
	अगर (ret) अणु
		eth_hw_addr_अक्रमom(qca->net_dev);
		dev_info(&serdev->dev, "Using random MAC address: %pM\n",
			 qca->net_dev->dev_addr);
	पूर्ण

	netअगर_carrier_on(qca->net_dev);
	serdev_device_set_drvdata(serdev, qca);
	serdev_device_set_client_ops(serdev, &qca_serdev_ops);

	ret = serdev_device_खोलो(serdev);
	अगर (ret) अणु
		dev_err(&serdev->dev, "Unable to open device %s\n",
			qcauart_dev->name);
		जाओ मुक्त;
	पूर्ण

	speed = serdev_device_set_baudrate(serdev, speed);
	dev_info(&serdev->dev, "Using baudrate: %u\n", speed);

	serdev_device_set_flow_control(serdev, false);

	ret = रेजिस्टर_netdev(qcauart_dev);
	अगर (ret) अणु
		dev_err(&serdev->dev, "Unable to register net device %s\n",
			qcauart_dev->name);
		serdev_device_बंद(serdev);
		cancel_work_sync(&qca->tx_work);
		जाओ मुक्त;
	पूर्ण

	वापस 0;

मुक्त:
	मुक्त_netdev(qcauart_dev);
	वापस ret;
पूर्ण

अटल व्योम qca_uart_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा qcauart *qca = serdev_device_get_drvdata(serdev);

	unरेजिस्टर_netdev(qca->net_dev);

	/* Flush any pending अक्षरacters in the driver. */
	serdev_device_बंद(serdev);
	cancel_work_sync(&qca->tx_work);

	मुक्त_netdev(qca->net_dev);
पूर्ण

अटल काष्ठा serdev_device_driver qca_uart_driver = अणु
	.probe = qca_uart_probe,
	.हटाओ = qca_uart_हटाओ,
	.driver = अणु
		.name = QCAUART_DRV_NAME,
		.of_match_table = of_match_ptr(qca_uart_of_match),
	पूर्ण,
पूर्ण;

module_serdev_device_driver(qca_uart_driver);

MODULE_DESCRIPTION("Qualcomm Atheros QCA7000 UART Driver");
MODULE_AUTHOR("Qualcomm Atheros Communications");
MODULE_AUTHOR("Stefan Wahren <stefan.wahren@i2se.com>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(QCAUART_DRV_VERSION);
