<शैली गुरु>
/* atp.c: Attached (pocket) ethernet adapter driver क्रम linux. */
/*
	This is a driver क्रम commonly OEM pocket (parallel port)
	ethernet adapters based on the Realtek RTL8002 and RTL8012 chips.

	Written 1993-2000 by Donald Becker.

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	Copyright 1993 United States Government as represented by the Director,
	National Security Agency.  Copyright 1994-2000 retained by the original
	author, Donald Becker. The समयr-based reset code was supplied in 1995
	by Bill Carlson, wwc@super.org.

	The author may be reached as becker@scyld.com, or C/O
	Scyld Computing Corporation
	410 Severn Ave., Suite 210
	Annapolis MD 21403

	Support inक्रमmation and updates available at
	http://www.scyld.com/network/atp.hपंचांगl


	Modular support/softnet added by Alan Cox.
	_bit abuse fixed up by Alan Cox

*/

अटल स्थिर अक्षर version[] =
"atp.c:v1.09=ac 2002/10/01 Donald Becker <becker@scyld.com>\n";

/* The user-configurable values.
   These may be modअगरied when a driver module is loaded.*/

अटल पूर्णांक debug = 1; 			/* 1 normal messages, 0 quiet .. 7 verbose. */
#घोषणा net_debug debug

/* Maximum events (Rx packets, etc.) to handle at each पूर्णांकerrupt. */
अटल पूर्णांक max_पूर्णांकerrupt_work = 15;

#घोषणा NUM_UNITS 2
/* The standard set of ISA module parameters. */
अटल पूर्णांक io[NUM_UNITS];
अटल पूर्णांक irq[NUM_UNITS];
अटल पूर्णांक xcvr[NUM_UNITS]; 			/* The data transfer mode. */

/* Operational parameters that are set at compile समय. */

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (400*HZ/1000)

/*
	This file is a device driver क्रम the RealTek (aka AT-Lan-Tec) pocket
	ethernet adapter.  This is a common low-cost OEM pocket ethernet
	adapter, sold under many names.

  Sources:
	This driver was written from the packet driver assembly code provided by
	Vincent Bono of AT-Lan-Tec.	 Ever try to figure out how a complicated
	device works just from the assembly code?  It ain't pretty.  The following
	description is written based on guesses and writing lots of special-purpose
	code to test my theorized operation.

	In 1997 Realtek made available the करोcumentation क्रम the second generation
	RTL8012 chip, which has lead to several driver improvements.
	  http://www.realtek.com.tw/

					Theory of Operation

	The RTL8002 adapter seems to be built around a custom spin of the SEEQ
	controller core.  It probably has a 16K or 64K पूर्णांकernal packet buffer, of
	which the first 4K is devoted to transmit and the rest to receive.
	The controller मुख्यtains the queue of received packet and the packet buffer
	access poपूर्णांकer पूर्णांकernally, with only 'reset to beginning' and 'skip to next
	packet' commands visible.  The transmit packet queue holds two (or more?)
	packets: both 'retransmit this packet' (due to collision) and 'transmit next
	packet' commands must be started by hand.

	The station address is stored in a standard bit-serial EEPROM which must be
	पढ़ो (ughh) by the device driver.  (Provisions have been made क्रम
	substituting a 74S288 PROM, but I haven't gotten reports of any models
	using it.)  Unlike built-in devices, a pocket adapter can temporarily lose
	घातer without indication to the device driver.  The major effect is that
	the station address, receive filter (promiscuous, etc.) and transceiver
	must be reset.

	The controller itself has 16 रेजिस्टरs, some of which use only the lower
	bits.  The रेजिस्टरs are पढ़ो and written 4 bits at a समय.  The four bit
	रेजिस्टर address is presented on the data lines aदीर्घ with a few additional
	timing and control bits.  The data is then पढ़ो from status port or written
	to the data port.

	Correction: the controller has two banks of 16 रेजिस्टरs.  The second
	bank contains only the multicast filter table (now used) and the EEPROM
	access रेजिस्टरs.

	Since the bulk data transfer of the actual packets through the slow
	parallel port करोminates the driver's running समय, four distinct data
	(non-रेजिस्टर) transfer modes are provided by the adapter, two in each
	direction.  In the first mode timing क्रम the nibble transfers is
	provided through the data port.  In the second mode the same timing is
	provided through the control port.  In either हाल the data is पढ़ो from
	the status port and written to the data port, just as it is accessing
	रेजिस्टरs.

	In addition to the basic data transfer methods, several more are modes are
	created by adding some delay by करोing multiple पढ़ोs of the data to allow
	it to stabilize.  This delay seems to be needed on most machines.

	The data transfer mode is stored in the 'dev->if_port' field.  Its शेष
	value is '4'.  It may be overridden at boot-समय using the third parameter
	to the "ether=..." initialization.

	The header file <atp.h> provides अंतरभूत functions that encapsulate the
	रेजिस्टर and data access methods.  These functions are hand-tuned to
	generate reasonable object code.  This header file also करोcuments my
	पूर्णांकerpretations of the device रेजिस्टरs.
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/crc32.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#समावेश "atp.h"

MODULE_AUTHOR("Donald Becker <becker@scyld.com>");
MODULE_DESCRIPTION("RealTek RTL8002/8012 parallel port Ethernet driver");
MODULE_LICENSE("GPL");

module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
module_param(debug, पूर्णांक, 0);
module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
module_param_array(xcvr, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(max_पूर्णांकerrupt_work, "ATP maximum events handled per interrupt");
MODULE_PARM_DESC(debug, "ATP debug level (0-7)");
MODULE_PARM_DESC(io, "ATP I/O base address(es)");
MODULE_PARM_DESC(irq, "ATP IRQ number(s)");
MODULE_PARM_DESC(xcvr, "ATP transceiver(s) (0=internal, 1=external)");

/* The number of low I/O ports used by the ethercard. */
#घोषणा ETHERCARD_TOTAL_SIZE	3

/* Sequence to चयन an 8012 from prपूर्णांकer mux to ethernet mode. */
अटल अक्षर mux_8012[] = अणु 0xff, 0xf7, 0xff, 0xfb, 0xf3, 0xfb, 0xff, 0xf7,पूर्ण;

काष्ठा net_local अणु
    spinlock_t lock;
    काष्ठा net_device *next_module;
    काष्ठा समयr_list समयr;	/* Media selection समयr. */
    काष्ठा net_device *dev;	/* Timer dev. */
    अचिन्हित दीर्घ last_rx_समय;	/* Last Rx, in jअगरfies, to handle Rx hang. */
    पूर्णांक saved_tx_size;
    अचिन्हित पूर्णांक tx_unit_busy:1;
    अचिन्हित अक्षर re_tx,	/* Number of packet retransmissions. */
		addr_mode,		/* Current Rx filter e.g. promiscuous, etc. */
		pac_cnt_in_tx_buf;
पूर्ण;

/* This code, written by wwc@super.org, resets the adapter every
   TIMED_CHECKER ticks.  This recovers from an unknown error which
   hangs the device. */
#घोषणा TIMED_CHECKER (HZ/4)
#अगर_घोषित TIMED_CHECKER
#समावेश <linux/समयr.h>
अटल व्योम atp_समयd_checker(काष्ठा समयr_list *t);
#पूर्ण_अगर

/* Index to functions, as function prototypes. */

अटल पूर्णांक atp_probe1(दीर्घ ioaddr);
अटल व्योम get_node_ID(काष्ठा net_device *dev);
अटल अचिन्हित लघु eeprom_op(दीर्घ ioaddr, अचिन्हित पूर्णांक cmd);
अटल पूर्णांक net_खोलो(काष्ठा net_device *dev);
अटल व्योम hardware_init(काष्ठा net_device *dev);
अटल व्योम ग_लिखो_packet(दीर्घ ioaddr, पूर्णांक length, अचिन्हित अक्षर *packet, पूर्णांक pad, पूर्णांक mode);
अटल व्योम trigger_send(दीर्घ ioaddr, पूर्णांक length);
अटल netdev_tx_t atp_send_packet(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev);
अटल irqवापस_t atp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल व्योम net_rx(काष्ठा net_device *dev);
अटल व्योम पढ़ो_block(दीर्घ ioaddr, पूर्णांक length, अचिन्हित अक्षर *buffer, पूर्णांक data_mode);
अटल पूर्णांक net_बंद(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल व्योम tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);


/* A list of all installed ATP devices, क्रम removing the driver module. */
अटल काष्ठा net_device *root_atp_dev;

/* Check क्रम a network adapter of this type, and वापस '0' अगरf one exists.
   If dev->base_addr == 0, probe all likely locations.
   If dev->base_addr == 1, always वापस failure.
   If dev->base_addr == 2, allocate space क्रम the device and वापस success
   (detachable devices only).

   FIXME: we should use the parport layer क्रम this
   */
अटल पूर्णांक __init atp_init(व्योम)
अणु
	पूर्णांक *port, ports[] = अणु0x378, 0x278, 0x3bc, 0पूर्ण;
	पूर्णांक base_addr = io[0];

	अगर (base_addr > 0x1ff)		/* Check a single specअगरied location. */
		वापस atp_probe1(base_addr);
	अन्यथा अगर (base_addr == 1)	/* Don't probe at all. */
		वापस -ENXIO;

	क्रम (port = ports; *port; port++) अणु
		दीर्घ ioaddr = *port;
		outb(0x57, ioaddr + PAR_DATA);
		अगर (inb(ioaddr + PAR_DATA) != 0x57)
			जारी;
		अगर (atp_probe1(ioaddr) == 0)
			वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा net_device_ops atp_netdev_ops = अणु
	.nकरो_खोलो		= net_खोलो,
	.nकरो_stop		= net_बंद,
	.nकरो_start_xmit		= atp_send_packet,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_tx_समयout		= tx_समयout,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक __init atp_probe1(दीर्घ ioaddr)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा net_local *lp;
	पूर्णांक saved_ctrl_reg, status, i;
	पूर्णांक res;

	outb(0xff, ioaddr + PAR_DATA);
	/* Save the original value of the Control रेजिस्टर, in हाल we guessed
	   wrong. */
	saved_ctrl_reg = inb(ioaddr + PAR_CONTROL);
	अगर (net_debug > 3)
		prपूर्णांकk("atp: Control register was %#2.2x.\n", saved_ctrl_reg);
	/* IRQEN=0, SLCTB=high INITB=high, AUTOFDB=high, STBB=high. */
	outb(0x04, ioaddr + PAR_CONTROL);
#अगर_अघोषित final_version
	अगर (net_debug > 3) अणु
		/* Turn off the prपूर्णांकer multiplexer on the 8012. */
		क्रम (i = 0; i < 8; i++)
			outb(mux_8012[i], ioaddr + PAR_DATA);
		ग_लिखो_reg(ioaddr, MODSEL, 0x00);
		prपूर्णांकk("atp: Registers are ");
		क्रम (i = 0; i < 32; i++)
			prपूर्णांकk(" %2.2x", पढ़ो_nibble(ioaddr, i));
		prपूर्णांकk(".\n");
	पूर्ण
#पूर्ण_अगर
	/* Turn off the prपूर्णांकer multiplexer on the 8012. */
	क्रम (i = 0; i < 8; i++)
		outb(mux_8012[i], ioaddr + PAR_DATA);
	ग_लिखो_reg_high(ioaddr, CMR1, CMR1h_RESET);
	/* udelay() here? */
	status = पढ़ो_nibble(ioaddr, CMR1);

	अगर (net_debug > 3) अणु
		prपूर्णांकk(KERN_DEBUG "atp: Status nibble was %#2.2x..", status);
		क्रम (i = 0; i < 32; i++)
			prपूर्णांकk(" %2.2x", पढ़ो_nibble(ioaddr, i));
		prपूर्णांकk("\n");
	पूर्ण

	अगर ((status & 0x78) != 0x08) अणु
		/* The pocket adapter probe failed, restore the control रेजिस्टर. */
		outb(saved_ctrl_reg, ioaddr + PAR_CONTROL);
		वापस -ENODEV;
	पूर्ण
	status = पढ़ो_nibble(ioaddr, CMR2_h);
	अगर ((status & 0x78) != 0x10) अणु
		outb(saved_ctrl_reg, ioaddr + PAR_CONTROL);
		वापस -ENODEV;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा net_local));
	अगर (!dev)
		वापस -ENOMEM;

	/* Find the IRQ used by triggering an पूर्णांकerrupt. */
	ग_लिखो_reg_byte(ioaddr, CMR2, 0x01);			/* No accept mode, IRQ out. */
	ग_लिखो_reg_high(ioaddr, CMR1, CMR1h_RxENABLE | CMR1h_TxENABLE);	/* Enable Tx and Rx. */

	/* Omit स्वतःIRQ routine क्रम now. Use "table lookup" instead.  Uhgggh. */
	अगर (irq[0])
		dev->irq = irq[0];
	अन्यथा अगर (ioaddr == 0x378)
		dev->irq = 7;
	अन्यथा
		dev->irq = 5;
	ग_लिखो_reg_high(ioaddr, CMR1, CMR1h_TxRxOFF); /* Disable Tx and Rx units. */
	ग_लिखो_reg(ioaddr, CMR2, CMR2_शून्य);

	dev->base_addr = ioaddr;

	/* Read the station address PROM.  */
	get_node_ID(dev);

#अगर_अघोषित MODULE
	अगर (net_debug)
		prपूर्णांकk(KERN_INFO "%s", version);
#पूर्ण_अगर

	prपूर्णांकk(KERN_NOTICE "%s: Pocket adapter found at %#3lx, IRQ %d, "
	       "SAPROM %pM.\n",
	       dev->name, dev->base_addr, dev->irq, dev->dev_addr);

	/* Reset the ethernet hardware and activate the prपूर्णांकer pass-through. */
	ग_लिखो_reg_high(ioaddr, CMR1, CMR1h_RESET | CMR1h_MUX);

	lp = netdev_priv(dev);
	lp->addr_mode = CMR2h_Normal;
	spin_lock_init(&lp->lock);

	/* For the ATP adapter the "if_port" is really the data transfer mode. */
	अगर (xcvr[0])
		dev->अगर_port = xcvr[0];
	अन्यथा
		dev->अगर_port = (dev->mem_start & 0xf) ? (dev->mem_start & 0x7) : 4;
	अगर (dev->mem_end & 0xf)
		net_debug = dev->mem_end & 7;

	dev->netdev_ops 	= &atp_netdev_ops;
	dev->watchकरोg_समयo	= TX_TIMEOUT;

	res = रेजिस्टर_netdev(dev);
	अगर (res) अणु
		मुक्त_netdev(dev);
		वापस res;
	पूर्ण

	lp->next_module = root_atp_dev;
	root_atp_dev = dev;

	वापस 0;
पूर्ण

/* Read the station address PROM, usually a word-wide EEPROM. */
अटल व्योम __init get_node_ID(काष्ठा net_device *dev)
अणु
	दीर्घ ioaddr = dev->base_addr;
	पूर्णांक sa_offset = 0;
	पूर्णांक i;

	ग_लिखो_reg(ioaddr, CMR2, CMR2_EEPROM);	  /* Poपूर्णांक to the EEPROM control रेजिस्टरs. */

	/* Some adapters have the station address at offset 15 instead of offset
	   zero.  Check क्रम it, and fix it अगर needed. */
	अगर (eeprom_op(ioaddr, EE_READ(0)) == 0xffff)
		sa_offset = 15;

	क्रम (i = 0; i < 3; i++)
		((__be16 *)dev->dev_addr)[i] =
			cpu_to_be16(eeprom_op(ioaddr, EE_READ(sa_offset + i)));

	ग_लिखो_reg(ioaddr, CMR2, CMR2_शून्य);
पूर्ण

/*
  An EEPROM पढ़ो command starts by shअगरting out 0x60+address, and then
  shअगरting in the serial data. See the NatSemi databook क्रम details.
 *		   ________________
 * CS : __|
 *			   ___	   ___
 * CLK: ______|	  |___|	  |
 *		 __ _______ _______
 * DI :	 __X_______X_______X
 * DO :	 _________X_______X
 */

अटल अचिन्हित लघु __init eeprom_op(दीर्घ ioaddr, u32 cmd)
अणु
	अचिन्हित eedata_out = 0;
	पूर्णांक num_bits = EE_CMD_SIZE;

	जबतक (--num_bits >= 0) अणु
		अक्षर outval = (cmd & (1<<num_bits)) ? EE_DATA_WRITE : 0;
		ग_लिखो_reg_high(ioaddr, PROM_CMD, outval | EE_CLK_LOW);
		ग_लिखो_reg_high(ioaddr, PROM_CMD, outval | EE_CLK_HIGH);
		eedata_out <<= 1;
		अगर (पढ़ो_nibble(ioaddr, PROM_DATA) & EE_DATA_READ)
			eedata_out++;
	पूर्ण
	ग_लिखो_reg_high(ioaddr, PROM_CMD, EE_CLK_LOW & ~EE_CS);
	वापस eedata_out;
पूर्ण


/* Open/initialize the board.  This is called (in the current kernel)
   someसमय after booting when the 'ifconfig' program is run.

   This routine sets everything up anew at each खोलो, even
   रेजिस्टरs that "should" only need to be set once at boot, so that
   there is non-reboot way to recover अगर something goes wrong.

   This is an attachable device: अगर there is no निजी entry then it wasn't
   probed क्रम at boot-समय, and we need to probe क्रम it again.
   */
अटल पूर्णांक net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	पूर्णांक ret;

	/* The पूर्णांकerrupt line is turned off (tri-stated) when the device isn't in
	   use.  That's especially important क्रम "attached" पूर्णांकerfaces where the
	   port or पूर्णांकerrupt may be shared. */
	ret = request_irq(dev->irq, atp_पूर्णांकerrupt, 0, dev->name, dev);
	अगर (ret)
		वापस ret;

	hardware_init(dev);

	lp->dev = dev;
	समयr_setup(&lp->समयr, atp_समयd_checker, 0);
	lp->समयr.expires = jअगरfies + TIMED_CHECKER;
	add_समयr(&lp->समयr);

	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

/* This routine resets the hardware.  We initialize everything, assuming that
   the hardware may have been temporarily detached. */
अटल व्योम hardware_init(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	दीर्घ ioaddr = dev->base_addr;
	पूर्णांक i;

	/* Turn off the prपूर्णांकer multiplexer on the 8012. */
	क्रम (i = 0; i < 8; i++)
		outb(mux_8012[i], ioaddr + PAR_DATA);
	ग_लिखो_reg_high(ioaddr, CMR1, CMR1h_RESET);

	क्रम (i = 0; i < 6; i++)
		ग_लिखो_reg_byte(ioaddr, PAR0 + i, dev->dev_addr[i]);

	ग_लिखो_reg_high(ioaddr, CMR2, lp->addr_mode);

	अगर (net_debug > 2) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Reset: current Rx mode %d.\n", dev->name,
			   (पढ़ो_nibble(ioaddr, CMR2_h) >> 3) & 0x0f);
	पूर्ण

	ग_लिखो_reg(ioaddr, CMR2, CMR2_IRQOUT);
	ग_लिखो_reg_high(ioaddr, CMR1, CMR1h_RxENABLE | CMR1h_TxENABLE);

	/* Enable the पूर्णांकerrupt line from the serial port. */
	outb(Ctrl_SelData + Ctrl_IRQEN, ioaddr + PAR_CONTROL);

	/* Unmask the पूर्णांकeresting पूर्णांकerrupts. */
	ग_लिखो_reg(ioaddr, IMR, ISR_RxOK | ISR_TxErr | ISR_TxOK);
	ग_लिखो_reg_high(ioaddr, IMR, ISRh_RxErr);

	lp->tx_unit_busy = 0;
	lp->pac_cnt_in_tx_buf = 0;
	lp->saved_tx_size = 0;
पूर्ण

अटल व्योम trigger_send(दीर्घ ioaddr, पूर्णांक length)
अणु
	ग_लिखो_reg_byte(ioaddr, TxCNT0, length & 0xff);
	ग_लिखो_reg(ioaddr, TxCNT1, length >> 8);
	ग_लिखो_reg(ioaddr, CMR1, CMR1_Xmit);
पूर्ण

अटल व्योम ग_लिखो_packet(दीर्घ ioaddr, पूर्णांक length, अचिन्हित अक्षर *packet, पूर्णांक pad_len, पूर्णांक data_mode)
अणु
    अगर (length & 1)
    अणु
    	length++;
    	pad_len++;
    पूर्ण

    outb(EOC+MAR, ioaddr + PAR_DATA);
    अगर ((data_mode & 1) == 0) अणु
		/* Write the packet out, starting with the ग_लिखो addr. */
		outb(WrAddr+MAR, ioaddr + PAR_DATA);
		करो अणु
			ग_लिखो_byte_mode0(ioaddr, *packet++);
		पूर्ण जबतक (--length > pad_len) ;
		करो अणु
			ग_लिखो_byte_mode0(ioaddr, 0);
		पूर्ण जबतक (--length > 0) ;
    पूर्ण अन्यथा अणु
		/* Write the packet out in slow mode. */
		अचिन्हित अक्षर outbyte = *packet++;

		outb(Ctrl_LNibWrite + Ctrl_IRQEN, ioaddr + PAR_CONTROL);
		outb(WrAddr+MAR, ioaddr + PAR_DATA);

		outb((outbyte & 0x0f)|0x40, ioaddr + PAR_DATA);
		outb(outbyte & 0x0f, ioaddr + PAR_DATA);
		outbyte >>= 4;
		outb(outbyte & 0x0f, ioaddr + PAR_DATA);
		outb(Ctrl_HNibWrite + Ctrl_IRQEN, ioaddr + PAR_CONTROL);
		जबतक (--length > pad_len)
			ग_लिखो_byte_mode1(ioaddr, *packet++);
		जबतक (--length > 0)
			ग_लिखो_byte_mode1(ioaddr, 0);
    पूर्ण
    /* Terminate the Tx frame.  End of ग_लिखो: ECB. */
    outb(0xff, ioaddr + PAR_DATA);
    outb(Ctrl_HNibWrite | Ctrl_SelData | Ctrl_IRQEN, ioaddr + PAR_CONTROL);
पूर्ण

अटल व्योम tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	दीर्घ ioaddr = dev->base_addr;

	prपूर्णांकk(KERN_WARNING "%s: Transmit timed out, %s?\n", dev->name,
		   inb(ioaddr + PAR_CONTROL) & 0x10 ? "network cable problem"
		   :  "IRQ conflict");
	dev->stats.tx_errors++;
	/* Try to restart the adapter. */
	hardware_init(dev);
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
	dev->stats.tx_errors++;
पूर्ण

अटल netdev_tx_t atp_send_packet(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	दीर्घ ioaddr = dev->base_addr;
	पूर्णांक length;
	अचिन्हित दीर्घ flags;

	length = ETH_ZLEN < skb->len ? skb->len : ETH_ZLEN;

	netअगर_stop_queue(dev);

	/* Disable पूर्णांकerrupts by writing 0x00 to the Interrupt Mask Register.
	   This sequence must not be पूर्णांकerrupted by an incoming packet. */

	spin_lock_irqsave(&lp->lock, flags);
	ग_लिखो_reg(ioaddr, IMR, 0);
	ग_लिखो_reg_high(ioaddr, IMR, 0);
	spin_unlock_irqrestore(&lp->lock, flags);

	ग_लिखो_packet(ioaddr, length, skb->data, length-skb->len, dev->अगर_port);

	lp->pac_cnt_in_tx_buf++;
	अगर (lp->tx_unit_busy == 0) अणु
		trigger_send(ioaddr, length);
		lp->saved_tx_size = 0; 				/* Redundant */
		lp->re_tx = 0;
		lp->tx_unit_busy = 1;
	पूर्ण अन्यथा
		lp->saved_tx_size = length;
	/* Re-enable the LPT पूर्णांकerrupts. */
	ग_लिखो_reg(ioaddr, IMR, ISR_RxOK | ISR_TxErr | ISR_TxOK);
	ग_लिखो_reg_high(ioaddr, IMR, ISRh_RxErr);

	dev_kमुक्त_skb (skb);
	वापस NETDEV_TX_OK;
पूर्ण


/* The typical workload of the driver:
   Handle the network पूर्णांकerface पूर्णांकerrupts. */
अटल irqवापस_t atp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा net_local *lp;
	दीर्घ ioaddr;
	अटल पूर्णांक num_tx_since_rx;
	पूर्णांक boguscount = max_पूर्णांकerrupt_work;
	पूर्णांक handled = 0;

	ioaddr = dev->base_addr;
	lp = netdev_priv(dev);

	spin_lock(&lp->lock);

	/* Disable additional spurious पूर्णांकerrupts. */
	outb(Ctrl_SelData, ioaddr + PAR_CONTROL);

	/* The adapter's output is currently the IRQ line, चयन it to data. */
	ग_लिखो_reg(ioaddr, CMR2, CMR2_शून्य);
	ग_लिखो_reg(ioaddr, IMR, 0);

	अगर (net_debug > 5)
		prपूर्णांकk(KERN_DEBUG "%s: In interrupt ", dev->name);
	जबतक (--boguscount > 0) अणु
		पूर्णांक status = पढ़ो_nibble(ioaddr, ISR);
		अगर (net_debug > 5)
			prपूर्णांकk("loop status %02x..", status);

		अगर (status & (ISR_RxOK<<3)) अणु
			handled = 1;
			ग_लिखो_reg(ioaddr, ISR, ISR_RxOK); /* Clear the Rx पूर्णांकerrupt. */
			करो अणु
				पूर्णांक पढ़ो_status = पढ़ो_nibble(ioaddr, CMR1);
				अगर (net_debug > 6)
					prपूर्णांकk("handling Rx packet %02x..", पढ़ो_status);
				/* We acknowledged the normal Rx पूर्णांकerrupt, so अगर the पूर्णांकerrupt
				   is still outstanding we must have a Rx error. */
				अगर (पढ़ो_status & (CMR1_IRQ << 3)) अणु /* Overrun. */
					dev->stats.rx_over_errors++;
					/* Set to no-accept mode दीर्घ enough to हटाओ a packet. */
					ग_लिखो_reg_high(ioaddr, CMR2, CMR2h_OFF);
					net_rx(dev);
					/* Clear the पूर्णांकerrupt and वापस to normal Rx mode. */
					ग_लिखो_reg_high(ioaddr, ISR, ISRh_RxErr);
					ग_लिखो_reg_high(ioaddr, CMR2, lp->addr_mode);
				पूर्ण अन्यथा अगर ((पढ़ो_status & (CMR1_BufEnb << 3)) == 0) अणु
					net_rx(dev);
					num_tx_since_rx = 0;
				पूर्ण अन्यथा
					अवरोध;
			पूर्ण जबतक (--boguscount > 0);
		पूर्ण अन्यथा अगर (status & ((ISR_TxErr + ISR_TxOK)<<3)) अणु
			handled = 1;
			अगर (net_debug > 6)
				prपूर्णांकk("handling Tx done..");
			/* Clear the Tx पूर्णांकerrupt.  We should check क्रम too many failures
			   and reinitialize the adapter. */
			ग_लिखो_reg(ioaddr, ISR, ISR_TxErr + ISR_TxOK);
			अगर (status & (ISR_TxErr<<3)) अणु
				dev->stats.collisions++;
				अगर (++lp->re_tx > 15) अणु
					dev->stats.tx_पातed_errors++;
					hardware_init(dev);
					अवरोध;
				पूर्ण
				/* Attempt to retransmit. */
				अगर (net_debug > 6)  prपूर्णांकk("attempting to ReTx");
				ग_लिखो_reg(ioaddr, CMR1, CMR1_ReXmit + CMR1_Xmit);
			पूर्ण अन्यथा अणु
				/* Finish up the transmit. */
				dev->stats.tx_packets++;
				lp->pac_cnt_in_tx_buf--;
				अगर ( lp->saved_tx_size) अणु
					trigger_send(ioaddr, lp->saved_tx_size);
					lp->saved_tx_size = 0;
					lp->re_tx = 0;
				पूर्ण अन्यथा
					lp->tx_unit_busy = 0;
				netअगर_wake_queue(dev);	/* Inक्रमm upper layers. */
			पूर्ण
			num_tx_since_rx++;
		पूर्ण अन्यथा अगर (num_tx_since_rx > 8 &&
			   समय_after(jअगरfies, lp->last_rx_समय + HZ)) अणु
			अगर (net_debug > 2)
				prपूर्णांकk(KERN_DEBUG "%s: Missed packet? No Rx after %d Tx and "
					   "%ld jiffies status %02x  CMR1 %02x.\n", dev->name,
					   num_tx_since_rx, jअगरfies - lp->last_rx_समय, status,
					   (पढ़ो_nibble(ioaddr, CMR1) >> 3) & 15);
			dev->stats.rx_missed_errors++;
			hardware_init(dev);
			num_tx_since_rx = 0;
			अवरोध;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	/* This following code fixes a rare (and very dअगरficult to track करोwn)
	   problem where the adapter क्रममाला_लो its ethernet address. */
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < 6; i++)
			ग_लिखो_reg_byte(ioaddr, PAR0 + i, dev->dev_addr[i]);
#अगर 0 && defined(TIMED_CHECKER)
		mod_समयr(&lp->समयr, jअगरfies + TIMED_CHECKER);
#पूर्ण_अगर
	पूर्ण

	/* Tell the adapter that it can go back to using the output line as IRQ. */
	ग_लिखो_reg(ioaddr, CMR2, CMR2_IRQOUT);
	/* Enable the physical पूर्णांकerrupt line, which is sure to be low until.. */
	outb(Ctrl_SelData + Ctrl_IRQEN, ioaddr + PAR_CONTROL);
	/* .. we enable the पूर्णांकerrupt sources. */
	ग_लिखो_reg(ioaddr, IMR, ISR_RxOK | ISR_TxErr | ISR_TxOK);
	ग_लिखो_reg_high(ioaddr, IMR, ISRh_RxErr); 			/* Hmmm, really needed? */

	spin_unlock(&lp->lock);

	अगर (net_debug > 5) prपूर्णांकk("exiting interrupt.\n");
	वापस IRQ_RETVAL(handled);
पूर्ण

#अगर_घोषित TIMED_CHECKER
/* This following code fixes a rare (and very dअगरficult to track करोwn)
   problem where the adapter क्रममाला_लो its ethernet address. */
अटल व्योम atp_समयd_checker(काष्ठा समयr_list *t)
अणु
	काष्ठा net_local *lp = from_समयr(lp, t, समयr);
	काष्ठा net_device *dev = lp->dev;
	दीर्घ ioaddr = dev->base_addr;
	पूर्णांक tickssofar = jअगरfies - lp->last_rx_समय;
	पूर्णांक i;

	spin_lock(&lp->lock);
	अगर (tickssofar > 2*HZ) अणु
#अगर 1
		क्रम (i = 0; i < 6; i++)
			ग_लिखो_reg_byte(ioaddr, PAR0 + i, dev->dev_addr[i]);
		lp->last_rx_समय = jअगरfies;
#अन्यथा
		क्रम (i = 0; i < 6; i++)
			अगर (पढ़ो_cmd_byte(ioaddr, PAR0 + i) != atp_समयd_dev->dev_addr[i])
				अणु
			काष्ठा net_local *lp = netdev_priv(atp_समयd_dev);
			ग_लिखो_reg_byte(ioaddr, PAR0 + i, atp_समयd_dev->dev_addr[i]);
			अगर (i == 2)
			  dev->stats.tx_errors++;
			अन्यथा अगर (i == 3)
			  dev->stats.tx_dropped++;
			अन्यथा अगर (i == 4)
			  dev->stats.collisions++;
			अन्यथा
			  dev->stats.rx_errors++;
		  पूर्ण
#पूर्ण_अगर
	पूर्ण
	spin_unlock(&lp->lock);
	lp->समयr.expires = jअगरfies + TIMED_CHECKER;
	add_समयr(&lp->समयr);
पूर्ण
#पूर्ण_अगर

/* We have a good packet(s), get it/them out of the buffers. */
अटल व्योम net_rx(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	दीर्घ ioaddr = dev->base_addr;
	काष्ठा rx_header rx_head;

	/* Process the received packet. */
	outb(EOC+MAR, ioaddr + PAR_DATA);
	पढ़ो_block(ioaddr, 8, (अचिन्हित अक्षर*)&rx_head, dev->अगर_port);
	अगर (net_debug > 5)
		prपूर्णांकk(KERN_DEBUG " rx_count %04x %04x %04x %04x..", rx_head.pad,
			   rx_head.rx_count, rx_head.rx_status, rx_head.cur_addr);
	अगर ((rx_head.rx_status & 0x77) != 0x01) अणु
		dev->stats.rx_errors++;
		अगर (rx_head.rx_status & 0x0004) dev->stats.rx_frame_errors++;
		अन्यथा अगर (rx_head.rx_status & 0x0002) dev->stats.rx_crc_errors++;
		अगर (net_debug > 3)
			prपूर्णांकk(KERN_DEBUG "%s: Unknown ATP Rx error %04x.\n",
				   dev->name, rx_head.rx_status);
		अगर  (rx_head.rx_status & 0x0020) अणु
			dev->stats.rx_fअगरo_errors++;
			ग_लिखो_reg_high(ioaddr, CMR1, CMR1h_TxENABLE);
			ग_लिखो_reg_high(ioaddr, CMR1, CMR1h_RxENABLE | CMR1h_TxENABLE);
		पूर्ण अन्यथा अगर (rx_head.rx_status & 0x0050)
			hardware_init(dev);
		वापस;
	पूर्ण अन्यथा अणु
		/* Malloc up new buffer. The "-4" omits the FCS (CRC). */
		पूर्णांक pkt_len = (rx_head.rx_count & 0x7ff) - 4;
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb(dev, pkt_len + 2);
		अगर (skb == शून्य) अणु
			dev->stats.rx_dropped++;
			जाओ करोne;
		पूर्ण

		skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
		पढ़ो_block(ioaddr, pkt_len, skb_put(skb,pkt_len), dev->अगर_port);
		skb->protocol = eth_type_trans(skb, dev);
		netअगर_rx(skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += pkt_len;
	पूर्ण
 करोne:
	ग_लिखो_reg(ioaddr, CMR1, CMR1_NextPkt);
	lp->last_rx_समय = jअगरfies;
पूर्ण

अटल व्योम पढ़ो_block(दीर्घ ioaddr, पूर्णांक length, अचिन्हित अक्षर *p, पूर्णांक data_mode)
अणु
	अगर (data_mode <= 3) अणु /* Mode 0 or 1 */
		outb(Ctrl_LNibRead, ioaddr + PAR_CONTROL);
		outb(length == 8  ?  RdAddr | HNib | MAR  :  RdAddr | MAR,
			 ioaddr + PAR_DATA);
		अगर (data_mode <= 1) अणु /* Mode 0 or 1 */
			करो अणु *p++ = पढ़ो_byte_mode0(ioaddr); पूर्ण जबतक (--length > 0);
		पूर्ण अन्यथा अणु /* Mode 2 or 3 */
			करो अणु *p++ = पढ़ो_byte_mode2(ioaddr); पूर्ण जबतक (--length > 0);
		पूर्ण
	पूर्ण अन्यथा अगर (data_mode <= 5) अणु
		करो अणु *p++ = पढ़ो_byte_mode4(ioaddr); पूर्ण जबतक (--length > 0);
	पूर्ण अन्यथा अणु
		करो अणु *p++ = पढ़ो_byte_mode6(ioaddr); पूर्ण जबतक (--length > 0);
	पूर्ण

	outb(EOC+HNib+MAR, ioaddr + PAR_DATA);
	outb(Ctrl_SelData, ioaddr + PAR_CONTROL);
पूर्ण

/* The inverse routine to net_खोलो(). */
अटल पूर्णांक
net_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	दीर्घ ioaddr = dev->base_addr;

	netअगर_stop_queue(dev);

	del_समयr_sync(&lp->समयr);

	/* Flush the Tx and disable Rx here. */
	lp->addr_mode = CMR2h_OFF;
	ग_लिखो_reg_high(ioaddr, CMR2, CMR2h_OFF);

	/* Free the IRQ line. */
	outb(0x00, ioaddr + PAR_CONTROL);
	मुक्त_irq(dev->irq, dev);

	/* Reset the ethernet hardware and activate the prपूर्णांकer pass-through. */
	ग_लिखो_reg_high(ioaddr, CMR1, CMR1h_RESET | CMR1h_MUX);
	वापस 0;
पूर्ण

/*
 *	Set or clear the multicast filter क्रम this adapter.
 */

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	दीर्घ ioaddr = dev->base_addr;

	अगर (!netdev_mc_empty(dev) || (dev->flags & (IFF_ALLMULTI|IFF_PROMISC)))
		lp->addr_mode = CMR2h_PROMISC;
	अन्यथा
		lp->addr_mode = CMR2h_Normal;
	ग_लिखो_reg_high(ioaddr, CMR2, lp->addr_mode);
पूर्ण

अटल पूर्णांक __init atp_init_module(व्योम) अणु
	अगर (debug)					/* Emit version even अगर no cards detected. */
		prपूर्णांकk(KERN_INFO "%s", version);
	वापस atp_init();
पूर्ण

अटल व्योम __निकास atp_cleanup_module(व्योम) अणु
	काष्ठा net_device *next_dev;

	जबतक (root_atp_dev) अणु
		काष्ठा net_local *atp_local = netdev_priv(root_atp_dev);
		next_dev = atp_local->next_module;
		unरेजिस्टर_netdev(root_atp_dev);
		/* No need to release_region(), since we never snarf it. */
		मुक्त_netdev(root_atp_dev);
		root_atp_dev = next_dev;
	पूर्ण
पूर्ण

module_init(atp_init_module);
module_निकास(atp_cleanup_module);
