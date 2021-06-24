<शैली गुरु>
/* A Linux device driver क्रम PCI NE2000 clones.
 *
 * Authors and other copyright holders:
 * 1992-2000 by Donald Becker, NE2000 core and various modअगरications.
 * 1995-1998 by Paul Gorपंचांगaker, core modअगरications and PCI support.
 * Copyright 1993 asचिन्हित to the United States Government as represented
 * by the Director, National Security Agency.
 *
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice.  This file is not
 * a complete program and may only be used when the entire operating
 * प्रणाली is licensed under the GPL.
 *
 * The author may be reached as becker@scyld.com, or C/O
 * Scyld Computing Corporation
 * 410 Severn Ave., Suite 210
 * Annapolis MD 21403
 *
 * Issues reमुख्यing:
 * People are making PCI NE2000 clones! Oh the horror, the horror...
 * Limited full-duplex support.
 */

#घोषणा DRV_NAME	"ne2k-pci"
#घोषणा DRV_DESCRIPTION	"PCI NE2000 clone driver"
#घोषणा DRV_AUTHOR	"Donald Becker / Paul Gortmaker"
#घोषणा DRV_VERSION	"1.03"
#घोषणा DRV_RELDATE	"9/22/2003"

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/* The user-configurable values.
 * These may be modअगरied when a driver module is loaded.
 */

/* More are supported, limit only on options */
#घोषणा MAX_UNITS 8

/* Used to pass the full-duplex flag, etc. */
अटल पूर्णांक full_duplex[MAX_UNITS];
अटल पूर्णांक options[MAX_UNITS];

/* Force a non std. amount of memory.  Units are 256 byte pages. */
/* #घोषणा PACKETBUF_MEMSIZE	0x40 */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#समावेश "8390.h"

अटल पूर्णांक ne2k_msg_enable;

अटल स्थिर पूर्णांक शेष_msg_level = (NETIF_MSG_DRV | NETIF_MSG_PROBE |
				      NETIF_MSG_RX_ERR | NETIF_MSG_TX_ERR);

#अगर defined(__घातerpc__)
#घोषणा inl_le(addr)  le32_to_cpu(inl(addr))
#घोषणा inw_le(addr)  le16_to_cpu(inw(addr))
#पूर्ण_अगर

MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");

module_param_named(msg_enable, ne2k_msg_enable, पूर्णांक, 0444);
module_param_array(options, पूर्णांक, शून्य, 0);
module_param_array(full_duplex, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(msg_enable, "Debug message level (see linux/netdevice.h for bitmap)");
MODULE_PARM_DESC(options, "Bit 5: full duplex");
MODULE_PARM_DESC(full_duplex, "full duplex setting(s) (1)");

/* Some defines that people can play with अगर so inclined.
 */

/* Use 32 bit data-movement operations instead of 16 bit. */
#घोषणा USE_LONGIO

/* Do we implement the पढ़ो beक्रमe ग_लिखो bugfix ? */
/* #घोषणा NE_RW_BUGFIX */

/* Flags.  We नाम an existing ei_status field to store flags!
 * Thus only the low 8 bits are usable क्रम non-init-समय flags.
 */
#घोषणा ne2k_flags reg0

क्रमागत अणु
	/* Chip can करो only 16/32-bit xfers. */
	ONLY_16BIT_IO = 8, ONLY_32BIT_IO = 4,
	/* User override. */
	FORCE_FDX = 0x20,
	REALTEK_FDX = 0x40, HOLTEK_FDX = 0x80,
	STOP_PG_0x60 = 0x100,
पूर्ण;

क्रमागत ne2k_pci_chipsets अणु
	CH_RealTek_RTL_8029 = 0,
	CH_Winbond_89C940,
	CH_Compex_RL2000,
	CH_KTI_ET32P2,
	CH_NetVin_NV5000SC,
	CH_Via_86C926,
	CH_SureCom_NE34,
	CH_Winbond_W89C940F,
	CH_Holtek_HT80232,
	CH_Holtek_HT80229,
	CH_Winbond_89C940_8c4a,
पूर्ण;


अटल काष्ठा अणु
	अक्षर *name;
	पूर्णांक flags;
पूर्ण pci_clone_list[] = अणु
	अणु"RealTek RTL-8029(AS)", REALTEK_FDXपूर्ण,
	अणु"Winbond 89C940", 0पूर्ण,
	अणु"Compex RL2000", 0पूर्ण,
	अणु"KTI ET32P2", 0पूर्ण,
	अणु"NetVin NV5000SC", 0पूर्ण,
	अणु"Via 86C926", ONLY_16BIT_IOपूर्ण,
	अणु"SureCom NE34", 0पूर्ण,
	अणु"Winbond W89C940F", 0पूर्ण,
	अणु"Holtek HT80232", ONLY_16BIT_IO | HOLTEK_FDXपूर्ण,
	अणु"Holtek HT80229", ONLY_32BIT_IO | HOLTEK_FDX | STOP_PG_0x60 पूर्ण,
	अणु"Winbond W89C940(misprogrammed)", 0पूर्ण,
	अणुशून्य,पूर्ण
पूर्ण;


अटल स्थिर काष्ठा pci_device_id ne2k_pci_tbl[] = अणु
	अणु 0x10ec, 0x8029, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_RealTek_RTL_8029 पूर्ण,
	अणु 0x1050, 0x0940, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_Winbond_89C940 पूर्ण,
	अणु 0x11f6, 0x1401, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_Compex_RL2000 पूर्ण,
	अणु 0x8e2e, 0x3000, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_KTI_ET32P2 पूर्ण,
	अणु 0x4a14, 0x5000, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_NetVin_NV5000SC पूर्ण,
	अणु 0x1106, 0x0926, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_Via_86C926 पूर्ण,
	अणु 0x10bd, 0x0e34, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_SureCom_NE34 पूर्ण,
	अणु 0x1050, 0x5a5a, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_Winbond_W89C940F पूर्ण,
	अणु 0x12c3, 0x0058, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_Holtek_HT80232 पूर्ण,
	अणु 0x12c3, 0x5598, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_Holtek_HT80229 पूर्ण,
	अणु 0x8c4a, 0x1980, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_Winbond_89C940_8c4a पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ne2k_pci_tbl);


/* ---- No user-serviceable parts below ---- */

#घोषणा NE_BASE	 (dev->base_addr)
#घोषणा NE_CMD		0x00
#घोषणा NE_DATAPORT	0x10	/* NatSemi-defined port winकरोw offset. */
#घोषणा NE_RESET	0x1f	/* Issue a पढ़ो to reset, a ग_लिखो to clear. */
#घोषणा NE_IO_EXTENT	0x20

#घोषणा NESM_START_PG	0x40	/* First page of TX buffer */
#घोषणा NESM_STOP_PG	0x80	/* Last page +1 of RX ring */


अटल पूर्णांक ne2k_pci_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक ne2k_pci_बंद(काष्ठा net_device *dev);

अटल व्योम ne2k_pci_reset_8390(काष्ठा net_device *dev);
अटल व्योम ne2k_pci_get_8390_hdr(काष्ठा net_device *dev,
				  काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page);
अटल व्योम ne2k_pci_block_input(काष्ठा net_device *dev, पूर्णांक count,
				 काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम ne2k_pci_block_output(काष्ठा net_device *dev, स्थिर पूर्णांक count,
				  स्थिर अचिन्हित अक्षर *buf,
				  स्थिर पूर्णांक start_page);
अटल स्थिर काष्ठा ethtool_ops ne2k_pci_ethtool_ops;



/* There is no room in the standard 8390 काष्ठाure क्रम extra info we need,
 * so we build a meta/outer-wrapper काष्ठाure..
 */
काष्ठा ne2k_pci_card अणु
	काष्ठा net_device *dev;
	काष्ठा pci_dev *pci_dev;
पूर्ण;



/* NEx000-clone boards have a Station Address (SA) PROM (SAPROM) in the packet
 * buffer memory space.  By-the-spec NE2000 clones have 0x57,0x57 in bytes
 * 0x0e,0x0f of the SAPROM, जबतक other supposed NE2000 clones must be
 * detected by their SA prefix.
 *
 * Reading the SAPROM from a word-wide card with the 8390 set in byte-wide
 * mode results in द्विगुनd values, which can be detected and compensated क्रम.
 *
 * The probe is also responsible क्रम initializing the card and filling
 * in the 'dev' and 'ei_status' काष्ठाures.
 */

अटल स्थिर काष्ठा net_device_ops ne2k_netdev_ops = अणु
	.nकरो_खोलो		= ne2k_pci_खोलो,
	.nकरो_stop		= ne2k_pci_बंद,
	.nकरो_start_xmit		= ei_start_xmit,
	.nकरो_tx_समयout		= ei_tx_समयout,
	.nकरो_get_stats		= ei_get_stats,
	.nकरो_set_rx_mode	= ei_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = ei_poll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक ne2k_pci_init_one(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	पूर्णांक i;
	अचिन्हित अक्षर SA_prom[32];
	पूर्णांक start_page, stop_page;
	पूर्णांक irq, reg0, chip_idx = ent->driver_data;
	अटल अचिन्हित पूर्णांक fnd_cnt;
	दीर्घ ioaddr;
	पूर्णांक flags = pci_clone_list[chip_idx].flags;
	काष्ठा ei_device *ei_local;

	fnd_cnt++;

	i = pci_enable_device(pdev);
	अगर (i)
		वापस i;

	ioaddr = pci_resource_start(pdev, 0);
	irq = pdev->irq;

	अगर (!ioaddr || ((pci_resource_flags(pdev, 0) & IORESOURCE_IO) == 0)) अणु
		dev_err(&pdev->dev, "no I/O resource at PCI BAR #0\n");
		जाओ err_out;
	पूर्ण

	अगर (!request_region(ioaddr, NE_IO_EXTENT, DRV_NAME)) अणु
		dev_err(&pdev->dev, "I/O resource 0x%x @ 0x%lx busy\n",
			NE_IO_EXTENT, ioaddr);
		जाओ err_out;
	पूर्ण

	reg0 = inb(ioaddr);
	अगर (reg0 == 0xFF)
		जाओ err_out_मुक्त_res;

	/* Do a preliminary verअगरication that we have a 8390. */
	अणु
		पूर्णांक regd;

		outb(E8390_NODMA + E8390_PAGE1 + E8390_STOP, ioaddr + E8390_CMD);
		regd = inb(ioaddr + 0x0d);
		outb(0xff, ioaddr + 0x0d);
		outb(E8390_NODMA + E8390_PAGE0, ioaddr + E8390_CMD);
		/* Clear the counter by पढ़ोing. */
		inb(ioaddr + EN0_COUNTER0);
		अगर (inb(ioaddr + EN0_COUNTER0) != 0) अणु
			outb(reg0, ioaddr);
			/*  Restore the old values. */
			outb(regd, ioaddr + 0x0d);
			जाओ err_out_मुक्त_res;
		पूर्ण
	पूर्ण

	/* Allocate net_device, dev->priv; fill in 8390 specअगरic dev fields. */
	dev = alloc_ei_netdev();
	अगर (!dev) अणु
		dev_err(&pdev->dev, "cannot allocate ethernet device\n");
		जाओ err_out_मुक्त_res;
	पूर्ण
	dev->netdev_ops = &ne2k_netdev_ops;
	ei_local = netdev_priv(dev);
	ei_local->msg_enable = netअगर_msg_init(ne2k_msg_enable, शेष_msg_level);

	SET_NETDEV_DEV(dev, &pdev->dev);

	/* Reset card. Who knows what dain-bramaged state it was left in. */
	अणु
		अचिन्हित दीर्घ reset_start_समय = jअगरfies;

		outb(inb(ioaddr + NE_RESET), ioaddr + NE_RESET);

		/* This looks like a horrible timing loop, but it should never
		 * take more than a few cycles.
		 */
		जबतक ((inb(ioaddr + EN0_ISR) & ENISR_RESET) == 0)
			/* Limit रुको: '2' aव्योमs jअगरfy roll-over. */
			अगर (jअगरfies - reset_start_समय > 2) अणु
				dev_err(&pdev->dev,
					"Card failure (no reset ack).\n");
				जाओ err_out_मुक्त_netdev;
			पूर्ण
		/* Ack all पूर्णांकr. */
		outb(0xff, ioaddr + EN0_ISR);
	पूर्ण

	/* Read the 16 bytes of station address PROM.
	 * We must first initialize रेजिस्टरs, similar
	 * to NS8390_init(eअगरdev, 0).
	 * We can't reliably पढ़ो the SAPROM address without this.
	 * (I learned the hard way!).
	 */
	अणु
		काष्ठा अणुअचिन्हित अक्षर value, offset; पूर्ण program_seq[] = अणु
			/* Select page 0 */
			अणुE8390_NODMA + E8390_PAGE0 + E8390_STOP, E8390_CMDपूर्ण,
			/* Set word-wide access */
			अणु0x49,	EN0_DCFGपूर्ण,
			/* Clear the count regs. */
			अणु0x00,	EN0_RCNTLOपूर्ण,
			/* Mask completion IRQ */
			अणु0x00,	EN0_RCNTHIपूर्ण,
			अणु0x00,	EN0_IMRपूर्ण,
			अणु0xFF,	EN0_ISRपूर्ण,
			/* 0x20 Set to monitor */
			अणुE8390_RXOFF, EN0_RXCRपूर्ण,
			/* 0x02 and loopback mode */
			अणुE8390_TXOFF, EN0_TXCRपूर्ण,
			अणु32,	EN0_RCNTLOपूर्ण,
			अणु0x00,	EN0_RCNTHIपूर्ण,
			/* DMA starting at 0x0000 */
			अणु0x00,	EN0_RSARLOपूर्ण,
			अणु0x00,	EN0_RSARHIपूर्ण,
			अणुE8390_RREAD+E8390_START, E8390_CMDपूर्ण,
		पूर्ण;
		क्रम (i = 0; i < ARRAY_SIZE(program_seq); i++)
			outb(program_seq[i].value,
			     ioaddr + program_seq[i].offset);

	पूर्ण

	/* Note: all PCI cards have at least 16 bit access, so we करोn't have
	 * to check क्रम 8 bit cards.  Most cards permit 32 bit access.
	 */
	अगर (flags & ONLY_32BIT_IO) अणु
		क्रम (i = 0; i < 4 ; i++)
			((u32 *)SA_prom)[i] = le32_to_cpu(inl(ioaddr + NE_DATAPORT));
	पूर्ण अन्यथा
		क्रम (i = 0; i < 32 /* माप(SA_prom )*/; i++)
			SA_prom[i] = inb(ioaddr + NE_DATAPORT);

	/* We always set the 8390 रेजिस्टरs क्रम word mode. */
	outb(0x49, ioaddr + EN0_DCFG);
	start_page = NESM_START_PG;

	stop_page = flags & STOP_PG_0x60 ? 0x60 : NESM_STOP_PG;

	/* Set up the rest of the parameters. */
	dev->irq = irq;
	dev->base_addr = ioaddr;
	pci_set_drvdata(pdev, dev);

	ei_status.name = pci_clone_list[chip_idx].name;
	ei_status.tx_start_page = start_page;
	ei_status.stop_page = stop_page;
	ei_status.word16 = 1;
	ei_status.ne2k_flags = flags;
	अगर (fnd_cnt < MAX_UNITS) अणु
		अगर (full_duplex[fnd_cnt] > 0 || (options[fnd_cnt] & FORCE_FDX))
			ei_status.ne2k_flags |= FORCE_FDX;
	पूर्ण

	ei_status.rx_start_page = start_page + TX_PAGES;
#अगर_घोषित PACKETBUF_MEMSIZE
	/* Allow the packet buffer size to be overridden by know-it-alls. */
	ei_status.stop_page = ei_status.tx_start_page + PACKETBUF_MEMSIZE;
#पूर्ण_अगर

	ei_status.reset_8390 = &ne2k_pci_reset_8390;
	ei_status.block_input = &ne2k_pci_block_input;
	ei_status.block_output = &ne2k_pci_block_output;
	ei_status.get_8390_hdr = &ne2k_pci_get_8390_hdr;
	ei_status.priv = (अचिन्हित दीर्घ) pdev;

	dev->ethtool_ops = &ne2k_pci_ethtool_ops;
	NS8390_init(dev, 0);

	स_नकल(dev->dev_addr, SA_prom, dev->addr_len);

	i = रेजिस्टर_netdev(dev);
	अगर (i)
		जाओ err_out_मुक्त_netdev;

	netdev_info(dev, "%s found at %#lx, IRQ %d, %pM.\n",
		    pci_clone_list[chip_idx].name, ioaddr, dev->irq,
		    dev->dev_addr);

	वापस 0;

err_out_मुक्त_netdev:
	मुक्त_netdev(dev);
err_out_मुक्त_res:
	release_region(ioaddr, NE_IO_EXTENT);
err_out:
	pci_disable_device(pdev);
	वापस -ENODEV;
पूर्ण

/* Magic incantation sequence क्रम full duplex on the supported cards.
 */
अटल अंतरभूत पूर्णांक set_realtek_fdx(काष्ठा net_device *dev)
अणु
	दीर्घ ioaddr = dev->base_addr;

	outb(0xC0 + E8390_NODMA, ioaddr + NE_CMD); /* Page 3 */
	outb(0xC0, ioaddr + 0x01); /* Enable ग_लिखोs to CONFIG3 */
	outb(0x40, ioaddr + 0x06); /* Enable full duplex */
	outb(0x00, ioaddr + 0x01); /* Disable ग_लिखोs to CONFIG3 */
	outb(E8390_PAGE0 + E8390_NODMA, ioaddr + NE_CMD); /* Page 0 */
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक set_holtek_fdx(काष्ठा net_device *dev)
अणु
	दीर्घ ioaddr = dev->base_addr;

	outb(inb(ioaddr + 0x20) | 0x80, ioaddr + 0x20);
	वापस 0;
पूर्ण

अटल पूर्णांक ne2k_pci_set_fdx(काष्ठा net_device *dev)
अणु
	अगर (ei_status.ne2k_flags & REALTEK_FDX)
		वापस set_realtek_fdx(dev);
	अन्यथा अगर (ei_status.ne2k_flags & HOLTEK_FDX)
		वापस set_holtek_fdx(dev);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ne2k_pci_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक ret = request_irq(dev->irq, ei_पूर्णांकerrupt, IRQF_SHARED,
			      dev->name, dev);

	अगर (ret)
		वापस ret;

	अगर (ei_status.ne2k_flags & FORCE_FDX)
		ne2k_pci_set_fdx(dev);

	ei_खोलो(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक ne2k_pci_बंद(काष्ठा net_device *dev)
अणु
	ei_बंद(dev);
	मुक्त_irq(dev->irq, dev);
	वापस 0;
पूर्ण

/* Hard reset the card.  This used to छोड़ो क्रम the same period that a
 * 8390 reset command required, but that shouldn't be necessary.
 */
अटल व्योम ne2k_pci_reset_8390(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ reset_start_समय = jअगरfies;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	netअगर_dbg(ei_local, hw, dev, "resetting the 8390 t=%ld...\n",
		  jअगरfies);

	outb(inb(NE_BASE + NE_RESET), NE_BASE + NE_RESET);

	ei_status.txing = 0;
	ei_status.dमुख्यg = 0;

	/* This check _should_not_ be necessary, omit eventually. */
	जबतक ((inb(NE_BASE+EN0_ISR) & ENISR_RESET) == 0)
		अगर (jअगरfies - reset_start_समय > 2) अणु
			netdev_err(dev, "%s did not complete.\n", __func__);
			अवरोध;
		पूर्ण
	/* Ack पूर्णांकr. */
	outb(ENISR_RESET, NE_BASE + EN0_ISR);
पूर्ण

/* Grab the 8390 specअगरic header. Similar to the block_input routine, but
 * we करोn't need to be concerned with ring wrap as the header will be at
 * the start of a page, so we optimize accordingly.
 */

अटल व्योम ne2k_pci_get_8390_hdr(काष्ठा net_device *dev,
				  काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु

	दीर्घ nic_base = dev->base_addr;

	/* This *shouldn't* happen. If it does, it's the last thing you'll see
	 */
	अगर (ei_status.dमुख्यg) अणु
		netdev_err(dev, "DMAing conflict in %s [DMAstat:%d][irqlock:%d].\n",
			   __func__, ei_status.dमुख्यg, ei_status.irqlock);
		वापस;
	पूर्ण

	ei_status.dमुख्यg |= 0x01;
	outb(E8390_NODMA + E8390_PAGE0 + E8390_START, nic_base + NE_CMD);
	outb(माप(काष्ठा e8390_pkt_hdr), nic_base + EN0_RCNTLO);
	outb(0, nic_base + EN0_RCNTHI);
	outb(0, nic_base + EN0_RSARLO);		/* On page boundary */
	outb(ring_page, nic_base + EN0_RSARHI);
	outb(E8390_RREAD+E8390_START, nic_base + NE_CMD);

	अगर (ei_status.ne2k_flags & ONLY_16BIT_IO) अणु
		insw(NE_BASE + NE_DATAPORT, hdr,
		     माप(काष्ठा e8390_pkt_hdr) >> 1);
	पूर्ण अन्यथा अणु
		*(u32 *)hdr = le32_to_cpu(inl(NE_BASE + NE_DATAPORT));
		le16_to_cpus(&hdr->count);
	पूर्ण
	/* Ack पूर्णांकr. */
	outb(ENISR_RDC, nic_base + EN0_ISR);
	ei_status.dमुख्यg &= ~0x01;
पूर्ण

/* Block input and output, similar to the Crynwr packet driver.  If you
 *are porting to a new ethercard, look at the packet driver source क्रम hपूर्णांकs.
 *The NEx000 करोesn't share the on-board packet memory -- you have to put
 *the packet out through the "remote DMA" dataport using outb.
 */

अटल व्योम ne2k_pci_block_input(काष्ठा net_device *dev, पूर्णांक count,
				 काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	दीर्घ nic_base = dev->base_addr;
	अक्षर *buf = skb->data;

	/* This *shouldn't* happen.
	 * If it करोes, it's the last thing you'll see.
	 */
	अगर (ei_status.dमुख्यg) अणु
		netdev_err(dev, "DMAing conflict in %s [DMAstat:%d][irqlock:%d]\n",
			   __func__, ei_status.dमुख्यg, ei_status.irqlock);
		वापस;
	पूर्ण
	ei_status.dमुख्यg |= 0x01;
	अगर (ei_status.ne2k_flags & ONLY_32BIT_IO)
		count = (count + 3) & 0xFFFC;
	outb(E8390_NODMA + E8390_PAGE0 + E8390_START, nic_base + NE_CMD);
	outb(count & 0xff, nic_base + EN0_RCNTLO);
	outb(count >> 8, nic_base + EN0_RCNTHI);
	outb(ring_offset & 0xff, nic_base + EN0_RSARLO);
	outb(ring_offset >> 8, nic_base + EN0_RSARHI);
	outb(E8390_RREAD + E8390_START, nic_base + NE_CMD);

	अगर (ei_status.ne2k_flags & ONLY_16BIT_IO) अणु
		insw(NE_BASE + NE_DATAPORT, buf, count >> 1);
		अगर (count & 0x01)
			buf[count-1] = inb(NE_BASE + NE_DATAPORT);
	पूर्ण अन्यथा अणु
		insl(NE_BASE + NE_DATAPORT, buf, count >> 2);
		अगर (count & 3) अणु
			buf += count & ~3;
			अगर (count & 2) अणु
				__le16 *b = (__le16 *)buf;

				*b++ = cpu_to_le16(inw(NE_BASE + NE_DATAPORT));
				buf = (अक्षर *)b;
			पूर्ण
			अगर (count & 1)
				*buf = inb(NE_BASE + NE_DATAPORT);
		पूर्ण
	पूर्ण
	/* Ack पूर्णांकr. */
	outb(ENISR_RDC, nic_base + EN0_ISR);
	ei_status.dमुख्यg &= ~0x01;
पूर्ण

अटल व्योम ne2k_pci_block_output(काष्ठा net_device *dev, पूर्णांक count,
		स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page)
अणु
	दीर्घ nic_base = NE_BASE;
	अचिन्हित दीर्घ dma_start;

	/* On little-endian it's always safe to round the count up क्रम
	 * word ग_लिखोs.
	 */
	अगर (ei_status.ne2k_flags & ONLY_32BIT_IO)
		count = (count + 3) & 0xFFFC;
	अन्यथा
		अगर (count & 0x01)
			count++;

	/* This *shouldn't* happen.
	 * If it करोes, it's the last thing you'll see.
	 */
	अगर (ei_status.dमुख्यg) अणु
		netdev_err(dev, "DMAing conflict in %s [DMAstat:%d][irqlock:%d]\n",
			   __func__, ei_status.dमुख्यg, ei_status.irqlock);
		वापस;
	पूर्ण
	ei_status.dमुख्यg |= 0x01;
	/* We should alपढ़ोy be in page 0, but to be safe... */
	outb(E8390_PAGE0+E8390_START+E8390_NODMA, nic_base + NE_CMD);

#अगर_घोषित NE_RW_BUGFIX
	/* Handle the पढ़ो-beक्रमe-ग_लिखो bug the same way as the
	 * Crynwr packet driver -- the NatSemi method करोesn't work.
	 * Actually this करोesn't always work either, but अगर you have
	 * problems with your NEx000 this is better than nothing!
	 */
	outb(0x42, nic_base + EN0_RCNTLO);
	outb(0x00, nic_base + EN0_RCNTHI);
	outb(0x42, nic_base + EN0_RSARLO);
	outb(0x00, nic_base + EN0_RSARHI);
	outb(E8390_RREAD+E8390_START, nic_base + NE_CMD);
#पूर्ण_अगर
	outb(ENISR_RDC, nic_base + EN0_ISR);

	/* Now the normal output. */
	outb(count & 0xff, nic_base + EN0_RCNTLO);
	outb(count >> 8,   nic_base + EN0_RCNTHI);
	outb(0x00, nic_base + EN0_RSARLO);
	outb(start_page, nic_base + EN0_RSARHI);
	outb(E8390_RWRITE+E8390_START, nic_base + NE_CMD);
	अगर (ei_status.ne2k_flags & ONLY_16BIT_IO) अणु
		outsw(NE_BASE + NE_DATAPORT, buf, count >> 1);
	पूर्ण अन्यथा अणु
		outsl(NE_BASE + NE_DATAPORT, buf, count >> 2);
		अगर (count & 3) अणु
			buf += count & ~3;
			अगर (count & 2) अणु
				__le16 *b = (__le16 *)buf;

				outw(le16_to_cpu(*b++), NE_BASE + NE_DATAPORT);
				buf = (अक्षर *)b;
			पूर्ण
		पूर्ण
	पूर्ण

	dma_start = jअगरfies;

	जबतक ((inb(nic_base + EN0_ISR) & ENISR_RDC) == 0)
		/* Aव्योम घड़ी roll-over. */
		अगर (jअगरfies - dma_start > 2) अणु
			netdev_warn(dev, "timeout waiting for Tx RDC.\n");
			ne2k_pci_reset_8390(dev);
			NS8390_init(dev, 1);
			अवरोध;
		पूर्ण
	/* Ack पूर्णांकr. */
	outb(ENISR_RDC, nic_base + EN0_ISR);
	ei_status.dमुख्यg &= ~0x01;
पूर्ण

अटल व्योम ne2k_pci_get_drvinfo(काष्ठा net_device *dev,
				 काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा ei_device *ei = netdev_priv(dev);
	काष्ठा pci_dev *pci_dev = (काष्ठा pci_dev *) ei->priv;

	strscpy(info->driver, DRV_NAME, माप(info->driver));
	strscpy(info->version, DRV_VERSION, माप(info->version));
	strscpy(info->bus_info, pci_name(pci_dev), माप(info->bus_info));
पूर्ण

अटल u32 ne2k_pci_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	वापस ei_local->msg_enable;
पूर्ण

अटल व्योम ne2k_pci_set_msglevel(काष्ठा net_device *dev, u32 v)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	ei_local->msg_enable = v;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ne2k_pci_ethtool_ops = अणु
	.get_drvinfo		= ne2k_pci_get_drvinfo,
	.get_msglevel		= ne2k_pci_get_msglevel,
	.set_msglevel		= ne2k_pci_set_msglevel,
पूर्ण;

अटल व्योम ne2k_pci_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	BUG_ON(!dev);
	unरेजिस्टर_netdev(dev);
	release_region(dev->base_addr, NE_IO_EXTENT);
	मुक्त_netdev(dev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused ne2k_pci_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ne2k_pci_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	NS8390_init(dev, 1);
	netअगर_device_attach(dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ne2k_pci_pm_ops, ne2k_pci_suspend, ne2k_pci_resume);

अटल काष्ठा pci_driver ne2k_driver = अणु
	.name		= DRV_NAME,
	.probe		= ne2k_pci_init_one,
	.हटाओ		= ne2k_pci_हटाओ_one,
	.id_table	= ne2k_pci_tbl,
	.driver.pm	= &ne2k_pci_pm_ops,
पूर्ण;


अटल पूर्णांक __init ne2k_pci_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&ne2k_driver);
पूर्ण


अटल व्योम __निकास ne2k_pci_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ne2k_driver);
पूर्ण

module_init(ne2k_pci_init);
module_निकास(ne2k_pci_cleanup);
