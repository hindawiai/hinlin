<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* SANE connection tracking helper
 * (SANE = Scanner Access Now Easy)
 * For करोcumentation about the SANE network protocol see
 * http://www.sane-project.org/hपंचांगl/करोc015.hपंचांगl
 */

/* Copyright (C) 2007 Red Hat, Inc.
 * Author: Michal Schmidt <mschmidt@redhat.com>
 * Based on the FTP conntrack helper (net/netfilter/nf_conntrack_ftp.c):
 *  (C) 1999-2001 Paul `Rusty' Russell
 *  (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 *  (C) 2003,2004 USAGI/WIDE Project <http://www.linux-ipv6.org>
 *  (C) 2003 Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <linux/netfilter/nf_conntrack_sane.h>

#घोषणा HELPER_NAME "sane"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Schmidt <mschmidt@redhat.com>");
MODULE_DESCRIPTION("SANE connection tracking helper");
MODULE_ALIAS_NFCT_HELPER(HELPER_NAME);

अटल अक्षर *sane_buffer;

अटल DEFINE_SPINLOCK(nf_sane_lock);

#घोषणा MAX_PORTS 8
अटल u_पूर्णांक16_t ports[MAX_PORTS];
अटल अचिन्हित पूर्णांक ports_c;
module_param_array(ports, uलघु, &ports_c, 0400);

काष्ठा sane_request अणु
	__be32 RPC_code;
#घोषणा SANE_NET_START      7   /* RPC code */

	__be32 handle;
पूर्ण;

काष्ठा sane_reply_net_start अणु
	__be32 status;
#घोषणा SANE_STATUS_SUCCESS 0

	__be16 zero;
	__be16 port;
	/* other fields aren't पूर्णांकeresting क्रम conntrack */
पूर्ण;

अटल पूर्णांक help(काष्ठा sk_buff *skb,
		अचिन्हित पूर्णांक protoff,
		काष्ठा nf_conn *ct,
		क्रमागत ip_conntrack_info ctinfo)
अणु
	अचिन्हित पूर्णांक dataoff, datalen;
	स्थिर काष्ठा tcphdr *th;
	काष्ठा tcphdr _tcph;
	व्योम *sb_ptr;
	पूर्णांक ret = NF_ACCEPT;
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	काष्ठा nf_ct_sane_master *ct_sane_info = nfct_help_data(ct);
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conntrack_tuple *tuple;
	काष्ठा sane_request *req;
	काष्ठा sane_reply_net_start *reply;

	/* Until there's been traffic both ways, don't look in packets. */
	अगर (ctinfo != IP_CT_ESTABLISHED &&
	    ctinfo != IP_CT_ESTABLISHED_REPLY)
		वापस NF_ACCEPT;

	/* Not a full tcp header? */
	th = skb_header_poपूर्णांकer(skb, protoff, माप(_tcph), &_tcph);
	अगर (th == शून्य)
		वापस NF_ACCEPT;

	/* No data? */
	dataoff = protoff + th->करोff * 4;
	अगर (dataoff >= skb->len)
		वापस NF_ACCEPT;

	datalen = skb->len - dataoff;

	spin_lock_bh(&nf_sane_lock);
	sb_ptr = skb_header_poपूर्णांकer(skb, dataoff, datalen, sane_buffer);
	अगर (!sb_ptr) अणु
		spin_unlock_bh(&nf_sane_lock);
		वापस NF_ACCEPT;
	पूर्ण

	अगर (dir == IP_CT_सूची_ORIGINAL) अणु
		अगर (datalen != माप(काष्ठा sane_request))
			जाओ out;

		req = sb_ptr;
		अगर (req->RPC_code != htonl(SANE_NET_START)) अणु
			/* Not an पूर्णांकeresting command */
			ct_sane_info->state = SANE_STATE_NORMAL;
			जाओ out;
		पूर्ण

		/* We're पूर्णांकerested in the next reply */
		ct_sane_info->state = SANE_STATE_START_REQUESTED;
		जाओ out;
	पूर्ण

	/* Is it a reply to an unपूर्णांकeresting command? */
	अगर (ct_sane_info->state != SANE_STATE_START_REQUESTED)
		जाओ out;

	/* It's a reply to SANE_NET_START. */
	ct_sane_info->state = SANE_STATE_NORMAL;

	अगर (datalen < माप(काष्ठा sane_reply_net_start)) अणु
		pr_debug("NET_START reply too short\n");
		जाओ out;
	पूर्ण

	reply = sb_ptr;
	अगर (reply->status != htonl(SANE_STATUS_SUCCESS)) अणु
		/* saned refused the command */
		pr_debug("unsuccessful SANE_STATUS = %u\n",
			 ntohl(reply->status));
		जाओ out;
	पूर्ण

	/* Invalid saned reply? Ignore it. */
	अगर (reply->zero != 0)
		जाओ out;

	exp = nf_ct_expect_alloc(ct);
	अगर (exp == शून्य) अणु
		nf_ct_helper_log(skb, ct, "cannot alloc expectation");
		ret = NF_DROP;
		जाओ out;
	पूर्ण

	tuple = &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &tuple->src.u3, &tuple->dst.u3,
			  IPPROTO_TCP, शून्य, &reply->port);

	pr_debug("expect: ");
	nf_ct_dump_tuple(&exp->tuple);

	/* Can't expect this?  Best to drop packet now. */
	अगर (nf_ct_expect_related(exp, 0) != 0) अणु
		nf_ct_helper_log(skb, ct, "cannot add expectation");
		ret = NF_DROP;
	पूर्ण

	nf_ct_expect_put(exp);

out:
	spin_unlock_bh(&nf_sane_lock);
	वापस ret;
पूर्ण

अटल काष्ठा nf_conntrack_helper sane[MAX_PORTS * 2] __पढ़ो_mostly;

अटल स्थिर काष्ठा nf_conntrack_expect_policy sane_exp_policy = अणु
	.max_expected	= 1,
	.समयout	= 5 * 60,
पूर्ण;

अटल व्योम __निकास nf_conntrack_sane_fini(व्योम)
अणु
	nf_conntrack_helpers_unरेजिस्टर(sane, ports_c * 2);
	kमुक्त(sane_buffer);
पूर्ण

अटल पूर्णांक __init nf_conntrack_sane_init(व्योम)
अणु
	पूर्णांक i, ret = 0;

	NF_CT_HELPER_BUILD_BUG_ON(माप(काष्ठा nf_ct_sane_master));

	sane_buffer = kदो_स्मृति(65536, GFP_KERNEL);
	अगर (!sane_buffer)
		वापस -ENOMEM;

	अगर (ports_c == 0)
		ports[ports_c++] = SANE_PORT;

	/* FIXME should be configurable whether IPv4 and IPv6 connections
		 are tracked or not - YK */
	क्रम (i = 0; i < ports_c; i++) अणु
		nf_ct_helper_init(&sane[2 * i], AF_INET, IPPROTO_TCP,
				  HELPER_NAME, SANE_PORT, ports[i], ports[i],
				  &sane_exp_policy, 0, help, शून्य,
				  THIS_MODULE);
		nf_ct_helper_init(&sane[2 * i + 1], AF_INET6, IPPROTO_TCP,
				  HELPER_NAME, SANE_PORT, ports[i], ports[i],
				  &sane_exp_policy, 0, help, शून्य,
				  THIS_MODULE);
	पूर्ण

	ret = nf_conntrack_helpers_रेजिस्टर(sane, ports_c * 2);
	अगर (ret < 0) अणु
		pr_err("failed to register helpers\n");
		kमुक्त(sane_buffer);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

module_init(nf_conntrack_sane_init);
module_निकास(nf_conntrack_sane_fini);
