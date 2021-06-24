<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001,2002,2003,2004 Broadcom Corporation
 * Copyright (c) 2006, 2007  Maciej W. Rozycki
 *
 * This driver is deचिन्हित क्रम the Broadcom SiByte SOC built-in
 * Ethernet controllers. Written by Mitch Lichtenberg at Broadcom Corp.
 *
 * Updated to the driver model and the PHY असलtraction layer
 * by Maciej W. Rozycki.
 */

#समावेश <linux/bug.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prefetch.h>

#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>	/* Processor type क्रम cache alignment. */

/* Operational parameters that usually are not changed. */

#घोषणा CONFIG_SBMAC_COALESCE

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (2*HZ)


MODULE_AUTHOR("Mitch Lichtenberg (Broadcom Corp.)");
MODULE_DESCRIPTION("Broadcom SiByte SOC GB Ethernet driver");

/* A few user-configurable values which may be modअगरied when a driver
   module is loaded. */

/* 1 normal messages, 0 quiet .. 7 verbose. */
अटल पूर्णांक debug = 1;
module_param(debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "Debug messages");

#अगर_घोषित CONFIG_SBMAC_COALESCE
अटल पूर्णांक पूर्णांक_pktcnt_tx = 255;
module_param(पूर्णांक_pktcnt_tx, पूर्णांक, 0444);
MODULE_PARM_DESC(पूर्णांक_pktcnt_tx, "TX packet count");

अटल पूर्णांक पूर्णांक_समयout_tx = 255;
module_param(पूर्णांक_समयout_tx, पूर्णांक, 0444);
MODULE_PARM_DESC(पूर्णांक_समयout_tx, "TX timeout value");

अटल पूर्णांक पूर्णांक_pktcnt_rx = 64;
module_param(पूर्णांक_pktcnt_rx, पूर्णांक, 0444);
MODULE_PARM_DESC(पूर्णांक_pktcnt_rx, "RX packet count");

अटल पूर्णांक पूर्णांक_समयout_rx = 64;
module_param(पूर्णांक_समयout_rx, पूर्णांक, 0444);
MODULE_PARM_DESC(पूर्णांक_समयout_rx, "RX timeout value");
#पूर्ण_अगर

#समावेश <यंत्र/sibyte/board.h>
#समावेश <यंत्र/sibyte/sb1250.h>
#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#समावेश <यंत्र/sibyte/bcm1480_पूर्णांक.h>
#घोषणा R_MAC_DMA_OODPKTLOST_RX	R_MAC_DMA_OODPKTLOST
#या_अगर defined(CONFIG_SIBYTE_SB1250) || defined(CONFIG_SIBYTE_BCM112X)
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_पूर्णांक.h>
#अन्यथा
#त्रुटि invalid SiByte MAC configuration
#पूर्ण_अगर
#समावेश <यंत्र/sibyte/sb1250_scd.h>
#समावेश <यंत्र/sibyte/sb1250_mac.h>
#समावेश <यंत्र/sibyte/sb1250_dma.h>

#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
#घोषणा UNIT_INT(n)		(K_BCM1480_INT_MAC_0 + ((n) * 2))
#या_अगर defined(CONFIG_SIBYTE_SB1250) || defined(CONFIG_SIBYTE_BCM112X)
#घोषणा UNIT_INT(n)		(K_INT_MAC_0 + (n))
#अन्यथा
#त्रुटि invalid SiByte MAC configuration
#पूर्ण_अगर

#अगर_घोषित K_INT_PHY
#घोषणा SBMAC_PHY_INT			K_INT_PHY
#अन्यथा
#घोषणा SBMAC_PHY_INT			PHY_POLL
#पूर्ण_अगर

/**********************************************************************
 *  Simple types
 ********************************************************************* */

क्रमागत sbmac_speed अणु
	sbmac_speed_none = 0,
	sbmac_speed_10 = SPEED_10,
	sbmac_speed_100 = SPEED_100,
	sbmac_speed_1000 = SPEED_1000,
पूर्ण;

क्रमागत sbmac_duplex अणु
	sbmac_duplex_none = -1,
	sbmac_duplex_half = DUPLEX_HALF,
	sbmac_duplex_full = DUPLEX_FULL,
पूर्ण;

क्रमागत sbmac_fc अणु
	sbmac_fc_none,
	sbmac_fc_disabled,
	sbmac_fc_frame,
	sbmac_fc_collision,
	sbmac_fc_carrier,
पूर्ण;

क्रमागत sbmac_state अणु
	sbmac_state_uninit,
	sbmac_state_off,
	sbmac_state_on,
	sbmac_state_broken,
पूर्ण;


/**********************************************************************
 *  Macros
 ********************************************************************* */


#घोषणा SBDMA_NEXTBUF(d,f) ((((d)->f+1) == (d)->sbdma_dscrtable_end) ? \
			  (d)->sbdma_dscrtable : (d)->f+1)


#घोषणा NUMCACHEBLKS(x) DIV_ROUND_UP(x, SMP_CACHE_BYTES)

#घोषणा SBMAC_MAX_TXDESCR	256
#घोषणा SBMAC_MAX_RXDESCR	256

#घोषणा ENET_PACKET_SIZE	1518
/*#घोषणा ENET_PACKET_SIZE	9216 */

/**********************************************************************
 *  DMA Descriptor काष्ठाure
 ********************************************************************* */

काष्ठा sbdmadscr अणु
	uपूर्णांक64_t  dscr_a;
	uपूर्णांक64_t  dscr_b;
पूर्ण;

/**********************************************************************
 *  DMA Controller काष्ठाure
 ********************************************************************* */

काष्ठा sbmacdma अणु

	/*
	 * This stuff is used to identअगरy the channel and the रेजिस्टरs
	 * associated with it.
	 */
	काष्ठा sbmac_softc	*sbdma_eth;	/* back poपूर्णांकer to associated
						   MAC */
	पूर्णांक			sbdma_channel;	/* channel number */
	पूर्णांक			sbdma_txdir;	/* direction (1=transmit) */
	पूर्णांक			sbdma_maxdescr;	/* total # of descriptors
						   in ring */
#अगर_घोषित CONFIG_SBMAC_COALESCE
	पूर्णांक			sbdma_पूर्णांक_pktcnt;
						/* # descriptors rx/tx
						   beक्रमe पूर्णांकerrupt */
	पूर्णांक			sbdma_पूर्णांक_समयout;
						/* # usec rx/tx पूर्णांकerrupt */
#पूर्ण_अगर
	व्योम __iomem		*sbdma_config0;	/* DMA config रेजिस्टर 0 */
	व्योम __iomem		*sbdma_config1;	/* DMA config रेजिस्टर 1 */
	व्योम __iomem		*sbdma_dscrbase;
						/* descriptor base address */
	व्योम __iomem		*sbdma_dscrcnt;	/* descriptor count रेजिस्टर */
	व्योम __iomem		*sbdma_curdscr;	/* current descriptor
						   address */
	व्योम __iomem		*sbdma_oodpktlost;
						/* pkt drop (rx only) */

	/*
	 * This stuff is क्रम मुख्यtenance of the ring
	 */
	व्योम			*sbdma_dscrtable_unaligned;
	काष्ठा sbdmadscr	*sbdma_dscrtable;
						/* base of descriptor table */
	काष्ठा sbdmadscr	*sbdma_dscrtable_end;
						/* end of descriptor table */
	काष्ठा sk_buff		**sbdma_ctxtable;
						/* context table, one
						   per descr */
	dma_addr_t		sbdma_dscrtable_phys;
						/* and also the phys addr */
	काष्ठा sbdmadscr	*sbdma_addptr;	/* next dscr क्रम sw to add */
	काष्ठा sbdmadscr	*sbdma_remptr;	/* next dscr क्रम sw
						   to हटाओ */
पूर्ण;


/**********************************************************************
 *  Ethernet softc काष्ठाure
 ********************************************************************* */

काष्ठा sbmac_softc अणु

	/*
	 * Linux-specअगरic things
	 */
	काष्ठा net_device	*sbm_dev;	/* poपूर्णांकer to linux device */
	काष्ठा napi_काष्ठा	napi;
	काष्ठा phy_device	*phy_dev;	/* the associated PHY device */
	काष्ठा mii_bus		*mii_bus;	/* the MII bus */
	spinlock_t		sbm_lock;	/* spin lock */
	पूर्णांक			sbm_devflags;	/* current device flags */

	/*
	 * Controller-specअगरic things
	 */
	व्योम __iomem		*sbm_base;	/* MAC's base address */
	क्रमागत sbmac_state	sbm_state;	/* current state */

	व्योम __iomem		*sbm_macenable;	/* MAC Enable Register */
	व्योम __iomem		*sbm_maccfg;	/* MAC Config Register */
	व्योम __iomem		*sbm_fअगरocfg;	/* FIFO Config Register */
	व्योम __iomem		*sbm_framecfg;	/* Frame Config Register */
	व्योम __iomem		*sbm_rxfilter;	/* Receive Filter Register */
	व्योम __iomem		*sbm_isr;	/* Interrupt Status Register */
	व्योम __iomem		*sbm_imr;	/* Interrupt Mask Register */
	व्योम __iomem		*sbm_mdio;	/* MDIO Register */

	क्रमागत sbmac_speed	sbm_speed;	/* current speed */
	क्रमागत sbmac_duplex	sbm_duplex;	/* current duplex */
	क्रमागत sbmac_fc		sbm_fc;		/* cur. flow control setting */
	पूर्णांक			sbm_छोड़ो;	/* current छोड़ो setting */
	पूर्णांक			sbm_link;	/* current link state */

	अचिन्हित अक्षर		sbm_hwaddr[ETH_ALEN];

	काष्ठा sbmacdma		sbm_txdma;	/* only channel 0 क्रम now */
	काष्ठा sbmacdma		sbm_rxdma;
	पूर्णांक			rx_hw_checksum;
	पूर्णांक			sbe_idx;
पूर्ण;


/**********************************************************************
 *  Externs
 ********************************************************************* */

/**********************************************************************
 *  Prototypes
 ********************************************************************* */

अटल व्योम sbdma_initctx(काष्ठा sbmacdma *d, काष्ठा sbmac_softc *s, पूर्णांक chan,
			  पूर्णांक txrx, पूर्णांक maxdescr);
अटल व्योम sbdma_channel_start(काष्ठा sbmacdma *d, पूर्णांक rxtx);
अटल पूर्णांक sbdma_add_rcvbuffer(काष्ठा sbmac_softc *sc, काष्ठा sbmacdma *d,
			       काष्ठा sk_buff *m);
अटल पूर्णांक sbdma_add_txbuffer(काष्ठा sbmacdma *d, काष्ठा sk_buff *m);
अटल व्योम sbdma_emptyring(काष्ठा sbmacdma *d);
अटल व्योम sbdma_fillring(काष्ठा sbmac_softc *sc, काष्ठा sbmacdma *d);
अटल पूर्णांक sbdma_rx_process(काष्ठा sbmac_softc *sc, काष्ठा sbmacdma *d,
			    पूर्णांक work_to_करो, पूर्णांक poll);
अटल व्योम sbdma_tx_process(काष्ठा sbmac_softc *sc, काष्ठा sbmacdma *d,
			     पूर्णांक poll);
अटल पूर्णांक sbmac_initctx(काष्ठा sbmac_softc *s);
अटल व्योम sbmac_channel_start(काष्ठा sbmac_softc *s);
अटल व्योम sbmac_channel_stop(काष्ठा sbmac_softc *s);
अटल क्रमागत sbmac_state sbmac_set_channel_state(काष्ठा sbmac_softc *,
						क्रमागत sbmac_state);
अटल व्योम sbmac_promiscuous_mode(काष्ठा sbmac_softc *sc, पूर्णांक onoff);
अटल uपूर्णांक64_t sbmac_addr2reg(अचिन्हित अक्षर *ptr);
अटल irqवापस_t sbmac_पूर्णांकr(पूर्णांक irq, व्योम *dev_instance);
अटल netdev_tx_t sbmac_start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल व्योम sbmac_seपंचांगulti(काष्ठा sbmac_softc *sc);
अटल पूर्णांक sbmac_init(काष्ठा platक्रमm_device *pldev, दीर्घ दीर्घ base);
अटल पूर्णांक sbmac_set_speed(काष्ठा sbmac_softc *s, क्रमागत sbmac_speed speed);
अटल पूर्णांक sbmac_set_duplex(काष्ठा sbmac_softc *s, क्रमागत sbmac_duplex duplex,
			    क्रमागत sbmac_fc fc);

अटल पूर्णांक sbmac_खोलो(काष्ठा net_device *dev);
अटल व्योम sbmac_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम sbmac_set_rx_mode(काष्ठा net_device *dev);
अटल पूर्णांक sbmac_mii_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल पूर्णांक sbmac_बंद(काष्ठा net_device *dev);
अटल पूर्णांक sbmac_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);

अटल व्योम sbmac_mii_poll(काष्ठा net_device *dev);
अटल पूर्णांक sbmac_mii_probe(काष्ठा net_device *dev);

अटल व्योम sbmac_mii_sync(व्योम __iomem *sbm_mdio);
अटल व्योम sbmac_mii_senddata(व्योम __iomem *sbm_mdio, अचिन्हित पूर्णांक data,
			       पूर्णांक bitcnt);
अटल पूर्णांक sbmac_mii_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक regidx);
अटल पूर्णांक sbmac_mii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक regidx,
			   u16 val);


/**********************************************************************
 *  Globals
 ********************************************************************* */

अटल अक्षर sbmac_string[] = "sb1250-mac";

अटल अक्षर sbmac_mdio_string[] = "sb1250-mac-mdio";


/**********************************************************************
 *  MDIO स्थिरants
 ********************************************************************* */

#घोषणा	MII_COMMAND_START	0x01
#घोषणा	MII_COMMAND_READ	0x02
#घोषणा	MII_COMMAND_WRITE	0x01
#घोषणा	MII_COMMAND_ACK		0x02

#घोषणा M_MAC_MDIO_सूची_OUTPUT	0		/* क्रम clarity */

#घोषणा ENABLE 		1
#घोषणा DISABLE		0

/**********************************************************************
 *  SBMAC_MII_SYNC(sbm_mdio)
 *
 *  Synchronize with the MII - send a pattern of bits to the MII
 *  that will guarantee that it is पढ़ोy to accept a command.
 *
 *  Input parameters:
 *  	   sbm_mdio - address of the MAC's MDIO रेजिस्टर
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbmac_mii_sync(व्योम __iomem *sbm_mdio)
अणु
	पूर्णांक cnt;
	uपूर्णांक64_t bits;
	पूर्णांक mac_mdio_genc;

	mac_mdio_genc = __raw_पढ़ोq(sbm_mdio) & M_MAC_GENC;

	bits = M_MAC_MDIO_सूची_OUTPUT | M_MAC_MDIO_OUT;

	__raw_ग_लिखोq(bits | mac_mdio_genc, sbm_mdio);

	क्रम (cnt = 0; cnt < 32; cnt++) अणु
		__raw_ग_लिखोq(bits | M_MAC_MDC | mac_mdio_genc, sbm_mdio);
		__raw_ग_लिखोq(bits | mac_mdio_genc, sbm_mdio);
	पूर्ण
पूर्ण

/**********************************************************************
 *  SBMAC_MII_SENDDATA(sbm_mdio, data, bitcnt)
 *
 *  Send some bits to the MII.  The bits to be sent are right-
 *  justअगरied in the 'data' parameter.
 *
 *  Input parameters:
 *  	   sbm_mdio - address of the MAC's MDIO रेजिस्टर
 *  	   data     - data to send
 *  	   bitcnt   - number of bits to send
 ********************************************************************* */

अटल व्योम sbmac_mii_senddata(व्योम __iomem *sbm_mdio, अचिन्हित पूर्णांक data,
			       पूर्णांक bitcnt)
अणु
	पूर्णांक i;
	uपूर्णांक64_t bits;
	अचिन्हित पूर्णांक curmask;
	पूर्णांक mac_mdio_genc;

	mac_mdio_genc = __raw_पढ़ोq(sbm_mdio) & M_MAC_GENC;

	bits = M_MAC_MDIO_सूची_OUTPUT;
	__raw_ग_लिखोq(bits | mac_mdio_genc, sbm_mdio);

	curmask = 1 << (bitcnt - 1);

	क्रम (i = 0; i < bitcnt; i++) अणु
		अगर (data & curmask)
			bits |= M_MAC_MDIO_OUT;
		अन्यथा bits &= ~M_MAC_MDIO_OUT;
		__raw_ग_लिखोq(bits | mac_mdio_genc, sbm_mdio);
		__raw_ग_लिखोq(bits | M_MAC_MDC | mac_mdio_genc, sbm_mdio);
		__raw_ग_लिखोq(bits | mac_mdio_genc, sbm_mdio);
		curmask >>= 1;
	पूर्ण
पूर्ण



/**********************************************************************
 *  SBMAC_MII_READ(bus, phyaddr, regidx)
 *  Read a PHY रेजिस्टर.
 *
 *  Input parameters:
 *  	   bus     - MDIO bus handle
 *  	   phyaddr - PHY's address
 *  	   regnum  - index of रेजिस्टर to पढ़ो
 *
 *  Return value:
 *  	   value पढ़ो, or 0xffff अगर an error occurred.
 ********************************************************************* */

अटल पूर्णांक sbmac_mii_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक regidx)
अणु
	काष्ठा sbmac_softc *sc = (काष्ठा sbmac_softc *)bus->priv;
	व्योम __iomem *sbm_mdio = sc->sbm_mdio;
	पूर्णांक idx;
	पूर्णांक error;
	पूर्णांक regval;
	पूर्णांक mac_mdio_genc;

	/*
	 * Synchronize ourselves so that the PHY knows the next
	 * thing coming करोwn is a command
	 */
	sbmac_mii_sync(sbm_mdio);

	/*
	 * Send the data to the PHY.  The sequence is
	 * a "start" command (2 bits)
	 * a "read" command (2 bits)
	 * the PHY addr (5 bits)
	 * the रेजिस्टर index (5 bits)
	 */
	sbmac_mii_senddata(sbm_mdio, MII_COMMAND_START, 2);
	sbmac_mii_senddata(sbm_mdio, MII_COMMAND_READ, 2);
	sbmac_mii_senddata(sbm_mdio, phyaddr, 5);
	sbmac_mii_senddata(sbm_mdio, regidx, 5);

	mac_mdio_genc = __raw_पढ़ोq(sbm_mdio) & M_MAC_GENC;

	/*
	 * Switch the port around without a घड़ी transition.
	 */
	__raw_ग_लिखोq(M_MAC_MDIO_सूची_INPUT | mac_mdio_genc, sbm_mdio);

	/*
	 * Send out a घड़ी pulse to संकेत we want the status
	 */
	__raw_ग_लिखोq(M_MAC_MDIO_सूची_INPUT | M_MAC_MDC | mac_mdio_genc,
		     sbm_mdio);
	__raw_ग_लिखोq(M_MAC_MDIO_सूची_INPUT | mac_mdio_genc, sbm_mdio);

	/*
	 * If an error occurred, the PHY will संकेत '1' back
	 */
	error = __raw_पढ़ोq(sbm_mdio) & M_MAC_MDIO_IN;

	/*
	 * Issue an 'idle' घड़ी pulse, but keep the direction
	 * the same.
	 */
	__raw_ग_लिखोq(M_MAC_MDIO_सूची_INPUT | M_MAC_MDC | mac_mdio_genc,
		     sbm_mdio);
	__raw_ग_लिखोq(M_MAC_MDIO_सूची_INPUT | mac_mdio_genc, sbm_mdio);

	regval = 0;

	क्रम (idx = 0; idx < 16; idx++) अणु
		regval <<= 1;

		अगर (error == 0) अणु
			अगर (__raw_पढ़ोq(sbm_mdio) & M_MAC_MDIO_IN)
				regval |= 1;
		पूर्ण

		__raw_ग_लिखोq(M_MAC_MDIO_सूची_INPUT | M_MAC_MDC | mac_mdio_genc,
			     sbm_mdio);
		__raw_ग_लिखोq(M_MAC_MDIO_सूची_INPUT | mac_mdio_genc, sbm_mdio);
	पूर्ण

	/* Switch back to output */
	__raw_ग_लिखोq(M_MAC_MDIO_सूची_OUTPUT | mac_mdio_genc, sbm_mdio);

	अगर (error == 0)
		वापस regval;
	वापस 0xffff;
पूर्ण


/**********************************************************************
 *  SBMAC_MII_WRITE(bus, phyaddr, regidx, regval)
 *
 *  Write a value to a PHY रेजिस्टर.
 *
 *  Input parameters:
 *  	   bus     - MDIO bus handle
 *  	   phyaddr - PHY to use
 *  	   regidx  - रेजिस्टर within the PHY
 *  	   regval  - data to ग_लिखो to रेजिस्टर
 *
 *  Return value:
 *  	   0 क्रम success
 ********************************************************************* */

अटल पूर्णांक sbmac_mii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक regidx,
			   u16 regval)
अणु
	काष्ठा sbmac_softc *sc = (काष्ठा sbmac_softc *)bus->priv;
	व्योम __iomem *sbm_mdio = sc->sbm_mdio;
	पूर्णांक mac_mdio_genc;

	sbmac_mii_sync(sbm_mdio);

	sbmac_mii_senddata(sbm_mdio, MII_COMMAND_START, 2);
	sbmac_mii_senddata(sbm_mdio, MII_COMMAND_WRITE, 2);
	sbmac_mii_senddata(sbm_mdio, phyaddr, 5);
	sbmac_mii_senddata(sbm_mdio, regidx, 5);
	sbmac_mii_senddata(sbm_mdio, MII_COMMAND_ACK, 2);
	sbmac_mii_senddata(sbm_mdio, regval, 16);

	mac_mdio_genc = __raw_पढ़ोq(sbm_mdio) & M_MAC_GENC;

	__raw_ग_लिखोq(M_MAC_MDIO_सूची_OUTPUT | mac_mdio_genc, sbm_mdio);

	वापस 0;
पूर्ण



/**********************************************************************
 *  SBDMA_INITCTX(d,s,chan,txrx,maxdescr)
 *
 *  Initialize a DMA channel context.  Since there are potentially
 *  eight DMA channels per MAC, it's nice to करो this in a standard
 *  way.
 *
 *  Input parameters:
 *  	   d - काष्ठा sbmacdma (DMA channel context)
 *  	   s - काष्ठा sbmac_softc (poपूर्णांकer to a MAC)
 *  	   chan - channel number (0..1 right now)
 *  	   txrx - Identअगरies DMA_TX or DMA_RX क्रम channel direction
 *      maxdescr - number of descriptors
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbdma_initctx(काष्ठा sbmacdma *d, काष्ठा sbmac_softc *s, पूर्णांक chan,
			  पूर्णांक txrx, पूर्णांक maxdescr)
अणु
#अगर_घोषित CONFIG_SBMAC_COALESCE
	पूर्णांक पूर्णांक_pktcnt, पूर्णांक_समयout;
#पूर्ण_अगर

	/*
	 * Save away पूर्णांकeresting stuff in the काष्ठाure
	 */

	d->sbdma_eth       = s;
	d->sbdma_channel   = chan;
	d->sbdma_txdir     = txrx;

#अगर 0
	/* RMON clearing */
	s->sbe_idx =(s->sbm_base - A_MAC_BASE_0)/MAC_SPACING;
#पूर्ण_अगर

	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_TX_BYTES);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_COLLISIONS);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_LATE_COL);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_EX_COL);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_FCS_ERROR);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_TX_ABORT);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_TX_BAD);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_TX_GOOD);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_TX_RUNT);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_TX_OVERSIZE);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_BYTES);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_MCAST);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_BCAST);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_BAD);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_GOOD);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_RUNT);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_OVERSIZE);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_FCS_ERROR);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_LENGTH_ERROR);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_CODE_ERROR);
	__raw_ग_लिखोq(0, s->sbm_base + R_MAC_RMON_RX_ALIGN_ERROR);

	/*
	 * initialize रेजिस्टर poपूर्णांकers
	 */

	d->sbdma_config0 =
		s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_CONFIG0);
	d->sbdma_config1 =
		s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_CONFIG1);
	d->sbdma_dscrbase =
		s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_DSCR_BASE);
	d->sbdma_dscrcnt =
		s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_DSCR_CNT);
	d->sbdma_curdscr =
		s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_CUR_DSCRADDR);
	अगर (d->sbdma_txdir)
		d->sbdma_oodpktlost = शून्य;
	अन्यथा
		d->sbdma_oodpktlost =
			s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_OODPKTLOST_RX);

	/*
	 * Allocate memory क्रम the ring
	 */

	d->sbdma_maxdescr = maxdescr;

	d->sbdma_dscrtable_unaligned = kसुस्मृति(d->sbdma_maxdescr + 1,
					       माप(*d->sbdma_dscrtable),
					       GFP_KERNEL);

	/*
	 * The descriptor table must be aligned to at least 16 bytes or the
	 * MAC will corrupt it.
	 */
	d->sbdma_dscrtable = (काष्ठा sbdmadscr *)
			     ALIGN((अचिन्हित दीर्घ)d->sbdma_dscrtable_unaligned,
				   माप(*d->sbdma_dscrtable));

	d->sbdma_dscrtable_end = d->sbdma_dscrtable + d->sbdma_maxdescr;

	d->sbdma_dscrtable_phys = virt_to_phys(d->sbdma_dscrtable);

	/*
	 * And context table
	 */

	d->sbdma_ctxtable = kसुस्मृति(d->sbdma_maxdescr,
				    माप(*d->sbdma_ctxtable), GFP_KERNEL);

#अगर_घोषित CONFIG_SBMAC_COALESCE
	/*
	 * Setup Rx/Tx DMA coalescing शेषs
	 */

	पूर्णांक_pktcnt = (txrx == DMA_TX) ? पूर्णांक_pktcnt_tx : पूर्णांक_pktcnt_rx;
	अगर ( पूर्णांक_pktcnt ) अणु
		d->sbdma_पूर्णांक_pktcnt = पूर्णांक_pktcnt;
	पूर्ण अन्यथा अणु
		d->sbdma_पूर्णांक_pktcnt = 1;
	पूर्ण

	पूर्णांक_समयout = (txrx == DMA_TX) ? पूर्णांक_समयout_tx : पूर्णांक_समयout_rx;
	अगर ( पूर्णांक_समयout ) अणु
		d->sbdma_पूर्णांक_समयout = पूर्णांक_समयout;
	पूर्ण अन्यथा अणु
		d->sbdma_पूर्णांक_समयout = 0;
	पूर्ण
#पूर्ण_अगर

पूर्ण

/**********************************************************************
 *  SBDMA_CHANNEL_START(d)
 *
 *  Initialize the hardware रेजिस्टरs क्रम a DMA channel.
 *
 *  Input parameters:
 *  	   d - DMA channel to init (context must be previously init'd
 *         rxtx - DMA_RX or DMA_TX depending on what type of channel
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbdma_channel_start(काष्ठा sbmacdma *d, पूर्णांक rxtx)
अणु
	/*
	 * Turn on the DMA channel
	 */

#अगर_घोषित CONFIG_SBMAC_COALESCE
	__raw_ग_लिखोq(V_DMA_INT_TIMEOUT(d->sbdma_पूर्णांक_समयout) |
		       0, d->sbdma_config1);
	__raw_ग_लिखोq(M_DMA_EOP_INT_EN |
		       V_DMA_RINGSZ(d->sbdma_maxdescr) |
		       V_DMA_INT_PKTCNT(d->sbdma_पूर्णांक_pktcnt) |
		       0, d->sbdma_config0);
#अन्यथा
	__raw_ग_लिखोq(0, d->sbdma_config1);
	__raw_ग_लिखोq(V_DMA_RINGSZ(d->sbdma_maxdescr) |
		       0, d->sbdma_config0);
#पूर्ण_अगर

	__raw_ग_लिखोq(d->sbdma_dscrtable_phys, d->sbdma_dscrbase);

	/*
	 * Initialize ring poपूर्णांकers
	 */

	d->sbdma_addptr = d->sbdma_dscrtable;
	d->sbdma_remptr = d->sbdma_dscrtable;
पूर्ण

/**********************************************************************
 *  SBDMA_CHANNEL_STOP(d)
 *
 *  Initialize the hardware रेजिस्टरs क्रम a DMA channel.
 *
 *  Input parameters:
 *  	   d - DMA channel to init (context must be previously init'd
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbdma_channel_stop(काष्ठा sbmacdma *d)
अणु
	/*
	 * Turn off the DMA channel
	 */

	__raw_ग_लिखोq(0, d->sbdma_config1);

	__raw_ग_लिखोq(0, d->sbdma_dscrbase);

	__raw_ग_लिखोq(0, d->sbdma_config0);

	/*
	 * Zero ring poपूर्णांकers
	 */

	d->sbdma_addptr = शून्य;
	d->sbdma_remptr = शून्य;
पूर्ण

अटल अंतरभूत व्योम sbdma_align_skb(काष्ठा sk_buff *skb,
				   अचिन्हित पूर्णांक घातer2, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित अक्षर *addr = skb->data;
	अचिन्हित अक्षर *newaddr = PTR_ALIGN(addr, घातer2);

	skb_reserve(skb, newaddr - addr + offset);
पूर्ण


/**********************************************************************
 *  SBDMA_ADD_RCVBUFFER(d,sb)
 *
 *  Add a buffer to the specअगरied DMA channel.   For receive channels,
 *  this queues a buffer क्रम inbound packets.
 *
 *  Input parameters:
 *	   sc - softc काष्ठाure
 *  	    d - DMA channel descriptor
 * 	   sb - sk_buff to add, or शून्य अगर we should allocate one
 *
 *  Return value:
 *  	   0 अगर buffer could not be added (ring is full)
 *  	   1 अगर buffer added successfully
 ********************************************************************* */


अटल पूर्णांक sbdma_add_rcvbuffer(काष्ठा sbmac_softc *sc, काष्ठा sbmacdma *d,
			       काष्ठा sk_buff *sb)
अणु
	काष्ठा net_device *dev = sc->sbm_dev;
	काष्ठा sbdmadscr *dsc;
	काष्ठा sbdmadscr *nextdsc;
	काष्ठा sk_buff *sb_new = शून्य;
	पूर्णांक pktsize = ENET_PACKET_SIZE;

	/* get poपूर्णांकer to our current place in the ring */

	dsc = d->sbdma_addptr;
	nextdsc = SBDMA_NEXTBUF(d,sbdma_addptr);

	/*
	 * figure out अगर the ring is full - अगर the next descriptor
	 * is the same as the one that we're going to हटाओ from
	 * the ring, the ring is full
	 */

	अगर (nextdsc == d->sbdma_remptr) अणु
		वापस -ENOSPC;
	पूर्ण

	/*
	 * Allocate a sk_buff अगर we करोn't alपढ़ोy have one.
	 * If we करो have an sk_buff, reset it so that it's empty.
	 *
	 * Note: sk_buffs करोn't seem to be guaranteed to have any sort
	 * of alignment when they are allocated.  Thereक्रमe, allocate enough
	 * extra space to make sure that:
	 *
	 *    1. the data करोes not start in the middle of a cache line.
	 *    2. The data करोes not end in the middle of a cache line
	 *    3. The buffer can be aligned such that the IP addresses are
	 *       naturally aligned.
	 *
	 *  Remember, the SOCs MAC ग_लिखोs whole cache lines at a समय,
	 *  without पढ़ोing the old contents first.  So, अगर the sk_buff's
	 *  data portion starts in the middle of a cache line, the SOC
	 *  DMA will trash the beginning (and ending) portions.
	 */

	अगर (sb == शून्य) अणु
		sb_new = netdev_alloc_skb(dev, ENET_PACKET_SIZE +
					       SMP_CACHE_BYTES * 2 +
					       NET_IP_ALIGN);
		अगर (sb_new == शून्य)
			वापस -ENOBUFS;

		sbdma_align_skb(sb_new, SMP_CACHE_BYTES, NET_IP_ALIGN);
	पूर्ण
	अन्यथा अणु
		sb_new = sb;
		/*
		 * nothing special to reinit buffer, it's alपढ़ोy aligned
		 * and sb->data alपढ़ोy poपूर्णांकs to a good place.
		 */
	पूर्ण

	/*
	 * fill in the descriptor
	 */

#अगर_घोषित CONFIG_SBMAC_COALESCE
	/*
	 * Do not पूर्णांकerrupt per DMA transfer.
	 */
	dsc->dscr_a = virt_to_phys(sb_new->data) |
		V_DMA_DSCRA_A_SIZE(NUMCACHEBLKS(pktsize + NET_IP_ALIGN)) | 0;
#अन्यथा
	dsc->dscr_a = virt_to_phys(sb_new->data) |
		V_DMA_DSCRA_A_SIZE(NUMCACHEBLKS(pktsize + NET_IP_ALIGN)) |
		M_DMA_DSCRA_INTERRUPT;
#पूर्ण_अगर

	/* receiving: no options */
	dsc->dscr_b = 0;

	/*
	 * fill in the context
	 */

	d->sbdma_ctxtable[dsc-d->sbdma_dscrtable] = sb_new;

	/*
	 * poपूर्णांक at next packet
	 */

	d->sbdma_addptr = nextdsc;

	/*
	 * Give the buffer to the DMA engine.
	 */

	__raw_ग_लिखोq(1, d->sbdma_dscrcnt);

	वापस 0;					/* we did it */
पूर्ण

/**********************************************************************
 *  SBDMA_ADD_TXBUFFER(d,sb)
 *
 *  Add a transmit buffer to the specअगरied DMA channel, causing a
 *  transmit to start.
 *
 *  Input parameters:
 *  	   d - DMA channel descriptor
 * 	   sb - sk_buff to add
 *
 *  Return value:
 *  	   0 transmit queued successfully
 *  	   otherwise error code
 ********************************************************************* */


अटल पूर्णांक sbdma_add_txbuffer(काष्ठा sbmacdma *d, काष्ठा sk_buff *sb)
अणु
	काष्ठा sbdmadscr *dsc;
	काष्ठा sbdmadscr *nextdsc;
	uपूर्णांक64_t phys;
	uपूर्णांक64_t ncb;
	पूर्णांक length;

	/* get poपूर्णांकer to our current place in the ring */

	dsc = d->sbdma_addptr;
	nextdsc = SBDMA_NEXTBUF(d,sbdma_addptr);

	/*
	 * figure out अगर the ring is full - अगर the next descriptor
	 * is the same as the one that we're going to हटाओ from
	 * the ring, the ring is full
	 */

	अगर (nextdsc == d->sbdma_remptr) अणु
		वापस -ENOSPC;
	पूर्ण

	/*
	 * Under Linux, it's not necessary to copy/coalesce buffers
	 * like it is on NetBSD.  We think they're all contiguous,
	 * but that may not be true क्रम GBE.
	 */

	length = sb->len;

	/*
	 * fill in the descriptor.  Note that the number of cache
	 * blocks in the descriptor is the number of blocks
	 * *spanned*, so we need to add in the offset (अगर any)
	 * जबतक करोing the calculation.
	 */

	phys = virt_to_phys(sb->data);
	ncb = NUMCACHEBLKS(length+(phys & (SMP_CACHE_BYTES - 1)));

	dsc->dscr_a = phys |
		V_DMA_DSCRA_A_SIZE(ncb) |
#अगर_अघोषित CONFIG_SBMAC_COALESCE
		M_DMA_DSCRA_INTERRUPT |
#पूर्ण_अगर
		M_DMA_ETHTX_SOP;

	/* transmitting: set outbound options and length */

	dsc->dscr_b = V_DMA_DSCRB_OPTIONS(K_DMA_ETHTX_APPENDCRC_APPENDPAD) |
		V_DMA_DSCRB_PKT_SIZE(length);

	/*
	 * fill in the context
	 */

	d->sbdma_ctxtable[dsc-d->sbdma_dscrtable] = sb;

	/*
	 * poपूर्णांक at next packet
	 */

	d->sbdma_addptr = nextdsc;

	/*
	 * Give the buffer to the DMA engine.
	 */

	__raw_ग_लिखोq(1, d->sbdma_dscrcnt);

	वापस 0;					/* we did it */
पूर्ण




/**********************************************************************
 *  SBDMA_EMPTYRING(d)
 *
 *  Free all allocated sk_buffs on the specअगरied DMA channel;
 *
 *  Input parameters:
 *  	   d  - DMA channel
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbdma_emptyring(काष्ठा sbmacdma *d)
अणु
	पूर्णांक idx;
	काष्ठा sk_buff *sb;

	क्रम (idx = 0; idx < d->sbdma_maxdescr; idx++) अणु
		sb = d->sbdma_ctxtable[idx];
		अगर (sb) अणु
			dev_kमुक्त_skb(sb);
			d->sbdma_ctxtable[idx] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण


/**********************************************************************
 *  SBDMA_FILLRING(d)
 *
 *  Fill the specअगरied DMA channel (must be receive channel)
 *  with sk_buffs
 *
 *  Input parameters:
 *	   sc - softc काष्ठाure
 *  	    d - DMA channel
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbdma_fillring(काष्ठा sbmac_softc *sc, काष्ठा sbmacdma *d)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < SBMAC_MAX_RXDESCR - 1; idx++) अणु
		अगर (sbdma_add_rcvbuffer(sc, d, शून्य) != 0)
			अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम sbmac_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा sbmac_softc *sc = netdev_priv(netdev);
	पूर्णांक irq = sc->sbm_dev->irq;

	__raw_ग_लिखोq(0, sc->sbm_imr);

	sbmac_पूर्णांकr(irq, netdev);

#अगर_घोषित CONFIG_SBMAC_COALESCE
	__raw_ग_लिखोq(((M_MAC_INT_EOP_COUNT | M_MAC_INT_EOP_TIMER) << S_MAC_TX_CH0) |
	((M_MAC_INT_EOP_COUNT | M_MAC_INT_EOP_TIMER) << S_MAC_RX_CH0),
	sc->sbm_imr);
#अन्यथा
	__raw_ग_लिखोq((M_MAC_INT_CHANNEL << S_MAC_TX_CH0) |
	(M_MAC_INT_CHANNEL << S_MAC_RX_CH0), sc->sbm_imr);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

/**********************************************************************
 *  SBDMA_RX_PROCESS(sc,d,work_to_करो,poll)
 *
 *  Process "completed" receive buffers on the specअगरied DMA channel.
 *
 *  Input parameters:
 *            sc - softc काष्ठाure
 *  	       d - DMA channel context
 *    work_to_करो - no. of packets to process beक्रमe enabling पूर्णांकerrupt
 *                 again (क्रम NAPI)
 *          poll - 1: using polling (क्रम NAPI)
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल पूर्णांक sbdma_rx_process(काष्ठा sbmac_softc *sc, काष्ठा sbmacdma *d,
			    पूर्णांक work_to_करो, पूर्णांक poll)
अणु
	काष्ठा net_device *dev = sc->sbm_dev;
	पूर्णांक curidx;
	पूर्णांक hwidx;
	काष्ठा sbdmadscr *dsc;
	काष्ठा sk_buff *sb;
	पूर्णांक len;
	पूर्णांक work_करोne = 0;
	पूर्णांक dropped = 0;

	prefetch(d);

again:
	/* Check अगर the HW dropped any frames */
	dev->stats.rx_fअगरo_errors
	    += __raw_पढ़ोq(sc->sbm_rxdma.sbdma_oodpktlost) & 0xffff;
	__raw_ग_लिखोq(0, sc->sbm_rxdma.sbdma_oodpktlost);

	जबतक (work_to_करो-- > 0) अणु
		/*
		 * figure out where we are (as an index) and where
		 * the hardware is (also as an index)
		 *
		 * This could be करोne faster अगर (क्रम example) the
		 * descriptor table was page-aligned and contiguous in
		 * both भव and physical memory -- you could then
		 * just compare the low-order bits of the भव address
		 * (sbdma_remptr) and the physical address (sbdma_curdscr CSR)
		 */

		dsc = d->sbdma_remptr;
		curidx = dsc - d->sbdma_dscrtable;

		prefetch(dsc);
		prefetch(&d->sbdma_ctxtable[curidx]);

		hwidx = ((__raw_पढ़ोq(d->sbdma_curdscr) & M_DMA_CURDSCR_ADDR) -
			 d->sbdma_dscrtable_phys) /
			माप(*d->sbdma_dscrtable);

		/*
		 * If they're the same, that means we've processed all
		 * of the descriptors up to (but not including) the one that
		 * the hardware is working on right now.
		 */

		अगर (curidx == hwidx)
			जाओ करोne;

		/*
		 * Otherwise, get the packet's sk_buff ptr back
		 */

		sb = d->sbdma_ctxtable[curidx];
		d->sbdma_ctxtable[curidx] = शून्य;

		len = (पूर्णांक)G_DMA_DSCRB_PKT_SIZE(dsc->dscr_b) - 4;

		/*
		 * Check packet status.  If good, process it.
		 * If not, silently drop it and put it back on the
		 * receive ring.
		 */

		अगर (likely (!(dsc->dscr_a & M_DMA_ETHRX_BAD))) अणु

			/*
			 * Add a new buffer to replace the old one.  If we fail
			 * to allocate a buffer, we're going to drop this
			 * packet and put it right back on the receive ring.
			 */

			अगर (unlikely(sbdma_add_rcvbuffer(sc, d, शून्य) ==
				     -ENOBUFS)) अणु
				dev->stats.rx_dropped++;
				/* Re-add old buffer */
				sbdma_add_rcvbuffer(sc, d, sb);
				/* No poपूर्णांक in continuing at the moment */
				prपूर्णांकk(KERN_ERR "dropped packet (1)\n");
				d->sbdma_remptr = SBDMA_NEXTBUF(d,sbdma_remptr);
				जाओ करोne;
			पूर्ण अन्यथा अणु
				/*
				 * Set length पूर्णांकo the packet
				 */
				skb_put(sb,len);

				/*
				 * Buffer has been replaced on the
				 * receive ring.  Pass the buffer to
				 * the kernel
				 */
				sb->protocol = eth_type_trans(sb,d->sbdma_eth->sbm_dev);
				/* Check hw IPv4/TCP checksum अगर supported */
				अगर (sc->rx_hw_checksum == ENABLE) अणु
					अगर (!((dsc->dscr_a) & M_DMA_ETHRX_BADIP4CS) &&
					    !((dsc->dscr_a) & M_DMA_ETHRX_BADTCPCS)) अणु
						sb->ip_summed = CHECKSUM_UNNECESSARY;
						/* करोn't need to set sb->csum */
					पूर्ण अन्यथा अणु
						skb_checksum_none_निश्चित(sb);
					पूर्ण
				पूर्ण
				prefetch(sb->data);
				prefetch((स्थिर व्योम *)(((अक्षर *)sb->data)+32));
				अगर (poll)
					dropped = netअगर_receive_skb(sb);
				अन्यथा
					dropped = netअगर_rx(sb);

				अगर (dropped == NET_RX_DROP) अणु
					dev->stats.rx_dropped++;
					d->sbdma_remptr = SBDMA_NEXTBUF(d,sbdma_remptr);
					जाओ करोne;
				पूर्ण
				अन्यथा अणु
					dev->stats.rx_bytes += len;
					dev->stats.rx_packets++;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Packet was mangled somehow.  Just drop it and
			 * put it back on the receive ring.
			 */
			dev->stats.rx_errors++;
			sbdma_add_rcvbuffer(sc, d, sb);
		पूर्ण


		/*
		 * .. and advance to the next buffer.
		 */

		d->sbdma_remptr = SBDMA_NEXTBUF(d,sbdma_remptr);
		work_करोne++;
	पूर्ण
	अगर (!poll) अणु
		work_to_करो = 32;
		जाओ again; /* collect fअगरo drop statistics again */
	पूर्ण
करोne:
	वापस work_करोne;
पूर्ण

/**********************************************************************
 *  SBDMA_TX_PROCESS(sc,d)
 *
 *  Process "completed" transmit buffers on the specअगरied DMA channel.
 *  This is normally called within the पूर्णांकerrupt service routine.
 *  Note that this isn't really ideal क्रम priority channels, since
 *  it processes all of the packets on a given channel beक्रमe
 *  वापसing.
 *
 *  Input parameters:
 *      sc - softc काष्ठाure
 *  	 d - DMA channel context
 *    poll - 1: using polling (क्रम NAPI)
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbdma_tx_process(काष्ठा sbmac_softc *sc, काष्ठा sbmacdma *d,
			     पूर्णांक poll)
अणु
	काष्ठा net_device *dev = sc->sbm_dev;
	पूर्णांक curidx;
	पूर्णांक hwidx;
	काष्ठा sbdmadscr *dsc;
	काष्ठा sk_buff *sb;
	अचिन्हित दीर्घ flags;
	पूर्णांक packets_handled = 0;

	spin_lock_irqsave(&(sc->sbm_lock), flags);

	अगर (d->sbdma_remptr == d->sbdma_addptr)
	  जाओ end_unlock;

	hwidx = ((__raw_पढ़ोq(d->sbdma_curdscr) & M_DMA_CURDSCR_ADDR) -
		 d->sbdma_dscrtable_phys) / माप(*d->sbdma_dscrtable);

	क्रम (;;) अणु
		/*
		 * figure out where we are (as an index) and where
		 * the hardware is (also as an index)
		 *
		 * This could be करोne faster अगर (क्रम example) the
		 * descriptor table was page-aligned and contiguous in
		 * both भव and physical memory -- you could then
		 * just compare the low-order bits of the भव address
		 * (sbdma_remptr) and the physical address (sbdma_curdscr CSR)
		 */

		curidx = d->sbdma_remptr - d->sbdma_dscrtable;

		/*
		 * If they're the same, that means we've processed all
		 * of the descriptors up to (but not including) the one that
		 * the hardware is working on right now.
		 */

		अगर (curidx == hwidx)
			अवरोध;

		/*
		 * Otherwise, get the packet's sk_buff ptr back
		 */

		dsc = &(d->sbdma_dscrtable[curidx]);
		sb = d->sbdma_ctxtable[curidx];
		d->sbdma_ctxtable[curidx] = शून्य;

		/*
		 * Stats
		 */

		dev->stats.tx_bytes += sb->len;
		dev->stats.tx_packets++;

		/*
		 * क्रम transmits, we just मुक्त buffers.
		 */

		dev_consume_skb_irq(sb);

		/*
		 * .. and advance to the next buffer.
		 */

		d->sbdma_remptr = SBDMA_NEXTBUF(d,sbdma_remptr);

		packets_handled++;

	पूर्ण

	/*
	 * Decide अगर we should wake up the protocol or not.
	 * Other drivers seem to करो this when we reach a low
	 * watermark on the transmit queue.
	 */

	अगर (packets_handled)
		netअगर_wake_queue(d->sbdma_eth->sbm_dev);

end_unlock:
	spin_unlock_irqrestore(&(sc->sbm_lock), flags);

पूर्ण



/**********************************************************************
 *  SBMAC_INITCTX(s)
 *
 *  Initialize an Ethernet context काष्ठाure - this is called
 *  once per MAC on the 1250.  Memory is allocated here, so करोn't
 *  call it again from inside the ioctl routines that bring the
 *  पूर्णांकerface up/करोwn
 *
 *  Input parameters:
 *  	   s - sbmac context काष्ठाure
 *
 *  Return value:
 *  	   0
 ********************************************************************* */

अटल पूर्णांक sbmac_initctx(काष्ठा sbmac_softc *s)
अणु

	/*
	 * figure out the addresses of some ports
	 */

	s->sbm_macenable = s->sbm_base + R_MAC_ENABLE;
	s->sbm_maccfg    = s->sbm_base + R_MAC_CFG;
	s->sbm_fअगरocfg   = s->sbm_base + R_MAC_THRSH_CFG;
	s->sbm_framecfg  = s->sbm_base + R_MAC_FRAMECFG;
	s->sbm_rxfilter  = s->sbm_base + R_MAC_ADFILTER_CFG;
	s->sbm_isr       = s->sbm_base + R_MAC_STATUS;
	s->sbm_imr       = s->sbm_base + R_MAC_INT_MASK;
	s->sbm_mdio      = s->sbm_base + R_MAC_MDIO;

	/*
	 * Initialize the DMA channels.  Right now, only one per MAC is used
	 * Note: Only करो this _once_, as it allocates memory from the kernel!
	 */

	sbdma_initctx(&(s->sbm_txdma),s,0,DMA_TX,SBMAC_MAX_TXDESCR);
	sbdma_initctx(&(s->sbm_rxdma),s,0,DMA_RX,SBMAC_MAX_RXDESCR);

	/*
	 * initial state is OFF
	 */

	s->sbm_state = sbmac_state_off;

	वापस 0;
पूर्ण


अटल व्योम sbdma_uninitctx(काष्ठा sbmacdma *d)
अणु
	kमुक्त(d->sbdma_dscrtable_unaligned);
	d->sbdma_dscrtable_unaligned = d->sbdma_dscrtable = शून्य;

	kमुक्त(d->sbdma_ctxtable);
	d->sbdma_ctxtable = शून्य;
पूर्ण


अटल व्योम sbmac_uninitctx(काष्ठा sbmac_softc *sc)
अणु
	sbdma_uninitctx(&(sc->sbm_txdma));
	sbdma_uninitctx(&(sc->sbm_rxdma));
पूर्ण


/**********************************************************************
 *  SBMAC_CHANNEL_START(s)
 *
 *  Start packet processing on this MAC.
 *
 *  Input parameters:
 *  	   s - sbmac काष्ठाure
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbmac_channel_start(काष्ठा sbmac_softc *s)
अणु
	uपूर्णांक64_t reg;
	व्योम __iomem *port;
	uपूर्णांक64_t cfg,fअगरo,framecfg;
	पूर्णांक idx, th_value;

	/*
	 * Don't करो this अगर running
	 */

	अगर (s->sbm_state == sbmac_state_on)
		वापस;

	/*
	 * Bring the controller out of reset, but leave it off.
	 */

	__raw_ग_लिखोq(0, s->sbm_macenable);

	/*
	 * Ignore all received packets
	 */

	__raw_ग_लिखोq(0, s->sbm_rxfilter);

	/*
	 * Calculate values क्रम various control रेजिस्टरs.
	 */

	cfg = M_MAC_RETRY_EN |
		M_MAC_TX_HOLD_SOP_EN |
		V_MAC_TX_PAUSE_CNT_16K |
		M_MAC_AP_STAT_EN |
		M_MAC_FAST_SYNC |
		M_MAC_SS_EN |
		0;

	/*
	 * Be sure that RD_THRSH+WR_THRSH <= 32 क्रम pass1 pars
	 * and make sure that RD_THRSH + WR_THRSH <=128 क्रम pass2 and above
	 * Use a larger RD_THRSH क्रम gigabit
	 */
	अगर (soc_type == K_SYS_SOC_TYPE_BCM1250 && periph_rev < 2)
		th_value = 28;
	अन्यथा
		th_value = 64;

	fअगरo = V_MAC_TX_WR_THRSH(4) |	/* Must be '4' or '8' */
		((s->sbm_speed == sbmac_speed_1000)
		 ? V_MAC_TX_RD_THRSH(th_value) : V_MAC_TX_RD_THRSH(4)) |
		V_MAC_TX_RL_THRSH(4) |
		V_MAC_RX_PL_THRSH(4) |
		V_MAC_RX_RD_THRSH(4) |	/* Must be '4' */
		V_MAC_RX_RL_THRSH(8) |
		0;

	framecfg = V_MAC_MIN_FRAMESZ_DEFAULT |
		V_MAC_MAX_FRAMESZ_DEFAULT |
		V_MAC_BACKOFF_SEL(1);

	/*
	 * Clear out the hash address map
	 */

	port = s->sbm_base + R_MAC_HASH_BASE;
	क्रम (idx = 0; idx < MAC_HASH_COUNT; idx++) अणु
		__raw_ग_लिखोq(0, port);
		port += माप(uपूर्णांक64_t);
	पूर्ण

	/*
	 * Clear out the exact-match table
	 */

	port = s->sbm_base + R_MAC_ADDR_BASE;
	क्रम (idx = 0; idx < MAC_ADDR_COUNT; idx++) अणु
		__raw_ग_लिखोq(0, port);
		port += माप(uपूर्णांक64_t);
	पूर्ण

	/*
	 * Clear out the DMA Channel mapping table रेजिस्टरs
	 */

	port = s->sbm_base + R_MAC_CHUP0_BASE;
	क्रम (idx = 0; idx < MAC_CHMAP_COUNT; idx++) अणु
		__raw_ग_लिखोq(0, port);
		port += माप(uपूर्णांक64_t);
	पूर्ण


	port = s->sbm_base + R_MAC_CHLO0_BASE;
	क्रम (idx = 0; idx < MAC_CHMAP_COUNT; idx++) अणु
		__raw_ग_लिखोq(0, port);
		port += माप(uपूर्णांक64_t);
	पूर्ण

	/*
	 * Program the hardware address.  It goes पूर्णांकo the hardware-address
	 * रेजिस्टर as well as the first filter रेजिस्टर.
	 */

	reg = sbmac_addr2reg(s->sbm_hwaddr);

	port = s->sbm_base + R_MAC_ADDR_BASE;
	__raw_ग_लिखोq(reg, port);
	port = s->sbm_base + R_MAC_ETHERNET_ADDR;

	__raw_ग_लिखोq(reg, port);

	/*
	 * Set the receive filter क्रम no packets, and ग_लिखो values
	 * to the various config रेजिस्टरs
	 */

	__raw_ग_लिखोq(0, s->sbm_rxfilter);
	__raw_ग_लिखोq(0, s->sbm_imr);
	__raw_ग_लिखोq(framecfg, s->sbm_framecfg);
	__raw_ग_लिखोq(fअगरo, s->sbm_fअगरocfg);
	__raw_ग_लिखोq(cfg, s->sbm_maccfg);

	/*
	 * Initialize DMA channels (rings should be ok now)
	 */

	sbdma_channel_start(&(s->sbm_rxdma), DMA_RX);
	sbdma_channel_start(&(s->sbm_txdma), DMA_TX);

	/*
	 * Configure the speed, duplex, and flow control
	 */

	sbmac_set_speed(s,s->sbm_speed);
	sbmac_set_duplex(s,s->sbm_duplex,s->sbm_fc);

	/*
	 * Fill the receive ring
	 */

	sbdma_fillring(s, &(s->sbm_rxdma));

	/*
	 * Turn on the rest of the bits in the enable रेजिस्टर
	 */

#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
	__raw_ग_लिखोq(M_MAC_RXDMA_EN0 |
		       M_MAC_TXDMA_EN0, s->sbm_macenable);
#या_अगर defined(CONFIG_SIBYTE_SB1250) || defined(CONFIG_SIBYTE_BCM112X)
	__raw_ग_लिखोq(M_MAC_RXDMA_EN0 |
		       M_MAC_TXDMA_EN0 |
		       M_MAC_RX_ENABLE |
		       M_MAC_TX_ENABLE, s->sbm_macenable);
#अन्यथा
#त्रुटि invalid SiByte MAC configuration
#पूर्ण_अगर

#अगर_घोषित CONFIG_SBMAC_COALESCE
	__raw_ग_लिखोq(((M_MAC_INT_EOP_COUNT | M_MAC_INT_EOP_TIMER) << S_MAC_TX_CH0) |
		       ((M_MAC_INT_EOP_COUNT | M_MAC_INT_EOP_TIMER) << S_MAC_RX_CH0), s->sbm_imr);
#अन्यथा
	__raw_ग_लिखोq((M_MAC_INT_CHANNEL << S_MAC_TX_CH0) |
		       (M_MAC_INT_CHANNEL << S_MAC_RX_CH0), s->sbm_imr);
#पूर्ण_अगर

	/*
	 * Enable receiving unicasts and broadcasts
	 */

	__raw_ग_लिखोq(M_MAC_UCAST_EN | M_MAC_BCAST_EN, s->sbm_rxfilter);

	/*
	 * we're running now.
	 */

	s->sbm_state = sbmac_state_on;

	/*
	 * Program multicast addresses
	 */

	sbmac_seपंचांगulti(s);

	/*
	 * If channel was in promiscuous mode beक्रमe, turn that on
	 */

	अगर (s->sbm_devflags & IFF_PROMISC) अणु
		sbmac_promiscuous_mode(s,1);
	पूर्ण

पूर्ण


/**********************************************************************
 *  SBMAC_CHANNEL_STOP(s)
 *
 *  Stop packet processing on this MAC.
 *
 *  Input parameters:
 *  	   s - sbmac काष्ठाure
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbmac_channel_stop(काष्ठा sbmac_softc *s)
अणु
	/* करोn't करो this अगर alपढ़ोy stopped */

	अगर (s->sbm_state == sbmac_state_off)
		वापस;

	/* करोn't accept any packets, disable all पूर्णांकerrupts */

	__raw_ग_लिखोq(0, s->sbm_rxfilter);
	__raw_ग_लिखोq(0, s->sbm_imr);

	/* Turn off ticker */

	/* XXX */

	/* turn off receiver and transmitter */

	__raw_ग_लिखोq(0, s->sbm_macenable);

	/* We're stopped now. */

	s->sbm_state = sbmac_state_off;

	/*
	 * Stop DMA channels (rings should be ok now)
	 */

	sbdma_channel_stop(&(s->sbm_rxdma));
	sbdma_channel_stop(&(s->sbm_txdma));

	/* Empty the receive and transmit rings */

	sbdma_emptyring(&(s->sbm_rxdma));
	sbdma_emptyring(&(s->sbm_txdma));

पूर्ण

/**********************************************************************
 *  SBMAC_SET_CHANNEL_STATE(state)
 *
 *  Set the channel's state ON or OFF
 *
 *  Input parameters:
 *  	   state - new state
 *
 *  Return value:
 *  	   old state
 ********************************************************************* */
अटल क्रमागत sbmac_state sbmac_set_channel_state(काष्ठा sbmac_softc *sc,
						क्रमागत sbmac_state state)
अणु
	क्रमागत sbmac_state oldstate = sc->sbm_state;

	/*
	 * If same as previous state, वापस
	 */

	अगर (state == oldstate) अणु
		वापस oldstate;
	पूर्ण

	/*
	 * If new state is ON, turn channel on
	 */

	अगर (state == sbmac_state_on) अणु
		sbmac_channel_start(sc);
	पूर्ण
	अन्यथा अणु
		sbmac_channel_stop(sc);
	पूर्ण

	/*
	 * Return previous state
	 */

	वापस oldstate;
पूर्ण


/**********************************************************************
 *  SBMAC_PROMISCUOUS_MODE(sc,onoff)
 *
 *  Turn on or off promiscuous mode
 *
 *  Input parameters:
 *  	   sc - softc
 *      onoff - 1 to turn on, 0 to turn off
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbmac_promiscuous_mode(काष्ठा sbmac_softc *sc,पूर्णांक onoff)
अणु
	uपूर्णांक64_t reg;

	अगर (sc->sbm_state != sbmac_state_on)
		वापस;

	अगर (onoff) अणु
		reg = __raw_पढ़ोq(sc->sbm_rxfilter);
		reg |= M_MAC_ALLPKT_EN;
		__raw_ग_लिखोq(reg, sc->sbm_rxfilter);
	पूर्ण
	अन्यथा अणु
		reg = __raw_पढ़ोq(sc->sbm_rxfilter);
		reg &= ~M_MAC_ALLPKT_EN;
		__raw_ग_लिखोq(reg, sc->sbm_rxfilter);
	पूर्ण
पूर्ण

/**********************************************************************
 *  SBMAC_SETIPHDR_OFFSET(sc,onoff)
 *
 *  Set the iphdr offset as 15 assuming ethernet encapsulation
 *
 *  Input parameters:
 *  	   sc - softc
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbmac_set_iphdr_offset(काष्ठा sbmac_softc *sc)
अणु
	uपूर्णांक64_t reg;

	/* Hard code the off set to 15 क्रम now */
	reg = __raw_पढ़ोq(sc->sbm_rxfilter);
	reg &= ~M_MAC_IPHDR_OFFSET | V_MAC_IPHDR_OFFSET(15);
	__raw_ग_लिखोq(reg, sc->sbm_rxfilter);

	/* BCM1250 pass1 didn't have hardware checksum.  Everything
	   later करोes.  */
	अगर (soc_type == K_SYS_SOC_TYPE_BCM1250 && periph_rev < 2) अणु
		sc->rx_hw_checksum = DISABLE;
	पूर्ण अन्यथा अणु
		sc->rx_hw_checksum = ENABLE;
	पूर्ण
पूर्ण


/**********************************************************************
 *  SBMAC_ADDR2REG(ptr)
 *
 *  Convert six bytes पूर्णांकo the 64-bit रेजिस्टर value that
 *  we typically ग_लिखो पूर्णांकo the SBMAC's address/mcast रेजिस्टरs
 *
 *  Input parameters:
 *  	   ptr - poपूर्णांकer to 6 bytes
 *
 *  Return value:
 *  	   रेजिस्टर value
 ********************************************************************* */

अटल uपूर्णांक64_t sbmac_addr2reg(अचिन्हित अक्षर *ptr)
अणु
	uपूर्णांक64_t reg = 0;

	ptr += 6;

	reg |= (uपूर्णांक64_t) *(--ptr);
	reg <<= 8;
	reg |= (uपूर्णांक64_t) *(--ptr);
	reg <<= 8;
	reg |= (uपूर्णांक64_t) *(--ptr);
	reg <<= 8;
	reg |= (uपूर्णांक64_t) *(--ptr);
	reg <<= 8;
	reg |= (uपूर्णांक64_t) *(--ptr);
	reg <<= 8;
	reg |= (uपूर्णांक64_t) *(--ptr);

	वापस reg;
पूर्ण


/**********************************************************************
 *  SBMAC_SET_SPEED(s,speed)
 *
 *  Configure LAN speed क्रम the specअगरied MAC.
 *  Warning: must be called when MAC is off!
 *
 *  Input parameters:
 *  	   s - sbmac काष्ठाure
 *  	   speed - speed to set MAC to (see क्रमागत sbmac_speed)
 *
 *  Return value:
 *  	   1 अगर successful
 *      0 indicates invalid parameters
 ********************************************************************* */

अटल पूर्णांक sbmac_set_speed(काष्ठा sbmac_softc *s, क्रमागत sbmac_speed speed)
अणु
	uपूर्णांक64_t cfg;
	uपूर्णांक64_t framecfg;

	/*
	 * Save new current values
	 */

	s->sbm_speed = speed;

	अगर (s->sbm_state == sbmac_state_on)
		वापस 0;	/* save क्रम next restart */

	/*
	 * Read current रेजिस्टर values
	 */

	cfg = __raw_पढ़ोq(s->sbm_maccfg);
	framecfg = __raw_पढ़ोq(s->sbm_framecfg);

	/*
	 * Mask out the stuff we want to change
	 */

	cfg &= ~(M_MAC_BURST_EN | M_MAC_SPEED_SEL);
	framecfg &= ~(M_MAC_IFG_RX | M_MAC_IFG_TX | M_MAC_IFG_THRSH |
		      M_MAC_SLOT_SIZE);

	/*
	 * Now add in the new bits
	 */

	चयन (speed) अणु
	हाल sbmac_speed_10:
		framecfg |= V_MAC_IFG_RX_10 |
			V_MAC_IFG_TX_10 |
			K_MAC_IFG_THRSH_10 |
			V_MAC_SLOT_SIZE_10;
		cfg |= V_MAC_SPEED_SEL_10MBPS;
		अवरोध;

	हाल sbmac_speed_100:
		framecfg |= V_MAC_IFG_RX_100 |
			V_MAC_IFG_TX_100 |
			V_MAC_IFG_THRSH_100 |
			V_MAC_SLOT_SIZE_100;
		cfg |= V_MAC_SPEED_SEL_100MBPS ;
		अवरोध;

	हाल sbmac_speed_1000:
		framecfg |= V_MAC_IFG_RX_1000 |
			V_MAC_IFG_TX_1000 |
			V_MAC_IFG_THRSH_1000 |
			V_MAC_SLOT_SIZE_1000;
		cfg |= V_MAC_SPEED_SEL_1000MBPS | M_MAC_BURST_EN;
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	/*
	 * Send the bits back to the hardware
	 */

	__raw_ग_लिखोq(framecfg, s->sbm_framecfg);
	__raw_ग_लिखोq(cfg, s->sbm_maccfg);

	वापस 1;
पूर्ण

/**********************************************************************
 *  SBMAC_SET_DUPLEX(s,duplex,fc)
 *
 *  Set Ethernet duplex and flow control options क्रम this MAC
 *  Warning: must be called when MAC is off!
 *
 *  Input parameters:
 *  	   s - sbmac काष्ठाure
 *  	   duplex - duplex setting (see क्रमागत sbmac_duplex)
 *  	   fc - flow control setting (see क्रमागत sbmac_fc)
 *
 *  Return value:
 *  	   1 अगर ok
 *  	   0 अगर an invalid parameter combination was specअगरied
 ********************************************************************* */

अटल पूर्णांक sbmac_set_duplex(काष्ठा sbmac_softc *s, क्रमागत sbmac_duplex duplex,
			    क्रमागत sbmac_fc fc)
अणु
	uपूर्णांक64_t cfg;

	/*
	 * Save new current values
	 */

	s->sbm_duplex = duplex;
	s->sbm_fc = fc;

	अगर (s->sbm_state == sbmac_state_on)
		वापस 0;	/* save क्रम next restart */

	/*
	 * Read current रेजिस्टर values
	 */

	cfg = __raw_पढ़ोq(s->sbm_maccfg);

	/*
	 * Mask off the stuff we're about to change
	 */

	cfg &= ~(M_MAC_FC_SEL | M_MAC_FC_CMD | M_MAC_HDX_EN);


	चयन (duplex) अणु
	हाल sbmac_duplex_half:
		चयन (fc) अणु
		हाल sbmac_fc_disabled:
			cfg |= M_MAC_HDX_EN | V_MAC_FC_CMD_DISABLED;
			अवरोध;

		हाल sbmac_fc_collision:
			cfg |= M_MAC_HDX_EN | V_MAC_FC_CMD_ENABLED;
			अवरोध;

		हाल sbmac_fc_carrier:
			cfg |= M_MAC_HDX_EN | V_MAC_FC_CMD_ENAB_FALSECARR;
			अवरोध;

		हाल sbmac_fc_frame:		/* not valid in half duplex */
		शेष:			/* invalid selection */
			वापस 0;
		पूर्ण
		अवरोध;

	हाल sbmac_duplex_full:
		चयन (fc) अणु
		हाल sbmac_fc_disabled:
			cfg |= V_MAC_FC_CMD_DISABLED;
			अवरोध;

		हाल sbmac_fc_frame:
			cfg |= V_MAC_FC_CMD_ENABLED;
			अवरोध;

		हाल sbmac_fc_collision:	/* not valid in full duplex */
		हाल sbmac_fc_carrier:		/* not valid in full duplex */
		शेष:
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	/*
	 * Send the bits back to the hardware
	 */

	__raw_ग_लिखोq(cfg, s->sbm_maccfg);

	वापस 1;
पूर्ण




/**********************************************************************
 *  SBMAC_INTR()
 *
 *  Interrupt handler क्रम MAC पूर्णांकerrupts
 *
 *  Input parameters:
 *  	   MAC काष्ठाure
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */
अटल irqवापस_t sbmac_पूर्णांकr(पूर्णांक irq,व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_instance;
	काष्ठा sbmac_softc *sc = netdev_priv(dev);
	uपूर्णांक64_t isr;
	पूर्णांक handled = 0;

	/*
	 * Read the ISR (this clears the bits in the real
	 * रेजिस्टर, except क्रम counter addr)
	 */

	isr = __raw_पढ़ोq(sc->sbm_isr) & ~M_MAC_COUNTER_ADDR;

	अगर (isr == 0)
		वापस IRQ_RETVAL(0);
	handled = 1;

	/*
	 * Transmits on channel 0
	 */

	अगर (isr & (M_MAC_INT_CHANNEL << S_MAC_TX_CH0))
		sbdma_tx_process(sc,&(sc->sbm_txdma), 0);

	अगर (isr & (M_MAC_INT_CHANNEL << S_MAC_RX_CH0)) अणु
		अगर (napi_schedule_prep(&sc->napi)) अणु
			__raw_ग_लिखोq(0, sc->sbm_imr);
			__napi_schedule(&sc->napi);
			/* Depend on the निकास from poll to reenable पूर्णांकr */
		पूर्ण
		अन्यथा अणु
			/* may leave some packets behind */
			sbdma_rx_process(sc,&(sc->sbm_rxdma),
					 SBMAC_MAX_RXDESCR * 2, 0);
		पूर्ण
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण

/**********************************************************************
 *  SBMAC_START_TX(skb,dev)
 *
 *  Start output on the specअगरied पूर्णांकerface.  Basically, we
 *  queue as many buffers as we can until the ring fills up, or
 *  we run off the end of the queue, whichever comes first.
 *
 *  Input parameters:
 *
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */
अटल netdev_tx_t sbmac_start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा sbmac_softc *sc = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	/* lock eth irq */
	spin_lock_irqsave(&sc->sbm_lock, flags);

	/*
	 * Put the buffer on the transmit ring.  If we
	 * करोn't have room, stop the queue.
	 */

	अगर (sbdma_add_txbuffer(&(sc->sbm_txdma),skb)) अणु
		/* XXX save skb that we could not send */
		netअगर_stop_queue(dev);
		spin_unlock_irqrestore(&sc->sbm_lock, flags);

		वापस NETDEV_TX_BUSY;
	पूर्ण

	spin_unlock_irqrestore(&sc->sbm_lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

/**********************************************************************
 *  SBMAC_SETMULTI(sc)
 *
 *  Reprogram the multicast table पूर्णांकo the hardware, given
 *  the list of multicasts associated with the पूर्णांकerface
 *  काष्ठाure.
 *
 *  Input parameters:
 *  	   sc - softc
 *
 *  Return value:
 *  	   nothing
 ********************************************************************* */

अटल व्योम sbmac_seपंचांगulti(काष्ठा sbmac_softc *sc)
अणु
	uपूर्णांक64_t reg;
	व्योम __iomem *port;
	पूर्णांक idx;
	काष्ठा netdev_hw_addr *ha;
	काष्ठा net_device *dev = sc->sbm_dev;

	/*
	 * Clear out entire multicast table.  We करो this by nuking
	 * the entire hash table and all the direct matches except
	 * the first one, which is used क्रम our station address
	 */

	क्रम (idx = 1; idx < MAC_ADDR_COUNT; idx++) अणु
		port = sc->sbm_base + R_MAC_ADDR_BASE+(idx*माप(uपूर्णांक64_t));
		__raw_ग_लिखोq(0, port);
	पूर्ण

	क्रम (idx = 0; idx < MAC_HASH_COUNT; idx++) अणु
		port = sc->sbm_base + R_MAC_HASH_BASE+(idx*माप(uपूर्णांक64_t));
		__raw_ग_लिखोq(0, port);
	पूर्ण

	/*
	 * Clear the filter to say we करोn't want any multicasts.
	 */

	reg = __raw_पढ़ोq(sc->sbm_rxfilter);
	reg &= ~(M_MAC_MCAST_INV | M_MAC_MCAST_EN);
	__raw_ग_लिखोq(reg, sc->sbm_rxfilter);

	अगर (dev->flags & IFF_ALLMULTI) अणु
		/*
		 * Enable ALL multicasts.  Do this by inverting the
		 * multicast enable bit.
		 */
		reg = __raw_पढ़ोq(sc->sbm_rxfilter);
		reg |= (M_MAC_MCAST_INV | M_MAC_MCAST_EN);
		__raw_ग_लिखोq(reg, sc->sbm_rxfilter);
		वापस;
	पूर्ण


	/*
	 * Progam new multicast entries.  For now, only use the
	 * perfect filter.  In the future we'll need to use the
	 * hash filter अगर the perfect filter overflows
	 */

	/* XXX only using perfect filter क्रम now, need to use hash
	 * XXX अगर the table overflows */

	idx = 1;		/* skip station address */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		अगर (idx == MAC_ADDR_COUNT)
			अवरोध;
		reg = sbmac_addr2reg(ha->addr);
		port = sc->sbm_base + R_MAC_ADDR_BASE+(idx * माप(uपूर्णांक64_t));
		__raw_ग_लिखोq(reg, port);
		idx++;
	पूर्ण

	/*
	 * Enable the "accept multicast bits" अगर we programmed at least one
	 * multicast.
	 */

	अगर (idx > 1) अणु
		reg = __raw_पढ़ोq(sc->sbm_rxfilter);
		reg |= M_MAC_MCAST_EN;
		__raw_ग_लिखोq(reg, sc->sbm_rxfilter);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops sbmac_netdev_ops = अणु
	.nकरो_खोलो		= sbmac_खोलो,
	.nकरो_stop		= sbmac_बंद,
	.nकरो_start_xmit		= sbmac_start_tx,
	.nकरो_set_rx_mode	= sbmac_set_rx_mode,
	.nकरो_tx_समयout		= sbmac_tx_समयout,
	.nकरो_करो_ioctl		= sbmac_mii_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= sbmac_netpoll,
#पूर्ण_अगर
पूर्ण;

/**********************************************************************
 *  SBMAC_INIT(dev)
 *
 *  Attach routine - init hardware and hook ourselves पूर्णांकo linux
 *
 *  Input parameters:
 *  	   dev - net_device काष्ठाure
 *
 *  Return value:
 *  	   status
 ********************************************************************* */

अटल पूर्णांक sbmac_init(काष्ठा platक्रमm_device *pldev, दीर्घ दीर्घ base)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pldev);
	पूर्णांक idx = pldev->id;
	काष्ठा sbmac_softc *sc = netdev_priv(dev);
	अचिन्हित अक्षर *eaddr;
	uपूर्णांक64_t ea_reg;
	पूर्णांक i;
	पूर्णांक err;

	sc->sbm_dev = dev;
	sc->sbe_idx = idx;

	eaddr = sc->sbm_hwaddr;

	/*
	 * Read the ethernet address.  The firmware left this programmed
	 * क्रम us in the ethernet address रेजिस्टर क्रम each mac.
	 */

	ea_reg = __raw_पढ़ोq(sc->sbm_base + R_MAC_ETHERNET_ADDR);
	__raw_ग_लिखोq(0, sc->sbm_base + R_MAC_ETHERNET_ADDR);
	क्रम (i = 0; i < 6; i++) अणु
		eaddr[i] = (uपूर्णांक8_t) (ea_reg & 0xFF);
		ea_reg >>= 8;
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		dev->dev_addr[i] = eaddr[i];
	पूर्ण

	/*
	 * Initialize context (get poपूर्णांकers to रेजिस्टरs and stuff), then
	 * allocate the memory क्रम the descriptor tables.
	 */

	sbmac_initctx(sc);

	/*
	 * Set up Linux device callins
	 */

	spin_lock_init(&(sc->sbm_lock));

	dev->netdev_ops = &sbmac_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	dev->min_mtu = 0;
	dev->max_mtu = ENET_PACKET_SIZE;

	netअगर_napi_add(dev, &sc->napi, sbmac_poll, 16);

	dev->irq		= UNIT_INT(idx);

	/* This is needed क्रम PASS2 क्रम Rx H/W checksum feature */
	sbmac_set_iphdr_offset(sc);

	sc->mii_bus = mdiobus_alloc();
	अगर (sc->mii_bus == शून्य) अणु
		err = -ENOMEM;
		जाओ uninit_ctx;
	पूर्ण

	sc->mii_bus->name = sbmac_mdio_string;
	snम_लिखो(sc->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		pldev->name, idx);
	sc->mii_bus->priv = sc;
	sc->mii_bus->पढ़ो = sbmac_mii_पढ़ो;
	sc->mii_bus->ग_लिखो = sbmac_mii_ग_लिखो;

	sc->mii_bus->parent = &pldev->dev;
	/*
	 * Probe PHY address
	 */
	err = mdiobus_रेजिस्टर(sc->mii_bus);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to register MDIO bus\n",
		       dev->name);
		जाओ मुक्त_mdio;
	पूर्ण
	platक्रमm_set_drvdata(pldev, sc->mii_bus);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s.%d: unable to register netdev\n",
		       sbmac_string, idx);
		जाओ unreg_mdio;
	पूर्ण

	pr_info("%s.%d: registered as %s\n", sbmac_string, idx, dev->name);

	अगर (sc->rx_hw_checksum == ENABLE)
		pr_info("%s: enabling TCP rcv checksum\n", dev->name);

	/*
	 * Display Ethernet address (this is called during the config
	 * process so we need to finish off the config message that
	 * was being displayed)
	 */
	pr_info("%s: SiByte Ethernet at 0x%08Lx, address: %pM\n",
	       dev->name, base, eaddr);

	वापस 0;
unreg_mdio:
	mdiobus_unरेजिस्टर(sc->mii_bus);
मुक्त_mdio:
	mdiobus_मुक्त(sc->mii_bus);
uninit_ctx:
	sbmac_uninitctx(sc);
	वापस err;
पूर्ण


अटल पूर्णांक sbmac_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा sbmac_softc *sc = netdev_priv(dev);
	पूर्णांक err;

	अगर (debug > 1)
		pr_debug("%s: sbmac_open() irq %d.\n", dev->name, dev->irq);

	/*
	 * map/route पूर्णांकerrupt (clear status first, in हाल something
	 * weird is pending; we haven't initialized the mac रेजिस्टरs
	 * yet)
	 */

	__raw_पढ़ोq(sc->sbm_isr);
	err = request_irq(dev->irq, sbmac_पूर्णांकr, IRQF_SHARED, dev->name, dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to get IRQ %d\n", dev->name,
		       dev->irq);
		जाओ out_err;
	पूर्ण

	sc->sbm_speed = sbmac_speed_none;
	sc->sbm_duplex = sbmac_duplex_none;
	sc->sbm_fc = sbmac_fc_none;
	sc->sbm_छोड़ो = -1;
	sc->sbm_link = 0;

	/*
	 * Attach to the PHY
	 */
	err = sbmac_mii_probe(dev);
	अगर (err)
		जाओ out_unरेजिस्टर;

	/*
	 * Turn on the channel
	 */

	sbmac_set_channel_state(sc,sbmac_state_on);

	netअगर_start_queue(dev);

	sbmac_set_rx_mode(dev);

	phy_start(sc->phy_dev);

	napi_enable(&sc->napi);

	वापस 0;

out_unरेजिस्टर:
	मुक्त_irq(dev->irq, dev);
out_err:
	वापस err;
पूर्ण

अटल पूर्णांक sbmac_mii_probe(काष्ठा net_device *dev)
अणु
	काष्ठा sbmac_softc *sc = netdev_priv(dev);
	काष्ठा phy_device *phy_dev;

	phy_dev = phy_find_first(sc->mii_bus);
	अगर (!phy_dev) अणु
		prपूर्णांकk(KERN_ERR "%s: no PHY found\n", dev->name);
		वापस -ENXIO;
	पूर्ण

	phy_dev = phy_connect(dev, dev_name(&phy_dev->mdio.dev),
			      &sbmac_mii_poll, PHY_INTERFACE_MODE_GMII);
	अगर (IS_ERR(phy_dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: could not attach to PHY\n", dev->name);
		वापस PTR_ERR(phy_dev);
	पूर्ण

	/* Remove any features not supported by the controller */
	phy_set_max_speed(phy_dev, SPEED_1000);
	phy_support_asym_छोड़ो(phy_dev);

	phy_attached_info(phy_dev);

	sc->phy_dev = phy_dev;

	वापस 0;
पूर्ण


अटल व्योम sbmac_mii_poll(काष्ठा net_device *dev)
अणु
	काष्ठा sbmac_softc *sc = netdev_priv(dev);
	काष्ठा phy_device *phy_dev = sc->phy_dev;
	अचिन्हित दीर्घ flags;
	क्रमागत sbmac_fc fc;
	पूर्णांक link_chg, speed_chg, duplex_chg, छोड़ो_chg, fc_chg;

	link_chg = (sc->sbm_link != phy_dev->link);
	speed_chg = (sc->sbm_speed != phy_dev->speed);
	duplex_chg = (sc->sbm_duplex != phy_dev->duplex);
	छोड़ो_chg = (sc->sbm_छोड़ो != phy_dev->छोड़ो);

	अगर (!link_chg && !speed_chg && !duplex_chg && !छोड़ो_chg)
		वापस;					/* Hmmm... */

	अगर (!phy_dev->link) अणु
		अगर (link_chg) अणु
			sc->sbm_link = phy_dev->link;
			sc->sbm_speed = sbmac_speed_none;
			sc->sbm_duplex = sbmac_duplex_none;
			sc->sbm_fc = sbmac_fc_disabled;
			sc->sbm_छोड़ो = -1;
			pr_info("%s: link unavailable\n", dev->name);
		पूर्ण
		वापस;
	पूर्ण

	अगर (phy_dev->duplex == DUPLEX_FULL) अणु
		अगर (phy_dev->छोड़ो)
			fc = sbmac_fc_frame;
		अन्यथा
			fc = sbmac_fc_disabled;
	पूर्ण अन्यथा
		fc = sbmac_fc_collision;
	fc_chg = (sc->sbm_fc != fc);

	pr_info("%s: link available: %dbase-%cD\n", dev->name, phy_dev->speed,
		phy_dev->duplex == DUPLEX_FULL ? 'F' : 'H');

	spin_lock_irqsave(&sc->sbm_lock, flags);

	sc->sbm_speed = phy_dev->speed;
	sc->sbm_duplex = phy_dev->duplex;
	sc->sbm_fc = fc;
	sc->sbm_छोड़ो = phy_dev->छोड़ो;
	sc->sbm_link = phy_dev->link;

	अगर ((speed_chg || duplex_chg || fc_chg) &&
	    sc->sbm_state != sbmac_state_off) अणु
		/*
		 * something changed, restart the channel
		 */
		अगर (debug > 1)
			pr_debug("%s: restarting channel "
				 "because PHY state changed\n", dev->name);
		sbmac_channel_stop(sc);
		sbmac_channel_start(sc);
	पूर्ण

	spin_unlock_irqrestore(&sc->sbm_lock, flags);
पूर्ण


अटल व्योम sbmac_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा sbmac_softc *sc = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sc->sbm_lock, flags);


	netअगर_trans_update(dev); /* prevent tx समयout */
	dev->stats.tx_errors++;

	spin_unlock_irqrestore(&sc->sbm_lock, flags);

	prपूर्णांकk (KERN_WARNING "%s: Transmit timed out\n",dev->name);
पूर्ण




अटल व्योम sbmac_set_rx_mode(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sbmac_softc *sc = netdev_priv(dev);

	spin_lock_irqsave(&sc->sbm_lock, flags);
	अगर ((dev->flags ^ sc->sbm_devflags) & IFF_PROMISC) अणु
		/*
		 * Promiscuous changed.
		 */

		अगर (dev->flags & IFF_PROMISC) अणु
			sbmac_promiscuous_mode(sc,1);
		पूर्ण
		अन्यथा अणु
			sbmac_promiscuous_mode(sc,0);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&sc->sbm_lock, flags);

	/*
	 * Program the multicasts.  Do this every समय.
	 */

	sbmac_seपंचांगulti(sc);

पूर्ण

अटल पूर्णांक sbmac_mii_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा sbmac_softc *sc = netdev_priv(dev);

	अगर (!netअगर_running(dev) || !sc->phy_dev)
		वापस -EINVAL;

	वापस phy_mii_ioctl(sc->phy_dev, rq, cmd);
पूर्ण

अटल पूर्णांक sbmac_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा sbmac_softc *sc = netdev_priv(dev);

	napi_disable(&sc->napi);

	phy_stop(sc->phy_dev);

	sbmac_set_channel_state(sc, sbmac_state_off);

	netअगर_stop_queue(dev);

	अगर (debug > 1)
		pr_debug("%s: Shutting down ethercard\n", dev->name);

	phy_disconnect(sc->phy_dev);
	sc->phy_dev = शून्य;
	मुक्त_irq(dev->irq, dev);

	sbdma_emptyring(&(sc->sbm_txdma));
	sbdma_emptyring(&(sc->sbm_rxdma));

	वापस 0;
पूर्ण

अटल पूर्णांक sbmac_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा sbmac_softc *sc = container_of(napi, काष्ठा sbmac_softc, napi);
	पूर्णांक work_करोne;

	work_करोne = sbdma_rx_process(sc, &(sc->sbm_rxdma), budget, 1);
	sbdma_tx_process(sc, &(sc->sbm_txdma), 1);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);

#अगर_घोषित CONFIG_SBMAC_COALESCE
		__raw_ग_लिखोq(((M_MAC_INT_EOP_COUNT | M_MAC_INT_EOP_TIMER) << S_MAC_TX_CH0) |
			     ((M_MAC_INT_EOP_COUNT | M_MAC_INT_EOP_TIMER) << S_MAC_RX_CH0),
			     sc->sbm_imr);
#अन्यथा
		__raw_ग_लिखोq((M_MAC_INT_CHANNEL << S_MAC_TX_CH0) |
			     (M_MAC_INT_CHANNEL << S_MAC_RX_CH0), sc->sbm_imr);
#पूर्ण_अगर
	पूर्ण

	वापस work_करोne;
पूर्ण


अटल पूर्णांक sbmac_probe(काष्ठा platक्रमm_device *pldev)
अणु
	काष्ठा net_device *dev;
	काष्ठा sbmac_softc *sc;
	व्योम __iomem *sbm_base;
	काष्ठा resource *res;
	u64 sbmac_orig_hwaddr;
	पूर्णांक err;

	res = platक्रमm_get_resource(pldev, IORESOURCE_MEM, 0);
	BUG_ON(!res);
	sbm_base = ioremap(res->start, resource_size(res));
	अगर (!sbm_base) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to map device registers\n",
		       dev_name(&pldev->dev));
		err = -ENOMEM;
		जाओ out_out;
	पूर्ण

	/*
	 * The R_MAC_ETHERNET_ADDR रेजिस्टर will be set to some nonzero
	 * value क्रम us by the firmware अगर we're going to use this MAC.
	 * If we find a zero, skip this MAC.
	 */
	sbmac_orig_hwaddr = __raw_पढ़ोq(sbm_base + R_MAC_ETHERNET_ADDR);
	pr_debug("%s: %sconfiguring MAC at 0x%08Lx\n", dev_name(&pldev->dev),
		 sbmac_orig_hwaddr ? "" : "not ", (दीर्घ दीर्घ)res->start);
	अगर (sbmac_orig_hwaddr == 0) अणु
		err = 0;
		जाओ out_unmap;
	पूर्ण

	/*
	 * Okay, cool.  Initialize this MAC.
	 */
	dev = alloc_etherdev(माप(काष्ठा sbmac_softc));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	platक्रमm_set_drvdata(pldev, dev);
	SET_NETDEV_DEV(dev, &pldev->dev);

	sc = netdev_priv(dev);
	sc->sbm_base = sbm_base;

	err = sbmac_init(pldev, res->start);
	अगर (err)
		जाओ out_kमुक्त;

	वापस 0;

out_kमुक्त:
	मुक्त_netdev(dev);
	__raw_ग_लिखोq(sbmac_orig_hwaddr, sbm_base + R_MAC_ETHERNET_ADDR);

out_unmap:
	iounmap(sbm_base);

out_out:
	वापस err;
पूर्ण

अटल पूर्णांक sbmac_हटाओ(काष्ठा platक्रमm_device *pldev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pldev);
	काष्ठा sbmac_softc *sc = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	sbmac_uninitctx(sc);
	mdiobus_unरेजिस्टर(sc->mii_bus);
	mdiobus_मुक्त(sc->mii_bus);
	iounmap(sc->sbm_base);
	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sbmac_driver = अणु
	.probe = sbmac_probe,
	.हटाओ = sbmac_हटाओ,
	.driver = अणु
		.name = sbmac_string,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sbmac_driver);
MODULE_LICENSE("GPL");
