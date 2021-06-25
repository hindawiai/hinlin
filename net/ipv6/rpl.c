<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Authors:
 * (C) 2020 Alexander Aring <alex.aring@gmail.com>
 */

#समावेश <net/ipv6.h>
#समावेश <net/rpl.h>

#घोषणा IPV6_PFXTAIL_LEN(x) (माप(काष्ठा in6_addr) - (x))
#घोषणा IPV6_RPL_BEST_ADDR_COMPRESSION 15

अटल व्योम ipv6_rpl_addr_decompress(काष्ठा in6_addr *dst,
				     स्थिर काष्ठा in6_addr *daddr,
				     स्थिर व्योम *post, अचिन्हित अक्षर pfx)
अणु
	स_नकल(dst, daddr, pfx);
	स_नकल(&dst->s6_addr[pfx], post, IPV6_PFXTAIL_LEN(pfx));
पूर्ण

अटल व्योम ipv6_rpl_addr_compress(व्योम *dst, स्थिर काष्ठा in6_addr *addr,
				   अचिन्हित अक्षर pfx)
अणु
	स_नकल(dst, &addr->s6_addr[pfx], IPV6_PFXTAIL_LEN(pfx));
पूर्ण

अटल व्योम *ipv6_rpl_segdata_pos(स्थिर काष्ठा ipv6_rpl_sr_hdr *hdr, पूर्णांक i)
अणु
	वापस (व्योम *)&hdr->rpl_segdata[i * IPV6_PFXTAIL_LEN(hdr->cmpri)];
पूर्ण

माप_प्रकार ipv6_rpl_srh_size(अचिन्हित अक्षर n, अचिन्हित अक्षर cmpri,
			 अचिन्हित अक्षर cmpre)
अणु
	वापस (n * IPV6_PFXTAIL_LEN(cmpri)) + IPV6_PFXTAIL_LEN(cmpre);
पूर्ण

व्योम ipv6_rpl_srh_decompress(काष्ठा ipv6_rpl_sr_hdr *outhdr,
			     स्थिर काष्ठा ipv6_rpl_sr_hdr *inhdr,
			     स्थिर काष्ठा in6_addr *daddr, अचिन्हित अक्षर n)
अणु
	पूर्णांक i;

	outhdr->nexthdr = inhdr->nexthdr;
	outhdr->hdrlen = (((n + 1) * माप(काष्ठा in6_addr)) >> 3);
	outhdr->pad = 0;
	outhdr->type = inhdr->type;
	outhdr->segments_left = inhdr->segments_left;
	outhdr->cmpri = 0;
	outhdr->cmpre = 0;

	क्रम (i = 0; i < n; i++)
		ipv6_rpl_addr_decompress(&outhdr->rpl_segaddr[i], daddr,
					 ipv6_rpl_segdata_pos(inhdr, i),
					 inhdr->cmpri);

	ipv6_rpl_addr_decompress(&outhdr->rpl_segaddr[n], daddr,
				 ipv6_rpl_segdata_pos(inhdr, n),
				 inhdr->cmpre);
पूर्ण

अटल अचिन्हित अक्षर ipv6_rpl_srh_calc_cmpri(स्थिर काष्ठा ipv6_rpl_sr_hdr *inhdr,
					     स्थिर काष्ठा in6_addr *daddr,
					     अचिन्हित अक्षर n)
अणु
	अचिन्हित अक्षर plen;
	पूर्णांक i;

	क्रम (plen = 0; plen < माप(*daddr); plen++) अणु
		क्रम (i = 0; i < n; i++) अणु
			अगर (daddr->s6_addr[plen] !=
			    inhdr->rpl_segaddr[i].s6_addr[plen])
				वापस plen;
		पूर्ण
	पूर्ण

	वापस IPV6_RPL_BEST_ADDR_COMPRESSION;
पूर्ण

अटल अचिन्हित अक्षर ipv6_rpl_srh_calc_cmpre(स्थिर काष्ठा in6_addr *daddr,
					     स्थिर काष्ठा in6_addr *last_segment)
अणु
	अचिन्हित पूर्णांक plen;

	क्रम (plen = 0; plen < माप(*daddr); plen++) अणु
		अगर (daddr->s6_addr[plen] != last_segment->s6_addr[plen])
			वापस plen;
	पूर्ण

	वापस IPV6_RPL_BEST_ADDR_COMPRESSION;
पूर्ण

व्योम ipv6_rpl_srh_compress(काष्ठा ipv6_rpl_sr_hdr *outhdr,
			   स्थिर काष्ठा ipv6_rpl_sr_hdr *inhdr,
			   स्थिर काष्ठा in6_addr *daddr, अचिन्हित अक्षर n)
अणु
	अचिन्हित अक्षर cmpri, cmpre;
	माप_प्रकार seglen;
	पूर्णांक i;

	cmpri = ipv6_rpl_srh_calc_cmpri(inhdr, daddr, n);
	cmpre = ipv6_rpl_srh_calc_cmpre(daddr, &inhdr->rpl_segaddr[n]);

	outhdr->nexthdr = inhdr->nexthdr;
	seglen = (n * IPV6_PFXTAIL_LEN(cmpri)) + IPV6_PFXTAIL_LEN(cmpre);
	outhdr->hdrlen = seglen >> 3;
	अगर (seglen & 0x7) अणु
		outhdr->hdrlen++;
		outhdr->pad = 8 - (seglen & 0x7);
	पूर्ण अन्यथा अणु
		outhdr->pad = 0;
	पूर्ण
	outhdr->type = inhdr->type;
	outhdr->segments_left = inhdr->segments_left;
	outhdr->cmpri = cmpri;
	outhdr->cmpre = cmpre;

	क्रम (i = 0; i < n; i++)
		ipv6_rpl_addr_compress(ipv6_rpl_segdata_pos(outhdr, i),
				       &inhdr->rpl_segaddr[i], cmpri);

	ipv6_rpl_addr_compress(ipv6_rpl_segdata_pos(outhdr, n),
			       &inhdr->rpl_segaddr[n], cmpre);
पूर्ण
