<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* nf_nat_helper.c - generic support functions क्रम NAT helpers
 *
 * (C) 2000-2002 Harald Welte <laक्रमge@netfilter.org>
 * (C) 2003-2006 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2007-2012 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <net/tcp.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_helper.h>

/* Frobs data inside this packet, which is linear. */
अटल व्योम mangle_contents(काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक dataoff,
			    अचिन्हित पूर्णांक match_offset,
			    अचिन्हित पूर्णांक match_len,
			    स्थिर अक्षर *rep_buffer,
			    अचिन्हित पूर्णांक rep_len)
अणु
	अचिन्हित अक्षर *data;

	SKB_LINEAR_ASSERT(skb);
	data = skb_network_header(skb) + dataoff;

	/* move post-replacement */
	स_हटाओ(data + match_offset + rep_len,
		data + match_offset + match_len,
		skb_tail_poपूर्णांकer(skb) - (skb_network_header(skb) + dataoff +
			     match_offset + match_len));

	/* insert data from buffer */
	स_नकल(data + match_offset, rep_buffer, rep_len);

	/* update skb info */
	अगर (rep_len > match_len) अणु
		pr_debug("nf_nat_mangle_packet: Extending packet by "
			 "%u from %u bytes\n", rep_len - match_len, skb->len);
		skb_put(skb, rep_len - match_len);
	पूर्ण अन्यथा अणु
		pr_debug("nf_nat_mangle_packet: Shrinking packet from "
			 "%u from %u bytes\n", match_len - rep_len, skb->len);
		__skb_trim(skb, skb->len + rep_len - match_len);
	पूर्ण

	अगर (nf_ct_l3num((काष्ठा nf_conn *)skb_nfct(skb)) == NFPROTO_IPV4) अणु
		/* fix IP hdr checksum inक्रमmation */
		ip_hdr(skb)->tot_len = htons(skb->len);
		ip_send_check(ip_hdr(skb));
	पूर्ण अन्यथा
		ipv6_hdr(skb)->payload_len =
			htons(skb->len - माप(काष्ठा ipv6hdr));
पूर्ण

/* Unusual, but possible हाल. */
अटल bool enlarge_skb(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक extra)
अणु
	अगर (skb->len + extra > 65535)
		वापस false;

	अगर (pskb_expand_head(skb, 0, extra - skb_tailroom(skb), GFP_ATOMIC))
		वापस false;

	वापस true;
पूर्ण

/* Generic function क्रम mangling variable-length address changes inside
 * NATed TCP connections (like the PORT XXX,XXX,XXX,XXX,XXX,XXX
 * command in FTP).
 *
 * Takes care about all the nasty sequence number changes, checksumming,
 * skb enlargement, ...
 *
 * */
bool __nf_nat_mangle_tcp_packet(काष्ठा sk_buff *skb,
				काष्ठा nf_conn *ct,
				क्रमागत ip_conntrack_info ctinfo,
				अचिन्हित पूर्णांक protoff,
				अचिन्हित पूर्णांक match_offset,
				अचिन्हित पूर्णांक match_len,
				स्थिर अक्षर *rep_buffer,
				अचिन्हित पूर्णांक rep_len, bool adjust)
अणु
	काष्ठा tcphdr *tcph;
	पूर्णांक oldlen, datalen;

	अगर (skb_ensure_writable(skb, skb->len))
		वापस false;

	अगर (rep_len > match_len &&
	    rep_len - match_len > skb_tailroom(skb) &&
	    !enlarge_skb(skb, rep_len - match_len))
		वापस false;

	tcph = (व्योम *)skb->data + protoff;

	oldlen = skb->len - protoff;
	mangle_contents(skb, protoff + tcph->करोff*4,
			match_offset, match_len, rep_buffer, rep_len);

	datalen = skb->len - protoff;

	nf_nat_csum_recalc(skb, nf_ct_l3num(ct), IPPROTO_TCP,
			   tcph, &tcph->check, datalen, oldlen);

	अगर (adjust && rep_len != match_len)
		nf_ct_seqadj_set(ct, ctinfo, tcph->seq,
				 (पूर्णांक)rep_len - (पूर्णांक)match_len);

	वापस true;
पूर्ण
EXPORT_SYMBOL(__nf_nat_mangle_tcp_packet);

/* Generic function क्रम mangling variable-length address changes inside
 * NATed UDP connections (like the CONNECT DATA XXXXX MESG XXXXX INDEX XXXXX
 * command in the Amanda protocol)
 *
 * Takes care about all the nasty sequence number changes, checksumming,
 * skb enlargement, ...
 *
 * XXX - This function could be merged with nf_nat_mangle_tcp_packet which
 *       should be fairly easy to करो.
 */
bool
nf_nat_mangle_udp_packet(काष्ठा sk_buff *skb,
			 काष्ठा nf_conn *ct,
			 क्रमागत ip_conntrack_info ctinfo,
			 अचिन्हित पूर्णांक protoff,
			 अचिन्हित पूर्णांक match_offset,
			 अचिन्हित पूर्णांक match_len,
			 स्थिर अक्षर *rep_buffer,
			 अचिन्हित पूर्णांक rep_len)
अणु
	काष्ठा udphdr *udph;
	पूर्णांक datalen, oldlen;

	अगर (skb_ensure_writable(skb, skb->len))
		वापस false;

	अगर (rep_len > match_len &&
	    rep_len - match_len > skb_tailroom(skb) &&
	    !enlarge_skb(skb, rep_len - match_len))
		वापस false;

	udph = (व्योम *)skb->data + protoff;

	oldlen = skb->len - protoff;
	mangle_contents(skb, protoff + माप(*udph),
			match_offset, match_len, rep_buffer, rep_len);

	/* update the length of the UDP packet */
	datalen = skb->len - protoff;
	udph->len = htons(datalen);

	/* fix udp checksum अगर udp checksum was previously calculated */
	अगर (!udph->check && skb->ip_summed != CHECKSUM_PARTIAL)
		वापस true;

	nf_nat_csum_recalc(skb, nf_ct_l3num(ct), IPPROTO_UDP,
			   udph, &udph->check, datalen, oldlen);

	वापस true;
पूर्ण
EXPORT_SYMBOL(nf_nat_mangle_udp_packet);

/* Setup NAT on this expected conntrack so it follows master. */
/* If we fail to get a मुक्त NAT slot, we'll get dropped on confirm */
व्योम nf_nat_follow_master(काष्ठा nf_conn *ct,
			  काष्ठा nf_conntrack_expect *exp)
अणु
	काष्ठा nf_nat_range2 range;

	/* This must be a fresh one. */
	BUG_ON(ct->status & IPS_NAT_DONE_MASK);

	/* Change src to where master sends to */
	range.flags = NF_NAT_RANGE_MAP_IPS;
	range.min_addr = range.max_addr
		= ct->master->tuplehash[!exp->dir].tuple.dst.u3;
	nf_nat_setup_info(ct, &range, NF_NAT_MANIP_SRC);

	/* For DST manip, map port here to where it's expected. */
	range.flags = (NF_NAT_RANGE_MAP_IPS | NF_NAT_RANGE_PROTO_SPECIFIED);
	range.min_proto = range.max_proto = exp->saved_proto;
	range.min_addr = range.max_addr
		= ct->master->tuplehash[!exp->dir].tuple.src.u3;
	nf_nat_setup_info(ct, &range, NF_NAT_MANIP_DST);
पूर्ण
EXPORT_SYMBOL(nf_nat_follow_master);
