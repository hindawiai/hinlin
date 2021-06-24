<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IPv6 library code, needed by अटल components when full IPv6 support is
 * not configured or अटल.
 */
#समावेश <linux/export.h>
#समावेश <net/ipv6.h>

/*
 * find out अगर nexthdr is a well-known extension header or a protocol
 */

bool ipv6_ext_hdr(u8 nexthdr)
अणु
	/*
	 * find out अगर nexthdr is an extension header or a protocol
	 */
	वापस   (nexthdr == NEXTHDR_HOP)	||
		 (nexthdr == NEXTHDR_ROUTING)	||
		 (nexthdr == NEXTHDR_FRAGMENT)	||
		 (nexthdr == NEXTHDR_AUTH)	||
		 (nexthdr == NEXTHDR_NONE)	||
		 (nexthdr == NEXTHDR_DEST);
पूर्ण
EXPORT_SYMBOL(ipv6_ext_hdr);

/*
 * Skip any extension headers. This is used by the ICMP module.
 *
 * Note that strictly speaking this conflicts with RFC 2460 4.0:
 * ...The contents and semantics of each extension header determine whether
 * or not to proceed to the next header.  Thereक्रमe, extension headers must
 * be processed strictly in the order they appear in the packet; a
 * receiver must not, क्रम example, scan through a packet looking क्रम a
 * particular kind of extension header and process that header prior to
 * processing all preceding ones.
 *
 * We करो exactly this. This is a protocol bug. We can't decide after a
 * seeing an unknown discard-with-error flavour TLV option अगर it's a
 * ICMP error message or not (errors should never be send in reply to
 * ICMP error messages).
 *
 * But I see no other way to करो this. This might need to be reexamined
 * when Linux implements ESP (and maybe AUTH) headers.
 * --AK
 *
 * This function parses (probably truncated) exthdr set "hdr".
 * "nexthdrp" initially poपूर्णांकs to some place,
 * where type of the first header can be found.
 *
 * It skips all well-known exthdrs, and वापसs poपूर्णांकer to the start
 * of unparsable area i.e. the first header with unknown type.
 * If it is not शून्य *nexthdr is updated by type/protocol of this header.
 *
 * NOTES: - अगर packet terminated with NEXTHDR_NONE it वापसs शून्य.
 *        - it may वापस poपूर्णांकer poपूर्णांकing beyond end of packet,
 *	    अगर the last recognized header is truncated in the middle.
 *        - अगर packet is truncated, so that all parsed headers are skipped,
 *	    it वापसs शून्य.
 *	  - First fragment header is skipped, not-first ones
 *	    are considered as unparsable.
 *	  - Reports the offset field of the final fragment header so it is
 *	    possible to tell whether this is a first fragment, later fragment,
 *	    or not fragmented.
 *	  - ESP is unparsable क्रम now and considered like
 *	    normal payload protocol.
 *	  - Note also special handling of AUTH header. Thanks to IPsec wizards.
 *
 * --ANK (980726)
 */

पूर्णांक ipv6_skip_exthdr(स्थिर काष्ठा sk_buff *skb, पूर्णांक start, u8 *nexthdrp,
		     __be16 *frag_offp)
अणु
	u8 nexthdr = *nexthdrp;

	*frag_offp = 0;

	जबतक (ipv6_ext_hdr(nexthdr)) अणु
		काष्ठा ipv6_opt_hdr _hdr, *hp;
		पूर्णांक hdrlen;

		अगर (nexthdr == NEXTHDR_NONE)
			वापस -1;
		hp = skb_header_poपूर्णांकer(skb, start, माप(_hdr), &_hdr);
		अगर (!hp)
			वापस -1;
		अगर (nexthdr == NEXTHDR_FRAGMENT) अणु
			__be16 _frag_off, *fp;
			fp = skb_header_poपूर्णांकer(skb,
						start+दुरत्व(काष्ठा frag_hdr,
							       frag_off),
						माप(_frag_off),
						&_frag_off);
			अगर (!fp)
				वापस -1;

			*frag_offp = *fp;
			अगर (ntohs(*frag_offp) & ~0x7)
				अवरोध;
			hdrlen = 8;
		पूर्ण अन्यथा अगर (nexthdr == NEXTHDR_AUTH)
			hdrlen = ipv6_authlen(hp);
		अन्यथा
			hdrlen = ipv6_optlen(hp);

		nexthdr = hp->nexthdr;
		start += hdrlen;
	पूर्ण

	*nexthdrp = nexthdr;
	वापस start;
पूर्ण
EXPORT_SYMBOL(ipv6_skip_exthdr);

पूर्णांक ipv6_find_tlv(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक type)
अणु
	स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);
	पूर्णांक packet_len = skb_tail_poपूर्णांकer(skb) - skb_network_header(skb);
	काष्ठा ipv6_opt_hdr *hdr;
	पूर्णांक len;

	अगर (offset + 2 > packet_len)
		जाओ bad;
	hdr = (काष्ठा ipv6_opt_hdr *)(nh + offset);
	len = ((hdr->hdrlen + 1) << 3);

	अगर (offset + len > packet_len)
		जाओ bad;

	offset += 2;
	len -= 2;

	जबतक (len > 0) अणु
		पूर्णांक opttype = nh[offset];
		पूर्णांक optlen;

		अगर (opttype == type)
			वापस offset;

		चयन (opttype) अणु
		हाल IPV6_TLV_PAD1:
			optlen = 1;
			अवरोध;
		शेष:
			optlen = nh[offset + 1] + 2;
			अगर (optlen > len)
				जाओ bad;
			अवरोध;
		पूर्ण
		offset += optlen;
		len -= optlen;
	पूर्ण
	/* not_found */
 bad:
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(ipv6_find_tlv);

/*
 * find the offset to specअगरied header or the protocol number of last header
 * अगर target < 0. "last header" is transport protocol header, ESP, or
 * "No next header".
 *
 * Note that *offset is used as input/output parameter, and अगर it is not zero,
 * then it must be a valid offset to an inner IPv6 header. This can be used
 * to explore inner IPv6 header, eg. ICMPv6 error messages.
 *
 * If target header is found, its offset is set in *offset and वापस protocol
 * number. Otherwise, वापस -1.
 *
 * If the first fragment करोesn't contain the final protocol header or
 * NEXTHDR_NONE it is considered invalid.
 *
 * Note that non-1st fragment is special हाल that "the protocol number
 * of last header" is "next header" field in Fragment header. In this हाल,
 * *offset is meaningless and fragment offset is stored in *fragoff अगर fragoff
 * isn't शून्य.
 *
 * अगर flags is not शून्य and it's a fragment, then the frag flag
 * IP6_FH_F_FRAG will be set. If it's an AH header, the
 * IP6_FH_F_AUTH flag is set and target < 0, then this function will
 * stop at the AH header. If IP6_FH_F_SKIP_RH flag was passed, then this
 * function will skip all those routing headers, where segements_left was 0.
 */
पूर्णांक ipv6_find_hdr(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक *offset,
		  पूर्णांक target, अचिन्हित लघु *fragoff, पूर्णांक *flags)
अणु
	अचिन्हित पूर्णांक start = skb_network_offset(skb) + माप(काष्ठा ipv6hdr);
	u8 nexthdr = ipv6_hdr(skb)->nexthdr;
	bool found;

	अगर (fragoff)
		*fragoff = 0;

	अगर (*offset) अणु
		काष्ठा ipv6hdr _ip6, *ip6;

		ip6 = skb_header_poपूर्णांकer(skb, *offset, माप(_ip6), &_ip6);
		अगर (!ip6 || (ip6->version != 6))
			वापस -EBADMSG;
		start = *offset + माप(काष्ठा ipv6hdr);
		nexthdr = ip6->nexthdr;
	पूर्ण

	करो अणु
		काष्ठा ipv6_opt_hdr _hdr, *hp;
		अचिन्हित पूर्णांक hdrlen;
		found = (nexthdr == target);

		अगर ((!ipv6_ext_hdr(nexthdr)) || nexthdr == NEXTHDR_NONE) अणु
			अगर (target < 0 || found)
				अवरोध;
			वापस -ENOENT;
		पूर्ण

		hp = skb_header_poपूर्णांकer(skb, start, माप(_hdr), &_hdr);
		अगर (!hp)
			वापस -EBADMSG;

		अगर (nexthdr == NEXTHDR_ROUTING) अणु
			काष्ठा ipv6_rt_hdr _rh, *rh;

			rh = skb_header_poपूर्णांकer(skb, start, माप(_rh),
						&_rh);
			अगर (!rh)
				वापस -EBADMSG;

			अगर (flags && (*flags & IP6_FH_F_SKIP_RH) &&
			    rh->segments_left == 0)
				found = false;
		पूर्ण

		अगर (nexthdr == NEXTHDR_FRAGMENT) अणु
			अचिन्हित लघु _frag_off;
			__be16 *fp;

			अगर (flags)	/* Indicate that this is a fragment */
				*flags |= IP6_FH_F_FRAG;
			fp = skb_header_poपूर्णांकer(skb,
						start+दुरत्व(काष्ठा frag_hdr,
							       frag_off),
						माप(_frag_off),
						&_frag_off);
			अगर (!fp)
				वापस -EBADMSG;

			_frag_off = ntohs(*fp) & ~0x7;
			अगर (_frag_off) अणु
				अगर (target < 0 &&
				    ((!ipv6_ext_hdr(hp->nexthdr)) ||
				     hp->nexthdr == NEXTHDR_NONE)) अणु
					अगर (fragoff)
						*fragoff = _frag_off;
					वापस hp->nexthdr;
				पूर्ण
				अगर (!found)
					वापस -ENOENT;
				अगर (fragoff)
					*fragoff = _frag_off;
				अवरोध;
			पूर्ण
			hdrlen = 8;
		पूर्ण अन्यथा अगर (nexthdr == NEXTHDR_AUTH) अणु
			अगर (flags && (*flags & IP6_FH_F_AUTH) && (target < 0))
				अवरोध;
			hdrlen = ipv6_authlen(hp);
		पूर्ण अन्यथा
			hdrlen = ipv6_optlen(hp);

		अगर (!found) अणु
			nexthdr = hp->nexthdr;
			start += hdrlen;
		पूर्ण
	पूर्ण जबतक (!found);

	*offset = start;
	वापस nexthdr;
पूर्ण
EXPORT_SYMBOL(ipv6_find_hdr);
