<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      FarSync WAN driver क्रम Linux (2.6.x kernel version)
 *
 *      Actually sync driver क्रम X.21, V.35 and V.24 on FarSync T-series cards
 *
 *      Copyright (C) 2001-2004 FarSite Communications Ltd.
 *      www.farsite.co.uk
 *
 *      Author:      R.J.Dunlop    <bob.dunlop@farsite.co.uk>
 *      Maपूर्णांकainer:  Kevin Curtis  <kevin.curtis@farsite.co.uk>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/version.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/अगर.h>
#समावेश <linux/hdlc.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश "farsync.h"

/*
 *      Module info
 */
MODULE_AUTHOR("R.J.Dunlop <bob.dunlop@farsite.co.uk>");
MODULE_DESCRIPTION("FarSync T-Series WAN driver. FarSite Communications Ltd.");
MODULE_LICENSE("GPL");

/*      Driver configuration and global parameters
 *      ==========================================
 */

/*      Number of ports (per card) and cards supported
 */
#घोषणा FST_MAX_PORTS           4
#घोषणा FST_MAX_CARDS           32

/*      Default parameters क्रम the link
 */
#घोषणा FST_TX_QUEUE_LEN        100	/* At 8Mbps a दीर्घer queue length is
					 * useful */
#घोषणा FST_TXQ_DEPTH           16	/* This one is क्रम the buffering
					 * of frames on the way करोwn to the card
					 * so that we can keep the card busy
					 * and maximise throughput
					 */
#घोषणा FST_HIGH_WATER_MARK     12	/* Poपूर्णांक at which we flow control
					 * network layer */
#घोषणा FST_LOW_WATER_MARK      8	/* Poपूर्णांक at which we हटाओ flow
					 * control from network layer */
#घोषणा FST_MAX_MTU             8000	/* Huge but possible */
#घोषणा FST_DEF_MTU             1500	/* Common sane value */

#घोषणा FST_TX_TIMEOUT          (2*HZ)

#अगर_घोषित ARPHRD_RAWHDLC
#घोषणा ARPHRD_MYTYPE   ARPHRD_RAWHDLC	/* Raw frames */
#अन्यथा
#घोषणा ARPHRD_MYTYPE   ARPHRD_HDLC	/* Cisco-HDLC (keepalives etc) */
#पूर्ण_अगर

/*
 * Modules parameters and associated variables
 */
अटल पूर्णांक fst_txq_low = FST_LOW_WATER_MARK;
अटल पूर्णांक fst_txq_high = FST_HIGH_WATER_MARK;
अटल पूर्णांक fst_max_पढ़ोs = 7;
अटल पूर्णांक fst_excluded_cards = 0;
अटल पूर्णांक fst_excluded_list[FST_MAX_CARDS];

module_param(fst_txq_low, पूर्णांक, 0);
module_param(fst_txq_high, पूर्णांक, 0);
module_param(fst_max_पढ़ोs, पूर्णांक, 0);
module_param(fst_excluded_cards, पूर्णांक, 0);
module_param_array(fst_excluded_list, पूर्णांक, शून्य, 0);

/*      Card shared memory layout
 *      =========================
 */
#आशय pack(1)

/*      This inक्रमmation is derived in part from the FarSite FarSync Smc.h
 *      file. Unक्रमtunately various name clashes and the non-portability of the
 *      bit field declarations in that file have meant that I have chosen to
 *      recreate the inक्रमmation here.
 *
 *      The SMC (Shared Memory Configuration) has a version number that is
 *      incremented every समय there is a signअगरicant change. This number can
 *      be used to check that we have not got out of step with the firmware
 *      contained in the .CDE files.
 */
#घोषणा SMC_VERSION 24

#घोषणा FST_MEMSIZE 0x100000	/* Size of card memory (1Mb) */

#घोषणा SMC_BASE 0x00002000L	/* Base offset of the shared memory winकरोw मुख्य
				 * configuration काष्ठाure */
#घोषणा BFM_BASE 0x00010000L	/* Base offset of the shared memory winकरोw DMA
				 * buffers */

#घोषणा LEN_TX_BUFFER 8192	/* Size of packet buffers */
#घोषणा LEN_RX_BUFFER 8192

#घोषणा LEN_SMALL_TX_BUFFER 256	/* Size of obsolete buffs used क्रम DOS diags */
#घोषणा LEN_SMALL_RX_BUFFER 256

#घोषणा NUM_TX_BUFFER 2		/* Must be घातer of 2. Fixed by firmware */
#घोषणा NUM_RX_BUFFER 8

/* Interrupt retry समय in milliseconds */
#घोषणा INT_RETRY_TIME 2

/*      The Am186CH/CC processors support a SmartDMA mode using circular pools
 *      of buffer descriptors. The काष्ठाure is almost identical to that used
 *      in the LANCE Ethernet controllers. Details available as PDF from the
 *      AMD web site: https://www.amd.com/products/epd/processors/\
 *                    2.16bitcont/3.am186cxfa/a21914/21914.pdf
 */
काष्ठा txdesc अणु			/* Transmit descriptor */
	अस्थिर u16 ladr;	/* Low order address of packet. This is a
				 * linear address in the Am186 memory space
				 */
	अस्थिर u8 hadr;	/* High order address. Low 4 bits only, high 4
				 * bits must be zero
				 */
	अस्थिर u8 bits;	/* Status and config */
	अस्थिर u16 bcnt;	/* 2s complement of packet size in low 15 bits.
				 * Transmit terminal count पूर्णांकerrupt enable in
				 * top bit.
				 */
	u16 unused;		/* Not used in Tx */
पूर्ण;

काष्ठा rxdesc अणु			/* Receive descriptor */
	अस्थिर u16 ladr;	/* Low order address of packet */
	अस्थिर u8 hadr;	/* High order address */
	अस्थिर u8 bits;	/* Status and config */
	अस्थिर u16 bcnt;	/* 2s complement of buffer size in low 15 bits.
				 * Receive terminal count पूर्णांकerrupt enable in
				 * top bit.
				 */
	अस्थिर u16 mcnt;	/* Message byte count (15 bits) */
पूर्ण;

/* Convert a length पूर्णांकo the 15 bit 2's complement */
/* #घोषणा cnv_bcnt(len)   (( ~(len) + 1 ) & 0x7FFF ) */
/* Since we need to set the high bit to enable the completion पूर्णांकerrupt this
 * can be made a lot simpler
 */
#घोषणा cnv_bcnt(len)   (-(len))

/* Status and config bits क्रम the above */
#घोषणा DMA_OWN         0x80	/* SmartDMA owns the descriptor */
#घोषणा TX_STP          0x02	/* Tx: start of packet */
#घोषणा TX_ENP          0x01	/* Tx: end of packet */
#घोषणा RX_ERR          0x40	/* Rx: error (OR of next 4 bits) */
#घोषणा RX_FRAM         0x20	/* Rx: framing error */
#घोषणा RX_OFLO         0x10	/* Rx: overflow error */
#घोषणा RX_CRC          0x08	/* Rx: CRC error */
#घोषणा RX_HBUF         0x04	/* Rx: buffer error */
#घोषणा RX_STP          0x02	/* Rx: start of packet */
#घोषणा RX_ENP          0x01	/* Rx: end of packet */

/* Interrupts from the card are caused by various events which are presented
 * in a circular buffer as several events may be processed on one physical पूर्णांक
 */
#घोषणा MAX_CIRBUFF     32

काष्ठा cirbuff अणु
	u8 rdindex;		/* पढ़ो, then increment and wrap */
	u8 wrindex;		/* ग_लिखो, then increment and wrap */
	u8 evntbuff[MAX_CIRBUFF];
पूर्ण;

/* Interrupt event codes.
 * Where appropriate the two low order bits indicate the port number
 */
#घोषणा CTLA_CHG        0x18	/* Control संकेत changed */
#घोषणा CTLB_CHG        0x19
#घोषणा CTLC_CHG        0x1A
#घोषणा CTLD_CHG        0x1B

#घोषणा INIT_CPLT       0x20	/* Initialisation complete */
#घोषणा INIT_FAIL       0x21	/* Initialisation failed */

#घोषणा ABTA_SENT       0x24	/* Abort sent */
#घोषणा ABTB_SENT       0x25
#घोषणा ABTC_SENT       0x26
#घोषणा ABTD_SENT       0x27

#घोषणा TXA_UNDF        0x28	/* Transmission underflow */
#घोषणा TXB_UNDF        0x29
#घोषणा TXC_UNDF        0x2A
#घोषणा TXD_UNDF        0x2B

#घोषणा F56_INT         0x2C
#घोषणा M32_INT         0x2D

#घोषणा TE1_ALMA        0x30

/* Port physical configuration. See farsync.h क्रम field values */
काष्ठा port_cfg अणु
	u16 lineInterface;	/* Physical पूर्णांकerface type */
	u8 x25op;		/* Unused at present */
	u8 पूर्णांकernalClock;	/* 1 => पूर्णांकernal घड़ी, 0 => बाह्यal */
	u8 transparentMode;	/* 1 => on, 0 => off */
	u8 invertClock;		/* 0 => normal, 1 => inverted */
	u8 padBytes[6];		/* Padding */
	u32 lineSpeed;		/* Speed in bps */
पूर्ण;

/* TE1 port physical configuration */
काष्ठा su_config अणु
	u32 dataRate;
	u8 घड़ीing;
	u8 framing;
	u8 काष्ठाure;
	u8 पूर्णांकerface;
	u8 coding;
	u8 lineBuildOut;
	u8 equalizer;
	u8 transparentMode;
	u8 loopMode;
	u8 range;
	u8 txBufferMode;
	u8 rxBufferMode;
	u8 startingSlot;
	u8 losThreshold;
	u8 enableIdleCode;
	u8 idleCode;
	u8 spare[44];
पूर्ण;

/* TE1 Status */
काष्ठा su_status अणु
	u32 receiveBufferDelay;
	u32 framingErrorCount;
	u32 codeViolationCount;
	u32 crcErrorCount;
	u32 lineAttenuation;
	u8 portStarted;
	u8 lossOfSignal;
	u8 receiveRemoteAlarm;
	u8 alarmIndicationSignal;
	u8 spare[40];
पूर्ण;

/* Finally sling all the above together पूर्णांकo the shared memory काष्ठाure.
 * Sorry it's a hodge podge of arrays, structures and unused bits, it's been
 * evolving under NT क्रम some समय so I guess we're stuck with it.
 * The काष्ठाure starts at offset SMC_BASE.
 * See farsync.h क्रम some field values.
 */
काष्ठा fst_shared अणु
	/* DMA descriptor rings */
	काष्ठा rxdesc rxDescrRing[FST_MAX_PORTS][NUM_RX_BUFFER];
	काष्ठा txdesc txDescrRing[FST_MAX_PORTS][NUM_TX_BUFFER];

	/* Obsolete small buffers */
	u8 smallRxBuffer[FST_MAX_PORTS][NUM_RX_BUFFER][LEN_SMALL_RX_BUFFER];
	u8 smallTxBuffer[FST_MAX_PORTS][NUM_TX_BUFFER][LEN_SMALL_TX_BUFFER];

	u8 taskStatus;		/* 0x00 => initialising, 0x01 => running,
				 * 0xFF => halted
				 */

	u8 पूर्णांकerruptHandshake;	/* Set to 0x01 by adapter to संकेत पूर्णांकerrupt,
				 * set to 0xEE by host to acknowledge पूर्णांकerrupt
				 */

	u16 smcVersion;		/* Must match SMC_VERSION */

	u32 smcFirmwareVersion;	/* 0xIIVVRRBB where II = product ID, VV = major
				 * version, RR = revision and BB = build
				 */

	u16 txa_करोne;		/* Obsolete completion flags */
	u16 rxa_करोne;
	u16 txb_करोne;
	u16 rxb_करोne;
	u16 txc_करोne;
	u16 rxc_करोne;
	u16 txd_करोne;
	u16 rxd_करोne;

	u16 mailbox[4];		/* Diagnostics mailbox. Not used */

	काष्ठा cirbuff पूर्णांकerruptEvent;	/* पूर्णांकerrupt causes */

	u32 v24IpSts[FST_MAX_PORTS];	/* V.24 control input status */
	u32 v24OpSts[FST_MAX_PORTS];	/* V.24 control output status */

	काष्ठा port_cfg portConfig[FST_MAX_PORTS];

	u16 घड़ीStatus[FST_MAX_PORTS];	/* lsb: 0=> present, 1=> असलent */

	u16 cableStatus;	/* lsb: 0=> present, 1=> असलent */

	u16 txDescrIndex[FST_MAX_PORTS];	/* transmit descriptor ring index */
	u16 rxDescrIndex[FST_MAX_PORTS];	/* receive descriptor ring index */

	u16 portMailbox[FST_MAX_PORTS][2];	/* command, modअगरier */
	u16 cardMailbox[4];	/* Not used */

	/* Number of बार the card thinks the host has
	 * missed an पूर्णांकerrupt by not acknowledging
	 * within 2mS (I guess NT has problems)
	 */
	u32 पूर्णांकerruptRetryCount;

	/* Driver निजी data used as an ID. We'll not
	 * use this as I'd rather keep such things
	 * in मुख्य memory rather than on the PCI bus
	 */
	u32 portHandle[FST_MAX_PORTS];

	/* Count of Tx underflows क्रम stats */
	u32 transmitBufferUnderflow[FST_MAX_PORTS];

	/* Debounced V.24 control input status */
	u32 v24DebouncedSts[FST_MAX_PORTS];

	/* Adapter debounce समयrs. Don't touch */
	u32 ctsTimer[FST_MAX_PORTS];
	u32 ctsTimerRun[FST_MAX_PORTS];
	u32 dcdTimer[FST_MAX_PORTS];
	u32 dcdTimerRun[FST_MAX_PORTS];

	u32 numberOfPorts;	/* Number of ports detected at startup */

	u16 _reserved[64];

	u16 cardMode;		/* Bit-mask to enable features:
				 * Bit 0: 1 enables LED identअगरy mode
				 */

	u16 portScheduleOffset;

	काष्ठा su_config suConfig;	/* TE1 Bits */
	काष्ठा su_status suStatus;

	u32 endOfSmcSignature;	/* endOfSmcSignature MUST be the last member of
				 * the काष्ठाure and marks the end of shared
				 * memory. Adapter code initializes it as
				 * END_SIG.
				 */
पूर्ण;

/* endOfSmcSignature value */
#घोषणा END_SIG                 0x12345678

/* Mailbox values. (portMailbox) */
#घोषणा NOP             0	/* No operation */
#घोषणा ACK             1	/* Positive acknowledgement to PC driver */
#घोषणा NAK             2	/* Negative acknowledgement to PC driver */
#घोषणा STARTPORT       3	/* Start an HDLC port */
#घोषणा STOPPORT        4	/* Stop an HDLC port */
#घोषणा ABORTTX         5	/* Abort the transmitter क्रम a port */
#घोषणा SETV24O         6	/* Set V24 outमाला_दो */

/* PLX Chip Register Offsets */
#घोषणा CNTRL_9052      0x50	/* Control Register */
#घोषणा CNTRL_9054      0x6c	/* Control Register */

#घोषणा INTCSR_9052     0x4c	/* Interrupt control/status रेजिस्टर */
#घोषणा INTCSR_9054     0x68	/* Interrupt control/status रेजिस्टर */

/* 9054 DMA Registers */
/*
 * Note that we will be using DMA Channel 0 क्रम copying rx data
 * and Channel 1 क्रम copying tx data
 */
#घोषणा DMAMODE0        0x80
#घोषणा DMAPADR0        0x84
#घोषणा DMALADR0        0x88
#घोषणा DMASIZ0         0x8c
#घोषणा DMADPR0         0x90
#घोषणा DMAMODE1        0x94
#घोषणा DMAPADR1        0x98
#घोषणा DMALADR1        0x9c
#घोषणा DMASIZ1         0xa0
#घोषणा DMADPR1         0xa4
#घोषणा DMACSR0         0xa8
#घोषणा DMACSR1         0xa9
#घोषणा DMAARB          0xac
#घोषणा DMATHR          0xb0
#घोषणा DMADAC0         0xb4
#घोषणा DMADAC1         0xb8
#घोषणा DMAMARBR        0xac

#घोषणा FST_MIN_DMA_LEN 64
#घोषणा FST_RX_DMA_INT  0x01
#घोषणा FST_TX_DMA_INT  0x02
#घोषणा FST_CARD_INT    0x04

/* Larger buffers are positioned in memory at offset BFM_BASE */
काष्ठा buf_winकरोw अणु
	u8 txBuffer[FST_MAX_PORTS][NUM_TX_BUFFER][LEN_TX_BUFFER];
	u8 rxBuffer[FST_MAX_PORTS][NUM_RX_BUFFER][LEN_RX_BUFFER];
पूर्ण;

/* Calculate offset of a buffer object within the shared memory winकरोw */
#घोषणा BUF_OFFSET(X)   (BFM_BASE + दुरत्व(काष्ठा buf_winकरोw, X))

#आशय pack()

/*      Device driver निजी inक्रमmation
 *      =================================
 */
/*      Per port (line or channel) inक्रमmation
 */
काष्ठा fst_port_info अणु
        काष्ठा net_device *dev; /* Device काष्ठा - must be first */
	काष्ठा fst_card_info *card;	/* Card we're associated with */
	पूर्णांक index;		/* Port index on the card */
	पूर्णांक hwअगर;		/* Line hardware (lineInterface copy) */
	पूर्णांक run;		/* Port is running */
	पूर्णांक mode;		/* Normal or FarSync raw */
	पूर्णांक rxpos;		/* Next Rx buffer to use */
	पूर्णांक txpos;		/* Next Tx buffer to use */
	पूर्णांक txipos;		/* Next Tx buffer to check क्रम मुक्त */
	पूर्णांक start;		/* Indication of start/stop to network */
	/*
	 * A sixteen entry transmit queue
	 */
	पूर्णांक txqs;		/* index to get next buffer to tx */
	पूर्णांक txqe;		/* index to queue next packet */
	काष्ठा sk_buff *txq[FST_TXQ_DEPTH];	/* The queue */
	पूर्णांक rxqdepth;
पूर्ण;

/*      Per card inक्रमmation
 */
काष्ठा fst_card_info अणु
	अक्षर __iomem *mem;	/* Card memory mapped to kernel space */
	अक्षर __iomem *ctlmem;	/* Control memory क्रम PCI cards */
	अचिन्हित पूर्णांक phys_mem;	/* Physical memory winकरोw address */
	अचिन्हित पूर्णांक phys_ctlmem;	/* Physical control memory address */
	अचिन्हित पूर्णांक irq;	/* Interrupt request line number */
	अचिन्हित पूर्णांक nports;	/* Number of serial ports */
	अचिन्हित पूर्णांक type;	/* Type index of card */
	अचिन्हित पूर्णांक state;	/* State of card */
	spinlock_t card_lock;	/* Lock क्रम SMP access */
	अचिन्हित लघु pci_conf;	/* PCI card config in I/O space */
	/* Per port info */
	काष्ठा fst_port_info ports[FST_MAX_PORTS];
	काष्ठा pci_dev *device;	/* Inक्रमmation about the pci device */
	पूर्णांक card_no;		/* Inst of the card on the प्रणाली */
	पूर्णांक family;		/* TxP or TxU */
	पूर्णांक dmarx_in_progress;
	पूर्णांक dmatx_in_progress;
	अचिन्हित दीर्घ पूर्णांक_count;
	अचिन्हित दीर्घ पूर्णांक_समय_ave;
	व्योम *rx_dma_handle_host;
	dma_addr_t rx_dma_handle_card;
	व्योम *tx_dma_handle_host;
	dma_addr_t tx_dma_handle_card;
	काष्ठा sk_buff *dma_skb_rx;
	काष्ठा fst_port_info *dma_port_rx;
	काष्ठा fst_port_info *dma_port_tx;
	पूर्णांक dma_len_rx;
	पूर्णांक dma_len_tx;
	पूर्णांक dma_txpos;
	पूर्णांक dma_rxpos;
पूर्ण;

/* Convert an HDLC device poपूर्णांकer पूर्णांकo a port info poपूर्णांकer and similar */
#घोषणा dev_to_port(D)  (dev_to_hdlc(D)->priv)
#घोषणा port_to_dev(P)  ((P)->dev)


/*
 *      Shared memory winकरोw access macros
 *
 *      We have a nice memory based काष्ठाure above, which could be directly
 *      mapped on i386 but might not work on other architectures unless we use
 *      the पढ़ोb,w,l and ग_लिखोb,w,l macros. Unक्रमtunately these macros take
 *      physical offsets so we have to convert. The only saving grace is that
 *      this should all collapse back to a simple indirection eventually.
 */
#घोषणा WIN_OFFSET(X)   ((दीर्घ)&(((काष्ठा fst_shared *)SMC_BASE)->X))

#घोषणा FST_RDB(C,E)    पढ़ोb ((C)->mem + WIN_OFFSET(E))
#घोषणा FST_RDW(C,E)    पढ़ोw ((C)->mem + WIN_OFFSET(E))
#घोषणा FST_RDL(C,E)    पढ़ोl ((C)->mem + WIN_OFFSET(E))

#घोषणा FST_WRB(C,E,B)  ग_लिखोb ((B), (C)->mem + WIN_OFFSET(E))
#घोषणा FST_WRW(C,E,W)  ग_लिखोw ((W), (C)->mem + WIN_OFFSET(E))
#घोषणा FST_WRL(C,E,L)  ग_लिखोl ((L), (C)->mem + WIN_OFFSET(E))

/*
 *      Debug support
 */
#अगर FST_DEBUG

अटल पूर्णांक fst_debug_mask = अणु FST_DEBUG पूर्ण;

/* Most common debug activity is to prपूर्णांक something अगर the corresponding bit
 * is set in the debug mask. Note: this uses a non-ANSI extension in GCC to
 * support variable numbers of macro parameters. The inverted अगर prevents us
 * eating someone अन्यथा's अन्यथा clause.
 */
#घोषणा dbg(F, fmt, args...)					\
करो अणु								\
	अगर (fst_debug_mask & (F))				\
		prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##args);		\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा dbg(F, fmt, args...)					\
करो अणु								\
	अगर (0)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##args);		\
पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 *      PCI ID lookup table
 */
अटल स्थिर काष्ठा pci_device_id fst_pci_dev_id[] = अणु
	अणुPCI_VENDOR_ID_FARSITE, PCI_DEVICE_ID_FARSITE_T2P, PCI_ANY_ID, 
	 PCI_ANY_ID, 0, 0, FST_TYPE_T2Pपूर्ण,

	अणुPCI_VENDOR_ID_FARSITE, PCI_DEVICE_ID_FARSITE_T4P, PCI_ANY_ID, 
	 PCI_ANY_ID, 0, 0, FST_TYPE_T4Pपूर्ण,

	अणुPCI_VENDOR_ID_FARSITE, PCI_DEVICE_ID_FARSITE_T1U, PCI_ANY_ID, 
	 PCI_ANY_ID, 0, 0, FST_TYPE_T1Uपूर्ण,

	अणुPCI_VENDOR_ID_FARSITE, PCI_DEVICE_ID_FARSITE_T2U, PCI_ANY_ID, 
	 PCI_ANY_ID, 0, 0, FST_TYPE_T2Uपूर्ण,

	अणुPCI_VENDOR_ID_FARSITE, PCI_DEVICE_ID_FARSITE_T4U, PCI_ANY_ID, 
	 PCI_ANY_ID, 0, 0, FST_TYPE_T4Uपूर्ण,

	अणुPCI_VENDOR_ID_FARSITE, PCI_DEVICE_ID_FARSITE_TE1, PCI_ANY_ID, 
	 PCI_ANY_ID, 0, 0, FST_TYPE_TE1पूर्ण,

	अणुPCI_VENDOR_ID_FARSITE, PCI_DEVICE_ID_FARSITE_TE1C, PCI_ANY_ID, 
	 PCI_ANY_ID, 0, 0, FST_TYPE_TE1पूर्ण,
	अणु0,पूर्ण			/* End */
पूर्ण;

MODULE_DEVICE_TABLE(pci, fst_pci_dev_id);

/*
 *      Device Driver Work Queues
 *
 *      So that we करोn't spend too much समय processing events in the 
 *      Interrupt Service routine, we will declare a work queue per Card 
 *      and make the ISR schedule a task in the queue क्रम later execution.
 *      In the 2.4 Kernel we used to use the immediate queue क्रम BH's
 *      Now that they are gone, tasklets seem to be much better than work 
 *      queues.
 */

अटल व्योम करो_bottom_half_tx(काष्ठा fst_card_info *card);
अटल व्योम करो_bottom_half_rx(काष्ठा fst_card_info *card);
अटल व्योम fst_process_tx_work_q(काष्ठा tasklet_काष्ठा *unused);
अटल व्योम fst_process_पूर्णांक_work_q(काष्ठा tasklet_काष्ठा *unused);

अटल DECLARE_TASKLET(fst_tx_task, fst_process_tx_work_q);
अटल DECLARE_TASKLET(fst_पूर्णांक_task, fst_process_पूर्णांक_work_q);

अटल काष्ठा fst_card_info *fst_card_array[FST_MAX_CARDS];
अटल DEFINE_SPINLOCK(fst_work_q_lock);
अटल u64 fst_work_txq;
अटल u64 fst_work_पूर्णांकq;

अटल व्योम
fst_q_work_item(u64 * queue, पूर्णांक card_index)
अणु
	अचिन्हित दीर्घ flags;
	u64 mask;

	/*
	 * Grab the queue exclusively
	 */
	spin_lock_irqsave(&fst_work_q_lock, flags);

	/*
	 * Making an entry in the queue is simply a matter of setting
	 * a bit क्रम the card indicating that there is work to करो in the
	 * bottom half क्रम the card.  Note the limitation of 64 cards.
	 * That ought to be enough
	 */
	mask = (u64)1 << card_index;
	*queue |= mask;
	spin_unlock_irqrestore(&fst_work_q_lock, flags);
पूर्ण

अटल व्योम
fst_process_tx_work_q(काष्ठा tasklet_काष्ठा *unused)
अणु
	अचिन्हित दीर्घ flags;
	u64 work_txq;
	पूर्णांक i;

	/*
	 * Grab the queue exclusively
	 */
	dbg(DBG_TX, "fst_process_tx_work_q\n");
	spin_lock_irqsave(&fst_work_q_lock, flags);
	work_txq = fst_work_txq;
	fst_work_txq = 0;
	spin_unlock_irqrestore(&fst_work_q_lock, flags);

	/*
	 * Call the bottom half क्रम each card with work रुकोing
	 */
	क्रम (i = 0; i < FST_MAX_CARDS; i++) अणु
		अगर (work_txq & 0x01) अणु
			अगर (fst_card_array[i] != शून्य) अणु
				dbg(DBG_TX, "Calling tx bh for card %d\n", i);
				करो_bottom_half_tx(fst_card_array[i]);
			पूर्ण
		पूर्ण
		work_txq = work_txq >> 1;
	पूर्ण
पूर्ण

अटल व्योम
fst_process_पूर्णांक_work_q(काष्ठा tasklet_काष्ठा *unused)
अणु
	अचिन्हित दीर्घ flags;
	u64 work_पूर्णांकq;
	पूर्णांक i;

	/*
	 * Grab the queue exclusively
	 */
	dbg(DBG_INTR, "fst_process_int_work_q\n");
	spin_lock_irqsave(&fst_work_q_lock, flags);
	work_पूर्णांकq = fst_work_पूर्णांकq;
	fst_work_पूर्णांकq = 0;
	spin_unlock_irqrestore(&fst_work_q_lock, flags);

	/*
	 * Call the bottom half क्रम each card with work रुकोing
	 */
	क्रम (i = 0; i < FST_MAX_CARDS; i++) अणु
		अगर (work_पूर्णांकq & 0x01) अणु
			अगर (fst_card_array[i] != शून्य) अणु
				dbg(DBG_INTR,
				    "Calling rx & tx bh for card %d\n", i);
				करो_bottom_half_rx(fst_card_array[i]);
				करो_bottom_half_tx(fst_card_array[i]);
			पूर्ण
		पूर्ण
		work_पूर्णांकq = work_पूर्णांकq >> 1;
	पूर्ण
पूर्ण

/*      Card control functions
 *      ======================
 */
/*      Place the processor in reset state
 *
 * Used to be a simple ग_लिखो to card control space but a glitch in the latest
 * AMD Am186CH processor means that we now have to करो it by निश्चितing and de-
 * निश्चितing the PLX chip PCI Adapter Software Reset. Bit 30 in CNTRL रेजिस्टर
 * at offset 9052_CNTRL.  Note the updates क्रम the TXU.
 */
अटल अंतरभूत व्योम
fst_cpureset(काष्ठा fst_card_info *card)
अणु
	अचिन्हित अक्षर पूर्णांकerrupt_line_रेजिस्टर;
	अचिन्हित पूर्णांक regval;

	अगर (card->family == FST_FAMILY_TXU) अणु
		अगर (pci_पढ़ो_config_byte
		    (card->device, PCI_INTERRUPT_LINE, &पूर्णांकerrupt_line_रेजिस्टर)) अणु
			dbg(DBG_ASS,
			    "Error in reading interrupt line register\n");
		पूर्ण
		/*
		 * Assert PLX software reset and Am186 hardware reset
		 * and then deनिश्चित the PLX software reset but 186 still in reset
		 */
		outw(0x440f, card->pci_conf + CNTRL_9054 + 2);
		outw(0x040f, card->pci_conf + CNTRL_9054 + 2);
		/*
		 * We are delaying here to allow the 9054 to reset itself
		 */
		usleep_range(10, 20);
		outw(0x240f, card->pci_conf + CNTRL_9054 + 2);
		/*
		 * We are delaying here to allow the 9054 to reload its eeprom
		 */
		usleep_range(10, 20);
		outw(0x040f, card->pci_conf + CNTRL_9054 + 2);

		अगर (pci_ग_लिखो_config_byte
		    (card->device, PCI_INTERRUPT_LINE, पूर्णांकerrupt_line_रेजिस्टर)) अणु
			dbg(DBG_ASS,
			    "Error in writing interrupt line register\n");
		पूर्ण

	पूर्ण अन्यथा अणु
		regval = inl(card->pci_conf + CNTRL_9052);

		outl(regval | 0x40000000, card->pci_conf + CNTRL_9052);
		outl(regval & ~0x40000000, card->pci_conf + CNTRL_9052);
	पूर्ण
पूर्ण

/*      Release the processor from reset
 */
अटल अंतरभूत व्योम
fst_cpurelease(काष्ठा fst_card_info *card)
अणु
	अगर (card->family == FST_FAMILY_TXU) अणु
		/*
		 * Force posted ग_लिखोs to complete
		 */
		(व्योम) पढ़ोb(card->mem);

		/*
		 * Release LRESET DO = 1
		 * Then release Local Hold, DO = 1
		 */
		outw(0x040e, card->pci_conf + CNTRL_9054 + 2);
		outw(0x040f, card->pci_conf + CNTRL_9054 + 2);
	पूर्ण अन्यथा अणु
		(व्योम) पढ़ोb(card->ctlmem);
	पूर्ण
पूर्ण

/*      Clear the cards पूर्णांकerrupt flag
 */
अटल अंतरभूत व्योम
fst_clear_पूर्णांकr(काष्ठा fst_card_info *card)
अणु
	अगर (card->family == FST_FAMILY_TXU) अणु
		(व्योम) पढ़ोb(card->ctlmem);
	पूर्ण अन्यथा अणु
		/* Poke the appropriate PLX chip रेजिस्टर (same as enabling पूर्णांकerrupts)
		 */
		outw(0x0543, card->pci_conf + INTCSR_9052);
	पूर्ण
पूर्ण

/*      Enable card पूर्णांकerrupts
 */
अटल अंतरभूत व्योम
fst_enable_पूर्णांकr(काष्ठा fst_card_info *card)
अणु
	अगर (card->family == FST_FAMILY_TXU) अणु
		outl(0x0f0c0900, card->pci_conf + INTCSR_9054);
	पूर्ण अन्यथा अणु
		outw(0x0543, card->pci_conf + INTCSR_9052);
	पूर्ण
पूर्ण

/*      Disable card पूर्णांकerrupts
 */
अटल अंतरभूत व्योम
fst_disable_पूर्णांकr(काष्ठा fst_card_info *card)
अणु
	अगर (card->family == FST_FAMILY_TXU) अणु
		outl(0x00000000, card->pci_conf + INTCSR_9054);
	पूर्ण अन्यथा अणु
		outw(0x0000, card->pci_conf + INTCSR_9052);
	पूर्ण
पूर्ण

/*      Process the result of trying to pass a received frame up the stack
 */
अटल व्योम
fst_process_rx_status(पूर्णांक rx_status, अक्षर *name)
अणु
	चयन (rx_status) अणु
	हाल NET_RX_SUCCESS:
		अणु
			/*
			 * Nothing to करो here
			 */
			अवरोध;
		पूर्ण
	हाल NET_RX_DROP:
		अणु
			dbg(DBG_ASS, "%s: Received packet dropped\n", name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*      Initilaise DMA क्रम PLX 9054
 */
अटल अंतरभूत व्योम
fst_init_dma(काष्ठा fst_card_info *card)
अणु
	/*
	 * This is only required क्रम the PLX 9054
	 */
	अगर (card->family == FST_FAMILY_TXU) अणु
	        pci_set_master(card->device);
		outl(0x00020441, card->pci_conf + DMAMODE0);
		outl(0x00020441, card->pci_conf + DMAMODE1);
		outl(0x0, card->pci_conf + DMATHR);
	पूर्ण
पूर्ण

/*      Tx dma complete पूर्णांकerrupt
 */
अटल व्योम
fst_tx_dma_complete(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port,
		    पूर्णांक len, पूर्णांक txpos)
अणु
	काष्ठा net_device *dev = port_to_dev(port);

	/*
	 * Everything is now set, just tell the card to go
	 */
	dbg(DBG_TX, "fst_tx_dma_complete\n");
	FST_WRB(card, txDescrRing[port->index][txpos].bits,
		DMA_OWN | TX_STP | TX_ENP);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += len;
	netअगर_trans_update(dev);
पूर्ण

/*
 * Mark it क्रम our own raw sockets पूर्णांकerface
 */
अटल __be16 farsync_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	skb->dev = dev;
	skb_reset_mac_header(skb);
	skb->pkt_type = PACKET_HOST;
	वापस htons(ETH_P_CUST);
पूर्ण

/*      Rx dma complete पूर्णांकerrupt
 */
अटल व्योम
fst_rx_dma_complete(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port,
		    पूर्णांक len, काष्ठा sk_buff *skb, पूर्णांक rxp)
अणु
	काष्ठा net_device *dev = port_to_dev(port);
	पूर्णांक pi;
	पूर्णांक rx_status;

	dbg(DBG_TX, "fst_rx_dma_complete\n");
	pi = port->index;
	skb_put_data(skb, card->rx_dma_handle_host, len);

	/* Reset buffer descriptor */
	FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);

	/* Update stats */
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;

	/* Push upstream */
	dbg(DBG_RX, "Pushing the frame up the stack\n");
	अगर (port->mode == FST_RAW)
		skb->protocol = farsync_type_trans(skb, dev);
	अन्यथा
		skb->protocol = hdlc_type_trans(skb, dev);
	rx_status = netअगर_rx(skb);
	fst_process_rx_status(rx_status, port_to_dev(port)->name);
	अगर (rx_status == NET_RX_DROP)
		dev->stats.rx_dropped++;
पूर्ण

/*
 *      Receive a frame through the DMA
 */
अटल अंतरभूत व्योम
fst_rx_dma(काष्ठा fst_card_info *card, dma_addr_t dma, u32 mem, पूर्णांक len)
अणु
	/*
	 * This routine will setup the DMA and start it
	 */

	dbg(DBG_RX, "In fst_rx_dma %x %x %d\n", (u32)dma, mem, len);
	अगर (card->dmarx_in_progress) अणु
		dbg(DBG_ASS, "In fst_rx_dma while dma in progress\n");
	पूर्ण

	outl(dma, card->pci_conf + DMAPADR0);	/* Copy to here */
	outl(mem, card->pci_conf + DMALADR0);	/* from here */
	outl(len, card->pci_conf + DMASIZ0);	/* क्रम this length */
	outl(0x00000000c, card->pci_conf + DMADPR0);	/* In this direction */

	/*
	 * We use the dmarx_in_progress flag to flag the channel as busy
	 */
	card->dmarx_in_progress = 1;
	outb(0x03, card->pci_conf + DMACSR0);	/* Start the transfer */
पूर्ण

/*
 *      Send a frame through the DMA
 */
अटल अंतरभूत व्योम
fst_tx_dma(काष्ठा fst_card_info *card, dma_addr_t dma, u32 mem, पूर्णांक len)
अणु
	/*
	 * This routine will setup the DMA and start it.
	 */

	dbg(DBG_TX, "In fst_tx_dma %x %x %d\n", (u32)dma, mem, len);
	अगर (card->dmatx_in_progress) अणु
		dbg(DBG_ASS, "In fst_tx_dma while dma in progress\n");
	पूर्ण

	outl(dma, card->pci_conf + DMAPADR1);	/* Copy from here */
	outl(mem, card->pci_conf + DMALADR1);	/* to here */
	outl(len, card->pci_conf + DMASIZ1);	/* क्रम this length */
	outl(0x000000004, card->pci_conf + DMADPR1);	/* In this direction */

	/*
	 * We use the dmatx_in_progress to flag the channel as busy
	 */
	card->dmatx_in_progress = 1;
	outb(0x03, card->pci_conf + DMACSR1);	/* Start the transfer */
पूर्ण

/*      Issue a Mailbox command क्रम a port.
 *      Note we issue them on a fire and क्रमget basis, not expecting to see an
 *      error and not रुकोing क्रम completion.
 */
अटल व्योम
fst_issue_cmd(काष्ठा fst_port_info *port, अचिन्हित लघु cmd)
अणु
	काष्ठा fst_card_info *card;
	अचिन्हित लघु mbval;
	अचिन्हित दीर्घ flags;
	पूर्णांक safety;

	card = port->card;
	spin_lock_irqsave(&card->card_lock, flags);
	mbval = FST_RDW(card, portMailbox[port->index][0]);

	safety = 0;
	/* Wait क्रम any previous command to complete */
	जबतक (mbval > NAK) अणु
		spin_unlock_irqrestore(&card->card_lock, flags);
		schedule_समयout_unपूर्णांकerruptible(1);
		spin_lock_irqsave(&card->card_lock, flags);

		अगर (++safety > 2000) अणु
			pr_err("Mailbox safety timeout\n");
			अवरोध;
		पूर्ण

		mbval = FST_RDW(card, portMailbox[port->index][0]);
	पूर्ण
	अगर (safety > 0) अणु
		dbg(DBG_CMD, "Mailbox clear after %d jiffies\n", safety);
	पूर्ण
	अगर (mbval == NAK) अणु
		dbg(DBG_CMD, "issue_cmd: previous command was NAK'd\n");
	पूर्ण

	FST_WRW(card, portMailbox[port->index][0], cmd);

	अगर (cmd == ABORTTX || cmd == STARTPORT) अणु
		port->txpos = 0;
		port->txipos = 0;
		port->start = 0;
	पूर्ण

	spin_unlock_irqrestore(&card->card_lock, flags);
पूर्ण

/*      Port output संकेतs control
 */
अटल अंतरभूत व्योम
fst_op_उठाओ(काष्ठा fst_port_info *port, अचिन्हित पूर्णांक outमाला_दो)
अणु
	outमाला_दो |= FST_RDL(port->card, v24OpSts[port->index]);
	FST_WRL(port->card, v24OpSts[port->index], outमाला_दो);

	अगर (port->run)
		fst_issue_cmd(port, SETV24O);
पूर्ण

अटल अंतरभूत व्योम
fst_op_lower(काष्ठा fst_port_info *port, अचिन्हित पूर्णांक outमाला_दो)
अणु
	outमाला_दो = ~outमाला_दो & FST_RDL(port->card, v24OpSts[port->index]);
	FST_WRL(port->card, v24OpSts[port->index], outमाला_दो);

	अगर (port->run)
		fst_issue_cmd(port, SETV24O);
पूर्ण

/*
 *      Setup port Rx buffers
 */
अटल व्योम
fst_rx_config(काष्ठा fst_port_info *port)
अणु
	पूर्णांक i;
	पूर्णांक pi;
	अचिन्हित पूर्णांक offset;
	अचिन्हित दीर्घ flags;
	काष्ठा fst_card_info *card;

	pi = port->index;
	card = port->card;
	spin_lock_irqsave(&card->card_lock, flags);
	क्रम (i = 0; i < NUM_RX_BUFFER; i++) अणु
		offset = BUF_OFFSET(rxBuffer[pi][i][0]);

		FST_WRW(card, rxDescrRing[pi][i].ladr, (u16) offset);
		FST_WRB(card, rxDescrRing[pi][i].hadr, (u8) (offset >> 16));
		FST_WRW(card, rxDescrRing[pi][i].bcnt, cnv_bcnt(LEN_RX_BUFFER));
		FST_WRW(card, rxDescrRing[pi][i].mcnt, LEN_RX_BUFFER);
		FST_WRB(card, rxDescrRing[pi][i].bits, DMA_OWN);
	पूर्ण
	port->rxpos = 0;
	spin_unlock_irqrestore(&card->card_lock, flags);
पूर्ण

/*
 *      Setup port Tx buffers
 */
अटल व्योम
fst_tx_config(काष्ठा fst_port_info *port)
अणु
	पूर्णांक i;
	पूर्णांक pi;
	अचिन्हित पूर्णांक offset;
	अचिन्हित दीर्घ flags;
	काष्ठा fst_card_info *card;

	pi = port->index;
	card = port->card;
	spin_lock_irqsave(&card->card_lock, flags);
	क्रम (i = 0; i < NUM_TX_BUFFER; i++) अणु
		offset = BUF_OFFSET(txBuffer[pi][i][0]);

		FST_WRW(card, txDescrRing[pi][i].ladr, (u16) offset);
		FST_WRB(card, txDescrRing[pi][i].hadr, (u8) (offset >> 16));
		FST_WRW(card, txDescrRing[pi][i].bcnt, 0);
		FST_WRB(card, txDescrRing[pi][i].bits, 0);
	पूर्ण
	port->txpos = 0;
	port->txipos = 0;
	port->start = 0;
	spin_unlock_irqrestore(&card->card_lock, flags);
पूर्ण

/*      TE1 Alarm change पूर्णांकerrupt event
 */
अटल व्योम
fst_पूर्णांकr_te1_alarm(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port)
अणु
	u8 los;
	u8 rra;
	u8 ais;

	los = FST_RDB(card, suStatus.lossOfSignal);
	rra = FST_RDB(card, suStatus.receiveRemoteAlarm);
	ais = FST_RDB(card, suStatus.alarmIndicationSignal);

	अगर (los) अणु
		/*
		 * Lost the link
		 */
		अगर (netअगर_carrier_ok(port_to_dev(port))) अणु
			dbg(DBG_INTR, "Net carrier off\n");
			netअगर_carrier_off(port_to_dev(port));
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Link available
		 */
		अगर (!netअगर_carrier_ok(port_to_dev(port))) अणु
			dbg(DBG_INTR, "Net carrier on\n");
			netअगर_carrier_on(port_to_dev(port));
		पूर्ण
	पूर्ण

	अगर (los)
		dbg(DBG_INTR, "Assert LOS Alarm\n");
	अन्यथा
		dbg(DBG_INTR, "De-assert LOS Alarm\n");
	अगर (rra)
		dbg(DBG_INTR, "Assert RRA Alarm\n");
	अन्यथा
		dbg(DBG_INTR, "De-assert RRA Alarm\n");

	अगर (ais)
		dbg(DBG_INTR, "Assert AIS Alarm\n");
	अन्यथा
		dbg(DBG_INTR, "De-assert AIS Alarm\n");
पूर्ण

/*      Control संकेत change पूर्णांकerrupt event
 */
अटल व्योम
fst_पूर्णांकr_ctlchg(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port)
अणु
	पूर्णांक संकेतs;

	संकेतs = FST_RDL(card, v24DebouncedSts[port->index]);

	अगर (संकेतs & (((port->hwअगर == X21) || (port->hwअगर == X21D))
		       ? IPSTS_INDICATE : IPSTS_DCD)) अणु
		अगर (!netअगर_carrier_ok(port_to_dev(port))) अणु
			dbg(DBG_INTR, "DCD active\n");
			netअगर_carrier_on(port_to_dev(port));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(port_to_dev(port))) अणु
			dbg(DBG_INTR, "DCD lost\n");
			netअगर_carrier_off(port_to_dev(port));
		पूर्ण
	पूर्ण
पूर्ण

/*      Log Rx Errors
 */
अटल व्योम
fst_log_rx_error(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port,
		 अचिन्हित अक्षर dmabits, पूर्णांक rxp, अचिन्हित लघु len)
अणु
	काष्ठा net_device *dev = port_to_dev(port);

	/*
	 * Increment the appropriate error counter
	 */
	dev->stats.rx_errors++;
	अगर (dmabits & RX_OFLO) अणु
		dev->stats.rx_fअगरo_errors++;
		dbg(DBG_ASS, "Rx fifo error on card %d port %d buffer %d\n",
		    card->card_no, port->index, rxp);
	पूर्ण
	अगर (dmabits & RX_CRC) अणु
		dev->stats.rx_crc_errors++;
		dbg(DBG_ASS, "Rx crc error on card %d port %d\n",
		    card->card_no, port->index);
	पूर्ण
	अगर (dmabits & RX_FRAM) अणु
		dev->stats.rx_frame_errors++;
		dbg(DBG_ASS, "Rx frame error on card %d port %d\n",
		    card->card_no, port->index);
	पूर्ण
	अगर (dmabits == (RX_STP | RX_ENP)) अणु
		dev->stats.rx_length_errors++;
		dbg(DBG_ASS, "Rx length error (%d) on card %d port %d\n",
		    len, card->card_no, port->index);
	पूर्ण
पूर्ण

/*      Rx Error Recovery
 */
अटल व्योम
fst_recover_rx_error(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port,
		     अचिन्हित अक्षर dmabits, पूर्णांक rxp, अचिन्हित लघु len)
अणु
	पूर्णांक i;
	पूर्णांक pi;

	pi = port->index;
	/* 
	 * Discard buffer descriptors until we see the start of the
	 * next frame.  Note that क्रम दीर्घ frames this could be in
	 * a subsequent पूर्णांकerrupt. 
	 */
	i = 0;
	जबतक ((dmabits & (DMA_OWN | RX_STP)) == 0) अणु
		FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);
		rxp = (rxp+1) % NUM_RX_BUFFER;
		अगर (++i > NUM_RX_BUFFER) अणु
			dbg(DBG_ASS, "intr_rx: Discarding more bufs"
			    " than we have\n");
			अवरोध;
		पूर्ण
		dmabits = FST_RDB(card, rxDescrRing[pi][rxp].bits);
		dbg(DBG_ASS, "DMA Bits of next buffer was %x\n", dmabits);
	पूर्ण
	dbg(DBG_ASS, "There were %d subsequent buffers in error\n", i);

	/* Discard the terminal buffer */
	अगर (!(dmabits & DMA_OWN)) अणु
		FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);
		rxp = (rxp+1) % NUM_RX_BUFFER;
	पूर्ण
	port->rxpos = rxp;
	वापस;

पूर्ण

/*      Rx complete पूर्णांकerrupt
 */
अटल व्योम
fst_पूर्णांकr_rx(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port)
अणु
	अचिन्हित अक्षर dmabits;
	पूर्णांक pi;
	पूर्णांक rxp;
	पूर्णांक rx_status;
	अचिन्हित लघु len;
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev = port_to_dev(port);

	/* Check we have a buffer to process */
	pi = port->index;
	rxp = port->rxpos;
	dmabits = FST_RDB(card, rxDescrRing[pi][rxp].bits);
	अगर (dmabits & DMA_OWN) अणु
		dbg(DBG_RX | DBG_INTR, "intr_rx: No buffer port %d pos %d\n",
		    pi, rxp);
		वापस;
	पूर्ण
	अगर (card->dmarx_in_progress) अणु
		वापस;
	पूर्ण

	/* Get buffer length */
	len = FST_RDW(card, rxDescrRing[pi][rxp].mcnt);
	/* Discard the CRC */
	len -= 2;
	अगर (len == 0) अणु
		/*
		 * This seems to happen on the TE1 पूर्णांकerface someबार
		 * so throw the frame away and log the event.
		 */
		pr_err("Frame received with 0 length. Card %d Port %d\n",
		       card->card_no, port->index);
		/* Return descriptor to card */
		FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);

		rxp = (rxp+1) % NUM_RX_BUFFER;
		port->rxpos = rxp;
		वापस;
	पूर्ण

	/* Check buffer length and क्रम other errors. We insist on one packet
	 * in one buffer. This simplअगरies things greatly and since we've
	 * allocated 8K it shouldn't be a real world limitation
	 */
	dbg(DBG_RX, "intr_rx: %d,%d: flags %x len %d\n", pi, rxp, dmabits, len);
	अगर (dmabits != (RX_STP | RX_ENP) || len > LEN_RX_BUFFER - 2) अणु
		fst_log_rx_error(card, port, dmabits, rxp, len);
		fst_recover_rx_error(card, port, dmabits, rxp, len);
		वापस;
	पूर्ण

	/* Allocate SKB */
	अगर ((skb = dev_alloc_skb(len)) == शून्य) अणु
		dbg(DBG_RX, "intr_rx: can't allocate buffer\n");

		dev->stats.rx_dropped++;

		/* Return descriptor to card */
		FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);

		rxp = (rxp+1) % NUM_RX_BUFFER;
		port->rxpos = rxp;
		वापस;
	पूर्ण

	/*
	 * We know the length we need to receive, len.
	 * It's not worth using the DMA क्रम पढ़ोs of less than
	 * FST_MIN_DMA_LEN
	 */

	अगर ((len < FST_MIN_DMA_LEN) || (card->family == FST_FAMILY_TXP)) अणु
		स_नकल_fromio(skb_put(skb, len),
			      card->mem + BUF_OFFSET(rxBuffer[pi][rxp][0]),
			      len);

		/* Reset buffer descriptor */
		FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);

		/* Update stats */
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += len;

		/* Push upstream */
		dbg(DBG_RX, "Pushing frame up the stack\n");
		अगर (port->mode == FST_RAW)
			skb->protocol = farsync_type_trans(skb, dev);
		अन्यथा
			skb->protocol = hdlc_type_trans(skb, dev);
		rx_status = netअगर_rx(skb);
		fst_process_rx_status(rx_status, port_to_dev(port)->name);
		अगर (rx_status == NET_RX_DROP)
			dev->stats.rx_dropped++;
	पूर्ण अन्यथा अणु
		card->dma_skb_rx = skb;
		card->dma_port_rx = port;
		card->dma_len_rx = len;
		card->dma_rxpos = rxp;
		fst_rx_dma(card, card->rx_dma_handle_card,
			   BUF_OFFSET(rxBuffer[pi][rxp][0]), len);
	पूर्ण
	अगर (rxp != port->rxpos) अणु
		dbg(DBG_ASS, "About to increment rxpos by more than 1\n");
		dbg(DBG_ASS, "rxp = %d rxpos = %d\n", rxp, port->rxpos);
	पूर्ण
	rxp = (rxp+1) % NUM_RX_BUFFER;
	port->rxpos = rxp;
पूर्ण

/*
 *      The bottom halfs to the ISR
 *
 */

अटल व्योम
करो_bottom_half_tx(काष्ठा fst_card_info *card)
अणु
	काष्ठा fst_port_info *port;
	पूर्णांक pi;
	पूर्णांक txq_length;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	काष्ठा net_device *dev;

	/*
	 *  Find a मुक्त buffer क्रम the transmit
	 *  Step through each port on this card
	 */

	dbg(DBG_TX, "do_bottom_half_tx\n");
	क्रम (pi = 0, port = card->ports; pi < card->nports; pi++, port++) अणु
		अगर (!port->run)
			जारी;

		dev = port_to_dev(port);
		जबतक (!(FST_RDB(card, txDescrRing[pi][port->txpos].bits) &
			 DMA_OWN) &&
		       !(card->dmatx_in_progress)) अणु
			/*
			 * There करोesn't seem to be a txकरोne event per-se
			 * We seem to have to deduce it, by checking the DMA_OWN
			 * bit on the next buffer we think we can use
			 */
			spin_lock_irqsave(&card->card_lock, flags);
			अगर ((txq_length = port->txqe - port->txqs) < 0) अणु
				/*
				 * This is the हाल where one has wrapped and the
				 * maths gives us a negative number
				 */
				txq_length = txq_length + FST_TXQ_DEPTH;
			पूर्ण
			spin_unlock_irqrestore(&card->card_lock, flags);
			अगर (txq_length > 0) अणु
				/*
				 * There is something to send
				 */
				spin_lock_irqsave(&card->card_lock, flags);
				skb = port->txq[port->txqs];
				port->txqs++;
				अगर (port->txqs == FST_TXQ_DEPTH) अणु
					port->txqs = 0;
				पूर्ण
				spin_unlock_irqrestore(&card->card_lock, flags);
				/*
				 * copy the data and set the required indicators on the
				 * card.
				 */
				FST_WRW(card, txDescrRing[pi][port->txpos].bcnt,
					cnv_bcnt(skb->len));
				अगर ((skb->len < FST_MIN_DMA_LEN) ||
				    (card->family == FST_FAMILY_TXP)) अणु
					/* Enqueue the packet with normal io */
					स_नकल_toio(card->mem +
						    BUF_OFFSET(txBuffer[pi]
							       [port->
								txpos][0]),
						    skb->data, skb->len);
					FST_WRB(card,
						txDescrRing[pi][port->txpos].
						bits,
						DMA_OWN | TX_STP | TX_ENP);
					dev->stats.tx_packets++;
					dev->stats.tx_bytes += skb->len;
					netअगर_trans_update(dev);
				पूर्ण अन्यथा अणु
					/* Or करो it through dma */
					स_नकल(card->tx_dma_handle_host,
					       skb->data, skb->len);
					card->dma_port_tx = port;
					card->dma_len_tx = skb->len;
					card->dma_txpos = port->txpos;
					fst_tx_dma(card,
						   card->tx_dma_handle_card,
						   BUF_OFFSET(txBuffer[pi]
							      [port->txpos][0]),
						   skb->len);
				पूर्ण
				अगर (++port->txpos >= NUM_TX_BUFFER)
					port->txpos = 0;
				/*
				 * If we have flow control on, can we now release it?
				 */
				अगर (port->start) अणु
					अगर (txq_length < fst_txq_low) अणु
						netअगर_wake_queue(port_to_dev
								 (port));
						port->start = 0;
					पूर्ण
				पूर्ण
				dev_kमुक्त_skb(skb);
			पूर्ण अन्यथा अणु
				/*
				 * Nothing to send so अवरोध out of the जबतक loop
				 */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
करो_bottom_half_rx(काष्ठा fst_card_info *card)
अणु
	काष्ठा fst_port_info *port;
	पूर्णांक pi;
	पूर्णांक rx_count = 0;

	/* Check क्रम rx completions on all ports on this card */
	dbg(DBG_RX, "do_bottom_half_rx\n");
	क्रम (pi = 0, port = card->ports; pi < card->nports; pi++, port++) अणु
		अगर (!port->run)
			जारी;

		जबतक (!(FST_RDB(card, rxDescrRing[pi][port->rxpos].bits)
			 & DMA_OWN) && !(card->dmarx_in_progress)) अणु
			अगर (rx_count > fst_max_पढ़ोs) अणु
				/*
				 * Don't spend क्रमever in receive processing
				 * Schedule another event
				 */
				fst_q_work_item(&fst_work_पूर्णांकq, card->card_no);
				tasklet_schedule(&fst_पूर्णांक_task);
				अवरोध;	/* Leave the loop */
			पूर्ण
			fst_पूर्णांकr_rx(card, port);
			rx_count++;
		पूर्ण
	पूर्ण
पूर्ण

/*
 *      The पूर्णांकerrupt service routine
 *      Dev_id is our fst_card_info poपूर्णांकer
 */
अटल irqवापस_t
fst_पूर्णांकr(पूर्णांक dummy, व्योम *dev_id)
अणु
	काष्ठा fst_card_info *card = dev_id;
	काष्ठा fst_port_info *port;
	पूर्णांक rdidx;		/* Event buffer indices */
	पूर्णांक wridx;
	पूर्णांक event;		/* Actual event क्रम processing */
	अचिन्हित पूर्णांक dma_पूर्णांकcsr = 0;
	अचिन्हित पूर्णांक करो_card_पूर्णांकerrupt;
	अचिन्हित पूर्णांक पूर्णांक_retry_count;

	/*
	 * Check to see अगर the पूर्णांकerrupt was क्रम this card
	 * वापस अगर not
	 * Note that the call to clear the पूर्णांकerrupt is important
	 */
	dbg(DBG_INTR, "intr: %d %p\n", card->irq, card);
	अगर (card->state != FST_RUNNING) अणु
		pr_err("Interrupt received for card %d in a non running state (%d)\n",
		       card->card_no, card->state);

		/* 
		 * It is possible to really be running, i.e. we have re-loaded
		 * a running card
		 * Clear and reprime the पूर्णांकerrupt source 
		 */
		fst_clear_पूर्णांकr(card);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Clear and reprime the पूर्णांकerrupt source */
	fst_clear_पूर्णांकr(card);

	/*
	 * Is the पूर्णांकerrupt क्रम this card (handshake == 1)
	 */
	करो_card_पूर्णांकerrupt = 0;
	अगर (FST_RDB(card, पूर्णांकerruptHandshake) == 1) अणु
		करो_card_पूर्णांकerrupt += FST_CARD_INT;
		/* Set the software acknowledge */
		FST_WRB(card, पूर्णांकerruptHandshake, 0xEE);
	पूर्ण
	अगर (card->family == FST_FAMILY_TXU) अणु
		/*
		 * Is it a DMA Interrupt
		 */
		dma_पूर्णांकcsr = inl(card->pci_conf + INTCSR_9054);
		अगर (dma_पूर्णांकcsr & 0x00200000) अणु
			/*
			 * DMA Channel 0 (Rx transfer complete)
			 */
			dbg(DBG_RX, "DMA Rx xfer complete\n");
			outb(0x8, card->pci_conf + DMACSR0);
			fst_rx_dma_complete(card, card->dma_port_rx,
					    card->dma_len_rx, card->dma_skb_rx,
					    card->dma_rxpos);
			card->dmarx_in_progress = 0;
			करो_card_पूर्णांकerrupt += FST_RX_DMA_INT;
		पूर्ण
		अगर (dma_पूर्णांकcsr & 0x00400000) अणु
			/*
			 * DMA Channel 1 (Tx transfer complete)
			 */
			dbg(DBG_TX, "DMA Tx xfer complete\n");
			outb(0x8, card->pci_conf + DMACSR1);
			fst_tx_dma_complete(card, card->dma_port_tx,
					    card->dma_len_tx, card->dma_txpos);
			card->dmatx_in_progress = 0;
			करो_card_पूर्णांकerrupt += FST_TX_DMA_INT;
		पूर्ण
	पूर्ण

	/*
	 * Have we been missing Interrupts
	 */
	पूर्णांक_retry_count = FST_RDL(card, पूर्णांकerruptRetryCount);
	अगर (पूर्णांक_retry_count) अणु
		dbg(DBG_ASS, "Card %d int_retry_count is  %d\n",
		    card->card_no, पूर्णांक_retry_count);
		FST_WRL(card, पूर्णांकerruptRetryCount, 0);
	पूर्ण

	अगर (!करो_card_पूर्णांकerrupt) अणु
		वापस IRQ_HANDLED;
	पूर्ण

	/* Scehdule the bottom half of the ISR */
	fst_q_work_item(&fst_work_पूर्णांकq, card->card_no);
	tasklet_schedule(&fst_पूर्णांक_task);

	/* Drain the event queue */
	rdidx = FST_RDB(card, पूर्णांकerruptEvent.rdindex) & 0x1f;
	wridx = FST_RDB(card, पूर्णांकerruptEvent.wrindex) & 0x1f;
	जबतक (rdidx != wridx) अणु
		event = FST_RDB(card, पूर्णांकerruptEvent.evntbuff[rdidx]);
		port = &card->ports[event & 0x03];

		dbg(DBG_INTR, "Processing Interrupt event: %x\n", event);

		चयन (event) अणु
		हाल TE1_ALMA:
			dbg(DBG_INTR, "TE1 Alarm intr\n");
			अगर (port->run)
				fst_पूर्णांकr_te1_alarm(card, port);
			अवरोध;

		हाल CTLA_CHG:
		हाल CTLB_CHG:
		हाल CTLC_CHG:
		हाल CTLD_CHG:
			अगर (port->run)
				fst_पूर्णांकr_ctlchg(card, port);
			अवरोध;

		हाल ABTA_SENT:
		हाल ABTB_SENT:
		हाल ABTC_SENT:
		हाल ABTD_SENT:
			dbg(DBG_TX, "Abort complete port %d\n", port->index);
			अवरोध;

		हाल TXA_UNDF:
		हाल TXB_UNDF:
		हाल TXC_UNDF:
		हाल TXD_UNDF:
			/* Dअगरficult to see how we'd get this given that we
			 * always load up the entire packet क्रम DMA.
			 */
			dbg(DBG_TX, "Tx underflow port %d\n", port->index);
			port_to_dev(port)->stats.tx_errors++;
			port_to_dev(port)->stats.tx_fअगरo_errors++;
			dbg(DBG_ASS, "Tx underflow on card %d port %d\n",
			    card->card_no, port->index);
			अवरोध;

		हाल INIT_CPLT:
			dbg(DBG_INIT, "Card init OK intr\n");
			अवरोध;

		हाल INIT_FAIL:
			dbg(DBG_INIT, "Card init FAILED intr\n");
			card->state = FST_IFAILED;
			अवरोध;

		शेष:
			pr_err("intr: unknown card event %d. ignored\n", event);
			अवरोध;
		पूर्ण

		/* Bump and wrap the index */
		अगर (++rdidx >= MAX_CIRBUFF)
			rdidx = 0;
	पूर्ण
	FST_WRB(card, पूर्णांकerruptEvent.rdindex, rdidx);
        वापस IRQ_HANDLED;
पूर्ण

/*      Check that the shared memory configuration is one that we can handle
 *      and that some basic parameters are correct
 */
अटल व्योम
check_started_ok(काष्ठा fst_card_info *card)
अणु
	पूर्णांक i;

	/* Check काष्ठाure version and end marker */
	अगर (FST_RDW(card, smcVersion) != SMC_VERSION) अणु
		pr_err("Bad shared memory version %d expected %d\n",
		       FST_RDW(card, smcVersion), SMC_VERSION);
		card->state = FST_BADVERSION;
		वापस;
	पूर्ण
	अगर (FST_RDL(card, endOfSmcSignature) != END_SIG) अणु
		pr_err("Missing shared memory signature\n");
		card->state = FST_BADVERSION;
		वापस;
	पूर्ण
	/* Firmware status flag, 0x00 = initialising, 0x01 = OK, 0xFF = fail */
	अगर ((i = FST_RDB(card, taskStatus)) == 0x01) अणु
		card->state = FST_RUNNING;
	पूर्ण अन्यथा अगर (i == 0xFF) अणु
		pr_err("Firmware initialisation failed. Card halted\n");
		card->state = FST_HALTED;
		वापस;
	पूर्ण अन्यथा अगर (i != 0x00) अणु
		pr_err("Unknown firmware status 0x%x\n", i);
		card->state = FST_HALTED;
		वापस;
	पूर्ण

	/* Finally check the number of ports reported by firmware against the
	 * number we assumed at card detection. Should never happen with
	 * existing firmware etc so we just report it क्रम the moment.
	 */
	अगर (FST_RDL(card, numberOfPorts) != card->nports) अणु
		pr_warn("Port count mismatch on card %d.  Firmware thinks %d we say %d\n",
			card->card_no,
			FST_RDL(card, numberOfPorts), card->nports);
	पूर्ण
पूर्ण

अटल पूर्णांक
set_conf_from_info(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port,
		   काष्ठा fstioc_info *info)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर my_framing;

	/* Set things according to the user set valid flags 
	 * Several of the old options have been invalidated/replaced by the 
	 * generic hdlc package.
	 */
	err = 0;
	अगर (info->valid & FSTVAL_PROTO) अणु
		अगर (info->proto == FST_RAW)
			port->mode = FST_RAW;
		अन्यथा
			port->mode = FST_GEN_HDLC;
	पूर्ण

	अगर (info->valid & FSTVAL_CABLE)
		err = -EINVAL;

	अगर (info->valid & FSTVAL_SPEED)
		err = -EINVAL;

	अगर (info->valid & FSTVAL_PHASE)
		FST_WRB(card, portConfig[port->index].invertClock,
			info->invertClock);
	अगर (info->valid & FSTVAL_MODE)
		FST_WRW(card, cardMode, info->cardMode);
	अगर (info->valid & FSTVAL_TE1) अणु
		FST_WRL(card, suConfig.dataRate, info->lineSpeed);
		FST_WRB(card, suConfig.घड़ीing, info->घड़ीSource);
		my_framing = FRAMING_E1;
		अगर (info->framing == E1)
			my_framing = FRAMING_E1;
		अगर (info->framing == T1)
			my_framing = FRAMING_T1;
		अगर (info->framing == J1)
			my_framing = FRAMING_J1;
		FST_WRB(card, suConfig.framing, my_framing);
		FST_WRB(card, suConfig.काष्ठाure, info->काष्ठाure);
		FST_WRB(card, suConfig.पूर्णांकerface, info->पूर्णांकerface);
		FST_WRB(card, suConfig.coding, info->coding);
		FST_WRB(card, suConfig.lineBuildOut, info->lineBuildOut);
		FST_WRB(card, suConfig.equalizer, info->equalizer);
		FST_WRB(card, suConfig.transparentMode, info->transparentMode);
		FST_WRB(card, suConfig.loopMode, info->loopMode);
		FST_WRB(card, suConfig.range, info->range);
		FST_WRB(card, suConfig.txBufferMode, info->txBufferMode);
		FST_WRB(card, suConfig.rxBufferMode, info->rxBufferMode);
		FST_WRB(card, suConfig.startingSlot, info->startingSlot);
		FST_WRB(card, suConfig.losThreshold, info->losThreshold);
		अगर (info->idleCode)
			FST_WRB(card, suConfig.enableIdleCode, 1);
		अन्यथा
			FST_WRB(card, suConfig.enableIdleCode, 0);
		FST_WRB(card, suConfig.idleCode, info->idleCode);
#अगर FST_DEBUG
		अगर (info->valid & FSTVAL_TE1) अणु
			prपूर्णांकk("Setting TE1 data\n");
			prपूर्णांकk("Line Speed = %d\n", info->lineSpeed);
			prपूर्णांकk("Start slot = %d\n", info->startingSlot);
			prपूर्णांकk("Clock source = %d\n", info->घड़ीSource);
			prपूर्णांकk("Framing = %d\n", my_framing);
			prपूर्णांकk("Structure = %d\n", info->काष्ठाure);
			prपूर्णांकk("interface = %d\n", info->पूर्णांकerface);
			prपूर्णांकk("Coding = %d\n", info->coding);
			prपूर्णांकk("Line build out = %d\n", info->lineBuildOut);
			prपूर्णांकk("Equaliser = %d\n", info->equalizer);
			prपूर्णांकk("Transparent mode = %d\n",
			       info->transparentMode);
			prपूर्णांकk("Loop mode = %d\n", info->loopMode);
			prपूर्णांकk("Range = %d\n", info->range);
			prपूर्णांकk("Tx Buffer mode = %d\n", info->txBufferMode);
			prपूर्णांकk("Rx Buffer mode = %d\n", info->rxBufferMode);
			prपूर्णांकk("LOS Threshold = %d\n", info->losThreshold);
			prपूर्णांकk("Idle Code = %d\n", info->idleCode);
		पूर्ण
#पूर्ण_अगर
	पूर्ण
#अगर FST_DEBUG
	अगर (info->valid & FSTVAL_DEBUG) अणु
		fst_debug_mask = info->debug;
	पूर्ण
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल व्योम
gather_conf_info(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port,
		 काष्ठा fstioc_info *info)
अणु
	पूर्णांक i;

	स_रखो(info, 0, माप (काष्ठा fstioc_info));

	i = port->index;
	info->kernelVersion = LINUX_VERSION_CODE;
	info->nports = card->nports;
	info->type = card->type;
	info->state = card->state;
	info->proto = FST_GEN_HDLC;
	info->index = i;
#अगर FST_DEBUG
	info->debug = fst_debug_mask;
#पूर्ण_अगर

	/* Only mark inक्रमmation as valid अगर card is running.
	 * Copy the data anyway in हाल it is useful क्रम diagnostics
	 */
	info->valid = ((card->state == FST_RUNNING) ? FSTVAL_ALL : FSTVAL_CARD)
#अगर FST_DEBUG
	    | FSTVAL_DEBUG
#पूर्ण_अगर
	    ;

	info->lineInterface = FST_RDW(card, portConfig[i].lineInterface);
	info->पूर्णांकernalClock = FST_RDB(card, portConfig[i].पूर्णांकernalClock);
	info->lineSpeed = FST_RDL(card, portConfig[i].lineSpeed);
	info->invertClock = FST_RDB(card, portConfig[i].invertClock);
	info->v24IpSts = FST_RDL(card, v24IpSts[i]);
	info->v24OpSts = FST_RDL(card, v24OpSts[i]);
	info->घड़ीStatus = FST_RDW(card, घड़ीStatus[i]);
	info->cableStatus = FST_RDW(card, cableStatus);
	info->cardMode = FST_RDW(card, cardMode);
	info->smcFirmwareVersion = FST_RDL(card, smcFirmwareVersion);

	/*
	 * The T2U can report cable presence क्रम both A or B
	 * in bits 0 and 1 of cableStatus.  See which port we are and 
	 * करो the mapping.
	 */
	अगर (card->family == FST_FAMILY_TXU) अणु
		अगर (port->index == 0) अणु
			/*
			 * Port A
			 */
			info->cableStatus = info->cableStatus & 1;
		पूर्ण अन्यथा अणु
			/*
			 * Port B
			 */
			info->cableStatus = info->cableStatus >> 1;
			info->cableStatus = info->cableStatus & 1;
		पूर्ण
	पूर्ण
	/*
	 * Some additional bits अगर we are TE1
	 */
	अगर (card->type == FST_TYPE_TE1) अणु
		info->lineSpeed = FST_RDL(card, suConfig.dataRate);
		info->घड़ीSource = FST_RDB(card, suConfig.घड़ीing);
		info->framing = FST_RDB(card, suConfig.framing);
		info->काष्ठाure = FST_RDB(card, suConfig.काष्ठाure);
		info->पूर्णांकerface = FST_RDB(card, suConfig.पूर्णांकerface);
		info->coding = FST_RDB(card, suConfig.coding);
		info->lineBuildOut = FST_RDB(card, suConfig.lineBuildOut);
		info->equalizer = FST_RDB(card, suConfig.equalizer);
		info->loopMode = FST_RDB(card, suConfig.loopMode);
		info->range = FST_RDB(card, suConfig.range);
		info->txBufferMode = FST_RDB(card, suConfig.txBufferMode);
		info->rxBufferMode = FST_RDB(card, suConfig.rxBufferMode);
		info->startingSlot = FST_RDB(card, suConfig.startingSlot);
		info->losThreshold = FST_RDB(card, suConfig.losThreshold);
		अगर (FST_RDB(card, suConfig.enableIdleCode))
			info->idleCode = FST_RDB(card, suConfig.idleCode);
		अन्यथा
			info->idleCode = 0;
		info->receiveBufferDelay =
		    FST_RDL(card, suStatus.receiveBufferDelay);
		info->framingErrorCount =
		    FST_RDL(card, suStatus.framingErrorCount);
		info->codeViolationCount =
		    FST_RDL(card, suStatus.codeViolationCount);
		info->crcErrorCount = FST_RDL(card, suStatus.crcErrorCount);
		info->lineAttenuation = FST_RDL(card, suStatus.lineAttenuation);
		info->lossOfSignal = FST_RDB(card, suStatus.lossOfSignal);
		info->receiveRemoteAlarm =
		    FST_RDB(card, suStatus.receiveRemoteAlarm);
		info->alarmIndicationSignal =
		    FST_RDB(card, suStatus.alarmIndicationSignal);
	पूर्ण
पूर्ण

अटल पूर्णांक
fst_set_अगरace(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port,
	      काष्ठा अगरreq *अगरr)
अणु
	sync_serial_settings sync;
	पूर्णांक i;

	अगर (अगरr->अगरr_settings.size != माप (sync)) अणु
		वापस -ENOMEM;
	पूर्ण

	अगर (copy_from_user
	    (&sync, अगरr->अगरr_settings.अगरs_अगरsu.sync, माप (sync))) अणु
		वापस -EFAULT;
	पूर्ण

	अगर (sync.loopback)
		वापस -EINVAL;

	i = port->index;

	चयन (अगरr->अगरr_settings.type) अणु
	हाल IF_IFACE_V35:
		FST_WRW(card, portConfig[i].lineInterface, V35);
		port->hwअगर = V35;
		अवरोध;

	हाल IF_IFACE_V24:
		FST_WRW(card, portConfig[i].lineInterface, V24);
		port->hwअगर = V24;
		अवरोध;

	हाल IF_IFACE_X21:
		FST_WRW(card, portConfig[i].lineInterface, X21);
		port->hwअगर = X21;
		अवरोध;

	हाल IF_IFACE_X21D:
		FST_WRW(card, portConfig[i].lineInterface, X21D);
		port->hwअगर = X21D;
		अवरोध;

	हाल IF_IFACE_T1:
		FST_WRW(card, portConfig[i].lineInterface, T1);
		port->hwअगर = T1;
		अवरोध;

	हाल IF_IFACE_E1:
		FST_WRW(card, portConfig[i].lineInterface, E1);
		port->hwअगर = E1;
		अवरोध;

	हाल IF_IFACE_SYNC_SERIAL:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (sync.घड़ी_प्रकारype) अणु
	हाल CLOCK_EXT:
		FST_WRB(card, portConfig[i].पूर्णांकernalClock, EXTCLK);
		अवरोध;

	हाल CLOCK_INT:
		FST_WRB(card, portConfig[i].पूर्णांकernalClock, INTCLK);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	FST_WRL(card, portConfig[i].lineSpeed, sync.घड़ी_rate);
	वापस 0;
पूर्ण

अटल पूर्णांक
fst_get_अगरace(काष्ठा fst_card_info *card, काष्ठा fst_port_info *port,
	      काष्ठा अगरreq *अगरr)
अणु
	sync_serial_settings sync;
	पूर्णांक i;

	/* First check what line type is set, we'll शेष to reporting X.21
	 * अगर nothing is set as IF_IFACE_SYNC_SERIAL implies it can't be
	 * changed
	 */
	चयन (port->hwअगर) अणु
	हाल E1:
		अगरr->अगरr_settings.type = IF_IFACE_E1;
		अवरोध;
	हाल T1:
		अगरr->अगरr_settings.type = IF_IFACE_T1;
		अवरोध;
	हाल V35:
		अगरr->अगरr_settings.type = IF_IFACE_V35;
		अवरोध;
	हाल V24:
		अगरr->अगरr_settings.type = IF_IFACE_V24;
		अवरोध;
	हाल X21D:
		अगरr->अगरr_settings.type = IF_IFACE_X21D;
		अवरोध;
	हाल X21:
	शेष:
		अगरr->अगरr_settings.type = IF_IFACE_X21;
		अवरोध;
	पूर्ण
	अगर (अगरr->अगरr_settings.size == 0) अणु
		वापस 0;	/* only type requested */
	पूर्ण
	अगर (अगरr->अगरr_settings.size < माप (sync)) अणु
		वापस -ENOMEM;
	पूर्ण

	i = port->index;
	स_रखो(&sync, 0, माप(sync));
	sync.घड़ी_rate = FST_RDL(card, portConfig[i].lineSpeed);
	/* Lucky card and linux use same encoding here */
	sync.घड़ी_प्रकारype = FST_RDB(card, portConfig[i].पूर्णांकernalClock) ==
	    INTCLK ? CLOCK_INT : CLOCK_EXT;
	sync.loopback = 0;

	अगर (copy_to_user(अगरr->अगरr_settings.अगरs_अगरsu.sync, &sync, माप (sync))) अणु
		वापस -EFAULT;
	पूर्ण

	अगरr->अगरr_settings.size = माप (sync);
	वापस 0;
पूर्ण

अटल पूर्णांक
fst_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा fst_card_info *card;
	काष्ठा fst_port_info *port;
	काष्ठा fstioc_ग_लिखो wrthdr;
	काष्ठा fstioc_info info;
	अचिन्हित दीर्घ flags;
	व्योम *buf;

	dbg(DBG_IOCTL, "ioctl: %x, %p\n", cmd, अगरr->अगरr_data);

	port = dev_to_port(dev);
	card = port->card;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल FSTCPURESET:
		fst_cpureset(card);
		card->state = FST_RESET;
		वापस 0;

	हाल FSTCPURELEASE:
		fst_cpurelease(card);
		card->state = FST_STARTING;
		वापस 0;

	हाल FSTWRITE:		/* Code ग_लिखो (करोwnload) */

		/* First copy in the header with the length and offset of data
		 * to ग_लिखो
		 */
		अगर (अगरr->अगरr_data == शून्य) अणु
			वापस -EINVAL;
		पूर्ण
		अगर (copy_from_user(&wrthdr, अगरr->अगरr_data,
				   माप (काष्ठा fstioc_ग_लिखो))) अणु
			वापस -EFAULT;
		पूर्ण

		/* Sanity check the parameters. We करोn't support partial ग_लिखोs
		 * when going over the top
		 */
		अगर (wrthdr.size > FST_MEMSIZE || wrthdr.offset > FST_MEMSIZE ||
		    wrthdr.size + wrthdr.offset > FST_MEMSIZE) अणु
			वापस -ENXIO;
		पूर्ण

		/* Now copy the data to the card. */

		buf = memdup_user(अगरr->अगरr_data + माप(काष्ठा fstioc_ग_लिखो),
				  wrthdr.size);
		अगर (IS_ERR(buf))
			वापस PTR_ERR(buf);

		स_नकल_toio(card->mem + wrthdr.offset, buf, wrthdr.size);
		kमुक्त(buf);

		/* Writes to the memory of a card in the reset state स्थिरitute
		 * a करोwnload
		 */
		अगर (card->state == FST_RESET) अणु
			card->state = FST_DOWNLOAD;
		पूर्ण
		वापस 0;

	हाल FSTGETCONF:

		/* If card has just been started check the shared memory config
		 * version and marker
		 */
		अगर (card->state == FST_STARTING) अणु
			check_started_ok(card);

			/* If everything checked out enable card पूर्णांकerrupts */
			अगर (card->state == FST_RUNNING) अणु
				spin_lock_irqsave(&card->card_lock, flags);
				fst_enable_पूर्णांकr(card);
				FST_WRB(card, पूर्णांकerruptHandshake, 0xEE);
				spin_unlock_irqrestore(&card->card_lock, flags);
			पूर्ण
		पूर्ण

		अगर (अगरr->अगरr_data == शून्य) अणु
			वापस -EINVAL;
		पूर्ण

		gather_conf_info(card, port, &info);

		अगर (copy_to_user(अगरr->अगरr_data, &info, माप (info))) अणु
			वापस -EFAULT;
		पूर्ण
		वापस 0;

	हाल FSTSETCONF:

		/*
		 * Most of the settings have been moved to the generic ioctls
		 * this just covers debug and board ident now
		 */

		अगर (card->state != FST_RUNNING) अणु
			pr_err("Attempt to configure card %d in non-running state (%d)\n",
			       card->card_no, card->state);
			वापस -EIO;
		पूर्ण
		अगर (copy_from_user(&info, अगरr->अगरr_data, माप (info))) अणु
			वापस -EFAULT;
		पूर्ण

		वापस set_conf_from_info(card, port, &info);

	हाल SIOCWANDEV:
		चयन (अगरr->अगरr_settings.type) अणु
		हाल IF_GET_IFACE:
			वापस fst_get_अगरace(card, port, अगरr);

		हाल IF_IFACE_SYNC_SERIAL:
		हाल IF_IFACE_V35:
		हाल IF_IFACE_V24:
		हाल IF_IFACE_X21:
		हाल IF_IFACE_X21D:
		हाल IF_IFACE_T1:
		हाल IF_IFACE_E1:
			वापस fst_set_अगरace(card, port, अगरr);

		हाल IF_PROTO_RAW:
			port->mode = FST_RAW;
			वापस 0;

		हाल IF_GET_PROTO:
			अगर (port->mode == FST_RAW) अणु
				अगरr->अगरr_settings.type = IF_PROTO_RAW;
				वापस 0;
			पूर्ण
			वापस hdlc_ioctl(dev, अगरr, cmd);

		शेष:
			port->mode = FST_GEN_HDLC;
			dbg(DBG_IOCTL, "Passing this type to hdlc %x\n",
			    अगरr->अगरr_settings.type);
			वापस hdlc_ioctl(dev, अगरr, cmd);
		पूर्ण

	शेष:
		/* Not one of ours. Pass through to HDLC package */
		वापस hdlc_ioctl(dev, अगरr, cmd);
	पूर्ण
पूर्ण

अटल व्योम
fst_खोलोport(काष्ठा fst_port_info *port)
अणु
	पूर्णांक संकेतs;

	/* Only init things अगर card is actually running. This allows खोलो to
	 * succeed क्रम करोwnloads etc.
	 */
	अगर (port->card->state == FST_RUNNING) अणु
		अगर (port->run) अणु
			dbg(DBG_OPEN, "open: found port already running\n");

			fst_issue_cmd(port, STOPPORT);
			port->run = 0;
		पूर्ण

		fst_rx_config(port);
		fst_tx_config(port);
		fst_op_उठाओ(port, OPSTS_RTS | OPSTS_DTR);

		fst_issue_cmd(port, STARTPORT);
		port->run = 1;

		संकेतs = FST_RDL(port->card, v24DebouncedSts[port->index]);
		अगर (संकेतs & (((port->hwअगर == X21) || (port->hwअगर == X21D))
			       ? IPSTS_INDICATE : IPSTS_DCD))
			netअगर_carrier_on(port_to_dev(port));
		अन्यथा
			netअगर_carrier_off(port_to_dev(port));

		port->txqe = 0;
		port->txqs = 0;
	पूर्ण

पूर्ण

अटल व्योम
fst_बंदport(काष्ठा fst_port_info *port)
अणु
	अगर (port->card->state == FST_RUNNING) अणु
		अगर (port->run) अणु
			port->run = 0;
			fst_op_lower(port, OPSTS_RTS | OPSTS_DTR);

			fst_issue_cmd(port, STOPPORT);
		पूर्ण अन्यथा अणु
			dbg(DBG_OPEN, "close: port not running\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
fst_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक err;
	काष्ठा fst_port_info *port;

	port = dev_to_port(dev);
	अगर (!try_module_get(THIS_MODULE))
          वापस -EBUSY;

	अगर (port->mode != FST_RAW) अणु
		err = hdlc_खोलो(dev);
		अगर (err) अणु
			module_put(THIS_MODULE);
			वापस err;
		पूर्ण
	पूर्ण

	fst_खोलोport(port);
	netअगर_wake_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक
fst_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा fst_port_info *port;
	काष्ठा fst_card_info *card;
	अचिन्हित अक्षर tx_dma_करोne;
	अचिन्हित अक्षर rx_dma_करोne;

	port = dev_to_port(dev);
	card = port->card;

	tx_dma_करोne = inb(card->pci_conf + DMACSR1);
	rx_dma_करोne = inb(card->pci_conf + DMACSR0);
	dbg(DBG_OPEN,
	    "Port Close: tx_dma_in_progress = %d (%x) rx_dma_in_progress = %d (%x)\n",
	    card->dmatx_in_progress, tx_dma_करोne, card->dmarx_in_progress,
	    rx_dma_करोne);

	netअगर_stop_queue(dev);
	fst_बंदport(dev_to_port(dev));
	अगर (port->mode != FST_RAW) अणु
		hdlc_बंद(dev);
	पूर्ण
	module_put(THIS_MODULE);
	वापस 0;
पूर्ण

अटल पूर्णांक
fst_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding, अचिन्हित लघु parity)
अणु
	/*
	 * Setting currently fixed in FarSync card so we check and क्रमget
	 */
	अगर (encoding != ENCODING_NRZ || parity != PARITY_CRC16_PR1_CCITT)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम
fst_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा fst_port_info *port;
	काष्ठा fst_card_info *card;

	port = dev_to_port(dev);
	card = port->card;
	dev->stats.tx_errors++;
	dev->stats.tx_पातed_errors++;
	dbg(DBG_ASS, "Tx timeout card %d port %d\n",
	    card->card_no, port->index);
	fst_issue_cmd(port, ABORTTX);

	netअगर_trans_update(dev);
	netअगर_wake_queue(dev);
	port->start = 0;
पूर्ण

अटल netdev_tx_t
fst_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा fst_card_info *card;
	काष्ठा fst_port_info *port;
	अचिन्हित दीर्घ flags;
	पूर्णांक txq_length;

	port = dev_to_port(dev);
	card = port->card;
	dbg(DBG_TX, "fst_start_xmit: length = %d\n", skb->len);

	/* Drop packet with error अगर we करोn't have carrier */
	अगर (!netअगर_carrier_ok(dev)) अणु
		dev_kमुक्त_skb(skb);
		dev->stats.tx_errors++;
		dev->stats.tx_carrier_errors++;
		dbg(DBG_ASS,
		    "Tried to transmit but no carrier on card %d port %d\n",
		    card->card_no, port->index);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Drop it अगर it's too big! MTU failure ? */
	अगर (skb->len > LEN_TX_BUFFER) अणु
		dbg(DBG_ASS, "Packet too large %d vs %d\n", skb->len,
		    LEN_TX_BUFFER);
		dev_kमुक्त_skb(skb);
		dev->stats.tx_errors++;
		वापस NETDEV_TX_OK;
	पूर्ण

	/*
	 * We are always going to queue the packet
	 * so that the bottom half is the only place we tx from
	 * Check there is room in the port txq
	 */
	spin_lock_irqsave(&card->card_lock, flags);
	अगर ((txq_length = port->txqe - port->txqs) < 0) अणु
		/*
		 * This is the हाल where the next मुक्त has wrapped but the
		 * last used hasn't
		 */
		txq_length = txq_length + FST_TXQ_DEPTH;
	पूर्ण
	spin_unlock_irqrestore(&card->card_lock, flags);
	अगर (txq_length > fst_txq_high) अणु
		/*
		 * We have got enough buffers in the pipeline.  Ask the network
		 * layer to stop sending frames करोwn
		 */
		netअगर_stop_queue(dev);
		port->start = 1;	/* I'm using this to संकेत stop sent up */
	पूर्ण

	अगर (txq_length == FST_TXQ_DEPTH - 1) अणु
		/*
		 * This shouldn't have happened but such is lअगरe
		 */
		dev_kमुक्त_skb(skb);
		dev->stats.tx_errors++;
		dbg(DBG_ASS, "Tx queue overflow card %d port %d\n",
		    card->card_no, port->index);
		वापस NETDEV_TX_OK;
	पूर्ण

	/*
	 * queue the buffer
	 */
	spin_lock_irqsave(&card->card_lock, flags);
	port->txq[port->txqe] = skb;
	port->txqe++;
	अगर (port->txqe == FST_TXQ_DEPTH)
		port->txqe = 0;
	spin_unlock_irqrestore(&card->card_lock, flags);

	/* Scehdule the bottom half which now करोes transmit processing */
	fst_q_work_item(&fst_work_txq, card->card_no);
	tasklet_schedule(&fst_tx_task);

	वापस NETDEV_TX_OK;
पूर्ण

/*
 *      Card setup having checked hardware resources.
 *      Should be pretty bizarre अगर we get an error here (kernel memory
 *      exhaustion is one possibility). If we करो see a problem we report it
 *      via a prपूर्णांकk and leave the corresponding पूर्णांकerface and all that follow
 *      disabled.
 */
अटल अक्षर *type_strings[] = अणु
	"no hardware",		/* Should never be seen */
	"FarSync T2P",
	"FarSync T4P",
	"FarSync T1U",
	"FarSync T2U",
	"FarSync T4U",
	"FarSync TE1"
पूर्ण;

अटल पूर्णांक
fst_init_card(काष्ठा fst_card_info *card)
अणु
	पूर्णांक i;
	पूर्णांक err;

	/* We're working on a number of ports based on the card ID. If the
	 * firmware detects something dअगरferent later (should never happen)
	 * we'll have to revise it in some way then.
	 */
	क्रम (i = 0; i < card->nports; i++) अणु
		err = रेजिस्टर_hdlc_device(card->ports[i].dev);
		अगर (err < 0) अणु
			pr_err("Cannot register HDLC device for port %d (errno %d)\n",
				i, -err);
			जबतक (i--)
				unरेजिस्टर_hdlc_device(card->ports[i].dev);
			वापस err;
		पूर्ण
	पूर्ण

	pr_info("%s-%s: %s IRQ%d, %d ports\n",
		port_to_dev(&card->ports[0])->name,
		port_to_dev(&card->ports[card->nports - 1])->name,
		type_strings[card->type], card->irq, card->nports);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops fst_ops = अणु
	.nकरो_खोलो       = fst_खोलो,
	.nकरो_stop       = fst_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = fst_ioctl,
	.nकरो_tx_समयout = fst_tx_समयout,
पूर्ण;

/*
 *      Initialise card when detected.
 *      Returns 0 to indicate success, or त्रुटि_सं otherwise.
 */
अटल पूर्णांक
fst_add_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल पूर्णांक no_of_cards_added = 0;
	काष्ठा fst_card_info *card;
	पूर्णांक err = 0;
	पूर्णांक i;

	prपूर्णांकk_once(KERN_INFO
		    pr_fmt("FarSync WAN driver " FST_USER_VERSION
			   " (c) 2001-2004 FarSite Communications Ltd.\n"));
#अगर FST_DEBUG
	dbg(DBG_ASS, "The value of debug mask is %x\n", fst_debug_mask);
#पूर्ण_अगर
	/*
	 * We are going to be clever and allow certain cards not to be
	 * configured.  An exclude list can be provided in /etc/modules.conf
	 */
	अगर (fst_excluded_cards != 0) अणु
		/*
		 * There are cards to exclude
		 *
		 */
		क्रम (i = 0; i < fst_excluded_cards; i++) अणु
			अगर ((pdev->devfn) >> 3 == fst_excluded_list[i]) अणु
				pr_info("FarSync PCI device %d not assigned\n",
					(pdev->devfn) >> 3);
				वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Allocate driver निजी data */
	card = kzalloc(माप(काष्ठा fst_card_info), GFP_KERNEL);
	अगर (card == शून्य)
		वापस -ENOMEM;

	/* Try to enable the device */
	अगर ((err = pci_enable_device(pdev)) != 0) अणु
		pr_err("Failed to enable card. Err %d\n", -err);
		जाओ enable_fail;
	पूर्ण

	अगर ((err = pci_request_regions(pdev, "FarSync")) !=0) अणु
		pr_err("Failed to allocate regions. Err %d\n", -err);
		जाओ regions_fail;
	पूर्ण

	/* Get भव addresses of memory regions */
	card->pci_conf = pci_resource_start(pdev, 1);
	card->phys_mem = pci_resource_start(pdev, 2);
	card->phys_ctlmem = pci_resource_start(pdev, 3);
	अगर ((card->mem = ioremap(card->phys_mem, FST_MEMSIZE)) == शून्य) अणु
		pr_err("Physical memory remap failed\n");
		err = -ENODEV;
		जाओ ioremap_physmem_fail;
	पूर्ण
	अगर ((card->ctlmem = ioremap(card->phys_ctlmem, 0x10)) == शून्य) अणु
		pr_err("Control memory remap failed\n");
		err = -ENODEV;
		जाओ ioremap_ctlmem_fail;
	पूर्ण
	dbg(DBG_PCI, "kernel mem %p, ctlmem %p\n", card->mem, card->ctlmem);

	/* Register the पूर्णांकerrupt handler */
	अगर (request_irq(pdev->irq, fst_पूर्णांकr, IRQF_SHARED, FST_DEV_NAME, card)) अणु
		pr_err("Unable to register interrupt %d\n", card->irq);
		err = -ENODEV;
		जाओ irq_fail;
	पूर्ण

	/* Record info we need */
	card->irq = pdev->irq;
	card->type = ent->driver_data;
	card->family = ((ent->driver_data == FST_TYPE_T2P) ||
			(ent->driver_data == FST_TYPE_T4P))
	    ? FST_FAMILY_TXP : FST_FAMILY_TXU;
	अगर ((ent->driver_data == FST_TYPE_T1U) ||
	    (ent->driver_data == FST_TYPE_TE1))
		card->nports = 1;
	अन्यथा
		card->nports = ((ent->driver_data == FST_TYPE_T2P) ||
				(ent->driver_data == FST_TYPE_T2U)) ? 2 : 4;

	card->state = FST_UNINIT;
        spin_lock_init ( &card->card_lock );

        क्रम ( i = 0 ; i < card->nports ; i++ ) अणु
		काष्ठा net_device *dev = alloc_hdlcdev(&card->ports[i]);
		hdlc_device *hdlc;
		अगर (!dev) अणु
			जबतक (i--)
				मुक्त_netdev(card->ports[i].dev);
			pr_err("FarSync: out of memory\n");
			err = -ENOMEM;
			जाओ hdlcdev_fail;
		पूर्ण
		card->ports[i].dev    = dev;
                card->ports[i].card   = card;
                card->ports[i].index  = i;
                card->ports[i].run    = 0;

		hdlc = dev_to_hdlc(dev);

                /* Fill in the net device info */
		/* Since this is a PCI setup this is purely
		 * inक्रमmational. Give them the buffer addresses
		 * and basic card I/O.
		 */
                dev->mem_start   = card->phys_mem
                                 + BUF_OFFSET ( txBuffer[i][0][0]);
                dev->mem_end     = card->phys_mem
                                 + BUF_OFFSET ( txBuffer[i][NUM_TX_BUFFER - 1][LEN_RX_BUFFER - 1]);
                dev->base_addr   = card->pci_conf;
                dev->irq         = card->irq;

		dev->netdev_ops = &fst_ops;
		dev->tx_queue_len = FST_TX_QUEUE_LEN;
		dev->watchकरोg_समयo = FST_TX_TIMEOUT;
                hdlc->attach = fst_attach;
                hdlc->xmit   = fst_start_xmit;
	पूर्ण

	card->device = pdev;

	dbg(DBG_PCI, "type %d nports %d irq %d\n", card->type,
	    card->nports, card->irq);
	dbg(DBG_PCI, "conf %04x mem %08x ctlmem %08x\n",
	    card->pci_conf, card->phys_mem, card->phys_ctlmem);

	/* Reset the card's processor */
	fst_cpureset(card);
	card->state = FST_RESET;

	/* Initialise DMA (अगर required) */
	fst_init_dma(card);

	/* Record driver data क्रम later use */
	pci_set_drvdata(pdev, card);

	/* Reमुख्यder of card setup */
	अगर (no_of_cards_added >= FST_MAX_CARDS) अणु
		pr_err("FarSync: too many cards\n");
		err = -ENOMEM;
		जाओ card_array_fail;
	पूर्ण
	fst_card_array[no_of_cards_added] = card;
	card->card_no = no_of_cards_added++;	/* Record instance and bump it */
	err = fst_init_card(card);
	अगर (err)
		जाओ init_card_fail;
	अगर (card->family == FST_FAMILY_TXU) अणु
		/*
		 * Allocate a dma buffer क्रम transmit and receives
		 */
		card->rx_dma_handle_host =
		    dma_alloc_coherent(&card->device->dev, FST_MAX_MTU,
				       &card->rx_dma_handle_card, GFP_KERNEL);
		अगर (card->rx_dma_handle_host == शून्य) अणु
			pr_err("Could not allocate rx dma buffer\n");
			err = -ENOMEM;
			जाओ rx_dma_fail;
		पूर्ण
		card->tx_dma_handle_host =
		    dma_alloc_coherent(&card->device->dev, FST_MAX_MTU,
				       &card->tx_dma_handle_card, GFP_KERNEL);
		अगर (card->tx_dma_handle_host == शून्य) अणु
			pr_err("Could not allocate tx dma buffer\n");
			err = -ENOMEM;
			जाओ tx_dma_fail;
		पूर्ण
	पूर्ण
	वापस 0;		/* Success */

tx_dma_fail:
	dma_मुक्त_coherent(&card->device->dev, FST_MAX_MTU,
			  card->rx_dma_handle_host, card->rx_dma_handle_card);
rx_dma_fail:
	fst_disable_पूर्णांकr(card);
	क्रम (i = 0 ; i < card->nports ; i++)
		unरेजिस्टर_hdlc_device(card->ports[i].dev);
init_card_fail:
	fst_card_array[card->card_no] = शून्य;
card_array_fail:
	क्रम (i = 0 ; i < card->nports ; i++)
		मुक्त_netdev(card->ports[i].dev);
hdlcdev_fail:
	मुक्त_irq(card->irq, card);
irq_fail:
	iounmap(card->ctlmem);
ioremap_ctlmem_fail:
	iounmap(card->mem);
ioremap_physmem_fail:
	pci_release_regions(pdev);
regions_fail:
	pci_disable_device(pdev);
enable_fail:
	kमुक्त(card);
	वापस err;
पूर्ण

/*
 *      Cleanup and बंद करोwn a card
 */
अटल व्योम
fst_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fst_card_info *card;
	पूर्णांक i;

	card = pci_get_drvdata(pdev);

	क्रम (i = 0; i < card->nports; i++) अणु
		काष्ठा net_device *dev = port_to_dev(&card->ports[i]);
		unरेजिस्टर_hdlc_device(dev);
	पूर्ण

	fst_disable_पूर्णांकr(card);
	मुक्त_irq(card->irq, card);

	iounmap(card->ctlmem);
	iounmap(card->mem);
	pci_release_regions(pdev);
	अगर (card->family == FST_FAMILY_TXU) अणु
		/*
		 * Free dma buffers
		 */
		dma_मुक्त_coherent(&card->device->dev, FST_MAX_MTU,
				  card->rx_dma_handle_host,
				  card->rx_dma_handle_card);
		dma_मुक्त_coherent(&card->device->dev, FST_MAX_MTU,
				  card->tx_dma_handle_host,
				  card->tx_dma_handle_card);
	पूर्ण
	fst_card_array[card->card_no] = शून्य;
पूर्ण

अटल काष्ठा pci_driver fst_driver = अणु
	.name		= FST_NAME,
	.id_table	= fst_pci_dev_id,
	.probe		= fst_add_one,
	.हटाओ		= fst_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init
fst_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < FST_MAX_CARDS; i++)
		fst_card_array[i] = शून्य;
	वापस pci_रेजिस्टर_driver(&fst_driver);
पूर्ण

अटल व्योम __निकास
fst_cleanup_module(व्योम)
अणु
	pr_info("FarSync WAN driver unloading\n");
	pci_unरेजिस्टर_driver(&fst_driver);
पूर्ण

module_init(fst_init);
module_निकास(fst_cleanup_module);
