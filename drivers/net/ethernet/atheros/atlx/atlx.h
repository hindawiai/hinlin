<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* atlx_hw.h -- common hardware definitions क्रम Attansic network drivers
 *
 * Copyright(c) 2005 - 2006 Attansic Corporation. All rights reserved.
 * Copyright(c) 2006 - 2007 Chris Snook <csnook@redhat.com>
 * Copyright(c) 2006 - 2008 Jay Cliburn <jcliburn@gmail.com>
 * Copyright(c) 2007 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित ATLX_H
#घोषणा ATLX_H

#समावेश <linux/module.h>
#समावेश <linux/types.h>

#घोषणा ATLX_ERR_PHY			2
#घोषणा ATLX_ERR_PHY_SPEED		7
#घोषणा ATLX_ERR_PHY_RES		8

#घोषणा SPEED_0				0xffff
#घोषणा SPEED_10			10
#घोषणा SPEED_100			100
#घोषणा SPEED_1000			1000
#घोषणा HALF_DUPLEX			1
#घोषणा FULL_DUPLEX			2

#घोषणा MEDIA_TYPE_AUTO_SENSOR		0

/* रेजिस्टर definitions */
#घोषणा REG_PM_CTRLSTAT			0x44

#घोषणा REG_PCIE_CAP_LIST		0x58

#घोषणा REG_VPD_CAP			0x6C
#घोषणा VPD_CAP_ID_MASK			0xFF
#घोषणा VPD_CAP_ID_SHIFT		0
#घोषणा VPD_CAP_NEXT_PTR_MASK		0xFF
#घोषणा VPD_CAP_NEXT_PTR_SHIFT		8
#घोषणा VPD_CAP_VPD_ADDR_MASK		0x7FFF
#घोषणा VPD_CAP_VPD_ADDR_SHIFT		16
#घोषणा VPD_CAP_VPD_FLAG		0x80000000

#घोषणा REG_VPD_DATA			0x70

#घोषणा REG_SPI_FLASH_CTRL		0x200
#घोषणा SPI_FLASH_CTRL_STS_NON_RDY	0x1
#घोषणा SPI_FLASH_CTRL_STS_WEN		0x2
#घोषणा SPI_FLASH_CTRL_STS_WPEN		0x80
#घोषणा SPI_FLASH_CTRL_DEV_STS_MASK	0xFF
#घोषणा SPI_FLASH_CTRL_DEV_STS_SHIFT	0
#घोषणा SPI_FLASH_CTRL_INS_MASK		0x7
#घोषणा SPI_FLASH_CTRL_INS_SHIFT	8
#घोषणा SPI_FLASH_CTRL_START		0x800
#घोषणा SPI_FLASH_CTRL_EN_VPD		0x2000
#घोषणा SPI_FLASH_CTRL_LDSTART		0x8000
#घोषणा SPI_FLASH_CTRL_CS_HI_MASK	0x3
#घोषणा SPI_FLASH_CTRL_CS_HI_SHIFT	16
#घोषणा SPI_FLASH_CTRL_CS_HOLD_MASK	0x3
#घोषणा SPI_FLASH_CTRL_CS_HOLD_SHIFT	18
#घोषणा SPI_FLASH_CTRL_CLK_LO_MASK	0x3
#घोषणा SPI_FLASH_CTRL_CLK_LO_SHIFT	20
#घोषणा SPI_FLASH_CTRL_CLK_HI_MASK	0x3
#घोषणा SPI_FLASH_CTRL_CLK_HI_SHIFT	22
#घोषणा SPI_FLASH_CTRL_CS_SETUP_MASK	0x3
#घोषणा SPI_FLASH_CTRL_CS_SETUP_SHIFT	24
#घोषणा SPI_FLASH_CTRL_EROM_PGSZ_MASK	0x3
#घोषणा SPI_FLASH_CTRL_EROM_PGSZ_SHIFT	26
#घोषणा SPI_FLASH_CTRL_WAIT_READY	0x10000000

#घोषणा REG_SPI_ADDR			0x204

#घोषणा REG_SPI_DATA			0x208

#घोषणा REG_SPI_FLASH_CONFIG		0x20C
#घोषणा SPI_FLASH_CONFIG_LD_ADDR_MASK	0xFFFFFF
#घोषणा SPI_FLASH_CONFIG_LD_ADDR_SHIFT	0
#घोषणा SPI_FLASH_CONFIG_VPD_ADDR_MASK	0x3
#घोषणा SPI_FLASH_CONFIG_VPD_ADDR_SHIFT	24
#घोषणा SPI_FLASH_CONFIG_LD_EXIST	0x4000000

#घोषणा REG_SPI_FLASH_OP_PROGRAM	0x210
#घोषणा REG_SPI_FLASH_OP_SC_ERASE	0x211
#घोषणा REG_SPI_FLASH_OP_CHIP_ERASE	0x212
#घोषणा REG_SPI_FLASH_OP_RDID		0x213
#घोषणा REG_SPI_FLASH_OP_WREN		0x214
#घोषणा REG_SPI_FLASH_OP_RDSR		0x215
#घोषणा REG_SPI_FLASH_OP_WRSR		0x216
#घोषणा REG_SPI_FLASH_OP_READ		0x217

#घोषणा REG_TWSI_CTRL			0x218
#घोषणा TWSI_CTRL_LD_OFFSET_MASK	0xFF
#घोषणा TWSI_CTRL_LD_OFFSET_SHIFT	0
#घोषणा TWSI_CTRL_LD_SLV_ADDR_MASK	0x7
#घोषणा TWSI_CTRL_LD_SLV_ADDR_SHIFT	8
#घोषणा TWSI_CTRL_SW_LDSTART		0x800
#घोषणा TWSI_CTRL_HW_LDSTART		0x1000
#घोषणा TWSI_CTRL_SMB_SLV_ADDR_MASK	0x7F
#घोषणा TWSI_CTRL_SMB_SLV_ADDR_SHIFT	15
#घोषणा TWSI_CTRL_LD_EXIST		0x400000
#घोषणा TWSI_CTRL_READ_FREQ_SEL_MASK	0x3
#घोषणा TWSI_CTRL_READ_FREQ_SEL_SHIFT	23
#घोषणा TWSI_CTRL_FREQ_SEL_100K		0
#घोषणा TWSI_CTRL_FREQ_SEL_200K		1
#घोषणा TWSI_CTRL_FREQ_SEL_300K		2
#घोषणा TWSI_CTRL_FREQ_SEL_400K		3
#घोषणा TWSI_CTRL_SMB_SLV_ADDR		/* FIXME: define or हटाओ */
#घोषणा TWSI_CTRL_WRITE_FREQ_SEL_MASK	0x3
#घोषणा TWSI_CTRL_WRITE_FREQ_SEL_SHIFT	24

#घोषणा REG_PCIE_DEV_MISC_CTRL			0x21C
#घोषणा PCIE_DEV_MISC_CTRL_EXT_PIPE		0x2
#घोषणा PCIE_DEV_MISC_CTRL_RETRY_BUFDIS		0x1
#घोषणा PCIE_DEV_MISC_CTRL_SPIROM_EXIST		0x4
#घोषणा PCIE_DEV_MISC_CTRL_SERDES_ENDIAN	0x8
#घोषणा PCIE_DEV_MISC_CTRL_SERDES_SEL_DIN	0x10

#घोषणा REG_PCIE_PHYMISC		0x1000
#घोषणा PCIE_PHYMISC_FORCE_RCV_DET	0x4

#घोषणा REG_PCIE_DLL_TX_CTRL1		0x1104
#घोषणा PCIE_DLL_TX_CTRL1_SEL_NOR_CLK	0x400
#घोषणा PCIE_DLL_TX_CTRL1_DEF		0x568

#घोषणा REG_LTSSM_TEST_MODE		0x12FC
#घोषणा LTSSM_TEST_MODE_DEF		0x6500

/* Master Control Register */
#घोषणा REG_MASTER_CTRL			0x1400
#घोषणा MASTER_CTRL_SOFT_RST		0x1
#घोषणा MASTER_CTRL_MTIMER_EN		0x2
#घोषणा MASTER_CTRL_ITIMER_EN		0x4
#घोषणा MASTER_CTRL_MANUAL_INT		0x8
#घोषणा MASTER_CTRL_REV_NUM_SHIFT	16
#घोषणा MASTER_CTRL_REV_NUM_MASK	0xFF
#घोषणा MASTER_CTRL_DEV_ID_SHIFT	24
#घोषणा MASTER_CTRL_DEV_ID_MASK		0xFF

/* Timer Initial Value Register */
#घोषणा REG_MANUAL_TIMER_INIT		0x1404

/* IRQ Moderator Timer Initial Value Register */
#घोषणा REG_IRQ_MODU_TIMER_INIT		0x1408

#घोषणा REG_PHY_ENABLE			0x140C

/* IRQ Anti-Lost Timer Initial Value Register */
#घोषणा REG_CMBDISDMA_TIMER		0x140E

/* Block IDLE Status Register */
#घोषणा REG_IDLE_STATUS			0x1410

/* MDIO Control Register */
#घोषणा REG_MDIO_CTRL			0x1414
#घोषणा MDIO_DATA_MASK			0xFFFF
#घोषणा MDIO_DATA_SHIFT			0
#घोषणा MDIO_REG_ADDR_MASK		0x1F
#घोषणा MDIO_REG_ADDR_SHIFT		16
#घोषणा MDIO_RW				0x200000
#घोषणा MDIO_SUP_PREAMBLE		0x400000
#घोषणा MDIO_START			0x800000
#घोषणा MDIO_CLK_SEL_SHIFT		24
#घोषणा MDIO_CLK_25_4			0
#घोषणा MDIO_CLK_25_6			2
#घोषणा MDIO_CLK_25_8			3
#घोषणा MDIO_CLK_25_10			4
#घोषणा MDIO_CLK_25_14			5
#घोषणा MDIO_CLK_25_20			6
#घोषणा MDIO_CLK_25_28			7
#घोषणा MDIO_BUSY			0x8000000

/* MII PHY Status Register */
#घोषणा REG_PHY_STATUS			0x1418

/* BIST Control and Status Register0 (क्रम the Packet Memory) */
#घोषणा REG_BIST0_CTRL			0x141C
#घोषणा BIST0_NOW			0x1
#घोषणा BIST0_SRAM_FAIL			0x2
#घोषणा BIST0_FUSE_FLAG			0x4
#घोषणा REG_BIST1_CTRL			0x1420
#घोषणा BIST1_NOW			0x1
#घोषणा BIST1_SRAM_FAIL			0x2
#घोषणा BIST1_FUSE_FLAG			0x4

/* SerDes Lock Detect Control and Status Register */
#घोषणा REG_SERDES_LOCK			0x1424
#घोषणा SERDES_LOCK_DETECT		1
#घोषणा SERDES_LOCK_DETECT_EN		2

/* MAC Control Register */
#घोषणा REG_MAC_CTRL			0x1480
#घोषणा MAC_CTRL_TX_EN			1
#घोषणा MAC_CTRL_RX_EN			2
#घोषणा MAC_CTRL_TX_FLOW		4
#घोषणा MAC_CTRL_RX_FLOW		8
#घोषणा MAC_CTRL_LOOPBACK		0x10
#घोषणा MAC_CTRL_DUPLX			0x20
#घोषणा MAC_CTRL_ADD_CRC		0x40
#घोषणा MAC_CTRL_PAD			0x80
#घोषणा MAC_CTRL_LENCHK			0x100
#घोषणा MAC_CTRL_HUGE_EN		0x200
#घोषणा MAC_CTRL_PRMLEN_SHIFT		10
#घोषणा MAC_CTRL_PRMLEN_MASK		0xF
#घोषणा MAC_CTRL_RMV_VLAN		0x4000
#घोषणा MAC_CTRL_PROMIS_EN		0x8000
#घोषणा MAC_CTRL_MC_ALL_EN		0x2000000
#घोषणा MAC_CTRL_BC_EN			0x4000000

/* MAC IPG/IFG Control Register */
#घोषणा REG_MAC_IPG_IFG			0x1484
#घोषणा MAC_IPG_IFG_IPGT_SHIFT		0
#घोषणा MAC_IPG_IFG_IPGT_MASK		0x7F
#घोषणा MAC_IPG_IFG_MIFG_SHIFT		8
#घोषणा MAC_IPG_IFG_MIFG_MASK		0xFF
#घोषणा MAC_IPG_IFG_IPGR1_SHIFT		16
#घोषणा MAC_IPG_IFG_IPGR1_MASK		0x7F
#घोषणा MAC_IPG_IFG_IPGR2_SHIFT		24
#घोषणा MAC_IPG_IFG_IPGR2_MASK		0x7F

/* MAC STATION ADDRESS */
#घोषणा REG_MAC_STA_ADDR		0x1488

/* Hash table क्रम multicast address */
#घोषणा REG_RX_HASH_TABLE		0x1490

/* MAC Half-Duplex Control Register */
#घोषणा REG_MAC_HALF_DUPLX_CTRL			0x1498
#घोषणा MAC_HALF_DUPLX_CTRL_LCOL_SHIFT		0
#घोषणा MAC_HALF_DUPLX_CTRL_LCOL_MASK		0x3FF
#घोषणा MAC_HALF_DUPLX_CTRL_RETRY_SHIFT		12
#घोषणा MAC_HALF_DUPLX_CTRL_RETRY_MASK		0xF
#घोषणा MAC_HALF_DUPLX_CTRL_EXC_DEF_EN		0x10000
#घोषणा MAC_HALF_DUPLX_CTRL_NO_BACK_C		0x20000
#घोषणा MAC_HALF_DUPLX_CTRL_NO_BACK_P		0x40000
#घोषणा MAC_HALF_DUPLX_CTRL_ABEBE		0x80000
#घोषणा MAC_HALF_DUPLX_CTRL_ABEBT_SHIFT		20
#घोषणा MAC_HALF_DUPLX_CTRL_ABEBT_MASK		0xF
#घोषणा MAC_HALF_DUPLX_CTRL_JAMIPG_SHIFT	24
#घोषणा MAC_HALF_DUPLX_CTRL_JAMIPG_MASK		0xF

/* Maximum Frame Length Control Register */
#घोषणा REG_MTU				0x149C

/* Wake-On-Lan control रेजिस्टर */
#घोषणा REG_WOL_CTRL			0x14A0
#घोषणा WOL_PATTERN_EN			0x1
#घोषणा WOL_PATTERN_PME_EN		0x2
#घोषणा WOL_MAGIC_EN			0x4
#घोषणा WOL_MAGIC_PME_EN		0x8
#घोषणा WOL_LINK_CHG_EN			0x10
#घोषणा WOL_LINK_CHG_PME_EN		0x20
#घोषणा WOL_PATTERN_ST			0x100
#घोषणा WOL_MAGIC_ST			0x200
#घोषणा WOL_LINKCHG_ST			0x400
#घोषणा WOL_PT0_EN			0x10000
#घोषणा WOL_PT1_EN			0x20000
#घोषणा WOL_PT2_EN			0x40000
#घोषणा WOL_PT3_EN			0x80000
#घोषणा WOL_PT4_EN			0x100000
#घोषणा WOL_PT0_MATCH			0x1000000
#घोषणा WOL_PT1_MATCH			0x2000000
#घोषणा WOL_PT2_MATCH			0x4000000
#घोषणा WOL_PT3_MATCH			0x8000000
#घोषणा WOL_PT4_MATCH			0x10000000

/* Internal SRAM Partition Register, high 32 bits */
#घोषणा REG_SRAM_RFD_ADDR		0x1500

/* Descriptor Control रेजिस्टर, high 32 bits */
#घोषणा REG_DESC_BASE_ADDR_HI		0x1540

/* Interrupt Status Register */
#घोषणा REG_ISR				0x1600
#घोषणा ISR_UR_DETECTED			0x1000000
#घोषणा ISR_FERR_DETECTED		0x2000000
#घोषणा ISR_NFERR_DETECTED		0x4000000
#घोषणा ISR_CERR_DETECTED		0x8000000
#घोषणा ISR_PHY_LINKDOWN		0x10000000
#घोषणा ISR_DIS_INT			0x80000000

/* Interrupt Mask Register */
#घोषणा REG_IMR				0x1604

#घोषणा REG_RFD_RRD_IDX			0x1800
#घोषणा REG_TPD_IDX			0x1804

/* MII definitions */

/* PHY Common Register */
#घोषणा MII_ATLX_CR			0x09
#घोषणा MII_ATLX_SR			0x0A
#घोषणा MII_ATLX_ESR			0x0F
#घोषणा MII_ATLX_PSCR			0x10
#घोषणा MII_ATLX_PSSR			0x11

/* PHY Control Register */
#घोषणा MII_CR_SPEED_SELECT_MSB		0x0040	/* bits 6,13: 10=1000, 01=100,
						 * 00=10
						 */
#घोषणा MII_CR_COLL_TEST_ENABLE		0x0080	/* Collision test enable */
#घोषणा MII_CR_FULL_DUPLEX		0x0100	/* FDX =1, half duplex =0 */
#घोषणा MII_CR_RESTART_AUTO_NEG		0x0200	/* Restart स्वतः negotiation */
#घोषणा MII_CR_ISOLATE			0x0400	/* Isolate PHY from MII */
#घोषणा MII_CR_POWER_DOWN		0x0800	/* Power करोwn */
#घोषणा MII_CR_AUTO_NEG_EN		0x1000	/* Auto Neg Enable */
#घोषणा MII_CR_SPEED_SELECT_LSB		0x2000	/* bits 6,13: 10=1000, 01=100,
						 * 00=10
						 */
#घोषणा MII_CR_LOOPBACK			0x4000	/* 0 = normal, 1 = loopback */
#घोषणा MII_CR_RESET			0x8000	/* 0 = normal, 1 = PHY reset */
#घोषणा MII_CR_SPEED_MASK		0x2040
#घोषणा MII_CR_SPEED_1000		0x0040
#घोषणा MII_CR_SPEED_100		0x2000
#घोषणा MII_CR_SPEED_10			0x0000

/* PHY Status Register */
#घोषणा MII_SR_EXTENDED_CAPS		0x0001	/* Ext रेजिस्टर capabilities */
#घोषणा MII_SR_JABBER_DETECT		0x0002	/* Jabber Detected */
#घोषणा MII_SR_LINK_STATUS		0x0004	/* Link Status 1 = link */
#घोषणा MII_SR_AUTONEG_CAPS		0x0008	/* Auto Neg Capable */
#घोषणा MII_SR_REMOTE_FAULT		0x0010	/* Remote Fault Detect */
#घोषणा MII_SR_AUTONEG_COMPLETE		0x0020	/* Auto Neg Complete */
#घोषणा MII_SR_PREAMBLE_SUPPRESS	0x0040	/* Preamble may be suppressed */
#घोषणा MII_SR_EXTENDED_STATUS		0x0100	/* Ext stat info in Reg 0x0F */
#घोषणा MII_SR_100T2_HD_CAPS		0x0200	/* 100T2 Half Duplex Capable */
#घोषणा MII_SR_100T2_FD_CAPS		0x0400	/* 100T2 Full Duplex Capable */
#घोषणा MII_SR_10T_HD_CAPS		0x0800	/* 10T   Half Duplex Capable */
#घोषणा MII_SR_10T_FD_CAPS		0x1000	/* 10T   Full Duplex Capable */
#घोषणा MII_SR_100X_HD_CAPS		0x2000	/* 100X  Half Duplex Capable */
#घोषणा MII_SR_100X_FD_CAPS		0x4000	/* 100X  Full Duplex Capable */
#घोषणा MII_SR_100T4_CAPS		0x8000	/* 100T4 Capable */

/* Link partner ability रेजिस्टर */
#घोषणा MII_LPA_SLCT			0x001f	/* Same as advertise selector */
#घोषणा MII_LPA_10HALF			0x0020	/* Can करो 10mbps half-duplex */
#घोषणा MII_LPA_10FULL			0x0040	/* Can करो 10mbps full-duplex */
#घोषणा MII_LPA_100HALF			0x0080	/* Can करो 100mbps half-duplex */
#घोषणा MII_LPA_100FULL			0x0100	/* Can करो 100mbps full-duplex */
#घोषणा MII_LPA_100BASE4		0x0200	/* 100BASE-T4 */
#घोषणा MII_LPA_PAUSE			0x0400	/* PAUSE */
#घोषणा MII_LPA_ASYPAUSE		0x0800	/* Asymmetrical PAUSE */
#घोषणा MII_LPA_RFAULT			0x2000	/* Link partner faulted */
#घोषणा MII_LPA_LPACK			0x4000	/* Link partner acked us */
#घोषणा MII_LPA_NPAGE			0x8000	/* Next page bit */

/* Autoneg Advertisement Register */
#घोषणा MII_AR_SELECTOR_FIELD		0x0001	/* IEEE 802.3 CSMA/CD */
#घोषणा MII_AR_10T_HD_CAPS		0x0020	/* 10T   Half Duplex Capable */
#घोषणा MII_AR_10T_FD_CAPS		0x0040	/* 10T   Full Duplex Capable */
#घोषणा MII_AR_100TX_HD_CAPS		0x0080	/* 100TX Half Duplex Capable */
#घोषणा MII_AR_100TX_FD_CAPS		0x0100	/* 100TX Full Duplex Capable */
#घोषणा MII_AR_100T4_CAPS		0x0200	/* 100T4 Capable */
#घोषणा MII_AR_PAUSE			0x0400	/* Pause operation desired */
#घोषणा MII_AR_ASM_सूची			0x0800	/* Asymmetric Pause Dir bit */
#घोषणा MII_AR_REMOTE_FAULT		0x2000	/* Remote Fault detected */
#घोषणा MII_AR_NEXT_PAGE		0x8000	/* Next Page ability support */
#घोषणा MII_AR_SPEED_MASK		0x01E0
#घोषणा MII_AR_DEFAULT_CAP_MASK		0x0DE0

/* 1000BASE-T Control Register */
#घोषणा MII_ATLX_CR_1000T_HD_CAPS	0x0100	/* Adv 1000T HD cap */
#घोषणा MII_ATLX_CR_1000T_FD_CAPS	0x0200	/* Adv 1000T FD cap */
#घोषणा MII_ATLX_CR_1000T_REPEATER_DTE	0x0400	/* 1=Repeater/चयन device,
						 * 0=DTE device */
#घोषणा MII_ATLX_CR_1000T_MS_VALUE	0x0800	/* 1=Config PHY as Master,
						 * 0=Configure PHY as Slave */
#घोषणा MII_ATLX_CR_1000T_MS_ENABLE	0x1000	/* 1=Man Master/Slave config,
						 * 0=Auto Master/Slave config
						 */
#घोषणा MII_ATLX_CR_1000T_TEST_MODE_NORMAL	0x0000	/* Normal Operation */
#घोषणा MII_ATLX_CR_1000T_TEST_MODE_1	0x2000	/* Transmit Waveक्रमm test */
#घोषणा MII_ATLX_CR_1000T_TEST_MODE_2	0x4000	/* Master Xmit Jitter test */
#घोषणा MII_ATLX_CR_1000T_TEST_MODE_3	0x6000	/* Slave Xmit Jitter test */
#घोषणा MII_ATLX_CR_1000T_TEST_MODE_4	0x8000	/* Xmitter Distortion test */
#घोषणा MII_ATLX_CR_1000T_SPEED_MASK	0x0300
#घोषणा MII_ATLX_CR_1000T_DEFAULT_CAP_MASK	0x0300

/* 1000BASE-T Status Register */
#घोषणा MII_ATLX_SR_1000T_LP_HD_CAPS	0x0400	/* LP is 1000T HD capable */
#घोषणा MII_ATLX_SR_1000T_LP_FD_CAPS	0x0800	/* LP is 1000T FD capable */
#घोषणा MII_ATLX_SR_1000T_REMOTE_RX_STATUS	0x1000	/* Remote receiver OK */
#घोषणा MII_ATLX_SR_1000T_LOCAL_RX_STATUS	0x2000	/* Local receiver OK */
#घोषणा MII_ATLX_SR_1000T_MS_CONFIG_RES		0x4000	/* 1=Local TX is Master
							 * 0=Slave
							 */
#घोषणा MII_ATLX_SR_1000T_MS_CONFIG_FAULT	0x8000	/* Master/Slave config
							 * fault */
#घोषणा MII_ATLX_SR_1000T_REMOTE_RX_STATUS_SHIFT	12
#घोषणा MII_ATLX_SR_1000T_LOCAL_RX_STATUS_SHIFT		13

/* Extended Status Register */
#घोषणा MII_ATLX_ESR_1000T_HD_CAPS	0x1000	/* 1000T HD capable */
#घोषणा MII_ATLX_ESR_1000T_FD_CAPS	0x2000	/* 1000T FD capable */
#घोषणा MII_ATLX_ESR_1000X_HD_CAPS	0x4000	/* 1000X HD capable */
#घोषणा MII_ATLX_ESR_1000X_FD_CAPS	0x8000	/* 1000X FD capable */

/* ATLX PHY Specअगरic Control Register */
#घोषणा MII_ATLX_PSCR_JABBER_DISABLE	0x0001	/* 1=Jabber Func disabled */
#घोषणा MII_ATLX_PSCR_POLARITY_REVERSAL	0x0002	/* 1=Polarity Reversal enbld */
#घोषणा MII_ATLX_PSCR_SQE_TEST		0x0004	/* 1=SQE Test enabled */
#घोषणा MII_ATLX_PSCR_MAC_POWERDOWN	0x0008
#घोषणा MII_ATLX_PSCR_CLK125_DISABLE	0x0010	/* 1=CLK125 low
						 * 0=CLK125 toggling
						 */
#घोषणा MII_ATLX_PSCR_MDI_MANUAL_MODE	0x0000	/* MDI Crossover Mode bits 6:5,
						 * Manual MDI configuration
						 */
#घोषणा MII_ATLX_PSCR_MDIX_MANUAL_MODE	0x0020	/* Manual MDIX configuration */
#घोषणा MII_ATLX_PSCR_AUTO_X_1000T	0x0040	/* 1000BASE-T: Auto crossover
						 * 100BASE-TX/10BASE-T: MDI
						 * Mode */
#घोषणा MII_ATLX_PSCR_AUTO_X_MODE	0x0060	/* Auto crossover enabled
						 * all speeds.
						 */
#घोषणा MII_ATLX_PSCR_10BT_EXT_DIST_ENABLE	0x0080	/* 1=Enable Extended
							 * 10BASE-T distance
							 * (Lower 10BASE-T RX
							 * Threshold)
							 * 0=Normal 10BASE-T RX
							 * Threshold
							 */
#घोषणा MII_ATLX_PSCR_MII_5BIT_ENABLE	0x0100	/* 1=5-Bit पूर्णांकerface in
						 * 100BASE-TX
						 * 0=MII पूर्णांकerface in
						 * 100BASE-TX
						 */
#घोषणा MII_ATLX_PSCR_SCRAMBLER_DISABLE	0x0200	/* 1=Scrambler dsbl */
#घोषणा MII_ATLX_PSCR_FORCE_LINK_GOOD	0x0400	/* 1=Force link good */
#घोषणा MII_ATLX_PSCR_ASSERT_CRS_ON_TX	0x0800	/* 1=Assert CRS on Transmit */
#घोषणा MII_ATLX_PSCR_POLARITY_REVERSAL_SHIFT		1
#घोषणा MII_ATLX_PSCR_AUTO_X_MODE_SHIFT			5
#घोषणा MII_ATLX_PSCR_10BT_EXT_DIST_ENABLE_SHIFT	7

/* ATLX PHY Specअगरic Status Register */
#घोषणा MII_ATLX_PSSR_SPD_DPLX_RESOLVED	0x0800	/* 1=Speed & Duplex resolved */
#घोषणा MII_ATLX_PSSR_DPLX		0x2000	/* 1=Duplex 0=Half Duplex */
#घोषणा MII_ATLX_PSSR_SPEED		0xC000	/* Speed, bits 14:15 */
#घोषणा MII_ATLX_PSSR_10MBS		0x0000	/* 00=10Mbs */
#घोषणा MII_ATLX_PSSR_100MBS		0x4000	/* 01=100Mbs */
#घोषणा MII_ATLX_PSSR_1000MBS		0x8000	/* 10=1000Mbs */

#घोषणा MII_DBG_ADDR			0x1D
#घोषणा MII_DBG_DATA			0x1E

/* PCI Command Register Bit Definitions */
#घोषणा PCI_REG_COMMAND			0x04	/* PCI Command Register */
#घोषणा CMD_IO_SPACE			0x0001
#घोषणा CMD_MEMORY_SPACE		0x0002
#घोषणा CMD_BUS_MASTER			0x0004

/* Wake Up Filter Control */
#घोषणा ATLX_WUFC_LNKC	0x00000001	/* Link Status Change Wakeup Enable */
#घोषणा ATLX_WUFC_MAG	0x00000002	/* Magic Packet Wakeup Enable */
#घोषणा ATLX_WUFC_EX	0x00000004	/* Directed Exact Wakeup Enable */
#घोषणा ATLX_WUFC_MC	0x00000008	/* Multicast Wakeup Enable */
#घोषणा ATLX_WUFC_BC	0x00000010	/* Broadcast Wakeup Enable */

#घोषणा ADVERTISE_10_HALF		0x0001
#घोषणा ADVERTISE_10_FULL		0x0002
#घोषणा ADVERTISE_100_HALF		0x0004
#घोषणा ADVERTISE_100_FULL		0x0008
#घोषणा ADVERTISE_1000_HALF		0x0010
#घोषणा ADVERTISE_1000_FULL		0x0020
#घोषणा AUTONEG_ADVERTISE_10_100_ALL	0x000F	/* All 10/100 speeds */
#घोषणा AUTONEG_ADVERTISE_10_ALL	0x0003	/* 10Mbps Full & Half speeds */

#घोषणा PHY_AUTO_NEG_TIME		45	/* 4.5 Seconds */
#घोषणा PHY_FORCE_TIME			20	/* 2.0 Seconds */

/* For checksumming, the sum of all words in the EEPROM should equal 0xBABA */
#घोषणा EEPROM_SUM			0xBABA

काष्ठा atlx_spi_flash_dev अणु
	स्थिर अक्षर *manu_name;	/* manufacturer id */
	/* op-code */
	u8 cmd_wrsr;
	u8 cmd_पढ़ो;
	u8 cmd_program;
	u8 cmd_wren;
	u8 cmd_wrdi;
	u8 cmd_rdsr;
	u8 cmd_rdid;
	u8 cmd_sector_erase;
	u8 cmd_chip_erase;
पूर्ण;

#पूर्ण_अगर /* ATLX_H */
