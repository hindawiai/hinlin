<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _LMC_VAR_H_
#घोषणा _LMC_VAR_H_

 /*
  * Copyright (c) 1997-2000 LAN Media Corporation (LMC)
  * All rights reserved.  www.lanmedia.com
  *
  * This code is written by:
  * Andrew Stanley-Jones (asj@cban.com)
  * Rob Braun (bbraun@vix.com),
  * Michael Graff (explorer@vix.com) and
  * Matt Thomas (matt@3am-software.com).
  */

#समावेश <linux/समयr.h>

/*
 * basic definitions used in lmc include files
 */

प्रकार काष्ठा lmc___softc lmc_softc_t;
प्रकार काष्ठा lmc___media lmc_media_t;
प्रकार काष्ठा lmc___ctl lmc_ctl_t;

#घोषणा lmc_csrptr_t    अचिन्हित दीर्घ

#घोषणा LMC_REG_RANGE 0x80

#घोषणा LMC_PRINTF_FMT  "%s"
#घोषणा LMC_PRINTF_ARGS	(sc->lmc_device->name)

#घोषणा TX_TIMEOUT (2*HZ)

#घोषणा LMC_TXDESCS            32
#घोषणा LMC_RXDESCS            32

#घोषणा LMC_LINK_UP            1
#घोषणा LMC_LINK_DOWN          0

/* These macros क्रम generic पढ़ो and ग_लिखो to and from the dec chip */
#घोषणा LMC_CSR_READ(sc, csr) \
	inl((sc)->lmc_csrs.csr)
#घोषणा LMC_CSR_WRITE(sc, reg, val) \
	outl((val), (sc)->lmc_csrs.reg)

//#अगर_घोषित _LINUX_DELAY_H
//	#घोषणा SLOW_DOWN_IO udelay(2);
//	#अघोषित __SLOW_DOWN_IO
//	#घोषणा __SLOW_DOWN_IO udelay(2);
//#पूर्ण_अगर

#घोषणा DELAY(n) SLOW_DOWN_IO

#घोषणा lmc_delay() inl(sc->lmc_csrs.csr_9)

/* This macro sync's up with the mii so that पढ़ोs and ग_लिखोs can take place */
#घोषणा LMC_MII_SYNC(sc) करो अणुपूर्णांक n=32; जबतक( n >= 0 ) अणु \
                LMC_CSR_WRITE((sc), csr_9, 0x20000); \
		lmc_delay(); \
		LMC_CSR_WRITE((sc), csr_9, 0x30000); \
                lmc_delay(); \
		n--; पूर्णपूर्ण जबतक(0)

काष्ठा lmc_regfile_t अणु
    lmc_csrptr_t csr_busmode;                  /* CSR0 */
    lmc_csrptr_t csr_txpoll;                   /* CSR1 */
    lmc_csrptr_t csr_rxpoll;                   /* CSR2 */
    lmc_csrptr_t csr_rxlist;                   /* CSR3 */
    lmc_csrptr_t csr_txlist;                   /* CSR4 */
    lmc_csrptr_t csr_status;                   /* CSR5 */
    lmc_csrptr_t csr_command;                  /* CSR6 */
    lmc_csrptr_t csr_पूर्णांकr;                     /* CSR7 */
    lmc_csrptr_t csr_missed_frames;            /* CSR8 */
    lmc_csrptr_t csr_9;                        /* CSR9 */
    lmc_csrptr_t csr_10;                       /* CSR10 */
    lmc_csrptr_t csr_11;                       /* CSR11 */
    lmc_csrptr_t csr_12;                       /* CSR12 */
    lmc_csrptr_t csr_13;                       /* CSR13 */
    lmc_csrptr_t csr_14;                       /* CSR14 */
    lmc_csrptr_t csr_15;                       /* CSR15 */
पूर्ण;

#घोषणा csr_enetrom             csr_9   /* 21040 */
#घोषणा csr_reserved            csr_10  /* 21040 */
#घोषणा csr_full_duplex         csr_11  /* 21040 */
#घोषणा csr_bootrom             csr_10  /* 21041/21140A/?? */
#घोषणा csr_gp                  csr_12  /* 21140* */
#घोषणा csr_watchकरोg            csr_15  /* 21140* */
#घोषणा csr_gp_समयr            csr_11  /* 21041/21140* */
#घोषणा csr_srom_mii            csr_9   /* 21041/21140* */
#घोषणा csr_sia_status          csr_12  /* 2104x */
#घोषणा csr_sia_connectivity    csr_13  /* 2104x */
#घोषणा csr_sia_tx_rx           csr_14  /* 2104x */
#घोषणा csr_sia_general         csr_15  /* 2104x */

/* tulip length/control transmit descriptor definitions
 *  used to define bits in the second tulip_desc_t field (length)
 *  क्रम the transmit descriptor -baz */

#घोषणा LMC_TDES_FIRST_BUFFER_SIZE       ((u32)(0x000007FF))
#घोषणा LMC_TDES_SECOND_BUFFER_SIZE      ((u32)(0x003FF800))
#घोषणा LMC_TDES_HASH_FILTERING          ((u32)(0x00400000))
#घोषणा LMC_TDES_DISABLE_PADDING         ((u32)(0x00800000))
#घोषणा LMC_TDES_SECOND_ADDR_CHAINED     ((u32)(0x01000000))
#घोषणा LMC_TDES_END_OF_RING             ((u32)(0x02000000))
#घोषणा LMC_TDES_ADD_CRC_DISABLE         ((u32)(0x04000000))
#घोषणा LMC_TDES_SETUP_PACKET            ((u32)(0x08000000))
#घोषणा LMC_TDES_INVERSE_FILTERING       ((u32)(0x10000000))
#घोषणा LMC_TDES_FIRST_SEGMENT           ((u32)(0x20000000))
#घोषणा LMC_TDES_LAST_SEGMENT            ((u32)(0x40000000))
#घोषणा LMC_TDES_INTERRUPT_ON_COMPLETION ((u32)(0x80000000))

#घोषणा TDES_SECOND_BUFFER_SIZE_BIT_NUMBER  11
#घोषणा TDES_COLLISION_COUNT_BIT_NUMBER     3

/* Constants क्रम the RCV descriptor RDES */

#घोषणा LMC_RDES_OVERFLOW             ((u32)(0x00000001))
#घोषणा LMC_RDES_CRC_ERROR            ((u32)(0x00000002))
#घोषणा LMC_RDES_DRIBBLING_BIT        ((u32)(0x00000004))
#घोषणा LMC_RDES_REPORT_ON_MII_ERR    ((u32)(0x00000008))
#घोषणा LMC_RDES_RCV_WATCHDOG_TIMEOUT ((u32)(0x00000010))
#घोषणा LMC_RDES_FRAME_TYPE           ((u32)(0x00000020))
#घोषणा LMC_RDES_COLLISION_SEEN       ((u32)(0x00000040))
#घोषणा LMC_RDES_FRAME_TOO_LONG       ((u32)(0x00000080))
#घोषणा LMC_RDES_LAST_DESCRIPTOR      ((u32)(0x00000100))
#घोषणा LMC_RDES_FIRST_DESCRIPTOR     ((u32)(0x00000200))
#घोषणा LMC_RDES_MULTICAST_FRAME      ((u32)(0x00000400))
#घोषणा LMC_RDES_RUNT_FRAME           ((u32)(0x00000800))
#घोषणा LMC_RDES_DATA_TYPE            ((u32)(0x00003000))
#घोषणा LMC_RDES_LENGTH_ERROR         ((u32)(0x00004000))
#घोषणा LMC_RDES_ERROR_SUMMARY        ((u32)(0x00008000))
#घोषणा LMC_RDES_FRAME_LENGTH         ((u32)(0x3FFF0000))
#घोषणा LMC_RDES_OWN_BIT              ((u32)(0x80000000))

#घोषणा RDES_FRAME_LENGTH_BIT_NUMBER       16

#घोषणा LMC_RDES_ERROR_MASK ( (u32)( \
	  LMC_RDES_OVERFLOW \
	| LMC_RDES_DRIBBLING_BIT \
	| LMC_RDES_REPORT_ON_MII_ERR \
        | LMC_RDES_COLLISION_SEEN ) )


/*
 * Ioctl info
 */

प्रकार काष्ठा अणु
	u32	n;
	u32	m;
	u32	v;
	u32	x;
	u32	r;
	u32	f;
	u32	exact;
पूर्ण lmc_av9110_t;

/*
 * Common काष्ठाure passed to the ioctl code.
 */
काष्ठा lmc___ctl अणु
	u32	cardtype;
	u32	घड़ी_source;		/* HSSI, T1 */
	u32	घड़ी_rate;		/* T1 */
	u32	crc_length;
	u32	cable_length;		/* DS3 */
	u32	scrambler_onoff;	/* DS3 */
	u32	cable_type;		/* T1 */
	u32	keepalive_onoff;	/* protocol */
	u32	ticks;			/* ticks/sec */
	जोड़ अणु
		lmc_av9110_t	ssi;
	पूर्ण cardspec;
	u32       circuit_type;   /* T1 or E1 */
पूर्ण;


/*
 * Careful, look at the data sheet, there's more to this
 * काष्ठाure than meets the eye.  It should probably be:
 *
 * काष्ठा tulip_desc_t अणु
 *         u8  own:1;
 *         u32 status:31;
 *         u32 control:10;
 *         u32 buffer1;
 *         u32 buffer2;
 * पूर्ण;
 * You could also expand status control to provide more bit inक्रमmation
 */

काष्ठा tulip_desc_t अणु
	s32 status;
	s32 length;
	u32 buffer1;
	u32 buffer2;
पूर्ण;

/*
 * media independent methods to check on media status, link, light LEDs,
 * etc.
 */
काष्ठा lmc___media अणु
	व्योम	(* init)(lmc_softc_t * स्थिर);
	व्योम	(* शेषs)(lmc_softc_t * स्थिर);
	व्योम	(* set_status)(lmc_softc_t * स्थिर, lmc_ctl_t *);
	व्योम	(* set_घड़ी_source)(lmc_softc_t * स्थिर, पूर्णांक);
	व्योम	(* set_speed)(lmc_softc_t * स्थिर, lmc_ctl_t *);
	व्योम	(* set_cable_length)(lmc_softc_t * स्थिर, पूर्णांक);
	व्योम	(* set_scrambler)(lmc_softc_t * स्थिर, पूर्णांक);
	पूर्णांक	(* get_link_status)(lmc_softc_t * स्थिर);
	व्योम	(* set_link_status)(lmc_softc_t * स्थिर, पूर्णांक);
	व्योम	(* set_crc_length)(lmc_softc_t * स्थिर, पूर्णांक);
        व्योम    (* set_circuit_type)(lmc_softc_t * स्थिर, पूर्णांक);
        व्योम	(* watchकरोg)(lmc_softc_t * स्थिर);
पूर्ण;


#घोषणा STATCHECK     0xBEEFCAFE

काष्ठा lmc_extra_statistics
अणु
	u32       version_size;
	u32       lmc_cardtype;

	u32       tx_ProcTimeout;
	u32       tx_IntTimeout;
	u32       tx_NoCompleteCnt;
	u32       tx_MaxXmtsB4Int;
	u32       tx_TimeoutCnt;
	u32       tx_OutOfSyncPtr;
	u32       tx_tbusy0;
	u32       tx_tbusy1;
	u32       tx_tbusy_calls;
	u32       resetCount;
	u32       lmc_txfull;
	u32       tbusy;
	u32       dirtyTx;
	u32       lmc_next_tx;
	u32       otherTypeCnt;
	u32       lastType;
	u32       lastTypeOK;
	u32       txLoopCnt;
	u32       usedXmtDescripCnt;
	u32       txIndexCnt;
	u32       rxIntLoopCnt;

	u32       rx_SmallPktCnt;
	u32       rx_BadPktSurgeCnt;
	u32       rx_BuffAllocErr;
	u32       tx_lossOfClockCnt;

	/* T1 error counters */
	u32       framingBitErrorCount;
	u32       lineCodeViolationCount;

	u32       lossOfFrameCount;
	u32       changeOfFrameAlignmentCount;
	u32       severelyErroredFrameCount;

	u32       check;
पूर्ण;

प्रकार काष्ठा lmc_xinfo अणु
	u32       Magic0;                         /* BEEFCAFE */

	u32       PciCardType;
	u32       PciSlotNumber;          /* PCI slot number       */

	u16	       DriverMajorVersion;
	u16	       DriverMinorVersion;
	u16	       DriverSubVersion;

	u16	       XilinxRevisionNumber;
	u16	       MaxFrameSize;

	u16     	  t1_alarm1_status;
	u16       	t1_alarm2_status;

	पूर्णांक             link_status;
	u32       mii_reg16;

	u32       Magic1;                         /* DEADBEEF */
पूर्ण LMC_XINFO;


/*
 * क्रमward decl
 */
काष्ठा lmc___softc अणु
	अक्षर                   *name;
	u8			board_idx;
	काष्ठा lmc_extra_statistics extra_stats;
	काष्ठा net_device      *lmc_device;

	पूर्णांक                     hang, rxdesc, bad_packet, some_counter;
	u32  	         	txgo;
	काष्ठा lmc_regfile_t	lmc_csrs;
	अस्थिर u32		lmc_txtick;
	अस्थिर u32		lmc_rxtick;
	u32			lmc_flags;
	u32			lmc_पूर्णांकrmask;	/* our copy of csr_पूर्णांकr */
	u32			lmc_cmdmode;	/* our copy of csr_cmdmode */
	u32			lmc_busmode;	/* our copy of csr_busmode */
	u32			lmc_gpio_io;	/* state of in/out settings */
	u32			lmc_gpio;	/* state of outमाला_दो */
	काष्ठा sk_buff*		lmc_txq[LMC_TXDESCS];
	काष्ठा sk_buff*		lmc_rxq[LMC_RXDESCS];
	अस्थिर
	काष्ठा tulip_desc_t	lmc_rxring[LMC_RXDESCS];
	अस्थिर
	काष्ठा tulip_desc_t	lmc_txring[LMC_TXDESCS];
	अचिन्हित पूर्णांक		lmc_next_rx, lmc_next_tx;
	अस्थिर
	अचिन्हित पूर्णांक		lmc_taपूर्णांक_tx, lmc_taपूर्णांक_rx;
	पूर्णांक			lmc_tx_start, lmc_txfull;
	पूर्णांक			lmc_txbusy;
	u16			lmc_miireg16;
	पूर्णांक			lmc_ok;
	पूर्णांक			last_link_status;
	पूर्णांक			lmc_cardtype;
	u32               	last_frameerr;
	lmc_media_t	       *lmc_media;
	काष्ठा समयr_list	समयr;
	lmc_ctl_t		ictl;
	u32			TxDescriptControlInit;

	पूर्णांक                     tx_TimeoutInd; /* additional driver state */
	पूर्णांक                     tx_TimeoutDisplay;
	अचिन्हित पूर्णांक		lastlmc_taपूर्णांक_tx;
	पूर्णांक                     lasttx_packets;
	u32			tx_घड़ीState;
	u32			lmc_crcSize;
	LMC_XINFO		lmc_xinfo;
	अक्षर                    lmc_yel, lmc_blue, lmc_red; /* क्रम T1 and DS3 */
	अक्षर                    lmc_timing; /* क्रम HSSI and SSI */
	पूर्णांक                     got_irq;

	अक्षर                    last_led_err[4];

	u32                     last_पूर्णांक;
	u32                     num_पूर्णांक;

	spinlock_t              lmc_lock;
	u16			अगर_type;       /* HDLC/PPP or NET */

	/* Failure हालs */
	u8			failed_ring;
	u8			failed_recv_alloc;

	/* Structure check */
	u32                     check;
पूर्ण;

#घोषणा LMC_PCI_TIME 1
#घोषणा LMC_EXT_TIME 0

#घोषणा PKT_BUF_SZ              1542  /* was 1536 */

/* CSR5 settings */
#घोषणा TIMER_INT     0x00000800
#घोषणा TP_LINK_FAIL  0x00001000
#घोषणा TP_LINK_PASS  0x00000010
#घोषणा NORMAL_INT    0x00010000
#घोषणा ABNORMAL_INT  0x00008000
#घोषणा RX_JABBER_INT 0x00000200
#घोषणा RX_DIED       0x00000100
#घोषणा RX_NOBUFF     0x00000080
#घोषणा RX_INT        0x00000040
#घोषणा TX_FIFO_UNDER 0x00000020
#घोषणा TX_JABBER     0x00000008
#घोषणा TX_NOBUFF     0x00000004
#घोषणा TX_DIED       0x00000002
#घोषणा TX_INT        0x00000001

/* CSR6 settings */
#घोषणा OPERATION_MODE  0x00000200 /* Full Duplex      */
#घोषणा PROMISC_MODE    0x00000040 /* Promiscuous Mode */
#घोषणा RECEIVE_ALL     0x40000000 /* Receive All      */
#घोषणा PASS_BAD_FRAMES 0x00000008 /* Pass Bad Frames  */

/* Dec control रेजिस्टरs  CSR6 as well */
#घोषणा LMC_DEC_ST 0x00002000
#घोषणा LMC_DEC_SR 0x00000002

/* CSR15 settings */
#घोषणा RECV_WATCHDOG_DISABLE 0x00000010
#घोषणा JABBER_DISABLE        0x00000001

/* More settings */
/*
 * aSR6 -- Command (Operation Mode) Register
 */
#घोषणा TULIP_CMD_RECEIVEALL    0x40000000L /* (RW)  Receivel all frames? */
#घोषणा TULIP_CMD_MUSTBEONE     0x02000000L /* (RW)  Must Be One (21140) */
#घोषणा TULIP_CMD_TXTHRSHLDCTL  0x00400000L /* (RW)  Transmit Threshold Mode (21140) */
#घोषणा TULIP_CMD_STOREFWD      0x00200000L /* (RW)  Store and Forward (21140) */
#घोषणा TULIP_CMD_NOHEARTBEAT   0x00080000L /* (RW)  No Heartbeat (21140) */
#घोषणा TULIP_CMD_PORTSELECT    0x00040000L /* (RW)  Post Select (100Mb) (21140) */
#घोषणा TULIP_CMD_FULLDUPLEX    0x00000200L /* (RW)  Full Duplex Mode */
#घोषणा TULIP_CMD_OPERMODE      0x00000C00L /* (RW)  Operating Mode */
#घोषणा TULIP_CMD_PROMISCUOUS   0x00000041L /* (RW)  Promiscuous Mode */
#घोषणा TULIP_CMD_PASSBADPKT    0x00000008L /* (RW)  Pass Bad Frames */
#घोषणा TULIP_CMD_THRESHOLDCTL  0x0000C000L /* (RW)  Threshold Control */

#घोषणा TULIP_GP_PINSET         0x00000100L
#घोषणा TULIP_BUSMODE_SWRESET   0x00000001L
#घोषणा TULIP_WATCHDOG_TXDISABLE 0x00000001L
#घोषणा TULIP_WATCHDOG_RXDISABLE 0x00000010L

#घोषणा TULIP_STS_NORMALINTR    0x00010000L /* (RW)  Normal Interrupt */
#घोषणा TULIP_STS_ABNRMLINTR    0x00008000L /* (RW)  Abnormal Interrupt */
#घोषणा TULIP_STS_ERI           0x00004000L /* (RW)  Early Receive Interrupt */
#घोषणा TULIP_STS_SYSERROR      0x00002000L /* (RW)  System Error */
#घोषणा TULIP_STS_GTE           0x00000800L /* (RW)  General Pupose Timer Exp */
#घोषणा TULIP_STS_ETI           0x00000400L /* (RW)  Early Transmit Interrupt */
#घोषणा TULIP_STS_RXWT          0x00000200L /* (RW)  Receiver Watchकरोg Timeout */
#घोषणा TULIP_STS_RXSTOPPED     0x00000100L /* (RW)  Receiver Process Stopped */
#घोषणा TULIP_STS_RXNOBUF       0x00000080L /* (RW)  Receive Buf Unavail */
#घोषणा TULIP_STS_RXINTR        0x00000040L /* (RW)  Receive Interrupt */
#घोषणा TULIP_STS_TXUNDERFLOW   0x00000020L /* (RW)  Transmit Underflow */
#घोषणा TULIP_STS_TXJABER       0x00000008L /* (RW)  Jabber समयout */
#घोषणा TULIP_STS_TXNOBUF       0x00000004L
#घोषणा TULIP_STS_TXSTOPPED     0x00000002L /* (RW)  Transmit Process Stopped */
#घोषणा TULIP_STS_TXINTR        0x00000001L /* (RW)  Transmit Interrupt */

#घोषणा TULIP_STS_RXS_STOPPED   0x00000000L /*        000 - Stopped */

#घोषणा TULIP_STS_RXSTOPPED     0x00000100L             /* (RW)  Receive Process Stopped */
#घोषणा TULIP_STS_RXNOBUF       0x00000080L

#घोषणा TULIP_CMD_TXRUN         0x00002000L /* (RW)  Start/Stop Transmitter */
#घोषणा TULIP_CMD_RXRUN         0x00000002L /* (RW)  Start/Stop Receive Filtering */
#घोषणा TULIP_DSTS_TxDEFERRED   0x00000001      /* Initially Deferred */
#घोषणा TULIP_DSTS_OWNER        0x80000000      /* Owner (1 = 21040) */
#घोषणा TULIP_DSTS_RxMIIERR     0x00000008
#घोषणा LMC_DSTS_ERRSUM         (TULIP_DSTS_RxMIIERR)

#घोषणा TULIP_DEFAULT_INTR_MASK  (TULIP_STS_NORMALINTR \
  | TULIP_STS_RXINTR       \
  | TULIP_STS_TXINTR     \
  | TULIP_STS_ABNRMLINTR \
  | TULIP_STS_SYSERROR   \
  | TULIP_STS_TXSTOPPED  \
  | TULIP_STS_TXUNDERFLOW\
  | TULIP_STS_RXSTOPPED )

#घोषणा DESC_OWNED_BY_SYSTEM   ((u32)(0x00000000))
#घोषणा DESC_OWNED_BY_DC21X4   ((u32)(0x80000000))

#अगर_अघोषित TULIP_CMD_RECEIVEALL
#घोषणा TULIP_CMD_RECEIVEALL 0x40000000L
#पूर्ण_अगर

/* Adapter module number */
#घोषणा LMC_ADAP_HSSI           2
#घोषणा LMC_ADAP_DS3            3
#घोषणा LMC_ADAP_SSI            4
#घोषणा LMC_ADAP_T1             5

#घोषणा LMC_MTU 1500

#घोषणा LMC_CRC_LEN_16 2  /* 16-bit CRC */
#घोषणा LMC_CRC_LEN_32 4

#पूर्ण_अगर /* _LMC_VAR_H_ */
