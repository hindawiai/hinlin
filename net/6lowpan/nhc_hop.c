<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN IPv6 Hop-by-Hop Options Header compression according to RFC6282
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_NHC_HOP_IDLEN	1
#घोषणा LOWPAN_NHC_HOP_ID_0	0xe0
#घोषणा LOWPAN_NHC_HOP_MASK_0	0xfe

अटल व्योम hop_nhid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_NHC_HOP_ID_0;
	nhc->idmask[0] = LOWPAN_NHC_HOP_MASK_0;
पूर्ण

LOWPAN_NHC(nhc_hop, "RFC6282 Hop-by-Hop Options", NEXTHDR_HOP, 0,
	   hop_nhid_setup, LOWPAN_NHC_HOP_IDLEN, शून्य, शून्य);

module_lowpan_nhc(nhc_hop);
MODULE_DESCRIPTION("6LoWPAN next header RFC6282 Hop-by-Hop Options compression");
MODULE_LICENSE("GPL");
