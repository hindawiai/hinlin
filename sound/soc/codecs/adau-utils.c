<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Shared helper functions क्रम devices from the ADAU family
 *
 * Copyright 2011-2016 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/gcd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "adau-utils.h"

पूर्णांक adau_calc_pll_cfg(अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out,
	uपूर्णांक8_t regs[5])
अणु
	अचिन्हित पूर्णांक r, n, m, i, j;
	अचिन्हित पूर्णांक भाग;

	अगर (!freq_out) अणु
		r = 0;
		n = 0;
		m = 0;
		भाग = 0;
	पूर्ण अन्यथा अणु
		अगर (freq_out % freq_in != 0) अणु
			भाग = DIV_ROUND_UP(freq_in, 13500000);
			freq_in /= भाग;
			r = freq_out / freq_in;
			i = freq_out % freq_in;
			j = gcd(i, freq_in);
			n = i / j;
			m = freq_in / j;
			भाग--;
		पूर्ण अन्यथा अणु
			r = freq_out / freq_in;
			n = 0;
			m = 0;
			भाग = 0;
		पूर्ण
		अगर (n > 0xffff || m > 0xffff || भाग > 3 || r > 8 || r < 2)
			वापस -EINVAL;
	पूर्ण

	regs[0] = m >> 8;
	regs[1] = m & 0xff;
	regs[2] = n >> 8;
	regs[3] = n & 0xff;
	regs[4] = (r << 3) | (भाग << 1);
	अगर (m != 0)
		regs[4] |= 1; /* Fractional mode */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adau_calc_pll_cfg);

MODULE_DESCRIPTION("ASoC ADAU audio CODECs shared helper functions");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL v2");
