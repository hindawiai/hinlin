<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
 /*
 * drivers/net/ethernet/ec_bhf.c
 *
 * Copyright (C) 2014 Darek Marcinkiewicz <reksio@newterm.pl>
 */

/* This is a driver क्रम EtherCAT master module present on CCAT FPGA.
 * Those can be found on Bechhoff CX50xx industrial PCs.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/स्थिति.स>

#घोषणा TIMER_INTERVAL_NSEC	20000

#घोषणा INFO_BLOCK_SIZE		0x10
#घोषणा INFO_BLOCK_TYPE		0x0
#घोषणा INFO_BLOCK_REV		0x2
#घोषणा INFO_BLOCK_BLK_CNT	0x4
#घोषणा INFO_BLOCK_TX_CHAN	0x4
#घोषणा INFO_BLOCK_RX_CHAN	0x5
#घोषणा INFO_BLOCK_OFFSET	0x8

#घोषणा EC_MII_OFFSET		0x4
#घोषणा EC_FIFO_OFFSET		0x8
#घोषणा EC_MAC_OFFSET		0xc

#घोषणा MAC_FRAME_ERR_CNT	0x0
#घोषणा MAC_RX_ERR_CNT		0x1
#घोषणा MAC_CRC_ERR_CNT		0x2
#घोषणा MAC_LNK_LST_ERR_CNT	0x3
#घोषणा MAC_TX_FRAME_CNT	0x10
#घोषणा MAC_RX_FRAME_CNT	0x14
#घोषणा MAC_TX_FIFO_LVL		0x20
#घोषणा MAC_DROPPED_FRMS	0x28
#घोषणा MAC_CONNECTED_CCAT_FLAG	0x78

#घोषणा MII_MAC_ADDR		0x8
#घोषणा MII_MAC_FILT_FLAG	0xe
#घोषणा MII_LINK_STATUS		0xf

#घोषणा FIFO_TX_REG		0x0
#घोषणा FIFO_TX_RESET		0x8
#घोषणा FIFO_RX_REG		0x10
#घोषणा FIFO_RX_ADDR_VALID	(1u << 31)
#घोषणा FIFO_RX_RESET		0x18

#घोषणा DMA_CHAN_OFFSET		0x1000
#घोषणा DMA_CHAN_SIZE		0x8

#घोषणा DMA_WINDOW_SIZE_MASK	0xfffffffc

#घोषणा ETHERCAT_MASTER_ID	0x14

अटल स्थिर काष्ठा pci_device_id ids[] = अणु
	अणु PCI_DEVICE(0x15ec, 0x5000), पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ids);

काष्ठा rx_header अणु
#घोषणा RXHDR_NEXT_ADDR_MASK	0xffffffu
#घोषणा RXHDR_NEXT_VALID	(1u << 31)
	__le32 next;
#घोषणा RXHDR_NEXT_RECV_FLAG	0x1
	__le32 recv;
#घोषणा RXHDR_LEN_MASK		0xfffu
	__le16 len;
	__le16 port;
	__le32 reserved;
	u8 बारtamp[8];
पूर्ण __packed;

#घोषणा PKT_PAYLOAD_SIZE	0x7e8
काष्ठा rx_desc अणु
	काष्ठा rx_header header;
	u8 data[PKT_PAYLOAD_SIZE];
पूर्ण __packed;

काष्ठा tx_header अणु
	__le16 len;
#घोषणा TX_HDR_PORT_0		0x1
#घोषणा TX_HDR_PORT_1		0x2
	u8 port;
	u8 ts_enable;
#घोषणा TX_HDR_SENT		0x1
	__le32 sent;
	u8 बारtamp[8];
पूर्ण __packed;

काष्ठा tx_desc अणु
	काष्ठा tx_header header;
	u8 data[PKT_PAYLOAD_SIZE];
पूर्ण __packed;

#घोषणा FIFO_SIZE		64

अटल दीर्घ polling_frequency = TIMER_INTERVAL_NSEC;

काष्ठा bhf_dma अणु
	u8 *buf;
	माप_प्रकार len;
	dma_addr_t buf_phys;

	u8 *alloc;
	माप_प्रकार alloc_len;
	dma_addr_t alloc_phys;
पूर्ण;

काष्ठा ec_bhf_priv अणु
	काष्ठा net_device *net_dev;
	काष्ठा pci_dev *dev;

	व्योम __iomem *io;
	व्योम __iomem *dma_io;

	काष्ठा hrसमयr hrसमयr;

	पूर्णांक tx_dma_chan;
	पूर्णांक rx_dma_chan;
	व्योम __iomem *ec_io;
	व्योम __iomem *fअगरo_io;
	व्योम __iomem *mii_io;
	व्योम __iomem *mac_io;

	काष्ठा bhf_dma rx_buf;
	काष्ठा rx_desc *rx_descs;
	पूर्णांक rx_dnext;
	पूर्णांक rx_dcount;

	काष्ठा bhf_dma tx_buf;
	काष्ठा tx_desc *tx_descs;
	पूर्णांक tx_dcount;
	पूर्णांक tx_dnext;

	u64 stat_rx_bytes;
	u64 stat_tx_bytes;
पूर्ण;

#घोषणा PRIV_TO_DEV(priv) (&(priv)->dev->dev)

अटल व्योम ec_bhf_reset(काष्ठा ec_bhf_priv *priv)
अणु
	ioग_लिखो8(0, priv->mac_io + MAC_FRAME_ERR_CNT);
	ioग_लिखो8(0, priv->mac_io + MAC_RX_ERR_CNT);
	ioग_लिखो8(0, priv->mac_io + MAC_CRC_ERR_CNT);
	ioग_लिखो8(0, priv->mac_io + MAC_LNK_LST_ERR_CNT);
	ioग_लिखो32(0, priv->mac_io + MAC_TX_FRAME_CNT);
	ioग_लिखो32(0, priv->mac_io + MAC_RX_FRAME_CNT);
	ioग_लिखो8(0, priv->mac_io + MAC_DROPPED_FRMS);

	ioग_लिखो8(0, priv->fअगरo_io + FIFO_TX_RESET);
	ioग_लिखो8(0, priv->fअगरo_io + FIFO_RX_RESET);

	ioग_लिखो8(0, priv->mac_io + MAC_TX_FIFO_LVL);
पूर्ण

अटल व्योम ec_bhf_send_packet(काष्ठा ec_bhf_priv *priv, काष्ठा tx_desc *desc)
अणु
	u32 len = le16_to_cpu(desc->header.len) + माप(desc->header);
	u32 addr = (u8 *)desc - priv->tx_buf.buf;

	ioग_लिखो32((ALIGN(len, 8) << 24) | addr, priv->fअगरo_io + FIFO_TX_REG);
पूर्ण

अटल पूर्णांक ec_bhf_desc_sent(काष्ठा tx_desc *desc)
अणु
	वापस le32_to_cpu(desc->header.sent) & TX_HDR_SENT;
पूर्ण

अटल व्योम ec_bhf_process_tx(काष्ठा ec_bhf_priv *priv)
अणु
	अगर (unlikely(netअगर_queue_stopped(priv->net_dev))) अणु
		/* Make sure that we perceive changes to tx_dnext. */
		smp_rmb();

		अगर (ec_bhf_desc_sent(&priv->tx_descs[priv->tx_dnext]))
			netअगर_wake_queue(priv->net_dev);
	पूर्ण
पूर्ण

अटल पूर्णांक ec_bhf_pkt_received(काष्ठा rx_desc *desc)
अणु
	वापस le32_to_cpu(desc->header.recv) & RXHDR_NEXT_RECV_FLAG;
पूर्ण

अटल व्योम ec_bhf_add_rx_desc(काष्ठा ec_bhf_priv *priv, काष्ठा rx_desc *desc)
अणु
	ioग_लिखो32(FIFO_RX_ADDR_VALID | ((u8 *)(desc) - priv->rx_buf.buf),
		  priv->fअगरo_io + FIFO_RX_REG);
पूर्ण

अटल व्योम ec_bhf_process_rx(काष्ठा ec_bhf_priv *priv)
अणु
	काष्ठा rx_desc *desc = &priv->rx_descs[priv->rx_dnext];

	जबतक (ec_bhf_pkt_received(desc)) अणु
		पूर्णांक pkt_size = (le16_to_cpu(desc->header.len) &
			       RXHDR_LEN_MASK) - माप(काष्ठा rx_header) - 4;
		u8 *data = desc->data;
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb_ip_align(priv->net_dev, pkt_size);
		अगर (skb) अणु
			skb_put_data(skb, data, pkt_size);
			skb->protocol = eth_type_trans(skb, priv->net_dev);
			priv->stat_rx_bytes += pkt_size;

			netअगर_rx(skb);
		पूर्ण अन्यथा अणु
			dev_err_ratelimited(PRIV_TO_DEV(priv),
					    "Couldn't allocate a skb_buff for a packet of size %u\n",
					    pkt_size);
		पूर्ण

		desc->header.recv = 0;

		ec_bhf_add_rx_desc(priv, desc);

		priv->rx_dnext = (priv->rx_dnext + 1) % priv->rx_dcount;
		desc = &priv->rx_descs[priv->rx_dnext];
	पूर्ण
पूर्ण

अटल क्रमागत hrसमयr_restart ec_bhf_समयr_fun(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा ec_bhf_priv *priv = container_of(समयr, काष्ठा ec_bhf_priv,
						hrसमयr);
	ec_bhf_process_rx(priv);
	ec_bhf_process_tx(priv);

	अगर (!netअगर_running(priv->net_dev))
		वापस HRTIMER_NORESTART;

	hrसमयr_क्रमward_now(समयr, polling_frequency);
	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक ec_bhf_setup_offsets(काष्ठा ec_bhf_priv *priv)
अणु
	काष्ठा device *dev = PRIV_TO_DEV(priv);
	अचिन्हित block_count, i;
	व्योम __iomem *ec_info;

	block_count = ioपढ़ो8(priv->io + INFO_BLOCK_BLK_CNT);
	क्रम (i = 0; i < block_count; i++) अणु
		u16 type = ioपढ़ो16(priv->io + i * INFO_BLOCK_SIZE +
				    INFO_BLOCK_TYPE);
		अगर (type == ETHERCAT_MASTER_ID)
			अवरोध;
	पूर्ण
	अगर (i == block_count) अणु
		dev_err(dev, "EtherCAT master with DMA block not found\n");
		वापस -ENODEV;
	पूर्ण

	ec_info = priv->io + i * INFO_BLOCK_SIZE;

	priv->tx_dma_chan = ioपढ़ो8(ec_info + INFO_BLOCK_TX_CHAN);
	priv->rx_dma_chan = ioपढ़ो8(ec_info + INFO_BLOCK_RX_CHAN);

	priv->ec_io = priv->io + ioपढ़ो32(ec_info + INFO_BLOCK_OFFSET);
	priv->mii_io = priv->ec_io + ioपढ़ो32(priv->ec_io + EC_MII_OFFSET);
	priv->fअगरo_io = priv->ec_io + ioपढ़ो32(priv->ec_io + EC_FIFO_OFFSET);
	priv->mac_io = priv->ec_io + ioपढ़ो32(priv->ec_io + EC_MAC_OFFSET);

	वापस 0;
पूर्ण

अटल netdev_tx_t ec_bhf_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *net_dev)
अणु
	काष्ठा ec_bhf_priv *priv = netdev_priv(net_dev);
	काष्ठा tx_desc *desc;
	अचिन्हित len;

	desc = &priv->tx_descs[priv->tx_dnext];

	skb_copy_and_csum_dev(skb, desc->data);
	len = skb->len;

	स_रखो(&desc->header, 0, माप(desc->header));
	desc->header.len = cpu_to_le16(len);
	desc->header.port = TX_HDR_PORT_0;

	ec_bhf_send_packet(priv, desc);

	priv->tx_dnext = (priv->tx_dnext + 1) % priv->tx_dcount;

	अगर (!ec_bhf_desc_sent(&priv->tx_descs[priv->tx_dnext])) अणु
		/* Make sure that updates to tx_dnext are perceived
		 * by समयr routine.
		 */
		smp_wmb();

		netअगर_stop_queue(net_dev);
	पूर्ण

	priv->stat_tx_bytes += len;

	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ec_bhf_alloc_dma_mem(काष्ठा ec_bhf_priv *priv,
				काष्ठा bhf_dma *buf,
				पूर्णांक channel,
				पूर्णांक size)
अणु
	पूर्णांक offset = channel * DMA_CHAN_SIZE + DMA_CHAN_OFFSET;
	काष्ठा device *dev = PRIV_TO_DEV(priv);
	u32 mask;

	ioग_लिखो32(0xffffffff, priv->dma_io + offset);

	mask = ioपढ़ो32(priv->dma_io + offset);
	mask &= DMA_WINDOW_SIZE_MASK;

	/* We want to allocate a chunk of memory that is:
	 * - aligned to the mask we just पढ़ो
	 * - is of size 2^mask bytes (at most)
	 * In order to ensure that we will allocate buffer of
	 * 2 * 2^mask bytes.
	 */
	buf->len = min_t(पूर्णांक, ~mask + 1, size);
	buf->alloc_len = 2 * buf->len;

	buf->alloc = dma_alloc_coherent(dev, buf->alloc_len, &buf->alloc_phys,
					GFP_KERNEL);
	अगर (buf->alloc == शून्य) अणु
		dev_err(dev, "Failed to allocate buffer\n");
		वापस -ENOMEM;
	पूर्ण

	buf->buf_phys = (buf->alloc_phys + buf->len) & mask;
	buf->buf = buf->alloc + (buf->buf_phys - buf->alloc_phys);

	ioग_लिखो32(0, priv->dma_io + offset + 4);
	ioग_लिखो32(buf->buf_phys, priv->dma_io + offset);

	वापस 0;
पूर्ण

अटल व्योम ec_bhf_setup_tx_descs(काष्ठा ec_bhf_priv *priv)
अणु
	पूर्णांक i = 0;

	priv->tx_dcount = priv->tx_buf.len / माप(काष्ठा tx_desc);
	priv->tx_descs = (काष्ठा tx_desc *)priv->tx_buf.buf;
	priv->tx_dnext = 0;

	क्रम (i = 0; i < priv->tx_dcount; i++)
		priv->tx_descs[i].header.sent = cpu_to_le32(TX_HDR_SENT);
पूर्ण

अटल व्योम ec_bhf_setup_rx_descs(काष्ठा ec_bhf_priv *priv)
अणु
	पूर्णांक i;

	priv->rx_dcount = priv->rx_buf.len / माप(काष्ठा rx_desc);
	priv->rx_descs = (काष्ठा rx_desc *)priv->rx_buf.buf;
	priv->rx_dnext = 0;

	क्रम (i = 0; i < priv->rx_dcount; i++) अणु
		काष्ठा rx_desc *desc = &priv->rx_descs[i];
		u32 next;

		अगर (i != priv->rx_dcount - 1)
			next = (u8 *)(desc + 1) - priv->rx_buf.buf;
		अन्यथा
			next = 0;
		next |= RXHDR_NEXT_VALID;
		desc->header.next = cpu_to_le32(next);
		desc->header.recv = 0;
		ec_bhf_add_rx_desc(priv, desc);
	पूर्ण
पूर्ण

अटल पूर्णांक ec_bhf_खोलो(काष्ठा net_device *net_dev)
अणु
	काष्ठा ec_bhf_priv *priv = netdev_priv(net_dev);
	काष्ठा device *dev = PRIV_TO_DEV(priv);
	पूर्णांक err = 0;

	ec_bhf_reset(priv);

	err = ec_bhf_alloc_dma_mem(priv, &priv->rx_buf, priv->rx_dma_chan,
				   FIFO_SIZE * माप(काष्ठा rx_desc));
	अगर (err) अणु
		dev_err(dev, "Failed to allocate rx buffer\n");
		जाओ out;
	पूर्ण
	ec_bhf_setup_rx_descs(priv);

	err = ec_bhf_alloc_dma_mem(priv, &priv->tx_buf, priv->tx_dma_chan,
				   FIFO_SIZE * माप(काष्ठा tx_desc));
	अगर (err) अणु
		dev_err(dev, "Failed to allocate tx buffer\n");
		जाओ error_rx_मुक्त;
	पूर्ण
	ioग_लिखो8(0, priv->mii_io + MII_MAC_FILT_FLAG);
	ec_bhf_setup_tx_descs(priv);

	netअगर_start_queue(net_dev);

	hrसमयr_init(&priv->hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	priv->hrसमयr.function = ec_bhf_समयr_fun;
	hrसमयr_start(&priv->hrसमयr, polling_frequency, HRTIMER_MODE_REL);

	वापस 0;

error_rx_मुक्त:
	dma_मुक्त_coherent(dev, priv->rx_buf.alloc_len, priv->rx_buf.alloc,
			  priv->rx_buf.alloc_len);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ec_bhf_stop(काष्ठा net_device *net_dev)
अणु
	काष्ठा ec_bhf_priv *priv = netdev_priv(net_dev);
	काष्ठा device *dev = PRIV_TO_DEV(priv);

	hrसमयr_cancel(&priv->hrसमयr);

	ec_bhf_reset(priv);

	netअगर_tx_disable(net_dev);

	dma_मुक्त_coherent(dev, priv->tx_buf.alloc_len,
			  priv->tx_buf.alloc, priv->tx_buf.alloc_phys);
	dma_मुक्त_coherent(dev, priv->rx_buf.alloc_len,
			  priv->rx_buf.alloc, priv->rx_buf.alloc_phys);

	वापस 0;
पूर्ण

अटल व्योम
ec_bhf_get_stats(काष्ठा net_device *net_dev,
		 काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ec_bhf_priv *priv = netdev_priv(net_dev);

	stats->rx_errors = ioपढ़ो8(priv->mac_io + MAC_RX_ERR_CNT) +
				ioपढ़ो8(priv->mac_io + MAC_CRC_ERR_CNT) +
				ioपढ़ो8(priv->mac_io + MAC_FRAME_ERR_CNT);
	stats->rx_packets = ioपढ़ो32(priv->mac_io + MAC_RX_FRAME_CNT);
	stats->tx_packets = ioपढ़ो32(priv->mac_io + MAC_TX_FRAME_CNT);
	stats->rx_dropped = ioपढ़ो8(priv->mac_io + MAC_DROPPED_FRMS);

	stats->tx_bytes = priv->stat_tx_bytes;
	stats->rx_bytes = priv->stat_rx_bytes;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ec_bhf_netdev_ops = अणु
	.nकरो_start_xmit		= ec_bhf_start_xmit,
	.nकरो_खोलो		= ec_bhf_खोलो,
	.nकरो_stop		= ec_bhf_stop,
	.nकरो_get_stats64	= ec_bhf_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr
पूर्ण;

अटल पूर्णांक ec_bhf_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा net_device *net_dev;
	काष्ठा ec_bhf_priv *priv;
	व्योम __iomem *dma_io;
	व्योम __iomem *io;
	पूर्णांक err = 0;

	err = pci_enable_device(dev);
	अगर (err)
		वापस err;

	pci_set_master(dev);

	err = pci_set_dma_mask(dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&dev->dev,
			"Required dma mask not supported, failed to initialize device\n");
		err = -EIO;
		जाओ err_disable_dev;
	पूर्ण

	err = pci_set_consistent_dma_mask(dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&dev->dev,
			"Required dma mask not supported, failed to initialize device\n");
		जाओ err_disable_dev;
	पूर्ण

	err = pci_request_regions(dev, "ec_bhf");
	अगर (err) अणु
		dev_err(&dev->dev, "Failed to request pci memory regions\n");
		जाओ err_disable_dev;
	पूर्ण

	io = pci_iomap(dev, 0, 0);
	अगर (!io) अणु
		dev_err(&dev->dev, "Failed to map pci card memory bar 0");
		err = -EIO;
		जाओ err_release_regions;
	पूर्ण

	dma_io = pci_iomap(dev, 2, 0);
	अगर (!dma_io) अणु
		dev_err(&dev->dev, "Failed to map pci card memory bar 2");
		err = -EIO;
		जाओ err_unmap;
	पूर्ण

	net_dev = alloc_etherdev(माप(काष्ठा ec_bhf_priv));
	अगर (net_dev == शून्य) अणु
		err = -ENOMEM;
		जाओ err_unmap_dma_io;
	पूर्ण

	pci_set_drvdata(dev, net_dev);
	SET_NETDEV_DEV(net_dev, &dev->dev);

	net_dev->features = 0;
	net_dev->flags |= IFF_NOARP;

	net_dev->netdev_ops = &ec_bhf_netdev_ops;

	priv = netdev_priv(net_dev);
	priv->net_dev = net_dev;
	priv->io = io;
	priv->dma_io = dma_io;
	priv->dev = dev;

	err = ec_bhf_setup_offsets(priv);
	अगर (err < 0)
		जाओ err_मुक्त_net_dev;

	स_नकल_fromio(net_dev->dev_addr, priv->mii_io + MII_MAC_ADDR, 6);

	err = रेजिस्टर_netdev(net_dev);
	अगर (err < 0)
		जाओ err_मुक्त_net_dev;

	वापस 0;

err_मुक्त_net_dev:
	मुक्त_netdev(net_dev);
err_unmap_dma_io:
	pci_iounmap(dev, dma_io);
err_unmap:
	pci_iounmap(dev, io);
err_release_regions:
	pci_release_regions(dev);
err_disable_dev:
	pci_clear_master(dev);
	pci_disable_device(dev);

	वापस err;
पूर्ण

अटल व्योम ec_bhf_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा net_device *net_dev = pci_get_drvdata(dev);
	काष्ठा ec_bhf_priv *priv = netdev_priv(net_dev);

	unरेजिस्टर_netdev(net_dev);

	pci_iounmap(dev, priv->dma_io);
	pci_iounmap(dev, priv->io);

	मुक्त_netdev(net_dev);

	pci_release_regions(dev);
	pci_clear_master(dev);
	pci_disable_device(dev);
पूर्ण

अटल काष्ठा pci_driver pci_driver = अणु
	.name		= "ec_bhf",
	.id_table	= ids,
	.probe		= ec_bhf_probe,
	.हटाओ		= ec_bhf_हटाओ,
पूर्ण;
module_pci_driver(pci_driver);

module_param(polling_frequency, दीर्घ, 0444);
MODULE_PARM_DESC(polling_frequency, "Polling timer frequency in ns");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dariusz Marcinkiewicz <reksio@newterm.pl>");
