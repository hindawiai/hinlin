<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RRUNNER_H_
#घोषणा _RRUNNER_H_

#समावेश <linux/पूर्णांकerrupt.h>

#अगर ((BITS_PER_LONG != 32) && (BITS_PER_LONG != 64))
#त्रुटि "BITS_PER_LONG not defined or not valid"
#पूर्ण_अगर


काष्ठा rr_regs अणु

	u32	pad0[16];

	u32	HostCtrl;
	u32	LocalCtrl;
	u32	Pc;
	u32	BrkPt;

/* Timer increments every 0.97 micro-seconds (अचिन्हित पूर्णांक) */
	u32	Timer_Hi;
	u32	Timer;
	u32	TimerRef;
	u32	PciState;

	u32	Event;
	u32	MbEvent;

	u32	WinBase;
	u32	WinData;
	u32	RX_state;
	u32	TX_state;

	u32	Overhead;
	u32	ExtIo;

	u32	DmaWriteHostHi;
	u32	DmaWriteHostLo;

	u32	pad1[2];

	u32	DmaReadHostHi;
	u32	DmaReadHostLo;

	u32	pad2;

	u32	DmaReadLen;
	u32	DmaWriteState;

	u32	DmaWriteLcl;
	u32	DmaWriteIPchecksum;
	u32	DmaWriteLen;
	u32	DmaReadState;
	u32	DmaReadLcl;
	u32	DmaReadIPchecksum;
	u32	pad3;

	u32	RxBase;
	u32	RxPrd;
	u32	RxCon;

	u32	pad4;

	u32	TxBase;
	u32	TxPrd;
	u32	TxCon;

	u32	pad5;

	u32	RxIndPro;
	u32	RxIndCon;
	u32	RxIndRef;

	u32	pad6;

	u32	TxIndPro;
	u32	TxIndCon;
	u32	TxIndRef;

	u32	pad7[17];

	u32	DrCmndPro;
	u32	DrCmndCon;
	u32	DrCmndRef;

	u32	pad8;

	u32	DwCmndPro;
	u32	DwCmndCon;
	u32	DwCmndRef;

	u32	AssistState;

	u32	DrDataPro;
	u32	DrDataCon;
	u32	DrDataRef;

	u32	pad9;

	u32	DwDataPro;
	u32	DwDataCon;
	u32	DwDataRef;

	u32	pad10[33];

	u32	EvtCon;

	u32	pad11[5];

	u32	TxPi;
	u32	IpRxPi;

	u32	pad11a[8];

	u32	CmdRing[16];

/* The ULA is in two रेजिस्टरs the high order two bytes of the first
 * word contain the RunCode features.
 * ula0		res	res	byte0	byte1
 * ula1		byte2	byte3	byte4	byte5
 */
	u32	Ula0;
	u32	Ula1;

	u32	RxRingHi;
	u32	RxRingLo;

	u32	InfoPtrHi;
	u32	InfoPtrLo;

	u32	Mode;

	u32	ConRetry;
	u32	ConRetryTmr;

	u32	ConTmout;
	u32	CtatTmr;

	u32	MaxRxRng;

	u32	IntrTmr;
	u32	TxDataMvTimeout;
	u32	RxDataMvTimeout;

	u32	EvtPrd;
	u32	TraceIdx;

	u32	Fail1;
	u32	Fail2;

	u32	DrvPrm;

	u32	FilterLA;

	u32	FwRev;
	u32	FwRes1;
	u32	FwRes2;
	u32	FwRes3;

	u32	WriteDmaThresh;
	u32	ReadDmaThresh;

	u32	pad12[325];
	u32	Winकरोw[512];
पूर्ण;

/*
 * Host control रेजिस्टर bits.
 */

#घोषणा RR_INT		0x01
#घोषणा RR_CLEAR_INT	0x02
#घोषणा NO_SWAP		0x04000004
#घोषणा NO_SWAP1	0x00000004
#घोषणा PCI_RESET_NIC	0x08
#घोषणा HALT_NIC	0x10
#घोषणा SSTEP_NIC	0x20
#घोषणा MEM_READ_MULTI	0x40
#घोषणा NIC_HALTED	0x100
#घोषणा HALT_INST	0x200
#घोषणा PARITY_ERR	0x400
#घोषणा INVALID_INST_B	0x800
#घोषणा RR_REV_2	0x20000000
#घोषणा RR_REV_MASK	0xf0000000

/*
 * Local control रेजिस्टर bits.
 */

#घोषणा INTA_STATE		0x01
#घोषणा CLEAR_INTA		0x02
#घोषणा FAST_EEPROM_ACCESS	0x08
#घोषणा ENABLE_EXTRA_SRAM	0x100
#घोषणा ENABLE_EXTRA_DESC	0x200
#घोषणा ENABLE_PARITY		0x400
#घोषणा FORCE_DMA_PARITY_ERROR	0x800
#घोषणा ENABLE_EEPROM_WRITE	0x1000
#घोषणा ENABLE_DATA_CACHE	0x2000
#घोषणा SRAM_LO_PARITY_ERR	0x4000
#घोषणा SRAM_HI_PARITY_ERR	0x8000

/*
 * PCI state bits.
 */

#घोषणा FORCE_PCI_RESET		0x01
#घोषणा PROVIDE_LENGTH		0x02
#घोषणा MASK_DMA_READ_MAX	0x1C
#घोषणा RBURST_DISABLE		0x00
#घोषणा RBURST_4		0x04
#घोषणा RBURST_16		0x08
#घोषणा RBURST_32		0x0C
#घोषणा RBURST_64		0x10
#घोषणा RBURST_128		0x14
#घोषणा RBURST_256		0x18
#घोषणा RBURST_1024		0x1C
#घोषणा MASK_DMA_WRITE_MAX	0xE0
#घोषणा WBURST_DISABLE		0x00
#घोषणा WBURST_4		0x20
#घोषणा WBURST_16		0x40
#घोषणा WBURST_32		0x60
#घोषणा WBURST_64		0x80
#घोषणा WBURST_128		0xa0
#घोषणा WBURST_256		0xc0
#घोषणा WBURST_1024		0xe0
#घोषणा MASK_MIN_DMA		0xFF00
#घोषणा FIFO_RETRY_ENABLE	0x10000

/*
 * Event रेजिस्टर
 */

#घोषणा DMA_WRITE_DONE		0x10000
#घोषणा DMA_READ_DONE		0x20000
#घोषणा DMA_WRITE_ERR		0x40000
#घोषणा DMA_READ_ERR		0x80000

/*
 * Receive state
 *
 * RoadRunner HIPPI Receive State Register controls and monitors the
 * HIPPI receive पूर्णांकerface in the NIC. Look at err bits when a HIPPI
 * receive Error Event occurs.
 */

#घोषणा ENABLE_NEW_CON		0x01
#घोषणा RESET_RECV		0x02
#घोषणा RECV_ALL		0x00
#घोषणा RECV_1K			0x20
#घोषणा RECV_2K			0x40
#घोषणा RECV_4K			0x60
#घोषणा RECV_8K			0x80
#घोषणा RECV_16K		0xa0
#घोषणा RECV_32K		0xc0
#घोषणा RECV_64K		0xe0

/*
 * Transmit status.
 */

#घोषणा ENA_XMIT		0x01
#घोषणा PERM_CON		0x02

/*
 * DMA ग_लिखो state
 */

#घोषणा RESET_DMA		0x01
#घोषणा NO_SWAP_DMA		0x02
#घोषणा DMA_ACTIVE		0x04
#घोषणा THRESH_MASK		0x1F
#घोषणा DMA_ERROR_MASK		0xff000000

/*
 * Gooddies stored in the ULA रेजिस्टरs.
 */

#घोषणा TRACE_ON_WHAT_BIT	0x00020000    /* Traces on */
#घोषणा ONEM_BUF_WHAT_BIT	0x00040000    /* 1Meg vs 256K */
#घोषणा CHAR_API_WHAT_BIT	0x00080000    /* Char API vs network only */
#घोषणा CMD_EVT_WHAT_BIT	0x00200000    /* Command event */
#घोषणा LONG_TX_WHAT_BIT	0x00400000
#घोषणा LONG_RX_WHAT_BIT	0x00800000
#घोषणा WHAT_BIT_MASK		0xFFFD0000    /* Feature bit mask */

/*
 * Mode status
 */

#घोषणा EVENT_OVFL		0x80000000
#घोषणा FATAL_ERR		0x40000000
#घोषणा LOOP_BACK		0x01
#घोषणा MODE_PH			0x02
#घोषणा MODE_FP			0x00
#घोषणा PTR64BIT		0x04
#घोषणा PTR32BIT		0x00
#घोषणा PTR_WD_SWAP		0x08
#घोषणा PTR_WD_NOSWAP		0x00
#घोषणा POST_WARN_EVENT		0x10
#घोषणा ERR_TERM		0x20
#घोषणा सूचीECT_CONN		0x40
#घोषणा NO_NIC_WATCHDOG		0x80
#घोषणा SWAP_DATA		0x100
#घोषणा SWAP_CONTROL		0x200
#घोषणा NIC_HALT_ON_ERR		0x400
#घोषणा NIC_NO_RESTART		0x800
#घोषणा HALF_DUP_TX		0x1000
#घोषणा HALF_DUP_RX		0x2000


/*
 * Error codes
 */

/* Host Error Codes - values of fail1 */
#घोषणा ERR_UNKNOWN_MBOX	0x1001
#घोषणा ERR_UNKNOWN_CMD		0x1002
#घोषणा ERR_MAX_RING		0x1003
#घोषणा ERR_RING_CLOSED		0x1004
#घोषणा ERR_RING_OPEN		0x1005
/* Firmware पूर्णांकernal errors */
#घोषणा ERR_EVENT_RING_FULL	0x01
#घोषणा ERR_DW_PEND_CMND_FULL	0x02
#घोषणा ERR_DR_PEND_CMND_FULL	0x03
#घोषणा ERR_DW_PEND_DATA_FULL	0x04
#घोषणा ERR_DR_PEND_DATA_FULL	0x05
#घोषणा ERR_ILLEGAL_JUMP	0x06
#घोषणा ERR_UNIMPLEMENTED	0x07
#घोषणा ERR_TX_INFO_FULL	0x08
#घोषणा ERR_RX_INFO_FULL	0x09
#घोषणा ERR_ILLEGAL_MODE	0x0A
#घोषणा ERR_MAIN_TIMEOUT	0x0B
#घोषणा ERR_EVENT_BITS		0x0C
#घोषणा ERR_UNPEND_FULL		0x0D
#घोषणा ERR_TIMER_QUEUE_FULL	0x0E
#घोषणा ERR_TIMER_QUEUE_EMPTY	0x0F
#घोषणा ERR_TIMER_NO_FREE	0x10
#घोषणा ERR_INTR_START		0x11
#घोषणा ERR_BAD_STARTUP		0x12
#घोषणा ERR_NO_PKT_END		0x13
#घोषणा ERR_HALTED_ON_ERR	0x14
/* Hardware NIC Errors */
#घोषणा ERR_WRITE_DMA		0x0101
#घोषणा ERR_READ_DMA		0x0102
#घोषणा ERR_EXT_SERIAL		0x0103
#घोषणा ERR_TX_INT_PARITY	0x0104


/*
 * Event definitions
 */

#घोषणा EVT_RING_ENTRIES	64
#घोषणा EVT_RING_SIZE		(EVT_RING_ENTRIES * माप(काष्ठा event))

काष्ठा event अणु
#अगर_घोषित __LITTLE_ENDIAN
	u16     index;
	u8      ring;
	u8      code;
#अन्यथा
	u8      code;
	u8      ring;
	u16     index;
#पूर्ण_अगर
	u32     बारtamp;
पूर्ण;

/*
 * General Events
 */

#घोषणा E_NIC_UP	0x01
#घोषणा E_WATCHDOG	0x02

#घोषणा E_STAT_UPD	0x04
#घोषणा E_INVAL_CMD	0x05
#घोषणा E_SET_CMD_CONS	0x06
#घोषणा E_LINK_ON	0x07
#घोषणा E_LINK_OFF	0x08
#घोषणा E_INTERN_ERR	0x09
#घोषणा E_HOST_ERR	0x0A
#घोषणा E_STATS_UPDATE	0x0B
#घोषणा E_REJECTING	0x0C

/*
 * Send  Events
 */
#घोषणा E_CON_REJ	0x13
#घोषणा E_CON_TMOUT	0x14
#घोषणा E_CON_NC_TMOUT	0x15	/* I  , Connection No Campon Timeout */
#घोषणा E_DISC_ERR	0x16
#घोषणा E_INT_PRTY	0x17
#घोषणा E_TX_IDLE	0x18
#घोषणा E_TX_LINK_DROP	0x19
#घोषणा E_TX_INV_RNG	0x1A
#घोषणा E_TX_INV_BUF	0x1B
#घोषणा E_TX_INV_DSC	0x1C

/*
 * Destination Events
 */
/*
 * General Receive events
 */
#घोषणा E_VAL_RNG	0x20
#घोषणा E_RX_RNG_ENER	0x21
#घोषणा E_INV_RNG	0x22
#घोषणा E_RX_RNG_SPC	0x23
#घोषणा E_RX_RNG_OUT	0x24
#घोषणा E_PKT_DISCARD	0x25
#घोषणा E_INFO_EVT	0x27

/*
 * Data corrupted events
 */
#घोषणा E_RX_PAR_ERR	0x2B
#घोषणा E_RX_LLRC_ERR	0x2C
#घोषणा E_IP_CKSM_ERR	0x2D
#घोषणा E_DTA_CKSM_ERR	0x2E
#घोषणा E_SHT_BST	0x2F

/*
 * Data lost events
 */
#घोषणा E_LST_LNK_ERR	0x30
#घोषणा E_FLG_SYN_ERR	0x31
#घोषणा E_FRM_ERR	0x32
#घोषणा E_RX_IDLE	0x33
#घोषणा E_PKT_LN_ERR	0x34
#घोषणा E_STATE_ERR	0x35
#घोषणा E_UNEXP_DATA	0x3C

/*
 * Fatal events
 */
#घोषणा E_RX_INV_BUF	0x36
#घोषणा E_RX_INV_DSC	0x37
#घोषणा E_RNG_BLK	0x38

/*
 * Warning events
 */
#घोषणा E_RX_TO		0x39
#घोषणा E_BFR_SPC	0x3A
#घोषणा E_INV_ULP	0x3B

#घोषणा E_NOT_IMPLEMENTED 0x40


/*
 * Commands
 */

#घोषणा CMD_RING_ENTRIES	16

काष्ठा cmd अणु
#अगर_घोषित __LITTLE_ENDIAN
	u16     index;
	u8      ring;
	u8      code;
#अन्यथा
	u8      code;
	u8      ring;
	u16     index;
#पूर्ण_अगर
पूर्ण;

#घोषणा C_START_FW	0x01
#घोषणा C_UPD_STAT	0x02
#घोषणा C_WATCHDOG	0x05
#घोषणा C_DEL_RNG	0x09
#घोषणा C_NEW_RNG	0x0A
#घोषणा C_CONN		0x0D


/*
 * Mode bits
 */

#घोषणा  PACKET_BAD		0x01 /* Packet had link-layer error */
#घोषणा  INTERRUPT		0x02
#घोषणा  TX_IP_CKSUM		0x04
#घोषणा  PACKET_END		0x08
#घोषणा  PACKET_START		0x10
#घोषणा  SAME_IFIELD		0x80


प्रकार काष्ठा अणु
#अगर (BITS_PER_LONG == 64)
	u64 addrlo;
#अन्यथा
	u32 addrhi;
	u32 addrlo;
#पूर्ण_अगर
पूर्ण rraddr;


अटल अंतरभूत व्योम set_rraddr(rraddr *ra, dma_addr_t addr)
अणु
	अचिन्हित दीर्घ baddr = addr;
#अगर (BITS_PER_LONG == 64)
	ra->addrlo = baddr;
#अन्यथा
    /* Don't bother setting zero every समय */
	ra->addrlo = baddr;
#पूर्ण_अगर
	mb();
पूर्ण


अटल अंतरभूत व्योम set_rxaddr(काष्ठा rr_regs __iomem *regs, अस्थिर dma_addr_t addr)
अणु
	अचिन्हित दीर्घ baddr = addr;
#अगर (BITS_PER_LONG == 64) && defined(__LITTLE_ENDIAN)
	ग_लिखोl(baddr & 0xffffffff, &regs->RxRingHi);
	ग_लिखोl(baddr >> 32, &regs->RxRingLo);
#या_अगर (BITS_PER_LONG == 64)
	ग_लिखोl(baddr >> 32, &regs->RxRingHi);
	ग_लिखोl(baddr & 0xffffffff, &regs->RxRingLo);
#अन्यथा
	ग_लिखोl(0, &regs->RxRingHi);
	ग_लिखोl(baddr, &regs->RxRingLo);
#पूर्ण_अगर
	mb();
पूर्ण


अटल अंतरभूत व्योम set_infoaddr(काष्ठा rr_regs __iomem *regs, अस्थिर dma_addr_t addr)
अणु
	अचिन्हित दीर्घ baddr = addr;
#अगर (BITS_PER_LONG == 64) && defined(__LITTLE_ENDIAN)
	ग_लिखोl(baddr & 0xffffffff, &regs->InfoPtrHi);
	ग_लिखोl(baddr >> 32, &regs->InfoPtrLo);
#या_अगर (BITS_PER_LONG == 64)
	ग_लिखोl(baddr >> 32, &regs->InfoPtrHi);
	ग_लिखोl(baddr & 0xffffffff, &regs->InfoPtrLo);
#अन्यथा
	ग_लिखोl(0, &regs->InfoPtrHi);
	ग_लिखोl(baddr, &regs->InfoPtrLo);
#पूर्ण_अगर
	mb();
पूर्ण


/*
 * TX ring
 */

#अगर_घोषित CONFIG_ROADRUNNER_LARGE_RINGS
#घोषणा TX_RING_ENTRIES	32
#अन्यथा
#घोषणा TX_RING_ENTRIES	16
#पूर्ण_अगर
#घोषणा TX_TOTAL_SIZE	(TX_RING_ENTRIES * माप(काष्ठा tx_desc))

काष्ठा tx_descअणु
	rraddr	addr;
	u32	res;
#अगर_घोषित __LITTLE_ENDIAN
	u16	size;
	u8	pad;
	u8	mode;
#अन्यथा
	u8	mode;
	u8	pad;
	u16	size;
#पूर्ण_अगर
पूर्ण;


#अगर_घोषित CONFIG_ROADRUNNER_LARGE_RINGS
#घोषणा RX_RING_ENTRIES	32
#अन्यथा
#घोषणा RX_RING_ENTRIES 16
#पूर्ण_अगर
#घोषणा RX_TOTAL_SIZE	(RX_RING_ENTRIES * माप(काष्ठा rx_desc))

काष्ठा rx_descअणु
	rraddr	addr;
	u32	res;
#अगर_घोषित __LITTLE_ENDIAN
	u16	size;
	u8	pad;
	u8	mode;
#अन्यथा
	u8	mode;
	u8	pad;
	u16	size;
#पूर्ण_अगर
पूर्ण;


/*
 * ioctl's
 */

#घोषणा SIOCRRPFW	SIOCDEVPRIVATE		/* put firmware */
#घोषणा SIOCRRGFW	SIOCDEVPRIVATE+1	/* get firmware */
#घोषणा SIOCRRID	SIOCDEVPRIVATE+2	/* identअगरy */


काष्ठा seg_hdr अणु
	u32	seg_start;
	u32	seg_len;
	u32	seg_eestart;
पूर्ण;


#घोषणा EEPROM_BASE 0x80000000
#घोषणा EEPROM_WORDS 8192
#घोषणा EEPROM_BYTES (EEPROM_WORDS * माप(u32))

काष्ठा eeprom_boot अणु
	u32	key1;
	u32	key2;
	u32	sram_size;
	काष्ठा	seg_hdr loader;
	u32	init_chksum;
	u32	reserved1;
पूर्ण;

काष्ठा eeprom_manf अणु
	u32	HeaderFmt;
	u32	Firmware;
	u32	BoardRevision;
	u32	RoadrunnerRev;
	अक्षर	OpticsPart[8];
	u32	OpticsRev;
	u32	pad1;
	अक्षर	SramPart[8];
	u32	SramRev;
	u32	pad2;
	अक्षर	EepromPart[8];
	u32	EepromRev;
	u32	EepromSize;
	अक्षर	PalPart[8];
	u32	PalRev;
	u32	pad3;
	अक्षर	PalCodeFile[12];
	u32	PalCodeRev;
	अक्षर	BoardULA[8];
	अक्षर	SerialNo[8];
	अक्षर	MfgDate[8];
	अक्षर	MfgTime[8];
	अक्षर	ModअगरyDate[8];
	u32	ModCount;
	u32	pad4[13];
पूर्ण;


काष्ठा eeprom_phase_info अणु
	अक्षर	phase1File[12];
	u32	phase1Rev;
	अक्षर	phase1Date[8];
	अक्षर	phase2File[12];
	u32	phase2Rev;
	अक्षर	phase2Date[8];
	u32	reserved7[4];
पूर्ण;

काष्ठा eeprom_rncd_info अणु
	u32	FwStart;
	u32	FwRev;
	अक्षर	FwDate[8];
	u32	AddrRunCodeSegs;
	u32	FileNames;
	अक्षर	File[13][8];
पूर्ण;


/* Phase 1 region (starts are word offset 0x80) */
काष्ठा phase1_hdrअणु
	u32	jump;
	u32	noop;
	काष्ठा seg_hdr phase2Seg;
पूर्ण;

काष्ठा eeprom अणु
	काष्ठा eeprom_boot	boot;
	u32			pad1[8];
	काष्ठा eeprom_manf	manf;
	काष्ठा eeprom_phase_info phase_info;
	काष्ठा eeprom_rncd_info	rncd_info;
	u32			pad2[15];
	u32			hdr_checksum;
	काष्ठा phase1_hdr	phase1;
पूर्ण;


काष्ठा rr_stats अणु
	u32	NicTimeStamp;
	u32	RngCreated;
	u32	RngDeleted;
	u32	IntrGen;
	u32	NEvtOvfl;
	u32	InvCmd;
	u32	DmaReadErrs;
	u32	DmaWriteErrs;
	u32	StatUpdtT;
	u32	StatUpdtC;
	u32	WatchDog;
	u32	Trace;

	/* Serial HIPPI */
	u32	LnkRdyEst;
	u32	GLinkErr;
	u32	AltFlgErr;
	u32	OvhdBit8Sync;
	u32	RmtSerPrtyErr;
	u32	RmtParPrtyErr;
	u32	RmtLoopBk;
	u32	pad1;

	/* HIPPI tx */
	u32	ConEst;
	u32	ConRejS;
	u32	ConRetry;
	u32	ConTmOut;
	u32	SndConDiscon;
	u32	SndParErr;
	u32	PktSnt;
	u32	pad2[2];
	u32	ShFBstSnt;
	u64	BytSent;
	u32	TxTimeout;
	u32	pad3[3];

	/* HIPPI rx */
	u32	ConAcc;
	u32	ConRejdiPrty;
	u32	ConRejd64b;
	u32	ConRejdBuf;
	u32	RxConDiscon;
	u32	RxConNoData;
	u32	PktRx;
	u32	pad4[2];
	u32	ShFBstRx;
	u64	BytRx;
	u32	RxParErr;
	u32	RxLLRCerr;
	u32	RxBstSZerr;
	u32	RxStateErr;
	u32	RxRdyErr;
	u32	RxInvULP;
	u32	RxSpcBuf;
	u32	RxSpcDesc;
	u32	RxRngSpc;
	u32	RxRngFull;
	u32	RxPktLenErr;
	u32	RxCksmErr;
	u32	RxPktDrp;
	u32	RngLowSpc;
	u32	RngDataClose;
	u32	RxTimeout;
	u32	RxIdle;
पूर्ण;


/*
 * This काष्ठा is shared with the NIC firmware.
 */
काष्ठा ring_ctrl अणु
	rraddr	rngptr;
#अगर_घोषित __LITTLE_ENDIAN
	u16	entries;
	u8	pad;
	u8	entry_size;
	u16	pi;
	u16	mode;
#अन्यथा
	u8	entry_size;
	u8	pad;
	u16	entries;
	u16	mode;
	u16	pi;
#पूर्ण_अगर
पूर्ण;

काष्ठा rr_info अणु
	जोड़ अणु
		काष्ठा rr_stats stats;
		u32 stati[128];
	पूर्ण s;
	काष्ठा ring_ctrl	evt_ctrl;
	काष्ठा ring_ctrl	cmd_ctrl;
	काष्ठा ring_ctrl	tx_ctrl;
	u8			pad[464];
	u8			trace[3072];
पूर्ण;

/*
 * The linux काष्ठाure क्रम the RoadRunner.
 *
 * RX/TX descriptors are put first to make sure they are properly
 * aligned and करो not cross cache-line boundaries.
 */

काष्ठा rr_निजी
अणु
	काष्ठा rx_desc		*rx_ring;
	काष्ठा tx_desc		*tx_ring;
	काष्ठा event		*evt_ring;
	dma_addr_t 		tx_ring_dma;
	dma_addr_t 		rx_ring_dma;
	dma_addr_t 		evt_ring_dma;
	/* Alignment ok ? */
	काष्ठा sk_buff		*rx_skbuff[RX_RING_ENTRIES];
	काष्ठा sk_buff		*tx_skbuff[TX_RING_ENTRIES];
	काष्ठा rr_regs		__iomem *regs;		/* Register base */
	काष्ठा ring_ctrl	*rx_ctrl;	/* Receive ring control */
	काष्ठा rr_info		*info;		/* Shared info page */
	dma_addr_t 		rx_ctrl_dma;
	dma_addr_t 		info_dma;
	spinlock_t		lock;
	काष्ठा समयr_list	समयr;
	u32			cur_rx, cur_cmd, cur_evt;
	u32			dirty_rx, dirty_tx;
	u32			tx_full;
	u32			fw_rev;
	अस्थिर लघु		fw_running;
	काष्ठा pci_dev		*pci_dev;
पूर्ण;


/*
 * Prototypes
 */
अटल पूर्णांक rr_init(काष्ठा net_device *dev);
अटल पूर्णांक rr_init1(काष्ठा net_device *dev);
अटल irqवापस_t rr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

अटल पूर्णांक rr_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t rr_start_xmit(काष्ठा sk_buff *skb,
				 काष्ठा net_device *dev);
अटल पूर्णांक rr_बंद(काष्ठा net_device *dev);
अटल पूर्णांक rr_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल अचिन्हित पूर्णांक rr_पढ़ो_eeprom(काष्ठा rr_निजी *rrpriv,
				   अचिन्हित दीर्घ offset,
				   अचिन्हित अक्षर *buf,
				   अचिन्हित दीर्घ length);
अटल u32 rr_पढ़ो_eeprom_word(काष्ठा rr_निजी *rrpriv, माप_प्रकार offset);
अटल पूर्णांक rr_load_firmware(काष्ठा net_device *dev);
अटल अंतरभूत व्योम rr_raz_tx(काष्ठा rr_निजी *, काष्ठा net_device *);
अटल अंतरभूत व्योम rr_raz_rx(काष्ठा rr_निजी *, काष्ठा net_device *);
#पूर्ण_अगर /* _RRUNNER_H_ */
