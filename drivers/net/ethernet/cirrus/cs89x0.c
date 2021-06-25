<शैली गुरु>
/* cs89x0.c: A Crystal Semiconductor (Now Cirrus Logic) CS89[02]0
 *           driver क्रम linux.
 * Written 1996 by Russell Nelson, with reference to skeleton.c
 * written 1993-1994 by Donald Becker.
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 * The author may be reached at nelson@crynwr.com, Crynwr
 * Software, 521 Pleasant Valley Rd., Potsdam, NY 13676
 *
 * Other contributors:
 * Mike Cruse        : mcruse@cti-ltd.com
 * Russ Nelson
 * Melody Lee        : ethernet@crystal.cirrus.com
 * Alan Cox
 * Andrew Morton
 * Oskar Schirmer    : oskar@scara.com
 * Deepak Saxena     : dsaxena@plनिकासy.net
 * Dmitry Pervushin  : dpervushin@ru.mvista.com
 * Deepak Saxena     : dsaxena@plनिकासy.net
 * Domenico Andreoli : cavokz@gmail.com
 */


/*
 * Set this to zero to disable DMA code
 *
 * Note that even अगर DMA is turned off we still support the 'dma' and  'use_dma'
 * module options so we करोn't अवरोध any startup scripts.
 */
#अगर_अघोषित CONFIG_ISA_DMA_API
#घोषणा ALLOW_DMA	0
#अन्यथा
#घोषणा ALLOW_DMA	1
#पूर्ण_अगर

/*
 * Set this to zero to हटाओ all the debug statements via
 * dead code elimination
 */
#घोषणा DEBUGGING	1

/* Sources:
 *	Crynwr packet driver epktisa.
 *	Crystal Semiconductor data sheets.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>
#समावेश <linux/atomic.h>
#अगर ALLOW_DMA
#समावेश <यंत्र/dma.h>
#पूर्ण_अगर

#समावेश "cs89x0.h"

#घोषणा cs89_dbg(val, level, fmt, ...)				\
करो अणु								\
	अगर (val <= net_debug)					\
		pr_##level(fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

अटल अक्षर version[] __initdata =
	"v2.4.3-pre1 Russell Nelson <nelson@crynwr.com>, Andrew Morton";

#घोषणा DRV_NAME "cs89x0"

/* First, a few definitions that the brave might change.
 * A zero-terminated list of I/O addresses to be probed. Some special flags..
 * Addr & 1 = Read back the address port, look क्रम signature and reset
 * the page winकरोw beक्रमe probing
 * Addr & 3 = Reset the page winकरोw and probe
 * The CLPS eval board has the Cirrus chip at 0x80090300, in ARM IO space,
 * but it is possible that a Cirrus board could be plugged पूर्णांकo the ISA
 * slots.
 */
/* The cs8900 has 4 IRQ pins, software selectable. cs8900_irq_map maps
 * them to प्रणाली IRQ numbers. This mapping is card specअगरic and is set to
 * the configuration of the Cirrus Eval board क्रम this chip.
 */
#अगर_अघोषित CONFIG_CS89x0_PLATFORM
अटल अचिन्हित पूर्णांक netcard_portlist[] __used __initdata = अणु
	0x300, 0x320, 0x340, 0x360, 0x200, 0x220, 0x240,
	0x260, 0x280, 0x2a0, 0x2c0, 0x2e0, 0
पूर्ण;
अटल अचिन्हित पूर्णांक cs8900_irq_map[] = अणु
	10, 11, 12, 5
पूर्ण;
#पूर्ण_अगर

#अगर DEBUGGING
अटल अचिन्हित पूर्णांक net_debug = DEBUGGING;
#अन्यथा
#घोषणा net_debug 0	/* gcc will हटाओ all the debug code क्रम us */
#पूर्ण_अगर

/* The number of low I/O ports used by the ethercard. */
#घोषणा NETCARD_IO_EXTENT	16

/* we allow the user to override various values normally set in the EEPROM */
#घोषणा FORCE_RJ45	0x0001    /* pick one of these three */
#घोषणा FORCE_AUI	0x0002
#घोषणा FORCE_BNC	0x0004

#घोषणा FORCE_AUTO	0x0010    /* pick one of these three */
#घोषणा FORCE_HALF	0x0020
#घोषणा FORCE_FULL	0x0030

/* Inक्रमmation that need to be kept क्रम each board. */
काष्ठा net_local अणु
	पूर्णांक chip_type;		/* one of: CS8900, CS8920, CS8920M */
	अक्षर chip_revision;	/* revision letter of the chip ('A'...) */
	पूर्णांक send_cmd;		/* the proper send command: TX_NOW, TX_AFTER_381, or TX_AFTER_ALL */
	पूर्णांक स्वतः_neg_cnf;	/* स्वतः-negotiation word from EEPROM */
	पूर्णांक adapter_cnf;	/* adapter configuration from EEPROM */
	पूर्णांक isa_config;		/* ISA configuration from EEPROM */
	पूर्णांक irq_map;		/* IRQ map from EEPROM */
	पूर्णांक rx_mode;		/* what mode are we in? 0, RX_MULTCAST_ACCEPT, or RX_ALL_ACCEPT */
	पूर्णांक curr_rx_cfg;	/* a copy of PP_RxCFG */
	पूर्णांक linectl;		/* either 0 or LOW_RX_SQUELCH, depending on configuration. */
	पूर्णांक send_underrun;	/* keep track of how many underruns in a row we get */
	पूर्णांक क्रमce;		/* क्रमce various values; see FORCE* above. */
	spinlock_t lock;
	व्योम __iomem *virt_addr;/* CS89x0 भव address. */
#अगर ALLOW_DMA
	पूर्णांक use_dma;		/* Flag: we're using dma */
	पूर्णांक dma;		/* DMA channel */
	पूर्णांक dmasize;		/* 16 or 64 */
	अचिन्हित अक्षर *dma_buff;	/* poपूर्णांकs to the beginning of the buffer */
	अचिन्हित अक्षर *end_dma_buff;	/* poपूर्णांकs to the end of the buffer */
	अचिन्हित अक्षर *rx_dma_ptr;	/* poपूर्णांकs to the next packet  */
#पूर्ण_अगर
पूर्ण;

/* Example routines you must ग_लिखो ;->. */
#घोषणा tx_करोne(dev) 1

/*
 * Permit 'cs89x0_dma=N' in the kernel boot environment
 */
#अगर !defined(MODULE)
#अगर ALLOW_DMA
अटल पूर्णांक g_cs89x0_dma;

अटल पूर्णांक __init dma_fn(अक्षर *str)
अणु
	g_cs89x0_dma = simple_म_से_दीर्घ(str, शून्य, 0);
	वापस 1;
पूर्ण

__setup("cs89x0_dma=", dma_fn);
#पूर्ण_अगर	/* ALLOW_DMA */

अटल पूर्णांक g_cs89x0_media__क्रमce;

अटल पूर्णांक __init media_fn(अक्षर *str)
अणु
	अगर (!म_भेद(str, "rj45"))
		g_cs89x0_media__क्रमce = FORCE_RJ45;
	अन्यथा अगर (!म_भेद(str, "aui"))
		g_cs89x0_media__क्रमce = FORCE_AUI;
	अन्यथा अगर (!म_भेद(str, "bnc"))
		g_cs89x0_media__क्रमce = FORCE_BNC;

	वापस 1;
पूर्ण

__setup("cs89x0_media=", media_fn);
#पूर्ण_अगर

अटल व्योम पढ़ोwords(काष्ठा net_local *lp, पूर्णांक portno, व्योम *buf, पूर्णांक length)
अणु
	u8 *buf8 = (u8 *)buf;

	करो अणु
		u16 पंचांगp16;

		पंचांगp16 = ioपढ़ो16(lp->virt_addr + portno);
		*buf8++ = (u8)पंचांगp16;
		*buf8++ = (u8)(पंचांगp16 >> 8);
	पूर्ण जबतक (--length);
पूर्ण

अटल व्योम ग_लिखोwords(काष्ठा net_local *lp, पूर्णांक portno, व्योम *buf, पूर्णांक length)
अणु
	u8 *buf8 = (u8 *)buf;

	करो अणु
		u16 पंचांगp16;

		पंचांगp16 = *buf8++;
		पंचांगp16 |= (*buf8++) << 8;
		ioग_लिखो16(पंचांगp16, lp->virt_addr + portno);
	पूर्ण जबतक (--length);
पूर्ण

अटल u16
पढ़ोreg(काष्ठा net_device *dev, u16 regno)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);

	ioग_लिखो16(regno, lp->virt_addr + ADD_PORT);
	वापस ioपढ़ो16(lp->virt_addr + DATA_PORT);
पूर्ण

अटल व्योम
ग_लिखोreg(काष्ठा net_device *dev, u16 regno, u16 value)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);

	ioग_लिखो16(regno, lp->virt_addr + ADD_PORT);
	ioग_लिखो16(value, lp->virt_addr + DATA_PORT);
पूर्ण

अटल पूर्णांक __init
रुको_eeprom_पढ़ोy(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies;
	/* check to see अगर the EEPROM is पढ़ोy,
	 * a समयout is used just in हाल EEPROM is पढ़ोy when
	 * SI_BUSY in the PP_SelfST is clear
	 */
	जबतक (पढ़ोreg(dev, PP_SelfST) & SI_BUSY)
		अगर (समय_after_eq(jअगरfies, समयout + 40))
			वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init
get_eeprom_data(काष्ठा net_device *dev, पूर्णांक off, पूर्णांक len, पूर्णांक *buffer)
अणु
	पूर्णांक i;

	cs89_dbg(3, info, "EEPROM data from %x for %x:", off, len);
	क्रम (i = 0; i < len; i++) अणु
		अगर (रुको_eeprom_पढ़ोy(dev) < 0)
			वापस -1;
		/* Now send the EEPROM पढ़ो command and EEPROM location to पढ़ो */
		ग_लिखोreg(dev, PP_EECMD, (off + i) | EEPROM_READ_CMD);
		अगर (रुको_eeprom_पढ़ोy(dev) < 0)
			वापस -1;
		buffer[i] = पढ़ोreg(dev, PP_EEData);
		cs89_dbg(3, cont, " %04x", buffer[i]);
	पूर्ण
	cs89_dbg(3, cont, "\n");
	वापस 0;
पूर्ण

अटल पूर्णांक  __init
get_eeprom_cksum(पूर्णांक off, पूर्णांक len, पूर्णांक *buffer)
अणु
	पूर्णांक i, cksum;

	cksum = 0;
	क्रम (i = 0; i < len; i++)
		cksum += buffer[i];
	cksum &= 0xffff;
	अगर (cksum == 0)
		वापस 0;
	वापस -1;
पूर्ण

अटल व्योम
ग_लिखो_irq(काष्ठा net_device *dev, पूर्णांक chip_type, पूर्णांक irq)
अणु
	पूर्णांक i;

	अगर (chip_type == CS8900) अणु
#अगर_अघोषित CONFIG_CS89x0_PLATFORM
		/* Search the mapping table क्रम the corresponding IRQ pin. */
		क्रम (i = 0; i != ARRAY_SIZE(cs8900_irq_map); i++)
			अगर (cs8900_irq_map[i] == irq)
				अवरोध;
		/* Not found */
		अगर (i == ARRAY_SIZE(cs8900_irq_map))
			i = 3;
#अन्यथा
		/* INTRQ0 pin is used क्रम पूर्णांकerrupt generation. */
		i = 0;
#पूर्ण_अगर
		ग_लिखोreg(dev, PP_CS8900_ISAINT, i);
	पूर्ण अन्यथा अणु
		ग_लिखोreg(dev, PP_CS8920_ISAINT, irq);
	पूर्ण
पूर्ण

अटल व्योम
count_rx_errors(पूर्णांक status, काष्ठा net_device *dev)
अणु
	dev->stats.rx_errors++;
	अगर (status & RX_RUNT)
		dev->stats.rx_length_errors++;
	अगर (status & RX_EXTRA_DATA)
		dev->stats.rx_length_errors++;
	अगर ((status & RX_CRC_ERROR) && !(status & (RX_EXTRA_DATA | RX_RUNT)))
		/* per str 172 */
		dev->stats.rx_crc_errors++;
	अगर (status & RX_DRIBBLE)
		dev->stats.rx_frame_errors++;
पूर्ण

/*********************************
 * This page contains DMA routines
 *********************************/

#अगर ALLOW_DMA

#घोषणा dma_page_eq(ptr1, ptr2) ((दीर्घ)(ptr1) >> 17 == (दीर्घ)(ptr2) >> 17)

अटल व्योम
get_dma_channel(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);

	अगर (lp->dma) अणु
		dev->dma = lp->dma;
		lp->isa_config |= ISA_RxDMA;
	पूर्ण अन्यथा अणु
		अगर ((lp->isa_config & ANY_ISA_DMA) == 0)
			वापस;
		dev->dma = lp->isa_config & DMA_NO_MASK;
		अगर (lp->chip_type == CS8900)
			dev->dma += 5;
		अगर (dev->dma < 5 || dev->dma > 7) अणु
			lp->isa_config &= ~ANY_ISA_DMA;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
ग_लिखो_dma(काष्ठा net_device *dev, पूर्णांक chip_type, पूर्णांक dma)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	अगर ((lp->isa_config & ANY_ISA_DMA) == 0)
		वापस;
	अगर (chip_type == CS8900)
		ग_लिखोreg(dev, PP_CS8900_ISADMA, dma - 5);
	अन्यथा
		ग_लिखोreg(dev, PP_CS8920_ISADMA, dma);
पूर्ण

अटल व्योम
set_dma_cfg(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);

	अगर (lp->use_dma) अणु
		अगर ((lp->isa_config & ANY_ISA_DMA) == 0) अणु
			cs89_dbg(3, err, "set_dma_cfg(): no DMA\n");
			वापस;
		पूर्ण
		अगर (lp->isa_config & ISA_RxDMA) अणु
			lp->curr_rx_cfg |= RX_DMA_ONLY;
			cs89_dbg(3, info, "set_dma_cfg(): RX_DMA_ONLY\n");
		पूर्ण अन्यथा अणु
			lp->curr_rx_cfg |= AUTO_RX_DMA;	/* not that we support it... */
			cs89_dbg(3, info, "set_dma_cfg(): AUTO_RX_DMA\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
dma_bufcfg(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	अगर (lp->use_dma)
		वापस (lp->isa_config & ANY_ISA_DMA) ? RX_DMA_ENBL : 0;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक
dma_busctl(काष्ठा net_device *dev)
अणु
	पूर्णांक retval = 0;
	काष्ठा net_local *lp = netdev_priv(dev);
	अगर (lp->use_dma) अणु
		अगर (lp->isa_config & ANY_ISA_DMA)
			retval |= RESET_RX_DMA; /* Reset the DMA poपूर्णांकer */
		अगर (lp->isa_config & DMA_BURST)
			retval |= DMA_BURST_MODE; /* Does ISA config specअगरy DMA burst ? */
		अगर (lp->dmasize == 64)
			retval |= RX_DMA_SIZE_64K; /* did they ask क्रम 64K? */
		retval |= MEMORY_ON;	/* we need memory enabled to use DMA. */
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम
dma_rx(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक status, length;
	अचिन्हित अक्षर *bp = lp->rx_dma_ptr;

	status = bp[0] + (bp[1] << 8);
	length = bp[2] + (bp[3] << 8);
	bp += 4;

	cs89_dbg(5, debug, "%s: receiving DMA packet at %lx, status %x, length %x\n",
		 dev->name, (अचिन्हित दीर्घ)bp, status, length);

	अगर ((status & RX_OK) == 0) अणु
		count_rx_errors(status, dev);
		जाओ skip_this_frame;
	पूर्ण

	/* Malloc up new buffer. */
	skb = netdev_alloc_skb(dev, length + 2);
	अगर (skb == शून्य) अणु
		dev->stats.rx_dropped++;

		/* AKPM: advance bp to the next frame */
skip_this_frame:
		bp += (length + 3) & ~3;
		अगर (bp >= lp->end_dma_buff)
			bp -= lp->dmasize * 1024;
		lp->rx_dma_ptr = bp;
		वापस;
	पूर्ण
	skb_reserve(skb, 2);	/* दीर्घword align L3 header */

	अगर (bp + length > lp->end_dma_buff) अणु
		पूर्णांक semi_cnt = lp->end_dma_buff - bp;
		skb_put_data(skb, bp, semi_cnt);
		skb_put_data(skb, lp->dma_buff, length - semi_cnt);
	पूर्ण अन्यथा अणु
		skb_put_data(skb, bp, length);
	पूर्ण
	bp += (length + 3) & ~3;
	अगर (bp >= lp->end_dma_buff)
		bp -= lp->dmasize*1024;
	lp->rx_dma_ptr = bp;

	cs89_dbg(3, info, "%s: received %d byte DMA packet of type %x\n",
		 dev->name, length,
		 ((skb->data[ETH_ALEN + ETH_ALEN] << 8) |
		  skb->data[ETH_ALEN + ETH_ALEN + 1]));

	skb->protocol = eth_type_trans(skb, dev);
	netअगर_rx(skb);
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += length;
पूर्ण

अटल व्योम release_dma_buff(काष्ठा net_local *lp)
अणु
	अगर (lp->dma_buff) अणु
		मुक्त_pages((अचिन्हित दीर्घ)(lp->dma_buff),
			   get_order(lp->dmasize * 1024));
		lp->dma_buff = शून्य;
	पूर्ण
पूर्ण

#पूर्ण_अगर	/* ALLOW_DMA */

अटल व्योम
control_dc_dc(काष्ठा net_device *dev, पूर्णांक on_not_off)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक selfcontrol;
	अचिन्हित दीर्घ समयnow = jअगरfies;
	/* control the DC to DC convertor in the SelfControl रेजिस्टर.
	 * Note: This is hooked up to a general purpose pin, might not
	 * always be a DC to DC convertor.
	 */

	selfcontrol = HCB1_ENBL; /* Enable the HCB1 bit as an output */
	अगर (((lp->adapter_cnf & A_CNF_DC_DC_POLARITY) != 0) ^ on_not_off)
		selfcontrol |= HCB1;
	अन्यथा
		selfcontrol &= ~HCB1;
	ग_लिखोreg(dev, PP_SelfCTL, selfcontrol);

	/* Wait क्रम the DC/DC converter to घातer up - 500ms */
	जबतक (समय_beक्रमe(jअगरfies, समयnow + HZ))
		;
पूर्ण

/* send a test packet - वापस true अगर carrier bits are ok */
अटल पूर्णांक
send_test_pkt(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	अक्षर test_packet[] = अणु
		0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,
		0, 46,		/* A 46 in network order */
		0, 0,		/* DSAP=0 & SSAP=0 fields */
		0xf3, 0		/* Control (Test Req + P bit set) */
	पूर्ण;
	अचिन्हित दीर्घ समयnow = jअगरfies;

	ग_लिखोreg(dev, PP_LineCTL, पढ़ोreg(dev, PP_LineCTL) | SERIAL_TX_ON);

	स_नकल(test_packet,            dev->dev_addr, ETH_ALEN);
	स_नकल(test_packet + ETH_ALEN, dev->dev_addr, ETH_ALEN);

	ioग_लिखो16(TX_AFTER_ALL, lp->virt_addr + TX_CMD_PORT);
	ioग_लिखो16(ETH_ZLEN, lp->virt_addr + TX_LEN_PORT);

	/* Test to see अगर the chip has allocated memory क्रम the packet */
	जबतक (समय_beक्रमe(jअगरfies, समयnow + 5))
		अगर (पढ़ोreg(dev, PP_BusST) & READY_FOR_TX_NOW)
			अवरोध;
	अगर (समय_after_eq(jअगरfies, समयnow + 5))
		वापस 0;	/* this shouldn't happen */

	/* Write the contents of the packet */
	ग_लिखोwords(lp, TX_FRAME_PORT, test_packet, (ETH_ZLEN + 1) >> 1);

	cs89_dbg(1, debug, "Sending test packet ");
	/* रुको a couple of jअगरfies क्रम packet to be received */
	क्रम (समयnow = jअगरfies; समय_beक्रमe(jअगरfies, समयnow + 3);)
		;
	अगर ((पढ़ोreg(dev, PP_TxEvent) & TX_SEND_OK_BITS) == TX_OK) अणु
		cs89_dbg(1, cont, "succeeded\n");
		वापस 1;
	पूर्ण
	cs89_dbg(1, cont, "failed\n");
	वापस 0;
पूर्ण

#घोषणा DETECTED_NONE  0
#घोषणा DETECTED_RJ45H 1
#घोषणा DETECTED_RJ45F 2
#घोषणा DETECTED_AUI   3
#घोषणा DETECTED_BNC   4

अटल पूर्णांक
detect_tp(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	अचिन्हित दीर्घ समयnow = jअगरfies;
	पूर्णांक fdx;

	cs89_dbg(1, debug, "%s: Attempting TP\n", dev->name);

	/* If connected to another full duplex capable 10-Base-T card
	 * the link pulses seem to be lost when the स्वतः detect bit in
	 * the LineCTL is set.  To overcome this the स्वतः detect bit will
	 * be cleared whilst testing the 10-Base-T पूर्णांकerface.  This would
	 * not be necessary क्रम the sparrow chip but is simpler to करो it
	 * anyway.
	 */
	ग_लिखोreg(dev, PP_LineCTL, lp->linectl & ~AUI_ONLY);
	control_dc_dc(dev, 0);

	/* Delay क्रम the hardware to work out अगर the TP cable is present
	 * - 150ms
	 */
	क्रम (समयnow = jअगरfies; समय_beक्रमe(jअगरfies, समयnow + 15);)
		;
	अगर ((पढ़ोreg(dev, PP_LineST) & LINK_OK) == 0)
		वापस DETECTED_NONE;

	अगर (lp->chip_type == CS8900) अणु
		चयन (lp->क्रमce & 0xf0) अणु
#अगर 0
		हाल FORCE_AUTO:
			pr_info("%s: cs8900 doesn't autonegotiate\n",
				dev->name);
			वापस DETECTED_NONE;
#पूर्ण_अगर
			/* CS8900 करोesn't support AUTO, change to HALF*/
		हाल FORCE_AUTO:
			lp->क्रमce &= ~FORCE_AUTO;
			lp->क्रमce |= FORCE_HALF;
			अवरोध;
		हाल FORCE_HALF:
			अवरोध;
		हाल FORCE_FULL:
			ग_लिखोreg(dev, PP_TestCTL,
				 पढ़ोreg(dev, PP_TestCTL) | FDX_8900);
			अवरोध;
		पूर्ण
		fdx = पढ़ोreg(dev, PP_TestCTL) & FDX_8900;
	पूर्ण अन्यथा अणु
		चयन (lp->क्रमce & 0xf0) अणु
		हाल FORCE_AUTO:
			lp->स्वतः_neg_cnf = AUTO_NEG_ENABLE;
			अवरोध;
		हाल FORCE_HALF:
			lp->स्वतः_neg_cnf = 0;
			अवरोध;
		हाल FORCE_FULL:
			lp->स्वतः_neg_cnf = RE_NEG_NOW | ALLOW_FDX;
			अवरोध;
		पूर्ण

		ग_लिखोreg(dev, PP_AutoNegCTL, lp->स्वतः_neg_cnf & AUTO_NEG_MASK);

		अगर ((lp->स्वतः_neg_cnf & AUTO_NEG_BITS) == AUTO_NEG_ENABLE) अणु
			pr_info("%s: negotiating duplex...\n", dev->name);
			जबतक (पढ़ोreg(dev, PP_AutoNegST) & AUTO_NEG_BUSY) अणु
				अगर (समय_after(jअगरfies, समयnow + 4000)) अणु
					pr_err("**** Full / half duplex auto-negotiation timed out ****\n");
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		fdx = पढ़ोreg(dev, PP_AutoNegST) & FDX_ACTIVE;
	पूर्ण
	अगर (fdx)
		वापस DETECTED_RJ45F;
	अन्यथा
		वापस DETECTED_RJ45H;
पूर्ण

अटल पूर्णांक
detect_bnc(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);

	cs89_dbg(1, debug, "%s: Attempting BNC\n", dev->name);
	control_dc_dc(dev, 1);

	ग_लिखोreg(dev, PP_LineCTL, (lp->linectl & ~AUTO_AUI_10BASET) | AUI_ONLY);

	अगर (send_test_pkt(dev))
		वापस DETECTED_BNC;
	अन्यथा
		वापस DETECTED_NONE;
पूर्ण

अटल पूर्णांक
detect_aui(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);

	cs89_dbg(1, debug, "%s: Attempting AUI\n", dev->name);
	control_dc_dc(dev, 0);

	ग_लिखोreg(dev, PP_LineCTL, (lp->linectl & ~AUTO_AUI_10BASET) | AUI_ONLY);

	अगर (send_test_pkt(dev))
		वापस DETECTED_AUI;
	अन्यथा
		वापस DETECTED_NONE;
पूर्ण

/* We have a good packet(s), get it/them out of the buffers. */
अटल व्योम
net_rx(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक status, length;

	status = ioपढ़ो16(lp->virt_addr + RX_FRAME_PORT);
	length = ioपढ़ो16(lp->virt_addr + RX_FRAME_PORT);

	अगर ((status & RX_OK) == 0) अणु
		count_rx_errors(status, dev);
		वापस;
	पूर्ण

	/* Malloc up new buffer. */
	skb = netdev_alloc_skb(dev, length + 2);
	अगर (skb == शून्य) अणु
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण
	skb_reserve(skb, 2);	/* दीर्घword align L3 header */

	पढ़ोwords(lp, RX_FRAME_PORT, skb_put(skb, length), length >> 1);
	अगर (length & 1)
		skb->data[length-1] = ioपढ़ो16(lp->virt_addr + RX_FRAME_PORT);

	cs89_dbg(3, debug, "%s: received %d byte packet of type %x\n",
		 dev->name, length,
		 (skb->data[ETH_ALEN + ETH_ALEN] << 8) |
		 skb->data[ETH_ALEN + ETH_ALEN + 1]);

	skb->protocol = eth_type_trans(skb, dev);
	netअगर_rx(skb);
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += length;
पूर्ण

/* The typical workload of the driver:
 * Handle the network पूर्णांकerface पूर्णांकerrupts.
 */

अटल irqवापस_t net_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा net_local *lp;
	पूर्णांक status;
	पूर्णांक handled = 0;

	lp = netdev_priv(dev);

	/* we MUST पढ़ो all the events out of the ISQ, otherwise we'll never
	 * get पूर्णांकerrupted again.  As a consequence, we can't have any limit
	 * on the number of बार we loop in the पूर्णांकerrupt handler.  The
	 * hardware guarantees that eventually we'll run out of events.  Of
	 * course, अगर you're on a slow machine, and packets are arriving
	 * faster than you can पढ़ो them off, you're screwed.  Hasta la
	 * vista, baby!
	 */
	जबतक ((status = ioपढ़ो16(lp->virt_addr + ISQ_PORT))) अणु
		cs89_dbg(4, debug, "%s: event=%04x\n", dev->name, status);
		handled = 1;
		चयन (status & ISQ_EVENT_MASK) अणु
		हाल ISQ_RECEIVER_EVENT:
			/* Got a packet(s). */
			net_rx(dev);
			अवरोध;
		हाल ISQ_TRANSMITTER_EVENT:
			dev->stats.tx_packets++;
			netअगर_wake_queue(dev);	/* Inक्रमm upper layers. */
			अगर ((status & (TX_OK |
				       TX_LOST_CRS |
				       TX_SQE_ERROR |
				       TX_LATE_COL |
				       TX_16_COL)) != TX_OK) अणु
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
			पूर्ण
			अवरोध;
		हाल ISQ_BUFFER_EVENT:
			अगर (status & READY_FOR_TX) अणु
				/* we tried to transmit a packet earlier,
				 * but inexplicably ran out of buffers.
				 * That shouldn't happen since we only ever
				 * load one packet.  Shrug.  Do the right
				 * thing anyway.
				 */
				netअगर_wake_queue(dev);	/* Inक्रमm upper layers. */
			पूर्ण
			अगर (status & TX_UNDERRUN) अणु
				cs89_dbg(0, err, "%s: transmit underrun\n",
					 dev->name);
				lp->send_underrun++;
				अगर (lp->send_underrun == 3)
					lp->send_cmd = TX_AFTER_381;
				अन्यथा अगर (lp->send_underrun == 6)
					lp->send_cmd = TX_AFTER_ALL;
				/* transmit cycle is करोne, although
				 * frame wasn't transmitted - this
				 * aव्योमs having to रुको क्रम the upper
				 * layers to समयout on us, in the
				 * event of a tx underrun
				 */
				netअगर_wake_queue(dev);	/* Inक्रमm upper layers. */
			पूर्ण
#अगर ALLOW_DMA
			अगर (lp->use_dma && (status & RX_DMA)) अणु
				पूर्णांक count = पढ़ोreg(dev, PP_DmaFrameCnt);
				जबतक (count) अणु
					cs89_dbg(5, debug,
						 "%s: receiving %d DMA frames\n",
						 dev->name, count);
					अगर (count > 1)
						cs89_dbg(2, debug,
							 "%s: receiving %d DMA frames\n",
							 dev->name, count);
					dma_rx(dev);
					अगर (--count == 0)
						count = पढ़ोreg(dev, PP_DmaFrameCnt);
					अगर (count > 0)
						cs89_dbg(2, debug,
							 "%s: continuing with %d DMA frames\n",
							 dev->name, count);
				पूर्ण
			पूर्ण
#पूर्ण_अगर
			अवरोध;
		हाल ISQ_RX_MISS_EVENT:
			dev->stats.rx_missed_errors += (status >> 6);
			अवरोध;
		हाल ISQ_TX_COL_EVENT:
			dev->stats.collisions += (status >> 6);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण

/* Open/initialize the board.  This is called (in the current kernel)
   someसमय after booting when the 'ifconfig' program is run.

   This routine should set everything up anew at each खोलो, even
   रेजिस्टरs that "should" only need to be set once at boot, so that
   there is non-reboot way to recover अगर something goes wrong.
*/

/* AKPM: करो we need to करो any locking here? */

अटल पूर्णांक
net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	पूर्णांक result = 0;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (dev->irq < 2) अणु
		/* Allow पूर्णांकerrupts to be generated by the chip */
/* Cirrus' release had this: */
#अगर 0
		ग_लिखोreg(dev, PP_BusCTL, पढ़ोreg(dev, PP_BusCTL) | ENABLE_IRQ);
#पूर्ण_अगर
/* And 2.3.47 had this: */
		ग_लिखोreg(dev, PP_BusCTL, ENABLE_IRQ | MEMORY_ON);

		क्रम (i = 2; i < CS8920_NO_INTS; i++) अणु
			अगर ((1 << i) & lp->irq_map) अणु
				अगर (request_irq(i, net_पूर्णांकerrupt, 0, dev->name,
						dev) == 0) अणु
					dev->irq = i;
					ग_लिखो_irq(dev, lp->chip_type, i);
					/* ग_लिखोreg(dev, PP_BufCFG, GENERATE_SW_INTERRUPT); */
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (i >= CS8920_NO_INTS) अणु
			ग_लिखोreg(dev, PP_BusCTL, 0);	/* disable पूर्णांकerrupts. */
			pr_err("can't get an interrupt\n");
			ret = -EAGAIN;
			जाओ bad_out;
		पूर्ण
	पूर्ण अन्यथा अणु
#अगर !defined(CONFIG_CS89x0_PLATFORM)
		अगर (((1 << dev->irq) & lp->irq_map) == 0) अणु
			pr_err("%s: IRQ %d is not in our map of allowable IRQs, which is %x\n",
			       dev->name, dev->irq, lp->irq_map);
			ret = -EAGAIN;
			जाओ bad_out;
		पूर्ण
#पूर्ण_अगर
/* FIXME: Cirrus' release had this: */
		ग_लिखोreg(dev, PP_BusCTL, पढ़ोreg(dev, PP_BusCTL)|ENABLE_IRQ);
/* And 2.3.47 had this: */
#अगर 0
		ग_लिखोreg(dev, PP_BusCTL, ENABLE_IRQ | MEMORY_ON);
#पूर्ण_अगर
		ग_लिखो_irq(dev, lp->chip_type, dev->irq);
		ret = request_irq(dev->irq, net_पूर्णांकerrupt, 0, dev->name, dev);
		अगर (ret) अणु
			pr_err("request_irq(%d) failed\n", dev->irq);
			जाओ bad_out;
		पूर्ण
	पूर्ण

#अगर ALLOW_DMA
	अगर (lp->use_dma && (lp->isa_config & ANY_ISA_DMA)) अणु
		अचिन्हित दीर्घ flags;
		lp->dma_buff = (अचिन्हित अक्षर *)__get_dma_pages(GFP_KERNEL,
								get_order(lp->dmasize * 1024));
		अगर (!lp->dma_buff) अणु
			pr_err("%s: cannot get %dK memory for DMA\n",
			       dev->name, lp->dmasize);
			जाओ release_irq;
		पूर्ण
		cs89_dbg(1, debug, "%s: dma %lx %lx\n",
			 dev->name,
			 (अचिन्हित दीर्घ)lp->dma_buff,
			 (अचिन्हित दीर्घ)isa_virt_to_bus(lp->dma_buff));
		अगर ((अचिन्हित दीर्घ)lp->dma_buff >= MAX_DMA_ADDRESS ||
		    !dma_page_eq(lp->dma_buff,
				 lp->dma_buff + lp->dmasize * 1024 - 1)) अणु
			pr_err("%s: not usable as DMA buffer\n", dev->name);
			जाओ release_irq;
		पूर्ण
		स_रखो(lp->dma_buff, 0, lp->dmasize * 1024);	/* Why? */
		अगर (request_dma(dev->dma, dev->name)) अणु
			pr_err("%s: cannot get dma channel %d\n",
			       dev->name, dev->dma);
			जाओ release_irq;
		पूर्ण
		ग_लिखो_dma(dev, lp->chip_type, dev->dma);
		lp->rx_dma_ptr = lp->dma_buff;
		lp->end_dma_buff = lp->dma_buff + lp->dmasize * 1024;
		spin_lock_irqsave(&lp->lock, flags);
		disable_dma(dev->dma);
		clear_dma_ff(dev->dma);
		set_dma_mode(dev->dma, DMA_RX_MODE); /* स्वतः_init as well */
		set_dma_addr(dev->dma, isa_virt_to_bus(lp->dma_buff));
		set_dma_count(dev->dma, lp->dmasize * 1024);
		enable_dma(dev->dma);
		spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण
#पूर्ण_अगर	/* ALLOW_DMA */

	/* set the Ethernet address */
	क्रम (i = 0; i < ETH_ALEN / 2; i++)
		ग_लिखोreg(dev, PP_IA + i * 2,
			 (dev->dev_addr[i * 2] |
			  (dev->dev_addr[i * 2 + 1] << 8)));

	/* जबतक we're testing the पूर्णांकerface, leave पूर्णांकerrupts disabled */
	ग_लिखोreg(dev, PP_BusCTL, MEMORY_ON);

	/* Set the LineCTL quपूर्णांकuplet based on adapter configuration पढ़ो from EEPROM */
	अगर ((lp->adapter_cnf & A_CNF_EXTND_10B_2) &&
	    (lp->adapter_cnf & A_CNF_LOW_RX_SQUELCH))
		lp->linectl = LOW_RX_SQUELCH;
	अन्यथा
		lp->linectl = 0;

	/* check to make sure that they have the "right" hardware available */
	चयन (lp->adapter_cnf & A_CNF_MEDIA_TYPE) अणु
	हाल A_CNF_MEDIA_10B_T:
		result = lp->adapter_cnf & A_CNF_10B_T;
		अवरोध;
	हाल A_CNF_MEDIA_AUI:
		result = lp->adapter_cnf & A_CNF_AUI;
		अवरोध;
	हाल A_CNF_MEDIA_10B_2:
		result = lp->adapter_cnf & A_CNF_10B_2;
		अवरोध;
	शेष:
		result = lp->adapter_cnf & (A_CNF_10B_T |
					    A_CNF_AUI |
					    A_CNF_10B_2);
	पूर्ण
	अगर (!result) अणु
		pr_err("%s: EEPROM is configured for unavailable media\n",
		       dev->name);
release_dma:
#अगर ALLOW_DMA
		मुक्त_dma(dev->dma);
release_irq:
		release_dma_buff(lp);
#पूर्ण_अगर
		ग_लिखोreg(dev, PP_LineCTL,
			 पढ़ोreg(dev, PP_LineCTL) & ~(SERIAL_TX_ON | SERIAL_RX_ON));
		मुक्त_irq(dev->irq, dev);
		ret = -EAGAIN;
		जाओ bad_out;
	पूर्ण

	/* set the hardware to the configured choice */
	चयन (lp->adapter_cnf & A_CNF_MEDIA_TYPE) अणु
	हाल A_CNF_MEDIA_10B_T:
		result = detect_tp(dev);
		अगर (result == DETECTED_NONE) अणु
			pr_warn("%s: 10Base-T (RJ-45) has no cable\n",
				dev->name);
			अगर (lp->स्वतः_neg_cnf & IMM_BIT) /* check "ignore missing media" bit */
				result = DETECTED_RJ45H; /* Yes! I करोn't care अगर I see a link pulse */
		पूर्ण
		अवरोध;
	हाल A_CNF_MEDIA_AUI:
		result = detect_aui(dev);
		अगर (result == DETECTED_NONE) अणु
			pr_warn("%s: 10Base-5 (AUI) has no cable\n", dev->name);
			अगर (lp->स्वतः_neg_cnf & IMM_BIT) /* check "ignore missing media" bit */
				result = DETECTED_AUI; /* Yes! I करोn't care अगर I see a carrrier */
		पूर्ण
		अवरोध;
	हाल A_CNF_MEDIA_10B_2:
		result = detect_bnc(dev);
		अगर (result == DETECTED_NONE) अणु
			pr_warn("%s: 10Base-2 (BNC) has no cable\n", dev->name);
			अगर (lp->स्वतः_neg_cnf & IMM_BIT) /* check "ignore missing media" bit */
				result = DETECTED_BNC; /* Yes! I करोn't care अगर I can xmit a packet */
		पूर्ण
		अवरोध;
	हाल A_CNF_MEDIA_AUTO:
		ग_लिखोreg(dev, PP_LineCTL, lp->linectl | AUTO_AUI_10BASET);
		अगर (lp->adapter_cnf & A_CNF_10B_T) अणु
			result = detect_tp(dev);
			अगर (result != DETECTED_NONE)
				अवरोध;
		पूर्ण
		अगर (lp->adapter_cnf & A_CNF_AUI) अणु
			result = detect_aui(dev);
			अगर (result != DETECTED_NONE)
				अवरोध;
		पूर्ण
		अगर (lp->adapter_cnf & A_CNF_10B_2) अणु
			result = detect_bnc(dev);
			अगर (result != DETECTED_NONE)
				अवरोध;
		पूर्ण
		pr_err("%s: no media detected\n", dev->name);
		जाओ release_dma;
	पूर्ण
	चयन (result) अणु
	हाल DETECTED_NONE:
		pr_err("%s: no network cable attached to configured media\n",
		       dev->name);
		जाओ release_dma;
	हाल DETECTED_RJ45H:
		pr_info("%s: using half-duplex 10Base-T (RJ-45)\n", dev->name);
		अवरोध;
	हाल DETECTED_RJ45F:
		pr_info("%s: using full-duplex 10Base-T (RJ-45)\n", dev->name);
		अवरोध;
	हाल DETECTED_AUI:
		pr_info("%s: using 10Base-5 (AUI)\n", dev->name);
		अवरोध;
	हाल DETECTED_BNC:
		pr_info("%s: using 10Base-2 (BNC)\n", dev->name);
		अवरोध;
	पूर्ण

	/* Turn on both receive and transmit operations */
	ग_लिखोreg(dev, PP_LineCTL,
		 पढ़ोreg(dev, PP_LineCTL) | SERIAL_RX_ON | SERIAL_TX_ON);

	/* Receive only error मुक्त packets addressed to this card */
	lp->rx_mode = 0;
	ग_लिखोreg(dev, PP_RxCTL, DEF_RX_ACCEPT);

	lp->curr_rx_cfg = RX_OK_ENBL | RX_CRC_ERROR_ENBL;

	अगर (lp->isa_config & STREAM_TRANSFER)
		lp->curr_rx_cfg |= RX_STREAM_ENBL;
#अगर ALLOW_DMA
	set_dma_cfg(dev);
#पूर्ण_अगर
	ग_लिखोreg(dev, PP_RxCFG, lp->curr_rx_cfg);

	ग_लिखोreg(dev, PP_TxCFG, (TX_LOST_CRS_ENBL |
				 TX_SQE_ERROR_ENBL |
				 TX_OK_ENBL |
				 TX_LATE_COL_ENBL |
				 TX_JBR_ENBL |
				 TX_ANY_COL_ENBL |
				 TX_16_COL_ENBL));

	ग_लिखोreg(dev, PP_BufCFG, (READY_FOR_TX_ENBL |
				  RX_MISS_COUNT_OVRFLOW_ENBL |
#अगर ALLOW_DMA
				  dma_bufcfg(dev) |
#पूर्ण_अगर
				  TX_COL_COUNT_OVRFLOW_ENBL |
				  TX_UNDERRUN_ENBL));

	/* now that we've got our act together, enable everything */
	ग_लिखोreg(dev, PP_BusCTL, (ENABLE_IRQ
				  | (dev->mem_start ? MEMORY_ON : 0) /* turn memory on */
#अगर ALLOW_DMA
				  | dma_busctl(dev)
#पूर्ण_अगर
			 ));
	netअगर_start_queue(dev);
	cs89_dbg(1, debug, "net_open() succeeded\n");
	वापस 0;
bad_out:
	वापस ret;
पूर्ण

/* The inverse routine to net_खोलो(). */
अटल पूर्णांक
net_बंद(काष्ठा net_device *dev)
अणु
#अगर ALLOW_DMA
	काष्ठा net_local *lp = netdev_priv(dev);
#पूर्ण_अगर

	netअगर_stop_queue(dev);

	ग_लिखोreg(dev, PP_RxCFG, 0);
	ग_लिखोreg(dev, PP_TxCFG, 0);
	ग_लिखोreg(dev, PP_BufCFG, 0);
	ग_लिखोreg(dev, PP_BusCTL, 0);

	मुक्त_irq(dev->irq, dev);

#अगर ALLOW_DMA
	अगर (lp->use_dma && lp->dma) अणु
		मुक्त_dma(dev->dma);
		release_dma_buff(lp);
	पूर्ण
#पूर्ण_अगर

	/* Update the statistics here. */
	वापस 0;
पूर्ण

/* Get the current statistics.
 * This may be called with the card खोलो or बंदd.
 */
अटल काष्ठा net_device_stats *
net_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lp->lock, flags);
	/* Update the statistics from the device रेजिस्टरs. */
	dev->stats.rx_missed_errors += (पढ़ोreg(dev, PP_RxMiss) >> 6);
	dev->stats.collisions += (पढ़ोreg(dev, PP_TxCol) >> 6);
	spin_unlock_irqrestore(&lp->lock, flags);

	वापस &dev->stats;
पूर्ण

अटल व्योम net_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	/* If we get here, some higher level has decided we are broken.
	   There should really be a "kick me" function call instead. */
	cs89_dbg(0, err, "%s: transmit timed out, %s?\n",
		 dev->name,
		 tx_करोne(dev) ? "IRQ conflict" : "network cable problem");
	/* Try to restart the adaptor. */
	netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t net_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	cs89_dbg(3, debug, "%s: sent %d byte packet of type %x\n",
		 dev->name, skb->len,
		 ((skb->data[ETH_ALEN + ETH_ALEN] << 8) |
		  skb->data[ETH_ALEN + ETH_ALEN + 1]));

	/* keep the upload from being पूर्णांकerrupted, since we
	 * ask the chip to start transmitting beक्रमe the
	 * whole packet has been completely uploaded.
	 */

	spin_lock_irqsave(&lp->lock, flags);
	netअगर_stop_queue(dev);

	/* initiate a transmit sequence */
	ioग_लिखो16(lp->send_cmd, lp->virt_addr + TX_CMD_PORT);
	ioग_लिखो16(skb->len, lp->virt_addr + TX_LEN_PORT);

	/* Test to see अगर the chip has allocated memory क्रम the packet */
	अगर ((पढ़ोreg(dev, PP_BusST) & READY_FOR_TX_NOW) == 0) अणु
		/* Gasp!  It hasn't.  But that shouldn't happen since
		 * we're रुकोing क्रम TxOk, so वापस 1 and requeue this packet.
		 */

		spin_unlock_irqrestore(&lp->lock, flags);
		cs89_dbg(0, err, "Tx buffer not free!\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण
	/* Write the contents of the packet */
	ग_लिखोwords(lp, TX_FRAME_PORT, skb->data, (skb->len + 1) >> 1);
	spin_unlock_irqrestore(&lp->lock, flags);
	dev->stats.tx_bytes += skb->len;
	dev_consume_skb_any(skb);

	/* We DO NOT call netअगर_wake_queue() here.
	 * We also DO NOT call netअगर_start_queue().
	 *
	 * Either of these would cause another bottom half run through
	 * net_send_packet() beक्रमe this packet has fully gone out.
	 * That causes us to hit the "Gasp!" above and the send is rescheduled.
	 * it runs like a करोg.  We just वापस and रुको क्रम the Tx completion
	 * पूर्णांकerrupt handler to restart the netdevice layer
	 */

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	u16 cfg;

	spin_lock_irqsave(&lp->lock, flags);
	अगर (dev->flags & IFF_PROMISC)
		lp->rx_mode = RX_ALL_ACCEPT;
	अन्यथा अगर ((dev->flags & IFF_ALLMULTI) || !netdev_mc_empty(dev))
		/* The multicast-accept list is initialized to accept-all,
		 * and we rely on higher-level filtering क्रम now.
		 */
		lp->rx_mode = RX_MULTCAST_ACCEPT;
	अन्यथा
		lp->rx_mode = 0;

	ग_लिखोreg(dev, PP_RxCTL, DEF_RX_ACCEPT | lp->rx_mode);

	/* in promiscuous mode, we accept errored packets,
	 * so we have to enable पूर्णांकerrupts on them also
	 */
	cfg = lp->curr_rx_cfg;
	अगर (lp->rx_mode == RX_ALL_ACCEPT)
		cfg |= RX_CRC_ERROR_ENBL | RX_RUNT_ENBL | RX_EXTRA_DATA_ENBL;
	ग_लिखोreg(dev, PP_RxCFG, cfg);
	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

अटल पूर्णांक set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक i;
	काष्ठा sockaddr *addr = p;

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	cs89_dbg(0, debug, "%s: Setting MAC address to %pM\n",
		 dev->name, dev->dev_addr);

	/* set the Ethernet address */
	क्रम (i = 0; i < ETH_ALEN / 2; i++)
		ग_लिखोreg(dev, PP_IA + i * 2,
			 (dev->dev_addr[i * 2] |
			  (dev->dev_addr[i * 2 + 1] << 8)));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling receive - used by netconsole and other diagnostic tools
 * to allow network i/o with पूर्णांकerrupts disabled.
 */
अटल व्योम net_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	net_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops net_ops = अणु
	.nकरो_खोलो		= net_खोलो,
	.nकरो_stop		= net_बंद,
	.nकरो_tx_समयout		= net_समयout,
	.nकरो_start_xmit		= net_send_packet,
	.nकरो_get_stats		= net_get_stats,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address	= set_mac_address,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= net_poll_controller,
#पूर्ण_अगर
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल व्योम __init reset_chip(काष्ठा net_device *dev)
अणु
#अगर !defined(CONFIG_MACH_MX31ADS)
	काष्ठा net_local *lp = netdev_priv(dev);
	अचिन्हित दीर्घ reset_start_समय;

	ग_लिखोreg(dev, PP_SelfCTL, पढ़ोreg(dev, PP_SelfCTL) | POWER_ON_RESET);

	/* रुको 30 ms */
	msleep(30);

	अगर (lp->chip_type != CS8900) अणु
		/* Hardware problem requires PNP रेजिस्टरs to be reconfigured after a reset */
		ioग_लिखो16(PP_CS8920_ISAINT, lp->virt_addr + ADD_PORT);
		ioग_लिखो8(dev->irq, lp->virt_addr + DATA_PORT);
		ioग_लिखो8(0, lp->virt_addr + DATA_PORT + 1);

		ioग_लिखो16(PP_CS8920_ISAMemB, lp->virt_addr + ADD_PORT);
		ioग_लिखो8((dev->mem_start >> 16) & 0xff,
			 lp->virt_addr + DATA_PORT);
		ioग_लिखो8((dev->mem_start >> 8) & 0xff,
			 lp->virt_addr + DATA_PORT + 1);
	पूर्ण

	/* Wait until the chip is reset */
	reset_start_समय = jअगरfies;
	जबतक ((पढ़ोreg(dev, PP_SelfST) & INIT_DONE) == 0 &&
	       समय_beक्रमe(jअगरfies, reset_start_समय + 2))
		;
#पूर्ण_अगर /* !CONFIG_MACH_MX31ADS */
पूर्ण

/* This is the real probe routine.
 * Linux has a history of मित्रly device probes on the ISA bus.
 * A good device probes aव्योमs करोing ग_लिखोs, and
 * verअगरies that the correct device exists and functions.
 * Return 0 on success.
 */
अटल पूर्णांक __init
cs89x0_probe1(काष्ठा net_device *dev, व्योम __iomem *ioaddr, पूर्णांक modular)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	पूर्णांक i;
	पूर्णांक पंचांगp;
	अचिन्हित rev_type = 0;
	पूर्णांक eeprom_buff[CHKSUM_LEN];
	पूर्णांक retval;

	/* Initialize the device काष्ठाure. */
	अगर (!modular) अणु
		स_रखो(lp, 0, माप(*lp));
		spin_lock_init(&lp->lock);
#अगर_अघोषित MODULE
#अगर ALLOW_DMA
		अगर (g_cs89x0_dma) अणु
			lp->use_dma = 1;
			lp->dma = g_cs89x0_dma;
			lp->dmasize = 16;	/* Could make this an option... */
		पूर्ण
#पूर्ण_अगर
		lp->क्रमce = g_cs89x0_media__क्रमce;
#पूर्ण_अगर
	पूर्ण

	pr_debug("PP_addr at %p[%x]: 0x%x\n",
		 ioaddr, ADD_PORT, ioपढ़ो16(ioaddr + ADD_PORT));
	ioग_लिखो16(PP_ChipID, ioaddr + ADD_PORT);

	पंचांगp = ioपढ़ो16(ioaddr + DATA_PORT);
	अगर (पंचांगp != CHIP_EISA_ID_SIG) अणु
		pr_debug("%s: incorrect signature at %p[%x]: 0x%x!="
			 CHIP_EISA_ID_SIG_STR "\n",
			 dev->name, ioaddr, DATA_PORT, पंचांगp);
		retval = -ENODEV;
		जाओ out1;
	पूर्ण

	lp->virt_addr = ioaddr;

	/* get the chip type */
	rev_type = पढ़ोreg(dev, PRODUCT_ID_ADD);
	lp->chip_type = rev_type & ~REVISON_BITS;
	lp->chip_revision = ((rev_type & REVISON_BITS) >> 8) + 'A';

	/* Check the chip type and revision in order to set the correct
	 * send command.  CS8920 revision C and CS8900 revision F can use
	 * the faster send.
	 */
	lp->send_cmd = TX_AFTER_381;
	अगर (lp->chip_type == CS8900 && lp->chip_revision >= 'F')
		lp->send_cmd = TX_NOW;
	अगर (lp->chip_type != CS8900 && lp->chip_revision >= 'C')
		lp->send_cmd = TX_NOW;

	pr_info_once("%s\n", version);

	pr_info("%s: cs89%c0%s rev %c found at %p ",
		dev->name,
		lp->chip_type == CS8900  ? '0' : '2',
		lp->chip_type == CS8920M ? "M" : "",
		lp->chip_revision,
		lp->virt_addr);

	reset_chip(dev);

	/* Here we पढ़ो the current configuration of the chip.
	 * If there is no Extended EEPROM then the idea is to not disturb
	 * the chip configuration, it should have been correctly setup by
	 * स्वतःmatic EEPROM पढ़ो on reset. So, अगर the chip says it पढ़ो
	 * the EEPROM the driver will always करो *something* instead of
	 * complain that adapter_cnf is 0.
	 */

	अगर ((पढ़ोreg(dev, PP_SelfST) & (EEPROM_OK | EEPROM_PRESENT)) ==
	    (EEPROM_OK | EEPROM_PRESENT)) अणु
		/* Load the MAC. */
		क्रम (i = 0; i < ETH_ALEN / 2; i++) अणु
			अचिन्हित पूर्णांक Addr;
			Addr = पढ़ोreg(dev, PP_IA + i * 2);
			dev->dev_addr[i * 2] = Addr & 0xFF;
			dev->dev_addr[i * 2 + 1] = Addr >> 8;
		पूर्ण

		/* Load the Adapter Configuration.
		 * Note:  Barring any more specअगरic inक्रमmation from some
		 * other source (ie EEPROM+Schematics), we would not know
		 * how to operate a 10Base2 पूर्णांकerface on the AUI port.
		 * However, since we  करो पढ़ो the status of HCB1 and use
		 * settings that always result in calls to control_dc_dc(dev,0)
		 * a BNC पूर्णांकerface should work अगर the enable pin
		 * (dc/dc converter) is on HCB1.
		 * It will be called AUI however.
		 */

		lp->adapter_cnf = 0;
		i = पढ़ोreg(dev, PP_LineCTL);
		/* Preserve the setting of the HCB1 pin. */
		अगर ((i & (HCB1 | HCB1_ENBL)) == (HCB1 | HCB1_ENBL))
			lp->adapter_cnf |= A_CNF_DC_DC_POLARITY;
		/* Save the sqelch bit */
		अगर ((i & LOW_RX_SQUELCH) == LOW_RX_SQUELCH)
			lp->adapter_cnf |= A_CNF_EXTND_10B_2 | A_CNF_LOW_RX_SQUELCH;
		/* Check अगर the card is in 10Base-t only mode */
		अगर ((i & (AUI_ONLY | AUTO_AUI_10BASET)) == 0)
			lp->adapter_cnf |=  A_CNF_10B_T | A_CNF_MEDIA_10B_T;
		/* Check अगर the card is in AUI only mode */
		अगर ((i & (AUI_ONLY | AUTO_AUI_10BASET)) == AUI_ONLY)
			lp->adapter_cnf |=  A_CNF_AUI | A_CNF_MEDIA_AUI;
		/* Check अगर the card is in Auto mode. */
		अगर ((i & (AUI_ONLY | AUTO_AUI_10BASET)) == AUTO_AUI_10BASET)
			lp->adapter_cnf |=  A_CNF_AUI | A_CNF_10B_T |
				A_CNF_MEDIA_AUI | A_CNF_MEDIA_10B_T | A_CNF_MEDIA_AUTO;

		cs89_dbg(1, info, "%s: PP_LineCTL=0x%x, adapter_cnf=0x%x\n",
			 dev->name, i, lp->adapter_cnf);

		/* IRQ. Other chips alपढ़ोy probe, see below. */
		अगर (lp->chip_type == CS8900)
			lp->isa_config = पढ़ोreg(dev, PP_CS8900_ISAINT) & INT_NO_MASK;

		pr_cont("[Cirrus EEPROM] ");
	पूर्ण

	pr_cont("\n");

	/* First check to see अगर an EEPROM is attached. */

	अगर ((पढ़ोreg(dev, PP_SelfST) & EEPROM_PRESENT) == 0)
		pr_warn("No EEPROM, relying on command line....\n");
	अन्यथा अगर (get_eeprom_data(dev, START_EEPROM_DATA, CHKSUM_LEN, eeprom_buff) < 0) अणु
		pr_warn("EEPROM read failed, relying on command line\n");
	पूर्ण अन्यथा अगर (get_eeprom_cksum(START_EEPROM_DATA, CHKSUM_LEN, eeprom_buff) < 0) अणु
		/* Check अगर the chip was able to पढ़ो its own configuration starting
		   at 0 in the EEPROM*/
		अगर ((पढ़ोreg(dev, PP_SelfST) & (EEPROM_OK | EEPROM_PRESENT)) !=
		    (EEPROM_OK | EEPROM_PRESENT))
			pr_warn("Extended EEPROM checksum bad and no Cirrus EEPROM, relying on command line\n");

	पूर्ण अन्यथा अणु
		/* This पढ़ोs an extended EEPROM that is not करोcumented
		 * in the CS8900 datasheet.
		 */

		/* get transmission control word  but keep the स्वतःnegotiation bits */
		अगर (!lp->स्वतः_neg_cnf)
			lp->स्वतः_neg_cnf = eeprom_buff[AUTO_NEG_CNF_OFFSET / 2];
		/* Store adapter configuration */
		अगर (!lp->adapter_cnf)
			lp->adapter_cnf = eeprom_buff[ADAPTER_CNF_OFFSET / 2];
		/* Store ISA configuration */
		lp->isa_config = eeprom_buff[ISA_CNF_OFFSET / 2];
		dev->mem_start = eeprom_buff[PACKET_PAGE_OFFSET / 2] << 8;

		/* eeprom_buff has 32-bit पूर्णांकs, so we can't just स_नकल it */
		/* store the initial memory base address */
		क्रम (i = 0; i < ETH_ALEN / 2; i++) अणु
			dev->dev_addr[i * 2] = eeprom_buff[i];
			dev->dev_addr[i * 2 + 1] = eeprom_buff[i] >> 8;
		पूर्ण
		cs89_dbg(1, debug, "%s: new adapter_cnf: 0x%x\n",
			 dev->name, lp->adapter_cnf);
	पूर्ण

	/* allow them to क्रमce multiple transceivers.  If they क्रमce multiple, स्वतःsense */
	अणु
		पूर्णांक count = 0;
		अगर (lp->क्रमce & FORCE_RJ45) अणु
			lp->adapter_cnf |= A_CNF_10B_T;
			count++;
		पूर्ण
		अगर (lp->क्रमce & FORCE_AUI) अणु
			lp->adapter_cnf |= A_CNF_AUI;
			count++;
		पूर्ण
		अगर (lp->क्रमce & FORCE_BNC) अणु
			lp->adapter_cnf |= A_CNF_10B_2;
			count++;
		पूर्ण
		अगर (count > 1)
			lp->adapter_cnf |= A_CNF_MEDIA_AUTO;
		अन्यथा अगर (lp->क्रमce & FORCE_RJ45)
			lp->adapter_cnf |= A_CNF_MEDIA_10B_T;
		अन्यथा अगर (lp->क्रमce & FORCE_AUI)
			lp->adapter_cnf |= A_CNF_MEDIA_AUI;
		अन्यथा अगर (lp->क्रमce & FORCE_BNC)
			lp->adapter_cnf |= A_CNF_MEDIA_10B_2;
	पूर्ण

	cs89_dbg(1, debug, "%s: after force 0x%x, adapter_cnf=0x%x\n",
		 dev->name, lp->क्रमce, lp->adapter_cnf);

	/* FIXME: We करोn't let you set dc-dc polarity or low RX squelch from the command line: add it here */

	/* FIXME: We करोn't let you set the IMM bit from the command line: add it to lp->स्वतः_neg_cnf here */

	/* FIXME: we करोn't set the Ethernet address on the command line.  Use
	 * अगरconfig IFACE hw ether AABBCCDDEEFF
	 */

	pr_info("media %s%s%s",
		(lp->adapter_cnf & A_CNF_10B_T) ? "RJ-45," : "",
		(lp->adapter_cnf & A_CNF_AUI) ? "AUI," : "",
		(lp->adapter_cnf & A_CNF_10B_2) ? "BNC," : "");

	lp->irq_map = 0xffff;

	/* If this is a CS8900 then no pnp soft */
	अगर (lp->chip_type != CS8900 &&
	    /* Check अगर the ISA IRQ has been set  */
	    (i = पढ़ोreg(dev, PP_CS8920_ISAINT) & 0xff,
	     (i != 0 && i < CS8920_NO_INTS))) अणु
		अगर (!dev->irq)
			dev->irq = i;
	पूर्ण अन्यथा अणु
		i = lp->isa_config & INT_NO_MASK;
#अगर_अघोषित CONFIG_CS89x0_PLATFORM
		अगर (lp->chip_type == CS8900) अणु
			/* Translate the IRQ using the IRQ mapping table. */
			अगर (i >= ARRAY_SIZE(cs8900_irq_map))
				pr_err("invalid ISA interrupt number %d\n", i);
			अन्यथा
				i = cs8900_irq_map[i];

			lp->irq_map = CS8900_IRQ_MAP; /* fixed IRQ map क्रम CS8900 */
		पूर्ण अन्यथा अणु
			पूर्णांक irq_map_buff[IRQ_MAP_LEN/2];

			अगर (get_eeprom_data(dev, IRQ_MAP_EEPROM_DATA,
					    IRQ_MAP_LEN / 2,
					    irq_map_buff) >= 0) अणु
				अगर ((irq_map_buff[0] & 0xff) == PNP_IRQ_FRMT)
					lp->irq_map = ((irq_map_buff[0] >> 8) |
						       (irq_map_buff[1] << 8));
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		अगर (!dev->irq)
			dev->irq = i;
	पूर्ण

	pr_cont(" IRQ %d", dev->irq);

#अगर ALLOW_DMA
	अगर (lp->use_dma) अणु
		get_dma_channel(dev);
		pr_cont(", DMA %d", dev->dma);
	पूर्ण अन्यथा
#पूर्ण_अगर
		pr_cont(", programmed I/O");

	/* prपूर्णांक the ethernet address. */
	pr_cont(", MAC %pM\n", dev->dev_addr);

	dev->netdev_ops	= &net_ops;
	dev->watchकरोg_समयo = HZ;

	cs89_dbg(0, info, "cs89x0_probe1() successful\n");

	retval = रेजिस्टर_netdev(dev);
	अगर (retval)
		जाओ out2;
	वापस 0;
out2:
	ioग_लिखो16(PP_ChipID, lp->virt_addr + ADD_PORT);
out1:
	वापस retval;
पूर्ण

#अगर_अघोषित CONFIG_CS89x0_PLATFORM
/*
 * This function converts the I/O port address used by the cs89x0_probe() and
 * init_module() functions to the I/O memory address used by the
 * cs89x0_probe1() function.
 */
अटल पूर्णांक __init
cs89x0_ioport_probe(काष्ठा net_device *dev, अचिन्हित दीर्घ ioport, पूर्णांक modular)
अणु
	काष्ठा net_local *lp = netdev_priv(dev);
	पूर्णांक ret;
	व्योम __iomem *io_mem;

	अगर (!lp)
		वापस -ENOMEM;

	dev->base_addr = ioport;

	अगर (!request_region(ioport, NETCARD_IO_EXTENT, DRV_NAME)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	io_mem = ioport_map(ioport & ~3, NETCARD_IO_EXTENT);
	अगर (!io_mem) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	/* अगर they give us an odd I/O address, then करो ONE ग_लिखो to
	 * the address port, to get it back to address zero, where we
	 * expect to find the EISA signature word. An IO with a base of 0x3
	 * will skip the test क्रम the ADD_PORT.
	 */
	अगर (ioport & 1) अणु
		cs89_dbg(1, info, "%s: odd ioaddr 0x%lx\n", dev->name, ioport);
		अगर ((ioport & 2) != 2) अणु
			अगर ((ioपढ़ो16(io_mem + ADD_PORT) & ADD_MASK) !=
			    ADD_SIG) अणु
				pr_err("%s: bad signature 0x%x\n",
				       dev->name, ioपढ़ो16(io_mem + ADD_PORT));
				ret = -ENODEV;
				जाओ unmap;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = cs89x0_probe1(dev, io_mem, modular);
	अगर (!ret)
		जाओ out;
unmap:
	ioport_unmap(io_mem);
release:
	release_region(ioport, NETCARD_IO_EXTENT);
out:
	वापस ret;
पूर्ण

#अगर_अघोषित MODULE
/* Check क्रम a network adaptor of this type, and वापस '0' अगरf one exists.
 * If dev->base_addr == 0, probe all likely locations.
 * If dev->base_addr == 1, always वापस failure.
 * If dev->base_addr == 2, allocate space क्रम the device and वापस success
 * (detachable devices only).
 * Return 0 on success.
 */

काष्ठा net_device * __init cs89x0_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev = alloc_etherdev(माप(काष्ठा net_local));
	अचिन्हित *port;
	पूर्णांक err = 0;
	पूर्णांक irq;
	पूर्णांक io;

	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	प्र_लिखो(dev->name, "eth%d", unit);
	netdev_boot_setup_check(dev);
	io = dev->base_addr;
	irq = dev->irq;

	cs89_dbg(0, info, "cs89x0_probe(0x%x)\n", io);

	अगर (io > 0x1ff)	अणु	/* Check a single specअगरied location. */
		err = cs89x0_ioport_probe(dev, io, 0);
	पूर्ण अन्यथा अगर (io != 0) अणु	/* Don't probe at all. */
		err = -ENXIO;
	पूर्ण अन्यथा अणु
		क्रम (port = netcard_portlist; *port; port++) अणु
			अगर (cs89x0_ioport_probe(dev, *port, 0) == 0)
				अवरोध;
			dev->irq = irq;
		पूर्ण
		अगर (!*port)
			err = -ENODEV;
	पूर्ण
	अगर (err)
		जाओ out;
	वापस dev;
out:
	मुक्त_netdev(dev);
	pr_warn("no cs8900 or cs8920 detected.  Be sure to disable PnP with SETUP\n");
	वापस ERR_PTR(err);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर defined(MODULE) && !defined(CONFIG_CS89x0_PLATFORM)

अटल काष्ठा net_device *dev_cs89x0;

/* Support the 'debug' module parm even if we're compiled क्रम non-debug to
 * aव्योम अवरोधing someone's startup scripts
 */

अटल पूर्णांक io;
अटल पूर्णांक irq;
अटल पूर्णांक debug;
अटल अक्षर media[8];
अटल पूर्णांक duplex = -1;

अटल पूर्णांक use_dma;			/* These generate unused var warnings अगर ALLOW_DMA = 0 */
अटल पूर्णांक dma;
अटल पूर्णांक dmasize = 16;		/* or 64 */

module_param_hw(io, पूर्णांक, ioport, 0);
module_param_hw(irq, पूर्णांक, irq, 0);
module_param(debug, पूर्णांक, 0);
module_param_string(media, media, माप(media), 0);
module_param(duplex, पूर्णांक, 0);
module_param_hw(dma , पूर्णांक, dma, 0);
module_param(dmasize , पूर्णांक, 0);
module_param(use_dma , पूर्णांक, 0);
MODULE_PARM_DESC(io, "cs89x0 I/O base address");
MODULE_PARM_DESC(irq, "cs89x0 IRQ number");
#अगर DEBUGGING
MODULE_PARM_DESC(debug, "cs89x0 debug level (0-6)");
#अन्यथा
MODULE_PARM_DESC(debug, "(ignored)");
#पूर्ण_अगर
MODULE_PARM_DESC(media, "Set cs89x0 adapter(s) media type(s) (rj45,bnc,aui)");
/* No other value than -1 क्रम duplex seems to be currently पूर्णांकerpreted */
MODULE_PARM_DESC(duplex, "(ignored)");
#अगर ALLOW_DMA
MODULE_PARM_DESC(dma , "cs89x0 ISA DMA channel; ignored if use_dma=0");
MODULE_PARM_DESC(dmasize , "cs89x0 DMA size in kB (16,64); ignored if use_dma=0");
MODULE_PARM_DESC(use_dma , "cs89x0 using DMA (0-1)");
#अन्यथा
MODULE_PARM_DESC(dma , "(ignored)");
MODULE_PARM_DESC(dmasize , "(ignored)");
MODULE_PARM_DESC(use_dma , "(ignored)");
#पूर्ण_अगर

MODULE_AUTHOR("Mike Cruse, Russwll Nelson <nelson@crynwr.com>, Andrew Morton");
MODULE_LICENSE("GPL");

/*
 * media=t             - specअगरy media type
 * or media=2
 * or media=aui
 * or medai=स्वतः
 * duplex=0            - specअगरy क्रमced half/full/स्वतःnegotiate duplex
 * debug=#             - debug level
 *
 * Default Chip Configuration:
 * DMA Burst = enabled
 * IOCHRDY Enabled = enabled
 * UseSA = enabled
 * CS8900 शेषs to half-duplex अगर not specअगरied on command-line
 * CS8920 शेषs to स्वतःneg अगर not specअगरied on command-line
 * Use reset शेषs क्रम other config parameters
 *
 * Assumptions:
 * media type specअगरied is supported (circuitry is present)
 * अगर memory address is > 1MB, then required mem decode hw is present
 * अगर 10B-2, then agent other than driver will enable DC/DC converter
 * (hw or software util)
 */

पूर्णांक __init init_module(व्योम)
अणु
	काष्ठा net_device *dev = alloc_etherdev(माप(काष्ठा net_local));
	काष्ठा net_local *lp;
	पूर्णांक ret = 0;

#अगर DEBUGGING
	net_debug = debug;
#अन्यथा
	debug = 0;
#पूर्ण_अगर
	अगर (!dev)
		वापस -ENOMEM;

	dev->irq = irq;
	dev->base_addr = io;
	lp = netdev_priv(dev);

#अगर ALLOW_DMA
	अगर (use_dma) अणु
		lp->use_dma = use_dma;
		lp->dma = dma;
		lp->dmasize = dmasize;
	पूर्ण
#पूर्ण_अगर

	spin_lock_init(&lp->lock);

	/* boy, they'd better get these right */
	अगर (!म_भेद(media, "rj45"))
		lp->adapter_cnf = A_CNF_MEDIA_10B_T | A_CNF_10B_T;
	अन्यथा अगर (!म_भेद(media, "aui"))
		lp->adapter_cnf = A_CNF_MEDIA_AUI   | A_CNF_AUI;
	अन्यथा अगर (!म_भेद(media, "bnc"))
		lp->adapter_cnf = A_CNF_MEDIA_10B_2 | A_CNF_10B_2;
	अन्यथा
		lp->adapter_cnf = A_CNF_MEDIA_10B_T | A_CNF_10B_T;

	अगर (duplex == -1)
		lp->स्वतः_neg_cnf = AUTO_NEG_ENABLE;

	अगर (io == 0) अणु
		pr_err("Module autoprobing not allowed\n");
		pr_err("Append io=0xNNN\n");
		ret = -EPERM;
		जाओ out;
	पूर्ण अन्यथा अगर (io <= 0x1ff) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

#अगर ALLOW_DMA
	अगर (use_dma && dmasize != 16 && dmasize != 64) अणु
		pr_err("dma size must be either 16K or 64K, not %dK\n",
		       dmasize);
		ret = -EPERM;
		जाओ out;
	पूर्ण
#पूर्ण_अगर
	ret = cs89x0_ioport_probe(dev, io, 1);
	अगर (ret)
		जाओ out;

	dev_cs89x0 = dev;
	वापस 0;
out:
	मुक्त_netdev(dev);
	वापस ret;
पूर्ण

व्योम __निकास
cleanup_module(व्योम)
अणु
	काष्ठा net_local *lp = netdev_priv(dev_cs89x0);

	unरेजिस्टर_netdev(dev_cs89x0);
	ioग_लिखो16(PP_ChipID, lp->virt_addr + ADD_PORT);
	ioport_unmap(lp->virt_addr);
	release_region(dev_cs89x0->base_addr, NETCARD_IO_EXTENT);
	मुक्त_netdev(dev_cs89x0);
पूर्ण
#पूर्ण_अगर /* MODULE && !CONFIG_CS89x0_PLATFORM */

#अगर_घोषित CONFIG_CS89x0_PLATFORM
अटल पूर्णांक __init cs89x0_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = alloc_etherdev(माप(काष्ठा net_local));
	व्योम __iomem *virt_addr;
	पूर्णांक err;

	अगर (!dev)
		वापस -ENOMEM;

	dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dev->irq <= 0) अणु
		dev_warn(&dev->dev, "interrupt resource missing\n");
		err = -ENXIO;
		जाओ मुक्त;
	पूर्ण

	virt_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(virt_addr)) अणु
		err = PTR_ERR(virt_addr);
		जाओ मुक्त;
	पूर्ण

	err = cs89x0_probe1(dev, virt_addr, 0);
	अगर (err) अणु
		dev_warn(&dev->dev, "no cs8900 or cs8920 detected\n");
		जाओ मुक्त;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);
	वापस 0;

मुक्त:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक cs89x0_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	/* This platक्रमm_get_resource() call will not वापस शून्य, because
	 * the same call in cs89x0_platक्रमm_probe() has वापसed a non शून्य
	 * value.
	 */
	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused cs89x0_match[] = अणु
	अणु .compatible = "cirrus,cs8900", पूर्ण,
	अणु .compatible = "cirrus,cs8920", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cs89x0_match);

अटल काष्ठा platक्रमm_driver cs89x0_driver = अणु
	.driver	= अणु
		.name		= DRV_NAME,
		.of_match_table	= of_match_ptr(cs89x0_match),
	पूर्ण,
	.हटाओ	= cs89x0_platक्रमm_हटाओ,
पूर्ण;

module_platक्रमm_driver_probe(cs89x0_driver, cs89x0_platक्रमm_probe);

#पूर्ण_अगर /* CONFIG_CS89x0_PLATFORM */

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Crystal Semiconductor (Now Cirrus Logic) CS89[02]0 network driver");
MODULE_AUTHOR("Russell Nelson <nelson@crynwr.com>");
