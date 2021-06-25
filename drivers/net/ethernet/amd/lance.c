<शैली गुरु>
/* lance.c: An AMD LANCE/PCnet ethernet driver क्रम Linux. */
/*
	Written/copyright 1993-1998 by Donald Becker.

	Copyright 1993 United States Government as represented by the
	Director, National Security Agency.
	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	This driver is क्रम the Allied Telesis AT1500 and HP J2405A, and should work
	with most other LANCE-based bus-master (NE2100/NE2500) ethercards.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	Andrey V. Savochkin:
	- alignment problem with 1.3.* kernel and some minor changes.
	Thomas Bogenकरोerfer (tsbogend@bigbug.franken.de):
	- added support क्रम Linux/Alpha, but हटाओd most of it, because
        it worked only क्रम the PCI chip.
      - added hook क्रम the 32bit lance driver
      - added PCnetPCI II (79C970A) to chip table
	Paul Gorपंचांगaker (gpg109@rsphy1.anu.edu.au):
	- hopefully fix above so Linux/Alpha can use ISA cards too.
    8/20/96 Fixed 7990 स्वतःIRQ failure and reversed unneeded alignment -djb
    v1.12 10/27/97 Module support -djb
    v1.14  2/3/98 Module support modअगरied, made PCI support optional -djb
    v1.15 5/27/99 Fixed bug in the cleanup_module(). dev->priv was मुक्तd
                  beक्रमe unरेजिस्टर_netdev() which caused शून्य poपूर्णांकer
                  reference later in the chain (in rtnetlink_fill_अगरinfo())
                  -- Mika Kuoppala <miku@iki.fi>

    Forward ported v1.14 to 2.1.129, merged the PCI and misc changes from
    the 2.1 version of the old driver - Alan Cox

    Get rid of check_region, check kदो_स्मृति वापस in lance_probe1
    Arnalकरो Carvalho de Melo <acme@conectiva.com.br> - 11/01/2001

	Reworked detection, added support क्रम Racal InterLan EtherBlaster cards
	Vesselin Kostadinov <vesok at yahoo करोt com > - 22/4/2004
*/

अटल स्थिर अक्षर version[] = "lance.c:v1.16 2006/11/09 dplatt@3do.com, becker@cesdis.gsfc.nasa.gov\n";

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

अटल अचिन्हित पूर्णांक lance_portlist[] __initdata = अणु 0x300, 0x320, 0x340, 0x360, 0पूर्ण;
अटल पूर्णांक lance_probe1(काष्ठा net_device *dev, पूर्णांक ioaddr, पूर्णांक irq, पूर्णांक options);
अटल पूर्णांक __init करो_lance_probe(काष्ठा net_device *dev);


अटल काष्ठा card अणु
	अक्षर id_offset14;
	अक्षर id_offset15;
पूर्ण cards[] = अणु
	अणु	//"normal"
		.id_offset14 = 0x57,
		.id_offset15 = 0x57,
	पूर्ण,
	अणु	//NI6510EB
		.id_offset14 = 0x52,
		.id_offset15 = 0x44,
	पूर्ण,
	अणु	//Racal InterLan EtherBlaster
		.id_offset14 = 0x52,
		.id_offset15 = 0x49,
	पूर्ण,
पूर्ण;
#घोषणा NUM_CARDS 3

#अगर_घोषित LANCE_DEBUG
अटल पूर्णांक lance_debug = LANCE_DEBUG;
#अन्यथा
अटल पूर्णांक lance_debug = 1;
#पूर्ण_अगर

/*
				Theory of Operation

I. Board Compatibility

This device driver is deचिन्हित क्रम the AMD 79C960, the "PCnet-ISA
single-chip ethernet controller क्रम ISA".  This chip is used in a wide
variety of boards from venकरोrs such as Allied Telesis, HP, Kingston,
and Boca.  This driver is also पूर्णांकended to work with older AMD 7990
designs, such as the NE1500 and NE2100, and newer 79C961.  For convenience,
I use the name LANCE to refer to all of the AMD chips, even though it properly
refers only to the original 7990.

II. Board-specअगरic settings

The driver is deचिन्हित to work the boards that use the faster
bus-master mode, rather than in shared memory mode.	 (Only older designs
have on-board buffer memory needed to support the slower shared memory mode.)

Most ISA boards have jumpered settings क्रम the I/O base, IRQ line, and DMA
channel.  This driver probes the likely base addresses:
अणु0x300, 0x320, 0x340, 0x360पूर्ण.
After the board is found it generates a DMA-समयout पूर्णांकerrupt and uses
स्वतःIRQ to find the IRQ line.  The DMA channel can be set with the low bits
of the otherwise-unused dev->mem_start value (aka PARAM1).  If unset it is
probed क्रम by enabling each मुक्त DMA channel in turn and checking अगर
initialization succeeds.

The HP-J2405A board is an exception: with this board it is easy to पढ़ो the
EEPROM-set values क्रम the base, IRQ, and DMA.  (Of course you must alपढ़ोy
_know_ the base address -- that field is क्रम writing the EEPROM.)

III. Driver operation

IIIa. Ring buffers
The LANCE uses ring buffers of Tx and Rx descriptors.  Each entry describes
the base and length of the data buffer, aदीर्घ with status bits.	 The length
of these buffers is set by LANCE_LOG_अणुRX,TXपूर्ण_BUFFERS, which is log_2() of
the buffer length (rather than being directly the buffer length) क्रम
implementation ease.  The current values are 2 (Tx) and 4 (Rx), which leads to
ring sizes of 4 (Tx) and 16 (Rx).  Increasing the number of ring entries
needlessly uses extra space and reduces the chance that an upper layer will
be able to reorder queued Tx packets based on priority.	 Decreasing the number
of entries makes it more dअगरficult to achieve back-to-back packet transmission
and increases the chance that Rx ring will overflow.  (Consider the worst हाल
of receiving back-to-back minimum-sized packets.)

The LANCE has the capability to "chain" both Rx and Tx buffers, but this driver
अटलally allocates full-sized (slightly oversized -- PKT_BUF_SZ) buffers to
aव्योम the administrative overhead. For the Rx side this aव्योमs dynamically
allocating full-sized buffers "just in case", at the expense of a
memory-to-memory data copy क्रम each packet received.  For most प्रणालीs this
is a good tradeoff: the Rx buffer will always be in low memory, the copy
is inexpensive, and it primes the cache क्रम later packet processing.  For Tx
the buffers are only used when needed as low-memory bounce buffers.

IIIB. 16M memory limitations.
For the ISA bus master mode all काष्ठाures used directly by the LANCE,
the initialization block, Rx and Tx rings, and data buffers, must be
accessible from the ISA bus, i.e. in the lower 16M of real memory.
This is a problem क्रम current Linux kernels on >16M machines. The network
devices are initialized after memory initialization, and the kernel करोles out
memory from the top of memory करोwnward.	 The current solution is to have a
special network initialization routine that's called beक्रमe memory
initialization; this will eventually be generalized क्रम all network devices.
As mentioned beक्रमe, low-memory "bounce-buffers" are used when needed.

IIIC. Synchronization
The driver runs as two independent, single-thपढ़ोed flows of control.  One
is the send-packet routine, which enक्रमces single-thपढ़ोed use by the
dev->tbusy flag.  The other thपढ़ो is the पूर्णांकerrupt handler, which is single
thपढ़ोed by the hardware and other software.

The send packet thपढ़ो has partial control over the Tx ring and 'dev->tbusy'
flag.  It sets the tbusy flag whenever it's queuing a Tx packet. If the next
queue slot is empty, it clears the tbusy flag when finished otherwise it sets
the 'lp->tx_full' flag.

The पूर्णांकerrupt handler has exclusive control over the Rx ring and records stats
from the Tx ring. (The Tx-करोne पूर्णांकerrupt can't be selectively turned off, so
we can't aव्योम the पूर्णांकerrupt overhead by having the Tx routine reap the Tx
stats.)	 After reaping the stats, it marks the queue entry as empty by setting
the 'base' to zero. Iff the 'lp->tx_full' flag is set, it clears both the
tx_full and tbusy flags.

*/

/* Set the number of Tx and Rx buffers, using Log_2(# buffers).
   Reasonable शेष values are 16 Tx buffers, and 16 Rx buffers.
   That translates to 4 and 4 (16 == 2^^4).
   This is a compile-समय option क्रम efficiency.
   */
#अगर_अघोषित LANCE_LOG_TX_BUFFERS
#घोषणा LANCE_LOG_TX_BUFFERS 4
#घोषणा LANCE_LOG_RX_BUFFERS 4
#पूर्ण_अगर

#घोषणा TX_RING_SIZE			(1 << (LANCE_LOG_TX_BUFFERS))
#घोषणा TX_RING_MOD_MASK		(TX_RING_SIZE - 1)
#घोषणा TX_RING_LEN_BITS		((LANCE_LOG_TX_BUFFERS) << 29)

#घोषणा RX_RING_SIZE			(1 << (LANCE_LOG_RX_BUFFERS))
#घोषणा RX_RING_MOD_MASK		(RX_RING_SIZE - 1)
#घोषणा RX_RING_LEN_BITS		((LANCE_LOG_RX_BUFFERS) << 29)

#घोषणा PKT_BUF_SZ		1544

/* Offsets from base I/O address. */
#घोषणा LANCE_DATA 0x10
#घोषणा LANCE_ADDR 0x12
#घोषणा LANCE_RESET 0x14
#घोषणा LANCE_BUS_IF 0x16
#घोषणा LANCE_TOTAL_SIZE 0x18

#घोषणा TX_TIMEOUT	(HZ/5)

/* The LANCE Rx and Tx ring descriptors. */
काष्ठा lance_rx_head अणु
	s32 base;
	s16 buf_length;			/* This length is 2s complement (negative)! */
	s16 msg_length;			/* This length is "normal". */
पूर्ण;

काष्ठा lance_tx_head अणु
	s32 base;
	s16 length;				/* Length is 2s complement (negative)! */
	s16 misc;
पूर्ण;

/* The LANCE initialization block, described in databook. */
काष्ठा lance_init_block अणु
	u16 mode;		/* Pre-set mode (reg. 15) */
	u8  phys_addr[6]; /* Physical ethernet address */
	u32 filter[2];			/* Multicast filter (unused). */
	/* Receive and transmit ring base, aदीर्घ with extra bits. */
	u32  rx_ring;			/* Tx and Rx ring base poपूर्णांकers */
	u32  tx_ring;
पूर्ण;

काष्ठा lance_निजी अणु
	/* The Tx and Rx ring entries must be aligned on 8-byte boundaries. */
	काष्ठा lance_rx_head rx_ring[RX_RING_SIZE];
	काष्ठा lance_tx_head tx_ring[TX_RING_SIZE];
	काष्ठा lance_init_block	init_block;
	स्थिर अक्षर *name;
	/* The saved address of a sent-in-place packet/buffer, क्रम skमुक्त(). */
	काष्ठा sk_buff* tx_skbuff[TX_RING_SIZE];
	/* The addresses of receive-in-place skbuffs. */
	काष्ठा sk_buff* rx_skbuff[RX_RING_SIZE];
	अचिन्हित दीर्घ rx_buffs;		/* Address of Rx and Tx buffers. */
	/* Tx low-memory "bounce buffer" address. */
	अक्षर (*tx_bounce_buffs)[PKT_BUF_SZ];
	पूर्णांक cur_rx, cur_tx;			/* The next मुक्त ring entry */
	पूर्णांक dirty_rx, dirty_tx;		/* The ring entries to be मुक्त()ed. */
	पूर्णांक dma;
	अचिन्हित अक्षर chip_version;	/* See lance_chip_type. */
	spinlock_t devlock;
पूर्ण;

#घोषणा LANCE_MUST_PAD          0x00000001
#घोषणा LANCE_ENABLE_AUTOSELECT 0x00000002
#घोषणा LANCE_MUST_REINIT_RING  0x00000004
#घोषणा LANCE_MUST_UNRESET      0x00000008
#घोषणा LANCE_HAS_MISSED_FRAME  0x00000010

/* A mapping from the chip ID number to the part number and features.
   These are from the datasheets -- in real lअगरe the '970 version
   reportedly has the same ID as the '965. */
अटल काष्ठा lance_chip_type अणु
	पूर्णांक id_number;
	स्थिर अक्षर *name;
	पूर्णांक flags;
पूर्ण chip_table[] = अणु
	अणु0x0000, "LANCE 7990",				/* Ancient lance chip.  */
		LANCE_MUST_PAD + LANCE_MUST_UNRESETपूर्ण,
	अणु0x0003, "PCnet/ISA 79C960",		/* 79C960 PCnet/ISA.  */
		LANCE_ENABLE_AUTOSELECT + LANCE_MUST_REINIT_RING +
			LANCE_HAS_MISSED_FRAMEपूर्ण,
	अणु0x2260, "PCnet/ISA+ 79C961",		/* 79C961 PCnet/ISA+, Plug-n-Play.  */
		LANCE_ENABLE_AUTOSELECT + LANCE_MUST_REINIT_RING +
			LANCE_HAS_MISSED_FRAMEपूर्ण,
	अणु0x2420, "PCnet/PCI 79C970",		/* 79C970 or 79C974 PCnet-SCSI, PCI. */
		LANCE_ENABLE_AUTOSELECT + LANCE_MUST_REINIT_RING +
			LANCE_HAS_MISSED_FRAMEपूर्ण,
	/* Bug: the PCnet/PCI actually uses the PCnet/VLB ID number, so just call
		it the PCnet32. */
	अणु0x2430, "PCnet32",					/* 79C965 PCnet क्रम VL bus. */
		LANCE_ENABLE_AUTOSELECT + LANCE_MUST_REINIT_RING +
			LANCE_HAS_MISSED_FRAMEपूर्ण,
        अणु0x2621, "PCnet/PCI-II 79C970A",        /* 79C970A PCInetPCI II. */
                LANCE_ENABLE_AUTOSELECT + LANCE_MUST_REINIT_RING +
                        LANCE_HAS_MISSED_FRAMEपूर्ण,
	अणु0x0, 	 "PCnet (unknown)",
		LANCE_ENABLE_AUTOSELECT + LANCE_MUST_REINIT_RING +
			LANCE_HAS_MISSED_FRAMEपूर्ण,
पूर्ण;

क्रमागत अणुOLD_LANCE = 0, PCNET_ISA=1, PCNET_ISAP=2, PCNET_PCI=3, PCNET_VLB=4, PCNET_PCI_II=5, LANCE_UNKNOWN=6पूर्ण;


/* Non-zero अगर lance_probe1() needs to allocate low-memory bounce buffers.
   Assume yes until we know the memory size. */
अटल अचिन्हित अक्षर lance_need_isa_bounce_buffers = 1;

अटल पूर्णांक lance_खोलो(काष्ठा net_device *dev);
अटल व्योम lance_init_ring(काष्ठा net_device *dev, gfp_t mode);
अटल netdev_tx_t lance_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev);
अटल पूर्णांक lance_rx(काष्ठा net_device *dev);
अटल irqवापस_t lance_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक lance_बंद(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *lance_get_stats(काष्ठा net_device *dev);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);
अटल व्योम lance_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);



#अगर_घोषित MODULE
#घोषणा MAX_CARDS		8	/* Max number of पूर्णांकerfaces (cards) per module */

अटल काष्ठा net_device *dev_lance[MAX_CARDS];
अटल पूर्णांक io[MAX_CARDS];
अटल पूर्णांक dma[MAX_CARDS];
अटल पूर्णांक irq[MAX_CARDS];

module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
module_param_hw_array(dma, पूर्णांक, dma, शून्य, 0);
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
module_param(lance_debug, पूर्णांक, 0);
MODULE_PARM_DESC(io, "LANCE/PCnet I/O base address(es),required");
MODULE_PARM_DESC(dma, "LANCE/PCnet ISA DMA channel (ignored for some devices)");
MODULE_PARM_DESC(irq, "LANCE/PCnet IRQ number (ignored for some devices)");
MODULE_PARM_DESC(lance_debug, "LANCE/PCnet debug level (0-7)");

पूर्णांक __init init_module(व्योम)
अणु
	काष्ठा net_device *dev;
	पूर्णांक this_dev, found = 0;

	क्रम (this_dev = 0; this_dev < MAX_CARDS; this_dev++) अणु
		अगर (io[this_dev] == 0)  अणु
			अगर (this_dev != 0) /* only complain once */
				अवरोध;
			prपूर्णांकk(KERN_NOTICE "lance.c: Module autoprobing not allowed. Append \"io=0xNNN\" value(s).\n");
			वापस -EPERM;
		पूर्ण
		dev = alloc_etherdev(0);
		अगर (!dev)
			अवरोध;
		dev->irq = irq[this_dev];
		dev->base_addr = io[this_dev];
		dev->dma = dma[this_dev];
		अगर (करो_lance_probe(dev) == 0) अणु
			dev_lance[found++] = dev;
			जारी;
		पूर्ण
		मुक्त_netdev(dev);
		अवरोध;
	पूर्ण
	अगर (found != 0)
		वापस 0;
	वापस -ENXIO;
पूर्ण

अटल व्योम cleanup_card(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = dev->ml_priv;
	अगर (dev->dma != 4)
		मुक्त_dma(dev->dma);
	release_region(dev->base_addr, LANCE_TOTAL_SIZE);
	kमुक्त(lp->tx_bounce_buffs);
	kमुक्त((व्योम*)lp->rx_buffs);
	kमुक्त(lp);
पूर्ण

व्योम __निकास cleanup_module(व्योम)
अणु
	पूर्णांक this_dev;

	क्रम (this_dev = 0; this_dev < MAX_CARDS; this_dev++) अणु
		काष्ठा net_device *dev = dev_lance[this_dev];
		अगर (dev) अणु
			unरेजिस्टर_netdev(dev);
			cleanup_card(dev);
			मुक्त_netdev(dev);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* MODULE */
MODULE_LICENSE("GPL");


/* Starting in v2.1.*, the LANCE/PCnet probe is now similar to the other
   board probes now that kदो_स्मृति() can allocate ISA DMA-able regions.
   This also allows the LANCE driver to be used as a module.
   */
अटल पूर्णांक __init करो_lance_probe(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक *port;
	पूर्णांक result;

	अगर (high_memory <= phys_to_virt(16*1024*1024))
		lance_need_isa_bounce_buffers = 0;

	क्रम (port = lance_portlist; *port; port++) अणु
		पूर्णांक ioaddr = *port;
		काष्ठा resource *r = request_region(ioaddr, LANCE_TOTAL_SIZE,
							"lance-probe");

		अगर (r) अणु
			/* Detect the card with minimal I/O पढ़ोs */
			अक्षर offset14 = inb(ioaddr + 14);
			पूर्णांक card;
			क्रम (card = 0; card < NUM_CARDS; ++card)
				अगर (cards[card].id_offset14 == offset14)
					अवरोध;
			अगर (card < NUM_CARDS) अणु/*yes, the first byte matches*/
				अक्षर offset15 = inb(ioaddr + 15);
				क्रम (card = 0; card < NUM_CARDS; ++card)
					अगर ((cards[card].id_offset14 == offset14) &&
						(cards[card].id_offset15 == offset15))
						अवरोध;
			पूर्ण
			अगर (card < NUM_CARDS) अणु /*Signature OK*/
				result = lance_probe1(dev, ioaddr, 0, 0);
				अगर (!result) अणु
					काष्ठा lance_निजी *lp = dev->ml_priv;
					पूर्णांक ver = lp->chip_version;

					r->name = chip_table[ver].name;
					वापस 0;
				पूर्ण
			पूर्ण
			release_region(ioaddr, LANCE_TOTAL_SIZE);
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण

#अगर_अघोषित MODULE
काष्ठा net_device * __init lance_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev = alloc_etherdev(0);
	पूर्णांक err;

	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	प्र_लिखो(dev->name, "eth%d", unit);
	netdev_boot_setup_check(dev);

	err = करो_lance_probe(dev);
	अगर (err)
		जाओ out;
	वापस dev;
out:
	मुक्त_netdev(dev);
	वापस ERR_PTR(err);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops lance_netdev_ops = अणु
	.nकरो_खोलो 		= lance_खोलो,
	.nकरो_start_xmit		= lance_start_xmit,
	.nकरो_stop		= lance_बंद,
	.nकरो_get_stats		= lance_get_stats,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_tx_समयout		= lance_tx_समयout,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक __init lance_probe1(काष्ठा net_device *dev, पूर्णांक ioaddr, पूर्णांक irq, पूर्णांक options)
अणु
	काष्ठा lance_निजी *lp;
	अचिन्हित दीर्घ dma_channels;	/* Mark spuriously-busy DMA channels */
	पूर्णांक i, reset_val, lance_version;
	स्थिर अक्षर *chipname;
	/* Flags क्रम specअगरic chips or boards. */
	अचिन्हित अक्षर hpJ2405A = 0;	/* HP ISA adaptor */
	पूर्णांक hp_builtin = 0;		/* HP on-board ethernet. */
	अटल पूर्णांक did_version;		/* Alपढ़ोy prपूर्णांकed version info. */
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -ENOMEM;
	व्योम __iomem *bios;

	/* First we look क्रम special हालs.
	   Check क्रम HP's on-board ethernet by looking for 'HP' in the BIOS.
	   There are two HP versions, check the BIOS क्रम the configuration port.
	   This method provided by L. Julliard, Laurent_Julliard@grenoble.hp.com.
	   */
	bios = ioremap(0xf00f0, 0x14);
	अगर (!bios)
		वापस -ENOMEM;
	अगर (पढ़ोw(bios + 0x12) == 0x5048)  अणु
		अटल स्थिर लघु ioaddr_table[] = अणु 0x300, 0x320, 0x340, 0x360पूर्ण;
		पूर्णांक hp_port = (पढ़ोl(bios + 1) & 1)  ? 0x499 : 0x99;
		/* We can have boards other than the built-in!  Verअगरy this is on-board. */
		अगर ((inb(hp_port) & 0xc0) == 0x80 &&
		    ioaddr_table[inb(hp_port) & 3] == ioaddr)
			hp_builtin = hp_port;
	पूर्ण
	iounmap(bios);
	/* We also recognize the HP Vectra on-board here, but check below. */
	hpJ2405A = (inb(ioaddr) == 0x08 && inb(ioaddr+1) == 0x00 &&
		    inb(ioaddr+2) == 0x09);

	/* Reset the LANCE.	 */
	reset_val = inw(ioaddr+LANCE_RESET); /* Reset the LANCE */

	/* The Un-Reset needed is only needed क्रम the real NE2100, and will
	   confuse the HP board. */
	अगर (!hpJ2405A)
		outw(reset_val, ioaddr+LANCE_RESET);

	outw(0x0000, ioaddr+LANCE_ADDR); /* Switch to winकरोw 0 */
	अगर (inw(ioaddr+LANCE_DATA) != 0x0004)
		वापस -ENODEV;

	/* Get the version of the chip. */
	outw(88, ioaddr+LANCE_ADDR);
	अगर (inw(ioaddr+LANCE_ADDR) != 88) अणु
		lance_version = 0;
	पूर्ण अन्यथा अणु			/* Good, it's a newer chip. */
		पूर्णांक chip_version = inw(ioaddr+LANCE_DATA);
		outw(89, ioaddr+LANCE_ADDR);
		chip_version |= inw(ioaddr+LANCE_DATA) << 16;
		अगर (lance_debug > 2)
			prपूर्णांकk("  LANCE chip version is %#x.\n", chip_version);
		अगर ((chip_version & 0xfff) != 0x003)
			वापस -ENODEV;
		chip_version = (chip_version >> 12) & 0xffff;
		क्रम (lance_version = 1; chip_table[lance_version].id_number; lance_version++) अणु
			अगर (chip_table[lance_version].id_number == chip_version)
				अवरोध;
		पूर्ण
	पूर्ण

	/* We can't allocate निजी data from alloc_etherdev() because it must
	   a ISA DMA-able region. */
	chipname = chip_table[lance_version].name;
	prपूर्णांकk("%s: %s at %#3x, ", dev->name, chipname, ioaddr);

	/* There is a 16 byte station address PROM at the base address.
	   The first six bytes are the station address. */
	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = inb(ioaddr + i);
	prपूर्णांकk("%pM", dev->dev_addr);

	dev->base_addr = ioaddr;
	/* Make certain the data काष्ठाures used by the LANCE are aligned and DMAble. */

	lp = kzalloc(माप(*lp), GFP_DMA | GFP_KERNEL);
	अगर (!lp)
		वापस -ENOMEM;
	अगर (lance_debug > 6) prपूर्णांकk(" (#0x%05lx)", (अचिन्हित दीर्घ)lp);
	dev->ml_priv = lp;
	lp->name = chipname;
	lp->rx_buffs = (अचिन्हित दीर्घ)kदो_स्मृति_array(RX_RING_SIZE, PKT_BUF_SZ,
						    GFP_DMA | GFP_KERNEL);
	अगर (!lp->rx_buffs)
		जाओ out_lp;
	अगर (lance_need_isa_bounce_buffers) अणु
		lp->tx_bounce_buffs = kदो_स्मृति_array(TX_RING_SIZE, PKT_BUF_SZ,
						    GFP_DMA | GFP_KERNEL);
		अगर (!lp->tx_bounce_buffs)
			जाओ out_rx;
	पूर्ण अन्यथा
		lp->tx_bounce_buffs = शून्य;

	lp->chip_version = lance_version;
	spin_lock_init(&lp->devlock);

	lp->init_block.mode = 0x0003;		/* Disable Rx and Tx. */
	क्रम (i = 0; i < 6; i++)
		lp->init_block.phys_addr[i] = dev->dev_addr[i];
	lp->init_block.filter[0] = 0x00000000;
	lp->init_block.filter[1] = 0x00000000;
	lp->init_block.rx_ring = ((u32)isa_virt_to_bus(lp->rx_ring) & 0xffffff) | RX_RING_LEN_BITS;
	lp->init_block.tx_ring = ((u32)isa_virt_to_bus(lp->tx_ring) & 0xffffff) | TX_RING_LEN_BITS;

	outw(0x0001, ioaddr+LANCE_ADDR);
	inw(ioaddr+LANCE_ADDR);
	outw((लघु) (u32) isa_virt_to_bus(&lp->init_block), ioaddr+LANCE_DATA);
	outw(0x0002, ioaddr+LANCE_ADDR);
	inw(ioaddr+LANCE_ADDR);
	outw(((u32)isa_virt_to_bus(&lp->init_block)) >> 16, ioaddr+LANCE_DATA);
	outw(0x0000, ioaddr+LANCE_ADDR);
	inw(ioaddr+LANCE_ADDR);

	अगर (irq) अणु					/* Set अगरf PCI card. */
		dev->dma = 4;			/* Native bus-master, no DMA channel needed. */
		dev->irq = irq;
	पूर्ण अन्यथा अगर (hp_builtin) अणु
		अटल स्थिर अक्षर dma_tbl[4] = अणु3, 5, 6, 0पूर्ण;
		अटल स्थिर अक्षर irq_tbl[4] = अणु3, 4, 5, 9पूर्ण;
		अचिन्हित अक्षर port_val = inb(hp_builtin);
		dev->dma = dma_tbl[(port_val >> 4) & 3];
		dev->irq = irq_tbl[(port_val >> 2) & 3];
		prपूर्णांकk(" HP Vectra IRQ %d DMA %d.\n", dev->irq, dev->dma);
	पूर्ण अन्यथा अगर (hpJ2405A) अणु
		अटल स्थिर अक्षर dma_tbl[4] = अणु3, 5, 6, 7पूर्ण;
		अटल स्थिर अक्षर irq_tbl[8] = अणु3, 4, 5, 9, 10, 11, 12, 15पूर्ण;
		लघु reset_val = inw(ioaddr+LANCE_RESET);
		dev->dma = dma_tbl[(reset_val >> 2) & 3];
		dev->irq = irq_tbl[(reset_val >> 4) & 7];
		prपूर्णांकk(" HP J2405A IRQ %d DMA %d.\n", dev->irq, dev->dma);
	पूर्ण अन्यथा अगर (lance_version == PCNET_ISAP) अणु		/* The plug-n-play version. */
		लघु bus_info;
		outw(8, ioaddr+LANCE_ADDR);
		bus_info = inw(ioaddr+LANCE_BUS_IF);
		dev->dma = bus_info & 0x07;
		dev->irq = (bus_info >> 4) & 0x0F;
	पूर्ण अन्यथा अणु
		/* The DMA channel may be passed in PARAM1. */
		अगर (dev->mem_start & 0x07)
			dev->dma = dev->mem_start & 0x07;
	पूर्ण

	अगर (dev->dma == 0) अणु
		/* Read the DMA channel status रेजिस्टर, so that we can aव्योम
		   stuck DMA channels in the DMA detection below. */
		dma_channels = ((inb(DMA1_STAT_REG) >> 4) & 0x0f) |
			(inb(DMA2_STAT_REG) & 0xf0);
	पूर्ण
	err = -ENODEV;
	अगर (dev->irq >= 2)
		prपूर्णांकk(" assigned IRQ %d", dev->irq);
	अन्यथा अगर (lance_version != 0)  अणु	/* 7990 boards need DMA detection first. */
		अचिन्हित दीर्घ irq_mask;

		/* To स्वतः-IRQ we enable the initialization-करोne and DMA error
		   पूर्णांकerrupts. For ISA boards we get a DMA error, but VLB and PCI
		   boards will work. */
		irq_mask = probe_irq_on();

		/* Trigger an initialization just क्रम the पूर्णांकerrupt. */
		outw(0x0041, ioaddr+LANCE_DATA);

		mdelay(20);
		dev->irq = probe_irq_off(irq_mask);
		अगर (dev->irq)
			prपूर्णांकk(", probed IRQ %d", dev->irq);
		अन्यथा अणु
			prपूर्णांकk(", failed to detect IRQ line.\n");
			जाओ out_tx;
		पूर्ण

		/* Check क्रम the initialization करोne bit, 0x0100, which means
		   that we करोn't need a DMA channel. */
		अगर (inw(ioaddr+LANCE_DATA) & 0x0100)
			dev->dma = 4;
	पूर्ण

	अगर (dev->dma == 4) अणु
		prपूर्णांकk(", no DMA needed.\n");
	पूर्ण अन्यथा अगर (dev->dma) अणु
		अगर (request_dma(dev->dma, chipname)) अणु
			prपूर्णांकk("DMA %d allocation failed.\n", dev->dma);
			जाओ out_tx;
		पूर्ण अन्यथा
			prपूर्णांकk(", assigned DMA %d.\n", dev->dma);
	पूर्ण अन्यथा अणु			/* OK, we have to स्वतः-DMA. */
		क्रम (i = 0; i < 4; i++) अणु
			अटल स्थिर अक्षर dmas[] = अणु 5, 6, 7, 3 पूर्ण;
			पूर्णांक dma = dmas[i];
			पूर्णांक boguscnt;

			/* Don't enable a permanently busy DMA channel, or the machine
			   will hang. */
			अगर (test_bit(dma, &dma_channels))
				जारी;
			outw(0x7f04, ioaddr+LANCE_DATA); /* Clear the memory error bits. */
			अगर (request_dma(dma, chipname))
				जारी;

			flags=claim_dma_lock();
			set_dma_mode(dma, DMA_MODE_CASCADE);
			enable_dma(dma);
			release_dma_lock(flags);

			/* Trigger an initialization. */
			outw(0x0001, ioaddr+LANCE_DATA);
			क्रम (boguscnt = 100; boguscnt > 0; --boguscnt)
				अगर (inw(ioaddr+LANCE_DATA) & 0x0900)
					अवरोध;
			अगर (inw(ioaddr+LANCE_DATA) & 0x0100) अणु
				dev->dma = dma;
				prपूर्णांकk(", DMA %d.\n", dev->dma);
				अवरोध;
			पूर्ण अन्यथा अणु
				flags=claim_dma_lock();
				disable_dma(dma);
				release_dma_lock(flags);
				मुक्त_dma(dma);
			पूर्ण
		पूर्ण
		अगर (i == 4) अणु			/* Failure: bail. */
			prपूर्णांकk("DMA detection failed.\n");
			जाओ out_tx;
		पूर्ण
	पूर्ण

	अगर (lance_version == 0 && dev->irq == 0) अणु
		/* We may स्वतः-IRQ now that we have a DMA channel. */
		/* Trigger an initialization just क्रम the पूर्णांकerrupt. */
		अचिन्हित दीर्घ irq_mask;

		irq_mask = probe_irq_on();
		outw(0x0041, ioaddr+LANCE_DATA);

		mdelay(40);
		dev->irq = probe_irq_off(irq_mask);
		अगर (dev->irq == 0) अणु
			prपूर्णांकk("  Failed to detect the 7990 IRQ line.\n");
			जाओ out_dma;
		पूर्ण
		prपूर्णांकk("  Auto-IRQ detected IRQ%d.\n", dev->irq);
	पूर्ण

	अगर (chip_table[lp->chip_version].flags & LANCE_ENABLE_AUTOSELECT) अणु
		/* Turn on स्वतः-select of media (10baseT or BNC) so that the user
		   can watch the LEDs even अगर the board isn't खोलोed. */
		outw(0x0002, ioaddr+LANCE_ADDR);
		/* Don't touch 10base2 घातer bit. */
		outw(inw(ioaddr+LANCE_BUS_IF) | 0x0002, ioaddr+LANCE_BUS_IF);
	पूर्ण

	अगर (lance_debug > 0  &&  did_version++ == 0)
		prपूर्णांकk(version);

	/* The LANCE-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &lance_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out_dma;
	वापस 0;
out_dma:
	अगर (dev->dma != 4)
		मुक्त_dma(dev->dma);
out_tx:
	kमुक्त(lp->tx_bounce_buffs);
out_rx:
	kमुक्त((व्योम*)lp->rx_buffs);
out_lp:
	kमुक्त(lp);
	वापस err;
पूर्ण


अटल पूर्णांक
lance_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = dev->ml_priv;
	पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक i;

	अगर (dev->irq == 0 ||
		request_irq(dev->irq, lance_पूर्णांकerrupt, 0, dev->name, dev)) अणु
		वापस -EAGAIN;
	पूर्ण

	/* We used to allocate DMA here, but that was silly.
	   DMA lines can't be shared!  We now permanently allocate them. */

	/* Reset the LANCE */
	inw(ioaddr+LANCE_RESET);

	/* The DMA controller is used as a no-operation slave, "cascade mode". */
	अगर (dev->dma != 4) अणु
		अचिन्हित दीर्घ flags=claim_dma_lock();
		enable_dma(dev->dma);
		set_dma_mode(dev->dma, DMA_MODE_CASCADE);
		release_dma_lock(flags);
	पूर्ण

	/* Un-Reset the LANCE, needed only क्रम the NE2100. */
	अगर (chip_table[lp->chip_version].flags & LANCE_MUST_UNRESET)
		outw(0, ioaddr+LANCE_RESET);

	अगर (chip_table[lp->chip_version].flags & LANCE_ENABLE_AUTOSELECT) अणु
		/* This is 79C960-specअगरic: Turn on स्वतः-select of media (AUI, BNC). */
		outw(0x0002, ioaddr+LANCE_ADDR);
		/* Only touch स्वतःselect bit. */
		outw(inw(ioaddr+LANCE_BUS_IF) | 0x0002, ioaddr+LANCE_BUS_IF);
 	पूर्ण

	अगर (lance_debug > 1)
		prपूर्णांकk("%s: lance_open() irq %d dma %d tx/rx rings %#x/%#x init %#x.\n",
			   dev->name, dev->irq, dev->dma,
		           (u32) isa_virt_to_bus(lp->tx_ring),
		           (u32) isa_virt_to_bus(lp->rx_ring),
			   (u32) isa_virt_to_bus(&lp->init_block));

	lance_init_ring(dev, GFP_KERNEL);
	/* Re-initialize the LANCE, and start it when करोne. */
	outw(0x0001, ioaddr+LANCE_ADDR);
	outw((लघु) (u32) isa_virt_to_bus(&lp->init_block), ioaddr+LANCE_DATA);
	outw(0x0002, ioaddr+LANCE_ADDR);
	outw(((u32)isa_virt_to_bus(&lp->init_block)) >> 16, ioaddr+LANCE_DATA);

	outw(0x0004, ioaddr+LANCE_ADDR);
	outw(0x0915, ioaddr+LANCE_DATA);

	outw(0x0000, ioaddr+LANCE_ADDR);
	outw(0x0001, ioaddr+LANCE_DATA);

	netअगर_start_queue (dev);

	i = 0;
	जबतक (i++ < 100)
		अगर (inw(ioaddr+LANCE_DATA) & 0x0100)
			अवरोध;
	/*
	 * We used to clear the InitDone bit, 0x0100, here but Mark Stockton
	 * reports that करोing so triggers a bug in the '974.
	 */
 	outw(0x0042, ioaddr+LANCE_DATA);

	अगर (lance_debug > 2)
		prपूर्णांकk("%s: LANCE open after %d ticks, init block %#x csr0 %4.4x.\n",
			   dev->name, i, (u32) isa_virt_to_bus(&lp->init_block), inw(ioaddr+LANCE_DATA));

	वापस 0;					/* Always succeed */
पूर्ण

/* The LANCE has been halted क्रम one reason or another (busmaster memory
   arbitration error, Tx FIFO underflow, driver stopped it to reconfigure,
   etc.).  Modern LANCE variants always reload their ring-buffer
   configuration when restarted, so we must reinitialize our ring
   context beक्रमe restarting.  As part of this reinitialization,
   find all packets still on the Tx ring and pretend that they had been
   sent (in effect, drop the packets on the न्यूनमान) - the higher-level
   protocols will समय out and retransmit.  It'd be better to shuffle
   these skbs to a temp list and then actually re-Tx them after
   restarting the chip, but I'm too lazy to करो so right now.  dplatt@3करो.com
*/

अटल व्योम
lance_purge_ring(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = dev->ml_priv;
	पूर्णांक i;

	/* Free all the skbuffs in the Rx and Tx queues. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = lp->rx_skbuff[i];
		lp->rx_skbuff[i] = शून्य;
		lp->rx_ring[i].base = 0;		/* Not owned by LANCE chip. */
		अगर (skb)
			dev_kमुक्त_skb_any(skb);
	पूर्ण
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		अगर (lp->tx_skbuff[i]) अणु
			dev_kमुक्त_skb_any(lp->tx_skbuff[i]);
			lp->tx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण


/* Initialize the LANCE Rx and Tx rings. */
अटल व्योम
lance_init_ring(काष्ठा net_device *dev, gfp_t gfp)
अणु
	काष्ठा lance_निजी *lp = dev->ml_priv;
	पूर्णांक i;

	lp->cur_rx = lp->cur_tx = 0;
	lp->dirty_rx = lp->dirty_tx = 0;

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb;
		व्योम *rx_buff;

		skb = alloc_skb(PKT_BUF_SZ, GFP_DMA | gfp);
		lp->rx_skbuff[i] = skb;
		अगर (skb)
			rx_buff = skb->data;
		अन्यथा
			rx_buff = kदो_स्मृति(PKT_BUF_SZ, GFP_DMA | gfp);
		अगर (rx_buff == शून्य)
			lp->rx_ring[i].base = 0;
		अन्यथा
			lp->rx_ring[i].base = (u32)isa_virt_to_bus(rx_buff) | 0x80000000;
		lp->rx_ring[i].buf_length = -PKT_BUF_SZ;
	पूर्ण
	/* The Tx buffer address is filled in as needed, but we करो need to clear
	   the upper ownership bit. */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		lp->tx_skbuff[i] = शून्य;
		lp->tx_ring[i].base = 0;
	पूर्ण

	lp->init_block.mode = 0x0000;
	क्रम (i = 0; i < 6; i++)
		lp->init_block.phys_addr[i] = dev->dev_addr[i];
	lp->init_block.filter[0] = 0x00000000;
	lp->init_block.filter[1] = 0x00000000;
	lp->init_block.rx_ring = ((u32)isa_virt_to_bus(lp->rx_ring) & 0xffffff) | RX_RING_LEN_BITS;
	lp->init_block.tx_ring = ((u32)isa_virt_to_bus(lp->tx_ring) & 0xffffff) | TX_RING_LEN_BITS;
पूर्ण

अटल व्योम
lance_restart(काष्ठा net_device *dev, अचिन्हित पूर्णांक csr0_bits, पूर्णांक must_reinit)
अणु
	काष्ठा lance_निजी *lp = dev->ml_priv;

	अगर (must_reinit ||
		(chip_table[lp->chip_version].flags & LANCE_MUST_REINIT_RING)) अणु
		lance_purge_ring(dev);
		lance_init_ring(dev, GFP_ATOMIC);
	पूर्ण
	outw(0x0000,    dev->base_addr + LANCE_ADDR);
	outw(csr0_bits, dev->base_addr + LANCE_DATA);
पूर्ण


अटल व्योम lance_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा lance_निजी *lp = (काष्ठा lance_निजी *) dev->ml_priv;
	पूर्णांक ioaddr = dev->base_addr;

	outw (0, ioaddr + LANCE_ADDR);
	prपूर्णांकk ("%s: transmit timed out, status %4.4x, resetting.\n",
		dev->name, inw (ioaddr + LANCE_DATA));
	outw (0x0004, ioaddr + LANCE_DATA);
	dev->stats.tx_errors++;
#अगर_अघोषित final_version
	अगर (lance_debug > 3) अणु
		पूर्णांक i;
		prपूर्णांकk (" Ring data dump: dirty_tx %d cur_tx %d%s cur_rx %d.",
		  lp->dirty_tx, lp->cur_tx, netअगर_queue_stopped(dev) ? " (full)" : "",
			lp->cur_rx);
		क्रम (i = 0; i < RX_RING_SIZE; i++)
			prपूर्णांकk ("%s %08x %04x %04x", i & 0x3 ? "" : "\n ",
			 lp->rx_ring[i].base, -lp->rx_ring[i].buf_length,
				lp->rx_ring[i].msg_length);
		क्रम (i = 0; i < TX_RING_SIZE; i++)
			prपूर्णांकk ("%s %08x %04x %04x", i & 0x3 ? "" : "\n ",
			     lp->tx_ring[i].base, -lp->tx_ring[i].length,
				lp->tx_ring[i].misc);
		prपूर्णांकk ("\n");
	पूर्ण
#पूर्ण_अगर
	lance_restart (dev, 0x0043, 1);

	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue (dev);
पूर्ण


अटल netdev_tx_t lance_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = dev->ml_priv;
	पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lp->devlock, flags);

	अगर (lance_debug > 3) अणु
		outw(0x0000, ioaddr+LANCE_ADDR);
		prपूर्णांकk("%s: lance_start_xmit() called, csr0 %4.4x.\n", dev->name,
			   inw(ioaddr+LANCE_DATA));
		outw(0x0000, ioaddr+LANCE_DATA);
	पूर्ण

	/* Fill in a Tx ring entry */

	/* Mask to ring buffer boundary. */
	entry = lp->cur_tx & TX_RING_MOD_MASK;

	/* Caution: the ग_लिखो order is important here, set the base address
	   with the "ownership" bits last. */

	/* The old LANCE chips करोesn't स्वतःmatically pad buffers to min. size. */
	अगर (chip_table[lp->chip_version].flags & LANCE_MUST_PAD) अणु
		अगर (skb->len < ETH_ZLEN) अणु
			अगर (skb_padto(skb, ETH_ZLEN))
				जाओ out;
			lp->tx_ring[entry].length = -ETH_ZLEN;
		पूर्ण
		अन्यथा
			lp->tx_ring[entry].length = -skb->len;
	पूर्ण अन्यथा
		lp->tx_ring[entry].length = -skb->len;

	lp->tx_ring[entry].misc = 0x0000;

	dev->stats.tx_bytes += skb->len;

	/* If any part of this buffer is >16M we must copy it to a low-memory
	   buffer. */
	अगर ((u32)isa_virt_to_bus(skb->data) + skb->len > 0x01000000) अणु
		अगर (lance_debug > 5)
			prपूर्णांकk("%s: bouncing a high-memory packet (%#x).\n",
				   dev->name, (u32)isa_virt_to_bus(skb->data));
		skb_copy_from_linear_data(skb, &lp->tx_bounce_buffs[entry], skb->len);
		lp->tx_ring[entry].base =
			((u32)isa_virt_to_bus((lp->tx_bounce_buffs + entry)) & 0xffffff) | 0x83000000;
		dev_kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		lp->tx_skbuff[entry] = skb;
		lp->tx_ring[entry].base = ((u32)isa_virt_to_bus(skb->data) & 0xffffff) | 0x83000000;
	पूर्ण
	lp->cur_tx++;

	/* Trigger an immediate send poll. */
	outw(0x0000, ioaddr+LANCE_ADDR);
	outw(0x0048, ioaddr+LANCE_DATA);

	अगर ((lp->cur_tx - lp->dirty_tx) >= TX_RING_SIZE)
		netअगर_stop_queue(dev);

out:
	spin_unlock_irqrestore(&lp->devlock, flags);
	वापस NETDEV_TX_OK;
पूर्ण

/* The LANCE पूर्णांकerrupt handler. */
अटल irqवापस_t lance_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा lance_निजी *lp;
	पूर्णांक csr0, ioaddr, boguscnt=10;
	पूर्णांक must_restart;

	ioaddr = dev->base_addr;
	lp = dev->ml_priv;

	spin_lock (&lp->devlock);

	outw(0x00, dev->base_addr + LANCE_ADDR);
	जबतक ((csr0 = inw(dev->base_addr + LANCE_DATA)) & 0x8600 &&
	       --boguscnt >= 0) अणु
		/* Acknowledge all of the current पूर्णांकerrupt sources ASAP. */
		outw(csr0 & ~0x004f, dev->base_addr + LANCE_DATA);

		must_restart = 0;

		अगर (lance_debug > 5)
			prपूर्णांकk("%s: interrupt  csr0=%#2.2x new csr=%#2.2x.\n",
				   dev->name, csr0, inw(dev->base_addr + LANCE_DATA));

		अगर (csr0 & 0x0400)			/* Rx पूर्णांकerrupt */
			lance_rx(dev);

		अगर (csr0 & 0x0200) अणु		/* Tx-करोne पूर्णांकerrupt */
			पूर्णांक dirty_tx = lp->dirty_tx;

			जबतक (dirty_tx < lp->cur_tx) अणु
				पूर्णांक entry = dirty_tx & TX_RING_MOD_MASK;
				पूर्णांक status = lp->tx_ring[entry].base;

				अगर (status < 0)
					अवरोध;			/* It still hasn't been Txed */

				lp->tx_ring[entry].base = 0;

				अगर (status & 0x40000000) अणु
					/* There was an major error, log it. */
					पूर्णांक err_status = lp->tx_ring[entry].misc;
					dev->stats.tx_errors++;
					अगर (err_status & 0x0400)
						dev->stats.tx_पातed_errors++;
					अगर (err_status & 0x0800)
						dev->stats.tx_carrier_errors++;
					अगर (err_status & 0x1000)
						dev->stats.tx_winकरोw_errors++;
					अगर (err_status & 0x4000) अणु
						/* Ackk!  On FIFO errors the Tx unit is turned off! */
						dev->stats.tx_fअगरo_errors++;
						/* Remove this verbosity later! */
						prपूर्णांकk("%s: Tx FIFO error! Status %4.4x.\n",
							   dev->name, csr0);
						/* Restart the chip. */
						must_restart = 1;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (status & 0x18000000)
						dev->stats.collisions++;
					dev->stats.tx_packets++;
				पूर्ण

				/* We must मुक्त the original skb अगर it's not a data-only copy
				   in the bounce buffer. */
				अगर (lp->tx_skbuff[entry]) अणु
					dev_consume_skb_irq(lp->tx_skbuff[entry]);
					lp->tx_skbuff[entry] = शून्य;
				पूर्ण
				dirty_tx++;
			पूर्ण

#अगर_अघोषित final_version
			अगर (lp->cur_tx - dirty_tx >= TX_RING_SIZE) अणु
				prपूर्णांकk("out-of-sync dirty pointer, %d vs. %d, full=%s.\n",
					   dirty_tx, lp->cur_tx,
					   netअगर_queue_stopped(dev) ? "yes" : "no");
				dirty_tx += TX_RING_SIZE;
			पूर्ण
#पूर्ण_अगर

			/* अगर the ring is no दीर्घer full, accept more packets */
			अगर (netअगर_queue_stopped(dev) &&
			    dirty_tx > lp->cur_tx - TX_RING_SIZE + 2)
				netअगर_wake_queue (dev);

			lp->dirty_tx = dirty_tx;
		पूर्ण

		/* Log misc errors. */
		अगर (csr0 & 0x4000)
			dev->stats.tx_errors++; /* Tx babble. */
		अगर (csr0 & 0x1000)
			dev->stats.rx_errors++; /* Missed a Rx frame. */
		अगर (csr0 & 0x0800) अणु
			prपूर्णांकk("%s: Bus master arbitration failure, status %4.4x.\n",
				   dev->name, csr0);
			/* Restart the chip. */
			must_restart = 1;
		पूर्ण

		अगर (must_restart) अणु
			/* stop the chip to clear the error condition, then restart */
			outw(0x0000, dev->base_addr + LANCE_ADDR);
			outw(0x0004, dev->base_addr + LANCE_DATA);
			lance_restart(dev, 0x0002, 0);
		पूर्ण
	पूर्ण

	/* Clear any other पूर्णांकerrupt, and set पूर्णांकerrupt enable. */
	outw(0x0000, dev->base_addr + LANCE_ADDR);
	outw(0x7940, dev->base_addr + LANCE_DATA);

	अगर (lance_debug > 4)
		prपूर्णांकk("%s: exiting interrupt, csr%d=%#4.4x.\n",
			   dev->name, inw(ioaddr + LANCE_ADDR),
			   inw(dev->base_addr + LANCE_DATA));

	spin_unlock (&lp->devlock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
lance_rx(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = dev->ml_priv;
	पूर्णांक entry = lp->cur_rx & RX_RING_MOD_MASK;
	पूर्णांक i;

	/* If we own the next entry, it's a new packet. Send it up. */
	जबतक (lp->rx_ring[entry].base >= 0) अणु
		पूर्णांक status = lp->rx_ring[entry].base >> 24;

		अगर (status != 0x03) अणु			/* There was an error. */
			/* There is a tricky error noted by John Murphy,
			   <murf@perftech.com> to Russ Nelson: Even with full-sized
			   buffers it's possible क्रम a jabber packet to use two
			   buffers, with only the last correctly noting the error. */
			अगर (status & 0x01)	/* Only count a general error at the */
				dev->stats.rx_errors++; /* end of a packet.*/
			अगर (status & 0x20)
				dev->stats.rx_frame_errors++;
			अगर (status & 0x10)
				dev->stats.rx_over_errors++;
			अगर (status & 0x08)
				dev->stats.rx_crc_errors++;
			अगर (status & 0x04)
				dev->stats.rx_fअगरo_errors++;
			lp->rx_ring[entry].base &= 0x03ffffff;
		पूर्ण
		अन्यथा
		अणु
			/* Malloc up new buffer, compatible with net3. */
			लघु pkt_len = (lp->rx_ring[entry].msg_length & 0xfff)-4;
			काष्ठा sk_buff *skb;

			अगर(pkt_len<60)
			अणु
				prपूर्णांकk("%s: Runt packet!\n",dev->name);
				dev->stats.rx_errors++;
			पूर्ण
			अन्यथा
			अणु
				skb = dev_alloc_skb(pkt_len+2);
				अगर (skb == शून्य)
				अणु
					prपूर्णांकk("%s: Memory squeeze, deferring packet.\n", dev->name);
					क्रम (i=0; i < RX_RING_SIZE; i++)
						अगर (lp->rx_ring[(entry+i) & RX_RING_MOD_MASK].base < 0)
							अवरोध;

					अगर (i > RX_RING_SIZE -2)
					अणु
						dev->stats.rx_dropped++;
						lp->rx_ring[entry].base |= 0x80000000;
						lp->cur_rx++;
					पूर्ण
					अवरोध;
				पूर्ण
				skb_reserve(skb,2);	/* 16 byte align */
				skb_put(skb,pkt_len);	/* Make room */
				skb_copy_to_linear_data(skb,
					(अचिन्हित अक्षर *)isa_bus_to_virt((lp->rx_ring[entry].base & 0x00ffffff)),
					pkt_len);
				skb->protocol=eth_type_trans(skb,dev);
				netअगर_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
			पूर्ण
		पूर्ण
		/* The करोcs say that the buffer length isn't touched, but Andrew Boyd
		   of QNX reports that some revs of the 79C965 clear it. */
		lp->rx_ring[entry].buf_length = -PKT_BUF_SZ;
		lp->rx_ring[entry].base |= 0x80000000;
		entry = (++lp->cur_rx) & RX_RING_MOD_MASK;
	पूर्ण

	/* We should check that at least two ring entries are मुक्त.	 If not,
	   we should मुक्त one and mark stats->rx_dropped++. */

	वापस 0;
पूर्ण

अटल पूर्णांक
lance_बंद(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	काष्ठा lance_निजी *lp = dev->ml_priv;

	netअगर_stop_queue (dev);

	अगर (chip_table[lp->chip_version].flags & LANCE_HAS_MISSED_FRAME) अणु
		outw(112, ioaddr+LANCE_ADDR);
		dev->stats.rx_missed_errors = inw(ioaddr+LANCE_DATA);
	पूर्ण
	outw(0, ioaddr+LANCE_ADDR);

	अगर (lance_debug > 1)
		prपूर्णांकk("%s: Shutting down ethercard, status was %2.2x.\n",
			   dev->name, inw(ioaddr+LANCE_DATA));

	/* We stop the LANCE here -- it occasionally polls
	   memory अगर we करोn't. */
	outw(0x0004, ioaddr+LANCE_DATA);

	अगर (dev->dma != 4)
	अणु
		अचिन्हित दीर्घ flags=claim_dma_lock();
		disable_dma(dev->dma);
		release_dma_lock(flags);
	पूर्ण
	मुक्त_irq(dev->irq, dev);

	lance_purge_ring(dev);

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *lance_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = dev->ml_priv;

	अगर (chip_table[lp->chip_version].flags & LANCE_HAS_MISSED_FRAME) अणु
		लघु ioaddr = dev->base_addr;
		लघु saved_addr;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&lp->devlock, flags);
		saved_addr = inw(ioaddr+LANCE_ADDR);
		outw(112, ioaddr+LANCE_ADDR);
		dev->stats.rx_missed_errors = inw(ioaddr+LANCE_DATA);
		outw(saved_addr, ioaddr+LANCE_ADDR);
		spin_unlock_irqrestore(&lp->devlock, flags);
	पूर्ण

	वापस &dev->stats;
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor.
 */

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	लघु ioaddr = dev->base_addr;

	outw(0, ioaddr+LANCE_ADDR);
	outw(0x0004, ioaddr+LANCE_DATA); /* Temporarily stop the lance.	 */

	अगर (dev->flags&IFF_PROMISC) अणु
		outw(15, ioaddr+LANCE_ADDR);
		outw(0x8000, ioaddr+LANCE_DATA); /* Set promiscuous mode */
	पूर्ण अन्यथा अणु
		लघु multicast_table[4];
		पूर्णांक i;
		पूर्णांक num_addrs=netdev_mc_count(dev);
		अगर(dev->flags&IFF_ALLMULTI)
			num_addrs=1;
		/* FIXIT: We करोn't use the multicast table, but rely on upper-layer filtering. */
		स_रखो(multicast_table, (num_addrs == 0) ? 0 : -1, माप(multicast_table));
		क्रम (i = 0; i < 4; i++) अणु
			outw(8 + i, ioaddr+LANCE_ADDR);
			outw(multicast_table[i], ioaddr+LANCE_DATA);
		पूर्ण
		outw(15, ioaddr+LANCE_ADDR);
		outw(0x0000, ioaddr+LANCE_DATA); /* Unset promiscuous mode */
	पूर्ण

	lance_restart(dev, 0x0142, 0); /*  Resume normal operation */

पूर्ण

