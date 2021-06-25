<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN Extension Header compression according to RFC7400
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_GHC_EXT_HOP_IDLEN	1
#घोषणा LOWPAN_GHC_EXT_HOP_ID_0		0xb0
#घोषणा LOWPAN_GHC_EXT_HOP_MASK_0	0xfe

अटल व्योम hop_ghid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_GHC_EXT_HOP_ID_0;
	nhc->idmask[0] = LOWPAN_GHC_EXT_HOP_MASK_0;
पूर्ण

LOWPAN_NHC(ghc_ext_hop, "RFC7400 Hop-by-Hop Extension Header", NEXTHDR_HOP, 0,
	   hop_ghid_setup, LOWPAN_GHC_EXT_HOP_IDLEN, शून्य, शून्य);

module_lowpan_nhc(ghc_ext_hop);
MODULE_DESCRIPTION("6LoWPAN generic header hop-by-hop extension compression");
MODULE_LICENSE("GPL");
