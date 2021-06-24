<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * क्रमcedeth: Ethernet driver क्रम NVIDIA nForce media access controllers.
 *
 * Note: This driver is a cleanroom reimplementation based on reverse
 *      engineered करोcumentation written by Carl-Daniel Hailfinger
 *      and Andrew de Quincey.
 *
 * NVIDIA, nForce and other NVIDIA marks are trademarks or रेजिस्टरed
 * trademarks of NVIDIA Corporation in the United States and other
 * countries.
 *
 * Copyright (C) 2003,4,5 Manfred Spraul
 * Copyright (C) 2004 Andrew de Quincey (wol support)
 * Copyright (C) 2004 Carl-Daniel Hailfinger (invalid MAC handling, insane
 *		IRQ rate fixes, bigendian fixes, cleanups, verअगरication)
 * Copyright (c) 2004,2005,2006,2007,2008,2009 NVIDIA Corporation
 *
 * Known bugs:
 * We suspect that on some hardware no TX करोne पूर्णांकerrupts are generated.
 * This means recovery from netअगर_stop_queue only happens अगर the hw समयr
 * पूर्णांकerrupt fires (100 बार/second, configurable with NVREG_POLL_DEFAULT)
 * and the समयr is active in the IRQMask, or अगर a rx packet arrives by chance.
 * If your hardware reliably generates tx करोne पूर्णांकerrupts, then you can हटाओ
 * DEV_NEED_TIMERIRQ from the driver_data flags.
 * DEV_NEED_TIMERIRQ will not harm you on sane hardware, only generating a few
 * superfluous समयr पूर्णांकerrupts from the nic.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा FORCEDETH_VERSION		"0.64"
#घोषणा DRV_NAME			"forcedeth"

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/समयr.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mii.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>

#घोषणा TX_WORK_PER_LOOP  64
#घोषणा RX_WORK_PER_LOOP  64

/*
 * Hardware access:
 */

#घोषणा DEV_NEED_TIMERIRQ          0x0000001  /* set the समयr irq flag in the irq mask */
#घोषणा DEV_NEED_LINKTIMER         0x0000002  /* poll link settings. Relies on the समयr irq */
#घोषणा DEV_HAS_LARGEDESC          0x0000004  /* device supports jumbo frames and needs packet क्रमmat 2 */
#घोषणा DEV_HAS_HIGH_DMA           0x0000008  /* device supports 64bit dma */
#घोषणा DEV_HAS_CHECKSUM           0x0000010  /* device supports tx and rx checksum offloads */
#घोषणा DEV_HAS_VLAN               0x0000020  /* device supports vlan tagging and striping */
#घोषणा DEV_HAS_MSI                0x0000040  /* device supports MSI */
#घोषणा DEV_HAS_MSI_X              0x0000080  /* device supports MSI-X */
#घोषणा DEV_HAS_POWER_CNTRL        0x0000100  /* device supports घातer savings */
#घोषणा DEV_HAS_STATISTICS_V1      0x0000200  /* device supports hw statistics version 1 */
#घोषणा DEV_HAS_STATISTICS_V2      0x0000400  /* device supports hw statistics version 2 */
#घोषणा DEV_HAS_STATISTICS_V3      0x0000800  /* device supports hw statistics version 3 */
#घोषणा DEV_HAS_STATISTICS_V12     0x0000600  /* device supports hw statistics version 1 and 2 */
#घोषणा DEV_HAS_STATISTICS_V123    0x0000e00  /* device supports hw statistics version 1, 2, and 3 */
#घोषणा DEV_HAS_TEST_EXTENDED      0x0001000  /* device supports extended diagnostic test */
#घोषणा DEV_HAS_MGMT_UNIT          0x0002000  /* device supports management unit */
#घोषणा DEV_HAS_CORRECT_MACADDR    0x0004000  /* device supports correct mac address order */
#घोषणा DEV_HAS_COLLISION_FIX      0x0008000  /* device supports tx collision fix */
#घोषणा DEV_HAS_PAUSEFRAME_TX_V1   0x0010000  /* device supports tx छोड़ो frames version 1 */
#घोषणा DEV_HAS_PAUSEFRAME_TX_V2   0x0020000  /* device supports tx छोड़ो frames version 2 */
#घोषणा DEV_HAS_PAUSEFRAME_TX_V3   0x0040000  /* device supports tx छोड़ो frames version 3 */
#घोषणा DEV_NEED_TX_LIMIT          0x0080000  /* device needs to limit tx */
#घोषणा DEV_NEED_TX_LIMIT2         0x0180000  /* device needs to limit tx, expect क्रम some revs */
#घोषणा DEV_HAS_GEAR_MODE          0x0200000  /* device supports gear mode */
#घोषणा DEV_NEED_PHY_INIT_FIX      0x0400000  /* device needs specअगरic phy workaround */
#घोषणा DEV_NEED_LOW_POWER_FIX     0x0800000  /* device needs special घातer up workaround */
#घोषणा DEV_NEED_MSI_FIX           0x1000000  /* device needs msi workaround */

क्रमागत अणु
	NvRegIrqStatus = 0x000,
#घोषणा NVREG_IRQSTAT_MIIEVENT	0x040
#घोषणा NVREG_IRQSTAT_MASK		0x83ff
	NvRegIrqMask = 0x004,
#घोषणा NVREG_IRQ_RX_ERROR		0x0001
#घोषणा NVREG_IRQ_RX			0x0002
#घोषणा NVREG_IRQ_RX_NOBUF		0x0004
#घोषणा NVREG_IRQ_TX_ERR		0x0008
#घोषणा NVREG_IRQ_TX_OK			0x0010
#घोषणा NVREG_IRQ_TIMER			0x0020
#घोषणा NVREG_IRQ_LINK			0x0040
#घोषणा NVREG_IRQ_RX_FORCED		0x0080
#घोषणा NVREG_IRQ_TX_FORCED		0x0100
#घोषणा NVREG_IRQ_RECOVER_ERROR		0x8200
#घोषणा NVREG_IRQMASK_THROUGHPUT	0x00df
#घोषणा NVREG_IRQMASK_CPU		0x0060
#घोषणा NVREG_IRQ_TX_ALL		(NVREG_IRQ_TX_ERR|NVREG_IRQ_TX_OK|NVREG_IRQ_TX_FORCED)
#घोषणा NVREG_IRQ_RX_ALL		(NVREG_IRQ_RX_ERROR|NVREG_IRQ_RX|NVREG_IRQ_RX_NOBUF|NVREG_IRQ_RX_FORCED)
#घोषणा NVREG_IRQ_OTHER			(NVREG_IRQ_TIMER|NVREG_IRQ_LINK|NVREG_IRQ_RECOVER_ERROR)

	NvRegUnknownSetupReg6 = 0x008,
#घोषणा NVREG_UNKSETUP6_VAL		3

/*
 * NVREG_POLL_DEFAULT is the पूर्णांकerval length of the समयr source on the nic
 * NVREG_POLL_DEFAULT=97 would result in an पूर्णांकerval length of 1 ms
 */
	NvRegPollingInterval = 0x00c,
#घोषणा NVREG_POLL_DEFAULT_THROUGHPUT	65535 /* backup tx cleanup अगर loop max reached */
#घोषणा NVREG_POLL_DEFAULT_CPU	13
	NvRegMSIMap0 = 0x020,
	NvRegMSIMap1 = 0x024,
	NvRegMSIIrqMask = 0x030,
#घोषणा NVREG_MSI_VECTOR_0_ENABLED 0x01
	NvRegMisc1 = 0x080,
#घोषणा NVREG_MISC1_PAUSE_TX	0x01
#घोषणा NVREG_MISC1_HD		0x02
#घोषणा NVREG_MISC1_FORCE	0x3b0f3c

	NvRegMacReset = 0x34,
#घोषणा NVREG_MAC_RESET_ASSERT	0x0F3
	NvRegTransmitterControl = 0x084,
#घोषणा NVREG_XMITCTL_START	0x01
#घोषणा NVREG_XMITCTL_MGMT_ST	0x40000000
#घोषणा NVREG_XMITCTL_SYNC_MASK		0x000f0000
#घोषणा NVREG_XMITCTL_SYNC_NOT_READY	0x0
#घोषणा NVREG_XMITCTL_SYNC_PHY_INIT	0x00040000
#घोषणा NVREG_XMITCTL_MGMT_SEMA_MASK	0x00000f00
#घोषणा NVREG_XMITCTL_MGMT_SEMA_FREE	0x0
#घोषणा NVREG_XMITCTL_HOST_SEMA_MASK	0x0000f000
#घोषणा NVREG_XMITCTL_HOST_SEMA_ACQ	0x0000f000
#घोषणा NVREG_XMITCTL_HOST_LOADED	0x00004000
#घोषणा NVREG_XMITCTL_TX_PATH_EN	0x01000000
#घोषणा NVREG_XMITCTL_DATA_START	0x00100000
#घोषणा NVREG_XMITCTL_DATA_READY	0x00010000
#घोषणा NVREG_XMITCTL_DATA_ERROR	0x00020000
	NvRegTransmitterStatus = 0x088,
#घोषणा NVREG_XMITSTAT_BUSY	0x01

	NvRegPacketFilterFlags = 0x8c,
#घोषणा NVREG_PFF_PAUSE_RX	0x08
#घोषणा NVREG_PFF_ALWAYS	0x7F0000
#घोषणा NVREG_PFF_PROMISC	0x80
#घोषणा NVREG_PFF_MYADDR	0x20
#घोषणा NVREG_PFF_LOOPBACK	0x10

	NvRegOffloadConfig = 0x90,
#घोषणा NVREG_OFFLOAD_HOMEPHY	0x601
#घोषणा NVREG_OFFLOAD_NORMAL	RX_NIC_बफ_मानE
	NvRegReceiverControl = 0x094,
#घोषणा NVREG_RCVCTL_START	0x01
#घोषणा NVREG_RCVCTL_RX_PATH_EN	0x01000000
	NvRegReceiverStatus = 0x98,
#घोषणा NVREG_RCVSTAT_BUSY	0x01

	NvRegSlotTime = 0x9c,
#घोषणा NVREG_SLOTTIME_LEGBF_ENABLED	0x80000000
#घोषणा NVREG_SLOTTIME_10_100_FULL	0x00007f00
#घोषणा NVREG_SLOTTIME_1000_FULL	0x0003ff00
#घोषणा NVREG_SLOTTIME_HALF		0x0000ff00
#घोषणा NVREG_SLOTTIME_DEFAULT		0x00007f00
#घोषणा NVREG_SLOTTIME_MASK		0x000000ff

	NvRegTxDeferral = 0xA0,
#घोषणा NVREG_TX_DEFERRAL_DEFAULT		0x15050f
#घोषणा NVREG_TX_DEFERRAL_RGMII_10_100		0x16070f
#घोषणा NVREG_TX_DEFERRAL_RGMII_1000		0x14050f
#घोषणा NVREG_TX_DEFERRAL_RGMII_STRETCH_10	0x16190f
#घोषणा NVREG_TX_DEFERRAL_RGMII_STRETCH_100	0x16300f
#घोषणा NVREG_TX_DEFERRAL_MII_STRETCH		0x152000
	NvRegRxDeferral = 0xA4,
#घोषणा NVREG_RX_DEFERRAL_DEFAULT	0x16
	NvRegMacAddrA = 0xA8,
	NvRegMacAddrB = 0xAC,
	NvRegMulticastAddrA = 0xB0,
#घोषणा NVREG_MCASTADDRA_FORCE	0x01
	NvRegMulticastAddrB = 0xB4,
	NvRegMulticastMaskA = 0xB8,
#घोषणा NVREG_MCASTMASKA_NONE		0xffffffff
	NvRegMulticastMaskB = 0xBC,
#घोषणा NVREG_MCASTMASKB_NONE		0xffff

	NvRegPhyInterface = 0xC0,
#घोषणा PHY_RGMII		0x10000000
	NvRegBackOffControl = 0xC4,
#घोषणा NVREG_BKOFFCTRL_DEFAULT			0x70000000
#घोषणा NVREG_BKOFFCTRL_SEED_MASK		0x000003ff
#घोषणा NVREG_BKOFFCTRL_SELECT			24
#घोषणा NVREG_BKOFFCTRL_GEAR			12

	NvRegTxRingPhysAddr = 0x100,
	NvRegRxRingPhysAddr = 0x104,
	NvRegRingSizes = 0x108,
#घोषणा NVREG_RINGSZ_TXSHIFT 0
#घोषणा NVREG_RINGSZ_RXSHIFT 16
	NvRegTransmitPoll = 0x10c,
#घोषणा NVREG_TRANSMITPOLL_MAC_ADDR_REV	0x00008000
	NvRegLinkSpeed = 0x110,
#घोषणा NVREG_LINKSPEED_FORCE 0x10000
#घोषणा NVREG_LINKSPEED_10	1000
#घोषणा NVREG_LINKSPEED_100	100
#घोषणा NVREG_LINKSPEED_1000	50
#घोषणा NVREG_LINKSPEED_MASK	(0xFFF)
	NvRegUnknownSetupReg5 = 0x130,
#घोषणा NVREG_UNKSETUP5_BIT31	(1<<31)
	NvRegTxWatermark = 0x13c,
#घोषणा NVREG_TX_WM_DESC1_DEFAULT	0x0200010
#घोषणा NVREG_TX_WM_DESC2_3_DEFAULT	0x1e08000
#घोषणा NVREG_TX_WM_DESC2_3_1000	0xfe08000
	NvRegTxRxControl = 0x144,
#घोषणा NVREG_TXRXCTL_KICK	0x0001
#घोषणा NVREG_TXRXCTL_BIT1	0x0002
#घोषणा NVREG_TXRXCTL_BIT2	0x0004
#घोषणा NVREG_TXRXCTL_IDLE	0x0008
#घोषणा NVREG_TXRXCTL_RESET	0x0010
#घोषणा NVREG_TXRXCTL_RXCHECK	0x0400
#घोषणा NVREG_TXRXCTL_DESC_1	0
#घोषणा NVREG_TXRXCTL_DESC_2	0x002100
#घोषणा NVREG_TXRXCTL_DESC_3	0xc02200
#घोषणा NVREG_TXRXCTL_VLANSTRIP 0x00040
#घोषणा NVREG_TXRXCTL_VLANINS	0x00080
	NvRegTxRingPhysAddrHigh = 0x148,
	NvRegRxRingPhysAddrHigh = 0x14C,
	NvRegTxPauseFrame = 0x170,
#घोषणा NVREG_TX_PAUSEFRAME_DISABLE	0x0fff0080
#घोषणा NVREG_TX_PAUSEFRAME_ENABLE_V1	0x01800010
#घोषणा NVREG_TX_PAUSEFRAME_ENABLE_V2	0x056003f0
#घोषणा NVREG_TX_PAUSEFRAME_ENABLE_V3	0x09f00880
	NvRegTxPauseFrameLimit = 0x174,
#घोषणा NVREG_TX_PAUSEFRAMELIMIT_ENABLE	0x00010000
	NvRegMIIStatus = 0x180,
#घोषणा NVREG_MIISTAT_ERROR		0x0001
#घोषणा NVREG_MIISTAT_LINKCHANGE	0x0008
#घोषणा NVREG_MIISTAT_MASK_RW		0x0007
#घोषणा NVREG_MIISTAT_MASK_ALL		0x000f
	NvRegMIIMask = 0x184,
#घोषणा NVREG_MII_LINKCHANGE		0x0008

	NvRegAdapterControl = 0x188,
#घोषणा NVREG_ADAPTCTL_START	0x02
#घोषणा NVREG_ADAPTCTL_LINKUP	0x04
#घोषणा NVREG_ADAPTCTL_PHYVALID	0x40000
#घोषणा NVREG_ADAPTCTL_RUNNING	0x100000
#घोषणा NVREG_ADAPTCTL_PHYSHIFT	24
	NvRegMIISpeed = 0x18c,
#घोषणा NVREG_MIISPEED_BIT8	(1<<8)
#घोषणा NVREG_MIIDELAY	5
	NvRegMIIControl = 0x190,
#घोषणा NVREG_MIICTL_INUSE	0x08000
#घोषणा NVREG_MIICTL_WRITE	0x00400
#घोषणा NVREG_MIICTL_ADDRSHIFT	5
	NvRegMIIData = 0x194,
	NvRegTxUnicast = 0x1a0,
	NvRegTxMulticast = 0x1a4,
	NvRegTxBroadcast = 0x1a8,
	NvRegWakeUpFlags = 0x200,
#घोषणा NVREG_WAKEUPFLAGS_VAL		0x7770
#घोषणा NVREG_WAKEUPFLAGS_BUSYSHIFT	24
#घोषणा NVREG_WAKEUPFLAGS_ENABLESHIFT	16
#घोषणा NVREG_WAKEUPFLAGS_D3SHIFT	12
#घोषणा NVREG_WAKEUPFLAGS_D2SHIFT	8
#घोषणा NVREG_WAKEUPFLAGS_D1SHIFT	4
#घोषणा NVREG_WAKEUPFLAGS_D0SHIFT	0
#घोषणा NVREG_WAKEUPFLAGS_ACCEPT_MAGPAT		0x01
#घोषणा NVREG_WAKEUPFLAGS_ACCEPT_WAKEUPPAT	0x02
#घोषणा NVREG_WAKEUPFLAGS_ACCEPT_LINKCHANGE	0x04
#घोषणा NVREG_WAKEUPFLAGS_ENABLE	0x1111

	NvRegMgmtUnitGetVersion = 0x204,
#घोषणा NVREG_MGMTUNITGETVERSION	0x01
	NvRegMgmtUnitVersion = 0x208,
#घोषणा NVREG_MGMTUNITVERSION		0x08
	NvRegPowerCap = 0x268,
#घोषणा NVREG_POWERCAP_D3SUPP	(1<<30)
#घोषणा NVREG_POWERCAP_D2SUPP	(1<<26)
#घोषणा NVREG_POWERCAP_D1SUPP	(1<<25)
	NvRegPowerState = 0x26c,
#घोषणा NVREG_POWERSTATE_POWEREDUP	0x8000
#घोषणा NVREG_POWERSTATE_VALID		0x0100
#घोषणा NVREG_POWERSTATE_MASK		0x0003
#घोषणा NVREG_POWERSTATE_D0		0x0000
#घोषणा NVREG_POWERSTATE_D1		0x0001
#घोषणा NVREG_POWERSTATE_D2		0x0002
#घोषणा NVREG_POWERSTATE_D3		0x0003
	NvRegMgmtUnitControl = 0x278,
#घोषणा NVREG_MGMTUNITCONTROL_INUSE	0x20000
	NvRegTxCnt = 0x280,
	NvRegTxZeroReXmt = 0x284,
	NvRegTxOneReXmt = 0x288,
	NvRegTxManyReXmt = 0x28c,
	NvRegTxLateCol = 0x290,
	NvRegTxUnderflow = 0x294,
	NvRegTxLossCarrier = 0x298,
	NvRegTxExcessDef = 0x29c,
	NvRegTxRetryErr = 0x2a0,
	NvRegRxFrameErr = 0x2a4,
	NvRegRxExtraByte = 0x2a8,
	NvRegRxLateCol = 0x2ac,
	NvRegRxRunt = 0x2b0,
	NvRegRxFrameTooLong = 0x2b4,
	NvRegRxOverflow = 0x2b8,
	NvRegRxFCSErr = 0x2bc,
	NvRegRxFrameAlignErr = 0x2c0,
	NvRegRxLenErr = 0x2c4,
	NvRegRxUnicast = 0x2c8,
	NvRegRxMulticast = 0x2cc,
	NvRegRxBroadcast = 0x2d0,
	NvRegTxDef = 0x2d4,
	NvRegTxFrame = 0x2d8,
	NvRegRxCnt = 0x2dc,
	NvRegTxPause = 0x2e0,
	NvRegRxPause = 0x2e4,
	NvRegRxDropFrame = 0x2e8,
	NvRegVlanControl = 0x300,
#घोषणा NVREG_VLANCONTROL_ENABLE	0x2000
	NvRegMSIXMap0 = 0x3e0,
	NvRegMSIXMap1 = 0x3e4,
	NvRegMSIXIrqStatus = 0x3f0,

	NvRegPowerState2 = 0x600,
#घोषणा NVREG_POWERSTATE2_POWERUP_MASK		0x0F15
#घोषणा NVREG_POWERSTATE2_POWERUP_REV_A3	0x0001
#घोषणा NVREG_POWERSTATE2_PHY_RESET		0x0004
#घोषणा NVREG_POWERSTATE2_GATE_CLOCKS		0x0F00
पूर्ण;

/* Big endian: should work, but is untested */
काष्ठा ring_desc अणु
	__le32 buf;
	__le32 flaglen;
पूर्ण;

काष्ठा ring_desc_ex अणु
	__le32 bufhigh;
	__le32 buflow;
	__le32 txvlan;
	__le32 flaglen;
पूर्ण;

जोड़ ring_type अणु
	काष्ठा ring_desc *orig;
	काष्ठा ring_desc_ex *ex;
पूर्ण;

#घोषणा FLAG_MASK_V1 0xffff0000
#घोषणा FLAG_MASK_V2 0xffffc000
#घोषणा LEN_MASK_V1 (0xffffffff ^ FLAG_MASK_V1)
#घोषणा LEN_MASK_V2 (0xffffffff ^ FLAG_MASK_V2)

#घोषणा NV_TX_LASTPACKET	(1<<16)
#घोषणा NV_TX_RETRYERROR	(1<<19)
#घोषणा NV_TX_RETRYCOUNT_MASK	(0xF<<20)
#घोषणा NV_TX_FORCED_INTERRUPT	(1<<24)
#घोषणा NV_TX_DEFERRED		(1<<26)
#घोषणा NV_TX_CARRIERLOST	(1<<27)
#घोषणा NV_TX_LATECOLLISION	(1<<28)
#घोषणा NV_TX_UNDERFLOW		(1<<29)
#घोषणा NV_TX_ERROR		(1<<30)
#घोषणा NV_TX_VALID		(1<<31)

#घोषणा NV_TX2_LASTPACKET	(1<<29)
#घोषणा NV_TX2_RETRYERROR	(1<<18)
#घोषणा NV_TX2_RETRYCOUNT_MASK	(0xF<<19)
#घोषणा NV_TX2_FORCED_INTERRUPT	(1<<30)
#घोषणा NV_TX2_DEFERRED		(1<<25)
#घोषणा NV_TX2_CARRIERLOST	(1<<26)
#घोषणा NV_TX2_LATECOLLISION	(1<<27)
#घोषणा NV_TX2_UNDERFLOW	(1<<28)
/* error and valid are the same क्रम both */
#घोषणा NV_TX2_ERROR		(1<<30)
#घोषणा NV_TX2_VALID		(1<<31)
#घोषणा NV_TX2_TSO		(1<<28)
#घोषणा NV_TX2_TSO_SHIFT	14
#घोषणा NV_TX2_TSO_MAX_SHIFT	14
#घोषणा NV_TX2_TSO_MAX_SIZE	(1<<NV_TX2_TSO_MAX_SHIFT)
#घोषणा NV_TX2_CHECKSUM_L3	(1<<27)
#घोषणा NV_TX2_CHECKSUM_L4	(1<<26)

#घोषणा NV_TX3_VLAN_TAG_PRESENT (1<<18)

#घोषणा NV_RX_DESCRIPTORVALID	(1<<16)
#घोषणा NV_RX_MISSEDFRAME	(1<<17)
#घोषणा NV_RX_SUBTRACT1		(1<<18)
#घोषणा NV_RX_ERROR1		(1<<23)
#घोषणा NV_RX_ERROR2		(1<<24)
#घोषणा NV_RX_ERROR3		(1<<25)
#घोषणा NV_RX_ERROR4		(1<<26)
#घोषणा NV_RX_CRCERR		(1<<27)
#घोषणा NV_RX_OVERFLOW		(1<<28)
#घोषणा NV_RX_FRAMINGERR	(1<<29)
#घोषणा NV_RX_ERROR		(1<<30)
#घोषणा NV_RX_AVAIL		(1<<31)
#घोषणा NV_RX_ERROR_MASK	(NV_RX_ERROR1|NV_RX_ERROR2|NV_RX_ERROR3|NV_RX_ERROR4|NV_RX_CRCERR|NV_RX_OVERFLOW|NV_RX_FRAMINGERR)

#घोषणा NV_RX2_CHECKSUMMASK	(0x1C000000)
#घोषणा NV_RX2_CHECKSUM_IP	(0x10000000)
#घोषणा NV_RX2_CHECKSUM_IP_TCP	(0x14000000)
#घोषणा NV_RX2_CHECKSUM_IP_UDP	(0x18000000)
#घोषणा NV_RX2_DESCRIPTORVALID	(1<<29)
#घोषणा NV_RX2_SUBTRACT1	(1<<25)
#घोषणा NV_RX2_ERROR1		(1<<18)
#घोषणा NV_RX2_ERROR2		(1<<19)
#घोषणा NV_RX2_ERROR3		(1<<20)
#घोषणा NV_RX2_ERROR4		(1<<21)
#घोषणा NV_RX2_CRCERR		(1<<22)
#घोषणा NV_RX2_OVERFLOW		(1<<23)
#घोषणा NV_RX2_FRAMINGERR	(1<<24)
/* error and avail are the same क्रम both */
#घोषणा NV_RX2_ERROR		(1<<30)
#घोषणा NV_RX2_AVAIL		(1<<31)
#घोषणा NV_RX2_ERROR_MASK	(NV_RX2_ERROR1|NV_RX2_ERROR2|NV_RX2_ERROR3|NV_RX2_ERROR4|NV_RX2_CRCERR|NV_RX2_OVERFLOW|NV_RX2_FRAMINGERR)

#घोषणा NV_RX3_VLAN_TAG_PRESENT (1<<16)
#घोषणा NV_RX3_VLAN_TAG_MASK	(0x0000FFFF)

/* Miscellaneous hardware related defines: */
#घोषणा NV_PCI_REGSZ_VER1	0x270
#घोषणा NV_PCI_REGSZ_VER2	0x2d4
#घोषणा NV_PCI_REGSZ_VER3	0x604
#घोषणा NV_PCI_REGSZ_MAX	0x604

/* various समयout delays: all in usec */
#घोषणा NV_TXRX_RESET_DELAY	4
#घोषणा NV_TXSTOP_DELAY1	10
#घोषणा NV_TXSTOP_DELAY1MAX	500000
#घोषणा NV_TXSTOP_DELAY2	100
#घोषणा NV_RXSTOP_DELAY1	10
#घोषणा NV_RXSTOP_DELAY1MAX	500000
#घोषणा NV_RXSTOP_DELAY2	100
#घोषणा NV_SETUP5_DELAY		5
#घोषणा NV_SETUP5_DELAYMAX	50000
#घोषणा NV_POWERUP_DELAY	5
#घोषणा NV_POWERUP_DELAYMAX	5000
#घोषणा NV_MIIBUSY_DELAY	50
#घोषणा NV_MIIPHY_DELAY	10
#घोषणा NV_MIIPHY_DELAYMAX	10000
#घोषणा NV_MAC_RESET_DELAY	64

#घोषणा NV_WAKEUPPATTERNS	5
#घोषणा NV_WAKEUPMASKENTRIES	4

/* General driver शेषs */
#घोषणा NV_WATCHDOG_TIMEO	(5*HZ)

#घोषणा RX_RING_DEFAULT		512
#घोषणा TX_RING_DEFAULT		256
#घोषणा RX_RING_MIN		128
#घोषणा TX_RING_MIN		64
#घोषणा RING_MAX_DESC_VER_1	1024
#घोषणा RING_MAX_DESC_VER_2_3	16384

/* rx/tx mac addr + type + vlan + align + slack*/
#घोषणा NV_RX_HEADERS		(64)
/* even more slack. */
#घोषणा NV_RX_ALLOC_PAD		(64)

/* maximum mtu size */
#घोषणा NV_PKTLIMIT_1	ETH_DATA_LEN	/* hard limit not known */
#घोषणा NV_PKTLIMIT_2	9100	/* Actual limit according to NVidia: 9202 */

#घोषणा OOM_REFILL	(1+HZ/20)
#घोषणा POLL_WAIT	(1+HZ/100)
#घोषणा LINK_TIMEOUT	(3*HZ)
#घोषणा STATS_INTERVAL	(10*HZ)

/*
 * desc_ver values:
 * The nic supports three dअगरferent descriptor types:
 * - DESC_VER_1: Original
 * - DESC_VER_2: support क्रम jumbo frames.
 * - DESC_VER_3: 64-bit क्रमmat.
 */
#घोषणा DESC_VER_1	1
#घोषणा DESC_VER_2	2
#घोषणा DESC_VER_3	3

/* PHY defines */
#घोषणा PHY_OUI_MARVELL		0x5043
#घोषणा PHY_OUI_CICADA		0x03f1
#घोषणा PHY_OUI_VITESSE		0x01c1
#घोषणा PHY_OUI_REALTEK		0x0732
#घोषणा PHY_OUI_REALTEK2	0x0020
#घोषणा PHYID1_OUI_MASK	0x03ff
#घोषणा PHYID1_OUI_SHFT	6
#घोषणा PHYID2_OUI_MASK	0xfc00
#घोषणा PHYID2_OUI_SHFT	10
#घोषणा PHYID2_MODEL_MASK		0x03f0
#घोषणा PHY_MODEL_REALTEK_8211		0x0110
#घोषणा PHY_REV_MASK			0x0001
#घोषणा PHY_REV_REALTEK_8211B		0x0000
#घोषणा PHY_REV_REALTEK_8211C		0x0001
#घोषणा PHY_MODEL_REALTEK_8201		0x0200
#घोषणा PHY_MODEL_MARVELL_E3016		0x0220
#घोषणा PHY_MARVELL_E3016_INITMASK	0x0300
#घोषणा PHY_CICADA_INIT1	0x0f000
#घोषणा PHY_CICADA_INIT2	0x0e00
#घोषणा PHY_CICADA_INIT3	0x01000
#घोषणा PHY_CICADA_INIT4	0x0200
#घोषणा PHY_CICADA_INIT5	0x0004
#घोषणा PHY_CICADA_INIT6	0x02000
#घोषणा PHY_VITESSE_INIT_REG1	0x1f
#घोषणा PHY_VITESSE_INIT_REG2	0x10
#घोषणा PHY_VITESSE_INIT_REG3	0x11
#घोषणा PHY_VITESSE_INIT_REG4	0x12
#घोषणा PHY_VITESSE_INIT_MSK1	0xc
#घोषणा PHY_VITESSE_INIT_MSK2	0x0180
#घोषणा PHY_VITESSE_INIT1	0x52b5
#घोषणा PHY_VITESSE_INIT2	0xaf8a
#घोषणा PHY_VITESSE_INIT3	0x8
#घोषणा PHY_VITESSE_INIT4	0x8f8a
#घोषणा PHY_VITESSE_INIT5	0xaf86
#घोषणा PHY_VITESSE_INIT6	0x8f86
#घोषणा PHY_VITESSE_INIT7	0xaf82
#घोषणा PHY_VITESSE_INIT8	0x0100
#घोषणा PHY_VITESSE_INIT9	0x8f82
#घोषणा PHY_VITESSE_INIT10	0x0
#घोषणा PHY_REALTEK_INIT_REG1	0x1f
#घोषणा PHY_REALTEK_INIT_REG2	0x19
#घोषणा PHY_REALTEK_INIT_REG3	0x13
#घोषणा PHY_REALTEK_INIT_REG4	0x14
#घोषणा PHY_REALTEK_INIT_REG5	0x18
#घोषणा PHY_REALTEK_INIT_REG6	0x11
#घोषणा PHY_REALTEK_INIT_REG7	0x01
#घोषणा PHY_REALTEK_INIT1	0x0000
#घोषणा PHY_REALTEK_INIT2	0x8e00
#घोषणा PHY_REALTEK_INIT3	0x0001
#घोषणा PHY_REALTEK_INIT4	0xad17
#घोषणा PHY_REALTEK_INIT5	0xfb54
#घोषणा PHY_REALTEK_INIT6	0xf5c7
#घोषणा PHY_REALTEK_INIT7	0x1000
#घोषणा PHY_REALTEK_INIT8	0x0003
#घोषणा PHY_REALTEK_INIT9	0x0008
#घोषणा PHY_REALTEK_INIT10	0x0005
#घोषणा PHY_REALTEK_INIT11	0x0200
#घोषणा PHY_REALTEK_INIT_MSK1	0x0003

#घोषणा PHY_GIGABIT	0x0100

#घोषणा PHY_TIMEOUT	0x1
#घोषणा PHY_ERROR	0x2

#घोषणा PHY_100	0x1
#घोषणा PHY_1000	0x2
#घोषणा PHY_HALF	0x100

#घोषणा NV_PAUSEFRAME_RX_CAPABLE 0x0001
#घोषणा NV_PAUSEFRAME_TX_CAPABLE 0x0002
#घोषणा NV_PAUSEFRAME_RX_ENABLE  0x0004
#घोषणा NV_PAUSEFRAME_TX_ENABLE  0x0008
#घोषणा NV_PAUSEFRAME_RX_REQ     0x0010
#घोषणा NV_PAUSEFRAME_TX_REQ     0x0020
#घोषणा NV_PAUSEFRAME_AUTONEG    0x0040

/* MSI/MSI-X defines */
#घोषणा NV_MSI_X_MAX_VECTORS  8
#घोषणा NV_MSI_X_VECTORS_MASK 0x000f
#घोषणा NV_MSI_CAPABLE        0x0010
#घोषणा NV_MSI_X_CAPABLE      0x0020
#घोषणा NV_MSI_ENABLED        0x0040
#घोषणा NV_MSI_X_ENABLED      0x0080

#घोषणा NV_MSI_X_VECTOR_ALL   0x0
#घोषणा NV_MSI_X_VECTOR_RX    0x0
#घोषणा NV_MSI_X_VECTOR_TX    0x1
#घोषणा NV_MSI_X_VECTOR_OTHER 0x2

#घोषणा NV_MSI_PRIV_OFFSET 0x68
#घोषणा NV_MSI_PRIV_VALUE  0xffffffff

#घोषणा NV_RESTART_TX         0x1
#घोषणा NV_RESTART_RX         0x2

#घोषणा NV_TX_LIMIT_COUNT     16

#घोषणा NV_DYNAMIC_THRESHOLD        4
#घोषणा NV_DYNAMIC_MAX_QUIET_COUNT  2048

/* statistics */
काष्ठा nv_ethtool_str अणु
	अक्षर name[ETH_GSTRING_LEN];
पूर्ण;

अटल स्थिर काष्ठा nv_ethtool_str nv_estats_str[] = अणु
	अणु "tx_bytes" पूर्ण, /* includes Ethernet FCS CRC */
	अणु "tx_zero_rexmt" पूर्ण,
	अणु "tx_one_rexmt" पूर्ण,
	अणु "tx_many_rexmt" पूर्ण,
	अणु "tx_late_collision" पूर्ण,
	अणु "tx_fifo_errors" पूर्ण,
	अणु "tx_carrier_errors" पूर्ण,
	अणु "tx_excess_deferral" पूर्ण,
	अणु "tx_retry_error" पूर्ण,
	अणु "rx_frame_error" पूर्ण,
	अणु "rx_extra_byte" पूर्ण,
	अणु "rx_late_collision" पूर्ण,
	अणु "rx_runt" पूर्ण,
	अणु "rx_frame_too_long" पूर्ण,
	अणु "rx_over_errors" पूर्ण,
	अणु "rx_crc_errors" पूर्ण,
	अणु "rx_frame_align_error" पूर्ण,
	अणु "rx_length_error" पूर्ण,
	अणु "rx_unicast" पूर्ण,
	अणु "rx_multicast" पूर्ण,
	अणु "rx_broadcast" पूर्ण,
	अणु "rx_packets" पूर्ण,
	अणु "rx_errors_total" पूर्ण,
	अणु "tx_errors_total" पूर्ण,

	/* version 2 stats */
	अणु "tx_deferral" पूर्ण,
	अणु "tx_packets" पूर्ण,
	अणु "rx_bytes" पूर्ण, /* includes Ethernet FCS CRC */
	अणु "tx_pause" पूर्ण,
	अणु "rx_pause" पूर्ण,
	अणु "rx_drop_frame" पूर्ण,

	/* version 3 stats */
	अणु "tx_unicast" पूर्ण,
	अणु "tx_multicast" पूर्ण,
	अणु "tx_broadcast" पूर्ण
पूर्ण;

काष्ठा nv_ethtool_stats अणु
	u64 tx_bytes; /* should be अगरconfig->tx_bytes + 4*tx_packets */
	u64 tx_zero_rexmt;
	u64 tx_one_rexmt;
	u64 tx_many_rexmt;
	u64 tx_late_collision;
	u64 tx_fअगरo_errors;
	u64 tx_carrier_errors;
	u64 tx_excess_deferral;
	u64 tx_retry_error;
	u64 rx_frame_error;
	u64 rx_extra_byte;
	u64 rx_late_collision;
	u64 rx_runt;
	u64 rx_frame_too_दीर्घ;
	u64 rx_over_errors;
	u64 rx_crc_errors;
	u64 rx_frame_align_error;
	u64 rx_length_error;
	u64 rx_unicast;
	u64 rx_multicast;
	u64 rx_broadcast;
	u64 rx_packets; /* should be अगरconfig->rx_packets */
	u64 rx_errors_total;
	u64 tx_errors_total;

	/* version 2 stats */
	u64 tx_deferral;
	u64 tx_packets; /* should be अगरconfig->tx_packets */
	u64 rx_bytes;   /* should be अगरconfig->rx_bytes + 4*rx_packets */
	u64 tx_छोड़ो;
	u64 rx_छोड़ो;
	u64 rx_drop_frame;

	/* version 3 stats */
	u64 tx_unicast;
	u64 tx_multicast;
	u64 tx_broadcast;
पूर्ण;

#घोषणा NV_DEV_STATISTICS_V3_COUNT (माप(काष्ठा nv_ethtool_stats)/माप(u64))
#घोषणा NV_DEV_STATISTICS_V2_COUNT (NV_DEV_STATISTICS_V3_COUNT - 3)
#घोषणा NV_DEV_STATISTICS_V1_COUNT (NV_DEV_STATISTICS_V2_COUNT - 6)

/* diagnostics */
#घोषणा NV_TEST_COUNT_BASE 3
#घोषणा NV_TEST_COUNT_EXTENDED 4

अटल स्थिर काष्ठा nv_ethtool_str nv_etests_str[] = अणु
	अणु "link      (online/offline)" पूर्ण,
	अणु "register  (offline)       " पूर्ण,
	अणु "interrupt (offline)       " पूर्ण,
	अणु "loopback  (offline)       " पूर्ण
पूर्ण;

काष्ठा रेजिस्टर_test अणु
	__u32 reg;
	__u32 mask;
पूर्ण;

अटल स्थिर काष्ठा रेजिस्टर_test nv_रेजिस्टरs_test[] = अणु
	अणु NvRegUnknownSetupReg6, 0x01 पूर्ण,
	अणु NvRegMisc1, 0x03c पूर्ण,
	अणु NvRegOffloadConfig, 0x03ff पूर्ण,
	अणु NvRegMulticastAddrA, 0xffffffff पूर्ण,
	अणु NvRegTxWatermark, 0x0ff पूर्ण,
	अणु NvRegWakeUpFlags, 0x07777 पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

काष्ठा nv_skb_map अणु
	काष्ठा sk_buff *skb;
	dma_addr_t dma;
	अचिन्हित पूर्णांक dma_len:31;
	अचिन्हित पूर्णांक dma_single:1;
	काष्ठा ring_desc_ex *first_tx_desc;
	काष्ठा nv_skb_map *next_tx_ctx;
पूर्ण;

काष्ठा nv_txrx_stats अणु
	u64 stat_rx_packets;
	u64 stat_rx_bytes; /* not always available in HW */
	u64 stat_rx_missed_errors;
	u64 stat_rx_dropped;
	u64 stat_tx_packets; /* not always available in HW */
	u64 stat_tx_bytes;
	u64 stat_tx_dropped;
पूर्ण;

#घोषणा nv_txrx_stats_inc(member) \
		__this_cpu_inc(np->txrx_stats->member)
#घोषणा nv_txrx_stats_add(member, count) \
		__this_cpu_add(np->txrx_stats->member, (count))

/*
 * SMP locking:
 * All hardware access under netdev_priv(dev)->lock, except the perक्रमmance
 * critical parts:
 * - rx is (pseuकरो-) lockless: it relies on the single-thपढ़ोing provided
 *	by the arch code क्रम पूर्णांकerrupts.
 * - tx setup is lockless: it relies on netअगर_tx_lock. Actual submission
 *	needs netdev_priv(dev)->lock :-(
 * - set_multicast_list: preparation lockless, relies on netअगर_tx_lock.
 *
 * Hardware stats updates are रक्षित by hwstats_lock:
 * - updated by nv_करो_stats_poll (समयr). This is meant to aव्योम
 *   पूर्णांकeger wraparound in the NIC stats रेजिस्टरs, at low frequency
 *   (0.1 Hz)
 * - updated by nv_get_ethtool_stats + nv_get_stats64
 *
 * Software stats are accessed only through 64b synchronization poपूर्णांकs
 * and are not subject to other synchronization techniques (single
 * update thपढ़ो on the TX or RX paths).
 */

/* in dev: base, irq */
काष्ठा fe_priv अणु
	spinlock_t lock;

	काष्ठा net_device *dev;
	काष्ठा napi_काष्ठा napi;

	/* hardware stats are updated in syscall and समयr */
	spinlock_t hwstats_lock;
	काष्ठा nv_ethtool_stats estats;

	पूर्णांक in_shutकरोwn;
	u32 linkspeed;
	पूर्णांक duplex;
	पूर्णांक स्वतःneg;
	पूर्णांक fixed_mode;
	पूर्णांक phyaddr;
	पूर्णांक wolenabled;
	अचिन्हित पूर्णांक phy_oui;
	अचिन्हित पूर्णांक phy_model;
	अचिन्हित पूर्णांक phy_rev;
	u16 gigabit;
	पूर्णांक पूर्णांकr_test;
	पूर्णांक recover_error;
	पूर्णांक quiet_count;

	/* General data: RO fields */
	dma_addr_t ring_addr;
	काष्ठा pci_dev *pci_dev;
	u32 orig_mac[2];
	u32 events;
	u32 irqmask;
	u32 desc_ver;
	u32 txrxctl_bits;
	u32 vlanctl_bits;
	u32 driver_data;
	u32 device_id;
	u32 रेजिस्टर_size;
	u32 mac_in_use;
	पूर्णांक mgmt_version;
	पूर्णांक mgmt_sema;

	व्योम __iomem *base;

	/* rx specअगरic fields.
	 * Locking: Within irq hander or disable_irq+spin_lock(&np->lock);
	 */
	जोड़ ring_type get_rx, put_rx, last_rx;
	काष्ठा nv_skb_map *get_rx_ctx, *put_rx_ctx;
	काष्ठा nv_skb_map *last_rx_ctx;
	काष्ठा nv_skb_map *rx_skb;

	जोड़ ring_type rx_ring;
	अचिन्हित पूर्णांक rx_buf_sz;
	अचिन्हित पूर्णांक pkt_limit;
	काष्ठा समयr_list oom_kick;
	काष्ठा समयr_list nic_poll;
	काष्ठा समयr_list stats_poll;
	u32 nic_poll_irq;
	पूर्णांक rx_ring_size;

	/* RX software stats */
	काष्ठा u64_stats_sync swstats_rx_syncp;
	काष्ठा nv_txrx_stats __percpu *txrx_stats;

	/* media detection workaround.
	 * Locking: Within irq hander or disable_irq+spin_lock(&np->lock);
	 */
	पूर्णांक need_linkसमयr;
	अचिन्हित दीर्घ link_समयout;
	/*
	 * tx specअगरic fields.
	 */
	जोड़ ring_type get_tx, put_tx, last_tx;
	काष्ठा nv_skb_map *get_tx_ctx, *put_tx_ctx;
	काष्ठा nv_skb_map *last_tx_ctx;
	काष्ठा nv_skb_map *tx_skb;

	जोड़ ring_type tx_ring;
	u32 tx_flags;
	पूर्णांक tx_ring_size;
	पूर्णांक tx_limit;
	u32 tx_pkts_in_progress;
	काष्ठा nv_skb_map *tx_change_owner;
	काष्ठा nv_skb_map *tx_end_flip;
	पूर्णांक tx_stop;

	/* TX software stats */
	काष्ठा u64_stats_sync swstats_tx_syncp;

	/* msi/msi-x fields */
	u32 msi_flags;
	काष्ठा msix_entry msi_x_entry[NV_MSI_X_MAX_VECTORS];

	/* flow control */
	u32 छोड़ो_flags;

	/* घातer saved state */
	u32 saved_config_space[NV_PCI_REGSZ_MAX/4];

	/* क्रम dअगरferent msi-x irq type */
	अक्षर name_rx[IFNAMSIZ + 3];       /* -rx    */
	अक्षर name_tx[IFNAMSIZ + 3];       /* -tx    */
	अक्षर name_other[IFNAMSIZ + 6];    /* -other */
पूर्ण;

/*
 * Maximum number of loops until we assume that a bit in the irq mask
 * is stuck. Overridable with module param.
 */
अटल पूर्णांक max_पूर्णांकerrupt_work = 4;

/*
 * Optimization can be either throuput mode or cpu mode
 *
 * Throughput Mode: Every tx and rx packet will generate an पूर्णांकerrupt.
 * CPU Mode: Interrupts are controlled by a समयr.
 */
क्रमागत अणु
	NV_OPTIMIZATION_MODE_THROUGHPUT,
	NV_OPTIMIZATION_MODE_CPU,
	NV_OPTIMIZATION_MODE_DYNAMIC
पूर्ण;
अटल पूर्णांक optimization_mode = NV_OPTIMIZATION_MODE_DYNAMIC;

/*
 * Poll पूर्णांकerval क्रम समयr irq
 *
 * This पूर्णांकerval determines how frequent an पूर्णांकerrupt is generated.
 * The is value is determined by [(समय_in_micro_secs * 100) / (2^10)]
 * Min = 0, and Max = 65535
 */
अटल पूर्णांक poll_पूर्णांकerval = -1;

/*
 * MSI पूर्णांकerrupts
 */
क्रमागत अणु
	NV_MSI_INT_DISABLED,
	NV_MSI_INT_ENABLED
पूर्ण;
अटल पूर्णांक msi = NV_MSI_INT_ENABLED;

/*
 * MSIX पूर्णांकerrupts
 */
क्रमागत अणु
	NV_MSIX_INT_DISABLED,
	NV_MSIX_INT_ENABLED
पूर्ण;
अटल पूर्णांक msix = NV_MSIX_INT_ENABLED;

/*
 * DMA 64bit
 */
क्रमागत अणु
	NV_DMA_64BIT_DISABLED,
	NV_DMA_64BIT_ENABLED
पूर्ण;
अटल पूर्णांक dma_64bit = NV_DMA_64BIT_ENABLED;

/*
 * Debug output control क्रम tx_समयout
 */
अटल bool debug_tx_समयout = false;

/*
 * Crossover Detection
 * Realtek 8201 phy + some OEM boards करो not work properly.
 */
क्रमागत अणु
	NV_CROSSOVER_DETECTION_DISABLED,
	NV_CROSSOVER_DETECTION_ENABLED
पूर्ण;
अटल पूर्णांक phy_cross = NV_CROSSOVER_DETECTION_DISABLED;

/*
 * Power करोwn phy when पूर्णांकerface is करोwn (persists through reboot;
 * older Linux and other OSes may not घातer it up again)
 */
अटल पूर्णांक phy_घातer_करोwn;

अटल अंतरभूत काष्ठा fe_priv *get_nvpriv(काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

अटल अंतरभूत u8 __iomem *get_hwbase(काष्ठा net_device *dev)
अणु
	वापस ((काष्ठा fe_priv *)netdev_priv(dev))->base;
पूर्ण

अटल अंतरभूत व्योम pci_push(u8 __iomem *base)
अणु
	/* क्रमce out pending posted ग_लिखोs */
	पढ़ोl(base);
पूर्ण

अटल अंतरभूत u32 nv_descr_getlength(काष्ठा ring_desc *prd, u32 v)
अणु
	वापस le32_to_cpu(prd->flaglen)
		& ((v == DESC_VER_1) ? LEN_MASK_V1 : LEN_MASK_V2);
पूर्ण

अटल अंतरभूत u32 nv_descr_getlength_ex(काष्ठा ring_desc_ex *prd, u32 v)
अणु
	वापस le32_to_cpu(prd->flaglen) & LEN_MASK_V2;
पूर्ण

अटल bool nv_optimized(काष्ठा fe_priv *np)
अणु
	अगर (np->desc_ver == DESC_VER_1 || np->desc_ver == DESC_VER_2)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक reg_delay(काष्ठा net_device *dev, पूर्णांक offset, u32 mask, u32 target,
		     पूर्णांक delay, पूर्णांक delaymax)
अणु
	u8 __iomem *base = get_hwbase(dev);

	pci_push(base);
	करो अणु
		udelay(delay);
		delaymax -= delay;
		अगर (delaymax < 0)
			वापस 1;
	पूर्ण जबतक ((पढ़ोl(base + offset) & mask) != target);
	वापस 0;
पूर्ण

#घोषणा NV_SETUP_RX_RING 0x01
#घोषणा NV_SETUP_TX_RING 0x02

अटल अंतरभूत u32 dma_low(dma_addr_t addr)
अणु
	वापस addr;
पूर्ण

अटल अंतरभूत u32 dma_high(dma_addr_t addr)
अणु
	वापस addr>>31>>1;	/* 0 अगर 32bit, shअगरt करोwn by 32 अगर 64bit */
पूर्ण

अटल व्योम setup_hw_rings(काष्ठा net_device *dev, पूर्णांक rxtx_flags)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);
	u8 __iomem *base = get_hwbase(dev);

	अगर (!nv_optimized(np)) अणु
		अगर (rxtx_flags & NV_SETUP_RX_RING)
			ग_लिखोl(dma_low(np->ring_addr), base + NvRegRxRingPhysAddr);
		अगर (rxtx_flags & NV_SETUP_TX_RING)
			ग_लिखोl(dma_low(np->ring_addr + np->rx_ring_size*माप(काष्ठा ring_desc)), base + NvRegTxRingPhysAddr);
	पूर्ण अन्यथा अणु
		अगर (rxtx_flags & NV_SETUP_RX_RING) अणु
			ग_लिखोl(dma_low(np->ring_addr), base + NvRegRxRingPhysAddr);
			ग_लिखोl(dma_high(np->ring_addr), base + NvRegRxRingPhysAddrHigh);
		पूर्ण
		अगर (rxtx_flags & NV_SETUP_TX_RING) अणु
			ग_लिखोl(dma_low(np->ring_addr + np->rx_ring_size*माप(काष्ठा ring_desc_ex)), base + NvRegTxRingPhysAddr);
			ग_लिखोl(dma_high(np->ring_addr + np->rx_ring_size*माप(काष्ठा ring_desc_ex)), base + NvRegTxRingPhysAddrHigh);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम मुक्त_rings(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);

	अगर (!nv_optimized(np)) अणु
		अगर (np->rx_ring.orig)
			dma_मुक्त_coherent(&np->pci_dev->dev,
					  माप(काष्ठा ring_desc) *
					  (np->rx_ring_size +
					  np->tx_ring_size),
					  np->rx_ring.orig, np->ring_addr);
	पूर्ण अन्यथा अणु
		अगर (np->rx_ring.ex)
			dma_मुक्त_coherent(&np->pci_dev->dev,
					  माप(काष्ठा ring_desc_ex) *
					  (np->rx_ring_size +
					  np->tx_ring_size),
					  np->rx_ring.ex, np->ring_addr);
	पूर्ण
	kमुक्त(np->rx_skb);
	kमुक्त(np->tx_skb);
पूर्ण

अटल पूर्णांक using_multi_irqs(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);

	अगर (!(np->msi_flags & NV_MSI_X_ENABLED) ||
	    ((np->msi_flags & NV_MSI_X_VECTORS_MASK) == 0x1))
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल व्योम nv_txrx_gate(काष्ठा net_device *dev, bool gate)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 घातerstate;

	अगर (!np->mac_in_use &&
	    (np->driver_data & DEV_HAS_POWER_CNTRL)) अणु
		घातerstate = पढ़ोl(base + NvRegPowerState2);
		अगर (gate)
			घातerstate |= NVREG_POWERSTATE2_GATE_CLOCKS;
		अन्यथा
			घातerstate &= ~NVREG_POWERSTATE2_GATE_CLOCKS;
		ग_लिखोl(घातerstate, base + NvRegPowerState2);
	पूर्ण
पूर्ण

अटल व्योम nv_enable_irq(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);

	अगर (!using_multi_irqs(dev)) अणु
		अगर (np->msi_flags & NV_MSI_X_ENABLED)
			enable_irq(np->msi_x_entry[NV_MSI_X_VECTOR_ALL].vector);
		अन्यथा
			enable_irq(np->pci_dev->irq);
	पूर्ण अन्यथा अणु
		enable_irq(np->msi_x_entry[NV_MSI_X_VECTOR_RX].vector);
		enable_irq(np->msi_x_entry[NV_MSI_X_VECTOR_TX].vector);
		enable_irq(np->msi_x_entry[NV_MSI_X_VECTOR_OTHER].vector);
	पूर्ण
पूर्ण

अटल व्योम nv_disable_irq(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);

	अगर (!using_multi_irqs(dev)) अणु
		अगर (np->msi_flags & NV_MSI_X_ENABLED)
			disable_irq(np->msi_x_entry[NV_MSI_X_VECTOR_ALL].vector);
		अन्यथा
			disable_irq(np->pci_dev->irq);
	पूर्ण अन्यथा अणु
		disable_irq(np->msi_x_entry[NV_MSI_X_VECTOR_RX].vector);
		disable_irq(np->msi_x_entry[NV_MSI_X_VECTOR_TX].vector);
		disable_irq(np->msi_x_entry[NV_MSI_X_VECTOR_OTHER].vector);
	पूर्ण
पूर्ण

/* In MSIX mode, a ग_लिखो to irqmask behaves as XOR */
अटल व्योम nv_enable_hw_पूर्णांकerrupts(काष्ठा net_device *dev, u32 mask)
अणु
	u8 __iomem *base = get_hwbase(dev);

	ग_लिखोl(mask, base + NvRegIrqMask);
पूर्ण

अटल व्योम nv_disable_hw_पूर्णांकerrupts(काष्ठा net_device *dev, u32 mask)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);
	u8 __iomem *base = get_hwbase(dev);

	अगर (np->msi_flags & NV_MSI_X_ENABLED) अणु
		ग_लिखोl(mask, base + NvRegIrqMask);
	पूर्ण अन्यथा अणु
		अगर (np->msi_flags & NV_MSI_ENABLED)
			ग_लिखोl(0, base + NvRegMSIIrqMask);
		ग_लिखोl(0, base + NvRegIrqMask);
	पूर्ण
पूर्ण

अटल व्योम nv_napi_enable(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);

	napi_enable(&np->napi);
पूर्ण

अटल व्योम nv_napi_disable(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);

	napi_disable(&np->napi);
पूर्ण

#घोषणा MII_READ	(-1)
/* mii_rw: पढ़ो/ग_लिखो a रेजिस्टर on the PHY.
 *
 * Caller must guarantee serialization
 */
अटल पूर्णांक mii_rw(काष्ठा net_device *dev, पूर्णांक addr, पूर्णांक miireg, पूर्णांक value)
अणु
	u8 __iomem *base = get_hwbase(dev);
	u32 reg;
	पूर्णांक retval;

	ग_लिखोl(NVREG_MIISTAT_MASK_RW, base + NvRegMIIStatus);

	reg = पढ़ोl(base + NvRegMIIControl);
	अगर (reg & NVREG_MIICTL_INUSE) अणु
		ग_लिखोl(NVREG_MIICTL_INUSE, base + NvRegMIIControl);
		udelay(NV_MIIBUSY_DELAY);
	पूर्ण

	reg = (addr << NVREG_MIICTL_ADDRSHIFT) | miireg;
	अगर (value != MII_READ) अणु
		ग_लिखोl(value, base + NvRegMIIData);
		reg |= NVREG_MIICTL_WRITE;
	पूर्ण
	ग_लिखोl(reg, base + NvRegMIIControl);

	अगर (reg_delay(dev, NvRegMIIControl, NVREG_MIICTL_INUSE, 0,
			NV_MIIPHY_DELAY, NV_MIIPHY_DELAYMAX)) अणु
		retval = -1;
	पूर्ण अन्यथा अगर (value != MII_READ) अणु
		/* it was a ग_लिखो operation - fewer failures are detectable */
		retval = 0;
	पूर्ण अन्यथा अगर (पढ़ोl(base + NvRegMIIStatus) & NVREG_MIISTAT_ERROR) अणु
		retval = -1;
	पूर्ण अन्यथा अणु
		retval = पढ़ोl(base + NvRegMIIData);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक phy_reset(काष्ठा net_device *dev, u32 bmcr_setup)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u32 miicontrol;
	अचिन्हित पूर्णांक tries = 0;

	miicontrol = BMCR_RESET | bmcr_setup;
	अगर (mii_rw(dev, np->phyaddr, MII_BMCR, miicontrol))
		वापस -1;

	/* रुको क्रम 500ms */
	msleep(500);

	/* must रुको till reset is deनिश्चितed */
	जबतक (miicontrol & BMCR_RESET) अणु
		usleep_range(10000, 20000);
		miicontrol = mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ);
		/* FIXME: 100 tries seem excessive */
		अगर (tries++ > 100)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक init_realtek_8211b(काष्ठा net_device *dev, काष्ठा fe_priv *np)
अणु
	अटल स्थिर काष्ठा अणु
		पूर्णांक reg;
		पूर्णांक init;
	पूर्ण ri[] = अणु
		अणु PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT1 पूर्ण,
		अणु PHY_REALTEK_INIT_REG2, PHY_REALTEK_INIT2 पूर्ण,
		अणु PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT3 पूर्ण,
		अणु PHY_REALTEK_INIT_REG3, PHY_REALTEK_INIT4 पूर्ण,
		अणु PHY_REALTEK_INIT_REG4, PHY_REALTEK_INIT5 पूर्ण,
		अणु PHY_REALTEK_INIT_REG5, PHY_REALTEK_INIT6 पूर्ण,
		अणु PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT1 पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ri); i++) अणु
		अगर (mii_rw(dev, np->phyaddr, ri[i].reg, ri[i].init))
			वापस PHY_ERROR;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_realtek_8211c(काष्ठा net_device *dev, काष्ठा fe_priv *np)
अणु
	u32 reg;
	u8 __iomem *base = get_hwbase(dev);
	u32 घातerstate = पढ़ोl(base + NvRegPowerState2);

	/* need to perक्रमm hw phy reset */
	घातerstate |= NVREG_POWERSTATE2_PHY_RESET;
	ग_लिखोl(घातerstate, base + NvRegPowerState2);
	msleep(25);

	घातerstate &= ~NVREG_POWERSTATE2_PHY_RESET;
	ग_लिखोl(घातerstate, base + NvRegPowerState2);
	msleep(25);

	reg = mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG6, MII_READ);
	reg |= PHY_REALTEK_INIT9;
	अगर (mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG6, reg))
		वापस PHY_ERROR;
	अगर (mii_rw(dev, np->phyaddr,
		   PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT10))
		वापस PHY_ERROR;
	reg = mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG7, MII_READ);
	अगर (!(reg & PHY_REALTEK_INIT11)) अणु
		reg |= PHY_REALTEK_INIT11;
		अगर (mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG7, reg))
			वापस PHY_ERROR;
	पूर्ण
	अगर (mii_rw(dev, np->phyaddr,
		   PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT1))
		वापस PHY_ERROR;

	वापस 0;
पूर्ण

अटल पूर्णांक init_realtek_8201(काष्ठा net_device *dev, काष्ठा fe_priv *np)
अणु
	u32 phy_reserved;

	अगर (np->driver_data & DEV_NEED_PHY_INIT_FIX) अणु
		phy_reserved = mii_rw(dev, np->phyaddr,
				      PHY_REALTEK_INIT_REG6, MII_READ);
		phy_reserved |= PHY_REALTEK_INIT7;
		अगर (mii_rw(dev, np->phyaddr,
			   PHY_REALTEK_INIT_REG6, phy_reserved))
			वापस PHY_ERROR;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_realtek_8201_cross(काष्ठा net_device *dev, काष्ठा fe_priv *np)
अणु
	u32 phy_reserved;

	अगर (phy_cross == NV_CROSSOVER_DETECTION_DISABLED) अणु
		अगर (mii_rw(dev, np->phyaddr,
			   PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT3))
			वापस PHY_ERROR;
		phy_reserved = mii_rw(dev, np->phyaddr,
				      PHY_REALTEK_INIT_REG2, MII_READ);
		phy_reserved &= ~PHY_REALTEK_INIT_MSK1;
		phy_reserved |= PHY_REALTEK_INIT3;
		अगर (mii_rw(dev, np->phyaddr,
			   PHY_REALTEK_INIT_REG2, phy_reserved))
			वापस PHY_ERROR;
		अगर (mii_rw(dev, np->phyaddr,
			   PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT1))
			वापस PHY_ERROR;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_cicada(काष्ठा net_device *dev, काष्ठा fe_priv *np,
		       u32 phyपूर्णांकerface)
अणु
	u32 phy_reserved;

	अगर (phyपूर्णांकerface & PHY_RGMII) अणु
		phy_reserved = mii_rw(dev, np->phyaddr, MII_RESV1, MII_READ);
		phy_reserved &= ~(PHY_CICADA_INIT1 | PHY_CICADA_INIT2);
		phy_reserved |= (PHY_CICADA_INIT3 | PHY_CICADA_INIT4);
		अगर (mii_rw(dev, np->phyaddr, MII_RESV1, phy_reserved))
			वापस PHY_ERROR;
		phy_reserved = mii_rw(dev, np->phyaddr, MII_NCONFIG, MII_READ);
		phy_reserved |= PHY_CICADA_INIT5;
		अगर (mii_rw(dev, np->phyaddr, MII_NCONFIG, phy_reserved))
			वापस PHY_ERROR;
	पूर्ण
	phy_reserved = mii_rw(dev, np->phyaddr, MII_SREVISION, MII_READ);
	phy_reserved |= PHY_CICADA_INIT6;
	अगर (mii_rw(dev, np->phyaddr, MII_SREVISION, phy_reserved))
		वापस PHY_ERROR;

	वापस 0;
पूर्ण

अटल पूर्णांक init_vitesse(काष्ठा net_device *dev, काष्ठा fe_priv *np)
अणु
	u32 phy_reserved;

	अगर (mii_rw(dev, np->phyaddr,
		   PHY_VITESSE_INIT_REG1, PHY_VITESSE_INIT1))
		वापस PHY_ERROR;
	अगर (mii_rw(dev, np->phyaddr,
		   PHY_VITESSE_INIT_REG2, PHY_VITESSE_INIT2))
		वापस PHY_ERROR;
	phy_reserved = mii_rw(dev, np->phyaddr,
			      PHY_VITESSE_INIT_REG4, MII_READ);
	अगर (mii_rw(dev, np->phyaddr, PHY_VITESSE_INIT_REG4, phy_reserved))
		वापस PHY_ERROR;
	phy_reserved = mii_rw(dev, np->phyaddr,
			      PHY_VITESSE_INIT_REG3, MII_READ);
	phy_reserved &= ~PHY_VITESSE_INIT_MSK1;
	phy_reserved |= PHY_VITESSE_INIT3;
	अगर (mii_rw(dev, np->phyaddr, PHY_VITESSE_INIT_REG3, phy_reserved))
		वापस PHY_ERROR;
	अगर (mii_rw(dev, np->phyaddr,
		   PHY_VITESSE_INIT_REG2, PHY_VITESSE_INIT4))
		वापस PHY_ERROR;
	अगर (mii_rw(dev, np->phyaddr,
		   PHY_VITESSE_INIT_REG2, PHY_VITESSE_INIT5))
		वापस PHY_ERROR;
	phy_reserved = mii_rw(dev, np->phyaddr,
			      PHY_VITESSE_INIT_REG4, MII_READ);
	phy_reserved &= ~PHY_VITESSE_INIT_MSK1;
	phy_reserved |= PHY_VITESSE_INIT3;
	अगर (mii_rw(dev, np->phyaddr, PHY_VITESSE_INIT_REG4, phy_reserved))
		वापस PHY_ERROR;
	phy_reserved = mii_rw(dev, np->phyaddr,
			      PHY_VITESSE_INIT_REG3, MII_READ);
	अगर (mii_rw(dev, np->phyaddr, PHY_VITESSE_INIT_REG3, phy_reserved))
		वापस PHY_ERROR;
	अगर (mii_rw(dev, np->phyaddr,
		   PHY_VITESSE_INIT_REG2, PHY_VITESSE_INIT6))
		वापस PHY_ERROR;
	अगर (mii_rw(dev, np->phyaddr,
		   PHY_VITESSE_INIT_REG2, PHY_VITESSE_INIT7))
		वापस PHY_ERROR;
	phy_reserved = mii_rw(dev, np->phyaddr,
			      PHY_VITESSE_INIT_REG4, MII_READ);
	अगर (mii_rw(dev, np->phyaddr, PHY_VITESSE_INIT_REG4, phy_reserved))
		वापस PHY_ERROR;
	phy_reserved = mii_rw(dev, np->phyaddr,
			      PHY_VITESSE_INIT_REG3, MII_READ);
	phy_reserved &= ~PHY_VITESSE_INIT_MSK2;
	phy_reserved |= PHY_VITESSE_INIT8;
	अगर (mii_rw(dev, np->phyaddr, PHY_VITESSE_INIT_REG3, phy_reserved))
		वापस PHY_ERROR;
	अगर (mii_rw(dev, np->phyaddr,
		   PHY_VITESSE_INIT_REG2, PHY_VITESSE_INIT9))
		वापस PHY_ERROR;
	अगर (mii_rw(dev, np->phyaddr,
		   PHY_VITESSE_INIT_REG1, PHY_VITESSE_INIT10))
		वापस PHY_ERROR;

	वापस 0;
पूर्ण

अटल पूर्णांक phy_init(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 phyपूर्णांकerface;
	u32 mii_status, mii_control, mii_control_1000, reg;

	/* phy errata क्रम E3016 phy */
	अगर (np->phy_model == PHY_MODEL_MARVELL_E3016) अणु
		reg = mii_rw(dev, np->phyaddr, MII_NCONFIG, MII_READ);
		reg &= ~PHY_MARVELL_E3016_INITMASK;
		अगर (mii_rw(dev, np->phyaddr, MII_NCONFIG, reg)) अणु
			netdev_info(dev, "%s: phy write to errata reg failed\n",
				    pci_name(np->pci_dev));
			वापस PHY_ERROR;
		पूर्ण
	पूर्ण
	अगर (np->phy_oui == PHY_OUI_REALTEK) अणु
		अगर (np->phy_model == PHY_MODEL_REALTEK_8211 &&
		    np->phy_rev == PHY_REV_REALTEK_8211B) अणु
			अगर (init_realtek_8211b(dev, np)) अणु
				netdev_info(dev, "%s: phy init failed\n",
					    pci_name(np->pci_dev));
				वापस PHY_ERROR;
			पूर्ण
		पूर्ण अन्यथा अगर (np->phy_model == PHY_MODEL_REALTEK_8211 &&
			   np->phy_rev == PHY_REV_REALTEK_8211C) अणु
			अगर (init_realtek_8211c(dev, np)) अणु
				netdev_info(dev, "%s: phy init failed\n",
					    pci_name(np->pci_dev));
				वापस PHY_ERROR;
			पूर्ण
		पूर्ण अन्यथा अगर (np->phy_model == PHY_MODEL_REALTEK_8201) अणु
			अगर (init_realtek_8201(dev, np)) अणु
				netdev_info(dev, "%s: phy init failed\n",
					    pci_name(np->pci_dev));
				वापस PHY_ERROR;
			पूर्ण
		पूर्ण
	पूर्ण

	/* set advertise रेजिस्टर */
	reg = mii_rw(dev, np->phyaddr, MII_ADVERTISE, MII_READ);
	reg |= (ADVERTISE_10HALF | ADVERTISE_10FULL |
		ADVERTISE_100HALF | ADVERTISE_100FULL |
		ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP);
	अगर (mii_rw(dev, np->phyaddr, MII_ADVERTISE, reg)) अणु
		netdev_info(dev, "%s: phy write to advertise failed\n",
			    pci_name(np->pci_dev));
		वापस PHY_ERROR;
	पूर्ण

	/* get phy पूर्णांकerface type */
	phyपूर्णांकerface = पढ़ोl(base + NvRegPhyInterface);

	/* see अगर gigabit phy */
	mii_status = mii_rw(dev, np->phyaddr, MII_BMSR, MII_READ);
	अगर (mii_status & PHY_GIGABIT) अणु
		np->gigabit = PHY_GIGABIT;
		mii_control_1000 = mii_rw(dev, np->phyaddr,
					  MII_CTRL1000, MII_READ);
		mii_control_1000 &= ~ADVERTISE_1000HALF;
		अगर (phyपूर्णांकerface & PHY_RGMII)
			mii_control_1000 |= ADVERTISE_1000FULL;
		अन्यथा
			mii_control_1000 &= ~ADVERTISE_1000FULL;

		अगर (mii_rw(dev, np->phyaddr, MII_CTRL1000, mii_control_1000)) अणु
			netdev_info(dev, "%s: phy init failed\n",
				    pci_name(np->pci_dev));
			वापस PHY_ERROR;
		पूर्ण
	पूर्ण अन्यथा
		np->gigabit = 0;

	mii_control = mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ);
	mii_control |= BMCR_ANENABLE;

	अगर (np->phy_oui == PHY_OUI_REALTEK &&
	    np->phy_model == PHY_MODEL_REALTEK_8211 &&
	    np->phy_rev == PHY_REV_REALTEK_8211C) अणु
		/* start स्वतःneg since we alपढ़ोy perक्रमmed hw reset above */
		mii_control |= BMCR_ANRESTART;
		अगर (mii_rw(dev, np->phyaddr, MII_BMCR, mii_control)) अणु
			netdev_info(dev, "%s: phy init failed\n",
				    pci_name(np->pci_dev));
			वापस PHY_ERROR;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* reset the phy
		 * (certain phys need bmcr to be setup with reset)
		 */
		अगर (phy_reset(dev, mii_control)) अणु
			netdev_info(dev, "%s: phy reset failed\n",
				    pci_name(np->pci_dev));
			वापस PHY_ERROR;
		पूर्ण
	पूर्ण

	/* phy venकरोr specअगरic configuration */
	अगर (np->phy_oui == PHY_OUI_CICADA) अणु
		अगर (init_cicada(dev, np, phyपूर्णांकerface)) अणु
			netdev_info(dev, "%s: phy init failed\n",
				    pci_name(np->pci_dev));
			वापस PHY_ERROR;
		पूर्ण
	पूर्ण अन्यथा अगर (np->phy_oui == PHY_OUI_VITESSE) अणु
		अगर (init_vitesse(dev, np)) अणु
			netdev_info(dev, "%s: phy init failed\n",
				    pci_name(np->pci_dev));
			वापस PHY_ERROR;
		पूर्ण
	पूर्ण अन्यथा अगर (np->phy_oui == PHY_OUI_REALTEK) अणु
		अगर (np->phy_model == PHY_MODEL_REALTEK_8211 &&
		    np->phy_rev == PHY_REV_REALTEK_8211B) अणु
			/* reset could have cleared these out, set them back */
			अगर (init_realtek_8211b(dev, np)) अणु
				netdev_info(dev, "%s: phy init failed\n",
					    pci_name(np->pci_dev));
				वापस PHY_ERROR;
			पूर्ण
		पूर्ण अन्यथा अगर (np->phy_model == PHY_MODEL_REALTEK_8201) अणु
			अगर (init_realtek_8201(dev, np) ||
			    init_realtek_8201_cross(dev, np)) अणु
				netdev_info(dev, "%s: phy init failed\n",
					    pci_name(np->pci_dev));
				वापस PHY_ERROR;
			पूर्ण
		पूर्ण
	पूर्ण

	/* some phys clear out छोड़ो advertisement on reset, set it back */
	mii_rw(dev, np->phyaddr, MII_ADVERTISE, reg);

	/* restart स्वतः negotiation, घातer करोwn phy */
	mii_control = mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ);
	mii_control |= (BMCR_ANRESTART | BMCR_ANENABLE);
	अगर (phy_घातer_करोwn)
		mii_control |= BMCR_PDOWN;
	अगर (mii_rw(dev, np->phyaddr, MII_BMCR, mii_control))
		वापस PHY_ERROR;

	वापस 0;
पूर्ण

अटल व्योम nv_start_rx(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 rx_ctrl = पढ़ोl(base + NvRegReceiverControl);

	/* Alपढ़ोy running? Stop it. */
	अगर ((पढ़ोl(base + NvRegReceiverControl) & NVREG_RCVCTL_START) && !np->mac_in_use) अणु
		rx_ctrl &= ~NVREG_RCVCTL_START;
		ग_लिखोl(rx_ctrl, base + NvRegReceiverControl);
		pci_push(base);
	पूर्ण
	ग_लिखोl(np->linkspeed, base + NvRegLinkSpeed);
	pci_push(base);
	rx_ctrl |= NVREG_RCVCTL_START;
	अगर (np->mac_in_use)
		rx_ctrl &= ~NVREG_RCVCTL_RX_PATH_EN;
	ग_लिखोl(rx_ctrl, base + NvRegReceiverControl);
	pci_push(base);
पूर्ण

अटल व्योम nv_stop_rx(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 rx_ctrl = पढ़ोl(base + NvRegReceiverControl);

	अगर (!np->mac_in_use)
		rx_ctrl &= ~NVREG_RCVCTL_START;
	अन्यथा
		rx_ctrl |= NVREG_RCVCTL_RX_PATH_EN;
	ग_लिखोl(rx_ctrl, base + NvRegReceiverControl);
	अगर (reg_delay(dev, NvRegReceiverStatus, NVREG_RCVSTAT_BUSY, 0,
		      NV_RXSTOP_DELAY1, NV_RXSTOP_DELAY1MAX))
		netdev_info(dev, "%s: ReceiverStatus remained busy\n",
			    __func__);

	udelay(NV_RXSTOP_DELAY2);
	अगर (!np->mac_in_use)
		ग_लिखोl(0, base + NvRegLinkSpeed);
पूर्ण

अटल व्योम nv_start_tx(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 tx_ctrl = पढ़ोl(base + NvRegTransmitterControl);

	tx_ctrl |= NVREG_XMITCTL_START;
	अगर (np->mac_in_use)
		tx_ctrl &= ~NVREG_XMITCTL_TX_PATH_EN;
	ग_लिखोl(tx_ctrl, base + NvRegTransmitterControl);
	pci_push(base);
पूर्ण

अटल व्योम nv_stop_tx(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 tx_ctrl = पढ़ोl(base + NvRegTransmitterControl);

	अगर (!np->mac_in_use)
		tx_ctrl &= ~NVREG_XMITCTL_START;
	अन्यथा
		tx_ctrl |= NVREG_XMITCTL_TX_PATH_EN;
	ग_लिखोl(tx_ctrl, base + NvRegTransmitterControl);
	अगर (reg_delay(dev, NvRegTransmitterStatus, NVREG_XMITSTAT_BUSY, 0,
		      NV_TXSTOP_DELAY1, NV_TXSTOP_DELAY1MAX))
		netdev_info(dev, "%s: TransmitterStatus remained busy\n",
			    __func__);

	udelay(NV_TXSTOP_DELAY2);
	अगर (!np->mac_in_use)
		ग_लिखोl(पढ़ोl(base + NvRegTransmitPoll) & NVREG_TRANSMITPOLL_MAC_ADDR_REV,
		       base + NvRegTransmitPoll);
पूर्ण

अटल व्योम nv_start_rxtx(काष्ठा net_device *dev)
अणु
	nv_start_rx(dev);
	nv_start_tx(dev);
पूर्ण

अटल व्योम nv_stop_rxtx(काष्ठा net_device *dev)
अणु
	nv_stop_rx(dev);
	nv_stop_tx(dev);
पूर्ण

अटल व्योम nv_txrx_reset(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);

	ग_लिखोl(NVREG_TXRXCTL_BIT2 | NVREG_TXRXCTL_RESET | np->txrxctl_bits, base + NvRegTxRxControl);
	pci_push(base);
	udelay(NV_TXRX_RESET_DELAY);
	ग_लिखोl(NVREG_TXRXCTL_BIT2 | np->txrxctl_bits, base + NvRegTxRxControl);
	pci_push(base);
पूर्ण

अटल व्योम nv_mac_reset(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 temp1, temp2, temp3;

	ग_लिखोl(NVREG_TXRXCTL_BIT2 | NVREG_TXRXCTL_RESET | np->txrxctl_bits, base + NvRegTxRxControl);
	pci_push(base);

	/* save रेजिस्टरs since they will be cleared on reset */
	temp1 = पढ़ोl(base + NvRegMacAddrA);
	temp2 = पढ़ोl(base + NvRegMacAddrB);
	temp3 = पढ़ोl(base + NvRegTransmitPoll);

	ग_लिखोl(NVREG_MAC_RESET_ASSERT, base + NvRegMacReset);
	pci_push(base);
	udelay(NV_MAC_RESET_DELAY);
	ग_लिखोl(0, base + NvRegMacReset);
	pci_push(base);
	udelay(NV_MAC_RESET_DELAY);

	/* restore saved रेजिस्टरs */
	ग_लिखोl(temp1, base + NvRegMacAddrA);
	ग_लिखोl(temp2, base + NvRegMacAddrB);
	ग_लिखोl(temp3, base + NvRegTransmitPoll);

	ग_लिखोl(NVREG_TXRXCTL_BIT2 | np->txrxctl_bits, base + NvRegTxRxControl);
	pci_push(base);
पूर्ण

/* Caller must appropriately lock netdev_priv(dev)->hwstats_lock */
अटल व्योम nv_update_stats(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);

	lockdep_निश्चित_held(&np->hwstats_lock);

	/* query hardware */
	np->estats.tx_bytes += पढ़ोl(base + NvRegTxCnt);
	np->estats.tx_zero_rexmt += पढ़ोl(base + NvRegTxZeroReXmt);
	np->estats.tx_one_rexmt += पढ़ोl(base + NvRegTxOneReXmt);
	np->estats.tx_many_rexmt += पढ़ोl(base + NvRegTxManyReXmt);
	np->estats.tx_late_collision += पढ़ोl(base + NvRegTxLateCol);
	np->estats.tx_fअगरo_errors += पढ़ोl(base + NvRegTxUnderflow);
	np->estats.tx_carrier_errors += पढ़ोl(base + NvRegTxLossCarrier);
	np->estats.tx_excess_deferral += पढ़ोl(base + NvRegTxExcessDef);
	np->estats.tx_retry_error += पढ़ोl(base + NvRegTxRetryErr);
	np->estats.rx_frame_error += पढ़ोl(base + NvRegRxFrameErr);
	np->estats.rx_extra_byte += पढ़ोl(base + NvRegRxExtraByte);
	np->estats.rx_late_collision += पढ़ोl(base + NvRegRxLateCol);
	np->estats.rx_runt += पढ़ोl(base + NvRegRxRunt);
	np->estats.rx_frame_too_दीर्घ += पढ़ोl(base + NvRegRxFrameTooLong);
	np->estats.rx_over_errors += पढ़ोl(base + NvRegRxOverflow);
	np->estats.rx_crc_errors += पढ़ोl(base + NvRegRxFCSErr);
	np->estats.rx_frame_align_error += पढ़ोl(base + NvRegRxFrameAlignErr);
	np->estats.rx_length_error += पढ़ोl(base + NvRegRxLenErr);
	np->estats.rx_unicast += पढ़ोl(base + NvRegRxUnicast);
	np->estats.rx_multicast += पढ़ोl(base + NvRegRxMulticast);
	np->estats.rx_broadcast += पढ़ोl(base + NvRegRxBroadcast);
	np->estats.rx_packets =
		np->estats.rx_unicast +
		np->estats.rx_multicast +
		np->estats.rx_broadcast;
	np->estats.rx_errors_total =
		np->estats.rx_crc_errors +
		np->estats.rx_over_errors +
		np->estats.rx_frame_error +
		(np->estats.rx_frame_align_error - np->estats.rx_extra_byte) +
		np->estats.rx_late_collision +
		np->estats.rx_runt +
		np->estats.rx_frame_too_दीर्घ;
	np->estats.tx_errors_total =
		np->estats.tx_late_collision +
		np->estats.tx_fअगरo_errors +
		np->estats.tx_carrier_errors +
		np->estats.tx_excess_deferral +
		np->estats.tx_retry_error;

	अगर (np->driver_data & DEV_HAS_STATISTICS_V2) अणु
		np->estats.tx_deferral += पढ़ोl(base + NvRegTxDef);
		np->estats.tx_packets += पढ़ोl(base + NvRegTxFrame);
		np->estats.rx_bytes += पढ़ोl(base + NvRegRxCnt);
		np->estats.tx_छोड़ो += पढ़ोl(base + NvRegTxPause);
		np->estats.rx_छोड़ो += पढ़ोl(base + NvRegRxPause);
		np->estats.rx_drop_frame += पढ़ोl(base + NvRegRxDropFrame);
		np->estats.rx_errors_total += np->estats.rx_drop_frame;
	पूर्ण

	अगर (np->driver_data & DEV_HAS_STATISTICS_V3) अणु
		np->estats.tx_unicast += पढ़ोl(base + NvRegTxUnicast);
		np->estats.tx_multicast += पढ़ोl(base + NvRegTxMulticast);
		np->estats.tx_broadcast += पढ़ोl(base + NvRegTxBroadcast);
	पूर्ण
पूर्ण

अटल व्योम nv_get_stats(पूर्णांक cpu, काष्ठा fe_priv *np,
			 काष्ठा rtnl_link_stats64 *storage)
अणु
	काष्ठा nv_txrx_stats *src = per_cpu_ptr(np->txrx_stats, cpu);
	अचिन्हित पूर्णांक syncp_start;
	u64 rx_packets, rx_bytes, rx_dropped, rx_missed_errors;
	u64 tx_packets, tx_bytes, tx_dropped;

	करो अणु
		syncp_start = u64_stats_fetch_begin_irq(&np->swstats_rx_syncp);
		rx_packets       = src->stat_rx_packets;
		rx_bytes         = src->stat_rx_bytes;
		rx_dropped       = src->stat_rx_dropped;
		rx_missed_errors = src->stat_rx_missed_errors;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&np->swstats_rx_syncp, syncp_start));

	storage->rx_packets       += rx_packets;
	storage->rx_bytes         += rx_bytes;
	storage->rx_dropped       += rx_dropped;
	storage->rx_missed_errors += rx_missed_errors;

	करो अणु
		syncp_start = u64_stats_fetch_begin_irq(&np->swstats_tx_syncp);
		tx_packets  = src->stat_tx_packets;
		tx_bytes    = src->stat_tx_bytes;
		tx_dropped  = src->stat_tx_dropped;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&np->swstats_tx_syncp, syncp_start));

	storage->tx_packets += tx_packets;
	storage->tx_bytes   += tx_bytes;
	storage->tx_dropped += tx_dropped;
पूर्ण

/*
 * nv_get_stats64: dev->nकरो_get_stats64 function
 * Get latest stats value from the nic.
 * Called with पढ़ो_lock(&dev_base_lock) held क्रम पढ़ो -
 * only synchronized against unरेजिस्टर_netdevice.
 */
अटल व्योम
nv_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *storage)
	__acquires(&netdev_priv(dev)->hwstats_lock)
	__releases(&netdev_priv(dev)->hwstats_lock)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	पूर्णांक cpu;

	/*
	 * Note: because HW stats are not always available and क्रम
	 * consistency reasons, the following अगरconfig stats are
	 * managed by software: rx_bytes, tx_bytes, rx_packets and
	 * tx_packets. The related hardware stats reported by ethtool
	 * should be equivalent to these अगरconfig stats, with 4
	 * additional bytes per packet (Ethernet FCS CRC), except क्रम
	 * tx_packets when TSO kicks in.
	 */

	/* software stats */
	क्रम_each_online_cpu(cpu)
		nv_get_stats(cpu, np, storage);

	/* If the nic supports hw counters then retrieve latest values */
	अगर (np->driver_data & DEV_HAS_STATISTICS_V123) अणु
		spin_lock_bh(&np->hwstats_lock);

		nv_update_stats(dev);

		/* generic stats */
		storage->rx_errors = np->estats.rx_errors_total;
		storage->tx_errors = np->estats.tx_errors_total;

		/* meaningful only when NIC supports stats v3 */
		storage->multicast = np->estats.rx_multicast;

		/* detailed rx_errors */
		storage->rx_length_errors = np->estats.rx_length_error;
		storage->rx_over_errors   = np->estats.rx_over_errors;
		storage->rx_crc_errors    = np->estats.rx_crc_errors;
		storage->rx_frame_errors  = np->estats.rx_frame_align_error;
		storage->rx_fअगरo_errors   = np->estats.rx_drop_frame;

		/* detailed tx_errors */
		storage->tx_carrier_errors = np->estats.tx_carrier_errors;
		storage->tx_fअगरo_errors    = np->estats.tx_fअगरo_errors;

		spin_unlock_bh(&np->hwstats_lock);
	पूर्ण
पूर्ण

/*
 * nv_alloc_rx: fill rx ring entries.
 * Return 1 अगर the allocations क्रम the skbs failed and the
 * rx engine is without Available descriptors
 */
अटल पूर्णांक nv_alloc_rx(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	काष्ठा ring_desc *less_rx;

	less_rx = np->get_rx.orig;
	अगर (less_rx-- == np->rx_ring.orig)
		less_rx = np->last_rx.orig;

	जबतक (np->put_rx.orig != less_rx) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, np->rx_buf_sz + NV_RX_ALLOC_PAD);
		अगर (likely(skb)) अणु
			np->put_rx_ctx->skb = skb;
			np->put_rx_ctx->dma = dma_map_single(&np->pci_dev->dev,
							     skb->data,
							     skb_tailroom(skb),
							     DMA_FROM_DEVICE);
			अगर (unlikely(dma_mapping_error(&np->pci_dev->dev,
						       np->put_rx_ctx->dma))) अणु
				kमुक्त_skb(skb);
				जाओ packet_dropped;
			पूर्ण
			np->put_rx_ctx->dma_len = skb_tailroom(skb);
			np->put_rx.orig->buf = cpu_to_le32(np->put_rx_ctx->dma);
			wmb();
			np->put_rx.orig->flaglen = cpu_to_le32(np->rx_buf_sz | NV_RX_AVAIL);
			अगर (unlikely(np->put_rx.orig++ == np->last_rx.orig))
				np->put_rx.orig = np->rx_ring.orig;
			अगर (unlikely(np->put_rx_ctx++ == np->last_rx_ctx))
				np->put_rx_ctx = np->rx_skb;
		पूर्ण अन्यथा अणु
packet_dropped:
			u64_stats_update_begin(&np->swstats_rx_syncp);
			nv_txrx_stats_inc(stat_rx_dropped);
			u64_stats_update_end(&np->swstats_rx_syncp);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nv_alloc_rx_optimized(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	काष्ठा ring_desc_ex *less_rx;

	less_rx = np->get_rx.ex;
	अगर (less_rx-- == np->rx_ring.ex)
		less_rx = np->last_rx.ex;

	जबतक (np->put_rx.ex != less_rx) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, np->rx_buf_sz + NV_RX_ALLOC_PAD);
		अगर (likely(skb)) अणु
			np->put_rx_ctx->skb = skb;
			np->put_rx_ctx->dma = dma_map_single(&np->pci_dev->dev,
							     skb->data,
							     skb_tailroom(skb),
							     DMA_FROM_DEVICE);
			अगर (unlikely(dma_mapping_error(&np->pci_dev->dev,
						       np->put_rx_ctx->dma))) अणु
				kमुक्त_skb(skb);
				जाओ packet_dropped;
			पूर्ण
			np->put_rx_ctx->dma_len = skb_tailroom(skb);
			np->put_rx.ex->bufhigh = cpu_to_le32(dma_high(np->put_rx_ctx->dma));
			np->put_rx.ex->buflow = cpu_to_le32(dma_low(np->put_rx_ctx->dma));
			wmb();
			np->put_rx.ex->flaglen = cpu_to_le32(np->rx_buf_sz | NV_RX2_AVAIL);
			अगर (unlikely(np->put_rx.ex++ == np->last_rx.ex))
				np->put_rx.ex = np->rx_ring.ex;
			अगर (unlikely(np->put_rx_ctx++ == np->last_rx_ctx))
				np->put_rx_ctx = np->rx_skb;
		पूर्ण अन्यथा अणु
packet_dropped:
			u64_stats_update_begin(&np->swstats_rx_syncp);
			nv_txrx_stats_inc(stat_rx_dropped);
			u64_stats_update_end(&np->swstats_rx_syncp);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* If rx bufs are exhausted called after 50ms to attempt to refresh */
अटल व्योम nv_करो_rx_refill(काष्ठा समयr_list *t)
अणु
	काष्ठा fe_priv *np = from_समयr(np, t, oom_kick);

	/* Just reschedule NAPI rx processing */
	napi_schedule(&np->napi);
पूर्ण

अटल व्योम nv_init_rx(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	पूर्णांक i;

	np->get_rx = np->rx_ring;
	np->put_rx = np->rx_ring;

	अगर (!nv_optimized(np))
		np->last_rx.orig = &np->rx_ring.orig[np->rx_ring_size-1];
	अन्यथा
		np->last_rx.ex = &np->rx_ring.ex[np->rx_ring_size-1];
	np->get_rx_ctx = np->rx_skb;
	np->put_rx_ctx = np->rx_skb;
	np->last_rx_ctx = &np->rx_skb[np->rx_ring_size-1];

	क्रम (i = 0; i < np->rx_ring_size; i++) अणु
		अगर (!nv_optimized(np)) अणु
			np->rx_ring.orig[i].flaglen = 0;
			np->rx_ring.orig[i].buf = 0;
		पूर्ण अन्यथा अणु
			np->rx_ring.ex[i].flaglen = 0;
			np->rx_ring.ex[i].txvlan = 0;
			np->rx_ring.ex[i].bufhigh = 0;
			np->rx_ring.ex[i].buflow = 0;
		पूर्ण
		np->rx_skb[i].skb = शून्य;
		np->rx_skb[i].dma = 0;
	पूर्ण
पूर्ण

अटल व्योम nv_init_tx(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	पूर्णांक i;

	np->get_tx = np->tx_ring;
	np->put_tx = np->tx_ring;

	अगर (!nv_optimized(np))
		np->last_tx.orig = &np->tx_ring.orig[np->tx_ring_size-1];
	अन्यथा
		np->last_tx.ex = &np->tx_ring.ex[np->tx_ring_size-1];
	np->get_tx_ctx = np->tx_skb;
	np->put_tx_ctx = np->tx_skb;
	np->last_tx_ctx = &np->tx_skb[np->tx_ring_size-1];
	netdev_reset_queue(np->dev);
	np->tx_pkts_in_progress = 0;
	np->tx_change_owner = शून्य;
	np->tx_end_flip = शून्य;
	np->tx_stop = 0;

	क्रम (i = 0; i < np->tx_ring_size; i++) अणु
		अगर (!nv_optimized(np)) अणु
			np->tx_ring.orig[i].flaglen = 0;
			np->tx_ring.orig[i].buf = 0;
		पूर्ण अन्यथा अणु
			np->tx_ring.ex[i].flaglen = 0;
			np->tx_ring.ex[i].txvlan = 0;
			np->tx_ring.ex[i].bufhigh = 0;
			np->tx_ring.ex[i].buflow = 0;
		पूर्ण
		np->tx_skb[i].skb = शून्य;
		np->tx_skb[i].dma = 0;
		np->tx_skb[i].dma_len = 0;
		np->tx_skb[i].dma_single = 0;
		np->tx_skb[i].first_tx_desc = शून्य;
		np->tx_skb[i].next_tx_ctx = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक nv_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);

	nv_init_tx(dev);
	nv_init_rx(dev);

	अगर (!nv_optimized(np))
		वापस nv_alloc_rx(dev);
	अन्यथा
		वापस nv_alloc_rx_optimized(dev);
पूर्ण

अटल व्योम nv_unmap_txskb(काष्ठा fe_priv *np, काष्ठा nv_skb_map *tx_skb)
अणु
	अगर (tx_skb->dma) अणु
		अगर (tx_skb->dma_single)
			dma_unmap_single(&np->pci_dev->dev, tx_skb->dma,
					 tx_skb->dma_len,
					 DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_page(&np->pci_dev->dev, tx_skb->dma,
				       tx_skb->dma_len,
				       DMA_TO_DEVICE);
		tx_skb->dma = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक nv_release_txskb(काष्ठा fe_priv *np, काष्ठा nv_skb_map *tx_skb)
अणु
	nv_unmap_txskb(np, tx_skb);
	अगर (tx_skb->skb) अणु
		dev_kमुक्त_skb_any(tx_skb->skb);
		tx_skb->skb = शून्य;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nv_drain_tx(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < np->tx_ring_size; i++) अणु
		अगर (!nv_optimized(np)) अणु
			np->tx_ring.orig[i].flaglen = 0;
			np->tx_ring.orig[i].buf = 0;
		पूर्ण अन्यथा अणु
			np->tx_ring.ex[i].flaglen = 0;
			np->tx_ring.ex[i].txvlan = 0;
			np->tx_ring.ex[i].bufhigh = 0;
			np->tx_ring.ex[i].buflow = 0;
		पूर्ण
		अगर (nv_release_txskb(np, &np->tx_skb[i])) अणु
			u64_stats_update_begin(&np->swstats_tx_syncp);
			nv_txrx_stats_inc(stat_tx_dropped);
			u64_stats_update_end(&np->swstats_tx_syncp);
		पूर्ण
		np->tx_skb[i].dma = 0;
		np->tx_skb[i].dma_len = 0;
		np->tx_skb[i].dma_single = 0;
		np->tx_skb[i].first_tx_desc = शून्य;
		np->tx_skb[i].next_tx_ctx = शून्य;
	पूर्ण
	np->tx_pkts_in_progress = 0;
	np->tx_change_owner = शून्य;
	np->tx_end_flip = शून्य;
पूर्ण

अटल व्योम nv_drain_rx(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < np->rx_ring_size; i++) अणु
		अगर (!nv_optimized(np)) अणु
			np->rx_ring.orig[i].flaglen = 0;
			np->rx_ring.orig[i].buf = 0;
		पूर्ण अन्यथा अणु
			np->rx_ring.ex[i].flaglen = 0;
			np->rx_ring.ex[i].txvlan = 0;
			np->rx_ring.ex[i].bufhigh = 0;
			np->rx_ring.ex[i].buflow = 0;
		पूर्ण
		wmb();
		अगर (np->rx_skb[i].skb) अणु
			dma_unmap_single(&np->pci_dev->dev, np->rx_skb[i].dma,
					 (skb_end_poपूर्णांकer(np->rx_skb[i].skb) -
					 np->rx_skb[i].skb->data),
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(np->rx_skb[i].skb);
			np->rx_skb[i].skb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nv_drain_rxtx(काष्ठा net_device *dev)
अणु
	nv_drain_tx(dev);
	nv_drain_rx(dev);
पूर्ण

अटल अंतरभूत u32 nv_get_empty_tx_slots(काष्ठा fe_priv *np)
अणु
	वापस (u32)(np->tx_ring_size - ((np->tx_ring_size + (np->put_tx_ctx - np->get_tx_ctx)) % np->tx_ring_size));
पूर्ण

अटल व्योम nv_legacybackoff_reseed(काष्ठा net_device *dev)
अणु
	u8 __iomem *base = get_hwbase(dev);
	u32 reg;
	u32 low;
	पूर्णांक tx_status = 0;

	reg = पढ़ोl(base + NvRegSlotTime) & ~NVREG_SLOTTIME_MASK;
	get_अक्रमom_bytes(&low, माप(low));
	reg |= low & NVREG_SLOTTIME_MASK;

	/* Need to stop tx beक्रमe change takes effect.
	 * Caller has alपढ़ोy gained np->lock.
	 */
	tx_status = पढ़ोl(base + NvRegTransmitterControl) & NVREG_XMITCTL_START;
	अगर (tx_status)
		nv_stop_tx(dev);
	nv_stop_rx(dev);
	ग_लिखोl(reg, base + NvRegSlotTime);
	अगर (tx_status)
		nv_start_tx(dev);
	nv_start_rx(dev);
पूर्ण

/* Gear Backoff Seeds */
#घोषणा BACKOFF_SEEDSET_ROWS	8
#घोषणा BACKOFF_SEEDSET_LFSRS	15

/* Known Good seed sets */
अटल स्थिर u32 मुख्य_seedset[BACKOFF_SEEDSET_ROWS][BACKOFF_SEEDSET_LFSRS] = अणु
	अणु145, 155, 165, 175, 185, 196, 235, 245, 255, 265, 275, 285, 660, 690, 874पूर्ण,
	अणु245, 255, 265, 575, 385, 298, 335, 345, 355, 366, 375, 385, 761, 790, 974पूर्ण,
	अणु145, 155, 165, 175, 185, 196, 235, 245, 255, 265, 275, 285, 660, 690, 874पूर्ण,
	अणु245, 255, 265, 575, 385, 298, 335, 345, 355, 366, 375, 386, 761, 790, 974पूर्ण,
	अणु266, 265, 276, 585, 397, 208, 345, 355, 365, 376, 385, 396, 771, 700, 984पूर्ण,
	अणु266, 265, 276, 586, 397, 208, 346, 355, 365, 376, 285, 396, 771, 700, 984पूर्ण,
	अणु366, 365, 376, 686, 497, 308, 447, 455, 466, 476, 485, 496, 871, 800,  84पूर्ण,
	अणु466, 465, 476, 786, 597, 408, 547, 555, 566, 576, 585, 597, 971, 900, 184पूर्ण पूर्ण;

अटल स्थिर u32 gear_seedset[BACKOFF_SEEDSET_ROWS][BACKOFF_SEEDSET_LFSRS] = अणु
	अणु251, 262, 273, 324, 319, 508, 375, 364, 341, 371, 398, 193, 375,  30, 295पूर्ण,
	अणु351, 375, 373, 469, 551, 639, 477, 464, 441, 472, 498, 293, 476, 130, 395पूर्ण,
	अणु351, 375, 373, 469, 551, 639, 477, 464, 441, 472, 498, 293, 476, 130, 397पूर्ण,
	अणु251, 262, 273, 324, 319, 508, 375, 364, 341, 371, 398, 193, 375,  30, 295पूर्ण,
	अणु251, 262, 273, 324, 319, 508, 375, 364, 341, 371, 398, 193, 375,  30, 295पूर्ण,
	अणु351, 375, 373, 469, 551, 639, 477, 464, 441, 472, 498, 293, 476, 130, 395पूर्ण,
	अणु351, 375, 373, 469, 551, 639, 477, 464, 441, 472, 498, 293, 476, 130, 395पूर्ण,
	अणु351, 375, 373, 469, 551, 639, 477, 464, 441, 472, 498, 293, 476, 130, 395पूर्ण पूर्ण;

अटल व्योम nv_gear_backoff_reseed(काष्ठा net_device *dev)
अणु
	u8 __iomem *base = get_hwbase(dev);
	u32 miniseed1, miniseed2, miniseed2_reversed, miniseed3, miniseed3_reversed;
	u32 temp, seedset, combinedSeed;
	पूर्णांक i;

	/* Setup seed क्रम मुक्त running LFSR */
	/* We are going to पढ़ो the समय stamp counter 3 बार
	   and swizzle bits around to increase अक्रमomness */
	get_अक्रमom_bytes(&miniseed1, माप(miniseed1));
	miniseed1 &= 0x0fff;
	अगर (miniseed1 == 0)
		miniseed1 = 0xabc;

	get_अक्रमom_bytes(&miniseed2, माप(miniseed2));
	miniseed2 &= 0x0fff;
	अगर (miniseed2 == 0)
		miniseed2 = 0xabc;
	miniseed2_reversed =
		((miniseed2 & 0xF00) >> 8) |
		 (miniseed2 & 0x0F0) |
		 ((miniseed2 & 0x00F) << 8);

	get_अक्रमom_bytes(&miniseed3, माप(miniseed3));
	miniseed3 &= 0x0fff;
	अगर (miniseed3 == 0)
		miniseed3 = 0xabc;
	miniseed3_reversed =
		((miniseed3 & 0xF00) >> 8) |
		 (miniseed3 & 0x0F0) |
		 ((miniseed3 & 0x00F) << 8);

	combinedSeed = ((miniseed1 ^ miniseed2_reversed) << 12) |
		       (miniseed2 ^ miniseed3_reversed);

	/* Seeds can not be zero */
	अगर ((combinedSeed & NVREG_BKOFFCTRL_SEED_MASK) == 0)
		combinedSeed |= 0x08;
	अगर ((combinedSeed & (NVREG_BKOFFCTRL_SEED_MASK << NVREG_BKOFFCTRL_GEAR)) == 0)
		combinedSeed |= 0x8000;

	/* No need to disable tx here */
	temp = NVREG_BKOFFCTRL_DEFAULT | (0 << NVREG_BKOFFCTRL_SELECT);
	temp |= combinedSeed & NVREG_BKOFFCTRL_SEED_MASK;
	temp |= combinedSeed >> NVREG_BKOFFCTRL_GEAR;
	ग_लिखोl(temp, base + NvRegBackOffControl);

	/* Setup seeds क्रम all gear LFSRs. */
	get_अक्रमom_bytes(&seedset, माप(seedset));
	seedset = seedset % BACKOFF_SEEDSET_ROWS;
	क्रम (i = 1; i <= BACKOFF_SEEDSET_LFSRS; i++) अणु
		temp = NVREG_BKOFFCTRL_DEFAULT | (i << NVREG_BKOFFCTRL_SELECT);
		temp |= मुख्य_seedset[seedset][i-1] & 0x3ff;
		temp |= ((gear_seedset[seedset][i-1] & 0x3ff) << NVREG_BKOFFCTRL_GEAR);
		ग_लिखोl(temp, base + NvRegBackOffControl);
	पूर्ण
पूर्ण

/*
 * nv_start_xmit: dev->hard_start_xmit function
 * Called with netअगर_tx_lock held.
 */
अटल netdev_tx_t nv_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u32 tx_flags = 0;
	u32 tx_flags_extra = (np->desc_ver == DESC_VER_1 ? NV_TX_LASTPACKET : NV_TX2_LASTPACKET);
	अचिन्हित पूर्णांक fragments = skb_shinfo(skb)->nr_frags;
	अचिन्हित पूर्णांक i;
	u32 offset = 0;
	u32 bcnt;
	u32 size = skb_headlen(skb);
	u32 entries = (size >> NV_TX2_TSO_MAX_SHIFT) + ((size & (NV_TX2_TSO_MAX_SIZE-1)) ? 1 : 0);
	u32 empty_slots;
	काष्ठा ring_desc *put_tx;
	काष्ठा ring_desc *start_tx;
	काष्ठा ring_desc *prev_tx;
	काष्ठा nv_skb_map *prev_tx_ctx;
	काष्ठा nv_skb_map *पंचांगp_tx_ctx = शून्य, *start_tx_ctx = शून्य;
	अचिन्हित दीर्घ flags;
	netdev_tx_t ret = NETDEV_TX_OK;

	/* add fragments to entries count */
	क्रम (i = 0; i < fragments; i++) अणु
		u32 frag_size = skb_frag_size(&skb_shinfo(skb)->frags[i]);

		entries += (frag_size >> NV_TX2_TSO_MAX_SHIFT) +
			   ((frag_size & (NV_TX2_TSO_MAX_SIZE-1)) ? 1 : 0);
	पूर्ण

	spin_lock_irqsave(&np->lock, flags);
	empty_slots = nv_get_empty_tx_slots(np);
	अगर (unlikely(empty_slots <= entries)) अणु
		netअगर_stop_queue(dev);
		np->tx_stop = 1;
		spin_unlock_irqrestore(&np->lock, flags);

		/* When normal packets and/or xmit_more packets fill up
		 * tx_desc, it is necessary to trigger NIC tx reg.
		 */
		ret = NETDEV_TX_BUSY;
		जाओ txkick;
	पूर्ण
	spin_unlock_irqrestore(&np->lock, flags);

	start_tx = put_tx = np->put_tx.orig;

	/* setup the header buffer */
	करो अणु
		bcnt = (size > NV_TX2_TSO_MAX_SIZE) ? NV_TX2_TSO_MAX_SIZE : size;
		np->put_tx_ctx->dma = dma_map_single(&np->pci_dev->dev,
						     skb->data + offset, bcnt,
						     DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(&np->pci_dev->dev,
					       np->put_tx_ctx->dma))) अणु
			/* on DMA mapping error - drop the packet */
			dev_kमुक्त_skb_any(skb);
			u64_stats_update_begin(&np->swstats_tx_syncp);
			nv_txrx_stats_inc(stat_tx_dropped);
			u64_stats_update_end(&np->swstats_tx_syncp);

			ret = NETDEV_TX_OK;

			जाओ dma_error;
		पूर्ण
		np->put_tx_ctx->dma_len = bcnt;
		np->put_tx_ctx->dma_single = 1;
		put_tx->buf = cpu_to_le32(np->put_tx_ctx->dma);
		put_tx->flaglen = cpu_to_le32((bcnt-1) | tx_flags);

		tx_flags = np->tx_flags;
		offset += bcnt;
		size -= bcnt;
		अगर (unlikely(put_tx++ == np->last_tx.orig))
			put_tx = np->tx_ring.orig;
		अगर (unlikely(np->put_tx_ctx++ == np->last_tx_ctx))
			np->put_tx_ctx = np->tx_skb;
	पूर्ण जबतक (size);

	/* setup the fragments */
	क्रम (i = 0; i < fragments; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		u32 frag_size = skb_frag_size(frag);
		offset = 0;

		करो अणु
			अगर (!start_tx_ctx)
				start_tx_ctx = पंचांगp_tx_ctx = np->put_tx_ctx;

			bcnt = (frag_size > NV_TX2_TSO_MAX_SIZE) ? NV_TX2_TSO_MAX_SIZE : frag_size;
			np->put_tx_ctx->dma = skb_frag_dma_map(
							&np->pci_dev->dev,
							frag, offset,
							bcnt,
							DMA_TO_DEVICE);
			अगर (unlikely(dma_mapping_error(&np->pci_dev->dev,
						       np->put_tx_ctx->dma))) अणु

				/* Unwind the mapped fragments */
				करो अणु
					nv_unmap_txskb(np, start_tx_ctx);
					अगर (unlikely(पंचांगp_tx_ctx++ == np->last_tx_ctx))
						पंचांगp_tx_ctx = np->tx_skb;
				पूर्ण जबतक (पंचांगp_tx_ctx != np->put_tx_ctx);
				dev_kमुक्त_skb_any(skb);
				np->put_tx_ctx = start_tx_ctx;
				u64_stats_update_begin(&np->swstats_tx_syncp);
				nv_txrx_stats_inc(stat_tx_dropped);
				u64_stats_update_end(&np->swstats_tx_syncp);

				ret = NETDEV_TX_OK;

				जाओ dma_error;
			पूर्ण

			np->put_tx_ctx->dma_len = bcnt;
			np->put_tx_ctx->dma_single = 0;
			put_tx->buf = cpu_to_le32(np->put_tx_ctx->dma);
			put_tx->flaglen = cpu_to_le32((bcnt-1) | tx_flags);

			offset += bcnt;
			frag_size -= bcnt;
			अगर (unlikely(put_tx++ == np->last_tx.orig))
				put_tx = np->tx_ring.orig;
			अगर (unlikely(np->put_tx_ctx++ == np->last_tx_ctx))
				np->put_tx_ctx = np->tx_skb;
		पूर्ण जबतक (frag_size);
	पूर्ण

	अगर (unlikely(put_tx == np->tx_ring.orig))
		prev_tx = np->last_tx.orig;
	अन्यथा
		prev_tx = put_tx - 1;

	अगर (unlikely(np->put_tx_ctx == np->tx_skb))
		prev_tx_ctx = np->last_tx_ctx;
	अन्यथा
		prev_tx_ctx = np->put_tx_ctx - 1;

	/* set last fragment flag  */
	prev_tx->flaglen |= cpu_to_le32(tx_flags_extra);

	/* save skb in this slot's context area */
	prev_tx_ctx->skb = skb;

	अगर (skb_is_gso(skb))
		tx_flags_extra = NV_TX2_TSO | (skb_shinfo(skb)->gso_size << NV_TX2_TSO_SHIFT);
	अन्यथा
		tx_flags_extra = skb->ip_summed == CHECKSUM_PARTIAL ?
			 NV_TX2_CHECKSUM_L3 | NV_TX2_CHECKSUM_L4 : 0;

	spin_lock_irqsave(&np->lock, flags);

	/* set tx flags */
	start_tx->flaglen |= cpu_to_le32(tx_flags | tx_flags_extra);

	netdev_sent_queue(np->dev, skb->len);

	skb_tx_बारtamp(skb);

	np->put_tx.orig = put_tx;

	spin_unlock_irqrestore(&np->lock, flags);

txkick:
	अगर (netअगर_queue_stopped(dev) || !netdev_xmit_more()) अणु
		u32 txrxctl_kick;
dma_error:
		txrxctl_kick = NVREG_TXRXCTL_KICK | np->txrxctl_bits;
		ग_लिखोl(txrxctl_kick, get_hwbase(dev) + NvRegTxRxControl);
	पूर्ण

	वापस ret;
पूर्ण

अटल netdev_tx_t nv_start_xmit_optimized(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u32 tx_flags = 0;
	u32 tx_flags_extra;
	अचिन्हित पूर्णांक fragments = skb_shinfo(skb)->nr_frags;
	अचिन्हित पूर्णांक i;
	u32 offset = 0;
	u32 bcnt;
	u32 size = skb_headlen(skb);
	u32 entries = (size >> NV_TX2_TSO_MAX_SHIFT) + ((size & (NV_TX2_TSO_MAX_SIZE-1)) ? 1 : 0);
	u32 empty_slots;
	काष्ठा ring_desc_ex *put_tx;
	काष्ठा ring_desc_ex *start_tx;
	काष्ठा ring_desc_ex *prev_tx;
	काष्ठा nv_skb_map *prev_tx_ctx;
	काष्ठा nv_skb_map *start_tx_ctx = शून्य;
	काष्ठा nv_skb_map *पंचांगp_tx_ctx = शून्य;
	अचिन्हित दीर्घ flags;
	netdev_tx_t ret = NETDEV_TX_OK;

	/* add fragments to entries count */
	क्रम (i = 0; i < fragments; i++) अणु
		u32 frag_size = skb_frag_size(&skb_shinfo(skb)->frags[i]);

		entries += (frag_size >> NV_TX2_TSO_MAX_SHIFT) +
			   ((frag_size & (NV_TX2_TSO_MAX_SIZE-1)) ? 1 : 0);
	पूर्ण

	spin_lock_irqsave(&np->lock, flags);
	empty_slots = nv_get_empty_tx_slots(np);
	अगर (unlikely(empty_slots <= entries)) अणु
		netअगर_stop_queue(dev);
		np->tx_stop = 1;
		spin_unlock_irqrestore(&np->lock, flags);

		/* When normal packets and/or xmit_more packets fill up
		 * tx_desc, it is necessary to trigger NIC tx reg.
		 */
		ret = NETDEV_TX_BUSY;

		जाओ txkick;
	पूर्ण
	spin_unlock_irqrestore(&np->lock, flags);

	start_tx = put_tx = np->put_tx.ex;
	start_tx_ctx = np->put_tx_ctx;

	/* setup the header buffer */
	करो अणु
		bcnt = (size > NV_TX2_TSO_MAX_SIZE) ? NV_TX2_TSO_MAX_SIZE : size;
		np->put_tx_ctx->dma = dma_map_single(&np->pci_dev->dev,
						     skb->data + offset, bcnt,
						     DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(&np->pci_dev->dev,
					       np->put_tx_ctx->dma))) अणु
			/* on DMA mapping error - drop the packet */
			dev_kमुक्त_skb_any(skb);
			u64_stats_update_begin(&np->swstats_tx_syncp);
			nv_txrx_stats_inc(stat_tx_dropped);
			u64_stats_update_end(&np->swstats_tx_syncp);

			ret = NETDEV_TX_OK;

			जाओ dma_error;
		पूर्ण
		np->put_tx_ctx->dma_len = bcnt;
		np->put_tx_ctx->dma_single = 1;
		put_tx->bufhigh = cpu_to_le32(dma_high(np->put_tx_ctx->dma));
		put_tx->buflow = cpu_to_le32(dma_low(np->put_tx_ctx->dma));
		put_tx->flaglen = cpu_to_le32((bcnt-1) | tx_flags);

		tx_flags = NV_TX2_VALID;
		offset += bcnt;
		size -= bcnt;
		अगर (unlikely(put_tx++ == np->last_tx.ex))
			put_tx = np->tx_ring.ex;
		अगर (unlikely(np->put_tx_ctx++ == np->last_tx_ctx))
			np->put_tx_ctx = np->tx_skb;
	पूर्ण जबतक (size);

	/* setup the fragments */
	क्रम (i = 0; i < fragments; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		u32 frag_size = skb_frag_size(frag);
		offset = 0;

		करो अणु
			bcnt = (frag_size > NV_TX2_TSO_MAX_SIZE) ? NV_TX2_TSO_MAX_SIZE : frag_size;
			अगर (!start_tx_ctx)
				start_tx_ctx = पंचांगp_tx_ctx = np->put_tx_ctx;
			np->put_tx_ctx->dma = skb_frag_dma_map(
							&np->pci_dev->dev,
							frag, offset,
							bcnt,
							DMA_TO_DEVICE);

			अगर (unlikely(dma_mapping_error(&np->pci_dev->dev,
						       np->put_tx_ctx->dma))) अणु

				/* Unwind the mapped fragments */
				करो अणु
					nv_unmap_txskb(np, start_tx_ctx);
					अगर (unlikely(पंचांगp_tx_ctx++ == np->last_tx_ctx))
						पंचांगp_tx_ctx = np->tx_skb;
				पूर्ण जबतक (पंचांगp_tx_ctx != np->put_tx_ctx);
				dev_kमुक्त_skb_any(skb);
				np->put_tx_ctx = start_tx_ctx;
				u64_stats_update_begin(&np->swstats_tx_syncp);
				nv_txrx_stats_inc(stat_tx_dropped);
				u64_stats_update_end(&np->swstats_tx_syncp);

				ret = NETDEV_TX_OK;

				जाओ dma_error;
			पूर्ण
			np->put_tx_ctx->dma_len = bcnt;
			np->put_tx_ctx->dma_single = 0;
			put_tx->bufhigh = cpu_to_le32(dma_high(np->put_tx_ctx->dma));
			put_tx->buflow = cpu_to_le32(dma_low(np->put_tx_ctx->dma));
			put_tx->flaglen = cpu_to_le32((bcnt-1) | tx_flags);

			offset += bcnt;
			frag_size -= bcnt;
			अगर (unlikely(put_tx++ == np->last_tx.ex))
				put_tx = np->tx_ring.ex;
			अगर (unlikely(np->put_tx_ctx++ == np->last_tx_ctx))
				np->put_tx_ctx = np->tx_skb;
		पूर्ण जबतक (frag_size);
	पूर्ण

	अगर (unlikely(put_tx == np->tx_ring.ex))
		prev_tx = np->last_tx.ex;
	अन्यथा
		prev_tx = put_tx - 1;

	अगर (unlikely(np->put_tx_ctx == np->tx_skb))
		prev_tx_ctx = np->last_tx_ctx;
	अन्यथा
		prev_tx_ctx = np->put_tx_ctx - 1;

	/* set last fragment flag  */
	prev_tx->flaglen |= cpu_to_le32(NV_TX2_LASTPACKET);

	/* save skb in this slot's context area */
	prev_tx_ctx->skb = skb;

	अगर (skb_is_gso(skb))
		tx_flags_extra = NV_TX2_TSO | (skb_shinfo(skb)->gso_size << NV_TX2_TSO_SHIFT);
	अन्यथा
		tx_flags_extra = skb->ip_summed == CHECKSUM_PARTIAL ?
			 NV_TX2_CHECKSUM_L3 | NV_TX2_CHECKSUM_L4 : 0;

	/* vlan tag */
	अगर (skb_vlan_tag_present(skb))
		start_tx->txvlan = cpu_to_le32(NV_TX3_VLAN_TAG_PRESENT |
					skb_vlan_tag_get(skb));
	अन्यथा
		start_tx->txvlan = 0;

	spin_lock_irqsave(&np->lock, flags);

	अगर (np->tx_limit) अणु
		/* Limit the number of outstanding tx. Setup all fragments, but
		 * करो not set the VALID bit on the first descriptor. Save a poपूर्णांकer
		 * to that descriptor and also क्रम next skb_map element.
		 */

		अगर (np->tx_pkts_in_progress == NV_TX_LIMIT_COUNT) अणु
			अगर (!np->tx_change_owner)
				np->tx_change_owner = start_tx_ctx;

			/* हटाओ VALID bit */
			tx_flags &= ~NV_TX2_VALID;
			start_tx_ctx->first_tx_desc = start_tx;
			start_tx_ctx->next_tx_ctx = np->put_tx_ctx;
			np->tx_end_flip = np->put_tx_ctx;
		पूर्ण अन्यथा अणु
			np->tx_pkts_in_progress++;
		पूर्ण
	पूर्ण

	/* set tx flags */
	start_tx->flaglen |= cpu_to_le32(tx_flags | tx_flags_extra);

	netdev_sent_queue(np->dev, skb->len);

	skb_tx_बारtamp(skb);

	np->put_tx.ex = put_tx;

	spin_unlock_irqrestore(&np->lock, flags);

txkick:
	अगर (netअगर_queue_stopped(dev) || !netdev_xmit_more()) अणु
		u32 txrxctl_kick;
dma_error:
		txrxctl_kick = NVREG_TXRXCTL_KICK | np->txrxctl_bits;
		ग_लिखोl(txrxctl_kick, get_hwbase(dev) + NvRegTxRxControl);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम nv_tx_flip_ownership(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);

	np->tx_pkts_in_progress--;
	अगर (np->tx_change_owner) अणु
		np->tx_change_owner->first_tx_desc->flaglen |=
			cpu_to_le32(NV_TX2_VALID);
		np->tx_pkts_in_progress++;

		np->tx_change_owner = np->tx_change_owner->next_tx_ctx;
		अगर (np->tx_change_owner == np->tx_end_flip)
			np->tx_change_owner = शून्य;

		ग_लिखोl(NVREG_TXRXCTL_KICK|np->txrxctl_bits, get_hwbase(dev) + NvRegTxRxControl);
	पूर्ण
पूर्ण

/*
 * nv_tx_करोne: check क्रम completed packets, release the skbs.
 *
 * Caller must own np->lock.
 */
अटल पूर्णांक nv_tx_करोne(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u32 flags;
	पूर्णांक tx_work = 0;
	काष्ठा ring_desc *orig_get_tx = np->get_tx.orig;
	अचिन्हित पूर्णांक bytes_compl = 0;

	जबतक ((np->get_tx.orig != np->put_tx.orig) &&
	       !((flags = le32_to_cpu(np->get_tx.orig->flaglen)) & NV_TX_VALID) &&
	       (tx_work < limit)) अणु

		nv_unmap_txskb(np, np->get_tx_ctx);

		अगर (np->desc_ver == DESC_VER_1) अणु
			अगर (flags & NV_TX_LASTPACKET) अणु
				अगर (unlikely(flags & NV_TX_ERROR)) अणु
					अगर ((flags & NV_TX_RETRYERROR)
					    && !(flags & NV_TX_RETRYCOUNT_MASK))
						nv_legacybackoff_reseed(dev);
				पूर्ण अन्यथा अणु
					अचिन्हित पूर्णांक len;

					u64_stats_update_begin(&np->swstats_tx_syncp);
					nv_txrx_stats_inc(stat_tx_packets);
					len = np->get_tx_ctx->skb->len;
					nv_txrx_stats_add(stat_tx_bytes, len);
					u64_stats_update_end(&np->swstats_tx_syncp);
				पूर्ण
				bytes_compl += np->get_tx_ctx->skb->len;
				dev_kमुक्त_skb_any(np->get_tx_ctx->skb);
				np->get_tx_ctx->skb = शून्य;
				tx_work++;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (flags & NV_TX2_LASTPACKET) अणु
				अगर (unlikely(flags & NV_TX2_ERROR)) अणु
					अगर ((flags & NV_TX2_RETRYERROR)
					    && !(flags & NV_TX2_RETRYCOUNT_MASK))
						nv_legacybackoff_reseed(dev);
				पूर्ण अन्यथा अणु
					अचिन्हित पूर्णांक len;

					u64_stats_update_begin(&np->swstats_tx_syncp);
					nv_txrx_stats_inc(stat_tx_packets);
					len = np->get_tx_ctx->skb->len;
					nv_txrx_stats_add(stat_tx_bytes, len);
					u64_stats_update_end(&np->swstats_tx_syncp);
				पूर्ण
				bytes_compl += np->get_tx_ctx->skb->len;
				dev_kमुक्त_skb_any(np->get_tx_ctx->skb);
				np->get_tx_ctx->skb = शून्य;
				tx_work++;
			पूर्ण
		पूर्ण
		अगर (unlikely(np->get_tx.orig++ == np->last_tx.orig))
			np->get_tx.orig = np->tx_ring.orig;
		अगर (unlikely(np->get_tx_ctx++ == np->last_tx_ctx))
			np->get_tx_ctx = np->tx_skb;
	पूर्ण

	netdev_completed_queue(np->dev, tx_work, bytes_compl);

	अगर (unlikely((np->tx_stop == 1) && (np->get_tx.orig != orig_get_tx))) अणु
		np->tx_stop = 0;
		netअगर_wake_queue(dev);
	पूर्ण
	वापस tx_work;
पूर्ण

अटल पूर्णांक nv_tx_करोne_optimized(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u32 flags;
	पूर्णांक tx_work = 0;
	काष्ठा ring_desc_ex *orig_get_tx = np->get_tx.ex;
	अचिन्हित दीर्घ bytes_cleaned = 0;

	जबतक ((np->get_tx.ex != np->put_tx.ex) &&
	       !((flags = le32_to_cpu(np->get_tx.ex->flaglen)) & NV_TX2_VALID) &&
	       (tx_work < limit)) अणु

		nv_unmap_txskb(np, np->get_tx_ctx);

		अगर (flags & NV_TX2_LASTPACKET) अणु
			अगर (unlikely(flags & NV_TX2_ERROR)) अणु
				अगर ((flags & NV_TX2_RETRYERROR)
				    && !(flags & NV_TX2_RETRYCOUNT_MASK)) अणु
					अगर (np->driver_data & DEV_HAS_GEAR_MODE)
						nv_gear_backoff_reseed(dev);
					अन्यथा
						nv_legacybackoff_reseed(dev);
				पूर्ण
			पूर्ण अन्यथा अणु
				अचिन्हित पूर्णांक len;

				u64_stats_update_begin(&np->swstats_tx_syncp);
				nv_txrx_stats_inc(stat_tx_packets);
				len = np->get_tx_ctx->skb->len;
				nv_txrx_stats_add(stat_tx_bytes, len);
				u64_stats_update_end(&np->swstats_tx_syncp);
			पूर्ण

			bytes_cleaned += np->get_tx_ctx->skb->len;
			dev_kमुक्त_skb_any(np->get_tx_ctx->skb);
			np->get_tx_ctx->skb = शून्य;
			tx_work++;

			अगर (np->tx_limit)
				nv_tx_flip_ownership(dev);
		पूर्ण

		अगर (unlikely(np->get_tx.ex++ == np->last_tx.ex))
			np->get_tx.ex = np->tx_ring.ex;
		अगर (unlikely(np->get_tx_ctx++ == np->last_tx_ctx))
			np->get_tx_ctx = np->tx_skb;
	पूर्ण

	netdev_completed_queue(np->dev, tx_work, bytes_cleaned);

	अगर (unlikely((np->tx_stop == 1) && (np->get_tx.ex != orig_get_tx))) अणु
		np->tx_stop = 0;
		netअगर_wake_queue(dev);
	पूर्ण
	वापस tx_work;
पूर्ण

/*
 * nv_tx_समयout: dev->tx_समयout function
 * Called with netअगर_tx_lock held.
 */
अटल व्योम nv_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 status;
	जोड़ ring_type put_tx;
	पूर्णांक saved_tx_limit;

	अगर (np->msi_flags & NV_MSI_X_ENABLED)
		status = पढ़ोl(base + NvRegMSIXIrqStatus) & NVREG_IRQSTAT_MASK;
	अन्यथा
		status = पढ़ोl(base + NvRegIrqStatus) & NVREG_IRQSTAT_MASK;

	netdev_warn(dev, "Got tx_timeout. irq status: %08x\n", status);

	अगर (unlikely(debug_tx_समयout)) अणु
		पूर्णांक i;

		netdev_info(dev, "Ring at %lx\n", (अचिन्हित दीर्घ)np->ring_addr);
		netdev_info(dev, "Dumping tx registers\n");
		क्रम (i = 0; i <= np->रेजिस्टर_size; i += 32) अणु
			netdev_info(dev,
				    "%3x: %08x %08x %08x %08x "
				    "%08x %08x %08x %08x\n",
				    i,
				    पढ़ोl(base + i + 0), पढ़ोl(base + i + 4),
				    पढ़ोl(base + i + 8), पढ़ोl(base + i + 12),
				    पढ़ोl(base + i + 16), पढ़ोl(base + i + 20),
				    पढ़ोl(base + i + 24), पढ़ोl(base + i + 28));
		पूर्ण
		netdev_info(dev, "Dumping tx ring\n");
		क्रम (i = 0; i < np->tx_ring_size; i += 4) अणु
			अगर (!nv_optimized(np)) अणु
				netdev_info(dev,
					    "%03x: %08x %08x // %08x %08x "
					    "// %08x %08x // %08x %08x\n",
					    i,
					    le32_to_cpu(np->tx_ring.orig[i].buf),
					    le32_to_cpu(np->tx_ring.orig[i].flaglen),
					    le32_to_cpu(np->tx_ring.orig[i+1].buf),
					    le32_to_cpu(np->tx_ring.orig[i+1].flaglen),
					    le32_to_cpu(np->tx_ring.orig[i+2].buf),
					    le32_to_cpu(np->tx_ring.orig[i+2].flaglen),
					    le32_to_cpu(np->tx_ring.orig[i+3].buf),
					    le32_to_cpu(np->tx_ring.orig[i+3].flaglen));
			पूर्ण अन्यथा अणु
				netdev_info(dev,
					    "%03x: %08x %08x %08x "
					    "// %08x %08x %08x "
					    "// %08x %08x %08x "
					    "// %08x %08x %08x\n",
					    i,
					    le32_to_cpu(np->tx_ring.ex[i].bufhigh),
					    le32_to_cpu(np->tx_ring.ex[i].buflow),
					    le32_to_cpu(np->tx_ring.ex[i].flaglen),
					    le32_to_cpu(np->tx_ring.ex[i+1].bufhigh),
					    le32_to_cpu(np->tx_ring.ex[i+1].buflow),
					    le32_to_cpu(np->tx_ring.ex[i+1].flaglen),
					    le32_to_cpu(np->tx_ring.ex[i+2].bufhigh),
					    le32_to_cpu(np->tx_ring.ex[i+2].buflow),
					    le32_to_cpu(np->tx_ring.ex[i+2].flaglen),
					    le32_to_cpu(np->tx_ring.ex[i+3].bufhigh),
					    le32_to_cpu(np->tx_ring.ex[i+3].buflow),
					    le32_to_cpu(np->tx_ring.ex[i+3].flaglen));
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irq(&np->lock);

	/* 1) stop tx engine */
	nv_stop_tx(dev);

	/* 2) complete any outstanding tx and करो not give HW any limited tx pkts */
	saved_tx_limit = np->tx_limit;
	np->tx_limit = 0; /* prevent giving HW any limited pkts */
	np->tx_stop = 0;  /* prevent waking tx queue */
	अगर (!nv_optimized(np))
		nv_tx_करोne(dev, np->tx_ring_size);
	अन्यथा
		nv_tx_करोne_optimized(dev, np->tx_ring_size);

	/* save current HW position */
	अगर (np->tx_change_owner)
		put_tx.ex = np->tx_change_owner->first_tx_desc;
	अन्यथा
		put_tx = np->put_tx;

	/* 3) clear all tx state */
	nv_drain_tx(dev);
	nv_init_tx(dev);

	/* 4) restore state to current HW position */
	np->get_tx = np->put_tx = put_tx;
	np->tx_limit = saved_tx_limit;

	/* 5) restart tx engine */
	nv_start_tx(dev);
	netअगर_wake_queue(dev);
	spin_unlock_irq(&np->lock);
पूर्ण

/*
 * Called when the nic notices a mismatch between the actual data len on the
 * wire and the len indicated in the 802 header
 */
अटल पूर्णांक nv_getlen(काष्ठा net_device *dev, व्योम *packet, पूर्णांक datalen)
अणु
	पूर्णांक hdrlen;	/* length of the 802 header */
	पूर्णांक protolen;	/* length as stored in the proto field */

	/* 1) calculate len according to header */
	अगर (((काष्ठा vlan_ethhdr *)packet)->h_vlan_proto == htons(ETH_P_8021Q)) अणु
		protolen = ntohs(((काष्ठा vlan_ethhdr *)packet)->h_vlan_encapsulated_proto);
		hdrlen = VLAN_HLEN;
	पूर्ण अन्यथा अणु
		protolen = ntohs(((काष्ठा ethhdr *)packet)->h_proto);
		hdrlen = ETH_HLEN;
	पूर्ण
	अगर (protolen > ETH_DATA_LEN)
		वापस datalen; /* Value in proto field not a len, no checks possible */

	protolen += hdrlen;
	/* consistency checks: */
	अगर (datalen > ETH_ZLEN) अणु
		अगर (datalen >= protolen) अणु
			/* more data on wire than in 802 header, trim of
			 * additional data.
			 */
			वापस protolen;
		पूर्ण अन्यथा अणु
			/* less data on wire than mentioned in header.
			 * Discard the packet.
			 */
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* लघु packet. Accept only अगर 802 values are also लघु */
		अगर (protolen > ETH_ZLEN) अणु
			वापस -1;
		पूर्ण
		वापस datalen;
	पूर्ण
पूर्ण

अटल व्योम rx_missing_handler(u32 flags, काष्ठा fe_priv *np)
अणु
	अगर (flags & NV_RX_MISSEDFRAME) अणु
		u64_stats_update_begin(&np->swstats_rx_syncp);
		nv_txrx_stats_inc(stat_rx_missed_errors);
		u64_stats_update_end(&np->swstats_rx_syncp);
	पूर्ण
पूर्ण

अटल पूर्णांक nv_rx_process(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u32 flags;
	पूर्णांक rx_work = 0;
	काष्ठा sk_buff *skb;
	पूर्णांक len;

	जबतक ((np->get_rx.orig != np->put_rx.orig) &&
	      !((flags = le32_to_cpu(np->get_rx.orig->flaglen)) & NV_RX_AVAIL) &&
		(rx_work < limit)) अणु

		/*
		 * the packet is क्रम us - immediately tear करोwn the pci mapping.
		 * TODO: check अगर a prefetch of the first cacheline improves
		 * the perक्रमmance.
		 */
		dma_unmap_single(&np->pci_dev->dev, np->get_rx_ctx->dma,
				 np->get_rx_ctx->dma_len,
				 DMA_FROM_DEVICE);
		skb = np->get_rx_ctx->skb;
		np->get_rx_ctx->skb = शून्य;

		/* look at what we actually got: */
		अगर (np->desc_ver == DESC_VER_1) अणु
			अगर (likely(flags & NV_RX_DESCRIPTORVALID)) अणु
				len = flags & LEN_MASK_V1;
				अगर (unlikely(flags & NV_RX_ERROR)) अणु
					अगर ((flags & NV_RX_ERROR_MASK) == NV_RX_ERROR4) अणु
						len = nv_getlen(dev, skb->data, len);
						अगर (len < 0) अणु
							dev_kमुक्त_skb(skb);
							जाओ next_pkt;
						पूर्ण
					पूर्ण
					/* framing errors are soft errors */
					अन्यथा अगर ((flags & NV_RX_ERROR_MASK) == NV_RX_FRAMINGERR) अणु
						अगर (flags & NV_RX_SUBTRACT1)
							len--;
					पूर्ण
					/* the rest are hard errors */
					अन्यथा अणु
						rx_missing_handler(flags, np);
						dev_kमुक्त_skb(skb);
						जाओ next_pkt;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				dev_kमुक्त_skb(skb);
				जाओ next_pkt;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (likely(flags & NV_RX2_DESCRIPTORVALID)) अणु
				len = flags & LEN_MASK_V2;
				अगर (unlikely(flags & NV_RX2_ERROR)) अणु
					अगर ((flags & NV_RX2_ERROR_MASK) == NV_RX2_ERROR4) अणु
						len = nv_getlen(dev, skb->data, len);
						अगर (len < 0) अणु
							dev_kमुक्त_skb(skb);
							जाओ next_pkt;
						पूर्ण
					पूर्ण
					/* framing errors are soft errors */
					अन्यथा अगर ((flags & NV_RX2_ERROR_MASK) == NV_RX2_FRAMINGERR) अणु
						अगर (flags & NV_RX2_SUBTRACT1)
							len--;
					पूर्ण
					/* the rest are hard errors */
					अन्यथा अणु
						dev_kमुक्त_skb(skb);
						जाओ next_pkt;
					पूर्ण
				पूर्ण
				अगर (((flags & NV_RX2_CHECKSUMMASK) == NV_RX2_CHECKSUM_IP_TCP) || /*ip and tcp */
				    ((flags & NV_RX2_CHECKSUMMASK) == NV_RX2_CHECKSUM_IP_UDP))   /*ip and udp */
					skb->ip_summed = CHECKSUM_UNNECESSARY;
			पूर्ण अन्यथा अणु
				dev_kमुक्त_skb(skb);
				जाओ next_pkt;
			पूर्ण
		पूर्ण
		/* got a valid packet - क्रमward it to the network core */
		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, dev);
		napi_gro_receive(&np->napi, skb);
		u64_stats_update_begin(&np->swstats_rx_syncp);
		nv_txrx_stats_inc(stat_rx_packets);
		nv_txrx_stats_add(stat_rx_bytes, len);
		u64_stats_update_end(&np->swstats_rx_syncp);
next_pkt:
		अगर (unlikely(np->get_rx.orig++ == np->last_rx.orig))
			np->get_rx.orig = np->rx_ring.orig;
		अगर (unlikely(np->get_rx_ctx++ == np->last_rx_ctx))
			np->get_rx_ctx = np->rx_skb;

		rx_work++;
	पूर्ण

	वापस rx_work;
पूर्ण

अटल पूर्णांक nv_rx_process_optimized(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u32 flags;
	u32 vlanflags = 0;
	पूर्णांक rx_work = 0;
	काष्ठा sk_buff *skb;
	पूर्णांक len;

	जबतक ((np->get_rx.ex != np->put_rx.ex) &&
	      !((flags = le32_to_cpu(np->get_rx.ex->flaglen)) & NV_RX2_AVAIL) &&
	      (rx_work < limit)) अणु

		/*
		 * the packet is क्रम us - immediately tear करोwn the pci mapping.
		 * TODO: check अगर a prefetch of the first cacheline improves
		 * the perक्रमmance.
		 */
		dma_unmap_single(&np->pci_dev->dev, np->get_rx_ctx->dma,
				 np->get_rx_ctx->dma_len,
				 DMA_FROM_DEVICE);
		skb = np->get_rx_ctx->skb;
		np->get_rx_ctx->skb = शून्य;

		/* look at what we actually got: */
		अगर (likely(flags & NV_RX2_DESCRIPTORVALID)) अणु
			len = flags & LEN_MASK_V2;
			अगर (unlikely(flags & NV_RX2_ERROR)) अणु
				अगर ((flags & NV_RX2_ERROR_MASK) == NV_RX2_ERROR4) अणु
					len = nv_getlen(dev, skb->data, len);
					अगर (len < 0) अणु
						dev_kमुक्त_skb(skb);
						जाओ next_pkt;
					पूर्ण
				पूर्ण
				/* framing errors are soft errors */
				अन्यथा अगर ((flags & NV_RX2_ERROR_MASK) == NV_RX2_FRAMINGERR) अणु
					अगर (flags & NV_RX2_SUBTRACT1)
						len--;
				पूर्ण
				/* the rest are hard errors */
				अन्यथा अणु
					dev_kमुक्त_skb(skb);
					जाओ next_pkt;
				पूर्ण
			पूर्ण

			अगर (((flags & NV_RX2_CHECKSUMMASK) == NV_RX2_CHECKSUM_IP_TCP) || /*ip and tcp */
			    ((flags & NV_RX2_CHECKSUMMASK) == NV_RX2_CHECKSUM_IP_UDP))   /*ip and udp */
				skb->ip_summed = CHECKSUM_UNNECESSARY;

			/* got a valid packet - क्रमward it to the network core */
			skb_put(skb, len);
			skb->protocol = eth_type_trans(skb, dev);
			prefetch(skb->data);

			vlanflags = le32_to_cpu(np->get_rx.ex->buflow);

			/*
			 * There's need to check क्रम NETIF_F_HW_VLAN_CTAG_RX
			 * here. Even अगर vlan rx accel is disabled,
			 * NV_RX3_VLAN_TAG_PRESENT is pseuकरो अक्रमomly set.
			 */
			अगर (dev->features & NETIF_F_HW_VLAN_CTAG_RX &&
			    vlanflags & NV_RX3_VLAN_TAG_PRESENT) अणु
				u16 vid = vlanflags & NV_RX3_VLAN_TAG_MASK;

				__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
			पूर्ण
			napi_gro_receive(&np->napi, skb);
			u64_stats_update_begin(&np->swstats_rx_syncp);
			nv_txrx_stats_inc(stat_rx_packets);
			nv_txrx_stats_add(stat_rx_bytes, len);
			u64_stats_update_end(&np->swstats_rx_syncp);
		पूर्ण अन्यथा अणु
			dev_kमुक्त_skb(skb);
		पूर्ण
next_pkt:
		अगर (unlikely(np->get_rx.ex++ == np->last_rx.ex))
			np->get_rx.ex = np->rx_ring.ex;
		अगर (unlikely(np->get_rx_ctx++ == np->last_rx_ctx))
			np->get_rx_ctx = np->rx_skb;

		rx_work++;
	पूर्ण

	वापस rx_work;
पूर्ण

अटल व्योम set_bufsize(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);

	अगर (dev->mtu <= ETH_DATA_LEN)
		np->rx_buf_sz = ETH_DATA_LEN + NV_RX_HEADERS;
	अन्यथा
		np->rx_buf_sz = dev->mtu + NV_RX_HEADERS;
पूर्ण

/*
 * nv_change_mtu: dev->change_mtu function
 * Called with dev_base_lock held क्रम पढ़ो.
 */
अटल पूर्णांक nv_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	पूर्णांक old_mtu;

	old_mtu = dev->mtu;
	dev->mtu = new_mtu;

	/* वापस early अगर the buffer sizes will not change */
	अगर (old_mtu <= ETH_DATA_LEN && new_mtu <= ETH_DATA_LEN)
		वापस 0;

	/* synchronized against खोलो : rtnl_lock() held by caller */
	अगर (netअगर_running(dev)) अणु
		u8 __iomem *base = get_hwbase(dev);
		/*
		 * It seems that the nic preloads valid ring entries पूर्णांकo an
		 * पूर्णांकernal buffer. The procedure क्रम flushing everything is
		 * guessed, there is probably a simpler approach.
		 * Changing the MTU is a rare event, it shouldn't matter.
		 */
		nv_disable_irq(dev);
		nv_napi_disable(dev);
		netअगर_tx_lock_bh(dev);
		netअगर_addr_lock(dev);
		spin_lock(&np->lock);
		/* stop engines */
		nv_stop_rxtx(dev);
		nv_txrx_reset(dev);
		/* drain rx queue */
		nv_drain_rxtx(dev);
		/* reinit driver view of the rx queue */
		set_bufsize(dev);
		अगर (nv_init_ring(dev)) अणु
			अगर (!np->in_shutकरोwn)
				mod_समयr(&np->oom_kick, jअगरfies + OOM_REFILL);
		पूर्ण
		/* reinit nic view of the rx queue */
		ग_लिखोl(np->rx_buf_sz, base + NvRegOffloadConfig);
		setup_hw_rings(dev, NV_SETUP_RX_RING | NV_SETUP_TX_RING);
		ग_लिखोl(((np->rx_ring_size-1) << NVREG_RINGSZ_RXSHIFT) + ((np->tx_ring_size-1) << NVREG_RINGSZ_TXSHIFT),
			base + NvRegRingSizes);
		pci_push(base);
		ग_लिखोl(NVREG_TXRXCTL_KICK|np->txrxctl_bits, get_hwbase(dev) + NvRegTxRxControl);
		pci_push(base);

		/* restart rx engine */
		nv_start_rxtx(dev);
		spin_unlock(&np->lock);
		netअगर_addr_unlock(dev);
		netअगर_tx_unlock_bh(dev);
		nv_napi_enable(dev);
		nv_enable_irq(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nv_copy_mac_to_hw(काष्ठा net_device *dev)
अणु
	u8 __iomem *base = get_hwbase(dev);
	u32 mac[2];

	mac[0] = (dev->dev_addr[0] << 0) + (dev->dev_addr[1] << 8) +
			(dev->dev_addr[2] << 16) + (dev->dev_addr[3] << 24);
	mac[1] = (dev->dev_addr[4] << 0) + (dev->dev_addr[5] << 8);

	ग_लिखोl(mac[0], base + NvRegMacAddrA);
	ग_लिखोl(mac[1], base + NvRegMacAddrB);
पूर्ण

/*
 * nv_set_mac_address: dev->set_mac_address function
 * Called with rtnl_lock() held.
 */
अटल पूर्णांक nv_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	काष्ठा sockaddr *macaddr = (काष्ठा sockaddr *)addr;

	अगर (!is_valid_ether_addr(macaddr->sa_data))
		वापस -EADDRNOTAVAIL;

	/* synchronized against खोलो : rtnl_lock() held by caller */
	स_नकल(dev->dev_addr, macaddr->sa_data, ETH_ALEN);

	अगर (netअगर_running(dev)) अणु
		netअगर_tx_lock_bh(dev);
		netअगर_addr_lock(dev);
		spin_lock_irq(&np->lock);

		/* stop rx engine */
		nv_stop_rx(dev);

		/* set mac address */
		nv_copy_mac_to_hw(dev);

		/* restart rx engine */
		nv_start_rx(dev);
		spin_unlock_irq(&np->lock);
		netअगर_addr_unlock(dev);
		netअगर_tx_unlock_bh(dev);
	पूर्ण अन्यथा अणु
		nv_copy_mac_to_hw(dev);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * nv_set_multicast: dev->set_multicast function
 * Called with netअगर_tx_lock held.
 */
अटल व्योम nv_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 addr[2];
	u32 mask[2];
	u32 pff = पढ़ोl(base + NvRegPacketFilterFlags) & NVREG_PFF_PAUSE_RX;

	स_रखो(addr, 0, माप(addr));
	स_रखो(mask, 0, माप(mask));

	अगर (dev->flags & IFF_PROMISC) अणु
		pff |= NVREG_PFF_PROMISC;
	पूर्ण अन्यथा अणु
		pff |= NVREG_PFF_MYADDR;

		अगर (dev->flags & IFF_ALLMULTI || !netdev_mc_empty(dev)) अणु
			u32 alwaysOff[2];
			u32 alwaysOn[2];

			alwaysOn[0] = alwaysOn[1] = alwaysOff[0] = alwaysOff[1] = 0xffffffff;
			अगर (dev->flags & IFF_ALLMULTI) अणु
				alwaysOn[0] = alwaysOn[1] = alwaysOff[0] = alwaysOff[1] = 0;
			पूर्ण अन्यथा अणु
				काष्ठा netdev_hw_addr *ha;

				netdev_क्रम_each_mc_addr(ha, dev) अणु
					अचिन्हित अक्षर *hw_addr = ha->addr;
					u32 a, b;

					a = le32_to_cpu(*(__le32 *) hw_addr);
					b = le16_to_cpu(*(__le16 *) (&hw_addr[4]));
					alwaysOn[0] &= a;
					alwaysOff[0] &= ~a;
					alwaysOn[1] &= b;
					alwaysOff[1] &= ~b;
				पूर्ण
			पूर्ण
			addr[0] = alwaysOn[0];
			addr[1] = alwaysOn[1];
			mask[0] = alwaysOn[0] | alwaysOff[0];
			mask[1] = alwaysOn[1] | alwaysOff[1];
		पूर्ण अन्यथा अणु
			mask[0] = NVREG_MCASTMASKA_NONE;
			mask[1] = NVREG_MCASTMASKB_NONE;
		पूर्ण
	पूर्ण
	addr[0] |= NVREG_MCASTADDRA_FORCE;
	pff |= NVREG_PFF_ALWAYS;
	spin_lock_irq(&np->lock);
	nv_stop_rx(dev);
	ग_लिखोl(addr[0], base + NvRegMulticastAddrA);
	ग_लिखोl(addr[1], base + NvRegMulticastAddrB);
	ग_लिखोl(mask[0], base + NvRegMulticastMaskA);
	ग_लिखोl(mask[1], base + NvRegMulticastMaskB);
	ग_लिखोl(pff, base + NvRegPacketFilterFlags);
	nv_start_rx(dev);
	spin_unlock_irq(&np->lock);
पूर्ण

अटल व्योम nv_update_छोड़ो(काष्ठा net_device *dev, u32 छोड़ो_flags)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);

	np->छोड़ो_flags &= ~(NV_PAUSEFRAME_TX_ENABLE | NV_PAUSEFRAME_RX_ENABLE);

	अगर (np->छोड़ो_flags & NV_PAUSEFRAME_RX_CAPABLE) अणु
		u32 pff = पढ़ोl(base + NvRegPacketFilterFlags) & ~NVREG_PFF_PAUSE_RX;
		अगर (छोड़ो_flags & NV_PAUSEFRAME_RX_ENABLE) अणु
			ग_लिखोl(pff|NVREG_PFF_PAUSE_RX, base + NvRegPacketFilterFlags);
			np->छोड़ो_flags |= NV_PAUSEFRAME_RX_ENABLE;
		पूर्ण अन्यथा अणु
			ग_लिखोl(pff, base + NvRegPacketFilterFlags);
		पूर्ण
	पूर्ण
	अगर (np->छोड़ो_flags & NV_PAUSEFRAME_TX_CAPABLE) अणु
		u32 regmisc = पढ़ोl(base + NvRegMisc1) & ~NVREG_MISC1_PAUSE_TX;
		अगर (छोड़ो_flags & NV_PAUSEFRAME_TX_ENABLE) अणु
			u32 छोड़ो_enable = NVREG_TX_PAUSEFRAME_ENABLE_V1;
			अगर (np->driver_data & DEV_HAS_PAUSEFRAME_TX_V2)
				छोड़ो_enable = NVREG_TX_PAUSEFRAME_ENABLE_V2;
			अगर (np->driver_data & DEV_HAS_PAUSEFRAME_TX_V3) अणु
				छोड़ो_enable = NVREG_TX_PAUSEFRAME_ENABLE_V3;
				/* limit the number of tx छोड़ो frames to a शेष of 8 */
				ग_लिखोl(पढ़ोl(base + NvRegTxPauseFrameLimit)|NVREG_TX_PAUSEFRAMELIMIT_ENABLE, base + NvRegTxPauseFrameLimit);
			पूर्ण
			ग_लिखोl(छोड़ो_enable,  base + NvRegTxPauseFrame);
			ग_लिखोl(regmisc|NVREG_MISC1_PAUSE_TX, base + NvRegMisc1);
			np->छोड़ो_flags |= NV_PAUSEFRAME_TX_ENABLE;
		पूर्ण अन्यथा अणु
			ग_लिखोl(NVREG_TX_PAUSEFRAME_DISABLE,  base + NvRegTxPauseFrame);
			ग_लिखोl(regmisc, base + NvRegMisc1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nv_क्रमce_linkspeed(काष्ठा net_device *dev, पूर्णांक speed, पूर्णांक duplex)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 phyreg, txreg;
	पूर्णांक mii_status;

	np->linkspeed = NVREG_LINKSPEED_FORCE|speed;
	np->duplex = duplex;

	/* see अगर gigabit phy */
	mii_status = mii_rw(dev, np->phyaddr, MII_BMSR, MII_READ);
	अगर (mii_status & PHY_GIGABIT) अणु
		np->gigabit = PHY_GIGABIT;
		phyreg = पढ़ोl(base + NvRegSlotTime);
		phyreg &= ~(0x3FF00);
		अगर ((np->linkspeed & 0xFFF) == NVREG_LINKSPEED_10)
			phyreg |= NVREG_SLOTTIME_10_100_FULL;
		अन्यथा अगर ((np->linkspeed & 0xFFF) == NVREG_LINKSPEED_100)
			phyreg |= NVREG_SLOTTIME_10_100_FULL;
		अन्यथा अगर ((np->linkspeed & 0xFFF) == NVREG_LINKSPEED_1000)
			phyreg |= NVREG_SLOTTIME_1000_FULL;
		ग_लिखोl(phyreg, base + NvRegSlotTime);
	पूर्ण

	phyreg = पढ़ोl(base + NvRegPhyInterface);
	phyreg &= ~(PHY_HALF|PHY_100|PHY_1000);
	अगर (np->duplex == 0)
		phyreg |= PHY_HALF;
	अगर ((np->linkspeed & NVREG_LINKSPEED_MASK) == NVREG_LINKSPEED_100)
		phyreg |= PHY_100;
	अन्यथा अगर ((np->linkspeed & NVREG_LINKSPEED_MASK) ==
							NVREG_LINKSPEED_1000)
		phyreg |= PHY_1000;
	ग_लिखोl(phyreg, base + NvRegPhyInterface);

	अगर (phyreg & PHY_RGMII) अणु
		अगर ((np->linkspeed & NVREG_LINKSPEED_MASK) ==
							NVREG_LINKSPEED_1000)
			txreg = NVREG_TX_DEFERRAL_RGMII_1000;
		अन्यथा
			txreg = NVREG_TX_DEFERRAL_RGMII_10_100;
	पूर्ण अन्यथा अणु
		txreg = NVREG_TX_DEFERRAL_DEFAULT;
	पूर्ण
	ग_लिखोl(txreg, base + NvRegTxDeferral);

	अगर (np->desc_ver == DESC_VER_1) अणु
		txreg = NVREG_TX_WM_DESC1_DEFAULT;
	पूर्ण अन्यथा अणु
		अगर ((np->linkspeed & NVREG_LINKSPEED_MASK) ==
					 NVREG_LINKSPEED_1000)
			txreg = NVREG_TX_WM_DESC2_3_1000;
		अन्यथा
			txreg = NVREG_TX_WM_DESC2_3_DEFAULT;
	पूर्ण
	ग_लिखोl(txreg, base + NvRegTxWatermark);

	ग_लिखोl(NVREG_MISC1_FORCE | (np->duplex ? 0 : NVREG_MISC1_HD),
			base + NvRegMisc1);
	pci_push(base);
	ग_लिखोl(np->linkspeed, base + NvRegLinkSpeed);
	pci_push(base);
पूर्ण

/**
 * nv_update_linkspeed - Setup the MAC according to the link partner
 * @dev: Network device to be configured
 *
 * The function queries the PHY and checks अगर there is a link partner.
 * If yes, then it sets up the MAC accordingly. Otherwise, the MAC is
 * set to 10 MBit HD.
 *
 * The function वापसs 0 अगर there is no link partner and 1 अगर there is
 * a good link partner.
 */
अटल पूर्णांक nv_update_linkspeed(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	पूर्णांक adv = 0;
	पूर्णांक lpa = 0;
	पूर्णांक adv_lpa, adv_छोड़ो, lpa_छोड़ो;
	पूर्णांक newls = np->linkspeed;
	पूर्णांक newdup = np->duplex;
	पूर्णांक mii_status;
	u32 bmcr;
	पूर्णांक retval = 0;
	u32 control_1000, status_1000, phyreg, छोड़ो_flags, txreg;
	u32 txrxFlags = 0;
	u32 phy_exp;

	/* If device loopback is enabled, set carrier on and enable max link
	 * speed.
	 */
	bmcr = mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ);
	अगर (bmcr & BMCR_LOOPBACK) अणु
		अगर (netअगर_running(dev)) अणु
			nv_क्रमce_linkspeed(dev, NVREG_LINKSPEED_1000, 1);
			अगर (!netअगर_carrier_ok(dev))
				netअगर_carrier_on(dev);
		पूर्ण
		वापस 1;
	पूर्ण

	/* BMSR_LSTATUS is latched, पढ़ो it twice:
	 * we want the current value.
	 */
	mii_rw(dev, np->phyaddr, MII_BMSR, MII_READ);
	mii_status = mii_rw(dev, np->phyaddr, MII_BMSR, MII_READ);

	अगर (!(mii_status & BMSR_LSTATUS)) अणु
		newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_10;
		newdup = 0;
		retval = 0;
		जाओ set_speed;
	पूर्ण

	अगर (np->स्वतःneg == 0) अणु
		अगर (np->fixed_mode & LPA_100FULL) अणु
			newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_100;
			newdup = 1;
		पूर्ण अन्यथा अगर (np->fixed_mode & LPA_100HALF) अणु
			newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_100;
			newdup = 0;
		पूर्ण अन्यथा अगर (np->fixed_mode & LPA_10FULL) अणु
			newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_10;
			newdup = 1;
		पूर्ण अन्यथा अणु
			newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_10;
			newdup = 0;
		पूर्ण
		retval = 1;
		जाओ set_speed;
	पूर्ण
	/* check स्वतः negotiation is complete */
	अगर (!(mii_status & BMSR_ANEGCOMPLETE)) अणु
		/* still in स्वतःnegotiation - configure nic क्रम 10 MBit HD and रुको. */
		newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_10;
		newdup = 0;
		retval = 0;
		जाओ set_speed;
	पूर्ण

	adv = mii_rw(dev, np->phyaddr, MII_ADVERTISE, MII_READ);
	lpa = mii_rw(dev, np->phyaddr, MII_LPA, MII_READ);

	retval = 1;
	अगर (np->gigabit == PHY_GIGABIT) अणु
		control_1000 = mii_rw(dev, np->phyaddr, MII_CTRL1000, MII_READ);
		status_1000 = mii_rw(dev, np->phyaddr, MII_STAT1000, MII_READ);

		अगर ((control_1000 & ADVERTISE_1000FULL) &&
			(status_1000 & LPA_1000FULL)) अणु
			newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_1000;
			newdup = 1;
			जाओ set_speed;
		पूर्ण
	पूर्ण

	/* FIXME: handle parallel detection properly */
	adv_lpa = lpa & adv;
	अगर (adv_lpa & LPA_100FULL) अणु
		newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_100;
		newdup = 1;
	पूर्ण अन्यथा अगर (adv_lpa & LPA_100HALF) अणु
		newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_100;
		newdup = 0;
	पूर्ण अन्यथा अगर (adv_lpa & LPA_10FULL) अणु
		newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_10;
		newdup = 1;
	पूर्ण अन्यथा अगर (adv_lpa & LPA_10HALF) अणु
		newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_10;
		newdup = 0;
	पूर्ण अन्यथा अणु
		newls = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_10;
		newdup = 0;
	पूर्ण

set_speed:
	अगर (np->duplex == newdup && np->linkspeed == newls)
		वापस retval;

	np->duplex = newdup;
	np->linkspeed = newls;

	/* The transmitter and receiver must be restarted क्रम safe update */
	अगर (पढ़ोl(base + NvRegTransmitterControl) & NVREG_XMITCTL_START) अणु
		txrxFlags |= NV_RESTART_TX;
		nv_stop_tx(dev);
	पूर्ण
	अगर (पढ़ोl(base + NvRegReceiverControl) & NVREG_RCVCTL_START) अणु
		txrxFlags |= NV_RESTART_RX;
		nv_stop_rx(dev);
	पूर्ण

	अगर (np->gigabit == PHY_GIGABIT) अणु
		phyreg = पढ़ोl(base + NvRegSlotTime);
		phyreg &= ~(0x3FF00);
		अगर (((np->linkspeed & 0xFFF) == NVREG_LINKSPEED_10) ||
		    ((np->linkspeed & 0xFFF) == NVREG_LINKSPEED_100))
			phyreg |= NVREG_SLOTTIME_10_100_FULL;
		अन्यथा अगर ((np->linkspeed & 0xFFF) == NVREG_LINKSPEED_1000)
			phyreg |= NVREG_SLOTTIME_1000_FULL;
		ग_लिखोl(phyreg, base + NvRegSlotTime);
	पूर्ण

	phyreg = पढ़ोl(base + NvRegPhyInterface);
	phyreg &= ~(PHY_HALF|PHY_100|PHY_1000);
	अगर (np->duplex == 0)
		phyreg |= PHY_HALF;
	अगर ((np->linkspeed & NVREG_LINKSPEED_MASK) == NVREG_LINKSPEED_100)
		phyreg |= PHY_100;
	अन्यथा अगर ((np->linkspeed & NVREG_LINKSPEED_MASK) == NVREG_LINKSPEED_1000)
		phyreg |= PHY_1000;
	ग_लिखोl(phyreg, base + NvRegPhyInterface);

	phy_exp = mii_rw(dev, np->phyaddr, MII_EXPANSION, MII_READ) & EXPANSION_NWAY; /* स्वतःneg capable */
	अगर (phyreg & PHY_RGMII) अणु
		अगर ((np->linkspeed & NVREG_LINKSPEED_MASK) == NVREG_LINKSPEED_1000) अणु
			txreg = NVREG_TX_DEFERRAL_RGMII_1000;
		पूर्ण अन्यथा अणु
			अगर (!phy_exp && !np->duplex && (np->driver_data & DEV_HAS_COLLISION_FIX)) अणु
				अगर ((np->linkspeed & NVREG_LINKSPEED_MASK) == NVREG_LINKSPEED_10)
					txreg = NVREG_TX_DEFERRAL_RGMII_STRETCH_10;
				अन्यथा
					txreg = NVREG_TX_DEFERRAL_RGMII_STRETCH_100;
			पूर्ण अन्यथा अणु
				txreg = NVREG_TX_DEFERRAL_RGMII_10_100;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!phy_exp && !np->duplex && (np->driver_data & DEV_HAS_COLLISION_FIX))
			txreg = NVREG_TX_DEFERRAL_MII_STRETCH;
		अन्यथा
			txreg = NVREG_TX_DEFERRAL_DEFAULT;
	पूर्ण
	ग_लिखोl(txreg, base + NvRegTxDeferral);

	अगर (np->desc_ver == DESC_VER_1) अणु
		txreg = NVREG_TX_WM_DESC1_DEFAULT;
	पूर्ण अन्यथा अणु
		अगर ((np->linkspeed & NVREG_LINKSPEED_MASK) == NVREG_LINKSPEED_1000)
			txreg = NVREG_TX_WM_DESC2_3_1000;
		अन्यथा
			txreg = NVREG_TX_WM_DESC2_3_DEFAULT;
	पूर्ण
	ग_लिखोl(txreg, base + NvRegTxWatermark);

	ग_लिखोl(NVREG_MISC1_FORCE | (np->duplex ? 0 : NVREG_MISC1_HD),
		base + NvRegMisc1);
	pci_push(base);
	ग_लिखोl(np->linkspeed, base + NvRegLinkSpeed);
	pci_push(base);

	छोड़ो_flags = 0;
	/* setup छोड़ो frame */
	अगर (netअगर_running(dev) && (np->duplex != 0)) अणु
		अगर (np->स्वतःneg && np->छोड़ो_flags & NV_PAUSEFRAME_AUTONEG) अणु
			adv_छोड़ो = adv & (ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);
			lpa_छोड़ो = lpa & (LPA_PAUSE_CAP | LPA_PAUSE_ASYM);

			चयन (adv_छोड़ो) अणु
			हाल ADVERTISE_PAUSE_CAP:
				अगर (lpa_छोड़ो & LPA_PAUSE_CAP) अणु
					छोड़ो_flags |= NV_PAUSEFRAME_RX_ENABLE;
					अगर (np->छोड़ो_flags & NV_PAUSEFRAME_TX_REQ)
						छोड़ो_flags |= NV_PAUSEFRAME_TX_ENABLE;
				पूर्ण
				अवरोध;
			हाल ADVERTISE_PAUSE_ASYM:
				अगर (lpa_छोड़ो == (LPA_PAUSE_CAP | LPA_PAUSE_ASYM))
					छोड़ो_flags |= NV_PAUSEFRAME_TX_ENABLE;
				अवरोध;
			हाल ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM:
				अगर (lpa_छोड़ो & LPA_PAUSE_CAP) अणु
					छोड़ो_flags |=  NV_PAUSEFRAME_RX_ENABLE;
					अगर (np->छोड़ो_flags & NV_PAUSEFRAME_TX_REQ)
						छोड़ो_flags |= NV_PAUSEFRAME_TX_ENABLE;
				पूर्ण
				अगर (lpa_छोड़ो == LPA_PAUSE_ASYM)
					छोड़ो_flags |= NV_PAUSEFRAME_RX_ENABLE;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			छोड़ो_flags = np->छोड़ो_flags;
		पूर्ण
	पूर्ण
	nv_update_छोड़ो(dev, छोड़ो_flags);

	अगर (txrxFlags & NV_RESTART_TX)
		nv_start_tx(dev);
	अगर (txrxFlags & NV_RESTART_RX)
		nv_start_rx(dev);

	वापस retval;
पूर्ण

अटल व्योम nv_linkchange(काष्ठा net_device *dev)
अणु
	अगर (nv_update_linkspeed(dev)) अणु
		अगर (!netअगर_carrier_ok(dev)) अणु
			netअगर_carrier_on(dev);
			netdev_info(dev, "link up\n");
			nv_txrx_gate(dev, false);
			nv_start_rx(dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(dev)) अणु
			netअगर_carrier_off(dev);
			netdev_info(dev, "link down\n");
			nv_txrx_gate(dev, true);
			nv_stop_rx(dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nv_link_irq(काष्ठा net_device *dev)
अणु
	u8 __iomem *base = get_hwbase(dev);
	u32 miistat;

	miistat = पढ़ोl(base + NvRegMIIStatus);
	ग_लिखोl(NVREG_MIISTAT_LINKCHANGE, base + NvRegMIIStatus);

	अगर (miistat & (NVREG_MIISTAT_LINKCHANGE))
		nv_linkchange(dev);
पूर्ण

अटल व्योम nv_msi_workaround(काष्ठा fe_priv *np)
अणु

	/* Need to toggle the msi irq mask within the ethernet device,
	 * otherwise, future पूर्णांकerrupts will not be detected.
	 */
	अगर (np->msi_flags & NV_MSI_ENABLED) अणु
		u8 __iomem *base = np->base;

		ग_लिखोl(0, base + NvRegMSIIrqMask);
		ग_लिखोl(NVREG_MSI_VECTOR_0_ENABLED, base + NvRegMSIIrqMask);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक nv_change_पूर्णांकerrupt_mode(काष्ठा net_device *dev, पूर्णांक total_work)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);

	अगर (optimization_mode == NV_OPTIMIZATION_MODE_DYNAMIC) अणु
		अगर (total_work > NV_DYNAMIC_THRESHOLD) अणु
			/* transition to poll based पूर्णांकerrupts */
			np->quiet_count = 0;
			अगर (np->irqmask != NVREG_IRQMASK_CPU) अणु
				np->irqmask = NVREG_IRQMASK_CPU;
				वापस 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (np->quiet_count < NV_DYNAMIC_MAX_QUIET_COUNT) अणु
				np->quiet_count++;
			पूर्ण अन्यथा अणु
				/* reached a period of low activity, चयन
				   to per tx/rx packet पूर्णांकerrupts */
				अगर (np->irqmask != NVREG_IRQMASK_THROUGHPUT) अणु
					np->irqmask = NVREG_IRQMASK_THROUGHPUT;
					वापस 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t nv_nic_irq(पूर्णांक foo, व्योम *data)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) data;
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);

	अगर (!(np->msi_flags & NV_MSI_X_ENABLED)) अणु
		np->events = पढ़ोl(base + NvRegIrqStatus);
		ग_लिखोl(np->events, base + NvRegIrqStatus);
	पूर्ण अन्यथा अणु
		np->events = पढ़ोl(base + NvRegMSIXIrqStatus);
		ग_लिखोl(np->events, base + NvRegMSIXIrqStatus);
	पूर्ण
	अगर (!(np->events & np->irqmask))
		वापस IRQ_NONE;

	nv_msi_workaround(np);

	अगर (napi_schedule_prep(&np->napi)) अणु
		/*
		 * Disable further irq's (msix not enabled with napi)
		 */
		ग_लिखोl(0, base + NvRegIrqMask);
		__napi_schedule(&np->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* All _optimized functions are used to help increase perक्रमmance
 * (reduce CPU and increase throughput). They use descripter version 3,
 * compiler directives, and reduce memory accesses.
 */
अटल irqवापस_t nv_nic_irq_optimized(पूर्णांक foo, व्योम *data)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) data;
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);

	अगर (!(np->msi_flags & NV_MSI_X_ENABLED)) अणु
		np->events = पढ़ोl(base + NvRegIrqStatus);
		ग_लिखोl(np->events, base + NvRegIrqStatus);
	पूर्ण अन्यथा अणु
		np->events = पढ़ोl(base + NvRegMSIXIrqStatus);
		ग_लिखोl(np->events, base + NvRegMSIXIrqStatus);
	पूर्ण
	अगर (!(np->events & np->irqmask))
		वापस IRQ_NONE;

	nv_msi_workaround(np);

	अगर (napi_schedule_prep(&np->napi)) अणु
		/*
		 * Disable further irq's (msix not enabled with napi)
		 */
		ग_लिखोl(0, base + NvRegIrqMask);
		__napi_schedule(&np->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t nv_nic_irq_tx(पूर्णांक foo, व्योम *data)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) data;
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 events;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0;; i++) अणु
		events = पढ़ोl(base + NvRegMSIXIrqStatus) & NVREG_IRQ_TX_ALL;
		ग_लिखोl(events, base + NvRegMSIXIrqStatus);
		netdev_dbg(dev, "tx irq events: %08x\n", events);
		अगर (!(events & np->irqmask))
			अवरोध;

		spin_lock_irqsave(&np->lock, flags);
		nv_tx_करोne_optimized(dev, TX_WORK_PER_LOOP);
		spin_unlock_irqrestore(&np->lock, flags);

		अगर (unlikely(i > max_पूर्णांकerrupt_work)) अणु
			spin_lock_irqsave(&np->lock, flags);
			/* disable पूर्णांकerrupts on the nic */
			ग_लिखोl(NVREG_IRQ_TX_ALL, base + NvRegIrqMask);
			pci_push(base);

			अगर (!np->in_shutकरोwn) अणु
				np->nic_poll_irq |= NVREG_IRQ_TX_ALL;
				mod_समयr(&np->nic_poll, jअगरfies + POLL_WAIT);
			पूर्ण
			spin_unlock_irqrestore(&np->lock, flags);
			netdev_dbg(dev, "%s: too many iterations (%d)\n",
				   __func__, i);
			अवरोध;
		पूर्ण

	पूर्ण

	वापस IRQ_RETVAL(i);
पूर्ण

अटल पूर्णांक nv_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा fe_priv *np = container_of(napi, काष्ठा fe_priv, napi);
	काष्ठा net_device *dev = np->dev;
	u8 __iomem *base = get_hwbase(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक retcode;
	पूर्णांक rx_count, tx_work = 0, rx_work = 0;

	करो अणु
		अगर (!nv_optimized(np)) अणु
			spin_lock_irqsave(&np->lock, flags);
			tx_work += nv_tx_करोne(dev, np->tx_ring_size);
			spin_unlock_irqrestore(&np->lock, flags);

			rx_count = nv_rx_process(dev, budget - rx_work);
			retcode = nv_alloc_rx(dev);
		पूर्ण अन्यथा अणु
			spin_lock_irqsave(&np->lock, flags);
			tx_work += nv_tx_करोne_optimized(dev, np->tx_ring_size);
			spin_unlock_irqrestore(&np->lock, flags);

			rx_count = nv_rx_process_optimized(dev,
			    budget - rx_work);
			retcode = nv_alloc_rx_optimized(dev);
		पूर्ण
	पूर्ण जबतक (retcode == 0 &&
		 rx_count > 0 && (rx_work += rx_count) < budget);

	अगर (retcode) अणु
		spin_lock_irqsave(&np->lock, flags);
		अगर (!np->in_shutकरोwn)
			mod_समयr(&np->oom_kick, jअगरfies + OOM_REFILL);
		spin_unlock_irqrestore(&np->lock, flags);
	पूर्ण

	nv_change_पूर्णांकerrupt_mode(dev, tx_work + rx_work);

	अगर (unlikely(np->events & NVREG_IRQ_LINK)) अणु
		spin_lock_irqsave(&np->lock, flags);
		nv_link_irq(dev);
		spin_unlock_irqrestore(&np->lock, flags);
	पूर्ण
	अगर (unlikely(np->need_linkसमयr && समय_after(jअगरfies, np->link_समयout))) अणु
		spin_lock_irqsave(&np->lock, flags);
		nv_linkchange(dev);
		spin_unlock_irqrestore(&np->lock, flags);
		np->link_समयout = jअगरfies + LINK_TIMEOUT;
	पूर्ण
	अगर (unlikely(np->events & NVREG_IRQ_RECOVER_ERROR)) अणु
		spin_lock_irqsave(&np->lock, flags);
		अगर (!np->in_shutकरोwn) अणु
			np->nic_poll_irq = np->irqmask;
			np->recover_error = 1;
			mod_समयr(&np->nic_poll, jअगरfies + POLL_WAIT);
		पूर्ण
		spin_unlock_irqrestore(&np->lock, flags);
		napi_complete(napi);
		वापस rx_work;
	पूर्ण

	अगर (rx_work < budget) अणु
		/* re-enable पूर्णांकerrupts
		   (msix not enabled in napi) */
		napi_complete_करोne(napi, rx_work);

		ग_लिखोl(np->irqmask, base + NvRegIrqMask);
	पूर्ण
	वापस rx_work;
पूर्ण

अटल irqवापस_t nv_nic_irq_rx(पूर्णांक foo, व्योम *data)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) data;
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 events;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0;; i++) अणु
		events = पढ़ोl(base + NvRegMSIXIrqStatus) & NVREG_IRQ_RX_ALL;
		ग_लिखोl(events, base + NvRegMSIXIrqStatus);
		netdev_dbg(dev, "rx irq events: %08x\n", events);
		अगर (!(events & np->irqmask))
			अवरोध;

		अगर (nv_rx_process_optimized(dev, RX_WORK_PER_LOOP)) अणु
			अगर (unlikely(nv_alloc_rx_optimized(dev))) अणु
				spin_lock_irqsave(&np->lock, flags);
				अगर (!np->in_shutकरोwn)
					mod_समयr(&np->oom_kick, jअगरfies + OOM_REFILL);
				spin_unlock_irqrestore(&np->lock, flags);
			पूर्ण
		पूर्ण

		अगर (unlikely(i > max_पूर्णांकerrupt_work)) अणु
			spin_lock_irqsave(&np->lock, flags);
			/* disable पूर्णांकerrupts on the nic */
			ग_लिखोl(NVREG_IRQ_RX_ALL, base + NvRegIrqMask);
			pci_push(base);

			अगर (!np->in_shutकरोwn) अणु
				np->nic_poll_irq |= NVREG_IRQ_RX_ALL;
				mod_समयr(&np->nic_poll, jअगरfies + POLL_WAIT);
			पूर्ण
			spin_unlock_irqrestore(&np->lock, flags);
			netdev_dbg(dev, "%s: too many iterations (%d)\n",
				   __func__, i);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस IRQ_RETVAL(i);
पूर्ण

अटल irqवापस_t nv_nic_irq_other(पूर्णांक foo, व्योम *data)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) data;
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 events;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0;; i++) अणु
		events = पढ़ोl(base + NvRegMSIXIrqStatus) & NVREG_IRQ_OTHER;
		ग_लिखोl(events, base + NvRegMSIXIrqStatus);
		netdev_dbg(dev, "irq events: %08x\n", events);
		अगर (!(events & np->irqmask))
			अवरोध;

		/* check tx in हाल we reached max loop limit in tx isr */
		spin_lock_irqsave(&np->lock, flags);
		nv_tx_करोne_optimized(dev, TX_WORK_PER_LOOP);
		spin_unlock_irqrestore(&np->lock, flags);

		अगर (events & NVREG_IRQ_LINK) अणु
			spin_lock_irqsave(&np->lock, flags);
			nv_link_irq(dev);
			spin_unlock_irqrestore(&np->lock, flags);
		पूर्ण
		अगर (np->need_linkसमयr && समय_after(jअगरfies, np->link_समयout)) अणु
			spin_lock_irqsave(&np->lock, flags);
			nv_linkchange(dev);
			spin_unlock_irqrestore(&np->lock, flags);
			np->link_समयout = jअगरfies + LINK_TIMEOUT;
		पूर्ण
		अगर (events & NVREG_IRQ_RECOVER_ERROR) अणु
			spin_lock_irqsave(&np->lock, flags);
			/* disable पूर्णांकerrupts on the nic */
			ग_लिखोl(NVREG_IRQ_OTHER, base + NvRegIrqMask);
			pci_push(base);

			अगर (!np->in_shutकरोwn) अणु
				np->nic_poll_irq |= NVREG_IRQ_OTHER;
				np->recover_error = 1;
				mod_समयr(&np->nic_poll, jअगरfies + POLL_WAIT);
			पूर्ण
			spin_unlock_irqrestore(&np->lock, flags);
			अवरोध;
		पूर्ण
		अगर (unlikely(i > max_पूर्णांकerrupt_work)) अणु
			spin_lock_irqsave(&np->lock, flags);
			/* disable पूर्णांकerrupts on the nic */
			ग_लिखोl(NVREG_IRQ_OTHER, base + NvRegIrqMask);
			pci_push(base);

			अगर (!np->in_shutकरोwn) अणु
				np->nic_poll_irq |= NVREG_IRQ_OTHER;
				mod_समयr(&np->nic_poll, jअगरfies + POLL_WAIT);
			पूर्ण
			spin_unlock_irqrestore(&np->lock, flags);
			netdev_dbg(dev, "%s: too many iterations (%d)\n",
				   __func__, i);
			अवरोध;
		पूर्ण

	पूर्ण

	वापस IRQ_RETVAL(i);
पूर्ण

अटल irqवापस_t nv_nic_irq_test(पूर्णांक foo, व्योम *data)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) data;
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 events;

	अगर (!(np->msi_flags & NV_MSI_X_ENABLED)) अणु
		events = पढ़ोl(base + NvRegIrqStatus) & NVREG_IRQSTAT_MASK;
		ग_लिखोl(events & NVREG_IRQ_TIMER, base + NvRegIrqStatus);
	पूर्ण अन्यथा अणु
		events = पढ़ोl(base + NvRegMSIXIrqStatus) & NVREG_IRQSTAT_MASK;
		ग_लिखोl(events & NVREG_IRQ_TIMER, base + NvRegMSIXIrqStatus);
	पूर्ण
	pci_push(base);
	अगर (!(events & NVREG_IRQ_TIMER))
		वापस IRQ_RETVAL(0);

	nv_msi_workaround(np);

	spin_lock(&np->lock);
	np->पूर्णांकr_test = 1;
	spin_unlock(&np->lock);

	वापस IRQ_RETVAL(1);
पूर्ण

अटल व्योम set_msix_vector_map(काष्ठा net_device *dev, u32 vector, u32 irqmask)
अणु
	u8 __iomem *base = get_hwbase(dev);
	पूर्णांक i;
	u32 msixmap = 0;

	/* Each पूर्णांकerrupt bit can be mapped to a MSIX vector (4 bits).
	 * MSIXMap0 represents the first 8 पूर्णांकerrupts and MSIXMap1 represents
	 * the reमुख्यing 8 पूर्णांकerrupts.
	 */
	क्रम (i = 0; i < 8; i++) अणु
		अगर ((irqmask >> i) & 0x1)
			msixmap |= vector << (i << 2);
	पूर्ण
	ग_लिखोl(पढ़ोl(base + NvRegMSIXMap0) | msixmap, base + NvRegMSIXMap0);

	msixmap = 0;
	क्रम (i = 0; i < 8; i++) अणु
		अगर ((irqmask >> (i + 8)) & 0x1)
			msixmap |= vector << (i << 2);
	पूर्ण
	ग_लिखोl(पढ़ोl(base + NvRegMSIXMap1) | msixmap, base + NvRegMSIXMap1);
पूर्ण

अटल पूर्णांक nv_request_irq(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_test)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);
	u8 __iomem *base = get_hwbase(dev);
	पूर्णांक ret;
	पूर्णांक i;
	irqवापस_t (*handler)(पूर्णांक foo, व्योम *data);

	अगर (पूर्णांकr_test) अणु
		handler = nv_nic_irq_test;
	पूर्ण अन्यथा अणु
		अगर (nv_optimized(np))
			handler = nv_nic_irq_optimized;
		अन्यथा
			handler = nv_nic_irq;
	पूर्ण

	अगर (np->msi_flags & NV_MSI_X_CAPABLE) अणु
		क्रम (i = 0; i < (np->msi_flags & NV_MSI_X_VECTORS_MASK); i++)
			np->msi_x_entry[i].entry = i;
		ret = pci_enable_msix_range(np->pci_dev,
					    np->msi_x_entry,
					    np->msi_flags & NV_MSI_X_VECTORS_MASK,
					    np->msi_flags & NV_MSI_X_VECTORS_MASK);
		अगर (ret > 0) अणु
			np->msi_flags |= NV_MSI_X_ENABLED;
			अगर (optimization_mode == NV_OPTIMIZATION_MODE_THROUGHPUT && !पूर्णांकr_test) अणु
				/* Request irq क्रम rx handling */
				प्र_लिखो(np->name_rx, "%s-rx", dev->name);
				ret = request_irq(np->msi_x_entry[NV_MSI_X_VECTOR_RX].vector,
						  nv_nic_irq_rx, IRQF_SHARED, np->name_rx, dev);
				अगर (ret) अणु
					netdev_info(dev,
						    "request_irq failed for rx %d\n",
						    ret);
					pci_disable_msix(np->pci_dev);
					np->msi_flags &= ~NV_MSI_X_ENABLED;
					जाओ out_err;
				पूर्ण
				/* Request irq क्रम tx handling */
				प्र_लिखो(np->name_tx, "%s-tx", dev->name);
				ret = request_irq(np->msi_x_entry[NV_MSI_X_VECTOR_TX].vector,
						  nv_nic_irq_tx, IRQF_SHARED, np->name_tx, dev);
				अगर (ret) अणु
					netdev_info(dev,
						    "request_irq failed for tx %d\n",
						    ret);
					pci_disable_msix(np->pci_dev);
					np->msi_flags &= ~NV_MSI_X_ENABLED;
					जाओ out_मुक्त_rx;
				पूर्ण
				/* Request irq क्रम link and समयr handling */
				प्र_लिखो(np->name_other, "%s-other", dev->name);
				ret = request_irq(np->msi_x_entry[NV_MSI_X_VECTOR_OTHER].vector,
						  nv_nic_irq_other, IRQF_SHARED, np->name_other, dev);
				अगर (ret) अणु
					netdev_info(dev,
						    "request_irq failed for link %d\n",
						    ret);
					pci_disable_msix(np->pci_dev);
					np->msi_flags &= ~NV_MSI_X_ENABLED;
					जाओ out_मुक्त_tx;
				पूर्ण
				/* map पूर्णांकerrupts to their respective vector */
				ग_लिखोl(0, base + NvRegMSIXMap0);
				ग_लिखोl(0, base + NvRegMSIXMap1);
				set_msix_vector_map(dev, NV_MSI_X_VECTOR_RX, NVREG_IRQ_RX_ALL);
				set_msix_vector_map(dev, NV_MSI_X_VECTOR_TX, NVREG_IRQ_TX_ALL);
				set_msix_vector_map(dev, NV_MSI_X_VECTOR_OTHER, NVREG_IRQ_OTHER);
			पूर्ण अन्यथा अणु
				/* Request irq क्रम all पूर्णांकerrupts */
				ret = request_irq(np->msi_x_entry[NV_MSI_X_VECTOR_ALL].vector,
						  handler, IRQF_SHARED, dev->name, dev);
				अगर (ret) अणु
					netdev_info(dev,
						    "request_irq failed %d\n",
						    ret);
					pci_disable_msix(np->pci_dev);
					np->msi_flags &= ~NV_MSI_X_ENABLED;
					जाओ out_err;
				पूर्ण

				/* map पूर्णांकerrupts to vector 0 */
				ग_लिखोl(0, base + NvRegMSIXMap0);
				ग_लिखोl(0, base + NvRegMSIXMap1);
			पूर्ण
			netdev_info(dev, "MSI-X enabled\n");
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (np->msi_flags & NV_MSI_CAPABLE) अणु
		ret = pci_enable_msi(np->pci_dev);
		अगर (ret == 0) अणु
			np->msi_flags |= NV_MSI_ENABLED;
			ret = request_irq(np->pci_dev->irq, handler, IRQF_SHARED, dev->name, dev);
			अगर (ret) अणु
				netdev_info(dev, "request_irq failed %d\n",
					    ret);
				pci_disable_msi(np->pci_dev);
				np->msi_flags &= ~NV_MSI_ENABLED;
				जाओ out_err;
			पूर्ण

			/* map पूर्णांकerrupts to vector 0 */
			ग_लिखोl(0, base + NvRegMSIMap0);
			ग_लिखोl(0, base + NvRegMSIMap1);
			/* enable msi vector 0 */
			ग_लिखोl(NVREG_MSI_VECTOR_0_ENABLED, base + NvRegMSIIrqMask);
			netdev_info(dev, "MSI enabled\n");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (request_irq(np->pci_dev->irq, handler, IRQF_SHARED, dev->name, dev) != 0)
		जाओ out_err;

	वापस 0;
out_मुक्त_tx:
	मुक्त_irq(np->msi_x_entry[NV_MSI_X_VECTOR_TX].vector, dev);
out_मुक्त_rx:
	मुक्त_irq(np->msi_x_entry[NV_MSI_X_VECTOR_RX].vector, dev);
out_err:
	वापस 1;
पूर्ण

अटल व्योम nv_मुक्त_irq(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);
	पूर्णांक i;

	अगर (np->msi_flags & NV_MSI_X_ENABLED) अणु
		क्रम (i = 0; i < (np->msi_flags & NV_MSI_X_VECTORS_MASK); i++)
			मुक्त_irq(np->msi_x_entry[i].vector, dev);
		pci_disable_msix(np->pci_dev);
		np->msi_flags &= ~NV_MSI_X_ENABLED;
	पूर्ण अन्यथा अणु
		मुक्त_irq(np->pci_dev->irq, dev);
		अगर (np->msi_flags & NV_MSI_ENABLED) अणु
			pci_disable_msi(np->pci_dev);
			np->msi_flags &= ~NV_MSI_ENABLED;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nv_करो_nic_poll(काष्ठा समयr_list *t)
अणु
	काष्ठा fe_priv *np = from_समयr(np, t, nic_poll);
	काष्ठा net_device *dev = np->dev;
	u8 __iomem *base = get_hwbase(dev);
	u32 mask = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक irq = 0;

	/*
	 * First disable irq(s) and then
	 * reenable पूर्णांकerrupts on the nic, we have to करो this beक्रमe calling
	 * nv_nic_irq because that may decide to करो otherwise
	 */

	अगर (!using_multi_irqs(dev)) अणु
		अगर (np->msi_flags & NV_MSI_X_ENABLED)
			irq = np->msi_x_entry[NV_MSI_X_VECTOR_ALL].vector;
		अन्यथा
			irq = np->pci_dev->irq;
		mask = np->irqmask;
	पूर्ण अन्यथा अणु
		अगर (np->nic_poll_irq & NVREG_IRQ_RX_ALL) अणु
			irq = np->msi_x_entry[NV_MSI_X_VECTOR_RX].vector;
			mask |= NVREG_IRQ_RX_ALL;
		पूर्ण
		अगर (np->nic_poll_irq & NVREG_IRQ_TX_ALL) अणु
			irq = np->msi_x_entry[NV_MSI_X_VECTOR_TX].vector;
			mask |= NVREG_IRQ_TX_ALL;
		पूर्ण
		अगर (np->nic_poll_irq & NVREG_IRQ_OTHER) अणु
			irq = np->msi_x_entry[NV_MSI_X_VECTOR_OTHER].vector;
			mask |= NVREG_IRQ_OTHER;
		पूर्ण
	पूर्ण

	disable_irq_nosync_lockdep_irqsave(irq, &flags);
	synchronize_irq(irq);

	अगर (np->recover_error) अणु
		np->recover_error = 0;
		netdev_info(dev, "MAC in recoverable error state\n");
		अगर (netअगर_running(dev)) अणु
			netअगर_tx_lock_bh(dev);
			netअगर_addr_lock(dev);
			spin_lock(&np->lock);
			/* stop engines */
			nv_stop_rxtx(dev);
			अगर (np->driver_data & DEV_HAS_POWER_CNTRL)
				nv_mac_reset(dev);
			nv_txrx_reset(dev);
			/* drain rx queue */
			nv_drain_rxtx(dev);
			/* reinit driver view of the rx queue */
			set_bufsize(dev);
			अगर (nv_init_ring(dev)) अणु
				अगर (!np->in_shutकरोwn)
					mod_समयr(&np->oom_kick, jअगरfies + OOM_REFILL);
			पूर्ण
			/* reinit nic view of the rx queue */
			ग_लिखोl(np->rx_buf_sz, base + NvRegOffloadConfig);
			setup_hw_rings(dev, NV_SETUP_RX_RING | NV_SETUP_TX_RING);
			ग_लिखोl(((np->rx_ring_size-1) << NVREG_RINGSZ_RXSHIFT) + ((np->tx_ring_size-1) << NVREG_RINGSZ_TXSHIFT),
				base + NvRegRingSizes);
			pci_push(base);
			ग_लिखोl(NVREG_TXRXCTL_KICK|np->txrxctl_bits, get_hwbase(dev) + NvRegTxRxControl);
			pci_push(base);
			/* clear पूर्णांकerrupts */
			अगर (!(np->msi_flags & NV_MSI_X_ENABLED))
				ग_लिखोl(NVREG_IRQSTAT_MASK, base + NvRegIrqStatus);
			अन्यथा
				ग_लिखोl(NVREG_IRQSTAT_MASK, base + NvRegMSIXIrqStatus);

			/* restart rx engine */
			nv_start_rxtx(dev);
			spin_unlock(&np->lock);
			netअगर_addr_unlock(dev);
			netअगर_tx_unlock_bh(dev);
		पूर्ण
	पूर्ण

	ग_लिखोl(mask, base + NvRegIrqMask);
	pci_push(base);

	अगर (!using_multi_irqs(dev)) अणु
		np->nic_poll_irq = 0;
		अगर (nv_optimized(np))
			nv_nic_irq_optimized(0, dev);
		अन्यथा
			nv_nic_irq(0, dev);
	पूर्ण अन्यथा अणु
		अगर (np->nic_poll_irq & NVREG_IRQ_RX_ALL) अणु
			np->nic_poll_irq &= ~NVREG_IRQ_RX_ALL;
			nv_nic_irq_rx(0, dev);
		पूर्ण
		अगर (np->nic_poll_irq & NVREG_IRQ_TX_ALL) अणु
			np->nic_poll_irq &= ~NVREG_IRQ_TX_ALL;
			nv_nic_irq_tx(0, dev);
		पूर्ण
		अगर (np->nic_poll_irq & NVREG_IRQ_OTHER) अणु
			np->nic_poll_irq &= ~NVREG_IRQ_OTHER;
			nv_nic_irq_other(0, dev);
		पूर्ण
	पूर्ण

	enable_irq_lockdep_irqrestore(irq, &flags);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम nv_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);

	nv_करो_nic_poll(&np->nic_poll);
पूर्ण
#पूर्ण_अगर

अटल व्योम nv_करो_stats_poll(काष्ठा समयr_list *t)
	__acquires(&netdev_priv(dev)->hwstats_lock)
	__releases(&netdev_priv(dev)->hwstats_lock)
अणु
	काष्ठा fe_priv *np = from_समयr(np, t, stats_poll);
	काष्ठा net_device *dev = np->dev;

	/* If lock is currently taken, the stats are being refreshed
	 * and hence fresh enough */
	अगर (spin_trylock(&np->hwstats_lock)) अणु
		nv_update_stats(dev);
		spin_unlock(&np->hwstats_lock);
	पूर्ण

	अगर (!np->in_shutकरोwn)
		mod_समयr(&np->stats_poll,
			round_jअगरfies(jअगरfies + STATS_INTERVAL));
पूर्ण

अटल व्योम nv_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, FORCEDETH_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(np->pci_dev), माप(info->bus_info));
पूर्ण

अटल व्योम nv_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	wolinfo->supported = WAKE_MAGIC;

	spin_lock_irq(&np->lock);
	अगर (np->wolenabled)
		wolinfo->wolopts = WAKE_MAGIC;
	spin_unlock_irq(&np->lock);
पूर्ण

अटल पूर्णांक nv_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 flags = 0;

	अगर (wolinfo->wolopts == 0) अणु
		np->wolenabled = 0;
	पूर्ण अन्यथा अगर (wolinfo->wolopts & WAKE_MAGIC) अणु
		np->wolenabled = 1;
		flags = NVREG_WAKEUPFLAGS_ENABLE;
	पूर्ण
	अगर (netअगर_running(dev)) अणु
		spin_lock_irq(&np->lock);
		ग_लिखोl(flags, base + NvRegWakeUpFlags);
		spin_unlock_irq(&np->lock);
	पूर्ण
	device_set_wakeup_enable(&np->pci_dev->dev, np->wolenabled);
	वापस 0;
पूर्ण

अटल पूर्णांक nv_get_link_ksettings(काष्ठा net_device *dev,
				 काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u32 speed, supported, advertising;
	पूर्णांक adv;

	spin_lock_irq(&np->lock);
	cmd->base.port = PORT_MII;
	अगर (!netअगर_running(dev)) अणु
		/* We करो not track link speed / duplex setting अगर the
		 * पूर्णांकerface is disabled. Force a link check */
		अगर (nv_update_linkspeed(dev)) अणु
			netअगर_carrier_on(dev);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(dev);
		पूर्ण
	पूर्ण

	अगर (netअगर_carrier_ok(dev)) अणु
		चयन (np->linkspeed & (NVREG_LINKSPEED_MASK)) अणु
		हाल NVREG_LINKSPEED_10:
			speed = SPEED_10;
			अवरोध;
		हाल NVREG_LINKSPEED_100:
			speed = SPEED_100;
			अवरोध;
		हाल NVREG_LINKSPEED_1000:
			speed = SPEED_1000;
			अवरोध;
		शेष:
			speed = -1;
			अवरोध;
		पूर्ण
		cmd->base.duplex = DUPLEX_HALF;
		अगर (np->duplex)
			cmd->base.duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण
	cmd->base.speed = speed;
	cmd->base.स्वतःneg = np->स्वतःneg;

	advertising = ADVERTISED_MII;
	अगर (np->स्वतःneg) अणु
		advertising |= ADVERTISED_Autoneg;
		adv = mii_rw(dev, np->phyaddr, MII_ADVERTISE, MII_READ);
		अगर (adv & ADVERTISE_10HALF)
			advertising |= ADVERTISED_10baseT_Half;
		अगर (adv & ADVERTISE_10FULL)
			advertising |= ADVERTISED_10baseT_Full;
		अगर (adv & ADVERTISE_100HALF)
			advertising |= ADVERTISED_100baseT_Half;
		अगर (adv & ADVERTISE_100FULL)
			advertising |= ADVERTISED_100baseT_Full;
		अगर (np->gigabit == PHY_GIGABIT) अणु
			adv = mii_rw(dev, np->phyaddr, MII_CTRL1000, MII_READ);
			अगर (adv & ADVERTISE_1000FULL)
				advertising |= ADVERTISED_1000baseT_Full;
		पूर्ण
	पूर्ण
	supported = (SUPPORTED_Autoneg |
		SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
		SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
		SUPPORTED_MII);
	अगर (np->gigabit == PHY_GIGABIT)
		supported |= SUPPORTED_1000baseT_Full;

	cmd->base.phy_address = np->phyaddr;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	/* ignore maxtxpkt, maxrxpkt क्रम now */
	spin_unlock_irq(&np->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक nv_set_link_ksettings(काष्ठा net_device *dev,
				 स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (cmd->base.port != PORT_MII)
		वापस -EINVAL;
	अगर (cmd->base.phy_address != np->phyaddr) अणु
		/* TODO: support चयनing between multiple phys. Should be
		 * trivial, but not enabled due to lack of test hardware. */
		वापस -EINVAL;
	पूर्ण
	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		u32 mask;

		mask = ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full |
			  ADVERTISED_100baseT_Half | ADVERTISED_100baseT_Full;
		अगर (np->gigabit == PHY_GIGABIT)
			mask |= ADVERTISED_1000baseT_Full;

		अगर ((advertising & mask) == 0)
			वापस -EINVAL;

	पूर्ण अन्यथा अगर (cmd->base.स्वतःneg == AUTONEG_DISABLE) अणु
		/* Note: स्वतःnegotiation disable, speed 1000 पूर्णांकentionally
		 * क्रमbidden - no one should need that. */

		अगर (speed != SPEED_10 && speed != SPEED_100)
			वापस -EINVAL;
		अगर (cmd->base.duplex != DUPLEX_HALF &&
		    cmd->base.duplex != DUPLEX_FULL)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	netअगर_carrier_off(dev);
	अगर (netअगर_running(dev)) अणु
		अचिन्हित दीर्घ flags;

		nv_disable_irq(dev);
		netअगर_tx_lock_bh(dev);
		netअगर_addr_lock(dev);
		/* with plain spinlock lockdep complains */
		spin_lock_irqsave(&np->lock, flags);
		/* stop engines */
		/* FIXME:
		 * this can take some समय, and पूर्णांकerrupts are disabled
		 * due to spin_lock_irqsave, but let's hope no daemon
		 * is going to change the settings very often...
		 * Worst हाल:
		 * NV_RXSTOP_DELAY1MAX + NV_TXSTOP_DELAY1MAX
		 * + some minor delays, which is up to a second approximately
		 */
		nv_stop_rxtx(dev);
		spin_unlock_irqrestore(&np->lock, flags);
		netअगर_addr_unlock(dev);
		netअगर_tx_unlock_bh(dev);
	पूर्ण

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		पूर्णांक adv, bmcr;

		np->स्वतःneg = 1;

		/* advertise only what has been requested */
		adv = mii_rw(dev, np->phyaddr, MII_ADVERTISE, MII_READ);
		adv &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4 | ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);
		अगर (advertising & ADVERTISED_10baseT_Half)
			adv |= ADVERTISE_10HALF;
		अगर (advertising & ADVERTISED_10baseT_Full)
			adv |= ADVERTISE_10FULL;
		अगर (advertising & ADVERTISED_100baseT_Half)
			adv |= ADVERTISE_100HALF;
		अगर (advertising & ADVERTISED_100baseT_Full)
			adv |= ADVERTISE_100FULL;
		अगर (np->छोड़ो_flags & NV_PAUSEFRAME_RX_REQ)  /* क्रम rx we set both advertisements but disable tx छोड़ो */
			adv |=  ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
		अगर (np->छोड़ो_flags & NV_PAUSEFRAME_TX_REQ)
			adv |=  ADVERTISE_PAUSE_ASYM;
		mii_rw(dev, np->phyaddr, MII_ADVERTISE, adv);

		अगर (np->gigabit == PHY_GIGABIT) अणु
			adv = mii_rw(dev, np->phyaddr, MII_CTRL1000, MII_READ);
			adv &= ~ADVERTISE_1000FULL;
			अगर (advertising & ADVERTISED_1000baseT_Full)
				adv |= ADVERTISE_1000FULL;
			mii_rw(dev, np->phyaddr, MII_CTRL1000, adv);
		पूर्ण

		अगर (netअगर_running(dev))
			netdev_info(dev, "link down\n");
		bmcr = mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ);
		अगर (np->phy_model == PHY_MODEL_MARVELL_E3016) अणु
			bmcr |= BMCR_ANENABLE;
			/* reset the phy in order क्रम settings to stick,
			 * and cause स्वतःneg to start */
			अगर (phy_reset(dev, bmcr)) अणु
				netdev_info(dev, "phy reset failed\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
			mii_rw(dev, np->phyaddr, MII_BMCR, bmcr);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक adv, bmcr;

		np->स्वतःneg = 0;

		adv = mii_rw(dev, np->phyaddr, MII_ADVERTISE, MII_READ);
		adv &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4 | ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);
		अगर (speed == SPEED_10 && cmd->base.duplex == DUPLEX_HALF)
			adv |= ADVERTISE_10HALF;
		अगर (speed == SPEED_10 && cmd->base.duplex == DUPLEX_FULL)
			adv |= ADVERTISE_10FULL;
		अगर (speed == SPEED_100 && cmd->base.duplex == DUPLEX_HALF)
			adv |= ADVERTISE_100HALF;
		अगर (speed == SPEED_100 && cmd->base.duplex == DUPLEX_FULL)
			adv |= ADVERTISE_100FULL;
		np->छोड़ो_flags &= ~(NV_PAUSEFRAME_AUTONEG|NV_PAUSEFRAME_RX_ENABLE|NV_PAUSEFRAME_TX_ENABLE);
		अगर (np->छोड़ो_flags & NV_PAUSEFRAME_RX_REQ) अणु/* क्रम rx we set both advertisements but disable tx छोड़ो */
			adv |=  ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
			np->छोड़ो_flags |= NV_PAUSEFRAME_RX_ENABLE;
		पूर्ण
		अगर (np->छोड़ो_flags & NV_PAUSEFRAME_TX_REQ) अणु
			adv |=  ADVERTISE_PAUSE_ASYM;
			np->छोड़ो_flags |= NV_PAUSEFRAME_TX_ENABLE;
		पूर्ण
		mii_rw(dev, np->phyaddr, MII_ADVERTISE, adv);
		np->fixed_mode = adv;

		अगर (np->gigabit == PHY_GIGABIT) अणु
			adv = mii_rw(dev, np->phyaddr, MII_CTRL1000, MII_READ);
			adv &= ~ADVERTISE_1000FULL;
			mii_rw(dev, np->phyaddr, MII_CTRL1000, adv);
		पूर्ण

		bmcr = mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ);
		bmcr &= ~(BMCR_ANENABLE|BMCR_SPEED100|BMCR_SPEED1000|BMCR_FULLDPLX);
		अगर (np->fixed_mode & (ADVERTISE_10FULL|ADVERTISE_100FULL))
			bmcr |= BMCR_FULLDPLX;
		अगर (np->fixed_mode & (ADVERTISE_100HALF|ADVERTISE_100FULL))
			bmcr |= BMCR_SPEED100;
		अगर (np->phy_oui == PHY_OUI_MARVELL) अणु
			/* reset the phy in order क्रम क्रमced mode settings to stick */
			अगर (phy_reset(dev, bmcr)) अणु
				netdev_info(dev, "phy reset failed\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			mii_rw(dev, np->phyaddr, MII_BMCR, bmcr);
			अगर (netअगर_running(dev)) अणु
				/* Wait a bit and then reconfigure the nic. */
				udelay(10);
				nv_linkchange(dev);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		nv_start_rxtx(dev);
		nv_enable_irq(dev);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा FORCEDETH_REGS_VER	1

अटल पूर्णांक nv_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	वापस np->रेजिस्टर_size;
पूर्ण

अटल व्योम nv_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs, व्योम *buf)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 *rbuf = buf;
	पूर्णांक i;

	regs->version = FORCEDETH_REGS_VER;
	spin_lock_irq(&np->lock);
	क्रम (i = 0; i < np->रेजिस्टर_size/माप(u32); i++)
		rbuf[i] = पढ़ोl(base + i*माप(u32));
	spin_unlock_irq(&np->lock);
पूर्ण

अटल पूर्णांक nv_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	पूर्णांक ret;

	अगर (np->स्वतःneg) अणु
		पूर्णांक bmcr;

		netअगर_carrier_off(dev);
		अगर (netअगर_running(dev)) अणु
			nv_disable_irq(dev);
			netअगर_tx_lock_bh(dev);
			netअगर_addr_lock(dev);
			spin_lock(&np->lock);
			/* stop engines */
			nv_stop_rxtx(dev);
			spin_unlock(&np->lock);
			netअगर_addr_unlock(dev);
			netअगर_tx_unlock_bh(dev);
			netdev_info(dev, "link down\n");
		पूर्ण

		bmcr = mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ);
		अगर (np->phy_model == PHY_MODEL_MARVELL_E3016) अणु
			bmcr |= BMCR_ANENABLE;
			/* reset the phy in order क्रम settings to stick*/
			अगर (phy_reset(dev, bmcr)) अणु
				netdev_info(dev, "phy reset failed\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
			mii_rw(dev, np->phyaddr, MII_BMCR, bmcr);
		पूर्ण

		अगर (netअगर_running(dev)) अणु
			nv_start_rxtx(dev);
			nv_enable_irq(dev);
		पूर्ण
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम nv_get_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam* ring)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);

	ring->rx_max_pending = (np->desc_ver == DESC_VER_1) ? RING_MAX_DESC_VER_1 : RING_MAX_DESC_VER_2_3;
	ring->tx_max_pending = (np->desc_ver == DESC_VER_1) ? RING_MAX_DESC_VER_1 : RING_MAX_DESC_VER_2_3;

	ring->rx_pending = np->rx_ring_size;
	ring->tx_pending = np->tx_ring_size;
पूर्ण

अटल पूर्णांक nv_set_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam* ring)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u8 *rxtx_ring, *rx_skbuff, *tx_skbuff;
	dma_addr_t ring_addr;

	अगर (ring->rx_pending < RX_RING_MIN ||
	    ring->tx_pending < TX_RING_MIN ||
	    ring->rx_mini_pending != 0 ||
	    ring->rx_jumbo_pending != 0 ||
	    (np->desc_ver == DESC_VER_1 &&
	     (ring->rx_pending > RING_MAX_DESC_VER_1 ||
	      ring->tx_pending > RING_MAX_DESC_VER_1)) ||
	    (np->desc_ver != DESC_VER_1 &&
	     (ring->rx_pending > RING_MAX_DESC_VER_2_3 ||
	      ring->tx_pending > RING_MAX_DESC_VER_2_3))) अणु
		वापस -EINVAL;
	पूर्ण

	/* allocate new rings */
	अगर (!nv_optimized(np)) अणु
		rxtx_ring = dma_alloc_coherent(&np->pci_dev->dev,
					       माप(काष्ठा ring_desc) *
					       (ring->rx_pending +
					       ring->tx_pending),
					       &ring_addr, GFP_ATOMIC);
	पूर्ण अन्यथा अणु
		rxtx_ring = dma_alloc_coherent(&np->pci_dev->dev,
					       माप(काष्ठा ring_desc_ex) *
					       (ring->rx_pending +
					       ring->tx_pending),
					       &ring_addr, GFP_ATOMIC);
	पूर्ण
	rx_skbuff = kदो_स्मृति_array(ring->rx_pending, माप(काष्ठा nv_skb_map),
				  GFP_KERNEL);
	tx_skbuff = kदो_स्मृति_array(ring->tx_pending, माप(काष्ठा nv_skb_map),
				  GFP_KERNEL);
	अगर (!rxtx_ring || !rx_skbuff || !tx_skbuff) अणु
		/* fall back to old rings */
		अगर (!nv_optimized(np)) अणु
			अगर (rxtx_ring)
				dma_मुक्त_coherent(&np->pci_dev->dev,
						  माप(काष्ठा ring_desc) *
						  (ring->rx_pending +
						  ring->tx_pending),
						  rxtx_ring, ring_addr);
		पूर्ण अन्यथा अणु
			अगर (rxtx_ring)
				dma_मुक्त_coherent(&np->pci_dev->dev,
						  माप(काष्ठा ring_desc_ex) *
						  (ring->rx_pending +
						  ring->tx_pending),
						  rxtx_ring, ring_addr);
		पूर्ण

		kमुक्त(rx_skbuff);
		kमुक्त(tx_skbuff);
		जाओ निकास;
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		nv_disable_irq(dev);
		nv_napi_disable(dev);
		netअगर_tx_lock_bh(dev);
		netअगर_addr_lock(dev);
		spin_lock(&np->lock);
		/* stop engines */
		nv_stop_rxtx(dev);
		nv_txrx_reset(dev);
		/* drain queues */
		nv_drain_rxtx(dev);
		/* delete queues */
		मुक्त_rings(dev);
	पूर्ण

	/* set new values */
	np->rx_ring_size = ring->rx_pending;
	np->tx_ring_size = ring->tx_pending;

	अगर (!nv_optimized(np)) अणु
		np->rx_ring.orig = (काष्ठा ring_desc *)rxtx_ring;
		np->tx_ring.orig = &np->rx_ring.orig[np->rx_ring_size];
	पूर्ण अन्यथा अणु
		np->rx_ring.ex = (काष्ठा ring_desc_ex *)rxtx_ring;
		np->tx_ring.ex = &np->rx_ring.ex[np->rx_ring_size];
	पूर्ण
	np->rx_skb = (काष्ठा nv_skb_map *)rx_skbuff;
	np->tx_skb = (काष्ठा nv_skb_map *)tx_skbuff;
	np->ring_addr = ring_addr;

	स_रखो(np->rx_skb, 0, माप(काष्ठा nv_skb_map) * np->rx_ring_size);
	स_रखो(np->tx_skb, 0, माप(काष्ठा nv_skb_map) * np->tx_ring_size);

	अगर (netअगर_running(dev)) अणु
		/* reinit driver view of the queues */
		set_bufsize(dev);
		अगर (nv_init_ring(dev)) अणु
			अगर (!np->in_shutकरोwn)
				mod_समयr(&np->oom_kick, jअगरfies + OOM_REFILL);
		पूर्ण

		/* reinit nic view of the queues */
		ग_लिखोl(np->rx_buf_sz, base + NvRegOffloadConfig);
		setup_hw_rings(dev, NV_SETUP_RX_RING | NV_SETUP_TX_RING);
		ग_लिखोl(((np->rx_ring_size-1) << NVREG_RINGSZ_RXSHIFT) + ((np->tx_ring_size-1) << NVREG_RINGSZ_TXSHIFT),
			base + NvRegRingSizes);
		pci_push(base);
		ग_लिखोl(NVREG_TXRXCTL_KICK|np->txrxctl_bits, get_hwbase(dev) + NvRegTxRxControl);
		pci_push(base);

		/* restart engines */
		nv_start_rxtx(dev);
		spin_unlock(&np->lock);
		netअगर_addr_unlock(dev);
		netअगर_tx_unlock_bh(dev);
		nv_napi_enable(dev);
		nv_enable_irq(dev);
	पूर्ण
	वापस 0;
निकास:
	वापस -ENOMEM;
पूर्ण

अटल व्योम nv_get_छोड़ोparam(काष्ठा net_device *dev, काष्ठा ethtool_छोड़ोparam* छोड़ो)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);

	छोड़ो->स्वतःneg = (np->छोड़ो_flags & NV_PAUSEFRAME_AUTONEG) != 0;
	छोड़ो->rx_छोड़ो = (np->छोड़ो_flags & NV_PAUSEFRAME_RX_ENABLE) != 0;
	छोड़ो->tx_छोड़ो = (np->छोड़ो_flags & NV_PAUSEFRAME_TX_ENABLE) != 0;
पूर्ण

अटल पूर्णांक nv_set_छोड़ोparam(काष्ठा net_device *dev, काष्ठा ethtool_छोड़ोparam* छोड़ो)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	पूर्णांक adv, bmcr;

	अगर ((!np->स्वतःneg && np->duplex == 0) ||
	    (np->स्वतःneg && !छोड़ो->स्वतःneg && np->duplex == 0)) अणु
		netdev_info(dev, "can not set pause settings when forced link is in half duplex\n");
		वापस -EINVAL;
	पूर्ण
	अगर (छोड़ो->tx_छोड़ो && !(np->छोड़ो_flags & NV_PAUSEFRAME_TX_CAPABLE)) अणु
		netdev_info(dev, "hardware does not support tx pause frames\n");
		वापस -EINVAL;
	पूर्ण

	netअगर_carrier_off(dev);
	अगर (netअगर_running(dev)) अणु
		nv_disable_irq(dev);
		netअगर_tx_lock_bh(dev);
		netअगर_addr_lock(dev);
		spin_lock(&np->lock);
		/* stop engines */
		nv_stop_rxtx(dev);
		spin_unlock(&np->lock);
		netअगर_addr_unlock(dev);
		netअगर_tx_unlock_bh(dev);
	पूर्ण

	np->छोड़ो_flags &= ~(NV_PAUSEFRAME_RX_REQ|NV_PAUSEFRAME_TX_REQ);
	अगर (छोड़ो->rx_छोड़ो)
		np->छोड़ो_flags |= NV_PAUSEFRAME_RX_REQ;
	अगर (छोड़ो->tx_छोड़ो)
		np->छोड़ो_flags |= NV_PAUSEFRAME_TX_REQ;

	अगर (np->स्वतःneg && छोड़ो->स्वतःneg) अणु
		np->छोड़ो_flags |= NV_PAUSEFRAME_AUTONEG;

		adv = mii_rw(dev, np->phyaddr, MII_ADVERTISE, MII_READ);
		adv &= ~(ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);
		अगर (np->छोड़ो_flags & NV_PAUSEFRAME_RX_REQ) /* क्रम rx we set both advertisements but disable tx छोड़ो */
			adv |=  ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
		अगर (np->छोड़ो_flags & NV_PAUSEFRAME_TX_REQ)
			adv |=  ADVERTISE_PAUSE_ASYM;
		mii_rw(dev, np->phyaddr, MII_ADVERTISE, adv);

		अगर (netअगर_running(dev))
			netdev_info(dev, "link down\n");
		bmcr = mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ);
		bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
		mii_rw(dev, np->phyaddr, MII_BMCR, bmcr);
	पूर्ण अन्यथा अणु
		np->छोड़ो_flags &= ~(NV_PAUSEFRAME_AUTONEG|NV_PAUSEFRAME_RX_ENABLE|NV_PAUSEFRAME_TX_ENABLE);
		अगर (छोड़ो->rx_छोड़ो)
			np->छोड़ो_flags |= NV_PAUSEFRAME_RX_ENABLE;
		अगर (छोड़ो->tx_छोड़ो)
			np->छोड़ो_flags |= NV_PAUSEFRAME_TX_ENABLE;

		अगर (!netअगर_running(dev))
			nv_update_linkspeed(dev);
		अन्यथा
			nv_update_छोड़ो(dev, np->छोड़ो_flags);
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		nv_start_rxtx(dev);
		nv_enable_irq(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nv_set_loopback(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	u32 miicontrol;
	पूर्णांक err, retval = 0;

	spin_lock_irqsave(&np->lock, flags);
	miicontrol = mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ);
	अगर (features & NETIF_F_LOOPBACK) अणु
		अगर (miicontrol & BMCR_LOOPBACK) अणु
			spin_unlock_irqrestore(&np->lock, flags);
			netdev_info(dev, "Loopback already enabled\n");
			वापस 0;
		पूर्ण
		nv_disable_irq(dev);
		/* Turn on loopback mode */
		miicontrol |= BMCR_LOOPBACK | BMCR_FULLDPLX | BMCR_SPEED1000;
		err = mii_rw(dev, np->phyaddr, MII_BMCR, miicontrol);
		अगर (err) अणु
			retval = PHY_ERROR;
			spin_unlock_irqrestore(&np->lock, flags);
			phy_init(dev);
		पूर्ण अन्यथा अणु
			अगर (netअगर_running(dev)) अणु
				/* Force 1000 Mbps full-duplex */
				nv_क्रमce_linkspeed(dev, NVREG_LINKSPEED_1000,
									 1);
				/* Force link up */
				netअगर_carrier_on(dev);
			पूर्ण
			spin_unlock_irqrestore(&np->lock, flags);
			netdev_info(dev,
				"Internal PHY loopback mode enabled.\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(miicontrol & BMCR_LOOPBACK)) अणु
			spin_unlock_irqrestore(&np->lock, flags);
			netdev_info(dev, "Loopback already disabled\n");
			वापस 0;
		पूर्ण
		nv_disable_irq(dev);
		/* Turn off loopback */
		spin_unlock_irqrestore(&np->lock, flags);
		netdev_info(dev, "Internal PHY loopback mode disabled.\n");
		phy_init(dev);
	पूर्ण
	msleep(500);
	spin_lock_irqsave(&np->lock, flags);
	nv_enable_irq(dev);
	spin_unlock_irqrestore(&np->lock, flags);

	वापस retval;
पूर्ण

अटल netdev_features_t nv_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	/* vlan is dependent on rx checksum offload */
	अगर (features & (NETIF_F_HW_VLAN_CTAG_TX|NETIF_F_HW_VLAN_CTAG_RX))
		features |= NETIF_F_RXCSUM;

	वापस features;
पूर्ण

अटल व्योम nv_vlan_mode(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा fe_priv *np = get_nvpriv(dev);

	spin_lock_irq(&np->lock);

	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		np->txrxctl_bits |= NVREG_TXRXCTL_VLANSTRIP;
	अन्यथा
		np->txrxctl_bits &= ~NVREG_TXRXCTL_VLANSTRIP;

	अगर (features & NETIF_F_HW_VLAN_CTAG_TX)
		np->txrxctl_bits |= NVREG_TXRXCTL_VLANINS;
	अन्यथा
		np->txrxctl_bits &= ~NVREG_TXRXCTL_VLANINS;

	ग_लिखोl(np->txrxctl_bits, get_hwbase(dev) + NvRegTxRxControl);

	spin_unlock_irq(&np->lock);
पूर्ण

अटल पूर्णांक nv_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	netdev_features_t changed = dev->features ^ features;
	पूर्णांक retval;

	अगर ((changed & NETIF_F_LOOPBACK) && netअगर_running(dev)) अणु
		retval = nv_set_loopback(dev, features);
		अगर (retval != 0)
			वापस retval;
	पूर्ण

	अगर (changed & NETIF_F_RXCSUM) अणु
		spin_lock_irq(&np->lock);

		अगर (features & NETIF_F_RXCSUM)
			np->txrxctl_bits |= NVREG_TXRXCTL_RXCHECK;
		अन्यथा
			np->txrxctl_bits &= ~NVREG_TXRXCTL_RXCHECK;

		अगर (netअगर_running(dev))
			ग_लिखोl(np->txrxctl_bits, base + NvRegTxRxControl);

		spin_unlock_irq(&np->lock);
	पूर्ण

	अगर (changed & (NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX))
		nv_vlan_mode(dev, features);

	वापस 0;
पूर्ण

अटल पूर्णांक nv_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_TEST:
		अगर (np->driver_data & DEV_HAS_TEST_EXTENDED)
			वापस NV_TEST_COUNT_EXTENDED;
		अन्यथा
			वापस NV_TEST_COUNT_BASE;
	हाल ETH_SS_STATS:
		अगर (np->driver_data & DEV_HAS_STATISTICS_V3)
			वापस NV_DEV_STATISTICS_V3_COUNT;
		अन्यथा अगर (np->driver_data & DEV_HAS_STATISTICS_V2)
			वापस NV_DEV_STATISTICS_V2_COUNT;
		अन्यथा अगर (np->driver_data & DEV_HAS_STATISTICS_V1)
			वापस NV_DEV_STATISTICS_V1_COUNT;
		अन्यथा
			वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम nv_get_ethtool_stats(काष्ठा net_device *dev,
				 काष्ठा ethtool_stats *estats, u64 *buffer)
	__acquires(&netdev_priv(dev)->hwstats_lock)
	__releases(&netdev_priv(dev)->hwstats_lock)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);

	spin_lock_bh(&np->hwstats_lock);
	nv_update_stats(dev);
	स_नकल(buffer, &np->estats,
	       nv_get_sset_count(dev, ETH_SS_STATS)*माप(u64));
	spin_unlock_bh(&np->hwstats_lock);
पूर्ण

अटल पूर्णांक nv_link_test(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	पूर्णांक mii_status;

	mii_rw(dev, np->phyaddr, MII_BMSR, MII_READ);
	mii_status = mii_rw(dev, np->phyaddr, MII_BMSR, MII_READ);

	/* check phy link status */
	अगर (!(mii_status & BMSR_LSTATUS))
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक nv_रेजिस्टर_test(काष्ठा net_device *dev)
अणु
	u8 __iomem *base = get_hwbase(dev);
	पूर्णांक i = 0;
	u32 orig_पढ़ो, new_पढ़ो;

	करो अणु
		orig_पढ़ो = पढ़ोl(base + nv_रेजिस्टरs_test[i].reg);

		/* xor with mask to toggle bits */
		orig_पढ़ो ^= nv_रेजिस्टरs_test[i].mask;

		ग_लिखोl(orig_पढ़ो, base + nv_रेजिस्टरs_test[i].reg);

		new_पढ़ो = पढ़ोl(base + nv_रेजिस्टरs_test[i].reg);

		अगर ((new_पढ़ो & nv_रेजिस्टरs_test[i].mask) != (orig_पढ़ो & nv_रेजिस्टरs_test[i].mask))
			वापस 0;

		/* restore original value */
		orig_पढ़ो ^= nv_रेजिस्टरs_test[i].mask;
		ग_लिखोl(orig_पढ़ो, base + nv_रेजिस्टरs_test[i].reg);

	पूर्ण जबतक (nv_रेजिस्टरs_test[++i].reg != 0);

	वापस 1;
पूर्ण

अटल पूर्णांक nv_पूर्णांकerrupt_test(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	पूर्णांक ret = 1;
	पूर्णांक testcnt;
	u32 save_msi_flags, save_poll_पूर्णांकerval = 0;

	अगर (netअगर_running(dev)) अणु
		/* मुक्त current irq */
		nv_मुक्त_irq(dev);
		save_poll_पूर्णांकerval = पढ़ोl(base+NvRegPollingInterval);
	पूर्ण

	/* flag to test पूर्णांकerrupt handler */
	np->पूर्णांकr_test = 0;

	/* setup test irq */
	save_msi_flags = np->msi_flags;
	np->msi_flags &= ~NV_MSI_X_VECTORS_MASK;
	np->msi_flags |= 0x001; /* setup 1 vector */
	अगर (nv_request_irq(dev, 1))
		वापस 0;

	/* setup समयr पूर्णांकerrupt */
	ग_लिखोl(NVREG_POLL_DEFAULT_CPU, base + NvRegPollingInterval);
	ग_लिखोl(NVREG_UNKSETUP6_VAL, base + NvRegUnknownSetupReg6);

	nv_enable_hw_पूर्णांकerrupts(dev, NVREG_IRQ_TIMER);

	/* रुको क्रम at least one पूर्णांकerrupt */
	msleep(100);

	spin_lock_irq(&np->lock);

	/* flag should be set within ISR */
	testcnt = np->पूर्णांकr_test;
	अगर (!testcnt)
		ret = 2;

	nv_disable_hw_पूर्णांकerrupts(dev, NVREG_IRQ_TIMER);
	अगर (!(np->msi_flags & NV_MSI_X_ENABLED))
		ग_लिखोl(NVREG_IRQSTAT_MASK, base + NvRegIrqStatus);
	अन्यथा
		ग_लिखोl(NVREG_IRQSTAT_MASK, base + NvRegMSIXIrqStatus);

	spin_unlock_irq(&np->lock);

	nv_मुक्त_irq(dev);

	np->msi_flags = save_msi_flags;

	अगर (netअगर_running(dev)) अणु
		ग_लिखोl(save_poll_पूर्णांकerval, base + NvRegPollingInterval);
		ग_लिखोl(NVREG_UNKSETUP6_VAL, base + NvRegUnknownSetupReg6);
		/* restore original irq */
		अगर (nv_request_irq(dev, 0))
			वापस 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nv_loopback_test(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	काष्ठा sk_buff *tx_skb, *rx_skb;
	dma_addr_t test_dma_addr;
	u32 tx_flags_extra = (np->desc_ver == DESC_VER_1 ? NV_TX_LASTPACKET : NV_TX2_LASTPACKET);
	u32 flags;
	पूर्णांक len, i, pkt_len;
	u8 *pkt_data;
	u32 filter_flags = 0;
	u32 misc1_flags = 0;
	पूर्णांक ret = 1;

	अगर (netअगर_running(dev)) अणु
		nv_disable_irq(dev);
		filter_flags = पढ़ोl(base + NvRegPacketFilterFlags);
		misc1_flags = पढ़ोl(base + NvRegMisc1);
	पूर्ण अन्यथा अणु
		nv_txrx_reset(dev);
	पूर्ण

	/* reinit driver view of the rx queue */
	set_bufsize(dev);
	nv_init_ring(dev);

	/* setup hardware क्रम loopback */
	ग_लिखोl(NVREG_MISC1_FORCE, base + NvRegMisc1);
	ग_लिखोl(NVREG_PFF_ALWAYS | NVREG_PFF_LOOPBACK, base + NvRegPacketFilterFlags);

	/* reinit nic view of the rx queue */
	ग_लिखोl(np->rx_buf_sz, base + NvRegOffloadConfig);
	setup_hw_rings(dev, NV_SETUP_RX_RING | NV_SETUP_TX_RING);
	ग_लिखोl(((np->rx_ring_size-1) << NVREG_RINGSZ_RXSHIFT) + ((np->tx_ring_size-1) << NVREG_RINGSZ_TXSHIFT),
		base + NvRegRingSizes);
	pci_push(base);

	/* restart rx engine */
	nv_start_rxtx(dev);

	/* setup packet क्रम tx */
	pkt_len = ETH_DATA_LEN;
	tx_skb = netdev_alloc_skb(dev, pkt_len);
	अगर (!tx_skb) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	test_dma_addr = dma_map_single(&np->pci_dev->dev, tx_skb->data,
				       skb_tailroom(tx_skb),
				       DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(&np->pci_dev->dev,
				       test_dma_addr))) अणु
		dev_kमुक्त_skb_any(tx_skb);
		जाओ out;
	पूर्ण
	pkt_data = skb_put(tx_skb, pkt_len);
	क्रम (i = 0; i < pkt_len; i++)
		pkt_data[i] = (u8)(i & 0xff);

	अगर (!nv_optimized(np)) अणु
		np->tx_ring.orig[0].buf = cpu_to_le32(test_dma_addr);
		np->tx_ring.orig[0].flaglen = cpu_to_le32((pkt_len-1) | np->tx_flags | tx_flags_extra);
	पूर्ण अन्यथा अणु
		np->tx_ring.ex[0].bufhigh = cpu_to_le32(dma_high(test_dma_addr));
		np->tx_ring.ex[0].buflow = cpu_to_le32(dma_low(test_dma_addr));
		np->tx_ring.ex[0].flaglen = cpu_to_le32((pkt_len-1) | np->tx_flags | tx_flags_extra);
	पूर्ण
	ग_लिखोl(NVREG_TXRXCTL_KICK|np->txrxctl_bits, get_hwbase(dev) + NvRegTxRxControl);
	pci_push(get_hwbase(dev));

	msleep(500);

	/* check क्रम rx of the packet */
	अगर (!nv_optimized(np)) अणु
		flags = le32_to_cpu(np->rx_ring.orig[0].flaglen);
		len = nv_descr_getlength(&np->rx_ring.orig[0], np->desc_ver);

	पूर्ण अन्यथा अणु
		flags = le32_to_cpu(np->rx_ring.ex[0].flaglen);
		len = nv_descr_getlength_ex(&np->rx_ring.ex[0], np->desc_ver);
	पूर्ण

	अगर (flags & NV_RX_AVAIL) अणु
		ret = 0;
	पूर्ण अन्यथा अगर (np->desc_ver == DESC_VER_1) अणु
		अगर (flags & NV_RX_ERROR)
			ret = 0;
	पूर्ण अन्यथा अणु
		अगर (flags & NV_RX2_ERROR)
			ret = 0;
	पूर्ण

	अगर (ret) अणु
		अगर (len != pkt_len) अणु
			ret = 0;
		पूर्ण अन्यथा अणु
			rx_skb = np->rx_skb[0].skb;
			क्रम (i = 0; i < pkt_len; i++) अणु
				अगर (rx_skb->data[i] != (u8)(i & 0xff)) अणु
					ret = 0;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	dma_unmap_single(&np->pci_dev->dev, test_dma_addr,
			 (skb_end_poपूर्णांकer(tx_skb) - tx_skb->data),
			 DMA_TO_DEVICE);
	dev_kमुक्त_skb_any(tx_skb);
 out:
	/* stop engines */
	nv_stop_rxtx(dev);
	nv_txrx_reset(dev);
	/* drain rx queue */
	nv_drain_rxtx(dev);

	अगर (netअगर_running(dev)) अणु
		ग_लिखोl(misc1_flags, base + NvRegMisc1);
		ग_लिखोl(filter_flags, base + NvRegPacketFilterFlags);
		nv_enable_irq(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम nv_self_test(काष्ठा net_device *dev, काष्ठा ethtool_test *test, u64 *buffer)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	पूर्णांक result, count;

	count = nv_get_sset_count(dev, ETH_SS_TEST);
	स_रखो(buffer, 0, count * माप(u64));

	अगर (!nv_link_test(dev)) अणु
		test->flags |= ETH_TEST_FL_FAILED;
		buffer[0] = 1;
	पूर्ण

	अगर (test->flags & ETH_TEST_FL_OFFLINE) अणु
		अगर (netअगर_running(dev)) अणु
			netअगर_stop_queue(dev);
			nv_napi_disable(dev);
			netअगर_tx_lock_bh(dev);
			netअगर_addr_lock(dev);
			spin_lock_irq(&np->lock);
			nv_disable_hw_पूर्णांकerrupts(dev, np->irqmask);
			अगर (!(np->msi_flags & NV_MSI_X_ENABLED))
				ग_लिखोl(NVREG_IRQSTAT_MASK, base + NvRegIrqStatus);
			अन्यथा
				ग_लिखोl(NVREG_IRQSTAT_MASK, base + NvRegMSIXIrqStatus);
			/* stop engines */
			nv_stop_rxtx(dev);
			nv_txrx_reset(dev);
			/* drain rx queue */
			nv_drain_rxtx(dev);
			spin_unlock_irq(&np->lock);
			netअगर_addr_unlock(dev);
			netअगर_tx_unlock_bh(dev);
		पूर्ण

		अगर (!nv_रेजिस्टर_test(dev)) अणु
			test->flags |= ETH_TEST_FL_FAILED;
			buffer[1] = 1;
		पूर्ण

		result = nv_पूर्णांकerrupt_test(dev);
		अगर (result != 1) अणु
			test->flags |= ETH_TEST_FL_FAILED;
			buffer[2] = 1;
		पूर्ण
		अगर (result == 0) अणु
			/* bail out */
			वापस;
		पूर्ण

		अगर (count > NV_TEST_COUNT_BASE && !nv_loopback_test(dev)) अणु
			test->flags |= ETH_TEST_FL_FAILED;
			buffer[3] = 1;
		पूर्ण

		अगर (netअगर_running(dev)) अणु
			/* reinit driver view of the rx queue */
			set_bufsize(dev);
			अगर (nv_init_ring(dev)) अणु
				अगर (!np->in_shutकरोwn)
					mod_समयr(&np->oom_kick, jअगरfies + OOM_REFILL);
			पूर्ण
			/* reinit nic view of the rx queue */
			ग_लिखोl(np->rx_buf_sz, base + NvRegOffloadConfig);
			setup_hw_rings(dev, NV_SETUP_RX_RING | NV_SETUP_TX_RING);
			ग_लिखोl(((np->rx_ring_size-1) << NVREG_RINGSZ_RXSHIFT) + ((np->tx_ring_size-1) << NVREG_RINGSZ_TXSHIFT),
				base + NvRegRingSizes);
			pci_push(base);
			ग_लिखोl(NVREG_TXRXCTL_KICK|np->txrxctl_bits, get_hwbase(dev) + NvRegTxRxControl);
			pci_push(base);
			/* restart rx engine */
			nv_start_rxtx(dev);
			netअगर_start_queue(dev);
			nv_napi_enable(dev);
			nv_enable_hw_पूर्णांकerrupts(dev, np->irqmask);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nv_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buffer)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(buffer, &nv_estats_str, nv_get_sset_count(dev, ETH_SS_STATS)*माप(काष्ठा nv_ethtool_str));
		अवरोध;
	हाल ETH_SS_TEST:
		स_नकल(buffer, &nv_etests_str, nv_get_sset_count(dev, ETH_SS_TEST)*माप(काष्ठा nv_ethtool_str));
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_drvinfo = nv_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_wol = nv_get_wol,
	.set_wol = nv_set_wol,
	.get_regs_len = nv_get_regs_len,
	.get_regs = nv_get_regs,
	.nway_reset = nv_nway_reset,
	.get_ringparam = nv_get_ringparam,
	.set_ringparam = nv_set_ringparam,
	.get_छोड़ोparam = nv_get_छोड़ोparam,
	.set_छोड़ोparam = nv_set_छोड़ोparam,
	.get_strings = nv_get_strings,
	.get_ethtool_stats = nv_get_ethtool_stats,
	.get_sset_count = nv_get_sset_count,
	.self_test = nv_self_test,
	.get_ts_info = ethtool_op_get_ts_info,
	.get_link_ksettings = nv_get_link_ksettings,
	.set_link_ksettings = nv_set_link_ksettings,
पूर्ण;

/* The mgmt unit and driver use a semaphore to access the phy during init */
अटल पूर्णांक nv_mgmt_acquire_sema(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	पूर्णांक i;
	u32 tx_ctrl, mgmt_sema;

	क्रम (i = 0; i < 10; i++) अणु
		mgmt_sema = पढ़ोl(base + NvRegTransmitterControl) & NVREG_XMITCTL_MGMT_SEMA_MASK;
		अगर (mgmt_sema == NVREG_XMITCTL_MGMT_SEMA_FREE)
			अवरोध;
		msleep(500);
	पूर्ण

	अगर (mgmt_sema != NVREG_XMITCTL_MGMT_SEMA_FREE)
		वापस 0;

	क्रम (i = 0; i < 2; i++) अणु
		tx_ctrl = पढ़ोl(base + NvRegTransmitterControl);
		tx_ctrl |= NVREG_XMITCTL_HOST_SEMA_ACQ;
		ग_लिखोl(tx_ctrl, base + NvRegTransmitterControl);

		/* verअगरy that semaphore was acquired */
		tx_ctrl = पढ़ोl(base + NvRegTransmitterControl);
		अगर (((tx_ctrl & NVREG_XMITCTL_HOST_SEMA_MASK) == NVREG_XMITCTL_HOST_SEMA_ACQ) &&
		    ((tx_ctrl & NVREG_XMITCTL_MGMT_SEMA_MASK) == NVREG_XMITCTL_MGMT_SEMA_FREE)) अणु
			np->mgmt_sema = 1;
			वापस 1;
		पूर्ण अन्यथा
			udelay(50);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nv_mgmt_release_sema(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 tx_ctrl;

	अगर (np->driver_data & DEV_HAS_MGMT_UNIT) अणु
		अगर (np->mgmt_sema) अणु
			tx_ctrl = पढ़ोl(base + NvRegTransmitterControl);
			tx_ctrl &= ~NVREG_XMITCTL_HOST_SEMA_ACQ;
			ग_लिखोl(tx_ctrl, base + NvRegTransmitterControl);
		पूर्ण
	पूर्ण
पूर्ण


अटल पूर्णांक nv_mgmt_get_version(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	u32 data_पढ़ोy = पढ़ोl(base + NvRegTransmitterControl);
	u32 data_पढ़ोy2 = 0;
	अचिन्हित दीर्घ start;
	पूर्णांक पढ़ोy = 0;

	ग_लिखोl(NVREG_MGMTUNITGETVERSION, base + NvRegMgmtUnitGetVersion);
	ग_लिखोl(data_पढ़ोy ^ NVREG_XMITCTL_DATA_START, base + NvRegTransmitterControl);
	start = jअगरfies;
	जबतक (समय_beक्रमe(jअगरfies, start + 5*HZ)) अणु
		data_पढ़ोy2 = पढ़ोl(base + NvRegTransmitterControl);
		अगर ((data_पढ़ोy & NVREG_XMITCTL_DATA_READY) != (data_पढ़ोy2 & NVREG_XMITCTL_DATA_READY)) अणु
			पढ़ोy = 1;
			अवरोध;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण

	अगर (!पढ़ोy || (data_पढ़ोy2 & NVREG_XMITCTL_DATA_ERROR))
		वापस 0;

	np->mgmt_version = पढ़ोl(base + NvRegMgmtUnitVersion) & NVREG_MGMTUNITVERSION;

	वापस 1;
पूर्ण

अटल पूर्णांक nv_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	पूर्णांक ret = 1;
	पूर्णांक oom, i;
	u32 low;

	/* घातer up phy */
	mii_rw(dev, np->phyaddr, MII_BMCR,
	       mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ) & ~BMCR_PDOWN);

	nv_txrx_gate(dev, false);
	/* erase previous misconfiguration */
	अगर (np->driver_data & DEV_HAS_POWER_CNTRL)
		nv_mac_reset(dev);
	ग_लिखोl(NVREG_MCASTADDRA_FORCE, base + NvRegMulticastAddrA);
	ग_लिखोl(0, base + NvRegMulticastAddrB);
	ग_लिखोl(NVREG_MCASTMASKA_NONE, base + NvRegMulticastMaskA);
	ग_लिखोl(NVREG_MCASTMASKB_NONE, base + NvRegMulticastMaskB);
	ग_लिखोl(0, base + NvRegPacketFilterFlags);

	ग_लिखोl(0, base + NvRegTransmitterControl);
	ग_लिखोl(0, base + NvRegReceiverControl);

	ग_लिखोl(0, base + NvRegAdapterControl);

	अगर (np->छोड़ो_flags & NV_PAUSEFRAME_TX_CAPABLE)
		ग_लिखोl(NVREG_TX_PAUSEFRAME_DISABLE,  base + NvRegTxPauseFrame);

	/* initialize descriptor rings */
	set_bufsize(dev);
	oom = nv_init_ring(dev);

	ग_लिखोl(0, base + NvRegLinkSpeed);
	ग_लिखोl(पढ़ोl(base + NvRegTransmitPoll) & NVREG_TRANSMITPOLL_MAC_ADDR_REV, base + NvRegTransmitPoll);
	nv_txrx_reset(dev);
	ग_लिखोl(0, base + NvRegUnknownSetupReg6);

	np->in_shutकरोwn = 0;

	/* give hw rings */
	setup_hw_rings(dev, NV_SETUP_RX_RING | NV_SETUP_TX_RING);
	ग_लिखोl(((np->rx_ring_size-1) << NVREG_RINGSZ_RXSHIFT) + ((np->tx_ring_size-1) << NVREG_RINGSZ_TXSHIFT),
		base + NvRegRingSizes);

	ग_लिखोl(np->linkspeed, base + NvRegLinkSpeed);
	अगर (np->desc_ver == DESC_VER_1)
		ग_लिखोl(NVREG_TX_WM_DESC1_DEFAULT, base + NvRegTxWatermark);
	अन्यथा
		ग_लिखोl(NVREG_TX_WM_DESC2_3_DEFAULT, base + NvRegTxWatermark);
	ग_लिखोl(np->txrxctl_bits, base + NvRegTxRxControl);
	ग_लिखोl(np->vlanctl_bits, base + NvRegVlanControl);
	pci_push(base);
	ग_लिखोl(NVREG_TXRXCTL_BIT1|np->txrxctl_bits, base + NvRegTxRxControl);
	अगर (reg_delay(dev, NvRegUnknownSetupReg5,
		      NVREG_UNKSETUP5_BIT31, NVREG_UNKSETUP5_BIT31,
		      NV_SETUP5_DELAY, NV_SETUP5_DELAYMAX))
		netdev_info(dev,
			    "%s: SetupReg5, Bit 31 remained off\n", __func__);

	ग_लिखोl(0, base + NvRegMIIMask);
	ग_लिखोl(NVREG_IRQSTAT_MASK, base + NvRegIrqStatus);
	ग_लिखोl(NVREG_MIISTAT_MASK_ALL, base + NvRegMIIStatus);

	ग_लिखोl(NVREG_MISC1_FORCE | NVREG_MISC1_HD, base + NvRegMisc1);
	ग_लिखोl(पढ़ोl(base + NvRegTransmitterStatus), base + NvRegTransmitterStatus);
	ग_लिखोl(NVREG_PFF_ALWAYS, base + NvRegPacketFilterFlags);
	ग_लिखोl(np->rx_buf_sz, base + NvRegOffloadConfig);

	ग_लिखोl(पढ़ोl(base + NvRegReceiverStatus), base + NvRegReceiverStatus);

	get_अक्रमom_bytes(&low, माप(low));
	low &= NVREG_SLOTTIME_MASK;
	अगर (np->desc_ver == DESC_VER_1) अणु
		ग_लिखोl(low|NVREG_SLOTTIME_DEFAULT, base + NvRegSlotTime);
	पूर्ण अन्यथा अणु
		अगर (!(np->driver_data & DEV_HAS_GEAR_MODE)) अणु
			/* setup legacy backoff */
			ग_लिखोl(NVREG_SLOTTIME_LEGBF_ENABLED|NVREG_SLOTTIME_10_100_FULL|low, base + NvRegSlotTime);
		पूर्ण अन्यथा अणु
			ग_लिखोl(NVREG_SLOTTIME_10_100_FULL, base + NvRegSlotTime);
			nv_gear_backoff_reseed(dev);
		पूर्ण
	पूर्ण
	ग_लिखोl(NVREG_TX_DEFERRAL_DEFAULT, base + NvRegTxDeferral);
	ग_लिखोl(NVREG_RX_DEFERRAL_DEFAULT, base + NvRegRxDeferral);
	अगर (poll_पूर्णांकerval == -1) अणु
		अगर (optimization_mode == NV_OPTIMIZATION_MODE_THROUGHPUT)
			ग_लिखोl(NVREG_POLL_DEFAULT_THROUGHPUT, base + NvRegPollingInterval);
		अन्यथा
			ग_लिखोl(NVREG_POLL_DEFAULT_CPU, base + NvRegPollingInterval);
	पूर्ण अन्यथा
		ग_लिखोl(poll_पूर्णांकerval & 0xFFFF, base + NvRegPollingInterval);
	ग_लिखोl(NVREG_UNKSETUP6_VAL, base + NvRegUnknownSetupReg6);
	ग_लिखोl((np->phyaddr << NVREG_ADAPTCTL_PHYSHIFT)|NVREG_ADAPTCTL_PHYVALID|NVREG_ADAPTCTL_RUNNING,
			base + NvRegAdapterControl);
	ग_लिखोl(NVREG_MIISPEED_BIT8|NVREG_MIIDELAY, base + NvRegMIISpeed);
	ग_लिखोl(NVREG_MII_LINKCHANGE, base + NvRegMIIMask);
	अगर (np->wolenabled)
		ग_लिखोl(NVREG_WAKEUPFLAGS_ENABLE , base + NvRegWakeUpFlags);

	i = पढ़ोl(base + NvRegPowerState);
	अगर ((i & NVREG_POWERSTATE_POWEREDUP) == 0)
		ग_लिखोl(NVREG_POWERSTATE_POWEREDUP|i, base + NvRegPowerState);

	pci_push(base);
	udelay(10);
	ग_लिखोl(पढ़ोl(base + NvRegPowerState) | NVREG_POWERSTATE_VALID, base + NvRegPowerState);

	nv_disable_hw_पूर्णांकerrupts(dev, np->irqmask);
	pci_push(base);
	ग_लिखोl(NVREG_MIISTAT_MASK_ALL, base + NvRegMIIStatus);
	ग_लिखोl(NVREG_IRQSTAT_MASK, base + NvRegIrqStatus);
	pci_push(base);

	अगर (nv_request_irq(dev, 0))
		जाओ out_drain;

	/* ask क्रम पूर्णांकerrupts */
	nv_enable_hw_पूर्णांकerrupts(dev, np->irqmask);

	spin_lock_irq(&np->lock);
	ग_लिखोl(NVREG_MCASTADDRA_FORCE, base + NvRegMulticastAddrA);
	ग_लिखोl(0, base + NvRegMulticastAddrB);
	ग_लिखोl(NVREG_MCASTMASKA_NONE, base + NvRegMulticastMaskA);
	ग_लिखोl(NVREG_MCASTMASKB_NONE, base + NvRegMulticastMaskB);
	ग_लिखोl(NVREG_PFF_ALWAYS|NVREG_PFF_MYADDR, base + NvRegPacketFilterFlags);
	/* One manual link speed update: Interrupts are enabled, future link
	 * speed changes cause पूर्णांकerrupts and are handled by nv_link_irq().
	 */
	पढ़ोl(base + NvRegMIIStatus);
	ग_लिखोl(NVREG_MIISTAT_MASK_ALL, base + NvRegMIIStatus);

	/* set linkspeed to invalid value, thus क्रमce nv_update_linkspeed
	 * to init hw */
	np->linkspeed = 0;
	ret = nv_update_linkspeed(dev);
	nv_start_rxtx(dev);
	netअगर_start_queue(dev);
	nv_napi_enable(dev);

	अगर (ret) अणु
		netअगर_carrier_on(dev);
	पूर्ण अन्यथा अणु
		netdev_info(dev, "no link during initialization\n");
		netअगर_carrier_off(dev);
	पूर्ण
	अगर (oom)
		mod_समयr(&np->oom_kick, jअगरfies + OOM_REFILL);

	/* start statistics समयr */
	अगर (np->driver_data & (DEV_HAS_STATISTICS_V1|DEV_HAS_STATISTICS_V2|DEV_HAS_STATISTICS_V3))
		mod_समयr(&np->stats_poll,
			round_jअगरfies(jअगरfies + STATS_INTERVAL));

	spin_unlock_irq(&np->lock);

	/* If the loopback feature was set जबतक the device was करोwn, make sure
	 * that it's set correctly now.
	 */
	अगर (dev->features & NETIF_F_LOOPBACK)
		nv_set_loopback(dev, dev->features);

	वापस 0;
out_drain:
	nv_drain_rxtx(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक nv_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base;

	spin_lock_irq(&np->lock);
	np->in_shutकरोwn = 1;
	spin_unlock_irq(&np->lock);
	nv_napi_disable(dev);
	synchronize_irq(np->pci_dev->irq);

	del_समयr_sync(&np->oom_kick);
	del_समयr_sync(&np->nic_poll);
	del_समयr_sync(&np->stats_poll);

	netअगर_stop_queue(dev);
	spin_lock_irq(&np->lock);
	nv_update_छोड़ो(dev, 0); /* otherwise stop_tx bricks NIC */
	nv_stop_rxtx(dev);
	nv_txrx_reset(dev);

	/* disable पूर्णांकerrupts on the nic or we will lock up */
	base = get_hwbase(dev);
	nv_disable_hw_पूर्णांकerrupts(dev, np->irqmask);
	pci_push(base);

	spin_unlock_irq(&np->lock);

	nv_मुक्त_irq(dev);

	nv_drain_rxtx(dev);

	अगर (np->wolenabled || !phy_घातer_करोwn) अणु
		nv_txrx_gate(dev, false);
		ग_लिखोl(NVREG_PFF_ALWAYS|NVREG_PFF_MYADDR, base + NvRegPacketFilterFlags);
		nv_start_rx(dev);
	पूर्ण अन्यथा अणु
		/* घातer करोwn phy */
		mii_rw(dev, np->phyaddr, MII_BMCR,
		       mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ)|BMCR_PDOWN);
		nv_txrx_gate(dev, true);
	पूर्ण

	/* FIXME: घातer करोwn nic */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops nv_netdev_ops = अणु
	.nकरो_खोलो		= nv_खोलो,
	.nकरो_stop		= nv_बंद,
	.nकरो_get_stats64	= nv_get_stats64,
	.nकरो_start_xmit		= nv_start_xmit,
	.nकरो_tx_समयout		= nv_tx_समयout,
	.nकरो_change_mtu		= nv_change_mtu,
	.nकरो_fix_features	= nv_fix_features,
	.nकरो_set_features	= nv_set_features,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= nv_set_mac_address,
	.nकरो_set_rx_mode	= nv_set_multicast,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= nv_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_device_ops nv_netdev_ops_optimized = अणु
	.nकरो_खोलो		= nv_खोलो,
	.nकरो_stop		= nv_बंद,
	.nकरो_get_stats64	= nv_get_stats64,
	.nकरो_start_xmit		= nv_start_xmit_optimized,
	.nकरो_tx_समयout		= nv_tx_समयout,
	.nकरो_change_mtu		= nv_change_mtu,
	.nकरो_fix_features	= nv_fix_features,
	.nकरो_set_features	= nv_set_features,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= nv_set_mac_address,
	.nकरो_set_rx_mode	= nv_set_multicast,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= nv_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक nv_probe(काष्ठा pci_dev *pci_dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा net_device *dev;
	काष्ठा fe_priv *np;
	अचिन्हित दीर्घ addr;
	u8 __iomem *base;
	पूर्णांक err, i;
	u32 घातerstate, txreg;
	u32 phystate_orig = 0, phystate;
	पूर्णांक phyinitialized = 0;
	अटल पूर्णांक prपूर्णांकed_version;

	अगर (!prपूर्णांकed_version++)
		pr_info("Reverse Engineered nForce ethernet driver. Version %s.\n",
			FORCEDETH_VERSION);

	dev = alloc_etherdev(माप(काष्ठा fe_priv));
	err = -ENOMEM;
	अगर (!dev)
		जाओ out;

	np = netdev_priv(dev);
	np->dev = dev;
	np->pci_dev = pci_dev;
	spin_lock_init(&np->lock);
	spin_lock_init(&np->hwstats_lock);
	SET_NETDEV_DEV(dev, &pci_dev->dev);
	u64_stats_init(&np->swstats_rx_syncp);
	u64_stats_init(&np->swstats_tx_syncp);
	np->txrx_stats = alloc_percpu(काष्ठा nv_txrx_stats);
	अगर (!np->txrx_stats) अणु
		pr_err("np->txrx_stats, alloc memory error.\n");
		err = -ENOMEM;
		जाओ out_alloc_percpu;
	पूर्ण

	समयr_setup(&np->oom_kick, nv_करो_rx_refill, 0);
	समयr_setup(&np->nic_poll, nv_करो_nic_poll, 0);
	समयr_setup(&np->stats_poll, nv_करो_stats_poll, TIMER_DEFERRABLE);

	err = pci_enable_device(pci_dev);
	अगर (err)
		जाओ out_मुक्त;

	pci_set_master(pci_dev);

	err = pci_request_regions(pci_dev, DRV_NAME);
	अगर (err < 0)
		जाओ out_disable;

	अगर (id->driver_data & (DEV_HAS_VLAN|DEV_HAS_MSI_X|DEV_HAS_POWER_CNTRL|DEV_HAS_STATISTICS_V2|DEV_HAS_STATISTICS_V3))
		np->रेजिस्टर_size = NV_PCI_REGSZ_VER3;
	अन्यथा अगर (id->driver_data & DEV_HAS_STATISTICS_V1)
		np->रेजिस्टर_size = NV_PCI_REGSZ_VER2;
	अन्यथा
		np->रेजिस्टर_size = NV_PCI_REGSZ_VER1;

	err = -EINVAL;
	addr = 0;
	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		अगर (pci_resource_flags(pci_dev, i) & IORESOURCE_MEM &&
				pci_resource_len(pci_dev, i) >= np->रेजिस्टर_size) अणु
			addr = pci_resource_start(pci_dev, i);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == DEVICE_COUNT_RESOURCE) अणु
		dev_info(&pci_dev->dev, "Couldn't find register window\n");
		जाओ out_relreg;
	पूर्ण

	/* copy of driver data */
	np->driver_data = id->driver_data;
	/* copy of device id */
	np->device_id = id->device;

	/* handle dअगरferent descriptor versions */
	अगर (id->driver_data & DEV_HAS_HIGH_DMA) अणु
		/* packet क्रमmat 3: supports 40-bit addressing */
		np->desc_ver = DESC_VER_3;
		np->txrxctl_bits = NVREG_TXRXCTL_DESC_3;
		अगर (dma_64bit) अणु
			अगर (pci_set_dma_mask(pci_dev, DMA_BIT_MASK(39)))
				dev_info(&pci_dev->dev,
					 "64-bit DMA failed, using 32-bit addressing\n");
			अन्यथा
				dev->features |= NETIF_F_HIGHDMA;
			अगर (pci_set_consistent_dma_mask(pci_dev, DMA_BIT_MASK(39))) अणु
				dev_info(&pci_dev->dev,
					 "64-bit DMA (consistent) failed, using 32-bit ring buffers\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (id->driver_data & DEV_HAS_LARGEDESC) अणु
		/* packet क्रमmat 2: supports jumbo frames */
		np->desc_ver = DESC_VER_2;
		np->txrxctl_bits = NVREG_TXRXCTL_DESC_2;
	पूर्ण अन्यथा अणु
		/* original packet क्रमmat */
		np->desc_ver = DESC_VER_1;
		np->txrxctl_bits = NVREG_TXRXCTL_DESC_1;
	पूर्ण

	np->pkt_limit = NV_PKTLIMIT_1;
	अगर (id->driver_data & DEV_HAS_LARGEDESC)
		np->pkt_limit = NV_PKTLIMIT_2;

	अगर (id->driver_data & DEV_HAS_CHECKSUM) अणु
		np->txrxctl_bits |= NVREG_TXRXCTL_RXCHECK;
		dev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_SG |
			NETIF_F_TSO | NETIF_F_RXCSUM;
	पूर्ण

	np->vlanctl_bits = 0;
	अगर (id->driver_data & DEV_HAS_VLAN) अणु
		np->vlanctl_bits = NVREG_VLANCONTROL_ENABLE;
		dev->hw_features |= NETIF_F_HW_VLAN_CTAG_RX |
				    NETIF_F_HW_VLAN_CTAG_TX;
	पूर्ण

	dev->features |= dev->hw_features;

	/* Add loopback capability to the device. */
	dev->hw_features |= NETIF_F_LOOPBACK;

	/* MTU range: 64 - 1500 or 9100 */
	dev->min_mtu = ETH_ZLEN + ETH_FCS_LEN;
	dev->max_mtu = np->pkt_limit;

	np->छोड़ो_flags = NV_PAUSEFRAME_RX_CAPABLE | NV_PAUSEFRAME_RX_REQ | NV_PAUSEFRAME_AUTONEG;
	अगर ((id->driver_data & DEV_HAS_PAUSEFRAME_TX_V1) ||
	    (id->driver_data & DEV_HAS_PAUSEFRAME_TX_V2) ||
	    (id->driver_data & DEV_HAS_PAUSEFRAME_TX_V3)) अणु
		np->छोड़ो_flags |= NV_PAUSEFRAME_TX_CAPABLE | NV_PAUSEFRAME_TX_REQ;
	पूर्ण

	err = -ENOMEM;
	np->base = ioremap(addr, np->रेजिस्टर_size);
	अगर (!np->base)
		जाओ out_relreg;

	np->rx_ring_size = RX_RING_DEFAULT;
	np->tx_ring_size = TX_RING_DEFAULT;

	अगर (!nv_optimized(np)) अणु
		np->rx_ring.orig = dma_alloc_coherent(&pci_dev->dev,
						      माप(काष्ठा ring_desc) *
						      (np->rx_ring_size +
						      np->tx_ring_size),
						      &np->ring_addr,
						      GFP_KERNEL);
		अगर (!np->rx_ring.orig)
			जाओ out_unmap;
		np->tx_ring.orig = &np->rx_ring.orig[np->rx_ring_size];
	पूर्ण अन्यथा अणु
		np->rx_ring.ex = dma_alloc_coherent(&pci_dev->dev,
						    माप(काष्ठा ring_desc_ex) *
						    (np->rx_ring_size +
						    np->tx_ring_size),
						    &np->ring_addr, GFP_KERNEL);
		अगर (!np->rx_ring.ex)
			जाओ out_unmap;
		np->tx_ring.ex = &np->rx_ring.ex[np->rx_ring_size];
	पूर्ण
	np->rx_skb = kसुस्मृति(np->rx_ring_size, माप(काष्ठा nv_skb_map), GFP_KERNEL);
	np->tx_skb = kसुस्मृति(np->tx_ring_size, माप(काष्ठा nv_skb_map), GFP_KERNEL);
	अगर (!np->rx_skb || !np->tx_skb)
		जाओ out_मुक्तring;

	अगर (!nv_optimized(np))
		dev->netdev_ops = &nv_netdev_ops;
	अन्यथा
		dev->netdev_ops = &nv_netdev_ops_optimized;

	netअगर_napi_add(dev, &np->napi, nv_napi_poll, RX_WORK_PER_LOOP);
	dev->ethtool_ops = &ops;
	dev->watchकरोg_समयo = NV_WATCHDOG_TIMEO;

	pci_set_drvdata(pci_dev, dev);

	/* पढ़ो the mac address */
	base = get_hwbase(dev);
	np->orig_mac[0] = पढ़ोl(base + NvRegMacAddrA);
	np->orig_mac[1] = पढ़ोl(base + NvRegMacAddrB);

	/* check the workaround bit क्रम correct mac address order */
	txreg = पढ़ोl(base + NvRegTransmitPoll);
	अगर (id->driver_data & DEV_HAS_CORRECT_MACADDR) अणु
		/* mac address is alपढ़ोy in correct order */
		dev->dev_addr[0] = (np->orig_mac[0] >>  0) & 0xff;
		dev->dev_addr[1] = (np->orig_mac[0] >>  8) & 0xff;
		dev->dev_addr[2] = (np->orig_mac[0] >> 16) & 0xff;
		dev->dev_addr[3] = (np->orig_mac[0] >> 24) & 0xff;
		dev->dev_addr[4] = (np->orig_mac[1] >>  0) & 0xff;
		dev->dev_addr[5] = (np->orig_mac[1] >>  8) & 0xff;
	पूर्ण अन्यथा अगर (txreg & NVREG_TRANSMITPOLL_MAC_ADDR_REV) अणु
		/* mac address is alपढ़ोy in correct order */
		dev->dev_addr[0] = (np->orig_mac[0] >>  0) & 0xff;
		dev->dev_addr[1] = (np->orig_mac[0] >>  8) & 0xff;
		dev->dev_addr[2] = (np->orig_mac[0] >> 16) & 0xff;
		dev->dev_addr[3] = (np->orig_mac[0] >> 24) & 0xff;
		dev->dev_addr[4] = (np->orig_mac[1] >>  0) & 0xff;
		dev->dev_addr[5] = (np->orig_mac[1] >>  8) & 0xff;
		/*
		 * Set orig mac address back to the reversed version.
		 * This flag will be cleared during low घातer transition.
		 * Thereक्रमe, we should always put back the reversed address.
		 */
		np->orig_mac[0] = (dev->dev_addr[5] << 0) + (dev->dev_addr[4] << 8) +
			(dev->dev_addr[3] << 16) + (dev->dev_addr[2] << 24);
		np->orig_mac[1] = (dev->dev_addr[1] << 0) + (dev->dev_addr[0] << 8);
	पूर्ण अन्यथा अणु
		/* need to reverse mac address to correct order */
		dev->dev_addr[0] = (np->orig_mac[1] >>  8) & 0xff;
		dev->dev_addr[1] = (np->orig_mac[1] >>  0) & 0xff;
		dev->dev_addr[2] = (np->orig_mac[0] >> 24) & 0xff;
		dev->dev_addr[3] = (np->orig_mac[0] >> 16) & 0xff;
		dev->dev_addr[4] = (np->orig_mac[0] >>  8) & 0xff;
		dev->dev_addr[5] = (np->orig_mac[0] >>  0) & 0xff;
		ग_लिखोl(txreg|NVREG_TRANSMITPOLL_MAC_ADDR_REV, base + NvRegTransmitPoll);
		dev_dbg(&pci_dev->dev,
			"%s: set workaround bit for reversed mac addr\n",
			__func__);
	पूर्ण

	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		/*
		 * Bad mac address. At least one bios sets the mac address
		 * to 01:23:45:67:89:ab
		 */
		dev_err(&pci_dev->dev,
			"Invalid MAC address detected: %pM - Please complain to your hardware vendor.\n",
			dev->dev_addr);
		eth_hw_addr_अक्रमom(dev);
		dev_err(&pci_dev->dev,
			"Using random MAC address: %pM\n", dev->dev_addr);
	पूर्ण

	/* set mac address */
	nv_copy_mac_to_hw(dev);

	/* disable WOL */
	ग_लिखोl(0, base + NvRegWakeUpFlags);
	np->wolenabled = 0;
	device_set_wakeup_enable(&pci_dev->dev, false);

	अगर (id->driver_data & DEV_HAS_POWER_CNTRL) अणु

		/* take phy and nic out of low घातer mode */
		घातerstate = पढ़ोl(base + NvRegPowerState2);
		घातerstate &= ~NVREG_POWERSTATE2_POWERUP_MASK;
		अगर ((id->driver_data & DEV_NEED_LOW_POWER_FIX) &&
		    pci_dev->revision >= 0xA3)
			घातerstate |= NVREG_POWERSTATE2_POWERUP_REV_A3;
		ग_लिखोl(घातerstate, base + NvRegPowerState2);
	पूर्ण

	अगर (np->desc_ver == DESC_VER_1)
		np->tx_flags = NV_TX_VALID;
	अन्यथा
		np->tx_flags = NV_TX2_VALID;

	np->msi_flags = 0;
	अगर ((id->driver_data & DEV_HAS_MSI) && msi)
		np->msi_flags |= NV_MSI_CAPABLE;

	अगर ((id->driver_data & DEV_HAS_MSI_X) && msix) अणु
		/* msix has had reported issues when modअगरying irqmask
		   as in the हाल of napi, thereक्रमe, disable क्रम now
		*/
#अगर 0
		np->msi_flags |= NV_MSI_X_CAPABLE;
#पूर्ण_अगर
	पूर्ण

	अगर (optimization_mode == NV_OPTIMIZATION_MODE_CPU) अणु
		np->irqmask = NVREG_IRQMASK_CPU;
		अगर (np->msi_flags & NV_MSI_X_CAPABLE) /* set number of vectors */
			np->msi_flags |= 0x0001;
	पूर्ण अन्यथा अगर (optimization_mode == NV_OPTIMIZATION_MODE_DYNAMIC &&
		   !(id->driver_data & DEV_NEED_TIMERIRQ)) अणु
		/* start off in throughput mode */
		np->irqmask = NVREG_IRQMASK_THROUGHPUT;
		/* हटाओ support क्रम msix mode */
		np->msi_flags &= ~NV_MSI_X_CAPABLE;
	पूर्ण अन्यथा अणु
		optimization_mode = NV_OPTIMIZATION_MODE_THROUGHPUT;
		np->irqmask = NVREG_IRQMASK_THROUGHPUT;
		अगर (np->msi_flags & NV_MSI_X_CAPABLE) /* set number of vectors */
			np->msi_flags |= 0x0003;
	पूर्ण

	अगर (id->driver_data & DEV_NEED_TIMERIRQ)
		np->irqmask |= NVREG_IRQ_TIMER;
	अगर (id->driver_data & DEV_NEED_LINKTIMER) अणु
		np->need_linkसमयr = 1;
		np->link_समयout = jअगरfies + LINK_TIMEOUT;
	पूर्ण अन्यथा अणु
		np->need_linkसमयr = 0;
	पूर्ण

	/* Limit the number of tx's outstanding क्रम hw bug */
	अगर (id->driver_data & DEV_NEED_TX_LIMIT) अणु
		np->tx_limit = 1;
		अगर (((id->driver_data & DEV_NEED_TX_LIMIT2) == DEV_NEED_TX_LIMIT2) &&
		    pci_dev->revision >= 0xA2)
			np->tx_limit = 0;
	पूर्ण

	/* clear phy state and temporarily halt phy पूर्णांकerrupts */
	ग_लिखोl(0, base + NvRegMIIMask);
	phystate = पढ़ोl(base + NvRegAdapterControl);
	अगर (phystate & NVREG_ADAPTCTL_RUNNING) अणु
		phystate_orig = 1;
		phystate &= ~NVREG_ADAPTCTL_RUNNING;
		ग_लिखोl(phystate, base + NvRegAdapterControl);
	पूर्ण
	ग_लिखोl(NVREG_MIISTAT_MASK_ALL, base + NvRegMIIStatus);

	अगर (id->driver_data & DEV_HAS_MGMT_UNIT) अणु
		/* management unit running on the mac? */
		अगर ((पढ़ोl(base + NvRegTransmitterControl) & NVREG_XMITCTL_MGMT_ST) &&
		    (पढ़ोl(base + NvRegTransmitterControl) & NVREG_XMITCTL_SYNC_PHY_INIT) &&
		    nv_mgmt_acquire_sema(dev) &&
		    nv_mgmt_get_version(dev)) अणु
			np->mac_in_use = 1;
			अगर (np->mgmt_version > 0)
				np->mac_in_use = पढ़ोl(base + NvRegMgmtUnitControl) & NVREG_MGMTUNITCONTROL_INUSE;
			/* management unit setup the phy alपढ़ोy? */
			अगर (np->mac_in_use &&
			    ((पढ़ोl(base + NvRegTransmitterControl) & NVREG_XMITCTL_SYNC_MASK) ==
			     NVREG_XMITCTL_SYNC_PHY_INIT)) अणु
				/* phy is inited by mgmt unit */
				phyinitialized = 1;
			पूर्ण अन्यथा अणु
				/* we need to init the phy */
			पूर्ण
		पूर्ण
	पूर्ण

	/* find a suitable phy */
	क्रम (i = 1; i <= 32; i++) अणु
		पूर्णांक id1, id2;
		पूर्णांक phyaddr = i & 0x1F;

		spin_lock_irq(&np->lock);
		id1 = mii_rw(dev, phyaddr, MII_PHYSID1, MII_READ);
		spin_unlock_irq(&np->lock);
		अगर (id1 < 0 || id1 == 0xffff)
			जारी;
		spin_lock_irq(&np->lock);
		id2 = mii_rw(dev, phyaddr, MII_PHYSID2, MII_READ);
		spin_unlock_irq(&np->lock);
		अगर (id2 < 0 || id2 == 0xffff)
			जारी;

		np->phy_model = id2 & PHYID2_MODEL_MASK;
		id1 = (id1 & PHYID1_OUI_MASK) << PHYID1_OUI_SHFT;
		id2 = (id2 & PHYID2_OUI_MASK) >> PHYID2_OUI_SHFT;
		np->phyaddr = phyaddr;
		np->phy_oui = id1 | id2;

		/* Realtek hardcoded phy id1 to all zero's on certain phys */
		अगर (np->phy_oui == PHY_OUI_REALTEK2)
			np->phy_oui = PHY_OUI_REALTEK;
		/* Setup phy revision क्रम Realtek */
		अगर (np->phy_oui == PHY_OUI_REALTEK && np->phy_model == PHY_MODEL_REALTEK_8211)
			np->phy_rev = mii_rw(dev, phyaddr, MII_RESV1, MII_READ) & PHY_REV_MASK;

		अवरोध;
	पूर्ण
	अगर (i == 33) अणु
		dev_info(&pci_dev->dev, "open: Could not find a valid PHY\n");
		जाओ out_error;
	पूर्ण

	अगर (!phyinitialized) अणु
		/* reset it */
		phy_init(dev);
	पूर्ण अन्यथा अणु
		/* see अगर it is a gigabit phy */
		u32 mii_status = mii_rw(dev, np->phyaddr, MII_BMSR, MII_READ);
		अगर (mii_status & PHY_GIGABIT)
			np->gigabit = PHY_GIGABIT;
	पूर्ण

	/* set शेष link speed settings */
	np->linkspeed = NVREG_LINKSPEED_FORCE|NVREG_LINKSPEED_10;
	np->duplex = 0;
	np->स्वतःneg = 1;

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_info(&pci_dev->dev, "unable to register netdev: %d\n", err);
		जाओ out_error;
	पूर्ण

	netअगर_carrier_off(dev);

	/* Some NICs मुक्तze when TX छोड़ो is enabled जबतक NIC is
	 * करोwn, and this stays across warm reboots. The sequence
	 * below should be enough to recover from that state.
	 */
	nv_update_छोड़ो(dev, 0);
	nv_start_tx(dev);
	nv_stop_tx(dev);

	अगर (id->driver_data & DEV_HAS_VLAN)
		nv_vlan_mode(dev, dev->features);

	dev_info(&pci_dev->dev, "ifname %s, PHY OUI 0x%x @ %d, addr %pM\n",
		 dev->name, np->phy_oui, np->phyaddr, dev->dev_addr);

	dev_info(&pci_dev->dev, "%s%s%s%s%s%s%s%s%s%s%sdesc-v%u\n",
		 dev->features & NETIF_F_HIGHDMA ? "highdma " : "",
		 dev->features & (NETIF_F_IP_CSUM | NETIF_F_SG) ?
			"csum " : "",
		 dev->features & (NETIF_F_HW_VLAN_CTAG_RX |
				  NETIF_F_HW_VLAN_CTAG_TX) ?
			"vlan " : "",
		 dev->features & (NETIF_F_LOOPBACK) ?
			"loopback " : "",
		 id->driver_data & DEV_HAS_POWER_CNTRL ? "pwrctl " : "",
		 id->driver_data & DEV_HAS_MGMT_UNIT ? "mgmt " : "",
		 id->driver_data & DEV_NEED_TIMERIRQ ? "timirq " : "",
		 np->gigabit == PHY_GIGABIT ? "gbit " : "",
		 np->need_linkसमयr ? "lnktim " : "",
		 np->msi_flags & NV_MSI_CAPABLE ? "msi " : "",
		 np->msi_flags & NV_MSI_X_CAPABLE ? "msi-x " : "",
		 np->desc_ver);

	वापस 0;

out_error:
	अगर (phystate_orig)
		ग_लिखोl(phystate|NVREG_ADAPTCTL_RUNNING, base + NvRegAdapterControl);
out_मुक्तring:
	मुक्त_rings(dev);
out_unmap:
	iounmap(get_hwbase(dev));
out_relreg:
	pci_release_regions(pci_dev);
out_disable:
	pci_disable_device(pci_dev);
out_मुक्त:
	मुक्त_percpu(np->txrx_stats);
out_alloc_percpu:
	मुक्त_netdev(dev);
out:
	वापस err;
पूर्ण

अटल व्योम nv_restore_phy(काष्ठा net_device *dev)
अणु
	काष्ठा fe_priv *np = netdev_priv(dev);
	u16 phy_reserved, mii_control;

	अगर (np->phy_oui == PHY_OUI_REALTEK &&
	    np->phy_model == PHY_MODEL_REALTEK_8201 &&
	    phy_cross == NV_CROSSOVER_DETECTION_DISABLED) अणु
		mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT3);
		phy_reserved = mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG2, MII_READ);
		phy_reserved &= ~PHY_REALTEK_INIT_MSK1;
		phy_reserved |= PHY_REALTEK_INIT8;
		mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG2, phy_reserved);
		mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT1);

		/* restart स्वतः negotiation */
		mii_control = mii_rw(dev, np->phyaddr, MII_BMCR, MII_READ);
		mii_control |= (BMCR_ANRESTART | BMCR_ANENABLE);
		mii_rw(dev, np->phyaddr, MII_BMCR, mii_control);
	पूर्ण
पूर्ण

अटल व्योम nv_restore_mac_addr(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pci_dev);
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);

	/* special op: ग_लिखो back the misordered MAC address - otherwise
	 * the next nv_probe would see a wrong address.
	 */
	ग_लिखोl(np->orig_mac[0], base + NvRegMacAddrA);
	ग_लिखोl(np->orig_mac[1], base + NvRegMacAddrB);
	ग_लिखोl(पढ़ोl(base + NvRegTransmitPoll) & ~NVREG_TRANSMITPOLL_MAC_ADDR_REV,
	       base + NvRegTransmitPoll);
पूर्ण

अटल व्योम nv_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pci_dev);
	काष्ठा fe_priv *np = netdev_priv(dev);

	मुक्त_percpu(np->txrx_stats);

	unरेजिस्टर_netdev(dev);

	nv_restore_mac_addr(pci_dev);

	/* restore any phy related changes */
	nv_restore_phy(dev);

	nv_mgmt_release_sema(dev);

	/* मुक्त all काष्ठाures */
	मुक्त_rings(dev);
	iounmap(get_hwbase(dev));
	pci_release_regions(pci_dev);
	pci_disable_device(pci_dev);
	मुक्त_netdev(dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक nv_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	पूर्णांक i;

	अगर (netअगर_running(dev)) अणु
		/* Gross. */
		nv_बंद(dev);
	पूर्ण
	netअगर_device_detach(dev);

	/* save non-pci configuration space */
	क्रम (i = 0; i <= np->रेजिस्टर_size/माप(u32); i++)
		np->saved_config_space[i] = पढ़ोl(base + i*माप(u32));

	वापस 0;
पूर्ण

अटल पूर्णांक nv_resume(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा fe_priv *np = netdev_priv(dev);
	u8 __iomem *base = get_hwbase(dev);
	पूर्णांक i, rc = 0;

	/* restore non-pci configuration space */
	क्रम (i = 0; i <= np->रेजिस्टर_size/माप(u32); i++)
		ग_लिखोl(np->saved_config_space[i], base+i*माप(u32));

	अगर (np->driver_data & DEV_NEED_MSI_FIX)
		pci_ग_लिखो_config_dword(pdev, NV_MSI_PRIV_OFFSET, NV_MSI_PRIV_VALUE);

	/* restore phy state, including स्वतःneg */
	phy_init(dev);

	netअगर_device_attach(dev);
	अगर (netअगर_running(dev)) अणु
		rc = nv_खोलो(dev);
		nv_set_multicast(dev);
	पूर्ण
	वापस rc;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(nv_pm_ops, nv_suspend, nv_resume);
#घोषणा NV_PM_OPS (&nv_pm_ops)

#अन्यथा
#घोषणा NV_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल व्योम nv_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा fe_priv *np = netdev_priv(dev);

	अगर (netअगर_running(dev))
		nv_बंद(dev);

	/*
	 * Restore the MAC so a kernel started by kexec won't get confused.
	 * If we really go क्रम घातeroff, we must not restore the MAC,
	 * otherwise the MAC क्रम WOL will be reversed at least on some boards.
	 */
	अगर (प्रणाली_state != SYSTEM_POWER_OFF)
		nv_restore_mac_addr(pdev);

	pci_disable_device(pdev);
	/*
	 * Apparently it is not possible to reinitialise from D3 hot,
	 * only put the device पूर्णांकo D3 अगर we really go क्रम घातeroff.
	 */
	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, np->wolenabled);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा nv_shutकरोwn शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	अणु	/* nForce Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x01C3),
		.driver_data = DEV_NEED_TIMERIRQ|DEV_NEED_LINKTIMER,
	पूर्ण,
	अणु	/* nForce2 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0066),
		.driver_data = DEV_NEED_TIMERIRQ|DEV_NEED_LINKTIMER,
	पूर्ण,
	अणु	/* nForce3 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x00D6),
		.driver_data = DEV_NEED_TIMERIRQ|DEV_NEED_LINKTIMER,
	पूर्ण,
	अणु	/* nForce3 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0086),
		.driver_data = DEV_NEED_TIMERIRQ|DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM,
	पूर्ण,
	अणु	/* nForce3 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x008C),
		.driver_data = DEV_NEED_TIMERIRQ|DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM,
	पूर्ण,
	अणु	/* nForce3 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x00E6),
		.driver_data = DEV_NEED_TIMERIRQ|DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM,
	पूर्ण,
	अणु	/* nForce3 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x00DF),
		.driver_data = DEV_NEED_TIMERIRQ|DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM,
	पूर्ण,
	अणु	/* CK804 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0056),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_STATISTICS_V1|DEV_NEED_TX_LIMIT,
	पूर्ण,
	अणु	/* CK804 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0057),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_STATISTICS_V1|DEV_NEED_TX_LIMIT,
	पूर्ण,
	अणु	/* MCP04 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0037),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_STATISTICS_V1|DEV_NEED_TX_LIMIT,
	पूर्ण,
	अणु	/* MCP04 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0038),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_STATISTICS_V1|DEV_NEED_TX_LIMIT,
	पूर्ण,
	अणु	/* MCP51 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0268),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_STATISTICS_V1|DEV_NEED_LOW_POWER_FIX,
	पूर्ण,
	अणु	/* MCP51 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0269),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_STATISTICS_V1|DEV_NEED_LOW_POWER_FIX,
	पूर्ण,
	अणु	/* MCP55 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0372),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_VLAN|DEV_HAS_MSI|DEV_HAS_MSI_X|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_NEED_TX_LIMIT|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP55 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0373),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_VLAN|DEV_HAS_MSI|DEV_HAS_MSI_X|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_NEED_TX_LIMIT|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP61 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x03E5),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP61 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x03E6),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP61 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x03EE),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP61 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x03EF),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP65 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0450),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_NEED_TX_LIMIT|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP65 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0451),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_NEED_TX_LIMIT|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP65 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0452),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_NEED_TX_LIMIT|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP65 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0453),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_NEED_TX_LIMIT|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP67 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x054C),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP67 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x054D),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP67 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x054E),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP67 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x054F),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP73 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x07DC),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP73 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x07DD),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP73 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x07DE),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP73 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x07DF),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_HIGH_DMA|DEV_HAS_POWER_CNTRL|DEV_HAS_MSI|DEV_HAS_PAUSEFRAME_TX_V1|DEV_HAS_STATISTICS_V12|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_HAS_GEAR_MODE|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP77 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0760),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_MSI|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V2|DEV_HAS_STATISTICS_V123|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_NEED_TX_LIMIT2|DEV_HAS_GEAR_MODE|DEV_NEED_PHY_INIT_FIX|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP77 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0761),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_MSI|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V2|DEV_HAS_STATISTICS_V123|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_NEED_TX_LIMIT2|DEV_HAS_GEAR_MODE|DEV_NEED_PHY_INIT_FIX|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP77 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0762),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_MSI|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V2|DEV_HAS_STATISTICS_V123|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_NEED_TX_LIMIT2|DEV_HAS_GEAR_MODE|DEV_NEED_PHY_INIT_FIX|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP77 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0763),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_MSI|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V2|DEV_HAS_STATISTICS_V123|DEV_HAS_TEST_EXTENDED|DEV_HAS_MGMT_UNIT|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_NEED_TX_LIMIT2|DEV_HAS_GEAR_MODE|DEV_NEED_PHY_INIT_FIX|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP79 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0AB0),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_MSI|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V3|DEV_HAS_STATISTICS_V123|DEV_HAS_TEST_EXTENDED|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_NEED_TX_LIMIT2|DEV_HAS_GEAR_MODE|DEV_NEED_PHY_INIT_FIX|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP79 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0AB1),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_MSI|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V3|DEV_HAS_STATISTICS_V123|DEV_HAS_TEST_EXTENDED|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_NEED_TX_LIMIT2|DEV_HAS_GEAR_MODE|DEV_NEED_PHY_INIT_FIX|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP79 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0AB2),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_MSI|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V3|DEV_HAS_STATISTICS_V123|DEV_HAS_TEST_EXTENDED|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_NEED_TX_LIMIT2|DEV_HAS_GEAR_MODE|DEV_NEED_PHY_INIT_FIX|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP79 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0AB3),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_MSI|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V3|DEV_HAS_STATISTICS_V123|DEV_HAS_TEST_EXTENDED|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_NEED_TX_LIMIT2|DEV_HAS_GEAR_MODE|DEV_NEED_PHY_INIT_FIX|DEV_NEED_MSI_FIX,
	पूर्ण,
	अणु	/* MCP89 Ethernet Controller */
		PCI_DEVICE(0x10DE, 0x0D7D),
		.driver_data = DEV_NEED_LINKTIMER|DEV_HAS_LARGEDESC|DEV_HAS_CHECKSUM|DEV_HAS_HIGH_DMA|DEV_HAS_MSI|DEV_HAS_POWER_CNTRL|DEV_HAS_PAUSEFRAME_TX_V3|DEV_HAS_STATISTICS_V123|DEV_HAS_TEST_EXTENDED|DEV_HAS_CORRECT_MACADDR|DEV_HAS_COLLISION_FIX|DEV_HAS_GEAR_MODE|DEV_NEED_PHY_INIT_FIX,
	पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver क्रमcedeth_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= pci_tbl,
	.probe		= nv_probe,
	.हटाओ		= nv_हटाओ,
	.shutकरोwn	= nv_shutकरोwn,
	.driver.pm	= NV_PM_OPS,
पूर्ण;

module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "forcedeth maximum events handled per interrupt");
module_param(optimization_mode, पूर्णांक, 0);
MODULE_PARM_DESC(optimization_mode, "In throughput mode (0), every tx & rx packet will generate an interrupt. In CPU mode (1), interrupts are controlled by a timer. In dynamic mode (2), the mode toggles between throughput and CPU mode based on network load.");
module_param(poll_पूर्णांकerval, पूर्णांक, 0);
MODULE_PARM_DESC(poll_पूर्णांकerval, "Interval determines how frequent समयr पूर्णांकerrupt is generated by [(समय_in_micro_secs * 100) / (2^10)]. Min is 0 and Max is 65535.");
module_param(msi, पूर्णांक, 0);
MODULE_PARM_DESC(msi, "MSI interrupts are enabled by setting to 1 and disabled by setting to 0.");
module_param(msix, पूर्णांक, 0);
MODULE_PARM_DESC(msix, "MSIX interrupts are enabled by setting to 1 and disabled by setting to 0.");
module_param(dma_64bit, पूर्णांक, 0);
MODULE_PARM_DESC(dma_64bit, "High DMA is enabled by setting to 1 and disabled by setting to 0.");
module_param(phy_cross, पूर्णांक, 0);
MODULE_PARM_DESC(phy_cross, "Phy crossover detection for Realtek 8201 phy is enabled by setting to 1 and disabled by setting to 0.");
module_param(phy_घातer_करोwn, पूर्णांक, 0);
MODULE_PARM_DESC(phy_घातer_करोwn, "Power down phy and disable link when interface is down (1), or leave phy powered up (0).");
module_param(debug_tx_समयout, bool, 0);
MODULE_PARM_DESC(debug_tx_समयout,
		 "Dump tx related registers and ring when tx_timeout happens");

module_pci_driver(क्रमcedeth_pci_driver);
MODULE_AUTHOR("Manfred Spraul <manfred@colorfullife.com>");
MODULE_DESCRIPTION("Reverse Engineered nForce ethernet driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, pci_tbl);
