<शैली गुरु>
/* 8390.c: A general NS8390 ethernet driver core क्रम linux. */
/*
	Written 1992-94 by Donald Becker.

	Copyright 1993 United States Government as represented by the
	Director, National Security Agency.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403


  This is the chip-specअगरic code क्रम many 8390-based ethernet adaptors.
  This is not a complete driver, it must be combined with board-specअगरic
  code such as ne.c, wd.c, 3c503.c, etc.

  Seeing how at least eight drivers use this code, (not counting the
  PCMCIA ones either) it is easy to अवरोध some card by what seems like
  a simple innocent change. Please contact me or Donald अगर you think
  you have found something that needs changing. -- PG


  Changelog:

  Paul Gorपंचांगaker	: हटाओ set_bit lock, other cleanups.
  Paul Gorपंचांगaker	: add ei_get_8390_hdr() so we can pass skb's to
			  ei_block_input() क्रम eth_io_copy_and_sum().
  Paul Gorपंचांगaker	: exchange अटल पूर्णांक ei_pingpong क्रम a #घोषणा,
			  also add better Tx error handling.
  Paul Gorपंचांगaker	: reग_लिखो Rx overrun handling as per NS specs.
  Alexey Kuznetsov	: use the 8390's six bit hash multicast filter.
  Paul Gorपंचांगaker	: tweak ANK's above multicast changes a bit.
  Paul Gorपंचांगaker	: update packet statistics क्रम v2.1.x
  Alan Cox		: support arbitrary stupid port mappings on the
			  68K Macपूर्णांकosh. Support >16bit I/O spaces
  Paul Gorपंचांगaker	: add kmod support क्रम स्वतः-loading of the 8390
			  module by all drivers that require it.
  Alan Cox		: Spinlocking work, added 'BUG_83C690'
  Paul Gorपंचांगaker	: Separate out Tx समयout code from Tx path.
  Paul Gorपंचांगaker	: Remove old unused single Tx buffer code.
  Hayato Fujiwara	: Add m32r support.
  Paul Gorपंचांगaker	: use skb_padto() instead of stack scratch area

  Sources:
  The National Semiconductor LAN Databook, and the 3Com 3c503 databook.

  */

#समावेश <linux/build_bug.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/in.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/crc32.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>

#घोषणा NS8390_CORE
#समावेश "8390.h"

#घोषणा BUG_83C690

/* These are the operational function पूर्णांकerfaces to board-specअगरic
   routines.
	व्योम reset_8390(काष्ठा net_device *dev)
		Resets the board associated with DEV, including a hardware reset of
		the 8390.  This is only called when there is a transmit समयout, and
		it is always followed by 8390_init().
	व्योम block_output(काष्ठा net_device *dev, पूर्णांक count, स्थिर अचिन्हित अक्षर *buf,
					  पूर्णांक start_page)
		Write the COUNT bytes of BUF to the packet buffer at START_PAGE.  The
		"page" value uses the 8390's 256-byte pages.
	व्योम get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_hdr *hdr, पूर्णांक ring_page)
		Read the 4 byte, page aligned 8390 header. *If* there is a
		subsequent पढ़ो, it will be of the rest of the packet.
	व्योम block_input(काष्ठा net_device *dev, पूर्णांक count, काष्ठा sk_buff *skb, पूर्णांक ring_offset)
		Read COUNT bytes from the packet buffer पूर्णांकo the skb data area. Start
		पढ़ोing from RING_OFFSET, the address as the 8390 sees it.  This will always
		follow the पढ़ो of the 8390 header.
*/
#घोषणा ei_reset_8390 (ei_local->reset_8390)
#घोषणा ei_block_output (ei_local->block_output)
#घोषणा ei_block_input (ei_local->block_input)
#घोषणा ei_get_8390_hdr (ei_local->get_8390_hdr)

/* Index to functions. */
अटल व्योम ei_tx_पूर्णांकr(काष्ठा net_device *dev);
अटल व्योम ei_tx_err(काष्ठा net_device *dev);
अटल व्योम ei_receive(काष्ठा net_device *dev);
अटल व्योम ei_rx_overrun(काष्ठा net_device *dev);

/* Routines generic to NS8390-based boards. */
अटल व्योम NS8390_trigger_send(काष्ठा net_device *dev, अचिन्हित पूर्णांक length,
								पूर्णांक start_page);
अटल व्योम करो_set_multicast_list(काष्ठा net_device *dev);
अटल व्योम __NS8390_init(काष्ठा net_device *dev, पूर्णांक startp);

अटल अचिन्हित version_prपूर्णांकed;
अटल पूर्णांक msg_enable;
अटल स्थिर पूर्णांक शेष_msg_level = (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_RX_ERR |
				     NETIF_MSG_TX_ERR);
module_param(msg_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(msg_enable, "Debug message level (see linux/netdevice.h for bitmap)");

/*
 *	SMP and the 8390 setup.
 *
 *	The 8390 isn't exactly deचिन्हित to be multithपढ़ोed on RX/TX. There is
 *	a page रेजिस्टर that controls bank and packet buffer access. We guard
 *	this with ei_local->page_lock. Nobody should assume or set the page other
 *	than zero when the lock is not held. Lock holders must restore page 0
 *	beक्रमe unlocking. Even pure पढ़ोers must take the lock to protect in
 *	page 0.
 *
 *	To make lअगरe dअगरficult the chip can also be very slow. We thereक्रमe can't
 *	just use spinlocks. For the दीर्घer lockups we disable the irq the device
 *	sits on and hold the lock. We must hold the lock because there is a dual
 *	processor हाल other than पूर्णांकerrupts (get stats/set multicast list in
 *	parallel with each other and transmit).
 *
 *	Note: in theory we can just disable the irq on the card _but_ there is
 *	a latency on SMP irq delivery. So we can easily go "disable irq" "sync irqs"
 *	enter lock, take the queued irq. So we waddle instead of flying.
 *
 *	Finally by special arrangement क्रम the purpose of being generally
 *	annoying the transmit function is called bh atomic. That places
 *	restrictions on the user context callers as disable_irq won't save
 *	them.
 *
 *	Additional explanation of problems with locking by Alan Cox:
 *
 *	"The author (me) didn't use spin_lock_irqsave because the slowness of the
 *	card means that approach caused horrible problems like losing serial data
 *	at 38400 baud on some chips. Remember many 8390 nics on PCI were ISA
 *	chips with FPGA front ends.
 *
 *	Ok the logic behind the 8390 is very simple:
 *
 *	Things to know
 *		- IRQ delivery is asynchronous to the PCI bus
 *		- Blocking the local CPU IRQ via spin locks was too slow
 *		- The chip has रेजिस्टर winकरोws needing locking work
 *
 *	So the path was once (I say once as people appear to have changed it
 *	in the mean समय and it now looks rather bogus अगर the changes to use
 *	disable_irq_nosync_irqsave are disabling the local IRQ)
 *
 *
 *		Take the page lock
 *		Mask the IRQ on chip
 *		Disable the IRQ (but not mask locally- someone seems to have
 *			broken this with the lock validator stuff)
 *			[This must be _nosync as the page lock may otherwise
 *				deadlock us]
 *		Drop the page lock and turn IRQs back on
 *
 *		At this poपूर्णांक an existing IRQ may still be running but we can't
 *		get a new one
 *
 *		Take the lock (so we know the IRQ has terminated) but करोn't mask
 *	the IRQs on the processor
 *		Set irqlock [क्रम debug]
 *
 *		Transmit (slow as ****)
 *
 *		re-enable the IRQ
 *
 *
 *	We have to use disable_irq because otherwise you will get delayed
 *	पूर्णांकerrupts on the APIC bus deadlocking the transmit path.
 *
 *	Quite hairy but the chip simply wasn't designed for SMP and you can't
 *	even ACK an पूर्णांकerrupt without risking corrupting other parallel
 *	activities on the chip." [lkml, 25 Jul 2007]
 */



/**
 * ei_खोलो - Open/initialize the board.
 * @dev: network device to initialize
 *
 * This routine goes all-out, setting everything
 * up anew at each खोलो, even though many of these रेजिस्टरs should only
 * need to be set once at boot.
 */
अटल पूर्णांक __ei_खोलो(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	अगर (dev->watchकरोg_समयo <= 0)
		dev->watchकरोg_समयo = TX_TIMEOUT;

	/*
	 *	Grab the page lock so we own the रेजिस्टर set, then call
	 *	the init function.
	 */

	spin_lock_irqsave(&ei_local->page_lock, flags);
	__NS8390_init(dev, 1);
	/* Set the flag beक्रमe we drop the lock, That way the IRQ arrives
	   after its set and we get no silly warnings */
	netअगर_start_queue(dev);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);
	ei_local->irqlock = 0;
	वापस 0;
पूर्ण

/**
 * ei_बंद - shut करोwn network device
 * @dev: network device to बंद
 *
 * Opposite of ei_खोलो(). Only used when "ifconfig <devname> down" is करोne.
 */
अटल पूर्णांक __ei_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	/*
	 *	Hold the page lock during बंद
	 */

	spin_lock_irqsave(&ei_local->page_lock, flags);
	__NS8390_init(dev, 0);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

/**
 * ei_tx_समयout - handle transmit समय out condition
 * @dev: network device which has apparently fallen asleep
 *
 * Called by kernel when device never acknowledges a transmit has
 * completed (or failed) - i.e. never posted a Tx related पूर्णांकerrupt.
 */

अटल व्योम __ei_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	अचिन्हित दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	पूर्णांक txsr, isr, tickssofar = jअगरfies - dev_trans_start(dev);
	अचिन्हित दीर्घ flags;

	dev->stats.tx_errors++;

	spin_lock_irqsave(&ei_local->page_lock, flags);
	txsr = ei_inb(e8390_base+EN0_TSR);
	isr = ei_inb(e8390_base+EN0_ISR);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);

	netdev_dbg(dev, "Tx timed out, %s TSR=%#2x, ISR=%#2x, t=%d\n",
		   (txsr & ENTSR_ABT) ? "excess collisions." :
		   (isr) ? "lost interrupt?" : "cable problem?",
		   txsr, isr, tickssofar);

	अगर (!isr && !dev->stats.tx_packets) अणु
		/* The 8390 probably hasn't gotten on the cable yet. */
		ei_local->पूर्णांकerface_num ^= 1;   /* Try a dअगरferent xcvr.  */
	पूर्ण

	/* Ugly but a reset can be slow, yet must be रक्षित */

	disable_irq_nosync_lockdep(dev->irq);
	spin_lock(&ei_local->page_lock);

	/* Try to restart the card.  Perhaps the user has fixed something. */
	ei_reset_8390(dev);
	__NS8390_init(dev, 1);

	spin_unlock(&ei_local->page_lock);
	enable_irq_lockdep(dev->irq);
	netअगर_wake_queue(dev);
पूर्ण

/**
 * ei_start_xmit - begin packet transmission
 * @skb: packet to be sent
 * @dev: network device to which packet is sent
 *
 * Sends a packet to an 8390 network device.
 */

अटल netdev_tx_t __ei_start_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	पूर्णांक send_length = skb->len, output_page;
	अचिन्हित दीर्घ flags;
	अक्षर buf[ETH_ZLEN];
	अक्षर *data = skb->data;

	अगर (skb->len < ETH_ZLEN) अणु
		स_रखो(buf, 0, ETH_ZLEN);	/* more efficient than करोing just the needed bits */
		स_नकल(buf, data, skb->len);
		send_length = ETH_ZLEN;
		data = buf;
	पूर्ण

	/* Mask पूर्णांकerrupts from the ethercard.
	   SMP: We have to grab the lock here otherwise the IRQ handler
	   on another CPU can flip winकरोw and race the IRQ mask set. We end
	   up trashing the mcast filter not disabling irqs अगर we करोn't lock */

	spin_lock_irqsave(&ei_local->page_lock, flags);
	ei_outb_p(0x00, e8390_base + EN0_IMR);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);


	/*
	 *	Slow phase with lock held.
	 */

	disable_irq_nosync_lockdep_irqsave(dev->irq, &flags);

	spin_lock(&ei_local->page_lock);

	ei_local->irqlock = 1;

	/*
	 * We have two Tx slots available क्रम use. Find the first मुक्त
	 * slot, and then perक्रमm some sanity checks. With two Tx bufs,
	 * you get very बंद to transmitting back-to-back packets. With
	 * only one Tx buf, the transmitter sits idle जबतक you reload the
	 * card, leaving a substantial gap between each transmitted packet.
	 */

	अगर (ei_local->tx1 == 0) अणु
		output_page = ei_local->tx_start_page;
		ei_local->tx1 = send_length;
		अगर ((netअगर_msg_tx_queued(ei_local)) &&
		    ei_local->tx2 > 0)
			netdev_dbg(dev,
				   "idle transmitter tx2=%d, lasttx=%d, txing=%d\n",
				   ei_local->tx2, ei_local->lasttx, ei_local->txing);
	पूर्ण अन्यथा अगर (ei_local->tx2 == 0) अणु
		output_page = ei_local->tx_start_page + TX_PAGES/2;
		ei_local->tx2 = send_length;
		अगर ((netअगर_msg_tx_queued(ei_local)) &&
		    ei_local->tx1 > 0)
			netdev_dbg(dev,
				   "idle transmitter, tx1=%d, lasttx=%d, txing=%d\n",
				   ei_local->tx1, ei_local->lasttx, ei_local->txing);
	पूर्ण अन्यथा अणु			/* We should never get here. */
		netअगर_dbg(ei_local, tx_err, dev,
			  "No Tx buffers free! tx1=%d tx2=%d last=%d\n",
			  ei_local->tx1, ei_local->tx2, ei_local->lasttx);
		ei_local->irqlock = 0;
		netअगर_stop_queue(dev);
		ei_outb_p(ENISR_ALL, e8390_base + EN0_IMR);
		spin_unlock(&ei_local->page_lock);
		enable_irq_lockdep_irqrestore(dev->irq, &flags);
		dev->stats.tx_errors++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/*
	 * Okay, now upload the packet and trigger a send अगर the transmitter
	 * isn't alपढ़ोy sending. If it is busy, the पूर्णांकerrupt handler will
	 * trigger the send later, upon receiving a Tx करोne पूर्णांकerrupt.
	 */

	ei_block_output(dev, send_length, data, output_page);

	अगर (!ei_local->txing) अणु
		ei_local->txing = 1;
		NS8390_trigger_send(dev, send_length, output_page);
		अगर (output_page == ei_local->tx_start_page) अणु
			ei_local->tx1 = -1;
			ei_local->lasttx = -1;
		पूर्ण अन्यथा अणु
			ei_local->tx2 = -1;
			ei_local->lasttx = -2;
		पूर्ण
	पूर्ण अन्यथा
		ei_local->txqueue++;

	अगर (ei_local->tx1 && ei_local->tx2)
		netअगर_stop_queue(dev);
	अन्यथा
		netअगर_start_queue(dev);

	/* Turn 8390 पूर्णांकerrupts back on. */
	ei_local->irqlock = 0;
	ei_outb_p(ENISR_ALL, e8390_base + EN0_IMR);

	spin_unlock(&ei_local->page_lock);
	enable_irq_lockdep_irqrestore(dev->irq, &flags);
	skb_tx_बारtamp(skb);
	dev_consume_skb_any(skb);
	dev->stats.tx_bytes += send_length;

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * ei_पूर्णांकerrupt - handle the पूर्णांकerrupts from an 8390
 * @irq: पूर्णांकerrupt number
 * @dev_id: a poपूर्णांकer to the net_device
 *
 * Handle the ether पूर्णांकerface पूर्णांकerrupts. We pull packets from
 * the 8390 via the card specअगरic functions and fire them at the networking
 * stack. We also handle transmit completions and wake the transmit path अगर
 * necessary. We also update the counters and करो other housekeeping as
 * needed.
 */

अटल irqवापस_t __ei_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	अचिन्हित दीर्घ e8390_base = dev->base_addr;
	पूर्णांक पूर्णांकerrupts, nr_serviced = 0;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	/*
	 *	Protect the irq test too.
	 */

	spin_lock(&ei_local->page_lock);

	अगर (ei_local->irqlock) अणु
		/*
		 * This might just be an पूर्णांकerrupt क्रम a PCI device sharing
		 * this line
		 */
		netdev_err(dev, "Interrupted while interrupts are masked! isr=%#2x imr=%#2x\n",
			   ei_inb_p(e8390_base + EN0_ISR),
			   ei_inb_p(e8390_base + EN0_IMR));
		spin_unlock(&ei_local->page_lock);
		वापस IRQ_NONE;
	पूर्ण

	/* Change to page 0 and पढ़ो the पूर्णांकr status reg. */
	ei_outb_p(E8390_NODMA+E8390_PAGE0, e8390_base + E8390_CMD);
	netअगर_dbg(ei_local, पूर्णांकr, dev, "interrupt(isr=%#2.2x)\n",
		  ei_inb_p(e8390_base + EN0_ISR));

	/* !!Assumption!! -- we stay in page 0.	 Don't अवरोध this. */
	जबतक ((पूर्णांकerrupts = ei_inb_p(e8390_base + EN0_ISR)) != 0 &&
	       ++nr_serviced < MAX_SERVICE) अणु
		अगर (!netअगर_running(dev)) अणु
			netdev_warn(dev, "interrupt from stopped card\n");
			/* rmk - acknowledge the पूर्णांकerrupts */
			ei_outb_p(पूर्णांकerrupts, e8390_base + EN0_ISR);
			पूर्णांकerrupts = 0;
			अवरोध;
		पूर्ण
		अगर (पूर्णांकerrupts & ENISR_OVER)
			ei_rx_overrun(dev);
		अन्यथा अगर (पूर्णांकerrupts & (ENISR_RX+ENISR_RX_ERR)) अणु
			/* Got a good (?) packet. */
			ei_receive(dev);
		पूर्ण
		/* Push the next to-transmit packet through. */
		अगर (पूर्णांकerrupts & ENISR_TX)
			ei_tx_पूर्णांकr(dev);
		अन्यथा अगर (पूर्णांकerrupts & ENISR_TX_ERR)
			ei_tx_err(dev);

		अगर (पूर्णांकerrupts & ENISR_COUNTERS) अणु
			dev->stats.rx_frame_errors += ei_inb_p(e8390_base + EN0_COUNTER0);
			dev->stats.rx_crc_errors   += ei_inb_p(e8390_base + EN0_COUNTER1);
			dev->stats.rx_missed_errors += ei_inb_p(e8390_base + EN0_COUNTER2);
			ei_outb_p(ENISR_COUNTERS, e8390_base + EN0_ISR); /* Ack पूर्णांकr. */
		पूर्ण

		/* Ignore any RDC पूर्णांकerrupts that make it back to here. */
		अगर (पूर्णांकerrupts & ENISR_RDC)
			ei_outb_p(ENISR_RDC, e8390_base + EN0_ISR);

		ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, e8390_base + E8390_CMD);
	पूर्ण

	अगर (पूर्णांकerrupts && (netअगर_msg_पूर्णांकr(ei_local))) अणु
		ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, e8390_base + E8390_CMD);
		अगर (nr_serviced >= MAX_SERVICE) अणु
			/* 0xFF is valid क्रम a card removal */
			अगर (पूर्णांकerrupts != 0xFF)
				netdev_warn(dev, "Too much work at interrupt, status %#2.2x\n",
					    पूर्णांकerrupts);
			ei_outb_p(ENISR_ALL, e8390_base + EN0_ISR); /* Ack. most पूर्णांकrs. */
		पूर्ण अन्यथा अणु
			netdev_warn(dev, "unknown interrupt %#2x\n", पूर्णांकerrupts);
			ei_outb_p(0xff, e8390_base + EN0_ISR); /* Ack. all पूर्णांकrs. */
		पूर्ण
	पूर्ण
	spin_unlock(&ei_local->page_lock);
	वापस IRQ_RETVAL(nr_serviced > 0);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम __ei_poll(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	__ei_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

/**
 * ei_tx_err - handle transmitter error
 * @dev: network device which threw the exception
 *
 * A transmitter error has happened. Most likely excess collisions (which
 * is a fairly normal condition). If the error is one where the Tx will
 * have been पातed, we try and send another one right away, instead of
 * letting the failed packet sit and collect dust in the Tx buffer. This
 * is a much better solution as it aव्योमs kernel based Tx समयouts, and
 * an unnecessary card reset.
 *
 * Called with lock held.
 */

अटल व्योम ei_tx_err(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ e8390_base = dev->base_addr;
	/* ei_local is used on some platक्रमms via the EI_SHIFT macro */
	काष्ठा ei_device *ei_local __maybe_unused = netdev_priv(dev);
	अचिन्हित अक्षर txsr = ei_inb_p(e8390_base+EN0_TSR);
	अचिन्हित अक्षर tx_was_पातed = txsr & (ENTSR_ABT+ENTSR_FU);

#अगर_घोषित VERBOSE_ERROR_DUMP
	netdev_dbg(dev, "transmitter error (%#2x):", txsr);
	अगर (txsr & ENTSR_ABT)
		pr_cont(" excess-collisions ");
	अगर (txsr & ENTSR_ND)
		pr_cont(" non-deferral ");
	अगर (txsr & ENTSR_CRS)
		pr_cont(" lost-carrier ");
	अगर (txsr & ENTSR_FU)
		pr_cont(" FIFO-underrun ");
	अगर (txsr & ENTSR_CDH)
		pr_cont(" lost-heartbeat ");
	pr_cont("\n");
#पूर्ण_अगर

	ei_outb_p(ENISR_TX_ERR, e8390_base + EN0_ISR); /* Ack पूर्णांकr. */

	अगर (tx_was_पातed)
		ei_tx_पूर्णांकr(dev);
	अन्यथा अणु
		dev->stats.tx_errors++;
		अगर (txsr & ENTSR_CRS)
			dev->stats.tx_carrier_errors++;
		अगर (txsr & ENTSR_CDH)
			dev->stats.tx_heartbeat_errors++;
		अगर (txsr & ENTSR_OWC)
			dev->stats.tx_winकरोw_errors++;
	पूर्ण
पूर्ण

/**
 * ei_tx_पूर्णांकr - transmit पूर्णांकerrupt handler
 * @dev: network device क्रम which tx पूर्णांकr is handled
 *
 * We have finished a transmit: check क्रम errors and then trigger the next
 * packet to be sent. Called with lock held.
 */

अटल व्योम ei_tx_पूर्णांकr(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	पूर्णांक status = ei_inb(e8390_base + EN0_TSR);

	ei_outb_p(ENISR_TX, e8390_base + EN0_ISR); /* Ack पूर्णांकr. */

	/*
	 * There are two Tx buffers, see which one finished, and trigger
	 * the send of another one अगर it exists.
	 */
	ei_local->txqueue--;

	अगर (ei_local->tx1 < 0) अणु
		अगर (ei_local->lasttx != 1 && ei_local->lasttx != -1)
			pr_err("%s: bogus last_tx_buffer %d, tx1=%d\n",
			       ei_local->name, ei_local->lasttx, ei_local->tx1);
		ei_local->tx1 = 0;
		अगर (ei_local->tx2 > 0) अणु
			ei_local->txing = 1;
			NS8390_trigger_send(dev, ei_local->tx2, ei_local->tx_start_page + 6);
			netअगर_trans_update(dev);
			ei_local->tx2 = -1;
			ei_local->lasttx = 2;
		पूर्ण अन्यथा अणु
			ei_local->lasttx = 20;
			ei_local->txing = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (ei_local->tx2 < 0) अणु
		अगर (ei_local->lasttx != 2  &&  ei_local->lasttx != -2)
			pr_err("%s: bogus last_tx_buffer %d, tx2=%d\n",
			       ei_local->name, ei_local->lasttx, ei_local->tx2);
		ei_local->tx2 = 0;
		अगर (ei_local->tx1 > 0) अणु
			ei_local->txing = 1;
			NS8390_trigger_send(dev, ei_local->tx1, ei_local->tx_start_page);
			netअगर_trans_update(dev);
			ei_local->tx1 = -1;
			ei_local->lasttx = 1;
		पूर्ण अन्यथा अणु
			ei_local->lasttx = 10;
			ei_local->txing = 0;
		पूर्ण
	पूर्ण /* अन्यथा
		netdev_warn(dev, "unexpected TX-done interrupt, lasttx=%d\n",
			    ei_local->lasttx);
*/

	/* Minimize Tx latency: update the statistics after we restart TXing. */
	अगर (status & ENTSR_COL)
		dev->stats.collisions++;
	अगर (status & ENTSR_PTX)
		dev->stats.tx_packets++;
	अन्यथा अणु
		dev->stats.tx_errors++;
		अगर (status & ENTSR_ABT) अणु
			dev->stats.tx_पातed_errors++;
			dev->stats.collisions += 16;
		पूर्ण
		अगर (status & ENTSR_CRS)
			dev->stats.tx_carrier_errors++;
		अगर (status & ENTSR_FU)
			dev->stats.tx_fअगरo_errors++;
		अगर (status & ENTSR_CDH)
			dev->stats.tx_heartbeat_errors++;
		अगर (status & ENTSR_OWC)
			dev->stats.tx_winकरोw_errors++;
	पूर्ण
	netअगर_wake_queue(dev);
पूर्ण

/**
 * ei_receive - receive some packets
 * @dev: network device with which receive will be run
 *
 * We have a good packet(s), get it/them out of the buffers.
 * Called with lock held.
 */

अटल व्योम ei_receive(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	अचिन्हित अक्षर rxing_page, this_frame, next_frame;
	अचिन्हित लघु current_offset;
	पूर्णांक rx_pkt_count = 0;
	काष्ठा e8390_pkt_hdr rx_frame;
	पूर्णांक num_rx_pages = ei_local->stop_page-ei_local->rx_start_page;

	जबतक (++rx_pkt_count < 10) अणु
		पूर्णांक pkt_len, pkt_stat;

		/* Get the rx page (incoming packet poपूर्णांकer). */
		ei_outb_p(E8390_NODMA+E8390_PAGE1, e8390_base + E8390_CMD);
		rxing_page = ei_inb_p(e8390_base + EN1_CURPAG);
		ei_outb_p(E8390_NODMA+E8390_PAGE0, e8390_base + E8390_CMD);

		/* Remove one frame from the ring.  Boundary is always a page behind. */
		this_frame = ei_inb_p(e8390_base + EN0_BOUNDARY) + 1;
		अगर (this_frame >= ei_local->stop_page)
			this_frame = ei_local->rx_start_page;

		/* Someday we'll omit the previous, अगरf we never get this message.
		   (There is at least one clone claimed to have a problem.)

		   Keep quiet अगर it looks like a card removal. One problem here
		   is that some clones crash in roughly the same way.
		 */
		अगर ((netअगर_msg_rx_status(ei_local)) &&
		    this_frame != ei_local->current_page &&
		    (this_frame != 0x0 || rxing_page != 0xFF))
			netdev_err(dev,
				   "mismatched read page pointers %2x vs %2x\n",
				   this_frame, ei_local->current_page);

		अगर (this_frame == rxing_page)	/* Read all the frames? */
			अवरोध;				/* Done क्रम now */

		current_offset = this_frame << 8;
		ei_get_8390_hdr(dev, &rx_frame, this_frame);

		pkt_len = rx_frame.count - माप(काष्ठा e8390_pkt_hdr);
		pkt_stat = rx_frame.status;

		next_frame = this_frame + 1 + ((pkt_len+4)>>8);

		/* Check क्रम bogosity warned by 3c503 book: the status byte is never
		   written.  This happened a lot during testing! This code should be
		   cleaned up someday. */
		अगर (rx_frame.next != next_frame &&
		    rx_frame.next != next_frame + 1 &&
		    rx_frame.next != next_frame - num_rx_pages &&
		    rx_frame.next != next_frame + 1 - num_rx_pages) अणु
			ei_local->current_page = rxing_page;
			ei_outb(ei_local->current_page-1, e8390_base+EN0_BOUNDARY);
			dev->stats.rx_errors++;
			जारी;
		पूर्ण

		अगर (pkt_len < 60  ||  pkt_len > 1518) अणु
			netअगर_dbg(ei_local, rx_status, dev,
				  "bogus packet size: %d, status=%#2x nxpg=%#2x\n",
				  rx_frame.count, rx_frame.status,
				  rx_frame.next);
			dev->stats.rx_errors++;
			dev->stats.rx_length_errors++;
		पूर्ण अन्यथा अगर ((pkt_stat & 0x0F) == ENRSR_RXOK) अणु
			काष्ठा sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 2);
			अगर (skb == शून्य) अणु
				netअगर_err(ei_local, rx_err, dev,
					  "Couldn't allocate a sk_buff of size %d\n",
					  pkt_len);
				dev->stats.rx_dropped++;
				अवरोध;
			पूर्ण अन्यथा अणु
				skb_reserve(skb, 2);	/* IP headers on 16 byte boundaries */
				skb_put(skb, pkt_len);	/* Make room */
				ei_block_input(dev, pkt_len, skb, current_offset + माप(rx_frame));
				skb->protocol = eth_type_trans(skb, dev);
				अगर (!skb_defer_rx_बारtamp(skb))
					netअगर_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
				अगर (pkt_stat & ENRSR_PHY)
					dev->stats.multicast++;
			पूर्ण
		पूर्ण अन्यथा अणु
			netअगर_err(ei_local, rx_err, dev,
				  "bogus packet: status=%#2x nxpg=%#2x size=%d\n",
				  rx_frame.status, rx_frame.next,
				  rx_frame.count);
			dev->stats.rx_errors++;
			/* NB: The NIC counts CRC, frame and missed errors. */
			अगर (pkt_stat & ENRSR_FO)
				dev->stats.rx_fअगरo_errors++;
		पूर्ण
		next_frame = rx_frame.next;

		/* This _should_ never happen: it's here क्रम aव्योमing bad clones. */
		अगर (next_frame >= ei_local->stop_page) अणु
			netdev_notice(dev, "next frame inconsistency, %#2x\n",
				      next_frame);
			next_frame = ei_local->rx_start_page;
		पूर्ण
		ei_local->current_page = next_frame;
		ei_outb_p(next_frame-1, e8390_base+EN0_BOUNDARY);
	पूर्ण

	/* We used to also ack ENISR_OVER here, but that would someबार mask
	   a real overrun, leaving the 8390 in a stopped state with rec'vr off. */
	ei_outb_p(ENISR_RX+ENISR_RX_ERR, e8390_base+EN0_ISR);
पूर्ण

/**
 * ei_rx_overrun - handle receiver overrun
 * @dev: network device which threw exception
 *
 * We have a receiver overrun: we have to kick the 8390 to get it started
 * again. Problem is that you have to kick it exactly as NS prescribes in
 * the updated datasheets, or "the NIC may act in an unpredictable manner."
 * This includes causing "the NIC to defer indefinitely when it is stopped
 * on a busy network."  Ugh.
 * Called with lock held. Don't call this with the पूर्णांकerrupts off or your
 * computer will hate you - it takes 10ms or so.
 */

अटल व्योम ei_rx_overrun(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ e8390_base = dev->base_addr;
	अचिन्हित अक्षर was_txing, must_resend = 0;
	/* ei_local is used on some platक्रमms via the EI_SHIFT macro */
	काष्ठा ei_device *ei_local __maybe_unused = netdev_priv(dev);

	/*
	 * Record whether a Tx was in progress and then issue the
	 * stop command.
	 */
	was_txing = ei_inb_p(e8390_base+E8390_CMD) & E8390_TRANS;
	ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD);

	netअगर_dbg(ei_local, rx_err, dev, "Receiver overrun\n");
	dev->stats.rx_over_errors++;

	/*
	 * Wait a full Tx समय (1.2ms) + some guard समय, NS says 1.6ms total.
	 * Early datasheets said to poll the reset bit, but now they say that
	 * it "is not a reliable indicator and subsequently should be ignored."
	 * We रुको at least 10ms.
	 */

	mdelay(10);

	/*
	 * Reset RBCR[01] back to zero as per magic incantation.
	 */
	ei_outb_p(0x00, e8390_base+EN0_RCNTLO);
	ei_outb_p(0x00, e8390_base+EN0_RCNTHI);

	/*
	 * See अगर any Tx was पूर्णांकerrupted or not. According to NS, this
	 * step is vital, and skipping it will cause no end of havoc.
	 */

	अगर (was_txing) अणु
		अचिन्हित अक्षर tx_completed = ei_inb_p(e8390_base+EN0_ISR) & (ENISR_TX+ENISR_TX_ERR);
		अगर (!tx_completed)
			must_resend = 1;
	पूर्ण

	/*
	 * Have to enter loopback mode and then restart the NIC beक्रमe
	 * you are allowed to slurp packets up off the ring.
	 */
	ei_outb_p(E8390_TXOFF, e8390_base + EN0_TXCR);
	ei_outb_p(E8390_NODMA + E8390_PAGE0 + E8390_START, e8390_base + E8390_CMD);

	/*
	 * Clear the Rx ring of all the debris, and ack the पूर्णांकerrupt.
	 */
	ei_receive(dev);
	ei_outb_p(ENISR_OVER, e8390_base+EN0_ISR);

	/*
	 * Leave loopback mode, and resend any packet that got stopped.
	 */
	ei_outb_p(E8390_TXCONFIG, e8390_base + EN0_TXCR);
	अगर (must_resend)
		ei_outb_p(E8390_NODMA + E8390_PAGE0 + E8390_START + E8390_TRANS, e8390_base + E8390_CMD);
पूर्ण

/*
 *	Collect the stats. This is called unlocked and from several contexts.
 */

अटल काष्ठा net_device_stats *__ei_get_stats(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ ioaddr = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	/* If the card is stopped, just वापस the present stats. */
	अगर (!netअगर_running(dev))
		वापस &dev->stats;

	spin_lock_irqsave(&ei_local->page_lock, flags);
	/* Read the counter रेजिस्टरs, assuming we are in page 0. */
	dev->stats.rx_frame_errors  += ei_inb_p(ioaddr + EN0_COUNTER0);
	dev->stats.rx_crc_errors    += ei_inb_p(ioaddr + EN0_COUNTER1);
	dev->stats.rx_missed_errors += ei_inb_p(ioaddr + EN0_COUNTER2);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);

	वापस &dev->stats;
पूर्ण

/*
 * Form the 64 bit 8390 multicast table from the linked list of addresses
 * associated with this dev काष्ठाure.
 */

अटल अंतरभूत व्योम make_mc_bits(u8 *bits, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;

	netdev_क्रम_each_mc_addr(ha, dev) अणु
		u32 crc = ether_crc(ETH_ALEN, ha->addr);
		/*
		 * The 8390 uses the 6 most signअगरicant bits of the
		 * CRC to index the multicast table.
		 */
		bits[crc>>29] |= (1<<((crc>>26)&7));
	पूर्ण
पूर्ण

/**
 * करो_set_multicast_list - set/clear multicast filter
 * @dev: net device क्रम which multicast filter is adjusted
 *
 *	Set or clear the multicast filter क्रम this adaptor. May be called
 *	from a BH in 2.1.x. Must be called with lock held.
 */

अटल व्योम करो_set_multicast_list(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ e8390_base = dev->base_addr;
	पूर्णांक i;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	अगर (!(dev->flags&(IFF_PROMISC|IFF_ALLMULTI))) अणु
		स_रखो(ei_local->mcfilter, 0, 8);
		अगर (!netdev_mc_empty(dev))
			make_mc_bits(ei_local->mcfilter, dev);
	पूर्ण अन्यथा
		स_रखो(ei_local->mcfilter, 0xFF, 8);	/* mcast set to accept-all */

	/*
	 * DP8390 manuals करोn't specअगरy any magic sequence क्रम altering
	 * the multicast regs on an alपढ़ोy running card. To be safe, we
	 * ensure multicast mode is off prior to loading up the new hash
	 * table. If this proves to be not enough, we can always resort
	 * to stopping the NIC, loading the table and then restarting.
	 *
	 * Bug Alert!  The MC regs on the SMC 83C690 (SMC Elite and SMC
	 * Elite16) appear to be ग_लिखो-only. The NS 8390 data sheet lists
	 * them as r/w so this is a bug.  The SMC 83C790 (SMC Ultra and
	 * Ultra32 EISA) appears to have this bug fixed.
	 */

	अगर (netअगर_running(dev))
		ei_outb_p(E8390_RXCONFIG, e8390_base + EN0_RXCR);
	ei_outb_p(E8390_NODMA + E8390_PAGE1, e8390_base + E8390_CMD);
	क्रम (i = 0; i < 8; i++) अणु
		ei_outb_p(ei_local->mcfilter[i], e8390_base + EN1_MULT_SHIFT(i));
#अगर_अघोषित BUG_83C690
		अगर (ei_inb_p(e8390_base + EN1_MULT_SHIFT(i)) != ei_local->mcfilter[i])
			netdev_err(dev, "Multicast filter read/write mismap %d\n",
				   i);
#पूर्ण_अगर
	पूर्ण
	ei_outb_p(E8390_NODMA + E8390_PAGE0, e8390_base + E8390_CMD);

	अगर (dev->flags&IFF_PROMISC)
		ei_outb_p(E8390_RXCONFIG | 0x18, e8390_base + EN0_RXCR);
	अन्यथा अगर (dev->flags & IFF_ALLMULTI || !netdev_mc_empty(dev))
		ei_outb_p(E8390_RXCONFIG | 0x08, e8390_base + EN0_RXCR);
	अन्यथा
		ei_outb_p(E8390_RXCONFIG, e8390_base + EN0_RXCR);
पूर्ण

/*
 *	Called without lock held. This is invoked from user context and may
 *	be parallel to just about everything अन्यथा. Its also fairly quick and
 *	not called too often. Must protect against both bh and irq users
 */

अटल व्योम __ei_set_multicast_list(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	spin_lock_irqsave(&ei_local->page_lock, flags);
	करो_set_multicast_list(dev);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);
पूर्ण

/**
 * ethdev_setup - init rest of 8390 device काष्ठा
 * @dev: network device काष्ठाure to init
 *
 * Initialize the rest of the 8390 device काष्ठाure.  Do NOT __init
 * this, as it is used by 8390 based modular drivers too.
 */

अटल व्योम ethdev_setup(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	ether_setup(dev);

	spin_lock_init(&ei_local->page_lock);

	ei_local->msg_enable = netअगर_msg_init(msg_enable, शेष_msg_level);

	अगर (netअगर_msg_drv(ei_local) && (version_prपूर्णांकed++ == 0))
		pr_info("%s", version);
पूर्ण

/**
 * alloc_ei_netdev - alloc_etherdev counterpart क्रम 8390
 * @size: extra bytes to allocate
 *
 * Allocate 8390-specअगरic net_device.
 */
अटल काष्ठा net_device *____alloc_ei_netdev(पूर्णांक size)
अणु
	वापस alloc_netdev(माप(काष्ठा ei_device) + size, "eth%d",
			    NET_NAME_UNKNOWN, ethdev_setup);
पूर्ण




/* This page of functions should be 8390 generic */
/* Follow National Semi's recommendations क्रम initializing the "NIC". */

/**
 * NS8390_init - initialize 8390 hardware
 * @dev: network device to initialize
 * @startp: boolean.  non-zero value to initiate chip processing
 *
 *	Must be called with lock held.
 */

अटल व्योम __NS8390_init(काष्ठा net_device *dev, पूर्णांक startp)
अणु
	अचिन्हित दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
	पूर्णांक i;
	पूर्णांक endcfg = ei_local->word16
	    ? (0x48 | ENDCFG_WTS | (ei_local->bigendian ? ENDCFG_BOS : 0))
	    : 0x48;

	BUILD_BUG_ON(माप(काष्ठा e8390_pkt_hdr) != 4);
	/* Follow National Semi's recommendations क्रम initing the DP83902. */
	ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD); /* 0x21 */
	ei_outb_p(endcfg, e8390_base + EN0_DCFG);	/* 0x48 or 0x49 */
	/* Clear the remote byte count रेजिस्टरs. */
	ei_outb_p(0x00,  e8390_base + EN0_RCNTLO);
	ei_outb_p(0x00,  e8390_base + EN0_RCNTHI);
	/* Set to monitor and loopback mode -- this is vital!. */
	ei_outb_p(E8390_RXOFF, e8390_base + EN0_RXCR); /* 0x20 */
	ei_outb_p(E8390_TXOFF, e8390_base + EN0_TXCR); /* 0x02 */
	/* Set the transmit page and receive ring. */
	ei_outb_p(ei_local->tx_start_page, e8390_base + EN0_TPSR);
	ei_local->tx1 = ei_local->tx2 = 0;
	ei_outb_p(ei_local->rx_start_page, e8390_base + EN0_STARTPG);
	ei_outb_p(ei_local->stop_page-1, e8390_base + EN0_BOUNDARY);	/* 3c503 says 0x3f,NS0x26*/
	ei_local->current_page = ei_local->rx_start_page;		/* निश्चित boundary+1 */
	ei_outb_p(ei_local->stop_page, e8390_base + EN0_STOPPG);
	/* Clear the pending पूर्णांकerrupts and mask. */
	ei_outb_p(0xFF, e8390_base + EN0_ISR);
	ei_outb_p(0x00,  e8390_base + EN0_IMR);

	/* Copy the station address पूर्णांकo the DS8390 रेजिस्टरs. */

	ei_outb_p(E8390_NODMA + E8390_PAGE1 + E8390_STOP, e8390_base+E8390_CMD); /* 0x61 */
	क्रम (i = 0; i < 6; i++) अणु
		ei_outb_p(dev->dev_addr[i], e8390_base + EN1_PHYS_SHIFT(i));
		अगर ((netअगर_msg_probe(ei_local)) &&
		    ei_inb_p(e8390_base + EN1_PHYS_SHIFT(i)) != dev->dev_addr[i])
			netdev_err(dev,
				   "Hw. address read/write mismap %d\n", i);
	पूर्ण

	ei_outb_p(ei_local->rx_start_page, e8390_base + EN1_CURPAG);
	ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD);

	ei_local->tx1 = ei_local->tx2 = 0;
	ei_local->txing = 0;

	अगर (startp) अणु
		ei_outb_p(0xff,  e8390_base + EN0_ISR);
		ei_outb_p(ENISR_ALL,  e8390_base + EN0_IMR);
		ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, e8390_base+E8390_CMD);
		ei_outb_p(E8390_TXCONFIG, e8390_base + EN0_TXCR); /* xmit on. */
		/* 3c503 TechMan says rxconfig only after the NIC is started. */
		ei_outb_p(E8390_RXCONFIG, e8390_base + EN0_RXCR); /* rx on,  */
		करो_set_multicast_list(dev);	/* (re)load the mcast table */
	पूर्ण
पूर्ण

/* Trigger a transmit start, assuming the length is valid.
   Always called with the page lock held */

अटल व्योम NS8390_trigger_send(काष्ठा net_device *dev, अचिन्हित पूर्णांक length,
								पूर्णांक start_page)
अणु
	अचिन्हित दीर्घ e8390_base = dev->base_addr;
	काष्ठा ei_device *ei_local __attribute((unused)) = netdev_priv(dev);

	ei_outb_p(E8390_NODMA+E8390_PAGE0, e8390_base+E8390_CMD);

	अगर (ei_inb_p(e8390_base + E8390_CMD) & E8390_TRANS) अणु
		netdev_warn(dev, "trigger_send() called with the transmitter busy\n");
		वापस;
	पूर्ण
	ei_outb_p(length & 0xff, e8390_base + EN0_TCNTLO);
	ei_outb_p(length >> 8, e8390_base + EN0_TCNTHI);
	ei_outb_p(start_page, e8390_base + EN0_TPSR);
	ei_outb_p(E8390_NODMA+E8390_TRANS+E8390_START, e8390_base+E8390_CMD);
पूर्ण
