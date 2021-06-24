<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SUNGEM_PHY_H__
#घोषणा __SUNGEM_PHY_H__

काष्ठा mii_phy;

/* Operations supported by any kind of PHY */
काष्ठा mii_phy_ops
अणु
	पूर्णांक		(*init)(काष्ठा mii_phy *phy);
	पूर्णांक		(*suspend)(काष्ठा mii_phy *phy);
	पूर्णांक		(*setup_aneg)(काष्ठा mii_phy *phy, u32 advertise);
	पूर्णांक		(*setup_क्रमced)(काष्ठा mii_phy *phy, पूर्णांक speed, पूर्णांक fd);
	पूर्णांक		(*poll_link)(काष्ठा mii_phy *phy);
	पूर्णांक		(*पढ़ो_link)(काष्ठा mii_phy *phy);
	पूर्णांक		(*enable_fiber)(काष्ठा mii_phy *phy, पूर्णांक स्वतःneg);
पूर्ण;

/* Structure used to अटलally define an mii/gii based PHY */
काष्ठा mii_phy_def
अणु
	u32				phy_id;		/* Concatenated ID1 << 16 | ID2 */
	u32				phy_id_mask;	/* Signअगरicant bits */
	u32				features;	/* Ethtool SUPPORTED_* defines */
	पूर्णांक				magic_aneg;	/* Autoneg करोes all speed test क्रम us */
	स्थिर अक्षर*			name;
	स्थिर काष्ठा mii_phy_ops*	ops;
पूर्ण;

क्रमागत अणु
	BCM54XX_COPPER,
	BCM54XX_FIBER,
	BCM54XX_GBIC,
	BCM54XX_SGMII,
	BCM54XX_UNKNOWN,
पूर्ण;

/* An instance of a PHY, partially borrowed from mii_अगर_info */
काष्ठा mii_phy
अणु
	काष्ठा mii_phy_def*	def;
	u32			advertising;
	पूर्णांक			mii_id;

	/* 1: स्वतःneg enabled, 0: disabled */
	पूर्णांक			स्वतःneg;

	/* क्रमced speed & duplex (no स्वतःneg)
	 * partner speed & duplex & छोड़ो (स्वतःneg)
	 */
	पूर्णांक			speed;
	पूर्णांक			duplex;
	पूर्णांक			छोड़ो;

	/* Provided by host chip */
	काष्ठा net_device	*dev;
	पूर्णांक (*mdio_पढ़ो) (काष्ठा net_device *dev, पूर्णांक mii_id, पूर्णांक reg);
	व्योम (*mdio_ग_लिखो) (काष्ठा net_device *dev, पूर्णांक mii_id, पूर्णांक reg, पूर्णांक val);
	व्योम			*platक्रमm_data;
पूर्ण;

/* Pass in a काष्ठा mii_phy with dev, mdio_पढ़ो and mdio_ग_लिखो
 * filled, the reमुख्यing fields will be filled on वापस
 */
बाह्य पूर्णांक sungem_phy_probe(काष्ठा mii_phy *phy, पूर्णांक mii_id);


/* MII definitions missing from mii.h */

#घोषणा BMCR_SPD2	0x0040		/* Gigabit enable (bcm54xx)	*/
#घोषणा LPA_PAUSE	0x0400

/* More PHY रेजिस्टरs (model specअगरic) */

/* MII BCM5201 MULTIPHY पूर्णांकerrupt रेजिस्टर */
#घोषणा MII_BCM5201_INTERRUPT			0x1A
#घोषणा MII_BCM5201_INTERRUPT_INTENABLE		0x4000

#घोषणा MII_BCM5201_AUXMODE2			0x1B
#घोषणा MII_BCM5201_AUXMODE2_LOWPOWER		0x0008

#घोषणा MII_BCM5201_MULTIPHY                    0x1E

/* MII BCM5201 MULTIPHY रेजिस्टर bits */
#घोषणा MII_BCM5201_MULTIPHY_SERIALMODE         0x0002
#घोषणा MII_BCM5201_MULTIPHY_SUPERISOLATE       0x0008

/* MII BCM5221 Additional रेजिस्टरs */
#घोषणा MII_BCM5221_TEST			0x1f
#घोषणा MII_BCM5221_TEST_ENABLE_SHADOWS		0x0080
#घोषणा MII_BCM5221_SHDOW_AUX_STAT2		0x1b
#घोषणा MII_BCM5221_SHDOW_AUX_STAT2_APD		0x0020
#घोषणा MII_BCM5221_SHDOW_AUX_MODE4		0x1a
#घोषणा MII_BCM5221_SHDOW_AUX_MODE4_IDDQMODE	0x0001
#घोषणा MII_BCM5221_SHDOW_AUX_MODE4_CLKLOPWR	0x0004

/* MII BCM5241 Additional रेजिस्टरs */
#घोषणा MII_BCM5241_SHDOW_AUX_MODE4_STANDBYPWR	0x0008

/* MII BCM5400 1000-BASET Control रेजिस्टर */
#घोषणा MII_BCM5400_GB_CONTROL			0x09
#घोषणा MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP	0x0200

/* MII BCM5400 AUXCONTROL रेजिस्टर */
#घोषणा MII_BCM5400_AUXCONTROL                  0x18
#घोषणा MII_BCM5400_AUXCONTROL_PWR10BASET       0x0004

/* MII BCM5400 AUXSTATUS रेजिस्टर */
#घोषणा MII_BCM5400_AUXSTATUS                   0x19
#घोषणा MII_BCM5400_AUXSTATUS_LINKMODE_MASK     0x0700
#घोषणा MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT    8

/* 1000BT control (Marvell & BCM54xx at least) */
#घोषणा MII_1000BASETCONTROL			0x09
#घोषणा MII_1000BASETCONTROL_FULLDUPLEXCAP	0x0200
#घोषणा MII_1000BASETCONTROL_HALFDUPLEXCAP	0x0100

/* Marvell 88E1011 PHY control */
#घोषणा MII_M1011_PHY_SPEC_CONTROL		0x10
#घोषणा MII_M1011_PHY_SPEC_CONTROL_MANUAL_MDIX	0x20
#घोषणा MII_M1011_PHY_SPEC_CONTROL_AUTO_MDIX	0x40

/* Marvell 88E1011 PHY status */
#घोषणा MII_M1011_PHY_SPEC_STATUS		0x11
#घोषणा MII_M1011_PHY_SPEC_STATUS_1000		0x8000
#घोषणा MII_M1011_PHY_SPEC_STATUS_100		0x4000
#घोषणा MII_M1011_PHY_SPEC_STATUS_SPD_MASK	0xc000
#घोषणा MII_M1011_PHY_SPEC_STATUS_FULLDUPLEX	0x2000
#घोषणा MII_M1011_PHY_SPEC_STATUS_RESOLVED	0x0800
#घोषणा MII_M1011_PHY_SPEC_STATUS_TX_PAUSE	0x0008
#घोषणा MII_M1011_PHY_SPEC_STATUS_RX_PAUSE	0x0004

#पूर्ण_अगर /* __SUNGEM_PHY_H__ */
