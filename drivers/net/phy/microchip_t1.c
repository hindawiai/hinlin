<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Microchip Technology

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>

/* External Register Control Register */
#घोषणा LAN87XX_EXT_REG_CTL                     (0x14)
#घोषणा LAN87XX_EXT_REG_CTL_RD_CTL              (0x1000)
#घोषणा LAN87XX_EXT_REG_CTL_WR_CTL              (0x0800)

/* External Register Read Data Register */
#घोषणा LAN87XX_EXT_REG_RD_DATA                 (0x15)

/* External Register Write Data Register */
#घोषणा LAN87XX_EXT_REG_WR_DATA                 (0x16)

/* Interrupt Source Register */
#घोषणा LAN87XX_INTERRUPT_SOURCE                (0x18)

/* Interrupt Mask Register */
#घोषणा LAN87XX_INTERRUPT_MASK                  (0x19)
#घोषणा LAN87XX_MASK_LINK_UP                    (0x0004)
#घोषणा LAN87XX_MASK_LINK_DOWN                  (0x0002)

/* phyaccess nested types */
#घोषणा	PHYACC_ATTR_MODE_READ		0
#घोषणा	PHYACC_ATTR_MODE_WRITE		1
#घोषणा	PHYACC_ATTR_MODE_MODIFY		2

#घोषणा	PHYACC_ATTR_BANK_SMI		0
#घोषणा	PHYACC_ATTR_BANK_MISC		1
#घोषणा	PHYACC_ATTR_BANK_PCS		2
#घोषणा	PHYACC_ATTR_BANK_AFE		3
#घोषणा	PHYACC_ATTR_BANK_MAX		7

#घोषणा DRIVER_AUTHOR	"Nisar Sayed <nisar.sayed@microchip.com>"
#घोषणा DRIVER_DESC	"Microchip LAN87XX T1 PHY driver"

काष्ठा access_ereg_val अणु
	u8  mode;
	u8  bank;
	u8  offset;
	u16 val;
	u16 mask;
पूर्ण;

अटल पूर्णांक access_ereg(काष्ठा phy_device *phydev, u8 mode, u8 bank,
		       u8 offset, u16 val)
अणु
	u16 ereg = 0;
	पूर्णांक rc = 0;

	अगर (mode > PHYACC_ATTR_MODE_WRITE || bank > PHYACC_ATTR_BANK_MAX)
		वापस -EINVAL;

	अगर (bank == PHYACC_ATTR_BANK_SMI) अणु
		अगर (mode == PHYACC_ATTR_MODE_WRITE)
			rc = phy_ग_लिखो(phydev, offset, val);
		अन्यथा
			rc = phy_पढ़ो(phydev, offset);
		वापस rc;
	पूर्ण

	अगर (mode == PHYACC_ATTR_MODE_WRITE) अणु
		ereg = LAN87XX_EXT_REG_CTL_WR_CTL;
		rc = phy_ग_लिखो(phydev, LAN87XX_EXT_REG_WR_DATA, val);
		अगर (rc < 0)
			वापस rc;
	पूर्ण अन्यथा अणु
		ereg = LAN87XX_EXT_REG_CTL_RD_CTL;
	पूर्ण

	ereg |= (bank << 8) | offset;

	rc = phy_ग_लिखो(phydev, LAN87XX_EXT_REG_CTL, ereg);
	अगर (rc < 0)
		वापस rc;

	अगर (mode == PHYACC_ATTR_MODE_READ)
		rc = phy_पढ़ो(phydev, LAN87XX_EXT_REG_RD_DATA);

	वापस rc;
पूर्ण

अटल पूर्णांक access_ereg_modअगरy_changed(काष्ठा phy_device *phydev,
				      u8 bank, u8 offset, u16 val, u16 mask)
अणु
	पूर्णांक new = 0, rc = 0;

	अगर (bank > PHYACC_ATTR_BANK_MAX)
		वापस -EINVAL;

	rc = access_ereg(phydev, PHYACC_ATTR_MODE_READ, bank, offset, val);
	अगर (rc < 0)
		वापस rc;

	new = val | (rc & (mask ^ 0xFFFF));
	rc = access_ereg(phydev, PHYACC_ATTR_MODE_WRITE, bank, offset, new);

	वापस rc;
पूर्ण

अटल पूर्णांक lan87xx_phy_init(काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा access_ereg_val init[] = अणु
		/* TX Amplitude = 5 */
		अणुPHYACC_ATTR_MODE_MODIFY, PHYACC_ATTR_BANK_AFE, 0x0B,
		 0x000A, 0x001Eपूर्ण,
		/* Clear SMI पूर्णांकerrupts */
		अणुPHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_SMI, 0x18,
		 0, 0पूर्ण,
		/* Clear MISC पूर्णांकerrupts */
		अणुPHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_MISC, 0x08,
		 0, 0पूर्ण,
		/* Turn on TC10 Ring Oscillator (ROSC) */
		अणुPHYACC_ATTR_MODE_MODIFY, PHYACC_ATTR_BANK_MISC, 0x20,
		 0x0020, 0x0020पूर्ण,
		/* WUR Detect Length to 1.2uS, LPC Detect Length to 1.09uS */
		अणुPHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_PCS, 0x20,
		 0x283C, 0पूर्ण,
		/* Wake_In Debounce Length to 39uS, Wake_Out Length to 79uS */
		अणुPHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_MISC, 0x21,
		 0x274F, 0पूर्ण,
		/* Enable Auto Wake Forward to Wake_Out, ROSC on, Sleep,
		 * and Wake_In to wake PHY
		 */
		अणुPHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_MISC, 0x20,
		 0x80A7, 0पूर्ण,
		/* Enable WUP Auto Fwd, Enable Wake on MDI, Wakeup Debouncer
		 * to 128 uS
		 */
		अणुPHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_MISC, 0x24,
		 0xF110, 0पूर्ण,
		/* Enable HW Init */
		अणुPHYACC_ATTR_MODE_MODIFY, PHYACC_ATTR_BANK_SMI, 0x1A,
		 0x0100, 0x0100पूर्ण,
	पूर्ण;
	पूर्णांक rc, i;

	/* Start manual initialization procedures in Managed Mode */
	rc = access_ereg_modअगरy_changed(phydev, PHYACC_ATTR_BANK_SMI,
					0x1a, 0x0000, 0x0100);
	अगर (rc < 0)
		वापस rc;

	/* Soft Reset the SMI block */
	rc = access_ereg_modअगरy_changed(phydev, PHYACC_ATTR_BANK_SMI,
					0x00, 0x8000, 0x8000);
	अगर (rc < 0)
		वापस rc;

	/* Check to see अगर the self-clearing bit is cleared */
	usleep_range(1000, 2000);
	rc = access_ereg(phydev, PHYACC_ATTR_MODE_READ,
			 PHYACC_ATTR_BANK_SMI, 0x00, 0);
	अगर (rc < 0)
		वापस rc;
	अगर ((rc & 0x8000) != 0)
		वापस -ETIMEDOUT;

	/* PHY Initialization */
	क्रम (i = 0; i < ARRAY_SIZE(init); i++) अणु
		अगर (init[i].mode == PHYACC_ATTR_MODE_MODIFY) अणु
			rc = access_ereg_modअगरy_changed(phydev, init[i].bank,
							init[i].offset,
							init[i].val,
							init[i].mask);
		पूर्ण अन्यथा अणु
			rc = access_ereg(phydev, init[i].mode, init[i].bank,
					 init[i].offset, init[i].val);
		पूर्ण
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lan87xx_phy_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc, val = 0;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		/* unmask all source and clear them beक्रमe enable */
		rc = phy_ग_लिखो(phydev, LAN87XX_INTERRUPT_MASK, 0x7FFF);
		rc = phy_पढ़ो(phydev, LAN87XX_INTERRUPT_SOURCE);
		val = LAN87XX_MASK_LINK_UP | LAN87XX_MASK_LINK_DOWN;
		rc = phy_ग_लिखो(phydev, LAN87XX_INTERRUPT_MASK, val);
	पूर्ण अन्यथा अणु
		rc = phy_ग_लिखो(phydev, LAN87XX_INTERRUPT_MASK, val);
		अगर (rc)
			वापस rc;

		rc = phy_पढ़ो(phydev, LAN87XX_INTERRUPT_SOURCE);
	पूर्ण

	वापस rc < 0 ? rc : 0;
पूर्ण

अटल irqवापस_t lan87xx_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, LAN87XX_INTERRUPT_SOURCE);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (irq_status == 0)
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lan87xx_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc = lan87xx_phy_init(phydev);

	वापस rc < 0 ? rc : 0;
पूर्ण

अटल काष्ठा phy_driver microchip_t1_phy_driver[] = अणु
	अणु
		.phy_id         = 0x0007c150,
		.phy_id_mask    = 0xfffffff0,
		.name           = "Microchip LAN87xx T1",

		.features       = PHY_BASIC_T1_FEATURES,

		.config_init	= lan87xx_config_init,

		.config_पूर्णांकr    = lan87xx_phy_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = lan87xx_handle_पूर्णांकerrupt,

		.suspend        = genphy_suspend,
		.resume         = genphy_resume,
	पूर्ण
पूर्ण;

module_phy_driver(microchip_t1_phy_driver);

अटल काष्ठा mdio_device_id __maybe_unused microchip_t1_tbl[] = अणु
	अणु 0x0007c150, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, microchip_t1_tbl);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
