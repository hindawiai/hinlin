<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#समावेश <linux/hardirq.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/tty.h>
#समावेश <linux/file.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/caअगर/caअगर_device.h>
#समावेश <net/caअगर/cfcnfg.h>
#समावेश <linux/err.h>
#समावेश <linux/debugfs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sjur Brendeland");
MODULE_DESCRIPTION("CAIF serial device TTY line discipline");
MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_CAIF);

#घोषणा SEND_QUEUE_LOW 10
#घोषणा SEND_QUEUE_HIGH 100
#घोषणा CAIF_SENDING	        1 /* Bit 1 = 0x02*/
#घोषणा CAIF_FLOW_OFF_SENT	4 /* Bit 4 = 0x10 */
#घोषणा MAX_WRITE_CHUNK	     4096
#घोषणा ON 1
#घोषणा OFF 0
#घोषणा CAIF_MAX_MTU 4096

अटल DEFINE_SPINLOCK(ser_lock);
अटल LIST_HEAD(ser_list);
अटल LIST_HEAD(ser_release_list);

अटल bool ser_loop;
module_param(ser_loop, bool, 0444);
MODULE_PARM_DESC(ser_loop, "Run in simulated loopback mode.");

अटल bool ser_use_stx = true;
module_param(ser_use_stx, bool, 0444);
MODULE_PARM_DESC(ser_use_stx, "STX enabled or not.");

अटल bool ser_use_fcs = true;

module_param(ser_use_fcs, bool, 0444);
MODULE_PARM_DESC(ser_use_fcs, "FCS enabled or not.");

अटल पूर्णांक ser_ग_लिखो_chunk = MAX_WRITE_CHUNK;
module_param(ser_ग_लिखो_chunk, पूर्णांक, 0444);

MODULE_PARM_DESC(ser_ग_लिखो_chunk, "Maximum size of data written to UART.");

अटल काष्ठा dentry *debugfsdir;

अटल पूर्णांक caअगर_net_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक caअगर_net_बंद(काष्ठा net_device *dev);

काष्ठा ser_device अणु
	काष्ठा caअगर_dev_common common;
	काष्ठा list_head node;
	काष्ठा net_device *dev;
	काष्ठा sk_buff_head head;
	काष्ठा tty_काष्ठा *tty;
	bool tx_started;
	अचिन्हित दीर्घ state;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_tty_dir;
	काष्ठा debugfs_blob_wrapper tx_blob;
	काष्ठा debugfs_blob_wrapper rx_blob;
	u8 rx_data[128];
	u8 tx_data[128];
	u8 tty_status;

#पूर्ण_अगर
पूर्ण;

अटल व्योम caअगरdev_setup(काष्ठा net_device *dev);
अटल व्योम ldisc_tx_wakeup(काष्ठा tty_काष्ठा *tty);
#अगर_घोषित CONFIG_DEBUG_FS
अटल अंतरभूत व्योम update_tty_status(काष्ठा ser_device *ser)
अणु
	ser->tty_status =
		ser->tty->stopped << 5 |
		ser->tty->flow_stopped << 3 |
		ser->tty->packet << 2;
पूर्ण
अटल अंतरभूत व्योम debugfs_init(काष्ठा ser_device *ser, काष्ठा tty_काष्ठा *tty)
अणु
	ser->debugfs_tty_dir = debugfs_create_dir(tty->name, debugfsdir);

	debugfs_create_blob("last_tx_msg", 0400, ser->debugfs_tty_dir,
			    &ser->tx_blob);

	debugfs_create_blob("last_rx_msg", 0400, ser->debugfs_tty_dir,
			    &ser->rx_blob);

	debugfs_create_xul("ser_state", 0400, ser->debugfs_tty_dir,
			   &ser->state);

	debugfs_create_x8("tty_status", 0400, ser->debugfs_tty_dir,
			  &ser->tty_status);

	ser->tx_blob.data = ser->tx_data;
	ser->tx_blob.size = 0;
	ser->rx_blob.data = ser->rx_data;
	ser->rx_blob.size = 0;
पूर्ण

अटल अंतरभूत व्योम debugfs_deinit(काष्ठा ser_device *ser)
अणु
	debugfs_हटाओ_recursive(ser->debugfs_tty_dir);
पूर्ण

अटल अंतरभूत व्योम debugfs_rx(काष्ठा ser_device *ser, स्थिर u8 *data, पूर्णांक size)
अणु
	अगर (size > माप(ser->rx_data))
		size = माप(ser->rx_data);
	स_नकल(ser->rx_data, data, size);
	ser->rx_blob.data = ser->rx_data;
	ser->rx_blob.size = size;
पूर्ण

अटल अंतरभूत व्योम debugfs_tx(काष्ठा ser_device *ser, स्थिर u8 *data, पूर्णांक size)
अणु
	अगर (size > माप(ser->tx_data))
		size = माप(ser->tx_data);
	स_नकल(ser->tx_data, data, size);
	ser->tx_blob.data = ser->tx_data;
	ser->tx_blob.size = size;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम debugfs_init(काष्ठा ser_device *ser, काष्ठा tty_काष्ठा *tty)
अणु
पूर्ण

अटल अंतरभूत व्योम debugfs_deinit(काष्ठा ser_device *ser)
अणु
पूर्ण

अटल अंतरभूत व्योम update_tty_status(काष्ठा ser_device *ser)
अणु
पूर्ण

अटल अंतरभूत व्योम debugfs_rx(काष्ठा ser_device *ser, स्थिर u8 *data, पूर्णांक size)
अणु
पूर्ण

अटल अंतरभूत व्योम debugfs_tx(काष्ठा ser_device *ser, स्थिर u8 *data, पूर्णांक size)
अणु
पूर्ण

#पूर्ण_अगर

अटल व्योम ldisc_receive(काष्ठा tty_काष्ठा *tty, स्थिर u8 *data,
			अक्षर *flags, पूर्णांक count)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा ser_device *ser;
	पूर्णांक ret;

	ser = tty->disc_data;

	/*
	 * NOTE: flags may contain inक्रमmation about अवरोध or overrun.
	 * This is not yet handled.
	 */


	/*
	 * Workaround क्रम garbage at start of transmission,
	 * only enable अगर STX handling is not enabled.
	 */
	अगर (!ser->common.use_stx && !ser->tx_started) अणु
		dev_info(&ser->dev->dev,
			"Bytes received before initial transmission -"
			"bytes discarded.\n");
		वापस;
	पूर्ण

	BUG_ON(ser->dev == शून्य);

	/* Get a suitable caअगर packet and copy in data. */
	skb = netdev_alloc_skb(ser->dev, count+1);
	अगर (skb == शून्य)
		वापस;
	skb_put_data(skb, data, count);

	skb->protocol = htons(ETH_P_CAIF);
	skb_reset_mac_header(skb);
	debugfs_rx(ser, data, count);
	/* Push received packet up the stack. */
	ret = netअगर_rx_ni(skb);
	अगर (!ret) अणु
		ser->dev->stats.rx_packets++;
		ser->dev->stats.rx_bytes += count;
	पूर्ण अन्यथा
		++ser->dev->stats.rx_dropped;
	update_tty_status(ser);
पूर्ण

अटल पूर्णांक handle_tx(काष्ठा ser_device *ser)
अणु
	काष्ठा tty_काष्ठा *tty;
	काष्ठा sk_buff *skb;
	पूर्णांक tty_wr, len, room;

	tty = ser->tty;
	ser->tx_started = true;

	/* Enter critical section */
	अगर (test_and_set_bit(CAIF_SENDING, &ser->state))
		वापस 0;

	/* skb_peek is safe because handle_tx is called after skb_queue_tail */
	जबतक ((skb = skb_peek(&ser->head)) != शून्य) अणु

		/* Make sure you करोn't ग_लिखो too much */
		len = skb->len;
		room = tty_ग_लिखो_room(tty);
		अगर (!room)
			अवरोध;
		अगर (room > ser_ग_लिखो_chunk)
			room = ser_ग_लिखो_chunk;
		अगर (len > room)
			len = room;

		/* Write to tty or loopback */
		अगर (!ser_loop) अणु
			tty_wr = tty->ops->ग_लिखो(tty, skb->data, len);
			update_tty_status(ser);
		पूर्ण अन्यथा अणु
			tty_wr = len;
			ldisc_receive(tty, skb->data, शून्य, len);
		पूर्ण
		ser->dev->stats.tx_packets++;
		ser->dev->stats.tx_bytes += tty_wr;

		/* Error on TTY ?! */
		अगर (tty_wr < 0)
			जाओ error;
		/* Reduce buffer written, and discard अगर empty */
		skb_pull(skb, tty_wr);
		अगर (skb->len == 0) अणु
			काष्ठा sk_buff *पंचांगp = skb_dequeue(&ser->head);
			WARN_ON(पंचांगp != skb);
			dev_consume_skb_any(skb);
		पूर्ण
	पूर्ण
	/* Send flow off अगर queue is empty */
	अगर (ser->head.qlen <= SEND_QUEUE_LOW &&
		test_and_clear_bit(CAIF_FLOW_OFF_SENT, &ser->state) &&
		ser->common.flowctrl != शून्य)
				ser->common.flowctrl(ser->dev, ON);
	clear_bit(CAIF_SENDING, &ser->state);
	वापस 0;
error:
	clear_bit(CAIF_SENDING, &ser->state);
	वापस tty_wr;
पूर्ण

अटल netdev_tx_t caअगर_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ser_device *ser;

	ser = netdev_priv(dev);

	/* Send flow off once, on high water mark */
	अगर (ser->head.qlen > SEND_QUEUE_HIGH &&
		!test_and_set_bit(CAIF_FLOW_OFF_SENT, &ser->state) &&
		ser->common.flowctrl != शून्य)

		ser->common.flowctrl(ser->dev, OFF);

	skb_queue_tail(&ser->head, skb);
	वापस handle_tx(ser);
पूर्ण


अटल व्योम ldisc_tx_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ser_device *ser;

	ser = tty->disc_data;
	BUG_ON(ser == शून्य);
	WARN_ON(ser->tty != tty);
	handle_tx(ser);
पूर्ण


अटल व्योम ser_release(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा list_head list;
	काष्ठा ser_device *ser, *पंचांगp;

	spin_lock(&ser_lock);
	list_replace_init(&ser_release_list, &list);
	spin_unlock(&ser_lock);

	अगर (!list_empty(&list)) अणु
		rtnl_lock();
		list_क्रम_each_entry_safe(ser, पंचांगp, &list, node) अणु
			dev_बंद(ser->dev);
			unरेजिस्टर_netdevice(ser->dev);
			debugfs_deinit(ser);
		पूर्ण
		rtnl_unlock();
	पूर्ण
पूर्ण

अटल DECLARE_WORK(ser_release_work, ser_release);

अटल पूर्णांक ldisc_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ser_device *ser;
	काष्ठा net_device *dev;
	अक्षर name[64];
	पूर्णांक result;

	/* No ग_लिखो no play */
	अगर (tty->ops->ग_लिखो == शून्य)
		वापस -EOPNOTSUPP;
	अगर (!capable(CAP_SYS_ADMIN) && !capable(CAP_SYS_TTY_CONFIG))
		वापस -EPERM;

	/* release devices to aव्योम name collision */
	ser_release(शून्य);

	result = snम_लिखो(name, माप(name), "cf%s", tty->name);
	अगर (result >= IFNAMSIZ)
		वापस -EINVAL;
	dev = alloc_netdev(माप(*ser), name, NET_NAME_UNKNOWN,
			   caअगरdev_setup);
	अगर (!dev)
		वापस -ENOMEM;

	ser = netdev_priv(dev);
	ser->tty = tty_kref_get(tty);
	ser->dev = dev;
	debugfs_init(ser, tty);
	tty->receive_room = N_TTY_BUF_SIZE;
	tty->disc_data = ser;
	set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	rtnl_lock();
	result = रेजिस्टर_netdevice(dev);
	अगर (result) अणु
		tty_kref_put(tty);
		rtnl_unlock();
		मुक्त_netdev(dev);
		वापस -ENODEV;
	पूर्ण

	spin_lock(&ser_lock);
	list_add(&ser->node, &ser_list);
	spin_unlock(&ser_lock);
	rtnl_unlock();
	netअगर_stop_queue(dev);
	update_tty_status(ser);
	वापस 0;
पूर्ण

अटल व्योम ldisc_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ser_device *ser = tty->disc_data;

	tty_kref_put(ser->tty);

	spin_lock(&ser_lock);
	list_move(&ser->node, &ser_release_list);
	spin_unlock(&ser_lock);
	schedule_work(&ser_release_work);
पूर्ण

/* The line discipline काष्ठाure. */
अटल काष्ठा tty_ldisc_ops caअगर_ldisc = अणु
	.owner =	THIS_MODULE,
	.name =		"n_caif",
	.खोलो =		ldisc_खोलो,
	.बंद =	ldisc_बंद,
	.receive_buf =	ldisc_receive,
	.ग_लिखो_wakeup =	ldisc_tx_wakeup
पूर्ण;

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो = caअगर_net_खोलो,
	.nकरो_stop = caअगर_net_बंद,
	.nकरो_start_xmit = caअगर_xmit
पूर्ण;

अटल व्योम caअगरdev_setup(काष्ठा net_device *dev)
अणु
	काष्ठा ser_device *serdev = netdev_priv(dev);

	dev->features = 0;
	dev->netdev_ops = &netdev_ops;
	dev->type = ARPHRD_CAIF;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP;
	dev->mtu = CAIF_MAX_MTU;
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->needs_मुक्त_netdev = true;
	skb_queue_head_init(&serdev->head);
	serdev->common.link_select = CAIF_LINK_LOW_LATENCY;
	serdev->common.use_frag = true;
	serdev->common.use_stx = ser_use_stx;
	serdev->common.use_fcs = ser_use_fcs;
	serdev->dev = dev;
पूर्ण


अटल पूर्णांक caअगर_net_खोलो(काष्ठा net_device *dev)
अणु
	netअगर_wake_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक caअगर_net_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __init caअगर_ser_init(व्योम)
अणु
	पूर्णांक ret;

	ret = tty_रेजिस्टर_ldisc(N_CAIF, &caअगर_ldisc);
	अगर (ret < 0)
		pr_err("cannot register CAIF ldisc=%d err=%d\n", N_CAIF, ret);

	debugfsdir = debugfs_create_dir("caif_serial", शून्य);
	वापस ret;
पूर्ण

अटल व्योम __निकास caअगर_ser_निकास(व्योम)
अणु
	spin_lock(&ser_lock);
	list_splice(&ser_list, &ser_release_list);
	spin_unlock(&ser_lock);
	ser_release(शून्य);
	cancel_work_sync(&ser_release_work);
	tty_unरेजिस्टर_ldisc(N_CAIF);
	debugfs_हटाओ_recursive(debugfsdir);
पूर्ण

module_init(caअगर_ser_init);
module_निकास(caअगर_ser_निकास);
