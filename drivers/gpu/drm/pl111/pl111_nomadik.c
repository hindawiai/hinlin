<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश "pl111_nomadik.h"

#घोषणा PMU_CTRL_OFFSET 0x0000
#घोषणा PMU_CTRL_LCDNDIF BIT(26)

व्योम pl111_nomadik_init(काष्ठा device *dev)
अणु
	काष्ठा regmap *pmu_regmap;

	/*
	 * Just bail out of this is not found, we could be running
	 * multiplatक्रमm on something अन्यथा than Nomadik.
	 */
	pmu_regmap =
		syscon_regmap_lookup_by_compatible("stericsson,nomadik-pmu");
	अगर (IS_ERR(pmu_regmap))
		वापस;

	/*
	 * This bit in the PMU controller multiplexes the two graphics
	 * blocks found in the Nomadik STn8815. The other one is called
	 * MDIF (Master Display Interface) and माला_लो muxed out here.
	 */
	regmap_update_bits(pmu_regmap,
			   PMU_CTRL_OFFSET,
			   PMU_CTRL_LCDNDIF,
			   0);
	dev_info(dev, "set Nomadik PMU mux to CLCD mode\n");
पूर्ण
EXPORT_SYMBOL_GPL(pl111_nomadik_init);
