<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2012 Daniel Schwierzeck <daniel.schwierzeck@googlemail.com>
 * Copyright (C) 2016 Hauke Mehrtens <hauke@hauke-m.de>
 */

#समावेश <linux/mdपन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>

#घोषणा XWAY_MDIO_IMASK			0x19	/* पूर्णांकerrupt mask */
#घोषणा XWAY_MDIO_ISTAT			0x1A	/* पूर्णांकerrupt status */
#घोषणा XWAY_MDIO_LED			0x1B	/* led control */

/* bit 15:12 are reserved */
#घोषणा XWAY_MDIO_LED_LED3_EN		BIT(11)	/* Enable the पूर्णांकegrated function of LED3 */
#घोषणा XWAY_MDIO_LED_LED2_EN		BIT(10)	/* Enable the पूर्णांकegrated function of LED2 */
#घोषणा XWAY_MDIO_LED_LED1_EN		BIT(9)	/* Enable the पूर्णांकegrated function of LED1 */
#घोषणा XWAY_MDIO_LED_LED0_EN		BIT(8)	/* Enable the पूर्णांकegrated function of LED0 */
/* bit 7:4 are reserved */
#घोषणा XWAY_MDIO_LED_LED3_DA		BIT(3)	/* Direct Access to LED3 */
#घोषणा XWAY_MDIO_LED_LED2_DA		BIT(2)	/* Direct Access to LED2 */
#घोषणा XWAY_MDIO_LED_LED1_DA		BIT(1)	/* Direct Access to LED1 */
#घोषणा XWAY_MDIO_LED_LED0_DA		BIT(0)	/* Direct Access to LED0 */

#घोषणा XWAY_MDIO_INIT_WOL		BIT(15)	/* Wake-On-LAN */
#घोषणा XWAY_MDIO_INIT_MSRE		BIT(14)
#घोषणा XWAY_MDIO_INIT_NPRX		BIT(13)
#घोषणा XWAY_MDIO_INIT_NPTX		BIT(12)
#घोषणा XWAY_MDIO_INIT_ANE		BIT(11)	/* Auto-Neg error */
#घोषणा XWAY_MDIO_INIT_ANC		BIT(10)	/* Auto-Neg complete */
#घोषणा XWAY_MDIO_INIT_ADSC		BIT(5)	/* Link स्वतः-करोwnspeed detect */
#घोषणा XWAY_MDIO_INIT_MPIPC		BIT(4)
#घोषणा XWAY_MDIO_INIT_MDIXC		BIT(3)
#घोषणा XWAY_MDIO_INIT_DXMC		BIT(2)	/* Duplex mode change */
#घोषणा XWAY_MDIO_INIT_LSPC		BIT(1)	/* Link speed change */
#घोषणा XWAY_MDIO_INIT_LSTC		BIT(0)	/* Link state change */
#घोषणा XWAY_MDIO_INIT_MASK		(XWAY_MDIO_INIT_LSTC | \
					 XWAY_MDIO_INIT_ADSC)

#घोषणा ADVERTISED_MPD			BIT(10)	/* Multi-port device */

/* LED Configuration */
#घोषणा XWAY_MMD_LEDCH			0x01E0
/* Inverse of SCAN Function */
#घोषणा  XWAY_MMD_LEDCH_NACS_NONE	0x0000
#घोषणा  XWAY_MMD_LEDCH_NACS_LINK	0x0001
#घोषणा  XWAY_MMD_LEDCH_NACS_PDOWN	0x0002
#घोषणा  XWAY_MMD_LEDCH_NACS_EEE	0x0003
#घोषणा  XWAY_MMD_LEDCH_NACS_ANEG	0x0004
#घोषणा  XWAY_MMD_LEDCH_NACS_ABIST	0x0005
#घोषणा  XWAY_MMD_LEDCH_NACS_CDIAG	0x0006
#घोषणा  XWAY_MMD_LEDCH_NACS_TEST	0x0007
/* Slow Blink Frequency */
#घोषणा  XWAY_MMD_LEDCH_SBF_F02HZ	0x0000
#घोषणा  XWAY_MMD_LEDCH_SBF_F04HZ	0x0010
#घोषणा  XWAY_MMD_LEDCH_SBF_F08HZ	0x0020
#घोषणा  XWAY_MMD_LEDCH_SBF_F16HZ	0x0030
/* Fast Blink Frequency */
#घोषणा  XWAY_MMD_LEDCH_FBF_F02HZ	0x0000
#घोषणा  XWAY_MMD_LEDCH_FBF_F04HZ	0x0040
#घोषणा  XWAY_MMD_LEDCH_FBF_F08HZ	0x0080
#घोषणा  XWAY_MMD_LEDCH_FBF_F16HZ	0x00C0
/* LED Configuration */
#घोषणा XWAY_MMD_LEDCL			0x01E1
/* Complex Blinking Configuration */
#घोषणा  XWAY_MMD_LEDCH_CBLINK_NONE	0x0000
#घोषणा  XWAY_MMD_LEDCH_CBLINK_LINK	0x0001
#घोषणा  XWAY_MMD_LEDCH_CBLINK_PDOWN	0x0002
#घोषणा  XWAY_MMD_LEDCH_CBLINK_EEE	0x0003
#घोषणा  XWAY_MMD_LEDCH_CBLINK_ANEG	0x0004
#घोषणा  XWAY_MMD_LEDCH_CBLINK_ABIST	0x0005
#घोषणा  XWAY_MMD_LEDCH_CBLINK_CDIAG	0x0006
#घोषणा  XWAY_MMD_LEDCH_CBLINK_TEST	0x0007
/* Complex SCAN Configuration */
#घोषणा  XWAY_MMD_LEDCH_SCAN_NONE	0x0000
#घोषणा  XWAY_MMD_LEDCH_SCAN_LINK	0x0010
#घोषणा  XWAY_MMD_LEDCH_SCAN_PDOWN	0x0020
#घोषणा  XWAY_MMD_LEDCH_SCAN_EEE	0x0030
#घोषणा  XWAY_MMD_LEDCH_SCAN_ANEG	0x0040
#घोषणा  XWAY_MMD_LEDCH_SCAN_ABIST	0x0050
#घोषणा  XWAY_MMD_LEDCH_SCAN_CDIAG	0x0060
#घोषणा  XWAY_MMD_LEDCH_SCAN_TEST	0x0070
/* Configuration क्रम LED Pin x */
#घोषणा XWAY_MMD_LED0H			0x01E2
/* Fast Blinking Configuration */
#घोषणा  XWAY_MMD_LEDxH_BLINKF_MASK	0x000F
#घोषणा  XWAY_MMD_LEDxH_BLINKF_NONE	0x0000
#घोषणा  XWAY_MMD_LEDxH_BLINKF_LINK10	0x0001
#घोषणा  XWAY_MMD_LEDxH_BLINKF_LINK100	0x0002
#घोषणा  XWAY_MMD_LEDxH_BLINKF_LINK10X	0x0003
#घोषणा  XWAY_MMD_LEDxH_BLINKF_LINK1000	0x0004
#घोषणा  XWAY_MMD_LEDxH_BLINKF_LINK10_0	0x0005
#घोषणा  XWAY_MMD_LEDxH_BLINKF_LINK100X	0x0006
#घोषणा  XWAY_MMD_LEDxH_BLINKF_LINK10XX	0x0007
#घोषणा  XWAY_MMD_LEDxH_BLINKF_PDOWN	0x0008
#घोषणा  XWAY_MMD_LEDxH_BLINKF_EEE	0x0009
#घोषणा  XWAY_MMD_LEDxH_BLINKF_ANEG	0x000A
#घोषणा  XWAY_MMD_LEDxH_BLINKF_ABIST	0x000B
#घोषणा  XWAY_MMD_LEDxH_BLINKF_CDIAG	0x000C
/* Constant On Configuration */
#घोषणा  XWAY_MMD_LEDxH_CON_MASK	0x00F0
#घोषणा  XWAY_MMD_LEDxH_CON_NONE	0x0000
#घोषणा  XWAY_MMD_LEDxH_CON_LINK10	0x0010
#घोषणा  XWAY_MMD_LEDxH_CON_LINK100	0x0020
#घोषणा  XWAY_MMD_LEDxH_CON_LINK10X	0x0030
#घोषणा  XWAY_MMD_LEDxH_CON_LINK1000	0x0040
#घोषणा  XWAY_MMD_LEDxH_CON_LINK10_0	0x0050
#घोषणा  XWAY_MMD_LEDxH_CON_LINK100X	0x0060
#घोषणा  XWAY_MMD_LEDxH_CON_LINK10XX	0x0070
#घोषणा  XWAY_MMD_LEDxH_CON_PDOWN	0x0080
#घोषणा  XWAY_MMD_LEDxH_CON_EEE		0x0090
#घोषणा  XWAY_MMD_LEDxH_CON_ANEG	0x00A0
#घोषणा  XWAY_MMD_LEDxH_CON_ABIST	0x00B0
#घोषणा  XWAY_MMD_LEDxH_CON_CDIAG	0x00C0
#घोषणा  XWAY_MMD_LEDxH_CON_COPPER	0x00D0
#घोषणा  XWAY_MMD_LEDxH_CON_FIBER	0x00E0
/* Configuration क्रम LED Pin x */
#घोषणा XWAY_MMD_LED0L			0x01E3
/* Pulsing Configuration */
#घोषणा  XWAY_MMD_LEDxL_PULSE_MASK	0x000F
#घोषणा  XWAY_MMD_LEDxL_PULSE_NONE	0x0000
#घोषणा  XWAY_MMD_LEDxL_PULSE_TXACT	0x0001
#घोषणा  XWAY_MMD_LEDxL_PULSE_RXACT	0x0002
#घोषणा  XWAY_MMD_LEDxL_PULSE_COL	0x0004
/* Slow Blinking Configuration */
#घोषणा  XWAY_MMD_LEDxL_BLINKS_MASK	0x00F0
#घोषणा  XWAY_MMD_LEDxL_BLINKS_NONE	0x0000
#घोषणा  XWAY_MMD_LEDxL_BLINKS_LINK10	0x0010
#घोषणा  XWAY_MMD_LEDxL_BLINKS_LINK100	0x0020
#घोषणा  XWAY_MMD_LEDxL_BLINKS_LINK10X	0x0030
#घोषणा  XWAY_MMD_LEDxL_BLINKS_LINK1000	0x0040
#घोषणा  XWAY_MMD_LEDxL_BLINKS_LINK10_0	0x0050
#घोषणा  XWAY_MMD_LEDxL_BLINKS_LINK100X	0x0060
#घोषणा  XWAY_MMD_LEDxL_BLINKS_LINK10XX	0x0070
#घोषणा  XWAY_MMD_LEDxL_BLINKS_PDOWN	0x0080
#घोषणा  XWAY_MMD_LEDxL_BLINKS_EEE	0x0090
#घोषणा  XWAY_MMD_LEDxL_BLINKS_ANEG	0x00A0
#घोषणा  XWAY_MMD_LEDxL_BLINKS_ABIST	0x00B0
#घोषणा  XWAY_MMD_LEDxL_BLINKS_CDIAG	0x00C0
#घोषणा XWAY_MMD_LED1H			0x01E4
#घोषणा XWAY_MMD_LED1L			0x01E5
#घोषणा XWAY_MMD_LED2H			0x01E6
#घोषणा XWAY_MMD_LED2L			0x01E7
#घोषणा XWAY_MMD_LED3H			0x01E8
#घोषणा XWAY_MMD_LED3L			0x01E9

#घोषणा PHY_ID_PHY11G_1_3		0x030260D1
#घोषणा PHY_ID_PHY22F_1_3		0x030260E1
#घोषणा PHY_ID_PHY11G_1_4		0xD565A400
#घोषणा PHY_ID_PHY22F_1_4		0xD565A410
#घोषणा PHY_ID_PHY11G_1_5		0xD565A401
#घोषणा PHY_ID_PHY22F_1_5		0xD565A411
#घोषणा PHY_ID_PHY11G_VR9_1_1		0xD565A408
#घोषणा PHY_ID_PHY22F_VR9_1_1		0xD565A418
#घोषणा PHY_ID_PHY11G_VR9_1_2		0xD565A409
#घोषणा PHY_ID_PHY22F_VR9_1_2		0xD565A419

अटल पूर्णांक xway_gphy_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;
	u32 ledxh;
	u32 ledxl;

	/* Mask all पूर्णांकerrupts */
	err = phy_ग_लिखो(phydev, XWAY_MDIO_IMASK, 0);
	अगर (err)
		वापस err;

	/* Clear all pending पूर्णांकerrupts */
	phy_पढ़ो(phydev, XWAY_MDIO_ISTAT);

	/* Ensure that पूर्णांकegrated led function is enabled क्रम all leds */
	err = phy_ग_लिखो(phydev, XWAY_MDIO_LED,
			XWAY_MDIO_LED_LED0_EN |
			XWAY_MDIO_LED_LED1_EN |
			XWAY_MDIO_LED_LED2_EN |
			XWAY_MDIO_LED_LED3_EN);
	अगर (err)
		वापस err;

	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LEDCH,
		      XWAY_MMD_LEDCH_NACS_NONE |
		      XWAY_MMD_LEDCH_SBF_F02HZ |
		      XWAY_MMD_LEDCH_FBF_F16HZ);
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LEDCL,
		      XWAY_MMD_LEDCH_CBLINK_NONE |
		      XWAY_MMD_LEDCH_SCAN_NONE);

	/**
	 * In most हालs only one LED is connected to this phy, so
	 * configure them all to स्थिरant on and pulse mode. LED3 is
	 * only available in some packages, leave it in its reset
	 * configuration.
	 */
	ledxh = XWAY_MMD_LEDxH_BLINKF_NONE | XWAY_MMD_LEDxH_CON_LINK10XX;
	ledxl = XWAY_MMD_LEDxL_PULSE_TXACT | XWAY_MMD_LEDxL_PULSE_RXACT |
		XWAY_MMD_LEDxL_BLINKS_NONE;
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED0H, ledxh);
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED0L, ledxl);
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED1H, ledxh);
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED1L, ledxl);
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED2H, ledxh);
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED2L, ledxl);

	वापस 0;
पूर्ण

अटल पूर्णांक xway_gphy14_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg, err;

	/* Advertise as multi-port device, see IEEE802.3-2002 40.5.1.1 */
	/* This is a workaround क्रम an errata in rev < 1.5 devices */
	reg = phy_पढ़ो(phydev, MII_CTRL1000);
	reg |= ADVERTISED_MPD;
	err = phy_ग_लिखो(phydev, MII_CTRL1000, reg);
	अगर (err)
		वापस err;

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक xway_gphy_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg;

	reg = phy_पढ़ो(phydev, XWAY_MDIO_ISTAT);
	वापस (reg < 0) ? reg : 0;
पूर्ण

अटल पूर्णांक xway_gphy_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	u16 mask = 0;
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = xway_gphy_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		mask = XWAY_MDIO_INIT_MASK;
		err = phy_ग_लिखो(phydev, XWAY_MDIO_IMASK, mask);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, XWAY_MDIO_IMASK, mask);
		अगर (err)
			वापस err;

		err = xway_gphy_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t xway_gphy_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, XWAY_MDIO_ISTAT);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & XWAY_MDIO_INIT_MASK))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा phy_driver xway_gphy[] = अणु
	अणु
		.phy_id		= PHY_ID_PHY11G_1_3,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intel XWAY PHY11G (PEF 7071/PEF 7072) v1.3",
		/* PHY_GBIT_FEATURES */
		.config_init	= xway_gphy_config_init,
		.config_aneg	= xway_gphy14_config_aneg,
		.handle_पूर्णांकerrupt = xway_gphy_handle_पूर्णांकerrupt,
		.config_पूर्णांकr	= xway_gphy_config_पूर्णांकr,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण, अणु
		.phy_id		= PHY_ID_PHY22F_1_3,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intel XWAY PHY22F (PEF 7061) v1.3",
		/* PHY_BASIC_FEATURES */
		.config_init	= xway_gphy_config_init,
		.config_aneg	= xway_gphy14_config_aneg,
		.handle_पूर्णांकerrupt = xway_gphy_handle_पूर्णांकerrupt,
		.config_पूर्णांकr	= xway_gphy_config_पूर्णांकr,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण, अणु
		.phy_id		= PHY_ID_PHY11G_1_4,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intel XWAY PHY11G (PEF 7071/PEF 7072) v1.4",
		/* PHY_GBIT_FEATURES */
		.config_init	= xway_gphy_config_init,
		.config_aneg	= xway_gphy14_config_aneg,
		.handle_पूर्णांकerrupt = xway_gphy_handle_पूर्णांकerrupt,
		.config_पूर्णांकr	= xway_gphy_config_पूर्णांकr,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण, अणु
		.phy_id		= PHY_ID_PHY22F_1_4,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intel XWAY PHY22F (PEF 7061) v1.4",
		/* PHY_BASIC_FEATURES */
		.config_init	= xway_gphy_config_init,
		.config_aneg	= xway_gphy14_config_aneg,
		.handle_पूर्णांकerrupt = xway_gphy_handle_पूर्णांकerrupt,
		.config_पूर्णांकr	= xway_gphy_config_पूर्णांकr,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण, अणु
		.phy_id		= PHY_ID_PHY11G_1_5,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intel XWAY PHY11G (PEF 7071/PEF 7072) v1.5 / v1.6",
		/* PHY_GBIT_FEATURES */
		.config_init	= xway_gphy_config_init,
		.handle_पूर्णांकerrupt = xway_gphy_handle_पूर्णांकerrupt,
		.config_पूर्णांकr	= xway_gphy_config_पूर्णांकr,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण, अणु
		.phy_id		= PHY_ID_PHY22F_1_5,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intel XWAY PHY22F (PEF 7061) v1.5 / v1.6",
		/* PHY_BASIC_FEATURES */
		.config_init	= xway_gphy_config_init,
		.handle_पूर्णांकerrupt = xway_gphy_handle_पूर्णांकerrupt,
		.config_पूर्णांकr	= xway_gphy_config_पूर्णांकr,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण, अणु
		.phy_id		= PHY_ID_PHY11G_VR9_1_1,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intel XWAY PHY11G (xRX v1.1 integrated)",
		/* PHY_GBIT_FEATURES */
		.config_init	= xway_gphy_config_init,
		.handle_पूर्णांकerrupt = xway_gphy_handle_पूर्णांकerrupt,
		.config_पूर्णांकr	= xway_gphy_config_पूर्णांकr,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण, अणु
		.phy_id		= PHY_ID_PHY22F_VR9_1_1,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intel XWAY PHY22F (xRX v1.1 integrated)",
		/* PHY_BASIC_FEATURES */
		.config_init	= xway_gphy_config_init,
		.handle_पूर्णांकerrupt = xway_gphy_handle_पूर्णांकerrupt,
		.config_पूर्णांकr	= xway_gphy_config_पूर्णांकr,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण, अणु
		.phy_id		= PHY_ID_PHY11G_VR9_1_2,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intel XWAY PHY11G (xRX v1.2 integrated)",
		/* PHY_GBIT_FEATURES */
		.config_init	= xway_gphy_config_init,
		.handle_पूर्णांकerrupt = xway_gphy_handle_पूर्णांकerrupt,
		.config_पूर्णांकr	= xway_gphy_config_पूर्णांकr,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण, अणु
		.phy_id		= PHY_ID_PHY22F_VR9_1_2,
		.phy_id_mask	= 0xffffffff,
		.name		= "Intel XWAY PHY22F (xRX v1.2 integrated)",
		/* PHY_BASIC_FEATURES */
		.config_init	= xway_gphy_config_init,
		.handle_पूर्णांकerrupt = xway_gphy_handle_पूर्णांकerrupt,
		.config_पूर्णांकr	= xway_gphy_config_पूर्णांकr,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण,
पूर्ण;
module_phy_driver(xway_gphy);

अटल काष्ठा mdio_device_id __maybe_unused xway_gphy_tbl[] = अणु
	अणु PHY_ID_PHY11G_1_3, 0xffffffff पूर्ण,
	अणु PHY_ID_PHY22F_1_3, 0xffffffff पूर्ण,
	अणु PHY_ID_PHY11G_1_4, 0xffffffff पूर्ण,
	अणु PHY_ID_PHY22F_1_4, 0xffffffff पूर्ण,
	अणु PHY_ID_PHY11G_1_5, 0xffffffff पूर्ण,
	अणु PHY_ID_PHY22F_1_5, 0xffffffff पूर्ण,
	अणु PHY_ID_PHY11G_VR9_1_1, 0xffffffff पूर्ण,
	अणु PHY_ID_PHY22F_VR9_1_1, 0xffffffff पूर्ण,
	अणु PHY_ID_PHY11G_VR9_1_2, 0xffffffff पूर्ण,
	अणु PHY_ID_PHY22F_VR9_1_2, 0xffffffff पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mdio, xway_gphy_tbl);

MODULE_DESCRIPTION("Intel XWAY PHY driver");
MODULE_LICENSE("GPL");
