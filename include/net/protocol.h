<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the protocol dispatcher.
 *
 * Version:	@(#)protocol.h	1.0.2	05/07/93
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *	Changes:
 *		Alan Cox	:	Added a name field and a frag handler
 *					field क्रम later.
 *		Alan Cox	:	Cleaned up, and sorted types.
 *		Pedro Roque	:	inet6 protocols
 */
 
#अगर_अघोषित _PROTOCOL_H
#घोषणा _PROTOCOL_H

#समावेश <linux/in6.h>
#समावेश <linux/skbuff.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <linux/ipv6.h>
#पूर्ण_अगर
#समावेश <linux/netdevice.h>

/* This is one larger than the largest protocol value that can be
 * found in an ipv4 or ipv6 header.  Since in both हालs the protocol
 * value is presented in a __u8, this is defined to be 256.
 */
#घोषणा MAX_INET_PROTOS		256

/* This is used to रेजिस्टर protocols. */
काष्ठा net_protocol अणु
	पूर्णांक			(*early_demux)(काष्ठा sk_buff *skb);
	पूर्णांक			(*early_demux_handler)(काष्ठा sk_buff *skb);
	पूर्णांक			(*handler)(काष्ठा sk_buff *skb);

	/* This वापसs an error अगर we weren't able to handle the error. */
	पूर्णांक			(*err_handler)(काष्ठा sk_buff *skb, u32 info);

	अचिन्हित पूर्णांक		no_policy:1,
				netns_ok:1,
				/* करोes the protocol करो more stringent
				 * icmp tag validation than simple
				 * socket lookup?
				 */
				icmp_strict_tag_validation:1;
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
काष्ठा inet6_protocol अणु
	व्योम	(*early_demux)(काष्ठा sk_buff *skb);
	व्योम    (*early_demux_handler)(काष्ठा sk_buff *skb);
	पूर्णांक	(*handler)(काष्ठा sk_buff *skb);

	/* This वापसs an error अगर we weren't able to handle the error. */
	पूर्णांक	(*err_handler)(काष्ठा sk_buff *skb,
			       काष्ठा inet6_skb_parm *opt,
			       u8 type, u8 code, पूर्णांक offset,
			       __be32 info);

	अचिन्हित पूर्णांक	flags;	/* INET6_PROTO_xxx */
पूर्ण;

#घोषणा INET6_PROTO_NOPOLICY	0x1
#घोषणा INET6_PROTO_FINAL	0x2
#पूर्ण_अगर

काष्ठा net_offload अणु
	काष्ठा offload_callbacks callbacks;
	अचिन्हित पूर्णांक		 flags;	/* Flags used by IPv6 क्रम now */
पूर्ण;
/* This should be set क्रम any extension header which is compatible with GSO. */
#घोषणा INET6_PROTO_GSO_EXTHDR	0x1

/* This is used to रेजिस्टर socket पूर्णांकerfaces क्रम IP protocols.  */
काष्ठा inet_protosw अणु
	काष्ठा list_head list;

        /* These two fields क्रमm the lookup key.  */
	अचिन्हित लघु	 type;	   /* This is the 2nd argument to socket(2). */
	अचिन्हित लघु	 protocol; /* This is the L4 protocol number.  */

	काष्ठा proto	 *prot;
	स्थिर काष्ठा proto_ops *ops;
  
	अचिन्हित अक्षर	 flags;      /* See INET_PROTOSW_* below.  */
पूर्ण;
#घोषणा INET_PROTOSW_REUSE 0x01	     /* Are ports स्वतःmatically reusable? */
#घोषणा INET_PROTOSW_PERMANENT 0x02  /* Permanent protocols are unremovable. */
#घोषणा INET_PROTOSW_ICSK      0x04  /* Is this an inet_connection_sock? */

बाह्य काष्ठा net_protocol __rcu *inet_protos[MAX_INET_PROTOS];
बाह्य स्थिर काष्ठा net_offload __rcu *inet_offloads[MAX_INET_PROTOS];
बाह्य स्थिर काष्ठा net_offload __rcu *inet6_offloads[MAX_INET_PROTOS];

#अगर IS_ENABLED(CONFIG_IPV6)
बाह्य काष्ठा inet6_protocol __rcu *inet6_protos[MAX_INET_PROTOS];
#पूर्ण_अगर

पूर्णांक inet_add_protocol(स्थिर काष्ठा net_protocol *prot, अचिन्हित अक्षर num);
पूर्णांक inet_del_protocol(स्थिर काष्ठा net_protocol *prot, अचिन्हित अक्षर num);
पूर्णांक inet_add_offload(स्थिर काष्ठा net_offload *prot, अचिन्हित अक्षर num);
पूर्णांक inet_del_offload(स्थिर काष्ठा net_offload *prot, अचिन्हित अक्षर num);
व्योम inet_रेजिस्टर_protosw(काष्ठा inet_protosw *p);
व्योम inet_unरेजिस्टर_protosw(काष्ठा inet_protosw *p);

#अगर IS_ENABLED(CONFIG_IPV6)
पूर्णांक inet6_add_protocol(स्थिर काष्ठा inet6_protocol *prot, अचिन्हित अक्षर num);
पूर्णांक inet6_del_protocol(स्थिर काष्ठा inet6_protocol *prot, अचिन्हित अक्षर num);
पूर्णांक inet6_रेजिस्टर_protosw(काष्ठा inet_protosw *p);
व्योम inet6_unरेजिस्टर_protosw(काष्ठा inet_protosw *p);
#पूर्ण_अगर
पूर्णांक inet6_add_offload(स्थिर काष्ठा net_offload *prot, अचिन्हित अक्षर num);
पूर्णांक inet6_del_offload(स्थिर काष्ठा net_offload *prot, अचिन्हित अक्षर num);

#पूर्ण_अगर	/* _PROTOCOL_H */
