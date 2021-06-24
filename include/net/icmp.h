<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the ICMP module.
 *
 * Version:	@(#)icmp.h	1.0.4	05/13/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 */
#अगर_अघोषित _ICMP_H
#घोषणा	_ICMP_H

#समावेश <linux/icmp.h>

#समावेश <net/inet_sock.h>
#समावेश <net/snmp.h>
#समावेश <net/ip.h>

काष्ठा icmp_err अणु
  पूर्णांक		त्रुटि_सं;
  अचिन्हित पूर्णांक	fatal:1;
पूर्ण;

बाह्य स्थिर काष्ठा icmp_err icmp_err_convert[];
#घोषणा ICMP_INC_STATS(net, field)	SNMP_INC_STATS((net)->mib.icmp_statistics, field)
#घोषणा __ICMP_INC_STATS(net, field)	__SNMP_INC_STATS((net)->mib.icmp_statistics, field)
#घोषणा ICMPMSGOUT_INC_STATS(net, field)	SNMP_INC_STATS_ATOMIC_LONG((net)->mib.icmpmsg_statistics, field+256)
#घोषणा ICMPMSGIN_INC_STATS(net, field)		SNMP_INC_STATS_ATOMIC_LONG((net)->mib.icmpmsg_statistics, field)

काष्ठा dst_entry;
काष्ठा net_proto_family;
काष्ठा sk_buff;
काष्ठा net;

व्योम __icmp_send(काष्ठा sk_buff *skb_in, पूर्णांक type, पूर्णांक code, __be32 info,
		 स्थिर काष्ठा ip_options *opt);
अटल अंतरभूत व्योम icmp_send(काष्ठा sk_buff *skb_in, पूर्णांक type, पूर्णांक code, __be32 info)
अणु
	__icmp_send(skb_in, type, code, info, &IPCB(skb_in)->opt);
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_NAT)
व्योम icmp_nकरो_send(काष्ठा sk_buff *skb_in, पूर्णांक type, पूर्णांक code, __be32 info);
#अन्यथा
अटल अंतरभूत व्योम icmp_nकरो_send(काष्ठा sk_buff *skb_in, पूर्णांक type, पूर्णांक code, __be32 info)
अणु
	काष्ठा ip_options opts = अणु 0 पूर्ण;
	__icmp_send(skb_in, type, code, info, &opts);
पूर्ण
#पूर्ण_अगर

पूर्णांक icmp_rcv(काष्ठा sk_buff *skb);
पूर्णांक icmp_err(काष्ठा sk_buff *skb, u32 info);
पूर्णांक icmp_init(व्योम);
व्योम icmp_out_count(काष्ठा net *net, अचिन्हित अक्षर type);

#पूर्ण_अगर	/* _ICMP_H */
