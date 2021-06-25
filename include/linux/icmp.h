<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the ICMP protocol.
 *
 * Version:	@(#)icmp.h	1.0.3	04/28/93
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 */
#अगर_अघोषित _LINUX_ICMP_H
#घोषणा	_LINUX_ICMP_H

#समावेश <linux/skbuff.h>
#समावेश <uapi/linux/icmp.h>
#समावेश <uapi/linux/errqueue.h>

अटल अंतरभूत काष्ठा icmphdr *icmp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा icmphdr *)skb_transport_header(skb);
पूर्ण

अटल अंतरभूत bool icmp_is_err(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल ICMP_DEST_UNREACH:
	हाल ICMP_SOURCE_QUENCH:
	हाल ICMP_REसूचीECT:
	हाल ICMP_TIME_EXCEEDED:
	हाल ICMP_PARAMETERPROB:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम ip_icmp_error_rfc4884(स्थिर काष्ठा sk_buff *skb,
			   काष्ठा sock_ee_data_rfc4884 *out,
			   पूर्णांक thlen, पूर्णांक off);

#पूर्ण_अगर	/* _LINUX_ICMP_H */
