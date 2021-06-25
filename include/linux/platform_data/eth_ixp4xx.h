<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PLATFORM_DATA_ETH_IXP4XX
#घोषणा __PLATFORM_DATA_ETH_IXP4XX

#समावेश <linux/types.h>

#घोषणा IXP4XX_ETH_NPEA		0x00
#घोषणा IXP4XX_ETH_NPEB		0x10
#घोषणा IXP4XX_ETH_NPEC		0x20

/* Inक्रमmation about built-in Ethernet MAC पूर्णांकerfaces */
काष्ठा eth_plat_info अणु
	u8 phy;		/* MII PHY ID, 0 - 31 */
	u8 rxq;		/* configurable, currently 0 - 31 only */
	u8 txपढ़ोyq;
	u8 hwaddr[6];
	u8 npe;		/* NPE instance used by this पूर्णांकerface */
	bool has_mdio;	/* If this instance has an MDIO bus */
पूर्ण;

#पूर्ण_अगर
