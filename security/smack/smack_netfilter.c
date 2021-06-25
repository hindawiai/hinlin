<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Simplअगरied MAC Kernel (smack) security module
 *
 *  This file contains the Smack netfilter implementation
 *
 *  Author:
 *	Casey Schaufler <हालy@schaufler-ca.com>
 *
 *  Copyright (C) 2014 Casey Schaufler <हालy@schaufler-ca.com>
 *  Copyright (C) 2014 Intel Corporation.
 */

#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netdevice.h>
#समावेश <net/inet_sock.h>
#समावेश <net/net_namespace.h>
#समावेश "smack.h"

#अगर IS_ENABLED(CONFIG_IPV6)

अटल अचिन्हित पूर्णांक smack_ipv6_output(व्योम *priv,
					काष्ठा sk_buff *skb,
					स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा sock *sk = skb_to_full_sk(skb);
	काष्ठा socket_smack *ssp;
	काष्ठा smack_known *skp;

	अगर (sk && sk->sk_security) अणु
		ssp = sk->sk_security;
		skp = ssp->smk_out;
		skb->secmark = skp->smk_secid;
	पूर्ण

	वापस NF_ACCEPT;
पूर्ण
#पूर्ण_अगर	/* IPV6 */

अटल अचिन्हित पूर्णांक smack_ipv4_output(व्योम *priv,
					काष्ठा sk_buff *skb,
					स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा sock *sk = skb_to_full_sk(skb);
	काष्ठा socket_smack *ssp;
	काष्ठा smack_known *skp;

	अगर (sk && sk->sk_security) अणु
		ssp = sk->sk_security;
		skp = ssp->smk_out;
		skb->secmark = skp->smk_secid;
	पूर्ण

	वापस NF_ACCEPT;
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops smack_nf_ops[] = अणु
	अणु
		.hook =		smack_ipv4_output,
		.pf =		NFPROTO_IPV4,
		.hooknum =	NF_INET_LOCAL_OUT,
		.priority =	NF_IP_PRI_SELINUX_FIRST,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IPV6)
	अणु
		.hook =		smack_ipv6_output,
		.pf =		NFPROTO_IPV6,
		.hooknum =	NF_INET_LOCAL_OUT,
		.priority =	NF_IP6_PRI_SELINUX_FIRST,
	पूर्ण,
#पूर्ण_अगर	/* IPV6 */
पूर्ण;

अटल पूर्णांक __net_init smack_nf_रेजिस्टर(काष्ठा net *net)
अणु
	वापस nf_रेजिस्टर_net_hooks(net, smack_nf_ops,
				     ARRAY_SIZE(smack_nf_ops));
पूर्ण

अटल व्योम __net_निकास smack_nf_unरेजिस्टर(काष्ठा net *net)
अणु
	nf_unरेजिस्टर_net_hooks(net, smack_nf_ops, ARRAY_SIZE(smack_nf_ops));
पूर्ण

अटल काष्ठा pernet_operations smack_net_ops = अणु
	.init = smack_nf_रेजिस्टर,
	.निकास = smack_nf_unरेजिस्टर,
पूर्ण;

अटल पूर्णांक __init smack_nf_ip_init(व्योम)
अणु
	अगर (smack_enabled == 0)
		वापस 0;

	prपूर्णांकk(KERN_DEBUG "Smack: Registering netfilter hooks\n");
	वापस रेजिस्टर_pernet_subsys(&smack_net_ops);
पूर्ण

__initcall(smack_nf_ip_init);
