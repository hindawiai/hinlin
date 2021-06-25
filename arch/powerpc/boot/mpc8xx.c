<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MPC8xx support functions
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "types.h"
#समावेश "fsl-soc.h"
#समावेश "mpc8xx.h"
#समावेश "stdio.h"
#समावेश "io.h"

#घोषणा MPC8XX_PLPRCR (0x284/4) /* PLL and Reset Control Register */

/* Return प्रणाली घड़ी from crystal frequency */
u32 mpc885_get_घड़ी(u32 crystal)
अणु
	u32 *immr;
	u32 plprcr;
	पूर्णांक mfi, mfn, mfd, pdf;
	u32 ret;

	immr = fsl_get_immr();
	अगर (!immr) अणु
		म_लिखो("mpc885_get_clock: Couldn't get IMMR base.\r\n");
		वापस 0;
	पूर्ण

	plprcr = in_be32(&immr[MPC8XX_PLPRCR]);

	mfi = (plprcr >> 16) & 15;
	अगर (mfi < 5) अणु
		म_लिखो("Warning: PLPRCR[MFI] value of %d out-of-bounds\r\n",
		       mfi);
		mfi = 5;
	पूर्ण

	pdf = (plprcr >> 1) & 0xf;
	mfd = (plprcr >> 22) & 0x1f;
	mfn = (plprcr >> 27) & 0x1f;

	ret = crystal * mfi;

	अगर (mfn != 0)
		ret += crystal * mfn / (mfd + 1);

	वापस ret / (pdf + 1);
पूर्ण

/* Set common device tree fields based on the given घड़ी frequencies. */
व्योम mpc8xx_set_घड़ीs(u32 sysclk)
अणु
	व्योम *node;

	dt_fixup_cpu_घड़ीs(sysclk, sysclk / 16, sysclk);

	node = finddevice("/soc/cpm");
	अगर (node)
		setprop(node, "clock-frequency", &sysclk, 4);

	node = finddevice("/soc/cpm/brg");
	अगर (node)
		setprop(node, "clock-frequency", &sysclk, 4);
पूर्ण

पूर्णांक mpc885_fixup_घड़ीs(u32 crystal)
अणु
	u32 sysclk = mpc885_get_घड़ी(crystal);
	अगर (!sysclk)
		वापस 0;

	mpc8xx_set_घड़ीs(sysclk);
	वापस 1;
पूर्ण
