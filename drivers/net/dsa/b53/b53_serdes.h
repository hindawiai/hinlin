<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause */
/*
 * Northstar Plus चयन SerDes/SGMII PHY definitions
 *
 * Copyright (C) 2018 Florian Fainelli <f.fainelli@gmail.com>
 */

#समावेश <linux/phy.h>
#समावेश <linux/types.h>

/* Non-standard page used to access SerDes PHY रेजिस्टरs on NorthStar Plus */
#घोषणा B53_SERDES_PAGE			0x16
#घोषणा B53_SERDES_BLKADDR		0x3e
#घोषणा B53_SERDES_LANE			0x3c

#घोषणा B53_SERDES_ID0			0x20
#घोषणा  SERDES_ID0_MODEL_MASK		0x3f
#घोषणा  SERDES_ID0_REV_NUM_SHIFT	11
#घोषणा  SERDES_ID0_REV_NUM_MASK	0x7
#घोषणा  SERDES_ID0_REV_LETTER_SHIFT	14

#घोषणा B53_SERDES_MII_REG(x)		(0x20 + (x) * 2)
#घोषणा B53_SERDES_DIGITAL_CONTROL(x)	(0x1e + (x) * 2)
#घोषणा B53_SERDES_DIGITAL_STATUS	0x28

/* SERDES_DIGITAL_CONTROL1 */
#घोषणा  FIBER_MODE_1000X		BIT(0)
#घोषणा  TBI_INTERFACE			BIT(1)
#घोषणा  SIGNAL_DETECT_EN		BIT(2)
#घोषणा  INVERT_SIGNAL_DETECT		BIT(3)
#घोषणा  AUTODET_EN			BIT(4)
#घोषणा  SGMII_MASTER_MODE		BIT(5)
#घोषणा  DISABLE_DLL_PWRDOWN		BIT(6)
#घोषणा  CRC_CHECKER_DIS		BIT(7)
#घोषणा  COMMA_DET_EN			BIT(8)
#घोषणा  ZERO_COMMA_DET_EN		BIT(9)
#घोषणा  REMOTE_LOOPBACK		BIT(10)
#घोषणा  SEL_RX_PKTS_FOR_CNTR		BIT(11)
#घोषणा  MASTER_MDIO_PHY_SEL		BIT(13)
#घोषणा  DISABLE_SIGNAL_DETECT_FLT	BIT(14)

/* SERDES_DIGITAL_CONTROL2 */
#घोषणा  EN_PARALLEL_DET		BIT(0)
#घोषणा  DIS_FALSE_LINK			BIT(1)
#घोषणा  FLT_FORCE_LINK			BIT(2)
#घोषणा  EN_AUTONEG_ERR_TIMER		BIT(3)
#घोषणा  DIS_REMOTE_FAULT_SENSING	BIT(4)
#घोषणा  FORCE_XMIT_DATA		BIT(5)
#घोषणा  AUTONEG_FAST_TIMERS		BIT(6)
#घोषणा  DIS_CARRIER_EXTEND		BIT(7)
#घोषणा  DIS_TRRR_GENERATION		BIT(8)
#घोषणा  BYPASS_PCS_RX			BIT(9)
#घोषणा  BYPASS_PCS_TX			BIT(10)
#घोषणा  TEST_CNTR_EN			BIT(11)
#घोषणा  TX_PACKET_SEQ_TEST		BIT(12)
#घोषणा  TX_IDLE_JAM_SEQ_TEST		BIT(13)
#घोषणा  CLR_BER_CNTR			BIT(14)

/* SERDES_DIGITAL_CONTROL3 */
#घोषणा  TX_FIFO_RST			BIT(0)
#घोषणा  FIFO_ELAST_TX_RX_SHIFT		1
#घोषणा  FIFO_ELAST_TX_RX_5K		0
#घोषणा  FIFO_ELAST_TX_RX_10K		1
#घोषणा  FIFO_ELAST_TX_RX_13_5K		2
#घोषणा  FIFO_ELAST_TX_RX_18_5K		3
#घोषणा  BLOCK_TXEN_MODE		BIT(9)
#घोषणा  JAM_FALSE_CARRIER_MODE		BIT(10)
#घोषणा  EXT_PHY_CRS_MODE		BIT(11)
#घोषणा  INVERT_EXT_PHY_CRS		BIT(12)
#घोषणा  DISABLE_TX_CRS			BIT(13)

/* SERDES_DIGITAL_STATUS */
#घोषणा  SGMII_MODE			BIT(0)
#घोषणा  LINK_STATUS			BIT(1)
#घोषणा  DUPLEX_STATUS			BIT(2)
#घोषणा  SPEED_STATUS_SHIFT		3
#घोषणा  SPEED_STATUS_10		0
#घोषणा  SPEED_STATUS_100		1
#घोषणा  SPEED_STATUS_1000		2
#घोषणा  SPEED_STATUS_2500		3
#घोषणा  SPEED_STATUS_MASK		SPEED_STATUS_2500
#घोषणा  PAUSE_RESOLUTION_TX_SIDE	BIT(5)
#घोषणा  PAUSE_RESOLUTION_RX_SIDE	BIT(6)
#घोषणा  LINK_STATUS_CHANGE		BIT(7)
#घोषणा  EARLY_END_EXT_DET		BIT(8)
#घोषणा  CARRIER_EXT_ERR_DET		BIT(9)
#घोषणा  RX_ERR_DET			BIT(10)
#घोषणा  TX_ERR_DET			BIT(11)
#घोषणा  CRC_ERR_DET			BIT(12)
#घोषणा  FALSE_CARRIER_ERR_DET		BIT(13)
#घोषणा  RXFIFO_ERR_DET			BIT(14)
#घोषणा  TXFIFO_ERR_DET			BIT(15)

/* Block offsets */
#घोषणा SERDES_DIGITAL_BLK		0x8300
#घोषणा SERDES_ID0			0x8310
#घोषणा SERDES_MII_BLK			0xffe0
#घोषणा SERDES_XGXSBLK0_BLOCKADDRESS	0xffd0

काष्ठा phylink_link_state;

अटल अंतरभूत u8 b53_serdes_map_lane(काष्ठा b53_device *dev, पूर्णांक port)
अणु
	अगर (!dev->ops->serdes_map_lane)
		वापस B53_INVALID_LANE;

	वापस dev->ops->serdes_map_lane(dev, port);
पूर्ण

पूर्णांक b53_serdes_get_link(काष्ठा b53_device *dev, पूर्णांक port);
पूर्णांक b53_serdes_link_state(काष्ठा b53_device *dev, पूर्णांक port,
			  काष्ठा phylink_link_state *state);
व्योम b53_serdes_config(काष्ठा b53_device *dev, पूर्णांक port, अचिन्हित पूर्णांक mode,
		       स्थिर काष्ठा phylink_link_state *state);
व्योम b53_serdes_an_restart(काष्ठा b53_device *dev, पूर्णांक port);
व्योम b53_serdes_link_set(काष्ठा b53_device *dev, पूर्णांक port, अचिन्हित पूर्णांक mode,
			 phy_पूर्णांकerface_t पूर्णांकerface, bool link_up);
व्योम b53_serdes_phylink_validate(काष्ठा b53_device *dev, पूर्णांक port,
				अचिन्हित दीर्घ *supported,
				काष्ठा phylink_link_state *state);
#अगर IS_ENABLED(CONFIG_B53_SERDES)
पूर्णांक b53_serdes_init(काष्ठा b53_device *dev, पूर्णांक port);
#अन्यथा
अटल अंतरभूत पूर्णांक b53_serdes_init(काष्ठा b53_device *dev, पूर्णांक port)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर
