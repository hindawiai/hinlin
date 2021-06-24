<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN IPv6 Mobility Header compression according to RFC6282
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_NHC_MOBILITY_IDLEN	1
#घोषणा LOWPAN_NHC_MOBILITY_ID_0	0xe8
#घोषणा LOWPAN_NHC_MOBILITY_MASK_0	0xfe

अटल व्योम mobility_nhid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_NHC_MOBILITY_ID_0;
	nhc->idmask[0] = LOWPAN_NHC_MOBILITY_MASK_0;
पूर्ण

LOWPAN_NHC(nhc_mobility, "RFC6282 Mobility", NEXTHDR_MOBILITY, 0,
	   mobility_nhid_setup, LOWPAN_NHC_MOBILITY_IDLEN, शून्य, शून्य);

module_lowpan_nhc(nhc_mobility);
MODULE_DESCRIPTION("6LoWPAN next header RFC6282 Mobility compression");
MODULE_LICENSE("GPL");
