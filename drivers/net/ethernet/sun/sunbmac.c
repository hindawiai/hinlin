<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sunbmac.c: Driver क्रम Sparc BigMAC 100baseT ethernet adapters.
 *
 * Copyright (C) 1997, 1998, 1999, 2003, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/module.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/auxपन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>

#समावेश "sunbmac.h"

#घोषणा DRV_NAME	"sunbmac"
#घोषणा DRV_VERSION	"2.1"
#घोषणा DRV_RELDATE	"August 26, 2008"
#घोषणा DRV_AUTHOR	"David S. Miller (davem@davemloft.net)"

अटल अक्षर version[] =
	DRV_NAME ".c:v" DRV_VERSION " " DRV_RELDATE " " DRV_AUTHOR "\n";

MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION("Sun BigMAC 100baseT ethernet driver");
MODULE_LICENSE("GPL");

#अघोषित DEBUG_PROBE
#अघोषित DEBUG_TX
#अघोषित DEBUG_IRQ

#अगर_घोषित DEBUG_PROBE
#घोषणा DP(x)  prपूर्णांकk x
#अन्यथा
#घोषणा DP(x)
#पूर्ण_अगर

#अगर_घोषित DEBUG_TX
#घोषणा DTX(x)  prपूर्णांकk x
#अन्यथा
#घोषणा DTX(x)
#पूर्ण_अगर

#अगर_घोषित DEBUG_IRQ
#घोषणा सूचीQ(x)  prपूर्णांकk x
#अन्यथा
#घोषणा सूचीQ(x)
#पूर्ण_अगर

#घोषणा DEFAULT_JAMSIZE    4 /* Toe jam */

#घोषणा QEC_RESET_TRIES 200

अटल पूर्णांक qec_global_reset(व्योम __iomem *gregs)
अणु
	पूर्णांक tries = QEC_RESET_TRIES;

	sbus_ग_लिखोl(GLOB_CTRL_RESET, gregs + GLOB_CTRL);
	जबतक (--tries) अणु
		अगर (sbus_पढ़ोl(gregs + GLOB_CTRL) & GLOB_CTRL_RESET) अणु
			udelay(20);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (tries)
		वापस 0;
	prपूर्णांकk(KERN_ERR "BigMAC: Cannot reset the QEC.\n");
	वापस -1;
पूर्ण

अटल व्योम qec_init(काष्ठा bigmac *bp)
अणु
	काष्ठा platक्रमm_device *qec_op = bp->qec_op;
	व्योम __iomem *gregs = bp->gregs;
	u8 bsizes = bp->bigmac_bursts;
	u32 regval;

	/* 64byte bursts करो not work at the moment, करो
	 * not even try to enable them.  -DaveM
	 */
	अगर (bsizes & DMA_BURST32)
		regval = GLOB_CTRL_B32;
	अन्यथा
		regval = GLOB_CTRL_B16;
	sbus_ग_लिखोl(regval | GLOB_CTRL_BMODE, gregs + GLOB_CTRL);
	sbus_ग_लिखोl(GLOB_PSIZE_2048, gregs + GLOB_PSIZE);

	/* All of memsize is given to bigmac. */
	sbus_ग_लिखोl(resource_size(&qec_op->resource[1]),
		    gregs + GLOB_MSIZE);

	/* Half to the transmitter, half to the receiver. */
	sbus_ग_लिखोl(resource_size(&qec_op->resource[1]) >> 1,
		    gregs + GLOB_TSIZE);
	sbus_ग_लिखोl(resource_size(&qec_op->resource[1]) >> 1,
		    gregs + GLOB_RSIZE);
पूर्ण

#घोषणा TX_RESET_TRIES     32
#घोषणा RX_RESET_TRIES     32

अटल व्योम bigmac_tx_reset(व्योम __iomem *bregs)
अणु
	पूर्णांक tries = TX_RESET_TRIES;

	sbus_ग_लिखोl(0, bregs + BMAC_TXCFG);

	/* The fअगरo threshold bit is पढ़ो-only and करोes
	 * not clear.  -DaveM
	 */
	जबतक ((sbus_पढ़ोl(bregs + BMAC_TXCFG) & ~(BIGMAC_TXCFG_FIFO)) != 0 &&
	       --tries != 0)
		udelay(20);

	अगर (!tries) अणु
		prपूर्णांकk(KERN_ERR "BIGMAC: Transmitter will not reset.\n");
		prपूर्णांकk(KERN_ERR "BIGMAC: tx_cfg is %08x\n",
		       sbus_पढ़ोl(bregs + BMAC_TXCFG));
	पूर्ण
पूर्ण

अटल व्योम bigmac_rx_reset(व्योम __iomem *bregs)
अणु
	पूर्णांक tries = RX_RESET_TRIES;

	sbus_ग_लिखोl(0, bregs + BMAC_RXCFG);
	जबतक (sbus_पढ़ोl(bregs + BMAC_RXCFG) && --tries)
		udelay(20);

	अगर (!tries) अणु
		prपूर्णांकk(KERN_ERR "BIGMAC: Receiver will not reset.\n");
		prपूर्णांकk(KERN_ERR "BIGMAC: rx_cfg is %08x\n",
		       sbus_पढ़ोl(bregs + BMAC_RXCFG));
	पूर्ण
पूर्ण

/* Reset the transmitter and receiver. */
अटल व्योम bigmac_stop(काष्ठा bigmac *bp)
अणु
	bigmac_tx_reset(bp->bregs);
	bigmac_rx_reset(bp->bregs);
पूर्ण

अटल व्योम bigmac_get_counters(काष्ठा bigmac *bp, व्योम __iomem *bregs)
अणु
	काष्ठा net_device_stats *stats = &bp->dev->stats;

	stats->rx_crc_errors += sbus_पढ़ोl(bregs + BMAC_RCRCECTR);
	sbus_ग_लिखोl(0, bregs + BMAC_RCRCECTR);

	stats->rx_frame_errors += sbus_पढ़ोl(bregs + BMAC_UNALECTR);
	sbus_ग_लिखोl(0, bregs + BMAC_UNALECTR);

	stats->rx_length_errors += sbus_पढ़ोl(bregs + BMAC_GLECTR);
	sbus_ग_लिखोl(0, bregs + BMAC_GLECTR);

	stats->tx_पातed_errors += sbus_पढ़ोl(bregs + BMAC_EXCTR);

	stats->collisions +=
		(sbus_पढ़ोl(bregs + BMAC_EXCTR) +
		 sbus_पढ़ोl(bregs + BMAC_LTCTR));
	sbus_ग_लिखोl(0, bregs + BMAC_EXCTR);
	sbus_ग_लिखोl(0, bregs + BMAC_LTCTR);
पूर्ण

अटल व्योम bigmac_clean_rings(काष्ठा bigmac *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		अगर (bp->rx_skbs[i] != शून्य) अणु
			dev_kमुक्त_skb_any(bp->rx_skbs[i]);
			bp->rx_skbs[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		अगर (bp->tx_skbs[i] != शून्य) अणु
			dev_kमुक्त_skb_any(bp->tx_skbs[i]);
			bp->tx_skbs[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bigmac_init_rings(काष्ठा bigmac *bp, bool non_blocking)
अणु
	काष्ठा bmac_init_block *bb = bp->bmac_block;
	पूर्णांक i;
	gfp_t gfp_flags = GFP_KERNEL;

	अगर (non_blocking)
		gfp_flags = GFP_ATOMIC;

	bp->rx_new = bp->rx_old = bp->tx_new = bp->tx_old = 0;

	/* Free any skippy bufs left around in the rings. */
	bigmac_clean_rings(bp);

	/* Now get new skbufs क्रम the receive ring. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb;

		skb = big_mac_alloc_skb(RX_BUF_ALLOC_SIZE, gfp_flags);
		अगर (!skb)
			जारी;

		bp->rx_skbs[i] = skb;

		/* Because we reserve afterwards. */
		skb_put(skb, ETH_FRAME_LEN);
		skb_reserve(skb, 34);

		bb->be_rxd[i].rx_addr =
			dma_map_single(&bp->bigmac_op->dev,
				       skb->data,
				       RX_BUF_ALLOC_SIZE - 34,
				       DMA_FROM_DEVICE);
		bb->be_rxd[i].rx_flags =
			(RXD_OWN | ((RX_BUF_ALLOC_SIZE - 34) & RXD_LENGTH));
	पूर्ण

	क्रम (i = 0; i < TX_RING_SIZE; i++)
		bb->be_txd[i].tx_flags = bb->be_txd[i].tx_addr = 0;
पूर्ण

#घोषणा MGMT_CLKON  (MGMT_PAL_INT_MDIO|MGMT_PAL_EXT_MDIO|MGMT_PAL_OENAB|MGMT_PAL_DCLOCK)
#घोषणा MGMT_CLKOFF (MGMT_PAL_INT_MDIO|MGMT_PAL_EXT_MDIO|MGMT_PAL_OENAB)

अटल व्योम idle_transceiver(व्योम __iomem *tregs)
अणु
	पूर्णांक i = 20;

	जबतक (i--) अणु
		sbus_ग_लिखोl(MGMT_CLKOFF, tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
		sbus_ग_लिखोl(MGMT_CLKON, tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_tcvr_bit(काष्ठा bigmac *bp, व्योम __iomem *tregs, पूर्णांक bit)
अणु
	अगर (bp->tcvr_type == पूर्णांकernal) अणु
		bit = (bit & 1) << 3;
		sbus_ग_लिखोl(bit | (MGMT_PAL_OENAB | MGMT_PAL_EXT_MDIO),
			    tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
		sbus_ग_लिखोl(bit | MGMT_PAL_OENAB | MGMT_PAL_EXT_MDIO | MGMT_PAL_DCLOCK,
			    tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
	पूर्ण अन्यथा अगर (bp->tcvr_type == बाह्यal) अणु
		bit = (bit & 1) << 2;
		sbus_ग_लिखोl(bit | MGMT_PAL_INT_MDIO | MGMT_PAL_OENAB,
			    tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
		sbus_ग_लिखोl(bit | MGMT_PAL_INT_MDIO | MGMT_PAL_OENAB | MGMT_PAL_DCLOCK,
			    tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "write_tcvr_bit: No transceiver type known!\n");
	पूर्ण
पूर्ण

अटल पूर्णांक पढ़ो_tcvr_bit(काष्ठा bigmac *bp, व्योम __iomem *tregs)
अणु
	पूर्णांक retval = 0;

	अगर (bp->tcvr_type == पूर्णांकernal) अणु
		sbus_ग_लिखोl(MGMT_PAL_EXT_MDIO, tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
		sbus_ग_लिखोl(MGMT_PAL_EXT_MDIO | MGMT_PAL_DCLOCK,
			    tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
		retval = (sbus_पढ़ोl(tregs + TCVR_MPAL) & MGMT_PAL_INT_MDIO) >> 3;
	पूर्ण अन्यथा अगर (bp->tcvr_type == बाह्यal) अणु
		sbus_ग_लिखोl(MGMT_PAL_INT_MDIO, tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
		sbus_ग_लिखोl(MGMT_PAL_INT_MDIO | MGMT_PAL_DCLOCK, tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
		retval = (sbus_पढ़ोl(tregs + TCVR_MPAL) & MGMT_PAL_EXT_MDIO) >> 2;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "read_tcvr_bit: No transceiver type known!\n");
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक पढ़ो_tcvr_bit2(काष्ठा bigmac *bp, व्योम __iomem *tregs)
अणु
	पूर्णांक retval = 0;

	अगर (bp->tcvr_type == पूर्णांकernal) अणु
		sbus_ग_लिखोl(MGMT_PAL_EXT_MDIO, tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
		retval = (sbus_पढ़ोl(tregs + TCVR_MPAL) & MGMT_PAL_INT_MDIO) >> 3;
		sbus_ग_लिखोl(MGMT_PAL_EXT_MDIO | MGMT_PAL_DCLOCK, tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
	पूर्ण अन्यथा अगर (bp->tcvr_type == बाह्यal) अणु
		sbus_ग_लिखोl(MGMT_PAL_INT_MDIO, tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
		retval = (sbus_पढ़ोl(tregs + TCVR_MPAL) & MGMT_PAL_EXT_MDIO) >> 2;
		sbus_ग_लिखोl(MGMT_PAL_INT_MDIO | MGMT_PAL_DCLOCK, tregs + TCVR_MPAL);
		sbus_पढ़ोl(tregs + TCVR_MPAL);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "read_tcvr_bit2: No transceiver type known!\n");
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम put_tcvr_byte(काष्ठा bigmac *bp,
			  व्योम __iomem *tregs,
			  अचिन्हित पूर्णांक byte)
अणु
	पूर्णांक shअगरt = 4;

	करो अणु
		ग_लिखो_tcvr_bit(bp, tregs, ((byte >> shअगरt) & 1));
		shअगरt -= 1;
	पूर्ण जबतक (shअगरt >= 0);
पूर्ण

अटल व्योम bigmac_tcvr_ग_लिखो(काष्ठा bigmac *bp, व्योम __iomem *tregs,
			      पूर्णांक reg, अचिन्हित लघु val)
अणु
	पूर्णांक shअगरt;

	reg &= 0xff;
	val &= 0xffff;
	चयन(bp->tcvr_type) अणु
	हाल पूर्णांकernal:
	हाल बाह्यal:
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "bigmac_tcvr_read: Whoops, no known transceiver type.\n");
		वापस;
	पूर्ण

	idle_transceiver(tregs);
	ग_लिखो_tcvr_bit(bp, tregs, 0);
	ग_लिखो_tcvr_bit(bp, tregs, 1);
	ग_लिखो_tcvr_bit(bp, tregs, 0);
	ग_लिखो_tcvr_bit(bp, tregs, 1);

	put_tcvr_byte(bp, tregs,
		      ((bp->tcvr_type == पूर्णांकernal) ?
		       BIGMAC_PHY_INTERNAL : BIGMAC_PHY_EXTERNAL));

	put_tcvr_byte(bp, tregs, reg);

	ग_लिखो_tcvr_bit(bp, tregs, 1);
	ग_लिखो_tcvr_bit(bp, tregs, 0);

	shअगरt = 15;
	करो अणु
		ग_लिखो_tcvr_bit(bp, tregs, (val >> shअगरt) & 1);
		shअगरt -= 1;
	पूर्ण जबतक (shअगरt >= 0);
पूर्ण

अटल अचिन्हित लघु bigmac_tcvr_पढ़ो(काष्ठा bigmac *bp,
				       व्योम __iomem *tregs,
				       पूर्णांक reg)
अणु
	अचिन्हित लघु retval = 0;

	reg &= 0xff;
	चयन(bp->tcvr_type) अणु
	हाल पूर्णांकernal:
	हाल बाह्यal:
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "bigmac_tcvr_read: Whoops, no known transceiver type.\n");
		वापस 0xffff;
	पूर्ण

	idle_transceiver(tregs);
	ग_लिखो_tcvr_bit(bp, tregs, 0);
	ग_लिखो_tcvr_bit(bp, tregs, 1);
	ग_लिखो_tcvr_bit(bp, tregs, 1);
	ग_लिखो_tcvr_bit(bp, tregs, 0);

	put_tcvr_byte(bp, tregs,
		      ((bp->tcvr_type == पूर्णांकernal) ?
		       BIGMAC_PHY_INTERNAL : BIGMAC_PHY_EXTERNAL));

	put_tcvr_byte(bp, tregs, reg);

	अगर (bp->tcvr_type == बाह्यal) अणु
		पूर्णांक shअगरt = 15;

		(व्योम) पढ़ो_tcvr_bit2(bp, tregs);
		(व्योम) पढ़ो_tcvr_bit2(bp, tregs);

		करो अणु
			पूर्णांक पंचांगp;

			पंचांगp = पढ़ो_tcvr_bit2(bp, tregs);
			retval |= ((पंचांगp & 1) << shअगरt);
			shअगरt -= 1;
		पूर्ण जबतक (shअगरt >= 0);

		(व्योम) पढ़ो_tcvr_bit2(bp, tregs);
		(व्योम) पढ़ो_tcvr_bit2(bp, tregs);
		(व्योम) पढ़ो_tcvr_bit2(bp, tregs);
	पूर्ण अन्यथा अणु
		पूर्णांक shअगरt = 15;

		(व्योम) पढ़ो_tcvr_bit(bp, tregs);
		(व्योम) पढ़ो_tcvr_bit(bp, tregs);

		करो अणु
			पूर्णांक पंचांगp;

			पंचांगp = पढ़ो_tcvr_bit(bp, tregs);
			retval |= ((पंचांगp & 1) << shअगरt);
			shअगरt -= 1;
		पूर्ण जबतक (shअगरt >= 0);

		(व्योम) पढ़ो_tcvr_bit(bp, tregs);
		(व्योम) पढ़ो_tcvr_bit(bp, tregs);
		(व्योम) पढ़ो_tcvr_bit(bp, tregs);
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम bigmac_tcvr_init(काष्ठा bigmac *bp)
अणु
	व्योम __iomem *tregs = bp->tregs;
	u32 mpal;

	idle_transceiver(tregs);
	sbus_ग_लिखोl(MGMT_PAL_INT_MDIO | MGMT_PAL_EXT_MDIO | MGMT_PAL_DCLOCK,
		    tregs + TCVR_MPAL);
	sbus_पढ़ोl(tregs + TCVR_MPAL);

	/* Only the bit क्रम the present transceiver (पूर्णांकernal or
	 * बाह्यal) will stick, set them both and see what stays.
	 */
	sbus_ग_लिखोl(MGMT_PAL_INT_MDIO | MGMT_PAL_EXT_MDIO, tregs + TCVR_MPAL);
	sbus_पढ़ोl(tregs + TCVR_MPAL);
	udelay(20);

	mpal = sbus_पढ़ोl(tregs + TCVR_MPAL);
	अगर (mpal & MGMT_PAL_EXT_MDIO) अणु
		bp->tcvr_type = बाह्यal;
		sbus_ग_लिखोl(~(TCVR_PAL_EXTLBACK | TCVR_PAL_MSENSE | TCVR_PAL_LTENABLE),
			    tregs + TCVR_TPAL);
		sbus_पढ़ोl(tregs + TCVR_TPAL);
	पूर्ण अन्यथा अगर (mpal & MGMT_PAL_INT_MDIO) अणु
		bp->tcvr_type = पूर्णांकernal;
		sbus_ग_लिखोl(~(TCVR_PAL_SERIAL | TCVR_PAL_EXTLBACK |
			      TCVR_PAL_MSENSE | TCVR_PAL_LTENABLE),
			    tregs + TCVR_TPAL);
		sbus_पढ़ोl(tregs + TCVR_TPAL);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "BIGMAC: AIEEE, neither internal nor "
		       "external MDIO available!\n");
		prपूर्णांकk(KERN_ERR "BIGMAC: mgmt_pal[%08x] tcvr_pal[%08x]\n",
		       sbus_पढ़ोl(tregs + TCVR_MPAL),
		       sbus_पढ़ोl(tregs + TCVR_TPAL));
	पूर्ण
पूर्ण

अटल पूर्णांक bigmac_init_hw(काष्ठा bigmac *, bool);

अटल पूर्णांक try_next_permutation(काष्ठा bigmac *bp, व्योम __iomem *tregs)
अणु
	अगर (bp->sw_bmcr & BMCR_SPEED100) अणु
		पूर्णांक समयout;

		/* Reset the PHY. */
		bp->sw_bmcr	= (BMCR_ISOLATE | BMCR_PDOWN | BMCR_LOOPBACK);
		bigmac_tcvr_ग_लिखो(bp, tregs, MII_BMCR, bp->sw_bmcr);
		bp->sw_bmcr	= (BMCR_RESET);
		bigmac_tcvr_ग_लिखो(bp, tregs, MII_BMCR, bp->sw_bmcr);

		समयout = 64;
		जबतक (--समयout) अणु
			bp->sw_bmcr = bigmac_tcvr_पढ़ो(bp, tregs, MII_BMCR);
			अगर ((bp->sw_bmcr & BMCR_RESET) == 0)
				अवरोध;
			udelay(20);
		पूर्ण
		अगर (समयout == 0)
			prपूर्णांकk(KERN_ERR "%s: PHY reset failed.\n", bp->dev->name);

		bp->sw_bmcr = bigmac_tcvr_पढ़ो(bp, tregs, MII_BMCR);

		/* Now we try 10baseT. */
		bp->sw_bmcr &= ~(BMCR_SPEED100);
		bigmac_tcvr_ग_लिखो(bp, tregs, MII_BMCR, bp->sw_bmcr);
		वापस 0;
	पूर्ण

	/* We've tried them all. */
	वापस -1;
पूर्ण

अटल व्योम bigmac_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा bigmac *bp = from_समयr(bp, t, bigmac_समयr);
	व्योम __iomem *tregs = bp->tregs;
	पूर्णांक restart_समयr = 0;

	bp->समयr_ticks++;
	अगर (bp->समयr_state == ltryरुको) अणु
		bp->sw_bmsr = bigmac_tcvr_पढ़ो(bp, tregs, MII_BMSR);
		bp->sw_bmcr = bigmac_tcvr_पढ़ो(bp, tregs, MII_BMCR);
		अगर (bp->sw_bmsr & BMSR_LSTATUS) अणु
			prपूर्णांकk(KERN_INFO "%s: Link is now up at %s.\n",
			       bp->dev->name,
			       (bp->sw_bmcr & BMCR_SPEED100) ?
			       "100baseT" : "10baseT");
			bp->समयr_state = asleep;
			restart_समयr = 0;
		पूर्ण अन्यथा अणु
			अगर (bp->समयr_ticks >= 4) अणु
				पूर्णांक ret;

				ret = try_next_permutation(bp, tregs);
				अगर (ret == -1) अणु
					prपूर्णांकk(KERN_ERR "%s: Link down, cable problem?\n",
					       bp->dev->name);
					ret = bigmac_init_hw(bp, true);
					अगर (ret) अणु
						prपूर्णांकk(KERN_ERR "%s: Error, cannot re-init the "
						       "BigMAC.\n", bp->dev->name);
					पूर्ण
					वापस;
				पूर्ण
				bp->समयr_ticks = 0;
				restart_समयr = 1;
			पूर्ण अन्यथा अणु
				restart_समयr = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Can't happens.... */
		prपूर्णांकk(KERN_ERR "%s: Aieee, link timer is asleep but we got one anyways!\n",
		       bp->dev->name);
		restart_समयr = 0;
		bp->समयr_ticks = 0;
		bp->समयr_state = asleep; /* foo on you */
	पूर्ण

	अगर (restart_समयr != 0) अणु
		bp->bigmac_समयr.expires = jअगरfies + ((12 * HZ)/10); /* 1.2 sec. */
		add_समयr(&bp->bigmac_समयr);
	पूर्ण
पूर्ण

/* Well, really we just क्रमce the chip पूर्णांकo 100baseT then
 * 10baseT, each समय checking क्रम a link status.
 */
अटल व्योम bigmac_begin_स्वतः_negotiation(काष्ठा bigmac *bp)
अणु
	व्योम __iomem *tregs = bp->tregs;
	पूर्णांक समयout;

	/* Grab new software copies of PHY रेजिस्टरs. */
	bp->sw_bmsr	= bigmac_tcvr_पढ़ो(bp, tregs, MII_BMSR);
	bp->sw_bmcr	= bigmac_tcvr_पढ़ो(bp, tregs, MII_BMCR);

	/* Reset the PHY. */
	bp->sw_bmcr	= (BMCR_ISOLATE | BMCR_PDOWN | BMCR_LOOPBACK);
	bigmac_tcvr_ग_लिखो(bp, tregs, MII_BMCR, bp->sw_bmcr);
	bp->sw_bmcr	= (BMCR_RESET);
	bigmac_tcvr_ग_लिखो(bp, tregs, MII_BMCR, bp->sw_bmcr);

	समयout = 64;
	जबतक (--समयout) अणु
		bp->sw_bmcr = bigmac_tcvr_पढ़ो(bp, tregs, MII_BMCR);
		अगर ((bp->sw_bmcr & BMCR_RESET) == 0)
			अवरोध;
		udelay(20);
	पूर्ण
	अगर (समयout == 0)
		prपूर्णांकk(KERN_ERR "%s: PHY reset failed.\n", bp->dev->name);

	bp->sw_bmcr = bigmac_tcvr_पढ़ो(bp, tregs, MII_BMCR);

	/* First we try 100baseT. */
	bp->sw_bmcr |= BMCR_SPEED100;
	bigmac_tcvr_ग_लिखो(bp, tregs, MII_BMCR, bp->sw_bmcr);

	bp->समयr_state = ltryरुको;
	bp->समयr_ticks = 0;
	bp->bigmac_समयr.expires = jअगरfies + (12 * HZ) / 10;
	add_समयr(&bp->bigmac_समयr);
पूर्ण

अटल पूर्णांक bigmac_init_hw(काष्ठा bigmac *bp, bool non_blocking)
अणु
	व्योम __iomem *gregs        = bp->gregs;
	व्योम __iomem *cregs        = bp->creg;
	व्योम __iomem *bregs        = bp->bregs;
	__u32 bblk_dvma = (__u32)bp->bblock_dvma;
	अचिन्हित अक्षर *e = &bp->dev->dev_addr[0];

	/* Latch current counters पूर्णांकo statistics. */
	bigmac_get_counters(bp, bregs);

	/* Reset QEC. */
	qec_global_reset(gregs);

	/* Init QEC. */
	qec_init(bp);

	/* Alloc and reset the tx/rx descriptor chains. */
	bigmac_init_rings(bp, non_blocking);

	/* Initialize the PHY. */
	bigmac_tcvr_init(bp);

	/* Stop transmitter and receiver. */
	bigmac_stop(bp);

	/* Set hardware ethernet address. */
	sbus_ग_लिखोl(((e[4] << 8) | e[5]), bregs + BMAC_MACADDR2);
	sbus_ग_लिखोl(((e[2] << 8) | e[3]), bregs + BMAC_MACADDR1);
	sbus_ग_लिखोl(((e[0] << 8) | e[1]), bregs + BMAC_MACADDR0);

	/* Clear the hash table until mc upload occurs. */
	sbus_ग_लिखोl(0, bregs + BMAC_HTABLE3);
	sbus_ग_लिखोl(0, bregs + BMAC_HTABLE2);
	sbus_ग_लिखोl(0, bregs + BMAC_HTABLE1);
	sbus_ग_लिखोl(0, bregs + BMAC_HTABLE0);

	/* Enable Big Mac hash table filter. */
	sbus_ग_लिखोl(BIGMAC_RXCFG_HENABLE | BIGMAC_RXCFG_FIFO,
		    bregs + BMAC_RXCFG);
	udelay(20);

	/* Ok, configure the Big Mac transmitter. */
	sbus_ग_लिखोl(BIGMAC_TXCFG_FIFO, bregs + BMAC_TXCFG);

	/* The HME करोcs recommend to use the 10LSB of our MAC here. */
	sbus_ग_लिखोl(((e[5] | e[4] << 8) & 0x3ff),
		    bregs + BMAC_RSEED);

	/* Enable the output drivers no matter what. */
	sbus_ग_लिखोl(BIGMAC_XCFG_ODENABLE | BIGMAC_XCFG_RESV,
		    bregs + BMAC_XIFCFG);

	/* Tell the QEC where the ring descriptors are. */
	sbus_ग_लिखोl(bblk_dvma + bib_offset(be_rxd, 0),
		    cregs + CREG_RXDS);
	sbus_ग_लिखोl(bblk_dvma + bib_offset(be_txd, 0),
		    cregs + CREG_TXDS);

	/* Setup the FIFO poपूर्णांकers पूर्णांकo QEC local memory. */
	sbus_ग_लिखोl(0, cregs + CREG_RXRBUFPTR);
	sbus_ग_लिखोl(0, cregs + CREG_RXWBUFPTR);
	sbus_ग_लिखोl(sbus_पढ़ोl(gregs + GLOB_RSIZE),
		    cregs + CREG_TXRBUFPTR);
	sbus_ग_लिखोl(sbus_पढ़ोl(gregs + GLOB_RSIZE),
		    cregs + CREG_TXWBUFPTR);

	/* Tell bigmac what पूर्णांकerrupts we करोn't want to hear about. */
	sbus_ग_लिखोl(BIGMAC_IMASK_GOTFRAME | BIGMAC_IMASK_SENTFRAME,
		    bregs + BMAC_IMASK);

	/* Enable the various other irq's. */
	sbus_ग_लिखोl(0, cregs + CREG_RIMASK);
	sbus_ग_लिखोl(0, cregs + CREG_TIMASK);
	sbus_ग_लिखोl(0, cregs + CREG_QMASK);
	sbus_ग_लिखोl(0, cregs + CREG_BMASK);

	/* Set jam size to a reasonable शेष. */
	sbus_ग_लिखोl(DEFAULT_JAMSIZE, bregs + BMAC_JSIZE);

	/* Clear collision counter. */
	sbus_ग_लिखोl(0, cregs + CREG_CCNT);

	/* Enable transmitter and receiver. */
	sbus_ग_लिखोl(sbus_पढ़ोl(bregs + BMAC_TXCFG) | BIGMAC_TXCFG_ENABLE,
		    bregs + BMAC_TXCFG);
	sbus_ग_लिखोl(sbus_पढ़ोl(bregs + BMAC_RXCFG) | BIGMAC_RXCFG_ENABLE,
		    bregs + BMAC_RXCFG);

	/* Ok, start detecting link speed/duplex. */
	bigmac_begin_स्वतः_negotiation(bp);

	/* Success. */
	वापस 0;
पूर्ण

/* Error पूर्णांकerrupts get sent here. */
अटल व्योम bigmac_is_medium_rare(काष्ठा bigmac *bp, u32 qec_status, u32 bmac_status)
अणु
	prपूर्णांकk(KERN_ERR "bigmac_is_medium_rare: ");
	अगर (qec_status & (GLOB_STAT_ER | GLOB_STAT_BM)) अणु
		अगर (qec_status & GLOB_STAT_ER)
			prपूर्णांकk("QEC_ERROR, ");
		अगर (qec_status & GLOB_STAT_BM)
			prपूर्णांकk("QEC_BMAC_ERROR, ");
	पूर्ण
	अगर (bmac_status & CREG_STAT_ERRORS) अणु
		अगर (bmac_status & CREG_STAT_BERROR)
			prपूर्णांकk("BMAC_ERROR, ");
		अगर (bmac_status & CREG_STAT_TXDERROR)
			prपूर्णांकk("TXD_ERROR, ");
		अगर (bmac_status & CREG_STAT_TXLERR)
			prपूर्णांकk("TX_LATE_ERROR, ");
		अगर (bmac_status & CREG_STAT_TXPERR)
			prपूर्णांकk("TX_PARITY_ERROR, ");
		अगर (bmac_status & CREG_STAT_TXSERR)
			prपूर्णांकk("TX_SBUS_ERROR, ");

		अगर (bmac_status & CREG_STAT_RXDROP)
			prपूर्णांकk("RX_DROP_ERROR, ");

		अगर (bmac_status & CREG_STAT_RXSMALL)
			prपूर्णांकk("RX_SMALL_ERROR, ");
		अगर (bmac_status & CREG_STAT_RXLERR)
			prपूर्णांकk("RX_LATE_ERROR, ");
		अगर (bmac_status & CREG_STAT_RXPERR)
			prपूर्णांकk("RX_PARITY_ERROR, ");
		अगर (bmac_status & CREG_STAT_RXSERR)
			prपूर्णांकk("RX_SBUS_ERROR, ");
	पूर्ण

	prपूर्णांकk(" RESET\n");
	bigmac_init_hw(bp, true);
पूर्ण

/* BigMAC transmit complete service routines. */
अटल व्योम bigmac_tx(काष्ठा bigmac *bp)
अणु
	काष्ठा be_txd *txbase = &bp->bmac_block->be_txd[0];
	काष्ठा net_device *dev = bp->dev;
	पूर्णांक elem;

	spin_lock(&bp->lock);

	elem = bp->tx_old;
	DTX(("bigmac_tx: tx_old[%d] ", elem));
	जबतक (elem != bp->tx_new) अणु
		काष्ठा sk_buff *skb;
		काष्ठा be_txd *this = &txbase[elem];

		DTX(("this(%p) [flags(%08x)addr(%08x)]",
		     this, this->tx_flags, this->tx_addr));

		अगर (this->tx_flags & TXD_OWN)
			अवरोध;
		skb = bp->tx_skbs[elem];
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb->len;
		dma_unmap_single(&bp->bigmac_op->dev,
				 this->tx_addr, skb->len,
				 DMA_TO_DEVICE);

		DTX(("skb(%p) ", skb));
		bp->tx_skbs[elem] = शून्य;
		dev_consume_skb_irq(skb);

		elem = NEXT_TX(elem);
	पूर्ण
	DTX((" DONE, tx_old=%d\n", elem));
	bp->tx_old = elem;

	अगर (netअगर_queue_stopped(dev) &&
	    TX_BUFFS_AVAIL(bp) > 0)
		netअगर_wake_queue(bp->dev);

	spin_unlock(&bp->lock);
पूर्ण

/* BigMAC receive complete service routines. */
अटल व्योम bigmac_rx(काष्ठा bigmac *bp)
अणु
	काष्ठा be_rxd *rxbase = &bp->bmac_block->be_rxd[0];
	काष्ठा be_rxd *this;
	पूर्णांक elem = bp->rx_new, drops = 0;
	u32 flags;

	this = &rxbase[elem];
	जबतक (!((flags = this->rx_flags) & RXD_OWN)) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक len = (flags & RXD_LENGTH); /* FCS not included */

		/* Check क्रम errors. */
		अगर (len < ETH_ZLEN) अणु
			bp->dev->stats.rx_errors++;
			bp->dev->stats.rx_length_errors++;

	drop_it:
			/* Return it to the BigMAC. */
			bp->dev->stats.rx_dropped++;
			this->rx_flags =
				(RXD_OWN | ((RX_BUF_ALLOC_SIZE - 34) & RXD_LENGTH));
			जाओ next;
		पूर्ण
		skb = bp->rx_skbs[elem];
		अगर (len > RX_COPY_THRESHOLD) अणु
			काष्ठा sk_buff *new_skb;

			/* Now refill the entry, अगर we can. */
			new_skb = big_mac_alloc_skb(RX_BUF_ALLOC_SIZE, GFP_ATOMIC);
			अगर (new_skb == शून्य) अणु
				drops++;
				जाओ drop_it;
			पूर्ण
			dma_unmap_single(&bp->bigmac_op->dev,
					 this->rx_addr,
					 RX_BUF_ALLOC_SIZE - 34,
					 DMA_FROM_DEVICE);
			bp->rx_skbs[elem] = new_skb;
			skb_put(new_skb, ETH_FRAME_LEN);
			skb_reserve(new_skb, 34);
			this->rx_addr =
				dma_map_single(&bp->bigmac_op->dev,
					       new_skb->data,
					       RX_BUF_ALLOC_SIZE - 34,
					       DMA_FROM_DEVICE);
			this->rx_flags =
				(RXD_OWN | ((RX_BUF_ALLOC_SIZE - 34) & RXD_LENGTH));

			/* Trim the original skb क्रम the netअगर. */
			skb_trim(skb, len);
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *copy_skb = netdev_alloc_skb(bp->dev, len + 2);

			अगर (copy_skb == शून्य) अणु
				drops++;
				जाओ drop_it;
			पूर्ण
			skb_reserve(copy_skb, 2);
			skb_put(copy_skb, len);
			dma_sync_single_क्रम_cpu(&bp->bigmac_op->dev,
						this->rx_addr, len,
						DMA_FROM_DEVICE);
			skb_copy_to_linear_data(copy_skb, (अचिन्हित अक्षर *)skb->data, len);
			dma_sync_single_क्रम_device(&bp->bigmac_op->dev,
						   this->rx_addr, len,
						   DMA_FROM_DEVICE);

			/* Reuse original ring buffer. */
			this->rx_flags =
				(RXD_OWN | ((RX_BUF_ALLOC_SIZE - 34) & RXD_LENGTH));

			skb = copy_skb;
		पूर्ण

		/* No checksums करोne by the BigMAC ;-( */
		skb->protocol = eth_type_trans(skb, bp->dev);
		netअगर_rx(skb);
		bp->dev->stats.rx_packets++;
		bp->dev->stats.rx_bytes += len;
	next:
		elem = NEXT_RX(elem);
		this = &rxbase[elem];
	पूर्ण
	bp->rx_new = elem;
	अगर (drops)
		prपूर्णांकk(KERN_NOTICE "%s: Memory squeeze, deferring packet.\n", bp->dev->name);
पूर्ण

अटल irqवापस_t bigmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bigmac *bp = (काष्ठा bigmac *) dev_id;
	u32 qec_status, bmac_status;

	सूचीQ(("bigmac_interrupt: "));

	/* Latch status रेजिस्टरs now. */
	bmac_status = sbus_पढ़ोl(bp->creg + CREG_STAT);
	qec_status = sbus_पढ़ोl(bp->gregs + GLOB_STAT);

	सूचीQ(("qec_status=%08x bmac_status=%08x\n", qec_status, bmac_status));
	अगर ((qec_status & (GLOB_STAT_ER | GLOB_STAT_BM)) ||
	   (bmac_status & CREG_STAT_ERRORS))
		bigmac_is_medium_rare(bp, qec_status, bmac_status);

	अगर (bmac_status & CREG_STAT_TXIRQ)
		bigmac_tx(bp);

	अगर (bmac_status & CREG_STAT_RXIRQ)
		bigmac_rx(bp);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bigmac_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bigmac *bp = netdev_priv(dev);
	पूर्णांक ret;

	ret = request_irq(dev->irq, bigmac_पूर्णांकerrupt, IRQF_SHARED, dev->name, bp);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "BIGMAC: Can't order irq %d to go.\n", dev->irq);
		वापस ret;
	पूर्ण
	समयr_setup(&bp->bigmac_समयr, bigmac_समयr, 0);
	ret = bigmac_init_hw(bp, false);
	अगर (ret)
		मुक्त_irq(dev->irq, bp);
	वापस ret;
पूर्ण

अटल पूर्णांक bigmac_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा bigmac *bp = netdev_priv(dev);

	del_समयr(&bp->bigmac_समयr);
	bp->समयr_state = asleep;
	bp->समयr_ticks = 0;

	bigmac_stop(bp);
	bigmac_clean_rings(bp);
	मुक्त_irq(dev->irq, bp);
	वापस 0;
पूर्ण

अटल व्योम bigmac_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा bigmac *bp = netdev_priv(dev);

	bigmac_init_hw(bp, true);
	netअगर_wake_queue(dev);
पूर्ण

/* Put a packet on the wire. */
अटल netdev_tx_t
bigmac_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bigmac *bp = netdev_priv(dev);
	पूर्णांक len, entry;
	u32 mapping;

	len = skb->len;
	mapping = dma_map_single(&bp->bigmac_op->dev, skb->data,
				 len, DMA_TO_DEVICE);

	/* Aव्योम a race... */
	spin_lock_irq(&bp->lock);
	entry = bp->tx_new;
	DTX(("bigmac_start_xmit: len(%d) entry(%d)\n", len, entry));
	bp->bmac_block->be_txd[entry].tx_flags = TXD_UPDATE;
	bp->tx_skbs[entry] = skb;
	bp->bmac_block->be_txd[entry].tx_addr = mapping;
	bp->bmac_block->be_txd[entry].tx_flags =
		(TXD_OWN | TXD_SOP | TXD_EOP | (len & TXD_LENGTH));
	bp->tx_new = NEXT_TX(entry);
	अगर (TX_BUFFS_AVAIL(bp) <= 0)
		netअगर_stop_queue(dev);
	spin_unlock_irq(&bp->lock);

	/* Get it going. */
	sbus_ग_लिखोl(CREG_CTRL_TWAKEUP, bp->creg + CREG_CTRL);


	वापस NETDEV_TX_OK;
पूर्ण

अटल काष्ठा net_device_stats *bigmac_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा bigmac *bp = netdev_priv(dev);

	bigmac_get_counters(bp, bp->bregs);
	वापस &dev->stats;
पूर्ण

अटल व्योम bigmac_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा bigmac *bp = netdev_priv(dev);
	व्योम __iomem *bregs = bp->bregs;
	काष्ठा netdev_hw_addr *ha;
	u32 पंचांगp, crc;

	/* Disable the receiver.  The bit self-clears when
	 * the operation is complete.
	 */
	पंचांगp = sbus_पढ़ोl(bregs + BMAC_RXCFG);
	पंचांगp &= ~(BIGMAC_RXCFG_ENABLE);
	sbus_ग_लिखोl(पंचांगp, bregs + BMAC_RXCFG);
	जबतक ((sbus_पढ़ोl(bregs + BMAC_RXCFG) & BIGMAC_RXCFG_ENABLE) != 0)
		udelay(20);

	अगर ((dev->flags & IFF_ALLMULTI) || (netdev_mc_count(dev) > 64)) अणु
		sbus_ग_लिखोl(0xffff, bregs + BMAC_HTABLE0);
		sbus_ग_लिखोl(0xffff, bregs + BMAC_HTABLE1);
		sbus_ग_लिखोl(0xffff, bregs + BMAC_HTABLE2);
		sbus_ग_लिखोl(0xffff, bregs + BMAC_HTABLE3);
	पूर्ण अन्यथा अगर (dev->flags & IFF_PROMISC) अणु
		पंचांगp = sbus_पढ़ोl(bregs + BMAC_RXCFG);
		पंचांगp |= BIGMAC_RXCFG_PMISC;
		sbus_ग_लिखोl(पंचांगp, bregs + BMAC_RXCFG);
	पूर्ण अन्यथा अणु
		u16 hash_table[4] = अणु 0 पूर्ण;

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			crc = ether_crc_le(6, ha->addr);
			crc >>= 26;
			hash_table[crc >> 4] |= 1 << (crc & 0xf);
		पूर्ण
		sbus_ग_लिखोl(hash_table[0], bregs + BMAC_HTABLE0);
		sbus_ग_लिखोl(hash_table[1], bregs + BMAC_HTABLE1);
		sbus_ग_लिखोl(hash_table[2], bregs + BMAC_HTABLE2);
		sbus_ग_लिखोl(hash_table[3], bregs + BMAC_HTABLE3);
	पूर्ण

	/* Re-enable the receiver. */
	पंचांगp = sbus_पढ़ोl(bregs + BMAC_RXCFG);
	पंचांगp |= BIGMAC_RXCFG_ENABLE;
	sbus_ग_लिखोl(पंचांगp, bregs + BMAC_RXCFG);
पूर्ण

/* Ethtool support... */
अटल व्योम bigmac_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, "sunbmac", माप(info->driver));
	strlcpy(info->version, "2.0", माप(info->version));
पूर्ण

अटल u32 bigmac_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा bigmac *bp = netdev_priv(dev);

	spin_lock_irq(&bp->lock);
	bp->sw_bmsr = bigmac_tcvr_पढ़ो(bp, bp->tregs, MII_BMSR);
	spin_unlock_irq(&bp->lock);

	वापस (bp->sw_bmsr & BMSR_LSTATUS);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bigmac_ethtool_ops = अणु
	.get_drvinfo		= bigmac_get_drvinfo,
	.get_link		= bigmac_get_link,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops bigmac_ops = अणु
	.nकरो_खोलो		= bigmac_खोलो,
	.nकरो_stop		= bigmac_बंद,
	.nकरो_start_xmit		= bigmac_start_xmit,
	.nकरो_get_stats		= bigmac_get_stats,
	.nकरो_set_rx_mode	= bigmac_set_multicast,
	.nकरो_tx_समयout		= bigmac_tx_समयout,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक bigmac_ether_init(काष्ठा platक्रमm_device *op,
			     काष्ठा platक्रमm_device *qec_op)
अणु
	अटल पूर्णांक version_prपूर्णांकed;
	काष्ठा net_device *dev;
	u8 bsizes, bsizes_more;
	काष्ठा bigmac *bp;
	पूर्णांक i;

	/* Get a new device काष्ठा क्रम this पूर्णांकerface. */
	dev = alloc_etherdev(माप(काष्ठा bigmac));
	अगर (!dev)
		वापस -ENOMEM;

	अगर (version_prपूर्णांकed++ == 0)
		prपूर्णांकk(KERN_INFO "%s", version);

	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = idprom->id_ethaddr[i];

	/* Setup softc, with backpoपूर्णांकers to QEC and BigMAC SBUS device काष्ठाs. */
	bp = netdev_priv(dev);
	bp->qec_op = qec_op;
	bp->bigmac_op = op;

	SET_NETDEV_DEV(dev, &op->dev);

	spin_lock_init(&bp->lock);

	/* Map in QEC global control रेजिस्टरs. */
	bp->gregs = of_ioremap(&qec_op->resource[0], 0,
			       GLOB_REG_SIZE, "BigMAC QEC GLobal Regs");
	अगर (!bp->gregs) अणु
		prपूर्णांकk(KERN_ERR "BIGMAC: Cannot map QEC global registers.\n");
		जाओ fail_and_cleanup;
	पूर्ण

	/* Make sure QEC is in BigMAC mode. */
	अगर ((sbus_पढ़ोl(bp->gregs + GLOB_CTRL) & 0xf0000000) != GLOB_CTRL_BMODE) अणु
		prपूर्णांकk(KERN_ERR "BigMAC: AIEEE, QEC is not in BigMAC mode!\n");
		जाओ fail_and_cleanup;
	पूर्ण

	/* Reset the QEC. */
	अगर (qec_global_reset(bp->gregs))
		जाओ fail_and_cleanup;

	/* Get supported SBUS burst sizes. */
	bsizes = of_getपूर्णांकprop_शेष(qec_op->dev.of_node, "burst-sizes", 0xff);
	bsizes_more = of_getपूर्णांकprop_शेष(qec_op->dev.of_node, "burst-sizes", 0xff);

	bsizes &= 0xff;
	अगर (bsizes_more != 0xff)
		bsizes &= bsizes_more;
	अगर (bsizes == 0xff || (bsizes & DMA_BURST16) == 0 ||
	    (bsizes & DMA_BURST32) == 0)
		bsizes = (DMA_BURST32 - 1);
	bp->bigmac_bursts = bsizes;

	/* Perक्रमm QEC initialization. */
	qec_init(bp);

	/* Map in the BigMAC channel रेजिस्टरs. */
	bp->creg = of_ioremap(&op->resource[0], 0,
			      CREG_REG_SIZE, "BigMAC QEC Channel Regs");
	अगर (!bp->creg) अणु
		prपूर्णांकk(KERN_ERR "BIGMAC: Cannot map QEC channel registers.\n");
		जाओ fail_and_cleanup;
	पूर्ण

	/* Map in the BigMAC control रेजिस्टरs. */
	bp->bregs = of_ioremap(&op->resource[1], 0,
			       BMAC_REG_SIZE, "BigMAC Primary Regs");
	अगर (!bp->bregs) अणु
		prपूर्णांकk(KERN_ERR "BIGMAC: Cannot map BigMAC primary registers.\n");
		जाओ fail_and_cleanup;
	पूर्ण

	/* Map in the BigMAC transceiver रेजिस्टरs, this is how you poke at
	 * the BigMAC's PHY.
	 */
	bp->tregs = of_ioremap(&op->resource[2], 0,
			       TCVR_REG_SIZE, "BigMAC Transceiver Regs");
	अगर (!bp->tregs) अणु
		prपूर्णांकk(KERN_ERR "BIGMAC: Cannot map BigMAC transceiver registers.\n");
		जाओ fail_and_cleanup;
	पूर्ण

	/* Stop the BigMAC. */
	bigmac_stop(bp);

	/* Allocate transmit/receive descriptor DVMA block. */
	bp->bmac_block = dma_alloc_coherent(&bp->bigmac_op->dev,
					    PAGE_SIZE,
					    &bp->bblock_dvma, GFP_ATOMIC);
	अगर (bp->bmac_block == शून्य || bp->bblock_dvma == 0)
		जाओ fail_and_cleanup;

	/* Get the board revision of this BigMAC. */
	bp->board_rev = of_getपूर्णांकprop_शेष(bp->bigmac_op->dev.of_node,
					      "board-version", 1);

	/* Init स्वतः-negotiation समयr state. */
	समयr_setup(&bp->bigmac_समयr, bigmac_समयr, 0);
	bp->समयr_state = asleep;
	bp->समयr_ticks = 0;

	/* Backlink to generic net device काष्ठा. */
	bp->dev = dev;

	/* Set links to our BigMAC खोलो and बंद routines. */
	dev->ethtool_ops = &bigmac_ethtool_ops;
	dev->netdev_ops = &bigmac_ops;
	dev->watchकरोg_समयo = 5*HZ;

	/* Finish net device registration. */
	dev->irq = bp->bigmac_op->archdata.irqs[0];
	dev->dma = 0;

	अगर (रेजिस्टर_netdev(dev)) अणु
		prपूर्णांकk(KERN_ERR "BIGMAC: Cannot register device.\n");
		जाओ fail_and_cleanup;
	पूर्ण

	dev_set_drvdata(&bp->bigmac_op->dev, bp);

	prपूर्णांकk(KERN_INFO "%s: BigMAC 100baseT Ethernet %pM\n",
	       dev->name, dev->dev_addr);

	वापस 0;

fail_and_cleanup:
	/* Something went wrong, unकरो whatever we did so far. */
	/* Free रेजिस्टर mappings अगर any. */
	अगर (bp->gregs)
		of_iounmap(&qec_op->resource[0], bp->gregs, GLOB_REG_SIZE);
	अगर (bp->creg)
		of_iounmap(&op->resource[0], bp->creg, CREG_REG_SIZE);
	अगर (bp->bregs)
		of_iounmap(&op->resource[1], bp->bregs, BMAC_REG_SIZE);
	अगर (bp->tregs)
		of_iounmap(&op->resource[2], bp->tregs, TCVR_REG_SIZE);

	अगर (bp->bmac_block)
		dma_मुक्त_coherent(&bp->bigmac_op->dev,
				  PAGE_SIZE,
				  bp->bmac_block,
				  bp->bblock_dvma);

	/* This also मुक्तs the co-located निजी data */
	मुक्त_netdev(dev);
	वापस -ENODEV;
पूर्ण

/* QEC can be the parent of either QuadEthernet or a BigMAC.  We want
 * the latter.
 */
अटल पूर्णांक bigmac_sbus_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device *parent = op->dev.parent;
	काष्ठा platक्रमm_device *qec_op;

	qec_op = to_platक्रमm_device(parent);

	वापस bigmac_ether_init(op, qec_op);
पूर्ण

अटल पूर्णांक bigmac_sbus_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा bigmac *bp = platक्रमm_get_drvdata(op);
	काष्ठा device *parent = op->dev.parent;
	काष्ठा net_device *net_dev = bp->dev;
	काष्ठा platक्रमm_device *qec_op;

	qec_op = to_platक्रमm_device(parent);

	unरेजिस्टर_netdev(net_dev);

	of_iounmap(&qec_op->resource[0], bp->gregs, GLOB_REG_SIZE);
	of_iounmap(&op->resource[0], bp->creg, CREG_REG_SIZE);
	of_iounmap(&op->resource[1], bp->bregs, BMAC_REG_SIZE);
	of_iounmap(&op->resource[2], bp->tregs, TCVR_REG_SIZE);
	dma_मुक्त_coherent(&op->dev,
			  PAGE_SIZE,
			  bp->bmac_block,
			  bp->bblock_dvma);

	मुक्त_netdev(net_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bigmac_sbus_match[] = अणु
	अणु
		.name = "be",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, bigmac_sbus_match);

अटल काष्ठा platक्रमm_driver bigmac_sbus_driver = अणु
	.driver = अणु
		.name = "sunbmac",
		.of_match_table = bigmac_sbus_match,
	पूर्ण,
	.probe		= bigmac_sbus_probe,
	.हटाओ		= bigmac_sbus_हटाओ,
पूर्ण;

module_platक्रमm_driver(bigmac_sbus_driver);
