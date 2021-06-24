<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Connection tracking support क्रम PPTP (Poपूर्णांक to Poपूर्णांक Tunneling Protocol).
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
 * Limitations:
 * 	 - We blindly assume that control connections are always
 * 	   established in PNS->PAC direction.  This is a violation
 *	   of RFC 2637
 * 	 - We can only support one single call within each session
 * TODO:
 *	 - testing of incoming PPTP calls
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <linux/netfilter/nf_conntrack_proto_gre.h>
#समावेश <linux/netfilter/nf_conntrack_pptp.h>

#घोषणा NF_CT_PPTP_VERSION "3.1"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@gnumonks.org>");
MODULE_DESCRIPTION("Netfilter connection tracking helper module for PPTP");
MODULE_ALIAS("ip_conntrack_pptp");
MODULE_ALIAS_NFCT_HELPER("pptp");

अटल DEFINE_SPINLOCK(nf_pptp_lock);

पूर्णांक
(*nf_nat_pptp_hook_outbound)(काष्ठा sk_buff *skb,
			     काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
			     अचिन्हित पूर्णांक protoff, काष्ठा PptpControlHeader *ctlh,
			     जोड़ pptp_ctrl_जोड़ *pptpReq) __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_nat_pptp_hook_outbound);

पूर्णांक
(*nf_nat_pptp_hook_inbound)(काष्ठा sk_buff *skb,
			    काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
			    अचिन्हित पूर्णांक protoff, काष्ठा PptpControlHeader *ctlh,
			    जोड़ pptp_ctrl_जोड़ *pptpReq) __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_nat_pptp_hook_inbound);

व्योम
(*nf_nat_pptp_hook_exp_gre)(काष्ठा nf_conntrack_expect *expect_orig,
			    काष्ठा nf_conntrack_expect *expect_reply)
			    __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_nat_pptp_hook_exp_gre);

व्योम
(*nf_nat_pptp_hook_expectfn)(काष्ठा nf_conn *ct,
			     काष्ठा nf_conntrack_expect *exp) __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_nat_pptp_hook_expectfn);

#अगर defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
/* PptpControlMessageType names */
अटल स्थिर अक्षर *स्थिर pptp_msg_name_array[PPTP_MSG_MAX + 1] = अणु
	[0]				= "UNKNOWN_MESSAGE",
	[PPTP_START_SESSION_REQUEST]	= "START_SESSION_REQUEST",
	[PPTP_START_SESSION_REPLY]	= "START_SESSION_REPLY",
	[PPTP_STOP_SESSION_REQUEST]	= "STOP_SESSION_REQUEST",
	[PPTP_STOP_SESSION_REPLY]	= "STOP_SESSION_REPLY",
	[PPTP_ECHO_REQUEST]		= "ECHO_REQUEST",
	[PPTP_ECHO_REPLY]		= "ECHO_REPLY",
	[PPTP_OUT_CALL_REQUEST]		= "OUT_CALL_REQUEST",
	[PPTP_OUT_CALL_REPLY]		= "OUT_CALL_REPLY",
	[PPTP_IN_CALL_REQUEST]		= "IN_CALL_REQUEST",
	[PPTP_IN_CALL_REPLY]		= "IN_CALL_REPLY",
	[PPTP_IN_CALL_CONNECT]		= "IN_CALL_CONNECT",
	[PPTP_CALL_CLEAR_REQUEST]	= "CALL_CLEAR_REQUEST",
	[PPTP_CALL_DISCONNECT_NOTIFY]	= "CALL_DISCONNECT_NOTIFY",
	[PPTP_WAN_ERROR_NOTIFY]		= "WAN_ERROR_NOTIFY",
	[PPTP_SET_LINK_INFO]		= "SET_LINK_INFO"
पूर्ण;

स्थिर अक्षर *pptp_msg_name(u_पूर्णांक16_t msg)
अणु
	अगर (msg > PPTP_MSG_MAX)
		वापस pptp_msg_name_array[0];

	वापस pptp_msg_name_array[msg];
पूर्ण
EXPORT_SYMBOL(pptp_msg_name);
#पूर्ण_अगर

#घोषणा SECS *HZ
#घोषणा MINS * 60 SECS
#घोषणा HOURS * 60 MINS

#घोषणा PPTP_GRE_TIMEOUT 		(10 MINS)
#घोषणा PPTP_GRE_STREAM_TIMEOUT 	(5 HOURS)

अटल व्योम pptp_expectfn(काष्ठा nf_conn *ct,
			 काष्ठा nf_conntrack_expect *exp)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	typeof(nf_nat_pptp_hook_expectfn) nf_nat_pptp_expectfn;
	pr_debug("increasing timeouts\n");

	/* increase समयout of GRE data channel conntrack entry */
	ct->proto.gre.समयout	     = PPTP_GRE_TIMEOUT;
	ct->proto.gre.stream_समयout = PPTP_GRE_STREAM_TIMEOUT;

	/* Can you see how rusty this code is, compared with the pre-2.6.11
	 * one? That's what happened to my shiny newnat of 2002 ;( -HW */

	nf_nat_pptp_expectfn = rcu_dereference(nf_nat_pptp_hook_expectfn);
	अगर (nf_nat_pptp_expectfn && ct->master->status & IPS_NAT_MASK)
		nf_nat_pptp_expectfn(ct, exp);
	अन्यथा अणु
		काष्ठा nf_conntrack_tuple inv_t;
		काष्ठा nf_conntrack_expect *exp_other;

		/* obviously this tuple inversion only works until you करो NAT */
		nf_ct_invert_tuple(&inv_t, &exp->tuple);
		pr_debug("trying to unexpect other dir: ");
		nf_ct_dump_tuple(&inv_t);

		exp_other = nf_ct_expect_find_get(net, nf_ct_zone(ct), &inv_t);
		अगर (exp_other) अणु
			/* delete other expectation.  */
			pr_debug("found\n");
			nf_ct_unexpect_related(exp_other);
			nf_ct_expect_put(exp_other);
		पूर्ण अन्यथा अणु
			pr_debug("not found\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक destroy_sibling_or_exp(काष्ठा net *net, काष्ठा nf_conn *ct,
				  स्थिर काष्ठा nf_conntrack_tuple *t)
अणु
	स्थिर काष्ठा nf_conntrack_tuple_hash *h;
	स्थिर काष्ठा nf_conntrack_zone *zone;
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conn *sibling;

	pr_debug("trying to timeout ct or exp for tuple ");
	nf_ct_dump_tuple(t);

	zone = nf_ct_zone(ct);
	h = nf_conntrack_find_get(net, zone, t);
	अगर (h)  अणु
		sibling = nf_ct_tuplehash_to_ctrack(h);
		pr_debug("setting timeout of conntrack %p to 0\n", sibling);
		sibling->proto.gre.समयout	  = 0;
		sibling->proto.gre.stream_समयout = 0;
		nf_ct_समाप्त(sibling);
		nf_ct_put(sibling);
		वापस 1;
	पूर्ण अन्यथा अणु
		exp = nf_ct_expect_find_get(net, zone, t);
		अगर (exp) अणु
			pr_debug("unexpect_related of expect %p\n", exp);
			nf_ct_unexpect_related(exp);
			nf_ct_expect_put(exp);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* समयout GRE data connections */
अटल व्योम pptp_destroy_siblings(काष्ठा nf_conn *ct)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	स्थिर काष्ठा nf_ct_pptp_master *ct_pptp_info = nfct_help_data(ct);
	काष्ठा nf_conntrack_tuple t;

	nf_ct_gre_keymap_destroy(ct);

	/* try original (pns->pac) tuple */
	स_नकल(&t, &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple, माप(t));
	t.dst.protonum = IPPROTO_GRE;
	t.src.u.gre.key = ct_pptp_info->pns_call_id;
	t.dst.u.gre.key = ct_pptp_info->pac_call_id;
	अगर (!destroy_sibling_or_exp(net, ct, &t))
		pr_debug("failed to timeout original pns->pac ct/exp\n");

	/* try reply (pac->pns) tuple */
	स_नकल(&t, &ct->tuplehash[IP_CT_सूची_REPLY].tuple, माप(t));
	t.dst.protonum = IPPROTO_GRE;
	t.src.u.gre.key = ct_pptp_info->pac_call_id;
	t.dst.u.gre.key = ct_pptp_info->pns_call_id;
	अगर (!destroy_sibling_or_exp(net, ct, &t))
		pr_debug("failed to timeout reply pac->pns ct/exp\n");
पूर्ण

/* expect GRE connections (PNS->PAC and PAC->PNS direction) */
अटल पूर्णांक exp_gre(काष्ठा nf_conn *ct, __be16 callid, __be16 peer_callid)
अणु
	काष्ठा nf_conntrack_expect *exp_orig, *exp_reply;
	क्रमागत ip_conntrack_dir dir;
	पूर्णांक ret = 1;
	typeof(nf_nat_pptp_hook_exp_gre) nf_nat_pptp_exp_gre;

	exp_orig = nf_ct_expect_alloc(ct);
	अगर (exp_orig == शून्य)
		जाओ out;

	exp_reply = nf_ct_expect_alloc(ct);
	अगर (exp_reply == शून्य)
		जाओ out_put_orig;

	/* original direction, PNS->PAC */
	dir = IP_CT_सूची_ORIGINAL;
	nf_ct_expect_init(exp_orig, NF_CT_EXPECT_CLASS_DEFAULT,
			  nf_ct_l3num(ct),
			  &ct->tuplehash[dir].tuple.src.u3,
			  &ct->tuplehash[dir].tuple.dst.u3,
			  IPPROTO_GRE, &peer_callid, &callid);
	exp_orig->expectfn = pptp_expectfn;

	/* reply direction, PAC->PNS */
	dir = IP_CT_सूची_REPLY;
	nf_ct_expect_init(exp_reply, NF_CT_EXPECT_CLASS_DEFAULT,
			  nf_ct_l3num(ct),
			  &ct->tuplehash[dir].tuple.src.u3,
			  &ct->tuplehash[dir].tuple.dst.u3,
			  IPPROTO_GRE, &callid, &peer_callid);
	exp_reply->expectfn = pptp_expectfn;

	nf_nat_pptp_exp_gre = rcu_dereference(nf_nat_pptp_hook_exp_gre);
	अगर (nf_nat_pptp_exp_gre && ct->status & IPS_NAT_MASK)
		nf_nat_pptp_exp_gre(exp_orig, exp_reply);
	अगर (nf_ct_expect_related(exp_orig, 0) != 0)
		जाओ out_put_both;
	अगर (nf_ct_expect_related(exp_reply, 0) != 0)
		जाओ out_unexpect_orig;

	/* Add GRE keymap entries */
	अगर (nf_ct_gre_keymap_add(ct, IP_CT_सूची_ORIGINAL, &exp_orig->tuple) != 0)
		जाओ out_unexpect_both;
	अगर (nf_ct_gre_keymap_add(ct, IP_CT_सूची_REPLY, &exp_reply->tuple) != 0) अणु
		nf_ct_gre_keymap_destroy(ct);
		जाओ out_unexpect_both;
	पूर्ण
	ret = 0;

out_put_both:
	nf_ct_expect_put(exp_reply);
out_put_orig:
	nf_ct_expect_put(exp_orig);
out:
	वापस ret;

out_unexpect_both:
	nf_ct_unexpect_related(exp_reply);
out_unexpect_orig:
	nf_ct_unexpect_related(exp_orig);
	जाओ out_put_both;
पूर्ण

अटल पूर्णांक
pptp_inbound_pkt(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		 काष्ठा PptpControlHeader *ctlh,
		 जोड़ pptp_ctrl_जोड़ *pptpReq,
		 अचिन्हित पूर्णांक reqlen,
		 काष्ठा nf_conn *ct,
		 क्रमागत ip_conntrack_info ctinfo)
अणु
	काष्ठा nf_ct_pptp_master *info = nfct_help_data(ct);
	u_पूर्णांक16_t msg;
	__be16 cid = 0, pcid = 0;
	typeof(nf_nat_pptp_hook_inbound) nf_nat_pptp_inbound;

	msg = ntohs(ctlh->messageType);
	pr_debug("inbound control message %s\n", pptp_msg_name(msg));

	चयन (msg) अणु
	हाल PPTP_START_SESSION_REPLY:
		/* server confirms new control session */
		अगर (info->sstate < PPTP_SESSION_REQUESTED)
			जाओ invalid;
		अगर (pptpReq->srep.resultCode == PPTP_START_OK)
			info->sstate = PPTP_SESSION_CONFIRMED;
		अन्यथा
			info->sstate = PPTP_SESSION_ERROR;
		अवरोध;

	हाल PPTP_STOP_SESSION_REPLY:
		/* server confirms end of control session */
		अगर (info->sstate > PPTP_SESSION_STOPREQ)
			जाओ invalid;
		अगर (pptpReq->strep.resultCode == PPTP_STOP_OK)
			info->sstate = PPTP_SESSION_NONE;
		अन्यथा
			info->sstate = PPTP_SESSION_ERROR;
		अवरोध;

	हाल PPTP_OUT_CALL_REPLY:
		/* server accepted call, we now expect GRE frames */
		अगर (info->sstate != PPTP_SESSION_CONFIRMED)
			जाओ invalid;
		अगर (info->cstate != PPTP_CALL_OUT_REQ &&
		    info->cstate != PPTP_CALL_OUT_CONF)
			जाओ invalid;

		cid = pptpReq->ocack.callID;
		pcid = pptpReq->ocack.peersCallID;
		अगर (info->pns_call_id != pcid)
			जाओ invalid;
		pr_debug("%s, CID=%X, PCID=%X\n", pptp_msg_name(msg),
			 ntohs(cid), ntohs(pcid));

		अगर (pptpReq->ocack.resultCode == PPTP_OUTCALL_CONNECT) अणु
			info->cstate = PPTP_CALL_OUT_CONF;
			info->pac_call_id = cid;
			exp_gre(ct, cid, pcid);
		पूर्ण अन्यथा
			info->cstate = PPTP_CALL_NONE;
		अवरोध;

	हाल PPTP_IN_CALL_REQUEST:
		/* server tells us about incoming call request */
		अगर (info->sstate != PPTP_SESSION_CONFIRMED)
			जाओ invalid;

		cid = pptpReq->icreq.callID;
		pr_debug("%s, CID=%X\n", pptp_msg_name(msg), ntohs(cid));
		info->cstate = PPTP_CALL_IN_REQ;
		info->pac_call_id = cid;
		अवरोध;

	हाल PPTP_IN_CALL_CONNECT:
		/* server tells us about incoming call established */
		अगर (info->sstate != PPTP_SESSION_CONFIRMED)
			जाओ invalid;
		अगर (info->cstate != PPTP_CALL_IN_REP &&
		    info->cstate != PPTP_CALL_IN_CONF)
			जाओ invalid;

		pcid = pptpReq->iccon.peersCallID;
		cid = info->pac_call_id;

		अगर (info->pns_call_id != pcid)
			जाओ invalid;

		pr_debug("%s, PCID=%X\n", pptp_msg_name(msg), ntohs(pcid));
		info->cstate = PPTP_CALL_IN_CONF;

		/* we expect a GRE connection from PAC to PNS */
		exp_gre(ct, cid, pcid);
		अवरोध;

	हाल PPTP_CALL_DISCONNECT_NOTIFY:
		/* server confirms disconnect */
		cid = pptpReq->disc.callID;
		pr_debug("%s, CID=%X\n", pptp_msg_name(msg), ntohs(cid));
		info->cstate = PPTP_CALL_NONE;

		/* untrack this call id, unexpect GRE packets */
		pptp_destroy_siblings(ct);
		अवरोध;

	हाल PPTP_WAN_ERROR_NOTIFY:
	हाल PPTP_SET_LINK_INFO:
	हाल PPTP_ECHO_REQUEST:
	हाल PPTP_ECHO_REPLY:
		/* I करोn't have to explain these ;) */
		अवरोध;

	शेष:
		जाओ invalid;
	पूर्ण

	nf_nat_pptp_inbound = rcu_dereference(nf_nat_pptp_hook_inbound);
	अगर (nf_nat_pptp_inbound && ct->status & IPS_NAT_MASK)
		वापस nf_nat_pptp_inbound(skb, ct, ctinfo,
					   protoff, ctlh, pptpReq);
	वापस NF_ACCEPT;

invalid:
	pr_debug("invalid %s: type=%d cid=%u pcid=%u "
		 "cstate=%d sstate=%d pns_cid=%u pac_cid=%u\n",
		 pptp_msg_name(msg),
		 msg, ntohs(cid), ntohs(pcid),  info->cstate, info->sstate,
		 ntohs(info->pns_call_id), ntohs(info->pac_call_id));
	वापस NF_ACCEPT;
पूर्ण

अटल पूर्णांक
pptp_outbound_pkt(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		  काष्ठा PptpControlHeader *ctlh,
		  जोड़ pptp_ctrl_जोड़ *pptpReq,
		  अचिन्हित पूर्णांक reqlen,
		  काष्ठा nf_conn *ct,
		  क्रमागत ip_conntrack_info ctinfo)
अणु
	काष्ठा nf_ct_pptp_master *info = nfct_help_data(ct);
	u_पूर्णांक16_t msg;
	__be16 cid = 0, pcid = 0;
	typeof(nf_nat_pptp_hook_outbound) nf_nat_pptp_outbound;

	msg = ntohs(ctlh->messageType);
	pr_debug("outbound control message %s\n", pptp_msg_name(msg));

	चयन (msg) अणु
	हाल PPTP_START_SESSION_REQUEST:
		/* client requests क्रम new control session */
		अगर (info->sstate != PPTP_SESSION_NONE)
			जाओ invalid;
		info->sstate = PPTP_SESSION_REQUESTED;
		अवरोध;

	हाल PPTP_STOP_SESSION_REQUEST:
		/* client requests end of control session */
		info->sstate = PPTP_SESSION_STOPREQ;
		अवरोध;

	हाल PPTP_OUT_CALL_REQUEST:
		/* client initiating connection to server */
		अगर (info->sstate != PPTP_SESSION_CONFIRMED)
			जाओ invalid;
		info->cstate = PPTP_CALL_OUT_REQ;
		/* track PNS call id */
		cid = pptpReq->ocreq.callID;
		pr_debug("%s, CID=%X\n", pptp_msg_name(msg), ntohs(cid));
		info->pns_call_id = cid;
		अवरोध;

	हाल PPTP_IN_CALL_REPLY:
		/* client answers incoming call */
		अगर (info->cstate != PPTP_CALL_IN_REQ &&
		    info->cstate != PPTP_CALL_IN_REP)
			जाओ invalid;

		cid = pptpReq->icack.callID;
		pcid = pptpReq->icack.peersCallID;
		अगर (info->pac_call_id != pcid)
			जाओ invalid;
		pr_debug("%s, CID=%X PCID=%X\n", pptp_msg_name(msg),
			 ntohs(cid), ntohs(pcid));

		अगर (pptpReq->icack.resultCode == PPTP_INCALL_ACCEPT) अणु
			/* part two of the three-way handshake */
			info->cstate = PPTP_CALL_IN_REP;
			info->pns_call_id = cid;
		पूर्ण अन्यथा
			info->cstate = PPTP_CALL_NONE;
		अवरोध;

	हाल PPTP_CALL_CLEAR_REQUEST:
		/* client requests hangup of call */
		अगर (info->sstate != PPTP_SESSION_CONFIRMED)
			जाओ invalid;
		/* FUTURE: iterate over all calls and check अगर
		 * call ID is valid.  We करोn't करो this without newnat,
		 * because we only know about last call */
		info->cstate = PPTP_CALL_CLEAR_REQ;
		अवरोध;

	हाल PPTP_SET_LINK_INFO:
	हाल PPTP_ECHO_REQUEST:
	हाल PPTP_ECHO_REPLY:
		/* I करोn't have to explain these ;) */
		अवरोध;

	शेष:
		जाओ invalid;
	पूर्ण

	nf_nat_pptp_outbound = rcu_dereference(nf_nat_pptp_hook_outbound);
	अगर (nf_nat_pptp_outbound && ct->status & IPS_NAT_MASK)
		वापस nf_nat_pptp_outbound(skb, ct, ctinfo,
					    protoff, ctlh, pptpReq);
	वापस NF_ACCEPT;

invalid:
	pr_debug("invalid %s: type=%d cid=%u pcid=%u "
		 "cstate=%d sstate=%d pns_cid=%u pac_cid=%u\n",
		 pptp_msg_name(msg),
		 msg, ntohs(cid), ntohs(pcid),  info->cstate, info->sstate,
		 ntohs(info->pns_call_id), ntohs(info->pac_call_id));
	वापस NF_ACCEPT;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक pptp_msg_size[] = अणु
	[PPTP_START_SESSION_REQUEST]  = माप(काष्ठा PptpStartSessionRequest),
	[PPTP_START_SESSION_REPLY]    = माप(काष्ठा PptpStartSessionReply),
	[PPTP_STOP_SESSION_REQUEST]   = माप(काष्ठा PptpStopSessionRequest),
	[PPTP_STOP_SESSION_REPLY]     = माप(काष्ठा PptpStopSessionReply),
	[PPTP_OUT_CALL_REQUEST]       = माप(काष्ठा PptpOutCallRequest),
	[PPTP_OUT_CALL_REPLY]	      = माप(काष्ठा PptpOutCallReply),
	[PPTP_IN_CALL_REQUEST]	      = माप(काष्ठा PptpInCallRequest),
	[PPTP_IN_CALL_REPLY]	      = माप(काष्ठा PptpInCallReply),
	[PPTP_IN_CALL_CONNECT]	      = माप(काष्ठा PptpInCallConnected),
	[PPTP_CALL_CLEAR_REQUEST]     = माप(काष्ठा PptpClearCallRequest),
	[PPTP_CALL_DISCONNECT_NOTIFY] = माप(काष्ठा PptpCallDisconnectNotअगरy),
	[PPTP_WAN_ERROR_NOTIFY]	      = माप(काष्ठा PptpWanErrorNotअगरy),
	[PPTP_SET_LINK_INFO]	      = माप(काष्ठा PptpSetLinkInfo),
पूर्ण;

/* track caller id inside control connection, call expect_related */
अटल पूर्णांक
conntrack_pptp_help(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		    काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo)

अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	स्थिर काष्ठा nf_ct_pptp_master *info = nfct_help_data(ct);
	स्थिर काष्ठा tcphdr *tcph;
	काष्ठा tcphdr _tcph;
	स्थिर काष्ठा pptp_pkt_hdr *pptph;
	काष्ठा pptp_pkt_hdr _pptph;
	काष्ठा PptpControlHeader _ctlh, *ctlh;
	जोड़ pptp_ctrl_जोड़ _pptpReq, *pptpReq;
	अचिन्हित पूर्णांक tcplen = skb->len - protoff;
	अचिन्हित पूर्णांक datalen, reqlen, nexthdr_off;
	पूर्णांक oldsstate, oldcstate;
	पूर्णांक ret;
	u_पूर्णांक16_t msg;

#अगर IS_ENABLED(CONFIG_NF_NAT)
	अगर (!nf_ct_is_confirmed(ct) && (ct->status & IPS_NAT_MASK)) अणु
		काष्ठा nf_conn_nat *nat = nf_ct_ext_find(ct, NF_CT_EXT_NAT);

		अगर (!nat && !nf_ct_ext_add(ct, NF_CT_EXT_NAT, GFP_ATOMIC))
			वापस NF_DROP;
	पूर्ण
#पूर्ण_अगर
	/* करोn't करो any tracking beक्रमe tcp handshake complete */
	अगर (ctinfo != IP_CT_ESTABLISHED && ctinfo != IP_CT_ESTABLISHED_REPLY)
		वापस NF_ACCEPT;

	nexthdr_off = protoff;
	tcph = skb_header_poपूर्णांकer(skb, nexthdr_off, माप(_tcph), &_tcph);
	अगर (!tcph)
		वापस NF_ACCEPT;

	nexthdr_off += tcph->करोff * 4;
	datalen = tcplen - tcph->करोff * 4;

	pptph = skb_header_poपूर्णांकer(skb, nexthdr_off, माप(_pptph), &_pptph);
	अगर (!pptph) अणु
		pr_debug("no full PPTP header, can't track\n");
		वापस NF_ACCEPT;
	पूर्ण
	nexthdr_off += माप(_pptph);
	datalen -= माप(_pptph);

	/* अगर it's not a control message we can't करो anything with it */
	अगर (ntohs(pptph->packetType) != PPTP_PACKET_CONTROL ||
	    ntohl(pptph->magicCookie) != PPTP_MAGIC_COOKIE) अणु
		pr_debug("not a control packet\n");
		वापस NF_ACCEPT;
	पूर्ण

	ctlh = skb_header_poपूर्णांकer(skb, nexthdr_off, माप(_ctlh), &_ctlh);
	अगर (!ctlh)
		वापस NF_ACCEPT;
	nexthdr_off += माप(_ctlh);
	datalen -= माप(_ctlh);

	reqlen = datalen;
	msg = ntohs(ctlh->messageType);
	अगर (msg > 0 && msg <= PPTP_MSG_MAX && reqlen < pptp_msg_size[msg])
		वापस NF_ACCEPT;
	अगर (reqlen > माप(*pptpReq))
		reqlen = माप(*pptpReq);

	pptpReq = skb_header_poपूर्णांकer(skb, nexthdr_off, reqlen, &_pptpReq);
	अगर (!pptpReq)
		वापस NF_ACCEPT;

	oldsstate = info->sstate;
	oldcstate = info->cstate;

	spin_lock_bh(&nf_pptp_lock);

	/* FIXME: We just blindly assume that the control connection is always
	 * established from PNS->PAC.  However, RFC makes no guarantee */
	अगर (dir == IP_CT_सूची_ORIGINAL)
		/* client -> server (PNS -> PAC) */
		ret = pptp_outbound_pkt(skb, protoff, ctlh, pptpReq, reqlen, ct,
					ctinfo);
	अन्यथा
		/* server -> client (PAC -> PNS) */
		ret = pptp_inbound_pkt(skb, protoff, ctlh, pptpReq, reqlen, ct,
				       ctinfo);
	pr_debug("sstate: %d->%d, cstate: %d->%d\n",
		 oldsstate, info->sstate, oldcstate, info->cstate);
	spin_unlock_bh(&nf_pptp_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nf_conntrack_expect_policy pptp_exp_policy = अणु
	.max_expected	= 2,
	.समयout	= 5 * 60,
पूर्ण;

/* control protocol helper */
अटल काष्ठा nf_conntrack_helper pptp __पढ़ो_mostly = अणु
	.name			= "pptp",
	.me			= THIS_MODULE,
	.tuple.src.l3num	= AF_INET,
	.tuple.src.u.tcp.port	= cpu_to_be16(PPTP_CONTROL_PORT),
	.tuple.dst.protonum	= IPPROTO_TCP,
	.help			= conntrack_pptp_help,
	.destroy		= pptp_destroy_siblings,
	.expect_policy		= &pptp_exp_policy,
पूर्ण;

अटल पूर्णांक __init nf_conntrack_pptp_init(व्योम)
अणु
	NF_CT_HELPER_BUILD_BUG_ON(माप(काष्ठा nf_ct_pptp_master));

	वापस nf_conntrack_helper_रेजिस्टर(&pptp);
पूर्ण

अटल व्योम __निकास nf_conntrack_pptp_fini(व्योम)
अणु
	nf_conntrack_helper_unरेजिस्टर(&pptp);
पूर्ण

module_init(nf_conntrack_pptp_init);
module_निकास(nf_conntrack_pptp_fini);
