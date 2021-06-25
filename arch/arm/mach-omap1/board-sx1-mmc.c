<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-sx1-mmc.c
 *
 * Copyright (C) 2007 Instituto Nokia de Tecnologia - INdT
 * Author: Carlos Eduarकरो Aguiar <carlos.aguiar@indt.org.br>
 *
 * This code is based on linux/arch/arm/mach-omap1/board-h2-mmc.c, which is:
 * Copyright (C) 2007 Instituto Nokia de Tecnologia - INdT
 */

#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश <mach/hardware.h>
#समावेश "board-sx1.h"

#समावेश "mmc.h"

#अगर IS_ENABLED(CONFIG_MMC_OMAP)

अटल पूर्णांक mmc_set_घातer(काष्ठा device *dev, पूर्णांक slot, पूर्णांक घातer_on,
				पूर्णांक vdd)
अणु
	पूर्णांक err;
	u8 dat = 0;

	err = sx1_i2c_पढ़ो_byte(SOFIA_I2C_ADDR, SOFIA_POWER1_REG, &dat);
	अगर (err < 0)
		वापस err;

	अगर (घातer_on)
		dat |= SOFIA_MMC_POWER;
	अन्यथा
		dat &= ~SOFIA_MMC_POWER;

	वापस sx1_i2c_ग_लिखो_byte(SOFIA_I2C_ADDR, SOFIA_POWER1_REG, dat);
पूर्ण

/* Cover चयन is at OMAP_MPUIO(3) */
अटल काष्ठा omap_mmc_platक्रमm_data mmc1_data = अणु
	.nr_slots                       = 1,
	.slots[0]       = अणु
		.set_घातer              = mmc_set_घातer,
		.ocr_mask               = MMC_VDD_32_33 | MMC_VDD_33_34,
		.name                   = "mmcblk",
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_mmc_platक्रमm_data *mmc_data[OMAP15XX_NR_MMC];

व्योम __init sx1_mmc_init(व्योम)
अणु
	mmc_data[0] = &mmc1_data;
	omap1_init_mmc(mmc_data, OMAP15XX_NR_MMC);
पूर्ण

#अन्यथा

व्योम __init sx1_mmc_init(व्योम)
अणु
पूर्ण

#पूर्ण_अगर
