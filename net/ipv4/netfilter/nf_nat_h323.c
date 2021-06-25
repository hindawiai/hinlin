<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * H.323 extension क्रम NAT alteration.
 *
 * Copyright (c) 2006 Jing Min Zhao <zhaojingmin@users.sourceक्रमge.net>
 * Copyright (c) 2006-2012 Patrick McHardy <kaber@trash.net>
 *
 * Based on the 'brute force' H.323 NAT module by
 * Jozsef Kadlecsik <kadlec@netfilter.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/tcp.h>
#समावेश <net/tcp.h>

#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <linux/netfilter/nf_conntrack_h323.h>

/****************************************************************************/
अटल पूर्णांक set_addr(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		    अचिन्हित अक्षर **data, पूर्णांक dataoff,
		    अचिन्हित पूर्णांक addroff, __be32 ip, __be16 port)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा अणु
		__be32 ip;
		__be16 port;
	पूर्ण __attribute__ ((__packed__)) buf;
	स्थिर काष्ठा tcphdr *th;
	काष्ठा tcphdr _tcph;

	buf.ip = ip;
	buf.port = port;
	addroff += dataoff;

	अगर (ip_hdr(skb)->protocol == IPPROTO_TCP) अणु
		अगर (!nf_nat_mangle_tcp_packet(skb, ct, ctinfo,
					      protoff, addroff, माप(buf),
					      (अक्षर *) &buf, माप(buf))) अणु
			net_notice_ratelimited("nf_nat_h323: nf_nat_mangle_tcp_packet error\n");
			वापस -1;
		पूर्ण

		/* Relocate data poपूर्णांकer */
		th = skb_header_poपूर्णांकer(skb, ip_hdrlen(skb),
					माप(_tcph), &_tcph);
		अगर (th == शून्य)
			वापस -1;
		*data = skb->data + ip_hdrlen(skb) + th->करोff * 4 + dataoff;
	पूर्ण अन्यथा अणु
		अगर (!nf_nat_mangle_udp_packet(skb, ct, ctinfo,
					      protoff, addroff, माप(buf),
					      (अक्षर *) &buf, माप(buf))) अणु
			net_notice_ratelimited("nf_nat_h323: nf_nat_mangle_udp_packet error\n");
			वापस -1;
		पूर्ण
		/* nf_nat_mangle_udp_packet uses skb_ensure_writable() to copy
		 * or pull everything in a linear buffer, so we can safely
		 * use the skb poपूर्णांकers now */
		*data = skb->data + ip_hdrlen(skb) + माप(काष्ठा udphdr);
	पूर्ण

	वापस 0;
पूर्ण

/****************************************************************************/
अटल पूर्णांक set_h225_addr(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			 अचिन्हित अक्षर **data, पूर्णांक dataoff,
			 TransportAddress *taddr,
			 जोड़ nf_inet_addr *addr, __be16 port)
अणु
	वापस set_addr(skb, protoff, data, dataoff, taddr->ipAddress.ip,
			addr->ip, port);
पूर्ण

/****************************************************************************/
अटल पूर्णांक set_h245_addr(काष्ठा sk_buff *skb, अचिन्हित protoff,
			 अचिन्हित अक्षर **data, पूर्णांक dataoff,
			 H245_TransportAddress *taddr,
			 जोड़ nf_inet_addr *addr, __be16 port)
अणु
	वापस set_addr(skb, protoff, data, dataoff,
			taddr->unicastAddress.iPAddress.network,
			addr->ip, port);
पूर्ण

/****************************************************************************/
अटल पूर्णांक set_sig_addr(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			क्रमागत ip_conntrack_info ctinfo,
			अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data,
			TransportAddress *taddr, पूर्णांक count)
अणु
	स्थिर काष्ठा nf_ct_h323_master *info = nfct_help_data(ct);
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक i;
	__be16 port;
	जोड़ nf_inet_addr addr;

	क्रम (i = 0; i < count; i++) अणु
		अगर (get_h225_addr(ct, *data, &taddr[i], &addr, &port)) अणु
			अगर (addr.ip == ct->tuplehash[dir].tuple.src.u3.ip &&
			    port == info->sig_port[dir]) अणु
				/* GW->GK */

				/* Fix क्रम Gnomemeeting */
				अगर (i > 0 &&
				    get_h225_addr(ct, *data, &taddr[0],
						  &addr, &port) &&
				    (ntohl(addr.ip) & 0xff000000) == 0x7f000000)
					i = 0;

				pr_debug("nf_nat_ras: set signal address %pI4:%hu->%pI4:%hu\n",
					 &addr.ip, port,
					 &ct->tuplehash[!dir].tuple.dst.u3.ip,
					 info->sig_port[!dir]);
				वापस set_h225_addr(skb, protoff, data, 0,
						     &taddr[i],
						     &ct->tuplehash[!dir].
						     tuple.dst.u3,
						     info->sig_port[!dir]);
			पूर्ण अन्यथा अगर (addr.ip == ct->tuplehash[dir].tuple.dst.u3.ip &&
				   port == info->sig_port[dir]) अणु
				/* GK->GW */
				pr_debug("nf_nat_ras: set signal address %pI4:%hu->%pI4:%hu\n",
					 &addr.ip, port,
					 &ct->tuplehash[!dir].tuple.src.u3.ip,
					 info->sig_port[!dir]);
				वापस set_h225_addr(skb, protoff, data, 0,
						     &taddr[i],
						     &ct->tuplehash[!dir].
						     tuple.src.u3,
						     info->sig_port[!dir]);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/****************************************************************************/
अटल पूर्णांक set_ras_addr(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			क्रमागत ip_conntrack_info ctinfo,
			अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data,
			TransportAddress *taddr, पूर्णांक count)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक i;
	__be16 port;
	जोड़ nf_inet_addr addr;

	क्रम (i = 0; i < count; i++) अणु
		अगर (get_h225_addr(ct, *data, &taddr[i], &addr, &port) &&
		    addr.ip == ct->tuplehash[dir].tuple.src.u3.ip &&
		    port == ct->tuplehash[dir].tuple.src.u.udp.port) अणु
			pr_debug("nf_nat_ras: set rasAddress %pI4:%hu->%pI4:%hu\n",
				 &addr.ip, ntohs(port),
				 &ct->tuplehash[!dir].tuple.dst.u3.ip,
				 ntohs(ct->tuplehash[!dir].tuple.dst.u.udp.port));
			वापस set_h225_addr(skb, protoff, data, 0, &taddr[i],
					     &ct->tuplehash[!dir].tuple.dst.u3,
					     ct->tuplehash[!dir].tuple.
								dst.u.udp.port);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/****************************************************************************/
अटल पूर्णांक nat_rtp_rtcp(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			क्रमागत ip_conntrack_info ctinfo,
			अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data, पूर्णांक dataoff,
			H245_TransportAddress *taddr,
			__be16 port, __be16 rtp_port,
			काष्ठा nf_conntrack_expect *rtp_exp,
			काष्ठा nf_conntrack_expect *rtcp_exp)
अणु
	काष्ठा nf_ct_h323_master *info = nfct_help_data(ct);
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	पूर्णांक i;
	u_पूर्णांक16_t nated_port;

	/* Set expectations क्रम NAT */
	rtp_exp->saved_proto.udp.port = rtp_exp->tuple.dst.u.udp.port;
	rtp_exp->expectfn = nf_nat_follow_master;
	rtp_exp->dir = !dir;
	rtcp_exp->saved_proto.udp.port = rtcp_exp->tuple.dst.u.udp.port;
	rtcp_exp->expectfn = nf_nat_follow_master;
	rtcp_exp->dir = !dir;

	/* Lookup existing expects */
	क्रम (i = 0; i < H323_RTP_CHANNEL_MAX; i++) अणु
		अगर (info->rtp_port[i][dir] == rtp_port) अणु
			/* Expected */

			/* Use allocated ports first. This will refresh
			 * the expects */
			rtp_exp->tuple.dst.u.udp.port = info->rtp_port[i][dir];
			rtcp_exp->tuple.dst.u.udp.port =
			    htons(ntohs(info->rtp_port[i][dir]) + 1);
			अवरोध;
		पूर्ण अन्यथा अगर (info->rtp_port[i][dir] == 0) अणु
			/* Not expected */
			अवरोध;
		पूर्ण
	पूर्ण

	/* Run out of expectations */
	अगर (i >= H323_RTP_CHANNEL_MAX) अणु
		net_notice_ratelimited("nf_nat_h323: out of expectations\n");
		वापस 0;
	पूर्ण

	/* Try to get a pair of ports. */
	क्रम (nated_port = ntohs(rtp_exp->tuple.dst.u.udp.port);
	     nated_port != 0; nated_port += 2) अणु
		पूर्णांक ret;

		rtp_exp->tuple.dst.u.udp.port = htons(nated_port);
		ret = nf_ct_expect_related(rtp_exp, 0);
		अगर (ret == 0) अणु
			rtcp_exp->tuple.dst.u.udp.port =
			    htons(nated_port + 1);
			ret = nf_ct_expect_related(rtcp_exp, 0);
			अगर (ret == 0)
				अवरोध;
			अन्यथा अगर (ret == -EBUSY) अणु
				nf_ct_unexpect_related(rtp_exp);
				जारी;
			पूर्ण अन्यथा अगर (ret < 0) अणु
				nf_ct_unexpect_related(rtp_exp);
				nated_port = 0;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (ret != -EBUSY) अणु
			nated_port = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nated_port == 0) अणु	/* No port available */
		net_notice_ratelimited("nf_nat_h323: out of RTP ports\n");
		वापस 0;
	पूर्ण

	/* Modअगरy संकेत */
	अगर (set_h245_addr(skb, protoff, data, dataoff, taddr,
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  htons((port & htons(1)) ? nated_port + 1 :
						    nated_port))) अणु
		nf_ct_unexpect_related(rtp_exp);
		nf_ct_unexpect_related(rtcp_exp);
		वापस -1;
	पूर्ण

	/* Save ports */
	info->rtp_port[i][dir] = rtp_port;
	info->rtp_port[i][!dir] = htons(nated_port);

	/* Success */
	pr_debug("nf_nat_h323: expect RTP %pI4:%hu->%pI4:%hu\n",
		 &rtp_exp->tuple.src.u3.ip,
		 ntohs(rtp_exp->tuple.src.u.udp.port),
		 &rtp_exp->tuple.dst.u3.ip,
		 ntohs(rtp_exp->tuple.dst.u.udp.port));
	pr_debug("nf_nat_h323: expect RTCP %pI4:%hu->%pI4:%hu\n",
		 &rtcp_exp->tuple.src.u3.ip,
		 ntohs(rtcp_exp->tuple.src.u.udp.port),
		 &rtcp_exp->tuple.dst.u3.ip,
		 ntohs(rtcp_exp->tuple.dst.u.udp.port));

	वापस 0;
पूर्ण

/****************************************************************************/
अटल पूर्णांक nat_t120(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		    क्रमागत ip_conntrack_info ctinfo,
		    अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data, पूर्णांक dataoff,
		    H245_TransportAddress *taddr, __be16 port,
		    काष्ठा nf_conntrack_expect *exp)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	u_पूर्णांक16_t nated_port = ntohs(port);

	/* Set expectations क्रम NAT */
	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->expectfn = nf_nat_follow_master;
	exp->dir = !dir;

	/* Try to get same port: अगर not, try to change it. */
	क्रम (; nated_port != 0; nated_port++) अणु
		पूर्णांक ret;

		exp->tuple.dst.u.tcp.port = htons(nated_port);
		ret = nf_ct_expect_related(exp, 0);
		अगर (ret == 0)
			अवरोध;
		अन्यथा अगर (ret != -EBUSY) अणु
			nated_port = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nated_port == 0) अणु	/* No port available */
		net_notice_ratelimited("nf_nat_h323: out of TCP ports\n");
		वापस 0;
	पूर्ण

	/* Modअगरy संकेत */
	अगर (set_h245_addr(skb, protoff, data, dataoff, taddr,
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  htons(nated_port)) < 0) अणु
		nf_ct_unexpect_related(exp);
		वापस -1;
	पूर्ण

	pr_debug("nf_nat_h323: expect T.120 %pI4:%hu->%pI4:%hu\n",
		 &exp->tuple.src.u3.ip,
		 ntohs(exp->tuple.src.u.tcp.port),
		 &exp->tuple.dst.u3.ip,
		 ntohs(exp->tuple.dst.u.tcp.port));

	वापस 0;
पूर्ण

/****************************************************************************/
अटल पूर्णांक nat_h245(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		    क्रमागत ip_conntrack_info ctinfo,
		    अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data, पूर्णांक dataoff,
		    TransportAddress *taddr, __be16 port,
		    काष्ठा nf_conntrack_expect *exp)
अणु
	काष्ठा nf_ct_h323_master *info = nfct_help_data(ct);
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	u_पूर्णांक16_t nated_port = ntohs(port);

	/* Set expectations क्रम NAT */
	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->expectfn = nf_nat_follow_master;
	exp->dir = !dir;

	/* Check existing expects */
	अगर (info->sig_port[dir] == port)
		nated_port = ntohs(info->sig_port[!dir]);

	/* Try to get same port: अगर not, try to change it. */
	क्रम (; nated_port != 0; nated_port++) अणु
		पूर्णांक ret;

		exp->tuple.dst.u.tcp.port = htons(nated_port);
		ret = nf_ct_expect_related(exp, 0);
		अगर (ret == 0)
			अवरोध;
		अन्यथा अगर (ret != -EBUSY) अणु
			nated_port = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nated_port == 0) अणु	/* No port available */
		net_notice_ratelimited("nf_nat_q931: out of TCP ports\n");
		वापस 0;
	पूर्ण

	/* Modअगरy संकेत */
	अगर (set_h225_addr(skb, protoff, data, dataoff, taddr,
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  htons(nated_port))) अणु
		nf_ct_unexpect_related(exp);
		वापस -1;
	पूर्ण

	/* Save ports */
	info->sig_port[dir] = port;
	info->sig_port[!dir] = htons(nated_port);

	pr_debug("nf_nat_q931: expect H.245 %pI4:%hu->%pI4:%hu\n",
		 &exp->tuple.src.u3.ip,
		 ntohs(exp->tuple.src.u.tcp.port),
		 &exp->tuple.dst.u3.ip,
		 ntohs(exp->tuple.dst.u.tcp.port));

	वापस 0;
पूर्ण

/****************************************************************************
 * This conntrack expect function replaces nf_conntrack_q931_expect()
 * which was set by nf_conntrack_h323.c.
 ****************************************************************************/
अटल व्योम ip_nat_q931_expect(काष्ठा nf_conn *new,
			       काष्ठा nf_conntrack_expect *this)
अणु
	काष्ठा nf_nat_range2 range;

	अगर (this->tuple.src.u3.ip != 0) अणु	/* Only accept calls from GK */
		nf_nat_follow_master(new, this);
		वापस;
	पूर्ण

	/* This must be a fresh one. */
	BUG_ON(new->status & IPS_NAT_DONE_MASK);

	/* Change src to where master sends to */
	range.flags = NF_NAT_RANGE_MAP_IPS;
	range.min_addr = range.max_addr =
	    new->tuplehash[!this->dir].tuple.src.u3;
	nf_nat_setup_info(new, &range, NF_NAT_MANIP_SRC);

	/* For DST manip, map port here to where it's expected. */
	range.flags = (NF_NAT_RANGE_MAP_IPS | NF_NAT_RANGE_PROTO_SPECIFIED);
	range.min_proto = range.max_proto = this->saved_proto;
	range.min_addr = range.max_addr =
	    new->master->tuplehash[!this->dir].tuple.src.u3;
	nf_nat_setup_info(new, &range, NF_NAT_MANIP_DST);
पूर्ण

/****************************************************************************/
अटल पूर्णांक nat_q931(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		    क्रमागत ip_conntrack_info ctinfo,
		    अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data,
		    TransportAddress *taddr, पूर्णांक idx,
		    __be16 port, काष्ठा nf_conntrack_expect *exp)
अणु
	काष्ठा nf_ct_h323_master *info = nfct_help_data(ct);
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	u_पूर्णांक16_t nated_port = ntohs(port);
	जोड़ nf_inet_addr addr;

	/* Set expectations क्रम NAT */
	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->expectfn = ip_nat_q931_expect;
	exp->dir = !dir;

	/* Check existing expects */
	अगर (info->sig_port[dir] == port)
		nated_port = ntohs(info->sig_port[!dir]);

	/* Try to get same port: अगर not, try to change it. */
	क्रम (; nated_port != 0; nated_port++) अणु
		पूर्णांक ret;

		exp->tuple.dst.u.tcp.port = htons(nated_port);
		ret = nf_ct_expect_related(exp, 0);
		अगर (ret == 0)
			अवरोध;
		अन्यथा अगर (ret != -EBUSY) अणु
			nated_port = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nated_port == 0) अणु	/* No port available */
		net_notice_ratelimited("nf_nat_ras: out of TCP ports\n");
		वापस 0;
	पूर्ण

	/* Modअगरy संकेत */
	अगर (set_h225_addr(skb, protoff, data, 0, &taddr[idx],
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  htons(nated_port))) अणु
		nf_ct_unexpect_related(exp);
		वापस -1;
	पूर्ण

	/* Save ports */
	info->sig_port[dir] = port;
	info->sig_port[!dir] = htons(nated_port);

	/* Fix क्रम Gnomemeeting */
	अगर (idx > 0 &&
	    get_h225_addr(ct, *data, &taddr[0], &addr, &port) &&
	    (ntohl(addr.ip) & 0xff000000) == 0x7f000000) अणु
		अगर (set_h225_addr(skb, protoff, data, 0, &taddr[0],
				  &ct->tuplehash[!dir].tuple.dst.u3,
				  info->sig_port[!dir])) अणु
			nf_ct_unexpect_related(exp);
			वापस -1;
		पूर्ण
	पूर्ण

	/* Success */
	pr_debug("nf_nat_ras: expect Q.931 %pI4:%hu->%pI4:%hu\n",
		 &exp->tuple.src.u3.ip,
		 ntohs(exp->tuple.src.u.tcp.port),
		 &exp->tuple.dst.u3.ip,
		 ntohs(exp->tuple.dst.u.tcp.port));

	वापस 0;
पूर्ण

/****************************************************************************/
अटल व्योम ip_nat_callक्रमwarding_expect(काष्ठा nf_conn *new,
					 काष्ठा nf_conntrack_expect *this)
अणु
	काष्ठा nf_nat_range2 range;

	/* This must be a fresh one. */
	BUG_ON(new->status & IPS_NAT_DONE_MASK);

	/* Change src to where master sends to */
	range.flags = NF_NAT_RANGE_MAP_IPS;
	range.min_addr = range.max_addr =
	    new->tuplehash[!this->dir].tuple.src.u3;
	nf_nat_setup_info(new, &range, NF_NAT_MANIP_SRC);

	/* For DST manip, map port here to where it's expected. */
	range.flags = (NF_NAT_RANGE_MAP_IPS | NF_NAT_RANGE_PROTO_SPECIFIED);
	range.min_proto = range.max_proto = this->saved_proto;
	range.min_addr = range.max_addr = this->saved_addr;
	nf_nat_setup_info(new, &range, NF_NAT_MANIP_DST);
पूर्ण

/****************************************************************************/
अटल पूर्णांक nat_callक्रमwarding(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			      क्रमागत ip_conntrack_info ctinfo,
			      अचिन्हित पूर्णांक protoff,
			      अचिन्हित अक्षर **data, पूर्णांक dataoff,
			      TransportAddress *taddr, __be16 port,
			      काष्ठा nf_conntrack_expect *exp)
अणु
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	u_पूर्णांक16_t nated_port;

	/* Set expectations क्रम NAT */
	exp->saved_addr = exp->tuple.dst.u3;
	exp->tuple.dst.u3.ip = ct->tuplehash[!dir].tuple.dst.u3.ip;
	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->expectfn = ip_nat_callक्रमwarding_expect;
	exp->dir = !dir;

	/* Try to get same port: अगर not, try to change it. */
	क्रम (nated_port = ntohs(port); nated_port != 0; nated_port++) अणु
		पूर्णांक ret;

		exp->tuple.dst.u.tcp.port = htons(nated_port);
		ret = nf_ct_expect_related(exp, 0);
		अगर (ret == 0)
			अवरोध;
		अन्यथा अगर (ret != -EBUSY) अणु
			nated_port = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nated_port == 0) अणु	/* No port available */
		net_notice_ratelimited("nf_nat_q931: out of TCP ports\n");
		वापस 0;
	पूर्ण

	/* Modअगरy संकेत */
	अगर (set_h225_addr(skb, protoff, data, dataoff, taddr,
			  &ct->tuplehash[!dir].tuple.dst.u3,
			  htons(nated_port))) अणु
		nf_ct_unexpect_related(exp);
		वापस -1;
	पूर्ण

	/* Success */
	pr_debug("nf_nat_q931: expect Call Forwarding %pI4:%hu->%pI4:%hu\n",
		 &exp->tuple.src.u3.ip,
		 ntohs(exp->tuple.src.u.tcp.port),
		 &exp->tuple.dst.u3.ip,
		 ntohs(exp->tuple.dst.u.tcp.port));

	वापस 0;
पूर्ण

अटल काष्ठा nf_ct_helper_expectfn q931_nat = अणु
	.name		= "Q.931",
	.expectfn	= ip_nat_q931_expect,
पूर्ण;

अटल काष्ठा nf_ct_helper_expectfn callक्रमwarding_nat = अणु
	.name		= "callforwarding",
	.expectfn	= ip_nat_callक्रमwarding_expect,
पूर्ण;

/****************************************************************************/
अटल पूर्णांक __init init(व्योम)
अणु
	BUG_ON(set_h245_addr_hook != शून्य);
	BUG_ON(set_h225_addr_hook != शून्य);
	BUG_ON(set_sig_addr_hook != शून्य);
	BUG_ON(set_ras_addr_hook != शून्य);
	BUG_ON(nat_rtp_rtcp_hook != शून्य);
	BUG_ON(nat_t120_hook != शून्य);
	BUG_ON(nat_h245_hook != शून्य);
	BUG_ON(nat_callक्रमwarding_hook != शून्य);
	BUG_ON(nat_q931_hook != शून्य);

	RCU_INIT_POINTER(set_h245_addr_hook, set_h245_addr);
	RCU_INIT_POINTER(set_h225_addr_hook, set_h225_addr);
	RCU_INIT_POINTER(set_sig_addr_hook, set_sig_addr);
	RCU_INIT_POINTER(set_ras_addr_hook, set_ras_addr);
	RCU_INIT_POINTER(nat_rtp_rtcp_hook, nat_rtp_rtcp);
	RCU_INIT_POINTER(nat_t120_hook, nat_t120);
	RCU_INIT_POINTER(nat_h245_hook, nat_h245);
	RCU_INIT_POINTER(nat_callक्रमwarding_hook, nat_callक्रमwarding);
	RCU_INIT_POINTER(nat_q931_hook, nat_q931);
	nf_ct_helper_expectfn_रेजिस्टर(&q931_nat);
	nf_ct_helper_expectfn_रेजिस्टर(&callक्रमwarding_nat);
	वापस 0;
पूर्ण

/****************************************************************************/
अटल व्योम __निकास fini(व्योम)
अणु
	RCU_INIT_POINTER(set_h245_addr_hook, शून्य);
	RCU_INIT_POINTER(set_h225_addr_hook, शून्य);
	RCU_INIT_POINTER(set_sig_addr_hook, शून्य);
	RCU_INIT_POINTER(set_ras_addr_hook, शून्य);
	RCU_INIT_POINTER(nat_rtp_rtcp_hook, शून्य);
	RCU_INIT_POINTER(nat_t120_hook, शून्य);
	RCU_INIT_POINTER(nat_h245_hook, शून्य);
	RCU_INIT_POINTER(nat_callक्रमwarding_hook, शून्य);
	RCU_INIT_POINTER(nat_q931_hook, शून्य);
	nf_ct_helper_expectfn_unरेजिस्टर(&q931_nat);
	nf_ct_helper_expectfn_unरेजिस्टर(&callक्रमwarding_nat);
	synchronize_rcu();
पूर्ण

/****************************************************************************/
module_init(init);
module_निकास(fini);

MODULE_AUTHOR("Jing Min Zhao <zhaojingmin@users.sourceforge.net>");
MODULE_DESCRIPTION("H.323 NAT helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NF_NAT_HELPER("h323");
