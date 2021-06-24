<शैली गुरु>
/* sbni.c:  Granch SBNI12 leased line adapters driver क्रम linux
 *
 *	Written 2001 by Denis I.Timofeev (timofeev@granch.ru)
 *
 *	Previous versions were written by Yaroslav Polyakov,
 *	Alexey Zverev and Max Khon.
 *
 *	Driver supports SBNI12-02,-04,-05,-10,-11 cards, single and
 *	द्विगुन-channel, PCI and ISA modअगरications.
 *	More info and useful utilities to work with SBNI12 cards you can find
 *	at http://www.granch.com (English) or http://www.granch.ru (Russian)
 *
 *	This software may be used and distributed according to the terms
 *	of the GNU General Public License.
 *
 *
 *  5.0.1	Jun 22 2001
 *	  - Fixed bug in probe
 *  5.0.0	Jun 06 2001
 *	  - Driver was completely redeचिन्हित by Denis I.Timofeev,
 *	  - now PCI/Dual, ISA/Dual (with single पूर्णांकerrupt line) models are
 *	  - supported
 *  3.3.0	Thu Feb 24 21:30:28 NOVT 2000 
 *        - PCI cards support
 *  3.2.0	Mon Dec 13 22:26:53 NOVT 1999
 * 	  - Completely rebuilt all the packet storage प्रणाली
 * 	  -    to work in Ethernet-like style.
 *  3.1.1	just fixed some bugs (5 aug 1999)
 *  3.1.0	added balancing feature	(26 apr 1999)
 *  3.0.1	just fixed some bugs (14 apr 1999).
 *  3.0.0	Initial Revision, Yaroslav Polyakov (24 Feb 1999)
 *        - added pre-calculation क्रम CRC, fixed bug with "len-2" frames, 
 *        - हटाओd outbound fragmentation (MTU=1000), written CRC-calculation 
 *        - on यंत्र, added work with hard_headers and now we have our own cache 
 *        - क्रम them, optionally supported word-पूर्णांकerchange on some chipsets,
 * 
 *	Known problem: this driver wasn't tested on multiprocessor machine.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश <net/net_namespace.h>
#समावेश <net/arp.h>
#समावेश <net/Space.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#समावेश "sbni.h"

/* device निजी data */

काष्ठा net_local अणु
	काष्ठा समयr_list	watchकरोg;
	काष्ठा net_device	*watchकरोg_dev;

	spinlock_t	lock;
	काष्ठा sk_buff  *rx_buf_p;		/* receive buffer ptr */
	काष्ठा sk_buff  *tx_buf_p;		/* transmit buffer ptr */
	
	अचिन्हित पूर्णांक	framelen;		/* current frame length */
	अचिन्हित पूर्णांक	maxframe;		/* maximum valid frame length */
	अचिन्हित पूर्णांक	state;
	अचिन्हित पूर्णांक	inppos, outpos;		/* positions in rx/tx buffers */

	/* transmitting frame number - from frames qty to 1 */
	अचिन्हित पूर्णांक	tx_frameno;

	/* expected number of next receiving frame */
	अचिन्हित पूर्णांक	रुको_frameno;

	/* count of failed attempts to frame send - 32 attempts करो beक्रमe
	   error - जबतक receiver tunes on opposite side of wire */
	अचिन्हित पूर्णांक	trans_errors;

	/* idle समय; send pong when limit exceeded */
	अचिन्हित पूर्णांक	समयr_ticks;

	/* fields used क्रम receive level स्वतःselection */
	पूर्णांक	delta_rxl;
	अचिन्हित पूर्णांक	cur_rxl_index, समयout_rxl;
	अचिन्हित दीर्घ	cur_rxl_rcvd, prev_rxl_rcvd;

	काष्ठा sbni_csr1	csr1;		/* current value of CSR1 */
	काष्ठा sbni_in_stats	in_stats; 	/* पूर्णांकernal statistics */ 

	काष्ठा net_device		*second;	/* क्रम ISA/dual cards */

#अगर_घोषित CONFIG_SBNI_MULTILINE
	काष्ठा net_device		*master;
	काष्ठा net_device		*link;
#पूर्ण_अगर
पूर्ण;


अटल पूर्णांक  sbni_card_probe( अचिन्हित दीर्घ );
अटल पूर्णांक  sbni_pci_probe( काष्ठा net_device  * );
अटल काष्ठा net_device  *sbni_probe1(काष्ठा net_device *, अचिन्हित दीर्घ, पूर्णांक);
अटल पूर्णांक  sbni_खोलो( काष्ठा net_device * );
अटल पूर्णांक  sbni_बंद( काष्ठा net_device * );
अटल netdev_tx_t sbni_start_xmit(काष्ठा sk_buff *,
					 काष्ठा net_device * );
अटल पूर्णांक  sbni_ioctl( काष्ठा net_device *, काष्ठा अगरreq *, पूर्णांक );
अटल व्योम  set_multicast_list( काष्ठा net_device * );

अटल irqवापस_t sbni_पूर्णांकerrupt( पूर्णांक, व्योम * );
अटल व्योम  handle_channel( काष्ठा net_device * );
अटल पूर्णांक   recv_frame( काष्ठा net_device * );
अटल व्योम  send_frame( काष्ठा net_device * );
अटल पूर्णांक   upload_data( काष्ठा net_device *,
			  अचिन्हित, अचिन्हित, अचिन्हित, u32 );
अटल व्योम  करोwnload_data( काष्ठा net_device *, u32 * );
अटल व्योम  sbni_watchकरोg(काष्ठा समयr_list *);
अटल व्योम  पूर्णांकerpret_ack( काष्ठा net_device *, अचिन्हित );
अटल पूर्णांक   append_frame_to_pkt( काष्ठा net_device *, अचिन्हित, u32 );
अटल व्योम  indicate_pkt( काष्ठा net_device * );
अटल व्योम  card_start( काष्ठा net_device * );
अटल व्योम  prepare_to_send( काष्ठा sk_buff *, काष्ठा net_device * );
अटल व्योम  drop_xmit_queue( काष्ठा net_device * );
अटल व्योम  send_frame_header( काष्ठा net_device *, u32 * );
अटल पूर्णांक   skip_tail( अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, u32 );
अटल पूर्णांक   check_fhdr( u32, u32 *, u32 *, u32 *, u32 *, u32 * );
अटल व्योम  change_level( काष्ठा net_device * );
अटल व्योम  समयout_change_level( काष्ठा net_device * );
अटल u32   calc_crc32( u32, u8 *, u32 );
अटल काष्ठा sk_buff *  get_rx_buf( काष्ठा net_device * );
अटल पूर्णांक  sbni_init( काष्ठा net_device * );

#अगर_घोषित CONFIG_SBNI_MULTILINE
अटल पूर्णांक  enslave( काष्ठा net_device *, काष्ठा net_device * );
अटल पूर्णांक  emancipate( काष्ठा net_device * );
#पूर्ण_अगर

अटल स्थिर अक्षर  version[] =
	"Granch SBNI12 driver ver 5.0.1  Jun 22 2001  Denis I.Timofeev.\n";

अटल bool skip_pci_probe	__initdata = false;
अटल पूर्णांक  scanकरोne	__initdata = 0;
अटल पूर्णांक  num		__initdata = 0;

अटल अचिन्हित अक्षर  rxl_tab[];
अटल u32  crc32tab[];

/* A list of all installed devices, क्रम removing the driver module. */
अटल काष्ठा net_device  *sbni_cards[ SBNI_MAX_NUM_CARDS ];

/* Lists of device's parameters */
अटल u32	io[   SBNI_MAX_NUM_CARDS ] __initdata =
	अणु [0 ... SBNI_MAX_NUM_CARDS-1] = -1 पूर्ण;
अटल u32	irq[  SBNI_MAX_NUM_CARDS ] __initdata;
अटल u32	baud[ SBNI_MAX_NUM_CARDS ] __initdata;
अटल u32	rxl[  SBNI_MAX_NUM_CARDS ] __initdata =
	अणु [0 ... SBNI_MAX_NUM_CARDS-1] = -1 पूर्ण;
अटल u32	mac[  SBNI_MAX_NUM_CARDS ] __initdata;

#अगर_अघोषित MODULE
प्रकार u32  iarr[];
अटल iarr *dest[5] __initdata = अणु &io, &irq, &baud, &rxl, &mac पूर्ण;
#पूर्ण_अगर

/* A zero-terminated list of I/O addresses to be probed on ISA bus */
अटल अचिन्हित पूर्णांक  netcard_portlist[ ] __initdata = अणु 
	0x210, 0x214, 0x220, 0x224, 0x230, 0x234, 0x240, 0x244, 0x250, 0x254,
	0x260, 0x264, 0x270, 0x274, 0x280, 0x284, 0x290, 0x294, 0x2a0, 0x2a4,
	0x2b0, 0x2b4, 0x2c0, 0x2c4, 0x2d0, 0x2d4, 0x2e0, 0x2e4, 0x2f0, 0x2f4,
	0 पूर्ण;

#घोषणा NET_LOCAL_LOCK(dev) (((काष्ठा net_local *)netdev_priv(dev))->lock)

/*
 * Look क्रम SBNI card which addr stored in dev->base_addr, अगर nonzero.
 * Otherwise, look through PCI bus. If none PCI-card was found, scan ISA.
 */

अटल अंतरभूत पूर्णांक __init
sbni_isa_probe( काष्ठा net_device  *dev )
अणु
	अगर( dev->base_addr > 0x1ff &&
	    request_region( dev->base_addr, SBNI_IO_EXTENT, dev->name ) &&
	    sbni_probe1( dev, dev->base_addr, dev->irq ) )

		वापस  0;
	अन्यथा अणु
		pr_err("base address 0x%lx is busy, or adapter is malfunctional!\n",
		       dev->base_addr);
		वापस  -ENODEV;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops sbni_netdev_ops = अणु
	.nकरो_खोलो		= sbni_खोलो,
	.nकरो_stop		= sbni_बंद,
	.nकरो_start_xmit		= sbni_start_xmit,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_करो_ioctl		= sbni_ioctl,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल व्योम __init sbni_devsetup(काष्ठा net_device *dev)
अणु
	ether_setup( dev );
	dev->netdev_ops = &sbni_netdev_ops;
पूर्ण

पूर्णांक __init sbni_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev;
	पूर्णांक err;

	dev = alloc_netdev(माप(काष्ठा net_local), "sbni",
			   NET_NAME_UNKNOWN, sbni_devsetup);
	अगर (!dev)
		वापस -ENOMEM;

	dev->netdev_ops = &sbni_netdev_ops;

	प्र_लिखो(dev->name, "sbni%d", unit);
	netdev_boot_setup_check(dev);

	err = sbni_init(dev);
	अगर (err) अणु
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		release_region( dev->base_addr, SBNI_IO_EXTENT );
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण
	pr_info_once("%s", version);
	वापस 0;
पूर्ण

अटल पूर्णांक __init sbni_init(काष्ठा net_device *dev)
अणु
	पूर्णांक  i;
	अगर( dev->base_addr )
		वापस  sbni_isa_probe( dev );
	/* otherwise we have to perक्रमm search our adapter */

	अगर( io[ num ] != -1 ) अणु
		dev->base_addr	= io[ num ];
		dev->irq	= irq[ num ];
	पूर्ण अन्यथा अगर( scanकरोne  ||  io[ 0 ] != -1 ) अणु
		वापस  -ENODEV;
	पूर्ण

	/* अगर io[ num ] contains non-zero address, then that is on ISA bus */
	अगर( dev->base_addr )
		वापस  sbni_isa_probe( dev );

	/* ...otherwise - scan PCI first */
	अगर( !skip_pci_probe  &&  !sbni_pci_probe( dev ) )
		वापस  0;

	अगर( io[ num ] == -1 ) अणु
		/* Auto-scan will be stopped when first ISA card were found */
		scanकरोne = 1;
		अगर( num > 0 )
			वापस  -ENODEV;
	पूर्ण

	क्रम( i = 0;  netcard_portlist[ i ];  ++i ) अणु
		पूर्णांक  ioaddr = netcard_portlist[ i ];
		अगर( request_region( ioaddr, SBNI_IO_EXTENT, dev->name ) &&
		    sbni_probe1( dev, ioaddr, 0 ))
			वापस 0;
	पूर्ण

	वापस  -ENODEV;
पूर्ण


अटल पूर्णांक __init
sbni_pci_probe( काष्ठा net_device  *dev )
अणु
	काष्ठा pci_dev  *pdev = शून्य;

	जबतक( (pdev = pci_get_class( PCI_CLASS_NETWORK_OTHER << 8, pdev ))
	       != शून्य ) अणु
		पूर्णांक  pci_irq_line;
		अचिन्हित दीर्घ  pci_ioaddr;

		अगर( pdev->venकरोr != SBNI_PCI_VENDOR &&
		    pdev->device != SBNI_PCI_DEVICE )
			जारी;

		pci_ioaddr = pci_resource_start( pdev, 0 );
		pci_irq_line = pdev->irq;

		/* Aव्योम alपढ़ोy found cards from previous calls */
		अगर( !request_region( pci_ioaddr, SBNI_IO_EXTENT, dev->name ) ) अणु
			अगर (pdev->subप्रणाली_device != 2)
				जारी;

			/* Dual adapter is present */
			अगर (!request_region(pci_ioaddr += 4, SBNI_IO_EXTENT,
							dev->name ) )
				जारी;
		पूर्ण

		अगर (pci_irq_line <= 0 || pci_irq_line >= nr_irqs)
			pr_warn(
"WARNING: The PCI BIOS assigned this PCI card to IRQ %d, which is unlikely to work!.\n"
"You should use the PCI BIOS setup to assign a valid IRQ line.\n",
				pci_irq_line );

		/* aव्योमing re-enable dual adapters */
		अगर( (pci_ioaddr & 7) == 0  &&  pci_enable_device( pdev ) ) अणु
			release_region( pci_ioaddr, SBNI_IO_EXTENT );
			pci_dev_put( pdev );
			वापस  -EIO;
		पूर्ण
		अगर( sbni_probe1( dev, pci_ioaddr, pci_irq_line ) ) अणु
			SET_NETDEV_DEV(dev, &pdev->dev);
			/* not the best thing to करो, but this is all messed up 
			   क्रम hotplug प्रणालीs anyway... */
			pci_dev_put( pdev );
			वापस  0;
		पूर्ण
	पूर्ण
	वापस  -ENODEV;
पूर्ण


अटल काष्ठा net_device * __init
sbni_probe1( काष्ठा net_device  *dev,  अचिन्हित दीर्घ  ioaddr,  पूर्णांक  irq )
अणु
	काष्ठा net_local  *nl;

	अगर( sbni_card_probe( ioaddr ) ) अणु
		release_region( ioaddr, SBNI_IO_EXTENT );
		वापस शून्य;
	पूर्ण

	outb( 0, ioaddr + CSR0 );

	अगर( irq < 2 ) अणु
		अचिन्हित दीर्घ irq_mask;

		irq_mask = probe_irq_on();
		outb( EN_INT | TR_REQ, ioaddr + CSR0 );
		outb( PR_RES, ioaddr + CSR1 );
		mdelay(50);
		irq = probe_irq_off(irq_mask);
		outb( 0, ioaddr + CSR0 );

		अगर( !irq ) अणु
			pr_err("%s: can't detect device irq!\n", dev->name);
			release_region( ioaddr, SBNI_IO_EXTENT );
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर( irq == 2 )
		irq = 9;

	dev->irq = irq;
	dev->base_addr = ioaddr;

	/* Fill in sbni-specअगरic dev fields. */
	nl = netdev_priv(dev);
	अगर( !nl ) अणु
		pr_err("%s: unable to get memory!\n", dev->name);
		release_region( ioaddr, SBNI_IO_EXTENT );
		वापस शून्य;
	पूर्ण

	स_रखो( nl, 0, माप(काष्ठा net_local) );
	spin_lock_init( &nl->lock );

	/* store MAC address (generate अगर that isn't known) */
	*(__be16 *)dev->dev_addr = htons( 0x00ff );
	*(__be32 *)(dev->dev_addr + 2) = htonl( 0x01000000 |
		((mac[num] ?
		mac[num] :
		(u32)((दीर्घ)netdev_priv(dev))) & 0x00ffffff));

	/* store link settings (speed, receive level ) */
	nl->maxframe  = DEFAULT_FRAME_LEN;
	nl->csr1.rate = baud[ num ];

	अगर( (nl->cur_rxl_index = rxl[ num ]) == -1 ) अणु
		/* स्वतःtune rxl */
		nl->cur_rxl_index = DEF_RXL;
		nl->delta_rxl = DEF_RXL_DELTA;
	पूर्ण अन्यथा अणु
		nl->delta_rxl = 0;
	पूर्ण
	nl->csr1.rxl  = rxl_tab[ nl->cur_rxl_index ];
	अगर( inb( ioaddr + CSR0 ) & 0x01 )
		nl->state |= FL_SLOW_MODE;

	pr_notice("%s: ioaddr %#lx, irq %d, MAC: 00:ff:01:%02x:%02x:%02x\n",
		  dev->name, dev->base_addr, dev->irq,
		  ((u8 *)dev->dev_addr)[3],
		  ((u8 *)dev->dev_addr)[4],
		  ((u8 *)dev->dev_addr)[5]);

	pr_notice("%s: speed %d",
		  dev->name,
		  ((nl->state & FL_SLOW_MODE) ? 500000 : 2000000)
		  / (1 << nl->csr1.rate));

	अगर( nl->delta_rxl == 0 )
		pr_cont(", receive level 0x%x (fixed)\n", nl->cur_rxl_index);
	अन्यथा
		pr_cont(", receive level (auto)\n");

#अगर_घोषित CONFIG_SBNI_MULTILINE
	nl->master = dev;
	nl->link   = शून्य;
#पूर्ण_अगर
   
	sbni_cards[ num++ ] = dev;
	वापस  dev;
पूर्ण

/* -------------------------------------------------------------------------- */

#अगर_घोषित CONFIG_SBNI_MULTILINE

अटल netdev_tx_t
sbni_start_xmit( काष्ठा sk_buff  *skb,  काष्ठा net_device  *dev )
अणु
	काष्ठा net_device  *p;

	netअगर_stop_queue( dev );

	/* Looking क्रम idle device in the list */
	क्रम( p = dev;  p; ) अणु
		काष्ठा net_local  *nl = netdev_priv(p);
		spin_lock( &nl->lock );
		अगर( nl->tx_buf_p  ||  (nl->state & FL_LINE_DOWN) ) अणु
			p = nl->link;
			spin_unlock( &nl->lock );
		पूर्ण अन्यथा अणु
			/* Idle dev is found */
			prepare_to_send( skb, p );
			spin_unlock( &nl->lock );
			netअगर_start_queue( dev );
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	वापस NETDEV_TX_BUSY;
पूर्ण

#अन्यथा	/* CONFIG_SBNI_MULTILINE */

अटल netdev_tx_t
sbni_start_xmit( काष्ठा sk_buff  *skb,  काष्ठा net_device  *dev )
अणु
	काष्ठा net_local  *nl  = netdev_priv(dev);

	netअगर_stop_queue( dev );
	spin_lock( &nl->lock );

	prepare_to_send( skb, dev );

	spin_unlock( &nl->lock );
	वापस NETDEV_TX_OK;
पूर्ण

#पूर्ण_अगर	/* CONFIG_SBNI_MULTILINE */

/* -------------------------------------------------------------------------- */

/* पूर्णांकerrupt handler */

/*
 * 	SBNI12D-10, -11/ISA boards within "common interrupt" mode could not
 * be looked as two independent single-channel devices. Every channel seems
 * as Ethernet पूर्णांकerface but पूर्णांकerrupt handler must be common. Really, first
 * channel ("master") driver only रेजिस्टरs the handler. In its काष्ठा net_local
 * it has got poपूर्णांकer to "slave" channel's struct net_local and handles that's
 * पूर्णांकerrupts too.
 *	dev of successfully attached ISA SBNI boards is linked to list.
 * While next board driver is initialized, it scans this list. If one
 * has found dev with same irq and ioaddr dअगरferent by 4 then it assumes
 * this board to be "master".
 */ 

अटल irqवापस_t
sbni_पूर्णांकerrupt( पूर्णांक  irq,  व्योम  *dev_id )
अणु
	काष्ठा net_device	  *dev = dev_id;
	काष्ठा net_local  *nl  = netdev_priv(dev);
	पूर्णांक	repeat;

	spin_lock( &nl->lock );
	अगर( nl->second )
		spin_lock(&NET_LOCAL_LOCK(nl->second));

	करो अणु
		repeat = 0;
		अगर( inb( dev->base_addr + CSR0 ) & (RC_RDY | TR_RDY) ) अणु
			handle_channel( dev );
			repeat = 1;
		पूर्ण
		अगर( nl->second  && 	/* second channel present */
		    (inb( nl->second->base_addr+CSR0 ) & (RC_RDY | TR_RDY)) ) अणु
			handle_channel( nl->second );
			repeat = 1;
		पूर्ण
	पूर्ण जबतक( repeat );

	अगर( nl->second )
		spin_unlock(&NET_LOCAL_LOCK(nl->second));
	spin_unlock( &nl->lock );
	वापस IRQ_HANDLED;
पूर्ण


अटल व्योम
handle_channel( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local	*nl    = netdev_priv(dev);
	अचिन्हित दीर्घ		ioaddr = dev->base_addr;

	पूर्णांक  req_ans;
	अचिन्हित अक्षर  csr0;

#अगर_घोषित CONFIG_SBNI_MULTILINE
	/* Lock the master device because we going to change its local data */
	अगर( nl->state & FL_SLAVE )
		spin_lock(&NET_LOCAL_LOCK(nl->master));
#पूर्ण_अगर

	outb( (inb( ioaddr + CSR0 ) & ~EN_INT) | TR_REQ, ioaddr + CSR0 );

	nl->समयr_ticks = CHANGE_LEVEL_START_TICKS;
	क्रम(;;) अणु
		csr0 = inb( ioaddr + CSR0 );
		अगर( ( csr0 & (RC_RDY | TR_RDY) ) == 0 )
			अवरोध;

		req_ans = !(nl->state & FL_PREV_OK);

		अगर( csr0 & RC_RDY )
			req_ans = recv_frame( dev );

		/*
		 * TR_RDY always equals 1 here because we have owned the marker,
		 * and we set TR_REQ when disabled पूर्णांकerrupts
		 */
		csr0 = inb( ioaddr + CSR0 );
		अगर( !(csr0 & TR_RDY)  ||  (csr0 & RC_RDY) )
			netdev_err(dev, "internal error!\n");

		/* अगर state & FL_NEED_RESEND != 0 then tx_frameno != 0 */
		अगर( req_ans  ||  nl->tx_frameno != 0 )
			send_frame( dev );
		अन्यथा
			/* send marker without any data */
			outb( inb( ioaddr + CSR0 ) & ~TR_REQ, ioaddr + CSR0 );
	पूर्ण

	outb( inb( ioaddr + CSR0 ) | EN_INT, ioaddr + CSR0 );

#अगर_घोषित CONFIG_SBNI_MULTILINE
	अगर( nl->state & FL_SLAVE )
		spin_unlock(&NET_LOCAL_LOCK(nl->master));
#पूर्ण_अगर
पूर्ण


/*
 * Routine वापसs 1 अगर it needs to acknowledge received frame.
 * Empty frame received without errors won't be acknowledged.
 */

अटल पूर्णांक
recv_frame( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local  *nl   = netdev_priv(dev);
	अचिन्हित दीर्घ  ioaddr	= dev->base_addr;

	u32  crc = CRC32_INITIAL;

	अचिन्हित  framelen = 0, frameno, ack;
	अचिन्हित  is_first, frame_ok = 0;

	अगर( check_fhdr( ioaddr, &framelen, &frameno, &ack, &is_first, &crc ) ) अणु
		frame_ok = framelen > 4
			?  upload_data( dev, framelen, frameno, is_first, crc )
			:  skip_tail( ioaddr, framelen, crc );
		अगर( frame_ok )
			पूर्णांकerpret_ack( dev, ack );
	पूर्ण

	outb( inb( ioaddr + CSR0 ) ^ CT_ZER, ioaddr + CSR0 );
	अगर( frame_ok ) अणु
		nl->state |= FL_PREV_OK;
		अगर( framelen > 4 )
			nl->in_stats.all_rx_number++;
	पूर्ण अन्यथा अणु
		nl->state &= ~FL_PREV_OK;
		change_level( dev );
		nl->in_stats.all_rx_number++;
		nl->in_stats.bad_rx_number++;
	पूर्ण

	वापस  !frame_ok  ||  framelen > 4;
पूर्ण


अटल व्योम
send_frame( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local  *nl    = netdev_priv(dev);

	u32  crc = CRC32_INITIAL;

	अगर( nl->state & FL_NEED_RESEND ) अणु

		/* अगर frame was sended but not ACK'ed - resend it */
		अगर( nl->trans_errors ) अणु
			--nl->trans_errors;
			अगर( nl->framelen != 0 )
				nl->in_stats.resend_tx_number++;
		पूर्ण अन्यथा अणु
			/* cannot xmit with many attempts */
#अगर_घोषित CONFIG_SBNI_MULTILINE
			अगर( (nl->state & FL_SLAVE)  ||  nl->link )
#पूर्ण_अगर
			nl->state |= FL_LINE_DOWN;
			drop_xmit_queue( dev );
			जाओ  करो_send;
		पूर्ण
	पूर्ण अन्यथा
		nl->trans_errors = TR_ERROR_COUNT;

	send_frame_header( dev, &crc );
	nl->state |= FL_NEED_RESEND;
	/*
	 * FL_NEED_RESEND will be cleared after ACK, but अगर empty
	 * frame sended then in prepare_to_send next frame
	 */


	अगर( nl->framelen ) अणु
		करोwnload_data( dev, &crc );
		nl->in_stats.all_tx_number++;
		nl->state |= FL_WAIT_ACK;
	पूर्ण

	outsb( dev->base_addr + DAT, (u8 *)&crc, माप crc );

करो_send:
	outb( inb( dev->base_addr + CSR0 ) & ~TR_REQ, dev->base_addr + CSR0 );

	अगर( nl->tx_frameno )
		/* next frame exists - we request card to send it */
		outb( inb( dev->base_addr + CSR0 ) | TR_REQ,
		      dev->base_addr + CSR0 );
पूर्ण


/*
 * Write the frame data पूर्णांकo adapter's buffer memory, and calculate CRC.
 * Do padding अगर necessary.
 */

अटल व्योम
करोwnload_data( काष्ठा net_device  *dev,  u32  *crc_p )
अणु
	काष्ठा net_local  *nl    = netdev_priv(dev);
	काष्ठा sk_buff    *skb	 = nl->tx_buf_p;

	अचिन्हित  len = min_t(अचिन्हित पूर्णांक, skb->len - nl->outpos, nl->framelen);

	outsb( dev->base_addr + DAT, skb->data + nl->outpos, len );
	*crc_p = calc_crc32( *crc_p, skb->data + nl->outpos, len );

	/* अगर packet too लघु we should ग_लिखो some more bytes to pad */
	क्रम( len = nl->framelen - len;  len--; ) अणु
		outb( 0, dev->base_addr + DAT );
		*crc_p = CRC32( 0, *crc_p );
	पूर्ण
पूर्ण


अटल पूर्णांक
upload_data( काष्ठा net_device  *dev,  अचिन्हित  framelen,  अचिन्हित  frameno,
	     अचिन्हित  is_first,  u32  crc )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);

	पूर्णांक  frame_ok;

	अगर( is_first ) अणु
		nl->रुको_frameno = frameno;
		nl->inppos = 0;
	पूर्ण

	अगर( nl->रुको_frameno == frameno ) अणु

		अगर( nl->inppos + framelen  <=  ETHER_MAX_LEN )
			frame_ok = append_frame_to_pkt( dev, framelen, crc );

		/*
		 * अगर CRC is right but framelen incorrect then transmitter
		 * error was occurred... drop entire packet
		 */
		अन्यथा अगर( (frame_ok = skip_tail( dev->base_addr, framelen, crc ))
			 != 0 ) अणु
			nl->रुको_frameno = 0;
			nl->inppos = 0;
#अगर_घोषित CONFIG_SBNI_MULTILINE
			nl->master->stats.rx_errors++;
			nl->master->stats.rx_missed_errors++;
#अन्यथा
		        dev->stats.rx_errors++;
			dev->stats.rx_missed_errors++;
#पूर्ण_अगर
		पूर्ण
			/* now skip all frames until is_first != 0 */
	पूर्ण अन्यथा
		frame_ok = skip_tail( dev->base_addr, framelen, crc );

	अगर( is_first  &&  !frame_ok ) अणु
		/*
		 * Frame has been broken, but we had alपढ़ोy stored
		 * is_first... Drop entire packet.
		 */
		nl->रुको_frameno = 0;
#अगर_घोषित CONFIG_SBNI_MULTILINE
		nl->master->stats.rx_errors++;
		nl->master->stats.rx_crc_errors++;
#अन्यथा
		dev->stats.rx_errors++;
		dev->stats.rx_crc_errors++;
#पूर्ण_अगर
	पूर्ण

	वापस  frame_ok;
पूर्ण


अटल अंतरभूत व्योम
send_complete( काष्ठा net_device *dev )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);

#अगर_घोषित CONFIG_SBNI_MULTILINE
	nl->master->stats.tx_packets++;
	nl->master->stats.tx_bytes += nl->tx_buf_p->len;
#अन्यथा
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += nl->tx_buf_p->len;
#पूर्ण_अगर
	dev_consume_skb_irq(nl->tx_buf_p);

	nl->tx_buf_p = शून्य;

	nl->outpos = 0;
	nl->state &= ~(FL_WAIT_ACK | FL_NEED_RESEND);
	nl->framelen   = 0;
पूर्ण


अटल व्योम
पूर्णांकerpret_ack( काष्ठा net_device  *dev,  अचिन्हित  ack )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);

	अगर( ack == FRAME_SENT_OK ) अणु
		nl->state &= ~FL_NEED_RESEND;

		अगर( nl->state & FL_WAIT_ACK ) अणु
			nl->outpos += nl->framelen;

			अगर( --nl->tx_frameno ) अणु
				nl->framelen = min_t(अचिन्हित पूर्णांक,
						   nl->maxframe,
						   nl->tx_buf_p->len - nl->outpos);
			पूर्ण अन्यथा अणु
				send_complete( dev );
#अगर_घोषित CONFIG_SBNI_MULTILINE
				netअगर_wake_queue( nl->master );
#अन्यथा
				netअगर_wake_queue( dev );
#पूर्ण_अगर
			पूर्ण
		पूर्ण
	पूर्ण

	nl->state &= ~FL_WAIT_ACK;
पूर्ण


/*
 * Glue received frame with previous fragments of packet.
 * Indicate packet when last frame would be accepted.
 */

अटल पूर्णांक
append_frame_to_pkt( काष्ठा net_device  *dev,  अचिन्हित  framelen,  u32  crc )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);

	u8  *p;

	अगर( nl->inppos + framelen  >  ETHER_MAX_LEN )
		वापस  0;

	अगर( !nl->rx_buf_p  &&  !(nl->rx_buf_p = get_rx_buf( dev )) )
		वापस  0;

	p = nl->rx_buf_p->data + nl->inppos;
	insb( dev->base_addr + DAT, p, framelen );
	अगर( calc_crc32( crc, p, framelen ) != CRC32_REMAINDER )
		वापस  0;

	nl->inppos += framelen - 4;
	अगर( --nl->रुको_frameno == 0 )		/* last frame received */
		indicate_pkt( dev );

	वापस  1;
पूर्ण


/*
 * Prepare to start output on adapter.
 * Transmitter will be actually activated when marker is accepted.
 */

अटल व्योम
prepare_to_send( काष्ठा sk_buff  *skb,  काष्ठा net_device  *dev )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);

	अचिन्हित पूर्णांक  len;

	/* nl->tx_buf_p == शून्य here! */
	अगर( nl->tx_buf_p )
		netdev_err(dev, "memory leak!\n");

	nl->outpos = 0;
	nl->state &= ~(FL_WAIT_ACK | FL_NEED_RESEND);

	len = skb->len;
	अगर( len < SBNI_MIN_LEN )
		len = SBNI_MIN_LEN;

	nl->tx_buf_p	= skb;
	nl->tx_frameno	= DIV_ROUND_UP(len, nl->maxframe);
	nl->framelen	= len < nl->maxframe  ?  len  :  nl->maxframe;

	outb( inb( dev->base_addr + CSR0 ) | TR_REQ,  dev->base_addr + CSR0 );
#अगर_घोषित CONFIG_SBNI_MULTILINE
	netअगर_trans_update(nl->master);
#अन्यथा
	netअगर_trans_update(dev);
#पूर्ण_अगर
पूर्ण


अटल व्योम
drop_xmit_queue( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);

	अगर( nl->tx_buf_p ) अणु
		dev_kमुक्त_skb_any( nl->tx_buf_p );
		nl->tx_buf_p = शून्य;
#अगर_घोषित CONFIG_SBNI_MULTILINE
		nl->master->stats.tx_errors++;
		nl->master->stats.tx_carrier_errors++;
#अन्यथा
		dev->stats.tx_errors++;
		dev->stats.tx_carrier_errors++;
#पूर्ण_अगर
	पूर्ण

	nl->tx_frameno	= 0;
	nl->framelen	= 0;
	nl->outpos	= 0;
	nl->state &= ~(FL_WAIT_ACK | FL_NEED_RESEND);
#अगर_घोषित CONFIG_SBNI_MULTILINE
	netअगर_start_queue( nl->master );
	netअगर_trans_update(nl->master);
#अन्यथा
	netअगर_start_queue( dev );
	netअगर_trans_update(dev);
#पूर्ण_अगर
पूर्ण


अटल व्योम
send_frame_header( काष्ठा net_device  *dev,  u32  *crc_p )
अणु
	काष्ठा net_local  *nl  = netdev_priv(dev);

	u32  crc = *crc_p;
	u32  len_field = nl->framelen + 6;	/* CRC + frameno + reserved */
	u8   value;

	अगर( nl->state & FL_NEED_RESEND )
		len_field |= FRAME_RETRY;	/* non-first attempt... */

	अगर( nl->outpos == 0 )
		len_field |= FRAME_FIRST;

	len_field |= (nl->state & FL_PREV_OK) ? FRAME_SENT_OK : FRAME_SENT_BAD;
	outb( SBNI_SIG, dev->base_addr + DAT );

	value = (u8) len_field;
	outb( value, dev->base_addr + DAT );
	crc = CRC32( value, crc );
	value = (u8) (len_field >> 8);
	outb( value, dev->base_addr + DAT );
	crc = CRC32( value, crc );

	outb( nl->tx_frameno, dev->base_addr + DAT );
	crc = CRC32( nl->tx_frameno, crc );
	outb( 0, dev->base_addr + DAT );
	crc = CRC32( 0, crc );
	*crc_p = crc;
पूर्ण


/*
 * अगर frame tail not needed (incorrect number or received twice),
 * it won't store, but CRC will be calculated
 */

अटल पूर्णांक
skip_tail( अचिन्हित पूर्णांक  ioaddr,  अचिन्हित पूर्णांक  tail_len,  u32 crc )
अणु
	जबतक( tail_len-- )
		crc = CRC32( inb( ioaddr + DAT ), crc );

	वापस  crc == CRC32_REMAINDER;
पूर्ण


/*
 * Preliminary checks अगर frame header is correct, calculates its CRC
 * and split it to simple fields
 */

अटल पूर्णांक
check_fhdr( u32  ioaddr,  u32  *framelen,  u32  *frameno,  u32  *ack,
	    u32  *is_first,  u32  *crc_p )
अणु
	u32  crc = *crc_p;
	u8   value;

	अगर( inb( ioaddr + DAT ) != SBNI_SIG )
		वापस  0;

	value = inb( ioaddr + DAT );
	*framelen = (u32)value;
	crc = CRC32( value, crc );
	value = inb( ioaddr + DAT );
	*framelen |= ((u32)value) << 8;
	crc = CRC32( value, crc );

	*ack = *framelen & FRAME_ACK_MASK;
	*is_first = (*framelen & FRAME_FIRST) != 0;

	अगर( (*framelen &= FRAME_LEN_MASK) < 6 ||
	    *framelen > SBNI_MAX_FRAME - 3 )
		वापस  0;

	value = inb( ioaddr + DAT );
	*frameno = (u32)value;
	crc = CRC32( value, crc );

	crc = CRC32( inb( ioaddr + DAT ), crc );	/* reserved byte */
	*framelen -= 2;

	*crc_p = crc;
	वापस  1;
पूर्ण


अटल काष्ठा sk_buff *
get_rx_buf( काष्ठा net_device  *dev )
अणु
	/* +2 is to compensate क्रम the alignment fixup below */
	काष्ठा sk_buff  *skb = dev_alloc_skb( ETHER_MAX_LEN + 2 );
	अगर( !skb )
		वापस  शून्य;

	skb_reserve( skb, 2 );		/* Align IP on दीर्घword boundaries */
	वापस  skb;
पूर्ण


अटल व्योम
indicate_pkt( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local  *nl  = netdev_priv(dev);
	काष्ठा sk_buff    *skb = nl->rx_buf_p;

	skb_put( skb, nl->inppos );

#अगर_घोषित CONFIG_SBNI_MULTILINE
	skb->protocol = eth_type_trans( skb, nl->master );
	netअगर_rx( skb );
	++nl->master->stats.rx_packets;
	nl->master->stats.rx_bytes += nl->inppos;
#अन्यथा
	skb->protocol = eth_type_trans( skb, dev );
	netअगर_rx( skb );
	++dev->stats.rx_packets;
	dev->stats.rx_bytes += nl->inppos;
#पूर्ण_अगर
	nl->rx_buf_p = शून्य;	/* protocol driver will clear this sk_buff */
पूर्ण


/* -------------------------------------------------------------------------- */

/*
 * Routine checks periodically wire activity and regenerates marker अगर
 * connect was inactive क्रम a दीर्घ समय.
 */

अटल व्योम
sbni_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा net_local   *nl  = from_समयr(nl, t, watchकरोg);
	काष्ठा net_device  *dev = nl->watchकरोg_dev;
	अचिन्हित दीर्घ	   flags;
	अचिन्हित अक्षर	   csr0;

	spin_lock_irqsave( &nl->lock, flags );

	csr0 = inb( dev->base_addr + CSR0 );
	अगर( csr0 & RC_CHK ) अणु

		अगर( nl->समयr_ticks ) अणु
			अगर( csr0 & (RC_RDY | BU_EMP) )
				/* receiving not active */
				nl->समयr_ticks--;
		पूर्ण अन्यथा अणु
			nl->in_stats.समयout_number++;
			अगर( nl->delta_rxl )
				समयout_change_level( dev );

			outb( *(u_अक्षर *)&nl->csr1 | PR_RES,
			      dev->base_addr + CSR1 );
			csr0 = inb( dev->base_addr + CSR0 );
		पूर्ण
	पूर्ण अन्यथा
		nl->state &= ~FL_LINE_DOWN;

	outb( csr0 | RC_CHK, dev->base_addr + CSR0 ); 

	mod_समयr(t, jअगरfies + SBNI_TIMEOUT);

	spin_unlock_irqrestore( &nl->lock, flags );
पूर्ण


अटल अचिन्हित अक्षर  rxl_tab[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08,
	0x0a, 0x0c, 0x0f, 0x16, 0x18, 0x1a, 0x1c, 0x1f
पूर्ण;

#घोषणा SIZE_OF_TIMEOUT_RXL_TAB 4
अटल अचिन्हित अक्षर  समयout_rxl_tab[] = अणु
	0x03, 0x05, 0x08, 0x0b
पूर्ण;

/* -------------------------------------------------------------------------- */

अटल व्योम
card_start( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);

	nl->समयr_ticks = CHANGE_LEVEL_START_TICKS;
	nl->state &= ~(FL_WAIT_ACK | FL_NEED_RESEND);
	nl->state |= FL_PREV_OK;

	nl->inppos = nl->outpos = 0;
	nl->रुको_frameno = 0;
	nl->tx_frameno	 = 0;
	nl->framelen	 = 0;

	outb( *(u_अक्षर *)&nl->csr1 | PR_RES, dev->base_addr + CSR1 );
	outb( EN_INT, dev->base_addr + CSR0 );
पूर्ण

/* -------------------------------------------------------------------------- */

/* Receive level स्वतः-selection */

अटल व्योम
change_level( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);

	अगर( nl->delta_rxl == 0 )	/* करो not स्वतः-negotiate RxL */
		वापस;

	अगर( nl->cur_rxl_index == 0 )
		nl->delta_rxl = 1;
	अन्यथा अगर( nl->cur_rxl_index == 15 )
		nl->delta_rxl = -1;
	अन्यथा अगर( nl->cur_rxl_rcvd < nl->prev_rxl_rcvd )
		nl->delta_rxl = -nl->delta_rxl;

	nl->csr1.rxl = rxl_tab[ nl->cur_rxl_index += nl->delta_rxl ];
	inb( dev->base_addr + CSR0 );	/* needs क्रम PCI cards */
	outb( *(u8 *)&nl->csr1, dev->base_addr + CSR1 );

	nl->prev_rxl_rcvd = nl->cur_rxl_rcvd;
	nl->cur_rxl_rcvd  = 0;
पूर्ण


अटल व्योम
समयout_change_level( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);

	nl->cur_rxl_index = समयout_rxl_tab[ nl->समयout_rxl ];
	अगर( ++nl->समयout_rxl >= 4 )
		nl->समयout_rxl = 0;

	nl->csr1.rxl = rxl_tab[ nl->cur_rxl_index ];
	inb( dev->base_addr + CSR0 );
	outb( *(अचिन्हित अक्षर *)&nl->csr1, dev->base_addr + CSR1 );

	nl->prev_rxl_rcvd = nl->cur_rxl_rcvd;
	nl->cur_rxl_rcvd  = 0;
पूर्ण

/* -------------------------------------------------------------------------- */

/*
 *	Open/initialize the board. 
 */

अटल पूर्णांक
sbni_खोलो( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local	*nl = netdev_priv(dev);
	काष्ठा समयr_list	*w  = &nl->watchकरोg;

	/*
	 * For द्विगुन ISA adapters within "common irq" mode, we have to
	 * determine whether primary or secondary channel is initialized,
	 * and set the irq handler only in first हाल.
	 */
	अगर( dev->base_addr < 0x400 ) अणु		/* ISA only */
		काष्ठा net_device  **p = sbni_cards;
		क्रम( ;  *p  &&  p < sbni_cards + SBNI_MAX_NUM_CARDS;  ++p )
			अगर( (*p)->irq == dev->irq &&
			    ((*p)->base_addr == dev->base_addr + 4 ||
			     (*p)->base_addr == dev->base_addr - 4) &&
			    (*p)->flags & IFF_UP ) अणु

				((काष्ठा net_local *) (netdev_priv(*p)))
					->second = dev;
				netdev_notice(dev, "using shared irq with %s\n",
					      (*p)->name);
				nl->state |= FL_SECONDARY;
				जाओ  handler_attached;
			पूर्ण
	पूर्ण

	अगर( request_irq(dev->irq, sbni_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev) ) अणु
		netdev_err(dev, "unable to get IRQ %d\n", dev->irq);
		वापस  -EAGAIN;
	पूर्ण

handler_attached:

	spin_lock( &nl->lock );
	स_रखो( &dev->stats, 0, माप(काष्ठा net_device_stats) );
	स_रखो( &nl->in_stats, 0, माप(काष्ठा sbni_in_stats) );

	card_start( dev );

	netअगर_start_queue( dev );

	/* set समयr watchकरोg */
	nl->watchकरोg_dev = dev;
	समयr_setup(w, sbni_watchकरोg, 0);
	w->expires	= jअगरfies + SBNI_TIMEOUT;
	add_समयr( w );
   
	spin_unlock( &nl->lock );
	वापस 0;
पूर्ण


अटल पूर्णांक
sbni_बंद( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);

	अगर( nl->second  &&  nl->second->flags & IFF_UP ) अणु
		netdev_notice(dev, "Secondary channel (%s) is active!\n",
			      nl->second->name);
		वापस  -EBUSY;
	पूर्ण

#अगर_घोषित CONFIG_SBNI_MULTILINE
	अगर( nl->state & FL_SLAVE )
		emancipate( dev );
	अन्यथा
		जबतक( nl->link )	/* it's master device! */
			emancipate( nl->link );
#पूर्ण_अगर

	spin_lock( &nl->lock );

	nl->second = शून्य;
	drop_xmit_queue( dev );	
	netअगर_stop_queue( dev );
   
	del_समयr( &nl->watchकरोg );

	outb( 0, dev->base_addr + CSR0 );

	अगर( !(nl->state & FL_SECONDARY) )
		मुक्त_irq( dev->irq, dev );
	nl->state &= FL_SECONDARY;

	spin_unlock( &nl->lock );
	वापस 0;
पूर्ण


/*
	Valid combinations in CSR0 (क्रम probing):

	VALID_DECODER	0000,0011,1011,1010

				    	; 0   ; -
				TR_REQ	; 1   ; +
			TR_RDY	    	; 2   ; -
			TR_RDY	TR_REQ	; 3   ; +
		BU_EMP		    	; 4   ; +
		BU_EMP	     	TR_REQ	; 5   ; +
		BU_EMP	TR_RDY	    	; 6   ; -
		BU_EMP	TR_RDY	TR_REQ	; 7   ; +
	RC_RDY 		     		; 8   ; +
	RC_RDY			TR_REQ	; 9   ; +
	RC_RDY		TR_RDY		; 10  ; -
	RC_RDY		TR_RDY	TR_REQ	; 11  ; -
	RC_RDY	BU_EMP			; 12  ; -
	RC_RDY	BU_EMP		TR_REQ	; 13  ; -
	RC_RDY	BU_EMP	TR_RDY		; 14  ; -
	RC_RDY	BU_EMP	TR_RDY	TR_REQ	; 15  ; -
*/

#घोषणा VALID_DECODER (2 + 8 + 0x10 + 0x20 + 0x80 + 0x100 + 0x200)


अटल पूर्णांक
sbni_card_probe( अचिन्हित दीर्घ  ioaddr )
अणु
	अचिन्हित अक्षर  csr0;

	csr0 = inb( ioaddr + CSR0 );
	अगर( csr0 != 0xff  &&  csr0 != 0x00 ) अणु
		csr0 &= ~EN_INT;
		अगर( csr0 & BU_EMP )
			csr0 |= EN_INT;
      
		अगर( VALID_DECODER & (1 << (csr0 >> 4)) )
			वापस  0;
	पूर्ण
   
	वापस  -ENODEV;
पूर्ण

/* -------------------------------------------------------------------------- */

अटल पूर्णांक
sbni_ioctl( काष्ठा net_device  *dev,  काष्ठा अगरreq  *अगरr,  पूर्णांक  cmd )
अणु
	काष्ठा net_local  *nl = netdev_priv(dev);
	काष्ठा sbni_flags  flags;
	पूर्णांक  error = 0;

#अगर_घोषित CONFIG_SBNI_MULTILINE
	काष्ठा net_device  *slave_dev;
	अक्षर  slave_name[ 8 ];
#पूर्ण_अगर
  
	चयन( cmd ) अणु
	हाल  SIOCDEVGETINSTATS :
		अगर (copy_to_user( अगरr->अगरr_data, &nl->in_stats,
					माप(काष्ठा sbni_in_stats) ))
			error = -EFAULT;
		अवरोध;

	हाल  SIOCDEVRESINSTATS :
		अगर (!capable(CAP_NET_ADMIN))
			वापस  -EPERM;
		स_रखो( &nl->in_stats, 0, माप(काष्ठा sbni_in_stats) );
		अवरोध;

	हाल  SIOCDEVGHWSTATE :
		flags.mac_addr	= *(u32 *)(dev->dev_addr + 3);
		flags.rate	= nl->csr1.rate;
		flags.slow_mode	= (nl->state & FL_SLOW_MODE) != 0;
		flags.rxl	= nl->cur_rxl_index;
		flags.fixed_rxl	= nl->delta_rxl == 0;

		अगर (copy_to_user( अगरr->अगरr_data, &flags, माप flags ))
			error = -EFAULT;
		अवरोध;

	हाल  SIOCDEVSHWSTATE :
		अगर (!capable(CAP_NET_ADMIN))
			वापस  -EPERM;

		spin_lock( &nl->lock );
		flags = *(काष्ठा sbni_flags*) &अगरr->अगरr_अगरru;
		अगर( flags.fixed_rxl ) अणु
			nl->delta_rxl = 0;
			nl->cur_rxl_index = flags.rxl;
		पूर्ण अन्यथा अणु
			nl->delta_rxl = DEF_RXL_DELTA;
			nl->cur_rxl_index = DEF_RXL;
		पूर्ण

		nl->csr1.rxl = rxl_tab[ nl->cur_rxl_index ];
		nl->csr1.rate = flags.rate;
		outb( *(u8 *)&nl->csr1 | PR_RES, dev->base_addr + CSR1 );
		spin_unlock( &nl->lock );
		अवरोध;

#अगर_घोषित CONFIG_SBNI_MULTILINE

	हाल  SIOCDEVENSLAVE :
		अगर (!capable(CAP_NET_ADMIN))
			वापस  -EPERM;

		अगर (copy_from_user( slave_name, अगरr->अगरr_data, माप slave_name ))
			वापस -EFAULT;
		slave_dev = dev_get_by_name(&init_net, slave_name );
		अगर( !slave_dev  ||  !(slave_dev->flags & IFF_UP) ) अणु
			netdev_err(dev, "trying to enslave non-active device %s\n",
				   slave_name);
			अगर (slave_dev)
				dev_put(slave_dev);
			वापस  -EPERM;
		पूर्ण

		वापस  enslave( dev, slave_dev );

	हाल  SIOCDEVEMANSIPATE :
		अगर (!capable(CAP_NET_ADMIN))
			वापस  -EPERM;

		वापस  emancipate( dev );

#पूर्ण_अगर	/* CONFIG_SBNI_MULTILINE */

	शेष :
		वापस  -EOPNOTSUPP;
	पूर्ण

	वापस  error;
पूर्ण


#अगर_घोषित CONFIG_SBNI_MULTILINE

अटल पूर्णांक
enslave( काष्ठा net_device  *dev,  काष्ठा net_device  *slave_dev )
अणु
	काष्ठा net_local  *nl  = netdev_priv(dev);
	काष्ठा net_local  *snl = netdev_priv(slave_dev);

	अगर( nl->state & FL_SLAVE )	/* This isn't master or मुक्त device */
		वापस  -EBUSY;

	अगर( snl->state & FL_SLAVE )	/* That was alपढ़ोy enslaved */
		वापस  -EBUSY;

	spin_lock( &nl->lock );
	spin_lock( &snl->lock );

	/* append to list */
	snl->link = nl->link;
	nl->link  = slave_dev;
	snl->master = dev;
	snl->state |= FL_SLAVE;

	/* Summary statistics of MultiLine operation will be stored
	   in master's counters */
	स_रखो( &slave_dev->stats, 0, माप(काष्ठा net_device_stats) );
	netअगर_stop_queue( slave_dev );
	netअगर_wake_queue( dev );	/* Now we are able to transmit */

	spin_unlock( &snl->lock );
	spin_unlock( &nl->lock );
	netdev_notice(dev, "slave device (%s) attached\n", slave_dev->name);
	वापस  0;
पूर्ण


अटल पूर्णांक
emancipate( काष्ठा net_device  *dev )
अणु
	काष्ठा net_local   *snl = netdev_priv(dev);
	काष्ठा net_device  *p   = snl->master;
	काष्ठा net_local   *nl  = netdev_priv(p);

	अगर( !(snl->state & FL_SLAVE) )
		वापस  -EINVAL;

	spin_lock( &nl->lock );
	spin_lock( &snl->lock );
	drop_xmit_queue( dev );

	/* exclude from list */
	क्रम(;;) अणु	/* must be in list */
		काष्ठा net_local  *t = netdev_priv(p);
		अगर( t->link == dev ) अणु
			t->link = snl->link;
			अवरोध;
		पूर्ण
		p = t->link;
	पूर्ण

	snl->link = शून्य;
	snl->master = dev;
	snl->state &= ~FL_SLAVE;

	netअगर_start_queue( dev );

	spin_unlock( &snl->lock );
	spin_unlock( &nl->lock );

	dev_put( dev );
	वापस  0;
पूर्ण

#पूर्ण_अगर

अटल व्योम
set_multicast_list( काष्ठा net_device  *dev )
अणु
	वापस;		/* sbni always operate in promiscuos mode */
पूर्ण


#अगर_घोषित MODULE
module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
module_param_array(baud, पूर्णांक, शून्य, 0);
module_param_array(rxl, पूर्णांक, शून्य, 0);
module_param_array(mac, पूर्णांक, शून्य, 0);
module_param(skip_pci_probe, bool, 0);

MODULE_LICENSE("GPL");


पूर्णांक __init init_module( व्योम )
अणु
	काष्ठा net_device  *dev;
	पूर्णांक err;

	जबतक( num < SBNI_MAX_NUM_CARDS ) अणु
		dev = alloc_netdev(माप(काष्ठा net_local), "sbni%d",
				   NET_NAME_UNKNOWN, sbni_devsetup);
		अगर( !dev)
			अवरोध;

		प्र_लिखो( dev->name, "sbni%d", num );

		err = sbni_init(dev);
		अगर (err) अणु
			मुक्त_netdev(dev);
			अवरोध;
		पूर्ण

		अगर( रेजिस्टर_netdev( dev ) ) अणु
			release_region( dev->base_addr, SBNI_IO_EXTENT );
			मुक्त_netdev( dev );
			अवरोध;
		पूर्ण
	पूर्ण

	वापस  *sbni_cards  ?  0  :  -ENODEV;
पूर्ण

व्योम
cleanup_module(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0;  i < SBNI_MAX_NUM_CARDS;  ++i) अणु
		काष्ठा net_device *dev = sbni_cards[i];
		अगर (dev != शून्य) अणु
			unरेजिस्टर_netdev(dev);
			release_region(dev->base_addr, SBNI_IO_EXTENT);
			मुक्त_netdev(dev);
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा	/* MODULE */

अटल पूर्णांक __init
sbni_setup( अक्षर  *p )
अणु
	पूर्णांक  n, parm;

	अगर( *p++ != '(' )
		जाओ  bad_param;

	क्रम( n = 0, parm = 0;  *p  &&  n < 8; ) अणु
		(*dest[ parm ])[ n ] = simple_म_से_अदीर्घ( p, &p, 0 );
		अगर( !*p  ||  *p == ')' )
			वापस 1;
		अगर( *p == ';' ) अणु
			++p;
			++n;
			parm = 0;
		पूर्ण अन्यथा अगर( *p++ != ',' ) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			अगर( ++parm >= 5 )
				अवरोध;
		पूर्ण
	पूर्ण
bad_param:
	pr_err("Error in sbni kernel parameter!\n");
	वापस 0;
पूर्ण

__setup( "sbni=", sbni_setup );

#पूर्ण_अगर	/* MODULE */

/* -------------------------------------------------------------------------- */

अटल u32
calc_crc32( u32  crc,  u8  *p,  u32  len )
अणु
	जबतक( len-- )
		crc = CRC32( *p++, crc );

	वापस  crc;
पूर्ण

अटल u32  crc32tab[] __attribute__ ((aligned(8))) = अणु
	0xD202EF8D,  0xA505DF1B,  0x3C0C8EA1,  0x4B0BBE37,
	0xD56F2B94,  0xA2681B02,  0x3B614AB8,  0x4C667A2E,
	0xDCD967BF,  0xABDE5729,  0x32D70693,  0x45D03605,
	0xDBB4A3A6,  0xACB39330,  0x35BAC28A,  0x42BDF21C,
	0xCFB5FFE9,  0xB8B2CF7F,  0x21BB9EC5,  0x56BCAE53,
	0xC8D83BF0,  0xBFDF0B66,  0x26D65ADC,  0x51D16A4A,
	0xC16E77DB,  0xB669474D,  0x2F6016F7,  0x58672661,
	0xC603B3C2,  0xB1048354,  0x280DD2EE,  0x5F0AE278,
	0xE96CCF45,  0x9E6BFFD3,  0x0762AE69,  0x70659EFF,
	0xEE010B5C,  0x99063BCA,  0x000F6A70,  0x77085AE6,
	0xE7B74777,  0x90B077E1,  0x09B9265B,  0x7EBE16CD,
	0xE0DA836E,  0x97DDB3F8,  0x0ED4E242,  0x79D3D2D4,
	0xF4DBDF21,  0x83DCEFB7,  0x1AD5BE0D,  0x6DD28E9B,
	0xF3B61B38,  0x84B12BAE,  0x1DB87A14,  0x6ABF4A82,
	0xFA005713,  0x8D076785,  0x140E363F,  0x630906A9,
	0xFD6D930A,  0x8A6AA39C,  0x1363F226,  0x6464C2B0,
	0xA4DEAE1D,  0xD3D99E8B,  0x4AD0CF31,  0x3DD7FFA7,
	0xA3B36A04,  0xD4B45A92,  0x4DBD0B28,  0x3ABA3BBE,
	0xAA05262F,  0xDD0216B9,  0x440B4703,  0x330C7795,
	0xAD68E236,  0xDA6FD2A0,  0x4366831A,  0x3461B38C,
	0xB969BE79,  0xCE6E8EEF,  0x5767DF55,  0x2060EFC3,
	0xBE047A60,  0xC9034AF6,  0x500A1B4C,  0x270D2BDA,
	0xB7B2364B,  0xC0B506DD,  0x59BC5767,  0x2EBB67F1,
	0xB0DFF252,  0xC7D8C2C4,  0x5ED1937E,  0x29D6A3E8,
	0x9FB08ED5,  0xE8B7BE43,  0x71BEEFF9,  0x06B9DF6F,
	0x98DD4ACC,  0xEFDA7A5A,  0x76D32BE0,  0x01D41B76,
	0x916B06E7,  0xE66C3671,  0x7F6567CB,  0x0862575D,
	0x9606C2FE,  0xE101F268,  0x7808A3D2,  0x0F0F9344,
	0x82079EB1,  0xF500AE27,  0x6C09FF9D,  0x1B0ECF0B,
	0x856A5AA8,  0xF26D6A3E,  0x6B643B84,  0x1C630B12,
	0x8CDC1683,  0xFBDB2615,  0x62D277AF,  0x15D54739,
	0x8BB1D29A,  0xFCB6E20C,  0x65BFB3B6,  0x12B88320,
	0x3FBA6CAD,  0x48BD5C3B,  0xD1B40D81,  0xA6B33D17,
	0x38D7A8B4,  0x4FD09822,  0xD6D9C998,  0xA1DEF90E,
	0x3161E49F,  0x4666D409,  0xDF6F85B3,  0xA868B525,
	0x360C2086,  0x410B1010,  0xD80241AA,  0xAF05713C,
	0x220D7CC9,  0x550A4C5F,  0xCC031DE5,  0xBB042D73,
	0x2560B8D0,  0x52678846,  0xCB6ED9FC,  0xBC69E96A,
	0x2CD6F4FB,  0x5BD1C46D,  0xC2D895D7,  0xB5DFA541,
	0x2BBB30E2,  0x5CBC0074,  0xC5B551CE,  0xB2B26158,
	0x04D44C65,  0x73D37CF3,  0xEADA2D49,  0x9DDD1DDF,
	0x03B9887C,  0x74BEB8EA,  0xEDB7E950,  0x9AB0D9C6,
	0x0A0FC457,  0x7D08F4C1,  0xE401A57B,  0x930695ED,
	0x0D62004E,  0x7A6530D8,  0xE36C6162,  0x946B51F4,
	0x19635C01,  0x6E646C97,  0xF76D3D2D,  0x806A0DBB,
	0x1E0E9818,  0x6909A88E,  0xF000F934,  0x8707C9A2,
	0x17B8D433,  0x60BFE4A5,  0xF9B6B51F,  0x8EB18589,
	0x10D5102A,  0x67D220BC,  0xFEDB7106,  0x89DC4190,
	0x49662D3D,  0x3E611DAB,  0xA7684C11,  0xD06F7C87,
	0x4E0BE924,  0x390CD9B2,  0xA0058808,  0xD702B89E,
	0x47BDA50F,  0x30BA9599,  0xA9B3C423,  0xDEB4F4B5,
	0x40D06116,  0x37D75180,  0xAEDE003A,  0xD9D930AC,
	0x54D13D59,  0x23D60DCF,  0xBADF5C75,  0xCDD86CE3,
	0x53BCF940,  0x24BBC9D6,  0xBDB2986C,  0xCAB5A8FA,
	0x5A0AB56B,  0x2D0D85FD,  0xB404D447,  0xC303E4D1,
	0x5D677172,  0x2A6041E4,  0xB369105E,  0xC46E20C8,
	0x72080DF5,  0x050F3D63,  0x9C066CD9,  0xEB015C4F,
	0x7565C9EC,  0x0262F97A,  0x9B6BA8C0,  0xEC6C9856,
	0x7CD385C7,  0x0BD4B551,  0x92DDE4EB,  0xE5DAD47D,
	0x7BBE41DE,  0x0CB97148,  0x95B020F2,  0xE2B71064,
	0x6FBF1D91,  0x18B82D07,  0x81B17CBD,  0xF6B64C2B,
	0x68D2D988,  0x1FD5E91E,  0x86DCB8A4,  0xF1DB8832,
	0x616495A3,  0x1663A535,  0x8F6AF48F,  0xF86DC419,
	0x660951BA,  0x110E612C,  0x88073096,  0xFF000000
पूर्ण;

