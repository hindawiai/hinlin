<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Global definitions क्रम the Ethernet IEEE 802.3 पूर्णांकerface.
 *
 * Version:	@(#)अगर_ether.h	1.0.1a	02/08/94
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Donald Becker, <becker@super.org>
 *		Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *		Steve Whitehouse, <gw7rrm@eeshack3.swan.ac.uk>
 */
#अगर_अघोषित _LINUX_IF_ETHER_H
#घोषणा _LINUX_IF_ETHER_H

#समावेश <linux/skbuff.h>
#समावेश <uapi/linux/अगर_ether.h>

अटल अंतरभूत काष्ठा ethhdr *eth_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ethhdr *)skb_mac_header(skb);
पूर्ण

/* Prefer this version in TX path, instead of
 * skb_reset_mac_header() + eth_hdr()
 */
अटल अंतरभूत काष्ठा ethhdr *skb_eth_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ethhdr *)skb->data;
पूर्ण

अटल अंतरभूत काष्ठा ethhdr *inner_eth_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ethhdr *)skb_inner_mac_header(skb);
पूर्ण

पूर्णांक eth_header_parse(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर *haddr);

बाह्य sमाप_प्रकार sysfs_क्रमmat_mac(अक्षर *buf, स्थिर अचिन्हित अक्षर *addr, पूर्णांक len);

#पूर्ण_अगर	/* _LINUX_IF_ETHER_H */
