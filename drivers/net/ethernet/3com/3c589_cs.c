<शैली गुरु>
/* ======================================================================
 *
 * A PCMCIA ethernet driver क्रम the 3com 3c589 card.
 *
 * Copyright (C) 1999 David A. Hinds -- dahinds@users.sourceक्रमge.net
 *
 * 3c589_cs.c 1.162 2001/10/13 00:08:50
 *
 * The network driver code is based on Donald Becker's 3c589 code:
 *
 * Written 1994 by Donald Becker.
 * Copyright 1993 United States Government as represented by the
 * Director, National Security Agency.  This software may be used and
 * distributed according to the terms of the GNU General Public License,
 * incorporated herein by reference.
 * Donald Becker may be reached at becker@scyld.com
 *
 * Updated क्रम 2.5.x by Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * ======================================================================
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"3c589_cs"

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/bitops.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>


/* To minimize the size of the driver source I only define operating
 * स्थिरants अगर they are used several बार. You'll need the manual
 * अगर you want to understand driver details.
 */

/* Offsets from base I/O address. */
#घोषणा EL3_DATA	0x00
#घोषणा EL3_TIMER	0x0a
#घोषणा EL3_CMD		0x0e
#घोषणा EL3_STATUS	0x0e

#घोषणा EEPROM_READ	0x0080
#घोषणा EEPROM_BUSY	0x8000

#घोषणा EL3WINDOW(win_num) outw(SelectWinकरोw + (win_num), ioaddr + EL3_CMD)

/* The top five bits written to EL3_CMD are a command, the lower
 * 11 bits are the parameter, अगर applicable.
 */

क्रमागत c509cmd अणु
	TotalReset	= 0<<11,
	SelectWinकरोw	= 1<<11,
	StartCoax	= 2<<11,
	RxDisable	= 3<<11,
	RxEnable	= 4<<11,
	RxReset		= 5<<11,
	RxDiscard	= 8<<11,
	TxEnable	= 9<<11,
	TxDisable	= 10<<11,
	TxReset		= 11<<11,
	FakeIntr	= 12<<11,
	AckIntr		= 13<<11,
	SetIntrEnb	= 14<<11,
	SetStatusEnb	= 15<<11,
	SetRxFilter	= 16<<11,
	SetRxThreshold	= 17<<11,
	SetTxThreshold	= 18<<11,
	SetTxStart	= 19<<11,
	StatsEnable	= 21<<11,
	StatsDisable	= 22<<11,
	StopCoax	= 23<<11
पूर्ण;

क्रमागत c509status अणु
	IntLatch	= 0x0001,
	AdapterFailure	= 0x0002,
	TxComplete	= 0x0004,
	TxAvailable	= 0x0008,
	RxComplete	= 0x0010,
	RxEarly		= 0x0020,
	IntReq		= 0x0040,
	StatsFull	= 0x0080,
	CmdBusy		= 0x1000
पूर्ण;

/* The SetRxFilter command accepts the following classes: */
क्रमागत RxFilter अणु
	RxStation	= 1,
	RxMulticast	= 2,
	RxBroadcast	= 4,
	RxProm		= 8
पूर्ण;

/* Register winकरोw 1 offsets, the winकरोw used in normal operation. */
#घोषणा TX_FIFO		0x00
#घोषणा RX_FIFO		0x00
#घोषणा RX_STATUS	0x08
#घोषणा TX_STATUS	0x0B
#घोषणा TX_FREE		0x0C	/* Reमुख्यing मुक्त bytes in Tx buffer. */

#घोषणा WN0_IRQ		0x08	/* Winकरोw 0: Set IRQ line in bits 12-15. */
#घोषणा WN4_MEDIA	0x0A	/* Winकरोw 4: Various transcvr/media bits. */
#घोषणा MEDIA_TP	0x00C0	/* Enable link beat and jabber क्रम 10baseT. */
#घोषणा MEDIA_LED	0x0001	/* Enable link light on 3C589E cards. */

/* Time in jअगरfies beक्रमe concluding Tx hung */
#घोषणा TX_TIMEOUT	((400*HZ)/1000)

काष्ठा el3_निजी अणु
	काष्ठा pcmcia_device	*p_dev;
	/* For transceiver monitoring */
	काष्ठा समयr_list	media;
	u16			media_status;
	u16			fast_poll;
	अचिन्हित दीर्घ		last_irq;
	spinlock_t		lock;
पूर्ण;

अटल स्थिर अक्षर *अगर_names[] = अणु "auto", "10baseT", "10base2", "AUI" पूर्ण;

/*====================================================================*/

/* Module parameters */

MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("3Com 3c589 series PCMCIA ethernet driver");
MODULE_LICENSE("GPL");

#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v; module_param(n, पूर्णांक, 0)

/* Special hook क्रम setting अगर_port when module is loaded */
INT_MODULE_PARM(अगर_port, 0);


/*====================================================================*/

अटल पूर्णांक tc589_config(काष्ठा pcmcia_device *link);
अटल व्योम tc589_release(काष्ठा pcmcia_device *link);

अटल u16 पढ़ो_eeprom(अचिन्हित पूर्णांक ioaddr, पूर्णांक index);
अटल व्योम tc589_reset(काष्ठा net_device *dev);
अटल व्योम media_check(काष्ठा समयr_list *t);
अटल पूर्णांक el3_config(काष्ठा net_device *dev, काष्ठा अगरmap *map);
अटल पूर्णांक el3_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t el3_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev);
अटल irqवापस_t el3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल व्योम update_stats(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *el3_get_stats(काष्ठा net_device *dev);
अटल पूर्णांक el3_rx(काष्ठा net_device *dev);
अटल पूर्णांक el3_बंद(काष्ठा net_device *dev);
अटल व्योम el3_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;

अटल व्योम tc589_detach(काष्ठा pcmcia_device *p_dev);

अटल स्थिर काष्ठा net_device_ops el3_netdev_ops = अणु
	.nकरो_खोलो		= el3_खोलो,
	.nकरो_stop		= el3_बंद,
	.nकरो_start_xmit		= el3_start_xmit,
	.nकरो_tx_समयout		= el3_tx_समयout,
	.nकरो_set_config		= el3_config,
	.nकरो_get_stats		= el3_get_stats,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक tc589_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा el3_निजी *lp;
	काष्ठा net_device *dev;

	dev_dbg(&link->dev, "3c589_attach()\n");

	/* Create new ethernet device */
	dev = alloc_etherdev(माप(काष्ठा el3_निजी));
	अगर (!dev)
		वापस -ENOMEM;
	lp = netdev_priv(dev);
	link->priv = dev;
	lp->p_dev = link;

	spin_lock_init(&lp->lock);
	link->resource[0]->end = 16;
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;

	link->config_flags |= CONF_ENABLE_IRQ;
	link->config_index = 1;

	dev->netdev_ops = &el3_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	dev->ethtool_ops = &netdev_ethtool_ops;

	वापस tc589_config(link);
पूर्ण

अटल व्योम tc589_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	dev_dbg(&link->dev, "3c589_detach\n");

	unरेजिस्टर_netdev(dev);

	tc589_release(link);

	मुक्त_netdev(dev);
पूर्ण /* tc589_detach */

अटल पूर्णांक tc589_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;
	__be16 *phys_addr;
	पूर्णांक ret, i, j, multi = 0, fअगरo;
	अचिन्हित पूर्णांक ioaddr;
	अटल स्थिर अक्षर * स्थिर ram_split[] = अणु"5:3", "3:1", "1:1", "3:5"पूर्ण;
	u8 *buf;
	माप_प्रकार len;

	dev_dbg(&link->dev, "3c589_config\n");

	phys_addr = (__be16 *)dev->dev_addr;
	/* Is this a 3c562? */
	अगर (link->manf_id != MANFID_3COM)
		dev_info(&link->dev, "hmmm, is this really a 3Com card??\n");
	multi = (link->card_id == PRODID_3COM_3C562);

	link->io_lines = 16;

	/* For the 3c562, the base address must be xx00-xx7f */
	क्रम (i = j = 0; j < 0x400; j += 0x10) अणु
		अगर (multi && (j & 0x80))
			जारी;
		link->resource[0]->start = j ^ 0x300;
		i = pcmcia_request_io(link);
		अगर (i == 0)
			अवरोध;
	पूर्ण
	अगर (i != 0)
		जाओ failed;

	ret = pcmcia_request_irq(link, el3_पूर्णांकerrupt);
	अगर (ret)
		जाओ failed;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	dev->irq = link->irq;
	dev->base_addr = link->resource[0]->start;
	ioaddr = dev->base_addr;
	EL3WINDOW(0);

	/* The 3c589 has an extra EEPROM क्रम configuration info, including
	 * the hardware address.  The 3c562 माला_दो the address in the CIS.
	 */
	len = pcmcia_get_tuple(link, 0x88, &buf);
	अगर (buf && len >= 6) अणु
		क्रम (i = 0; i < 3; i++)
			phys_addr[i] = htons(le16_to_cpu(buf[i*2]));
		kमुक्त(buf);
	पूर्ण अन्यथा अणु
		kमुक्त(buf); /* 0 < len < 6 */
		क्रम (i = 0; i < 3; i++)
			phys_addr[i] = htons(पढ़ो_eeprom(ioaddr, i));
		अगर (phys_addr[0] == htons(0x6060)) अणु
			dev_err(&link->dev, "IO port conflict at 0x%03lx-0x%03lx\n",
					dev->base_addr, dev->base_addr+15);
			जाओ failed;
		पूर्ण
	पूर्ण

	/* The address and resource configuration रेजिस्टर aren't loaded from
	 * the EEPROM and *must* be set to 0 and IRQ3 क्रम the PCMCIA version.
	 */

	outw(0x3f00, ioaddr + 8);
	fअगरo = inl(ioaddr);

	/* The अगर_port symbol can be set when the module is loaded */
	अगर ((अगर_port >= 0) && (अगर_port <= 3))
		dev->अगर_port = अगर_port;
	अन्यथा
		dev_err(&link->dev, "invalid if_port requested\n");

	SET_NETDEV_DEV(dev, &link->dev);

	अगर (रेजिस्टर_netdev(dev) != 0) अणु
		dev_err(&link->dev, "register_netdev() failed\n");
		जाओ failed;
	पूर्ण

	netdev_info(dev, "3Com 3c%s, io %#3lx, irq %d, hw_addr %pM\n",
			(multi ? "562" : "589"), dev->base_addr, dev->irq,
			dev->dev_addr);
	netdev_info(dev, "  %dK FIFO split %s Rx:Tx, %s xcvr\n",
			(fअगरo & 7) ? 32 : 8, ram_split[(fअगरo >> 16) & 3],
			अगर_names[dev->अगर_port]);
	वापस 0;

failed:
	tc589_release(link);
	वापस -ENODEV;
पूर्ण /* tc589_config */

अटल व्योम tc589_release(काष्ठा pcmcia_device *link)
अणु
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक tc589_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो)
		netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tc589_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो) अणु
		tc589_reset(dev);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण

/*====================================================================*/

/* Use this क्रम commands that may take समय to finish */

अटल व्योम tc589_रुको_क्रम_completion(काष्ठा net_device *dev, पूर्णांक cmd)
अणु
	पूर्णांक i = 100;
	outw(cmd, dev->base_addr + EL3_CMD);
	जबतक (--i > 0)
		अगर (!(inw(dev->base_addr + EL3_STATUS) & 0x1000))
			अवरोध;
	अगर (i == 0)
		netdev_warn(dev, "command 0x%04x did not complete!\n", cmd);
पूर्ण

/* Read a word from the EEPROM using the regular EEPROM access रेजिस्टर.
 * Assume that we are in रेजिस्टर winकरोw zero.
 */

अटल u16 पढ़ो_eeprom(अचिन्हित पूर्णांक ioaddr, पूर्णांक index)
अणु
	पूर्णांक i;
	outw(EEPROM_READ + index, ioaddr + 10);
	/* Reading the eeprom takes 162 us */
	क्रम (i = 1620; i >= 0; i--)
		अगर ((inw(ioaddr + 10) & EEPROM_BUSY) == 0)
			अवरोध;
	वापस inw(ioaddr + 12);
पूर्ण

/* Set transceiver type, perhaps to something other than what the user
 * specअगरied in dev->अगर_port.
 */

अटल व्योम tc589_set_xcvr(काष्ठा net_device *dev, पूर्णांक अगर_port)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;

	EL3WINDOW(0);
	चयन (अगर_port) अणु
	हाल 0:
	हाल 1:
		outw(0, ioaddr + 6);
		अवरोध;
	हाल 2:
		outw(3<<14, ioaddr + 6);
		अवरोध;
	हाल 3:
		outw(1<<14, ioaddr + 6);
		अवरोध;
	पूर्ण
	/* On PCMCIA, this just turns on the LED */
	outw((अगर_port == 2) ? StartCoax : StopCoax, ioaddr + EL3_CMD);
	/* 10baseT पूर्णांकerface, enable link beat and jabber check. */
	EL3WINDOW(4);
	outw(MEDIA_LED | ((अगर_port < 2) ? MEDIA_TP : 0), ioaddr + WN4_MEDIA);
	EL3WINDOW(1);
	अगर (अगर_port == 2)
		lp->media_status = ((dev->अगर_port == 0) ? 0x8000 : 0x4000);
	अन्यथा
		lp->media_status = ((dev->अगर_port == 0) ? 0x4010 : 0x8800);
पूर्ण

अटल व्योम dump_status(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	EL3WINDOW(1);
	netdev_info(dev, "  irq status %04x, rx status %04x, tx status %02x  tx free %04x\n",
			inw(ioaddr+EL3_STATUS), inw(ioaddr+RX_STATUS),
			inb(ioaddr+TX_STATUS), inw(ioaddr+TX_FREE));
	EL3WINDOW(4);
	netdev_info(dev, "  diagnostics: fifo %04x net %04x ethernet %04x media %04x\n",
			inw(ioaddr+0x04), inw(ioaddr+0x06), inw(ioaddr+0x08),
			inw(ioaddr+0x0a));
	EL3WINDOW(1);
पूर्ण

/* Reset and restore all of the 3c589 रेजिस्टरs. */
अटल व्योम tc589_reset(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक i;

	EL3WINDOW(0);
	outw(0x0001, ioaddr + 4);			/* Activate board. */
	outw(0x3f00, ioaddr + 8);			/* Set the IRQ line. */

	/* Set the station address in winकरोw 2. */
	EL3WINDOW(2);
	क्रम (i = 0; i < 6; i++)
		outb(dev->dev_addr[i], ioaddr + i);

	tc589_set_xcvr(dev, dev->अगर_port);

	/* Switch to the stats winकरोw, and clear all stats by पढ़ोing. */
	outw(StatsDisable, ioaddr + EL3_CMD);
	EL3WINDOW(6);
	क्रम (i = 0; i < 9; i++)
		inb(ioaddr+i);
	inw(ioaddr + 10);
	inw(ioaddr + 12);

	/* Switch to रेजिस्टर set 1 क्रम normal use. */
	EL3WINDOW(1);

	set_rx_mode(dev);
	outw(StatsEnable, ioaddr + EL3_CMD); /* Turn on statistics. */
	outw(RxEnable, ioaddr + EL3_CMD); /* Enable the receiver. */
	outw(TxEnable, ioaddr + EL3_CMD); /* Enable transmitter. */
	/* Allow status bits to be seen. */
	outw(SetStatusEnb | 0xff, ioaddr + EL3_CMD);
	/* Ack all pending events, and set active indicator mask. */
	outw(AckIntr | IntLatch | TxAvailable | RxEarly | IntReq,
	 ioaddr + EL3_CMD);
	outw(SetIntrEnb | IntLatch | TxAvailable | RxComplete | StatsFull
	 | AdapterFailure, ioaddr + EL3_CMD);
पूर्ण

अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	snम_लिखो(info->bus_info, माप(info->bus_info),
		"PCMCIA 0x%lx", dev->base_addr);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
पूर्ण;

अटल पूर्णांक el3_config(काष्ठा net_device *dev, काष्ठा अगरmap *map)
अणु
	अगर ((map->port != (u_अक्षर)(-1)) && (map->port != dev->अगर_port)) अणु
		अगर (map->port <= 3) अणु
			dev->अगर_port = map->port;
			netdev_info(dev, "switched to %s port\n", अगर_names[dev->अगर_port]);
			tc589_set_xcvr(dev, dev->अगर_port);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक el3_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	काष्ठा pcmcia_device *link = lp->p_dev;

	अगर (!pcmcia_dev_present(link))
		वापस -ENODEV;

	link->खोलो++;
	netअगर_start_queue(dev);

	tc589_reset(dev);
	समयr_setup(&lp->media, media_check, 0);
	mod_समयr(&lp->media, jअगरfies + HZ);

	dev_dbg(&link->dev, "%s: opened, status %4.4x.\n",
	  dev->name, inw(dev->base_addr + EL3_STATUS));

	वापस 0;
पूर्ण

अटल व्योम el3_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;

	netdev_warn(dev, "Transmit timed out!\n");
	dump_status(dev);
	dev->stats.tx_errors++;
	netअगर_trans_update(dev); /* prevent tx समयout */
	/* Issue TX_RESET and TX_START commands. */
	tc589_रुको_क्रम_completion(dev, TxReset);
	outw(TxEnable, ioaddr + EL3_CMD);
	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम pop_tx_status(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक i;

	/* Clear the Tx status stack. */
	क्रम (i = 32; i > 0; i--) अणु
		u_अक्षर tx_status = inb(ioaddr + TX_STATUS);
		अगर (!(tx_status & 0x84))
			अवरोध;
		/* reset transmitter on jabber error or underrun */
		अगर (tx_status & 0x30)
			tc589_रुको_क्रम_completion(dev, TxReset);
		अगर (tx_status & 0x38) अणु
			netdev_dbg(dev, "transmit error: status 0x%02x\n", tx_status);
			outw(TxEnable, ioaddr + EL3_CMD);
			dev->stats.tx_पातed_errors++;
		पूर्ण
		outb(0x00, ioaddr + TX_STATUS); /* Pop the status stack. */
	पूर्ण
पूर्ण

अटल netdev_tx_t el3_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	काष्ठा el3_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	netdev_dbg(dev, "el3_start_xmit(length = %ld) called, status %4.4x.\n",
	       (दीर्घ)skb->len, inw(ioaddr + EL3_STATUS));

	spin_lock_irqsave(&priv->lock, flags);

	dev->stats.tx_bytes += skb->len;

	/* Put out the द्विगुनword header... */
	outw(skb->len, ioaddr + TX_FIFO);
	outw(0x00, ioaddr + TX_FIFO);
	/* ... and the packet rounded to a द्विगुनword. */
	outsl(ioaddr + TX_FIFO, skb->data, (skb->len + 3) >> 2);

	अगर (inw(ioaddr + TX_FREE) <= 1536) अणु
		netअगर_stop_queue(dev);
		/* Interrupt us when the FIFO has room क्रम max-sized packet. */
		outw(SetTxThreshold + 1536, ioaddr + EL3_CMD);
	पूर्ण

	pop_tx_status(dev);
	spin_unlock_irqrestore(&priv->lock, flags);
	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

/* The EL3 पूर्णांकerrupt handler. */
अटल irqवापस_t el3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक ioaddr;
	__u16 status;
	पूर्णांक i = 0, handled = 1;

	अगर (!netअगर_device_present(dev))
		वापस IRQ_NONE;

	ioaddr = dev->base_addr;

	netdev_dbg(dev, "interrupt, status %4.4x.\n", inw(ioaddr + EL3_STATUS));

	spin_lock(&lp->lock);
	जबतक ((status = inw(ioaddr + EL3_STATUS)) &
	(IntLatch | RxComplete | StatsFull)) अणु
		अगर ((status & 0xe000) != 0x2000) अणु
			netdev_dbg(dev, "interrupt from dead card\n");
			handled = 0;
			अवरोध;
		पूर्ण
		अगर (status & RxComplete)
			el3_rx(dev);
		अगर (status & TxAvailable) अणु
			netdev_dbg(dev, "    TX room bit was handled.\n");
			/* There's room in the FIFO क्रम a full-sized packet. */
			outw(AckIntr | TxAvailable, ioaddr + EL3_CMD);
			netअगर_wake_queue(dev);
		पूर्ण
		अगर (status & TxComplete)
			pop_tx_status(dev);
		अगर (status & (AdapterFailure | RxEarly | StatsFull)) अणु
			/* Handle all uncommon पूर्णांकerrupts. */
			अगर (status & StatsFull)		/* Empty statistics. */
				update_stats(dev);
			अगर (status & RxEarly) अणु
				/* Rx early is unused. */
				el3_rx(dev);
				outw(AckIntr | RxEarly, ioaddr + EL3_CMD);
			पूर्ण
			अगर (status & AdapterFailure) अणु
				u16 fअगरo_diag;
				EL3WINDOW(4);
				fअगरo_diag = inw(ioaddr + 4);
				EL3WINDOW(1);
				netdev_warn(dev, "adapter failure, FIFO diagnostic register %04x.\n",
			    fअगरo_diag);
				अगर (fअगरo_diag & 0x0400) अणु
					/* Tx overrun */
					tc589_रुको_क्रम_completion(dev, TxReset);
					outw(TxEnable, ioaddr + EL3_CMD);
				पूर्ण
				अगर (fअगरo_diag & 0x2000) अणु
					/* Rx underrun */
					tc589_रुको_क्रम_completion(dev, RxReset);
					set_rx_mode(dev);
					outw(RxEnable, ioaddr + EL3_CMD);
				पूर्ण
				outw(AckIntr | AdapterFailure, ioaddr + EL3_CMD);
			पूर्ण
		पूर्ण
		अगर (++i > 10) अणु
			netdev_err(dev, "infinite loop in interrupt, status %4.4x.\n",
					status);
			/* Clear all पूर्णांकerrupts */
			outw(AckIntr | 0xFF, ioaddr + EL3_CMD);
			अवरोध;
		पूर्ण
		/* Acknowledge the IRQ. */
		outw(AckIntr | IntReq | IntLatch, ioaddr + EL3_CMD);
	पूर्ण
	lp->last_irq = jअगरfies;
	spin_unlock(&lp->lock);
	netdev_dbg(dev, "exiting interrupt, status %4.4x.\n",
			inw(ioaddr + EL3_STATUS));
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम media_check(काष्ठा समयr_list *t)
अणु
	काष्ठा el3_निजी *lp = from_समयr(lp, t, media);
	काष्ठा net_device *dev = lp->p_dev->priv;
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	u16 media, errs;
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_device_present(dev))
		जाओ reschedule;

	/* Check क्रम pending पूर्णांकerrupt with expired latency समयr: with
	 * this, we can limp aदीर्घ even अगर the पूर्णांकerrupt is blocked
	 */
	अगर ((inw(ioaddr + EL3_STATUS) & IntLatch) &&
	(inb(ioaddr + EL3_TIMER) == 0xff)) अणु
		अगर (!lp->fast_poll)
			netdev_warn(dev, "interrupt(s) dropped!\n");

		local_irq_save(flags);
		el3_पूर्णांकerrupt(dev->irq, dev);
		local_irq_restore(flags);

		lp->fast_poll = HZ;
	पूर्ण
	अगर (lp->fast_poll) अणु
		lp->fast_poll--;
		lp->media.expires = jअगरfies + HZ/100;
		add_समयr(&lp->media);
		वापस;
	पूर्ण

	/* lp->lock guards the EL3 winकरोw. Winकरोw should always be 1 except
	 * when the lock is held
	 */

	spin_lock_irqsave(&lp->lock, flags);
	EL3WINDOW(4);
	media = inw(ioaddr+WN4_MEDIA) & 0xc810;

	/* Ignore collisions unless we've had no irq's recently */
	अगर (समय_beक्रमe(jअगरfies, lp->last_irq + HZ)) अणु
		media &= ~0x0010;
	पूर्ण अन्यथा अणु
		/* Try harder to detect carrier errors */
		EL3WINDOW(6);
		outw(StatsDisable, ioaddr + EL3_CMD);
		errs = inb(ioaddr + 0);
		outw(StatsEnable, ioaddr + EL3_CMD);
		dev->stats.tx_carrier_errors += errs;
		अगर (errs || (lp->media_status & 0x0010))
			media |= 0x0010;
	पूर्ण

	अगर (media != lp->media_status) अणु
		अगर ((media & lp->media_status & 0x8000) &&
				((lp->media_status ^ media) & 0x0800))
		netdev_info(dev, "%s link beat\n",
				(lp->media_status & 0x0800 ? "lost" : "found"));
		अन्यथा अगर ((media & lp->media_status & 0x4000) &&
		 ((lp->media_status ^ media) & 0x0010))
		netdev_info(dev, "coax cable %s\n",
				(lp->media_status & 0x0010 ? "ok" : "problem"));
		अगर (dev->अगर_port == 0) अणु
			अगर (media & 0x8000) अणु
				अगर (media & 0x0800)
					netdev_info(dev, "flipped to 10baseT\n");
				अन्यथा
			tc589_set_xcvr(dev, 2);
			पूर्ण अन्यथा अगर (media & 0x4000) अणु
				अगर (media & 0x0010)
					tc589_set_xcvr(dev, 1);
				अन्यथा
					netdev_info(dev, "flipped to 10base2\n");
			पूर्ण
		पूर्ण
		lp->media_status = media;
	पूर्ण

	EL3WINDOW(1);
	spin_unlock_irqrestore(&lp->lock, flags);

reschedule:
	lp->media.expires = jअगरfies + HZ;
	add_समयr(&lp->media);
पूर्ण

अटल काष्ठा net_device_stats *el3_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	काष्ठा pcmcia_device *link = lp->p_dev;

	अगर (pcmcia_dev_present(link)) अणु
		spin_lock_irqsave(&lp->lock, flags);
		update_stats(dev);
		spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण
	वापस &dev->stats;
पूर्ण

/* Update statistics.  We change to रेजिस्टर winकरोw 6, so this should be run
* single-thपढ़ोed अगर the device is active. This is expected to be a rare
* operation, and it's simpler क्रम the rest of the driver to assume that
* winकरोw 1 is always valid rather than use a special winकरोw-state variable.
*
* Caller must hold the lock क्रम this
*/

अटल व्योम update_stats(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;

	netdev_dbg(dev, "updating the statistics.\n");
	/* Turn off statistics updates जबतक पढ़ोing. */
	outw(StatsDisable, ioaddr + EL3_CMD);
	/* Switch to the stats winकरोw, and पढ़ो everything. */
	EL3WINDOW(6);
	dev->stats.tx_carrier_errors	+= inb(ioaddr + 0);
	dev->stats.tx_heartbeat_errors	+= inb(ioaddr + 1);
	/* Multiple collisions. */
	inb(ioaddr + 2);
	dev->stats.collisions		+= inb(ioaddr + 3);
	dev->stats.tx_winकरोw_errors		+= inb(ioaddr + 4);
	dev->stats.rx_fअगरo_errors		+= inb(ioaddr + 5);
	dev->stats.tx_packets		+= inb(ioaddr + 6);
	/* Rx packets   */
	inb(ioaddr + 7);
	/* Tx deferrals */
	inb(ioaddr + 8);
	/* Rx octets */
	inw(ioaddr + 10);
	/* Tx octets */
	inw(ioaddr + 12);

	/* Back to winकरोw 1, and turn statistics back on. */
	EL3WINDOW(1);
	outw(StatsEnable, ioaddr + EL3_CMD);
पूर्ण

अटल पूर्णांक el3_rx(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक worklimit = 32;
	लघु rx_status;

	netdev_dbg(dev, "in rx_packet(), status %4.4x, rx_status %4.4x.\n",
	       inw(ioaddr+EL3_STATUS), inw(ioaddr+RX_STATUS));
	जबतक (!((rx_status = inw(ioaddr + RX_STATUS)) & 0x8000) &&
		    worklimit > 0) अणु
		worklimit--;
		अगर (rx_status & 0x4000) अणु /* Error, update stats. */
			लघु error = rx_status & 0x3800;
			dev->stats.rx_errors++;
			चयन (error) अणु
			हाल 0x0000:
				dev->stats.rx_over_errors++;
				अवरोध;
			हाल 0x0800:
				dev->stats.rx_length_errors++;
				अवरोध;
			हाल 0x1000:
				dev->stats.rx_frame_errors++;
				अवरोध;
			हाल 0x1800:
				dev->stats.rx_length_errors++;
				अवरोध;
			हाल 0x2000:
				dev->stats.rx_frame_errors++;
				अवरोध;
			हाल 0x2800:
				dev->stats.rx_crc_errors++;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			लघु pkt_len = rx_status & 0x7ff;
			काष्ठा sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 5);

			netdev_dbg(dev, "    Receiving packet size %d status %4.4x.\n",
		       pkt_len, rx_status);
			अगर (skb != शून्य) अणु
				skb_reserve(skb, 2);
				insl(ioaddr+RX_FIFO, skb_put(skb, pkt_len),
			(pkt_len+3)>>2);
				skb->protocol = eth_type_trans(skb, dev);
				netअगर_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
			पूर्ण अन्यथा अणु
				netdev_dbg(dev, "couldn't allocate a sk_buff of size %d.\n",
			   pkt_len);
				dev->stats.rx_dropped++;
			पूर्ण
		पूर्ण
		/* Pop the top of the Rx FIFO */
		tc589_रुको_क्रम_completion(dev, RxDiscard);
	पूर्ण
	अगर (worklimit == 0)
		netdev_warn(dev, "too much work in el3_rx!\n");
	वापस 0;
पूर्ण

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	u16 opts = SetRxFilter | RxStation | RxBroadcast;

	अगर (dev->flags & IFF_PROMISC)
		opts |= RxMulticast | RxProm;
	अन्यथा अगर (!netdev_mc_empty(dev) || (dev->flags & IFF_ALLMULTI))
		opts |= RxMulticast;
	outw(opts, ioaddr + EL3_CMD);
पूर्ण

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	set_rx_mode(dev);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक el3_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	काष्ठा pcmcia_device *link = lp->p_dev;
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;

	dev_dbg(&link->dev, "%s: shutting down ethercard.\n", dev->name);

	अगर (pcmcia_dev_present(link)) अणु
		/* Turn off statistics ASAP.  We update dev->stats below. */
		outw(StatsDisable, ioaddr + EL3_CMD);

		/* Disable the receiver and transmitter. */
		outw(RxDisable, ioaddr + EL3_CMD);
		outw(TxDisable, ioaddr + EL3_CMD);

		अगर (dev->अगर_port == 2)
			/* Turn off thinnet घातer.  Green! */
			outw(StopCoax, ioaddr + EL3_CMD);
		अन्यथा अगर (dev->अगर_port == 1) अणु
			/* Disable link beat and jabber */
			EL3WINDOW(4);
			outw(0, ioaddr + WN4_MEDIA);
		पूर्ण

		/* Switching back to winकरोw 0 disables the IRQ. */
		EL3WINDOW(0);
		/* But we explicitly zero the IRQ line select anyway. */
		outw(0x0f00, ioaddr + WN0_IRQ);

		/* Check अगर the card still exists */
		अगर ((inw(ioaddr+EL3_STATUS) & 0xe000) == 0x2000)
			update_stats(dev);
	पूर्ण

	link->खोलो--;
	netअगर_stop_queue(dev);
	del_समयr_sync(&lp->media);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id tc589_ids[] = अणु
	PCMCIA_MFC_DEVICE_MANF_CARD(0, 0x0101, 0x0562),
	PCMCIA_MFC_DEVICE_PROD_ID1(0, "Motorola MARQUIS", 0xf03e4e77),
	PCMCIA_DEVICE_MANF_CARD(0x0101, 0x0589),
	PCMCIA_DEVICE_PROD_ID12("Farallon", "ENet", 0x58d93fc4, 0x992c2202),
	PCMCIA_MFC_DEVICE_CIS_MANF_CARD(0, 0x0101, 0x0035, "cis/3CXEM556.cis"),
	PCMCIA_MFC_DEVICE_CIS_MANF_CARD(0, 0x0101, 0x003d, "cis/3CXEM556.cis"),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, tc589_ids);

अटल काष्ठा pcmcia_driver tc589_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "3c589_cs",
	.probe		= tc589_probe,
	.हटाओ		= tc589_detach,
	.id_table	= tc589_ids,
	.suspend	= tc589_suspend,
	.resume		= tc589_resume,
पूर्ण;
module_pcmcia_driver(tc589_driver);
