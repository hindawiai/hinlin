<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * ChipCommon core driver
 *
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <m@bues.ch>
 * Copyright 2012, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"
#समावेश <linux/bcm47xx_wdt.h>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bcma/bcma.h>

अटल अंतरभूत u32 bcma_cc_ग_लिखो32_masked(काष्ठा bcma_drv_cc *cc, u16 offset,
					 u32 mask, u32 value)
अणु
	value &= mask;
	value |= bcma_cc_पढ़ो32(cc, offset) & ~mask;
	bcma_cc_ग_लिखो32(cc, offset, value);

	वापस value;
पूर्ण

u32 bcma_chipco_get_alp_घड़ी(काष्ठा bcma_drv_cc *cc)
अणु
	अगर (cc->capabilities & BCMA_CC_CAP_PMU)
		वापस bcma_pmu_get_alp_घड़ी(cc);

	वापस 20000000;
पूर्ण
EXPORT_SYMBOL_GPL(bcma_chipco_get_alp_घड़ी);

अटल bool bcma_core_cc_has_pmu_watchकरोg(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;

	अगर (cc->capabilities & BCMA_CC_CAP_PMU) अणु
		अगर (bus->chipinfo.id == BCMA_CHIP_ID_BCM53573) अणु
			WARN(bus->chipinfo.rev <= 1, "No watchdog available\n");
			/* 53573B0 and 53573B1 have bugged PMU watchकरोg. It can
			 * be enabled but समयr can't be bumped. Use CC one
			 * instead.
			 */
			वापस false;
		पूर्ण
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

अटल u32 bcma_chipco_watchकरोg_get_max_समयr(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;
	u32 nb;

	अगर (bcma_core_cc_has_pmu_watchकरोg(cc)) अणु
		अगर (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706)
			nb = 32;
		अन्यथा अगर (cc->core->id.rev < 26)
			nb = 16;
		अन्यथा
			nb = (cc->core->id.rev >= 37) ? 32 : 24;
	पूर्ण अन्यथा अणु
		nb = 28;
	पूर्ण
	अगर (nb == 32)
		वापस 0xffffffff;
	अन्यथा
		वापस (1 << nb) - 1;
पूर्ण

अटल u32 bcma_chipco_watchकरोg_समयr_set_wdt(काष्ठा bcm47xx_wdt *wdt,
					      u32 ticks)
अणु
	काष्ठा bcma_drv_cc *cc = bcm47xx_wdt_get_drvdata(wdt);

	वापस bcma_chipco_watchकरोg_समयr_set(cc, ticks);
पूर्ण

अटल u32 bcma_chipco_watchकरोg_समयr_set_ms_wdt(काष्ठा bcm47xx_wdt *wdt,
						 u32 ms)
अणु
	काष्ठा bcma_drv_cc *cc = bcm47xx_wdt_get_drvdata(wdt);
	u32 ticks;

	ticks = bcma_chipco_watchकरोg_समयr_set(cc, cc->ticks_per_ms * ms);
	वापस ticks / cc->ticks_per_ms;
पूर्ण

अटल पूर्णांक bcma_chipco_watchकरोg_ticks_per_ms(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;

	अगर (cc->capabilities & BCMA_CC_CAP_PMU) अणु
		अगर (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706)
			/* 4706 CC and PMU watchकरोgs are घड़ीed at 1/4 of ALP
			 * घड़ी
			 */
			वापस bcma_chipco_get_alp_घड़ी(cc) / 4000;
		अन्यथा
			/* based on 32KHz ILP घड़ी */
			वापस 32;
	पूर्ण अन्यथा अणु
		वापस bcma_chipco_get_alp_घड़ी(cc) / 1000;
	पूर्ण
पूर्ण

पूर्णांक bcma_chipco_watchकरोg_रेजिस्टर(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;
	काष्ठा bcm47xx_wdt wdt = अणुपूर्ण;
	काष्ठा platक्रमm_device *pdev;

	अगर (bus->chipinfo.id == BCMA_CHIP_ID_BCM53573 &&
	    bus->chipinfo.rev <= 1) अणु
		pr_debug("No watchdog on 53573A0 / 53573A1\n");
		वापस 0;
	पूर्ण

	wdt.driver_data = cc;
	wdt.समयr_set = bcma_chipco_watchकरोg_समयr_set_wdt;
	wdt.समयr_set_ms = bcma_chipco_watchकरोg_समयr_set_ms_wdt;
	wdt.max_समयr_ms =
		bcma_chipco_watchकरोg_get_max_समयr(cc) / cc->ticks_per_ms;

	pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "bcm47xx-wdt",
					     bus->num, &wdt,
					     माप(wdt));
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	cc->watchकरोg = pdev;

	वापस 0;
पूर्ण

अटल व्योम bcma_core_chipcommon_flash_detect(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;

	चयन (cc->capabilities & BCMA_CC_CAP_FLASHT) अणु
	हाल BCMA_CC_FLASHT_STSER:
	हाल BCMA_CC_FLASHT_ATSER:
		bcma_debug(bus, "Found serial flash\n");
		bcma_sflash_init(cc);
		अवरोध;
	हाल BCMA_CC_FLASHT_PARA:
		bcma_debug(bus, "Found parallel flash\n");
		bcma_pflash_init(cc);
		अवरोध;
	शेष:
		bcma_err(bus, "Flash type not supported\n");
	पूर्ण

	अगर (cc->core->id.rev == 38 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM4706) अणु
		अगर (cc->capabilities & BCMA_CC_CAP_NFLASH) अणु
			bcma_debug(bus, "Found NAND flash\n");
			bcma_nflash_init(cc);
		पूर्ण
	पूर्ण
पूर्ण

व्योम bcma_core_chipcommon_early_init(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;

	अगर (cc->early_setup_करोne)
		वापस;

	spin_lock_init(&cc->gpio_lock);

	अगर (cc->core->id.rev >= 11)
		cc->status = bcma_cc_पढ़ो32(cc, BCMA_CC_CHIPSTAT);
	cc->capabilities = bcma_cc_पढ़ो32(cc, BCMA_CC_CAP);
	अगर (cc->core->id.rev >= 35)
		cc->capabilities_ext = bcma_cc_पढ़ो32(cc, BCMA_CC_CAP_EXT);

	अगर (cc->capabilities & BCMA_CC_CAP_PMU)
		bcma_pmu_early_init(cc);

	अगर (bus->hosttype == BCMA_HOSTTYPE_SOC)
		bcma_core_chipcommon_flash_detect(cc);

	cc->early_setup_करोne = true;
पूर्ण

व्योम bcma_core_chipcommon_init(काष्ठा bcma_drv_cc *cc)
अणु
	u32 leddc_on = 10;
	u32 leddc_off = 90;

	अगर (cc->setup_करोne)
		वापस;

	bcma_core_chipcommon_early_init(cc);

	अगर (cc->core->id.rev >= 20) अणु
		u32 pullup = 0, pullकरोwn = 0;

		अगर (cc->core->bus->chipinfo.id == BCMA_CHIP_ID_BCM43142) अणु
			pullup = 0x402e0;
			pullकरोwn = 0x20500;
		पूर्ण

		bcma_cc_ग_लिखो32(cc, BCMA_CC_GPIOPULLUP, pullup);
		bcma_cc_ग_लिखो32(cc, BCMA_CC_GPIOPULLDOWN, pullकरोwn);
	पूर्ण

	अगर (cc->capabilities & BCMA_CC_CAP_PMU)
		bcma_pmu_init(cc);
	अगर (cc->capabilities & BCMA_CC_CAP_PCTL)
		bcma_err(cc->core->bus, "Power control not implemented!\n");

	अगर (cc->core->id.rev >= 16) अणु
		अगर (cc->core->bus->sprom.leddc_on_समय &&
		    cc->core->bus->sprom.leddc_off_समय) अणु
			leddc_on = cc->core->bus->sprom.leddc_on_समय;
			leddc_off = cc->core->bus->sprom.leddc_off_समय;
		पूर्ण
		bcma_cc_ग_लिखो32(cc, BCMA_CC_GPIOTIMER,
			((leddc_on << BCMA_CC_GPIOTIMER_ONTIME_SHIFT) |
			 (leddc_off << BCMA_CC_GPIOTIMER_OFFTIME_SHIFT)));
	पूर्ण
	cc->ticks_per_ms = bcma_chipco_watchकरोg_ticks_per_ms(cc);

	cc->setup_करोne = true;
पूर्ण

/* Set chip watchकरोg reset समयr to fire in 'ticks' backplane cycles */
u32 bcma_chipco_watchकरोg_समयr_set(काष्ठा bcma_drv_cc *cc, u32 ticks)
अणु
	u32 maxt;

	maxt = bcma_chipco_watchकरोg_get_max_समयr(cc);
	अगर (bcma_core_cc_has_pmu_watchकरोg(cc)) अणु
		अगर (ticks == 1)
			ticks = 2;
		अन्यथा अगर (ticks > maxt)
			ticks = maxt;
		bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_WATCHDOG, ticks);
	पूर्ण अन्यथा अणु
		काष्ठा bcma_bus *bus = cc->core->bus;

		अगर (bus->chipinfo.id != BCMA_CHIP_ID_BCM4707 &&
		    bus->chipinfo.id != BCMA_CHIP_ID_BCM47094 &&
		    bus->chipinfo.id != BCMA_CHIP_ID_BCM53018)
			bcma_core_set_घड़ीmode(cc->core,
						ticks ? BCMA_CLKMODE_FAST : BCMA_CLKMODE_DYNAMIC);

		अगर (ticks > maxt)
			ticks = maxt;
		/* instant NMI */
		bcma_cc_ग_लिखो32(cc, BCMA_CC_WATCHDOG, ticks);
	पूर्ण
	वापस ticks;
पूर्ण

व्योम bcma_chipco_irq_mask(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value)
अणु
	bcma_cc_ग_लिखो32_masked(cc, BCMA_CC_IRQMASK, mask, value);
पूर्ण

u32 bcma_chipco_irq_status(काष्ठा bcma_drv_cc *cc, u32 mask)
अणु
	वापस bcma_cc_पढ़ो32(cc, BCMA_CC_IRQSTAT) & mask;
पूर्ण

u32 bcma_chipco_gpio_in(काष्ठा bcma_drv_cc *cc, u32 mask)
अणु
	वापस bcma_cc_पढ़ो32(cc, BCMA_CC_GPIOIN) & mask;
पूर्ण

u32 bcma_chipco_gpio_out(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = bcma_cc_ग_लिखो32_masked(cc, BCMA_CC_GPIOOUT, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(bcma_chipco_gpio_out);

u32 bcma_chipco_gpio_outen(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = bcma_cc_ग_लिखो32_masked(cc, BCMA_CC_GPIOOUTEN, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(bcma_chipco_gpio_outen);

/*
 * If the bit is set to 0, chipcommon controlls this GPIO,
 * अगर the bit is set to 1, it is used by some part of the chip and not our code.
 */
u32 bcma_chipco_gpio_control(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = bcma_cc_ग_लिखो32_masked(cc, BCMA_CC_GPIOCTL, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(bcma_chipco_gpio_control);

u32 bcma_chipco_gpio_पूर्णांकmask(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = bcma_cc_ग_लिखो32_masked(cc, BCMA_CC_GPIOIRQ, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण

u32 bcma_chipco_gpio_polarity(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = bcma_cc_ग_लिखो32_masked(cc, BCMA_CC_GPIOPOL, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण

u32 bcma_chipco_gpio_pullup(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res;

	अगर (cc->core->id.rev < 20)
		वापस 0;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = bcma_cc_ग_लिखो32_masked(cc, BCMA_CC_GPIOPULLUP, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण

u32 bcma_chipco_gpio_pullकरोwn(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res;

	अगर (cc->core->id.rev < 20)
		वापस 0;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = bcma_cc_ग_लिखो32_masked(cc, BCMA_CC_GPIOPULLDOWN, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण

#अगर_घोषित CONFIG_BCMA_DRIVER_MIPS
व्योम bcma_chipco_serial_init(काष्ठा bcma_drv_cc *cc)
अणु
	अचिन्हित पूर्णांक irq;
	u32 baud_base;
	u32 i;
	अचिन्हित पूर्णांक ccrev = cc->core->id.rev;
	काष्ठा bcma_serial_port *ports = cc->serial_ports;

	अगर (ccrev >= 11 && ccrev != 15) अणु
		baud_base = bcma_chipco_get_alp_घड़ी(cc);
		अगर (ccrev >= 21) अणु
			/* Turn off UART घड़ी beक्रमe चयनing घड़ीsource. */
			bcma_cc_ग_लिखो32(cc, BCMA_CC_CORECTL,
				       bcma_cc_पढ़ो32(cc, BCMA_CC_CORECTL)
				       & ~BCMA_CC_CORECTL_UARTCLKEN);
		पूर्ण
		/* Set the override bit so we करोn't भागide it */
		bcma_cc_ग_लिखो32(cc, BCMA_CC_CORECTL,
			       bcma_cc_पढ़ो32(cc, BCMA_CC_CORECTL)
			       | BCMA_CC_CORECTL_UARTCLK0);
		अगर (ccrev >= 21) अणु
			/* Re-enable the UART घड़ी. */
			bcma_cc_ग_लिखो32(cc, BCMA_CC_CORECTL,
				       bcma_cc_पढ़ो32(cc, BCMA_CC_CORECTL)
				       | BCMA_CC_CORECTL_UARTCLKEN);
		पूर्ण
	पूर्ण अन्यथा अणु
		bcma_err(cc->core->bus, "serial not supported on this device ccrev: 0x%x\n",
			 ccrev);
		वापस;
	पूर्ण

	irq = bcma_core_irq(cc->core, 0);

	/* Determine the रेजिस्टरs of the UARTs */
	cc->nr_serial_ports = (cc->capabilities & BCMA_CC_CAP_NRUART);
	क्रम (i = 0; i < cc->nr_serial_ports; i++) अणु
		ports[i].regs = cc->core->io_addr + BCMA_CC_UART0_DATA +
				(i * 256);
		ports[i].irq = irq;
		ports[i].baud_base = baud_base;
		ports[i].reg_shअगरt = 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_BCMA_DRIVER_MIPS */
