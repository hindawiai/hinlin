<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright(c) 2007 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित _ATHL1E_HW_H_
#घोषणा _ATHL1E_HW_H_

#समावेश <linux/types.h>
#समावेश <linux/mii.h>

काष्ठा atl1e_adapter;
काष्ठा atl1e_hw;

/* function prototype */
s32 atl1e_reset_hw(काष्ठा atl1e_hw *hw);
s32 atl1e_पढ़ो_mac_addr(काष्ठा atl1e_hw *hw);
s32 atl1e_init_hw(काष्ठा atl1e_hw *hw);
s32 atl1e_phy_commit(काष्ठा atl1e_hw *hw);
s32 atl1e_get_speed_and_duplex(काष्ठा atl1e_hw *hw, u16 *speed, u16 *duplex);
u32 atl1e_स्वतः_get_fc(काष्ठा atl1e_adapter *adapter, u16 duplex);
u32 atl1e_hash_mc_addr(काष्ठा atl1e_hw *hw, u8 *mc_addr);
व्योम atl1e_hash_set(काष्ठा atl1e_hw *hw, u32 hash_value);
s32 atl1e_पढ़ो_phy_reg(काष्ठा atl1e_hw *hw, u16 reg_addr, u16 *phy_data);
s32 atl1e_ग_लिखो_phy_reg(काष्ठा atl1e_hw *hw, u32 reg_addr, u16 phy_data);
s32 atl1e_validate_mdi_setting(काष्ठा atl1e_hw *hw);
व्योम atl1e_hw_set_mac_addr(काष्ठा atl1e_hw *hw);
bool atl1e_पढ़ो_eeprom(काष्ठा atl1e_hw *hw, u32 offset, u32 *p_value);
bool atl1e_ग_लिखो_eeprom(काष्ठा atl1e_hw *hw, u32 offset, u32 value);
s32 atl1e_phy_enter_घातer_saving(काष्ठा atl1e_hw *hw);
s32 atl1e_phy_leave_घातer_saving(काष्ठा atl1e_hw *hw);
s32 atl1e_phy_init(काष्ठा atl1e_hw *hw);
पूर्णांक atl1e_check_eeprom_exist(काष्ठा atl1e_hw *hw);
व्योम atl1e_क्रमce_ps(काष्ठा atl1e_hw *hw);
s32 atl1e_restart_स्वतःneg(काष्ठा atl1e_hw *hw);

/* रेजिस्टर definition */
#घोषणा REG_PM_CTRLSTAT             0x44

#घोषणा REG_PCIE_CAP_LIST           0x58

#घोषणा REG_DEVICE_CAP              0x5C
#घोषणा     DEVICE_CAP_MAX_PAYLOAD_MASK     0x7
#घोषणा     DEVICE_CAP_MAX_PAYLOAD_SHIFT    0

#घोषणा REG_DEVICE_CTRL             0x60
#घोषणा     DEVICE_CTRL_MAX_PAYLOAD_MASK    0x7
#घोषणा     DEVICE_CTRL_MAX_PAYLOAD_SHIFT   5
#घोषणा     DEVICE_CTRL_MAX_RREQ_SZ_MASK    0x7
#घोषणा     DEVICE_CTRL_MAX_RREQ_SZ_SHIFT   12

#घोषणा REG_VPD_CAP                 0x6C
#घोषणा     VPD_CAP_ID_MASK                 0xff
#घोषणा     VPD_CAP_ID_SHIFT                0
#घोषणा     VPD_CAP_NEXT_PTR_MASK           0xFF
#घोषणा     VPD_CAP_NEXT_PTR_SHIFT          8
#घोषणा     VPD_CAP_VPD_ADDR_MASK           0x7FFF
#घोषणा     VPD_CAP_VPD_ADDR_SHIFT          16
#घोषणा     VPD_CAP_VPD_FLAG                0x80000000

#घोषणा REG_VPD_DATA                0x70

#घोषणा REG_SPI_FLASH_CTRL          0x200
#घोषणा     SPI_FLASH_CTRL_STS_NON_RDY      0x1
#घोषणा     SPI_FLASH_CTRL_STS_WEN          0x2
#घोषणा     SPI_FLASH_CTRL_STS_WPEN         0x80
#घोषणा     SPI_FLASH_CTRL_DEV_STS_MASK     0xFF
#घोषणा     SPI_FLASH_CTRL_DEV_STS_SHIFT    0
#घोषणा     SPI_FLASH_CTRL_INS_MASK         0x7
#घोषणा     SPI_FLASH_CTRL_INS_SHIFT        8
#घोषणा     SPI_FLASH_CTRL_START            0x800
#घोषणा     SPI_FLASH_CTRL_EN_VPD           0x2000
#घोषणा     SPI_FLASH_CTRL_LDSTART          0x8000
#घोषणा     SPI_FLASH_CTRL_CS_HI_MASK       0x3
#घोषणा     SPI_FLASH_CTRL_CS_HI_SHIFT      16
#घोषणा     SPI_FLASH_CTRL_CS_HOLD_MASK     0x3
#घोषणा     SPI_FLASH_CTRL_CS_HOLD_SHIFT    18
#घोषणा     SPI_FLASH_CTRL_CLK_LO_MASK      0x3
#घोषणा     SPI_FLASH_CTRL_CLK_LO_SHIFT     20
#घोषणा     SPI_FLASH_CTRL_CLK_HI_MASK      0x3
#घोषणा     SPI_FLASH_CTRL_CLK_HI_SHIFT     22
#घोषणा     SPI_FLASH_CTRL_CS_SETUP_MASK    0x3
#घोषणा     SPI_FLASH_CTRL_CS_SETUP_SHIFT   24
#घोषणा     SPI_FLASH_CTRL_EROM_PGSZ_MASK   0x3
#घोषणा     SPI_FLASH_CTRL_EROM_PGSZ_SHIFT  26
#घोषणा     SPI_FLASH_CTRL_WAIT_READY       0x10000000

#घोषणा REG_SPI_ADDR                0x204

#घोषणा REG_SPI_DATA                0x208

#घोषणा REG_SPI_FLASH_CONFIG        0x20C
#घोषणा     SPI_FLASH_CONFIG_LD_ADDR_MASK   0xFFFFFF
#घोषणा     SPI_FLASH_CONFIG_LD_ADDR_SHIFT  0
#घोषणा     SPI_FLASH_CONFIG_VPD_ADDR_MASK  0x3
#घोषणा     SPI_FLASH_CONFIG_VPD_ADDR_SHIFT 24
#घोषणा     SPI_FLASH_CONFIG_LD_EXIST       0x4000000


#घोषणा REG_SPI_FLASH_OP_PROGRAM    0x210
#घोषणा REG_SPI_FLASH_OP_SC_ERASE   0x211
#घोषणा REG_SPI_FLASH_OP_CHIP_ERASE 0x212
#घोषणा REG_SPI_FLASH_OP_RDID       0x213
#घोषणा REG_SPI_FLASH_OP_WREN       0x214
#घोषणा REG_SPI_FLASH_OP_RDSR       0x215
#घोषणा REG_SPI_FLASH_OP_WRSR       0x216
#घोषणा REG_SPI_FLASH_OP_READ       0x217

#घोषणा REG_TWSI_CTRL               0x218
#घोषणा     TWSI_CTRL_LD_OFFSET_MASK        0xFF
#घोषणा     TWSI_CTRL_LD_OFFSET_SHIFT       0
#घोषणा     TWSI_CTRL_LD_SLV_ADDR_MASK      0x7
#घोषणा     TWSI_CTRL_LD_SLV_ADDR_SHIFT     8
#घोषणा     TWSI_CTRL_SW_LDSTART            0x800
#घोषणा     TWSI_CTRL_HW_LDSTART            0x1000
#घोषणा     TWSI_CTRL_SMB_SLV_ADDR_MASK     0x7F
#घोषणा     TWSI_CTRL_SMB_SLV_ADDR_SHIFT    15
#घोषणा     TWSI_CTRL_LD_EXIST              0x400000
#घोषणा     TWSI_CTRL_READ_FREQ_SEL_MASK    0x3
#घोषणा     TWSI_CTRL_READ_FREQ_SEL_SHIFT   23
#घोषणा     TWSI_CTRL_FREQ_SEL_100K         0
#घोषणा     TWSI_CTRL_FREQ_SEL_200K         1
#घोषणा     TWSI_CTRL_FREQ_SEL_300K         2
#घोषणा     TWSI_CTRL_FREQ_SEL_400K         3
#घोषणा     TWSI_CTRL_SMB_SLV_ADDR
#घोषणा     TWSI_CTRL_WRITE_FREQ_SEL_MASK   0x3
#घोषणा     TWSI_CTRL_WRITE_FREQ_SEL_SHIFT  24


#घोषणा REG_PCIE_DEV_MISC_CTRL      0x21C
#घोषणा     PCIE_DEV_MISC_CTRL_EXT_PIPE     0x2
#घोषणा     PCIE_DEV_MISC_CTRL_RETRY_BUFDIS 0x1
#घोषणा     PCIE_DEV_MISC_CTRL_SPIROM_EXIST 0x4
#घोषणा     PCIE_DEV_MISC_CTRL_SERDES_ENDIAN    0x8
#घोषणा     PCIE_DEV_MISC_CTRL_SERDES_SEL_DIN   0x10

#घोषणा REG_PCIE_PHYMISC	    0x1000
#घोषणा PCIE_PHYMISC_FORCE_RCV_DET	0x4

#घोषणा REG_LTSSM_TEST_MODE         0x12FC
#घोषणा         LTSSM_TEST_MODE_DEF     0xE000

/* Selene Master Control Register */
#घोषणा REG_MASTER_CTRL             0x1400
#घोषणा     MASTER_CTRL_SOFT_RST            0x1
#घोषणा     MASTER_CTRL_MTIMER_EN           0x2
#घोषणा     MASTER_CTRL_ITIMER_EN           0x4
#घोषणा     MASTER_CTRL_MANUAL_INT          0x8
#घोषणा     MASTER_CTRL_ITIMER2_EN          0x20
#घोषणा     MASTER_CTRL_INT_RDCLR           0x40
#घोषणा     MASTER_CTRL_LED_MODE	    0x200
#घोषणा     MASTER_CTRL_REV_NUM_SHIFT       16
#घोषणा     MASTER_CTRL_REV_NUM_MASK        0xff
#घोषणा     MASTER_CTRL_DEV_ID_SHIFT        24
#घोषणा     MASTER_CTRL_DEV_ID_MASK         0xff

/* Timer Initial Value Register */
#घोषणा REG_MANUAL_TIMER_INIT       0x1404


/* IRQ ModeratorTimer Initial Value Register */
#घोषणा REG_IRQ_MODU_TIMER_INIT     0x1408   /* w */
#घोषणा REG_IRQ_MODU_TIMER2_INIT    0x140A   /* w */


#घोषणा REG_GPHY_CTRL               0x140C
#घोषणा     GPHY_CTRL_EXT_RESET         1
#घोषणा     GPHY_CTRL_PIPE_MOD          2
#घोषणा     GPHY_CTRL_TEST_MODE_MASK    3
#घोषणा     GPHY_CTRL_TEST_MODE_SHIFT   2
#घोषणा     GPHY_CTRL_BERT_START        0x10
#घोषणा     GPHY_CTRL_GATE_25M_EN       0x20
#घोषणा     GPHY_CTRL_LPW_EXIT          0x40
#घोषणा     GPHY_CTRL_PHY_IDDQ          0x80
#घोषणा     GPHY_CTRL_PHY_IDDQ_DIS      0x100
#घोषणा     GPHY_CTRL_PCLK_SEL_DIS      0x200
#घोषणा     GPHY_CTRL_HIB_EN            0x400
#घोषणा     GPHY_CTRL_HIB_PULSE         0x800
#घोषणा     GPHY_CTRL_SEL_ANA_RST       0x1000
#घोषणा     GPHY_CTRL_PHY_PLL_ON        0x2000
#घोषणा     GPHY_CTRL_PWDOWN_HW		0x4000
#घोषणा     GPHY_CTRL_DEFAULT (\
		GPHY_CTRL_PHY_PLL_ON	|\
		GPHY_CTRL_SEL_ANA_RST	|\
		GPHY_CTRL_HIB_PULSE	|\
		GPHY_CTRL_HIB_EN)

#घोषणा     GPHY_CTRL_PW_WOL_DIS (\
		GPHY_CTRL_PHY_PLL_ON	|\
		GPHY_CTRL_SEL_ANA_RST	|\
		GPHY_CTRL_HIB_PULSE	|\
		GPHY_CTRL_HIB_EN	|\
		GPHY_CTRL_PWDOWN_HW	|\
		GPHY_CTRL_PCLK_SEL_DIS	|\
		GPHY_CTRL_PHY_IDDQ)

/* IRQ Anti-Lost Timer Initial Value Register */
#घोषणा REG_CMBDISDMA_TIMER         0x140E


/* Block IDLE Status Register */
#घोषणा REG_IDLE_STATUS  	0x1410
#घोषणा     IDLE_STATUS_RXMAC       1    /* 1: RXMAC state machine is in non-IDLE state. 0: RXMAC is idling */
#घोषणा     IDLE_STATUS_TXMAC       2    /* 1: TXMAC state machine is in non-IDLE state. 0: TXMAC is idling */
#घोषणा     IDLE_STATUS_RXQ         4    /* 1: RXQ state machine is in non-IDLE state.   0: RXQ is idling   */
#घोषणा     IDLE_STATUS_TXQ         8    /* 1: TXQ state machine is in non-IDLE state.   0: TXQ is idling   */
#घोषणा     IDLE_STATUS_DMAR        0x10 /* 1: DMAR state machine is in non-IDLE state.  0: DMAR is idling  */
#घोषणा     IDLE_STATUS_DMAW        0x20 /* 1: DMAW state machine is in non-IDLE state.  0: DMAW is idling  */
#घोषणा     IDLE_STATUS_SMB         0x40 /* 1: SMB state machine is in non-IDLE state.   0: SMB is idling   */
#घोषणा     IDLE_STATUS_CMB         0x80 /* 1: CMB state machine is in non-IDLE state.   0: CMB is idling   */

/* MDIO Control Register */
#घोषणा REG_MDIO_CTRL           0x1414
#घोषणा     MDIO_DATA_MASK          0xffff  /* On MDIO ग_लिखो, the 16-bit control data to ग_लिखो to PHY MII management रेजिस्टर */
#घोषणा     MDIO_DATA_SHIFT         0       /* On MDIO पढ़ो, the 16-bit status data that was पढ़ो from the PHY MII management रेजिस्टर*/
#घोषणा     MDIO_REG_ADDR_MASK      0x1f    /* MDIO रेजिस्टर address */
#घोषणा     MDIO_REG_ADDR_SHIFT     16
#घोषणा     MDIO_RW                 0x200000      /* 1: पढ़ो, 0: ग_लिखो */
#घोषणा     MDIO_SUP_PREAMBLE       0x400000      /* Suppress preamble */
#घोषणा     MDIO_START              0x800000      /* Write 1 to initiate the MDIO master. And this bit is self cleared after one cycle*/
#घोषणा     MDIO_CLK_SEL_SHIFT      24
#घोषणा     MDIO_CLK_25_4           0
#घोषणा     MDIO_CLK_25_6           2
#घोषणा     MDIO_CLK_25_8           3
#घोषणा     MDIO_CLK_25_10          4
#घोषणा     MDIO_CLK_25_14          5
#घोषणा     MDIO_CLK_25_20          6
#घोषणा     MDIO_CLK_25_28          7
#घोषणा     MDIO_BUSY               0x8000000
#घोषणा     MDIO_AP_EN              0x10000000
#घोषणा MDIO_WAIT_TIMES         10

/* MII PHY Status Register */
#घोषणा REG_PHY_STATUS           0x1418
#घोषणा     PHY_STATUS_100M	      0x20000
#घोषणा     PHY_STATUS_EMI_CA	      0x40000

/* BIST Control and Status Register0 (क्रम the Packet Memory) */
#घोषणा REG_BIST0_CTRL              0x141c
#घोषणा     BIST0_NOW                   0x1 /* 1: To trigger BIST0 logic. This bit stays high during the */
/* BIST process and reset to zero when BIST is करोne */
#घोषणा     BIST0_SRAM_FAIL             0x2 /* 1: The SRAM failure is un-repairable because it has address */
/* decoder failure or more than 1 cell stuck-to-x failure */
#घोषणा     BIST0_FUSE_FLAG             0x4 /* 1: Indicating one cell has been fixed */

/* BIST Control and Status Register1(क्रम the retry buffer of PCI Express) */
#घोषणा REG_BIST1_CTRL              0x1420
#घोषणा     BIST1_NOW                   0x1 /* 1: To trigger BIST0 logic. This bit stays high during the */
/* BIST process and reset to zero when BIST is करोne */
#घोषणा     BIST1_SRAM_FAIL             0x2 /* 1: The SRAM failure is un-repairable because it has address */
/* decoder failure or more than 1 cell stuck-to-x failure.*/
#घोषणा     BIST1_FUSE_FLAG             0x4

/* SerDes Lock Detect Control and Status Register */
#घोषणा REG_SERDES_LOCK             0x1424
#घोषणा     SERDES_LOCK_DETECT          1  /* 1: SerDes lock detected . This संकेत comes from Analog SerDes */
#घोषणा     SERDES_LOCK_DETECT_EN       2  /* 1: Enable SerDes Lock detect function */

/* MAC Control Register  */
#घोषणा REG_MAC_CTRL                0x1480
#घोषणा     MAC_CTRL_TX_EN              1  /* 1: Transmit Enable */
#घोषणा     MAC_CTRL_RX_EN              2  /* 1: Receive Enable */
#घोषणा     MAC_CTRL_TX_FLOW            4  /* 1: Transmit Flow Control Enable */
#घोषणा     MAC_CTRL_RX_FLOW            8  /* 1: Receive Flow Control Enable */
#घोषणा     MAC_CTRL_LOOPBACK           0x10      /* 1: Loop back at G/MII Interface */
#घोषणा     MAC_CTRL_DUPLX              0x20      /* 1: Full-duplex mode  0: Half-duplex mode */
#घोषणा     MAC_CTRL_ADD_CRC            0x40      /* 1: Inकाष्ठा MAC to attach CRC on all egress Ethernet frames */
#घोषणा     MAC_CTRL_PAD                0x80      /* 1: Inकाष्ठा MAC to pad लघु frames to 60-bytes, and then attach CRC. This bit has higher priority over CRC_EN */
#घोषणा     MAC_CTRL_LENCHK             0x100     /* 1: Inकाष्ठा MAC to check अगर length field matches the real packet length */
#घोषणा     MAC_CTRL_HUGE_EN            0x200     /* 1: receive Jumbo frame enable */
#घोषणा     MAC_CTRL_PRMLEN_SHIFT       10        /* Preamble length */
#घोषणा     MAC_CTRL_PRMLEN_MASK        0xf
#घोषणा     MAC_CTRL_RMV_VLAN           0x4000    /* 1: to हटाओ VLAN Tag स्वतःmatically from all receive packets */
#घोषणा     MAC_CTRL_PROMIS_EN          0x8000    /* 1: Promiscuous Mode Enable */
#घोषणा     MAC_CTRL_TX_PAUSE           0x10000   /* 1: transmit test छोड़ो */
#घोषणा     MAC_CTRL_SCNT               0x20000   /* 1: लघुcut slot समय counter */
#घोषणा     MAC_CTRL_SRST_TX            0x40000   /* 1: synchronized reset Transmit MAC module */
#घोषणा     MAC_CTRL_TX_SIMURST         0x80000   /* 1: transmit simulation reset */
#घोषणा     MAC_CTRL_SPEED_SHIFT        20        /* 10: gigabit 01:10M/100M */
#घोषणा     MAC_CTRL_SPEED_MASK         0x300000
#घोषणा     MAC_CTRL_SPEED_1000         2
#घोषणा     MAC_CTRL_SPEED_10_100       1
#घोषणा     MAC_CTRL_DBG_TX_BKPRESURE   0x400000  /* 1: transmit maximum backoff (half-duplex test bit) */
#घोषणा     MAC_CTRL_TX_HUGE            0x800000  /* 1: transmit huge enable */
#घोषणा     MAC_CTRL_RX_CHKSUM_EN       0x1000000 /* 1: RX checksum enable */
#घोषणा     MAC_CTRL_MC_ALL_EN          0x2000000 /* 1: upload all multicast frame without error to प्रणाली */
#घोषणा     MAC_CTRL_BC_EN              0x4000000 /* 1: upload all broadcast frame without error to प्रणाली */
#घोषणा     MAC_CTRL_DBG                0x8000000 /* 1: upload all received frame to प्रणाली (Debug Mode) */

/* MAC IPG/IFG Control Register  */
#घोषणा REG_MAC_IPG_IFG             0x1484
#घोषणा     MAC_IPG_IFG_IPGT_SHIFT      0     /* Desired back to back पूर्णांकer-packet gap. The शेष is 96-bit समय */
#घोषणा     MAC_IPG_IFG_IPGT_MASK       0x7f
#घोषणा     MAC_IPG_IFG_MIFG_SHIFT      8     /* Minimum number of IFG to enक्रमce in between RX frames */
#घोषणा     MAC_IPG_IFG_MIFG_MASK       0xff  /* Frame gap below such IFP is dropped */
#घोषणा     MAC_IPG_IFG_IPGR1_SHIFT     16    /* 64bit Carrier-Sense winकरोw */
#घोषणा     MAC_IPG_IFG_IPGR1_MASK      0x7f
#घोषणा     MAC_IPG_IFG_IPGR2_SHIFT     24    /* 96-bit IPG winकरोw */
#घोषणा     MAC_IPG_IFG_IPGR2_MASK      0x7f

/* MAC STATION ADDRESS  */
#घोषणा REG_MAC_STA_ADDR            0x1488

/* Hash table क्रम multicast address */
#घोषणा REG_RX_HASH_TABLE           0x1490


/* MAC Half-Duplex Control Register */
#घोषणा REG_MAC_HALF_DUPLX_CTRL     0x1498
#घोषणा     MAC_HALF_DUPLX_CTRL_LCOL_SHIFT   0      /* Collision Winकरोw */
#घोषणा     MAC_HALF_DUPLX_CTRL_LCOL_MASK    0x3ff
#घोषणा     MAC_HALF_DUPLX_CTRL_RETRY_SHIFT  12     /* Retransmission maximum, afterwards the packet will be discarded */
#घोषणा     MAC_HALF_DUPLX_CTRL_RETRY_MASK   0xf
#घोषणा     MAC_HALF_DUPLX_CTRL_EXC_DEF_EN   0x10000 /* 1: Allow the transmission of a packet which has been excessively deferred */
#घोषणा     MAC_HALF_DUPLX_CTRL_NO_BACK_C    0x20000 /* 1: No back-off on collision, immediately start the retransmission */
#घोषणा     MAC_HALF_DUPLX_CTRL_NO_BACK_P    0x40000 /* 1: No back-off on backpressure, immediately start the transmission after back pressure */
#घोषणा     MAC_HALF_DUPLX_CTRL_ABEBE        0x80000 /* 1: Alternative Binary Exponential Back-off Enabled */
#घोषणा     MAC_HALF_DUPLX_CTRL_ABEBT_SHIFT  20      /* Maximum binary exponential number */
#घोषणा     MAC_HALF_DUPLX_CTRL_ABEBT_MASK   0xf
#घोषणा     MAC_HALF_DUPLX_CTRL_JAMIPG_SHIFT 24      /* IPG to start JAM क्रम collision based flow control in half-duplex */
#घोषणा     MAC_HALF_DUPLX_CTRL_JAMIPG_MASK  0xf     /* mode. In unit of 8-bit समय */

/* Maximum Frame Length Control Register   */
#घोषणा REG_MTU                     0x149c

/* Wake-On-Lan control रेजिस्टर */
#घोषणा REG_WOL_CTRL                0x14a0
#घोषणा     WOL_PATTERN_EN                  0x00000001
#घोषणा     WOL_PATTERN_PME_EN              0x00000002
#घोषणा     WOL_MAGIC_EN                    0x00000004
#घोषणा     WOL_MAGIC_PME_EN                0x00000008
#घोषणा     WOL_LINK_CHG_EN                 0x00000010
#घोषणा     WOL_LINK_CHG_PME_EN             0x00000020
#घोषणा     WOL_PATTERN_ST                  0x00000100
#घोषणा     WOL_MAGIC_ST                    0x00000200
#घोषणा     WOL_LINKCHG_ST                  0x00000400
#घोषणा     WOL_CLK_SWITCH_EN               0x00008000
#घोषणा     WOL_PT0_EN                      0x00010000
#घोषणा     WOL_PT1_EN                      0x00020000
#घोषणा     WOL_PT2_EN                      0x00040000
#घोषणा     WOL_PT3_EN                      0x00080000
#घोषणा     WOL_PT4_EN                      0x00100000
#घोषणा     WOL_PT5_EN                      0x00200000
#घोषणा     WOL_PT6_EN                      0x00400000
/* WOL Length ( 2 DWORD ) */
#घोषणा REG_WOL_PATTERN_LEN         0x14a4
#घोषणा     WOL_PT_LEN_MASK                 0x7f
#घोषणा     WOL_PT0_LEN_SHIFT               0
#घोषणा     WOL_PT1_LEN_SHIFT               8
#घोषणा     WOL_PT2_LEN_SHIFT               16
#घोषणा     WOL_PT3_LEN_SHIFT               24
#घोषणा     WOL_PT4_LEN_SHIFT               0
#घोषणा     WOL_PT5_LEN_SHIFT               8
#घोषणा     WOL_PT6_LEN_SHIFT               16

/* Internal SRAM Partition Register */
#घोषणा REG_SRAM_TRD_ADDR           0x1518
#घोषणा REG_SRAM_TRD_LEN            0x151C
#घोषणा REG_SRAM_RXF_ADDR           0x1520
#घोषणा REG_SRAM_RXF_LEN            0x1524
#घोषणा REG_SRAM_TXF_ADDR           0x1528
#घोषणा REG_SRAM_TXF_LEN            0x152C
#घोषणा REG_SRAM_TCPH_ADDR          0x1530
#घोषणा REG_SRAM_PKTH_ADDR          0x1532

/* Load Ptr Register */
#घोषणा REG_LOAD_PTR                0x1534  /* Software sets this bit after the initialization of the head and tail */

/*
 * addresses of all descriptors, as well as the following descriptor
 * control रेजिस्टर, which triggers each function block to load the head
 * poपूर्णांकer to prepare क्रम the operation. This bit is then self-cleared
 * after one cycle.
 */

/* Descriptor Control रेजिस्टर  */
#घोषणा REG_RXF3_BASE_ADDR_HI           0x153C
#घोषणा REG_DESC_BASE_ADDR_HI           0x1540
#घोषणा REG_RXF0_BASE_ADDR_HI           0x1540 /* share with DESC BASE ADDR HI */
#घोषणा REG_HOST_RXF0_PAGE0_LO          0x1544
#घोषणा REG_HOST_RXF0_PAGE1_LO          0x1548
#घोषणा REG_TPD_BASE_ADDR_LO            0x154C
#घोषणा REG_RXF1_BASE_ADDR_HI           0x1550
#घोषणा REG_RXF2_BASE_ADDR_HI           0x1554
#घोषणा REG_HOST_RXFPAGE_SIZE           0x1558
#घोषणा REG_TPD_RING_SIZE               0x155C
/* RSS about */
#घोषणा REG_RSS_KEY0                    0x14B0
#घोषणा REG_RSS_KEY1                    0x14B4
#घोषणा REG_RSS_KEY2                    0x14B8
#घोषणा REG_RSS_KEY3                    0x14BC
#घोषणा REG_RSS_KEY4                    0x14C0
#घोषणा REG_RSS_KEY5                    0x14C4
#घोषणा REG_RSS_KEY6                    0x14C8
#घोषणा REG_RSS_KEY7                    0x14CC
#घोषणा REG_RSS_KEY8                    0x14D0
#घोषणा REG_RSS_KEY9                    0x14D4
#घोषणा REG_IDT_TABLE4                  0x14E0
#घोषणा REG_IDT_TABLE5                  0x14E4
#घोषणा REG_IDT_TABLE6                  0x14E8
#घोषणा REG_IDT_TABLE7                  0x14EC
#घोषणा REG_IDT_TABLE0                  0x1560
#घोषणा REG_IDT_TABLE1                  0x1564
#घोषणा REG_IDT_TABLE2                  0x1568
#घोषणा REG_IDT_TABLE3                  0x156C
#घोषणा REG_IDT_TABLE                   REG_IDT_TABLE0
#घोषणा REG_RSS_HASH_VALUE              0x1570
#घोषणा REG_RSS_HASH_FLAG               0x1574
#घोषणा REG_BASE_CPU_NUMBER             0x157C


/* TXQ Control Register */
#घोषणा REG_TXQ_CTRL                0x1580
#घोषणा     TXQ_CTRL_NUM_TPD_BURST_MASK     0xF
#घोषणा     TXQ_CTRL_NUM_TPD_BURST_SHIFT    0
#घोषणा     TXQ_CTRL_EN                     0x20  /* 1: Enable TXQ */
#घोषणा     TXQ_CTRL_ENH_MODE               0x40  /* Perक्रमmance enhancement mode, in which up to two back-to-back DMA पढ़ो commands might be dispatched. */
#घोषणा     TXQ_CTRL_TXF_BURST_NUM_SHIFT    16    /* Number of data byte to पढ़ो in a cache-aligned burst. Each SRAM entry is 8-byte in length. */
#घोषणा     TXQ_CTRL_TXF_BURST_NUM_MASK     0xffff

/* Jumbo packet Threshold क्रम task offload */
#घोषणा REG_TX_EARLY_TH                     0x1584 /* Jumbo frame threshold in QWORD unit. Packet greater than */
/* JUMBO_TASK_OFFLOAD_THRESHOLD will not be task offloaded. */
#घोषणा     TX_TX_EARLY_TH_MASK             0x7ff
#घोषणा     TX_TX_EARLY_TH_SHIFT            0


/* RXQ Control Register */
#घोषणा REG_RXQ_CTRL                0x15A0
#घोषणा         RXQ_CTRL_PBA_ALIGN_32                   0   /* rx-packet alignment */
#घोषणा         RXQ_CTRL_PBA_ALIGN_64                   1
#घोषणा         RXQ_CTRL_PBA_ALIGN_128                  2
#घोषणा         RXQ_CTRL_PBA_ALIGN_256                  3
#घोषणा         RXQ_CTRL_Q1_EN				0x10
#घोषणा         RXQ_CTRL_Q2_EN				0x20
#घोषणा         RXQ_CTRL_Q3_EN				0x40
#घोषणा         RXQ_CTRL_IPV6_XSUM_VERIFY_EN		0x80
#घोषणा         RXQ_CTRL_HASH_TLEN_SHIFT                8
#घोषणा         RXQ_CTRL_HASH_TLEN_MASK                 0xFF
#घोषणा         RXQ_CTRL_HASH_TYPE_IPV4                 0x10000
#घोषणा         RXQ_CTRL_HASH_TYPE_IPV4_TCP             0x20000
#घोषणा         RXQ_CTRL_HASH_TYPE_IPV6                 0x40000
#घोषणा         RXQ_CTRL_HASH_TYPE_IPV6_TCP             0x80000
#घोषणा         RXQ_CTRL_RSS_MODE_DISABLE               0
#घोषणा         RXQ_CTRL_RSS_MODE_SQSINT                0x4000000
#घोषणा         RXQ_CTRL_RSS_MODE_MQUESINT              0x8000000
#घोषणा         RXQ_CTRL_RSS_MODE_MQUEMINT              0xC000000
#घोषणा         RXQ_CTRL_NIP_QUEUE_SEL_TBL              0x10000000
#घोषणा         RXQ_CTRL_HASH_ENABLE                    0x20000000
#घोषणा         RXQ_CTRL_CUT_THRU_EN                    0x40000000
#घोषणा         RXQ_CTRL_EN                             0x80000000

/* Rx jumbo packet threshold and rrd  retirement समयr  */
#घोषणा REG_RXQ_JMBOSZ_RRDTIM       0x15A4
/*
 * Jumbo packet threshold क्रम non-VLAN packet, in QWORD (64-bit) unit.
 * When the packet length greater than or equal to this value, RXQ
 * shall start cut-through क्रमwarding of the received packet.
 */
#घोषणा         RXQ_JMBOSZ_TH_MASK      0x7ff
#घोषणा         RXQ_JMBOSZ_TH_SHIFT         0  /* RRD retirement समयr. Decrement by 1 after every 512ns passes*/
#घोषणा         RXQ_JMBO_LKAH_MASK          0xf
#घोषणा         RXQ_JMBO_LKAH_SHIFT         11

/* RXF flow control रेजिस्टर */
#घोषणा REG_RXQ_RXF_PAUSE_THRESH    0x15A8
#घोषणा     RXQ_RXF_PAUSE_TH_HI_SHIFT       0
#घोषणा     RXQ_RXF_PAUSE_TH_HI_MASK        0xfff
#घोषणा     RXQ_RXF_PAUSE_TH_LO_SHIFT       16
#घोषणा     RXQ_RXF_PAUSE_TH_LO_MASK        0xfff


/* DMA Engine Control Register */
#घोषणा REG_DMA_CTRL                0x15C0
#घोषणा     DMA_CTRL_DMAR_IN_ORDER          0x1
#घोषणा     DMA_CTRL_DMAR_ENH_ORDER         0x2
#घोषणा     DMA_CTRL_DMAR_OUT_ORDER         0x4
#घोषणा     DMA_CTRL_RCB_VALUE              0x8
#घोषणा     DMA_CTRL_DMAR_BURST_LEN_SHIFT   4
#घोषणा     DMA_CTRL_DMAR_BURST_LEN_MASK    7
#घोषणा     DMA_CTRL_DMAW_BURST_LEN_SHIFT   7
#घोषणा     DMA_CTRL_DMAW_BURST_LEN_MASK    7
#घोषणा     DMA_CTRL_DMAR_REQ_PRI           0x400
#घोषणा     DMA_CTRL_DMAR_DLY_CNT_MASK      0x1F
#घोषणा     DMA_CTRL_DMAR_DLY_CNT_SHIFT     11
#घोषणा     DMA_CTRL_DMAW_DLY_CNT_MASK      0xF
#घोषणा     DMA_CTRL_DMAW_DLY_CNT_SHIFT     16
#घोषणा     DMA_CTRL_TXCMB_EN               0x100000
#घोषणा     DMA_CTRL_RXCMB_EN				0x200000


/* CMB/SMB Control Register */
#घोषणा REG_SMB_STAT_TIMER                      0x15C4
#घोषणा REG_TRIG_RRD_THRESH                     0x15CA
#घोषणा REG_TRIG_TPD_THRESH                     0x15C8
#घोषणा REG_TRIG_TXTIMER                        0x15CC
#घोषणा REG_TRIG_RXTIMER                        0x15CE

/* HOST RXF Page 1,2,3 address */
#घोषणा REG_HOST_RXF1_PAGE0_LO                  0x15D0
#घोषणा REG_HOST_RXF1_PAGE1_LO                  0x15D4
#घोषणा REG_HOST_RXF2_PAGE0_LO                  0x15D8
#घोषणा REG_HOST_RXF2_PAGE1_LO                  0x15DC
#घोषणा REG_HOST_RXF3_PAGE0_LO                  0x15E0
#घोषणा REG_HOST_RXF3_PAGE1_LO                  0x15E4

/* Mail box */
#घोषणा REG_MB_RXF1_RADDR                       0x15B4
#घोषणा REG_MB_RXF2_RADDR                       0x15B8
#घोषणा REG_MB_RXF3_RADDR                       0x15BC
#घोषणा REG_MB_TPD_PROD_IDX                     0x15F0

/* RXF-Page 0-3  PageNo & Valid bit */
#घोषणा REG_HOST_RXF0_PAGE0_VLD     0x15F4
#घोषणा     HOST_RXF_VALID              1
#घोषणा     HOST_RXF_PAGENO_SHIFT       1
#घोषणा     HOST_RXF_PAGENO_MASK        0x7F
#घोषणा REG_HOST_RXF0_PAGE1_VLD     0x15F5
#घोषणा REG_HOST_RXF1_PAGE0_VLD     0x15F6
#घोषणा REG_HOST_RXF1_PAGE1_VLD     0x15F7
#घोषणा REG_HOST_RXF2_PAGE0_VLD     0x15F8
#घोषणा REG_HOST_RXF2_PAGE1_VLD     0x15F9
#घोषणा REG_HOST_RXF3_PAGE0_VLD     0x15FA
#घोषणा REG_HOST_RXF3_PAGE1_VLD     0x15FB

/* Interrupt Status Register */
#घोषणा REG_ISR    0x1600
#घोषणा  ISR_SMB   		1
#घोषणा  ISR_TIMER		2       /* Interrupt when Timer is counted करोwn to zero */
/*
 * Software manual पूर्णांकerrupt, क्रम debug. Set when SW_MAN_INT_EN is set
 * in Table 51 Selene Master Control Register (Offset 0x1400).
 */
#घोषणा  ISR_MANUAL         	4
#घोषणा  ISR_HW_RXF_OV          8        /* RXF overflow पूर्णांकerrupt */
#घोषणा  ISR_HOST_RXF0_OV       0x10
#घोषणा  ISR_HOST_RXF1_OV       0x20
#घोषणा  ISR_HOST_RXF2_OV       0x40
#घोषणा  ISR_HOST_RXF3_OV       0x80
#घोषणा  ISR_TXF_UN             0x100
#घोषणा  ISR_RX0_PAGE_FULL      0x200
#घोषणा  ISR_DMAR_TO_RST        0x400
#घोषणा  ISR_DMAW_TO_RST        0x800
#घोषणा  ISR_GPHY               0x1000
#घोषणा  ISR_TX_CREDIT          0x2000
#घोषणा  ISR_GPHY_LPW           0x4000    /* GPHY low घातer state पूर्णांकerrupt */
#घोषणा  ISR_RX_PKT             0x10000   /* One packet received, triggered by RFD */
#घोषणा  ISR_TX_PKT             0x20000   /* One packet transmitted, triggered by TPD */
#घोषणा  ISR_TX_DMA             0x40000
#घोषणा  ISR_RX_PKT_1           0x80000
#घोषणा  ISR_RX_PKT_2           0x100000
#घोषणा  ISR_RX_PKT_3           0x200000
#घोषणा  ISR_MAC_RX             0x400000
#घोषणा  ISR_MAC_TX             0x800000
#घोषणा  ISR_UR_DETECTED        0x1000000
#घोषणा  ISR_FERR_DETECTED      0x2000000
#घोषणा  ISR_NFERR_DETECTED     0x4000000
#घोषणा  ISR_CERR_DETECTED      0x8000000
#घोषणा  ISR_PHY_LINKDOWN       0x10000000
#घोषणा  ISR_DIS_INT            0x80000000


/* Interrupt Mask Register */
#घोषणा REG_IMR 0x1604


#घोषणा IMR_NORMAL_MASK (\
		ISR_SMB	        |\
		ISR_TXF_UN      |\
		ISR_HW_RXF_OV   |\
		ISR_HOST_RXF0_OV|\
		ISR_MANUAL      |\
		ISR_GPHY        |\
		ISR_GPHY_LPW    |\
		ISR_DMAR_TO_RST |\
		ISR_DMAW_TO_RST |\
		ISR_PHY_LINKDOWN|\
		ISR_RX_PKT      |\
		ISR_TX_PKT)

#घोषणा ISR_TX_EVENT (ISR_TXF_UN | ISR_TX_PKT)
#घोषणा ISR_RX_EVENT (ISR_HOST_RXF0_OV | ISR_HW_RXF_OV | ISR_RX_PKT)

#घोषणा REG_MAC_RX_STATUS_BIN 0x1700
#घोषणा REG_MAC_RX_STATUS_END 0x175c
#घोषणा REG_MAC_TX_STATUS_BIN 0x1760
#घोषणा REG_MAC_TX_STATUS_END 0x17c0

/* Hardware Offset Register */
#घोषणा REG_HOST_RXF0_PAGखातापूर्णF 0x1800
#घोषणा REG_TPD_CONS_IDX      0x1804
#घोषणा REG_HOST_RXF1_PAGखातापूर्णF 0x1808
#घोषणा REG_HOST_RXF2_PAGखातापूर्णF 0x180C
#घोषणा REG_HOST_RXF3_PAGखातापूर्णF 0x1810

/* RXF-Page 0-3 Offset DMA Address */
#घोषणा REG_HOST_RXF0_MB0_LO  0x1820
#घोषणा REG_HOST_RXF0_MB1_LO  0x1824
#घोषणा REG_HOST_RXF1_MB0_LO  0x1828
#घोषणा REG_HOST_RXF1_MB1_LO  0x182C
#घोषणा REG_HOST_RXF2_MB0_LO  0x1830
#घोषणा REG_HOST_RXF2_MB1_LO  0x1834
#घोषणा REG_HOST_RXF3_MB0_LO  0x1838
#घोषणा REG_HOST_RXF3_MB1_LO  0x183C

/* Tpd CMB DMA Address */
#घोषणा REG_HOST_TX_CMB_LO    0x1840
#घोषणा REG_HOST_SMB_ADDR_LO  0x1844

/* DEBUG ADDR */
#घोषणा REG_DEBUG_DATA0 0x1900
#घोषणा REG_DEBUG_DATA1 0x1904

/***************************** MII definition ***************************************/
/* PHY Common Register */
#घोषणा MII_AT001_PSCR                  0x10
#घोषणा MII_AT001_PSSR                  0x11
#घोषणा MII_INT_CTRL                    0x12
#घोषणा MII_INT_STATUS                  0x13
#घोषणा MII_SMARTSPEED                  0x14
#घोषणा MII_LBRERROR                    0x18
#घोषणा MII_RESV2                       0x1a

#घोषणा MII_DBG_ADDR			0x1D
#घोषणा MII_DBG_DATA			0x1E

/* Autoneg Advertisement Register */
#घोषणा MII_AR_DEFAULT_CAP_MASK                 0

/* 1000BASE-T Control Register */
#घोषणा MII_AT001_CR_1000T_SPEED_MASK \
	(ADVERTISE_1000FULL | ADVERTISE_1000HALF)
#घोषणा MII_AT001_CR_1000T_DEFAULT_CAP_MASK	MII_AT001_CR_1000T_SPEED_MASK

/* AT001 PHY Specअगरic Control Register */
#घोषणा MII_AT001_PSCR_JABBER_DISABLE           0x0001  /* 1=Jabber Function disabled */
#घोषणा MII_AT001_PSCR_POLARITY_REVERSAL        0x0002  /* 1=Polarity Reversal enabled */
#घोषणा MII_AT001_PSCR_SQE_TEST                 0x0004  /* 1=SQE Test enabled */
#घोषणा MII_AT001_PSCR_MAC_POWERDOWN            0x0008
#घोषणा MII_AT001_PSCR_CLK125_DISABLE           0x0010  /* 1=CLK125 low,
							 * 0=CLK125 toggling
							 */
#घोषणा MII_AT001_PSCR_MDI_MANUAL_MODE          0x0000  /* MDI Crossover Mode bits 6:5 */
/* Manual MDI configuration */
#घोषणा MII_AT001_PSCR_MDIX_MANUAL_MODE         0x0020  /* Manual MDIX configuration */
#घोषणा MII_AT001_PSCR_AUTO_X_1000T             0x0040  /* 1000BASE-T: Auto crossover,
							 *  100BASE-TX/10BASE-T:
							 *  MDI Mode
							 */
#घोषणा MII_AT001_PSCR_AUTO_X_MODE              0x0060  /* Auto crossover enabled
							 * all speeds.
							 */
#घोषणा MII_AT001_PSCR_10BT_EXT_DIST_ENABLE     0x0080
/* 1=Enable Extended 10BASE-T distance
 * (Lower 10BASE-T RX Threshold)
 * 0=Normal 10BASE-T RX Threshold */
#घोषणा MII_AT001_PSCR_MII_5BIT_ENABLE          0x0100
/* 1=5-Bit पूर्णांकerface in 100BASE-TX
 * 0=MII पूर्णांकerface in 100BASE-TX */
#घोषणा MII_AT001_PSCR_SCRAMBLER_DISABLE        0x0200  /* 1=Scrambler disable */
#घोषणा MII_AT001_PSCR_FORCE_LINK_GOOD          0x0400  /* 1=Force link good */
#घोषणा MII_AT001_PSCR_ASSERT_CRS_ON_TX         0x0800  /* 1=Assert CRS on Transmit */
#घोषणा MII_AT001_PSCR_POLARITY_REVERSAL_SHIFT    1
#घोषणा MII_AT001_PSCR_AUTO_X_MODE_SHIFT          5
#घोषणा MII_AT001_PSCR_10BT_EXT_DIST_ENABLE_SHIFT 7
/* AT001 PHY Specअगरic Status Register */
#घोषणा MII_AT001_PSSR_SPD_DPLX_RESOLVED        0x0800  /* 1=Speed & Duplex resolved */
#घोषणा MII_AT001_PSSR_DPLX                     0x2000  /* 1=Duplex 0=Half Duplex */
#घोषणा MII_AT001_PSSR_SPEED                    0xC000  /* Speed, bits 14:15 */
#घोषणा MII_AT001_PSSR_10MBS                    0x0000  /* 00=10Mbs */
#घोषणा MII_AT001_PSSR_100MBS                   0x4000  /* 01=100Mbs */
#घोषणा MII_AT001_PSSR_1000MBS                  0x8000  /* 10=1000Mbs */

#पूर्ण_अगर /*_ATHL1E_HW_H_*/
