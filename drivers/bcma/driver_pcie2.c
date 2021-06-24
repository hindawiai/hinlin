<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * PCIe Gen 2 Core
 *
 * Copyright 2014, Broadcom Corporation
 * Copyright 2014, Rafaध Miधecki <zajec5@gmail.com>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/pci.h>

/**************************************************
 * R/W ops.
 **************************************************/

#अगर 0
अटल u32 bcma_core_pcie2_cfg_पढ़ो(काष्ठा bcma_drv_pcie2 *pcie2, u32 addr)
अणु
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, addr);
	pcie2_पढ़ो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR);
	वापस pcie2_पढ़ो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA);
पूर्ण
#पूर्ण_अगर

अटल व्योम bcma_core_pcie2_cfg_ग_लिखो(काष्ठा bcma_drv_pcie2 *pcie2, u32 addr,
				      u32 val)
अणु
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, addr);
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, val);
पूर्ण

/**************************************************
 * Init.
 **************************************************/

अटल u32 bcma_core_pcie2_war_delay_perst_enab(काष्ठा bcma_drv_pcie2 *pcie2,
						bool enable)
अणु
	u32 val;

	/* restore back to शेष */
	val = pcie2_पढ़ो32(pcie2, BCMA_CORE_PCIE2_CLK_CONTROL);
	val |= PCIE2_CLKC_DLYPERST;
	val &= ~PCIE2_CLKC_DISSPROMLD;
	अगर (enable) अणु
		val &= ~PCIE2_CLKC_DLYPERST;
		val |= PCIE2_CLKC_DISSPROMLD;
	पूर्ण
	pcie2_ग_लिखो32(pcie2, (BCMA_CORE_PCIE2_CLK_CONTROL), val);
	/* flush */
	वापस pcie2_पढ़ो32(pcie2, BCMA_CORE_PCIE2_CLK_CONTROL);
पूर्ण

अटल व्योम bcma_core_pcie2_set_ltr_vals(काष्ठा bcma_drv_pcie2 *pcie2)
अणु
	/* LTR0 */
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, 0x844);
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, 0x883c883c);
	/* LTR1 */
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, 0x848);
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, 0x88648864);
	/* LTR2 */
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, 0x84C);
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, 0x90039003);
पूर्ण

अटल व्योम bcma_core_pcie2_hw_ltr_war(काष्ठा bcma_drv_pcie2 *pcie2)
अणु
	u8 core_rev = pcie2->core->id.rev;
	u32 devstsctr2;

	अगर (core_rev < 2 || core_rev == 10 || core_rev > 13)
		वापस;

	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR,
		      PCIE2_CAP_DEVSTSCTRL2_OFFSET);
	devstsctr2 = pcie2_पढ़ो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA);
	अगर (devstsctr2 & PCIE2_CAP_DEVSTSCTRL2_LTRENAB) अणु
		/* क्रमce the right LTR values */
		bcma_core_pcie2_set_ltr_vals(pcie2);

		/* TODO:
		 *si_core_wrapperreg(pcie2, 3, 0x60, 0x8080, 0);
		 */

		/* enable the LTR */
		devstsctr2 |= PCIE2_CAP_DEVSTSCTRL2_LTRENAB;
		pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR,
			      PCIE2_CAP_DEVSTSCTRL2_OFFSET);
		pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, devstsctr2);

		/* set the LTR state to be active */
		pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_LTR_STATE,
			      PCIE2_LTR_ACTIVE);
		usleep_range(1000, 2000);

		/* set the LTR state to be sleep */
		pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_LTR_STATE,
			      PCIE2_LTR_SLEEP);
		usleep_range(1000, 2000);
	पूर्ण
पूर्ण

अटल व्योम pciedev_crwlpciegen2(काष्ठा bcma_drv_pcie2 *pcie2)
अणु
	u8 core_rev = pcie2->core->id.rev;
	bool pciewar160, pciewar162;

	pciewar160 = core_rev == 7 || core_rev == 9 || core_rev == 11;
	pciewar162 = core_rev == 5 || core_rev == 7 || core_rev == 8 ||
		     core_rev == 9 || core_rev == 11;

	अगर (!pciewar160 && !pciewar162)
		वापस;

/* TODO */
#अगर 0
	pcie2_set32(pcie2, BCMA_CORE_PCIE2_CLK_CONTROL,
		    PCIE_DISABLE_L1CLK_GATING);
#अगर 0
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR,
		      PCIEGEN2_COE_PVT_TL_CTRL_0);
	pcie2_mask32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA,
		     ~(1 << COE_PVT_TL_CTRL_0_PM_DIS_L1_REENTRY_BIT));
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

अटल व्योम pciedev_crwlpciegen2_180(काष्ठा bcma_drv_pcie2 *pcie2)
अणु
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, PCIE2_PMCR_REFUP);
	pcie2_set32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, 0x1f);
पूर्ण

अटल व्योम pciedev_crwlpciegen2_182(काष्ठा bcma_drv_pcie2 *pcie2)
अणु
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, PCIE2_SBMBX);
	pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, 1 << 0);
पूर्ण

अटल व्योम pciedev_reg_pm_clk_period(काष्ठा bcma_drv_pcie2 *pcie2)
अणु
	काष्ठा bcma_drv_cc *drv_cc = &pcie2->core->bus->drv_cc;
	u8 core_rev = pcie2->core->id.rev;
	u32 alp_khz, pm_value;

	अगर (core_rev <= 13) अणु
		alp_khz = bcma_pmu_get_alp_घड़ी(drv_cc) / 1000;
		pm_value = (1000000 * 2) / alp_khz;
		pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR,
			      PCIE2_PVT_REG_PM_CLK_PERIOD);
		pcie2_ग_लिखो32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, pm_value);
	पूर्ण
पूर्ण

व्योम bcma_core_pcie2_init(काष्ठा bcma_drv_pcie2 *pcie2)
अणु
	काष्ठा bcma_bus *bus = pcie2->core->bus;
	काष्ठा bcma_chipinfo *ci = &bus->chipinfo;
	u32 पंचांगp;

	पंचांगp = pcie2_पढ़ो32(pcie2, BCMA_CORE_PCIE2_SPROM(54));
	अगर ((पंचांगp & 0xe) >> 1 == 2)
		bcma_core_pcie2_cfg_ग_लिखो(pcie2, 0x4e0, 0x17);

	चयन (bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM4360:
	हाल BCMA_CHIP_ID_BCM4352:
		pcie2->reqsize = 1024;
		अवरोध;
	शेष:
		pcie2->reqsize = 128;
		अवरोध;
	पूर्ण

	अगर (ci->id == BCMA_CHIP_ID_BCM4360 && ci->rev > 3)
		bcma_core_pcie2_war_delay_perst_enab(pcie2, true);
	bcma_core_pcie2_hw_ltr_war(pcie2);
	pciedev_crwlpciegen2(pcie2);
	pciedev_reg_pm_clk_period(pcie2);
	pciedev_crwlpciegen2_180(pcie2);
	pciedev_crwlpciegen2_182(pcie2);
पूर्ण

/**************************************************
 * Runसमय ops.
 **************************************************/

व्योम bcma_core_pcie2_up(काष्ठा bcma_drv_pcie2 *pcie2)
अणु
	काष्ठा bcma_bus *bus = pcie2->core->bus;
	काष्ठा pci_dev *dev = bus->host_pci;
	पूर्णांक err;

	err = pcie_set_पढ़ोrq(dev, pcie2->reqsize);
	अगर (err)
		bcma_err(bus, "Error setting PCI_EXP_DEVCTL_READRQ: %d\n", err);
पूर्ण
