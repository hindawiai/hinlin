<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/***************************************************************************
 * Linux PPP over X - Generic PPP transport layer sockets
 * Linux PPP over Ethernet (PPPoE) Socket Implementation (RFC 2516) 
 *
 * This file supplies definitions required by the PPP over Ethernet driver
 * (pppox.c).  All version inक्रमmation wrt this file is located in pppox.c
 *
 * License:
 */
#अगर_अघोषित __LINUX_IF_PPPOX_H
#घोषणा __LINUX_IF_PPPOX_H

#समावेश <linux/अगर.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ppp_channel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/linux/अगर_pppox.h>

अटल अंतरभूत काष्ठा pppoe_hdr *pppoe_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा pppoe_hdr *)skb_network_header(skb);
पूर्ण

काष्ठा pppoe_opt अणु
	काष्ठा net_device      *dev;	  /* device associated with socket*/
	पूर्णांक			अगरindex;  /* अगरindex of device associated with socket */
	काष्ठा pppoe_addr	pa;	  /* what this socket is bound to*/
	काष्ठा sockaddr_pppox	relay;	  /* what socket data will be
					     relayed to (PPPoE relaying) */
	काष्ठा work_काष्ठा      padt_work;/* Work item क्रम handling PADT */
पूर्ण;

काष्ठा pptp_opt अणु
	काष्ठा pptp_addr src_addr;
	काष्ठा pptp_addr dst_addr;
	u32 ack_sent, ack_recv;
	u32 seq_sent, seq_recv;
	पूर्णांक ppp_flags;
पूर्ण;
#समावेश <net/sock.h>

काष्ठा pppox_sock अणु
	/* काष्ठा sock must be the first member of pppox_sock */
	काष्ठा sock sk;
	काष्ठा ppp_channel chan;
	काष्ठा pppox_sock	*next;	  /* क्रम hash table */
	जोड़ अणु
		काष्ठा pppoe_opt pppoe;
		काष्ठा pptp_opt  pptp;
	पूर्ण proto;
	__be16			num;
पूर्ण;
#घोषणा pppoe_dev	proto.pppoe.dev
#घोषणा pppoe_अगरindex	proto.pppoe.अगरindex
#घोषणा pppoe_pa	proto.pppoe.pa
#घोषणा pppoe_relay	proto.pppoe.relay

अटल अंतरभूत काष्ठा pppox_sock *pppox_sk(काष्ठा sock *sk)
अणु
	वापस (काष्ठा pppox_sock *)sk;
पूर्ण

अटल अंतरभूत काष्ठा sock *sk_pppox(काष्ठा pppox_sock *po)
अणु
	वापस (काष्ठा sock *)po;
पूर्ण

काष्ठा module;

काष्ठा pppox_proto अणु
	पूर्णांक		(*create)(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक kern);
	पूर्णांक		(*ioctl)(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg);
	काष्ठा module	*owner;
पूर्ण;

बाह्य पूर्णांक रेजिस्टर_pppox_proto(पूर्णांक proto_num, स्थिर काष्ठा pppox_proto *pp);
बाह्य व्योम unरेजिस्टर_pppox_proto(पूर्णांक proto_num);
बाह्य व्योम pppox_unbind_sock(काष्ठा sock *sk);/* delete ppp-channel binding */
बाह्य पूर्णांक pppox_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
बाह्य पूर्णांक pppox_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

#घोषणा PPPOEIOCSFWD32    _IOW(0xB1 ,0, compat_माप_प्रकार)

/* PPPoX socket states */
क्रमागत अणु
    PPPOX_NONE		= 0,  /* initial state */
    PPPOX_CONNECTED	= 1,  /* connection established ==TCP_ESTABLISHED */
    PPPOX_BOUND		= 2,  /* bound to ppp device */
    PPPOX_RELAY		= 4,  /* क्रमwarding is enabled */
    PPPOX_DEAD		= 16  /* dead, useless, please clean me up!*/
पूर्ण;

#पूर्ण_अगर /* !(__LINUX_IF_PPPOX_H) */
