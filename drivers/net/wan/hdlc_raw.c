<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic HDLC support routines क्रम Linux
 * HDLC support
 *
 * Copyright (C) 1999 - 2006 Krzysztof Halasa <khc@pm.waw.pl>
 */

#समावेश <linux/त्रुटिसं.स>
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


अटल पूर्णांक raw_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr);

अटल __be16 raw_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	वापस cpu_to_be16(ETH_P_IP);
पूर्ण

अटल काष्ठा hdlc_proto proto = अणु
	.type_trans	= raw_type_trans,
	.ioctl		= raw_ioctl,
	.module		= THIS_MODULE,
पूर्ण;


अटल पूर्णांक raw_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	raw_hdlc_proto __user *raw_s = अगरr->अगरr_settings.अगरs_अगरsu.raw_hdlc;
	स्थिर माप_प्रकार size = माप(raw_hdlc_proto);
	raw_hdlc_proto new_settings;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	पूर्णांक result;

	चयन (अगरr->अगरr_settings.type) अणु
	हाल IF_GET_PROTO:
		अगर (dev_to_hdlc(dev)->proto != &proto)
			वापस -EINVAL;
		अगरr->अगरr_settings.type = IF_PROTO_HDLC;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		अगर (copy_to_user(raw_s, hdlc->state, size))
			वापस -EFAULT;
		वापस 0;

	हाल IF_PROTO_HDLC:
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
		dev->type = ARPHRD_RAWHDLC;
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
MODULE_DESCRIPTION("Raw HDLC protocol support for generic HDLC");
MODULE_LICENSE("GPL v2");
