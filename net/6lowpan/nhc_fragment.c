<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN IPv6 Fragment Header compression according to RFC6282
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_NHC_FRAGMENT_IDLEN	1
#घोषणा LOWPAN_NHC_FRAGMENT_ID_0	0xe4
#घोषणा LOWPAN_NHC_FRAGMENT_MASK_0	0xfe

अटल व्योम fragment_nhid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_NHC_FRAGMENT_ID_0;
	nhc->idmask[0] = LOWPAN_NHC_FRAGMENT_MASK_0;
पूर्ण

LOWPAN_NHC(nhc_fragment, "RFC6282 Fragment", NEXTHDR_FRAGMENT, 0,
	   fragment_nhid_setup, LOWPAN_NHC_FRAGMENT_IDLEN, शून्य, शून्य);

module_lowpan_nhc(nhc_fragment);
MODULE_DESCRIPTION("6LoWPAN next header RFC6282 Fragment compression");
MODULE_LICENSE("GPL");
