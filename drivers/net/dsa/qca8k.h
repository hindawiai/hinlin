<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2009 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2011-2012 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __QCA8K_H
#घोषणा __QCA8K_H

#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/gpपन.स>

#घोषणा QCA8K_NUM_PORTS					7
#घोषणा QCA8K_MAX_MTU					9000

#घोषणा PHY_ID_QCA8337					0x004dd036
#घोषणा QCA8K_ID_QCA8337				0x13

#घोषणा QCA8K_NUM_FDB_RECORDS				2048

#घोषणा QCA8K_CPU_PORT					0

#घोषणा QCA8K_PORT_VID_DEF				1

/* Global control रेजिस्टरs */
#घोषणा QCA8K_REG_MASK_CTRL				0x000
#घोषणा   QCA8K_MASK_CTRL_ID_M				0xff
#घोषणा   QCA8K_MASK_CTRL_ID_S				8
#घोषणा QCA8K_REG_PORT0_PAD_CTRL			0x004
#घोषणा QCA8K_REG_PORT5_PAD_CTRL			0x008
#घोषणा QCA8K_REG_PORT6_PAD_CTRL			0x00c
#घोषणा   QCA8K_PORT_PAD_RGMII_EN			BIT(26)
#घोषणा   QCA8K_PORT_PAD_RGMII_TX_DELAY(x)		\
						((0x8 + (x & 0x3)) << 22)
#घोषणा   QCA8K_PORT_PAD_RGMII_RX_DELAY(x)		\
						((0x10 + (x & 0x3)) << 20)
#घोषणा   QCA8K_MAX_DELAY				3
#घोषणा   QCA8K_PORT_PAD_RGMII_RX_DELAY_EN		BIT(24)
#घोषणा   QCA8K_PORT_PAD_SGMII_EN			BIT(7)
#घोषणा QCA8K_REG_PWS					0x010
#घोषणा   QCA8K_PWS_SERDES_AEN_DIS			BIT(7)
#घोषणा QCA8K_REG_MODULE_EN				0x030
#घोषणा   QCA8K_MODULE_EN_MIB				BIT(0)
#घोषणा QCA8K_REG_MIB					0x034
#घोषणा   QCA8K_MIB_FLUSH				BIT(24)
#घोषणा   QCA8K_MIB_CPU_KEEP				BIT(20)
#घोषणा   QCA8K_MIB_BUSY				BIT(17)
#घोषणा QCA8K_MDIO_MASTER_CTRL				0x3c
#घोषणा   QCA8K_MDIO_MASTER_BUSY			BIT(31)
#घोषणा   QCA8K_MDIO_MASTER_EN				BIT(30)
#घोषणा   QCA8K_MDIO_MASTER_READ			BIT(27)
#घोषणा   QCA8K_MDIO_MASTER_WRITE			0
#घोषणा   QCA8K_MDIO_MASTER_SUP_PRE			BIT(26)
#घोषणा   QCA8K_MDIO_MASTER_PHY_ADDR(x)			((x) << 21)
#घोषणा   QCA8K_MDIO_MASTER_REG_ADDR(x)			((x) << 16)
#घोषणा   QCA8K_MDIO_MASTER_DATA(x)			(x)
#घोषणा   QCA8K_MDIO_MASTER_DATA_MASK			GENMASK(15, 0)
#घोषणा   QCA8K_MDIO_MASTER_MAX_PORTS			5
#घोषणा   QCA8K_MDIO_MASTER_MAX_REG			32
#घोषणा QCA8K_GOL_MAC_ADDR0				0x60
#घोषणा QCA8K_GOL_MAC_ADDR1				0x64
#घोषणा QCA8K_MAX_FRAME_SIZE				0x78
#घोषणा QCA8K_REG_PORT_STATUS(_i)			(0x07c + (_i) * 4)
#घोषणा   QCA8K_PORT_STATUS_SPEED			GENMASK(1, 0)
#घोषणा   QCA8K_PORT_STATUS_SPEED_10			0
#घोषणा   QCA8K_PORT_STATUS_SPEED_100			0x1
#घोषणा   QCA8K_PORT_STATUS_SPEED_1000			0x2
#घोषणा   QCA8K_PORT_STATUS_TXMAC			BIT(2)
#घोषणा   QCA8K_PORT_STATUS_RXMAC			BIT(3)
#घोषणा   QCA8K_PORT_STATUS_TXFLOW			BIT(4)
#घोषणा   QCA8K_PORT_STATUS_RXFLOW			BIT(5)
#घोषणा   QCA8K_PORT_STATUS_DUPLEX			BIT(6)
#घोषणा   QCA8K_PORT_STATUS_LINK_UP			BIT(8)
#घोषणा   QCA8K_PORT_STATUS_LINK_AUTO			BIT(9)
#घोषणा   QCA8K_PORT_STATUS_LINK_PAUSE			BIT(10)
#घोषणा   QCA8K_PORT_STATUS_FLOW_AUTO			BIT(12)
#घोषणा QCA8K_REG_PORT_HDR_CTRL(_i)			(0x9c + (_i * 4))
#घोषणा   QCA8K_PORT_HDR_CTRL_RX_MASK			GENMASK(3, 2)
#घोषणा   QCA8K_PORT_HDR_CTRL_RX_S			2
#घोषणा   QCA8K_PORT_HDR_CTRL_TX_MASK			GENMASK(1, 0)
#घोषणा   QCA8K_PORT_HDR_CTRL_TX_S			0
#घोषणा   QCA8K_PORT_HDR_CTRL_ALL			2
#घोषणा   QCA8K_PORT_HDR_CTRL_MGMT			1
#घोषणा   QCA8K_PORT_HDR_CTRL_NONE			0
#घोषणा QCA8K_REG_SGMII_CTRL				0x0e0
#घोषणा   QCA8K_SGMII_EN_PLL				BIT(1)
#घोषणा   QCA8K_SGMII_EN_RX				BIT(2)
#घोषणा   QCA8K_SGMII_EN_TX				BIT(3)
#घोषणा   QCA8K_SGMII_EN_SD				BIT(4)
#घोषणा   QCA8K_SGMII_CLK125M_DELAY			BIT(7)
#घोषणा   QCA8K_SGMII_MODE_CTRL_MASK			(BIT(22) | BIT(23))
#घोषणा   QCA8K_SGMII_MODE_CTRL_BASEX			(0 << 22)
#घोषणा   QCA8K_SGMII_MODE_CTRL_PHY			(1 << 22)
#घोषणा   QCA8K_SGMII_MODE_CTRL_MAC			(2 << 22)

/* EEE control रेजिस्टरs */
#घोषणा QCA8K_REG_EEE_CTRL				0x100
#घोषणा  QCA8K_REG_EEE_CTRL_LPI_EN(_i)			((_i + 1) * 2)

/* ACL रेजिस्टरs */
#घोषणा QCA8K_REG_PORT_VLAN_CTRL0(_i)			(0x420 + (_i * 8))
#घोषणा   QCA8K_PORT_VLAN_CVID(x)			(x << 16)
#घोषणा   QCA8K_PORT_VLAN_SVID(x)			x
#घोषणा QCA8K_REG_PORT_VLAN_CTRL1(_i)			(0x424 + (_i * 8))
#घोषणा QCA8K_REG_IPV4_PRI_BASE_ADDR			0x470
#घोषणा QCA8K_REG_IPV4_PRI_ADDR_MASK			0x474

/* Lookup रेजिस्टरs */
#घोषणा QCA8K_REG_ATU_DATA0				0x600
#घोषणा   QCA8K_ATU_ADDR2_S				24
#घोषणा   QCA8K_ATU_ADDR3_S				16
#घोषणा   QCA8K_ATU_ADDR4_S				8
#घोषणा QCA8K_REG_ATU_DATA1				0x604
#घोषणा   QCA8K_ATU_PORT_M				0x7f
#घोषणा   QCA8K_ATU_PORT_S				16
#घोषणा   QCA8K_ATU_ADDR0_S				8
#घोषणा QCA8K_REG_ATU_DATA2				0x608
#घोषणा   QCA8K_ATU_VID_M				0xfff
#घोषणा   QCA8K_ATU_VID_S				8
#घोषणा   QCA8K_ATU_STATUS_M				0xf
#घोषणा   QCA8K_ATU_STATUS_STATIC			0xf
#घोषणा QCA8K_REG_ATU_FUNC				0x60c
#घोषणा   QCA8K_ATU_FUNC_BUSY				BIT(31)
#घोषणा   QCA8K_ATU_FUNC_PORT_EN			BIT(14)
#घोषणा   QCA8K_ATU_FUNC_MULTI_EN			BIT(13)
#घोषणा   QCA8K_ATU_FUNC_FULL				BIT(12)
#घोषणा   QCA8K_ATU_FUNC_PORT_M				0xf
#घोषणा   QCA8K_ATU_FUNC_PORT_S				8
#घोषणा QCA8K_REG_VTU_FUNC0				0x610
#घोषणा   QCA8K_VTU_FUNC0_VALID				BIT(20)
#घोषणा   QCA8K_VTU_FUNC0_IVL_EN			BIT(19)
#घोषणा   QCA8K_VTU_FUNC0_EG_MODE_S(_i)			(4 + (_i) * 2)
#घोषणा   QCA8K_VTU_FUNC0_EG_MODE_MASK			3
#घोषणा   QCA8K_VTU_FUNC0_EG_MODE_UNMOD			0
#घोषणा   QCA8K_VTU_FUNC0_EG_MODE_UNTAG			1
#घोषणा   QCA8K_VTU_FUNC0_EG_MODE_TAG			2
#घोषणा   QCA8K_VTU_FUNC0_EG_MODE_NOT			3
#घोषणा QCA8K_REG_VTU_FUNC1				0x614
#घोषणा   QCA8K_VTU_FUNC1_BUSY				BIT(31)
#घोषणा   QCA8K_VTU_FUNC1_VID_S				16
#घोषणा   QCA8K_VTU_FUNC1_FULL				BIT(4)
#घोषणा QCA8K_REG_GLOBAL_FW_CTRL0			0x620
#घोषणा   QCA8K_GLOBAL_FW_CTRL0_CPU_PORT_EN		BIT(10)
#घोषणा QCA8K_REG_GLOBAL_FW_CTRL1			0x624
#घोषणा   QCA8K_GLOBAL_FW_CTRL1_IGMP_DP_S		24
#घोषणा   QCA8K_GLOBAL_FW_CTRL1_BC_DP_S			16
#घोषणा   QCA8K_GLOBAL_FW_CTRL1_MC_DP_S			8
#घोषणा   QCA8K_GLOBAL_FW_CTRL1_UC_DP_S			0
#घोषणा QCA8K_PORT_LOOKUP_CTRL(_i)			(0x660 + (_i) * 0xc)
#घोषणा   QCA8K_PORT_LOOKUP_MEMBER			GENMASK(6, 0)
#घोषणा   QCA8K_PORT_LOOKUP_VLAN_MODE			GENMASK(9, 8)
#घोषणा   QCA8K_PORT_LOOKUP_VLAN_MODE_NONE		(0 << 8)
#घोषणा   QCA8K_PORT_LOOKUP_VLAN_MODE_FALLBACK		(1 << 8)
#घोषणा   QCA8K_PORT_LOOKUP_VLAN_MODE_CHECK		(2 << 8)
#घोषणा   QCA8K_PORT_LOOKUP_VLAN_MODE_SECURE		(3 << 8)
#घोषणा   QCA8K_PORT_LOOKUP_STATE_MASK			GENMASK(18, 16)
#घोषणा   QCA8K_PORT_LOOKUP_STATE_DISABLED		(0 << 16)
#घोषणा   QCA8K_PORT_LOOKUP_STATE_BLOCKING		(1 << 16)
#घोषणा   QCA8K_PORT_LOOKUP_STATE_LISTENING		(2 << 16)
#घोषणा   QCA8K_PORT_LOOKUP_STATE_LEARNING		(3 << 16)
#घोषणा   QCA8K_PORT_LOOKUP_STATE_FORWARD		(4 << 16)
#घोषणा   QCA8K_PORT_LOOKUP_STATE			GENMASK(18, 16)
#घोषणा   QCA8K_PORT_LOOKUP_LEARN			BIT(20)

/* Pkt edit रेजिस्टरs */
#घोषणा QCA8K_EGRESS_VLAN(x)				(0x0c70 + (4 * (x / 2)))

/* L3 रेजिस्टरs */
#घोषणा QCA8K_HROUTER_CONTROL				0xe00
#घोषणा   QCA8K_HROUTER_CONTROL_GLB_LOCKTIME_M		GENMASK(17, 16)
#घोषणा   QCA8K_HROUTER_CONTROL_GLB_LOCKTIME_S		16
#घोषणा   QCA8K_HROUTER_CONTROL_ARP_AGE_MODE		1
#घोषणा QCA8K_HROUTER_PBASED_CONTROL1			0xe08
#घोषणा QCA8K_HROUTER_PBASED_CONTROL2			0xe0c
#घोषणा QCA8K_HNAT_CONTROL				0xe38

/* MIB रेजिस्टरs */
#घोषणा QCA8K_PORT_MIB_COUNTER(_i)			(0x1000 + (_i) * 0x100)

/* QCA specअगरic MII रेजिस्टरs */
#घोषणा MII_ATH_MMD_ADDR				0x0d
#घोषणा MII_ATH_MMD_DATA				0x0e

क्रमागत अणु
	QCA8K_PORT_SPEED_10M = 0,
	QCA8K_PORT_SPEED_100M = 1,
	QCA8K_PORT_SPEED_1000M = 2,
	QCA8K_PORT_SPEED_ERR = 3,
पूर्ण;

क्रमागत qca8k_fdb_cmd अणु
	QCA8K_FDB_FLUSH	= 1,
	QCA8K_FDB_LOAD = 2,
	QCA8K_FDB_PURGE = 3,
	QCA8K_FDB_NEXT = 6,
	QCA8K_FDB_SEARCH = 7,
पूर्ण;

क्रमागत qca8k_vlan_cmd अणु
	QCA8K_VLAN_FLUSH = 1,
	QCA8K_VLAN_LOAD = 2,
	QCA8K_VLAN_PURGE = 3,
	QCA8K_VLAN_REMOVE_PORT = 4,
	QCA8K_VLAN_NEXT = 5,
	QCA8K_VLAN_READ = 6,
पूर्ण;

काष्ठा ar8xxx_port_status अणु
	पूर्णांक enabled;
पूर्ण;

काष्ठा qca8k_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा mii_bus *bus;
	काष्ठा ar8xxx_port_status port_sts[QCA8K_NUM_PORTS];
	काष्ठा dsa_चयन *ds;
	काष्ठा mutex reg_mutex;
	काष्ठा device *dev;
	काष्ठा dsa_चयन_ops ops;
	काष्ठा gpio_desc *reset_gpio;
	अचिन्हित पूर्णांक port_mtu[QCA8K_NUM_PORTS];
पूर्ण;

काष्ठा qca8k_mib_desc अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक offset;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा qca8k_fdb अणु
	u16 vid;
	u8 port_mask;
	u8 aging;
	u8 mac[6];
पूर्ण;

#पूर्ण_अगर /* __QCA8K_H */
