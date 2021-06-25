<शैली गुरु>
/*
	Written 1997-1998 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	This driver is क्रम the 3Com ISA EtherLink XL "Corkscrew" 3c515 ethercard.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403


	2000/2/2- Added support क्रम kernel-level ISAPnP
		by Stephen Frost <sfrost@snowman.net> and Alessandro Zummo
	Cleaned up क्रम 2.3.x/softnet by Jeff Garzik and Alan Cox.

	2001/11/17 - Added ethtool support (jgarzik)

	2002/10/28 - Locking updates क्रम 2.5 (alan@lxorguk.ukuu.org.uk)

*/

#घोषणा DRV_NAME		"3c515"

#घोषणा CORKSCREW 1

/* "Knobs" that adjust features and parameters. */
/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
   Setting to > 1512 effectively disables this feature. */
अटल पूर्णांक rx_copyअवरोध = 200;

/* Allow setting MTU to a larger size, bypassing the normal ethernet setup. */
अटल स्थिर पूर्णांक mtu = 1500;

/* Maximum events (Rx packets, etc.) to handle at each पूर्णांकerrupt. */
अटल पूर्णांक max_पूर्णांकerrupt_work = 20;

/* Enable the स्वतःmatic media selection code -- usually set. */
#घोषणा AUTOMEDIA 1

/* Allow the use of fragment bus master transfers instead of only
   programmed-I/O क्रम Vortex cards.  Full-bus-master transfers are always
   enabled by शेष on Boomerang cards.  If VORTEX_BUS_MASTER is defined,
   the feature may be turned on using 'options'. */
#घोषणा VORTEX_BUS_MASTER

/* A few values that may be tweaked. */
/* Keep the ring sizes a घातer of two क्रम efficiency. */
#घोषणा TX_RING_SIZE	16
#घोषणा RX_RING_SIZE	16
#घोषणा PKT_BUF_SZ		1536	/* Size of each temporary Rx buffer. */

#समावेश <linux/module.h>
#समावेश <linux/isapnp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/ioport.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/bitops.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#घोषणा NEW_MULTICAST
#समावेश <linux/delay.h>

#घोषणा MAX_UNITS 8

MODULE_AUTHOR("Donald Becker <becker@scyld.com>");
MODULE_DESCRIPTION("3Com 3c515 Corkscrew driver");
MODULE_LICENSE("GPL");

/* "Knobs" क्रम adjusting पूर्णांकernal parameters. */
/* Put out somewhat more debugging messages. (0 - no msg, 1 minimal msgs). */
#घोषणा DRIVER_DEBUG 1
/* Some values here only क्रम perक्रमmance evaluation and path-coverage
   debugging. */
अटल पूर्णांक rx_nocopy, rx_copy, queued_packet;

/* Number of बार to check to see अगर the Tx FIFO has space, used in some
   limited हालs. */
#घोषणा WAIT_TX_AVAIL 200

/* Operational parameter that usually are not changed. */
#घोषणा TX_TIMEOUT  ((4*HZ)/10)	/* Time in jअगरfies beक्रमe concluding Tx hung */

/* The size here is somewhat misleading: the Corkscrew also uses the ISA
   aliased रेजिस्टरs at <base>+0x400.
   */
#घोषणा CORKSCREW_TOTAL_SIZE 0x20

#अगर_घोषित DRIVER_DEBUG
अटल पूर्णांक corkscrew_debug = DRIVER_DEBUG;
#अन्यथा
अटल पूर्णांक corkscrew_debug = 1;
#पूर्ण_अगर

#घोषणा CORKSCREW_ID 10

/*
				Theory of Operation

I. Board Compatibility

This device driver is deचिन्हित क्रम the 3Com 3c515 ISA Fast EtherLink XL,
3Com's ISA bus adapter क्रम Fast Ethernet.  Due to the unique I/O port layout,
it's not practical to पूर्णांकegrate this driver with the other EtherLink drivers.

II. Board-specअगरic settings

The Corkscrew has an EEPROM क्रम configuration, but no special settings are
needed क्रम Linux.

III. Driver operation

The 3c515 series use an पूर्णांकerface that's very similar to the 3c900 "Boomerang"
PCI cards, with the bus master पूर्णांकerface extensively modअगरied to work with
the ISA bus.

The card is capable of full-bus-master transfers with separate
lists of transmit and receive descriptors, similar to the AMD LANCE/PCnet,
DEC Tulip and Intel Speeकरो3.

This driver uses a "RX_COPYBREAK" scheme rather than a fixed पूर्णांकermediate
receive buffer.  This scheme allocates full-sized skbuffs as receive
buffers.  The value RX_COPYBREAK is used as the copying अवरोधpoपूर्णांक: it is
chosen to trade-off the memory wasted by passing the full-sized skbuff to
the queue layer क्रम all frames vs. the copying cost of copying a frame to a
correctly-sized skbuff.


IIIC. Synchronization
The driver runs as two independent, single-thपढ़ोed flows of control.  One
is the send-packet routine, which enक्रमces single-thपढ़ोed use by the netअगर
layer.  The other thपढ़ो is the पूर्णांकerrupt handler, which is single
thपढ़ोed by the hardware and other software.

IV. Notes

Thanks to Terry Murphy of 3Com क्रम providing करोcumentation and a development
board.

The names "Vortex", "Boomerang" and "Corkscrew" are the पूर्णांकernal 3Com
project names.  I use these names to eliminate confusion -- 3Com product
numbers and names are very similar and often confused.

The new chips support both ethernet (1.5K) and FDDI (4.5K) frame sizes!
This driver only supports ethernet frames because of the recent MTU limit
of 1.5K, but the changes to support 4.5K are minimal.
*/

/* Operational definitions.
   These are not used by other compilation units and thus are not
   exported in a ".h" file.

   First the winकरोws.  There are eight रेजिस्टर winकरोws, with the command
   and status रेजिस्टरs available in each.
   */
#घोषणा EL3WINDOW(win_num) outw(SelectWinकरोw + (win_num), ioaddr + EL3_CMD)
#घोषणा EL3_CMD 0x0e
#घोषणा EL3_STATUS 0x0e

/* The top five bits written to EL3_CMD are a command, the lower
   11 bits are the parameter, अगर applicable.
   Note that 11 parameters bits was fine क्रम ethernet, but the new chips
   can handle FDDI length frames (~4500 octets) and now parameters count
   32-bit 'Dwords' rather than octets. */

क्रमागत corkscrew_cmd अणु
	TotalReset = 0 << 11, SelectWinकरोw = 1 << 11, StartCoax = 2 << 11,
	RxDisable = 3 << 11, RxEnable = 4 << 11, RxReset = 5 << 11,
	UpStall = 6 << 11, UpUnstall = (6 << 11) + 1, DownStall = (6 << 11) + 2,
	DownUnstall = (6 << 11) + 3, RxDiscard = 8 << 11, TxEnable = 9 << 11,
	TxDisable = 10 << 11, TxReset = 11 << 11, FakeIntr = 12 << 11,
	AckIntr = 13 << 11, SetIntrEnb = 14 << 11, SetStatusEnb = 15 << 11,
	SetRxFilter = 16 << 11, SetRxThreshold = 17 << 11,
	SetTxThreshold = 18 << 11, SetTxStart = 19 << 11, StartDMAUp = 20 << 11,
	StartDMADown = (20 << 11) + 1, StatsEnable = 21 << 11,
	StatsDisable = 22 << 11, StopCoax = 23 << 11,
पूर्ण;

/* The SetRxFilter command accepts the following classes: */
क्रमागत RxFilter अणु
	RxStation = 1, RxMulticast = 2, RxBroadcast = 4, RxProm = 8
पूर्ण;

/* Bits in the general status रेजिस्टर. */
क्रमागत corkscrew_status अणु
	IntLatch = 0x0001, AdapterFailure = 0x0002, TxComplete = 0x0004,
	TxAvailable = 0x0008, RxComplete = 0x0010, RxEarly = 0x0020,
	IntReq = 0x0040, StatsFull = 0x0080,
	DMADone = 1 << 8, DownComplete = 1 << 9, UpComplete = 1 << 10,
	DMAInProgress = 1 << 11,	/* DMA controller is still busy. */
	CmdInProgress = 1 << 12,	/* EL3_CMD is still busy. */
पूर्ण;

/* Register winकरोw 1 offsets, the winकरोw used in normal operation.
   On the Corkscrew this winकरोw is always mapped at offsets 0x10-0x1f. */
क्रमागत Winकरोw1 अणु
	TX_FIFO = 0x10, RX_FIFO = 0x10, RxErrors = 0x14,
	RxStatus = 0x18, Timer = 0x1A, TxStatus = 0x1B,
	TxFree = 0x1C,		/* Reमुख्यing मुक्त bytes in Tx buffer. */
पूर्ण;
क्रमागत Winकरोw0 अणु
	Wn0IRQ = 0x08,
#अगर defined(CORKSCREW)
	Wn0EepromCmd = 0x200A,	/* Corkscrew EEPROM command रेजिस्टर. */
	Wn0EepromData = 0x200C,	/* Corkscrew EEPROM results रेजिस्टर. */
#अन्यथा
	Wn0EepromCmd = 10,	/* Winकरोw 0: EEPROM command रेजिस्टर. */
	Wn0EepromData = 12,	/* Winकरोw 0: EEPROM results रेजिस्टर. */
#पूर्ण_अगर
पूर्ण;
क्रमागत Win0_EEPROM_bits अणु
	EEPROM_Read = 0x80, EEPROM_WRITE = 0x40, EEPROM_ERASE = 0xC0,
	EEPROM_EWENB = 0x30,	/* Enable erasing/writing क्रम 10 msec. */
	EEPROM_EWDIS = 0x00,	/* Disable EWENB beक्रमe 10 msec समयout. */
पूर्ण;

/* EEPROM locations. */
क्रमागत eeprom_offset अणु
	PhysAddr01 = 0, PhysAddr23 = 1, PhysAddr45 = 2, ModelID = 3,
	EtherLink3ID = 7,
पूर्ण;

क्रमागत Winकरोw3 अणु			/* Winकरोw 3: MAC/config bits. */
	Wn3_Config = 0, Wn3_MAC_Ctrl = 6, Wn3_Options = 8,
पूर्ण;
क्रमागत wn3_config अणु
	Ram_size = 7,
	Ram_width = 8,
	Ram_speed = 0x30,
	Rom_size = 0xc0,
	Ram_split_shअगरt = 16,
	Ram_split = 3 << Ram_split_shअगरt,
	Xcvr_shअगरt = 20,
	Xcvr = 7 << Xcvr_shअगरt,
	Autoselect = 0x1000000,
पूर्ण;

क्रमागत Winकरोw4 अणु
	Wn4_NetDiag = 6, Wn4_Media = 10,	/* Winकरोw 4: Xcvr/media bits. */
पूर्ण;
क्रमागत Win4_Media_bits अणु
	Media_SQE = 0x0008,	/* Enable SQE error counting क्रम AUI. */
	Media_10TP = 0x00C0,	/* Enable link beat and jabber क्रम 10baseT. */
	Media_Lnk = 0x0080,	/* Enable just link beat क्रम 100TX/100FX. */
	Media_LnkBeat = 0x0800,
पूर्ण;
क्रमागत Winकरोw7 अणु			/* Winकरोw 7: Bus Master control. */
	Wn7_MasterAddr = 0, Wn7_MasterLen = 6, Wn7_MasterStatus = 12,
पूर्ण;

/* Boomerang-style bus master control रेजिस्टरs.  Note ISA aliases! */
क्रमागत MasterCtrl अणु
	PktStatus = 0x400, DownListPtr = 0x404, FragAddr = 0x408, FragLen =
	    0x40c,
	TxFreeThreshold = 0x40f, UpPktStatus = 0x410, UpListPtr = 0x418,
पूर्ण;

/* The Rx and Tx descriptor lists.
   Caution Alpha hackers: these types are 32 bits!  Note also the 8 byte
   alignment contraपूर्णांक on tx_ring[] and rx_ring[]. */
काष्ठा boom_rx_desc अणु
	u32 next;
	s32 status;
	u32 addr;
	s32 length;
पूर्ण;

/* Values क्रम the Rx status entry. */
क्रमागत rx_desc_status अणु
	RxDComplete = 0x00008000, RxDError = 0x4000,
	/* See boomerang_rx() क्रम actual error bits */
पूर्ण;

काष्ठा boom_tx_desc अणु
	u32 next;
	s32 status;
	u32 addr;
	s32 length;
पूर्ण;

काष्ठा corkscrew_निजी अणु
	स्थिर अक्षर *product_name;
	काष्ठा list_head list;
	काष्ठा net_device *our_dev;
	/* The Rx and Tx rings are here to keep them quad-word-aligned. */
	काष्ठा boom_rx_desc rx_ring[RX_RING_SIZE];
	काष्ठा boom_tx_desc tx_ring[TX_RING_SIZE];
	/* The addresses of transmit- and receive-in-place skbuffs. */
	काष्ठा sk_buff *rx_skbuff[RX_RING_SIZE];
	काष्ठा sk_buff *tx_skbuff[TX_RING_SIZE];
	अचिन्हित पूर्णांक cur_rx, cur_tx;	/* The next मुक्त ring entry */
	अचिन्हित पूर्णांक dirty_rx, dirty_tx;/* The ring entries to be मुक्त()ed. */
	काष्ठा sk_buff *tx_skb;	/* Packet being eaten by bus master ctrl.  */
	काष्ठा समयr_list समयr;	/* Media selection समयr. */
	पूर्णांक capabilities	;	/* Adapter capabilities word. */
	पूर्णांक options;			/* User-settable misc. driver options. */
	पूर्णांक last_rx_packets;		/* For media स्वतःselection. */
	अचिन्हित पूर्णांक available_media:8,	/* From Wn3_Options */
		media_override:3,	/* Passed-in media type. */
		शेष_media:3,	/* Read from the EEPROM. */
		full_duplex:1, स्वतःselect:1, bus_master:1,	/* Vortex can only करो a fragment bus-m. */
		full_bus_master_tx:1, full_bus_master_rx:1,	/* Boomerang  */
		tx_full:1;
	spinlock_t lock;
	काष्ठा device *dev;
पूर्ण;

/* The action to take with a media selection समयr tick.
   Note that we deviate from the 3Com order by checking 10base2 beक्रमe AUI.
 */
क्रमागत xcvr_types अणु
	XCVR_10baseT = 0, XCVR_AUI, XCVR_10baseTOnly, XCVR_10base2, XCVR_100baseTx,
	XCVR_100baseFx, XCVR_MII = 6, XCVR_Default = 8,
पूर्ण;

अटल काष्ठा media_table अणु
	अक्षर *name;
	अचिन्हित पूर्णांक media_bits:16,	/* Bits to set in Wn4_Media रेजिस्टर. */
		mask:8,			/* The transceiver-present bit in Wn3_Config. */
		next:8;			/* The media type to try next. */
	लघु रुको;			/* Time beक्रमe we check media status. */
पूर्ण media_tbl[] = अणु
	अणु "10baseT", Media_10TP, 0x08, XCVR_10base2, (14 * HZ) / 10 पूर्ण,
	अणु "10Mbs AUI", Media_SQE, 0x20, XCVR_Default, (1 * HZ) / 10पूर्ण,
	अणु "undefined", 0, 0x80, XCVR_10baseT, 10000पूर्ण,
	अणु "10base2", 0, 0x10, XCVR_AUI, (1 * HZ) / 10पूर्ण,
	अणु "100baseTX", Media_Lnk, 0x02, XCVR_100baseFx, (14 * HZ) / 10पूर्ण,
	अणु "100baseFX", Media_Lnk, 0x04, XCVR_MII, (14 * HZ) / 10पूर्ण,
	अणु "MII", 0, 0x40, XCVR_10baseT, 3 * HZपूर्ण,
	अणु "undefined", 0, 0x01, XCVR_10baseT, 10000पूर्ण,
	अणु "Default", 0, 0xFF, XCVR_10baseT, 10000पूर्ण,
पूर्ण;

#अगर_घोषित __ISAPNP__
अटल काष्ठा isapnp_device_id corkscrew_isapnp_adapters[] = अणु
	अणु	ISAPNP_ANY_ID, ISAPNP_ANY_ID,
		ISAPNP_VENDOR('T', 'C', 'M'), ISAPNP_FUNCTION(0x5051),
		(दीर्घ) "3Com Fast EtherLink ISA" पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;

MODULE_DEVICE_TABLE(isapnp, corkscrew_isapnp_adapters);

अटल पूर्णांक nopnp;
#पूर्ण_अगर /* __ISAPNP__ */

अटल काष्ठा net_device *corkscrew_scan(पूर्णांक unit);
अटल पूर्णांक corkscrew_setup(काष्ठा net_device *dev, पूर्णांक ioaddr,
			    काष्ठा pnp_dev *idev, पूर्णांक card_number);
अटल पूर्णांक corkscrew_खोलो(काष्ठा net_device *dev);
अटल व्योम corkscrew_समयr(काष्ठा समयr_list *t);
अटल netdev_tx_t corkscrew_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev);
अटल पूर्णांक corkscrew_rx(काष्ठा net_device *dev);
अटल व्योम corkscrew_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल पूर्णांक boomerang_rx(काष्ठा net_device *dev);
अटल irqवापस_t corkscrew_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक corkscrew_बंद(काष्ठा net_device *dev);
अटल व्योम update_stats(पूर्णांक addr, काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *corkscrew_get_stats(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;


/*
   Unक्रमtunately maximizing the shared code between the पूर्णांकegrated and
   module version of the driver results in a complicated set of initialization
   procedures.
   init_module() -- modules /  tc59x_init()  -- built-in
		The wrappers क्रम corkscrew_scan()
   corkscrew_scan()  		 The common routine that scans क्रम PCI and EISA cards
   corkscrew_found_device() Allocate a device काष्ठाure when we find a card.
					Dअगरferent versions exist क्रम modules and built-in.
   corkscrew_probe1()		Fill in the device काष्ठाure -- this is separated
					so that the modules code can put it in dev->init.
*/
/* This driver uses 'options' to pass the media type, full-duplex flag, etc. */
/* Note: this is the only limit on the number of cards supported!! */
अटल पूर्णांक options[MAX_UNITS] = अणु -1, -1, -1, -1, -1, -1, -1, -1, पूर्ण;

#अगर_घोषित MODULE
अटल पूर्णांक debug = -1;

module_param(debug, पूर्णांक, 0);
module_param_array(options, पूर्णांक, शून्य, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "3c515 debug level (0-6)");
MODULE_PARM_DESC(options, "3c515: Bits 0-2: media type, bit 3: full duplex, bit 4: bus mastering");
MODULE_PARM_DESC(rx_copyअवरोध, "3c515 copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "3c515 maximum events handled per interrupt");

/* A list of all installed Vortex devices, क्रम removing the driver module. */
/* we will need locking (and refcounting) अगर we ever use it क्रम more */
अटल LIST_HEAD(root_corkscrew_dev);

पूर्णांक init_module(व्योम)
अणु
	पूर्णांक found = 0;
	अगर (debug >= 0)
		corkscrew_debug = debug;
	जबतक (corkscrew_scan(-1))
		found++;
	वापस found ? 0 : -ENODEV;
पूर्ण

#अन्यथा
काष्ठा net_device *tc515_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev = corkscrew_scan(unit);

	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	वापस dev;
पूर्ण
#पूर्ण_अगर				/* not MODULE */

अटल पूर्णांक check_device(अचिन्हित ioaddr)
अणु
	पूर्णांक समयr;

	अगर (!request_region(ioaddr, CORKSCREW_TOTAL_SIZE, "3c515"))
		वापस 0;
	/* Check the resource configuration क्रम a matching ioaddr. */
	अगर ((inw(ioaddr + 0x2002) & 0x1f0) != (ioaddr & 0x1f0)) अणु
		release_region(ioaddr, CORKSCREW_TOTAL_SIZE);
		वापस 0;
	पूर्ण
	/* Verअगरy by पढ़ोing the device ID from the EEPROM. */
	outw(EEPROM_Read + 7, ioaddr + Wn0EepromCmd);
	/* Pause क्रम at least 162 us. क्रम the पढ़ो to take place. */
	क्रम (समयr = 4; समयr >= 0; समयr--) अणु
		udelay(162);
		अगर ((inw(ioaddr + Wn0EepromCmd) & 0x0200) == 0)
			अवरोध;
	पूर्ण
	अगर (inw(ioaddr + Wn0EepromData) != 0x6d50) अणु
		release_region(ioaddr, CORKSCREW_TOTAL_SIZE);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम cleanup_card(काष्ठा net_device *dev)
अणु
	काष्ठा corkscrew_निजी *vp = netdev_priv(dev);
	list_del_init(&vp->list);
	अगर (dev->dma)
		मुक्त_dma(dev->dma);
	outw(TotalReset, dev->base_addr + EL3_CMD);
	release_region(dev->base_addr, CORKSCREW_TOTAL_SIZE);
	अगर (vp->dev)
		pnp_device_detach(to_pnp_dev(vp->dev));
पूर्ण

अटल काष्ठा net_device *corkscrew_scan(पूर्णांक unit)
अणु
	काष्ठा net_device *dev;
	अटल पूर्णांक cards_found = 0;
	अटल पूर्णांक ioaddr;
	पूर्णांक err;
#अगर_घोषित __ISAPNP__
	लघु i;
	अटल पूर्णांक pnp_cards;
#पूर्ण_अगर

	dev = alloc_etherdev(माप(काष्ठा corkscrew_निजी));
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	अगर (unit >= 0) अणु
		प्र_लिखो(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
	पूर्ण

#अगर_घोषित __ISAPNP__
	अगर(nopnp == 1)
		जाओ no_pnp;
	क्रम(i=0; corkscrew_isapnp_adapters[i].venकरोr != 0; i++) अणु
		काष्ठा pnp_dev *idev = शून्य;
		पूर्णांक irq;
		जबतक((idev = pnp_find_dev(शून्य,
					   corkscrew_isapnp_adapters[i].venकरोr,
					   corkscrew_isapnp_adapters[i].function,
					   idev))) अणु

			अगर (pnp_device_attach(idev) < 0)
				जारी;
			अगर (pnp_activate_dev(idev) < 0) अणु
				pr_warn("pnp activate failed (out of resources?)\n");
				pnp_device_detach(idev);
				जारी;
			पूर्ण
			अगर (!pnp_port_valid(idev, 0) || !pnp_irq_valid(idev, 0)) अणु
				pnp_device_detach(idev);
				जारी;
			पूर्ण
			ioaddr = pnp_port_start(idev, 0);
			irq = pnp_irq(idev, 0);
			अगर (!check_device(ioaddr)) अणु
				pnp_device_detach(idev);
				जारी;
			पूर्ण
			अगर(corkscrew_debug)
				pr_debug("ISAPNP reports %s at i/o 0x%x, irq %d\n",
					(अक्षर*) corkscrew_isapnp_adapters[i].driver_data, ioaddr, irq);
			pr_info("3c515 Resource configuration register %#4.4x, DCR %4.4x.\n",
		     		inl(ioaddr + 0x2002), inw(ioaddr + 0x2000));
			/* irq = inw(ioaddr + 0x2002) & 15; */ /* Use the irq from isapnp */
			SET_NETDEV_DEV(dev, &idev->dev);
			pnp_cards++;
			err = corkscrew_setup(dev, ioaddr, idev, cards_found++);
			अगर (!err)
				वापस dev;
			cleanup_card(dev);
		पूर्ण
	पूर्ण
no_pnp:
#पूर्ण_अगर /* __ISAPNP__ */

	/* Check all locations on the ISA bus -- evil! */
	क्रम (ioaddr = 0x100; ioaddr < 0x400; ioaddr += 0x20) अणु
		अगर (!check_device(ioaddr))
			जारी;

		pr_info("3c515 Resource configuration register %#4.4x, DCR %4.4x.\n",
		     inl(ioaddr + 0x2002), inw(ioaddr + 0x2000));
		err = corkscrew_setup(dev, ioaddr, शून्य, cards_found++);
		अगर (!err)
			वापस dev;
		cleanup_card(dev);
	पूर्ण
	मुक्त_netdev(dev);
	वापस शून्य;
पूर्ण


अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= corkscrew_खोलो,
	.nकरो_stop		= corkscrew_बंद,
	.nकरो_start_xmit		= corkscrew_start_xmit,
	.nकरो_tx_समयout		= corkscrew_समयout,
	.nकरो_get_stats		= corkscrew_get_stats,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;


अटल पूर्णांक corkscrew_setup(काष्ठा net_device *dev, पूर्णांक ioaddr,
			    काष्ठा pnp_dev *idev, पूर्णांक card_number)
अणु
	काष्ठा corkscrew_निजी *vp = netdev_priv(dev);
	अचिन्हित पूर्णांक eeprom[0x40], checksum = 0;	/* EEPROM contents */
	पूर्णांक i;
	पूर्णांक irq;

#अगर_घोषित __ISAPNP__
	अगर (idev) अणु
		irq = pnp_irq(idev, 0);
		vp->dev = &idev->dev;
	पूर्ण अन्यथा अणु
		irq = inw(ioaddr + 0x2002) & 15;
	पूर्ण
#अन्यथा
	irq = inw(ioaddr + 0x2002) & 15;
#पूर्ण_अगर

	dev->base_addr = ioaddr;
	dev->irq = irq;
	dev->dma = inw(ioaddr + 0x2000) & 7;
	vp->product_name = "3c515";
	vp->options = dev->mem_start;
	vp->our_dev = dev;

	अगर (!vp->options) अणु
		 अगर (card_number >= MAX_UNITS)
			vp->options = -1;
		अन्यथा
			vp->options = options[card_number];
	पूर्ण

	अगर (vp->options >= 0) अणु
		vp->media_override = vp->options & 7;
		अगर (vp->media_override == 2)
			vp->media_override = 0;
		vp->full_duplex = (vp->options & 8) ? 1 : 0;
		vp->bus_master = (vp->options & 16) ? 1 : 0;
	पूर्ण अन्यथा अणु
		vp->media_override = 7;
		vp->full_duplex = 0;
		vp->bus_master = 0;
	पूर्ण
#अगर_घोषित MODULE
	list_add(&vp->list, &root_corkscrew_dev);
#पूर्ण_अगर

	pr_info("%s: 3Com %s at %#3x,", dev->name, vp->product_name, ioaddr);

	spin_lock_init(&vp->lock);

	समयr_setup(&vp->समयr, corkscrew_समयr, 0);

	/* Read the station address from the EEPROM. */
	EL3WINDOW(0);
	क्रम (i = 0; i < 0x18; i++) अणु
		__be16 *phys_addr = (__be16 *) dev->dev_addr;
		पूर्णांक समयr;
		outw(EEPROM_Read + i, ioaddr + Wn0EepromCmd);
		/* Pause क्रम at least 162 us. क्रम the पढ़ो to take place. */
		क्रम (समयr = 4; समयr >= 0; समयr--) अणु
			udelay(162);
			अगर ((inw(ioaddr + Wn0EepromCmd) & 0x0200) == 0)
				अवरोध;
		पूर्ण
		eeprom[i] = inw(ioaddr + Wn0EepromData);
		checksum ^= eeprom[i];
		अगर (i < 3)
			phys_addr[i] = htons(eeprom[i]);
	पूर्ण
	checksum = (checksum ^ (checksum >> 8)) & 0xff;
	अगर (checksum != 0x00)
		pr_cont(" ***INVALID CHECKSUM %4.4x*** ", checksum);
	pr_cont(" %pM", dev->dev_addr);
	अगर (eeprom[16] == 0x11c7) अणु	/* Corkscrew */
		अगर (request_dma(dev->dma, "3c515")) अणु
			pr_cont(", DMA %d allocation failed", dev->dma);
			dev->dma = 0;
		पूर्ण अन्यथा
			pr_cont(", DMA %d", dev->dma);
	पूर्ण
	pr_cont(", IRQ %d\n", dev->irq);
	/* Tell them about an invalid IRQ. */
	अगर (corkscrew_debug && (dev->irq <= 0 || dev->irq > 15))
		pr_warn(" *** Warning: this IRQ is unlikely to work! ***\n");

	अणु
		अटल स्थिर अक्षर * स्थिर ram_split[] = अणु
			"5:3", "3:1", "1:1", "3:5"
		पूर्ण;
		__u32 config;
		EL3WINDOW(3);
		vp->available_media = inw(ioaddr + Wn3_Options);
		config = inl(ioaddr + Wn3_Config);
		अगर (corkscrew_debug > 1)
			pr_info("  Internal config register is %4.4x, transceivers %#x.\n",
				config, inw(ioaddr + Wn3_Options));
		pr_info("  %dK %s-wide RAM %s Rx:Tx split, %s%s interface.\n",
			8 << config & Ram_size,
			config & Ram_width ? "word" : "byte",
			ram_split[(config & Ram_split) >> Ram_split_shअगरt],
			config & Autoselect ? "autoselect/" : "",
			media_tbl[(config & Xcvr) >> Xcvr_shअगरt].name);
		vp->शेष_media = (config & Xcvr) >> Xcvr_shअगरt;
		vp->स्वतःselect = config & Autoselect ? 1 : 0;
		dev->अगर_port = vp->शेष_media;
	पूर्ण
	अगर (vp->media_override != 7) अणु
		pr_info("  Media override to transceiver type %d (%s).\n",
		       vp->media_override,
		       media_tbl[vp->media_override].name);
		dev->अगर_port = vp->media_override;
	पूर्ण

	vp->capabilities = eeprom[16];
	vp->full_bus_master_tx = (vp->capabilities & 0x20) ? 1 : 0;
	/* Rx is broken at 10mbps, so we always disable it. */
	/* vp->full_bus_master_rx = 0; */
	vp->full_bus_master_rx = (vp->capabilities & 0x20) ? 1 : 0;

	/* The 3c51x-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &netdev_ops;
	dev->watchकरोg_समयo = (400 * HZ) / 1000;
	dev->ethtool_ops = &netdev_ethtool_ops;

	वापस रेजिस्टर_netdev(dev);
पूर्ण


अटल पूर्णांक corkscrew_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	काष्ठा corkscrew_निजी *vp = netdev_priv(dev);
	bool armसमयr = false;
	__u32 config;
	पूर्णांक i;

	/* Beक्रमe initializing select the active media port. */
	EL3WINDOW(3);
	अगर (vp->full_duplex)
		outb(0x20, ioaddr + Wn3_MAC_Ctrl);	/* Set the full-duplex bit. */
	config = inl(ioaddr + Wn3_Config);

	अगर (vp->media_override != 7) अणु
		अगर (corkscrew_debug > 1)
			pr_info("%s: Media override to transceiver %d (%s).\n",
				dev->name, vp->media_override,
				media_tbl[vp->media_override].name);
		dev->अगर_port = vp->media_override;
	पूर्ण अन्यथा अगर (vp->स्वतःselect) अणु
		/* Find first available media type, starting with 100baseTx. */
		dev->अगर_port = 4;
		जबतक (!(vp->available_media & media_tbl[dev->अगर_port].mask))
			dev->अगर_port = media_tbl[dev->अगर_port].next;

		अगर (corkscrew_debug > 1)
			pr_debug("%s: Initial media type %s.\n",
			       dev->name, media_tbl[dev->अगर_port].name);
		armसमयr = true;
	पूर्ण अन्यथा
		dev->अगर_port = vp->शेष_media;

	config = (config & ~Xcvr) | (dev->अगर_port << Xcvr_shअगरt);
	outl(config, ioaddr + Wn3_Config);

	अगर (corkscrew_debug > 1) अणु
		pr_debug("%s: corkscrew_open() InternalConfig %8.8x.\n",
		       dev->name, config);
	पूर्ण

	outw(TxReset, ioaddr + EL3_CMD);
	क्रम (i = 20; i >= 0; i--)
		अगर (!(inw(ioaddr + EL3_STATUS) & CmdInProgress))
			अवरोध;

	outw(RxReset, ioaddr + EL3_CMD);
	/* Wait a few ticks क्रम the RxReset command to complete. */
	क्रम (i = 20; i >= 0; i--)
		अगर (!(inw(ioaddr + EL3_STATUS) & CmdInProgress))
			अवरोध;

	outw(SetStatusEnb | 0x00, ioaddr + EL3_CMD);

	/* Use the now-standard shared IRQ implementation. */
	अगर (vp->capabilities == 0x11c7) अणु
		/* Corkscrew: Cannot share ISA resources. */
		अगर (dev->irq == 0 ||
		    dev->dma == 0 ||
		    request_irq(dev->irq, corkscrew_पूर्णांकerrupt, 0,
				vp->product_name, dev))
			वापस -EAGAIN;
		enable_dma(dev->dma);
		set_dma_mode(dev->dma, DMA_MODE_CASCADE);
	पूर्ण अन्यथा अगर (request_irq(dev->irq, corkscrew_पूर्णांकerrupt, IRQF_SHARED,
			       vp->product_name, dev)) अणु
		वापस -EAGAIN;
	पूर्ण

	अगर (armसमयr)
		mod_समयr(&vp->समयr, jअगरfies + media_tbl[dev->अगर_port].रुको);

	अगर (corkscrew_debug > 1) अणु
		EL3WINDOW(4);
		pr_debug("%s: corkscrew_open() irq %d media status %4.4x.\n",
		       dev->name, dev->irq, inw(ioaddr + Wn4_Media));
	पूर्ण

	/* Set the station address and mask in winकरोw 2 each समय खोलोed. */
	EL3WINDOW(2);
	क्रम (i = 0; i < 6; i++)
		outb(dev->dev_addr[i], ioaddr + i);
	क्रम (; i < 12; i += 2)
		outw(0, ioaddr + i);

	अगर (dev->अगर_port == 3)
		/* Start the thinnet transceiver. We should really रुको 50ms... */
		outw(StartCoax, ioaddr + EL3_CMD);
	EL3WINDOW(4);
	outw((inw(ioaddr + Wn4_Media) & ~(Media_10TP | Media_SQE)) |
	     media_tbl[dev->अगर_port].media_bits, ioaddr + Wn4_Media);

	/* Switch to the stats winकरोw, and clear all stats by पढ़ोing. */
	outw(StatsDisable, ioaddr + EL3_CMD);
	EL3WINDOW(6);
	क्रम (i = 0; i < 10; i++)
		inb(ioaddr + i);
	inw(ioaddr + 10);
	inw(ioaddr + 12);
	/* New: On the Vortex we must also clear the BadSSD counter. */
	EL3WINDOW(4);
	inb(ioaddr + 12);
	/* ..and on the Boomerang we enable the extra statistics bits. */
	outw(0x0040, ioaddr + Wn4_NetDiag);

	/* Switch to रेजिस्टर set 7 क्रम normal use. */
	EL3WINDOW(7);

	अगर (vp->full_bus_master_rx) अणु	/* Boomerang bus master. */
		vp->cur_rx = vp->dirty_rx = 0;
		अगर (corkscrew_debug > 2)
			pr_debug("%s:  Filling in the Rx ring.\n", dev->name);
		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			काष्ठा sk_buff *skb;
			अगर (i < (RX_RING_SIZE - 1))
				vp->rx_ring[i].next =
				    isa_virt_to_bus(&vp->rx_ring[i + 1]);
			अन्यथा
				vp->rx_ring[i].next = 0;
			vp->rx_ring[i].status = 0;	/* Clear complete bit. */
			vp->rx_ring[i].length = PKT_BUF_SZ | 0x80000000;
			skb = netdev_alloc_skb(dev, PKT_BUF_SZ);
			vp->rx_skbuff[i] = skb;
			अगर (skb == शून्य)
				अवरोध;	/* Bad news!  */
			skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
			vp->rx_ring[i].addr = isa_virt_to_bus(skb->data);
		पूर्ण
		अगर (i != 0)
			vp->rx_ring[i - 1].next =
				isa_virt_to_bus(&vp->rx_ring[0]);	/* Wrap the ring. */
		outl(isa_virt_to_bus(&vp->rx_ring[0]), ioaddr + UpListPtr);
	पूर्ण
	अगर (vp->full_bus_master_tx) अणु	/* Boomerang bus master Tx. */
		vp->cur_tx = vp->dirty_tx = 0;
		outb(PKT_BUF_SZ >> 8, ioaddr + TxFreeThreshold);	/* Room क्रम a packet. */
		/* Clear the Tx ring. */
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			vp->tx_skbuff[i] = शून्य;
		outl(0, ioaddr + DownListPtr);
	पूर्ण
	/* Set receiver mode: presumably accept b-हाल and phys addr only. */
	set_rx_mode(dev);
	outw(StatsEnable, ioaddr + EL3_CMD);	/* Turn on statistics. */

	netअगर_start_queue(dev);

	outw(RxEnable, ioaddr + EL3_CMD);	/* Enable the receiver. */
	outw(TxEnable, ioaddr + EL3_CMD);	/* Enable transmitter. */
	/* Allow status bits to be seen. */
	outw(SetStatusEnb | AdapterFailure | IntReq | StatsFull |
	     (vp->full_bus_master_tx ? DownComplete : TxAvailable) |
	     (vp->full_bus_master_rx ? UpComplete : RxComplete) |
	     (vp->bus_master ? DMADone : 0), ioaddr + EL3_CMD);
	/* Ack all pending events, and set active indicator mask. */
	outw(AckIntr | IntLatch | TxAvailable | RxEarly | IntReq,
	     ioaddr + EL3_CMD);
	outw(SetIntrEnb | IntLatch | TxAvailable | RxComplete | StatsFull
	     | (vp->bus_master ? DMADone : 0) | UpComplete | DownComplete,
	     ioaddr + EL3_CMD);

	वापस 0;
पूर्ण

अटल व्योम corkscrew_समयr(काष्ठा समयr_list *t)
अणु
#अगर_घोषित AUTOMEDIA
	काष्ठा corkscrew_निजी *vp = from_समयr(vp, t, समयr);
	काष्ठा net_device *dev = vp->our_dev;
	पूर्णांक ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ok = 0;

	अगर (corkscrew_debug > 1)
		pr_debug("%s: Media selection timer tick happened, %s.\n",
		       dev->name, media_tbl[dev->अगर_port].name);

	spin_lock_irqsave(&vp->lock, flags);

	अणु
		पूर्णांक old_winकरोw = inw(ioaddr + EL3_CMD) >> 13;
		पूर्णांक media_status;
		EL3WINDOW(4);
		media_status = inw(ioaddr + Wn4_Media);
		चयन (dev->अगर_port) अणु
		हाल 0:
		हाल 4:
		हाल 5:	/* 10baseT, 100baseTX, 100baseFX  */
			अगर (media_status & Media_LnkBeat) अणु
				ok = 1;
				अगर (corkscrew_debug > 1)
					pr_debug("%s: Media %s has link beat, %x.\n",
						dev->name,
						media_tbl[dev->अगर_port].name,
						media_status);
			पूर्ण अन्यथा अगर (corkscrew_debug > 1)
				pr_debug("%s: Media %s is has no link beat, %x.\n",
					dev->name,
					media_tbl[dev->अगर_port].name,
					media_status);

			अवरोध;
		शेष:	/* Other media types handled by Tx समयouts. */
			अगर (corkscrew_debug > 1)
				pr_debug("%s: Media %s is has no indication, %x.\n",
					dev->name,
					media_tbl[dev->अगर_port].name,
					media_status);
			ok = 1;
		पूर्ण
		अगर (!ok) अणु
			__u32 config;

			करो अणु
				dev->अगर_port =
				    media_tbl[dev->अगर_port].next;
			पूर्ण
			जबतक (!(vp->available_media & media_tbl[dev->अगर_port].mask));

			अगर (dev->अगर_port == 8) अणु	/* Go back to शेष. */
				dev->अगर_port = vp->शेष_media;
				अगर (corkscrew_debug > 1)
					pr_debug("%s: Media selection failing, using default %s port.\n",
						dev->name,
						media_tbl[dev->अगर_port].name);
			पूर्ण अन्यथा अणु
				अगर (corkscrew_debug > 1)
					pr_debug("%s: Media selection failed, now trying %s port.\n",
						dev->name,
						media_tbl[dev->अगर_port].name);
				vp->समयr.expires = jअगरfies + media_tbl[dev->अगर_port].रुको;
				add_समयr(&vp->समयr);
			पूर्ण
			outw((media_status & ~(Media_10TP | Media_SQE)) |
			     media_tbl[dev->अगर_port].media_bits,
			     ioaddr + Wn4_Media);

			EL3WINDOW(3);
			config = inl(ioaddr + Wn3_Config);
			config = (config & ~Xcvr) | (dev->अगर_port << Xcvr_shअगरt);
			outl(config, ioaddr + Wn3_Config);

			outw(dev->अगर_port == 3 ? StartCoax : StopCoax,
			     ioaddr + EL3_CMD);
		पूर्ण
		EL3WINDOW(old_winकरोw);
	पूर्ण

	spin_unlock_irqrestore(&vp->lock, flags);
	अगर (corkscrew_debug > 1)
		pr_debug("%s: Media selection timer finished, %s.\n",
		       dev->name, media_tbl[dev->अगर_port].name);

#पूर्ण_अगर				/* AUTOMEDIA */
पूर्ण

अटल व्योम corkscrew_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	पूर्णांक i;
	काष्ठा corkscrew_निजी *vp = netdev_priv(dev);
	पूर्णांक ioaddr = dev->base_addr;

	pr_warn("%s: transmit timed out, tx_status %2.2x status %4.4x\n",
		dev->name, inb(ioaddr + TxStatus),
		inw(ioaddr + EL3_STATUS));
	/* Slight code bloat to be user मित्रly. */
	अगर ((inb(ioaddr + TxStatus) & 0x88) == 0x88)
		pr_warn("%s: Transmitter encountered 16 collisions -- network cable problem?\n",
			dev->name);
#अगर_अघोषित final_version
	pr_debug("  Flags; bus-master %d, full %d; dirty %d current %d.\n",
	       vp->full_bus_master_tx, vp->tx_full, vp->dirty_tx,
	       vp->cur_tx);
	pr_debug("  Down list %8.8x vs. %p.\n", inl(ioaddr + DownListPtr),
	       &vp->tx_ring[0]);
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		pr_debug("  %d: %p  length %8.8x status %8.8x\n", i,
		       &vp->tx_ring[i],
		       vp->tx_ring[i].length, vp->tx_ring[i].status);
	पूर्ण
#पूर्ण_अगर
	/* Issue TX_RESET and TX_START commands. */
	outw(TxReset, ioaddr + EL3_CMD);
	क्रम (i = 20; i >= 0; i--)
		अगर (!(inw(ioaddr + EL3_STATUS) & CmdInProgress))
			अवरोध;
	outw(TxEnable, ioaddr + EL3_CMD);
	netअगर_trans_update(dev); /* prevent tx समयout */
	dev->stats.tx_errors++;
	dev->stats.tx_dropped++;
	netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t corkscrew_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	काष्ठा corkscrew_निजी *vp = netdev_priv(dev);
	पूर्णांक ioaddr = dev->base_addr;

	/* Block a समयr-based transmit from overlapping. */

	netअगर_stop_queue(dev);

	अगर (vp->full_bus_master_tx) अणु	/* BOOMERANG bus-master */
		/* Calculate the next Tx descriptor entry. */
		पूर्णांक entry = vp->cur_tx % TX_RING_SIZE;
		काष्ठा boom_tx_desc *prev_entry;
		अचिन्हित दीर्घ flags;
		पूर्णांक i;

		अगर (vp->tx_full)	/* No room to transmit with */
			वापस NETDEV_TX_BUSY;
		अगर (vp->cur_tx != 0)
			prev_entry = &vp->tx_ring[(vp->cur_tx - 1) % TX_RING_SIZE];
		अन्यथा
			prev_entry = शून्य;
		अगर (corkscrew_debug > 3)
			pr_debug("%s: Trying to send a packet, Tx index %d.\n",
				dev->name, vp->cur_tx);
		/* vp->tx_full = 1; */
		vp->tx_skbuff[entry] = skb;
		vp->tx_ring[entry].next = 0;
		vp->tx_ring[entry].addr = isa_virt_to_bus(skb->data);
		vp->tx_ring[entry].length = skb->len | 0x80000000;
		vp->tx_ring[entry].status = skb->len | 0x80000000;

		spin_lock_irqsave(&vp->lock, flags);
		outw(DownStall, ioaddr + EL3_CMD);
		/* Wait क्रम the stall to complete. */
		क्रम (i = 20; i >= 0; i--)
			अगर ((inw(ioaddr + EL3_STATUS) & CmdInProgress) == 0)
				अवरोध;
		अगर (prev_entry)
			prev_entry->next = isa_virt_to_bus(&vp->tx_ring[entry]);
		अगर (inl(ioaddr + DownListPtr) == 0) अणु
			outl(isa_virt_to_bus(&vp->tx_ring[entry]),
			     ioaddr + DownListPtr);
			queued_packet++;
		पूर्ण
		outw(DownUnstall, ioaddr + EL3_CMD);
		spin_unlock_irqrestore(&vp->lock, flags);

		vp->cur_tx++;
		अगर (vp->cur_tx - vp->dirty_tx > TX_RING_SIZE - 1)
			vp->tx_full = 1;
		अन्यथा अणु		/* Clear previous पूर्णांकerrupt enable. */
			अगर (prev_entry)
				prev_entry->status &= ~0x80000000;
			netअगर_wake_queue(dev);
		पूर्ण
		वापस NETDEV_TX_OK;
	पूर्ण
	/* Put out the द्विगुनword header... */
	outl(skb->len, ioaddr + TX_FIFO);
	dev->stats.tx_bytes += skb->len;
#अगर_घोषित VORTEX_BUS_MASTER
	अगर (vp->bus_master) अणु
		/* Set the bus-master controller to transfer the packet. */
		outl((पूर्णांक) (skb->data), ioaddr + Wn7_MasterAddr);
		outw((skb->len + 3) & ~3, ioaddr + Wn7_MasterLen);
		vp->tx_skb = skb;
		outw(StartDMADown, ioaddr + EL3_CMD);
		/* queue will be woken at the DMADone पूर्णांकerrupt. */
	पूर्ण अन्यथा अणु
		/* ... and the packet rounded to a द्विगुनword. */
		outsl(ioaddr + TX_FIFO, skb->data, (skb->len + 3) >> 2);
		dev_kमुक्त_skb(skb);
		अगर (inw(ioaddr + TxFree) > 1536) अणु
			netअगर_wake_queue(dev);
		पूर्ण अन्यथा
			/* Interrupt us when the FIFO has room क्रम max-sized packet. */
			outw(SetTxThreshold + (1536 >> 2),
			     ioaddr + EL3_CMD);
	पूर्ण
#अन्यथा
	/* ... and the packet rounded to a द्विगुनword. */
	outsl(ioaddr + TX_FIFO, skb->data, (skb->len + 3) >> 2);
	dev_kमुक्त_skb(skb);
	अगर (inw(ioaddr + TxFree) > 1536) अणु
		netअगर_wake_queue(dev);
	पूर्ण अन्यथा
		/* Interrupt us when the FIFO has room क्रम max-sized packet. */
		outw(SetTxThreshold + (1536 >> 2), ioaddr + EL3_CMD);
#पूर्ण_अगर				/* bus master */


	/* Clear the Tx status stack. */
	अणु
		लघु tx_status;
		पूर्णांक i = 4;

		जबतक (--i > 0 && (tx_status = inb(ioaddr + TxStatus)) > 0) अणु
			अगर (tx_status & 0x3C) अणु	/* A Tx-disabling error occurred.  */
				अगर (corkscrew_debug > 2)
					pr_debug("%s: Tx error, status %2.2x.\n",
						dev->name, tx_status);
				अगर (tx_status & 0x04)
					dev->stats.tx_fअगरo_errors++;
				अगर (tx_status & 0x38)
					dev->stats.tx_पातed_errors++;
				अगर (tx_status & 0x30) अणु
					पूर्णांक j;
					outw(TxReset, ioaddr + EL3_CMD);
					क्रम (j = 20; j >= 0; j--)
						अगर (!(inw(ioaddr + EL3_STATUS) & CmdInProgress))
							अवरोध;
				पूर्ण
				outw(TxEnable, ioaddr + EL3_CMD);
			पूर्ण
			outb(0x00, ioaddr + TxStatus);	/* Pop the status stack. */
		पूर्ण
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */

अटल irqवापस_t corkscrew_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	/* Use the now-standard shared IRQ implementation. */
	काष्ठा net_device *dev = dev_id;
	काष्ठा corkscrew_निजी *lp = netdev_priv(dev);
	पूर्णांक ioaddr, status;
	पूर्णांक latency;
	पूर्णांक i = max_पूर्णांकerrupt_work;

	ioaddr = dev->base_addr;
	latency = inb(ioaddr + Timer);

	spin_lock(&lp->lock);

	status = inw(ioaddr + EL3_STATUS);

	अगर (corkscrew_debug > 4)
		pr_debug("%s: interrupt, status %4.4x, timer %d.\n",
			dev->name, status, latency);
	अगर ((status & 0xE000) != 0xE000) अणु
		अटल पूर्णांक करोnedidthis;
		/* Some पूर्णांकerrupt controllers store a bogus पूर्णांकerrupt from boot-समय.
		   Ignore a single early पूर्णांकerrupt, but करोn't hang the machine क्रम
		   other पूर्णांकerrupt problems. */
		अगर (करोnedidthis++ > 100) अणु
			pr_err("%s: Bogus interrupt, bailing. Status %4.4x, start=%d.\n",
				   dev->name, status, netअगर_running(dev));
			मुक्त_irq(dev->irq, dev);
			dev->irq = -1;
		पूर्ण
	पूर्ण

	करो अणु
		अगर (corkscrew_debug > 5)
			pr_debug("%s: In interrupt loop, status %4.4x.\n",
			       dev->name, status);
		अगर (status & RxComplete)
			corkscrew_rx(dev);

		अगर (status & TxAvailable) अणु
			अगर (corkscrew_debug > 5)
				pr_debug("	TX room bit was handled.\n");
			/* There's room in the FIFO क्रम a full-sized packet. */
			outw(AckIntr | TxAvailable, ioaddr + EL3_CMD);
			netअगर_wake_queue(dev);
		पूर्ण
		अगर (status & DownComplete) अणु
			अचिन्हित पूर्णांक dirty_tx = lp->dirty_tx;

			जबतक (lp->cur_tx - dirty_tx > 0) अणु
				पूर्णांक entry = dirty_tx % TX_RING_SIZE;
				अगर (inl(ioaddr + DownListPtr) == isa_virt_to_bus(&lp->tx_ring[entry]))
					अवरोध;	/* It still hasn't been processed. */
				अगर (lp->tx_skbuff[entry]) अणु
					dev_consume_skb_irq(lp->tx_skbuff[entry]);
					lp->tx_skbuff[entry] = शून्य;
				पूर्ण
				dirty_tx++;
			पूर्ण
			lp->dirty_tx = dirty_tx;
			outw(AckIntr | DownComplete, ioaddr + EL3_CMD);
			अगर (lp->tx_full && (lp->cur_tx - dirty_tx <= TX_RING_SIZE - 1)) अणु
				lp->tx_full = 0;
				netअगर_wake_queue(dev);
			पूर्ण
		पूर्ण
#अगर_घोषित VORTEX_BUS_MASTER
		अगर (status & DMADone) अणु
			outw(0x1000, ioaddr + Wn7_MasterStatus);	/* Ack the event. */
			dev_consume_skb_irq(lp->tx_skb);	/* Release the transferred buffer */
			netअगर_wake_queue(dev);
		पूर्ण
#पूर्ण_अगर
		अगर (status & UpComplete) अणु
			boomerang_rx(dev);
			outw(AckIntr | UpComplete, ioaddr + EL3_CMD);
		पूर्ण
		अगर (status & (AdapterFailure | RxEarly | StatsFull)) अणु
			/* Handle all uncommon पूर्णांकerrupts at once. */
			अगर (status & RxEarly) अणु	/* Rx early is unused. */
				corkscrew_rx(dev);
				outw(AckIntr | RxEarly, ioaddr + EL3_CMD);
			पूर्ण
			अगर (status & StatsFull) अणु	/* Empty statistics. */
				अटल पूर्णांक DoneDidThat;
				अगर (corkscrew_debug > 4)
					pr_debug("%s: Updating stats.\n", dev->name);
				update_stats(ioaddr, dev);
				/* DEBUG HACK: Disable statistics as an पूर्णांकerrupt source. */
				/* This occurs when we have the wrong media type! */
				अगर (DoneDidThat == 0 && inw(ioaddr + EL3_STATUS) & StatsFull) अणु
					पूर्णांक win, reg;
					pr_notice("%s: Updating stats failed, disabling stats as an interrupt source.\n",
						dev->name);
					क्रम (win = 0; win < 8; win++) अणु
						EL3WINDOW(win);
						pr_notice("Vortex window %d:", win);
						क्रम (reg = 0; reg < 16; reg++)
							pr_cont(" %2.2x", inb(ioaddr + reg));
						pr_cont("\n");
					पूर्ण
					EL3WINDOW(7);
					outw(SetIntrEnb | TxAvailable |
					     RxComplete | AdapterFailure |
					     UpComplete | DownComplete |
					     TxComplete, ioaddr + EL3_CMD);
					DoneDidThat++;
				पूर्ण
			पूर्ण
			अगर (status & AdapterFailure) अणु
				/* Adapter failure requires Rx reset and reinit. */
				outw(RxReset, ioaddr + EL3_CMD);
				/* Set the Rx filter to the current state. */
				set_rx_mode(dev);
				outw(RxEnable, ioaddr + EL3_CMD);	/* Re-enable the receiver. */
				outw(AckIntr | AdapterFailure,
				     ioaddr + EL3_CMD);
			पूर्ण
		पूर्ण

		अगर (--i < 0) अणु
			pr_err("%s: Too much work in interrupt, status %4.4x. Disabling functions (%4.4x).\n",
				dev->name, status, SetStatusEnb | ((~status) & 0x7FE));
			/* Disable all pending पूर्णांकerrupts. */
			outw(SetStatusEnb | ((~status) & 0x7FE), ioaddr + EL3_CMD);
			outw(AckIntr | 0x7FF, ioaddr + EL3_CMD);
			अवरोध;
		पूर्ण
		/* Acknowledge the IRQ. */
		outw(AckIntr | IntReq | IntLatch, ioaddr + EL3_CMD);

	पूर्ण जबतक ((status = inw(ioaddr + EL3_STATUS)) & (IntLatch | RxComplete));

	spin_unlock(&lp->lock);

	अगर (corkscrew_debug > 4)
		pr_debug("%s: exiting interrupt, status %4.4x.\n", dev->name, status);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक corkscrew_rx(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक i;
	लघु rx_status;

	अगर (corkscrew_debug > 5)
		pr_debug("   In rx_packet(), status %4.4x, rx_status %4.4x.\n",
		     inw(ioaddr + EL3_STATUS), inw(ioaddr + RxStatus));
	जबतक ((rx_status = inw(ioaddr + RxStatus)) > 0) अणु
		अगर (rx_status & 0x4000) अणु	/* Error, update stats. */
			अचिन्हित अक्षर rx_error = inb(ioaddr + RxErrors);
			अगर (corkscrew_debug > 2)
				pr_debug(" Rx error: status %2.2x.\n",
				       rx_error);
			dev->stats.rx_errors++;
			अगर (rx_error & 0x01)
				dev->stats.rx_over_errors++;
			अगर (rx_error & 0x02)
				dev->stats.rx_length_errors++;
			अगर (rx_error & 0x04)
				dev->stats.rx_frame_errors++;
			अगर (rx_error & 0x08)
				dev->stats.rx_crc_errors++;
			अगर (rx_error & 0x10)
				dev->stats.rx_length_errors++;
		पूर्ण अन्यथा अणु
			/* The packet length: up to 4.5K!. */
			लघु pkt_len = rx_status & 0x1fff;
			काष्ठा sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 5 + 2);
			अगर (corkscrew_debug > 4)
				pr_debug("Receiving packet size %d status %4.4x.\n",
				     pkt_len, rx_status);
			अगर (skb != शून्य) अणु
				skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
				/* 'skb_put()' poपूर्णांकs to the start of sk_buff data area. */
				insl(ioaddr + RX_FIFO,
				     skb_put(skb, pkt_len),
				     (pkt_len + 3) >> 2);
				outw(RxDiscard, ioaddr + EL3_CMD);	/* Pop top Rx packet. */
				skb->protocol = eth_type_trans(skb, dev);
				netअगर_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
				/* Wait a limited समय to go to next packet. */
				क्रम (i = 200; i >= 0; i--)
					अगर (! (inw(ioaddr + EL3_STATUS) & CmdInProgress))
						अवरोध;
				जारी;
			पूर्ण अन्यथा अगर (corkscrew_debug)
				pr_debug("%s: Couldn't allocate a sk_buff of size %d.\n", dev->name, pkt_len);
		पूर्ण
		outw(RxDiscard, ioaddr + EL3_CMD);
		dev->stats.rx_dropped++;
		/* Wait a limited समय to skip this packet. */
		क्रम (i = 200; i >= 0; i--)
			अगर (!(inw(ioaddr + EL3_STATUS) & CmdInProgress))
				अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक boomerang_rx(काष्ठा net_device *dev)
अणु
	काष्ठा corkscrew_निजी *vp = netdev_priv(dev);
	पूर्णांक entry = vp->cur_rx % RX_RING_SIZE;
	पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक rx_status;

	अगर (corkscrew_debug > 5)
		pr_debug("   In boomerang_rx(), status %4.4x, rx_status %4.4x.\n",
			inw(ioaddr + EL3_STATUS), inw(ioaddr + RxStatus));
	जबतक ((rx_status = vp->rx_ring[entry].status) & RxDComplete) अणु
		अगर (rx_status & RxDError) अणु	/* Error, update stats. */
			अचिन्हित अक्षर rx_error = rx_status >> 16;
			अगर (corkscrew_debug > 2)
				pr_debug(" Rx error: status %2.2x.\n",
				       rx_error);
			dev->stats.rx_errors++;
			अगर (rx_error & 0x01)
				dev->stats.rx_over_errors++;
			अगर (rx_error & 0x02)
				dev->stats.rx_length_errors++;
			अगर (rx_error & 0x04)
				dev->stats.rx_frame_errors++;
			अगर (rx_error & 0x08)
				dev->stats.rx_crc_errors++;
			अगर (rx_error & 0x10)
				dev->stats.rx_length_errors++;
		पूर्ण अन्यथा अणु
			/* The packet length: up to 4.5K!. */
			लघु pkt_len = rx_status & 0x1fff;
			काष्ठा sk_buff *skb;

			dev->stats.rx_bytes += pkt_len;
			अगर (corkscrew_debug > 4)
				pr_debug("Receiving packet size %d status %4.4x.\n",
				     pkt_len, rx_status);

			/* Check अगर the packet is दीर्घ enough to just accept without
			   copying to a properly sized skbuff. */
			अगर (pkt_len < rx_copyअवरोध &&
			    (skb = netdev_alloc_skb(dev, pkt_len + 4)) != शून्य) अणु
				skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
				/* 'skb_put()' poपूर्णांकs to the start of sk_buff data area. */
				skb_put_data(skb,
					     isa_bus_to_virt(vp->rx_ring[entry].addr),
					     pkt_len);
				rx_copy++;
			पूर्ण अन्यथा अणु
				व्योम *temp;
				/* Pass up the skbuff alपढ़ोy on the Rx ring. */
				skb = vp->rx_skbuff[entry];
				vp->rx_skbuff[entry] = शून्य;
				temp = skb_put(skb, pkt_len);
				/* Remove this checking code क्रम final release. */
				अगर (isa_bus_to_virt(vp->rx_ring[entry].addr) != temp)
					pr_warn("%s: Warning -- the skbuff addresses do not match in boomerang_rx: %p vs. %p / %p\n",
						dev->name,
						isa_bus_to_virt(vp->rx_ring[entry].addr),
						skb->head, temp);
				rx_nocopy++;
			पूर्ण
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);
			dev->stats.rx_packets++;
		पूर्ण
		entry = (++vp->cur_rx) % RX_RING_SIZE;
	पूर्ण
	/* Refill the Rx ring buffers. */
	क्रम (; vp->cur_rx - vp->dirty_rx > 0; vp->dirty_rx++) अणु
		काष्ठा sk_buff *skb;
		entry = vp->dirty_rx % RX_RING_SIZE;
		अगर (vp->rx_skbuff[entry] == शून्य) अणु
			skb = netdev_alloc_skb(dev, PKT_BUF_SZ);
			अगर (skb == शून्य)
				अवरोध;	/* Bad news!  */
			skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
			vp->rx_ring[entry].addr = isa_virt_to_bus(skb->data);
			vp->rx_skbuff[entry] = skb;
		पूर्ण
		vp->rx_ring[entry].status = 0;	/* Clear complete bit. */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक corkscrew_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा corkscrew_निजी *vp = netdev_priv(dev);
	पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक i;

	netअगर_stop_queue(dev);

	अगर (corkscrew_debug > 1) अणु
		pr_debug("%s: corkscrew_close() status %4.4x, Tx status %2.2x.\n",
		     dev->name, inw(ioaddr + EL3_STATUS),
		     inb(ioaddr + TxStatus));
		pr_debug("%s: corkscrew close stats: rx_nocopy %d rx_copy %d tx_queued %d.\n",
			dev->name, rx_nocopy, rx_copy, queued_packet);
	पूर्ण

	del_समयr_sync(&vp->समयr);

	/* Turn off statistics ASAP.  We update lp->stats below. */
	outw(StatsDisable, ioaddr + EL3_CMD);

	/* Disable the receiver and transmitter. */
	outw(RxDisable, ioaddr + EL3_CMD);
	outw(TxDisable, ioaddr + EL3_CMD);

	अगर (dev->अगर_port == XCVR_10base2)
		/* Turn off thinnet घातer.  Green! */
		outw(StopCoax, ioaddr + EL3_CMD);

	मुक्त_irq(dev->irq, dev);

	outw(SetIntrEnb | 0x0000, ioaddr + EL3_CMD);

	update_stats(ioaddr, dev);
	अगर (vp->full_bus_master_rx) अणु	/* Free Boomerang bus master Rx buffers. */
		outl(0, ioaddr + UpListPtr);
		क्रम (i = 0; i < RX_RING_SIZE; i++)
			अगर (vp->rx_skbuff[i]) अणु
				dev_kमुक्त_skb(vp->rx_skbuff[i]);
				vp->rx_skbuff[i] = शून्य;
			पूर्ण
	पूर्ण
	अगर (vp->full_bus_master_tx) अणु	/* Free Boomerang bus master Tx buffers. */
		outl(0, ioaddr + DownListPtr);
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			अगर (vp->tx_skbuff[i]) अणु
				dev_kमुक्त_skb(vp->tx_skbuff[i]);
				vp->tx_skbuff[i] = शून्य;
			पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *corkscrew_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा corkscrew_निजी *vp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर (netअगर_running(dev)) अणु
		spin_lock_irqsave(&vp->lock, flags);
		update_stats(dev->base_addr, dev);
		spin_unlock_irqrestore(&vp->lock, flags);
	पूर्ण
	वापस &dev->stats;
पूर्ण

/*  Update statistics.
	Unlike with the EL3 we need not worry about पूर्णांकerrupts changing
	the winकरोw setting from underneath us, but we must still guard
	against a race condition with a StatsUpdate पूर्णांकerrupt updating the
	table.  This is करोne by checking that the ASM (!) code generated uses
	atomic updates with '+='.
	*/
अटल व्योम update_stats(पूर्णांक ioaddr, काष्ठा net_device *dev)
अणु
	/* Unlike the 3c5x9 we need not turn off stats updates जबतक पढ़ोing. */
	/* Switch to the stats winकरोw, and पढ़ो everything. */
	EL3WINDOW(6);
	dev->stats.tx_carrier_errors += inb(ioaddr + 0);
	dev->stats.tx_heartbeat_errors += inb(ioaddr + 1);
	/* Multiple collisions. */ inb(ioaddr + 2);
	dev->stats.collisions += inb(ioaddr + 3);
	dev->stats.tx_winकरोw_errors += inb(ioaddr + 4);
	dev->stats.rx_fअगरo_errors += inb(ioaddr + 5);
	dev->stats.tx_packets += inb(ioaddr + 6);
	dev->stats.tx_packets += (inb(ioaddr + 9) & 0x30) << 4;
						/* Rx packets   */ inb(ioaddr + 7);
						/* Must पढ़ो to clear */
	/* Tx deferrals */ inb(ioaddr + 8);
	/* Don't bother with रेजिस्टर 9, an extension of रेजिस्टरs 6&7.
	   If we करो use the 6&7 values the atomic update assumption above
	   is invalid. */
	inw(ioaddr + 10);	/* Total Rx and Tx octets. */
	inw(ioaddr + 12);
	/* New: On the Vortex we must also clear the BadSSD counter. */
	EL3WINDOW(4);
	inb(ioaddr + 12);

	/* We change back to winकरोw 7 (not 1) with the Vortex. */
	EL3WINDOW(7);
पूर्ण

/* This new version of set_rx_mode() supports v1.4 kernels.
   The Vortex chip has no करोcumented multicast filter, so the only
   multicast setting is to receive all multicast frames.  At least
   the chip has a very clean way to set the mode, unlike many others. */
अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	अचिन्हित लघु new_mode;

	अगर (dev->flags & IFF_PROMISC) अणु
		अगर (corkscrew_debug > 3)
			pr_debug("%s: Setting promiscuous mode.\n",
			       dev->name);
		new_mode = SetRxFilter | RxStation | RxMulticast | RxBroadcast | RxProm;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev) || dev->flags & IFF_ALLMULTI) अणु
		new_mode = SetRxFilter | RxStation | RxMulticast | RxBroadcast;
	पूर्ण अन्यथा
		new_mode = SetRxFilter | RxStation | RxBroadcast;

	outw(new_mode, ioaddr + EL3_CMD);
पूर्ण

अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	snम_लिखो(info->bus_info, माप(info->bus_info), "ISA 0x%lx",
		 dev->base_addr);
पूर्ण

अटल u32 netdev_get_msglevel(काष्ठा net_device *dev)
अणु
	वापस corkscrew_debug;
पूर्ण

अटल व्योम netdev_set_msglevel(काष्ठा net_device *dev, u32 level)
अणु
	corkscrew_debug = level;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
	.get_msglevel		= netdev_get_msglevel,
	.set_msglevel		= netdev_set_msglevel,
पूर्ण;


#अगर_घोषित MODULE
व्योम cleanup_module(व्योम)
अणु
	जबतक (!list_empty(&root_corkscrew_dev)) अणु
		काष्ठा net_device *dev;
		काष्ठा corkscrew_निजी *vp;

		vp = list_entry(root_corkscrew_dev.next,
				काष्ठा corkscrew_निजी, list);
		dev = vp->our_dev;
		unरेजिस्टर_netdev(dev);
		cleanup_card(dev);
		मुक्त_netdev(dev);
	पूर्ण
पूर्ण
#पूर्ण_अगर				/* MODULE */
