<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-h3-mmc.c
 *
 * Copyright (C) 2007 Instituto Nokia de Tecnologia - INdT
 * Author: Felipe Balbi <felipe.lima@indt.org.br>
 *
 * This code is based on linux/arch/arm/mach-omap2/board-n800-mmc.c, which is:
 * Copyright (C) 2006 Nokia Corporation
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/tps65010.h>

#समावेश "common.h"
#समावेश "board-h3.h"
#समावेश "mmc.h"

#अगर IS_ENABLED(CONFIG_MMC_OMAP)

अटल पूर्णांक mmc_set_घातer(काष्ठा device *dev, पूर्णांक slot, पूर्णांक घातer_on,
				पूर्णांक vdd)
अणु
	gpio_set_value(H3_TPS_GPIO_MMC_PWR_EN, घातer_on);
	वापस 0;
पूर्ण

/*
 * H3 could use the following functions tested:
 * - mmc_get_cover_state that uses OMAP_MPUIO(1)
 * - mmc_get_wp that maybe uses OMAP_MPUIO(3)
 */
अटल काष्ठा omap_mmc_platक्रमm_data mmc1_data = अणु
	.nr_slots                       = 1,
	.slots[0]       = अणु
		.set_घातer              = mmc_set_घातer,
		.ocr_mask               = MMC_VDD_32_33 | MMC_VDD_33_34,
		.name                   = "mmcblk",
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_mmc_platक्रमm_data *mmc_data[OMAP16XX_NR_MMC];

व्योम __init h3_mmc_init(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_request(H3_TPS_GPIO_MMC_PWR_EN, "MMC power");
	अगर (ret < 0)
		वापस;
	gpio_direction_output(H3_TPS_GPIO_MMC_PWR_EN, 0);

	mmc_data[0] = &mmc1_data;
	omap1_init_mmc(mmc_data, OMAP16XX_NR_MMC);
पूर्ण

#अन्यथा

व्योम __init h3_mmc_init(व्योम)
अणु
पूर्ण

#पूर्ण_अगर
