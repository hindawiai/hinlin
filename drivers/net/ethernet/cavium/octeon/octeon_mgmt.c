<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2009-2012 Cavium, Inc
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/capability.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_net.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/phy.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-mixx-defs.h>
#समावेश <यंत्र/octeon/cvmx-agl-defs.h>

#घोषणा DRV_NAME "octeon_mgmt"
#घोषणा DRV_DESCRIPTION \
	"Cavium Networks Octeon MII (management) port Network Driver"

#घोषणा OCTEON_MGMT_NAPI_WEIGHT 16

/* Ring sizes that are घातers of two allow क्रम more efficient modulo
 * opertions.
 */
#घोषणा OCTEON_MGMT_RX_RING_SIZE 512
#घोषणा OCTEON_MGMT_TX_RING_SIZE 128

/* Allow 8 bytes क्रम vlan and FCS. */
#घोषणा OCTEON_MGMT_RX_HEADROOM (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN)

जोड़ mgmt_port_ring_entry अणु
	u64 d64;
	काष्ठा अणु
#घोषणा RING_ENTRY_CODE_DONE 0xf
#घोषणा RING_ENTRY_CODE_MORE 0x10
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		u64 reserved_62_63:2;
		/* Length of the buffer/packet in bytes */
		u64 len:14;
		/* For TX, संकेतs that the packet should be बारtamped */
		u64 tstamp:1;
		/* The RX error code */
		u64 code:7;
		/* Physical address of the buffer */
		u64 addr:40;
#अन्यथा
		u64 addr:40;
		u64 code:7;
		u64 tstamp:1;
		u64 len:14;
		u64 reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा MIX_ORING1	0x0
#घोषणा MIX_ORING2	0x8
#घोषणा MIX_IRING1	0x10
#घोषणा MIX_IRING2	0x18
#घोषणा MIX_CTL		0x20
#घोषणा MIX_IRHWM	0x28
#घोषणा MIX_IRCNT	0x30
#घोषणा MIX_ORHWM	0x38
#घोषणा MIX_ORCNT	0x40
#घोषणा MIX_ISR		0x48
#घोषणा MIX_INTENA	0x50
#घोषणा MIX_REMCNT	0x58
#घोषणा MIX_BIST	0x78

#घोषणा AGL_GMX_PRT_CFG			0x10
#घोषणा AGL_GMX_RX_FRM_CTL		0x18
#घोषणा AGL_GMX_RX_FRM_MAX		0x30
#घोषणा AGL_GMX_RX_JABBER		0x38
#घोषणा AGL_GMX_RX_STATS_CTL		0x50

#घोषणा AGL_GMX_RX_STATS_PKTS_DRP	0xb0
#घोषणा AGL_GMX_RX_STATS_OCTS_DRP	0xb8
#घोषणा AGL_GMX_RX_STATS_PKTS_BAD	0xc0

#घोषणा AGL_GMX_RX_ADR_CTL		0x100
#घोषणा AGL_GMX_RX_ADR_CAM_EN		0x108
#घोषणा AGL_GMX_RX_ADR_CAM0		0x180
#घोषणा AGL_GMX_RX_ADR_CAM1		0x188
#घोषणा AGL_GMX_RX_ADR_CAM2		0x190
#घोषणा AGL_GMX_RX_ADR_CAM3		0x198
#घोषणा AGL_GMX_RX_ADR_CAM4		0x1a0
#घोषणा AGL_GMX_RX_ADR_CAM5		0x1a8

#घोषणा AGL_GMX_TX_CLK			0x208
#घोषणा AGL_GMX_TX_STATS_CTL		0x268
#घोषणा AGL_GMX_TX_CTL			0x270
#घोषणा AGL_GMX_TX_STAT0		0x280
#घोषणा AGL_GMX_TX_STAT1		0x288
#घोषणा AGL_GMX_TX_STAT2		0x290
#घोषणा AGL_GMX_TX_STAT3		0x298
#घोषणा AGL_GMX_TX_STAT4		0x2a0
#घोषणा AGL_GMX_TX_STAT5		0x2a8
#घोषणा AGL_GMX_TX_STAT6		0x2b0
#घोषणा AGL_GMX_TX_STAT7		0x2b8
#घोषणा AGL_GMX_TX_STAT8		0x2c0
#घोषणा AGL_GMX_TX_STAT9		0x2c8

काष्ठा octeon_mgmt अणु
	काष्ठा net_device *netdev;
	u64 mix;
	u64 agl;
	u64 agl_prt_ctl;
	पूर्णांक port;
	पूर्णांक irq;
	bool has_rx_tstamp;
	u64 *tx_ring;
	dma_addr_t tx_ring_handle;
	अचिन्हित पूर्णांक tx_next;
	अचिन्हित पूर्णांक tx_next_clean;
	अचिन्हित पूर्णांक tx_current_fill;
	/* The tx_list lock also protects the ring related variables */
	काष्ठा sk_buff_head tx_list;

	/* RX variables only touched in napi_poll.  No locking necessary. */
	u64 *rx_ring;
	dma_addr_t rx_ring_handle;
	अचिन्हित पूर्णांक rx_next;
	अचिन्हित पूर्णांक rx_next_fill;
	अचिन्हित पूर्णांक rx_current_fill;
	काष्ठा sk_buff_head rx_list;

	spinlock_t lock;
	अचिन्हित पूर्णांक last_duplex;
	अचिन्हित पूर्णांक last_link;
	अचिन्हित पूर्णांक last_speed;
	काष्ठा device *dev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा tasklet_काष्ठा tx_clean_tasklet;
	काष्ठा device_node *phy_np;
	resource_माप_प्रकार mix_phys;
	resource_माप_प्रकार mix_size;
	resource_माप_प्रकार agl_phys;
	resource_माप_प्रकार agl_size;
	resource_माप_प्रकार agl_prt_ctl_phys;
	resource_माप_प्रकार agl_prt_ctl_size;
पूर्ण;

अटल व्योम octeon_mgmt_set_rx_irq(काष्ठा octeon_mgmt *p, पूर्णांक enable)
अणु
	जोड़ cvmx_mixx_पूर्णांकena mix_पूर्णांकena;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&p->lock, flags);
	mix_पूर्णांकena.u64 = cvmx_पढ़ो_csr(p->mix + MIX_INTENA);
	mix_पूर्णांकena.s.ithena = enable ? 1 : 0;
	cvmx_ग_लिखो_csr(p->mix + MIX_INTENA, mix_पूर्णांकena.u64);
	spin_unlock_irqrestore(&p->lock, flags);
पूर्ण

अटल व्योम octeon_mgmt_set_tx_irq(काष्ठा octeon_mgmt *p, पूर्णांक enable)
अणु
	जोड़ cvmx_mixx_पूर्णांकena mix_पूर्णांकena;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&p->lock, flags);
	mix_पूर्णांकena.u64 = cvmx_पढ़ो_csr(p->mix + MIX_INTENA);
	mix_पूर्णांकena.s.othena = enable ? 1 : 0;
	cvmx_ग_लिखो_csr(p->mix + MIX_INTENA, mix_पूर्णांकena.u64);
	spin_unlock_irqrestore(&p->lock, flags);
पूर्ण

अटल व्योम octeon_mgmt_enable_rx_irq(काष्ठा octeon_mgmt *p)
अणु
	octeon_mgmt_set_rx_irq(p, 1);
पूर्ण

अटल व्योम octeon_mgmt_disable_rx_irq(काष्ठा octeon_mgmt *p)
अणु
	octeon_mgmt_set_rx_irq(p, 0);
पूर्ण

अटल व्योम octeon_mgmt_enable_tx_irq(काष्ठा octeon_mgmt *p)
अणु
	octeon_mgmt_set_tx_irq(p, 1);
पूर्ण

अटल व्योम octeon_mgmt_disable_tx_irq(काष्ठा octeon_mgmt *p)
अणु
	octeon_mgmt_set_tx_irq(p, 0);
पूर्ण

अटल अचिन्हित पूर्णांक ring_max_fill(अचिन्हित पूर्णांक ring_size)
अणु
	वापस ring_size - 8;
पूर्ण

अटल अचिन्हित पूर्णांक ring_माप_प्रकारo_bytes(अचिन्हित पूर्णांक ring_size)
अणु
	वापस ring_size * माप(जोड़ mgmt_port_ring_entry);
पूर्ण

अटल व्योम octeon_mgmt_rx_fill_ring(काष्ठा net_device *netdev)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);

	जबतक (p->rx_current_fill < ring_max_fill(OCTEON_MGMT_RX_RING_SIZE)) अणु
		अचिन्हित पूर्णांक size;
		जोड़ mgmt_port_ring_entry re;
		काष्ठा sk_buff *skb;

		/* CN56XX pass 1 needs 8 bytes of padding.  */
		size = netdev->mtu + OCTEON_MGMT_RX_HEADROOM + 8 + NET_IP_ALIGN;

		skb = netdev_alloc_skb(netdev, size);
		अगर (!skb)
			अवरोध;
		skb_reserve(skb, NET_IP_ALIGN);
		__skb_queue_tail(&p->rx_list, skb);

		re.d64 = 0;
		re.s.len = size;
		re.s.addr = dma_map_single(p->dev, skb->data,
					   size,
					   DMA_FROM_DEVICE);

		/* Put it in the ring.  */
		p->rx_ring[p->rx_next_fill] = re.d64;
		/* Make sure there is no reorder of filling the ring and ringing
		 * the bell
		 */
		wmb();

		dma_sync_single_क्रम_device(p->dev, p->rx_ring_handle,
					   ring_माप_प्रकारo_bytes(OCTEON_MGMT_RX_RING_SIZE),
					   DMA_BIसूचीECTIONAL);
		p->rx_next_fill =
			(p->rx_next_fill + 1) % OCTEON_MGMT_RX_RING_SIZE;
		p->rx_current_fill++;
		/* Ring the bell.  */
		cvmx_ग_लिखो_csr(p->mix + MIX_IRING2, 1);
	पूर्ण
पूर्ण

अटल व्योम octeon_mgmt_clean_tx_buffers(काष्ठा octeon_mgmt *p)
अणु
	जोड़ cvmx_mixx_orcnt mix_orcnt;
	जोड़ mgmt_port_ring_entry re;
	काष्ठा sk_buff *skb;
	पूर्णांक cleaned = 0;
	अचिन्हित दीर्घ flags;

	mix_orcnt.u64 = cvmx_पढ़ो_csr(p->mix + MIX_ORCNT);
	जबतक (mix_orcnt.s.orcnt) अणु
		spin_lock_irqsave(&p->tx_list.lock, flags);

		mix_orcnt.u64 = cvmx_पढ़ो_csr(p->mix + MIX_ORCNT);

		अगर (mix_orcnt.s.orcnt == 0) अणु
			spin_unlock_irqrestore(&p->tx_list.lock, flags);
			अवरोध;
		पूर्ण

		dma_sync_single_क्रम_cpu(p->dev, p->tx_ring_handle,
					ring_माप_प्रकारo_bytes(OCTEON_MGMT_TX_RING_SIZE),
					DMA_BIसूचीECTIONAL);

		re.d64 = p->tx_ring[p->tx_next_clean];
		p->tx_next_clean =
			(p->tx_next_clean + 1) % OCTEON_MGMT_TX_RING_SIZE;
		skb = __skb_dequeue(&p->tx_list);

		mix_orcnt.u64 = 0;
		mix_orcnt.s.orcnt = 1;

		/* Acknowledge to hardware that we have the buffer.  */
		cvmx_ग_लिखो_csr(p->mix + MIX_ORCNT, mix_orcnt.u64);
		p->tx_current_fill--;

		spin_unlock_irqrestore(&p->tx_list.lock, flags);

		dma_unmap_single(p->dev, re.s.addr, re.s.len,
				 DMA_TO_DEVICE);

		/* Read the hardware TX बारtamp अगर one was recorded */
		अगर (unlikely(re.s.tstamp)) अणु
			काष्ठा skb_shared_hwtstamps ts;
			u64 ns;

			स_रखो(&ts, 0, माप(ts));
			/* Read the बारtamp */
			ns = cvmx_पढ़ो_csr(CVMX_MIXX_TSTAMP(p->port));
			/* Remove the बारtamp from the FIFO */
			cvmx_ग_लिखो_csr(CVMX_MIXX_TSCTL(p->port), 0);
			/* Tell the kernel about the बारtamp */
			ts.hwtstamp = ns_to_kसमय(ns);
			skb_tstamp_tx(skb, &ts);
		पूर्ण

		dev_kमुक्त_skb_any(skb);
		cleaned++;

		mix_orcnt.u64 = cvmx_पढ़ो_csr(p->mix + MIX_ORCNT);
	पूर्ण

	अगर (cleaned && netअगर_queue_stopped(p->netdev))
		netअगर_wake_queue(p->netdev);
पूर्ण

अटल व्योम octeon_mgmt_clean_tx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा octeon_mgmt *p = from_tasklet(p, t, tx_clean_tasklet);
	octeon_mgmt_clean_tx_buffers(p);
	octeon_mgmt_enable_tx_irq(p);
पूर्ण

अटल व्योम octeon_mgmt_update_rx_stats(काष्ठा net_device *netdev)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	u64 drop, bad;

	/* These पढ़ोs also clear the count रेजिस्टरs.  */
	drop = cvmx_पढ़ो_csr(p->agl + AGL_GMX_RX_STATS_PKTS_DRP);
	bad = cvmx_पढ़ो_csr(p->agl + AGL_GMX_RX_STATS_PKTS_BAD);

	अगर (drop || bad) अणु
		/* Do an atomic update. */
		spin_lock_irqsave(&p->lock, flags);
		netdev->stats.rx_errors += bad;
		netdev->stats.rx_dropped += drop;
		spin_unlock_irqrestore(&p->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम octeon_mgmt_update_tx_stats(काष्ठा net_device *netdev)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	जोड़ cvmx_agl_gmx_txx_stat0 s0;
	जोड़ cvmx_agl_gmx_txx_stat1 s1;

	/* These पढ़ोs also clear the count रेजिस्टरs.  */
	s0.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_TX_STAT0);
	s1.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_TX_STAT1);

	अगर (s0.s.xsdef || s0.s.xscol || s1.s.scol || s1.s.mcol) अणु
		/* Do an atomic update. */
		spin_lock_irqsave(&p->lock, flags);
		netdev->stats.tx_errors += s0.s.xsdef + s0.s.xscol;
		netdev->stats.collisions += s1.s.scol + s1.s.mcol;
		spin_unlock_irqrestore(&p->lock, flags);
	पूर्ण
पूर्ण

/*
 * Dequeue a receive skb and its corresponding ring entry.  The ring
 * entry is वापसed, *pskb is updated to poपूर्णांक to the skb.
 */
अटल u64 octeon_mgmt_dequeue_rx_buffer(काष्ठा octeon_mgmt *p,
					 काष्ठा sk_buff **pskb)
अणु
	जोड़ mgmt_port_ring_entry re;

	dma_sync_single_क्रम_cpu(p->dev, p->rx_ring_handle,
				ring_माप_प्रकारo_bytes(OCTEON_MGMT_RX_RING_SIZE),
				DMA_BIसूचीECTIONAL);

	re.d64 = p->rx_ring[p->rx_next];
	p->rx_next = (p->rx_next + 1) % OCTEON_MGMT_RX_RING_SIZE;
	p->rx_current_fill--;
	*pskb = __skb_dequeue(&p->rx_list);

	dma_unmap_single(p->dev, re.s.addr,
			 ETH_FRAME_LEN + OCTEON_MGMT_RX_HEADROOM,
			 DMA_FROM_DEVICE);

	वापस re.d64;
पूर्ण


अटल पूर्णांक octeon_mgmt_receive_one(काष्ठा octeon_mgmt *p)
अणु
	काष्ठा net_device *netdev = p->netdev;
	जोड़ cvmx_mixx_ircnt mix_ircnt;
	जोड़ mgmt_port_ring_entry re;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *skb2;
	काष्ठा sk_buff *skb_new;
	जोड़ mgmt_port_ring_entry re2;
	पूर्णांक rc = 1;


	re.d64 = octeon_mgmt_dequeue_rx_buffer(p, &skb);
	अगर (likely(re.s.code == RING_ENTRY_CODE_DONE)) अणु
		/* A good packet, send it up. */
		skb_put(skb, re.s.len);
good:
		/* Process the RX बारtamp अगर it was recorded */
		अगर (p->has_rx_tstamp) अणु
			/* The first 8 bytes are the बारtamp */
			u64 ns = *(u64 *)skb->data;
			काष्ठा skb_shared_hwtstamps *ts;
			ts = skb_hwtstamps(skb);
			ts->hwtstamp = ns_to_kसमय(ns);
			__skb_pull(skb, 8);
		पूर्ण
		skb->protocol = eth_type_trans(skb, netdev);
		netdev->stats.rx_packets++;
		netdev->stats.rx_bytes += skb->len;
		netअगर_receive_skb(skb);
		rc = 0;
	पूर्ण अन्यथा अगर (re.s.code == RING_ENTRY_CODE_MORE) अणु
		/* Packet split across skbs.  This can happen अगर we
		 * increase the MTU.  Buffers that are alपढ़ोy in the
		 * rx ring can then end up being too small.  As the rx
		 * ring is refilled, buffers sized क्रम the new MTU
		 * will be used and we should go back to the normal
		 * non-split हाल.
		 */
		skb_put(skb, re.s.len);
		करो अणु
			re2.d64 = octeon_mgmt_dequeue_rx_buffer(p, &skb2);
			अगर (re2.s.code != RING_ENTRY_CODE_MORE
				&& re2.s.code != RING_ENTRY_CODE_DONE)
				जाओ split_error;
			skb_put(skb2,  re2.s.len);
			skb_new = skb_copy_expand(skb, 0, skb2->len,
						  GFP_ATOMIC);
			अगर (!skb_new)
				जाओ split_error;
			अगर (skb_copy_bits(skb2, 0, skb_tail_poपूर्णांकer(skb_new),
					  skb2->len))
				जाओ split_error;
			skb_put(skb_new, skb2->len);
			dev_kमुक्त_skb_any(skb);
			dev_kमुक्त_skb_any(skb2);
			skb = skb_new;
		पूर्ण जबतक (re2.s.code == RING_ENTRY_CODE_MORE);
		जाओ good;
	पूर्ण अन्यथा अणु
		/* Some other error, discard it. */
		dev_kमुक्त_skb_any(skb);
		/* Error statistics are accumulated in
		 * octeon_mgmt_update_rx_stats.
		 */
	पूर्ण
	जाओ करोne;
split_error:
	/* Discard the whole mess. */
	dev_kमुक्त_skb_any(skb);
	dev_kमुक्त_skb_any(skb2);
	जबतक (re2.s.code == RING_ENTRY_CODE_MORE) अणु
		re2.d64 = octeon_mgmt_dequeue_rx_buffer(p, &skb2);
		dev_kमुक्त_skb_any(skb2);
	पूर्ण
	netdev->stats.rx_errors++;

करोne:
	/* Tell the hardware we processed a packet.  */
	mix_ircnt.u64 = 0;
	mix_ircnt.s.ircnt = 1;
	cvmx_ग_लिखो_csr(p->mix + MIX_IRCNT, mix_ircnt.u64);
	वापस rc;
पूर्ण

अटल पूर्णांक octeon_mgmt_receive_packets(काष्ठा octeon_mgmt *p, पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक work_करोne = 0;
	जोड़ cvmx_mixx_ircnt mix_ircnt;
	पूर्णांक rc;

	mix_ircnt.u64 = cvmx_पढ़ो_csr(p->mix + MIX_IRCNT);
	जबतक (work_करोne < budget && mix_ircnt.s.ircnt) अणु

		rc = octeon_mgmt_receive_one(p);
		अगर (!rc)
			work_करोne++;

		/* Check क्रम more packets. */
		mix_ircnt.u64 = cvmx_पढ़ो_csr(p->mix + MIX_IRCNT);
	पूर्ण

	octeon_mgmt_rx_fill_ring(p->netdev);

	वापस work_करोne;
पूर्ण

अटल पूर्णांक octeon_mgmt_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा octeon_mgmt *p = container_of(napi, काष्ठा octeon_mgmt, napi);
	काष्ठा net_device *netdev = p->netdev;
	अचिन्हित पूर्णांक work_करोne = 0;

	work_करोne = octeon_mgmt_receive_packets(p, budget);

	अगर (work_करोne < budget) अणु
		/* We stopped because no more packets were available. */
		napi_complete_करोne(napi, work_करोne);
		octeon_mgmt_enable_rx_irq(p);
	पूर्ण
	octeon_mgmt_update_rx_stats(netdev);

	वापस work_करोne;
पूर्ण

/* Reset the hardware to clean state.  */
अटल व्योम octeon_mgmt_reset_hw(काष्ठा octeon_mgmt *p)
अणु
	जोड़ cvmx_mixx_ctl mix_ctl;
	जोड़ cvmx_mixx_bist mix_bist;
	जोड़ cvmx_agl_gmx_bist agl_gmx_bist;

	mix_ctl.u64 = 0;
	cvmx_ग_लिखो_csr(p->mix + MIX_CTL, mix_ctl.u64);
	करो अणु
		mix_ctl.u64 = cvmx_पढ़ो_csr(p->mix + MIX_CTL);
	पूर्ण जबतक (mix_ctl.s.busy);
	mix_ctl.s.reset = 1;
	cvmx_ग_लिखो_csr(p->mix + MIX_CTL, mix_ctl.u64);
	cvmx_पढ़ो_csr(p->mix + MIX_CTL);
	octeon_io_clk_delay(64);

	mix_bist.u64 = cvmx_पढ़ो_csr(p->mix + MIX_BIST);
	अगर (mix_bist.u64)
		dev_warn(p->dev, "MIX failed BIST (0x%016llx)\n",
			(अचिन्हित दीर्घ दीर्घ)mix_bist.u64);

	agl_gmx_bist.u64 = cvmx_पढ़ो_csr(CVMX_AGL_GMX_BIST);
	अगर (agl_gmx_bist.u64)
		dev_warn(p->dev, "AGL failed BIST (0x%016llx)\n",
			 (अचिन्हित दीर्घ दीर्घ)agl_gmx_bist.u64);
पूर्ण

काष्ठा octeon_mgmt_cam_state अणु
	u64 cam[6];
	u64 cam_mask;
	पूर्णांक cam_index;
पूर्ण;

अटल व्योम octeon_mgmt_cam_state_add(काष्ठा octeon_mgmt_cam_state *cs,
				      अचिन्हित अक्षर *addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++)
		cs->cam[i] |= (u64)addr[i] << (8 * (cs->cam_index));
	cs->cam_mask |= (1ULL << cs->cam_index);
	cs->cam_index++;
पूर्ण

अटल व्योम octeon_mgmt_set_rx_filtering(काष्ठा net_device *netdev)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);
	जोड़ cvmx_agl_gmx_rxx_adr_ctl adr_ctl;
	जोड़ cvmx_agl_gmx_prtx_cfg agl_gmx_prtx;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक prev_packet_enable;
	अचिन्हित पूर्णांक cam_mode = 1; /* 1 - Accept on CAM match */
	अचिन्हित पूर्णांक multicast_mode = 1; /* 1 - Reject all multicast.  */
	काष्ठा octeon_mgmt_cam_state cam_state;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक available_cam_entries;

	स_रखो(&cam_state, 0, माप(cam_state));

	अगर ((netdev->flags & IFF_PROMISC) || netdev->uc.count > 7) अणु
		cam_mode = 0;
		available_cam_entries = 8;
	पूर्ण अन्यथा अणु
		/* One CAM entry क्रम the primary address, leaves seven
		 * क्रम the secondary addresses.
		 */
		available_cam_entries = 7 - netdev->uc.count;
	पूर्ण

	अगर (netdev->flags & IFF_MULTICAST) अणु
		अगर (cam_mode == 0 || (netdev->flags & IFF_ALLMULTI) ||
		    netdev_mc_count(netdev) > available_cam_entries)
			multicast_mode = 2; /* 2 - Accept all multicast.  */
		अन्यथा
			multicast_mode = 0; /* 0 - Use CAM.  */
	पूर्ण

	अगर (cam_mode == 1) अणु
		/* Add primary address. */
		octeon_mgmt_cam_state_add(&cam_state, netdev->dev_addr);
		netdev_क्रम_each_uc_addr(ha, netdev)
			octeon_mgmt_cam_state_add(&cam_state, ha->addr);
	पूर्ण
	अगर (multicast_mode == 0) अणु
		netdev_क्रम_each_mc_addr(ha, netdev)
			octeon_mgmt_cam_state_add(&cam_state, ha->addr);
	पूर्ण

	spin_lock_irqsave(&p->lock, flags);

	/* Disable packet I/O. */
	agl_gmx_prtx.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_PRT_CFG);
	prev_packet_enable = agl_gmx_prtx.s.en;
	agl_gmx_prtx.s.en = 0;
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_PRT_CFG, agl_gmx_prtx.u64);

	adr_ctl.u64 = 0;
	adr_ctl.s.cam_mode = cam_mode;
	adr_ctl.s.mcst = multicast_mode;
	adr_ctl.s.bcst = 1;     /* Allow broadcast */

	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_ADR_CTL, adr_ctl.u64);

	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_ADR_CAM0, cam_state.cam[0]);
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_ADR_CAM1, cam_state.cam[1]);
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_ADR_CAM2, cam_state.cam[2]);
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_ADR_CAM3, cam_state.cam[3]);
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_ADR_CAM4, cam_state.cam[4]);
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_ADR_CAM5, cam_state.cam[5]);
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_ADR_CAM_EN, cam_state.cam_mask);

	/* Restore packet I/O. */
	agl_gmx_prtx.s.en = prev_packet_enable;
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_PRT_CFG, agl_gmx_prtx.u64);

	spin_unlock_irqrestore(&p->lock, flags);
पूर्ण

अटल पूर्णांक octeon_mgmt_set_mac_address(काष्ठा net_device *netdev, व्योम *addr)
अणु
	पूर्णांक r = eth_mac_addr(netdev, addr);

	अगर (r)
		वापस r;

	octeon_mgmt_set_rx_filtering(netdev);

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_mgmt_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);
	पूर्णांक max_packet = new_mtu + ETH_HLEN + ETH_FCS_LEN;

	netdev->mtu = new_mtu;

	/* HW lअगरts the limit अगर the frame is VLAN tagged
	 * (+4 bytes per each tag, up to two tags)
	 */
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_FRM_MAX, max_packet);
	/* Set the hardware to truncate packets larger than the MTU. The jabber
	 * रेजिस्टर must be set to a multiple of 8 bytes, so round up. JABBER is
	 * an unconditional limit, so we need to account क्रम two possible VLAN
	 * tags.
	 */
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_JABBER,
		       (max_packet + 7 + VLAN_HLEN * 2) & 0xfff8);

	वापस 0;
पूर्ण

अटल irqवापस_t octeon_mgmt_पूर्णांकerrupt(पूर्णांक cpl, व्योम *dev_id)
अणु
	काष्ठा net_device *netdev = dev_id;
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);
	जोड़ cvmx_mixx_isr mixx_isr;

	mixx_isr.u64 = cvmx_पढ़ो_csr(p->mix + MIX_ISR);

	/* Clear any pending पूर्णांकerrupts */
	cvmx_ग_लिखो_csr(p->mix + MIX_ISR, mixx_isr.u64);
	cvmx_पढ़ो_csr(p->mix + MIX_ISR);

	अगर (mixx_isr.s.irthresh) अणु
		octeon_mgmt_disable_rx_irq(p);
		napi_schedule(&p->napi);
	पूर्ण
	अगर (mixx_isr.s.orthresh) अणु
		octeon_mgmt_disable_tx_irq(p);
		tasklet_schedule(&p->tx_clean_tasklet);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक octeon_mgmt_ioctl_hwtstamp(काष्ठा net_device *netdev,
				      काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);
	काष्ठा hwtstamp_config config;
	जोड़ cvmx_mio_ptp_घड़ी_cfg ptp;
	जोड़ cvmx_agl_gmx_rxx_frm_ctl rxx_frm_ctl;
	bool have_hw_बारtamps = false;

	अगर (copy_from_user(&config, rq->अगरr_data, माप(config)))
		वापस -EFAULT;

	अगर (config.flags) /* reserved क्रम future extensions */
		वापस -EINVAL;

	/* Check the status of hardware क्रम tiemstamps */
	अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX)) अणु
		/* Get the current state of the PTP घड़ी */
		ptp.u64 = cvmx_पढ़ो_csr(CVMX_MIO_PTP_CLOCK_CFG);
		अगर (!ptp.s.ext_clk_en) अणु
			/* The घड़ी has not been configured to use an
			 * बाह्यal source.  Program it to use the मुख्य घड़ी
			 * reference.
			 */
			u64 घड़ी_comp = (NSEC_PER_SEC << 32) /	octeon_get_io_घड़ी_rate();
			अगर (!ptp.s.ptp_en)
				cvmx_ग_लिखो_csr(CVMX_MIO_PTP_CLOCK_COMP, घड़ी_comp);
			netdev_info(netdev,
				    "PTP Clock using sclk reference @ %lldHz\n",
				    (NSEC_PER_SEC << 32) / घड़ी_comp);
		पूर्ण अन्यथा अणु
			/* The घड़ी is alपढ़ोy programmed to use a GPIO */
			u64 घड़ी_comp = cvmx_पढ़ो_csr(CVMX_MIO_PTP_CLOCK_COMP);
			netdev_info(netdev,
				    "PTP Clock using GPIO%d @ %lld Hz\n",
				    ptp.s.ext_clk_in, (NSEC_PER_SEC << 32) / घड़ी_comp);
		पूर्ण

		/* Enable the घड़ी अगर it wasn't करोne alपढ़ोy */
		अगर (!ptp.s.ptp_en) अणु
			ptp.s.ptp_en = 1;
			cvmx_ग_लिखो_csr(CVMX_MIO_PTP_CLOCK_CFG, ptp.u64);
		पूर्ण
		have_hw_बारtamps = true;
	पूर्ण

	अगर (!have_hw_बारtamps)
		वापस -EINVAL;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
	हाल HWTSTAMP_TX_ON:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		p->has_rx_tstamp = false;
		rxx_frm_ctl.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_RX_FRM_CTL);
		rxx_frm_ctl.s.ptp_mode = 0;
		cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_FRM_CTL, rxx_frm_ctl.u64);
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_NTP_ALL:
		p->has_rx_tstamp = have_hw_बारtamps;
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		अगर (p->has_rx_tstamp) अणु
			rxx_frm_ctl.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_RX_FRM_CTL);
			rxx_frm_ctl.s.ptp_mode = 1;
			cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_FRM_CTL, rxx_frm_ctl.u64);
		पूर्ण
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	अगर (copy_to_user(rq->अगरr_data, &config, माप(config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_mgmt_ioctl(काष्ठा net_device *netdev,
			     काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस octeon_mgmt_ioctl_hwtstamp(netdev, rq, cmd);
	शेष:
		वापस phy_करो_ioctl(netdev, rq, cmd);
	पूर्ण
पूर्ण

अटल व्योम octeon_mgmt_disable_link(काष्ठा octeon_mgmt *p)
अणु
	जोड़ cvmx_agl_gmx_prtx_cfg prtx_cfg;

	/* Disable GMX beक्रमe we make any changes. */
	prtx_cfg.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_PRT_CFG);
	prtx_cfg.s.en = 0;
	prtx_cfg.s.tx_en = 0;
	prtx_cfg.s.rx_en = 0;
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_PRT_CFG, prtx_cfg.u64);

	अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX)) अणु
		पूर्णांक i;
		क्रम (i = 0; i < 10; i++) अणु
			prtx_cfg.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_PRT_CFG);
			अगर (prtx_cfg.s.tx_idle == 1 || prtx_cfg.s.rx_idle == 1)
				अवरोध;
			mdelay(1);
			i++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम octeon_mgmt_enable_link(काष्ठा octeon_mgmt *p)
अणु
	जोड़ cvmx_agl_gmx_prtx_cfg prtx_cfg;

	/* Restore the GMX enable state only अगर link is set */
	prtx_cfg.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_PRT_CFG);
	prtx_cfg.s.tx_en = 1;
	prtx_cfg.s.rx_en = 1;
	prtx_cfg.s.en = 1;
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_PRT_CFG, prtx_cfg.u64);
पूर्ण

अटल व्योम octeon_mgmt_update_link(काष्ठा octeon_mgmt *p)
अणु
	काष्ठा net_device *ndev = p->netdev;
	काष्ठा phy_device *phydev = ndev->phydev;
	जोड़ cvmx_agl_gmx_prtx_cfg prtx_cfg;

	prtx_cfg.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_PRT_CFG);

	अगर (!phydev->link)
		prtx_cfg.s.duplex = 1;
	अन्यथा
		prtx_cfg.s.duplex = phydev->duplex;

	चयन (phydev->speed) अणु
	हाल 10:
		prtx_cfg.s.speed = 0;
		prtx_cfg.s.slotसमय = 0;

		अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX)) अणु
			prtx_cfg.s.burst = 1;
			prtx_cfg.s.speed_msb = 1;
		पूर्ण
		अवरोध;
	हाल 100:
		prtx_cfg.s.speed = 0;
		prtx_cfg.s.slotसमय = 0;

		अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX)) अणु
			prtx_cfg.s.burst = 1;
			prtx_cfg.s.speed_msb = 0;
		पूर्ण
		अवरोध;
	हाल 1000:
		/* 1000 MBits is only supported on 6XXX chips */
		अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX)) अणु
			prtx_cfg.s.speed = 1;
			prtx_cfg.s.speed_msb = 0;
			/* Only matters क्रम half-duplex */
			prtx_cfg.s.slotसमय = 1;
			prtx_cfg.s.burst = phydev->duplex;
		पूर्ण
		अवरोध;
	हाल 0:  /* No link */
	शेष:
		अवरोध;
	पूर्ण

	/* Write the new GMX setting with the port still disabled. */
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_PRT_CFG, prtx_cfg.u64);

	/* Read GMX CFG again to make sure the config is completed. */
	prtx_cfg.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_PRT_CFG);

	अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX)) अणु
		जोड़ cvmx_agl_gmx_txx_clk agl_clk;
		जोड़ cvmx_agl_prtx_ctl prtx_ctl;

		prtx_ctl.u64 = cvmx_पढ़ो_csr(p->agl_prt_ctl);
		agl_clk.u64 = cvmx_पढ़ो_csr(p->agl + AGL_GMX_TX_CLK);
		/* MII (both speeds) and RGMII 1000 speed. */
		agl_clk.s.clk_cnt = 1;
		अगर (prtx_ctl.s.mode == 0) अणु /* RGMII mode */
			अगर (phydev->speed == 10)
				agl_clk.s.clk_cnt = 50;
			अन्यथा अगर (phydev->speed == 100)
				agl_clk.s.clk_cnt = 5;
		पूर्ण
		cvmx_ग_लिखो_csr(p->agl + AGL_GMX_TX_CLK, agl_clk.u64);
	पूर्ण
पूर्ण

अटल व्योम octeon_mgmt_adjust_link(काष्ठा net_device *netdev)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);
	काष्ठा phy_device *phydev = netdev->phydev;
	अचिन्हित दीर्घ flags;
	पूर्णांक link_changed = 0;

	अगर (!phydev)
		वापस;

	spin_lock_irqsave(&p->lock, flags);


	अगर (!phydev->link && p->last_link)
		link_changed = -1;

	अगर (phydev->link &&
	    (p->last_duplex != phydev->duplex ||
	     p->last_link != phydev->link ||
	     p->last_speed != phydev->speed)) अणु
		octeon_mgmt_disable_link(p);
		link_changed = 1;
		octeon_mgmt_update_link(p);
		octeon_mgmt_enable_link(p);
	पूर्ण

	p->last_link = phydev->link;
	p->last_speed = phydev->speed;
	p->last_duplex = phydev->duplex;

	spin_unlock_irqrestore(&p->lock, flags);

	अगर (link_changed != 0) अणु
		अगर (link_changed > 0)
			netdev_info(netdev, "Link is up - %d/%s\n",
				    phydev->speed, phydev->duplex == DUPLEX_FULL ? "Full" : "Half");
		अन्यथा
			netdev_info(netdev, "Link is down\n");
	पूर्ण
पूर्ण

अटल पूर्णांक octeon_mgmt_init_phy(काष्ठा net_device *netdev)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);
	काष्ठा phy_device *phydev = शून्य;

	अगर (octeon_is_simulation() || p->phy_np == शून्य) अणु
		/* No PHYs in the simulator. */
		netअगर_carrier_on(netdev);
		वापस 0;
	पूर्ण

	phydev = of_phy_connect(netdev, p->phy_np,
				octeon_mgmt_adjust_link, 0,
				PHY_INTERFACE_MODE_MII);

	अगर (!phydev)
		वापस -EPROBE_DEFER;

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_mgmt_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);
	जोड़ cvmx_mixx_ctl mix_ctl;
	जोड़ cvmx_agl_gmx_inf_mode agl_gmx_inf_mode;
	जोड़ cvmx_mixx_oring1 oring1;
	जोड़ cvmx_mixx_iring1 iring1;
	जोड़ cvmx_agl_gmx_rxx_frm_ctl rxx_frm_ctl;
	जोड़ cvmx_mixx_irhwm mix_irhwm;
	जोड़ cvmx_mixx_orhwm mix_orhwm;
	जोड़ cvmx_mixx_पूर्णांकena mix_पूर्णांकena;
	काष्ठा sockaddr sa;

	/* Allocate ring buffers.  */
	p->tx_ring = kzalloc(ring_माप_प्रकारo_bytes(OCTEON_MGMT_TX_RING_SIZE),
			     GFP_KERNEL);
	अगर (!p->tx_ring)
		वापस -ENOMEM;
	p->tx_ring_handle =
		dma_map_single(p->dev, p->tx_ring,
			       ring_माप_प्रकारo_bytes(OCTEON_MGMT_TX_RING_SIZE),
			       DMA_BIसूचीECTIONAL);
	p->tx_next = 0;
	p->tx_next_clean = 0;
	p->tx_current_fill = 0;


	p->rx_ring = kzalloc(ring_माप_प्रकारo_bytes(OCTEON_MGMT_RX_RING_SIZE),
			     GFP_KERNEL);
	अगर (!p->rx_ring)
		जाओ err_nomem;
	p->rx_ring_handle =
		dma_map_single(p->dev, p->rx_ring,
			       ring_माप_प्रकारo_bytes(OCTEON_MGMT_RX_RING_SIZE),
			       DMA_BIसूचीECTIONAL);

	p->rx_next = 0;
	p->rx_next_fill = 0;
	p->rx_current_fill = 0;

	octeon_mgmt_reset_hw(p);

	mix_ctl.u64 = cvmx_पढ़ो_csr(p->mix + MIX_CTL);

	/* Bring it out of reset अगर needed. */
	अगर (mix_ctl.s.reset) अणु
		mix_ctl.s.reset = 0;
		cvmx_ग_लिखो_csr(p->mix + MIX_CTL, mix_ctl.u64);
		करो अणु
			mix_ctl.u64 = cvmx_पढ़ो_csr(p->mix + MIX_CTL);
		पूर्ण जबतक (mix_ctl.s.reset);
	पूर्ण

	अगर (OCTEON_IS_MODEL(OCTEON_CN5XXX)) अणु
		agl_gmx_inf_mode.u64 = 0;
		agl_gmx_inf_mode.s.en = 1;
		cvmx_ग_लिखो_csr(CVMX_AGL_GMX_INF_MODE, agl_gmx_inf_mode.u64);
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X)
		|| OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_X)) अणु
		/* Force compensation values, as they are not
		 * determined properly by HW
		 */
		जोड़ cvmx_agl_gmx_drv_ctl drv_ctl;

		drv_ctl.u64 = cvmx_पढ़ो_csr(CVMX_AGL_GMX_DRV_CTL);
		अगर (p->port) अणु
			drv_ctl.s.byp_en1 = 1;
			drv_ctl.s.nctl1 = 6;
			drv_ctl.s.pctl1 = 6;
		पूर्ण अन्यथा अणु
			drv_ctl.s.byp_en = 1;
			drv_ctl.s.nctl = 6;
			drv_ctl.s.pctl = 6;
		पूर्ण
		cvmx_ग_लिखो_csr(CVMX_AGL_GMX_DRV_CTL, drv_ctl.u64);
	पूर्ण

	oring1.u64 = 0;
	oring1.s.obase = p->tx_ring_handle >> 3;
	oring1.s.osize = OCTEON_MGMT_TX_RING_SIZE;
	cvmx_ग_लिखो_csr(p->mix + MIX_ORING1, oring1.u64);

	iring1.u64 = 0;
	iring1.s.ibase = p->rx_ring_handle >> 3;
	iring1.s.isize = OCTEON_MGMT_RX_RING_SIZE;
	cvmx_ग_लिखो_csr(p->mix + MIX_IRING1, iring1.u64);

	स_नकल(sa.sa_data, netdev->dev_addr, ETH_ALEN);
	octeon_mgmt_set_mac_address(netdev, &sa);

	octeon_mgmt_change_mtu(netdev, netdev->mtu);

	/* Enable the port HW. Packets are not allowed until
	 * cvmx_mgmt_port_enable() is called.
	 */
	mix_ctl.u64 = 0;
	mix_ctl.s.crc_strip = 1;    /* Strip the ending CRC */
	mix_ctl.s.en = 1;           /* Enable the port */
	mix_ctl.s.nbtarb = 0;       /* Arbitration mode */
	/* MII CB-request FIFO programmable high watermark */
	mix_ctl.s.mrq_hwm = 1;
#अगर_घोषित __LITTLE_ENDIAN
	mix_ctl.s.lendian = 1;
#पूर्ण_अगर
	cvmx_ग_लिखो_csr(p->mix + MIX_CTL, mix_ctl.u64);

	/* Read the PHY to find the mode of the पूर्णांकerface. */
	अगर (octeon_mgmt_init_phy(netdev)) अणु
		dev_err(p->dev, "Cannot initialize PHY on MIX%d.\n", p->port);
		जाओ err_noirq;
	पूर्ण

	/* Set the mode of the पूर्णांकerface, RGMII/MII. */
	अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX) && netdev->phydev) अणु
		जोड़ cvmx_agl_prtx_ctl agl_prtx_ctl;
		पूर्णांक rgmii_mode =
			(linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
					   netdev->phydev->supported) |
			 linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
					   netdev->phydev->supported)) != 0;

		agl_prtx_ctl.u64 = cvmx_पढ़ो_csr(p->agl_prt_ctl);
		agl_prtx_ctl.s.mode = rgmii_mode ? 0 : 1;
		cvmx_ग_लिखो_csr(p->agl_prt_ctl,	agl_prtx_ctl.u64);

		/* MII घड़ीs counts are based on the 125Mhz
		 * reference, which has an 8nS period. So our delays
		 * need to be multiplied by this factor.
		 */
#घोषणा NS_PER_PHY_CLK 8

		/* Take the DLL and घड़ी tree out of reset */
		agl_prtx_ctl.u64 = cvmx_पढ़ो_csr(p->agl_prt_ctl);
		agl_prtx_ctl.s.clkrst = 0;
		अगर (rgmii_mode) अणु
			agl_prtx_ctl.s.dllrst = 0;
			agl_prtx_ctl.s.clktx_byp = 0;
		पूर्ण
		cvmx_ग_लिखो_csr(p->agl_prt_ctl,	agl_prtx_ctl.u64);
		cvmx_पढ़ो_csr(p->agl_prt_ctl); /* Force ग_लिखो out beक्रमe रुको */

		/* Wait क्रम the DLL to lock. External 125 MHz
		 * reference घड़ी must be stable at this poपूर्णांक.
		 */
		ndelay(256 * NS_PER_PHY_CLK);

		/* Enable the पूर्णांकerface */
		agl_prtx_ctl.u64 = cvmx_पढ़ो_csr(p->agl_prt_ctl);
		agl_prtx_ctl.s.enable = 1;
		cvmx_ग_लिखो_csr(p->agl_prt_ctl, agl_prtx_ctl.u64);

		/* Read the value back to क्रमce the previous ग_लिखो */
		agl_prtx_ctl.u64 = cvmx_पढ़ो_csr(p->agl_prt_ctl);

		/* Enable the compensation controller */
		agl_prtx_ctl.s.comp = 1;
		agl_prtx_ctl.s.drv_byp = 0;
		cvmx_ग_लिखो_csr(p->agl_prt_ctl,	agl_prtx_ctl.u64);
		/* Force ग_लिखो out beक्रमe रुको. */
		cvmx_पढ़ो_csr(p->agl_prt_ctl);

		/* For compensation state to lock. */
		ndelay(1040 * NS_PER_PHY_CLK);

		/* Default Interframe Gaps are too small.  Recommended
		 * workaround is.
		 *
		 * AGL_GMX_TX_IFG[IFG1]=14
		 * AGL_GMX_TX_IFG[IFG2]=10
		 */
		cvmx_ग_लिखो_csr(CVMX_AGL_GMX_TX_IFG, 0xae);
	पूर्ण

	octeon_mgmt_rx_fill_ring(netdev);

	/* Clear statistics. */
	/* Clear on पढ़ो. */
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_STATS_CTL, 1);
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_STATS_PKTS_DRP, 0);
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_STATS_PKTS_BAD, 0);

	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_TX_STATS_CTL, 1);
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_TX_STAT0, 0);
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_TX_STAT1, 0);

	/* Clear any pending पूर्णांकerrupts */
	cvmx_ग_लिखो_csr(p->mix + MIX_ISR, cvmx_पढ़ो_csr(p->mix + MIX_ISR));

	अगर (request_irq(p->irq, octeon_mgmt_पूर्णांकerrupt, 0, netdev->name,
			netdev)) अणु
		dev_err(p->dev, "request_irq(%d) failed.\n", p->irq);
		जाओ err_noirq;
	पूर्ण

	/* Interrupt every single RX packet */
	mix_irhwm.u64 = 0;
	mix_irhwm.s.irhwm = 0;
	cvmx_ग_लिखो_csr(p->mix + MIX_IRHWM, mix_irhwm.u64);

	/* Interrupt when we have 1 or more packets to clean.  */
	mix_orhwm.u64 = 0;
	mix_orhwm.s.orhwm = 0;
	cvmx_ग_लिखो_csr(p->mix + MIX_ORHWM, mix_orhwm.u64);

	/* Enable receive and transmit पूर्णांकerrupts */
	mix_पूर्णांकena.u64 = 0;
	mix_पूर्णांकena.s.ithena = 1;
	mix_पूर्णांकena.s.othena = 1;
	cvmx_ग_लिखो_csr(p->mix + MIX_INTENA, mix_पूर्णांकena.u64);

	/* Enable packet I/O. */

	rxx_frm_ctl.u64 = 0;
	rxx_frm_ctl.s.ptp_mode = p->has_rx_tstamp ? 1 : 0;
	rxx_frm_ctl.s.pre_align = 1;
	/* When set, disables the length check क्रम non-min sized pkts
	 * with padding in the client data.
	 */
	rxx_frm_ctl.s.pad_len = 1;
	/* When set, disables the length check क्रम VLAN pkts */
	rxx_frm_ctl.s.vlan_len = 1;
	/* When set, PREAMBLE checking is  less strict */
	rxx_frm_ctl.s.pre_मुक्त = 1;
	/* Control Pause Frames can match station SMAC */
	rxx_frm_ctl.s.ctl_smac = 0;
	/* Control Pause Frames can match globally assign Multicast address */
	rxx_frm_ctl.s.ctl_mcst = 1;
	/* Forward छोड़ो inक्रमmation to TX block */
	rxx_frm_ctl.s.ctl_bck = 1;
	/* Drop Control Pause Frames */
	rxx_frm_ctl.s.ctl_drp = 1;
	/* Strip off the preamble */
	rxx_frm_ctl.s.pre_strp = 1;
	/* This port is configured to send PREAMBLE+SFD to begin every
	 * frame.  GMX checks that the PREAMBLE is sent correctly.
	 */
	rxx_frm_ctl.s.pre_chk = 1;
	cvmx_ग_लिखो_csr(p->agl + AGL_GMX_RX_FRM_CTL, rxx_frm_ctl.u64);

	/* Configure the port duplex, speed and enables */
	octeon_mgmt_disable_link(p);
	अगर (netdev->phydev)
		octeon_mgmt_update_link(p);
	octeon_mgmt_enable_link(p);

	p->last_link = 0;
	p->last_speed = 0;
	/* PHY is not present in simulator. The carrier is enabled
	 * जबतक initializing the phy क्रम simulator, leave it enabled.
	 */
	अगर (netdev->phydev) अणु
		netअगर_carrier_off(netdev);
		phy_start(netdev->phydev);
	पूर्ण

	netअगर_wake_queue(netdev);
	napi_enable(&p->napi);

	वापस 0;
err_noirq:
	octeon_mgmt_reset_hw(p);
	dma_unmap_single(p->dev, p->rx_ring_handle,
			 ring_माप_प्रकारo_bytes(OCTEON_MGMT_RX_RING_SIZE),
			 DMA_BIसूचीECTIONAL);
	kमुक्त(p->rx_ring);
err_nomem:
	dma_unmap_single(p->dev, p->tx_ring_handle,
			 ring_माप_प्रकारo_bytes(OCTEON_MGMT_TX_RING_SIZE),
			 DMA_BIसूचीECTIONAL);
	kमुक्त(p->tx_ring);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक octeon_mgmt_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);

	napi_disable(&p->napi);
	netअगर_stop_queue(netdev);

	अगर (netdev->phydev) अणु
		phy_stop(netdev->phydev);
		phy_disconnect(netdev->phydev);
	पूर्ण

	netअगर_carrier_off(netdev);

	octeon_mgmt_reset_hw(p);

	मुक्त_irq(p->irq, netdev);

	/* dma_unmap is a nop on Octeon, so just मुक्त everything.  */
	skb_queue_purge(&p->tx_list);
	skb_queue_purge(&p->rx_list);

	dma_unmap_single(p->dev, p->rx_ring_handle,
			 ring_माप_प्रकारo_bytes(OCTEON_MGMT_RX_RING_SIZE),
			 DMA_BIसूचीECTIONAL);
	kमुक्त(p->rx_ring);

	dma_unmap_single(p->dev, p->tx_ring_handle,
			 ring_माप_प्रकारo_bytes(OCTEON_MGMT_TX_RING_SIZE),
			 DMA_BIसूचीECTIONAL);
	kमुक्त(p->tx_ring);

	वापस 0;
पूर्ण

अटल netdev_tx_t
octeon_mgmt_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);
	जोड़ mgmt_port_ring_entry re;
	अचिन्हित दीर्घ flags;
	netdev_tx_t rv = NETDEV_TX_BUSY;

	re.d64 = 0;
	re.s.tstamp = ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) != 0);
	re.s.len = skb->len;
	re.s.addr = dma_map_single(p->dev, skb->data,
				   skb->len,
				   DMA_TO_DEVICE);

	spin_lock_irqsave(&p->tx_list.lock, flags);

	अगर (unlikely(p->tx_current_fill >= ring_max_fill(OCTEON_MGMT_TX_RING_SIZE) - 1)) अणु
		spin_unlock_irqrestore(&p->tx_list.lock, flags);
		netअगर_stop_queue(netdev);
		spin_lock_irqsave(&p->tx_list.lock, flags);
	पूर्ण

	अगर (unlikely(p->tx_current_fill >=
		     ring_max_fill(OCTEON_MGMT_TX_RING_SIZE))) अणु
		spin_unlock_irqrestore(&p->tx_list.lock, flags);
		dma_unmap_single(p->dev, re.s.addr, re.s.len,
				 DMA_TO_DEVICE);
		जाओ out;
	पूर्ण

	__skb_queue_tail(&p->tx_list, skb);

	/* Put it in the ring.  */
	p->tx_ring[p->tx_next] = re.d64;
	p->tx_next = (p->tx_next + 1) % OCTEON_MGMT_TX_RING_SIZE;
	p->tx_current_fill++;

	spin_unlock_irqrestore(&p->tx_list.lock, flags);

	dma_sync_single_क्रम_device(p->dev, p->tx_ring_handle,
				   ring_माप_प्रकारo_bytes(OCTEON_MGMT_TX_RING_SIZE),
				   DMA_BIसूचीECTIONAL);

	netdev->stats.tx_packets++;
	netdev->stats.tx_bytes += skb->len;

	/* Ring the bell.  */
	cvmx_ग_लिखो_csr(p->mix + MIX_ORING2, 1);

	netअगर_trans_update(netdev);
	rv = NETDEV_TX_OK;
out:
	octeon_mgmt_update_tx_stats(netdev);
	वापस rv;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम octeon_mgmt_poll_controller(काष्ठा net_device *netdev)
अणु
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);

	octeon_mgmt_receive_packets(p, 16);
	octeon_mgmt_update_rx_stats(netdev);
पूर्ण
#पूर्ण_अगर

अटल व्योम octeon_mgmt_get_drvinfo(काष्ठा net_device *netdev,
				    काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
पूर्ण

अटल पूर्णांक octeon_mgmt_nway_reset(काष्ठा net_device *dev)
अणु
	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (dev->phydev)
		वापस phy_start_aneg(dev->phydev);

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops octeon_mgmt_ethtool_ops = अणु
	.get_drvinfo = octeon_mgmt_get_drvinfo,
	.nway_reset = octeon_mgmt_nway_reset,
	.get_link = ethtool_op_get_link,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops octeon_mgmt_ops = अणु
	.nकरो_खोलो =			octeon_mgmt_खोलो,
	.nकरो_stop =			octeon_mgmt_stop,
	.nकरो_start_xmit =		octeon_mgmt_xmit,
	.nकरो_set_rx_mode =		octeon_mgmt_set_rx_filtering,
	.nकरो_set_mac_address =		octeon_mgmt_set_mac_address,
	.nकरो_करो_ioctl =			octeon_mgmt_ioctl,
	.nकरो_change_mtu =		octeon_mgmt_change_mtu,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller =		octeon_mgmt_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक octeon_mgmt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *netdev;
	काष्ठा octeon_mgmt *p;
	स्थिर __be32 *data;
	काष्ठा resource *res_mix;
	काष्ठा resource *res_agl;
	काष्ठा resource *res_agl_prt_ctl;
	पूर्णांक len;
	पूर्णांक result;

	netdev = alloc_etherdev(माप(काष्ठा octeon_mgmt));
	अगर (netdev == शून्य)
		वापस -ENOMEM;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	platक्रमm_set_drvdata(pdev, netdev);
	p = netdev_priv(netdev);
	netअगर_napi_add(netdev, &p->napi, octeon_mgmt_napi_poll,
		       OCTEON_MGMT_NAPI_WEIGHT);

	p->netdev = netdev;
	p->dev = &pdev->dev;
	p->has_rx_tstamp = false;

	data = of_get_property(pdev->dev.of_node, "cell-index", &len);
	अगर (data && len == माप(*data)) अणु
		p->port = be32_to_cpup(data);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "no 'cell-index' property\n");
		result = -ENXIO;
		जाओ err;
	पूर्ण

	snम_लिखो(netdev->name, IFNAMSIZ, "mgmt%d", p->port);

	result = platक्रमm_get_irq(pdev, 0);
	अगर (result < 0)
		जाओ err;

	p->irq = result;

	res_mix = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res_mix == शून्य) अणु
		dev_err(&pdev->dev, "no 'reg' resource\n");
		result = -ENXIO;
		जाओ err;
	पूर्ण

	res_agl = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res_agl == शून्य) अणु
		dev_err(&pdev->dev, "no 'reg' resource\n");
		result = -ENXIO;
		जाओ err;
	पूर्ण

	res_agl_prt_ctl = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 3);
	अगर (res_agl_prt_ctl == शून्य) अणु
		dev_err(&pdev->dev, "no 'reg' resource\n");
		result = -ENXIO;
		जाओ err;
	पूर्ण

	p->mix_phys = res_mix->start;
	p->mix_size = resource_size(res_mix);
	p->agl_phys = res_agl->start;
	p->agl_size = resource_size(res_agl);
	p->agl_prt_ctl_phys = res_agl_prt_ctl->start;
	p->agl_prt_ctl_size = resource_size(res_agl_prt_ctl);


	अगर (!devm_request_mem_region(&pdev->dev, p->mix_phys, p->mix_size,
				     res_mix->name)) अणु
		dev_err(&pdev->dev, "request_mem_region (%s) failed\n",
			res_mix->name);
		result = -ENXIO;
		जाओ err;
	पूर्ण

	अगर (!devm_request_mem_region(&pdev->dev, p->agl_phys, p->agl_size,
				     res_agl->name)) अणु
		result = -ENXIO;
		dev_err(&pdev->dev, "request_mem_region (%s) failed\n",
			res_agl->name);
		जाओ err;
	पूर्ण

	अगर (!devm_request_mem_region(&pdev->dev, p->agl_prt_ctl_phys,
				     p->agl_prt_ctl_size, res_agl_prt_ctl->name)) अणु
		result = -ENXIO;
		dev_err(&pdev->dev, "request_mem_region (%s) failed\n",
			res_agl_prt_ctl->name);
		जाओ err;
	पूर्ण

	p->mix = (u64)devm_ioremap(&pdev->dev, p->mix_phys, p->mix_size);
	p->agl = (u64)devm_ioremap(&pdev->dev, p->agl_phys, p->agl_size);
	p->agl_prt_ctl = (u64)devm_ioremap(&pdev->dev, p->agl_prt_ctl_phys,
					   p->agl_prt_ctl_size);
	अगर (!p->mix || !p->agl || !p->agl_prt_ctl) अणु
		dev_err(&pdev->dev, "failed to map I/O memory\n");
		result = -ENOMEM;
		जाओ err;
	पूर्ण

	spin_lock_init(&p->lock);

	skb_queue_head_init(&p->tx_list);
	skb_queue_head_init(&p->rx_list);
	tasklet_setup(&p->tx_clean_tasklet,
		      octeon_mgmt_clean_tx_tasklet);

	netdev->priv_flags |= IFF_UNICAST_FLT;

	netdev->netdev_ops = &octeon_mgmt_ops;
	netdev->ethtool_ops = &octeon_mgmt_ethtool_ops;

	netdev->min_mtu = 64 - OCTEON_MGMT_RX_HEADROOM;
	netdev->max_mtu = 16383 - OCTEON_MGMT_RX_HEADROOM - VLAN_HLEN;

	result = of_get_mac_address(pdev->dev.of_node, netdev->dev_addr);
	अगर (result)
		eth_hw_addr_अक्रमom(netdev);

	p->phy_np = of_parse_phandle(pdev->dev.of_node, "phy-handle", 0);

	result = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (result)
		जाओ err;

	netअगर_carrier_off(netdev);
	result = रेजिस्टर_netdev(netdev);
	अगर (result)
		जाओ err;

	वापस 0;

err:
	of_node_put(p->phy_np);
	मुक्त_netdev(netdev);
	वापस result;
पूर्ण

अटल पूर्णांक octeon_mgmt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *netdev = platक्रमm_get_drvdata(pdev);
	काष्ठा octeon_mgmt *p = netdev_priv(netdev);

	unरेजिस्टर_netdev(netdev);
	of_node_put(p->phy_np);
	मुक्त_netdev(netdev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id octeon_mgmt_match[] = अणु
	अणु
		.compatible = "cavium,octeon-5750-mix",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, octeon_mgmt_match);

अटल काष्ठा platक्रमm_driver octeon_mgmt_driver = अणु
	.driver = अणु
		.name		= "octeon_mgmt",
		.of_match_table = octeon_mgmt_match,
	पूर्ण,
	.probe		= octeon_mgmt_probe,
	.हटाओ		= octeon_mgmt_हटाओ,
पूर्ण;

module_platक्रमm_driver(octeon_mgmt_driver);

MODULE_SOFTDEP("pre: mdio-cavium");
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR("David Daney");
MODULE_LICENSE("GPL");
