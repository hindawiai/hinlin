<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Global definitions क्रम the ARP (RFC 826) protocol.
 *
 * Version:	@(#)अगर_arp.h	1.0.1	04/16/93
 *
 * Authors:	Original taken from Berkeley UNIX 4.3, (c) UCB 1986-1988
 *		Portions taken from the KA9Q/NOS (v2.00m PA0GRI) source.
 *		Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Florian La Roche,
 *		Jonathan Layes <layes@loran.com>
 *		Arnalकरो Carvalho de Melo <acme@conectiva.com.br> ARPHRD_HWX25
 */
#अगर_अघोषित _LINUX_IF_ARP_H
#घोषणा _LINUX_IF_ARP_H

#समावेश <linux/skbuff.h>
#समावेश <uapi/linux/अगर_arp.h>

अटल अंतरभूत काष्ठा arphdr *arp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा arphdr *)skb_network_header(skb);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक arp_hdr_len(स्थिर काष्ठा net_device *dev)
अणु
	चयन (dev->type) अणु
#अगर IS_ENABLED(CONFIG_FIREWIRE_NET)
	हाल ARPHRD_IEEE1394:
		/* ARP header, device address and 2 IP addresses */
		वापस माप(काष्ठा arphdr) + dev->addr_len + माप(u32) * 2;
#पूर्ण_अगर
	शेष:
		/* ARP header, plus 2 device addresses, plus 2 IP addresses. */
		वापस माप(काष्ठा arphdr) + (dev->addr_len + माप(u32)) * 2;
	पूर्ण
पूर्ण

अटल अंतरभूत bool dev_is_mac_header_xmit(स्थिर काष्ठा net_device *dev)
अणु
	चयन (dev->type) अणु
	हाल ARPHRD_TUNNEL:
	हाल ARPHRD_TUNNEL6:
	हाल ARPHRD_SIT:
	हाल ARPHRD_IPGRE:
	हाल ARPHRD_VOID:
	हाल ARPHRD_NONE:
	हाल ARPHRD_RAWIP:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

#पूर्ण_अगर	/* _LINUX_IF_ARP_H */
