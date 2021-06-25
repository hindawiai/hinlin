<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the IP protocol.
 *
 * Version:	@(#)ip.h	1.0.2	04/28/93
 *
 * Authors:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 */
#अगर_अघोषित _LINUX_IP_H
#घोषणा _LINUX_IP_H

#समावेश <linux/skbuff.h>
#समावेश <uapi/linux/ip.h>

अटल अंतरभूत काष्ठा iphdr *ip_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा iphdr *)skb_network_header(skb);
पूर्ण

अटल अंतरभूत काष्ठा iphdr *inner_ip_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा iphdr *)skb_inner_network_header(skb);
पूर्ण

अटल अंतरभूत काष्ठा iphdr *ipip_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा iphdr *)skb_transport_header(skb);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ip_transport_len(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस ntohs(ip_hdr(skb)->tot_len) - skb_network_header_len(skb);
पूर्ण
#पूर्ण_अगर	/* _LINUX_IP_H */
