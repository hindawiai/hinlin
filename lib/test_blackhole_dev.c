<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This module tests the blackhole_dev that is created during the
 * net subप्रणाली initialization. The test this module perक्रमms is
 * by injecting an skb पूर्णांकo the stack with skb->dev as the
 * blackhole_dev and expects kernel to behave in a sane manner
 * (in other words, *not crash*)!
 *
 * Copyright (c) 2018, Mahesh Bandewar <maheshb@google.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/udp.h>
#समावेश <linux/ipv6.h>

#समावेश <net/dst.h>

#घोषणा SKB_SIZE  256
#घोषणा HEAD_SIZE (14+40+8)	/* Ether + IPv6 + UDP */
#घोषणा TAIL_SIZE 32		/* अक्रमom tail-room */

#घोषणा UDP_PORT 1234

अटल पूर्णांक __init test_blackholedev_init(व्योम)
अणु
	काष्ठा ipv6hdr *ip6h;
	काष्ठा sk_buff *skb;
	काष्ठा ethhdr *ethh;
	काष्ठा udphdr *uh;
	पूर्णांक data_len;
	पूर्णांक ret;

	skb = alloc_skb(SKB_SIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	/* Reserve head-room क्रम the headers */
	skb_reserve(skb, HEAD_SIZE);

	/* Add data to the skb */
	data_len = SKB_SIZE - (HEAD_SIZE + TAIL_SIZE);
	स_रखो(__skb_put(skb, data_len), 0xf, data_len);

	/* Add protocol data */
	/* (Transport) UDP */
	uh = (काष्ठा udphdr *)skb_push(skb, माप(काष्ठा udphdr));
	skb_set_transport_header(skb, 0);
	uh->source = uh->dest = htons(UDP_PORT);
	uh->len = htons(data_len);
	uh->check = 0;
	/* (Network) IPv6 */
	ip6h = (काष्ठा ipv6hdr *)skb_push(skb, माप(काष्ठा ipv6hdr));
	skb_set_network_header(skb, 0);
	ip6h->hop_limit = 32;
	ip6h->payload_len = data_len + माप(काष्ठा udphdr);
	ip6h->nexthdr = IPPROTO_UDP;
	ip6h->saddr = in6addr_loopback;
	ip6h->daddr = in6addr_loopback;
	/* Ether */
	ethh = (काष्ठा ethhdr *)skb_push(skb, माप(काष्ठा ethhdr));
	skb_set_mac_header(skb, 0);

	skb->protocol = htons(ETH_P_IPV6);
	skb->pkt_type = PACKET_HOST;
	skb->dev = blackhole_netdev;

	/* Now attempt to send the packet */
	ret = dev_queue_xmit(skb);

	चयन (ret) अणु
	हाल NET_XMIT_SUCCESS:
		pr_warn("dev_queue_xmit() returned NET_XMIT_SUCCESS\n");
		अवरोध;
	हाल NET_XMIT_DROP:
		pr_warn("dev_queue_xmit() returned NET_XMIT_DROP\n");
		अवरोध;
	हाल NET_XMIT_CN:
		pr_warn("dev_queue_xmit() returned NET_XMIT_CN\n");
		अवरोध;
	शेष:
		pr_err("dev_queue_xmit() returned UNKNOWN(%d)\n", ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास test_blackholedev_निकास(व्योम)
अणु
	pr_warn("test_blackholedev module terminating.\n");
पूर्ण

module_init(test_blackholedev_init);
module_निकास(test_blackholedev_निकास);

MODULE_AUTHOR("Mahesh Bandewar <maheshb@google.com>");
MODULE_LICENSE("GPL");
