<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * H.323 connection tracking helper
 *
 * Copyright (c) 2006 Jing Min Zhao <zhaojingmin@users.sourceक्रमge.net>
 * Copyright (c) 2006-2012 Patrick McHardy <kaber@trash.net>
 *
 * Based on the 'brute force' H.323 connection tracking module by
 * Jozsef Kadlecsik <kadlec@netfilter.org>
 *
 * For more inक्रमmation, please see http://nath323.sourceक्रमge.net/
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/inet.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/slab.h>
#समावेश <linux/udp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/route.h>
#समावेश <net/ip6_route.h>
#समावेश <linux/netfilter_ipv6.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <linux/netfilter/nf_conntrack_h323.h>

/* Parameters */
अटल अचिन्हित पूर्णांक शेष_rrq_ttl __पढ़ो_mostly = 300;
module_param(शेष_rrq_ttl, uपूर्णांक, 0600);
MODULE_PARM_DESC(शेष_rrq_ttl, "use this TTL if it's missing in RRQ");

अटल पूर्णांक gkrouted_only __पढ़ो_mostly = 1;
module_param(gkrouted_only, पूर्णांक, 0600);
MODULE_PARM_DESC(gkrouted_only, "only accept calls from gatekeeper");

अटल bool callक्रमward_filter __पढ़ो_mostly = true;
module_param(callक्रमward_filter, bool, 0600);
MODULE_PARM_DESC(callक्रमward_filter, "only create call forwarding expectations "
				     "if both endpoints are on different sides "
				     "(determined by routing information)");

/* Hooks क्रम NAT */
पूर्णांक (*set_h245_addr_hook) (काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			   अचिन्हित अक्षर **data, पूर्णांक dataoff,
			   H245_TransportAddress *taddr,
			   जोड़ nf_inet_addr *addr, __be16 port)
			   __पढ़ो_mostly;
पूर्णांक (*set_h225_addr_hook) (काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			   अचिन्हित अक्षर **data, पूर्णांक dataoff,
			   TransportAddress *taddr,
			   जोड़ nf_inet_addr *addr, __be16 port)
			   __पढ़ो_mostly;
पूर्णांक (*set_sig_addr_hook) (काष्ठा sk_buff *skb,
			  काष्ठा nf_conn *ct,
			  क्रमागत ip_conntrack_info ctinfo,
			  अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data,
			  TransportAddress *taddr, पूर्णांक count) __पढ़ो_mostly;
पूर्णांक (*set_ras_addr_hook) (काष्ठा sk_buff *skb,
			  काष्ठा nf_conn *ct,
			  क्रमागत ip_conntrack_info ctinfo,
			  अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data,
			  TransportAddress *taddr, पूर्णांक count) __पढ़ो_mostly;
पूर्णांक (*nat_rtp_rtcp_hook) (काष्ठा sk_buff *skb,
			  काष्ठा nf_conn *ct,
			  क्रमागत ip_conntrack_info ctinfo,
			  अचिन्हित पूर्णांक protoff,
			  अचिन्हित अक्षर **data, पूर्णांक dataoff,
			  H245_TransportAddress *taddr,
			  __be16 port, __be16 rtp_port,
			  काष्ठा nf_conntrack_expect *rtp_exp,
			  काष्ठा nf_conntrack_expect *rtcp_exp) __पढ़ो_mostly;
पूर्णांक (*nat_t120_hook) (काष्ठा sk_buff *skb,
		      काष्ठा nf_conn *ct,
		      क्रमागत ip_conntrack_info ctinfo,
		      अचिन्हित पूर्णांक protoff,
		      अचिन्हित अक्षर **data, पूर्णांक dataoff,
		      H245_TransportAddress *taddr, __be16 port,
		      काष्ठा nf_conntrack_expect *exp) __पढ़ो_mostly;
पूर्णांक (*nat_h245_hook) (काष्ठा sk_buff *skb,
		      काष्ठा nf_conn *ct,
		      क्रमागत ip_conntrack_info ctinfo,
		      अचिन्हित पूर्णांक protoff,
		      अचिन्हित अक्षर **data, पूर्णांक dataoff,
		      TransportAddress *taddr, __be16 port,
		      काष्ठा nf_conntrack_expect *exp) __पढ़ो_mostly;
पूर्णांक (*nat_callक्रमwarding_hook) (काष्ठा sk_buff *skb,
				काष्ठा nf_conn *ct,
				क्रमागत ip_conntrack_info ctinfo,
				अचिन्हित पूर्णांक protoff,
				अचिन्हित अक्षर **data, पूर्णांक dataoff,
				TransportAddress *taddr, __be16 port,
				काष्ठा nf_conntrack_expect *exp) __पढ़ो_mostly;
पूर्णांक (*nat_q931_hook) (काष्ठा sk_buff *skb,
		      काष्ठा nf_conn *ct,
		      क्रमागत ip_conntrack_info ctinfo,
		      अचिन्हित पूर्णांक protoff,
		      अचिन्हित अक्षर **data, TransportAddress *taddr, पूर्णांक idx,
		      __be16 port, काष्ठा nf_conntrack_expect *exp)
		      __पढ़ो_mostly;

अटल DEFINE_SPINLOCK(nf_h323_lock);
अटल अक्षर *h323_buffer;

अटल काष्ठा nf_conntrack_helper nf_conntrack_helper_h245;
अटल काष्ठा nf_conntrack_helper nf_conntrack_helper_q931[];
अटल काष्ठा nf_conntrack_helper nf_conntrack_helper_ras[];

अटल पूर्णांक get_tpkt_data(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			 काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
			 अचिन्हित अक्षर **data, पूर्णांक *datalen, पूर्णांक *dataoff)
अणु
	काष्ठा nf_ct_h323_master *info = nfct_help_data(ct);
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	स्थिर काष्ठा tcphdr *th;
	काष्ठा tcphdr _tcph;
	पूर्णांक tcpdatalen;
	पूर्णांक tcpdataoff;
	अचिन्हित अक्षर *tpkt;
	पूर्णांक tpktlen;
	पूर्णांक tpktoff;

	/* Get TCP header */
	th = skb_header_poपूर्णांकer(skb, protoff, माप(_tcph), &_tcph);
	अगर (th == शून्य)
		वापस 0;

	/* Get TCP data offset */
	tcpdataoff = protoff + th->करोff * 4;

	/* Get TCP data length */
	tcpdatalen = skb->len - tcpdataoff;
	अगर (tcpdatalen <= 0)	/* No TCP data */
		जाओ clear_out;

	अगर (*data == शून्य) अणु	/* first TPKT */
		/* Get first TPKT poपूर्णांकer */
		tpkt = skb_header_poपूर्णांकer(skb, tcpdataoff, tcpdatalen,
					  h323_buffer);
		अगर (!tpkt)
			जाओ clear_out;

		/* Validate TPKT identअगरier */
		अगर (tcpdatalen < 4 || tpkt[0] != 0x03 || tpkt[1] != 0) अणु
			/* Neपंचांगeeting sends TPKT header and data separately */
			अगर (info->tpkt_len[dir] > 0) अणु
				pr_debug("nf_ct_h323: previous packet "
					 "indicated separate TPKT data of %hu "
					 "bytes\n", info->tpkt_len[dir]);
				अगर (info->tpkt_len[dir] <= tcpdatalen) अणु
					/* Yes, there was a TPKT header
					 * received */
					*data = tpkt;
					*datalen = info->tpkt_len[dir];
					*dataoff = 0;
					जाओ out;
				पूर्ण

				/* Fragmented TPKT */
				pr_debug("nf_ct_h323: fragmented TPKT\n");
				जाओ clear_out;
			पूर्ण

			/* It is not even a TPKT */
			वापस 0;
		पूर्ण
		tpktoff = 0;
	पूर्ण अन्यथा अणु		/* Next TPKT */
		tpktoff = *dataoff + *datalen;
		tcpdatalen -= tpktoff;
		अगर (tcpdatalen <= 4)	/* No more TPKT */
			जाओ clear_out;
		tpkt = *data + *datalen;

		/* Validate TPKT identअगरier */
		अगर (tpkt[0] != 0x03 || tpkt[1] != 0)
			जाओ clear_out;
	पूर्ण

	/* Validate TPKT length */
	tpktlen = tpkt[2] * 256 + tpkt[3];
	अगर (tpktlen < 4)
		जाओ clear_out;
	अगर (tpktlen > tcpdatalen) अणु
		अगर (tcpdatalen == 4) अणु	/* Separate TPKT header */
			/* Neपंचांगeeting sends TPKT header and data separately */
			pr_debug("nf_ct_h323: separate TPKT header indicates "
				 "there will be TPKT data of %hu bytes\n",
				 tpktlen - 4);
			info->tpkt_len[dir] = tpktlen - 4;
			वापस 0;
		पूर्ण

		pr_debug("nf_ct_h323: incomplete TPKT (fragmented?)\n");
		जाओ clear_out;
	पूर्ण

	/* This is the encapsulated data */
	*data = tpkt + 4;
	*datalen = tpktlen - 4;
	*dataoff = tpktoff + 4;

      out:
	/* Clear TPKT length */
	info->tpkt_len[dir] = 0;
	वापस 1;

      clear_out:
	info->tpkt_len[dir] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक get_h245_addr(काष्ठा nf_conn *ct, स्थिर अचिन्हित अक्षर *data,
			 H245_TransportAddress *taddr,
			 जोड़ nf_inet_addr *addr, __be16 *port)
अणु
	स्थिर अचिन्हित अक्षर *p;
	पूर्णांक len;

	अगर (taddr->choice != eH245_TransportAddress_unicastAddress)
		वापस 0;

	चयन (taddr->unicastAddress.choice) अणु
	हाल eUnicastAddress_iPAddress:
		अगर (nf_ct_l3num(ct) != AF_INET)
			वापस 0;
		p = data + taddr->unicastAddress.iPAddress.network;
		len = 4;
		अवरोध;
	हाल eUnicastAddress_iP6Address:
		अगर (nf_ct_l3num(ct) != AF_INET6)
			वापस 0;
		p = data + taddr->unicastAddress.iP6Address.network;
		len = 16;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	स_नकल(addr, p, len);
	स_रखो((व्योम *)addr + len, 0, माप(*addr) - len);
	स_नकल(port, p + len, माप(__be16));

	वापस 1;
पूर्ण

अटल पूर्णांक expect_rtp_rtcp(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			   क्रमागत ip_conntrack_info ctinfo,
			   अचिन्हित पूर्णांक protoff,
			   अचिन्हित अक्षर **data, पूर्णांक dataoff,
			   H245_TransportAddress *taddr)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret = 0;
	__be16 port;
	__be16 rtp_port, rtcp_port;
	जोड़ nf_inet_addr addr;
	काष्ठा nf_conntrack_expect *rtp_exp;
	काष्ठा nf_conntrack_expect *rtcp_exp;
	typeof(nat_rtp_rtcp_hook) nat_rtp_rtcp;

	/* Read RTP or RTCP address */
	अगर (!get_h245_addr(ct, *data, taddr, &addr, &port) ||
	    स_भेद(&addr, &ct->tuplehash[dir].tuple.src.u3, माप(addr)) ||
	    port == 0)
		वापस 0;

	/* RTP port is even */
	rtp_port = port & ~htons(1);
	rtcp_port = port | htons(1);

	/* Create expect क्रम RTP */
	अगर ((rtp_exp = nf_ct_expect_alloc(ct)) == शून्य)
		वापस -1;
	nf_ct_expect_init(rtp_exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &ct->tuplehash[!dir].tuple.src.u3,
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  IPPROTO_UDP, शून्य, &rtp_port);

	/* Create expect क्रम RTCP */
	अगर ((rtcp_exp = nf_ct_expect_alloc(ct)) == शून्य) अणु
		nf_ct_expect_put(rtp_exp);
		वापस -1;
	पूर्ण
	nf_ct_expect_init(rtcp_exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &ct->tuplehash[!dir].tuple.src.u3,
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  IPPROTO_UDP, शून्य, &rtcp_port);

	अगर (स_भेद(&ct->tuplehash[dir].tuple.src.u3,
		   &ct->tuplehash[!dir].tuple.dst.u3,
		   माप(ct->tuplehash[dir].tuple.src.u3)) &&
		   (nat_rtp_rtcp = rcu_dereference(nat_rtp_rtcp_hook)) &&
		   nf_ct_l3num(ct) == NFPROTO_IPV4 &&
		   ct->status & IPS_NAT_MASK) अणु
		/* NAT needed */
		ret = nat_rtp_rtcp(skb, ct, ctinfo, protoff, data, dataoff,
				   taddr, port, rtp_port, rtp_exp, rtcp_exp);
	पूर्ण अन्यथा अणु		/* Conntrack only */
		अगर (nf_ct_expect_related(rtp_exp, 0) == 0) अणु
			अगर (nf_ct_expect_related(rtcp_exp, 0) == 0) अणु
				pr_debug("nf_ct_h323: expect RTP ");
				nf_ct_dump_tuple(&rtp_exp->tuple);
				pr_debug("nf_ct_h323: expect RTCP ");
				nf_ct_dump_tuple(&rtcp_exp->tuple);
			पूर्ण अन्यथा अणु
				nf_ct_unexpect_related(rtp_exp);
				ret = -1;
			पूर्ण
		पूर्ण अन्यथा
			ret = -1;
	पूर्ण

	nf_ct_expect_put(rtp_exp);
	nf_ct_expect_put(rtcp_exp);

	वापस ret;
पूर्ण

अटल पूर्णांक expect_t120(काष्ठा sk_buff *skb,
		       काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, पूर्णांक dataoff,
		       H245_TransportAddress *taddr)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret = 0;
	__be16 port;
	जोड़ nf_inet_addr addr;
	काष्ठा nf_conntrack_expect *exp;
	typeof(nat_t120_hook) nat_t120;

	/* Read T.120 address */
	अगर (!get_h245_addr(ct, *data, taddr, &addr, &port) ||
	    स_भेद(&addr, &ct->tuplehash[dir].tuple.src.u3, माप(addr)) ||
	    port == 0)
		वापस 0;

	/* Create expect क्रम T.120 connections */
	अगर ((exp = nf_ct_expect_alloc(ct)) == शून्य)
		वापस -1;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &ct->tuplehash[!dir].tuple.src.u3,
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  IPPROTO_TCP, शून्य, &port);
	exp->flags = NF_CT_EXPECT_PERMANENT;	/* Accept multiple channels */

	अगर (स_भेद(&ct->tuplehash[dir].tuple.src.u3,
		   &ct->tuplehash[!dir].tuple.dst.u3,
		   माप(ct->tuplehash[dir].tuple.src.u3)) &&
	    (nat_t120 = rcu_dereference(nat_t120_hook)) &&
	    nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK) अणु
		/* NAT needed */
		ret = nat_t120(skb, ct, ctinfo, protoff, data, dataoff, taddr,
			       port, exp);
	पूर्ण अन्यथा अणु		/* Conntrack only */
		अगर (nf_ct_expect_related(exp, 0) == 0) अणु
			pr_debug("nf_ct_h323: expect T.120 ");
			nf_ct_dump_tuple(&exp->tuple);
		पूर्ण अन्यथा
			ret = -1;
	पूर्ण

	nf_ct_expect_put(exp);

	वापस ret;
पूर्ण

अटल पूर्णांक process_h245_channel(काष्ठा sk_buff *skb,
				काष्ठा nf_conn *ct,
				क्रमागत ip_conntrack_info ctinfo,
				अचिन्हित पूर्णांक protoff,
				अचिन्हित अक्षर **data, पूर्णांक dataoff,
				H2250LogicalChannelParameters *channel)
अणु
	पूर्णांक ret;

	अगर (channel->options & eH2250LogicalChannelParameters_mediaChannel) अणु
		/* RTP */
		ret = expect_rtp_rtcp(skb, ct, ctinfo, protoff, data, dataoff,
				      &channel->mediaChannel);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर (channel->
	    options & eH2250LogicalChannelParameters_mediaControlChannel) अणु
		/* RTCP */
		ret = expect_rtp_rtcp(skb, ct, ctinfo, protoff, data, dataoff,
				      &channel->mediaControlChannel);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_olc(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, पूर्णांक dataoff,
		       OpenLogicalChannel *olc)
अणु
	पूर्णांक ret;

	pr_debug("nf_ct_h323: OpenLogicalChannel\n");

	अगर (olc->क्रमwardLogicalChannelParameters.multiplexParameters.choice ==
	    eOpenLogicalChannel_क्रमwardLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters)
	अणु
		ret = process_h245_channel(skb, ct, ctinfo,
					   protoff, data, dataoff,
					   &olc->
					   क्रमwardLogicalChannelParameters.
					   multiplexParameters.
					   h2250LogicalChannelParameters);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर ((olc->options &
	     eOpenLogicalChannel_reverseLogicalChannelParameters) &&
	    (olc->reverseLogicalChannelParameters.options &
	     eOpenLogicalChannel_reverseLogicalChannelParameters_multiplexParameters)
	    && (olc->reverseLogicalChannelParameters.multiplexParameters.
		choice ==
		eOpenLogicalChannel_reverseLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters))
	अणु
		ret =
		    process_h245_channel(skb, ct, ctinfo,
					 protoff, data, dataoff,
					 &olc->
					 reverseLogicalChannelParameters.
					 multiplexParameters.
					 h2250LogicalChannelParameters);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर ((olc->options & eOpenLogicalChannel_separateStack) &&
	    olc->क्रमwardLogicalChannelParameters.dataType.choice ==
	    eDataType_data &&
	    olc->क्रमwardLogicalChannelParameters.dataType.data.application.
	    choice == eDataApplicationCapability_application_t120 &&
	    olc->क्रमwardLogicalChannelParameters.dataType.data.application.
	    t120.choice == eDataProtocolCapability_separateLANStack &&
	    olc->separateStack.networkAddress.choice ==
	    eNetworkAccessParameters_networkAddress_localAreaAddress) अणु
		ret = expect_t120(skb, ct, ctinfo, protoff, data, dataoff,
				  &olc->separateStack.networkAddress.
				  localAreaAddress);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_olca(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			क्रमागत ip_conntrack_info ctinfo,
			अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data, पूर्णांक dataoff,
			OpenLogicalChannelAck *olca)
अणु
	H2250LogicalChannelAckParameters *ack;
	पूर्णांक ret;

	pr_debug("nf_ct_h323: OpenLogicalChannelAck\n");

	अगर ((olca->options &
	     eOpenLogicalChannelAck_reverseLogicalChannelParameters) &&
	    (olca->reverseLogicalChannelParameters.options &
	     eOpenLogicalChannelAck_reverseLogicalChannelParameters_multiplexParameters)
	    && (olca->reverseLogicalChannelParameters.multiplexParameters.
		choice ==
		eOpenLogicalChannelAck_reverseLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters))
	अणु
		ret = process_h245_channel(skb, ct, ctinfo,
					   protoff, data, dataoff,
					   &olca->
					   reverseLogicalChannelParameters.
					   multiplexParameters.
					   h2250LogicalChannelParameters);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर ((olca->options &
	     eOpenLogicalChannelAck_क्रमwardMultiplexAckParameters) &&
	    (olca->क्रमwardMultiplexAckParameters.choice ==
	     eOpenLogicalChannelAck_क्रमwardMultiplexAckParameters_h2250LogicalChannelAckParameters))
	अणु
		ack = &olca->क्रमwardMultiplexAckParameters.
		    h2250LogicalChannelAckParameters;
		अगर (ack->options &
		    eH2250LogicalChannelAckParameters_mediaChannel) अणु
			/* RTP */
			ret = expect_rtp_rtcp(skb, ct, ctinfo,
					      protoff, data, dataoff,
					      &ack->mediaChannel);
			अगर (ret < 0)
				वापस -1;
		पूर्ण

		अगर (ack->options &
		    eH2250LogicalChannelAckParameters_mediaControlChannel) अणु
			/* RTCP */
			ret = expect_rtp_rtcp(skb, ct, ctinfo,
					      protoff, data, dataoff,
					      &ack->mediaControlChannel);
			अगर (ret < 0)
				वापस -1;
		पूर्ण
	पूर्ण

	अगर ((olca->options & eOpenLogicalChannelAck_separateStack) &&
		olca->separateStack.networkAddress.choice ==
		eNetworkAccessParameters_networkAddress_localAreaAddress) अणु
		ret = expect_t120(skb, ct, ctinfo, protoff, data, dataoff,
				  &olca->separateStack.networkAddress.
				  localAreaAddress);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_h245(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			क्रमागत ip_conntrack_info ctinfo,
			अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data, पूर्णांक dataoff,
			MulसमयdiaSystemControlMessage *mscm)
अणु
	चयन (mscm->choice) अणु
	हाल eMulसमयdiaSystemControlMessage_request:
		अगर (mscm->request.choice ==
		    eRequestMessage_खोलोLogicalChannel) अणु
			वापस process_olc(skb, ct, ctinfo,
					   protoff, data, dataoff,
					   &mscm->request.खोलोLogicalChannel);
		पूर्ण
		pr_debug("nf_ct_h323: H.245 Request %d\n",
			 mscm->request.choice);
		अवरोध;
	हाल eMulसमयdiaSystemControlMessage_response:
		अगर (mscm->response.choice ==
		    eResponseMessage_खोलोLogicalChannelAck) अणु
			वापस process_olca(skb, ct, ctinfo,
					    protoff, data, dataoff,
					    &mscm->response.
					    खोलोLogicalChannelAck);
		पूर्ण
		pr_debug("nf_ct_h323: H.245 Response %d\n",
			 mscm->response.choice);
		अवरोध;
	शेष:
		pr_debug("nf_ct_h323: H.245 signal %d\n", mscm->choice);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक h245_help(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		     काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo)
अणु
	अटल MulसमयdiaSystemControlMessage mscm;
	अचिन्हित अक्षर *data = शून्य;
	पूर्णांक datalen;
	पूर्णांक dataoff;
	पूर्णांक ret;

	/* Until there's been traffic both ways, don't look in packets. */
	अगर (ctinfo != IP_CT_ESTABLISHED && ctinfo != IP_CT_ESTABLISHED_REPLY)
		वापस NF_ACCEPT;

	pr_debug("nf_ct_h245: skblen = %u\n", skb->len);

	spin_lock_bh(&nf_h323_lock);

	/* Process each TPKT */
	जबतक (get_tpkt_data(skb, protoff, ct, ctinfo,
			     &data, &datalen, &dataoff)) अणु
		pr_debug("nf_ct_h245: TPKT len=%d ", datalen);
		nf_ct_dump_tuple(&ct->tuplehash[CTINFO2सूची(ctinfo)].tuple);

		/* Decode H.245 संकेत */
		ret = DecodeMulसमयdiaSystemControlMessage(data, datalen,
							   &mscm);
		अगर (ret < 0) अणु
			pr_debug("nf_ct_h245: decoding error: %s\n",
				 ret == H323_ERROR_BOUND ?
				 "out of bound" : "out of range");
			/* We करोn't drop when decoding error */
			अवरोध;
		पूर्ण

		/* Process H.245 संकेत */
		अगर (process_h245(skb, ct, ctinfo, protoff,
				 &data, dataoff, &mscm) < 0)
			जाओ drop;
	पूर्ण

	spin_unlock_bh(&nf_h323_lock);
	वापस NF_ACCEPT;

      drop:
	spin_unlock_bh(&nf_h323_lock);
	nf_ct_helper_log(skb, ct, "cannot process H.245 message");
	वापस NF_DROP;
पूर्ण

अटल स्थिर काष्ठा nf_conntrack_expect_policy h245_exp_policy = अणु
	.max_expected	= H323_RTP_CHANNEL_MAX * 4 + 2 /* T.120 */,
	.समयout	= 240,
पूर्ण;

अटल काष्ठा nf_conntrack_helper nf_conntrack_helper_h245 __पढ़ो_mostly = अणु
	.name			= "H.245",
	.me			= THIS_MODULE,
	.tuple.src.l3num	= AF_UNSPEC,
	.tuple.dst.protonum	= IPPROTO_UDP,
	.help			= h245_help,
	.expect_policy		= &h245_exp_policy,
पूर्ण;

पूर्णांक get_h225_addr(काष्ठा nf_conn *ct, अचिन्हित अक्षर *data,
		  TransportAddress *taddr,
		  जोड़ nf_inet_addr *addr, __be16 *port)
अणु
	स्थिर अचिन्हित अक्षर *p;
	पूर्णांक len;

	चयन (taddr->choice) अणु
	हाल eTransportAddress_ipAddress:
		अगर (nf_ct_l3num(ct) != AF_INET)
			वापस 0;
		p = data + taddr->ipAddress.ip;
		len = 4;
		अवरोध;
	हाल eTransportAddress_ip6Address:
		अगर (nf_ct_l3num(ct) != AF_INET6)
			वापस 0;
		p = data + taddr->ip6Address.ip;
		len = 16;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	स_नकल(addr, p, len);
	स_रखो((व्योम *)addr + len, 0, माप(*addr) - len);
	स_नकल(port, p + len, माप(__be16));

	वापस 1;
पूर्ण

अटल पूर्णांक expect_h245(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data, पूर्णांक dataoff,
		       TransportAddress *taddr)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret = 0;
	__be16 port;
	जोड़ nf_inet_addr addr;
	काष्ठा nf_conntrack_expect *exp;
	typeof(nat_h245_hook) nat_h245;

	/* Read h245Address */
	अगर (!get_h225_addr(ct, *data, taddr, &addr, &port) ||
	    स_भेद(&addr, &ct->tuplehash[dir].tuple.src.u3, माप(addr)) ||
	    port == 0)
		वापस 0;

	/* Create expect क्रम h245 connection */
	अगर ((exp = nf_ct_expect_alloc(ct)) == शून्य)
		वापस -1;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &ct->tuplehash[!dir].tuple.src.u3,
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  IPPROTO_TCP, शून्य, &port);
	exp->helper = &nf_conntrack_helper_h245;

	अगर (स_भेद(&ct->tuplehash[dir].tuple.src.u3,
		   &ct->tuplehash[!dir].tuple.dst.u3,
		   माप(ct->tuplehash[dir].tuple.src.u3)) &&
	    (nat_h245 = rcu_dereference(nat_h245_hook)) &&
	    nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK) अणु
		/* NAT needed */
		ret = nat_h245(skb, ct, ctinfo, protoff, data, dataoff, taddr,
			       port, exp);
	पूर्ण अन्यथा अणु		/* Conntrack only */
		अगर (nf_ct_expect_related(exp, 0) == 0) अणु
			pr_debug("nf_ct_q931: expect H.245 ");
			nf_ct_dump_tuple(&exp->tuple);
		पूर्ण अन्यथा
			ret = -1;
	पूर्ण

	nf_ct_expect_put(exp);

	वापस ret;
पूर्ण

/* If the calling party is on the same side of the क्रमward-to party,
 * we करोn't need to track the second call
 */
अटल पूर्णांक callक्रमward_करो_filter(काष्ठा net *net,
				 स्थिर जोड़ nf_inet_addr *src,
				 स्थिर जोड़ nf_inet_addr *dst,
				 u_पूर्णांक8_t family)
अणु
	पूर्णांक ret = 0;

	चयन (family) अणु
	हाल AF_INET: अणु
		काष्ठा flowi4 fl1, fl2;
		काष्ठा rtable *rt1, *rt2;

		स_रखो(&fl1, 0, माप(fl1));
		fl1.daddr = src->ip;

		स_रखो(&fl2, 0, माप(fl2));
		fl2.daddr = dst->ip;
		अगर (!nf_ip_route(net, (काष्ठा dst_entry **)&rt1,
				 flowi4_to_flowi(&fl1), false)) अणु
			अगर (!nf_ip_route(net, (काष्ठा dst_entry **)&rt2,
					 flowi4_to_flowi(&fl2), false)) अणु
				अगर (rt_nexthop(rt1, fl1.daddr) ==
				    rt_nexthop(rt2, fl2.daddr) &&
				    rt1->dst.dev  == rt2->dst.dev)
					ret = 1;
				dst_release(&rt2->dst);
			पूर्ण
			dst_release(&rt1->dst);
		पूर्ण
		अवरोध;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6: अणु
		काष्ठा rt6_info *rt1, *rt2;
		काष्ठा flowi6 fl1, fl2;

		स_रखो(&fl1, 0, माप(fl1));
		fl1.daddr = src->in6;

		स_रखो(&fl2, 0, माप(fl2));
		fl2.daddr = dst->in6;
		अगर (!nf_ip6_route(net, (काष्ठा dst_entry **)&rt1,
				  flowi6_to_flowi(&fl1), false)) अणु
			अगर (!nf_ip6_route(net, (काष्ठा dst_entry **)&rt2,
					  flowi6_to_flowi(&fl2), false)) अणु
				अगर (ipv6_addr_equal(rt6_nexthop(rt1, &fl1.daddr),
						    rt6_nexthop(rt2, &fl2.daddr)) &&
				    rt1->dst.dev == rt2->dst.dev)
					ret = 1;
				dst_release(&rt2->dst);
			पूर्ण
			dst_release(&rt1->dst);
		पूर्ण
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस ret;

पूर्ण

अटल पूर्णांक expect_callक्रमwarding(काष्ठा sk_buff *skb,
				 काष्ठा nf_conn *ct,
				 क्रमागत ip_conntrack_info ctinfo,
				 अचिन्हित पूर्णांक protoff,
				 अचिन्हित अक्षर **data, पूर्णांक dataoff,
				 TransportAddress *taddr)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret = 0;
	__be16 port;
	जोड़ nf_inet_addr addr;
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा net *net = nf_ct_net(ct);
	typeof(nat_callक्रमwarding_hook) nat_callक्रमwarding;

	/* Read alternativeAddress */
	अगर (!get_h225_addr(ct, *data, taddr, &addr, &port) || port == 0)
		वापस 0;

	/* If the calling party is on the same side of the क्रमward-to party,
	 * we करोn't need to track the second call
	 */
	अगर (callक्रमward_filter &&
	    callक्रमward_करो_filter(net, &addr, &ct->tuplehash[!dir].tuple.src.u3,
				  nf_ct_l3num(ct))) अणु
		pr_debug("nf_ct_q931: Call Forwarding not tracked\n");
		वापस 0;
	पूर्ण

	/* Create expect क्रम the second call leg */
	अगर ((exp = nf_ct_expect_alloc(ct)) == शून्य)
		वापस -1;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &ct->tuplehash[!dir].tuple.src.u3, &addr,
			  IPPROTO_TCP, शून्य, &port);
	exp->helper = nf_conntrack_helper_q931;

	अगर (स_भेद(&ct->tuplehash[dir].tuple.src.u3,
		   &ct->tuplehash[!dir].tuple.dst.u3,
		   माप(ct->tuplehash[dir].tuple.src.u3)) &&
	    (nat_callक्रमwarding = rcu_dereference(nat_callक्रमwarding_hook)) &&
	    nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK) अणु
		/* Need NAT */
		ret = nat_callक्रमwarding(skb, ct, ctinfo,
					 protoff, data, dataoff,
					 taddr, port, exp);
	पूर्ण अन्यथा अणु		/* Conntrack only */
		अगर (nf_ct_expect_related(exp, 0) == 0) अणु
			pr_debug("nf_ct_q931: expect Call Forwarding ");
			nf_ct_dump_tuple(&exp->tuple);
		पूर्ण अन्यथा
			ret = -1;
	पूर्ण

	nf_ct_expect_put(exp);

	वापस ret;
पूर्ण

अटल पूर्णांक process_setup(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			 क्रमागत ip_conntrack_info ctinfo,
			 अचिन्हित पूर्णांक protoff,
			 अचिन्हित अक्षर **data, पूर्णांक dataoff,
			 Setup_UUIE *setup)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret;
	पूर्णांक i;
	__be16 port;
	जोड़ nf_inet_addr addr;
	typeof(set_h225_addr_hook) set_h225_addr;

	pr_debug("nf_ct_q931: Setup\n");

	अगर (setup->options & eSetup_UUIE_h245Address) अणु
		ret = expect_h245(skb, ct, ctinfo, protoff, data, dataoff,
				  &setup->h245Address);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	set_h225_addr = rcu_dereference(set_h225_addr_hook);
	अगर ((setup->options & eSetup_UUIE_destCallSignalAddress) &&
	    (set_h225_addr) && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK &&
	    get_h225_addr(ct, *data, &setup->destCallSignalAddress,
			  &addr, &port) &&
	    स_भेद(&addr, &ct->tuplehash[!dir].tuple.src.u3, माप(addr))) अणु
		pr_debug("nf_ct_q931: set destCallSignalAddress %pI6:%hu->%pI6:%hu\n",
			 &addr, ntohs(port), &ct->tuplehash[!dir].tuple.src.u3,
			 ntohs(ct->tuplehash[!dir].tuple.src.u.tcp.port));
		ret = set_h225_addr(skb, protoff, data, dataoff,
				    &setup->destCallSignalAddress,
				    &ct->tuplehash[!dir].tuple.src.u3,
				    ct->tuplehash[!dir].tuple.src.u.tcp.port);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर ((setup->options & eSetup_UUIE_sourceCallSignalAddress) &&
	    (set_h225_addr) && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK &&
	    get_h225_addr(ct, *data, &setup->sourceCallSignalAddress,
			  &addr, &port) &&
	    स_भेद(&addr, &ct->tuplehash[!dir].tuple.dst.u3, माप(addr))) अणु
		pr_debug("nf_ct_q931: set sourceCallSignalAddress %pI6:%hu->%pI6:%hu\n",
			 &addr, ntohs(port), &ct->tuplehash[!dir].tuple.dst.u3,
			 ntohs(ct->tuplehash[!dir].tuple.dst.u.tcp.port));
		ret = set_h225_addr(skb, protoff, data, dataoff,
				    &setup->sourceCallSignalAddress,
				    &ct->tuplehash[!dir].tuple.dst.u3,
				    ct->tuplehash[!dir].tuple.dst.u.tcp.port);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर (setup->options & eSetup_UUIE_fastStart) अणु
		क्रम (i = 0; i < setup->fastStart.count; i++) अणु
			ret = process_olc(skb, ct, ctinfo,
					  protoff, data, dataoff,
					  &setup->fastStart.item[i]);
			अगर (ret < 0)
				वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_callproceeding(काष्ठा sk_buff *skb,
				  काष्ठा nf_conn *ct,
				  क्रमागत ip_conntrack_info ctinfo,
				  अचिन्हित पूर्णांक protoff,
				  अचिन्हित अक्षर **data, पूर्णांक dataoff,
				  CallProceeding_UUIE *callproc)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	pr_debug("nf_ct_q931: CallProceeding\n");

	अगर (callproc->options & eCallProceeding_UUIE_h245Address) अणु
		ret = expect_h245(skb, ct, ctinfo, protoff, data, dataoff,
				  &callproc->h245Address);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर (callproc->options & eCallProceeding_UUIE_fastStart) अणु
		क्रम (i = 0; i < callproc->fastStart.count; i++) अणु
			ret = process_olc(skb, ct, ctinfo,
					  protoff, data, dataoff,
					  &callproc->fastStart.item[i]);
			अगर (ret < 0)
				वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_connect(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			   क्रमागत ip_conntrack_info ctinfo,
			   अचिन्हित पूर्णांक protoff,
			   अचिन्हित अक्षर **data, पूर्णांक dataoff,
			   Connect_UUIE *connect)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	pr_debug("nf_ct_q931: Connect\n");

	अगर (connect->options & eConnect_UUIE_h245Address) अणु
		ret = expect_h245(skb, ct, ctinfo, protoff, data, dataoff,
				  &connect->h245Address);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर (connect->options & eConnect_UUIE_fastStart) अणु
		क्रम (i = 0; i < connect->fastStart.count; i++) अणु
			ret = process_olc(skb, ct, ctinfo,
					  protoff, data, dataoff,
					  &connect->fastStart.item[i]);
			अगर (ret < 0)
				वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_alerting(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			    क्रमागत ip_conntrack_info ctinfo,
			    अचिन्हित पूर्णांक protoff,
			    अचिन्हित अक्षर **data, पूर्णांक dataoff,
			    Alerting_UUIE *alert)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	pr_debug("nf_ct_q931: Alerting\n");

	अगर (alert->options & eAlerting_UUIE_h245Address) अणु
		ret = expect_h245(skb, ct, ctinfo, protoff, data, dataoff,
				  &alert->h245Address);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर (alert->options & eAlerting_UUIE_fastStart) अणु
		क्रम (i = 0; i < alert->fastStart.count; i++) अणु
			ret = process_olc(skb, ct, ctinfo,
					  protoff, data, dataoff,
					  &alert->fastStart.item[i]);
			अगर (ret < 0)
				वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_facility(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			    क्रमागत ip_conntrack_info ctinfo,
			    अचिन्हित पूर्णांक protoff,
			    अचिन्हित अक्षर **data, पूर्णांक dataoff,
			    Facility_UUIE *facility)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	pr_debug("nf_ct_q931: Facility\n");

	अगर (facility->reason.choice == eFacilityReason_callForwarded) अणु
		अगर (facility->options & eFacility_UUIE_alternativeAddress)
			वापस expect_callक्रमwarding(skb, ct, ctinfo,
						     protoff, data, dataoff,
						     &facility->
						     alternativeAddress);
		वापस 0;
	पूर्ण

	अगर (facility->options & eFacility_UUIE_h245Address) अणु
		ret = expect_h245(skb, ct, ctinfo, protoff, data, dataoff,
				  &facility->h245Address);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर (facility->options & eFacility_UUIE_fastStart) अणु
		क्रम (i = 0; i < facility->fastStart.count; i++) अणु
			ret = process_olc(skb, ct, ctinfo,
					  protoff, data, dataoff,
					  &facility->fastStart.item[i]);
			अगर (ret < 0)
				वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_progress(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			    क्रमागत ip_conntrack_info ctinfo,
			    अचिन्हित पूर्णांक protoff,
			    अचिन्हित अक्षर **data, पूर्णांक dataoff,
			    Progress_UUIE *progress)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	pr_debug("nf_ct_q931: Progress\n");

	अगर (progress->options & eProgress_UUIE_h245Address) अणु
		ret = expect_h245(skb, ct, ctinfo, protoff, data, dataoff,
				  &progress->h245Address);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर (progress->options & eProgress_UUIE_fastStart) अणु
		क्रम (i = 0; i < progress->fastStart.count; i++) अणु
			ret = process_olc(skb, ct, ctinfo,
					  protoff, data, dataoff,
					  &progress->fastStart.item[i]);
			अगर (ret < 0)
				वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_q931(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			क्रमागत ip_conntrack_info ctinfo,
			अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data, पूर्णांक dataoff,
			Q931 *q931)
अणु
	H323_UU_PDU *pdu = &q931->UUIE.h323_uu_pdu;
	पूर्णांक i;
	पूर्णांक ret = 0;

	चयन (pdu->h323_message_body.choice) अणु
	हाल eH323_UU_PDU_h323_message_body_setup:
		ret = process_setup(skb, ct, ctinfo, protoff, data, dataoff,
				    &pdu->h323_message_body.setup);
		अवरोध;
	हाल eH323_UU_PDU_h323_message_body_callProceeding:
		ret = process_callproceeding(skb, ct, ctinfo,
					     protoff, data, dataoff,
					     &pdu->h323_message_body.
					     callProceeding);
		अवरोध;
	हाल eH323_UU_PDU_h323_message_body_connect:
		ret = process_connect(skb, ct, ctinfo, protoff, data, dataoff,
				      &pdu->h323_message_body.connect);
		अवरोध;
	हाल eH323_UU_PDU_h323_message_body_alerting:
		ret = process_alerting(skb, ct, ctinfo, protoff, data, dataoff,
				       &pdu->h323_message_body.alerting);
		अवरोध;
	हाल eH323_UU_PDU_h323_message_body_facility:
		ret = process_facility(skb, ct, ctinfo, protoff, data, dataoff,
				       &pdu->h323_message_body.facility);
		अवरोध;
	हाल eH323_UU_PDU_h323_message_body_progress:
		ret = process_progress(skb, ct, ctinfo, protoff, data, dataoff,
				       &pdu->h323_message_body.progress);
		अवरोध;
	शेष:
		pr_debug("nf_ct_q931: Q.931 signal %d\n",
			 pdu->h323_message_body.choice);
		अवरोध;
	पूर्ण

	अगर (ret < 0)
		वापस -1;

	अगर (pdu->options & eH323_UU_PDU_h245Control) अणु
		क्रम (i = 0; i < pdu->h245Control.count; i++) अणु
			ret = process_h245(skb, ct, ctinfo,
					   protoff, data, dataoff,
					   &pdu->h245Control.item[i]);
			अगर (ret < 0)
				वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q931_help(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		     काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo)
अणु
	अटल Q931 q931;
	अचिन्हित अक्षर *data = शून्य;
	पूर्णांक datalen;
	पूर्णांक dataoff;
	पूर्णांक ret;

	/* Until there's been traffic both ways, don't look in packets. */
	अगर (ctinfo != IP_CT_ESTABLISHED && ctinfo != IP_CT_ESTABLISHED_REPLY)
		वापस NF_ACCEPT;

	pr_debug("nf_ct_q931: skblen = %u\n", skb->len);

	spin_lock_bh(&nf_h323_lock);

	/* Process each TPKT */
	जबतक (get_tpkt_data(skb, protoff, ct, ctinfo,
			     &data, &datalen, &dataoff)) अणु
		pr_debug("nf_ct_q931: TPKT len=%d ", datalen);
		nf_ct_dump_tuple(&ct->tuplehash[CTINFO2सूची(ctinfo)].tuple);

		/* Decode Q.931 संकेत */
		ret = DecodeQ931(data, datalen, &q931);
		अगर (ret < 0) अणु
			pr_debug("nf_ct_q931: decoding error: %s\n",
				 ret == H323_ERROR_BOUND ?
				 "out of bound" : "out of range");
			/* We करोn't drop when decoding error */
			अवरोध;
		पूर्ण

		/* Process Q.931 संकेत */
		अगर (process_q931(skb, ct, ctinfo, protoff,
				 &data, dataoff, &q931) < 0)
			जाओ drop;
	पूर्ण

	spin_unlock_bh(&nf_h323_lock);
	वापस NF_ACCEPT;

      drop:
	spin_unlock_bh(&nf_h323_lock);
	nf_ct_helper_log(skb, ct, "cannot process Q.931 message");
	वापस NF_DROP;
पूर्ण

अटल स्थिर काष्ठा nf_conntrack_expect_policy q931_exp_policy = अणु
	/* T.120 and H.245 */
	.max_expected		= H323_RTP_CHANNEL_MAX * 4 + 4,
	.समयout		= 240,
पूर्ण;

अटल काष्ठा nf_conntrack_helper nf_conntrack_helper_q931[] __पढ़ो_mostly = अणु
	अणु
		.name			= "Q.931",
		.me			= THIS_MODULE,
		.tuple.src.l3num	= AF_INET,
		.tuple.src.u.tcp.port	= cpu_to_be16(Q931_PORT),
		.tuple.dst.protonum	= IPPROTO_TCP,
		.help			= q931_help,
		.expect_policy		= &q931_exp_policy,
	पूर्ण,
	अणु
		.name			= "Q.931",
		.me			= THIS_MODULE,
		.tuple.src.l3num	= AF_INET6,
		.tuple.src.u.tcp.port	= cpu_to_be16(Q931_PORT),
		.tuple.dst.protonum	= IPPROTO_TCP,
		.help			= q931_help,
		.expect_policy		= &q931_exp_policy,
	पूर्ण,
पूर्ण;

अटल अचिन्हित अक्षर *get_udp_data(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				   पूर्णांक *datalen)
अणु
	स्थिर काष्ठा udphdr *uh;
	काष्ठा udphdr _uh;
	पूर्णांक dataoff;

	uh = skb_header_poपूर्णांकer(skb, protoff, माप(_uh), &_uh);
	अगर (uh == शून्य)
		वापस शून्य;
	dataoff = protoff + माप(_uh);
	अगर (dataoff >= skb->len)
		वापस शून्य;
	*datalen = skb->len - dataoff;
	वापस skb_header_poपूर्णांकer(skb, dataoff, *datalen, h323_buffer);
पूर्ण

अटल काष्ठा nf_conntrack_expect *find_expect(काष्ठा nf_conn *ct,
					       जोड़ nf_inet_addr *addr,
					       __be16 port)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conntrack_tuple tuple;

	स_रखो(&tuple.src.u3, 0, माप(tuple.src.u3));
	tuple.src.u.tcp.port = 0;
	स_नकल(&tuple.dst.u3, addr, माप(tuple.dst.u3));
	tuple.dst.u.tcp.port = port;
	tuple.dst.protonum = IPPROTO_TCP;

	exp = __nf_ct_expect_find(net, nf_ct_zone(ct), &tuple);
	अगर (exp && exp->master == ct)
		वापस exp;
	वापस शून्य;
पूर्ण

अटल पूर्णांक expect_q931(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data,
		       TransportAddress *taddr, पूर्णांक count)
अणु
	काष्ठा nf_ct_h323_master *info = nfct_help_data(ct);
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret = 0;
	पूर्णांक i;
	__be16 port;
	जोड़ nf_inet_addr addr;
	काष्ठा nf_conntrack_expect *exp;
	typeof(nat_q931_hook) nat_q931;

	/* Look क्रम the first related address */
	क्रम (i = 0; i < count; i++) अणु
		अगर (get_h225_addr(ct, *data, &taddr[i], &addr, &port) &&
		    स_भेद(&addr, &ct->tuplehash[dir].tuple.src.u3,
			   माप(addr)) == 0 && port != 0)
			अवरोध;
	पूर्ण

	अगर (i >= count)		/* Not found */
		वापस 0;

	/* Create expect क्रम Q.931 */
	अगर ((exp = nf_ct_expect_alloc(ct)) == शून्य)
		वापस -1;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  gkrouted_only ? /* only accept calls from GK? */
				&ct->tuplehash[!dir].tuple.src.u3 : शून्य,
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  IPPROTO_TCP, शून्य, &port);
	exp->helper = nf_conntrack_helper_q931;
	exp->flags = NF_CT_EXPECT_PERMANENT;	/* Accept multiple calls */

	nat_q931 = rcu_dereference(nat_q931_hook);
	अगर (nat_q931 && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK) अणु	/* Need NAT */
		ret = nat_q931(skb, ct, ctinfo, protoff, data,
			       taddr, i, port, exp);
	पूर्ण अन्यथा अणु		/* Conntrack only */
		अगर (nf_ct_expect_related(exp, 0) == 0) अणु
			pr_debug("nf_ct_ras: expect Q.931 ");
			nf_ct_dump_tuple(&exp->tuple);

			/* Save port क्रम looking up expect in processing RCF */
			info->sig_port[dir] = port;
		पूर्ण अन्यथा
			ret = -1;
	पूर्ण

	nf_ct_expect_put(exp);

	वापस ret;
पूर्ण

अटल पूर्णांक process_grq(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, GatekeeperRequest *grq)
अणु
	typeof(set_ras_addr_hook) set_ras_addr;

	pr_debug("nf_ct_ras: GRQ\n");

	set_ras_addr = rcu_dereference(set_ras_addr_hook);
	अगर (set_ras_addr && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK)	/* NATed */
		वापस set_ras_addr(skb, ct, ctinfo, protoff, data,
				    &grq->rasAddress, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक process_gcf(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, GatekeeperConfirm *gcf)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret = 0;
	__be16 port;
	जोड़ nf_inet_addr addr;
	काष्ठा nf_conntrack_expect *exp;

	pr_debug("nf_ct_ras: GCF\n");

	अगर (!get_h225_addr(ct, *data, &gcf->rasAddress, &addr, &port))
		वापस 0;

	/* Registration port is the same as discovery port */
	अगर (!स_भेद(&addr, &ct->tuplehash[dir].tuple.src.u3, माप(addr)) &&
	    port == ct->tuplehash[dir].tuple.src.u.udp.port)
		वापस 0;

	/* Aव्योम RAS expectation loops. A GCF is never expected. */
	अगर (test_bit(IPS_EXPECTED_BIT, &ct->status))
		वापस 0;

	/* Need new expect */
	अगर ((exp = nf_ct_expect_alloc(ct)) == शून्य)
		वापस -1;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &ct->tuplehash[!dir].tuple.src.u3, &addr,
			  IPPROTO_UDP, शून्य, &port);
	exp->helper = nf_conntrack_helper_ras;

	अगर (nf_ct_expect_related(exp, 0) == 0) अणु
		pr_debug("nf_ct_ras: expect RAS ");
		nf_ct_dump_tuple(&exp->tuple);
	पूर्ण अन्यथा
		ret = -1;

	nf_ct_expect_put(exp);

	वापस ret;
पूर्ण

अटल पूर्णांक process_rrq(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, RegistrationRequest *rrq)
अणु
	काष्ठा nf_ct_h323_master *info = nfct_help_data(ct);
	पूर्णांक ret;
	typeof(set_ras_addr_hook) set_ras_addr;

	pr_debug("nf_ct_ras: RRQ\n");

	ret = expect_q931(skb, ct, ctinfo, protoff, data,
			  rrq->callSignalAddress.item,
			  rrq->callSignalAddress.count);
	अगर (ret < 0)
		वापस -1;

	set_ras_addr = rcu_dereference(set_ras_addr_hook);
	अगर (set_ras_addr && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK) अणु
		ret = set_ras_addr(skb, ct, ctinfo, protoff, data,
				   rrq->rasAddress.item,
				   rrq->rasAddress.count);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर (rrq->options & eRegistrationRequest_समयToLive) अणु
		pr_debug("nf_ct_ras: RRQ TTL = %u seconds\n", rrq->समयToLive);
		info->समयout = rrq->समयToLive;
	पूर्ण अन्यथा
		info->समयout = शेष_rrq_ttl;

	वापस 0;
पूर्ण

अटल पूर्णांक process_rcf(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, RegistrationConfirm *rcf)
अणु
	काष्ठा nf_ct_h323_master *info = nfct_help_data(ct);
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret;
	काष्ठा nf_conntrack_expect *exp;
	typeof(set_sig_addr_hook) set_sig_addr;

	pr_debug("nf_ct_ras: RCF\n");

	set_sig_addr = rcu_dereference(set_sig_addr_hook);
	अगर (set_sig_addr && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK) अणु
		ret = set_sig_addr(skb, ct, ctinfo, protoff, data,
					rcf->callSignalAddress.item,
					rcf->callSignalAddress.count);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	अगर (rcf->options & eRegistrationConfirm_समयToLive) अणु
		pr_debug("nf_ct_ras: RCF TTL = %u seconds\n", rcf->समयToLive);
		info->समयout = rcf->समयToLive;
	पूर्ण

	अगर (info->समयout > 0) अणु
		pr_debug("nf_ct_ras: set RAS connection timeout to "
			 "%u seconds\n", info->समयout);
		nf_ct_refresh(ct, skb, info->समयout * HZ);

		/* Set expect समयout */
		spin_lock_bh(&nf_conntrack_expect_lock);
		exp = find_expect(ct, &ct->tuplehash[dir].tuple.dst.u3,
				  info->sig_port[!dir]);
		अगर (exp) अणु
			pr_debug("nf_ct_ras: set Q.931 expect "
				 "timeout to %u seconds for",
				 info->समयout);
			nf_ct_dump_tuple(&exp->tuple);
			mod_समयr_pending(&exp->समयout,
					  jअगरfies + info->समयout * HZ);
		पूर्ण
		spin_unlock_bh(&nf_conntrack_expect_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_urq(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, UnregistrationRequest *urq)
अणु
	काष्ठा nf_ct_h323_master *info = nfct_help_data(ct);
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret;
	typeof(set_sig_addr_hook) set_sig_addr;

	pr_debug("nf_ct_ras: URQ\n");

	set_sig_addr = rcu_dereference(set_sig_addr_hook);
	अगर (set_sig_addr && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK) अणु
		ret = set_sig_addr(skb, ct, ctinfo, protoff, data,
				   urq->callSignalAddress.item,
				   urq->callSignalAddress.count);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	/* Clear old expect */
	nf_ct_हटाओ_expectations(ct);
	info->sig_port[dir] = 0;
	info->sig_port[!dir] = 0;

	/* Give it 30 seconds क्रम UCF or URJ */
	nf_ct_refresh(ct, skb, 30 * HZ);

	वापस 0;
पूर्ण

अटल पूर्णांक process_arq(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, AdmissionRequest *arq)
अणु
	स्थिर काष्ठा nf_ct_h323_master *info = nfct_help_data(ct);
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	__be16 port;
	जोड़ nf_inet_addr addr;
	typeof(set_h225_addr_hook) set_h225_addr;

	pr_debug("nf_ct_ras: ARQ\n");

	set_h225_addr = rcu_dereference(set_h225_addr_hook);
	अगर ((arq->options & eAdmissionRequest_destCallSignalAddress) &&
	    get_h225_addr(ct, *data, &arq->destCallSignalAddress,
			  &addr, &port) &&
	    !स_भेद(&addr, &ct->tuplehash[dir].tuple.src.u3, माप(addr)) &&
	    port == info->sig_port[dir] &&
	    nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    set_h225_addr && ct->status & IPS_NAT_MASK) अणु
		/* Answering ARQ */
		वापस set_h225_addr(skb, protoff, data, 0,
				     &arq->destCallSignalAddress,
				     &ct->tuplehash[!dir].tuple.dst.u3,
				     info->sig_port[!dir]);
	पूर्ण

	अगर ((arq->options & eAdmissionRequest_srcCallSignalAddress) &&
	    get_h225_addr(ct, *data, &arq->srcCallSignalAddress,
			  &addr, &port) &&
	    !स_भेद(&addr, &ct->tuplehash[dir].tuple.src.u3, माप(addr)) &&
	    set_h225_addr && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK) अणु
		/* Calling ARQ */
		वापस set_h225_addr(skb, protoff, data, 0,
				     &arq->srcCallSignalAddress,
				     &ct->tuplehash[!dir].tuple.dst.u3,
				     port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_acf(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, AdmissionConfirm *acf)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret = 0;
	__be16 port;
	जोड़ nf_inet_addr addr;
	काष्ठा nf_conntrack_expect *exp;
	typeof(set_sig_addr_hook) set_sig_addr;

	pr_debug("nf_ct_ras: ACF\n");

	अगर (!get_h225_addr(ct, *data, &acf->destCallSignalAddress,
			   &addr, &port))
		वापस 0;

	अगर (!स_भेद(&addr, &ct->tuplehash[dir].tuple.dst.u3, माप(addr))) अणु
		/* Answering ACF */
		set_sig_addr = rcu_dereference(set_sig_addr_hook);
		अगर (set_sig_addr && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
		    ct->status & IPS_NAT_MASK)
			वापस set_sig_addr(skb, ct, ctinfo, protoff, data,
					    &acf->destCallSignalAddress, 1);
		वापस 0;
	पूर्ण

	/* Need new expect */
	अगर ((exp = nf_ct_expect_alloc(ct)) == शून्य)
		वापस -1;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &ct->tuplehash[!dir].tuple.src.u3, &addr,
			  IPPROTO_TCP, शून्य, &port);
	exp->flags = NF_CT_EXPECT_PERMANENT;
	exp->helper = nf_conntrack_helper_q931;

	अगर (nf_ct_expect_related(exp, 0) == 0) अणु
		pr_debug("nf_ct_ras: expect Q.931 ");
		nf_ct_dump_tuple(&exp->tuple);
	पूर्ण अन्यथा
		ret = -1;

	nf_ct_expect_put(exp);

	वापस ret;
पूर्ण

अटल पूर्णांक process_lrq(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, LocationRequest *lrq)
अणु
	typeof(set_ras_addr_hook) set_ras_addr;

	pr_debug("nf_ct_ras: LRQ\n");

	set_ras_addr = rcu_dereference(set_ras_addr_hook);
	अगर (set_ras_addr && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK)
		वापस set_ras_addr(skb, ct, ctinfo, protoff, data,
				    &lrq->replyAddress, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक process_lcf(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, LocationConfirm *lcf)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक ret = 0;
	__be16 port;
	जोड़ nf_inet_addr addr;
	काष्ठा nf_conntrack_expect *exp;

	pr_debug("nf_ct_ras: LCF\n");

	अगर (!get_h225_addr(ct, *data, &lcf->callSignalAddress,
			   &addr, &port))
		वापस 0;

	/* Need new expect क्रम call संकेत */
	अगर ((exp = nf_ct_expect_alloc(ct)) == शून्य)
		वापस -1;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &ct->tuplehash[!dir].tuple.src.u3, &addr,
			  IPPROTO_TCP, शून्य, &port);
	exp->flags = NF_CT_EXPECT_PERMANENT;
	exp->helper = nf_conntrack_helper_q931;

	अगर (nf_ct_expect_related(exp, 0) == 0) अणु
		pr_debug("nf_ct_ras: expect Q.931 ");
		nf_ct_dump_tuple(&exp->tuple);
	पूर्ण अन्यथा
		ret = -1;

	nf_ct_expect_put(exp);

	/* Ignore rasAddress */

	वापस ret;
पूर्ण

अटल पूर्णांक process_irr(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, InfoRequestResponse *irr)
अणु
	पूर्णांक ret;
	typeof(set_ras_addr_hook) set_ras_addr;
	typeof(set_sig_addr_hook) set_sig_addr;

	pr_debug("nf_ct_ras: IRR\n");

	set_ras_addr = rcu_dereference(set_ras_addr_hook);
	अगर (set_ras_addr && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK) अणु
		ret = set_ras_addr(skb, ct, ctinfo, protoff, data,
				   &irr->rasAddress, 1);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	set_sig_addr = rcu_dereference(set_sig_addr_hook);
	अगर (set_sig_addr && nf_ct_l3num(ct) == NFPROTO_IPV4 &&
	    ct->status & IPS_NAT_MASK) अणु
		ret = set_sig_addr(skb, ct, ctinfo, protoff, data,
					irr->callSignalAddress.item,
					irr->callSignalAddress.count);
		अगर (ret < 0)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_ras(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       अचिन्हित पूर्णांक protoff,
		       अचिन्हित अक्षर **data, RasMessage *ras)
अणु
	चयन (ras->choice) अणु
	हाल eRasMessage_gatekeeperRequest:
		वापस process_grq(skb, ct, ctinfo, protoff, data,
				   &ras->gatekeeperRequest);
	हाल eRasMessage_gatekeeperConfirm:
		वापस process_gcf(skb, ct, ctinfo, protoff, data,
				   &ras->gatekeeperConfirm);
	हाल eRasMessage_registrationRequest:
		वापस process_rrq(skb, ct, ctinfo, protoff, data,
				   &ras->registrationRequest);
	हाल eRasMessage_registrationConfirm:
		वापस process_rcf(skb, ct, ctinfo, protoff, data,
				   &ras->registrationConfirm);
	हाल eRasMessage_unregistrationRequest:
		वापस process_urq(skb, ct, ctinfo, protoff, data,
				   &ras->unregistrationRequest);
	हाल eRasMessage_admissionRequest:
		वापस process_arq(skb, ct, ctinfo, protoff, data,
				   &ras->admissionRequest);
	हाल eRasMessage_admissionConfirm:
		वापस process_acf(skb, ct, ctinfo, protoff, data,
				   &ras->admissionConfirm);
	हाल eRasMessage_locationRequest:
		वापस process_lrq(skb, ct, ctinfo, protoff, data,
				   &ras->locationRequest);
	हाल eRasMessage_locationConfirm:
		वापस process_lcf(skb, ct, ctinfo, protoff, data,
				   &ras->locationConfirm);
	हाल eRasMessage_infoRequestResponse:
		वापस process_irr(skb, ct, ctinfo, protoff, data,
				   &ras->infoRequestResponse);
	शेष:
		pr_debug("nf_ct_ras: RAS message %d\n", ras->choice);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ras_help(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		    काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo)
अणु
	अटल RasMessage ras;
	अचिन्हित अक्षर *data;
	पूर्णांक datalen = 0;
	पूर्णांक ret;

	pr_debug("nf_ct_ras: skblen = %u\n", skb->len);

	spin_lock_bh(&nf_h323_lock);

	/* Get UDP data */
	data = get_udp_data(skb, protoff, &datalen);
	अगर (data == शून्य)
		जाओ accept;
	pr_debug("nf_ct_ras: RAS message len=%d ", datalen);
	nf_ct_dump_tuple(&ct->tuplehash[CTINFO2सूची(ctinfo)].tuple);

	/* Decode RAS message */
	ret = DecodeRasMessage(data, datalen, &ras);
	अगर (ret < 0) अणु
		pr_debug("nf_ct_ras: decoding error: %s\n",
			 ret == H323_ERROR_BOUND ?
			 "out of bound" : "out of range");
		जाओ accept;
	पूर्ण

	/* Process RAS message */
	अगर (process_ras(skb, ct, ctinfo, protoff, &data, &ras) < 0)
		जाओ drop;

      accept:
	spin_unlock_bh(&nf_h323_lock);
	वापस NF_ACCEPT;

      drop:
	spin_unlock_bh(&nf_h323_lock);
	nf_ct_helper_log(skb, ct, "cannot process RAS message");
	वापस NF_DROP;
पूर्ण

अटल स्थिर काष्ठा nf_conntrack_expect_policy ras_exp_policy = अणु
	.max_expected		= 32,
	.समयout		= 240,
पूर्ण;

अटल काष्ठा nf_conntrack_helper nf_conntrack_helper_ras[] __पढ़ो_mostly = अणु
	अणु
		.name			= "RAS",
		.me			= THIS_MODULE,
		.tuple.src.l3num	= AF_INET,
		.tuple.src.u.udp.port	= cpu_to_be16(RAS_PORT),
		.tuple.dst.protonum	= IPPROTO_UDP,
		.help			= ras_help,
		.expect_policy		= &ras_exp_policy,
	पूर्ण,
	अणु
		.name			= "RAS",
		.me			= THIS_MODULE,
		.tuple.src.l3num	= AF_INET6,
		.tuple.src.u.udp.port	= cpu_to_be16(RAS_PORT),
		.tuple.dst.protonum	= IPPROTO_UDP,
		.help			= ras_help,
		.expect_policy		= &ras_exp_policy,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init h323_helper_init(व्योम)
अणु
	पूर्णांक ret;

	ret = nf_conntrack_helper_रेजिस्टर(&nf_conntrack_helper_h245);
	अगर (ret < 0)
		वापस ret;
	ret = nf_conntrack_helpers_रेजिस्टर(nf_conntrack_helper_q931,
					ARRAY_SIZE(nf_conntrack_helper_q931));
	अगर (ret < 0)
		जाओ err1;
	ret = nf_conntrack_helpers_रेजिस्टर(nf_conntrack_helper_ras,
					ARRAY_SIZE(nf_conntrack_helper_ras));
	अगर (ret < 0)
		जाओ err2;

	वापस 0;
err2:
	nf_conntrack_helpers_unरेजिस्टर(nf_conntrack_helper_q931,
					ARRAY_SIZE(nf_conntrack_helper_q931));
err1:
	nf_conntrack_helper_unरेजिस्टर(&nf_conntrack_helper_h245);
	वापस ret;
पूर्ण

अटल व्योम __निकास h323_helper_निकास(व्योम)
अणु
	nf_conntrack_helpers_unरेजिस्टर(nf_conntrack_helper_ras,
					ARRAY_SIZE(nf_conntrack_helper_ras));
	nf_conntrack_helpers_unरेजिस्टर(nf_conntrack_helper_q931,
					ARRAY_SIZE(nf_conntrack_helper_q931));
	nf_conntrack_helper_unरेजिस्टर(&nf_conntrack_helper_h245);
पूर्ण

अटल व्योम __निकास nf_conntrack_h323_fini(व्योम)
अणु
	h323_helper_निकास();
	kमुक्त(h323_buffer);
	pr_debug("nf_ct_h323: fini\n");
पूर्ण

अटल पूर्णांक __init nf_conntrack_h323_init(व्योम)
अणु
	पूर्णांक ret;

	NF_CT_HELPER_BUILD_BUG_ON(माप(काष्ठा nf_ct_h323_master));

	h323_buffer = kदो_स्मृति(65536, GFP_KERNEL);
	अगर (!h323_buffer)
		वापस -ENOMEM;
	ret = h323_helper_init();
	अगर (ret < 0)
		जाओ err1;
	pr_debug("nf_ct_h323: init success\n");
	वापस 0;
err1:
	kमुक्त(h323_buffer);
	वापस ret;
पूर्ण

module_init(nf_conntrack_h323_init);
module_निकास(nf_conntrack_h323_fini);

EXPORT_SYMBOL_GPL(get_h225_addr);
EXPORT_SYMBOL_GPL(set_h245_addr_hook);
EXPORT_SYMBOL_GPL(set_h225_addr_hook);
EXPORT_SYMBOL_GPL(set_sig_addr_hook);
EXPORT_SYMBOL_GPL(set_ras_addr_hook);
EXPORT_SYMBOL_GPL(nat_rtp_rtcp_hook);
EXPORT_SYMBOL_GPL(nat_t120_hook);
EXPORT_SYMBOL_GPL(nat_h245_hook);
EXPORT_SYMBOL_GPL(nat_callक्रमwarding_hook);
EXPORT_SYMBOL_GPL(nat_q931_hook);

MODULE_AUTHOR("Jing Min Zhao <zhaojingmin@users.sourceforge.net>");
MODULE_DESCRIPTION("H.323 connection tracking helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ip_conntrack_h323");
MODULE_ALIAS_NFCT_HELPER("RAS");
MODULE_ALIAS_NFCT_HELPER("Q.931");
MODULE_ALIAS_NFCT_HELPER("H.245");
