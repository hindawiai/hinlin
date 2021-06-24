<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * EP93xx ethernet network device driver
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 * Dedicated to Marija Kulikova.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mii.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_data/eth-ep93xx.h>

#घोषणा DRV_MODULE_NAME		"ep93xx-eth"

#घोषणा RX_QUEUE_ENTRIES	64
#घोषणा TX_QUEUE_ENTRIES	8

#घोषणा MAX_PKT_SIZE		2044
#घोषणा PKT_BUF_SIZE		2048

#घोषणा REG_RXCTL		0x0000
#घोषणा  REG_RXCTL_DEFAULT	0x00073800
#घोषणा REG_TXCTL		0x0004
#घोषणा  REG_TXCTL_ENABLE	0x00000001
#घोषणा REG_MIICMD		0x0010
#घोषणा  REG_MIICMD_READ	0x00008000
#घोषणा  REG_MIICMD_WRITE	0x00004000
#घोषणा REG_MIIDATA		0x0014
#घोषणा REG_MIISTS		0x0018
#घोषणा  REG_MIISTS_BUSY	0x00000001
#घोषणा REG_SELFCTL		0x0020
#घोषणा  REG_SELFCTL_RESET	0x00000001
#घोषणा REG_INTEN		0x0024
#घोषणा  REG_INTEN_TX		0x00000008
#घोषणा  REG_INTEN_RX		0x00000007
#घोषणा REG_INTSTSP		0x0028
#घोषणा  REG_INTSTS_TX		0x00000008
#घोषणा  REG_INTSTS_RX		0x00000004
#घोषणा REG_INTSTSC		0x002c
#घोषणा REG_AFP			0x004c
#घोषणा REG_INDAD0		0x0050
#घोषणा REG_INDAD1		0x0051
#घोषणा REG_INDAD2		0x0052
#घोषणा REG_INDAD3		0x0053
#घोषणा REG_INDAD4		0x0054
#घोषणा REG_INDAD5		0x0055
#घोषणा REG_GIINTMSK		0x0064
#घोषणा  REG_GIINTMSK_ENABLE	0x00008000
#घोषणा REG_BMCTL		0x0080
#घोषणा  REG_BMCTL_ENABLE_TX	0x00000100
#घोषणा  REG_BMCTL_ENABLE_RX	0x00000001
#घोषणा REG_BMSTS		0x0084
#घोषणा  REG_BMSTS_RX_ACTIVE	0x00000008
#घोषणा REG_RXDQBADD		0x0090
#घोषणा REG_RXDQBLEN		0x0094
#घोषणा REG_RXDCURADD		0x0098
#घोषणा REG_RXDENQ		0x009c
#घोषणा REG_RXSTSQBADD		0x00a0
#घोषणा REG_RXSTSQBLEN		0x00a4
#घोषणा REG_RXSTSQCURADD	0x00a8
#घोषणा REG_RXSTSENQ		0x00ac
#घोषणा REG_TXDQBADD		0x00b0
#घोषणा REG_TXDQBLEN		0x00b4
#घोषणा REG_TXDQCURADD		0x00b8
#घोषणा REG_TXDENQ		0x00bc
#घोषणा REG_TXSTSQBADD		0x00c0
#घोषणा REG_TXSTSQBLEN		0x00c4
#घोषणा REG_TXSTSQCURADD	0x00c8
#घोषणा REG_MAXFRMLEN		0x00e8

काष्ठा ep93xx_rdesc
अणु
	u32	buf_addr;
	u32	rdesc1;
पूर्ण;

#घोषणा RDESC1_NSOF		0x80000000
#घोषणा RDESC1_BUFFER_INDEX	0x7fff0000
#घोषणा RDESC1_BUFFER_LENGTH	0x0000ffff

काष्ठा ep93xx_rstat
अणु
	u32	rstat0;
	u32	rstat1;
पूर्ण;

#घोषणा RSTAT0_RFP		0x80000000
#घोषणा RSTAT0_RWE		0x40000000
#घोषणा RSTAT0_खातापूर्ण		0x20000000
#घोषणा RSTAT0_EOB		0x10000000
#घोषणा RSTAT0_AM		0x00c00000
#घोषणा RSTAT0_RX_ERR		0x00200000
#घोषणा RSTAT0_OE		0x00100000
#घोषणा RSTAT0_FE		0x00080000
#घोषणा RSTAT0_RUNT		0x00040000
#घोषणा RSTAT0_EDATA		0x00020000
#घोषणा RSTAT0_CRCE		0x00010000
#घोषणा RSTAT0_CRCI		0x00008000
#घोषणा RSTAT0_HTI		0x00003f00
#घोषणा RSTAT1_RFP		0x80000000
#घोषणा RSTAT1_BUFFER_INDEX	0x7fff0000
#घोषणा RSTAT1_FRAME_LENGTH	0x0000ffff

काष्ठा ep93xx_tdesc
अणु
	u32	buf_addr;
	u32	tdesc1;
पूर्ण;

#घोषणा TDESC1_खातापूर्ण		0x80000000
#घोषणा TDESC1_BUFFER_INDEX	0x7fff0000
#घोषणा TDESC1_BUFFER_ABORT	0x00008000
#घोषणा TDESC1_BUFFER_LENGTH	0x00000fff

काष्ठा ep93xx_tstat
अणु
	u32	tstat0;
पूर्ण;

#घोषणा TSTAT0_TXFP		0x80000000
#घोषणा TSTAT0_TXWE		0x40000000
#घोषणा TSTAT0_FA		0x20000000
#घोषणा TSTAT0_LCRS		0x10000000
#घोषणा TSTAT0_OW		0x04000000
#घोषणा TSTAT0_TXU		0x02000000
#घोषणा TSTAT0_ECOLL		0x01000000
#घोषणा TSTAT0_NCOLL		0x001f0000
#घोषणा TSTAT0_BUFFER_INDEX	0x00007fff

काष्ठा ep93xx_descs
अणु
	काष्ठा ep93xx_rdesc	rdesc[RX_QUEUE_ENTRIES];
	काष्ठा ep93xx_tdesc	tdesc[TX_QUEUE_ENTRIES];
	काष्ठा ep93xx_rstat	rstat[RX_QUEUE_ENTRIES];
	काष्ठा ep93xx_tstat	tstat[TX_QUEUE_ENTRIES];
पूर्ण;

काष्ठा ep93xx_priv
अणु
	काष्ठा resource		*res;
	व्योम __iomem		*base_addr;
	पूर्णांक			irq;

	काष्ठा ep93xx_descs	*descs;
	dma_addr_t		descs_dma_addr;

	व्योम			*rx_buf[RX_QUEUE_ENTRIES];
	व्योम			*tx_buf[TX_QUEUE_ENTRIES];

	spinlock_t		rx_lock;
	अचिन्हित पूर्णांक		rx_poपूर्णांकer;
	अचिन्हित पूर्णांक		tx_clean_poपूर्णांकer;
	अचिन्हित पूर्णांक		tx_poपूर्णांकer;
	spinlock_t		tx_pending_lock;
	अचिन्हित पूर्णांक		tx_pending;

	काष्ठा net_device	*dev;
	काष्ठा napi_काष्ठा	napi;

	काष्ठा mii_अगर_info	mii;
	u8			mdc_भागisor;
पूर्ण;

#घोषणा rdb(ep, off)		__raw_पढ़ोb((ep)->base_addr + (off))
#घोषणा rdw(ep, off)		__raw_पढ़ोw((ep)->base_addr + (off))
#घोषणा rdl(ep, off)		__raw_पढ़ोl((ep)->base_addr + (off))
#घोषणा wrb(ep, off, val)	__raw_ग_लिखोb((val), (ep)->base_addr + (off))
#घोषणा wrw(ep, off, val)	__raw_ग_लिखोw((val), (ep)->base_addr + (off))
#घोषणा wrl(ep, off, val)	__raw_ग_लिखोl((val), (ep)->base_addr + (off))

अटल पूर्णांक ep93xx_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	पूर्णांक data;
	पूर्णांक i;

	wrl(ep, REG_MIICMD, REG_MIICMD_READ | (phy_id << 5) | reg);

	क्रम (i = 0; i < 10; i++) अणु
		अगर ((rdl(ep, REG_MIISTS) & REG_MIISTS_BUSY) == 0)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i == 10) अणु
		pr_info("mdio read timed out\n");
		data = 0xffff;
	पूर्ण अन्यथा अणु
		data = rdl(ep, REG_MIIDATA);
	पूर्ण

	वापस data;
पूर्ण

अटल व्योम ep93xx_mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg, पूर्णांक data)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	पूर्णांक i;

	wrl(ep, REG_MIIDATA, data);
	wrl(ep, REG_MIICMD, REG_MIICMD_WRITE | (phy_id << 5) | reg);

	क्रम (i = 0; i < 10; i++) अणु
		अगर ((rdl(ep, REG_MIISTS) & REG_MIISTS_BUSY) == 0)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i == 10)
		pr_info("mdio write timed out\n");
पूर्ण

अटल पूर्णांक ep93xx_rx(काष्ठा net_device *dev, पूर्णांक budget)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	पूर्णांक processed = 0;

	जबतक (processed < budget) अणु
		पूर्णांक entry;
		काष्ठा ep93xx_rstat *rstat;
		u32 rstat0;
		u32 rstat1;
		पूर्णांक length;
		काष्ठा sk_buff *skb;

		entry = ep->rx_poपूर्णांकer;
		rstat = ep->descs->rstat + entry;

		rstat0 = rstat->rstat0;
		rstat1 = rstat->rstat1;
		अगर (!(rstat0 & RSTAT0_RFP) || !(rstat1 & RSTAT1_RFP))
			अवरोध;

		rstat->rstat0 = 0;
		rstat->rstat1 = 0;

		अगर (!(rstat0 & RSTAT0_खातापूर्ण))
			pr_crit("not end-of-frame %.8x %.8x\n", rstat0, rstat1);
		अगर (!(rstat0 & RSTAT0_EOB))
			pr_crit("not end-of-buffer %.8x %.8x\n", rstat0, rstat1);
		अगर ((rstat1 & RSTAT1_BUFFER_INDEX) >> 16 != entry)
			pr_crit("entry mismatch %.8x %.8x\n", rstat0, rstat1);

		अगर (!(rstat0 & RSTAT0_RWE)) अणु
			dev->stats.rx_errors++;
			अगर (rstat0 & RSTAT0_OE)
				dev->stats.rx_fअगरo_errors++;
			अगर (rstat0 & RSTAT0_FE)
				dev->stats.rx_frame_errors++;
			अगर (rstat0 & (RSTAT0_RUNT | RSTAT0_EDATA))
				dev->stats.rx_length_errors++;
			अगर (rstat0 & RSTAT0_CRCE)
				dev->stats.rx_crc_errors++;
			जाओ err;
		पूर्ण

		length = rstat1 & RSTAT1_FRAME_LENGTH;
		अगर (length > MAX_PKT_SIZE) अणु
			pr_notice("invalid length %.8x %.8x\n", rstat0, rstat1);
			जाओ err;
		पूर्ण

		/* Strip FCS.  */
		अगर (rstat0 & RSTAT0_CRCI)
			length -= 4;

		skb = netdev_alloc_skb(dev, length + 2);
		अगर (likely(skb != शून्य)) अणु
			काष्ठा ep93xx_rdesc *rxd = &ep->descs->rdesc[entry];
			skb_reserve(skb, 2);
			dma_sync_single_क्रम_cpu(dev->dev.parent, rxd->buf_addr,
						length, DMA_FROM_DEVICE);
			skb_copy_to_linear_data(skb, ep->rx_buf[entry], length);
			dma_sync_single_क्रम_device(dev->dev.parent,
						   rxd->buf_addr, length,
						   DMA_FROM_DEVICE);
			skb_put(skb, length);
			skb->protocol = eth_type_trans(skb, dev);

			napi_gro_receive(&ep->napi, skb);

			dev->stats.rx_packets++;
			dev->stats.rx_bytes += length;
		पूर्ण अन्यथा अणु
			dev->stats.rx_dropped++;
		पूर्ण

err:
		ep->rx_poपूर्णांकer = (entry + 1) & (RX_QUEUE_ENTRIES - 1);
		processed++;
	पूर्ण

	वापस processed;
पूर्ण

अटल पूर्णांक ep93xx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ep93xx_priv *ep = container_of(napi, काष्ठा ep93xx_priv, napi);
	काष्ठा net_device *dev = ep->dev;
	पूर्णांक rx;

	rx = ep93xx_rx(dev, budget);
	अगर (rx < budget && napi_complete_करोne(napi, rx)) अणु
		spin_lock_irq(&ep->rx_lock);
		wrl(ep, REG_INTEN, REG_INTEN_TX | REG_INTEN_RX);
		spin_unlock_irq(&ep->rx_lock);
	पूर्ण

	अगर (rx) अणु
		wrw(ep, REG_RXDENQ, rx);
		wrw(ep, REG_RXSTSENQ, rx);
	पूर्ण

	वापस rx;
पूर्ण

अटल netdev_tx_t ep93xx_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	काष्ठा ep93xx_tdesc *txd;
	पूर्णांक entry;

	अगर (unlikely(skb->len > MAX_PKT_SIZE)) अणु
		dev->stats.tx_dropped++;
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	entry = ep->tx_poपूर्णांकer;
	ep->tx_poपूर्णांकer = (ep->tx_poपूर्णांकer + 1) & (TX_QUEUE_ENTRIES - 1);

	txd = &ep->descs->tdesc[entry];

	txd->tdesc1 = TDESC1_खातापूर्ण | (entry << 16) | (skb->len & 0xfff);
	dma_sync_single_क्रम_cpu(dev->dev.parent, txd->buf_addr, skb->len,
				DMA_TO_DEVICE);
	skb_copy_and_csum_dev(skb, ep->tx_buf[entry]);
	dma_sync_single_क्रम_device(dev->dev.parent, txd->buf_addr, skb->len,
				   DMA_TO_DEVICE);
	dev_kमुक्त_skb(skb);

	spin_lock_irq(&ep->tx_pending_lock);
	ep->tx_pending++;
	अगर (ep->tx_pending == TX_QUEUE_ENTRIES)
		netअगर_stop_queue(dev);
	spin_unlock_irq(&ep->tx_pending_lock);

	wrl(ep, REG_TXDENQ, 1);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ep93xx_tx_complete(काष्ठा net_device *dev)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	पूर्णांक wake;

	wake = 0;

	spin_lock(&ep->tx_pending_lock);
	जबतक (1) अणु
		पूर्णांक entry;
		काष्ठा ep93xx_tstat *tstat;
		u32 tstat0;

		entry = ep->tx_clean_poपूर्णांकer;
		tstat = ep->descs->tstat + entry;

		tstat0 = tstat->tstat0;
		अगर (!(tstat0 & TSTAT0_TXFP))
			अवरोध;

		tstat->tstat0 = 0;

		अगर (tstat0 & TSTAT0_FA)
			pr_crit("frame aborted %.8x\n", tstat0);
		अगर ((tstat0 & TSTAT0_BUFFER_INDEX) != entry)
			pr_crit("entry mismatch %.8x\n", tstat0);

		अगर (tstat0 & TSTAT0_TXWE) अणु
			पूर्णांक length = ep->descs->tdesc[entry].tdesc1 & 0xfff;

			dev->stats.tx_packets++;
			dev->stats.tx_bytes += length;
		पूर्ण अन्यथा अणु
			dev->stats.tx_errors++;
		पूर्ण

		अगर (tstat0 & TSTAT0_OW)
			dev->stats.tx_winकरोw_errors++;
		अगर (tstat0 & TSTAT0_TXU)
			dev->stats.tx_fअगरo_errors++;
		dev->stats.collisions += (tstat0 >> 16) & 0x1f;

		ep->tx_clean_poपूर्णांकer = (entry + 1) & (TX_QUEUE_ENTRIES - 1);
		अगर (ep->tx_pending == TX_QUEUE_ENTRIES)
			wake = 1;
		ep->tx_pending--;
	पूर्ण
	spin_unlock(&ep->tx_pending_lock);

	अगर (wake)
		netअगर_wake_queue(dev);
पूर्ण

अटल irqवापस_t ep93xx_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	u32 status;

	status = rdl(ep, REG_INTSTSC);
	अगर (status == 0)
		वापस IRQ_NONE;

	अगर (status & REG_INTSTS_RX) अणु
		spin_lock(&ep->rx_lock);
		अगर (likely(napi_schedule_prep(&ep->napi))) अणु
			wrl(ep, REG_INTEN, REG_INTEN_TX);
			__napi_schedule(&ep->napi);
		पूर्ण
		spin_unlock(&ep->rx_lock);
	पूर्ण

	अगर (status & REG_INTSTS_TX)
		ep93xx_tx_complete(dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ep93xx_मुक्त_buffers(काष्ठा ep93xx_priv *ep)
अणु
	काष्ठा device *dev = ep->dev->dev.parent;
	पूर्णांक i;

	अगर (!ep->descs)
		वापस;

	क्रम (i = 0; i < RX_QUEUE_ENTRIES; i++) अणु
		dma_addr_t d;

		d = ep->descs->rdesc[i].buf_addr;
		अगर (d)
			dma_unmap_single(dev, d, PKT_BUF_SIZE, DMA_FROM_DEVICE);

		kमुक्त(ep->rx_buf[i]);
	पूर्ण

	क्रम (i = 0; i < TX_QUEUE_ENTRIES; i++) अणु
		dma_addr_t d;

		d = ep->descs->tdesc[i].buf_addr;
		अगर (d)
			dma_unmap_single(dev, d, PKT_BUF_SIZE, DMA_TO_DEVICE);

		kमुक्त(ep->tx_buf[i]);
	पूर्ण

	dma_मुक्त_coherent(dev, माप(काष्ठा ep93xx_descs), ep->descs,
							ep->descs_dma_addr);
	ep->descs = शून्य;
पूर्ण

अटल पूर्णांक ep93xx_alloc_buffers(काष्ठा ep93xx_priv *ep)
अणु
	काष्ठा device *dev = ep->dev->dev.parent;
	पूर्णांक i;

	ep->descs = dma_alloc_coherent(dev, माप(काष्ठा ep93xx_descs),
				&ep->descs_dma_addr, GFP_KERNEL);
	अगर (ep->descs == शून्य)
		वापस 1;

	क्रम (i = 0; i < RX_QUEUE_ENTRIES; i++) अणु
		व्योम *buf;
		dma_addr_t d;

		buf = kदो_स्मृति(PKT_BUF_SIZE, GFP_KERNEL);
		अगर (buf == शून्य)
			जाओ err;

		d = dma_map_single(dev, buf, PKT_BUF_SIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dev, d)) अणु
			kमुक्त(buf);
			जाओ err;
		पूर्ण

		ep->rx_buf[i] = buf;
		ep->descs->rdesc[i].buf_addr = d;
		ep->descs->rdesc[i].rdesc1 = (i << 16) | PKT_BUF_SIZE;
	पूर्ण

	क्रम (i = 0; i < TX_QUEUE_ENTRIES; i++) अणु
		व्योम *buf;
		dma_addr_t d;

		buf = kदो_स्मृति(PKT_BUF_SIZE, GFP_KERNEL);
		अगर (buf == शून्य)
			जाओ err;

		d = dma_map_single(dev, buf, PKT_BUF_SIZE, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, d)) अणु
			kमुक्त(buf);
			जाओ err;
		पूर्ण

		ep->tx_buf[i] = buf;
		ep->descs->tdesc[i].buf_addr = d;
	पूर्ण

	वापस 0;

err:
	ep93xx_मुक्त_buffers(ep);
	वापस 1;
पूर्ण

अटल पूर्णांक ep93xx_start_hw(काष्ठा net_device *dev)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	अचिन्हित दीर्घ addr;
	पूर्णांक i;

	wrl(ep, REG_SELFCTL, REG_SELFCTL_RESET);
	क्रम (i = 0; i < 10; i++) अणु
		अगर ((rdl(ep, REG_SELFCTL) & REG_SELFCTL_RESET) == 0)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i == 10) अणु
		pr_crit("hw failed to reset\n");
		वापस 1;
	पूर्ण

	wrl(ep, REG_SELFCTL, ((ep->mdc_भागisor - 1) << 9));

	/* Does the PHY support preamble suppress?  */
	अगर ((ep93xx_mdio_पढ़ो(dev, ep->mii.phy_id, MII_BMSR) & 0x0040) != 0)
		wrl(ep, REG_SELFCTL, ((ep->mdc_भागisor - 1) << 9) | (1 << 8));

	/* Receive descriptor ring.  */
	addr = ep->descs_dma_addr + दुरत्व(काष्ठा ep93xx_descs, rdesc);
	wrl(ep, REG_RXDQBADD, addr);
	wrl(ep, REG_RXDCURADD, addr);
	wrw(ep, REG_RXDQBLEN, RX_QUEUE_ENTRIES * माप(काष्ठा ep93xx_rdesc));

	/* Receive status ring.  */
	addr = ep->descs_dma_addr + दुरत्व(काष्ठा ep93xx_descs, rstat);
	wrl(ep, REG_RXSTSQBADD, addr);
	wrl(ep, REG_RXSTSQCURADD, addr);
	wrw(ep, REG_RXSTSQBLEN, RX_QUEUE_ENTRIES * माप(काष्ठा ep93xx_rstat));

	/* Transmit descriptor ring.  */
	addr = ep->descs_dma_addr + दुरत्व(काष्ठा ep93xx_descs, tdesc);
	wrl(ep, REG_TXDQBADD, addr);
	wrl(ep, REG_TXDQCURADD, addr);
	wrw(ep, REG_TXDQBLEN, TX_QUEUE_ENTRIES * माप(काष्ठा ep93xx_tdesc));

	/* Transmit status ring.  */
	addr = ep->descs_dma_addr + दुरत्व(काष्ठा ep93xx_descs, tstat);
	wrl(ep, REG_TXSTSQBADD, addr);
	wrl(ep, REG_TXSTSQCURADD, addr);
	wrw(ep, REG_TXSTSQBLEN, TX_QUEUE_ENTRIES * माप(काष्ठा ep93xx_tstat));

	wrl(ep, REG_BMCTL, REG_BMCTL_ENABLE_TX | REG_BMCTL_ENABLE_RX);
	wrl(ep, REG_INTEN, REG_INTEN_TX | REG_INTEN_RX);
	wrl(ep, REG_GIINTMSK, 0);

	क्रम (i = 0; i < 10; i++) अणु
		अगर ((rdl(ep, REG_BMSTS) & REG_BMSTS_RX_ACTIVE) != 0)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i == 10) अणु
		pr_crit("hw failed to start\n");
		वापस 1;
	पूर्ण

	wrl(ep, REG_RXDENQ, RX_QUEUE_ENTRIES);
	wrl(ep, REG_RXSTSENQ, RX_QUEUE_ENTRIES);

	wrb(ep, REG_INDAD0, dev->dev_addr[0]);
	wrb(ep, REG_INDAD1, dev->dev_addr[1]);
	wrb(ep, REG_INDAD2, dev->dev_addr[2]);
	wrb(ep, REG_INDAD3, dev->dev_addr[3]);
	wrb(ep, REG_INDAD4, dev->dev_addr[4]);
	wrb(ep, REG_INDAD5, dev->dev_addr[5]);
	wrl(ep, REG_AFP, 0);

	wrl(ep, REG_MAXFRMLEN, (MAX_PKT_SIZE << 16) | MAX_PKT_SIZE);

	wrl(ep, REG_RXCTL, REG_RXCTL_DEFAULT);
	wrl(ep, REG_TXCTL, REG_TXCTL_ENABLE);

	वापस 0;
पूर्ण

अटल व्योम ep93xx_stop_hw(काष्ठा net_device *dev)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	पूर्णांक i;

	wrl(ep, REG_SELFCTL, REG_SELFCTL_RESET);
	क्रम (i = 0; i < 10; i++) अणु
		अगर ((rdl(ep, REG_SELFCTL) & REG_SELFCTL_RESET) == 0)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i == 10)
		pr_crit("hw failed to reset\n");
पूर्ण

अटल पूर्णांक ep93xx_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	पूर्णांक err;

	अगर (ep93xx_alloc_buffers(ep))
		वापस -ENOMEM;

	napi_enable(&ep->napi);

	अगर (ep93xx_start_hw(dev)) अणु
		napi_disable(&ep->napi);
		ep93xx_मुक्त_buffers(ep);
		वापस -EIO;
	पूर्ण

	spin_lock_init(&ep->rx_lock);
	ep->rx_poपूर्णांकer = 0;
	ep->tx_clean_poपूर्णांकer = 0;
	ep->tx_poपूर्णांकer = 0;
	spin_lock_init(&ep->tx_pending_lock);
	ep->tx_pending = 0;

	err = request_irq(ep->irq, ep93xx_irq, IRQF_SHARED, dev->name, dev);
	अगर (err) अणु
		napi_disable(&ep->napi);
		ep93xx_stop_hw(dev);
		ep93xx_मुक्त_buffers(ep);
		वापस err;
	पूर्ण

	wrl(ep, REG_GIINTMSK, REG_GIINTMSK_ENABLE);

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);

	napi_disable(&ep->napi);
	netअगर_stop_queue(dev);

	wrl(ep, REG_GIINTMSK, 0);
	मुक्त_irq(ep->irq, dev);
	ep93xx_stop_hw(dev);
	ep93xx_मुक्त_buffers(ep);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);

	वापस generic_mii_ioctl(&ep->mii, data, cmd, शून्य);
पूर्ण

अटल व्योम ep93xx_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
पूर्ण

अटल पूर्णांक ep93xx_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);

	mii_ethtool_get_link_ksettings(&ep->mii, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	वापस mii_ethtool_set_link_ksettings(&ep->mii, cmd);
पूर्ण

अटल पूर्णांक ep93xx_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	वापस mii_nway_restart(&ep->mii);
पूर्ण

अटल u32 ep93xx_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा ep93xx_priv *ep = netdev_priv(dev);
	वापस mii_link_ok(&ep->mii);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ep93xx_ethtool_ops = अणु
	.get_drvinfo		= ep93xx_get_drvinfo,
	.nway_reset		= ep93xx_nway_reset,
	.get_link		= ep93xx_get_link,
	.get_link_ksettings	= ep93xx_get_link_ksettings,
	.set_link_ksettings	= ep93xx_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ep93xx_netdev_ops = अणु
	.nकरो_खोलो		= ep93xx_खोलो,
	.nकरो_stop		= ep93xx_बंद,
	.nकरो_start_xmit		= ep93xx_xmit,
	.nकरो_करो_ioctl		= ep93xx_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल काष्ठा net_device *ep93xx_dev_alloc(काष्ठा ep93xx_eth_data *data)
अणु
	काष्ठा net_device *dev;

	dev = alloc_etherdev(माप(काष्ठा ep93xx_priv));
	अगर (dev == शून्य)
		वापस शून्य;

	स_नकल(dev->dev_addr, data->dev_addr, ETH_ALEN);

	dev->ethtool_ops = &ep93xx_ethtool_ops;
	dev->netdev_ops = &ep93xx_netdev_ops;

	dev->features |= NETIF_F_SG | NETIF_F_HW_CSUM;

	वापस dev;
पूर्ण


अटल पूर्णांक ep93xx_eth_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा ep93xx_priv *ep;
	काष्ठा resource *mem;

	dev = platक्रमm_get_drvdata(pdev);
	अगर (dev == शून्य)
		वापस 0;

	ep = netdev_priv(dev);

	/* @@@ Force करोwn.  */
	unरेजिस्टर_netdev(dev);
	ep93xx_मुक्त_buffers(ep);

	अगर (ep->base_addr != शून्य)
		iounmap(ep->base_addr);

	अगर (ep->res != शून्य) अणु
		mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		release_mem_region(mem->start, resource_size(mem));
	पूर्ण

	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_eth_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_eth_data *data;
	काष्ठा net_device *dev;
	काष्ठा ep93xx_priv *ep;
	काष्ठा resource *mem;
	पूर्णांक irq;
	पूर्णांक err;

	अगर (pdev == शून्य)
		वापस -ENODEV;
	data = dev_get_platdata(&pdev->dev);

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!mem || irq < 0)
		वापस -ENXIO;

	dev = ep93xx_dev_alloc(data);
	अगर (dev == शून्य) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	ep = netdev_priv(dev);
	ep->dev = dev;
	SET_NETDEV_DEV(dev, &pdev->dev);
	netअगर_napi_add(dev, &ep->napi, ep93xx_poll, 64);

	platक्रमm_set_drvdata(pdev, dev);

	ep->res = request_mem_region(mem->start, resource_size(mem),
				     dev_name(&pdev->dev));
	अगर (ep->res == शून्य) अणु
		dev_err(&pdev->dev, "Could not reserve memory region\n");
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	ep->base_addr = ioremap(mem->start, resource_size(mem));
	अगर (ep->base_addr == शून्य) अणु
		dev_err(&pdev->dev, "Failed to ioremap ethernet registers\n");
		err = -EIO;
		जाओ err_out;
	पूर्ण
	ep->irq = irq;

	ep->mii.phy_id = data->phy_id;
	ep->mii.phy_id_mask = 0x1f;
	ep->mii.reg_num_mask = 0x1f;
	ep->mii.dev = dev;
	ep->mii.mdio_पढ़ो = ep93xx_mdio_पढ़ो;
	ep->mii.mdio_ग_लिखो = ep93xx_mdio_ग_लिखो;
	ep->mdc_भागisor = 40;	/* Max HCLK 100 MHz, min MDIO clk 2.5 MHz.  */

	अगर (is_zero_ether_addr(dev->dev_addr))
		eth_hw_addr_अक्रमom(dev);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register netdev\n");
		जाओ err_out;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: ep93xx on-chip ethernet, IRQ %d, %pM\n",
			dev->name, ep->irq, dev->dev_addr);

	वापस 0;

err_out:
	ep93xx_eth_हटाओ(pdev);
	वापस err;
पूर्ण


अटल काष्ठा platक्रमm_driver ep93xx_eth_driver = अणु
	.probe		= ep93xx_eth_probe,
	.हटाओ		= ep93xx_eth_हटाओ,
	.driver		= अणु
		.name	= "ep93xx-eth",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ep93xx_eth_driver);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ep93xx-eth");
