<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Network device driver क्रम the BMAC ethernet controller on
 * Apple Powermacs.  Assumes it's under a DBDMA controller.
 *
 * Copyright (C) 1998 Randy Gobbel.
 *
 * May 1999, Al Viro: proper release of /proc/net/bmac entry, चयनed to
 * dynamic procfs inode.
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/crc32.h>
#समावेश <linux/crc32poly.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/slab.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/macपन.स>
#समावेश <यंत्र/irq.h>

#समावेश "bmac.h"

#घोषणा trunc_page(x)	((व्योम *)(((अचिन्हित दीर्घ)(x)) & ~((अचिन्हित दीर्घ)(PAGE_SIZE - 1))))
#घोषणा round_page(x)	trunc_page(((अचिन्हित दीर्घ)(x)) + ((अचिन्हित दीर्घ)(PAGE_SIZE - 1)))

/* चयन to use multicast code lअगरted from sunhme driver */
#घोषणा SUNHME_MULTICAST

#घोषणा N_RX_RING	64
#घोषणा N_TX_RING	32
#घोषणा MAX_TX_ACTIVE	1
#घोषणा ETHERCRC	4
#घोषणा ETHERMINPACKET	64
#घोषणा ETHERMTU	1500
#घोषणा RX_BUFLEN	(ETHERMTU + 14 + ETHERCRC + 2)
#घोषणा TX_TIMEOUT	HZ	/* 1 second */

/* Bits in transmit DMA status */
#घोषणा TX_DMA_ERR	0x80

#घोषणा XXDEBUG(args)

काष्ठा bmac_data अणु
	/* अस्थिर काष्ठा bmac *bmac; */
	काष्ठा sk_buff_head *queue;
	अस्थिर काष्ठा dbdma_regs __iomem *tx_dma;
	पूर्णांक tx_dma_पूर्णांकr;
	अस्थिर काष्ठा dbdma_regs __iomem *rx_dma;
	पूर्णांक rx_dma_पूर्णांकr;
	अस्थिर काष्ठा dbdma_cmd *tx_cmds;	/* xmit dma command list */
	अस्थिर काष्ठा dbdma_cmd *rx_cmds;	/* recv dma command list */
	काष्ठा macio_dev *mdev;
	पूर्णांक is_bmac_plus;
	काष्ठा sk_buff *rx_bufs[N_RX_RING];
	पूर्णांक rx_fill;
	पूर्णांक rx_empty;
	काष्ठा sk_buff *tx_bufs[N_TX_RING];
	पूर्णांक tx_fill;
	पूर्णांक tx_empty;
	अचिन्हित अक्षर tx_fullup;
	काष्ठा समयr_list tx_समयout;
	पूर्णांक समयout_active;
	पूर्णांक sleeping;
	पूर्णांक खोलोed;
	अचिन्हित लघु hash_use_count[64];
	अचिन्हित लघु hash_table_mask[4];
	spinlock_t lock;
पूर्ण;

#अगर 0 /* Move that to ethtool */

प्रकार काष्ठा bmac_reg_entry अणु
	अक्षर *name;
	अचिन्हित लघु reg_offset;
पूर्ण bmac_reg_entry_t;

#घोषणा N_REG_ENTRIES 31

अटल bmac_reg_entry_t reg_entries[N_REG_ENTRIES] = अणु
	अणु"MEMADD", MEMADDपूर्ण,
	अणु"MEMDATAHI", MEMDATAHIपूर्ण,
	अणु"MEMDATALO", MEMDATALOपूर्ण,
	अणु"TXPNTR", TXPNTRपूर्ण,
	अणु"RXPNTR", RXPNTRपूर्ण,
	अणु"IPG1", IPG1पूर्ण,
	अणु"IPG2", IPG2पूर्ण,
	अणु"ALIMIT", ALIMITपूर्ण,
	अणु"SLOT", SLOTपूर्ण,
	अणु"PALEN", PALENपूर्ण,
	अणु"PAPAT", PAPATपूर्ण,
	अणु"TXSFD", TXSFDपूर्ण,
	अणु"JAM", JAMपूर्ण,
	अणु"TXCFG", TXCFGपूर्ण,
	अणु"TXMAX", TXMAXपूर्ण,
	अणु"TXMIN", TXMINपूर्ण,
	अणु"PAREG", PAREGपूर्ण,
	अणु"DCNT", DCNTपूर्ण,
	अणु"NCCNT", NCCNTपूर्ण,
	अणु"NTCNT", NTCNTपूर्ण,
	अणु"EXCNT", EXCNTपूर्ण,
	अणु"LTCNT", LTCNTपूर्ण,
	अणु"TXSM", TXSMपूर्ण,
	अणु"RXCFG", RXCFGपूर्ण,
	अणु"RXMAX", RXMAXपूर्ण,
	अणु"RXMIN", RXMINपूर्ण,
	अणु"FRCNT", FRCNTपूर्ण,
	अणु"AECNT", AECNTपूर्ण,
	अणु"FECNT", FECNTपूर्ण,
	अणु"RXSM", RXSMपूर्ण,
	अणु"RXCV", RXCVपूर्ण
पूर्ण;

#पूर्ण_अगर

अटल अचिन्हित अक्षर *bmac_emergency_rxbuf;

/*
 * Number of bytes of निजी data per BMAC: allow enough क्रम
 * the rx and tx dma commands plus a branch dma command each,
 * and another 16 bytes to allow us to align the dma command
 * buffers on a 16 byte boundary.
 */
#घोषणा PRIV_BYTES	(माप(काष्ठा bmac_data) \
	+ (N_RX_RING + N_TX_RING + 4) * माप(काष्ठा dbdma_cmd) \
	+ माप(काष्ठा sk_buff_head))

अटल पूर्णांक bmac_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक bmac_बंद(काष्ठा net_device *dev);
अटल पूर्णांक bmac_transmit_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल व्योम bmac_set_multicast(काष्ठा net_device *dev);
अटल व्योम bmac_reset_and_enable(काष्ठा net_device *dev);
अटल व्योम bmac_start_chip(काष्ठा net_device *dev);
अटल व्योम bmac_init_chip(काष्ठा net_device *dev);
अटल व्योम bmac_init_रेजिस्टरs(काष्ठा net_device *dev);
अटल व्योम bmac_enable_and_reset_chip(काष्ठा net_device *dev);
अटल पूर्णांक bmac_set_address(काष्ठा net_device *dev, व्योम *addr);
अटल irqवापस_t bmac_misc_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t bmac_txdma_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t bmac_rxdma_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
अटल व्योम bmac_set_समयout(काष्ठा net_device *dev);
अटल व्योम bmac_tx_समयout(काष्ठा समयr_list *t);
अटल netdev_tx_t bmac_output(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल व्योम bmac_start(काष्ठा net_device *dev);

#घोषणा	DBDMA_SET(x)	( ((x) | (x) << 16) )
#घोषणा	DBDMA_CLEAR(x)	( (x) << 16)

अटल अंतरभूत व्योम
dbdma_st32(अस्थिर __u32 __iomem *a, अचिन्हित दीर्घ x)
अणु
	__यंत्र__ अस्थिर( "stwbrx %0,0,%1" : : "r" (x), "r" (a) : "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
dbdma_ld32(अस्थिर __u32 __iomem *a)
अणु
	__u32 swap;
	__यंत्र__ अस्थिर ("lwbrx %0,0,%1" :  "=r" (swap) : "r" (a));
	वापस swap;
पूर्ण

अटल व्योम
dbdma_जारी(अस्थिर काष्ठा dbdma_regs __iomem *dmap)
अणु
	dbdma_st32(&dmap->control,
		   DBDMA_SET(RUN|WAKE) | DBDMA_CLEAR(PAUSE|DEAD));
	eieio();
पूर्ण

अटल व्योम
dbdma_reset(अस्थिर काष्ठा dbdma_regs __iomem *dmap)
अणु
	dbdma_st32(&dmap->control,
		   DBDMA_CLEAR(ACTIVE|DEAD|WAKE|FLUSH|PAUSE|RUN));
	eieio();
	जबतक (dbdma_ld32(&dmap->status) & RUN)
		eieio();
पूर्ण

अटल व्योम
dbdma_setcmd(अस्थिर काष्ठा dbdma_cmd *cp,
	     अचिन्हित लघु cmd, अचिन्हित count, अचिन्हित दीर्घ addr,
	     अचिन्हित दीर्घ cmd_dep)
अणु
	out_le16(&cp->command, cmd);
	out_le16(&cp->req_count, count);
	out_le32(&cp->phy_addr, addr);
	out_le32(&cp->cmd_dep, cmd_dep);
	out_le16(&cp->xfer_status, 0);
	out_le16(&cp->res_count, 0);
पूर्ण

अटल अंतरभूत
व्योम bmग_लिखो(काष्ठा net_device *dev, अचिन्हित दीर्घ reg_offset, अचिन्हित data )
अणु
	out_le16((व्योम __iomem *)dev->base_addr + reg_offset, data);
पूर्ण


अटल अंतरभूत
अचिन्हित लघु bmपढ़ो(काष्ठा net_device *dev, अचिन्हित दीर्घ reg_offset )
अणु
	वापस in_le16((व्योम __iomem *)dev->base_addr + reg_offset);
पूर्ण

अटल व्योम
bmac_enable_and_reset_chip(काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अस्थिर काष्ठा dbdma_regs __iomem *rd = bp->rx_dma;
	अस्थिर काष्ठा dbdma_regs __iomem *td = bp->tx_dma;

	अगर (rd)
		dbdma_reset(rd);
	अगर (td)
		dbdma_reset(td);

	pmac_call_feature(PMAC_FTR_BMAC_ENABLE, macio_get_of_node(bp->mdev), 0, 1);
पूर्ण

#घोषणा MIFDELAY	udelay(10)

अटल अचिन्हित पूर्णांक
bmac_mअगर_पढ़ोbits(काष्ठा net_device *dev, पूर्णांक nb)
अणु
	अचिन्हित पूर्णांक val = 0;

	जबतक (--nb >= 0) अणु
		bmग_लिखो(dev, MIFCSR, 0);
		MIFDELAY;
		अगर (bmपढ़ो(dev, MIFCSR) & 8)
			val |= 1 << nb;
		bmग_लिखो(dev, MIFCSR, 1);
		MIFDELAY;
	पूर्ण
	bmग_लिखो(dev, MIFCSR, 0);
	MIFDELAY;
	bmग_लिखो(dev, MIFCSR, 1);
	MIFDELAY;
	वापस val;
पूर्ण

अटल व्योम
bmac_mअगर_ग_लिखोbits(काष्ठा net_device *dev, अचिन्हित पूर्णांक val, पूर्णांक nb)
अणु
	पूर्णांक b;

	जबतक (--nb >= 0) अणु
		b = (val & (1 << nb))? 6: 4;
		bmग_लिखो(dev, MIFCSR, b);
		MIFDELAY;
		bmग_लिखो(dev, MIFCSR, b|1);
		MIFDELAY;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
bmac_mअगर_पढ़ो(काष्ठा net_device *dev, अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक val;

	bmग_लिखो(dev, MIFCSR, 4);
	MIFDELAY;
	bmac_mअगर_ग_लिखोbits(dev, ~0U, 32);
	bmac_mअगर_ग_लिखोbits(dev, 6, 4);
	bmac_mअगर_ग_लिखोbits(dev, addr, 10);
	bmग_लिखो(dev, MIFCSR, 2);
	MIFDELAY;
	bmग_लिखो(dev, MIFCSR, 1);
	MIFDELAY;
	val = bmac_mअगर_पढ़ोbits(dev, 17);
	bmग_लिखो(dev, MIFCSR, 4);
	MIFDELAY;
	वापस val;
पूर्ण

अटल व्योम
bmac_mअगर_ग_लिखो(काष्ठा net_device *dev, अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक val)
अणु
	bmग_लिखो(dev, MIFCSR, 4);
	MIFDELAY;
	bmac_mअगर_ग_लिखोbits(dev, ~0U, 32);
	bmac_mअगर_ग_लिखोbits(dev, 5, 4);
	bmac_mअगर_ग_लिखोbits(dev, addr, 10);
	bmac_mअगर_ग_लिखोbits(dev, 2, 2);
	bmac_mअगर_ग_लिखोbits(dev, val, 16);
	bmac_mअगर_ग_लिखोbits(dev, 3, 2);
पूर्ण

अटल व्योम
bmac_init_रेजिस्टरs(काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अस्थिर अचिन्हित लघु regValue;
	अचिन्हित लघु *pWord16;
	पूर्णांक i;

	/* XXDEBUG(("bmac: enter init_registers\n")); */

	bmग_लिखो(dev, RXRST, RxResetValue);
	bmग_लिखो(dev, TXRST, TxResetBit);

	i = 100;
	करो अणु
		--i;
		udelay(10000);
		regValue = bmपढ़ो(dev, TXRST); /* रुको क्रम reset to clear..acknowledge */
	पूर्ण जबतक ((regValue & TxResetBit) && i > 0);

	अगर (!bp->is_bmac_plus) अणु
		regValue = bmपढ़ो(dev, XCVRIF);
		regValue |= ClkBit | SerialMode | COLActiveLow;
		bmग_लिखो(dev, XCVRIF, regValue);
		udelay(10000);
	पूर्ण

	bmग_लिखो(dev, RSEED, (अचिन्हित लघु)0x1968);

	regValue = bmपढ़ो(dev, XIFC);
	regValue |= TxOutputEnable;
	bmग_लिखो(dev, XIFC, regValue);

	bmपढ़ो(dev, PAREG);

	/* set collision counters to 0 */
	bmग_लिखो(dev, NCCNT, 0);
	bmग_लिखो(dev, NTCNT, 0);
	bmग_लिखो(dev, EXCNT, 0);
	bmग_लिखो(dev, LTCNT, 0);

	/* set rx counters to 0 */
	bmग_लिखो(dev, FRCNT, 0);
	bmग_लिखो(dev, LECNT, 0);
	bmग_लिखो(dev, AECNT, 0);
	bmग_लिखो(dev, FECNT, 0);
	bmग_लिखो(dev, RXCV, 0);

	/* set tx fअगरo inक्रमmation */
	bmग_लिखो(dev, TXTH, 4);	/* 4 octets beक्रमe tx starts */

	bmग_लिखो(dev, TXFIFOCSR, 0);	/* first disable txFIFO */
	bmग_लिखो(dev, TXFIFOCSR, TxFIFOEnable );

	/* set rx fअगरo inक्रमmation */
	bmग_लिखो(dev, RXFIFOCSR, 0);	/* first disable rxFIFO */
	bmग_लिखो(dev, RXFIFOCSR, RxFIFOEnable );

	//bmग_लिखो(dev, TXCFG, TxMACEnable);	       	/* TxNeverGiveUp maybe later */
	bmपढ़ो(dev, STATUS);		/* पढ़ो it just to clear it */

	/* zero out the chip Hash Filter रेजिस्टरs */
	क्रम (i=0; i<4; i++) bp->hash_table_mask[i] = 0;
	bmग_लिखो(dev, BHASH3, bp->hash_table_mask[0]); 	/* bits 15 - 0 */
	bmग_लिखो(dev, BHASH2, bp->hash_table_mask[1]); 	/* bits 31 - 16 */
	bmग_लिखो(dev, BHASH1, bp->hash_table_mask[2]); 	/* bits 47 - 32 */
	bmग_लिखो(dev, BHASH0, bp->hash_table_mask[3]); 	/* bits 63 - 48 */

	pWord16 = (अचिन्हित लघु *)dev->dev_addr;
	bmग_लिखो(dev, MADD0, *pWord16++);
	bmग_लिखो(dev, MADD1, *pWord16++);
	bmग_लिखो(dev, MADD2, *pWord16);

	bmग_लिखो(dev, RXCFG, RxCRCNoStrip | RxHashFilterEnable | RxRejectOwnPackets);

	bmग_लिखो(dev, INTDISABLE, EnableNormal);
पूर्ण

#अगर 0
अटल व्योम
bmac_disable_पूर्णांकerrupts(काष्ठा net_device *dev)
अणु
	bmग_लिखो(dev, INTDISABLE, DisableAll);
पूर्ण

अटल व्योम
bmac_enable_पूर्णांकerrupts(काष्ठा net_device *dev)
अणु
	bmग_लिखो(dev, INTDISABLE, EnableNormal);
पूर्ण
#पूर्ण_अगर


अटल व्योम
bmac_start_chip(काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अस्थिर काष्ठा dbdma_regs __iomem *rd = bp->rx_dma;
	अचिन्हित लघु	oldConfig;

	/* enable rx dma channel */
	dbdma_जारी(rd);

	oldConfig = bmपढ़ो(dev, TXCFG);
	bmग_लिखो(dev, TXCFG, oldConfig | TxMACEnable );

	/* turn on rx plus any other bits alपढ़ोy on (promiscuous possibly) */
	oldConfig = bmपढ़ो(dev, RXCFG);
	bmग_लिखो(dev, RXCFG, oldConfig | RxMACEnable );
	udelay(20000);
पूर्ण

अटल व्योम
bmac_init_phy(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक addr;
	काष्ठा bmac_data *bp = netdev_priv(dev);

	prपूर्णांकk(KERN_DEBUG "phy registers:");
	क्रम (addr = 0; addr < 32; ++addr) अणु
		अगर ((addr & 7) == 0)
			prपूर्णांकk(KERN_DEBUG);
		prपूर्णांकk(KERN_CONT " %.4x", bmac_mअगर_पढ़ो(dev, addr));
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");

	अगर (bp->is_bmac_plus) अणु
		अचिन्हित पूर्णांक capable, ctrl;

		ctrl = bmac_mअगर_पढ़ो(dev, 0);
		capable = ((bmac_mअगर_पढ़ो(dev, 1) & 0xf800) >> 6) | 1;
		अगर (bmac_mअगर_पढ़ो(dev, 4) != capable ||
		    (ctrl & 0x1000) == 0) अणु
			bmac_mअगर_ग_लिखो(dev, 4, capable);
			bmac_mअगर_ग_लिखो(dev, 0, 0x1200);
		पूर्ण अन्यथा
			bmac_mअगर_ग_लिखो(dev, 0, 0x1000);
	पूर्ण
पूर्ण

अटल व्योम bmac_init_chip(काष्ठा net_device *dev)
अणु
	bmac_init_phy(dev);
	bmac_init_रेजिस्टरs(dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bmac_suspend(काष्ठा macio_dev *mdev, pm_message_t state)
अणु
	काष्ठा net_device* dev = macio_get_drvdata(mdev);
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु config;
	पूर्णांक i;

	netअगर_device_detach(dev);
	/* prolly should रुको क्रम dma to finish & turn off the chip */
	spin_lock_irqsave(&bp->lock, flags);
	अगर (bp->समयout_active) अणु
		del_समयr(&bp->tx_समयout);
		bp->समयout_active = 0;
	पूर्ण
	disable_irq(dev->irq);
	disable_irq(bp->tx_dma_पूर्णांकr);
	disable_irq(bp->rx_dma_पूर्णांकr);
	bp->sleeping = 1;
	spin_unlock_irqrestore(&bp->lock, flags);
	अगर (bp->खोलोed) अणु
		अस्थिर काष्ठा dbdma_regs __iomem *rd = bp->rx_dma;
		अस्थिर काष्ठा dbdma_regs __iomem *td = bp->tx_dma;

		config = bmपढ़ो(dev, RXCFG);
		bmग_लिखो(dev, RXCFG, (config & ~RxMACEnable));
		config = bmपढ़ो(dev, TXCFG);
       		bmग_लिखो(dev, TXCFG, (config & ~TxMACEnable));
		bmग_लिखो(dev, INTDISABLE, DisableAll); /* disable all पूर्णांकrs */
       		/* disable rx and tx dma */
		rd->control = cpu_to_le32(DBDMA_CLEAR(RUN|PAUSE|FLUSH|WAKE));	/* clear run bit */
		td->control = cpu_to_le32(DBDMA_CLEAR(RUN|PAUSE|FLUSH|WAKE));	/* clear run bit */
       		/* मुक्त some skb's */
       		क्रम (i=0; i<N_RX_RING; i++) अणु
       			अगर (bp->rx_bufs[i] != शून्य) अणु
       				dev_kमुक्त_skb(bp->rx_bufs[i]);
       				bp->rx_bufs[i] = शून्य;
       			पूर्ण
       		पूर्ण
       		क्रम (i = 0; i<N_TX_RING; i++) अणु
			अगर (bp->tx_bufs[i] != शून्य) अणु
		       		dev_kमुक्त_skb(bp->tx_bufs[i]);
	       			bp->tx_bufs[i] = शून्य;
		       	पूर्ण
		पूर्ण
	पूर्ण
       	pmac_call_feature(PMAC_FTR_BMAC_ENABLE, macio_get_of_node(bp->mdev), 0, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक bmac_resume(काष्ठा macio_dev *mdev)
अणु
	काष्ठा net_device* dev = macio_get_drvdata(mdev);
	काष्ठा bmac_data *bp = netdev_priv(dev);

	/* see अगर this is enough */
	अगर (bp->खोलोed)
		bmac_reset_and_enable(dev);

	enable_irq(dev->irq);
       	enable_irq(bp->tx_dma_पूर्णांकr);
       	enable_irq(bp->rx_dma_पूर्णांकr);
       	netअगर_device_attach(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक bmac_set_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अचिन्हित अक्षर *p = addr;
	अचिन्हित लघु *pWord16;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	XXDEBUG(("bmac: enter set_address\n"));
	spin_lock_irqsave(&bp->lock, flags);

	क्रम (i = 0; i < 6; ++i) अणु
		dev->dev_addr[i] = p[i];
	पूर्ण
	/* load up the hardware address */
	pWord16  = (अचिन्हित लघु *)dev->dev_addr;
	bmग_लिखो(dev, MADD0, *pWord16++);
	bmग_लिखो(dev, MADD1, *pWord16++);
	bmग_लिखो(dev, MADD2, *pWord16);

	spin_unlock_irqrestore(&bp->lock, flags);
	XXDEBUG(("bmac: exit set_address\n"));
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bmac_set_समयout(काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bp->lock, flags);
	अगर (bp->समयout_active)
		del_समयr(&bp->tx_समयout);
	bp->tx_समयout.expires = jअगरfies + TX_TIMEOUT;
	add_समयr(&bp->tx_समयout);
	bp->समयout_active = 1;
	spin_unlock_irqrestore(&bp->lock, flags);
पूर्ण

अटल व्योम
bmac_स्थिरruct_xmt(काष्ठा sk_buff *skb, अस्थिर काष्ठा dbdma_cmd *cp)
अणु
	व्योम *vaddr;
	अचिन्हित दीर्घ baddr;
	अचिन्हित दीर्घ len;

	len = skb->len;
	vaddr = skb->data;
	baddr = virt_to_bus(vaddr);

	dbdma_setcmd(cp, (OUTPUT_LAST | INTR_ALWAYS | WAIT_IFCLR), len, baddr, 0);
पूर्ण

अटल व्योम
bmac_स्थिरruct_rxbuff(काष्ठा sk_buff *skb, अस्थिर काष्ठा dbdma_cmd *cp)
अणु
	अचिन्हित अक्षर *addr = skb? skb->data: bmac_emergency_rxbuf;

	dbdma_setcmd(cp, (INPUT_LAST | INTR_ALWAYS), RX_BUFLEN,
		     virt_to_bus(addr), 0);
पूर्ण

अटल व्योम
bmac_init_tx_ring(काष्ठा bmac_data *bp)
अणु
	अस्थिर काष्ठा dbdma_regs __iomem *td = bp->tx_dma;

	स_रखो((अक्षर *)bp->tx_cmds, 0, (N_TX_RING+1) * माप(काष्ठा dbdma_cmd));

	bp->tx_empty = 0;
	bp->tx_fill = 0;
	bp->tx_fullup = 0;

	/* put a branch at the end of the tx command list */
	dbdma_setcmd(&bp->tx_cmds[N_TX_RING],
		     (DBDMA_NOP | BR_ALWAYS), 0, 0, virt_to_bus(bp->tx_cmds));

	/* reset tx dma */
	dbdma_reset(td);
	out_le32(&td->रुको_sel, 0x00200020);
	out_le32(&td->cmdptr, virt_to_bus(bp->tx_cmds));
पूर्ण

अटल पूर्णांक
bmac_init_rx_ring(काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अस्थिर काष्ठा dbdma_regs __iomem *rd = bp->rx_dma;
	पूर्णांक i;
	काष्ठा sk_buff *skb;

	/* initialize list of sk_buffs क्रम receiving and set up recv dma */
	स_रखो((अक्षर *)bp->rx_cmds, 0,
	       (N_RX_RING + 1) * माप(काष्ठा dbdma_cmd));
	क्रम (i = 0; i < N_RX_RING; i++) अणु
		अगर ((skb = bp->rx_bufs[i]) == शून्य) अणु
			bp->rx_bufs[i] = skb = netdev_alloc_skb(dev, RX_BUFLEN + 2);
			अगर (skb != शून्य)
				skb_reserve(skb, 2);
		पूर्ण
		bmac_स्थिरruct_rxbuff(skb, &bp->rx_cmds[i]);
	पूर्ण

	bp->rx_empty = 0;
	bp->rx_fill = i;

	/* Put a branch back to the beginning of the receive command list */
	dbdma_setcmd(&bp->rx_cmds[N_RX_RING],
		     (DBDMA_NOP | BR_ALWAYS), 0, 0, virt_to_bus(bp->rx_cmds));

	/* start rx dma */
	dbdma_reset(rd);
	out_le32(&rd->cmdptr, virt_to_bus(bp->rx_cmds));

	वापस 1;
पूर्ण


अटल पूर्णांक bmac_transmit_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अस्थिर काष्ठा dbdma_regs __iomem *td = bp->tx_dma;
	पूर्णांक i;

	/* see अगर there's a मुक्त slot in the tx ring */
	/* XXDEBUG(("bmac_xmit_start: empty=%d fill=%d\n", */
	/* 	     bp->tx_empty, bp->tx_fill)); */
	i = bp->tx_fill + 1;
	अगर (i >= N_TX_RING)
		i = 0;
	अगर (i == bp->tx_empty) अणु
		netअगर_stop_queue(dev);
		bp->tx_fullup = 1;
		XXDEBUG(("bmac_transmit_packet: tx ring full\n"));
		वापस -1;		/* can't take it at the moment */
	पूर्ण

	dbdma_setcmd(&bp->tx_cmds[i], DBDMA_STOP, 0, 0, 0);

	bmac_स्थिरruct_xmt(skb, &bp->tx_cmds[bp->tx_fill]);

	bp->tx_bufs[bp->tx_fill] = skb;
	bp->tx_fill = i;

	dev->stats.tx_bytes += skb->len;

	dbdma_जारी(td);

	वापस 0;
पूर्ण

अटल पूर्णांक rxपूर्णांकcount;

अटल irqवापस_t bmac_rxdma_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अस्थिर काष्ठा dbdma_regs __iomem *rd = bp->rx_dma;
	अस्थिर काष्ठा dbdma_cmd *cp;
	पूर्णांक i, nb, stat;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक residual;
	पूर्णांक last;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bp->lock, flags);

	अगर (++rxपूर्णांकcount < 10) अणु
		XXDEBUG(("bmac_rxdma_intr\n"));
	पूर्ण

	last = -1;
	i = bp->rx_empty;

	जबतक (1) अणु
		cp = &bp->rx_cmds[i];
		stat = le16_to_cpu(cp->xfer_status);
		residual = le16_to_cpu(cp->res_count);
		अगर ((stat & ACTIVE) == 0)
			अवरोध;
		nb = RX_BUFLEN - residual - 2;
		अगर (nb < (ETHERMINPACKET - ETHERCRC)) अणु
			skb = शून्य;
			dev->stats.rx_length_errors++;
			dev->stats.rx_errors++;
		पूर्ण अन्यथा अणु
			skb = bp->rx_bufs[i];
			bp->rx_bufs[i] = शून्य;
		पूर्ण
		अगर (skb != शून्य) अणु
			nb -= ETHERCRC;
			skb_put(skb, nb);
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);
			++dev->stats.rx_packets;
			dev->stats.rx_bytes += nb;
		पूर्ण अन्यथा अणु
			++dev->stats.rx_dropped;
		पूर्ण
		अगर ((skb = bp->rx_bufs[i]) == शून्य) अणु
			bp->rx_bufs[i] = skb = netdev_alloc_skb(dev, RX_BUFLEN + 2);
			अगर (skb != शून्य)
				skb_reserve(bp->rx_bufs[i], 2);
		पूर्ण
		bmac_स्थिरruct_rxbuff(skb, &bp->rx_cmds[i]);
		cp->res_count = cpu_to_le16(0);
		cp->xfer_status = cpu_to_le16(0);
		last = i;
		अगर (++i >= N_RX_RING) i = 0;
	पूर्ण

	अगर (last != -1) अणु
		bp->rx_fill = last;
		bp->rx_empty = i;
	पूर्ण

	dbdma_जारी(rd);
	spin_unlock_irqrestore(&bp->lock, flags);

	अगर (rxपूर्णांकcount < 10) अणु
		XXDEBUG(("bmac_rxdma_intr done\n"));
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक txपूर्णांकcount;

अटल irqवापस_t bmac_txdma_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अस्थिर काष्ठा dbdma_cmd *cp;
	पूर्णांक stat;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bp->lock, flags);

	अगर (txपूर्णांकcount++ < 10) अणु
		XXDEBUG(("bmac_txdma_intr\n"));
	पूर्ण

	/*     del_समयr(&bp->tx_समयout); */
	/*     bp->समयout_active = 0; */

	जबतक (1) अणु
		cp = &bp->tx_cmds[bp->tx_empty];
		stat = le16_to_cpu(cp->xfer_status);
		अगर (txपूर्णांकcount < 10) अणु
			XXDEBUG(("bmac_txdma_xfer_stat=%#0x\n", stat));
		पूर्ण
		अगर (!(stat & ACTIVE)) अणु
			/*
			 * status field might not have been filled by DBDMA
			 */
			अगर (cp == bus_to_virt(in_le32(&bp->tx_dma->cmdptr)))
				अवरोध;
		पूर्ण

		अगर (bp->tx_bufs[bp->tx_empty]) अणु
			++dev->stats.tx_packets;
			dev_consume_skb_irq(bp->tx_bufs[bp->tx_empty]);
		पूर्ण
		bp->tx_bufs[bp->tx_empty] = शून्य;
		bp->tx_fullup = 0;
		netअगर_wake_queue(dev);
		अगर (++bp->tx_empty >= N_TX_RING)
			bp->tx_empty = 0;
		अगर (bp->tx_empty == bp->tx_fill)
			अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&bp->lock, flags);

	अगर (txपूर्णांकcount < 10) अणु
		XXDEBUG(("bmac_txdma_intr done->bmac_start\n"));
	पूर्ण

	bmac_start(dev);
	वापस IRQ_HANDLED;
पूर्ण

#अगर_अघोषित SUNHME_MULTICAST
/* Real fast bit-reversal algorithm, 6-bit values */
अटल पूर्णांक reverse6[64] = अणु
	0x0,0x20,0x10,0x30,0x8,0x28,0x18,0x38,
	0x4,0x24,0x14,0x34,0xc,0x2c,0x1c,0x3c,
	0x2,0x22,0x12,0x32,0xa,0x2a,0x1a,0x3a,
	0x6,0x26,0x16,0x36,0xe,0x2e,0x1e,0x3e,
	0x1,0x21,0x11,0x31,0x9,0x29,0x19,0x39,
	0x5,0x25,0x15,0x35,0xd,0x2d,0x1d,0x3d,
	0x3,0x23,0x13,0x33,0xb,0x2b,0x1b,0x3b,
	0x7,0x27,0x17,0x37,0xf,0x2f,0x1f,0x3f
पूर्ण;

अटल अचिन्हित पूर्णांक
crc416(अचिन्हित पूर्णांक curval, अचिन्हित लघु nxtval)
अणु
	अचिन्हित पूर्णांक counter, cur = curval, next = nxtval;
	पूर्णांक high_crc_set, low_data_set;

	/* Swap bytes */
	next = ((next & 0x00FF) << 8) | (next >> 8);

	/* Compute bit-by-bit */
	क्रम (counter = 0; counter < 16; ++counter) अणु
		/* is high CRC bit set? */
		अगर ((cur & 0x80000000) == 0) high_crc_set = 0;
		अन्यथा high_crc_set = 1;

		cur = cur << 1;

		अगर ((next & 0x0001) == 0) low_data_set = 0;
		अन्यथा low_data_set = 1;

		next = next >> 1;

		/* करो the XOR */
		अगर (high_crc_set ^ low_data_set) cur = cur ^ CRC32_POLY_BE;
	पूर्ण
	वापस cur;
पूर्ण

अटल अचिन्हित पूर्णांक
bmac_crc(अचिन्हित लघु *address)
अणु
	अचिन्हित पूर्णांक newcrc;

	XXDEBUG(("bmac_crc: addr=%#04x, %#04x, %#04x\n", *address, address[1], address[2]));
	newcrc = crc416(0xffffffff, *address);	/* address bits 47 - 32 */
	newcrc = crc416(newcrc, address[1]);	/* address bits 31 - 16 */
	newcrc = crc416(newcrc, address[2]);	/* address bits 15 - 0  */

	वापस(newcrc);
पूर्ण

/*
 * Add requested mcast addr to BMac's hash table filter.
 *
 */

अटल व्योम
bmac_addhash(काष्ठा bmac_data *bp, अचिन्हित अक्षर *addr)
अणु
	अचिन्हित पूर्णांक	 crc;
	अचिन्हित लघु	 mask;

	अगर (!(*addr)) वापस;
	crc = bmac_crc((अचिन्हित लघु *)addr) & 0x3f; /* Big-endian alert! */
	crc = reverse6[crc];	/* Hyperfast bit-reversing algorithm */
	अगर (bp->hash_use_count[crc]++) वापस; /* This bit is alपढ़ोy set */
	mask = crc % 16;
	mask = (अचिन्हित अक्षर)1 << mask;
	bp->hash_use_count[crc/16] |= mask;
पूर्ण

अटल व्योम
bmac_हटाओhash(काष्ठा bmac_data *bp, अचिन्हित अक्षर *addr)
अणु
	अचिन्हित पूर्णांक crc;
	अचिन्हित अक्षर mask;

	/* Now, delete the address from the filter copy, as indicated */
	crc = bmac_crc((अचिन्हित लघु *)addr) & 0x3f; /* Big-endian alert! */
	crc = reverse6[crc];	/* Hyperfast bit-reversing algorithm */
	अगर (bp->hash_use_count[crc] == 0) वापस; /* That bit wasn't in use! */
	अगर (--bp->hash_use_count[crc]) वापस; /* That bit is still in use */
	mask = crc % 16;
	mask = ((अचिन्हित अक्षर)1 << mask) ^ 0xffff; /* To turn off bit */
	bp->hash_table_mask[crc/16] &= mask;
पूर्ण

/*
 * Sync the adapter with the software copy of the multicast mask
 *  (logical address filter).
 */

अटल व्योम
bmac_rx_off(काष्ठा net_device *dev)
अणु
	अचिन्हित लघु rx_cfg;

	rx_cfg = bmपढ़ो(dev, RXCFG);
	rx_cfg &= ~RxMACEnable;
	bmग_लिखो(dev, RXCFG, rx_cfg);
	करो अणु
		rx_cfg = bmपढ़ो(dev, RXCFG);
	पूर्ण  जबतक (rx_cfg & RxMACEnable);
पूर्ण

अचिन्हित लघु
bmac_rx_on(काष्ठा net_device *dev, पूर्णांक hash_enable, पूर्णांक promisc_enable)
अणु
	अचिन्हित लघु rx_cfg;

	rx_cfg = bmपढ़ो(dev, RXCFG);
	rx_cfg |= RxMACEnable;
	अगर (hash_enable) rx_cfg |= RxHashFilterEnable;
	अन्यथा rx_cfg &= ~RxHashFilterEnable;
	अगर (promisc_enable) rx_cfg |= RxPromiscEnable;
	अन्यथा rx_cfg &= ~RxPromiscEnable;
	bmग_लिखो(dev, RXRST, RxResetValue);
	bmग_लिखो(dev, RXFIFOCSR, 0);	/* first disable rxFIFO */
	bmग_लिखो(dev, RXFIFOCSR, RxFIFOEnable );
	bmग_लिखो(dev, RXCFG, rx_cfg );
	वापस rx_cfg;
पूर्ण

अटल व्योम
bmac_update_hash_table_mask(काष्ठा net_device *dev, काष्ठा bmac_data *bp)
अणु
	bmग_लिखो(dev, BHASH3, bp->hash_table_mask[0]); /* bits 15 - 0 */
	bmग_लिखो(dev, BHASH2, bp->hash_table_mask[1]); /* bits 31 - 16 */
	bmग_लिखो(dev, BHASH1, bp->hash_table_mask[2]); /* bits 47 - 32 */
	bmग_लिखो(dev, BHASH0, bp->hash_table_mask[3]); /* bits 63 - 48 */
पूर्ण

#अगर 0
अटल व्योम
bmac_add_multi(काष्ठा net_device *dev,
	       काष्ठा bmac_data *bp, अचिन्हित अक्षर *addr)
अणु
	/* XXDEBUG(("bmac: enter bmac_add_multi\n")); */
	bmac_addhash(bp, addr);
	bmac_rx_off(dev);
	bmac_update_hash_table_mask(dev, bp);
	bmac_rx_on(dev, 1, (dev->flags & IFF_PROMISC)? 1 : 0);
	/* XXDEBUG(("bmac: exit bmac_add_multi\n")); */
पूर्ण

अटल व्योम
bmac_हटाओ_multi(काष्ठा net_device *dev,
		  काष्ठा bmac_data *bp, अचिन्हित अक्षर *addr)
अणु
	bmac_हटाओhash(bp, addr);
	bmac_rx_off(dev);
	bmac_update_hash_table_mask(dev, bp);
	bmac_rx_on(dev, 1, (dev->flags & IFF_PROMISC)? 1 : 0);
पूर्ण
#पूर्ण_अगर

/* Set or clear the multicast filter क्रम this adaptor.
    num_addrs == -1	Promiscuous mode, receive all packets
    num_addrs == 0	Normal mode, clear multicast list
    num_addrs > 0	Multicast mode, receive normal and MC packets, and करो
			best-efक्रमt filtering.
 */
अटल व्योम bmac_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	काष्ठा bmac_data *bp = netdev_priv(dev);
	पूर्णांक num_addrs = netdev_mc_count(dev);
	अचिन्हित लघु rx_cfg;
	पूर्णांक i;

	अगर (bp->sleeping)
		वापस;

	XXDEBUG(("bmac: enter bmac_set_multicast, n_addrs=%d\n", num_addrs));

	अगर((dev->flags & IFF_ALLMULTI) || (netdev_mc_count(dev) > 64)) अणु
		क्रम (i=0; i<4; i++) bp->hash_table_mask[i] = 0xffff;
		bmac_update_hash_table_mask(dev, bp);
		rx_cfg = bmac_rx_on(dev, 1, 0);
		XXDEBUG(("bmac: all multi, rx_cfg=%#08x\n"));
	पूर्ण अन्यथा अगर ((dev->flags & IFF_PROMISC) || (num_addrs < 0)) अणु
		rx_cfg = bmपढ़ो(dev, RXCFG);
		rx_cfg |= RxPromiscEnable;
		bmग_लिखो(dev, RXCFG, rx_cfg);
		rx_cfg = bmac_rx_on(dev, 0, 1);
		XXDEBUG(("bmac: promisc mode enabled, rx_cfg=%#08x\n", rx_cfg));
	पूर्ण अन्यथा अणु
		क्रम (i=0; i<4; i++) bp->hash_table_mask[i] = 0;
		क्रम (i=0; i<64; i++) bp->hash_use_count[i] = 0;
		अगर (num_addrs == 0) अणु
			rx_cfg = bmac_rx_on(dev, 0, 0);
			XXDEBUG(("bmac: multi disabled, rx_cfg=%#08x\n", rx_cfg));
		पूर्ण अन्यथा अणु
			netdev_क्रम_each_mc_addr(ha, dev)
				bmac_addhash(bp, ha->addr);
			bmac_update_hash_table_mask(dev, bp);
			rx_cfg = bmac_rx_on(dev, 1, 0);
			XXDEBUG(("bmac: multi enabled, rx_cfg=%#08x\n", rx_cfg));
		पूर्ण
	पूर्ण
	/* XXDEBUG(("bmac: exit bmac_set_multicast\n")); */
पूर्ण
#अन्यथा /* अगरdef SUNHME_MULTICAST */

/* The version of set_multicast below was lअगरted from sunhme.c */

अटल व्योम bmac_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित लघु rx_cfg;
	u32 crc;

	अगर((dev->flags & IFF_ALLMULTI) || (netdev_mc_count(dev) > 64)) अणु
		bmग_लिखो(dev, BHASH0, 0xffff);
		bmग_लिखो(dev, BHASH1, 0xffff);
		bmग_लिखो(dev, BHASH2, 0xffff);
		bmग_लिखो(dev, BHASH3, 0xffff);
	पूर्ण अन्यथा अगर(dev->flags & IFF_PROMISC) अणु
		rx_cfg = bmपढ़ो(dev, RXCFG);
		rx_cfg |= RxPromiscEnable;
		bmग_लिखो(dev, RXCFG, rx_cfg);
	पूर्ण अन्यथा अणु
		u16 hash_table[4] = अणु 0 पूर्ण;

		rx_cfg = bmपढ़ो(dev, RXCFG);
		rx_cfg &= ~RxPromiscEnable;
		bmग_लिखो(dev, RXCFG, rx_cfg);

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			crc = ether_crc_le(6, ha->addr);
			crc >>= 26;
			hash_table[crc >> 4] |= 1 << (crc & 0xf);
		पूर्ण
		bmग_लिखो(dev, BHASH0, hash_table[0]);
		bmग_लिखो(dev, BHASH1, hash_table[1]);
		bmग_लिखो(dev, BHASH2, hash_table[2]);
		bmग_लिखो(dev, BHASH3, hash_table[3]);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* SUNHME_MULTICAST */

अटल पूर्णांक miscपूर्णांकcount;

अटल irqवापस_t bmac_misc_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
	अचिन्हित पूर्णांक status = bmपढ़ो(dev, STATUS);
	अगर (miscपूर्णांकcount++ < 10) अणु
		XXDEBUG(("bmac_misc_intr\n"));
	पूर्ण
	/* XXDEBUG(("bmac_misc_intr, status=%#08x\n", status)); */
	/*     bmac_txdma_पूर्णांकr_inner(irq, dev_id); */
	/*   अगर (status & FrameReceived) dev->stats.rx_dropped++; */
	अगर (status & RxErrorMask) dev->stats.rx_errors++;
	अगर (status & RxCRCCntExp) dev->stats.rx_crc_errors++;
	अगर (status & RxLenCntExp) dev->stats.rx_length_errors++;
	अगर (status & RxOverFlow) dev->stats.rx_over_errors++;
	अगर (status & RxAlignCntExp) dev->stats.rx_frame_errors++;

	/*   अगर (status & FrameSent) dev->stats.tx_dropped++; */
	अगर (status & TxErrorMask) dev->stats.tx_errors++;
	अगर (status & TxUnderrun) dev->stats.tx_fअगरo_errors++;
	अगर (status & TxNormalCollExp) dev->stats.collisions++;
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Procedure क्रम पढ़ोing EEPROM
 */
#घोषणा SROMAddressLength	5
#घोषणा DataInOn		0x0008
#घोषणा DataInOff		0x0000
#घोषणा Clk			0x0002
#घोषणा ChipSelect		0x0001
#घोषणा SDIShअगरtCount		3
#घोषणा SD0ShअगरtCount		2
#घोषणा	DelayValue		1000	/* number of microseconds */
#घोषणा SROMStartOffset		10	/* this is in words */
#घोषणा SROMReadCount		3	/* number of words to पढ़ो from SROM */
#घोषणा SROMAddressBits		6
#घोषणा EnetAddressOffset	20

अटल अचिन्हित अक्षर
bmac_घड़ी_out_bit(काष्ठा net_device *dev)
अणु
	अचिन्हित लघु         data;
	अचिन्हित लघु         val;

	bmग_लिखो(dev, SROMCSR, ChipSelect | Clk);
	udelay(DelayValue);

	data = bmपढ़ो(dev, SROMCSR);
	udelay(DelayValue);
	val = (data >> SD0ShअगरtCount) & 1;

	bmग_लिखो(dev, SROMCSR, ChipSelect);
	udelay(DelayValue);

	वापस val;
पूर्ण

अटल व्योम
bmac_घड़ी_in_bit(काष्ठा net_device *dev, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित लघु data;

	अगर (val != 0 && val != 1) वापस;

	data = (val << SDIShअगरtCount);
	bmग_लिखो(dev, SROMCSR, data | ChipSelect  );
	udelay(DelayValue);

	bmग_लिखो(dev, SROMCSR, data | ChipSelect | Clk );
	udelay(DelayValue);

	bmग_लिखो(dev, SROMCSR, data | ChipSelect);
	udelay(DelayValue);
पूर्ण

अटल व्योम
reset_and_select_srom(काष्ठा net_device *dev)
अणु
	/* first reset */
	bmग_लिखो(dev, SROMCSR, 0);
	udelay(DelayValue);

	/* send it the पढ़ो command (110) */
	bmac_घड़ी_in_bit(dev, 1);
	bmac_घड़ी_in_bit(dev, 1);
	bmac_घड़ी_in_bit(dev, 0);
पूर्ण

अटल अचिन्हित लघु
पढ़ो_srom(काष्ठा net_device *dev, अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक addr_len)
अणु
	अचिन्हित लघु data, val;
	पूर्णांक i;

	/* send out the address we want to पढ़ो from */
	क्रम (i = 0; i < addr_len; i++)	अणु
		val = addr >> (addr_len-i-1);
		bmac_घड़ी_in_bit(dev, val & 1);
	पूर्ण

	/* Now पढ़ो in the 16-bit data */
	data = 0;
	क्रम (i = 0; i < 16; i++)	अणु
		val = bmac_घड़ी_out_bit(dev);
		data <<= 1;
		data |= val;
	पूर्ण
	bmग_लिखो(dev, SROMCSR, 0);

	वापस data;
पूर्ण

/*
 * It looks like Cogent and SMC use dअगरferent methods क्रम calculating
 * checksums. What a pain..
 */

अटल पूर्णांक
bmac_verअगरy_checksum(काष्ठा net_device *dev)
अणु
	अचिन्हित लघु data, storedCS;

	reset_and_select_srom(dev);
	data = पढ़ो_srom(dev, 3, SROMAddressBits);
	storedCS = ((data >> 8) & 0x0ff) | ((data << 8) & 0xff00);

	वापस 0;
पूर्ण


अटल व्योम
bmac_get_station_address(काष्ठा net_device *dev, अचिन्हित अक्षर *ea)
अणु
	पूर्णांक i;
	अचिन्हित लघु data;

	क्रम (i = 0; i < 3; i++)
		अणु
			reset_and_select_srom(dev);
			data = पढ़ो_srom(dev, i + EnetAddressOffset/2, SROMAddressBits);
			ea[2*i]   = bitrev8(data & 0x0ff);
			ea[2*i+1] = bitrev8((data >> 8) & 0x0ff);
		पूर्ण
पूर्ण

अटल व्योम bmac_reset_and_enable(काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *data;

	spin_lock_irqsave(&bp->lock, flags);
	bmac_enable_and_reset_chip(dev);
	bmac_init_tx_ring(bp);
	bmac_init_rx_ring(dev);
	bmac_init_chip(dev);
	bmac_start_chip(dev);
	bmग_लिखो(dev, INTDISABLE, EnableNormal);
	bp->sleeping = 0;

	/*
	 * It seems that the bmac can't receive until it's transmitted
	 * a packet.  So we give it a dummy packet to transmit.
	 */
	skb = netdev_alloc_skb(dev, ETHERMINPACKET);
	अगर (skb != शून्य) अणु
		data = skb_put_zero(skb, ETHERMINPACKET);
		स_नकल(data, dev->dev_addr, ETH_ALEN);
		स_नकल(data + ETH_ALEN, dev->dev_addr, ETH_ALEN);
		bmac_transmit_packet(skb, dev);
	पूर्ण
	spin_unlock_irqrestore(&bp->lock, flags);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bmac_ethtool_ops = अणु
	.get_link		= ethtool_op_get_link,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops bmac_netdev_ops = अणु
	.nकरो_खोलो		= bmac_खोलो,
	.nकरो_stop		= bmac_बंद,
	.nकरो_start_xmit		= bmac_output,
	.nकरो_set_rx_mode	= bmac_set_multicast,
	.nकरो_set_mac_address	= bmac_set_address,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक bmac_probe(काष्ठा macio_dev *mdev, स्थिर काष्ठा of_device_id *match)
अणु
	पूर्णांक j, rev, ret;
	काष्ठा bmac_data *bp;
	स्थिर अचिन्हित अक्षर *prop_addr;
	अचिन्हित अक्षर addr[6];
	काष्ठा net_device *dev;
	पूर्णांक is_bmac_plus = ((पूर्णांक)match->data) != 0;

	अगर (macio_resource_count(mdev) != 3 || macio_irq_count(mdev) != 3) अणु
		prपूर्णांकk(KERN_ERR "BMAC: can't use, need 3 addrs and 3 intrs\n");
		वापस -ENODEV;
	पूर्ण
	prop_addr = of_get_property(macio_get_of_node(mdev),
			"mac-address", शून्य);
	अगर (prop_addr == शून्य) अणु
		prop_addr = of_get_property(macio_get_of_node(mdev),
				"local-mac-address", शून्य);
		अगर (prop_addr == शून्य) अणु
			prपूर्णांकk(KERN_ERR "BMAC: Can't get mac-address\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	स_नकल(addr, prop_addr, माप(addr));

	dev = alloc_etherdev(PRIV_BYTES);
	अगर (!dev)
		वापस -ENOMEM;

	bp = netdev_priv(dev);
	SET_NETDEV_DEV(dev, &mdev->ofdev.dev);
	macio_set_drvdata(mdev, dev);

	bp->mdev = mdev;
	spin_lock_init(&bp->lock);

	अगर (macio_request_resources(mdev, "bmac")) अणु
		prपूर्णांकk(KERN_ERR "BMAC: can't request IO resource !\n");
		जाओ out_मुक्त;
	पूर्ण

	dev->base_addr = (अचिन्हित दीर्घ)
		ioremap(macio_resource_start(mdev, 0), macio_resource_len(mdev, 0));
	अगर (dev->base_addr == 0)
		जाओ out_release;

	dev->irq = macio_irq(mdev, 0);

	bmac_enable_and_reset_chip(dev);
	bmग_लिखो(dev, INTDISABLE, DisableAll);

	rev = addr[0] == 0 && addr[1] == 0xA0;
	क्रम (j = 0; j < 6; ++j)
		dev->dev_addr[j] = rev ? bitrev8(addr[j]): addr[j];

	/* Enable chip without पूर्णांकerrupts क्रम now */
	bmac_enable_and_reset_chip(dev);
	bmग_लिखो(dev, INTDISABLE, DisableAll);

	dev->netdev_ops = &bmac_netdev_ops;
	dev->ethtool_ops = &bmac_ethtool_ops;

	bmac_get_station_address(dev, addr);
	अगर (bmac_verअगरy_checksum(dev) != 0)
		जाओ err_out_iounmap;

	bp->is_bmac_plus = is_bmac_plus;
	bp->tx_dma = ioremap(macio_resource_start(mdev, 1), macio_resource_len(mdev, 1));
	अगर (!bp->tx_dma)
		जाओ err_out_iounmap;
	bp->tx_dma_पूर्णांकr = macio_irq(mdev, 1);
	bp->rx_dma = ioremap(macio_resource_start(mdev, 2), macio_resource_len(mdev, 2));
	अगर (!bp->rx_dma)
		जाओ err_out_iounmap_tx;
	bp->rx_dma_पूर्णांकr = macio_irq(mdev, 2);

	bp->tx_cmds = (अस्थिर काष्ठा dbdma_cmd *) DBDMA_ALIGN(bp + 1);
	bp->rx_cmds = bp->tx_cmds + N_TX_RING + 1;

	bp->queue = (काष्ठा sk_buff_head *)(bp->rx_cmds + N_RX_RING + 1);
	skb_queue_head_init(bp->queue);

	समयr_setup(&bp->tx_समयout, bmac_tx_समयout, 0);

	ret = request_irq(dev->irq, bmac_misc_पूर्णांकr, 0, "BMAC-misc", dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "BMAC: can't get irq %d\n", dev->irq);
		जाओ err_out_iounmap_rx;
	पूर्ण
	ret = request_irq(bp->tx_dma_पूर्णांकr, bmac_txdma_पूर्णांकr, 0, "BMAC-txdma", dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "BMAC: can't get irq %d\n", bp->tx_dma_पूर्णांकr);
		जाओ err_out_irq0;
	पूर्ण
	ret = request_irq(bp->rx_dma_पूर्णांकr, bmac_rxdma_पूर्णांकr, 0, "BMAC-rxdma", dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "BMAC: can't get irq %d\n", bp->rx_dma_पूर्णांकr);
		जाओ err_out_irq1;
	पूर्ण

	/* Mask chip पूर्णांकerrupts and disable chip, will be
	 * re-enabled on खोलो()
	 */
	disable_irq(dev->irq);
	pmac_call_feature(PMAC_FTR_BMAC_ENABLE, macio_get_of_node(bp->mdev), 0, 0);

	अगर (रेजिस्टर_netdev(dev) != 0) अणु
		prपूर्णांकk(KERN_ERR "BMAC: Ethernet registration failed\n");
		जाओ err_out_irq2;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: BMAC%s at %pM",
	       dev->name, (is_bmac_plus ? "+" : ""), dev->dev_addr);
	XXDEBUG((", base_addr=%#0lx", dev->base_addr));
	prपूर्णांकk("\n");

	वापस 0;

err_out_irq2:
	मुक्त_irq(bp->rx_dma_पूर्णांकr, dev);
err_out_irq1:
	मुक्त_irq(bp->tx_dma_पूर्णांकr, dev);
err_out_irq0:
	मुक्त_irq(dev->irq, dev);
err_out_iounmap_rx:
	iounmap(bp->rx_dma);
err_out_iounmap_tx:
	iounmap(bp->tx_dma);
err_out_iounmap:
	iounmap((व्योम __iomem *)dev->base_addr);
out_release:
	macio_release_resources(mdev);
out_मुक्त:
	pmac_call_feature(PMAC_FTR_BMAC_ENABLE, macio_get_of_node(bp->mdev), 0, 0);
	मुक्त_netdev(dev);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक bmac_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	/* XXDEBUG(("bmac: enter open\n")); */
	/* reset the chip */
	bp->खोलोed = 1;
	bmac_reset_and_enable(dev);
	enable_irq(dev->irq);
	वापस 0;
पूर्ण

अटल पूर्णांक bmac_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	अस्थिर काष्ठा dbdma_regs __iomem *rd = bp->rx_dma;
	अस्थिर काष्ठा dbdma_regs __iomem *td = bp->tx_dma;
	अचिन्हित लघु config;
	पूर्णांक i;

	bp->sleeping = 1;

	/* disable rx and tx */
	config = bmपढ़ो(dev, RXCFG);
	bmग_लिखो(dev, RXCFG, (config & ~RxMACEnable));

	config = bmपढ़ो(dev, TXCFG);
	bmग_लिखो(dev, TXCFG, (config & ~TxMACEnable));

	bmग_लिखो(dev, INTDISABLE, DisableAll); /* disable all पूर्णांकrs */

	/* disable rx and tx dma */
	rd->control = cpu_to_le32(DBDMA_CLEAR(RUN|PAUSE|FLUSH|WAKE));	/* clear run bit */
	td->control = cpu_to_le32(DBDMA_CLEAR(RUN|PAUSE|FLUSH|WAKE));	/* clear run bit */

	/* मुक्त some skb's */
	XXDEBUG(("bmac: free rx bufs\n"));
	क्रम (i=0; i<N_RX_RING; i++) अणु
		अगर (bp->rx_bufs[i] != शून्य) अणु
			dev_kमुक्त_skb(bp->rx_bufs[i]);
			bp->rx_bufs[i] = शून्य;
		पूर्ण
	पूर्ण
	XXDEBUG(("bmac: free tx bufs\n"));
	क्रम (i = 0; i<N_TX_RING; i++) अणु
		अगर (bp->tx_bufs[i] != शून्य) अणु
			dev_kमुक्त_skb(bp->tx_bufs[i]);
			bp->tx_bufs[i] = शून्य;
		पूर्ण
	पूर्ण
	XXDEBUG(("bmac: all bufs freed\n"));

	bp->खोलोed = 0;
	disable_irq(dev->irq);
	pmac_call_feature(PMAC_FTR_BMAC_ENABLE, macio_get_of_node(bp->mdev), 0, 0);

	वापस 0;
पूर्ण

अटल व्योम
bmac_start(काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	अगर (bp->sleeping)
		वापस;

	spin_lock_irqsave(&bp->lock, flags);
	जबतक (1) अणु
		i = bp->tx_fill + 1;
		अगर (i >= N_TX_RING)
			i = 0;
		अगर (i == bp->tx_empty)
			अवरोध;
		skb = skb_dequeue(bp->queue);
		अगर (skb == शून्य)
			अवरोध;
		bmac_transmit_packet(skb, dev);
	पूर्ण
	spin_unlock_irqrestore(&bp->lock, flags);
पूर्ण

अटल netdev_tx_t
bmac_output(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bmac_data *bp = netdev_priv(dev);
	skb_queue_tail(bp->queue, skb);
	bmac_start(dev);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम bmac_tx_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा bmac_data *bp = from_समयr(bp, t, tx_समयout);
	काष्ठा net_device *dev = macio_get_drvdata(bp->mdev);
	अस्थिर काष्ठा dbdma_regs __iomem *td = bp->tx_dma;
	अस्थिर काष्ठा dbdma_regs __iomem *rd = bp->rx_dma;
	अस्थिर काष्ठा dbdma_cmd *cp;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु config, oldConfig;
	पूर्णांक i;

	XXDEBUG(("bmac: tx_timeout called\n"));
	spin_lock_irqsave(&bp->lock, flags);
	bp->समयout_active = 0;

	/* update various counters */
/*     	bmac_handle_misc_पूर्णांकrs(bp, 0); */

	cp = &bp->tx_cmds[bp->tx_empty];
/*	XXDEBUG((KERN_DEBUG "bmac: tx dmastat=%x %x runt=%d pr=%x fs=%x fc=%x\n", */
/* 	   le32_to_cpu(td->status), le16_to_cpu(cp->xfer_status), bp->tx_bad_runt, */
/* 	   mb->pr, mb->xmtfs, mb->fअगरofc)); */

	/* turn off both tx and rx and reset the chip */
	config = bmपढ़ो(dev, RXCFG);
	bmग_लिखो(dev, RXCFG, (config & ~RxMACEnable));
	config = bmपढ़ो(dev, TXCFG);
	bmग_लिखो(dev, TXCFG, (config & ~TxMACEnable));
	out_le32(&td->control, DBDMA_CLEAR(RUN|PAUSE|FLUSH|WAKE|ACTIVE|DEAD));
	prपूर्णांकk(KERN_ERR "bmac: transmit timeout - resetting\n");
	bmac_enable_and_reset_chip(dev);

	/* restart rx dma */
	cp = bus_to_virt(le32_to_cpu(rd->cmdptr));
	out_le32(&rd->control, DBDMA_CLEAR(RUN|PAUSE|FLUSH|WAKE|ACTIVE|DEAD));
	out_le16(&cp->xfer_status, 0);
	out_le32(&rd->cmdptr, virt_to_bus(cp));
	out_le32(&rd->control, DBDMA_SET(RUN|WAKE));

	/* fix up the transmit side */
	XXDEBUG((KERN_DEBUG "bmac: tx empty=%d fill=%d fullup=%d\n",
		 bp->tx_empty, bp->tx_fill, bp->tx_fullup));
	i = bp->tx_empty;
	++dev->stats.tx_errors;
	अगर (i != bp->tx_fill) अणु
		dev_kमुक्त_skb(bp->tx_bufs[i]);
		bp->tx_bufs[i] = शून्य;
		अगर (++i >= N_TX_RING) i = 0;
		bp->tx_empty = i;
	पूर्ण
	bp->tx_fullup = 0;
	netअगर_wake_queue(dev);
	अगर (i != bp->tx_fill) अणु
		cp = &bp->tx_cmds[i];
		out_le16(&cp->xfer_status, 0);
		out_le16(&cp->command, OUTPUT_LAST);
		out_le32(&td->cmdptr, virt_to_bus(cp));
		out_le32(&td->control, DBDMA_SET(RUN));
		/* 	bmac_set_समयout(dev); */
		XXDEBUG((KERN_DEBUG "bmac: starting %d\n", i));
	पूर्ण

	/* turn it back on */
	oldConfig = bmपढ़ो(dev, RXCFG);
	bmग_लिखो(dev, RXCFG, oldConfig | RxMACEnable );
	oldConfig = bmपढ़ो(dev, TXCFG);
	bmग_लिखो(dev, TXCFG, oldConfig | TxMACEnable );

	spin_unlock_irqrestore(&bp->lock, flags);
पूर्ण

#अगर 0
अटल व्योम dump_dbdma(अस्थिर काष्ठा dbdma_cmd *cp,पूर्णांक count)
अणु
	पूर्णांक i,*ip;

	क्रम (i=0;i< count;i++) अणु
		ip = (पूर्णांक*)(cp+i);

		prपूर्णांकk("dbdma req 0x%x addr 0x%x baddr 0x%x xfer/res 0x%x\n",
		       le32_to_cpup(ip+0),
		       le32_to_cpup(ip+1),
		       le32_to_cpup(ip+2),
		       le32_to_cpup(ip+3));
	पूर्ण

पूर्ण
#पूर्ण_अगर

#अगर 0
अटल पूर्णांक
bmac_proc_info(अक्षर *buffer, अक्षर **start, off_t offset, पूर्णांक length)
अणु
	पूर्णांक len = 0;
	off_t pos   = 0;
	off_t begin = 0;
	पूर्णांक i;

	अगर (bmac_devs == शून्य)
		वापस -ENOSYS;

	len += प्र_लिखो(buffer, "BMAC counters & registers\n");

	क्रम (i = 0; i<N_REG_ENTRIES; i++) अणु
		len += प्र_लिखो(buffer + len, "%s: %#08x\n",
			       reg_entries[i].name,
			       bmपढ़ो(bmac_devs, reg_entries[i].reg_offset));
		pos = begin + len;

		अगर (pos < offset) अणु
			len = 0;
			begin = pos;
		पूर्ण

		अगर (pos > offset+length) अवरोध;
	पूर्ण

	*start = buffer + (offset - begin);
	len -= (offset - begin);

	अगर (len > length) len = length;

	वापस len;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक bmac_हटाओ(काष्ठा macio_dev *mdev)
अणु
	काष्ठा net_device *dev = macio_get_drvdata(mdev);
	काष्ठा bmac_data *bp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);

       	मुक्त_irq(dev->irq, dev);
	मुक्त_irq(bp->tx_dma_पूर्णांकr, dev);
	मुक्त_irq(bp->rx_dma_पूर्णांकr, dev);

	iounmap((व्योम __iomem *)dev->base_addr);
	iounmap(bp->tx_dma);
	iounmap(bp->rx_dma);

	macio_release_resources(mdev);

	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bmac_match[] =
अणु
	अणु
	.name 		= "bmac",
	.data		= (व्योम *)0,
	पूर्ण,
	अणु
	.type		= "network",
	.compatible	= "bmac+",
	.data		= (व्योम *)1,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE (of, bmac_match);

अटल काष्ठा macio_driver bmac_driver =
अणु
	.driver = अणु
		.name 		= "bmac",
		.owner		= THIS_MODULE,
		.of_match_table	= bmac_match,
	पूर्ण,
	.probe		= bmac_probe,
	.हटाओ		= bmac_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= bmac_suspend,
	.resume		= bmac_resume,
#पूर्ण_अगर
पूर्ण;


अटल पूर्णांक __init bmac_init(व्योम)
अणु
	अगर (bmac_emergency_rxbuf == शून्य) अणु
		bmac_emergency_rxbuf = kदो_स्मृति(RX_BUFLEN, GFP_KERNEL);
		अगर (bmac_emergency_rxbuf == शून्य)
			वापस -ENOMEM;
	पूर्ण

	वापस macio_रेजिस्टर_driver(&bmac_driver);
पूर्ण

अटल व्योम __निकास bmac_निकास(व्योम)
अणु
	macio_unरेजिस्टर_driver(&bmac_driver);

	kमुक्त(bmac_emergency_rxbuf);
	bmac_emergency_rxbuf = शून्य;
पूर्ण

MODULE_AUTHOR("Randy Gobbel/Paul Mackerras");
MODULE_DESCRIPTION("PowerMac BMAC ethernet driver.");
MODULE_LICENSE("GPL");

module_init(bmac_init);
module_निकास(bmac_निकास);
