<शैली गुरु>
/*======================================================================
    fmvj18x_cs.c 2.8 2002/03/23

    A fmvj18x (and its compatibles) PCMCIA client driver

    Contributed by Shingo Fujimoto, shingo@flab.fujitsu.co.jp

    TDK LAK-CD021 and CONTEC C-NET(PC)C support added by 
    Nobuhiro Katayama, kata-n@po.iijnet.or.jp

    The PCMCIA client code is based on code written by David Hinds.
    Network code is based on the "FMV-18x driver" by Yutaka TAMIYA
    but is actually largely Donald Becker's AT1700 driver, which
    carries the following attribution:

    Written 1993-94 by Donald Becker.

    Copyright 1993 United States Government as represented by the
    Director, National Security Agency.
    
    This software may be used and distributed according to the terms
    of the GNU General Public License, incorporated herein by reference.
    
    The author may be reached as becker@scyld.com, or C/O
    Scyld Computing Corporation
    410 Severn Ave., Suite 210
    Annapolis MD 21403
   
======================================================================*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"fmvj18x_cs"
#घोषणा DRV_VERSION	"2.9"

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
#समावेश <linux/crc32.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

/*====================================================================*/

/* Module parameters */

MODULE_DESCRIPTION("fmvj18x and compatible PCMCIA ethernet driver");
MODULE_LICENSE("GPL");

#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v; module_param(n, पूर्णांक, 0)

/* SRAM configuration */
/* 0:4KB*2 TX buffer   अन्यथा:8KB*2 TX buffer */
INT_MODULE_PARM(sram_config, 0);


/*====================================================================*/
/*
    PCMCIA event handlers
 */
अटल पूर्णांक fmvj18x_config(काष्ठा pcmcia_device *link);
अटल पूर्णांक fmvj18x_get_hwinfo(काष्ठा pcmcia_device *link, u_अक्षर *node_id);
अटल पूर्णांक fmvj18x_setup_mfc(काष्ठा pcmcia_device *link);
अटल व्योम fmvj18x_release(काष्ठा pcmcia_device *link);
अटल व्योम fmvj18x_detach(काष्ठा pcmcia_device *p_dev);

/*
    LAN controller(MBH86960A) specअगरic routines
 */
अटल पूर्णांक fjn_config(काष्ठा net_device *dev, काष्ठा अगरmap *map);
अटल पूर्णांक fjn_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक fjn_बंद(काष्ठा net_device *dev);
अटल netdev_tx_t fjn_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev);
अटल irqवापस_t fjn_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल व्योम fjn_rx(काष्ठा net_device *dev);
अटल व्योम fjn_reset(काष्ठा net_device *dev);
अटल व्योम set_rx_mode(काष्ठा net_device *dev);
अटल व्योम fjn_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;

/*
    card type
 */
क्रमागत cardtype अणु MBH10302, MBH10304, TDK, CONTEC, LA501, UNGERMANN,
	       XXX10304, NEC, KME
पूर्ण;

/*
    driver specअगरic data काष्ठाure
*/
काष्ठा local_info अणु
	काष्ठा pcmcia_device	*p_dev;
    दीर्घ खोलो_समय;
    uपूर्णांक tx_started:1;
    uपूर्णांक tx_queue;
    u_लघु tx_queue_len;
    क्रमागत cardtype cardtype;
    u_लघु sent;
    u_अक्षर __iomem *base;
पूर्ण;

#घोषणा MC_FILTERBREAK 64

/*====================================================================*/
/* 
    ioport offset from the base address 
 */
#घोषणा TX_STATUS               0 /* transmit status रेजिस्टर */
#घोषणा RX_STATUS               1 /* receive status रेजिस्टर */
#घोषणा TX_INTR                 2 /* transmit पूर्णांकerrupt mask रेजिस्टर */
#घोषणा RX_INTR                 3 /* receive पूर्णांकerrupt mask रेजिस्टर */
#घोषणा TX_MODE                 4 /* transmit mode रेजिस्टर */
#घोषणा RX_MODE                 5 /* receive mode रेजिस्टर */
#घोषणा CONFIG_0                6 /* configuration रेजिस्टर 0 */
#घोषणा CONFIG_1                7 /* configuration रेजिस्टर 1 */

#घोषणा NODE_ID                 8 /* node ID रेजिस्टर            (bank 0) */
#घोषणा MAR_ADR                 8 /* multicast address रेजिस्टरs (bank 1) */

#घोषणा DATAPORT                8 /* buffer mem port रेजिस्टरs   (bank 2) */
#घोषणा TX_START               10 /* transmit start रेजिस्टर */
#घोषणा COL_CTRL               11 /* 16 collision control रेजिस्टर */
#घोषणा BMPR12                 12 /* reserved */
#घोषणा BMPR13                 13 /* reserved */
#घोषणा RX_SKIP                14 /* skip received packet रेजिस्टर */

#घोषणा LAN_CTRL               16 /* LAN card control रेजिस्टर */

#घोषणा MAC_ID               0x1a /* hardware address */
#घोषणा UNGERMANN_MAC_ID     0x18 /* UNGERMANN-BASS hardware address */

/* 
    control bits 
 */
#घोषणा ENA_TMT_OK           0x80
#घोषणा ENA_TMT_REC          0x20
#घोषणा ENA_COL              0x04
#घोषणा ENA_16_COL           0x02
#घोषणा ENA_TBUS_ERR         0x01

#घोषणा ENA_PKT_RDY          0x80
#घोषणा ENA_BUS_ERR          0x40
#घोषणा ENA_LEN_ERR          0x08
#घोषणा ENA_ALG_ERR          0x04
#घोषणा ENA_CRC_ERR          0x02
#घोषणा ENA_OVR_FLO          0x01

/* flags */
#घोषणा F_TMT_RDY            0x80 /* can accept new packet */
#घोषणा F_NET_BSY            0x40 /* carrier is detected */
#घोषणा F_TMT_OK             0x20 /* send packet successfully */
#घोषणा F_SRT_PKT            0x10 /* लघु packet error */
#घोषणा F_COL_ERR            0x04 /* collision error */
#घोषणा F_16_COL             0x02 /* 16 collision error */
#घोषणा F_TBUS_ERR           0x01 /* bus पढ़ो error */

#घोषणा F_PKT_RDY            0x80 /* packet(s) in buffer */
#घोषणा F_BUS_ERR            0x40 /* bus पढ़ो error */
#घोषणा F_LEN_ERR            0x08 /* लघु packet */
#घोषणा F_ALG_ERR            0x04 /* frame error */
#घोषणा F_CRC_ERR            0x02 /* CRC error */
#घोषणा F_OVR_FLO            0x01 /* overflow error */

#घोषणा F_BUF_EMP            0x40 /* receive buffer is empty */

#घोषणा F_SKP_PKT            0x05 /* drop packet in buffer */

/* शेष biपंचांगaps */
#घोषणा D_TX_INTR  ( ENA_TMT_OK )
#घोषणा D_RX_INTR  ( ENA_PKT_RDY | ENA_LEN_ERR \
		   | ENA_ALG_ERR | ENA_CRC_ERR | ENA_OVR_FLO )
#घोषणा TX_STAT_M  ( F_TMT_RDY )
#घोषणा RX_STAT_M  ( F_PKT_RDY | F_LEN_ERR \
                   | F_ALG_ERR | F_CRC_ERR | F_OVR_FLO )

/* commands */
#घोषणा D_TX_MODE            0x06 /* no tests, detect carrier */
#घोषणा ID_MATCHED           0x02 /* (RX_MODE) */
#घोषणा RECV_ALL             0x03 /* (RX_MODE) */
#घोषणा CONFIG0_DFL          0x5a /* 16bit bus, 4K x 2 Tx queues */
#घोषणा CONFIG0_DFL_1        0x5e /* 16bit bus, 8K x 2 Tx queues */
#घोषणा CONFIG0_RST          0xda /* Data Link Controller off (CONFIG_0) */
#घोषणा CONFIG0_RST_1        0xde /* Data Link Controller off (CONFIG_0) */
#घोषणा BANK_0               0xa0 /* bank 0 (CONFIG_1) */
#घोषणा BANK_1               0xa4 /* bank 1 (CONFIG_1) */
#घोषणा BANK_2               0xa8 /* bank 2 (CONFIG_1) */
#घोषणा CHIP_OFF             0x80 /* contrl chip घातer off (CONFIG_1) */
#घोषणा DO_TX                0x80 /* करो transmit packet */
#घोषणा SEND_PKT             0x81 /* send a packet */
#घोषणा AUTO_MODE            0x07 /* Auto skip packet on 16 col detected */
#घोषणा MANU_MODE            0x03 /* Stop and skip packet on 16 col */
#घोषणा TDK_AUTO_MODE        0x47 /* Auto skip packet on 16 col detected */
#घोषणा TDK_MANU_MODE        0x43 /* Stop and skip packet on 16 col */
#घोषणा INTR_OFF             0x0d /* LAN controller ignores पूर्णांकerrupts */
#घोषणा INTR_ON              0x1d /* LAN controller will catch पूर्णांकerrupts */

#घोषणा TX_TIMEOUT		((400*HZ)/1000)

#घोषणा BANK_0U              0x20 /* bank 0 (CONFIG_1) */
#घोषणा BANK_1U              0x24 /* bank 1 (CONFIG_1) */
#घोषणा BANK_2U              0x28 /* bank 2 (CONFIG_1) */

अटल स्थिर काष्ठा net_device_ops fjn_netdev_ops = अणु
	.nकरो_खोलो 		= fjn_खोलो,
	.nकरो_stop		= fjn_बंद,
	.nकरो_start_xmit 	= fjn_start_xmit,
	.nकरो_tx_समयout 	= fjn_tx_समयout,
	.nकरो_set_config 	= fjn_config,
	.nकरो_set_rx_mode	= set_rx_mode,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक fmvj18x_probe(काष्ठा pcmcia_device *link)
अणु
    काष्ठा local_info *lp;
    काष्ठा net_device *dev;

    dev_dbg(&link->dev, "fmvj18x_attach()\n");

    /* Make up a FMVJ18x specअगरic data काष्ठाure */
    dev = alloc_etherdev(माप(काष्ठा local_info));
    अगर (!dev)
	वापस -ENOMEM;
    lp = netdev_priv(dev);
    link->priv = dev;
    lp->p_dev = link;
    lp->base = शून्य;

    /* The io काष्ठाure describes IO port mapping */
    link->resource[0]->end = 32;
    link->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;

    /* General socket configuration */
    link->config_flags |= CONF_ENABLE_IRQ;

    dev->netdev_ops = &fjn_netdev_ops;
    dev->watchकरोg_समयo = TX_TIMEOUT;

    dev->ethtool_ops = &netdev_ethtool_ops;

    वापस fmvj18x_config(link);
पूर्ण /* fmvj18x_attach */

/*====================================================================*/

अटल व्योम fmvj18x_detach(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;

    dev_dbg(&link->dev, "fmvj18x_detach\n");

    unरेजिस्टर_netdev(dev);

    fmvj18x_release(link);

    मुक्त_netdev(dev);
पूर्ण /* fmvj18x_detach */

/*====================================================================*/

अटल पूर्णांक mfc_try_io_port(काष्ठा pcmcia_device *link)
अणु
    पूर्णांक i, ret;
    अटल स्थिर अचिन्हित पूर्णांक serial_base[5] =
	अणु 0x3f8, 0x2f8, 0x3e8, 0x2e8, 0x0 पूर्ण;

    क्रम (i = 0; i < 5; i++) अणु
	link->resource[1]->start = serial_base[i];
	link->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;
	अगर (link->resource[1]->start == 0) अणु
	    link->resource[1]->end = 0;
	    pr_notice("out of resource for serial\n");
	पूर्ण
	ret = pcmcia_request_io(link);
	अगर (ret == 0)
		वापस ret;
    पूर्ण
    वापस ret;
पूर्ण

अटल पूर्णांक ungermann_try_io_port(काष्ठा pcmcia_device *link)
अणु
    पूर्णांक ret;
    अचिन्हित पूर्णांक ioaddr;
    /*
	Ungermann-Bass Access/CARD accepts 0x300,0x320,0x340,0x360
	0x380,0x3c0 only क्रम ioport.
    */
    क्रम (ioaddr = 0x300; ioaddr < 0x3e0; ioaddr += 0x20) अणु
	link->resource[0]->start = ioaddr;
	ret = pcmcia_request_io(link);
	अगर (ret == 0) अणु
	    /* calculate ConfigIndex value */
	    link->config_index =
		((link->resource[0]->start & 0x0f0) >> 3) | 0x22;
	    वापस ret;
	पूर्ण
    पूर्ण
    वापस ret;	/* RequestIO failed */
पूर्ण

अटल पूर्णांक fmvj18x_ioprobe(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	वापस 0; /* strange, but that's what the code did alपढ़ोy beक्रमe... */
पूर्ण

अटल पूर्णांक fmvj18x_config(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    काष्ठा local_info *lp = netdev_priv(dev);
    पूर्णांक i, ret;
    अचिन्हित पूर्णांक ioaddr;
    क्रमागत cardtype cardtype;
    अक्षर *card_name = "unknown";
    u8 *buf;
    माप_प्रकार len;
    u_अक्षर buggybuf[32];

    dev_dbg(&link->dev, "fmvj18x_config\n");

    link->io_lines = 5;

    len = pcmcia_get_tuple(link, CISTPL_FUNCE, &buf);
    kमुक्त(buf);

    अगर (len) अणु
	/* Yes, I have CISTPL_FUNCE. Let's check CISTPL_MANFID */
	ret = pcmcia_loop_config(link, fmvj18x_ioprobe, शून्य);
	अगर (ret != 0)
		जाओ failed;

	चयन (link->manf_id) अणु
	हाल MANFID_TDK:
	    cardtype = TDK;
	    अगर (link->card_id == PRODID_TDK_GN3410 ||
		link->card_id == PRODID_TDK_NP9610 ||
		link->card_id == PRODID_TDK_MN3200) अणु
		/* MultiFunction Card */
		link->config_base = 0x800;
		link->config_index = 0x47;
		link->resource[1]->end = 8;
	    पूर्ण
	    अवरोध;
	हाल MANFID_NEC:
	    cardtype = NEC; /* MultiFunction Card */
	    link->config_base = 0x800;
	    link->config_index = 0x47;
	    link->resource[1]->end = 8;
	    अवरोध;
	हाल MANFID_KME:
	    cardtype = KME; /* MultiFunction Card */
	    link->config_base = 0x800;
	    link->config_index = 0x47;
	    link->resource[1]->end = 8;
	    अवरोध;
	हाल MANFID_CONTEC:
	    cardtype = CONTEC;
	    अवरोध;
	हाल MANFID_FUJITSU:
	    अगर (link->config_base == 0x0fe0)
		cardtype = MBH10302;
	    अन्यथा अगर (link->card_id == PRODID_FUJITSU_MBH10302) 
                /* RATOC REX-5588/9822/4886's PRODID are 0004(=MBH10302),
                   but these are MBH10304 based card. */ 
		cardtype = MBH10304;
	    अन्यथा अगर (link->card_id == PRODID_FUJITSU_MBH10304)
		cardtype = MBH10304;
	    अन्यथा
		cardtype = LA501;
	    अवरोध;
	शेष:
	    cardtype = MBH10304;
	पूर्ण
    पूर्ण अन्यथा अणु
	/* old type card */
	चयन (link->manf_id) अणु
	हाल MANFID_FUJITSU:
	    अगर (link->card_id == PRODID_FUJITSU_MBH10304) अणु
		cardtype = XXX10304;    /* MBH10304 with buggy CIS */
		link->config_index = 0x20;
	    पूर्ण अन्यथा अणु
		cardtype = MBH10302;    /* NextCom NC5310, etc. */
		link->config_index = 1;
	    पूर्ण
	    अवरोध;
	हाल MANFID_UNGERMANN:
	    cardtype = UNGERMANN;
	    अवरोध;
	शेष:
	    cardtype = MBH10302;
	    link->config_index = 1;
	पूर्ण
    पूर्ण

    अगर (link->resource[1]->end != 0) अणु
	ret = mfc_try_io_port(link);
	अगर (ret != 0) जाओ failed;
    पूर्ण अन्यथा अगर (cardtype == UNGERMANN) अणु
	ret = ungermann_try_io_port(link);
	अगर (ret != 0) जाओ failed;
    पूर्ण अन्यथा अणु 
	    ret = pcmcia_request_io(link);
	    अगर (ret)
		    जाओ failed;
    पूर्ण
    ret = pcmcia_request_irq(link, fjn_पूर्णांकerrupt);
    अगर (ret)
	    जाओ failed;
    ret = pcmcia_enable_device(link);
    अगर (ret)
	    जाओ failed;

    dev->irq = link->irq;
    dev->base_addr = link->resource[0]->start;

    अगर (resource_size(link->resource[1]) != 0) अणु
	ret = fmvj18x_setup_mfc(link);
	अगर (ret != 0) जाओ failed;
    पूर्ण

    ioaddr = dev->base_addr;

    /* Reset controller */
    अगर (sram_config == 0) 
	outb(CONFIG0_RST, ioaddr + CONFIG_0);
    अन्यथा
	outb(CONFIG0_RST_1, ioaddr + CONFIG_0);

    /* Power On chip and select bank 0 */
    अगर (cardtype == MBH10302)
	outb(BANK_0, ioaddr + CONFIG_1);
    अन्यथा
	outb(BANK_0U, ioaddr + CONFIG_1);
    
    /* Set hardware address */
    चयन (cardtype) अणु
    हाल MBH10304:
    हाल TDK:
    हाल LA501:
    हाल CONTEC:
    हाल NEC:
    हाल KME:
	अगर (cardtype == MBH10304) अणु
	    card_name = "FMV-J182";

	    len = pcmcia_get_tuple(link, CISTPL_FUNCE, &buf);
	    अगर (len < 11) अणु
		    kमुक्त(buf);
		    जाओ failed;
	    पूर्ण
	    /* Read MACID from CIS */
	    क्रम (i = 0; i < 6; i++)
		    dev->dev_addr[i] = buf[i + 5];
	    kमुक्त(buf);
	पूर्ण अन्यथा अणु
	    अगर (pcmcia_get_mac_from_cis(link, dev))
		जाओ failed;
	    अगर( cardtype == TDK ) अणु
		card_name = "TDK LAK-CD021";
	    पूर्ण अन्यथा अगर( cardtype == LA501 ) अणु
		card_name = "LA501";
	    पूर्ण अन्यथा अगर( cardtype == NEC ) अणु
		card_name = "PK-UG-J001";
	    पूर्ण अन्यथा अगर( cardtype == KME ) अणु
		card_name = "Panasonic";
	    पूर्ण अन्यथा अणु
		card_name = "C-NET(PC)C";
	    पूर्ण
	पूर्ण
	अवरोध;
    हाल UNGERMANN:
	/* Read MACID from रेजिस्टर */
	क्रम (i = 0; i < 6; i++) 
	    dev->dev_addr[i] = inb(ioaddr + UNGERMANN_MAC_ID + i);
	card_name = "Access/CARD";
	अवरोध;
    हाल XXX10304:
	/* Read MACID from Buggy CIS */
	अगर (fmvj18x_get_hwinfo(link, buggybuf) == -1) अणु
	    pr_notice("unable to read hardware net address\n");
	    जाओ failed;
	पूर्ण
	क्रम (i = 0 ; i < 6; i++) अणु
	    dev->dev_addr[i] = buggybuf[i];
	पूर्ण
	card_name = "FMV-J182";
	अवरोध;
    हाल MBH10302:
    शेष:
	/* Read MACID from रेजिस्टर */
	क्रम (i = 0; i < 6; i++) 
	    dev->dev_addr[i] = inb(ioaddr + MAC_ID + i);
	card_name = "FMV-J181";
	अवरोध;
    पूर्ण

    lp->cardtype = cardtype;
    SET_NETDEV_DEV(dev, &link->dev);

    अगर (रेजिस्टर_netdev(dev) != 0) अणु
	pr_notice("register_netdev() failed\n");
	जाओ failed;
    पूर्ण

    /* prपूर्णांक current configuration */
    netdev_info(dev, "%s, sram %s, port %#3lx, irq %d, hw_addr %pM\n",
		card_name, sram_config == 0 ? "4K TX*2" : "8K TX*2",
		dev->base_addr, dev->irq, dev->dev_addr);

    वापस 0;
    
failed:
    fmvj18x_release(link);
    वापस -ENODEV;
पूर्ण /* fmvj18x_config */
/*====================================================================*/

अटल पूर्णांक fmvj18x_get_hwinfo(काष्ठा pcmcia_device *link, u_अक्षर *node_id)
अणु
    u_अक्षर __iomem *base;
    पूर्णांक i, j;

    /* Allocate a small memory winकरोw */
    link->resource[2]->flags |= WIN_DATA_WIDTH_8|WIN_MEMORY_TYPE_AM|WIN_ENABLE;
    link->resource[2]->start = 0; link->resource[2]->end = 0;
    i = pcmcia_request_winकरोw(link, link->resource[2], 0);
    अगर (i != 0)
	वापस -1;

    base = ioremap(link->resource[2]->start, resource_size(link->resource[2]));
    अगर (!base) अणु
	pcmcia_release_winकरोw(link, link->resource[2]);
	वापस -1;
    पूर्ण

    pcmcia_map_mem_page(link, link->resource[2], 0);

    /*
     *  MBH10304 CISTPL_FUNCE_LAN_NODE_ID क्रमmat
     *  22 0d xx xx xx 04 06 yy yy yy yy yy yy ff
     *  'xx' is garbage.
     *  'yy' is MAC address.
    */ 
    क्रम (i = 0; i < 0x200; i++) अणु
	अगर (पढ़ोb(base+i*2) == 0x22) अणु	
		अगर (पढ़ोb(base+(i-1)*2) == 0xff &&
		    पढ़ोb(base+(i+5)*2) == 0x04 &&
		    पढ़ोb(base+(i+6)*2) == 0x06 &&
		    पढ़ोb(base+(i+13)*2) == 0xff)
			अवरोध;
	पूर्ण
    पूर्ण

    अगर (i != 0x200) अणु
	क्रम (j = 0 ; j < 6; j++,i++) अणु
	    node_id[j] = पढ़ोb(base+(i+7)*2);
	पूर्ण
    पूर्ण

    iounmap(base);
    j = pcmcia_release_winकरोw(link, link->resource[2]);
    वापस (i != 0x200) ? 0 : -1;

पूर्ण /* fmvj18x_get_hwinfo */
/*====================================================================*/

अटल पूर्णांक fmvj18x_setup_mfc(काष्ठा pcmcia_device *link)
अणु
    पूर्णांक i;
    काष्ठा net_device *dev = link->priv;
    अचिन्हित पूर्णांक ioaddr;
    काष्ठा local_info *lp = netdev_priv(dev);

    /* Allocate a small memory winकरोw */
    link->resource[3]->flags = WIN_DATA_WIDTH_8|WIN_MEMORY_TYPE_AM|WIN_ENABLE;
    link->resource[3]->start = link->resource[3]->end = 0;
    i = pcmcia_request_winकरोw(link, link->resource[3], 0);
    अगर (i != 0)
	वापस -1;

    lp->base = ioremap(link->resource[3]->start,
		       resource_size(link->resource[3]));
    अगर (lp->base == शून्य) अणु
	netdev_notice(dev, "ioremap failed\n");
	वापस -1;
    पूर्ण

    i = pcmcia_map_mem_page(link, link->resource[3], 0);
    अगर (i != 0) अणु
	iounmap(lp->base);
	lp->base = शून्य;
	वापस -1;
    पूर्ण
    
    ioaddr = dev->base_addr;
    ग_लिखोb(0x47, lp->base+0x800);	/* Config Option Register of LAN */
    ग_लिखोb(0x0,  lp->base+0x802);	/* Config and Status Register */

    ग_लिखोb(ioaddr & 0xff, lp->base+0x80a);	  /* I/O Base(Low) of LAN */
    ग_लिखोb((ioaddr >> 8) & 0xff, lp->base+0x80c); /* I/O Base(High) of LAN */
   
    ग_लिखोb(0x45, lp->base+0x820);	/* Config Option Register of Modem */
    ग_लिखोb(0x8,  lp->base+0x822);	/* Config and Status Register */

    वापस 0;

पूर्ण
/*====================================================================*/

अटल व्योम fmvj18x_release(काष्ठा pcmcia_device *link)
अणु

    काष्ठा net_device *dev = link->priv;
    काष्ठा local_info *lp = netdev_priv(dev);
    u_अक्षर __iomem *पंचांगp;

    dev_dbg(&link->dev, "fmvj18x_release\n");

    अगर (lp->base != शून्य) अणु
	पंचांगp = lp->base;
	lp->base = शून्य;    /* set शून्य beक्रमe iounmap */
	iounmap(पंचांगp);
    पूर्ण

    pcmcia_disable_device(link);

पूर्ण

अटल पूर्णांक fmvj18x_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो)
		netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक fmvj18x_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो) अणु
		fjn_reset(dev);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण

/*====================================================================*/

अटल स्थिर काष्ठा pcmcia_device_id fmvj18x_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x0004, 0x0004),
	PCMCIA_DEVICE_PROD_ID12("EAGLE Technology", "NE200 ETHERNET LAN MBH10302 04", 0x528c88c4, 0x74f91e59),
	PCMCIA_DEVICE_PROD_ID12("Eiger Labs,Inc", "EPX-10BT PC Card Ethernet 10BT", 0x53af556e, 0x877f9922),
	PCMCIA_DEVICE_PROD_ID12("Eiger labs,Inc.", "EPX-10BT PC Card Ethernet 10BT", 0xf47e6c66, 0x877f9922),
	PCMCIA_DEVICE_PROD_ID12("FUJITSU", "LAN Card(FMV-J182)", 0x6ee5a3d8, 0x5baf31db),
	PCMCIA_DEVICE_PROD_ID12("FUJITSU", "MBH10308", 0x6ee5a3d8, 0x3f04875e),
	PCMCIA_DEVICE_PROD_ID12("FUJITSU TOWA", "LA501", 0xb8451188, 0x12939ba2),
	PCMCIA_DEVICE_PROD_ID12("HITACHI", "HT-4840-11", 0xf4f43949, 0x773910f4),
	PCMCIA_DEVICE_PROD_ID12("NextComK.K.", "NC5310B Ver1.0       ", 0x8cef4d3a, 0x075fc7b6),
	PCMCIA_DEVICE_PROD_ID12("NextComK.K.", "NC5310 Ver1.0        ", 0x8cef4d3a, 0xbccf43e6),
	PCMCIA_DEVICE_PROD_ID12("RATOC System Inc.", "10BASE_T CARD R280", 0x85c10e17, 0xd9413666),
	PCMCIA_DEVICE_PROD_ID12("TDK", "LAC-CD02x", 0x1eae9475, 0x8fa0ee70),
	PCMCIA_DEVICE_PROD_ID12("TDK", "LAC-CF010", 0x1eae9475, 0x7683bc9a),
	PCMCIA_DEVICE_PROD_ID1("CONTEC Co.,Ltd.", 0x58d8fee2),
	PCMCIA_DEVICE_PROD_ID1("PCMCIA LAN MBH10304  ES", 0x2599f454),
	PCMCIA_DEVICE_PROD_ID1("PCMCIA MBH10302", 0x8f4005da),
	PCMCIA_DEVICE_PROD_ID1("UBKK,V2.0", 0x90888080),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "TDK", "GlobalNetworker 3410/3412", 0x1eae9475, 0xd9a93bed),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "NEC", "PK-UG-J001" ,0x18df0ba0 ,0x831b1064),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0105, 0x0d0a),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0105, 0x0e0a),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0032, 0x0e01),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0032, 0x0a05),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0032, 0x0b05),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0032, 0x1101),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, fmvj18x_ids);

अटल काष्ठा pcmcia_driver fmvj18x_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "fmvj18x_cs",
	.probe		= fmvj18x_probe,
	.हटाओ		= fmvj18x_detach,
	.id_table       = fmvj18x_ids,
	.suspend	= fmvj18x_suspend,
	.resume		= fmvj18x_resume,
पूर्ण;
module_pcmcia_driver(fmvj18x_cs_driver);

/*====================================================================*/

अटल irqवापस_t fjn_पूर्णांकerrupt(पूर्णांक dummy, व्योम *dev_id)
अणु
    काष्ठा net_device *dev = dev_id;
    काष्ठा local_info *lp = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr;
    अचिन्हित लघु tx_stat, rx_stat;

    ioaddr = dev->base_addr;

    /* aव्योम multiple पूर्णांकerrupts */
    outw(0x0000, ioaddr + TX_INTR);

    /* रुको क्रम a जबतक */
    udelay(1);

    /* get status */
    tx_stat = inb(ioaddr + TX_STATUS);
    rx_stat = inb(ioaddr + RX_STATUS);

    /* clear status */
    outb(tx_stat, ioaddr + TX_STATUS);
    outb(rx_stat, ioaddr + RX_STATUS);
    
    pr_debug("%s: interrupt, rx_status %02x.\n", dev->name, rx_stat);
    pr_debug("               tx_status %02x.\n", tx_stat);
    
    अगर (rx_stat || (inb(ioaddr + RX_MODE) & F_BUF_EMP) == 0) अणु
	/* there is packet(s) in rx buffer */
	fjn_rx(dev);
    पूर्ण
    अगर (tx_stat & F_TMT_RDY) अणु
	dev->stats.tx_packets += lp->sent ;
        lp->sent = 0 ;
	अगर (lp->tx_queue) अणु
	    outb(DO_TX | lp->tx_queue, ioaddr + TX_START);
	    lp->sent = lp->tx_queue ;
	    lp->tx_queue = 0;
	    lp->tx_queue_len = 0;
	    netअगर_trans_update(dev);
	पूर्ण अन्यथा अणु
	    lp->tx_started = 0;
	पूर्ण
	netअगर_wake_queue(dev);
    पूर्ण
    pr_debug("%s: exiting interrupt,\n", dev->name);
    pr_debug("    tx_status %02x, rx_status %02x.\n", tx_stat, rx_stat);

    outb(D_TX_INTR, ioaddr + TX_INTR);
    outb(D_RX_INTR, ioaddr + RX_INTR);

    अगर (lp->base != शून्य) अणु
	/* Ack पूर्णांकerrupt क्रम multअगरunction card */
	ग_लिखोb(0x01, lp->base+0x802);
	ग_लिखोb(0x09, lp->base+0x822);
    पूर्ण

    वापस IRQ_HANDLED;

पूर्ण /* fjn_पूर्णांकerrupt */

/*====================================================================*/

अटल व्योम fjn_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
    काष्ठा local_info *lp = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;

    netdev_notice(dev, "transmit timed out with status %04x, %s?\n",
		  htons(inw(ioaddr + TX_STATUS)),
		  inb(ioaddr + TX_STATUS) & F_TMT_RDY
		  ? "IRQ conflict" : "network cable problem");
    netdev_notice(dev, "timeout registers: %04x %04x %04x "
		  "%04x %04x %04x %04x %04x.\n",
		  htons(inw(ioaddr + 0)), htons(inw(ioaddr + 2)),
		  htons(inw(ioaddr + 4)), htons(inw(ioaddr + 6)),
		  htons(inw(ioaddr + 8)), htons(inw(ioaddr + 10)),
		  htons(inw(ioaddr + 12)), htons(inw(ioaddr + 14)));
    dev->stats.tx_errors++;
    /* ToDo: We should try to restart the adaptor... */
    local_irq_disable();
    fjn_reset(dev);

    lp->tx_started = 0;
    lp->tx_queue = 0;
    lp->tx_queue_len = 0;
    lp->sent = 0;
    lp->खोलो_समय = jअगरfies;
    local_irq_enable();
    netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t fjn_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
    काष्ठा local_info *lp = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    लघु length = skb->len;
    
    अगर (length < ETH_ZLEN)
    अणु
    	अगर (skb_padto(skb, ETH_ZLEN))
    		वापस NETDEV_TX_OK;
    	length = ETH_ZLEN;
    पूर्ण

    netअगर_stop_queue(dev);

    अणु
	अचिन्हित अक्षर *buf = skb->data;

	अगर (length > ETH_FRAME_LEN) अणु
	    netdev_notice(dev, "Attempting to send a large packet (%d bytes)\n",
			  length);
	    वापस NETDEV_TX_BUSY;
	पूर्ण

	netdev_dbg(dev, "Transmitting a packet of length %lu\n",
		   (अचिन्हित दीर्घ)skb->len);
	dev->stats.tx_bytes += skb->len;

	/* Disable both पूर्णांकerrupts. */
	outw(0x0000, ioaddr + TX_INTR);

	/* रुको क्रम a जबतक */
	udelay(1);

	outw(length, ioaddr + DATAPORT);
	outsw(ioaddr + DATAPORT, buf, (length + 1) >> 1);

	lp->tx_queue++;
	lp->tx_queue_len += ((length+3) & ~1);

	अगर (lp->tx_started == 0) अणु
	    /* If the Tx is idle, always trigger a transmit. */
	    outb(DO_TX | lp->tx_queue, ioaddr + TX_START);
	    lp->sent = lp->tx_queue ;
	    lp->tx_queue = 0;
	    lp->tx_queue_len = 0;
	    lp->tx_started = 1;
	    netअगर_start_queue(dev);
	पूर्ण अन्यथा अणु
	    अगर( sram_config == 0 ) अणु
		अगर (lp->tx_queue_len < (4096 - (ETH_FRAME_LEN +2)) )
		    /* Yes, there is room क्रम one more packet. */
		    netअगर_start_queue(dev);
	    पूर्ण अन्यथा अणु
		अगर (lp->tx_queue_len < (8192 - (ETH_FRAME_LEN +2)) && 
						lp->tx_queue < 127 )
		    /* Yes, there is room क्रम one more packet. */
		    netअगर_start_queue(dev);
	    पूर्ण
	पूर्ण

	/* Re-enable पूर्णांकerrupts */
	outb(D_TX_INTR, ioaddr + TX_INTR);
	outb(D_RX_INTR, ioaddr + RX_INTR);
    पूर्ण
    dev_kमुक्त_skb (skb);

    वापस NETDEV_TX_OK;
पूर्ण /* fjn_start_xmit */

/*====================================================================*/

अटल व्योम fjn_reset(काष्ठा net_device *dev)
अणु
    काष्ठा local_info *lp = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    पूर्णांक i;

    netdev_dbg(dev, "fjn_reset() called\n");

    /* Reset controller */
    अगर( sram_config == 0 ) 
	outb(CONFIG0_RST, ioaddr + CONFIG_0);
    अन्यथा
	outb(CONFIG0_RST_1, ioaddr + CONFIG_0);

    /* Power On chip and select bank 0 */
    अगर (lp->cardtype == MBH10302)
	outb(BANK_0, ioaddr + CONFIG_1);
    अन्यथा
	outb(BANK_0U, ioaddr + CONFIG_1);

    /* Set Tx modes */
    outb(D_TX_MODE, ioaddr + TX_MODE);
    /* set Rx modes */
    outb(ID_MATCHED, ioaddr + RX_MODE);

    /* Set hardware address */
    क्रम (i = 0; i < 6; i++) 
        outb(dev->dev_addr[i], ioaddr + NODE_ID + i);

    /* (re)initialize the multicast table */
    set_rx_mode(dev);

    /* Switch to bank 2 (runसमय mode) */
    अगर (lp->cardtype == MBH10302)
	outb(BANK_2, ioaddr + CONFIG_1);
    अन्यथा
	outb(BANK_2U, ioaddr + CONFIG_1);

    /* set 16col ctrl bits */
    अगर( lp->cardtype == TDK || lp->cardtype == CONTEC) 
        outb(TDK_AUTO_MODE, ioaddr + COL_CTRL);
    अन्यथा
        outb(AUTO_MODE, ioaddr + COL_CTRL);

    /* clear Reserved Regs */
    outb(0x00, ioaddr + BMPR12);
    outb(0x00, ioaddr + BMPR13);

    /* reset Skip packet reg. */
    outb(0x01, ioaddr + RX_SKIP);

    /* Enable Tx and Rx */
    अगर( sram_config == 0 )
	outb(CONFIG0_DFL, ioaddr + CONFIG_0);
    अन्यथा
	outb(CONFIG0_DFL_1, ioaddr + CONFIG_0);

    /* Init receive poपूर्णांकer ? */
    inw(ioaddr + DATAPORT);
    inw(ioaddr + DATAPORT);

    /* Clear all status */
    outb(0xff, ioaddr + TX_STATUS);
    outb(0xff, ioaddr + RX_STATUS);

    अगर (lp->cardtype == MBH10302)
	outb(INTR_OFF, ioaddr + LAN_CTRL);

    /* Turn on Rx पूर्णांकerrupts */
    outb(D_TX_INTR, ioaddr + TX_INTR);
    outb(D_RX_INTR, ioaddr + RX_INTR);

    /* Turn on पूर्णांकerrupts from LAN card controller */
    अगर (lp->cardtype == MBH10302)
	outb(INTR_ON, ioaddr + LAN_CTRL);
पूर्ण /* fjn_reset */

/*====================================================================*/

अटल व्योम fjn_rx(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    पूर्णांक boguscount = 10;	/* 5 -> 10: by agy 19940922 */

    pr_debug("%s: in rx_packet(), rx_status %02x.\n",
	  dev->name, inb(ioaddr + RX_STATUS));

    जबतक ((inb(ioaddr + RX_MODE) & F_BUF_EMP) == 0) अणु
	u_लघु status = inw(ioaddr + DATAPORT);

	netdev_dbg(dev, "Rxing packet mode %02x status %04x.\n",
		   inb(ioaddr + RX_MODE), status);
#अगर_अघोषित final_version
	अगर (status == 0) अणु
	    outb(F_SKP_PKT, ioaddr + RX_SKIP);
	    अवरोध;
	पूर्ण
#पूर्ण_अगर
	अगर ((status & 0xF0) != 0x20) अणु	/* There was an error. */
	    dev->stats.rx_errors++;
	    अगर (status & F_LEN_ERR) dev->stats.rx_length_errors++;
	    अगर (status & F_ALG_ERR) dev->stats.rx_frame_errors++;
	    अगर (status & F_CRC_ERR) dev->stats.rx_crc_errors++;
	    अगर (status & F_OVR_FLO) dev->stats.rx_over_errors++;
	पूर्ण अन्यथा अणु
	    u_लघु pkt_len = inw(ioaddr + DATAPORT);
	    /* Malloc up new buffer. */
	    काष्ठा sk_buff *skb;

	    अगर (pkt_len > 1550) अणु
		netdev_notice(dev, "The FMV-18x claimed a very large packet, size %d\n",
			      pkt_len);
		outb(F_SKP_PKT, ioaddr + RX_SKIP);
		dev->stats.rx_errors++;
		अवरोध;
	    पूर्ण
	    skb = netdev_alloc_skb(dev, pkt_len + 2);
	    अगर (skb == शून्य) अणु
		outb(F_SKP_PKT, ioaddr + RX_SKIP);
		dev->stats.rx_dropped++;
		अवरोध;
	    पूर्ण

	    skb_reserve(skb, 2);
	    insw(ioaddr + DATAPORT, skb_put(skb, pkt_len),
		 (pkt_len + 1) >> 1);
	    skb->protocol = eth_type_trans(skb, dev);

	    अणु
		पूर्णांक i;
		pr_debug("%s: Rxed packet of length %d: ",
			dev->name, pkt_len);
		क्रम (i = 0; i < 14; i++)
			pr_debug(" %02x", skb->data[i]);
		pr_debug(".\n");
	    पूर्ण

	    netअगर_rx(skb);
	    dev->stats.rx_packets++;
	    dev->stats.rx_bytes += pkt_len;
	पूर्ण
	अगर (--boguscount <= 0)
	    अवरोध;
    पूर्ण

    /* If any worth-जबतक packets have been received, dev_rपूर्णांक()
	   has करोne a netअगर_wake_queue() क्रम us and will work on them
	   when we get to the bottom-half routine. */
/*
    अगर (lp->cardtype != TDK) अणु
	पूर्णांक i;
	क्रम (i = 0; i < 20; i++) अणु
	    अगर ((inb(ioaddr + RX_MODE) & F_BUF_EMP) == F_BUF_EMP)
		अवरोध;
	    (व्योम)inw(ioaddr + DATAPORT);  /+ dummy status पढ़ो +/
	    outb(F_SKP_PKT, ioaddr + RX_SKIP);
	पूर्ण

	अगर (i > 0)
	    pr_debug("%s: Exint Rx packet with mode %02x after "
		  "%d ticks.\n", dev->name, inb(ioaddr + RX_MODE), i);
    पूर्ण
*/
पूर्ण /* fjn_rx */

/*====================================================================*/

अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	snम_लिखो(info->bus_info, माप(info->bus_info),
		"PCMCIA 0x%lx", dev->base_addr);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
पूर्ण;

अटल पूर्णांक fjn_config(काष्ठा net_device *dev, काष्ठा अगरmap *map)अणु
    वापस 0;
पूर्ण

अटल पूर्णांक fjn_खोलो(काष्ठा net_device *dev)
अणु
    काष्ठा local_info *lp = netdev_priv(dev);
    काष्ठा pcmcia_device *link = lp->p_dev;

    pr_debug("fjn_open('%s').\n", dev->name);

    अगर (!pcmcia_dev_present(link))
	वापस -ENODEV;
    
    link->खोलो++;
    
    fjn_reset(dev);
    
    lp->tx_started = 0;
    lp->tx_queue = 0;
    lp->tx_queue_len = 0;
    lp->खोलो_समय = jअगरfies;
    netअगर_start_queue(dev);
    
    वापस 0;
पूर्ण /* fjn_खोलो */

/*====================================================================*/

अटल पूर्णांक fjn_बंद(काष्ठा net_device *dev)
अणु
    काष्ठा local_info *lp = netdev_priv(dev);
    काष्ठा pcmcia_device *link = lp->p_dev;
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;

    pr_debug("fjn_close('%s').\n", dev->name);

    lp->खोलो_समय = 0;
    netअगर_stop_queue(dev);

    /* Set configuration रेजिस्टर 0 to disable Tx and Rx. */
    अगर( sram_config == 0 ) 
	outb(CONFIG0_RST ,ioaddr + CONFIG_0);
    अन्यथा
	outb(CONFIG0_RST_1 ,ioaddr + CONFIG_0);

    /* Update the statistics -- ToDo. */

    /* Power-करोwn the chip.  Green, green, green! */
    outb(CHIP_OFF ,ioaddr + CONFIG_1);

    /* Set the ethernet adaptor disable IRQ */
    अगर (lp->cardtype == MBH10302)
	outb(INTR_OFF, ioaddr + LAN_CTRL);

    link->खोलो--;

    वापस 0;
पूर्ण /* fjn_बंद */

/*====================================================================*/

/*
  Set the multicast/promiscuous mode क्रम this adaptor.
*/

अटल व्योम set_rx_mode(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    u_अक्षर mc_filter[8];		 /* Multicast hash filter */
    u_दीर्घ flags;
    पूर्णांक i;
    
    पूर्णांक saved_bank;
    पूर्णांक saved_config_0 = inb(ioaddr + CONFIG_0);
     
    local_irq_save(flags); 

    /* Disable Tx and Rx */
    अगर (sram_config == 0) 
	outb(CONFIG0_RST, ioaddr + CONFIG_0);
    अन्यथा
	outb(CONFIG0_RST_1, ioaddr + CONFIG_0);

    अगर (dev->flags & IFF_PROMISC) अणु
	स_रखो(mc_filter, 0xff, माप(mc_filter));
	outb(3, ioaddr + RX_MODE);	/* Enable promiscuous mode */
    पूर्ण अन्यथा अगर (netdev_mc_count(dev) > MC_FILTERBREAK ||
	       (dev->flags & IFF_ALLMULTI)) अणु
	/* Too many to filter perfectly -- accept all multicasts. */
	स_रखो(mc_filter, 0xff, माप(mc_filter));
	outb(2, ioaddr + RX_MODE);	/* Use normal mode. */
    पूर्ण अन्यथा अगर (netdev_mc_empty(dev)) अणु
	स_रखो(mc_filter, 0x00, माप(mc_filter));
	outb(1, ioaddr + RX_MODE);	/* Ignore almost all multicasts. */
    पूर्ण अन्यथा अणु
	काष्ठा netdev_hw_addr *ha;

	स_रखो(mc_filter, 0, माप(mc_filter));
	netdev_क्रम_each_mc_addr(ha, dev) अणु
	    अचिन्हित पूर्णांक bit = ether_crc_le(ETH_ALEN, ha->addr) >> 26;
	    mc_filter[bit >> 3] |= (1 << (bit & 7));
	पूर्ण
	outb(2, ioaddr + RX_MODE);	/* Use normal mode. */
    पूर्ण

    /* Switch to bank 1 and set the multicast table. */
    saved_bank = inb(ioaddr + CONFIG_1);
    outb(0xe4, ioaddr + CONFIG_1);

    क्रम (i = 0; i < 8; i++)
	outb(mc_filter[i], ioaddr + MAR_ADR + i);
    outb(saved_bank, ioaddr + CONFIG_1);

    outb(saved_config_0, ioaddr + CONFIG_0);

    local_irq_restore(flags);
पूर्ण
