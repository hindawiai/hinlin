<शैली गुरु>
/* 3c574.c: A PCMCIA ethernet driver क्रम the 3com 3c574 "RoadRunner".

	Written 1993-1998 by
	Donald Becker, becker@scyld.com, (driver core) and
	David Hinds, dahinds@users.sourceक्रमge.net (from his PC card code).
	Locking fixes (C) Copyright 2003 Red Hat Inc

	This software may be used and distributed according to the terms of
	the GNU General Public License, incorporated herein by reference.

	This driver derives from Donald Becker's 3c509 core, which has the
	following copyright:
	Copyright 1993 United States Government as represented by the
	Director, National Security Agency.
	

*/

/*
				Theory of Operation

I. Board Compatibility

This device driver is deचिन्हित क्रम the 3Com 3c574 PC card Fast Ethernet
Adapter.

II. Board-specअगरic settings

None -- PC cards are स्वतःconfigured.

III. Driver operation

The 3c574 uses a Boomerang-style पूर्णांकerface, without the bus-master capability.
See the Boomerang driver and करोcumentation क्रम most details.

IV. Notes and chip करोcumentation.

Two added रेजिस्टरs are used to enhance PIO perक्रमmance, RunnerRdCtrl and
RunnerWrCtrl.  These are 11 bit करोwn-counters that are preloaded with the
count of word (16 bits) पढ़ोs or ग_लिखोs the driver is about to करो to the Rx
or Tx FIFO.  The chip is then able to hide the पूर्णांकernal-PCI-bus to PC-card
translation latency by buffering the I/O operations with an 8 word FIFO.
Note: No other chip accesses are permitted when this buffer is used.

A second enhancement is that both attribute and common memory space
0x0800-0x0fff can translated to the PIO FIFO.  Thus memory operations (faster
with *some* PCcard bridges) may be used instead of I/O operations.
This is enabled by setting the 0x10 bit in the PCMCIA LAN COR.

Some slow PC card bridges work better अगर they never see a WAIT संकेत.
This is configured by setting the 0x20 bit in the PCMCIA LAN COR.
Only करो this after testing that it is reliable and improves perक्रमmance.

The upper five bits of RunnerRdCtrl are used to winकरोw पूर्णांकo PCcard
configuration space रेजिस्टरs.  Winकरोw 0 is the regular Boomerang/Odie
रेजिस्टर set, 1-5 are various PC card control रेजिस्टरs, and 16-31 are
the (reversed!) CIS table.

A final note: writing the InternalConfig रेजिस्टर in winकरोw 3 with an
invalid ramWidth is Very Bad.

V. References

http://www.scyld.com/expert/NWay.hपंचांगl
http://www.national.com/opf/DP/DP83840A.hपंचांगl

Thanks to Terry Murphy of 3Com क्रम providing development inक्रमmation क्रम
earlier 3Com products.

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mii.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

/*====================================================================*/

/* Module parameters */

MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("3Com 3c574 series PCMCIA ethernet driver");
MODULE_LICENSE("GPL");

#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v; module_param(n, पूर्णांक, 0)

/* Maximum events (Rx packets, etc.) to handle at each पूर्णांकerrupt. */
INT_MODULE_PARM(max_पूर्णांकerrupt_work, 32);

/* Force full duplex modes? */
INT_MODULE_PARM(full_duplex, 0);

/* Autodetect link polarity reversal? */
INT_MODULE_PARM(स्वतः_polarity, 1);


/*====================================================================*/

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  ((800*HZ)/1000)

/* To minimize the size of the driver source and make the driver more
   पढ़ोable not all स्थिरants are symbolically defined.
   You'll need the manual अगर you want to understand driver details anyway. */
/* Offsets from base I/O address. */
#घोषणा EL3_DATA	0x00
#घोषणा EL3_CMD		0x0e
#घोषणा EL3_STATUS	0x0e

#घोषणा EL3WINDOW(win_num) outw(SelectWinकरोw + (win_num), ioaddr + EL3_CMD)

/* The top five bits written to EL3_CMD are a command, the lower
   11 bits are the parameter, अगर applicable. */
क्रमागत el3_cmds अणु
	TotalReset = 0<<11, SelectWinकरोw = 1<<11, StartCoax = 2<<11,
	RxDisable = 3<<11, RxEnable = 4<<11, RxReset = 5<<11, RxDiscard = 8<<11,
	TxEnable = 9<<11, TxDisable = 10<<11, TxReset = 11<<11,
	FakeIntr = 12<<11, AckIntr = 13<<11, SetIntrEnb = 14<<11,
	SetStatusEnb = 15<<11, SetRxFilter = 16<<11, SetRxThreshold = 17<<11,
	SetTxThreshold = 18<<11, SetTxStart = 19<<11, StatsEnable = 21<<11,
	StatsDisable = 22<<11, StopCoax = 23<<11,
पूर्ण;

क्रमागत elxl_status अणु
	IntLatch = 0x0001, AdapterFailure = 0x0002, TxComplete = 0x0004,
	TxAvailable = 0x0008, RxComplete = 0x0010, RxEarly = 0x0020,
	IntReq = 0x0040, StatsFull = 0x0080, CmdBusy = 0x1000 पूर्ण;

/* The SetRxFilter command accepts the following classes: */
क्रमागत RxFilter अणु
	RxStation = 1, RxMulticast = 2, RxBroadcast = 4, RxProm = 8
पूर्ण;

क्रमागत Winकरोw0 अणु
	Wn0EepromCmd = 10, Wn0EepromData = 12, /* EEPROM command/address, data. */
	IntrStatus=0x0E,		/* Valid in all winकरोws. */
पूर्ण;
/* These assumes the larger EEPROM. */
क्रमागत Win0_EEPROM_cmds अणु
	EEPROM_Read = 0x200, EEPROM_WRITE = 0x100, EEPROM_ERASE = 0x300,
	EEPROM_EWENB = 0x30,		/* Enable erasing/writing क्रम 10 msec. */
	EEPROM_EWDIS = 0x00,		/* Disable EWENB beक्रमe 10 msec समयout. */
पूर्ण;

/* Register winकरोw 1 offsets, the winकरोw used in normal operation.
   On the "Odie" this winकरोw is always mapped at offsets 0x10-0x1f.
   Except क्रम TxFree, which is overlapped by RunnerWrCtrl. */
क्रमागत Winकरोw1 अणु
	TX_FIFO = 0x10,  RX_FIFO = 0x10,  RxErrors = 0x14,
	RxStatus = 0x18,  Timer=0x1A, TxStatus = 0x1B,
	TxFree = 0x0C, /* Reमुख्यing मुक्त bytes in Tx buffer. */
	RunnerRdCtrl = 0x16, RunnerWrCtrl = 0x1c,
पूर्ण;

क्रमागत Winकरोw3 अणु			/* Winकरोw 3: MAC/config bits. */
	Wn3_Config=0, Wn3_MAC_Ctrl=6, Wn3_Options=8,
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

क्रमागत Winकरोw4 अणु		/* Winकरोw 4: Xcvr/media bits. */
	Wn4_FIFODiag = 4, Wn4_NetDiag = 6, Wn4_PhysicalMgmt=8, Wn4_Media = 10,
पूर्ण;

#घोषणा MEDIA_TP	0x00C0	/* Enable link beat and jabber क्रम 10baseT. */

काष्ठा el3_निजी अणु
	काष्ठा pcmcia_device	*p_dev;
	u16 advertising, partner;		/* NWay media advertisement */
	अचिन्हित अक्षर phys;			/* MII device address */
	अचिन्हित पूर्णांक स्वतःselect:1, शेष_media:3;	/* Read from the EEPROM/Wn3_Config. */
	/* क्रम transceiver monitoring */
	काष्ठा समयr_list media;
	अचिन्हित लघु media_status;
	अचिन्हित लघु fast_poll;
	अचिन्हित दीर्घ last_irq;
	spinlock_t winकरोw_lock;			/* Guards the Winकरोw selection */
पूर्ण;

/* Set अगरf a MII transceiver on any पूर्णांकerface requires mdio preamble.
   This only set with the original DP83840 on older 3c905 boards, so the extra
   code size of a per-पूर्णांकerface flag is not worthजबतक. */
अटल अक्षर mii_preamble_required = 0;

/* Index of functions. */

अटल पूर्णांक tc574_config(काष्ठा pcmcia_device *link);
अटल व्योम tc574_release(काष्ठा pcmcia_device *link);

अटल व्योम mdio_sync(अचिन्हित पूर्णांक ioaddr, पूर्णांक bits);
अटल पूर्णांक mdio_पढ़ो(अचिन्हित पूर्णांक ioaddr, पूर्णांक phy_id, पूर्णांक location);
अटल व्योम mdio_ग_लिखो(अचिन्हित पूर्णांक ioaddr, पूर्णांक phy_id, पूर्णांक location,
		       पूर्णांक value);
अटल अचिन्हित लघु पढ़ो_eeprom(अचिन्हित पूर्णांक ioaddr, पूर्णांक index);
अटल व्योम tc574_रुको_क्रम_completion(काष्ठा net_device *dev, पूर्णांक cmd);

अटल व्योम tc574_reset(काष्ठा net_device *dev);
अटल व्योम media_check(काष्ठा समयr_list *t);
अटल पूर्णांक el3_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t el3_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev);
अटल irqवापस_t el3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल व्योम update_stats(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *el3_get_stats(काष्ठा net_device *dev);
अटल पूर्णांक el3_rx(काष्ठा net_device *dev, पूर्णांक worklimit);
अटल पूर्णांक el3_बंद(काष्ठा net_device *dev);
अटल व्योम el3_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल पूर्णांक el3_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);

अटल व्योम tc574_detach(काष्ठा pcmcia_device *p_dev);

/*
	tc574_attach() creates an "instance" of the driver, allocating
	local data काष्ठाures क्रम one device.  The device is रेजिस्टरed
	with Card Services.
*/
अटल स्थिर काष्ठा net_device_ops el3_netdev_ops = अणु
	.nकरो_खोलो 		= el3_खोलो,
	.nकरो_stop 		= el3_बंद,
	.nकरो_start_xmit		= el3_start_xmit,
	.nकरो_tx_समयout 	= el3_tx_समयout,
	.nकरो_get_stats		= el3_get_stats,
	.nकरो_करो_ioctl		= el3_ioctl,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक tc574_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा el3_निजी *lp;
	काष्ठा net_device *dev;

	dev_dbg(&link->dev, "3c574_attach()\n");

	/* Create the PC card device object. */
	dev = alloc_etherdev(माप(काष्ठा el3_निजी));
	अगर (!dev)
		वापस -ENOMEM;
	lp = netdev_priv(dev);
	link->priv = dev;
	lp->p_dev = link;

	spin_lock_init(&lp->winकरोw_lock);
	link->resource[0]->end = 32;
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;
	link->config_flags |= CONF_ENABLE_IRQ;
	link->config_index = 1;

	dev->netdev_ops = &el3_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	वापस tc574_config(link);
पूर्ण

अटल व्योम tc574_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	dev_dbg(&link->dev, "3c574_detach()\n");

	unरेजिस्टर_netdev(dev);

	tc574_release(link);

	मुक्त_netdev(dev);
पूर्ण /* tc574_detach */

अटल स्थिर अक्षर *ram_split[] = अणु"5:3", "3:1", "1:1", "3:5"पूर्ण;

अटल पूर्णांक tc574_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	पूर्णांक ret, i, j;
	अचिन्हित पूर्णांक ioaddr;
	__be16 *phys_addr;
	अक्षर *cardname;
	__u32 config;
	u8 *buf;
	माप_प्रकार len;

	phys_addr = (__be16 *)dev->dev_addr;

	dev_dbg(&link->dev, "3c574_config()\n");

	link->io_lines = 16;

	क्रम (i = j = 0; j < 0x400; j += 0x20) अणु
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

	/* The 3c574 normally uses an EEPROM क्रम configuration info, including
	   the hardware address.  The future products may include a modem chip
	   and put the address in the CIS. */

	len = pcmcia_get_tuple(link, 0x88, &buf);
	अगर (buf && len >= 6) अणु
		क्रम (i = 0; i < 3; i++)
			phys_addr[i] = htons(le16_to_cpu(buf[i * 2]));
		kमुक्त(buf);
	पूर्ण अन्यथा अणु
		kमुक्त(buf); /* 0 < len < 6 */
		EL3WINDOW(0);
		क्रम (i = 0; i < 3; i++)
			phys_addr[i] = htons(पढ़ो_eeprom(ioaddr, i + 10));
		अगर (phys_addr[0] == htons(0x6060)) अणु
			pr_notice("IO port conflict at 0x%03lx-0x%03lx\n",
				  dev->base_addr, dev->base_addr+15);
			जाओ failed;
		पूर्ण
	पूर्ण
	अगर (link->prod_id[1])
		cardname = link->prod_id[1];
	अन्यथा
		cardname = "3Com 3c574";

	अणु
		u_अक्षर mcr;
		outw(2<<11, ioaddr + RunnerRdCtrl);
		mcr = inb(ioaddr + 2);
		outw(0<<11, ioaddr + RunnerRdCtrl);
		pr_info("  ASIC rev %d,", mcr>>3);
		EL3WINDOW(3);
		config = inl(ioaddr + Wn3_Config);
		lp->शेष_media = (config & Xcvr) >> Xcvr_shअगरt;
		lp->स्वतःselect = config & Autoselect ? 1 : 0;
	पूर्ण

	समयr_setup(&lp->media, media_check, 0);

	अणु
		पूर्णांक phy;
		
		/* Roadrunner only: Turn on the MII transceiver */
		outw(0x8040, ioaddr + Wn3_Options);
		mdelay(1);
		outw(0xc040, ioaddr + Wn3_Options);
		tc574_रुको_क्रम_completion(dev, TxReset);
		tc574_रुको_क्रम_completion(dev, RxReset);
		mdelay(1);
		outw(0x8040, ioaddr + Wn3_Options);
		
		EL3WINDOW(4);
		क्रम (phy = 1; phy <= 32; phy++) अणु
			पूर्णांक mii_status;
			mdio_sync(ioaddr, 32);
			mii_status = mdio_पढ़ो(ioaddr, phy & 0x1f, 1);
			अगर (mii_status != 0xffff) अणु
				lp->phys = phy & 0x1f;
				dev_dbg(&link->dev, "  MII transceiver at "
					"index %d, status %x.\n",
					  phy, mii_status);
				अगर ((mii_status & 0x0040) == 0)
					mii_preamble_required = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (phy > 32) अणु
			pr_notice("  No MII transceivers found!\n");
			जाओ failed;
		पूर्ण
		i = mdio_पढ़ो(ioaddr, lp->phys, 16) | 0x40;
		mdio_ग_लिखो(ioaddr, lp->phys, 16, i);
		lp->advertising = mdio_पढ़ो(ioaddr, lp->phys, 4);
		अगर (full_duplex) अणु
			/* Only advertise the FD media types. */
			lp->advertising &= ~0x02a0;
			mdio_ग_लिखो(ioaddr, lp->phys, 4, lp->advertising);
		पूर्ण
	पूर्ण

	SET_NETDEV_DEV(dev, &link->dev);

	अगर (रेजिस्टर_netdev(dev) != 0) अणु
		pr_notice("register_netdev() failed\n");
		जाओ failed;
	पूर्ण

	netdev_info(dev, "%s at io %#3lx, irq %d, hw_addr %pM\n",
		    cardname, dev->base_addr, dev->irq, dev->dev_addr);
	netdev_info(dev, " %dK FIFO split %s Rx:Tx, %sMII interface.\n",
		    8 << (config & Ram_size),
		    ram_split[(config & Ram_split) >> Ram_split_shअगरt],
		    config & Autoselect ? "autoselect " : "");

	वापस 0;

failed:
	tc574_release(link);
	वापस -ENODEV;

पूर्ण /* tc574_config */

अटल व्योम tc574_release(काष्ठा pcmcia_device *link)
अणु
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक tc574_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो)
		netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tc574_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो) अणु
		tc574_reset(dev);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dump_status(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	EL3WINDOW(1);
	netdev_info(dev, "  irq status %04x, rx status %04x, tx status %02x, tx free %04x\n",
		    inw(ioaddr+EL3_STATUS),
		    inw(ioaddr+RxStatus), inb(ioaddr+TxStatus),
		    inw(ioaddr+TxFree));
	EL3WINDOW(4);
	netdev_info(dev, "  diagnostics: fifo %04x net %04x ethernet %04x media %04x\n",
		    inw(ioaddr+0x04), inw(ioaddr+0x06),
		    inw(ioaddr+0x08), inw(ioaddr+0x0a));
	EL3WINDOW(1);
पूर्ण

/*
  Use this क्रम commands that may take समय to finish
*/
अटल व्योम tc574_रुको_क्रम_completion(काष्ठा net_device *dev, पूर्णांक cmd)
अणु
	पूर्णांक i = 1500;
	outw(cmd, dev->base_addr + EL3_CMD);
	जबतक (--i > 0)
		अगर (!(inw(dev->base_addr + EL3_STATUS) & 0x1000)) अवरोध;
	अगर (i == 0)
		netdev_notice(dev, "command 0x%04x did not complete!\n", cmd);
पूर्ण

/* Read a word from the EEPROM using the regular EEPROM access रेजिस्टर.
   Assume that we are in रेजिस्टर winकरोw zero.
 */
अटल अचिन्हित लघु पढ़ो_eeprom(अचिन्हित पूर्णांक ioaddr, पूर्णांक index)
अणु
	पूर्णांक समयr;
	outw(EEPROM_Read + index, ioaddr + Wn0EepromCmd);
	/* Pause क्रम at least 162 usec क्रम the पढ़ो to take place. */
	क्रम (समयr = 1620; समयr >= 0; समयr--) अणु
		अगर ((inw(ioaddr + Wn0EepromCmd) & 0x8000) == 0)
			अवरोध;
	पूर्ण
	वापस inw(ioaddr + Wn0EepromData);
पूर्ण

/* MII transceiver control section.
   Read and ग_लिखो the MII रेजिस्टरs using software-generated serial
   MDIO protocol.  See the MII specअगरications or DP83840A data sheet
   क्रम details.
   The maxium data घड़ी rate is 2.5 Mhz.  The timing is easily met by the
   slow PC card पूर्णांकerface. */

#घोषणा MDIO_SHIFT_CLK	0x01
#घोषणा MDIO_सूची_WRITE	0x04
#घोषणा MDIO_DATA_WRITE0 (0x00 | MDIO_सूची_WRITE)
#घोषणा MDIO_DATA_WRITE1 (0x02 | MDIO_सूची_WRITE)
#घोषणा MDIO_DATA_READ	0x02
#घोषणा MDIO_ENB_IN		0x00

/* Generate the preamble required क्रम initial synchronization and
   a few older transceivers. */
अटल व्योम mdio_sync(अचिन्हित पूर्णांक ioaddr, पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक mdio_addr = ioaddr + Wn4_PhysicalMgmt;

	/* Establish sync by sending at least 32 logic ones. */
	जबतक (-- bits >= 0) अणु
		outw(MDIO_DATA_WRITE1, mdio_addr);
		outw(MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, mdio_addr);
	पूर्ण
पूर्ण

अटल पूर्णांक mdio_पढ़ो(अचिन्हित पूर्णांक ioaddr, पूर्णांक phy_id, पूर्णांक location)
अणु
	पूर्णांक i;
	पूर्णांक पढ़ो_cmd = (0xf6 << 10) | (phy_id << 5) | location;
	अचिन्हित पूर्णांक retval = 0;
	अचिन्हित पूर्णांक mdio_addr = ioaddr + Wn4_PhysicalMgmt;

	अगर (mii_preamble_required)
		mdio_sync(ioaddr, 32);

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 14; i >= 0; i--) अणु
		पूर्णांक dataval = (पढ़ो_cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
		outw(dataval, mdio_addr);
		outw(dataval | MDIO_SHIFT_CLK, mdio_addr);
	पूर्ण
	/* Read the two transition, 16 data, and wire-idle bits. */
	क्रम (i = 19; i > 0; i--) अणु
		outw(MDIO_ENB_IN, mdio_addr);
		retval = (retval << 1) | ((inw(mdio_addr) & MDIO_DATA_READ) ? 1 : 0);
		outw(MDIO_ENB_IN | MDIO_SHIFT_CLK, mdio_addr);
	पूर्ण
	वापस (retval>>1) & 0xffff;
पूर्ण

अटल व्योम mdio_ग_लिखो(अचिन्हित पूर्णांक ioaddr, पूर्णांक phy_id, पूर्णांक location, पूर्णांक value)
अणु
	पूर्णांक ग_लिखो_cmd = 0x50020000 | (phy_id << 23) | (location << 18) | value;
	अचिन्हित पूर्णांक mdio_addr = ioaddr + Wn4_PhysicalMgmt;
	पूर्णांक i;

	अगर (mii_preamble_required)
		mdio_sync(ioaddr, 32);

	/* Shअगरt the command bits out. */
	क्रम (i = 31; i >= 0; i--) अणु
		पूर्णांक dataval = (ग_लिखो_cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
		outw(dataval, mdio_addr);
		outw(dataval | MDIO_SHIFT_CLK, mdio_addr);
	पूर्ण
	/* Leave the पूर्णांकerface idle. */
	क्रम (i = 1; i >= 0; i--) अणु
		outw(MDIO_ENB_IN, mdio_addr);
		outw(MDIO_ENB_IN | MDIO_SHIFT_CLK, mdio_addr);
	पूर्ण
पूर्ण

/* Reset and restore all of the 3c574 रेजिस्टरs. */
अटल व्योम tc574_reset(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	पूर्णांक i;
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;

	tc574_रुको_क्रम_completion(dev, TotalReset|0x10);

	spin_lock_irqsave(&lp->winकरोw_lock, flags);
	/* Clear any transactions in progress. */
	outw(0, ioaddr + RunnerWrCtrl);
	outw(0, ioaddr + RunnerRdCtrl);

	/* Set the station address and mask. */
	EL3WINDOW(2);
	क्रम (i = 0; i < 6; i++)
		outb(dev->dev_addr[i], ioaddr + i);
	क्रम (; i < 12; i+=2)
		outw(0, ioaddr + i);

	/* Reset config options */
	EL3WINDOW(3);
	outb((dev->mtu > 1500 ? 0x40 : 0), ioaddr + Wn3_MAC_Ctrl);
	outl((lp->स्वतःselect ? 0x01000000 : 0) | 0x0062001b,
		 ioaddr + Wn3_Config);
	/* Roadrunner only: Turn on the MII transceiver. */
	outw(0x8040, ioaddr + Wn3_Options);
	mdelay(1);
	outw(0xc040, ioaddr + Wn3_Options);
	EL3WINDOW(1);
	spin_unlock_irqrestore(&lp->winकरोw_lock, flags);
	
	tc574_रुको_क्रम_completion(dev, TxReset);
	tc574_रुको_क्रम_completion(dev, RxReset);
	mdelay(1);
	spin_lock_irqsave(&lp->winकरोw_lock, flags);
	EL3WINDOW(3);
	outw(0x8040, ioaddr + Wn3_Options);

	/* Switch to the stats winकरोw, and clear all stats by पढ़ोing. */
	outw(StatsDisable, ioaddr + EL3_CMD);
	EL3WINDOW(6);
	क्रम (i = 0; i < 10; i++)
		inb(ioaddr + i);
	inw(ioaddr + 10);
	inw(ioaddr + 12);
	EL3WINDOW(4);
	inb(ioaddr + 12);
	inb(ioaddr + 13);

	/* .. enable any extra statistics bits.. */
	outw(0x0040, ioaddr + Wn4_NetDiag);
	
	EL3WINDOW(1);
	spin_unlock_irqrestore(&lp->winकरोw_lock, flags);
	
	/* .. re-sync MII and re-fill what NWay is advertising. */
	mdio_sync(ioaddr, 32);
	mdio_ग_लिखो(ioaddr, lp->phys, 4, lp->advertising);
	अगर (!स्वतः_polarity) अणु
		/* works क्रम TDK 78Q2120 series MII's */
		i = mdio_पढ़ो(ioaddr, lp->phys, 16) | 0x20;
		mdio_ग_लिखो(ioaddr, lp->phys, 16, i);
	पूर्ण

	spin_lock_irqsave(&lp->winकरोw_lock, flags);
	/* Switch to रेजिस्टर set 1 क्रम normal use, just क्रम TxFree. */
	set_rx_mode(dev);
	spin_unlock_irqrestore(&lp->winकरोw_lock, flags);
	outw(StatsEnable, ioaddr + EL3_CMD); /* Turn on statistics. */
	outw(RxEnable, ioaddr + EL3_CMD); /* Enable the receiver. */
	outw(TxEnable, ioaddr + EL3_CMD); /* Enable transmitter. */
	/* Allow status bits to be seen. */
	outw(SetStatusEnb | 0xff, ioaddr + EL3_CMD);
	/* Ack all pending events, and set active indicator mask. */
	outw(AckIntr | IntLatch | TxAvailable | RxEarly | IntReq,
		 ioaddr + EL3_CMD);
	outw(SetIntrEnb | IntLatch | TxAvailable | RxComplete | StatsFull
		 | AdapterFailure | RxEarly, ioaddr + EL3_CMD);
पूर्ण

अटल पूर्णांक el3_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	काष्ठा pcmcia_device *link = lp->p_dev;

	अगर (!pcmcia_dev_present(link))
		वापस -ENODEV;
	
	link->खोलो++;
	netअगर_start_queue(dev);
	
	tc574_reset(dev);
	lp->media.expires = jअगरfies + HZ;
	add_समयr(&lp->media);
	
	dev_dbg(&link->dev, "%s: opened, status %4.4x.\n",
		  dev->name, inw(dev->base_addr + EL3_STATUS));
	
	वापस 0;
पूर्ण

अटल व्योम el3_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	
	netdev_notice(dev, "Transmit timed out!\n");
	dump_status(dev);
	dev->stats.tx_errors++;
	netअगर_trans_update(dev); /* prevent tx समयout */
	/* Issue TX_RESET and TX_START commands. */
	tc574_रुको_क्रम_completion(dev, TxReset);
	outw(TxEnable, ioaddr + EL3_CMD);
	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम pop_tx_status(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक i;
    
	/* Clear the Tx status stack. */
	क्रम (i = 32; i > 0; i--) अणु
		u_अक्षर tx_status = inb(ioaddr + TxStatus);
		अगर (!(tx_status & 0x84))
			अवरोध;
		/* reset transmitter on jabber error or underrun */
		अगर (tx_status & 0x30)
			tc574_रुको_क्रम_completion(dev, TxReset);
		अगर (tx_status & 0x38) अणु
			pr_debug("%s: transmit error: status 0x%02x\n",
				  dev->name, tx_status);
			outw(TxEnable, ioaddr + EL3_CMD);
			dev->stats.tx_पातed_errors++;
		पूर्ण
		outb(0x00, ioaddr + TxStatus); /* Pop the status stack. */
	पूर्ण
पूर्ण

अटल netdev_tx_t el3_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	pr_debug("%s: el3_start_xmit(length = %ld) called, "
		  "status %4.4x.\n", dev->name, (दीर्घ)skb->len,
		  inw(ioaddr + EL3_STATUS));

	spin_lock_irqsave(&lp->winकरोw_lock, flags);

	dev->stats.tx_bytes += skb->len;

	/* Put out the द्विगुनword header... */
	outw(skb->len, ioaddr + TX_FIFO);
	outw(0, ioaddr + TX_FIFO);
	/* ... and the packet rounded to a द्विगुनword. */
	outsl(ioaddr + TX_FIFO, skb->data, (skb->len+3)>>2);

	/* TxFree appears only in Winकरोw 1, not offset 0x1c. */
	अगर (inw(ioaddr + TxFree) <= 1536) अणु
		netअगर_stop_queue(dev);
		/* Interrupt us when the FIFO has room क्रम max-sized packet. 
		   The threshold is in units of dwords. */
		outw(SetTxThreshold + (1536>>2), ioaddr + EL3_CMD);
	पूर्ण

	pop_tx_status(dev);
	spin_unlock_irqrestore(&lp->winकरोw_lock, flags);
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/* The EL3 पूर्णांकerrupt handler. */
अटल irqवापस_t el3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक ioaddr;
	अचिन्हित status;
	पूर्णांक work_budget = max_पूर्णांकerrupt_work;
	पूर्णांक handled = 0;

	अगर (!netअगर_device_present(dev))
		वापस IRQ_NONE;
	ioaddr = dev->base_addr;

	pr_debug("%s: interrupt, status %4.4x.\n",
		  dev->name, inw(ioaddr + EL3_STATUS));

	spin_lock(&lp->winकरोw_lock);
	
	जबतक ((status = inw(ioaddr + EL3_STATUS)) &
		   (IntLatch | RxComplete | RxEarly | StatsFull)) अणु
		अगर (!netअगर_device_present(dev) ||
			((status & 0xe000) != 0x2000)) अणु
			pr_debug("%s: Interrupt from dead card\n", dev->name);
			अवरोध;
		पूर्ण

		handled = 1;

		अगर (status & RxComplete)
			work_budget = el3_rx(dev, work_budget);

		अगर (status & TxAvailable) अणु
			pr_debug("  TX room bit was handled.\n");
			/* There's room in the FIFO क्रम a full-sized packet. */
			outw(AckIntr | TxAvailable, ioaddr + EL3_CMD);
			netअगर_wake_queue(dev);
		पूर्ण

		अगर (status & TxComplete)
			pop_tx_status(dev);

		अगर (status & (AdapterFailure | RxEarly | StatsFull)) अणु
			/* Handle all uncommon पूर्णांकerrupts. */
			अगर (status & StatsFull)
				update_stats(dev);
			अगर (status & RxEarly) अणु
				work_budget = el3_rx(dev, work_budget);
				outw(AckIntr | RxEarly, ioaddr + EL3_CMD);
			पूर्ण
			अगर (status & AdapterFailure) अणु
				u16 fअगरo_diag;
				EL3WINDOW(4);
				fअगरo_diag = inw(ioaddr + Wn4_FIFODiag);
				EL3WINDOW(1);
				netdev_notice(dev, "adapter failure, FIFO diagnostic register %04x\n",
					      fअगरo_diag);
				अगर (fअगरo_diag & 0x0400) अणु
					/* Tx overrun */
					tc574_रुको_क्रम_completion(dev, TxReset);
					outw(TxEnable, ioaddr + EL3_CMD);
				पूर्ण
				अगर (fअगरo_diag & 0x2000) अणु
					/* Rx underrun */
					tc574_रुको_क्रम_completion(dev, RxReset);
					set_rx_mode(dev);
					outw(RxEnable, ioaddr + EL3_CMD);
				पूर्ण
				outw(AckIntr | AdapterFailure, ioaddr + EL3_CMD);
			पूर्ण
		पूर्ण

		अगर (--work_budget < 0) अणु
			pr_debug("%s: Too much work in interrupt, "
				  "status %4.4x.\n", dev->name, status);
			/* Clear all पूर्णांकerrupts */
			outw(AckIntr | 0xFF, ioaddr + EL3_CMD);
			अवरोध;
		पूर्ण
		/* Acknowledge the IRQ. */
		outw(AckIntr | IntReq | IntLatch, ioaddr + EL3_CMD);
	पूर्ण

	pr_debug("%s: exiting interrupt, status %4.4x.\n",
		  dev->name, inw(ioaddr + EL3_STATUS));
		  
	spin_unlock(&lp->winकरोw_lock);
	वापस IRQ_RETVAL(handled);
पूर्ण

/*
    This समयr serves two purposes: to check क्रम missed पूर्णांकerrupts
	(and as a last resort, poll the NIC क्रम events), and to monitor
	the MII, reporting changes in cable status.
*/
अटल व्योम media_check(काष्ठा समयr_list *t)
अणु
	काष्ठा el3_निजी *lp = from_समयr(lp, t, media);
	काष्ठा net_device *dev = lp->p_dev->priv;
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु /* cable, */ media, partner;

	अगर (!netअगर_device_present(dev))
		जाओ reschedule;
	
	/* Check क्रम pending पूर्णांकerrupt with expired latency समयr: with
	   this, we can limp aदीर्घ even अगर the पूर्णांकerrupt is blocked */
	अगर ((inw(ioaddr + EL3_STATUS) & IntLatch) && (inb(ioaddr + Timer) == 0xff)) अणु
		अगर (!lp->fast_poll)
			netdev_info(dev, "interrupt(s) dropped!\n");

		local_irq_save(flags);
		el3_पूर्णांकerrupt(dev->irq, dev);
		local_irq_restore(flags);

		lp->fast_poll = HZ;
	पूर्ण
	अगर (lp->fast_poll) अणु
		lp->fast_poll--;
		lp->media.expires = jअगरfies + 2*HZ/100;
		add_समयr(&lp->media);
		वापस;
	पूर्ण

	spin_lock_irqsave(&lp->winकरोw_lock, flags);
	EL3WINDOW(4);
	media = mdio_पढ़ो(ioaddr, lp->phys, 1);
	partner = mdio_पढ़ो(ioaddr, lp->phys, 5);
	EL3WINDOW(1);
	
	अगर (media != lp->media_status) अणु
		अगर ((media ^ lp->media_status) & 0x0004)
			netdev_info(dev, "%s link beat\n",
				    (lp->media_status & 0x0004) ? "lost" : "found");
		अगर ((media ^ lp->media_status) & 0x0020) अणु
			lp->partner = 0;
			अगर (lp->media_status & 0x0020) अणु
				netdev_info(dev, "autonegotiation restarted\n");
			पूर्ण अन्यथा अगर (partner) अणु
				partner &= lp->advertising;
				lp->partner = partner;
				netdev_info(dev, "autonegotiation complete: "
					    "%dbaseT-%cD selected\n",
					    (partner & 0x0180) ? 100 : 10,
					    (partner & 0x0140) ? 'F' : 'H');
			पूर्ण अन्यथा अणु
				netdev_info(dev, "link partner did not autonegotiate\n");
			पूर्ण

			EL3WINDOW(3);
			outb((partner & 0x0140 ? 0x20 : 0) |
				 (dev->mtu > 1500 ? 0x40 : 0), ioaddr + Wn3_MAC_Ctrl);
			EL3WINDOW(1);

		पूर्ण
		अगर (media & 0x0010)
			netdev_info(dev, "remote fault detected\n");
		अगर (media & 0x0002)
			netdev_info(dev, "jabber detected\n");
		lp->media_status = media;
	पूर्ण
	spin_unlock_irqrestore(&lp->winकरोw_lock, flags);

reschedule:
	lp->media.expires = jअगरfies + HZ;
	add_समयr(&lp->media);
पूर्ण

अटल काष्ठा net_device_stats *el3_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);

	अगर (netअगर_device_present(dev)) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&lp->winकरोw_lock, flags);
		update_stats(dev);
		spin_unlock_irqrestore(&lp->winकरोw_lock, flags);
	पूर्ण
	वापस &dev->stats;
पूर्ण

/*  Update statistics.
	Surprisingly this need not be run single-thपढ़ोed, but it effectively is.
	The counters clear when पढ़ो, so the adds must merely be atomic.
 */
अटल व्योम update_stats(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	u8 up;

	pr_debug("%s: updating the statistics.\n", dev->name);

	अगर (inw(ioaddr+EL3_STATUS) == 0xffff) /* No card. */
		वापस;
		
	/* Unlike the 3c509 we need not turn off stats updates जबतक पढ़ोing. */
	/* Switch to the stats winकरोw, and पढ़ो everything. */
	EL3WINDOW(6);
	dev->stats.tx_carrier_errors 		+= inb(ioaddr + 0);
	dev->stats.tx_heartbeat_errors		+= inb(ioaddr + 1);
	/* Multiple collisions. */	   	inb(ioaddr + 2);
	dev->stats.collisions			+= inb(ioaddr + 3);
	dev->stats.tx_winकरोw_errors		+= inb(ioaddr + 4);
	dev->stats.rx_fअगरo_errors		+= inb(ioaddr + 5);
	dev->stats.tx_packets			+= inb(ioaddr + 6);
	up		 			 = inb(ioaddr + 9);
	dev->stats.tx_packets			+= (up&0x30) << 4;
	/* Rx packets   */			   inb(ioaddr + 7);
	/* Tx deferrals */			   inb(ioaddr + 8);
	/* rx */				   inw(ioaddr + 10);
	/* tx */				   inw(ioaddr + 12);

	EL3WINDOW(4);
	/* BadSSD */				   inb(ioaddr + 12);
	up					 = inb(ioaddr + 13);

	EL3WINDOW(1);
पूर्ण

अटल पूर्णांक el3_rx(काष्ठा net_device *dev, पूर्णांक worklimit)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	लघु rx_status;
	
	pr_debug("%s: in rx_packet(), status %4.4x, rx_status %4.4x.\n",
		  dev->name, inw(ioaddr+EL3_STATUS), inw(ioaddr+RxStatus));
	जबतक (!((rx_status = inw(ioaddr + RxStatus)) & 0x8000) &&
			worklimit > 0) अणु
		worklimit--;
		अगर (rx_status & 0x4000) अणु /* Error, update stats. */
			लघु error = rx_status & 0x3800;
			dev->stats.rx_errors++;
			चयन (error) अणु
			हाल 0x0000:	dev->stats.rx_over_errors++; अवरोध;
			हाल 0x0800:	dev->stats.rx_length_errors++; अवरोध;
			हाल 0x1000:	dev->stats.rx_frame_errors++; अवरोध;
			हाल 0x1800:	dev->stats.rx_length_errors++; अवरोध;
			हाल 0x2000:	dev->stats.rx_frame_errors++; अवरोध;
			हाल 0x2800:	dev->stats.rx_crc_errors++; अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			लघु pkt_len = rx_status & 0x7ff;
			काष्ठा sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 5);

			pr_debug("  Receiving packet size %d status %4.4x.\n",
				  pkt_len, rx_status);
			अगर (skb != शून्य) अणु
				skb_reserve(skb, 2);
				insl(ioaddr+RX_FIFO, skb_put(skb, pkt_len),
						((pkt_len+3)>>2));
				skb->protocol = eth_type_trans(skb, dev);
				netअगर_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
			पूर्ण अन्यथा अणु
				pr_debug("%s: couldn't allocate a sk_buff of"
					  " size %d.\n", dev->name, pkt_len);
				dev->stats.rx_dropped++;
			पूर्ण
		पूर्ण
		tc574_रुको_क्रम_completion(dev, RxDiscard);
	पूर्ण

	वापस worklimit;
पूर्ण

/* Provide ioctl() calls to examine the MII xcvr state. */
अटल पूर्णांक el3_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);
	पूर्णांक phy = lp->phys & 0x1f;

	pr_debug("%s: In ioct(%-.6s, %#4.4x) %4.4x %4.4x %4.4x %4.4x.\n",
		  dev->name, rq->अगरr_अगरrn.अगरrn_name, cmd,
		  data->phy_id, data->reg_num, data->val_in, data->val_out);

	चयन(cmd) अणु
	हाल SIOCGMIIPHY:		/* Get the address of the PHY in use. */
		data->phy_id = phy;
		fallthrough;
	हाल SIOCGMIIREG:		/* Read the specअगरied MII रेजिस्टर. */
		अणु
			पूर्णांक saved_winकरोw;
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&lp->winकरोw_lock, flags);
			saved_winकरोw = inw(ioaddr + EL3_CMD) >> 13;
			EL3WINDOW(4);
			data->val_out = mdio_पढ़ो(ioaddr, data->phy_id & 0x1f,
						  data->reg_num & 0x1f);
			EL3WINDOW(saved_winकरोw);
			spin_unlock_irqrestore(&lp->winकरोw_lock, flags);
			वापस 0;
		पूर्ण
	हाल SIOCSMIIREG:		/* Write the specअगरied MII रेजिस्टर */
		अणु
			पूर्णांक saved_winकरोw;
                       अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&lp->winकरोw_lock, flags);
			saved_winकरोw = inw(ioaddr + EL3_CMD) >> 13;
			EL3WINDOW(4);
			mdio_ग_लिखो(ioaddr, data->phy_id & 0x1f,
				   data->reg_num & 0x1f, data->val_in);
			EL3WINDOW(saved_winकरोw);
			spin_unlock_irqrestore(&lp->winकरोw_lock, flags);
			वापस 0;
		पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/* The Odie chip has a 64 bin multicast filter, but the bit layout is not
   करोcumented.  Until it is we revert to receiving all multicast frames when
   any multicast reception is desired.
   Note: My other drivers emit a log message whenever promiscuous mode is
   entered to help detect password snअगरfers.  This is less desirable on
   typical PC card machines, so we omit the message.
   */

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;

	अगर (dev->flags & IFF_PROMISC)
		outw(SetRxFilter | RxStation | RxMulticast | RxBroadcast | RxProm,
			 ioaddr + EL3_CMD);
	अन्यथा अगर (!netdev_mc_empty(dev) || (dev->flags & IFF_ALLMULTI))
		outw(SetRxFilter|RxStation|RxMulticast|RxBroadcast, ioaddr + EL3_CMD);
	अन्यथा
		outw(SetRxFilter | RxStation | RxBroadcast, ioaddr + EL3_CMD);
पूर्ण

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lp->winकरोw_lock, flags);
	set_rx_mode(dev);
	spin_unlock_irqrestore(&lp->winकरोw_lock, flags);
पूर्ण

अटल पूर्णांक el3_बंद(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	काष्ठा el3_निजी *lp = netdev_priv(dev);
	काष्ठा pcmcia_device *link = lp->p_dev;

	dev_dbg(&link->dev, "%s: shutting down ethercard.\n", dev->name);
	
	अगर (pcmcia_dev_present(link)) अणु
		अचिन्हित दीर्घ flags;

		/* Turn off statistics ASAP.  We update lp->stats below. */
		outw(StatsDisable, ioaddr + EL3_CMD);
		
		/* Disable the receiver and transmitter. */
		outw(RxDisable, ioaddr + EL3_CMD);
		outw(TxDisable, ioaddr + EL3_CMD);
		
		/* Note: Switching to winकरोw 0 may disable the IRQ. */
		EL3WINDOW(0);
		spin_lock_irqsave(&lp->winकरोw_lock, flags);
		update_stats(dev);
		spin_unlock_irqrestore(&lp->winकरोw_lock, flags);

		/* क्रमce पूर्णांकerrupts off */
		outw(SetIntrEnb | 0x0000, ioaddr + EL3_CMD);
	पूर्ण

	link->खोलो--;
	netअगर_stop_queue(dev);
	del_समयr_sync(&lp->media);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id tc574_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x0101, 0x0574),
	PCMCIA_MFC_DEVICE_CIS_MANF_CARD(0, 0x0101, 0x0556, "cis/3CCFEM556.cis"),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, tc574_ids);

अटल काष्ठा pcmcia_driver tc574_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "3c574_cs",
	.probe		= tc574_probe,
	.हटाओ		= tc574_detach,
	.id_table       = tc574_ids,
	.suspend	= tc574_suspend,
	.resume		= tc574_resume,
पूर्ण;
module_pcmcia_driver(tc574_driver);
