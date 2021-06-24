<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * nf_nat_pptp.c
 *
 * NAT support क्रम PPTP (Poपूर्णांक to Poपूर्णांक Tunneling Protocol).
 * PPTP is a protocol क्रम creating भव निजी networks.
 * It is a specअगरication defined by Microsoft and some venकरोrs
 * working with Microsoft.  PPTP is built on top of a modअगरied
 * version of the Internet Generic Routing Encapsulation Protocol.
 * GRE is defined in RFC 1701 and RFC 1702.  Documentation of
 * PPTP can be found in RFC 2637
 *
 * (C) 2000-2005 by Harald Welte <laक्रमge@gnumonks.org>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 *
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 *
 * TODO: - NAT to a unique tuple, not to TCP source port
 * 	   (needs netfilter tuple reservation)
 */

#समावेश <linux/module.h>
#समावेश <linux/tcp.h>

#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <linux/netfilter/nf_conntrack_proto_gre.h>
#समावेश <linux/netfilter/nf_conntrack_pptp.h>

#घोषणा NF_NAT_PPTP_VERSION "3.0"

#घोषणा REQ_CID(req, off)		(*(__be16 *)((अक्षर *)(req) + (off)))

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@gnumonks.org>");
MODULE_DESCRIPTION("Netfilter NAT helper module for PPTP");
MODULE_ALIAS_NF_NAT_HELPER("pptp");

अटल व्योम pptp_nat_expected(काष्ठा nf_conn *ct,
			      काष्ठा nf_conntrack_expect *exp)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	स्थिर काष्ठा nf_conn *master = ct->master;
	काष्ठा nf_conntrack_expect *other_exp;
	काष्ठा nf_conntrack_tuple t = अणुपूर्ण;
	स्थिर काष्ठा nf_ct_pptp_master *ct_pptp_info;
	स्थिर काष्ठा nf_nat_pptp *nat_pptp_info;
	काष्ठा nf_nat_range2 range;
	काष्ठा nf_conn_nat *nat;

	nat = nf_ct_nat_ext_add(ct);
	अगर (WARN_ON_ONCE(!nat))
		वापस;

	nat_pptp_info = &nat->help.nat_pptp_info;
	ct_pptp_info = nfct_help_data(master);

	/* And here goes the gअक्रम finale of corrosion... */
	अगर (exp->dir == IP_CT_सूची_ORIGINAL) अणु
		pr_debug("we are PNS->PAC\n");
		/* thereक्रमe, build tuple क्रम PAC->PNS */
		t.src.l3num = AF_INET;
		t.src.u3.ip = master->tuplehash[!exp->dir].tuple.src.u3.ip;
		t.src.u.gre.key = ct_pptp_info->pac_call_id;
		t.dst.u3.ip = master->tuplehash[!exp->dir].tuple.dst.u3.ip;
		t.dst.u.gre.key = ct_pptp_info->pns_call_id;
		t.dst.protonum = IPPROTO_GRE;
	पूर्ण अन्यथा अणु
		pr_debug("we are PAC->PNS\n");
		/* build tuple क्रम PNS->PAC */
		t.src.l3num = AF_INET;
		t.src.u3.ip = master->tuplehash[!exp->dir].tuple.src.u3.ip;
		t.src.u.gre.key = nat_pptp_info->pns_call_id;
		t.dst.u3.ip = master->tuplehash[!exp->dir].tuple.dst.u3.ip;
		t.dst.u.gre.key = nat_pptp_info->pac_call_id;
		t.dst.protonum = IPPROTO_GRE;
	पूर्ण

	pr_debug("trying to unexpect other dir: ");
	nf_ct_dump_tuple_ip(&t);
	other_exp = nf_ct_expect_find_get(net, nf_ct_zone(ct), &t);
	अगर (other_exp) अणु
		nf_ct_unexpect_related(other_exp);
		nf_ct_expect_put(other_exp);
		pr_debug("success\n");
	पूर्ण अन्यथा अणु
		pr_debug("not found!\n");
	पूर्ण

	/* This must be a fresh one. */
	BUG_ON(ct->status & IPS_NAT_DONE_MASK);

	/* Change src to where master sends to */
	range.flags = NF_NAT_RANGE_MAP_IPS;
	range.min_addr = range.max_addr
		= ct->master->tuplehash[!exp->dir].tuple.dst.u3;
	अगर (exp->dir == IP_CT_सूची_ORIGINAL) अणु
		range.flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
		range.min_proto = range.max_proto = exp->saved_proto;
	पूर्ण
	nf_nat_setup_info(ct, &range, NF_NAT_MANIP_SRC);

	/* For DST manip, map port here to where it's expected. */
	range.flags = NF_NAT_RANGE_MAP_IPS;
	range.min_addr = range.max_addr
		= ct->master->tuplehash[!exp->dir].tuple.src.u3;
	अगर (exp->dir == IP_CT_सूची_REPLY) अणु
		range.flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
		range.min_proto = range.max_proto = exp->saved_proto;
	पूर्ण
	nf_nat_setup_info(ct, &range, NF_NAT_MANIP_DST);
पूर्ण

/* outbound packets == from PNS to PAC */
अटल पूर्णांक
pptp_outbound_pkt(काष्ठा sk_buff *skb,
		  काष्ठा nf_conn *ct,
		  क्रमागत ip_conntrack_info ctinfo,
		  अचिन्हित पूर्णांक protoff,
		  काष्ठा PptpControlHeader *ctlh,
		  जोड़ pptp_ctrl_जोड़ *pptpReq)

अणु
	काष्ठा nf_ct_pptp_master *ct_pptp_info;
	काष्ठा nf_conn_nat *nat = nfct_nat(ct);
	काष्ठा nf_nat_pptp *nat_pptp_info;
	u_पूर्णांक16_t msg;
	__be16 new_callid;
	अचिन्हित पूर्णांक cid_off;

	अगर (WARN_ON_ONCE(!nat))
		वापस NF_DROP;

	nat_pptp_info = &nat->help.nat_pptp_info;
	ct_pptp_info = nfct_help_data(ct);

	new_callid = ct_pptp_info->pns_call_id;

	चयन (msg = ntohs(ctlh->messageType)) अणु
	हाल PPTP_OUT_CALL_REQUEST:
		cid_off = दुरत्व(जोड़ pptp_ctrl_जोड़, ocreq.callID);
		/* FIXME: ideally we would want to reserve a call ID
		 * here.  current netfilter NAT core is not able to करो
		 * this :( For now we use TCP source port. This अवरोधs
		 * multiple calls within one control session */

		/* save original call ID in nat_info */
		nat_pptp_info->pns_call_id = ct_pptp_info->pns_call_id;

		/* करोn't use tcph->source since we are at a DSTmanip
		 * hook (e.g. PREROUTING) and pkt is not mangled yet */
		new_callid = ct->tuplehash[IP_CT_सूची_REPLY].tuple.dst.u.tcp.port;

		/* save new call ID in ct info */
		ct_pptp_info->pns_call_id = new_callid;
		अवरोध;
	हाल PPTP_IN_CALL_REPLY:
		cid_off = दुरत्व(जोड़ pptp_ctrl_जोड़, icack.callID);
		अवरोध;
	हाल PPTP_CALL_CLEAR_REQUEST:
		cid_off = दुरत्व(जोड़ pptp_ctrl_जोड़, clrreq.callID);
		अवरोध;
	शेष:
		pr_debug("unknown outbound packet 0x%04x:%s\n", msg,
			 pptp_msg_name(msg));
		fallthrough;
	हाल PPTP_SET_LINK_INFO:
		/* only need to NAT in हाल PAC is behind NAT box */
	हाल PPTP_START_SESSION_REQUEST:
	हाल PPTP_START_SESSION_REPLY:
	हाल PPTP_STOP_SESSION_REQUEST:
	हाल PPTP_STOP_SESSION_REPLY:
	हाल PPTP_ECHO_REQUEST:
	हाल PPTP_ECHO_REPLY:
		/* no need to alter packet */
		वापस NF_ACCEPT;
	पूर्ण

	/* only OUT_CALL_REQUEST, IN_CALL_REPLY, CALL_CLEAR_REQUEST pass
	 * करोwn to here */
	pr_debug("altering call id from 0x%04x to 0x%04x\n",
		 ntohs(REQ_CID(pptpReq, cid_off)), ntohs(new_callid));

	/* mangle packet */
	अगर (!nf_nat_mangle_tcp_packet(skb, ct, ctinfo, protoff,
				      cid_off + माप(काष्ठा pptp_pkt_hdr) +
				      माप(काष्ठा PptpControlHeader),
				      माप(new_callid), (अक्षर *)&new_callid,
				      माप(new_callid)))
		वापस NF_DROP;
	वापस NF_ACCEPT;
पूर्ण

अटल व्योम
pptp_exp_gre(काष्ठा nf_conntrack_expect *expect_orig,
	     काष्ठा nf_conntrack_expect *expect_reply)
अणु
	स्थिर काष्ठा nf_conn *ct = expect_orig->master;
	काष्ठा nf_conn_nat *nat = nfct_nat(ct);
	काष्ठा nf_ct_pptp_master *ct_pptp_info;
	काष्ठा nf_nat_pptp *nat_pptp_info;

	अगर (WARN_ON_ONCE(!nat))
		वापस;

	nat_pptp_info = &nat->help.nat_pptp_info;
	ct_pptp_info = nfct_help_data(ct);

	/* save original PAC call ID in nat_info */
	nat_pptp_info->pac_call_id = ct_pptp_info->pac_call_id;

	/* alter expectation क्रम PNS->PAC direction */
	expect_orig->saved_proto.gre.key = ct_pptp_info->pns_call_id;
	expect_orig->tuple.src.u.gre.key = nat_pptp_info->pns_call_id;
	expect_orig->tuple.dst.u.gre.key = ct_pptp_info->pac_call_id;
	expect_orig->dir = IP_CT_सूची_ORIGINAL;

	/* alter expectation क्रम PAC->PNS direction */
	expect_reply->saved_proto.gre.key = nat_pptp_info->pns_call_id;
	expect_reply->tuple.src.u.gre.key = nat_pptp_info->pac_call_id;
	expect_reply->tuple.dst.u.gre.key = ct_pptp_info->pns_call_id;
	expect_reply->dir = IP_CT_सूची_REPLY;
पूर्ण

/* inbound packets == from PAC to PNS */
अटल पूर्णांक
pptp_inbound_pkt(काष्ठा sk_buff *skb,
		 काष्ठा nf_conn *ct,
		 क्रमागत ip_conntrack_info ctinfo,
		 अचिन्हित पूर्णांक protoff,
		 काष्ठा PptpControlHeader *ctlh,
		 जोड़ pptp_ctrl_जोड़ *pptpReq)
अणु
	स्थिर काष्ठा nf_nat_pptp *nat_pptp_info;
	काष्ठा nf_conn_nat *nat = nfct_nat(ct);
	u_पूर्णांक16_t msg;
	__be16 new_pcid;
	अचिन्हित पूर्णांक pcid_off;

	अगर (WARN_ON_ONCE(!nat))
		वापस NF_DROP;

	nat_pptp_info = &nat->help.nat_pptp_info;
	new_pcid = nat_pptp_info->pns_call_id;

	चयन (msg = ntohs(ctlh->messageType)) अणु
	हाल PPTP_OUT_CALL_REPLY:
		pcid_off = दुरत्व(जोड़ pptp_ctrl_जोड़, ocack.peersCallID);
		अवरोध;
	हाल PPTP_IN_CALL_CONNECT:
		pcid_off = दुरत्व(जोड़ pptp_ctrl_जोड़, iccon.peersCallID);
		अवरोध;
	हाल PPTP_IN_CALL_REQUEST:
		/* only need to nat in हाल PAC is behind NAT box */
		वापस NF_ACCEPT;
	हाल PPTP_WAN_ERROR_NOTIFY:
		pcid_off = दुरत्व(जोड़ pptp_ctrl_जोड़, wanerr.peersCallID);
		अवरोध;
	हाल PPTP_CALL_DISCONNECT_NOTIFY:
		pcid_off = दुरत्व(जोड़ pptp_ctrl_जोड़, disc.callID);
		अवरोध;
	हाल PPTP_SET_LINK_INFO:
		pcid_off = दुरत्व(जोड़ pptp_ctrl_जोड़, setlink.peersCallID);
		अवरोध;
	शेष:
		pr_debug("unknown inbound packet %s\n", pptp_msg_name(msg));
		fallthrough;
	हाल PPTP_START_SESSION_REQUEST:
	हाल PPTP_START_SESSION_REPLY:
	हाल PPTP_STOP_SESSION_REQUEST:
	हाल PPTP_STOP_SESSION_REPLY:
	हाल PPTP_ECHO_REQUEST:
	हाल PPTP_ECHO_REPLY:
		/* no need to alter packet */
		वापस NF_ACCEPT;
	पूर्ण

	/* only OUT_CALL_REPLY, IN_CALL_CONNECT, IN_CALL_REQUEST,
	 * WAN_ERROR_NOTIFY, CALL_DISCONNECT_NOTIFY pass करोwn here */

	/* mangle packet */
	pr_debug("altering peer call id from 0x%04x to 0x%04x\n",
		 ntohs(REQ_CID(pptpReq, pcid_off)), ntohs(new_pcid));

	अगर (!nf_nat_mangle_tcp_packet(skb, ct, ctinfo, protoff,
				      pcid_off + माप(काष्ठा pptp_pkt_hdr) +
				      माप(काष्ठा PptpControlHeader),
				      माप(new_pcid), (अक्षर *)&new_pcid,
				      माप(new_pcid)))
		वापस NF_DROP;
	वापस NF_ACCEPT;
पूर्ण

अटल पूर्णांक __init nf_nat_helper_pptp_init(व्योम)
अणु
	BUG_ON(nf_nat_pptp_hook_outbound != शून्य);
	RCU_INIT_POINTER(nf_nat_pptp_hook_outbound, pptp_outbound_pkt);

	BUG_ON(nf_nat_pptp_hook_inbound != शून्य);
	RCU_INIT_POINTER(nf_nat_pptp_hook_inbound, pptp_inbound_pkt);

	BUG_ON(nf_nat_pptp_hook_exp_gre != शून्य);
	RCU_INIT_POINTER(nf_nat_pptp_hook_exp_gre, pptp_exp_gre);

	BUG_ON(nf_nat_pptp_hook_expectfn != शून्य);
	RCU_INIT_POINTER(nf_nat_pptp_hook_expectfn, pptp_nat_expected);
	वापस 0;
पूर्ण

अटल व्योम __निकास nf_nat_helper_pptp_fini(व्योम)
अणु
	RCU_INIT_POINTER(nf_nat_pptp_hook_expectfn, शून्य);
	RCU_INIT_POINTER(nf_nat_pptp_hook_exp_gre, शून्य);
	RCU_INIT_POINTER(nf_nat_pptp_hook_inbound, शून्य);
	RCU_INIT_POINTER(nf_nat_pptp_hook_outbound, शून्य);
	synchronize_rcu();
पूर्ण

module_init(nf_nat_helper_pptp_init);
module_निकास(nf_nat_helper_pptp_fini);
