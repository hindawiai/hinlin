<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _GFP_H
#घोषणा _GFP_H

#समावेश <linux/types.h>

#घोषणा __GFP_BITS_SHIFT 26
#घोषणा __GFP_BITS_MASK ((gfp_t)((1 << __GFP_BITS_SHIFT) - 1))

#घोषणा __GFP_HIGH		0x20u
#घोषणा __GFP_IO		0x40u
#घोषणा __GFP_FS		0x80u
#घोषणा __GFP_NOWARN		0x200u
#घोषणा __GFP_ZERO		0x8000u
#घोषणा __GFP_ATOMIC		0x80000u
#घोषणा __GFP_ACCOUNT		0x100000u
#घोषणा __GFP_सूचीECT_RECLAIM	0x400000u
#घोषणा __GFP_KSWAPD_RECLAIM	0x2000000u

#घोषणा __GFP_RECLAIM	(__GFP_सूचीECT_RECLAIM|__GFP_KSWAPD_RECLAIM)

#घोषणा GFP_ZONEMASK	0x0fu
#घोषणा GFP_ATOMIC	(__GFP_HIGH|__GFP_ATOMIC|__GFP_KSWAPD_RECLAIM)
#घोषणा GFP_KERNEL	(__GFP_RECLAIM | __GFP_IO | __GFP_FS)
#घोषणा GFP_NOWAIT	(__GFP_KSWAPD_RECLAIM)


अटल अंतरभूत bool gfpflags_allow_blocking(स्थिर gfp_t gfp_flags)
अणु
	वापस !!(gfp_flags & __GFP_सूचीECT_RECLAIM);
पूर्ण

#पूर्ण_अगर
