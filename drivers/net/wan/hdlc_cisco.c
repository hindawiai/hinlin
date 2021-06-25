<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic HDLC support routines क्रम Linux
 * Cisco HDLC support
 *
 * Copyright (C) 2000 - 2006 Krzysztof Halasa <khc@pm.waw.pl>
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

#अघोषित DEBUG_HARD_HEADER

#घोषणा CISCO_MULTICAST		0x8F	/* Cisco multicast address */
#घोषणा CISCO_UNICAST		0x0F	/* Cisco unicast address */
#घोषणा CISCO_KEEPALIVE		0x8035	/* Cisco keepalive protocol */
#घोषणा CISCO_SYS_INFO		0x2000	/* Cisco पूर्णांकerface/प्रणाली info */
#घोषणा CISCO_ADDR_REQ		0	/* Cisco address request */
#घोषणा CISCO_ADDR_REPLY	1	/* Cisco address reply */
#घोषणा CISCO_KEEPALIVE_REQ	2	/* Cisco keepalive request */


काष्ठा hdlc_header अणु
	u8 address;
	u8 control;
	__be16 protocol;
पूर्ण__packed;


काष्ठा cisco_packet अणु
	__be32 type;		/* code */
	__be32 par1;
	__be32 par2;
	__be16 rel;		/* reliability */
	__be32 समय;
पूर्ण__packed;
#घोषणा	CISCO_PACKET_LEN	18
#घोषणा	CISCO_BIG_PACKET_LEN	20


काष्ठा cisco_state अणु
	cisco_proto settings;

	काष्ठा समयr_list समयr;
	काष्ठा net_device *dev;
	spinlock_t lock;
	अचिन्हित दीर्घ last_poll;
	पूर्णांक up;
	u32 txseq; /* TX sequence number, 0 = none */
	u32 rxseq; /* RX sequence number */
पूर्ण;


अटल पूर्णांक cisco_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr);


अटल अंतरभूत काष्ठा cisco_state* state(hdlc_device *hdlc)
अणु
	वापस (काष्ठा cisco_state *)hdlc->state;
पूर्ण


अटल पूर्णांक cisco_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			     u16 type, स्थिर व्योम *daddr, स्थिर व्योम *saddr,
			     अचिन्हित पूर्णांक len)
अणु
	काष्ठा hdlc_header *data;
#अगर_घोषित DEBUG_HARD_HEADER
	netdev_dbg(dev, "%s called\n", __func__);
#पूर्ण_अगर

	skb_push(skb, माप(काष्ठा hdlc_header));
	data = (काष्ठा hdlc_header*)skb->data;
	अगर (type == CISCO_KEEPALIVE)
		data->address = CISCO_MULTICAST;
	अन्यथा
		data->address = CISCO_UNICAST;
	data->control = 0;
	data->protocol = htons(type);

	वापस माप(काष्ठा hdlc_header);
पूर्ण



अटल व्योम cisco_keepalive_send(काष्ठा net_device *dev, u32 type,
				 __be32 par1, __be32 par2)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cisco_packet *data;

	skb = dev_alloc_skb(माप(काष्ठा hdlc_header) +
			    माप(काष्ठा cisco_packet));
	अगर (!skb) अणु
		netdev_warn(dev, "Memory squeeze on %s()\n", __func__);
		वापस;
	पूर्ण
	skb_reserve(skb, 4);
	cisco_hard_header(skb, dev, CISCO_KEEPALIVE, शून्य, शून्य, 0);
	data = (काष्ठा cisco_packet*)(skb->data + 4);

	data->type = htonl(type);
	data->par1 = par1;
	data->par2 = par2;
	data->rel = cpu_to_be16(0xFFFF);
	/* we will need करो_भाग here अगर 1000 % HZ != 0 */
	data->समय = htonl((jअगरfies - INITIAL_JIFFIES) * (1000 / HZ));

	skb_put(skb, माप(काष्ठा cisco_packet));
	skb->priority = TC_PRIO_CONTROL;
	skb->dev = dev;
	skb->protocol = htons(ETH_P_HDLC);
	skb_reset_network_header(skb);

	dev_queue_xmit(skb);
पूर्ण



अटल __be16 cisco_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा hdlc_header *data = (काष्ठा hdlc_header*)skb->data;

	अगर (skb->len < माप(काष्ठा hdlc_header))
		वापस cpu_to_be16(ETH_P_HDLC);

	अगर (data->address != CISCO_MULTICAST &&
	    data->address != CISCO_UNICAST)
		वापस cpu_to_be16(ETH_P_HDLC);

	चयन (data->protocol) अणु
	हाल cpu_to_be16(ETH_P_IP):
	हाल cpu_to_be16(ETH_P_IPX):
	हाल cpu_to_be16(ETH_P_IPV6):
		skb_pull(skb, माप(काष्ठा hdlc_header));
		वापस data->protocol;
	शेष:
		वापस cpu_to_be16(ETH_P_HDLC);
	पूर्ण
पूर्ण


अटल पूर्णांक cisco_rx(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा cisco_state *st = state(hdlc);
	काष्ठा hdlc_header *data = (काष्ठा hdlc_header*)skb->data;
	काष्ठा cisco_packet *cisco_data;
	काष्ठा in_device *in_dev;
	__be32 addr, mask;
	u32 ack;

	अगर (skb->len < माप(काष्ठा hdlc_header))
		जाओ rx_error;

	अगर (data->address != CISCO_MULTICAST &&
	    data->address != CISCO_UNICAST)
		जाओ rx_error;

	चयन (ntohs(data->protocol)) अणु
	हाल CISCO_SYS_INFO:
		/* Packet is not needed, drop it. */
		dev_kमुक्त_skb_any(skb);
		वापस NET_RX_SUCCESS;

	हाल CISCO_KEEPALIVE:
		अगर ((skb->len != माप(काष्ठा hdlc_header) +
		     CISCO_PACKET_LEN) &&
		    (skb->len != माप(काष्ठा hdlc_header) +
		     CISCO_BIG_PACKET_LEN)) अणु
			netdev_info(dev, "Invalid length of Cisco control packet (%d bytes)\n",
				    skb->len);
			जाओ rx_error;
		पूर्ण

		cisco_data = (काष्ठा cisco_packet*)(skb->data + माप
						    (काष्ठा hdlc_header));

		चयन (ntohl (cisco_data->type)) अणु
		हाल CISCO_ADDR_REQ: /* Stolen from syncppp.c :-) */
			rcu_पढ़ो_lock();
			in_dev = __in_dev_get_rcu(dev);
			addr = 0;
			mask = ~cpu_to_be32(0); /* is the mask correct? */

			अगर (in_dev != शून्य) अणु
				स्थिर काष्ठा in_अगरaddr *अगरa;

				in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
					अगर (म_भेद(dev->name,
						   अगरa->अगरa_label) == 0) अणु
						addr = अगरa->अगरa_local;
						mask = अगरa->अगरa_mask;
						अवरोध;
					पूर्ण
				पूर्ण

				cisco_keepalive_send(dev, CISCO_ADDR_REPLY,
						     addr, mask);
			पूर्ण
			rcu_पढ़ो_unlock();
			dev_kमुक्त_skb_any(skb);
			वापस NET_RX_SUCCESS;

		हाल CISCO_ADDR_REPLY:
			netdev_info(dev, "Unexpected Cisco IP address reply\n");
			जाओ rx_error;

		हाल CISCO_KEEPALIVE_REQ:
			spin_lock(&st->lock);
			st->rxseq = ntohl(cisco_data->par1);
			ack = ntohl(cisco_data->par2);
			अगर (ack && (ack == st->txseq ||
				    /* our current REQ may be in transit */
				    ack == st->txseq - 1)) अणु
				st->last_poll = jअगरfies;
				अगर (!st->up) अणु
					u32 sec, min, hrs, days;
					sec = ntohl(cisco_data->समय) / 1000;
					min = sec / 60; sec -= min * 60;
					hrs = min / 60; min -= hrs * 60;
					days = hrs / 24; hrs -= days * 24;
					netdev_info(dev, "Link up (peer uptime %ud%uh%um%us)\n",
						    days, hrs, min, sec);
					netअगर_करोrmant_off(dev);
					st->up = 1;
				पूर्ण
			पूर्ण
			spin_unlock(&st->lock);

			dev_kमुक्त_skb_any(skb);
			वापस NET_RX_SUCCESS;
		पूर्ण /* चयन (keepalive type) */
	पूर्ण /* चयन (protocol) */

	netdev_info(dev, "Unsupported protocol %x\n", ntohs(data->protocol));
	dev_kमुक्त_skb_any(skb);
	वापस NET_RX_DROP;

rx_error:
	dev->stats.rx_errors++; /* Mark error */
	dev_kमुक्त_skb_any(skb);
	वापस NET_RX_DROP;
पूर्ण



अटल व्योम cisco_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा cisco_state *st = from_समयr(st, t, समयr);
	काष्ठा net_device *dev = st->dev;

	spin_lock(&st->lock);
	अगर (st->up &&
	    समय_after(jअगरfies, st->last_poll + st->settings.समयout * HZ)) अणु
		st->up = 0;
		netdev_info(dev, "Link down\n");
		netअगर_करोrmant_on(dev);
	पूर्ण

	cisco_keepalive_send(dev, CISCO_KEEPALIVE_REQ, htonl(++st->txseq),
			     htonl(st->rxseq));
	spin_unlock(&st->lock);

	st->समयr.expires = jअगरfies + st->settings.पूर्णांकerval * HZ;
	add_समयr(&st->समयr);
पूर्ण



अटल व्योम cisco_start(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा cisco_state *st = state(hdlc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&st->lock, flags);
	st->up = st->txseq = st->rxseq = 0;
	spin_unlock_irqrestore(&st->lock, flags);

	st->dev = dev;
	समयr_setup(&st->समयr, cisco_समयr, 0);
	st->समयr.expires = jअगरfies + HZ; /* First poll after 1 s */
	add_समयr(&st->समयr);
पूर्ण



अटल व्योम cisco_stop(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा cisco_state *st = state(hdlc);
	अचिन्हित दीर्घ flags;

	del_समयr_sync(&st->समयr);

	spin_lock_irqsave(&st->lock, flags);
	netअगर_करोrmant_on(dev);
	st->up = st->txseq = 0;
	spin_unlock_irqrestore(&st->lock, flags);
पूर्ण


अटल काष्ठा hdlc_proto proto = अणु
	.start		= cisco_start,
	.stop		= cisco_stop,
	.type_trans	= cisco_type_trans,
	.ioctl		= cisco_ioctl,
	.netअगर_rx	= cisco_rx,
	.module		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा header_ops cisco_header_ops = अणु
	.create = cisco_hard_header,
पूर्ण;

अटल पूर्णांक cisco_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	cisco_proto __user *cisco_s = अगरr->अगरr_settings.अगरs_अगरsu.cisco;
	स्थिर माप_प्रकार size = माप(cisco_proto);
	cisco_proto new_settings;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	पूर्णांक result;

	चयन (अगरr->अगरr_settings.type) अणु
	हाल IF_GET_PROTO:
		अगर (dev_to_hdlc(dev)->proto != &proto)
			वापस -EINVAL;
		अगरr->अगरr_settings.type = IF_PROTO_CISCO;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		अगर (copy_to_user(cisco_s, &state(hdlc)->settings, size))
			वापस -EFAULT;
		वापस 0;

	हाल IF_PROTO_CISCO:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;

		अगर (copy_from_user(&new_settings, cisco_s, size))
			वापस -EFAULT;

		अगर (new_settings.पूर्णांकerval < 1 ||
		    new_settings.समयout < 2)
			वापस -EINVAL;

		result = hdlc->attach(dev, ENCODING_NRZ,PARITY_CRC16_PR1_CCITT);
		अगर (result)
			वापस result;

		result = attach_hdlc_protocol(dev, &proto,
					      माप(काष्ठा cisco_state));
		अगर (result)
			वापस result;

		स_नकल(&state(hdlc)->settings, &new_settings, size);
		spin_lock_init(&state(hdlc)->lock);
		dev->header_ops = &cisco_header_ops;
		dev->hard_header_len = माप(काष्ठा hdlc_header);
		dev->type = ARPHRD_CISCO;
		call_netdevice_notअगरiers(NETDEV_POST_TYPE_CHANGE, dev);
		netअगर_करोrmant_on(dev);
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
MODULE_DESCRIPTION("Cisco HDLC protocol support for generic HDLC");
MODULE_LICENSE("GPL v2");
