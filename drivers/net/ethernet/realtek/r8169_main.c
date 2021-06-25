<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * r8169.c: RealTek 8169/8168/8101 ethernet driver.
 *
 * Copyright (c) 2002 ShuChen <shuchen@realtek.com.tw>
 * Copyright (c) 2003 - 2007 Francois Romieu <romieu@fr.zoreil.com>
 * Copyright (c) a lot of people too. Please respect their work.
 *
 * See MAINTAINERS file क्रम support contact inक्रमmation.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/पन.स>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/bitfield.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/ipv6.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/ip6_checksum.h>

#समावेश "r8169.h"
#समावेश "r8169_firmware.h"

#घोषणा MODULENAME "r8169"

#घोषणा FIRMWARE_8168D_1	"rtl_nic/rtl8168d-1.fw"
#घोषणा FIRMWARE_8168D_2	"rtl_nic/rtl8168d-2.fw"
#घोषणा FIRMWARE_8168E_1	"rtl_nic/rtl8168e-1.fw"
#घोषणा FIRMWARE_8168E_2	"rtl_nic/rtl8168e-2.fw"
#घोषणा FIRMWARE_8168E_3	"rtl_nic/rtl8168e-3.fw"
#घोषणा FIRMWARE_8168F_1	"rtl_nic/rtl8168f-1.fw"
#घोषणा FIRMWARE_8168F_2	"rtl_nic/rtl8168f-2.fw"
#घोषणा FIRMWARE_8105E_1	"rtl_nic/rtl8105e-1.fw"
#घोषणा FIRMWARE_8402_1		"rtl_nic/rtl8402-1.fw"
#घोषणा FIRMWARE_8411_1		"rtl_nic/rtl8411-1.fw"
#घोषणा FIRMWARE_8411_2		"rtl_nic/rtl8411-2.fw"
#घोषणा FIRMWARE_8106E_1	"rtl_nic/rtl8106e-1.fw"
#घोषणा FIRMWARE_8106E_2	"rtl_nic/rtl8106e-2.fw"
#घोषणा FIRMWARE_8168G_2	"rtl_nic/rtl8168g-2.fw"
#घोषणा FIRMWARE_8168G_3	"rtl_nic/rtl8168g-3.fw"
#घोषणा FIRMWARE_8168H_1	"rtl_nic/rtl8168h-1.fw"
#घोषणा FIRMWARE_8168H_2	"rtl_nic/rtl8168h-2.fw"
#घोषणा FIRMWARE_8168FP_3	"rtl_nic/rtl8168fp-3.fw"
#घोषणा FIRMWARE_8107E_1	"rtl_nic/rtl8107e-1.fw"
#घोषणा FIRMWARE_8107E_2	"rtl_nic/rtl8107e-2.fw"
#घोषणा FIRMWARE_8125A_3	"rtl_nic/rtl8125a-3.fw"
#घोषणा FIRMWARE_8125B_2	"rtl_nic/rtl8125b-2.fw"

/* Maximum number of multicast addresses to filter (vs. Rx-all-multicast).
   The RTL chips use a 64 element hash table based on the Ethernet CRC. */
#घोषणा	MC_FILTER_LIMIT	32

#घोषणा TX_DMA_BURST	7	/* Maximum PCI burst, '7' is unlimited */
#घोषणा InterFrameGap	0x03	/* 3 means InterFrameGap = the लघुest one */

#घोषणा R8169_REGS_SIZE		256
#घोषणा R8169_RX_BUF_SIZE	(SZ_16K - 1)
#घोषणा NUM_TX_DESC	256	/* Number of Tx descriptor रेजिस्टरs */
#घोषणा NUM_RX_DESC	256	/* Number of Rx descriptor रेजिस्टरs */
#घोषणा R8169_TX_RING_BYTES	(NUM_TX_DESC * माप(काष्ठा TxDesc))
#घोषणा R8169_RX_RING_BYTES	(NUM_RX_DESC * माप(काष्ठा RxDesc))

#घोषणा OCP_STD_PHY_BASE	0xa400

#घोषणा RTL_CFG_NO_GBIT	1

/* ग_लिखो/पढ़ो MMIO रेजिस्टर */
#घोषणा RTL_W8(tp, reg, val8)	ग_लिखोb((val8), tp->mmio_addr + (reg))
#घोषणा RTL_W16(tp, reg, val16)	ग_लिखोw((val16), tp->mmio_addr + (reg))
#घोषणा RTL_W32(tp, reg, val32)	ग_लिखोl((val32), tp->mmio_addr + (reg))
#घोषणा RTL_R8(tp, reg)		पढ़ोb(tp->mmio_addr + (reg))
#घोषणा RTL_R16(tp, reg)		पढ़ोw(tp->mmio_addr + (reg))
#घोषणा RTL_R32(tp, reg)		पढ़ोl(tp->mmio_addr + (reg))

#घोषणा JUMBO_4K	(4 * SZ_1K - VLAN_ETH_HLEN - ETH_FCS_LEN)
#घोषणा JUMBO_6K	(6 * SZ_1K - VLAN_ETH_HLEN - ETH_FCS_LEN)
#घोषणा JUMBO_7K	(7 * SZ_1K - VLAN_ETH_HLEN - ETH_FCS_LEN)
#घोषणा JUMBO_9K	(9 * SZ_1K - VLAN_ETH_HLEN - ETH_FCS_LEN)

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *fw_name;
पूर्ण rtl_chip_infos[] = अणु
	/* PCI devices. */
	[RTL_GIGA_MAC_VER_02] = अणु"RTL8169s"				पूर्ण,
	[RTL_GIGA_MAC_VER_03] = अणु"RTL8110s"				पूर्ण,
	[RTL_GIGA_MAC_VER_04] = अणु"RTL8169sb/8110sb"			पूर्ण,
	[RTL_GIGA_MAC_VER_05] = अणु"RTL8169sc/8110sc"			पूर्ण,
	[RTL_GIGA_MAC_VER_06] = अणु"RTL8169sc/8110sc"			पूर्ण,
	/* PCI-E devices. */
	[RTL_GIGA_MAC_VER_07] = अणु"RTL8102e"				पूर्ण,
	[RTL_GIGA_MAC_VER_08] = अणु"RTL8102e"				पूर्ण,
	[RTL_GIGA_MAC_VER_09] = अणु"RTL8102e/RTL8103e"			पूर्ण,
	[RTL_GIGA_MAC_VER_10] = अणु"RTL8101e"				पूर्ण,
	[RTL_GIGA_MAC_VER_11] = अणु"RTL8168b/8111b"			पूर्ण,
	[RTL_GIGA_MAC_VER_12] = अणु"RTL8168b/8111b"			पूर्ण,
	[RTL_GIGA_MAC_VER_13] = अणु"RTL8101e/RTL8100e"			पूर्ण,
	[RTL_GIGA_MAC_VER_14] = अणु"RTL8401"				पूर्ण,
	[RTL_GIGA_MAC_VER_16] = अणु"RTL8101e"				पूर्ण,
	[RTL_GIGA_MAC_VER_17] = अणु"RTL8168b/8111b"			पूर्ण,
	[RTL_GIGA_MAC_VER_18] = अणु"RTL8168cp/8111cp"			पूर्ण,
	[RTL_GIGA_MAC_VER_19] = अणु"RTL8168c/8111c"			पूर्ण,
	[RTL_GIGA_MAC_VER_20] = अणु"RTL8168c/8111c"			पूर्ण,
	[RTL_GIGA_MAC_VER_21] = अणु"RTL8168c/8111c"			पूर्ण,
	[RTL_GIGA_MAC_VER_22] = अणु"RTL8168c/8111c"			पूर्ण,
	[RTL_GIGA_MAC_VER_23] = अणु"RTL8168cp/8111cp"			पूर्ण,
	[RTL_GIGA_MAC_VER_24] = अणु"RTL8168cp/8111cp"			पूर्ण,
	[RTL_GIGA_MAC_VER_25] = अणु"RTL8168d/8111d",	FIRMWARE_8168D_1पूर्ण,
	[RTL_GIGA_MAC_VER_26] = अणु"RTL8168d/8111d",	FIRMWARE_8168D_2पूर्ण,
	[RTL_GIGA_MAC_VER_27] = अणु"RTL8168dp/8111dp"			पूर्ण,
	[RTL_GIGA_MAC_VER_28] = अणु"RTL8168dp/8111dp"			पूर्ण,
	[RTL_GIGA_MAC_VER_29] = अणु"RTL8105e",		FIRMWARE_8105E_1पूर्ण,
	[RTL_GIGA_MAC_VER_30] = अणु"RTL8105e",		FIRMWARE_8105E_1पूर्ण,
	[RTL_GIGA_MAC_VER_31] = अणु"RTL8168dp/8111dp"			पूर्ण,
	[RTL_GIGA_MAC_VER_32] = अणु"RTL8168e/8111e",	FIRMWARE_8168E_1पूर्ण,
	[RTL_GIGA_MAC_VER_33] = अणु"RTL8168e/8111e",	FIRMWARE_8168E_2पूर्ण,
	[RTL_GIGA_MAC_VER_34] = अणु"RTL8168evl/8111evl",	FIRMWARE_8168E_3पूर्ण,
	[RTL_GIGA_MAC_VER_35] = अणु"RTL8168f/8111f",	FIRMWARE_8168F_1पूर्ण,
	[RTL_GIGA_MAC_VER_36] = अणु"RTL8168f/8111f",	FIRMWARE_8168F_2पूर्ण,
	[RTL_GIGA_MAC_VER_37] = अणु"RTL8402",		FIRMWARE_8402_1 पूर्ण,
	[RTL_GIGA_MAC_VER_38] = अणु"RTL8411",		FIRMWARE_8411_1 पूर्ण,
	[RTL_GIGA_MAC_VER_39] = अणु"RTL8106e",		FIRMWARE_8106E_1पूर्ण,
	[RTL_GIGA_MAC_VER_40] = अणु"RTL8168g/8111g",	FIRMWARE_8168G_2पूर्ण,
	[RTL_GIGA_MAC_VER_41] = अणु"RTL8168g/8111g"			पूर्ण,
	[RTL_GIGA_MAC_VER_42] = अणु"RTL8168gu/8111gu",	FIRMWARE_8168G_3पूर्ण,
	[RTL_GIGA_MAC_VER_43] = अणु"RTL8106eus",		FIRMWARE_8106E_2पूर्ण,
	[RTL_GIGA_MAC_VER_44] = अणु"RTL8411b",		FIRMWARE_8411_2 पूर्ण,
	[RTL_GIGA_MAC_VER_45] = अणु"RTL8168h/8111h",	FIRMWARE_8168H_1पूर्ण,
	[RTL_GIGA_MAC_VER_46] = अणु"RTL8168h/8111h",	FIRMWARE_8168H_2पूर्ण,
	[RTL_GIGA_MAC_VER_47] = अणु"RTL8107e",		FIRMWARE_8107E_1पूर्ण,
	[RTL_GIGA_MAC_VER_48] = अणु"RTL8107e",		FIRMWARE_8107E_2पूर्ण,
	[RTL_GIGA_MAC_VER_49] = अणु"RTL8168ep/8111ep"			पूर्ण,
	[RTL_GIGA_MAC_VER_50] = अणु"RTL8168ep/8111ep"			पूर्ण,
	[RTL_GIGA_MAC_VER_51] = अणु"RTL8168ep/8111ep"			पूर्ण,
	[RTL_GIGA_MAC_VER_52] = अणु"RTL8168fp/RTL8117",  FIRMWARE_8168FP_3पूर्ण,
	[RTL_GIGA_MAC_VER_53] = अणु"RTL8168fp/RTL8117",			पूर्ण,
	[RTL_GIGA_MAC_VER_60] = अणु"RTL8125A"				पूर्ण,
	[RTL_GIGA_MAC_VER_61] = अणु"RTL8125A",		FIRMWARE_8125A_3पूर्ण,
	/* reserve 62 क्रम CFG_METHOD_4 in the venकरोr driver */
	[RTL_GIGA_MAC_VER_63] = अणु"RTL8125B",		FIRMWARE_8125B_2पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id rtl8169_pci_tbl[] = अणु
	अणु PCI_VDEVICE(REALTEK,	0x2502) पूर्ण,
	अणु PCI_VDEVICE(REALTEK,	0x2600) पूर्ण,
	अणु PCI_VDEVICE(REALTEK,	0x8129) पूर्ण,
	अणु PCI_VDEVICE(REALTEK,	0x8136), RTL_CFG_NO_GBIT पूर्ण,
	अणु PCI_VDEVICE(REALTEK,	0x8161) पूर्ण,
	अणु PCI_VDEVICE(REALTEK,	0x8167) पूर्ण,
	अणु PCI_VDEVICE(REALTEK,	0x8168) पूर्ण,
	अणु PCI_VDEVICE(NCUBE,	0x8168) पूर्ण,
	अणु PCI_VDEVICE(REALTEK,	0x8169) पूर्ण,
	अणु PCI_VENDOR_ID_DLINK,	0x4300,
		PCI_VENDOR_ID_DLINK, 0x4b10, 0, 0 पूर्ण,
	अणु PCI_VDEVICE(DLINK,	0x4300) पूर्ण,
	अणु PCI_VDEVICE(DLINK,	0x4302) पूर्ण,
	अणु PCI_VDEVICE(AT,	0xc107) पूर्ण,
	अणु PCI_VDEVICE(USR,	0x0116) पूर्ण,
	अणु PCI_VENDOR_ID_LINKSYS, 0x1032, PCI_ANY_ID, 0x0024 पूर्ण,
	अणु 0x0001, 0x8168, PCI_ANY_ID, 0x2410 पूर्ण,
	अणु PCI_VDEVICE(REALTEK,	0x8125) पूर्ण,
	अणु PCI_VDEVICE(REALTEK,	0x3000) पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, rtl8169_pci_tbl);

क्रमागत rtl_रेजिस्टरs अणु
	MAC0		= 0,	/* Ethernet hardware address. */
	MAC4		= 4,
	MAR0		= 8,	/* Multicast filter. */
	CounterAddrLow		= 0x10,
	CounterAddrHigh		= 0x14,
	TxDescStartAddrLow	= 0x20,
	TxDescStartAddrHigh	= 0x24,
	TxHDescStartAddrLow	= 0x28,
	TxHDescStartAddrHigh	= 0x2c,
	FLASH		= 0x30,
	ERSR		= 0x36,
	ChipCmd		= 0x37,
	TxPoll		= 0x38,
	IntrMask	= 0x3c,
	IntrStatus	= 0x3e,

	TxConfig	= 0x40,
#घोषणा	TXCFG_AUTO_FIFO			(1 << 7)	/* 8111e-vl */
#घोषणा	TXCFG_EMPTY			(1 << 11)	/* 8111e-vl */

	RxConfig	= 0x44,
#घोषणा	RX128_INT_EN			(1 << 15)	/* 8111c and later */
#घोषणा	RX_MULTI_EN			(1 << 14)	/* 8111c only */
#घोषणा	RXCFG_FIFO_SHIFT		13
					/* No threshold beक्रमe first PCI xfer */
#घोषणा	RX_FIFO_THRESH			(7 << RXCFG_FIFO_SHIFT)
#घोषणा	RX_EARLY_OFF			(1 << 11)
#घोषणा	RXCFG_DMA_SHIFT			8
					/* Unlimited maximum PCI burst. */
#घोषणा	RX_DMA_BURST			(7 << RXCFG_DMA_SHIFT)

	Cfg9346		= 0x50,
	Config0		= 0x51,
	Config1		= 0x52,
	Config2		= 0x53,
#घोषणा PME_SIGNAL			(1 << 5)	/* 8168c and later */

	Config3		= 0x54,
	Config4		= 0x55,
	Config5		= 0x56,
	PHYAR		= 0x60,
	PHYstatus	= 0x6c,
	RxMaxSize	= 0xda,
	CPlusCmd	= 0xe0,
	IntrMitigate	= 0xe2,

#घोषणा RTL_COALESCE_TX_USECS	GENMASK(15, 12)
#घोषणा RTL_COALESCE_TX_FRAMES	GENMASK(11, 8)
#घोषणा RTL_COALESCE_RX_USECS	GENMASK(7, 4)
#घोषणा RTL_COALESCE_RX_FRAMES	GENMASK(3, 0)

#घोषणा RTL_COALESCE_T_MAX	0x0fU
#घोषणा RTL_COALESCE_FRAME_MAX	(RTL_COALESCE_T_MAX * 4)

	RxDescAddrLow	= 0xe4,
	RxDescAddrHigh	= 0xe8,
	EarlyTxThres	= 0xec,	/* 8169. Unit of 32 bytes. */

#घोषणा NoEarlyTx	0x3f	/* Max value : no early transmit. */

	MaxTxPacketSize	= 0xec,	/* 8101/8168. Unit of 128 bytes. */

#घोषणा TxPacketMax	(8064 >> 7)
#घोषणा EarlySize	0x27

	FuncEvent	= 0xf0,
	FuncEventMask	= 0xf4,
	FuncPresetState	= 0xf8,
	IBCR0           = 0xf8,
	IBCR2           = 0xf9,
	IBIMR0          = 0xfa,
	IBISR0          = 0xfb,
	FuncForceEvent	= 0xfc,
पूर्ण;

क्रमागत rtl8168_8101_रेजिस्टरs अणु
	CSIDR			= 0x64,
	CSIAR			= 0x68,
#घोषणा	CSIAR_FLAG			0x80000000
#घोषणा	CSIAR_WRITE_CMD			0x80000000
#घोषणा	CSIAR_BYTE_ENABLE		0x0000f000
#घोषणा	CSIAR_ADDR_MASK			0x00000fff
	PMCH			= 0x6f,
#घोषणा D3COLD_NO_PLL_DOWN		BIT(7)
#घोषणा D3HOT_NO_PLL_DOWN		BIT(6)
#घोषणा D3_NO_PLL_DOWN			(BIT(7) | BIT(6))
	EPHYAR			= 0x80,
#घोषणा	EPHYAR_FLAG			0x80000000
#घोषणा	EPHYAR_WRITE_CMD		0x80000000
#घोषणा	EPHYAR_REG_MASK			0x1f
#घोषणा	EPHYAR_REG_SHIFT		16
#घोषणा	EPHYAR_DATA_MASK		0xffff
	DLLPR			= 0xd0,
#घोषणा	PFM_EN				(1 << 6)
#घोषणा	TX_10M_PS_EN			(1 << 7)
	DBG_REG			= 0xd1,
#घोषणा	FIX_NAK_1			(1 << 4)
#घोषणा	FIX_NAK_2			(1 << 3)
	TWSI			= 0xd2,
	MCU			= 0xd3,
#घोषणा	NOW_IS_OOB			(1 << 7)
#घोषणा	TX_EMPTY			(1 << 5)
#घोषणा	RX_EMPTY			(1 << 4)
#घोषणा	RXTX_EMPTY			(TX_EMPTY | RX_EMPTY)
#घोषणा	EN_NDP				(1 << 3)
#घोषणा	EN_OOB_RESET			(1 << 2)
#घोषणा	LINK_LIST_RDY			(1 << 1)
	EFUSEAR			= 0xdc,
#घोषणा	EFUSEAR_FLAG			0x80000000
#घोषणा	EFUSEAR_WRITE_CMD		0x80000000
#घोषणा	EFUSEAR_READ_CMD		0x00000000
#घोषणा	EFUSEAR_REG_MASK		0x03ff
#घोषणा	EFUSEAR_REG_SHIFT		8
#घोषणा	EFUSEAR_DATA_MASK		0xff
	MISC_1			= 0xf2,
#घोषणा	PFM_D3COLD_EN			(1 << 6)
पूर्ण;

क्रमागत rtl8168_रेजिस्टरs अणु
	LED_FREQ		= 0x1a,
	EEE_LED			= 0x1b,
	ERIDR			= 0x70,
	ERIAR			= 0x74,
#घोषणा ERIAR_FLAG			0x80000000
#घोषणा ERIAR_WRITE_CMD			0x80000000
#घोषणा ERIAR_READ_CMD			0x00000000
#घोषणा ERIAR_ADDR_BYTE_ALIGN		4
#घोषणा ERIAR_TYPE_SHIFT		16
#घोषणा ERIAR_EXGMAC			(0x00 << ERIAR_TYPE_SHIFT)
#घोषणा ERIAR_MSIX			(0x01 << ERIAR_TYPE_SHIFT)
#घोषणा ERIAR_ASF			(0x02 << ERIAR_TYPE_SHIFT)
#घोषणा ERIAR_OOB			(0x02 << ERIAR_TYPE_SHIFT)
#घोषणा ERIAR_MASK_SHIFT		12
#घोषणा ERIAR_MASK_0001			(0x1 << ERIAR_MASK_SHIFT)
#घोषणा ERIAR_MASK_0011			(0x3 << ERIAR_MASK_SHIFT)
#घोषणा ERIAR_MASK_0100			(0x4 << ERIAR_MASK_SHIFT)
#घोषणा ERIAR_MASK_0101			(0x5 << ERIAR_MASK_SHIFT)
#घोषणा ERIAR_MASK_1111			(0xf << ERIAR_MASK_SHIFT)
	EPHY_RXER_NUM		= 0x7c,
	OCPDR			= 0xb0,	/* OCP GPHY access */
#घोषणा OCPDR_WRITE_CMD			0x80000000
#घोषणा OCPDR_READ_CMD			0x00000000
#घोषणा OCPDR_REG_MASK			0x7f
#घोषणा OCPDR_GPHY_REG_SHIFT		16
#घोषणा OCPDR_DATA_MASK			0xffff
	OCPAR			= 0xb4,
#घोषणा OCPAR_FLAG			0x80000000
#घोषणा OCPAR_GPHY_WRITE_CMD		0x8000f060
#घोषणा OCPAR_GPHY_READ_CMD		0x0000f060
	GPHY_OCP		= 0xb8,
	RDSAR1			= 0xd0,	/* 8168c only. Unकरोcumented on 8168dp */
	MISC			= 0xf0,	/* 8168e only. */
#घोषणा TXPLA_RST			(1 << 29)
#घोषणा DISABLE_LAN_EN			(1 << 23) /* Enable GPIO pin */
#घोषणा PWM_EN				(1 << 22)
#घोषणा RXDV_GATED_EN			(1 << 19)
#घोषणा EARLY_TALLY_EN			(1 << 16)
पूर्ण;

क्रमागत rtl8125_रेजिस्टरs अणु
	IntrMask_8125		= 0x38,
	IntrStatus_8125		= 0x3c,
	TxPoll_8125		= 0x90,
	MAC0_BKP		= 0x19e0,
	EEE_TXIDLE_TIMER_8125	= 0x6048,
पूर्ण;

#घोषणा RX_VLAN_INNER_8125	BIT(22)
#घोषणा RX_VLAN_OUTER_8125	BIT(23)
#घोषणा RX_VLAN_8125		(RX_VLAN_INNER_8125 | RX_VLAN_OUTER_8125)

#घोषणा RX_FETCH_DFLT_8125	(8 << 27)

क्रमागत rtl_रेजिस्टर_content अणु
	/* InterruptStatusBits */
	SYSErr		= 0x8000,
	PCSTimeout	= 0x4000,
	SWInt		= 0x0100,
	TxDescUnavail	= 0x0080,
	RxFIFOOver	= 0x0040,
	LinkChg		= 0x0020,
	RxOverflow	= 0x0010,
	TxErr		= 0x0008,
	TxOK		= 0x0004,
	RxErr		= 0x0002,
	RxOK		= 0x0001,

	/* RxStatusDesc */
	RxRWT	= (1 << 22),
	RxRES	= (1 << 21),
	RxRUNT	= (1 << 20),
	RxCRC	= (1 << 19),

	/* ChipCmdBits */
	StopReq		= 0x80,
	CmdReset	= 0x10,
	CmdRxEnb	= 0x08,
	CmdTxEnb	= 0x04,
	RxBufEmpty	= 0x01,

	/* TXPoll रेजिस्टर p.5 */
	HPQ		= 0x80,		/* Poll cmd on the high prio queue */
	NPQ		= 0x40,		/* Poll cmd on the low prio queue */
	FSWInt		= 0x01,		/* Forced software पूर्णांकerrupt */

	/* Cfg9346Bits */
	Cfg9346_Lock	= 0x00,
	Cfg9346_Unlock	= 0xc0,

	/* rx_mode_bits */
	AcceptErr	= 0x20,
	AcceptRunt	= 0x10,
#घोषणा RX_CONFIG_ACCEPT_ERR_MASK	0x30
	AcceptBroadcast	= 0x08,
	AcceptMulticast	= 0x04,
	AcceptMyPhys	= 0x02,
	AcceptAllPhys	= 0x01,
#घोषणा RX_CONFIG_ACCEPT_OK_MASK	0x0f
#घोषणा RX_CONFIG_ACCEPT_MASK		0x3f

	/* TxConfigBits */
	TxInterFrameGapShअगरt = 24,
	TxDMAShअगरt = 8,	/* DMA burst value (0-7) is shअगरt this many bits */

	/* Config1 रेजिस्टर p.24 */
	LEDS1		= (1 << 7),
	LEDS0		= (1 << 6),
	Speed_करोwn	= (1 << 4),
	MEMMAP		= (1 << 3),
	IOMAP		= (1 << 2),
	VPD		= (1 << 1),
	PMEnable	= (1 << 0),	/* Power Management Enable */

	/* Config2 रेजिस्टर p. 25 */
	ClkReqEn	= (1 << 7),	/* Clock Request Enable */
	MSIEnable	= (1 << 5),	/* 8169 only. Reserved in the 8168. */
	PCI_Clock_66MHz = 0x01,
	PCI_Clock_33MHz = 0x00,

	/* Config3 रेजिस्टर p.25 */
	MagicPacket	= (1 << 5),	/* Wake up when receives a Magic Packet */
	LinkUp		= (1 << 4),	/* Wake up when the cable connection is re-established */
	Jumbo_En0	= (1 << 2),	/* 8168 only. Reserved in the 8168b */
	Rdy_to_L23	= (1 << 1),	/* L23 Enable */
	Beacon_en	= (1 << 0),	/* 8168 only. Reserved in the 8168b */

	/* Config4 रेजिस्टर */
	Jumbo_En1	= (1 << 1),	/* 8168 only. Reserved in the 8168b */

	/* Config5 रेजिस्टर p.27 */
	BWF		= (1 << 6),	/* Accept Broadcast wakeup frame */
	MWF		= (1 << 5),	/* Accept Multicast wakeup frame */
	UWF		= (1 << 4),	/* Accept Unicast wakeup frame */
	Spi_en		= (1 << 3),
	LanWake		= (1 << 1),	/* LanWake enable/disable */
	PMEStatus	= (1 << 0),	/* PME status can be reset by PCI RST# */
	ASPM_en		= (1 << 0),	/* ASPM enable */

	/* CPlusCmd p.31 */
	EnableBist	= (1 << 15),	// 8168 8101
	Mac_dbgo_oe	= (1 << 14),	// 8168 8101
	EnAnaPLL	= (1 << 14),	// 8169
	Normal_mode	= (1 << 13),	// unused
	Force_half_dup	= (1 << 12),	// 8168 8101
	Force_rxflow_en	= (1 << 11),	// 8168 8101
	Force_txflow_en	= (1 << 10),	// 8168 8101
	Cxpl_dbg_sel	= (1 << 9),	// 8168 8101
	ASF		= (1 << 8),	// 8168 8101
	PktCntrDisable	= (1 << 7),	// 8168 8101
	Mac_dbgo_sel	= 0x001c,	// 8168
	RxVlan		= (1 << 6),
	RxChkSum	= (1 << 5),
	PCIDAC		= (1 << 4),
	PCIMulRW	= (1 << 3),
#घोषणा INTT_MASK	GENMASK(1, 0)
#घोषणा CPCMD_MASK	(Normal_mode | RxVlan | RxChkSum | INTT_MASK)

	/* rtl8169_PHYstatus */
	TBI_Enable	= 0x80,
	TxFlowCtrl	= 0x40,
	RxFlowCtrl	= 0x20,
	_1000bpsF	= 0x10,
	_100bps		= 0x08,
	_10bps		= 0x04,
	LinkStatus	= 0x02,
	FullDup		= 0x01,

	/* ResetCounterCommand */
	CounterReset	= 0x1,

	/* DumpCounterCommand */
	CounterDump	= 0x8,

	/* magic enable v2 */
	MagicPacket_v2	= (1 << 16),	/* Wake up when receives a Magic Packet */
पूर्ण;

क्रमागत rtl_desc_bit अणु
	/* First द्विगुनword. */
	DescOwn		= (1 << 31), /* Descriptor is owned by NIC */
	RingEnd		= (1 << 30), /* End of descriptor ring */
	FirstFrag	= (1 << 29), /* First segment of a packet */
	LastFrag	= (1 << 28), /* Final segment of a packet */
पूर्ण;

/* Generic हाल. */
क्रमागत rtl_tx_desc_bit अणु
	/* First द्विगुनword. */
	TD_LSO		= (1 << 27),		/* Large Send Offload */
#घोषणा TD_MSS_MAX			0x07ffu	/* MSS value */

	/* Second द्विगुनword. */
	TxVlanTag	= (1 << 17),		/* Add VLAN tag */
पूर्ण;

/* 8169, 8168b and 810x except 8102e. */
क्रमागत rtl_tx_desc_bit_0 अणु
	/* First द्विगुनword. */
#घोषणा TD0_MSS_SHIFT			16	/* MSS position (11 bits) */
	TD0_TCP_CS	= (1 << 16),		/* Calculate TCP/IP checksum */
	TD0_UDP_CS	= (1 << 17),		/* Calculate UDP/IP checksum */
	TD0_IP_CS	= (1 << 18),		/* Calculate IP checksum */
पूर्ण;

/* 8102e, 8168c and beyond. */
क्रमागत rtl_tx_desc_bit_1 अणु
	/* First द्विगुनword. */
	TD1_GTSENV4	= (1 << 26),		/* Giant Send क्रम IPv4 */
	TD1_GTSENV6	= (1 << 25),		/* Giant Send क्रम IPv6 */
#घोषणा GTTCPHO_SHIFT			18
#घोषणा GTTCPHO_MAX			0x7f

	/* Second द्विगुनword. */
#घोषणा TCPHO_SHIFT			18
#घोषणा TCPHO_MAX			0x3ff
#घोषणा TD1_MSS_SHIFT			18	/* MSS position (11 bits) */
	TD1_IPv6_CS	= (1 << 28),		/* Calculate IPv6 checksum */
	TD1_IPv4_CS	= (1 << 29),		/* Calculate IPv4 checksum */
	TD1_TCP_CS	= (1 << 30),		/* Calculate TCP/IP checksum */
	TD1_UDP_CS	= (1 << 31),		/* Calculate UDP/IP checksum */
पूर्ण;

क्रमागत rtl_rx_desc_bit अणु
	/* Rx निजी */
	PID1		= (1 << 18), /* Protocol ID bit 1/2 */
	PID0		= (1 << 17), /* Protocol ID bit 0/2 */

#घोषणा RxProtoUDP	(PID1)
#घोषणा RxProtoTCP	(PID0)
#घोषणा RxProtoIP	(PID1 | PID0)
#घोषणा RxProtoMask	RxProtoIP

	IPFail		= (1 << 16), /* IP checksum failed */
	UDPFail		= (1 << 15), /* UDP/IP checksum failed */
	TCPFail		= (1 << 14), /* TCP/IP checksum failed */

#घोषणा RxCSFailMask	(IPFail | UDPFail | TCPFail)

	RxVlanTag	= (1 << 16), /* VLAN tag available */
पूर्ण;

#घोषणा RTL_GSO_MAX_SIZE_V1	32000
#घोषणा RTL_GSO_MAX_SEGS_V1	24
#घोषणा RTL_GSO_MAX_SIZE_V2	64000
#घोषणा RTL_GSO_MAX_SEGS_V2	64

काष्ठा TxDesc अणु
	__le32 opts1;
	__le32 opts2;
	__le64 addr;
पूर्ण;

काष्ठा RxDesc अणु
	__le32 opts1;
	__le32 opts2;
	__le64 addr;
पूर्ण;

काष्ठा ring_info अणु
	काष्ठा sk_buff	*skb;
	u32		len;
पूर्ण;

काष्ठा rtl8169_counters अणु
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
	__le16	tx_underun;
पूर्ण;

काष्ठा rtl8169_tc_offsets अणु
	bool	inited;
	__le64	tx_errors;
	__le32	tx_multi_collision;
	__le16	tx_पातed;
	__le16	rx_missed;
पूर्ण;

क्रमागत rtl_flag अणु
	RTL_FLAG_TASK_ENABLED = 0,
	RTL_FLAG_TASK_RESET_PENDING,
	RTL_FLAG_MAX
पूर्ण;

क्रमागत rtl_dash_type अणु
	RTL_DASH_NONE,
	RTL_DASH_DP,
	RTL_DASH_EP,
पूर्ण;

काष्ठा rtl8169_निजी अणु
	व्योम __iomem *mmio_addr;	/* memory map physical address */
	काष्ठा pci_dev *pci_dev;
	काष्ठा net_device *dev;
	काष्ठा phy_device *phydev;
	काष्ठा napi_काष्ठा napi;
	क्रमागत mac_version mac_version;
	क्रमागत rtl_dash_type dash_type;
	u32 cur_rx; /* Index पूर्णांकo the Rx descriptor buffer of next Rx pkt. */
	u32 cur_tx; /* Index पूर्णांकo the Tx descriptor buffer of next Rx pkt. */
	u32 dirty_tx;
	काष्ठा TxDesc *TxDescArray;	/* 256-aligned Tx descriptor ring */
	काष्ठा RxDesc *RxDescArray;	/* 256-aligned Rx descriptor ring */
	dma_addr_t TxPhyAddr;
	dma_addr_t RxPhyAddr;
	काष्ठा page *Rx_databuff[NUM_RX_DESC];	/* Rx data buffers */
	काष्ठा ring_info tx_skb[NUM_TX_DESC];	/* Tx data buffers */
	u16 cp_cmd;
	u32 irq_mask;
	काष्ठा clk *clk;

	काष्ठा अणु
		DECLARE_BITMAP(flags, RTL_FLAG_MAX);
		काष्ठा work_काष्ठा work;
	पूर्ण wk;

	अचिन्हित supports_gmii:1;
	अचिन्हित aspm_manageable:1;
	dma_addr_t counters_phys_addr;
	काष्ठा rtl8169_counters *counters;
	काष्ठा rtl8169_tc_offsets tc_offset;
	u32 saved_wolopts;
	पूर्णांक eee_adv;

	स्थिर अक्षर *fw_name;
	काष्ठा rtl_fw *rtl_fw;

	u32 ocp_base;
पूर्ण;

प्रकार व्योम (*rtl_generic_fct)(काष्ठा rtl8169_निजी *tp);

MODULE_AUTHOR("Realtek and the Linux r8169 crew <netdev@vger.kernel.org>");
MODULE_DESCRIPTION("RealTek RTL-8169 Gigabit Ethernet driver");
MODULE_SOFTDEP("pre: realtek");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE_8168D_1);
MODULE_FIRMWARE(FIRMWARE_8168D_2);
MODULE_FIRMWARE(FIRMWARE_8168E_1);
MODULE_FIRMWARE(FIRMWARE_8168E_2);
MODULE_FIRMWARE(FIRMWARE_8168E_3);
MODULE_FIRMWARE(FIRMWARE_8105E_1);
MODULE_FIRMWARE(FIRMWARE_8168F_1);
MODULE_FIRMWARE(FIRMWARE_8168F_2);
MODULE_FIRMWARE(FIRMWARE_8402_1);
MODULE_FIRMWARE(FIRMWARE_8411_1);
MODULE_FIRMWARE(FIRMWARE_8411_2);
MODULE_FIRMWARE(FIRMWARE_8106E_1);
MODULE_FIRMWARE(FIRMWARE_8106E_2);
MODULE_FIRMWARE(FIRMWARE_8168G_2);
MODULE_FIRMWARE(FIRMWARE_8168G_3);
MODULE_FIRMWARE(FIRMWARE_8168H_1);
MODULE_FIRMWARE(FIRMWARE_8168H_2);
MODULE_FIRMWARE(FIRMWARE_8168FP_3);
MODULE_FIRMWARE(FIRMWARE_8107E_1);
MODULE_FIRMWARE(FIRMWARE_8107E_2);
MODULE_FIRMWARE(FIRMWARE_8125A_3);
MODULE_FIRMWARE(FIRMWARE_8125B_2);

अटल अंतरभूत काष्ठा device *tp_to_dev(काष्ठा rtl8169_निजी *tp)
अणु
	वापस &tp->pci_dev->dev;
पूर्ण

अटल व्योम rtl_lock_config_regs(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, Cfg9346, Cfg9346_Lock);
पूर्ण

अटल व्योम rtl_unlock_config_regs(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, Cfg9346, Cfg9346_Unlock);
पूर्ण

अटल व्योम rtl_pci_commit(काष्ठा rtl8169_निजी *tp)
अणु
	/* Read an arbitrary रेजिस्टर to commit a preceding PCI ग_लिखो */
	RTL_R8(tp, ChipCmd);
पूर्ण

अटल bool rtl_is_8125(काष्ठा rtl8169_निजी *tp)
अणु
	वापस tp->mac_version >= RTL_GIGA_MAC_VER_60;
पूर्ण

अटल bool rtl_is_8168evl_up(काष्ठा rtl8169_निजी *tp)
अणु
	वापस tp->mac_version >= RTL_GIGA_MAC_VER_34 &&
	       tp->mac_version != RTL_GIGA_MAC_VER_39 &&
	       tp->mac_version <= RTL_GIGA_MAC_VER_53;
पूर्ण

अटल bool rtl_supports_eee(काष्ठा rtl8169_निजी *tp)
अणु
	वापस tp->mac_version >= RTL_GIGA_MAC_VER_34 &&
	       tp->mac_version != RTL_GIGA_MAC_VER_37 &&
	       tp->mac_version != RTL_GIGA_MAC_VER_39;
पूर्ण

अटल व्योम rtl_पढ़ो_mac_from_reg(काष्ठा rtl8169_निजी *tp, u8 *mac, पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		mac[i] = RTL_R8(tp, reg + i);
पूर्ण

काष्ठा rtl_cond अणु
	bool (*check)(काष्ठा rtl8169_निजी *);
	स्थिर अक्षर *msg;
पूर्ण;

अटल bool rtl_loop_रुको(काष्ठा rtl8169_निजी *tp, स्थिर काष्ठा rtl_cond *c,
			  अचिन्हित दीर्घ usecs, पूर्णांक n, bool high)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		अगर (c->check(tp) == high)
			वापस true;
		fsleep(usecs);
	पूर्ण

	अगर (net_ratelimit())
		netdev_err(tp->dev, "%s == %d (loop: %d, delay: %lu).\n",
			   c->msg, !high, n, usecs);
	वापस false;
पूर्ण

अटल bool rtl_loop_रुको_high(काष्ठा rtl8169_निजी *tp,
			       स्थिर काष्ठा rtl_cond *c,
			       अचिन्हित दीर्घ d, पूर्णांक n)
अणु
	वापस rtl_loop_रुको(tp, c, d, n, true);
पूर्ण

अटल bool rtl_loop_रुको_low(काष्ठा rtl8169_निजी *tp,
			      स्थिर काष्ठा rtl_cond *c,
			      अचिन्हित दीर्घ d, पूर्णांक n)
अणु
	वापस rtl_loop_रुको(tp, c, d, n, false);
पूर्ण

#घोषणा DECLARE_RTL_COND(name)				\
अटल bool name ## _check(काष्ठा rtl8169_निजी *);	\
							\
अटल स्थिर काष्ठा rtl_cond name = अणु			\
	.check	= name ## _check,			\
	.msg	= #name					\
पूर्ण;							\
							\
अटल bool name ## _check(काष्ठा rtl8169_निजी *tp)

अटल व्योम r8168fp_adjust_ocp_cmd(काष्ठा rtl8169_निजी *tp, u32 *cmd, पूर्णांक type)
अणु
	/* based on RTL8168FP_OOBMAC_BASE in venकरोr driver */
	अगर (type == ERIAR_OOB &&
	    (tp->mac_version == RTL_GIGA_MAC_VER_52 ||
	     tp->mac_version == RTL_GIGA_MAC_VER_53))
		*cmd |= 0xf70 << 18;
पूर्ण

DECLARE_RTL_COND(rtl_eriar_cond)
अणु
	वापस RTL_R32(tp, ERIAR) & ERIAR_FLAG;
पूर्ण

अटल व्योम _rtl_eri_ग_लिखो(काष्ठा rtl8169_निजी *tp, पूर्णांक addr, u32 mask,
			   u32 val, पूर्णांक type)
अणु
	u32 cmd = ERIAR_WRITE_CMD | type | mask | addr;

	अगर (WARN(addr & 3 || !mask, "addr: 0x%x, mask: 0x%08x\n", addr, mask))
		वापस;

	RTL_W32(tp, ERIDR, val);
	r8168fp_adjust_ocp_cmd(tp, &cmd, type);
	RTL_W32(tp, ERIAR, cmd);

	rtl_loop_रुको_low(tp, &rtl_eriar_cond, 100, 100);
पूर्ण

अटल व्योम rtl_eri_ग_लिखो(काष्ठा rtl8169_निजी *tp, पूर्णांक addr, u32 mask,
			  u32 val)
अणु
	_rtl_eri_ग_लिखो(tp, addr, mask, val, ERIAR_EXGMAC);
पूर्ण

अटल u32 _rtl_eri_पढ़ो(काष्ठा rtl8169_निजी *tp, पूर्णांक addr, पूर्णांक type)
अणु
	u32 cmd = ERIAR_READ_CMD | type | ERIAR_MASK_1111 | addr;

	r8168fp_adjust_ocp_cmd(tp, &cmd, type);
	RTL_W32(tp, ERIAR, cmd);

	वापस rtl_loop_रुको_high(tp, &rtl_eriar_cond, 100, 100) ?
		RTL_R32(tp, ERIDR) : ~0;
पूर्ण

अटल u32 rtl_eri_पढ़ो(काष्ठा rtl8169_निजी *tp, पूर्णांक addr)
अणु
	वापस _rtl_eri_पढ़ो(tp, addr, ERIAR_EXGMAC);
पूर्ण

अटल व्योम rtl_w0w1_eri(काष्ठा rtl8169_निजी *tp, पूर्णांक addr, u32 p, u32 m)
अणु
	u32 val = rtl_eri_पढ़ो(tp, addr);

	rtl_eri_ग_लिखो(tp, addr, ERIAR_MASK_1111, (val & ~m) | p);
पूर्ण

अटल व्योम rtl_eri_set_bits(काष्ठा rtl8169_निजी *tp, पूर्णांक addr, u32 p)
अणु
	rtl_w0w1_eri(tp, addr, p, 0);
पूर्ण

अटल व्योम rtl_eri_clear_bits(काष्ठा rtl8169_निजी *tp, पूर्णांक addr, u32 m)
अणु
	rtl_w0w1_eri(tp, addr, 0, m);
पूर्ण

अटल bool rtl_ocp_reg_failure(u32 reg)
अणु
	वापस WARN_ONCE(reg & 0xffff0001, "Invalid ocp reg %x!\n", reg);
पूर्ण

DECLARE_RTL_COND(rtl_ocp_gphy_cond)
अणु
	वापस RTL_R32(tp, GPHY_OCP) & OCPAR_FLAG;
पूर्ण

अटल व्योम r8168_phy_ocp_ग_लिखो(काष्ठा rtl8169_निजी *tp, u32 reg, u32 data)
अणु
	अगर (rtl_ocp_reg_failure(reg))
		वापस;

	RTL_W32(tp, GPHY_OCP, OCPAR_FLAG | (reg << 15) | data);

	rtl_loop_रुको_low(tp, &rtl_ocp_gphy_cond, 25, 10);
पूर्ण

अटल पूर्णांक r8168_phy_ocp_पढ़ो(काष्ठा rtl8169_निजी *tp, u32 reg)
अणु
	अगर (rtl_ocp_reg_failure(reg))
		वापस 0;

	RTL_W32(tp, GPHY_OCP, reg << 15);

	वापस rtl_loop_रुको_high(tp, &rtl_ocp_gphy_cond, 25, 10) ?
		(RTL_R32(tp, GPHY_OCP) & 0xffff) : -ETIMEDOUT;
पूर्ण

अटल व्योम r8168_mac_ocp_ग_लिखो(काष्ठा rtl8169_निजी *tp, u32 reg, u32 data)
अणु
	अगर (rtl_ocp_reg_failure(reg))
		वापस;

	RTL_W32(tp, OCPDR, OCPAR_FLAG | (reg << 15) | data);
पूर्ण

अटल u16 r8168_mac_ocp_पढ़ो(काष्ठा rtl8169_निजी *tp, u32 reg)
अणु
	अगर (rtl_ocp_reg_failure(reg))
		वापस 0;

	RTL_W32(tp, OCPDR, reg << 15);

	वापस RTL_R32(tp, OCPDR);
पूर्ण

अटल व्योम r8168_mac_ocp_modअगरy(काष्ठा rtl8169_निजी *tp, u32 reg, u16 mask,
				 u16 set)
अणु
	u16 data = r8168_mac_ocp_पढ़ो(tp, reg);

	r8168_mac_ocp_ग_लिखो(tp, reg, (data & ~mask) | set);
पूर्ण

/* Work around a hw issue with RTL8168g PHY, the quirk disables
 * PHY MCU पूर्णांकerrupts beक्रमe PHY घातer-करोwn.
 */
अटल व्योम rtl8168g_phy_suspend_quirk(काष्ठा rtl8169_निजी *tp, पूर्णांक value)
अणु
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_40:
	हाल RTL_GIGA_MAC_VER_41:
	हाल RTL_GIGA_MAC_VER_49:
		अगर (value & BMCR_RESET || !(value & BMCR_PDOWN))
			rtl_eri_set_bits(tp, 0x1a8, 0xfc000000);
		अन्यथा
			rtl_eri_clear_bits(tp, 0x1a8, 0xfc000000);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण;

अटल व्योम r8168g_mdio_ग_लिखो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg, पूर्णांक value)
अणु
	अगर (reg == 0x1f) अणु
		tp->ocp_base = value ? value << 4 : OCP_STD_PHY_BASE;
		वापस;
	पूर्ण

	अगर (tp->ocp_base != OCP_STD_PHY_BASE)
		reg -= 0x10;

	अगर (tp->ocp_base == OCP_STD_PHY_BASE && reg == MII_BMCR)
		rtl8168g_phy_suspend_quirk(tp, value);

	r8168_phy_ocp_ग_लिखो(tp, tp->ocp_base + reg * 2, value);
पूर्ण

अटल पूर्णांक r8168g_mdio_पढ़ो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg)
अणु
	अगर (reg == 0x1f)
		वापस tp->ocp_base == OCP_STD_PHY_BASE ? 0 : tp->ocp_base >> 4;

	अगर (tp->ocp_base != OCP_STD_PHY_BASE)
		reg -= 0x10;

	वापस r8168_phy_ocp_पढ़ो(tp, tp->ocp_base + reg * 2);
पूर्ण

अटल व्योम mac_mcu_ग_लिखो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg, पूर्णांक value)
अणु
	अगर (reg == 0x1f) अणु
		tp->ocp_base = value << 4;
		वापस;
	पूर्ण

	r8168_mac_ocp_ग_लिखो(tp, tp->ocp_base + reg, value);
पूर्ण

अटल पूर्णांक mac_mcu_पढ़ो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg)
अणु
	वापस r8168_mac_ocp_पढ़ो(tp, tp->ocp_base + reg);
पूर्ण

DECLARE_RTL_COND(rtl_phyar_cond)
अणु
	वापस RTL_R32(tp, PHYAR) & 0x80000000;
पूर्ण

अटल व्योम r8169_mdio_ग_लिखो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg, पूर्णांक value)
अणु
	RTL_W32(tp, PHYAR, 0x80000000 | (reg & 0x1f) << 16 | (value & 0xffff));

	rtl_loop_रुको_low(tp, &rtl_phyar_cond, 25, 20);
	/*
	 * According to hardware specs a 20us delay is required after ग_लिखो
	 * complete indication, but beक्रमe sending next command.
	 */
	udelay(20);
पूर्ण

अटल पूर्णांक r8169_mdio_पढ़ो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg)
अणु
	पूर्णांक value;

	RTL_W32(tp, PHYAR, 0x0 | (reg & 0x1f) << 16);

	value = rtl_loop_रुको_high(tp, &rtl_phyar_cond, 25, 20) ?
		RTL_R32(tp, PHYAR) & 0xffff : -ETIMEDOUT;

	/*
	 * According to hardware specs a 20us delay is required after पढ़ो
	 * complete indication, but beक्रमe sending next command.
	 */
	udelay(20);

	वापस value;
पूर्ण

DECLARE_RTL_COND(rtl_ocpar_cond)
अणु
	वापस RTL_R32(tp, OCPAR) & OCPAR_FLAG;
पूर्ण

अटल व्योम r8168dp_1_mdio_access(काष्ठा rtl8169_निजी *tp, पूर्णांक reg, u32 data)
अणु
	RTL_W32(tp, OCPDR, data | ((reg & OCPDR_REG_MASK) << OCPDR_GPHY_REG_SHIFT));
	RTL_W32(tp, OCPAR, OCPAR_GPHY_WRITE_CMD);
	RTL_W32(tp, EPHY_RXER_NUM, 0);

	rtl_loop_रुको_low(tp, &rtl_ocpar_cond, 1000, 100);
पूर्ण

अटल व्योम r8168dp_1_mdio_ग_लिखो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg, पूर्णांक value)
अणु
	r8168dp_1_mdio_access(tp, reg,
			      OCPDR_WRITE_CMD | (value & OCPDR_DATA_MASK));
पूर्ण

अटल पूर्णांक r8168dp_1_mdio_पढ़ो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg)
अणु
	r8168dp_1_mdio_access(tp, reg, OCPDR_READ_CMD);

	mdelay(1);
	RTL_W32(tp, OCPAR, OCPAR_GPHY_READ_CMD);
	RTL_W32(tp, EPHY_RXER_NUM, 0);

	वापस rtl_loop_रुको_high(tp, &rtl_ocpar_cond, 1000, 100) ?
		RTL_R32(tp, OCPDR) & OCPDR_DATA_MASK : -ETIMEDOUT;
पूर्ण

#घोषणा R8168DP_1_MDIO_ACCESS_BIT	0x00020000

अटल व्योम r8168dp_2_mdio_start(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W32(tp, 0xd0, RTL_R32(tp, 0xd0) & ~R8168DP_1_MDIO_ACCESS_BIT);
पूर्ण

अटल व्योम r8168dp_2_mdio_stop(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W32(tp, 0xd0, RTL_R32(tp, 0xd0) | R8168DP_1_MDIO_ACCESS_BIT);
पूर्ण

अटल व्योम r8168dp_2_mdio_ग_लिखो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg, पूर्णांक value)
अणु
	r8168dp_2_mdio_start(tp);

	r8169_mdio_ग_लिखो(tp, reg, value);

	r8168dp_2_mdio_stop(tp);
पूर्ण

अटल पूर्णांक r8168dp_2_mdio_पढ़ो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg)
अणु
	पूर्णांक value;

	/* Work around issue with chip reporting wrong PHY ID */
	अगर (reg == MII_PHYSID2)
		वापस 0xc912;

	r8168dp_2_mdio_start(tp);

	value = r8169_mdio_पढ़ो(tp, reg);

	r8168dp_2_mdio_stop(tp);

	वापस value;
पूर्ण

अटल व्योम rtl_ग_लिखोphy(काष्ठा rtl8169_निजी *tp, पूर्णांक location, पूर्णांक val)
अणु
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_27:
		r8168dp_1_mdio_ग_लिखो(tp, location, val);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_28:
	हाल RTL_GIGA_MAC_VER_31:
		r8168dp_2_mdio_ग_लिखो(tp, location, val);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_40 ... RTL_GIGA_MAC_VER_63:
		r8168g_mdio_ग_लिखो(tp, location, val);
		अवरोध;
	शेष:
		r8169_mdio_ग_लिखो(tp, location, val);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rtl_पढ़ोphy(काष्ठा rtl8169_निजी *tp, पूर्णांक location)
अणु
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_27:
		वापस r8168dp_1_mdio_पढ़ो(tp, location);
	हाल RTL_GIGA_MAC_VER_28:
	हाल RTL_GIGA_MAC_VER_31:
		वापस r8168dp_2_mdio_पढ़ो(tp, location);
	हाल RTL_GIGA_MAC_VER_40 ... RTL_GIGA_MAC_VER_63:
		वापस r8168g_mdio_पढ़ो(tp, location);
	शेष:
		वापस r8169_mdio_पढ़ो(tp, location);
	पूर्ण
पूर्ण

DECLARE_RTL_COND(rtl_ephyar_cond)
अणु
	वापस RTL_R32(tp, EPHYAR) & EPHYAR_FLAG;
पूर्ण

अटल व्योम rtl_ephy_ग_लिखो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg_addr, पूर्णांक value)
अणु
	RTL_W32(tp, EPHYAR, EPHYAR_WRITE_CMD | (value & EPHYAR_DATA_MASK) |
		(reg_addr & EPHYAR_REG_MASK) << EPHYAR_REG_SHIFT);

	rtl_loop_रुको_low(tp, &rtl_ephyar_cond, 10, 100);

	udelay(10);
पूर्ण

अटल u16 rtl_ephy_पढ़ो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg_addr)
अणु
	RTL_W32(tp, EPHYAR, (reg_addr & EPHYAR_REG_MASK) << EPHYAR_REG_SHIFT);

	वापस rtl_loop_रुको_high(tp, &rtl_ephyar_cond, 10, 100) ?
		RTL_R32(tp, EPHYAR) & EPHYAR_DATA_MASK : ~0;
पूर्ण

अटल u32 r8168dp_ocp_पढ़ो(काष्ठा rtl8169_निजी *tp, u16 reg)
अणु
	RTL_W32(tp, OCPAR, 0x0fu << 12 | (reg & 0x0fff));
	वापस rtl_loop_रुको_high(tp, &rtl_ocpar_cond, 100, 20) ?
		RTL_R32(tp, OCPDR) : ~0;
पूर्ण

अटल u32 r8168ep_ocp_पढ़ो(काष्ठा rtl8169_निजी *tp, u16 reg)
अणु
	वापस _rtl_eri_पढ़ो(tp, reg, ERIAR_OOB);
पूर्ण

अटल व्योम r8168dp_ocp_ग_लिखो(काष्ठा rtl8169_निजी *tp, u8 mask, u16 reg,
			      u32 data)
अणु
	RTL_W32(tp, OCPDR, data);
	RTL_W32(tp, OCPAR, OCPAR_FLAG | ((u32)mask & 0x0f) << 12 | (reg & 0x0fff));
	rtl_loop_रुको_low(tp, &rtl_ocpar_cond, 100, 20);
पूर्ण

अटल व्योम r8168ep_ocp_ग_लिखो(काष्ठा rtl8169_निजी *tp, u8 mask, u16 reg,
			      u32 data)
अणु
	_rtl_eri_ग_लिखो(tp, reg, ((u32)mask & 0x0f) << ERIAR_MASK_SHIFT,
		       data, ERIAR_OOB);
पूर्ण

अटल व्योम r8168dp_oob_notअगरy(काष्ठा rtl8169_निजी *tp, u8 cmd)
अणु
	rtl_eri_ग_लिखो(tp, 0xe8, ERIAR_MASK_0001, cmd);

	r8168dp_ocp_ग_लिखो(tp, 0x1, 0x30, 0x00000001);
पूर्ण

#घोषणा OOB_CMD_RESET		0x00
#घोषणा OOB_CMD_DRIVER_START	0x05
#घोषणा OOB_CMD_DRIVER_STOP	0x06

अटल u16 rtl8168_get_ocp_reg(काष्ठा rtl8169_निजी *tp)
अणु
	वापस (tp->mac_version == RTL_GIGA_MAC_VER_31) ? 0xb8 : 0x10;
पूर्ण

DECLARE_RTL_COND(rtl_dp_ocp_पढ़ो_cond)
अणु
	u16 reg;

	reg = rtl8168_get_ocp_reg(tp);

	वापस r8168dp_ocp_पढ़ो(tp, reg) & 0x00000800;
पूर्ण

DECLARE_RTL_COND(rtl_ep_ocp_पढ़ो_cond)
अणु
	वापस r8168ep_ocp_पढ़ो(tp, 0x124) & 0x00000001;
पूर्ण

DECLARE_RTL_COND(rtl_ocp_tx_cond)
अणु
	वापस RTL_R8(tp, IBISR0) & 0x20;
पूर्ण

अटल व्योम rtl8168ep_stop_cmac(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, IBCR2, RTL_R8(tp, IBCR2) & ~0x01);
	rtl_loop_रुको_high(tp, &rtl_ocp_tx_cond, 50000, 2000);
	RTL_W8(tp, IBISR0, RTL_R8(tp, IBISR0) | 0x20);
	RTL_W8(tp, IBCR0, RTL_R8(tp, IBCR0) & ~0x01);
पूर्ण

अटल व्योम rtl8168dp_driver_start(काष्ठा rtl8169_निजी *tp)
अणु
	r8168dp_oob_notअगरy(tp, OOB_CMD_DRIVER_START);
	rtl_loop_रुको_high(tp, &rtl_dp_ocp_पढ़ो_cond, 10000, 10);
पूर्ण

अटल व्योम rtl8168ep_driver_start(काष्ठा rtl8169_निजी *tp)
अणु
	r8168ep_ocp_ग_लिखो(tp, 0x01, 0x180, OOB_CMD_DRIVER_START);
	r8168ep_ocp_ग_लिखो(tp, 0x01, 0x30, r8168ep_ocp_पढ़ो(tp, 0x30) | 0x01);
	rtl_loop_रुको_high(tp, &rtl_ep_ocp_पढ़ो_cond, 10000, 10);
पूर्ण

अटल व्योम rtl8168_driver_start(काष्ठा rtl8169_निजी *tp)
अणु
	अगर (tp->dash_type == RTL_DASH_DP)
		rtl8168dp_driver_start(tp);
	अन्यथा
		rtl8168ep_driver_start(tp);
पूर्ण

अटल व्योम rtl8168dp_driver_stop(काष्ठा rtl8169_निजी *tp)
अणु
	r8168dp_oob_notअगरy(tp, OOB_CMD_DRIVER_STOP);
	rtl_loop_रुको_low(tp, &rtl_dp_ocp_पढ़ो_cond, 10000, 10);
पूर्ण

अटल व्योम rtl8168ep_driver_stop(काष्ठा rtl8169_निजी *tp)
अणु
	rtl8168ep_stop_cmac(tp);
	r8168ep_ocp_ग_लिखो(tp, 0x01, 0x180, OOB_CMD_DRIVER_STOP);
	r8168ep_ocp_ग_लिखो(tp, 0x01, 0x30, r8168ep_ocp_पढ़ो(tp, 0x30) | 0x01);
	rtl_loop_रुको_low(tp, &rtl_ep_ocp_पढ़ो_cond, 10000, 10);
पूर्ण

अटल व्योम rtl8168_driver_stop(काष्ठा rtl8169_निजी *tp)
अणु
	अगर (tp->dash_type == RTL_DASH_DP)
		rtl8168dp_driver_stop(tp);
	अन्यथा
		rtl8168ep_driver_stop(tp);
पूर्ण

अटल bool r8168dp_check_dash(काष्ठा rtl8169_निजी *tp)
अणु
	u16 reg = rtl8168_get_ocp_reg(tp);

	वापस r8168dp_ocp_पढ़ो(tp, reg) & BIT(15);
पूर्ण

अटल bool r8168ep_check_dash(काष्ठा rtl8169_निजी *tp)
अणु
	वापस r8168ep_ocp_पढ़ो(tp, 0x128) & BIT(0);
पूर्ण

अटल क्रमागत rtl_dash_type rtl_check_dash(काष्ठा rtl8169_निजी *tp)
अणु
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_27:
	हाल RTL_GIGA_MAC_VER_28:
	हाल RTL_GIGA_MAC_VER_31:
		वापस r8168dp_check_dash(tp) ? RTL_DASH_DP : RTL_DASH_NONE;
	हाल RTL_GIGA_MAC_VER_49 ... RTL_GIGA_MAC_VER_53:
		वापस r8168ep_check_dash(tp) ? RTL_DASH_EP : RTL_DASH_NONE;
	शेष:
		वापस RTL_DASH_NONE;
	पूर्ण
पूर्ण

अटल व्योम rtl_set_d3_pll_करोwn(काष्ठा rtl8169_निजी *tp, bool enable)
अणु
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_25 ... RTL_GIGA_MAC_VER_26:
	हाल RTL_GIGA_MAC_VER_29 ... RTL_GIGA_MAC_VER_30:
	हाल RTL_GIGA_MAC_VER_32 ... RTL_GIGA_MAC_VER_37:
	हाल RTL_GIGA_MAC_VER_39 ... RTL_GIGA_MAC_VER_63:
		अगर (enable)
			RTL_W8(tp, PMCH, RTL_R8(tp, PMCH) & ~D3_NO_PLL_DOWN);
		अन्यथा
			RTL_W8(tp, PMCH, RTL_R8(tp, PMCH) | D3_NO_PLL_DOWN);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtl_reset_packet_filter(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_eri_clear_bits(tp, 0xdc, BIT(0));
	rtl_eri_set_bits(tp, 0xdc, BIT(0));
पूर्ण

DECLARE_RTL_COND(rtl_efusear_cond)
अणु
	वापस RTL_R32(tp, EFUSEAR) & EFUSEAR_FLAG;
पूर्ण

u8 rtl8168d_efuse_पढ़ो(काष्ठा rtl8169_निजी *tp, पूर्णांक reg_addr)
अणु
	RTL_W32(tp, EFUSEAR, (reg_addr & EFUSEAR_REG_MASK) << EFUSEAR_REG_SHIFT);

	वापस rtl_loop_रुको_high(tp, &rtl_efusear_cond, 100, 300) ?
		RTL_R32(tp, EFUSEAR) & EFUSEAR_DATA_MASK : ~0;
पूर्ण

अटल u32 rtl_get_events(काष्ठा rtl8169_निजी *tp)
अणु
	अगर (rtl_is_8125(tp))
		वापस RTL_R32(tp, IntrStatus_8125);
	अन्यथा
		वापस RTL_R16(tp, IntrStatus);
पूर्ण

अटल व्योम rtl_ack_events(काष्ठा rtl8169_निजी *tp, u32 bits)
अणु
	अगर (rtl_is_8125(tp))
		RTL_W32(tp, IntrStatus_8125, bits);
	अन्यथा
		RTL_W16(tp, IntrStatus, bits);
पूर्ण

अटल व्योम rtl_irq_disable(काष्ठा rtl8169_निजी *tp)
अणु
	अगर (rtl_is_8125(tp))
		RTL_W32(tp, IntrMask_8125, 0);
	अन्यथा
		RTL_W16(tp, IntrMask, 0);
पूर्ण

अटल व्योम rtl_irq_enable(काष्ठा rtl8169_निजी *tp)
अणु
	अगर (rtl_is_8125(tp))
		RTL_W32(tp, IntrMask_8125, tp->irq_mask);
	अन्यथा
		RTL_W16(tp, IntrMask, tp->irq_mask);
पूर्ण

अटल व्योम rtl8169_irq_mask_and_ack(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_irq_disable(tp);
	rtl_ack_events(tp, 0xffffffff);
	rtl_pci_commit(tp);
पूर्ण

अटल व्योम rtl_link_chg_patch(काष्ठा rtl8169_निजी *tp)
अणु
	काष्ठा phy_device *phydev = tp->phydev;

	अगर (tp->mac_version == RTL_GIGA_MAC_VER_34 ||
	    tp->mac_version == RTL_GIGA_MAC_VER_38) अणु
		अगर (phydev->speed == SPEED_1000) अणु
			rtl_eri_ग_लिखो(tp, 0x1bc, ERIAR_MASK_1111, 0x00000011);
			rtl_eri_ग_लिखो(tp, 0x1dc, ERIAR_MASK_1111, 0x00000005);
		पूर्ण अन्यथा अगर (phydev->speed == SPEED_100) अणु
			rtl_eri_ग_लिखो(tp, 0x1bc, ERIAR_MASK_1111, 0x0000001f);
			rtl_eri_ग_लिखो(tp, 0x1dc, ERIAR_MASK_1111, 0x00000005);
		पूर्ण अन्यथा अणु
			rtl_eri_ग_लिखो(tp, 0x1bc, ERIAR_MASK_1111, 0x0000001f);
			rtl_eri_ग_लिखो(tp, 0x1dc, ERIAR_MASK_1111, 0x0000003f);
		पूर्ण
		rtl_reset_packet_filter(tp);
	पूर्ण अन्यथा अगर (tp->mac_version == RTL_GIGA_MAC_VER_35 ||
		   tp->mac_version == RTL_GIGA_MAC_VER_36) अणु
		अगर (phydev->speed == SPEED_1000) अणु
			rtl_eri_ग_लिखो(tp, 0x1bc, ERIAR_MASK_1111, 0x00000011);
			rtl_eri_ग_लिखो(tp, 0x1dc, ERIAR_MASK_1111, 0x00000005);
		पूर्ण अन्यथा अणु
			rtl_eri_ग_लिखो(tp, 0x1bc, ERIAR_MASK_1111, 0x0000001f);
			rtl_eri_ग_लिखो(tp, 0x1dc, ERIAR_MASK_1111, 0x0000003f);
		पूर्ण
	पूर्ण अन्यथा अगर (tp->mac_version == RTL_GIGA_MAC_VER_37) अणु
		अगर (phydev->speed == SPEED_10) अणु
			rtl_eri_ग_लिखो(tp, 0x1d0, ERIAR_MASK_0011, 0x4d02);
			rtl_eri_ग_लिखो(tp, 0x1dc, ERIAR_MASK_0011, 0x0060a);
		पूर्ण अन्यथा अणु
			rtl_eri_ग_लिखो(tp, 0x1d0, ERIAR_MASK_0011, 0x0000);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा WAKE_ANY (WAKE_PHY | WAKE_MAGIC | WAKE_UCAST | WAKE_BCAST | WAKE_MCAST)

अटल व्योम rtl8169_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);

	wol->supported = WAKE_ANY;
	wol->wolopts = tp->saved_wolopts;
पूर्ण

अटल व्योम __rtl8169_set_wol(काष्ठा rtl8169_निजी *tp, u32 wolopts)
अणु
	अटल स्थिर काष्ठा अणु
		u32 opt;
		u16 reg;
		u8  mask;
	पूर्ण cfg[] = अणु
		अणु WAKE_PHY,   Config3, LinkUp पूर्ण,
		अणु WAKE_UCAST, Config5, UWF पूर्ण,
		अणु WAKE_BCAST, Config5, BWF पूर्ण,
		अणु WAKE_MCAST, Config5, MWF पूर्ण,
		अणु WAKE_ANY,   Config5, LanWake पूर्ण,
		अणु WAKE_MAGIC, Config3, MagicPacket पूर्ण
	पूर्ण;
	अचिन्हित पूर्णांक i, पंचांगp = ARRAY_SIZE(cfg);
	u8 options;

	rtl_unlock_config_regs(tp);

	अगर (rtl_is_8168evl_up(tp)) अणु
		पंचांगp--;
		अगर (wolopts & WAKE_MAGIC)
			rtl_eri_set_bits(tp, 0x0dc, MagicPacket_v2);
		अन्यथा
			rtl_eri_clear_bits(tp, 0x0dc, MagicPacket_v2);
	पूर्ण अन्यथा अगर (rtl_is_8125(tp)) अणु
		पंचांगp--;
		अगर (wolopts & WAKE_MAGIC)
			r8168_mac_ocp_modअगरy(tp, 0xc0b6, 0, BIT(0));
		अन्यथा
			r8168_mac_ocp_modअगरy(tp, 0xc0b6, BIT(0), 0);
	पूर्ण

	क्रम (i = 0; i < पंचांगp; i++) अणु
		options = RTL_R8(tp, cfg[i].reg) & ~cfg[i].mask;
		अगर (wolopts & cfg[i].opt)
			options |= cfg[i].mask;
		RTL_W8(tp, cfg[i].reg, options);
	पूर्ण

	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_02 ... RTL_GIGA_MAC_VER_06:
		options = RTL_R8(tp, Config1) & ~PMEnable;
		अगर (wolopts)
			options |= PMEnable;
		RTL_W8(tp, Config1, options);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_34:
	हाल RTL_GIGA_MAC_VER_37:
	हाल RTL_GIGA_MAC_VER_39 ... RTL_GIGA_MAC_VER_63:
		options = RTL_R8(tp, Config2) & ~PME_SIGNAL;
		अगर (wolopts)
			options |= PME_SIGNAL;
		RTL_W8(tp, Config2, options);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rtl_lock_config_regs(tp);

	device_set_wakeup_enable(tp_to_dev(tp), wolopts);
	rtl_set_d3_pll_करोwn(tp, !wolopts);
	tp->dev->wol_enabled = wolopts ? 1 : 0;
पूर्ण

अटल पूर्णांक rtl8169_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);

	अगर (wol->wolopts & ~WAKE_ANY)
		वापस -EINVAL;

	tp->saved_wolopts = wol->wolopts;
	__rtl8169_set_wol(tp, tp->saved_wolopts);

	वापस 0;
पूर्ण

अटल व्योम rtl8169_get_drvinfo(काष्ठा net_device *dev,
				काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	काष्ठा rtl_fw *rtl_fw = tp->rtl_fw;

	strlcpy(info->driver, MODULENAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(tp->pci_dev), माप(info->bus_info));
	BUILD_BUG_ON(माप(info->fw_version) < माप(rtl_fw->version));
	अगर (rtl_fw)
		strlcpy(info->fw_version, rtl_fw->version,
			माप(info->fw_version));
पूर्ण

अटल पूर्णांक rtl8169_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस R8169_REGS_SIZE;
पूर्ण

अटल netdev_features_t rtl8169_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);

	अगर (dev->mtu > TD_MSS_MAX)
		features &= ~NETIF_F_ALL_TSO;

	अगर (dev->mtu > ETH_DATA_LEN &&
	    tp->mac_version > RTL_GIGA_MAC_VER_06)
		features &= ~(NETIF_F_CSUM_MASK | NETIF_F_ALL_TSO);

	वापस features;
पूर्ण

अटल व्योम rtl_set_rx_config_features(काष्ठा rtl8169_निजी *tp,
				       netdev_features_t features)
अणु
	u32 rx_config = RTL_R32(tp, RxConfig);

	अगर (features & NETIF_F_RXALL)
		rx_config |= RX_CONFIG_ACCEPT_ERR_MASK;
	अन्यथा
		rx_config &= ~RX_CONFIG_ACCEPT_ERR_MASK;

	अगर (rtl_is_8125(tp)) अणु
		अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
			rx_config |= RX_VLAN_8125;
		अन्यथा
			rx_config &= ~RX_VLAN_8125;
	पूर्ण

	RTL_W32(tp, RxConfig, rx_config);
पूर्ण

अटल पूर्णांक rtl8169_set_features(काष्ठा net_device *dev,
				netdev_features_t features)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);

	rtl_set_rx_config_features(tp, features);

	अगर (features & NETIF_F_RXCSUM)
		tp->cp_cmd |= RxChkSum;
	अन्यथा
		tp->cp_cmd &= ~RxChkSum;

	अगर (!rtl_is_8125(tp)) अणु
		अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
			tp->cp_cmd |= RxVlan;
		अन्यथा
			tp->cp_cmd &= ~RxVlan;
	पूर्ण

	RTL_W16(tp, CPlusCmd, tp->cp_cmd);
	rtl_pci_commit(tp);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 rtl8169_tx_vlan_tag(काष्ठा sk_buff *skb)
अणु
	वापस (skb_vlan_tag_present(skb)) ?
		TxVlanTag | swab16(skb_vlan_tag_get(skb)) : 0x00;
पूर्ण

अटल व्योम rtl8169_rx_vlan_tag(काष्ठा RxDesc *desc, काष्ठा sk_buff *skb)
अणु
	u32 opts2 = le32_to_cpu(desc->opts2);

	अगर (opts2 & RxVlanTag)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), swab16(opts2 & 0xffff));
पूर्ण

अटल व्योम rtl8169_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			     व्योम *p)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	u32 __iomem *data = tp->mmio_addr;
	u32 *dw = p;
	पूर्णांक i;

	क्रम (i = 0; i < R8169_REGS_SIZE; i += 4)
		स_नकल_fromio(dw++, data++, 4);
पूर्ण

अटल स्थिर अक्षर rtl8169_gstrings[][ETH_GSTRING_LEN] = अणु
	"tx_packets",
	"rx_packets",
	"tx_errors",
	"rx_errors",
	"rx_missed",
	"align_errors",
	"tx_single_collisions",
	"tx_multi_collisions",
	"unicast",
	"broadcast",
	"multicast",
	"tx_aborted",
	"tx_underrun",
पूर्ण;

अटल पूर्णांक rtl8169_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(rtl8169_gstrings);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

DECLARE_RTL_COND(rtl_counters_cond)
अणु
	वापस RTL_R32(tp, CounterAddrLow) & (CounterReset | CounterDump);
पूर्ण

अटल व्योम rtl8169_करो_counters(काष्ठा rtl8169_निजी *tp, u32 counter_cmd)
अणु
	u32 cmd = lower_32_bits(tp->counters_phys_addr);

	RTL_W32(tp, CounterAddrHigh, upper_32_bits(tp->counters_phys_addr));
	rtl_pci_commit(tp);
	RTL_W32(tp, CounterAddrLow, cmd);
	RTL_W32(tp, CounterAddrLow, cmd | counter_cmd);

	rtl_loop_रुको_low(tp, &rtl_counters_cond, 10, 1000);
पूर्ण

अटल व्योम rtl8169_update_counters(काष्ठा rtl8169_निजी *tp)
अणु
	u8 val = RTL_R8(tp, ChipCmd);

	/*
	 * Some chips are unable to dump tally counters when the receiver
	 * is disabled. If 0xff chip may be in a PCI घातer-save state.
	 */
	अगर (val & CmdRxEnb && val != 0xff)
		rtl8169_करो_counters(tp, CounterDump);
पूर्ण

अटल व्योम rtl8169_init_counter_offsets(काष्ठा rtl8169_निजी *tp)
अणु
	काष्ठा rtl8169_counters *counters = tp->counters;

	/*
	 * rtl8169_init_counter_offsets is called from rtl_खोलो.  On chip
	 * versions prior to RTL_GIGA_MAC_VER_19 the tally counters are only
	 * reset by a घातer cycle, जबतक the counter values collected by the
	 * driver are reset at every driver unload/load cycle.
	 *
	 * To make sure the HW values वापसed by @get_stats64 match the SW
	 * values, we collect the initial values at first खोलो(*) and use them
	 * as offsets to normalize the values वापसed by @get_stats64.
	 *
	 * (*) We can't call rtl8169_init_counter_offsets from rtl_init_one
	 * क्रम the reason stated in rtl8169_update_counters; CmdRxEnb is only
	 * set at खोलो समय by rtl_hw_start.
	 */

	अगर (tp->tc_offset.inited)
		वापस;

	अगर (tp->mac_version >= RTL_GIGA_MAC_VER_19) अणु
		rtl8169_करो_counters(tp, CounterReset);
	पूर्ण अन्यथा अणु
		rtl8169_update_counters(tp);
		tp->tc_offset.tx_errors = counters->tx_errors;
		tp->tc_offset.tx_multi_collision = counters->tx_multi_collision;
		tp->tc_offset.tx_पातed = counters->tx_पातed;
		tp->tc_offset.rx_missed = counters->rx_missed;
	पूर्ण

	tp->tc_offset.inited = true;
पूर्ण

अटल व्योम rtl8169_get_ethtool_stats(काष्ठा net_device *dev,
				      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	काष्ठा rtl8169_counters *counters;

	counters = tp->counters;
	rtl8169_update_counters(tp);

	data[0] = le64_to_cpu(counters->tx_packets);
	data[1] = le64_to_cpu(counters->rx_packets);
	data[2] = le64_to_cpu(counters->tx_errors);
	data[3] = le32_to_cpu(counters->rx_errors);
	data[4] = le16_to_cpu(counters->rx_missed);
	data[5] = le16_to_cpu(counters->align_errors);
	data[6] = le32_to_cpu(counters->tx_one_collision);
	data[7] = le32_to_cpu(counters->tx_multi_collision);
	data[8] = le64_to_cpu(counters->rx_unicast);
	data[9] = le64_to_cpu(counters->rx_broadcast);
	data[10] = le32_to_cpu(counters->rx_multicast);
	data[11] = le16_to_cpu(counters->tx_पातed);
	data[12] = le16_to_cpu(counters->tx_underun);
पूर्ण

अटल व्योम rtl8169_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	चयन(stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, rtl8169_gstrings, माप(rtl8169_gstrings));
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Interrupt coalescing
 *
 * > 1 - the availability of the IntrMitigate (0xe2) रेजिस्टर through the
 * >     8169, 8168 and 810x line of chipsets
 *
 * 8169, 8168, and 8136(810x) serial chipsets support it.
 *
 * > 2 - the Tx समयr unit at gigabit speed
 *
 * The unit of the समयr depends on both the speed and the setting of CPlusCmd
 * (0xe0) bit 1 and bit 0.
 *
 * For 8169
 * bit[1:0] \ speed        1000M           100M            10M
 * 0 0                     320ns           2.56us          40.96us
 * 0 1                     2.56us          20.48us         327.7us
 * 1 0                     5.12us          40.96us         655.4us
 * 1 1                     10.24us         81.92us         1.31ms
 *
 * For the other
 * bit[1:0] \ speed        1000M           100M            10M
 * 0 0                     5us             2.56us          40.96us
 * 0 1                     40us            20.48us         327.7us
 * 1 0                     80us            40.96us         655.4us
 * 1 1                     160us           81.92us         1.31ms
 */

/* rx/tx scale factors क्रम all CPlusCmd[0:1] हालs */
काष्ठा rtl_coalesce_info अणु
	u32 speed;
	u32 scale_nsecs[4];
पूर्ण;

/* produce array with base delay *1, *8, *8*2, *8*2*2 */
#घोषणा COALESCE_DELAY(d) अणु (d), 8 * (d), 16 * (d), 32 * (d) पूर्ण

अटल स्थिर काष्ठा rtl_coalesce_info rtl_coalesce_info_8169[] = अणु
	अणु SPEED_1000,	COALESCE_DELAY(320) पूर्ण,
	अणु SPEED_100,	COALESCE_DELAY(2560) पूर्ण,
	अणु SPEED_10,	COALESCE_DELAY(40960) पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtl_coalesce_info rtl_coalesce_info_8168_8136[] = अणु
	अणु SPEED_1000,	COALESCE_DELAY(5000) पूर्ण,
	अणु SPEED_100,	COALESCE_DELAY(2560) पूर्ण,
	अणु SPEED_10,	COALESCE_DELAY(40960) पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
#अघोषित COALESCE_DELAY

/* get rx/tx scale vector corresponding to current speed */
अटल स्थिर काष्ठा rtl_coalesce_info *
rtl_coalesce_info(काष्ठा rtl8169_निजी *tp)
अणु
	स्थिर काष्ठा rtl_coalesce_info *ci;

	अगर (tp->mac_version <= RTL_GIGA_MAC_VER_06)
		ci = rtl_coalesce_info_8169;
	अन्यथा
		ci = rtl_coalesce_info_8168_8136;

	/* अगर speed is unknown assume highest one */
	अगर (tp->phydev->speed == SPEED_UNKNOWN)
		वापस ci;

	क्रम (; ci->speed; ci++) अणु
		अगर (tp->phydev->speed == ci->speed)
			वापस ci;
	पूर्ण

	वापस ERR_PTR(-ELNRNG);
पूर्ण

अटल पूर्णांक rtl_get_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	स्थिर काष्ठा rtl_coalesce_info *ci;
	u32 scale, c_us, c_fr;
	u16 पूर्णांकrmit;

	अगर (rtl_is_8125(tp))
		वापस -EOPNOTSUPP;

	स_रखो(ec, 0, माप(*ec));

	/* get rx/tx scale corresponding to current speed and CPlusCmd[0:1] */
	ci = rtl_coalesce_info(tp);
	अगर (IS_ERR(ci))
		वापस PTR_ERR(ci);

	scale = ci->scale_nsecs[tp->cp_cmd & INTT_MASK];

	पूर्णांकrmit = RTL_R16(tp, IntrMitigate);

	c_us = FIELD_GET(RTL_COALESCE_TX_USECS, पूर्णांकrmit);
	ec->tx_coalesce_usecs = DIV_ROUND_UP(c_us * scale, 1000);

	c_fr = FIELD_GET(RTL_COALESCE_TX_FRAMES, पूर्णांकrmit);
	/* ethtool_coalesce states usecs and max_frames must not both be 0 */
	ec->tx_max_coalesced_frames = (c_us || c_fr) ? c_fr * 4 : 1;

	c_us = FIELD_GET(RTL_COALESCE_RX_USECS, पूर्णांकrmit);
	ec->rx_coalesce_usecs = DIV_ROUND_UP(c_us * scale, 1000);

	c_fr = FIELD_GET(RTL_COALESCE_RX_FRAMES, पूर्णांकrmit);
	ec->rx_max_coalesced_frames = (c_us || c_fr) ? c_fr * 4 : 1;

	वापस 0;
पूर्ण

/* choose appropriate scale factor and CPlusCmd[0:1] क्रम (speed, usec) */
अटल पूर्णांक rtl_coalesce_choose_scale(काष्ठा rtl8169_निजी *tp, u32 usec,
				     u16 *cp01)
अणु
	स्थिर काष्ठा rtl_coalesce_info *ci;
	u16 i;

	ci = rtl_coalesce_info(tp);
	अगर (IS_ERR(ci))
		वापस PTR_ERR(ci);

	क्रम (i = 0; i < 4; i++) अणु
		अगर (usec <= ci->scale_nsecs[i] * RTL_COALESCE_T_MAX / 1000U) अणु
			*cp01 = i;
			वापस ci->scale_nsecs[i];
		पूर्ण
	पूर्ण

	वापस -दुस्फल;
पूर्ण

अटल पूर्णांक rtl_set_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	u32 tx_fr = ec->tx_max_coalesced_frames;
	u32 rx_fr = ec->rx_max_coalesced_frames;
	u32 coal_usec_max, units;
	u16 w = 0, cp01 = 0;
	पूर्णांक scale;

	अगर (rtl_is_8125(tp))
		वापस -EOPNOTSUPP;

	अगर (rx_fr > RTL_COALESCE_FRAME_MAX || tx_fr > RTL_COALESCE_FRAME_MAX)
		वापस -दुस्फल;

	coal_usec_max = max(ec->rx_coalesce_usecs, ec->tx_coalesce_usecs);
	scale = rtl_coalesce_choose_scale(tp, coal_usec_max, &cp01);
	अगर (scale < 0)
		वापस scale;

	/* Accept max_frames=1 we वापसed in rtl_get_coalesce. Accept it
	 * not only when usecs=0 because of e.g. the following scenario:
	 *
	 * - both rx_usecs=0 & rx_frames=0 in hardware (no delay on RX)
	 * - rtl_get_coalesce वापसs rx_usecs=0, rx_frames=1
	 * - then user करोes `ethtool -C eth0 rx-usecs 100`
	 *
	 * Since ethtool sends to kernel whole ethtool_coalesce settings,
	 * अगर we want to ignore rx_frames then it has to be set to 0.
	 */
	अगर (rx_fr == 1)
		rx_fr = 0;
	अगर (tx_fr == 1)
		tx_fr = 0;

	/* HW requires समय limit to be set अगर frame limit is set */
	अगर ((tx_fr && !ec->tx_coalesce_usecs) ||
	    (rx_fr && !ec->rx_coalesce_usecs))
		वापस -EINVAL;

	w |= FIELD_PREP(RTL_COALESCE_TX_FRAMES, DIV_ROUND_UP(tx_fr, 4));
	w |= FIELD_PREP(RTL_COALESCE_RX_FRAMES, DIV_ROUND_UP(rx_fr, 4));

	units = DIV_ROUND_UP(ec->tx_coalesce_usecs * 1000U, scale);
	w |= FIELD_PREP(RTL_COALESCE_TX_USECS, units);
	units = DIV_ROUND_UP(ec->rx_coalesce_usecs * 1000U, scale);
	w |= FIELD_PREP(RTL_COALESCE_RX_USECS, units);

	RTL_W16(tp, IntrMitigate, w);

	/* Meaning of PktCntrDisable bit changed from RTL8168e-vl */
	अगर (rtl_is_8168evl_up(tp)) अणु
		अगर (!rx_fr && !tx_fr)
			/* disable packet counter */
			tp->cp_cmd |= PktCntrDisable;
		अन्यथा
			tp->cp_cmd &= ~PktCntrDisable;
	पूर्ण

	tp->cp_cmd = (tp->cp_cmd & ~INTT_MASK) | cp01;
	RTL_W16(tp, CPlusCmd, tp->cp_cmd);
	rtl_pci_commit(tp);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8169_get_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *data)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);

	अगर (!rtl_supports_eee(tp))
		वापस -EOPNOTSUPP;

	वापस phy_ethtool_get_eee(tp->phydev, data);
पूर्ण

अटल पूर्णांक rtl8169_set_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *data)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	पूर्णांक ret;

	अगर (!rtl_supports_eee(tp))
		वापस -EOPNOTSUPP;

	ret = phy_ethtool_set_eee(tp->phydev, data);

	अगर (!ret)
		tp->eee_adv = phy_पढ़ो_mmd(dev->phydev, MDIO_MMD_AN,
					   MDIO_AN_EEE_ADV);
	वापस ret;
पूर्ण

अटल व्योम rtl8169_get_ringparam(काष्ठा net_device *dev,
				  काष्ठा ethtool_ringparam *data)
अणु
	data->rx_max_pending = NUM_RX_DESC;
	data->rx_pending = NUM_RX_DESC;
	data->tx_max_pending = NUM_TX_DESC;
	data->tx_pending = NUM_TX_DESC;
पूर्ण

अटल व्योम rtl8169_get_छोड़ोparam(काष्ठा net_device *dev,
				   काष्ठा ethtool_छोड़ोparam *data)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	bool tx_छोड़ो, rx_छोड़ो;

	phy_get_छोड़ो(tp->phydev, &tx_छोड़ो, &rx_छोड़ो);

	data->स्वतःneg = tp->phydev->स्वतःneg;
	data->tx_छोड़ो = tx_छोड़ो ? 1 : 0;
	data->rx_छोड़ो = rx_छोड़ो ? 1 : 0;
पूर्ण

अटल पूर्णांक rtl8169_set_छोड़ोparam(काष्ठा net_device *dev,
				  काष्ठा ethtool_छोड़ोparam *data)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);

	अगर (dev->mtu > ETH_DATA_LEN)
		वापस -EOPNOTSUPP;

	phy_set_asym_छोड़ो(tp->phydev, data->rx_छोड़ो, data->tx_छोड़ो);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops rtl8169_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo		= rtl8169_get_drvinfo,
	.get_regs_len		= rtl8169_get_regs_len,
	.get_link		= ethtool_op_get_link,
	.get_coalesce		= rtl_get_coalesce,
	.set_coalesce		= rtl_set_coalesce,
	.get_regs		= rtl8169_get_regs,
	.get_wol		= rtl8169_get_wol,
	.set_wol		= rtl8169_set_wol,
	.get_strings		= rtl8169_get_strings,
	.get_sset_count		= rtl8169_get_sset_count,
	.get_ethtool_stats	= rtl8169_get_ethtool_stats,
	.get_ts_info		= ethtool_op_get_ts_info,
	.nway_reset		= phy_ethtool_nway_reset,
	.get_eee		= rtl8169_get_eee,
	.set_eee		= rtl8169_set_eee,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
	.get_ringparam		= rtl8169_get_ringparam,
	.get_छोड़ोparam		= rtl8169_get_छोड़ोparam,
	.set_छोड़ोparam		= rtl8169_set_छोड़ोparam,
पूर्ण;

अटल व्योम rtl_enable_eee(काष्ठा rtl8169_निजी *tp)
अणु
	काष्ठा phy_device *phydev = tp->phydev;
	पूर्णांक adv;

	/* respect EEE advertisement the user may have set */
	अगर (tp->eee_adv >= 0)
		adv = tp->eee_adv;
	अन्यथा
		adv = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MDIO_PCS_EEE_ABLE);

	अगर (adv >= 0)
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV, adv);
पूर्ण

अटल क्रमागत mac_version rtl8169_get_mac_version(u16 xid, bool gmii)
अणु
	/*
	 * The driver currently handles the 8168Bf and the 8168Be identically
	 * but they can be identअगरied more specअगरically through the test below
	 * अगर needed:
	 *
	 * (RTL_R32(tp, TxConfig) & 0x700000) == 0x500000 ? 8168Bf : 8168Be
	 *
	 * Same thing क्रम the 8101Eb and the 8101Ec:
	 *
	 * (RTL_R32(tp, TxConfig) & 0x700000) == 0x200000 ? 8101Eb : 8101Ec
	 */
	अटल स्थिर काष्ठा rtl_mac_info अणु
		u16 mask;
		u16 val;
		क्रमागत mac_version ver;
	पूर्ण mac_info[] = अणु
		/* 8125B family. */
		अणु 0x7cf, 0x641,	RTL_GIGA_MAC_VER_63 पूर्ण,

		/* 8125A family. */
		अणु 0x7cf, 0x608,	RTL_GIGA_MAC_VER_60 पूर्ण,
		अणु 0x7c8, 0x608,	RTL_GIGA_MAC_VER_61 पूर्ण,

		/* RTL8117 */
		अणु 0x7cf, 0x54b,	RTL_GIGA_MAC_VER_53 पूर्ण,
		अणु 0x7cf, 0x54a,	RTL_GIGA_MAC_VER_52 पूर्ण,

		/* 8168EP family. */
		अणु 0x7cf, 0x502,	RTL_GIGA_MAC_VER_51 पूर्ण,
		अणु 0x7cf, 0x501,	RTL_GIGA_MAC_VER_50 पूर्ण,
		अणु 0x7cf, 0x500,	RTL_GIGA_MAC_VER_49 पूर्ण,

		/* 8168H family. */
		अणु 0x7cf, 0x541,	RTL_GIGA_MAC_VER_46 पूर्ण,
		अणु 0x7cf, 0x540,	RTL_GIGA_MAC_VER_45 पूर्ण,

		/* 8168G family. */
		अणु 0x7cf, 0x5c8,	RTL_GIGA_MAC_VER_44 पूर्ण,
		अणु 0x7cf, 0x509,	RTL_GIGA_MAC_VER_42 पूर्ण,
		अणु 0x7cf, 0x4c1,	RTL_GIGA_MAC_VER_41 पूर्ण,
		अणु 0x7cf, 0x4c0,	RTL_GIGA_MAC_VER_40 पूर्ण,

		/* 8168F family. */
		अणु 0x7c8, 0x488,	RTL_GIGA_MAC_VER_38 पूर्ण,
		अणु 0x7cf, 0x481,	RTL_GIGA_MAC_VER_36 पूर्ण,
		अणु 0x7cf, 0x480,	RTL_GIGA_MAC_VER_35 पूर्ण,

		/* 8168E family. */
		अणु 0x7c8, 0x2c8,	RTL_GIGA_MAC_VER_34 पूर्ण,
		अणु 0x7cf, 0x2c1,	RTL_GIGA_MAC_VER_32 पूर्ण,
		अणु 0x7c8, 0x2c0,	RTL_GIGA_MAC_VER_33 पूर्ण,

		/* 8168D family. */
		अणु 0x7cf, 0x281,	RTL_GIGA_MAC_VER_25 पूर्ण,
		अणु 0x7c8, 0x280,	RTL_GIGA_MAC_VER_26 पूर्ण,

		/* 8168DP family. */
		/* It seems this early RTL8168dp version never made it to
		 * the wild. Let's see whether somebody complains, अगर not
		 * we'll हटाओ support क्रम this chip version completely.
		 * अणु 0x7cf, 0x288,      RTL_GIGA_MAC_VER_27 पूर्ण,
		 */
		अणु 0x7cf, 0x28a,	RTL_GIGA_MAC_VER_28 पूर्ण,
		अणु 0x7cf, 0x28b,	RTL_GIGA_MAC_VER_31 पूर्ण,

		/* 8168C family. */
		अणु 0x7cf, 0x3c9,	RTL_GIGA_MAC_VER_23 पूर्ण,
		अणु 0x7cf, 0x3c8,	RTL_GIGA_MAC_VER_18 पूर्ण,
		अणु 0x7c8, 0x3c8,	RTL_GIGA_MAC_VER_24 पूर्ण,
		अणु 0x7cf, 0x3c0,	RTL_GIGA_MAC_VER_19 पूर्ण,
		अणु 0x7cf, 0x3c2,	RTL_GIGA_MAC_VER_20 पूर्ण,
		अणु 0x7cf, 0x3c3,	RTL_GIGA_MAC_VER_21 पूर्ण,
		अणु 0x7c8, 0x3c0,	RTL_GIGA_MAC_VER_22 पूर्ण,

		/* 8168B family. */
		अणु 0x7cf, 0x380,	RTL_GIGA_MAC_VER_12 पूर्ण,
		अणु 0x7c8, 0x380,	RTL_GIGA_MAC_VER_17 पूर्ण,
		अणु 0x7c8, 0x300,	RTL_GIGA_MAC_VER_11 पूर्ण,

		/* 8101 family. */
		अणु 0x7c8, 0x448,	RTL_GIGA_MAC_VER_39 पूर्ण,
		अणु 0x7c8, 0x440,	RTL_GIGA_MAC_VER_37 पूर्ण,
		अणु 0x7cf, 0x409,	RTL_GIGA_MAC_VER_29 पूर्ण,
		अणु 0x7c8, 0x408,	RTL_GIGA_MAC_VER_30 पूर्ण,
		अणु 0x7cf, 0x349,	RTL_GIGA_MAC_VER_08 पूर्ण,
		अणु 0x7cf, 0x249,	RTL_GIGA_MAC_VER_08 पूर्ण,
		अणु 0x7cf, 0x348,	RTL_GIGA_MAC_VER_07 पूर्ण,
		अणु 0x7cf, 0x248,	RTL_GIGA_MAC_VER_07 पूर्ण,
		अणु 0x7cf, 0x340,	RTL_GIGA_MAC_VER_13 पूर्ण,
		अणु 0x7cf, 0x240,	RTL_GIGA_MAC_VER_14 पूर्ण,
		अणु 0x7cf, 0x343,	RTL_GIGA_MAC_VER_10 पूर्ण,
		अणु 0x7cf, 0x342,	RTL_GIGA_MAC_VER_16 पूर्ण,
		अणु 0x7c8, 0x348,	RTL_GIGA_MAC_VER_09 पूर्ण,
		अणु 0x7c8, 0x248,	RTL_GIGA_MAC_VER_09 पूर्ण,
		अणु 0x7c8, 0x340,	RTL_GIGA_MAC_VER_16 पूर्ण,
		/* FIXME: where did these entries come from ? -- FR
		 * Not even r8101 venकरोr driver knows these id's,
		 * so let's disable detection क्रम now. -- HK
		 * अणु 0xfc8, 0x388,	RTL_GIGA_MAC_VER_13 पूर्ण,
		 * अणु 0xfc8, 0x308,	RTL_GIGA_MAC_VER_13 पूर्ण,
		 */

		/* 8110 family. */
		अणु 0xfc8, 0x980,	RTL_GIGA_MAC_VER_06 पूर्ण,
		अणु 0xfc8, 0x180,	RTL_GIGA_MAC_VER_05 पूर्ण,
		अणु 0xfc8, 0x100,	RTL_GIGA_MAC_VER_04 पूर्ण,
		अणु 0xfc8, 0x040,	RTL_GIGA_MAC_VER_03 पूर्ण,
		अणु 0xfc8, 0x008,	RTL_GIGA_MAC_VER_02 पूर्ण,

		/* Catch-all */
		अणु 0x000, 0x000,	RTL_GIGA_MAC_NONE   पूर्ण
	पूर्ण;
	स्थिर काष्ठा rtl_mac_info *p = mac_info;
	क्रमागत mac_version ver;

	जबतक ((xid & p->mask) != p->val)
		p++;
	ver = p->ver;

	अगर (ver != RTL_GIGA_MAC_NONE && !gmii) अणु
		अगर (ver == RTL_GIGA_MAC_VER_42)
			ver = RTL_GIGA_MAC_VER_43;
		अन्यथा अगर (ver == RTL_GIGA_MAC_VER_45)
			ver = RTL_GIGA_MAC_VER_47;
		अन्यथा अगर (ver == RTL_GIGA_MAC_VER_46)
			ver = RTL_GIGA_MAC_VER_48;
	पूर्ण

	वापस ver;
पूर्ण

अटल व्योम rtl_release_firmware(काष्ठा rtl8169_निजी *tp)
अणु
	अगर (tp->rtl_fw) अणु
		rtl_fw_release_firmware(tp->rtl_fw);
		kमुक्त(tp->rtl_fw);
		tp->rtl_fw = शून्य;
	पूर्ण
पूर्ण

व्योम r8169_apply_firmware(काष्ठा rtl8169_निजी *tp)
अणु
	पूर्णांक val;

	/* TODO: release firmware अगर rtl_fw_ग_लिखो_firmware संकेतs failure. */
	अगर (tp->rtl_fw) अणु
		rtl_fw_ग_लिखो_firmware(tp, tp->rtl_fw);
		/* At least one firmware करोesn't reset tp->ocp_base. */
		tp->ocp_base = OCP_STD_PHY_BASE;

		/* PHY soft reset may still be in progress */
		phy_पढ़ो_poll_समयout(tp->phydev, MII_BMCR, val,
				      !(val & BMCR_RESET),
				      50000, 600000, true);
	पूर्ण
पूर्ण

अटल व्योम rtl8168_config_eee_mac(काष्ठा rtl8169_निजी *tp)
अणु
	/* Adjust EEE LED frequency */
	अगर (tp->mac_version != RTL_GIGA_MAC_VER_38)
		RTL_W8(tp, EEE_LED, RTL_R8(tp, EEE_LED) & ~0x07);

	rtl_eri_set_bits(tp, 0x1b0, 0x0003);
पूर्ण

अटल व्योम rtl8125a_config_eee_mac(काष्ठा rtl8169_निजी *tp)
अणु
	r8168_mac_ocp_modअगरy(tp, 0xe040, 0, BIT(1) | BIT(0));
	r8168_mac_ocp_modअगरy(tp, 0xeb62, 0, BIT(2) | BIT(1));
पूर्ण

अटल व्योम rtl8125_set_eee_txidle_समयr(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W16(tp, EEE_TXIDLE_TIMER_8125, tp->dev->mtu + ETH_HLEN + 0x20);
पूर्ण

अटल व्योम rtl8125b_config_eee_mac(काष्ठा rtl8169_निजी *tp)
अणु
	rtl8125_set_eee_txidle_समयr(tp);
	r8168_mac_ocp_modअगरy(tp, 0xe040, 0, BIT(1) | BIT(0));
पूर्ण

अटल व्योम rtl_rar_exgmac_set(काष्ठा rtl8169_निजी *tp, स्थिर u8 *addr)
अणु
	rtl_eri_ग_लिखो(tp, 0xe0, ERIAR_MASK_1111, get_unaligned_le32(addr));
	rtl_eri_ग_लिखो(tp, 0xe4, ERIAR_MASK_1111, get_unaligned_le16(addr + 4));
	rtl_eri_ग_लिखो(tp, 0xf0, ERIAR_MASK_1111, get_unaligned_le16(addr) << 16);
	rtl_eri_ग_लिखो(tp, 0xf4, ERIAR_MASK_1111, get_unaligned_le32(addr + 2));
पूर्ण

u16 rtl8168h_2_get_adc_bias_ioffset(काष्ठा rtl8169_निजी *tp)
अणु
	u16 data1, data2, ioffset;

	r8168_mac_ocp_ग_लिखो(tp, 0xdd02, 0x807d);
	data1 = r8168_mac_ocp_पढ़ो(tp, 0xdd02);
	data2 = r8168_mac_ocp_पढ़ो(tp, 0xdd00);

	ioffset = (data2 >> 1) & 0x7ff8;
	ioffset |= data2 & 0x0007;
	अगर (data1 & BIT(7))
		ioffset |= BIT(15);

	वापस ioffset;
पूर्ण

अटल व्योम rtl_schedule_task(काष्ठा rtl8169_निजी *tp, क्रमागत rtl_flag flag)
अणु
	set_bit(flag, tp->wk.flags);
	schedule_work(&tp->wk.work);
पूर्ण

अटल व्योम rtl8169_init_phy(काष्ठा rtl8169_निजी *tp)
अणु
	r8169_hw_phy_config(tp, tp->phydev, tp->mac_version);

	अगर (tp->mac_version <= RTL_GIGA_MAC_VER_06) अणु
		pci_ग_लिखो_config_byte(tp->pci_dev, PCI_LATENCY_TIMER, 0x40);
		pci_ग_लिखो_config_byte(tp->pci_dev, PCI_CACHE_LINE_SIZE, 0x08);
		/* set unकरोcumented MAC Reg C+CR Offset 0x82h */
		RTL_W8(tp, 0x82, 0x01);
	पूर्ण

	अगर (tp->mac_version == RTL_GIGA_MAC_VER_05 &&
	    tp->pci_dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_GIGABYTE &&
	    tp->pci_dev->subप्रणाली_device == 0xe000)
		phy_ग_लिखो_paged(tp->phydev, 0x0001, 0x10, 0xf01b);

	/* We may have called phy_speed_करोwn beक्रमe */
	phy_speed_up(tp->phydev);

	अगर (rtl_supports_eee(tp))
		rtl_enable_eee(tp);

	genphy_soft_reset(tp->phydev);
पूर्ण

अटल व्योम rtl_rar_set(काष्ठा rtl8169_निजी *tp, स्थिर u8 *addr)
अणु
	rtl_unlock_config_regs(tp);

	RTL_W32(tp, MAC4, get_unaligned_le16(addr + 4));
	rtl_pci_commit(tp);

	RTL_W32(tp, MAC0, get_unaligned_le32(addr));
	rtl_pci_commit(tp);

	अगर (tp->mac_version == RTL_GIGA_MAC_VER_34)
		rtl_rar_exgmac_set(tp, addr);

	rtl_lock_config_regs(tp);
पूर्ण

अटल पूर्णांक rtl_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	पूर्णांक ret;

	ret = eth_mac_addr(dev, p);
	अगर (ret)
		वापस ret;

	rtl_rar_set(tp, dev->dev_addr);

	वापस 0;
पूर्ण

अटल व्योम rtl_wol_enable_rx(काष्ठा rtl8169_निजी *tp)
अणु
	अगर (tp->mac_version >= RTL_GIGA_MAC_VER_25)
		RTL_W32(tp, RxConfig, RTL_R32(tp, RxConfig) |
			AcceptBroadcast | AcceptMulticast | AcceptMyPhys);
पूर्ण

अटल व्योम rtl_prepare_घातer_करोwn(काष्ठा rtl8169_निजी *tp)
अणु
	अगर (tp->dash_type != RTL_DASH_NONE)
		वापस;

	अगर (tp->mac_version == RTL_GIGA_MAC_VER_32 ||
	    tp->mac_version == RTL_GIGA_MAC_VER_33)
		rtl_ephy_ग_लिखो(tp, 0x19, 0xff64);

	अगर (device_may_wakeup(tp_to_dev(tp))) अणु
		phy_speed_करोwn(tp->phydev, false);
		rtl_wol_enable_rx(tp);
	पूर्ण
पूर्ण

अटल व्योम rtl_init_rxcfg(काष्ठा rtl8169_निजी *tp)
अणु
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_02 ... RTL_GIGA_MAC_VER_06:
	हाल RTL_GIGA_MAC_VER_10 ... RTL_GIGA_MAC_VER_17:
		RTL_W32(tp, RxConfig, RX_FIFO_THRESH | RX_DMA_BURST);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_18 ... RTL_GIGA_MAC_VER_24:
	हाल RTL_GIGA_MAC_VER_34 ... RTL_GIGA_MAC_VER_36:
	हाल RTL_GIGA_MAC_VER_38:
		RTL_W32(tp, RxConfig, RX128_INT_EN | RX_MULTI_EN | RX_DMA_BURST);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_40 ... RTL_GIGA_MAC_VER_53:
		RTL_W32(tp, RxConfig, RX128_INT_EN | RX_MULTI_EN | RX_DMA_BURST | RX_EARLY_OFF);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_60 ... RTL_GIGA_MAC_VER_63:
		RTL_W32(tp, RxConfig, RX_FETCH_DFLT_8125 | RX_DMA_BURST);
		अवरोध;
	शेष:
		RTL_W32(tp, RxConfig, RX128_INT_EN | RX_DMA_BURST);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtl8169_init_ring_indexes(काष्ठा rtl8169_निजी *tp)
अणु
	tp->dirty_tx = tp->cur_tx = tp->cur_rx = 0;
पूर्ण

अटल व्योम r8168c_hw_jumbo_enable(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) | Jumbo_En0);
	RTL_W8(tp, Config4, RTL_R8(tp, Config4) | Jumbo_En1);
पूर्ण

अटल व्योम r8168c_hw_jumbo_disable(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Jumbo_En0);
	RTL_W8(tp, Config4, RTL_R8(tp, Config4) & ~Jumbo_En1);
पूर्ण

अटल व्योम r8168dp_hw_jumbo_enable(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) | Jumbo_En0);
पूर्ण

अटल व्योम r8168dp_hw_jumbo_disable(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Jumbo_En0);
पूर्ण

अटल व्योम r8168e_hw_jumbo_enable(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, MaxTxPacketSize, 0x24);
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) | Jumbo_En0);
	RTL_W8(tp, Config4, RTL_R8(tp, Config4) | 0x01);
पूर्ण

अटल व्योम r8168e_hw_jumbo_disable(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, MaxTxPacketSize, 0x3f);
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Jumbo_En0);
	RTL_W8(tp, Config4, RTL_R8(tp, Config4) & ~0x01);
पूर्ण

अटल व्योम r8168b_1_hw_jumbo_enable(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, Config4, RTL_R8(tp, Config4) | (1 << 0));
पूर्ण

अटल व्योम r8168b_1_hw_jumbo_disable(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, Config4, RTL_R8(tp, Config4) & ~(1 << 0));
पूर्ण

अटल व्योम rtl_jumbo_config(काष्ठा rtl8169_निजी *tp)
अणु
	bool jumbo = tp->dev->mtu > ETH_DATA_LEN;
	पूर्णांक पढ़ोrq = 4096;

	rtl_unlock_config_regs(tp);
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_12:
	हाल RTL_GIGA_MAC_VER_17:
		अगर (jumbo) अणु
			पढ़ोrq = 512;
			r8168b_1_hw_jumbo_enable(tp);
		पूर्ण अन्यथा अणु
			r8168b_1_hw_jumbo_disable(tp);
		पूर्ण
		अवरोध;
	हाल RTL_GIGA_MAC_VER_18 ... RTL_GIGA_MAC_VER_26:
		अगर (jumbo) अणु
			पढ़ोrq = 512;
			r8168c_hw_jumbo_enable(tp);
		पूर्ण अन्यथा अणु
			r8168c_hw_jumbo_disable(tp);
		पूर्ण
		अवरोध;
	हाल RTL_GIGA_MAC_VER_27 ... RTL_GIGA_MAC_VER_28:
		अगर (jumbo)
			r8168dp_hw_jumbo_enable(tp);
		अन्यथा
			r8168dp_hw_jumbo_disable(tp);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_31 ... RTL_GIGA_MAC_VER_33:
		अगर (jumbo)
			r8168e_hw_jumbo_enable(tp);
		अन्यथा
			r8168e_hw_jumbo_disable(tp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rtl_lock_config_regs(tp);

	अगर (pci_is_pcie(tp->pci_dev) && tp->supports_gmii)
		pcie_set_पढ़ोrq(tp->pci_dev, पढ़ोrq);

	/* Chip करोesn't support छोड़ो in jumbo mode */
	अगर (jumbo) अणु
		linkmode_clear_bit(ETHTOOL_LINK_MODE_Pause_BIT,
				   tp->phydev->advertising);
		linkmode_clear_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
				   tp->phydev->advertising);
		phy_start_aneg(tp->phydev);
	पूर्ण
पूर्ण

DECLARE_RTL_COND(rtl_chipcmd_cond)
अणु
	वापस RTL_R8(tp, ChipCmd) & CmdReset;
पूर्ण

अटल व्योम rtl_hw_reset(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, ChipCmd, CmdReset);

	rtl_loop_रुको_low(tp, &rtl_chipcmd_cond, 100, 100);
पूर्ण

अटल व्योम rtl_request_firmware(काष्ठा rtl8169_निजी *tp)
अणु
	काष्ठा rtl_fw *rtl_fw;

	/* firmware loaded alपढ़ोy or no firmware available */
	अगर (tp->rtl_fw || !tp->fw_name)
		वापस;

	rtl_fw = kzalloc(माप(*rtl_fw), GFP_KERNEL);
	अगर (!rtl_fw)
		वापस;

	rtl_fw->phy_ग_लिखो = rtl_ग_लिखोphy;
	rtl_fw->phy_पढ़ो = rtl_पढ़ोphy;
	rtl_fw->mac_mcu_ग_लिखो = mac_mcu_ग_लिखो;
	rtl_fw->mac_mcu_पढ़ो = mac_mcu_पढ़ो;
	rtl_fw->fw_name = tp->fw_name;
	rtl_fw->dev = tp_to_dev(tp);

	अगर (rtl_fw_request_firmware(rtl_fw))
		kमुक्त(rtl_fw);
	अन्यथा
		tp->rtl_fw = rtl_fw;
पूर्ण

अटल व्योम rtl_rx_बंद(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W32(tp, RxConfig, RTL_R32(tp, RxConfig) & ~RX_CONFIG_ACCEPT_MASK);
पूर्ण

DECLARE_RTL_COND(rtl_npq_cond)
अणु
	वापस RTL_R8(tp, TxPoll) & NPQ;
पूर्ण

DECLARE_RTL_COND(rtl_txcfg_empty_cond)
अणु
	वापस RTL_R32(tp, TxConfig) & TXCFG_EMPTY;
पूर्ण

DECLARE_RTL_COND(rtl_rxtx_empty_cond)
अणु
	वापस (RTL_R8(tp, MCU) & RXTX_EMPTY) == RXTX_EMPTY;
पूर्ण

DECLARE_RTL_COND(rtl_rxtx_empty_cond_2)
अणु
	/* IntrMitigate has new functionality on RTL8125 */
	वापस (RTL_R16(tp, IntrMitigate) & 0x0103) == 0x0103;
पूर्ण

अटल व्योम rtl_रुको_txrx_fअगरo_empty(काष्ठा rtl8169_निजी *tp)
अणु
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_40 ... RTL_GIGA_MAC_VER_53:
		rtl_loop_रुको_high(tp, &rtl_txcfg_empty_cond, 100, 42);
		rtl_loop_रुको_high(tp, &rtl_rxtx_empty_cond, 100, 42);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_60 ... RTL_GIGA_MAC_VER_61:
		rtl_loop_रुको_high(tp, &rtl_rxtx_empty_cond, 100, 42);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_63:
		RTL_W8(tp, ChipCmd, RTL_R8(tp, ChipCmd) | StopReq);
		rtl_loop_रुको_high(tp, &rtl_rxtx_empty_cond, 100, 42);
		rtl_loop_रुको_high(tp, &rtl_rxtx_empty_cond_2, 100, 42);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtl_enable_rxdvgate(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W32(tp, MISC, RTL_R32(tp, MISC) | RXDV_GATED_EN);
	fsleep(2000);
	rtl_रुको_txrx_fअगरo_empty(tp);
पूर्ण

अटल व्योम rtl_set_tx_config_रेजिस्टरs(काष्ठा rtl8169_निजी *tp)
अणु
	u32 val = TX_DMA_BURST << TxDMAShअगरt |
		  InterFrameGap << TxInterFrameGapShअगरt;

	अगर (rtl_is_8168evl_up(tp))
		val |= TXCFG_AUTO_FIFO;

	RTL_W32(tp, TxConfig, val);
पूर्ण

अटल व्योम rtl_set_rx_max_size(काष्ठा rtl8169_निजी *tp)
अणु
	/* Low hurts. Let's disable the filtering. */
	RTL_W16(tp, RxMaxSize, R8169_RX_BUF_SIZE + 1);
पूर्ण

अटल व्योम rtl_set_rx_tx_desc_रेजिस्टरs(काष्ठा rtl8169_निजी *tp)
अणु
	/*
	 * Magic spell: some iop3xx ARM board needs the TxDescAddrHigh
	 * रेजिस्टर to be written beक्रमe TxDescAddrLow to work.
	 * Switching from MMIO to I/O access fixes the issue as well.
	 */
	RTL_W32(tp, TxDescStartAddrHigh, ((u64) tp->TxPhyAddr) >> 32);
	RTL_W32(tp, TxDescStartAddrLow, ((u64) tp->TxPhyAddr) & DMA_BIT_MASK(32));
	RTL_W32(tp, RxDescAddrHigh, ((u64) tp->RxPhyAddr) >> 32);
	RTL_W32(tp, RxDescAddrLow, ((u64) tp->RxPhyAddr) & DMA_BIT_MASK(32));
पूर्ण

अटल व्योम rtl8169_set_magic_reg(काष्ठा rtl8169_निजी *tp)
अणु
	u32 val;

	अगर (tp->mac_version == RTL_GIGA_MAC_VER_05)
		val = 0x000fff00;
	अन्यथा अगर (tp->mac_version == RTL_GIGA_MAC_VER_06)
		val = 0x00ffff00;
	अन्यथा
		वापस;

	अगर (RTL_R8(tp, Config2) & PCI_Clock_66MHz)
		val |= 0xff;

	RTL_W32(tp, 0x7c, val);
पूर्ण

अटल व्योम rtl_set_rx_mode(काष्ठा net_device *dev)
अणु
	u32 rx_mode = AcceptBroadcast | AcceptMyPhys | AcceptMulticast;
	/* Multicast hash filter */
	u32 mc_filter[2] = अणु 0xffffffff, 0xffffffff पूर्ण;
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	u32 पंचांगp;

	अगर (dev->flags & IFF_PROMISC) अणु
		rx_mode |= AcceptAllPhys;
	पूर्ण अन्यथा अगर (netdev_mc_count(dev) > MC_FILTER_LIMIT ||
		   dev->flags & IFF_ALLMULTI ||
		   tp->mac_version == RTL_GIGA_MAC_VER_35) अणु
		/* accept all multicasts */
	पूर्ण अन्यथा अगर (netdev_mc_empty(dev)) अणु
		rx_mode &= ~AcceptMulticast;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;

		mc_filter[1] = mc_filter[0] = 0;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			u32 bit_nr = eth_hw_addr_crc(ha) >> 26;
			mc_filter[bit_nr >> 5] |= BIT(bit_nr & 31);
		पूर्ण

		अगर (tp->mac_version > RTL_GIGA_MAC_VER_06) अणु
			पंचांगp = mc_filter[0];
			mc_filter[0] = swab32(mc_filter[1]);
			mc_filter[1] = swab32(पंचांगp);
		पूर्ण
	पूर्ण

	RTL_W32(tp, MAR0 + 4, mc_filter[1]);
	RTL_W32(tp, MAR0 + 0, mc_filter[0]);

	पंचांगp = RTL_R32(tp, RxConfig);
	RTL_W32(tp, RxConfig, (पंचांगp & ~RX_CONFIG_ACCEPT_OK_MASK) | rx_mode);
पूर्ण

DECLARE_RTL_COND(rtl_csiar_cond)
अणु
	वापस RTL_R32(tp, CSIAR) & CSIAR_FLAG;
पूर्ण

अटल व्योम rtl_csi_ग_लिखो(काष्ठा rtl8169_निजी *tp, पूर्णांक addr, पूर्णांक value)
अणु
	u32 func = PCI_FUNC(tp->pci_dev->devfn);

	RTL_W32(tp, CSIDR, value);
	RTL_W32(tp, CSIAR, CSIAR_WRITE_CMD | (addr & CSIAR_ADDR_MASK) |
		CSIAR_BYTE_ENABLE | func << 16);

	rtl_loop_रुको_low(tp, &rtl_csiar_cond, 10, 100);
पूर्ण

अटल u32 rtl_csi_पढ़ो(काष्ठा rtl8169_निजी *tp, पूर्णांक addr)
अणु
	u32 func = PCI_FUNC(tp->pci_dev->devfn);

	RTL_W32(tp, CSIAR, (addr & CSIAR_ADDR_MASK) | func << 16 |
		CSIAR_BYTE_ENABLE);

	वापस rtl_loop_रुको_high(tp, &rtl_csiar_cond, 10, 100) ?
		RTL_R32(tp, CSIDR) : ~0;
पूर्ण

अटल व्योम rtl_csi_access_enable(काष्ठा rtl8169_निजी *tp, u8 val)
अणु
	काष्ठा pci_dev *pdev = tp->pci_dev;
	u32 csi;

	/* According to Realtek the value at config space address 0x070f
	 * controls the L0s/L1 entrance latency. We try standard ECAM access
	 * first and अगर it fails fall back to CSI.
	 */
	अगर (pdev->cfg_size > 0x070f &&
	    pci_ग_लिखो_config_byte(pdev, 0x070f, val) == PCIBIOS_SUCCESSFUL)
		वापस;

	netdev_notice_once(tp->dev,
		"No native access to PCI extended config space, falling back to CSI\n");
	csi = rtl_csi_पढ़ो(tp, 0x070c) & 0x00ffffff;
	rtl_csi_ग_लिखो(tp, 0x070c, csi | val << 24);
पूर्ण

अटल व्योम rtl_set_def_aspm_entry_latency(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_csi_access_enable(tp, 0x27);
पूर्ण

काष्ठा ephy_info अणु
	अचिन्हित पूर्णांक offset;
	u16 mask;
	u16 bits;
पूर्ण;

अटल व्योम __rtl_ephy_init(काष्ठा rtl8169_निजी *tp,
			    स्थिर काष्ठा ephy_info *e, पूर्णांक len)
अणु
	u16 w;

	जबतक (len-- > 0) अणु
		w = (rtl_ephy_पढ़ो(tp, e->offset) & ~e->mask) | e->bits;
		rtl_ephy_ग_लिखो(tp, e->offset, w);
		e++;
	पूर्ण
पूर्ण

#घोषणा rtl_ephy_init(tp, a) __rtl_ephy_init(tp, a, ARRAY_SIZE(a))

अटल व्योम rtl_disable_घड़ी_request(काष्ठा rtl8169_निजी *tp)
अणु
	pcie_capability_clear_word(tp->pci_dev, PCI_EXP_LNKCTL,
				   PCI_EXP_LNKCTL_CLKREQ_EN);
पूर्ण

अटल व्योम rtl_enable_घड़ी_request(काष्ठा rtl8169_निजी *tp)
अणु
	pcie_capability_set_word(tp->pci_dev, PCI_EXP_LNKCTL,
				 PCI_EXP_LNKCTL_CLKREQ_EN);
पूर्ण

अटल व्योम rtl_pcie_state_l2l3_disable(काष्ठा rtl8169_निजी *tp)
अणु
	/* work around an issue when PCI reset occurs during L2/L3 state */
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Rdy_to_L23);
पूर्ण

अटल व्योम rtl_hw_aspm_clkreq_enable(काष्ठा rtl8169_निजी *tp, bool enable)
अणु
	/* Don't enable ASPM in the chip if OS can't control ASPM */
	अगर (enable && tp->aspm_manageable) अणु
		RTL_W8(tp, Config5, RTL_R8(tp, Config5) | ASPM_en);
		RTL_W8(tp, Config2, RTL_R8(tp, Config2) | ClkReqEn);
	पूर्ण अन्यथा अणु
		RTL_W8(tp, Config2, RTL_R8(tp, Config2) & ~ClkReqEn);
		RTL_W8(tp, Config5, RTL_R8(tp, Config5) & ~ASPM_en);
	पूर्ण

	udelay(10);
पूर्ण

अटल व्योम rtl_set_fअगरo_size(काष्ठा rtl8169_निजी *tp, u16 rx_stat,
			      u16 tx_stat, u16 rx_dyn, u16 tx_dyn)
अणु
	/* Usage of dynamic vs. अटल FIFO is controlled by bit
	 * TXCFG_AUTO_FIFO. Exact meaning of FIFO values isn't known.
	 */
	rtl_eri_ग_लिखो(tp, 0xc8, ERIAR_MASK_1111, (rx_stat << 16) | rx_dyn);
	rtl_eri_ग_लिखो(tp, 0xe8, ERIAR_MASK_1111, (tx_stat << 16) | tx_dyn);
पूर्ण

अटल व्योम rtl8168g_set_छोड़ो_thresholds(काष्ठा rtl8169_निजी *tp,
					  u8 low, u8 high)
अणु
	/* FIFO thresholds क्रम छोड़ो flow control */
	rtl_eri_ग_लिखो(tp, 0xcc, ERIAR_MASK_0001, low);
	rtl_eri_ग_लिखो(tp, 0xd0, ERIAR_MASK_0001, high);
पूर्ण

अटल व्योम rtl_hw_start_8168b(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Beacon_en);
पूर्ण

अटल व्योम __rtl_hw_start_8168cp(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, Config1, RTL_R8(tp, Config1) | Speed_करोwn);

	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Beacon_en);

	rtl_disable_घड़ी_request(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168cp_1(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168cp[] = अणु
		अणु 0x01, 0,	0x0001 पूर्ण,
		अणु 0x02, 0x0800,	0x1000 पूर्ण,
		अणु 0x03, 0,	0x0042 पूर्ण,
		अणु 0x06, 0x0080,	0x0000 पूर्ण,
		अणु 0x07, 0,	0x2000 पूर्ण
	पूर्ण;

	rtl_set_def_aspm_entry_latency(tp);

	rtl_ephy_init(tp, e_info_8168cp);

	__rtl_hw_start_8168cp(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168cp_2(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_set_def_aspm_entry_latency(tp);

	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Beacon_en);
पूर्ण

अटल व्योम rtl_hw_start_8168cp_3(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_set_def_aspm_entry_latency(tp);

	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Beacon_en);

	/* Magic. */
	RTL_W8(tp, DBG_REG, 0x20);
पूर्ण

अटल व्योम rtl_hw_start_8168c_1(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168c_1[] = अणु
		अणु 0x02, 0x0800,	0x1000 पूर्ण,
		अणु 0x03, 0,	0x0002 पूर्ण,
		अणु 0x06, 0x0080,	0x0000 पूर्ण
	पूर्ण;

	rtl_set_def_aspm_entry_latency(tp);

	RTL_W8(tp, DBG_REG, 0x06 | FIX_NAK_1 | FIX_NAK_2);

	rtl_ephy_init(tp, e_info_8168c_1);

	__rtl_hw_start_8168cp(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168c_2(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168c_2[] = अणु
		अणु 0x01, 0,	0x0001 पूर्ण,
		अणु 0x03, 0x0400,	0x0020 पूर्ण
	पूर्ण;

	rtl_set_def_aspm_entry_latency(tp);

	rtl_ephy_init(tp, e_info_8168c_2);

	__rtl_hw_start_8168cp(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168c_4(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_set_def_aspm_entry_latency(tp);

	__rtl_hw_start_8168cp(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168d(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_set_def_aspm_entry_latency(tp);

	rtl_disable_घड़ी_request(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168d_4(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168d_4[] = अणु
		अणु 0x0b, 0x0000,	0x0048 पूर्ण,
		अणु 0x19, 0x0020,	0x0050 पूर्ण,
		अणु 0x0c, 0x0100,	0x0020 पूर्ण,
		अणु 0x10, 0x0004,	0x0000 पूर्ण,
	पूर्ण;

	rtl_set_def_aspm_entry_latency(tp);

	rtl_ephy_init(tp, e_info_8168d_4);

	rtl_enable_घड़ी_request(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168e_1(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168e_1[] = अणु
		अणु 0x00, 0x0200,	0x0100 पूर्ण,
		अणु 0x00, 0x0000,	0x0004 पूर्ण,
		अणु 0x06, 0x0002,	0x0001 पूर्ण,
		अणु 0x06, 0x0000,	0x0030 पूर्ण,
		अणु 0x07, 0x0000,	0x2000 पूर्ण,
		अणु 0x00, 0x0000,	0x0020 पूर्ण,
		अणु 0x03, 0x5800,	0x2000 पूर्ण,
		अणु 0x03, 0x0000,	0x0001 पूर्ण,
		अणु 0x01, 0x0800,	0x1000 पूर्ण,
		अणु 0x07, 0x0000,	0x4000 पूर्ण,
		अणु 0x1e, 0x0000,	0x2000 पूर्ण,
		अणु 0x19, 0xffff,	0xfe6c पूर्ण,
		अणु 0x0a, 0x0000,	0x0040 पूर्ण
	पूर्ण;

	rtl_set_def_aspm_entry_latency(tp);

	rtl_ephy_init(tp, e_info_8168e_1);

	rtl_disable_घड़ी_request(tp);

	/* Reset tx FIFO poपूर्णांकer */
	RTL_W32(tp, MISC, RTL_R32(tp, MISC) | TXPLA_RST);
	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~TXPLA_RST);

	RTL_W8(tp, Config5, RTL_R8(tp, Config5) & ~Spi_en);
पूर्ण

अटल व्योम rtl_hw_start_8168e_2(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168e_2[] = अणु
		अणु 0x09, 0x0000,	0x0080 पूर्ण,
		अणु 0x19, 0x0000,	0x0224 पूर्ण,
		अणु 0x00, 0x0000,	0x0004 पूर्ण,
		अणु 0x0c, 0x3df0,	0x0200 पूर्ण,
	पूर्ण;

	rtl_set_def_aspm_entry_latency(tp);

	rtl_ephy_init(tp, e_info_8168e_2);

	rtl_eri_ग_लिखो(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_ग_लिखो(tp, 0xb8, ERIAR_MASK_1111, 0x0000);
	rtl_set_fअगरo_size(tp, 0x10, 0x10, 0x02, 0x06);
	rtl_eri_set_bits(tp, 0x0d4, 0x1f00);
	rtl_eri_set_bits(tp, 0x1d0, BIT(1));
	rtl_reset_packet_filter(tp);
	rtl_eri_set_bits(tp, 0x1b0, BIT(4));
	rtl_eri_ग_लिखो(tp, 0xcc, ERIAR_MASK_1111, 0x00000050);
	rtl_eri_ग_लिखो(tp, 0xd0, ERIAR_MASK_1111, 0x07ff0060);

	rtl_disable_घड़ी_request(tp);

	RTL_W8(tp, MCU, RTL_R8(tp, MCU) & ~NOW_IS_OOB);

	rtl8168_config_eee_mac(tp);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) | PFM_EN);
	RTL_W32(tp, MISC, RTL_R32(tp, MISC) | PWM_EN);
	RTL_W8(tp, Config5, RTL_R8(tp, Config5) & ~Spi_en);

	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_start_8168f(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_set_def_aspm_entry_latency(tp);

	rtl_eri_ग_लिखो(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_ग_लिखो(tp, 0xb8, ERIAR_MASK_1111, 0x0000);
	rtl_set_fअगरo_size(tp, 0x10, 0x10, 0x02, 0x06);
	rtl_reset_packet_filter(tp);
	rtl_eri_set_bits(tp, 0x1b0, BIT(4));
	rtl_eri_set_bits(tp, 0x1d0, BIT(4) | BIT(1));
	rtl_eri_ग_लिखो(tp, 0xcc, ERIAR_MASK_1111, 0x00000050);
	rtl_eri_ग_लिखो(tp, 0xd0, ERIAR_MASK_1111, 0x00000060);

	rtl_disable_घड़ी_request(tp);

	RTL_W8(tp, MCU, RTL_R8(tp, MCU) & ~NOW_IS_OOB);
	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) | PFM_EN);
	RTL_W32(tp, MISC, RTL_R32(tp, MISC) | PWM_EN);
	RTL_W8(tp, Config5, RTL_R8(tp, Config5) & ~Spi_en);

	rtl8168_config_eee_mac(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168f_1(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168f_1[] = अणु
		अणु 0x06, 0x00c0,	0x0020 पूर्ण,
		अणु 0x08, 0x0001,	0x0002 पूर्ण,
		अणु 0x09, 0x0000,	0x0080 पूर्ण,
		अणु 0x19, 0x0000,	0x0224 पूर्ण,
		अणु 0x00, 0x0000,	0x0008 पूर्ण,
		अणु 0x0c, 0x3df0,	0x0200 पूर्ण,
	पूर्ण;

	rtl_hw_start_8168f(tp);

	rtl_ephy_init(tp, e_info_8168f_1);

	rtl_eri_set_bits(tp, 0x0d4, 0x1f00);
पूर्ण

अटल व्योम rtl_hw_start_8411(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168f_1[] = अणु
		अणु 0x06, 0x00c0,	0x0020 पूर्ण,
		अणु 0x0f, 0xffff,	0x5200 पूर्ण,
		अणु 0x19, 0x0000,	0x0224 पूर्ण,
		अणु 0x00, 0x0000,	0x0008 पूर्ण,
		अणु 0x0c, 0x3df0,	0x0200 पूर्ण,
	पूर्ण;

	rtl_hw_start_8168f(tp);
	rtl_pcie_state_l2l3_disable(tp);

	rtl_ephy_init(tp, e_info_8168f_1);

	rtl_eri_set_bits(tp, 0x0d4, 0x0c00);
पूर्ण

अटल व्योम rtl_hw_start_8168g(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_set_fअगरo_size(tp, 0x08, 0x10, 0x02, 0x06);
	rtl8168g_set_छोड़ो_thresholds(tp, 0x38, 0x48);

	rtl_set_def_aspm_entry_latency(tp);

	rtl_reset_packet_filter(tp);
	rtl_eri_ग_लिखो(tp, 0x2f8, ERIAR_MASK_0011, 0x1d8f);

	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~RXDV_GATED_EN);

	rtl_eri_ग_लिखो(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_ग_लिखो(tp, 0xb8, ERIAR_MASK_0011, 0x0000);
	rtl_eri_set_bits(tp, 0x0d4, 0x1f80);

	rtl8168_config_eee_mac(tp);

	rtl_w0w1_eri(tp, 0x2fc, 0x01, 0x06);
	rtl_eri_clear_bits(tp, 0x1b0, BIT(12));

	rtl_pcie_state_l2l3_disable(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168g_1(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168g_1[] = अणु
		अणु 0x00, 0x0008,	0x0000 पूर्ण,
		अणु 0x0c, 0x3ff0,	0x0820 पूर्ण,
		अणु 0x1e, 0x0000,	0x0001 पूर्ण,
		अणु 0x19, 0x8000,	0x0000 पूर्ण
	पूर्ण;

	rtl_hw_start_8168g(tp);

	/* disable aspm and घड़ी request beक्रमe access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8168g_1);
	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_start_8168g_2(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168g_2[] = अणु
		अणु 0x00, 0x0008,	0x0000 पूर्ण,
		अणु 0x0c, 0x3ff0,	0x0820 पूर्ण,
		अणु 0x19, 0xffff,	0x7c00 पूर्ण,
		अणु 0x1e, 0xffff,	0x20eb पूर्ण,
		अणु 0x0d, 0xffff,	0x1666 पूर्ण,
		अणु 0x00, 0xffff,	0x10a3 पूर्ण,
		अणु 0x06, 0xffff,	0xf050 पूर्ण,
		अणु 0x04, 0x0000,	0x0010 पूर्ण,
		अणु 0x1d, 0x4000,	0x0000 पूर्ण,
	पूर्ण;

	rtl_hw_start_8168g(tp);

	/* disable aspm and घड़ी request beक्रमe access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8168g_2);
पूर्ण

अटल व्योम rtl_hw_start_8411_2(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8411_2[] = अणु
		अणु 0x00, 0x0008,	0x0000 पूर्ण,
		अणु 0x0c, 0x37d0,	0x0820 पूर्ण,
		अणु 0x1e, 0x0000,	0x0001 पूर्ण,
		अणु 0x19, 0x8021,	0x0000 पूर्ण,
		अणु 0x1e, 0x0000,	0x2000 पूर्ण,
		अणु 0x0d, 0x0100,	0x0200 पूर्ण,
		अणु 0x00, 0x0000,	0x0080 पूर्ण,
		अणु 0x06, 0x0000,	0x0010 पूर्ण,
		अणु 0x04, 0x0000,	0x0010 पूर्ण,
		अणु 0x1d, 0x0000,	0x4000 पूर्ण,
	पूर्ण;

	rtl_hw_start_8168g(tp);

	/* disable aspm and घड़ी request beक्रमe access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8411_2);

	/* The following Realtek-provided magic fixes an issue with the RX unit
	 * getting confused after the PHY having been घातered-करोwn.
	 */
	r8168_mac_ocp_ग_लिखो(tp, 0xFC28, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC2A, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC2C, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC2E, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC30, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC32, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC34, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC36, 0x0000);
	mdelay(3);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC26, 0x0000);

	r8168_mac_ocp_ग_लिखो(tp, 0xF800, 0xE008);
	r8168_mac_ocp_ग_लिखो(tp, 0xF802, 0xE00A);
	r8168_mac_ocp_ग_लिखो(tp, 0xF804, 0xE00C);
	r8168_mac_ocp_ग_लिखो(tp, 0xF806, 0xE00E);
	r8168_mac_ocp_ग_लिखो(tp, 0xF808, 0xE027);
	r8168_mac_ocp_ग_लिखो(tp, 0xF80A, 0xE04F);
	r8168_mac_ocp_ग_लिखो(tp, 0xF80C, 0xE05E);
	r8168_mac_ocp_ग_लिखो(tp, 0xF80E, 0xE065);
	r8168_mac_ocp_ग_लिखो(tp, 0xF810, 0xC602);
	r8168_mac_ocp_ग_लिखो(tp, 0xF812, 0xBE00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF814, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xF816, 0xC502);
	r8168_mac_ocp_ग_लिखो(tp, 0xF818, 0xBD00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF81A, 0x074C);
	r8168_mac_ocp_ग_लिखो(tp, 0xF81C, 0xC302);
	r8168_mac_ocp_ग_लिखो(tp, 0xF81E, 0xBB00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF820, 0x080A);
	r8168_mac_ocp_ग_लिखो(tp, 0xF822, 0x6420);
	r8168_mac_ocp_ग_लिखो(tp, 0xF824, 0x48C2);
	r8168_mac_ocp_ग_लिखो(tp, 0xF826, 0x8C20);
	r8168_mac_ocp_ग_लिखो(tp, 0xF828, 0xC516);
	r8168_mac_ocp_ग_लिखो(tp, 0xF82A, 0x64A4);
	r8168_mac_ocp_ग_लिखो(tp, 0xF82C, 0x49C0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF82E, 0xF009);
	r8168_mac_ocp_ग_लिखो(tp, 0xF830, 0x74A2);
	r8168_mac_ocp_ग_लिखो(tp, 0xF832, 0x8CA5);
	r8168_mac_ocp_ग_लिखो(tp, 0xF834, 0x74A0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF836, 0xC50E);
	r8168_mac_ocp_ग_लिखो(tp, 0xF838, 0x9CA2);
	r8168_mac_ocp_ग_लिखो(tp, 0xF83A, 0x1C11);
	r8168_mac_ocp_ग_लिखो(tp, 0xF83C, 0x9CA0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF83E, 0xE006);
	r8168_mac_ocp_ग_लिखो(tp, 0xF840, 0x74F8);
	r8168_mac_ocp_ग_लिखो(tp, 0xF842, 0x48C4);
	r8168_mac_ocp_ग_लिखो(tp, 0xF844, 0x8CF8);
	r8168_mac_ocp_ग_लिखो(tp, 0xF846, 0xC404);
	r8168_mac_ocp_ग_लिखो(tp, 0xF848, 0xBC00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF84A, 0xC403);
	r8168_mac_ocp_ग_लिखो(tp, 0xF84C, 0xBC00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF84E, 0x0BF2);
	r8168_mac_ocp_ग_लिखो(tp, 0xF850, 0x0C0A);
	r8168_mac_ocp_ग_लिखो(tp, 0xF852, 0xE434);
	r8168_mac_ocp_ग_लिखो(tp, 0xF854, 0xD3C0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF856, 0x49D9);
	r8168_mac_ocp_ग_लिखो(tp, 0xF858, 0xF01F);
	r8168_mac_ocp_ग_लिखो(tp, 0xF85A, 0xC526);
	r8168_mac_ocp_ग_लिखो(tp, 0xF85C, 0x64A5);
	r8168_mac_ocp_ग_लिखो(tp, 0xF85E, 0x1400);
	r8168_mac_ocp_ग_लिखो(tp, 0xF860, 0xF007);
	r8168_mac_ocp_ग_लिखो(tp, 0xF862, 0x0C01);
	r8168_mac_ocp_ग_लिखो(tp, 0xF864, 0x8CA5);
	r8168_mac_ocp_ग_लिखो(tp, 0xF866, 0x1C15);
	r8168_mac_ocp_ग_लिखो(tp, 0xF868, 0xC51B);
	r8168_mac_ocp_ग_लिखो(tp, 0xF86A, 0x9CA0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF86C, 0xE013);
	r8168_mac_ocp_ग_लिखो(tp, 0xF86E, 0xC519);
	r8168_mac_ocp_ग_लिखो(tp, 0xF870, 0x74A0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF872, 0x48C4);
	r8168_mac_ocp_ग_लिखो(tp, 0xF874, 0x8CA0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF876, 0xC516);
	r8168_mac_ocp_ग_लिखो(tp, 0xF878, 0x74A4);
	r8168_mac_ocp_ग_लिखो(tp, 0xF87A, 0x48C8);
	r8168_mac_ocp_ग_लिखो(tp, 0xF87C, 0x48CA);
	r8168_mac_ocp_ग_लिखो(tp, 0xF87E, 0x9CA4);
	r8168_mac_ocp_ग_लिखो(tp, 0xF880, 0xC512);
	r8168_mac_ocp_ग_लिखो(tp, 0xF882, 0x1B00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF884, 0x9BA0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF886, 0x1B1C);
	r8168_mac_ocp_ग_लिखो(tp, 0xF888, 0x483F);
	r8168_mac_ocp_ग_लिखो(tp, 0xF88A, 0x9BA2);
	r8168_mac_ocp_ग_लिखो(tp, 0xF88C, 0x1B04);
	r8168_mac_ocp_ग_लिखो(tp, 0xF88E, 0xC508);
	r8168_mac_ocp_ग_लिखो(tp, 0xF890, 0x9BA0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF892, 0xC505);
	r8168_mac_ocp_ग_लिखो(tp, 0xF894, 0xBD00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF896, 0xC502);
	r8168_mac_ocp_ग_लिखो(tp, 0xF898, 0xBD00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF89A, 0x0300);
	r8168_mac_ocp_ग_लिखो(tp, 0xF89C, 0x051E);
	r8168_mac_ocp_ग_लिखो(tp, 0xF89E, 0xE434);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8A0, 0xE018);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8A2, 0xE092);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8A4, 0xDE20);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8A6, 0xD3C0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8A8, 0xC50F);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8AA, 0x76A4);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8AC, 0x49E3);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8AE, 0xF007);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8B0, 0x49C0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8B2, 0xF103);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8B4, 0xC607);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8B6, 0xBE00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8B8, 0xC606);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8BA, 0xBE00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8BC, 0xC602);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8BE, 0xBE00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8C0, 0x0C4C);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8C2, 0x0C28);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8C4, 0x0C2C);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8C6, 0xDC00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8C8, 0xC707);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8CA, 0x1D00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8CC, 0x8DE2);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8CE, 0x48C1);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8D0, 0xC502);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8D2, 0xBD00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8D4, 0x00AA);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8D6, 0xE0C0);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8D8, 0xC502);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8DA, 0xBD00);
	r8168_mac_ocp_ग_लिखो(tp, 0xF8DC, 0x0132);

	r8168_mac_ocp_ग_लिखो(tp, 0xFC26, 0x8000);

	r8168_mac_ocp_ग_लिखो(tp, 0xFC2A, 0x0743);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC2C, 0x0801);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC2E, 0x0BE9);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC30, 0x02FD);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC32, 0x0C25);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC34, 0x00A9);
	r8168_mac_ocp_ग_लिखो(tp, 0xFC36, 0x012D);

	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_start_8168h_1(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168h_1[] = अणु
		अणु 0x1e, 0x0800,	0x0001 पूर्ण,
		अणु 0x1d, 0x0000,	0x0800 पूर्ण,
		अणु 0x05, 0xffff,	0x2089 पूर्ण,
		अणु 0x06, 0xffff,	0x5881 पूर्ण,
		अणु 0x04, 0xffff,	0x854a पूर्ण,
		अणु 0x01, 0xffff,	0x068b पूर्ण
	पूर्ण;
	पूर्णांक rg_saw_cnt;

	/* disable aspm and घड़ी request beक्रमe access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8168h_1);

	rtl_set_fअगरo_size(tp, 0x08, 0x10, 0x02, 0x06);
	rtl8168g_set_छोड़ो_thresholds(tp, 0x38, 0x48);

	rtl_set_def_aspm_entry_latency(tp);

	rtl_reset_packet_filter(tp);

	rtl_eri_set_bits(tp, 0xd4, 0x1f00);
	rtl_eri_set_bits(tp, 0xdc, 0x001c);

	rtl_eri_ग_लिखो(tp, 0x5f0, ERIAR_MASK_0011, 0x4f87);

	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~RXDV_GATED_EN);

	rtl_eri_ग_लिखो(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_ग_लिखो(tp, 0xb8, ERIAR_MASK_0011, 0x0000);

	rtl8168_config_eee_mac(tp);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~PFM_EN);
	RTL_W8(tp, MISC_1, RTL_R8(tp, MISC_1) & ~PFM_D3COLD_EN);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~TX_10M_PS_EN);

	rtl_eri_clear_bits(tp, 0x1b0, BIT(12));

	rtl_pcie_state_l2l3_disable(tp);

	rg_saw_cnt = phy_पढ़ो_paged(tp->phydev, 0x0c42, 0x13) & 0x3fff;
	अगर (rg_saw_cnt > 0) अणु
		u16 sw_cnt_1ms_ini;

		sw_cnt_1ms_ini = 16000000/rg_saw_cnt;
		sw_cnt_1ms_ini &= 0x0fff;
		r8168_mac_ocp_modअगरy(tp, 0xd412, 0x0fff, sw_cnt_1ms_ini);
	पूर्ण

	r8168_mac_ocp_modअगरy(tp, 0xe056, 0x00f0, 0x0070);
	r8168_mac_ocp_modअगरy(tp, 0xe052, 0x6000, 0x8008);
	r8168_mac_ocp_modअगरy(tp, 0xe0d6, 0x01ff, 0x017f);
	r8168_mac_ocp_modअगरy(tp, 0xd420, 0x0fff, 0x047f);

	r8168_mac_ocp_ग_लिखो(tp, 0xe63e, 0x0001);
	r8168_mac_ocp_ग_लिखो(tp, 0xe63e, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xc094, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xc09e, 0x0000);

	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_start_8168ep(काष्ठा rtl8169_निजी *tp)
अणु
	rtl8168ep_stop_cmac(tp);

	rtl_set_fअगरo_size(tp, 0x08, 0x10, 0x02, 0x06);
	rtl8168g_set_छोड़ो_thresholds(tp, 0x2f, 0x5f);

	rtl_set_def_aspm_entry_latency(tp);

	rtl_reset_packet_filter(tp);

	rtl_eri_set_bits(tp, 0xd4, 0x1f80);

	rtl_eri_ग_लिखो(tp, 0x5f0, ERIAR_MASK_0011, 0x4f87);

	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~RXDV_GATED_EN);

	rtl_eri_ग_लिखो(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_ग_लिखो(tp, 0xb8, ERIAR_MASK_0011, 0x0000);

	rtl8168_config_eee_mac(tp);

	rtl_w0w1_eri(tp, 0x2fc, 0x01, 0x06);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~TX_10M_PS_EN);

	rtl_pcie_state_l2l3_disable(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168ep_1(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168ep_1[] = अणु
		अणु 0x00, 0xffff,	0x10ab पूर्ण,
		अणु 0x06, 0xffff,	0xf030 पूर्ण,
		अणु 0x08, 0xffff,	0x2006 पूर्ण,
		अणु 0x0d, 0xffff,	0x1666 पूर्ण,
		अणु 0x0c, 0x3ff0,	0x0000 पूर्ण
	पूर्ण;

	/* disable aspm and घड़ी request beक्रमe access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8168ep_1);

	rtl_hw_start_8168ep(tp);

	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_start_8168ep_2(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168ep_2[] = अणु
		अणु 0x00, 0xffff,	0x10a3 पूर्ण,
		अणु 0x19, 0xffff,	0xfc00 पूर्ण,
		अणु 0x1e, 0xffff,	0x20ea पूर्ण
	पूर्ण;

	/* disable aspm and घड़ी request beक्रमe access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8168ep_2);

	rtl_hw_start_8168ep(tp);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~PFM_EN);
	RTL_W8(tp, MISC_1, RTL_R8(tp, MISC_1) & ~PFM_D3COLD_EN);

	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_start_8168ep_3(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8168ep_3[] = अणु
		अणु 0x00, 0x0000,	0x0080 पूर्ण,
		अणु 0x0d, 0x0100,	0x0200 पूर्ण,
		अणु 0x19, 0x8021,	0x0000 पूर्ण,
		अणु 0x1e, 0x0000,	0x2000 पूर्ण,
	पूर्ण;

	/* disable aspm and घड़ी request beक्रमe access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8168ep_3);

	rtl_hw_start_8168ep(tp);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~PFM_EN);
	RTL_W8(tp, MISC_1, RTL_R8(tp, MISC_1) & ~PFM_D3COLD_EN);

	r8168_mac_ocp_modअगरy(tp, 0xd3e2, 0x0fff, 0x0271);
	r8168_mac_ocp_modअगरy(tp, 0xd3e4, 0x00ff, 0x0000);
	r8168_mac_ocp_modअगरy(tp, 0xe860, 0x0000, 0x0080);

	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_start_8117(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8117[] = अणु
		अणु 0x19, 0x0040,	0x1100 पूर्ण,
		अणु 0x59, 0x0040,	0x1100 पूर्ण,
	पूर्ण;
	पूर्णांक rg_saw_cnt;

	rtl8168ep_stop_cmac(tp);

	/* disable aspm and घड़ी request beक्रमe access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8117);

	rtl_set_fअगरo_size(tp, 0x08, 0x10, 0x02, 0x06);
	rtl8168g_set_छोड़ो_thresholds(tp, 0x2f, 0x5f);

	rtl_set_def_aspm_entry_latency(tp);

	rtl_reset_packet_filter(tp);

	rtl_eri_set_bits(tp, 0xd4, 0x1f90);

	rtl_eri_ग_लिखो(tp, 0x5f0, ERIAR_MASK_0011, 0x4f87);

	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~RXDV_GATED_EN);

	rtl_eri_ग_लिखो(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_ग_लिखो(tp, 0xb8, ERIAR_MASK_0011, 0x0000);

	rtl8168_config_eee_mac(tp);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~PFM_EN);
	RTL_W8(tp, MISC_1, RTL_R8(tp, MISC_1) & ~PFM_D3COLD_EN);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~TX_10M_PS_EN);

	rtl_eri_clear_bits(tp, 0x1b0, BIT(12));

	rtl_pcie_state_l2l3_disable(tp);

	rg_saw_cnt = phy_पढ़ो_paged(tp->phydev, 0x0c42, 0x13) & 0x3fff;
	अगर (rg_saw_cnt > 0) अणु
		u16 sw_cnt_1ms_ini;

		sw_cnt_1ms_ini = (16000000 / rg_saw_cnt) & 0x0fff;
		r8168_mac_ocp_modअगरy(tp, 0xd412, 0x0fff, sw_cnt_1ms_ini);
	पूर्ण

	r8168_mac_ocp_modअगरy(tp, 0xe056, 0x00f0, 0x0070);
	r8168_mac_ocp_ग_लिखो(tp, 0xea80, 0x0003);
	r8168_mac_ocp_modअगरy(tp, 0xe052, 0x0000, 0x0009);
	r8168_mac_ocp_modअगरy(tp, 0xd420, 0x0fff, 0x047f);

	r8168_mac_ocp_ग_लिखो(tp, 0xe63e, 0x0001);
	r8168_mac_ocp_ग_लिखो(tp, 0xe63e, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xc094, 0x0000);
	r8168_mac_ocp_ग_लिखो(tp, 0xc09e, 0x0000);

	/* firmware is क्रम MAC only */
	r8169_apply_firmware(tp);

	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_start_8102e_1(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8102e_1[] = अणु
		अणु 0x01,	0, 0x6e65 पूर्ण,
		अणु 0x02,	0, 0x091f पूर्ण,
		अणु 0x03,	0, 0xc2f9 पूर्ण,
		अणु 0x06,	0, 0xafb5 पूर्ण,
		अणु 0x07,	0, 0x0e00 पूर्ण,
		अणु 0x19,	0, 0xec80 पूर्ण,
		अणु 0x01,	0, 0x2e65 पूर्ण,
		अणु 0x01,	0, 0x6e65 पूर्ण
	पूर्ण;
	u8 cfg1;

	rtl_set_def_aspm_entry_latency(tp);

	RTL_W8(tp, DBG_REG, FIX_NAK_1);

	RTL_W8(tp, Config1,
	       LEDS1 | LEDS0 | Speed_करोwn | MEMMAP | IOMAP | VPD | PMEnable);
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Beacon_en);

	cfg1 = RTL_R8(tp, Config1);
	अगर ((cfg1 & LEDS0) && (cfg1 & LEDS1))
		RTL_W8(tp, Config1, cfg1 & ~LEDS0);

	rtl_ephy_init(tp, e_info_8102e_1);
पूर्ण

अटल व्योम rtl_hw_start_8102e_2(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_set_def_aspm_entry_latency(tp);

	RTL_W8(tp, Config1, MEMMAP | IOMAP | VPD | PMEnable);
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Beacon_en);
पूर्ण

अटल व्योम rtl_hw_start_8102e_3(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_hw_start_8102e_2(tp);

	rtl_ephy_ग_लिखो(tp, 0x03, 0xc2f9);
पूर्ण

अटल व्योम rtl_hw_start_8401(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8401[] = अणु
		अणु 0x01,	0xffff, 0x6fe5 पूर्ण,
		अणु 0x03,	0xffff, 0x0599 पूर्ण,
		अणु 0x06,	0xffff, 0xaf25 पूर्ण,
		अणु 0x07,	0xffff, 0x8e68 पूर्ण,
	पूर्ण;

	rtl_ephy_init(tp, e_info_8401);
	RTL_W8(tp, Config3, RTL_R8(tp, Config3) & ~Beacon_en);
पूर्ण

अटल व्योम rtl_hw_start_8105e_1(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8105e_1[] = अणु
		अणु 0x07,	0, 0x4000 पूर्ण,
		अणु 0x19,	0, 0x0200 पूर्ण,
		अणु 0x19,	0, 0x0020 पूर्ण,
		अणु 0x1e,	0, 0x2000 पूर्ण,
		अणु 0x03,	0, 0x0001 पूर्ण,
		अणु 0x19,	0, 0x0100 पूर्ण,
		अणु 0x19,	0, 0x0004 पूर्ण,
		अणु 0x0a,	0, 0x0020 पूर्ण
	पूर्ण;

	/* Force LAN निकास from ASPM अगर Rx/Tx are not idle */
	RTL_W32(tp, FuncEvent, RTL_R32(tp, FuncEvent) | 0x002800);

	/* Disable Early Tally Counter */
	RTL_W32(tp, FuncEvent, RTL_R32(tp, FuncEvent) & ~0x010000);

	RTL_W8(tp, MCU, RTL_R8(tp, MCU) | EN_NDP | EN_OOB_RESET);
	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) | PFM_EN);

	rtl_ephy_init(tp, e_info_8105e_1);

	rtl_pcie_state_l2l3_disable(tp);
पूर्ण

अटल व्योम rtl_hw_start_8105e_2(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_hw_start_8105e_1(tp);
	rtl_ephy_ग_लिखो(tp, 0x1e, rtl_ephy_पढ़ो(tp, 0x1e) | 0x8000);
पूर्ण

अटल व्योम rtl_hw_start_8402(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8402[] = अणु
		अणु 0x19,	0xffff, 0xff64 पूर्ण,
		अणु 0x1e,	0, 0x4000 पूर्ण
	पूर्ण;

	rtl_set_def_aspm_entry_latency(tp);

	/* Force LAN निकास from ASPM अगर Rx/Tx are not idle */
	RTL_W32(tp, FuncEvent, RTL_R32(tp, FuncEvent) | 0x002800);

	RTL_W8(tp, MCU, RTL_R8(tp, MCU) & ~NOW_IS_OOB);

	rtl_ephy_init(tp, e_info_8402);

	rtl_set_fअगरo_size(tp, 0x00, 0x00, 0x02, 0x06);
	rtl_reset_packet_filter(tp);
	rtl_eri_ग_लिखो(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_ग_लिखो(tp, 0xb8, ERIAR_MASK_0011, 0x0000);
	rtl_w0w1_eri(tp, 0x0d4, 0x0e00, 0xff00);

	/* disable EEE */
	rtl_eri_ग_लिखो(tp, 0x1b0, ERIAR_MASK_0011, 0x0000);

	rtl_pcie_state_l2l3_disable(tp);
पूर्ण

अटल व्योम rtl_hw_start_8106(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_hw_aspm_clkreq_enable(tp, false);

	/* Force LAN निकास from ASPM अगर Rx/Tx are not idle */
	RTL_W32(tp, FuncEvent, RTL_R32(tp, FuncEvent) | 0x002800);

	RTL_W32(tp, MISC, (RTL_R32(tp, MISC) | DISABLE_LAN_EN) & ~EARLY_TALLY_EN);
	RTL_W8(tp, MCU, RTL_R8(tp, MCU) | EN_NDP | EN_OOB_RESET);
	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~PFM_EN);

	rtl_eri_ग_लिखो(tp, 0x1d0, ERIAR_MASK_0011, 0x0000);

	/* disable EEE */
	rtl_eri_ग_लिखो(tp, 0x1b0, ERIAR_MASK_0011, 0x0000);

	rtl_pcie_state_l2l3_disable(tp);
	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

DECLARE_RTL_COND(rtl_mac_ocp_e00e_cond)
अणु
	वापस r8168_mac_ocp_पढ़ो(tp, 0xe00e) & BIT(13);
पूर्ण

अटल व्योम rtl_hw_start_8125_common(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_pcie_state_l2l3_disable(tp);

	RTL_W16(tp, 0x382, 0x221b);
	RTL_W8(tp, 0x4500, 0);
	RTL_W16(tp, 0x4800, 0);

	/* disable UPS */
	r8168_mac_ocp_modअगरy(tp, 0xd40a, 0x0010, 0x0000);

	RTL_W8(tp, Config1, RTL_R8(tp, Config1) & ~0x10);

	r8168_mac_ocp_ग_लिखो(tp, 0xc140, 0xffff);
	r8168_mac_ocp_ग_लिखो(tp, 0xc142, 0xffff);

	r8168_mac_ocp_modअगरy(tp, 0xd3e2, 0x0fff, 0x03a9);
	r8168_mac_ocp_modअगरy(tp, 0xd3e4, 0x00ff, 0x0000);
	r8168_mac_ocp_modअगरy(tp, 0xe860, 0x0000, 0x0080);

	/* disable new tx descriptor क्रमmat */
	r8168_mac_ocp_modअगरy(tp, 0xeb58, 0x0001, 0x0000);

	अगर (tp->mac_version == RTL_GIGA_MAC_VER_63)
		r8168_mac_ocp_modअगरy(tp, 0xe614, 0x0700, 0x0200);
	अन्यथा
		r8168_mac_ocp_modअगरy(tp, 0xe614, 0x0700, 0x0400);

	अगर (tp->mac_version == RTL_GIGA_MAC_VER_63)
		r8168_mac_ocp_modअगरy(tp, 0xe63e, 0x0c30, 0x0000);
	अन्यथा
		r8168_mac_ocp_modअगरy(tp, 0xe63e, 0x0c30, 0x0020);

	r8168_mac_ocp_modअगरy(tp, 0xc0b4, 0x0000, 0x000c);
	r8168_mac_ocp_modअगरy(tp, 0xeb6a, 0x00ff, 0x0033);
	r8168_mac_ocp_modअगरy(tp, 0xeb50, 0x03e0, 0x0040);
	r8168_mac_ocp_modअगरy(tp, 0xe056, 0x00f0, 0x0030);
	r8168_mac_ocp_modअगरy(tp, 0xe040, 0x1000, 0x0000);
	r8168_mac_ocp_modअगरy(tp, 0xea1c, 0x0003, 0x0001);
	r8168_mac_ocp_modअगरy(tp, 0xe0c0, 0x4f0f, 0x4403);
	r8168_mac_ocp_modअगरy(tp, 0xe052, 0x0080, 0x0068);
	r8168_mac_ocp_modअगरy(tp, 0xc0ac, 0x0080, 0x1f00);
	r8168_mac_ocp_modअगरy(tp, 0xd430, 0x0fff, 0x047f);

	r8168_mac_ocp_modअगरy(tp, 0xea1c, 0x0004, 0x0000);
	r8168_mac_ocp_modअगरy(tp, 0xeb54, 0x0000, 0x0001);
	udelay(1);
	r8168_mac_ocp_modअगरy(tp, 0xeb54, 0x0001, 0x0000);
	RTL_W16(tp, 0x1880, RTL_R16(tp, 0x1880) & ~0x0030);

	r8168_mac_ocp_ग_लिखो(tp, 0xe098, 0xc302);

	rtl_loop_रुको_low(tp, &rtl_mac_ocp_e00e_cond, 1000, 10);

	अगर (tp->mac_version == RTL_GIGA_MAC_VER_63)
		rtl8125b_config_eee_mac(tp);
	अन्यथा
		rtl8125a_config_eee_mac(tp);

	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~RXDV_GATED_EN);
	udelay(10);
पूर्ण

अटल व्योम rtl_hw_start_8125a_1(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8125a_1[] = अणु
		अणु 0x01, 0xffff, 0xa812 पूर्ण,
		अणु 0x09, 0xffff, 0x520c पूर्ण,
		अणु 0x04, 0xffff, 0xd000 पूर्ण,
		अणु 0x0d, 0xffff, 0xf702 पूर्ण,
		अणु 0x0a, 0xffff, 0x8653 पूर्ण,
		अणु 0x06, 0xffff, 0x001e पूर्ण,
		अणु 0x08, 0xffff, 0x3595 पूर्ण,
		अणु 0x20, 0xffff, 0x9455 पूर्ण,
		अणु 0x21, 0xffff, 0x99ff पूर्ण,
		अणु 0x02, 0xffff, 0x6046 पूर्ण,
		अणु 0x29, 0xffff, 0xfe00 पूर्ण,
		अणु 0x23, 0xffff, 0xab62 पूर्ण,

		अणु 0x41, 0xffff, 0xa80c पूर्ण,
		अणु 0x49, 0xffff, 0x520c पूर्ण,
		अणु 0x44, 0xffff, 0xd000 पूर्ण,
		अणु 0x4d, 0xffff, 0xf702 पूर्ण,
		अणु 0x4a, 0xffff, 0x8653 पूर्ण,
		अणु 0x46, 0xffff, 0x001e पूर्ण,
		अणु 0x48, 0xffff, 0x3595 पूर्ण,
		अणु 0x60, 0xffff, 0x9455 पूर्ण,
		अणु 0x61, 0xffff, 0x99ff पूर्ण,
		अणु 0x42, 0xffff, 0x6046 पूर्ण,
		अणु 0x69, 0xffff, 0xfe00 पूर्ण,
		अणु 0x63, 0xffff, 0xab62 पूर्ण,
	पूर्ण;

	rtl_set_def_aspm_entry_latency(tp);

	/* disable aspm and घड़ी request beक्रमe access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8125a_1);

	rtl_hw_start_8125_common(tp);
	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_start_8125a_2(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8125a_2[] = अणु
		अणु 0x04, 0xffff, 0xd000 पूर्ण,
		अणु 0x0a, 0xffff, 0x8653 पूर्ण,
		अणु 0x23, 0xffff, 0xab66 पूर्ण,
		अणु 0x20, 0xffff, 0x9455 पूर्ण,
		अणु 0x21, 0xffff, 0x99ff पूर्ण,
		अणु 0x29, 0xffff, 0xfe04 पूर्ण,

		अणु 0x44, 0xffff, 0xd000 पूर्ण,
		अणु 0x4a, 0xffff, 0x8653 पूर्ण,
		अणु 0x63, 0xffff, 0xab66 पूर्ण,
		अणु 0x60, 0xffff, 0x9455 पूर्ण,
		अणु 0x61, 0xffff, 0x99ff पूर्ण,
		अणु 0x69, 0xffff, 0xfe04 पूर्ण,
	पूर्ण;

	rtl_set_def_aspm_entry_latency(tp);

	/* disable aspm and घड़ी request beक्रमe access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8125a_2);

	rtl_hw_start_8125_common(tp);
	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_start_8125b(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर काष्ठा ephy_info e_info_8125b[] = अणु
		अणु 0x0b, 0xffff, 0xa908 पूर्ण,
		अणु 0x1e, 0xffff, 0x20eb पूर्ण,
		अणु 0x4b, 0xffff, 0xa908 पूर्ण,
		अणु 0x5e, 0xffff, 0x20eb पूर्ण,
		अणु 0x22, 0x0030, 0x0020 पूर्ण,
		अणु 0x62, 0x0030, 0x0020 पूर्ण,
	पूर्ण;

	rtl_set_def_aspm_entry_latency(tp);
	rtl_hw_aspm_clkreq_enable(tp, false);

	rtl_ephy_init(tp, e_info_8125b);
	rtl_hw_start_8125_common(tp);

	rtl_hw_aspm_clkreq_enable(tp, true);
पूर्ण

अटल व्योम rtl_hw_config(काष्ठा rtl8169_निजी *tp)
अणु
	अटल स्थिर rtl_generic_fct hw_configs[] = अणु
		[RTL_GIGA_MAC_VER_07] = rtl_hw_start_8102e_1,
		[RTL_GIGA_MAC_VER_08] = rtl_hw_start_8102e_3,
		[RTL_GIGA_MAC_VER_09] = rtl_hw_start_8102e_2,
		[RTL_GIGA_MAC_VER_10] = शून्य,
		[RTL_GIGA_MAC_VER_11] = rtl_hw_start_8168b,
		[RTL_GIGA_MAC_VER_12] = rtl_hw_start_8168b,
		[RTL_GIGA_MAC_VER_13] = शून्य,
		[RTL_GIGA_MAC_VER_14] = rtl_hw_start_8401,
		[RTL_GIGA_MAC_VER_16] = शून्य,
		[RTL_GIGA_MAC_VER_17] = rtl_hw_start_8168b,
		[RTL_GIGA_MAC_VER_18] = rtl_hw_start_8168cp_1,
		[RTL_GIGA_MAC_VER_19] = rtl_hw_start_8168c_1,
		[RTL_GIGA_MAC_VER_20] = rtl_hw_start_8168c_2,
		[RTL_GIGA_MAC_VER_21] = rtl_hw_start_8168c_2,
		[RTL_GIGA_MAC_VER_22] = rtl_hw_start_8168c_4,
		[RTL_GIGA_MAC_VER_23] = rtl_hw_start_8168cp_2,
		[RTL_GIGA_MAC_VER_24] = rtl_hw_start_8168cp_3,
		[RTL_GIGA_MAC_VER_25] = rtl_hw_start_8168d,
		[RTL_GIGA_MAC_VER_26] = rtl_hw_start_8168d,
		[RTL_GIGA_MAC_VER_27] = rtl_hw_start_8168d,
		[RTL_GIGA_MAC_VER_28] = rtl_hw_start_8168d_4,
		[RTL_GIGA_MAC_VER_29] = rtl_hw_start_8105e_1,
		[RTL_GIGA_MAC_VER_30] = rtl_hw_start_8105e_2,
		[RTL_GIGA_MAC_VER_31] = rtl_hw_start_8168d,
		[RTL_GIGA_MAC_VER_32] = rtl_hw_start_8168e_1,
		[RTL_GIGA_MAC_VER_33] = rtl_hw_start_8168e_1,
		[RTL_GIGA_MAC_VER_34] = rtl_hw_start_8168e_2,
		[RTL_GIGA_MAC_VER_35] = rtl_hw_start_8168f_1,
		[RTL_GIGA_MAC_VER_36] = rtl_hw_start_8168f_1,
		[RTL_GIGA_MAC_VER_37] = rtl_hw_start_8402,
		[RTL_GIGA_MAC_VER_38] = rtl_hw_start_8411,
		[RTL_GIGA_MAC_VER_39] = rtl_hw_start_8106,
		[RTL_GIGA_MAC_VER_40] = rtl_hw_start_8168g_1,
		[RTL_GIGA_MAC_VER_41] = rtl_hw_start_8168g_1,
		[RTL_GIGA_MAC_VER_42] = rtl_hw_start_8168g_2,
		[RTL_GIGA_MAC_VER_43] = rtl_hw_start_8168g_2,
		[RTL_GIGA_MAC_VER_44] = rtl_hw_start_8411_2,
		[RTL_GIGA_MAC_VER_45] = rtl_hw_start_8168h_1,
		[RTL_GIGA_MAC_VER_46] = rtl_hw_start_8168h_1,
		[RTL_GIGA_MAC_VER_47] = rtl_hw_start_8168h_1,
		[RTL_GIGA_MAC_VER_48] = rtl_hw_start_8168h_1,
		[RTL_GIGA_MAC_VER_49] = rtl_hw_start_8168ep_1,
		[RTL_GIGA_MAC_VER_50] = rtl_hw_start_8168ep_2,
		[RTL_GIGA_MAC_VER_51] = rtl_hw_start_8168ep_3,
		[RTL_GIGA_MAC_VER_52] = rtl_hw_start_8117,
		[RTL_GIGA_MAC_VER_53] = rtl_hw_start_8117,
		[RTL_GIGA_MAC_VER_60] = rtl_hw_start_8125a_1,
		[RTL_GIGA_MAC_VER_61] = rtl_hw_start_8125a_2,
		[RTL_GIGA_MAC_VER_63] = rtl_hw_start_8125b,
	पूर्ण;

	अगर (hw_configs[tp->mac_version])
		hw_configs[tp->mac_version](tp);
पूर्ण

अटल व्योम rtl_hw_start_8125(काष्ठा rtl8169_निजी *tp)
अणु
	पूर्णांक i;

	/* disable पूर्णांकerrupt coalescing */
	क्रम (i = 0xa00; i < 0xb00; i += 4)
		RTL_W32(tp, i, 0);

	rtl_hw_config(tp);
पूर्ण

अटल व्योम rtl_hw_start_8168(काष्ठा rtl8169_निजी *tp)
अणु
	अगर (rtl_is_8168evl_up(tp))
		RTL_W8(tp, MaxTxPacketSize, EarlySize);
	अन्यथा
		RTL_W8(tp, MaxTxPacketSize, TxPacketMax);

	rtl_hw_config(tp);

	/* disable पूर्णांकerrupt coalescing */
	RTL_W16(tp, IntrMitigate, 0x0000);
पूर्ण

अटल व्योम rtl_hw_start_8169(काष्ठा rtl8169_निजी *tp)
अणु
	RTL_W8(tp, EarlyTxThres, NoEarlyTx);

	tp->cp_cmd |= PCIMulRW;

	अगर (tp->mac_version == RTL_GIGA_MAC_VER_02 ||
	    tp->mac_version == RTL_GIGA_MAC_VER_03)
		tp->cp_cmd |= EnAnaPLL;

	RTL_W16(tp, CPlusCmd, tp->cp_cmd);

	rtl8169_set_magic_reg(tp);

	/* disable पूर्णांकerrupt coalescing */
	RTL_W16(tp, IntrMitigate, 0x0000);
पूर्ण

अटल व्योम rtl_hw_start(काष्ठा  rtl8169_निजी *tp)
अणु
	rtl_unlock_config_regs(tp);

	RTL_W16(tp, CPlusCmd, tp->cp_cmd);

	अगर (tp->mac_version <= RTL_GIGA_MAC_VER_06)
		rtl_hw_start_8169(tp);
	अन्यथा अगर (rtl_is_8125(tp))
		rtl_hw_start_8125(tp);
	अन्यथा
		rtl_hw_start_8168(tp);

	rtl_set_rx_max_size(tp);
	rtl_set_rx_tx_desc_रेजिस्टरs(tp);
	rtl_lock_config_regs(tp);

	rtl_jumbo_config(tp);

	/* Initially a 10 us delay. Turned it पूर्णांकo a PCI commit. - FR */
	rtl_pci_commit(tp);

	RTL_W8(tp, ChipCmd, CmdTxEnb | CmdRxEnb);
	rtl_init_rxcfg(tp);
	rtl_set_tx_config_रेजिस्टरs(tp);
	rtl_set_rx_config_features(tp, tp->dev->features);
	rtl_set_rx_mode(tp->dev);
	rtl_irq_enable(tp);
पूर्ण

अटल पूर्णांक rtl8169_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);

	dev->mtu = new_mtu;
	netdev_update_features(dev);
	rtl_jumbo_config(tp);

	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_61:
	हाल RTL_GIGA_MAC_VER_63:
		rtl8125_set_eee_txidle_समयr(tp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtl8169_mark_to_asic(काष्ठा RxDesc *desc)
अणु
	u32 eor = le32_to_cpu(desc->opts1) & RingEnd;

	desc->opts2 = 0;
	/* Force memory ग_लिखोs to complete beक्रमe releasing descriptor */
	dma_wmb();
	WRITE_ONCE(desc->opts1, cpu_to_le32(DescOwn | eor | R8169_RX_BUF_SIZE));
पूर्ण

अटल काष्ठा page *rtl8169_alloc_rx_data(काष्ठा rtl8169_निजी *tp,
					  काष्ठा RxDesc *desc)
अणु
	काष्ठा device *d = tp_to_dev(tp);
	पूर्णांक node = dev_to_node(d);
	dma_addr_t mapping;
	काष्ठा page *data;

	data = alloc_pages_node(node, GFP_KERNEL, get_order(R8169_RX_BUF_SIZE));
	अगर (!data)
		वापस शून्य;

	mapping = dma_map_page(d, data, 0, R8169_RX_BUF_SIZE, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(d, mapping))) अणु
		netdev_err(tp->dev, "Failed to map RX DMA!\n");
		__मुक्त_pages(data, get_order(R8169_RX_BUF_SIZE));
		वापस शून्य;
	पूर्ण

	desc->addr = cpu_to_le64(mapping);
	rtl8169_mark_to_asic(desc);

	वापस data;
पूर्ण

अटल व्योम rtl8169_rx_clear(काष्ठा rtl8169_निजी *tp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_RX_DESC && tp->Rx_databuff[i]; i++) अणु
		dma_unmap_page(tp_to_dev(tp),
			       le64_to_cpu(tp->RxDescArray[i].addr),
			       R8169_RX_BUF_SIZE, DMA_FROM_DEVICE);
		__मुक्त_pages(tp->Rx_databuff[i], get_order(R8169_RX_BUF_SIZE));
		tp->Rx_databuff[i] = शून्य;
		tp->RxDescArray[i].addr = 0;
		tp->RxDescArray[i].opts1 = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8169_rx_fill(काष्ठा rtl8169_निजी *tp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_RX_DESC; i++) अणु
		काष्ठा page *data;

		data = rtl8169_alloc_rx_data(tp, tp->RxDescArray + i);
		अगर (!data) अणु
			rtl8169_rx_clear(tp);
			वापस -ENOMEM;
		पूर्ण
		tp->Rx_databuff[i] = data;
	पूर्ण

	/* mark as last descriptor in the ring */
	tp->RxDescArray[NUM_RX_DESC - 1].opts1 |= cpu_to_le32(RingEnd);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8169_init_ring(काष्ठा rtl8169_निजी *tp)
अणु
	rtl8169_init_ring_indexes(tp);

	स_रखो(tp->tx_skb, 0, माप(tp->tx_skb));
	स_रखो(tp->Rx_databuff, 0, माप(tp->Rx_databuff));

	वापस rtl8169_rx_fill(tp);
पूर्ण

अटल व्योम rtl8169_unmap_tx_skb(काष्ठा rtl8169_निजी *tp, अचिन्हित पूर्णांक entry)
अणु
	काष्ठा ring_info *tx_skb = tp->tx_skb + entry;
	काष्ठा TxDesc *desc = tp->TxDescArray + entry;

	dma_unmap_single(tp_to_dev(tp), le64_to_cpu(desc->addr), tx_skb->len,
			 DMA_TO_DEVICE);
	स_रखो(desc, 0, माप(*desc));
	स_रखो(tx_skb, 0, माप(*tx_skb));
पूर्ण

अटल व्योम rtl8169_tx_clear_range(काष्ठा rtl8169_निजी *tp, u32 start,
				   अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		अचिन्हित पूर्णांक entry = (start + i) % NUM_TX_DESC;
		काष्ठा ring_info *tx_skb = tp->tx_skb + entry;
		अचिन्हित पूर्णांक len = tx_skb->len;

		अगर (len) अणु
			काष्ठा sk_buff *skb = tx_skb->skb;

			rtl8169_unmap_tx_skb(tp, entry);
			अगर (skb)
				dev_consume_skb_any(skb);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl8169_tx_clear(काष्ठा rtl8169_निजी *tp)
अणु
	rtl8169_tx_clear_range(tp, tp->dirty_tx, NUM_TX_DESC);
	netdev_reset_queue(tp->dev);
पूर्ण

अटल व्योम rtl8169_cleanup(काष्ठा rtl8169_निजी *tp, bool going_करोwn)
अणु
	napi_disable(&tp->napi);

	/* Give a racing hard_start_xmit a few cycles to complete. */
	synchronize_net();

	/* Disable पूर्णांकerrupts */
	rtl8169_irq_mask_and_ack(tp);

	rtl_rx_बंद(tp);

	अगर (going_करोwn && tp->dev->wol_enabled)
		जाओ no_reset;

	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_27:
	हाल RTL_GIGA_MAC_VER_28:
	हाल RTL_GIGA_MAC_VER_31:
		rtl_loop_रुको_low(tp, &rtl_npq_cond, 20, 2000);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_34 ... RTL_GIGA_MAC_VER_38:
		RTL_W8(tp, ChipCmd, RTL_R8(tp, ChipCmd) | StopReq);
		rtl_loop_रुको_high(tp, &rtl_txcfg_empty_cond, 100, 666);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_40 ... RTL_GIGA_MAC_VER_63:
		rtl_enable_rxdvgate(tp);
		fsleep(2000);
		अवरोध;
	शेष:
		RTL_W8(tp, ChipCmd, RTL_R8(tp, ChipCmd) | StopReq);
		fsleep(100);
		अवरोध;
	पूर्ण

	rtl_hw_reset(tp);
no_reset:
	rtl8169_tx_clear(tp);
	rtl8169_init_ring_indexes(tp);
पूर्ण

अटल व्योम rtl_reset_work(काष्ठा rtl8169_निजी *tp)
अणु
	पूर्णांक i;

	netअगर_stop_queue(tp->dev);

	rtl8169_cleanup(tp, false);

	क्रम (i = 0; i < NUM_RX_DESC; i++)
		rtl8169_mark_to_asic(tp->RxDescArray + i);

	napi_enable(&tp->napi);
	rtl_hw_start(tp);
पूर्ण

अटल व्योम rtl8169_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);

	rtl_schedule_task(tp, RTL_FLAG_TASK_RESET_PENDING);
पूर्ण

अटल पूर्णांक rtl8169_tx_map(काष्ठा rtl8169_निजी *tp, स्थिर u32 *opts, u32 len,
			  व्योम *addr, अचिन्हित पूर्णांक entry, bool desc_own)
अणु
	काष्ठा TxDesc *txd = tp->TxDescArray + entry;
	काष्ठा device *d = tp_to_dev(tp);
	dma_addr_t mapping;
	u32 opts1;
	पूर्णांक ret;

	mapping = dma_map_single(d, addr, len, DMA_TO_DEVICE);
	ret = dma_mapping_error(d, mapping);
	अगर (unlikely(ret)) अणु
		अगर (net_ratelimit())
			netdev_err(tp->dev, "Failed to map TX data!\n");
		वापस ret;
	पूर्ण

	txd->addr = cpu_to_le64(mapping);
	txd->opts2 = cpu_to_le32(opts[1]);

	opts1 = opts[0] | len;
	अगर (entry == NUM_TX_DESC - 1)
		opts1 |= RingEnd;
	अगर (desc_own)
		opts1 |= DescOwn;
	txd->opts1 = cpu_to_le32(opts1);

	tp->tx_skb[entry].len = len;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8169_xmit_frags(काष्ठा rtl8169_निजी *tp, काष्ठा sk_buff *skb,
			      स्थिर u32 *opts, अचिन्हित पूर्णांक entry)
अणु
	काष्ठा skb_shared_info *info = skb_shinfo(skb);
	अचिन्हित पूर्णांक cur_frag;

	क्रम (cur_frag = 0; cur_frag < info->nr_frags; cur_frag++) अणु
		स्थिर skb_frag_t *frag = info->frags + cur_frag;
		व्योम *addr = skb_frag_address(frag);
		u32 len = skb_frag_size(frag);

		entry = (entry + 1) % NUM_TX_DESC;

		अगर (unlikely(rtl8169_tx_map(tp, opts, len, addr, entry, true)))
			जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	rtl8169_tx_clear_range(tp, tp->cur_tx + 1, cur_frag);
	वापस -EIO;
पूर्ण

अटल bool rtl_skb_is_udp(काष्ठा sk_buff *skb)
अणु
	पूर्णांक no = skb_network_offset(skb);
	काष्ठा ipv6hdr *i6h, _i6h;
	काष्ठा iphdr *ih, _ih;

	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_IP):
		ih = skb_header_poपूर्णांकer(skb, no, माप(_ih), &_ih);
		वापस ih && ih->protocol == IPPROTO_UDP;
	हाल htons(ETH_P_IPV6):
		i6h = skb_header_poपूर्णांकer(skb, no, माप(_i6h), &_i6h);
		वापस i6h && i6h->nexthdr == IPPROTO_UDP;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

#घोषणा RTL_MIN_PATCH_LEN	47

/* see rtl8125_get_patch_pad_len() in r8125 venकरोr driver */
अटल अचिन्हित पूर्णांक rtl8125_quirk_udp_padto(काष्ठा rtl8169_निजी *tp,
					    काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक padto = 0, len = skb->len;

	अगर (rtl_is_8125(tp) && len < 128 + RTL_MIN_PATCH_LEN &&
	    rtl_skb_is_udp(skb) && skb_transport_header_was_set(skb)) अणु
		अचिन्हित पूर्णांक trans_data_len = skb_tail_poपूर्णांकer(skb) -
					      skb_transport_header(skb);

		अगर (trans_data_len >= दुरत्व(काष्ठा udphdr, len) &&
		    trans_data_len < RTL_MIN_PATCH_LEN) अणु
			u16 dest = ntohs(udp_hdr(skb)->dest);

			/* dest is a standard PTP port */
			अगर (dest == 319 || dest == 320)
				padto = len + RTL_MIN_PATCH_LEN - trans_data_len;
		पूर्ण

		अगर (trans_data_len < माप(काष्ठा udphdr))
			padto = max_t(अचिन्हित पूर्णांक, padto,
				      len + माप(काष्ठा udphdr) - trans_data_len);
	पूर्ण

	वापस padto;
पूर्ण

अटल अचिन्हित पूर्णांक rtl_quirk_packet_padto(काष्ठा rtl8169_निजी *tp,
					   काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक padto;

	padto = rtl8125_quirk_udp_padto(tp, skb);

	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_34:
	हाल RTL_GIGA_MAC_VER_60:
	हाल RTL_GIGA_MAC_VER_61:
	हाल RTL_GIGA_MAC_VER_63:
		padto = max_t(अचिन्हित पूर्णांक, padto, ETH_ZLEN);
	शेष:
		अवरोध;
	पूर्ण

	वापस padto;
पूर्ण

अटल व्योम rtl8169_tso_csum_v1(काष्ठा sk_buff *skb, u32 *opts)
अणु
	u32 mss = skb_shinfo(skb)->gso_size;

	अगर (mss) अणु
		opts[0] |= TD_LSO;
		opts[0] |= mss << TD0_MSS_SHIFT;
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		स्थिर काष्ठा iphdr *ip = ip_hdr(skb);

		अगर (ip->protocol == IPPROTO_TCP)
			opts[0] |= TD0_IP_CS | TD0_TCP_CS;
		अन्यथा अगर (ip->protocol == IPPROTO_UDP)
			opts[0] |= TD0_IP_CS | TD0_UDP_CS;
		अन्यथा
			WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल bool rtl8169_tso_csum_v2(काष्ठा rtl8169_निजी *tp,
				काष्ठा sk_buff *skb, u32 *opts)
अणु
	u32 transport_offset = (u32)skb_transport_offset(skb);
	काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	u32 mss = shinfo->gso_size;

	अगर (mss) अणु
		अगर (shinfo->gso_type & SKB_GSO_TCPV4) अणु
			opts[0] |= TD1_GTSENV4;
		पूर्ण अन्यथा अगर (shinfo->gso_type & SKB_GSO_TCPV6) अणु
			अगर (skb_cow_head(skb, 0))
				वापस false;

			tcp_v6_gso_csum_prep(skb);
			opts[0] |= TD1_GTSENV6;
		पूर्ण अन्यथा अणु
			WARN_ON_ONCE(1);
		पूर्ण

		opts[0] |= transport_offset << GTTCPHO_SHIFT;
		opts[1] |= mss << TD1_MSS_SHIFT;
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		u8 ip_protocol;

		चयन (vlan_get_protocol(skb)) अणु
		हाल htons(ETH_P_IP):
			opts[1] |= TD1_IPv4_CS;
			ip_protocol = ip_hdr(skb)->protocol;
			अवरोध;

		हाल htons(ETH_P_IPV6):
			opts[1] |= TD1_IPv6_CS;
			ip_protocol = ipv6_hdr(skb)->nexthdr;
			अवरोध;

		शेष:
			ip_protocol = IPPROTO_RAW;
			अवरोध;
		पूर्ण

		अगर (ip_protocol == IPPROTO_TCP)
			opts[1] |= TD1_TCP_CS;
		अन्यथा अगर (ip_protocol == IPPROTO_UDP)
			opts[1] |= TD1_UDP_CS;
		अन्यथा
			WARN_ON_ONCE(1);

		opts[1] |= transport_offset << TCPHO_SHIFT;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक padto = rtl_quirk_packet_padto(tp, skb);

		/* skb_padto would मुक्त the skb on error */
		वापस !__skb_put_padto(skb, padto, false);
	पूर्ण

	वापस true;
पूर्ण

अटल bool rtl_tx_slots_avail(काष्ठा rtl8169_निजी *tp)
अणु
	अचिन्हित पूर्णांक slots_avail = READ_ONCE(tp->dirty_tx) + NUM_TX_DESC
					- READ_ONCE(tp->cur_tx);

	/* A skbuff with nr_frags needs nr_frags+1 entries in the tx queue */
	वापस slots_avail > MAX_SKB_FRAGS;
पूर्ण

/* Versions RTL8102e and from RTL8168c onwards support csum_v2 */
अटल bool rtl_chip_supports_csum_v2(काष्ठा rtl8169_निजी *tp)
अणु
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_02 ... RTL_GIGA_MAC_VER_06:
	हाल RTL_GIGA_MAC_VER_10 ... RTL_GIGA_MAC_VER_17:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम rtl8169_करोorbell(काष्ठा rtl8169_निजी *tp)
अणु
	अगर (rtl_is_8125(tp))
		RTL_W16(tp, TxPoll_8125, BIT(0));
	अन्यथा
		RTL_W8(tp, TxPoll, NPQ);
पूर्ण

अटल netdev_tx_t rtl8169_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक frags = skb_shinfo(skb)->nr_frags;
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	अचिन्हित पूर्णांक entry = tp->cur_tx % NUM_TX_DESC;
	काष्ठा TxDesc *txd_first, *txd_last;
	bool stop_queue, करोor_bell;
	u32 opts[2];

	अगर (unlikely(!rtl_tx_slots_avail(tp))) अणु
		अगर (net_ratelimit())
			netdev_err(dev, "BUG! Tx Ring full when queue awake!\n");
		जाओ err_stop_0;
	पूर्ण

	opts[1] = rtl8169_tx_vlan_tag(skb);
	opts[0] = 0;

	अगर (!rtl_chip_supports_csum_v2(tp))
		rtl8169_tso_csum_v1(skb, opts);
	अन्यथा अगर (!rtl8169_tso_csum_v2(tp, skb, opts))
		जाओ err_dma_0;

	अगर (unlikely(rtl8169_tx_map(tp, opts, skb_headlen(skb), skb->data,
				    entry, false)))
		जाओ err_dma_0;

	txd_first = tp->TxDescArray + entry;

	अगर (frags) अणु
		अगर (rtl8169_xmit_frags(tp, skb, opts, entry))
			जाओ err_dma_1;
		entry = (entry + frags) % NUM_TX_DESC;
	पूर्ण

	txd_last = tp->TxDescArray + entry;
	txd_last->opts1 |= cpu_to_le32(LastFrag);
	tp->tx_skb[entry].skb = skb;

	skb_tx_बारtamp(skb);

	/* Force memory ग_लिखोs to complete beक्रमe releasing descriptor */
	dma_wmb();

	करोor_bell = __netdev_sent_queue(dev, skb->len, netdev_xmit_more());

	txd_first->opts1 |= cpu_to_le32(DescOwn | FirstFrag);

	/* rtl_tx needs to see descriptor changes beक्रमe updated tp->cur_tx */
	smp_wmb();

	WRITE_ONCE(tp->cur_tx, tp->cur_tx + frags + 1);

	stop_queue = !rtl_tx_slots_avail(tp);
	अगर (unlikely(stop_queue)) अणु
		/* Aव्योम wrongly optimistic queue wake-up: rtl_tx thपढ़ो must
		 * not miss a ring update when it notices a stopped queue.
		 */
		smp_wmb();
		netअगर_stop_queue(dev);
		/* Sync with rtl_tx:
		 * - publish queue status and cur_tx ring index (ग_लिखो barrier)
		 * - refresh dirty_tx ring index (पढ़ो barrier).
		 * May the current thपढ़ो have a pessimistic view of the ring
		 * status and क्रमget to wake up queue, a racing rtl_tx thपढ़ो
		 * can't.
		 */
		smp_mb__after_atomic();
		अगर (rtl_tx_slots_avail(tp))
			netअगर_start_queue(dev);
		करोor_bell = true;
	पूर्ण

	अगर (करोor_bell)
		rtl8169_करोorbell(tp);

	वापस NETDEV_TX_OK;

err_dma_1:
	rtl8169_unmap_tx_skb(tp, entry);
err_dma_0:
	dev_kमुक्त_skb_any(skb);
	dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;

err_stop_0:
	netअगर_stop_queue(dev);
	dev->stats.tx_dropped++;
	वापस NETDEV_TX_BUSY;
पूर्ण

अटल अचिन्हित पूर्णांक rtl_last_frag_len(काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_info *info = skb_shinfo(skb);
	अचिन्हित पूर्णांक nr_frags = info->nr_frags;

	अगर (!nr_frags)
		वापस अच_पूर्णांक_उच्च;

	वापस skb_frag_size(info->frags + nr_frags - 1);
पूर्ण

/* Workaround क्रम hw issues with TSO on RTL8168evl */
अटल netdev_features_t rtl8168evl_fix_tso(काष्ठा sk_buff *skb,
					    netdev_features_t features)
अणु
	/* IPv4 header has options field */
	अगर (vlan_get_protocol(skb) == htons(ETH_P_IP) &&
	    ip_hdrlen(skb) > माप(काष्ठा iphdr))
		features &= ~NETIF_F_ALL_TSO;

	/* IPv4 TCP header has options field */
	अन्यथा अगर (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4 &&
		 tcp_hdrlen(skb) > माप(काष्ठा tcphdr))
		features &= ~NETIF_F_ALL_TSO;

	अन्यथा अगर (rtl_last_frag_len(skb) <= 6)
		features &= ~NETIF_F_ALL_TSO;

	वापस features;
पूर्ण

अटल netdev_features_t rtl8169_features_check(काष्ठा sk_buff *skb,
						काष्ठा net_device *dev,
						netdev_features_t features)
अणु
	पूर्णांक transport_offset = skb_transport_offset(skb);
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);

	अगर (skb_is_gso(skb)) अणु
		अगर (tp->mac_version == RTL_GIGA_MAC_VER_34)
			features = rtl8168evl_fix_tso(skb, features);

		अगर (transport_offset > GTTCPHO_MAX &&
		    rtl_chip_supports_csum_v2(tp))
			features &= ~NETIF_F_ALL_TSO;
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		/* work around hw bug on some chip versions */
		अगर (skb->len < ETH_ZLEN)
			features &= ~NETIF_F_CSUM_MASK;

		अगर (rtl_quirk_packet_padto(tp, skb))
			features &= ~NETIF_F_CSUM_MASK;

		अगर (transport_offset > TCPHO_MAX &&
		    rtl_chip_supports_csum_v2(tp))
			features &= ~NETIF_F_CSUM_MASK;
	पूर्ण

	वापस vlan_features_check(skb, features);
पूर्ण

अटल व्योम rtl8169_pcierr_पूर्णांकerrupt(काष्ठा net_device *dev)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	काष्ठा pci_dev *pdev = tp->pci_dev;
	पूर्णांक pci_status_errs;
	u16 pci_cmd;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &pci_cmd);

	pci_status_errs = pci_status_get_and_clear_errors(pdev);

	अगर (net_ratelimit())
		netdev_err(dev, "PCI error (cmd = 0x%04x, status_errs = 0x%04x)\n",
			   pci_cmd, pci_status_errs);

	rtl_schedule_task(tp, RTL_FLAG_TASK_RESET_PENDING);
पूर्ण

अटल व्योम rtl_tx(काष्ठा net_device *dev, काष्ठा rtl8169_निजी *tp,
		   पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक dirty_tx, bytes_compl = 0, pkts_compl = 0;
	काष्ठा sk_buff *skb;

	dirty_tx = tp->dirty_tx;

	जबतक (READ_ONCE(tp->cur_tx) != dirty_tx) अणु
		अचिन्हित पूर्णांक entry = dirty_tx % NUM_TX_DESC;
		u32 status;

		status = le32_to_cpu(tp->TxDescArray[entry].opts1);
		अगर (status & DescOwn)
			अवरोध;

		skb = tp->tx_skb[entry].skb;
		rtl8169_unmap_tx_skb(tp, entry);

		अगर (skb) अणु
			pkts_compl++;
			bytes_compl += skb->len;
			napi_consume_skb(skb, budget);
		पूर्ण
		dirty_tx++;
	पूर्ण

	अगर (tp->dirty_tx != dirty_tx) अणु
		netdev_completed_queue(dev, pkts_compl, bytes_compl);
		dev_sw_netstats_tx_add(dev, pkts_compl, bytes_compl);

		/* Sync with rtl8169_start_xmit:
		 * - publish dirty_tx ring index (ग_लिखो barrier)
		 * - refresh cur_tx ring index and queue status (पढ़ो barrier)
		 * May the current thपढ़ो miss the stopped queue condition,
		 * a racing xmit thपढ़ो can only have a right view of the
		 * ring status.
		 */
		smp_store_mb(tp->dirty_tx, dirty_tx);
		अगर (netअगर_queue_stopped(dev) && rtl_tx_slots_avail(tp))
			netअगर_wake_queue(dev);
		/*
		 * 8168 hack: TxPoll requests are lost when the Tx packets are
		 * too बंद. Let's kick an extra TxPoll request when a burst
		 * of start_xmit activity is detected (अगर it is not detected,
		 * it is slow enough). -- FR
		 * If skb is शून्य then we come here again once a tx irq is
		 * triggered after the last fragment is marked transmitted.
		 */
		अगर (tp->cur_tx != dirty_tx && skb)
			rtl8169_करोorbell(tp);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक rtl8169_fragmented_frame(u32 status)
अणु
	वापस (status & (FirstFrag | LastFrag)) != (FirstFrag | LastFrag);
पूर्ण

अटल अंतरभूत व्योम rtl8169_rx_csum(काष्ठा sk_buff *skb, u32 opts1)
अणु
	u32 status = opts1 & (RxProtoMask | RxCSFailMask);

	अगर (status == RxProtoTCP || status == RxProtoUDP)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	अन्यथा
		skb_checksum_none_निश्चित(skb);
पूर्ण

अटल पूर्णांक rtl_rx(काष्ठा net_device *dev, काष्ठा rtl8169_निजी *tp, पूर्णांक budget)
अणु
	काष्ठा device *d = tp_to_dev(tp);
	पूर्णांक count;

	क्रम (count = 0; count < budget; count++, tp->cur_rx++) अणु
		अचिन्हित पूर्णांक pkt_size, entry = tp->cur_rx % NUM_RX_DESC;
		काष्ठा RxDesc *desc = tp->RxDescArray + entry;
		काष्ठा sk_buff *skb;
		स्थिर व्योम *rx_buf;
		dma_addr_t addr;
		u32 status;

		status = le32_to_cpu(desc->opts1);
		अगर (status & DescOwn)
			अवरोध;

		/* This barrier is needed to keep us from पढ़ोing
		 * any other fields out of the Rx descriptor until
		 * we know the status of DescOwn
		 */
		dma_rmb();

		अगर (unlikely(status & RxRES)) अणु
			अगर (net_ratelimit())
				netdev_warn(dev, "Rx ERROR. status = %08x\n",
					    status);
			dev->stats.rx_errors++;
			अगर (status & (RxRWT | RxRUNT))
				dev->stats.rx_length_errors++;
			अगर (status & RxCRC)
				dev->stats.rx_crc_errors++;

			अगर (!(dev->features & NETIF_F_RXALL))
				जाओ release_descriptor;
			अन्यथा अगर (status & RxRWT || !(status & (RxRUNT | RxCRC)))
				जाओ release_descriptor;
		पूर्ण

		pkt_size = status & GENMASK(13, 0);
		अगर (likely(!(dev->features & NETIF_F_RXFCS)))
			pkt_size -= ETH_FCS_LEN;

		/* The driver करोes not support incoming fragmented frames.
		 * They are seen as a symptom of over-mtu sized frames.
		 */
		अगर (unlikely(rtl8169_fragmented_frame(status))) अणु
			dev->stats.rx_dropped++;
			dev->stats.rx_length_errors++;
			जाओ release_descriptor;
		पूर्ण

		skb = napi_alloc_skb(&tp->napi, pkt_size);
		अगर (unlikely(!skb)) अणु
			dev->stats.rx_dropped++;
			जाओ release_descriptor;
		पूर्ण

		addr = le64_to_cpu(desc->addr);
		rx_buf = page_address(tp->Rx_databuff[entry]);

		dma_sync_single_क्रम_cpu(d, addr, pkt_size, DMA_FROM_DEVICE);
		prefetch(rx_buf);
		skb_copy_to_linear_data(skb, rx_buf, pkt_size);
		skb->tail += pkt_size;
		skb->len = pkt_size;
		dma_sync_single_क्रम_device(d, addr, pkt_size, DMA_FROM_DEVICE);

		rtl8169_rx_csum(skb, status);
		skb->protocol = eth_type_trans(skb, dev);

		rtl8169_rx_vlan_tag(desc, skb);

		अगर (skb->pkt_type == PACKET_MULTICAST)
			dev->stats.multicast++;

		napi_gro_receive(&tp->napi, skb);

		dev_sw_netstats_rx_add(dev, pkt_size);
release_descriptor:
		rtl8169_mark_to_asic(desc);
	पूर्ण

	वापस count;
पूर्ण

अटल irqवापस_t rtl8169_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा rtl8169_निजी *tp = dev_instance;
	u32 status = rtl_get_events(tp);

	अगर ((status & 0xffff) == 0xffff || !(status & tp->irq_mask))
		वापस IRQ_NONE;

	अगर (unlikely(status & SYSErr)) अणु
		rtl8169_pcierr_पूर्णांकerrupt(tp->dev);
		जाओ out;
	पूर्ण

	अगर (status & LinkChg)
		phy_mac_पूर्णांकerrupt(tp->phydev);

	अगर (unlikely(status & RxFIFOOver &&
	    tp->mac_version == RTL_GIGA_MAC_VER_11)) अणु
		netअगर_stop_queue(tp->dev);
		rtl_schedule_task(tp, RTL_FLAG_TASK_RESET_PENDING);
	पूर्ण

	अगर (napi_schedule_prep(&tp->napi)) अणु
		rtl_irq_disable(tp);
		__napi_schedule(&tp->napi);
	पूर्ण
out:
	rtl_ack_events(tp, status);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rtl_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl8169_निजी *tp =
		container_of(work, काष्ठा rtl8169_निजी, wk.work);

	rtnl_lock();

	अगर (!netअगर_running(tp->dev) ||
	    !test_bit(RTL_FLAG_TASK_ENABLED, tp->wk.flags))
		जाओ out_unlock;

	अगर (test_and_clear_bit(RTL_FLAG_TASK_RESET_PENDING, tp->wk.flags)) अणु
		rtl_reset_work(tp);
		netअगर_wake_queue(tp->dev);
	पूर्ण
out_unlock:
	rtnl_unlock();
पूर्ण

अटल पूर्णांक rtl8169_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा rtl8169_निजी *tp = container_of(napi, काष्ठा rtl8169_निजी, napi);
	काष्ठा net_device *dev = tp->dev;
	पूर्णांक work_करोne;

	rtl_tx(dev, tp, budget);

	work_करोne = rtl_rx(dev, tp, budget);

	अगर (work_करोne < budget && napi_complete_करोne(napi, work_करोne))
		rtl_irq_enable(tp);

	वापस work_करोne;
पूर्ण

अटल व्योम r8169_phylink_handler(काष्ठा net_device *ndev)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(ndev);

	अगर (netअगर_carrier_ok(ndev)) अणु
		rtl_link_chg_patch(tp);
		pm_request_resume(&tp->pci_dev->dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_idle(&tp->pci_dev->dev);
	पूर्ण

	अगर (net_ratelimit())
		phy_prपूर्णांक_status(tp->phydev);
पूर्ण

अटल पूर्णांक r8169_phy_connect(काष्ठा rtl8169_निजी *tp)
अणु
	काष्ठा phy_device *phydev = tp->phydev;
	phy_पूर्णांकerface_t phy_mode;
	पूर्णांक ret;

	phy_mode = tp->supports_gmii ? PHY_INTERFACE_MODE_GMII :
		   PHY_INTERFACE_MODE_MII;

	ret = phy_connect_direct(tp->dev, phydev, r8169_phylink_handler,
				 phy_mode);
	अगर (ret)
		वापस ret;

	अगर (!tp->supports_gmii)
		phy_set_max_speed(phydev, SPEED_100);

	phy_attached_info(phydev);

	वापस 0;
पूर्ण

अटल व्योम rtl8169_करोwn(काष्ठा rtl8169_निजी *tp)
अणु
	/* Clear all task flags */
	biपंचांगap_zero(tp->wk.flags, RTL_FLAG_MAX);

	phy_stop(tp->phydev);

	rtl8169_update_counters(tp);

	pci_clear_master(tp->pci_dev);
	rtl_pci_commit(tp);

	rtl8169_cleanup(tp, true);

	rtl_prepare_घातer_करोwn(tp);
पूर्ण

अटल व्योम rtl8169_up(काष्ठा rtl8169_निजी *tp)
अणु
	pci_set_master(tp->pci_dev);
	phy_init_hw(tp->phydev);
	phy_resume(tp->phydev);
	rtl8169_init_phy(tp);
	napi_enable(&tp->napi);
	set_bit(RTL_FLAG_TASK_ENABLED, tp->wk.flags);
	rtl_reset_work(tp);

	phy_start(tp->phydev);
पूर्ण

अटल पूर्णांक rtl8169_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	काष्ठा pci_dev *pdev = tp->pci_dev;

	pm_runसमय_get_sync(&pdev->dev);

	netअगर_stop_queue(dev);
	rtl8169_करोwn(tp);
	rtl8169_rx_clear(tp);

	cancel_work_sync(&tp->wk.work);

	मुक्त_irq(pci_irq_vector(pdev, 0), tp);

	phy_disconnect(tp->phydev);

	dma_मुक्त_coherent(&pdev->dev, R8169_RX_RING_BYTES, tp->RxDescArray,
			  tp->RxPhyAddr);
	dma_मुक्त_coherent(&pdev->dev, R8169_TX_RING_BYTES, tp->TxDescArray,
			  tp->TxPhyAddr);
	tp->TxDescArray = शून्य;
	tp->RxDescArray = शून्य;

	pm_runसमय_put_sync(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम rtl8169_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);

	rtl8169_पूर्णांकerrupt(pci_irq_vector(tp->pci_dev, 0), tp);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rtl_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	काष्ठा pci_dev *pdev = tp->pci_dev;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक retval = -ENOMEM;

	pm_runसमय_get_sync(&pdev->dev);

	/*
	 * Rx and Tx descriptors needs 256 bytes alignment.
	 * dma_alloc_coherent provides more.
	 */
	tp->TxDescArray = dma_alloc_coherent(&pdev->dev, R8169_TX_RING_BYTES,
					     &tp->TxPhyAddr, GFP_KERNEL);
	अगर (!tp->TxDescArray)
		जाओ out;

	tp->RxDescArray = dma_alloc_coherent(&pdev->dev, R8169_RX_RING_BYTES,
					     &tp->RxPhyAddr, GFP_KERNEL);
	अगर (!tp->RxDescArray)
		जाओ err_मुक्त_tx_0;

	retval = rtl8169_init_ring(tp);
	अगर (retval < 0)
		जाओ err_मुक्त_rx_1;

	rtl_request_firmware(tp);

	irqflags = pci_dev_msi_enabled(pdev) ? IRQF_NO_THREAD : IRQF_SHARED;
	retval = request_irq(pci_irq_vector(pdev, 0), rtl8169_पूर्णांकerrupt,
			     irqflags, dev->name, tp);
	अगर (retval < 0)
		जाओ err_release_fw_2;

	retval = r8169_phy_connect(tp);
	अगर (retval)
		जाओ err_मुक्त_irq;

	rtl8169_up(tp);
	rtl8169_init_counter_offsets(tp);
	netअगर_start_queue(dev);
out:
	pm_runसमय_put_sync(&pdev->dev);

	वापस retval;

err_मुक्त_irq:
	मुक्त_irq(pci_irq_vector(pdev, 0), tp);
err_release_fw_2:
	rtl_release_firmware(tp);
	rtl8169_rx_clear(tp);
err_मुक्त_rx_1:
	dma_मुक्त_coherent(&pdev->dev, R8169_RX_RING_BYTES, tp->RxDescArray,
			  tp->RxPhyAddr);
	tp->RxDescArray = शून्य;
err_मुक्त_tx_0:
	dma_मुक्त_coherent(&pdev->dev, R8169_TX_RING_BYTES, tp->TxDescArray,
			  tp->TxPhyAddr);
	tp->TxDescArray = शून्य;
	जाओ out;
पूर्ण

अटल व्योम
rtl8169_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा rtl8169_निजी *tp = netdev_priv(dev);
	काष्ठा pci_dev *pdev = tp->pci_dev;
	काष्ठा rtl8169_counters *counters = tp->counters;

	pm_runसमय_get_noresume(&pdev->dev);

	netdev_stats_to_stats64(stats, &dev->stats);
	dev_fetch_sw_netstats(stats, dev->tstats);

	/*
	 * Fetch additional counter values missing in stats collected by driver
	 * from tally counters.
	 */
	अगर (pm_runसमय_active(&pdev->dev))
		rtl8169_update_counters(tp);

	/*
	 * Subtract values fetched during initalization.
	 * See rtl8169_init_counter_offsets क्रम a description why we करो that.
	 */
	stats->tx_errors = le64_to_cpu(counters->tx_errors) -
		le64_to_cpu(tp->tc_offset.tx_errors);
	stats->collisions = le32_to_cpu(counters->tx_multi_collision) -
		le32_to_cpu(tp->tc_offset.tx_multi_collision);
	stats->tx_पातed_errors = le16_to_cpu(counters->tx_पातed) -
		le16_to_cpu(tp->tc_offset.tx_पातed);
	stats->rx_missed_errors = le16_to_cpu(counters->rx_missed) -
		le16_to_cpu(tp->tc_offset.rx_missed);

	pm_runसमय_put_noidle(&pdev->dev);
पूर्ण

अटल व्योम rtl8169_net_suspend(काष्ठा rtl8169_निजी *tp)
अणु
	netअगर_device_detach(tp->dev);

	अगर (netअगर_running(tp->dev))
		rtl8169_करोwn(tp);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक rtl8169_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rtl8169_निजी *tp = dev_get_drvdata(dev);

	rtl_rar_set(tp, tp->dev->dev_addr);
	__rtl8169_set_wol(tp, tp->saved_wolopts);

	अगर (tp->TxDescArray)
		rtl8169_up(tp);

	netअगर_device_attach(tp->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rtl8169_suspend(काष्ठा device *device)
अणु
	काष्ठा rtl8169_निजी *tp = dev_get_drvdata(device);

	rtnl_lock();
	rtl8169_net_suspend(tp);
	अगर (!device_may_wakeup(tp_to_dev(tp)))
		clk_disable_unprepare(tp->clk);
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rtl8169_resume(काष्ठा device *device)
अणु
	काष्ठा rtl8169_निजी *tp = dev_get_drvdata(device);

	अगर (!device_may_wakeup(tp_to_dev(tp)))
		clk_prepare_enable(tp->clk);

	/* Reportedly at least Asus X453MA truncates packets otherwise */
	अगर (tp->mac_version == RTL_GIGA_MAC_VER_37)
		rtl_init_rxcfg(tp);

	वापस rtl8169_runसमय_resume(device);
पूर्ण

अटल पूर्णांक rtl8169_runसमय_suspend(काष्ठा device *device)
अणु
	काष्ठा rtl8169_निजी *tp = dev_get_drvdata(device);

	अगर (!tp->TxDescArray) अणु
		netअगर_device_detach(tp->dev);
		वापस 0;
	पूर्ण

	rtnl_lock();
	__rtl8169_set_wol(tp, WAKE_PHY);
	rtl8169_net_suspend(tp);
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8169_runसमय_idle(काष्ठा device *device)
अणु
	काष्ठा rtl8169_निजी *tp = dev_get_drvdata(device);

	अगर (!netअगर_running(tp->dev) || !netअगर_carrier_ok(tp->dev))
		pm_schedule_suspend(device, 10000);

	वापस -EBUSY;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rtl8169_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rtl8169_suspend, rtl8169_resume)
	SET_RUNTIME_PM_OPS(rtl8169_runसमय_suspend, rtl8169_runसमय_resume,
			   rtl8169_runसमय_idle)
पूर्ण;

#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम rtl_wol_shutकरोwn_quirk(काष्ठा rtl8169_निजी *tp)
अणु
	/* WoL fails with 8168b when the receiver is disabled. */
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_11:
	हाल RTL_GIGA_MAC_VER_12:
	हाल RTL_GIGA_MAC_VER_17:
		pci_clear_master(tp->pci_dev);

		RTL_W8(tp, ChipCmd, CmdRxEnb);
		rtl_pci_commit(tp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtl_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा rtl8169_निजी *tp = pci_get_drvdata(pdev);

	rtnl_lock();
	rtl8169_net_suspend(tp);
	rtnl_unlock();

	/* Restore original MAC address */
	rtl_rar_set(tp, tp->dev->perm_addr);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		अगर (tp->saved_wolopts)
			rtl_wol_shutकरोwn_quirk(tp);

		pci_wake_from_d3(pdev, tp->saved_wolopts);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण

अटल व्योम rtl_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा rtl8169_निजी *tp = pci_get_drvdata(pdev);

	अगर (pci_dev_run_wake(pdev))
		pm_runसमय_get_noresume(&pdev->dev);

	unरेजिस्टर_netdev(tp->dev);

	अगर (tp->dash_type != RTL_DASH_NONE)
		rtl8168_driver_stop(tp);

	rtl_release_firmware(tp);

	/* restore original MAC address */
	rtl_rar_set(tp, tp->dev->perm_addr);
पूर्ण

अटल स्थिर काष्ठा net_device_ops rtl_netdev_ops = अणु
	.nकरो_खोलो		= rtl_खोलो,
	.nकरो_stop		= rtl8169_बंद,
	.nकरो_get_stats64	= rtl8169_get_stats64,
	.nकरो_start_xmit		= rtl8169_start_xmit,
	.nकरो_features_check	= rtl8169_features_check,
	.nकरो_tx_समयout		= rtl8169_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= rtl8169_change_mtu,
	.nकरो_fix_features	= rtl8169_fix_features,
	.nकरो_set_features	= rtl8169_set_features,
	.nकरो_set_mac_address	= rtl_set_mac_address,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_set_rx_mode	= rtl_set_rx_mode,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= rtl8169_netpoll,
#पूर्ण_अगर

पूर्ण;

अटल व्योम rtl_set_irq_mask(काष्ठा rtl8169_निजी *tp)
अणु
	tp->irq_mask = RxOK | RxErr | TxOK | TxErr | LinkChg;

	अगर (tp->mac_version <= RTL_GIGA_MAC_VER_06)
		tp->irq_mask |= SYSErr | RxOverflow | RxFIFOOver;
	अन्यथा अगर (tp->mac_version == RTL_GIGA_MAC_VER_11)
		/* special workaround needed */
		tp->irq_mask |= RxFIFOOver;
	अन्यथा
		tp->irq_mask |= RxOverflow;
पूर्ण

अटल पूर्णांक rtl_alloc_irq(काष्ठा rtl8169_निजी *tp)
अणु
	अचिन्हित पूर्णांक flags;

	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_02 ... RTL_GIGA_MAC_VER_06:
		rtl_unlock_config_regs(tp);
		RTL_W8(tp, Config2, RTL_R8(tp, Config2) & ~MSIEnable);
		rtl_lock_config_regs(tp);
		fallthrough;
	हाल RTL_GIGA_MAC_VER_07 ... RTL_GIGA_MAC_VER_17:
		flags = PCI_IRQ_LEGACY;
		अवरोध;
	शेष:
		flags = PCI_IRQ_ALL_TYPES;
		अवरोध;
	पूर्ण

	वापस pci_alloc_irq_vectors(tp->pci_dev, 1, 1, flags);
पूर्ण

अटल व्योम rtl_पढ़ो_mac_address(काष्ठा rtl8169_निजी *tp,
				 u8 mac_addr[ETH_ALEN])
अणु
	/* Get MAC address */
	अगर (rtl_is_8168evl_up(tp) && tp->mac_version != RTL_GIGA_MAC_VER_34) अणु
		u32 value;

		value = rtl_eri_पढ़ो(tp, 0xe0);
		put_unaligned_le32(value, mac_addr);
		value = rtl_eri_पढ़ो(tp, 0xe4);
		put_unaligned_le16(value, mac_addr + 4);
	पूर्ण अन्यथा अगर (rtl_is_8125(tp)) अणु
		rtl_पढ़ो_mac_from_reg(tp, mac_addr, MAC0_BKP);
	पूर्ण
पूर्ण

DECLARE_RTL_COND(rtl_link_list_पढ़ोy_cond)
अणु
	वापस RTL_R8(tp, MCU) & LINK_LIST_RDY;
पूर्ण

अटल व्योम r8168g_रुको_ll_share_fअगरo_पढ़ोy(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_loop_रुको_high(tp, &rtl_link_list_पढ़ोy_cond, 100, 42);
पूर्ण

अटल पूर्णांक r8169_mdio_पढ़ो_reg(काष्ठा mii_bus *mii_bus, पूर्णांक phyaddr, पूर्णांक phyreg)
अणु
	काष्ठा rtl8169_निजी *tp = mii_bus->priv;

	अगर (phyaddr > 0)
		वापस -ENODEV;

	वापस rtl_पढ़ोphy(tp, phyreg);
पूर्ण

अटल पूर्णांक r8169_mdio_ग_लिखो_reg(काष्ठा mii_bus *mii_bus, पूर्णांक phyaddr,
				पूर्णांक phyreg, u16 val)
अणु
	काष्ठा rtl8169_निजी *tp = mii_bus->priv;

	अगर (phyaddr > 0)
		वापस -ENODEV;

	rtl_ग_लिखोphy(tp, phyreg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक r8169_mdio_रेजिस्टर(काष्ठा rtl8169_निजी *tp)
अणु
	काष्ठा pci_dev *pdev = tp->pci_dev;
	काष्ठा mii_bus *new_bus;
	पूर्णांक ret;

	new_bus = devm_mdiobus_alloc(&pdev->dev);
	अगर (!new_bus)
		वापस -ENOMEM;

	new_bus->name = "r8169";
	new_bus->priv = tp;
	new_bus->parent = &pdev->dev;
	new_bus->irq[0] = PHY_MAC_INTERRUPT;
	snम_लिखो(new_bus->id, MII_BUS_ID_SIZE, "r8169-%x", pci_dev_id(pdev));

	new_bus->पढ़ो = r8169_mdio_पढ़ो_reg;
	new_bus->ग_लिखो = r8169_mdio_ग_लिखो_reg;

	ret = devm_mdiobus_रेजिस्टर(&pdev->dev, new_bus);
	अगर (ret)
		वापस ret;

	tp->phydev = mdiobus_get_phy(new_bus, 0);
	अगर (!tp->phydev) अणु
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (!tp->phydev->drv) अणु
		/* Most chip versions fail with the genphy driver.
		 * Thereक्रमe ensure that the dedicated PHY driver is loaded.
		 */
		dev_err(&pdev->dev, "no dedicated PHY driver found for PHY ID 0x%08x, maybe realtek.ko needs to be added to initramfs?\n",
			tp->phydev->phy_id);
		वापस -EUNATCH;
	पूर्ण

	tp->phydev->mac_managed_pm = 1;

	phy_support_asym_छोड़ो(tp->phydev);

	/* PHY will be woken up in rtl_खोलो() */
	phy_suspend(tp->phydev);

	वापस 0;
पूर्ण

अटल व्योम rtl_hw_init_8168g(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_enable_rxdvgate(tp);

	RTL_W8(tp, ChipCmd, RTL_R8(tp, ChipCmd) & ~(CmdTxEnb | CmdRxEnb));
	msleep(1);
	RTL_W8(tp, MCU, RTL_R8(tp, MCU) & ~NOW_IS_OOB);

	r8168_mac_ocp_modअगरy(tp, 0xe8de, BIT(14), 0);
	r8168g_रुको_ll_share_fअगरo_पढ़ोy(tp);

	r8168_mac_ocp_modअगरy(tp, 0xe8de, 0, BIT(15));
	r8168g_रुको_ll_share_fअगरo_पढ़ोy(tp);
पूर्ण

अटल व्योम rtl_hw_init_8125(काष्ठा rtl8169_निजी *tp)
अणु
	rtl_enable_rxdvgate(tp);

	RTL_W8(tp, ChipCmd, RTL_R8(tp, ChipCmd) & ~(CmdTxEnb | CmdRxEnb));
	msleep(1);
	RTL_W8(tp, MCU, RTL_R8(tp, MCU) & ~NOW_IS_OOB);

	r8168_mac_ocp_modअगरy(tp, 0xe8de, BIT(14), 0);
	r8168g_रुको_ll_share_fअगरo_पढ़ोy(tp);

	r8168_mac_ocp_ग_लिखो(tp, 0xc0aa, 0x07d0);
	r8168_mac_ocp_ग_लिखो(tp, 0xc0a6, 0x0150);
	r8168_mac_ocp_ग_लिखो(tp, 0xc01e, 0x5555);
	r8168g_रुको_ll_share_fअगरo_पढ़ोy(tp);
पूर्ण

अटल व्योम rtl_hw_initialize(काष्ठा rtl8169_निजी *tp)
अणु
	चयन (tp->mac_version) अणु
	हाल RTL_GIGA_MAC_VER_49 ... RTL_GIGA_MAC_VER_53:
		rtl8168ep_stop_cmac(tp);
		fallthrough;
	हाल RTL_GIGA_MAC_VER_40 ... RTL_GIGA_MAC_VER_48:
		rtl_hw_init_8168g(tp);
		अवरोध;
	हाल RTL_GIGA_MAC_VER_60 ... RTL_GIGA_MAC_VER_63:
		rtl_hw_init_8125(tp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rtl_jumbo_max(काष्ठा rtl8169_निजी *tp)
अणु
	/* Non-GBit versions करोn't support jumbo frames */
	अगर (!tp->supports_gmii)
		वापस 0;

	चयन (tp->mac_version) अणु
	/* RTL8169 */
	हाल RTL_GIGA_MAC_VER_02 ... RTL_GIGA_MAC_VER_06:
		वापस JUMBO_7K;
	/* RTL8168b */
	हाल RTL_GIGA_MAC_VER_11:
	हाल RTL_GIGA_MAC_VER_12:
	हाल RTL_GIGA_MAC_VER_17:
		वापस JUMBO_4K;
	/* RTL8168c */
	हाल RTL_GIGA_MAC_VER_18 ... RTL_GIGA_MAC_VER_24:
		वापस JUMBO_6K;
	शेष:
		वापस JUMBO_9K;
	पूर्ण
पूर्ण

अटल व्योम rtl_disable_clk(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक rtl_get_ether_clk(काष्ठा rtl8169_निजी *tp)
अणु
	काष्ठा device *d = tp_to_dev(tp);
	काष्ठा clk *clk;
	पूर्णांक rc;

	clk = devm_clk_get(d, "ether_clk");
	अगर (IS_ERR(clk)) अणु
		rc = PTR_ERR(clk);
		अगर (rc == -ENOENT)
			/* clk-core allows शून्य (क्रम suspend / resume) */
			rc = 0;
		अन्यथा
			dev_err_probe(d, rc, "failed to get clk\n");
	पूर्ण अन्यथा अणु
		tp->clk = clk;
		rc = clk_prepare_enable(clk);
		अगर (rc)
			dev_err(d, "failed to enable clk: %d\n", rc);
		अन्यथा
			rc = devm_add_action_or_reset(d, rtl_disable_clk, clk);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम rtl_init_mac_address(काष्ठा rtl8169_निजी *tp)
अणु
	काष्ठा net_device *dev = tp->dev;
	u8 *mac_addr = dev->dev_addr;
	पूर्णांक rc;

	rc = eth_platक्रमm_get_mac_address(tp_to_dev(tp), mac_addr);
	अगर (!rc)
		जाओ करोne;

	rtl_पढ़ो_mac_address(tp, mac_addr);
	अगर (is_valid_ether_addr(mac_addr))
		जाओ करोne;

	rtl_पढ़ो_mac_from_reg(tp, mac_addr, MAC0);
	अगर (is_valid_ether_addr(mac_addr))
		जाओ करोne;

	eth_hw_addr_अक्रमom(dev);
	dev_warn(tp_to_dev(tp), "can't read MAC address, setting random one\n");
करोne:
	rtl_rar_set(tp, mac_addr);
पूर्ण

अटल पूर्णांक rtl_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा rtl8169_निजी *tp;
	पूर्णांक jumbo_max, region, rc;
	क्रमागत mac_version chipset;
	काष्ठा net_device *dev;
	u16 xid;

	dev = devm_alloc_etherdev(&pdev->dev, माप (*tp));
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);
	dev->netdev_ops = &rtl_netdev_ops;
	tp = netdev_priv(dev);
	tp->dev = dev;
	tp->pci_dev = pdev;
	tp->supports_gmii = ent->driver_data == RTL_CFG_NO_GBIT ? 0 : 1;
	tp->eee_adv = -1;
	tp->ocp_base = OCP_STD_PHY_BASE;

	dev->tstats = devm_netdev_alloc_pcpu_stats(&pdev->dev,
						   काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	/* Get the *optional* बाह्यal "ether_clk" used on some boards */
	rc = rtl_get_ether_clk(tp);
	अगर (rc)
		वापस rc;

	/* Disable ASPM completely as that cause अक्रमom device stop working
	 * problems as well as full प्रणाली hangs क्रम some PCIe devices users.
	 */
	rc = pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S |
					  PCIE_LINK_STATE_L1);
	tp->aspm_manageable = !rc;

	/* enable device (incl. PCI PM wakeup and hotplug setup) */
	rc = pcim_enable_device(pdev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "enable failure\n");
		वापस rc;
	पूर्ण

	अगर (pcim_set_mwi(pdev) < 0)
		dev_info(&pdev->dev, "Mem-Wr-Inval unavailable\n");

	/* use first MMIO region */
	region = ffs(pci_select_bars(pdev, IORESOURCE_MEM)) - 1;
	अगर (region < 0) अणु
		dev_err(&pdev->dev, "no MMIO resource found\n");
		वापस -ENODEV;
	पूर्ण

	/* check क्रम weird/broken PCI region reporting */
	अगर (pci_resource_len(pdev, region) < R8169_REGS_SIZE) अणु
		dev_err(&pdev->dev, "Invalid PCI region size(s), aborting\n");
		वापस -ENODEV;
	पूर्ण

	rc = pcim_iomap_regions(pdev, BIT(region), MODULENAME);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "cannot remap MMIO, aborting\n");
		वापस rc;
	पूर्ण

	tp->mmio_addr = pcim_iomap_table(pdev)[region];

	xid = (RTL_R32(tp, TxConfig) >> 20) & 0xfcf;

	/* Identअगरy chip attached to board */
	chipset = rtl8169_get_mac_version(xid, tp->supports_gmii);
	अगर (chipset == RTL_GIGA_MAC_NONE) अणु
		dev_err(&pdev->dev, "unknown chip XID %03x, contact r8169 maintainers (see MAINTAINERS file)\n", xid);
		वापस -ENODEV;
	पूर्ण

	tp->mac_version = chipset;

	tp->dash_type = rtl_check_dash(tp);

	tp->cp_cmd = RTL_R16(tp, CPlusCmd) & CPCMD_MASK;

	अगर (माप(dma_addr_t) > 4 && tp->mac_version >= RTL_GIGA_MAC_VER_18 &&
	    !dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64)))
		dev->features |= NETIF_F_HIGHDMA;

	rtl_init_rxcfg(tp);

	rtl8169_irq_mask_and_ack(tp);

	rtl_hw_initialize(tp);

	rtl_hw_reset(tp);

	rc = rtl_alloc_irq(tp);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Can't allocate interrupt\n");
		वापस rc;
	पूर्ण

	INIT_WORK(&tp->wk.work, rtl_task);

	rtl_init_mac_address(tp);

	dev->ethtool_ops = &rtl8169_ethtool_ops;

	netअगर_napi_add(dev, &tp->napi, rtl8169_poll, NAPI_POLL_WEIGHT);

	dev->hw_features = NETIF_F_IP_CSUM | NETIF_F_RXCSUM |
			   NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;
	dev->vlan_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	/*
	 * Pretend we are using VLANs; This bypasses a nasty bug where
	 * Interrupts stop flowing on high load on 8110SCd controllers.
	 */
	अगर (tp->mac_version == RTL_GIGA_MAC_VER_05)
		/* Disallow toggling */
		dev->hw_features &= ~NETIF_F_HW_VLAN_CTAG_RX;

	अगर (rtl_chip_supports_csum_v2(tp))
		dev->hw_features |= NETIF_F_IPV6_CSUM;

	dev->features |= dev->hw_features;

	/* There has been a number of reports that using SG/TSO results in
	 * tx समयouts. However क्रम a lot of people SG/TSO works fine.
	 * Thereक्रमe disable both features by शेष, but allow users to
	 * enable them. Use at own risk!
	 */
	अगर (rtl_chip_supports_csum_v2(tp)) अणु
		dev->hw_features |= NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6;
		dev->gso_max_size = RTL_GSO_MAX_SIZE_V2;
		dev->gso_max_segs = RTL_GSO_MAX_SEGS_V2;
	पूर्ण अन्यथा अणु
		dev->hw_features |= NETIF_F_SG | NETIF_F_TSO;
		dev->gso_max_size = RTL_GSO_MAX_SIZE_V1;
		dev->gso_max_segs = RTL_GSO_MAX_SEGS_V1;
	पूर्ण

	dev->hw_features |= NETIF_F_RXALL;
	dev->hw_features |= NETIF_F_RXFCS;

	/* configure chip क्रम शेष features */
	rtl8169_set_features(dev, dev->features);

	rtl_set_d3_pll_करोwn(tp, true);

	jumbo_max = rtl_jumbo_max(tp);
	अगर (jumbo_max)
		dev->max_mtu = jumbo_max;

	rtl_set_irq_mask(tp);

	tp->fw_name = rtl_chip_infos[chipset].fw_name;

	tp->counters = dmam_alloc_coherent (&pdev->dev, माप(*tp->counters),
					    &tp->counters_phys_addr,
					    GFP_KERNEL);
	अगर (!tp->counters)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, tp);

	rc = r8169_mdio_रेजिस्टर(tp);
	अगर (rc)
		वापस rc;

	rc = रेजिस्टर_netdev(dev);
	अगर (rc)
		वापस rc;

	netdev_info(dev, "%s, %pM, XID %03x, IRQ %d\n",
		    rtl_chip_infos[chipset].name, dev->dev_addr, xid,
		    pci_irq_vector(pdev, 0));

	अगर (jumbo_max)
		netdev_info(dev, "jumbo features [frames: %d bytes, tx checksumming: %s]\n",
			    jumbo_max, tp->mac_version <= RTL_GIGA_MAC_VER_06 ?
			    "ok" : "ko");

	अगर (tp->dash_type != RTL_DASH_NONE) अणु
		netdev_info(dev, "DASH enabled\n");
		rtl8168_driver_start(tp);
	पूर्ण

	अगर (pci_dev_run_wake(pdev))
		pm_runसमय_put_sync(&pdev->dev);

	वापस 0;
पूर्ण

अटल काष्ठा pci_driver rtl8169_pci_driver = अणु
	.name		= MODULENAME,
	.id_table	= rtl8169_pci_tbl,
	.probe		= rtl_init_one,
	.हटाओ		= rtl_हटाओ_one,
	.shutकरोwn	= rtl_shutकरोwn,
	.driver.pm	= pm_ptr(&rtl8169_pm_ops),
पूर्ण;

module_pci_driver(rtl8169_pci_driver);
