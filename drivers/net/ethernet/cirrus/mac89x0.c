<शैली गुरु>
/* mac89x0.c: A Crystal Semiconductor CS89[02]0 driver क्रम linux. */
/*
	Written 1996 by Russell Nelson, with reference to skeleton.c
	written 1993-1994 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	The author may be reached at nelson@crynwr.com, Crynwr
	Software, 11 Grant St., Potsdam, NY 13676

  Changelog:

  Mike Cruse        : mcruse@cti-ltd.com
                    : Changes क्रम Linux 2.0 compatibility.
                    : Added dev_id parameter in net_पूर्णांकerrupt(),
                    : request_irq() and मुक्त_irq(). Just शून्य क्रम now.

  Mike Cruse        : Added MOD_INC_USE_COUNT and MOD_DEC_USE_COUNT macros
                    : in net_खोलो() and net_बंद() so kerneld would know
                    : that the module is in use and wouldn't eject the
                    : driver prematurely.

  Mike Cruse        : Rewrote init_module() and cleanup_module using 8390.c
                    : as an example. Disabled स्वतःprobing in init_module(),
                    : not a good thing to करो to other devices जबतक Linux
                    : is running from all accounts.

  Alan Cox          : Removed 1.2 support, added 2.1 extra counters.

  David Huggins-Daines <dhd@debian.org>

  Split this off पूर्णांकo mac89x0.c, and gutted it of all parts which are
  not relevant to the existing CS8900 cards on the Macपूर्णांकosh
  (i.e. basically the Daynaport CS and LC cards).  To be precise:

    * Removed all the media-detection stuff, because these cards are
    TP-only.

    * Lobotomized the ISA पूर्णांकerrupt bogosity, because these cards use
    a hardwired NuBus पूर्णांकerrupt and a magic ISAIRQ value in the card.

    * Basically eliminated everything not relevant to getting the
    cards minimally functioning on the Macपूर्णांकosh.

  I might add that these cards are badly deचिन्हित even from the Mac
  standpoपूर्णांक, in that Dayna, in their infinite wisकरोm, used NuBus slot
  I/O space and NuBus पूर्णांकerrupts क्रम these cards, but neglected to
  provide anything even remotely resembling a NuBus ROM.  Thereक्रमe we
  have to probe क्रम them in a brain-damaged ISA-like fashion.

  Arnalकरो Carvalho de Melo <acme@conectiva.com.br> - 11/01/2001
  check kदो_स्मृति and release the allocated memory on failure in
  mac89x0_probe and in init_module
  use local_irq_अणुsave,restoreपूर्ण(flags) in net_get_stat, not just
  local_irq_अणुdis,enपूर्णable()
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

अटल स्थिर अक्षर version[] =
"cs89x0.c:v1.02 11/26/96 Russell Nelson <nelson@crynwr.com>\n";

#समावेश <linux/module.h>

/*
  Sources:

	Crynwr packet driver epktisa.

	Crystal Semiconductor data sheets.

*/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/nubus.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hwtest.h>
#समावेश <यंत्र/macपूर्णांकs.h>

#समावेश "cs89x0.h"

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "debug message level");

/* Inक्रमmation that need to be kept क्रम each board. */
काष्ठा net_local अणु
	पूर्णांक msg_enable;
	पूर्णांक chip_type;		/* one of: CS8900, CS8920, CS8920M */
	अक्षर chip_revision;	/* revision letter of the chip ('A'...) */
	पूर्णांक send_cmd;		/* the propercommand used to send a packet. */
	पूर्णांक rx_mode;
	पूर्णांक curr_rx_cfg;
        पूर्णांक send_underrun;      /* keep track of how many underruns in a row we get */
पूर्ण;

/* Index to functions, as function prototypes. */
अटल पूर्णांक net_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t net_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल irqवापस_t net_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);
अटल व्योम net_rx(काष्ठा net_device *dev);
अटल पूर्णांक net_बंद(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *net_get_stats(काष्ठा net_device *dev);
अटल पूर्णांक set_mac_address(काष्ठा net_device *dev, व्योम *addr);

/* For पढ़ोing/writing रेजिस्टरs ISA-style */
अटल अंतरभूत पूर्णांक
पढ़ोreg_io(काष्ठा net_device *dev, पूर्णांक portno)
अणु
	nubus_ग_लिखोw(swab16(portno), dev->base_addr + ADD_PORT);
	वापस swab16(nubus_पढ़ोw(dev->base_addr + DATA_PORT));
पूर्ण

अटल अंतरभूत व्योम
ग_लिखोreg_io(काष्ठा net_device *dev, पूर्णांक portno, पूर्णांक value)
अणु
	nubus_ग_लिखोw(swab16(portno), dev->base_addr + ADD_PORT);
	nubus_ग_लिखोw(swab16(value), dev->base_addr + DATA_PORT);
पूर्ण

/* These are क्रम पढ़ोing/writing रेजिस्टरs in shared memory */
अटल अंतरभूत पूर्णांक
पढ़ोreg(काष्ठा net_device *dev, पूर्णांक portno)
अणु
	वापस swab16(nubus_पढ़ोw(dev->mem_start + portno));
पूर्ण

अटल अंतरभूत व्योम
ग_लिखोreg(काष्ठा net_device *dev, पूर्णांक portno, पूर्णांक value)
अणु
	nubus_ग_लिखोw(swab16(value), dev->mem_start + portno);
पूर्ण

अटल स्थिर काष्ठा net_device_ops mac89x0_netdev_ops = अणु
	.nकरो_खोलो		= net_खोलो,
	.nकरो_stop		= net_बंद,
	.nकरो_start_xmit		= net_send_packet,
	.nकरो_get_stats		= net_get_stats,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address	= set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

/* Probe क्रम the CS8900 card in slot E.  We won't bother looking
   anywhere अन्यथा until we have a really good reason to करो so. */
अटल पूर्णांक mac89x0_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा net_local *lp;
	पूर्णांक i, slot;
	अचिन्हित rev_type = 0;
	अचिन्हित दीर्घ ioaddr;
	अचिन्हित लघु sig;
	पूर्णांक err = -ENODEV;
	काष्ठा nubus_rsrc *fres;

	dev = alloc_etherdev(माप(काष्ठा net_local));
	अगर (!dev)
		वापस -ENOMEM;

	/* We might have to parameterize this later */
	slot = 0xE;
	/* Get out now अगर there's a real NuBus card in slot E */
	क्रम_each_func_rsrc(fres)
		अगर (fres->board->slot == slot)
			जाओ out;

	/* The pseuकरो-ISA bits always live at offset 0x300 (gee,
           wonder why...) */
	ioaddr = (अचिन्हित दीर्घ)
		nubus_slot_addr(slot) | (((slot&0xf) << 20) + DEFAULTIOBASE);
	अणु
		पूर्णांक card_present;

		card_present = (hwreg_present((व्योम *)ioaddr + 4) &&
				hwreg_present((व्योम *)ioaddr + DATA_PORT));
		अगर (!card_present)
			जाओ out;
	पूर्ण

	nubus_ग_लिखोw(0, ioaddr + ADD_PORT);
	sig = nubus_पढ़ोw(ioaddr + DATA_PORT);
	अगर (sig != swab16(CHIP_EISA_ID_SIG))
		जाओ out;

	SET_NETDEV_DEV(dev, &pdev->dev);

	/* Initialize the net_device काष्ठाure. */
	lp = netdev_priv(dev);

	lp->msg_enable = netअगर_msg_init(debug, 0);

	/* Fill in the 'dev' fields. */
	dev->base_addr = ioaddr;
	dev->mem_start = (अचिन्हित दीर्घ)
		nubus_slot_addr(slot) | (((slot&0xf) << 20) + MMIOBASE);
	dev->mem_end = dev->mem_start + 0x1000;

	/* Turn on shared memory */
	ग_लिखोreg_io(dev, PP_BusCTL, MEMORY_ON);

	/* get the chip type */
	rev_type = पढ़ोreg(dev, PRODUCT_ID_ADD);
	lp->chip_type = rev_type &~ REVISON_BITS;
	lp->chip_revision = ((rev_type & REVISON_BITS) >> 8) + 'A';

	/* Check the chip type and revision in order to set the correct send command
	CS8920 revision C and CS8900 revision F can use the faster send. */
	lp->send_cmd = TX_AFTER_381;
	अगर (lp->chip_type == CS8900 && lp->chip_revision >= 'F')
		lp->send_cmd = TX_NOW;
	अगर (lp->chip_type != CS8900 && lp->chip_revision >= 'C')
		lp->send_cmd = TX_NOW;

	netअगर_dbg(lp, drv, dev, "%s", version);

	pr_info("cs89%c0%s rev %c found at %#8lx\n",
		lp->chip_type == CS8900 ? '0' : '2',
		lp->chip_type == CS8920M ? "M" : "",
		lp->chip_revision, dev->base_addr);

	/* Try to पढ़ो the MAC address */
	अगर ((पढ़ोreg(dev, PP_SelfST) & (EEPROM_PRESENT | EEPROM_OK)) == 0) अणु
		pr_info("No EEPROM, giving up now.\n");
		जाओ out1;
        पूर्ण अन्यथा अणु
                क्रम (i = 0; i < ETH_ALEN; i += 2) अणु
			/* Big-endian (why??!) */
			अचिन्हित लघु s = पढ़ोreg(dev, PP_IA + i);
                        dev->dev_addr[i] = s >> 8;
                        dev->dev_addr[i+1] = s & 0xff;
                पूर्ण
        पूर्ण

	dev->irq = SLOT2IRQ(slot);

	/* prपूर्णांक the IRQ and ethernet address. */

	pr_info("MAC %pM, IRQ %d\n", dev->dev_addr, dev->irq);

	dev->netdev_ops		= &mac89x0_netdev_ops;

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out1;

	platक्रमm_set_drvdata(pdev, dev);
	वापस 0;
out1:
	nubus_ग_लिखोw(0, dev->base_addr + ADD_PORT);
out:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

/* Open/initialize the board.  This is called (in the current kernel)
   someसमय after booting when the 'ifconfig' program is run.

   This routine should set everything up anew at each खोलो, even
   रेजिस्टरs that "should" only need to be set once at boot, so that
   there is non-reboot way to recover अगर something goes wrong.
   */
अटल पूर्णांक
net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	पूर्णांक i;

	/* Disable the पूर्णांकerrupt क्रम now */
	ग_लिखोreg(dev, PP_BusCTL, पढ़ोreg(dev, PP_BusCTL) & ~ENABLE_IRQ);

	/* Grab the पूर्णांकerrupt */
	अगर (request_irq(dev->irq, net_पूर्णांकerrupt, 0, "cs89x0", dev))
		वापस -EAGAIN;

	/* Set up the IRQ - Apparently magic */
	अगर (lp->chip_type == CS8900)
		ग_लिखोreg(dev, PP_CS8900_ISAINT, 0);
	अन्यथा
		ग_लिखोreg(dev, PP_CS8920_ISAINT, 0);

	/* set the Ethernet address */
	क्रम (i=0; i < ETH_ALEN/2; i++)
		ग_लिखोreg(dev, PP_IA+i*2, dev->dev_addr[i*2] | (dev->dev_addr[i*2+1] << 8));

	/* Turn on both receive and transmit operations */
	ग_लिखोreg(dev, PP_LineCTL, पढ़ोreg(dev, PP_LineCTL) | SERIAL_RX_ON | SERIAL_TX_ON);

	/* Receive only error मुक्त packets addressed to this card */
	lp->rx_mode = 0;
	ग_लिखोreg(dev, PP_RxCTL, DEF_RX_ACCEPT);

	lp->curr_rx_cfg = RX_OK_ENBL | RX_CRC_ERROR_ENBL;

	ग_लिखोreg(dev, PP_RxCFG, lp->curr_rx_cfg);

	ग_लिखोreg(dev, PP_TxCFG, TX_LOST_CRS_ENBL | TX_SQE_ERROR_ENBL | TX_OK_ENBL |
	       TX_LATE_COL_ENBL | TX_JBR_ENBL | TX_ANY_COL_ENBL | TX_16_COL_ENBL);

	ग_लिखोreg(dev, PP_BufCFG, READY_FOR_TX_ENBL | RX_MISS_COUNT_OVRFLOW_ENBL |
		 TX_COL_COUNT_OVRFLOW_ENBL | TX_UNDERRUN_ENBL);

	/* now that we've got our act together, enable everything */
	ग_लिखोreg(dev, PP_BusCTL, पढ़ोreg(dev, PP_BusCTL) | ENABLE_IRQ);
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल netdev_tx_t
net_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	netअगर_dbg(lp, tx_queued, dev, "sent %d byte packet of type %x\n",
		  skb->len, skb->data[ETH_ALEN + ETH_ALEN] << 8 |
		  skb->data[ETH_ALEN + ETH_ALEN + 1]);

	/* keep the upload from being पूर्णांकerrupted, since we
	   ask the chip to start transmitting beक्रमe the
	   whole packet has been completely uploaded. */
	local_irq_save(flags);
	netअगर_stop_queue(dev);

	/* initiate a transmit sequence */
	ग_लिखोreg(dev, PP_TxCMD, lp->send_cmd);
	ग_लिखोreg(dev, PP_TxLength, skb->len);

	/* Test to see अगर the chip has allocated memory क्रम the packet */
	अगर ((पढ़ोreg(dev, PP_BusST) & READY_FOR_TX_NOW) == 0) अणु
		/* Gasp!  It hasn't.  But that shouldn't happen since
		   we're रुकोing क्रम TxOk, so वापस 1 and requeue this packet. */
		local_irq_restore(flags);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Write the contents of the packet */
	skb_copy_from_linear_data(skb, (व्योम *)(dev->mem_start + PP_TxFrame),
				  skb->len+1);

	local_irq_restore(flags);
	dev_kमुक्त_skb (skb);

	वापस NETDEV_TX_OK;
पूर्ण

/* The typical workload of the driver:
   Handle the network पूर्णांकerface पूर्णांकerrupts. */
अटल irqवापस_t net_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा net_local *lp;
	पूर्णांक ioaddr, status;

	ioaddr = dev->base_addr;
	lp = netdev_priv(dev);

	/* we MUST पढ़ो all the events out of the ISQ, otherwise we'll never
           get पूर्णांकerrupted again.  As a consequence, we can't have any limit
           on the number of बार we loop in the पूर्णांकerrupt handler.  The
           hardware guarantees that eventually we'll run out of events.  Of
           course, अगर you're on a slow machine, and packets are arriving
           faster than you can पढ़ो them off, you're screwed.  Hasta la
           vista, baby!  */
	जबतक ((status = swab16(nubus_पढ़ोw(dev->base_addr + ISQ_PORT)))) अणु
		netअगर_dbg(lp, पूर्णांकr, dev, "status=%04x\n", status);
		चयन(status & ISQ_EVENT_MASK) अणु
		हाल ISQ_RECEIVER_EVENT:
			/* Got a packet(s). */
			net_rx(dev);
			अवरोध;
		हाल ISQ_TRANSMITTER_EVENT:
			dev->stats.tx_packets++;
			netअगर_wake_queue(dev);
			अगर ((status & TX_OK) == 0)
				dev->stats.tx_errors++;
			अगर (status & TX_LOST_CRS)
				dev->stats.tx_carrier_errors++;
			अगर (status & TX_SQE_ERROR)
				dev->stats.tx_heartbeat_errors++;
			अगर (status & TX_LATE_COL)
				dev->stats.tx_winकरोw_errors++;
			अगर (status & TX_16_COL)
				dev->stats.tx_पातed_errors++;
			अवरोध;
		हाल ISQ_BUFFER_EVENT:
			अगर (status & READY_FOR_TX) अणु
				/* we tried to transmit a packet earlier,
                                   but inexplicably ran out of buffers.
                                   That shouldn't happen since we only ever
                                   load one packet.  Shrug.  Do the right
                                   thing anyway. */
				netअगर_wake_queue(dev);
			पूर्ण
			अगर (status & TX_UNDERRUN) अणु
				netअगर_dbg(lp, tx_err, dev, "transmit underrun\n");
                                lp->send_underrun++;
                                अगर (lp->send_underrun == 3) lp->send_cmd = TX_AFTER_381;
                                अन्यथा अगर (lp->send_underrun == 6) lp->send_cmd = TX_AFTER_ALL;
                        पूर्ण
			अवरोध;
		हाल ISQ_RX_MISS_EVENT:
			dev->stats.rx_missed_errors += (status >> 6);
			अवरोध;
		हाल ISQ_TX_COL_EVENT:
			dev->stats.collisions += (status >> 6);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/* We have a good packet(s), get it/them out of the buffers. */
अटल व्योम
net_rx(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक status, length;

	status = पढ़ोreg(dev, PP_RxStatus);
	अगर ((status & RX_OK) == 0) अणु
		dev->stats.rx_errors++;
		अगर (status & RX_RUNT)
				dev->stats.rx_length_errors++;
		अगर (status & RX_EXTRA_DATA)
				dev->stats.rx_length_errors++;
		अगर ((status & RX_CRC_ERROR) &&
		    !(status & (RX_EXTRA_DATA|RX_RUNT)))
			/* per str 172 */
			dev->stats.rx_crc_errors++;
		अगर (status & RX_DRIBBLE)
				dev->stats.rx_frame_errors++;
		वापस;
	पूर्ण

	length = पढ़ोreg(dev, PP_RxLength);
	/* Malloc up new buffer. */
	skb = alloc_skb(length, GFP_ATOMIC);
	अगर (skb == शून्य) अणु
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण
	skb_put(skb, length);

	skb_copy_to_linear_data(skb, (व्योम *)(dev->mem_start + PP_RxFrame),
				length);

	netअगर_dbg(lp, rx_status, dev, "received %d byte packet of type %x\n",
		  length, skb->data[ETH_ALEN + ETH_ALEN] << 8 |
		  skb->data[ETH_ALEN + ETH_ALEN + 1]);

        skb->protocol=eth_type_trans(skb,dev);
	netअगर_rx(skb);
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += length;
पूर्ण

/* The inverse routine to net_खोलो(). */
अटल पूर्णांक
net_बंद(काष्ठा net_device *dev)
अणु

	ग_लिखोreg(dev, PP_RxCFG, 0);
	ग_लिखोreg(dev, PP_TxCFG, 0);
	ग_लिखोreg(dev, PP_BufCFG, 0);
	ग_लिखोreg(dev, PP_BusCTL, 0);

	netअगर_stop_queue(dev);

	मुक्त_irq(dev->irq, dev);

	/* Update the statistics here. */

	वापस 0;

पूर्ण

/* Get the current statistics.	This may be called with the card खोलो or
   बंदd. */
अटल काष्ठा net_device_stats *
net_get_stats(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	/* Update the statistics from the device रेजिस्टरs. */
	dev->stats.rx_missed_errors += (पढ़ोreg(dev, PP_RxMiss) >> 6);
	dev->stats.collisions += (पढ़ोreg(dev, PP_TxCol) >> 6);
	local_irq_restore(flags);

	वापस &dev->stats;
पूर्ण

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);

	अगर(dev->flags&IFF_PROMISC)
	अणु
		lp->rx_mode = RX_ALL_ACCEPT;
	पूर्ण अन्यथा अगर ((dev->flags & IFF_ALLMULTI) || !netdev_mc_empty(dev)) अणु
		/* The multicast-accept list is initialized to accept-all, and we
		   rely on higher-level filtering क्रम now. */
		lp->rx_mode = RX_MULTCAST_ACCEPT;
	पूर्ण
	अन्यथा
		lp->rx_mode = 0;

	ग_लिखोreg(dev, PP_RxCTL, DEF_RX_ACCEPT | lp->rx_mode);

	/* in promiscuous mode, we accept errored packets, so we have to enable पूर्णांकerrupts on them also */
	ग_लिखोreg(dev, PP_RxCFG, lp->curr_rx_cfg |
	     (lp->rx_mode == RX_ALL_ACCEPT? (RX_CRC_ERROR_ENBL|RX_RUNT_ENBL|RX_EXTRA_DATA_ENBL) : 0));
पूर्ण


अटल पूर्णांक set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *saddr = addr;
	पूर्णांक i;

	अगर (!is_valid_ether_addr(saddr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, saddr->sa_data, ETH_ALEN);
	netdev_info(dev, "Setting MAC address to %pM\n", dev->dev_addr);

	/* set the Ethernet address */
	क्रम (i=0; i < ETH_ALEN/2; i++)
		ग_लिखोreg(dev, PP_IA+i*2, dev->dev_addr[i*2] | (dev->dev_addr[i*2+1] << 8));

	वापस 0;
पूर्ण

MODULE_LICENSE("GPL");

अटल पूर्णांक mac89x0_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_netdev(dev);
	nubus_ग_लिखोw(0, dev->base_addr + ADD_PORT);
	मुक्त_netdev(dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mac89x0_platक्रमm_driver = अणु
	.probe = mac89x0_device_probe,
	.हटाओ = mac89x0_device_हटाओ,
	.driver = अणु
		.name = "mac89x0",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mac89x0_platक्रमm_driver);
