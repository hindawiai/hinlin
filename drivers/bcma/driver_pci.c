<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * PCI Core
 *
 * Copyright 2005, 2011, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <m@bues.ch>
 * Copyright 2011, 2012, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"
#समावेश <linux/export.h>
#समावेश <linux/bcma/bcma.h>

/**************************************************
 * R/W ops.
 **************************************************/

u32 bcma_pcie_पढ़ो(काष्ठा bcma_drv_pci *pc, u32 address)
अणु
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_PCIEIND_ADDR, address);
	pcicore_पढ़ो32(pc, BCMA_CORE_PCI_PCIEIND_ADDR);
	वापस pcicore_पढ़ो32(pc, BCMA_CORE_PCI_PCIEIND_DATA);
पूर्ण

अटल व्योम bcma_pcie_ग_लिखो(काष्ठा bcma_drv_pci *pc, u32 address, u32 data)
अणु
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_PCIEIND_ADDR, address);
	pcicore_पढ़ो32(pc, BCMA_CORE_PCI_PCIEIND_ADDR);
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_PCIEIND_DATA, data);
पूर्ण

अटल व्योम bcma_pcie_mdio_set_phy(काष्ठा bcma_drv_pci *pc, u16 phy)
अणु
	u32 v;
	पूर्णांक i;

	v = BCMA_CORE_PCI_MDIODATA_START;
	v |= BCMA_CORE_PCI_MDIODATA_WRITE;
	v |= (BCMA_CORE_PCI_MDIODATA_DEV_ADDR <<
	      BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF);
	v |= (BCMA_CORE_PCI_MDIODATA_BLK_ADDR <<
	      BCMA_CORE_PCI_MDIODATA_REGADDR_SHF);
	v |= BCMA_CORE_PCI_MDIODATA_TA;
	v |= (phy << 4);
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_MDIO_DATA, v);

	udelay(10);
	क्रम (i = 0; i < 200; i++) अणु
		v = pcicore_पढ़ो32(pc, BCMA_CORE_PCI_MDIO_CONTROL);
		अगर (v & BCMA_CORE_PCI_MDIOCTL_ACCESS_DONE)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
पूर्ण

अटल u16 bcma_pcie_mdio_पढ़ो(काष्ठा bcma_drv_pci *pc, u16 device, u8 address)
अणु
	पूर्णांक max_retries = 10;
	u16 ret = 0;
	u32 v;
	पूर्णांक i;

	/* enable mdio access to SERDES */
	v = BCMA_CORE_PCI_MDIOCTL_PREAM_EN;
	v |= BCMA_CORE_PCI_MDIOCTL_DIVISOR_VAL;
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_MDIO_CONTROL, v);

	अगर (pc->core->id.rev >= 10) अणु
		max_retries = 200;
		bcma_pcie_mdio_set_phy(pc, device);
		v = (BCMA_CORE_PCI_MDIODATA_DEV_ADDR <<
		     BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF);
		v |= (address << BCMA_CORE_PCI_MDIODATA_REGADDR_SHF);
	पूर्ण अन्यथा अणु
		v = (device << BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF_OLD);
		v |= (address << BCMA_CORE_PCI_MDIODATA_REGADDR_SHF_OLD);
	पूर्ण

	v |= BCMA_CORE_PCI_MDIODATA_START;
	v |= BCMA_CORE_PCI_MDIODATA_READ;
	v |= BCMA_CORE_PCI_MDIODATA_TA;

	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_MDIO_DATA, v);
	/* Wait क्रम the device to complete the transaction */
	udelay(10);
	क्रम (i = 0; i < max_retries; i++) अणु
		v = pcicore_पढ़ो32(pc, BCMA_CORE_PCI_MDIO_CONTROL);
		अगर (v & BCMA_CORE_PCI_MDIOCTL_ACCESS_DONE) अणु
			udelay(10);
			ret = pcicore_पढ़ो32(pc, BCMA_CORE_PCI_MDIO_DATA);
			अवरोध;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_MDIO_CONTROL, 0);
	वापस ret;
पूर्ण

अटल व्योम bcma_pcie_mdio_ग_लिखो(काष्ठा bcma_drv_pci *pc, u16 device,
				u8 address, u16 data)
अणु
	पूर्णांक max_retries = 10;
	u32 v;
	पूर्णांक i;

	/* enable mdio access to SERDES */
	v = BCMA_CORE_PCI_MDIOCTL_PREAM_EN;
	v |= BCMA_CORE_PCI_MDIOCTL_DIVISOR_VAL;
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_MDIO_CONTROL, v);

	अगर (pc->core->id.rev >= 10) अणु
		max_retries = 200;
		bcma_pcie_mdio_set_phy(pc, device);
		v = (BCMA_CORE_PCI_MDIODATA_DEV_ADDR <<
		     BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF);
		v |= (address << BCMA_CORE_PCI_MDIODATA_REGADDR_SHF);
	पूर्ण अन्यथा अणु
		v = (device << BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF_OLD);
		v |= (address << BCMA_CORE_PCI_MDIODATA_REGADDR_SHF_OLD);
	पूर्ण

	v |= BCMA_CORE_PCI_MDIODATA_START;
	v |= BCMA_CORE_PCI_MDIODATA_WRITE;
	v |= BCMA_CORE_PCI_MDIODATA_TA;
	v |= data;
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_MDIO_DATA, v);
	/* Wait क्रम the device to complete the transaction */
	udelay(10);
	क्रम (i = 0; i < max_retries; i++) अणु
		v = pcicore_पढ़ो32(pc, BCMA_CORE_PCI_MDIO_CONTROL);
		अगर (v & BCMA_CORE_PCI_MDIOCTL_ACCESS_DONE)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
	pcicore_ग_लिखो32(pc, BCMA_CORE_PCI_MDIO_CONTROL, 0);
पूर्ण

अटल u16 bcma_pcie_mdio_ग_लिखोपढ़ो(काष्ठा bcma_drv_pci *pc, u16 device,
				    u8 address, u16 data)
अणु
	bcma_pcie_mdio_ग_लिखो(pc, device, address, data);
	वापस bcma_pcie_mdio_पढ़ो(pc, device, address);
पूर्ण

/**************************************************
 * Early init.
 **************************************************/

अटल व्योम bcma_core_pci_fixcfg(काष्ठा bcma_drv_pci *pc)
अणु
	काष्ठा bcma_device *core = pc->core;
	u16 val16, core_index;
	uपूर्णांक regoff;

	regoff = BCMA_CORE_PCI_SPROM(BCMA_CORE_PCI_SPROM_PI_OFFSET);
	core_index = (u16)core->core_index;

	val16 = pcicore_पढ़ो16(pc, regoff);
	अगर (((val16 & BCMA_CORE_PCI_SPROM_PI_MASK) >> BCMA_CORE_PCI_SPROM_PI_SHIFT)
	     != core_index) अणु
		val16 = (core_index << BCMA_CORE_PCI_SPROM_PI_SHIFT) |
			(val16 & ~BCMA_CORE_PCI_SPROM_PI_MASK);
		pcicore_ग_लिखो16(pc, regoff, val16);
	पूर्ण
पूर्ण

/*
 * Apply some early fixes required beक्रमe accessing SPROM.
 * See also si_pci_fixcfg.
 */
व्योम bcma_core_pci_early_init(काष्ठा bcma_drv_pci *pc)
अणु
	अगर (pc->early_setup_करोne)
		वापस;

	pc->hosपंचांगode = bcma_core_pci_is_in_hosपंचांगode(pc);
	अगर (pc->hosपंचांगode)
		जाओ out;

	bcma_core_pci_fixcfg(pc);

out:
	pc->early_setup_करोne = true;
पूर्ण

/**************************************************
 * Workarounds.
 **************************************************/

अटल u8 bcma_pcicore_polarity_workaround(काष्ठा bcma_drv_pci *pc)
अणु
	u32 पंचांगp;

	पंचांगp = bcma_pcie_पढ़ो(pc, BCMA_CORE_PCI_PLP_STATUSREG);
	अगर (पंचांगp & BCMA_CORE_PCI_PLP_POLARITYINV_STAT)
		वापस BCMA_CORE_PCI_SERDES_RX_CTRL_FORCE |
		       BCMA_CORE_PCI_SERDES_RX_CTRL_POLARITY;
	अन्यथा
		वापस BCMA_CORE_PCI_SERDES_RX_CTRL_FORCE;
पूर्ण

अटल व्योम bcma_pcicore_serdes_workaround(काष्ठा bcma_drv_pci *pc)
अणु
	u16 पंचांगp;

	bcma_pcie_mdio_ग_लिखो(pc, BCMA_CORE_PCI_MDIODATA_DEV_RX,
	                     BCMA_CORE_PCI_SERDES_RX_CTRL,
			     bcma_pcicore_polarity_workaround(pc));
	पंचांगp = bcma_pcie_mdio_पढ़ो(pc, BCMA_CORE_PCI_MDIODATA_DEV_PLL,
	                          BCMA_CORE_PCI_SERDES_PLL_CTRL);
	अगर (पंचांगp & BCMA_CORE_PCI_PLL_CTRL_FREQDET_EN)
		bcma_pcie_mdio_ग_लिखो(pc, BCMA_CORE_PCI_MDIODATA_DEV_PLL,
		                     BCMA_CORE_PCI_SERDES_PLL_CTRL,
		                     पंचांगp & ~BCMA_CORE_PCI_PLL_CTRL_FREQDET_EN);
पूर्ण

/* Fix MISC config to allow coming out of L2/L3-Ready state w/o PRST */
/* Needs to happen when coming out of 'standby'/'hibernate' */
अटल व्योम bcma_core_pci_config_fixup(काष्ठा bcma_drv_pci *pc)
अणु
	u16 val16;
	uपूर्णांक regoff;

	regoff = BCMA_CORE_PCI_SPROM(BCMA_CORE_PCI_SPROM_MISC_CONFIG);

	val16 = pcicore_पढ़ो16(pc, regoff);

	अगर (!(val16 & BCMA_CORE_PCI_SPROM_L23READY_EXIT_NOPERST)) अणु
		val16 |= BCMA_CORE_PCI_SPROM_L23READY_EXIT_NOPERST;
		pcicore_ग_लिखो16(pc, regoff, val16);
	पूर्ण
पूर्ण

/**************************************************
 * Init.
 **************************************************/

अटल व्योम bcma_core_pci_clienपंचांगode_init(काष्ठा bcma_drv_pci *pc)
अणु
	bcma_pcicore_serdes_workaround(pc);
	bcma_core_pci_config_fixup(pc);
पूर्ण

व्योम bcma_core_pci_init(काष्ठा bcma_drv_pci *pc)
अणु
	अगर (pc->setup_करोne)
		वापस;

	bcma_core_pci_early_init(pc);

	अगर (pc->hosपंचांगode)
		bcma_core_pci_hosपंचांगode_init(pc);
	अन्यथा
		bcma_core_pci_clienपंचांगode_init(pc);
पूर्ण

व्योम bcma_core_pci_घातer_save(काष्ठा bcma_bus *bus, bool up)
अणु
	काष्ठा bcma_drv_pci *pc;
	u16 data;

	अगर (bus->hosttype != BCMA_HOSTTYPE_PCI)
		वापस;

	pc = &bus->drv_pci[0];

	अगर (pc->core->id.rev >= 15 && pc->core->id.rev <= 20) अणु
		data = up ? 0x74 : 0x7C;
		bcma_pcie_mdio_ग_लिखोपढ़ो(pc, BCMA_CORE_PCI_MDIO_BLK1,
					 BCMA_CORE_PCI_MDIO_BLK1_MGMT1, 0x7F64);
		bcma_pcie_mdio_ग_लिखोपढ़ो(pc, BCMA_CORE_PCI_MDIO_BLK1,
					 BCMA_CORE_PCI_MDIO_BLK1_MGMT3, data);
	पूर्ण अन्यथा अगर (pc->core->id.rev >= 21 && pc->core->id.rev <= 22) अणु
		data = up ? 0x75 : 0x7D;
		bcma_pcie_mdio_ग_लिखोपढ़ो(pc, BCMA_CORE_PCI_MDIO_BLK1,
					 BCMA_CORE_PCI_MDIO_BLK1_MGMT1, 0x7E65);
		bcma_pcie_mdio_ग_लिखोपढ़ो(pc, BCMA_CORE_PCI_MDIO_BLK1,
					 BCMA_CORE_PCI_MDIO_BLK1_MGMT3, data);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bcma_core_pci_घातer_save);

अटल व्योम bcma_core_pci_extend_L1समयr(काष्ठा bcma_drv_pci *pc, bool extend)
अणु
	u32 w;

	w = bcma_pcie_पढ़ो(pc, BCMA_CORE_PCI_DLLP_PMTHRESHREG);
	अगर (extend)
		w |= BCMA_CORE_PCI_ASPMTIMER_EXTEND;
	अन्यथा
		w &= ~BCMA_CORE_PCI_ASPMTIMER_EXTEND;
	bcma_pcie_ग_लिखो(pc, BCMA_CORE_PCI_DLLP_PMTHRESHREG, w);
	bcma_pcie_पढ़ो(pc, BCMA_CORE_PCI_DLLP_PMTHRESHREG);
पूर्ण

व्योम bcma_core_pci_up(काष्ठा bcma_drv_pci *pc)
अणु
	bcma_core_pci_extend_L1समयr(pc, true);
पूर्ण

व्योम bcma_core_pci_करोwn(काष्ठा bcma_drv_pci *pc)
अणु
	bcma_core_pci_extend_L1समयr(pc, false);
पूर्ण
