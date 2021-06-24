<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ip_vs_nfct.c:	Netfilter connection tracking support क्रम IPVS
 *
 * Portions Copyright (C) 2001-2002
 * Antefacto Ltd, 181 Parnell St, Dublin 1, Ireland.
 *
 * Portions Copyright (C) 2003-2010
 * Julian Anastasov
 *
 * Authors:
 * Ben North <ben@redfrontकरोor.org>
 * Julian Anastasov <ja@ssi.bg>		Reorganize and sync with latest kernels
 * Hannes Eder <heder@google.com>	Extend NFCT support क्रम FTP, ipvs match
 *
 * Current status:
 *
 * - provide conntrack confirmation क्रम new and related connections, by
 * this way we can see their proper conntrack state in all hooks
 * - support क्रम all क्रमwarding methods, not only NAT
 * - FTP support (NAT), ability to support other NAT apps with expectations
 * - to correctly create expectations क्रम related NAT connections the proper
 * NF conntrack support must be alपढ़ोy installed, eg. ip_vs_ftp requires
 * nf_conntrack_ftp ... iptables_nat क्रम the same ports (but no iptables
 * NAT rules are needed)
 * - alter reply क्रम NAT when क्रमwarding packet in original direction:
 * conntrack from client in NEW or RELATED (Passive FTP DATA) state or
 * when RELATED conntrack is created from real server (Active FTP DATA)
 * - अगर iptables_nat is not loaded the Passive FTP will not work (the
 * PASV response can not be NAT-ed) but Active FTP should work
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/compiler.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/skbuff.h>
#समावेश <net/ip.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <net/ip_vs.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>


#घोषणा FMT_TUPLE	"%s:%u->%s:%u/%u"
#घोषणा ARG_TUPLE(T)	IP_VS_DBG_ADDR((T)->src.l3num, &(T)->src.u3),	\
			ntohs((T)->src.u.all),				\
			IP_VS_DBG_ADDR((T)->src.l3num, &(T)->dst.u3),	\
			ntohs((T)->dst.u.all),				\
			(T)->dst.protonum

#घोषणा FMT_CONN	"%s:%u->%s:%u->%s:%u/%u:%u"
#घोषणा ARG_CONN(C)	IP_VS_DBG_ADDR((C)->af, &((C)->caddr)),		\
			ntohs((C)->cport),				\
			IP_VS_DBG_ADDR((C)->af, &((C)->vaddr)),		\
			ntohs((C)->vport),				\
			IP_VS_DBG_ADDR((C)->daf, &((C)->daddr)),	\
			ntohs((C)->dport),				\
			(C)->protocol, (C)->state

व्योम
ip_vs_update_conntrack(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp, पूर्णांक outin)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा nf_conntrack_tuple new_tuple;

	अगर (ct == शून्य || nf_ct_is_confirmed(ct) ||
	    nf_ct_is_dying(ct))
		वापस;

	/* Never alter conntrack क्रम non-NAT conns */
	अगर (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		वापस;

	/* Never alter conntrack क्रम OPS conns (no reply is expected) */
	अगर (cp->flags & IP_VS_CONN_F_ONE_PACKET)
		वापस;

	/* Alter reply only in original direction */
	अगर (CTINFO2सूची(ctinfo) != IP_CT_सूची_ORIGINAL)
		वापस;

	/* Applications may adjust TCP seqs */
	अगर (cp->app && nf_ct_protonum(ct) == IPPROTO_TCP &&
	    !nfct_seqadj(ct) && !nfct_seqadj_ext_add(ct))
		वापस;

	/*
	 * The connection is not yet in the hashtable, so we update it.
	 * CIP->VIP will reमुख्य the same, so leave the tuple in
	 * IP_CT_सूची_ORIGINAL untouched.  When the reply comes back from the
	 * real-server we will see RIP->DIP.
	 */
	new_tuple = ct->tuplehash[IP_CT_सूची_REPLY].tuple;
	/*
	 * This will also take care of UDP and other protocols.
	 */
	अगर (outin) अणु
		new_tuple.src.u3 = cp->daddr;
		अगर (new_tuple.dst.protonum != IPPROTO_ICMP &&
		    new_tuple.dst.protonum != IPPROTO_ICMPV6)
			new_tuple.src.u.tcp.port = cp->dport;
	पूर्ण अन्यथा अणु
		new_tuple.dst.u3 = cp->vaddr;
		अगर (new_tuple.dst.protonum != IPPROTO_ICMP &&
		    new_tuple.dst.protonum != IPPROTO_ICMPV6)
			new_tuple.dst.u.tcp.port = cp->vport;
	पूर्ण
	IP_VS_DBG_BUF(7, "%s: Updating conntrack ct=%p, status=0x%lX, "
		      "ctinfo=%d, old reply=" FMT_TUPLE "\n",
		      __func__, ct, ct->status, ctinfo,
		      ARG_TUPLE(&ct->tuplehash[IP_CT_सूची_REPLY].tuple));
	IP_VS_DBG_BUF(7, "%s: Updating conntrack ct=%p, status=0x%lX, "
		      "ctinfo=%d, new reply=" FMT_TUPLE "\n",
		      __func__, ct, ct->status, ctinfo,
		      ARG_TUPLE(&new_tuple));
	nf_conntrack_alter_reply(ct, &new_tuple);
	IP_VS_DBG_BUF(7, "%s: Updated conntrack ct=%p for cp=" FMT_CONN "\n",
		      __func__, ct, ARG_CONN(cp));
पूर्ण

पूर्णांक ip_vs_confirm_conntrack(काष्ठा sk_buff *skb)
अणु
	वापस nf_conntrack_confirm(skb);
पूर्ण

/*
 * Called from init_conntrack() as expectfn handler.
 */
अटल व्योम ip_vs_nfct_expect_callback(काष्ठा nf_conn *ct,
	काष्ठा nf_conntrack_expect *exp)
अणु
	काष्ठा nf_conntrack_tuple *orig, new_reply;
	काष्ठा ip_vs_conn *cp;
	काष्ठा ip_vs_conn_param p;
	काष्ठा net *net = nf_ct_net(ct);

	/*
	 * We assume that no NF locks are held beक्रमe this callback.
	 * ip_vs_conn_out_get and ip_vs_conn_in_get should match their
	 * expectations even अगर they use wildcard values, now we provide the
	 * actual values from the newly created original conntrack direction.
	 * The conntrack is confirmed when packet reaches IPVS hooks.
	 */

	/* RS->CLIENT */
	orig = &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple;
	ip_vs_conn_fill_param(net_ipvs(net), exp->tuple.src.l3num, orig->dst.protonum,
			      &orig->src.u3, orig->src.u.tcp.port,
			      &orig->dst.u3, orig->dst.u.tcp.port, &p);
	cp = ip_vs_conn_out_get(&p);
	अगर (cp) अणु
		/* Change reply CLIENT->RS to CLIENT->VS */
		IP_VS_DBG_BUF(7, "%s: for ct=%p, status=0x%lX found inout cp="
			      FMT_CONN "\n",
			      __func__, ct, ct->status, ARG_CONN(cp));
		new_reply = ct->tuplehash[IP_CT_सूची_REPLY].tuple;
		IP_VS_DBG_BUF(7, "%s: ct=%p before alter: reply tuple="
			      FMT_TUPLE "\n",
			      __func__, ct, ARG_TUPLE(&new_reply));
		new_reply.dst.u3 = cp->vaddr;
		new_reply.dst.u.tcp.port = cp->vport;
		जाओ alter;
	पूर्ण

	/* CLIENT->VS */
	cp = ip_vs_conn_in_get(&p);
	अगर (cp) अणु
		/* Change reply VS->CLIENT to RS->CLIENT */
		IP_VS_DBG_BUF(7, "%s: for ct=%p, status=0x%lX found outin cp="
			      FMT_CONN "\n",
			      __func__, ct, ct->status, ARG_CONN(cp));
		new_reply = ct->tuplehash[IP_CT_सूची_REPLY].tuple;
		IP_VS_DBG_BUF(7, "%s: ct=%p before alter: reply tuple="
			      FMT_TUPLE "\n",
			      __func__, ct, ARG_TUPLE(&new_reply));
		new_reply.src.u3 = cp->daddr;
		new_reply.src.u.tcp.port = cp->dport;
		जाओ alter;
	पूर्ण

	IP_VS_DBG_BUF(7, "%s: ct=%p, status=0x%lX, tuple=" FMT_TUPLE
		      " - unknown expect\n",
		      __func__, ct, ct->status, ARG_TUPLE(orig));
	वापस;

alter:
	/* Never alter conntrack क्रम non-NAT conns */
	अगर (IP_VS_FWD_METHOD(cp) == IP_VS_CONN_F_MASQ)
		nf_conntrack_alter_reply(ct, &new_reply);
	ip_vs_conn_put(cp);
	वापस;
पूर्ण

/*
 * Create NF conntrack expectation with wildcard (optional) source port.
 * Then the शेष callback function will alter the reply and will confirm
 * the conntrack entry when the first packet comes.
 * Use port 0 to expect connection from any port.
 */
व्योम ip_vs_nfct_expect_related(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			       काष्ठा ip_vs_conn *cp, u_पूर्णांक8_t proto,
			       स्थिर __be16 port, पूर्णांक from_rs)
अणु
	काष्ठा nf_conntrack_expect *exp;

	अगर (ct == शून्य)
		वापस;

	exp = nf_ct_expect_alloc(ct);
	अगर (!exp)
		वापस;

	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			from_rs ? &cp->daddr : &cp->caddr,
			from_rs ? &cp->caddr : &cp->vaddr,
			proto, port ? &port : शून्य,
			from_rs ? &cp->cport : &cp->vport);

	exp->expectfn = ip_vs_nfct_expect_callback;

	IP_VS_DBG_BUF(7, "%s: ct=%p, expect tuple=" FMT_TUPLE "\n",
		      __func__, ct, ARG_TUPLE(&exp->tuple));
	nf_ct_expect_related(exp, 0);
	nf_ct_expect_put(exp);
पूर्ण
EXPORT_SYMBOL(ip_vs_nfct_expect_related);

/*
 * Our connection was terminated, try to drop the conntrack immediately
 */
व्योम ip_vs_conn_drop_conntrack(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conn *ct;
	काष्ठा nf_conntrack_tuple tuple;

	अगर (!cp->cport)
		वापस;

	tuple = (काष्ठा nf_conntrack_tuple) अणु
		.dst = अणु .protonum = cp->protocol, .dir = IP_CT_सूची_ORIGINAL पूर्ण पूर्ण;
	tuple.src.u3 = cp->caddr;
	tuple.src.u.all = cp->cport;
	tuple.src.l3num = cp->af;
	tuple.dst.u3 = cp->vaddr;
	tuple.dst.u.all = cp->vport;

	IP_VS_DBG_BUF(7, "%s: dropping conntrack for conn " FMT_CONN "\n",
		      __func__, ARG_CONN(cp));

	h = nf_conntrack_find_get(cp->ipvs->net, &nf_ct_zone_dflt, &tuple);
	अगर (h) अणु
		ct = nf_ct_tuplehash_to_ctrack(h);
		अगर (nf_ct_समाप्त(ct)) अणु
			IP_VS_DBG_BUF(7, "%s: ct=%p deleted for tuple="
				      FMT_TUPLE "\n",
				      __func__, ct, ARG_TUPLE(&tuple));
		पूर्ण अन्यथा अणु
			IP_VS_DBG_BUF(7, "%s: ct=%p, no conntrack for tuple="
				      FMT_TUPLE "\n",
				      __func__, ct, ARG_TUPLE(&tuple));
		पूर्ण
		nf_ct_put(ct);
	पूर्ण अन्यथा अणु
		IP_VS_DBG_BUF(7, "%s: no conntrack for tuple=" FMT_TUPLE "\n",
			      __func__, ARG_TUPLE(&tuple));
	पूर्ण
पूर्ण

