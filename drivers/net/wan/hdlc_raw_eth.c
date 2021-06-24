<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic HDLC support routines क्रम Linux
 * HDLC Ethernet emulation support
 *
 * Copyright (C) 2002-2006 Krzysztof Halasa <khc@pm.waw.pl>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/poll.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>

अटल पूर्णांक raw_eth_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr);

अटल netdev_tx_t eth_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	पूर्णांक pad = ETH_ZLEN - skb->len;
	अगर (pad > 0) अणु		/* Pad the frame with zeros */
		पूर्णांक len = skb->len;
		अगर (skb_tailroom(skb) < pad)
			अगर (pskb_expand_head(skb, 0, pad, GFP_ATOMIC)) अणु
				dev->stats.tx_dropped++;
				dev_kमुक्त_skb(skb);
				वापस 0;
			पूर्ण
		skb_put(skb, pad);
		स_रखो(skb->data + len, 0, pad);
	पूर्ण
	वापस dev_to_hdlc(dev)->xmit(skb, dev);
पूर्ण


अटल काष्ठा hdlc_proto proto = अणु
	.type_trans	= eth_type_trans,
	.xmit		= eth_tx,
	.ioctl		= raw_eth_ioctl,
	.module		= THIS_MODULE,
पूर्ण;


अटल पूर्णांक raw_eth_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	raw_hdlc_proto __user *raw_s = अगरr->अगरr_settings.अगरs_अगरsu.raw_hdlc;
	स्थिर माप_प्रकार size = माप(raw_hdlc_proto);
	raw_hdlc_proto new_settings;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	अचिन्हित पूर्णांक old_qlen;
	पूर्णांक result;

	चयन (अगरr->अगरr_settings.type) अणु
	हाल IF_GET_PROTO:
		अगर (dev_to_hdlc(dev)->proto != &proto)
			वापस -EINVAL;
		अगरr->अगरr_settings.type = IF_PROTO_HDLC_ETH;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		अगर (copy_to_user(raw_s, hdlc->state, size))
			वापस -EFAULT;
		वापस 0;

	हाल IF_PROTO_HDLC_ETH:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;

		अगर (copy_from_user(&new_settings, raw_s, size))
			वापस -EFAULT;

		अगर (new_settings.encoding == ENCODING_DEFAULT)
			new_settings.encoding = ENCODING_NRZ;

		अगर (new_settings.parity == PARITY_DEFAULT)
			new_settings.parity = PARITY_CRC16_PR1_CCITT;

		result = hdlc->attach(dev, new_settings.encoding,
				      new_settings.parity);
		अगर (result)
			वापस result;

		result = attach_hdlc_protocol(dev, &proto,
					      माप(raw_hdlc_proto));
		अगर (result)
			वापस result;
		स_नकल(hdlc->state, &new_settings, size);
		old_qlen = dev->tx_queue_len;
		ether_setup(dev);
		dev->tx_queue_len = old_qlen;
		dev->priv_flags &= ~IFF_TX_SKB_SHARING;
		eth_hw_addr_अक्रमom(dev);
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
MODULE_DESCRIPTION("Ethernet encapsulation support for generic HDLC");
MODULE_LICENSE("GPL v2");
