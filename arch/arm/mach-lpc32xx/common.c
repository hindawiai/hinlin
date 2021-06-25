<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-lpc32xx/common.c
 *
 * Author: Kevin Wells <kevin.wells@nxp.com>
 *
 * Copyright (C) 2010 NXP Semiconductors
 */

#समावेश <linux/init.h>
#समावेश <linux/soc/nxp/lpc32xx-misc.h>

#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश "lpc32xx.h"
#समावेश "common.h"

/*
 * Returns the unique ID क्रम the device
 */
व्योम lpc32xx_get_uid(u32 devid[4])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		devid[i] = __raw_पढ़ोl(LPC32XX_CLKPWR_DEVID(i << 2));
पूर्ण

/*
 * Detects and वापसs IRAM size क्रम the device variation
 */
#घोषणा LPC32XX_IRAM_BANK_SIZE SZ_128K
अटल u32 iram_size;
u32 lpc32xx_वापस_iram(व्योम __iomem **mapbase, dma_addr_t *dmaaddr)
अणु
	अगर (iram_size == 0) अणु
		u32 savedval1, savedval2;
		व्योम __iomem *iramptr1, *iramptr2;

		iramptr1 = io_p2v(LPC32XX_IRAM_BASE);
		iramptr2 = io_p2v(LPC32XX_IRAM_BASE + LPC32XX_IRAM_BANK_SIZE);
		savedval1 = __raw_पढ़ोl(iramptr1);
		savedval2 = __raw_पढ़ोl(iramptr2);

		अगर (savedval1 == savedval2) अणु
			__raw_ग_लिखोl(savedval2 + 1, iramptr2);
			अगर (__raw_पढ़ोl(iramptr1) == savedval2 + 1)
				iram_size = LPC32XX_IRAM_BANK_SIZE;
			अन्यथा
				iram_size = LPC32XX_IRAM_BANK_SIZE * 2;
			__raw_ग_लिखोl(savedval2, iramptr2);
		पूर्ण अन्यथा
			iram_size = LPC32XX_IRAM_BANK_SIZE * 2;
	पूर्ण
	अगर (dmaaddr)
		*dmaaddr = LPC32XX_IRAM_BASE;
	अगर (mapbase)
		*mapbase = io_p2v(LPC32XX_IRAM_BASE);

	वापस iram_size;
पूर्ण
EXPORT_SYMBOL_GPL(lpc32xx_वापस_iram);

व्योम lpc32xx_set_phy_पूर्णांकerface_mode(phy_पूर्णांकerface_t mode)
अणु
	u32 पंचांगp = __raw_पढ़ोl(LPC32XX_CLKPWR_MACCLK_CTRL);
	पंचांगp &= ~LPC32XX_CLKPWR_MACCTRL_PINS_MSK;
	अगर (mode == PHY_INTERFACE_MODE_MII)
		पंचांगp |= LPC32XX_CLKPWR_MACCTRL_USE_MII_PINS;
	अन्यथा
		पंचांगp |= LPC32XX_CLKPWR_MACCTRL_USE_RMII_PINS;
	__raw_ग_लिखोl(पंचांगp, LPC32XX_CLKPWR_MACCLK_CTRL);
पूर्ण
EXPORT_SYMBOL_GPL(lpc32xx_set_phy_पूर्णांकerface_mode);

अटल काष्ठा map_desc lpc32xx_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)IO_ADDRESS(LPC32XX_AHB0_START),
		.pfn		= __phys_to_pfn(LPC32XX_AHB0_START),
		.length		= LPC32XX_AHB0_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= (अचिन्हित दीर्घ)IO_ADDRESS(LPC32XX_AHB1_START),
		.pfn		= __phys_to_pfn(LPC32XX_AHB1_START),
		.length		= LPC32XX_AHB1_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= (अचिन्हित दीर्घ)IO_ADDRESS(LPC32XX_FABAPB_START),
		.pfn		= __phys_to_pfn(LPC32XX_FABAPB_START),
		.length		= LPC32XX_FABAPB_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= (अचिन्हित दीर्घ)IO_ADDRESS(LPC32XX_IRAM_BASE),
		.pfn		= __phys_to_pfn(LPC32XX_IRAM_BASE),
		.length		= (LPC32XX_IRAM_BANK_SIZE * 2),
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

व्योम __init lpc32xx_map_io(व्योम)
अणु
	iotable_init(lpc32xx_io_desc, ARRAY_SIZE(lpc32xx_io_desc));
पूर्ण

अटल पूर्णांक __init lpc32xx_check_uid(व्योम)
अणु
	u32 uid[4];

	lpc32xx_get_uid(uid);

	prपूर्णांकk(KERN_INFO "LPC32XX unique ID: %08x%08x%08x%08x\n",
		uid[3], uid[2], uid[1], uid[0]);

	अगर (!प्रणाली_serial_low && !प्रणाली_serial_high) अणु
		प्रणाली_serial_low = uid[0];
		प्रणाली_serial_high = uid[1];
	पूर्ण

	वापस 1;
पूर्ण
arch_initcall(lpc32xx_check_uid);
