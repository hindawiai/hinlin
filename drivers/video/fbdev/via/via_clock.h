<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.
 * Copyright 2011 Florian Tobias Schandinat <FlorianSchandinat@gmx.de>
 */
/*
 * घड़ी and PLL management functions
 */

#अगर_अघोषित __VIA_CLOCK_H__
#घोषणा __VIA_CLOCK_H__

#समावेश <linux/types.h>

क्रमागत via_clksrc अणु
	VIA_CLKSRC_X1 = 0,
	VIA_CLKSRC_TVX1,
	VIA_CLKSRC_TVPLL,
	VIA_CLKSRC_DVP1TVCLKR,
	VIA_CLKSRC_CAP0,
	VIA_CLKSRC_CAP1,
पूर्ण;

काष्ठा via_pll_config अणु
	u16 multiplier;
	u8 भागisor;
	u8 rshअगरt;
पूर्ण;

काष्ठा via_घड़ी अणु
	व्योम (*set_primary_घड़ी_state)(u8 state);
	व्योम (*set_primary_घड़ी_source)(क्रमागत via_clksrc src, bool use_pll);
	व्योम (*set_primary_pll_state)(u8 state);
	व्योम (*set_primary_pll)(काष्ठा via_pll_config config);

	व्योम (*set_secondary_घड़ी_state)(u8 state);
	व्योम (*set_secondary_घड़ी_source)(क्रमागत via_clksrc src, bool use_pll);
	व्योम (*set_secondary_pll_state)(u8 state);
	व्योम (*set_secondary_pll)(काष्ठा via_pll_config config);

	व्योम (*set_engine_pll_state)(u8 state);
	व्योम (*set_engine_pll)(काष्ठा via_pll_config config);
पूर्ण;


अटल अंतरभूत u32 get_pll_पूर्णांकernal_frequency(u32 ref_freq,
	काष्ठा via_pll_config pll)
अणु
	वापस ref_freq / pll.भागisor * pll.multiplier;
पूर्ण

अटल अंतरभूत u32 get_pll_output_frequency(u32 ref_freq,
	काष्ठा via_pll_config pll)
अणु
	वापस get_pll_पूर्णांकernal_frequency(ref_freq, pll) >> pll.rshअगरt;
पूर्ण

व्योम via_घड़ी_init(काष्ठा via_घड़ी *घड़ी, पूर्णांक gfx_chip);

#पूर्ण_अगर /* __VIA_CLOCK_H__ */
