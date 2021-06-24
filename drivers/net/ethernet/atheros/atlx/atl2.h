<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* atl2.h -- atl2 driver definitions
 *
 * Copyright(c) 2007 Atheros Corporation. All rights reserved.
 * Copyright(c) 2006 xiong huang <xiong.huang@atheros.com>
 * Copyright(c) 2007 Chris Snook <csnook@redhat.com>
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित _ATL2_H_
#घोषणा _ATL2_H_

#समावेश <linux/atomic.h>
#समावेश <linux/netdevice.h>

#अगर_अघोषित _ATL2_HW_H_
#घोषणा _ATL2_HW_H_

#अगर_अघोषित _ATL2_OSDEP_H_
#घोषणा _ATL2_OSDEP_H_

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_ether.h>

#समावेश "atlx.h"

#अगर_घोषित ETHTOOL_OPS_COMPAT
पूर्णांक ethtool_ioctl(काष्ठा अगरreq *अगरr);
#पूर्ण_अगर

#घोषणा PCI_COMMAND_REGISTER	PCI_COMMAND
#घोषणा CMD_MEM_WRT_INVALIDATE	PCI_COMMAND_INVALIDATE

#घोषणा ATL2_WRITE_REG(a, reg, value) (ioग_लिखो32((value), \
	((a)->hw_addr + (reg))))

#घोषणा ATL2_WRITE_FLUSH(a) (ioपढ़ो32((a)->hw_addr))

#घोषणा ATL2_READ_REG(a, reg) (ioपढ़ो32((a)->hw_addr + (reg)))

#घोषणा ATL2_WRITE_REGB(a, reg, value) (ioग_लिखो8((value), \
	((a)->hw_addr + (reg))))

#घोषणा ATL2_READ_REGB(a, reg) (ioपढ़ो8((a)->hw_addr + (reg)))

#घोषणा ATL2_WRITE_REGW(a, reg, value) (ioग_लिखो16((value), \
	((a)->hw_addr + (reg))))

#घोषणा ATL2_READ_REGW(a, reg) (ioपढ़ो16((a)->hw_addr + (reg)))

#घोषणा ATL2_WRITE_REG_ARRAY(a, reg, offset, value) \
	(ioग_लिखो32((value), (((a)->hw_addr + (reg)) + ((offset) << 2))))

#घोषणा ATL2_READ_REG_ARRAY(a, reg, offset) \
	(ioपढ़ो32(((a)->hw_addr + (reg)) + ((offset) << 2)))

#पूर्ण_अगर /* _ATL2_OSDEP_H_ */

काष्ठा atl2_adapter;
काष्ठा atl2_hw;

/* function prototype */
अटल s32 atl2_reset_hw(काष्ठा atl2_hw *hw);
अटल s32 atl2_पढ़ो_mac_addr(काष्ठा atl2_hw *hw);
अटल s32 atl2_init_hw(काष्ठा atl2_hw *hw);
अटल s32 atl2_get_speed_and_duplex(काष्ठा atl2_hw *hw, u16 *speed,
	u16 *duplex);
अटल u32 atl2_hash_mc_addr(काष्ठा atl2_hw *hw, u8 *mc_addr);
अटल व्योम atl2_hash_set(काष्ठा atl2_hw *hw, u32 hash_value);
अटल s32 atl2_पढ़ो_phy_reg(काष्ठा atl2_hw *hw, u16 reg_addr, u16 *phy_data);
अटल s32 atl2_ग_लिखो_phy_reg(काष्ठा atl2_hw *hw, u32 reg_addr, u16 phy_data);
अटल व्योम atl2_पढ़ो_pci_cfg(काष्ठा atl2_hw *hw, u32 reg, u16 *value);
अटल व्योम atl2_ग_लिखो_pci_cfg(काष्ठा atl2_hw *hw, u32 reg, u16 *value);
अटल व्योम atl2_set_mac_addr(काष्ठा atl2_hw *hw);
अटल bool atl2_पढ़ो_eeprom(काष्ठा atl2_hw *hw, u32 Offset, u32 *pValue);
अटल bool atl2_ग_लिखो_eeprom(काष्ठा atl2_hw *hw, u32 offset, u32 value);
अटल s32 atl2_phy_init(काष्ठा atl2_hw *hw);
अटल पूर्णांक atl2_check_eeprom_exist(काष्ठा atl2_hw *hw);
अटल व्योम atl2_क्रमce_ps(काष्ठा atl2_hw *hw);

/* रेजिस्टर definition */

/* Block IDLE Status Register */
#घोषणा IDLE_STATUS_RXMAC	1	/* 1: RXMAC is non-IDLE */
#घोषणा IDLE_STATUS_TXMAC	2	/* 1: TXMAC is non-IDLE */
#घोषणा IDLE_STATUS_DMAR	8	/* 1: DMAR is non-IDLE */
#घोषणा IDLE_STATUS_DMAW	4	/* 1: DMAW is non-IDLE */

/* MDIO Control Register */
#घोषणा MDIO_WAIT_TIMES		10

/* MAC Control Register */
#घोषणा MAC_CTRL_DBG_TX_BKPRESURE	0x100000	/* 1: TX max backoff */
#घोषणा MAC_CTRL_MACLP_CLK_PHY		0x8000000	/* 1: 25MHz from phy */
#घोषणा MAC_CTRL_HALF_LEFT_BUF_SHIFT	28
#घोषणा MAC_CTRL_HALF_LEFT_BUF_MASK	0xF		/* MAC retry buf x32B */

/* Internal SRAM Partition Register */
#घोषणा REG_SRAM_TXRAM_END	0x1500	/* Internal tail address of TXRAM
					 * शेष: 2byte*1024 */
#घोषणा REG_SRAM_RXRAM_END	0x1502	/* Internal tail address of RXRAM
					 * शेष: 2byte*1024 */

/* Descriptor Control रेजिस्टर */
#घोषणा REG_TXD_BASE_ADDR_LO	0x1544	/* The base address of the Transmit
					 * Data Mem low 32-bit(dword align) */
#घोषणा REG_TXD_MEM_SIZE	0x1548	/* Transmit Data Memory size(by
					 * द्विगुन word , max 256KB) */
#घोषणा REG_TXS_BASE_ADDR_LO	0x154C	/* The base address of the Transmit
					 * Status Memory low 32-bit(dword word
					 * align) */
#घोषणा REG_TXS_MEM_SIZE	0x1550	/* द्विगुन word unit, max 4*2047
					 * bytes. */
#घोषणा REG_RXD_BASE_ADDR_LO	0x1554	/* The base address of the Transmit
					 * Status Memory low 32-bit(unit 8
					 * bytes) */
#घोषणा REG_RXD_BUF_NUM		0x1558	/* Receive Data & Status Memory buffer
					 * number (unit 1536bytes, max
					 * 1536*2047) */

/* DMAR Control Register */
#घोषणा REG_DMAR	0x1580
#घोषणा     DMAR_EN	0x1	/* 1: Enable DMAR */

/* TX Cur-Through (early tx threshold) Control Register */
#घोषणा REG_TX_CUT_THRESH	0x1590	/* TxMac begin transmit packet
					 * threshold(unit word) */

/* DMAW Control Register */
#घोषणा REG_DMAW	0x15A0
#घोषणा     DMAW_EN	0x1

/* Flow control रेजिस्टर */
#घोषणा REG_PAUSE_ON_TH		0x15A8	/* RXD high watermark of overflow
					 * threshold configuration रेजिस्टर */
#घोषणा REG_PAUSE_OFF_TH	0x15AA	/* RXD lower watermark of overflow
					 * threshold configuration रेजिस्टर */

/* Mailbox Register */
#घोषणा REG_MB_TXD_WR_IDX	0x15f0	/* द्विगुन word align */
#घोषणा REG_MB_RXD_RD_IDX	0x15F4	/* RXD Read index (unit: 1536byets) */

/* Interrupt Status Register */
#घोषणा ISR_TIMER	1	/* Interrupt when Timer counts करोwn to zero */
#घोषणा ISR_MANUAL	2	/* Software manual पूर्णांकerrupt, क्रम debug. Set
				 * when SW_MAN_INT_EN is set in Table 51
				 * Selene Master Control Register
				 * (Offset 0x1400). */
#घोषणा ISR_RXF_OV	4	/* RXF overflow पूर्णांकerrupt */
#घोषणा ISR_TXF_UR	8	/* TXF underrun पूर्णांकerrupt */
#घोषणा ISR_TXS_OV	0x10	/* Internal transmit status buffer full
				 * पूर्णांकerrupt */
#घोषणा ISR_RXS_OV	0x20	/* Internal receive status buffer full
				 * पूर्णांकerrupt */
#घोषणा ISR_LINK_CHG	0x40	/* Link Status Change Interrupt */
#घोषणा ISR_HOST_TXD_UR	0x80
#घोषणा ISR_HOST_RXD_OV	0x100	/* Host rx data memory full , one pulse */
#घोषणा ISR_DMAR_TO_RST	0x200	/* DMAR op समयout पूर्णांकerrupt. SW should
				 * करो Reset */
#घोषणा ISR_DMAW_TO_RST	0x400
#घोषणा ISR_PHY		0x800	/* phy पूर्णांकerrupt */
#घोषणा ISR_TS_UPDATE	0x10000	/* पूर्णांकerrupt after new tx pkt status written
				 * to host */
#घोषणा ISR_RS_UPDATE	0x20000	/* पूर्णांकerrupt ater new rx pkt status written
				 * to host. */
#घोषणा ISR_TX_EARLY	0x40000	/* पूर्णांकerrupt when txmac begin transmit one
				 * packet */

#घोषणा ISR_TX_EVENT (ISR_TXF_UR | ISR_TXS_OV | ISR_HOST_TXD_UR |\
	ISR_TS_UPDATE | ISR_TX_EARLY)
#घोषणा ISR_RX_EVENT (ISR_RXF_OV | ISR_RXS_OV | ISR_HOST_RXD_OV |\
	 ISR_RS_UPDATE)

#घोषणा IMR_NORMAL_MASK		(\
	/*ISR_LINK_CHG		|*/\
	ISR_MANUAL		|\
	ISR_DMAR_TO_RST		|\
	ISR_DMAW_TO_RST		|\
	ISR_PHY			|\
	ISR_PHY_LINKDOWN	|\
	ISR_TS_UPDATE		|\
	ISR_RS_UPDATE)

/* Receive MAC Statistics Registers */
#घोषणा REG_STS_RX_PAUSE	0x1700	/* Num छोड़ो packets received */
#घोषणा REG_STS_RXD_OV		0x1704	/* Num frames dropped due to RX
					 * FIFO overflow */
#घोषणा REG_STS_RXS_OV		0x1708	/* Num frames dropped due to RX
					 * Status Buffer Overflow */
#घोषणा REG_STS_RX_FILTER	0x170C	/* Num packets dropped due to
					 * address filtering */

/* MII definitions */

/* PHY Common Register */
#घोषणा MII_SMARTSPEED	0x14
#घोषणा MII_DBG_ADDR	0x1D
#घोषणा MII_DBG_DATA	0x1E

/* PCI Command Register Bit Definitions */
#घोषणा PCI_REG_COMMAND		0x04
#घोषणा CMD_IO_SPACE		0x0001
#घोषणा CMD_MEMORY_SPACE	0x0002
#घोषणा CMD_BUS_MASTER		0x0004

#घोषणा MEDIA_TYPE_100M_FULL	1
#घोषणा MEDIA_TYPE_100M_HALF	2
#घोषणा MEDIA_TYPE_10M_FULL	3
#घोषणा MEDIA_TYPE_10M_HALF	4

#घोषणा AUTONEG_ADVERTISE_SPEED_DEFAULT	0x000F	/* Everything */

/* The size (in bytes) of a ethernet packet */
#घोषणा MAXIMUM_ETHERNET_FRAME_SIZE	1518	/* with FCS */
#घोषणा MINIMUM_ETHERNET_FRAME_SIZE	64	/* with FCS */
#घोषणा MAX_JUMBO_FRAME_SIZE		0x2000

काष्ठा tx_pkt_header अणु
	अचिन्हित pkt_size:11;
	अचिन्हित:4;			/* reserved */
	अचिन्हित ins_vlan:1;		/* txmac should insert vlan */
	अचिन्हित लघु vlan;		/* vlan tag */
पूर्ण;
/* FIXME: replace above bitfields with MASK/SHIFT defines below */
#घोषणा TX_PKT_HEADER_SIZE_MASK		0x7FF
#घोषणा TX_PKT_HEADER_SIZE_SHIFT	0
#घोषणा TX_PKT_HEADER_INS_VLAN_MASK	0x1
#घोषणा TX_PKT_HEADER_INS_VLAN_SHIFT	15
#घोषणा TX_PKT_HEADER_VLAN_TAG_MASK	0xFFFF
#घोषणा TX_PKT_HEADER_VLAN_TAG_SHIFT	16

काष्ठा tx_pkt_status अणु
	अचिन्हित pkt_size:11;
	अचिन्हित:5;		/* reserved */
	अचिन्हित ok:1;		/* current packet transmitted without error */
	अचिन्हित bcast:1;	/* broadcast packet */
	अचिन्हित mcast:1;	/* multicast packet */
	अचिन्हित छोड़ो:1;	/* transmiited a छोड़ो frame */
	अचिन्हित ctrl:1;
	अचिन्हित defer:1;    	/* current packet is xmitted with defer */
	अचिन्हित exc_defer:1;
	अचिन्हित single_col:1;
	अचिन्हित multi_col:1;
	अचिन्हित late_col:1;
	अचिन्हित पात_col:1;
	अचिन्हित underrun:1;	/* current packet is पातed
				 * due to txram underrun */
	अचिन्हित:3;		/* reserved */
	अचिन्हित update:1;	/* always 1'b1 in tx_status_buf */
पूर्ण;
/* FIXME: replace above bitfields with MASK/SHIFT defines below */
#घोषणा TX_PKT_STATUS_SIZE_MASK		0x7FF
#घोषणा TX_PKT_STATUS_SIZE_SHIFT	0
#घोषणा TX_PKT_STATUS_OK_MASK		0x1
#घोषणा TX_PKT_STATUS_OK_SHIFT		16
#घोषणा TX_PKT_STATUS_BCAST_MASK	0x1
#घोषणा TX_PKT_STATUS_BCAST_SHIFT	17
#घोषणा TX_PKT_STATUS_MCAST_MASK	0x1
#घोषणा TX_PKT_STATUS_MCAST_SHIFT	18
#घोषणा TX_PKT_STATUS_PAUSE_MASK	0x1
#घोषणा TX_PKT_STATUS_PAUSE_SHIFT	19
#घोषणा TX_PKT_STATUS_CTRL_MASK		0x1
#घोषणा TX_PKT_STATUS_CTRL_SHIFT	20
#घोषणा TX_PKT_STATUS_DEFER_MASK	0x1
#घोषणा TX_PKT_STATUS_DEFER_SHIFT	21
#घोषणा TX_PKT_STATUS_EXC_DEFER_MASK	0x1
#घोषणा TX_PKT_STATUS_EXC_DEFER_SHIFT	22
#घोषणा TX_PKT_STATUS_SINGLE_COL_MASK	0x1
#घोषणा TX_PKT_STATUS_SINGLE_COL_SHIFT	23
#घोषणा TX_PKT_STATUS_MULTI_COL_MASK	0x1
#घोषणा TX_PKT_STATUS_MULTI_COL_SHIFT	24
#घोषणा TX_PKT_STATUS_LATE_COL_MASK	0x1
#घोषणा TX_PKT_STATUS_LATE_COL_SHIFT	25
#घोषणा TX_PKT_STATUS_ABORT_COL_MASK	0x1
#घोषणा TX_PKT_STATUS_ABORT_COL_SHIFT	26
#घोषणा TX_PKT_STATUS_UNDERRUN_MASK	0x1
#घोषणा TX_PKT_STATUS_UNDERRUN_SHIFT	27
#घोषणा TX_PKT_STATUS_UPDATE_MASK	0x1
#घोषणा TX_PKT_STATUS_UPDATE_SHIFT	31

काष्ठा rx_pkt_status अणु
	अचिन्हित pkt_size:11;	/* packet size, max 2047 bytes */
	अचिन्हित:5;		/* reserved */
	अचिन्हित ok:1;		/* current packet received ok without error */
	अचिन्हित bcast:1;	/* current packet is broadcast */
	अचिन्हित mcast:1;	/* current packet is multicast */
	अचिन्हित छोड़ो:1;
	अचिन्हित ctrl:1;
	अचिन्हित crc:1;		/* received a packet with crc error */
	अचिन्हित code:1;	/* received a packet with code error */
	अचिन्हित runt:1;	/* received a packet less than 64 bytes
				 * with good crc */
	अचिन्हित frag:1;	/* received a packet less than 64 bytes
				 * with bad crc */
	अचिन्हित trunc:1;	/* current frame truncated due to rxram full */
	अचिन्हित align:1;	/* this packet is alignment error */
	अचिन्हित vlan:1;	/* this packet has vlan */
	अचिन्हित:3;		/* reserved */
	अचिन्हित update:1;
	अचिन्हित लघु vtag;	/* vlan tag */
	अचिन्हित:16;
पूर्ण;
/* FIXME: replace above bitfields with MASK/SHIFT defines below */
#घोषणा RX_PKT_STATUS_SIZE_MASK		0x7FF
#घोषणा RX_PKT_STATUS_SIZE_SHIFT	0
#घोषणा RX_PKT_STATUS_OK_MASK		0x1
#घोषणा RX_PKT_STATUS_OK_SHIFT		16
#घोषणा RX_PKT_STATUS_BCAST_MASK	0x1
#घोषणा RX_PKT_STATUS_BCAST_SHIFT	17
#घोषणा RX_PKT_STATUS_MCAST_MASK	0x1
#घोषणा RX_PKT_STATUS_MCAST_SHIFT	18
#घोषणा RX_PKT_STATUS_PAUSE_MASK	0x1
#घोषणा RX_PKT_STATUS_PAUSE_SHIFT	19
#घोषणा RX_PKT_STATUS_CTRL_MASK		0x1
#घोषणा RX_PKT_STATUS_CTRL_SHIFT	20
#घोषणा RX_PKT_STATUS_CRC_MASK		0x1
#घोषणा RX_PKT_STATUS_CRC_SHIFT		21
#घोषणा RX_PKT_STATUS_CODE_MASK		0x1
#घोषणा RX_PKT_STATUS_CODE_SHIFT	22
#घोषणा RX_PKT_STATUS_RUNT_MASK		0x1
#घोषणा RX_PKT_STATUS_RUNT_SHIFT	23
#घोषणा RX_PKT_STATUS_FRAG_MASK		0x1
#घोषणा RX_PKT_STATUS_FRAG_SHIFT	24
#घोषणा RX_PKT_STATUS_TRUNK_MASK	0x1
#घोषणा RX_PKT_STATUS_TRUNK_SHIFT	25
#घोषणा RX_PKT_STATUS_ALIGN_MASK	0x1
#घोषणा RX_PKT_STATUS_ALIGN_SHIFT	26
#घोषणा RX_PKT_STATUS_VLAN_MASK		0x1
#घोषणा RX_PKT_STATUS_VLAN_SHIFT	27
#घोषणा RX_PKT_STATUS_UPDATE_MASK	0x1
#घोषणा RX_PKT_STATUS_UPDATE_SHIFT	31
#घोषणा RX_PKT_STATUS_VLAN_TAG_MASK	0xFFFF
#घोषणा RX_PKT_STATUS_VLAN_TAG_SHIFT	32

काष्ठा rx_desc अणु
	काष्ठा rx_pkt_status	status;
	अचिन्हित अक्षर     	packet[1536-माप(काष्ठा rx_pkt_status)];
पूर्ण;

क्रमागत atl2_speed_duplex अणु
	atl2_10_half = 0,
	atl2_10_full = 1,
	atl2_100_half = 2,
	atl2_100_full = 3
पूर्ण;

काष्ठा atl2_spi_flash_dev अणु
	स्थिर अक्षर *manu_name;	/* manufacturer id */
	/* op-code */
	u8 cmdWRSR;
	u8 cmdREAD;
	u8 cmdPROGRAM;
	u8 cmdWREN;
	u8 cmdWRDI;
	u8 cmdRDSR;
	u8 cmdRDID;
	u8 cmdSECTOR_ERASE;
	u8 cmdCHIP_ERASE;
पूर्ण;

/* Structure containing variables used by the shared code (atl2_hw.c) */
काष्ठा atl2_hw अणु
	u8 __iomem *hw_addr;
	व्योम *back;

	u8 preamble_len;
	u8 max_retry;          /* Retransmission maximum, afterwards the
				* packet will be discarded. */
	u8 jam_ipg;            /* IPG to start JAM क्रम collision based flow
				* control in half-duplex mode. In unit of
				* 8-bit समय. */
	u8 ipgt;               /* Desired back to back पूर्णांकer-packet gap. The
				* शेष is 96-bit समय. */
	u8 min_अगरg;            /* Minimum number of IFG to enक्रमce in between
				* RX frames. Frame gap below such IFP is
				* dropped. */
	u8 ipgr1;              /* 64bit Carrier-Sense winकरोw */
	u8 ipgr2;              /* 96-bit IPG winकरोw */
	u8 retry_buf;          /* When half-duplex mode, should hold some
				* bytes क्रम mac retry . (8*4bytes unit) */

	u16 fc_rxd_hi;
	u16 fc_rxd_lo;
	u16 lcol;              /* Collision Winकरोw */
	u16 max_frame_size;

	u16 MediaType;
	u16 स्वतःneg_advertised;
	u16 pci_cmd_word;

	u16 mii_स्वतःneg_adv_reg;

	u32 mem_rang;
	u32 txcw;
	u32 mc_filter_type;
	u32 num_mc_addrs;
	u32 collision_delta;
	u32 tx_packet_delta;
	u16 phy_spd_शेष;

	u16 device_id;
	u16 venकरोr_id;
	u16 subप्रणाली_id;
	u16 subप्रणाली_venकरोr_id;
	u8 revision_id;

	/* spi flash */
	u8 flash_venकरोr;

	u8 dma_fairness;
	u8 mac_addr[ETH_ALEN];
	u8 perm_mac_addr[ETH_ALEN];

	/* FIXME */
	/* bool phy_preamble_sup; */
	bool phy_configured;
पूर्ण;

#पूर्ण_अगर /* _ATL2_HW_H_ */

काष्ठा atl2_ring_header अणु
    /* poपूर्णांकer to the descriptor ring memory */
    व्योम *desc;
    /* physical address of the descriptor ring */
    dma_addr_t dma;
    /* length of descriptor ring in bytes */
    अचिन्हित पूर्णांक size;
पूर्ण;

/* board specअगरic निजी data काष्ठाure */
काष्ठा atl2_adapter अणु
	/* OS defined काष्ठाs */
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;
	u32 wol;
	u16 link_speed;
	u16 link_duplex;

	spinlock_t stats_lock;

	काष्ठा work_काष्ठा reset_task;
	काष्ठा work_काष्ठा link_chg_task;
	काष्ठा समयr_list watchकरोg_समयr;
	काष्ठा समयr_list phy_config_समयr;

	अचिन्हित दीर्घ cfg_phy;
	bool mac_disabled;

	/* All Descriptor memory */
	dma_addr_t	ring_dma;
	व्योम		*ring_vir_addr;
	पूर्णांक		ring_size;

	काष्ठा tx_pkt_header	*txd_ring;
	dma_addr_t	txd_dma;

	काष्ठा tx_pkt_status	*txs_ring;
	dma_addr_t	txs_dma;

	काष्ठा rx_desc	*rxd_ring;
	dma_addr_t	rxd_dma;

	u32 txd_ring_size;         /* bytes per unit */
	u32 txs_ring_size;         /* dwords per unit */
	u32 rxd_ring_size;         /* 1536 bytes per unit */

	/* पढ़ो /ग_लिखो ptr: */
	/* host */
	u32 txd_ग_लिखो_ptr;
	u32 txs_next_clear;
	u32 rxd_पढ़ो_ptr;

	/* nic */
	atomic_t txd_पढ़ो_ptr;
	atomic_t txs_ग_लिखो_ptr;
	u32 rxd_ग_लिखो_ptr;

	/* Interrupt Moderator समयr ( 2us resolution) */
	u16 imt;
	/* Interrupt Clear समयr (2us resolution) */
	u16 ict;

	अचिन्हित दीर्घ flags;
	/* काष्ठाs defined in atl2_hw.h */
	u32 bd_number;     /* board number */
	bool pci_using_64;
	bool have_msi;
	काष्ठा atl2_hw hw;

	u32 usr_cmd;
	/* FIXME */
	/* u32 regs_buff[ATL2_REGS_LEN]; */
	u32 pci_state[16];

	u32 *config_space;
पूर्ण;

क्रमागत atl2_state_t अणु
	__ATL2_TESTING,
	__ATL2_RESETTING,
	__ATL2_DOWN
पूर्ण;

#पूर्ण_अगर /* _ATL2_H_ */
