<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000E_ICH8LAN_H_
#घोषणा _E1000E_ICH8LAN_H_

#घोषणा ICH_FLASH_GFPREG		0x0000
#घोषणा ICH_FLASH_HSFSTS		0x0004
#घोषणा ICH_FLASH_HSFCTL		0x0006
#घोषणा ICH_FLASH_FADDR			0x0008
#घोषणा ICH_FLASH_FDATA0		0x0010
#घोषणा ICH_FLASH_PR0			0x0074

/* Requires up to 10 seconds when MNG might be accessing part. */
#घोषणा ICH_FLASH_READ_COMMAND_TIMEOUT	10000000
#घोषणा ICH_FLASH_WRITE_COMMAND_TIMEOUT	10000000
#घोषणा ICH_FLASH_ERASE_COMMAND_TIMEOUT	10000000
#घोषणा ICH_FLASH_LINEAR_ADDR_MASK	0x00FFFFFF
#घोषणा ICH_FLASH_CYCLE_REPEAT_COUNT	10

#घोषणा ICH_CYCLE_READ			0
#घोषणा ICH_CYCLE_WRITE			2
#घोषणा ICH_CYCLE_ERASE			3

#घोषणा FLASH_GFPREG_BASE_MASK		0x1FFF
#घोषणा FLASH_SECTOR_ADDR_SHIFT		12

#घोषणा ICH_FLASH_SEG_SIZE_256		256
#घोषणा ICH_FLASH_SEG_SIZE_4K		4096
#घोषणा ICH_FLASH_SEG_SIZE_8K		8192
#घोषणा ICH_FLASH_SEG_SIZE_64K		65536

#घोषणा E1000_ICH_FWSM_RSPCIPHY	0x00000040	/* Reset PHY on PCI Reset */
/* FW established a valid mode */
#घोषणा E1000_ICH_FWSM_FW_VALID	0x00008000
#घोषणा E1000_ICH_FWSM_PCIM2PCI	0x01000000	/* ME PCIm-to-PCI active */
#घोषणा E1000_ICH_FWSM_PCIM2PCI_COUNT	2000

#घोषणा E1000_ICH_MNG_IAMT_MODE		0x2

#घोषणा E1000_FWSM_WLOCK_MAC_MASK	0x0380
#घोषणा E1000_FWSM_WLOCK_MAC_SHIFT	7
#घोषणा E1000_FWSM_ULP_CFG_DONE		0x00000400	/* Low घातer cfg करोne */

/* Shared Receive Address Registers */
#घोषणा E1000_SHRAL_PCH_LPT(_i)		(0x05408 + ((_i) * 8))
#घोषणा E1000_SHRAH_PCH_LPT(_i)		(0x0540C + ((_i) * 8))

#घोषणा E1000_H2ME		0x05B50	/* Host to ME */
#घोषणा E1000_H2ME_ULP		0x00000800	/* ULP Indication Bit */
#घोषणा E1000_H2ME_ENFORCE_SETTINGS	0x00001000	/* Enक्रमce Settings */

#घोषणा ID_LED_DEFAULT_ICH8LAN	((ID_LED_DEF1_DEF2 << 12) | \
				 (ID_LED_OFF1_OFF2 <<  8) | \
				 (ID_LED_OFF1_ON2  <<  4) | \
				 (ID_LED_DEF1_DEF2))

#घोषणा E1000_ICH_NVM_SIG_WORD		0x13u
#घोषणा E1000_ICH_NVM_SIG_MASK		0xC000u
#घोषणा E1000_ICH_NVM_VALID_SIG_MASK	0xC0u
#घोषणा E1000_ICH_NVM_SIG_VALUE		0x80u

#घोषणा E1000_ICH8_LAN_INIT_TIMEOUT	1500

/* FEXT रेजिस्टर bit definition */
#घोषणा E1000_FEXT_PHY_CABLE_DISCONNECTED	0x00000004

#घोषणा E1000_FEXTNVM_SW_CONFIG		1
#घोषणा E1000_FEXTNVM_SW_CONFIG_ICH8M	(1 << 27)	/* dअगरferent on ICH8M */

#घोषणा E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK	0x0C000000
#घोषणा E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC	0x08000000

#घोषणा E1000_FEXTNVM4_BEACON_DURATION_MASK	0x7
#घोषणा E1000_FEXTNVM4_BEACON_DURATION_8USEC	0x7
#घोषणा E1000_FEXTNVM4_BEACON_DURATION_16USEC	0x3

#घोषणा E1000_FEXTNVM6_REQ_PLL_CLK	0x00000100
#घोषणा E1000_FEXTNVM6_ENABLE_K1_ENTRY_CONDITION	0x00000200
#घोषणा E1000_FEXTNVM6_K1_OFF_ENABLE	0x80000000
/* bit क्रम disabling packet buffer पढ़ो */
#घोषणा E1000_FEXTNVM7_DISABLE_PB_READ	0x00040000
#घोषणा E1000_FEXTNVM7_SIDE_CLK_UNGATE	0x00000004
#घोषणा E1000_FEXTNVM7_DISABLE_SMB_PERST	0x00000020
#घोषणा E1000_FEXTNVM9_IOSFSB_CLKGATE_DIS	0x00000800
#घोषणा E1000_FEXTNVM9_IOSFSB_CLKREQ_DIS	0x00001000
#घोषणा E1000_FEXTNVM11_DISABLE_PB_READ		0x00000200
#घोषणा E1000_FEXTNVM11_DISABLE_MULR_FIX	0x00002000

/* bit24: RXDCTL thresholds granularity: 0 - cache lines, 1 - descriptors */
#घोषणा E1000_RXDCTL_THRESH_UNIT_DESC	0x01000000

#घोषणा K1_ENTRY_LATENCY	0
#घोषणा K1_MIN_TIME		1
#घोषणा NVM_SIZE_MULTIPLIER 4096	/*multiplier क्रम NVMS field */
#घोषणा E1000_FLASH_BASE_ADDR 0xE000	/*offset of NVM access regs */
#घोषणा E1000_CTRL_EXT_NVMVS 0x3	/*NVM valid sector */
#घोषणा E1000_TARC0_CB_MULTIQ_3_REQ	0x30000000
#घोषणा E1000_TARC0_CB_MULTIQ_2_REQ	0x20000000
#घोषणा PCIE_ICH8_SNOOP_ALL	PCIE_NO_SNOOP_ALL

#घोषणा E1000_ICH_RAR_ENTRIES	7
#घोषणा E1000_PCH2_RAR_ENTRIES	5	/* RAR[0], SHRA[0-3] */
#घोषणा E1000_PCH_LPT_RAR_ENTRIES	12	/* RAR[0], SHRA[0-10] */

#घोषणा PHY_PAGE_SHIFT		5
#घोषणा PHY_REG(page, reg)	(((page) << PHY_PAGE_SHIFT) | \
				 ((reg) & MAX_PHY_REG_ADDRESS))
#घोषणा IGP3_KMRN_DIAG	PHY_REG(770, 19)	/* KMRN Diagnostic */
#घोषणा IGP3_VR_CTRL	PHY_REG(776, 18)	/* Voltage Regulator Control */

#घोषणा IGP3_KMRN_DIAG_PCS_LOCK_LOSS		0x0002
#घोषणा IGP3_VR_CTRL_DEV_POWERDOWN_MODE_MASK	0x0300
#घोषणा IGP3_VR_CTRL_MODE_SHUTDOWN		0x0200

/* PHY Wakeup Registers and defines */
#घोषणा BM_PORT_GEN_CFG		PHY_REG(BM_PORT_CTRL_PAGE, 17)
#घोषणा BM_RCTL			PHY_REG(BM_WUC_PAGE, 0)
#घोषणा BM_WUC			PHY_REG(BM_WUC_PAGE, 1)
#घोषणा BM_WUFC			PHY_REG(BM_WUC_PAGE, 2)
#घोषणा BM_WUS			PHY_REG(BM_WUC_PAGE, 3)
#घोषणा BM_RAR_L(_i)		(BM_PHY_REG(BM_WUC_PAGE, 16 + ((_i) << 2)))
#घोषणा BM_RAR_M(_i)		(BM_PHY_REG(BM_WUC_PAGE, 17 + ((_i) << 2)))
#घोषणा BM_RAR_H(_i)		(BM_PHY_REG(BM_WUC_PAGE, 18 + ((_i) << 2)))
#घोषणा BM_RAR_CTRL(_i)		(BM_PHY_REG(BM_WUC_PAGE, 19 + ((_i) << 2)))
#घोषणा BM_MTA(_i)		(BM_PHY_REG(BM_WUC_PAGE, 128 + ((_i) << 1)))

#घोषणा BM_RCTL_UPE		0x0001	/* Unicast Promiscuous Mode */
#घोषणा BM_RCTL_MPE		0x0002	/* Multicast Promiscuous Mode */
#घोषणा BM_RCTL_MO_SHIFT	3	/* Multicast Offset Shअगरt */
#घोषणा BM_RCTL_MO_MASK		(3 << 3)	/* Multicast Offset Mask */
#घोषणा BM_RCTL_BAM		0x0020	/* Broadcast Accept Mode */
#घोषणा BM_RCTL_PMCF		0x0040	/* Pass MAC Control Frames */
#घोषणा BM_RCTL_RFCE		0x0080	/* Rx Flow Control Enable */

#घोषणा HV_LED_CONFIG		PHY_REG(768, 30)	/* LED Configuration */
#घोषणा HV_MUX_DATA_CTRL	PHY_REG(776, 16)
#घोषणा HV_MUX_DATA_CTRL_GEN_TO_MAC	0x0400
#घोषणा HV_MUX_DATA_CTRL_FORCE_SPEED	0x0004
#घोषणा HV_STATS_PAGE	778
/* Half-duplex collision counts */
#घोषणा HV_SCC_UPPER	PHY_REG(HV_STATS_PAGE, 16)	/* Single Collision */
#घोषणा HV_SCC_LOWER	PHY_REG(HV_STATS_PAGE, 17)
#घोषणा HV_ECOL_UPPER	PHY_REG(HV_STATS_PAGE, 18)	/* Excessive Coll. */
#घोषणा HV_ECOL_LOWER	PHY_REG(HV_STATS_PAGE, 19)
#घोषणा HV_MCC_UPPER	PHY_REG(HV_STATS_PAGE, 20)	/* Multiple Collision */
#घोषणा HV_MCC_LOWER	PHY_REG(HV_STATS_PAGE, 21)
#घोषणा HV_LATECOL_UPPER PHY_REG(HV_STATS_PAGE, 23)	/* Late Collision */
#घोषणा HV_LATECOL_LOWER PHY_REG(HV_STATS_PAGE, 24)
#घोषणा HV_COLC_UPPER	PHY_REG(HV_STATS_PAGE, 25)	/* Collision */
#घोषणा HV_COLC_LOWER	PHY_REG(HV_STATS_PAGE, 26)
#घोषणा HV_DC_UPPER	PHY_REG(HV_STATS_PAGE, 27)	/* Defer Count */
#घोषणा HV_DC_LOWER	PHY_REG(HV_STATS_PAGE, 28)
#घोषणा HV_TNCRS_UPPER	PHY_REG(HV_STATS_PAGE, 29)	/* Tx with no CRS */
#घोषणा HV_TNCRS_LOWER	PHY_REG(HV_STATS_PAGE, 30)

#घोषणा E1000_FCRTV_PCH	0x05F40	/* PCH Flow Control Refresh Timer Value */

#घोषणा E1000_NVM_K1_CONFIG	0x1B	/* NVM K1 Config Word */
#घोषणा E1000_NVM_K1_ENABLE	0x1	/* NVM Enable K1 bit */

/* SMBus Control Phy Register */
#घोषणा CV_SMB_CTRL		PHY_REG(769, 23)
#घोषणा CV_SMB_CTRL_FORCE_SMBUS	0x0001

/* I218 Ultra Low Power Configuration 1 Register */
#घोषणा I218_ULP_CONFIG1		PHY_REG(779, 16)
#घोषणा I218_ULP_CONFIG1_START		0x0001	/* Start स्वतः ULP config */
#घोषणा I218_ULP_CONFIG1_IND		0x0004	/* Pwr up from ULP indication */
#घोषणा I218_ULP_CONFIG1_STICKY_ULP	0x0010	/* Set sticky ULP mode */
#घोषणा I218_ULP_CONFIG1_INBAND_EXIT	0x0020	/* Inband on ULP निकास */
#घोषणा I218_ULP_CONFIG1_WOL_HOST	0x0040	/* WoL Host on ULP निकास */
#घोषणा I218_ULP_CONFIG1_RESET_TO_SMBUS	0x0100	/* Reset to SMBus mode */
/* enable ULP even अगर when phy घातered करोwn via lanphypc */
#घोषणा I218_ULP_CONFIG1_EN_ULP_LANPHYPC	0x0400
/* disable clear of sticky ULP on PERST */
#घोषणा I218_ULP_CONFIG1_DIS_CLR_STICKY_ON_PERST	0x0800
#घोषणा I218_ULP_CONFIG1_DISABLE_SMB_PERST	0x1000	/* Disable on PERST# */

/* SMBus Address Phy Register */
#घोषणा HV_SMB_ADDR		PHY_REG(768, 26)
#घोषणा HV_SMB_ADDR_MASK	0x007F
#घोषणा HV_SMB_ADDR_PEC_EN	0x0200
#घोषणा HV_SMB_ADDR_VALID	0x0080
#घोषणा HV_SMB_ADDR_FREQ_MASK		0x1100
#घोषणा HV_SMB_ADDR_FREQ_LOW_SHIFT	8
#घोषणा HV_SMB_ADDR_FREQ_HIGH_SHIFT	12

/* Strapping Option Register - RO */
#घोषणा E1000_STRAP			0x0000C
#घोषणा E1000_STRAP_SMBUS_ADDRESS_MASK	0x00FE0000
#घोषणा E1000_STRAP_SMBUS_ADDRESS_SHIFT	17
#घोषणा E1000_STRAP_SMT_FREQ_MASK	0x00003000
#घोषणा E1000_STRAP_SMT_FREQ_SHIFT	12

/* OEM Bits Phy Register */
#घोषणा HV_OEM_BITS		PHY_REG(768, 25)
#घोषणा HV_OEM_BITS_LPLU	0x0004	/* Low Power Link Up */
#घोषणा HV_OEM_BITS_GBE_DIS	0x0040	/* Gigabit Disable */
#घोषणा HV_OEM_BITS_RESTART_AN	0x0400	/* Restart Auto-negotiation */

/* KMRN Mode Control */
#घोषणा HV_KMRN_MODE_CTRL	PHY_REG(769, 16)
#घोषणा HV_KMRN_MDIO_SLOW	0x0400

/* KMRN FIFO Control and Status */
#घोषणा HV_KMRN_FIFO_CTRLSTA			PHY_REG(770, 16)
#घोषणा HV_KMRN_FIFO_CTRLSTA_PREAMBLE_MASK	0x7000
#घोषणा HV_KMRN_FIFO_CTRLSTA_PREAMBLE_SHIFT	12

/* PHY Power Management Control */
#घोषणा HV_PM_CTRL		PHY_REG(770, 17)
#घोषणा HV_PM_CTRL_K1_CLK_REQ		0x200
#घोषणा HV_PM_CTRL_K1_ENABLE		0x4000

#घोषणा I217_PLL_CLOCK_GATE_REG	PHY_REG(772, 28)
#घोषणा I217_PLL_CLOCK_GATE_MASK	0x07FF

#घोषणा SW_FLAG_TIMEOUT		1000	/* SW Semaphore flag समयout in ms */

/* Inband Control */
#घोषणा I217_INBAND_CTRL				PHY_REG(770, 18)
#घोषणा I217_INBAND_CTRL_LINK_STAT_TX_TIMEOUT_MASK	0x3F00
#घोषणा I217_INBAND_CTRL_LINK_STAT_TX_TIMEOUT_SHIFT	8

/* Low Power Idle GPIO Control */
#घोषणा I217_LPI_GPIO_CTRL			PHY_REG(772, 18)
#घोषणा I217_LPI_GPIO_CTRL_AUTO_EN_LPI		0x0800

/* PHY Low Power Idle Control */
#घोषणा I82579_LPI_CTRL				PHY_REG(772, 20)
#घोषणा I82579_LPI_CTRL_100_ENABLE		0x2000
#घोषणा I82579_LPI_CTRL_1000_ENABLE		0x4000
#घोषणा I82579_LPI_CTRL_ENABLE_MASK		0x6000
#घोषणा I82579_LPI_CTRL_FORCE_PLL_LOCK_COUNT	0x80

/* Extended Management Interface (EMI) Registers */
#घोषणा I82579_EMI_ADDR		0x10
#घोषणा I82579_EMI_DATA		0x11
#घोषणा I82579_LPI_UPDATE_TIMER	0x4805	/* in 40ns units + 40 ns base value */
#घोषणा I82579_MSE_THRESHOLD	0x084F	/* 82579 Mean Square Error Threshold */
#घोषणा I82577_MSE_THRESHOLD	0x0887	/* 82577 Mean Square Error Threshold */
#घोषणा I82579_MSE_LINK_DOWN	0x2411	/* MSE count beक्रमe dropping link */
#घोषणा I82579_RX_CONFIG		0x3412	/* Receive configuration */
#घोषणा I82579_LPI_PLL_SHUT		0x4412	/* LPI PLL Shut Enable */
#घोषणा I82579_EEE_PCS_STATUS		0x182E	/* IEEE MMD Register 3.1 >> 8 */
#घोषणा I82579_EEE_CAPABILITY		0x0410	/* IEEE MMD Register 3.20 */
#घोषणा I82579_EEE_ADVERTISEMENT	0x040E	/* IEEE MMD Register 7.60 */
#घोषणा I82579_EEE_LP_ABILITY		0x040F	/* IEEE MMD Register 7.61 */
#घोषणा I82579_EEE_100_SUPPORTED	(1 << 1)	/* 100BaseTx EEE */
#घोषणा I82579_EEE_1000_SUPPORTED	(1 << 2)	/* 1000BaseTx EEE */
#घोषणा I82579_LPI_100_PLL_SHUT	(1 << 2)	/* 100M LPI PLL Shut Enabled */
#घोषणा I217_EEE_PCS_STATUS	0x9401	/* IEEE MMD Register 3.1 */
#घोषणा I217_EEE_CAPABILITY	0x8000	/* IEEE MMD Register 3.20 */
#घोषणा I217_EEE_ADVERTISEMENT	0x8001	/* IEEE MMD Register 7.60 */
#घोषणा I217_EEE_LP_ABILITY	0x8002	/* IEEE MMD Register 7.61 */
#घोषणा I217_RX_CONFIG		0xB20C	/* Receive configuration */

#घोषणा E1000_EEE_RX_LPI_RCVD	0x0400	/* Tx LP idle received */
#घोषणा E1000_EEE_TX_LPI_RCVD	0x0800	/* Rx LP idle received */

/* Intel Rapid Start Technology Support */
#घोषणा I217_PROXY_CTRL		BM_PHY_REG(BM_WUC_PAGE, 70)
#घोषणा I217_PROXY_CTRL_AUTO_DISABLE	0x0080
#घोषणा I217_SxCTRL			PHY_REG(BM_PORT_CTRL_PAGE, 28)
#घोषणा I217_SxCTRL_ENABLE_LPI_RESET	0x1000
#घोषणा I217_CGFREG			PHY_REG(772, 29)
#घोषणा I217_CGFREG_ENABLE_MTA_RESET	0x0002
#घोषणा I217_MEMPWR			PHY_REG(772, 26)
#घोषणा I217_MEMPWR_DISABLE_SMB_RELEASE	0x0010

/* Receive Address Initial CRC Calculation */
#घोषणा E1000_PCH_RAICC(_n)	(0x05F50 + ((_n) * 4))

/* Latency Tolerance Reporting */
#घोषणा E1000_LTRV			0x000F8
#घोषणा E1000_LTRV_SCALE_MAX		5
#घोषणा E1000_LTRV_SCALE_FACTOR		5
#घोषणा E1000_LTRV_REQ_SHIFT		15
#घोषणा E1000_LTRV_NOSNOOP_SHIFT	16
#घोषणा E1000_LTRV_SEND			(1 << 30)

/* Proprietary Latency Tolerance Reporting PCI Capability */
#घोषणा E1000_PCI_LTR_CAP_LPT		0xA8

व्योम e1000e_ग_लिखो_protect_nvm_ich8lan(काष्ठा e1000_hw *hw);
व्योम e1000e_set_kmrn_lock_loss_workaround_ich8lan(काष्ठा e1000_hw *hw,
						  bool state);
व्योम e1000e_igp3_phy_घातerकरोwn_workaround_ich8lan(काष्ठा e1000_hw *hw);
व्योम e1000e_gig_करोwnshअगरt_workaround_ich8lan(काष्ठा e1000_hw *hw);
व्योम e1000_suspend_workarounds_ich8lan(काष्ठा e1000_hw *hw);
व्योम e1000_resume_workarounds_pchlan(काष्ठा e1000_hw *hw);
s32 e1000_configure_k1_ich8lan(काष्ठा e1000_hw *hw, bool k1_enable);
व्योम e1000_copy_rx_addrs_to_phy_ich8lan(काष्ठा e1000_hw *hw);
s32 e1000_lv_jumbo_workaround_ich8lan(काष्ठा e1000_hw *hw, bool enable);
s32 e1000_पढ़ो_emi_reg_locked(काष्ठा e1000_hw *hw, u16 addr, u16 *data);
s32 e1000_ग_लिखो_emi_reg_locked(काष्ठा e1000_hw *hw, u16 addr, u16 data);
s32 e1000_set_eee_pchlan(काष्ठा e1000_hw *hw);
s32 e1000_enable_ulp_lpt_lp(काष्ठा e1000_hw *hw, bool to_sx);
#पूर्ण_अगर /* _E1000E_ICH8LAN_H_ */
