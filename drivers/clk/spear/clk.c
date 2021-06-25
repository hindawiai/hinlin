<शैली गुरु>
/*
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * SPEAr clk - Common routines
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/types.h>
#समावेश "clk.h"

दीर्घ clk_round_rate_index(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
		अचिन्हित दीर्घ parent_rate, clk_calc_rate calc_rate, u8 rtbl_cnt,
		पूर्णांक *index)
अणु
	अचिन्हित दीर्घ prev_rate, rate = 0;

	क्रम (*index = 0; *index < rtbl_cnt; (*index)++) अणु
		prev_rate = rate;
		rate = calc_rate(hw, parent_rate, *index);
		अगर (drate < rate) अणु
			/* previous घड़ी was best */
			अगर (*index) अणु
				rate = prev_rate;
				(*index)--;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((*index) == rtbl_cnt)
		(*index)--;

	वापस rate;
पूर्ण
