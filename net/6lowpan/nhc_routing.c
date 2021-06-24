<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN IPv6 Routing Header compression according to RFC6282
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_NHC_ROUTING_IDLEN	1
#घोषणा LOWPAN_NHC_ROUTING_ID_0		0xe2
#घोषणा LOWPAN_NHC_ROUTING_MASK_0	0xfe

अटल व्योम routing_nhid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_NHC_ROUTING_ID_0;
	nhc->idmask[0] = LOWPAN_NHC_ROUTING_MASK_0;
पूर्ण

LOWPAN_NHC(nhc_routing, "RFC6282 Routing", NEXTHDR_ROUTING, 0,
	   routing_nhid_setup, LOWPAN_NHC_ROUTING_IDLEN, शून्य, शून्य);

module_lowpan_nhc(nhc_routing);
MODULE_DESCRIPTION("6LoWPAN next header RFC6282 Routing compression");
MODULE_LICENSE("GPL");
