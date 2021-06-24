<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN IPv6 Header compression according to RFC6282
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_NHC_IPV6_IDLEN	1
#घोषणा LOWPAN_NHC_IPV6_ID_0	0xee
#घोषणा LOWPAN_NHC_IPV6_MASK_0	0xfe

अटल व्योम ipv6_nhid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_NHC_IPV6_ID_0;
	nhc->idmask[0] = LOWPAN_NHC_IPV6_MASK_0;
पूर्ण

LOWPAN_NHC(nhc_ipv6, "RFC6282 IPv6", NEXTHDR_IPV6, 0, ipv6_nhid_setup,
	   LOWPAN_NHC_IPV6_IDLEN, शून्य, शून्य);

module_lowpan_nhc(nhc_ipv6);
MODULE_DESCRIPTION("6LoWPAN next header RFC6282 IPv6 compression");
MODULE_LICENSE("GPL");
