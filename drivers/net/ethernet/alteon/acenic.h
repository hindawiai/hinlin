<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ACENIC_H_
#घोषणा _ACENIC_H_
#समावेश <linux/पूर्णांकerrupt.h>


/*
 * Generate TX index update each समय, when TX ring is बंदd.
 * Normally, this is not useful, because results in more dma (and irqs
 * without TX_COAL_INTS_ONLY).
 */
#घोषणा USE_TX_COAL_NOW	 0

/*
 * Addressing:
 *
 * The Tigon uses 64-bit host addresses, regardless of their actual
 * length, and it expects a big-endian क्रमmat. For 32 bit प्रणालीs the
 * upper 32 bits of the address are simply ignored (zero), however क्रम
 * little endian 64 bit प्रणालीs (Alpha) this looks strange with the
 * two parts of the address word being swapped.
 *
 * The addresses are split in two 32 bit words क्रम all architectures
 * as some of them are in PCI shared memory and it is necessary to use
 * पढ़ोl/ग_लिखोl to access them.
 *
 * The addressing code is derived from Pete Wyckoff's work, but
 * modअगरied to deal properly with पढ़ोl/ग_लिखोl usage.
 */

काष्ठा ace_regs अणु
	u32	pad0[16];	/* PCI control रेजिस्टरs */

	u32	HostCtrl;	/* 0x40 */
	u32	LocalCtrl;

	u32	pad1[2];

	u32	MiscCfg;	/* 0x50 */

	u32	pad2[2];

	u32	PciState;

	u32	pad3[2];	/* 0x60 */

	u32	WinBase;
	u32	WinData;

	u32	pad4[12];	/* 0x70 */

	u32	DmaWriteState;	/* 0xa0 */
	u32	pad5[3];
	u32	DmaReadState;	/* 0xb0 */

	u32	pad6[26];

	u32	AssistState;

	u32	pad7[8];	/* 0x120 */

	u32	CpuCtrl;	/* 0x140 */
	u32	Pc;

	u32	pad8[3];

	u32	SramAddr;	/* 0x154 */
	u32	SramData;

	u32	pad9[49];

	u32	MacRxState;	/* 0x220 */

	u32	pad10[7];

	u32	CpuBCtrl;	/* 0x240 */
	u32	PcB;

	u32	pad11[3];

	u32	SramBAddr;	/* 0x254 */
	u32	SramBData;

	u32	pad12[105];

	u32	pad13[32];	/* 0x400 */
	u32	Stats[32];

	u32	Mb0Hi;		/* 0x500 */
	u32	Mb0Lo;
	u32	Mb1Hi;
	u32	CmdPrd;
	u32	Mb2Hi;
	u32	TxPrd;
	u32	Mb3Hi;
	u32	RxStdPrd;
	u32	Mb4Hi;
	u32	RxJumboPrd;
	u32	Mb5Hi;
	u32	RxMiniPrd;
	u32	Mb6Hi;
	u32	Mb6Lo;
	u32	Mb7Hi;
	u32	Mb7Lo;
	u32	Mb8Hi;
	u32	Mb8Lo;
	u32	Mb9Hi;
	u32	Mb9Lo;
	u32	MbAHi;
	u32	MbALo;
	u32	MbBHi;
	u32	MbBLo;
	u32	MbCHi;
	u32	MbCLo;
	u32	MbDHi;
	u32	MbDLo;
	u32	MbEHi;
	u32	MbELo;
	u32	MbFHi;
	u32	MbFLo;

	u32	pad14[32];

	u32	MacAddrHi;	/* 0x600 */
	u32	MacAddrLo;
	u32	InfoPtrHi;
	u32	InfoPtrLo;
	u32	MultiCastHi;	/* 0x610 */
	u32	MultiCastLo;
	u32	ModeStat;
	u32	DmaReadCfg;
	u32	DmaWriteCfg;	/* 0x620 */
	u32	TxBufRat;
	u32	EvtCsm;
	u32	CmdCsm;
	u32	TuneRxCoalTicks;/* 0x630 */
	u32	TuneTxCoalTicks;
	u32	TuneStatTicks;
	u32	TuneMaxTxDesc;
	u32	TuneMaxRxDesc;	/* 0x640 */
	u32	TuneTrace;
	u32	TuneLink;
	u32	TuneFastLink;
	u32	TracePtr;	/* 0x650 */
	u32	TraceStrt;
	u32	TraceLen;
	u32	IfIdx;
	u32	IfMtu;		/* 0x660 */
	u32	MaskInt;
	u32	GigLnkState;
	u32	FastLnkState;
	u32	pad16[4];	/* 0x670 */
	u32	RxRetCsm;	/* 0x680 */

	u32	pad17[31];

	u32	CmdRng[64];	/* 0x700 */
	u32	Winकरोw[0x200];
पूर्ण;


प्रकार काष्ठा अणु
	u32 addrhi;
	u32 addrlo;
पूर्ण aceaddr;


#घोषणा ACE_WINDOW_SIZE	0x800

#घोषणा ACE_JUMBO_MTU 9000
#घोषणा ACE_STD_MTU 1500

#घोषणा ACE_TRACE_SIZE 0x8000

/*
 * Host control रेजिस्टर bits.
 */

#घोषणा IN_INT		0x01
#घोषणा CLR_INT		0x02
#घोषणा HW_RESET	0x08
#घोषणा BYTE_SWAP	0x10
#घोषणा WORD_SWAP	0x20
#घोषणा MASK_INTS	0x40

/*
 * Local control रेजिस्टर bits.
 */

#घोषणा EEPROM_DATA_IN		0x800000
#घोषणा EEPROM_DATA_OUT		0x400000
#घोषणा EEPROM_WRITE_ENABLE	0x200000
#घोषणा EEPROM_CLK_OUT		0x100000

#घोषणा EEPROM_BASE		0xa0000000

#घोषणा EEPROM_WRITE_SELECT	0xa0
#घोषणा EEPROM_READ_SELECT	0xa1

#घोषणा SRAM_BANK_512K		0x200


/*
 * udelay() values क्रम when घड़ीing the eeprom
 */
#घोषणा ACE_SHORT_DELAY		2
#घोषणा ACE_LONG_DELAY		4


/*
 * Misc Config bits
 */

#घोषणा SYNC_SRAM_TIMING	0x100000


/*
 * CPU state bits.
 */

#घोषणा CPU_RESET		0x01
#घोषणा CPU_TRACE		0x02
#घोषणा CPU_PROM_FAILED		0x10
#घोषणा CPU_HALT		0x00010000
#घोषणा CPU_HALTED		0xffff0000


/*
 * PCI State bits.
 */

#घोषणा DMA_READ_MAX_4		0x04
#घोषणा DMA_READ_MAX_16		0x08
#घोषणा DMA_READ_MAX_32		0x0c
#घोषणा DMA_READ_MAX_64		0x10
#घोषणा DMA_READ_MAX_128	0x14
#घोषणा DMA_READ_MAX_256	0x18
#घोषणा DMA_READ_MAX_1K		0x1c
#घोषणा DMA_WRITE_MAX_4		0x20
#घोषणा DMA_WRITE_MAX_16	0x40
#घोषणा DMA_WRITE_MAX_32	0x60
#घोषणा DMA_WRITE_MAX_64	0x80
#घोषणा DMA_WRITE_MAX_128	0xa0
#घोषणा DMA_WRITE_MAX_256	0xc0
#घोषणा DMA_WRITE_MAX_1K	0xe0
#घोषणा DMA_READ_WRITE_MASK	0xfc
#घोषणा MEM_READ_MULTIPLE	0x00020000
#घोषणा PCI_66MHZ		0x00080000
#घोषणा PCI_32BIT		0x00100000
#घोषणा DMA_WRITE_ALL_ALIGN	0x00800000
#घोषणा READ_CMD_MEM		0x06000000
#घोषणा WRITE_CMD_MEM		0x70000000


/*
 * Mode status
 */

#घोषणा ACE_BYTE_SWAP_BD	0x02
#घोषणा ACE_WORD_SWAP_BD	0x04		/* not actually used */
#घोषणा ACE_WARN		0x08
#घोषणा ACE_BYTE_SWAP_DMA	0x10
#घोषणा ACE_NO_JUMBO_FRAG	0x200
#घोषणा ACE_FATAL		0x40000000


/*
 * DMA config
 */

#घोषणा DMA_THRESH_1W		0x10
#घोषणा DMA_THRESH_2W		0x20
#घोषणा DMA_THRESH_4W		0x40
#घोषणा DMA_THRESH_8W		0x80
#घोषणा DMA_THRESH_16W		0x100
#घोषणा DMA_THRESH_32W		0x0	/* not described in करोc, but exists. */


/*
 * Tuning parameters
 */

#घोषणा TICKS_PER_SEC		1000000


/*
 * Link bits
 */

#घोषणा LNK_PREF		0x00008000
#घोषणा LNK_10MB		0x00010000
#घोषणा LNK_100MB		0x00020000
#घोषणा LNK_1000MB		0x00040000
#घोषणा LNK_FULL_DUPLEX		0x00080000
#घोषणा LNK_HALF_DUPLEX		0x00100000
#घोषणा LNK_TX_FLOW_CTL_Y	0x00200000
#घोषणा LNK_NEG_ADVANCED	0x00400000
#घोषणा LNK_RX_FLOW_CTL_Y	0x00800000
#घोषणा LNK_NIC			0x01000000
#घोषणा LNK_JAM			0x02000000
#घोषणा LNK_JUMBO		0x04000000
#घोषणा LNK_ALTEON		0x08000000
#घोषणा LNK_NEG_FCTL		0x10000000
#घोषणा LNK_NEGOTIATE		0x20000000
#घोषणा LNK_ENABLE		0x40000000
#घोषणा LNK_UP			0x80000000


/*
 * Event definitions
 */

#घोषणा EVT_RING_ENTRIES	256
#घोषणा EVT_RING_SIZE	(EVT_RING_ENTRIES * माप(काष्ठा event))

काष्ठा event अणु
#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
	u32	idx:12;
	u32	code:12;
	u32	evt:8;
#अन्यथा
	u32	evt:8;
	u32	code:12;
	u32	idx:12;
#पूर्ण_अगर
	u32     pad;
पूर्ण;


/*
 * Events
 */

#घोषणा E_FW_RUNNING		0x01
#घोषणा E_STATS_UPDATED		0x04

#घोषणा E_STATS_UPDATE		0x04

#घोषणा E_LNK_STATE		0x06
#घोषणा E_C_LINK_UP		0x01
#घोषणा E_C_LINK_DOWN		0x02
#घोषणा E_C_LINK_10_100		0x03

#घोषणा E_ERROR			0x07
#घोषणा E_C_ERR_INVAL_CMD	0x01
#घोषणा E_C_ERR_UNIMP_CMD	0x02
#घोषणा E_C_ERR_BAD_CFG		0x03

#घोषणा E_MCAST_LIST		0x08
#घोषणा E_C_MCAST_ADDR_ADD	0x01
#घोषणा E_C_MCAST_ADDR_DEL	0x02

#घोषणा E_RESET_JUMBO_RNG	0x09


/*
 * Commands
 */

#घोषणा CMD_RING_ENTRIES	64

काष्ठा cmd अणु
#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
	u32	idx:12;
	u32	code:12;
	u32	evt:8;
#अन्यथा
	u32	evt:8;
	u32	code:12;
	u32	idx:12;
#पूर्ण_अगर
पूर्ण;


#घोषणा C_HOST_STATE		0x01
#घोषणा C_C_STACK_UP		0x01
#घोषणा C_C_STACK_DOWN		0x02

#घोषणा C_FDR_FILTERING		0x02
#घोषणा C_C_FDR_FILT_ENABLE	0x01
#घोषणा C_C_FDR_FILT_DISABLE	0x02

#घोषणा C_SET_RX_PRD_IDX	0x03
#घोषणा C_UPDATE_STATS		0x04
#घोषणा C_RESET_JUMBO_RNG	0x05
#घोषणा C_ADD_MULTICAST_ADDR	0x08
#घोषणा C_DEL_MULTICAST_ADDR	0x09

#घोषणा C_SET_PROMISC_MODE	0x0a
#घोषणा C_C_PROMISC_ENABLE	0x01
#घोषणा C_C_PROMISC_DISABLE	0x02

#घोषणा C_LNK_NEGOTIATION	0x0b
#घोषणा C_C_NEGOTIATE_BOTH	0x00
#घोषणा C_C_NEGOTIATE_GIG	0x01
#घोषणा C_C_NEGOTIATE_10_100	0x02

#घोषणा C_SET_MAC_ADDR		0x0c
#घोषणा C_CLEAR_PROखाता		0x0d

#घोषणा C_SET_MULTICAST_MODE	0x0e
#घोषणा C_C_MCAST_ENABLE	0x01
#घोषणा C_C_MCAST_DISABLE	0x02

#घोषणा C_CLEAR_STATS		0x0f
#घोषणा C_SET_RX_JUMBO_PRD_IDX	0x10
#घोषणा C_REFRESH_STATS		0x11


/*
 * Descriptor flags
 */
#घोषणा BD_FLG_TCP_UDP_SUM	0x01
#घोषणा BD_FLG_IP_SUM		0x02
#घोषणा BD_FLG_END		0x04
#घोषणा BD_FLG_MORE		0x08
#घोषणा BD_FLG_JUMBO		0x10
#घोषणा BD_FLG_UCAST		0x20
#घोषणा BD_FLG_MCAST		0x40
#घोषणा BD_FLG_BCAST		0x60
#घोषणा BD_FLG_TYP_MASK		0x60
#घोषणा BD_FLG_IP_FRAG		0x80
#घोषणा BD_FLG_IP_FRAG_END	0x100
#घोषणा BD_FLG_VLAN_TAG		0x200
#घोषणा BD_FLG_FRAME_ERROR	0x400
#घोषणा BD_FLG_COAL_NOW		0x800
#घोषणा BD_FLG_MINI		0x1000


/*
 * Ring Control block flags
 */
#घोषणा RCB_FLG_TCP_UDP_SUM	0x01
#घोषणा RCB_FLG_IP_SUM		0x02
#घोषणा RCB_FLG_NO_PSEUDO_HDR	0x08
#घोषणा RCB_FLG_VLAN_ASSIST	0x10
#घोषणा RCB_FLG_COAL_INT_ONLY	0x20
#घोषणा RCB_FLG_TX_HOST_RING	0x40
#घोषणा RCB_FLG_IEEE_SNAP_SUM	0x80
#घोषणा RCB_FLG_EXT_RX_BD	0x100
#घोषणा RCB_FLG_RNG_DISABLE	0x200


/*
 * TX ring - maximum TX ring entries क्रम Tigon I's is 128
 */
#घोषणा MAX_TX_RING_ENTRIES	256
#घोषणा TIGON_I_TX_RING_ENTRIES	128
#घोषणा TX_RING_SIZE		(MAX_TX_RING_ENTRIES * माप(काष्ठा tx_desc))
#घोषणा TX_RING_BASE		0x3800

काष्ठा tx_descअणु
        aceaddr	addr;
	u32	flagsize;
#अगर 0
/*
 * This is in PCI shared mem and must be accessed with पढ़ोl/ग_लिखोl
 * real layout is:
 */
#अगर __LITTLE_ENDIAN
	u16	flags;
	u16	size;
	u16	vlan;
	u16	reserved;
#अन्यथा
	u16	size;
	u16	flags;
	u16	reserved;
	u16	vlan;
#पूर्ण_अगर
#पूर्ण_अगर
	u32	vlanres;
पूर्ण;


#घोषणा RX_STD_RING_ENTRIES	512
#घोषणा RX_STD_RING_SIZE	(RX_STD_RING_ENTRIES * माप(काष्ठा rx_desc))

#घोषणा RX_JUMBO_RING_ENTRIES	256
#घोषणा RX_JUMBO_RING_SIZE	(RX_JUMBO_RING_ENTRIES *माप(काष्ठा rx_desc))

#घोषणा RX_MINI_RING_ENTRIES	1024
#घोषणा RX_MINI_RING_SIZE	(RX_MINI_RING_ENTRIES *माप(काष्ठा rx_desc))

#घोषणा RX_RETURN_RING_ENTRIES	2048
#घोषणा RX_RETURN_RING_SIZE	(RX_MAX_RETURN_RING_ENTRIES * \
				 माप(काष्ठा rx_desc))

काष्ठा rx_descअणु
	aceaddr	addr;
#अगर_घोषित __LITTLE_ENDIAN
	u16	size;
	u16	idx;
#अन्यथा
	u16	idx;
	u16	size;
#पूर्ण_अगर
#अगर_घोषित __LITTLE_ENDIAN
	u16	flags;
	u16	type;
#अन्यथा
	u16	type;
	u16	flags;
#पूर्ण_अगर
#अगर_घोषित __LITTLE_ENDIAN
	u16	tcp_udp_csum;
	u16	ip_csum;
#अन्यथा
	u16	ip_csum;
	u16	tcp_udp_csum;
#पूर्ण_अगर
#अगर_घोषित __LITTLE_ENDIAN
	u16	vlan;
	u16	err_flags;
#अन्यथा
	u16	err_flags;
	u16	vlan;
#पूर्ण_अगर
	u32	reserved;
	u32	opague;
पूर्ण;


/*
 * This काष्ठा is shared with the NIC firmware.
 */
काष्ठा ring_ctrl अणु
	aceaddr	rngptr;
#अगर_घोषित __LITTLE_ENDIAN
	u16	flags;
	u16	max_len;
#अन्यथा
	u16	max_len;
	u16	flags;
#पूर्ण_अगर
	u32	pad;
पूर्ण;


काष्ठा ace_mac_stats अणु
	u32 excess_colls;
	u32 coll_1;
	u32 coll_2;
	u32 coll_3;
	u32 coll_4;
	u32 coll_5;
	u32 coll_6;
	u32 coll_7;
	u32 coll_8;
	u32 coll_9;
	u32 coll_10;
	u32 coll_11;
	u32 coll_12;
	u32 coll_13;
	u32 coll_14;
	u32 coll_15;
	u32 late_coll;
	u32 defers;
	u32 crc_err;
	u32 underrun;
	u32 crs_err;
	u32 pad[3];
	u32 drop_ula;
	u32 drop_mc;
	u32 drop_fc;
	u32 drop_space;
	u32 coll;
	u32 kept_bc;
	u32 kept_mc;
	u32 kept_uc;
पूर्ण;


काष्ठा ace_info अणु
	जोड़ अणु
		u32 stats[256];
	पूर्ण s;
	काष्ठा ring_ctrl	evt_ctrl;
	काष्ठा ring_ctrl	cmd_ctrl;
	काष्ठा ring_ctrl	tx_ctrl;
	काष्ठा ring_ctrl	rx_std_ctrl;
	काष्ठा ring_ctrl	rx_jumbo_ctrl;
	काष्ठा ring_ctrl	rx_mini_ctrl;
	काष्ठा ring_ctrl	rx_वापस_ctrl;
	aceaddr	evt_prd_ptr;
	aceaddr	rx_ret_prd_ptr;
	aceaddr	tx_csm_ptr;
	aceaddr	stats2_ptr;
पूर्ण;


काष्ठा ring_info अणु
	काष्ठा sk_buff		*skb;
	DEFINE_DMA_UNMAP_ADDR(mapping);
पूर्ण;


/*
 * Funny... As soon as we add maplen on alpha, it starts to work
 * much slower. Hmm... is it because काष्ठा करोes not fit to one cacheline?
 * So, split tx_ring_info.
 */
काष्ठा tx_ring_info अणु
	काष्ठा sk_buff		*skb;
	DEFINE_DMA_UNMAP_ADDR(mapping);
	DEFINE_DMA_UNMAP_LEN(maplen);
पूर्ण;


/*
 * काष्ठा ace_skb holding the rings of skb's. This is an awful lot of
 * poपूर्णांकers, but I करोn't see any other smart mode to करो this in an
 * efficient manner ;-(
 */
काष्ठा ace_skb
अणु
	काष्ठा tx_ring_info	tx_skbuff[MAX_TX_RING_ENTRIES];
	काष्ठा ring_info	rx_std_skbuff[RX_STD_RING_ENTRIES];
	काष्ठा ring_info	rx_mini_skbuff[RX_MINI_RING_ENTRIES];
	काष्ठा ring_info	rx_jumbo_skbuff[RX_JUMBO_RING_ENTRIES];
पूर्ण;


/*
 * Struct निजी क्रम the AceNIC.
 *
 * Elements are grouped so variables used by the tx handling goes
 * together, and will go पूर्णांकo the same cache lines etc. in order to
 * aव्योम cache line contention between the rx and tx handling on SMP.
 *
 * Frequently accessed variables are put at the beginning of the
 * काष्ठा to help the compiler generate better/लघुer code.
 */
काष्ठा ace_निजी
अणु
	काष्ठा net_device	*ndev;		/* backpoपूर्णांकer */
	काष्ठा ace_info		*info;
	काष्ठा ace_regs	__iomem	*regs;		/* रेजिस्टर base */
	काष्ठा ace_skb		*skb;
	dma_addr_t		info_dma;	/* 32/64 bit */

	पूर्णांक			version, link;
	पूर्णांक			promisc, mcast_all;

	/*
	 * TX elements
	 */
	काष्ठा tx_desc		*tx_ring;
	u32			tx_prd;
	अस्थिर u32		tx_ret_csm;
	पूर्णांक			tx_ring_entries;

	/*
	 * RX elements
	 */
	अचिन्हित दीर्घ		std_refill_busy
				__attribute__ ((aligned (SMP_CACHE_BYTES)));
	अचिन्हित दीर्घ		mini_refill_busy, jumbo_refill_busy;
	atomic_t		cur_rx_bufs;
	atomic_t		cur_mini_bufs;
	atomic_t		cur_jumbo_bufs;
	u32			rx_std_skbprd, rx_mini_skbprd, rx_jumbo_skbprd;
	u32			cur_rx;

	काष्ठा rx_desc		*rx_std_ring;
	काष्ठा rx_desc		*rx_jumbo_ring;
	काष्ठा rx_desc		*rx_mini_ring;
	काष्ठा rx_desc		*rx_वापस_ring;

	पूर्णांक			tasklet_pending, jumbo;
	काष्ठा tasklet_काष्ठा	ace_tasklet;

	काष्ठा event		*evt_ring;

	अस्थिर u32		*evt_prd, *rx_ret_prd, *tx_csm;

	dma_addr_t		tx_ring_dma;	/* 32/64 bit */
	dma_addr_t		rx_ring_base_dma;
	dma_addr_t		evt_ring_dma;
	dma_addr_t		evt_prd_dma, rx_ret_prd_dma, tx_csm_dma;

	अचिन्हित अक्षर		*trace_buf;
	काष्ठा pci_dev		*pdev;
	काष्ठा net_device	*next;
	अस्थिर पूर्णांक		fw_running;
	पूर्णांक			board_idx;
	u16			pci_command;
	u8			pci_latency;
	स्थिर अक्षर		*name;
#अगर_घोषित INDEX_DEBUG
	spinlock_t		debug_lock
				__attribute__ ((aligned (SMP_CACHE_BYTES)));
	u32			last_tx, last_std_rx, last_mini_rx;
#पूर्ण_अगर
	पूर्णांक			pci_using_dac;
	u8			firmware_major;
	u8			firmware_minor;
	u8			firmware_fix;
	u32			firmware_start;
पूर्ण;


#घोषणा TX_RESERVED	MAX_SKB_FRAGS

अटल अंतरभूत पूर्णांक tx_space (काष्ठा ace_निजी *ap, u32 csm, u32 prd)
अणु
	वापस (csm - prd - 1) & (ACE_TX_RING_ENTRIES(ap) - 1);
पूर्ण

#घोषणा tx_मुक्त(ap) 		tx_space((ap)->tx_ret_csm, (ap)->tx_prd, ap)
#घोषणा tx_ring_full(ap, csm, prd)	(tx_space(ap, csm, prd) <= TX_RESERVED)

अटल अंतरभूत व्योम set_aceaddr(aceaddr *aa, dma_addr_t addr)
अणु
	u64 baddr = (u64) addr;
	aa->addrlo = baddr & 0xffffffff;
	aa->addrhi = baddr >> 32;
	wmb();
पूर्ण


अटल अंतरभूत व्योम ace_set_txprd(काष्ठा ace_regs __iomem *regs,
				 काष्ठा ace_निजी *ap, u32 value)
अणु
#अगर_घोषित INDEX_DEBUG
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&ap->debug_lock, flags);
	ग_लिखोl(value, &regs->TxPrd);
	अगर (value == ap->last_tx)
		prपूर्णांकk(KERN_ERR "AceNIC RACE ALERT! writing identical value "
		       "to tx producer (%i)\n", value);
	ap->last_tx = value;
	spin_unlock_irqrestore(&ap->debug_lock, flags);
#अन्यथा
	ग_लिखोl(value, &regs->TxPrd);
#पूर्ण_अगर
	wmb();
पूर्ण


अटल अंतरभूत व्योम ace_mask_irq(काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;

	अगर (ACE_IS_TIGON_I(ap))
		ग_लिखोl(1, &regs->MaskInt);
	अन्यथा
		ग_लिखोl(पढ़ोl(&regs->HostCtrl) | MASK_INTS, &regs->HostCtrl);

	ace_sync_irq(dev->irq);
पूर्ण


अटल अंतरभूत व्योम ace_unmask_irq(काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;

	अगर (ACE_IS_TIGON_I(ap))
		ग_लिखोl(0, &regs->MaskInt);
	अन्यथा
		ग_लिखोl(पढ़ोl(&regs->HostCtrl) & ~MASK_INTS, &regs->HostCtrl);
पूर्ण


/*
 * Prototypes
 */
अटल पूर्णांक ace_init(काष्ठा net_device *dev);
अटल व्योम ace_load_std_rx_ring(काष्ठा net_device *dev, पूर्णांक nr_bufs);
अटल व्योम ace_load_mini_rx_ring(काष्ठा net_device *dev, पूर्णांक nr_bufs);
अटल व्योम ace_load_jumbo_rx_ring(काष्ठा net_device *dev, पूर्णांक nr_bufs);
अटल irqवापस_t ace_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक ace_load_firmware(काष्ठा net_device *dev);
अटल पूर्णांक ace_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t ace_start_xmit(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev);
अटल पूर्णांक ace_बंद(काष्ठा net_device *dev);
अटल व्योम ace_tasklet(काष्ठा tasklet_काष्ठा *t);
अटल व्योम ace_dump_trace(काष्ठा ace_निजी *ap);
अटल व्योम ace_set_multicast_list(काष्ठा net_device *dev);
अटल पूर्णांक ace_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu);
अटल पूर्णांक ace_set_mac_addr(काष्ठा net_device *dev, व्योम *p);
अटल व्योम ace_set_rxtx_parms(काष्ठा net_device *dev, पूर्णांक jumbo);
अटल पूर्णांक ace_allocate_descriptors(काष्ठा net_device *dev);
अटल व्योम ace_मुक्त_descriptors(काष्ठा net_device *dev);
अटल व्योम ace_init_cleanup(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *ace_get_stats(काष्ठा net_device *dev);
अटल पूर्णांक पढ़ो_eeprom_byte(काष्ठा net_device *dev, अचिन्हित दीर्घ offset);

#पूर्ण_अगर /* _ACENIC_H_ */
