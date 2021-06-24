<शैली गुरु>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/types.h>
#समावेश <net/checksum.h>
#समावेश <net/ip.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/protocol.h>
#समावेश <uapi/linux/ila.h>
#समावेश "ila.h"

व्योम ila_init_saved_csum(काष्ठा ila_params *p)
अणु
	अगर (!p->locator_match.v64)
		वापस;

	p->csum_dअगरf = compute_csum_dअगरf8(
				(__be32 *)&p->locator,
				(__be32 *)&p->locator_match);
पूर्ण

अटल __wsum get_csum_dअगरf_iaddr(काष्ठा ila_addr *iaddr, काष्ठा ila_params *p)
अणु
	अगर (p->locator_match.v64)
		वापस p->csum_dअगरf;
	अन्यथा
		वापस compute_csum_dअगरf8((__be32 *)&p->locator,
					  (__be32 *)&iaddr->loc);
पूर्ण

अटल __wsum get_csum_dअगरf(काष्ठा ipv6hdr *ip6h, काष्ठा ila_params *p)
अणु
	वापस get_csum_dअगरf_iaddr(ila_a2i(&ip6h->daddr), p);
पूर्ण

अटल व्योम ila_csum_करो_neutral_fmt(काष्ठा ila_addr *iaddr,
				    काष्ठा ila_params *p)
अणु
	__sum16 *adjust = (__क्रमce __sum16 *)&iaddr->ident.v16[3];
	__wsum dअगरf, fval;

	dअगरf = get_csum_dअगरf_iaddr(iaddr, p);

	fval = (__क्रमce __wsum)(ila_csum_neutral_set(iaddr->ident) ?
			CSUM_NEUTRAL_FLAG : ~CSUM_NEUTRAL_FLAG);

	dअगरf = csum_add(dअगरf, fval);

	*adjust = ~csum_fold(csum_add(dअगरf, csum_unfold(*adjust)));

	/* Flip the csum-neutral bit. Either we are करोing a SIR->ILA
	 * translation with ILA_CSUM_NEUTRAL_MAP as the csum_method
	 * and the C-bit is not set, or we are करोing an ILA-SIR
	 * tranlsation and the C-bit is set.
	 */
	iaddr->ident.csum_neutral ^= 1;
पूर्ण

अटल व्योम ila_csum_करो_neutral_nofmt(काष्ठा ila_addr *iaddr,
				      काष्ठा ila_params *p)
अणु
	__sum16 *adjust = (__क्रमce __sum16 *)&iaddr->ident.v16[3];
	__wsum dअगरf;

	dअगरf = get_csum_dअगरf_iaddr(iaddr, p);

	*adjust = ~csum_fold(csum_add(dअगरf, csum_unfold(*adjust)));
पूर्ण

अटल व्योम ila_csum_adjust_transport(काष्ठा sk_buff *skb,
				      काष्ठा ila_params *p)
अणु
	माप_प्रकार nhoff = माप(काष्ठा ipv6hdr);
	काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	__wsum dअगरf;

	चयन (ip6h->nexthdr) अणु
	हाल NEXTHDR_TCP:
		अगर (likely(pskb_may_pull(skb, nhoff + माप(काष्ठा tcphdr)))) अणु
			काष्ठा tcphdr *th = (काष्ठा tcphdr *)
					(skb_network_header(skb) + nhoff);

			dअगरf = get_csum_dअगरf(ip6h, p);
			inet_proto_csum_replace_by_dअगरf(&th->check, skb,
							dअगरf, true);
		पूर्ण
		अवरोध;
	हाल NEXTHDR_UDP:
		अगर (likely(pskb_may_pull(skb, nhoff + माप(काष्ठा udphdr)))) अणु
			काष्ठा udphdr *uh = (काष्ठा udphdr *)
					(skb_network_header(skb) + nhoff);

			अगर (uh->check || skb->ip_summed == CHECKSUM_PARTIAL) अणु
				dअगरf = get_csum_dअगरf(ip6h, p);
				inet_proto_csum_replace_by_dअगरf(&uh->check, skb,
								dअगरf, true);
				अगर (!uh->check)
					uh->check = CSUM_MANGLED_0;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NEXTHDR_ICMP:
		अगर (likely(pskb_may_pull(skb,
					 nhoff + माप(काष्ठा icmp6hdr)))) अणु
			काष्ठा icmp6hdr *ih = (काष्ठा icmp6hdr *)
					(skb_network_header(skb) + nhoff);

			dअगरf = get_csum_dअगरf(ip6h, p);
			inet_proto_csum_replace_by_dअगरf(&ih->icmp6_cksum, skb,
							dअगरf, true);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

व्योम ila_update_ipv6_locator(काष्ठा sk_buff *skb, काष्ठा ila_params *p,
			     bool sir2ila)
अणु
	काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	काष्ठा ila_addr *iaddr = ila_a2i(&ip6h->daddr);

	चयन (p->csum_mode) अणु
	हाल ILA_CSUM_ADJUST_TRANSPORT:
		ila_csum_adjust_transport(skb, p);
		अवरोध;
	हाल ILA_CSUM_NEUTRAL_MAP:
		अगर (sir2ila) अणु
			अगर (WARN_ON(ila_csum_neutral_set(iaddr->ident))) अणु
				/* Checksum flag should never be
				 * set in a क्रमmatted SIR address.
				 */
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (!ila_csum_neutral_set(iaddr->ident)) अणु
			/* ILA to SIR translation and C-bit isn't
			 * set so we're good.
			 */
			अवरोध;
		पूर्ण
		ila_csum_करो_neutral_fmt(iaddr, p);
		अवरोध;
	हाल ILA_CSUM_NEUTRAL_MAP_AUTO:
		ila_csum_करो_neutral_nofmt(iaddr, p);
		अवरोध;
	हाल ILA_CSUM_NO_ACTION:
		अवरोध;
	पूर्ण

	/* Now change destination address */
	iaddr->loc = p->locator;
पूर्ण
