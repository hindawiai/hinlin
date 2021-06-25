<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic HDLC support routines क्रम Linux
 * X.25 support
 *
 * Copyright (C) 1999 - 2006 Krzysztof Halasa <khc@pm.waw.pl>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/lapb.h>
#समावेश <linux/module.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/poll.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <net/x25device.h>

काष्ठा x25_state अणु
	x25_hdlc_proto settings;
	bool up;
	spinlock_t up_lock; /* Protects "up" */
	काष्ठा sk_buff_head rx_queue;
	काष्ठा tasklet_काष्ठा rx_tasklet;
पूर्ण;

अटल पूर्णांक x25_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr);

अटल काष्ठा x25_state *state(hdlc_device *hdlc)
अणु
	वापस hdlc->state;
पूर्ण

अटल व्योम x25_rx_queue_kick(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा x25_state *x25st = from_tasklet(x25st, t, rx_tasklet);
	काष्ठा sk_buff *skb = skb_dequeue(&x25st->rx_queue);

	जबतक (skb) अणु
		netअगर_receive_skb_core(skb);
		skb = skb_dequeue(&x25st->rx_queue);
	पूर्ण
पूर्ण

/* These functions are callbacks called by LAPB layer */

अटल व्योम x25_connect_disconnect(काष्ठा net_device *dev, पूर्णांक reason, पूर्णांक code)
अणु
	काष्ठा x25_state *x25st = state(dev_to_hdlc(dev));
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *ptr;

	skb = __dev_alloc_skb(1, GFP_ATOMIC | __GFP_NOMEMALLOC);
	अगर (!skb) अणु
		netdev_err(dev, "out of memory\n");
		वापस;
	पूर्ण

	ptr = skb_put(skb, 1);
	*ptr = code;

	skb->protocol = x25_type_trans(skb, dev);

	skb_queue_tail(&x25st->rx_queue, skb);
	tasklet_schedule(&x25st->rx_tasklet);
पूर्ण



अटल व्योम x25_connected(काष्ठा net_device *dev, पूर्णांक reason)
अणु
	x25_connect_disconnect(dev, reason, X25_IFACE_CONNECT);
पूर्ण



अटल व्योम x25_disconnected(काष्ठा net_device *dev, पूर्णांक reason)
अणु
	x25_connect_disconnect(dev, reason, X25_IFACE_DISCONNECT);
पूर्ण



अटल पूर्णांक x25_data_indication(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा x25_state *x25st = state(dev_to_hdlc(dev));
	अचिन्हित अक्षर *ptr;

	अगर (skb_cow(skb, 1)) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	skb_push(skb, 1);

	ptr  = skb->data;
	*ptr = X25_IFACE_DATA;

	skb->protocol = x25_type_trans(skb, dev);

	skb_queue_tail(&x25st->rx_queue, skb);
	tasklet_schedule(&x25st->rx_tasklet);
	वापस NET_RX_SUCCESS;
पूर्ण



अटल व्योम x25_data_transmit(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);

	skb_reset_network_header(skb);
	skb->protocol = hdlc_type_trans(skb, dev);

	अगर (dev_nit_active(dev))
		dev_queue_xmit_nit(skb, dev);

	hdlc->xmit(skb, dev); /* Ignore वापस value :-( */
पूर्ण



अटल netdev_tx_t x25_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा x25_state *x25st = state(hdlc);
	पूर्णांक result;

	/* There should be a pseuकरो header of 1 byte added by upper layers.
	 * Check to make sure it is there beक्रमe पढ़ोing it.
	 */
	अगर (skb->len < 1) अणु
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	spin_lock_bh(&x25st->up_lock);
	अगर (!x25st->up) अणु
		spin_unlock_bh(&x25st->up_lock);
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	चयन (skb->data[0]) अणु
	हाल X25_IFACE_DATA:	/* Data to be transmitted */
		skb_pull(skb, 1);
		अगर ((result = lapb_data_request(dev, skb)) != LAPB_OK)
			dev_kमुक्त_skb(skb);
		spin_unlock_bh(&x25st->up_lock);
		वापस NETDEV_TX_OK;

	हाल X25_IFACE_CONNECT:
		अगर ((result = lapb_connect_request(dev))!= LAPB_OK) अणु
			अगर (result == LAPB_CONNECTED)
				/* Send connect confirm. msg to level 3 */
				x25_connected(dev, 0);
			अन्यथा
				netdev_err(dev, "LAPB connect request failed, error code = %i\n",
					   result);
		पूर्ण
		अवरोध;

	हाल X25_IFACE_DISCONNECT:
		अगर ((result = lapb_disconnect_request(dev)) != LAPB_OK) अणु
			अगर (result == LAPB_NOTCONNECTED)
				/* Send disconnect confirm. msg to level 3 */
				x25_disconnected(dev, 0);
			अन्यथा
				netdev_err(dev, "LAPB disconnect request failed, error code = %i\n",
					   result);
		पूर्ण
		अवरोध;

	शेष:		/* to be defined */
		अवरोध;
	पूर्ण

	spin_unlock_bh(&x25st->up_lock);
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण



अटल पूर्णांक x25_खोलो(काष्ठा net_device *dev)
अणु
	अटल स्थिर काष्ठा lapb_रेजिस्टर_काष्ठा cb = अणु
		.connect_confirmation = x25_connected,
		.connect_indication = x25_connected,
		.disconnect_confirmation = x25_disconnected,
		.disconnect_indication = x25_disconnected,
		.data_indication = x25_data_indication,
		.data_transmit = x25_data_transmit,
	पूर्ण;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा x25_state *x25st = state(hdlc);
	काष्ठा lapb_parms_काष्ठा params;
	पूर्णांक result;

	result = lapb_रेजिस्टर(dev, &cb);
	अगर (result != LAPB_OK)
		वापस -ENOMEM;

	result = lapb_getparms(dev, &params);
	अगर (result != LAPB_OK)
		वापस -EINVAL;

	अगर (state(hdlc)->settings.dce)
		params.mode = params.mode | LAPB_DCE;

	अगर (state(hdlc)->settings.modulo == 128)
		params.mode = params.mode | LAPB_EXTENDED;

	params.winकरोw = state(hdlc)->settings.winकरोw;
	params.t1 = state(hdlc)->settings.t1;
	params.t2 = state(hdlc)->settings.t2;
	params.n2 = state(hdlc)->settings.n2;

	result = lapb_setparms(dev, &params);
	अगर (result != LAPB_OK)
		वापस -EINVAL;

	spin_lock_bh(&x25st->up_lock);
	x25st->up = true;
	spin_unlock_bh(&x25st->up_lock);

	वापस 0;
पूर्ण



अटल व्योम x25_बंद(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा x25_state *x25st = state(hdlc);

	spin_lock_bh(&x25st->up_lock);
	x25st->up = false;
	spin_unlock_bh(&x25st->up_lock);

	lapb_unरेजिस्टर(dev);
	tasklet_समाप्त(&x25st->rx_tasklet);
पूर्ण



अटल पूर्णांक x25_rx(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा x25_state *x25st = state(hdlc);

	अगर ((skb = skb_share_check(skb, GFP_ATOMIC)) == शून्य) अणु
		dev->stats.rx_dropped++;
		वापस NET_RX_DROP;
	पूर्ण

	spin_lock_bh(&x25st->up_lock);
	अगर (!x25st->up) अणु
		spin_unlock_bh(&x25st->up_lock);
		kमुक्त_skb(skb);
		dev->stats.rx_dropped++;
		वापस NET_RX_DROP;
	पूर्ण

	अगर (lapb_data_received(dev, skb) == LAPB_OK) अणु
		spin_unlock_bh(&x25st->up_lock);
		वापस NET_RX_SUCCESS;
	पूर्ण

	spin_unlock_bh(&x25st->up_lock);
	dev->stats.rx_errors++;
	dev_kमुक्त_skb_any(skb);
	वापस NET_RX_DROP;
पूर्ण


अटल काष्ठा hdlc_proto proto = अणु
	.खोलो		= x25_खोलो,
	.बंद		= x25_बंद,
	.ioctl		= x25_ioctl,
	.netअगर_rx	= x25_rx,
	.xmit		= x25_xmit,
	.module		= THIS_MODULE,
पूर्ण;


अटल पूर्णांक x25_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	x25_hdlc_proto __user *x25_s = अगरr->अगरr_settings.अगरs_अगरsu.x25;
	स्थिर माप_प्रकार size = माप(x25_hdlc_proto);
	hdlc_device *hdlc = dev_to_hdlc(dev);
	x25_hdlc_proto new_settings;
	पूर्णांक result;

	चयन (अगरr->अगरr_settings.type) अणु
	हाल IF_GET_PROTO:
		अगर (dev_to_hdlc(dev)->proto != &proto)
			वापस -EINVAL;
		अगरr->अगरr_settings.type = IF_PROTO_X25;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		अगर (copy_to_user(x25_s, &state(hdlc)->settings, size))
			वापस -EFAULT;
		वापस 0;

	हाल IF_PROTO_X25:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;

		/* backward compatibility */
		अगर (अगरr->अगरr_settings.size == 0) अणु
			new_settings.dce = 0;
			new_settings.modulo = 8;
			new_settings.winकरोw = 7;
			new_settings.t1 = 3;
			new_settings.t2 = 1;
			new_settings.n2 = 10;
		पूर्ण
		अन्यथा अणु
			अगर (copy_from_user(&new_settings, x25_s, size))
				वापस -EFAULT;

			अगर ((new_settings.dce != 0 &&
			new_settings.dce != 1) ||
			(new_settings.modulo != 8 &&
			new_settings.modulo != 128) ||
			new_settings.winकरोw < 1 ||
			(new_settings.modulo == 8 &&
			new_settings.winकरोw > 7) ||
			(new_settings.modulo == 128 &&
			new_settings.winकरोw > 127) ||
			new_settings.t1 < 1 ||
			new_settings.t1 > 255 ||
			new_settings.t2 < 1 ||
			new_settings.t2 > 255 ||
			new_settings.n2 < 1 ||
			new_settings.n2 > 255)
				वापस -EINVAL;
		पूर्ण

		result=hdlc->attach(dev, ENCODING_NRZ,PARITY_CRC16_PR1_CCITT);
		अगर (result)
			वापस result;

		अगर ((result = attach_hdlc_protocol(dev, &proto,
						   माप(काष्ठा x25_state))))
			वापस result;

		स_नकल(&state(hdlc)->settings, &new_settings, size);
		state(hdlc)->up = false;
		spin_lock_init(&state(hdlc)->up_lock);
		skb_queue_head_init(&state(hdlc)->rx_queue);
		tasklet_setup(&state(hdlc)->rx_tasklet, x25_rx_queue_kick);

		/* There's no header_ops so hard_header_len should be 0. */
		dev->hard_header_len = 0;
		/* When transmitting data:
		 * first we'll हटाओ a pseuकरो header of 1 byte,
		 * then we'll prepend an LAPB header of at most 3 bytes.
		 */
		dev->needed_headroom = 3 - 1;

		dev->type = ARPHRD_X25;
		call_netdevice_notअगरiers(NETDEV_POST_TYPE_CHANGE, dev);
		netअगर_करोrmant_off(dev);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण


अटल पूर्णांक __init mod_init(व्योम)
अणु
	रेजिस्टर_hdlc_protocol(&proto);
	वापस 0;
पूर्ण



अटल व्योम __निकास mod_निकास(व्योम)
अणु
	unरेजिस्टर_hdlc_protocol(&proto);
पूर्ण


module_init(mod_init);
module_निकास(mod_निकास);

MODULE_AUTHOR("Krzysztof Halasa <khc@pm.waw.pl>");
MODULE_DESCRIPTION("X.25 protocol support for generic HDLC");
MODULE_LICENSE("GPL v2");
