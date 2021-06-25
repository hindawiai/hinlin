<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN Extension Header compression according to RFC7400
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_GHC_EXT_ROUTE_IDLEN	1
#घोषणा LOWPAN_GHC_EXT_ROUTE_ID_0	0xb2
#घोषणा LOWPAN_GHC_EXT_ROUTE_MASK_0	0xfe

अटल व्योम route_ghid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_GHC_EXT_ROUTE_ID_0;
	nhc->idmask[0] = LOWPAN_GHC_EXT_ROUTE_MASK_0;
पूर्ण

LOWPAN_NHC(ghc_ext_route, "RFC7400 Routing Extension Header", NEXTHDR_ROUTING,
	   0, route_ghid_setup, LOWPAN_GHC_EXT_ROUTE_IDLEN, शून्य, शून्य);

module_lowpan_nhc(ghc_ext_route);
MODULE_DESCRIPTION("6LoWPAN generic header routing extension compression");
MODULE_LICENSE("GPL");
