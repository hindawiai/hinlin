<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* SIP extension क्रम NAT alteration.
 *
 * (C) 2005 by Christian Hentschel <chentschel@arnet.com.ar>
 * based on RR's ip_nat_ftp.c and other modules.
 * (C) 2007 United Security Providers
 * (C) 2007, 2008, 2011, 2012 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet.h>
#समावेश <linux/udp.h>
#समावेश <linux/tcp.h>

#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <linux/netfilter/nf_conntrack_sip.h>

#घोषणा NAT_HELPER_NAME "sip"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hentschel <chentschel@arnet.com.ar>");
MODULE_DESCRIPTION("SIP NAT helper");
MODULE_ALIAS_NF_NAT_HELPER(NAT_HELPER_NAME);

अटल काष्ठा nf_conntrack_nat_helper nat_helper_sip =
	NF_CT_NAT_HELPER_INIT(NAT_HELPER_NAME);

अटल अचिन्हित पूर्णांक mangle_packet(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				  अचिन्हित पूर्णांक dataoff,
				  स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				  अचिन्हित पूर्णांक matchoff, अचिन्हित पूर्णांक matchlen,
				  स्थिर अक्षर *buffer, अचिन्हित पूर्णांक buflen)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा tcphdr *th;
	अचिन्हित पूर्णांक baseoff;

	अगर (nf_ct_protonum(ct) == IPPROTO_TCP) अणु
		th = (काष्ठा tcphdr *)(skb->data + protoff);
		baseoff = protoff + th->करोff * 4;
		matchoff += dataoff - baseoff;

		अगर (!__nf_nat_mangle_tcp_packet(skb, ct, ctinfo,
						protoff, matchoff, matchlen,
						buffer, buflen, false))
			वापस 0;
	पूर्ण अन्यथा अणु
		baseoff = protoff + माप(काष्ठा udphdr);
		matchoff += dataoff - baseoff;

		अगर (!nf_nat_mangle_udp_packet(skb, ct, ctinfo,
					      protoff, matchoff, matchlen,
					      buffer, buflen))
			वापस 0;
	पूर्ण

	/* Reload data poपूर्णांकer and adjust datalen value */
	*dptr = skb->data + dataoff;
	*datalen += buflen - matchlen;
	वापस 1;
पूर्ण

अटल पूर्णांक sip_प्र_लिखो_addr(स्थिर काष्ठा nf_conn *ct, अक्षर *buffer,
			    स्थिर जोड़ nf_inet_addr *addr, bool delim)
अणु
	अगर (nf_ct_l3num(ct) == NFPROTO_IPV4)
		वापस प्र_लिखो(buffer, "%pI4", &addr->ip);
	अन्यथा अणु
		अगर (delim)
			वापस प्र_लिखो(buffer, "[%pI6c]", &addr->ip6);
		अन्यथा
			वापस प्र_लिखो(buffer, "%pI6c", &addr->ip6);
	पूर्ण
पूर्ण

अटल पूर्णांक sip_प्र_लिखो_addr_port(स्थिर काष्ठा nf_conn *ct, अक्षर *buffer,
				 स्थिर जोड़ nf_inet_addr *addr, u16 port)
अणु
	अगर (nf_ct_l3num(ct) == NFPROTO_IPV4)
		वापस प्र_लिखो(buffer, "%pI4:%u", &addr->ip, port);
	अन्यथा
		वापस प्र_लिखो(buffer, "[%pI6c]:%u", &addr->ip6, port);
पूर्ण

अटल पूर्णांक map_addr(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		    अचिन्हित पूर्णांक dataoff,
		    स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
		    अचिन्हित पूर्णांक matchoff, अचिन्हित पूर्णांक matchlen,
		    जोड़ nf_inet_addr *addr, __be16 port)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	काष्ठा nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);
	अक्षर buffer[INET6_ADDRSTRLEN + माप("[]:nnnnn")];
	अचिन्हित पूर्णांक buflen;
	जोड़ nf_inet_addr newaddr;
	__be16 newport;

	अगर (nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.src.u3, addr) &&
	    ct->tuplehash[dir].tuple.src.u.udp.port == port) अणु
		newaddr = ct->tuplehash[!dir].tuple.dst.u3;
		newport = ct->tuplehash[!dir].tuple.dst.u.udp.port;
	पूर्ण अन्यथा अगर (nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.dst.u3, addr) &&
		   ct->tuplehash[dir].tuple.dst.u.udp.port == port) अणु
		newaddr = ct->tuplehash[!dir].tuple.src.u3;
		newport = ct_sip_info->क्रमced_dport ? :
			  ct->tuplehash[!dir].tuple.src.u.udp.port;
	पूर्ण अन्यथा
		वापस 1;

	अगर (nf_inet_addr_cmp(&newaddr, addr) && newport == port)
		वापस 1;

	buflen = sip_प्र_लिखो_addr_port(ct, buffer, &newaddr, ntohs(newport));
	वापस mangle_packet(skb, protoff, dataoff, dptr, datalen,
			     matchoff, matchlen, buffer, buflen);
पूर्ण

अटल पूर्णांक map_sip_addr(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			अचिन्हित पूर्णांक dataoff,
			स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
			क्रमागत sip_header_types type)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	अचिन्हित पूर्णांक matchlen, matchoff;
	जोड़ nf_inet_addr addr;
	__be16 port;

	अगर (ct_sip_parse_header_uri(ct, *dptr, शून्य, *datalen, type, शून्य,
				    &matchoff, &matchlen, &addr, &port) <= 0)
		वापस 1;
	वापस map_addr(skb, protoff, dataoff, dptr, datalen,
			matchoff, matchlen, &addr, port);
पूर्ण

अटल अचिन्हित पूर्णांक nf_nat_sip(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			       अचिन्हित पूर्णांक dataoff,
			       स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	काष्ठा nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);
	अचिन्हित पूर्णांक coff, matchoff, matchlen;
	क्रमागत sip_header_types hdr;
	जोड़ nf_inet_addr addr;
	__be16 port;
	पूर्णांक request, in_header;

	/* Basic rules: requests and responses. */
	अगर (strnहालcmp(*dptr, "SIP/2.0", म_माप("SIP/2.0")) != 0) अणु
		अगर (ct_sip_parse_request(ct, *dptr, *datalen,
					 &matchoff, &matchlen,
					 &addr, &port) > 0 &&
		    !map_addr(skb, protoff, dataoff, dptr, datalen,
			      matchoff, matchlen, &addr, port)) अणु
			nf_ct_helper_log(skb, ct, "cannot mangle SIP message");
			वापस NF_DROP;
		पूर्ण
		request = 1;
	पूर्ण अन्यथा
		request = 0;

	अगर (nf_ct_protonum(ct) == IPPROTO_TCP)
		hdr = SIP_HDR_VIA_TCP;
	अन्यथा
		hdr = SIP_HDR_VIA_UDP;

	/* Translate topmost Via header and parameters */
	अगर (ct_sip_parse_header_uri(ct, *dptr, शून्य, *datalen,
				    hdr, शून्य, &matchoff, &matchlen,
				    &addr, &port) > 0) अणु
		अचिन्हित पूर्णांक olen, matchend, poff, plen, buflen, n;
		अक्षर buffer[INET6_ADDRSTRLEN + माप("[]:nnnnn")];

		/* We're only पूर्णांकerested in headers related to this
		 * connection */
		अगर (request) अणु
			अगर (!nf_inet_addr_cmp(&addr,
					&ct->tuplehash[dir].tuple.src.u3) ||
			    port != ct->tuplehash[dir].tuple.src.u.udp.port)
				जाओ next;
		पूर्ण अन्यथा अणु
			अगर (!nf_inet_addr_cmp(&addr,
					&ct->tuplehash[dir].tuple.dst.u3) ||
			    port != ct->tuplehash[dir].tuple.dst.u.udp.port)
				जाओ next;
		पूर्ण

		olen = *datalen;
		अगर (!map_addr(skb, protoff, dataoff, dptr, datalen,
			      matchoff, matchlen, &addr, port)) अणु
			nf_ct_helper_log(skb, ct, "cannot mangle Via header");
			वापस NF_DROP;
		पूर्ण

		matchend = matchoff + matchlen + *datalen - olen;

		/* The maddr= parameter (RFC 2361) specअगरies where to send
		 * the reply. */
		अगर (ct_sip_parse_address_param(ct, *dptr, matchend, *datalen,
					       "maddr=", &poff, &plen,
					       &addr, true) > 0 &&
		    nf_inet_addr_cmp(&addr, &ct->tuplehash[dir].tuple.src.u3) &&
		    !nf_inet_addr_cmp(&addr, &ct->tuplehash[!dir].tuple.dst.u3)) अणु
			buflen = sip_प्र_लिखो_addr(ct, buffer,
					&ct->tuplehash[!dir].tuple.dst.u3,
					true);
			अगर (!mangle_packet(skb, protoff, dataoff, dptr, datalen,
					   poff, plen, buffer, buflen)) अणु
				nf_ct_helper_log(skb, ct, "cannot mangle maddr");
				वापस NF_DROP;
			पूर्ण
		पूर्ण

		/* The received= parameter (RFC 2361) contains the address
		 * from which the server received the request. */
		अगर (ct_sip_parse_address_param(ct, *dptr, matchend, *datalen,
					       "received=", &poff, &plen,
					       &addr, false) > 0 &&
		    nf_inet_addr_cmp(&addr, &ct->tuplehash[dir].tuple.dst.u3) &&
		    !nf_inet_addr_cmp(&addr, &ct->tuplehash[!dir].tuple.src.u3)) अणु
			buflen = sip_प्र_लिखो_addr(ct, buffer,
					&ct->tuplehash[!dir].tuple.src.u3,
					false);
			अगर (!mangle_packet(skb, protoff, dataoff, dptr, datalen,
					   poff, plen, buffer, buflen)) अणु
				nf_ct_helper_log(skb, ct, "cannot mangle received");
				वापस NF_DROP;
			पूर्ण
		पूर्ण

		/* The rport= parameter (RFC 3581) contains the port number
		 * from which the server received the request. */
		अगर (ct_sip_parse_numerical_param(ct, *dptr, matchend, *datalen,
						 "rport=", &poff, &plen,
						 &n) > 0 &&
		    htons(n) == ct->tuplehash[dir].tuple.dst.u.udp.port &&
		    htons(n) != ct->tuplehash[!dir].tuple.src.u.udp.port) अणु
			__be16 p = ct->tuplehash[!dir].tuple.src.u.udp.port;
			buflen = प्र_लिखो(buffer, "%u", ntohs(p));
			अगर (!mangle_packet(skb, protoff, dataoff, dptr, datalen,
					   poff, plen, buffer, buflen)) अणु
				nf_ct_helper_log(skb, ct, "cannot mangle rport");
				वापस NF_DROP;
			पूर्ण
		पूर्ण
	पूर्ण

next:
	/* Translate Contact headers */
	coff = 0;
	in_header = 0;
	जबतक (ct_sip_parse_header_uri(ct, *dptr, &coff, *datalen,
				       SIP_HDR_CONTACT, &in_header,
				       &matchoff, &matchlen,
				       &addr, &port) > 0) अणु
		अगर (!map_addr(skb, protoff, dataoff, dptr, datalen,
			      matchoff, matchlen,
			      &addr, port)) अणु
			nf_ct_helper_log(skb, ct, "cannot mangle contact");
			वापस NF_DROP;
		पूर्ण
	पूर्ण

	अगर (!map_sip_addr(skb, protoff, dataoff, dptr, datalen, SIP_HDR_FROM) ||
	    !map_sip_addr(skb, protoff, dataoff, dptr, datalen, SIP_HDR_TO)) अणु
		nf_ct_helper_log(skb, ct, "cannot mangle SIP from/to");
		वापस NF_DROP;
	पूर्ण

	/* Mangle destination port क्रम Cisco phones, then fix up checksums */
	अगर (dir == IP_CT_सूची_REPLY && ct_sip_info->क्रमced_dport) अणु
		काष्ठा udphdr *uh;

		अगर (skb_ensure_writable(skb, skb->len)) अणु
			nf_ct_helper_log(skb, ct, "cannot mangle packet");
			वापस NF_DROP;
		पूर्ण

		uh = (व्योम *)skb->data + protoff;
		uh->dest = ct_sip_info->क्रमced_dport;

		अगर (!nf_nat_mangle_udp_packet(skb, ct, ctinfo, protoff,
					      0, 0, शून्य, 0)) अणु
			nf_ct_helper_log(skb, ct, "cannot mangle packet");
			वापस NF_DROP;
		पूर्ण
	पूर्ण

	वापस NF_ACCEPT;
पूर्ण

अटल व्योम nf_nat_sip_seq_adjust(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				  s16 off)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	स्थिर काष्ठा tcphdr *th;

	अगर (nf_ct_protonum(ct) != IPPROTO_TCP || off == 0)
		वापस;

	th = (काष्ठा tcphdr *)(skb->data + protoff);
	nf_ct_seqadj_set(ct, ctinfo, th->seq, off);
पूर्ण

/* Handles expected संकेतling connections and media streams */
अटल व्योम nf_nat_sip_expected(काष्ठा nf_conn *ct,
				काष्ठा nf_conntrack_expect *exp)
अणु
	काष्ठा nf_conn_help *help = nfct_help(ct->master);
	काष्ठा nf_conntrack_expect *pair_exp;
	पूर्णांक range_set_क्रम_snat = 0;
	काष्ठा nf_nat_range2 range;

	/* This must be a fresh one. */
	BUG_ON(ct->status & IPS_NAT_DONE_MASK);

	/* For DST manip, map port here to where it's expected. */
	range.flags = (NF_NAT_RANGE_MAP_IPS | NF_NAT_RANGE_PROTO_SPECIFIED);
	range.min_proto = range.max_proto = exp->saved_proto;
	range.min_addr = range.max_addr = exp->saved_addr;
	nf_nat_setup_info(ct, &range, NF_NAT_MANIP_DST);

	/* Do media streams SRC manip according with the parameters
	 * found in the paired expectation.
	 */
	अगर (exp->class != SIP_EXPECT_SIGNALLING) अणु
		spin_lock_bh(&nf_conntrack_expect_lock);
		hlist_क्रम_each_entry(pair_exp, &help->expectations, lnode) अणु
			अगर (pair_exp->tuple.src.l3num == nf_ct_l3num(ct) &&
			    pair_exp->tuple.dst.protonum == ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.dst.protonum &&
			    nf_inet_addr_cmp(&ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u3, &pair_exp->saved_addr) &&
			    ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u.all == pair_exp->saved_proto.all) अणु
				range.flags = (NF_NAT_RANGE_MAP_IPS | NF_NAT_RANGE_PROTO_SPECIFIED);
				range.min_proto.all = range.max_proto.all = pair_exp->tuple.dst.u.all;
				range.min_addr = range.max_addr = pair_exp->tuple.dst.u3;
				range_set_क्रम_snat = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&nf_conntrack_expect_lock);
	पूर्ण

	/* When no paired expectation has been found, change src to
	 * where master sends to, but only अगर the connection actually came
	 * from the same source.
	 */
	अगर (!range_set_क्रम_snat &&
	    nf_inet_addr_cmp(&ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u3,
			     &ct->master->tuplehash[exp->dir].tuple.src.u3)) अणु
		range.flags = NF_NAT_RANGE_MAP_IPS;
		range.min_addr = range.max_addr
			= ct->master->tuplehash[!exp->dir].tuple.dst.u3;
		range_set_क्रम_snat = 1;
	पूर्ण

	/* Perक्रमm SRC manip. */
	अगर (range_set_क्रम_snat)
		nf_nat_setup_info(ct, &range, NF_NAT_MANIP_SRC);
पूर्ण

अटल अचिन्हित पूर्णांक nf_nat_sip_expect(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				      अचिन्हित पूर्णांक dataoff,
				      स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				      काष्ठा nf_conntrack_expect *exp,
				      अचिन्हित पूर्णांक matchoff,
				      अचिन्हित पूर्णांक matchlen)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	काष्ठा nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);
	जोड़ nf_inet_addr newaddr;
	u_पूर्णांक16_t port;
	__be16 srcport;
	अक्षर buffer[INET6_ADDRSTRLEN + माप("[]:nnnnn")];
	अचिन्हित पूर्णांक buflen;

	/* Connection will come from reply */
	अगर (nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.src.u3,
			     &ct->tuplehash[!dir].tuple.dst.u3))
		newaddr = exp->tuple.dst.u3;
	अन्यथा
		newaddr = ct->tuplehash[!dir].tuple.dst.u3;

	/* If the संकेतling port matches the connection's source port in the
	 * original direction, try to use the destination port in the opposite
	 * direction. */
	srcport = ct_sip_info->क्रमced_dport ? :
		  ct->tuplehash[dir].tuple.src.u.udp.port;
	अगर (exp->tuple.dst.u.udp.port == srcport)
		port = ntohs(ct->tuplehash[!dir].tuple.dst.u.udp.port);
	अन्यथा
		port = ntohs(exp->tuple.dst.u.udp.port);

	exp->saved_addr = exp->tuple.dst.u3;
	exp->tuple.dst.u3 = newaddr;
	exp->saved_proto.udp.port = exp->tuple.dst.u.udp.port;
	exp->dir = !dir;
	exp->expectfn = nf_nat_sip_expected;

	क्रम (; port != 0; port++) अणु
		पूर्णांक ret;

		exp->tuple.dst.u.udp.port = htons(port);
		ret = nf_ct_expect_related(exp, NF_CT_EXP_F_SKIP_MASTER);
		अगर (ret == 0)
			अवरोध;
		अन्यथा अगर (ret != -EBUSY) अणु
			port = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (port == 0) अणु
		nf_ct_helper_log(skb, ct, "all ports in use for SIP");
		वापस NF_DROP;
	पूर्ण

	अगर (!nf_inet_addr_cmp(&exp->tuple.dst.u3, &exp->saved_addr) ||
	    exp->tuple.dst.u.udp.port != exp->saved_proto.udp.port) अणु
		buflen = sip_प्र_लिखो_addr_port(ct, buffer, &newaddr, port);
		अगर (!mangle_packet(skb, protoff, dataoff, dptr, datalen,
				   matchoff, matchlen, buffer, buflen)) अणु
			nf_ct_helper_log(skb, ct, "cannot mangle packet");
			जाओ err;
		पूर्ण
	पूर्ण
	वापस NF_ACCEPT;

err:
	nf_ct_unexpect_related(exp);
	वापस NF_DROP;
पूर्ण

अटल पूर्णांक mangle_content_len(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			      अचिन्हित पूर्णांक dataoff,
			      स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	अचिन्हित पूर्णांक matchoff, matchlen;
	अक्षर buffer[माप("65536")];
	पूर्णांक buflen, c_len;

	/* Get actual SDP length */
	अगर (ct_sip_get_sdp_header(ct, *dptr, 0, *datalen,
				  SDP_HDR_VERSION, SDP_HDR_UNSPEC,
				  &matchoff, &matchlen) <= 0)
		वापस 0;
	c_len = *datalen - matchoff + म_माप("v=");

	/* Now, update SDP length */
	अगर (ct_sip_get_header(ct, *dptr, 0, *datalen, SIP_HDR_CONTENT_LENGTH,
			      &matchoff, &matchlen) <= 0)
		वापस 0;

	buflen = प्र_लिखो(buffer, "%u", c_len);
	वापस mangle_packet(skb, protoff, dataoff, dptr, datalen,
			     matchoff, matchlen, buffer, buflen);
पूर्ण

अटल पूर्णांक mangle_sdp_packet(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			     अचिन्हित पूर्णांक dataoff,
			     स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
			     अचिन्हित पूर्णांक sdpoff,
			     क्रमागत sdp_header_types type,
			     क्रमागत sdp_header_types term,
			     अक्षर *buffer, पूर्णांक buflen)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	अचिन्हित पूर्णांक matchlen, matchoff;

	अगर (ct_sip_get_sdp_header(ct, *dptr, sdpoff, *datalen, type, term,
				  &matchoff, &matchlen) <= 0)
		वापस -ENOENT;
	वापस mangle_packet(skb, protoff, dataoff, dptr, datalen,
			     matchoff, matchlen, buffer, buflen) ? 0 : -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक nf_nat_sdp_addr(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				    अचिन्हित पूर्णांक dataoff,
				    स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				    अचिन्हित पूर्णांक sdpoff,
				    क्रमागत sdp_header_types type,
				    क्रमागत sdp_header_types term,
				    स्थिर जोड़ nf_inet_addr *addr)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	अक्षर buffer[INET6_ADDRSTRLEN];
	अचिन्हित पूर्णांक buflen;

	buflen = sip_प्र_लिखो_addr(ct, buffer, addr, false);
	अगर (mangle_sdp_packet(skb, protoff, dataoff, dptr, datalen,
			      sdpoff, type, term, buffer, buflen))
		वापस 0;

	वापस mangle_content_len(skb, protoff, dataoff, dptr, datalen);
पूर्ण

अटल अचिन्हित पूर्णांक nf_nat_sdp_port(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				    अचिन्हित पूर्णांक dataoff,
				    स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				    अचिन्हित पूर्णांक matchoff,
				    अचिन्हित पूर्णांक matchlen,
				    u_पूर्णांक16_t port)
अणु
	अक्षर buffer[माप("nnnnn")];
	अचिन्हित पूर्णांक buflen;

	buflen = प्र_लिखो(buffer, "%u", port);
	अगर (!mangle_packet(skb, protoff, dataoff, dptr, datalen,
			   matchoff, matchlen, buffer, buflen))
		वापस 0;

	वापस mangle_content_len(skb, protoff, dataoff, dptr, datalen);
पूर्ण

अटल अचिन्हित पूर्णांक nf_nat_sdp_session(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				       अचिन्हित पूर्णांक dataoff,
				       स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				       अचिन्हित पूर्णांक sdpoff,
				       स्थिर जोड़ nf_inet_addr *addr)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	अक्षर buffer[INET6_ADDRSTRLEN];
	अचिन्हित पूर्णांक buflen;

	/* Mangle session description owner and contact addresses */
	buflen = sip_प्र_लिखो_addr(ct, buffer, addr, false);
	अगर (mangle_sdp_packet(skb, protoff, dataoff, dptr, datalen, sdpoff,
			      SDP_HDR_OWNER, SDP_HDR_MEDIA, buffer, buflen))
		वापस 0;

	चयन (mangle_sdp_packet(skb, protoff, dataoff, dptr, datalen, sdpoff,
				  SDP_HDR_CONNECTION, SDP_HDR_MEDIA,
				  buffer, buflen)) अणु
	हाल 0:
	/*
	 * RFC 2327:
	 *
	 * Session description
	 *
	 * c=* (connection inक्रमmation - not required अगर included in all media)
	 */
	हाल -ENOENT:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस mangle_content_len(skb, protoff, dataoff, dptr, datalen);
पूर्ण

/* So, this packet has hit the connection tracking matching code.
   Mangle it, and change the expectation to match the new version. */
अटल अचिन्हित पूर्णांक nf_nat_sdp_media(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				     अचिन्हित पूर्णांक dataoff,
				     स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				     काष्ठा nf_conntrack_expect *rtp_exp,
				     काष्ठा nf_conntrack_expect *rtcp_exp,
				     अचिन्हित पूर्णांक mediaoff,
				     अचिन्हित पूर्णांक medialen,
				     जोड़ nf_inet_addr *rtp_addr)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	u_पूर्णांक16_t port;

	/* Connection will come from reply */
	अगर (nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.src.u3,
			     &ct->tuplehash[!dir].tuple.dst.u3))
		*rtp_addr = rtp_exp->tuple.dst.u3;
	अन्यथा
		*rtp_addr = ct->tuplehash[!dir].tuple.dst.u3;

	rtp_exp->saved_addr = rtp_exp->tuple.dst.u3;
	rtp_exp->tuple.dst.u3 = *rtp_addr;
	rtp_exp->saved_proto.udp.port = rtp_exp->tuple.dst.u.udp.port;
	rtp_exp->dir = !dir;
	rtp_exp->expectfn = nf_nat_sip_expected;

	rtcp_exp->saved_addr = rtcp_exp->tuple.dst.u3;
	rtcp_exp->tuple.dst.u3 = *rtp_addr;
	rtcp_exp->saved_proto.udp.port = rtcp_exp->tuple.dst.u.udp.port;
	rtcp_exp->dir = !dir;
	rtcp_exp->expectfn = nf_nat_sip_expected;

	/* Try to get same pair of ports: अगर not, try to change them. */
	क्रम (port = ntohs(rtp_exp->tuple.dst.u.udp.port);
	     port != 0; port += 2) अणु
		पूर्णांक ret;

		rtp_exp->tuple.dst.u.udp.port = htons(port);
		ret = nf_ct_expect_related(rtp_exp,
					   NF_CT_EXP_F_SKIP_MASTER);
		अगर (ret == -EBUSY)
			जारी;
		अन्यथा अगर (ret < 0) अणु
			port = 0;
			अवरोध;
		पूर्ण
		rtcp_exp->tuple.dst.u.udp.port = htons(port + 1);
		ret = nf_ct_expect_related(rtcp_exp,
					   NF_CT_EXP_F_SKIP_MASTER);
		अगर (ret == 0)
			अवरोध;
		अन्यथा अगर (ret == -EBUSY) अणु
			nf_ct_unexpect_related(rtp_exp);
			जारी;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			nf_ct_unexpect_related(rtp_exp);
			port = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (port == 0) अणु
		nf_ct_helper_log(skb, ct, "all ports in use for SDP media");
		जाओ err1;
	पूर्ण

	/* Update media port. */
	अगर (rtp_exp->tuple.dst.u.udp.port != rtp_exp->saved_proto.udp.port &&
	    !nf_nat_sdp_port(skb, protoff, dataoff, dptr, datalen,
			     mediaoff, medialen, port)) अणु
		nf_ct_helper_log(skb, ct, "cannot mangle SDP message");
		जाओ err2;
	पूर्ण

	वापस NF_ACCEPT;

err2:
	nf_ct_unexpect_related(rtp_exp);
	nf_ct_unexpect_related(rtcp_exp);
err1:
	वापस NF_DROP;
पूर्ण

अटल काष्ठा nf_ct_helper_expectfn sip_nat = अणु
	.name		= "sip",
	.expectfn	= nf_nat_sip_expected,
पूर्ण;

अटल व्योम __निकास nf_nat_sip_fini(व्योम)
अणु
	nf_nat_helper_unरेजिस्टर(&nat_helper_sip);
	RCU_INIT_POINTER(nf_nat_sip_hooks, शून्य);
	nf_ct_helper_expectfn_unरेजिस्टर(&sip_nat);
	synchronize_rcu();
पूर्ण

अटल स्थिर काष्ठा nf_nat_sip_hooks sip_hooks = अणु
	.msg		= nf_nat_sip,
	.seq_adjust	= nf_nat_sip_seq_adjust,
	.expect		= nf_nat_sip_expect,
	.sdp_addr	= nf_nat_sdp_addr,
	.sdp_port	= nf_nat_sdp_port,
	.sdp_session	= nf_nat_sdp_session,
	.sdp_media	= nf_nat_sdp_media,
पूर्ण;

अटल पूर्णांक __init nf_nat_sip_init(व्योम)
अणु
	BUG_ON(nf_nat_sip_hooks != शून्य);
	nf_nat_helper_रेजिस्टर(&nat_helper_sip);
	RCU_INIT_POINTER(nf_nat_sip_hooks, &sip_hooks);
	nf_ct_helper_expectfn_रेजिस्टर(&sip_nat);
	वापस 0;
पूर्ण

module_init(nf_nat_sip_init);
module_निकास(nf_nat_sip_fini);
