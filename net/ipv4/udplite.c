<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  UDPLITE     An implementation of the UDP-Lite protocol (RFC 3828).
 *
 *  Authors:    Gerrit Renker       <gerrit@erg.abdn.ac.uk>
 *
 *  Changes:
 *  Fixes:
 */

#घोषणा pr_fmt(fmt) "UDPLite: " fmt

#समावेश <linux/export.h>
#समावेश <linux/proc_fs.h>
#समावेश "udp_impl.h"

काष्ठा udp_table 	udplite_table __पढ़ो_mostly;
EXPORT_SYMBOL(udplite_table);

अटल पूर्णांक udplite_rcv(काष्ठा sk_buff *skb)
अणु
	वापस __udp4_lib_rcv(skb, &udplite_table, IPPROTO_UDPLITE);
पूर्ण

अटल पूर्णांक udplite_err(काष्ठा sk_buff *skb, u32 info)
अणु
	वापस __udp4_lib_err(skb, info, &udplite_table);
पूर्ण

अटल स्थिर काष्ठा net_protocol udplite_protocol = अणु
	.handler	= udplite_rcv,
	.err_handler	= udplite_err,
	.no_policy	= 1,
	.netns_ok	= 1,
पूर्ण;

काष्ठा proto 	udplite_prot = अणु
	.name		   = "UDP-Lite",
	.owner		   = THIS_MODULE,
	.बंद		   = udp_lib_बंद,
	.connect	   = ip4_datagram_connect,
	.disconnect	   = udp_disconnect,
	.ioctl		   = udp_ioctl,
	.init		   = udplite_sk_init,
	.destroy	   = udp_destroy_sock,
	.setsockopt	   = udp_setsockopt,
	.माला_लोockopt	   = udp_माला_लोockopt,
	.sendmsg	   = udp_sendmsg,
	.recvmsg	   = udp_recvmsg,
	.sendpage	   = udp_sendpage,
	.hash		   = udp_lib_hash,
	.unhash		   = udp_lib_unhash,
	.rehash		   = udp_v4_rehash,
	.get_port	   = udp_v4_get_port,
	.memory_allocated  = &udp_memory_allocated,
	.sysctl_mem	   = sysctl_udp_mem,
	.obj_size	   = माप(काष्ठा udp_sock),
	.h.udp_table	   = &udplite_table,
पूर्ण;
EXPORT_SYMBOL(udplite_prot);

अटल काष्ठा inet_protosw udplite4_protosw = अणु
	.type		=  SOCK_DGRAM,
	.protocol	=  IPPROTO_UDPLITE,
	.prot		=  &udplite_prot,
	.ops		=  &inet_dgram_ops,
	.flags		=  INET_PROTOSW_PERMANENT,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
अटल काष्ठा udp_seq_afinfo udplite4_seq_afinfo = अणु
	.family		= AF_INET,
	.udp_table 	= &udplite_table,
पूर्ण;

अटल पूर्णांक __net_init udplite4_proc_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net_data("udplite", 0444, net->proc_net, &udp_seq_ops,
			माप(काष्ठा udp_iter_state), &udplite4_seq_afinfo))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास udplite4_proc_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("udplite", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations udplite4_net_ops = अणु
	.init = udplite4_proc_init_net,
	.निकास = udplite4_proc_निकास_net,
पूर्ण;

अटल __init पूर्णांक udplite4_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&udplite4_net_ops);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक udplite4_proc_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम __init udplite4_रेजिस्टर(व्योम)
अणु
	udp_table_init(&udplite_table, "UDP-Lite");
	अगर (proto_रेजिस्टर(&udplite_prot, 1))
		जाओ out_रेजिस्टर_err;

	अगर (inet_add_protocol(&udplite_protocol, IPPROTO_UDPLITE) < 0)
		जाओ out_unरेजिस्टर_proto;

	inet_रेजिस्टर_protosw(&udplite4_protosw);

	अगर (udplite4_proc_init())
		pr_err("%s: Cannot register /proc!\n", __func__);
	वापस;

out_unरेजिस्टर_proto:
	proto_unरेजिस्टर(&udplite_prot);
out_रेजिस्टर_err:
	pr_crit("%s: Cannot add UDP-Lite protocol\n", __func__);
पूर्ण
