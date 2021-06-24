<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * ChipCommon Power Management Unit driver
 *
 * Copyright 2009, Michael Buesch <m@bues.ch>
 * Copyright 2007, 2011, Broadcom Corporation
 * Copyright 2011, 2012, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"
#समावेश <linux/export.h>
#समावेश <linux/bcma/bcma.h>

u32 bcma_chipco_pll_पढ़ो(काष्ठा bcma_drv_cc *cc, u32 offset)
अणु
	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_PLLCTL_ADDR, offset);
	bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_PLLCTL_ADDR);
	वापस bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_PLLCTL_DATA);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_chipco_pll_पढ़ो);

व्योम bcma_chipco_pll_ग_लिखो(काष्ठा bcma_drv_cc *cc, u32 offset, u32 value)
अणु
	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_PLLCTL_ADDR, offset);
	bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_PLLCTL_ADDR);
	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_PLLCTL_DATA, value);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_chipco_pll_ग_लिखो);

व्योम bcma_chipco_pll_maskset(काष्ठा bcma_drv_cc *cc, u32 offset, u32 mask,
			     u32 set)
अणु
	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_PLLCTL_ADDR, offset);
	bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_PLLCTL_ADDR);
	bcma_pmu_maskset32(cc, BCMA_CC_PMU_PLLCTL_DATA, mask, set);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_chipco_pll_maskset);

व्योम bcma_chipco_chipctl_maskset(काष्ठा bcma_drv_cc *cc,
				 u32 offset, u32 mask, u32 set)
अणु
	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_CHIPCTL_ADDR, offset);
	bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_CHIPCTL_ADDR);
	bcma_pmu_maskset32(cc, BCMA_CC_PMU_CHIPCTL_DATA, mask, set);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_chipco_chipctl_maskset);

व्योम bcma_chipco_regctl_maskset(काष्ठा bcma_drv_cc *cc, u32 offset, u32 mask,
				u32 set)
अणु
	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_REGCTL_ADDR, offset);
	bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_REGCTL_ADDR);
	bcma_pmu_maskset32(cc, BCMA_CC_PMU_REGCTL_DATA, mask, set);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_chipco_regctl_maskset);

अटल u32 bcma_pmu_xtalfreq(काष्ठा bcma_drv_cc *cc)
अणु
	u32 ilp_ctl, alp_hz;

	अगर (!(bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_STAT) &
	      BCMA_CC_PMU_STAT_EXT_LPO_AVAIL))
		वापस 0;

	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_XTAL_FREQ,
			 BIT(BCMA_CC_PMU_XTAL_FREQ_MEASURE_SHIFT));
	usleep_range(1000, 2000);

	ilp_ctl = bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_XTAL_FREQ);
	ilp_ctl &= BCMA_CC_PMU_XTAL_FREQ_ILPCTL_MASK;

	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_XTAL_FREQ, 0);

	alp_hz = ilp_ctl * 32768 / 4;
	वापस (alp_hz + 50000) / 100000 * 100;
पूर्ण

अटल व्योम bcma_pmu2_pll_init0(काष्ठा bcma_drv_cc *cc, u32 xtalfreq)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;
	u32 freq_tgt_target = 0, freq_tgt_current;
	u32 pll0, mask;

	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM43142:
		/* pmu2_xtaltab0_adfll_485 */
		चयन (xtalfreq) अणु
		हाल 12000:
			freq_tgt_target = 0x50D52;
			अवरोध;
		हाल 20000:
			freq_tgt_target = 0x307FE;
			अवरोध;
		हाल 26000:
			freq_tgt_target = 0x254EA;
			अवरोध;
		हाल 37400:
			freq_tgt_target = 0x19EF8;
			अवरोध;
		हाल 52000:
			freq_tgt_target = 0x12A75;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!freq_tgt_target) अणु
		bcma_err(bus, "Unknown TGT frequency for xtalfreq %d\n",
			 xtalfreq);
		वापस;
	पूर्ण

	pll0 = bcma_chipco_pll_पढ़ो(cc, BCMA_CC_PMU15_PLL_PLLCTL0);
	freq_tgt_current = (pll0 & BCMA_CC_PMU15_PLL_PC0_FREQTGT_MASK) >>
		BCMA_CC_PMU15_PLL_PC0_FREQTGT_SHIFT;

	अगर (freq_tgt_current == freq_tgt_target) अणु
		bcma_debug(bus, "Target TGT frequency already set\n");
		वापस;
	पूर्ण

	/* Turn off PLL */
	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM43142:
		mask = (u32)~(BCMA_RES_4314_HT_AVAIL |
			      BCMA_RES_4314_MACPHY_CLK_AVAIL);

		bcma_pmu_mask32(cc, BCMA_CC_PMU_MINRES_MSK, mask);
		bcma_pmu_mask32(cc, BCMA_CC_PMU_MAXRES_MSK, mask);
		bcma_रुको_value(cc->core, BCMA_CLKCTLST,
				BCMA_CLKCTLST_HAVEHT, 0, 20000);
		अवरोध;
	पूर्ण

	pll0 &= ~BCMA_CC_PMU15_PLL_PC0_FREQTGT_MASK;
	pll0 |= freq_tgt_target << BCMA_CC_PMU15_PLL_PC0_FREQTGT_SHIFT;
	bcma_chipco_pll_ग_लिखो(cc, BCMA_CC_PMU15_PLL_PLLCTL0, pll0);

	/* Flush */
	अगर (cc->pmu.rev >= 2)
		bcma_pmu_set32(cc, BCMA_CC_PMU_CTL, BCMA_CC_PMU_CTL_PLL_UPD);

	/* TODO: Do we need to update OTP? */
पूर्ण

अटल व्योम bcma_pmu_pll_init(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;
	u32 xtalfreq = bcma_pmu_xtalfreq(cc);

	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM43142:
		अगर (xtalfreq == 0)
			xtalfreq = 20000;
		bcma_pmu2_pll_init0(cc, xtalfreq);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bcma_pmu_resources_init(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;
	u32 min_msk = 0, max_msk = 0;

	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM4313:
		min_msk = 0x200D;
		max_msk = 0xFFFF;
		अवरोध;
	हाल BCMA_CHIP_ID_BCM43142:
		min_msk = BCMA_RES_4314_LPLDO_PU |
			  BCMA_RES_4314_PMU_SLEEP_DIS |
			  BCMA_RES_4314_PMU_BG_PU |
			  BCMA_RES_4314_CBUCK_LPOM_PU |
			  BCMA_RES_4314_CBUCK_PFM_PU |
			  BCMA_RES_4314_CLDO_PU |
			  BCMA_RES_4314_LPLDO2_LVM |
			  BCMA_RES_4314_WL_PMU_PU |
			  BCMA_RES_4314_LDO3P3_PU |
			  BCMA_RES_4314_OTP_PU |
			  BCMA_RES_4314_WL_PWRSW_PU |
			  BCMA_RES_4314_LQ_AVAIL |
			  BCMA_RES_4314_LOGIC_RET |
			  BCMA_RES_4314_MEM_SLEEP |
			  BCMA_RES_4314_MACPHY_RET |
			  BCMA_RES_4314_WL_CORE_READY;
		max_msk = 0x3FFFFFFF;
		अवरोध;
	शेष:
		bcma_debug(bus, "PMU resource config unknown or not needed for device 0x%04X\n",
			   bus->chipinfo.id);
	पूर्ण

	/* Set the resource masks. */
	अगर (min_msk)
		bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_MINRES_MSK, min_msk);
	अगर (max_msk)
		bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_MAXRES_MSK, max_msk);

	/*
	 * Add some delay; allow resources to come up and settle.
	 * Delay is required क्रम SoC (early init).
	 */
	usleep_range(2000, 2500);
पूर्ण

/* Disable to allow पढ़ोing SPROM. Don't know the adventages of enabling it. */
व्योम bcma_chipco_bcm4331_ext_pa_lines_ctl(काष्ठा bcma_drv_cc *cc, bool enable)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;
	u32 val;

	val = bcma_cc_पढ़ो32(cc, BCMA_CC_CHIPCTL);
	अगर (enable) अणु
		val |= BCMA_CHIPCTL_4331_EXTPA_EN;
		अगर (bus->chipinfo.pkg == 9 || bus->chipinfo.pkg == 11)
			val |= BCMA_CHIPCTL_4331_EXTPA_ON_GPIO2_5;
		अन्यथा अगर (bus->chipinfo.rev > 0)
			val |= BCMA_CHIPCTL_4331_EXTPA_EN2;
	पूर्ण अन्यथा अणु
		val &= ~BCMA_CHIPCTL_4331_EXTPA_EN;
		val &= ~BCMA_CHIPCTL_4331_EXTPA_EN2;
		val &= ~BCMA_CHIPCTL_4331_EXTPA_ON_GPIO2_5;
	पूर्ण
	bcma_cc_ग_लिखो32(cc, BCMA_CC_CHIPCTL, val);
पूर्ण

अटल व्योम bcma_pmu_workarounds(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;

	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM4313:
		/*
		 * enable 12 mA drive strenth क्रम 4313 and set chipControl
		 * रेजिस्टर bit 1
		 */
		bcma_chipco_chipctl_maskset(cc, 0,
					    ~BCMA_CCTRL_4313_12MA_LED_DRIVE,
					    BCMA_CCTRL_4313_12MA_LED_DRIVE);
		अवरोध;
	हाल BCMA_CHIP_ID_BCM4331:
	हाल BCMA_CHIP_ID_BCM43431:
		/* Ext PA lines must be enabled क्रम tx on BCM4331 */
		bcma_chipco_bcm4331_ext_pa_lines_ctl(cc, true);
		अवरोध;
	हाल BCMA_CHIP_ID_BCM43224:
	हाल BCMA_CHIP_ID_BCM43421:
		/*
		 * enable 12 mA drive strenth क्रम 43224 and set chipControl
		 * रेजिस्टर bit 15
		 */
		अगर (bus->chipinfo.rev == 0) अणु
			bcma_cc_maskset32(cc, BCMA_CC_CHIPCTL,
					  ~BCMA_CCTRL_43224_GPIO_TOGGLE,
					  BCMA_CCTRL_43224_GPIO_TOGGLE);
			bcma_chipco_chipctl_maskset(cc, 0,
						    ~BCMA_CCTRL_43224A0_12MA_LED_DRIVE,
						    BCMA_CCTRL_43224A0_12MA_LED_DRIVE);
		पूर्ण अन्यथा अणु
			bcma_chipco_chipctl_maskset(cc, 0,
						    ~BCMA_CCTRL_43224B0_12MA_LED_DRIVE,
						    BCMA_CCTRL_43224B0_12MA_LED_DRIVE);
		पूर्ण
		अवरोध;
	शेष:
		bcma_debug(bus, "Workarounds unknown or not needed for device 0x%04X\n",
			   bus->chipinfo.id);
	पूर्ण
पूर्ण

व्योम bcma_pmu_early_init(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;
	u32 pmucap;

	अगर (cc->core->id.rev >= 35 &&
	    cc->capabilities_ext & BCMA_CC_CAP_EXT_AOB_PRESENT) अणु
		cc->pmu.core = bcma_find_core(bus, BCMA_CORE_PMU);
		अगर (!cc->pmu.core)
			bcma_warn(bus, "Couldn't find expected PMU core");
	पूर्ण
	अगर (!cc->pmu.core)
		cc->pmu.core = cc->core;

	pmucap = bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_CAP);
	cc->pmu.rev = (pmucap & BCMA_CC_PMU_CAP_REVISION);

	bcma_debug(bus, "Found rev %u PMU (capabilities 0x%08X)\n", cc->pmu.rev,
		   pmucap);
पूर्ण

व्योम bcma_pmu_init(काष्ठा bcma_drv_cc *cc)
अणु
	अगर (cc->pmu.rev == 1)
		bcma_pmu_mask32(cc, BCMA_CC_PMU_CTL,
				~BCMA_CC_PMU_CTL_NOILPONW);
	अन्यथा
		bcma_pmu_set32(cc, BCMA_CC_PMU_CTL,
			       BCMA_CC_PMU_CTL_NOILPONW);

	bcma_pmu_pll_init(cc);
	bcma_pmu_resources_init(cc);
	bcma_pmu_workarounds(cc);
पूर्ण

u32 bcma_pmu_get_alp_घड़ी(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;

	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM4313:
	हाल BCMA_CHIP_ID_BCM43224:
	हाल BCMA_CHIP_ID_BCM43225:
	हाल BCMA_CHIP_ID_BCM43227:
	हाल BCMA_CHIP_ID_BCM43228:
	हाल BCMA_CHIP_ID_BCM4331:
	हाल BCMA_CHIP_ID_BCM43421:
	हाल BCMA_CHIP_ID_BCM43428:
	हाल BCMA_CHIP_ID_BCM43431:
	हाल BCMA_CHIP_ID_BCM4716:
	हाल BCMA_CHIP_ID_BCM47162:
	हाल BCMA_CHIP_ID_BCM4748:
	हाल BCMA_CHIP_ID_BCM4749:
	हाल BCMA_CHIP_ID_BCM5357:
	हाल BCMA_CHIP_ID_BCM53572:
	हाल BCMA_CHIP_ID_BCM6362:
		/* always 20Mhz */
		वापस 20000 * 1000;
	हाल BCMA_CHIP_ID_BCM4706:
	हाल BCMA_CHIP_ID_BCM5356:
		/* always 25Mhz */
		वापस 25000 * 1000;
	हाल BCMA_CHIP_ID_BCM43460:
	हाल BCMA_CHIP_ID_BCM4352:
	हाल BCMA_CHIP_ID_BCM4360:
		अगर (cc->status & BCMA_CC_CHIPST_4360_XTAL_40MZ)
			वापस 40000 * 1000;
		अन्यथा
			वापस 20000 * 1000;
	शेष:
		bcma_warn(bus, "No ALP clock specified for %04X device, pmu rev. %d, using default %d Hz\n",
			  bus->chipinfo.id, cc->pmu.rev, BCMA_CC_PMU_ALP_CLOCK);
	पूर्ण
	वापस BCMA_CC_PMU_ALP_CLOCK;
पूर्ण

/* Find the output of the "m" pll भागider given pll controls that start with
 * pllreg "pll0" i.e. 12 क्रम मुख्य 6 क्रम phy, 0 क्रम misc.
 */
अटल u32 bcma_pmu_pll_घड़ी(काष्ठा bcma_drv_cc *cc, u32 pll0, u32 m)
अणु
	u32 पंचांगp, भाग, nभाग, p1, p2, fc;
	काष्ठा bcma_bus *bus = cc->core->bus;

	BUG_ON((pll0 & 3) || (pll0 > BCMA_CC_PMU4716_MAINPLL_PLL0));

	BUG_ON(!m || m > 4);

	अगर (bus->chipinfo.id == BCMA_CHIP_ID_BCM5357 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM4749) अणु
		/* Detect failure in घड़ी setting */
		पंचांगp = bcma_cc_पढ़ो32(cc, BCMA_CC_CHIPSTAT);
		अगर (पंचांगp & 0x40000)
			वापस 133 * 1000000;
	पूर्ण

	पंचांगp = bcma_chipco_pll_पढ़ो(cc, pll0 + BCMA_CC_PPL_P1P2_OFF);
	p1 = (पंचांगp & BCMA_CC_PPL_P1_MASK) >> BCMA_CC_PPL_P1_SHIFT;
	p2 = (पंचांगp & BCMA_CC_PPL_P2_MASK) >> BCMA_CC_PPL_P2_SHIFT;

	पंचांगp = bcma_chipco_pll_पढ़ो(cc, pll0 + BCMA_CC_PPL_M14_OFF);
	भाग = (पंचांगp >> ((m - 1) * BCMA_CC_PPL_MDIV_WIDTH)) &
		BCMA_CC_PPL_MDIV_MASK;

	पंचांगp = bcma_chipco_pll_पढ़ो(cc, pll0 + BCMA_CC_PPL_NM5_OFF);
	nभाग = (पंचांगp & BCMA_CC_PPL_NDIV_MASK) >> BCMA_CC_PPL_NDIV_SHIFT;

	/* Do calculation in Mhz */
	fc = bcma_pmu_get_alp_घड़ी(cc) / 1000000;
	fc = (p1 * nभाग * fc) / p2;

	/* Return घड़ी in Hertz */
	वापस (fc / भाग) * 1000000;
पूर्ण

अटल u32 bcma_pmu_pll_घड़ी_bcm4706(काष्ठा bcma_drv_cc *cc, u32 pll0, u32 m)
अणु
	u32 पंचांगp, nभाग, p1भाग, p2भाग;
	u32 घड़ी;

	BUG_ON(!m || m > 4);

	/* Get N, P1 and P2 भागiders to determine CPU घड़ी */
	पंचांगp = bcma_chipco_pll_पढ़ो(cc, pll0 + BCMA_CC_PMU6_4706_PROCPLL_OFF);
	nभाग = (पंचांगp & BCMA_CC_PMU6_4706_PROC_NDIV_INT_MASK)
		>> BCMA_CC_PMU6_4706_PROC_NDIV_INT_SHIFT;
	p1भाग = (पंचांगp & BCMA_CC_PMU6_4706_PROC_P1DIV_MASK)
		>> BCMA_CC_PMU6_4706_PROC_P1DIV_SHIFT;
	p2भाग = (पंचांगp & BCMA_CC_PMU6_4706_PROC_P2DIV_MASK)
		>> BCMA_CC_PMU6_4706_PROC_P2DIV_SHIFT;

	पंचांगp = bcma_cc_पढ़ो32(cc, BCMA_CC_CHIPSTAT);
	अगर (पंचांगp & BCMA_CC_CHIPST_4706_PKG_OPTION)
		/* Low cost bonding: Fixed reference घड़ी 25MHz and m = 4 */
		घड़ी = (25000000 / 4) * nभाग * p2भाग / p1भाग;
	अन्यथा
		/* Fixed reference घड़ी 25MHz and m = 2 */
		घड़ी = (25000000 / 2) * nभाग * p2भाग / p1भाग;

	अगर (m == BCMA_CC_PMU5_MAINPLL_SSB)
		घड़ी = घड़ी / 4;

	वापस घड़ी;
पूर्ण

/* query bus घड़ी frequency क्रम PMU-enabled chipcommon */
u32 bcma_pmu_get_bus_घड़ी(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;

	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM4716:
	हाल BCMA_CHIP_ID_BCM4748:
	हाल BCMA_CHIP_ID_BCM47162:
		वापस bcma_pmu_pll_घड़ी(cc, BCMA_CC_PMU4716_MAINPLL_PLL0,
					  BCMA_CC_PMU5_MAINPLL_SSB);
	हाल BCMA_CHIP_ID_BCM5356:
		वापस bcma_pmu_pll_घड़ी(cc, BCMA_CC_PMU5356_MAINPLL_PLL0,
					  BCMA_CC_PMU5_MAINPLL_SSB);
	हाल BCMA_CHIP_ID_BCM5357:
	हाल BCMA_CHIP_ID_BCM4749:
		वापस bcma_pmu_pll_घड़ी(cc, BCMA_CC_PMU5357_MAINPLL_PLL0,
					  BCMA_CC_PMU5_MAINPLL_SSB);
	हाल BCMA_CHIP_ID_BCM4706:
		वापस bcma_pmu_pll_घड़ी_bcm4706(cc,
						  BCMA_CC_PMU4706_MAINPLL_PLL0,
						  BCMA_CC_PMU5_MAINPLL_SSB);
	हाल BCMA_CHIP_ID_BCM53572:
		वापस 75000000;
	शेष:
		bcma_warn(bus, "No bus clock specified for %04X device, pmu rev. %d, using default %d Hz\n",
			  bus->chipinfo.id, cc->pmu.rev, BCMA_CC_PMU_HT_CLOCK);
	पूर्ण
	वापस BCMA_CC_PMU_HT_CLOCK;
पूर्ण
EXPORT_SYMBOL_GPL(bcma_pmu_get_bus_घड़ी);

/* query cpu घड़ी frequency क्रम PMU-enabled chipcommon */
u32 bcma_pmu_get_cpu_घड़ी(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;

	अगर (bus->chipinfo.id == BCMA_CHIP_ID_BCM53572)
		वापस 300000000;

	/* New PMUs can have dअगरferent घड़ी क्रम bus and CPU */
	अगर (cc->pmu.rev >= 5) अणु
		u32 pll;
		चयन (bus->chipinfo.id) अणु
		हाल BCMA_CHIP_ID_BCM4706:
			वापस bcma_pmu_pll_घड़ी_bcm4706(cc,
						BCMA_CC_PMU4706_MAINPLL_PLL0,
						BCMA_CC_PMU5_MAINPLL_CPU);
		हाल BCMA_CHIP_ID_BCM5356:
			pll = BCMA_CC_PMU5356_MAINPLL_PLL0;
			अवरोध;
		हाल BCMA_CHIP_ID_BCM5357:
		हाल BCMA_CHIP_ID_BCM4749:
			pll = BCMA_CC_PMU5357_MAINPLL_PLL0;
			अवरोध;
		शेष:
			pll = BCMA_CC_PMU4716_MAINPLL_PLL0;
			अवरोध;
		पूर्ण

		वापस bcma_pmu_pll_घड़ी(cc, pll, BCMA_CC_PMU5_MAINPLL_CPU);
	पूर्ण

	/* On old PMUs CPU has the same घड़ी as the bus */
	वापस bcma_pmu_get_bus_घड़ी(cc);
पूर्ण

अटल व्योम bcma_pmu_spuraव्योम_pll_ग_लिखो(काष्ठा bcma_drv_cc *cc, u32 offset,
					 u32 value)
अणु
	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_PLLCTL_ADDR, offset);
	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_PLLCTL_DATA, value);
पूर्ण

व्योम bcma_pmu_spuraव्योम_pllupdate(काष्ठा bcma_drv_cc *cc, पूर्णांक spuraव्योम)
अणु
	u32 पंचांगp = 0;
	u8 phypll_offset = 0;
	u8 bcm5357_bcm43236_p1भाग[] = अणु0x1, 0x5, 0x5पूर्ण;
	u8 bcm5357_bcm43236_nभाग[] = अणु0x30, 0xf6, 0xfcपूर्ण;
	काष्ठा bcma_bus *bus = cc->core->bus;

	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM5357:
	हाल BCMA_CHIP_ID_BCM4749:
	हाल BCMA_CHIP_ID_BCM53572:
		/* 5357[ab]0, 43236[ab]0, and 6362b0 */

		/*
		 * BCM5357 needs to touch PLL1_PLLCTL[02],
		 * so offset PLL0_PLLCTL[02] by 6
		 */
		phypll_offset = (bus->chipinfo.id == BCMA_CHIP_ID_BCM5357 ||
		       bus->chipinfo.id == BCMA_CHIP_ID_BCM4749 ||
		       bus->chipinfo.id == BCMA_CHIP_ID_BCM53572) ? 6 : 0;

		/* RMW only the P1 भागider */
		bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_PLLCTL_ADDR,
				BCMA_CC_PMU_PLL_CTL0 + phypll_offset);
		पंचांगp = bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_PLLCTL_DATA);
		पंचांगp &= (~(BCMA_CC_PMU1_PLL0_PC0_P1DIV_MASK));
		पंचांगp |= (bcm5357_bcm43236_p1भाग[spuraव्योम] << BCMA_CC_PMU1_PLL0_PC0_P1DIV_SHIFT);
		bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_PLLCTL_DATA, पंचांगp);

		/* RMW only the पूर्णांक feedback भागider */
		bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_PLLCTL_ADDR,
				BCMA_CC_PMU_PLL_CTL2 + phypll_offset);
		पंचांगp = bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_PLLCTL_DATA);
		पंचांगp &= ~(BCMA_CC_PMU1_PLL0_PC2_NDIV_INT_MASK);
		पंचांगp |= (bcm5357_bcm43236_nभाग[spuraव्योम]) << BCMA_CC_PMU1_PLL0_PC2_NDIV_INT_SHIFT;
		bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_PLLCTL_DATA, पंचांगp);

		पंचांगp = BCMA_CC_PMU_CTL_PLL_UPD;
		अवरोध;

	हाल BCMA_CHIP_ID_BCM4331:
	हाल BCMA_CHIP_ID_BCM43431:
		अगर (spuraव्योम == 2) अणु
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11500014);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x0FC00a08);
		पूर्ण अन्यथा अगर (spuraव्योम == 1) अणु
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11500014);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x0F600a08);
		पूर्ण अन्यथा अणु
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11100014);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x03000a08);
		पूर्ण
		पंचांगp = BCMA_CC_PMU_CTL_PLL_UPD;
		अवरोध;

	हाल BCMA_CHIP_ID_BCM43224:
	हाल BCMA_CHIP_ID_BCM43225:
	हाल BCMA_CHIP_ID_BCM43421:
		अगर (spuraव्योम == 1) अणु
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11500010);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x000C0C06);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x0F600a08);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00000000);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x2001E920);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		पूर्ण अन्यथा अणु
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11100010);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x000c0c06);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x03000a08);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00000000);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x200005c0);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		पूर्ण
		पंचांगp = BCMA_CC_PMU_CTL_PLL_UPD;
		अवरोध;

	हाल BCMA_CHIP_ID_BCM4716:
	हाल BCMA_CHIP_ID_BCM4748:
	हाल BCMA_CHIP_ID_BCM47162:
		अगर (spuraव्योम == 1) अणु
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11500060);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x080C0C06);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x0F600000);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00000000);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x2001E924);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		पूर्ण अन्यथा अणु
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11100060);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x080c0c06);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x03000000);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00000000);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x200005c0);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		पूर्ण

		पंचांगp = BCMA_CC_PMU_CTL_PLL_UPD | BCMA_CC_PMU_CTL_NOILPONW;
		अवरोध;

	हाल BCMA_CHIP_ID_BCM43131:
	हाल BCMA_CHIP_ID_BCM43217:
	हाल BCMA_CHIP_ID_BCM43227:
	हाल BCMA_CHIP_ID_BCM43228:
	हाल BCMA_CHIP_ID_BCM43428:
		/* LCNXN */
		/*
		 * PLL Settings क्रम spur aव्योमance on/off mode,
		 * no on2 support क्रम 43228A0
		 */
		अगर (spuraव्योम == 1) अणु
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x01100014);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x040C0C06);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x03140A08);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00333333);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x202C2820);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		पूर्ण अन्यथा अणु
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL0,
						     0x11100014);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL1,
						     0x040c0c06);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL2,
						     0x03000a08);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL3,
						     0x00000000);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL4,
						     0x200005c0);
			bcma_pmu_spuraव्योम_pll_ग_लिखो(cc, BCMA_CC_PMU_PLL_CTL5,
						     0x88888815);
		पूर्ण
		पंचांगp = BCMA_CC_PMU_CTL_PLL_UPD;
		अवरोध;
	शेष:
		bcma_err(bus, "Unknown spuravoidance settings for chip 0x%04X, not changing PLL\n",
			 bus->chipinfo.id);
		अवरोध;
	पूर्ण

	पंचांगp |= bcma_pmu_पढ़ो32(cc, BCMA_CC_PMU_CTL);
	bcma_pmu_ग_लिखो32(cc, BCMA_CC_PMU_CTL, पंचांगp);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_pmu_spuraव्योम_pllupdate);
