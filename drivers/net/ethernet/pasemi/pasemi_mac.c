<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2007 PA Semi, Inc
 *
 * Driver क्रम the PA Semi PWRficient onchip 1G/10G Ethernet MACs
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/dma-mapping.h>
#समावेश <linux/in.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/ip.h>
#समावेश <net/checksum.h>
#समावेश <linux/prefetch.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/pasemi_dma.h>

#समावेश "pasemi_mac.h"

/* We have our own align, since ppc64 in general has it at 0 because
 * of design flaws in some of the server bridge chips. However, क्रम
 * PWRficient करोing the unaligned copies is more expensive than करोing
 * unaligned DMA, so make sure the data is aligned instead.
 */
#घोषणा LOCAL_SKB_ALIGN	2

/* TODO list
 *
 * - Multicast support
 * - Large MTU support
 * - Multiqueue RX/TX
 */

#घोषणा PE_MIN_MTU	(ETH_ZLEN + ETH_HLEN)
#घोषणा PE_MAX_MTU	9000
#घोषणा PE_DEF_MTU	ETH_DATA_LEN

#घोषणा DEFAULT_MSG_ENABLE	  \
	(NETIF_MSG_DRV		| \
	 NETIF_MSG_PROBE	| \
	 NETIF_MSG_LINK		| \
	 NETIF_MSG_TIMER	| \
	 NETIF_MSG_IFDOWN	| \
	 NETIF_MSG_IFUP		| \
	 NETIF_MSG_RX_ERR	| \
	 NETIF_MSG_TX_ERR)

MODULE_LICENSE("GPL");
MODULE_AUTHOR ("Olof Johansson <olof@lixom.net>");
MODULE_DESCRIPTION("PA Semi PWRficient Ethernet driver");

अटल पूर्णांक debug = -1;	/* -1 == use DEFAULT_MSG_ENABLE as value */
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "PA Semi MAC bitmapped debugging message enable value");

बाह्य स्थिर काष्ठा ethtool_ops pasemi_mac_ethtool_ops;

अटल पूर्णांक translation_enabled(व्योम)
अणु
#अगर defined(CONFIG_PPC_PASEMI_IOMMU_DMA_FORCE)
	वापस 1;
#अन्यथा
	वापस firmware_has_feature(FW_FEATURE_LPAR);
#पूर्ण_अगर
पूर्ण

अटल व्योम ग_लिखो_iob_reg(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	pasemi_ग_लिखो_iob_reg(reg, val);
पूर्ण

अटल अचिन्हित पूर्णांक पढ़ो_mac_reg(स्थिर काष्ठा pasemi_mac *mac, अचिन्हित पूर्णांक reg)
अणु
	वापस pasemi_पढ़ो_mac_reg(mac->dma_अगर, reg);
पूर्ण

अटल व्योम ग_लिखो_mac_reg(स्थिर काष्ठा pasemi_mac *mac, अचिन्हित पूर्णांक reg,
			  अचिन्हित पूर्णांक val)
अणु
	pasemi_ग_लिखो_mac_reg(mac->dma_अगर, reg, val);
पूर्ण

अटल अचिन्हित पूर्णांक पढ़ो_dma_reg(अचिन्हित पूर्णांक reg)
अणु
	वापस pasemi_पढ़ो_dma_reg(reg);
पूर्ण

अटल व्योम ग_लिखो_dma_reg(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	pasemi_ग_लिखो_dma_reg(reg, val);
पूर्ण

अटल काष्ठा pasemi_mac_rxring *rx_ring(स्थिर काष्ठा pasemi_mac *mac)
अणु
	वापस mac->rx;
पूर्ण

अटल काष्ठा pasemi_mac_txring *tx_ring(स्थिर काष्ठा pasemi_mac *mac)
अणु
	वापस mac->tx;
पूर्ण

अटल अंतरभूत व्योम prefetch_skb(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम *d = skb;

	prefetch(d);
	prefetch(d+64);
	prefetch(d+128);
	prefetch(d+192);
पूर्ण

अटल पूर्णांक mac_to_पूर्णांकf(काष्ठा pasemi_mac *mac)
अणु
	काष्ठा pci_dev *pdev = mac->pdev;
	u32 पंचांगp;
	पूर्णांक nपूर्णांकf, off, i, j;
	पूर्णांक devfn = pdev->devfn;

	पंचांगp = पढ़ो_dma_reg(PAS_DMA_CAP_IFI);
	nपूर्णांकf = (पंचांगp & PAS_DMA_CAP_IFI_NIN_M) >> PAS_DMA_CAP_IFI_NIN_S;
	off = (पंचांगp & PAS_DMA_CAP_IFI_IOFF_M) >> PAS_DMA_CAP_IFI_IOFF_S;

	/* IOFF contains the offset to the रेजिस्टरs containing the
	 * DMA पूर्णांकerface-to-MAC-pci-id mappings, and NIN contains number
	 * of total पूर्णांकerfaces. Each रेजिस्टर contains 4 devfns.
	 * Just करो a linear search until we find the devfn of the MAC
	 * we're trying to look up.
	 */

	क्रम (i = 0; i < (nपूर्णांकf+3)/4; i++) अणु
		पंचांगp = पढ़ो_dma_reg(off+4*i);
		क्रम (j = 0; j < 4; j++) अणु
			अगर (((पंचांगp >> (8*j)) & 0xff) == devfn)
				वापस i*4 + j;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम pasemi_mac_पूर्णांकf_disable(काष्ठा pasemi_mac *mac)
अणु
	अचिन्हित पूर्णांक flags;

	flags = पढ़ो_mac_reg(mac, PAS_MAC_CFG_PCFG);
	flags &= ~PAS_MAC_CFG_PCFG_PE;
	ग_लिखो_mac_reg(mac, PAS_MAC_CFG_PCFG, flags);
पूर्ण

अटल व्योम pasemi_mac_पूर्णांकf_enable(काष्ठा pasemi_mac *mac)
अणु
	अचिन्हित पूर्णांक flags;

	flags = पढ़ो_mac_reg(mac, PAS_MAC_CFG_PCFG);
	flags |= PAS_MAC_CFG_PCFG_PE;
	ग_लिखो_mac_reg(mac, PAS_MAC_CFG_PCFG, flags);
पूर्ण

अटल पूर्णांक pasemi_get_mac_addr(काष्ठा pasemi_mac *mac)
अणु
	काष्ठा pci_dev *pdev = mac->pdev;
	काष्ठा device_node *dn = pci_device_to_OF_node(pdev);
	पूर्णांक len;
	स्थिर u8 *maddr;
	u8 addr[ETH_ALEN];

	अगर (!dn) अणु
		dev_dbg(&pdev->dev,
			  "No device node for mac, not configuring\n");
		वापस -ENOENT;
	पूर्ण

	maddr = of_get_property(dn, "local-mac-address", &len);

	अगर (maddr && len == ETH_ALEN) अणु
		स_नकल(mac->mac_addr, maddr, ETH_ALEN);
		वापस 0;
	पूर्ण

	/* Some old versions of firmware mistakenly uses mac-address
	 * (and as a string) instead of a byte array in local-mac-address.
	 */

	अगर (maddr == शून्य)
		maddr = of_get_property(dn, "mac-address", शून्य);

	अगर (maddr == शून्य) अणु
		dev_warn(&pdev->dev,
			 "no mac address in device tree, not configuring\n");
		वापस -ENOENT;
	पूर्ण

	अगर (!mac_pton(maddr, addr)) अणु
		dev_warn(&pdev->dev,
			 "can't parse mac address, not configuring\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(mac->mac_addr, addr, ETH_ALEN);

	वापस 0;
पूर्ण

अटल पूर्णांक pasemi_mac_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;
	अचिन्हित पूर्णांक adr0, adr1;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	adr0 = dev->dev_addr[2] << 24 |
	       dev->dev_addr[3] << 16 |
	       dev->dev_addr[4] << 8 |
	       dev->dev_addr[5];
	adr1 = पढ़ो_mac_reg(mac, PAS_MAC_CFG_ADR1);
	adr1 &= ~0xffff;
	adr1 |= dev->dev_addr[0] << 8 | dev->dev_addr[1];

	pasemi_mac_पूर्णांकf_disable(mac);
	ग_लिखो_mac_reg(mac, PAS_MAC_CFG_ADR0, adr0);
	ग_लिखो_mac_reg(mac, PAS_MAC_CFG_ADR1, adr1);
	pasemi_mac_पूर्णांकf_enable(mac);

	वापस 0;
पूर्ण

अटल पूर्णांक pasemi_mac_unmap_tx_skb(काष्ठा pasemi_mac *mac,
				    स्थिर पूर्णांक nfrags,
				    काष्ठा sk_buff *skb,
				    स्थिर dma_addr_t *dmas)
अणु
	पूर्णांक f;
	काष्ठा pci_dev *pdev = mac->dma_pdev;

	pci_unmap_single(pdev, dmas[0], skb_headlen(skb), PCI_DMA_TODEVICE);

	क्रम (f = 0; f < nfrags; f++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		pci_unmap_page(pdev, dmas[f+1], skb_frag_size(frag), PCI_DMA_TODEVICE);
	पूर्ण
	dev_kमुक्त_skb_irq(skb);

	/* Freed descriptor slot + मुख्य SKB ptr + nfrags additional ptrs,
	 * aligned up to a घातer of 2
	 */
	वापस (nfrags + 3) & ~1;
पूर्ण

अटल काष्ठा pasemi_mac_csring *pasemi_mac_setup_csring(काष्ठा pasemi_mac *mac)
अणु
	काष्ठा pasemi_mac_csring *ring;
	u32 val;
	अचिन्हित पूर्णांक cfg;
	पूर्णांक chno;

	ring = pasemi_dma_alloc_chan(TXCHAN, माप(काष्ठा pasemi_mac_csring),
				       दुरत्व(काष्ठा pasemi_mac_csring, chan));

	अगर (!ring) अणु
		dev_err(&mac->pdev->dev, "Can't allocate checksum channel\n");
		जाओ out_chan;
	पूर्ण

	chno = ring->chan.chno;

	ring->size = CS_RING_SIZE;
	ring->next_to_fill = 0;

	/* Allocate descriptors */
	अगर (pasemi_dma_alloc_ring(&ring->chan, CS_RING_SIZE))
		जाओ out_ring_desc;

	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_BASEL(chno),
		      PAS_DMA_TXCHAN_BASEL_BRBL(ring->chan.ring_dma));
	val = PAS_DMA_TXCHAN_BASEU_BRBH(ring->chan.ring_dma >> 32);
	val |= PAS_DMA_TXCHAN_BASEU_SIZ(CS_RING_SIZE >> 3);

	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_BASEU(chno), val);

	ring->events[0] = pasemi_dma_alloc_flag();
	ring->events[1] = pasemi_dma_alloc_flag();
	अगर (ring->events[0] < 0 || ring->events[1] < 0)
		जाओ out_flags;

	pasemi_dma_clear_flag(ring->events[0]);
	pasemi_dma_clear_flag(ring->events[1]);

	ring->fun = pasemi_dma_alloc_fun();
	अगर (ring->fun < 0)
		जाओ out_fun;

	cfg = PAS_DMA_TXCHAN_CFG_TY_FUNC | PAS_DMA_TXCHAN_CFG_UP |
	      PAS_DMA_TXCHAN_CFG_TATTR(ring->fun) |
	      PAS_DMA_TXCHAN_CFG_LPSQ | PAS_DMA_TXCHAN_CFG_LPDQ;

	अगर (translation_enabled())
		cfg |= PAS_DMA_TXCHAN_CFG_TRD | PAS_DMA_TXCHAN_CFG_TRR;

	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_CFG(chno), cfg);

	/* enable channel */
	pasemi_dma_start_chan(&ring->chan, PAS_DMA_TXCHAN_TCMDSTA_SZ |
					   PAS_DMA_TXCHAN_TCMDSTA_DB |
					   PAS_DMA_TXCHAN_TCMDSTA_DE |
					   PAS_DMA_TXCHAN_TCMDSTA_DA);

	वापस ring;

out_fun:
out_flags:
	अगर (ring->events[0] >= 0)
		pasemi_dma_मुक्त_flag(ring->events[0]);
	अगर (ring->events[1] >= 0)
		pasemi_dma_मुक्त_flag(ring->events[1]);
	pasemi_dma_मुक्त_ring(&ring->chan);
out_ring_desc:
	pasemi_dma_मुक्त_chan(&ring->chan);
out_chan:

	वापस शून्य;
पूर्ण

अटल व्योम pasemi_mac_setup_csrings(काष्ठा pasemi_mac *mac)
अणु
	पूर्णांक i;
	mac->cs[0] = pasemi_mac_setup_csring(mac);
	अगर (mac->type == MAC_TYPE_XAUI)
		mac->cs[1] = pasemi_mac_setup_csring(mac);
	अन्यथा
		mac->cs[1] = 0;

	क्रम (i = 0; i < MAX_CS; i++)
		अगर (mac->cs[i])
			mac->num_cs++;
पूर्ण

अटल व्योम pasemi_mac_मुक्त_csring(काष्ठा pasemi_mac_csring *csring)
अणु
	pasemi_dma_stop_chan(&csring->chan);
	pasemi_dma_मुक्त_flag(csring->events[0]);
	pasemi_dma_मुक्त_flag(csring->events[1]);
	pasemi_dma_मुक्त_ring(&csring->chan);
	pasemi_dma_मुक्त_chan(&csring->chan);
	pasemi_dma_मुक्त_fun(csring->fun);
पूर्ण

अटल पूर्णांक pasemi_mac_setup_rx_resources(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा pasemi_mac_rxring *ring;
	काष्ठा pasemi_mac *mac = netdev_priv(dev);
	पूर्णांक chno;
	अचिन्हित पूर्णांक cfg;

	ring = pasemi_dma_alloc_chan(RXCHAN, माप(काष्ठा pasemi_mac_rxring),
				     दुरत्व(काष्ठा pasemi_mac_rxring, chan));

	अगर (!ring) अणु
		dev_err(&mac->pdev->dev, "Can't allocate RX channel\n");
		जाओ out_chan;
	पूर्ण
	chno = ring->chan.chno;

	spin_lock_init(&ring->lock);

	ring->size = RX_RING_SIZE;
	ring->ring_info = kसुस्मृति(RX_RING_SIZE,
				  माप(काष्ठा pasemi_mac_buffer),
				  GFP_KERNEL);

	अगर (!ring->ring_info)
		जाओ out_ring_info;

	/* Allocate descriptors */
	अगर (pasemi_dma_alloc_ring(&ring->chan, RX_RING_SIZE))
		जाओ out_ring_desc;

	ring->buffers = dma_alloc_coherent(&mac->dma_pdev->dev,
					   RX_RING_SIZE * माप(u64),
					   &ring->buf_dma, GFP_KERNEL);
	अगर (!ring->buffers)
		जाओ out_ring_desc;

	ग_लिखो_dma_reg(PAS_DMA_RXCHAN_BASEL(chno),
		      PAS_DMA_RXCHAN_BASEL_BRBL(ring->chan.ring_dma));

	ग_लिखो_dma_reg(PAS_DMA_RXCHAN_BASEU(chno),
		      PAS_DMA_RXCHAN_BASEU_BRBH(ring->chan.ring_dma >> 32) |
		      PAS_DMA_RXCHAN_BASEU_SIZ(RX_RING_SIZE >> 3));

	cfg = PAS_DMA_RXCHAN_CFG_HBU(2);

	अगर (translation_enabled())
		cfg |= PAS_DMA_RXCHAN_CFG_CTR;

	ग_लिखो_dma_reg(PAS_DMA_RXCHAN_CFG(chno), cfg);

	ग_लिखो_dma_reg(PAS_DMA_RXINT_BASEL(mac->dma_अगर),
		      PAS_DMA_RXINT_BASEL_BRBL(ring->buf_dma));

	ग_लिखो_dma_reg(PAS_DMA_RXINT_BASEU(mac->dma_अगर),
		      PAS_DMA_RXINT_BASEU_BRBH(ring->buf_dma >> 32) |
		      PAS_DMA_RXINT_BASEU_SIZ(RX_RING_SIZE >> 3));

	cfg = PAS_DMA_RXINT_CFG_DHL(2) | PAS_DMA_RXINT_CFG_L2 |
	      PAS_DMA_RXINT_CFG_LW | PAS_DMA_RXINT_CFG_RBP |
	      PAS_DMA_RXINT_CFG_HEN;

	अगर (translation_enabled())
		cfg |= PAS_DMA_RXINT_CFG_ITRR | PAS_DMA_RXINT_CFG_ITR;

	ग_लिखो_dma_reg(PAS_DMA_RXINT_CFG(mac->dma_अगर), cfg);

	ring->next_to_fill = 0;
	ring->next_to_clean = 0;
	ring->mac = mac;
	mac->rx = ring;

	वापस 0;

out_ring_desc:
	kमुक्त(ring->ring_info);
out_ring_info:
	pasemi_dma_मुक्त_chan(&ring->chan);
out_chan:
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा pasemi_mac_txring *
pasemi_mac_setup_tx_resources(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(dev);
	u32 val;
	काष्ठा pasemi_mac_txring *ring;
	अचिन्हित पूर्णांक cfg;
	पूर्णांक chno;

	ring = pasemi_dma_alloc_chan(TXCHAN, माप(काष्ठा pasemi_mac_txring),
				     दुरत्व(काष्ठा pasemi_mac_txring, chan));

	अगर (!ring) अणु
		dev_err(&mac->pdev->dev, "Can't allocate TX channel\n");
		जाओ out_chan;
	पूर्ण

	chno = ring->chan.chno;

	spin_lock_init(&ring->lock);

	ring->size = TX_RING_SIZE;
	ring->ring_info = kसुस्मृति(TX_RING_SIZE,
				  माप(काष्ठा pasemi_mac_buffer),
				  GFP_KERNEL);
	अगर (!ring->ring_info)
		जाओ out_ring_info;

	/* Allocate descriptors */
	अगर (pasemi_dma_alloc_ring(&ring->chan, TX_RING_SIZE))
		जाओ out_ring_desc;

	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_BASEL(chno),
		      PAS_DMA_TXCHAN_BASEL_BRBL(ring->chan.ring_dma));
	val = PAS_DMA_TXCHAN_BASEU_BRBH(ring->chan.ring_dma >> 32);
	val |= PAS_DMA_TXCHAN_BASEU_SIZ(TX_RING_SIZE >> 3);

	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_BASEU(chno), val);

	cfg = PAS_DMA_TXCHAN_CFG_TY_IFACE |
	      PAS_DMA_TXCHAN_CFG_TATTR(mac->dma_अगर) |
	      PAS_DMA_TXCHAN_CFG_UP |
	      PAS_DMA_TXCHAN_CFG_WT(4);

	अगर (translation_enabled())
		cfg |= PAS_DMA_TXCHAN_CFG_TRD | PAS_DMA_TXCHAN_CFG_TRR;

	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_CFG(chno), cfg);

	ring->next_to_fill = 0;
	ring->next_to_clean = 0;
	ring->mac = mac;

	वापस ring;

out_ring_desc:
	kमुक्त(ring->ring_info);
out_ring_info:
	pasemi_dma_मुक्त_chan(&ring->chan);
out_chan:
	वापस शून्य;
पूर्ण

अटल व्योम pasemi_mac_मुक्त_tx_resources(काष्ठा pasemi_mac *mac)
अणु
	काष्ठा pasemi_mac_txring *txring = tx_ring(mac);
	अचिन्हित पूर्णांक i, j;
	काष्ठा pasemi_mac_buffer *info;
	dma_addr_t dmas[MAX_SKB_FRAGS+1];
	पूर्णांक मुक्तd, nfrags;
	पूर्णांक start, limit;

	start = txring->next_to_clean;
	limit = txring->next_to_fill;

	/* Compensate क्रम when fill has wrapped and clean has not */
	अगर (start > limit)
		limit += TX_RING_SIZE;

	क्रम (i = start; i < limit; i += मुक्तd) अणु
		info = &txring->ring_info[(i+1) & (TX_RING_SIZE-1)];
		अगर (info->dma && info->skb) अणु
			nfrags = skb_shinfo(info->skb)->nr_frags;
			क्रम (j = 0; j <= nfrags; j++)
				dmas[j] = txring->ring_info[(i+1+j) &
						(TX_RING_SIZE-1)].dma;
			मुक्तd = pasemi_mac_unmap_tx_skb(mac, nfrags,
							info->skb, dmas);
		पूर्ण अन्यथा अणु
			मुक्तd = 2;
		पूर्ण
	पूर्ण

	kमुक्त(txring->ring_info);
	pasemi_dma_मुक्त_chan(&txring->chan);

पूर्ण

अटल व्योम pasemi_mac_मुक्त_rx_buffers(काष्ठा pasemi_mac *mac)
अणु
	काष्ठा pasemi_mac_rxring *rx = rx_ring(mac);
	अचिन्हित पूर्णांक i;
	काष्ठा pasemi_mac_buffer *info;

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		info = &RX_DESC_INFO(rx, i);
		अगर (info->skb && info->dma) अणु
			pci_unmap_single(mac->dma_pdev,
					 info->dma,
					 info->skb->len,
					 PCI_DMA_FROMDEVICE);
			dev_kमुक्त_skb_any(info->skb);
		पूर्ण
		info->dma = 0;
		info->skb = शून्य;
	पूर्ण

	क्रम (i = 0; i < RX_RING_SIZE; i++)
		RX_BUFF(rx, i) = 0;
पूर्ण

अटल व्योम pasemi_mac_मुक्त_rx_resources(काष्ठा pasemi_mac *mac)
अणु
	pasemi_mac_मुक्त_rx_buffers(mac);

	dma_मुक्त_coherent(&mac->dma_pdev->dev, RX_RING_SIZE * माप(u64),
			  rx_ring(mac)->buffers, rx_ring(mac)->buf_dma);

	kमुक्त(rx_ring(mac)->ring_info);
	pasemi_dma_मुक्त_chan(&rx_ring(mac)->chan);
	mac->rx = शून्य;
पूर्ण

अटल व्योम pasemi_mac_replenish_rx_ring(काष्ठा net_device *dev,
					 स्थिर पूर्णांक limit)
अणु
	स्थिर काष्ठा pasemi_mac *mac = netdev_priv(dev);
	काष्ठा pasemi_mac_rxring *rx = rx_ring(mac);
	पूर्णांक fill, count;

	अगर (limit <= 0)
		वापस;

	fill = rx_ring(mac)->next_to_fill;
	क्रम (count = 0; count < limit; count++) अणु
		काष्ठा pasemi_mac_buffer *info = &RX_DESC_INFO(rx, fill);
		u64 *buff = &RX_BUFF(rx, fill);
		काष्ठा sk_buff *skb;
		dma_addr_t dma;

		/* Entry in use? */
		WARN_ON(*buff);

		skb = netdev_alloc_skb(dev, mac->bufsz);
		skb_reserve(skb, LOCAL_SKB_ALIGN);

		अगर (unlikely(!skb))
			अवरोध;

		dma = pci_map_single(mac->dma_pdev, skb->data,
				     mac->bufsz - LOCAL_SKB_ALIGN,
				     PCI_DMA_FROMDEVICE);

		अगर (unlikely(pci_dma_mapping_error(mac->dma_pdev, dma))) अणु
			dev_kमुक्त_skb_irq(info->skb);
			अवरोध;
		पूर्ण

		info->skb = skb;
		info->dma = dma;
		*buff = XCT_RXB_LEN(mac->bufsz) | XCT_RXB_ADDR(dma);
		fill++;
	पूर्ण

	wmb();

	ग_लिखो_dma_reg(PAS_DMA_RXINT_INCR(mac->dma_अगर), count);

	rx_ring(mac)->next_to_fill = (rx_ring(mac)->next_to_fill + count) &
				(RX_RING_SIZE - 1);
पूर्ण

अटल व्योम pasemi_mac_restart_rx_पूर्णांकr(स्थिर काष्ठा pasemi_mac *mac)
अणु
	काष्ठा pasemi_mac_rxring *rx = rx_ring(mac);
	अचिन्हित पूर्णांक reg, pcnt;
	/* Re-enable packet count पूर्णांकerrupts: finally
	 * ack the packet count पूर्णांकerrupt we got in rx_पूर्णांकr.
	 */

	pcnt = *rx->chan.status & PAS_STATUS_PCNT_M;

	reg = PAS_IOB_DMA_RXCH_RESET_PCNT(pcnt) | PAS_IOB_DMA_RXCH_RESET_PINTC;

	अगर (*rx->chan.status & PAS_STATUS_TIMER)
		reg |= PAS_IOB_DMA_RXCH_RESET_TINTC;

	ग_लिखो_iob_reg(PAS_IOB_DMA_RXCH_RESET(mac->rx->chan.chno), reg);
पूर्ण

अटल व्योम pasemi_mac_restart_tx_पूर्णांकr(स्थिर काष्ठा pasemi_mac *mac)
अणु
	अचिन्हित पूर्णांक reg, pcnt;

	/* Re-enable packet count पूर्णांकerrupts */
	pcnt = *tx_ring(mac)->chan.status & PAS_STATUS_PCNT_M;

	reg = PAS_IOB_DMA_TXCH_RESET_PCNT(pcnt) | PAS_IOB_DMA_TXCH_RESET_PINTC;

	ग_लिखो_iob_reg(PAS_IOB_DMA_TXCH_RESET(tx_ring(mac)->chan.chno), reg);
पूर्ण


अटल अंतरभूत व्योम pasemi_mac_rx_error(स्थिर काष्ठा pasemi_mac *mac,
				       स्थिर u64 macrx)
अणु
	अचिन्हित पूर्णांक rcmdsta, ccmdsta;
	काष्ठा pasemi_dmachan *chan = &rx_ring(mac)->chan;

	अगर (!netअगर_msg_rx_err(mac))
		वापस;

	rcmdsta = पढ़ो_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_अगर));
	ccmdsta = पढ़ो_dma_reg(PAS_DMA_RXCHAN_CCMDSTA(chan->chno));

	prपूर्णांकk(KERN_ERR "pasemi_mac: rx error. macrx %016llx, rx status %llx\n",
		macrx, *chan->status);

	prपूर्णांकk(KERN_ERR "pasemi_mac: rcmdsta %08x ccmdsta %08x\n",
		rcmdsta, ccmdsta);
पूर्ण

अटल अंतरभूत व्योम pasemi_mac_tx_error(स्थिर काष्ठा pasemi_mac *mac,
				       स्थिर u64 mactx)
अणु
	अचिन्हित पूर्णांक cmdsta;
	काष्ठा pasemi_dmachan *chan = &tx_ring(mac)->chan;

	अगर (!netअगर_msg_tx_err(mac))
		वापस;

	cmdsta = पढ़ो_dma_reg(PAS_DMA_TXCHAN_TCMDSTA(chan->chno));

	prपूर्णांकk(KERN_ERR "pasemi_mac: tx error. mactx 0x%016llx, "\
		"tx status 0x%016llx\n", mactx, *chan->status);

	prपूर्णांकk(KERN_ERR "pasemi_mac: tcmdsta 0x%08x\n", cmdsta);
पूर्ण

अटल पूर्णांक pasemi_mac_clean_rx(काष्ठा pasemi_mac_rxring *rx,
			       स्थिर पूर्णांक limit)
अणु
	स्थिर काष्ठा pasemi_dmachan *chan = &rx->chan;
	काष्ठा pasemi_mac *mac = rx->mac;
	काष्ठा pci_dev *pdev = mac->dma_pdev;
	अचिन्हित पूर्णांक n;
	पूर्णांक count, buf_index, tot_bytes, packets;
	काष्ठा pasemi_mac_buffer *info;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;
	u64 macrx, eval;
	dma_addr_t dma;

	tot_bytes = 0;
	packets = 0;

	spin_lock(&rx->lock);

	n = rx->next_to_clean;

	prefetch(&RX_DESC(rx, n));

	क्रम (count = 0; count < limit; count++) अणु
		macrx = RX_DESC(rx, n);
		prefetch(&RX_DESC(rx, n+4));

		अगर ((macrx & XCT_MACRX_E) ||
		    (*chan->status & PAS_STATUS_ERROR))
			pasemi_mac_rx_error(mac, macrx);

		अगर (!(macrx & XCT_MACRX_O))
			अवरोध;

		info = शून्य;

		BUG_ON(!(macrx & XCT_MACRX_RR_8BRES));

		eval = (RX_DESC(rx, n+1) & XCT_RXRES_8B_EVAL_M) >>
			XCT_RXRES_8B_EVAL_S;
		buf_index = eval-1;

		dma = (RX_DESC(rx, n+2) & XCT_PTR_ADDR_M);
		info = &RX_DESC_INFO(rx, buf_index);

		skb = info->skb;

		prefetch_skb(skb);

		len = (macrx & XCT_MACRX_LLEN_M) >> XCT_MACRX_LLEN_S;

		pci_unmap_single(pdev, dma, mac->bufsz - LOCAL_SKB_ALIGN,
				 PCI_DMA_FROMDEVICE);

		अगर (macrx & XCT_MACRX_CRC) अणु
			/* CRC error flagged */
			mac->netdev->stats.rx_errors++;
			mac->netdev->stats.rx_crc_errors++;
			/* No need to मुक्त skb, it'll be reused */
			जाओ next;
		पूर्ण

		info->skb = शून्य;
		info->dma = 0;

		अगर (likely((macrx & XCT_MACRX_HTY_M) == XCT_MACRX_HTY_IPV4_OK)) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			skb->csum = (macrx & XCT_MACRX_CSUM_M) >>
					   XCT_MACRX_CSUM_S;
		पूर्ण अन्यथा अणु
			skb_checksum_none_निश्चित(skb);
		पूर्ण

		packets++;
		tot_bytes += len;

		/* Don't include CRC */
		skb_put(skb, len-4);

		skb->protocol = eth_type_trans(skb, mac->netdev);
		napi_gro_receive(&mac->napi, skb);

next:
		RX_DESC(rx, n) = 0;
		RX_DESC(rx, n+1) = 0;

		/* Need to zero it out since hardware करोesn't, since the
		 * replenish loop uses it to tell when it's करोne.
		 */
		RX_BUFF(rx, buf_index) = 0;

		n += 4;
	पूर्ण

	अगर (n > RX_RING_SIZE) अणु
		/* Errata 5971 workaround: L2 target of headers */
		ग_लिखो_iob_reg(PAS_IOB_COM_PKTHDRCNT, 0);
		n &= (RX_RING_SIZE-1);
	पूर्ण

	rx_ring(mac)->next_to_clean = n;

	/* Increase is in number of 16-byte entries, and since each descriptor
	 * with an 8BRES takes up 3x8 bytes (padded to 4x8), increase with
	 * count*2.
	 */
	ग_लिखो_dma_reg(PAS_DMA_RXCHAN_INCR(mac->rx->chan.chno), count << 1);

	pasemi_mac_replenish_rx_ring(mac->netdev, count);

	mac->netdev->stats.rx_bytes += tot_bytes;
	mac->netdev->stats.rx_packets += packets;

	spin_unlock(&rx_ring(mac)->lock);

	वापस count;
पूर्ण

/* Can't make this too large or we blow the kernel stack limits */
#घोषणा TX_CLEAN_BATCHSIZE (128/MAX_SKB_FRAGS)

अटल पूर्णांक pasemi_mac_clean_tx(काष्ठा pasemi_mac_txring *txring)
अणु
	काष्ठा pasemi_dmachan *chan = &txring->chan;
	काष्ठा pasemi_mac *mac = txring->mac;
	पूर्णांक i, j;
	अचिन्हित पूर्णांक start, descr_count, buf_count, batch_limit;
	अचिन्हित पूर्णांक ring_limit;
	अचिन्हित पूर्णांक total_count;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skbs[TX_CLEAN_BATCHSIZE];
	dma_addr_t dmas[TX_CLEAN_BATCHSIZE][MAX_SKB_FRAGS+1];
	पूर्णांक nf[TX_CLEAN_BATCHSIZE];
	पूर्णांक nr_frags;

	total_count = 0;
	batch_limit = TX_CLEAN_BATCHSIZE;
restart:
	spin_lock_irqsave(&txring->lock, flags);

	start = txring->next_to_clean;
	ring_limit = txring->next_to_fill;

	prefetch(&TX_DESC_INFO(txring, start+1).skb);

	/* Compensate क्रम when fill has wrapped but clean has not */
	अगर (start > ring_limit)
		ring_limit += TX_RING_SIZE;

	buf_count = 0;
	descr_count = 0;

	क्रम (i = start;
	     descr_count < batch_limit && i < ring_limit;
	     i += buf_count) अणु
		u64 mactx = TX_DESC(txring, i);
		काष्ठा sk_buff *skb;

		अगर ((mactx  & XCT_MACTX_E) ||
		    (*chan->status & PAS_STATUS_ERROR))
			pasemi_mac_tx_error(mac, mactx);

		/* Skip over control descriptors */
		अगर (!(mactx & XCT_MACTX_LLEN_M)) अणु
			TX_DESC(txring, i) = 0;
			TX_DESC(txring, i+1) = 0;
			buf_count = 2;
			जारी;
		पूर्ण

		skb = TX_DESC_INFO(txring, i+1).skb;
		nr_frags = TX_DESC_INFO(txring, i).dma;

		अगर (unlikely(mactx & XCT_MACTX_O))
			/* Not yet transmitted */
			अवरोध;

		buf_count = 2 + nr_frags;
		/* Since we always fill with an even number of entries, make
		 * sure we skip any unused one at the end as well.
		 */
		अगर (buf_count & 1)
			buf_count++;

		क्रम (j = 0; j <= nr_frags; j++)
			dmas[descr_count][j] = TX_DESC_INFO(txring, i+1+j).dma;

		skbs[descr_count] = skb;
		nf[descr_count] = nr_frags;

		TX_DESC(txring, i) = 0;
		TX_DESC(txring, i+1) = 0;

		descr_count++;
	पूर्ण
	txring->next_to_clean = i & (TX_RING_SIZE-1);

	spin_unlock_irqrestore(&txring->lock, flags);
	netअगर_wake_queue(mac->netdev);

	क्रम (i = 0; i < descr_count; i++)
		pasemi_mac_unmap_tx_skb(mac, nf[i], skbs[i], dmas[i]);

	total_count += descr_count;

	/* If the batch was full, try to clean more */
	अगर (descr_count == batch_limit)
		जाओ restart;

	वापस total_count;
पूर्ण


अटल irqवापस_t pasemi_mac_rx_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	स्थिर काष्ठा pasemi_mac_rxring *rxring = data;
	काष्ठा pasemi_mac *mac = rxring->mac;
	स्थिर काष्ठा pasemi_dmachan *chan = &rxring->chan;
	अचिन्हित पूर्णांक reg;

	अगर (!(*chan->status & PAS_STATUS_CAUSE_M))
		वापस IRQ_NONE;

	/* Don't reset packet count so it won't fire again but clear
	 * all others.
	 */

	reg = 0;
	अगर (*chan->status & PAS_STATUS_SOFT)
		reg |= PAS_IOB_DMA_RXCH_RESET_SINTC;
	अगर (*chan->status & PAS_STATUS_ERROR)
		reg |= PAS_IOB_DMA_RXCH_RESET_DINTC;

	napi_schedule(&mac->napi);

	ग_लिखो_iob_reg(PAS_IOB_DMA_RXCH_RESET(chan->chno), reg);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा TX_CLEAN_INTERVAL HZ

अटल व्योम pasemi_mac_tx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा pasemi_mac_txring *txring = from_समयr(txring, t, clean_समयr);
	काष्ठा pasemi_mac *mac = txring->mac;

	pasemi_mac_clean_tx(txring);

	mod_समयr(&txring->clean_समयr, jअगरfies + TX_CLEAN_INTERVAL);

	pasemi_mac_restart_tx_पूर्णांकr(mac);
पूर्ण

अटल irqवापस_t pasemi_mac_tx_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pasemi_mac_txring *txring = data;
	स्थिर काष्ठा pasemi_dmachan *chan = &txring->chan;
	काष्ठा pasemi_mac *mac = txring->mac;
	अचिन्हित पूर्णांक reg;

	अगर (!(*chan->status & PAS_STATUS_CAUSE_M))
		वापस IRQ_NONE;

	reg = 0;

	अगर (*chan->status & PAS_STATUS_SOFT)
		reg |= PAS_IOB_DMA_TXCH_RESET_SINTC;
	अगर (*chan->status & PAS_STATUS_ERROR)
		reg |= PAS_IOB_DMA_TXCH_RESET_DINTC;

	mod_समयr(&txring->clean_समयr, jअगरfies + (TX_CLEAN_INTERVAL)*2);

	napi_schedule(&mac->napi);

	अगर (reg)
		ग_लिखो_iob_reg(PAS_IOB_DMA_TXCH_RESET(chan->chno), reg);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pasemi_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(dev);
	पूर्णांक msg;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक new_flags;

	अगर (!dev->phydev->link) अणु
		/* If no link, MAC speed settings करोn't matter. Just report
		 * link करोwn and वापस.
		 */
		अगर (mac->link && netअगर_msg_link(mac))
			prपूर्णांकk(KERN_INFO "%s: Link is down.\n", dev->name);

		netअगर_carrier_off(dev);
		pasemi_mac_पूर्णांकf_disable(mac);
		mac->link = 0;

		वापस;
	पूर्ण अन्यथा अणु
		pasemi_mac_पूर्णांकf_enable(mac);
		netअगर_carrier_on(dev);
	पूर्ण

	flags = पढ़ो_mac_reg(mac, PAS_MAC_CFG_PCFG);
	new_flags = flags & ~(PAS_MAC_CFG_PCFG_HD | PAS_MAC_CFG_PCFG_SPD_M |
			      PAS_MAC_CFG_PCFG_TSR_M);

	अगर (!dev->phydev->duplex)
		new_flags |= PAS_MAC_CFG_PCFG_HD;

	चयन (dev->phydev->speed) अणु
	हाल 1000:
		new_flags |= PAS_MAC_CFG_PCFG_SPD_1G |
			     PAS_MAC_CFG_PCFG_TSR_1G;
		अवरोध;
	हाल 100:
		new_flags |= PAS_MAC_CFG_PCFG_SPD_100M |
			     PAS_MAC_CFG_PCFG_TSR_100M;
		अवरोध;
	हाल 10:
		new_flags |= PAS_MAC_CFG_PCFG_SPD_10M |
			     PAS_MAC_CFG_PCFG_TSR_10M;
		अवरोध;
	शेष:
		prपूर्णांकk("Unsupported speed %d\n", dev->phydev->speed);
	पूर्ण

	/* Prपूर्णांक on link or speed/duplex change */
	msg = mac->link != dev->phydev->link || flags != new_flags;

	mac->duplex = dev->phydev->duplex;
	mac->speed = dev->phydev->speed;
	mac->link = dev->phydev->link;

	अगर (new_flags != flags)
		ग_लिखो_mac_reg(mac, PAS_MAC_CFG_PCFG, new_flags);

	अगर (msg && netअगर_msg_link(mac))
		prपूर्णांकk(KERN_INFO "%s: Link is up at %d Mbps, %s duplex.\n",
		       dev->name, mac->speed, mac->duplex ? "full" : "half");
पूर्ण

अटल पूर्णांक pasemi_mac_phy_init(काष्ठा net_device *dev)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(dev);
	काष्ठा device_node *dn, *phy_dn;
	काष्ठा phy_device *phydev;

	dn = pci_device_to_OF_node(mac->pdev);
	phy_dn = of_parse_phandle(dn, "phy-handle", 0);

	mac->link = 0;
	mac->speed = 0;
	mac->duplex = -1;

	phydev = of_phy_connect(dev, phy_dn, &pasemi_adjust_link, 0,
				PHY_INTERFACE_MODE_SGMII);

	of_node_put(phy_dn);
	अगर (!phydev) अणु
		prपूर्णांकk(KERN_ERR "%s: Could not attach to phy\n", dev->name);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक pasemi_mac_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(dev);
	अचिन्हित पूर्णांक flags;
	पूर्णांक i, ret;

	flags = PAS_MAC_CFG_TXP_FCE | PAS_MAC_CFG_TXP_FPC(3) |
		PAS_MAC_CFG_TXP_SL(3) | PAS_MAC_CFG_TXP_COB(0xf) |
		PAS_MAC_CFG_TXP_TIFT(8) | PAS_MAC_CFG_TXP_TIFG(12);

	ग_लिखो_mac_reg(mac, PAS_MAC_CFG_TXP, flags);

	ret = pasemi_mac_setup_rx_resources(dev);
	अगर (ret)
		जाओ out_rx_resources;

	mac->tx = pasemi_mac_setup_tx_resources(dev);

	अगर (!mac->tx) अणु
		ret = -ENOMEM;
		जाओ out_tx_ring;
	पूर्ण

	/* We might alपढ़ोy have allocated rings in हाल mtu was changed
	 * beक्रमe पूर्णांकerface was brought up.
	 */
	अगर (dev->mtu > 1500 && !mac->num_cs) अणु
		pasemi_mac_setup_csrings(mac);
		अगर (!mac->num_cs) अणु
			ret = -ENOMEM;
			जाओ out_tx_ring;
		पूर्ण
	पूर्ण

	/* Zero out rmon counters */
	क्रम (i = 0; i < 32; i++)
		ग_लिखो_mac_reg(mac, PAS_MAC_RMON(i), 0);

	/* 0x3ff with 33MHz घड़ी is about 31us */
	ग_लिखो_iob_reg(PAS_IOB_DMA_COM_TIMEOUTCFG,
		      PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT(0x3ff));

	ग_लिखो_iob_reg(PAS_IOB_DMA_RXCH_CFG(mac->rx->chan.chno),
		      PAS_IOB_DMA_RXCH_CFG_CNTTH(256));

	ग_लिखो_iob_reg(PAS_IOB_DMA_TXCH_CFG(mac->tx->chan.chno),
		      PAS_IOB_DMA_TXCH_CFG_CNTTH(32));

	ग_लिखो_mac_reg(mac, PAS_MAC_IPC_CHNL,
		      PAS_MAC_IPC_CHNL_DCHNO(mac->rx->chan.chno) |
		      PAS_MAC_IPC_CHNL_BCH(mac->rx->chan.chno));

	/* enable rx अगर */
	ग_लिखो_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_अगर),
		      PAS_DMA_RXINT_RCMDSTA_EN |
		      PAS_DMA_RXINT_RCMDSTA_DROPS_M |
		      PAS_DMA_RXINT_RCMDSTA_BP |
		      PAS_DMA_RXINT_RCMDSTA_OO |
		      PAS_DMA_RXINT_RCMDSTA_BT);

	/* enable rx channel */
	pasemi_dma_start_chan(&rx_ring(mac)->chan, PAS_DMA_RXCHAN_CCMDSTA_DU |
						   PAS_DMA_RXCHAN_CCMDSTA_OD |
						   PAS_DMA_RXCHAN_CCMDSTA_FD |
						   PAS_DMA_RXCHAN_CCMDSTA_DT);

	/* enable tx channel */
	pasemi_dma_start_chan(&tx_ring(mac)->chan, PAS_DMA_TXCHAN_TCMDSTA_SZ |
						   PAS_DMA_TXCHAN_TCMDSTA_DB |
						   PAS_DMA_TXCHAN_TCMDSTA_DE |
						   PAS_DMA_TXCHAN_TCMDSTA_DA);

	pasemi_mac_replenish_rx_ring(dev, RX_RING_SIZE);

	ग_लिखो_dma_reg(PAS_DMA_RXCHAN_INCR(rx_ring(mac)->chan.chno),
		      RX_RING_SIZE>>1);

	/* Clear out any residual packet count state from firmware */
	pasemi_mac_restart_rx_पूर्णांकr(mac);
	pasemi_mac_restart_tx_पूर्णांकr(mac);

	flags = PAS_MAC_CFG_PCFG_S1 | PAS_MAC_CFG_PCFG_PR | PAS_MAC_CFG_PCFG_CE;

	अगर (mac->type == MAC_TYPE_GMAC)
		flags |= PAS_MAC_CFG_PCFG_TSR_1G | PAS_MAC_CFG_PCFG_SPD_1G;
	अन्यथा
		flags |= PAS_MAC_CFG_PCFG_TSR_10G | PAS_MAC_CFG_PCFG_SPD_10G;

	/* Enable पूर्णांकerface in MAC */
	ग_लिखो_mac_reg(mac, PAS_MAC_CFG_PCFG, flags);

	ret = pasemi_mac_phy_init(dev);
	अगर (ret) अणु
		/* Since we won't get link notअगरication, just enable RX */
		pasemi_mac_पूर्णांकf_enable(mac);
		अगर (mac->type == MAC_TYPE_GMAC) अणु
			/* Warn क्रम missing PHY on SGMII (1Gig) ports */
			dev_warn(&mac->pdev->dev,
				 "PHY init failed: %d.\n", ret);
			dev_warn(&mac->pdev->dev,
				 "Defaulting to 1Gbit full duplex\n");
		पूर्ण
	पूर्ण

	netअगर_start_queue(dev);
	napi_enable(&mac->napi);

	snम_लिखो(mac->tx_irq_name, माप(mac->tx_irq_name), "%s tx",
		 dev->name);

	ret = request_irq(mac->tx->chan.irq, pasemi_mac_tx_पूर्णांकr, 0,
			  mac->tx_irq_name, mac->tx);
	अगर (ret) अणु
		dev_err(&mac->pdev->dev, "request_irq of irq %d failed: %d\n",
			mac->tx->chan.irq, ret);
		जाओ out_tx_पूर्णांक;
	पूर्ण

	snम_लिखो(mac->rx_irq_name, माप(mac->rx_irq_name), "%s rx",
		 dev->name);

	ret = request_irq(mac->rx->chan.irq, pasemi_mac_rx_पूर्णांकr, 0,
			  mac->rx_irq_name, mac->rx);
	अगर (ret) अणु
		dev_err(&mac->pdev->dev, "request_irq of irq %d failed: %d\n",
			mac->rx->chan.irq, ret);
		जाओ out_rx_पूर्णांक;
	पूर्ण

	अगर (dev->phydev)
		phy_start(dev->phydev);

	समयr_setup(&mac->tx->clean_समयr, pasemi_mac_tx_समयr, 0);
	mod_समयr(&mac->tx->clean_समयr, jअगरfies + HZ);

	वापस 0;

out_rx_पूर्णांक:
	मुक्त_irq(mac->tx->chan.irq, mac->tx);
out_tx_पूर्णांक:
	napi_disable(&mac->napi);
	netअगर_stop_queue(dev);
out_tx_ring:
	अगर (mac->tx)
		pasemi_mac_मुक्त_tx_resources(mac);
	pasemi_mac_मुक्त_rx_resources(mac);
out_rx_resources:

	वापस ret;
पूर्ण

#घोषणा MAX_RETRIES 5000

अटल व्योम pasemi_mac_छोड़ो_txchan(काष्ठा pasemi_mac *mac)
अणु
	अचिन्हित पूर्णांक sta, retries;
	पूर्णांक txch = tx_ring(mac)->chan.chno;

	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_TCMDSTA(txch),
		      PAS_DMA_TXCHAN_TCMDSTA_ST);

	क्रम (retries = 0; retries < MAX_RETRIES; retries++) अणु
		sta = पढ़ो_dma_reg(PAS_DMA_TXCHAN_TCMDSTA(txch));
		अगर (!(sta & PAS_DMA_TXCHAN_TCMDSTA_ACT))
			अवरोध;
		cond_resched();
	पूर्ण

	अगर (sta & PAS_DMA_TXCHAN_TCMDSTA_ACT)
		dev_err(&mac->dma_pdev->dev,
			"Failed to stop tx channel, tcmdsta %08x\n", sta);

	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_TCMDSTA(txch), 0);
पूर्ण

अटल व्योम pasemi_mac_छोड़ो_rxchan(काष्ठा pasemi_mac *mac)
अणु
	अचिन्हित पूर्णांक sta, retries;
	पूर्णांक rxch = rx_ring(mac)->chan.chno;

	ग_लिखो_dma_reg(PAS_DMA_RXCHAN_CCMDSTA(rxch),
		      PAS_DMA_RXCHAN_CCMDSTA_ST);
	क्रम (retries = 0; retries < MAX_RETRIES; retries++) अणु
		sta = पढ़ो_dma_reg(PAS_DMA_RXCHAN_CCMDSTA(rxch));
		अगर (!(sta & PAS_DMA_RXCHAN_CCMDSTA_ACT))
			अवरोध;
		cond_resched();
	पूर्ण

	अगर (sta & PAS_DMA_RXCHAN_CCMDSTA_ACT)
		dev_err(&mac->dma_pdev->dev,
			"Failed to stop rx channel, ccmdsta 08%x\n", sta);
	ग_लिखो_dma_reg(PAS_DMA_RXCHAN_CCMDSTA(rxch), 0);
पूर्ण

अटल व्योम pasemi_mac_छोड़ो_rxपूर्णांक(काष्ठा pasemi_mac *mac)
अणु
	अचिन्हित पूर्णांक sta, retries;

	ग_लिखो_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_अगर),
		      PAS_DMA_RXINT_RCMDSTA_ST);
	क्रम (retries = 0; retries < MAX_RETRIES; retries++) अणु
		sta = पढ़ो_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_अगर));
		अगर (!(sta & PAS_DMA_RXINT_RCMDSTA_ACT))
			अवरोध;
		cond_resched();
	पूर्ण

	अगर (sta & PAS_DMA_RXINT_RCMDSTA_ACT)
		dev_err(&mac->dma_pdev->dev,
			"Failed to stop rx interface, rcmdsta %08x\n", sta);
	ग_लिखो_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_अगर), 0);
पूर्ण

अटल पूर्णांक pasemi_mac_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(dev);
	अचिन्हित पूर्णांक sta;
	पूर्णांक rxch, txch, i;

	rxch = rx_ring(mac)->chan.chno;
	txch = tx_ring(mac)->chan.chno;

	अगर (dev->phydev) अणु
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
	पूर्ण

	del_समयr_sync(&mac->tx->clean_समयr);

	netअगर_stop_queue(dev);
	napi_disable(&mac->napi);

	sta = पढ़ो_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_अगर));
	अगर (sta & (PAS_DMA_RXINT_RCMDSTA_BP |
		      PAS_DMA_RXINT_RCMDSTA_OO |
		      PAS_DMA_RXINT_RCMDSTA_BT))
		prपूर्णांकk(KERN_DEBUG "pasemi_mac: rcmdsta error: 0x%08x\n", sta);

	sta = पढ़ो_dma_reg(PAS_DMA_RXCHAN_CCMDSTA(rxch));
	अगर (sta & (PAS_DMA_RXCHAN_CCMDSTA_DU |
		     PAS_DMA_RXCHAN_CCMDSTA_OD |
		     PAS_DMA_RXCHAN_CCMDSTA_FD |
		     PAS_DMA_RXCHAN_CCMDSTA_DT))
		prपूर्णांकk(KERN_DEBUG "pasemi_mac: ccmdsta error: 0x%08x\n", sta);

	sta = पढ़ो_dma_reg(PAS_DMA_TXCHAN_TCMDSTA(txch));
	अगर (sta & (PAS_DMA_TXCHAN_TCMDSTA_SZ | PAS_DMA_TXCHAN_TCMDSTA_DB |
		      PAS_DMA_TXCHAN_TCMDSTA_DE | PAS_DMA_TXCHAN_TCMDSTA_DA))
		prपूर्णांकk(KERN_DEBUG "pasemi_mac: tcmdsta error: 0x%08x\n", sta);

	/* Clean out any pending buffers */
	pasemi_mac_clean_tx(tx_ring(mac));
	pasemi_mac_clean_rx(rx_ring(mac), RX_RING_SIZE);

	pasemi_mac_छोड़ो_txchan(mac);
	pasemi_mac_छोड़ो_rxपूर्णांक(mac);
	pasemi_mac_छोड़ो_rxchan(mac);
	pasemi_mac_पूर्णांकf_disable(mac);

	मुक्त_irq(mac->tx->chan.irq, mac->tx);
	मुक्त_irq(mac->rx->chan.irq, mac->rx);

	क्रम (i = 0; i < mac->num_cs; i++) अणु
		pasemi_mac_मुक्त_csring(mac->cs[i]);
		mac->cs[i] = शून्य;
	पूर्ण

	mac->num_cs = 0;

	/* Free resources */
	pasemi_mac_मुक्त_rx_resources(mac);
	pasemi_mac_मुक्त_tx_resources(mac);

	वापस 0;
पूर्ण

अटल व्योम pasemi_mac_queue_csdesc(स्थिर काष्ठा sk_buff *skb,
				    स्थिर dma_addr_t *map,
				    स्थिर अचिन्हित पूर्णांक *map_size,
				    काष्ठा pasemi_mac_txring *txring,
				    काष्ठा pasemi_mac_csring *csring)
अणु
	u64 fund;
	dma_addr_t cs_dest;
	स्थिर पूर्णांक nh_off = skb_network_offset(skb);
	स्थिर पूर्णांक nh_len = skb_network_header_len(skb);
	स्थिर पूर्णांक nfrags = skb_shinfo(skb)->nr_frags;
	पूर्णांक cs_size, i, fill, hdr, evt;
	dma_addr_t csdma;

	fund = XCT_FUN_ST | XCT_FUN_RR_8BRES |
	       XCT_FUN_O | XCT_FUN_FUN(csring->fun) |
	       XCT_FUN_CRM_SIG | XCT_FUN_LLEN(skb->len - nh_off) |
	       XCT_FUN_SHL(nh_len >> 2) | XCT_FUN_SE;

	चयन (ip_hdr(skb)->protocol) अणु
	हाल IPPROTO_TCP:
		fund |= XCT_FUN_SIG_TCP4;
		/* TCP checksum is 16 bytes पूर्णांकo the header */
		cs_dest = map[0] + skb_transport_offset(skb) + 16;
		अवरोध;
	हाल IPPROTO_UDP:
		fund |= XCT_FUN_SIG_UDP4;
		/* UDP checksum is 6 bytes पूर्णांकo the header */
		cs_dest = map[0] + skb_transport_offset(skb) + 6;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	/* Do the checksum offloaded */
	fill = csring->next_to_fill;
	hdr = fill;

	CS_DESC(csring, fill++) = fund;
	/* Room क्रम 8BRES. Checksum result is really 2 bytes पूर्णांकo it */
	csdma = csring->chan.ring_dma + (fill & (CS_RING_SIZE-1)) * 8 + 2;
	CS_DESC(csring, fill++) = 0;

	CS_DESC(csring, fill) = XCT_PTR_LEN(map_size[0]-nh_off) | XCT_PTR_ADDR(map[0]+nh_off);
	क्रम (i = 1; i <= nfrags; i++)
		CS_DESC(csring, fill+i) = XCT_PTR_LEN(map_size[i]) | XCT_PTR_ADDR(map[i]);

	fill += i;
	अगर (fill & 1)
		fill++;

	/* Copy the result पूर्णांकo the TCP packet */
	CS_DESC(csring, fill++) = XCT_FUN_O | XCT_FUN_FUN(csring->fun) |
				  XCT_FUN_LLEN(2) | XCT_FUN_SE;
	CS_DESC(csring, fill++) = XCT_PTR_LEN(2) | XCT_PTR_ADDR(cs_dest) | XCT_PTR_T;
	CS_DESC(csring, fill++) = XCT_PTR_LEN(2) | XCT_PTR_ADDR(csdma);
	fill++;

	evt = !csring->last_event;
	csring->last_event = evt;

	/* Event handshaking with MAC TX */
	CS_DESC(csring, fill++) = CTRL_CMD_T | CTRL_CMD_META_EVT | CTRL_CMD_O |
				  CTRL_CMD_ETYPE_SET | CTRL_CMD_REG(csring->events[evt]);
	CS_DESC(csring, fill++) = 0;
	CS_DESC(csring, fill++) = CTRL_CMD_T | CTRL_CMD_META_EVT | CTRL_CMD_O |
				  CTRL_CMD_ETYPE_WCLR | CTRL_CMD_REG(csring->events[!evt]);
	CS_DESC(csring, fill++) = 0;
	csring->next_to_fill = fill & (CS_RING_SIZE-1);

	cs_size = fill - hdr;
	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_INCR(csring->chan.chno), (cs_size) >> 1);

	/* TX-side event handshaking */
	fill = txring->next_to_fill;
	TX_DESC(txring, fill++) = CTRL_CMD_T | CTRL_CMD_META_EVT | CTRL_CMD_O |
				  CTRL_CMD_ETYPE_WSET | CTRL_CMD_REG(csring->events[evt]);
	TX_DESC(txring, fill++) = 0;
	TX_DESC(txring, fill++) = CTRL_CMD_T | CTRL_CMD_META_EVT | CTRL_CMD_O |
				  CTRL_CMD_ETYPE_CLR | CTRL_CMD_REG(csring->events[!evt]);
	TX_DESC(txring, fill++) = 0;
	txring->next_to_fill = fill;

	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_INCR(txring->chan.chno), 2);
पूर्ण

अटल पूर्णांक pasemi_mac_start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा pasemi_mac * स्थिर mac = netdev_priv(dev);
	काष्ठा pasemi_mac_txring * स्थिर txring = tx_ring(mac);
	काष्ठा pasemi_mac_csring *csring;
	u64 dflags = 0;
	u64 mactx;
	dma_addr_t map[MAX_SKB_FRAGS+1];
	अचिन्हित पूर्णांक map_size[MAX_SKB_FRAGS+1];
	अचिन्हित दीर्घ flags;
	पूर्णांक i, nfrags;
	पूर्णांक fill;
	स्थिर पूर्णांक nh_off = skb_network_offset(skb);
	स्थिर पूर्णांक nh_len = skb_network_header_len(skb);

	prefetch(&txring->ring_info);

	dflags = XCT_MACTX_O | XCT_MACTX_ST | XCT_MACTX_CRC_PAD;

	nfrags = skb_shinfo(skb)->nr_frags;

	map[0] = pci_map_single(mac->dma_pdev, skb->data, skb_headlen(skb),
				PCI_DMA_TODEVICE);
	map_size[0] = skb_headlen(skb);
	अगर (pci_dma_mapping_error(mac->dma_pdev, map[0]))
		जाओ out_err_nolock;

	क्रम (i = 0; i < nfrags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		map[i + 1] = skb_frag_dma_map(&mac->dma_pdev->dev, frag, 0,
					      skb_frag_size(frag), DMA_TO_DEVICE);
		map_size[i+1] = skb_frag_size(frag);
		अगर (dma_mapping_error(&mac->dma_pdev->dev, map[i + 1])) अणु
			nfrags = i;
			जाओ out_err_nolock;
		पूर्ण
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL && skb->len <= 1540) अणु
		चयन (ip_hdr(skb)->protocol) अणु
		हाल IPPROTO_TCP:
			dflags |= XCT_MACTX_CSUM_TCP;
			dflags |= XCT_MACTX_IPH(nh_len >> 2);
			dflags |= XCT_MACTX_IPO(nh_off);
			अवरोध;
		हाल IPPROTO_UDP:
			dflags |= XCT_MACTX_CSUM_UDP;
			dflags |= XCT_MACTX_IPH(nh_len >> 2);
			dflags |= XCT_MACTX_IPO(nh_off);
			अवरोध;
		शेष:
			WARN_ON(1);
		पूर्ण
	पूर्ण

	mactx = dflags | XCT_MACTX_LLEN(skb->len);

	spin_lock_irqsave(&txring->lock, flags);

	/* Aव्योम stepping on the same cache line that the DMA controller
	 * is currently about to send, so leave at least 8 words available.
	 * Total मुक्त space needed is mactx + fragments + 8
	 */
	अगर (RING_AVAIL(txring) < nfrags + 14) अणु
		/* no room -- stop the queue and रुको क्रम tx पूर्णांकr */
		netअगर_stop_queue(dev);
		जाओ out_err;
	पूर्ण

	/* Queue up checksum + event descriptors, अगर needed */
	अगर (mac->num_cs && skb->ip_summed == CHECKSUM_PARTIAL && skb->len > 1540) अणु
		csring = mac->cs[mac->last_cs];
		mac->last_cs = (mac->last_cs + 1) % mac->num_cs;

		pasemi_mac_queue_csdesc(skb, map, map_size, txring, csring);
	पूर्ण

	fill = txring->next_to_fill;
	TX_DESC(txring, fill) = mactx;
	TX_DESC_INFO(txring, fill).dma = nfrags;
	fill++;
	TX_DESC_INFO(txring, fill).skb = skb;
	क्रम (i = 0; i <= nfrags; i++) अणु
		TX_DESC(txring, fill+i) =
			XCT_PTR_LEN(map_size[i]) | XCT_PTR_ADDR(map[i]);
		TX_DESC_INFO(txring, fill+i).dma = map[i];
	पूर्ण

	/* We have to add an even number of 8-byte entries to the ring
	 * even अगर the last one is unused. That means always an odd number
	 * of poपूर्णांकers + one mactx descriptor.
	 */
	अगर (nfrags & 1)
		nfrags++;

	txring->next_to_fill = (fill + nfrags + 1) & (TX_RING_SIZE-1);

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	spin_unlock_irqrestore(&txring->lock, flags);

	ग_लिखो_dma_reg(PAS_DMA_TXCHAN_INCR(txring->chan.chno), (nfrags+2) >> 1);

	वापस NETDEV_TX_OK;

out_err:
	spin_unlock_irqrestore(&txring->lock, flags);
out_err_nolock:
	जबतक (nfrags--)
		pci_unmap_single(mac->dma_pdev, map[nfrags], map_size[nfrags],
				 PCI_DMA_TODEVICE);

	वापस NETDEV_TX_BUSY;
पूर्ण

अटल व्योम pasemi_mac_set_rx_mode(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा pasemi_mac *mac = netdev_priv(dev);
	अचिन्हित पूर्णांक flags;

	flags = पढ़ो_mac_reg(mac, PAS_MAC_CFG_PCFG);

	/* Set promiscuous */
	अगर (dev->flags & IFF_PROMISC)
		flags |= PAS_MAC_CFG_PCFG_PR;
	अन्यथा
		flags &= ~PAS_MAC_CFG_PCFG_PR;

	ग_लिखो_mac_reg(mac, PAS_MAC_CFG_PCFG, flags);
पूर्ण


अटल पूर्णांक pasemi_mac_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा pasemi_mac *mac = container_of(napi, काष्ठा pasemi_mac, napi);
	पूर्णांक pkts;

	pasemi_mac_clean_tx(tx_ring(mac));
	pkts = pasemi_mac_clean_rx(rx_ring(mac), budget);
	अगर (pkts < budget) अणु
		/* all करोne, no more packets present */
		napi_complete_करोne(napi, pkts);

		pasemi_mac_restart_rx_पूर्णांकr(mac);
		pasemi_mac_restart_tx_पूर्णांकr(mac);
	पूर्ण
	वापस pkts;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
 */
अटल व्योम pasemi_mac_netpoll(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा pasemi_mac *mac = netdev_priv(dev);

	disable_irq(mac->tx->chan.irq);
	pasemi_mac_tx_पूर्णांकr(mac->tx->chan.irq, mac->tx);
	enable_irq(mac->tx->chan.irq);

	disable_irq(mac->rx->chan.irq);
	pasemi_mac_rx_पूर्णांकr(mac->rx->chan.irq, mac->rx);
	enable_irq(mac->rx->chan.irq);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pasemi_mac_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(dev);
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक rcmdsta = 0;
	पूर्णांक running;
	पूर्णांक ret = 0;

	running = netअगर_running(dev);

	अगर (running) अणु
		/* Need to stop the पूर्णांकerface, clean out all alपढ़ोy
		 * received buffers, मुक्त all unused buffers on the RX
		 * पूर्णांकerface ring, then finally re-fill the rx ring with
		 * the new-size buffers and restart.
		 */

		napi_disable(&mac->napi);
		netअगर_tx_disable(dev);
		pasemi_mac_पूर्णांकf_disable(mac);

		rcmdsta = पढ़ो_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_अगर));
		pasemi_mac_छोड़ो_rxपूर्णांक(mac);
		pasemi_mac_clean_rx(rx_ring(mac), RX_RING_SIZE);
		pasemi_mac_मुक्त_rx_buffers(mac);

	पूर्ण

	/* Setup checksum channels अगर large MTU and none alपढ़ोy allocated */
	अगर (new_mtu > PE_DEF_MTU && !mac->num_cs) अणु
		pasemi_mac_setup_csrings(mac);
		अगर (!mac->num_cs) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Change maxf, i.e. what size frames are accepted.
	 * Need room क्रम ethernet header and CRC word
	 */
	reg = पढ़ो_mac_reg(mac, PAS_MAC_CFG_MACCFG);
	reg &= ~PAS_MAC_CFG_MACCFG_MAXF_M;
	reg |= PAS_MAC_CFG_MACCFG_MAXF(new_mtu + ETH_HLEN + 4);
	ग_लिखो_mac_reg(mac, PAS_MAC_CFG_MACCFG, reg);

	dev->mtu = new_mtu;
	/* MTU + ETH_HLEN + VLAN_HLEN + 2 64B cachelines */
	mac->bufsz = new_mtu + ETH_HLEN + ETH_FCS_LEN + LOCAL_SKB_ALIGN + 128;

out:
	अगर (running) अणु
		ग_लिखो_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_अगर),
			      rcmdsta | PAS_DMA_RXINT_RCMDSTA_EN);

		rx_ring(mac)->next_to_fill = 0;
		pasemi_mac_replenish_rx_ring(dev, RX_RING_SIZE-1);

		napi_enable(&mac->napi);
		netअगर_start_queue(dev);
		pasemi_mac_पूर्णांकf_enable(mac);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops pasemi_netdev_ops = अणु
	.nकरो_खोलो		= pasemi_mac_खोलो,
	.nकरो_stop		= pasemi_mac_बंद,
	.nकरो_start_xmit		= pasemi_mac_start_tx,
	.nकरो_set_rx_mode	= pasemi_mac_set_rx_mode,
	.nकरो_set_mac_address	= pasemi_mac_set_mac_addr,
	.nकरो_change_mtu		= pasemi_mac_change_mtu,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= pasemi_mac_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक
pasemi_mac_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा pasemi_mac *mac;
	पूर्णांक err, ret;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	dev = alloc_etherdev(माप(काष्ठा pasemi_mac));
	अगर (dev == शून्य) अणु
		err = -ENOMEM;
		जाओ out_disable_device;
	पूर्ण

	pci_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	mac = netdev_priv(dev);

	mac->pdev = pdev;
	mac->netdev = dev;

	netअगर_napi_add(dev, &mac->napi, pasemi_mac_poll, 64);

	dev->features = NETIF_F_IP_CSUM | NETIF_F_LLTX | NETIF_F_SG |
			NETIF_F_HIGHDMA | NETIF_F_GSO;

	mac->dma_pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa007, शून्य);
	अगर (!mac->dma_pdev) अणु
		dev_err(&mac->pdev->dev, "Can't find DMA Controller\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण
	dma_set_mask(&mac->dma_pdev->dev, DMA_BIT_MASK(64));

	mac->iob_pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa001, शून्य);
	अगर (!mac->iob_pdev) अणु
		dev_err(&mac->pdev->dev, "Can't find I/O Bridge\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण

	/* get mac addr from device tree */
	अगर (pasemi_get_mac_addr(mac) || !is_valid_ether_addr(mac->mac_addr)) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण
	स_नकल(dev->dev_addr, mac->mac_addr, माप(mac->mac_addr));

	ret = mac_to_पूर्णांकf(mac);
	अगर (ret < 0) अणु
		dev_err(&mac->pdev->dev, "Can't map DMA interface\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण
	mac->dma_अगर = ret;

	चयन (pdev->device) अणु
	हाल 0xa005:
		mac->type = MAC_TYPE_GMAC;
		अवरोध;
	हाल 0xa006:
		mac->type = MAC_TYPE_XAUI;
		अवरोध;
	शेष:
		err = -ENODEV;
		जाओ out;
	पूर्ण

	dev->netdev_ops = &pasemi_netdev_ops;
	dev->mtu = PE_DEF_MTU;

	/* MTU range: 64 - 9000 */
	dev->min_mtu = PE_MIN_MTU;
	dev->max_mtu = PE_MAX_MTU;

	/* 1500 MTU + ETH_HLEN + VLAN_HLEN + 2 64B cachelines */
	mac->bufsz = dev->mtu + ETH_HLEN + ETH_FCS_LEN + LOCAL_SKB_ALIGN + 128;

	dev->ethtool_ops = &pasemi_mac_ethtool_ops;

	अगर (err)
		जाओ out;

	mac->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

	/* Enable most messages by शेष */
	mac->msg_enable = (NETIF_MSG_IFUP << 1 ) - 1;

	err = रेजिस्टर_netdev(dev);

	अगर (err) अणु
		dev_err(&mac->pdev->dev, "register_netdev failed with error %d\n",
			err);
		जाओ out;
	पूर्ण अन्यथा अगर (netअगर_msg_probe(mac)) अणु
		prपूर्णांकk(KERN_INFO "%s: PA Semi %s: intf %d, hw addr %pM\n",
		       dev->name, mac->type == MAC_TYPE_GMAC ? "GMAC" : "XAUI",
		       mac->dma_अगर, dev->dev_addr);
	पूर्ण

	वापस err;

out:
	pci_dev_put(mac->iob_pdev);
	pci_dev_put(mac->dma_pdev);

	मुक्त_netdev(dev);
out_disable_device:
	pci_disable_device(pdev);
	वापस err;

पूर्ण

अटल व्योम pasemi_mac_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा pasemi_mac *mac;

	अगर (!netdev)
		वापस;

	mac = netdev_priv(netdev);

	unरेजिस्टर_netdev(netdev);

	pci_disable_device(pdev);
	pci_dev_put(mac->dma_pdev);
	pci_dev_put(mac->iob_pdev);

	pasemi_dma_मुक्त_chan(&mac->tx->chan);
	pasemi_dma_मुक्त_chan(&mac->rx->chan);

	मुक्त_netdev(netdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pasemi_mac_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_PASEMI, 0xa005) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_PASEMI, 0xa006) पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, pasemi_mac_pci_tbl);

अटल काष्ठा pci_driver pasemi_mac_driver = अणु
	.name		= "pasemi_mac",
	.id_table	= pasemi_mac_pci_tbl,
	.probe		= pasemi_mac_probe,
	.हटाओ		= pasemi_mac_हटाओ,
पूर्ण;

अटल व्योम __निकास pasemi_mac_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pasemi_mac_driver);
पूर्ण

अटल पूर्णांक pasemi_mac_init_module(व्योम)
अणु
	पूर्णांक err;

	err = pasemi_dma_init();
	अगर (err)
		वापस err;

	वापस pci_रेजिस्टर_driver(&pasemi_mac_driver);
पूर्ण

module_init(pasemi_mac_init_module);
module_निकास(pasemi_mac_cleanup_module);
