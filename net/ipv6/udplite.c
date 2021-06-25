<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  UDPLITEv6   An implementation of the UDP-Lite protocol over IPv6.
 *              See also net/ipv4/udplite.c
 *
 *  Authors:    Gerrit Renker       <gerrit@erg.abdn.ac.uk>
 *
 *  Changes:
 *  Fixes:
 */
#समावेश <linux/export.h>
#समावेश <linux/proc_fs.h>
#समावेश "udp_impl.h"

अटल पूर्णांक udplitev6_rcv(काष्ठा sk_buff *skb)
अणु
	वापस __udp6_lib_rcv(skb, &udplite_table, IPPROTO_UDPLITE);
पूर्ण

अटल पूर्णांक udplitev6_err(काष्ठा sk_buff *skb,
			  काष्ठा inet6_skb_parm *opt,
			  u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	वापस __udp6_lib_err(skb, opt, type, code, offset, info,
			      &udplite_table);
पूर्ण

अटल स्थिर काष्ठा inet6_protocol udplitev6_protocol = अणु
	.handler	=	udplitev6_rcv,
	.err_handler	=	udplitev6_err,
	.flags		=	INET6_PROTO_NOPOLICY|INET6_PROTO_FINAL,
पूर्ण;

काष्ठा proto udplitev6_prot = अणु
	.name		   = "UDPLITEv6",
	.owner		   = THIS_MODULE,
	.बंद		   = udp_lib_बंद,
	.connect	   = ip6_datagram_connect,
	.disconnect	   = udp_disconnect,
	.ioctl		   = udp_ioctl,
	.init		   = udplite_sk_init,
	.destroy	   = udpv6_destroy_sock,
	.setsockopt	   = udpv6_setsockopt,
	.माला_लोockopt	   = udpv6_माला_लोockopt,
	.sendmsg	   = udpv6_sendmsg,
	.recvmsg	   = udpv6_recvmsg,
	.hash		   = udp_lib_hash,
	.unhash		   = udp_lib_unhash,
	.rehash		   = udp_v6_rehash,
	.get_port	   = udp_v6_get_port,
	.memory_allocated  = &udp_memory_allocated,
	.sysctl_mem	   = sysctl_udp_mem,
	.obj_size	   = माप(काष्ठा udp6_sock),
	.h.udp_table	   = &udplite_table,
पूर्ण;

अटल काष्ठा inet_protosw udplite6_protosw = अणु
	.type		= SOCK_DGRAM,
	.protocol	= IPPROTO_UDPLITE,
	.prot		= &udplitev6_prot,
	.ops		= &inet6_dgram_ops,
	.flags		= INET_PROTOSW_PERMANENT,
पूर्ण;

पूर्णांक __init udplitev6_init(व्योम)
अणु
	पूर्णांक ret;

	ret = inet6_add_protocol(&udplitev6_protocol, IPPROTO_UDPLITE);
	अगर (ret)
		जाओ out;

	ret = inet6_रेजिस्टर_protosw(&udplite6_protosw);
	अगर (ret)
		जाओ out_udplitev6_protocol;
out:
	वापस ret;

out_udplitev6_protocol:
	inet6_del_protocol(&udplitev6_protocol, IPPROTO_UDPLITE);
	जाओ out;
पूर्ण

व्योम udplitev6_निकास(व्योम)
अणु
	inet6_unरेजिस्टर_protosw(&udplite6_protosw);
	inet6_del_protocol(&udplitev6_protocol, IPPROTO_UDPLITE);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल काष्ठा udp_seq_afinfo udplite6_seq_afinfo = अणु
	.family		= AF_INET6,
	.udp_table	= &udplite_table,
पूर्ण;

अटल पूर्णांक __net_init udplite6_proc_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net_data("udplite6", 0444, net->proc_net,
			&udp6_seq_ops, माप(काष्ठा udp_iter_state),
			&udplite6_seq_afinfo))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास udplite6_proc_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("udplite6", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations udplite6_net_ops = अणु
	.init = udplite6_proc_init_net,
	.निकास = udplite6_proc_निकास_net,
पूर्ण;

पूर्णांक __init udplite6_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&udplite6_net_ops);
पूर्ण

व्योम udplite6_proc_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&udplite6_net_ops);
पूर्ण
#पूर्ण_अगर
