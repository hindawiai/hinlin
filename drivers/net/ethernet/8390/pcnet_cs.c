<शैली गुरु>
/*======================================================================

    A PCMCIA ethernet driver क्रम NS8390-based cards

    This driver supports the D-Link DE-650 and Linksys EthernetCard
    cards, the newer D-Link and Linksys combo cards, Accton EN2212
    cards, the RPTI EP400, and the PreMax PE-200 in non-shared-memory
    mode, and the IBM Credit Card Adapter, the NE4100, the Thomas
    Conrad ethernet card, and the Kingston KNE-PCM/x in shared-memory
    mode.  It will also handle the Socket EA card in either mode.

    Copyright (C) 1999 David A. Hinds -- dahinds@users.sourceक्रमge.net

    pcnet_cs.c 1.153 2003/11/09 18:53:09

    The network driver code is based on Donald Becker's NE2000 code:

    Written 1992,1993 by Donald Becker.
    Copyright 1993 United States Government as represented by the
    Director, National Security Agency.  This software may be used and
    distributed according to the terms of the GNU General Public License,
    incorporated herein by reference.
    Donald Becker may be reached at becker@scyld.com

    Based also on Keith Moore's changes to Don Becker's code, क्रम IBM
    CCAE support.  Drivers merged back together, and shared-memory
    Socket EA support added, by Ken Raeburn, September 1995.

======================================================================*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/log2.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mii.h>
#समावेश "8390.h"

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/cisreg.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>

#घोषणा PCNET_CMD	0x00
#घोषणा PCNET_DATAPORT	0x10	/* NatSemi-defined port winकरोw offset. */
#घोषणा PCNET_RESET	0x1f	/* Issue a पढ़ो to reset, a ग_लिखो to clear. */
#घोषणा PCNET_MISC	0x18	/* For IBM CCAE and Socket EA cards */

#घोषणा PCNET_START_PG	0x40	/* First page of TX buffer */
#घोषणा PCNET_STOP_PG	0x80	/* Last page +1 of RX ring */

/* Socket EA cards have a larger packet buffer */
#घोषणा SOCKET_START_PG	0x01
#घोषणा SOCKET_STOP_PG	0xff

#घोषणा PCNET_RDC_TIMEOUT (2*HZ/100)	/* Max रुको in jअगरfies क्रम Tx RDC */

अटल स्थिर अक्षर *अगर_names[] = अणु "auto", "10baseT", "10base2"पूर्ण;

/*====================================================================*/

/* Module parameters */

MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("NE2000 compatible PCMCIA ethernet driver");
MODULE_LICENSE("GPL");

#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v; module_param(n, पूर्णांक, 0)

INT_MODULE_PARM(अगर_port,	1);	/* Transceiver type */
INT_MODULE_PARM(use_big_buf,	1);	/* use 64K packet buffer? */
INT_MODULE_PARM(mem_speed,	0);	/* shared mem speed, in ns */
INT_MODULE_PARM(delay_output,	0);	/* छोड़ो after xmit? */
INT_MODULE_PARM(delay_समय,	4);	/* in usec */
INT_MODULE_PARM(use_shmem,	-1);	/* use shared memory? */
INT_MODULE_PARM(full_duplex,	0);	/* full duplex? */

/* Ugh!  Let the user hardwire the hardware address क्रम queer cards */
अटल पूर्णांक hw_addr[6] = अणु 0, /* ... */ पूर्ण;
module_param_array(hw_addr, पूर्णांक, शून्य, 0);

/*====================================================================*/

अटल व्योम mii_phy_probe(काष्ठा net_device *dev);
अटल पूर्णांक pcnet_config(काष्ठा pcmcia_device *link);
अटल व्योम pcnet_release(काष्ठा pcmcia_device *link);
अटल पूर्णांक pcnet_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक pcnet_बंद(काष्ठा net_device *dev);
अटल पूर्णांक ei_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल irqवापस_t ei_irq_wrapper(पूर्णांक irq, व्योम *dev_id);
अटल व्योम ei_watchकरोg(काष्ठा समयr_list *t);
अटल व्योम pcnet_reset_8390(काष्ठा net_device *dev);
अटल पूर्णांक set_config(काष्ठा net_device *dev, काष्ठा अगरmap *map);
अटल पूर्णांक setup_shmem_winकरोw(काष्ठा pcmcia_device *link, पूर्णांक start_pg,
			      पूर्णांक stop_pg, पूर्णांक cm_offset);
अटल पूर्णांक setup_dma_config(काष्ठा pcmcia_device *link, पूर्णांक start_pg,
			    पूर्णांक stop_pg);

अटल व्योम pcnet_detach(काष्ठा pcmcia_device *p_dev);

/*====================================================================*/

काष्ठा hw_info अणु
    u_पूर्णांक	offset;
    u_अक्षर	a0, a1, a2;
    u_पूर्णांक	flags;
पूर्ण;

#घोषणा DELAY_OUTPUT	0x01
#घोषणा HAS_MISC_REG	0x02
#घोषणा USE_BIG_BUF	0x04
#घोषणा HAS_IBM_MISC	0x08
#घोषणा IS_DL10019	0x10
#घोषणा IS_DL10022	0x20
#घोषणा HAS_MII		0x40
#घोषणा USE_SHMEM	0x80	/* स्वतःdetected */

#घोषणा AM79C9XX_HOME_PHY	0x00006B90  /* HomePNA PHY */
#घोषणा AM79C9XX_ETH_PHY	0x00006B70  /* 10baseT PHY */
#घोषणा MII_PHYID_REV_MASK	0xfffffff0
#घोषणा MII_PHYID_REG1		0x02
#घोषणा MII_PHYID_REG2		0x03

अटल काष्ठा hw_info hw_info[] = अणु
    अणु /* Accton EN2212 */ 0x0ff0, 0x00, 0x00, 0xe8, DELAY_OUTPUT पूर्ण,
    अणु /* Allied Telesis LA-PCM */ 0x0ff0, 0x00, 0x00, 0xf4, 0 पूर्ण,
    अणु /* APEX MultiCard */ 0x03f4, 0x00, 0x20, 0xe5, 0 पूर्ण,
    अणु /* ASANTE FriendlyNet */ 0x4910, 0x00, 0x00, 0x94,
      DELAY_OUTPUT | HAS_IBM_MISC पूर्ण,
    अणु /* Danpex EN-6200P2 */ 0x0110, 0x00, 0x40, 0xc7, 0 पूर्ण,
    अणु /* DataTrek NetCard */ 0x0ff0, 0x00, 0x20, 0xe8, 0 पूर्ण,
    अणु /* Dayna CommuniCard E */ 0x0110, 0x00, 0x80, 0x19, 0 पूर्ण,
    अणु /* D-Link DE-650 */ 0x0040, 0x00, 0x80, 0xc8, 0 पूर्ण,
    अणु /* EP-210 Ethernet */ 0x0110, 0x00, 0x40, 0x33, 0 पूर्ण,
    अणु /* EP4000 Ethernet */ 0x01c0, 0x00, 0x00, 0xb4, 0 पूर्ण,
    अणु /* Epson EEN10B */ 0x0ff0, 0x00, 0x00, 0x48,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* ELECOM Laneed LD-CDWA */ 0xb8, 0x08, 0x00, 0x42, 0 पूर्ण,
    अणु /* Hypertec Ethernet */ 0x01c0, 0x00, 0x40, 0x4c, 0 पूर्ण,
    अणु /* IBM CCAE */ 0x0ff0, 0x08, 0x00, 0x5a,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* IBM CCAE */ 0x0ff0, 0x00, 0x04, 0xac,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* IBM CCAE */ 0x0ff0, 0x00, 0x06, 0x29,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* IBM FME */ 0x0374, 0x08, 0x00, 0x5a,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* IBM FME */ 0x0374, 0x00, 0x04, 0xac,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* Kansai KLA-PCM/T */ 0x0ff0, 0x00, 0x60, 0x87,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* NSC DP83903 */ 0x0374, 0x08, 0x00, 0x17,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* NSC DP83903 */ 0x0374, 0x00, 0xc0, 0xa8,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* NSC DP83903 */ 0x0374, 0x00, 0xa0, 0xb0,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* NSC DP83903 */ 0x0198, 0x00, 0x20, 0xe0,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* I-O DATA PCLA/T */ 0x0ff0, 0x00, 0xa0, 0xb0, 0 पूर्ण,
    अणु /* Katron PE-520 */ 0x0110, 0x00, 0x40, 0xf6, 0 पूर्ण,
    अणु /* Kingston KNE-PCM/x */ 0x0ff0, 0x00, 0xc0, 0xf0,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* Kingston KNE-PCM/x */ 0x0ff0, 0xe2, 0x0c, 0x0f,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* Kingston KNE-PC2 */ 0x0180, 0x00, 0xc0, 0xf0, 0 पूर्ण,
    अणु /* Maxtech PCN2000 */ 0x5000, 0x00, 0x00, 0xe8, 0 पूर्ण,
    अणु /* NDC Instant-Link */ 0x003a, 0x00, 0x80, 0xc6, 0 पूर्ण,
    अणु /* NE2000 Compatible */ 0x0ff0, 0x00, 0xa0, 0x0c, 0 पूर्ण,
    अणु /* Network General Snअगरfer */ 0x0ff0, 0x00, 0x00, 0x65,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* Panasonic VEL211 */ 0x0ff0, 0x00, 0x80, 0x45,
      HAS_MISC_REG | HAS_IBM_MISC पूर्ण,
    अणु /* PreMax PE-200 */ 0x07f0, 0x00, 0x20, 0xe0, 0 पूर्ण,
    अणु /* RPTI EP400 */ 0x0110, 0x00, 0x40, 0x95, 0 पूर्ण,
    अणु /* SCM Ethernet */ 0x0ff0, 0x00, 0x20, 0xcb, 0 पूर्ण,
    अणु /* Socket EA */ 0x4000, 0x00, 0xc0, 0x1b,
      DELAY_OUTPUT | HAS_MISC_REG | USE_BIG_BUF पूर्ण,
    अणु /* Socket LP-E CF+ */ 0x01c0, 0x00, 0xc0, 0x1b, 0 पूर्ण,
    अणु /* SuperSocket RE450T */ 0x0110, 0x00, 0xe0, 0x98, 0 पूर्ण,
    अणु /* Volktek NPL-402CT */ 0x0060, 0x00, 0x40, 0x05, 0 पूर्ण,
    अणु /* NEC PC-9801N-J12 */ 0x0ff0, 0x00, 0x00, 0x4c, 0 पूर्ण,
    अणु /* PCMCIA Technology OEM */ 0x01c8, 0x00, 0xa0, 0x0c, 0 पूर्ण
पूर्ण;

#घोषणा NR_INFO		ARRAY_SIZE(hw_info)

अटल काष्ठा hw_info शेष_info = अणु 0, 0, 0, 0, 0 पूर्ण;
अटल काष्ठा hw_info dl10019_info = अणु 0, 0, 0, 0, IS_DL10019|HAS_MII पूर्ण;
अटल काष्ठा hw_info dl10022_info = अणु 0, 0, 0, 0, IS_DL10022|HAS_MII पूर्ण;

काष्ठा pcnet_dev अणु
	काष्ठा pcmcia_device	*p_dev;
    u_पूर्णांक		flags;
    व्योम		__iomem *base;
    काष्ठा समयr_list	watchकरोg;
    पूर्णांक			stale, fast_poll;
    u_अक्षर		phy_id;
    u_अक्षर		eth_phy, pna_phy;
    u_लघु		link_status;
    u_दीर्घ		mii_reset;
पूर्ण;

अटल अंतरभूत काष्ठा pcnet_dev *PRIV(काष्ठा net_device *dev)
अणु
	अक्षर *p = netdev_priv(dev);
	वापस (काष्ठा pcnet_dev *)(p + माप(काष्ठा ei_device));
पूर्ण

अटल स्थिर काष्ठा net_device_ops pcnet_netdev_ops = अणु
	.nकरो_खोलो		= pcnet_खोलो,
	.nकरो_stop		= pcnet_बंद,
	.nकरो_set_config		= set_config,
	.nकरो_start_xmit 	= ei_start_xmit,
	.nकरो_get_stats		= ei_get_stats,
	.nकरो_करो_ioctl 		= ei_ioctl,
	.nकरो_set_rx_mode	= ei_set_multicast_list,
	.nकरो_tx_समयout 	= ei_tx_समयout,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller 	= ei_poll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक pcnet_probe(काष्ठा pcmcia_device *link)
अणु
    काष्ठा pcnet_dev *info;
    काष्ठा net_device *dev;

    dev_dbg(&link->dev, "pcnet_attach()\n");

    /* Create new ethernet device */
    dev = __alloc_ei_netdev(माप(काष्ठा pcnet_dev));
    अगर (!dev) वापस -ENOMEM;
    info = PRIV(dev);
    info->p_dev = link;
    link->priv = dev;

    link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

    dev->netdev_ops = &pcnet_netdev_ops;

    वापस pcnet_config(link);
पूर्ण /* pcnet_attach */

अटल व्योम pcnet_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	dev_dbg(&link->dev, "pcnet_detach\n");

	unरेजिस्टर_netdev(dev);

	pcnet_release(link);

	मुक्त_netdev(dev);
पूर्ण /* pcnet_detach */

/*======================================================================

    This probes क्रम a card's hardware address, क्रम card types that
    encode this inक्रमmation in their CIS.

======================================================================*/

अटल काष्ठा hw_info *get_hwinfo(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    u_अक्षर __iomem *base, *virt;
    पूर्णांक i, j;

    /* Allocate a small memory winकरोw */
    link->resource[2]->flags |= WIN_DATA_WIDTH_8|WIN_MEMORY_TYPE_AM|WIN_ENABLE;
    link->resource[2]->start = 0; link->resource[2]->end = 0;
    i = pcmcia_request_winकरोw(link, link->resource[2], 0);
    अगर (i != 0)
	वापस शून्य;

    virt = ioremap(link->resource[2]->start,
	    resource_size(link->resource[2]));
    अगर (unlikely(!virt)) अणु
	    pcmcia_release_winकरोw(link, link->resource[2]);
	    वापस शून्य;
    पूर्ण

    क्रम (i = 0; i < NR_INFO; i++) अणु
	pcmcia_map_mem_page(link, link->resource[2],
		hw_info[i].offset & ~(resource_size(link->resource[2])-1));
	base = &virt[hw_info[i].offset & (resource_size(link->resource[2])-1)];
	अगर ((पढ़ोb(base+0) == hw_info[i].a0) &&
	    (पढ़ोb(base+2) == hw_info[i].a1) &&
	    (पढ़ोb(base+4) == hw_info[i].a2)) अणु
		क्रम (j = 0; j < 6; j++)
		    dev->dev_addr[j] = पढ़ोb(base + (j<<1));
		अवरोध;
	पूर्ण
    पूर्ण

    iounmap(virt);
    j = pcmcia_release_winकरोw(link, link->resource[2]);
    वापस (i < NR_INFO) ? hw_info+i : शून्य;
पूर्ण /* get_hwinfo */

/*======================================================================

    This probes क्रम a card's hardware address by पढ़ोing the PROM.
    It checks the address against a list of known types, then falls
    back to a simple NE2000 clone signature check.

======================================================================*/

अटल काष्ठा hw_info *get_prom(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    u_अक्षर prom[32];
    पूर्णांक i, j;

    /* This is lअगरted straight from drivers/net/ethernet/8390/ne.c */
    काष्ठा अणु
	u_अक्षर value, offset;
    पूर्ण program_seq[] = अणु
	अणुE8390_NODMA+E8390_PAGE0+E8390_STOP, E8390_CMDपूर्ण, /* Select page 0*/
	अणु0x48,	EN0_DCFGपूर्ण,	/* Set byte-wide (0x48) access. */
	अणु0x00,	EN0_RCNTLOपूर्ण,	/* Clear the count regs. */
	अणु0x00,	EN0_RCNTHIपूर्ण,
	अणु0x00,	EN0_IMRपूर्ण,	/* Mask completion irq. */
	अणु0xFF,	EN0_ISRपूर्ण,
	अणुE8390_RXOFF, EN0_RXCRपूर्ण,	/* 0x20  Set to monitor */
	अणुE8390_TXOFF, EN0_TXCRपूर्ण,	/* 0x02  and loopback mode. */
	अणु32,	EN0_RCNTLOपूर्ण,
	अणु0x00,	EN0_RCNTHIपूर्ण,
	अणु0x00,	EN0_RSARLOपूर्ण,	/* DMA starting at 0x0000. */
	अणु0x00,	EN0_RSARHIपूर्ण,
	अणुE8390_RREAD+E8390_START, E8390_CMDपूर्ण,
    पूर्ण;

    pcnet_reset_8390(dev);
    mdelay(10);

    क्रम (i = 0; i < ARRAY_SIZE(program_seq); i++)
	outb_p(program_seq[i].value, ioaddr + program_seq[i].offset);

    क्रम (i = 0; i < 32; i++)
	prom[i] = inb(ioaddr + PCNET_DATAPORT);
    क्रम (i = 0; i < NR_INFO; i++) अणु
	अगर ((prom[0] == hw_info[i].a0) &&
	    (prom[2] == hw_info[i].a1) &&
	    (prom[4] == hw_info[i].a2))
	    अवरोध;
    पूर्ण
    अगर ((i < NR_INFO) || ((prom[28] == 0x57) && (prom[30] == 0x57))) अणु
	क्रम (j = 0; j < 6; j++)
	    dev->dev_addr[j] = prom[j<<1];
	वापस (i < NR_INFO) ? hw_info+i : &शेष_info;
    पूर्ण
    वापस शून्य;
पूर्ण /* get_prom */

/*======================================================================

    For DL10019 based cards, like the Linksys EtherFast

======================================================================*/

अटल काष्ठा hw_info *get_dl10019(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    पूर्णांक i;
    u_अक्षर sum;

    क्रम (sum = 0, i = 0x14; i < 0x1c; i++)
	sum += inb_p(dev->base_addr + i);
    अगर (sum != 0xff)
	वापस शून्य;
    क्रम (i = 0; i < 6; i++)
	dev->dev_addr[i] = inb_p(dev->base_addr + 0x14 + i);
    i = inb(dev->base_addr + 0x1f);
    वापस ((i == 0x91)||(i == 0x99)) ? &dl10022_info : &dl10019_info;
पूर्ण

/*======================================================================

    For Asix AX88190 based cards

======================================================================*/

अटल काष्ठा hw_info *get_ax88190(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    पूर्णांक i, j;

    /* Not much of a test, but the alternatives are messy */
    अगर (link->config_base != 0x03c0)
	वापस शून्य;

    outb_p(0x01, ioaddr + EN0_DCFG);	/* Set word-wide access. */
    outb_p(0x00, ioaddr + EN0_RSARLO);	/* DMA starting at 0x0400. */
    outb_p(0x04, ioaddr + EN0_RSARHI);
    outb_p(E8390_RREAD+E8390_START, ioaddr + E8390_CMD);

    क्रम (i = 0; i < 6; i += 2) अणु
	j = inw(ioaddr + PCNET_DATAPORT);
	dev->dev_addr[i] = j & 0xff;
	dev->dev_addr[i+1] = j >> 8;
    पूर्ण
    वापस शून्य;
पूर्ण

/*======================================================================

    This should be totally unnecessary... but when we can't figure
    out the hardware address any other way, we'll let the user hard
    wire it when the module is initialized.

======================================================================*/

अटल काष्ठा hw_info *get_hwired(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    पूर्णांक i;

    क्रम (i = 0; i < 6; i++)
	अगर (hw_addr[i] != 0) अवरोध;
    अगर (i == 6)
	वापस शून्य;

    क्रम (i = 0; i < 6; i++)
	dev->dev_addr[i] = hw_addr[i];

    वापस &शेष_info;
पूर्ण /* get_hwired */

अटल पूर्णांक try_io_port(काष्ठा pcmcia_device *link)
अणु
    पूर्णांक j, ret;
    link->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
    link->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
    अगर (link->resource[0]->end == 32) अणु
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
	अगर (link->resource[1]->end > 0) अणु
	    /* क्रम master/slave multअगरunction cards */
	    link->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;
	पूर्ण
    पूर्ण अन्यथा अणु
	/* This should be two 16-port winकरोws */
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	link->resource[1]->flags |= IO_DATA_PATH_WIDTH_16;
    पूर्ण
    अगर (link->resource[0]->start == 0) अणु
	क्रम (j = 0; j < 0x400; j += 0x20) अणु
	    link->resource[0]->start = j ^ 0x300;
	    link->resource[1]->start = (j ^ 0x300) + 0x10;
	    link->io_lines = 16;
	    ret = pcmcia_request_io(link);
	    अगर (ret == 0)
		    वापस ret;
	पूर्ण
	वापस ret;
    पूर्ण अन्यथा अणु
	वापस pcmcia_request_io(link);
    पूर्ण
पूर्ण

अटल पूर्णांक pcnet_confcheck(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	पूर्णांक *priv = priv_data;
	पूर्णांक try = (*priv & 0x1);

	*priv &= (p_dev->resource[2]->end >= 0x4000) ? 0x10 : ~0x10;

	अगर (p_dev->config_index == 0)
		वापस -EINVAL;

	अगर (p_dev->resource[0]->end + p_dev->resource[1]->end < 32)
		वापस -EINVAL;

	अगर (try)
		p_dev->io_lines = 16;
	वापस try_io_port(p_dev);
पूर्ण

अटल काष्ठा hw_info *pcnet_try_config(काष्ठा pcmcia_device *link,
					पूर्णांक *has_shmem, पूर्णांक try)
अणु
	काष्ठा net_device *dev = link->priv;
	काष्ठा hw_info *local_hw_info;
	काष्ठा pcnet_dev *info = PRIV(dev);
	पूर्णांक priv = try;
	पूर्णांक ret;

	ret = pcmcia_loop_config(link, pcnet_confcheck, &priv);
	अगर (ret) अणु
		dev_warn(&link->dev, "no useable port range found\n");
		वापस शून्य;
	पूर्ण
	*has_shmem = (priv & 0x10);

	अगर (!link->irq)
		वापस शून्य;

	अगर (resource_size(link->resource[1]) == 8)
		link->config_flags |= CONF_ENABLE_SPKR;

	अगर ((link->manf_id == MANFID_IBM) &&
	    (link->card_id == PRODID_IBM_HOME_AND_AWAY))
		link->config_index |= 0x10;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		वापस शून्य;

	dev->irq = link->irq;
	dev->base_addr = link->resource[0]->start;

	अगर (info->flags & HAS_MISC_REG) अणु
		अगर ((अगर_port == 1) || (अगर_port == 2))
			dev->अगर_port = अगर_port;
		अन्यथा
			dev_notice(&link->dev, "invalid if_port requested\n");
	पूर्ण अन्यथा
		dev->अगर_port = 0;

	अगर ((link->config_base == 0x03c0) &&
	    (link->manf_id == 0x149) && (link->card_id == 0xc1ab)) अणु
		dev_info(&link->dev,
			"this is an AX88190 card - use axnet_cs instead.\n");
		वापस शून्य;
	पूर्ण

	local_hw_info = get_hwinfo(link);
	अगर (!local_hw_info)
		local_hw_info = get_prom(link);
	अगर (!local_hw_info)
		local_hw_info = get_dl10019(link);
	अगर (!local_hw_info)
		local_hw_info = get_ax88190(link);
	अगर (!local_hw_info)
		local_hw_info = get_hwired(link);

	वापस local_hw_info;
पूर्ण

अटल पूर्णांक pcnet_config(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    काष्ठा pcnet_dev *info = PRIV(dev);
    पूर्णांक start_pg, stop_pg, cm_offset;
    पूर्णांक has_shmem = 0;
    काष्ठा hw_info *local_hw_info;

    dev_dbg(&link->dev, "pcnet_config\n");

    local_hw_info = pcnet_try_config(link, &has_shmem, 0);
    अगर (!local_hw_info) अणु
	    /* check whether क्रमcing io_lines to 16 helps... */
	    pcmcia_disable_device(link);
	    local_hw_info = pcnet_try_config(link, &has_shmem, 1);
	    अगर (local_hw_info == शून्य) अणु
		    dev_notice(&link->dev, "unable to read hardware net"
			    " address for io base %#3lx\n", dev->base_addr);
		    जाओ failed;
	    पूर्ण
    पूर्ण

    info->flags = local_hw_info->flags;
    /* Check क्रम user overrides */
    info->flags |= (delay_output) ? DELAY_OUTPUT : 0;
    अगर ((link->manf_id == MANFID_SOCKET) &&
	((link->card_id == PRODID_SOCKET_LPE) ||
	 (link->card_id == PRODID_SOCKET_LPE_CF) ||
	 (link->card_id == PRODID_SOCKET_EIO)))
	info->flags &= ~USE_BIG_BUF;
    अगर (!use_big_buf)
	info->flags &= ~USE_BIG_BUF;

    अगर (info->flags & USE_BIG_BUF) अणु
	start_pg = SOCKET_START_PG;
	stop_pg = SOCKET_STOP_PG;
	cm_offset = 0x10000;
    पूर्ण अन्यथा अणु
	start_pg = PCNET_START_PG;
	stop_pg = PCNET_STOP_PG;
	cm_offset = 0;
    पूर्ण

    /* has_shmem is ignored अगर use_shmem != -1 */
    अगर ((use_shmem == 0) || (!has_shmem && (use_shmem == -1)) ||
	(setup_shmem_winकरोw(link, start_pg, stop_pg, cm_offset) != 0))
	setup_dma_config(link, start_pg, stop_pg);

    ei_status.name = "NE2000";
    ei_status.word16 = 1;
    ei_status.reset_8390 = pcnet_reset_8390;

    अगर (info->flags & (IS_DL10019|IS_DL10022))
	mii_phy_probe(dev);

    SET_NETDEV_DEV(dev, &link->dev);

    अगर (रेजिस्टर_netdev(dev) != 0) अणु
	pr_notice("register_netdev() failed\n");
	जाओ failed;
    पूर्ण

    अगर (info->flags & (IS_DL10019|IS_DL10022)) अणु
	u_अक्षर id = inb(dev->base_addr + 0x1a);
	netdev_info(dev, "NE2000 (DL100%d rev %02x): ",
		    (info->flags & IS_DL10022) ? 22 : 19, id);
	अगर (info->pna_phy)
	    pr_cont("PNA, ");
    पूर्ण अन्यथा अणु
	netdev_info(dev, "NE2000 Compatible: ");
    पूर्ण
    pr_cont("io %#3lx, irq %d,", dev->base_addr, dev->irq);
    अगर (info->flags & USE_SHMEM)
	pr_cont(" mem %#5lx,", dev->mem_start);
    अगर (info->flags & HAS_MISC_REG)
	pr_cont(" %s xcvr,", अगर_names[dev->अगर_port]);
    pr_cont(" hw_addr %pM\n", dev->dev_addr);
    वापस 0;

failed:
    pcnet_release(link);
    वापस -ENODEV;
पूर्ण /* pcnet_config */

अटल व्योम pcnet_release(काष्ठा pcmcia_device *link)
अणु
	काष्ठा pcnet_dev *info = PRIV(link->priv);

	dev_dbg(&link->dev, "pcnet_release\n");

	अगर (info->flags & USE_SHMEM)
		iounmap(info->base);

	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक pcnet_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो)
		netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pcnet_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो) अणु
		pcnet_reset_8390(dev);
		NS8390_init(dev, 1);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण


/*======================================================================

    MII पूर्णांकerface support क्रम DL10019 and DL10022 based cards

    On the DL10019, the MII IO direction bit is 0x10; on the DL10022
    it is 0x20.  Setting both bits seems to work on both card types.

======================================================================*/

#घोषणा DLINK_GPIO		0x1c
#घोषणा DLINK_DIAG		0x1d
#घोषणा DLINK_EEPROM		0x1e

#घोषणा MDIO_SHIFT_CLK		0x80
#घोषणा MDIO_DATA_OUT		0x40
#घोषणा MDIO_सूची_WRITE		0x30
#घोषणा MDIO_DATA_WRITE0	(MDIO_सूची_WRITE)
#घोषणा MDIO_DATA_WRITE1	(MDIO_सूची_WRITE | MDIO_DATA_OUT)
#घोषणा MDIO_DATA_READ		0x10
#घोषणा MDIO_MASK		0x0f

अटल व्योम mdio_sync(अचिन्हित पूर्णांक addr)
अणु
    पूर्णांक bits, mask = inb(addr) & MDIO_MASK;
    क्रम (bits = 0; bits < 32; bits++) अणु
	outb(mask | MDIO_DATA_WRITE1, addr);
	outb(mask | MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, addr);
    पूर्ण
पूर्ण

अटल पूर्णांक mdio_पढ़ो(अचिन्हित पूर्णांक addr, पूर्णांक phy_id, पूर्णांक loc)
अणु
    u_पूर्णांक cmd = (0x06<<10)|(phy_id<<5)|loc;
    पूर्णांक i, retval = 0, mask = inb(addr) & MDIO_MASK;

    mdio_sync(addr);
    क्रम (i = 13; i >= 0; i--) अणु
	पूर्णांक dat = (cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
	outb(mask | dat, addr);
	outb(mask | dat | MDIO_SHIFT_CLK, addr);
    पूर्ण
    क्रम (i = 19; i > 0; i--) अणु
	outb(mask, addr);
	retval = (retval << 1) | ((inb(addr) & MDIO_DATA_READ) != 0);
	outb(mask | MDIO_SHIFT_CLK, addr);
    पूर्ण
    वापस (retval>>1) & 0xffff;
पूर्ण

अटल व्योम mdio_ग_लिखो(अचिन्हित पूर्णांक addr, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक value)
अणु
    u_पूर्णांक cmd = (0x05<<28)|(phy_id<<23)|(loc<<18)|(1<<17)|value;
    पूर्णांक i, mask = inb(addr) & MDIO_MASK;

    mdio_sync(addr);
    क्रम (i = 31; i >= 0; i--) अणु
	पूर्णांक dat = (cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
	outb(mask | dat, addr);
	outb(mask | dat | MDIO_SHIFT_CLK, addr);
    पूर्ण
    क्रम (i = 1; i >= 0; i--) अणु
	outb(mask, addr);
	outb(mask | MDIO_SHIFT_CLK, addr);
    पूर्ण
पूर्ण

/*======================================================================

    EEPROM access routines क्रम DL10019 and DL10022 based cards

======================================================================*/

#घोषणा EE_EEP		0x40
#घोषणा EE_ASIC		0x10
#घोषणा EE_CS		0x08
#घोषणा EE_CK		0x04
#घोषणा EE_DO		0x02
#घोषणा EE_DI		0x01
#घोषणा EE_ADOT		0x01	/* DataOut क्रम ASIC */
#घोषणा EE_READ_CMD	0x06

#घोषणा DL19FDUPLX	0x0400	/* DL10019 Full duplex mode */

अटल पूर्णांक पढ़ो_eeprom(अचिन्हित पूर्णांक ioaddr, पूर्णांक location)
अणु
    पूर्णांक i, retval = 0;
    अचिन्हित पूर्णांक ee_addr = ioaddr + DLINK_EEPROM;
    पूर्णांक पढ़ो_cmd = location | (EE_READ_CMD << 8);

    outb(0, ee_addr);
    outb(EE_EEP|EE_CS, ee_addr);

    /* Shअगरt the पढ़ो command bits out. */
    क्रम (i = 10; i >= 0; i--) अणु
	लघु dataval = (पढ़ो_cmd & (1 << i)) ? EE_DO : 0;
	outb_p(EE_EEP|EE_CS|dataval, ee_addr);
	outb_p(EE_EEP|EE_CS|dataval|EE_CK, ee_addr);
    पूर्ण
    outb(EE_EEP|EE_CS, ee_addr);

    क्रम (i = 16; i > 0; i--) अणु
	outb_p(EE_EEP|EE_CS | EE_CK, ee_addr);
	retval = (retval << 1) | ((inb(ee_addr) & EE_DI) ? 1 : 0);
	outb_p(EE_EEP|EE_CS, ee_addr);
    पूर्ण

    /* Terminate the EEPROM access. */
    outb(0, ee_addr);
    वापस retval;
पूर्ण

/*
    The पूर्णांकernal ASIC रेजिस्टरs can be changed by EEPROM READ access
    with EE_ASIC bit set.
    In ASIC mode, EE_ADOT is used to output the data to the ASIC.
*/

अटल व्योम ग_लिखो_asic(अचिन्हित पूर्णांक ioaddr, पूर्णांक location, लघु asic_data)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक ee_addr = ioaddr + DLINK_EEPROM;
	लघु dataval;
	पूर्णांक पढ़ो_cmd = location | (EE_READ_CMD << 8);

	asic_data |= पढ़ो_eeprom(ioaddr, location);

	outb(0, ee_addr);
	outb(EE_ASIC|EE_CS|EE_DI, ee_addr);

	पढ़ो_cmd = पढ़ो_cmd >> 1;

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 9; i >= 0; i--) अणु
		dataval = (पढ़ो_cmd & (1 << i)) ? EE_DO : 0;
		outb_p(EE_ASIC|EE_CS|EE_DI|dataval, ee_addr);
		outb_p(EE_ASIC|EE_CS|EE_DI|dataval|EE_CK, ee_addr);
		outb_p(EE_ASIC|EE_CS|EE_DI|dataval, ee_addr);
	पूर्ण
	// sync
	outb(EE_ASIC|EE_CS, ee_addr);
	outb(EE_ASIC|EE_CS|EE_CK, ee_addr);
	outb(EE_ASIC|EE_CS, ee_addr);

	क्रम (i = 15; i >= 0; i--) अणु
		dataval = (asic_data & (1 << i)) ? EE_ADOT : 0;
		outb_p(EE_ASIC|EE_CS|dataval, ee_addr);
		outb_p(EE_ASIC|EE_CS|dataval|EE_CK, ee_addr);
		outb_p(EE_ASIC|EE_CS|dataval, ee_addr);
	पूर्ण

	/* Terminate the ASIC access. */
	outb(EE_ASIC|EE_DI, ee_addr);
	outb(EE_ASIC|EE_DI| EE_CK, ee_addr);
	outb(EE_ASIC|EE_DI, ee_addr);

	outb(0, ee_addr);
पूर्ण

/*====================================================================*/

अटल व्योम set_misc_reg(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक nic_base = dev->base_addr;
    काष्ठा pcnet_dev *info = PRIV(dev);
    u_अक्षर पंचांगp;

    अगर (info->flags & HAS_MISC_REG) अणु
	पंचांगp = inb_p(nic_base + PCNET_MISC) & ~3;
	अगर (dev->अगर_port == 2)
	    पंचांगp |= 1;
	अगर (info->flags & USE_BIG_BUF)
	    पंचांगp |= 2;
	अगर (info->flags & HAS_IBM_MISC)
	    पंचांगp |= 8;
	outb_p(पंचांगp, nic_base + PCNET_MISC);
    पूर्ण
    अगर (info->flags & IS_DL10022) अणु
	अगर (info->flags & HAS_MII) अणु
	    /* Advertise 100F, 100H, 10F, 10H */
	    mdio_ग_लिखो(nic_base + DLINK_GPIO, info->eth_phy, 4, 0x01e1);
	    /* Restart MII स्वतःnegotiation */
	    mdio_ग_लिखो(nic_base + DLINK_GPIO, info->eth_phy, 0, 0x0000);
	    mdio_ग_लिखो(nic_base + DLINK_GPIO, info->eth_phy, 0, 0x1200);
	    info->mii_reset = jअगरfies;
	पूर्ण अन्यथा अणु
	    outb(full_duplex ? 4 : 0, nic_base + DLINK_DIAG);
	पूर्ण
    पूर्ण अन्यथा अगर (info->flags & IS_DL10019) अणु
	/* Advertise 100F, 100H, 10F, 10H */
	mdio_ग_लिखो(nic_base + DLINK_GPIO, info->eth_phy, 4, 0x01e1);
	/* Restart MII स्वतःnegotiation */
	mdio_ग_लिखो(nic_base + DLINK_GPIO, info->eth_phy, 0, 0x0000);
	mdio_ग_लिखो(nic_base + DLINK_GPIO, info->eth_phy, 0, 0x1200);
    पूर्ण
पूर्ण

/*====================================================================*/

अटल व्योम mii_phy_probe(काष्ठा net_device *dev)
अणु
    काष्ठा pcnet_dev *info = PRIV(dev);
    अचिन्हित पूर्णांक mii_addr = dev->base_addr + DLINK_GPIO;
    पूर्णांक i;
    u_पूर्णांक पंचांगp, phyid;

    क्रम (i = 31; i >= 0; i--) अणु
	पंचांगp = mdio_पढ़ो(mii_addr, i, 1);
	अगर ((पंचांगp == 0) || (पंचांगp == 0xffff))
	    जारी;
	पंचांगp = mdio_पढ़ो(mii_addr, i, MII_PHYID_REG1);
	phyid = पंचांगp << 16;
	phyid |= mdio_पढ़ो(mii_addr, i, MII_PHYID_REG2);
	phyid &= MII_PHYID_REV_MASK;
	netdev_dbg(dev, "MII at %d is 0x%08x\n", i, phyid);
	अगर (phyid == AM79C9XX_HOME_PHY) अणु
	    info->pna_phy = i;
	पूर्ण अन्यथा अगर (phyid != AM79C9XX_ETH_PHY) अणु
	    info->eth_phy = i;
	पूर्ण
    पूर्ण
पूर्ण

अटल पूर्णांक pcnet_खोलो(काष्ठा net_device *dev)
अणु
    पूर्णांक ret;
    काष्ठा pcnet_dev *info = PRIV(dev);
    काष्ठा pcmcia_device *link = info->p_dev;
    अचिन्हित पूर्णांक nic_base = dev->base_addr;

    dev_dbg(&link->dev, "pcnet_open('%s')\n", dev->name);

    अगर (!pcmcia_dev_present(link))
	वापस -ENODEV;

    set_misc_reg(dev);

    outb_p(0xFF, nic_base + EN0_ISR); /* Clear bogus पूर्णांकr. */
    ret = request_irq(dev->irq, ei_irq_wrapper, IRQF_SHARED, dev->name, dev);
    अगर (ret)
	    वापस ret;

    link->खोलो++;

    info->phy_id = info->eth_phy;
    info->link_status = 0x00;
    समयr_setup(&info->watchकरोg, ei_watchकरोg, 0);
    mod_समयr(&info->watchकरोg, jअगरfies + HZ);

    वापस ei_खोलो(dev);
पूर्ण /* pcnet_खोलो */

/*====================================================================*/

अटल पूर्णांक pcnet_बंद(काष्ठा net_device *dev)
अणु
    काष्ठा pcnet_dev *info = PRIV(dev);
    काष्ठा pcmcia_device *link = info->p_dev;

    dev_dbg(&link->dev, "pcnet_close('%s')\n", dev->name);

    ei_बंद(dev);
    मुक्त_irq(dev->irq, dev);

    link->खोलो--;
    netअगर_stop_queue(dev);
    del_समयr_sync(&info->watchकरोg);

    वापस 0;
पूर्ण /* pcnet_बंद */

/*======================================================================

    Hard reset the card.  This used to छोड़ो क्रम the same period that
    a 8390 reset command required, but that shouldn't be necessary.

======================================================================*/

अटल व्योम pcnet_reset_8390(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक nic_base = dev->base_addr;
    पूर्णांक i;

    ei_status.txing = ei_status.dमुख्यg = 0;

    outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, nic_base + E8390_CMD);

    outb(inb(nic_base + PCNET_RESET), nic_base + PCNET_RESET);

    क्रम (i = 0; i < 100; i++) अणु
	अगर ((inb_p(nic_base+EN0_ISR) & ENISR_RESET) != 0)
	    अवरोध;
	udelay(100);
    पूर्ण
    outb_p(ENISR_RESET, nic_base + EN0_ISR); /* Ack पूर्णांकr. */

    अगर (i == 100)
	netdev_err(dev, "pcnet_reset_8390() did not complete.\n");

    set_misc_reg(dev);

पूर्ण /* pcnet_reset_8390 */

/*====================================================================*/

अटल पूर्णांक set_config(काष्ठा net_device *dev, काष्ठा अगरmap *map)
अणु
    काष्ठा pcnet_dev *info = PRIV(dev);
    अगर ((map->port != (u_अक्षर)(-1)) && (map->port != dev->अगर_port)) अणु
	अगर (!(info->flags & HAS_MISC_REG))
	    वापस -EOPNOTSUPP;
	अन्यथा अगर ((map->port < 1) || (map->port > 2))
	    वापस -EINVAL;
	dev->अगर_port = map->port;
	netdev_info(dev, "switched to %s port\n", अगर_names[dev->अगर_port]);
	NS8390_init(dev, 1);
    पूर्ण
    वापस 0;
पूर्ण

/*====================================================================*/

अटल irqवापस_t ei_irq_wrapper(पूर्णांक irq, व्योम *dev_id)
अणु
    काष्ठा net_device *dev = dev_id;
    काष्ठा pcnet_dev *info;
    irqवापस_t ret = ei_पूर्णांकerrupt(irq, dev_id);

    अगर (ret == IRQ_HANDLED) अणु
	    info = PRIV(dev);
	    info->stale = 0;
    पूर्ण
    वापस ret;
पूर्ण

अटल व्योम ei_watchकरोg(काष्ठा समयr_list *t)
अणु
    काष्ठा pcnet_dev *info = from_समयr(info, t, watchकरोg);
    काष्ठा net_device *dev = info->p_dev->priv;
    अचिन्हित पूर्णांक nic_base = dev->base_addr;
    अचिन्हित पूर्णांक mii_addr = nic_base + DLINK_GPIO;
    u_लघु link;

    अगर (!netअगर_device_present(dev)) जाओ reschedule;

    /* Check क्रम pending पूर्णांकerrupt with expired latency समयr: with
       this, we can limp aदीर्घ even अगर the पूर्णांकerrupt is blocked */
    अगर (info->stale++ && (inb_p(nic_base + EN0_ISR) & ENISR_ALL)) अणु
	अगर (!info->fast_poll)
	    netdev_info(dev, "interrupt(s) dropped!\n");
	ei_irq_wrapper(dev->irq, dev);
	info->fast_poll = HZ;
    पूर्ण
    अगर (info->fast_poll) अणु
	info->fast_poll--;
	info->watchकरोg.expires = jअगरfies + 1;
	add_समयr(&info->watchकरोg);
	वापस;
    पूर्ण

    अगर (!(info->flags & HAS_MII))
	जाओ reschedule;

    mdio_पढ़ो(mii_addr, info->phy_id, 1);
    link = mdio_पढ़ो(mii_addr, info->phy_id, 1);
    अगर (!link || (link == 0xffff)) अणु
	अगर (info->eth_phy) अणु
	    info->phy_id = info->eth_phy = 0;
	पूर्ण अन्यथा अणु
	    netdev_info(dev, "MII is missing!\n");
	    info->flags &= ~HAS_MII;
	पूर्ण
	जाओ reschedule;
    पूर्ण

    link &= 0x0004;
    अगर (link != info->link_status) अणु
	u_लघु p = mdio_पढ़ो(mii_addr, info->phy_id, 5);
	netdev_info(dev, "%s link beat\n", link ? "found" : "lost");
	अगर (link && (info->flags & IS_DL10022)) अणु
	    /* Disable collision detection on full duplex links */
	    outb((p & 0x0140) ? 4 : 0, nic_base + DLINK_DIAG);
	पूर्ण अन्यथा अगर (link && (info->flags & IS_DL10019)) अणु
	    /* Disable collision detection on full duplex links */
	    ग_लिखो_asic(dev->base_addr, 4, (p & 0x140) ? DL19FDUPLX : 0);
	पूर्ण
	अगर (link) अणु
	    अगर (info->phy_id == info->eth_phy) अणु
		अगर (p)
		    netdev_info(dev, "autonegotiation complete: "
				"%sbaseT-%cD selected\n",
				((p & 0x0180) ? "100" : "10"),
				((p & 0x0140) ? 'F' : 'H'));
		अन्यथा
		    netdev_info(dev, "link partner did not autonegotiate\n");
	    पूर्ण
	    NS8390_init(dev, 1);
	पूर्ण
	info->link_status = link;
    पूर्ण
    अगर (info->pna_phy && समय_after(jअगरfies, info->mii_reset + 6*HZ)) अणु
	link = mdio_पढ़ो(mii_addr, info->eth_phy, 1) & 0x0004;
	अगर (((info->phy_id == info->pna_phy) && link) ||
	    ((info->phy_id != info->pna_phy) && !link)) अणु
	    /* isolate this MII and try flipping to the other one */
	    mdio_ग_लिखो(mii_addr, info->phy_id, 0, 0x0400);
	    info->phy_id ^= info->pna_phy ^ info->eth_phy;
	    netdev_info(dev, "switched to %s transceiver\n",
			(info->phy_id == info->eth_phy) ? "ethernet" : "PNA");
	    mdio_ग_लिखो(mii_addr, info->phy_id, 0,
		       (info->phy_id == info->eth_phy) ? 0x1000 : 0);
	    info->link_status = 0;
	    info->mii_reset = jअगरfies;
	पूर्ण
    पूर्ण

reschedule:
    info->watchकरोg.expires = jअगरfies + HZ;
    add_समयr(&info->watchकरोg);
पूर्ण

/*====================================================================*/


अटल पूर्णांक ei_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
    काष्ठा pcnet_dev *info = PRIV(dev);
    काष्ठा mii_ioctl_data *data = अगर_mii(rq);
    अचिन्हित पूर्णांक mii_addr = dev->base_addr + DLINK_GPIO;

    अगर (!(info->flags & (IS_DL10019|IS_DL10022)))
	वापस -EINVAL;

    चयन (cmd) अणु
    हाल SIOCGMIIPHY:
	data->phy_id = info->phy_id;
	fallthrough;
    हाल SIOCGMIIREG:		/* Read MII PHY रेजिस्टर. */
	data->val_out = mdio_पढ़ो(mii_addr, data->phy_id, data->reg_num & 0x1f);
	वापस 0;
    हाल SIOCSMIIREG:		/* Write MII PHY रेजिस्टर. */
	mdio_ग_लिखो(mii_addr, data->phy_id, data->reg_num & 0x1f, data->val_in);
	वापस 0;
    पूर्ण
    वापस -EOPNOTSUPP;
पूर्ण

/*====================================================================*/

अटल व्योम dma_get_8390_hdr(काष्ठा net_device *dev,
			     काष्ठा e8390_pkt_hdr *hdr,
			     पूर्णांक ring_page)
अणु
    अचिन्हित पूर्णांक nic_base = dev->base_addr;

    अगर (ei_status.dमुख्यg) अणु
	netdev_err(dev, "DMAing conflict in dma_block_input."
		   "[DMAstat:%1x][irqlock:%1x]\n",
		   ei_status.dमुख्यg, ei_status.irqlock);
	वापस;
    पूर्ण

    ei_status.dमुख्यg |= 0x01;
    outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, nic_base + PCNET_CMD);
    outb_p(माप(काष्ठा e8390_pkt_hdr), nic_base + EN0_RCNTLO);
    outb_p(0, nic_base + EN0_RCNTHI);
    outb_p(0, nic_base + EN0_RSARLO);		/* On page boundary */
    outb_p(ring_page, nic_base + EN0_RSARHI);
    outb_p(E8390_RREAD+E8390_START, nic_base + PCNET_CMD);

    insw(nic_base + PCNET_DATAPORT, hdr,
	    माप(काष्ठा e8390_pkt_hdr)>>1);
    /* Fix क्रम big endian प्रणालीs */
    hdr->count = le16_to_cpu(hdr->count);

    outb_p(ENISR_RDC, nic_base + EN0_ISR);	/* Ack पूर्णांकr. */
    ei_status.dमुख्यg &= ~0x01;
पूर्ण

/*====================================================================*/

अटल व्योम dma_block_input(काष्ठा net_device *dev, पूर्णांक count,
			    काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
    अचिन्हित पूर्णांक nic_base = dev->base_addr;
    पूर्णांक xfer_count = count;
    अक्षर *buf = skb->data;
    काष्ठा ei_device *ei_local = netdev_priv(dev);

    अगर ((netअगर_msg_rx_status(ei_local)) && (count != 4))
	netdev_dbg(dev, "[bi=%d]\n", count+4);
    अगर (ei_status.dमुख्यg) अणु
	netdev_err(dev, "DMAing conflict in dma_block_input."
		   "[DMAstat:%1x][irqlock:%1x]\n",
		   ei_status.dमुख्यg, ei_status.irqlock);
	वापस;
    पूर्ण
    ei_status.dमुख्यg |= 0x01;
    outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, nic_base + PCNET_CMD);
    outb_p(count & 0xff, nic_base + EN0_RCNTLO);
    outb_p(count >> 8, nic_base + EN0_RCNTHI);
    outb_p(ring_offset & 0xff, nic_base + EN0_RSARLO);
    outb_p(ring_offset >> 8, nic_base + EN0_RSARHI);
    outb_p(E8390_RREAD+E8390_START, nic_base + PCNET_CMD);

    insw(nic_base + PCNET_DATAPORT,buf,count>>1);
    अगर (count & 0x01) अणु
	buf[count-1] = inb(nic_base + PCNET_DATAPORT);
	xfer_count++;
    पूर्ण

    /* This was क्रम the ALPHA version only, but enough people have been
       encountering problems that it is still here. */
#अगर_घोषित PCMCIA_DEBUG
      /* DMA termination address check... */
    अगर (netअगर_msg_rx_status(ei_local)) अणु
	पूर्णांक addr, tries = 20;
	करो अणु
	    /* DON'T check for 'inb_p(EN0_ISR) & ENISR_RDC' here
	       -- it's broken क्रम Rx on some cards! */
	    पूर्णांक high = inb_p(nic_base + EN0_RSARHI);
	    पूर्णांक low = inb_p(nic_base + EN0_RSARLO);
	    addr = (high << 8) + low;
	    अगर (((ring_offset + xfer_count) & 0xff) == (addr & 0xff))
		अवरोध;
	पूर्ण जबतक (--tries > 0);
	अगर (tries <= 0)
	    netdev_notice(dev, "RX transfer address mismatch,"
			  "%#4.4x (expected) vs. %#4.4x (actual).\n",
			  ring_offset + xfer_count, addr);
    पूर्ण
#पूर्ण_अगर
    outb_p(ENISR_RDC, nic_base + EN0_ISR);	/* Ack पूर्णांकr. */
    ei_status.dमुख्यg &= ~0x01;
पूर्ण /* dma_block_input */

/*====================================================================*/

अटल व्योम dma_block_output(काष्ठा net_device *dev, पूर्णांक count,
			     स्थिर u_अक्षर *buf, स्थिर पूर्णांक start_page)
अणु
    अचिन्हित पूर्णांक nic_base = dev->base_addr;
    काष्ठा pcnet_dev *info = PRIV(dev);
#अगर_घोषित PCMCIA_DEBUG
    पूर्णांक retries = 0;
    काष्ठा ei_device *ei_local = netdev_priv(dev);
#पूर्ण_अगर
    u_दीर्घ dma_start;

#अगर_घोषित PCMCIA_DEBUG
    netअगर_dbg(ei_local, tx_queued, dev, "[bo=%d]\n", count);
#पूर्ण_अगर

    /* Round the count up क्रम word ग_लिखोs.  Do we need to करो this?
       What effect will an odd byte count have on the 8390?
       I should check someday. */
    अगर (count & 0x01)
	count++;
    अगर (ei_status.dमुख्यg) अणु
	netdev_err(dev, "DMAing conflict in dma_block_output."
		   "[DMAstat:%1x][irqlock:%1x]\n",
		   ei_status.dमुख्यg, ei_status.irqlock);
	वापस;
    पूर्ण
    ei_status.dमुख्यg |= 0x01;
    /* We should alपढ़ोy be in page 0, but to be safe... */
    outb_p(E8390_PAGE0+E8390_START+E8390_NODMA, nic_base+PCNET_CMD);

#अगर_घोषित PCMCIA_DEBUG
  retry:
#पूर्ण_अगर

    outb_p(ENISR_RDC, nic_base + EN0_ISR);

    /* Now the normal output. */
    outb_p(count & 0xff, nic_base + EN0_RCNTLO);
    outb_p(count >> 8,   nic_base + EN0_RCNTHI);
    outb_p(0x00, nic_base + EN0_RSARLO);
    outb_p(start_page, nic_base + EN0_RSARHI);

    outb_p(E8390_RWRITE+E8390_START, nic_base + PCNET_CMD);
    outsw(nic_base + PCNET_DATAPORT, buf, count>>1);

    dma_start = jअगरfies;

#अगर_घोषित PCMCIA_DEBUG
    /* This was क्रम the ALPHA version only, but enough people have been
       encountering problems that it is still here. */
    /* DMA termination address check... */
    अगर (netअगर_msg_tx_queued(ei_local)) अणु
	पूर्णांक addr, tries = 20;
	करो अणु
	    पूर्णांक high = inb_p(nic_base + EN0_RSARHI);
	    पूर्णांक low = inb_p(nic_base + EN0_RSARLO);
	    addr = (high << 8) + low;
	    अगर ((start_page << 8) + count == addr)
		अवरोध;
	पूर्ण जबतक (--tries > 0);
	अगर (tries <= 0) अणु
	    netdev_notice(dev, "Tx packet transfer address mismatch,"
			  "%#4.4x (expected) vs. %#4.4x (actual).\n",
			  (start_page << 8) + count, addr);
	    अगर (retries++ == 0)
		जाओ retry;
	पूर्ण
    पूर्ण
#पूर्ण_अगर

    जबतक ((inb_p(nic_base + EN0_ISR) & ENISR_RDC) == 0)
	अगर (समय_after(jअगरfies, dma_start + PCNET_RDC_TIMEOUT)) अणु
		netdev_warn(dev, "timeout waiting for Tx RDC.\n");
		pcnet_reset_8390(dev);
		NS8390_init(dev, 1);
		अवरोध;
	पूर्ण

    outb_p(ENISR_RDC, nic_base + EN0_ISR);	/* Ack पूर्णांकr. */
    अगर (info->flags & DELAY_OUTPUT)
	udelay((दीर्घ)delay_समय);
    ei_status.dमुख्यg &= ~0x01;
पूर्ण

/*====================================================================*/

अटल पूर्णांक setup_dma_config(काष्ठा pcmcia_device *link, पूर्णांक start_pg,
			    पूर्णांक stop_pg)
अणु
    काष्ठा net_device *dev = link->priv;

    ei_status.tx_start_page = start_pg;
    ei_status.rx_start_page = start_pg + TX_PAGES;
    ei_status.stop_page = stop_pg;

    /* set up block i/o functions */
    ei_status.get_8390_hdr = dma_get_8390_hdr;
    ei_status.block_input = dma_block_input;
    ei_status.block_output = dma_block_output;

    वापस 0;
पूर्ण

/*====================================================================*/

अटल व्योम copyin(व्योम *dest, व्योम __iomem *src, पूर्णांक c)
अणु
    u_लघु *d = dest;
    u_लघु __iomem *s = src;
    पूर्णांक odd;

    अगर (c <= 0)
	वापस;
    odd = (c & 1); c >>= 1;

    अगर (c) अणु
	करो अणु *d++ = __raw_पढ़ोw(s++); पूर्ण जबतक (--c);
    पूर्ण
    /* get last byte by fetching a word and masking */
    अगर (odd)
	*((u_अक्षर *)d) = पढ़ोw(s) & 0xff;
पूर्ण

अटल व्योम copyout(व्योम __iomem *dest, स्थिर व्योम *src, पूर्णांक c)
अणु
    u_लघु __iomem *d = dest;
    स्थिर u_लघु *s = src;
    पूर्णांक odd;

    अगर (c <= 0)
	वापस;
    odd = (c & 1); c >>= 1;

    अगर (c) अणु
	करो अणु __raw_ग_लिखोw(*s++, d++); पूर्ण जबतक (--c);
    पूर्ण
    /* copy last byte करोing a पढ़ो-modअगरy-ग_लिखो */
    अगर (odd)
	ग_लिखोw((पढ़ोw(d) & 0xff00) | *(u_अक्षर *)s, d);
पूर्ण

/*====================================================================*/

अटल व्योम shmem_get_8390_hdr(काष्ठा net_device *dev,
			       काष्ठा e8390_pkt_hdr *hdr,
			       पूर्णांक ring_page)
अणु
    व्योम __iomem *xfer_start = ei_status.mem + (TX_PAGES<<8)
				+ (ring_page << 8)
				- (ei_status.rx_start_page << 8);

    copyin(hdr, xfer_start, माप(काष्ठा e8390_pkt_hdr));
    /* Fix क्रम big endian प्रणालीs */
    hdr->count = le16_to_cpu(hdr->count);
पूर्ण

/*====================================================================*/

अटल व्योम shmem_block_input(काष्ठा net_device *dev, पूर्णांक count,
			      काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
    व्योम __iomem *base = ei_status.mem;
    अचिन्हित दीर्घ offset = (TX_PAGES<<8) + ring_offset
				- (ei_status.rx_start_page << 8);
    अक्षर *buf = skb->data;

    अगर (offset + count > ei_status.priv) अणु
	/* We must wrap the input move. */
	पूर्णांक semi_count = ei_status.priv - offset;
	copyin(buf, base + offset, semi_count);
	buf += semi_count;
	offset = TX_PAGES<<8;
	count -= semi_count;
    पूर्ण
    copyin(buf, base + offset, count);
पूर्ण

/*====================================================================*/

अटल व्योम shmem_block_output(काष्ठा net_device *dev, पूर्णांक count,
			       स्थिर u_अक्षर *buf, स्थिर पूर्णांक start_page)
अणु
    व्योम __iomem *shmem = ei_status.mem + (start_page << 8);
    shmem -= ei_status.tx_start_page << 8;
    copyout(shmem, buf, count);
पूर्ण

/*====================================================================*/

अटल पूर्णांक setup_shmem_winकरोw(काष्ठा pcmcia_device *link, पूर्णांक start_pg,
			      पूर्णांक stop_pg, पूर्णांक cm_offset)
अणु
    काष्ठा net_device *dev = link->priv;
    काष्ठा pcnet_dev *info = PRIV(dev);
    पूर्णांक i, winकरोw_size, offset, ret;

    winकरोw_size = (stop_pg - start_pg) << 8;
    अगर (winकरोw_size > 32 * 1024)
	winकरोw_size = 32 * 1024;

    /* Make sure it's a घातer of two.  */
    winकरोw_size = roundup_घात_of_two(winकरोw_size);

    /* Allocate a memory winकरोw */
    link->resource[3]->flags |= WIN_DATA_WIDTH_16|WIN_MEMORY_TYPE_CM|WIN_ENABLE;
    link->resource[3]->flags |= WIN_USE_WAIT;
    link->resource[3]->start = 0; link->resource[3]->end = winकरोw_size;
    ret = pcmcia_request_winकरोw(link, link->resource[3], mem_speed);
    अगर (ret)
	    जाओ failed;

    offset = (start_pg << 8) + cm_offset;
    offset -= offset % winकरोw_size;
    ret = pcmcia_map_mem_page(link, link->resource[3], offset);
    अगर (ret)
	    जाओ failed;

    /* Try scribbling on the buffer */
    info->base = ioremap(link->resource[3]->start,
			resource_size(link->resource[3]));
    अगर (unlikely(!info->base)) अणु
	    ret = -ENOMEM;
	    जाओ failed;
    पूर्ण

    क्रम (i = 0; i < (TX_PAGES<<8); i += 2)
	__raw_ग_लिखोw((i>>1), info->base+offset+i);
    udelay(100);
    क्रम (i = 0; i < (TX_PAGES<<8); i += 2)
	अगर (__raw_पढ़ोw(info->base+offset+i) != (i>>1)) अवरोध;
    pcnet_reset_8390(dev);
    अगर (i != (TX_PAGES<<8)) अणु
	iounmap(info->base);
	pcmcia_release_winकरोw(link, link->resource[3]);
	info->base = शून्य;
	जाओ failed;
    पूर्ण

    ei_status.mem = info->base + offset;
    ei_status.priv = resource_size(link->resource[3]);
    dev->mem_start = (u_दीर्घ)ei_status.mem;
    dev->mem_end = dev->mem_start + resource_size(link->resource[3]);

    ei_status.tx_start_page = start_pg;
    ei_status.rx_start_page = start_pg + TX_PAGES;
    ei_status.stop_page = start_pg + (
	    (resource_size(link->resource[3]) - offset) >> 8);

    /* set up block i/o functions */
    ei_status.get_8390_hdr = shmem_get_8390_hdr;
    ei_status.block_input = shmem_block_input;
    ei_status.block_output = shmem_block_output;

    info->flags |= USE_SHMEM;
    वापस 0;

failed:
    वापस 1;
पूर्ण

/*====================================================================*/

अटल स्थिर काष्ठा pcmcia_device_id pcnet_ids[] = अणु
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0057, 0x0021),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0104, 0x000a),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0105, 0xea15),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0143, 0x3341),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0143, 0xc0ab),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x021b, 0x0101),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x08a1, 0xc0ab),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "AnyCom", "Fast Ethernet + 56K COMBO", 0x578ba6e7, 0xb0ac62c4),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "ATKK", "LM33-PCM-T", 0xba9eb7e2, 0x077c174e),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "D-Link", "DME336T", 0x1a424a1c, 0xb23897ff),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "Grey Cell", "GCS3000", 0x2a151fac, 0x48b932ae),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "Linksys", "EtherFast 10&100 + 56K PC Card (PCMLM56)", 0x0733cc81, 0xb3765033),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "LINKSYS", "PCMLM336", 0xf7cb0b07, 0x7a821b58),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "MICRO RESEARCH", "COMBO-L/M-336", 0xb2ced065, 0x3ced0555),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "PCMCIAs", "ComboCard", 0xdcfe12d3, 0xcd8906cc),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "PCMCIAs", "LanModem", 0xdcfe12d3, 0xc67c648f),
	PCMCIA_MFC_DEVICE_PROD_ID12(0, "IBM", "Home and Away 28.8 PC Card       ", 0xb569a6e5, 0x5bd4ff2c),
	PCMCIA_MFC_DEVICE_PROD_ID12(0, "IBM", "Home and Away Credit Card Adapter", 0xb569a6e5, 0x4bdf15c3),
	PCMCIA_MFC_DEVICE_PROD_ID12(0, "IBM", "w95 Home and Away Credit Card ", 0xb569a6e5, 0xae911c15),
	PCMCIA_MFC_DEVICE_PROD_ID123(0, "APEX DATA", "MULTICARD", "ETHERNET-MODEM", 0x11c2da09, 0x7289dc5d, 0xaad95e1f),
	PCMCIA_MFC_DEVICE_PROD_ID2(0, "FAX/Modem/Ethernet Combo Card ", 0x1ed59302),
	PCMCIA_DEVICE_MANF_CARD(0x0057, 0x1004),
	PCMCIA_DEVICE_MANF_CARD(0x0104, 0x000d),
	PCMCIA_DEVICE_MANF_CARD(0x0104, 0x0075),
	PCMCIA_DEVICE_MANF_CARD(0x0104, 0x0145),
	PCMCIA_DEVICE_MANF_CARD(0x0149, 0x0230),
	PCMCIA_DEVICE_MANF_CARD(0x0149, 0x4530),
	PCMCIA_DEVICE_MANF_CARD(0x0149, 0xc1ab),
	PCMCIA_DEVICE_MANF_CARD(0x0186, 0x0110),
	PCMCIA_DEVICE_MANF_CARD(0x01bf, 0x8041),
	PCMCIA_DEVICE_MANF_CARD(0x0213, 0x2452),
	PCMCIA_DEVICE_MANF_CARD(0x026f, 0x0300),
	PCMCIA_DEVICE_MANF_CARD(0x026f, 0x0307),
	PCMCIA_DEVICE_MANF_CARD(0x026f, 0x030a),
	PCMCIA_DEVICE_MANF_CARD(0x0274, 0x1103),
	PCMCIA_DEVICE_MANF_CARD(0x0274, 0x1121),
	PCMCIA_DEVICE_MANF_CARD(0xc001, 0x0009),
	PCMCIA_DEVICE_PROD_ID12("2408LAN", "Ethernet", 0x352fff7f, 0x00b2e941),
	PCMCIA_DEVICE_PROD_ID1234("Socket", "CF 10/100 Ethernet Card", "Revision B", "05/11/06", 0xb38bcc2e, 0x4de88352, 0xeaca6c8d, 0x7e57c22e),
	PCMCIA_DEVICE_PROD_ID123("Cardwell", "PCMCIA", "ETHERNET", 0x9533672e, 0x281f1c5d, 0x3ff7175b),
	PCMCIA_DEVICE_PROD_ID123("CNet  ", "CN30BC", "ETHERNET", 0x9fe55d3d, 0x85601198, 0x3ff7175b),
	PCMCIA_DEVICE_PROD_ID123("Digital", "Ethernet", "Adapter", 0x9999ab35, 0x00b2e941, 0x4b0d829e),
	PCMCIA_DEVICE_PROD_ID123("Edimax Technology Inc.", "PCMCIA", "Ethernet Card", 0x738a0019, 0x281f1c5d, 0x5e9d92c0),
	PCMCIA_DEVICE_PROD_ID123("EFA   ", "EFA207", "ETHERNET", 0x3d294be4, 0xeb9aab6c, 0x3ff7175b),
	PCMCIA_DEVICE_PROD_ID123("I-O DATA", "PCLA", "ETHERNET", 0x1d55d7ec, 0xe4c64d34, 0x3ff7175b),
	PCMCIA_DEVICE_PROD_ID123("IO DATA", "PCLATE", "ETHERNET", 0x547e66dc, 0x6b260753, 0x3ff7175b),
	PCMCIA_DEVICE_PROD_ID123("KingMax Technology Inc.", "EN10-T2", "PCMCIA Ethernet Card", 0x932b7189, 0x699e4436, 0x6f6652e0),
	PCMCIA_DEVICE_PROD_ID123("PCMCIA", "PCMCIA-ETHERNET-CARD", "UE2216", 0x281f1c5d, 0xd4cd2f20, 0xb87add82),
	PCMCIA_DEVICE_PROD_ID123("PCMCIA", "PCMCIA-ETHERNET-CARD", "UE2620", 0x281f1c5d, 0xd4cd2f20, 0x7d3d83a8),
	PCMCIA_DEVICE_PROD_ID1("2412LAN", 0x67f236ab),
	PCMCIA_DEVICE_PROD_ID12("ACCTON", "EN2212", 0xdfc6b5b2, 0xcb112a11),
	PCMCIA_DEVICE_PROD_ID12("ACCTON", "EN2216-PCMCIA-ETHERNET", 0xdfc6b5b2, 0x5542bfff),
	PCMCIA_DEVICE_PROD_ID12("Allied Telesis, K.K.", "CentreCOM LA100-PCM-T V2 100/10M LAN PC Card", 0xbb7fbdd7, 0xcd91cc68),
	PCMCIA_DEVICE_PROD_ID12("Allied Telesis K.K.", "LA100-PCM V2", 0x36634a66, 0xc6d05997),
  	PCMCIA_DEVICE_PROD_ID12("Allied Telesis, K.K.", "CentreCOM LA-PCM_V2", 0xbb7fBdd7, 0x28e299f8),
	PCMCIA_DEVICE_PROD_ID12("Allied Telesis K.K.", "LA-PCM V3", 0x36634a66, 0x62241d96),
	PCMCIA_DEVICE_PROD_ID12("AmbiCom", "AMB8010", 0x5070a7f9, 0x82f96e96),
	PCMCIA_DEVICE_PROD_ID12("AmbiCom", "AMB8610", 0x5070a7f9, 0x86741224),
	PCMCIA_DEVICE_PROD_ID12("AmbiCom Inc", "AMB8002", 0x93b15570, 0x75ec3efb),
	PCMCIA_DEVICE_PROD_ID12("AmbiCom Inc", "AMB8002T", 0x93b15570, 0x461c5247),
	PCMCIA_DEVICE_PROD_ID12("AmbiCom Inc", "AMB8010", 0x93b15570, 0x82f96e96),
	PCMCIA_DEVICE_PROD_ID12("AnyCom", "ECO Ethernet", 0x578ba6e7, 0x0a9888c1),
	PCMCIA_DEVICE_PROD_ID12("AnyCom", "ECO Ethernet 10/100", 0x578ba6e7, 0x939fedbd),
	PCMCIA_DEVICE_PROD_ID12("AROWANA", "PCMCIA Ethernet LAN Card", 0x313adbc8, 0x08d9f190),
	PCMCIA_DEVICE_PROD_ID12("ASANTE", "FriendlyNet PC Card", 0x3a7ade0f, 0x41c64504),
	PCMCIA_DEVICE_PROD_ID12("Billionton", "LNT-10TB", 0x552ab682, 0xeeb1ba6a),
	PCMCIA_DEVICE_PROD_ID12("CF", "10Base-Ethernet", 0x44ebf863, 0x93ae4d79),
	PCMCIA_DEVICE_PROD_ID12("CNet", "CN40BC Ethernet", 0xbc477dde, 0xfba775a7),
	PCMCIA_DEVICE_PROD_ID12("COMPU-SHACK", "BASEline PCMCIA 10 MBit Ethernetadapter", 0xfa2e424d, 0xe9190d8a),
	PCMCIA_DEVICE_PROD_ID12("COMPU-SHACK", "FASTline PCMCIA 10/100 Fast-Ethernet", 0xfa2e424d, 0x3953d9b9),
	PCMCIA_DEVICE_PROD_ID12("CONTEC", "C-NET(PC)C-10L", 0x21cab552, 0xf6f90722),
	PCMCIA_DEVICE_PROD_ID12("corega", "FEther PCC-TXF", 0x0a21501a, 0xa51564a2),
	PCMCIA_DEVICE_PROD_ID12("corega", "Ether CF-TD", 0x0a21501a, 0x6589340a),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "corega Ether CF-TD LAN Card", 0x5261440f, 0x8797663b),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "corega EtherII PCC-T", 0x5261440f, 0xfa9d85bd),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "corega EtherII PCC-TD", 0x5261440f, 0xc49bd73d),
	PCMCIA_DEVICE_PROD_ID12("Corega K.K.", "corega EtherII PCC-TD", 0xd4fdcbd8, 0xc49bd73d),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "corega Ether PCC-T", 0x5261440f, 0x6705fcaa),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "corega Ether PCC-TD", 0x5261440f, 0x47d5ca83),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "corega FastEther PCC-TX", 0x5261440f, 0x485e85d9),
	PCMCIA_DEVICE_PROD_ID12("Corega,K.K.", "Ethernet LAN Card", 0x110d26d9, 0x9fd2f0a2),
	PCMCIA_DEVICE_PROD_ID12("corega,K.K.", "Ethernet LAN Card", 0x9791a90e, 0x9fd2f0a2),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "(CG-LAPCCTXD)", 0x5261440f, 0x73ec0d88),
	PCMCIA_DEVICE_PROD_ID12("CouplerlessPCMCIA", "100BASE", 0xee5af0ad, 0x7c2add04),
	PCMCIA_DEVICE_PROD_ID12("CyQ've", "ELA-010", 0x77008979, 0x9d8d445d),
	PCMCIA_DEVICE_PROD_ID12("CyQ've", "ELA-110E 10/100M LAN Card", 0x77008979, 0xfd184814),
	PCMCIA_DEVICE_PROD_ID12("DataTrek.", "NetCard ", 0x5cd66d9d, 0x84697ce0),
	PCMCIA_DEVICE_PROD_ID12("Dayna Communications, Inc.", "CommuniCard E", 0x0c629325, 0xb4e7dbaf),
	PCMCIA_DEVICE_PROD_ID12("Digicom", "Palladio LAN 10/100", 0x697403d8, 0xe160b995),
	PCMCIA_DEVICE_PROD_ID12("Digicom", "Palladio LAN 10/100 Dongless", 0x697403d8, 0xa6d3b233),
	PCMCIA_DEVICE_PROD_ID12("DIGITAL", "DEPCM-XX", 0x69616cb3, 0xe600e76e),
	PCMCIA_DEVICE_PROD_ID12("D-Link", "DE-650", 0x1a424a1c, 0xf28c8398),
	PCMCIA_DEVICE_PROD_ID12("D-Link", "DE-660", 0x1a424a1c, 0xd9a1d05b),
	PCMCIA_DEVICE_PROD_ID12("D-Link", "DE-660+", 0x1a424a1c, 0x50dcd0ec),
	PCMCIA_DEVICE_PROD_ID12("D-Link", "DFE-650", 0x1a424a1c, 0x0f0073f9),
	PCMCIA_DEVICE_PROD_ID12("Dual Speed", "10/100 PC Card", 0x725b842d, 0xf1efee84),
	PCMCIA_DEVICE_PROD_ID12("Dual Speed", "10/100 Port Attached PC Card", 0x725b842d, 0x2db1f8e9),
	PCMCIA_DEVICE_PROD_ID12("Dynalink", "L10BC", 0x55632fd5, 0xdc65f2b1),
	PCMCIA_DEVICE_PROD_ID12("DYNALINK", "L10BC", 0x6a26d1cf, 0xdc65f2b1),
	PCMCIA_DEVICE_PROD_ID12("DYNALINK", "L10C", 0x6a26d1cf, 0xc4f84efb),
	PCMCIA_DEVICE_PROD_ID12("E-CARD", "E-CARD", 0x6701da11, 0x6701da11),
	PCMCIA_DEVICE_PROD_ID12("EIGER Labs Inc.", "Ethernet 10BaseT card", 0x53c864c6, 0xedd059f6),
	PCMCIA_DEVICE_PROD_ID12("EIGER Labs Inc.", "Ethernet Combo card", 0x53c864c6, 0x929c486c),
	PCMCIA_DEVICE_PROD_ID12("Ethernet", "Adapter", 0x00b2e941, 0x4b0d829e),
	PCMCIA_DEVICE_PROD_ID12("Ethernet Adapter", "E2000 PCMCIA Ethernet", 0x96767301, 0x71fbbc61),
	PCMCIA_DEVICE_PROD_ID12("Ethernet PCMCIA adapter", "EP-210", 0x8dd86181, 0xf2b52517),
	PCMCIA_DEVICE_PROD_ID12("Fast Ethernet", "Adapter", 0xb4be14e3, 0x4b0d829e),
	PCMCIA_DEVICE_PROD_ID12("Grey Cell", "GCS2000", 0x2a151fac, 0xf00555cb),
	PCMCIA_DEVICE_PROD_ID12("Grey Cell", "GCS2220", 0x2a151fac, 0xc1b7e327),
	PCMCIA_DEVICE_PROD_ID12("GVC", "NIC-2000p", 0x76e171bd, 0x6eb1c947),
	PCMCIA_DEVICE_PROD_ID12("IBM Corp.", "Ethernet", 0xe3736c88, 0x00b2e941),
	PCMCIA_DEVICE_PROD_ID12("IC-CARD", "IC-CARD", 0x60cb09a6, 0x60cb09a6),
	PCMCIA_DEVICE_PROD_ID12("IC-CARD+", "IC-CARD+", 0x93693494, 0x93693494),
	PCMCIA_DEVICE_PROD_ID12("IO DATA", "PCETTX", 0x547e66dc, 0x6fc5459b),
	PCMCIA_DEVICE_PROD_ID12("iPort", "10/100 Ethernet Card", 0x56c538d2, 0x11b0ffc0),
	PCMCIA_DEVICE_PROD_ID12("KANSAI ELECTRIC CO.,LTD", "KLA-PCM/T", 0xb18dc3b4, 0xcc51a956),
	PCMCIA_DEVICE_PROD_ID12("KENTRONICS", "KEP-230", 0xaf8144c9, 0x868f6616),
	PCMCIA_DEVICE_PROD_ID12("KCI", "PE520 PCMCIA Ethernet Adapter", 0xa89b87d3, 0x1eb88e64),
	PCMCIA_DEVICE_PROD_ID12("KINGMAX", "EN10T2T", 0x7bcb459a, 0xa5c81fa5),
	PCMCIA_DEVICE_PROD_ID12("Kingston", "KNE-PC2", 0x1128e633, 0xce2a89b3),
	PCMCIA_DEVICE_PROD_ID12("Kingston Technology Corp.", "EtheRx PC Card Ethernet Adapter", 0x313c7be3, 0x0afb54a2),
	PCMCIA_DEVICE_PROD_ID12("Laneed", "LD-10/100CD", 0x1b7827b2, 0xcda71d1c),
	PCMCIA_DEVICE_PROD_ID12("Laneed", "LD-CDF", 0x1b7827b2, 0xfec71e40),
	PCMCIA_DEVICE_PROD_ID12("Laneed", "LD-CDL/T", 0x1b7827b2, 0x79fba4f7),
	PCMCIA_DEVICE_PROD_ID12("Laneed", "LD-CDS", 0x1b7827b2, 0x931afaab),
	PCMCIA_DEVICE_PROD_ID12("LEMEL", "LM-N89TX PRO", 0xbbefb52f, 0xd2897a97),
	PCMCIA_DEVICE_PROD_ID12("Linksys", "Combo PCMCIA EthernetCard (EC2T)", 0x0733cc81, 0x32ee8c78),
	PCMCIA_DEVICE_PROD_ID12("LINKSYS", "E-CARD", 0xf7cb0b07, 0x6701da11),
	PCMCIA_DEVICE_PROD_ID12("Linksys", "EtherFast 10/100 Integrated PC Card (PCM100)", 0x0733cc81, 0x453c3f9d),
	PCMCIA_DEVICE_PROD_ID12("Linksys", "EtherFast 10/100 PC Card (PCMPC100)", 0x0733cc81, 0x66c5a389),
	PCMCIA_DEVICE_PROD_ID12("Linksys", "EtherFast 10/100 PC Card (PCMPC100 V2)", 0x0733cc81, 0x3a3b28e9),
	PCMCIA_DEVICE_PROD_ID12("Linksys", "HomeLink Phoneline + 10/100 Network PC Card (PCM100H1)", 0x733cc81, 0x7a3e5c3a),
	PCMCIA_DEVICE_PROD_ID12("Logitec", "LPM-LN100TX", 0x88fcdeda, 0x6d772737),
	PCMCIA_DEVICE_PROD_ID12("Logitec", "LPM-LN100TE", 0x88fcdeda, 0x0e714bee),
	PCMCIA_DEVICE_PROD_ID12("Logitec", "LPM-LN20T", 0x88fcdeda, 0x81090922),
	PCMCIA_DEVICE_PROD_ID12("Logitec", "LPM-LN10TE", 0x88fcdeda, 0xc1e2521c),
	PCMCIA_DEVICE_PROD_ID12("LONGSHINE", "PCMCIA Ethernet Card", 0xf866b0b0, 0x6f6652e0),
	PCMCIA_DEVICE_PROD_ID12("MACNICA", "ME1-JEIDA", 0x20841b68, 0xaf8a3578),
	PCMCIA_DEVICE_PROD_ID12("Macsense", "MPC-10", 0xd830297f, 0xd265c307),
	PCMCIA_DEVICE_PROD_ID12("Matsushita Electric Industrial Co.,LTD.", "CF-VEL211", 0x44445376, 0x8ded41d4),
	PCMCIA_DEVICE_PROD_ID12("MAXTECH", "PCN2000", 0x78d64bc0, 0xca0ca4b8),
	PCMCIA_DEVICE_PROD_ID12("MELCO", "LPC2-T", 0x481e0094, 0xa2eb0cf3),
	PCMCIA_DEVICE_PROD_ID12("MELCO", "LPC2-TX", 0x481e0094, 0x41a6916c),
	PCMCIA_DEVICE_PROD_ID12("Microcom C.E.", "Travel Card LAN 10/100", 0x4b91cec7, 0xe70220d6),
	PCMCIA_DEVICE_PROD_ID12("Microdyne", "NE4200", 0x2e6da59b, 0x0478e472),
	PCMCIA_DEVICE_PROD_ID12("MIDORI ELEC.", "LT-PCMT", 0x648d55c1, 0xbde526c7),
	PCMCIA_DEVICE_PROD_ID12("National Semiconductor", "InfoMover 4100", 0x36e1191f, 0x60c229b9),
	PCMCIA_DEVICE_PROD_ID12("National Semiconductor", "InfoMover NE4100", 0x36e1191f, 0xa6617ec8),
	PCMCIA_DEVICE_PROD_ID12("NEC", "PC-9801N-J12", 0x18df0ba0, 0xbc912d76),
	PCMCIA_DEVICE_PROD_ID12("NETGEAR", "FA410TX", 0x9aa79dc3, 0x60e5bc0e),
	PCMCIA_DEVICE_PROD_ID12("Network Everywhere", "Fast Ethernet 10/100 PC Card", 0x820a67b6, 0x31ed1a5f),
	PCMCIA_DEVICE_PROD_ID12("NextCom K.K.", "Next Hawk", 0xaedaec74, 0xad050ef1),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "10/100Mbps Ethernet Card", 0x281f1c5d, 0x6e41773b),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "Ethernet", 0x281f1c5d, 0x00b2e941),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "ETHERNET", 0x281f1c5d, 0x3ff7175b),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "Ethernet 10BaseT Card", 0x281f1c5d, 0x4de2f6c8),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "Ethernet Card", 0x281f1c5d, 0x5e9d92c0),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "Ethernet Combo card", 0x281f1c5d, 0x929c486c),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "ETHERNET V1.0", 0x281f1c5d, 0x4d8817c8),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "FastEthernet", 0x281f1c5d, 0xfe871eeb),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "Fast-Ethernet", 0x281f1c5d, 0x45f1f3b4),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "FAST ETHERNET CARD", 0x281f1c5d, 0xec5dbca7),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA LAN", "Ethernet", 0x7500e246, 0x00b2e941),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "LNT-10TN", 0x281f1c5d, 0xe707f641),
	PCMCIA_DEVICE_PROD_ID12("PCMCIAs", "ComboCard", 0xdcfe12d3, 0xcd8906cc),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "UE2212", 0x281f1c5d, 0xbf17199b),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "    Ethernet NE2000 Compatible", 0x281f1c5d, 0x42d5d7e1),
	PCMCIA_DEVICE_PROD_ID12("PRETEC", "Ethernet CompactLAN 10baseT 3.3V", 0xebf91155, 0x30074c80),
	PCMCIA_DEVICE_PROD_ID12("PRETEC", "Ethernet CompactLAN 10BaseT 3.3V", 0xebf91155, 0x7f5a4f50),
	PCMCIA_DEVICE_PROD_ID12("Psion Dacom", "Gold Card Ethernet", 0xf5f025c2, 0x3a30e110),
	PCMCIA_DEVICE_PROD_ID12("=RELIA==", "Ethernet", 0xcdd0644a, 0x00b2e941),
	PCMCIA_DEVICE_PROD_ID12("RIOS Systems Co.", "PC CARD3 ETHERNET", 0x7dd33481, 0x10b41826),
	PCMCIA_DEVICE_PROD_ID12("RP", "1625B Ethernet NE2000 Compatible", 0xe3e66e22, 0xb96150df),
	PCMCIA_DEVICE_PROD_ID12("RPTI", "EP400 Ethernet NE2000 Compatible", 0xdc6f88fd, 0x4a7e2ae0),
	PCMCIA_DEVICE_PROD_ID12("RPTI", "EP401 Ethernet NE2000 Compatible", 0xdc6f88fd, 0x4bcbd7fd),
	PCMCIA_DEVICE_PROD_ID12("RPTI LTD.", "EP400", 0xc53ac515, 0x81e39388),
	PCMCIA_DEVICE_PROD_ID12("SCM", "Ethernet Combo card", 0xbdc3b102, 0x929c486c),
	PCMCIA_DEVICE_PROD_ID12("Seiko Epson Corp.", "Ethernet", 0x09928730, 0x00b2e941),
	PCMCIA_DEVICE_PROD_ID12("SMC", "EZCard-10-PCMCIA", 0xc4f8b18b, 0xfb21d265),
	PCMCIA_DEVICE_PROD_ID12("Socket Communications Inc", "Socket EA PCMCIA LAN Adapter Revision D", 0xc70a4760, 0x2ade483e),
	PCMCIA_DEVICE_PROD_ID12("Socket Communications Inc", "Socket EA PCMCIA LAN Adapter Revision E", 0xc70a4760, 0x5dd978a8),
	PCMCIA_DEVICE_PROD_ID12("TDK", "LAK-CD031 for PCMCIA", 0x1eae9475, 0x0ed386fa),
	PCMCIA_DEVICE_PROD_ID12("Telecom Device K.K.", "SuperSocket RE450T", 0x466b05f0, 0x8b74bc4f),
	PCMCIA_DEVICE_PROD_ID12("Telecom Device K.K.", "SuperSocket RE550T", 0x466b05f0, 0x33c8db2a),
	PCMCIA_DEVICE_PROD_ID13("Hypertec",  "EP401", 0x8787bec7, 0xf6e4a31e),
	PCMCIA_DEVICE_PROD_ID13("KingMax Technology Inc.", "Ethernet Card", 0x932b7189, 0x5e9d92c0),
	PCMCIA_DEVICE_PROD_ID13("LONGSHINE", "EP401", 0xf866b0b0, 0xf6e4a31e),
	PCMCIA_DEVICE_PROD_ID13("Xircom", "CFE-10", 0x2e3ee845, 0x22a49f89),
	PCMCIA_DEVICE_PROD_ID1("CyQ've 10 Base-T LAN CARD", 0x94faf360),
	PCMCIA_DEVICE_PROD_ID1("EP-210 PCMCIA LAN CARD.", 0x8850b4de),
	PCMCIA_DEVICE_PROD_ID1("ETHER-C16", 0x06a8514f),
	PCMCIA_DEVICE_PROD_ID1("NE2000 Compatible", 0x75b8ad5a),
	PCMCIA_DEVICE_PROD_ID2("EN-6200P2", 0xa996d078),
	/* too generic! */
	/* PCMCIA_DEVICE_PROD_ID12("PCMCIA", "10/100 Ethernet Card", 0x281f1c5d, 0x11b0ffc0), */
	PCMCIA_PFC_DEVICE_CIS_PROD_ID12(0, "PCMCIA", "EN2218-LAN/MODEM", 0x281f1c5d, 0x570f348e, "cis/PCMLM28.cis"),
	PCMCIA_PFC_DEVICE_CIS_PROD_ID12(0, "PCMCIA", "UE2218-LAN/MODEM", 0x281f1c5d, 0x6fdcacee, "cis/PCMLM28.cis"),
	PCMCIA_PFC_DEVICE_CIS_PROD_ID12(0, "Psion Dacom", "Gold Card V34 Ethernet", 0xf5f025c2, 0x338e8155, "cis/PCMLM28.cis"),
	PCMCIA_PFC_DEVICE_CIS_PROD_ID12(0, "Psion Dacom", "Gold Card V34 Ethernet GSM", 0xf5f025c2, 0x4ae85d35, "cis/PCMLM28.cis"),
	PCMCIA_PFC_DEVICE_CIS_PROD_ID12(0, "LINKSYS", "PCMLM28", 0xf7cb0b07, 0x66881874, "cis/PCMLM28.cis"),
	PCMCIA_PFC_DEVICE_CIS_PROD_ID12(0, "TOSHIBA", "Modem/LAN Card", 0xb4585a1a, 0x53f922f8, "cis/PCMLM28.cis"),
	PCMCIA_MFC_DEVICE_CIS_PROD_ID12(0, "DAYNA COMMUNICATIONS", "LAN AND MODEM MULTIFUNCTION", 0x8fdf8f89, 0xdd5ed9e8, "cis/DP83903.cis"),
	PCMCIA_MFC_DEVICE_CIS_PROD_ID4(0, "NSC MF LAN/Modem", 0x58fc6056, "cis/DP83903.cis"),
	PCMCIA_MFC_DEVICE_CIS_MANF_CARD(0, 0x0175, 0x0000, "cis/DP83903.cis"),
	PCMCIA_DEVICE_CIS_PROD_ID12("Allied Telesis,K.K", "Ethernet LAN Card", 0x2ad62f3c, 0x9fd2f0a2, "cis/LA-PCM.cis"),
	PCMCIA_DEVICE_CIS_PROD_ID12("KTI", "PE520 PLUS", 0xad180345, 0x9d58d392, "cis/PE520.cis"),
	PCMCIA_DEVICE_CIS_PROD_ID12("NDC", "Ethernet", 0x01c43ae1, 0x00b2e941, "cis/NE2K.cis"),
	PCMCIA_DEVICE_CIS_PROD_ID12("PMX   ", "PE-200", 0x34f3f1c8, 0x10b59f8c, "cis/PE-200.cis"),
	PCMCIA_DEVICE_CIS_PROD_ID12("TAMARACK", "Ethernet", 0xcf434fba, 0x00b2e941, "cis/tamarack.cis"),
	PCMCIA_DEVICE_PROD_ID12("Ethernet", "CF Size PC Card", 0x00b2e941, 0x43ac239b),
	PCMCIA_DEVICE_PROD_ID123("Fast Ethernet", "CF Size PC Card", "1.0",
		0xb4be14e3, 0x43ac239b, 0x0877b627),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, pcnet_ids);
MODULE_FIRMWARE("cis/PCMLM28.cis");
MODULE_FIRMWARE("cis/DP83903.cis");
MODULE_FIRMWARE("cis/LA-PCM.cis");
MODULE_FIRMWARE("cis/PE520.cis");
MODULE_FIRMWARE("cis/NE2K.cis");
MODULE_FIRMWARE("cis/PE-200.cis");
MODULE_FIRMWARE("cis/tamarack.cis");

अटल काष्ठा pcmcia_driver pcnet_driver = अणु
	.name		= "pcnet_cs",
	.probe		= pcnet_probe,
	.हटाओ		= pcnet_detach,
	.owner		= THIS_MODULE,
	.id_table	= pcnet_ids,
	.suspend	= pcnet_suspend,
	.resume		= pcnet_resume,
पूर्ण;
module_pcmcia_driver(pcnet_driver);
