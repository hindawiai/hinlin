<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN UDP compression according to RFC7400
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_GHC_UDP_IDLEN	1
#घोषणा LOWPAN_GHC_UDP_ID_0	0xd0
#घोषणा LOWPAN_GHC_UDP_MASK_0	0xf8

अटल व्योम udp_ghid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_GHC_UDP_ID_0;
	nhc->idmask[0] = LOWPAN_GHC_UDP_MASK_0;
पूर्ण

LOWPAN_NHC(ghc_udp, "RFC7400 UDP", NEXTHDR_UDP, 0,
	   udp_ghid_setup, LOWPAN_GHC_UDP_IDLEN, शून्य, शून्य);

module_lowpan_nhc(ghc_udp);
MODULE_DESCRIPTION("6LoWPAN generic header UDP compression");
MODULE_LICENSE("GPL");
