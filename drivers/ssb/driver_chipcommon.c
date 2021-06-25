<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * Broadcom ChipCommon core driver
 *
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <m@bues.ch>
 * Copyright 2012, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/ssb/ssb_regs.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/bcm47xx_wdt.h>


/* Clock sources */
क्रमागत ssb_clksrc अणु
	/* PCI घड़ी */
	SSB_CHIPCO_CLKSRC_PCI,
	/* Crystal slow घड़ी oscillator */
	SSB_CHIPCO_CLKSRC_XTALOS,
	/* Low घातer oscillator */
	SSB_CHIPCO_CLKSRC_LOPWROS,
पूर्ण;


अटल अंतरभूत u32 chipco_ग_लिखो32_masked(काष्ठा ssb_chipcommon *cc, u16 offset,
					u32 mask, u32 value)
अणु
	value &= mask;
	value |= chipco_पढ़ो32(cc, offset) & ~mask;
	chipco_ग_लिखो32(cc, offset, value);

	वापस value;
पूर्ण

व्योम ssb_chipco_set_घड़ीmode(काष्ठा ssb_chipcommon *cc,
			      क्रमागत ssb_clkmode mode)
अणु
	काष्ठा ssb_device *ccdev = cc->dev;
	काष्ठा ssb_bus *bus;
	u32 पंचांगp;

	अगर (!ccdev)
		वापस;
	bus = ccdev->bus;

	/* We support SLOW only on 6..9 */
	अगर (ccdev->id.revision >= 10 && mode == SSB_CLKMODE_SLOW)
		mode = SSB_CLKMODE_DYNAMIC;

	अगर (cc->capabilities & SSB_CHIPCO_CAP_PMU)
		वापस; /* PMU controls घड़ीmode, separated function needed */
	WARN_ON(ccdev->id.revision >= 20);

	/* chipcommon cores prior to rev6 करोn't support dynamic घड़ी control */
	अगर (ccdev->id.revision < 6)
		वापस;

	/* ChipCommon cores rev10+ need testing */
	अगर (ccdev->id.revision >= 10)
		वापस;

	अगर (!(cc->capabilities & SSB_CHIPCO_CAP_PCTL))
		वापस;

	चयन (mode) अणु
	हाल SSB_CLKMODE_SLOW: /* For revs 6..9 only */
		पंचांगp = chipco_पढ़ो32(cc, SSB_CHIPCO_SLOWCLKCTL);
		पंचांगp |= SSB_CHIPCO_SLOWCLKCTL_FSLOW;
		chipco_ग_लिखो32(cc, SSB_CHIPCO_SLOWCLKCTL, पंचांगp);
		अवरोध;
	हाल SSB_CLKMODE_FAST:
		अगर (ccdev->id.revision < 10) अणु
			ssb_pci_xtal(bus, SSB_GPIO_XTAL, 1); /* Force crystal on */
			पंचांगp = chipco_पढ़ो32(cc, SSB_CHIPCO_SLOWCLKCTL);
			पंचांगp &= ~SSB_CHIPCO_SLOWCLKCTL_FSLOW;
			पंचांगp |= SSB_CHIPCO_SLOWCLKCTL_IPLL;
			chipco_ग_लिखो32(cc, SSB_CHIPCO_SLOWCLKCTL, पंचांगp);
		पूर्ण अन्यथा अणु
			chipco_ग_लिखो32(cc, SSB_CHIPCO_SYSCLKCTL,
				(chipco_पढ़ो32(cc, SSB_CHIPCO_SYSCLKCTL) |
				 SSB_CHIPCO_SYSCLKCTL_FORCEHT));
			/* udelay(150); TODO: not available in early init */
		पूर्ण
		अवरोध;
	हाल SSB_CLKMODE_DYNAMIC:
		अगर (ccdev->id.revision < 10) अणु
			पंचांगp = chipco_पढ़ो32(cc, SSB_CHIPCO_SLOWCLKCTL);
			पंचांगp &= ~SSB_CHIPCO_SLOWCLKCTL_FSLOW;
			पंचांगp &= ~SSB_CHIPCO_SLOWCLKCTL_IPLL;
			पंचांगp &= ~SSB_CHIPCO_SLOWCLKCTL_ENXTAL;
			अगर ((पंचांगp & SSB_CHIPCO_SLOWCLKCTL_SRC) !=
			    SSB_CHIPCO_SLOWCLKCTL_SRC_XTAL)
				पंचांगp |= SSB_CHIPCO_SLOWCLKCTL_ENXTAL;
			chipco_ग_लिखो32(cc, SSB_CHIPCO_SLOWCLKCTL, पंचांगp);

			/* For dynamic control, we have to release our xtal_pu
			 * "force on" */
			अगर (पंचांगp & SSB_CHIPCO_SLOWCLKCTL_ENXTAL)
				ssb_pci_xtal(bus, SSB_GPIO_XTAL, 0);
		पूर्ण अन्यथा अणु
			chipco_ग_लिखो32(cc, SSB_CHIPCO_SYSCLKCTL,
				(chipco_पढ़ो32(cc, SSB_CHIPCO_SYSCLKCTL) &
				 ~SSB_CHIPCO_SYSCLKCTL_FORCEHT));
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

/* Get the Slow Clock Source */
अटल क्रमागत ssb_clksrc chipco_pctl_get_slowclksrc(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;
	u32 पंचांगp;

	अगर (cc->dev->id.revision < 6) अणु
		अगर (bus->bustype == SSB_BUSTYPE_SSB ||
		    bus->bustype == SSB_BUSTYPE_PCMCIA)
			वापस SSB_CHIPCO_CLKSRC_XTALOS;
		अगर (bus->bustype == SSB_BUSTYPE_PCI) अणु
			pci_पढ़ो_config_dword(bus->host_pci, SSB_GPIO_OUT, &पंचांगp);
			अगर (पंचांगp & 0x10)
				वापस SSB_CHIPCO_CLKSRC_PCI;
			वापस SSB_CHIPCO_CLKSRC_XTALOS;
		पूर्ण
	पूर्ण
	अगर (cc->dev->id.revision < 10) अणु
		पंचांगp = chipco_पढ़ो32(cc, SSB_CHIPCO_SLOWCLKCTL);
		पंचांगp &= 0x7;
		अगर (पंचांगp == 0)
			वापस SSB_CHIPCO_CLKSRC_LOPWROS;
		अगर (पंचांगp == 1)
			वापस SSB_CHIPCO_CLKSRC_XTALOS;
		अगर (पंचांगp == 2)
			वापस SSB_CHIPCO_CLKSRC_PCI;
	पूर्ण

	वापस SSB_CHIPCO_CLKSRC_XTALOS;
पूर्ण

/* Get maximum or minimum (depending on get_max flag) slowघड़ी frequency. */
अटल पूर्णांक chipco_pctl_घड़ीfreqlimit(काष्ठा ssb_chipcommon *cc, पूर्णांक get_max)
अणु
	पूर्णांक limit;
	क्रमागत ssb_clksrc घड़ीsrc;
	पूर्णांक भागisor = 1;
	u32 पंचांगp;

	घड़ीsrc = chipco_pctl_get_slowclksrc(cc);
	अगर (cc->dev->id.revision < 6) अणु
		चयन (घड़ीsrc) अणु
		हाल SSB_CHIPCO_CLKSRC_PCI:
			भागisor = 64;
			अवरोध;
		हाल SSB_CHIPCO_CLKSRC_XTALOS:
			भागisor = 32;
			अवरोध;
		शेष:
			WARN_ON(1);
		पूर्ण
	पूर्ण अन्यथा अगर (cc->dev->id.revision < 10) अणु
		चयन (घड़ीsrc) अणु
		हाल SSB_CHIPCO_CLKSRC_LOPWROS:
			अवरोध;
		हाल SSB_CHIPCO_CLKSRC_XTALOS:
		हाल SSB_CHIPCO_CLKSRC_PCI:
			पंचांगp = chipco_पढ़ो32(cc, SSB_CHIPCO_SLOWCLKCTL);
			भागisor = (पंचांगp >> 16) + 1;
			भागisor *= 4;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp = chipco_पढ़ो32(cc, SSB_CHIPCO_SYSCLKCTL);
		भागisor = (पंचांगp >> 16) + 1;
		भागisor *= 4;
	पूर्ण

	चयन (घड़ीsrc) अणु
	हाल SSB_CHIPCO_CLKSRC_LOPWROS:
		अगर (get_max)
			limit = 43000;
		अन्यथा
			limit = 25000;
		अवरोध;
	हाल SSB_CHIPCO_CLKSRC_XTALOS:
		अगर (get_max)
			limit = 20200000;
		अन्यथा
			limit = 19800000;
		अवरोध;
	हाल SSB_CHIPCO_CLKSRC_PCI:
		अगर (get_max)
			limit = 34000000;
		अन्यथा
			limit = 25000000;
		अवरोध;
	पूर्ण
	limit /= भागisor;

	वापस limit;
पूर्ण

अटल व्योम chipco_घातercontrol_init(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;

	अगर (bus->chip_id == 0x4321) अणु
		अगर (bus->chip_rev == 0)
			chipco_ग_लिखो32(cc, SSB_CHIPCO_CHIPCTL, 0x3A4);
		अन्यथा अगर (bus->chip_rev == 1)
			chipco_ग_लिखो32(cc, SSB_CHIPCO_CHIPCTL, 0xA4);
	पूर्ण

	अगर (!(cc->capabilities & SSB_CHIPCO_CAP_PCTL))
		वापस;

	अगर (cc->dev->id.revision >= 10) अणु
		/* Set Idle Power घड़ी rate to 1Mhz */
		chipco_ग_लिखो32(cc, SSB_CHIPCO_SYSCLKCTL,
			       (chipco_पढ़ो32(cc, SSB_CHIPCO_SYSCLKCTL) &
				0x0000FFFF) | 0x00040000);
	पूर्ण अन्यथा अणु
		पूर्णांक maxfreq;

		maxfreq = chipco_pctl_घड़ीfreqlimit(cc, 1);
		chipco_ग_लिखो32(cc, SSB_CHIPCO_PLLONDELAY,
			       (maxfreq * 150 + 999999) / 1000000);
		chipco_ग_लिखो32(cc, SSB_CHIPCO_FREFSELDELAY,
			       (maxfreq * 15 + 999999) / 1000000);
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PmuFastPwrupDelay */
अटल u16 pmu_fast_घातerup_delay(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;

	चयन (bus->chip_id) अणु
	हाल 0x4312:
	हाल 0x4322:
	हाल 0x4328:
		वापस 7000;
	हाल 0x4325:
		/* TODO: */
	शेष:
		वापस 15000;
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/ClkctlFastPwrupDelay */
अटल व्योम calc_fast_घातerup_delay(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;
	पूर्णांक minfreq;
	अचिन्हित पूर्णांक पंचांगp;
	u32 pll_on_delay;

	अगर (bus->bustype != SSB_BUSTYPE_PCI)
		वापस;

	अगर (cc->capabilities & SSB_CHIPCO_CAP_PMU) अणु
		cc->fast_pwrup_delay = pmu_fast_घातerup_delay(cc);
		वापस;
	पूर्ण

	अगर (!(cc->capabilities & SSB_CHIPCO_CAP_PCTL))
		वापस;

	minfreq = chipco_pctl_घड़ीfreqlimit(cc, 0);
	pll_on_delay = chipco_पढ़ो32(cc, SSB_CHIPCO_PLLONDELAY);
	पंचांगp = (((pll_on_delay + 2) * 1000000) + (minfreq - 1)) / minfreq;
	WARN_ON(पंचांगp & ~0xFFFF);

	cc->fast_pwrup_delay = पंचांगp;
पूर्ण

अटल u32 ssb_chipco_alp_घड़ी(काष्ठा ssb_chipcommon *cc)
अणु
	अगर (cc->capabilities & SSB_CHIPCO_CAP_PMU)
		वापस ssb_pmu_get_alp_घड़ी(cc);

	वापस 20000000;
पूर्ण

अटल u32 ssb_chipco_watchकरोg_get_max_समयr(काष्ठा ssb_chipcommon *cc)
अणु
	u32 nb;

	अगर (cc->capabilities & SSB_CHIPCO_CAP_PMU) अणु
		अगर (cc->dev->id.revision < 26)
			nb = 16;
		अन्यथा
			nb = (cc->dev->id.revision >= 37) ? 32 : 24;
	पूर्ण अन्यथा अणु
		nb = 28;
	पूर्ण
	अगर (nb == 32)
		वापस 0xffffffff;
	अन्यथा
		वापस (1 << nb) - 1;
पूर्ण

u32 ssb_chipco_watchकरोg_समयr_set_wdt(काष्ठा bcm47xx_wdt *wdt, u32 ticks)
अणु
	काष्ठा ssb_chipcommon *cc = bcm47xx_wdt_get_drvdata(wdt);

	अगर (cc->dev->bus->bustype != SSB_BUSTYPE_SSB)
		वापस 0;

	वापस ssb_chipco_watchकरोg_समयr_set(cc, ticks);
पूर्ण

u32 ssb_chipco_watchकरोg_समयr_set_ms(काष्ठा bcm47xx_wdt *wdt, u32 ms)
अणु
	काष्ठा ssb_chipcommon *cc = bcm47xx_wdt_get_drvdata(wdt);
	u32 ticks;

	अगर (cc->dev->bus->bustype != SSB_BUSTYPE_SSB)
		वापस 0;

	ticks = ssb_chipco_watchकरोg_समयr_set(cc, cc->ticks_per_ms * ms);
	वापस ticks / cc->ticks_per_ms;
पूर्ण

अटल पूर्णांक ssb_chipco_watchकरोg_ticks_per_ms(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;

	अगर (cc->capabilities & SSB_CHIPCO_CAP_PMU) अणु
			/* based on 32KHz ILP घड़ी */
			वापस 32;
	पूर्ण अन्यथा अणु
		अगर (cc->dev->id.revision < 18)
			वापस ssb_घड़ीspeed(bus) / 1000;
		अन्यथा
			वापस ssb_chipco_alp_घड़ी(cc) / 1000;
	पूर्ण
पूर्ण

व्योम ssb_chipcommon_init(काष्ठा ssb_chipcommon *cc)
अणु
	अगर (!cc->dev)
		वापस; /* We करोn't have a ChipCommon */

	spin_lock_init(&cc->gpio_lock);

	अगर (cc->dev->id.revision >= 11)
		cc->status = chipco_पढ़ो32(cc, SSB_CHIPCO_CHIPSTAT);
	dev_dbg(cc->dev->dev, "chipcommon status is 0x%x\n", cc->status);

	अगर (cc->dev->id.revision >= 20) अणु
		chipco_ग_लिखो32(cc, SSB_CHIPCO_GPIOPULLUP, 0);
		chipco_ग_लिखो32(cc, SSB_CHIPCO_GPIOPULLDOWN, 0);
	पूर्ण

	ssb_pmu_init(cc);
	chipco_घातercontrol_init(cc);
	ssb_chipco_set_घड़ीmode(cc, SSB_CLKMODE_FAST);
	calc_fast_घातerup_delay(cc);

	अगर (cc->dev->bus->bustype == SSB_BUSTYPE_SSB) अणु
		cc->ticks_per_ms = ssb_chipco_watchकरोg_ticks_per_ms(cc);
		cc->max_समयr_ms = ssb_chipco_watchकरोg_get_max_समयr(cc) / cc->ticks_per_ms;
	पूर्ण
पूर्ण

व्योम ssb_chipco_suspend(काष्ठा ssb_chipcommon *cc)
अणु
	अगर (!cc->dev)
		वापस;
	ssb_chipco_set_घड़ीmode(cc, SSB_CLKMODE_SLOW);
पूर्ण

व्योम ssb_chipco_resume(काष्ठा ssb_chipcommon *cc)
अणु
	अगर (!cc->dev)
		वापस;
	chipco_घातercontrol_init(cc);
	ssb_chipco_set_घड़ीmode(cc, SSB_CLKMODE_FAST);
पूर्ण

/* Get the processor घड़ी */
व्योम ssb_chipco_get_घड़ीcpu(काष्ठा ssb_chipcommon *cc,
                             u32 *plltype, u32 *n, u32 *m)
अणु
	*n = chipco_पढ़ो32(cc, SSB_CHIPCO_CLOCK_N);
	*plltype = (cc->capabilities & SSB_CHIPCO_CAP_PLLT);
	चयन (*plltype) अणु
	हाल SSB_PLLTYPE_2:
	हाल SSB_PLLTYPE_4:
	हाल SSB_PLLTYPE_6:
	हाल SSB_PLLTYPE_7:
		*m = chipco_पढ़ो32(cc, SSB_CHIPCO_CLOCK_MIPS);
		अवरोध;
	हाल SSB_PLLTYPE_3:
		/* 5350 uses m2 to control mips */
		*m = chipco_पढ़ो32(cc, SSB_CHIPCO_CLOCK_M2);
		अवरोध;
	शेष:
		*m = chipco_पढ़ो32(cc, SSB_CHIPCO_CLOCK_SB);
		अवरोध;
	पूर्ण
पूर्ण

/* Get the bus घड़ी */
व्योम ssb_chipco_get_घड़ीcontrol(काष्ठा ssb_chipcommon *cc,
				 u32 *plltype, u32 *n, u32 *m)
अणु
	*n = chipco_पढ़ो32(cc, SSB_CHIPCO_CLOCK_N);
	*plltype = (cc->capabilities & SSB_CHIPCO_CAP_PLLT);
	चयन (*plltype) अणु
	हाल SSB_PLLTYPE_6: /* 100/200 or 120/240 only */
		*m = chipco_पढ़ो32(cc, SSB_CHIPCO_CLOCK_MIPS);
		अवरोध;
	हाल SSB_PLLTYPE_3: /* 25Mhz, 2 भागiders */
		अगर (cc->dev->bus->chip_id != 0x5365) अणु
			*m = chipco_पढ़ो32(cc, SSB_CHIPCO_CLOCK_M2);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		*m = chipco_पढ़ो32(cc, SSB_CHIPCO_CLOCK_SB);
	पूर्ण
पूर्ण

व्योम ssb_chipco_timing_init(काष्ठा ssb_chipcommon *cc,
			    अचिन्हित दीर्घ ns)
अणु
	काष्ठा ssb_device *dev = cc->dev;
	काष्ठा ssb_bus *bus = dev->bus;
	u32 पंचांगp;

	/* set रेजिस्टर क्रम बाह्यal IO to control LED. */
	chipco_ग_लिखो32(cc, SSB_CHIPCO_PROG_CFG, 0x11);
	पंचांगp = DIV_ROUND_UP(10, ns) << SSB_PROG_WCNT_3_SHIFT;		/* Waitcount-3 = 10ns */
	पंचांगp |= DIV_ROUND_UP(40, ns) << SSB_PROG_WCNT_1_SHIFT;	/* Waitcount-1 = 40ns */
	पंचांगp |= DIV_ROUND_UP(240, ns);				/* Waitcount-0 = 240ns */
	chipco_ग_लिखो32(cc, SSB_CHIPCO_PROG_WAITCNT, पंचांगp);	/* 0x01020a0c क्रम a 100Mhz घड़ी */

	/* Set timing क्रम the flash */
	पंचांगp = DIV_ROUND_UP(10, ns) << SSB_FLASH_WCNT_3_SHIFT;	/* Waitcount-3 = 10nS */
	पंचांगp |= DIV_ROUND_UP(10, ns) << SSB_FLASH_WCNT_1_SHIFT;	/* Waitcount-1 = 10nS */
	पंचांगp |= DIV_ROUND_UP(120, ns);				/* Waitcount-0 = 120nS */
	अगर ((bus->chip_id == 0x5365) ||
	    (dev->id.revision < 9))
		chipco_ग_लिखो32(cc, SSB_CHIPCO_FLASH_WAITCNT, पंचांगp);
	अगर ((bus->chip_id == 0x5365) ||
	    (dev->id.revision < 9) ||
	    ((bus->chip_id == 0x5350) && (bus->chip_rev == 0)))
		chipco_ग_लिखो32(cc, SSB_CHIPCO_PCMCIA_MEMWAIT, पंचांगp);

	अगर (bus->chip_id == 0x5350) अणु
		/* Enable EXTIF */
		पंचांगp = DIV_ROUND_UP(10, ns) << SSB_PROG_WCNT_3_SHIFT;	  /* Waitcount-3 = 10ns */
		पंचांगp |= DIV_ROUND_UP(20, ns) << SSB_PROG_WCNT_2_SHIFT;  /* Waitcount-2 = 20ns */
		पंचांगp |= DIV_ROUND_UP(100, ns) << SSB_PROG_WCNT_1_SHIFT; /* Waitcount-1 = 100ns */
		पंचांगp |= DIV_ROUND_UP(120, ns);			  /* Waitcount-0 = 120ns */
		chipco_ग_लिखो32(cc, SSB_CHIPCO_PROG_WAITCNT, पंचांगp); /* 0x01020a0c क्रम a 100Mhz घड़ी */
	पूर्ण
पूर्ण

/* Set chip watchकरोg reset समयr to fire in 'ticks' backplane cycles */
u32 ssb_chipco_watchकरोg_समयr_set(काष्ठा ssb_chipcommon *cc, u32 ticks)
अणु
	u32 maxt;
	क्रमागत ssb_clkmode clkmode;

	maxt = ssb_chipco_watchकरोg_get_max_समयr(cc);
	अगर (cc->capabilities & SSB_CHIPCO_CAP_PMU) अणु
		अगर (ticks == 1)
			ticks = 2;
		अन्यथा अगर (ticks > maxt)
			ticks = maxt;
		chipco_ग_लिखो32(cc, SSB_CHIPCO_PMU_WATCHDOG, ticks);
	पूर्ण अन्यथा अणु
		clkmode = ticks ? SSB_CLKMODE_FAST : SSB_CLKMODE_DYNAMIC;
		ssb_chipco_set_घड़ीmode(cc, clkmode);
		अगर (ticks > maxt)
			ticks = maxt;
		/* instant NMI */
		chipco_ग_लिखो32(cc, SSB_CHIPCO_WATCHDOG, ticks);
	पूर्ण
	वापस ticks;
पूर्ण

व्योम ssb_chipco_irq_mask(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value)
अणु
	chipco_ग_लिखो32_masked(cc, SSB_CHIPCO_IRQMASK, mask, value);
पूर्ण

u32 ssb_chipco_irq_status(काष्ठा ssb_chipcommon *cc, u32 mask)
अणु
	वापस chipco_पढ़ो32(cc, SSB_CHIPCO_IRQSTAT) & mask;
पूर्ण

u32 ssb_chipco_gpio_in(काष्ठा ssb_chipcommon *cc, u32 mask)
अणु
	वापस chipco_पढ़ो32(cc, SSB_CHIPCO_GPIOIN) & mask;
पूर्ण

u32 ssb_chipco_gpio_out(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = chipco_ग_लिखो32_masked(cc, SSB_CHIPCO_GPIOOUT, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण

u32 ssb_chipco_gpio_outen(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = chipco_ग_लिखो32_masked(cc, SSB_CHIPCO_GPIOOUTEN, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण

u32 ssb_chipco_gpio_control(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = chipco_ग_लिखो32_masked(cc, SSB_CHIPCO_GPIOCTL, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL(ssb_chipco_gpio_control);

u32 ssb_chipco_gpio_पूर्णांकmask(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = chipco_ग_लिखो32_masked(cc, SSB_CHIPCO_GPIOIRQ, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण

u32 ssb_chipco_gpio_polarity(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = chipco_ग_लिखो32_masked(cc, SSB_CHIPCO_GPIOPOL, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण

u32 ssb_chipco_gpio_pullup(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	अगर (cc->dev->id.revision < 20)
		वापस 0xffffffff;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = chipco_ग_लिखो32_masked(cc, SSB_CHIPCO_GPIOPULLUP, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण

u32 ssb_chipco_gpio_pullकरोwn(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	अगर (cc->dev->id.revision < 20)
		वापस 0xffffffff;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = chipco_ग_लिखो32_masked(cc, SSB_CHIPCO_GPIOPULLDOWN, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	वापस res;
पूर्ण

#अगर_घोषित CONFIG_SSB_SERIAL
पूर्णांक ssb_chipco_serial_init(काष्ठा ssb_chipcommon *cc,
			   काष्ठा ssb_serial_port *ports)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;
	पूर्णांक nr_ports = 0;
	u32 plltype;
	अचिन्हित पूर्णांक irq;
	u32 baud_base, भाग;
	u32 i, n;
	अचिन्हित पूर्णांक ccrev = cc->dev->id.revision;

	plltype = (cc->capabilities & SSB_CHIPCO_CAP_PLLT);
	irq = ssb_mips_irq(cc->dev);

	अगर (plltype == SSB_PLLTYPE_1) अणु
		/* PLL घड़ी */
		baud_base = ssb_calc_घड़ी_rate(plltype,
						chipco_पढ़ो32(cc, SSB_CHIPCO_CLOCK_N),
						chipco_पढ़ो32(cc, SSB_CHIPCO_CLOCK_M2));
		भाग = 1;
	पूर्ण अन्यथा अणु
		अगर (ccrev == 20) अणु
			/* BCM5354 uses स्थिरant 25MHz घड़ी */
			baud_base = 25000000;
			भाग = 48;
			/* Set the override bit so we करोn't भागide it */
			chipco_ग_लिखो32(cc, SSB_CHIPCO_CORECTL,
				       chipco_पढ़ो32(cc, SSB_CHIPCO_CORECTL)
				       | SSB_CHIPCO_CORECTL_UARTCLK0);
		पूर्ण अन्यथा अगर ((ccrev >= 11) && (ccrev != 15)) अणु
			baud_base = ssb_chipco_alp_घड़ी(cc);
			भाग = 1;
			अगर (ccrev >= 21) अणु
				/* Turn off UART घड़ी beक्रमe चयनing घड़ीsource. */
				chipco_ग_लिखो32(cc, SSB_CHIPCO_CORECTL,
					       chipco_पढ़ो32(cc, SSB_CHIPCO_CORECTL)
					       & ~SSB_CHIPCO_CORECTL_UARTCLKEN);
			पूर्ण
			/* Set the override bit so we करोn't भागide it */
			chipco_ग_लिखो32(cc, SSB_CHIPCO_CORECTL,
				       chipco_पढ़ो32(cc, SSB_CHIPCO_CORECTL)
				       | SSB_CHIPCO_CORECTL_UARTCLK0);
			अगर (ccrev >= 21) अणु
				/* Re-enable the UART घड़ी. */
				chipco_ग_लिखो32(cc, SSB_CHIPCO_CORECTL,
					       chipco_पढ़ो32(cc, SSB_CHIPCO_CORECTL)
					       | SSB_CHIPCO_CORECTL_UARTCLKEN);
			पूर्ण
		पूर्ण अन्यथा अगर (ccrev >= 3) अणु
			/* Internal backplane घड़ी */
			baud_base = ssb_घड़ीspeed(bus);
			भाग = chipco_पढ़ो32(cc, SSB_CHIPCO_CLKDIV)
			      & SSB_CHIPCO_CLKDIV_UART;
		पूर्ण अन्यथा अणु
			/* Fixed पूर्णांकernal backplane घड़ी */
			baud_base = 88000000;
			भाग = 48;
		पूर्ण

		/* Clock source depends on strapping अगर UartClkOverride is unset */
		अगर ((ccrev > 0) &&
		    !(chipco_पढ़ो32(cc, SSB_CHIPCO_CORECTL) & SSB_CHIPCO_CORECTL_UARTCLK0)) अणु
			अगर ((cc->capabilities & SSB_CHIPCO_CAP_UARTCLK) ==
			    SSB_CHIPCO_CAP_UARTCLK_INT) अणु
				/* Internal भागided backplane घड़ी */
				baud_base /= भाग;
			पूर्ण अन्यथा अणु
				/* Assume बाह्यal घड़ी of 1.8432 MHz */
				baud_base = 1843200;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Determine the रेजिस्टरs of the UARTs */
	n = (cc->capabilities & SSB_CHIPCO_CAP_NRUART);
	क्रम (i = 0; i < n; i++) अणु
		व्योम __iomem *cc_mmio;
		व्योम __iomem *uart_regs;

		cc_mmio = cc->dev->bus->mmio + (cc->dev->core_index * SSB_CORE_SIZE);
		uart_regs = cc_mmio + SSB_CHIPCO_UART0_DATA;
		/* Offset changed at after rev 0 */
		अगर (ccrev == 0)
			uart_regs += (i * 8);
		अन्यथा
			uart_regs += (i * 256);

		nr_ports++;
		ports[i].regs = uart_regs;
		ports[i].irq = irq;
		ports[i].baud_base = baud_base;
		ports[i].reg_shअगरt = 0;
	पूर्ण

	वापस nr_ports;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_SERIAL */
