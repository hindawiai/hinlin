<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PowerQUICC II support functions
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "types.h"
#समावेश "fsl-soc.h"
#समावेश "pq2.h"
#समावेश "stdio.h"
#समावेश "io.h"

#घोषणा PQ2_SCCR (0x10c80/4) /* System Clock Configuration Register */
#घोषणा PQ2_SCMR (0x10c88/4) /* System Clock Mode Register */

अटल पूर्णांक pq2_corecnf_map[] = अणु
	3, 2, 2, 2, 4, 4, 5, 9, 6, 11, 8, 10, 3, 12, 7, -1,
	6, 5, 13, 2, 14, 4, 15, 9, 0, 11, 8, 10, 16, 12, 7, -1
पूर्ण;

/* Get various घड़ीs from crystal frequency.
 * Returns zero on failure and non-zero on success.
 */
पूर्णांक pq2_get_घड़ीs(u32 crystal, u32 *sysfreq, u32 *corefreq,
                   u32 *समयbase, u32 *brgfreq)
अणु
	u32 *immr;
	u32 sccr, scmr, मुख्यclk, busclk;
	पूर्णांक corecnf, busdf, plldf, pllmf, dfbrg;

	immr = fsl_get_immr();
	अगर (!immr) अणु
		म_लिखो("pq2_get_clocks: Couldn't get IMMR base.\r\n");
		वापस 0;
	पूर्ण

	sccr = in_be32(&immr[PQ2_SCCR]);
	scmr = in_be32(&immr[PQ2_SCMR]);

	dfbrg = sccr & 3;
	corecnf = (scmr >> 24) & 0x1f;
	busdf = (scmr >> 20) & 0xf;
	plldf = (scmr >> 12) & 1;
	pllmf = scmr & 0xfff;

	मुख्यclk = crystal * (pllmf + 1) / (plldf + 1);
	busclk = मुख्यclk / (busdf + 1);

	अगर (sysfreq)
		*sysfreq = मुख्यclk / 2;
	अगर (समयbase)
		*समयbase = busclk / 4;
	अगर (brgfreq)
		*brgfreq = मुख्यclk / (1 << ((dfbrg + 1) * 2));

	अगर (corefreq) अणु
		पूर्णांक coremult = pq2_corecnf_map[corecnf];

		अगर (coremult < 0)
			*corefreq = मुख्यclk / 2;
		अन्यथा अगर (coremult == 0)
			वापस 0;
		अन्यथा
			*corefreq = busclk * coremult / 2;
	पूर्ण

	वापस 1;
पूर्ण

/* Set common device tree fields based on the given घड़ी frequencies. */
व्योम pq2_set_घड़ीs(u32 sysfreq, u32 corefreq, u32 समयbase, u32 brgfreq)
अणु
	व्योम *node;

	dt_fixup_cpu_घड़ीs(corefreq, समयbase, sysfreq);

	node = finddevice("/soc/cpm");
	अगर (node)
		setprop(node, "clock-frequency", &sysfreq, 4);

	node = finddevice("/soc/cpm/brg");
	अगर (node)
		setprop(node, "clock-frequency", &brgfreq, 4);
पूर्ण

पूर्णांक pq2_fixup_घड़ीs(u32 crystal)
अणु
	u32 sysfreq, corefreq, समयbase, brgfreq;

	अगर (!pq2_get_घड़ीs(crystal, &sysfreq, &corefreq, &समयbase, &brgfreq))
		वापस 0;

	pq2_set_घड़ीs(sysfreq, corefreq, समयbase, brgfreq);
	वापस 1;
पूर्ण
