<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright(c) 2008 - 2009 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित _ATL1C_HW_H_
#घोषणा _ATL1C_HW_H_

#समावेश <linux/types.h>
#समावेश <linux/mii.h>

#घोषणा FIELD_GETX(_x, _name)   ((_x) >> (_name##_SHIFT) & (_name##_MASK))
#घोषणा FIELD_SETX(_x, _name, _v) \
(((_x) & ~((_name##_MASK) << (_name##_SHIFT))) |\
(((_v) & (_name##_MASK)) << (_name##_SHIFT)))
#घोषणा FIELDX(_name, _v) (((_v) & (_name##_MASK)) << (_name##_SHIFT))

काष्ठा atl1c_adapter;
काष्ठा atl1c_hw;

/* function prototype */
व्योम atl1c_phy_disable(काष्ठा atl1c_hw *hw);
व्योम atl1c_hw_set_mac_addr(काष्ठा atl1c_hw *hw, u8 *mac_addr);
पूर्णांक atl1c_phy_reset(काष्ठा atl1c_hw *hw);
पूर्णांक atl1c_पढ़ो_mac_addr(काष्ठा atl1c_hw *hw);
पूर्णांक atl1c_get_speed_and_duplex(काष्ठा atl1c_hw *hw, u16 *speed, u16 *duplex);
u32 atl1c_hash_mc_addr(काष्ठा atl1c_hw *hw, u8 *mc_addr);
व्योम atl1c_hash_set(काष्ठा atl1c_hw *hw, u32 hash_value);
पूर्णांक atl1c_पढ़ो_phy_reg(काष्ठा atl1c_hw *hw, u16 reg_addr, u16 *phy_data);
पूर्णांक atl1c_ग_लिखो_phy_reg(काष्ठा atl1c_hw *hw, u32 reg_addr, u16 phy_data);
bool atl1c_पढ़ो_eeprom(काष्ठा atl1c_hw *hw, u32 offset, u32 *p_value);
पूर्णांक atl1c_phy_init(काष्ठा atl1c_hw *hw);
पूर्णांक atl1c_check_eeprom_exist(काष्ठा atl1c_hw *hw);
पूर्णांक atl1c_restart_स्वतःneg(काष्ठा atl1c_hw *hw);
पूर्णांक atl1c_phy_to_ps_link(काष्ठा atl1c_hw *hw);
पूर्णांक atl1c_घातer_saving(काष्ठा atl1c_hw *hw, u32 wufc);
bool atl1c_रुको_mdio_idle(काष्ठा atl1c_hw *hw);
व्योम atl1c_stop_phy_polling(काष्ठा atl1c_hw *hw);
व्योम atl1c_start_phy_polling(काष्ठा atl1c_hw *hw, u16 clk_sel);
पूर्णांक atl1c_पढ़ो_phy_core(काष्ठा atl1c_hw *hw, bool ext, u8 dev,
			u16 reg, u16 *phy_data);
पूर्णांक atl1c_ग_लिखो_phy_core(काष्ठा atl1c_hw *hw, bool ext, u8 dev,
			u16 reg, u16 phy_data);
पूर्णांक atl1c_पढ़ो_phy_ext(काष्ठा atl1c_hw *hw, u8 dev_addr,
			u16 reg_addr, u16 *phy_data);
पूर्णांक atl1c_ग_लिखो_phy_ext(काष्ठा atl1c_hw *hw, u8 dev_addr,
			u16 reg_addr, u16 phy_data);
पूर्णांक atl1c_पढ़ो_phy_dbg(काष्ठा atl1c_hw *hw, u16 reg_addr, u16 *phy_data);
पूर्णांक atl1c_ग_लिखो_phy_dbg(काष्ठा atl1c_hw *hw, u16 reg_addr, u16 phy_data);
व्योम atl1c_post_phy_linkchg(काष्ठा atl1c_hw *hw, u16 link_speed);

/* hw-ids */
#घोषणा PCI_DEVICE_ID_ATTANSIC_L2C      0x1062
#घोषणा PCI_DEVICE_ID_ATTANSIC_L1C      0x1063
#घोषणा PCI_DEVICE_ID_ATHEROS_L2C_B	0x2060 /* AR8152 v1.1 Fast 10/100 */
#घोषणा PCI_DEVICE_ID_ATHEROS_L2C_B2	0x2062 /* AR8152 v2.0 Fast 10/100 */
#घोषणा PCI_DEVICE_ID_ATHEROS_L1D	0x1073 /* AR8151 v1.0 Gigabit 1000 */
#घोषणा PCI_DEVICE_ID_ATHEROS_L1D_2_0	0x1083 /* AR8151 v2.0 Gigabit 1000 */
#घोषणा L2CB_V10			0xc0
#घोषणा L2CB_V11			0xc1
#घोषणा L2CB_V20			0xc0
#घोषणा L2CB_V21			0xc1

/* रेजिस्टर definition */
#घोषणा REG_DEVICE_CAP              	0x5C
#घोषणा DEVICE_CAP_MAX_PAYLOAD_MASK     0x7
#घोषणा DEVICE_CAP_MAX_PAYLOAD_SHIFT    0

#घोषणा DEVICE_CTRL_MAXRRS_MIN		2

#घोषणा REG_LINK_CTRL			0x68
#घोषणा LINK_CTRL_L0S_EN		0x01
#घोषणा LINK_CTRL_L1_EN			0x02
#घोषणा LINK_CTRL_EXT_SYNC		0x80

#घोषणा REG_PCIE_IND_ACC_ADDR		0x80
#घोषणा REG_PCIE_IND_ACC_DATA		0x84

#घोषणा REG_DEV_SERIALNUM_CTRL		0x200
#घोषणा REG_DEV_MAC_SEL_MASK		0x0 /* 0:EUI; 1:MAC */
#घोषणा REG_DEV_MAC_SEL_SHIFT		0
#घोषणा REG_DEV_SERIAL_NUM_EN_MASK	0x1
#घोषणा REG_DEV_SERIAL_NUM_EN_SHIFT	1

#घोषणा REG_TWSI_CTRL               	0x218
#घोषणा TWSI_CTLR_FREQ_MASK		0x3UL
#घोषणा TWSI_CTRL_FREQ_SHIFT		24
#घोषणा TWSI_CTRL_FREQ_100K		0
#घोषणा TWSI_CTRL_FREQ_200K		1
#घोषणा TWSI_CTRL_FREQ_300K		2
#घोषणा TWSI_CTRL_FREQ_400K		3
#घोषणा TWSI_CTRL_LD_EXIST		BIT(23)
#घोषणा TWSI_CTRL_HW_LDSTAT		BIT(12)	/* 0:finish,1:in progress */
#घोषणा TWSI_CTRL_SW_LDSTART            BIT(11)
#घोषणा TWSI_CTRL_LD_OFFSET_MASK        0xFF
#घोषणा TWSI_CTRL_LD_OFFSET_SHIFT       0

#घोषणा REG_PCIE_DEV_MISC_CTRL      	0x21C
#घोषणा PCIE_DEV_MISC_EXT_PIPE     	0x2
#घोषणा PCIE_DEV_MISC_RETRY_BUFDIS 	0x1
#घोषणा PCIE_DEV_MISC_SPIROM_EXIST 	0x4
#घोषणा PCIE_DEV_MISC_SERDES_ENDIAN    	0x8
#घोषणा PCIE_DEV_MISC_SERDES_SEL_DIN   	0x10

#घोषणा REG_PCIE_PHYMISC	    	0x1000
#घोषणा PCIE_PHYMISC_FORCE_RCV_DET	BIT(2)
#घोषणा PCIE_PHYMISC_NFTS_MASK		0xFFUL
#घोषणा PCIE_PHYMISC_NFTS_SHIFT		16

#घोषणा REG_PCIE_PHYMISC2		0x1004
#घोषणा PCIE_PHYMISC2_L0S_TH_MASK	0x3UL
#घोषणा PCIE_PHYMISC2_L0S_TH_SHIFT	18
#घोषणा L2CB1_PCIE_PHYMISC2_L0S_TH	3
#घोषणा PCIE_PHYMISC2_CDR_BW_MASK	0x3UL
#घोषणा PCIE_PHYMISC2_CDR_BW_SHIFT	16
#घोषणा L2CB1_PCIE_PHYMISC2_CDR_BW	3

#घोषणा REG_TWSI_DEBUG			0x1108
#घोषणा TWSI_DEBUG_DEV_EXIST		BIT(29)

#घोषणा REG_DMA_DBG			0x1114
#घोषणा DMA_DBG_VENDOR_MSG		BIT(0)

#घोषणा REG_EEPROM_CTRL			0x12C0
#घोषणा EEPROM_CTRL_DATA_HI_MASK	0xFFFF
#घोषणा EEPROM_CTRL_DATA_HI_SHIFT	0
#घोषणा EEPROM_CTRL_ADDR_MASK		0x3FF
#घोषणा EEPROM_CTRL_ADDR_SHIFT		16
#घोषणा EEPROM_CTRL_ACK			0x40000000
#घोषणा EEPROM_CTRL_RW			0x80000000

#घोषणा REG_EEPROM_DATA_LO		0x12C4

#घोषणा REG_OTP_CTRL			0x12F0
#घोषणा OTP_CTRL_CLK_EN			BIT(1)

#घोषणा REG_PM_CTRL			0x12F8
#घोषणा PM_CTRL_HOTRST			BIT(31)
#घोषणा PM_CTRL_MAC_ASPM_CHK		BIT(30)	/* L0s/L1 dis by MAC based on
						 * thrghput(setting in 15A0) */
#घोषणा PM_CTRL_SA_DLY_EN		BIT(29)
#घोषणा PM_CTRL_L0S_BUFSRX_EN		BIT(28)
#घोषणा PM_CTRL_LCKDET_TIMER_MASK	0xFUL
#घोषणा PM_CTRL_LCKDET_TIMER_SHIFT	24
#घोषणा PM_CTRL_LCKDET_TIMER_DEF	0xC
#घोषणा PM_CTRL_PM_REQ_TIMER_MASK	0xFUL
#घोषणा PM_CTRL_PM_REQ_TIMER_SHIFT	20	/* pm_request_l1 समय > @
						 * ->L0s not L1 */
#घोषणा PM_CTRL_PM_REQ_TO_DEF		0xF
#घोषणा PMCTRL_TXL1_AFTER_L0S		BIT(19)	/* l1dv2.0+ */
#घोषणा L1D_PMCTRL_L1_ENTRY_TM_MASK	7UL	/* l1dv2.0+, 3bits */
#घोषणा L1D_PMCTRL_L1_ENTRY_TM_SHIFT	16
#घोषणा L1D_PMCTRL_L1_ENTRY_TM_DIS	0
#घोषणा L1D_PMCTRL_L1_ENTRY_TM_2US	1
#घोषणा L1D_PMCTRL_L1_ENTRY_TM_4US	2
#घोषणा L1D_PMCTRL_L1_ENTRY_TM_8US	3
#घोषणा L1D_PMCTRL_L1_ENTRY_TM_16US	4
#घोषणा L1D_PMCTRL_L1_ENTRY_TM_24US	5
#घोषणा L1D_PMCTRL_L1_ENTRY_TM_32US	6
#घोषणा L1D_PMCTRL_L1_ENTRY_TM_63US	7
#घोषणा PM_CTRL_L1_ENTRY_TIMER_MASK	0xFUL  /* l1C 4bits */
#घोषणा PM_CTRL_L1_ENTRY_TIMER_SHIFT	16
#घोषणा L2CB1_PM_CTRL_L1_ENTRY_TM	7
#घोषणा L1C_PM_CTRL_L1_ENTRY_TM		0xF
#घोषणा PM_CTRL_RCVR_WT_TIMER		BIT(15)	/* 1:1us, 0:2ms */
#घोषणा PM_CTRL_CLK_PWM_VER1_1		BIT(14)	/* 0:1.0a,1:1.1 */
#घोषणा PM_CTRL_CLK_SWH_L1		BIT(13)	/* en pcie clk sw in L1 */
#घोषणा PM_CTRL_ASPM_L0S_EN		BIT(12)
#घोषणा PM_CTRL_RXL1_AFTER_L0S		BIT(11)	/* l1dv2.0+ */
#घोषणा L1D_PMCTRL_L0S_TIMER_MASK	7UL	/* l1d2.0+, 3bits*/
#घोषणा L1D_PMCTRL_L0S_TIMER_SHIFT	8
#घोषणा PM_CTRL_L0S_ENTRY_TIMER_MASK	0xFUL	/* l1c, 4bits */
#घोषणा PM_CTRL_L0S_ENTRY_TIMER_SHIFT	8
#घोषणा PM_CTRL_SERDES_BUFS_RX_L1_EN	BIT(7)
#घोषणा PM_CTRL_SERDES_PD_EX_L1		BIT(6)	/* घातer करोwn serdes rx */
#घोषणा PM_CTRL_SERDES_PLL_L1_EN	BIT(5)
#घोषणा PM_CTRL_SERDES_L1_EN		BIT(4)
#घोषणा PM_CTRL_ASPM_L1_EN		BIT(3)
#घोषणा PM_CTRL_CLK_REQ_EN		BIT(2)
#घोषणा PM_CTRL_RBER_EN			BIT(1)
#घोषणा PM_CTRL_SPRSDWER_EN		BIT(0)

#घोषणा REG_LTSSM_ID_CTRL		0x12FC
#घोषणा LTSSM_ID_EN_WRO			0x1000


/* Selene Master Control Register */
#घोषणा REG_MASTER_CTRL			0x1400
#घोषणा MASTER_CTRL_OTP_SEL		BIT(31)
#घोषणा MASTER_DEV_NUM_MASK		0x7FUL
#घोषणा MASTER_DEV_NUM_SHIFT		24
#घोषणा MASTER_REV_NUM_MASK		0xFFUL
#घोषणा MASTER_REV_NUM_SHIFT		16
#घोषणा MASTER_CTRL_INT_RDCLR		BIT(14)
#घोषणा MASTER_CTRL_CLK_SEL_DIS		BIT(12)	/* 1:alwys sel pclk from
						 * serdes, not sw to 25M */
#घोषणा MASTER_CTRL_RX_ITIMER_EN	BIT(11)	/* IRQ MODURATION FOR RX */
#घोषणा MASTER_CTRL_TX_ITIMER_EN	BIT(10)	/* MODURATION FOR TX/RX */
#घोषणा MASTER_CTRL_MANU_INT		BIT(9)	/* SOFT MANUAL INT */
#घोषणा MASTER_CTRL_MANUTIMER_EN	BIT(8)
#घोषणा MASTER_CTRL_SA_TIMER_EN		BIT(7)	/* SYS ALIVE TIMER EN */
#घोषणा MASTER_CTRL_OOB_DIS		BIT(6)	/* OUT OF BOX DIS */
#घोषणा MASTER_CTRL_WAKEN_25M		BIT(5)	/* WAKE WO. PCIE CLK */
#घोषणा MASTER_CTRL_BERT_START		BIT(4)
#घोषणा MASTER_PCIE_TSTMOD_MASK		3UL
#घोषणा MASTER_PCIE_TSTMOD_SHIFT	2
#घोषणा MASTER_PCIE_RST			BIT(1)
#घोषणा MASTER_CTRL_SOFT_RST		BIT(0)	/* RST MAC & DMA */
#घोषणा DMA_MAC_RST_TO			50

/* Timer Initial Value Register */
#घोषणा REG_MANUAL_TIMER_INIT       	0x1404

/* IRQ ModeratorTimer Initial Value Register */
#घोषणा REG_IRQ_MODRT_TIMER_INIT     	0x1408
#घोषणा IRQ_MODRT_TIMER_MASK		0xffff
#घोषणा IRQ_MODRT_TX_TIMER_SHIFT    	0
#घोषणा IRQ_MODRT_RX_TIMER_SHIFT	16

#घोषणा REG_GPHY_CTRL               	0x140C
#घोषणा GPHY_CTRL_ADDR_MASK		0x1FUL
#घोषणा GPHY_CTRL_ADDR_SHIFT		19
#घोषणा GPHY_CTRL_BP_VLTGSW		BIT(18)
#घोषणा GPHY_CTRL_100AB_EN		BIT(17)
#घोषणा GPHY_CTRL_10AB_EN		BIT(16)
#घोषणा GPHY_CTRL_PHY_PLL_BYPASS	BIT(15)
#घोषणा GPHY_CTRL_PWDOWN_HW		BIT(14)	/* affect MAC&PHY, to low pw */
#घोषणा GPHY_CTRL_PHY_PLL_ON		BIT(13)	/* 1:pll always on, 0:can sw */
#घोषणा GPHY_CTRL_SEL_ANA_RST		BIT(12)
#घोषणा GPHY_CTRL_HIB_PULSE		BIT(11)
#घोषणा GPHY_CTRL_HIB_EN		BIT(10)
#घोषणा GPHY_CTRL_GIGA_DIS		BIT(9)
#घोषणा GPHY_CTRL_PHY_IDDQ_DIS		BIT(8)	/* pw on RST */
#घोषणा GPHY_CTRL_PHY_IDDQ		BIT(7)	/* bit8 affect bit7 जबतक rb */
#घोषणा GPHY_CTRL_LPW_EXIT		BIT(6)
#घोषणा GPHY_CTRL_GATE_25M_EN		BIT(5)
#घोषणा GPHY_CTRL_REV_ANEG		BIT(4)
#घोषणा GPHY_CTRL_ANEG_NOW		BIT(3)
#घोषणा GPHY_CTRL_LED_MODE		BIT(2)
#घोषणा GPHY_CTRL_RTL_MODE		BIT(1)
#घोषणा GPHY_CTRL_EXT_RESET		BIT(0)	/* 1:out of DSP RST status */
#घोषणा GPHY_CTRL_EXT_RST_TO		80	/* 800us aपंचांगost */
#घोषणा GPHY_CTRL_CLS			(\
	GPHY_CTRL_LED_MODE		|\
	GPHY_CTRL_100AB_EN		|\
	GPHY_CTRL_PHY_PLL_ON)

/* Block IDLE Status Register */
#घोषणा REG_IDLE_STATUS			0x1410
#घोषणा IDLE_STATUS_SFORCE_MASK		0xFUL
#घोषणा IDLE_STATUS_SFORCE_SHIFT	14
#घोषणा IDLE_STATUS_CALIB_DONE		BIT(13)
#घोषणा IDLE_STATUS_CALIB_RES_MASK	0x1FUL
#घोषणा IDLE_STATUS_CALIB_RES_SHIFT	8
#घोषणा IDLE_STATUS_CALIBERR_MASK	0xFUL
#घोषणा IDLE_STATUS_CALIBERR_SHIFT	4
#घोषणा IDLE_STATUS_TXQ_BUSY		BIT(3)
#घोषणा IDLE_STATUS_RXQ_BUSY		BIT(2)
#घोषणा IDLE_STATUS_TXMAC_BUSY		BIT(1)
#घोषणा IDLE_STATUS_RXMAC_BUSY		BIT(0)
#घोषणा IDLE_STATUS_MASK		(\
	IDLE_STATUS_TXQ_BUSY		|\
	IDLE_STATUS_RXQ_BUSY		|\
	IDLE_STATUS_TXMAC_BUSY		|\
	IDLE_STATUS_RXMAC_BUSY)

/* MDIO Control Register */
#घोषणा REG_MDIO_CTRL           	0x1414
#घोषणा MDIO_CTRL_MODE_EXT		BIT(30)
#घोषणा MDIO_CTRL_POST_READ		BIT(29)
#घोषणा MDIO_CTRL_AP_EN			BIT(28)
#घोषणा MDIO_CTRL_BUSY			BIT(27)
#घोषणा MDIO_CTRL_CLK_SEL_MASK		0x7UL
#घोषणा MDIO_CTRL_CLK_SEL_SHIFT		24
#घोषणा MDIO_CTRL_CLK_25_4		0	/* 25MHz भागide 4 */
#घोषणा MDIO_CTRL_CLK_25_6		2
#घोषणा MDIO_CTRL_CLK_25_8		3
#घोषणा MDIO_CTRL_CLK_25_10		4
#घोषणा MDIO_CTRL_CLK_25_32		5
#घोषणा MDIO_CTRL_CLK_25_64		6
#घोषणा MDIO_CTRL_CLK_25_128		7
#घोषणा MDIO_CTRL_START			BIT(23)
#घोषणा MDIO_CTRL_SPRES_PRMBL		BIT(22)
#घोषणा MDIO_CTRL_OP_READ		BIT(21)	/* 1:पढ़ो, 0:ग_लिखो */
#घोषणा MDIO_CTRL_REG_MASK		0x1FUL
#घोषणा MDIO_CTRL_REG_SHIFT		16
#घोषणा MDIO_CTRL_DATA_MASK		0xFFFFUL
#घोषणा MDIO_CTRL_DATA_SHIFT		0
#घोषणा MDIO_MAX_AC_TO			120	/* 1.2ms समयout क्रम slow clk */

/* क्रम extension reg access */
#घोषणा REG_MDIO_EXTN			0x1448
#घोषणा MDIO_EXTN_PORTAD_MASK		0x1FUL
#घोषणा MDIO_EXTN_PORTAD_SHIFT		21
#घोषणा MDIO_EXTN_DEVAD_MASK		0x1FUL
#घोषणा MDIO_EXTN_DEVAD_SHIFT		16
#घोषणा MDIO_EXTN_REG_MASK		0xFFFFUL
#घोषणा MDIO_EXTN_REG_SHIFT		0

/* BIST Control and Status Register0 (क्रम the Packet Memory) */
#घोषणा REG_BIST0_CTRL              	0x141c
#घोषणा BIST0_NOW                   	0x1
#घोषणा BIST0_SRAM_FAIL             	0x2 /* 1: The SRAM failure is
					     * un-repairable  because
					     * it has address decoder
					     * failure or more than 1 cell
					     * stuck-to-x failure */
#घोषणा BIST0_FUSE_FLAG             	0x4

/* BIST Control and Status Register1(क्रम the retry buffer of PCI Express) */
#घोषणा REG_BIST1_CTRL			0x1420
#घोषणा BIST1_NOW                   	0x1
#घोषणा BIST1_SRAM_FAIL             	0x2
#घोषणा BIST1_FUSE_FLAG             	0x4

/* SerDes Lock Detect Control and Status Register */
#घोषणा REG_SERDES			0x1424
#घोषणा SERDES_PHY_CLK_SLOWDOWN		BIT(18)
#घोषणा SERDES_MAC_CLK_SLOWDOWN		BIT(17)
#घोषणा SERDES_SELFB_PLL_MASK		0x3UL
#घोषणा SERDES_SELFB_PLL_SHIFT		14
#घोषणा SERDES_PHYCLK_SEL_GTX		BIT(13)	/* 1:gtx_clk, 0:25M */
#घोषणा SERDES_PCIECLK_SEL_SRDS		BIT(12)	/* 1:serdes,0:25M */
#घोषणा SERDES_BUFS_RX_EN		BIT(11)
#घोषणा SERDES_PD_RX			BIT(10)
#घोषणा SERDES_PLL_EN			BIT(9)
#घोषणा SERDES_EN			BIT(8)
#घोषणा SERDES_SELFB_PLL_SEL_CSR	BIT(6)	/* 0:state-machine,1:csr */
#घोषणा SERDES_SELFB_PLL_CSR_MASK	0x3UL
#घोषणा SERDES_SELFB_PLL_CSR_SHIFT	4
#घोषणा SERDES_SELFB_PLL_CSR_4		3	/* 4-12% OV-CLK */
#घोषणा SERDES_SELFB_PLL_CSR_0		2	/* 0-4% OV-CLK */
#घोषणा SERDES_SELFB_PLL_CSR_12		1	/* 12-18% OV-CLK */
#घोषणा SERDES_SELFB_PLL_CSR_18		0	/* 18-25% OV-CLK */
#घोषणा SERDES_VCO_SLOW			BIT(3)
#घोषणा SERDES_VCO_FAST			BIT(2)
#घोषणा SERDES_LOCK_DETECT_EN		BIT(1)
#घोषणा SERDES_LOCK_DETECT		BIT(0)

#घोषणा REG_LPI_DECISN_TIMER            0x143C
#घोषणा L2CB_LPI_DESISN_TIMER		0x7D00

#घोषणा REG_LPI_CTRL                    0x1440
#घोषणा LPI_CTRL_CHK_DA			BIT(31)
#घोषणा LPI_CTRL_ENH_TO_MASK		0x1FFFUL
#घोषणा LPI_CTRL_ENH_TO_SHIFT		12
#घोषणा LPI_CTRL_ENH_TH_MASK		0x1FUL
#घोषणा LPI_CTRL_ENH_TH_SHIFT		6
#घोषणा LPI_CTRL_ENH_EN			BIT(5)
#घोषणा LPI_CTRL_CHK_RX			BIT(4)
#घोषणा LPI_CTRL_CHK_STATE		BIT(3)
#घोषणा LPI_CTRL_GMII			BIT(2)
#घोषणा LPI_CTRL_TO_PHY			BIT(1)
#घोषणा LPI_CTRL_EN			BIT(0)

#घोषणा REG_LPI_WAIT			0x1444
#घोषणा LPI_WAIT_TIMER_MASK		0xFFFFUL
#घोषणा LPI_WAIT_TIMER_SHIFT		0

/* MAC Control Register  */
#घोषणा REG_MAC_CTRL         		0x1480
#घोषणा MAC_CTRL_SPEED_MODE_SW		BIT(30) /* 0:phy,1:sw */
#घोषणा MAC_CTRL_HASH_ALG_CRC32		BIT(29) /* 1:legacy,0:lw_5b */
#घोषणा MAC_CTRL_SINGLE_PAUSE_EN	BIT(28)
#घोषणा MAC_CTRL_DBG			BIT(27)
#घोषणा MAC_CTRL_BC_EN			BIT(26)
#घोषणा MAC_CTRL_MC_ALL_EN		BIT(25)
#घोषणा MAC_CTRL_RX_CHKSUM_EN		BIT(24)
#घोषणा MAC_CTRL_TX_HUGE		BIT(23)
#घोषणा MAC_CTRL_DBG_TX_BKPRESURE	BIT(22)
#घोषणा MAC_CTRL_SPEED_MASK		3UL
#घोषणा MAC_CTRL_SPEED_SHIFT		20
#घोषणा MAC_CTRL_SPEED_10_100		1
#घोषणा MAC_CTRL_SPEED_1000		2
#घोषणा MAC_CTRL_TX_SIMURST		BIT(19)
#घोषणा MAC_CTRL_SCNT			BIT(17)
#घोषणा MAC_CTRL_TX_PAUSE		BIT(16)
#घोषणा MAC_CTRL_PROMIS_EN		BIT(15)
#घोषणा MAC_CTRL_RMV_VLAN		BIT(14)
#घोषणा MAC_CTRL_PRMLEN_MASK		0xFUL
#घोषणा MAC_CTRL_PRMLEN_SHIFT		10
#घोषणा MAC_CTRL_HUGE_EN		BIT(9)
#घोषणा MAC_CTRL_LENCHK			BIT(8)
#घोषणा MAC_CTRL_PAD			BIT(7)
#घोषणा MAC_CTRL_ADD_CRC		BIT(6)
#घोषणा MAC_CTRL_DUPLX			BIT(5)
#घोषणा MAC_CTRL_LOOPBACK		BIT(4)
#घोषणा MAC_CTRL_RX_FLOW		BIT(3)
#घोषणा MAC_CTRL_TX_FLOW		BIT(2)
#घोषणा MAC_CTRL_RX_EN			BIT(1)
#घोषणा MAC_CTRL_TX_EN			BIT(0)

/* MAC IPG/IFG Control Register  */
#घोषणा REG_MAC_IPG_IFG             	0x1484
#घोषणा MAC_IPG_IFG_IPGT_SHIFT      	0 	/* Desired back to back
						 * पूर्णांकer-packet gap. The
						 * शेष is 96-bit समय */
#घोषणा MAC_IPG_IFG_IPGT_MASK       	0x7f
#घोषणा MAC_IPG_IFG_MIFG_SHIFT      	8       /* Minimum number of IFG to
						 * enक्रमce in between RX frames */
#घोषणा MAC_IPG_IFG_MIFG_MASK       	0xff  	/* Frame gap below such IFP is dropped */
#घोषणा MAC_IPG_IFG_IPGR1_SHIFT     	16   	/* 64bit Carrier-Sense winकरोw */
#घोषणा MAC_IPG_IFG_IPGR1_MASK      	0x7f
#घोषणा MAC_IPG_IFG_IPGR2_SHIFT     	24    	/* 96-bit IPG winकरोw */
#घोषणा MAC_IPG_IFG_IPGR2_MASK      	0x7f

/* MAC STATION ADDRESS  */
#घोषणा REG_MAC_STA_ADDR		0x1488

/* Hash table क्रम multicast address */
#घोषणा REG_RX_HASH_TABLE		0x1490

/* MAC Half-Duplex Control Register */
#घोषणा REG_MAC_HALF_DUPLX_CTRL     	0x1498
#घोषणा MAC_HALF_DUPLX_CTRL_LCOL_SHIFT  0      /* Collision Winकरोw */
#घोषणा MAC_HALF_DUPLX_CTRL_LCOL_MASK   0x3ff
#घोषणा MAC_HALF_DUPLX_CTRL_RETRY_SHIFT 12
#घोषणा MAC_HALF_DUPLX_CTRL_RETRY_MASK  0xf
#घोषणा MAC_HALF_DUPLX_CTRL_EXC_DEF_EN  0x10000
#घोषणा MAC_HALF_DUPLX_CTRL_NO_BACK_C   0x20000
#घोषणा MAC_HALF_DUPLX_CTRL_NO_BACK_P   0x40000 /* No back-off on backpressure,
						 * immediately start the
						 * transmission after back pressure */
#घोषणा MAC_HALF_DUPLX_CTRL_ABEBE        0x80000 /* 1: Alternative Binary Exponential Back-off Enabled */
#घोषणा MAC_HALF_DUPLX_CTRL_ABEBT_SHIFT  20      /* Maximum binary exponential number */
#घोषणा MAC_HALF_DUPLX_CTRL_ABEBT_MASK   0xf
#घोषणा MAC_HALF_DUPLX_CTRL_JAMIPG_SHIFT 24      /* IPG to start JAM क्रम collision based flow control in half-duplex */
#घोषणा MAC_HALF_DUPLX_CTRL_JAMIPG_MASK  0xf     /* mode. In unit of 8-bit समय */

/* Maximum Frame Length Control Register   */
#घोषणा REG_MTU                     	0x149c

/* Wake-On-Lan control रेजिस्टर */
#घोषणा REG_WOL_CTRL                	0x14a0
#घोषणा WOL_PT7_MATCH			BIT(31)
#घोषणा WOL_PT6_MATCH			BIT(30)
#घोषणा WOL_PT5_MATCH			BIT(29)
#घोषणा WOL_PT4_MATCH			BIT(28)
#घोषणा WOL_PT3_MATCH			BIT(27)
#घोषणा WOL_PT2_MATCH			BIT(26)
#घोषणा WOL_PT1_MATCH			BIT(25)
#घोषणा WOL_PT0_MATCH			BIT(24)
#घोषणा WOL_PT7_EN			BIT(23)
#घोषणा WOL_PT6_EN			BIT(22)
#घोषणा WOL_PT5_EN			BIT(21)
#घोषणा WOL_PT4_EN			BIT(20)
#घोषणा WOL_PT3_EN			BIT(19)
#घोषणा WOL_PT2_EN			BIT(18)
#घोषणा WOL_PT1_EN			BIT(17)
#घोषणा WOL_PT0_EN			BIT(16)
#घोषणा WOL_LNKCHG_ST			BIT(10)
#घोषणा WOL_MAGIC_ST			BIT(9)
#घोषणा WOL_PATTERN_ST			BIT(8)
#घोषणा WOL_OOB_EN			BIT(6)
#घोषणा WOL_LINK_CHG_PME_EN		BIT(5)
#घोषणा WOL_LINK_CHG_EN			BIT(4)
#घोषणा WOL_MAGIC_PME_EN		BIT(3)
#घोषणा WOL_MAGIC_EN			BIT(2)
#घोषणा WOL_PATTERN_PME_EN		BIT(1)
#घोषणा WOL_PATTERN_EN			BIT(0)

/* WOL Length ( 2 DWORD ) */
#घोषणा REG_WOL_PTLEN1			0x14A4
#घोषणा WOL_PTLEN1_3_MASK		0xFFUL
#घोषणा WOL_PTLEN1_3_SHIFT		24
#घोषणा WOL_PTLEN1_2_MASK		0xFFUL
#घोषणा WOL_PTLEN1_2_SHIFT		16
#घोषणा WOL_PTLEN1_1_MASK		0xFFUL
#घोषणा WOL_PTLEN1_1_SHIFT		8
#घोषणा WOL_PTLEN1_0_MASK		0xFFUL
#घोषणा WOL_PTLEN1_0_SHIFT		0

#घोषणा REG_WOL_PTLEN2			0x14A8
#घोषणा WOL_PTLEN2_7_MASK		0xFFUL
#घोषणा WOL_PTLEN2_7_SHIFT		24
#घोषणा WOL_PTLEN2_6_MASK		0xFFUL
#घोषणा WOL_PTLEN2_6_SHIFT		16
#घोषणा WOL_PTLEN2_5_MASK		0xFFUL
#घोषणा WOL_PTLEN2_5_SHIFT		8
#घोषणा WOL_PTLEN2_4_MASK		0xFFUL
#घोषणा WOL_PTLEN2_4_SHIFT		0

/* Internal SRAM Partition Register */
#घोषणा RFDX_HEAD_ADDR_MASK		0x03FF
#घोषणा RFDX_HARD_ADDR_SHIFT		0
#घोषणा RFDX_TAIL_ADDR_MASK		0x03FF
#घोषणा RFDX_TAIL_ADDR_SHIFT            16

#घोषणा REG_SRAM_RFD0_INFO		0x1500
#घोषणा REG_SRAM_RFD1_INFO		0x1504
#घोषणा REG_SRAM_RFD2_INFO		0x1508
#घोषणा	REG_SRAM_RFD3_INFO		0x150C

#घोषणा REG_RFD_NIC_LEN			0x1510 /* In 8-bytes */
#घोषणा RFD_NIC_LEN_MASK		0x03FF

#घोषणा REG_SRAM_TRD_ADDR           	0x1518
#घोषणा TPD_HEAD_ADDR_MASK		0x03FF
#घोषणा TPD_HEAD_ADDR_SHIFT		0
#घोषणा TPD_TAIL_ADDR_MASK		0x03FF
#घोषणा TPD_TAIL_ADDR_SHIFT		16

#घोषणा REG_SRAM_TRD_LEN            	0x151C /* In 8-bytes */
#घोषणा TPD_NIC_LEN_MASK		0x03FF

#घोषणा REG_SRAM_RXF_ADDR          	0x1520
#घोषणा REG_SRAM_RXF_LEN            	0x1524
#घोषणा REG_SRAM_TXF_ADDR           	0x1528
#घोषणा REG_SRAM_TXF_LEN            	0x152C
#घोषणा REG_SRAM_TCPH_ADDR          	0x1530
#घोषणा REG_SRAM_PKTH_ADDR          	0x1532

/*
 * Load Ptr Register
 * Software sets this bit after the initialization of the head and tail */
#घोषणा REG_LOAD_PTR                	0x1534

/*
 * addresses of all descriptors, as well as the following descriptor
 * control रेजिस्टर, which triggers each function block to load the head
 * poपूर्णांकer to prepare क्रम the operation. This bit is then self-cleared
 * after one cycle.
 */
#घोषणा REG_RX_BASE_ADDR_HI		0x1540
#घोषणा REG_TX_BASE_ADDR_HI		0x1544
#घोषणा REG_RFD0_HEAD_ADDR_LO		0x1550
#घोषणा REG_RFD_RING_SIZE		0x1560
#घोषणा RFD_RING_SIZE_MASK		0x0FFF
#घोषणा REG_RX_BUF_SIZE			0x1564
#घोषणा RX_BUF_SIZE_MASK		0xFFFF
#घोषणा REG_RRD0_HEAD_ADDR_LO		0x1568
#घोषणा REG_RRD_RING_SIZE		0x1578
#घोषणा RRD_RING_SIZE_MASK		0x0FFF
#घोषणा REG_TPD_PRI1_ADDR_LO		0x157C
#घोषणा REG_TPD_PRI0_ADDR_LO		0x1580
#घोषणा REG_TPD_RING_SIZE		0x1584
#घोषणा TPD_RING_SIZE_MASK		0xFFFF

/* TXQ Control Register */
#घोषणा REG_TXQ_CTRL			0x1590
#घोषणा TXQ_TXF_BURST_NUM_MASK          0xFFFFUL
#घोषणा TXQ_TXF_BURST_NUM_SHIFT		16
#घोषणा L1C_TXQ_TXF_BURST_PREF          0x200
#घोषणा L2CB_TXQ_TXF_BURST_PREF         0x40
#घोषणा TXQ_CTRL_PEDING_CLR             BIT(8)
#घोषणा TXQ_CTRL_LS_8023_EN             BIT(7)
#घोषणा TXQ_CTRL_ENH_MODE               BIT(6)
#घोषणा TXQ_CTRL_EN                     BIT(5)
#घोषणा TXQ_CTRL_IP_OPTION_EN           BIT(4)
#घोषणा TXQ_NUM_TPD_BURST_MASK          0xFUL
#घोषणा TXQ_NUM_TPD_BURST_SHIFT         0
#घोषणा TXQ_NUM_TPD_BURST_DEF           5
#घोषणा TXQ_CFGV			(\
	FIELDX(TXQ_NUM_TPD_BURST, TXQ_NUM_TPD_BURST_DEF) |\
	TXQ_CTRL_ENH_MODE |\
	TXQ_CTRL_LS_8023_EN |\
	TXQ_CTRL_IP_OPTION_EN)
#घोषणा L1C_TXQ_CFGV			(\
	TXQ_CFGV |\
	FIELDX(TXQ_TXF_BURST_NUM, L1C_TXQ_TXF_BURST_PREF))
#घोषणा L2CB_TXQ_CFGV			(\
	TXQ_CFGV |\
	FIELDX(TXQ_TXF_BURST_NUM, L2CB_TXQ_TXF_BURST_PREF))


/* Jumbo packet Threshold क्रम task offload */
#घोषणा REG_TX_TSO_OFFLOAD_THRESH	0x1594 /* In 8-bytes */
#घोषणा TX_TSO_OFFLOAD_THRESH_MASK	0x07FF
#घोषणा MAX_TSO_FRAME_SIZE		(7*1024)

#घोषणा	REG_TXF_WATER_MARK		0x1598 /* In 8-bytes */
#घोषणा TXF_WATER_MARK_MASK		0x0FFF
#घोषणा TXF_LOW_WATER_MARK_SHIFT	0
#घोषणा TXF_HIGH_WATER_MARK_SHIFT 	16
#घोषणा TXQ_CTRL_BURST_MODE_EN		0x80000000

#घोषणा REG_THRUPUT_MON_CTRL		0x159C
#घोषणा THRUPUT_MON_RATE_MASK		0x3
#घोषणा THRUPUT_MON_RATE_SHIFT		0
#घोषणा THRUPUT_MON_EN			0x80

/* RXQ Control Register */
#घोषणा REG_RXQ_CTRL                	0x15A0
#घोषणा ASPM_THRUPUT_LIMIT_MASK		0x3
#घोषणा ASPM_THRUPUT_LIMIT_SHIFT	0
#घोषणा ASPM_THRUPUT_LIMIT_NO		0x00
#घोषणा ASPM_THRUPUT_LIMIT_1M		0x01
#घोषणा ASPM_THRUPUT_LIMIT_10M		0x02
#घोषणा ASPM_THRUPUT_LIMIT_100M		0x03
#घोषणा IPV6_CHKSUM_CTRL_EN		BIT(7)
#घोषणा RXQ_RFD_BURST_NUM_MASK		0x003F
#घोषणा RXQ_RFD_BURST_NUM_SHIFT		20
#घोषणा RXQ_NUM_RFD_PREF_DEF		8
#घोषणा RSS_MODE_MASK			3UL
#घोषणा RSS_MODE_SHIFT			26
#घोषणा RSS_MODE_DIS			0
#घोषणा RSS_MODE_SQSI			1
#घोषणा RSS_MODE_MQSI			2
#घोषणा RSS_MODE_MQMI			3
#घोषणा RSS_NIP_QUEUE_SEL		BIT(28) /* 0:q0, 1:table */
#घोषणा RRS_HASH_CTRL_EN		BIT(29)
#घोषणा RX_CUT_THRU_EN			BIT(30)
#घोषणा RXQ_CTRL_EN			BIT(31)

#घोषणा REG_RFD_FREE_THRESH		0x15A4
#घोषणा RFD_FREE_THRESH_MASK		0x003F
#घोषणा RFD_FREE_HI_THRESH_SHIFT	0
#घोषणा RFD_FREE_LO_THRESH_SHIFT	6

/* RXF flow control रेजिस्टर */
#घोषणा REG_RXQ_RXF_PAUSE_THRESH    	0x15A8
#घोषणा RXQ_RXF_PAUSE_TH_HI_SHIFT       0
#घोषणा RXQ_RXF_PAUSE_TH_HI_MASK        0x0FFF
#घोषणा RXQ_RXF_PAUSE_TH_LO_SHIFT       16
#घोषणा RXQ_RXF_PAUSE_TH_LO_MASK        0x0FFF

#घोषणा REG_RXD_DMA_CTRL		0x15AC
#घोषणा RXD_DMA_THRESH_MASK		0x0FFF	/* In 8-bytes */
#घोषणा RXD_DMA_THRESH_SHIFT		0
#घोषणा RXD_DMA_DOWN_TIMER_MASK		0xFFFF
#घोषणा RXD_DMA_DOWN_TIMER_SHIFT	16

/* DMA Engine Control Register */
#घोषणा REG_DMA_CTRL			0x15C0
#घोषणा DMA_CTRL_SMB_NOW                BIT(31)
#घोषणा DMA_CTRL_WPEND_CLR              BIT(30)
#घोषणा DMA_CTRL_RPEND_CLR              BIT(29)
#घोषणा DMA_CTRL_WDLY_CNT_MASK          0xFUL
#घोषणा DMA_CTRL_WDLY_CNT_SHIFT         16
#घोषणा DMA_CTRL_WDLY_CNT_DEF           4
#घोषणा DMA_CTRL_RDLY_CNT_MASK          0x1FUL
#घोषणा DMA_CTRL_RDLY_CNT_SHIFT         11
#घोषणा DMA_CTRL_RDLY_CNT_DEF           15
#घोषणा DMA_CTRL_RREQ_PRI_DATA          BIT(10)      /* 0:tpd, 1:data */
#घोषणा DMA_CTRL_WREQ_BLEN_MASK         7UL
#घोषणा DMA_CTRL_WREQ_BLEN_SHIFT        7
#घोषणा DMA_CTRL_RREQ_BLEN_MASK         7UL
#घोषणा DMA_CTRL_RREQ_BLEN_SHIFT        4
#घोषणा L1C_CTRL_DMA_RCB_LEN128         BIT(3)   /* 0:64bytes,1:128bytes */
#घोषणा DMA_CTRL_RORDER_MODE_MASK       7UL
#घोषणा DMA_CTRL_RORDER_MODE_SHIFT      0
#घोषणा DMA_CTRL_RORDER_MODE_OUT        4
#घोषणा DMA_CTRL_RORDER_MODE_ENHANCE    2
#घोषणा DMA_CTRL_RORDER_MODE_IN         1

/* INT-triggle/SMB Control Register */
#घोषणा REG_SMB_STAT_TIMER		0x15C4	/* 2us resolution */
#घोषणा SMB_STAT_TIMER_MASK		0xFFFFFF
#घोषणा REG_TINT_TPD_THRESH             0x15C8 /* tpd th to trig पूर्णांकrrupt */

/* Mail box */
#घोषणा MB_RFDX_PROD_IDX_MASK		0xFFFF
#घोषणा REG_MB_RFD0_PROD_IDX		0x15E0

#घोषणा REG_TPD_PRI1_PIDX               0x15F0	/* 16bit,hi-tpd producer idx */
#घोषणा REG_TPD_PRI0_PIDX		0x15F2	/* 16bit,lo-tpd producer idx */
#घोषणा REG_TPD_PRI1_CIDX		0x15F4	/* 16bit,hi-tpd consumer idx */
#घोषणा REG_TPD_PRI0_CIDX		0x15F6	/* 16bit,lo-tpd consumer idx */

#घोषणा REG_MB_RFD01_CONS_IDX		0x15F8
#घोषणा MB_RFD0_CONS_IDX_MASK		0x0000FFFF
#घोषणा MB_RFD1_CONS_IDX_MASK		0xFFFF0000

/* Interrupt Status Register */
#घोषणा REG_ISR    			0x1600
#घोषणा ISR_SMB				0x00000001
#घोषणा ISR_TIMER			0x00000002
/*
 * Software manual पूर्णांकerrupt, क्रम debug. Set when SW_MAN_INT_EN is set
 * in Table 51 Selene Master Control Register (Offset 0x1400).
 */
#घोषणा ISR_MANUAL         		0x00000004
#घोषणा ISR_HW_RXF_OV          		0x00000008 /* RXF overflow पूर्णांकerrupt */
#घोषणा ISR_RFD0_UR			0x00000010 /* RFD0 under run */
#घोषणा ISR_RFD1_UR			0x00000020
#घोषणा ISR_RFD2_UR			0x00000040
#घोषणा ISR_RFD3_UR			0x00000080
#घोषणा ISR_TXF_UR			0x00000100
#घोषणा ISR_DMAR_TO_RST			0x00000200
#घोषणा ISR_DMAW_TO_RST			0x00000400
#घोषणा ISR_TX_CREDIT			0x00000800
#घोषणा ISR_GPHY			0x00001000
/* GPHY low घातer state पूर्णांकerrupt */
#घोषणा ISR_GPHY_LPW           		0x00002000
#घोषणा ISR_TXQ_TO_RST			0x00004000
#घोषणा ISR_TX_PKT			0x00008000
#घोषणा ISR_RX_PKT_0			0x00010000
#घोषणा ISR_RX_PKT_1			0x00020000
#घोषणा ISR_RX_PKT_2			0x00040000
#घोषणा ISR_RX_PKT_3			0x00080000
#घोषणा ISR_MAC_RX			0x00100000
#घोषणा ISR_MAC_TX			0x00200000
#घोषणा ISR_UR_DETECTED			0x00400000
#घोषणा ISR_FERR_DETECTED		0x00800000
#घोषणा ISR_NFERR_DETECTED		0x01000000
#घोषणा ISR_CERR_DETECTED		0x02000000
#घोषणा ISR_PHY_LINKDOWN		0x04000000
#घोषणा ISR_DIS_INT			0x80000000

/* Interrupt Mask Register */
#घोषणा REG_IMR				0x1604

#घोषणा IMR_NORMAL_MASK		(\
		ISR_MANUAL	|\
		ISR_HW_RXF_OV	|\
		ISR_RFD0_UR	|\
		ISR_TXF_UR	|\
		ISR_DMAR_TO_RST	|\
		ISR_TXQ_TO_RST  |\
		ISR_DMAW_TO_RST	|\
		ISR_GPHY	|\
		ISR_TX_PKT	|\
		ISR_RX_PKT_0	|\
		ISR_GPHY_LPW    |\
		ISR_PHY_LINKDOWN)

#घोषणा ISR_RX_PKT 	(\
	ISR_RX_PKT_0    |\
	ISR_RX_PKT_1    |\
	ISR_RX_PKT_2    |\
	ISR_RX_PKT_3)

#घोषणा ISR_OVER	(\
	ISR_RFD0_UR 	|\
	ISR_RFD1_UR	|\
	ISR_RFD2_UR	|\
	ISR_RFD3_UR	|\
	ISR_HW_RXF_OV	|\
	ISR_TXF_UR)

#घोषणा ISR_ERROR	(\
	ISR_DMAR_TO_RST	|\
	ISR_TXQ_TO_RST  |\
	ISR_DMAW_TO_RST	|\
	ISR_PHY_LINKDOWN)

#घोषणा REG_INT_RETRIG_TIMER		0x1608
#घोषणा INT_RETRIG_TIMER_MASK		0xFFFF

#घोषणा REG_MAC_RX_STATUS_BIN 		0x1700
#घोषणा REG_MAC_RX_STATUS_END 		0x175c
#घोषणा REG_MAC_TX_STATUS_BIN 		0x1760
#घोषणा REG_MAC_TX_STATUS_END 		0x17c0

#घोषणा REG_CLK_GATING_CTRL		0x1814
#घोषणा CLK_GATING_DMAW_EN		0x0001
#घोषणा CLK_GATING_DMAR_EN		0x0002
#घोषणा CLK_GATING_TXQ_EN		0x0004
#घोषणा CLK_GATING_RXQ_EN		0x0008
#घोषणा CLK_GATING_TXMAC_EN		0x0010
#घोषणा CLK_GATING_RXMAC_EN		0x0020

#घोषणा CLK_GATING_EN_ALL	(CLK_GATING_DMAW_EN |\
				 CLK_GATING_DMAR_EN |\
				 CLK_GATING_TXQ_EN  |\
				 CLK_GATING_RXQ_EN  |\
				 CLK_GATING_TXMAC_EN|\
				 CLK_GATING_RXMAC_EN)

/* DEBUG ADDR */
#घोषणा REG_DEBUG_DATA0 		0x1900
#घोषणा REG_DEBUG_DATA1 		0x1904

#घोषणा L1D_MPW_PHYID1			0xD01C  /* V7 */
#घोषणा L1D_MPW_PHYID2			0xD01D  /* V1-V6 */
#घोषणा L1D_MPW_PHYID3			0xD01E  /* V8 */


/* Autoneg Advertisement Register */
#घोषणा ADVERTISE_DEFAULT_CAP \
	(ADVERTISE_ALL | ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM)

/* 1000BASE-T Control Register */
#घोषणा GIGA_CR_1000T_REPEATER_DTE	0x0400  /* 1=Repeater/चयन device port 0=DTE device */

#घोषणा GIGA_CR_1000T_MS_VALUE		0x0800  /* 1=Configure PHY as Master 0=Configure PHY as Slave */
#घोषणा GIGA_CR_1000T_MS_ENABLE		0x1000  /* 1=Master/Slave manual config value 0=Automatic Master/Slave config */
#घोषणा GIGA_CR_1000T_TEST_MODE_NORMAL	0x0000  /* Normal Operation */
#घोषणा GIGA_CR_1000T_TEST_MODE_1	0x2000  /* Transmit Waveक्रमm test */
#घोषणा GIGA_CR_1000T_TEST_MODE_2	0x4000  /* Master Transmit Jitter test */
#घोषणा GIGA_CR_1000T_TEST_MODE_3	0x6000  /* Slave Transmit Jitter test */
#घोषणा GIGA_CR_1000T_TEST_MODE_4	0x8000	/* Transmitter Distortion test */
#घोषणा GIGA_CR_1000T_SPEED_MASK	0x0300
#घोषणा GIGA_CR_1000T_DEFAULT_CAP	0x0300

/* PHY Specअगरic Status Register */
#घोषणा MII_GIGA_PSSR			0x11
#घोषणा GIGA_PSSR_SPD_DPLX_RESOLVED	0x0800  /* 1=Speed & Duplex resolved */
#घोषणा GIGA_PSSR_DPLX			0x2000  /* 1=Duplex 0=Half Duplex */
#घोषणा GIGA_PSSR_SPEED			0xC000  /* Speed, bits 14:15 */
#घोषणा GIGA_PSSR_10MBS			0x0000  /* 00=10Mbs */
#घोषणा GIGA_PSSR_100MBS		0x4000  /* 01=100Mbs */
#घोषणा GIGA_PSSR_1000MBS		0x8000  /* 10=1000Mbs */

/* PHY Interrupt Enable Register */
#घोषणा MII_IER				0x12
#घोषणा IER_LINK_UP			0x0400
#घोषणा IER_LINK_DOWN			0x0800

/* PHY Interrupt Status Register */
#घोषणा MII_ISR				0x13
#घोषणा ISR_LINK_UP			0x0400
#घोषणा ISR_LINK_DOWN			0x0800

/* Cable-Detect-Test Control Register */
#घोषणा MII_CDTC			0x16
#घोषणा CDTC_EN_OFF			0   /* sc */
#घोषणा CDTC_EN_BITS			1
#घोषणा CDTC_PAIR_OFF			8
#घोषणा CDTC_PAIR_BIT			2

/* Cable-Detect-Test Status Register */
#घोषणा MII_CDTS			0x1C
#घोषणा CDTS_STATUS_OFF			8
#घोषणा CDTS_STATUS_BITS		2
#घोषणा CDTS_STATUS_NORMAL		0
#घोषणा CDTS_STATUS_SHORT		1
#घोषणा CDTS_STATUS_OPEN		2
#घोषणा CDTS_STATUS_INVALID		3

#घोषणा MII_DBG_ADDR			0x1D
#घोषणा MII_DBG_DATA			0x1E

/***************************** debug port *************************************/

#घोषणा MIIDBG_ANACTRL                  0x00
#घोषणा ANACTRL_CLK125M_DELAY_EN        0x8000
#घोषणा ANACTRL_VCO_FAST                0x4000
#घोषणा ANACTRL_VCO_SLOW                0x2000
#घोषणा ANACTRL_AFE_MODE_EN             0x1000
#घोषणा ANACTRL_LCKDET_PHY              0x800
#घोषणा ANACTRL_LCKDET_EN               0x400
#घोषणा ANACTRL_OEN_125M                0x200
#घोषणा ANACTRL_HBIAS_EN                0x100
#घोषणा ANACTRL_HB_EN                   0x80
#घोषणा ANACTRL_SEL_HSP                 0x40
#घोषणा ANACTRL_CLASSA_EN               0x20
#घोषणा ANACTRL_MANUSWON_SWR_MASK       3U
#घोषणा ANACTRL_MANUSWON_SWR_SHIFT      2
#घोषणा ANACTRL_MANUSWON_SWR_2V         0
#घोषणा ANACTRL_MANUSWON_SWR_1P9V       1
#घोषणा ANACTRL_MANUSWON_SWR_1P8V       2
#घोषणा ANACTRL_MANUSWON_SWR_1P7V       3
#घोषणा ANACTRL_MANUSWON_BW3_4M         0x2
#घोषणा ANACTRL_RESTART_CAL             0x1
#घोषणा ANACTRL_DEF                     0x02EF

#घोषणा MIIDBG_SYSMODCTRL               0x04
#घोषणा SYSMODCTRL_IECHOADJ_PFMH_PHY    0x8000
#घोषणा SYSMODCTRL_IECHOADJ_BIASGEN     0x4000
#घोषणा SYSMODCTRL_IECHOADJ_PFML_PHY    0x2000
#घोषणा SYSMODCTRL_IECHOADJ_PS_MASK     3U
#घोषणा SYSMODCTRL_IECHOADJ_PS_SHIFT    10
#घोषणा SYSMODCTRL_IECHOADJ_PS_40       3
#घोषणा SYSMODCTRL_IECHOADJ_PS_20       2
#घोषणा SYSMODCTRL_IECHOADJ_PS_0        1
#घोषणा SYSMODCTRL_IECHOADJ_10BT_100MV  0x40 /* 1:100mv, 0:200mv */
#घोषणा SYSMODCTRL_IECHOADJ_HLFAP_MASK  3U
#घोषणा SYSMODCTRL_IECHOADJ_HLFAP_SHIFT 4
#घोषणा SYSMODCTRL_IECHOADJ_VDFULBW     0x8
#घोषणा SYSMODCTRL_IECHOADJ_VDBIASHLF   0x4
#घोषणा SYSMODCTRL_IECHOADJ_VDAMPHLF    0x2
#घोषणा SYSMODCTRL_IECHOADJ_VDLANSW     0x1
#घोषणा SYSMODCTRL_IECHOADJ_DEF         0x88BB /* ???? */

/* क्रम l1d & l2cb */
#घोषणा SYSMODCTRL_IECHOADJ_CUR_ADD     0x8000
#घोषणा SYSMODCTRL_IECHOADJ_CUR_MASK    7U
#घोषणा SYSMODCTRL_IECHOADJ_CUR_SHIFT   12
#घोषणा SYSMODCTRL_IECHOADJ_VOL_MASK    0xFU
#घोषणा SYSMODCTRL_IECHOADJ_VOL_SHIFT   8
#घोषणा SYSMODCTRL_IECHOADJ_VOL_17ALL   3
#घोषणा SYSMODCTRL_IECHOADJ_VOL_100M15  1
#घोषणा SYSMODCTRL_IECHOADJ_VOL_10M17   0
#घोषणा SYSMODCTRL_IECHOADJ_BIAS1_MASK  0xFU
#घोषणा SYSMODCTRL_IECHOADJ_BIAS1_SHIFT 4
#घोषणा SYSMODCTRL_IECHOADJ_BIAS2_MASK  0xFU
#घोषणा SYSMODCTRL_IECHOADJ_BIAS2_SHIFT 0
#घोषणा L1D_SYSMODCTRL_IECHOADJ_DEF     0x4FBB

#घोषणा MIIDBG_SRDSYSMOD                0x05
#घोषणा SRDSYSMOD_LCKDET_EN             0x2000
#घोषणा SRDSYSMOD_PLL_EN                0x800
#घोषणा SRDSYSMOD_SEL_HSP               0x400
#घोषणा SRDSYSMOD_HLFTXDR               0x200
#घोषणा SRDSYSMOD_TXCLK_DELAY_EN        0x100
#घोषणा SRDSYSMOD_TXELECIDLE            0x80
#घोषणा SRDSYSMOD_DEEMP_EN              0x40
#घोषणा SRDSYSMOD_MS_PAD                0x4
#घोषणा SRDSYSMOD_CDR_ADC_VLTG          0x2
#घोषणा SRDSYSMOD_CDR_DAC_1MA           0x1
#घोषणा SRDSYSMOD_DEF                   0x2C46

#घोषणा MIIDBG_CFGLPSPD                 0x0A
#घोषणा CFGLPSPD_RSTCNT_MASK            3U
#घोषणा CFGLPSPD_RSTCNT_SHIFT           14
#घोषणा CFGLPSPD_RSTCNT_CLK125SW        0x2000

#घोषणा MIIDBG_HIBNEG                   0x0B
#घोषणा HIBNEG_PSHIB_EN                 0x8000
#घोषणा HIBNEG_WAKE_BOTH                0x4000
#घोषणा HIBNEG_ONOFF_ANACHG_SUDEN       0x2000
#घोषणा HIBNEG_HIB_PULSE                0x1000
#घोषणा HIBNEG_GATE_25M_EN              0x800
#घोषणा HIBNEG_RST_80U                  0x400
#घोषणा HIBNEG_RST_TIMER_MASK           3U
#घोषणा HIBNEG_RST_TIMER_SHIFT          8
#घोषणा HIBNEG_GTX_CLK_DELAY_MASK       3U
#घोषणा HIBNEG_GTX_CLK_DELAY_SHIFT      5
#घोषणा HIBNEG_BYPSS_BRKTIMER           0x10
#घोषणा HIBNEG_DEF                      0xBC40

#घोषणा MIIDBG_TST10BTCFG               0x12
#घोषणा TST10BTCFG_INTV_TIMER_MASK      3U
#घोषणा TST10BTCFG_INTV_TIMER_SHIFT     14
#घोषणा TST10BTCFG_TRIGER_TIMER_MASK    3U
#घोषणा TST10BTCFG_TRIGER_TIMER_SHIFT   12
#घोषणा TST10BTCFG_DIV_MAN_MLT3_EN      0x800
#घोषणा TST10BTCFG_OFF_DAC_IDLE         0x400
#घोषणा TST10BTCFG_LPBK_DEEP            0x4 /* 1:deep,0:shallow */
#घोषणा TST10BTCFG_DEF                  0x4C04

#घोषणा MIIDBG_AZ_ANADECT		0x15
#घोषणा AZ_ANADECT_10BTRX_TH		0x8000
#घोषणा AZ_ANADECT_BOTH_01CHNL		0x4000
#घोषणा AZ_ANADECT_INTV_MASK		0x3FU
#घोषणा AZ_ANADECT_INTV_SHIFT		8
#घोषणा AZ_ANADECT_THRESH_MASK		0xFU
#घोषणा AZ_ANADECT_THRESH_SHIFT		4
#घोषणा AZ_ANADECT_CHNL_MASK		0xFU
#घोषणा AZ_ANADECT_CHNL_SHIFT		0
#घोषणा AZ_ANADECT_DEF			0x3220
#घोषणा AZ_ANADECT_LONG                 0xb210

#घोषणा MIIDBG_MSE16DB			0x18	/* l1d */
#घोषणा L1D_MSE16DB_UP			0x05EA
#घोषणा L1D_MSE16DB_DOWN		0x02EA

#घोषणा MIIDBG_LEGCYPS                  0x29
#घोषणा LEGCYPS_EN                      0x8000
#घोषणा LEGCYPS_DAC_AMP1000_MASK        7U
#घोषणा LEGCYPS_DAC_AMP1000_SHIFT       12
#घोषणा LEGCYPS_DAC_AMP100_MASK         7U
#घोषणा LEGCYPS_DAC_AMP100_SHIFT        9
#घोषणा LEGCYPS_DAC_AMP10_MASK          7U
#घोषणा LEGCYPS_DAC_AMP10_SHIFT         6
#घोषणा LEGCYPS_UNPLUG_TIMER_MASK       7U
#घोषणा LEGCYPS_UNPLUG_TIMER_SHIFT      3
#घोषणा LEGCYPS_UNPLUG_DECT_EN          0x4
#घोषणा LEGCYPS_ECNC_PS_EN              0x1
#घोषणा L1D_LEGCYPS_DEF                 0x129D
#घोषणा L1C_LEGCYPS_DEF                 0x36DD

#घोषणा MIIDBG_TST100BTCFG              0x36
#घोषणा TST100BTCFG_NORMAL_BW_EN        0x8000
#घोषणा TST100BTCFG_BADLNK_BYPASS       0x4000
#घोषणा TST100BTCFG_SHORTCABL_TH_MASK   0x3FU
#घोषणा TST100BTCFG_SHORTCABL_TH_SHIFT  8
#घोषणा TST100BTCFG_LITCH_EN            0x80
#घोषणा TST100BTCFG_VLT_SW              0x40
#घोषणा TST100BTCFG_LONGCABL_TH_MASK    0x3FU
#घोषणा TST100BTCFG_LONGCABL_TH_SHIFT   0
#घोषणा TST100BTCFG_DEF                 0xE12C

#घोषणा MIIDBG_VOLT_CTRL                0x3B	/* only क्रम l2cb 1 & 2 */
#घोषणा VOLT_CTRL_CABLE1TH_MASK         0x1FFU
#घोषणा VOLT_CTRL_CABLE1TH_SHIFT        7
#घोषणा VOLT_CTRL_AMPCTRL_MASK          3U
#घोषणा VOLT_CTRL_AMPCTRL_SHIFT         5
#घोषणा VOLT_CTRL_SW_BYPASS             0x10
#घोषणा VOLT_CTRL_SWLOWEST              0x8
#घोषणा VOLT_CTRL_DACAMP10_MASK         7U
#घोषणा VOLT_CTRL_DACAMP10_SHIFT        0

#घोषणा MIIDBG_CABLE1TH_DET             0x3E
#घोषणा CABLE1TH_DET_EN                 0x8000


/******* dev 3 *********/
#घोषणा MIIEXT_PCS                      3

#घोषणा MIIEXT_CLDCTRL3                 0x8003
#घोषणा CLDCTRL3_BP_CABLE1TH_DET_GT     0x8000
#घोषणा CLDCTRL3_AZ_DISAMP              0x1000
#घोषणा L2CB_CLDCTRL3                   0x4D19
#घोषणा L1D_CLDCTRL3                    0xDD19

#घोषणा MIIEXT_CLDCTRL6			0x8006
#घोषणा CLDCTRL6_CAB_LEN_MASK		0x1FFU
#घोषणा CLDCTRL6_CAB_LEN_SHIFT          0
#घोषणा CLDCTRL6_CAB_LEN_SHORT          0x50

/********* dev 7 **********/
#घोषणा MIIEXT_ANEG                     7

#घोषणा MIIEXT_LOCAL_EEEADV             0x3C
#घोषणा LOCAL_EEEADV_1000BT             0x4
#घोषणा LOCAL_EEEADV_100BT              0x2

#घोषणा MIIEXT_REMOTE_EEEADV            0x3D
#घोषणा REMOTE_EEEADV_1000BT            0x4
#घोषणा REMOTE_EEEADV_100BT             0x2

#घोषणा MIIEXT_EEE_ANEG                 0x8000
#घोषणा EEE_ANEG_1000M                  0x4
#घोषणा EEE_ANEG_100M                   0x2

#पूर्ण_अगर /*_ATL1C_HW_H_*/
