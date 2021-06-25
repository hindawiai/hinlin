<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (c) 2014 Realtek Semiconductor Corp. All rights reserved.
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/list.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ip6_checksum.h>
#समावेश <uapi/linux/mdपन.स>
#समावेश <linux/mdपन.स>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/suspend.h>
#समावेश <linux/atomic.h>
#समावेश <linux/acpi.h>
#समावेश <linux/firmware.h>
#समावेश <crypto/hash.h>
#समावेश <linux/usb/r8152.h>

/* Inक्रमmation क्रम net-next */
#घोषणा NETNEXT_VERSION		"12"

/* Inक्रमmation क्रम net */
#घोषणा NET_VERSION		"11"

#घोषणा DRIVER_VERSION		"v1." NETNEXT_VERSION "." NET_VERSION
#घोषणा DRIVER_AUTHOR "Realtek linux nic maintainers <nic_swsd@realtek.com>"
#घोषणा DRIVER_DESC "Realtek RTL8152/RTL8153 Based USB Ethernet Adapters"
#घोषणा MODULENAME "r8152"

#घोषणा R8152_PHY_ID		32

#घोषणा PLA_IDR			0xc000
#घोषणा PLA_RCR			0xc010
#घोषणा PLA_RCR1		0xc012
#घोषणा PLA_RMS			0xc016
#घोषणा PLA_RXFIFO_CTRL0	0xc0a0
#घोषणा PLA_RXFIFO_FULL		0xc0a2
#घोषणा PLA_RXFIFO_CTRL1	0xc0a4
#घोषणा PLA_RX_FIFO_FULL	0xc0a6
#घोषणा PLA_RXFIFO_CTRL2	0xc0a8
#घोषणा PLA_RX_FIFO_EMPTY	0xc0aa
#घोषणा PLA_DMY_REG0		0xc0b0
#घोषणा PLA_FMC			0xc0b4
#घोषणा PLA_CFG_WOL		0xc0b6
#घोषणा PLA_TEREDO_CFG		0xc0bc
#घोषणा PLA_TEREDO_WAKE_BASE	0xc0c4
#घोषणा PLA_MAR			0xcd00
#घोषणा PLA_BACKUP		0xd000
#घोषणा PLA_BDC_CR		0xd1a0
#घोषणा PLA_TEREDO_TIMER	0xd2cc
#घोषणा PLA_REALWOW_TIMER	0xd2e8
#घोषणा PLA_UPHY_TIMER		0xd388
#घोषणा PLA_SUSPEND_FLAG	0xd38a
#घोषणा PLA_INDICATE_FALG	0xd38c
#घोषणा PLA_MACDBG_PRE		0xd38c	/* RTL_VER_04 only */
#घोषणा PLA_MACDBG_POST		0xd38e	/* RTL_VER_04 only */
#घोषणा PLA_EXTRA_STATUS	0xd398
#घोषणा PLA_GPHY_CTRL		0xd3ae
#घोषणा PLA_POL_GPIO_CTRL	0xdc6a
#घोषणा PLA_EFUSE_DATA		0xdd00
#घोषणा PLA_EFUSE_CMD		0xdd02
#घोषणा PLA_LEDSEL		0xdd90
#घोषणा PLA_LED_FEATURE		0xdd92
#घोषणा PLA_PHYAR		0xde00
#घोषणा PLA_BOOT_CTRL		0xe004
#घोषणा PLA_LWAKE_CTRL_REG	0xe007
#घोषणा PLA_GPHY_INTR_IMR	0xe022
#घोषणा PLA_EEE_CR		0xe040
#घोषणा PLA_EEE_TXTWSYS		0xe04c
#घोषणा PLA_EEE_TXTWSYS_2P5G	0xe058
#घोषणा PLA_EEEP_CR		0xe080
#घोषणा PLA_MAC_PWR_CTRL	0xe0c0
#घोषणा PLA_MAC_PWR_CTRL2	0xe0ca
#घोषणा PLA_MAC_PWR_CTRL3	0xe0cc
#घोषणा PLA_MAC_PWR_CTRL4	0xe0ce
#घोषणा PLA_WDT6_CTRL		0xe428
#घोषणा PLA_TCR0		0xe610
#घोषणा PLA_TCR1		0xe612
#घोषणा PLA_MTPS		0xe615
#घोषणा PLA_TXFIFO_CTRL		0xe618
#घोषणा PLA_TXFIFO_FULL		0xe61a
#घोषणा PLA_RSTTALLY		0xe800
#घोषणा PLA_CR			0xe813
#घोषणा PLA_CRWECR		0xe81c
#घोषणा PLA_CONFIG12		0xe81e	/* CONFIG1, CONFIG2 */
#घोषणा PLA_CONFIG34		0xe820	/* CONFIG3, CONFIG4 */
#घोषणा PLA_CONFIG5		0xe822
#घोषणा PLA_PHY_PWR		0xe84c
#घोषणा PLA_OOB_CTRL		0xe84f
#घोषणा PLA_CPCR		0xe854
#घोषणा PLA_MISC_0		0xe858
#घोषणा PLA_MISC_1		0xe85a
#घोषणा PLA_OCP_GPHY_BASE	0xe86c
#घोषणा PLA_TALLYCNT		0xe890
#घोषणा PLA_SFF_STS_7		0xe8de
#घोषणा PLA_PHYSTATUS		0xe908
#घोषणा PLA_CONFIG6		0xe90a /* CONFIG6 */
#घोषणा PLA_USB_CFG		0xe952
#घोषणा PLA_BP_BA		0xfc26
#घोषणा PLA_BP_0		0xfc28
#घोषणा PLA_BP_1		0xfc2a
#घोषणा PLA_BP_2		0xfc2c
#घोषणा PLA_BP_3		0xfc2e
#घोषणा PLA_BP_4		0xfc30
#घोषणा PLA_BP_5		0xfc32
#घोषणा PLA_BP_6		0xfc34
#घोषणा PLA_BP_7		0xfc36
#घोषणा PLA_BP_EN		0xfc38

#घोषणा USB_USB2PHY		0xb41e
#घोषणा USB_SSPHYLINK1		0xb426
#घोषणा USB_SSPHYLINK2		0xb428
#घोषणा USB_L1_CTRL		0xb45e
#घोषणा USB_U2P3_CTRL		0xb460
#घोषणा USB_CSR_DUMMY1		0xb464
#घोषणा USB_CSR_DUMMY2		0xb466
#घोषणा USB_DEV_STAT		0xb808
#घोषणा USB_CONNECT_TIMER	0xcbf8
#घोषणा USB_MSC_TIMER		0xcbfc
#घोषणा USB_BURST_SIZE		0xcfc0
#घोषणा USB_FW_FIX_EN0		0xcfca
#घोषणा USB_FW_FIX_EN1		0xcfcc
#घोषणा USB_LPM_CONFIG		0xcfd8
#घोषणा USB_ECM_OPTION		0xcfee
#घोषणा USB_CSTMR		0xcfef	/* RTL8153A */
#घोषणा USB_MISC_2		0xcfff
#घोषणा USB_ECM_OP		0xd26b
#घोषणा USB_GPHY_CTRL		0xd284
#घोषणा USB_SPEED_OPTION	0xd32a
#घोषणा USB_FW_CTRL		0xd334	/* RTL8153B */
#घोषणा USB_FC_TIMER		0xd340
#घोषणा USB_USB_CTRL		0xd406
#घोषणा USB_PHY_CTRL		0xd408
#घोषणा USB_TX_AGG		0xd40a
#घोषणा USB_RX_BUF_TH		0xd40c
#घोषणा USB_USB_TIMER		0xd428
#घोषणा USB_RX_EARLY_TIMEOUT	0xd42c
#घोषणा USB_RX_EARLY_SIZE	0xd42e
#घोषणा USB_PM_CTRL_STATUS	0xd432	/* RTL8153A */
#घोषणा USB_RX_EXTRA_AGGR_TMR	0xd432	/* RTL8153B */
#घोषणा USB_TX_DMA		0xd434
#घोषणा USB_UPT_RXDMA_OWN	0xd437
#घोषणा USB_UPHY3_MDCMDIO	0xd480
#घोषणा USB_TOLERANCE		0xd490
#घोषणा USB_LPM_CTRL		0xd41a
#घोषणा USB_BMU_RESET		0xd4b0
#घोषणा USB_BMU_CONFIG		0xd4b4
#घोषणा USB_U1U2_TIMER		0xd4da
#घोषणा USB_FW_TASK		0xd4e8	/* RTL8153B */
#घोषणा USB_RX_AGGR_NUM		0xd4ee
#घोषणा USB_UPS_CTRL		0xd800
#घोषणा USB_POWER_CUT		0xd80a
#घोषणा USB_MISC_0		0xd81a
#घोषणा USB_MISC_1		0xd81f
#घोषणा USB_AFE_CTRL2		0xd824
#घोषणा USB_UPHY_XTAL		0xd826
#घोषणा USB_UPS_CFG		0xd842
#घोषणा USB_UPS_FLAGS		0xd848
#घोषणा USB_WDT1_CTRL		0xe404
#घोषणा USB_WDT11_CTRL		0xe43c
#घोषणा USB_BP_BA		PLA_BP_BA
#घोषणा USB_BP_0		PLA_BP_0
#घोषणा USB_BP_1		PLA_BP_1
#घोषणा USB_BP_2		PLA_BP_2
#घोषणा USB_BP_3		PLA_BP_3
#घोषणा USB_BP_4		PLA_BP_4
#घोषणा USB_BP_5		PLA_BP_5
#घोषणा USB_BP_6		PLA_BP_6
#घोषणा USB_BP_7		PLA_BP_7
#घोषणा USB_BP_EN		PLA_BP_EN	/* RTL8153A */
#घोषणा USB_BP_8		0xfc38		/* RTL8153B */
#घोषणा USB_BP_9		0xfc3a
#घोषणा USB_BP_10		0xfc3c
#घोषणा USB_BP_11		0xfc3e
#घोषणा USB_BP_12		0xfc40
#घोषणा USB_BP_13		0xfc42
#घोषणा USB_BP_14		0xfc44
#घोषणा USB_BP_15		0xfc46
#घोषणा USB_BP2_EN		0xfc48

/* OCP Registers */
#घोषणा OCP_ALDPS_CONFIG	0x2010
#घोषणा OCP_EEE_CONFIG1		0x2080
#घोषणा OCP_EEE_CONFIG2		0x2092
#घोषणा OCP_EEE_CONFIG3		0x2094
#घोषणा OCP_BASE_MII		0xa400
#घोषणा OCP_EEE_AR		0xa41a
#घोषणा OCP_EEE_DATA		0xa41c
#घोषणा OCP_PHY_STATUS		0xa420
#घोषणा OCP_NCTL_CFG		0xa42c
#घोषणा OCP_POWER_CFG		0xa430
#घोषणा OCP_EEE_CFG		0xa432
#घोषणा OCP_SRAM_ADDR		0xa436
#घोषणा OCP_SRAM_DATA		0xa438
#घोषणा OCP_DOWN_SPEED		0xa442
#घोषणा OCP_EEE_ABLE		0xa5c4
#घोषणा OCP_EEE_ADV		0xa5d0
#घोषणा OCP_EEE_LPABLE		0xa5d2
#घोषणा OCP_10GBT_CTRL		0xa5d4
#घोषणा OCP_10GBT_STAT		0xa5d6
#घोषणा OCP_EEE_ADV2		0xa6d4
#घोषणा OCP_PHY_STATE		0xa708		/* nway state क्रम 8153 */
#घोषणा OCP_PHY_PATCH_STAT	0xb800
#घोषणा OCP_PHY_PATCH_CMD	0xb820
#घोषणा OCP_PHY_LOCK		0xb82e
#घोषणा OCP_ADC_IOFFSET		0xbcfc
#घोषणा OCP_ADC_CFG		0xbc06
#घोषणा OCP_SYSCLK_CFG		0xc416

/* SRAM Register */
#घोषणा SRAM_GREEN_CFG		0x8011
#घोषणा SRAM_LPF_CFG		0x8012
#घोषणा SRAM_GPHY_FW_VER	0x801e
#घोषणा SRAM_10M_AMP1		0x8080
#घोषणा SRAM_10M_AMP2		0x8082
#घोषणा SRAM_IMPEDANCE		0x8084
#घोषणा SRAM_PHY_LOCK		0xb82e

/* PLA_RCR */
#घोषणा RCR_AAP			0x00000001
#घोषणा RCR_APM			0x00000002
#घोषणा RCR_AM			0x00000004
#घोषणा RCR_AB			0x00000008
#घोषणा RCR_ACPT_ALL		(RCR_AAP | RCR_APM | RCR_AM | RCR_AB)
#घोषणा SLOT_EN			BIT(11)

/* PLA_RCR1 */
#घोषणा OUTER_VLAN		BIT(7)
#घोषणा INNER_VLAN		BIT(6)

/* PLA_RXFIFO_CTRL0 */
#घोषणा RXFIFO_THR1_NORMAL	0x00080002
#घोषणा RXFIFO_THR1_OOB		0x01800003

/* PLA_RXFIFO_FULL */
#घोषणा RXFIFO_FULL_MASK	0xfff

/* PLA_RXFIFO_CTRL1 */
#घोषणा RXFIFO_THR2_FULL	0x00000060
#घोषणा RXFIFO_THR2_HIGH	0x00000038
#घोषणा RXFIFO_THR2_OOB		0x0000004a
#घोषणा RXFIFO_THR2_NORMAL	0x00a0

/* PLA_RXFIFO_CTRL2 */
#घोषणा RXFIFO_THR3_FULL	0x00000078
#घोषणा RXFIFO_THR3_HIGH	0x00000048
#घोषणा RXFIFO_THR3_OOB		0x0000005a
#घोषणा RXFIFO_THR3_NORMAL	0x0110

/* PLA_TXFIFO_CTRL */
#घोषणा TXFIFO_THR_NORMAL	0x00400008
#घोषणा TXFIFO_THR_NORMAL2	0x01000008

/* PLA_DMY_REG0 */
#घोषणा ECM_ALDPS		0x0002

/* PLA_FMC */
#घोषणा FMC_FCR_MCU_EN		0x0001

/* PLA_EEEP_CR */
#घोषणा EEEP_CR_EEEP_TX		0x0002

/* PLA_WDT6_CTRL */
#घोषणा WDT6_SET_MODE		0x0010

/* PLA_TCR0 */
#घोषणा TCR0_TX_EMPTY		0x0800
#घोषणा TCR0_AUTO_FIFO		0x0080

/* PLA_TCR1 */
#घोषणा VERSION_MASK		0x7cf0
#घोषणा IFG_MASK		(BIT(3) | BIT(9) | BIT(8))
#घोषणा IFG_144NS		BIT(9)
#घोषणा IFG_96NS		(BIT(9) | BIT(8))

/* PLA_MTPS */
#घोषणा MTPS_JUMBO		(12 * 1024 / 64)
#घोषणा MTPS_DEFAULT		(6 * 1024 / 64)

/* PLA_RSTTALLY */
#घोषणा TALLY_RESET		0x0001

/* PLA_CR */
#घोषणा CR_RST			0x10
#घोषणा CR_RE			0x08
#घोषणा CR_TE			0x04

/* PLA_CRWECR */
#घोषणा CRWECR_NORAML		0x00
#घोषणा CRWECR_CONFIG		0xc0

/* PLA_OOB_CTRL */
#घोषणा NOW_IS_OOB		0x80
#घोषणा TXFIFO_EMPTY		0x20
#घोषणा RXFIFO_EMPTY		0x10
#घोषणा LINK_LIST_READY		0x02
#घोषणा DIS_MCU_CLROOB		0x01
#घोषणा FIFO_EMPTY		(TXFIFO_EMPTY | RXFIFO_EMPTY)

/* PLA_MISC_1 */
#घोषणा RXDY_GATED_EN		0x0008

/* PLA_SFF_STS_7 */
#घोषणा RE_INIT_LL		0x8000
#घोषणा MCU_BORW_EN		0x4000

/* PLA_CPCR */
#घोषणा FLOW_CTRL_EN		BIT(0)
#घोषणा CPCR_RX_VLAN		0x0040

/* PLA_CFG_WOL */
#घोषणा MAGIC_EN		0x0001

/* PLA_TEREDO_CFG */
#घोषणा TEREDO_SEL		0x8000
#घोषणा TEREDO_WAKE_MASK	0x7f00
#घोषणा TEREDO_RS_EVENT_MASK	0x00fe
#घोषणा OOB_TEREDO_EN		0x0001

/* PLA_BDC_CR */
#घोषणा ALDPS_PROXY_MODE	0x0001

/* PLA_EFUSE_CMD */
#घोषणा EFUSE_READ_CMD		BIT(15)
#घोषणा EFUSE_DATA_BIT16	BIT(7)

/* PLA_CONFIG34 */
#घोषणा LINK_ON_WAKE_EN		0x0010
#घोषणा LINK_OFF_WAKE_EN	0x0008

/* PLA_CONFIG6 */
#घोषणा LANWAKE_CLR_EN		BIT(0)

/* PLA_USB_CFG */
#घोषणा EN_XG_LIP		BIT(1)
#घोषणा EN_G_LIP		BIT(2)

/* PLA_CONFIG5 */
#घोषणा BWF_EN			0x0040
#घोषणा MWF_EN			0x0020
#घोषणा UWF_EN			0x0010
#घोषणा LAN_WAKE_EN		0x0002

/* PLA_LED_FEATURE */
#घोषणा LED_MODE_MASK		0x0700

/* PLA_PHY_PWR */
#घोषणा TX_10M_IDLE_EN		0x0080
#घोषणा PFM_PWM_SWITCH		0x0040
#घोषणा TEST_IO_OFF		BIT(4)

/* PLA_MAC_PWR_CTRL */
#घोषणा D3_CLK_GATED_EN		0x00004000
#घोषणा MCU_CLK_RATIO		0x07010f07
#घोषणा MCU_CLK_RATIO_MASK	0x0f0f0f0f
#घोषणा ALDPS_SPDWN_RATIO	0x0f87

/* PLA_MAC_PWR_CTRL2 */
#घोषणा EEE_SPDWN_RATIO		0x8007
#घोषणा MAC_CLK_SPDWN_EN	BIT(15)
#घोषणा EEE_SPDWN_RATIO_MASK	0xff

/* PLA_MAC_PWR_CTRL3 */
#घोषणा PLA_MCU_SPDWN_EN	BIT(14)
#घोषणा PKT_AVAIL_SPDWN_EN	0x0100
#घोषणा SUSPEND_SPDWN_EN	0x0004
#घोषणा U1U2_SPDWN_EN		0x0002
#घोषणा L1_SPDWN_EN		0x0001

/* PLA_MAC_PWR_CTRL4 */
#घोषणा PWRSAVE_SPDWN_EN	0x1000
#घोषणा RXDV_SPDWN_EN		0x0800
#घोषणा TX10MIDLE_EN		0x0100
#घोषणा IDLE_SPDWN_EN		BIT(6)
#घोषणा TP100_SPDWN_EN		0x0020
#घोषणा TP500_SPDWN_EN		0x0010
#घोषणा TP1000_SPDWN_EN		0x0008
#घोषणा EEE_SPDWN_EN		0x0001

/* PLA_GPHY_INTR_IMR */
#घोषणा GPHY_STS_MSK		0x0001
#घोषणा SPEED_DOWN_MSK		0x0002
#घोषणा SPDWN_RXDV_MSK		0x0004
#घोषणा SPDWN_LINKCHG_MSK	0x0008

/* PLA_PHYAR */
#घोषणा PHYAR_FLAG		0x80000000

/* PLA_EEE_CR */
#घोषणा EEE_RX_EN		0x0001
#घोषणा EEE_TX_EN		0x0002

/* PLA_BOOT_CTRL */
#घोषणा AUTOLOAD_DONE		0x0002

/* PLA_LWAKE_CTRL_REG */
#घोषणा LANWAKE_PIN		BIT(7)

/* PLA_SUSPEND_FLAG */
#घोषणा LINK_CHG_EVENT		BIT(0)

/* PLA_INDICATE_FALG */
#घोषणा UPCOMING_RUNTIME_D3	BIT(0)

/* PLA_MACDBG_PRE and PLA_MACDBG_POST */
#घोषणा DEBUG_OE		BIT(0)
#घोषणा DEBUG_LTSSM		0x0082

/* PLA_EXTRA_STATUS */
#घोषणा CUR_LINK_OK		BIT(15)
#घोषणा U3P3_CHECK_EN		BIT(7)	/* RTL_VER_05 only */
#घोषणा LINK_CHANGE_FLAG	BIT(8)
#घोषणा POLL_LINK_CHG		BIT(0)

/* PLA_GPHY_CTRL */
#घोषणा GPHY_FLASH		BIT(1)

/* PLA_POL_GPIO_CTRL */
#घोषणा DACK_DET_EN		BIT(15)
#घोषणा POL_GPHY_PATCH		BIT(4)

/* USB_USB2PHY */
#घोषणा USB2PHY_SUSPEND		0x0001
#घोषणा USB2PHY_L1		0x0002

/* USB_SSPHYLINK1 */
#घोषणा DELAY_PHY_PWR_CHG	BIT(1)

/* USB_SSPHYLINK2 */
#घोषणा pwd_dn_scale_mask	0x3ffe
#घोषणा pwd_dn_scale(x)		((x) << 1)

/* USB_CSR_DUMMY1 */
#घोषणा DYNAMIC_BURST		0x0001

/* USB_CSR_DUMMY2 */
#घोषणा EP4_FULL_FC		0x0001

/* USB_DEV_STAT */
#घोषणा STAT_SPEED_MASK		0x0006
#घोषणा STAT_SPEED_HIGH		0x0000
#घोषणा STAT_SPEED_FULL		0x0002

/* USB_FW_FIX_EN0 */
#घोषणा FW_FIX_SUSPEND		BIT(14)

/* USB_FW_FIX_EN1 */
#घोषणा FW_IP_RESET_EN		BIT(9)

/* USB_LPM_CONFIG */
#घोषणा LPM_U1U2_EN		BIT(0)

/* USB_TX_AGG */
#घोषणा TX_AGG_MAX_THRESHOLD	0x03

/* USB_RX_BUF_TH */
#घोषणा RX_THR_SUPPER		0x0c350180
#घोषणा RX_THR_HIGH		0x7a120180
#घोषणा RX_THR_SLOW		0xffff0180
#घोषणा RX_THR_B		0x00010001

/* USB_TX_DMA */
#घोषणा TEST_MODE_DISABLE	0x00000001
#घोषणा TX_SIZE_ADJUST1		0x00000100

/* USB_BMU_RESET */
#घोषणा BMU_RESET_EP_IN		0x01
#घोषणा BMU_RESET_EP_OUT	0x02

/* USB_BMU_CONFIG */
#घोषणा ACT_ODMA		BIT(1)

/* USB_UPT_RXDMA_OWN */
#घोषणा OWN_UPDATE		BIT(0)
#घोषणा OWN_CLEAR		BIT(1)

/* USB_FW_TASK */
#घोषणा FC_PATCH_TASK		BIT(1)

/* USB_RX_AGGR_NUM */
#घोषणा RX_AGGR_NUM_MASK	0x1ff

/* USB_UPS_CTRL */
#घोषणा POWER_CUT		0x0100

/* USB_PM_CTRL_STATUS */
#घोषणा RESUME_INDICATE		0x0001

/* USB_ECM_OPTION */
#घोषणा BYPASS_MAC_RESET	BIT(5)

/* USB_CSTMR */
#घोषणा FORCE_SUPER		BIT(0)

/* USB_MISC_2 */
#घोषणा UPS_FORCE_PWR_DOWN	BIT(0)

/* USB_ECM_OP */
#घोषणा	EN_ALL_SPEED		BIT(0)

/* USB_GPHY_CTRL */
#घोषणा GPHY_PATCH_DONE		BIT(2)
#घोषणा BYPASS_FLASH		BIT(5)
#घोषणा BACKUP_RESTRORE		BIT(6)

/* USB_SPEED_OPTION */
#घोषणा RG_PWRDN_EN		BIT(8)
#घोषणा ALL_SPEED_OFF		BIT(9)

/* USB_FW_CTRL */
#घोषणा FLOW_CTRL_PATCH_OPT	BIT(1)
#घोषणा AUTO_SPEEDUP		BIT(3)
#घोषणा FLOW_CTRL_PATCH_2	BIT(8)

/* USB_FC_TIMER */
#घोषणा CTRL_TIMER_EN		BIT(15)

/* USB_USB_CTRL */
#घोषणा CDC_ECM_EN		BIT(3)
#घोषणा RX_AGG_DISABLE		0x0010
#घोषणा RX_ZERO_EN		0x0080

/* USB_U2P3_CTRL */
#घोषणा U2P3_ENABLE		0x0001
#घोषणा RX_DETECT8		BIT(3)

/* USB_POWER_CUT */
#घोषणा PWR_EN			0x0001
#घोषणा PHASE2_EN		0x0008
#घोषणा UPS_EN			BIT(4)
#घोषणा USP_PREWAKE		BIT(5)

/* USB_MISC_0 */
#घोषणा PCUT_STATUS		0x0001

/* USB_RX_EARLY_TIMEOUT */
#घोषणा COALESCE_SUPER		 85000U
#घोषणा COALESCE_HIGH		250000U
#घोषणा COALESCE_SLOW		524280U

/* USB_WDT1_CTRL */
#घोषणा WTD1_EN			BIT(0)

/* USB_WDT11_CTRL */
#घोषणा TIMER11_EN		0x0001

/* USB_LPM_CTRL */
/* bit 4 ~ 5: fअगरo empty boundary */
#घोषणा FIFO_EMPTY_1FB		0x30	/* 0x1fb * 64 = 32448 bytes */
/* bit 2 ~ 3: LMP समयr */
#घोषणा LPM_TIMER_MASK		0x0c
#घोषणा LPM_TIMER_500MS		0x04	/* 500 ms */
#घोषणा LPM_TIMER_500US		0x0c	/* 500 us */
#घोषणा ROK_EXIT_LPM		0x02

/* USB_AFE_CTRL2 */
#घोषणा SEN_VAL_MASK		0xf800
#घोषणा SEN_VAL_NORMAL		0xa000
#घोषणा SEL_RXIDLE		0x0100

/* USB_UPHY_XTAL */
#घोषणा OOBS_POLLING		BIT(8)

/* USB_UPS_CFG */
#घोषणा SAW_CNT_1MS_MASK	0x0fff
#घोषणा MID_REVERSE		BIT(5)	/* RTL8156A */

/* USB_UPS_FLAGS */
#घोषणा UPS_FLAGS_R_TUNE		BIT(0)
#घोषणा UPS_FLAGS_EN_10M_CKDIV		BIT(1)
#घोषणा UPS_FLAGS_250M_CKDIV		BIT(2)
#घोषणा UPS_FLAGS_EN_ALDPS		BIT(3)
#घोषणा UPS_FLAGS_CTAP_SHORT_DIS	BIT(4)
#घोषणा UPS_FLAGS_SPEED_MASK		(0xf << 16)
#घोषणा ups_flags_speed(x)		((x) << 16)
#घोषणा UPS_FLAGS_EN_EEE		BIT(20)
#घोषणा UPS_FLAGS_EN_500M_EEE		BIT(21)
#घोषणा UPS_FLAGS_EN_EEE_CKDIV		BIT(22)
#घोषणा UPS_FLAGS_EEE_PLLOFF_100	BIT(23)
#घोषणा UPS_FLAGS_EEE_PLLOFF_GIGA	BIT(24)
#घोषणा UPS_FLAGS_EEE_CMOD_LV_EN	BIT(25)
#घोषणा UPS_FLAGS_EN_GREEN		BIT(26)
#घोषणा UPS_FLAGS_EN_FLOW_CTR		BIT(27)

क्रमागत spd_duplex अणु
	NWAY_10M_HALF,
	NWAY_10M_FULL,
	NWAY_100M_HALF,
	NWAY_100M_FULL,
	NWAY_1000M_FULL,
	FORCE_10M_HALF,
	FORCE_10M_FULL,
	FORCE_100M_HALF,
	FORCE_100M_FULL,
	FORCE_1000M_FULL,
	NWAY_2500M_FULL,
पूर्ण;

/* OCP_ALDPS_CONFIG */
#घोषणा ENPWRSAVE		0x8000
#घोषणा ENPDNPS			0x0200
#घोषणा LINKENA			0x0100
#घोषणा DIS_SDSAVE		0x0010

/* OCP_PHY_STATUS */
#घोषणा PHY_STAT_MASK		0x0007
#घोषणा PHY_STAT_EXT_INIT	2
#घोषणा PHY_STAT_LAN_ON		3
#घोषणा PHY_STAT_PWRDN		5

/* OCP_NCTL_CFG */
#घोषणा PGA_RETURN_EN		BIT(1)

/* OCP_POWER_CFG */
#घोषणा EEE_CLKDIV_EN		0x8000
#घोषणा EN_ALDPS		0x0004
#घोषणा EN_10M_PLLOFF		0x0001

/* OCP_EEE_CONFIG1 */
#घोषणा RG_TXLPI_MSK_HFDUP	0x8000
#घोषणा RG_MATCLR_EN		0x4000
#घोषणा EEE_10_CAP		0x2000
#घोषणा EEE_NWAY_EN		0x1000
#घोषणा TX_QUIET_EN		0x0200
#घोषणा RX_QUIET_EN		0x0100
#घोषणा sd_rise_समय_mask	0x0070
#घोषणा sd_rise_समय(x)		(min(x, 7) << 4)	/* bit 4 ~ 6 */
#घोषणा RG_RXLPI_MSK_HFDUP	0x0008
#घोषणा SDFALLTIME		0x0007	/* bit 0 ~ 2 */

/* OCP_EEE_CONFIG2 */
#घोषणा RG_LPIHYS_NUM		0x7000	/* bit 12 ~ 15 */
#घोषणा RG_DACQUIET_EN		0x0400
#घोषणा RG_LDVQUIET_EN		0x0200
#घोषणा RG_CKRSEL		0x0020
#घोषणा RG_EEEPRG_EN		0x0010

/* OCP_EEE_CONFIG3 */
#घोषणा fast_snr_mask		0xff80
#घोषणा fast_snr(x)		(min(x, 0x1ff) << 7)	/* bit 7 ~ 15 */
#घोषणा RG_LFS_SEL		0x0060	/* bit 6 ~ 5 */
#घोषणा MSK_PH			0x0006	/* bit 0 ~ 3 */

/* OCP_EEE_AR */
/* bit[15:14] function */
#घोषणा FUN_ADDR		0x0000
#घोषणा FUN_DATA		0x4000
/* bit[4:0] device addr */

/* OCP_EEE_CFG */
#घोषणा CTAP_SHORT_EN		0x0040
#घोषणा EEE10_EN		0x0010

/* OCP_DOWN_SPEED */
#घोषणा EN_EEE_CMODE		BIT(14)
#घोषणा EN_EEE_1000		BIT(13)
#घोषणा EN_EEE_100		BIT(12)
#घोषणा EN_10M_CLKDIV		BIT(11)
#घोषणा EN_10M_BGOFF		0x0080

/* OCP_10GBT_CTRL */
#घोषणा RTL_ADV2_5G_F_R		BIT(5)	/* Advertise 2.5GBASE-T fast-retrain */

/* OCP_PHY_STATE */
#घोषणा TXDIS_STATE		0x01
#घोषणा ABD_STATE		0x02

/* OCP_PHY_PATCH_STAT */
#घोषणा PATCH_READY		BIT(6)

/* OCP_PHY_PATCH_CMD */
#घोषणा PATCH_REQUEST		BIT(4)

/* OCP_PHY_LOCK */
#घोषणा PATCH_LOCK		BIT(0)

/* OCP_ADC_CFG */
#घोषणा CKADSEL_L		0x0100
#घोषणा ADC_EN			0x0080
#घोषणा EN_EMI_L		0x0040

/* OCP_SYSCLK_CFG */
#घोषणा sysclk_भाग_expo(x)	(min(x, 5) << 8)
#घोषणा clk_भाग_expo(x)		(min(x, 5) << 4)

/* SRAM_GREEN_CFG */
#घोषणा GREEN_ETH_EN		BIT(15)
#घोषणा R_TUNE_EN		BIT(11)

/* SRAM_LPF_CFG */
#घोषणा LPF_AUTO_TUNE		0x8000

/* SRAM_10M_AMP1 */
#घोषणा GDAC_IB_UPALL		0x0008

/* SRAM_10M_AMP2 */
#घोषणा AMP_DN			0x0200

/* SRAM_IMPEDANCE */
#घोषणा RX_DRIVING_MASK		0x6000

/* SRAM_PHY_LOCK */
#घोषणा PHY_PATCH_LOCK		0x0001

/* MAC PASSTHRU */
#घोषणा AD_MASK			0xfee0
#घोषणा BND_MASK		0x0004
#घोषणा BD_MASK			0x0001
#घोषणा EFUSE			0xcfdb
#घोषणा PASS_THRU_MASK		0x1

#घोषणा BP4_SUPER_ONLY		0x1578	/* RTL_VER_04 only */

क्रमागत rtl_रेजिस्टर_content अणु
	_2500bps	= BIT(10),
	_1250bps	= BIT(9),
	_500bps		= BIT(8),
	_tx_flow	= BIT(6),
	_rx_flow	= BIT(5),
	_1000bps	= 0x10,
	_100bps		= 0x08,
	_10bps		= 0x04,
	LINK_STATUS	= 0x02,
	FULL_DUP	= 0x01,
पूर्ण;

#घोषणा is_speed_2500(_speed)	(((_speed) & (_2500bps | LINK_STATUS)) == (_2500bps | LINK_STATUS))
#घोषणा is_flow_control(_speed)	(((_speed) & (_tx_flow | _rx_flow)) == (_tx_flow | _rx_flow))

#घोषणा RTL8152_MAX_TX		4
#घोषणा RTL8152_MAX_RX		10
#घोषणा INTबफ_मानE		2
#घोषणा TX_ALIGN		4
#घोषणा RX_ALIGN		8

#घोषणा RTL8152_RX_MAX_PENDING	4096
#घोषणा RTL8152_RXFG_HEADSZ	256

#घोषणा INTR_LINK		0x0004

#घोषणा RTL8152_RMS		(VLAN_ETH_FRAME_LEN + ETH_FCS_LEN)
#घोषणा RTL8153_RMS		RTL8153_MAX_PACKET
#घोषणा RTL8152_TX_TIMEOUT	(5 * HZ)
#घोषणा mtu_to_size(m)		((m) + VLAN_ETH_HLEN + ETH_FCS_LEN)
#घोषणा माप_प्रकारo_mtu(s)		((s) - VLAN_ETH_HLEN - ETH_FCS_LEN)
#घोषणा rx_reserved_size(x)	(mtu_to_size(x) + माप(काष्ठा rx_desc) + RX_ALIGN)

/* rtl8152 flags */
क्रमागत rtl8152_flags अणु
	RTL8152_UNPLUG = 0,
	RTL8152_SET_RX_MODE,
	WORK_ENABLE,
	RTL8152_LINK_CHG,
	SELECTIVE_SUSPEND,
	PHY_RESET,
	SCHEDULE_TASKLET,
	GREEN_ETHERNET,
पूर्ण;

#घोषणा DEVICE_ID_THINKPAD_THUNDERBOLT3_DOCK_GEN2	0x3082
#घोषणा DEVICE_ID_THINKPAD_USB_C_DOCK_GEN2		0xa387

काष्ठा tally_counter अणु
	__le64	tx_packets;
	__le64	rx_packets;
	__le64	tx_errors;
	__le32	rx_errors;
	__le16	rx_missed;
	__le16	align_errors;
	__le32	tx_one_collision;
	__le32	tx_multi_collision;
	__le64	rx_unicast;
	__le64	rx_broadcast;
	__le32	rx_multicast;
	__le16	tx_पातed;
	__le16	tx_underrun;
पूर्ण;

काष्ठा rx_desc अणु
	__le32 opts1;
#घोषणा RX_LEN_MASK			0x7fff

	__le32 opts2;
#घोषणा RD_UDP_CS			BIT(23)
#घोषणा RD_TCP_CS			BIT(22)
#घोषणा RD_IPV6_CS			BIT(20)
#घोषणा RD_IPV4_CS			BIT(19)

	__le32 opts3;
#घोषणा IPF				BIT(23) /* IP checksum fail */
#घोषणा UDPF				BIT(22) /* UDP checksum fail */
#घोषणा TCPF				BIT(21) /* TCP checksum fail */
#घोषणा RX_VLAN_TAG			BIT(16)

	__le32 opts4;
	__le32 opts5;
	__le32 opts6;
पूर्ण;

काष्ठा tx_desc अणु
	__le32 opts1;
#घोषणा TX_FS			BIT(31) /* First segment of a packet */
#घोषणा TX_LS			BIT(30) /* Final segment of a packet */
#घोषणा GTSENDV4		BIT(28)
#घोषणा GTSENDV6		BIT(27)
#घोषणा GTTCPHO_SHIFT		18
#घोषणा GTTCPHO_MAX		0x7fU
#घोषणा TX_LEN_MAX		0x3ffffU

	__le32 opts2;
#घोषणा UDP_CS			BIT(31) /* Calculate UDP/IP checksum */
#घोषणा TCP_CS			BIT(30) /* Calculate TCP/IP checksum */
#घोषणा IPV4_CS			BIT(29) /* Calculate IPv4 checksum */
#घोषणा IPV6_CS			BIT(28) /* Calculate IPv6 checksum */
#घोषणा MSS_SHIFT		17
#घोषणा MSS_MAX			0x7ffU
#घोषणा TCPHO_SHIFT		17
#घोषणा TCPHO_MAX		0x7ffU
#घोषणा TX_VLAN_TAG		BIT(16)
पूर्ण;

काष्ठा r8152;

काष्ठा rx_agg अणु
	काष्ठा list_head list, info_list;
	काष्ठा urb *urb;
	काष्ठा r8152 *context;
	काष्ठा page *page;
	व्योम *buffer;
पूर्ण;

काष्ठा tx_agg अणु
	काष्ठा list_head list;
	काष्ठा urb *urb;
	काष्ठा r8152 *context;
	व्योम *buffer;
	व्योम *head;
	u32 skb_num;
	u32 skb_len;
पूर्ण;

काष्ठा r8152 अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_device *udev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा net_device *netdev;
	काष्ठा urb *पूर्णांकr_urb;
	काष्ठा tx_agg tx_info[RTL8152_MAX_TX];
	काष्ठा list_head rx_info, rx_used;
	काष्ठा list_head rx_करोne, tx_मुक्त;
	काष्ठा sk_buff_head tx_queue, rx_queue;
	spinlock_t rx_lock, tx_lock;
	काष्ठा delayed_work schedule, hw_phy_work;
	काष्ठा mii_अगर_info mii;
	काष्ठा mutex control;	/* use क्रम hw setting */
#अगर_घोषित CONFIG_PM_SLEEP
	काष्ठा notअगरier_block pm_notअगरier;
#पूर्ण_अगर
	काष्ठा tasklet_काष्ठा tx_tl;

	काष्ठा rtl_ops अणु
		व्योम (*init)(काष्ठा r8152 *tp);
		पूर्णांक (*enable)(काष्ठा r8152 *tp);
		व्योम (*disable)(काष्ठा r8152 *tp);
		व्योम (*up)(काष्ठा r8152 *tp);
		व्योम (*करोwn)(काष्ठा r8152 *tp);
		व्योम (*unload)(काष्ठा r8152 *tp);
		पूर्णांक (*eee_get)(काष्ठा r8152 *tp, काष्ठा ethtool_eee *eee);
		पूर्णांक (*eee_set)(काष्ठा r8152 *tp, काष्ठा ethtool_eee *eee);
		bool (*in_nway)(काष्ठा r8152 *tp);
		व्योम (*hw_phy_cfg)(काष्ठा r8152 *tp);
		व्योम (*स्वतःsuspend_en)(काष्ठा r8152 *tp, bool enable);
		व्योम (*change_mtu)(काष्ठा r8152 *tp);
	पूर्ण rtl_ops;

	काष्ठा ups_info अणु
		u32 r_tune:1;
		u32 _10m_ckभाग:1;
		u32 _250m_ckभाग:1;
		u32 aldps:1;
		u32 lite_mode:2;
		u32 speed_duplex:4;
		u32 eee:1;
		u32 eee_lite:1;
		u32 eee_ckभाग:1;
		u32 eee_plloff_100:1;
		u32 eee_plloff_giga:1;
		u32 eee_cmod_lv:1;
		u32 green:1;
		u32 flow_control:1;
		u32 ctap_लघु_off:1;
	पूर्ण ups_info;

#घोषणा RTL_VER_SIZE		32

	काष्ठा rtl_fw अणु
		स्थिर अक्षर *fw_name;
		स्थिर काष्ठा firmware *fw;

		अक्षर version[RTL_VER_SIZE];
		पूर्णांक (*pre_fw)(काष्ठा r8152 *tp);
		पूर्णांक (*post_fw)(काष्ठा r8152 *tp);

		bool retry;
	पूर्ण rtl_fw;

	atomic_t rx_count;

	bool eee_en;
	पूर्णांक पूर्णांकr_पूर्णांकerval;
	u32 saved_wolopts;
	u32 msg_enable;
	u32 tx_qlen;
	u32 coalesce;
	u32 advertising;
	u32 rx_buf_sz;
	u32 rx_copyअवरोध;
	u32 rx_pending;
	u32 fc_छोड़ो_on, fc_छोड़ो_off;

	u32 support_2500full:1;
	u32 lenovo_macpassthru:1;
	u32 dell_tb_rx_agg_bug:1;
	u16 ocp_base;
	u16 speed;
	u16 eee_adv;
	u8 *पूर्णांकr_buff;
	u8 version;
	u8 duplex;
	u8 स्वतःneg;
पूर्ण;

/**
 * काष्ठा fw_block - block type and total length
 * @type: type of the current block, such as RTL_FW_END, RTL_FW_PLA,
 *	RTL_FW_USB and so on.
 * @length: total length of the current block.
 */
काष्ठा fw_block अणु
	__le32 type;
	__le32 length;
पूर्ण __packed;

/**
 * काष्ठा fw_header - header of the firmware file
 * @checksum: checksum of sha256 which is calculated from the whole file
 *	except the checksum field of the file. That is, calculate sha256
 *	from the version field to the end of the file.
 * @version: version of this firmware.
 * @blocks: the first firmware block of the file
 */
काष्ठा fw_header अणु
	u8 checksum[32];
	अक्षर version[RTL_VER_SIZE];
	काष्ठा fw_block blocks[];
पूर्ण __packed;

क्रमागत rtl8152_fw_flags अणु
	FW_FLAGS_USB = 0,
	FW_FLAGS_PLA,
	FW_FLAGS_START,
	FW_FLAGS_STOP,
	FW_FLAGS_NC,
	FW_FLAGS_NC1,
	FW_FLAGS_NC2,
	FW_FLAGS_UC2,
	FW_FLAGS_UC,
	FW_FLAGS_SPEED_UP,
	FW_FLAGS_VER,
पूर्ण;

क्रमागत rtl8152_fw_fixup_cmd अणु
	FW_FIXUP_AND = 0,
	FW_FIXUP_OR,
	FW_FIXUP_NOT,
	FW_FIXUP_XOR,
पूर्ण;

काष्ठा fw_phy_set अणु
	__le16 addr;
	__le16 data;
पूर्ण __packed;

काष्ठा fw_phy_speed_up अणु
	काष्ठा fw_block blk_hdr;
	__le16 fw_offset;
	__le16 version;
	__le16 fw_reg;
	__le16 reserved;
	अक्षर info[];
पूर्ण __packed;

काष्ठा fw_phy_ver अणु
	काष्ठा fw_block blk_hdr;
	काष्ठा fw_phy_set ver;
	__le32 reserved;
पूर्ण __packed;

काष्ठा fw_phy_fixup अणु
	काष्ठा fw_block blk_hdr;
	काष्ठा fw_phy_set setting;
	__le16 bit_cmd;
	__le16 reserved;
पूर्ण __packed;

काष्ठा fw_phy_जोड़ अणु
	काष्ठा fw_block blk_hdr;
	__le16 fw_offset;
	__le16 fw_reg;
	काष्ठा fw_phy_set pre_set[2];
	काष्ठा fw_phy_set bp[8];
	काष्ठा fw_phy_set bp_en;
	u8 pre_num;
	u8 bp_num;
	अक्षर info[];
पूर्ण __packed;

/**
 * काष्ठा fw_mac - a firmware block used by RTL_FW_PLA and RTL_FW_USB.
 *	The layout of the firmware block is:
 *	<काष्ठा fw_mac> + <info> + <firmware data>.
 * @blk_hdr: firmware descriptor (type, length)
 * @fw_offset: offset of the firmware binary data. The start address of
 *	the data would be the address of काष्ठा fw_mac + @fw_offset.
 * @fw_reg: the रेजिस्टर to load the firmware. Depends on chip.
 * @bp_ba_addr: the रेजिस्टर to ग_लिखो अवरोध poपूर्णांक base address. Depends on
 *	chip.
 * @bp_ba_value: अवरोध poपूर्णांक base address. Depends on chip.
 * @bp_en_addr: the रेजिस्टर to ग_लिखो अवरोध poपूर्णांक enabled mask. Depends
 *	on chip.
 * @bp_en_value: अवरोध poपूर्णांक enabled mask. Depends on the firmware.
 * @bp_start: the start रेजिस्टर of अवरोध poपूर्णांकs. Depends on chip.
 * @bp_num: the अवरोध poपूर्णांक number which needs to be set क्रम this firmware.
 *	Depends on the firmware.
 * @bp: अवरोध poपूर्णांकs. Depends on firmware.
 * @reserved: reserved space (unused)
 * @fw_ver_reg: the रेजिस्टर to store the fw version.
 * @fw_ver_data: the firmware version of the current type.
 * @info: additional inक्रमmation क्रम debugging, and is followed by the
 *	binary data of firmware.
 */
काष्ठा fw_mac अणु
	काष्ठा fw_block blk_hdr;
	__le16 fw_offset;
	__le16 fw_reg;
	__le16 bp_ba_addr;
	__le16 bp_ba_value;
	__le16 bp_en_addr;
	__le16 bp_en_value;
	__le16 bp_start;
	__le16 bp_num;
	__le16 bp[16]; /* any value determined by firmware */
	__le32 reserved;
	__le16 fw_ver_reg;
	u8 fw_ver_data;
	अक्षर info[];
पूर्ण __packed;

/**
 * काष्ठा fw_phy_patch_key - a firmware block used by RTL_FW_PHY_START.
 *	This is used to set patch key when loading the firmware of PHY.
 * @blk_hdr: firmware descriptor (type, length)
 * @key_reg: the रेजिस्टर to ग_लिखो the patch key.
 * @key_data: patch key.
 * @reserved: reserved space (unused)
 */
काष्ठा fw_phy_patch_key अणु
	काष्ठा fw_block blk_hdr;
	__le16 key_reg;
	__le16 key_data;
	__le32 reserved;
पूर्ण __packed;

/**
 * काष्ठा fw_phy_nc - a firmware block used by RTL_FW_PHY_NC.
 *	The layout of the firmware block is:
 *	<काष्ठा fw_phy_nc> + <info> + <firmware data>.
 * @blk_hdr: firmware descriptor (type, length)
 * @fw_offset: offset of the firmware binary data. The start address of
 *	the data would be the address of काष्ठा fw_phy_nc + @fw_offset.
 * @fw_reg: the रेजिस्टर to load the firmware. Depends on chip.
 * @ba_reg: the रेजिस्टर to ग_लिखो the base address. Depends on chip.
 * @ba_data: base address. Depends on chip.
 * @patch_en_addr: the रेजिस्टर of enabling patch mode. Depends on chip.
 * @patch_en_value: patch mode enabled mask. Depends on the firmware.
 * @mode_reg: the regitster of चयनing the mode.
 * @mode_pre: the mode needing to be set beक्रमe loading the firmware.
 * @mode_post: the mode to be set when finishing to load the firmware.
 * @reserved: reserved space (unused)
 * @bp_start: the start रेजिस्टर of अवरोध poपूर्णांकs. Depends on chip.
 * @bp_num: the अवरोध poपूर्णांक number which needs to be set क्रम this firmware.
 *	Depends on the firmware.
 * @bp: अवरोध poपूर्णांकs. Depends on firmware.
 * @info: additional inक्रमmation क्रम debugging, and is followed by the
 *	binary data of firmware.
 */
काष्ठा fw_phy_nc अणु
	काष्ठा fw_block blk_hdr;
	__le16 fw_offset;
	__le16 fw_reg;
	__le16 ba_reg;
	__le16 ba_data;
	__le16 patch_en_addr;
	__le16 patch_en_value;
	__le16 mode_reg;
	__le16 mode_pre;
	__le16 mode_post;
	__le16 reserved;
	__le16 bp_start;
	__le16 bp_num;
	__le16 bp[4];
	अक्षर info[];
पूर्ण __packed;

क्रमागत rtl_fw_type अणु
	RTL_FW_END = 0,
	RTL_FW_PLA,
	RTL_FW_USB,
	RTL_FW_PHY_START,
	RTL_FW_PHY_STOP,
	RTL_FW_PHY_NC,
	RTL_FW_PHY_FIXUP,
	RTL_FW_PHY_UNION_NC,
	RTL_FW_PHY_UNION_NC1,
	RTL_FW_PHY_UNION_NC2,
	RTL_FW_PHY_UNION_UC2,
	RTL_FW_PHY_UNION_UC,
	RTL_FW_PHY_UNION_MISC,
	RTL_FW_PHY_SPEED_UP,
	RTL_FW_PHY_VER,
पूर्ण;

क्रमागत rtl_version अणु
	RTL_VER_UNKNOWN = 0,
	RTL_VER_01,
	RTL_VER_02,
	RTL_VER_03,
	RTL_VER_04,
	RTL_VER_05,
	RTL_VER_06,
	RTL_VER_07,
	RTL_VER_08,
	RTL_VER_09,

	RTL_TEST_01,
	RTL_VER_10,
	RTL_VER_11,
	RTL_VER_12,
	RTL_VER_13,
	RTL_VER_14,
	RTL_VER_15,

	RTL_VER_MAX
पूर्ण;

क्रमागत tx_csum_stat अणु
	TX_CSUM_SUCCESS = 0,
	TX_CSUM_TSO,
	TX_CSUM_NONE
पूर्ण;

#घोषणा RTL_ADVERTISED_10_HALF			BIT(0)
#घोषणा RTL_ADVERTISED_10_FULL			BIT(1)
#घोषणा RTL_ADVERTISED_100_HALF			BIT(2)
#घोषणा RTL_ADVERTISED_100_FULL			BIT(3)
#घोषणा RTL_ADVERTISED_1000_HALF		BIT(4)
#घोषणा RTL_ADVERTISED_1000_FULL		BIT(5)
#घोषणा RTL_ADVERTISED_2500_FULL		BIT(6)

/* Maximum number of multicast addresses to filter (vs. Rx-all-multicast).
 * The RTL chips use a 64 element hash table based on the Ethernet CRC.
 */
अटल स्थिर पूर्णांक multicast_filter_limit = 32;
अटल अचिन्हित पूर्णांक agg_buf_sz = 16384;

#घोषणा RTL_LIMITED_TSO_SIZE	(माप_प्रकारo_mtu(agg_buf_sz) - माप(काष्ठा tx_desc))

अटल
पूर्णांक get_रेजिस्टरs(काष्ठा r8152 *tp, u16 value, u16 index, u16 size, व्योम *data)
अणु
	पूर्णांक ret;
	व्योम *पंचांगp;

	पंचांगp = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	ret = usb_control_msg(tp->udev, usb_rcvctrlpipe(tp->udev, 0),
			      RTL8152_REQ_GET_REGS, RTL8152_REQT_READ,
			      value, index, पंचांगp, size, 500);
	अगर (ret < 0)
		स_रखो(data, 0xff, size);
	अन्यथा
		स_नकल(data, पंचांगp, size);

	kमुक्त(पंचांगp);

	वापस ret;
पूर्ण

अटल
पूर्णांक set_रेजिस्टरs(काष्ठा r8152 *tp, u16 value, u16 index, u16 size, व्योम *data)
अणु
	पूर्णांक ret;
	व्योम *पंचांगp;

	पंचांगp = kmemdup(data, size, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	ret = usb_control_msg(tp->udev, usb_sndctrlpipe(tp->udev, 0),
			      RTL8152_REQ_SET_REGS, RTL8152_REQT_WRITE,
			      value, index, पंचांगp, size, 500);

	kमुक्त(पंचांगp);

	वापस ret;
पूर्ण

अटल व्योम rtl_set_unplug(काष्ठा r8152 *tp)
अणु
	अगर (tp->udev->state == USB_STATE_NOTATTACHED) अणु
		set_bit(RTL8152_UNPLUG, &tp->flags);
		smp_mb__after_atomic();
	पूर्ण
पूर्ण

अटल पूर्णांक generic_ocp_पढ़ो(काष्ठा r8152 *tp, u16 index, u16 size,
			    व्योम *data, u16 type)
अणु
	u16 limit = 64;
	पूर्णांक ret = 0;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस -ENODEV;

	/* both size and indix must be 4 bytes align */
	अगर ((size & 3) || !size || (index & 3) || !data)
		वापस -EPERM;

	अगर ((u32)index + (u32)size > 0xffff)
		वापस -EPERM;

	जबतक (size) अणु
		अगर (size > limit) अणु
			ret = get_रेजिस्टरs(tp, index, type, limit, data);
			अगर (ret < 0)
				अवरोध;

			index += limit;
			data += limit;
			size -= limit;
		पूर्ण अन्यथा अणु
			ret = get_रेजिस्टरs(tp, index, type, size, data);
			अगर (ret < 0)
				अवरोध;

			index += size;
			data += size;
			size = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret == -ENODEV)
		rtl_set_unplug(tp);

	वापस ret;
पूर्ण

अटल पूर्णांक generic_ocp_ग_लिखो(काष्ठा r8152 *tp, u16 index, u16 byteen,
			     u16 size, व्योम *data, u16 type)
अणु
	पूर्णांक ret;
	u16 byteen_start, byteen_end, byen;
	u16 limit = 512;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस -ENODEV;

	/* both size and indix must be 4 bytes align */
	अगर ((size & 3) || !size || (index & 3) || !data)
		वापस -EPERM;

	अगर ((u32)index + (u32)size > 0xffff)
		वापस -EPERM;

	byteen_start = byteen & BYTE_EN_START_MASK;
	byteen_end = byteen & BYTE_EN_END_MASK;

	byen = byteen_start | (byteen_start << 4);
	ret = set_रेजिस्टरs(tp, index, type | byen, 4, data);
	अगर (ret < 0)
		जाओ error1;

	index += 4;
	data += 4;
	size -= 4;

	अगर (size) अणु
		size -= 4;

		जबतक (size) अणु
			अगर (size > limit) अणु
				ret = set_रेजिस्टरs(tp, index,
						    type | BYTE_EN_DWORD,
						    limit, data);
				अगर (ret < 0)
					जाओ error1;

				index += limit;
				data += limit;
				size -= limit;
			पूर्ण अन्यथा अणु
				ret = set_रेजिस्टरs(tp, index,
						    type | BYTE_EN_DWORD,
						    size, data);
				अगर (ret < 0)
					जाओ error1;

				index += size;
				data += size;
				size = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		byen = byteen_end | (byteen_end >> 4);
		ret = set_रेजिस्टरs(tp, index, type | byen, 4, data);
		अगर (ret < 0)
			जाओ error1;
	पूर्ण

error1:
	अगर (ret == -ENODEV)
		rtl_set_unplug(tp);

	वापस ret;
पूर्ण

अटल अंतरभूत
पूर्णांक pla_ocp_पढ़ो(काष्ठा r8152 *tp, u16 index, u16 size, व्योम *data)
अणु
	वापस generic_ocp_पढ़ो(tp, index, size, data, MCU_TYPE_PLA);
पूर्ण

अटल अंतरभूत
पूर्णांक pla_ocp_ग_लिखो(काष्ठा r8152 *tp, u16 index, u16 byteen, u16 size, व्योम *data)
अणु
	वापस generic_ocp_ग_लिखो(tp, index, byteen, size, data, MCU_TYPE_PLA);
पूर्ण

अटल अंतरभूत
पूर्णांक usb_ocp_ग_लिखो(काष्ठा r8152 *tp, u16 index, u16 byteen, u16 size, व्योम *data)
अणु
	वापस generic_ocp_ग_लिखो(tp, index, byteen, size, data, MCU_TYPE_USB);
पूर्ण

अटल u32 ocp_पढ़ो_dword(काष्ठा r8152 *tp, u16 type, u16 index)
अणु
	__le32 data;

	generic_ocp_पढ़ो(tp, index, माप(data), &data, type);

	वापस __le32_to_cpu(data);
पूर्ण

अटल व्योम ocp_ग_लिखो_dword(काष्ठा r8152 *tp, u16 type, u16 index, u32 data)
अणु
	__le32 पंचांगp = __cpu_to_le32(data);

	generic_ocp_ग_लिखो(tp, index, BYTE_EN_DWORD, माप(पंचांगp), &पंचांगp, type);
पूर्ण

अटल u16 ocp_पढ़ो_word(काष्ठा r8152 *tp, u16 type, u16 index)
अणु
	u32 data;
	__le32 पंचांगp;
	u16 byen = BYTE_EN_WORD;
	u8 shअगरt = index & 2;

	index &= ~3;
	byen <<= shअगरt;

	generic_ocp_पढ़ो(tp, index, माप(पंचांगp), &पंचांगp, type | byen);

	data = __le32_to_cpu(पंचांगp);
	data >>= (shअगरt * 8);
	data &= 0xffff;

	वापस (u16)data;
पूर्ण

अटल व्योम ocp_ग_लिखो_word(काष्ठा r8152 *tp, u16 type, u16 index, u32 data)
अणु
	u32 mask = 0xffff;
	__le32 पंचांगp;
	u16 byen = BYTE_EN_WORD;
	u8 shअगरt = index & 2;

	data &= mask;

	अगर (index & 2) अणु
		byen <<= shअगरt;
		mask <<= (shअगरt * 8);
		data <<= (shअगरt * 8);
		index &= ~3;
	पूर्ण

	पंचांगp = __cpu_to_le32(data);

	generic_ocp_ग_लिखो(tp, index, byen, माप(पंचांगp), &पंचांगp, type);
पूर्ण

अटल u8 ocp_पढ़ो_byte(काष्ठा r8152 *tp, u16 type, u16 index)
अणु
	u32 data;
	__le32 पंचांगp;
	u8 shअगरt = index & 3;

	index &= ~3;

	generic_ocp_पढ़ो(tp, index, माप(पंचांगp), &पंचांगp, type);

	data = __le32_to_cpu(पंचांगp);
	data >>= (shअगरt * 8);
	data &= 0xff;

	वापस (u8)data;
पूर्ण

अटल व्योम ocp_ग_लिखो_byte(काष्ठा r8152 *tp, u16 type, u16 index, u32 data)
अणु
	u32 mask = 0xff;
	__le32 पंचांगp;
	u16 byen = BYTE_EN_BYTE;
	u8 shअगरt = index & 3;

	data &= mask;

	अगर (index & 3) अणु
		byen <<= shअगरt;
		mask <<= (shअगरt * 8);
		data <<= (shअगरt * 8);
		index &= ~3;
	पूर्ण

	पंचांगp = __cpu_to_le32(data);

	generic_ocp_ग_लिखो(tp, index, byen, माप(पंचांगp), &पंचांगp, type);
पूर्ण

अटल u16 ocp_reg_पढ़ो(काष्ठा r8152 *tp, u16 addr)
अणु
	u16 ocp_base, ocp_index;

	ocp_base = addr & 0xf000;
	अगर (ocp_base != tp->ocp_base) अणु
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, ocp_base);
		tp->ocp_base = ocp_base;
	पूर्ण

	ocp_index = (addr & 0x0fff) | 0xb000;
	वापस ocp_पढ़ो_word(tp, MCU_TYPE_PLA, ocp_index);
पूर्ण

अटल व्योम ocp_reg_ग_लिखो(काष्ठा r8152 *tp, u16 addr, u16 data)
अणु
	u16 ocp_base, ocp_index;

	ocp_base = addr & 0xf000;
	अगर (ocp_base != tp->ocp_base) अणु
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, ocp_base);
		tp->ocp_base = ocp_base;
	पूर्ण

	ocp_index = (addr & 0x0fff) | 0xb000;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, ocp_index, data);
पूर्ण

अटल अंतरभूत व्योम r8152_mdio_ग_लिखो(काष्ठा r8152 *tp, u32 reg_addr, u32 value)
अणु
	ocp_reg_ग_लिखो(tp, OCP_BASE_MII + reg_addr * 2, value);
पूर्ण

अटल अंतरभूत पूर्णांक r8152_mdio_पढ़ो(काष्ठा r8152 *tp, u32 reg_addr)
अणु
	वापस ocp_reg_पढ़ो(tp, OCP_BASE_MII + reg_addr * 2);
पूर्ण

अटल व्योम sram_ग_लिखो(काष्ठा r8152 *tp, u16 addr, u16 data)
अणु
	ocp_reg_ग_लिखो(tp, OCP_SRAM_ADDR, addr);
	ocp_reg_ग_लिखो(tp, OCP_SRAM_DATA, data);
पूर्ण

अटल u16 sram_पढ़ो(काष्ठा r8152 *tp, u16 addr)
अणु
	ocp_reg_ग_लिखो(tp, OCP_SRAM_ADDR, addr);
	वापस ocp_reg_पढ़ो(tp, OCP_SRAM_DATA);
पूर्ण

अटल पूर्णांक पढ़ो_mii_word(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);
	पूर्णांक ret;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस -ENODEV;

	अगर (phy_id != R8152_PHY_ID)
		वापस -EINVAL;

	ret = r8152_mdio_पढ़ो(tp, reg);

	वापस ret;
पूर्ण

अटल
व्योम ग_लिखो_mii_word(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	अगर (phy_id != R8152_PHY_ID)
		वापस;

	r8152_mdio_ग_लिखो(tp, reg, val);
पूर्ण

अटल पूर्णांक
r8152_submit_rx(काष्ठा r8152 *tp, काष्ठा rx_agg *agg, gfp_t mem_flags);

अटल पूर्णांक
rtl8152_set_speed(काष्ठा r8152 *tp, u8 स्वतःneg, u32 speed, u8 duplex,
		  u32 advertising);

अटल पूर्णांक rtl8152_set_mac_address(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;
	पूर्णांक ret = -EADDRNOTAVAIL;

	अगर (!is_valid_ether_addr(addr->sa_data))
		जाओ out1;

	ret = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (ret < 0)
		जाओ out1;

	mutex_lock(&tp->control);

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);

	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);
	pla_ocp_ग_लिखो(tp, PLA_IDR, BYTE_EN_SIX_BYTES, 8, addr->sa_data);
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);
out1:
	वापस ret;
पूर्ण

/* Devices containing proper chips can support a persistent
 * host प्रणाली provided MAC address.
 * Examples of this are Dell TB15 and Dell WD15 करोcks
 */
अटल पूर्णांक venकरोr_mac_passthru_addr_पढ़ो(काष्ठा r8152 *tp, काष्ठा sockaddr *sa)
अणु
	acpi_status status;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	पूर्णांक ret = -EINVAL;
	u32 ocp_data;
	अचिन्हित अक्षर buf[6];
	अक्षर *mac_obj_name;
	acpi_object_type mac_obj_type;
	पूर्णांक mac_म_माप;

	अगर (tp->lenovo_macpassthru) अणु
		mac_obj_name = "\\MACA";
		mac_obj_type = ACPI_TYPE_STRING;
		mac_म_माप = 0x16;
	पूर्ण अन्यथा अणु
		/* test क्रम -AD variant of RTL8153 */
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_MISC_0);
		अगर ((ocp_data & AD_MASK) == 0x1000) अणु
			/* test क्रम MAC address pass-through bit */
			ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, EFUSE);
			अगर ((ocp_data & PASS_THRU_MASK) != 1) अणु
				netअगर_dbg(tp, probe, tp->netdev,
						"No efuse for RTL8153-AD MAC pass through\n");
				वापस -ENODEV;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* test क्रम RTL8153-BND and RTL8153-BD */
			ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_MISC_1);
			अगर ((ocp_data & BND_MASK) == 0 && (ocp_data & BD_MASK) == 0) अणु
				netअगर_dbg(tp, probe, tp->netdev,
						"Invalid variant for MAC pass through\n");
				वापस -ENODEV;
			पूर्ण
		पूर्ण

		mac_obj_name = "\\_SB.AMAC";
		mac_obj_type = ACPI_TYPE_BUFFER;
		mac_म_माप = 0x17;
	पूर्ण

	/* वापसs _AUXMAC_#AABBCCDDEEFF# */
	status = acpi_evaluate_object(शून्य, mac_obj_name, शून्य, &buffer);
	obj = (जोड़ acpi_object *)buffer.poपूर्णांकer;
	अगर (!ACPI_SUCCESS(status))
		वापस -ENODEV;
	अगर (obj->type != mac_obj_type || obj->string.length != mac_म_माप) अणु
		netअगर_warn(tp, probe, tp->netdev,
			   "Invalid buffer for pass-thru MAC addr: (%d, %d)\n",
			   obj->type, obj->string.length);
		जाओ amacout;
	पूर्ण

	अगर (म_भेदन(obj->string.poपूर्णांकer, "_AUXMAC_#", 9) != 0 ||
	    म_भेदन(obj->string.poपूर्णांकer + 0x15, "#", 1) != 0) अणु
		netअगर_warn(tp, probe, tp->netdev,
			   "Invalid header when reading pass-thru MAC addr\n");
		जाओ amacout;
	पूर्ण
	ret = hex2bin(buf, obj->string.poपूर्णांकer + 9, 6);
	अगर (!(ret == 0 && is_valid_ether_addr(buf))) अणु
		netअगर_warn(tp, probe, tp->netdev,
			   "Invalid MAC for pass-thru MAC addr: %d, %pM\n",
			   ret, buf);
		ret = -EINVAL;
		जाओ amacout;
	पूर्ण
	स_नकल(sa->sa_data, buf, 6);
	netअगर_info(tp, probe, tp->netdev,
		   "Using pass-thru MAC addr %pM\n", sa->sa_data);

amacout:
	kमुक्त(obj);
	वापस ret;
पूर्ण

अटल पूर्णांक determine_ethernet_addr(काष्ठा r8152 *tp, काष्ठा sockaddr *sa)
अणु
	काष्ठा net_device *dev = tp->netdev;
	पूर्णांक ret;

	sa->sa_family = dev->type;

	ret = eth_platक्रमm_get_mac_address(&tp->udev->dev, sa->sa_data);
	अगर (ret < 0) अणु
		अगर (tp->version == RTL_VER_01) अणु
			ret = pla_ocp_पढ़ो(tp, PLA_IDR, 8, sa->sa_data);
		पूर्ण अन्यथा अणु
			/* अगर device करोesn't support MAC pass through this will
			 * be expected to be non-zero
			 */
			ret = venकरोr_mac_passthru_addr_पढ़ो(tp, sa);
			अगर (ret < 0)
				ret = pla_ocp_पढ़ो(tp, PLA_BACKUP, 8,
						   sa->sa_data);
		पूर्ण
	पूर्ण

	अगर (ret < 0) अणु
		netअगर_err(tp, probe, dev, "Get ether addr fail\n");
	पूर्ण अन्यथा अगर (!is_valid_ether_addr(sa->sa_data)) अणु
		netअगर_err(tp, probe, dev, "Invalid ether addr %pM\n",
			  sa->sa_data);
		eth_hw_addr_अक्रमom(dev);
		ether_addr_copy(sa->sa_data, dev->dev_addr);
		netअगर_info(tp, probe, dev, "Random ether addr %pM\n",
			   sa->sa_data);
		वापस 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक set_ethernet_addr(काष्ठा r8152 *tp)
अणु
	काष्ठा net_device *dev = tp->netdev;
	काष्ठा sockaddr sa;
	पूर्णांक ret;

	ret = determine_ethernet_addr(tp, &sa);
	अगर (ret < 0)
		वापस ret;

	अगर (tp->version == RTL_VER_01)
		ether_addr_copy(dev->dev_addr, sa.sa_data);
	अन्यथा
		ret = rtl8152_set_mac_address(dev, &sa);

	वापस ret;
पूर्ण

अटल व्योम पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा net_device *netdev;
	पूर्णांक status = urb->status;
	काष्ठा rx_agg *agg;
	काष्ठा r8152 *tp;
	अचिन्हित दीर्घ flags;

	agg = urb->context;
	अगर (!agg)
		वापस;

	tp = agg->context;
	अगर (!tp)
		वापस;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	अगर (!test_bit(WORK_ENABLE, &tp->flags))
		वापस;

	netdev = tp->netdev;

	/* When link करोwn, the driver would cancel all bulks. */
	/* This aव्योम the re-submitting bulk */
	अगर (!netअगर_carrier_ok(netdev))
		वापस;

	usb_mark_last_busy(tp->udev);

	चयन (status) अणु
	हाल 0:
		अगर (urb->actual_length < ETH_ZLEN)
			अवरोध;

		spin_lock_irqsave(&tp->rx_lock, flags);
		list_add_tail(&agg->list, &tp->rx_करोne);
		spin_unlock_irqrestore(&tp->rx_lock, flags);
		napi_schedule(&tp->napi);
		वापस;
	हाल -ESHUTDOWN:
		rtl_set_unplug(tp);
		netअगर_device_detach(tp->netdev);
		वापस;
	हाल -ENOENT:
		वापस;	/* the urb is in unlink state */
	हाल -ETIME:
		अगर (net_ratelimit())
			netdev_warn(netdev, "maybe reset is needed?\n");
		अवरोध;
	शेष:
		अगर (net_ratelimit())
			netdev_warn(netdev, "Rx status %d\n", status);
		अवरोध;
	पूर्ण

	r8152_submit_rx(tp, agg, GFP_ATOMIC);
पूर्ण

अटल व्योम ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा net_device_stats *stats;
	काष्ठा net_device *netdev;
	काष्ठा tx_agg *agg;
	काष्ठा r8152 *tp;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = urb->status;

	agg = urb->context;
	अगर (!agg)
		वापस;

	tp = agg->context;
	अगर (!tp)
		वापस;

	netdev = tp->netdev;
	stats = &netdev->stats;
	अगर (status) अणु
		अगर (net_ratelimit())
			netdev_warn(netdev, "Tx status %d\n", status);
		stats->tx_errors += agg->skb_num;
	पूर्ण अन्यथा अणु
		stats->tx_packets += agg->skb_num;
		stats->tx_bytes += agg->skb_len;
	पूर्ण

	spin_lock_irqsave(&tp->tx_lock, flags);
	list_add_tail(&agg->list, &tp->tx_मुक्त);
	spin_unlock_irqrestore(&tp->tx_lock, flags);

	usb_स्वतःpm_put_पूर्णांकerface_async(tp->पूर्णांकf);

	अगर (!netअगर_carrier_ok(netdev))
		वापस;

	अगर (!test_bit(WORK_ENABLE, &tp->flags))
		वापस;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	अगर (!skb_queue_empty(&tp->tx_queue))
		tasklet_schedule(&tp->tx_tl);
पूर्ण

अटल व्योम पूर्णांकr_callback(काष्ठा urb *urb)
अणु
	काष्ठा r8152 *tp;
	__le16 *d;
	पूर्णांक status = urb->status;
	पूर्णांक res;

	tp = urb->context;
	अगर (!tp)
		वापस;

	अगर (!test_bit(WORK_ENABLE, &tp->flags))
		वापस;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	चयन (status) अणु
	हाल 0:			/* success */
		अवरोध;
	हाल -ECONNRESET:	/* unlink */
	हाल -ESHUTDOWN:
		netअगर_device_detach(tp->netdev);
		fallthrough;
	हाल -ENOENT:
	हाल -EPROTO:
		netअगर_info(tp, पूर्णांकr, tp->netdev,
			   "Stop submitting intr, status %d\n", status);
		वापस;
	हाल -EOVERFLOW:
		netअगर_info(tp, पूर्णांकr, tp->netdev, "intr status -EOVERFLOW\n");
		जाओ resubmit;
	/* -EPIPE:  should clear the halt */
	शेष:
		netअगर_info(tp, पूर्णांकr, tp->netdev, "intr status %d\n", status);
		जाओ resubmit;
	पूर्ण

	d = urb->transfer_buffer;
	अगर (INTR_LINK & __le16_to_cpu(d[0])) अणु
		अगर (!netअगर_carrier_ok(tp->netdev)) अणु
			set_bit(RTL8152_LINK_CHG, &tp->flags);
			schedule_delayed_work(&tp->schedule, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(tp->netdev)) अणु
			netअगर_stop_queue(tp->netdev);
			set_bit(RTL8152_LINK_CHG, &tp->flags);
			schedule_delayed_work(&tp->schedule, 0);
		पूर्ण
	पूर्ण

resubmit:
	res = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (res == -ENODEV) अणु
		rtl_set_unplug(tp);
		netअगर_device_detach(tp->netdev);
	पूर्ण अन्यथा अगर (res) अणु
		netअगर_err(tp, पूर्णांकr, tp->netdev,
			  "can't resubmit intr, status %d\n", res);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *rx_agg_align(व्योम *data)
अणु
	वापस (व्योम *)ALIGN((uपूर्णांकptr_t)data, RX_ALIGN);
पूर्ण

अटल अंतरभूत व्योम *tx_agg_align(व्योम *data)
अणु
	वापस (व्योम *)ALIGN((uपूर्णांकptr_t)data, TX_ALIGN);
पूर्ण

अटल व्योम मुक्त_rx_agg(काष्ठा r8152 *tp, काष्ठा rx_agg *agg)
अणु
	list_del(&agg->info_list);

	usb_मुक्त_urb(agg->urb);
	put_page(agg->page);
	kमुक्त(agg);

	atomic_dec(&tp->rx_count);
पूर्ण

अटल काष्ठा rx_agg *alloc_rx_agg(काष्ठा r8152 *tp, gfp_t mflags)
अणु
	काष्ठा net_device *netdev = tp->netdev;
	पूर्णांक node = netdev->dev.parent ? dev_to_node(netdev->dev.parent) : -1;
	अचिन्हित पूर्णांक order = get_order(tp->rx_buf_sz);
	काष्ठा rx_agg *rx_agg;
	अचिन्हित दीर्घ flags;

	rx_agg = kदो_स्मृति_node(माप(*rx_agg), mflags, node);
	अगर (!rx_agg)
		वापस शून्य;

	rx_agg->page = alloc_pages(mflags | __GFP_COMP, order);
	अगर (!rx_agg->page)
		जाओ मुक्त_rx;

	rx_agg->buffer = page_address(rx_agg->page);

	rx_agg->urb = usb_alloc_urb(0, mflags);
	अगर (!rx_agg->urb)
		जाओ मुक्त_buf;

	rx_agg->context = tp;

	INIT_LIST_HEAD(&rx_agg->list);
	INIT_LIST_HEAD(&rx_agg->info_list);
	spin_lock_irqsave(&tp->rx_lock, flags);
	list_add_tail(&rx_agg->info_list, &tp->rx_info);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	atomic_inc(&tp->rx_count);

	वापस rx_agg;

मुक्त_buf:
	__मुक्त_pages(rx_agg->page, order);
मुक्त_rx:
	kमुक्त(rx_agg);
	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_all_mem(काष्ठा r8152 *tp)
अणु
	काष्ठा rx_agg *agg, *agg_next;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&tp->rx_lock, flags);

	list_क्रम_each_entry_safe(agg, agg_next, &tp->rx_info, info_list)
		मुक्त_rx_agg(tp, agg);

	spin_unlock_irqrestore(&tp->rx_lock, flags);

	WARN_ON(atomic_पढ़ो(&tp->rx_count));

	क्रम (i = 0; i < RTL8152_MAX_TX; i++) अणु
		usb_मुक्त_urb(tp->tx_info[i].urb);
		tp->tx_info[i].urb = शून्य;

		kमुक्त(tp->tx_info[i].buffer);
		tp->tx_info[i].buffer = शून्य;
		tp->tx_info[i].head = शून्य;
	पूर्ण

	usb_मुक्त_urb(tp->पूर्णांकr_urb);
	tp->पूर्णांकr_urb = शून्य;

	kमुक्त(tp->पूर्णांकr_buff);
	tp->पूर्णांकr_buff = शून्य;
पूर्ण

अटल पूर्णांक alloc_all_mem(काष्ठा r8152 *tp)
अणु
	काष्ठा net_device *netdev = tp->netdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = tp->पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;
	काष्ठा usb_host_endpoपूर्णांक *ep_पूर्णांकr = alt->endpoपूर्णांक + 2;
	पूर्णांक node, i;

	node = netdev->dev.parent ? dev_to_node(netdev->dev.parent) : -1;

	spin_lock_init(&tp->rx_lock);
	spin_lock_init(&tp->tx_lock);
	INIT_LIST_HEAD(&tp->rx_info);
	INIT_LIST_HEAD(&tp->tx_मुक्त);
	INIT_LIST_HEAD(&tp->rx_करोne);
	skb_queue_head_init(&tp->tx_queue);
	skb_queue_head_init(&tp->rx_queue);
	atomic_set(&tp->rx_count, 0);

	क्रम (i = 0; i < RTL8152_MAX_RX; i++) अणु
		अगर (!alloc_rx_agg(tp, GFP_KERNEL))
			जाओ err1;
	पूर्ण

	क्रम (i = 0; i < RTL8152_MAX_TX; i++) अणु
		काष्ठा urb *urb;
		u8 *buf;

		buf = kदो_स्मृति_node(agg_buf_sz, GFP_KERNEL, node);
		अगर (!buf)
			जाओ err1;

		अगर (buf != tx_agg_align(buf)) अणु
			kमुक्त(buf);
			buf = kदो_स्मृति_node(agg_buf_sz + TX_ALIGN, GFP_KERNEL,
					   node);
			अगर (!buf)
				जाओ err1;
		पूर्ण

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			kमुक्त(buf);
			जाओ err1;
		पूर्ण

		INIT_LIST_HEAD(&tp->tx_info[i].list);
		tp->tx_info[i].context = tp;
		tp->tx_info[i].urb = urb;
		tp->tx_info[i].buffer = buf;
		tp->tx_info[i].head = tx_agg_align(buf);

		list_add_tail(&tp->tx_info[i].list, &tp->tx_मुक्त);
	पूर्ण

	tp->पूर्णांकr_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!tp->पूर्णांकr_urb)
		जाओ err1;

	tp->पूर्णांकr_buff = kदो_स्मृति(INTबफ_मानE, GFP_KERNEL);
	अगर (!tp->पूर्णांकr_buff)
		जाओ err1;

	tp->पूर्णांकr_पूर्णांकerval = (पूर्णांक)ep_पूर्णांकr->desc.bInterval;
	usb_fill_पूर्णांक_urb(tp->पूर्णांकr_urb, tp->udev, usb_rcvपूर्णांकpipe(tp->udev, 3),
			 tp->पूर्णांकr_buff, INTबफ_मानE, पूर्णांकr_callback,
			 tp, tp->पूर्णांकr_पूर्णांकerval);

	वापस 0;

err1:
	मुक्त_all_mem(tp);
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा tx_agg *r8152_get_tx_agg(काष्ठा r8152 *tp)
अणु
	काष्ठा tx_agg *agg = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (list_empty(&tp->tx_मुक्त))
		वापस शून्य;

	spin_lock_irqsave(&tp->tx_lock, flags);
	अगर (!list_empty(&tp->tx_मुक्त)) अणु
		काष्ठा list_head *cursor;

		cursor = tp->tx_मुक्त.next;
		list_del_init(cursor);
		agg = list_entry(cursor, काष्ठा tx_agg, list);
	पूर्ण
	spin_unlock_irqrestore(&tp->tx_lock, flags);

	वापस agg;
पूर्ण

/* r8152_csum_workaround()
 * The hw limits the value of the transport offset. When the offset is out of
 * range, calculate the checksum by sw.
 */
अटल व्योम r8152_csum_workaround(काष्ठा r8152 *tp, काष्ठा sk_buff *skb,
				  काष्ठा sk_buff_head *list)
अणु
	अगर (skb_shinfo(skb)->gso_size) अणु
		netdev_features_t features = tp->netdev->features;
		काष्ठा sk_buff *segs, *seg, *next;
		काष्ठा sk_buff_head seg_list;

		features &= ~(NETIF_F_SG | NETIF_F_IPV6_CSUM | NETIF_F_TSO6);
		segs = skb_gso_segment(skb, features);
		अगर (IS_ERR(segs) || !segs)
			जाओ drop;

		__skb_queue_head_init(&seg_list);

		skb_list_walk_safe(segs, seg, next) अणु
			skb_mark_not_on_list(seg);
			__skb_queue_tail(&seg_list, seg);
		पूर्ण

		skb_queue_splice(&seg_list, list);
		dev_kमुक्त_skb(skb);
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (skb_checksum_help(skb) < 0)
			जाओ drop;

		__skb_queue_head(list, skb);
	पूर्ण अन्यथा अणु
		काष्ठा net_device_stats *stats;

drop:
		stats = &tp->netdev->stats;
		stats->tx_dropped++;
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rtl_tx_vlan_tag(काष्ठा tx_desc *desc, काष्ठा sk_buff *skb)
अणु
	अगर (skb_vlan_tag_present(skb)) अणु
		u32 opts2;

		opts2 = TX_VLAN_TAG | swab16(skb_vlan_tag_get(skb));
		desc->opts2 |= cpu_to_le32(opts2);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rtl_rx_vlan_tag(काष्ठा rx_desc *desc, काष्ठा sk_buff *skb)
अणु
	u32 opts2 = le32_to_cpu(desc->opts2);

	अगर (opts2 & RX_VLAN_TAG)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       swab16(opts2 & 0xffff));
पूर्ण

अटल पूर्णांक r8152_tx_csum(काष्ठा r8152 *tp, काष्ठा tx_desc *desc,
			 काष्ठा sk_buff *skb, u32 len, u32 transport_offset)
अणु
	u32 mss = skb_shinfo(skb)->gso_size;
	u32 opts1, opts2 = 0;
	पूर्णांक ret = TX_CSUM_SUCCESS;

	WARN_ON_ONCE(len > TX_LEN_MAX);

	opts1 = len | TX_FS | TX_LS;

	अगर (mss) अणु
		अगर (transport_offset > GTTCPHO_MAX) अणु
			netअगर_warn(tp, tx_err, tp->netdev,
				   "Invalid transport offset 0x%x for TSO\n",
				   transport_offset);
			ret = TX_CSUM_TSO;
			जाओ unavailable;
		पूर्ण

		चयन (vlan_get_protocol(skb)) अणु
		हाल htons(ETH_P_IP):
			opts1 |= GTSENDV4;
			अवरोध;

		हाल htons(ETH_P_IPV6):
			अगर (skb_cow_head(skb, 0)) अणु
				ret = TX_CSUM_TSO;
				जाओ unavailable;
			पूर्ण
			tcp_v6_gso_csum_prep(skb);
			opts1 |= GTSENDV6;
			अवरोध;

		शेष:
			WARN_ON_ONCE(1);
			अवरोध;
		पूर्ण

		opts1 |= transport_offset << GTTCPHO_SHIFT;
		opts2 |= min(mss, MSS_MAX) << MSS_SHIFT;
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		u8 ip_protocol;

		अगर (transport_offset > TCPHO_MAX) अणु
			netअगर_warn(tp, tx_err, tp->netdev,
				   "Invalid transport offset 0x%x\n",
				   transport_offset);
			ret = TX_CSUM_NONE;
			जाओ unavailable;
		पूर्ण

		चयन (vlan_get_protocol(skb)) अणु
		हाल htons(ETH_P_IP):
			opts2 |= IPV4_CS;
			ip_protocol = ip_hdr(skb)->protocol;
			अवरोध;

		हाल htons(ETH_P_IPV6):
			opts2 |= IPV6_CS;
			ip_protocol = ipv6_hdr(skb)->nexthdr;
			अवरोध;

		शेष:
			ip_protocol = IPPROTO_RAW;
			अवरोध;
		पूर्ण

		अगर (ip_protocol == IPPROTO_TCP)
			opts2 |= TCP_CS;
		अन्यथा अगर (ip_protocol == IPPROTO_UDP)
			opts2 |= UDP_CS;
		अन्यथा
			WARN_ON_ONCE(1);

		opts2 |= transport_offset << TCPHO_SHIFT;
	पूर्ण

	desc->opts2 = cpu_to_le32(opts2);
	desc->opts1 = cpu_to_le32(opts1);

unavailable:
	वापस ret;
पूर्ण

अटल पूर्णांक r8152_tx_agg_fill(काष्ठा r8152 *tp, काष्ठा tx_agg *agg)
अणु
	काष्ठा sk_buff_head skb_head, *tx_queue = &tp->tx_queue;
	पूर्णांक reमुख्य, ret;
	u8 *tx_data;

	__skb_queue_head_init(&skb_head);
	spin_lock(&tx_queue->lock);
	skb_queue_splice_init(tx_queue, &skb_head);
	spin_unlock(&tx_queue->lock);

	tx_data = agg->head;
	agg->skb_num = 0;
	agg->skb_len = 0;
	reमुख्य = agg_buf_sz;

	जबतक (reमुख्य >= ETH_ZLEN + माप(काष्ठा tx_desc)) अणु
		काष्ठा tx_desc *tx_desc;
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक len;
		u32 offset;

		skb = __skb_dequeue(&skb_head);
		अगर (!skb)
			अवरोध;

		len = skb->len + माप(*tx_desc);

		अगर (len > reमुख्य) अणु
			__skb_queue_head(&skb_head, skb);
			अवरोध;
		पूर्ण

		tx_data = tx_agg_align(tx_data);
		tx_desc = (काष्ठा tx_desc *)tx_data;

		offset = (u32)skb_transport_offset(skb);

		अगर (r8152_tx_csum(tp, tx_desc, skb, skb->len, offset)) अणु
			r8152_csum_workaround(tp, skb, &skb_head);
			जारी;
		पूर्ण

		rtl_tx_vlan_tag(tx_desc, skb);

		tx_data += माप(*tx_desc);

		len = skb->len;
		अगर (skb_copy_bits(skb, 0, tx_data, len) < 0) अणु
			काष्ठा net_device_stats *stats = &tp->netdev->stats;

			stats->tx_dropped++;
			dev_kमुक्त_skb_any(skb);
			tx_data -= माप(*tx_desc);
			जारी;
		पूर्ण

		tx_data += len;
		agg->skb_len += len;
		agg->skb_num += skb_shinfo(skb)->gso_segs ?: 1;

		dev_kमुक्त_skb_any(skb);

		reमुख्य = agg_buf_sz - (पूर्णांक)(tx_agg_align(tx_data) - agg->head);

		अगर (tp->dell_tb_rx_agg_bug)
			अवरोध;
	पूर्ण

	अगर (!skb_queue_empty(&skb_head)) अणु
		spin_lock(&tx_queue->lock);
		skb_queue_splice(&skb_head, tx_queue);
		spin_unlock(&tx_queue->lock);
	पूर्ण

	netअगर_tx_lock(tp->netdev);

	अगर (netअगर_queue_stopped(tp->netdev) &&
	    skb_queue_len(&tp->tx_queue) < tp->tx_qlen)
		netअगर_wake_queue(tp->netdev);

	netअगर_tx_unlock(tp->netdev);

	ret = usb_स्वतःpm_get_पूर्णांकerface_async(tp->पूर्णांकf);
	अगर (ret < 0)
		जाओ out_tx_fill;

	usb_fill_bulk_urb(agg->urb, tp->udev, usb_sndbulkpipe(tp->udev, 2),
			  agg->head, (पूर्णांक)(tx_data - (u8 *)agg->head),
			  (usb_complete_t)ग_लिखो_bulk_callback, agg);

	ret = usb_submit_urb(agg->urb, GFP_ATOMIC);
	अगर (ret < 0)
		usb_स्वतःpm_put_पूर्णांकerface_async(tp->पूर्णांकf);

out_tx_fill:
	वापस ret;
पूर्ण

अटल u8 r8152_rx_csum(काष्ठा r8152 *tp, काष्ठा rx_desc *rx_desc)
अणु
	u8 checksum = CHECKSUM_NONE;
	u32 opts2, opts3;

	अगर (!(tp->netdev->features & NETIF_F_RXCSUM))
		जाओ वापस_result;

	opts2 = le32_to_cpu(rx_desc->opts2);
	opts3 = le32_to_cpu(rx_desc->opts3);

	अगर (opts2 & RD_IPV4_CS) अणु
		अगर (opts3 & IPF)
			checksum = CHECKSUM_NONE;
		अन्यथा अगर ((opts2 & RD_UDP_CS) && !(opts3 & UDPF))
			checksum = CHECKSUM_UNNECESSARY;
		अन्यथा अगर ((opts2 & RD_TCP_CS) && !(opts3 & TCPF))
			checksum = CHECKSUM_UNNECESSARY;
	पूर्ण अन्यथा अगर (opts2 & RD_IPV6_CS) अणु
		अगर ((opts2 & RD_UDP_CS) && !(opts3 & UDPF))
			checksum = CHECKSUM_UNNECESSARY;
		अन्यथा अगर ((opts2 & RD_TCP_CS) && !(opts3 & TCPF))
			checksum = CHECKSUM_UNNECESSARY;
	पूर्ण

वापस_result:
	वापस checksum;
पूर्ण

अटल अंतरभूत bool rx_count_exceed(काष्ठा r8152 *tp)
अणु
	वापस atomic_पढ़ो(&tp->rx_count) > RTL8152_MAX_RX;
पूर्ण

अटल अंतरभूत पूर्णांक agg_offset(काष्ठा rx_agg *agg, व्योम *addr)
अणु
	वापस (पूर्णांक)(addr - agg->buffer);
पूर्ण

अटल काष्ठा rx_agg *rtl_get_मुक्त_rx(काष्ठा r8152 *tp, gfp_t mflags)
अणु
	काष्ठा rx_agg *agg, *agg_next, *agg_मुक्त = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tp->rx_lock, flags);

	list_क्रम_each_entry_safe(agg, agg_next, &tp->rx_used, list) अणु
		अगर (page_count(agg->page) == 1) अणु
			अगर (!agg_मुक्त) अणु
				list_del_init(&agg->list);
				agg_मुक्त = agg;
				जारी;
			पूर्ण
			अगर (rx_count_exceed(tp)) अणु
				list_del_init(&agg->list);
				मुक्त_rx_agg(tp, agg);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&tp->rx_lock, flags);

	अगर (!agg_मुक्त && atomic_पढ़ो(&tp->rx_count) < tp->rx_pending)
		agg_मुक्त = alloc_rx_agg(tp, mflags);

	वापस agg_मुक्त;
पूर्ण

अटल पूर्णांक rx_bottom(काष्ठा r8152 *tp, पूर्णांक budget)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *cursor, *next, rx_queue;
	पूर्णांक ret = 0, work_करोne = 0;
	काष्ठा napi_काष्ठा *napi = &tp->napi;

	अगर (!skb_queue_empty(&tp->rx_queue)) अणु
		जबतक (work_करोne < budget) अणु
			काष्ठा sk_buff *skb = __skb_dequeue(&tp->rx_queue);
			काष्ठा net_device *netdev = tp->netdev;
			काष्ठा net_device_stats *stats = &netdev->stats;
			अचिन्हित पूर्णांक pkt_len;

			अगर (!skb)
				अवरोध;

			pkt_len = skb->len;
			napi_gro_receive(napi, skb);
			work_करोne++;
			stats->rx_packets++;
			stats->rx_bytes += pkt_len;
		पूर्ण
	पूर्ण

	अगर (list_empty(&tp->rx_करोne))
		जाओ out1;

	INIT_LIST_HEAD(&rx_queue);
	spin_lock_irqsave(&tp->rx_lock, flags);
	list_splice_init(&tp->rx_करोne, &rx_queue);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	list_क्रम_each_safe(cursor, next, &rx_queue) अणु
		काष्ठा rx_desc *rx_desc;
		काष्ठा rx_agg *agg, *agg_मुक्त;
		पूर्णांक len_used = 0;
		काष्ठा urb *urb;
		u8 *rx_data;

		list_del_init(cursor);

		agg = list_entry(cursor, काष्ठा rx_agg, list);
		urb = agg->urb;
		अगर (urb->actual_length < ETH_ZLEN)
			जाओ submit;

		agg_मुक्त = rtl_get_मुक्त_rx(tp, GFP_ATOMIC);

		rx_desc = agg->buffer;
		rx_data = agg->buffer;
		len_used += माप(काष्ठा rx_desc);

		जबतक (urb->actual_length > len_used) अणु
			काष्ठा net_device *netdev = tp->netdev;
			काष्ठा net_device_stats *stats = &netdev->stats;
			अचिन्हित पूर्णांक pkt_len, rx_frag_head_sz;
			काष्ठा sk_buff *skb;

			/* limite the skb numbers क्रम rx_queue */
			अगर (unlikely(skb_queue_len(&tp->rx_queue) >= 1000))
				अवरोध;

			pkt_len = le32_to_cpu(rx_desc->opts1) & RX_LEN_MASK;
			अगर (pkt_len < ETH_ZLEN)
				अवरोध;

			len_used += pkt_len;
			अगर (urb->actual_length < len_used)
				अवरोध;

			pkt_len -= ETH_FCS_LEN;
			rx_data += माप(काष्ठा rx_desc);

			अगर (!agg_मुक्त || tp->rx_copyअवरोध > pkt_len)
				rx_frag_head_sz = pkt_len;
			अन्यथा
				rx_frag_head_sz = tp->rx_copyअवरोध;

			skb = napi_alloc_skb(napi, rx_frag_head_sz);
			अगर (!skb) अणु
				stats->rx_dropped++;
				जाओ find_next_rx;
			पूर्ण

			skb->ip_summed = r8152_rx_csum(tp, rx_desc);
			स_नकल(skb->data, rx_data, rx_frag_head_sz);
			skb_put(skb, rx_frag_head_sz);
			pkt_len -= rx_frag_head_sz;
			rx_data += rx_frag_head_sz;
			अगर (pkt_len) अणु
				skb_add_rx_frag(skb, 0, agg->page,
						agg_offset(agg, rx_data),
						pkt_len,
						SKB_DATA_ALIGN(pkt_len));
				get_page(agg->page);
			पूर्ण

			skb->protocol = eth_type_trans(skb, netdev);
			rtl_rx_vlan_tag(rx_desc, skb);
			अगर (work_करोne < budget) अणु
				work_करोne++;
				stats->rx_packets++;
				stats->rx_bytes += skb->len;
				napi_gro_receive(napi, skb);
			पूर्ण अन्यथा अणु
				__skb_queue_tail(&tp->rx_queue, skb);
			पूर्ण

find_next_rx:
			rx_data = rx_agg_align(rx_data + pkt_len + ETH_FCS_LEN);
			rx_desc = (काष्ठा rx_desc *)rx_data;
			len_used = agg_offset(agg, rx_data);
			len_used += माप(काष्ठा rx_desc);
		पूर्ण

		WARN_ON(!agg_मुक्त && page_count(agg->page) > 1);

		अगर (agg_मुक्त) अणु
			spin_lock_irqsave(&tp->rx_lock, flags);
			अगर (page_count(agg->page) == 1) अणु
				list_add(&agg_मुक्त->list, &tp->rx_used);
			पूर्ण अन्यथा अणु
				list_add_tail(&agg->list, &tp->rx_used);
				agg = agg_मुक्त;
				urb = agg->urb;
			पूर्ण
			spin_unlock_irqrestore(&tp->rx_lock, flags);
		पूर्ण

submit:
		अगर (!ret) अणु
			ret = r8152_submit_rx(tp, agg, GFP_ATOMIC);
		पूर्ण अन्यथा अणु
			urb->actual_length = 0;
			list_add_tail(&agg->list, next);
		पूर्ण
	पूर्ण

	अगर (!list_empty(&rx_queue)) अणु
		spin_lock_irqsave(&tp->rx_lock, flags);
		list_splice_tail(&rx_queue, &tp->rx_करोne);
		spin_unlock_irqrestore(&tp->rx_lock, flags);
	पूर्ण

out1:
	वापस work_करोne;
पूर्ण

अटल व्योम tx_bottom(काष्ठा r8152 *tp)
अणु
	पूर्णांक res;

	करो अणु
		काष्ठा net_device *netdev = tp->netdev;
		काष्ठा tx_agg *agg;

		अगर (skb_queue_empty(&tp->tx_queue))
			अवरोध;

		agg = r8152_get_tx_agg(tp);
		अगर (!agg)
			अवरोध;

		res = r8152_tx_agg_fill(tp, agg);
		अगर (!res)
			जारी;

		अगर (res == -ENODEV) अणु
			rtl_set_unplug(tp);
			netअगर_device_detach(netdev);
		पूर्ण अन्यथा अणु
			काष्ठा net_device_stats *stats = &netdev->stats;
			अचिन्हित दीर्घ flags;

			netअगर_warn(tp, tx_err, netdev,
				   "failed tx_urb %d\n", res);
			stats->tx_dropped += agg->skb_num;

			spin_lock_irqsave(&tp->tx_lock, flags);
			list_add_tail(&agg->list, &tp->tx_मुक्त);
			spin_unlock_irqrestore(&tp->tx_lock, flags);
		पूर्ण
	पूर्ण जबतक (res == 0);
पूर्ण

अटल व्योम bottom_half(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा r8152 *tp = from_tasklet(tp, t, tx_tl);

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	अगर (!test_bit(WORK_ENABLE, &tp->flags))
		वापस;

	/* When link करोwn, the driver would cancel all bulks. */
	/* This aव्योम the re-submitting bulk */
	अगर (!netअगर_carrier_ok(tp->netdev))
		वापस;

	clear_bit(SCHEDULE_TASKLET, &tp->flags);

	tx_bottom(tp);
पूर्ण

अटल पूर्णांक r8152_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा r8152 *tp = container_of(napi, काष्ठा r8152, napi);
	पूर्णांक work_करोne;

	work_करोne = rx_bottom(tp, budget);

	अगर (work_करोne < budget) अणु
		अगर (!napi_complete_करोne(napi, work_करोne))
			जाओ out;
		अगर (!list_empty(&tp->rx_करोne))
			napi_schedule(napi);
	पूर्ण

out:
	वापस work_करोne;
पूर्ण

अटल
पूर्णांक r8152_submit_rx(काष्ठा r8152 *tp, काष्ठा rx_agg *agg, gfp_t mem_flags)
अणु
	पूर्णांक ret;

	/* The rx would be stopped, so skip submitting */
	अगर (test_bit(RTL8152_UNPLUG, &tp->flags) ||
	    !test_bit(WORK_ENABLE, &tp->flags) || !netअगर_carrier_ok(tp->netdev))
		वापस 0;

	usb_fill_bulk_urb(agg->urb, tp->udev, usb_rcvbulkpipe(tp->udev, 1),
			  agg->buffer, tp->rx_buf_sz,
			  (usb_complete_t)पढ़ो_bulk_callback, agg);

	ret = usb_submit_urb(agg->urb, mem_flags);
	अगर (ret == -ENODEV) अणु
		rtl_set_unplug(tp);
		netअगर_device_detach(tp->netdev);
	पूर्ण अन्यथा अगर (ret) अणु
		काष्ठा urb *urb = agg->urb;
		अचिन्हित दीर्घ flags;

		urb->actual_length = 0;
		spin_lock_irqsave(&tp->rx_lock, flags);
		list_add_tail(&agg->list, &tp->rx_करोne);
		spin_unlock_irqrestore(&tp->rx_lock, flags);

		netअगर_err(tp, rx_err, tp->netdev,
			  "Couldn't submit rx[%p], ret = %d\n", agg, ret);

		napi_schedule(&tp->napi);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम rtl_drop_queued_tx(काष्ठा r8152 *tp)
अणु
	काष्ठा net_device_stats *stats = &tp->netdev->stats;
	काष्ठा sk_buff_head skb_head, *tx_queue = &tp->tx_queue;
	काष्ठा sk_buff *skb;

	अगर (skb_queue_empty(tx_queue))
		वापस;

	__skb_queue_head_init(&skb_head);
	spin_lock_bh(&tx_queue->lock);
	skb_queue_splice_init(tx_queue, &skb_head);
	spin_unlock_bh(&tx_queue->lock);

	जबतक ((skb = __skb_dequeue(&skb_head))) अणु
		dev_kमुक्त_skb(skb);
		stats->tx_dropped++;
	पूर्ण
पूर्ण

अटल व्योम rtl8152_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);

	netअगर_warn(tp, tx_err, netdev, "Tx timeout\n");

	usb_queue_reset_device(tp->पूर्णांकf);
पूर्ण

अटल व्योम rtl8152_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);

	अगर (netअगर_carrier_ok(netdev)) अणु
		set_bit(RTL8152_SET_RX_MODE, &tp->flags);
		schedule_delayed_work(&tp->schedule, 0);
	पूर्ण
पूर्ण

अटल व्योम _rtl8152_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);
	u32 mc_filter[2];	/* Multicast hash filter */
	__le32 पंचांगp[2];
	u32 ocp_data;

	netअगर_stop_queue(netdev);
	ocp_data = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_data |= RCR_AB | RCR_APM;

	अगर (netdev->flags & IFF_PROMISC) अणु
		/* Unconditionally log net taps. */
		netअगर_notice(tp, link, netdev, "Promiscuous mode enabled\n");
		ocp_data |= RCR_AM | RCR_AAP;
		mc_filter[1] = 0xffffffff;
		mc_filter[0] = 0xffffffff;
	पूर्ण अन्यथा अगर ((netdev_mc_count(netdev) > multicast_filter_limit) ||
		   (netdev->flags & IFF_ALLMULTI)) अणु
		/* Too many to filter perfectly -- accept all multicasts. */
		ocp_data |= RCR_AM;
		mc_filter[1] = 0xffffffff;
		mc_filter[0] = 0xffffffff;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;

		mc_filter[1] = 0;
		mc_filter[0] = 0;
		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			पूर्णांक bit_nr = ether_crc(ETH_ALEN, ha->addr) >> 26;

			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
			ocp_data |= RCR_AM;
		पूर्ण
	पूर्ण

	पंचांगp[0] = __cpu_to_le32(swab32(mc_filter[1]));
	पंचांगp[1] = __cpu_to_le32(swab32(mc_filter[0]));

	pla_ocp_ग_लिखो(tp, PLA_MAR, BYTE_EN_DWORD, माप(पंचांगp), पंचांगp);
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
	netअगर_wake_queue(netdev);
पूर्ण

अटल netdev_features_t
rtl8152_features_check(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       netdev_features_t features)
अणु
	u32 mss = skb_shinfo(skb)->gso_size;
	पूर्णांक max_offset = mss ? GTTCPHO_MAX : TCPHO_MAX;
	पूर्णांक offset = skb_transport_offset(skb);

	अगर ((mss || skb->ip_summed == CHECKSUM_PARTIAL) && offset > max_offset)
		features &= ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
	अन्यथा अगर ((skb->len + माप(काष्ठा tx_desc)) > agg_buf_sz)
		features &= ~NETIF_F_GSO_MASK;

	वापस features;
पूर्ण

अटल netdev_tx_t rtl8152_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *netdev)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);

	skb_tx_बारtamp(skb);

	skb_queue_tail(&tp->tx_queue, skb);

	अगर (!list_empty(&tp->tx_मुक्त)) अणु
		अगर (test_bit(SELECTIVE_SUSPEND, &tp->flags)) अणु
			set_bit(SCHEDULE_TASKLET, &tp->flags);
			schedule_delayed_work(&tp->schedule, 0);
		पूर्ण अन्यथा अणु
			usb_mark_last_busy(tp->udev);
			tasklet_schedule(&tp->tx_tl);
		पूर्ण
	पूर्ण अन्यथा अगर (skb_queue_len(&tp->tx_queue) > tp->tx_qlen) अणु
		netअगर_stop_queue(netdev);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम r8152b_reset_packet_filter(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_FMC);
	ocp_data &= ~FMC_FCR_MCU_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_FMC, ocp_data);
	ocp_data |= FMC_FCR_MCU_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_FMC, ocp_data);
पूर्ण

अटल व्योम rtl8152_nic_reset(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	पूर्णांक i;

	चयन (tp->version) अणु
	हाल RTL_TEST_01:
	हाल RTL_VER_10:
	हाल RTL_VER_11:
		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_CR);
		ocp_data &= ~CR_TE;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CR, ocp_data);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_BMU_RESET);
		ocp_data &= ~BMU_RESET_EP_IN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
		ocp_data |= CDC_ECM_EN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_CR);
		ocp_data &= ~CR_RE;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CR, ocp_data);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_BMU_RESET);
		ocp_data |= BMU_RESET_EP_IN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
		ocp_data &= ~CDC_ECM_EN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);
		अवरोध;

	शेष:
		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CR, CR_RST);

		क्रम (i = 0; i < 1000; i++) अणु
			अगर (!(ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_CR) & CR_RST))
				अवरोध;
			usleep_range(100, 400);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_tx_qlen(काष्ठा r8152 *tp)
अणु
	tp->tx_qlen = agg_buf_sz / (mtu_to_size(tp->netdev->mtu) + माप(काष्ठा tx_desc));
पूर्ण

अटल अंतरभूत u16 rtl8152_get_speed(काष्ठा r8152 *tp)
अणु
	वापस ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_PHYSTATUS);
पूर्ण

अटल व्योम rtl_eee_plus_en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EEEP_CR);
	अगर (enable)
		ocp_data |= EEEP_CR_EEEP_TX;
	अन्यथा
		ocp_data &= ~EEEP_CR_EEEP_TX;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EEEP_CR, ocp_data);
पूर्ण

अटल व्योम rtl_set_eee_plus(काष्ठा r8152 *tp)
अणु
	अगर (rtl8152_get_speed(tp) & _10bps)
		rtl_eee_plus_en(tp, true);
	अन्यथा
		rtl_eee_plus_en(tp, false);
पूर्ण

अटल व्योम rxdy_gated_en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MISC_1);
	अगर (enable)
		ocp_data |= RXDY_GATED_EN;
	अन्यथा
		ocp_data &= ~RXDY_GATED_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MISC_1, ocp_data);
पूर्ण

अटल पूर्णांक rtl_start_rx(काष्ठा r8152 *tp)
अणु
	काष्ठा rx_agg *agg, *agg_next;
	काष्ठा list_head पंचांगp_list;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0, i = 0;

	INIT_LIST_HEAD(&पंचांगp_list);

	spin_lock_irqsave(&tp->rx_lock, flags);

	INIT_LIST_HEAD(&tp->rx_करोne);
	INIT_LIST_HEAD(&tp->rx_used);

	list_splice_init(&tp->rx_info, &पंचांगp_list);

	spin_unlock_irqrestore(&tp->rx_lock, flags);

	list_क्रम_each_entry_safe(agg, agg_next, &पंचांगp_list, info_list) अणु
		INIT_LIST_HEAD(&agg->list);

		/* Only RTL8152_MAX_RX rx_agg need to be submitted. */
		अगर (++i > RTL8152_MAX_RX) अणु
			spin_lock_irqsave(&tp->rx_lock, flags);
			list_add_tail(&agg->list, &tp->rx_used);
			spin_unlock_irqrestore(&tp->rx_lock, flags);
		पूर्ण अन्यथा अगर (unlikely(ret < 0)) अणु
			spin_lock_irqsave(&tp->rx_lock, flags);
			list_add_tail(&agg->list, &tp->rx_करोne);
			spin_unlock_irqrestore(&tp->rx_lock, flags);
		पूर्ण अन्यथा अणु
			ret = r8152_submit_rx(tp, agg, GFP_KERNEL);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&tp->rx_lock, flags);
	WARN_ON(!list_empty(&tp->rx_info));
	list_splice(&पंचांगp_list, &tp->rx_info);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक rtl_stop_rx(काष्ठा r8152 *tp)
अणु
	काष्ठा rx_agg *agg, *agg_next;
	काष्ठा list_head पंचांगp_list;
	अचिन्हित दीर्घ flags;

	INIT_LIST_HEAD(&पंचांगp_list);

	/* The usb_समाप्त_urb() couldn't be used in atomic.
	 * Thereक्रमe, move the list of rx_info to a पंचांगp one.
	 * Then, list_क्रम_each_entry_safe could be used without
	 * spin lock.
	 */

	spin_lock_irqsave(&tp->rx_lock, flags);
	list_splice_init(&tp->rx_info, &पंचांगp_list);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	list_क्रम_each_entry_safe(agg, agg_next, &पंचांगp_list, info_list) अणु
		/* At least RTL8152_MAX_RX rx_agg have the page_count being
		 * equal to 1, so the other ones could be मुक्तd safely.
		 */
		अगर (page_count(agg->page) > 1)
			मुक्त_rx_agg(tp, agg);
		अन्यथा
			usb_समाप्त_urb(agg->urb);
	पूर्ण

	/* Move back the list of temp to the rx_info */
	spin_lock_irqsave(&tp->rx_lock, flags);
	WARN_ON(!list_empty(&tp->rx_info));
	list_splice(&पंचांगp_list, &tp->rx_info);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	जबतक (!skb_queue_empty(&tp->rx_queue))
		dev_kमुक्त_skb(__skb_dequeue(&tp->rx_queue));

	वापस 0;
पूर्ण

अटल व्योम rtl_set_अगरg(काष्ठा r8152 *tp, u16 speed)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_TCR1);
	ocp_data &= ~IFG_MASK;
	अगर ((speed & (_10bps | _100bps)) && !(speed & FULL_DUP)) अणु
		ocp_data |= IFG_144NS;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TCR1, ocp_data);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
		ocp_data &= ~TX10MIDLE_EN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);
	पूर्ण अन्यथा अणु
		ocp_data |= IFG_96NS;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TCR1, ocp_data);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
		ocp_data |= TX10MIDLE_EN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम r8153b_rx_agg_chg_indicate(काष्ठा r8152 *tp)
अणु
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_UPT_RXDMA_OWN,
		       OWN_UPDATE | OWN_CLEAR);
पूर्ण

अटल पूर्णांक rtl_enable(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	r8152b_reset_packet_filter(tp);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_CR);
	ocp_data |= CR_RE | CR_TE;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CR, ocp_data);

	चयन (tp->version) अणु
	हाल RTL_VER_08:
	हाल RTL_VER_09:
	हाल RTL_VER_14:
		r8153b_rx_agg_chg_indicate(tp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rxdy_gated_en(tp, false);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8152_enable(काष्ठा r8152 *tp)
अणु
	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस -ENODEV;

	set_tx_qlen(tp);
	rtl_set_eee_plus(tp);

	वापस rtl_enable(tp);
पूर्ण

अटल व्योम r8153_set_rx_early_समयout(काष्ठा r8152 *tp)
अणु
	u32 ocp_data = tp->coalesce / 8;

	चयन (tp->version) अणु
	हाल RTL_VER_03:
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_RX_EARLY_TIMEOUT,
			       ocp_data);
		अवरोध;

	हाल RTL_VER_08:
	हाल RTL_VER_09:
	हाल RTL_VER_14:
		/* The RTL8153B uses USB_RX_EXTRA_AGGR_TMR क्रम rx समयout
		 * primarily. For USB_RX_EARLY_TIMEOUT, we fix it to 128ns.
		 */
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_RX_EARLY_TIMEOUT,
			       128 / 8);
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_RX_EXTRA_AGGR_TMR,
			       ocp_data);
		अवरोध;

	हाल RTL_VER_10:
	हाल RTL_VER_11:
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_RX_EARLY_TIMEOUT,
			       640 / 8);
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_RX_EXTRA_AGGR_TMR,
			       ocp_data);
		r8153b_rx_agg_chg_indicate(tp);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम r8153_set_rx_early_size(काष्ठा r8152 *tp)
अणु
	u32 ocp_data = tp->rx_buf_sz - rx_reserved_size(tp->netdev->mtu);

	चयन (tp->version) अणु
	हाल RTL_VER_03:
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_RX_EARLY_SIZE,
			       ocp_data / 4);
		अवरोध;
	हाल RTL_VER_08:
	हाल RTL_VER_09:
	हाल RTL_VER_14:
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_RX_EARLY_SIZE,
			       ocp_data / 8);
		अवरोध;
	हाल RTL_TEST_01:
	हाल RTL_VER_10:
	हाल RTL_VER_11:
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_RX_EARLY_SIZE,
			       ocp_data / 8);
		r8153b_rx_agg_chg_indicate(tp);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8153_enable(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस -ENODEV;

	set_tx_qlen(tp);
	rtl_set_eee_plus(tp);
	r8153_set_rx_early_समयout(tp);
	r8153_set_rx_early_size(tp);

	rtl_set_अगरg(tp, rtl8152_get_speed(tp));

	चयन (tp->version) अणु
	हाल RTL_VER_09:
	हाल RTL_VER_14:
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_TASK);
		ocp_data &= ~FC_PATCH_TASK;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);
		usleep_range(1000, 2000);
		ocp_data |= FC_PATCH_TASK;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rtl_enable(tp);
पूर्ण

अटल व्योम rtl_disable(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	पूर्णांक i;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags)) अणु
		rtl_drop_queued_tx(tp);
		वापस;
	पूर्ण

	ocp_data = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rtl_drop_queued_tx(tp);

	क्रम (i = 0; i < RTL8152_MAX_TX; i++)
		usb_समाप्त_urb(tp->tx_info[i].urb);

	rxdy_gated_en(tp, true);

	क्रम (i = 0; i < 1000; i++) अणु
		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		अगर ((ocp_data & FIFO_EMPTY) == FIFO_EMPTY)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	क्रम (i = 0; i < 1000; i++) अणु
		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_TCR0) & TCR0_TX_EMPTY)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	rtl_stop_rx(tp);

	rtl8152_nic_reset(tp);
पूर्ण

अटल व्योम r8152_घातer_cut_en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_UPS_CTRL);
	अगर (enable)
		ocp_data |= POWER_CUT;
	अन्यथा
		ocp_data &= ~POWER_CUT;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_UPS_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_PM_CTRL_STATUS);
	ocp_data &= ~RESUME_INDICATE;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_PM_CTRL_STATUS, ocp_data);
पूर्ण

अटल व्योम rtl_rx_vlan_en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;

	चयन (tp->version) अणु
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_03:
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
	हाल RTL_VER_07:
	हाल RTL_VER_08:
	हाल RTL_VER_09:
	हाल RTL_VER_14:
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CPCR);
		अगर (enable)
			ocp_data |= CPCR_RX_VLAN;
		अन्यथा
			ocp_data &= ~CPCR_RX_VLAN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_CPCR, ocp_data);
		अवरोध;

	हाल RTL_TEST_01:
	हाल RTL_VER_10:
	हाल RTL_VER_11:
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_15:
	शेष:
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_RCR1);
		अगर (enable)
			ocp_data |= OUTER_VLAN | INNER_VLAN;
		अन्यथा
			ocp_data &= ~(OUTER_VLAN | INNER_VLAN);
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RCR1, ocp_data);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8152_set_features(काष्ठा net_device *dev,
				netdev_features_t features)
अणु
	netdev_features_t changed = features ^ dev->features;
	काष्ठा r8152 *tp = netdev_priv(dev);
	पूर्णांक ret;

	ret = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (ret < 0)
		जाओ out;

	mutex_lock(&tp->control);

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX) अणु
		अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
			rtl_rx_vlan_en(tp, true);
		अन्यथा
			rtl_rx_vlan_en(tp, false);
	पूर्ण

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

out:
	वापस ret;
पूर्ण

#घोषणा WAKE_ANY (WAKE_PHY | WAKE_MAGIC | WAKE_UCAST | WAKE_BCAST | WAKE_MCAST)

अटल u32 __rtl_get_wol(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u32 wolopts = 0;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
	अगर (ocp_data & LINK_ON_WAKE_EN)
		wolopts |= WAKE_PHY;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CONFIG5);
	अगर (ocp_data & UWF_EN)
		wolopts |= WAKE_UCAST;
	अगर (ocp_data & BWF_EN)
		wolopts |= WAKE_BCAST;
	अगर (ocp_data & MWF_EN)
		wolopts |= WAKE_MCAST;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CFG_WOL);
	अगर (ocp_data & MAGIC_EN)
		wolopts |= WAKE_MAGIC;

	वापस wolopts;
पूर्ण

अटल व्योम __rtl_set_wol(काष्ठा r8152 *tp, u32 wolopts)
अणु
	u32 ocp_data;

	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
	ocp_data &= ~LINK_ON_WAKE_EN;
	अगर (wolopts & WAKE_PHY)
		ocp_data |= LINK_ON_WAKE_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CONFIG5);
	ocp_data &= ~(UWF_EN | BWF_EN | MWF_EN);
	अगर (wolopts & WAKE_UCAST)
		ocp_data |= UWF_EN;
	अगर (wolopts & WAKE_BCAST)
		ocp_data |= BWF_EN;
	अगर (wolopts & WAKE_MCAST)
		ocp_data |= MWF_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_CONFIG5, ocp_data);

	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CFG_WOL);
	ocp_data &= ~MAGIC_EN;
	अगर (wolopts & WAKE_MAGIC)
		ocp_data |= MAGIC_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_CFG_WOL, ocp_data);

	अगर (wolopts & WAKE_ANY)
		device_set_wakeup_enable(&tp->udev->dev, true);
	अन्यथा
		device_set_wakeup_enable(&tp->udev->dev, false);
पूर्ण

अटल व्योम r8153_mac_clk_speed_करोwn(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2);

	/* MAC घड़ी speed करोwn */
	अगर (enable)
		ocp_data |= MAC_CLK_SPDWN_EN;
	अन्यथा
		ocp_data &= ~MAC_CLK_SPDWN_EN;

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2, ocp_data);
पूर्ण

अटल व्योम r8156_mac_clk_spd(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;

	/* MAC घड़ी speed करोwn */
	अगर (enable) अणु
		/* aldps_spdwn_ratio, tp10_spdwn_ratio */
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL,
			       0x0403);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2);
		ocp_data &= ~EEE_SPDWN_RATIO_MASK;
		ocp_data |= MAC_CLK_SPDWN_EN | 0x03; /* eee_spdwn_ratio */
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2, ocp_data);
	पूर्ण अन्यथा अणु
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2);
		ocp_data &= ~MAC_CLK_SPDWN_EN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2, ocp_data);
	पूर्ण
पूर्ण

अटल व्योम r8153_u1u2en(काष्ठा r8152 *tp, bool enable)
अणु
	u8 u1u2[8];

	अगर (enable)
		स_रखो(u1u2, 0xff, माप(u1u2));
	अन्यथा
		स_रखो(u1u2, 0x00, माप(u1u2));

	usb_ocp_ग_लिखो(tp, USB_TOLERANCE, BYTE_EN_SIX_BYTES, माप(u1u2), u1u2);
पूर्ण

अटल व्योम r8153b_u1u2en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_LPM_CONFIG);
	अगर (enable)
		ocp_data |= LPM_U1U2_EN;
	अन्यथा
		ocp_data &= ~LPM_U1U2_EN;

	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_LPM_CONFIG, ocp_data);
पूर्ण

अटल व्योम r8153_u2p3en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_U2P3_CTRL);
	अगर (enable)
		ocp_data |= U2P3_ENABLE;
	अन्यथा
		ocp_data &= ~U2P3_ENABLE;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_U2P3_CTRL, ocp_data);
पूर्ण

अटल व्योम r8153b_ups_flags(काष्ठा r8152 *tp)
अणु
	u32 ups_flags = 0;

	अगर (tp->ups_info.green)
		ups_flags |= UPS_FLAGS_EN_GREEN;

	अगर (tp->ups_info.aldps)
		ups_flags |= UPS_FLAGS_EN_ALDPS;

	अगर (tp->ups_info.eee)
		ups_flags |= UPS_FLAGS_EN_EEE;

	अगर (tp->ups_info.flow_control)
		ups_flags |= UPS_FLAGS_EN_FLOW_CTR;

	अगर (tp->ups_info.eee_ckभाग)
		ups_flags |= UPS_FLAGS_EN_EEE_CKDIV;

	अगर (tp->ups_info.eee_cmod_lv)
		ups_flags |= UPS_FLAGS_EEE_CMOD_LV_EN;

	अगर (tp->ups_info.r_tune)
		ups_flags |= UPS_FLAGS_R_TUNE;

	अगर (tp->ups_info._10m_ckभाग)
		ups_flags |= UPS_FLAGS_EN_10M_CKDIV;

	अगर (tp->ups_info.eee_plloff_100)
		ups_flags |= UPS_FLAGS_EEE_PLLOFF_100;

	अगर (tp->ups_info.eee_plloff_giga)
		ups_flags |= UPS_FLAGS_EEE_PLLOFF_GIGA;

	अगर (tp->ups_info._250m_ckभाग)
		ups_flags |= UPS_FLAGS_250M_CKDIV;

	अगर (tp->ups_info.ctap_लघु_off)
		ups_flags |= UPS_FLAGS_CTAP_SHORT_DIS;

	चयन (tp->ups_info.speed_duplex) अणु
	हाल NWAY_10M_HALF:
		ups_flags |= ups_flags_speed(1);
		अवरोध;
	हाल NWAY_10M_FULL:
		ups_flags |= ups_flags_speed(2);
		अवरोध;
	हाल NWAY_100M_HALF:
		ups_flags |= ups_flags_speed(3);
		अवरोध;
	हाल NWAY_100M_FULL:
		ups_flags |= ups_flags_speed(4);
		अवरोध;
	हाल NWAY_1000M_FULL:
		ups_flags |= ups_flags_speed(5);
		अवरोध;
	हाल FORCE_10M_HALF:
		ups_flags |= ups_flags_speed(6);
		अवरोध;
	हाल FORCE_10M_FULL:
		ups_flags |= ups_flags_speed(7);
		अवरोध;
	हाल FORCE_100M_HALF:
		ups_flags |= ups_flags_speed(8);
		अवरोध;
	हाल FORCE_100M_FULL:
		ups_flags |= ups_flags_speed(9);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ocp_ग_लिखो_dword(tp, MCU_TYPE_USB, USB_UPS_FLAGS, ups_flags);
पूर्ण

अटल व्योम r8156_ups_flags(काष्ठा r8152 *tp)
अणु
	u32 ups_flags = 0;

	अगर (tp->ups_info.green)
		ups_flags |= UPS_FLAGS_EN_GREEN;

	अगर (tp->ups_info.aldps)
		ups_flags |= UPS_FLAGS_EN_ALDPS;

	अगर (tp->ups_info.eee)
		ups_flags |= UPS_FLAGS_EN_EEE;

	अगर (tp->ups_info.flow_control)
		ups_flags |= UPS_FLAGS_EN_FLOW_CTR;

	अगर (tp->ups_info.eee_ckभाग)
		ups_flags |= UPS_FLAGS_EN_EEE_CKDIV;

	अगर (tp->ups_info._10m_ckभाग)
		ups_flags |= UPS_FLAGS_EN_10M_CKDIV;

	अगर (tp->ups_info.eee_plloff_100)
		ups_flags |= UPS_FLAGS_EEE_PLLOFF_100;

	अगर (tp->ups_info.eee_plloff_giga)
		ups_flags |= UPS_FLAGS_EEE_PLLOFF_GIGA;

	अगर (tp->ups_info._250m_ckभाग)
		ups_flags |= UPS_FLAGS_250M_CKDIV;

	चयन (tp->ups_info.speed_duplex) अणु
	हाल FORCE_10M_HALF:
		ups_flags |= ups_flags_speed(0);
		अवरोध;
	हाल FORCE_10M_FULL:
		ups_flags |= ups_flags_speed(1);
		अवरोध;
	हाल FORCE_100M_HALF:
		ups_flags |= ups_flags_speed(2);
		अवरोध;
	हाल FORCE_100M_FULL:
		ups_flags |= ups_flags_speed(3);
		अवरोध;
	हाल NWAY_10M_HALF:
		ups_flags |= ups_flags_speed(4);
		अवरोध;
	हाल NWAY_10M_FULL:
		ups_flags |= ups_flags_speed(5);
		अवरोध;
	हाल NWAY_100M_HALF:
		ups_flags |= ups_flags_speed(6);
		अवरोध;
	हाल NWAY_100M_FULL:
		ups_flags |= ups_flags_speed(7);
		अवरोध;
	हाल NWAY_1000M_FULL:
		ups_flags |= ups_flags_speed(8);
		अवरोध;
	हाल NWAY_2500M_FULL:
		ups_flags |= ups_flags_speed(9);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (tp->ups_info.lite_mode) अणु
	हाल 1:
		ups_flags |= 0 << 5;
		अवरोध;
	हाल 2:
		ups_flags |= 2 << 5;
		अवरोध;
	हाल 0:
	शेष:
		ups_flags |= 1 << 5;
		अवरोध;
	पूर्ण

	ocp_ग_लिखो_dword(tp, MCU_TYPE_USB, USB_UPS_FLAGS, ups_flags);
पूर्ण

अटल व्योम rtl_green_en(काष्ठा r8152 *tp, bool enable)
अणु
	u16 data;

	data = sram_पढ़ो(tp, SRAM_GREEN_CFG);
	अगर (enable)
		data |= GREEN_ETH_EN;
	अन्यथा
		data &= ~GREEN_ETH_EN;
	sram_ग_लिखो(tp, SRAM_GREEN_CFG, data);

	tp->ups_info.green = enable;
पूर्ण

अटल व्योम r8153b_green_en(काष्ठा r8152 *tp, bool enable)
अणु
	अगर (enable) अणु
		sram_ग_लिखो(tp, 0x8045, 0);	/* 10M abiq&ldvbias */
		sram_ग_लिखो(tp, 0x804d, 0x1222);	/* 100M लघु abiq&ldvbias */
		sram_ग_लिखो(tp, 0x805d, 0x0022);	/* 1000M लघु abiq&ldvbias */
	पूर्ण अन्यथा अणु
		sram_ग_लिखो(tp, 0x8045, 0x2444);	/* 10M abiq&ldvbias */
		sram_ग_लिखो(tp, 0x804d, 0x2444);	/* 100M लघु abiq&ldvbias */
		sram_ग_लिखो(tp, 0x805d, 0x2444);	/* 1000M लघु abiq&ldvbias */
	पूर्ण

	rtl_green_en(tp, true);
पूर्ण

अटल u16 r8153_phy_status(काष्ठा r8152 *tp, u16 desired)
अणु
	u16 data;
	पूर्णांक i;

	क्रम (i = 0; i < 500; i++) अणु
		data = ocp_reg_पढ़ो(tp, OCP_PHY_STATUS);
		data &= PHY_STAT_MASK;
		अगर (desired) अणु
			अगर (data == desired)
				अवरोध;
		पूर्ण अन्यथा अगर (data == PHY_STAT_LAN_ON || data == PHY_STAT_PWRDN ||
			   data == PHY_STAT_EXT_INIT) अणु
			अवरोध;
		पूर्ण

		msleep(20);
		अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
			अवरोध;
	पूर्ण

	वापस data;
पूर्ण

अटल व्योम r8153b_ups_en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_POWER_CUT);

	अगर (enable) अणु
		r8153b_ups_flags(tp);

		ocp_data |= UPS_EN | USP_PREWAKE | PHASE2_EN;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data |= UPS_FORCE_PWR_DOWN;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);
	पूर्ण अन्यथा अणु
		ocp_data &= ~(UPS_EN | USP_PREWAKE);
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data &= ~UPS_FORCE_PWR_DOWN;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);

		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_MISC_0) & PCUT_STATUS) अणु
			पूर्णांक i;

			क्रम (i = 0; i < 500; i++) अणु
				अगर (ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
				    AUTOLOAD_DONE)
					अवरोध;
				msleep(20);
			पूर्ण

			tp->rtl_ops.hw_phy_cfg(tp);

			rtl8152_set_speed(tp, tp->स्वतःneg, tp->speed,
					  tp->duplex, tp->advertising);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम r8153c_ups_en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_POWER_CUT);

	अगर (enable) अणु
		r8153b_ups_flags(tp);

		ocp_data |= UPS_EN | USP_PREWAKE | PHASE2_EN;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data |= UPS_FORCE_PWR_DOWN;
		ocp_data &= ~BIT(7);
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);
	पूर्ण अन्यथा अणु
		ocp_data &= ~(UPS_EN | USP_PREWAKE);
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data &= ~UPS_FORCE_PWR_DOWN;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);

		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_MISC_0) & PCUT_STATUS) अणु
			पूर्णांक i;

			क्रम (i = 0; i < 500; i++) अणु
				अगर (ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
				    AUTOLOAD_DONE)
					अवरोध;
				msleep(20);
			पूर्ण

			tp->rtl_ops.hw_phy_cfg(tp);

			rtl8152_set_speed(tp, tp->स्वतःneg, tp->speed,
					  tp->duplex, tp->advertising);
		पूर्ण

		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
		ocp_data |= BIT(8);
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	पूर्ण
पूर्ण

अटल व्योम r8156_ups_en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_POWER_CUT);

	अगर (enable) अणु
		r8156_ups_flags(tp);

		ocp_data |= UPS_EN | USP_PREWAKE | PHASE2_EN;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data |= UPS_FORCE_PWR_DOWN;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);

		चयन (tp->version) अणु
		हाल RTL_VER_13:
		हाल RTL_VER_15:
			ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_UPHY_XTAL);
			ocp_data &= ~OOBS_POLLING;
			ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_UPHY_XTAL, ocp_data);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		ocp_data &= ~(UPS_EN | USP_PREWAKE);
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data &= ~UPS_FORCE_PWR_DOWN;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);

		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_MISC_0) & PCUT_STATUS) अणु
			tp->rtl_ops.hw_phy_cfg(tp);

			rtl8152_set_speed(tp, tp->स्वतःneg, tp->speed,
					  tp->duplex, tp->advertising);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम r8153_घातer_cut_en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_POWER_CUT);
	अगर (enable)
		ocp_data |= PWR_EN | PHASE2_EN;
	अन्यथा
		ocp_data &= ~(PWR_EN | PHASE2_EN);
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_MISC_0);
	ocp_data &= ~PCUT_STATUS;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_MISC_0, ocp_data);
पूर्ण

अटल व्योम r8153b_घातer_cut_en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_POWER_CUT);
	अगर (enable)
		ocp_data |= PWR_EN | PHASE2_EN;
	अन्यथा
		ocp_data &= ~PWR_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_MISC_0);
	ocp_data &= ~PCUT_STATUS;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_MISC_0, ocp_data);
पूर्ण

अटल व्योम r8153_queue_wake(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_INDICATE_FALG);
	अगर (enable)
		ocp_data |= UPCOMING_RUNTIME_D3;
	अन्यथा
		ocp_data &= ~UPCOMING_RUNTIME_D3;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_INDICATE_FALG, ocp_data);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_SUSPEND_FLAG);
	ocp_data &= ~LINK_CHG_EVENT;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_SUSPEND_FLAG, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	ocp_data &= ~LINK_CHANGE_FLAG;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);
पूर्ण

अटल bool rtl_can_wakeup(काष्ठा r8152 *tp)
अणु
	काष्ठा usb_device *udev = tp->udev;

	वापस (udev->actconfig->desc.bmAttributes & USB_CONFIG_ATT_WAKEUP);
पूर्ण

अटल व्योम rtl_runसमय_suspend_enable(काष्ठा r8152 *tp, bool enable)
अणु
	अगर (enable) अणु
		u32 ocp_data;

		__rtl_set_wol(tp, WAKE_ANY);

		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
		ocp_data |= LINK_OFF_WAKE_EN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	पूर्ण अन्यथा अणु
		u32 ocp_data;

		__rtl_set_wol(tp, tp->saved_wolopts);

		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
		ocp_data &= ~LINK_OFF_WAKE_EN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	पूर्ण
पूर्ण

अटल व्योम rtl8153_runसमय_enable(काष्ठा r8152 *tp, bool enable)
अणु
	अगर (enable) अणु
		r8153_u1u2en(tp, false);
		r8153_u2p3en(tp, false);
		rtl_runसमय_suspend_enable(tp, true);
	पूर्ण अन्यथा अणु
		rtl_runसमय_suspend_enable(tp, false);

		चयन (tp->version) अणु
		हाल RTL_VER_03:
		हाल RTL_VER_04:
			अवरोध;
		हाल RTL_VER_05:
		हाल RTL_VER_06:
		शेष:
			r8153_u2p3en(tp, true);
			अवरोध;
		पूर्ण

		r8153_u1u2en(tp, true);
	पूर्ण
पूर्ण

अटल व्योम rtl8153b_runसमय_enable(काष्ठा r8152 *tp, bool enable)
अणु
	अगर (enable) अणु
		r8153_queue_wake(tp, true);
		r8153b_u1u2en(tp, false);
		r8153_u2p3en(tp, false);
		rtl_runसमय_suspend_enable(tp, true);
		r8153b_ups_en(tp, true);
	पूर्ण अन्यथा अणु
		r8153b_ups_en(tp, false);
		r8153_queue_wake(tp, false);
		rtl_runसमय_suspend_enable(tp, false);
		अगर (tp->udev->speed >= USB_SPEED_SUPER)
			r8153b_u1u2en(tp, true);
	पूर्ण
पूर्ण

अटल व्योम rtl8153c_runसमय_enable(काष्ठा r8152 *tp, bool enable)
अणु
	अगर (enable) अणु
		r8153_queue_wake(tp, true);
		r8153b_u1u2en(tp, false);
		r8153_u2p3en(tp, false);
		rtl_runसमय_suspend_enable(tp, true);
		r8153c_ups_en(tp, true);
	पूर्ण अन्यथा अणु
		r8153c_ups_en(tp, false);
		r8153_queue_wake(tp, false);
		rtl_runसमय_suspend_enable(tp, false);
		r8153b_u1u2en(tp, true);
	पूर्ण
पूर्ण

अटल व्योम rtl8156_runसमय_enable(काष्ठा r8152 *tp, bool enable)
अणु
	अगर (enable) अणु
		r8153_queue_wake(tp, true);
		r8153b_u1u2en(tp, false);
		r8153_u2p3en(tp, false);
		rtl_runसमय_suspend_enable(tp, true);
	पूर्ण अन्यथा अणु
		r8153_queue_wake(tp, false);
		rtl_runसमय_suspend_enable(tp, false);
		r8153_u2p3en(tp, true);
		अगर (tp->udev->speed >= USB_SPEED_SUPER)
			r8153b_u1u2en(tp, true);
	पूर्ण
पूर्ण

अटल व्योम r8153_tereकरो_off(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	चयन (tp->version) अणु
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_03:
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
	हाल RTL_VER_07:
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG);
		ocp_data &= ~(TEREDO_SEL | TEREDO_RS_EVENT_MASK |
			      OOB_TEREDO_EN);
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG, ocp_data);
		अवरोध;

	हाल RTL_VER_08:
	हाल RTL_VER_09:
	हाल RTL_TEST_01:
	हाल RTL_VER_10:
	हाल RTL_VER_11:
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_14:
	हाल RTL_VER_15:
	शेष:
		/* The bit 0 ~ 7 are relative with tereकरो settings. They are
		 * W1C (ग_लिखो 1 to clear), so set all 1 to disable it.
		 */
		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG, 0xff);
		अवरोध;
	पूर्ण

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_WDT6_CTRL, WDT6_SET_MODE);
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_REALWOW_TIMER, 0);
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_TEREDO_TIMER, 0);
पूर्ण

अटल व्योम rtl_reset_bmu(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_BMU_RESET);
	ocp_data &= ~(BMU_RESET_EP_IN | BMU_RESET_EP_OUT);
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);
	ocp_data |= BMU_RESET_EP_IN | BMU_RESET_EP_OUT;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);
पूर्ण

/* Clear the bp to stop the firmware beक्रमe loading a new one */
अटल व्योम rtl_clear_bp(काष्ठा r8152 *tp, u16 type)
अणु
	चयन (tp->version) अणु
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_07:
		अवरोध;
	हाल RTL_VER_03:
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
		ocp_ग_लिखो_byte(tp, type, PLA_BP_EN, 0);
		अवरोध;
	हाल RTL_VER_08:
	हाल RTL_VER_09:
	हाल RTL_VER_10:
	हाल RTL_VER_11:
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_14:
	हाल RTL_VER_15:
	शेष:
		अगर (type == MCU_TYPE_USB) अणु
			ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_BP2_EN, 0);

			ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BP_8, 0);
			ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BP_9, 0);
			ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BP_10, 0);
			ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BP_11, 0);
			ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BP_12, 0);
			ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BP_13, 0);
			ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BP_14, 0);
			ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BP_15, 0);
		पूर्ण अन्यथा अणु
			ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_BP_EN, 0);
		पूर्ण
		अवरोध;
	पूर्ण

	ocp_ग_लिखो_word(tp, type, PLA_BP_0, 0);
	ocp_ग_लिखो_word(tp, type, PLA_BP_1, 0);
	ocp_ग_लिखो_word(tp, type, PLA_BP_2, 0);
	ocp_ग_लिखो_word(tp, type, PLA_BP_3, 0);
	ocp_ग_लिखो_word(tp, type, PLA_BP_4, 0);
	ocp_ग_लिखो_word(tp, type, PLA_BP_5, 0);
	ocp_ग_लिखो_word(tp, type, PLA_BP_6, 0);
	ocp_ग_लिखो_word(tp, type, PLA_BP_7, 0);

	/* रुको 3 ms to make sure the firmware is stopped */
	usleep_range(3000, 6000);
	ocp_ग_लिखो_word(tp, type, PLA_BP_BA, 0);
पूर्ण

अटल पूर्णांक rtl_phy_patch_request(काष्ठा r8152 *tp, bool request, bool रुको)
अणु
	u16 data, check;
	पूर्णांक i;

	data = ocp_reg_पढ़ो(tp, OCP_PHY_PATCH_CMD);
	अगर (request) अणु
		data |= PATCH_REQUEST;
		check = 0;
	पूर्ण अन्यथा अणु
		data &= ~PATCH_REQUEST;
		check = PATCH_READY;
	पूर्ण
	ocp_reg_ग_लिखो(tp, OCP_PHY_PATCH_CMD, data);

	क्रम (i = 0; रुको && i < 5000; i++) अणु
		u32 ocp_data;

		usleep_range(1000, 2000);
		ocp_data = ocp_reg_पढ़ो(tp, OCP_PHY_PATCH_STAT);
		अगर ((ocp_data & PATCH_READY) ^ check)
			अवरोध;
	पूर्ण

	अगर (request && रुको &&
	    !(ocp_reg_पढ़ो(tp, OCP_PHY_PATCH_STAT) & PATCH_READY)) अणु
		dev_err(&tp->पूर्णांकf->dev, "PHY patch request fail\n");
		rtl_phy_patch_request(tp, false, false);
		वापस -ETIME;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम rtl_patch_key_set(काष्ठा r8152 *tp, u16 key_addr, u16 patch_key)
अणु
	अगर (patch_key && key_addr) अणु
		sram_ग_लिखो(tp, key_addr, patch_key);
		sram_ग_लिखो(tp, SRAM_PHY_LOCK, PHY_PATCH_LOCK);
	पूर्ण अन्यथा अगर (key_addr) अणु
		u16 data;

		sram_ग_लिखो(tp, 0x0000, 0x0000);

		data = ocp_reg_पढ़ो(tp, OCP_PHY_LOCK);
		data &= ~PATCH_LOCK;
		ocp_reg_ग_लिखो(tp, OCP_PHY_LOCK, data);

		sram_ग_लिखो(tp, key_addr, 0x0000);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल पूर्णांक
rtl_pre_ram_code(काष्ठा r8152 *tp, u16 key_addr, u16 patch_key, bool रुको)
अणु
	अगर (rtl_phy_patch_request(tp, true, रुको))
		वापस -ETIME;

	rtl_patch_key_set(tp, key_addr, patch_key);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl_post_ram_code(काष्ठा r8152 *tp, u16 key_addr, bool रुको)
अणु
	rtl_patch_key_set(tp, key_addr, 0);

	rtl_phy_patch_request(tp, false, रुको);

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, tp->ocp_base);

	वापस 0;
पूर्ण

अटल bool rtl8152_is_fw_phy_speed_up_ok(काष्ठा r8152 *tp, काष्ठा fw_phy_speed_up *phy)
अणु
	u16 fw_offset;
	u32 length;
	bool rc = false;

	चयन (tp->version) अणु
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_03:
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
	हाल RTL_VER_07:
	हाल RTL_VER_08:
	हाल RTL_VER_09:
	हाल RTL_VER_10:
	हाल RTL_VER_11:
	हाल RTL_VER_12:
	हाल RTL_VER_14:
		जाओ out;
	हाल RTL_VER_13:
	हाल RTL_VER_15:
	शेष:
		अवरोध;
	पूर्ण

	fw_offset = __le16_to_cpu(phy->fw_offset);
	length = __le32_to_cpu(phy->blk_hdr.length);
	अगर (fw_offset < माप(*phy) || length <= fw_offset) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid fw_offset\n");
		जाओ out;
	पूर्ण

	length -= fw_offset;
	अगर (length & 3) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid block length\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(phy->fw_reg) != 0x9A00) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid register to load firmware\n");
		जाओ out;
	पूर्ण

	rc = true;
out:
	वापस rc;
पूर्ण

अटल bool rtl8152_is_fw_phy_ver_ok(काष्ठा r8152 *tp, काष्ठा fw_phy_ver *ver)
अणु
	bool rc = false;

	चयन (tp->version) अणु
	हाल RTL_VER_10:
	हाल RTL_VER_11:
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	अगर (__le32_to_cpu(ver->blk_hdr.length) != माप(*ver)) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid block length\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(ver->ver.addr) != SRAM_GPHY_FW_VER) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid phy ver addr\n");
		जाओ out;
	पूर्ण

	rc = true;
out:
	वापस rc;
पूर्ण

अटल bool rtl8152_is_fw_phy_fixup_ok(काष्ठा r8152 *tp, काष्ठा fw_phy_fixup *fix)
अणु
	bool rc = false;

	चयन (tp->version) अणु
	हाल RTL_VER_10:
	हाल RTL_VER_11:
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	अगर (__le32_to_cpu(fix->blk_hdr.length) != माप(*fix)) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid block length\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(fix->setting.addr) != OCP_PHY_PATCH_CMD ||
	    __le16_to_cpu(fix->setting.data) != BIT(7)) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid phy fixup\n");
		जाओ out;
	पूर्ण

	rc = true;
out:
	वापस rc;
पूर्ण

अटल bool rtl8152_is_fw_phy_जोड़_ok(काष्ठा r8152 *tp, काष्ठा fw_phy_जोड़ *phy)
अणु
	u16 fw_offset;
	u32 length;
	bool rc = false;

	चयन (tp->version) अणु
	हाल RTL_VER_10:
	हाल RTL_VER_11:
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	fw_offset = __le16_to_cpu(phy->fw_offset);
	length = __le32_to_cpu(phy->blk_hdr.length);
	अगर (fw_offset < माप(*phy) || length <= fw_offset) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid fw_offset\n");
		जाओ out;
	पूर्ण

	length -= fw_offset;
	अगर (length & 1) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid block length\n");
		जाओ out;
	पूर्ण

	अगर (phy->pre_num > 2) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid pre_num %d\n", phy->pre_num);
		जाओ out;
	पूर्ण

	अगर (phy->bp_num > 8) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid bp_num %d\n", phy->bp_num);
		जाओ out;
	पूर्ण

	rc = true;
out:
	वापस rc;
पूर्ण

अटल bool rtl8152_is_fw_phy_nc_ok(काष्ठा r8152 *tp, काष्ठा fw_phy_nc *phy)
अणु
	u32 length;
	u16 fw_offset, fw_reg, ba_reg, patch_en_addr, mode_reg, bp_start;
	bool rc = false;

	चयन (tp->version) अणु
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
		fw_reg = 0xa014;
		ba_reg = 0xa012;
		patch_en_addr = 0xa01a;
		mode_reg = 0xb820;
		bp_start = 0xa000;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	fw_offset = __le16_to_cpu(phy->fw_offset);
	अगर (fw_offset < माप(*phy)) अणु
		dev_err(&tp->पूर्णांकf->dev, "fw_offset too small\n");
		जाओ out;
	पूर्ण

	length = __le32_to_cpu(phy->blk_hdr.length);
	अगर (length < fw_offset) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid fw_offset\n");
		जाओ out;
	पूर्ण

	length -= __le16_to_cpu(phy->fw_offset);
	अगर (!length || (length & 1)) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid block length\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(phy->fw_reg) != fw_reg) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid register to load firmware\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(phy->ba_reg) != ba_reg) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid base address register\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(phy->patch_en_addr) != patch_en_addr) अणु
		dev_err(&tp->पूर्णांकf->dev,
			"invalid patch mode enabled register\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(phy->mode_reg) != mode_reg) अणु
		dev_err(&tp->पूर्णांकf->dev,
			"invalid register to switch the mode\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(phy->bp_start) != bp_start) अणु
		dev_err(&tp->पूर्णांकf->dev,
			"invalid start register of break point\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(phy->bp_num) > 4) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid break point number\n");
		जाओ out;
	पूर्ण

	rc = true;
out:
	वापस rc;
पूर्ण

अटल bool rtl8152_is_fw_mac_ok(काष्ठा r8152 *tp, काष्ठा fw_mac *mac)
अणु
	u16 fw_reg, bp_ba_addr, bp_en_addr, bp_start, fw_offset;
	bool rc = false;
	u32 length, type;
	पूर्णांक i, max_bp;

	type = __le32_to_cpu(mac->blk_hdr.type);
	अगर (type == RTL_FW_PLA) अणु
		चयन (tp->version) अणु
		हाल RTL_VER_01:
		हाल RTL_VER_02:
		हाल RTL_VER_07:
			fw_reg = 0xf800;
			bp_ba_addr = PLA_BP_BA;
			bp_en_addr = 0;
			bp_start = PLA_BP_0;
			max_bp = 8;
			अवरोध;
		हाल RTL_VER_03:
		हाल RTL_VER_04:
		हाल RTL_VER_05:
		हाल RTL_VER_06:
		हाल RTL_VER_08:
		हाल RTL_VER_09:
		हाल RTL_VER_11:
		हाल RTL_VER_12:
		हाल RTL_VER_13:
		हाल RTL_VER_14:
		हाल RTL_VER_15:
			fw_reg = 0xf800;
			bp_ba_addr = PLA_BP_BA;
			bp_en_addr = PLA_BP_EN;
			bp_start = PLA_BP_0;
			max_bp = 8;
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (type == RTL_FW_USB) अणु
		चयन (tp->version) अणु
		हाल RTL_VER_03:
		हाल RTL_VER_04:
		हाल RTL_VER_05:
		हाल RTL_VER_06:
			fw_reg = 0xf800;
			bp_ba_addr = USB_BP_BA;
			bp_en_addr = USB_BP_EN;
			bp_start = USB_BP_0;
			max_bp = 8;
			अवरोध;
		हाल RTL_VER_08:
		हाल RTL_VER_09:
		हाल RTL_VER_11:
		हाल RTL_VER_12:
		हाल RTL_VER_13:
		हाल RTL_VER_14:
		हाल RTL_VER_15:
			fw_reg = 0xe600;
			bp_ba_addr = USB_BP_BA;
			bp_en_addr = USB_BP2_EN;
			bp_start = USB_BP_0;
			max_bp = 16;
			अवरोध;
		हाल RTL_VER_01:
		हाल RTL_VER_02:
		हाल RTL_VER_07:
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण

	fw_offset = __le16_to_cpu(mac->fw_offset);
	अगर (fw_offset < माप(*mac)) अणु
		dev_err(&tp->पूर्णांकf->dev, "fw_offset too small\n");
		जाओ out;
	पूर्ण

	length = __le32_to_cpu(mac->blk_hdr.length);
	अगर (length < fw_offset) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid fw_offset\n");
		जाओ out;
	पूर्ण

	length -= fw_offset;
	अगर (length < 4 || (length & 3)) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid block length\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(mac->fw_reg) != fw_reg) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid register to load firmware\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(mac->bp_ba_addr) != bp_ba_addr) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid base address register\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(mac->bp_en_addr) != bp_en_addr) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid enabled mask register\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(mac->bp_start) != bp_start) अणु
		dev_err(&tp->पूर्णांकf->dev,
			"invalid start register of break point\n");
		जाओ out;
	पूर्ण

	अगर (__le16_to_cpu(mac->bp_num) > max_bp) अणु
		dev_err(&tp->पूर्णांकf->dev, "invalid break point number\n");
		जाओ out;
	पूर्ण

	क्रम (i = __le16_to_cpu(mac->bp_num); i < max_bp; i++) अणु
		अगर (mac->bp[i]) अणु
			dev_err(&tp->पूर्णांकf->dev, "unused bp%u is not zero\n", i);
			जाओ out;
		पूर्ण
	पूर्ण

	rc = true;
out:
	वापस rc;
पूर्ण

/* Verअगरy the checksum क्रम the firmware file. It is calculated from the version
 * field to the end of the file. Compare the result with the checksum field to
 * make sure the file is correct.
 */
अटल दीर्घ rtl8152_fw_verअगरy_checksum(काष्ठा r8152 *tp,
				       काष्ठा fw_header *fw_hdr, माप_प्रकार size)
अणु
	अचिन्हित अक्षर checksum[माप(fw_hdr->checksum)];
	काष्ठा crypto_shash *alg;
	काष्ठा shash_desc *sdesc;
	माप_प्रकार len;
	दीर्घ rc;

	alg = crypto_alloc_shash("sha256", 0, 0);
	अगर (IS_ERR(alg)) अणु
		rc = PTR_ERR(alg);
		जाओ out;
	पूर्ण

	अगर (crypto_shash_digestsize(alg) != माप(fw_hdr->checksum)) अणु
		rc = -EFAULT;
		dev_err(&tp->पूर्णांकf->dev, "digestsize incorrect (%u)\n",
			crypto_shash_digestsize(alg));
		जाओ मुक्त_shash;
	पूर्ण

	len = माप(*sdesc) + crypto_shash_descsize(alg);
	sdesc = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!sdesc) अणु
		rc = -ENOMEM;
		जाओ मुक्त_shash;
	पूर्ण
	sdesc->tfm = alg;

	len = size - माप(fw_hdr->checksum);
	rc = crypto_shash_digest(sdesc, fw_hdr->version, len, checksum);
	kमुक्त(sdesc);
	अगर (rc)
		जाओ मुक्त_shash;

	अगर (स_भेद(fw_hdr->checksum, checksum, माप(fw_hdr->checksum))) अणु
		dev_err(&tp->पूर्णांकf->dev, "checksum fail\n");
		rc = -EFAULT;
	पूर्ण

मुक्त_shash:
	crypto_मुक्त_shash(alg);
out:
	वापस rc;
पूर्ण

अटल दीर्घ rtl8152_check_firmware(काष्ठा r8152 *tp, काष्ठा rtl_fw *rtl_fw)
अणु
	स्थिर काष्ठा firmware *fw = rtl_fw->fw;
	काष्ठा fw_header *fw_hdr = (काष्ठा fw_header *)fw->data;
	अचिन्हित दीर्घ fw_flags = 0;
	दीर्घ ret = -EFAULT;
	पूर्णांक i;

	अगर (fw->size < माप(*fw_hdr)) अणु
		dev_err(&tp->पूर्णांकf->dev, "file too small\n");
		जाओ fail;
	पूर्ण

	ret = rtl8152_fw_verअगरy_checksum(tp, fw_hdr, fw->size);
	अगर (ret)
		जाओ fail;

	ret = -EFAULT;

	क्रम (i = माप(*fw_hdr); i < fw->size;) अणु
		काष्ठा fw_block *block = (काष्ठा fw_block *)&fw->data[i];
		u32 type;

		अगर ((i + माप(*block)) > fw->size)
			जाओ fail;

		type = __le32_to_cpu(block->type);
		चयन (type) अणु
		हाल RTL_FW_END:
			अगर (__le32_to_cpu(block->length) != माप(*block))
				जाओ fail;
			जाओ fw_end;
		हाल RTL_FW_PLA:
			अगर (test_bit(FW_FLAGS_PLA, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"multiple PLA firmware encountered");
				जाओ fail;
			पूर्ण

			अगर (!rtl8152_is_fw_mac_ok(tp, (काष्ठा fw_mac *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"check PLA firmware failed\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_PLA, &fw_flags);
			अवरोध;
		हाल RTL_FW_USB:
			अगर (test_bit(FW_FLAGS_USB, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"multiple USB firmware encountered");
				जाओ fail;
			पूर्ण

			अगर (!rtl8152_is_fw_mac_ok(tp, (काष्ठा fw_mac *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"check USB firmware failed\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_USB, &fw_flags);
			अवरोध;
		हाल RTL_FW_PHY_START:
			अगर (test_bit(FW_FLAGS_START, &fw_flags) ||
			    test_bit(FW_FLAGS_NC, &fw_flags) ||
			    test_bit(FW_FLAGS_NC1, &fw_flags) ||
			    test_bit(FW_FLAGS_NC2, &fw_flags) ||
			    test_bit(FW_FLAGS_UC2, &fw_flags) ||
			    test_bit(FW_FLAGS_UC, &fw_flags) ||
			    test_bit(FW_FLAGS_STOP, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"check PHY_START fail\n");
				जाओ fail;
			पूर्ण

			अगर (__le32_to_cpu(block->length) != माप(काष्ठा fw_phy_patch_key)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"Invalid length for PHY_START\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_START, &fw_flags);
			अवरोध;
		हाल RTL_FW_PHY_STOP:
			अगर (test_bit(FW_FLAGS_STOP, &fw_flags) ||
			    !test_bit(FW_FLAGS_START, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"Check PHY_STOP fail\n");
				जाओ fail;
			पूर्ण

			अगर (__le32_to_cpu(block->length) != माप(*block)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"Invalid length for PHY_STOP\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_STOP, &fw_flags);
			अवरोध;
		हाल RTL_FW_PHY_NC:
			अगर (!test_bit(FW_FLAGS_START, &fw_flags) ||
			    test_bit(FW_FLAGS_STOP, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"check PHY_NC fail\n");
				जाओ fail;
			पूर्ण

			अगर (test_bit(FW_FLAGS_NC, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"multiple PHY NC encountered\n");
				जाओ fail;
			पूर्ण

			अगर (!rtl8152_is_fw_phy_nc_ok(tp, (काष्ठा fw_phy_nc *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev,
					"check PHY NC firmware failed\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_NC, &fw_flags);
			अवरोध;
		हाल RTL_FW_PHY_UNION_NC:
			अगर (!test_bit(FW_FLAGS_START, &fw_flags) ||
			    test_bit(FW_FLAGS_NC1, &fw_flags) ||
			    test_bit(FW_FLAGS_NC2, &fw_flags) ||
			    test_bit(FW_FLAGS_UC2, &fw_flags) ||
			    test_bit(FW_FLAGS_UC, &fw_flags) ||
			    test_bit(FW_FLAGS_STOP, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "PHY_UNION_NC out of order\n");
				जाओ fail;
			पूर्ण

			अगर (test_bit(FW_FLAGS_NC, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "multiple PHY_UNION_NC encountered\n");
				जाओ fail;
			पूर्ण

			अगर (!rtl8152_is_fw_phy_जोड़_ok(tp, (काष्ठा fw_phy_जोड़ *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev, "check PHY_UNION_NC failed\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_NC, &fw_flags);
			अवरोध;
		हाल RTL_FW_PHY_UNION_NC1:
			अगर (!test_bit(FW_FLAGS_START, &fw_flags) ||
			    test_bit(FW_FLAGS_NC2, &fw_flags) ||
			    test_bit(FW_FLAGS_UC2, &fw_flags) ||
			    test_bit(FW_FLAGS_UC, &fw_flags) ||
			    test_bit(FW_FLAGS_STOP, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "PHY_UNION_NC1 out of order\n");
				जाओ fail;
			पूर्ण

			अगर (test_bit(FW_FLAGS_NC1, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "multiple PHY NC1 encountered\n");
				जाओ fail;
			पूर्ण

			अगर (!rtl8152_is_fw_phy_जोड़_ok(tp, (काष्ठा fw_phy_जोड़ *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev, "check PHY_UNION_NC1 failed\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_NC1, &fw_flags);
			अवरोध;
		हाल RTL_FW_PHY_UNION_NC2:
			अगर (!test_bit(FW_FLAGS_START, &fw_flags) ||
			    test_bit(FW_FLAGS_UC2, &fw_flags) ||
			    test_bit(FW_FLAGS_UC, &fw_flags) ||
			    test_bit(FW_FLAGS_STOP, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "PHY_UNION_NC2 out of order\n");
				जाओ fail;
			पूर्ण

			अगर (test_bit(FW_FLAGS_NC2, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "multiple PHY NC2 encountered\n");
				जाओ fail;
			पूर्ण

			अगर (!rtl8152_is_fw_phy_जोड़_ok(tp, (काष्ठा fw_phy_जोड़ *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev, "check PHY_UNION_NC2 failed\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_NC2, &fw_flags);
			अवरोध;
		हाल RTL_FW_PHY_UNION_UC2:
			अगर (!test_bit(FW_FLAGS_START, &fw_flags) ||
			    test_bit(FW_FLAGS_UC, &fw_flags) ||
			    test_bit(FW_FLAGS_STOP, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "PHY_UNION_UC2 out of order\n");
				जाओ fail;
			पूर्ण

			अगर (test_bit(FW_FLAGS_UC2, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "multiple PHY UC2 encountered\n");
				जाओ fail;
			पूर्ण

			अगर (!rtl8152_is_fw_phy_जोड़_ok(tp, (काष्ठा fw_phy_जोड़ *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev, "check PHY_UNION_UC2 failed\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_UC2, &fw_flags);
			अवरोध;
		हाल RTL_FW_PHY_UNION_UC:
			अगर (!test_bit(FW_FLAGS_START, &fw_flags) ||
			    test_bit(FW_FLAGS_STOP, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "PHY_UNION_UC out of order\n");
				जाओ fail;
			पूर्ण

			अगर (test_bit(FW_FLAGS_UC, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "multiple PHY UC encountered\n");
				जाओ fail;
			पूर्ण

			अगर (!rtl8152_is_fw_phy_जोड़_ok(tp, (काष्ठा fw_phy_जोड़ *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev, "check PHY_UNION_UC failed\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_UC, &fw_flags);
			अवरोध;
		हाल RTL_FW_PHY_UNION_MISC:
			अगर (!rtl8152_is_fw_phy_जोड़_ok(tp, (काष्ठा fw_phy_जोड़ *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev, "check RTL_FW_PHY_UNION_MISC failed\n");
				जाओ fail;
			पूर्ण
			अवरोध;
		हाल RTL_FW_PHY_FIXUP:
			अगर (!rtl8152_is_fw_phy_fixup_ok(tp, (काष्ठा fw_phy_fixup *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev, "check PHY fixup failed\n");
				जाओ fail;
			पूर्ण
			अवरोध;
		हाल RTL_FW_PHY_SPEED_UP:
			अगर (test_bit(FW_FLAGS_SPEED_UP, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "multiple PHY firmware encountered");
				जाओ fail;
			पूर्ण

			अगर (!rtl8152_is_fw_phy_speed_up_ok(tp, (काष्ठा fw_phy_speed_up *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev, "check PHY speed up failed\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_SPEED_UP, &fw_flags);
			अवरोध;
		हाल RTL_FW_PHY_VER:
			अगर (test_bit(FW_FLAGS_START, &fw_flags) ||
			    test_bit(FW_FLAGS_NC, &fw_flags) ||
			    test_bit(FW_FLAGS_NC1, &fw_flags) ||
			    test_bit(FW_FLAGS_NC2, &fw_flags) ||
			    test_bit(FW_FLAGS_UC2, &fw_flags) ||
			    test_bit(FW_FLAGS_UC, &fw_flags) ||
			    test_bit(FW_FLAGS_STOP, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "Invalid order to set PHY version\n");
				जाओ fail;
			पूर्ण

			अगर (test_bit(FW_FLAGS_VER, &fw_flags)) अणु
				dev_err(&tp->पूर्णांकf->dev, "multiple PHY version encountered");
				जाओ fail;
			पूर्ण

			अगर (!rtl8152_is_fw_phy_ver_ok(tp, (काष्ठा fw_phy_ver *)block)) अणु
				dev_err(&tp->पूर्णांकf->dev, "check PHY version failed\n");
				जाओ fail;
			पूर्ण
			__set_bit(FW_FLAGS_VER, &fw_flags);
			अवरोध;
		शेष:
			dev_warn(&tp->पूर्णांकf->dev, "Unknown type %u is found\n",
				 type);
			अवरोध;
		पूर्ण

		/* next block */
		i += ALIGN(__le32_to_cpu(block->length), 8);
	पूर्ण

fw_end:
	अगर (test_bit(FW_FLAGS_START, &fw_flags) && !test_bit(FW_FLAGS_STOP, &fw_flags)) अणु
		dev_err(&tp->पूर्णांकf->dev, "without PHY_STOP\n");
		जाओ fail;
	पूर्ण

	वापस 0;
fail:
	वापस ret;
पूर्ण

अटल व्योम rtl_ram_code_speed_up(काष्ठा r8152 *tp, काष्ठा fw_phy_speed_up *phy, bool रुको)
अणु
	u32 len;
	u8 *data;

	अगर (sram_पढ़ो(tp, SRAM_GPHY_FW_VER) >= __le16_to_cpu(phy->version)) अणु
		dev_dbg(&tp->पूर्णांकf->dev, "PHY firmware has been the newest\n");
		वापस;
	पूर्ण

	len = __le32_to_cpu(phy->blk_hdr.length);
	len -= __le16_to_cpu(phy->fw_offset);
	data = (u8 *)phy + __le16_to_cpu(phy->fw_offset);

	अगर (rtl_phy_patch_request(tp, true, रुको))
		वापस;

	जबतक (len) अणु
		u32 ocp_data, size;
		पूर्णांक i;

		अगर (len < 2048)
			size = len;
		अन्यथा
			size = 2048;

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_GPHY_CTRL);
		ocp_data |= GPHY_PATCH_DONE | BACKUP_RESTRORE;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_GPHY_CTRL, ocp_data);

		generic_ocp_ग_लिखो(tp, __le16_to_cpu(phy->fw_reg), 0xff, size, data, MCU_TYPE_USB);

		data += size;
		len -= size;

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_POL_GPIO_CTRL);
		ocp_data |= POL_GPHY_PATCH;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_POL_GPIO_CTRL, ocp_data);

		क्रम (i = 0; i < 1000; i++) अणु
			अगर (!(ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_POL_GPIO_CTRL) & POL_GPHY_PATCH))
				अवरोध;
		पूर्ण

		अगर (i == 1000) अणु
			dev_err(&tp->पूर्णांकf->dev, "ram code speedup mode timeout\n");
			अवरोध;
		पूर्ण
	पूर्ण

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, tp->ocp_base);
	rtl_phy_patch_request(tp, false, रुको);

	अगर (sram_पढ़ो(tp, SRAM_GPHY_FW_VER) == __le16_to_cpu(phy->version))
		dev_dbg(&tp->पूर्णांकf->dev, "successfully applied %s\n", phy->info);
	अन्यथा
		dev_err(&tp->पूर्णांकf->dev, "ram code speedup mode fail\n");
पूर्ण

अटल पूर्णांक rtl8152_fw_phy_ver(काष्ठा r8152 *tp, काष्ठा fw_phy_ver *phy_ver)
अणु
	u16 ver_addr, ver;

	ver_addr = __le16_to_cpu(phy_ver->ver.addr);
	ver = __le16_to_cpu(phy_ver->ver.data);

	अगर (sram_पढ़ो(tp, ver_addr) >= ver) अणु
		dev_dbg(&tp->पूर्णांकf->dev, "PHY firmware has been the newest\n");
		वापस 0;
	पूर्ण

	sram_ग_लिखो(tp, ver_addr, ver);

	dev_dbg(&tp->पूर्णांकf->dev, "PHY firmware version %x\n", ver);

	वापस ver;
पूर्ण

अटल व्योम rtl8152_fw_phy_fixup(काष्ठा r8152 *tp, काष्ठा fw_phy_fixup *fix)
अणु
	u16 addr, data;

	addr = __le16_to_cpu(fix->setting.addr);
	data = ocp_reg_पढ़ो(tp, addr);

	चयन (__le16_to_cpu(fix->bit_cmd)) अणु
	हाल FW_FIXUP_AND:
		data &= __le16_to_cpu(fix->setting.data);
		अवरोध;
	हाल FW_FIXUP_OR:
		data |= __le16_to_cpu(fix->setting.data);
		अवरोध;
	हाल FW_FIXUP_NOT:
		data &= ~__le16_to_cpu(fix->setting.data);
		अवरोध;
	हाल FW_FIXUP_XOR:
		data ^= __le16_to_cpu(fix->setting.data);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ocp_reg_ग_लिखो(tp, addr, data);

	dev_dbg(&tp->पूर्णांकf->dev, "applied ocp %x %x\n", addr, data);
पूर्ण

अटल व्योम rtl8152_fw_phy_जोड़_apply(काष्ठा r8152 *tp, काष्ठा fw_phy_जोड़ *phy)
अणु
	__le16 *data;
	u32 length;
	पूर्णांक i, num;

	num = phy->pre_num;
	क्रम (i = 0; i < num; i++)
		sram_ग_लिखो(tp, __le16_to_cpu(phy->pre_set[i].addr),
			   __le16_to_cpu(phy->pre_set[i].data));

	length = __le32_to_cpu(phy->blk_hdr.length);
	length -= __le16_to_cpu(phy->fw_offset);
	num = length / 2;
	data = (__le16 *)((u8 *)phy + __le16_to_cpu(phy->fw_offset));

	ocp_reg_ग_लिखो(tp, OCP_SRAM_ADDR, __le16_to_cpu(phy->fw_reg));
	क्रम (i = 0; i < num; i++)
		ocp_reg_ग_लिखो(tp, OCP_SRAM_DATA, __le16_to_cpu(data[i]));

	num = phy->bp_num;
	क्रम (i = 0; i < num; i++)
		sram_ग_लिखो(tp, __le16_to_cpu(phy->bp[i].addr), __le16_to_cpu(phy->bp[i].data));

	अगर (phy->bp_num && phy->bp_en.addr)
		sram_ग_लिखो(tp, __le16_to_cpu(phy->bp_en.addr), __le16_to_cpu(phy->bp_en.data));

	dev_dbg(&tp->पूर्णांकf->dev, "successfully applied %s\n", phy->info);
पूर्ण

अटल व्योम rtl8152_fw_phy_nc_apply(काष्ठा r8152 *tp, काष्ठा fw_phy_nc *phy)
अणु
	u16 mode_reg, bp_index;
	u32 length, i, num;
	__le16 *data;

	mode_reg = __le16_to_cpu(phy->mode_reg);
	sram_ग_लिखो(tp, mode_reg, __le16_to_cpu(phy->mode_pre));
	sram_ग_लिखो(tp, __le16_to_cpu(phy->ba_reg),
		   __le16_to_cpu(phy->ba_data));

	length = __le32_to_cpu(phy->blk_hdr.length);
	length -= __le16_to_cpu(phy->fw_offset);
	num = length / 2;
	data = (__le16 *)((u8 *)phy + __le16_to_cpu(phy->fw_offset));

	ocp_reg_ग_लिखो(tp, OCP_SRAM_ADDR, __le16_to_cpu(phy->fw_reg));
	क्रम (i = 0; i < num; i++)
		ocp_reg_ग_लिखो(tp, OCP_SRAM_DATA, __le16_to_cpu(data[i]));

	sram_ग_लिखो(tp, __le16_to_cpu(phy->patch_en_addr),
		   __le16_to_cpu(phy->patch_en_value));

	bp_index = __le16_to_cpu(phy->bp_start);
	num = __le16_to_cpu(phy->bp_num);
	क्रम (i = 0; i < num; i++) अणु
		sram_ग_लिखो(tp, bp_index, __le16_to_cpu(phy->bp[i]));
		bp_index += 2;
	पूर्ण

	sram_ग_लिखो(tp, mode_reg, __le16_to_cpu(phy->mode_post));

	dev_dbg(&tp->पूर्णांकf->dev, "successfully applied %s\n", phy->info);
पूर्ण

अटल व्योम rtl8152_fw_mac_apply(काष्ठा r8152 *tp, काष्ठा fw_mac *mac)
अणु
	u16 bp_en_addr, bp_index, type, bp_num, fw_ver_reg;
	u32 length;
	u8 *data;
	पूर्णांक i;

	चयन (__le32_to_cpu(mac->blk_hdr.type)) अणु
	हाल RTL_FW_PLA:
		type = MCU_TYPE_PLA;
		अवरोध;
	हाल RTL_FW_USB:
		type = MCU_TYPE_USB;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	fw_ver_reg = __le16_to_cpu(mac->fw_ver_reg);
	अगर (fw_ver_reg && ocp_पढ़ो_byte(tp, MCU_TYPE_USB, fw_ver_reg) >= mac->fw_ver_data) अणु
		dev_dbg(&tp->पूर्णांकf->dev, "%s firmware has been the newest\n", type ? "PLA" : "USB");
		वापस;
	पूर्ण

	rtl_clear_bp(tp, type);

	/* Enable backup/restore of MACDBG. This is required after clearing PLA
	 * अवरोध poपूर्णांकs and beक्रमe applying the PLA firmware.
	 */
	अगर (tp->version == RTL_VER_04 && type == MCU_TYPE_PLA &&
	    !(ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MACDBG_POST) & DEBUG_OE)) अणु
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MACDBG_PRE, DEBUG_LTSSM);
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MACDBG_POST, DEBUG_LTSSM);
	पूर्ण

	length = __le32_to_cpu(mac->blk_hdr.length);
	length -= __le16_to_cpu(mac->fw_offset);

	data = (u8 *)mac;
	data += __le16_to_cpu(mac->fw_offset);

	generic_ocp_ग_लिखो(tp, __le16_to_cpu(mac->fw_reg), 0xff, length, data,
			  type);

	ocp_ग_लिखो_word(tp, type, __le16_to_cpu(mac->bp_ba_addr),
		       __le16_to_cpu(mac->bp_ba_value));

	bp_index = __le16_to_cpu(mac->bp_start);
	bp_num = __le16_to_cpu(mac->bp_num);
	क्रम (i = 0; i < bp_num; i++) अणु
		ocp_ग_लिखो_word(tp, type, bp_index, __le16_to_cpu(mac->bp[i]));
		bp_index += 2;
	पूर्ण

	bp_en_addr = __le16_to_cpu(mac->bp_en_addr);
	अगर (bp_en_addr)
		ocp_ग_लिखो_word(tp, type, bp_en_addr,
			       __le16_to_cpu(mac->bp_en_value));

	अगर (fw_ver_reg)
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, fw_ver_reg,
			       mac->fw_ver_data);

	dev_dbg(&tp->पूर्णांकf->dev, "successfully applied %s\n", mac->info);
पूर्ण

अटल व्योम rtl8152_apply_firmware(काष्ठा r8152 *tp, bool घातer_cut)
अणु
	काष्ठा rtl_fw *rtl_fw = &tp->rtl_fw;
	स्थिर काष्ठा firmware *fw;
	काष्ठा fw_header *fw_hdr;
	काष्ठा fw_phy_patch_key *key;
	u16 key_addr = 0;
	पूर्णांक i, patch_phy = 1;

	अगर (IS_ERR_OR_शून्य(rtl_fw->fw))
		वापस;

	fw = rtl_fw->fw;
	fw_hdr = (काष्ठा fw_header *)fw->data;

	अगर (rtl_fw->pre_fw)
		rtl_fw->pre_fw(tp);

	क्रम (i = दुरत्व(काष्ठा fw_header, blocks); i < fw->size;) अणु
		काष्ठा fw_block *block = (काष्ठा fw_block *)&fw->data[i];

		चयन (__le32_to_cpu(block->type)) अणु
		हाल RTL_FW_END:
			जाओ post_fw;
		हाल RTL_FW_PLA:
		हाल RTL_FW_USB:
			rtl8152_fw_mac_apply(tp, (काष्ठा fw_mac *)block);
			अवरोध;
		हाल RTL_FW_PHY_START:
			अगर (!patch_phy)
				अवरोध;
			key = (काष्ठा fw_phy_patch_key *)block;
			key_addr = __le16_to_cpu(key->key_reg);
			rtl_pre_ram_code(tp, key_addr, __le16_to_cpu(key->key_data), !घातer_cut);
			अवरोध;
		हाल RTL_FW_PHY_STOP:
			अगर (!patch_phy)
				अवरोध;
			WARN_ON(!key_addr);
			rtl_post_ram_code(tp, key_addr, !घातer_cut);
			अवरोध;
		हाल RTL_FW_PHY_NC:
			rtl8152_fw_phy_nc_apply(tp, (काष्ठा fw_phy_nc *)block);
			अवरोध;
		हाल RTL_FW_PHY_VER:
			patch_phy = rtl8152_fw_phy_ver(tp, (काष्ठा fw_phy_ver *)block);
			अवरोध;
		हाल RTL_FW_PHY_UNION_NC:
		हाल RTL_FW_PHY_UNION_NC1:
		हाल RTL_FW_PHY_UNION_NC2:
		हाल RTL_FW_PHY_UNION_UC2:
		हाल RTL_FW_PHY_UNION_UC:
		हाल RTL_FW_PHY_UNION_MISC:
			अगर (patch_phy)
				rtl8152_fw_phy_जोड़_apply(tp, (काष्ठा fw_phy_जोड़ *)block);
			अवरोध;
		हाल RTL_FW_PHY_FIXUP:
			अगर (patch_phy)
				rtl8152_fw_phy_fixup(tp, (काष्ठा fw_phy_fixup *)block);
			अवरोध;
		हाल RTL_FW_PHY_SPEED_UP:
			rtl_ram_code_speed_up(tp, (काष्ठा fw_phy_speed_up *)block, !घातer_cut);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		i += ALIGN(__le32_to_cpu(block->length), 8);
	पूर्ण

post_fw:
	अगर (rtl_fw->post_fw)
		rtl_fw->post_fw(tp);

	strscpy(rtl_fw->version, fw_hdr->version, RTL_VER_SIZE);
	dev_info(&tp->पूर्णांकf->dev, "load %s successfully\n", rtl_fw->version);
पूर्ण

अटल व्योम rtl8152_release_firmware(काष्ठा r8152 *tp)
अणु
	काष्ठा rtl_fw *rtl_fw = &tp->rtl_fw;

	अगर (!IS_ERR_OR_शून्य(rtl_fw->fw)) अणु
		release_firmware(rtl_fw->fw);
		rtl_fw->fw = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8152_request_firmware(काष्ठा r8152 *tp)
अणु
	काष्ठा rtl_fw *rtl_fw = &tp->rtl_fw;
	दीर्घ rc;

	अगर (rtl_fw->fw || !rtl_fw->fw_name) अणु
		dev_info(&tp->पूर्णांकf->dev, "skip request firmware\n");
		rc = 0;
		जाओ result;
	पूर्ण

	rc = request_firmware(&rtl_fw->fw, rtl_fw->fw_name, &tp->पूर्णांकf->dev);
	अगर (rc < 0)
		जाओ result;

	rc = rtl8152_check_firmware(tp, rtl_fw);
	अगर (rc < 0)
		release_firmware(rtl_fw->fw);

result:
	अगर (rc) अणु
		rtl_fw->fw = ERR_PTR(rc);

		dev_warn(&tp->पूर्णांकf->dev,
			 "unable to load firmware patch %s (%ld)\n",
			 rtl_fw->fw_name, rc);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम r8152_aldps_en(काष्ठा r8152 *tp, bool enable)
अणु
	अगर (enable) अणु
		ocp_reg_ग_लिखो(tp, OCP_ALDPS_CONFIG, ENPWRSAVE | ENPDNPS |
						    LINKENA | DIS_SDSAVE);
	पूर्ण अन्यथा अणु
		ocp_reg_ग_लिखो(tp, OCP_ALDPS_CONFIG, ENPDNPS | LINKENA |
						    DIS_SDSAVE);
		msleep(20);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम r8152_mmd_indirect(काष्ठा r8152 *tp, u16 dev, u16 reg)
अणु
	ocp_reg_ग_लिखो(tp, OCP_EEE_AR, FUN_ADDR | dev);
	ocp_reg_ग_लिखो(tp, OCP_EEE_DATA, reg);
	ocp_reg_ग_लिखो(tp, OCP_EEE_AR, FUN_DATA | dev);
पूर्ण

अटल u16 r8152_mmd_पढ़ो(काष्ठा r8152 *tp, u16 dev, u16 reg)
अणु
	u16 data;

	r8152_mmd_indirect(tp, dev, reg);
	data = ocp_reg_पढ़ो(tp, OCP_EEE_DATA);
	ocp_reg_ग_लिखो(tp, OCP_EEE_AR, 0x0000);

	वापस data;
पूर्ण

अटल व्योम r8152_mmd_ग_लिखो(काष्ठा r8152 *tp, u16 dev, u16 reg, u16 data)
अणु
	r8152_mmd_indirect(tp, dev, reg);
	ocp_reg_ग_लिखो(tp, OCP_EEE_DATA, data);
	ocp_reg_ग_लिखो(tp, OCP_EEE_AR, 0x0000);
पूर्ण

अटल व्योम r8152_eee_en(काष्ठा r8152 *tp, bool enable)
अणु
	u16 config1, config2, config3;
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EEE_CR);
	config1 = ocp_reg_पढ़ो(tp, OCP_EEE_CONFIG1) & ~sd_rise_समय_mask;
	config2 = ocp_reg_पढ़ो(tp, OCP_EEE_CONFIG2);
	config3 = ocp_reg_पढ़ो(tp, OCP_EEE_CONFIG3) & ~fast_snr_mask;

	अगर (enable) अणु
		ocp_data |= EEE_RX_EN | EEE_TX_EN;
		config1 |= EEE_10_CAP | EEE_NWAY_EN | TX_QUIET_EN | RX_QUIET_EN;
		config1 |= sd_rise_समय(1);
		config2 |= RG_DACQUIET_EN | RG_LDVQUIET_EN;
		config3 |= fast_snr(42);
	पूर्ण अन्यथा अणु
		ocp_data &= ~(EEE_RX_EN | EEE_TX_EN);
		config1 &= ~(EEE_10_CAP | EEE_NWAY_EN | TX_QUIET_EN |
			     RX_QUIET_EN);
		config1 |= sd_rise_समय(7);
		config2 &= ~(RG_DACQUIET_EN | RG_LDVQUIET_EN);
		config3 |= fast_snr(511);
	पूर्ण

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EEE_CR, ocp_data);
	ocp_reg_ग_लिखो(tp, OCP_EEE_CONFIG1, config1);
	ocp_reg_ग_लिखो(tp, OCP_EEE_CONFIG2, config2);
	ocp_reg_ग_लिखो(tp, OCP_EEE_CONFIG3, config3);
पूर्ण

अटल व्योम r8153_eee_en(काष्ठा r8152 *tp, bool enable)
अणु
	u32 ocp_data;
	u16 config;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EEE_CR);
	config = ocp_reg_पढ़ो(tp, OCP_EEE_CFG);

	अगर (enable) अणु
		ocp_data |= EEE_RX_EN | EEE_TX_EN;
		config |= EEE10_EN;
	पूर्ण अन्यथा अणु
		ocp_data &= ~(EEE_RX_EN | EEE_TX_EN);
		config &= ~EEE10_EN;
	पूर्ण

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EEE_CR, ocp_data);
	ocp_reg_ग_लिखो(tp, OCP_EEE_CFG, config);

	tp->ups_info.eee = enable;
पूर्ण

अटल व्योम r8156_eee_en(काष्ठा r8152 *tp, bool enable)
अणु
	u16 config;

	r8153_eee_en(tp, enable);

	config = ocp_reg_पढ़ो(tp, OCP_EEE_ADV2);

	अगर (enable)
		config |= MDIO_EEE_2_5GT;
	अन्यथा
		config &= ~MDIO_EEE_2_5GT;

	ocp_reg_ग_लिखो(tp, OCP_EEE_ADV2, config);
पूर्ण

अटल व्योम rtl_eee_enable(काष्ठा r8152 *tp, bool enable)
अणु
	चयन (tp->version) अणु
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_07:
		अगर (enable) अणु
			r8152_eee_en(tp, true);
			r8152_mmd_ग_लिखो(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV,
					tp->eee_adv);
		पूर्ण अन्यथा अणु
			r8152_eee_en(tp, false);
			r8152_mmd_ग_लिखो(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV, 0);
		पूर्ण
		अवरोध;
	हाल RTL_VER_03:
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
	हाल RTL_VER_08:
	हाल RTL_VER_09:
	हाल RTL_VER_14:
		अगर (enable) अणु
			r8153_eee_en(tp, true);
			ocp_reg_ग_लिखो(tp, OCP_EEE_ADV, tp->eee_adv);
		पूर्ण अन्यथा अणु
			r8153_eee_en(tp, false);
			ocp_reg_ग_लिखो(tp, OCP_EEE_ADV, 0);
		पूर्ण
		अवरोध;
	हाल RTL_VER_10:
	हाल RTL_VER_11:
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		अगर (enable) अणु
			r8156_eee_en(tp, true);
			ocp_reg_ग_लिखो(tp, OCP_EEE_ADV, tp->eee_adv);
		पूर्ण अन्यथा अणु
			r8156_eee_en(tp, false);
			ocp_reg_ग_लिखो(tp, OCP_EEE_ADV, 0);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम r8152b_enable_fc(काष्ठा r8152 *tp)
अणु
	u16 anar;

	anar = r8152_mdio_पढ़ो(tp, MII_ADVERTISE);
	anar |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
	r8152_mdio_ग_लिखो(tp, MII_ADVERTISE, anar);

	tp->ups_info.flow_control = true;
पूर्ण

अटल व्योम rtl8152_disable(काष्ठा r8152 *tp)
अणु
	r8152_aldps_en(tp, false);
	rtl_disable(tp);
	r8152_aldps_en(tp, true);
पूर्ण

अटल व्योम r8152b_hw_phy_cfg(काष्ठा r8152 *tp)
अणु
	rtl8152_apply_firmware(tp, false);
	rtl_eee_enable(tp, tp->eee_en);
	r8152_aldps_en(tp, true);
	r8152b_enable_fc(tp);

	set_bit(PHY_RESET, &tp->flags);
पूर्ण

अटल व्योम रुको_oob_link_list_पढ़ोy(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	पूर्णांक i;

	क्रम (i = 0; i < 1000; i++) अणु
		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		अगर (ocp_data & LINK_LIST_READY)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
पूर्ण

अटल व्योम r8156b_रुको_loading_flash(काष्ठा r8152 *tp)
अणु
	अगर ((ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_GPHY_CTRL) & GPHY_FLASH) &&
	    !(ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_GPHY_CTRL) & BYPASS_FLASH)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 100; i++) अणु
			अगर (ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_GPHY_CTRL) & GPHY_PATCH_DONE)
				अवरोध;
			usleep_range(1000, 2000);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम r8152b_निकास_oob(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rxdy_gated_en(tp, true);
	r8153_tereकरो_off(tp);
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CR, 0x00);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	रुको_oob_link_list_पढ़ोy(tp);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	रुको_oob_link_list_पढ़ोy(tp);

	rtl8152_nic_reset(tp);

	/* rx share fअगरo credit full threshold */
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_NORMAL);

	अगर (tp->udev->speed == USB_SPEED_FULL ||
	    tp->udev->speed == USB_SPEED_LOW) अणु
		/* rx share fअगरo credit near full threshold */
		ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1,
				RXFIFO_THR2_FULL);
		ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2,
				RXFIFO_THR3_FULL);
	पूर्ण अन्यथा अणु
		/* rx share fअगरo credit near full threshold */
		ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1,
				RXFIFO_THR2_HIGH);
		ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2,
				RXFIFO_THR3_HIGH);
	पूर्ण

	/* TX share fअगरo मुक्त credit full threshold */
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, TXFIFO_THR_NORMAL2);

	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_TX_AGG, TX_AGG_MAX_THRESHOLD);
	ocp_ग_लिखो_dword(tp, MCU_TYPE_USB, USB_RX_BUF_TH, RX_THR_HIGH);
	ocp_ग_लिखो_dword(tp, MCU_TYPE_USB, USB_TX_DMA,
			TEST_MODE_DISABLE | TX_SIZE_ADJUST1);

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RMS, RTL8152_RMS);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_TCR0);
	ocp_data |= TCR0_AUTO_FIFO;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TCR0, ocp_data);
पूर्ण

अटल व्योम r8152b_enter_oob(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_OOB);
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1, RXFIFO_THR2_OOB);
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2, RXFIFO_THR3_OOB);

	rtl_disable(tp);

	रुको_oob_link_list_पढ़ोy(tp);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	रुको_oob_link_list_पढ़ोy(tp);

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RMS, RTL8152_RMS);

	rtl_rx_vlan_en(tp, true);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BDC_CR);
	ocp_data |= ALDPS_PROXY_MODE;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_BDC_CR, ocp_data);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data |= NOW_IS_OOB | DIS_MCU_CLROOB;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rxdy_gated_en(tp, false);

	ocp_data = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data |= RCR_APM | RCR_AM | RCR_AB;
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
पूर्ण

अटल पूर्णांक r8153_pre_firmware_1(काष्ठा r8152 *tp)
अणु
	पूर्णांक i;

	/* Wait till the WTD समयr is पढ़ोy. It would take at most 104 ms. */
	क्रम (i = 0; i < 104; i++) अणु
		u32 ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_WDT1_CTRL);

		अगर (!(ocp_data & WTD1_EN))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r8153_post_firmware_1(काष्ठा r8152 *tp)
अणु
	/* set USB_BP_4 to support USB_SPEED_SUPER only */
	अगर (ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_CSTMR) & FORCE_SUPER)
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BP_4, BP4_SUPER_ONLY);

	/* reset UPHY समयr to 36 ms */
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_UPHY_TIMER, 36000 / 16);

	वापस 0;
पूर्ण

अटल पूर्णांक r8153_pre_firmware_2(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	r8153_pre_firmware_1(tp);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN0);
	ocp_data &= ~FW_FIX_SUSPEND;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN0, ocp_data);

	वापस 0;
पूर्ण

अटल पूर्णांक r8153_post_firmware_2(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	/* enable bp0 अगर support USB_SPEED_SUPER only */
	अगर (ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_CSTMR) & FORCE_SUPER) अणु
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BP_EN);
		ocp_data |= BIT(0);
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_BP_EN, ocp_data);
	पूर्ण

	/* reset UPHY समयr to 36 ms */
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_UPHY_TIMER, 36000 / 16);

	/* enable U3P3 check, set the counter to 4 */
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, U3P3_CHECK_EN | 4);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN0);
	ocp_data |= FW_FIX_SUSPEND;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN0, ocp_data);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_USB2PHY);
	ocp_data |= USB2PHY_L1 | USB2PHY_SUSPEND;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_USB2PHY, ocp_data);

	वापस 0;
पूर्ण

अटल पूर्णांक r8153_post_firmware_3(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_USB2PHY);
	ocp_data |= USB2PHY_L1 | USB2PHY_SUSPEND;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_USB2PHY, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1);
	ocp_data |= FW_IP_RESET_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1, ocp_data);

	वापस 0;
पूर्ण

अटल पूर्णांक r8153b_pre_firmware_1(काष्ठा r8152 *tp)
अणु
	/* enable fc समयr and set समयr to 1 second. */
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FC_TIMER,
		       CTRL_TIMER_EN | (1000 / 8));

	वापस 0;
पूर्ण

अटल पूर्णांक r8153b_post_firmware_1(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	/* enable bp0 क्रम RTL8153-BND */
	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_MISC_1);
	अगर (ocp_data & BND_MASK) अणु
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BP_EN);
		ocp_data |= BIT(0);
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_BP_EN, ocp_data);
	पूर्ण

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_CTRL);
	ocp_data |= FLOW_CTRL_PATCH_OPT;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_TASK);
	ocp_data |= FC_PATCH_TASK;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1);
	ocp_data |= FW_IP_RESET_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1, ocp_data);

	वापस 0;
पूर्ण

अटल पूर्णांक r8153c_post_firmware_1(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_CTRL);
	ocp_data |= FLOW_CTRL_PATCH_2;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_TASK);
	ocp_data |= FC_PATCH_TASK;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);

	वापस 0;
पूर्ण

अटल पूर्णांक r8156a_post_firmware_1(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1);
	ocp_data |= FW_IP_RESET_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1, ocp_data);

	/* Modअगरy U3PHY parameter क्रम compatibility issue */
	ocp_ग_लिखो_dword(tp, MCU_TYPE_USB, USB_UPHY3_MDCMDIO, 0x4026840e);
	ocp_ग_लिखो_dword(tp, MCU_TYPE_USB, USB_UPHY3_MDCMDIO, 0x4001acc9);

	वापस 0;
पूर्ण

अटल व्योम r8153_aldps_en(काष्ठा r8152 *tp, bool enable)
अणु
	u16 data;

	data = ocp_reg_पढ़ो(tp, OCP_POWER_CFG);
	अगर (enable) अणु
		data |= EN_ALDPS;
		ocp_reg_ग_लिखो(tp, OCP_POWER_CFG, data);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		data &= ~EN_ALDPS;
		ocp_reg_ग_लिखो(tp, OCP_POWER_CFG, data);
		क्रम (i = 0; i < 20; i++) अणु
			usleep_range(1000, 2000);
			अगर (ocp_पढ़ो_word(tp, MCU_TYPE_PLA, 0xe000) & 0x0100)
				अवरोध;
		पूर्ण
	पूर्ण

	tp->ups_info.aldps = enable;
पूर्ण

अटल व्योम r8153_hw_phy_cfg(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 data;

	/* disable ALDPS beक्रमe updating the PHY parameters */
	r8153_aldps_en(tp, false);

	/* disable EEE beक्रमe updating the PHY parameters */
	rtl_eee_enable(tp, false);

	rtl8152_apply_firmware(tp, false);

	अगर (tp->version == RTL_VER_03) अणु
		data = ocp_reg_पढ़ो(tp, OCP_EEE_CFG);
		data &= ~CTAP_SHORT_EN;
		ocp_reg_ग_लिखो(tp, OCP_EEE_CFG, data);
	पूर्ण

	data = ocp_reg_पढ़ो(tp, OCP_POWER_CFG);
	data |= EEE_CLKDIV_EN;
	ocp_reg_ग_लिखो(tp, OCP_POWER_CFG, data);

	data = ocp_reg_पढ़ो(tp, OCP_DOWN_SPEED);
	data |= EN_10M_BGOFF;
	ocp_reg_ग_लिखो(tp, OCP_DOWN_SPEED, data);
	data = ocp_reg_पढ़ो(tp, OCP_POWER_CFG);
	data |= EN_10M_PLLOFF;
	ocp_reg_ग_लिखो(tp, OCP_POWER_CFG, data);
	sram_ग_लिखो(tp, SRAM_IMPEDANCE, 0x0b13);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= PFM_PWM_SWITCH;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);

	/* Enable LPF corner स्वतः tune */
	sram_ग_लिखो(tp, SRAM_LPF_CFG, 0xf70f);

	/* Adjust 10M Amplitude */
	sram_ग_लिखो(tp, SRAM_10M_AMP1, 0x00af);
	sram_ग_लिखो(tp, SRAM_10M_AMP2, 0x0208);

	अगर (tp->eee_en)
		rtl_eee_enable(tp, true);

	r8153_aldps_en(tp, true);
	r8152b_enable_fc(tp);

	चयन (tp->version) अणु
	हाल RTL_VER_03:
	हाल RTL_VER_04:
		अवरोध;
	हाल RTL_VER_05:
	हाल RTL_VER_06:
	शेष:
		r8153_u2p3en(tp, true);
		अवरोध;
	पूर्ण

	set_bit(PHY_RESET, &tp->flags);
पूर्ण

अटल u32 r8152_efuse_पढ़ो(काष्ठा r8152 *tp, u8 addr)
अणु
	u32 ocp_data;

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EFUSE_CMD, EFUSE_READ_CMD | addr);
	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EFUSE_CMD);
	ocp_data = (ocp_data & EFUSE_DATA_BIT16) << 9;	/* data of bit16 */
	ocp_data |= ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EFUSE_DATA);

	वापस ocp_data;
पूर्ण

अटल व्योम r8153b_hw_phy_cfg(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_MISC_0);
	अगर (ocp_data & PCUT_STATUS) अणु
		ocp_data &= ~PCUT_STATUS;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_MISC_0, ocp_data);
	पूर्ण

	/* disable ALDPS beक्रमe updating the PHY parameters */
	r8153_aldps_en(tp, false);

	/* disable EEE beक्रमe updating the PHY parameters */
	rtl_eee_enable(tp, false);

	/* U1/U2/L1 idle समयr. 500 us */
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_U1U2_TIMER, 500);

	data = r8153_phy_status(tp, 0);

	चयन (data) अणु
	हाल PHY_STAT_PWRDN:
	हाल PHY_STAT_EXT_INIT:
		rtl8152_apply_firmware(tp, true);

		data = r8152_mdio_पढ़ो(tp, MII_BMCR);
		data &= ~BMCR_PDOWN;
		r8152_mdio_ग_लिखो(tp, MII_BMCR, data);
		अवरोध;
	हाल PHY_STAT_LAN_ON:
	शेष:
		rtl8152_apply_firmware(tp, false);
		अवरोध;
	पूर्ण

	r8153b_green_en(tp, test_bit(GREEN_ETHERNET, &tp->flags));

	data = sram_पढ़ो(tp, SRAM_GREEN_CFG);
	data |= R_TUNE_EN;
	sram_ग_लिखो(tp, SRAM_GREEN_CFG, data);
	data = ocp_reg_पढ़ो(tp, OCP_NCTL_CFG);
	data |= PGA_RETURN_EN;
	ocp_reg_ग_लिखो(tp, OCP_NCTL_CFG, data);

	/* ADC Bias Calibration:
	 * पढ़ो efuse offset 0x7d to get a 17-bit data. Remove the dummy/fake
	 * bit (bit3) to rebuild the real 16-bit data. Write the data to the
	 * ADC ioffset.
	 */
	ocp_data = r8152_efuse_पढ़ो(tp, 0x7d);
	data = (u16)(((ocp_data & 0x1fff0) >> 1) | (ocp_data & 0x7));
	अगर (data != 0xffff)
		ocp_reg_ग_लिखो(tp, OCP_ADC_IOFFSET, data);

	/* ups mode tx-link-pulse timing adjusपंचांगent:
	 * rg_saw_cnt = OCP reg 0xC426 Bit[13:0]
	 * swr_cnt_1ms_ini = 16000000 / rg_saw_cnt
	 */
	ocp_data = ocp_reg_पढ़ो(tp, 0xc426);
	ocp_data &= 0x3fff;
	अगर (ocp_data) अणु
		u32 swr_cnt_1ms_ini;

		swr_cnt_1ms_ini = (16000000 / ocp_data) & SAW_CNT_1MS_MASK;
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_UPS_CFG);
		ocp_data = (ocp_data & ~SAW_CNT_1MS_MASK) | swr_cnt_1ms_ini;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_UPS_CFG, ocp_data);
	पूर्ण

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= PFM_PWM_SWITCH;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);

	/* Advnace EEE */
	अगर (!rtl_phy_patch_request(tp, true, true)) अणु
		data = ocp_reg_पढ़ो(tp, OCP_POWER_CFG);
		data |= EEE_CLKDIV_EN;
		ocp_reg_ग_लिखो(tp, OCP_POWER_CFG, data);
		tp->ups_info.eee_ckभाग = true;

		data = ocp_reg_पढ़ो(tp, OCP_DOWN_SPEED);
		data |= EN_EEE_CMODE | EN_EEE_1000 | EN_10M_CLKDIV;
		ocp_reg_ग_लिखो(tp, OCP_DOWN_SPEED, data);
		tp->ups_info.eee_cmod_lv = true;
		tp->ups_info._10m_ckभाग = true;
		tp->ups_info.eee_plloff_giga = true;

		ocp_reg_ग_लिखो(tp, OCP_SYSCLK_CFG, 0);
		ocp_reg_ग_लिखो(tp, OCP_SYSCLK_CFG, clk_भाग_expo(5));
		tp->ups_info._250m_ckभाग = true;

		rtl_phy_patch_request(tp, false, true);
	पूर्ण

	अगर (tp->eee_en)
		rtl_eee_enable(tp, true);

	r8153_aldps_en(tp, true);
	r8152b_enable_fc(tp);

	set_bit(PHY_RESET, &tp->flags);
पूर्ण

अटल व्योम r8153c_hw_phy_cfg(काष्ठा r8152 *tp)
अणु
	r8153b_hw_phy_cfg(tp);

	tp->ups_info.r_tune = true;
पूर्ण

अटल व्योम rtl8153_change_mtu(काष्ठा r8152 *tp)
अणु
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RMS, mtu_to_size(tp->netdev->mtu));
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_MTPS, MTPS_JUMBO);
पूर्ण

अटल व्योम r8153_first_init(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	rxdy_gated_en(tp, true);
	r8153_tereकरो_off(tp);

	ocp_data = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rtl8152_nic_reset(tp);
	rtl_reset_bmu(tp);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	रुको_oob_link_list_पढ़ोy(tp);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	रुको_oob_link_list_पढ़ोy(tp);

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	rtl8153_change_mtu(tp);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_TCR0);
	ocp_data |= TCR0_AUTO_FIFO;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TCR0, ocp_data);

	rtl8152_nic_reset(tp);

	/* rx share fअगरo credit full threshold */
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_NORMAL);
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1, RXFIFO_THR2_NORMAL);
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2, RXFIFO_THR3_NORMAL);
	/* TX share fअगरo मुक्त credit full threshold */
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, TXFIFO_THR_NORMAL2);
पूर्ण

अटल व्योम r8153_enter_oob(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rtl_disable(tp);
	rtl_reset_bmu(tp);

	रुको_oob_link_list_पढ़ोy(tp);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	रुको_oob_link_list_पढ़ोy(tp);

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RMS, mtu_to_size(tp->netdev->mtu));

	चयन (tp->version) अणु
	हाल RTL_VER_03:
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG);
		ocp_data &= ~TEREDO_WAKE_MASK;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG, ocp_data);
		अवरोध;

	हाल RTL_VER_08:
	हाल RTL_VER_09:
	हाल RTL_VER_14:
		/* Clear tereकरो wake event. bit[15:8] is the tereकरो wakeup
		 * type. Set it to zero. bits[7:0] are the W1C bits about
		 * the events. Set them to all 1 to clear them.
		 */
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TEREDO_WAKE_BASE, 0x00ff);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	rtl_rx_vlan_en(tp, true);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BDC_CR);
	ocp_data |= ALDPS_PROXY_MODE;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_BDC_CR, ocp_data);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data |= NOW_IS_OOB | DIS_MCU_CLROOB;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rxdy_gated_en(tp, false);

	ocp_data = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data |= RCR_APM | RCR_AM | RCR_AB;
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
पूर्ण

अटल व्योम rtl8153_disable(काष्ठा r8152 *tp)
अणु
	r8153_aldps_en(tp, false);
	rtl_disable(tp);
	rtl_reset_bmu(tp);
	r8153_aldps_en(tp, true);
पूर्ण

अटल पूर्णांक rtl8156_enable(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 speed;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस -ENODEV;

	set_tx_qlen(tp);
	rtl_set_eee_plus(tp);
	r8153_set_rx_early_समयout(tp);
	r8153_set_rx_early_size(tp);

	speed = rtl8152_get_speed(tp);
	rtl_set_अगरg(tp, speed);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
	अगर (speed & _2500bps)
		ocp_data &= ~IDLE_SPDWN_EN;
	अन्यथा
		ocp_data |= IDLE_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);

	अगर (speed & _1000bps)
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EEE_TXTWSYS, 0x11);
	अन्यथा अगर (speed & _500bps)
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EEE_TXTWSYS, 0x3d);

	अगर (tp->udev->speed == USB_SPEED_HIGH) अणु
		/* USB 0xb45e[3:0] l1_nyet_hird */
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_L1_CTRL);
		ocp_data &= ~0xf;
		अगर (is_flow_control(speed))
			ocp_data |= 0xf;
		अन्यथा
			ocp_data |= 0x1;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_L1_CTRL, ocp_data);
	पूर्ण

	वापस rtl_enable(tp);
पूर्ण

अटल पूर्णांक rtl8156b_enable(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 speed;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस -ENODEV;

	set_tx_qlen(tp);
	rtl_set_eee_plus(tp);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_RX_AGGR_NUM);
	ocp_data &= ~RX_AGGR_NUM_MASK;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_RX_AGGR_NUM, ocp_data);

	r8153_set_rx_early_समयout(tp);
	r8153_set_rx_early_size(tp);

	speed = rtl8152_get_speed(tp);
	rtl_set_अगरg(tp, speed);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
	अगर (speed & _2500bps)
		ocp_data &= ~IDLE_SPDWN_EN;
	अन्यथा
		ocp_data |= IDLE_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);

	अगर (tp->udev->speed == USB_SPEED_HIGH) अणु
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_L1_CTRL);
		ocp_data &= ~0xf;
		अगर (is_flow_control(speed))
			ocp_data |= 0xf;
		अन्यथा
			ocp_data |= 0x1;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_L1_CTRL, ocp_data);
	पूर्ण

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_TASK);
	ocp_data &= ~FC_PATCH_TASK;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);
	usleep_range(1000, 2000);
	ocp_data |= FC_PATCH_TASK;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);

	वापस rtl_enable(tp);
पूर्ण

अटल पूर्णांक rtl8152_set_speed(काष्ठा r8152 *tp, u8 स्वतःneg, u32 speed, u8 duplex,
			     u32 advertising)
अणु
	u16 bmcr;
	पूर्णांक ret = 0;

	अगर (स्वतःneg == AUTONEG_DISABLE) अणु
		अगर (duplex != DUPLEX_HALF && duplex != DUPLEX_FULL)
			वापस -EINVAL;

		चयन (speed) अणु
		हाल SPEED_10:
			bmcr = BMCR_SPEED10;
			अगर (duplex == DUPLEX_FULL) अणु
				bmcr |= BMCR_FULLDPLX;
				tp->ups_info.speed_duplex = FORCE_10M_FULL;
			पूर्ण अन्यथा अणु
				tp->ups_info.speed_duplex = FORCE_10M_HALF;
			पूर्ण
			अवरोध;
		हाल SPEED_100:
			bmcr = BMCR_SPEED100;
			अगर (duplex == DUPLEX_FULL) अणु
				bmcr |= BMCR_FULLDPLX;
				tp->ups_info.speed_duplex = FORCE_100M_FULL;
			पूर्ण अन्यथा अणु
				tp->ups_info.speed_duplex = FORCE_100M_HALF;
			पूर्ण
			अवरोध;
		हाल SPEED_1000:
			अगर (tp->mii.supports_gmii) अणु
				bmcr = BMCR_SPEED1000 | BMCR_FULLDPLX;
				tp->ups_info.speed_duplex = NWAY_1000M_FULL;
				अवरोध;
			पूर्ण
			fallthrough;
		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (duplex == DUPLEX_FULL)
			tp->mii.full_duplex = 1;
		अन्यथा
			tp->mii.full_duplex = 0;

		tp->mii.क्रमce_media = 1;
	पूर्ण अन्यथा अणु
		u16 orig, new1;
		u32 support;

		support = RTL_ADVERTISED_10_HALF | RTL_ADVERTISED_10_FULL |
			  RTL_ADVERTISED_100_HALF | RTL_ADVERTISED_100_FULL;

		अगर (tp->mii.supports_gmii) अणु
			support |= RTL_ADVERTISED_1000_FULL;

			अगर (tp->support_2500full)
				support |= RTL_ADVERTISED_2500_FULL;
		पूर्ण

		अगर (!(advertising & support))
			वापस -EINVAL;

		orig = r8152_mdio_पढ़ो(tp, MII_ADVERTISE);
		new1 = orig & ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
				ADVERTISE_100HALF | ADVERTISE_100FULL);
		अगर (advertising & RTL_ADVERTISED_10_HALF) अणु
			new1 |= ADVERTISE_10HALF;
			tp->ups_info.speed_duplex = NWAY_10M_HALF;
		पूर्ण
		अगर (advertising & RTL_ADVERTISED_10_FULL) अणु
			new1 |= ADVERTISE_10FULL;
			tp->ups_info.speed_duplex = NWAY_10M_FULL;
		पूर्ण

		अगर (advertising & RTL_ADVERTISED_100_HALF) अणु
			new1 |= ADVERTISE_100HALF;
			tp->ups_info.speed_duplex = NWAY_100M_HALF;
		पूर्ण
		अगर (advertising & RTL_ADVERTISED_100_FULL) अणु
			new1 |= ADVERTISE_100FULL;
			tp->ups_info.speed_duplex = NWAY_100M_FULL;
		पूर्ण

		अगर (orig != new1) अणु
			r8152_mdio_ग_लिखो(tp, MII_ADVERTISE, new1);
			tp->mii.advertising = new1;
		पूर्ण

		अगर (tp->mii.supports_gmii) अणु
			orig = r8152_mdio_पढ़ो(tp, MII_CTRL1000);
			new1 = orig & ~(ADVERTISE_1000FULL |
					ADVERTISE_1000HALF);

			अगर (advertising & RTL_ADVERTISED_1000_FULL) अणु
				new1 |= ADVERTISE_1000FULL;
				tp->ups_info.speed_duplex = NWAY_1000M_FULL;
			पूर्ण

			अगर (orig != new1)
				r8152_mdio_ग_लिखो(tp, MII_CTRL1000, new1);
		पूर्ण

		अगर (tp->support_2500full) अणु
			orig = ocp_reg_पढ़ो(tp, OCP_10GBT_CTRL);
			new1 = orig & ~MDIO_AN_10GBT_CTRL_ADV2_5G;

			अगर (advertising & RTL_ADVERTISED_2500_FULL) अणु
				new1 |= MDIO_AN_10GBT_CTRL_ADV2_5G;
				tp->ups_info.speed_duplex = NWAY_2500M_FULL;
			पूर्ण

			अगर (orig != new1)
				ocp_reg_ग_लिखो(tp, OCP_10GBT_CTRL, new1);
		पूर्ण

		bmcr = BMCR_ANENABLE | BMCR_ANRESTART;

		tp->mii.क्रमce_media = 0;
	पूर्ण

	अगर (test_and_clear_bit(PHY_RESET, &tp->flags))
		bmcr |= BMCR_RESET;

	r8152_mdio_ग_लिखो(tp, MII_BMCR, bmcr);

	अगर (bmcr & BMCR_RESET) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 50; i++) अणु
			msleep(20);
			अगर ((r8152_mdio_पढ़ो(tp, MII_BMCR) & BMCR_RESET) == 0)
				अवरोध;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम rtl8152_up(काष्ठा r8152 *tp)
अणु
	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	r8152_aldps_en(tp, false);
	r8152b_निकास_oob(tp);
	r8152_aldps_en(tp, true);
पूर्ण

अटल व्योम rtl8152_करोwn(काष्ठा r8152 *tp)
अणु
	अगर (test_bit(RTL8152_UNPLUG, &tp->flags)) अणु
		rtl_drop_queued_tx(tp);
		वापस;
	पूर्ण

	r8152_घातer_cut_en(tp, false);
	r8152_aldps_en(tp, false);
	r8152b_enter_oob(tp);
	r8152_aldps_en(tp, true);
पूर्ण

अटल व्योम rtl8153_up(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	r8153_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_aldps_en(tp, false);
	r8153_first_init(tp);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6);
	ocp_data |= LANWAKE_CLR_EN;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6, ocp_data);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_LWAKE_CTRL_REG);
	ocp_data &= ~LANWAKE_PIN;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_LWAKE_CTRL_REG, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_SSPHYLINK1);
	ocp_data &= ~DELAY_PHY_PWR_CHG;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_SSPHYLINK1, ocp_data);

	r8153_aldps_en(tp, true);

	चयन (tp->version) अणु
	हाल RTL_VER_03:
	हाल RTL_VER_04:
		अवरोध;
	हाल RTL_VER_05:
	हाल RTL_VER_06:
	शेष:
		r8153_u2p3en(tp, true);
		अवरोध;
	पूर्ण

	r8153_u1u2en(tp, true);
पूर्ण

अटल व्योम rtl8153_करोwn(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags)) अणु
		rtl_drop_queued_tx(tp);
		वापस;
	पूर्ण

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6);
	ocp_data &= ~LANWAKE_CLR_EN;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6, ocp_data);

	r8153_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_घातer_cut_en(tp, false);
	r8153_aldps_en(tp, false);
	r8153_enter_oob(tp);
	r8153_aldps_en(tp, true);
पूर्ण

अटल व्योम rtl8153b_up(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	r8153b_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_aldps_en(tp, false);

	r8153_first_init(tp);
	ocp_ग_लिखो_dword(tp, MCU_TYPE_USB, USB_RX_BUF_TH, RX_THR_B);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3);
	ocp_data &= ~PLA_MCU_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3, ocp_data);

	r8153_aldps_en(tp, true);

	अगर (tp->udev->speed >= USB_SPEED_SUPER)
		r8153b_u1u2en(tp, true);
पूर्ण

अटल व्योम rtl8153b_करोwn(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags)) अणु
		rtl_drop_queued_tx(tp);
		वापस;
	पूर्ण

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3);
	ocp_data |= PLA_MCU_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3, ocp_data);

	r8153b_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153b_घातer_cut_en(tp, false);
	r8153_aldps_en(tp, false);
	r8153_enter_oob(tp);
	r8153_aldps_en(tp, true);
पूर्ण

अटल व्योम rtl8153c_change_mtu(काष्ठा r8152 *tp)
अणु
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RMS, mtu_to_size(tp->netdev->mtu));
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_MTPS, 10 * 1024 / 64);

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, 512 / 64);

	/* Adjust the tx fअगरo मुक्त credit full threshold, otherwise
	 * the fअगरo would be too small to send a jumbo frame packet.
	 */
	अगर (tp->netdev->mtu < 8000)
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TXFIFO_FULL, 2048 / 8);
	अन्यथा
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TXFIFO_FULL, 900 / 8);
पूर्ण

अटल व्योम rtl8153c_up(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	r8153b_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_aldps_en(tp, false);

	rxdy_gated_en(tp, true);
	r8153_tereकरो_off(tp);

	ocp_data = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rtl8152_nic_reset(tp);
	rtl_reset_bmu(tp);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	रुको_oob_link_list_पढ़ोy(tp);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	रुको_oob_link_list_पढ़ोy(tp);

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	rtl8153c_change_mtu(tp);

	rtl8152_nic_reset(tp);

	/* rx share fअगरo credit full threshold */
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, 0x02);
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_RXFIFO_FULL, 0x08);
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1, RXFIFO_THR2_NORMAL);
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2, RXFIFO_THR3_NORMAL);

	ocp_ग_लिखो_dword(tp, MCU_TYPE_USB, USB_RX_BUF_TH, RX_THR_B);

	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
	ocp_data |= BIT(8);
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3);
	ocp_data &= ~PLA_MCU_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3, ocp_data);

	r8153_aldps_en(tp, true);
	r8153b_u1u2en(tp, true);
पूर्ण

अटल अंतरभूत u32 fc_छोड़ो_on_स्वतः(काष्ठा r8152 *tp)
अणु
	वापस (ALIGN(mtu_to_size(tp->netdev->mtu), 1024) + 6 * 1024);
पूर्ण

अटल अंतरभूत u32 fc_छोड़ो_off_स्वतः(काष्ठा r8152 *tp)
अणु
	वापस (ALIGN(mtu_to_size(tp->netdev->mtu), 1024) + 14 * 1024);
पूर्ण

अटल व्योम r8156_fc_parameter(काष्ठा r8152 *tp)
अणु
	u32 छोड़ो_on = tp->fc_छोड़ो_on ? tp->fc_छोड़ो_on : fc_छोड़ो_on_स्वतः(tp);
	u32 छोड़ो_off = tp->fc_छोड़ो_off ? tp->fc_छोड़ो_off : fc_छोड़ो_off_स्वतः(tp);

	चयन (tp->version) अणु
	हाल RTL_VER_10:
	हाल RTL_VER_11:
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RX_FIFO_FULL, छोड़ो_on / 8);
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RX_FIFO_EMPTY, छोड़ो_off / 8);
		अवरोध;
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RX_FIFO_FULL, छोड़ो_on / 16);
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RX_FIFO_EMPTY, छोड़ो_off / 16);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtl8156_change_mtu(काष्ठा r8152 *tp)
अणु
	u32 rx_max_size = mtu_to_size(tp->netdev->mtu);

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RMS, rx_max_size);
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_MTPS, MTPS_JUMBO);
	r8156_fc_parameter(tp);

	/* TX share fअगरo मुक्त credit full threshold */
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, 512 / 64);
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TXFIFO_FULL,
		       ALIGN(rx_max_size + माप(काष्ठा tx_desc), 1024) / 16);
पूर्ण

अटल व्योम rtl8156_up(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	r8153b_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_aldps_en(tp, false);

	rxdy_gated_en(tp, true);
	r8153_tereकरो_off(tp);

	ocp_data = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rtl8152_nic_reset(tp);
	rtl_reset_bmu(tp);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	rtl8156_change_mtu(tp);

	चयन (tp->version) अणु
	हाल RTL_TEST_01:
	हाल RTL_VER_10:
	हाल RTL_VER_11:
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_BMU_CONFIG);
		ocp_data |= ACT_ODMA;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_BMU_CONFIG, ocp_data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* share FIFO settings */
	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_FULL);
	ocp_data &= ~RXFIFO_FULL_MASK;
	ocp_data |= 0x08;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_FULL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3);
	ocp_data &= ~PLA_MCU_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_SPEED_OPTION);
	ocp_data &= ~(RG_PWRDN_EN | ALL_SPEED_OFF);
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_SPEED_OPTION, ocp_data);

	ocp_ग_लिखो_dword(tp, MCU_TYPE_USB, USB_RX_BUF_TH, 0x00600400);

	अगर (tp->saved_wolopts != __rtl_get_wol(tp)) अणु
		netअगर_warn(tp, अगरup, tp->netdev, "wol setting is changed\n");
		__rtl_set_wol(tp, tp->saved_wolopts);
	पूर्ण

	r8153_aldps_en(tp, true);
	r8153_u2p3en(tp, true);

	अगर (tp->udev->speed >= USB_SPEED_SUPER)
		r8153b_u1u2en(tp, true);
पूर्ण

अटल व्योम rtl8156_करोwn(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags)) अणु
		rtl_drop_queued_tx(tp);
		वापस;
	पूर्ण

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3);
	ocp_data |= PLA_MCU_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3, ocp_data);

	r8153b_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153b_घातer_cut_en(tp, false);
	r8153_aldps_en(tp, false);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rtl_disable(tp);
	rtl_reset_bmu(tp);

	/* Clear tereकरो wake event. bit[15:8] is the tereकरो wakeup
	 * type. Set it to zero. bits[7:0] are the W1C bits about
	 * the events. Set them to all 1 to clear them.
	 */
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_TEREDO_WAKE_BASE, 0x00ff);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data |= NOW_IS_OOB;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rtl_rx_vlan_en(tp, true);
	rxdy_gated_en(tp, false);

	ocp_data = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data |= RCR_APM | RCR_AM | RCR_AB;
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	r8153_aldps_en(tp, true);
पूर्ण

अटल bool rtl8152_in_nway(काष्ठा r8152 *tp)
अणु
	u16 nway_state;

	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, 0x2000);
	tp->ocp_base = 0x2000;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, 0xb014, 0x4c);		/* phy state */
	nway_state = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, 0xb01a);

	/* bit 15: TXDIS_STATE, bit 14: ABD_STATE */
	अगर (nway_state & 0xc000)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल bool rtl8153_in_nway(काष्ठा r8152 *tp)
अणु
	u16 phy_state = ocp_reg_पढ़ो(tp, OCP_PHY_STATE) & 0xff;

	अगर (phy_state == TXDIS_STATE || phy_state == ABD_STATE)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल व्योम set_carrier(काष्ठा r8152 *tp)
अणु
	काष्ठा net_device *netdev = tp->netdev;
	काष्ठा napi_काष्ठा *napi = &tp->napi;
	u16 speed;

	speed = rtl8152_get_speed(tp);

	अगर (speed & LINK_STATUS) अणु
		अगर (!netअगर_carrier_ok(netdev)) अणु
			tp->rtl_ops.enable(tp);
			netअगर_stop_queue(netdev);
			napi_disable(napi);
			netअगर_carrier_on(netdev);
			rtl_start_rx(tp);
			clear_bit(RTL8152_SET_RX_MODE, &tp->flags);
			_rtl8152_set_rx_mode(netdev);
			napi_enable(napi);
			netअगर_wake_queue(netdev);
			netअगर_info(tp, link, netdev, "carrier on\n");
		पूर्ण अन्यथा अगर (netअगर_queue_stopped(netdev) &&
			   skb_queue_len(&tp->tx_queue) < tp->tx_qlen) अणु
			netअगर_wake_queue(netdev);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			netअगर_carrier_off(netdev);
			tasklet_disable(&tp->tx_tl);
			napi_disable(napi);
			tp->rtl_ops.disable(tp);
			napi_enable(napi);
			tasklet_enable(&tp->tx_tl);
			netअगर_info(tp, link, netdev, "carrier off\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl_work_func_t(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा r8152 *tp = container_of(work, काष्ठा r8152, schedule.work);

	/* If the device is unplugged or !netअगर_running(), the workqueue
	 * करोesn't need to wake the device, and could वापस directly.
	 */
	अगर (test_bit(RTL8152_UNPLUG, &tp->flags) || !netअगर_running(tp->netdev))
		वापस;

	अगर (usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf) < 0)
		वापस;

	अगर (!test_bit(WORK_ENABLE, &tp->flags))
		जाओ out1;

	अगर (!mutex_trylock(&tp->control)) अणु
		schedule_delayed_work(&tp->schedule, 0);
		जाओ out1;
	पूर्ण

	अगर (test_and_clear_bit(RTL8152_LINK_CHG, &tp->flags))
		set_carrier(tp);

	अगर (test_and_clear_bit(RTL8152_SET_RX_MODE, &tp->flags))
		_rtl8152_set_rx_mode(tp->netdev);

	/* करोn't schedule tasket beक्रमe linking */
	अगर (test_and_clear_bit(SCHEDULE_TASKLET, &tp->flags) &&
	    netअगर_carrier_ok(tp->netdev))
		tasklet_schedule(&tp->tx_tl);

	mutex_unlock(&tp->control);

out1:
	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);
पूर्ण

अटल व्योम rtl_hw_phy_work_func_t(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा r8152 *tp = container_of(work, काष्ठा r8152, hw_phy_work.work);

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	अगर (usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf) < 0)
		वापस;

	mutex_lock(&tp->control);

	अगर (rtl8152_request_firmware(tp) == -ENODEV && tp->rtl_fw.retry) अणु
		tp->rtl_fw.retry = false;
		tp->rtl_fw.fw = शून्य;

		/* Delay execution in हाल request_firmware() is not पढ़ोy yet.
		 */
		queue_delayed_work(प्रणाली_दीर्घ_wq, &tp->hw_phy_work, HZ * 10);
		जाओ ignore_once;
	पूर्ण

	tp->rtl_ops.hw_phy_cfg(tp);

	rtl8152_set_speed(tp, tp->स्वतःneg, tp->speed, tp->duplex,
			  tp->advertising);

ignore_once:
	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rtl_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			व्योम *data)
अणु
	काष्ठा r8152 *tp = container_of(nb, काष्ठा r8152, pm_notअगरier);

	चयन (action) अणु
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_SUSPEND_PREPARE:
		usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
		अवरोध;

	हाल PM_POST_HIBERNATION:
	हाल PM_POST_SUSPEND:
		usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);
		अवरोध;

	हाल PM_POST_RESTORE:
	हाल PM_RESTORE_PREPARE:
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rtl8152_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);
	पूर्णांक res = 0;

	अगर (work_busy(&tp->hw_phy_work.work) & WORK_BUSY_PENDING) अणु
		cancel_delayed_work_sync(&tp->hw_phy_work);
		rtl_hw_phy_work_func_t(&tp->hw_phy_work.work);
	पूर्ण

	res = alloc_all_mem(tp);
	अगर (res)
		जाओ out;

	res = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (res < 0)
		जाओ out_मुक्त;

	mutex_lock(&tp->control);

	tp->rtl_ops.up(tp);

	netअगर_carrier_off(netdev);
	netअगर_start_queue(netdev);
	set_bit(WORK_ENABLE, &tp->flags);

	res = usb_submit_urb(tp->पूर्णांकr_urb, GFP_KERNEL);
	अगर (res) अणु
		अगर (res == -ENODEV)
			netअगर_device_detach(tp->netdev);
		netअगर_warn(tp, अगरup, netdev, "intr_urb submit failed: %d\n",
			   res);
		जाओ out_unlock;
	पूर्ण
	napi_enable(&tp->napi);
	tasklet_enable(&tp->tx_tl);

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);
#अगर_घोषित CONFIG_PM_SLEEP
	tp->pm_notअगरier.notअगरier_call = rtl_notअगरier;
	रेजिस्टर_pm_notअगरier(&tp->pm_notअगरier);
#पूर्ण_अगर
	वापस 0;

out_unlock:
	mutex_unlock(&tp->control);
	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);
out_मुक्त:
	मुक्त_all_mem(tp);
out:
	वापस res;
पूर्ण

अटल पूर्णांक rtl8152_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);
	पूर्णांक res = 0;

#अगर_घोषित CONFIG_PM_SLEEP
	unरेजिस्टर_pm_notअगरier(&tp->pm_notअगरier);
#पूर्ण_अगर
	tasklet_disable(&tp->tx_tl);
	clear_bit(WORK_ENABLE, &tp->flags);
	usb_समाप्त_urb(tp->पूर्णांकr_urb);
	cancel_delayed_work_sync(&tp->schedule);
	napi_disable(&tp->napi);
	netअगर_stop_queue(netdev);

	res = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (res < 0 || test_bit(RTL8152_UNPLUG, &tp->flags)) अणु
		rtl_drop_queued_tx(tp);
		rtl_stop_rx(tp);
	पूर्ण अन्यथा अणु
		mutex_lock(&tp->control);

		tp->rtl_ops.करोwn(tp);

		mutex_unlock(&tp->control);

		usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);
	पूर्ण

	मुक्त_all_mem(tp);

	वापस res;
पूर्ण

अटल व्योम rtl_tally_reset(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_RSTTALLY);
	ocp_data |= TALLY_RESET;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RSTTALLY, ocp_data);
पूर्ण

अटल व्योम r8152b_init(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 data;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	data = r8152_mdio_पढ़ो(tp, MII_BMCR);
	अगर (data & BMCR_PDOWN) अणु
		data &= ~BMCR_PDOWN;
		r8152_mdio_ग_लिखो(tp, MII_BMCR, data);
	पूर्ण

	r8152_aldps_en(tp, false);

	अगर (tp->version == RTL_VER_01) अणु
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE);
		ocp_data &= ~LED_MODE_MASK;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE, ocp_data);
	पूर्ण

	r8152_घातer_cut_en(tp, false);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= TX_10M_IDLE_EN | PFM_PWM_SWITCH;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);
	ocp_data = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL);
	ocp_data &= ~MCU_CLK_RATIO_MASK;
	ocp_data |= MCU_CLK_RATIO | D3_CLK_GATED_EN;
	ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL, ocp_data);
	ocp_data = GPHY_STS_MSK | SPEED_DOWN_MSK |
		   SPDWN_RXDV_MSK | SPDWN_LINKCHG_MSK;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_GPHY_INTR_IMR, ocp_data);

	rtl_tally_reset(tp);

	/* enable rx aggregation */
	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);
पूर्ण

अटल व्योम r8153_init(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 data;
	पूर्णांक i;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	r8153_u1u2en(tp, false);

	क्रम (i = 0; i < 500; i++) अणु
		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			अवरोध;

		msleep(20);
		अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
			अवरोध;
	पूर्ण

	data = r8153_phy_status(tp, 0);

	अगर (tp->version == RTL_VER_03 || tp->version == RTL_VER_04 ||
	    tp->version == RTL_VER_05)
		ocp_reg_ग_लिखो(tp, OCP_ADC_CFG, CKADSEL_L | ADC_EN | EN_EMI_L);

	data = r8152_mdio_पढ़ो(tp, MII_BMCR);
	अगर (data & BMCR_PDOWN) अणु
		data &= ~BMCR_PDOWN;
		r8152_mdio_ग_लिखो(tp, MII_BMCR, data);
	पूर्ण

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	अगर (tp->version == RTL_VER_04) अणु
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_SSPHYLINK2);
		ocp_data &= ~pwd_dn_scale_mask;
		ocp_data |= pwd_dn_scale(96);
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_SSPHYLINK2, ocp_data);

		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_USB2PHY);
		ocp_data |= USB2PHY_L1 | USB2PHY_SUSPEND;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_USB2PHY, ocp_data);
	पूर्ण अन्यथा अगर (tp->version == RTL_VER_05) अणु
		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_DMY_REG0);
		ocp_data &= ~ECM_ALDPS;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_DMY_REG0, ocp_data);

		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1);
		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_BURST_SIZE) == 0)
			ocp_data &= ~DYNAMIC_BURST;
		अन्यथा
			ocp_data |= DYNAMIC_BURST;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1, ocp_data);
	पूर्ण अन्यथा अगर (tp->version == RTL_VER_06) अणु
		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1);
		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_BURST_SIZE) == 0)
			ocp_data &= ~DYNAMIC_BURST;
		अन्यथा
			ocp_data |= DYNAMIC_BURST;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1, ocp_data);

		r8153_queue_wake(tp, false);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
		अगर (rtl8152_get_speed(tp) & LINK_STATUS)
			ocp_data |= CUR_LINK_OK;
		अन्यथा
			ocp_data &= ~CUR_LINK_OK;
		ocp_data |= POLL_LINK_CHG;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);
	पूर्ण

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY2);
	ocp_data |= EP4_FULL_FC;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY2, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_WDT11_CTRL);
	ocp_data &= ~TIMER11_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_WDT11_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE);
	ocp_data &= ~LED_MODE_MASK;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE, ocp_data);

	ocp_data = FIFO_EMPTY_1FB | ROK_EXIT_LPM;
	अगर (tp->version == RTL_VER_04 && tp->udev->speed < USB_SPEED_SUPER)
		ocp_data |= LPM_TIMER_500MS;
	अन्यथा
		ocp_data |= LPM_TIMER_500US;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_LPM_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_AFE_CTRL2);
	ocp_data &= ~SEN_VAL_MASK;
	ocp_data |= SEN_VAL_NORMAL | SEL_RXIDLE;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_AFE_CTRL2, ocp_data);

	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_CONNECT_TIMER, 0x0001);

	r8153_घातer_cut_en(tp, false);
	rtl_runसमय_suspend_enable(tp, false);
	r8153_mac_clk_speed_करोwn(tp, false);
	r8153_u1u2en(tp, true);
	usb_enable_lpm(tp->udev);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6);
	ocp_data |= LANWAKE_CLR_EN;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6, ocp_data);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_LWAKE_CTRL_REG);
	ocp_data &= ~LANWAKE_PIN;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_LWAKE_CTRL_REG, ocp_data);

	/* rx aggregation */
	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	अगर (tp->dell_tb_rx_agg_bug)
		ocp_data |= RX_AGG_DISABLE;

	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	rtl_tally_reset(tp);

	चयन (tp->udev->speed) अणु
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		tp->coalesce = COALESCE_SUPER;
		अवरोध;
	हाल USB_SPEED_HIGH:
		tp->coalesce = COALESCE_HIGH;
		अवरोध;
	शेष:
		tp->coalesce = COALESCE_SLOW;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम r8153b_init(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 data;
	पूर्णांक i;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	r8153b_u1u2en(tp, false);

	क्रम (i = 0; i < 500; i++) अणु
		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			अवरोध;

		msleep(20);
		अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
			अवरोध;
	पूर्ण

	data = r8153_phy_status(tp, 0);

	data = r8152_mdio_पढ़ो(tp, MII_BMCR);
	अगर (data & BMCR_PDOWN) अणु
		data &= ~BMCR_PDOWN;
		r8152_mdio_ग_लिखो(tp, MII_BMCR, data);
	पूर्ण

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	/* MSC समयr = 0xfff * 8ms = 32760 ms */
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_MSC_TIMER, 0x0fff);

	r8153b_घातer_cut_en(tp, false);
	r8153b_ups_en(tp, false);
	r8153_queue_wake(tp, false);
	rtl_runसमय_suspend_enable(tp, false);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	अगर (rtl8152_get_speed(tp) & LINK_STATUS)
		ocp_data |= CUR_LINK_OK;
	अन्यथा
		ocp_data &= ~CUR_LINK_OK;
	ocp_data |= POLL_LINK_CHG;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);

	अगर (tp->udev->speed >= USB_SPEED_SUPER)
		r8153b_u1u2en(tp, true);

	usb_enable_lpm(tp->udev);

	/* MAC घड़ी speed करोwn */
	r8153_mac_clk_speed_करोwn(tp, true);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3);
	ocp_data &= ~PLA_MCU_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3, ocp_data);

	अगर (tp->version == RTL_VER_09) अणु
		/* Disable Test IO क्रम 32QFN */
		अगर (ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, 0xdc00) & BIT(5)) अणु
			ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
			ocp_data |= TEST_IO_OFF;
			ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);
		पूर्ण
	पूर्ण

	set_bit(GREEN_ETHERNET, &tp->flags);

	/* rx aggregation */
	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	rtl_tally_reset(tp);

	tp->coalesce = 15000;	/* 15 us */
पूर्ण

अटल व्योम r8153c_init(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 data;
	पूर्णांक i;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	r8153b_u1u2en(tp, false);

	/* Disable spi_en */
	ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);
	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CONFIG5);
	ocp_data &= ~BIT(3);
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_CONFIG5, ocp_data);
	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, 0xcbf0);
	ocp_data |= BIT(1);
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, 0xcbf0, ocp_data);

	क्रम (i = 0; i < 500; i++) अणु
		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			अवरोध;

		msleep(20);
		अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
			वापस;
	पूर्ण

	data = r8153_phy_status(tp, 0);

	data = r8152_mdio_पढ़ो(tp, MII_BMCR);
	अगर (data & BMCR_PDOWN) अणु
		data &= ~BMCR_PDOWN;
		r8152_mdio_ग_लिखो(tp, MII_BMCR, data);
	पूर्ण

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	/* MSC समयr = 0xfff * 8ms = 32760 ms */
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_MSC_TIMER, 0x0fff);

	r8153b_घातer_cut_en(tp, false);
	r8153c_ups_en(tp, false);
	r8153_queue_wake(tp, false);
	rtl_runसमय_suspend_enable(tp, false);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	अगर (rtl8152_get_speed(tp) & LINK_STATUS)
		ocp_data |= CUR_LINK_OK;
	अन्यथा
		ocp_data &= ~CUR_LINK_OK;

	ocp_data |= POLL_LINK_CHG;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);

	r8153b_u1u2en(tp, true);

	usb_enable_lpm(tp->udev);

	/* MAC घड़ी speed करोwn */
	r8153_mac_clk_speed_करोwn(tp, true);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_MISC_2);
	ocp_data &= ~BIT(7);
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);

	set_bit(GREEN_ETHERNET, &tp->flags);

	/* rx aggregation */
	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	rtl_tally_reset(tp);

	tp->coalesce = 15000;	/* 15 us */
पूर्ण

अटल व्योम r8156_hw_phy_cfg(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 data;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_MISC_0);
	अगर (ocp_data & PCUT_STATUS) अणु
		ocp_data &= ~PCUT_STATUS;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_MISC_0, ocp_data);
	पूर्ण

	data = r8153_phy_status(tp, 0);
	चयन (data) अणु
	हाल PHY_STAT_EXT_INIT:
		rtl8152_apply_firmware(tp, true);

		data = ocp_reg_पढ़ो(tp, 0xa468);
		data &= ~(BIT(3) | BIT(1));
		ocp_reg_ग_लिखो(tp, 0xa468, data);
		अवरोध;
	हाल PHY_STAT_LAN_ON:
	हाल PHY_STAT_PWRDN:
	शेष:
		rtl8152_apply_firmware(tp, false);
		अवरोध;
	पूर्ण

	/* disable ALDPS beक्रमe updating the PHY parameters */
	r8153_aldps_en(tp, false);

	/* disable EEE beक्रमe updating the PHY parameters */
	rtl_eee_enable(tp, false);

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);
	WARN_ON_ONCE(data != PHY_STAT_LAN_ON);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= PFM_PWM_SWITCH;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);

	चयन (tp->version) अणु
	हाल RTL_VER_10:
		data = ocp_reg_पढ़ो(tp, 0xad40);
		data &= ~0x3ff;
		data |= BIT(7) | BIT(2);
		ocp_reg_ग_लिखो(tp, 0xad40, data);

		data = ocp_reg_पढ़ो(tp, 0xad4e);
		data |= BIT(4);
		ocp_reg_ग_लिखो(tp, 0xad4e, data);
		data = ocp_reg_पढ़ो(tp, 0xad16);
		data &= ~0x3ff;
		data |= 0x6;
		ocp_reg_ग_लिखो(tp, 0xad16, data);
		data = ocp_reg_पढ़ो(tp, 0xad32);
		data &= ~0x3f;
		data |= 6;
		ocp_reg_ग_लिखो(tp, 0xad32, data);
		data = ocp_reg_पढ़ो(tp, 0xac08);
		data &= ~(BIT(12) | BIT(8));
		ocp_reg_ग_लिखो(tp, 0xac08, data);
		data = ocp_reg_पढ़ो(tp, 0xac8a);
		data |= BIT(12) | BIT(13) | BIT(14);
		data &= ~BIT(15);
		ocp_reg_ग_लिखो(tp, 0xac8a, data);
		data = ocp_reg_पढ़ो(tp, 0xad18);
		data |= BIT(10);
		ocp_reg_ग_लिखो(tp, 0xad18, data);
		data = ocp_reg_पढ़ो(tp, 0xad1a);
		data |= 0x3ff;
		ocp_reg_ग_लिखो(tp, 0xad1a, data);
		data = ocp_reg_पढ़ो(tp, 0xad1c);
		data |= 0x3ff;
		ocp_reg_ग_लिखो(tp, 0xad1c, data);

		data = sram_पढ़ो(tp, 0x80ea);
		data &= ~0xff00;
		data |= 0xc400;
		sram_ग_लिखो(tp, 0x80ea, data);
		data = sram_पढ़ो(tp, 0x80eb);
		data &= ~0x0700;
		data |= 0x0300;
		sram_ग_लिखो(tp, 0x80eb, data);
		data = sram_पढ़ो(tp, 0x80f8);
		data &= ~0xff00;
		data |= 0x1c00;
		sram_ग_लिखो(tp, 0x80f8, data);
		data = sram_पढ़ो(tp, 0x80f1);
		data &= ~0xff00;
		data |= 0x3000;
		sram_ग_लिखो(tp, 0x80f1, data);

		data = sram_पढ़ो(tp, 0x80fe);
		data &= ~0xff00;
		data |= 0xa500;
		sram_ग_लिखो(tp, 0x80fe, data);
		data = sram_पढ़ो(tp, 0x8102);
		data &= ~0xff00;
		data |= 0x5000;
		sram_ग_लिखो(tp, 0x8102, data);
		data = sram_पढ़ो(tp, 0x8015);
		data &= ~0xff00;
		data |= 0x3300;
		sram_ग_लिखो(tp, 0x8015, data);
		data = sram_पढ़ो(tp, 0x8100);
		data &= ~0xff00;
		data |= 0x7000;
		sram_ग_लिखो(tp, 0x8100, data);
		data = sram_पढ़ो(tp, 0x8014);
		data &= ~0xff00;
		data |= 0xf000;
		sram_ग_लिखो(tp, 0x8014, data);
		data = sram_पढ़ो(tp, 0x8016);
		data &= ~0xff00;
		data |= 0x6500;
		sram_ग_लिखो(tp, 0x8016, data);
		data = sram_पढ़ो(tp, 0x80dc);
		data &= ~0xff00;
		data |= 0xed00;
		sram_ग_लिखो(tp, 0x80dc, data);
		data = sram_पढ़ो(tp, 0x80df);
		data |= BIT(8);
		sram_ग_लिखो(tp, 0x80df, data);
		data = sram_पढ़ो(tp, 0x80e1);
		data &= ~BIT(8);
		sram_ग_लिखो(tp, 0x80e1, data);

		data = ocp_reg_पढ़ो(tp, 0xbf06);
		data &= ~0x003f;
		data |= 0x0038;
		ocp_reg_ग_लिखो(tp, 0xbf06, data);

		sram_ग_लिखो(tp, 0x819f, 0xddb6);

		ocp_reg_ग_लिखो(tp, 0xbc34, 0x5555);
		data = ocp_reg_पढ़ो(tp, 0xbf0a);
		data &= ~0x0e00;
		data |= 0x0a00;
		ocp_reg_ग_लिखो(tp, 0xbf0a, data);

		data = ocp_reg_पढ़ो(tp, 0xbd2c);
		data &= ~BIT(13);
		ocp_reg_ग_लिखो(tp, 0xbd2c, data);
		अवरोध;
	हाल RTL_VER_11:
		data = ocp_reg_पढ़ो(tp, 0xad16);
		data |= 0x3ff;
		ocp_reg_ग_लिखो(tp, 0xad16, data);
		data = ocp_reg_पढ़ो(tp, 0xad32);
		data &= ~0x3f;
		data |= 6;
		ocp_reg_ग_लिखो(tp, 0xad32, data);
		data = ocp_reg_पढ़ो(tp, 0xac08);
		data &= ~(BIT(12) | BIT(8));
		ocp_reg_ग_लिखो(tp, 0xac08, data);
		data = ocp_reg_पढ़ो(tp, 0xacc0);
		data &= ~0x3;
		data |= BIT(1);
		ocp_reg_ग_लिखो(tp, 0xacc0, data);
		data = ocp_reg_पढ़ो(tp, 0xad40);
		data &= ~0xe7;
		data |= BIT(6) | BIT(2);
		ocp_reg_ग_लिखो(tp, 0xad40, data);
		data = ocp_reg_पढ़ो(tp, 0xac14);
		data &= ~BIT(7);
		ocp_reg_ग_लिखो(tp, 0xac14, data);
		data = ocp_reg_पढ़ो(tp, 0xac80);
		data &= ~(BIT(8) | BIT(9));
		ocp_reg_ग_लिखो(tp, 0xac80, data);
		data = ocp_reg_पढ़ो(tp, 0xac5e);
		data &= ~0x7;
		data |= BIT(1);
		ocp_reg_ग_लिखो(tp, 0xac5e, data);
		ocp_reg_ग_लिखो(tp, 0xad4c, 0x00a8);
		ocp_reg_ग_लिखो(tp, 0xac5c, 0x01ff);
		data = ocp_reg_पढ़ो(tp, 0xac8a);
		data &= ~0xf0;
		data |= BIT(4) | BIT(5);
		ocp_reg_ग_लिखो(tp, 0xac8a, data);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8157);
		data = ocp_reg_पढ़ो(tp, 0xb87e);
		data &= ~0xff00;
		data |= 0x0500;
		ocp_reg_ग_लिखो(tp, 0xb87e, data);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8159);
		data = ocp_reg_पढ़ो(tp, 0xb87e);
		data &= ~0xff00;
		data |= 0x0700;
		ocp_reg_ग_लिखो(tp, 0xb87e, data);

		/* AAGC */
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x80a2);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0153);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x809c);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0153);

		/* EEE parameter */
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EEE_TXTWSYS_2P5G, 0x0056);

		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_USB_CFG);
		ocp_data |= EN_XG_LIP | EN_G_LIP;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_USB_CFG, ocp_data);

		sram_ग_लिखो(tp, 0x8257, 0x020f); /*  XG PLL */
		sram_ग_लिखो(tp, 0x80ea, 0x7843); /* GIGA Master */

		अगर (rtl_phy_patch_request(tp, true, true))
			वापस;

		/* Advance EEE */
		ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
		ocp_data |= EEE_SPDWN_EN;
		ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);

		data = ocp_reg_पढ़ो(tp, OCP_DOWN_SPEED);
		data &= ~(EN_EEE_100 | EN_EEE_1000);
		data |= EN_10M_CLKDIV;
		ocp_reg_ग_लिखो(tp, OCP_DOWN_SPEED, data);
		tp->ups_info._10m_ckभाग = true;
		tp->ups_info.eee_plloff_100 = false;
		tp->ups_info.eee_plloff_giga = false;

		data = ocp_reg_पढ़ो(tp, OCP_POWER_CFG);
		data &= ~EEE_CLKDIV_EN;
		ocp_reg_ग_लिखो(tp, OCP_POWER_CFG, data);
		tp->ups_info.eee_ckभाग = false;

		ocp_reg_ग_लिखो(tp, OCP_SYSCLK_CFG, 0);
		ocp_reg_ग_लिखो(tp, OCP_SYSCLK_CFG, sysclk_भाग_expo(5));
		tp->ups_info._250m_ckभाग = false;

		rtl_phy_patch_request(tp, false, true);

		/* enable ADC Ibias Cal */
		data = ocp_reg_पढ़ो(tp, 0xd068);
		data |= BIT(13);
		ocp_reg_ग_लिखो(tp, 0xd068, data);

		/* enable Thermal Sensor */
		data = sram_पढ़ो(tp, 0x81a2);
		data &= ~BIT(8);
		sram_ग_लिखो(tp, 0x81a2, data);
		data = ocp_reg_पढ़ो(tp, 0xb54c);
		data &= ~0xff00;
		data |= 0xdb00;
		ocp_reg_ग_लिखो(tp, 0xb54c, data);

		/* Nway 2.5G Lite */
		data = ocp_reg_पढ़ो(tp, 0xa454);
		data &= ~BIT(0);
		ocp_reg_ग_लिखो(tp, 0xa454, data);

		/* CS DSP solution */
		data = ocp_reg_पढ़ो(tp, OCP_10GBT_CTRL);
		data |= RTL_ADV2_5G_F_R;
		ocp_reg_ग_लिखो(tp, OCP_10GBT_CTRL, data);
		data = ocp_reg_पढ़ो(tp, 0xad4e);
		data &= ~BIT(4);
		ocp_reg_ग_लिखो(tp, 0xad4e, data);
		data = ocp_reg_पढ़ो(tp, 0xa86a);
		data &= ~BIT(0);
		ocp_reg_ग_लिखो(tp, 0xa86a, data);

		/* MDI SWAP */
		अगर ((ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_UPS_CFG) & MID_REVERSE) &&
		    (ocp_reg_पढ़ो(tp, 0xd068) & BIT(1))) अणु
			u16 swap_a, swap_b;

			data = ocp_reg_पढ़ो(tp, 0xd068);
			data &= ~0x1f;
			data |= 0x1; /* p0 */
			ocp_reg_ग_लिखो(tp, 0xd068, data);
			swap_a = ocp_reg_पढ़ो(tp, 0xd06a);
			data &= ~0x18;
			data |= 0x18; /* p3 */
			ocp_reg_ग_लिखो(tp, 0xd068, data);
			swap_b = ocp_reg_पढ़ो(tp, 0xd06a);
			data &= ~0x18; /* p0 */
			ocp_reg_ग_लिखो(tp, 0xd068, data);
			ocp_reg_ग_लिखो(tp, 0xd06a,
				      (swap_a & ~0x7ff) | (swap_b & 0x7ff));
			data |= 0x18; /* p3 */
			ocp_reg_ग_लिखो(tp, 0xd068, data);
			ocp_reg_ग_लिखो(tp, 0xd06a,
				      (swap_b & ~0x7ff) | (swap_a & 0x7ff));
			data &= ~0x18;
			data |= 0x08; /* p1 */
			ocp_reg_ग_लिखो(tp, 0xd068, data);
			swap_a = ocp_reg_पढ़ो(tp, 0xd06a);
			data &= ~0x18;
			data |= 0x10; /* p2 */
			ocp_reg_ग_लिखो(tp, 0xd068, data);
			swap_b = ocp_reg_पढ़ो(tp, 0xd06a);
			data &= ~0x18;
			data |= 0x08; /* p1 */
			ocp_reg_ग_लिखो(tp, 0xd068, data);
			ocp_reg_ग_लिखो(tp, 0xd06a,
				      (swap_a & ~0x7ff) | (swap_b & 0x7ff));
			data &= ~0x18;
			data |= 0x10; /* p2 */
			ocp_reg_ग_लिखो(tp, 0xd068, data);
			ocp_reg_ग_लिखो(tp, 0xd06a,
				      (swap_b & ~0x7ff) | (swap_a & 0x7ff));
			swap_a = ocp_reg_पढ़ो(tp, 0xbd5a);
			swap_b = ocp_reg_पढ़ो(tp, 0xbd5c);
			ocp_reg_ग_लिखो(tp, 0xbd5a, (swap_a & ~0x1f1f) |
				      ((swap_b & 0x1f) << 8) |
				      ((swap_b >> 8) & 0x1f));
			ocp_reg_ग_लिखो(tp, 0xbd5c, (swap_b & ~0x1f1f) |
				      ((swap_a & 0x1f) << 8) |
				      ((swap_a >> 8) & 0x1f));
			swap_a = ocp_reg_पढ़ो(tp, 0xbc18);
			swap_b = ocp_reg_पढ़ो(tp, 0xbc1a);
			ocp_reg_ग_लिखो(tp, 0xbc18, (swap_a & ~0x1f1f) |
				      ((swap_b & 0x1f) << 8) |
				      ((swap_b >> 8) & 0x1f));
			ocp_reg_ग_लिखो(tp, 0xbc1a, (swap_b & ~0x1f1f) |
				      ((swap_a & 0x1f) << 8) |
				      ((swap_a >> 8) & 0x1f));
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rtl_green_en(tp, test_bit(GREEN_ETHERNET, &tp->flags));

	data = ocp_reg_पढ़ो(tp, 0xa428);
	data &= ~BIT(9);
	ocp_reg_ग_लिखो(tp, 0xa428, data);
	data = ocp_reg_पढ़ो(tp, 0xa5ea);
	data &= ~BIT(0);
	ocp_reg_ग_लिखो(tp, 0xa5ea, data);
	tp->ups_info.lite_mode = 0;

	अगर (tp->eee_en)
		rtl_eee_enable(tp, true);

	r8153_aldps_en(tp, true);
	r8152b_enable_fc(tp);
	r8153_u2p3en(tp, true);

	set_bit(PHY_RESET, &tp->flags);
पूर्ण

अटल व्योम r8156b_hw_phy_cfg(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 data;

	चयन (tp->version) अणु
	हाल RTL_VER_12:
		ocp_reg_ग_लिखो(tp, 0xbf86, 0x9000);
		data = ocp_reg_पढ़ो(tp, 0xc402);
		data |= BIT(10);
		ocp_reg_ग_लिखो(tp, 0xc402, data);
		data &= ~BIT(10);
		ocp_reg_ग_लिखो(tp, 0xc402, data);
		ocp_reg_ग_लिखो(tp, 0xbd86, 0x1010);
		ocp_reg_ग_लिखो(tp, 0xbd88, 0x1010);
		data = ocp_reg_पढ़ो(tp, 0xbd4e);
		data &= ~(BIT(10) | BIT(11));
		data |= BIT(11);
		ocp_reg_ग_लिखो(tp, 0xbd4e, data);
		data = ocp_reg_पढ़ो(tp, 0xbf46);
		data &= ~0xf00;
		data |= 0x700;
		ocp_reg_ग_लिखो(tp, 0xbf46, data);
		अवरोध;
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		r8156b_रुको_loading_flash(tp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_MISC_0);
	अगर (ocp_data & PCUT_STATUS) अणु
		ocp_data &= ~PCUT_STATUS;
		ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_MISC_0, ocp_data);
	पूर्ण

	data = r8153_phy_status(tp, 0);
	चयन (data) अणु
	हाल PHY_STAT_EXT_INIT:
		rtl8152_apply_firmware(tp, true);

		data = ocp_reg_पढ़ो(tp, 0xa466);
		data &= ~BIT(0);
		ocp_reg_ग_लिखो(tp, 0xa466, data);

		data = ocp_reg_पढ़ो(tp, 0xa468);
		data &= ~(BIT(3) | BIT(1));
		ocp_reg_ग_लिखो(tp, 0xa468, data);
		अवरोध;
	हाल PHY_STAT_LAN_ON:
	हाल PHY_STAT_PWRDN:
	शेष:
		rtl8152_apply_firmware(tp, false);
		अवरोध;
	पूर्ण

	data = r8152_mdio_पढ़ो(tp, MII_BMCR);
	अगर (data & BMCR_PDOWN) अणु
		data &= ~BMCR_PDOWN;
		r8152_mdio_ग_लिखो(tp, MII_BMCR, data);
	पूर्ण

	/* disable ALDPS beक्रमe updating the PHY parameters */
	r8153_aldps_en(tp, false);

	/* disable EEE beक्रमe updating the PHY parameters */
	rtl_eee_enable(tp, false);

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);
	WARN_ON_ONCE(data != PHY_STAT_LAN_ON);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= PFM_PWM_SWITCH;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);

	चयन (tp->version) अणु
	हाल RTL_VER_12:
		data = ocp_reg_पढ़ो(tp, 0xbc08);
		data |= BIT(3) | BIT(2);
		ocp_reg_ग_लिखो(tp, 0xbc08, data);

		data = sram_पढ़ो(tp, 0x8fff);
		data &= ~0xff00;
		data |= 0x0400;
		sram_ग_लिखो(tp, 0x8fff, data);

		data = ocp_reg_पढ़ो(tp, 0xacda);
		data |= 0xff00;
		ocp_reg_ग_लिखो(tp, 0xacda, data);
		data = ocp_reg_पढ़ो(tp, 0xacde);
		data |= 0xf000;
		ocp_reg_ग_लिखो(tp, 0xacde, data);
		ocp_reg_ग_लिखो(tp, 0xac8c, 0x0ffc);
		ocp_reg_ग_लिखो(tp, 0xac46, 0xb7b4);
		ocp_reg_ग_लिखो(tp, 0xac50, 0x0fbc);
		ocp_reg_ग_लिखो(tp, 0xac3c, 0x9240);
		ocp_reg_ग_लिखो(tp, 0xac4e, 0x0db4);
		ocp_reg_ग_लिखो(tp, 0xacc6, 0x0707);
		ocp_reg_ग_लिखो(tp, 0xacc8, 0xa0d3);
		ocp_reg_ग_लिखो(tp, 0xad08, 0x0007);

		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8560);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x19cc);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8562);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x19cc);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8564);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x19cc);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8566);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x147d);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8568);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x147d);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x856a);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x147d);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8ffe);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0907);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x80d6);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x2801);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x80f2);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x2801);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x80f4);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x6077);
		ocp_reg_ग_लिखो(tp, 0xb506, 0x01e7);

		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8013);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0700);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fb9);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x2801);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fba);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0100);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fbc);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x1900);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fbe);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xe100);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fc0);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0800);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fc2);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xe500);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fc4);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0f00);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fc6);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xf100);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fc8);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0400);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fca);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xf300);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fcc);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xfd00);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fce);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xff00);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fd0);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xfb00);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fd2);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0100);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fd4);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xf400);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fd6);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xff00);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8fd8);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xf600);

		ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA, PLA_USB_CFG);
		ocp_data |= EN_XG_LIP | EN_G_LIP;
		ocp_ग_लिखो_byte(tp, MCU_TYPE_PLA, PLA_USB_CFG, ocp_data);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x813d);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x390e);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x814f);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x790e);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x80b0);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0f31);
		data = ocp_reg_पढ़ो(tp, 0xbf4c);
		data |= BIT(1);
		ocp_reg_ग_लिखो(tp, 0xbf4c, data);
		data = ocp_reg_पढ़ो(tp, 0xbcca);
		data |= BIT(9) | BIT(8);
		ocp_reg_ग_लिखो(tp, 0xbcca, data);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8141);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x320e);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8153);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x720e);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8529);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x050e);
		data = ocp_reg_पढ़ो(tp, OCP_EEE_CFG);
		data &= ~CTAP_SHORT_EN;
		ocp_reg_ग_लिखो(tp, OCP_EEE_CFG, data);

		sram_ग_लिखो(tp, 0x816c, 0xc4a0);
		sram_ग_लिखो(tp, 0x8170, 0xc4a0);
		sram_ग_लिखो(tp, 0x8174, 0x04a0);
		sram_ग_लिखो(tp, 0x8178, 0x04a0);
		sram_ग_लिखो(tp, 0x817c, 0x0719);
		sram_ग_लिखो(tp, 0x8ff4, 0x0400);
		sram_ग_लिखो(tp, 0x8ff1, 0x0404);

		ocp_reg_ग_लिखो(tp, 0xbf4a, 0x001b);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8033);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x7c13);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8037);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x7c13);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x803b);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0xfc32);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x803f);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x7c13);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8043);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x7c13);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8047);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x7c13);

		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8145);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x370e);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8157);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x770e);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8169);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x0d0a);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x817b);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x1d0a);

		data = sram_पढ़ो(tp, 0x8217);
		data &= ~0xff00;
		data |= 0x5000;
		sram_ग_लिखो(tp, 0x8217, data);
		data = sram_पढ़ो(tp, 0x821a);
		data &= ~0xff00;
		data |= 0x5000;
		sram_ग_लिखो(tp, 0x821a, data);
		sram_ग_लिखो(tp, 0x80da, 0x0403);
		data = sram_पढ़ो(tp, 0x80dc);
		data &= ~0xff00;
		data |= 0x1000;
		sram_ग_लिखो(tp, 0x80dc, data);
		sram_ग_लिखो(tp, 0x80b3, 0x0384);
		sram_ग_लिखो(tp, 0x80b7, 0x2007);
		data = sram_पढ़ो(tp, 0x80ba);
		data &= ~0xff00;
		data |= 0x6c00;
		sram_ग_लिखो(tp, 0x80ba, data);
		sram_ग_लिखो(tp, 0x80b5, 0xf009);
		data = sram_पढ़ो(tp, 0x80bd);
		data &= ~0xff00;
		data |= 0x9f00;
		sram_ग_लिखो(tp, 0x80bd, data);
		sram_ग_लिखो(tp, 0x80c7, 0xf083);
		sram_ग_लिखो(tp, 0x80dd, 0x03f0);
		data = sram_पढ़ो(tp, 0x80df);
		data &= ~0xff00;
		data |= 0x1000;
		sram_ग_लिखो(tp, 0x80df, data);
		sram_ग_लिखो(tp, 0x80cb, 0x2007);
		data = sram_पढ़ो(tp, 0x80ce);
		data &= ~0xff00;
		data |= 0x6c00;
		sram_ग_लिखो(tp, 0x80ce, data);
		sram_ग_लिखो(tp, 0x80c9, 0x8009);
		data = sram_पढ़ो(tp, 0x80d1);
		data &= ~0xff00;
		data |= 0x8000;
		sram_ग_लिखो(tp, 0x80d1, data);
		sram_ग_लिखो(tp, 0x80a3, 0x200a);
		sram_ग_लिखो(tp, 0x80a5, 0xf0ad);
		sram_ग_लिखो(tp, 0x809f, 0x6073);
		sram_ग_लिखो(tp, 0x80a1, 0x000b);
		data = sram_पढ़ो(tp, 0x80a9);
		data &= ~0xff00;
		data |= 0xc000;
		sram_ग_लिखो(tp, 0x80a9, data);

		अगर (rtl_phy_patch_request(tp, true, true))
			वापस;

		data = ocp_reg_पढ़ो(tp, 0xb896);
		data &= ~BIT(0);
		ocp_reg_ग_लिखो(tp, 0xb896, data);
		data = ocp_reg_पढ़ो(tp, 0xb892);
		data &= ~0xff00;
		ocp_reg_ग_लिखो(tp, 0xb892, data);
		ocp_reg_ग_लिखो(tp, 0xb88e, 0xc23e);
		ocp_reg_ग_लिखो(tp, 0xb890, 0x0000);
		ocp_reg_ग_लिखो(tp, 0xb88e, 0xc240);
		ocp_reg_ग_लिखो(tp, 0xb890, 0x0103);
		ocp_reg_ग_लिखो(tp, 0xb88e, 0xc242);
		ocp_reg_ग_लिखो(tp, 0xb890, 0x0507);
		ocp_reg_ग_लिखो(tp, 0xb88e, 0xc244);
		ocp_reg_ग_लिखो(tp, 0xb890, 0x090b);
		ocp_reg_ग_लिखो(tp, 0xb88e, 0xc246);
		ocp_reg_ग_लिखो(tp, 0xb890, 0x0c0e);
		ocp_reg_ग_लिखो(tp, 0xb88e, 0xc248);
		ocp_reg_ग_लिखो(tp, 0xb890, 0x1012);
		ocp_reg_ग_लिखो(tp, 0xb88e, 0xc24a);
		ocp_reg_ग_लिखो(tp, 0xb890, 0x1416);
		data = ocp_reg_पढ़ो(tp, 0xb896);
		data |= BIT(0);
		ocp_reg_ग_लिखो(tp, 0xb896, data);

		rtl_phy_patch_request(tp, false, true);

		data = ocp_reg_पढ़ो(tp, 0xa86a);
		data |= BIT(0);
		ocp_reg_ग_लिखो(tp, 0xa86a, data);
		data = ocp_reg_पढ़ो(tp, 0xa6f0);
		data |= BIT(0);
		ocp_reg_ग_लिखो(tp, 0xa6f0, data);

		ocp_reg_ग_लिखो(tp, 0xbfa0, 0xd70d);
		ocp_reg_ग_लिखो(tp, 0xbfa2, 0x4100);
		ocp_reg_ग_लिखो(tp, 0xbfa4, 0xe868);
		ocp_reg_ग_लिखो(tp, 0xbfa6, 0xdc59);
		ocp_reg_ग_लिखो(tp, 0xb54c, 0x3c18);
		data = ocp_reg_पढ़ो(tp, 0xbfa4);
		data &= ~BIT(5);
		ocp_reg_ग_लिखो(tp, 0xbfa4, data);
		data = sram_पढ़ो(tp, 0x817d);
		data |= BIT(12);
		sram_ग_लिखो(tp, 0x817d, data);
		अवरोध;
	हाल RTL_VER_13:
		/* 2.5G INRX */
		data = ocp_reg_पढ़ो(tp, 0xac46);
		data &= ~0x00f0;
		data |= 0x0090;
		ocp_reg_ग_लिखो(tp, 0xac46, data);
		data = ocp_reg_पढ़ो(tp, 0xad30);
		data &= ~0x0003;
		data |= 0x0001;
		ocp_reg_ग_लिखो(tp, 0xad30, data);
		fallthrough;
	हाल RTL_VER_15:
		/* EEE parameter */
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x80f5);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x760e);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8107);
		ocp_reg_ग_लिखो(tp, 0xb87e, 0x360e);
		ocp_reg_ग_लिखो(tp, 0xb87c, 0x8551);
		data = ocp_reg_पढ़ो(tp, 0xb87e);
		data &= ~0xff00;
		data |= 0x0800;
		ocp_reg_ग_लिखो(tp, 0xb87e, data);

		/* ADC_PGA parameter */
		data = ocp_reg_पढ़ो(tp, 0xbf00);
		data &= ~0xe000;
		data |= 0xa000;
		ocp_reg_ग_लिखो(tp, 0xbf00, data);
		data = ocp_reg_पढ़ो(tp, 0xbf46);
		data &= ~0x0f00;
		data |= 0x0300;
		ocp_reg_ग_लिखो(tp, 0xbf46, data);

		/* Green Table-PGA, 1G full viterbi */
		sram_ग_लिखो(tp, 0x8044, 0x2417);
		sram_ग_लिखो(tp, 0x804a, 0x2417);
		sram_ग_लिखो(tp, 0x8050, 0x2417);
		sram_ग_लिखो(tp, 0x8056, 0x2417);
		sram_ग_लिखो(tp, 0x805c, 0x2417);
		sram_ग_लिखो(tp, 0x8062, 0x2417);
		sram_ग_लिखो(tp, 0x8068, 0x2417);
		sram_ग_लिखो(tp, 0x806e, 0x2417);
		sram_ग_लिखो(tp, 0x8074, 0x2417);
		sram_ग_लिखो(tp, 0x807a, 0x2417);

		/* XG PLL */
		data = ocp_reg_पढ़ो(tp, 0xbf84);
		data &= ~0xe000;
		data |= 0xa000;
		ocp_reg_ग_लिखो(tp, 0xbf84, data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (rtl_phy_patch_request(tp, true, true))
		वापस;

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
	ocp_data |= EEE_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);

	data = ocp_reg_पढ़ो(tp, OCP_DOWN_SPEED);
	data &= ~(EN_EEE_100 | EN_EEE_1000);
	data |= EN_10M_CLKDIV;
	ocp_reg_ग_लिखो(tp, OCP_DOWN_SPEED, data);
	tp->ups_info._10m_ckभाग = true;
	tp->ups_info.eee_plloff_100 = false;
	tp->ups_info.eee_plloff_giga = false;

	data = ocp_reg_पढ़ो(tp, OCP_POWER_CFG);
	data &= ~EEE_CLKDIV_EN;
	ocp_reg_ग_लिखो(tp, OCP_POWER_CFG, data);
	tp->ups_info.eee_ckभाग = false;

	rtl_phy_patch_request(tp, false, true);

	rtl_green_en(tp, test_bit(GREEN_ETHERNET, &tp->flags));

	data = ocp_reg_पढ़ो(tp, 0xa428);
	data &= ~BIT(9);
	ocp_reg_ग_लिखो(tp, 0xa428, data);
	data = ocp_reg_पढ़ो(tp, 0xa5ea);
	data &= ~BIT(0);
	ocp_reg_ग_लिखो(tp, 0xa5ea, data);
	tp->ups_info.lite_mode = 0;

	अगर (tp->eee_en)
		rtl_eee_enable(tp, true);

	r8153_aldps_en(tp, true);
	r8152b_enable_fc(tp);
	r8153_u2p3en(tp, true);

	set_bit(PHY_RESET, &tp->flags);
पूर्ण

अटल व्योम r8156_init(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 data;
	पूर्णांक i;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_ECM_OP);
	ocp_data &= ~EN_ALL_SPEED;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_ECM_OP, ocp_data);

	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_SPEED_OPTION, 0);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_ECM_OPTION);
	ocp_data |= BYPASS_MAC_RESET;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_ECM_OPTION, ocp_data);

	r8153b_u1u2en(tp, false);

	क्रम (i = 0; i < 500; i++) अणु
		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			अवरोध;

		msleep(20);
		अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
			वापस;
	पूर्ण

	data = r8153_phy_status(tp, 0);
	अगर (data == PHY_STAT_EXT_INIT) अणु
		data = ocp_reg_पढ़ो(tp, 0xa468);
		data &= ~(BIT(3) | BIT(1));
		ocp_reg_ग_लिखो(tp, 0xa468, data);
	पूर्ण

	data = r8152_mdio_पढ़ो(tp, MII_BMCR);
	अगर (data & BMCR_PDOWN) अणु
		data &= ~BMCR_PDOWN;
		r8152_mdio_ग_लिखो(tp, MII_BMCR, data);
	पूर्ण

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);
	WARN_ON_ONCE(data != PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	/* MSC समयr = 0xfff * 8ms = 32760 ms */
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_MSC_TIMER, 0x0fff);

	/* U1/U2/L1 idle समयr. 500 us */
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_U1U2_TIMER, 500);

	r8153b_घातer_cut_en(tp, false);
	r8156_ups_en(tp, false);
	r8153_queue_wake(tp, false);
	rtl_runसमय_suspend_enable(tp, false);

	अगर (tp->udev->speed >= USB_SPEED_SUPER)
		r8153b_u1u2en(tp, true);

	usb_enable_lpm(tp->udev);

	r8156_mac_clk_spd(tp, true);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3);
	ocp_data &= ~PLA_MCU_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	अगर (rtl8152_get_speed(tp) & LINK_STATUS)
		ocp_data |= CUR_LINK_OK;
	अन्यथा
		ocp_data &= ~CUR_LINK_OK;
	ocp_data |= POLL_LINK_CHG;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);

	set_bit(GREEN_ETHERNET, &tp->flags);

	/* rx aggregation */
	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_BMU_CONFIG);
	ocp_data |= ACT_ODMA;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_BMU_CONFIG, ocp_data);

	rtl_tally_reset(tp);

	tp->coalesce = 15000;	/* 15 us */
पूर्ण

अटल व्योम r8156b_init(काष्ठा r8152 *tp)
अणु
	u32 ocp_data;
	u16 data;
	पूर्णांक i;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_USB, USB_ECM_OP);
	ocp_data &= ~EN_ALL_SPEED;
	ocp_ग_लिखो_byte(tp, MCU_TYPE_USB, USB_ECM_OP, ocp_data);

	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_SPEED_OPTION, 0);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_ECM_OPTION);
	ocp_data |= BYPASS_MAC_RESET;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_ECM_OPTION, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_U2P3_CTRL);
	ocp_data |= RX_DETECT8;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_U2P3_CTRL, ocp_data);

	r8153b_u1u2en(tp, false);

	चयन (tp->version) अणु
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		r8156b_रुको_loading_flash(tp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < 500; i++) अणु
		अगर (ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			अवरोध;

		msleep(20);
		अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
			वापस;
	पूर्ण

	data = r8153_phy_status(tp, 0);
	अगर (data == PHY_STAT_EXT_INIT) अणु
		data = ocp_reg_पढ़ो(tp, 0xa468);
		data &= ~(BIT(3) | BIT(1));
		ocp_reg_ग_लिखो(tp, 0xa468, data);

		data = ocp_reg_पढ़ो(tp, 0xa466);
		data &= ~BIT(0);
		ocp_reg_ग_लिखो(tp, 0xa466, data);
	पूर्ण

	data = r8152_mdio_पढ़ो(tp, MII_BMCR);
	अगर (data & BMCR_PDOWN) अणु
		data &= ~BMCR_PDOWN;
		r8152_mdio_ग_लिखो(tp, MII_BMCR, data);
	पूर्ण

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	/* MSC समयr = 0xfff * 8ms = 32760 ms */
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_MSC_TIMER, 0x0fff);

	/* U1/U2/L1 idle समयr. 500 us */
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_U1U2_TIMER, 500);

	r8153b_घातer_cut_en(tp, false);
	r8156_ups_en(tp, false);
	r8153_queue_wake(tp, false);
	rtl_runसमय_suspend_enable(tp, false);

	अगर (tp->udev->speed >= USB_SPEED_SUPER)
		r8153b_u1u2en(tp, true);

	usb_enable_lpm(tp->udev);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~SLOT_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_CPCR);
	ocp_data |= FLOW_CTRL_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_CPCR, ocp_data);

	/* enable fc समयr and set समयr to 600 ms. */
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FC_TIMER,
		       CTRL_TIMER_EN | (600 / 8));

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_CTRL);
	अगर (!(ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_POL_GPIO_CTRL) & DACK_DET_EN))
		ocp_data |= FLOW_CTRL_PATCH_2;
	ocp_data &= ~AUTO_SPEEDUP;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_CTRL, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_FW_TASK);
	ocp_data |= FC_PATCH_TASK;
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);

	r8156_mac_clk_spd(tp, true);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3);
	ocp_data &= ~PLA_MCU_SPDWN_EN;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3, ocp_data);

	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	अगर (rtl8152_get_speed(tp) & LINK_STATUS)
		ocp_data |= CUR_LINK_OK;
	अन्यथा
		ocp_data &= ~CUR_LINK_OK;
	ocp_data |= POLL_LINK_CHG;
	ocp_ग_लिखो_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);

	set_bit(GREEN_ETHERNET, &tp->flags);

	/* rx aggregation */
	ocp_data = ocp_पढ़ो_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_ग_लिखो_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	rtl_tally_reset(tp);

	tp->coalesce = 15000;	/* 15 us */
पूर्ण

अटल bool rtl_check_venकरोr_ok(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *in, *out, *पूर्णांकr;

	अगर (usb_find_common_endpoपूर्णांकs(alt, &in, &out, &पूर्णांकr, शून्य) < 0) अणु
		dev_err(&पूर्णांकf->dev, "Expected endpoints are not found\n");
		वापस false;
	पूर्ण

	/* Check Rx endpoपूर्णांक address */
	अगर (usb_endpoपूर्णांक_num(in) != 1) अणु
		dev_err(&पूर्णांकf->dev, "Invalid Rx endpoint address\n");
		वापस false;
	पूर्ण

	/* Check Tx endpoपूर्णांक address */
	अगर (usb_endpoपूर्णांक_num(out) != 2) अणु
		dev_err(&पूर्णांकf->dev, "Invalid Tx endpoint address\n");
		वापस false;
	पूर्ण

	/* Check पूर्णांकerrupt endpoपूर्णांक address */
	अगर (usb_endpoपूर्णांक_num(पूर्णांकr) != 3) अणु
		dev_err(&पूर्णांकf->dev, "Invalid interrupt endpoint address\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool rtl_venकरोr_mode(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;
	काष्ठा usb_device *udev;
	काष्ठा usb_host_config *c;
	पूर्णांक i, num_configs;

	अगर (alt->desc.bInterfaceClass == USB_CLASS_VENDOR_SPEC)
		वापस rtl_check_venकरोr_ok(पूर्णांकf);

	/* The venकरोr mode is not always config #1, so to find it out. */
	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	c = udev->config;
	num_configs = udev->descriptor.bNumConfigurations;
	अगर (num_configs < 2)
		वापस false;

	क्रम (i = 0; i < num_configs; (i++, c++)) अणु
		काष्ठा usb_पूर्णांकerface_descriptor	*desc = शून्य;

		अगर (c->desc.bNumInterfaces > 0)
			desc = &c->पूर्णांकf_cache[0]->altsetting->desc;
		अन्यथा
			जारी;

		अगर (desc->bInterfaceClass == USB_CLASS_VENDOR_SPEC) अणु
			usb_driver_set_configuration(udev, c->desc.bConfigurationValue);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == num_configs)
		dev_err(&पूर्णांकf->dev, "Unexpected Device\n");

	वापस false;
पूर्ण

अटल पूर्णांक rtl8152_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा r8152 *tp = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा net_device *netdev;

	अगर (!tp)
		वापस 0;

	netdev = tp->netdev;
	अगर (!netअगर_running(netdev))
		वापस 0;

	netअगर_stop_queue(netdev);
	tasklet_disable(&tp->tx_tl);
	clear_bit(WORK_ENABLE, &tp->flags);
	usb_समाप्त_urb(tp->पूर्णांकr_urb);
	cancel_delayed_work_sync(&tp->schedule);
	napi_disable(&tp->napi);
	अगर (netअगर_carrier_ok(netdev)) अणु
		mutex_lock(&tp->control);
		tp->rtl_ops.disable(tp);
		mutex_unlock(&tp->control);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8152_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा r8152 *tp = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा net_device *netdev;
	काष्ठा sockaddr sa;

	अगर (!tp)
		वापस 0;

	/* reset the MAC adddress in हाल of policy change */
	अगर (determine_ethernet_addr(tp, &sa) >= 0) अणु
		rtnl_lock();
		dev_set_mac_address (tp->netdev, &sa, शून्य);
		rtnl_unlock();
	पूर्ण

	netdev = tp->netdev;
	अगर (!netअगर_running(netdev))
		वापस 0;

	set_bit(WORK_ENABLE, &tp->flags);
	अगर (netअगर_carrier_ok(netdev)) अणु
		mutex_lock(&tp->control);
		tp->rtl_ops.enable(tp);
		rtl_start_rx(tp);
		_rtl8152_set_rx_mode(netdev);
		mutex_unlock(&tp->control);
	पूर्ण

	napi_enable(&tp->napi);
	tasklet_enable(&tp->tx_tl);
	netअगर_wake_queue(netdev);
	usb_submit_urb(tp->पूर्णांकr_urb, GFP_KERNEL);

	अगर (!list_empty(&tp->rx_करोne))
		napi_schedule(&tp->napi);

	वापस 0;
पूर्ण

अटल bool delay_स्वतःsuspend(काष्ठा r8152 *tp)
अणु
	bool sw_linking = !!netअगर_carrier_ok(tp->netdev);
	bool hw_linking = !!(rtl8152_get_speed(tp) & LINK_STATUS);

	/* This means a linking change occurs and the driver करोesn't detect it,
	 * yet. If the driver has disabled tx/rx and hw is linking on, the
	 * device wouldn't wake up by receiving any packet.
	 */
	अगर (work_busy(&tp->schedule.work) || sw_linking != hw_linking)
		वापस true;

	/* If the linking करोwn is occurred by nway, the device may miss the
	 * linking change event. And it wouldn't wake when linking on.
	 */
	अगर (!sw_linking && tp->rtl_ops.in_nway(tp))
		वापस true;
	अन्यथा अगर (!skb_queue_empty(&tp->tx_queue))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक rtl8152_runसमय_resume(काष्ठा r8152 *tp)
अणु
	काष्ठा net_device *netdev = tp->netdev;

	अगर (netअगर_running(netdev) && netdev->flags & IFF_UP) अणु
		काष्ठा napi_काष्ठा *napi = &tp->napi;

		tp->rtl_ops.स्वतःsuspend_en(tp, false);
		napi_disable(napi);
		set_bit(WORK_ENABLE, &tp->flags);

		अगर (netअगर_carrier_ok(netdev)) अणु
			अगर (rtl8152_get_speed(tp) & LINK_STATUS) अणु
				rtl_start_rx(tp);
			पूर्ण अन्यथा अणु
				netअगर_carrier_off(netdev);
				tp->rtl_ops.disable(tp);
				netअगर_info(tp, link, netdev, "linking down\n");
			पूर्ण
		पूर्ण

		napi_enable(napi);
		clear_bit(SELECTIVE_SUSPEND, &tp->flags);
		smp_mb__after_atomic();

		अगर (!list_empty(&tp->rx_करोne))
			napi_schedule(&tp->napi);

		usb_submit_urb(tp->पूर्णांकr_urb, GFP_NOIO);
	पूर्ण अन्यथा अणु
		अगर (netdev->flags & IFF_UP)
			tp->rtl_ops.स्वतःsuspend_en(tp, false);

		clear_bit(SELECTIVE_SUSPEND, &tp->flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8152_प्रणाली_resume(काष्ठा r8152 *tp)
अणु
	काष्ठा net_device *netdev = tp->netdev;

	netअगर_device_attach(netdev);

	अगर (netअगर_running(netdev) && (netdev->flags & IFF_UP)) अणु
		tp->rtl_ops.up(tp);
		netअगर_carrier_off(netdev);
		set_bit(WORK_ENABLE, &tp->flags);
		usb_submit_urb(tp->पूर्णांकr_urb, GFP_NOIO);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8152_runसमय_suspend(काष्ठा r8152 *tp)
अणु
	काष्ठा net_device *netdev = tp->netdev;
	पूर्णांक ret = 0;

	अगर (!tp->rtl_ops.स्वतःsuspend_en)
		वापस -EBUSY;

	set_bit(SELECTIVE_SUSPEND, &tp->flags);
	smp_mb__after_atomic();

	अगर (netअगर_running(netdev) && test_bit(WORK_ENABLE, &tp->flags)) अणु
		u32 rcr = 0;

		अगर (netअगर_carrier_ok(netdev)) अणु
			u32 ocp_data;

			rcr = ocp_पढ़ो_dword(tp, MCU_TYPE_PLA, PLA_RCR);
			ocp_data = rcr & ~RCR_ACPT_ALL;
			ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
			rxdy_gated_en(tp, true);
			ocp_data = ocp_पढ़ो_byte(tp, MCU_TYPE_PLA,
						 PLA_OOB_CTRL);
			अगर (!(ocp_data & RXFIFO_EMPTY)) अणु
				rxdy_gated_en(tp, false);
				ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, rcr);
				clear_bit(SELECTIVE_SUSPEND, &tp->flags);
				smp_mb__after_atomic();
				ret = -EBUSY;
				जाओ out1;
			पूर्ण
		पूर्ण

		clear_bit(WORK_ENABLE, &tp->flags);
		usb_समाप्त_urb(tp->पूर्णांकr_urb);

		tp->rtl_ops.स्वतःsuspend_en(tp, true);

		अगर (netअगर_carrier_ok(netdev)) अणु
			काष्ठा napi_काष्ठा *napi = &tp->napi;

			napi_disable(napi);
			rtl_stop_rx(tp);
			rxdy_gated_en(tp, false);
			ocp_ग_लिखो_dword(tp, MCU_TYPE_PLA, PLA_RCR, rcr);
			napi_enable(napi);
		पूर्ण

		अगर (delay_स्वतःsuspend(tp)) अणु
			rtl8152_runसमय_resume(tp);
			ret = -EBUSY;
		पूर्ण
	पूर्ण

out1:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8152_प्रणाली_suspend(काष्ठा r8152 *tp)
अणु
	काष्ठा net_device *netdev = tp->netdev;

	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev) && test_bit(WORK_ENABLE, &tp->flags)) अणु
		काष्ठा napi_काष्ठा *napi = &tp->napi;

		clear_bit(WORK_ENABLE, &tp->flags);
		usb_समाप्त_urb(tp->पूर्णांकr_urb);
		tasklet_disable(&tp->tx_tl);
		napi_disable(napi);
		cancel_delayed_work_sync(&tp->schedule);
		tp->rtl_ops.करोwn(tp);
		napi_enable(napi);
		tasklet_enable(&tp->tx_tl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8152_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा r8152 *tp = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक ret;

	mutex_lock(&tp->control);

	अगर (PMSG_IS_AUTO(message))
		ret = rtl8152_runसमय_suspend(tp);
	अन्यथा
		ret = rtl8152_प्रणाली_suspend(tp);

	mutex_unlock(&tp->control);

	वापस ret;
पूर्ण

अटल पूर्णांक rtl8152_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा r8152 *tp = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक ret;

	mutex_lock(&tp->control);

	अगर (test_bit(SELECTIVE_SUSPEND, &tp->flags))
		ret = rtl8152_runसमय_resume(tp);
	अन्यथा
		ret = rtl8152_प्रणाली_resume(tp);

	mutex_unlock(&tp->control);

	वापस ret;
पूर्ण

अटल पूर्णांक rtl8152_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा r8152 *tp = usb_get_पूर्णांकfdata(पूर्णांकf);

	clear_bit(SELECTIVE_SUSPEND, &tp->flags);
	tp->rtl_ops.init(tp);
	queue_delayed_work(प्रणाली_दीर्घ_wq, &tp->hw_phy_work, 0);
	set_ethernet_addr(tp);
	वापस rtl8152_resume(पूर्णांकf);
पूर्ण

अटल व्योम rtl8152_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा r8152 *tp = netdev_priv(dev);

	अगर (usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf) < 0)
		वापस;

	अगर (!rtl_can_wakeup(tp)) अणु
		wol->supported = 0;
		wol->wolopts = 0;
	पूर्ण अन्यथा अणु
		mutex_lock(&tp->control);
		wol->supported = WAKE_ANY;
		wol->wolopts = __rtl_get_wol(tp);
		mutex_unlock(&tp->control);
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);
पूर्ण

अटल पूर्णांक rtl8152_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा r8152 *tp = netdev_priv(dev);
	पूर्णांक ret;

	अगर (!rtl_can_wakeup(tp))
		वापस -EOPNOTSUPP;

	अगर (wol->wolopts & ~WAKE_ANY)
		वापस -EINVAL;

	ret = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (ret < 0)
		जाओ out_set_wol;

	mutex_lock(&tp->control);

	__rtl_set_wol(tp, wol->wolopts);
	tp->saved_wolopts = wol->wolopts & WAKE_ANY;

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

out_set_wol:
	वापस ret;
पूर्ण

अटल u32 rtl8152_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा r8152 *tp = netdev_priv(dev);

	वापस tp->msg_enable;
पूर्ण

अटल व्योम rtl8152_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा r8152 *tp = netdev_priv(dev);

	tp->msg_enable = value;
पूर्ण

अटल व्योम rtl8152_get_drvinfo(काष्ठा net_device *netdev,
				काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);

	strlcpy(info->driver, MODULENAME, माप(info->driver));
	strlcpy(info->version, DRIVER_VERSION, माप(info->version));
	usb_make_path(tp->udev, info->bus_info, माप(info->bus_info));
	अगर (!IS_ERR_OR_शून्य(tp->rtl_fw.fw))
		strlcpy(info->fw_version, tp->rtl_fw.version,
			माप(info->fw_version));
पूर्ण

अटल
पूर्णांक rtl8152_get_link_ksettings(काष्ठा net_device *netdev,
			       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);
	पूर्णांक ret;

	अगर (!tp->mii.mdio_पढ़ो)
		वापस -EOPNOTSUPP;

	ret = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (ret < 0)
		जाओ out;

	mutex_lock(&tp->control);

	mii_ethtool_get_link_ksettings(&tp->mii, cmd);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
			 cmd->link_modes.supported, tp->support_2500full);

	अगर (tp->support_2500full) अणु
		linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
				 cmd->link_modes.advertising,
				 ocp_reg_पढ़ो(tp, OCP_10GBT_CTRL) & MDIO_AN_10GBT_CTRL_ADV2_5G);

		linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
				 cmd->link_modes.lp_advertising,
				 ocp_reg_पढ़ो(tp, OCP_10GBT_STAT) & MDIO_AN_10GBT_STAT_LP2_5G);

		अगर (is_speed_2500(rtl8152_get_speed(tp)))
			cmd->base.speed = SPEED_2500;
	पूर्ण

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8152_set_link_ksettings(काष्ठा net_device *dev,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा r8152 *tp = netdev_priv(dev);
	u32 advertising = 0;
	पूर्णांक ret;

	ret = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (ret < 0)
		जाओ out;

	अगर (test_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_10_HALF;

	अगर (test_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_10_FULL;

	अगर (test_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_100_HALF;

	अगर (test_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_100_FULL;

	अगर (test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_1000_HALF;

	अगर (test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_1000_FULL;

	अगर (test_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_2500_FULL;

	mutex_lock(&tp->control);

	ret = rtl8152_set_speed(tp, cmd->base.स्वतःneg, cmd->base.speed,
				cmd->base.duplex, advertising);
	अगर (!ret) अणु
		tp->स्वतःneg = cmd->base.स्वतःneg;
		tp->speed = cmd->base.speed;
		tp->duplex = cmd->base.duplex;
		tp->advertising = advertising;
	पूर्ण

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

out:
	वापस ret;
पूर्ण

अटल स्थिर अक्षर rtl8152_gstrings[][ETH_GSTRING_LEN] = अणु
	"tx_packets",
	"rx_packets",
	"tx_errors",
	"rx_errors",
	"rx_missed",
	"align_errors",
	"tx_single_collisions",
	"tx_multi_collisions",
	"rx_unicast",
	"rx_broadcast",
	"rx_multicast",
	"tx_aborted",
	"tx_underrun",
पूर्ण;

अटल पूर्णांक rtl8152_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(rtl8152_gstrings);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम rtl8152_get_ethtool_stats(काष्ठा net_device *dev,
				      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा r8152 *tp = netdev_priv(dev);
	काष्ठा tally_counter tally;

	अगर (usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf) < 0)
		वापस;

	generic_ocp_पढ़ो(tp, PLA_TALLYCNT, माप(tally), &tally, MCU_TYPE_PLA);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

	data[0] = le64_to_cpu(tally.tx_packets);
	data[1] = le64_to_cpu(tally.rx_packets);
	data[2] = le64_to_cpu(tally.tx_errors);
	data[3] = le32_to_cpu(tally.rx_errors);
	data[4] = le16_to_cpu(tally.rx_missed);
	data[5] = le16_to_cpu(tally.align_errors);
	data[6] = le32_to_cpu(tally.tx_one_collision);
	data[7] = le32_to_cpu(tally.tx_multi_collision);
	data[8] = le64_to_cpu(tally.rx_unicast);
	data[9] = le64_to_cpu(tally.rx_broadcast);
	data[10] = le32_to_cpu(tally.rx_multicast);
	data[11] = le16_to_cpu(tally.tx_पातed);
	data[12] = le16_to_cpu(tally.tx_underrun);
पूर्ण

अटल व्योम rtl8152_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, rtl8152_gstrings, माप(rtl8152_gstrings));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक r8152_get_eee(काष्ठा r8152 *tp, काष्ठा ethtool_eee *eee)
अणु
	u32 lp, adv, supported = 0;
	u16 val;

	val = r8152_mmd_पढ़ो(tp, MDIO_MMD_PCS, MDIO_PCS_EEE_ABLE);
	supported = mmd_eee_cap_to_ethtool_sup_t(val);

	val = r8152_mmd_पढ़ो(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV);
	adv = mmd_eee_adv_to_ethtool_adv_t(val);

	val = r8152_mmd_पढ़ो(tp, MDIO_MMD_AN, MDIO_AN_EEE_LPABLE);
	lp = mmd_eee_adv_to_ethtool_adv_t(val);

	eee->eee_enabled = tp->eee_en;
	eee->eee_active = !!(supported & adv & lp);
	eee->supported = supported;
	eee->advertised = tp->eee_adv;
	eee->lp_advertised = lp;

	वापस 0;
पूर्ण

अटल पूर्णांक r8152_set_eee(काष्ठा r8152 *tp, काष्ठा ethtool_eee *eee)
अणु
	u16 val = ethtool_adv_to_mmd_eee_adv_t(eee->advertised);

	tp->eee_en = eee->eee_enabled;
	tp->eee_adv = val;

	rtl_eee_enable(tp, tp->eee_en);

	वापस 0;
पूर्ण

अटल पूर्णांक r8153_get_eee(काष्ठा r8152 *tp, काष्ठा ethtool_eee *eee)
अणु
	u32 lp, adv, supported = 0;
	u16 val;

	val = ocp_reg_पढ़ो(tp, OCP_EEE_ABLE);
	supported = mmd_eee_cap_to_ethtool_sup_t(val);

	val = ocp_reg_पढ़ो(tp, OCP_EEE_ADV);
	adv = mmd_eee_adv_to_ethtool_adv_t(val);

	val = ocp_reg_पढ़ो(tp, OCP_EEE_LPABLE);
	lp = mmd_eee_adv_to_ethtool_adv_t(val);

	eee->eee_enabled = tp->eee_en;
	eee->eee_active = !!(supported & adv & lp);
	eee->supported = supported;
	eee->advertised = tp->eee_adv;
	eee->lp_advertised = lp;

	वापस 0;
पूर्ण

अटल पूर्णांक
rtl_ethtool_get_eee(काष्ठा net_device *net, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा r8152 *tp = netdev_priv(net);
	पूर्णांक ret;

	अगर (!tp->rtl_ops.eee_get) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (ret < 0)
		जाओ out;

	mutex_lock(&tp->control);

	ret = tp->rtl_ops.eee_get(tp, edata);

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक
rtl_ethtool_set_eee(काष्ठा net_device *net, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा r8152 *tp = netdev_priv(net);
	पूर्णांक ret;

	अगर (!tp->rtl_ops.eee_set) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (ret < 0)
		जाओ out;

	mutex_lock(&tp->control);

	ret = tp->rtl_ops.eee_set(tp, edata);
	अगर (!ret)
		ret = mii_nway_restart(&tp->mii);

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8152_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा r8152 *tp = netdev_priv(dev);
	पूर्णांक ret;

	ret = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (ret < 0)
		जाओ out;

	mutex_lock(&tp->control);

	ret = mii_nway_restart(&tp->mii);

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8152_get_coalesce(काष्ठा net_device *netdev,
				काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);

	चयन (tp->version) अणु
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_07:
		वापस -EOPNOTSUPP;
	शेष:
		अवरोध;
	पूर्ण

	coalesce->rx_coalesce_usecs = tp->coalesce;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8152_set_coalesce(काष्ठा net_device *netdev,
				काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);
	पूर्णांक ret;

	चयन (tp->version) अणु
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_07:
		वापस -EOPNOTSUPP;
	शेष:
		अवरोध;
	पूर्ण

	अगर (coalesce->rx_coalesce_usecs > COALESCE_SLOW)
		वापस -EINVAL;

	ret = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&tp->control);

	अगर (tp->coalesce != coalesce->rx_coalesce_usecs) अणु
		tp->coalesce = coalesce->rx_coalesce_usecs;

		अगर (netअगर_running(netdev) && netअगर_carrier_ok(netdev)) अणु
			netअगर_stop_queue(netdev);
			napi_disable(&tp->napi);
			tp->rtl_ops.disable(tp);
			tp->rtl_ops.enable(tp);
			rtl_start_rx(tp);
			clear_bit(RTL8152_SET_RX_MODE, &tp->flags);
			_rtl8152_set_rx_mode(netdev);
			napi_enable(&tp->napi);
			netअगर_wake_queue(netdev);
		पूर्ण
	पूर्ण

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

	वापस ret;
पूर्ण

अटल पूर्णांक rtl8152_get_tunable(काष्ठा net_device *netdev,
			       स्थिर काष्ठा ethtool_tunable *tunable, व्योम *d)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);

	चयन (tunable->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)d = tp->rx_copyअवरोध;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8152_set_tunable(काष्ठा net_device *netdev,
			       स्थिर काष्ठा ethtool_tunable *tunable,
			       स्थिर व्योम *d)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);
	u32 val;

	चयन (tunable->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		val = *(u32 *)d;
		अगर (val < ETH_ZLEN) अणु
			netअगर_err(tp, rx_err, netdev,
				  "Invalid rx copy break value\n");
			वापस -EINVAL;
		पूर्ण

		अगर (tp->rx_copyअवरोध != val) अणु
			अगर (netdev->flags & IFF_UP) अणु
				mutex_lock(&tp->control);
				napi_disable(&tp->napi);
				tp->rx_copyअवरोध = val;
				napi_enable(&tp->napi);
				mutex_unlock(&tp->control);
			पूर्ण अन्यथा अणु
				tp->rx_copyअवरोध = val;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtl8152_get_ringparam(काष्ठा net_device *netdev,
				  काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);

	ring->rx_max_pending = RTL8152_RX_MAX_PENDING;
	ring->rx_pending = tp->rx_pending;
पूर्ण

अटल पूर्णांक rtl8152_set_ringparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);

	अगर (ring->rx_pending < (RTL8152_MAX_RX * 2))
		वापस -EINVAL;

	अगर (tp->rx_pending != ring->rx_pending) अणु
		अगर (netdev->flags & IFF_UP) अणु
			mutex_lock(&tp->control);
			napi_disable(&tp->napi);
			tp->rx_pending = ring->rx_pending;
			napi_enable(&tp->napi);
			mutex_unlock(&tp->control);
		पूर्ण अन्यथा अणु
			tp->rx_pending = ring->rx_pending;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS,
	.get_drvinfo = rtl8152_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.nway_reset = rtl8152_nway_reset,
	.get_msglevel = rtl8152_get_msglevel,
	.set_msglevel = rtl8152_set_msglevel,
	.get_wol = rtl8152_get_wol,
	.set_wol = rtl8152_set_wol,
	.get_strings = rtl8152_get_strings,
	.get_sset_count = rtl8152_get_sset_count,
	.get_ethtool_stats = rtl8152_get_ethtool_stats,
	.get_coalesce = rtl8152_get_coalesce,
	.set_coalesce = rtl8152_set_coalesce,
	.get_eee = rtl_ethtool_get_eee,
	.set_eee = rtl_ethtool_set_eee,
	.get_link_ksettings = rtl8152_get_link_ksettings,
	.set_link_ksettings = rtl8152_set_link_ksettings,
	.get_tunable = rtl8152_get_tunable,
	.set_tunable = rtl8152_set_tunable,
	.get_ringparam = rtl8152_get_ringparam,
	.set_ringparam = rtl8152_set_ringparam,
पूर्ण;

अटल पूर्णांक rtl8152_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा r8152 *tp = netdev_priv(netdev);
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);
	पूर्णांक res;

	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस -ENODEV;

	res = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (res < 0)
		जाओ out;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = R8152_PHY_ID; /* Internal PHY */
		अवरोध;

	हाल SIOCGMIIREG:
		mutex_lock(&tp->control);
		data->val_out = r8152_mdio_पढ़ो(tp, data->reg_num);
		mutex_unlock(&tp->control);
		अवरोध;

	हाल SIOCSMIIREG:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			res = -EPERM;
			अवरोध;
		पूर्ण
		mutex_lock(&tp->control);
		r8152_mdio_ग_लिखो(tp, data->reg_num, data->val_in);
		mutex_unlock(&tp->control);
		अवरोध;

	शेष:
		res = -EOPNOTSUPP;
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

out:
	वापस res;
पूर्ण

अटल पूर्णांक rtl8152_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा r8152 *tp = netdev_priv(dev);
	पूर्णांक ret;

	चयन (tp->version) अणु
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_07:
		dev->mtu = new_mtu;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	ret = usb_स्वतःpm_get_पूर्णांकerface(tp->पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&tp->control);

	dev->mtu = new_mtu;

	अगर (netअगर_running(dev)) अणु
		अगर (tp->rtl_ops.change_mtu)
			tp->rtl_ops.change_mtu(tp);

		अगर (netअगर_carrier_ok(dev)) अणु
			netअगर_stop_queue(dev);
			napi_disable(&tp->napi);
			tasklet_disable(&tp->tx_tl);
			tp->rtl_ops.disable(tp);
			tp->rtl_ops.enable(tp);
			rtl_start_rx(tp);
			tasklet_enable(&tp->tx_tl);
			napi_enable(&tp->napi);
			rtl8152_set_rx_mode(dev);
			netअगर_wake_queue(dev);
		पूर्ण
	पूर्ण

	mutex_unlock(&tp->control);

	usb_स्वतःpm_put_पूर्णांकerface(tp->पूर्णांकf);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops rtl8152_netdev_ops = अणु
	.nकरो_खोलो		= rtl8152_खोलो,
	.nकरो_stop		= rtl8152_बंद,
	.nकरो_करो_ioctl		= rtl8152_ioctl,
	.nकरो_start_xmit		= rtl8152_start_xmit,
	.nकरो_tx_समयout		= rtl8152_tx_समयout,
	.nकरो_set_features	= rtl8152_set_features,
	.nकरो_set_rx_mode	= rtl8152_set_rx_mode,
	.nकरो_set_mac_address	= rtl8152_set_mac_address,
	.nकरो_change_mtu		= rtl8152_change_mtu,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_features_check	= rtl8152_features_check,
पूर्ण;

अटल व्योम rtl8152_unload(काष्ठा r8152 *tp)
अणु
	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	अगर (tp->version != RTL_VER_01)
		r8152_घातer_cut_en(tp, true);
पूर्ण

अटल व्योम rtl8153_unload(काष्ठा r8152 *tp)
अणु
	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	r8153_घातer_cut_en(tp, false);
पूर्ण

अटल व्योम rtl8153b_unload(काष्ठा r8152 *tp)
अणु
	अगर (test_bit(RTL8152_UNPLUG, &tp->flags))
		वापस;

	r8153b_घातer_cut_en(tp, false);
पूर्ण

अटल पूर्णांक rtl_ops_init(काष्ठा r8152 *tp)
अणु
	काष्ठा rtl_ops *ops = &tp->rtl_ops;
	पूर्णांक ret = 0;

	चयन (tp->version) अणु
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_07:
		ops->init		= r8152b_init;
		ops->enable		= rtl8152_enable;
		ops->disable		= rtl8152_disable;
		ops->up			= rtl8152_up;
		ops->करोwn		= rtl8152_करोwn;
		ops->unload		= rtl8152_unload;
		ops->eee_get		= r8152_get_eee;
		ops->eee_set		= r8152_set_eee;
		ops->in_nway		= rtl8152_in_nway;
		ops->hw_phy_cfg		= r8152b_hw_phy_cfg;
		ops->स्वतःsuspend_en	= rtl_runसमय_suspend_enable;
		tp->rx_buf_sz		= 16 * 1024;
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_100TX;
		अवरोध;

	हाल RTL_VER_03:
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
		ops->init		= r8153_init;
		ops->enable		= rtl8153_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8153_up;
		ops->करोwn		= rtl8153_करोwn;
		ops->unload		= rtl8153_unload;
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8152_set_eee;
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8153_hw_phy_cfg;
		ops->स्वतःsuspend_en	= rtl8153_runसमय_enable;
		ops->change_mtu		= rtl8153_change_mtu;
		अगर (tp->udev->speed < USB_SPEED_SUPER)
			tp->rx_buf_sz	= 16 * 1024;
		अन्यथा
			tp->rx_buf_sz	= 32 * 1024;
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_1000T | MDIO_EEE_100TX;
		अवरोध;

	हाल RTL_VER_08:
	हाल RTL_VER_09:
		ops->init		= r8153b_init;
		ops->enable		= rtl8153_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8153b_up;
		ops->करोwn		= rtl8153b_करोwn;
		ops->unload		= rtl8153b_unload;
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8152_set_eee;
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8153b_hw_phy_cfg;
		ops->स्वतःsuspend_en	= rtl8153b_runसमय_enable;
		ops->change_mtu		= rtl8153_change_mtu;
		tp->rx_buf_sz		= 32 * 1024;
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_1000T | MDIO_EEE_100TX;
		अवरोध;

	हाल RTL_VER_11:
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_1000T | MDIO_EEE_100TX;
		fallthrough;
	हाल RTL_VER_10:
		ops->init		= r8156_init;
		ops->enable		= rtl8156_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8156_up;
		ops->करोwn		= rtl8156_करोwn;
		ops->unload		= rtl8153_unload;
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8152_set_eee;
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8156_hw_phy_cfg;
		ops->स्वतःsuspend_en	= rtl8156_runसमय_enable;
		ops->change_mtu		= rtl8156_change_mtu;
		tp->rx_buf_sz		= 48 * 1024;
		tp->support_2500full	= 1;
		अवरोध;

	हाल RTL_VER_12:
	हाल RTL_VER_13:
		tp->support_2500full	= 1;
		fallthrough;
	हाल RTL_VER_15:
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_1000T | MDIO_EEE_100TX;
		ops->init		= r8156b_init;
		ops->enable		= rtl8156b_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8156_up;
		ops->करोwn		= rtl8156_करोwn;
		ops->unload		= rtl8153_unload;
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8152_set_eee;
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8156b_hw_phy_cfg;
		ops->स्वतःsuspend_en	= rtl8156_runसमय_enable;
		ops->change_mtu		= rtl8156_change_mtu;
		tp->rx_buf_sz		= 48 * 1024;
		अवरोध;

	हाल RTL_VER_14:
		ops->init		= r8153c_init;
		ops->enable		= rtl8153_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8153c_up;
		ops->करोwn		= rtl8153b_करोwn;
		ops->unload		= rtl8153_unload;
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8152_set_eee;
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8153c_hw_phy_cfg;
		ops->स्वतःsuspend_en	= rtl8153c_runसमय_enable;
		ops->change_mtu		= rtl8153c_change_mtu;
		tp->rx_buf_sz		= 32 * 1024;
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_1000T | MDIO_EEE_100TX;
		अवरोध;

	शेष:
		ret = -ENODEV;
		dev_err(&tp->पूर्णांकf->dev, "Unknown Device\n");
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा FIRMWARE_8153A_2	"rtl_nic/rtl8153a-2.fw"
#घोषणा FIRMWARE_8153A_3	"rtl_nic/rtl8153a-3.fw"
#घोषणा FIRMWARE_8153A_4	"rtl_nic/rtl8153a-4.fw"
#घोषणा FIRMWARE_8153B_2	"rtl_nic/rtl8153b-2.fw"
#घोषणा FIRMWARE_8153C_1	"rtl_nic/rtl8153c-1.fw"
#घोषणा FIRMWARE_8156A_2	"rtl_nic/rtl8156a-2.fw"
#घोषणा FIRMWARE_8156B_2	"rtl_nic/rtl8156b-2.fw"

MODULE_FIRMWARE(FIRMWARE_8153A_2);
MODULE_FIRMWARE(FIRMWARE_8153A_3);
MODULE_FIRMWARE(FIRMWARE_8153A_4);
MODULE_FIRMWARE(FIRMWARE_8153B_2);
MODULE_FIRMWARE(FIRMWARE_8153C_1);
MODULE_FIRMWARE(FIRMWARE_8156A_2);
MODULE_FIRMWARE(FIRMWARE_8156B_2);

अटल पूर्णांक rtl_fw_init(काष्ठा r8152 *tp)
अणु
	काष्ठा rtl_fw *rtl_fw = &tp->rtl_fw;

	चयन (tp->version) अणु
	हाल RTL_VER_04:
		rtl_fw->fw_name		= FIRMWARE_8153A_2;
		rtl_fw->pre_fw		= r8153_pre_firmware_1;
		rtl_fw->post_fw		= r8153_post_firmware_1;
		अवरोध;
	हाल RTL_VER_05:
		rtl_fw->fw_name		= FIRMWARE_8153A_3;
		rtl_fw->pre_fw		= r8153_pre_firmware_2;
		rtl_fw->post_fw		= r8153_post_firmware_2;
		अवरोध;
	हाल RTL_VER_06:
		rtl_fw->fw_name		= FIRMWARE_8153A_4;
		rtl_fw->post_fw		= r8153_post_firmware_3;
		अवरोध;
	हाल RTL_VER_09:
		rtl_fw->fw_name		= FIRMWARE_8153B_2;
		rtl_fw->pre_fw		= r8153b_pre_firmware_1;
		rtl_fw->post_fw		= r8153b_post_firmware_1;
		अवरोध;
	हाल RTL_VER_11:
		rtl_fw->fw_name		= FIRMWARE_8156A_2;
		rtl_fw->post_fw		= r8156a_post_firmware_1;
		अवरोध;
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		rtl_fw->fw_name		= FIRMWARE_8156B_2;
		अवरोध;
	हाल RTL_VER_14:
		rtl_fw->fw_name		= FIRMWARE_8153C_1;
		rtl_fw->pre_fw		= r8153b_pre_firmware_1;
		rtl_fw->post_fw		= r8153c_post_firmware_1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

u8 rtl8152_get_version(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	u32 ocp_data = 0;
	__le32 *पंचांगp;
	u8 version;
	पूर्णांक ret;

	पंचांगp = kदो_स्मृति(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस 0;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      RTL8152_REQ_GET_REGS, RTL8152_REQT_READ,
			      PLA_TCR0, MCU_TYPE_PLA, पंचांगp, माप(*पंचांगp), 500);
	अगर (ret > 0)
		ocp_data = (__le32_to_cpu(*पंचांगp) >> 16) & VERSION_MASK;

	kमुक्त(पंचांगp);

	चयन (ocp_data) अणु
	हाल 0x4c00:
		version = RTL_VER_01;
		अवरोध;
	हाल 0x4c10:
		version = RTL_VER_02;
		अवरोध;
	हाल 0x5c00:
		version = RTL_VER_03;
		अवरोध;
	हाल 0x5c10:
		version = RTL_VER_04;
		अवरोध;
	हाल 0x5c20:
		version = RTL_VER_05;
		अवरोध;
	हाल 0x5c30:
		version = RTL_VER_06;
		अवरोध;
	हाल 0x4800:
		version = RTL_VER_07;
		अवरोध;
	हाल 0x6000:
		version = RTL_VER_08;
		अवरोध;
	हाल 0x6010:
		version = RTL_VER_09;
		अवरोध;
	हाल 0x7010:
		version = RTL_TEST_01;
		अवरोध;
	हाल 0x7020:
		version = RTL_VER_10;
		अवरोध;
	हाल 0x7030:
		version = RTL_VER_11;
		अवरोध;
	हाल 0x7400:
		version = RTL_VER_12;
		अवरोध;
	हाल 0x7410:
		version = RTL_VER_13;
		अवरोध;
	हाल 0x6400:
		version = RTL_VER_14;
		अवरोध;
	हाल 0x7420:
		version = RTL_VER_15;
		अवरोध;
	शेष:
		version = RTL_VER_UNKNOWN;
		dev_info(&पूर्णांकf->dev, "Unknown version 0x%04x\n", ocp_data);
		अवरोध;
	पूर्ण

	dev_dbg(&पूर्णांकf->dev, "Detected version 0x%04x\n", version);

	वापस version;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8152_get_version);

अटल पूर्णांक rtl8152_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	u8 version = rtl8152_get_version(पूर्णांकf);
	काष्ठा r8152 *tp;
	काष्ठा net_device *netdev;
	पूर्णांक ret;

	अगर (version == RTL_VER_UNKNOWN)
		वापस -ENODEV;

	अगर (!rtl_venकरोr_mode(पूर्णांकf))
		वापस -ENODEV;

	usb_reset_device(udev);
	netdev = alloc_etherdev(माप(काष्ठा r8152));
	अगर (!netdev) अणु
		dev_err(&पूर्णांकf->dev, "Out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);
	tp = netdev_priv(netdev);
	tp->msg_enable = 0x7FFF;

	tp->udev = udev;
	tp->netdev = netdev;
	tp->पूर्णांकf = पूर्णांकf;
	tp->version = version;

	चयन (version) अणु
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_07:
		tp->mii.supports_gmii = 0;
		अवरोध;
	शेष:
		tp->mii.supports_gmii = 1;
		अवरोध;
	पूर्ण

	ret = rtl_ops_init(tp);
	अगर (ret)
		जाओ out;

	rtl_fw_init(tp);

	mutex_init(&tp->control);
	INIT_DELAYED_WORK(&tp->schedule, rtl_work_func_t);
	INIT_DELAYED_WORK(&tp->hw_phy_work, rtl_hw_phy_work_func_t);
	tasklet_setup(&tp->tx_tl, bottom_half);
	tasklet_disable(&tp->tx_tl);

	netdev->netdev_ops = &rtl8152_netdev_ops;
	netdev->watchकरोg_समयo = RTL8152_TX_TIMEOUT;

	netdev->features |= NETIF_F_RXCSUM | NETIF_F_IP_CSUM | NETIF_F_SG |
			    NETIF_F_TSO | NETIF_F_FRAGLIST | NETIF_F_IPV6_CSUM |
			    NETIF_F_TSO6 | NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_TX;
	netdev->hw_features = NETIF_F_RXCSUM | NETIF_F_IP_CSUM | NETIF_F_SG |
			      NETIF_F_TSO | NETIF_F_FRAGLIST |
			      NETIF_F_IPV6_CSUM | NETIF_F_TSO6 |
			      NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_CTAG_TX;
	netdev->vlan_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO |
				NETIF_F_HIGHDMA | NETIF_F_FRAGLIST |
				NETIF_F_IPV6_CSUM | NETIF_F_TSO6;

	अगर (tp->version == RTL_VER_01) अणु
		netdev->features &= ~NETIF_F_RXCSUM;
		netdev->hw_features &= ~NETIF_F_RXCSUM;
	पूर्ण

	अगर (le16_to_cpu(udev->descriptor.idVenकरोr) == VENDOR_ID_LENOVO) अणु
		चयन (le16_to_cpu(udev->descriptor.idProduct)) अणु
		हाल DEVICE_ID_THINKPAD_THUNDERBOLT3_DOCK_GEN2:
		हाल DEVICE_ID_THINKPAD_USB_C_DOCK_GEN2:
			tp->lenovo_macpassthru = 1;
		पूर्ण
	पूर्ण

	अगर (le16_to_cpu(udev->descriptor.bcdDevice) == 0x3011 && udev->serial &&
	    (!म_भेद(udev->serial, "000001000000") ||
	     !म_भेद(udev->serial, "000002000000"))) अणु
		dev_info(&udev->dev, "Dell TB16 Dock, disable RX aggregation");
		tp->dell_tb_rx_agg_bug = 1;
	पूर्ण

	netdev->ethtool_ops = &ops;
	netअगर_set_gso_max_size(netdev, RTL_LIMITED_TSO_SIZE);

	/* MTU range: 68 - 1500 or 9194 */
	netdev->min_mtu = ETH_MIN_MTU;
	चयन (tp->version) अणु
	हाल RTL_VER_03:
	हाल RTL_VER_04:
	हाल RTL_VER_05:
	हाल RTL_VER_06:
	हाल RTL_VER_08:
	हाल RTL_VER_09:
	हाल RTL_VER_14:
		netdev->max_mtu = माप_प्रकारo_mtu(9 * 1024);
		अवरोध;
	हाल RTL_VER_10:
	हाल RTL_VER_11:
		netdev->max_mtu = माप_प्रकारo_mtu(15 * 1024);
		अवरोध;
	हाल RTL_VER_12:
	हाल RTL_VER_13:
	हाल RTL_VER_15:
		netdev->max_mtu = माप_प्रकारo_mtu(16 * 1024);
		अवरोध;
	हाल RTL_VER_01:
	हाल RTL_VER_02:
	हाल RTL_VER_07:
	शेष:
		netdev->max_mtu = ETH_DATA_LEN;
		अवरोध;
	पूर्ण

	tp->mii.dev = netdev;
	tp->mii.mdio_पढ़ो = पढ़ो_mii_word;
	tp->mii.mdio_ग_लिखो = ग_लिखो_mii_word;
	tp->mii.phy_id_mask = 0x3f;
	tp->mii.reg_num_mask = 0x1f;
	tp->mii.phy_id = R8152_PHY_ID;

	tp->स्वतःneg = AUTONEG_ENABLE;
	tp->speed = SPEED_100;
	tp->advertising = RTL_ADVERTISED_10_HALF | RTL_ADVERTISED_10_FULL |
			  RTL_ADVERTISED_100_HALF | RTL_ADVERTISED_100_FULL;
	अगर (tp->mii.supports_gmii) अणु
		अगर (tp->support_2500full &&
		    tp->udev->speed >= USB_SPEED_SUPER) अणु
			tp->speed = SPEED_2500;
			tp->advertising |= RTL_ADVERTISED_2500_FULL;
		पूर्ण अन्यथा अणु
			tp->speed = SPEED_1000;
		पूर्ण
		tp->advertising |= RTL_ADVERTISED_1000_FULL;
	पूर्ण
	tp->duplex = DUPLEX_FULL;

	tp->rx_copyअवरोध = RTL8152_RXFG_HEADSZ;
	tp->rx_pending = 10 * RTL8152_MAX_RX;

	पूर्णांकf->needs_remote_wakeup = 1;

	अगर (!rtl_can_wakeup(tp))
		__rtl_set_wol(tp, 0);
	अन्यथा
		tp->saved_wolopts = __rtl_get_wol(tp);

	tp->rtl_ops.init(tp);
#अगर IS_BUILTIN(CONFIG_USB_RTL8152)
	/* Retry in हाल request_firmware() is not पढ़ोy yet. */
	tp->rtl_fw.retry = true;
#पूर्ण_अगर
	queue_delayed_work(प्रणाली_दीर्घ_wq, &tp->hw_phy_work, 0);
	set_ethernet_addr(tp);

	usb_set_पूर्णांकfdata(पूर्णांकf, tp);

	अगर (tp->support_2500full)
		netअगर_napi_add(netdev, &tp->napi, r8152_poll, 256);
	अन्यथा
		netअगर_napi_add(netdev, &tp->napi, r8152_poll, 64);

	ret = रेजिस्टर_netdev(netdev);
	अगर (ret != 0) अणु
		dev_err(&पूर्णांकf->dev, "couldn't register the device\n");
		जाओ out1;
	पूर्ण

	अगर (tp->saved_wolopts)
		device_set_wakeup_enable(&udev->dev, true);
	अन्यथा
		device_set_wakeup_enable(&udev->dev, false);

	netअगर_info(tp, probe, netdev, "%s\n", DRIVER_VERSION);

	वापस 0;

out1:
	tasklet_समाप्त(&tp->tx_tl);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
out:
	मुक्त_netdev(netdev);
	वापस ret;
पूर्ण

अटल व्योम rtl8152_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा r8152 *tp = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (tp) अणु
		rtl_set_unplug(tp);

		unरेजिस्टर_netdev(tp->netdev);
		tasklet_समाप्त(&tp->tx_tl);
		cancel_delayed_work_sync(&tp->hw_phy_work);
		अगर (tp->rtl_ops.unload)
			tp->rtl_ops.unload(tp);
		rtl8152_release_firmware(tp);
		मुक्त_netdev(tp->netdev);
	पूर्ण
पूर्ण

#घोषणा REALTEK_USB_DEVICE(vend, prod)	अणु \
	USB_DEVICE_INTERFACE_CLASS(vend, prod, USB_CLASS_VENDOR_SPEC), \
पूर्ण, \
अणु \
	USB_DEVICE_AND_INTERFACE_INFO(vend, prod, USB_CLASS_COMM, \
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE), \
पूर्ण

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id rtl8152_table[] = अणु
	/* Realtek */
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8050),
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8053),
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8152),
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8153),
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8155),
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8156),

	/* Microsoft */
	REALTEK_USB_DEVICE(VENDOR_ID_MICROSOFT, 0x07ab),
	REALTEK_USB_DEVICE(VENDOR_ID_MICROSOFT, 0x07c6),
	REALTEK_USB_DEVICE(VENDOR_ID_MICROSOFT, 0x0927),
	REALTEK_USB_DEVICE(VENDOR_ID_SAMSUNG, 0xa101),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO,  0x304f),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO,  0x3062),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO,  0x3069),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO,  0x3082),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO,  0x7205),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO,  0x720c),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO,  0x7214),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO,  0x721e),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO,  0xa387),
	REALTEK_USB_DEVICE(VENDOR_ID_LINKSYS, 0x0041),
	REALTEK_USB_DEVICE(VENDOR_ID_NVIDIA,  0x09ff),
	REALTEK_USB_DEVICE(VENDOR_ID_TPLINK,  0x0601),
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, rtl8152_table);

अटल काष्ठा usb_driver rtl8152_driver = अणु
	.name =		MODULENAME,
	.id_table =	rtl8152_table,
	.probe =	rtl8152_probe,
	.disconnect =	rtl8152_disconnect,
	.suspend =	rtl8152_suspend,
	.resume =	rtl8152_resume,
	.reset_resume =	rtl8152_reset_resume,
	.pre_reset =	rtl8152_pre_reset,
	.post_reset =	rtl8152_post_reset,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(rtl8152_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);
