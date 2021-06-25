<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN IPv6 Destination Options Header compression according to
 *	RFC6282
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_NHC_DEST_IDLEN	1
#घोषणा LOWPAN_NHC_DEST_ID_0	0xe6
#घोषणा LOWPAN_NHC_DEST_MASK_0	0xfe

अटल व्योम dest_nhid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_NHC_DEST_ID_0;
	nhc->idmask[0] = LOWPAN_NHC_DEST_MASK_0;
पूर्ण

LOWPAN_NHC(nhc_dest, "RFC6282 Destination Options", NEXTHDR_DEST, 0,
	   dest_nhid_setup, LOWPAN_NHC_DEST_IDLEN, शून्य, शून्य);

module_lowpan_nhc(nhc_dest);
MODULE_DESCRIPTION("6LoWPAN next header RFC6282 Destination Options compression");
MODULE_LICENSE("GPL");
