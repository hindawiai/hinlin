<शैली गुरु>
/*
	Written 1998-2000 by Donald Becker.

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	Support inक्रमmation and updates available at
	http://www.scyld.com/network/pci-skeleton.hपंचांगl

	Linux kernel updates:

	Version 2.51, Nov 17, 2001 (jgarzik):
	- Add ethtool support
	- Replace some MII-related magic numbers with स्थिरants

*/

#घोषणा DRV_NAME	"fealnx"

अटल पूर्णांक debug;		/* 1-> prपूर्णांक debug message */
अटल पूर्णांक max_पूर्णांकerrupt_work = 20;

/* Maximum number of multicast addresses to filter (vs. Rx-all-multicast). */
अटल पूर्णांक multicast_filter_limit = 32;

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme. */
/* Setting to > 1518 effectively disables this feature.          */
अटल पूर्णांक rx_copyअवरोध;

/* Used to pass the media type, etc.                            */
/* Both 'options[]' and 'full_duplex[]' should exist क्रम driver */
/* पूर्णांकeroperability.                                            */
/* The media type is usually passed in 'options[]'.             */
#घोषणा MAX_UNITS 8		/* More are supported, limit only on options */
अटल पूर्णांक options[MAX_UNITS] = अणु -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक full_duplex[MAX_UNITS] = अणु -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;

/* Operational parameters that are set at compile समय.                 */
/* Keep the ring sizes a घातer of two क्रम compile efficiency.           */
/* The compiler will convert <अचिन्हित>'%'<2^N> पूर्णांकo a bit mask.        */
/* Making the Tx ring too large decreases the effectiveness of channel  */
/* bonding and packet priority.                                         */
/* There are no ill effects from too-large receive rings.               */
// 88-12-9 modअगरy,
// #घोषणा TX_RING_SIZE    16
// #घोषणा RX_RING_SIZE    32
#घोषणा TX_RING_SIZE    6
#घोषणा RX_RING_SIZE    12
#घोषणा TX_TOTAL_SIZE	TX_RING_SIZE*माप(काष्ठा fealnx_desc)
#घोषणा RX_TOTAL_SIZE	RX_RING_SIZE*माप(काष्ठा fealnx_desc)

/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT      (2*HZ)

#घोषणा PKT_BUF_SZ      1536	/* Size of each temporary Rx buffer. */


/* Include files, deचिन्हित to support most kernel versions 2.0.0 and later. */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/processor.h>	/* Processor type क्रम cache alignment. */
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>

/* This driver was written to use PCI memory space, however some x86 प्रणालीs
   work only with I/O space accesses. */
#अगर_अघोषित __alpha__
#घोषणा USE_IO_OPS
#पूर्ण_अगर

/* Kernel compatibility defines, some common to David Hinds' PCMCIA package. */
/* This is only in the support-all-kernels source code. */

#घोषणा RUN_AT(x) (jअगरfies + (x))

MODULE_AUTHOR("Myson or whoever");
MODULE_DESCRIPTION("Myson MTD-8xx 100/10M Ethernet PCI Adapter Driver");
MODULE_LICENSE("GPL");
module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
module_param(debug, पूर्णांक, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param(multicast_filter_limit, पूर्णांक, 0);
module_param_array(options, पूर्णांक, शून्य, 0);
module_param_array(full_duplex, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "fealnx maximum events handled per interrupt");
MODULE_PARM_DESC(debug, "fealnx enable debugging (0-1)");
MODULE_PARM_DESC(rx_copyअवरोध, "fealnx copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(multicast_filter_limit, "fealnx maximum number of filtered multicast addresses");
MODULE_PARM_DESC(options, "fealnx: Bits 0-3: media type, bit 17: full duplex");
MODULE_PARM_DESC(full_duplex, "fealnx full duplex setting(s) (1)");

क्रमागत अणु
	MIN_REGION_SIZE		= 136,
पूर्ण;

/* A chip capabilities table, matching the entries in pci_tbl[] above. */
क्रमागत chip_capability_flags अणु
	HAS_MII_XCVR,
	HAS_CHIP_XCVR,
पूर्ण;

/* 89/6/13 add, */
/* क्रम dअगरferent PHY */
क्रमागत phy_type_flags अणु
	MysonPHY = 1,
	AhकरोcPHY = 2,
	SeeqPHY = 3,
	MarvellPHY = 4,
	Myson981 = 5,
	LevelOnePHY = 6,
	OtherPHY = 10,
पूर्ण;

काष्ठा chip_info अणु
	अक्षर *chip_name;
	पूर्णांक flags;
पूर्ण;

अटल स्थिर काष्ठा chip_info skel_netdrv_tbl[] = अणु
 	अणु "100/10M Ethernet PCI Adapter",	HAS_MII_XCVR पूर्ण,
	अणु "100/10M Ethernet PCI Adapter",	HAS_CHIP_XCVR पूर्ण,
	अणु "1000/100/10M Ethernet PCI Adapter",	HAS_MII_XCVR पूर्ण,
पूर्ण;

/* Offsets to the Command and Status Registers. */
क्रमागत fealnx_offsets अणु
	PAR0 = 0x0,		/* physical address 0-3 */
	PAR1 = 0x04,		/* physical address 4-5 */
	MAR0 = 0x08,		/* multicast address 0-3 */
	MAR1 = 0x0C,		/* multicast address 4-7 */
	FAR0 = 0x10,		/* flow-control address 0-3 */
	FAR1 = 0x14,		/* flow-control address 4-5 */
	TCRRCR = 0x18,		/* receive & transmit configuration */
	BCR = 0x1C,		/* bus command */
	TXPDR = 0x20,		/* transmit polling demand */
	RXPDR = 0x24,		/* receive polling demand */
	RXCWP = 0x28,		/* receive current word poपूर्णांकer */
	TXLBA = 0x2C,		/* transmit list base address */
	RXLBA = 0x30,		/* receive list base address */
	ISR = 0x34,		/* पूर्णांकerrupt status */
	IMR = 0x38,		/* पूर्णांकerrupt mask */
	FTH = 0x3C,		/* flow control high/low threshold */
	MANAGEMENT = 0x40,	/* bootrom/eeprom and mii management */
	TALLY = 0x44,		/* tally counters क्रम crc and mpa */
	TSR = 0x48,		/* tally counter क्रम transmit status */
	BMCRSR = 0x4c,		/* basic mode control and status */
	PHYIDENTIFIER = 0x50,	/* phy identअगरier */
	ANARANLPAR = 0x54,	/* स्वतः-negotiation advertisement and link
				   partner ability */
	ANEROCR = 0x58,		/* स्वतः-negotiation expansion and pci conf. */
	BPREMRPSR = 0x5c,	/* bypass & receive error mask and phy status */
पूर्ण;

/* Bits in the पूर्णांकerrupt status/enable रेजिस्टरs. */
/* The bits in the Intr Status/Enable रेजिस्टरs, mostly पूर्णांकerrupt sources. */
क्रमागत पूर्णांकr_status_bits अणु
	RFCON = 0x00020000,	/* receive flow control xon packet */
	RFCOFF = 0x00010000,	/* receive flow control xoff packet */
	LSCStatus = 0x00008000,	/* link status change */
	ANCStatus = 0x00004000,	/* स्वतःnegotiation completed */
	FBE = 0x00002000,	/* fatal bus error */
	FBEMask = 0x00001800,	/* mask bit12-11 */
	ParityErr = 0x00000000,	/* parity error */
	TargetErr = 0x00001000,	/* target पात */
	MasterErr = 0x00000800,	/* master error */
	TUNF = 0x00000400,	/* transmit underflow */
	ROVF = 0x00000200,	/* receive overflow */
	ETI = 0x00000100,	/* transmit early पूर्णांक */
	ERI = 0x00000080,	/* receive early पूर्णांक */
	CNTOVF = 0x00000040,	/* counter overflow */
	RBU = 0x00000020,	/* receive buffer unavailable */
	TBU = 0x00000010,	/* transmit buffer unavilable */
	TI = 0x00000008,	/* transmit पूर्णांकerrupt */
	RI = 0x00000004,	/* receive पूर्णांकerrupt */
	RxErr = 0x00000002,	/* receive error */
पूर्ण;

/* Bits in the NetworkConfig रेजिस्टर, W क्रम writing, R क्रम पढ़ोing */
/* FIXME: some names are invented by me. Marked with (name?) */
/* If you have करोcs and know bit names, please fix 'em */
क्रमागत rx_mode_bits अणु
	CR_W_ENH	= 0x02000000,	/* enhanced mode (name?) */
	CR_W_FD		= 0x00100000,	/* full duplex */
	CR_W_PS10	= 0x00080000,	/* 10 mbit */
	CR_W_TXEN	= 0x00040000,	/* tx enable (name?) */
	CR_W_PS1000	= 0x00010000,	/* 1000 mbit */
     /* CR_W_RXBURSTMASK= 0x00000e00, Im unsure about this */
	CR_W_RXMODEMASK	= 0x000000e0,
	CR_W_PROM	= 0x00000080,	/* promiscuous mode */
	CR_W_AB		= 0x00000040,	/* accept broadcast */
	CR_W_AM		= 0x00000020,	/* accept mutlicast */
	CR_W_ARP	= 0x00000008,	/* receive runt pkt */
	CR_W_ALP	= 0x00000004,	/* receive दीर्घ pkt */
	CR_W_SEP	= 0x00000002,	/* receive error pkt */
	CR_W_RXEN	= 0x00000001,	/* rx enable (unicast?) (name?) */

	CR_R_TXSTOP	= 0x04000000,	/* tx stopped (name?) */
	CR_R_FD		= 0x00100000,	/* full duplex detected */
	CR_R_PS10	= 0x00080000,	/* 10 mbit detected */
	CR_R_RXSTOP	= 0x00008000,	/* rx stopped (name?) */
पूर्ण;

/* The Tulip Rx and Tx buffer descriptors. */
काष्ठा fealnx_desc अणु
	s32 status;
	s32 control;
	u32 buffer;
	u32 next_desc;
	काष्ठा fealnx_desc *next_desc_logical;
	काष्ठा sk_buff *skbuff;
	u32 reserved1;
	u32 reserved2;
पूर्ण;

/* Bits in network_desc.status */
क्रमागत rx_desc_status_bits अणु
	RXOWN = 0x80000000,	/* own bit */
	FLNGMASK = 0x0fff0000,	/* frame length */
	FLNGShअगरt = 16,
	MARSTATUS = 0x00004000,	/* multicast address received */
	BARSTATUS = 0x00002000,	/* broadcast address received */
	PHYSTATUS = 0x00001000,	/* physical address received */
	RXFSD = 0x00000800,	/* first descriptor */
	RXLSD = 0x00000400,	/* last descriptor */
	ErrorSummary = 0x80,	/* error summary */
	RUNTPKT = 0x40,		/* runt packet received */
	LONGPKT = 0x20,		/* दीर्घ packet received */
	FAE = 0x10,		/* frame align error */
	CRC = 0x08,		/* crc error */
	RXER = 0x04,		/* receive error */
पूर्ण;

क्रमागत rx_desc_control_bits अणु
	RXIC = 0x00800000,	/* पूर्णांकerrupt control */
	RBSShअगरt = 0,
पूर्ण;

क्रमागत tx_desc_status_bits अणु
	TXOWN = 0x80000000,	/* own bit */
	JABTO = 0x00004000,	/* jabber समयout */
	CSL = 0x00002000,	/* carrier sense lost */
	LC = 0x00001000,	/* late collision */
	EC = 0x00000800,	/* excessive collision */
	UDF = 0x00000400,	/* fअगरo underflow */
	DFR = 0x00000200,	/* deferred */
	HF = 0x00000100,	/* heartbeat fail */
	NCRMask = 0x000000ff,	/* collision retry count */
	NCRShअगरt = 0,
पूर्ण;

क्रमागत tx_desc_control_bits अणु
	TXIC = 0x80000000,	/* पूर्णांकerrupt control */
	ETIControl = 0x40000000,	/* early transmit पूर्णांकerrupt */
	TXLD = 0x20000000,	/* last descriptor */
	TXFD = 0x10000000,	/* first descriptor */
	CRCEnable = 0x08000000,	/* crc control */
	PADEnable = 0x04000000,	/* padding control */
	RetryTxLC = 0x02000000,	/* retry late collision */
	PKTSMask = 0x3ff800,	/* packet size bit21-11 */
	PKTSShअगरt = 11,
	TBSMask = 0x000007ff,	/* transmit buffer bit 10-0 */
	TBSShअगरt = 0,
पूर्ण;

/* BootROM/EEPROM/MII Management Register */
#घोषणा MASK_MIIR_MII_READ       0x00000000
#घोषणा MASK_MIIR_MII_WRITE      0x00000008
#घोषणा MASK_MIIR_MII_MDO        0x00000004
#घोषणा MASK_MIIR_MII_MDI        0x00000002
#घोषणा MASK_MIIR_MII_MDC        0x00000001

/* ST+OP+PHYAD+REGAD+TA */
#घोषणा OP_READ             0x6000	/* ST:01+OP:10+PHYAD+REGAD+TA:Z0 */
#घोषणा OP_WRITE            0x5002	/* ST:01+OP:01+PHYAD+REGAD+TA:10 */

/* ------------------------------------------------------------------------- */
/*      Constants क्रम Myson PHY                                              */
/* ------------------------------------------------------------------------- */
#घोषणा MysonPHYID      0xd0000302
/* 89-7-27 add, (begin) */
#घोषणा MysonPHYID0     0x0302
#घोषणा StatusRegister  18
#घोषणा SPEED100        0x0400	// bit10
#घोषणा FULLMODE        0x0800	// bit11
/* 89-7-27 add, (end) */

/* ------------------------------------------------------------------------- */
/*      Constants क्रम Seeq 80225 PHY                                         */
/* ------------------------------------------------------------------------- */
#घोषणा SeeqPHYID0      0x0016

#घोषणा MIIRegister18   18
#घोषणा SPD_DET_100     0x80
#घोषणा DPLX_DET_FULL   0x40

/* ------------------------------------------------------------------------- */
/*      Constants क्रम Ahकरोc 101 PHY                                          */
/* ------------------------------------------------------------------------- */
#घोषणा AhकरोcPHYID0     0x0022

#घोषणा DiagnosticReg   18
#घोषणा DPLX_FULL       0x0800
#घोषणा Speed_100       0x0400

/* 89/6/13 add, */
/* -------------------------------------------------------------------------- */
/*      Constants                                                             */
/* -------------------------------------------------------------------------- */
#घोषणा MarvellPHYID0           0x0141
#घोषणा LevelOnePHYID0		0x0013

#घोषणा MII1000BaseTControlReg  9
#घोषणा MII1000BaseTStatusReg   10
#घोषणा SpecअगरicReg		17

/* क्रम 1000BaseT Control Register */
#घोषणा PHYAbletoPerक्रमm1000FullDuplex  0x0200
#घोषणा PHYAbletoPerक्रमm1000HalfDuplex  0x0100
#घोषणा PHY1000AbilityMask              0x300

// क्रम phy specअगरic status रेजिस्टर, marvell phy.
#घोषणा SpeedMask       0x0c000
#घोषणा Speed_1000M     0x08000
#घोषणा Speed_100M      0x4000
#घोषणा Speed_10M       0
#घोषणा Full_Duplex     0x2000

// 89/12/29 add, क्रम phy specअगरic status रेजिस्टर, levelone phy, (begin)
#घोषणा LXT1000_100M    0x08000
#घोषणा LXT1000_1000M   0x0c000
#घोषणा LXT1000_Full    0x200
// 89/12/29 add, क्रम phy specअगरic status रेजिस्टर, levelone phy, (end)

/* क्रम 3-in-1 हाल, BMCRSR रेजिस्टर */
#घोषणा LinkIsUp2	0x00040000

/* क्रम PHY */
#घोषणा LinkIsUp        0x0004


काष्ठा netdev_निजी अणु
	/* Descriptor rings first क्रम alignment. */
	काष्ठा fealnx_desc *rx_ring;
	काष्ठा fealnx_desc *tx_ring;

	dma_addr_t rx_ring_dma;
	dma_addr_t tx_ring_dma;

	spinlock_t lock;

	/* Media monitoring समयr. */
	काष्ठा समयr_list समयr;

	/* Reset समयr */
	काष्ठा समयr_list reset_समयr;
	पूर्णांक reset_समयr_armed;
	अचिन्हित दीर्घ crvalue_sv;
	अचिन्हित दीर्घ imrvalue_sv;

	/* Frequently used values: keep some adjacent क्रम cache effect. */
	पूर्णांक flags;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित दीर्घ crvalue;
	अचिन्हित दीर्घ bcrvalue;
	अचिन्हित दीर्घ imrvalue;
	काष्ठा fealnx_desc *cur_rx;
	काष्ठा fealnx_desc *lack_rxbuf;
	पूर्णांक really_rx_count;
	काष्ठा fealnx_desc *cur_tx;
	काष्ठा fealnx_desc *cur_tx_copy;
	पूर्णांक really_tx_count;
	पूर्णांक मुक्त_tx_count;
	अचिन्हित पूर्णांक rx_buf_sz;	/* Based on MTU+slack. */

	/* These values are keep track of the transceiver/media in use. */
	अचिन्हित पूर्णांक linkok;
	अचिन्हित पूर्णांक line_speed;
	अचिन्हित पूर्णांक duplexmode;
	अचिन्हित पूर्णांक शेष_port:4;	/* Last dev->अगर_port value. */
	अचिन्हित पूर्णांक PHYType;

	/* MII transceiver section. */
	पूर्णांक mii_cnt;		/* MII device addresses. */
	अचिन्हित अक्षर phys[2];	/* MII device addresses. */
	काष्ठा mii_अगर_info mii;
	व्योम __iomem *mem;
पूर्ण;


अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value);
अटल पूर्णांक netdev_खोलो(काष्ठा net_device *dev);
अटल व्योम getlinktype(काष्ठा net_device *dev);
अटल व्योम getlinkstatus(काष्ठा net_device *dev);
अटल व्योम netdev_समयr(काष्ठा समयr_list *t);
अटल व्योम reset_समयr(काष्ठा समयr_list *t);
अटल व्योम fealnx_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम init_ring(काष्ठा net_device *dev);
अटल netdev_tx_t start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_instance);
अटल पूर्णांक netdev_rx(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल व्योम __set_rx_mode(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev);
अटल पूर्णांक mii_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;
अटल पूर्णांक netdev_बंद(काष्ठा net_device *dev);
अटल व्योम reset_rx_descriptors(काष्ठा net_device *dev);
अटल व्योम reset_tx_descriptors(काष्ठा net_device *dev);

अटल व्योम stop_nic_rx(व्योम __iomem *ioaddr, दीर्घ crvalue)
अणु
	पूर्णांक delay = 0x1000;
	ioग_लिखो32(crvalue & ~(CR_W_RXEN), ioaddr + TCRRCR);
	जबतक (--delay) अणु
		अगर ( (ioपढ़ो32(ioaddr + TCRRCR) & CR_R_RXSTOP) == CR_R_RXSTOP)
			अवरोध;
	पूर्ण
पूर्ण


अटल व्योम stop_nic_rxtx(व्योम __iomem *ioaddr, दीर्घ crvalue)
अणु
	पूर्णांक delay = 0x1000;
	ioग_लिखो32(crvalue & ~(CR_W_RXEN+CR_W_TXEN), ioaddr + TCRRCR);
	जबतक (--delay) अणु
		अगर ( (ioपढ़ो32(ioaddr + TCRRCR) & (CR_R_RXSTOP+CR_R_TXSTOP))
					    == (CR_R_RXSTOP+CR_R_TXSTOP) )
			अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= netdev_खोलो,
	.nकरो_stop		= netdev_बंद,
	.nकरो_start_xmit		= start_tx,
	.nकरो_get_stats 		= get_stats,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_करो_ioctl		= mii_ioctl,
	.nकरो_tx_समयout		= fealnx_tx_समयout,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक fealnx_init_one(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा netdev_निजी *np;
	पूर्णांक i, option, err, irq;
	अटल पूर्णांक card_idx = -1;
	अक्षर boardname[12];
	व्योम __iomem *ioaddr;
	अचिन्हित दीर्घ len;
	अचिन्हित पूर्णांक chip_id = ent->driver_data;
	काष्ठा net_device *dev;
	व्योम *ring_space;
	dma_addr_t ring_dma;
#अगर_घोषित USE_IO_OPS
	पूर्णांक bar = 0;
#अन्यथा
	पूर्णांक bar = 1;
#पूर्ण_अगर

	card_idx++;
	प्र_लिखो(boardname, "fealnx%d", card_idx);

	option = card_idx < MAX_UNITS ? options[card_idx] : 0;

	i = pci_enable_device(pdev);
	अगर (i) वापस i;
	pci_set_master(pdev);

	len = pci_resource_len(pdev, bar);
	अगर (len < MIN_REGION_SIZE) अणु
		dev_err(&pdev->dev,
			   "region size %ld too small, aborting\n", len);
		वापस -ENODEV;
	पूर्ण

	i = pci_request_regions(pdev, boardname);
	अगर (i)
		वापस i;

	irq = pdev->irq;

	ioaddr = pci_iomap(pdev, bar, len);
	अगर (!ioaddr) अणु
		err = -ENOMEM;
		जाओ err_out_res;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा netdev_निजी));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out_unmap;
	पूर्ण
	SET_NETDEV_DEV(dev, &pdev->dev);

	/* पढ़ो ethernet id */
	क्रम (i = 0; i < 6; ++i)
		dev->dev_addr[i] = ioपढ़ो8(ioaddr + PAR0 + i);

	/* Reset the chip to erase previous misconfiguration. */
	ioग_लिखो32(0x00000001, ioaddr + BCR);

	/* Make certain the descriptor lists are aligned. */
	np = netdev_priv(dev);
	np->mem = ioaddr;
	spin_lock_init(&np->lock);
	np->pci_dev = pdev;
	np->flags = skel_netdrv_tbl[chip_id].flags;
	pci_set_drvdata(pdev, dev);
	np->mii.dev = dev;
	np->mii.mdio_पढ़ो = mdio_पढ़ो;
	np->mii.mdio_ग_लिखो = mdio_ग_लिखो;
	np->mii.phy_id_mask = 0x1f;
	np->mii.reg_num_mask = 0x1f;

	ring_space = dma_alloc_coherent(&pdev->dev, RX_TOTAL_SIZE, &ring_dma,
					GFP_KERNEL);
	अगर (!ring_space) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_dev;
	पूर्ण
	np->rx_ring = ring_space;
	np->rx_ring_dma = ring_dma;

	ring_space = dma_alloc_coherent(&pdev->dev, TX_TOTAL_SIZE, &ring_dma,
					GFP_KERNEL);
	अगर (!ring_space) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_rx;
	पूर्ण
	np->tx_ring = ring_space;
	np->tx_ring_dma = ring_dma;

	/* find the connected MII xcvrs */
	अगर (np->flags == HAS_MII_XCVR) अणु
		पूर्णांक phy, phy_idx = 0;

		क्रम (phy = 1; phy < 32 && phy_idx < ARRAY_SIZE(np->phys);
			       phy++) अणु
			पूर्णांक mii_status = mdio_पढ़ो(dev, phy, 1);

			अगर (mii_status != 0xffff && mii_status != 0x0000) अणु
				np->phys[phy_idx++] = phy;
				dev_info(&pdev->dev,
				       "MII PHY found at address %d, status "
				       "0x%4.4x.\n", phy, mii_status);
				/* get phy type */
				अणु
					अचिन्हित पूर्णांक data;

					data = mdio_पढ़ो(dev, np->phys[0], 2);
					अगर (data == SeeqPHYID0)
						np->PHYType = SeeqPHY;
					अन्यथा अगर (data == AhकरोcPHYID0)
						np->PHYType = AhकरोcPHY;
					अन्यथा अगर (data == MarvellPHYID0)
						np->PHYType = MarvellPHY;
					अन्यथा अगर (data == MysonPHYID0)
						np->PHYType = Myson981;
					अन्यथा अगर (data == LevelOnePHYID0)
						np->PHYType = LevelOnePHY;
					अन्यथा
						np->PHYType = OtherPHY;
				पूर्ण
			पूर्ण
		पूर्ण

		np->mii_cnt = phy_idx;
		अगर (phy_idx == 0)
			dev_warn(&pdev->dev,
				"MII PHY not found -- this device may "
			       "not operate correctly.\n");
	पूर्ण अन्यथा अणु
		np->phys[0] = 32;
/* 89/6/23 add, (begin) */
		/* get phy type */
		अगर (ioपढ़ो32(ioaddr + PHYIDENTIFIER) == MysonPHYID)
			np->PHYType = MysonPHY;
		अन्यथा
			np->PHYType = OtherPHY;
	पूर्ण
	np->mii.phy_id = np->phys[0];

	अगर (dev->mem_start)
		option = dev->mem_start;

	/* The lower four bits are the media type. */
	अगर (option > 0) अणु
		अगर (option & 0x200)
			np->mii.full_duplex = 1;
		np->शेष_port = option & 15;
	पूर्ण

	अगर (card_idx < MAX_UNITS && full_duplex[card_idx] > 0)
		np->mii.full_duplex = full_duplex[card_idx];

	अगर (np->mii.full_duplex) अणु
		dev_info(&pdev->dev, "Media type forced to Full Duplex.\n");
/* 89/6/13 add, (begin) */
//      अगर (np->PHYType==MarvellPHY)
		अगर ((np->PHYType == MarvellPHY) || (np->PHYType == LevelOnePHY)) अणु
			अचिन्हित पूर्णांक data;

			data = mdio_पढ़ो(dev, np->phys[0], 9);
			data = (data & 0xfcff) | 0x0200;
			mdio_ग_लिखो(dev, np->phys[0], 9, data);
		पूर्ण
/* 89/6/13 add, (end) */
		अगर (np->flags == HAS_MII_XCVR)
			mdio_ग_लिखो(dev, np->phys[0], MII_ADVERTISE, ADVERTISE_FULL);
		अन्यथा
			ioग_लिखो32(ADVERTISE_FULL, ioaddr + ANARANLPAR);
		np->mii.क्रमce_media = 1;
	पूर्ण

	dev->netdev_ops = &netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ err_out_मुक्त_tx;

	prपूर्णांकk(KERN_INFO "%s: %s at %p, %pM, IRQ %d.\n",
	       dev->name, skel_netdrv_tbl[chip_id].chip_name, ioaddr,
	       dev->dev_addr, irq);

	वापस 0;

err_out_मुक्त_tx:
	dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, np->tx_ring,
			  np->tx_ring_dma);
err_out_मुक्त_rx:
	dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, np->rx_ring,
			  np->rx_ring_dma);
err_out_मुक्त_dev:
	मुक्त_netdev(dev);
err_out_unmap:
	pci_iounmap(pdev, ioaddr);
err_out_res:
	pci_release_regions(pdev);
	वापस err;
पूर्ण


अटल व्योम fealnx_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
		काष्ठा netdev_निजी *np = netdev_priv(dev);

		dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, np->tx_ring,
				  np->tx_ring_dma);
		dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, np->rx_ring,
				  np->rx_ring_dma);
		unरेजिस्टर_netdev(dev);
		pci_iounmap(pdev, np->mem);
		मुक्त_netdev(dev);
		pci_release_regions(pdev);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "fealnx: remove for unknown device\n");
पूर्ण


अटल uदीर्घ m80x_send_cmd_to_phy(व्योम __iomem *miiport, पूर्णांक opcode, पूर्णांक phyad, पूर्णांक regad)
अणु
	uदीर्घ miir;
	पूर्णांक i;
	अचिन्हित पूर्णांक mask, data;

	/* enable MII output */
	miir = (uदीर्घ) ioपढ़ो32(miiport);
	miir &= 0xfffffff0;

	miir |= MASK_MIIR_MII_WRITE + MASK_MIIR_MII_MDO;

	/* send 32 1's preamble */
	क्रम (i = 0; i < 32; i++) अणु
		/* low MDC; MDO is alपढ़ोy high (miir) */
		miir &= ~MASK_MIIR_MII_MDC;
		ioग_लिखो32(miir, miiport);

		/* high MDC */
		miir |= MASK_MIIR_MII_MDC;
		ioग_लिखो32(miir, miiport);
	पूर्ण

	/* calculate ST+OP+PHYAD+REGAD+TA */
	data = opcode | (phyad << 7) | (regad << 2);

	/* sent out */
	mask = 0x8000;
	जबतक (mask) अणु
		/* low MDC, prepare MDO */
		miir &= ~(MASK_MIIR_MII_MDC + MASK_MIIR_MII_MDO);
		अगर (mask & data)
			miir |= MASK_MIIR_MII_MDO;

		ioग_लिखो32(miir, miiport);
		/* high MDC */
		miir |= MASK_MIIR_MII_MDC;
		ioग_लिखो32(miir, miiport);
		udelay(30);

		/* next */
		mask >>= 1;
		अगर (mask == 0x2 && opcode == OP_READ)
			miir &= ~MASK_MIIR_MII_WRITE;
	पूर्ण
	वापस miir;
पूर्ण


अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phyad, पूर्णांक regad)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *miiport = np->mem + MANAGEMENT;
	uदीर्घ miir;
	अचिन्हित पूर्णांक mask, data;

	miir = m80x_send_cmd_to_phy(miiport, OP_READ, phyad, regad);

	/* पढ़ो data */
	mask = 0x8000;
	data = 0;
	जबतक (mask) अणु
		/* low MDC */
		miir &= ~MASK_MIIR_MII_MDC;
		ioग_लिखो32(miir, miiport);

		/* पढ़ो MDI */
		miir = ioपढ़ो32(miiport);
		अगर (miir & MASK_MIIR_MII_MDI)
			data |= mask;

		/* high MDC, and रुको */
		miir |= MASK_MIIR_MII_MDC;
		ioग_लिखो32(miir, miiport);
		udelay(30);

		/* next */
		mask >>= 1;
	पूर्ण

	/* low MDC */
	miir &= ~MASK_MIIR_MII_MDC;
	ioग_लिखो32(miir, miiport);

	वापस data & 0xffff;
पूर्ण


अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phyad, पूर्णांक regad, पूर्णांक data)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *miiport = np->mem + MANAGEMENT;
	uदीर्घ miir;
	अचिन्हित पूर्णांक mask;

	miir = m80x_send_cmd_to_phy(miiport, OP_WRITE, phyad, regad);

	/* ग_लिखो data */
	mask = 0x8000;
	जबतक (mask) अणु
		/* low MDC, prepare MDO */
		miir &= ~(MASK_MIIR_MII_MDC + MASK_MIIR_MII_MDO);
		अगर (mask & data)
			miir |= MASK_MIIR_MII_MDO;
		ioग_लिखो32(miir, miiport);

		/* high MDC */
		miir |= MASK_MIIR_MII_MDC;
		ioग_लिखो32(miir, miiport);

		/* next */
		mask >>= 1;
	पूर्ण

	/* low MDC */
	miir &= ~MASK_MIIR_MII_MDC;
	ioग_लिखो32(miir, miiport);
पूर्ण


अटल पूर्णांक netdev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->mem;
	स्थिर पूर्णांक irq = np->pci_dev->irq;
	पूर्णांक rc, i;

	ioग_लिखो32(0x00000001, ioaddr + BCR);	/* Reset */

	rc = request_irq(irq, पूर्णांकr_handler, IRQF_SHARED, dev->name, dev);
	अगर (rc)
		वापस -EAGAIN;

	क्रम (i = 0; i < 3; i++)
		ioग_लिखो16(((अचिन्हित लघु*)dev->dev_addr)[i],
				ioaddr + PAR0 + i*2);

	init_ring(dev);

	ioग_लिखो32(np->rx_ring_dma, ioaddr + RXLBA);
	ioग_लिखो32(np->tx_ring_dma, ioaddr + TXLBA);

	/* Initialize other रेजिस्टरs. */
	/* Configure the PCI bus bursts and FIFO thresholds.
	   486: Set 8 दीर्घword burst.
	   586: no burst limit.
	   Burst length 5:3
	   0 0 0   1
	   0 0 1   4
	   0 1 0   8
	   0 1 1   16
	   1 0 0   32
	   1 0 1   64
	   1 1 0   128
	   1 1 1   256
	   Wait the specअगरied 50 PCI cycles after a reset by initializing
	   Tx and Rx queues and the address filter list.
	   FIXME (Ueimor): optimistic क्रम alpha + posted ग_लिखोs ? */

	np->bcrvalue = 0x10;	/* little-endian, 8 burst length */
#अगर_घोषित __BIG_ENDIAN
	np->bcrvalue |= 0x04;	/* big-endian */
#पूर्ण_अगर

#अगर defined(__i386__) && !defined(MODULE)
	अगर (boot_cpu_data.x86 <= 4)
		np->crvalue = 0xa00;
	अन्यथा
#पूर्ण_अगर
		np->crvalue = 0xe00;	/* rx 128 burst length */


// 89/12/29 add,
// 90/1/16 modअगरy,
//   np->imrvalue=FBE|TUNF|CNTOVF|RBU|TI|RI;
	np->imrvalue = TUNF | CNTOVF | RBU | TI | RI;
	अगर (np->pci_dev->device == 0x891) अणु
		np->bcrvalue |= 0x200;	/* set PROG bit */
		np->crvalue |= CR_W_ENH;	/* set enhanced bit */
		np->imrvalue |= ETI;
	पूर्ण
	ioग_लिखो32(np->bcrvalue, ioaddr + BCR);

	अगर (dev->अगर_port == 0)
		dev->अगर_port = np->शेष_port;

	ioग_लिखो32(0, ioaddr + RXPDR);
// 89/9/1 modअगरy,
//   np->crvalue = 0x00e40001;    /* tx store and क्रमward, tx/rx enable */
	np->crvalue |= 0x00e40001;	/* tx store and क्रमward, tx/rx enable */
	np->mii.full_duplex = np->mii.क्रमce_media;
	getlinkstatus(dev);
	अगर (np->linkok)
		getlinktype(dev);
	__set_rx_mode(dev);

	netअगर_start_queue(dev);

	/* Clear and Enable पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	ioग_लिखो32(FBE | TUNF | CNTOVF | RBU | TI | RI, ioaddr + ISR);
	ioग_लिखो32(np->imrvalue, ioaddr + IMR);

	अगर (debug)
		prपूर्णांकk(KERN_DEBUG "%s: Done netdev_open().\n", dev->name);

	/* Set the समयr to check क्रम link beat. */
	समयr_setup(&np->समयr, netdev_समयr, 0);
	np->समयr.expires = RUN_AT(3 * HZ);

	/* समयr handler */
	add_समयr(&np->समयr);

	समयr_setup(&np->reset_समयr, reset_समयr, 0);
	np->reset_समयr_armed = 0;
	वापस rc;
पूर्ण


अटल व्योम getlinkstatus(काष्ठा net_device *dev)
/* function: Routine will पढ़ो MII Status Register to get link status.       */
/* input   : dev... poपूर्णांकer to the adapter block.                            */
/* output  : none.                                                           */
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	अचिन्हित पूर्णांक i, DelayTime = 0x1000;

	np->linkok = 0;

	अगर (np->PHYType == MysonPHY) अणु
		क्रम (i = 0; i < DelayTime; ++i) अणु
			अगर (ioपढ़ो32(np->mem + BMCRSR) & LinkIsUp2) अणु
				np->linkok = 1;
				वापस;
			पूर्ण
			udelay(100);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < DelayTime; ++i) अणु
			अगर (mdio_पढ़ो(dev, np->phys[0], MII_BMSR) & BMSR_LSTATUS) अणु
				np->linkok = 1;
				वापस;
			पूर्ण
			udelay(100);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम getlinktype(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	अगर (np->PHYType == MysonPHY) अणु	/* 3-in-1 हाल */
		अगर (ioपढ़ो32(np->mem + TCRRCR) & CR_R_FD)
			np->duplexmode = 2;	/* full duplex */
		अन्यथा
			np->duplexmode = 1;	/* half duplex */
		अगर (ioपढ़ो32(np->mem + TCRRCR) & CR_R_PS10)
			np->line_speed = 1;	/* 10M */
		अन्यथा
			np->line_speed = 2;	/* 100M */
	पूर्ण अन्यथा अणु
		अगर (np->PHYType == SeeqPHY) अणु	/* this PHY is SEEQ 80225 */
			अचिन्हित पूर्णांक data;

			data = mdio_पढ़ो(dev, np->phys[0], MIIRegister18);
			अगर (data & SPD_DET_100)
				np->line_speed = 2;	/* 100M */
			अन्यथा
				np->line_speed = 1;	/* 10M */
			अगर (data & DPLX_DET_FULL)
				np->duplexmode = 2;	/* full duplex mode */
			अन्यथा
				np->duplexmode = 1;	/* half duplex mode */
		पूर्ण अन्यथा अगर (np->PHYType == AhकरोcPHY) अणु
			अचिन्हित पूर्णांक data;

			data = mdio_पढ़ो(dev, np->phys[0], DiagnosticReg);
			अगर (data & Speed_100)
				np->line_speed = 2;	/* 100M */
			अन्यथा
				np->line_speed = 1;	/* 10M */
			अगर (data & DPLX_FULL)
				np->duplexmode = 2;	/* full duplex mode */
			अन्यथा
				np->duplexmode = 1;	/* half duplex mode */
		पूर्ण
/* 89/6/13 add, (begin) */
		अन्यथा अगर (np->PHYType == MarvellPHY) अणु
			अचिन्हित पूर्णांक data;

			data = mdio_पढ़ो(dev, np->phys[0], SpecअगरicReg);
			अगर (data & Full_Duplex)
				np->duplexmode = 2;	/* full duplex mode */
			अन्यथा
				np->duplexmode = 1;	/* half duplex mode */
			data &= SpeedMask;
			अगर (data == Speed_1000M)
				np->line_speed = 3;	/* 1000M */
			अन्यथा अगर (data == Speed_100M)
				np->line_speed = 2;	/* 100M */
			अन्यथा
				np->line_speed = 1;	/* 10M */
		पूर्ण
/* 89/6/13 add, (end) */
/* 89/7/27 add, (begin) */
		अन्यथा अगर (np->PHYType == Myson981) अणु
			अचिन्हित पूर्णांक data;

			data = mdio_पढ़ो(dev, np->phys[0], StatusRegister);

			अगर (data & SPEED100)
				np->line_speed = 2;
			अन्यथा
				np->line_speed = 1;

			अगर (data & FULLMODE)
				np->duplexmode = 2;
			अन्यथा
				np->duplexmode = 1;
		पूर्ण
/* 89/7/27 add, (end) */
/* 89/12/29 add */
		अन्यथा अगर (np->PHYType == LevelOnePHY) अणु
			अचिन्हित पूर्णांक data;

			data = mdio_पढ़ो(dev, np->phys[0], SpecअगरicReg);
			अगर (data & LXT1000_Full)
				np->duplexmode = 2;	/* full duplex mode */
			अन्यथा
				np->duplexmode = 1;	/* half duplex mode */
			data &= SpeedMask;
			अगर (data == LXT1000_1000M)
				np->line_speed = 3;	/* 1000M */
			अन्यथा अगर (data == LXT1000_100M)
				np->line_speed = 2;	/* 100M */
			अन्यथा
				np->line_speed = 1;	/* 10M */
		पूर्ण
		np->crvalue &= (~CR_W_PS10) & (~CR_W_FD) & (~CR_W_PS1000);
		अगर (np->line_speed == 1)
			np->crvalue |= CR_W_PS10;
		अन्यथा अगर (np->line_speed == 3)
			np->crvalue |= CR_W_PS1000;
		अगर (np->duplexmode == 2)
			np->crvalue |= CR_W_FD;
	पूर्ण
पूर्ण


/* Take lock beक्रमe calling this */
अटल व्योम allocate_rx_buffers(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	/*  allocate skb क्रम rx buffers */
	जबतक (np->really_rx_count != RX_RING_SIZE) अणु
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb(dev, np->rx_buf_sz);
		अगर (skb == शून्य)
			अवरोध;	/* Better luck next round. */

		जबतक (np->lack_rxbuf->skbuff)
			np->lack_rxbuf = np->lack_rxbuf->next_desc_logical;

		np->lack_rxbuf->skbuff = skb;
		np->lack_rxbuf->buffer = dma_map_single(&np->pci_dev->dev,
							skb->data,
							np->rx_buf_sz,
							DMA_FROM_DEVICE);
		np->lack_rxbuf->status = RXOWN;
		++np->really_rx_count;
	पूर्ण
पूर्ण


अटल व्योम netdev_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा netdev_निजी *np = from_समयr(np, t, समयr);
	काष्ठा net_device *dev = np->mii.dev;
	व्योम __iomem *ioaddr = np->mem;
	पूर्णांक old_crvalue = np->crvalue;
	अचिन्हित पूर्णांक old_linkok = np->linkok;
	अचिन्हित दीर्घ flags;

	अगर (debug)
		prपूर्णांकk(KERN_DEBUG "%s: Media selection timer tick, status %8.8x "
		       "config %8.8x.\n", dev->name, ioपढ़ो32(ioaddr + ISR),
		       ioपढ़ो32(ioaddr + TCRRCR));

	spin_lock_irqsave(&np->lock, flags);

	अगर (np->flags == HAS_MII_XCVR) अणु
		getlinkstatus(dev);
		अगर ((old_linkok == 0) && (np->linkok == 1)) अणु	/* we need to detect the media type again */
			getlinktype(dev);
			अगर (np->crvalue != old_crvalue) अणु
				stop_nic_rxtx(ioaddr, np->crvalue);
				ioग_लिखो32(np->crvalue, ioaddr + TCRRCR);
			पूर्ण
		पूर्ण
	पूर्ण

	allocate_rx_buffers(dev);

	spin_unlock_irqrestore(&np->lock, flags);

	np->समयr.expires = RUN_AT(10 * HZ);
	add_समयr(&np->समयr);
पूर्ण


/* Take lock beक्रमe calling */
/* Reset chip and disable rx, tx and पूर्णांकerrupts */
अटल व्योम reset_and_disable_rxtx(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->mem;
	पूर्णांक delay=51;

	/* Reset the chip's Tx and Rx processes. */
	stop_nic_rxtx(ioaddr, 0);

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	ioग_लिखो32(0, ioaddr + IMR);

	/* Reset the chip to erase previous misconfiguration. */
	ioग_लिखो32(0x00000001, ioaddr + BCR);

	/* Ueimor: रुको क्रम 50 PCI cycles (and flush posted ग_लिखोs btw).
	   We surely रुको too दीर्घ (address+data phase). Who cares? */
	जबतक (--delay) अणु
		ioपढ़ो32(ioaddr + BCR);
		rmb();
	पूर्ण
पूर्ण


/* Take lock beक्रमe calling */
/* Restore chip after reset */
अटल व्योम enable_rxtx(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->mem;

	reset_rx_descriptors(dev);

	ioग_लिखो32(np->tx_ring_dma + ((अक्षर*)np->cur_tx - (अक्षर*)np->tx_ring),
		ioaddr + TXLBA);
	ioग_लिखो32(np->rx_ring_dma + ((अक्षर*)np->cur_rx - (अक्षर*)np->rx_ring),
		ioaddr + RXLBA);

	ioग_लिखो32(np->bcrvalue, ioaddr + BCR);

	ioग_लिखो32(0, ioaddr + RXPDR);
	__set_rx_mode(dev); /* changes np->crvalue, ग_लिखोs it पूर्णांकo TCRRCR */

	/* Clear and Enable पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	ioग_लिखो32(FBE | TUNF | CNTOVF | RBU | TI | RI, ioaddr + ISR);
	ioग_लिखो32(np->imrvalue, ioaddr + IMR);

	ioग_लिखो32(0, ioaddr + TXPDR);
पूर्ण


अटल व्योम reset_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा netdev_निजी *np = from_समयr(np, t, reset_समयr);
	काष्ठा net_device *dev = np->mii.dev;
	अचिन्हित दीर्घ flags;

	prपूर्णांकk(KERN_WARNING "%s: resetting tx and rx machinery\n", dev->name);

	spin_lock_irqsave(&np->lock, flags);
	np->crvalue = np->crvalue_sv;
	np->imrvalue = np->imrvalue_sv;

	reset_and_disable_rxtx(dev);
	/* works क्रम me without this:
	reset_tx_descriptors(dev); */
	enable_rxtx(dev);
	netअगर_start_queue(dev); /* FIXME: or netअगर_wake_queue(dev); ? */

	np->reset_समयr_armed = 0;

	spin_unlock_irqrestore(&np->lock, flags);
पूर्ण


अटल व्योम fealnx_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->mem;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	prपूर्णांकk(KERN_WARNING
	       "%s: Transmit timed out, status %8.8x, resetting...\n",
	       dev->name, ioपढ़ो32(ioaddr + ISR));

	अणु
		prपूर्णांकk(KERN_DEBUG "  Rx ring %p: ", np->rx_ring);
		क्रम (i = 0; i < RX_RING_SIZE; i++)
			prपूर्णांकk(KERN_CONT " %8.8x",
			       (अचिन्हित पूर्णांक) np->rx_ring[i].status);
		prपूर्णांकk(KERN_CONT "\n");
		prपूर्णांकk(KERN_DEBUG "  Tx ring %p: ", np->tx_ring);
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			prपूर्णांकk(KERN_CONT " %4.4x", np->tx_ring[i].status);
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण

	spin_lock_irqsave(&np->lock, flags);

	reset_and_disable_rxtx(dev);
	reset_tx_descriptors(dev);
	enable_rxtx(dev);

	spin_unlock_irqrestore(&np->lock, flags);

	netअगर_trans_update(dev); /* prevent tx समयout */
	dev->stats.tx_errors++;
	netअगर_wake_queue(dev); /* or .._start_.. ?? */
पूर्ण


/* Initialize the Rx and Tx rings, aदीर्घ with various 'dev' bits. */
अटल व्योम init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक i;

	/* initialize rx variables */
	np->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);
	np->cur_rx = &np->rx_ring[0];
	np->lack_rxbuf = np->rx_ring;
	np->really_rx_count = 0;

	/* initial rx descriptors. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		np->rx_ring[i].status = 0;
		np->rx_ring[i].control = np->rx_buf_sz << RBSShअगरt;
		np->rx_ring[i].next_desc = np->rx_ring_dma +
			(i + 1)*माप(काष्ठा fealnx_desc);
		np->rx_ring[i].next_desc_logical = &np->rx_ring[i + 1];
		np->rx_ring[i].skbuff = शून्य;
	पूर्ण

	/* क्रम the last rx descriptor */
	np->rx_ring[i - 1].next_desc = np->rx_ring_dma;
	np->rx_ring[i - 1].next_desc_logical = np->rx_ring;

	/* allocate skb क्रम rx buffers */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, np->rx_buf_sz);

		अगर (skb == शून्य) अणु
			np->lack_rxbuf = &np->rx_ring[i];
			अवरोध;
		पूर्ण

		++np->really_rx_count;
		np->rx_ring[i].skbuff = skb;
		np->rx_ring[i].buffer = dma_map_single(&np->pci_dev->dev,
						       skb->data,
						       np->rx_buf_sz,
						       DMA_FROM_DEVICE);
		np->rx_ring[i].status = RXOWN;
		np->rx_ring[i].control |= RXIC;
	पूर्ण

	/* initialize tx variables */
	np->cur_tx = &np->tx_ring[0];
	np->cur_tx_copy = &np->tx_ring[0];
	np->really_tx_count = 0;
	np->मुक्त_tx_count = TX_RING_SIZE;

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		np->tx_ring[i].status = 0;
		/* करो we need np->tx_ring[i].control = XXX; ?? */
		np->tx_ring[i].next_desc = np->tx_ring_dma +
			(i + 1)*माप(काष्ठा fealnx_desc);
		np->tx_ring[i].next_desc_logical = &np->tx_ring[i + 1];
		np->tx_ring[i].skbuff = शून्य;
	पूर्ण

	/* क्रम the last tx descriptor */
	np->tx_ring[i - 1].next_desc = np->tx_ring_dma;
	np->tx_ring[i - 1].next_desc_logical = &np->tx_ring[0];
पूर्ण


अटल netdev_tx_t start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&np->lock, flags);

	np->cur_tx_copy->skbuff = skb;

#घोषणा one_buffer
#घोषणा BPT 1022
#अगर defined(one_buffer)
	np->cur_tx_copy->buffer = dma_map_single(&np->pci_dev->dev, skb->data,
						 skb->len, DMA_TO_DEVICE);
	np->cur_tx_copy->control = TXIC | TXLD | TXFD | CRCEnable | PADEnable;
	np->cur_tx_copy->control |= (skb->len << PKTSShअगरt);	/* pkt size */
	np->cur_tx_copy->control |= (skb->len << TBSShअगरt);	/* buffer size */
// 89/12/29 add,
	अगर (np->pci_dev->device == 0x891)
		np->cur_tx_copy->control |= ETIControl | RetryTxLC;
	np->cur_tx_copy->status = TXOWN;
	np->cur_tx_copy = np->cur_tx_copy->next_desc_logical;
	--np->मुक्त_tx_count;
#या_अगर defined(two_buffer)
	अगर (skb->len > BPT) अणु
		काष्ठा fealnx_desc *next;

		/* क्रम the first descriptor */
		np->cur_tx_copy->buffer = dma_map_single(&np->pci_dev->dev,
							 skb->data, BPT,
							 DMA_TO_DEVICE);
		np->cur_tx_copy->control = TXIC | TXFD | CRCEnable | PADEnable;
		np->cur_tx_copy->control |= (skb->len << PKTSShअगरt);	/* pkt size */
		np->cur_tx_copy->control |= (BPT << TBSShअगरt);	/* buffer size */

		/* क्रम the last descriptor */
		next = np->cur_tx_copy->next_desc_logical;
		next->skbuff = skb;
		next->control = TXIC | TXLD | CRCEnable | PADEnable;
		next->control |= (skb->len << PKTSShअगरt);	/* pkt size */
		next->control |= ((skb->len - BPT) << TBSShअगरt);	/* buf size */
// 89/12/29 add,
		अगर (np->pci_dev->device == 0x891)
			np->cur_tx_copy->control |= ETIControl | RetryTxLC;
		next->buffer = dma_map_single(&ep->pci_dev->dev,
					      skb->data + BPT, skb->len - BPT,
					      DMA_TO_DEVICE);

		next->status = TXOWN;
		np->cur_tx_copy->status = TXOWN;

		np->cur_tx_copy = next->next_desc_logical;
		np->मुक्त_tx_count -= 2;
	पूर्ण अन्यथा अणु
		np->cur_tx_copy->buffer = dma_map_single(&np->pci_dev->dev,
							 skb->data, skb->len,
							 DMA_TO_DEVICE);
		np->cur_tx_copy->control = TXIC | TXLD | TXFD | CRCEnable | PADEnable;
		np->cur_tx_copy->control |= (skb->len << PKTSShअगरt);	/* pkt size */
		np->cur_tx_copy->control |= (skb->len << TBSShअगरt);	/* buffer size */
// 89/12/29 add,
		अगर (np->pci_dev->device == 0x891)
			np->cur_tx_copy->control |= ETIControl | RetryTxLC;
		np->cur_tx_copy->status = TXOWN;
		np->cur_tx_copy = np->cur_tx_copy->next_desc_logical;
		--np->मुक्त_tx_count;
	पूर्ण
#पूर्ण_अगर

	अगर (np->मुक्त_tx_count < 2)
		netअगर_stop_queue(dev);
	++np->really_tx_count;
	ioग_लिखो32(0, np->mem + TXPDR);

	spin_unlock_irqrestore(&np->lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण


/* Take lock beक्रमe calling */
/* Chip probably hosed tx ring. Clean up. */
अटल व्योम reset_tx_descriptors(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	काष्ठा fealnx_desc *cur;
	पूर्णांक i;

	/* initialize tx variables */
	np->cur_tx = &np->tx_ring[0];
	np->cur_tx_copy = &np->tx_ring[0];
	np->really_tx_count = 0;
	np->मुक्त_tx_count = TX_RING_SIZE;

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		cur = &np->tx_ring[i];
		अगर (cur->skbuff) अणु
			dma_unmap_single(&np->pci_dev->dev, cur->buffer,
					 cur->skbuff->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(cur->skbuff);
			cur->skbuff = शून्य;
		पूर्ण
		cur->status = 0;
		cur->control = 0;	/* needed? */
		/* probably not needed. We करो it क्रम purely paranoid reasons */
		cur->next_desc = np->tx_ring_dma +
			(i + 1)*माप(काष्ठा fealnx_desc);
		cur->next_desc_logical = &np->tx_ring[i + 1];
	पूर्ण
	/* क्रम the last tx descriptor */
	np->tx_ring[TX_RING_SIZE - 1].next_desc = np->tx_ring_dma;
	np->tx_ring[TX_RING_SIZE - 1].next_desc_logical = &np->tx_ring[0];
पूर्ण


/* Take lock and stop rx beक्रमe calling this */
अटल व्योम reset_rx_descriptors(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	काष्ठा fealnx_desc *cur = np->cur_rx;
	पूर्णांक i;

	allocate_rx_buffers(dev);

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		अगर (cur->skbuff)
			cur->status = RXOWN;
		cur = cur->next_desc_logical;
	पूर्ण

	ioग_लिखो32(np->rx_ring_dma + ((अक्षर*)np->cur_rx - (अक्षर*)np->rx_ring),
		np->mem + RXLBA);
पूर्ण


/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_instance;
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->mem;
	दीर्घ boguscnt = max_पूर्णांकerrupt_work;
	अचिन्हित पूर्णांक num_tx = 0;
	पूर्णांक handled = 0;

	spin_lock(&np->lock);

	ioग_लिखो32(0, ioaddr + IMR);

	करो अणु
		u32 पूर्णांकr_status = ioपढ़ो32(ioaddr + ISR);

		/* Acknowledge all of the current पूर्णांकerrupt sources ASAP. */
		ioग_लिखो32(पूर्णांकr_status, ioaddr + ISR);

		अगर (debug)
			prपूर्णांकk(KERN_DEBUG "%s: Interrupt, status %4.4x.\n", dev->name,
			       पूर्णांकr_status);

		अगर (!(पूर्णांकr_status & np->imrvalue))
			अवरोध;

		handled = 1;

// 90/1/16 delete,
//
//      अगर (पूर्णांकr_status & FBE)
//      अणु   /* fatal error */
//          stop_nic_tx(ioaddr, 0);
//          stop_nic_rx(ioaddr, 0);
//          अवरोध;
//      पूर्ण;

		अगर (पूर्णांकr_status & TUNF)
			ioग_लिखो32(0, ioaddr + TXPDR);

		अगर (पूर्णांकr_status & CNTOVF) अणु
			/* missed pkts */
			dev->stats.rx_missed_errors +=
				ioपढ़ो32(ioaddr + TALLY) & 0x7fff;

			/* crc error */
			dev->stats.rx_crc_errors +=
			    (ioपढ़ो32(ioaddr + TALLY) & 0x7fff0000) >> 16;
		पूर्ण

		अगर (पूर्णांकr_status & (RI | RBU)) अणु
			अगर (पूर्णांकr_status & RI)
				netdev_rx(dev);
			अन्यथा अणु
				stop_nic_rx(ioaddr, np->crvalue);
				reset_rx_descriptors(dev);
				ioग_लिखो32(np->crvalue, ioaddr + TCRRCR);
			पूर्ण
		पूर्ण

		जबतक (np->really_tx_count) अणु
			दीर्घ tx_status = np->cur_tx->status;
			दीर्घ tx_control = np->cur_tx->control;

			अगर (!(tx_control & TXLD)) अणु	/* this pkt is combined by two tx descriptors */
				काष्ठा fealnx_desc *next;

				next = np->cur_tx->next_desc_logical;
				tx_status = next->status;
				tx_control = next->control;
			पूर्ण

			अगर (tx_status & TXOWN)
				अवरोध;

			अगर (!(np->crvalue & CR_W_ENH)) अणु
				अगर (tx_status & (CSL | LC | EC | UDF | HF)) अणु
					dev->stats.tx_errors++;
					अगर (tx_status & EC)
						dev->stats.tx_पातed_errors++;
					अगर (tx_status & CSL)
						dev->stats.tx_carrier_errors++;
					अगर (tx_status & LC)
						dev->stats.tx_winकरोw_errors++;
					अगर (tx_status & UDF)
						dev->stats.tx_fअगरo_errors++;
					अगर ((tx_status & HF) && np->mii.full_duplex == 0)
						dev->stats.tx_heartbeat_errors++;

				पूर्ण अन्यथा अणु
					dev->stats.tx_bytes +=
					    ((tx_control & PKTSMask) >> PKTSShअगरt);

					dev->stats.collisions +=
					    ((tx_status & NCRMask) >> NCRShअगरt);
					dev->stats.tx_packets++;
				पूर्ण
			पूर्ण अन्यथा अणु
				dev->stats.tx_bytes +=
				    ((tx_control & PKTSMask) >> PKTSShअगरt);
				dev->stats.tx_packets++;
			पूर्ण

			/* Free the original skb. */
			dma_unmap_single(&np->pci_dev->dev,
					 np->cur_tx->buffer,
					 np->cur_tx->skbuff->len,
					 DMA_TO_DEVICE);
			dev_consume_skb_irq(np->cur_tx->skbuff);
			np->cur_tx->skbuff = शून्य;
			--np->really_tx_count;
			अगर (np->cur_tx->control & TXLD) अणु
				np->cur_tx = np->cur_tx->next_desc_logical;
				++np->मुक्त_tx_count;
			पूर्ण अन्यथा अणु
				np->cur_tx = np->cur_tx->next_desc_logical;
				np->cur_tx = np->cur_tx->next_desc_logical;
				np->मुक्त_tx_count += 2;
			पूर्ण
			num_tx++;
		पूर्ण		/* end of क्रम loop */

		अगर (num_tx && np->मुक्त_tx_count >= 2)
			netअगर_wake_queue(dev);

		/* पढ़ो transmit status क्रम enhanced mode only */
		अगर (np->crvalue & CR_W_ENH) अणु
			दीर्घ data;

			data = ioपढ़ो32(ioaddr + TSR);
			dev->stats.tx_errors += (data & 0xff000000) >> 24;
			dev->stats.tx_पातed_errors +=
				(data & 0xff000000) >> 24;
			dev->stats.tx_winकरोw_errors +=
				(data & 0x00ff0000) >> 16;
			dev->stats.collisions += (data & 0x0000ffff);
		पूर्ण

		अगर (--boguscnt < 0) अणु
			prपूर्णांकk(KERN_WARNING "%s: Too much work at interrupt, "
			       "status=0x%4.4x.\n", dev->name, पूर्णांकr_status);
			अगर (!np->reset_समयr_armed) अणु
				np->reset_समयr_armed = 1;
				np->reset_समयr.expires = RUN_AT(HZ/2);
				add_समयr(&np->reset_समयr);
				stop_nic_rxtx(ioaddr, 0);
				netअगर_stop_queue(dev);
				/* or netअगर_tx_disable(dev); ?? */
				/* Prevent other paths from enabling tx,rx,पूर्णांकrs */
				np->crvalue_sv = np->crvalue;
				np->imrvalue_sv = np->imrvalue;
				np->crvalue &= ~(CR_W_TXEN | CR_W_RXEN); /* or simply = 0? */
				np->imrvalue = 0;
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	/* पढ़ो the tally counters */
	/* missed pkts */
	dev->stats.rx_missed_errors += ioपढ़ो32(ioaddr + TALLY) & 0x7fff;

	/* crc error */
	dev->stats.rx_crc_errors +=
		(ioपढ़ो32(ioaddr + TALLY) & 0x7fff0000) >> 16;

	अगर (debug)
		prपूर्णांकk(KERN_DEBUG "%s: exiting interrupt, status=%#4.4x.\n",
		       dev->name, ioपढ़ो32(ioaddr + ISR));

	ioग_लिखो32(np->imrvalue, ioaddr + IMR);

	spin_unlock(&np->lock);

	वापस IRQ_RETVAL(handled);
पूर्ण


/* This routine is logically part of the पूर्णांकerrupt handler, but separated
   क्रम clarity and better रेजिस्टर allocation. */
अटल पूर्णांक netdev_rx(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->mem;

	/* If EOP is set on the next entry, it's a new packet. Send it up. */
	जबतक (!(np->cur_rx->status & RXOWN) && np->cur_rx->skbuff) अणु
		s32 rx_status = np->cur_rx->status;

		अगर (np->really_rx_count == 0)
			अवरोध;

		अगर (debug)
			prपूर्णांकk(KERN_DEBUG "  netdev_rx() status was %8.8x.\n", rx_status);

		अगर ((!((rx_status & RXFSD) && (rx_status & RXLSD))) ||
		    (rx_status & ErrorSummary)) अणु
			अगर (rx_status & ErrorSummary) अणु	/* there was a fatal error */
				अगर (debug)
					prपूर्णांकk(KERN_DEBUG
					       "%s: Receive error, Rx status %8.8x.\n",
					       dev->name, rx_status);

				dev->stats.rx_errors++;	/* end of a packet. */
				अगर (rx_status & (LONGPKT | RUNTPKT))
					dev->stats.rx_length_errors++;
				अगर (rx_status & RXER)
					dev->stats.rx_frame_errors++;
				अगर (rx_status & CRC)
					dev->stats.rx_crc_errors++;
			पूर्ण अन्यथा अणु
				पूर्णांक need_to_reset = 0;
				पूर्णांक desno = 0;

				अगर (rx_status & RXFSD) अणु	/* this pkt is too दीर्घ, over one rx buffer */
					काष्ठा fealnx_desc *cur;

					/* check this packet is received completely? */
					cur = np->cur_rx;
					जबतक (desno <= np->really_rx_count) अणु
						++desno;
						अगर ((!(cur->status & RXOWN)) &&
						    (cur->status & RXLSD))
							अवरोध;
						/* जाओ next rx descriptor */
						cur = cur->next_desc_logical;
					पूर्ण
					अगर (desno > np->really_rx_count)
						need_to_reset = 1;
				पूर्ण अन्यथा	/* RXLSD did not find, something error */
					need_to_reset = 1;

				अगर (need_to_reset == 0) अणु
					पूर्णांक i;

					dev->stats.rx_length_errors++;

					/* मुक्त all rx descriptors related this दीर्घ pkt */
					क्रम (i = 0; i < desno; ++i) अणु
						अगर (!np->cur_rx->skbuff) अणु
							prपूर्णांकk(KERN_DEBUG
								"%s: I'm scared\n", dev->name);
							अवरोध;
						पूर्ण
						np->cur_rx->status = RXOWN;
						np->cur_rx = np->cur_rx->next_desc_logical;
					पूर्ण
					जारी;
				पूर्ण अन्यथा अणु        /* rx error, need to reset this chip */
					stop_nic_rx(ioaddr, np->crvalue);
					reset_rx_descriptors(dev);
					ioग_लिखो32(np->crvalue, ioaddr + TCRRCR);
				पूर्ण
				अवरोध;	/* निकास the जबतक loop */
			पूर्ण
		पूर्ण अन्यथा अणु	/* this received pkt is ok */

			काष्ठा sk_buff *skb;
			/* Omit the four octet CRC from the length. */
			लघु pkt_len = ((rx_status & FLNGMASK) >> FLNGShअगरt) - 4;

#अगर_अघोषित final_version
			अगर (debug)
				prपूर्णांकk(KERN_DEBUG "  netdev_rx() normal Rx pkt length %d"
				       " status %x.\n", pkt_len, rx_status);
#पूर्ण_अगर

			/* Check अगर the packet is दीर्घ enough to accept without copying
			   to a minimally-sized skbuff. */
			अगर (pkt_len < rx_copyअवरोध &&
			    (skb = netdev_alloc_skb(dev, pkt_len + 2)) != शून्य) अणु
				skb_reserve(skb, 2);	/* 16 byte align the IP header */
				dma_sync_single_क्रम_cpu(&np->pci_dev->dev,
							np->cur_rx->buffer,
							np->rx_buf_sz,
							DMA_FROM_DEVICE);
				/* Call copy + cksum अगर available. */

#अगर ! defined(__alpha__)
				skb_copy_to_linear_data(skb,
					np->cur_rx->skbuff->data, pkt_len);
				skb_put(skb, pkt_len);
#अन्यथा
				skb_put_data(skb, np->cur_rx->skbuff->data,
					     pkt_len);
#पूर्ण_अगर
				dma_sync_single_क्रम_device(&np->pci_dev->dev,
							   np->cur_rx->buffer,
							   np->rx_buf_sz,
							   DMA_FROM_DEVICE);
			पूर्ण अन्यथा अणु
				dma_unmap_single(&np->pci_dev->dev,
						 np->cur_rx->buffer,
						 np->rx_buf_sz,
						 DMA_FROM_DEVICE);
				skb_put(skb = np->cur_rx->skbuff, pkt_len);
				np->cur_rx->skbuff = शून्य;
				--np->really_rx_count;
			पूर्ण
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		पूर्ण

		np->cur_rx = np->cur_rx->next_desc_logical;
	पूर्ण			/* end of जबतक loop */

	/*  allocate skb क्रम rx buffers */
	allocate_rx_buffers(dev);

	वापस 0;
पूर्ण


अटल काष्ठा net_device_stats *get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->mem;

	/* The chip only need report frame silently dropped. */
	अगर (netअगर_running(dev)) अणु
		dev->stats.rx_missed_errors +=
			ioपढ़ो32(ioaddr + TALLY) & 0x7fff;
		dev->stats.rx_crc_errors +=
			(ioपढ़ो32(ioaddr + TALLY) & 0x7fff0000) >> 16;
	पूर्ण

	वापस &dev->stats;
पूर्ण


/* क्रम dev->set_multicast_list */
अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	spinlock_t *lp = &((काष्ठा netdev_निजी *)netdev_priv(dev))->lock;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(lp, flags);
	__set_rx_mode(dev);
	spin_unlock_irqrestore(lp, flags);
पूर्ण


/* Take lock beक्रमe calling */
अटल व्योम __set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->mem;
	u32 mc_filter[2];	/* Multicast hash filter */
	u32 rx_mode;

	अगर (dev->flags & IFF_PROMISC) अणु	/* Set promiscuous. */
		स_रखो(mc_filter, 0xff, माप(mc_filter));
		rx_mode = CR_W_PROM | CR_W_AB | CR_W_AM;
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > multicast_filter_limit) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to match, or accept all multicasts. */
		स_रखो(mc_filter, 0xff, माप(mc_filter));
		rx_mode = CR_W_AB | CR_W_AM;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;

		स_रखो(mc_filter, 0, माप(mc_filter));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अचिन्हित पूर्णांक bit;
			bit = (ether_crc(ETH_ALEN, ha->addr) >> 26) ^ 0x3F;
			mc_filter[bit >> 5] |= (1 << bit);
		पूर्ण
		rx_mode = CR_W_AB | CR_W_AM;
	पूर्ण

	stop_nic_rxtx(ioaddr, np->crvalue);

	ioग_लिखो32(mc_filter[0], ioaddr + MAR0);
	ioग_लिखो32(mc_filter[1], ioaddr + MAR1);
	np->crvalue &= ~CR_W_RXMODEMASK;
	np->crvalue |= rx_mode;
	ioग_लिखो32(np->crvalue, ioaddr + TCRRCR);
पूर्ण

अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(np->pci_dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक netdev_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);

	spin_lock_irq(&np->lock);
	mii_ethtool_get_link_ksettings(&np->mii, cmd);
	spin_unlock_irq(&np->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक netdev_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक rc;

	spin_lock_irq(&np->lock);
	rc = mii_ethtool_set_link_ksettings(&np->mii, cmd);
	spin_unlock_irq(&np->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक netdev_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	वापस mii_nway_restart(&np->mii);
पूर्ण

अटल u32 netdev_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	वापस mii_link_ok(&np->mii);
पूर्ण

अटल u32 netdev_get_msglevel(काष्ठा net_device *dev)
अणु
	वापस debug;
पूर्ण

अटल व्योम netdev_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	debug = value;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
	.nway_reset		= netdev_nway_reset,
	.get_link		= netdev_get_link,
	.get_msglevel		= netdev_get_msglevel,
	.set_msglevel		= netdev_set_msglevel,
	.get_link_ksettings	= netdev_get_link_ksettings,
	.set_link_ksettings	= netdev_set_link_ksettings,
पूर्ण;

अटल पूर्णांक mii_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	पूर्णांक rc;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	spin_lock_irq(&np->lock);
	rc = generic_mii_ioctl(&np->mii, अगर_mii(rq), cmd, शून्य);
	spin_unlock_irq(&np->lock);

	वापस rc;
पूर्ण


अटल पूर्णांक netdev_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_निजी *np = netdev_priv(dev);
	व्योम __iomem *ioaddr = np->mem;
	पूर्णांक i;

	netअगर_stop_queue(dev);

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	ioग_लिखो32(0x0000, ioaddr + IMR);

	/* Stop the chip's Tx and Rx processes. */
	stop_nic_rxtx(ioaddr, 0);

	del_समयr_sync(&np->समयr);
	del_समयr_sync(&np->reset_समयr);

	मुक्त_irq(np->pci_dev->irq, dev);

	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = np->rx_ring[i].skbuff;

		np->rx_ring[i].status = 0;
		अगर (skb) अणु
			dma_unmap_single(&np->pci_dev->dev,
					 np->rx_ring[i].buffer, np->rx_buf_sz,
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(skb);
			np->rx_ring[i].skbuff = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = np->tx_ring[i].skbuff;

		अगर (skb) अणु
			dma_unmap_single(&np->pci_dev->dev,
					 np->tx_ring[i].buffer, skb->len,
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb(skb);
			np->tx_ring[i].skbuff = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id fealnx_pci_tbl[] = अणु
	अणु0x1516, 0x0800, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0x1516, 0x0803, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1पूर्ण,
	अणु0x1516, 0x0891, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 2पूर्ण,
	अणुपूर्ण /* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, fealnx_pci_tbl);


अटल काष्ठा pci_driver fealnx_driver = अणु
	.name		= "fealnx",
	.id_table	= fealnx_pci_tbl,
	.probe		= fealnx_init_one,
	.हटाओ		= fealnx_हटाओ_one,
पूर्ण;

module_pci_driver(fealnx_driver);
