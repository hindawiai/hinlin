<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <यंत्र/भाग64.h>

#समावेश "clk.h"

#घोषणा भाग_mask(w) ((1 << (w)) - 1)

पूर्णांक भाग_frac_get(अचिन्हित दीर्घ rate, अचिन्हित parent_rate, u8 width,
		 u8 frac_width, u8 flags)
अणु
	u64 भागider_ux1 = parent_rate;
	पूर्णांक mul;

	अगर (!rate)
		वापस 0;

	mul = 1 << frac_width;

	अगर (!(flags & TEGRA_DIVIDER_INT))
		भागider_ux1 *= mul;

	अगर (flags & TEGRA_DIVIDER_ROUND_UP)
		भागider_ux1 += rate - 1;

	करो_भाग(भागider_ux1, rate);

	अगर (flags & TEGRA_DIVIDER_INT)
		भागider_ux1 *= mul;

	अगर (भागider_ux1 < mul)
		वापस 0;

	भागider_ux1 -= mul;

	अगर (भागider_ux1 > भाग_mask(width))
		वापस भाग_mask(width);

	वापस भागider_ux1;
पूर्ण
