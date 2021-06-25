<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN Extension Header compression according to RFC7400
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_GHC_EXT_DEST_IDLEN	1
#घोषणा LOWPAN_GHC_EXT_DEST_ID_0	0xb6
#घोषणा LOWPAN_GHC_EXT_DEST_MASK_0	0xfe

अटल व्योम dest_ghid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_GHC_EXT_DEST_ID_0;
	nhc->idmask[0] = LOWPAN_GHC_EXT_DEST_MASK_0;
पूर्ण

LOWPAN_NHC(ghc_ext_dest, "RFC7400 Destination Extension Header", NEXTHDR_DEST,
	   0, dest_ghid_setup, LOWPAN_GHC_EXT_DEST_IDLEN, शून्य, शून्य);

module_lowpan_nhc(ghc_ext_dest);
MODULE_DESCRIPTION("6LoWPAN generic header destination extension compression");
MODULE_LICENSE("GPL");
