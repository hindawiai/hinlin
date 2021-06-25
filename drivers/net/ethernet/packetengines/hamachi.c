<शैली गुरु>
/* hamachi.c: A Packet Engines GNIC-II Gigabit Ethernet driver क्रम Linux. */
/*
	Written 1998-2000 by Donald Becker.
	Updates 2000 by Keith Underwood.

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

	This driver is क्रम the Packet Engines GNIC-II PCI Gigabit Ethernet
	adapter.

	Support and updates available at
	http://www.scyld.com/network/hamachi.hपंचांगl
	[link no दीर्घer provides useful info -jgarzik]
	or
	http://www.parl.clemson.edu/~keithu/hamachi.hपंचांगl

*/

#घोषणा DRV_NAME	"hamachi"
#घोषणा DRV_VERSION	"2.1"
#घोषणा DRV_RELDATE	"Sept 11, 2006"


/* A few user-configurable values. */

अटल पूर्णांक debug = 1;		/* 1 normal messages, 0 quiet .. 7 verbose.  */
#घोषणा final_version
#घोषणा hamachi_debug debug
/* Maximum events (Rx packets, etc.) to handle at each पूर्णांकerrupt. */
अटल पूर्णांक max_पूर्णांकerrupt_work = 40;
अटल पूर्णांक mtu;
/* Default values selected by testing on a dual processor PIII-450 */
/* These six पूर्णांकerrupt control parameters may be set directly when loading the
 * module, or through the rx_params and tx_params variables
 */
अटल पूर्णांक max_rx_latency = 0x11;
अटल पूर्णांक max_rx_gap = 0x05;
अटल पूर्णांक min_rx_pkt = 0x18;
अटल पूर्णांक max_tx_latency = 0x00;
अटल पूर्णांक max_tx_gap = 0x00;
अटल पूर्णांक min_tx_pkt = 0x30;

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
   -Setting to > 1518 causes all frames to be copied
	-Setting to 0 disables copies
*/
अटल पूर्णांक rx_copyअवरोध;

/* An override क्रम the hardware detection of bus width.
	Set to 1 to क्रमce 32 bit PCI bus detection.  Set to 4 to क्रमce 64 bit.
	Add 2 to disable parity detection.
*/
अटल पूर्णांक क्रमce32;


/* Used to pass the media type, etc.
   These exist क्रम driver पूर्णांकeroperability.
   No media types are currently defined.
		- The lower 4 bits are reserved क्रम the media type.
		- The next three bits may be set to one of the following:
			0x00000000 : Autodetect PCI bus
			0x00000010 : Force 32 bit PCI bus
			0x00000020 : Disable parity detection
			0x00000040 : Force 64 bit PCI bus
			Default is स्वतःdetect
		- The next bit can be used to क्रमce half-duplex.  This is a bad
		  idea since no known implementations implement half-duplex, and,
		  in general, half-duplex क्रम gigabit ethernet is a bad idea.
			0x00000080 : Force half-duplex
			Default is full-duplex.
		- In the original driver, the nपूर्णांकh bit could be used to क्रमce
		  full-duplex.  Maपूर्णांकain that क्रम compatibility
		   0x00000200 : Force full-duplex
*/
#घोषणा MAX_UNITS 8				/* More are supported, limit only on options */
अटल पूर्णांक options[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;
अटल पूर्णांक full_duplex[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;
/* The Hamachi chipset supports 3 parameters each क्रम Rx and Tx
 * पूर्णांकerruput management.  Parameters will be loaded as specअगरied पूर्णांकo
 * the TxIntControl and RxIntControl रेजिस्टरs.
 *
 * The रेजिस्टरs are arranged as follows:
 *     23 - 16   15 -  8   7    -    0
 *    _________________________________
 *   | min_pkt | max_gap | max_latency |
 *    ---------------------------------
 *   min_pkt      : The minimum number of packets processed between
 *                  पूर्णांकerrupts.
 *   max_gap      : The maximum पूर्णांकer-packet gap in units of 8.192 us
 *   max_latency  : The असलolute समय between पूर्णांकerrupts in units of 8.192 us
 *
 */
अटल पूर्णांक rx_params[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;
अटल पूर्णांक tx_params[MAX_UNITS] = अणु-1, -1, -1, -1, -1, -1, -1, -1पूर्ण;

/* Operational parameters that are set at compile समय. */

/* Keep the ring sizes a घातer of two क्रम compile efficiency.
	The compiler will convert <अचिन्हित>'%'<2^N> पूर्णांकo a bit mask.
   Making the Tx ring too large decreases the effectiveness of channel
   bonding and packet priority.
   There are no ill effects from too-large receive rings, except क्रम
	excessive memory usage */
/* Empirically it appears that the Tx ring needs to be a little bigger
   क्रम these Gbit adapters or you get पूर्णांकo an overrun condition really
   easily.  Also, things appear to work a bit better in back-to-back
   configurations अगर the Rx ring is 8 बार the size of the Tx ring
*/
#घोषणा TX_RING_SIZE	64
#घोषणा RX_RING_SIZE	512
#घोषणा TX_TOTAL_SIZE	TX_RING_SIZE*माप(काष्ठा hamachi_desc)
#घोषणा RX_TOTAL_SIZE	RX_RING_SIZE*माप(काष्ठा hamachi_desc)

/*
 * Enable netdev_ioctl.  Added पूर्णांकerrupt coalescing parameter adjusपंचांगent.
 * 2/19/99 Pete Wyckoff <wyckoff@ca.sandia.gov>
 */

/* play with 64-bit addrlen; seems to be a teensy bit slower  --pw */
/* #घोषणा ADDRLEN 64 */

/*
 * RX_CHECKSUM turns on card-generated receive checksum generation क्रम
 *   TCP and UDP packets.  Otherwise the upper layers करो the calculation.
 * 3/10/1999 Pete Wyckoff <wyckoff@ca.sandia.gov>
 */
#घोषणा RX_CHECKSUM

/* Operational parameters that usually are not changed. */
/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (5*HZ)

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/समय.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>	/* Processor type क्रम cache alignment. */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/cache.h>

अटल स्थिर अक्षर version[] =
KERN_INFO DRV_NAME ".c:v" DRV_VERSION " " DRV_RELDATE "  Written by Donald Becker\n"
"   Some modifications by Eric kasten <kasten@nscl.msu.edu>\n"
"   Further modifications by Keith Underwood <keithu@parl.clemson.edu>\n";


/* IP_MF appears to be only defined in <netinet/ip.h>, however,
   we need it क्रम hardware checksumming support.  FYI... some of
   the definitions in <netinet/ip.h> conflict/duplicate those in
   other linux headers causing many compiler warnings.
*/
#अगर_अघोषित IP_MF
  #घोषणा IP_MF 0x2000   /* IP more frags from <netinet/ip.h> */
#पूर्ण_अगर

/* Define IP_OFFSET to be IPOPT_OFFSET */
#अगर_अघोषित IP_OFFSET
  #अगर_घोषित IPOPT_OFFSET
    #घोषणा IP_OFFSET IPOPT_OFFSET
  #अन्यथा
    #घोषणा IP_OFFSET 2
  #पूर्ण_अगर
#पूर्ण_अगर

#घोषणा RUN_AT(x) (jअगरfies + (x))

#अगर_अघोषित ADDRLEN
#घोषणा ADDRLEN 32
#पूर्ण_अगर

/* Condensed bus+endian portability operations. */
#अगर ADDRLEN == 64
#घोषणा cpu_to_leXX(addr)	cpu_to_le64(addr)
#घोषणा leXX_to_cpu(addr)	le64_to_cpu(addr)
#अन्यथा
#घोषणा cpu_to_leXX(addr)	cpu_to_le32(addr)
#घोषणा leXX_to_cpu(addr)	le32_to_cpu(addr)
#पूर्ण_अगर


/*
				Theory of Operation

I. Board Compatibility

This device driver is deचिन्हित क्रम the Packet Engines "Hamachi"
Gigabit Ethernet chip.  The only PCA currently supported is the GNIC-II 64-bit
66Mhz PCI card.

II. Board-specअगरic settings

No jumpers exist on the board.  The chip supports software correction of
various motherboard wiring errors, however this driver करोes not support
that feature.

III. Driver operation

IIIa. Ring buffers

The Hamachi uses a typical descriptor based bus-master architecture.
The descriptor list is similar to that used by the Digital Tulip.
This driver uses two अटलally allocated fixed-size descriptor lists
क्रमmed पूर्णांकo rings by a branch from the final descriptor to the beginning of
the list.  The ring sizes are set at compile समय by RX/TX_RING_SIZE.

This driver uses a zero-copy receive and transmit scheme similar my other
network drivers.
The driver allocates full frame size skbuffs क्रम the Rx ring buffers at
खोलो() समय and passes the skb->data field to the Hamachi as receive data
buffers.  When an incoming frame is less than RX_COPYBREAK bytes दीर्घ,
a fresh skbuff is allocated and the frame is copied to the new skbuff.
When the incoming frame is larger, the skbuff is passed directly up the
protocol stack and replaced by a newly allocated skbuff.

The RX_COPYBREAK value is chosen to trade-off the memory wasted by
using a full-sized skbuff क्रम small frames vs. the copying costs of larger
frames.  Gigabit cards are typically used on generously configured machines
and the underfilled buffers have negligible impact compared to the benefit of
a single allocation size, so the शेष value of zero results in never
copying packets.

IIIb/c. Transmit/Receive Structure

The Rx and Tx descriptor काष्ठाure are straight-क्रमward, with no historical
baggage that must be explained.  Unlike the awkward DBDMA काष्ठाure, there
are no unused fields or option bits that had only one allowable setting.

Two details should be noted about the descriptors: The chip supports both 32
bit and 64 bit address काष्ठाures, and the length field is overwritten on
the receive descriptors.  The descriptor length is set in the control word
क्रम each channel. The development driver uses 32 bit addresses only, however
64 bit addresses may be enabled क्रम 64 bit architectures e.g. the Alpha.

IIId. Synchronization

This driver is very similar to my other network drivers.
The driver runs as two independent, single-thपढ़ोed flows of control.  One
is the send-packet routine, which enक्रमces single-thपढ़ोed use by the
dev->tbusy flag.  The other thपढ़ो is the पूर्णांकerrupt handler, which is single
thपढ़ोed by the hardware and other software.

The send packet thपढ़ो has partial control over the Tx ring and 'dev->tbusy'
flag.  It sets the tbusy flag whenever it's queuing a Tx packet. If the next
queue slot is empty, it clears the tbusy flag when finished otherwise it sets
the 'hmp->tx_full' flag.

The पूर्णांकerrupt handler has exclusive control over the Rx ring and records stats
from the Tx ring.  After reaping the stats, it marks the Tx queue entry as
empty by incrementing the dirty_tx mark. Iff the 'hmp->tx_full' flag is set, it
clears both the tx_full and tbusy flags.

IV. Notes

Thanks to Kim Stearns of Packet Engines क्रम providing a pair of GNIC-II boards.

IVb. References

Hamachi Engineering Design Specअगरication, 5/15/97
(Note: This version was marked "Confidential".)

IVc. Errata

None noted.

V.  Recent Changes

01/15/1999 EPK  Enlargement of the TX and RX ring sizes.  This appears
    to help aव्योम some stall conditions -- this needs further research.

01/15/1999 EPK  Creation of the hamachi_tx function.  This function cleans
    the Tx ring and is called from hamachi_start_xmit (this used to be
    called from hamachi_पूर्णांकerrupt but it tends to delay execution of the
    पूर्णांकerrupt handler and thus reduce bandwidth by reducing the latency
    between hamachi_rx()'s).  Notably, some modअगरication has been made so
    that the cleaning loop checks only to make sure that the DescOwn bit
    isn't set in the status flag since the card is not required
    to set the entire flag to zero after processing.

01/15/1999 EPK In the hamachi_start_tx function, the Tx ring full flag is
    checked beक्रमe attempting to add a buffer to the ring.  If the ring is full
    an attempt is made to मुक्त any dirty buffers and thus find space क्रम
    the new buffer or the function वापसs non-zero which should हाल the
    scheduler to reschedule the buffer later.

01/15/1999 EPK Some adjusपंचांगents were made to the chip initialization.
    End-to-end flow control should now be fully active and the पूर्णांकerrupt
    algorithm vars have been changed.  These could probably use further tuning.

01/15/1999 EPK Added the max_अणुrx,txपूर्ण_latency options.  These are used to
    set the rx and tx latencies क्रम the Hamachi पूर्णांकerrupts. If you're having
    problems with network stalls, try setting these to higher values.
    Valid values are 0x00 through 0xff.

01/15/1999 EPK In general, the overall bandwidth has increased and
    latencies are better (someबार by a factor of 2).  Stalls are rare at
    this poपूर्णांक, however there still appears to be a bug somewhere between the
    hardware and driver.  TCP checksum errors under load also appear to be
    eliminated at this poपूर्णांक.

01/18/1999 EPK Ensured that the DescEndRing bit was being set on both the
    Rx and Tx rings.  This appears to have been affecting whether a particular
    peer-to-peer connection would hang under high load.  I believe the Rx
    rings was typically getting set correctly, but the Tx ring wasn't getting
    the DescEndRing bit set during initialization. ??? Does this mean the
    hamachi card is using the DescEndRing in processing even अगर a particular
    slot isn't in use -- hypothetically, the card might be searching the
    entire Tx ring क्रम slots with the DescOwn bit set and then processing
    them.  If the DescEndRing bit isn't set, then it might just wander off
    through memory until it hits a chunk of data with that bit set
    and then looping back.

02/09/1999 EPK Added Michel Mueller's TxDMA Interrupt and Tx-समयout
    problem (TxCmd and RxCmd need only to be set when idle or stopped.

02/09/1999 EPK Added code to check/reset dev->tbusy in hamachi_पूर्णांकerrupt.
    (Michel Mueller poपूर्णांकed out the ``permanently busy'' potential
    problem here).

02/22/1999 EPK Added Pete Wyckoff's ioctl to control the Tx/Rx latencies.

02/23/1999 EPK Verअगरied that the पूर्णांकerrupt status field bits क्रम Tx were
    incorrectly defined and corrected (as per Michel Mueller).

02/23/1999 EPK Corrected the Tx full check to check that at least 4 slots
    were available beक्रमe resetting the tbusy and tx_full flags
    (as per Michel Mueller).

03/11/1999 EPK Added Pete Wyckoff's hardware checksumming support.

12/31/1999 KDU Cleaned up assorted things and added Don's code to क्रमce
32 bit.

02/20/2000 KDU Some of the control was just plain odd.  Cleaned up the
hamachi_start_xmit() and hamachi_पूर्णांकerrupt() code.  There is still some
re-काष्ठाuring I would like to करो.

03/01/2000 KDU Experimenting with a WIDE range of पूर्णांकerrupt mitigation
parameters on a dual P3-450 setup yielded the new शेष पूर्णांकerrupt
mitigation parameters.  Tx should पूर्णांकerrupt VERY infrequently due to
Eric's scheme.  Rx should be more often...

03/13/2000 KDU Added a patch to make the Rx Checksum code पूर्णांकeract
nicely with non-linux machines.

03/13/2000 KDU Experimented with some of the configuration values:

	-It seems that enabling PCI perक्रमmance commands क्रम descriptors
	(changing RxDMACtrl and TxDMACtrl lower nibble from 5 to D) has minimal
	perक्रमmance impact क्रम any of my tests. (ttcp, netpipe, netperf)  I will
	leave them that way until I hear further feedback.

	-Increasing the PCI_LATENCY_TIMER to 130
	(2 + (burst size of 128 * (0 रुको states + 1))) seems to slightly
	degrade perक्रमmance.  Leaving शेष at 64 pending further inक्रमmation.

03/14/2000 KDU Further tuning:

	-adjusted boguscnt in hamachi_rx() to depend on पूर्णांकerrupt
	mitigation parameters chosen.

	-Selected a set of पूर्णांकerrupt parameters based on some extensive testing.
	These may change with more testing.

TO DO:

-Consider borrowing from the acenic driver code to check PCI_COMMAND क्रम
PCI_COMMAND_INVALIDATE.  Set maximum burst size to cache line size in
that हाल.

-fix the reset procedure.  It करोesn't quite work.
*/

/* A few values that may be tweaked. */
/* Size of each temporary Rx buffer, calculated as:
 * 1518 bytes (ethernet packet) + 2 bytes (to get 8 byte alignment क्रम
 * the card) + 8 bytes of status info + 8 bytes क्रम the Rx Checksum
 */
#घोषणा PKT_BUF_SZ		1536

/* For now, this is going to be set to the maximum size of an ethernet
 * packet.  Eventually, we may want to make it a variable that is
 * related to the MTU
 */
#घोषणा MAX_FRAME_SIZE  1518

/* The rest of these values should never change. */

अटल व्योम hamachi_समयr(काष्ठा समयr_list *t);

क्रमागत capability_flags अणुCanHaveMII=1, पूर्ण;
अटल स्थिर काष्ठा chip_info अणु
	u16	venकरोr_id, device_id, device_id_mask, pad;
	स्थिर अक्षर *name;
	व्योम (*media_समयr)(काष्ठा समयr_list *t);
	पूर्णांक flags;
पूर्ण chip_tbl[] = अणु
	अणु0x1318, 0x0911, 0xffff, 0, "Hamachi GNIC-II", hamachi_समयr, 0पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

/* Offsets to the Hamachi रेजिस्टरs.  Various sizes. */
क्रमागत hamachi_offsets अणु
	TxDMACtrl=0x00, TxCmd=0x04, TxStatus=0x06, TxPtr=0x08, TxCurPtr=0x10,
	RxDMACtrl=0x20, RxCmd=0x24, RxStatus=0x26, RxPtr=0x28, RxCurPtr=0x30,
	PCIClkMeas=0x060, MiscStatus=0x066, ChipRev=0x68, ChipReset=0x06B,
	LEDCtrl=0x06C, VirtualJumpers=0x06D, GPIO=0x6E,
	TxChecksum=0x074, RxChecksum=0x076,
	TxIntrCtrl=0x078, RxIntrCtrl=0x07C,
	InterruptEnable=0x080, InterruptClear=0x084, IntrStatus=0x088,
	EventStatus=0x08C,
	MACCnfg=0x0A0, FrameGap0=0x0A2, FrameGap1=0x0A4,
	/* See क्रमागत MII_offsets below. */
	MACCnfg2=0x0B0, RxDepth=0x0B8, FlowCtrl=0x0BC, MaxFrameSize=0x0CE,
	AddrMode=0x0D0, StationAddr=0x0D2,
	/* Gigabit AutoNegotiation. */
	ANCtrl=0x0E0, ANStatus=0x0E2, ANXchngCtrl=0x0E4, ANAdvertise=0x0E8,
	ANLinkPartnerAbility=0x0EA,
	EECmdStatus=0x0F0, EEData=0x0F1, EEAddr=0x0F2,
	FIFOcfg=0x0F8,
पूर्ण;

/* Offsets to the MII-mode रेजिस्टरs. */
क्रमागत MII_offsets अणु
	MII_Cmd=0xA6, MII_Addr=0xA8, MII_Wr_Data=0xAA, MII_Rd_Data=0xAC,
	MII_Status=0xAE,
पूर्ण;

/* Bits in the पूर्णांकerrupt status/mask रेजिस्टरs. */
क्रमागत पूर्णांकr_status_bits अणु
	IntrRxDone=0x01, IntrRxPCIFault=0x02, IntrRxPCIErr=0x04,
	IntrTxDone=0x100, IntrTxPCIFault=0x200, IntrTxPCIErr=0x400,
	LinkChange=0x10000, NegotiationChange=0x20000, StatsMax=0x40000, पूर्ण;

/* The Hamachi Rx and Tx buffer descriptors. */
काष्ठा hamachi_desc अणु
	__le32 status_n_length;
#अगर ADDRLEN == 64
	u32 pad;
	__le64 addr;
#अन्यथा
	__le32 addr;
#पूर्ण_अगर
पूर्ण;

/* Bits in hamachi_desc.status_n_length */
क्रमागत desc_status_bits अणु
	DescOwn=0x80000000, DescEndPacket=0x40000000, DescEndRing=0x20000000,
	DescIntr=0x10000000,
पूर्ण;

#घोषणा PRIV_ALIGN	15  			/* Required alignment mask */
#घोषणा MII_CNT		4
काष्ठा hamachi_निजी अणु
	/* Descriptor rings first क्रम alignment.  Tx requires a second descriptor
	   क्रम status. */
	काष्ठा hamachi_desc *rx_ring;
	काष्ठा hamachi_desc *tx_ring;
	काष्ठा sk_buff* rx_skbuff[RX_RING_SIZE];
	काष्ठा sk_buff* tx_skbuff[TX_RING_SIZE];
	dma_addr_t tx_ring_dma;
	dma_addr_t rx_ring_dma;
	काष्ठा समयr_list समयr;		/* Media selection समयr. */
	/* Frequently used and paired value: keep adjacent क्रम cache effect. */
	spinlock_t lock;
	पूर्णांक chip_id;
	अचिन्हित पूर्णांक cur_rx, dirty_rx;		/* Producer/consumer ring indices */
	अचिन्हित पूर्णांक cur_tx, dirty_tx;
	अचिन्हित पूर्णांक rx_buf_sz;			/* Based on MTU+slack. */
	अचिन्हित पूर्णांक tx_full:1;			/* The Tx queue is full. */
	अचिन्हित पूर्णांक duplex_lock:1;
	अचिन्हित पूर्णांक शेष_port:4;		/* Last dev->अगर_port value. */
	/* MII transceiver section. */
	पूर्णांक mii_cnt;								/* MII device addresses. */
	काष्ठा mii_अगर_info mii_अगर;		/* MII lib hooks/info */
	अचिन्हित अक्षर phys[MII_CNT];		/* MII device addresses, only first one used. */
	u32 rx_पूर्णांक_var, tx_पूर्णांक_var;	/* पूर्णांकerrupt control variables */
	u32 option;							/* Hold on to a copy of the options */
	काष्ठा pci_dev *pci_dev;
	व्योम __iomem *base;
पूर्ण;

MODULE_AUTHOR("Donald Becker <becker@scyld.com>, Eric Kasten <kasten@nscl.msu.edu>, Keith Underwood <keithu@parl.clemson.edu>");
MODULE_DESCRIPTION("Packet Engines 'Hamachi' GNIC-II Gigabit Ethernet driver");
MODULE_LICENSE("GPL");

module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
module_param(mtu, पूर्णांक, 0);
module_param(debug, पूर्णांक, 0);
module_param(min_rx_pkt, पूर्णांक, 0);
module_param(max_rx_gap, पूर्णांक, 0);
module_param(max_rx_latency, पूर्णांक, 0);
module_param(min_tx_pkt, पूर्णांक, 0);
module_param(max_tx_gap, पूर्णांक, 0);
module_param(max_tx_latency, पूर्णांक, 0);
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param_array(rx_params, पूर्णांक, शून्य, 0);
module_param_array(tx_params, पूर्णांक, शून्य, 0);
module_param_array(options, पूर्णांक, शून्य, 0);
module_param_array(full_duplex, पूर्णांक, शून्य, 0);
module_param(क्रमce32, पूर्णांक, 0);
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "GNIC-II maximum events handled per interrupt");
MODULE_PARM_DESC(mtu, "GNIC-II MTU (all boards)");
MODULE_PARM_DESC(debug, "GNIC-II debug level (0-7)");
MODULE_PARM_DESC(min_rx_pkt, "GNIC-II minimum Rx packets processed between interrupts");
MODULE_PARM_DESC(max_rx_gap, "GNIC-II maximum Rx inter-packet gap in 8.192 microsecond units");
MODULE_PARM_DESC(max_rx_latency, "GNIC-II time between Rx interrupts in 8.192 microsecond units");
MODULE_PARM_DESC(min_tx_pkt, "GNIC-II minimum Tx packets processed between interrupts");
MODULE_PARM_DESC(max_tx_gap, "GNIC-II maximum Tx inter-packet gap in 8.192 microsecond units");
MODULE_PARM_DESC(max_tx_latency, "GNIC-II time between Tx interrupts in 8.192 microsecond units");
MODULE_PARM_DESC(rx_copyअवरोध, "GNIC-II copy breakpoint for copy-only-tiny-frames");
MODULE_PARM_DESC(rx_params, "GNIC-II min_rx_pkt+max_rx_gap+max_rx_latency");
MODULE_PARM_DESC(tx_params, "GNIC-II min_tx_pkt+max_tx_gap+max_tx_latency");
MODULE_PARM_DESC(options, "GNIC-II Bits 0-3: media type, bits 4-6: as force32, bit 7: half duplex, bit 9 full duplex");
MODULE_PARM_DESC(full_duplex, "GNIC-II full duplex setting(s) (1)");
MODULE_PARM_DESC(क्रमce32, "GNIC-II: Bit 0: 32 bit PCI, bit 1: disable parity, bit 2: 64 bit PCI (all boards)");

अटल पूर्णांक पढ़ो_eeprom(व्योम __iomem *ioaddr, पूर्णांक location);
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value);
अटल पूर्णांक hamachi_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल व्योम hamachi_समयr(काष्ठा समयr_list *t);
अटल व्योम hamachi_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम hamachi_init_ring(काष्ठा net_device *dev);
अटल netdev_tx_t hamachi_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev);
अटल irqवापस_t hamachi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल पूर्णांक hamachi_rx(काष्ठा net_device *dev);
अटल अंतरभूत पूर्णांक hamachi_tx(काष्ठा net_device *dev);
अटल व्योम hamachi_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status);
अटल पूर्णांक hamachi_बंद(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *hamachi_get_stats(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल स्थिर काष्ठा ethtool_ops ethtool_ops;
अटल स्थिर काष्ठा ethtool_ops ethtool_ops_no_mii;

अटल स्थिर काष्ठा net_device_ops hamachi_netdev_ops = अणु
	.nकरो_खोलो		= hamachi_खोलो,
	.nकरो_stop		= hamachi_बंद,
	.nकरो_start_xmit		= hamachi_start_xmit,
	.nकरो_get_stats		= hamachi_get_stats,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_tx_समयout		= hamachi_tx_समयout,
	.nकरो_करो_ioctl		= netdev_ioctl,
पूर्ण;


अटल पूर्णांक hamachi_init_one(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा hamachi_निजी *hmp;
	पूर्णांक option, i, rx_पूर्णांक_var, tx_पूर्णांक_var, boguscnt;
	पूर्णांक chip_id = ent->driver_data;
	पूर्णांक irq;
	व्योम __iomem *ioaddr;
	अचिन्हित दीर्घ base;
	अटल पूर्णांक card_idx;
	काष्ठा net_device *dev;
	व्योम *ring_space;
	dma_addr_t ring_dma;
	पूर्णांक ret = -ENOMEM;

/* when built पूर्णांकo the kernel, we only prपूर्णांक version अगर device is found */
#अगर_अघोषित MODULE
	अटल पूर्णांक prपूर्णांकed_version;
	अगर (!prपूर्णांकed_version++)
		prपूर्णांकk(version);
#पूर्ण_अगर

	अगर (pci_enable_device(pdev)) अणु
		ret = -EIO;
		जाओ err_out;
	पूर्ण

	base = pci_resource_start(pdev, 0);
#अगर_घोषित __alpha__				/* Really "64 bit addrs" */
	base |= (pci_resource_start(pdev, 1) << 32);
#पूर्ण_अगर

	pci_set_master(pdev);

	i = pci_request_regions(pdev, DRV_NAME);
	अगर (i)
		वापस i;

	irq = pdev->irq;
	ioaddr = ioremap(base, 0x400);
	अगर (!ioaddr)
		जाओ err_out_release;

	dev = alloc_etherdev(माप(काष्ठा hamachi_निजी));
	अगर (!dev)
		जाओ err_out_iounmap;

	SET_NETDEV_DEV(dev, &pdev->dev);

	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = 1 ? पढ़ो_eeprom(ioaddr, 4 + i)
			: पढ़ोb(ioaddr + StationAddr + i);

#अगर ! defined(final_version)
	अगर (hamachi_debug > 4)
		क्रम (i = 0; i < 0x10; i++)
			prपूर्णांकk("%2.2x%s",
				   पढ़ो_eeprom(ioaddr, i), i % 16 != 15 ? " " : "\n");
#पूर्ण_अगर

	hmp = netdev_priv(dev);
	spin_lock_init(&hmp->lock);

	hmp->mii_अगर.dev = dev;
	hmp->mii_अगर.mdio_पढ़ो = mdio_पढ़ो;
	hmp->mii_अगर.mdio_ग_लिखो = mdio_ग_लिखो;
	hmp->mii_अगर.phy_id_mask = 0x1f;
	hmp->mii_अगर.reg_num_mask = 0x1f;

	ring_space = dma_alloc_coherent(&pdev->dev, TX_TOTAL_SIZE, &ring_dma,
					GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_cleardev;
	hmp->tx_ring = ring_space;
	hmp->tx_ring_dma = ring_dma;

	ring_space = dma_alloc_coherent(&pdev->dev, RX_TOTAL_SIZE, &ring_dma,
					GFP_KERNEL);
	अगर (!ring_space)
		जाओ err_out_unmap_tx;
	hmp->rx_ring = ring_space;
	hmp->rx_ring_dma = ring_dma;

	/* Check क्रम options being passed in */
	option = card_idx < MAX_UNITS ? options[card_idx] : 0;
	अगर (dev->mem_start)
		option = dev->mem_start;

	/* If the bus size is misidentअगरied, करो the following. */
	क्रमce32 = क्रमce32 ? क्रमce32 :
		((option  >= 0) ? ((option & 0x00000070) >> 4) : 0 );
	अगर (क्रमce32)
		ग_लिखोb(क्रमce32, ioaddr + VirtualJumpers);

	/* Hmmm, करो we really need to reset the chip???. */
	ग_लिखोb(0x01, ioaddr + ChipReset);

	/* After a reset, the घड़ी speed measurement of the PCI bus will not
	 * be valid क्रम a moment.  Wait क्रम a little जबतक until it is.  If
	 * it takes more than 10ms, क्रमget it.
	 */
	udelay(10);
	i = पढ़ोb(ioaddr + PCIClkMeas);
	क्रम (boguscnt = 0; (!(i & 0x080)) && boguscnt < 1000; boguscnt++)अणु
		udelay(10);
		i = पढ़ोb(ioaddr + PCIClkMeas);
	पूर्ण

	hmp->base = ioaddr;
	pci_set_drvdata(pdev, dev);

	hmp->chip_id = chip_id;
	hmp->pci_dev = pdev;

	/* The lower four bits are the media type. */
	अगर (option > 0) अणु
		hmp->option = option;
		अगर (option & 0x200)
			hmp->mii_अगर.full_duplex = 1;
		अन्यथा अगर (option & 0x080)
			hmp->mii_अगर.full_duplex = 0;
		hmp->शेष_port = option & 15;
		अगर (hmp->शेष_port)
			hmp->mii_अगर.क्रमce_media = 1;
	पूर्ण
	अगर (card_idx < MAX_UNITS  &&  full_duplex[card_idx] > 0)
		hmp->mii_अगर.full_duplex = 1;

	/* lock the duplex mode अगर someone specअगरied a value */
	अगर (hmp->mii_अगर.full_duplex || (option & 0x080))
		hmp->duplex_lock = 1;

	/* Set पूर्णांकerrupt tuning parameters */
	max_rx_latency = max_rx_latency & 0x00ff;
	max_rx_gap = max_rx_gap & 0x00ff;
	min_rx_pkt = min_rx_pkt & 0x00ff;
	max_tx_latency = max_tx_latency & 0x00ff;
	max_tx_gap = max_tx_gap & 0x00ff;
	min_tx_pkt = min_tx_pkt & 0x00ff;

	rx_पूर्णांक_var = card_idx < MAX_UNITS ? rx_params[card_idx] : -1;
	tx_पूर्णांक_var = card_idx < MAX_UNITS ? tx_params[card_idx] : -1;
	hmp->rx_पूर्णांक_var = rx_पूर्णांक_var >= 0 ? rx_पूर्णांक_var :
		(min_rx_pkt << 16 | max_rx_gap << 8 | max_rx_latency);
	hmp->tx_पूर्णांक_var = tx_पूर्णांक_var >= 0 ? tx_पूर्णांक_var :
		(min_tx_pkt << 16 | max_tx_gap << 8 | max_tx_latency);


	/* The Hamachi-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &hamachi_netdev_ops;
	dev->ethtool_ops = (chip_tbl[hmp->chip_id].flags & CanHaveMII) ?
		&ethtool_ops : &ethtool_ops_no_mii;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	अगर (mtu)
		dev->mtu = mtu;

	i = रेजिस्टर_netdev(dev);
	अगर (i) अणु
		ret = i;
		जाओ err_out_unmap_rx;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: %s type %x at %p, %pM, IRQ %d.\n",
		   dev->name, chip_tbl[chip_id].name, पढ़ोl(ioaddr + ChipRev),
		   ioaddr, dev->dev_addr, irq);
	i = पढ़ोb(ioaddr + PCIClkMeas);
	prपूर्णांकk(KERN_INFO "%s:  %d-bit %d Mhz PCI bus (%d), Virtual Jumpers "
		   "%2.2x, LPA %4.4x.\n",
		   dev->name, पढ़ोw(ioaddr + MiscStatus) & 1 ? 64 : 32,
		   i ? 2000/(i&0x7f) : 0, i&0x7f, (पूर्णांक)पढ़ोb(ioaddr + VirtualJumpers),
		   पढ़ोw(ioaddr + ANLinkPartnerAbility));

	अगर (chip_tbl[hmp->chip_id].flags & CanHaveMII) अणु
		पूर्णांक phy, phy_idx = 0;
		क्रम (phy = 0; phy < 32 && phy_idx < MII_CNT; phy++) अणु
			पूर्णांक mii_status = mdio_पढ़ो(dev, phy, MII_BMSR);
			अगर (mii_status != 0xffff  &&
				mii_status != 0x0000) अणु
				hmp->phys[phy_idx++] = phy;
				hmp->mii_अगर.advertising = mdio_पढ़ो(dev, phy, MII_ADVERTISE);
				prपूर्णांकk(KERN_INFO "%s: MII PHY found at address %d, status "
					   "0x%4.4x advertising %4.4x.\n",
					   dev->name, phy, mii_status, hmp->mii_अगर.advertising);
			पूर्ण
		पूर्ण
		hmp->mii_cnt = phy_idx;
		अगर (hmp->mii_cnt > 0)
			hmp->mii_अगर.phy_id = hmp->phys[0];
		अन्यथा
			स_रखो(&hmp->mii_अगर, 0, माप(hmp->mii_अगर));
	पूर्ण
	/* Configure gigabit स्वतःnegotiation. */
	ग_लिखोw(0x0400, ioaddr + ANXchngCtrl);	/* Enable legacy links. */
	ग_लिखोw(0x08e0, ioaddr + ANAdvertise);	/* Set our advertise word. */
	ग_लिखोw(0x1000, ioaddr + ANCtrl);			/* Enable negotiation */

	card_idx++;
	वापस 0;

err_out_unmap_rx:
	dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, hmp->rx_ring,
			  hmp->rx_ring_dma);
err_out_unmap_tx:
	dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, hmp->tx_ring,
			  hmp->tx_ring_dma);
err_out_cleardev:
	मुक्त_netdev (dev);
err_out_iounmap:
	iounmap(ioaddr);
err_out_release:
	pci_release_regions(pdev);
err_out:
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_eeprom(व्योम __iomem *ioaddr, पूर्णांक location)
अणु
	पूर्णांक bogus_cnt = 1000;

	/* We should check busy first - per करोcs -KDU */
	जबतक ((पढ़ोb(ioaddr + EECmdStatus) & 0x40)  && --bogus_cnt > 0);
	ग_लिखोw(location, ioaddr + EEAddr);
	ग_लिखोb(0x02, ioaddr + EECmdStatus);
	bogus_cnt = 1000;
	जबतक ((पढ़ोb(ioaddr + EECmdStatus) & 0x40)  && --bogus_cnt > 0);
	अगर (hamachi_debug > 5)
		prपूर्णांकk("   EEPROM status is %2.2x after %d ticks.\n",
			   (पूर्णांक)पढ़ोb(ioaddr + EECmdStatus), 1000- bogus_cnt);
	वापस पढ़ोb(ioaddr + EEData);
पूर्ण

/* MII Managemen Data I/O accesses.
   These routines assume the MDIO controller is idle, and करो not निकास until
   the command is finished. */

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	व्योम __iomem *ioaddr = hmp->base;
	पूर्णांक i;

	/* We should check busy first - per करोcs -KDU */
	क्रम (i = 10000; i >= 0; i--)
		अगर ((पढ़ोw(ioaddr + MII_Status) & 1) == 0)
			अवरोध;
	ग_लिखोw((phy_id<<8) + location, ioaddr + MII_Addr);
	ग_लिखोw(0x0001, ioaddr + MII_Cmd);
	क्रम (i = 10000; i >= 0; i--)
		अगर ((पढ़ोw(ioaddr + MII_Status) & 1) == 0)
			अवरोध;
	वापस पढ़ोw(ioaddr + MII_Rd_Data);
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	व्योम __iomem *ioaddr = hmp->base;
	पूर्णांक i;

	/* We should check busy first - per करोcs -KDU */
	क्रम (i = 10000; i >= 0; i--)
		अगर ((पढ़ोw(ioaddr + MII_Status) & 1) == 0)
			अवरोध;
	ग_लिखोw((phy_id<<8) + location, ioaddr + MII_Addr);
	ग_लिखोw(value, ioaddr + MII_Wr_Data);

	/* Wait क्रम the command to finish. */
	क्रम (i = 10000; i >= 0; i--)
		अगर ((पढ़ोw(ioaddr + MII_Status) & 1) == 0)
			अवरोध;
पूर्ण


अटल पूर्णांक hamachi_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	व्योम __iomem *ioaddr = hmp->base;
	पूर्णांक i;
	u32 rx_पूर्णांक_var, tx_पूर्णांक_var;
	u16 fअगरo_info;

	i = request_irq(hmp->pci_dev->irq, hamachi_पूर्णांकerrupt, IRQF_SHARED,
			dev->name, dev);
	अगर (i)
		वापस i;

	hamachi_init_ring(dev);

#अगर ADDRLEN == 64
	/* ग_लिखोllll anyone ? */
	ग_लिखोl(hmp->rx_ring_dma, ioaddr + RxPtr);
	ग_लिखोl(hmp->rx_ring_dma >> 32, ioaddr + RxPtr + 4);
	ग_लिखोl(hmp->tx_ring_dma, ioaddr + TxPtr);
	ग_लिखोl(hmp->tx_ring_dma >> 32, ioaddr + TxPtr + 4);
#अन्यथा
	ग_लिखोl(hmp->rx_ring_dma, ioaddr + RxPtr);
	ग_लिखोl(hmp->tx_ring_dma, ioaddr + TxPtr);
#पूर्ण_अगर

	/* TODO:  It would make sense to organize this as words since the card
	 * करोcumentation करोes. -KDU
	 */
	क्रम (i = 0; i < 6; i++)
		ग_लिखोb(dev->dev_addr[i], ioaddr + StationAddr + i);

	/* Initialize other रेजिस्टरs: with so many this eventually this will
	   converted to an offset/value list. */

	/* Configure the FIFO */
	fअगरo_info = (पढ़ोw(ioaddr + GPIO) & 0x00C0) >> 6;
	चयन (fअगरo_info)अणु
		हाल 0 :
			/* No FIFO */
			ग_लिखोw(0x0000, ioaddr + FIFOcfg);
			अवरोध;
		हाल 1 :
			/* Configure the FIFO क्रम 512K बाह्यal, 16K used क्रम Tx. */
			ग_लिखोw(0x0028, ioaddr + FIFOcfg);
			अवरोध;
		हाल 2 :
			/* Configure the FIFO क्रम 1024 बाह्यal, 32K used क्रम Tx. */
			ग_लिखोw(0x004C, ioaddr + FIFOcfg);
			अवरोध;
		हाल 3 :
			/* Configure the FIFO क्रम 2048 बाह्यal, 32K used क्रम Tx. */
			ग_लिखोw(0x006C, ioaddr + FIFOcfg);
			अवरोध;
		शेष :
			prपूर्णांकk(KERN_WARNING "%s:  Unsupported external memory config!\n",
				dev->name);
			/* Default to no FIFO */
			ग_लिखोw(0x0000, ioaddr + FIFOcfg);
			अवरोध;
	पूर्ण

	अगर (dev->अगर_port == 0)
		dev->अगर_port = hmp->शेष_port;


	/* Setting the Rx mode will start the Rx process. */
	/* If someone didn't choose a duplex, शेष to full-duplex */
	अगर (hmp->duplex_lock != 1)
		hmp->mii_अगर.full_duplex = 1;

	/* always 1, takes no more समय to करो it */
	ग_लिखोw(0x0001, ioaddr + RxChecksum);
	ग_लिखोw(0x0000, ioaddr + TxChecksum);
	ग_लिखोw(0x8000, ioaddr + MACCnfg); /* Soft reset the MAC */
	ग_लिखोw(0x215F, ioaddr + MACCnfg);
	ग_लिखोw(0x000C, ioaddr + FrameGap0);
	/* WHAT?!?!?  Why isn't this करोcumented somewhere? -KDU */
	ग_लिखोw(0x1018, ioaddr + FrameGap1);
	/* Why करो we enable receives/transmits here? -KDU */
	ग_लिखोw(0x0780, ioaddr + MACCnfg2); /* Upper 16 bits control LEDs. */
	/* Enable स्वतःmatic generation of flow control frames, period 0xffff. */
	ग_लिखोl(0x0030FFFF, ioaddr + FlowCtrl);
	ग_लिखोw(MAX_FRAME_SIZE, ioaddr + MaxFrameSize); 	/* dev->mtu+14 ??? */

	/* Enable legacy links. */
	ग_लिखोw(0x0400, ioaddr + ANXchngCtrl);	/* Enable legacy links. */
	/* Initial Link LED to blinking red. */
	ग_लिखोb(0x03, ioaddr + LEDCtrl);

	/* Configure पूर्णांकerrupt mitigation.  This has a great effect on
	   perक्रमmance, so प्रणालीs tuning should start here!. */

	rx_पूर्णांक_var = hmp->rx_पूर्णांक_var;
	tx_पूर्णांक_var = hmp->tx_पूर्णांक_var;

	अगर (hamachi_debug > 1) अणु
		prपूर्णांकk("max_tx_latency: %d, max_tx_gap: %d, min_tx_pkt: %d\n",
			tx_पूर्णांक_var & 0x00ff, (tx_पूर्णांक_var & 0x00ff00) >> 8,
			(tx_पूर्णांक_var & 0x00ff0000) >> 16);
		prपूर्णांकk("max_rx_latency: %d, max_rx_gap: %d, min_rx_pkt: %d\n",
			rx_पूर्णांक_var & 0x00ff, (rx_पूर्णांक_var & 0x00ff00) >> 8,
			(rx_पूर्णांक_var & 0x00ff0000) >> 16);
		prपूर्णांकk("rx_int_var: %x, tx_int_var: %x\n", rx_पूर्णांक_var, tx_पूर्णांक_var);
	पूर्ण

	ग_लिखोl(tx_पूर्णांक_var, ioaddr + TxIntrCtrl);
	ग_लिखोl(rx_पूर्णांक_var, ioaddr + RxIntrCtrl);

	set_rx_mode(dev);

	netअगर_start_queue(dev);

	/* Enable पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	ग_लिखोl(0x80878787, ioaddr + InterruptEnable);
	ग_लिखोw(0x0000, ioaddr + EventStatus);	/* Clear non-पूर्णांकerrupting events */

	/* Configure and start the DMA channels. */
	/* Burst sizes are in the low three bits: size = 4<<(val&7) */
#अगर ADDRLEN == 64
	ग_लिखोw(0x005D, ioaddr + RxDMACtrl); 		/* 128 dword bursts */
	ग_लिखोw(0x005D, ioaddr + TxDMACtrl);
#अन्यथा
	ग_लिखोw(0x001D, ioaddr + RxDMACtrl);
	ग_लिखोw(0x001D, ioaddr + TxDMACtrl);
#पूर्ण_अगर
	ग_लिखोw(0x0001, ioaddr + RxCmd);

	अगर (hamachi_debug > 2) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Done hamachi_open(), status: Rx %x Tx %x.\n",
			   dev->name, पढ़ोw(ioaddr + RxStatus), पढ़ोw(ioaddr + TxStatus));
	पूर्ण
	/* Set the समयr to check क्रम link beat. */
	समयr_setup(&hmp->समयr, hamachi_समयr, 0);
	hmp->समयr.expires = RUN_AT((24*HZ)/10);			/* 2.4 sec. */
	add_समयr(&hmp->समयr);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hamachi_tx(काष्ठा net_device *dev)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);

	/* Update the dirty poपूर्णांकer until we find an entry that is
		still owned by the card */
	क्रम (; hmp->cur_tx - hmp->dirty_tx > 0; hmp->dirty_tx++) अणु
		पूर्णांक entry = hmp->dirty_tx % TX_RING_SIZE;
		काष्ठा sk_buff *skb;

		अगर (hmp->tx_ring[entry].status_n_length & cpu_to_le32(DescOwn))
			अवरोध;
		/* Free the original skb. */
		skb = hmp->tx_skbuff[entry];
		अगर (skb) अणु
			dma_unmap_single(&hmp->pci_dev->dev,
					 leXX_to_cpu(hmp->tx_ring[entry].addr),
					 skb->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb(skb);
			hmp->tx_skbuff[entry] = शून्य;
		पूर्ण
		hmp->tx_ring[entry].status_n_length = 0;
		अगर (entry >= TX_RING_SIZE-1)
			hmp->tx_ring[TX_RING_SIZE-1].status_n_length |=
				cpu_to_le32(DescEndRing);
		dev->stats.tx_packets++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hamachi_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा hamachi_निजी *hmp = from_समयr(hmp, t, समयr);
	काष्ठा net_device *dev = hmp->mii_अगर.dev;
	व्योम __iomem *ioaddr = hmp->base;
	पूर्णांक next_tick = 10*HZ;

	अगर (hamachi_debug > 2) अणु
		prपूर्णांकk(KERN_INFO "%s: Hamachi Autonegotiation status %4.4x, LPA "
			   "%4.4x.\n", dev->name, पढ़ोw(ioaddr + ANStatus),
			   पढ़ोw(ioaddr + ANLinkPartnerAbility));
		prपूर्णांकk(KERN_INFO "%s: Autonegotiation regs %4.4x %4.4x %4.4x "
		       "%4.4x %4.4x %4.4x.\n", dev->name,
		       पढ़ोw(ioaddr + 0x0e0),
		       पढ़ोw(ioaddr + 0x0e2),
		       पढ़ोw(ioaddr + 0x0e4),
		       पढ़ोw(ioaddr + 0x0e6),
		       पढ़ोw(ioaddr + 0x0e8),
		       पढ़ोw(ioaddr + 0x0eA));
	पूर्ण
	/* We could करो something here... nah. */
	hmp->समयr.expires = RUN_AT(next_tick);
	add_समयr(&hmp->समयr);
पूर्ण

अटल व्योम hamachi_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	पूर्णांक i;
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	व्योम __iomem *ioaddr = hmp->base;

	prपूर्णांकk(KERN_WARNING "%s: Hamachi transmit timed out, status %8.8x,"
		   " resetting...\n", dev->name, (पूर्णांक)पढ़ोw(ioaddr + TxStatus));

	अणु
		prपूर्णांकk(KERN_DEBUG "  Rx ring %p: ", hmp->rx_ring);
		क्रम (i = 0; i < RX_RING_SIZE; i++)
			prपूर्णांकk(KERN_CONT " %8.8x",
			       le32_to_cpu(hmp->rx_ring[i].status_n_length));
		prपूर्णांकk(KERN_CONT "\n");
		prपूर्णांकk(KERN_DEBUG"  Tx ring %p: ", hmp->tx_ring);
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			prपूर्णांकk(KERN_CONT " %4.4x",
			       le32_to_cpu(hmp->tx_ring[i].status_n_length));
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण

	/* Reinit the hardware and make sure the Rx and Tx processes
		are up and running.
	 */
	dev->अगर_port = 0;
	/* The right way to करो Reset. -KDU
	 *		-Clear OWN bit in all Rx/Tx descriptors
	 *		-Wait 50 uS क्रम channels to go idle
	 *		-Turn off MAC receiver
	 *		-Issue Reset
	 */

	क्रम (i = 0; i < RX_RING_SIZE; i++)
		hmp->rx_ring[i].status_n_length &= cpu_to_le32(~DescOwn);

	/* Presume that all packets in the Tx queue are gone अगर we have to
	 * re-init the hardware.
	 */
	क्रम (i = 0; i < TX_RING_SIZE; i++)अणु
		काष्ठा sk_buff *skb;

		अगर (i >= TX_RING_SIZE - 1)
			hmp->tx_ring[i].status_n_length =
				cpu_to_le32(DescEndRing) |
				(hmp->tx_ring[i].status_n_length &
				 cpu_to_le32(0x0000ffff));
		अन्यथा
			hmp->tx_ring[i].status_n_length &= cpu_to_le32(0x0000ffff);
		skb = hmp->tx_skbuff[i];
		अगर (skb)अणु
			dma_unmap_single(&hmp->pci_dev->dev,
					 leXX_to_cpu(hmp->tx_ring[i].addr),
					 skb->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb(skb);
			hmp->tx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण

	udelay(60); /* Sleep 60 us just क्रम safety sake */
	ग_लिखोw(0x0002, ioaddr + RxCmd); /* STOP Rx */

	ग_लिखोb(0x01, ioaddr + ChipReset);  /* Reinit the hardware */

	hmp->tx_full = 0;
	hmp->cur_rx = hmp->cur_tx = 0;
	hmp->dirty_rx = hmp->dirty_tx = 0;
	/* Rx packets are also presumed lost; however, we need to make sure a
	 * ring of buffers is in tact. -KDU
	 */
	क्रम (i = 0; i < RX_RING_SIZE; i++)अणु
		काष्ठा sk_buff *skb = hmp->rx_skbuff[i];

		अगर (skb)अणु
			dma_unmap_single(&hmp->pci_dev->dev,
					 leXX_to_cpu(hmp->rx_ring[i].addr),
					 hmp->rx_buf_sz, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(skb);
			hmp->rx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण
	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb_ip_align(dev, hmp->rx_buf_sz);
		hmp->rx_skbuff[i] = skb;
		अगर (skb == शून्य)
			अवरोध;

		hmp->rx_ring[i].addr = cpu_to_leXX(dma_map_single(&hmp->pci_dev->dev,
								  skb->data,
								  hmp->rx_buf_sz,
								  DMA_FROM_DEVICE));
		hmp->rx_ring[i].status_n_length = cpu_to_le32(DescOwn |
			DescEndPacket | DescIntr | (hmp->rx_buf_sz - 2));
	पूर्ण
	hmp->dirty_rx = (अचिन्हित पूर्णांक)(i - RX_RING_SIZE);
	/* Mark the last entry as wrapping the ring. */
	hmp->rx_ring[RX_RING_SIZE-1].status_n_length |= cpu_to_le32(DescEndRing);

	/* Trigger an immediate transmit demand. */
	netअगर_trans_update(dev); /* prevent tx समयout */
	dev->stats.tx_errors++;

	/* Restart the chip's Tx/Rx processes . */
	ग_लिखोw(0x0002, ioaddr + TxCmd); /* STOP Tx */
	ग_लिखोw(0x0001, ioaddr + TxCmd); /* START Tx */
	ग_लिखोw(0x0001, ioaddr + RxCmd); /* START Rx */

	netअगर_wake_queue(dev);
पूर्ण


/* Initialize the Rx and Tx rings, aदीर्घ with various 'dev' bits. */
अटल व्योम hamachi_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	पूर्णांक i;

	hmp->tx_full = 0;
	hmp->cur_rx = hmp->cur_tx = 0;
	hmp->dirty_rx = hmp->dirty_tx = 0;

	/* +26 माला_लो the maximum ethernet encapsulation, +7 & ~7 because the
	 * card needs room to करो 8 byte alignment, +2 so we can reserve
	 * the first 2 bytes, and +16 माला_लो room क्रम the status word from the
	 * card.  -KDU
	 */
	hmp->rx_buf_sz = (dev->mtu <= 1492 ? PKT_BUF_SZ :
		(((dev->mtu+26+7) & ~7) + 16));

	/* Initialize all Rx descriptors. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		hmp->rx_ring[i].status_n_length = 0;
		hmp->rx_skbuff[i] = शून्य;
	पूर्ण
	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, hmp->rx_buf_sz + 2);
		hmp->rx_skbuff[i] = skb;
		अगर (skb == शून्य)
			अवरोध;
		skb_reserve(skb, 2); /* 16 byte align the IP header. */
		hmp->rx_ring[i].addr = cpu_to_leXX(dma_map_single(&hmp->pci_dev->dev,
								  skb->data,
								  hmp->rx_buf_sz,
								  DMA_FROM_DEVICE));
		/* -2 because it करोesn't REALLY have that first 2 bytes -KDU */
		hmp->rx_ring[i].status_n_length = cpu_to_le32(DescOwn |
			DescEndPacket | DescIntr | (hmp->rx_buf_sz -2));
	पूर्ण
	hmp->dirty_rx = (अचिन्हित पूर्णांक)(i - RX_RING_SIZE);
	hmp->rx_ring[RX_RING_SIZE-1].status_n_length |= cpu_to_le32(DescEndRing);

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		hmp->tx_skbuff[i] = शून्य;
		hmp->tx_ring[i].status_n_length = 0;
	पूर्ण
	/* Mark the last entry of the ring */
	hmp->tx_ring[TX_RING_SIZE-1].status_n_length |= cpu_to_le32(DescEndRing);
पूर्ण


अटल netdev_tx_t hamachi_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	अचिन्हित entry;
	u16 status;

	/* Ok, now make sure that the queue has space beक्रमe trying to
		add another skbuff.  अगर we वापस non-zero the scheduler
		should पूर्णांकerpret this as a queue full and requeue the buffer
		क्रम later.
	 */
	अगर (hmp->tx_full) अणु
		/* We should NEVER reach this poपूर्णांक -KDU */
		prपूर्णांकk(KERN_WARNING "%s: Hamachi transmit queue full at slot %d.\n",dev->name, hmp->cur_tx);

		/* Wake the potentially-idle transmit channel. */
		/* If we करोn't need to read status, DON'T -KDU */
		status=पढ़ोw(hmp->base + TxStatus);
		अगर( !(status & 0x0001) || (status & 0x0002))
			ग_लिखोw(0x0001, hmp->base + TxCmd);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Caution: the ग_लिखो order is important here, set the field
	   with the "ownership" bits last. */

	/* Calculate the next Tx descriptor entry. */
	entry = hmp->cur_tx % TX_RING_SIZE;

	hmp->tx_skbuff[entry] = skb;

	hmp->tx_ring[entry].addr = cpu_to_leXX(dma_map_single(&hmp->pci_dev->dev,
							      skb->data,
							      skb->len,
							      DMA_TO_DEVICE));

	/* Hmmmm, could probably put a DescIntr on these, but the way
		the driver is currently coded makes Tx पूर्णांकerrupts unnecessary
		since the clearing of the Tx ring is handled by the start_xmit
		routine.  This organization helps mitigate the पूर्णांकerrupts a
		bit and probably renders the max_tx_latency param useless.

		Update: Putting a DescIntr bit on all of the descriptors and
		mitigating पूर्णांकerrupt frequency with the tx_min_pkt parameter. -KDU
	*/
	अगर (entry >= TX_RING_SIZE-1)		 /* Wrap ring */
		hmp->tx_ring[entry].status_n_length = cpu_to_le32(DescOwn |
			DescEndPacket | DescEndRing | DescIntr | skb->len);
	अन्यथा
		hmp->tx_ring[entry].status_n_length = cpu_to_le32(DescOwn |
			DescEndPacket | DescIntr | skb->len);
	hmp->cur_tx++;

	/* Non-x86 Toकरो: explicitly flush cache lines here. */

	/* Wake the potentially-idle transmit channel. */
	/* If we करोn't need to read status, DON'T -KDU */
	status=पढ़ोw(hmp->base + TxStatus);
	अगर( !(status & 0x0001) || (status & 0x0002))
		ग_लिखोw(0x0001, hmp->base + TxCmd);

	/* Immediately beक्रमe वापसing, let's clear as many entries as we can. */
	hamachi_tx(dev);

	/* We should kick the bottom half here, since we are not accepting
	 * पूर्णांकerrupts with every packet.  i.e. realize that Gigabit ethernet
	 * can transmit faster than ordinary machines can load packets;
	 * hence, any packet that got put off because we were in the transmit
	 * routine should IMMEDIATELY get a chance to be re-queued. -KDU
	 */
	अगर ((hmp->cur_tx - hmp->dirty_tx) < (TX_RING_SIZE - 4))
		netअगर_wake_queue(dev);  /* Typical path */
	अन्यथा अणु
		hmp->tx_full = 1;
		netअगर_stop_queue(dev);
	पूर्ण

	अगर (hamachi_debug > 4) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Hamachi transmit frame #%d queued in slot %d.\n",
			   dev->name, hmp->cur_tx, entry);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */
अटल irqवापस_t hamachi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	व्योम __iomem *ioaddr = hmp->base;
	दीर्घ boguscnt = max_पूर्णांकerrupt_work;
	पूर्णांक handled = 0;

#अगर_अघोषित final_version			/* Can never occur. */
	अगर (dev == शून्य) अणु
		prपूर्णांकk (KERN_ERR "hamachi_interrupt(): irq %d for unknown device.\n", irq);
		वापस IRQ_NONE;
	पूर्ण
#पूर्ण_अगर

	spin_lock(&hmp->lock);

	करो अणु
		u32 पूर्णांकr_status = पढ़ोl(ioaddr + InterruptClear);

		अगर (hamachi_debug > 4)
			prपूर्णांकk(KERN_DEBUG "%s: Hamachi interrupt, status %4.4x.\n",
				   dev->name, पूर्णांकr_status);

		अगर (पूर्णांकr_status == 0)
			अवरोध;

		handled = 1;

		अगर (पूर्णांकr_status & IntrRxDone)
			hamachi_rx(dev);

		अगर (पूर्णांकr_status & IntrTxDone)अणु
			/* This code should RARELY need to execute. After all, this is
			 * a gigabit link, it should consume packets as fast as we put
			 * them in AND we clear the Tx ring in hamachi_start_xmit().
			 */
			अगर (hmp->tx_full)अणु
				क्रम (; hmp->cur_tx - hmp->dirty_tx > 0; hmp->dirty_tx++)अणु
					पूर्णांक entry = hmp->dirty_tx % TX_RING_SIZE;
					काष्ठा sk_buff *skb;

					अगर (hmp->tx_ring[entry].status_n_length & cpu_to_le32(DescOwn))
						अवरोध;
					skb = hmp->tx_skbuff[entry];
					/* Free the original skb. */
					अगर (skb)अणु
						dma_unmap_single(&hmp->pci_dev->dev,
								 leXX_to_cpu(hmp->tx_ring[entry].addr),
								 skb->len,
								 DMA_TO_DEVICE);
						dev_consume_skb_irq(skb);
						hmp->tx_skbuff[entry] = शून्य;
					पूर्ण
					hmp->tx_ring[entry].status_n_length = 0;
					अगर (entry >= TX_RING_SIZE-1)
						hmp->tx_ring[TX_RING_SIZE-1].status_n_length |=
							cpu_to_le32(DescEndRing);
					dev->stats.tx_packets++;
				पूर्ण
				अगर (hmp->cur_tx - hmp->dirty_tx < TX_RING_SIZE - 4)अणु
					/* The ring is no दीर्घer full */
					hmp->tx_full = 0;
					netअगर_wake_queue(dev);
				पूर्ण
			पूर्ण अन्यथा अणु
				netअगर_wake_queue(dev);
			पूर्ण
		पूर्ण


		/* Abnormal error summary/uncommon events handlers. */
		अगर (पूर्णांकr_status &
			(IntrTxPCIFault | IntrTxPCIErr | IntrRxPCIFault | IntrRxPCIErr |
			 LinkChange | NegotiationChange | StatsMax))
			hamachi_error(dev, पूर्णांकr_status);

		अगर (--boguscnt < 0) अणु
			prपूर्णांकk(KERN_WARNING "%s: Too much work at interrupt, status=0x%4.4x.\n",
				   dev->name, पूर्णांकr_status);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	अगर (hamachi_debug > 3)
		prपूर्णांकk(KERN_DEBUG "%s: exiting interrupt, status=%#4.4x.\n",
			   dev->name, पढ़ोl(ioaddr + IntrStatus));

#अगर_अघोषित final_version
	/* Code that should never be run!  Perhaps हटाओ after testing.. */
	अणु
		अटल पूर्णांक stopit = 10;
		अगर (dev->start == 0  &&  --stopit < 0) अणु
			prपूर्णांकk(KERN_ERR "%s: Emergency stop, looping startup interrupt.\n",
				   dev->name);
			मुक्त_irq(irq, dev);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	spin_unlock(&hmp->lock);
	वापस IRQ_RETVAL(handled);
पूर्ण

/* This routine is logically part of the पूर्णांकerrupt handler, but separated
   क्रम clarity and better रेजिस्टर allocation. */
अटल पूर्णांक hamachi_rx(काष्ठा net_device *dev)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	पूर्णांक entry = hmp->cur_rx % RX_RING_SIZE;
	पूर्णांक boguscnt = (hmp->dirty_rx + RX_RING_SIZE) - hmp->cur_rx;

	अगर (hamachi_debug > 4) अणु
		prपूर्णांकk(KERN_DEBUG " In hamachi_rx(), entry %d status %4.4x.\n",
			   entry, hmp->rx_ring[entry].status_n_length);
	पूर्ण

	/* If EOP is set on the next entry, it's a new packet. Send it up. */
	जबतक (1) अणु
		काष्ठा hamachi_desc *desc = &(hmp->rx_ring[entry]);
		u32 desc_status = le32_to_cpu(desc->status_n_length);
		u16 data_size = desc_status;	/* Implicit truncate */
		u8 *buf_addr;
		s32 frame_status;

		अगर (desc_status & DescOwn)
			अवरोध;
		dma_sync_single_क्रम_cpu(&hmp->pci_dev->dev,
					leXX_to_cpu(desc->addr),
					hmp->rx_buf_sz, DMA_FROM_DEVICE);
		buf_addr = (u8 *) hmp->rx_skbuff[entry]->data;
		frame_status = get_unaligned_le32(&(buf_addr[data_size - 12]));
		अगर (hamachi_debug > 4)
			prपूर्णांकk(KERN_DEBUG "  hamachi_rx() status was %8.8x.\n",
				frame_status);
		अगर (--boguscnt < 0)
			अवरोध;
		अगर ( ! (desc_status & DescEndPacket)) अणु
			prपूर्णांकk(KERN_WARNING "%s: Oversized Ethernet frame spanned "
				   "multiple buffers, entry %#x length %d status %4.4x!\n",
				   dev->name, hmp->cur_rx, data_size, desc_status);
			prपूर्णांकk(KERN_WARNING "%s: Oversized Ethernet frame %p vs %p.\n",
				   dev->name, desc, &hmp->rx_ring[hmp->cur_rx % RX_RING_SIZE]);
			prपूर्णांकk(KERN_WARNING "%s: Oversized Ethernet frame -- next status %x/%x last status %x.\n",
				   dev->name,
				   le32_to_cpu(hmp->rx_ring[(hmp->cur_rx+1) % RX_RING_SIZE].status_n_length) & 0xffff0000,
				   le32_to_cpu(hmp->rx_ring[(hmp->cur_rx+1) % RX_RING_SIZE].status_n_length) & 0x0000ffff,
				   le32_to_cpu(hmp->rx_ring[(hmp->cur_rx-1) % RX_RING_SIZE].status_n_length));
			dev->stats.rx_length_errors++;
		पूर्ण /* अन्यथा  Omit क्रम prototype errata??? */
		अगर (frame_status & 0x00380000) अणु
			/* There was an error. */
			अगर (hamachi_debug > 2)
				prपूर्णांकk(KERN_DEBUG "  hamachi_rx() Rx error was %8.8x.\n",
					   frame_status);
			dev->stats.rx_errors++;
			अगर (frame_status & 0x00600000)
				dev->stats.rx_length_errors++;
			अगर (frame_status & 0x00080000)
				dev->stats.rx_frame_errors++;
			अगर (frame_status & 0x00100000)
				dev->stats.rx_crc_errors++;
			अगर (frame_status < 0)
				dev->stats.rx_dropped++;
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb;
			/* Omit CRC */
			u16 pkt_len = (frame_status & 0x07ff) - 4;
#अगर_घोषित RX_CHECKSUM
			u32 pfck = *(u32 *) &buf_addr[data_size - 8];
#पूर्ण_अगर


#अगर_अघोषित final_version
			अगर (hamachi_debug > 4)
				prपूर्णांकk(KERN_DEBUG "  hamachi_rx() normal Rx pkt length %d"
					   " of %d, bogus_cnt %d.\n",
					   pkt_len, data_size, boguscnt);
			अगर (hamachi_debug > 5)
				prपूर्णांकk(KERN_DEBUG"%s:  rx status %8.8x %8.8x %8.8x %8.8x %8.8x.\n",
					   dev->name,
					   *(s32*)&(buf_addr[data_size - 20]),
					   *(s32*)&(buf_addr[data_size - 16]),
					   *(s32*)&(buf_addr[data_size - 12]),
					   *(s32*)&(buf_addr[data_size - 8]),
					   *(s32*)&(buf_addr[data_size - 4]));
#पूर्ण_अगर
			/* Check अगर the packet is दीर्घ enough to accept without copying
			   to a minimally-sized skbuff. */
			अगर (pkt_len < rx_copyअवरोध &&
			    (skb = netdev_alloc_skb(dev, pkt_len + 2)) != शून्य) अणु
#अगर_घोषित RX_CHECKSUM
				prपूर्णांकk(KERN_ERR "%s: rx_copybreak non-zero "
				  "not good with RX_CHECKSUM\n", dev->name);
#पूर्ण_अगर
				skb_reserve(skb, 2);	/* 16 byte align the IP header */
				dma_sync_single_क्रम_cpu(&hmp->pci_dev->dev,
							leXX_to_cpu(hmp->rx_ring[entry].addr),
							hmp->rx_buf_sz,
							DMA_FROM_DEVICE);
				/* Call copy + cksum अगर available. */
#अगर 1 || USE_IP_COPYSUM
				skb_copy_to_linear_data(skb,
					hmp->rx_skbuff[entry]->data, pkt_len);
				skb_put(skb, pkt_len);
#अन्यथा
				skb_put_data(skb, hmp->rx_ring_dma
					     + entry*माप(*desc), pkt_len);
#पूर्ण_अगर
				dma_sync_single_क्रम_device(&hmp->pci_dev->dev,
							   leXX_to_cpu(hmp->rx_ring[entry].addr),
							   hmp->rx_buf_sz,
							   DMA_FROM_DEVICE);
			पूर्ण अन्यथा अणु
				dma_unmap_single(&hmp->pci_dev->dev,
						 leXX_to_cpu(hmp->rx_ring[entry].addr),
						 hmp->rx_buf_sz,
						 DMA_FROM_DEVICE);
				skb_put(skb = hmp->rx_skbuff[entry], pkt_len);
				hmp->rx_skbuff[entry] = शून्य;
			पूर्ण
			skb->protocol = eth_type_trans(skb, dev);


#अगर_घोषित RX_CHECKSUM
			/* TCP or UDP on ipv4, DIX encoding */
			अगर (pfck>>24 == 0x91 || pfck>>24 == 0x51) अणु
				काष्ठा iphdr *ih = (काष्ठा iphdr *) skb->data;
				/* Check that IP packet is at least 46 bytes, otherwise,
				 * there may be pad bytes included in the hardware checksum.
				 * This wouldn't happen अगर everyone padded with 0.
				 */
				अगर (ntohs(ih->tot_len) >= 46)अणु
					/* करोn't worry about frags */
					अगर (!(ih->frag_off & cpu_to_be16(IP_MF|IP_OFFSET))) अणु
						u32 inv = *(u32 *) &buf_addr[data_size - 16];
						u32 *p = (u32 *) &buf_addr[data_size - 20];
						रेजिस्टर u32 crc, p_r, p_r1;

						अगर (inv & 4) अणु
							inv &= ~4;
							--p;
						पूर्ण
						p_r = *p;
						p_r1 = *(p-1);
						चयन (inv) अणु
							हाल 0:
								crc = (p_r & 0xffff) + (p_r >> 16);
								अवरोध;
							हाल 1:
								crc = (p_r >> 16) + (p_r & 0xffff)
									+ (p_r1 >> 16 & 0xff00);
								अवरोध;
							हाल 2:
								crc = p_r + (p_r1 >> 16);
								अवरोध;
							हाल 3:
								crc = p_r + (p_r1 & 0xff00) + (p_r1 >> 16);
								अवरोध;
							शेष:	/*NOTREACHED*/ crc = 0;
						पूर्ण
						अगर (crc & 0xffff0000) अणु
							crc &= 0xffff;
							++crc;
						पूर्ण
						/* tcp/udp will add in pseuकरो */
						skb->csum = ntohs(pfck & 0xffff);
						अगर (skb->csum > crc)
							skb->csum -= crc;
						अन्यथा
							skb->csum += (~crc & 0xffff);
						/*
						* could करो the pseuकरो myself and वापस
						* CHECKSUM_UNNECESSARY
						*/
						skb->ip_summed = CHECKSUM_COMPLETE;
					पूर्ण
				पूर्ण
			पूर्ण
#पूर्ण_अगर  /* RX_CHECKSUM */

			netअगर_rx(skb);
			dev->stats.rx_packets++;
		पूर्ण
		entry = (++hmp->cur_rx) % RX_RING_SIZE;
	पूर्ण

	/* Refill the Rx ring buffers. */
	क्रम (; hmp->cur_rx - hmp->dirty_rx > 0; hmp->dirty_rx++) अणु
		काष्ठा hamachi_desc *desc;

		entry = hmp->dirty_rx % RX_RING_SIZE;
		desc = &(hmp->rx_ring[entry]);
		अगर (hmp->rx_skbuff[entry] == शून्य) अणु
			काष्ठा sk_buff *skb = netdev_alloc_skb(dev, hmp->rx_buf_sz + 2);

			hmp->rx_skbuff[entry] = skb;
			अगर (skb == शून्य)
				अवरोध;		/* Better luck next round. */
			skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
			desc->addr = cpu_to_leXX(dma_map_single(&hmp->pci_dev->dev,
								skb->data,
								hmp->rx_buf_sz,
								DMA_FROM_DEVICE));
		पूर्ण
		desc->status_n_length = cpu_to_le32(hmp->rx_buf_sz);
		अगर (entry >= RX_RING_SIZE-1)
			desc->status_n_length |= cpu_to_le32(DescOwn |
				DescEndPacket | DescEndRing | DescIntr);
		अन्यथा
			desc->status_n_length |= cpu_to_le32(DescOwn |
				DescEndPacket | DescIntr);
	पूर्ण

	/* Restart Rx engine अगर stopped. */
	/* If we करोn't need to check status, don't. -KDU */
	अगर (पढ़ोw(hmp->base + RxStatus) & 0x0002)
		ग_लिखोw(0x0001, hmp->base + RxCmd);

	वापस 0;
पूर्ण

/* This is more properly named "uncommon interrupt events", as it covers more
   than just errors. */
अटल व्योम hamachi_error(काष्ठा net_device *dev, पूर्णांक पूर्णांकr_status)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	व्योम __iomem *ioaddr = hmp->base;

	अगर (पूर्णांकr_status & (LinkChange|NegotiationChange)) अणु
		अगर (hamachi_debug > 1)
			prपूर्णांकk(KERN_INFO "%s: Link changed: AutoNegotiation Ctrl"
				   " %4.4x, Status %4.4x %4.4x Intr status %4.4x.\n",
				   dev->name, पढ़ोw(ioaddr + 0x0E0), पढ़ोw(ioaddr + 0x0E2),
				   पढ़ोw(ioaddr + ANLinkPartnerAbility),
				   पढ़ोl(ioaddr + IntrStatus));
		अगर (पढ़ोw(ioaddr + ANStatus) & 0x20)
			ग_लिखोb(0x01, ioaddr + LEDCtrl);
		अन्यथा
			ग_लिखोb(0x03, ioaddr + LEDCtrl);
	पूर्ण
	अगर (पूर्णांकr_status & StatsMax) अणु
		hamachi_get_stats(dev);
		/* Read the overflow bits to clear. */
		पढ़ोl(ioaddr + 0x370);
		पढ़ोl(ioaddr + 0x3F0);
	पूर्ण
	अगर ((पूर्णांकr_status & ~(LinkChange|StatsMax|NegotiationChange|IntrRxDone|IntrTxDone)) &&
	    hamachi_debug)
		prपूर्णांकk(KERN_ERR "%s: Something Wicked happened! %4.4x.\n",
		       dev->name, पूर्णांकr_status);
	/* Hmmmmm, it's not clear how to recover from PCI faults. */
	अगर (पूर्णांकr_status & (IntrTxPCIErr | IntrTxPCIFault))
		dev->stats.tx_fअगरo_errors++;
	अगर (पूर्णांकr_status & (IntrRxPCIErr | IntrRxPCIFault))
		dev->stats.rx_fअगरo_errors++;
पूर्ण

अटल पूर्णांक hamachi_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	व्योम __iomem *ioaddr = hmp->base;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	netअगर_stop_queue(dev);

	अगर (hamachi_debug > 1) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Shutting down ethercard, status was Tx %4.4x Rx %4.4x Int %2.2x.\n",
			   dev->name, पढ़ोw(ioaddr + TxStatus),
			   पढ़ोw(ioaddr + RxStatus), पढ़ोl(ioaddr + IntrStatus));
		prपूर्णांकk(KERN_DEBUG "%s: Queue pointers were Tx %d / %d,  Rx %d / %d.\n",
			   dev->name, hmp->cur_tx, hmp->dirty_tx, hmp->cur_rx, hmp->dirty_rx);
	पूर्ण

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	ग_लिखोl(0x0000, ioaddr + InterruptEnable);

	/* Stop the chip's Tx and Rx processes. */
	ग_लिखोl(2, ioaddr + RxCmd);
	ग_लिखोw(2, ioaddr + TxCmd);

#अगर_घोषित __i386__
	अगर (hamachi_debug > 2) अणु
		prपूर्णांकk(KERN_DEBUG "  Tx ring at %8.8x:\n",
			   (पूर्णांक)hmp->tx_ring_dma);
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			prपूर्णांकk(KERN_DEBUG " %c #%d desc. %8.8x %8.8x.\n",
				   पढ़ोl(ioaddr + TxCurPtr) == (दीर्घ)&hmp->tx_ring[i] ? '>' : ' ',
				   i, hmp->tx_ring[i].status_n_length, hmp->tx_ring[i].addr);
		prपूर्णांकk(KERN_DEBUG "  Rx ring %8.8x:\n",
			   (पूर्णांक)hmp->rx_ring_dma);
		क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
			prपूर्णांकk(KERN_DEBUG " %c #%d desc. %4.4x %8.8x\n",
				   पढ़ोl(ioaddr + RxCurPtr) == (दीर्घ)&hmp->rx_ring[i] ? '>' : ' ',
				   i, hmp->rx_ring[i].status_n_length, hmp->rx_ring[i].addr);
			अगर (hamachi_debug > 6) अणु
				अगर (*(u8*)hmp->rx_skbuff[i]->data != 0x69) अणु
					u16 *addr = (u16 *)
						hmp->rx_skbuff[i]->data;
					पूर्णांक j;
					prपूर्णांकk(KERN_DEBUG "Addr: ");
					क्रम (j = 0; j < 0x50; j++)
						prपूर्णांकk(" %4.4x", addr[j]);
					prपूर्णांकk("\n");
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* __i386__ debugging only */

	मुक्त_irq(hmp->pci_dev->irq, dev);

	del_समयr_sync(&hmp->समयr);

	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		skb = hmp->rx_skbuff[i];
		hmp->rx_ring[i].status_n_length = 0;
		अगर (skb) अणु
			dma_unmap_single(&hmp->pci_dev->dev,
					 leXX_to_cpu(hmp->rx_ring[i].addr),
					 hmp->rx_buf_sz, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(skb);
			hmp->rx_skbuff[i] = शून्य;
		पूर्ण
		hmp->rx_ring[i].addr = cpu_to_leXX(0xBADF00D0); /* An invalid address. */
	पूर्ण
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		skb = hmp->tx_skbuff[i];
		अगर (skb) अणु
			dma_unmap_single(&hmp->pci_dev->dev,
					 leXX_to_cpu(hmp->tx_ring[i].addr),
					 skb->len, DMA_TO_DEVICE);
			dev_kमुक्त_skb(skb);
			hmp->tx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण

	ग_लिखोb(0x00, ioaddr + LEDCtrl);

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *hamachi_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	व्योम __iomem *ioaddr = hmp->base;

	/* We should lock this segment of code क्रम SMP eventually, although
	   the vulnerability winकरोw is very small and statistics are
	   non-critical. */
        /* Ok, what goes here?  This appears to be stuck at 21 packets
           according to अगरconfig.  It करोes get incremented in hamachi_tx(),
           so I think I'll comment it out here and see अगर better things
           happen.
        */
	/* dev->stats.tx_packets	= पढ़ोl(ioaddr + 0x000); */

	/* Total Uni+Brd+Multi */
	dev->stats.rx_bytes = पढ़ोl(ioaddr + 0x330);
	/* Total Uni+Brd+Multi */
	dev->stats.tx_bytes = पढ़ोl(ioaddr + 0x3B0);
	/* Multicast Rx */
	dev->stats.multicast = पढ़ोl(ioaddr + 0x320);

	/* Over+Undersized */
	dev->stats.rx_length_errors = पढ़ोl(ioaddr + 0x368);
	/* Jabber */
	dev->stats.rx_over_errors = पढ़ोl(ioaddr + 0x35C);
	/* Jabber */
	dev->stats.rx_crc_errors = पढ़ोl(ioaddr + 0x360);
	/* Symbol Errs */
	dev->stats.rx_frame_errors = पढ़ोl(ioaddr + 0x364);
	/* Dropped */
	dev->stats.rx_missed_errors = पढ़ोl(ioaddr + 0x36C);

	वापस &dev->stats;
पूर्ण

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा hamachi_निजी *hmp = netdev_priv(dev);
	व्योम __iomem *ioaddr = hmp->base;

	अगर (dev->flags & IFF_PROMISC) अणु			/* Set promiscuous. */
		ग_लिखोw(0x000F, ioaddr + AddrMode);
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > 63) || (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to match, or accept all multicasts. */
		ग_लिखोw(0x000B, ioaddr + AddrMode);
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु /* Must use the CAM filter. */
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक i = 0;

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			ग_लिखोl(*(u32 *)(ha->addr), ioaddr + 0x100 + i*8);
			ग_लिखोl(0x20000 | (*(u16 *)&ha->addr[4]),
				   ioaddr + 0x104 + i*8);
			i++;
		पूर्ण
		/* Clear reमुख्यing entries. */
		क्रम (; i < 64; i++)
			ग_लिखोl(0, ioaddr + 0x104 + i*8);
		ग_लिखोw(0x0003, ioaddr + AddrMode);
	पूर्ण अन्यथा अणु					/* Normal, unicast/broadcast-only mode. */
		ग_लिखोw(0x0001, ioaddr + AddrMode);
	पूर्ण
पूर्ण

अटल पूर्णांक check_अगर_running(काष्ठा net_device *dev)
अणु
	अगर (!netअगर_running(dev))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम hamachi_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा hamachi_निजी *np = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(np->pci_dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक hamachi_get_link_ksettings(काष्ठा net_device *dev,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा hamachi_निजी *np = netdev_priv(dev);
	spin_lock_irq(&np->lock);
	mii_ethtool_get_link_ksettings(&np->mii_अगर, cmd);
	spin_unlock_irq(&np->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक hamachi_set_link_ksettings(काष्ठा net_device *dev,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा hamachi_निजी *np = netdev_priv(dev);
	पूर्णांक res;
	spin_lock_irq(&np->lock);
	res = mii_ethtool_set_link_ksettings(&np->mii_अगर, cmd);
	spin_unlock_irq(&np->lock);
	वापस res;
पूर्ण

अटल पूर्णांक hamachi_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा hamachi_निजी *np = netdev_priv(dev);
	वापस mii_nway_restart(&np->mii_अगर);
पूर्ण

अटल u32 hamachi_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा hamachi_निजी *np = netdev_priv(dev);
	वापस mii_link_ok(&np->mii_अगर);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ethtool_ops = अणु
	.begin = check_अगर_running,
	.get_drvinfo = hamachi_get_drvinfo,
	.nway_reset = hamachi_nway_reset,
	.get_link = hamachi_get_link,
	.get_link_ksettings = hamachi_get_link_ksettings,
	.set_link_ksettings = hamachi_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops ethtool_ops_no_mii = अणु
	.begin = check_अगर_running,
	.get_drvinfo = hamachi_get_drvinfo,
पूर्ण;

अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा hamachi_निजी *np = netdev_priv(dev);
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);
	पूर्णांक rc;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	अगर (cmd == (SIOCDEVPRIVATE+3)) अणु /* set rx,tx पूर्णांकr params */
		u32 *d = (u32 *)&rq->अगरr_अगरru;
		/* Should add this check here or an ordinary user can करो nasty
		 * things. -KDU
		 *
		 * TODO: Shut करोwn the Rx and Tx engines जबतक करोing this.
		 */
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		ग_लिखोl(d[0], np->base + TxIntrCtrl);
		ग_लिखोl(d[1], np->base + RxIntrCtrl);
		prपूर्णांकk(KERN_NOTICE "%s: tx %08x, rx %08x intr\n", dev->name,
		  (u32) पढ़ोl(np->base + TxIntrCtrl),
		  (u32) पढ़ोl(np->base + RxIntrCtrl));
		rc = 0;
	पूर्ण

	अन्यथा अणु
		spin_lock_irq(&np->lock);
		rc = generic_mii_ioctl(&np->mii_अगर, data, cmd, शून्य);
		spin_unlock_irq(&np->lock);
	पूर्ण

	वापस rc;
पूर्ण


अटल व्योम hamachi_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
		काष्ठा hamachi_निजी *hmp = netdev_priv(dev);

		dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, hmp->rx_ring,
				  hmp->rx_ring_dma);
		dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, hmp->tx_ring,
				  hmp->tx_ring_dma);
		unरेजिस्टर_netdev(dev);
		iounmap(hmp->base);
		मुक्त_netdev(dev);
		pci_release_regions(pdev);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id hamachi_pci_tbl[] = अणु
	अणु 0x1318, 0x0911, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, hamachi_pci_tbl);

अटल काष्ठा pci_driver hamachi_driver = अणु
	.name		= DRV_NAME,
	.id_table	= hamachi_pci_tbl,
	.probe		= hamachi_init_one,
	.हटाओ		= hamachi_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init hamachi_init (व्योम)
अणु
/* when a module, this is prपूर्णांकed whether or not devices are found in probe */
#अगर_घोषित MODULE
	prपूर्णांकk(version);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&hamachi_driver);
पूर्ण

अटल व्योम __निकास hamachi_निकास (व्योम)
अणु
	pci_unरेजिस्टर_driver(&hamachi_driver);
पूर्ण


module_init(hamachi_init);
module_निकास(hamachi_निकास);
