<शैली गुरु>
/*======================================================================

    A PCMCIA ethernet driver क्रम SMC91c92-based cards.

    This driver supports Megahertz PCMCIA ethernet cards; and
    Megahertz, Motorola, Ositech, and Psion Dacom ethernet/modem
    multअगरunction cards.

    Copyright (C) 1999 David A. Hinds -- dahinds@users.sourceक्रमge.net

    smc91c92_cs.c 1.122 2002/10/25 06:26:39

    This driver contains code written by Donald Becker
    (becker@scyld.com), Rowan Hughes (x-csrdh@jcu.edu.au),
    David Hinds (dahinds@users.sourceक्रमge.net), and Erik Stahlman
    (erik@vt.edu).  Donald wrote the SMC 91c92 code using parts of
    Erik's SMC 91c94 driver.  Rowan wrote a similar driver, and I've
    incorporated some parts of his driver here.  I (Dave) wrote most
    of the PCMCIA glue code, and the Ositech support code.  Kelly
    Stephens (kstephen@holli.com) added support क्रम the Motorola
    Mariner, with help from Allen Brost.

    This software may be used and distributed according to the terms of
    the GNU General Public License, incorporated herein by reference.

======================================================================*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/firmware.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/ss.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

/*====================================================================*/

अटल स्थिर अक्षर *अगर_names[] = अणु "auto", "10baseT", "10base2"पूर्ण;

/* Firmware name */
#घोषणा FIRMWARE_NAME		"ositech/Xilinx7OD.bin"

/* Module parameters */

MODULE_DESCRIPTION("SMC 91c92 series PCMCIA ethernet driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE_NAME);

#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v; module_param(n, पूर्णांक, 0)

/*
  Transceiver/media type.
   0 = स्वतः
   1 = 10baseT (and स्वतःselect अगर #घोषणा AUTOSELECT),
   2 = AUI/10base2,
*/
INT_MODULE_PARM(अगर_port, 0);


#घोषणा DRV_NAME	"smc91c92_cs"
#घोषणा DRV_VERSION	"1.123"

/*====================================================================*/

/* Operational parameter that usually are not changed. */

/* Time in jअगरfies beक्रमe concluding Tx hung */
#घोषणा TX_TIMEOUT		((400*HZ)/1000)

/* Maximum events (Rx packets, etc.) to handle at each पूर्णांकerrupt. */
#घोषणा INTR_WORK		4

/* Times to check the check the chip beक्रमe concluding that it करोesn't
   currently have room क्रम another Tx packet. */
#घोषणा MEMORY_WAIT_TIME       	8

काष्ठा smc_निजी अणु
	काष्ठा pcmcia_device	*p_dev;
    spinlock_t			lock;
    u_लघु			manfid;
    u_लघु			cardid;

    काष्ठा sk_buff		*saved_skb;
    पूर्णांक				packets_रुकोing;
    व्योम			__iomem *base;
    u_लघु			cfg;
    काष्ठा समयr_list		media;
    पूर्णांक				watchकरोg, tx_err;
    u_लघु			media_status;
    u_लघु			fast_poll;
    u_लघु			link_status;
    काष्ठा mii_अगर_info		mii_अगर;
    पूर्णांक				duplex;
    पूर्णांक				rx_ovrn;
    अचिन्हित दीर्घ		last_rx;
पूर्ण;

/* Special definitions क्रम Megahertz multअगरunction cards */
#घोषणा MEGAHERTZ_ISR		0x0380

/* Special function रेजिस्टरs क्रम Motorola Mariner */
#घोषणा MOT_LAN			0x0000
#घोषणा MOT_UART		0x0020
#घोषणा MOT_EEPROM		0x20

#घोषणा MOT_NORMAL \
(COR_LEVEL_REQ | COR_FUNC_ENA | COR_ADDR_DECODE | COR_IREQ_ENA)

/* Special function रेजिस्टरs क्रम Ositech cards */
#घोषणा OSITECH_AUI_CTL		0x0c
#घोषणा OSITECH_PWRDOWN		0x0d
#घोषणा OSITECH_RESET		0x0e
#घोषणा OSITECH_ISR		0x0f
#घोषणा OSITECH_AUI_PWR		0x0c
#घोषणा OSITECH_RESET_ISR	0x0e

#घोषणा OSI_AUI_PWR		0x40
#घोषणा OSI_LAN_PWRDOWN		0x02
#घोषणा OSI_MODEM_PWRDOWN	0x01
#घोषणा OSI_LAN_RESET		0x02
#घोषणा OSI_MODEM_RESET		0x01

/* Symbolic स्थिरants क्रम the SMC91c9* series chips, from Erik Stahlman. */
#घोषणा	BANK_SELECT		14		/* Winकरोw select रेजिस्टर. */
#घोषणा SMC_SELECT_BANK(x)  अणु outw(x, ioaddr + BANK_SELECT); पूर्ण

/* Bank 0 रेजिस्टरs. */
#घोषणा	TCR 		0	/* transmit control रेजिस्टर */
#घोषणा	 TCR_CLEAR	0	/* करो NOTHING */
#घोषणा  TCR_ENABLE	0x0001	/* अगर this is 1, we can transmit */
#घोषणा	 TCR_PAD_EN	0x0080	/* pads लघु packets to 64 bytes */
#घोषणा  TCR_MONCSN	0x0400  /* Monitor Carrier. */
#घोषणा  TCR_FDUPLX	0x0800  /* Full duplex mode. */
#घोषणा	 TCR_NORMAL TCR_ENABLE | TCR_PAD_EN

#घोषणा EPH		2	/* Ethernet Protocol Handler report. */
#घोषणा  EPH_TX_SUC	0x0001
#घोषणा  EPH_SNGLCOL	0x0002
#घोषणा  EPH_MULCOL	0x0004
#घोषणा  EPH_LTX_MULT	0x0008
#घोषणा  EPH_16COL	0x0010
#घोषणा  EPH_SQET	0x0020
#घोषणा  EPH_LTX_BRD	0x0040
#घोषणा  EPH_TX_DEFR	0x0080
#घोषणा  EPH_LAT_COL	0x0200
#घोषणा  EPH_LOST_CAR	0x0400
#घोषणा  EPH_EXC_DEF	0x0800
#घोषणा  EPH_CTR_ROL	0x1000
#घोषणा  EPH_RX_OVRN	0x2000
#घोषणा  EPH_LINK_OK	0x4000
#घोषणा  EPH_TX_UNRN	0x8000
#घोषणा MEMINFO		8	/* Memory Inक्रमmation Register */
#घोषणा MEMCFG		10	/* Memory Configuration Register */

/* Bank 1 रेजिस्टरs. */
#घोषणा CONFIG			0
#घोषणा  CFG_MII_SELECT		0x8000	/* 91C100 only */
#घोषणा  CFG_NO_WAIT		0x1000
#घोषणा  CFG_FULL_STEP		0x0400
#घोषणा  CFG_SET_SQLCH		0x0200
#घोषणा  CFG_AUI_SELECT	 	0x0100
#घोषणा  CFG_16BIT		0x0080
#घोषणा  CFG_DIS_LINK		0x0040
#घोषणा  CFG_STATIC		0x0030
#घोषणा  CFG_IRQ_SEL_1		0x0004
#घोषणा  CFG_IRQ_SEL_0		0x0002
#घोषणा BASE_ADDR		2
#घोषणा	ADDR0			4
#घोषणा	GENERAL			10
#घोषणा	CONTROL			12
#घोषणा  CTL_STORE		0x0001
#घोषणा  CTL_RELOAD		0x0002
#घोषणा  CTL_EE_SELECT		0x0004
#घोषणा  CTL_TE_ENABLE		0x0020
#घोषणा  CTL_CR_ENABLE		0x0040
#घोषणा  CTL_LE_ENABLE		0x0080
#घोषणा  CTL_AUTO_RELEASE	0x0800
#घोषणा	 CTL_POWERDOWN		0x2000

/* Bank 2 रेजिस्टरs. */
#घोषणा MMU_CMD		0
#घोषणा	 MC_ALLOC	0x20  	/* or with number of 256 byte packets */
#घोषणा	 MC_RESET	0x40
#घोषणा  MC_RELEASE  	0x80  	/* हटाओ and release the current rx packet */
#घोषणा  MC_FREEPKT  	0xA0  	/* Release packet in PNR रेजिस्टर */
#घोषणा  MC_ENQUEUE	0xC0 	/* Enqueue the packet क्रम transmit */
#घोषणा	PNR_ARR		2
#घोषणा FIFO_PORTS	4
#घोषणा  FP_RXEMPTY	0x8000
#घोषणा	POINTER		6
#घोषणा  PTR_AUTO_INC	0x0040
#घोषणा  PTR_READ	0x2000
#घोषणा	 PTR_AUTOINC 	0x4000
#घोषणा	 PTR_RCV	0x8000
#घोषणा	DATA_1		8
#घोषणा	INTERRUPT	12
#घोषणा  IM_RCV_INT		0x1
#घोषणा	 IM_TX_INT		0x2
#घोषणा	 IM_TX_EMPTY_INT	0x4
#घोषणा	 IM_ALLOC_INT		0x8
#घोषणा	 IM_RX_OVRN_INT		0x10
#घोषणा	 IM_EPH_INT		0x20

#घोषणा	RCR		4
क्रमागत RxCfg अणु RxAllMulti = 0x0004, RxPromisc = 0x0002,
	     RxEnable = 0x0100, RxStripCRC = 0x0200पूर्ण;
#घोषणा  RCR_SOFTRESET	0x8000 	/* resets the chip */
#घोषणा	 RCR_STRIP_CRC	0x200	/* strips CRC */
#घोषणा  RCR_ENABLE	0x100	/* IFF this is set, we can receive packets */
#घोषणा  RCR_ALMUL	0x4 	/* receive all multicast packets */
#घोषणा	 RCR_PROMISC	0x2	/* enable promiscuous mode */

/* the normal settings क्रम the RCR रेजिस्टर : */
#घोषणा	 RCR_NORMAL	(RCR_STRIP_CRC | RCR_ENABLE)
#घोषणा  RCR_CLEAR	0x0		/* set it to a base state */
#घोषणा	COUNTER		6

/* BANK 3 -- not the same values as in smc9194! */
#घोषणा	MULTICAST0	0
#घोषणा	MULTICAST2	2
#घोषणा	MULTICAST4	4
#घोषणा	MULTICAST6	6
#घोषणा MGMT    	8
#घोषणा REVISION	0x0a

/* Transmit status bits. */
#घोषणा TS_SUCCESS 0x0001
#घोषणा TS_16COL   0x0010
#घोषणा TS_LATCOL  0x0200
#घोषणा TS_LOSTCAR 0x0400

/* Receive status bits. */
#घोषणा RS_ALGNERR	0x8000
#घोषणा RS_BADCRC	0x2000
#घोषणा RS_ODDFRAME	0x1000
#घोषणा RS_TOOLONG	0x0800
#घोषणा RS_TOOSHORT	0x0400
#घोषणा RS_MULTICAST	0x0001
#घोषणा RS_ERRORS	(RS_ALGNERR | RS_BADCRC | RS_TOOLONG | RS_TOOSHORT)

#घोषणा set_bits(v, p) outw(inw(p)|(v), (p))
#घोषणा mask_bits(v, p) outw(inw(p)&(v), (p))

/*====================================================================*/

अटल व्योम smc91c92_detach(काष्ठा pcmcia_device *p_dev);
अटल पूर्णांक smc91c92_config(काष्ठा pcmcia_device *link);
अटल व्योम smc91c92_release(काष्ठा pcmcia_device *link);

अटल पूर्णांक smc_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक smc_बंद(काष्ठा net_device *dev);
अटल पूर्णांक smc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल व्योम smc_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल netdev_tx_t smc_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev);
अटल irqवापस_t smc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल व्योम smc_rx(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल पूर्णांक s9k_config(काष्ठा net_device *dev, काष्ठा अगरmap *map);
अटल व्योम smc_set_xcvr(काष्ठा net_device *dev, पूर्णांक अगर_port);
अटल व्योम smc_reset(काष्ठा net_device *dev);
अटल व्योम media_check(काष्ठा समयr_list *t);
अटल व्योम mdio_sync(अचिन्हित पूर्णांक addr);
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक loc);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक value);
अटल पूर्णांक smc_link_ok(काष्ठा net_device *dev);
अटल स्थिर काष्ठा ethtool_ops ethtool_ops;

अटल स्थिर काष्ठा net_device_ops smc_netdev_ops = अणु
	.nकरो_खोलो		= smc_खोलो,
	.nकरो_stop		= smc_बंद,
	.nकरो_start_xmit		= smc_start_xmit,
	.nकरो_tx_समयout 	= smc_tx_समयout,
	.nकरो_set_config 	= s9k_config,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_करो_ioctl		= smc_ioctl,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक smc91c92_probe(काष्ठा pcmcia_device *link)
अणु
    काष्ठा smc_निजी *smc;
    काष्ठा net_device *dev;

    dev_dbg(&link->dev, "smc91c92_attach()\n");

    /* Create new ethernet device */
    dev = alloc_etherdev(माप(काष्ठा smc_निजी));
    अगर (!dev)
	वापस -ENOMEM;
    smc = netdev_priv(dev);
    smc->p_dev = link;
    link->priv = dev;

    spin_lock_init(&smc->lock);

    /* The SMC91c92-specअगरic entries in the device काष्ठाure. */
    dev->netdev_ops = &smc_netdev_ops;
    dev->ethtool_ops = &ethtool_ops;
    dev->watchकरोg_समयo = TX_TIMEOUT;

    smc->mii_अगर.dev = dev;
    smc->mii_अगर.mdio_पढ़ो = mdio_पढ़ो;
    smc->mii_अगर.mdio_ग_लिखो = mdio_ग_लिखो;
    smc->mii_अगर.phy_id_mask = 0x1f;
    smc->mii_अगर.reg_num_mask = 0x1f;

    वापस smc91c92_config(link);
पूर्ण /* smc91c92_attach */

अटल व्योम smc91c92_detach(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;

    dev_dbg(&link->dev, "smc91c92_detach\n");

    unरेजिस्टर_netdev(dev);

    smc91c92_release(link);

    मुक्त_netdev(dev);
पूर्ण /* smc91c92_detach */

/*====================================================================*/

अटल पूर्णांक cvt_ascii_address(काष्ठा net_device *dev, अक्षर *s)
अणु
    पूर्णांक i, j, da, c;

    अगर (म_माप(s) != 12)
	वापस -1;
    क्रम (i = 0; i < 6; i++) अणु
	da = 0;
	क्रम (j = 0; j < 2; j++) अणु
	    c = *s++;
	    da <<= 4;
	    da += ((c >= '0') && (c <= '9')) ?
		(c - '0') : ((c & 0x0f) + 9);
	पूर्ण
	dev->dev_addr[i] = da;
    पूर्ण
    वापस 0;
पूर्ण

/*====================================================================

    Configuration stuff क्रम Megahertz cards

    mhz_3288_घातer() is used to घातer up a 3288's ethernet chip.
    mhz_mfc_config() handles socket setup क्रम multअगरunction (1144
    and 3288) cards.  mhz_setup() माला_लो a card's hardware ethernet
    address.

======================================================================*/

अटल पूर्णांक mhz_3288_घातer(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    u_अक्षर पंचांगp;

    /* Read the ISR twice... */
    पढ़ोb(smc->base+MEGAHERTZ_ISR);
    udelay(5);
    पढ़ोb(smc->base+MEGAHERTZ_ISR);

    /* Pause 200ms... */
    mdelay(200);

    /* Now पढ़ो and ग_लिखो the COR... */
    पंचांगp = पढ़ोb(smc->base + link->config_base + CISREG_COR);
    udelay(5);
    ग_लिखोb(पंचांगp, smc->base + link->config_base + CISREG_COR);

    वापस 0;
पूर्ण

अटल पूर्णांक mhz_mfc_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	पूर्णांक k;
	p_dev->io_lines = 16;
	p_dev->resource[1]->start = p_dev->resource[0]->start;
	p_dev->resource[1]->end = 8;
	p_dev->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;
	p_dev->resource[0]->end = 16;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
	क्रम (k = 0; k < 0x400; k += 0x10) अणु
		अगर (k & 0x80)
			जारी;
		p_dev->resource[0]->start = k ^ 0x300;
		अगर (!pcmcia_request_io(p_dev))
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक mhz_mfc_config(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अचिन्हित पूर्णांक offset;
    पूर्णांक i;

    link->config_flags |= CONF_ENABLE_SPKR | CONF_ENABLE_IRQ |
	    CONF_AUTO_SET_IO;

    /* The Megahertz combo cards have modem-like CIS entries, so
       we have to explicitly try a bunch of port combinations. */
    अगर (pcmcia_loop_config(link, mhz_mfc_config_check, शून्य))
	    वापस -ENODEV;

    dev->base_addr = link->resource[0]->start;

    /* Allocate a memory winकरोw, क्रम accessing the ISR */
    link->resource[2]->flags = WIN_DATA_WIDTH_8|WIN_MEMORY_TYPE_AM|WIN_ENABLE;
    link->resource[2]->start = link->resource[2]->end = 0;
    i = pcmcia_request_winकरोw(link, link->resource[2], 0);
    अगर (i != 0)
	    वापस -ENODEV;

    smc->base = ioremap(link->resource[2]->start,
		    resource_size(link->resource[2]));
    offset = (smc->manfid == MANFID_MOTOROLA) ? link->config_base : 0;
    i = pcmcia_map_mem_page(link, link->resource[2], offset);
    अगर ((i == 0) &&
	(smc->manfid == MANFID_MEGAHERTZ) &&
	(smc->cardid == PRODID_MEGAHERTZ_EM3288))
	    mhz_3288_घातer(link);

    वापस 0;
पूर्ण

अटल पूर्णांक pcmcia_get_versmac(काष्ठा pcmcia_device *p_dev,
			      tuple_t *tuple,
			      व्योम *priv)
अणु
	काष्ठा net_device *dev = priv;
	cisparse_t parse;
	u8 *buf;

	अगर (pcmcia_parse_tuple(tuple, &parse))
		वापस -EINVAL;

	buf = parse.version_1.str + parse.version_1.ofs[3];

	अगर ((parse.version_1.ns > 3) && (cvt_ascii_address(dev, buf) == 0))
		वापस 0;

	वापस -EINVAL;
पूर्ण;

अटल पूर्णांक mhz_setup(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    माप_प्रकार len;
    u8 *buf;
    पूर्णांक rc;

    /* Read the station address from the CIS.  It is stored as the last
       (fourth) string in the Version 1 Version/ID tuple. */
    अगर ((link->prod_id[3]) &&
	(cvt_ascii_address(dev, link->prod_id[3]) == 0))
	    वापस 0;

    /* Workarounds क्रम broken cards start here. */
    /* Ugh -- the EM1144 card has two VERS_1 tuples!?! */
    अगर (!pcmcia_loop_tuple(link, CISTPL_VERS_1, pcmcia_get_versmac, dev))
	    वापस 0;

    /* Another possibility: क्रम the EM3288, in a special tuple */
    rc = -1;
    len = pcmcia_get_tuple(link, 0x81, &buf);
    अगर (buf && len >= 13) अणु
	    buf[12] = '\0';
	    अगर (cvt_ascii_address(dev, buf) == 0)
		    rc = 0;
    पूर्ण
    kमुक्त(buf);

    वापस rc;
पूर्ण;

/*======================================================================

    Configuration stuff क्रम the Motorola Mariner

    mot_config() ग_लिखोs directly to the Mariner configuration
    रेजिस्टरs because the CIS is just bogus.

======================================================================*/

अटल व्योम mot_config(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    अचिन्हित पूर्णांक iouart = link->resource[1]->start;

    /* Set UART base address and क्रमce map with COR bit 1 */
    ग_लिखोb(iouart & 0xff,        smc->base + MOT_UART + CISREG_IOBASE_0);
    ग_लिखोb((iouart >> 8) & 0xff, smc->base + MOT_UART + CISREG_IOBASE_1);
    ग_लिखोb(MOT_NORMAL,           smc->base + MOT_UART + CISREG_COR);

    /* Set SMC base address and क्रमce map with COR bit 1 */
    ग_लिखोb(ioaddr & 0xff,        smc->base + MOT_LAN + CISREG_IOBASE_0);
    ग_लिखोb((ioaddr >> 8) & 0xff, smc->base + MOT_LAN + CISREG_IOBASE_1);
    ग_लिखोb(MOT_NORMAL,           smc->base + MOT_LAN + CISREG_COR);

    /* Wait क्रम things to settle करोwn */
    mdelay(100);
पूर्ण

अटल पूर्णांक mot_setup(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    पूर्णांक i, रुको, loop;
    u_पूर्णांक addr;

    /* Read Ethernet address from Serial EEPROM */

    क्रम (i = 0; i < 3; i++) अणु
	SMC_SELECT_BANK(2);
	outw(MOT_EEPROM + i, ioaddr + POINTER);
	SMC_SELECT_BANK(1);
	outw((CTL_RELOAD | CTL_EE_SELECT), ioaddr + CONTROL);

	क्रम (loop = रुको = 0; loop < 200; loop++) अणु
	    udelay(10);
	    रुको = ((CTL_RELOAD | CTL_STORE) & inw(ioaddr + CONTROL));
	    अगर (रुको == 0) अवरोध;
	पूर्ण
	
	अगर (रुको)
	    वापस -1;
	
	addr = inw(ioaddr + GENERAL);
	dev->dev_addr[2*i]   = addr & 0xff;
	dev->dev_addr[2*i+1] = (addr >> 8) & 0xff;
    पूर्ण

    वापस 0;
पूर्ण

/*====================================================================*/

अटल पूर्णांक smc_configcheck(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	p_dev->resource[0]->end = 16;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;

	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक smc_config(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    पूर्णांक i;

    link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

    i = pcmcia_loop_config(link, smc_configcheck, शून्य);
    अगर (!i)
	    dev->base_addr = link->resource[0]->start;

    वापस i;
पूर्ण


अटल पूर्णांक smc_setup(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;

    /* Check क्रम a LAN function extension tuple */
    अगर (!pcmcia_get_mac_from_cis(link, dev))
	    वापस 0;

    /* Try the third string in the Version 1 Version/ID tuple. */
    अगर (link->prod_id[2]) अणु
	    अगर (cvt_ascii_address(dev, link->prod_id[2]) == 0)
		    वापस 0;
    पूर्ण
    वापस -1;
पूर्ण

/*====================================================================*/

अटल पूर्णांक osi_config(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    अटल स्थिर अचिन्हित पूर्णांक com[4] = अणु 0x3f8, 0x2f8, 0x3e8, 0x2e8 पूर्ण;
    पूर्णांक i, j;

    link->config_flags |= CONF_ENABLE_SPKR | CONF_ENABLE_IRQ;
    link->resource[0]->end = 64;
    link->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;
    link->resource[1]->end = 8;

    /* Enable Hard Decode, LAN, Modem */
    link->io_lines = 16;
    link->config_index = 0x23;

    क्रम (i = j = 0; j < 4; j++) अणु
	link->resource[1]->start = com[j];
	i = pcmcia_request_io(link);
	अगर (i == 0)
		अवरोध;
    पूर्ण
    अगर (i != 0) अणु
	/* Fallback: turn off hard decode */
	link->config_index = 0x03;
	link->resource[1]->end = 0;
	i = pcmcia_request_io(link);
    पूर्ण
    dev->base_addr = link->resource[0]->start + 0x10;
    वापस i;
पूर्ण

अटल पूर्णांक osi_load_firmware(काष्ठा pcmcia_device *link)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक i, err;

	err = request_firmware(&fw, FIRMWARE_NAME, &link->dev);
	अगर (err) अणु
		pr_err("Failed to load firmware \"%s\"\n", FIRMWARE_NAME);
		वापस err;
	पूर्ण

	/* Download the Seven of Diamonds firmware */
	क्रम (i = 0; i < fw->size; i++) अणु
	    outb(fw->data[i], link->resource[0]->start + 2);
	    udelay(50);
	पूर्ण
	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक pcmcia_osi_mac(काष्ठा pcmcia_device *p_dev,
			  tuple_t *tuple,
			  व्योम *priv)
अणु
	काष्ठा net_device *dev = priv;
	पूर्णांक i;

	अगर (tuple->TupleDataLen < 8)
		वापस -EINVAL;
	अगर (tuple->TupleData[0] != 0x04)
		वापस -EINVAL;
	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = tuple->TupleData[i+2];
	वापस 0;
पूर्ण;


अटल पूर्णांक osi_setup(काष्ठा pcmcia_device *link, u_लघु manfid, u_लघु cardid)
अणु
    काष्ठा net_device *dev = link->priv;
    पूर्णांक rc;

    /* Read the station address from tuple 0x90, subtuple 0x04 */
    अगर (pcmcia_loop_tuple(link, 0x90, pcmcia_osi_mac, dev))
	    वापस -1;

    अगर (((manfid == MANFID_OSITECH) &&
	 (cardid == PRODID_OSITECH_SEVEN)) ||
	((manfid == MANFID_PSION) &&
	 (cardid == PRODID_PSION_NET100))) अणु
	rc = osi_load_firmware(link);
	अगर (rc)
		वापस rc;
    पूर्ण अन्यथा अगर (manfid == MANFID_OSITECH) अणु
	/* Make sure both functions are घातered up */
	set_bits(0x300, link->resource[0]->start + OSITECH_AUI_PWR);
	/* Now, turn on the पूर्णांकerrupt क्रम both card functions */
	set_bits(0x300, link->resource[0]->start + OSITECH_RESET_ISR);
	dev_dbg(&link->dev, "AUI/PWR: %4.4x RESET/ISR: %4.4x\n",
	      inw(link->resource[0]->start + OSITECH_AUI_PWR),
	      inw(link->resource[0]->start + OSITECH_RESET_ISR));
    पूर्ण
    वापस 0;
पूर्ण

अटल पूर्णांक smc91c92_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो)
		netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक smc91c92_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;
	काष्ठा smc_निजी *smc = netdev_priv(dev);
	पूर्णांक i;

	अगर ((smc->manfid == MANFID_MEGAHERTZ) &&
	    (smc->cardid == PRODID_MEGAHERTZ_EM3288))
		mhz_3288_घातer(link);
	अगर (smc->manfid == MANFID_MOTOROLA)
		mot_config(link);
	अगर ((smc->manfid == MANFID_OSITECH) &&
	    (smc->cardid != PRODID_OSITECH_SEVEN)) अणु
		/* Power up the card and enable पूर्णांकerrupts */
		set_bits(0x0300, dev->base_addr-0x10+OSITECH_AUI_PWR);
		set_bits(0x0300, dev->base_addr-0x10+OSITECH_RESET_ISR);
	पूर्ण
	अगर (((smc->manfid == MANFID_OSITECH) &&
	     (smc->cardid == PRODID_OSITECH_SEVEN)) ||
	    ((smc->manfid == MANFID_PSION) &&
	     (smc->cardid == PRODID_PSION_NET100))) अणु
		i = osi_load_firmware(link);
		अगर (i) अणु
			netdev_err(dev, "Failed to load firmware\n");
			वापस i;
		पूर्ण
	पूर्ण
	अगर (link->खोलो) अणु
		smc_reset(dev);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण


/*======================================================================

    This verअगरies that the chip is some SMC91cXX variant, and वापसs
    the revision code अगर successful.  Otherwise, it वापसs -ENODEV.

======================================================================*/

अटल पूर्णांक check_sig(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    पूर्णांक width;
    u_लघु s;

    SMC_SELECT_BANK(1);
    अगर (inw(ioaddr + BANK_SELECT) >> 8 != 0x33) अणु
	/* Try घातering up the chip */
	outw(0, ioaddr + CONTROL);
	mdelay(55);
    पूर्ण

    /* Try setting bus width */
    width = (link->resource[0]->flags == IO_DATA_PATH_WIDTH_AUTO);
    s = inb(ioaddr + CONFIG);
    अगर (width)
	s |= CFG_16BIT;
    अन्यथा
	s &= ~CFG_16BIT;
    outb(s, ioaddr + CONFIG);

    /* Check Base Address Register to make sure bus width is OK */
    s = inw(ioaddr + BASE_ADDR);
    अगर ((inw(ioaddr + BANK_SELECT) >> 8 == 0x33) &&
	((s >> 8) != (s & 0xff))) अणु
	SMC_SELECT_BANK(3);
	s = inw(ioaddr + REVISION);
	वापस s & 0xff;
    पूर्ण

    अगर (width) अणु
	    netdev_info(dev, "using 8-bit IO window\n");

	    smc91c92_suspend(link);
	    pcmcia_fixup_iowidth(link);
	    smc91c92_resume(link);
	    वापस check_sig(link);
    पूर्ण
    वापस -ENODEV;
पूर्ण

अटल पूर्णांक smc91c92_config(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अक्षर *name;
    पूर्णांक i, rev, j = 0;
    अचिन्हित पूर्णांक ioaddr;
    u_दीर्घ mir;

    dev_dbg(&link->dev, "smc91c92_config\n");

    smc->manfid = link->manf_id;
    smc->cardid = link->card_id;

    अगर ((smc->manfid == MANFID_OSITECH) &&
	(smc->cardid != PRODID_OSITECH_SEVEN)) अणु
	i = osi_config(link);
    पूर्ण अन्यथा अगर ((smc->manfid == MANFID_MOTOROLA) ||
	       ((smc->manfid == MANFID_MEGAHERTZ) &&
		((smc->cardid == PRODID_MEGAHERTZ_VARIOUS) ||
		 (smc->cardid == PRODID_MEGAHERTZ_EM3288)))) अणु
	i = mhz_mfc_config(link);
    पूर्ण अन्यथा अणु
	i = smc_config(link);
    पूर्ण
    अगर (i)
	    जाओ config_failed;

    i = pcmcia_request_irq(link, smc_पूर्णांकerrupt);
    अगर (i)
	    जाओ config_failed;
    i = pcmcia_enable_device(link);
    अगर (i)
	    जाओ config_failed;

    अगर (smc->manfid == MANFID_MOTOROLA)
	mot_config(link);

    dev->irq = link->irq;

    अगर ((अगर_port >= 0) && (अगर_port <= 2))
	dev->अगर_port = अगर_port;
    अन्यथा
	dev_notice(&link->dev, "invalid if_port requested\n");

    चयन (smc->manfid) अणु
    हाल MANFID_OSITECH:
    हाल MANFID_PSION:
	i = osi_setup(link, smc->manfid, smc->cardid); अवरोध;
    हाल MANFID_SMC:
    हाल MANFID_NEW_MEDIA:
	i = smc_setup(link); अवरोध;
    हाल 0x128: /* For broken Megahertz cards */
    हाल MANFID_MEGAHERTZ:
	i = mhz_setup(link); अवरोध;
    हाल MANFID_MOTOROLA:
    शेष: /* get the hw address from EEPROM */
	i = mot_setup(link); अवरोध;
    पूर्ण

    अगर (i != 0) अणु
	dev_notice(&link->dev, "Unable to find hardware address.\n");
	जाओ config_failed;
    पूर्ण

    smc->duplex = 0;
    smc->rx_ovrn = 0;

    rev = check_sig(link);
    name = "???";
    अगर (rev > 0)
	चयन (rev >> 4) अणु
	हाल 3: name = "92"; अवरोध;
	हाल 4: name = ((rev & 15) >= 6) ? "96" : "94"; अवरोध;
	हाल 5: name = "95"; अवरोध;
	हाल 7: name = "100"; अवरोध;
	हाल 8: name = "100-FD"; अवरोध;
	हाल 9: name = "110"; अवरोध;
	पूर्ण

    ioaddr = dev->base_addr;
    अगर (rev > 0) अणु
	u_दीर्घ mcr;
	SMC_SELECT_BANK(0);
	mir = inw(ioaddr + MEMINFO) & 0xff;
	अगर (mir == 0xff) mir++;
	/* Get scale factor क्रम memory size */
	mcr = ((rev >> 4) > 3) ? inw(ioaddr + MEMCFG) : 0x0200;
	mir *= 128 * (1<<((mcr >> 9) & 7));
	SMC_SELECT_BANK(1);
	smc->cfg = inw(ioaddr + CONFIG) & ~CFG_AUI_SELECT;
	smc->cfg |= CFG_NO_WAIT | CFG_16BIT | CFG_STATIC;
	अगर (smc->manfid == MANFID_OSITECH)
	    smc->cfg |= CFG_IRQ_SEL_1 | CFG_IRQ_SEL_0;
	अगर ((rev >> 4) >= 7)
	    smc->cfg |= CFG_MII_SELECT;
    पूर्ण अन्यथा
	mir = 0;

    अगर (smc->cfg & CFG_MII_SELECT) अणु
	SMC_SELECT_BANK(3);

	क्रम (i = 0; i < 32; i++) अणु
	    j = mdio_पढ़ो(dev, i, 1);
	    अगर ((j != 0) && (j != 0xffff)) अवरोध;
	पूर्ण
	smc->mii_अगर.phy_id = (i < 32) ? i : -1;

	SMC_SELECT_BANK(0);
    पूर्ण

    SET_NETDEV_DEV(dev, &link->dev);

    अगर (रेजिस्टर_netdev(dev) != 0) अणु
	dev_err(&link->dev, "register_netdev() failed\n");
	जाओ config_unकरो;
    पूर्ण

    netdev_info(dev, "smc91c%s rev %d: io %#3lx, irq %d, hw_addr %pM\n",
		name, (rev & 0x0f), dev->base_addr, dev->irq, dev->dev_addr);

    अगर (rev > 0) अणु
	अगर (mir & 0x3ff)
	    netdev_info(dev, "  %lu byte", mir);
	अन्यथा
	    netdev_info(dev, "  %lu kb", mir>>10);
	pr_cont(" buffer, %s xcvr\n",
		(smc->cfg & CFG_MII_SELECT) ? "MII" : अगर_names[dev->अगर_port]);
    पूर्ण

    अगर (smc->cfg & CFG_MII_SELECT) अणु
	अगर (smc->mii_अगर.phy_id != -1) अणु
	    netdev_dbg(dev, "  MII transceiver at index %d, status %x\n",
		       smc->mii_अगर.phy_id, j);
	पूर्ण अन्यथा अणु
	    netdev_notice(dev, "  No MII transceivers found!\n");
	पूर्ण
    पूर्ण
    वापस 0;

config_unकरो:
    unरेजिस्टर_netdev(dev);
config_failed:
    smc91c92_release(link);
    मुक्त_netdev(dev);
    वापस -ENODEV;
पूर्ण /* smc91c92_config */

अटल व्योम smc91c92_release(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "smc91c92_release\n");
	अगर (link->resource[2]->end) अणु
		काष्ठा net_device *dev = link->priv;
		काष्ठा smc_निजी *smc = netdev_priv(dev);
		iounmap(smc->base);
	पूर्ण
	pcmcia_disable_device(link);
पूर्ण

/*======================================================================

    MII पूर्णांकerface support क्रम SMC91cXX based cards
======================================================================*/

#घोषणा MDIO_SHIFT_CLK		0x04
#घोषणा MDIO_DATA_OUT		0x01
#घोषणा MDIO_सूची_WRITE		0x08
#घोषणा MDIO_DATA_WRITE0	(MDIO_सूची_WRITE)
#घोषणा MDIO_DATA_WRITE1	(MDIO_सूची_WRITE | MDIO_DATA_OUT)
#घोषणा MDIO_DATA_READ		0x02

अटल व्योम mdio_sync(अचिन्हित पूर्णांक addr)
अणु
    पूर्णांक bits;
    क्रम (bits = 0; bits < 32; bits++) अणु
	outb(MDIO_DATA_WRITE1, addr);
	outb(MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, addr);
    पूर्ण
पूर्ण

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक loc)
अणु
    अचिन्हित पूर्णांक addr = dev->base_addr + MGMT;
    u_पूर्णांक cmd = (0x06<<10)|(phy_id<<5)|loc;
    पूर्णांक i, retval = 0;

    mdio_sync(addr);
    क्रम (i = 13; i >= 0; i--) अणु
	पूर्णांक dat = (cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
	outb(dat, addr);
	outb(dat | MDIO_SHIFT_CLK, addr);
    पूर्ण
    क्रम (i = 19; i > 0; i--) अणु
	outb(0, addr);
	retval = (retval << 1) | ((inb(addr) & MDIO_DATA_READ) != 0);
	outb(MDIO_SHIFT_CLK, addr);
    पूर्ण
    वापस (retval>>1) & 0xffff;
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक value)
अणु
    अचिन्हित पूर्णांक addr = dev->base_addr + MGMT;
    u_पूर्णांक cmd = (0x05<<28)|(phy_id<<23)|(loc<<18)|(1<<17)|value;
    पूर्णांक i;

    mdio_sync(addr);
    क्रम (i = 31; i >= 0; i--) अणु
	पूर्णांक dat = (cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
	outb(dat, addr);
	outb(dat | MDIO_SHIFT_CLK, addr);
    पूर्ण
    क्रम (i = 1; i >= 0; i--) अणु
	outb(0, addr);
	outb(MDIO_SHIFT_CLK, addr);
    पूर्ण
पूर्ण

/*======================================================================

    The driver core code, most of which should be common with a
    non-PCMCIA implementation.

======================================================================*/

#अगर_घोषित PCMCIA_DEBUG
अटल व्योम smc_dump(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    u_लघु i, w, save;
    save = inw(ioaddr + BANK_SELECT);
    क्रम (w = 0; w < 4; w++) अणु
	SMC_SELECT_BANK(w);
	netdev_dbg(dev, "bank %d: ", w);
	क्रम (i = 0; i < 14; i += 2)
	    pr_cont(" %04x", inw(ioaddr + i));
	pr_cont("\n");
    पूर्ण
    outw(save, ioaddr + BANK_SELECT);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक smc_खोलो(काष्ठा net_device *dev)
अणु
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    काष्ठा pcmcia_device *link = smc->p_dev;

    dev_dbg(&link->dev, "%s: smc_open(%p), ID/Window %4.4x.\n",
	  dev->name, dev, inw(dev->base_addr + BANK_SELECT));
#अगर_घोषित PCMCIA_DEBUG
    smc_dump(dev);
#पूर्ण_अगर

    /* Check that the PCMCIA card is still here. */
    अगर (!pcmcia_dev_present(link))
	वापस -ENODEV;
    /* Physical device present signature. */
    अगर (check_sig(link) < 0) अणु
	netdev_info(dev, "Yikes!  Bad chip signature!\n");
	वापस -ENODEV;
    पूर्ण
    link->खोलो++;

    netअगर_start_queue(dev);
    smc->saved_skb = शून्य;
    smc->packets_रुकोing = 0;

    smc_reset(dev);
    समयr_setup(&smc->media, media_check, 0);
    mod_समयr(&smc->media, jअगरfies + HZ);

    वापस 0;
पूर्ण /* smc_खोलो */

/*====================================================================*/

अटल पूर्णांक smc_बंद(काष्ठा net_device *dev)
अणु
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    काष्ठा pcmcia_device *link = smc->p_dev;
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;

    dev_dbg(&link->dev, "%s: smc_close(), status %4.4x.\n",
	  dev->name, inw(ioaddr + BANK_SELECT));

    netअगर_stop_queue(dev);

    /* Shut off all पूर्णांकerrupts, and turn off the Tx and Rx sections.
       Don't bother to check क्रम chip present. */
    SMC_SELECT_BANK(2);	/* Nominally paranoia, but करो no assume... */
    outw(0, ioaddr + INTERRUPT);
    SMC_SELECT_BANK(0);
    mask_bits(0xff00, ioaddr + RCR);
    mask_bits(0xff00, ioaddr + TCR);

    /* Put the chip पूर्णांकo घातer-करोwn mode. */
    SMC_SELECT_BANK(1);
    outw(CTL_POWERDOWN, ioaddr + CONTROL );

    link->खोलो--;
    del_समयr_sync(&smc->media);

    वापस 0;
पूर्ण /* smc_बंद */

/*======================================================================

   Transfer a packet to the hardware and trigger the packet send.
   This may be called at either from either the Tx queue code
   or the पूर्णांकerrupt handler.

======================================================================*/

अटल व्योम smc_hardware_send_packet(काष्ठा net_device * dev)
अणु
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    काष्ठा sk_buff *skb = smc->saved_skb;
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    u_अक्षर packet_no;

    अगर (!skb) अणु
	netdev_err(dev, "In XMIT with no packet to send\n");
	वापस;
    पूर्ण

    /* There should be a packet slot रुकोing. */
    packet_no = inw(ioaddr + PNR_ARR) >> 8;
    अगर (packet_no & 0x80) अणु
	/* If not, there is a hardware problem!  Likely an ejected card. */
	netdev_warn(dev, "hardware Tx buffer allocation failed, status %#2.2x\n",
		    packet_no);
	dev_kमुक्त_skb_irq(skb);
	smc->saved_skb = शून्य;
	netअगर_start_queue(dev);
	वापस;
    पूर्ण

    dev->stats.tx_bytes += skb->len;
    /* The card should use the just-allocated buffer. */
    outw(packet_no, ioaddr + PNR_ARR);
    /* poपूर्णांक to the beginning of the packet */
    outw(PTR_AUTOINC , ioaddr + POINTER);

    /* Send the packet length (+6 क्रम status, length and ctl byte)
       and the status word (set to zeros). */
    अणु
	u_अक्षर *buf = skb->data;
	u_पूर्णांक length = skb->len; /* The chip will pad to ethernet min. */

	netdev_dbg(dev, "Trying to xmit packet of length %d\n", length);
	
	/* send the packet length: +6 क्रम status word, length, and ctl */
	outw(0, ioaddr + DATA_1);
	outw(length + 6, ioaddr + DATA_1);
	outsw(ioaddr + DATA_1, buf, length >> 1);
	
	/* The odd last byte, अगर there is one, goes in the control word. */
	outw((length & 1) ? 0x2000 | buf[length-1] : 0, ioaddr + DATA_1);
    पूर्ण

    /* Enable the Tx पूर्णांकerrupts, both Tx (TxErr) and TxEmpty. */
    outw(((IM_TX_INT|IM_TX_EMPTY_INT)<<8) |
	 (inw(ioaddr + INTERRUPT) & 0xff00),
	 ioaddr + INTERRUPT);

    /* The chip करोes the rest of the work. */
    outw(MC_ENQUEUE , ioaddr + MMU_CMD);

    smc->saved_skb = शून्य;
    dev_kमुक्त_skb_irq(skb);
    netअगर_trans_update(dev);
    netअगर_start_queue(dev);
पूर्ण

/*====================================================================*/

अटल व्योम smc_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;

    netdev_notice(dev, "transmit timed out, Tx_status %2.2x status %4.4x.\n",
		  inw(ioaddr)&0xff, inw(ioaddr + 2));
    dev->stats.tx_errors++;
    smc_reset(dev);
    netअगर_trans_update(dev); /* prevent tx समयout */
    smc->saved_skb = शून्य;
    netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t smc_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    u_लघु num_pages;
    लघु समय_out, ir;
    अचिन्हित दीर्घ flags;

    netअगर_stop_queue(dev);

    netdev_dbg(dev, "smc_start_xmit(length = %d) called, status %04x\n",
	       skb->len, inw(ioaddr + 2));

    अगर (smc->saved_skb) अणु
	/* THIS SHOULD NEVER HAPPEN. */
	dev->stats.tx_पातed_errors++;
	netdev_dbg(dev, "Internal error -- sent packet while busy\n");
	वापस NETDEV_TX_BUSY;
    पूर्ण
    smc->saved_skb = skb;

    num_pages = skb->len >> 8;

    अगर (num_pages > 7) अणु
	netdev_err(dev, "Far too big packet error: %d pages\n", num_pages);
	dev_kमुक्त_skb (skb);
	smc->saved_skb = शून्य;
	dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;		/* Do not re-queue this packet. */
    पूर्ण
    /* A packet is now रुकोing. */
    smc->packets_रुकोing++;

    spin_lock_irqsave(&smc->lock, flags);
    SMC_SELECT_BANK(2);	/* Paranoia, we should always be in winकरोw 2 */

    /* need MC_RESET to keep the memory consistent. errata? */
    अगर (smc->rx_ovrn) अणु
	outw(MC_RESET, ioaddr + MMU_CMD);
	smc->rx_ovrn = 0;
    पूर्ण

    /* Allocate the memory; send the packet now अगर we win. */
    outw(MC_ALLOC | num_pages, ioaddr + MMU_CMD);
    क्रम (समय_out = MEMORY_WAIT_TIME; समय_out >= 0; समय_out--) अणु
	ir = inw(ioaddr+INTERRUPT);
	अगर (ir & IM_ALLOC_INT) अणु
	    /* Acknowledge the पूर्णांकerrupt, send the packet. */
	    outw((ir&0xff00) | IM_ALLOC_INT, ioaddr + INTERRUPT);
	    smc_hardware_send_packet(dev);	/* Send the packet now.. */
	    spin_unlock_irqrestore(&smc->lock, flags);
	    वापस NETDEV_TX_OK;
	पूर्ण
    पूर्ण

    /* Otherwise defer until the Tx-space-allocated पूर्णांकerrupt. */
    netdev_dbg(dev, "memory allocation deferred.\n");
    outw((IM_ALLOC_INT << 8) | (ir & 0xff00), ioaddr + INTERRUPT);
    spin_unlock_irqrestore(&smc->lock, flags);

    वापस NETDEV_TX_OK;
पूर्ण

/*======================================================================

    Handle a Tx anomalous event.  Entered जबतक in Winकरोw 2.

======================================================================*/

अटल व्योम smc_tx_err(काष्ठा net_device * dev)
अणु
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    पूर्णांक saved_packet = inw(ioaddr + PNR_ARR) & 0xff;
    पूर्णांक packet_no = inw(ioaddr + FIFO_PORTS) & 0x7f;
    पूर्णांक tx_status;

    /* select this as the packet to पढ़ो from */
    outw(packet_no, ioaddr + PNR_ARR);

    /* पढ़ो the first word from this packet */
    outw(PTR_AUTOINC | PTR_READ | 0, ioaddr + POINTER);

    tx_status = inw(ioaddr + DATA_1);

    dev->stats.tx_errors++;
    अगर (tx_status & TS_LOSTCAR) dev->stats.tx_carrier_errors++;
    अगर (tx_status & TS_LATCOL)  dev->stats.tx_winकरोw_errors++;
    अगर (tx_status & TS_16COL) अणु
	dev->stats.tx_पातed_errors++;
	smc->tx_err++;
    पूर्ण

    अगर (tx_status & TS_SUCCESS) अणु
	netdev_notice(dev, "Successful packet caused error interrupt?\n");
    पूर्ण
    /* re-enable transmit */
    SMC_SELECT_BANK(0);
    outw(inw(ioaddr + TCR) | TCR_ENABLE | smc->duplex, ioaddr + TCR);
    SMC_SELECT_BANK(2);

    outw(MC_FREEPKT, ioaddr + MMU_CMD); 	/* Free the packet memory. */

    /* one less packet रुकोing क्रम me */
    smc->packets_रुकोing--;

    outw(saved_packet, ioaddr + PNR_ARR);
पूर्ण

/*====================================================================*/

अटल व्योम smc_eph_irq(काष्ठा net_device *dev)
अणु
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    u_लघु card_stats, ephs;

    SMC_SELECT_BANK(0);
    ephs = inw(ioaddr + EPH);
    netdev_dbg(dev, "Ethernet protocol handler interrupt, status %4.4x.\n",
	       ephs);
    /* Could be a counter roll-over warning: update stats. */
    card_stats = inw(ioaddr + COUNTER);
    /* single collisions */
    dev->stats.collisions += card_stats & 0xF;
    card_stats >>= 4;
    /* multiple collisions */
    dev->stats.collisions += card_stats & 0xF;
#अगर 0 		/* These are क्रम when linux supports these statistics */
    card_stats >>= 4;			/* deferred */
    card_stats >>= 4;			/* excess deferred */
#पूर्ण_अगर
    /* If we had a transmit error we must re-enable the transmitter. */
    outw(inw(ioaddr + TCR) | TCR_ENABLE | smc->duplex, ioaddr + TCR);

    /* Clear a link error पूर्णांकerrupt. */
    SMC_SELECT_BANK(1);
    outw(CTL_AUTO_RELEASE | 0x0000, ioaddr + CONTROL);
    outw(CTL_AUTO_RELEASE | CTL_TE_ENABLE | CTL_CR_ENABLE,
	 ioaddr + CONTROL);
    SMC_SELECT_BANK(2);
पूर्ण

/*====================================================================*/

अटल irqवापस_t smc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
    काष्ठा net_device *dev = dev_id;
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr;
    u_लघु saved_bank, saved_poपूर्णांकer, mask, status;
    अचिन्हित पूर्णांक handled = 1;
    अक्षर bogus_cnt = INTR_WORK;		/* Work we are willing to करो. */

    अगर (!netअगर_device_present(dev))
	वापस IRQ_NONE;

    ioaddr = dev->base_addr;

    netdev_dbg(dev, "SMC91c92 interrupt %d at %#x.\n",
	       irq, ioaddr);

    spin_lock(&smc->lock);
    smc->watchकरोg = 0;
    saved_bank = inw(ioaddr + BANK_SELECT);
    अगर ((saved_bank & 0xff00) != 0x3300) अणु
	/* The device करोes not exist -- the card could be off-line, or
	   maybe it has been ejected. */
	netdev_dbg(dev, "SMC91c92 interrupt %d for non-existent/ejected device.\n",
		   irq);
	handled = 0;
	जाओ irq_करोne;
    पूर्ण

    SMC_SELECT_BANK(2);
    saved_poपूर्णांकer = inw(ioaddr + POINTER);
    mask = inw(ioaddr + INTERRUPT) >> 8;
    /* clear all पूर्णांकerrupts */
    outw(0, ioaddr + INTERRUPT);

    करो अणु /* पढ़ो the status flag, and mask it */
	status = inw(ioaddr + INTERRUPT) & 0xff;
	netdev_dbg(dev, "Status is %#2.2x (mask %#2.2x).\n",
		   status, mask);
	अगर ((status & mask) == 0) अणु
	    अगर (bogus_cnt == INTR_WORK)
		handled = 0;
	    अवरोध;
	पूर्ण
	अगर (status & IM_RCV_INT) अणु
	    /* Got a packet(s). */
	    smc_rx(dev);
	पूर्ण
	अगर (status & IM_TX_INT) अणु
	    smc_tx_err(dev);
	    outw(IM_TX_INT, ioaddr + INTERRUPT);
	पूर्ण
	status &= mask;
	अगर (status & IM_TX_EMPTY_INT) अणु
	    outw(IM_TX_EMPTY_INT, ioaddr + INTERRUPT);
	    mask &= ~IM_TX_EMPTY_INT;
	    dev->stats.tx_packets += smc->packets_रुकोing;
	    smc->packets_रुकोing = 0;
	पूर्ण
	अगर (status & IM_ALLOC_INT) अणु
	    /* Clear this पूर्णांकerrupt so it करोesn't happen again */
	    mask &= ~IM_ALLOC_INT;
	
	    smc_hardware_send_packet(dev);
	
	    /* enable xmit पूर्णांकerrupts based on this */
	    mask |= (IM_TX_EMPTY_INT | IM_TX_INT);
	
	    /* and let the card send more packets to me */
	    netअगर_wake_queue(dev);
	पूर्ण
	अगर (status & IM_RX_OVRN_INT) अणु
	    dev->stats.rx_errors++;
	    dev->stats.rx_fअगरo_errors++;
	    अगर (smc->duplex)
		smc->rx_ovrn = 1; /* need MC_RESET outside smc_पूर्णांकerrupt */
	    outw(IM_RX_OVRN_INT, ioaddr + INTERRUPT);
	पूर्ण
	अगर (status & IM_EPH_INT)
	    smc_eph_irq(dev);
    पूर्ण जबतक (--bogus_cnt);

    netdev_dbg(dev, "  Restoring saved registers mask %2.2x bank %4.4x pointer %4.4x.\n",
	       mask, saved_bank, saved_poपूर्णांकer);

    /* restore state रेजिस्टर */
    outw((mask<<8), ioaddr + INTERRUPT);
    outw(saved_poपूर्णांकer, ioaddr + POINTER);
    SMC_SELECT_BANK(saved_bank);

    netdev_dbg(dev, "Exiting interrupt IRQ%d.\n", irq);

irq_करोne:

    अगर ((smc->manfid == MANFID_OSITECH) &&
	(smc->cardid != PRODID_OSITECH_SEVEN)) अणु
	/* Retrigger पूर्णांकerrupt अगर needed */
	mask_bits(0x00ff, ioaddr-0x10+OSITECH_RESET_ISR);
	set_bits(0x0300, ioaddr-0x10+OSITECH_RESET_ISR);
    पूर्ण
    अगर (smc->manfid == MANFID_MOTOROLA) अणु
	u_अक्षर cor;
	cor = पढ़ोb(smc->base + MOT_UART + CISREG_COR);
	ग_लिखोb(cor & ~COR_IREQ_ENA, smc->base + MOT_UART + CISREG_COR);
	ग_लिखोb(cor, smc->base + MOT_UART + CISREG_COR);
	cor = पढ़ोb(smc->base + MOT_LAN + CISREG_COR);
	ग_लिखोb(cor & ~COR_IREQ_ENA, smc->base + MOT_LAN + CISREG_COR);
	ग_लिखोb(cor, smc->base + MOT_LAN + CISREG_COR);
    पूर्ण

    अगर ((smc->base != शून्य) &&  /* Megahertz MFC's */
	(smc->manfid == MANFID_MEGAHERTZ) &&
	(smc->cardid == PRODID_MEGAHERTZ_EM3288)) अणु

	u_अक्षर पंचांगp;
	पंचांगp = पढ़ोb(smc->base+MEGAHERTZ_ISR);
	पंचांगp = पढ़ोb(smc->base+MEGAHERTZ_ISR);

	/* Retrigger पूर्णांकerrupt अगर needed */
	ग_लिखोb(पंचांगp, smc->base + MEGAHERTZ_ISR);
	ग_लिखोb(पंचांगp, smc->base + MEGAHERTZ_ISR);
    पूर्ण

    spin_unlock(&smc->lock);
    वापस IRQ_RETVAL(handled);
पूर्ण

/*====================================================================*/

अटल व्योम smc_rx(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    पूर्णांक rx_status;
    पूर्णांक packet_length;	/* Caution: not frame length, rather words
			   to transfer from the chip. */

    /* Assertion: we are in Winकरोw 2. */

    अगर (inw(ioaddr + FIFO_PORTS) & FP_RXEMPTY) अणु
	netdev_err(dev, "smc_rx() with nothing on Rx FIFO\n");
	वापस;
    पूर्ण

    /*  Reset the पढ़ो poपूर्णांकer, and पढ़ो the status and packet length. */
    outw(PTR_READ | PTR_RCV | PTR_AUTOINC, ioaddr + POINTER);
    rx_status = inw(ioaddr + DATA_1);
    packet_length = inw(ioaddr + DATA_1) & 0x07ff;

    netdev_dbg(dev, "Receive status %4.4x length %d.\n",
	       rx_status, packet_length);

    अगर (!(rx_status & RS_ERRORS)) अणु
	/* करो stuff to make a new packet */
	काष्ठा sk_buff *skb;
	काष्ठा smc_निजी *smc = netdev_priv(dev);
	
	/* Note: packet_length adds 5 or 6 extra bytes here! */
	skb = netdev_alloc_skb(dev, packet_length+2);
	
	अगर (skb == शून्य) अणु
	    netdev_dbg(dev, "Low memory, packet dropped.\n");
	    dev->stats.rx_dropped++;
	    outw(MC_RELEASE, ioaddr + MMU_CMD);
	    वापस;
	पूर्ण
	
	packet_length -= (rx_status & RS_ODDFRAME ? 5 : 6);
	skb_reserve(skb, 2);
	insw(ioaddr+DATA_1, skb_put(skb, packet_length),
	     (packet_length+1)>>1);
	skb->protocol = eth_type_trans(skb, dev);
	
	netअगर_rx(skb);
	smc->last_rx = jअगरfies;
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += packet_length;
	अगर (rx_status & RS_MULTICAST)
	    dev->stats.multicast++;
    पूर्ण अन्यथा अणु
	/* error ... */
	dev->stats.rx_errors++;
	
	अगर (rx_status & RS_ALGNERR)  dev->stats.rx_frame_errors++;
	अगर (rx_status & (RS_TOOSHORT | RS_TOOLONG))
	    dev->stats.rx_length_errors++;
	अगर (rx_status & RS_BADCRC)	dev->stats.rx_crc_errors++;
    पूर्ण
    /* Let the MMU मुक्त the memory of this packet. */
    outw(MC_RELEASE, ioaddr + MMU_CMD);
पूर्ण

/*======================================================================

    Set the receive mode.

    This routine is used by both the protocol level to notअगरy us of
    promiscuous/multicast mode changes, and by the खोलो/reset code to
    initialize the Rx रेजिस्टरs.  We always set the multicast list and
    leave the receiver running.

======================================================================*/

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अचिन्हित अक्षर multicast_table[8];
    अचिन्हित दीर्घ flags;
    u_लघु rx_cfg_setting;
    पूर्णांक i;

    स_रखो(multicast_table, 0, माप(multicast_table));

    अगर (dev->flags & IFF_PROMISC) अणु
	rx_cfg_setting = RxStripCRC | RxEnable | RxPromisc | RxAllMulti;
    पूर्ण अन्यथा अगर (dev->flags & IFF_ALLMULTI)
	rx_cfg_setting = RxStripCRC | RxEnable | RxAllMulti;
    अन्यथा अणु
	अगर (!netdev_mc_empty(dev)) अणु
	    काष्ठा netdev_hw_addr *ha;

	    netdev_क्रम_each_mc_addr(ha, dev) अणु
		u_पूर्णांक position = ether_crc(6, ha->addr);
		multicast_table[position >> 29] |= 1 << ((position >> 26) & 7);
	    पूर्ण
	पूर्ण
	rx_cfg_setting = RxStripCRC | RxEnable;
    पूर्ण

    /* Load MC table and Rx setting पूर्णांकo the chip without पूर्णांकerrupts. */
    spin_lock_irqsave(&smc->lock, flags);
    SMC_SELECT_BANK(3);
    क्रम (i = 0; i < 8; i++)
	outb(multicast_table[i], ioaddr + MULTICAST0 + i);
    SMC_SELECT_BANK(0);
    outw(rx_cfg_setting, ioaddr + RCR);
    SMC_SELECT_BANK(2);
    spin_unlock_irqrestore(&smc->lock, flags);
पूर्ण

/*======================================================================

    Senses when a card's config changes. Here, it's coax or TP.

======================================================================*/

अटल पूर्णांक s9k_config(काष्ठा net_device *dev, काष्ठा अगरmap *map)
अणु
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अगर ((map->port != (u_अक्षर)(-1)) && (map->port != dev->अगर_port)) अणु
	अगर (smc->cfg & CFG_MII_SELECT)
	    वापस -EOPNOTSUPP;
	अन्यथा अगर (map->port > 2)
	    वापस -EINVAL;
	dev->अगर_port = map->port;
	netdev_info(dev, "switched to %s port\n", अगर_names[dev->अगर_port]);
	smc_reset(dev);
    पूर्ण
    वापस 0;
पूर्ण

/*======================================================================

    Reset the chip, reloading every रेजिस्टर that might be corrupted.

======================================================================*/

/*
  Set transceiver type, perhaps to something other than what the user
  specअगरied in dev->अगर_port.
*/
अटल व्योम smc_set_xcvr(काष्ठा net_device *dev, पूर्णांक अगर_port)
अणु
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    u_लघु saved_bank;

    saved_bank = inw(ioaddr + BANK_SELECT);
    SMC_SELECT_BANK(1);
    अगर (अगर_port == 2) अणु
	outw(smc->cfg | CFG_AUI_SELECT, ioaddr + CONFIG);
	अगर ((smc->manfid == MANFID_OSITECH) &&
	    (smc->cardid != PRODID_OSITECH_SEVEN))
	    set_bits(OSI_AUI_PWR, ioaddr - 0x10 + OSITECH_AUI_PWR);
	smc->media_status = ((dev->अगर_port == 0) ? 0x0001 : 0x0002);
    पूर्ण अन्यथा अणु
	outw(smc->cfg, ioaddr + CONFIG);
	अगर ((smc->manfid == MANFID_OSITECH) &&
	    (smc->cardid != PRODID_OSITECH_SEVEN))
	    mask_bits(~OSI_AUI_PWR, ioaddr - 0x10 + OSITECH_AUI_PWR);
	smc->media_status = ((dev->अगर_port == 0) ? 0x0012 : 0x4001);
    पूर्ण
    SMC_SELECT_BANK(saved_bank);
पूर्ण

अटल व्योम smc_reset(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    काष्ठा smc_निजी *smc = netdev_priv(dev);
    पूर्णांक i;

    netdev_dbg(dev, "smc91c92 reset called.\n");

    /* The first पूर्णांकeraction must be a ग_लिखो to bring the chip out
       of sleep mode. */
    SMC_SELECT_BANK(0);
    /* Reset the chip. */
    outw(RCR_SOFTRESET, ioaddr + RCR);
    udelay(10);

    /* Clear the transmit and receive configuration रेजिस्टरs. */
    outw(RCR_CLEAR, ioaddr + RCR);
    outw(TCR_CLEAR, ioaddr + TCR);

    /* Set the Winकरोw 1 control, configuration and station addr रेजिस्टरs.
       No poपूर्णांक in writing the I/O base रेजिस्टर ;-> */
    SMC_SELECT_BANK(1);
    /* Automatically release successfully transmitted packets,
       Accept link errors, counter and Tx error पूर्णांकerrupts. */
    outw(CTL_AUTO_RELEASE | CTL_TE_ENABLE | CTL_CR_ENABLE,
	 ioaddr + CONTROL);
    smc_set_xcvr(dev, dev->अगर_port);
    अगर ((smc->manfid == MANFID_OSITECH) &&
	(smc->cardid != PRODID_OSITECH_SEVEN))
	outw((dev->अगर_port == 2 ? OSI_AUI_PWR : 0) |
	     (inw(ioaddr-0x10+OSITECH_AUI_PWR) & 0xff00),
	     ioaddr - 0x10 + OSITECH_AUI_PWR);

    /* Fill in the physical address.  The databook is wrong about the order! */
    क्रम (i = 0; i < 6; i += 2)
	outw((dev->dev_addr[i+1]<<8)+dev->dev_addr[i],
	     ioaddr + ADDR0 + i);

    /* Reset the MMU */
    SMC_SELECT_BANK(2);
    outw(MC_RESET, ioaddr + MMU_CMD);
    outw(0, ioaddr + INTERRUPT);

    /* Re-enable the chip. */
    SMC_SELECT_BANK(0);
    outw(((smc->cfg & CFG_MII_SELECT) ? 0 : TCR_MONCSN) |
	 TCR_ENABLE | TCR_PAD_EN | smc->duplex, ioaddr + TCR);
    set_rx_mode(dev);

    अगर (smc->cfg & CFG_MII_SELECT) अणु
	SMC_SELECT_BANK(3);

	/* Reset MII */
	mdio_ग_लिखो(dev, smc->mii_अगर.phy_id, 0, 0x8000);

	/* Advertise 100F, 100H, 10F, 10H */
	mdio_ग_लिखो(dev, smc->mii_अगर.phy_id, 4, 0x01e1);

	/* Restart MII स्वतःnegotiation */
	mdio_ग_लिखो(dev, smc->mii_अगर.phy_id, 0, 0x0000);
	mdio_ग_लिखो(dev, smc->mii_अगर.phy_id, 0, 0x1200);
    पूर्ण

    /* Enable पूर्णांकerrupts. */
    SMC_SELECT_BANK(2);
    outw((IM_EPH_INT | IM_RX_OVRN_INT | IM_RCV_INT) << 8,
	 ioaddr + INTERRUPT);
पूर्ण

/*======================================================================

    Media selection समयr routine

======================================================================*/

अटल व्योम media_check(काष्ठा समयr_list *t)
अणु
    काष्ठा smc_निजी *smc = from_समयr(smc, t, media);
    काष्ठा net_device *dev = smc->mii_अगर.dev;
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    u_लघु i, media, saved_bank;
    u_लघु link;
    अचिन्हित दीर्घ flags;

    spin_lock_irqsave(&smc->lock, flags);

    saved_bank = inw(ioaddr + BANK_SELECT);

    अगर (!netअगर_device_present(dev))
	जाओ reschedule;

    SMC_SELECT_BANK(2);

    /* need MC_RESET to keep the memory consistent. errata? */
    अगर (smc->rx_ovrn) अणु
	outw(MC_RESET, ioaddr + MMU_CMD);
	smc->rx_ovrn = 0;
    पूर्ण
    i = inw(ioaddr + INTERRUPT);
    SMC_SELECT_BANK(0);
    media = inw(ioaddr + EPH) & EPH_LINK_OK;
    SMC_SELECT_BANK(1);
    media |= (inw(ioaddr + CONFIG) & CFG_AUI_SELECT) ? 2 : 1;

    SMC_SELECT_BANK(saved_bank);
    spin_unlock_irqrestore(&smc->lock, flags);

    /* Check क्रम pending पूर्णांकerrupt with watchकरोg flag set: with
       this, we can limp aदीर्घ even अगर the पूर्णांकerrupt is blocked */
    अगर (smc->watchकरोg++ && ((i>>8) & i)) अणु
	अगर (!smc->fast_poll)
	    netdev_info(dev, "interrupt(s) dropped!\n");
	local_irq_save(flags);
	smc_पूर्णांकerrupt(dev->irq, dev);
	local_irq_restore(flags);
	smc->fast_poll = HZ;
    पूर्ण
    अगर (smc->fast_poll) अणु
	smc->fast_poll--;
	smc->media.expires = jअगरfies + HZ/100;
	add_समयr(&smc->media);
	वापस;
    पूर्ण

    spin_lock_irqsave(&smc->lock, flags);

    saved_bank = inw(ioaddr + BANK_SELECT);

    अगर (smc->cfg & CFG_MII_SELECT) अणु
	अगर (smc->mii_अगर.phy_id < 0)
	    जाओ reschedule;

	SMC_SELECT_BANK(3);
	link = mdio_पढ़ो(dev, smc->mii_अगर.phy_id, 1);
	अगर (!link || (link == 0xffff)) अणु
	    netdev_info(dev, "MII is missing!\n");
	    smc->mii_अगर.phy_id = -1;
	    जाओ reschedule;
	पूर्ण

	link &= 0x0004;
	अगर (link != smc->link_status) अणु
	    u_लघु p = mdio_पढ़ो(dev, smc->mii_अगर.phy_id, 5);
	    netdev_info(dev, "%s link beat\n", link ? "found" : "lost");
	    smc->duplex = (((p & 0x0100) || ((p & 0x1c0) == 0x40))
			   ? TCR_FDUPLX : 0);
	    अगर (link) अणु
		netdev_info(dev, "autonegotiation complete: "
			    "%dbaseT-%cD selected\n",
			    (p & 0x0180) ? 100 : 10, smc->duplex ? 'F' : 'H');
	    पूर्ण
	    SMC_SELECT_BANK(0);
	    outw(inw(ioaddr + TCR) | smc->duplex, ioaddr + TCR);
	    smc->link_status = link;
	पूर्ण
	जाओ reschedule;
    पूर्ण

    /* Ignore collisions unless we've had no rx's recently */
    अगर (समय_after(jअगरfies, smc->last_rx + HZ)) अणु
	अगर (smc->tx_err || (smc->media_status & EPH_16COL))
	    media |= EPH_16COL;
    पूर्ण
    smc->tx_err = 0;

    अगर (media != smc->media_status) अणु
	अगर ((media & smc->media_status & 1) &&
	    ((smc->media_status ^ media) & EPH_LINK_OK))
	    netdev_info(dev, "%s link beat\n",
			smc->media_status & EPH_LINK_OK ? "lost" : "found");
	अन्यथा अगर ((media & smc->media_status & 2) &&
		 ((smc->media_status ^ media) & EPH_16COL))
	    netdev_info(dev, "coax cable %s\n",
			media & EPH_16COL ? "problem" : "ok");
	अगर (dev->अगर_port == 0) अणु
	    अगर (media & 1) अणु
		अगर (media & EPH_LINK_OK)
		    netdev_info(dev, "flipped to 10baseT\n");
		अन्यथा
		    smc_set_xcvr(dev, 2);
	    पूर्ण अन्यथा अणु
		अगर (media & EPH_16COL)
		    smc_set_xcvr(dev, 1);
		अन्यथा
		    netdev_info(dev, "flipped to 10base2\n");
	    पूर्ण
	पूर्ण
	smc->media_status = media;
    पूर्ण

reschedule:
    smc->media.expires = jअगरfies + HZ;
    add_समयr(&smc->media);
    SMC_SELECT_BANK(saved_bank);
    spin_unlock_irqrestore(&smc->lock, flags);
पूर्ण

अटल पूर्णांक smc_link_ok(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    काष्ठा smc_निजी *smc = netdev_priv(dev);

    अगर (smc->cfg & CFG_MII_SELECT) अणु
	वापस mii_link_ok(&smc->mii_अगर);
    पूर्ण अन्यथा अणु
        SMC_SELECT_BANK(0);
	वापस inw(ioaddr + EPH) & EPH_LINK_OK;
    पूर्ण
पूर्ण

अटल व्योम smc_netdev_get_ecmd(काष्ठा net_device *dev,
				काष्ठा ethtool_link_ksettings *ecmd)
अणु
	u16 पंचांगp;
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	u32 supported;

	supported = (SUPPORTED_TP | SUPPORTED_AUI |
		     SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full);

	SMC_SELECT_BANK(1);
	पंचांगp = inw(ioaddr + CONFIG);
	ecmd->base.port = (पंचांगp & CFG_AUI_SELECT) ? PORT_AUI : PORT_TP;
	ecmd->base.speed = SPEED_10;
	ecmd->base.phy_address = ioaddr + MGMT;

	SMC_SELECT_BANK(0);
	पंचांगp = inw(ioaddr + TCR);
	ecmd->base.duplex = (पंचांगp & TCR_FDUPLX) ? DUPLEX_FULL : DUPLEX_HALF;

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
पूर्ण

अटल पूर्णांक smc_netdev_set_ecmd(काष्ठा net_device *dev,
			       स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	u16 पंचांगp;
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;

	अगर (ecmd->base.speed != SPEED_10)
		वापस -EINVAL;
	अगर (ecmd->base.duplex != DUPLEX_HALF &&
	    ecmd->base.duplex != DUPLEX_FULL)
		वापस -EINVAL;
	अगर (ecmd->base.port != PORT_TP && ecmd->base.port != PORT_AUI)
		वापस -EINVAL;

	अगर (ecmd->base.port == PORT_AUI)
		smc_set_xcvr(dev, 1);
	अन्यथा
		smc_set_xcvr(dev, 0);

	SMC_SELECT_BANK(0);
	पंचांगp = inw(ioaddr + TCR);
	अगर (ecmd->base.duplex == DUPLEX_FULL)
		पंचांगp |= TCR_FDUPLX;
	अन्यथा
		पंचांगp &= ~TCR_FDUPLX;
	outw(पंचांगp, ioaddr + TCR);

	वापस 0;
पूर्ण

अटल पूर्णांक check_अगर_running(काष्ठा net_device *dev)
अणु
	अगर (!netअगर_running(dev))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम smc_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
पूर्ण

अटल पूर्णांक smc_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा smc_निजी *smc = netdev_priv(dev);
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	u16 saved_bank = inw(ioaddr + BANK_SELECT);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&smc->lock, flags);
	SMC_SELECT_BANK(3);
	अगर (smc->cfg & CFG_MII_SELECT)
		mii_ethtool_get_link_ksettings(&smc->mii_अगर, ecmd);
	अन्यथा
		smc_netdev_get_ecmd(dev, ecmd);
	SMC_SELECT_BANK(saved_bank);
	spin_unlock_irqrestore(&smc->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक smc_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा smc_निजी *smc = netdev_priv(dev);
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	u16 saved_bank = inw(ioaddr + BANK_SELECT);
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&smc->lock, flags);
	SMC_SELECT_BANK(3);
	अगर (smc->cfg & CFG_MII_SELECT)
		ret = mii_ethtool_set_link_ksettings(&smc->mii_अगर, ecmd);
	अन्यथा
		ret = smc_netdev_set_ecmd(dev, ecmd);
	SMC_SELECT_BANK(saved_bank);
	spin_unlock_irqrestore(&smc->lock, flags);
	वापस ret;
पूर्ण

अटल u32 smc_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा smc_निजी *smc = netdev_priv(dev);
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	u16 saved_bank = inw(ioaddr + BANK_SELECT);
	u32 ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&smc->lock, flags);
	SMC_SELECT_BANK(3);
	ret = smc_link_ok(dev);
	SMC_SELECT_BANK(saved_bank);
	spin_unlock_irqrestore(&smc->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक smc_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा smc_निजी *smc = netdev_priv(dev);
	अगर (smc->cfg & CFG_MII_SELECT) अणु
		अचिन्हित पूर्णांक ioaddr = dev->base_addr;
		u16 saved_bank = inw(ioaddr + BANK_SELECT);
		पूर्णांक res;

		SMC_SELECT_BANK(3);
		res = mii_nway_restart(&smc->mii_अगर);
		SMC_SELECT_BANK(saved_bank);

		वापस res;
	पूर्ण अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ethtool_ops = अणु
	.begin = check_अगर_running,
	.get_drvinfo = smc_get_drvinfo,
	.get_link = smc_get_link,
	.nway_reset = smc_nway_reset,
	.get_link_ksettings = smc_get_link_ksettings,
	.set_link_ksettings = smc_set_link_ksettings,
पूर्ण;

अटल पूर्णांक smc_ioctl (काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा smc_निजी *smc = netdev_priv(dev);
	काष्ठा mii_ioctl_data *mii = अगर_mii(rq);
	पूर्णांक rc = 0;
	u16 saved_bank;
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	spin_lock_irqsave(&smc->lock, flags);
	saved_bank = inw(ioaddr + BANK_SELECT);
	SMC_SELECT_BANK(3);
	rc = generic_mii_ioctl(&smc->mii_अगर, mii, cmd, शून्य);
	SMC_SELECT_BANK(saved_bank);
	spin_unlock_irqrestore(&smc->lock, flags);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id smc91c92_ids[] = अणु
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0109, 0x0501),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0140, 0x000a),
	PCMCIA_PFC_DEVICE_PROD_ID123(0, "MEGAHERTZ", "CC/XJEM3288", "DATA/FAX/CELL ETHERNET MODEM", 0xf510db04, 0x04cd2988, 0x46a52d63),
	PCMCIA_PFC_DEVICE_PROD_ID123(0, "MEGAHERTZ", "CC/XJEM3336", "DATA/FAX/CELL ETHERNET MODEM", 0xf510db04, 0x0143b773, 0x46a52d63),
	PCMCIA_PFC_DEVICE_PROD_ID123(0, "MEGAHERTZ", "EM1144T", "PCMCIA MODEM", 0xf510db04, 0x856d66c8, 0xbd6c43ef),
	PCMCIA_PFC_DEVICE_PROD_ID123(0, "MEGAHERTZ", "XJEM1144/CCEM1144", "PCMCIA MODEM", 0xf510db04, 0x52d21e1e, 0xbd6c43ef),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "Gateway 2000", "XJEM3336", 0xdd9989be, 0x662c394c),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "MEGAHERTZ", "XJEM1144/CCEM1144", 0xf510db04, 0x52d21e1e),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "Ositech", "Trumpcard:Jack of Diamonds Modem+Ethernet", 0xc2f80cd, 0x656947b9),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "Ositech", "Trumpcard:Jack of Hearts Modem+Ethernet", 0xc2f80cd, 0xdc9ba5ed),
	PCMCIA_MFC_DEVICE_MANF_CARD(0, 0x016c, 0x0020),
	PCMCIA_DEVICE_MANF_CARD(0x016c, 0x0023),
	PCMCIA_DEVICE_PROD_ID123("BASICS by New Media Corporation", "Ethernet", "SMC91C94", 0x23c78a9d, 0x00b2e941, 0xcef397fb),
	PCMCIA_DEVICE_PROD_ID12("ARGOSY", "Fast Ethernet PCCard", 0x78f308dc, 0xdcea68bc),
	PCMCIA_DEVICE_PROD_ID12("dit Co., Ltd.", "PC Card-10/100BTX", 0xe59365c8, 0x6a2161d1),
	PCMCIA_DEVICE_PROD_ID12("DYNALINK", "L100C", 0x6a26d1cf, 0xc16ce9c5),
	PCMCIA_DEVICE_PROD_ID12("Farallon", "Farallon Enet", 0x58d93fc4, 0x244734e9),
	PCMCIA_DEVICE_PROD_ID12("Megahertz", "CC10BT/2", 0x33234748, 0x3c95b953),
	PCMCIA_DEVICE_PROD_ID12("MELCO/SMC", "LPC-TX", 0xa2cd8e6d, 0x42da662a),
	PCMCIA_DEVICE_PROD_ID12("Ositech", "Trumpcard:Four of Diamonds Ethernet", 0xc2f80cd, 0xb3466314),
	PCMCIA_DEVICE_PROD_ID12("Ositech", "Trumpcard:Seven of Diamonds Ethernet", 0xc2f80cd, 0x194b650a),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "Fast Ethernet PCCard", 0x281f1c5d, 0xdcea68bc),
	PCMCIA_DEVICE_PROD_ID12("Psion", "10Mb Ethernet", 0x4ef00b21, 0x844be9e9),
	PCMCIA_DEVICE_PROD_ID12("SMC", "EtherEZ Ethernet 8020", 0xc4f8b18b, 0x4a0eeb2d),
	/* These conflict with other cards! */
	/* PCMCIA_DEVICE_MANF_CARD(0x0186, 0x0100), */
	/* PCMCIA_DEVICE_MANF_CARD(0x8a01, 0xc1ab), */
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, smc91c92_ids);

अटल काष्ठा pcmcia_driver smc91c92_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "smc91c92_cs",
	.probe		= smc91c92_probe,
	.हटाओ		= smc91c92_detach,
	.id_table       = smc91c92_ids,
	.suspend	= smc91c92_suspend,
	.resume		= smc91c92_resume,
पूर्ण;
module_pcmcia_driver(smc91c92_cs_driver);
