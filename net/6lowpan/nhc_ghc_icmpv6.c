<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN ICMPv6 compression according to RFC7400
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_GHC_ICMPV6_IDLEN		1
#घोषणा LOWPAN_GHC_ICMPV6_ID_0		0xdf
#घोषणा LOWPAN_GHC_ICMPV6_MASK_0	0xff

अटल व्योम icmpv6_ghid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_GHC_ICMPV6_ID_0;
	nhc->idmask[0] = LOWPAN_GHC_ICMPV6_MASK_0;
पूर्ण

LOWPAN_NHC(ghc_icmpv6, "RFC7400 ICMPv6", NEXTHDR_ICMP, 0,
	   icmpv6_ghid_setup, LOWPAN_GHC_ICMPV6_IDLEN, शून्य, शून्य);

module_lowpan_nhc(ghc_icmpv6);
MODULE_DESCRIPTION("6LoWPAN generic header ICMPv6 compression");
MODULE_LICENSE("GPL");
