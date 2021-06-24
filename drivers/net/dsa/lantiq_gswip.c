<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Lantiq / Intel GSWIP चयन driver क्रम VRX200, xRX300 and xRX330 SoCs
 *
 * Copyright (C) 2010 Lantiq Deutschland
 * Copyright (C) 2012 John Crispin <john@phrozen.org>
 * Copyright (C) 2017 - 2019 Hauke Mehrtens <hauke@hauke-m.de>
 *
 * The VLAN and bridge model the GSWIP hardware uses करोes not directly
 * matches the model DSA uses.
 *
 * The hardware has 64 possible table entries क्रम bridges with one VLAN
 * ID, one flow id and a list of ports क्रम each bridge. All entries which
 * match the same flow ID are combined in the mac learning table, they
 * act as one global bridge.
 * The hardware करोes not support VLAN filter on the port, but on the
 * bridge, this driver converts the DSA model to the hardware.
 *
 * The CPU माला_लो all the exception frames which करो not match any क्रमwarding
 * rule and the CPU port is also added to all bridges. This makes it possible
 * to handle all the special हालs easily in software.
 * At the initialization the driver allocates one bridge table entry क्रम
 * each चयन port which is used when the port is used without an
 * explicit bridge. This prevents the frames from being क्रमwarded
 * between all LAN ports by शेष.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/phylink.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <net/dsa.h>
#समावेश <dt-bindings/mips/lantiq_rcu_gphy.h>

#समावेश "lantiq_pce.h"

/* GSWIP MDIO Registers */
#घोषणा GSWIP_MDIO_GLOB			0x00
#घोषणा  GSWIP_MDIO_GLOB_ENABLE		BIT(15)
#घोषणा GSWIP_MDIO_CTRL			0x08
#घोषणा  GSWIP_MDIO_CTRL_BUSY		BIT(12)
#घोषणा  GSWIP_MDIO_CTRL_RD		BIT(11)
#घोषणा  GSWIP_MDIO_CTRL_WR		BIT(10)
#घोषणा  GSWIP_MDIO_CTRL_PHYAD_MASK	0x1f
#घोषणा  GSWIP_MDIO_CTRL_PHYAD_SHIFT	5
#घोषणा  GSWIP_MDIO_CTRL_REGAD_MASK	0x1f
#घोषणा GSWIP_MDIO_READ			0x09
#घोषणा GSWIP_MDIO_WRITE		0x0A
#घोषणा GSWIP_MDIO_MDC_CFG0		0x0B
#घोषणा GSWIP_MDIO_MDC_CFG1		0x0C
#घोषणा GSWIP_MDIO_PHYp(p)		(0x15 - (p))
#घोषणा  GSWIP_MDIO_PHY_LINK_MASK	0x6000
#घोषणा  GSWIP_MDIO_PHY_LINK_AUTO	0x0000
#घोषणा  GSWIP_MDIO_PHY_LINK_DOWN	0x4000
#घोषणा  GSWIP_MDIO_PHY_LINK_UP		0x2000
#घोषणा  GSWIP_MDIO_PHY_SPEED_MASK	0x1800
#घोषणा  GSWIP_MDIO_PHY_SPEED_AUTO	0x1800
#घोषणा  GSWIP_MDIO_PHY_SPEED_M10	0x0000
#घोषणा  GSWIP_MDIO_PHY_SPEED_M100	0x0800
#घोषणा  GSWIP_MDIO_PHY_SPEED_G1	0x1000
#घोषणा  GSWIP_MDIO_PHY_FDUP_MASK	0x0600
#घोषणा  GSWIP_MDIO_PHY_FDUP_AUTO	0x0000
#घोषणा  GSWIP_MDIO_PHY_FDUP_EN		0x0200
#घोषणा  GSWIP_MDIO_PHY_FDUP_DIS	0x0600
#घोषणा  GSWIP_MDIO_PHY_FCONTX_MASK	0x0180
#घोषणा  GSWIP_MDIO_PHY_FCONTX_AUTO	0x0000
#घोषणा  GSWIP_MDIO_PHY_FCONTX_EN	0x0100
#घोषणा  GSWIP_MDIO_PHY_FCONTX_DIS	0x0180
#घोषणा  GSWIP_MDIO_PHY_FCONRX_MASK	0x0060
#घोषणा  GSWIP_MDIO_PHY_FCONRX_AUTO	0x0000
#घोषणा  GSWIP_MDIO_PHY_FCONRX_EN	0x0020
#घोषणा  GSWIP_MDIO_PHY_FCONRX_DIS	0x0060
#घोषणा  GSWIP_MDIO_PHY_ADDR_MASK	0x001f
#घोषणा  GSWIP_MDIO_PHY_MASK		(GSWIP_MDIO_PHY_ADDR_MASK | \
					 GSWIP_MDIO_PHY_FCONRX_MASK | \
					 GSWIP_MDIO_PHY_FCONTX_MASK | \
					 GSWIP_MDIO_PHY_LINK_MASK | \
					 GSWIP_MDIO_PHY_SPEED_MASK | \
					 GSWIP_MDIO_PHY_FDUP_MASK)

/* GSWIP MII Registers */
#घोषणा GSWIP_MII_CFGp(p)		(0x2 * (p))
#घोषणा  GSWIP_MII_CFG_RESET		BIT(15)
#घोषणा  GSWIP_MII_CFG_EN		BIT(14)
#घोषणा  GSWIP_MII_CFG_ISOLATE		BIT(13)
#घोषणा  GSWIP_MII_CFG_LDCLKDIS		BIT(12)
#घोषणा  GSWIP_MII_CFG_RGMII_IBS	BIT(8)
#घोषणा  GSWIP_MII_CFG_RMII_CLK		BIT(7)
#घोषणा  GSWIP_MII_CFG_MODE_MIIP	0x0
#घोषणा  GSWIP_MII_CFG_MODE_MIIM	0x1
#घोषणा  GSWIP_MII_CFG_MODE_RMIIP	0x2
#घोषणा  GSWIP_MII_CFG_MODE_RMIIM	0x3
#घोषणा  GSWIP_MII_CFG_MODE_RGMII	0x4
#घोषणा  GSWIP_MII_CFG_MODE_GMII	0x9
#घोषणा  GSWIP_MII_CFG_MODE_MASK	0xf
#घोषणा  GSWIP_MII_CFG_RATE_M2P5	0x00
#घोषणा  GSWIP_MII_CFG_RATE_M25	0x10
#घोषणा  GSWIP_MII_CFG_RATE_M125	0x20
#घोषणा  GSWIP_MII_CFG_RATE_M50	0x30
#घोषणा  GSWIP_MII_CFG_RATE_AUTO	0x40
#घोषणा  GSWIP_MII_CFG_RATE_MASK	0x70
#घोषणा GSWIP_MII_PCDU0			0x01
#घोषणा GSWIP_MII_PCDU1			0x03
#घोषणा GSWIP_MII_PCDU5			0x05
#घोषणा  GSWIP_MII_PCDU_TXDLY_MASK	GENMASK(2, 0)
#घोषणा  GSWIP_MII_PCDU_RXDLY_MASK	GENMASK(9, 7)

/* GSWIP Core Registers */
#घोषणा GSWIP_SWRES			0x000
#घोषणा  GSWIP_SWRES_R1			BIT(1)	/* GSWIP Software reset */
#घोषणा  GSWIP_SWRES_R0			BIT(0)	/* GSWIP Hardware reset */
#घोषणा GSWIP_VERSION			0x013
#घोषणा  GSWIP_VERSION_REV_SHIFT	0
#घोषणा  GSWIP_VERSION_REV_MASK		GENMASK(7, 0)
#घोषणा  GSWIP_VERSION_MOD_SHIFT	8
#घोषणा  GSWIP_VERSION_MOD_MASK		GENMASK(15, 8)
#घोषणा   GSWIP_VERSION_2_0		0x100
#घोषणा   GSWIP_VERSION_2_1		0x021
#घोषणा   GSWIP_VERSION_2_2		0x122
#घोषणा   GSWIP_VERSION_2_2_ETC		0x022

#घोषणा GSWIP_BM_RAM_VAL(x)		(0x043 - (x))
#घोषणा GSWIP_BM_RAM_ADDR		0x044
#घोषणा GSWIP_BM_RAM_CTRL		0x045
#घोषणा  GSWIP_BM_RAM_CTRL_BAS		BIT(15)
#घोषणा  GSWIP_BM_RAM_CTRL_OPMOD	BIT(5)
#घोषणा  GSWIP_BM_RAM_CTRL_ADDR_MASK	GENMASK(4, 0)
#घोषणा GSWIP_BM_QUEUE_GCTRL		0x04A
#घोषणा  GSWIP_BM_QUEUE_GCTRL_GL_MOD	BIT(10)
/* buffer management Port Configuration Register */
#घोषणा GSWIP_BM_PCFGp(p)		(0x080 + ((p) * 2))
#घोषणा  GSWIP_BM_PCFG_CNTEN		BIT(0)	/* RMON Counter Enable */
#घोषणा  GSWIP_BM_PCFG_IGCNT		BIT(1)	/* Ingres Special Tag RMON count */
/* buffer management Port Control Register */
#घोषणा GSWIP_BM_RMON_CTRLp(p)		(0x81 + ((p) * 2))
#घोषणा  GSWIP_BM_CTRL_RMON_RAM1_RES	BIT(0)	/* Software Reset क्रम RMON RAM 1 */
#घोषणा  GSWIP_BM_CTRL_RMON_RAM2_RES	BIT(1)	/* Software Reset क्रम RMON RAM 2 */

/* PCE */
#घोषणा GSWIP_PCE_TBL_KEY(x)		(0x447 - (x))
#घोषणा GSWIP_PCE_TBL_MASK		0x448
#घोषणा GSWIP_PCE_TBL_VAL(x)		(0x44D - (x))
#घोषणा GSWIP_PCE_TBL_ADDR		0x44E
#घोषणा GSWIP_PCE_TBL_CTRL		0x44F
#घोषणा  GSWIP_PCE_TBL_CTRL_BAS		BIT(15)
#घोषणा  GSWIP_PCE_TBL_CTRL_TYPE	BIT(13)
#घोषणा  GSWIP_PCE_TBL_CTRL_VLD		BIT(12)
#घोषणा  GSWIP_PCE_TBL_CTRL_KEYFORM	BIT(11)
#घोषणा  GSWIP_PCE_TBL_CTRL_GMAP_MASK	GENMASK(10, 7)
#घोषणा  GSWIP_PCE_TBL_CTRL_OPMOD_MASK	GENMASK(6, 5)
#घोषणा  GSWIP_PCE_TBL_CTRL_OPMOD_ADRD	0x00
#घोषणा  GSWIP_PCE_TBL_CTRL_OPMOD_ADWR	0x20
#घोषणा  GSWIP_PCE_TBL_CTRL_OPMOD_KSRD	0x40
#घोषणा  GSWIP_PCE_TBL_CTRL_OPMOD_KSWR	0x60
#घोषणा  GSWIP_PCE_TBL_CTRL_ADDR_MASK	GENMASK(4, 0)
#घोषणा GSWIP_PCE_PMAP1			0x453	/* Monitoring port map */
#घोषणा GSWIP_PCE_PMAP2			0x454	/* Default Multicast port map */
#घोषणा GSWIP_PCE_PMAP3			0x455	/* Default Unknown Unicast port map */
#घोषणा GSWIP_PCE_GCTRL_0		0x456
#घोषणा  GSWIP_PCE_GCTRL_0_MTFL		BIT(0)  /* MAC Table Flushing */
#घोषणा  GSWIP_PCE_GCTRL_0_MC_VALID	BIT(3)
#घोषणा  GSWIP_PCE_GCTRL_0_VLAN		BIT(14) /* VLAN aware Switching */
#घोषणा GSWIP_PCE_GCTRL_1		0x457
#घोषणा  GSWIP_PCE_GCTRL_1_MAC_GLOCK	BIT(2)	/* MAC Address table lock */
#घोषणा  GSWIP_PCE_GCTRL_1_MAC_GLOCK_MOD	BIT(3) /* Mac address table lock क्रमwarding mode */
#घोषणा GSWIP_PCE_PCTRL_0p(p)		(0x480 + ((p) * 0xA))
#घोषणा  GSWIP_PCE_PCTRL_0_TVM		BIT(5)	/* Transparent VLAN mode */
#घोषणा  GSWIP_PCE_PCTRL_0_VREP		BIT(6)	/* VLAN Replace Mode */
#घोषणा  GSWIP_PCE_PCTRL_0_INGRESS	BIT(11)	/* Accept special tag in ingress */
#घोषणा  GSWIP_PCE_PCTRL_0_PSTATE_LISTEN	0x0
#घोषणा  GSWIP_PCE_PCTRL_0_PSTATE_RX		0x1
#घोषणा  GSWIP_PCE_PCTRL_0_PSTATE_TX		0x2
#घोषणा  GSWIP_PCE_PCTRL_0_PSTATE_LEARNING	0x3
#घोषणा  GSWIP_PCE_PCTRL_0_PSTATE_FORWARDING	0x7
#घोषणा  GSWIP_PCE_PCTRL_0_PSTATE_MASK	GENMASK(2, 0)
#घोषणा GSWIP_PCE_VCTRL(p)		(0x485 + ((p) * 0xA))
#घोषणा  GSWIP_PCE_VCTRL_UVR		BIT(0)	/* Unknown VLAN Rule */
#घोषणा  GSWIP_PCE_VCTRL_VIMR		BIT(3)	/* VLAN Ingress Member violation rule */
#घोषणा  GSWIP_PCE_VCTRL_VEMR		BIT(4)	/* VLAN Egress Member violation rule */
#घोषणा  GSWIP_PCE_VCTRL_VSR		BIT(5)	/* VLAN Security */
#घोषणा  GSWIP_PCE_VCTRL_VID0		BIT(6)	/* Priority Tagged Rule */
#घोषणा GSWIP_PCE_DEFPVID(p)		(0x486 + ((p) * 0xA))

#घोषणा GSWIP_MAC_FLEN			0x8C5
#घोषणा GSWIP_MAC_CTRL_0p(p)		(0x903 + ((p) * 0xC))
#घोषणा  GSWIP_MAC_CTRL_0_PADEN		BIT(8)
#घोषणा  GSWIP_MAC_CTRL_0_FCS_EN	BIT(7)
#घोषणा  GSWIP_MAC_CTRL_0_FCON_MASK	0x0070
#घोषणा  GSWIP_MAC_CTRL_0_FCON_AUTO	0x0000
#घोषणा  GSWIP_MAC_CTRL_0_FCON_RX	0x0010
#घोषणा  GSWIP_MAC_CTRL_0_FCON_TX	0x0020
#घोषणा  GSWIP_MAC_CTRL_0_FCON_RXTX	0x0030
#घोषणा  GSWIP_MAC_CTRL_0_FCON_NONE	0x0040
#घोषणा  GSWIP_MAC_CTRL_0_FDUP_MASK	0x000C
#घोषणा  GSWIP_MAC_CTRL_0_FDUP_AUTO	0x0000
#घोषणा  GSWIP_MAC_CTRL_0_FDUP_EN	0x0004
#घोषणा  GSWIP_MAC_CTRL_0_FDUP_DIS	0x000C
#घोषणा  GSWIP_MAC_CTRL_0_GMII_MASK	0x0003
#घोषणा  GSWIP_MAC_CTRL_0_GMII_AUTO	0x0000
#घोषणा  GSWIP_MAC_CTRL_0_GMII_MII	0x0001
#घोषणा  GSWIP_MAC_CTRL_0_GMII_RGMII	0x0002
#घोषणा GSWIP_MAC_CTRL_2p(p)		(0x905 + ((p) * 0xC))
#घोषणा GSWIP_MAC_CTRL_2_MLEN		BIT(3) /* Maximum Untagged Frame Lnegth */

/* Ethernet Switch Fetch DMA Port Control Register */
#घोषणा GSWIP_FDMA_PCTRLp(p)		(0xA80 + ((p) * 0x6))
#घोषणा  GSWIP_FDMA_PCTRL_EN		BIT(0)	/* FDMA Port Enable */
#घोषणा  GSWIP_FDMA_PCTRL_STEN		BIT(1)	/* Special Tag Insertion Enable */
#घोषणा  GSWIP_FDMA_PCTRL_VLANMOD_MASK	GENMASK(4, 3)	/* VLAN Modअगरication Control */
#घोषणा  GSWIP_FDMA_PCTRL_VLANMOD_SHIFT	3	/* VLAN Modअगरication Control */
#घोषणा  GSWIP_FDMA_PCTRL_VLANMOD_DIS	(0x0 << GSWIP_FDMA_PCTRL_VLANMOD_SHIFT)
#घोषणा  GSWIP_FDMA_PCTRL_VLANMOD_PRIO	(0x1 << GSWIP_FDMA_PCTRL_VLANMOD_SHIFT)
#घोषणा  GSWIP_FDMA_PCTRL_VLANMOD_ID	(0x2 << GSWIP_FDMA_PCTRL_VLANMOD_SHIFT)
#घोषणा  GSWIP_FDMA_PCTRL_VLANMOD_BOTH	(0x3 << GSWIP_FDMA_PCTRL_VLANMOD_SHIFT)

/* Ethernet Switch Store DMA Port Control Register */
#घोषणा GSWIP_SDMA_PCTRLp(p)		(0xBC0 + ((p) * 0x6))
#घोषणा  GSWIP_SDMA_PCTRL_EN		BIT(0)	/* SDMA Port Enable */
#घोषणा  GSWIP_SDMA_PCTRL_FCEN		BIT(1)	/* Flow Control Enable */
#घोषणा  GSWIP_SDMA_PCTRL_PAUFWD	BIT(1)	/* Pause Frame Forwarding */

#घोषणा GSWIP_TABLE_ACTIVE_VLAN		0x01
#घोषणा GSWIP_TABLE_VLAN_MAPPING	0x02
#घोषणा GSWIP_TABLE_MAC_BRIDGE		0x0b
#घोषणा  GSWIP_TABLE_MAC_BRIDGE_STATIC	0x01	/* Static not, aging entry */

#घोषणा XRX200_GPHY_FW_ALIGN	(16 * 1024)

काष्ठा gswip_hw_info अणु
	पूर्णांक max_ports;
	पूर्णांक cpu_port;
	स्थिर काष्ठा dsa_चयन_ops *ops;
पूर्ण;

काष्ठा xway_gphy_match_data अणु
	अक्षर *fe_firmware_name;
	अक्षर *ge_firmware_name;
पूर्ण;

काष्ठा gswip_gphy_fw अणु
	काष्ठा clk *clk_gate;
	काष्ठा reset_control *reset;
	u32 fw_addr_offset;
	अक्षर *fw_name;
पूर्ण;

काष्ठा gswip_vlan अणु
	काष्ठा net_device *bridge;
	u16 vid;
	u8 fid;
पूर्ण;

काष्ठा gswip_priv अणु
	__iomem व्योम *gswip;
	__iomem व्योम *mdio;
	__iomem व्योम *mii;
	स्थिर काष्ठा gswip_hw_info *hw_info;
	स्थिर काष्ठा xway_gphy_match_data *gphy_fw_name_cfg;
	काष्ठा dsa_चयन *ds;
	काष्ठा device *dev;
	काष्ठा regmap *rcu_regmap;
	काष्ठा gswip_vlan vlans[64];
	पूर्णांक num_gphy_fw;
	काष्ठा gswip_gphy_fw *gphy_fw;
	u32 port_vlan_filter;
पूर्ण;

काष्ठा gswip_pce_table_entry अणु
	u16 index;      // PCE_TBL_ADDR.ADDR = pData->table_index
	u16 table;      // PCE_TBL_CTRL.ADDR = pData->table
	u16 key[8];
	u16 val[5];
	u16 mask;
	u8 gmap;
	bool type;
	bool valid;
	bool key_mode;
पूर्ण;

काष्ठा gswip_rmon_cnt_desc अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक offset;
	स्थिर अक्षर *name;
पूर्ण;

#घोषणा MIB_DESC(_size, _offset, _name) अणु.size = _size, .offset = _offset, .name = _nameपूर्ण

अटल स्थिर काष्ठा gswip_rmon_cnt_desc gswip_rmon_cnt[] = अणु
	/** Receive Packet Count (only packets that are accepted and not discarded). */
	MIB_DESC(1, 0x1F, "RxGoodPkts"),
	MIB_DESC(1, 0x23, "RxUnicastPkts"),
	MIB_DESC(1, 0x22, "RxMulticastPkts"),
	MIB_DESC(1, 0x21, "RxFCSErrorPkts"),
	MIB_DESC(1, 0x1D, "RxUnderSizeGoodPkts"),
	MIB_DESC(1, 0x1E, "RxUnderSizeErrorPkts"),
	MIB_DESC(1, 0x1B, "RxOversizeGoodPkts"),
	MIB_DESC(1, 0x1C, "RxOversizeErrorPkts"),
	MIB_DESC(1, 0x20, "RxGoodPausePkts"),
	MIB_DESC(1, 0x1A, "RxAlignErrorPkts"),
	MIB_DESC(1, 0x12, "Rx64BytePkts"),
	MIB_DESC(1, 0x13, "Rx127BytePkts"),
	MIB_DESC(1, 0x14, "Rx255BytePkts"),
	MIB_DESC(1, 0x15, "Rx511BytePkts"),
	MIB_DESC(1, 0x16, "Rx1023BytePkts"),
	/** Receive Size 1024-1522 (or more, अगर configured) Packet Count. */
	MIB_DESC(1, 0x17, "RxMaxBytePkts"),
	MIB_DESC(1, 0x18, "RxDroppedPkts"),
	MIB_DESC(1, 0x19, "RxFilteredPkts"),
	MIB_DESC(2, 0x24, "RxGoodBytes"),
	MIB_DESC(2, 0x26, "RxBadBytes"),
	MIB_DESC(1, 0x11, "TxAcmDroppedPkts"),
	MIB_DESC(1, 0x0C, "TxGoodPkts"),
	MIB_DESC(1, 0x06, "TxUnicastPkts"),
	MIB_DESC(1, 0x07, "TxMulticastPkts"),
	MIB_DESC(1, 0x00, "Tx64BytePkts"),
	MIB_DESC(1, 0x01, "Tx127BytePkts"),
	MIB_DESC(1, 0x02, "Tx255BytePkts"),
	MIB_DESC(1, 0x03, "Tx511BytePkts"),
	MIB_DESC(1, 0x04, "Tx1023BytePkts"),
	/** Transmit Size 1024-1522 (or more, अगर configured) Packet Count. */
	MIB_DESC(1, 0x05, "TxMaxBytePkts"),
	MIB_DESC(1, 0x08, "TxSingleCollCount"),
	MIB_DESC(1, 0x09, "TxMultCollCount"),
	MIB_DESC(1, 0x0A, "TxLateCollCount"),
	MIB_DESC(1, 0x0B, "TxExcessCollCount"),
	MIB_DESC(1, 0x0D, "TxPauseCount"),
	MIB_DESC(1, 0x10, "TxDroppedPkts"),
	MIB_DESC(2, 0x0E, "TxGoodBytes"),
पूर्ण;

अटल u32 gswip_चयन_r(काष्ठा gswip_priv *priv, u32 offset)
अणु
	वापस __raw_पढ़ोl(priv->gswip + (offset * 4));
पूर्ण

अटल व्योम gswip_चयन_w(काष्ठा gswip_priv *priv, u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, priv->gswip + (offset * 4));
पूर्ण

अटल व्योम gswip_चयन_mask(काष्ठा gswip_priv *priv, u32 clear, u32 set,
			      u32 offset)
अणु
	u32 val = gswip_चयन_r(priv, offset);

	val &= ~(clear);
	val |= set;
	gswip_चयन_w(priv, val, offset);
पूर्ण

अटल u32 gswip_चयन_r_समयout(काष्ठा gswip_priv *priv, u32 offset,
				  u32 cleared)
अणु
	u32 val;

	वापस पढ़ोx_poll_समयout(__raw_पढ़ोl, priv->gswip + (offset * 4), val,
				  (val & cleared) == 0, 20, 50000);
पूर्ण

अटल u32 gswip_mdio_r(काष्ठा gswip_priv *priv, u32 offset)
अणु
	वापस __raw_पढ़ोl(priv->mdio + (offset * 4));
पूर्ण

अटल व्योम gswip_mdio_w(काष्ठा gswip_priv *priv, u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, priv->mdio + (offset * 4));
पूर्ण

अटल व्योम gswip_mdio_mask(काष्ठा gswip_priv *priv, u32 clear, u32 set,
			    u32 offset)
अणु
	u32 val = gswip_mdio_r(priv, offset);

	val &= ~(clear);
	val |= set;
	gswip_mdio_w(priv, val, offset);
पूर्ण

अटल u32 gswip_mii_r(काष्ठा gswip_priv *priv, u32 offset)
अणु
	वापस __raw_पढ़ोl(priv->mii + (offset * 4));
पूर्ण

अटल व्योम gswip_mii_w(काष्ठा gswip_priv *priv, u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, priv->mii + (offset * 4));
पूर्ण

अटल व्योम gswip_mii_mask(काष्ठा gswip_priv *priv, u32 clear, u32 set,
			   u32 offset)
अणु
	u32 val = gswip_mii_r(priv, offset);

	val &= ~(clear);
	val |= set;
	gswip_mii_w(priv, val, offset);
पूर्ण

अटल व्योम gswip_mii_mask_cfg(काष्ठा gswip_priv *priv, u32 clear, u32 set,
			       पूर्णांक port)
अणु
	/* There's no MII_CFG रेजिस्टर क्रम the CPU port */
	अगर (!dsa_is_cpu_port(priv->ds, port))
		gswip_mii_mask(priv, clear, set, GSWIP_MII_CFGp(port));
पूर्ण

अटल व्योम gswip_mii_mask_pcdu(काष्ठा gswip_priv *priv, u32 clear, u32 set,
				पूर्णांक port)
अणु
	चयन (port) अणु
	हाल 0:
		gswip_mii_mask(priv, clear, set, GSWIP_MII_PCDU0);
		अवरोध;
	हाल 1:
		gswip_mii_mask(priv, clear, set, GSWIP_MII_PCDU1);
		अवरोध;
	हाल 5:
		gswip_mii_mask(priv, clear, set, GSWIP_MII_PCDU5);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक gswip_mdio_poll(काष्ठा gswip_priv *priv)
अणु
	पूर्णांक cnt = 100;

	जबतक (likely(cnt--)) अणु
		u32 ctrl = gswip_mdio_r(priv, GSWIP_MDIO_CTRL);

		अगर ((ctrl & GSWIP_MDIO_CTRL_BUSY) == 0)
			वापस 0;
		usleep_range(20, 40);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक gswip_mdio_wr(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक reg, u16 val)
अणु
	काष्ठा gswip_priv *priv = bus->priv;
	पूर्णांक err;

	err = gswip_mdio_poll(priv);
	अगर (err) अणु
		dev_err(&bus->dev, "waiting for MDIO bus busy timed out\n");
		वापस err;
	पूर्ण

	gswip_mdio_w(priv, val, GSWIP_MDIO_WRITE);
	gswip_mdio_w(priv, GSWIP_MDIO_CTRL_BUSY | GSWIP_MDIO_CTRL_WR |
		((addr & GSWIP_MDIO_CTRL_PHYAD_MASK) << GSWIP_MDIO_CTRL_PHYAD_SHIFT) |
		(reg & GSWIP_MDIO_CTRL_REGAD_MASK),
		GSWIP_MDIO_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक gswip_mdio_rd(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक reg)
अणु
	काष्ठा gswip_priv *priv = bus->priv;
	पूर्णांक err;

	err = gswip_mdio_poll(priv);
	अगर (err) अणु
		dev_err(&bus->dev, "waiting for MDIO bus busy timed out\n");
		वापस err;
	पूर्ण

	gswip_mdio_w(priv, GSWIP_MDIO_CTRL_BUSY | GSWIP_MDIO_CTRL_RD |
		((addr & GSWIP_MDIO_CTRL_PHYAD_MASK) << GSWIP_MDIO_CTRL_PHYAD_SHIFT) |
		(reg & GSWIP_MDIO_CTRL_REGAD_MASK),
		GSWIP_MDIO_CTRL);

	err = gswip_mdio_poll(priv);
	अगर (err) अणु
		dev_err(&bus->dev, "waiting for MDIO bus busy timed out\n");
		वापस err;
	पूर्ण

	वापस gswip_mdio_r(priv, GSWIP_MDIO_READ);
पूर्ण

अटल पूर्णांक gswip_mdio(काष्ठा gswip_priv *priv, काष्ठा device_node *mdio_np)
अणु
	काष्ठा dsa_चयन *ds = priv->ds;

	ds->slave_mii_bus = devm_mdiobus_alloc(priv->dev);
	अगर (!ds->slave_mii_bus)
		वापस -ENOMEM;

	ds->slave_mii_bus->priv = priv;
	ds->slave_mii_bus->पढ़ो = gswip_mdio_rd;
	ds->slave_mii_bus->ग_लिखो = gswip_mdio_wr;
	ds->slave_mii_bus->name = "lantiq,xrx200-mdio";
	snम_लिखो(ds->slave_mii_bus->id, MII_BUS_ID_SIZE, "%s-mii",
		 dev_name(priv->dev));
	ds->slave_mii_bus->parent = priv->dev;
	ds->slave_mii_bus->phy_mask = ~ds->phys_mii_mask;

	वापस of_mdiobus_रेजिस्टर(ds->slave_mii_bus, mdio_np);
पूर्ण

अटल पूर्णांक gswip_pce_table_entry_पढ़ो(काष्ठा gswip_priv *priv,
				      काष्ठा gswip_pce_table_entry *tbl)
अणु
	पूर्णांक i;
	पूर्णांक err;
	u16 crtl;
	u16 addr_mode = tbl->key_mode ? GSWIP_PCE_TBL_CTRL_OPMOD_KSRD :
					GSWIP_PCE_TBL_CTRL_OPMOD_ADRD;

	err = gswip_चयन_r_समयout(priv, GSWIP_PCE_TBL_CTRL,
				     GSWIP_PCE_TBL_CTRL_BAS);
	अगर (err)
		वापस err;

	gswip_चयन_w(priv, tbl->index, GSWIP_PCE_TBL_ADDR);
	gswip_चयन_mask(priv, GSWIP_PCE_TBL_CTRL_ADDR_MASK |
				GSWIP_PCE_TBL_CTRL_OPMOD_MASK,
			  tbl->table | addr_mode | GSWIP_PCE_TBL_CTRL_BAS,
			  GSWIP_PCE_TBL_CTRL);

	err = gswip_चयन_r_समयout(priv, GSWIP_PCE_TBL_CTRL,
				     GSWIP_PCE_TBL_CTRL_BAS);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(tbl->key); i++)
		tbl->key[i] = gswip_चयन_r(priv, GSWIP_PCE_TBL_KEY(i));

	क्रम (i = 0; i < ARRAY_SIZE(tbl->val); i++)
		tbl->val[i] = gswip_चयन_r(priv, GSWIP_PCE_TBL_VAL(i));

	tbl->mask = gswip_चयन_r(priv, GSWIP_PCE_TBL_MASK);

	crtl = gswip_चयन_r(priv, GSWIP_PCE_TBL_CTRL);

	tbl->type = !!(crtl & GSWIP_PCE_TBL_CTRL_TYPE);
	tbl->valid = !!(crtl & GSWIP_PCE_TBL_CTRL_VLD);
	tbl->gmap = (crtl & GSWIP_PCE_TBL_CTRL_GMAP_MASK) >> 7;

	वापस 0;
पूर्ण

अटल पूर्णांक gswip_pce_table_entry_ग_लिखो(काष्ठा gswip_priv *priv,
				       काष्ठा gswip_pce_table_entry *tbl)
अणु
	पूर्णांक i;
	पूर्णांक err;
	u16 crtl;
	u16 addr_mode = tbl->key_mode ? GSWIP_PCE_TBL_CTRL_OPMOD_KSWR :
					GSWIP_PCE_TBL_CTRL_OPMOD_ADWR;

	err = gswip_चयन_r_समयout(priv, GSWIP_PCE_TBL_CTRL,
				     GSWIP_PCE_TBL_CTRL_BAS);
	अगर (err)
		वापस err;

	gswip_चयन_w(priv, tbl->index, GSWIP_PCE_TBL_ADDR);
	gswip_चयन_mask(priv, GSWIP_PCE_TBL_CTRL_ADDR_MASK |
				GSWIP_PCE_TBL_CTRL_OPMOD_MASK,
			  tbl->table | addr_mode,
			  GSWIP_PCE_TBL_CTRL);

	क्रम (i = 0; i < ARRAY_SIZE(tbl->key); i++)
		gswip_चयन_w(priv, tbl->key[i], GSWIP_PCE_TBL_KEY(i));

	क्रम (i = 0; i < ARRAY_SIZE(tbl->val); i++)
		gswip_चयन_w(priv, tbl->val[i], GSWIP_PCE_TBL_VAL(i));

	gswip_चयन_mask(priv, GSWIP_PCE_TBL_CTRL_ADDR_MASK |
				GSWIP_PCE_TBL_CTRL_OPMOD_MASK,
			  tbl->table | addr_mode,
			  GSWIP_PCE_TBL_CTRL);

	gswip_चयन_w(priv, tbl->mask, GSWIP_PCE_TBL_MASK);

	crtl = gswip_चयन_r(priv, GSWIP_PCE_TBL_CTRL);
	crtl &= ~(GSWIP_PCE_TBL_CTRL_TYPE | GSWIP_PCE_TBL_CTRL_VLD |
		  GSWIP_PCE_TBL_CTRL_GMAP_MASK);
	अगर (tbl->type)
		crtl |= GSWIP_PCE_TBL_CTRL_TYPE;
	अगर (tbl->valid)
		crtl |= GSWIP_PCE_TBL_CTRL_VLD;
	crtl |= (tbl->gmap << 7) & GSWIP_PCE_TBL_CTRL_GMAP_MASK;
	crtl |= GSWIP_PCE_TBL_CTRL_BAS;
	gswip_चयन_w(priv, crtl, GSWIP_PCE_TBL_CTRL);

	वापस gswip_चयन_r_समयout(priv, GSWIP_PCE_TBL_CTRL,
				      GSWIP_PCE_TBL_CTRL_BAS);
पूर्ण

/* Add the LAN port पूर्णांकo a bridge with the CPU port by
 * शेष. This prevents स्वतःmatic क्रमwarding of
 * packages between the LAN ports when no explicit
 * bridge is configured.
 */
अटल पूर्णांक gswip_add_single_port_br(काष्ठा gswip_priv *priv, पूर्णांक port, bool add)
अणु
	काष्ठा gswip_pce_table_entry vlan_active = अणु0,पूर्ण;
	काष्ठा gswip_pce_table_entry vlan_mapping = अणु0,पूर्ण;
	अचिन्हित पूर्णांक cpu_port = priv->hw_info->cpu_port;
	अचिन्हित पूर्णांक max_ports = priv->hw_info->max_ports;
	पूर्णांक err;

	अगर (port >= max_ports) अणु
		dev_err(priv->dev, "single port for %i supported\n", port);
		वापस -EIO;
	पूर्ण

	vlan_active.index = port + 1;
	vlan_active.table = GSWIP_TABLE_ACTIVE_VLAN;
	vlan_active.key[0] = 0; /* vid */
	vlan_active.val[0] = port + 1 /* fid */;
	vlan_active.valid = add;
	err = gswip_pce_table_entry_ग_लिखो(priv, &vlan_active);
	अगर (err) अणु
		dev_err(priv->dev, "failed to write active VLAN: %d\n", err);
		वापस err;
	पूर्ण

	अगर (!add)
		वापस 0;

	vlan_mapping.index = port + 1;
	vlan_mapping.table = GSWIP_TABLE_VLAN_MAPPING;
	vlan_mapping.val[0] = 0 /* vid */;
	vlan_mapping.val[1] = BIT(port) | BIT(cpu_port);
	vlan_mapping.val[2] = 0;
	err = gswip_pce_table_entry_ग_लिखो(priv, &vlan_mapping);
	अगर (err) अणु
		dev_err(priv->dev, "failed to write VLAN mapping: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gswip_port_enable(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा phy_device *phydev)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	पूर्णांक err;

	अगर (!dsa_is_user_port(ds, port))
		वापस 0;

	अगर (!dsa_is_cpu_port(ds, port)) अणु
		err = gswip_add_single_port_br(priv, port, true);
		अगर (err)
			वापस err;
	पूर्ण

	/* RMON Counter Enable क्रम port */
	gswip_चयन_w(priv, GSWIP_BM_PCFG_CNTEN, GSWIP_BM_PCFGp(port));

	/* enable port fetch/store dma & VLAN Modअगरication */
	gswip_चयन_mask(priv, 0, GSWIP_FDMA_PCTRL_EN |
				   GSWIP_FDMA_PCTRL_VLANMOD_BOTH,
			 GSWIP_FDMA_PCTRLp(port));
	gswip_चयन_mask(priv, 0, GSWIP_SDMA_PCTRL_EN,
			  GSWIP_SDMA_PCTRLp(port));

	अगर (!dsa_is_cpu_port(ds, port)) अणु
		u32 mdio_phy = 0;

		अगर (phydev)
			mdio_phy = phydev->mdio.addr & GSWIP_MDIO_PHY_ADDR_MASK;

		gswip_mdio_mask(priv, GSWIP_MDIO_PHY_ADDR_MASK, mdio_phy,
				GSWIP_MDIO_PHYp(port));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gswip_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा gswip_priv *priv = ds->priv;

	अगर (!dsa_is_user_port(ds, port))
		वापस;

	gswip_चयन_mask(priv, GSWIP_FDMA_PCTRL_EN, 0,
			  GSWIP_FDMA_PCTRLp(port));
	gswip_चयन_mask(priv, GSWIP_SDMA_PCTRL_EN, 0,
			  GSWIP_SDMA_PCTRLp(port));
पूर्ण

अटल पूर्णांक gswip_pce_load_microcode(काष्ठा gswip_priv *priv)
अणु
	पूर्णांक i;
	पूर्णांक err;

	gswip_चयन_mask(priv, GSWIP_PCE_TBL_CTRL_ADDR_MASK |
				GSWIP_PCE_TBL_CTRL_OPMOD_MASK,
			  GSWIP_PCE_TBL_CTRL_OPMOD_ADWR, GSWIP_PCE_TBL_CTRL);
	gswip_चयन_w(priv, 0, GSWIP_PCE_TBL_MASK);

	क्रम (i = 0; i < ARRAY_SIZE(gswip_pce_microcode); i++) अणु
		gswip_चयन_w(priv, i, GSWIP_PCE_TBL_ADDR);
		gswip_चयन_w(priv, gswip_pce_microcode[i].val_0,
			       GSWIP_PCE_TBL_VAL(0));
		gswip_चयन_w(priv, gswip_pce_microcode[i].val_1,
			       GSWIP_PCE_TBL_VAL(1));
		gswip_चयन_w(priv, gswip_pce_microcode[i].val_2,
			       GSWIP_PCE_TBL_VAL(2));
		gswip_चयन_w(priv, gswip_pce_microcode[i].val_3,
			       GSWIP_PCE_TBL_VAL(3));

		/* start the table access: */
		gswip_चयन_mask(priv, 0, GSWIP_PCE_TBL_CTRL_BAS,
				  GSWIP_PCE_TBL_CTRL);
		err = gswip_चयन_r_समयout(priv, GSWIP_PCE_TBL_CTRL,
					     GSWIP_PCE_TBL_CTRL_BAS);
		अगर (err)
			वापस err;
	पूर्ण

	/* tell the चयन that the microcode is loaded */
	gswip_चयन_mask(priv, 0, GSWIP_PCE_GCTRL_0_MC_VALID,
			  GSWIP_PCE_GCTRL_0);

	वापस 0;
पूर्ण

अटल पूर्णांक gswip_port_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     bool vlan_filtering,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *bridge = dsa_to_port(ds, port)->bridge_dev;
	काष्ठा gswip_priv *priv = ds->priv;

	/* Do not allow changing the VLAN filtering options जबतक in bridge */
	अगर (bridge && !!(priv->port_vlan_filter & BIT(port)) != vlan_filtering) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Dynamic toggling of vlan_filtering not supported");
		वापस -EIO;
	पूर्ण

	अगर (vlan_filtering) अणु
		/* Use port based VLAN tag */
		gswip_चयन_mask(priv,
				  GSWIP_PCE_VCTRL_VSR,
				  GSWIP_PCE_VCTRL_UVR | GSWIP_PCE_VCTRL_VIMR |
				  GSWIP_PCE_VCTRL_VEMR,
				  GSWIP_PCE_VCTRL(port));
		gswip_चयन_mask(priv, GSWIP_PCE_PCTRL_0_TVM, 0,
				  GSWIP_PCE_PCTRL_0p(port));
	पूर्ण अन्यथा अणु
		/* Use port based VLAN tag */
		gswip_चयन_mask(priv,
				  GSWIP_PCE_VCTRL_UVR | GSWIP_PCE_VCTRL_VIMR |
				  GSWIP_PCE_VCTRL_VEMR,
				  GSWIP_PCE_VCTRL_VSR,
				  GSWIP_PCE_VCTRL(port));
		gswip_चयन_mask(priv, 0, GSWIP_PCE_PCTRL_0_TVM,
				  GSWIP_PCE_PCTRL_0p(port));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gswip_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	अचिन्हित पूर्णांक cpu_port = priv->hw_info->cpu_port;
	पूर्णांक i;
	पूर्णांक err;

	gswip_चयन_w(priv, GSWIP_SWRES_R0, GSWIP_SWRES);
	usleep_range(5000, 10000);
	gswip_चयन_w(priv, 0, GSWIP_SWRES);

	/* disable port fetch/store dma on all ports */
	क्रम (i = 0; i < priv->hw_info->max_ports; i++) अणु
		gswip_port_disable(ds, i);
		gswip_port_vlan_filtering(ds, i, false, शून्य);
	पूर्ण

	/* enable Switch */
	gswip_mdio_mask(priv, 0, GSWIP_MDIO_GLOB_ENABLE, GSWIP_MDIO_GLOB);

	err = gswip_pce_load_microcode(priv);
	अगर (err) अणु
		dev_err(priv->dev, "writing PCE microcode failed, %i", err);
		वापस err;
	पूर्ण

	/* Default unknown Broadcast/Multicast/Unicast port maps */
	gswip_चयन_w(priv, BIT(cpu_port), GSWIP_PCE_PMAP1);
	gswip_चयन_w(priv, BIT(cpu_port), GSWIP_PCE_PMAP2);
	gswip_चयन_w(priv, BIT(cpu_port), GSWIP_PCE_PMAP3);

	/* Deactivate MDIO PHY स्वतः polling. Some PHYs as the AR8030 have an
	 * पूर्णांकeroperability problem with this स्वतः polling mechanism because
	 * their status रेजिस्टरs think that the link is in a dअगरferent state
	 * than it actually is. For the AR8030 it has the BMSR_ESTATEN bit set
	 * as well as ESTATUS_1000_TFULL and ESTATUS_1000_XFULL. This makes the
	 * स्वतः polling state machine consider the link being negotiated with
	 * 1Gbit/s. Since the PHY itself is a Fast Ethernet RMII PHY this leads
	 * to the चयन port being completely dead (RX and TX are both not
	 * working).
	 * Also with various other PHY / port combinations (PHY11G GPHY, PHY22F
	 * GPHY, बाह्यal RGMII PEF7071/7072) any traffic would stop. Someबार
	 * it would work fine क्रम a few minutes to hours and then stop, on
	 * other device it would no traffic could be sent or received at all.
	 * Testing shows that when PHY स्वतः polling is disabled these problems
	 * go away.
	 */
	gswip_mdio_w(priv, 0x0, GSWIP_MDIO_MDC_CFG0);

	/* Configure the MDIO Clock 2.5 MHz */
	gswip_mdio_mask(priv, 0xff, 0x09, GSWIP_MDIO_MDC_CFG1);

	/* Disable the xMII पूर्णांकerface and clear it's isolation bit */
	क्रम (i = 0; i < priv->hw_info->max_ports; i++)
		gswip_mii_mask_cfg(priv,
				   GSWIP_MII_CFG_EN | GSWIP_MII_CFG_ISOLATE,
				   0, i);

	/* enable special tag insertion on cpu port */
	gswip_चयन_mask(priv, 0, GSWIP_FDMA_PCTRL_STEN,
			  GSWIP_FDMA_PCTRLp(cpu_port));

	/* accept special tag in ingress direction */
	gswip_चयन_mask(priv, 0, GSWIP_PCE_PCTRL_0_INGRESS,
			  GSWIP_PCE_PCTRL_0p(cpu_port));

	gswip_चयन_mask(priv, 0, GSWIP_MAC_CTRL_2_MLEN,
			  GSWIP_MAC_CTRL_2p(cpu_port));
	gswip_चयन_w(priv, VLAN_ETH_FRAME_LEN + 8, GSWIP_MAC_FLEN);
	gswip_चयन_mask(priv, 0, GSWIP_BM_QUEUE_GCTRL_GL_MOD,
			  GSWIP_BM_QUEUE_GCTRL);

	/* VLAN aware Switching */
	gswip_चयन_mask(priv, 0, GSWIP_PCE_GCTRL_0_VLAN, GSWIP_PCE_GCTRL_0);

	/* Flush MAC Table */
	gswip_चयन_mask(priv, 0, GSWIP_PCE_GCTRL_0_MTFL, GSWIP_PCE_GCTRL_0);

	err = gswip_चयन_r_समयout(priv, GSWIP_PCE_GCTRL_0,
				     GSWIP_PCE_GCTRL_0_MTFL);
	अगर (err) अणु
		dev_err(priv->dev, "MAC flushing didn't finish\n");
		वापस err;
	पूर्ण

	gswip_port_enable(ds, cpu_port, शून्य);

	ds->configure_vlan_जबतक_not_filtering = false;

	वापस 0;
पूर्ण

अटल क्रमागत dsa_tag_protocol gswip_get_tag_protocol(काष्ठा dsa_चयन *ds,
						    पूर्णांक port,
						    क्रमागत dsa_tag_protocol mp)
अणु
	वापस DSA_TAG_PROTO_GSWIP;
पूर्ण

अटल पूर्णांक gswip_vlan_active_create(काष्ठा gswip_priv *priv,
				    काष्ठा net_device *bridge,
				    पूर्णांक fid, u16 vid)
अणु
	काष्ठा gswip_pce_table_entry vlan_active = अणु0,पूर्ण;
	अचिन्हित पूर्णांक max_ports = priv->hw_info->max_ports;
	पूर्णांक idx = -1;
	पूर्णांक err;
	पूर्णांक i;

	/* Look क्रम a मुक्त slot */
	क्रम (i = max_ports; i < ARRAY_SIZE(priv->vlans); i++) अणु
		अगर (!priv->vlans[i].bridge) अणु
			idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (idx == -1)
		वापस -ENOSPC;

	अगर (fid == -1)
		fid = idx;

	vlan_active.index = idx;
	vlan_active.table = GSWIP_TABLE_ACTIVE_VLAN;
	vlan_active.key[0] = vid;
	vlan_active.val[0] = fid;
	vlan_active.valid = true;

	err = gswip_pce_table_entry_ग_लिखो(priv, &vlan_active);
	अगर (err) अणु
		dev_err(priv->dev, "failed to write active VLAN: %d\n",	err);
		वापस err;
	पूर्ण

	priv->vlans[idx].bridge = bridge;
	priv->vlans[idx].vid = vid;
	priv->vlans[idx].fid = fid;

	वापस idx;
पूर्ण

अटल पूर्णांक gswip_vlan_active_हटाओ(काष्ठा gswip_priv *priv, पूर्णांक idx)
अणु
	काष्ठा gswip_pce_table_entry vlan_active = अणु0,पूर्ण;
	पूर्णांक err;

	vlan_active.index = idx;
	vlan_active.table = GSWIP_TABLE_ACTIVE_VLAN;
	vlan_active.valid = false;
	err = gswip_pce_table_entry_ग_लिखो(priv, &vlan_active);
	अगर (err)
		dev_err(priv->dev, "failed to delete active VLAN: %d\n", err);
	priv->vlans[idx].bridge = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक gswip_vlan_add_unaware(काष्ठा gswip_priv *priv,
				  काष्ठा net_device *bridge, पूर्णांक port)
अणु
	काष्ठा gswip_pce_table_entry vlan_mapping = अणु0,पूर्ण;
	अचिन्हित पूर्णांक max_ports = priv->hw_info->max_ports;
	अचिन्हित पूर्णांक cpu_port = priv->hw_info->cpu_port;
	bool active_vlan_created = false;
	पूर्णांक idx = -1;
	पूर्णांक i;
	पूर्णांक err;

	/* Check अगर there is alपढ़ोy a page क्रम this bridge */
	क्रम (i = max_ports; i < ARRAY_SIZE(priv->vlans); i++) अणु
		अगर (priv->vlans[i].bridge == bridge) अणु
			idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If this bridge is not programmed yet, add a Active VLAN table
	 * entry in a मुक्त slot and prepare the VLAN mapping table entry.
	 */
	अगर (idx == -1) अणु
		idx = gswip_vlan_active_create(priv, bridge, -1, 0);
		अगर (idx < 0)
			वापस idx;
		active_vlan_created = true;

		vlan_mapping.index = idx;
		vlan_mapping.table = GSWIP_TABLE_VLAN_MAPPING;
		/* VLAN ID byte, maps to the VLAN ID of vlan active table */
		vlan_mapping.val[0] = 0;
	पूर्ण अन्यथा अणु
		/* Read the existing VLAN mapping entry from the चयन */
		vlan_mapping.index = idx;
		vlan_mapping.table = GSWIP_TABLE_VLAN_MAPPING;
		err = gswip_pce_table_entry_पढ़ो(priv, &vlan_mapping);
		अगर (err) अणु
			dev_err(priv->dev, "failed to read VLAN mapping: %d\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण

	/* Update the VLAN mapping entry and ग_लिखो it to the चयन */
	vlan_mapping.val[1] |= BIT(cpu_port);
	vlan_mapping.val[1] |= BIT(port);
	err = gswip_pce_table_entry_ग_लिखो(priv, &vlan_mapping);
	अगर (err) अणु
		dev_err(priv->dev, "failed to write VLAN mapping: %d\n", err);
		/* In हाल an Active VLAN was creaetd delete it again */
		अगर (active_vlan_created)
			gswip_vlan_active_हटाओ(priv, idx);
		वापस err;
	पूर्ण

	gswip_चयन_w(priv, 0, GSWIP_PCE_DEFPVID(port));
	वापस 0;
पूर्ण

अटल पूर्णांक gswip_vlan_add_aware(काष्ठा gswip_priv *priv,
				काष्ठा net_device *bridge, पूर्णांक port,
				u16 vid, bool untagged,
				bool pvid)
अणु
	काष्ठा gswip_pce_table_entry vlan_mapping = अणु0,पूर्ण;
	अचिन्हित पूर्णांक max_ports = priv->hw_info->max_ports;
	अचिन्हित पूर्णांक cpu_port = priv->hw_info->cpu_port;
	bool active_vlan_created = false;
	पूर्णांक idx = -1;
	पूर्णांक fid = -1;
	पूर्णांक i;
	पूर्णांक err;

	/* Check अगर there is alपढ़ोy a page क्रम this bridge */
	क्रम (i = max_ports; i < ARRAY_SIZE(priv->vlans); i++) अणु
		अगर (priv->vlans[i].bridge == bridge) अणु
			अगर (fid != -1 && fid != priv->vlans[i].fid)
				dev_err(priv->dev, "one bridge with multiple flow ids\n");
			fid = priv->vlans[i].fid;
			अगर (priv->vlans[i].vid == vid) अणु
				idx = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* If this bridge is not programmed yet, add a Active VLAN table
	 * entry in a मुक्त slot and prepare the VLAN mapping table entry.
	 */
	अगर (idx == -1) अणु
		idx = gswip_vlan_active_create(priv, bridge, fid, vid);
		अगर (idx < 0)
			वापस idx;
		active_vlan_created = true;

		vlan_mapping.index = idx;
		vlan_mapping.table = GSWIP_TABLE_VLAN_MAPPING;
		/* VLAN ID byte, maps to the VLAN ID of vlan active table */
		vlan_mapping.val[0] = vid;
	पूर्ण अन्यथा अणु
		/* Read the existing VLAN mapping entry from the चयन */
		vlan_mapping.index = idx;
		vlan_mapping.table = GSWIP_TABLE_VLAN_MAPPING;
		err = gswip_pce_table_entry_पढ़ो(priv, &vlan_mapping);
		अगर (err) अणु
			dev_err(priv->dev, "failed to read VLAN mapping: %d\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण

	vlan_mapping.val[0] = vid;
	/* Update the VLAN mapping entry and ग_लिखो it to the चयन */
	vlan_mapping.val[1] |= BIT(cpu_port);
	vlan_mapping.val[2] |= BIT(cpu_port);
	vlan_mapping.val[1] |= BIT(port);
	अगर (untagged)
		vlan_mapping.val[2] &= ~BIT(port);
	अन्यथा
		vlan_mapping.val[2] |= BIT(port);
	err = gswip_pce_table_entry_ग_लिखो(priv, &vlan_mapping);
	अगर (err) अणु
		dev_err(priv->dev, "failed to write VLAN mapping: %d\n", err);
		/* In हाल an Active VLAN was creaetd delete it again */
		अगर (active_vlan_created)
			gswip_vlan_active_हटाओ(priv, idx);
		वापस err;
	पूर्ण

	अगर (pvid)
		gswip_चयन_w(priv, idx, GSWIP_PCE_DEFPVID(port));

	वापस 0;
पूर्ण

अटल पूर्णांक gswip_vlan_हटाओ(काष्ठा gswip_priv *priv,
			     काष्ठा net_device *bridge, पूर्णांक port,
			     u16 vid, bool pvid, bool vlan_aware)
अणु
	काष्ठा gswip_pce_table_entry vlan_mapping = अणु0,पूर्ण;
	अचिन्हित पूर्णांक max_ports = priv->hw_info->max_ports;
	अचिन्हित पूर्णांक cpu_port = priv->hw_info->cpu_port;
	पूर्णांक idx = -1;
	पूर्णांक i;
	पूर्णांक err;

	/* Check अगर there is alपढ़ोy a page क्रम this bridge */
	क्रम (i = max_ports; i < ARRAY_SIZE(priv->vlans); i++) अणु
		अगर (priv->vlans[i].bridge == bridge &&
		    (!vlan_aware || priv->vlans[i].vid == vid)) अणु
			idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (idx == -1) अणु
		dev_err(priv->dev, "bridge to leave does not exists\n");
		वापस -ENOENT;
	पूर्ण

	vlan_mapping.index = idx;
	vlan_mapping.table = GSWIP_TABLE_VLAN_MAPPING;
	err = gswip_pce_table_entry_पढ़ो(priv, &vlan_mapping);
	अगर (err) अणु
		dev_err(priv->dev, "failed to read VLAN mapping: %d\n",	err);
		वापस err;
	पूर्ण

	vlan_mapping.val[1] &= ~BIT(port);
	vlan_mapping.val[2] &= ~BIT(port);
	err = gswip_pce_table_entry_ग_लिखो(priv, &vlan_mapping);
	अगर (err) अणु
		dev_err(priv->dev, "failed to write VLAN mapping: %d\n", err);
		वापस err;
	पूर्ण

	/* In हाल all ports are हटाओd from the bridge, हटाओ the VLAN */
	अगर ((vlan_mapping.val[1] & ~BIT(cpu_port)) == 0) अणु
		err = gswip_vlan_active_हटाओ(priv, idx);
		अगर (err) अणु
			dev_err(priv->dev, "failed to write active VLAN: %d\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण

	/* GSWIP 2.2 (GRX300) and later program here the VID directly. */
	अगर (pvid)
		gswip_चयन_w(priv, 0, GSWIP_PCE_DEFPVID(port));

	वापस 0;
पूर्ण

अटल पूर्णांक gswip_port_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा net_device *bridge)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	पूर्णांक err;

	/* When the bridge uses VLAN filtering we have to configure VLAN
	 * specअगरic bridges. No bridge is configured here.
	 */
	अगर (!br_vlan_enabled(bridge)) अणु
		err = gswip_vlan_add_unaware(priv, bridge, port);
		अगर (err)
			वापस err;
		priv->port_vlan_filter &= ~BIT(port);
	पूर्ण अन्यथा अणु
		priv->port_vlan_filter |= BIT(port);
	पूर्ण
	वापस gswip_add_single_port_br(priv, port, false);
पूर्ण

अटल व्योम gswip_port_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    काष्ठा net_device *bridge)
अणु
	काष्ठा gswip_priv *priv = ds->priv;

	gswip_add_single_port_br(priv, port, true);

	/* When the bridge uses VLAN filtering we have to configure VLAN
	 * specअगरic bridges. No bridge is configured here.
	 */
	अगर (!br_vlan_enabled(bridge))
		gswip_vlan_हटाओ(priv, bridge, port, 0, true, false);
पूर्ण

अटल पूर्णांक gswip_port_vlan_prepare(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	काष्ठा net_device *bridge = dsa_to_port(ds, port)->bridge_dev;
	अचिन्हित पूर्णांक max_ports = priv->hw_info->max_ports;
	पूर्णांक pos = max_ports;
	पूर्णांक i, idx = -1;

	/* We only support VLAN filtering on bridges */
	अगर (!dsa_is_cpu_port(ds, port) && !bridge)
		वापस -EOPNOTSUPP;

	/* Check अगर there is alपढ़ोy a page क्रम this VLAN */
	क्रम (i = max_ports; i < ARRAY_SIZE(priv->vlans); i++) अणु
		अगर (priv->vlans[i].bridge == bridge &&
		    priv->vlans[i].vid == vlan->vid) अणु
			idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If this VLAN is not programmed yet, we have to reserve
	 * one entry in the VLAN table. Make sure we start at the
	 * next position round.
	 */
	अगर (idx == -1) अणु
		/* Look क्रम a मुक्त slot */
		क्रम (; pos < ARRAY_SIZE(priv->vlans); pos++) अणु
			अगर (!priv->vlans[pos].bridge) अणु
				idx = pos;
				pos++;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (idx == -1) अणु
			NL_SET_ERR_MSG_MOD(extack, "No slot in VLAN table");
			वापस -ENOSPC;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gswip_port_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	काष्ठा net_device *bridge = dsa_to_port(ds, port)->bridge_dev;
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	पूर्णांक err;

	err = gswip_port_vlan_prepare(ds, port, vlan, extack);
	अगर (err)
		वापस err;

	/* We have to receive all packets on the CPU port and should not
	 * करो any VLAN filtering here. This is also called with bridge
	 * शून्य and then we करो not know क्रम which bridge to configure
	 * this.
	 */
	अगर (dsa_is_cpu_port(ds, port))
		वापस 0;

	वापस gswip_vlan_add_aware(priv, bridge, port, vlan->vid,
				    untagged, pvid);
पूर्ण

अटल पूर्णांक gswip_port_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	काष्ठा net_device *bridge = dsa_to_port(ds, port)->bridge_dev;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;

	/* We have to receive all packets on the CPU port and should not
	 * करो any VLAN filtering here. This is also called with bridge
	 * शून्य and then we करो not know क्रम which bridge to configure
	 * this.
	 */
	अगर (dsa_is_cpu_port(ds, port))
		वापस 0;

	वापस gswip_vlan_हटाओ(priv, bridge, port, vlan->vid, pvid, true);
पूर्ण

अटल व्योम gswip_port_fast_age(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	काष्ठा gswip_pce_table_entry mac_bridge = अणु0,पूर्ण;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < 2048; i++) अणु
		mac_bridge.table = GSWIP_TABLE_MAC_BRIDGE;
		mac_bridge.index = i;

		err = gswip_pce_table_entry_पढ़ो(priv, &mac_bridge);
		अगर (err) अणु
			dev_err(priv->dev, "failed to read mac bridge: %d\n",
				err);
			वापस;
		पूर्ण

		अगर (!mac_bridge.valid)
			जारी;

		अगर (mac_bridge.val[1] & GSWIP_TABLE_MAC_BRIDGE_STATIC)
			जारी;

		अगर (((mac_bridge.val[0] & GENMASK(7, 4)) >> 4) != port)
			जारी;

		mac_bridge.valid = false;
		err = gswip_pce_table_entry_ग_लिखो(priv, &mac_bridge);
		अगर (err) अणु
			dev_err(priv->dev, "failed to write mac bridge: %d\n",
				err);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gswip_port_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port, u8 state)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	u32 stp_state;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		gswip_चयन_mask(priv, GSWIP_SDMA_PCTRL_EN, 0,
				  GSWIP_SDMA_PCTRLp(port));
		वापस;
	हाल BR_STATE_BLOCKING:
	हाल BR_STATE_LISTENING:
		stp_state = GSWIP_PCE_PCTRL_0_PSTATE_LISTEN;
		अवरोध;
	हाल BR_STATE_LEARNING:
		stp_state = GSWIP_PCE_PCTRL_0_PSTATE_LEARNING;
		अवरोध;
	हाल BR_STATE_FORWARDING:
		stp_state = GSWIP_PCE_PCTRL_0_PSTATE_FORWARDING;
		अवरोध;
	शेष:
		dev_err(priv->dev, "invalid STP state: %d\n", state);
		वापस;
	पूर्ण

	gswip_चयन_mask(priv, 0, GSWIP_SDMA_PCTRL_EN,
			  GSWIP_SDMA_PCTRLp(port));
	gswip_चयन_mask(priv, GSWIP_PCE_PCTRL_0_PSTATE_MASK, stp_state,
			  GSWIP_PCE_PCTRL_0p(port));
पूर्ण

अटल पूर्णांक gswip_port_fdb(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  स्थिर अचिन्हित अक्षर *addr, u16 vid, bool add)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	काष्ठा net_device *bridge = dsa_to_port(ds, port)->bridge_dev;
	काष्ठा gswip_pce_table_entry mac_bridge = अणु0,पूर्ण;
	अचिन्हित पूर्णांक cpu_port = priv->hw_info->cpu_port;
	पूर्णांक fid = -1;
	पूर्णांक i;
	पूर्णांक err;

	अगर (!bridge)
		वापस -EINVAL;

	क्रम (i = cpu_port; i < ARRAY_SIZE(priv->vlans); i++) अणु
		अगर (priv->vlans[i].bridge == bridge) अणु
			fid = priv->vlans[i].fid;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fid == -1) अणु
		dev_err(priv->dev, "Port not part of a bridge\n");
		वापस -EINVAL;
	पूर्ण

	mac_bridge.table = GSWIP_TABLE_MAC_BRIDGE;
	mac_bridge.key_mode = true;
	mac_bridge.key[0] = addr[5] | (addr[4] << 8);
	mac_bridge.key[1] = addr[3] | (addr[2] << 8);
	mac_bridge.key[2] = addr[1] | (addr[0] << 8);
	mac_bridge.key[3] = fid;
	mac_bridge.val[0] = add ? BIT(port) : 0; /* port map */
	mac_bridge.val[1] = GSWIP_TABLE_MAC_BRIDGE_STATIC;
	mac_bridge.valid = add;

	err = gswip_pce_table_entry_ग_लिखो(priv, &mac_bridge);
	अगर (err)
		dev_err(priv->dev, "failed to write mac bridge: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक gswip_port_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	वापस gswip_port_fdb(ds, port, addr, vid, true);
पूर्ण

अटल पूर्णांक gswip_port_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	वापस gswip_port_fdb(ds, port, addr, vid, false);
पूर्ण

अटल पूर्णांक gswip_port_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	काष्ठा gswip_pce_table_entry mac_bridge = अणु0,पूर्ण;
	अचिन्हित अक्षर addr[6];
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < 2048; i++) अणु
		mac_bridge.table = GSWIP_TABLE_MAC_BRIDGE;
		mac_bridge.index = i;

		err = gswip_pce_table_entry_पढ़ो(priv, &mac_bridge);
		अगर (err) अणु
			dev_err(priv->dev, "failed to write mac bridge: %d\n",
				err);
			वापस err;
		पूर्ण

		अगर (!mac_bridge.valid)
			जारी;

		addr[5] = mac_bridge.key[0] & 0xff;
		addr[4] = (mac_bridge.key[0] >> 8) & 0xff;
		addr[3] = mac_bridge.key[1] & 0xff;
		addr[2] = (mac_bridge.key[1] >> 8) & 0xff;
		addr[1] = mac_bridge.key[2] & 0xff;
		addr[0] = (mac_bridge.key[2] >> 8) & 0xff;
		अगर (mac_bridge.val[1] & GSWIP_TABLE_MAC_BRIDGE_STATIC) अणु
			अगर (mac_bridge.val[0] & BIT(port))
				cb(addr, 0, true, data);
		पूर्ण अन्यथा अणु
			अगर (((mac_bridge.val[0] & GENMASK(7, 4)) >> 4) == port)
				cb(addr, 0, false, data);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gswip_phylink_set_capab(अचिन्हित दीर्घ *supported,
				    काष्ठा phylink_link_state *state)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	/* Allow all the expected bits */
	phylink_set(mask, Autoneg);
	phylink_set_port_modes(mask);
	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);

	/* With the exclusion of MII, Reverse MII and Reduced MII, we
	 * support Gigabit, including Half duplex
	 */
	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_MII &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_REVMII &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_RMII) अणु
		phylink_set(mask, 1000baseT_Full);
		phylink_set(mask, 1000baseT_Half);
	पूर्ण

	phylink_set(mask, 10baseT_Half);
	phylink_set(mask, 10baseT_Full);
	phylink_set(mask, 100baseT_Half);
	phylink_set(mask, 100baseT_Full);

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल व्योम gswip_xrx200_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
					  अचिन्हित दीर्घ *supported,
					  काष्ठा phylink_link_state *state)
अणु
	चयन (port) अणु
	हाल 0:
	हाल 1:
		अगर (!phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface) &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_MII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_REVMII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_RMII)
			जाओ unsupported;
		अवरोध;
	हाल 2:
	हाल 3:
	हाल 4:
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_INTERNAL)
			जाओ unsupported;
		अवरोध;
	हाल 5:
		अगर (!phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface) &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_INTERNAL)
			जाओ unsupported;
		अवरोध;
	शेष:
		biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
		dev_err(ds->dev, "Unsupported port: %i\n", port);
		वापस;
	पूर्ण

	gswip_phylink_set_capab(supported, state);

	वापस;

unsupported:
	biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
	dev_err(ds->dev, "Unsupported interface '%s' for port %d\n",
		phy_modes(state->पूर्णांकerface), port);
पूर्ण

अटल व्योम gswip_xrx300_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
					  अचिन्हित दीर्घ *supported,
					  काष्ठा phylink_link_state *state)
अणु
	चयन (port) अणु
	हाल 0:
		अगर (!phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface) &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_GMII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_RMII)
			जाओ unsupported;
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_INTERNAL)
			जाओ unsupported;
		अवरोध;
	हाल 5:
		अगर (!phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface) &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_INTERNAL &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_RMII)
			जाओ unsupported;
		अवरोध;
	शेष:
		biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
		dev_err(ds->dev, "Unsupported port: %i\n", port);
		वापस;
	पूर्ण

	gswip_phylink_set_capab(supported, state);

	वापस;

unsupported:
	biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
	dev_err(ds->dev, "Unsupported interface '%s' for port %d\n",
		phy_modes(state->पूर्णांकerface), port);
पूर्ण

अटल व्योम gswip_port_set_link(काष्ठा gswip_priv *priv, पूर्णांक port, bool link)
अणु
	u32 mdio_phy;

	अगर (link)
		mdio_phy = GSWIP_MDIO_PHY_LINK_UP;
	अन्यथा
		mdio_phy = GSWIP_MDIO_PHY_LINK_DOWN;

	gswip_mdio_mask(priv, GSWIP_MDIO_PHY_LINK_MASK, mdio_phy,
			GSWIP_MDIO_PHYp(port));
पूर्ण

अटल व्योम gswip_port_set_speed(काष्ठा gswip_priv *priv, पूर्णांक port, पूर्णांक speed,
				 phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	u32 mdio_phy = 0, mii_cfg = 0, mac_ctrl_0 = 0;

	चयन (speed) अणु
	हाल SPEED_10:
		mdio_phy = GSWIP_MDIO_PHY_SPEED_M10;

		अगर (पूर्णांकerface == PHY_INTERFACE_MODE_RMII)
			mii_cfg = GSWIP_MII_CFG_RATE_M50;
		अन्यथा
			mii_cfg = GSWIP_MII_CFG_RATE_M2P5;

		mac_ctrl_0 = GSWIP_MAC_CTRL_0_GMII_MII;
		अवरोध;

	हाल SPEED_100:
		mdio_phy = GSWIP_MDIO_PHY_SPEED_M100;

		अगर (पूर्णांकerface == PHY_INTERFACE_MODE_RMII)
			mii_cfg = GSWIP_MII_CFG_RATE_M50;
		अन्यथा
			mii_cfg = GSWIP_MII_CFG_RATE_M25;

		mac_ctrl_0 = GSWIP_MAC_CTRL_0_GMII_MII;
		अवरोध;

	हाल SPEED_1000:
		mdio_phy = GSWIP_MDIO_PHY_SPEED_G1;

		mii_cfg = GSWIP_MII_CFG_RATE_M125;

		mac_ctrl_0 = GSWIP_MAC_CTRL_0_GMII_RGMII;
		अवरोध;
	पूर्ण

	gswip_mdio_mask(priv, GSWIP_MDIO_PHY_SPEED_MASK, mdio_phy,
			GSWIP_MDIO_PHYp(port));
	gswip_mii_mask_cfg(priv, GSWIP_MII_CFG_RATE_MASK, mii_cfg, port);
	gswip_चयन_mask(priv, GSWIP_MAC_CTRL_0_GMII_MASK, mac_ctrl_0,
			  GSWIP_MAC_CTRL_0p(port));
पूर्ण

अटल व्योम gswip_port_set_duplex(काष्ठा gswip_priv *priv, पूर्णांक port, पूर्णांक duplex)
अणु
	u32 mac_ctrl_0, mdio_phy;

	अगर (duplex == DUPLEX_FULL) अणु
		mac_ctrl_0 = GSWIP_MAC_CTRL_0_FDUP_EN;
		mdio_phy = GSWIP_MDIO_PHY_FDUP_EN;
	पूर्ण अन्यथा अणु
		mac_ctrl_0 = GSWIP_MAC_CTRL_0_FDUP_DIS;
		mdio_phy = GSWIP_MDIO_PHY_FDUP_DIS;
	पूर्ण

	gswip_चयन_mask(priv, GSWIP_MAC_CTRL_0_FDUP_MASK, mac_ctrl_0,
			  GSWIP_MAC_CTRL_0p(port));
	gswip_mdio_mask(priv, GSWIP_MDIO_PHY_FDUP_MASK, mdio_phy,
			GSWIP_MDIO_PHYp(port));
पूर्ण

अटल व्योम gswip_port_set_छोड़ो(काष्ठा gswip_priv *priv, पूर्णांक port,
				 bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	u32 mac_ctrl_0, mdio_phy;

	अगर (tx_छोड़ो && rx_छोड़ो) अणु
		mac_ctrl_0 = GSWIP_MAC_CTRL_0_FCON_RXTX;
		mdio_phy = GSWIP_MDIO_PHY_FCONTX_EN |
			   GSWIP_MDIO_PHY_FCONRX_EN;
	पूर्ण अन्यथा अगर (tx_छोड़ो) अणु
		mac_ctrl_0 = GSWIP_MAC_CTRL_0_FCON_TX;
		mdio_phy = GSWIP_MDIO_PHY_FCONTX_EN |
			   GSWIP_MDIO_PHY_FCONRX_DIS;
	पूर्ण अन्यथा अगर (rx_छोड़ो) अणु
		mac_ctrl_0 = GSWIP_MAC_CTRL_0_FCON_RX;
		mdio_phy = GSWIP_MDIO_PHY_FCONTX_DIS |
			   GSWIP_MDIO_PHY_FCONRX_EN;
	पूर्ण अन्यथा अणु
		mac_ctrl_0 = GSWIP_MAC_CTRL_0_FCON_NONE;
		mdio_phy = GSWIP_MDIO_PHY_FCONTX_DIS |
			   GSWIP_MDIO_PHY_FCONRX_DIS;
	पूर्ण

	gswip_चयन_mask(priv, GSWIP_MAC_CTRL_0_FCON_MASK,
			  mac_ctrl_0, GSWIP_MAC_CTRL_0p(port));
	gswip_mdio_mask(priv,
			GSWIP_MDIO_PHY_FCONTX_MASK |
			GSWIP_MDIO_PHY_FCONRX_MASK,
			mdio_phy, GSWIP_MDIO_PHYp(port));
पूर्ण

अटल व्योम gswip_phylink_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     अचिन्हित पूर्णांक mode,
				     स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	u32 miicfg = 0;

	miicfg |= GSWIP_MII_CFG_LDCLKDIS;

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_MII:
	हाल PHY_INTERFACE_MODE_INTERNAL:
		miicfg |= GSWIP_MII_CFG_MODE_MIIM;
		अवरोध;
	हाल PHY_INTERFACE_MODE_REVMII:
		miicfg |= GSWIP_MII_CFG_MODE_MIIP;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		miicfg |= GSWIP_MII_CFG_MODE_RMIIM;

		/* Configure the RMII घड़ी as output: */
		miicfg |= GSWIP_MII_CFG_RMII_CLK;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		miicfg |= GSWIP_MII_CFG_MODE_RGMII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_GMII:
		miicfg |= GSWIP_MII_CFG_MODE_GMII;
		अवरोध;
	शेष:
		dev_err(ds->dev,
			"Unsupported interface: %d\n", state->पूर्णांकerface);
		वापस;
	पूर्ण

	gswip_mii_mask_cfg(priv,
			   GSWIP_MII_CFG_MODE_MASK | GSWIP_MII_CFG_RMII_CLK |
			   GSWIP_MII_CFG_RGMII_IBS | GSWIP_MII_CFG_LDCLKDIS,
			   miicfg, port);

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		gswip_mii_mask_pcdu(priv, GSWIP_MII_PCDU_TXDLY_MASK |
					  GSWIP_MII_PCDU_RXDLY_MASK, 0, port);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		gswip_mii_mask_pcdu(priv, GSWIP_MII_PCDU_RXDLY_MASK, 0, port);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		gswip_mii_mask_pcdu(priv, GSWIP_MII_PCDU_TXDLY_MASK, 0, port);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gswip_phylink_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port,
					अचिन्हित पूर्णांक mode,
					phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा gswip_priv *priv = ds->priv;

	gswip_mii_mask_cfg(priv, GSWIP_MII_CFG_EN, 0, port);

	अगर (!dsa_is_cpu_port(ds, port))
		gswip_port_set_link(priv, port, false);
पूर्ण

अटल व्योम gswip_phylink_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      अचिन्हित पूर्णांक mode,
				      phy_पूर्णांकerface_t पूर्णांकerface,
				      काष्ठा phy_device *phydev,
				      पूर्णांक speed, पूर्णांक duplex,
				      bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा gswip_priv *priv = ds->priv;

	अगर (!dsa_is_cpu_port(ds, port)) अणु
		gswip_port_set_link(priv, port, true);
		gswip_port_set_speed(priv, port, speed, पूर्णांकerface);
		gswip_port_set_duplex(priv, port, duplex);
		gswip_port_set_छोड़ो(priv, port, tx_छोड़ो, rx_छोड़ो);
	पूर्ण

	gswip_mii_mask_cfg(priv, 0, GSWIP_MII_CFG_EN, port);
पूर्ण

अटल व्योम gswip_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port, u32 stringset,
			      uपूर्णांक8_t *data)
अणु
	पूर्णांक i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(gswip_rmon_cnt); i++)
		म_नकलन(data + i * ETH_GSTRING_LEN, gswip_rmon_cnt[i].name,
			ETH_GSTRING_LEN);
पूर्ण

अटल u32 gswip_bcm_ram_entry_पढ़ो(काष्ठा gswip_priv *priv, u32 table,
				    u32 index)
अणु
	u32 result;
	पूर्णांक err;

	gswip_चयन_w(priv, index, GSWIP_BM_RAM_ADDR);
	gswip_चयन_mask(priv, GSWIP_BM_RAM_CTRL_ADDR_MASK |
				GSWIP_BM_RAM_CTRL_OPMOD,
			      table | GSWIP_BM_RAM_CTRL_BAS,
			      GSWIP_BM_RAM_CTRL);

	err = gswip_चयन_r_समयout(priv, GSWIP_BM_RAM_CTRL,
				     GSWIP_BM_RAM_CTRL_BAS);
	अगर (err) अणु
		dev_err(priv->dev, "timeout while reading table: %u, index: %u",
			table, index);
		वापस 0;
	पूर्ण

	result = gswip_चयन_r(priv, GSWIP_BM_RAM_VAL(0));
	result |= gswip_चयन_r(priv, GSWIP_BM_RAM_VAL(1)) << 16;

	वापस result;
पूर्ण

अटल व्योम gswip_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    uपूर्णांक64_t *data)
अणु
	काष्ठा gswip_priv *priv = ds->priv;
	स्थिर काष्ठा gswip_rmon_cnt_desc *rmon_cnt;
	पूर्णांक i;
	u64 high;

	क्रम (i = 0; i < ARRAY_SIZE(gswip_rmon_cnt); i++) अणु
		rmon_cnt = &gswip_rmon_cnt[i];

		data[i] = gswip_bcm_ram_entry_पढ़ो(priv, port,
						   rmon_cnt->offset);
		अगर (rmon_cnt->size == 2) अणु
			high = gswip_bcm_ram_entry_पढ़ो(priv, port,
							rmon_cnt->offset + 1);
			data[i] |= high << 32;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक gswip_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	अगर (sset != ETH_SS_STATS)
		वापस 0;

	वापस ARRAY_SIZE(gswip_rmon_cnt);
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops gswip_xrx200_चयन_ops = अणु
	.get_tag_protocol	= gswip_get_tag_protocol,
	.setup			= gswip_setup,
	.port_enable		= gswip_port_enable,
	.port_disable		= gswip_port_disable,
	.port_bridge_join	= gswip_port_bridge_join,
	.port_bridge_leave	= gswip_port_bridge_leave,
	.port_fast_age		= gswip_port_fast_age,
	.port_vlan_filtering	= gswip_port_vlan_filtering,
	.port_vlan_add		= gswip_port_vlan_add,
	.port_vlan_del		= gswip_port_vlan_del,
	.port_stp_state_set	= gswip_port_stp_state_set,
	.port_fdb_add		= gswip_port_fdb_add,
	.port_fdb_del		= gswip_port_fdb_del,
	.port_fdb_dump		= gswip_port_fdb_dump,
	.phylink_validate	= gswip_xrx200_phylink_validate,
	.phylink_mac_config	= gswip_phylink_mac_config,
	.phylink_mac_link_करोwn	= gswip_phylink_mac_link_करोwn,
	.phylink_mac_link_up	= gswip_phylink_mac_link_up,
	.get_strings		= gswip_get_strings,
	.get_ethtool_stats	= gswip_get_ethtool_stats,
	.get_sset_count		= gswip_get_sset_count,
पूर्ण;

अटल स्थिर काष्ठा dsa_चयन_ops gswip_xrx300_चयन_ops = अणु
	.get_tag_protocol	= gswip_get_tag_protocol,
	.setup			= gswip_setup,
	.port_enable		= gswip_port_enable,
	.port_disable		= gswip_port_disable,
	.port_bridge_join	= gswip_port_bridge_join,
	.port_bridge_leave	= gswip_port_bridge_leave,
	.port_fast_age		= gswip_port_fast_age,
	.port_vlan_filtering	= gswip_port_vlan_filtering,
	.port_vlan_add		= gswip_port_vlan_add,
	.port_vlan_del		= gswip_port_vlan_del,
	.port_stp_state_set	= gswip_port_stp_state_set,
	.port_fdb_add		= gswip_port_fdb_add,
	.port_fdb_del		= gswip_port_fdb_del,
	.port_fdb_dump		= gswip_port_fdb_dump,
	.phylink_validate	= gswip_xrx300_phylink_validate,
	.phylink_mac_config	= gswip_phylink_mac_config,
	.phylink_mac_link_करोwn	= gswip_phylink_mac_link_करोwn,
	.phylink_mac_link_up	= gswip_phylink_mac_link_up,
	.get_strings		= gswip_get_strings,
	.get_ethtool_stats	= gswip_get_ethtool_stats,
	.get_sset_count		= gswip_get_sset_count,
पूर्ण;

अटल स्थिर काष्ठा xway_gphy_match_data xrx200a1x_gphy_data = अणु
	.fe_firmware_name = "lantiq/xrx200_phy22f_a14.bin",
	.ge_firmware_name = "lantiq/xrx200_phy11g_a14.bin",
पूर्ण;

अटल स्थिर काष्ठा xway_gphy_match_data xrx200a2x_gphy_data = अणु
	.fe_firmware_name = "lantiq/xrx200_phy22f_a22.bin",
	.ge_firmware_name = "lantiq/xrx200_phy11g_a22.bin",
पूर्ण;

अटल स्थिर काष्ठा xway_gphy_match_data xrx300_gphy_data = अणु
	.fe_firmware_name = "lantiq/xrx300_phy22f_a21.bin",
	.ge_firmware_name = "lantiq/xrx300_phy11g_a21.bin",
पूर्ण;

अटल स्थिर काष्ठा of_device_id xway_gphy_match[] = अणु
	अणु .compatible = "lantiq,xrx200-gphy-fw", .data = शून्य पूर्ण,
	अणु .compatible = "lantiq,xrx200a1x-gphy-fw", .data = &xrx200a1x_gphy_data पूर्ण,
	अणु .compatible = "lantiq,xrx200a2x-gphy-fw", .data = &xrx200a2x_gphy_data पूर्ण,
	अणु .compatible = "lantiq,xrx300-gphy-fw", .data = &xrx300_gphy_data पूर्ण,
	अणु .compatible = "lantiq,xrx330-gphy-fw", .data = &xrx300_gphy_data पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक gswip_gphy_fw_load(काष्ठा gswip_priv *priv, काष्ठा gswip_gphy_fw *gphy_fw)
अणु
	काष्ठा device *dev = priv->dev;
	स्थिर काष्ठा firmware *fw;
	व्योम *fw_addr;
	dma_addr_t dma_addr;
	dma_addr_t dev_addr;
	माप_प्रकार size;
	पूर्णांक ret;

	ret = clk_prepare_enable(gphy_fw->clk_gate);
	अगर (ret)
		वापस ret;

	reset_control_निश्चित(gphy_fw->reset);

	ret = request_firmware(&fw, gphy_fw->fw_name, dev);
	अगर (ret) अणु
		dev_err(dev, "failed to load firmware: %s, error: %i\n",
			gphy_fw->fw_name, ret);
		वापस ret;
	पूर्ण

	/* GPHY cores need the firmware code in a persistent and contiguous
	 * memory area with a 16 kB boundary aligned start address.
	 */
	size = fw->size + XRX200_GPHY_FW_ALIGN;

	fw_addr = dmam_alloc_coherent(dev, size, &dma_addr, GFP_KERNEL);
	अगर (fw_addr) अणु
		fw_addr = PTR_ALIGN(fw_addr, XRX200_GPHY_FW_ALIGN);
		dev_addr = ALIGN(dma_addr, XRX200_GPHY_FW_ALIGN);
		स_नकल(fw_addr, fw->data, fw->size);
	पूर्ण अन्यथा अणु
		dev_err(dev, "failed to alloc firmware memory\n");
		release_firmware(fw);
		वापस -ENOMEM;
	पूर्ण

	release_firmware(fw);

	ret = regmap_ग_लिखो(priv->rcu_regmap, gphy_fw->fw_addr_offset, dev_addr);
	अगर (ret)
		वापस ret;

	reset_control_deनिश्चित(gphy_fw->reset);

	वापस ret;
पूर्ण

अटल पूर्णांक gswip_gphy_fw_probe(काष्ठा gswip_priv *priv,
			       काष्ठा gswip_gphy_fw *gphy_fw,
			       काष्ठा device_node *gphy_fw_np, पूर्णांक i)
अणु
	काष्ठा device *dev = priv->dev;
	u32 gphy_mode;
	पूर्णांक ret;
	अक्षर gphyname[10];

	snम_लिखो(gphyname, माप(gphyname), "gphy%d", i);

	gphy_fw->clk_gate = devm_clk_get(dev, gphyname);
	अगर (IS_ERR(gphy_fw->clk_gate)) अणु
		dev_err(dev, "Failed to lookup gate clock\n");
		वापस PTR_ERR(gphy_fw->clk_gate);
	पूर्ण

	ret = of_property_पढ़ो_u32(gphy_fw_np, "reg", &gphy_fw->fw_addr_offset);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u32(gphy_fw_np, "lantiq,gphy-mode", &gphy_mode);
	/* Default to GE mode */
	अगर (ret)
		gphy_mode = GPHY_MODE_GE;

	चयन (gphy_mode) अणु
	हाल GPHY_MODE_FE:
		gphy_fw->fw_name = priv->gphy_fw_name_cfg->fe_firmware_name;
		अवरोध;
	हाल GPHY_MODE_GE:
		gphy_fw->fw_name = priv->gphy_fw_name_cfg->ge_firmware_name;
		अवरोध;
	शेष:
		dev_err(dev, "Unknown GPHY mode %d\n", gphy_mode);
		वापस -EINVAL;
	पूर्ण

	gphy_fw->reset = of_reset_control_array_get_exclusive(gphy_fw_np);
	अगर (IS_ERR(gphy_fw->reset)) अणु
		अगर (PTR_ERR(gphy_fw->reset) != -EPROBE_DEFER)
			dev_err(dev, "Failed to lookup gphy reset\n");
		वापस PTR_ERR(gphy_fw->reset);
	पूर्ण

	वापस gswip_gphy_fw_load(priv, gphy_fw);
पूर्ण

अटल व्योम gswip_gphy_fw_हटाओ(काष्ठा gswip_priv *priv,
				 काष्ठा gswip_gphy_fw *gphy_fw)
अणु
	पूर्णांक ret;

	/* check अगर the device was fully probed */
	अगर (!gphy_fw->fw_name)
		वापस;

	ret = regmap_ग_लिखो(priv->rcu_regmap, gphy_fw->fw_addr_offset, 0);
	अगर (ret)
		dev_err(priv->dev, "can not reset GPHY FW pointer");

	clk_disable_unprepare(gphy_fw->clk_gate);

	reset_control_put(gphy_fw->reset);
पूर्ण

अटल पूर्णांक gswip_gphy_fw_list(काष्ठा gswip_priv *priv,
			      काष्ठा device_node *gphy_fw_list_np, u32 version)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा device_node *gphy_fw_np;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक err;
	पूर्णांक i = 0;

	/* The VRX200 rev 1.1 uses the GSWIP 2.0 and needs the older
	 * GPHY firmware. The VRX200 rev 1.2 uses the GSWIP 2.1 and also
	 * needs a dअगरferent GPHY firmware.
	 */
	अगर (of_device_is_compatible(gphy_fw_list_np, "lantiq,xrx200-gphy-fw")) अणु
		चयन (version) अणु
		हाल GSWIP_VERSION_2_0:
			priv->gphy_fw_name_cfg = &xrx200a1x_gphy_data;
			अवरोध;
		हाल GSWIP_VERSION_2_1:
			priv->gphy_fw_name_cfg = &xrx200a2x_gphy_data;
			अवरोध;
		शेष:
			dev_err(dev, "unknown GSWIP version: 0x%x", version);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	match = of_match_node(xway_gphy_match, gphy_fw_list_np);
	अगर (match && match->data)
		priv->gphy_fw_name_cfg = match->data;

	अगर (!priv->gphy_fw_name_cfg) अणु
		dev_err(dev, "GPHY compatible type not supported");
		वापस -ENOENT;
	पूर्ण

	priv->num_gphy_fw = of_get_available_child_count(gphy_fw_list_np);
	अगर (!priv->num_gphy_fw)
		वापस -ENOENT;

	priv->rcu_regmap = syscon_regmap_lookup_by_phandle(gphy_fw_list_np,
							   "lantiq,rcu");
	अगर (IS_ERR(priv->rcu_regmap))
		वापस PTR_ERR(priv->rcu_regmap);

	priv->gphy_fw = devm_kदो_स्मृति_array(dev, priv->num_gphy_fw,
					   माप(*priv->gphy_fw),
					   GFP_KERNEL | __GFP_ZERO);
	अगर (!priv->gphy_fw)
		वापस -ENOMEM;

	क्रम_each_available_child_of_node(gphy_fw_list_np, gphy_fw_np) अणु
		err = gswip_gphy_fw_probe(priv, &priv->gphy_fw[i],
					  gphy_fw_np, i);
		अगर (err)
			जाओ हटाओ_gphy;
		i++;
	पूर्ण

	/* The standalone PHY11G requires 300ms to be fully
	 * initialized and पढ़ोy क्रम any MDIO communication after being
	 * taken out of reset. For the SoC-पूर्णांकernal GPHY variant there
	 * is no (known) करोcumentation क्रम the minimum समय after a
	 * reset. Use the same value as क्रम the standalone variant as
	 * some users have reported पूर्णांकernal PHYs not being detected
	 * without any delay.
	 */
	msleep(300);

	वापस 0;

हटाओ_gphy:
	क्रम (i = 0; i < priv->num_gphy_fw; i++)
		gswip_gphy_fw_हटाओ(priv, &priv->gphy_fw[i]);
	वापस err;
पूर्ण

अटल पूर्णांक gswip_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gswip_priv *priv;
	काष्ठा device_node *np, *mdio_np, *gphy_fw_np;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;
	पूर्णांक i;
	u32 version;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->gswip = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->gswip))
		वापस PTR_ERR(priv->gswip);

	priv->mdio = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(priv->mdio))
		वापस PTR_ERR(priv->mdio);

	priv->mii = devm_platक्रमm_ioremap_resource(pdev, 2);
	अगर (IS_ERR(priv->mii))
		वापस PTR_ERR(priv->mii);

	priv->hw_info = of_device_get_match_data(dev);
	अगर (!priv->hw_info)
		वापस -EINVAL;

	priv->ds = devm_kzalloc(dev, माप(*priv->ds), GFP_KERNEL);
	अगर (!priv->ds)
		वापस -ENOMEM;

	priv->ds->dev = dev;
	priv->ds->num_ports = priv->hw_info->max_ports;
	priv->ds->priv = priv;
	priv->ds->ops = priv->hw_info->ops;
	priv->dev = dev;
	version = gswip_चयन_r(priv, GSWIP_VERSION);

	np = dev->of_node;
	चयन (version) अणु
	हाल GSWIP_VERSION_2_0:
	हाल GSWIP_VERSION_2_1:
		अगर (!of_device_is_compatible(np, "lantiq,xrx200-gswip"))
			वापस -EINVAL;
		अवरोध;
	हाल GSWIP_VERSION_2_2:
	हाल GSWIP_VERSION_2_2_ETC:
		अगर (!of_device_is_compatible(np, "lantiq,xrx300-gswip") &&
		    !of_device_is_compatible(np, "lantiq,xrx330-gswip"))
			वापस -EINVAL;
		अवरोध;
	शेष:
		dev_err(dev, "unknown GSWIP version: 0x%x", version);
		वापस -ENOENT;
	पूर्ण

	/* bring up the mdio bus */
	gphy_fw_np = of_get_compatible_child(dev->of_node, "lantiq,gphy-fw");
	अगर (gphy_fw_np) अणु
		err = gswip_gphy_fw_list(priv, gphy_fw_np, version);
		of_node_put(gphy_fw_np);
		अगर (err) अणु
			dev_err(dev, "gphy fw probe failed\n");
			वापस err;
		पूर्ण
	पूर्ण

	/* bring up the mdio bus */
	mdio_np = of_get_compatible_child(dev->of_node, "lantiq,xrx200-mdio");
	अगर (mdio_np) अणु
		err = gswip_mdio(priv, mdio_np);
		अगर (err) अणु
			dev_err(dev, "mdio probe failed\n");
			जाओ put_mdio_node;
		पूर्ण
	पूर्ण

	err = dsa_रेजिस्टर_चयन(priv->ds);
	अगर (err) अणु
		dev_err(dev, "dsa switch register failed: %i\n", err);
		जाओ mdio_bus;
	पूर्ण
	अगर (!dsa_is_cpu_port(priv->ds, priv->hw_info->cpu_port)) अणु
		dev_err(dev, "wrong CPU port defined, HW only supports port: %i",
			priv->hw_info->cpu_port);
		err = -EINVAL;
		जाओ disable_चयन;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	dev_info(dev, "probed GSWIP version %lx mod %lx\n",
		 (version & GSWIP_VERSION_REV_MASK) >> GSWIP_VERSION_REV_SHIFT,
		 (version & GSWIP_VERSION_MOD_MASK) >> GSWIP_VERSION_MOD_SHIFT);
	वापस 0;

disable_चयन:
	gswip_mdio_mask(priv, GSWIP_MDIO_GLOB_ENABLE, 0, GSWIP_MDIO_GLOB);
	dsa_unरेजिस्टर_चयन(priv->ds);
mdio_bus:
	अगर (mdio_np)
		mdiobus_unरेजिस्टर(priv->ds->slave_mii_bus);
put_mdio_node:
	of_node_put(mdio_np);
	क्रम (i = 0; i < priv->num_gphy_fw; i++)
		gswip_gphy_fw_हटाओ(priv, &priv->gphy_fw[i]);
	वापस err;
पूर्ण

अटल पूर्णांक gswip_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gswip_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	/* disable the चयन */
	gswip_mdio_mask(priv, GSWIP_MDIO_GLOB_ENABLE, 0, GSWIP_MDIO_GLOB);

	dsa_unरेजिस्टर_चयन(priv->ds);

	अगर (priv->ds->slave_mii_bus) अणु
		mdiobus_unरेजिस्टर(priv->ds->slave_mii_bus);
		of_node_put(priv->ds->slave_mii_bus->dev.of_node);
	पूर्ण

	क्रम (i = 0; i < priv->num_gphy_fw; i++)
		gswip_gphy_fw_हटाओ(priv, &priv->gphy_fw[i]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gswip_hw_info gswip_xrx200 = अणु
	.max_ports = 7,
	.cpu_port = 6,
	.ops = &gswip_xrx200_चयन_ops,
पूर्ण;

अटल स्थिर काष्ठा gswip_hw_info gswip_xrx300 = अणु
	.max_ports = 7,
	.cpu_port = 6,
	.ops = &gswip_xrx300_चयन_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id gswip_of_match[] = अणु
	अणु .compatible = "lantiq,xrx200-gswip", .data = &gswip_xrx200 पूर्ण,
	अणु .compatible = "lantiq,xrx300-gswip", .data = &gswip_xrx300 पूर्ण,
	अणु .compatible = "lantiq,xrx330-gswip", .data = &gswip_xrx300 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gswip_of_match);

अटल काष्ठा platक्रमm_driver gswip_driver = अणु
	.probe = gswip_probe,
	.हटाओ = gswip_हटाओ,
	.driver = अणु
		.name = "gswip",
		.of_match_table = gswip_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(gswip_driver);

MODULE_FIRMWARE("lantiq/xrx300_phy11g_a21.bin");
MODULE_FIRMWARE("lantiq/xrx300_phy22f_a21.bin");
MODULE_FIRMWARE("lantiq/xrx200_phy11g_a14.bin");
MODULE_FIRMWARE("lantiq/xrx200_phy11g_a22.bin");
MODULE_FIRMWARE("lantiq/xrx200_phy22f_a14.bin");
MODULE_FIRMWARE("lantiq/xrx200_phy22f_a22.bin");
MODULE_AUTHOR("Hauke Mehrtens <hauke@hauke-m.de>");
MODULE_DESCRIPTION("Lantiq / Intel GSWIP driver");
MODULE_LICENSE("GPL v2");
